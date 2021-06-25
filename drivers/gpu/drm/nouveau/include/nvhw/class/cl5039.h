<शैली गुरु>
/*
 * Copyright (c) 2003-2004, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _cl_nv50_memory_to_memory_क्रमmat_h_
#घोषणा _cl_nv50_memory_to_memory_क्रमmat_h_

#घोषणा NV5039_SET_OBJECT                                                                                  0x0000
#घोषणा NV5039_SET_OBJECT_POINTER                                                                            15:0

#घोषणा NV5039_NO_OPERATION                                                                                0x0100
#घोषणा NV5039_NO_OPERATION_V                                                                                31:0

#घोषणा NV5039_SET_CONTEXT_DMA_NOTIFY                                                                      0x0180
#घोषणा NV5039_SET_CONTEXT_DMA_NOTIFY_HANDLE                                                                 31:0

#घोषणा NV5039_SET_CONTEXT_DMA_BUFFER_IN                                                                   0x0184
#घोषणा NV5039_SET_CONTEXT_DMA_BUFFER_IN_HANDLE                                                              31:0

#घोषणा NV5039_SET_CONTEXT_DMA_BUFFER_OUT                                                                  0x0188
#घोषणा NV5039_SET_CONTEXT_DMA_BUFFER_OUT_HANDLE                                                             31:0

#घोषणा NV5039_SET_SRC_MEMORY_LAYOUT                                                                       0x0200
#घोषणा NV5039_SET_SRC_MEMORY_LAYOUT_V                                                                        0:0
#घोषणा NV5039_SET_SRC_MEMORY_LAYOUT_V_BLOCKLINEAR                                                     0x00000000
#घोषणा NV5039_SET_SRC_MEMORY_LAYOUT_V_PITCH                                                           0x00000001

#घोषणा NV5039_SET_SRC_BLOCK_SIZE                                                                          0x0204
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_WIDTH                                                                       3:0
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_WIDTH_ONE_GOB                                                        0x00000000
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_HEIGHT                                                                      7:4
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_HEIGHT_ONE_GOB                                                       0x00000000
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_HEIGHT_TWO_GOBS                                                      0x00000001
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_HEIGHT_FOUR_GOBS                                                     0x00000002
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_HEIGHT_EIGHT_GOBS                                                    0x00000003
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_HEIGHT_SIXTEEN_GOBS                                                  0x00000004
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_HEIGHT_THIRTYTWO_GOBS                                                0x00000005
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_DEPTH                                                                      11:8
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_DEPTH_ONE_GOB                                                        0x00000000
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_DEPTH_TWO_GOBS                                                       0x00000001
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_DEPTH_FOUR_GOBS                                                      0x00000002
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_DEPTH_EIGHT_GOBS                                                     0x00000003
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_DEPTH_SIXTEEN_GOBS                                                   0x00000004
#घोषणा NV5039_SET_SRC_BLOCK_SIZE_DEPTH_THIRTYTWO_GOBS                                                 0x00000005

#घोषणा NV5039_SET_SRC_WIDTH                                                                               0x0208
#घोषणा NV5039_SET_SRC_WIDTH_V                                                                               31:0

#घोषणा NV5039_SET_SRC_HEIGHT                                                                              0x020c
#घोषणा NV5039_SET_SRC_HEIGHT_V                                                                              31:0

#घोषणा NV5039_SET_SRC_DEPTH                                                                               0x0210
#घोषणा NV5039_SET_SRC_DEPTH_V                                                                               31:0

#घोषणा NV5039_SET_SRC_LAYER                                                                               0x0214
#घोषणा NV5039_SET_SRC_LAYER_V                                                                               31:0

#घोषणा NV5039_SET_SRC_ORIGIN                                                                              0x0218
#घोषणा NV5039_SET_SRC_ORIGIN_X                                                                              15:0
#घोषणा NV5039_SET_SRC_ORIGIN_Y                                                                             31:16

#घोषणा NV5039_SET_DST_MEMORY_LAYOUT                                                                       0x021c
#घोषणा NV5039_SET_DST_MEMORY_LAYOUT_V                                                                        0:0
#घोषणा NV5039_SET_DST_MEMORY_LAYOUT_V_BLOCKLINEAR                                                     0x00000000
#घोषणा NV5039_SET_DST_MEMORY_LAYOUT_V_PITCH                                                           0x00000001

#घोषणा NV5039_SET_DST_BLOCK_SIZE                                                                          0x0220
#घोषणा NV5039_SET_DST_BLOCK_SIZE_WIDTH                                                                       3:0
#घोषणा NV5039_SET_DST_BLOCK_SIZE_WIDTH_ONE_GOB                                                        0x00000000
#घोषणा NV5039_SET_DST_BLOCK_SIZE_HEIGHT                                                                      7:4
#घोषणा NV5039_SET_DST_BLOCK_SIZE_HEIGHT_ONE_GOB                                                       0x00000000
#घोषणा NV5039_SET_DST_BLOCK_SIZE_HEIGHT_TWO_GOBS                                                      0x00000001
#घोषणा NV5039_SET_DST_BLOCK_SIZE_HEIGHT_FOUR_GOBS                                                     0x00000002
#घोषणा NV5039_SET_DST_BLOCK_SIZE_HEIGHT_EIGHT_GOBS                                                    0x00000003
#घोषणा NV5039_SET_DST_BLOCK_SIZE_HEIGHT_SIXTEEN_GOBS                                                  0x00000004
#घोषणा NV5039_SET_DST_BLOCK_SIZE_HEIGHT_THIRTYTWO_GOBS                                                0x00000005
#घोषणा NV5039_SET_DST_BLOCK_SIZE_DEPTH                                                                      11:8
#घोषणा NV5039_SET_DST_BLOCK_SIZE_DEPTH_ONE_GOB                                                        0x00000000
#घोषणा NV5039_SET_DST_BLOCK_SIZE_DEPTH_TWO_GOBS                                                       0x00000001
#घोषणा NV5039_SET_DST_BLOCK_SIZE_DEPTH_FOUR_GOBS                                                      0x00000002
#घोषणा NV5039_SET_DST_BLOCK_SIZE_DEPTH_EIGHT_GOBS                                                     0x00000003
#घोषणा NV5039_SET_DST_BLOCK_SIZE_DEPTH_SIXTEEN_GOBS                                                   0x00000004
#घोषणा NV5039_SET_DST_BLOCK_SIZE_DEPTH_THIRTYTWO_GOBS                                                 0x00000005

#घोषणा NV5039_SET_DST_WIDTH                                                                               0x0224
#घोषणा NV5039_SET_DST_WIDTH_V                                                                               31:0

#घोषणा NV5039_SET_DST_HEIGHT                                                                              0x0228
#घोषणा NV5039_SET_DST_HEIGHT_V                                                                              31:0

#घोषणा NV5039_SET_DST_DEPTH                                                                               0x022c
#घोषणा NV5039_SET_DST_DEPTH_V                                                                               31:0

#घोषणा NV5039_SET_DST_LAYER                                                                               0x0230
#घोषणा NV5039_SET_DST_LAYER_V                                                                               31:0

#घोषणा NV5039_SET_DST_ORIGIN                                                                              0x0234
#घोषणा NV5039_SET_DST_ORIGIN_X                                                                              15:0
#घोषणा NV5039_SET_DST_ORIGIN_Y                                                                             31:16

#घोषणा NV5039_OFFSET_IN_UPPER                                                                             0x0238
#घोषणा NV5039_OFFSET_IN_UPPER_VALUE                                                                          7:0

#घोषणा NV5039_OFFSET_OUT_UPPER                                                                            0x023c
#घोषणा NV5039_OFFSET_OUT_UPPER_VALUE                                                                         7:0

#घोषणा NV5039_OFFSET_IN                                                                                   0x030c
#घोषणा NV5039_OFFSET_IN_VALUE                                                                               31:0

#घोषणा NV5039_OFFSET_OUT                                                                                  0x0310
#घोषणा NV5039_OFFSET_OUT_VALUE                                                                              31:0

#घोषणा NV5039_PITCH_IN                                                                                    0x0314
#घोषणा NV5039_PITCH_IN_VALUE                                                                                31:0

#घोषणा NV5039_PITCH_OUT                                                                                   0x0318
#घोषणा NV5039_PITCH_OUT_VALUE                                                                               31:0

#घोषणा NV5039_LINE_LENGTH_IN                                                                              0x031c
#घोषणा NV5039_LINE_LENGTH_IN_VALUE                                                                          31:0

#घोषणा NV5039_LINE_COUNT                                                                                  0x0320
#घोषणा NV5039_LINE_COUNT_VALUE                                                                              31:0

#घोषणा NV5039_FORMAT                                                                                      0x0324
#घोषणा NV5039_FORMAT_IN                                                                                      7:0
#घोषणा NV5039_FORMAT_IN_ONE                                                                           0x00000001
#घोषणा NV5039_FORMAT_OUT                                                                                    15:8
#घोषणा NV5039_FORMAT_OUT_ONE                                                                          0x00000001

#घोषणा NV5039_BUFFER_NOTIFY                                                                               0x0328
#घोषणा NV5039_BUFFER_NOTIFY_TYPE                                                                            31:0
#घोषणा NV5039_BUFFER_NOTIFY_TYPE_WRITE_ONLY                                                           0x00000000
#घोषणा NV5039_BUFFER_NOTIFY_TYPE_WRITE_THEN_AWAKEN                                                    0x00000001
#पूर्ण_अगर /* _cl_nv50_memory_to_memory_क्रमmat_h_ */
