/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Dec  5 18:27:20 2022
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "8128ba8c9e9a7cfdde182ab262568034"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon Dec  5 18:27:20 2022"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_1_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1250, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  node_38_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1246, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  node_40_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1246, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  node_41_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 930, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  node_43_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 930, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  node_44_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 770, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  node_46_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 770, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  node_47_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 760, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  node_49_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 760, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  node_50_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 370, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  node_52_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 370, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  node_54_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 370, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  node_55_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 2, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  node_38_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  node_38_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  node_40_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  node_40_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  node_41_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 30, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  node_41_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  node_43_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  node_43_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)
/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  node_44_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 60, AI_STATIC)
/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  node_44_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5, AI_STATIC)
/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  node_46_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5, AI_STATIC)
/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  node_46_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5, AI_STATIC)
/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  node_47_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 200, AI_STATIC)
/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  node_47_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  node_49_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  node_49_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  node_50_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 400, AI_STATIC)
/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  node_50_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  node_52_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  node_52_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  node_55_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 740, AI_STATIC)
/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  node_55_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  input_1_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1250), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &input_1_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  node_38_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 623), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_38_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  node_40_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 623), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_40_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  node_41_output, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 310), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &node_41_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  node_43_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 310), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &node_43_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  node_44_output, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 154), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &node_44_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  node_46_output, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 154), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &node_46_output_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  node_47_output, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 76), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_47_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  node_49_output, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 76), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_49_output_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  node_50_output, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 37), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_50_output_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  node_52_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 37), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_52_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  node_54_to_chlast_output, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 37, 10), AI_STRIDE_INIT(4, 4, 4, 4, 148),
  1, &node_54_to_chlast_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  node_54_to_chlast_output0, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 370, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1480, 1480),
  1, &node_54_to_chlast_output_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  node_55_output, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_55_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  node_38_weights, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 6, 2), AI_STRIDE_INIT(4, 4, 4, 4, 24),
  1, &node_38_weights_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  node_38_bias, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_38_bias_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  node_40_scale, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_40_scale_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  node_40_bias, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_40_bias_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  node_41_weights, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 2, 1, 5, 3), AI_STRIDE_INIT(4, 4, 8, 8, 40),
  1, &node_41_weights_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  node_41_bias, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &node_41_bias_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  node_43_scale, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &node_43_scale_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  node_43_bias, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &node_43_bias_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  node_44_weights, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 3, 1, 4, 5), AI_STRIDE_INIT(4, 4, 12, 12, 48),
  1, &node_44_weights_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  node_44_bias, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &node_44_bias_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  node_46_scale, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &node_46_scale_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  node_46_bias, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &node_46_bias_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  node_47_weights, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 5, 1, 4, 10), AI_STRIDE_INIT(4, 4, 20, 20, 80),
  1, &node_47_weights_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  node_47_bias, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_47_bias_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  node_49_scale, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_49_scale_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  node_49_bias, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_49_bias_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  node_50_weights, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 10, 1, 4, 10), AI_STRIDE_INIT(4, 4, 40, 40, 160),
  1, &node_50_weights_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  node_50_bias, AI_STATIC,
  31, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_50_bias_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  node_52_scale, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_52_scale_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  node_52_bias, AI_STATIC,
  33, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &node_52_bias_array, NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  node_55_weights, AI_STATIC,
  34, 0x0,
  AI_SHAPE_INIT(4, 370, 2, 1, 1), AI_STRIDE_INIT(4, 4, 1480, 2960, 2960),
  1, &node_55_weights_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  node_55_bias, AI_STATIC,
  35, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_55_bias_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_55_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_54_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_55_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &node_55_weights, &node_55_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_55_layer, 17,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &node_55_chain,
  NULL, &node_55_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_54_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_52_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_54_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_54_to_chlast_layer, 16,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &node_54_to_chlast_chain,
  NULL, &node_55_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_52_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_50_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_52_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &node_52_scale, &node_52_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_52_layer, 15,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &node_52_chain,
  NULL, &node_54_to_chlast_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_50_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_49_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_50_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_50_weights, &node_50_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_50_layer, 14,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &node_50_chain,
  NULL, &node_52_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_49_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_47_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_49_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &node_49_scale, &node_49_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_49_layer, 12,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &node_49_chain,
  NULL, &node_50_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_47_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_46_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_47_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_47_weights, &node_47_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_47_layer, 11,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &node_47_chain,
  NULL, &node_49_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_46_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_44_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_46_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &node_46_scale, &node_46_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_46_layer, 9,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &node_46_chain,
  NULL, &node_47_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_44_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_43_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_44_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_44_weights, &node_44_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_44_layer, 8,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &node_44_chain,
  NULL, &node_46_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_43_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_41_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_43_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &node_43_scale, &node_43_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_43_layer, 6,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &node_43_chain,
  NULL, &node_44_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_41_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_40_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_41_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_41_weights, &node_41_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_41_layer, 5,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &node_41_chain,
  NULL, &node_43_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_40_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_38_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_40_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &node_40_scale, &node_40_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_40_layer, 3,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &node_40_chain,
  NULL, &node_41_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_38_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &node_38_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &node_38_weights, &node_38_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_38_layer, 2,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &node_38_chain,
  NULL, &node_40_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = NULL, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 6136, 1, 1),
    6136, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 5116, 1, 1),
    5116, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_1_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &node_55_output),
  &node_38_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 6136, 1, 1),
      6136, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 5116, 1, 1),
      5116, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_1_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &node_55_output),
  &node_38_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_1_output_array.data = AI_PTR(g_network_activations_map[0] + 116);
    input_1_output_array.data_start = AI_PTR(g_network_activations_map[0] + 116);
    
    node_38_output_array.data = AI_PTR(g_network_activations_map[0] + 104);
    node_38_output_array.data_start = AI_PTR(g_network_activations_map[0] + 104);
    
    node_40_output_array.data = AI_PTR(g_network_activations_map[0] + 104);
    node_40_output_array.data_start = AI_PTR(g_network_activations_map[0] + 104);
    
    node_41_output_array.data = AI_PTR(g_network_activations_map[0] + 88);
    node_41_output_array.data_start = AI_PTR(g_network_activations_map[0] + 88);
    
    node_43_output_array.data = AI_PTR(g_network_activations_map[0] + 88);
    node_43_output_array.data_start = AI_PTR(g_network_activations_map[0] + 88);
    
    node_44_output_array.data = AI_PTR(g_network_activations_map[0] + 60);
    node_44_output_array.data_start = AI_PTR(g_network_activations_map[0] + 60);
    
    node_46_output_array.data = AI_PTR(g_network_activations_map[0] + 60);
    node_46_output_array.data_start = AI_PTR(g_network_activations_map[0] + 60);
    
    node_47_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    node_47_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    node_49_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    node_49_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    node_50_output_array.data = AI_PTR(g_network_activations_map[0] + 3040);
    node_50_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3040);
    
    node_52_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    node_52_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    node_54_to_chlast_output_array.data = AI_PTR(g_network_activations_map[0] + 1480);
    node_54_to_chlast_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1480);
    
    node_55_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    node_55_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    node_38_weights_array.format |= AI_FMT_FLAG_CONST;
    node_38_weights_array.data = AI_PTR(g_network_weights_map[0] + 0);
    node_38_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    
    node_38_bias_array.format |= AI_FMT_FLAG_CONST;
    node_38_bias_array.data = AI_PTR(g_network_weights_map[0] + 48);
    node_38_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 48);
    
    node_40_scale_array.format |= AI_FMT_FLAG_CONST;
    node_40_scale_array.data = AI_PTR(g_network_weights_map[0] + 56);
    node_40_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 56);
    
    node_40_bias_array.format |= AI_FMT_FLAG_CONST;
    node_40_bias_array.data = AI_PTR(g_network_weights_map[0] + 64);
    node_40_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 64);
    
    node_41_weights_array.format |= AI_FMT_FLAG_CONST;
    node_41_weights_array.data = AI_PTR(g_network_weights_map[0] + 72);
    node_41_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 72);
    
    node_41_bias_array.format |= AI_FMT_FLAG_CONST;
    node_41_bias_array.data = AI_PTR(g_network_weights_map[0] + 192);
    node_41_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 192);
    
    node_43_scale_array.format |= AI_FMT_FLAG_CONST;
    node_43_scale_array.data = AI_PTR(g_network_weights_map[0] + 204);
    node_43_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 204);
    
    node_43_bias_array.format |= AI_FMT_FLAG_CONST;
    node_43_bias_array.data = AI_PTR(g_network_weights_map[0] + 216);
    node_43_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 216);
    
    node_44_weights_array.format |= AI_FMT_FLAG_CONST;
    node_44_weights_array.data = AI_PTR(g_network_weights_map[0] + 228);
    node_44_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 228);
    
    node_44_bias_array.format |= AI_FMT_FLAG_CONST;
    node_44_bias_array.data = AI_PTR(g_network_weights_map[0] + 468);
    node_44_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 468);
    
    node_46_scale_array.format |= AI_FMT_FLAG_CONST;
    node_46_scale_array.data = AI_PTR(g_network_weights_map[0] + 488);
    node_46_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 488);
    
    node_46_bias_array.format |= AI_FMT_FLAG_CONST;
    node_46_bias_array.data = AI_PTR(g_network_weights_map[0] + 508);
    node_46_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 508);
    
    node_47_weights_array.format |= AI_FMT_FLAG_CONST;
    node_47_weights_array.data = AI_PTR(g_network_weights_map[0] + 528);
    node_47_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 528);
    
    node_47_bias_array.format |= AI_FMT_FLAG_CONST;
    node_47_bias_array.data = AI_PTR(g_network_weights_map[0] + 1328);
    node_47_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 1328);
    
    node_49_scale_array.format |= AI_FMT_FLAG_CONST;
    node_49_scale_array.data = AI_PTR(g_network_weights_map[0] + 1368);
    node_49_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 1368);
    
    node_49_bias_array.format |= AI_FMT_FLAG_CONST;
    node_49_bias_array.data = AI_PTR(g_network_weights_map[0] + 1408);
    node_49_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 1408);
    
    node_50_weights_array.format |= AI_FMT_FLAG_CONST;
    node_50_weights_array.data = AI_PTR(g_network_weights_map[0] + 1448);
    node_50_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1448);
    
    node_50_bias_array.format |= AI_FMT_FLAG_CONST;
    node_50_bias_array.data = AI_PTR(g_network_weights_map[0] + 3048);
    node_50_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 3048);
    
    node_52_scale_array.format |= AI_FMT_FLAG_CONST;
    node_52_scale_array.data = AI_PTR(g_network_weights_map[0] + 3088);
    node_52_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 3088);
    
    node_52_bias_array.format |= AI_FMT_FLAG_CONST;
    node_52_bias_array.data = AI_PTR(g_network_weights_map[0] + 3128);
    node_52_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 3128);
    
    node_55_weights_array.format |= AI_FMT_FLAG_CONST;
    node_55_weights_array.data = AI_PTR(g_network_weights_map[0] + 3168);
    node_55_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3168);
    
    node_55_bias_array.format |= AI_FMT_FLAG_CONST;
    node_55_bias_array.data = AI_PTR(g_network_weights_map[0] + 6128);
    node_55_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 6128);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 69016,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 69016,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_network_data_params_get(&params) != true) {
        err = ai_network_get_error(*network);
        return err;
    }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_network_init(*network, &params) != true) {
        err = ai_network_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

