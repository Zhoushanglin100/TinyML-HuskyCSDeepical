### train
python3 train_1D.py -a simple5a --epoch 50 --lr 0.01 --loss f1 --batchsz 256 --ext _Sf1bz256lr0.01

### test
python3 test_1D.py --net_name saved_models/IEGM_net_Sf1bz256lr0.01.pkl -b 1

### convert 
python3 pt2onnx.py IEGM_net_Sf1bz256lr0.01