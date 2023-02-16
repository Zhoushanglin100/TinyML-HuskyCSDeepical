# Code for TinyML Contest at ICCAD 2022

This is the submission from team **HuskyCSDeepical** to [2022 ACM/IEEE TinyML Design Contest at ICCAD](https://tinymlcontest.github.io/TinyML-Design-Contest/index.html). Data can be found [here](https://drive.google.com/file/d/1I_bxfTrfxPP9S4pSp_tTSNFAHLP0vkoI/view?usp=share_link).

## Folder Structure

- **./ModelDesign/**: The folder for the NN training design in python.

- **./test-code/**: The folder which consists of the C code generated from the [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) platform. 

- **IEGM_net_Sf1bz256lr0.01.onnx**: The .ONNX file that contains the nodel weights and architecture which was utilized with the STMCube MCU platform to generate the MDK-ARM Keil project with the C code.


## How to run

### NN Model Design and Training

Please find the code in folder **./ModelDesign**

- Requirement

    ```bash
    pip install -r requirement.txt
    ```

- Training 

    ```bash
    python train_1D.py --path_data <DATA_PATH> -a simple5a --epoch 100 --lr 0.01 --loss f1 --batchsz 256 --ext _Sf1bz256lr0.01
    ```
   - Model will be saved to "./ModelDesign/saved_models/"

- Validation

    ```bash
    python test_1D.py --path_data <DATA_PATH> --net_name saved_models/IEGM_net_Sf1bz256lr0.01.pkl -b 1
    ```
- Convert saved model to ONNX

    ```bash
    python pt2onnx.py IEGM_net_Sf1bz256lr0.01
    ```

Example running process can be found in **./ModelDesign/run.sh**


### Deploy and Validate model on MCU Platform

- Requirement

    1. STM32CubeMX platform with enabling of the XCubeAI packages. 
    
    2. [MDK5 Microcontroller IDE developed by ARM](https://www2.keil.com/mdk5/)

    3. Please follow the [tutorial](https://github.com/tinymlcontest/tinyml_contest2022_demo_example/blob/master/README-Cube.md) for installation.

- Deply and validate

    1. Open the MDK5-Keil platform to compile project. Open the MDK5 Generated project. 

    2. Set default compiler version to 6 using the **Options for target..**. Check the **Use MicroLIB** option in modal window. 

    3. Build project. If error appears, add '*include <stdio.h>*' header to **project-folder\src\main.c**

    4. Connect the STM Nucleo 32 board and load the built code.

    5. Run validation.py from [demo](https://github.com/tinymlcontest/tinyml_contest2022_demo_evaluation).
        ```bash
        python validation.py --com * --baudrate * --path_data *
        ```

