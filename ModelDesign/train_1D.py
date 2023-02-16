import argparse
import numpy as np
import random

import torch
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
import torch.nn as nn
import torch.optim as optim
from help_code_demo import *
from loss import F1_Loss, Fbeta_Loss
from dataset import IEGMDataset_tfm
from models.model_1 import *
from sklearn.metrics import confusion_matrix

try:
    import wandb
    has_wandb = True
except ImportError: 
    has_wandb = False

# ------------------------------
def main():
    # Hyperparameters
    BATCH_SIZE = args.batchsz
    BATCH_SIZE_TEST = args.batchsz
    LR = args.lr
    EPOCH = args.epoch
    SIZE = args.size
    path_data = args.path_data
    path_indices = args.path_indices
    # seed = 2222 # 0.960
    seed = 8888

    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)

    # Instantiating NN
    net = IEGMNetSimple5a()
    net = net.float().to(device)

    print(net)
    for name, W in net.named_parameters():
        print(name, W.shape)

    if has_wandb and args.enable_wandb:
        wandb.watch(net)

    # Start dataset loading
    if args.dataset == "orig":
        trainset = IEGM_DataSET(root_dir=path_data,
                                indice_dir=path_indices,
                                mode='train',
                                size=SIZE,
                                transform=transforms.Compose([ToTensor()])
                                )
        testset =IEGM_DataSET(root_dir=path_data,
                            indice_dir=path_indices,
                            mode='test',
                            size=SIZE,
                            transform=transforms.Compose([ToTensor()])
                            )
    elif args.dataset == "ecg":
        trainset = IEGMDataset_tfm(root_dir=path_data,
                                indice_dir=path_indices,
                                mode='train',
                                size=SIZE)
        testset =IEGMDataset_tfm(root_dir=path_data,
                            indice_dir=path_indices,
                            mode='test',
                            size=SIZE)

    trainloader = DataLoader(trainset, batch_size=BATCH_SIZE, shuffle=True, num_workers=4)
    testloader = DataLoader(testset, batch_size=BATCH_SIZE_TEST, shuffle=True, num_workers=4)

    print("Training Dataset loading finish.")

    if args.loss == "f1":
        criterion = F1_Loss()
    elif args.loss == "fb":
        criterion = Fbeta_Loss()
    elif args.loss == 'ce':
        criterion = nn.CrossEntropyLoss()
    else:
        print("Not supported, use fbeta loss")
        criterion = Fbeta_Loss()

    optimizer = optim.Adam(net.parameters(), lr=LR)
    epoch_num = EPOCH

    max_test_fb = 0.0

    Train_loss, Train_acc = [], []
    Test_loss, Test_acc = [], []

    train_f1_lst, train_fb_lst, train_precision_lst, train_recall_lst = [], [], [], []
    test_f1_lst, test_fb_lst, test_precision_lst, test_recall_lst = [], [], [], []

    print("Start training")
    for epoch in range(epoch_num):  # loop over the dataset multiple times (specify the #epoch)

        ### Train
        net.train()
        running_loss = 0.0
        true_label, pred_label = [], []

        for j, data in enumerate(trainloader, 0):
            inputs, labels = data['IEGM_seg'], data['label']
            inputs = inputs.float().to(device)
            labels = labels.to(device)

            optimizer.zero_grad()
            outputs = net(inputs)
            
            loss = criterion(outputs, labels)
            _, predicted = torch.max(outputs.data, 1)

            running_loss += loss.item()
            loss.backward()
            optimizer.step()

            true_label.extend(labels.detach().cpu().numpy())
            pred_label.extend(predicted.detach().cpu().numpy())

        C = confusion_matrix(true_label, pred_label)
        acc = (C[0][0] + C[1][1]) / (C[0][0] + C[0][1] + C[1][0] + C[1][1])
        precision = C[1][1] / (C[1][1] + C[0][1])
        recall = C[1][1] / (C[1][1] + C[1][0])
        f1_score = (2 * precision * recall) / (precision + recall)
        fb_score = (1+2**2) * (precision * recall) / ((2**2)*precision + recall)

        if has_wandb and args.enable_wandb:
            wandb.log({"train/acc": acc.item()})
            wandb.log({"train/precision": precision.item()})
            wandb.log({"train/recall": recall.item()})
            wandb.log({"train/f1_score": f1_score.item()})
            wandb.log({"train/fb_score": fb_score.item()})

        print('Epoch %d \nTrain Acc: %.5f Train loss: %.5f' %
              (epoch + 1, acc, running_loss / len(trainloader.dataset)))
        print("precision: {:.5f}, recall: {:.5f}, F1_score: {:.5f}, Fb_score: {:.5f}".format(precision, recall, f1_score, fb_score))

        Train_loss.append(running_loss / len(trainloader.dataset))
        Train_acc.append(acc.item())
        train_f1_lst.append(f1_score.item())
        train_fb_lst.append(fb_score.item())
        train_precision_lst.append(precision.item())
        train_recall_lst.append(recall.item())

        ### Test
        net.eval()

        running_loss_test = 0.0
        true_label_test, pred_label_test = [], []

        with torch.no_grad():
            for data_test in testloader:
                
                IEGM_test, labels_test = data_test['IEGM_seg'], data_test['label']
                IEGM_test = IEGM_test.float().to(device)
                labels_test = labels_test.to(device)

                outputs_test = net(IEGM_test)

                if args.arch  == "simple5a1":
                    loss_test = criterion(outputs_test, labels_test)
                    predicted_test = torch.round(torch.sigmoid(outputs_test.squeeze()))
                else:
                    loss_test = criterion(outputs_test, labels_test)
                    _, predicted_test = torch.max(outputs_test.data, 1)
                
                running_loss_test += loss_test.item()

                true_label_test.extend(labels_test.detach().cpu().numpy())
                pred_label_test.extend(predicted_test.detach().cpu().numpy())

        test_C = confusion_matrix(true_label_test, pred_label_test)
        test_acc = (test_C[0][0] + test_C[1][1]) / (test_C[0][0] + test_C[0][1] + test_C[1][0] + test_C[1][1])
        test_precision = test_C[1][1] / (test_C[1][1] + test_C[0][1])
        test_recall = test_C[1][1] / (test_C[1][1] + test_C[1][0])
        test_f1_score = (2 * test_precision * test_recall) / (test_precision + test_recall)
        test_fb_score = (1+2**2) * (test_precision * test_recall) / ((2**2)*test_precision + test_recall)

        if has_wandb and args.enable_wandb:
            wandb.log({"test/acc": test_acc.item()})
            wandb.log({"test/precision": test_precision.item()})
            wandb.log({"test/recall": test_recall.item()})
            wandb.log({"test/f1_score": test_f1_score.item()})
            wandb.log({"test/fb_score": test_fb_score.item()})

        print(f'Test || Loss:{(running_loss_test/len(testloader.dataset)):.5f} Acc: {test_acc:.5f}')
        print(f'        Precision: {test_precision:.5f} Recall: {test_recall:.5f} F1: {test_f1_score:.5f} FB: {test_fb_score:.5f} ')

        Test_loss.append(running_loss_test/len(testloader.dataset))
        Test_acc.append(test_acc.item())
        test_f1_lst.append(test_f1_score.item())
        test_fb_lst.append(test_fb_score.item())
        test_precision_lst.append(test_precision.item())
        test_recall_lst.append(test_recall.item())

        ### save best model
        if test_fb_score >= max_test_fb:
            max_test_fb = max(max_test_fb, test_fb_score)
            torch.save(net, f'./saved_models/IEGM_net{args.ext}.pkl')
            torch.save(net.state_dict(), f'./saved_models/IEGM_net_state_dict{args.ext}.pkl')

    print("Best Fb:", max_test_fb)

    file = open(f'./result/result{args.ext}.txt', 'w')

    file.write("Train_loss\n")
    file.write(str(Train_loss))
    file.write('\n\n')
    file.write("Train_acc\n")
    file.write(str(Train_acc))
    file.write('\n\n')

    file.write("Test_loss\n")
    file.write(str(Test_loss))
    file.write('\n\n')
    file.write("Test_acc\n")
    file.write(str(Test_acc))
    file.write('\n\n')

    file.write("Train_F1_score\n")
    file.write(str(train_f1_lst))
    file.write('\n\n')
    file.write("Test_F1_score\n")
    file.write(str(test_f1_lst))
    file.write('\n\n')

    file.write("Train_Fb_score\n")
    file.write(str(train_fb_lst))
    file.write('\n\n')
    file.write("Test_Fb_score\n")
    file.write(str(test_fb_lst))
    file.write('\n\n')

    file.write("Train_Precision\n")
    file.write(str(train_precision_lst))
    file.write('\n\n')    
    file.write("Test_Precision\n")
    file.write(str(test_precision_lst))
    file.write('\n\n')

    file.write("Train_Recall\n")
    file.write(str(train_recall_lst))
    file.write('\n\n')
    file.write("Test_Recall\n")
    file.write(str(test_recall_lst))
    file.write('\n\n')

    print('Finish training')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--arch', '-a', type=str, default='simple', help='model architecture', )
    parser.add_argument('--dataset', '-d', type=str, default='ecg', help='dataset with transform, [orig, ecg]')
    parser.add_argument('--loss', type=str, default='ce', help='loss function, [f1, fb, ce]')
    parser.add_argument('--epoch', type=int, default=50, help='epoch number', )
    parser.add_argument('--lr', type=float, default=0.0001, help='learning rate', )
    parser.add_argument('--batchsz', type=int, default=32, help='total batchsz for train')
    parser.add_argument('--size', type=int, default=1250)
    parser.add_argument('--path_data', type=str, default='../../data/tinyml_contest_data_training/')
    parser.add_argument('--path_indices', type=str, default='./data_indices/')
    parser.add_argument('--ext', type=str, default='', help='save extension')
    parser.add_argument('--enable-wandb', action='store_true', default=False,
                            help='whether to use wandb to log')
    args = parser.parse_args()

    if has_wandb and args.enable_wandb:
        wandb.init(project='TinyML', entity='zhoushanglin100')
        wandb.init(config=args)
        wandb.config.update(args)

    use_cuda = torch.cuda.is_available()
    device = torch.device("cuda" if use_cuda else "cpu")

    print("device is --------------", device)

    main()
