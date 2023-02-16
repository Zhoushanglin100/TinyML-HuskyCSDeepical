import torch, sys

model_name = sys.argv[1]

# net_path = f"./checkpoints/{model_name}.pkl"
net_path = f"./saved_models/{model_name}.pkl"
net_name = f'./cvt_onnx/{model_name}'
size = 1250

net = torch.load(net_path, map_location=torch.device('cpu'))
dummy_input = torch.randn(1, 1, size, 1).to(torch.float32)
optName = str(net_name)+'.onnx'
torch.onnx.export(net, dummy_input, optName, verbose=True)

