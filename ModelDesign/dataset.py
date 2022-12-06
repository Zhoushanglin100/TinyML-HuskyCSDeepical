import pywt, os, copy, csv, random
import torch
import numpy as np
import pandas as pd
from torch.utils.data import Dataset
from sklearn.preprocessing import scale
from scipy import signal


def loadCSV(csvf):
    """
    return a dict saving the information of csv
    :param splitFile: csv file name
    :return: {label:[file1, file2 ...]}
    """
    dictLabels = {}
    with open(csvf) as csvfile:
        csvreader = csv.reader(csvfile, delimiter=',')
        next(csvreader, None)  # skip (filename, label)
        for i, row in enumerate(csvreader):
            filename = row[0]
            label = row[1]

            # append filename to current label
            if label in dictLabels.keys():
                dictLabels[label].append(filename)
            else:
                dictLabels[label] = [filename]
    return dictLabels


def txt_to_numpy(filename, row):
    file = open(filename)
    lines = file.readlines()
    datamat = np.arange(row, dtype=np.float)
    row_count = 0
    for line in lines:
        line = line.strip().split(' ')
        datamat[row_count] = line[0]
        row_count += 1

    return datamat


def resample(sig, target_point_num=None):
    sig = signal.resample(sig, target_point_num) if target_point_num else sig
    return sig

def scaling(X, sigma=0.1):
    scalingFactor = np.random.normal(loc=1.0, scale=sigma, size=(1, X.shape[1]))
    myNoise = np.matmul(np.ones((X.shape[0], 1)), scalingFactor).reshape(1, -1, 1)
    return X * myNoise

def verflip(sig):
    return sig[::-1, :]

def shift(sig):
    for col in range(sig.shape[1]):
        # offset = np.random.choice(range(-interval, interval))
        offset = random.gauss(0, 1)
        sig[:, col] += offset
    return sig

def transform(sig, mode='test'):

    if mode == "train":
        if np.random.randn() > 0.5: sig = scaling(sig)
        if np.random.randn() > 0.5: sig = verflip(sig)
        if np.random.randn() > 0.5: sig = shift(sig)

    # sig = scaling(sig)
    # sig = verflip(sig)
    # sig = shift(sig)

    sig = sig.transpose()
    sig = torch.tensor(sig.copy(), dtype=torch.float)

    return sig


class IEGMDataset_tfm():

    def __init__(self, root_dir, indice_dir, mode, size):
        self.root_dir = root_dir
        self.indice_dir = indice_dir
        self.size = size
        self.names_list = []
        self.mode = mode
        # self.transform = transform

        csvdata_all = loadCSV(os.path.join(self.indice_dir, self.mode + '_indice.csv'))

        for i, (k, v) in enumerate(csvdata_all.items()):
            self.names_list.append(str(k) + ' ' + str(v[0]))

    def __getitem__(self, idx):

        text_path = self.root_dir + self.names_list[idx].split(' ')[0]
        if not os.path.isfile(text_path):
            print(text_path + 'does not exist')
            return None

        IEGM_seg = txt_to_numpy(text_path, self.size).reshape(1, self.size, 1)
        IEGM_seg = transform(IEGM_seg, self.mode)

        label = int(self.names_list[idx].split(' ')[1])
        sample = {'IEGM_seg': IEGM_seg, 'label': label}

        return sample

    def __len__(self):
        return len(self.names_list)


# if __name__ == '__main__':

#     BATCH_SIZE = 32
#     BATCH_SIZE_TEST = 32
#     SIZE = 1250
#     path_data = '../data/tinyml_contest_data_training/'
#     path_indices = './data_indices/'

#     d = IEGMDataset_tfm(root_dir=path_data,
#                      indice_dir=path_indices,
#                      mode='train',
#                      size=SIZE)
#     print(d[0])