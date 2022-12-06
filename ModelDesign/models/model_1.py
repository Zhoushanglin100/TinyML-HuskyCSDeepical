import torch.nn as nn

class IEGMNetSimple5a(nn.Module):
    def __init__(self):
        super(IEGMNetSimple5a, self).__init__()
        
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels=1, out_channels=2, kernel_size=(6, 1), stride=(2,1), padding=0),
            nn.ReLU(True),
            nn.BatchNorm2d(2, affine=True, track_running_stats=True, eps=1e-5, momentum=0.1),
        )

        self.conv2 = nn.Sequential(
            nn.Conv2d(in_channels=2, out_channels=3, kernel_size=(5, 1), stride=(2,1), padding=0),
            nn.ReLU(True),
            nn.BatchNorm2d(3, affine=True, track_running_stats=True, eps=1e-5, momentum=0.1),
        )

        self.conv3 = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=5, kernel_size=(4, 1), stride=(2,1), padding=0),
            nn.ReLU(True),
            nn.BatchNorm2d(5, affine=True, track_running_stats=True, eps=1e-5, momentum=0.1),
        )

        self.conv4 = nn.Sequential(
            nn.Conv2d(in_channels=5, out_channels=10, kernel_size=(4, 1), stride=(2,1), padding=0),
            nn.ReLU(True),
            nn.BatchNorm2d(10, affine=True, track_running_stats=True, eps=1e-5, momentum=0.1),
        )

        self.conv5 = nn.Sequential(
            nn.Conv2d(in_channels=10, out_channels=10, kernel_size=(4, 1), stride=(2,1), padding=0),
            nn.ReLU(True),
            nn.BatchNorm2d(10, affine=True, track_running_stats=True, eps=1e-5, momentum=0.1),
        )

        self.linear = nn.Linear(370, 2)

    def forward(self, input):

        conv1_output = self.conv1(input)
        conv2_output = self.conv2(conv1_output)
        conv3_output = self.conv3(conv2_output)
        conv4_output = self.conv4(conv3_output)
        conv5_output = self.conv5(conv4_output)
        conv5_output = conv5_output.view(-1, 370)

        out = self.linear(conv5_output)

        return out
