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


#अगर_अघोषित _cl827e_h_
#घोषणा _cl827e_h_

#घोषणा NV_DISP_NOTIFICATION_1                                                       0x00000000
#घोषणा NV_DISP_NOTIFICATION_1_SIZखातापूर्ण                                                0x00000010
#घोषणा NV_DISP_NOTIFICATION_1_TIME_STAMP_0                                          0x00000000
#घोषणा NV_DISP_NOTIFICATION_1_TIME_STAMP_0_न_अंकOSECONDS0                             31:0
#घोषणा NV_DISP_NOTIFICATION_1_TIME_STAMP_1                                          0x00000001
#घोषणा NV_DISP_NOTIFICATION_1_TIME_STAMP_1_न_अंकOSECONDS1                             31:0
#घोषणा NV_DISP_NOTIFICATION_1__2                                                    0x00000002
#घोषणा NV_DISP_NOTIFICATION_1__2_AUDIT_TIMESTAMP                                    31:0
#घोषणा NV_DISP_NOTIFICATION_1__3                                                    0x00000003
#घोषणा NV_DISP_NOTIFICATION_1__3_PRESENT_COUNT                                      7:0
#घोषणा NV_DISP_NOTIFICATION_1__3_R0                                                 15:8
#घोषणा NV_DISP_NOTIFICATION_1__3_STATUS                                             31:16
#घोषणा NV_DISP_NOTIFICATION_1__3_STATUS_NOT_BEGUN                                   0x00008000
#घोषणा NV_DISP_NOTIFICATION_1__3_STATUS_BEGUN                                       0x0000FFFF
#घोषणा NV_DISP_NOTIFICATION_1__3_STATUS_FINISHED                                    0x00000000


// class methods
#घोषणा NV827E_SET_PRESENT_CONTROL                                              (0x00000084)
#घोषणा NV827E_SET_PRESENT_CONTROL_BEGIN_MODE                                   1:0
#घोषणा NV827E_SET_PRESENT_CONTROL_BEGIN_MODE_ASAP                              (0x00000000)
#घोषणा NV827E_SET_PRESENT_CONTROL_BEGIN_MODE_TIMESTAMP                         (0x00000003)
#घोषणा NV827E_SET_PRESENT_CONTROL_MIN_PRESENT_INTERVAL                         7:4
#घोषणा NV827E_SET_CONTEXT_DMA_ISO                                              (0x000000C0)
#घोषणा NV827E_SET_CONTEXT_DMA_ISO_HANDLE                                       31:0
#घोषणा NV827E_SET_COMPOSITION_CONTROL                                          (0x00000100)
#घोषणा NV827E_SET_COMPOSITION_CONTROL_MODE                                     3:0
#घोषणा NV827E_SET_COMPOSITION_CONTROL_MODE_SOURCE_COLOR_VALUE_KEYING           (0x00000000)
#घोषणा NV827E_SET_COMPOSITION_CONTROL_MODE_DESTINATION_COLOR_VALUE_KEYING      (0x00000001)
#घोषणा NV827E_SET_COMPOSITION_CONTROL_MODE_OPAQUE_SUSPEND_BASE                 (0x00000002)

#घोषणा NV827E_SURFACE_SET_OFFSET                                               (0x00000800)
#घोषणा NV827E_SURFACE_SET_OFFSET_ORIGIN                                        31:0
#घोषणा NV827E_SURFACE_SET_SIZE                                                 (0x00000808)
#घोषणा NV827E_SURFACE_SET_SIZE_WIDTH                                           14:0
#घोषणा NV827E_SURFACE_SET_SIZE_HEIGHT                                          30:16
#घोषणा NV827E_SURFACE_SET_STORAGE                                              (0x0000080C)
#घोषणा NV827E_SURFACE_SET_STORAGE_BLOCK_HEIGHT                                 3:0
#घोषणा NV827E_SURFACE_SET_STORAGE_BLOCK_HEIGHT_ONE_GOB                         (0x00000000)
#घोषणा NV827E_SURFACE_SET_STORAGE_BLOCK_HEIGHT_TWO_GOBS                        (0x00000001)
#घोषणा NV827E_SURFACE_SET_STORAGE_BLOCK_HEIGHT_FOUR_GOBS                       (0x00000002)
#घोषणा NV827E_SURFACE_SET_STORAGE_BLOCK_HEIGHT_EIGHT_GOBS                      (0x00000003)
#घोषणा NV827E_SURFACE_SET_STORAGE_BLOCK_HEIGHT_SIXTEEN_GOBS                    (0x00000004)
#घोषणा NV827E_SURFACE_SET_STORAGE_BLOCK_HEIGHT_THIRTYTWO_GOBS                  (0x00000005)
#घोषणा NV827E_SURFACE_SET_STORAGE_PITCH                                        17:8
#घोषणा NV827E_SURFACE_SET_STORAGE_MEMORY_LAYOUT                                20:20
#घोषणा NV827E_SURFACE_SET_STORAGE_MEMORY_LAYOUT_BLOCKLINEAR                    (0x00000000)
#घोषणा NV827E_SURFACE_SET_STORAGE_MEMORY_LAYOUT_PITCH                          (0x00000001)
#घोषणा NV827E_SURFACE_SET_PARAMS                                               (0x00000810)
#घोषणा NV827E_SURFACE_SET_PARAMS_FORMAT                                        15:8
#घोषणा NV827E_SURFACE_SET_PARAMS_FORMAT_VE8YO8UE8YE8                           (0x00000028)
#घोषणा NV827E_SURFACE_SET_PARAMS_FORMAT_YO8VE8YE8UE8                           (0x00000029)
#घोषणा NV827E_SURFACE_SET_PARAMS_FORMAT_A2B10G10R10                            (0x000000D1)
#घोषणा NV827E_SURFACE_SET_PARAMS_FORMAT_A8R8G8B8                               (0x000000CF)
#घोषणा NV827E_SURFACE_SET_PARAMS_FORMAT_A1R5G5B5                               (0x000000E9)
#घोषणा NV827E_SURFACE_SET_PARAMS_COLOR_SPACE                                   1:0
#घोषणा NV827E_SURFACE_SET_PARAMS_COLOR_SPACE_RGB                               (0x00000000)
#घोषणा NV827E_SURFACE_SET_PARAMS_COLOR_SPACE_YUV_601                           (0x00000001)
#घोषणा NV827E_SURFACE_SET_PARAMS_COLOR_SPACE_YUV_709                           (0x00000002)
#घोषणा NV827E_SURFACE_SET_PARAMS_RESERVED0                                     22:16
#घोषणा NV827E_SURFACE_SET_PARAMS_RESERVED1                                     24:24
#पूर्ण_अगर // _cl827e_h
