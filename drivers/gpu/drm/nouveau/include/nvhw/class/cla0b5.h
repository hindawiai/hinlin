<शैली गुरु>
/*******************************************************************************
    Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.

    Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
    copy of this software and associated करोcumentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to करो so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#अगर_अघोषित _cla0b5_h_
#घोषणा _cla0b5_h_

#घोषणा NVA0B5_SET_SRC_PHYS_MODE                                                (0x00000260)
#घोषणा NVA0B5_SET_SRC_PHYS_MODE_TARGET                                         1:0
#घोषणा NVA0B5_SET_SRC_PHYS_MODE_TARGET_LOCAL_FB                                (0x00000000)
#घोषणा NVA0B5_SET_SRC_PHYS_MODE_TARGET_COHERENT_SYSMEM                         (0x00000001)
#घोषणा NVA0B5_SET_SRC_PHYS_MODE_TARGET_NONCOHERENT_SYSMEM                      (0x00000002)
#घोषणा NVA0B5_SET_DST_PHYS_MODE                                                (0x00000264)
#घोषणा NVA0B5_SET_DST_PHYS_MODE_TARGET                                         1:0
#घोषणा NVA0B5_SET_DST_PHYS_MODE_TARGET_LOCAL_FB                                (0x00000000)
#घोषणा NVA0B5_SET_DST_PHYS_MODE_TARGET_COHERENT_SYSMEM                         (0x00000001)
#घोषणा NVA0B5_SET_DST_PHYS_MODE_TARGET_NONCOHERENT_SYSMEM                      (0x00000002)
#घोषणा NVA0B5_LAUNCH_DMA                                                       (0x00000300)
#घोषणा NVA0B5_LAUNCH_DMA_DATA_TRANSFER_TYPE                                    1:0
#घोषणा NVA0B5_LAUNCH_DMA_DATA_TRANSFER_TYPE_NONE                               (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_DATA_TRANSFER_TYPE_PIPELINED                          (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_DATA_TRANSFER_TYPE_NON_PIPELINED                      (0x00000002)
#घोषणा NVA0B5_LAUNCH_DMA_FLUSH_ENABLE                                          2:2
#घोषणा NVA0B5_LAUNCH_DMA_FLUSH_ENABLE_FALSE                                    (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_FLUSH_ENABLE_TRUE                                     (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_TYPE                                        4:3
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_TYPE_NONE                                   (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_TYPE_RELEASE_ONE_WORD_SEMAPHORE             (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_TYPE_RELEASE_FOUR_WORD_SEMAPHORE            (0x00000002)
#घोषणा NVA0B5_LAUNCH_DMA_INTERRUPT_TYPE                                        6:5
#घोषणा NVA0B5_LAUNCH_DMA_INTERRUPT_TYPE_NONE                                   (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_INTERRUPT_TYPE_BLOCKING                               (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_INTERRUPT_TYPE_NON_BLOCKING                           (0x00000002)
#घोषणा NVA0B5_LAUNCH_DMA_SRC_MEMORY_LAYOUT                                     7:7
#घोषणा NVA0B5_LAUNCH_DMA_SRC_MEMORY_LAYOUT_BLOCKLINEAR                         (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_SRC_MEMORY_LAYOUT_PITCH                               (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_DST_MEMORY_LAYOUT                                     8:8
#घोषणा NVA0B5_LAUNCH_DMA_DST_MEMORY_LAYOUT_BLOCKLINEAR                         (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_DST_MEMORY_LAYOUT_PITCH                               (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_MULTI_LINE_ENABLE                                     9:9
#घोषणा NVA0B5_LAUNCH_DMA_MULTI_LINE_ENABLE_FALSE                               (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_MULTI_LINE_ENABLE_TRUE                                (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_REMAP_ENABLE                                          10:10
#घोषणा NVA0B5_LAUNCH_DMA_REMAP_ENABLE_FALSE                                    (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_REMAP_ENABLE_TRUE                                     (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_BYPASS_L2                                             11:11
#घोषणा NVA0B5_LAUNCH_DMA_BYPASS_L2_USE_PTE_SETTING                             (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_BYPASS_L2_FORCE_VOLATILE                              (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_SRC_TYPE                                              12:12
#घोषणा NVA0B5_LAUNCH_DMA_SRC_TYPE_VIRTUAL                                      (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_SRC_TYPE_PHYSICAL                                     (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_DST_TYPE                                              13:13
#घोषणा NVA0B5_LAUNCH_DMA_DST_TYPE_VIRTUAL                                      (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_DST_TYPE_PHYSICAL                                     (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION                                   17:14
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_IMIN                              (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_IMAX                              (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_IXOR                              (0x00000002)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_IAND                              (0x00000003)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_IOR                               (0x00000004)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_IADD                              (0x00000005)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_INC                               (0x00000006)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_DEC                               (0x00000007)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_FADD                              (0x0000000A)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_FMIN                              (0x0000000B)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_FMAX                              (0x0000000C)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_FMUL                              (0x0000000D)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_IMUL                              (0x0000000E)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_SIGN                              18:18
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_SIGN_SIGNED                       (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_SIGN_UNSIGNED                     (0x00000001)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_ENABLE                            19:19
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_ENABLE_FALSE                      (0x00000000)
#घोषणा NVA0B5_LAUNCH_DMA_SEMAPHORE_REDUCTION_ENABLE_TRUE                       (0x00000001)
#घोषणा NVA0B5_OFFSET_IN_UPPER                                                  (0x00000400)
#घोषणा NVA0B5_OFFSET_IN_UPPER_UPPER                                            7:0
#घोषणा NVA0B5_OFFSET_IN_LOWER                                                  (0x00000404)
#घोषणा NVA0B5_OFFSET_IN_LOWER_VALUE                                            31:0
#घोषणा NVA0B5_OFFSET_OUT_UPPER                                                 (0x00000408)
#घोषणा NVA0B5_OFFSET_OUT_UPPER_UPPER                                           7:0
#घोषणा NVA0B5_OFFSET_OUT_LOWER                                                 (0x0000040C)
#घोषणा NVA0B5_OFFSET_OUT_LOWER_VALUE                                           31:0
#घोषणा NVA0B5_PITCH_IN                                                         (0x00000410)
#घोषणा NVA0B5_PITCH_IN_VALUE                                                   31:0
#घोषणा NVA0B5_PITCH_OUT                                                        (0x00000414)
#घोषणा NVA0B5_PITCH_OUT_VALUE                                                  31:0
#घोषणा NVA0B5_LINE_LENGTH_IN                                                   (0x00000418)
#घोषणा NVA0B5_LINE_LENGTH_IN_VALUE                                             31:0
#घोषणा NVA0B5_LINE_COUNT                                                       (0x0000041C)
#घोषणा NVA0B5_LINE_COUNT_VALUE                                                 31:0
#घोषणा NVA0B5_SET_REMAP_CONST_A                                                (0x00000700)
#घोषणा NVA0B5_SET_REMAP_CONST_A_V                                              31:0
#घोषणा NVA0B5_SET_REMAP_CONST_B                                                (0x00000704)
#घोषणा NVA0B5_SET_REMAP_CONST_B_V                                              31:0
#घोषणा NVA0B5_SET_REMAP_COMPONENTS                                             (0x00000708)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X                                       2:0
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X_SRC_X                                 (0x00000000)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X_SRC_Y                                 (0x00000001)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X_SRC_Z                                 (0x00000002)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X_SRC_W                                 (0x00000003)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X_CONST_A                               (0x00000004)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X_CONST_B                               (0x00000005)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_X_NO_WRITE                              (0x00000006)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y                                       6:4
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y_SRC_X                                 (0x00000000)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y_SRC_Y                                 (0x00000001)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y_SRC_Z                                 (0x00000002)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y_SRC_W                                 (0x00000003)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y_CONST_A                               (0x00000004)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y_CONST_B                               (0x00000005)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Y_NO_WRITE                              (0x00000006)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z                                       10:8
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z_SRC_X                                 (0x00000000)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z_SRC_Y                                 (0x00000001)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z_SRC_Z                                 (0x00000002)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z_SRC_W                                 (0x00000003)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z_CONST_A                               (0x00000004)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z_CONST_B                               (0x00000005)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_Z_NO_WRITE                              (0x00000006)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W                                       14:12
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W_SRC_X                                 (0x00000000)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W_SRC_Y                                 (0x00000001)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W_SRC_Z                                 (0x00000002)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W_SRC_W                                 (0x00000003)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W_CONST_A                               (0x00000004)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W_CONST_B                               (0x00000005)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_DST_W_NO_WRITE                              (0x00000006)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_COMPONENT_SIZE                              17:16
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_COMPONENT_SIZE_ONE                          (0x00000000)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_COMPONENT_SIZE_TWO                          (0x00000001)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_COMPONENT_SIZE_THREE                        (0x00000002)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_COMPONENT_SIZE_FOUR                         (0x00000003)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_SRC_COMPONENTS                          21:20
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_SRC_COMPONENTS_ONE                      (0x00000000)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_SRC_COMPONENTS_TWO                      (0x00000001)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_SRC_COMPONENTS_THREE                    (0x00000002)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_SRC_COMPONENTS_FOUR                     (0x00000003)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_DST_COMPONENTS                          25:24
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_DST_COMPONENTS_ONE                      (0x00000000)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_DST_COMPONENTS_TWO                      (0x00000001)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_DST_COMPONENTS_THREE                    (0x00000002)
#घोषणा NVA0B5_SET_REMAP_COMPONENTS_NUM_DST_COMPONENTS_FOUR                     (0x00000003)
#पूर्ण_अगर // _cla0b5_h
