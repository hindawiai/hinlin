<शैली गुरु>
/*
 * Copyright (c) 1993-2014, NVIDIA CORPORATION. All rights reserved.
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


#अगर_अघोषित _cl907c_h_
#घोषणा _cl907c_h_

// class methods
#घोषणा NV907C_SET_PRESENT_CONTROL                                              (0x00000084)
#घोषणा NV907C_SET_PRESENT_CONTROL_BEGIN_MODE                                   9:8
#घोषणा NV907C_SET_PRESENT_CONTROL_BEGIN_MODE_NON_TEARING                       (0x00000000)
#घोषणा NV907C_SET_PRESENT_CONTROL_BEGIN_MODE_IMMEDIATE                         (0x00000001)
#घोषणा NV907C_SET_PRESENT_CONTROL_BEGIN_MODE_ON_LINE                           (0x00000002)
#घोषणा NV907C_SET_PRESENT_CONTROL_BEGIN_MODE_AT_FRAME                          (0x00000003)
#घोषणा NV907C_SET_PRESENT_CONTROL_TIMESTAMP_MODE                               2:2
#घोषणा NV907C_SET_PRESENT_CONTROL_TIMESTAMP_MODE_DISABLE                       (0x00000000)
#घोषणा NV907C_SET_PRESENT_CONTROL_TIMESTAMP_MODE_ENABLE                        (0x00000001)
#घोषणा NV907C_SET_PRESENT_CONTROL_MIN_PRESENT_INTERVAL                         7:4
#घोषणा NV907C_SET_PRESENT_CONTROL_BEGIN_LINE                                   30:16
#घोषणा NV907C_SET_PRESENT_CONTROL_ON_LINE_MARGIN                               15:10
#घोषणा NV907C_SET_CONTEXT_DMAS_ISO(b)                                          (0x000000C0 + (b)*0x00000004)
#घोषणा NV907C_SET_CONTEXT_DMAS_ISO_HANDLE                                      31:0
#घोषणा NV907C_SET_BASE_LUT_LO                                                  (0x000000E0)
#घोषणा NV907C_SET_BASE_LUT_LO_ENABLE                                           31:30
#घोषणा NV907C_SET_BASE_LUT_LO_ENABLE_DISABLE                                   (0x00000000)
#घोषणा NV907C_SET_BASE_LUT_LO_ENABLE_USE_CORE_LUT                              (0x00000001)
#घोषणा NV907C_SET_BASE_LUT_LO_ENABLE_ENABLE                                    (0x00000002)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE                                             27:24
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_LORES                                       (0x00000000)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_HIRES                                       (0x00000001)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_INDEX_1025_UNITY_RANGE                      (0x00000003)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_INTERPOLATE_1025_UNITY_RANGE                (0x00000004)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_INTERPOLATE_1025_XRBIAS_RANGE               (0x00000005)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_INTERPOLATE_1025_XVYCC_RANGE                (0x00000006)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_INTERPOLATE_257_UNITY_RANGE                 (0x00000007)
#घोषणा NV907C_SET_BASE_LUT_LO_MODE_INTERPOLATE_257_LEGACY_RANGE                (0x00000008)
#घोषणा NV907C_SET_BASE_LUT_HI                                                  (0x000000E4)
#घोषणा NV907C_SET_BASE_LUT_HI_ORIGIN                                           31:0
#घोषणा NV907C_SET_OUTPUT_LUT_LO                                                (0x000000E8)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_ENABLE                                         31:30
#घोषणा NV907C_SET_OUTPUT_LUT_LO_ENABLE_DISABLE                                 (0x00000000)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_ENABLE_USE_CORE_LUT                            (0x00000001)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_ENABLE_ENABLE                                  (0x00000002)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE                                           27:24
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_LORES                                     (0x00000000)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_HIRES                                     (0x00000001)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_INDEX_1025_UNITY_RANGE                    (0x00000003)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_INTERPOLATE_1025_UNITY_RANGE              (0x00000004)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_INTERPOLATE_1025_XRBIAS_RANGE             (0x00000005)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_INTERPOLATE_1025_XVYCC_RANGE              (0x00000006)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_INTERPOLATE_257_UNITY_RANGE               (0x00000007)
#घोषणा NV907C_SET_OUTPUT_LUT_LO_MODE_INTERPOLATE_257_LEGACY_RANGE              (0x00000008)
#घोषणा NV907C_SET_CONTEXT_DMA_LUT                                              (0x000000FC)
#घोषणा NV907C_SET_CONTEXT_DMA_LUT_HANDLE                                       31:0
#घोषणा NV907C_SET_CSC_RED2RED                                                  (0x00000140)
#घोषणा NV907C_SET_CSC_RED2RED_OWNER                                            31:31
#घोषणा NV907C_SET_CSC_RED2RED_OWNER_CORE                                       (0x00000000)
#घोषणा NV907C_SET_CSC_RED2RED_OWNER_BASE                                       (0x00000001)
#घोषणा NV907C_SET_CSC_RED2RED_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_GRN2RED                                                  (0x00000144)
#घोषणा NV907C_SET_CSC_GRN2RED_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_BLU2RED                                                  (0x00000148)
#घोषणा NV907C_SET_CSC_BLU2RED_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_CONSTANT2RED                                             (0x0000014C)
#घोषणा NV907C_SET_CSC_CONSTANT2RED_COEFF                                       18:0
#घोषणा NV907C_SET_CSC_RED2GRN                                                  (0x00000150)
#घोषणा NV907C_SET_CSC_RED2GRN_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_GRN2GRN                                                  (0x00000154)
#घोषणा NV907C_SET_CSC_GRN2GRN_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_BLU2GRN                                                  (0x00000158)
#घोषणा NV907C_SET_CSC_BLU2GRN_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_CONSTANT2GRN                                             (0x0000015C)
#घोषणा NV907C_SET_CSC_CONSTANT2GRN_COEFF                                       18:0
#घोषणा NV907C_SET_CSC_RED2BLU                                                  (0x00000160)
#घोषणा NV907C_SET_CSC_RED2BLU_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_GRN2BLU                                                  (0x00000164)
#घोषणा NV907C_SET_CSC_GRN2BLU_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_BLU2BLU                                                  (0x00000168)
#घोषणा NV907C_SET_CSC_BLU2BLU_COEFF                                            18:0
#घोषणा NV907C_SET_CSC_CONSTANT2BLU                                             (0x0000016C)
#घोषणा NV907C_SET_CSC_CONSTANT2BLU_COEFF                                       18:0

#घोषणा NV907C_SURFACE_SET_OFFSET(a,b)                                          (0x00000400 + (a)*0x00000020 + (b)*0x00000004)
#घोषणा NV907C_SURFACE_SET_OFFSET_ORIGIN                                        31:0
#घोषणा NV907C_SURFACE_SET_SIZE(a)                                              (0x00000408 + (a)*0x00000020)
#घोषणा NV907C_SURFACE_SET_SIZE_WIDTH                                           15:0
#घोषणा NV907C_SURFACE_SET_SIZE_HEIGHT                                          31:16
#घोषणा NV907C_SURFACE_SET_STORAGE(a)                                           (0x0000040C + (a)*0x00000020)
#घोषणा NV907C_SURFACE_SET_STORAGE_BLOCK_HEIGHT                                 3:0
#घोषणा NV907C_SURFACE_SET_STORAGE_BLOCK_HEIGHT_ONE_GOB                         (0x00000000)
#घोषणा NV907C_SURFACE_SET_STORAGE_BLOCK_HEIGHT_TWO_GOBS                        (0x00000001)
#घोषणा NV907C_SURFACE_SET_STORAGE_BLOCK_HEIGHT_FOUR_GOBS                       (0x00000002)
#घोषणा NV907C_SURFACE_SET_STORAGE_BLOCK_HEIGHT_EIGHT_GOBS                      (0x00000003)
#घोषणा NV907C_SURFACE_SET_STORAGE_BLOCK_HEIGHT_SIXTEEN_GOBS                    (0x00000004)
#घोषणा NV907C_SURFACE_SET_STORAGE_BLOCK_HEIGHT_THIRTYTWO_GOBS                  (0x00000005)
#घोषणा NV907C_SURFACE_SET_STORAGE_PITCH                                        20:8
#घोषणा NV907C_SURFACE_SET_STORAGE_MEMORY_LAYOUT                                24:24
#घोषणा NV907C_SURFACE_SET_STORAGE_MEMORY_LAYOUT_BLOCKLINEAR                    (0x00000000)
#घोषणा NV907C_SURFACE_SET_STORAGE_MEMORY_LAYOUT_PITCH                          (0x00000001)
#घोषणा NV907C_SURFACE_SET_PARAMS(a)                                            (0x00000410 + (a)*0x00000020)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT                                        15:8
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_I8                                     (0x0000001E)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_VOID16                                 (0x0000001F)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_VOID32                                 (0x0000002E)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_RF16_GF16_BF16_AF16                    (0x000000CA)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_A8R8G8B8                               (0x000000CF)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_A2B10G10R10                            (0x000000D1)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_X2BL10GL10RL10_XRBIAS                  (0x00000022)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_A8B8G8R8                               (0x000000D5)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_R5G6B5                                 (0x000000E8)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_A1R5G5B5                               (0x000000E9)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_R16_G16_B16_A16                        (0x000000C6)
#घोषणा NV907C_SURFACE_SET_PARAMS_FORMAT_R16_G16_B16_A16_NVBIAS                 (0x00000023)
#घोषणा NV907C_SURFACE_SET_PARAMS_SUPER_SAMPLE                                  1:0
#घोषणा NV907C_SURFACE_SET_PARAMS_SUPER_SAMPLE_X1_AA                            (0x00000000)
#घोषणा NV907C_SURFACE_SET_PARAMS_SUPER_SAMPLE_X4_AA                            (0x00000002)
#घोषणा NV907C_SURFACE_SET_PARAMS_GAMMA                                         2:2
#घोषणा NV907C_SURFACE_SET_PARAMS_GAMMA_LINEAR                                  (0x00000000)
#घोषणा NV907C_SURFACE_SET_PARAMS_GAMMA_SRGB                                    (0x00000001)
#घोषणा NV907C_SURFACE_SET_PARAMS_LAYOUT                                        5:4
#घोषणा NV907C_SURFACE_SET_PARAMS_LAYOUT_FRM                                    (0x00000000)
#घोषणा NV907C_SURFACE_SET_PARAMS_LAYOUT_FLD1                                   (0x00000001)
#घोषणा NV907C_SURFACE_SET_PARAMS_LAYOUT_FLD2                                   (0x00000002)
#पूर्ण_अगर // _cl907c_h
