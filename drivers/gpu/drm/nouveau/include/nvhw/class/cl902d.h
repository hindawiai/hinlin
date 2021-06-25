<शैली गुरु>
/*
 * Copyright (c) 2003 - 2004, NVIDIA CORPORATION. All rights reserved.
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

#अगर_अघोषित _cl_fermi_twod_a_h_
#घोषणा _cl_fermi_twod_a_h_

#घोषणा NV902D_SET_OBJECT                                                                                  0x0000
#घोषणा NV902D_SET_OBJECT_CLASS_ID                                                                           15:0
#घोषणा NV902D_SET_OBJECT_ENGINE_ID                                                                         20:16

#घोषणा NV902D_WAIT_FOR_IDLE                                                                               0x0110
#घोषणा NV902D_WAIT_FOR_IDLE_V                                                                               31:0

#घोषणा NV902D_SET_DST_FORMAT                                                                              0x0200
#घोषणा NV902D_SET_DST_FORMAT_V                                                                               7:0
#घोषणा NV902D_SET_DST_FORMAT_V_A8R8G8B8                                                               0x000000CF
#घोषणा NV902D_SET_DST_FORMAT_V_A8RL8GL8BL8                                                            0x000000D0
#घोषणा NV902D_SET_DST_FORMAT_V_A2R10G10B10                                                            0x000000DF
#घोषणा NV902D_SET_DST_FORMAT_V_A8B8G8R8                                                               0x000000D5
#घोषणा NV902D_SET_DST_FORMAT_V_A8BL8GL8RL8                                                            0x000000D6
#घोषणा NV902D_SET_DST_FORMAT_V_A2B10G10R10                                                            0x000000D1
#घोषणा NV902D_SET_DST_FORMAT_V_X8R8G8B8                                                               0x000000E6
#घोषणा NV902D_SET_DST_FORMAT_V_X8RL8GL8BL8                                                            0x000000E7
#घोषणा NV902D_SET_DST_FORMAT_V_X8B8G8R8                                                               0x000000F9
#घोषणा NV902D_SET_DST_FORMAT_V_X8BL8GL8RL8                                                            0x000000FA
#घोषणा NV902D_SET_DST_FORMAT_V_R5G6B5                                                                 0x000000E8
#घोषणा NV902D_SET_DST_FORMAT_V_A1R5G5B5                                                               0x000000E9
#घोषणा NV902D_SET_DST_FORMAT_V_X1R5G5B5                                                               0x000000F8
#घोषणा NV902D_SET_DST_FORMAT_V_Y8                                                                     0x000000F3
#घोषणा NV902D_SET_DST_FORMAT_V_Y16                                                                    0x000000EE
#घोषणा NV902D_SET_DST_FORMAT_V_Y32                                                                    0x000000FF
#घोषणा NV902D_SET_DST_FORMAT_V_Z1R5G5B5                                                               0x000000FB
#घोषणा NV902D_SET_DST_FORMAT_V_O1R5G5B5                                                               0x000000FC
#घोषणा NV902D_SET_DST_FORMAT_V_Z8R8G8B8                                                               0x000000FD
#घोषणा NV902D_SET_DST_FORMAT_V_O8R8G8B8                                                               0x000000FE
#घोषणा NV902D_SET_DST_FORMAT_V_Y1_8X8                                                                 0x0000001C
#घोषणा NV902D_SET_DST_FORMAT_V_RF16                                                                   0x000000F2
#घोषणा NV902D_SET_DST_FORMAT_V_RF32                                                                   0x000000E5
#घोषणा NV902D_SET_DST_FORMAT_V_RF32_GF32                                                              0x000000CB
#घोषणा NV902D_SET_DST_FORMAT_V_RF16_GF16_BF16_AF16                                                    0x000000CA
#घोषणा NV902D_SET_DST_FORMAT_V_RF16_GF16_BF16_X16                                                     0x000000CE
#घोषणा NV902D_SET_DST_FORMAT_V_RF32_GF32_BF32_AF32                                                    0x000000C0
#घोषणा NV902D_SET_DST_FORMAT_V_RF32_GF32_BF32_X32                                                     0x000000C3
#घोषणा NV902D_SET_DST_FORMAT_V_R16_G16_B16_A16                                                        0x000000C6
#घोषणा NV902D_SET_DST_FORMAT_V_RN16_GN16_BN16_AN16                                                    0x000000C7
#घोषणा NV902D_SET_DST_FORMAT_V_BF10GF11RF11                                                           0x000000E0
#घोषणा NV902D_SET_DST_FORMAT_V_AN8BN8GN8RN8                                                           0x000000D7
#घोषणा NV902D_SET_DST_FORMAT_V_RF16_GF16                                                              0x000000DE
#घोषणा NV902D_SET_DST_FORMAT_V_R16_G16                                                                0x000000DA
#घोषणा NV902D_SET_DST_FORMAT_V_RN16_GN16                                                              0x000000DB
#घोषणा NV902D_SET_DST_FORMAT_V_G8R8                                                                   0x000000EA
#घोषणा NV902D_SET_DST_FORMAT_V_GN8RN8                                                                 0x000000EB
#घोषणा NV902D_SET_DST_FORMAT_V_RN16                                                                   0x000000EF
#घोषणा NV902D_SET_DST_FORMAT_V_RN8                                                                    0x000000F4
#घोषणा NV902D_SET_DST_FORMAT_V_A8                                                                     0x000000F7

#घोषणा NV902D_SET_DST_MEMORY_LAYOUT                                                                       0x0204
#घोषणा NV902D_SET_DST_MEMORY_LAYOUT_V                                                                        0:0
#घोषणा NV902D_SET_DST_MEMORY_LAYOUT_V_BLOCKLINEAR                                                     0x00000000
#घोषणा NV902D_SET_DST_MEMORY_LAYOUT_V_PITCH                                                           0x00000001

#घोषणा NV902D_SET_DST_PITCH                                                                               0x0214
#घोषणा NV902D_SET_DST_PITCH_V                                                                               31:0

#घोषणा NV902D_SET_DST_WIDTH                                                                               0x0218
#घोषणा NV902D_SET_DST_WIDTH_V                                                                               31:0

#घोषणा NV902D_SET_DST_HEIGHT                                                                              0x021c
#घोषणा NV902D_SET_DST_HEIGHT_V                                                                              31:0

#घोषणा NV902D_SET_DST_OFFSET_UPPER                                                                        0x0220
#घोषणा NV902D_SET_DST_OFFSET_UPPER_V                                                                         7:0

#घोषणा NV902D_SET_DST_OFFSET_LOWER                                                                        0x0224
#घोषणा NV902D_SET_DST_OFFSET_LOWER_V                                                                        31:0

#घोषणा NV902D_SET_SRC_FORMAT                                                                              0x0230
#घोषणा NV902D_SET_SRC_FORMAT_V                                                                               7:0
#घोषणा NV902D_SET_SRC_FORMAT_V_A8R8G8B8                                                               0x000000CF
#घोषणा NV902D_SET_SRC_FORMAT_V_A8RL8GL8BL8                                                            0x000000D0
#घोषणा NV902D_SET_SRC_FORMAT_V_A2R10G10B10                                                            0x000000DF
#घोषणा NV902D_SET_SRC_FORMAT_V_A8B8G8R8                                                               0x000000D5
#घोषणा NV902D_SET_SRC_FORMAT_V_A8BL8GL8RL8                                                            0x000000D6
#घोषणा NV902D_SET_SRC_FORMAT_V_A2B10G10R10                                                            0x000000D1
#घोषणा NV902D_SET_SRC_FORMAT_V_X8R8G8B8                                                               0x000000E6
#घोषणा NV902D_SET_SRC_FORMAT_V_X8RL8GL8BL8                                                            0x000000E7
#घोषणा NV902D_SET_SRC_FORMAT_V_X8B8G8R8                                                               0x000000F9
#घोषणा NV902D_SET_SRC_FORMAT_V_X8BL8GL8RL8                                                            0x000000FA
#घोषणा NV902D_SET_SRC_FORMAT_V_R5G6B5                                                                 0x000000E8
#घोषणा NV902D_SET_SRC_FORMAT_V_A1R5G5B5                                                               0x000000E9
#घोषणा NV902D_SET_SRC_FORMAT_V_X1R5G5B5                                                               0x000000F8
#घोषणा NV902D_SET_SRC_FORMAT_V_Y8                                                                     0x000000F3
#घोषणा NV902D_SET_SRC_FORMAT_V_AY8                                                                    0x0000001D
#घोषणा NV902D_SET_SRC_FORMAT_V_Y16                                                                    0x000000EE
#घोषणा NV902D_SET_SRC_FORMAT_V_Y32                                                                    0x000000FF
#घोषणा NV902D_SET_SRC_FORMAT_V_Z1R5G5B5                                                               0x000000FB
#घोषणा NV902D_SET_SRC_FORMAT_V_O1R5G5B5                                                               0x000000FC
#घोषणा NV902D_SET_SRC_FORMAT_V_Z8R8G8B8                                                               0x000000FD
#घोषणा NV902D_SET_SRC_FORMAT_V_O8R8G8B8                                                               0x000000FE
#घोषणा NV902D_SET_SRC_FORMAT_V_Y1_8X8                                                                 0x0000001C
#घोषणा NV902D_SET_SRC_FORMAT_V_RF16                                                                   0x000000F2
#घोषणा NV902D_SET_SRC_FORMAT_V_RF32                                                                   0x000000E5
#घोषणा NV902D_SET_SRC_FORMAT_V_RF32_GF32                                                              0x000000CB
#घोषणा NV902D_SET_SRC_FORMAT_V_RF16_GF16_BF16_AF16                                                    0x000000CA
#घोषणा NV902D_SET_SRC_FORMAT_V_RF16_GF16_BF16_X16                                                     0x000000CE
#घोषणा NV902D_SET_SRC_FORMAT_V_RF32_GF32_BF32_AF32                                                    0x000000C0
#घोषणा NV902D_SET_SRC_FORMAT_V_RF32_GF32_BF32_X32                                                     0x000000C3
#घोषणा NV902D_SET_SRC_FORMAT_V_R16_G16_B16_A16                                                        0x000000C6
#घोषणा NV902D_SET_SRC_FORMAT_V_RN16_GN16_BN16_AN16                                                    0x000000C7
#घोषणा NV902D_SET_SRC_FORMAT_V_BF10GF11RF11                                                           0x000000E0
#घोषणा NV902D_SET_SRC_FORMAT_V_AN8BN8GN8RN8                                                           0x000000D7
#घोषणा NV902D_SET_SRC_FORMAT_V_RF16_GF16                                                              0x000000DE
#घोषणा NV902D_SET_SRC_FORMAT_V_R16_G16                                                                0x000000DA
#घोषणा NV902D_SET_SRC_FORMAT_V_RN16_GN16                                                              0x000000DB
#घोषणा NV902D_SET_SRC_FORMAT_V_G8R8                                                                   0x000000EA
#घोषणा NV902D_SET_SRC_FORMAT_V_GN8RN8                                                                 0x000000EB
#घोषणा NV902D_SET_SRC_FORMAT_V_RN16                                                                   0x000000EF
#घोषणा NV902D_SET_SRC_FORMAT_V_RN8                                                                    0x000000F4
#घोषणा NV902D_SET_SRC_FORMAT_V_A8                                                                     0x000000F7

#घोषणा NV902D_SET_SRC_MEMORY_LAYOUT                                                                       0x0234
#घोषणा NV902D_SET_SRC_MEMORY_LAYOUT_V                                                                        0:0
#घोषणा NV902D_SET_SRC_MEMORY_LAYOUT_V_BLOCKLINEAR                                                     0x00000000
#घोषणा NV902D_SET_SRC_MEMORY_LAYOUT_V_PITCH                                                           0x00000001

#घोषणा NV902D_SET_SRC_PITCH                                                                               0x0244
#घोषणा NV902D_SET_SRC_PITCH_V                                                                               31:0

#घोषणा NV902D_SET_SRC_WIDTH                                                                               0x0248
#घोषणा NV902D_SET_SRC_WIDTH_V                                                                               31:0

#घोषणा NV902D_SET_SRC_HEIGHT                                                                              0x024c
#घोषणा NV902D_SET_SRC_HEIGHT_V                                                                              31:0

#घोषणा NV902D_SET_SRC_OFFSET_UPPER                                                                        0x0250
#घोषणा NV902D_SET_SRC_OFFSET_UPPER_V                                                                         7:0

#घोषणा NV902D_SET_SRC_OFFSET_LOWER                                                                        0x0254
#घोषणा NV902D_SET_SRC_OFFSET_LOWER_V                                                                        31:0

#घोषणा NV902D_SET_CLIP_ENABLE                                                                             0x0290
#घोषणा NV902D_SET_CLIP_ENABLE_V                                                                              0:0
#घोषणा NV902D_SET_CLIP_ENABLE_V_FALSE                                                                 0x00000000
#घोषणा NV902D_SET_CLIP_ENABLE_V_TRUE                                                                  0x00000001

#घोषणा NV902D_SET_ROP                                                                                     0x02a0
#घोषणा NV902D_SET_ROP_V                                                                                      7:0

#घोषणा NV902D_SET_OPERATION                                                                               0x02ac
#घोषणा NV902D_SET_OPERATION_V                                                                                2:0
#घोषणा NV902D_SET_OPERATION_V_SRCCOPY_AND                                                             0x00000000
#घोषणा NV902D_SET_OPERATION_V_ROP_AND                                                                 0x00000001
#घोषणा NV902D_SET_OPERATION_V_BLEND_AND                                                               0x00000002
#घोषणा NV902D_SET_OPERATION_V_SRCCOPY                                                                 0x00000003
#घोषणा NV902D_SET_OPERATION_V_ROP                                                                     0x00000004
#घोषणा NV902D_SET_OPERATION_V_SRCCOPY_PREMULT                                                         0x00000005
#घोषणा NV902D_SET_OPERATION_V_BLEND_PREMULT                                                           0x00000006

#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT                                                         0x02e8
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V                                                          2:0
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V_A8X8R5G6B5                                        0x00000000
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V_A1R5G5B5                                          0x00000001
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V_A8R8G8B8                                          0x00000002
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V_A8Y8                                              0x00000003
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V_A8X8Y16                                           0x00000004
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V_Y32                                               0x00000005
#घोषणा NV902D_SET_MONOCHROME_PATTERN_COLOR_FORMAT_V_BYTE_EXPAND                                       0x00000006

#घोषणा NV902D_SET_MONOCHROME_PATTERN_FORMAT                                                               0x02ec
#घोषणा NV902D_SET_MONOCHROME_PATTERN_FORMAT_V                                                                0:0
#घोषणा NV902D_SET_MONOCHROME_PATTERN_FORMAT_V_CGA6_M1                                                 0x00000000
#घोषणा NV902D_SET_MONOCHROME_PATTERN_FORMAT_V_LE_M1                                                   0x00000001

#घोषणा NV902D_RENDER_SOLID_PRIM_MODE                                                                      0x0580
#घोषणा NV902D_RENDER_SOLID_PRIM_MODE_V                                                                       2:0
#घोषणा NV902D_RENDER_SOLID_PRIM_MODE_V_POINTS                                                         0x00000000
#घोषणा NV902D_RENDER_SOLID_PRIM_MODE_V_LINES                                                          0x00000001
#घोषणा NV902D_RENDER_SOLID_PRIM_MODE_V_POLYLINE                                                       0x00000002
#घोषणा NV902D_RENDER_SOLID_PRIM_MODE_V_TRIANGLES                                                      0x00000003
#घोषणा NV902D_RENDER_SOLID_PRIM_MODE_V_RECTS                                                          0x00000004

#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT                                                          0x0584
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V                                                           7:0
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_RF32_GF32_BF32_AF32                                0x000000C0
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_RF16_GF16_BF16_AF16                                0x000000CA
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_RF32_GF32                                          0x000000CB
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_A8R8G8B8                                           0x000000CF
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_A2R10G10B10                                        0x000000DF
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_A8B8G8R8                                           0x000000D5
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_A2B10G10R10                                        0x000000D1
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_X8R8G8B8                                           0x000000E6
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_X8B8G8R8                                           0x000000F9
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_R5G6B5                                             0x000000E8
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_A1R5G5B5                                           0x000000E9
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_X1R5G5B5                                           0x000000F8
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_Y8                                                 0x000000F3
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_Y16                                                0x000000EE
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_Y32                                                0x000000FF
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_Z1R5G5B5                                           0x000000FB
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_O1R5G5B5                                           0x000000FC
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_Z8R8G8B8                                           0x000000FD
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_FORMAT_V_O8R8G8B8                                           0x000000FE

#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR                                                                 0x0588
#घोषणा NV902D_SET_RENDER_SOLID_PRIM_COLOR_V                                                                 31:0

#घोषणा NV902D_RENDER_SOLID_PRIM_POINT_SET_X(j)                                                    (0x0600+(j)*8)
#घोषणा NV902D_RENDER_SOLID_PRIM_POINT_SET_X_V                                                               31:0

#घोषणा NV902D_RENDER_SOLID_PRIM_POINT_Y(j)                                                        (0x0604+(j)*8)
#घोषणा NV902D_RENDER_SOLID_PRIM_POINT_Y_V                                                                   31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DATA_TYPE                                                               0x0800
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DATA_TYPE_V                                                                0:0
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DATA_TYPE_V_COLOR                                                   0x00000000
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DATA_TYPE_V_INDEX                                                   0x00000001

#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT                                                            0x0804
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V                                                             7:0
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_A8R8G8B8                                             0x000000CF
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_A2R10G10B10                                          0x000000DF
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_A8B8G8R8                                             0x000000D5
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_A2B10G10R10                                          0x000000D1
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_X8R8G8B8                                             0x000000E6
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_X8B8G8R8                                             0x000000F9
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_R5G6B5                                               0x000000E8
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_A1R5G5B5                                             0x000000E9
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_X1R5G5B5                                             0x000000F8
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_Y8                                                   0x000000F3
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_Y16                                                  0x000000EE
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_Y32                                                  0x000000FF
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_Z1R5G5B5                                             0x000000FB
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_O1R5G5B5                                             0x000000FC
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_Z8R8G8B8                                             0x000000FD
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR_FORMAT_V_O8R8G8B8                                             0x000000FE

#घोषणा NV902D_SET_PIXELS_FROM_CPU_INDEX_FORMAT                                                            0x0808
#घोषणा NV902D_SET_PIXELS_FROM_CPU_INDEX_FORMAT_V                                                             1:0
#घोषणा NV902D_SET_PIXELS_FROM_CPU_INDEX_FORMAT_V_I1                                                   0x00000000
#घोषणा NV902D_SET_PIXELS_FROM_CPU_INDEX_FORMAT_V_I4                                                   0x00000001
#घोषणा NV902D_SET_PIXELS_FROM_CPU_INDEX_FORMAT_V_I8                                                   0x00000002

#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_FORMAT                                                             0x080c
#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_FORMAT_V                                                              0:0
#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_FORMAT_V_CGA6_M1                                               0x00000000
#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_FORMAT_V_LE_M1                                                 0x00000001

#घोषणा NV902D_SET_PIXELS_FROM_CPU_WRAP                                                                    0x0810
#घोषणा NV902D_SET_PIXELS_FROM_CPU_WRAP_V                                                                     1:0
#घोषणा NV902D_SET_PIXELS_FROM_CPU_WRAP_V_WRAP_PIXEL                                                   0x00000000
#घोषणा NV902D_SET_PIXELS_FROM_CPU_WRAP_V_WRAP_BYTE                                                    0x00000001
#घोषणा NV902D_SET_PIXELS_FROM_CPU_WRAP_V_WRAP_DWORD                                                   0x00000002

#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR0                                                                  0x0814
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR0_V                                                                  31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR1                                                                  0x0818
#घोषणा NV902D_SET_PIXELS_FROM_CPU_COLOR1_V                                                                  31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_OPACITY                                                            0x081c
#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_OPACITY_V                                                             0:0
#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_OPACITY_V_TRANSPARENT                                          0x00000000
#घोषणा NV902D_SET_PIXELS_FROM_CPU_MONO_OPACITY_V_OPAQUE                                               0x00000001

#घोषणा NV902D_SET_PIXELS_FROM_CPU_SRC_WIDTH                                                               0x0838
#घोषणा NV902D_SET_PIXELS_FROM_CPU_SRC_WIDTH_V                                                               31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_SRC_HEIGHT                                                              0x083c
#घोषणा NV902D_SET_PIXELS_FROM_CPU_SRC_HEIGHT_V                                                              31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DX_DU_FRAC                                                              0x0840
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DX_DU_FRAC_V                                                              31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DX_DU_INT                                                               0x0844
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DX_DU_INT_V                                                               31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DY_DV_FRAC                                                              0x0848
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DY_DV_FRAC_V                                                              31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DY_DV_INT                                                               0x084c
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DY_DV_INT_V                                                               31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_X0_FRAC                                                             0x0850
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_X0_FRAC_V                                                             31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_X0_INT                                                              0x0854
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_X0_INT_V                                                              31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_Y0_FRAC                                                             0x0858
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_Y0_FRAC_V                                                             31:0

#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_Y0_INT                                                              0x085c
#घोषणा NV902D_SET_PIXELS_FROM_CPU_DST_Y0_INT_V                                                              31:0

#घोषणा NV902D_PIXELS_FROM_CPU_DATA                                                                        0x0860
#घोषणा NV902D_PIXELS_FROM_CPU_DATA_V                                                                        31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SAFE_OVERLAP                                                         0x0888
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SAFE_OVERLAP_V                                                          0:0
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SAFE_OVERLAP_V_FALSE                                             0x00000000
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SAFE_OVERLAP_V_TRUE                                              0x00000001

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_X0                                                               0x08b0
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_X0_V                                                               31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_Y0                                                               0x08b4
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_Y0_V                                                               31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_WIDTH                                                            0x08b8
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_WIDTH_V                                                            31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_HEIGHT                                                           0x08bc
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DST_HEIGHT_V                                                           31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DU_DX_FRAC                                                           0x08c0
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DU_DX_FRAC_V                                                           31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DU_DX_INT                                                            0x08c4
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DU_DX_INT_V                                                            31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DV_DY_FRAC                                                           0x08c8
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DV_DY_FRAC_V                                                           31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DV_DY_INT                                                            0x08cc
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_DV_DY_INT_V                                                            31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SRC_X0_FRAC                                                          0x08d0
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SRC_X0_FRAC_V                                                          31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SRC_X0_INT                                                           0x08d4
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SRC_X0_INT_V                                                           31:0

#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SRC_Y0_FRAC                                                          0x08d8
#घोषणा NV902D_SET_PIXELS_FROM_MEMORY_SRC_Y0_FRAC_V                                                          31:0

#घोषणा NV902D_PIXELS_FROM_MEMORY_SRC_Y0_INT                                                               0x08dc
#घोषणा NV902D_PIXELS_FROM_MEMORY_SRC_Y0_INT_V                                                               31:0
#पूर्ण_अगर /* _cl_fermi_twod_a_h_ */
