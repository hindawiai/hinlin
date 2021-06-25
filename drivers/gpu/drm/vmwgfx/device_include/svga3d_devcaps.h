<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**********************************************************
 * Copyright 1998-2019 VMware, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person
 * obtaining a copy of this software and associated करोcumentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************/

/*
 * svga3d_devcaps.h --
 *
 *       SVGA 3d caps definitions
 */

#अगर_अघोषित _SVGA3D_DEVCAPS_H_
#घोषणा _SVGA3D_DEVCAPS_H_

#घोषणा INCLUDE_ALLOW_MODULE
#घोषणा INCLUDE_ALLOW_USERLEVEL
#घोषणा INCLUDE_ALLOW_VMCORE

#समावेश "includeCheck.h"

#समावेश "svga3d_types.h"

/*
 * 3D Hardware Version
 *
 *   The hardware version is stored in the SVGA_FIFO_3D_HWVERSION fअगरo
 *   रेजिस्टर.   Is set by the host and पढ़ो by the guest.  This lets
 *   us make new guest drivers which are backwards-compatible with old
 *   SVGA hardware revisions.  It करोes not let us support old guest
 *   drivers.  Good enough क्रम now.
 *
 */

#घोषणा SVGA3D_MAKE_HWVERSION(major, minor)      (((major) << 16) | ((minor) & 0xFF))
#घोषणा SVGA3D_MAJOR_HWVERSION(version)          ((version) >> 16)
#घोषणा SVGA3D_MINOR_HWVERSION(version)          ((version) & 0xFF)

प्रकार क्रमागत अणु
   SVGA3D_HWVERSION_WS5_RC1   = SVGA3D_MAKE_HWVERSION(0, 1),
   SVGA3D_HWVERSION_WS5_RC2   = SVGA3D_MAKE_HWVERSION(0, 2),
   SVGA3D_HWVERSION_WS51_RC1  = SVGA3D_MAKE_HWVERSION(0, 3),
   SVGA3D_HWVERSION_WS6_B1    = SVGA3D_MAKE_HWVERSION(1, 1),
   SVGA3D_HWVERSION_FUSION_11 = SVGA3D_MAKE_HWVERSION(1, 4),
   SVGA3D_HWVERSION_WS65_B1   = SVGA3D_MAKE_HWVERSION(2, 0),
   SVGA3D_HWVERSION_WS8_B1    = SVGA3D_MAKE_HWVERSION(2, 1),
   SVGA3D_HWVERSION_CURRENT   = SVGA3D_HWVERSION_WS8_B1,
पूर्ण SVGA3dHardwareVersion;

/*
 * DevCap indexes.
 */

प्रकार uपूर्णांक32 SVGA3dDevCapIndex;

#घोषणा SVGA3D_DEVCAP_INVALID                              ((uपूर्णांक32)-1)
#घोषणा SVGA3D_DEVCAP_3D                                   0
#घोषणा SVGA3D_DEVCAP_MAX_LIGHTS                           1

/*
 * SVGA3D_DEVCAP_MAX_TEXTURES reflects the maximum number of
 * fixed-function texture units available. Each of these units
 * work in both FFP and Shader modes, and they support texture
 * transक्रमms and texture coordinates. The host may have additional
 * texture image units that are only usable with shaders.
 */
#घोषणा SVGA3D_DEVCAP_MAX_TEXTURES                         2
#घोषणा SVGA3D_DEVCAP_MAX_CLIP_PLANES                      3
#घोषणा SVGA3D_DEVCAP_VERTEX_SHADER_VERSION                4
#घोषणा SVGA3D_DEVCAP_VERTEX_SHADER                        5
#घोषणा SVGA3D_DEVCAP_FRAGMENT_SHADER_VERSION              6
#घोषणा SVGA3D_DEVCAP_FRAGMENT_SHADER                      7
#घोषणा SVGA3D_DEVCAP_MAX_RENDER_TARGETS                   8
#घोषणा SVGA3D_DEVCAP_S23E8_TEXTURES                       9
#घोषणा SVGA3D_DEVCAP_S10E5_TEXTURES                       10
#घोषणा SVGA3D_DEVCAP_MAX_FIXED_VERTEXBLEND                11
#घोषणा SVGA3D_DEVCAP_D16_BUFFER_FORMAT                    12
#घोषणा SVGA3D_DEVCAP_D24S8_BUFFER_FORMAT                  13
#घोषणा SVGA3D_DEVCAP_D24X8_BUFFER_FORMAT                  14
#घोषणा SVGA3D_DEVCAP_QUERY_TYPES                          15
#घोषणा SVGA3D_DEVCAP_TEXTURE_GRADIENT_SAMPLING            16
#घोषणा SVGA3D_DEVCAP_MAX_POINT_SIZE                       17
#घोषणा SVGA3D_DEVCAP_MAX_SHADER_TEXTURES                  18
#घोषणा SVGA3D_DEVCAP_MAX_TEXTURE_WIDTH                    19
#घोषणा SVGA3D_DEVCAP_MAX_TEXTURE_HEIGHT                   20
#घोषणा SVGA3D_DEVCAP_MAX_VOLUME_EXTENT                    21
#घोषणा SVGA3D_DEVCAP_MAX_TEXTURE_REPEAT                   22
#घोषणा SVGA3D_DEVCAP_MAX_TEXTURE_ASPECT_RATIO             23
#घोषणा SVGA3D_DEVCAP_MAX_TEXTURE_ANISOTROPY               24
#घोषणा SVGA3D_DEVCAP_MAX_PRIMITIVE_COUNT                  25
#घोषणा SVGA3D_DEVCAP_MAX_VERTEX_INDEX                     26
#घोषणा SVGA3D_DEVCAP_MAX_VERTEX_SHADER_INSTRUCTIONS       27
#घोषणा SVGA3D_DEVCAP_MAX_FRAGMENT_SHADER_INSTRUCTIONS     28
#घोषणा SVGA3D_DEVCAP_MAX_VERTEX_SHADER_TEMPS              29
#घोषणा SVGA3D_DEVCAP_MAX_FRAGMENT_SHADER_TEMPS            30
#घोषणा SVGA3D_DEVCAP_TEXTURE_OPS                          31
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_X8R8G8B8                  32
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_A8R8G8B8                  33
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_A2R10G10B10               34
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_X1R5G5B5                  35
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_A1R5G5B5                  36
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_A4R4G4B4                  37
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_R5G6B5                    38
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_LUMIन_अंकCE16               39
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_LUMIन_अंकCE8_ALPHA8         40
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_ALPHA8                    41
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_LUMIन_अंकCE8                42
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_Z_D16                     43
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_Z_D24S8                   44
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_Z_D24X8                   45
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_DXT1                      46
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_DXT2                      47
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_DXT3                      48
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_DXT4                      49
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_DXT5                      50
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_BUMPX8L8V8U8              51
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_A2W10V10U10               52
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_BUMPU8V8                  53
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_Q8W8V8U8                  54
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_CxV8U8                    55
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_R_S10E5                   56
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_R_S23E8                   57
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_RG_S10E5                  58
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_RG_S23E8                  59
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_ARGB_S10E5                60
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_ARGB_S23E8                61

/*
 * There is a hole in our devcap definitions क्रम
 * historical reasons.
 *
 * Define a स्थिरant just क्रम completeness.
 */
#घोषणा SVGA3D_DEVCAP_MISSING62                            62

#घोषणा SVGA3D_DEVCAP_MAX_VERTEX_SHADER_TEXTURES           63

/*
 * Note that MAX_SIMULTANEOUS_RENDER_TARGETS is a maximum count of color
 * render tarमाला_लो.  This करोes not include the depth or stencil tarमाला_लो.
 */
#घोषणा SVGA3D_DEVCAP_MAX_SIMULTANEOUS_RENDER_TARGETS      64

#घोषणा SVGA3D_DEVCAP_SURFACEFMT_V16U16                    65
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_G16R16                    66
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_A16B16G16R16              67
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_UYVY                      68
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_YUY2                      69

/*
 * Deprecated.
 */
#घोषणा SVGA3D_DEVCAP_DEAD4                                70
#घोषणा SVGA3D_DEVCAP_DEAD5                                71
#घोषणा SVGA3D_DEVCAP_DEAD7                                72
#घोषणा SVGA3D_DEVCAP_DEAD6                                73

#घोषणा SVGA3D_DEVCAP_AUTOGENMIPMAPS                       74
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_NV12                      75
#घोषणा SVGA3D_DEVCAP_DEAD10                               76

/*
 * This is the maximum number of SVGA context IDs that the guest
 * can define using SVGA_3D_CMD_CONTEXT_DEFINE.
 */
#घोषणा SVGA3D_DEVCAP_MAX_CONTEXT_IDS                      77

/*
 * This is the maximum number of SVGA surface IDs that the guest
 * can define using SVGA_3D_CMD_SURFACE_DEFINE*.
 */
#घोषणा SVGA3D_DEVCAP_MAX_SURFACE_IDS                      78

#घोषणा SVGA3D_DEVCAP_SURFACEFMT_Z_DF16                    79
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_Z_DF24                    80
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_Z_D24S8_INT               81

#घोषणा SVGA3D_DEVCAP_SURFACEFMT_ATI1                      82
#घोषणा SVGA3D_DEVCAP_SURFACEFMT_ATI2                      83

/*
 * Deprecated.
 */
#घोषणा SVGA3D_DEVCAP_DEAD1                                84
#घोषणा SVGA3D_DEVCAP_DEAD8                                85
#घोषणा SVGA3D_DEVCAP_DEAD9                                86

#घोषणा SVGA3D_DEVCAP_LINE_AA                              87  /* boolean */
#घोषणा SVGA3D_DEVCAP_LINE_STIPPLE                         88  /* boolean */
#घोषणा SVGA3D_DEVCAP_MAX_LINE_WIDTH                       89  /* भग्न */
#घोषणा SVGA3D_DEVCAP_MAX_AA_LINE_WIDTH                    90  /* भग्न */

#घोषणा SVGA3D_DEVCAP_SURFACEFMT_YV12                      91

/*
 * Deprecated.
 */
#घोषणा SVGA3D_DEVCAP_DEAD3                                92

/*
 * Are TS_CONSTANT, TS_COLOR_KEY, and TS_COLOR_KEY_ENABLE supported?
 */
#घोषणा SVGA3D_DEVCAP_TS_COLOR_KEY                         93 /* boolean */

/*
 * Deprecated.
 */
#घोषणा SVGA3D_DEVCAP_DEAD2                                94

/*
 * Does the device support DXContexts?
 */
#घोषणा SVGA3D_DEVCAP_DXCONTEXT                            95

/*
 * Deprecated.
 */
#घोषणा SVGA3D_DEVCAP_DEAD11                               96

/*
 * What is the maximum number of vertex buffers or vertex input रेजिस्टरs
 * that can be expected to work correctly with a DXContext?
 *
 * The guest is allowed to set up to SVGA3D_DX_MAX_VERTEXBUFFERS, but
 * anything in excess of this cap is not guaranteed to render correctly.
 *
 * Similarly, the guest can set up to SVGA3D_DX_MAX_VERTEXINPUTREGISTERS
 * input रेजिस्टरs without the SVGA3D_DEVCAP_SM4_1 cap, or
 * SVGA3D_DX_SM41_MAX_VERTEXINPUTREGISTERS with the SVGA3D_DEVCAP_SM4_1,
 * but only the रेजिस्टरs up to this cap value are guaranteed to render
 * correctly.
 *
 * If guest-drivers are able to expose a lower-limit, it's recommended
 * that they clamp to this value.  Otherwise, the host will make a
 * best-efक्रमt on हाल-by-हाल basis अगर guests exceed this.
 */
#घोषणा SVGA3D_DEVCAP_DX_MAX_VERTEXBUFFERS                 97

/*
 * What is the maximum number of स्थिरant buffers that can be expected to
 * work correctly with a DX context?
 *
 * The guest is allowed to set up to SVGA3D_DX_MAX_CONSTBUFFERS, but
 * anything in excess of this cap is not guaranteed to render correctly.
 *
 * If guest-drivers are able to expose a lower-limit, it's recommended
 * that they clamp to this value.  Otherwise, the host will make a
 * best-efक्रमt on हाल-by-हाल basis अगर guests exceed this.
 */
#घोषणा SVGA3D_DEVCAP_DX_MAX_CONSTANT_BUFFERS              98

/*
 * Does the device support provoking vertex control?
 *
 * If this cap is present, the provokingVertexLast field in the
 * rasterizer state is enabled.  (Guests can then set it to FALSE,
 * meaning that the first vertex is the provoking vertex, or TRUE,
 * meaning that the last verteix is the provoking vertex.)
 *
 * If this cap is FALSE, then guests should set the provokingVertexLast
 * to FALSE, otherwise rendering behavior is undefined.
 */
#घोषणा SVGA3D_DEVCAP_DX_PROVOKING_VERTEX                  99

#घोषणा SVGA3D_DEVCAP_DXFMT_X8R8G8B8                       100
#घोषणा SVGA3D_DEVCAP_DXFMT_A8R8G8B8                       101
#घोषणा SVGA3D_DEVCAP_DXFMT_R5G6B5                         102
#घोषणा SVGA3D_DEVCAP_DXFMT_X1R5G5B5                       103
#घोषणा SVGA3D_DEVCAP_DXFMT_A1R5G5B5                       104
#घोषणा SVGA3D_DEVCAP_DXFMT_A4R4G4B4                       105
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_D32                          106
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_D16                          107
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_D24S8                        108
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_D15S1                        109
#घोषणा SVGA3D_DEVCAP_DXFMT_LUMIन_अंकCE8                     110
#घोषणा SVGA3D_DEVCAP_DXFMT_LUMIन_अंकCE4_ALPHA4              111
#घोषणा SVGA3D_DEVCAP_DXFMT_LUMIन_अंकCE16                    112
#घोषणा SVGA3D_DEVCAP_DXFMT_LUMIन_अंकCE8_ALPHA8              113
#घोषणा SVGA3D_DEVCAP_DXFMT_DXT1                           114
#घोषणा SVGA3D_DEVCAP_DXFMT_DXT2                           115
#घोषणा SVGA3D_DEVCAP_DXFMT_DXT3                           116
#घोषणा SVGA3D_DEVCAP_DXFMT_DXT4                           117
#घोषणा SVGA3D_DEVCAP_DXFMT_DXT5                           118
#घोषणा SVGA3D_DEVCAP_DXFMT_BUMPU8V8                       119
#घोषणा SVGA3D_DEVCAP_DXFMT_BUMPL6V5U5                     120
#घोषणा SVGA3D_DEVCAP_DXFMT_BUMPX8L8V8U8                   121
#घोषणा SVGA3D_DEVCAP_DXFMT_FORMAT_DEAD1                   122
#घोषणा SVGA3D_DEVCAP_DXFMT_ARGB_S10E5                     123
#घोषणा SVGA3D_DEVCAP_DXFMT_ARGB_S23E8                     124
#घोषणा SVGA3D_DEVCAP_DXFMT_A2R10G10B10                    125
#घोषणा SVGA3D_DEVCAP_DXFMT_V8U8                           126
#घोषणा SVGA3D_DEVCAP_DXFMT_Q8W8V8U8                       127
#घोषणा SVGA3D_DEVCAP_DXFMT_CxV8U8                         128
#घोषणा SVGA3D_DEVCAP_DXFMT_X8L8V8U8                       129
#घोषणा SVGA3D_DEVCAP_DXFMT_A2W10V10U10                    130
#घोषणा SVGA3D_DEVCAP_DXFMT_ALPHA8                         131
#घोषणा SVGA3D_DEVCAP_DXFMT_R_S10E5                        132
#घोषणा SVGA3D_DEVCAP_DXFMT_R_S23E8                        133
#घोषणा SVGA3D_DEVCAP_DXFMT_RG_S10E5                       134
#घोषणा SVGA3D_DEVCAP_DXFMT_RG_S23E8                       135
#घोषणा SVGA3D_DEVCAP_DXFMT_BUFFER                         136
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_D24X8                        137
#घोषणा SVGA3D_DEVCAP_DXFMT_V16U16                         138
#घोषणा SVGA3D_DEVCAP_DXFMT_G16R16                         139
#घोषणा SVGA3D_DEVCAP_DXFMT_A16B16G16R16                   140
#घोषणा SVGA3D_DEVCAP_DXFMT_UYVY                           141
#घोषणा SVGA3D_DEVCAP_DXFMT_YUY2                           142
#घोषणा SVGA3D_DEVCAP_DXFMT_NV12                           143
#घोषणा SVGA3D_DEVCAP_DXFMT_FORMAT_DEAD2                   144
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32A32_TYPELESS          145
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32A32_UINT              146
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32A32_SINT              147
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32_TYPELESS             148
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32_FLOAT                149
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32_UINT                 150
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32_SINT                 151
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16B16A16_TYPELESS          152
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16B16A16_UINT              153
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16B16A16_SNORM             154
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16B16A16_SINT              155
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32_TYPELESS                156
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32_UINT                    157
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32_SINT                    158
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G8X24_TYPELESS              159
#घोषणा SVGA3D_DEVCAP_DXFMT_D32_FLOAT_S8X24_UINT           160
#घोषणा SVGA3D_DEVCAP_DXFMT_R32_FLOAT_X8X24                161
#घोषणा SVGA3D_DEVCAP_DXFMT_X32_G8X24_UINT                 162
#घोषणा SVGA3D_DEVCAP_DXFMT_R10G10B10A2_TYPELESS           163
#घोषणा SVGA3D_DEVCAP_DXFMT_R10G10B10A2_UINT               164
#घोषणा SVGA3D_DEVCAP_DXFMT_R11G11B10_FLOAT                165
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8B8A8_TYPELESS              166
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8B8A8_UNORM                 167
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8B8A8_UNORM_SRGB            168
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8B8A8_UINT                  169
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8B8A8_SINT                  170
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16_TYPELESS                171
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16_UINT                    172
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16_SINT                    173
#घोषणा SVGA3D_DEVCAP_DXFMT_R32_TYPELESS                   174
#घोषणा SVGA3D_DEVCAP_DXFMT_D32_FLOAT                      175
#घोषणा SVGA3D_DEVCAP_DXFMT_R32_UINT                       176
#घोषणा SVGA3D_DEVCAP_DXFMT_R32_SINT                       177
#घोषणा SVGA3D_DEVCAP_DXFMT_R24G8_TYPELESS                 178
#घोषणा SVGA3D_DEVCAP_DXFMT_D24_UNORM_S8_UINT              179
#घोषणा SVGA3D_DEVCAP_DXFMT_R24_UNORM_X8                   180
#घोषणा SVGA3D_DEVCAP_DXFMT_X24_G8_UINT                    181
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8_TYPELESS                  182
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8_UNORM                     183
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8_UINT                      184
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8_SINT                      185
#घोषणा SVGA3D_DEVCAP_DXFMT_R16_TYPELESS                   186
#घोषणा SVGA3D_DEVCAP_DXFMT_R16_UNORM                      187
#घोषणा SVGA3D_DEVCAP_DXFMT_R16_UINT                       188
#घोषणा SVGA3D_DEVCAP_DXFMT_R16_SNORM                      189
#घोषणा SVGA3D_DEVCAP_DXFMT_R16_SINT                       190
#घोषणा SVGA3D_DEVCAP_DXFMT_R8_TYPELESS                    191
#घोषणा SVGA3D_DEVCAP_DXFMT_R8_UNORM                       192
#घोषणा SVGA3D_DEVCAP_DXFMT_R8_UINT                        193
#घोषणा SVGA3D_DEVCAP_DXFMT_R8_SNORM                       194
#घोषणा SVGA3D_DEVCAP_DXFMT_R8_SINT                        195
#घोषणा SVGA3D_DEVCAP_DXFMT_P8                             196
#घोषणा SVGA3D_DEVCAP_DXFMT_R9G9B9E5_SHAREDEXP             197
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8_B8G8_UNORM                198
#घोषणा SVGA3D_DEVCAP_DXFMT_G8R8_G8B8_UNORM                199
#घोषणा SVGA3D_DEVCAP_DXFMT_BC1_TYPELESS                   200
#घोषणा SVGA3D_DEVCAP_DXFMT_BC1_UNORM_SRGB                 201
#घोषणा SVGA3D_DEVCAP_DXFMT_BC2_TYPELESS                   202
#घोषणा SVGA3D_DEVCAP_DXFMT_BC2_UNORM_SRGB                 203
#घोषणा SVGA3D_DEVCAP_DXFMT_BC3_TYPELESS                   204
#घोषणा SVGA3D_DEVCAP_DXFMT_BC3_UNORM_SRGB                 205
#घोषणा SVGA3D_DEVCAP_DXFMT_BC4_TYPELESS                   206
#घोषणा SVGA3D_DEVCAP_DXFMT_ATI1                           207
#घोषणा SVGA3D_DEVCAP_DXFMT_BC4_SNORM                      208
#घोषणा SVGA3D_DEVCAP_DXFMT_BC5_TYPELESS                   209
#घोषणा SVGA3D_DEVCAP_DXFMT_ATI2                           210
#घोषणा SVGA3D_DEVCAP_DXFMT_BC5_SNORM                      211
#घोषणा SVGA3D_DEVCAP_DXFMT_R10G10B10_XR_BIAS_A2_UNORM     212
#घोषणा SVGA3D_DEVCAP_DXFMT_B8G8R8A8_TYPELESS              213
#घोषणा SVGA3D_DEVCAP_DXFMT_B8G8R8A8_UNORM_SRGB            214
#घोषणा SVGA3D_DEVCAP_DXFMT_B8G8R8X8_TYPELESS              215
#घोषणा SVGA3D_DEVCAP_DXFMT_B8G8R8X8_UNORM_SRGB            216
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_DF16                         217
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_DF24                         218
#घोषणा SVGA3D_DEVCAP_DXFMT_Z_D24S8_INT                    219
#घोषणा SVGA3D_DEVCAP_DXFMT_YV12                           220
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32B32A32_FLOAT             221
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16B16A16_FLOAT             222
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16B16A16_UNORM             223
#घोषणा SVGA3D_DEVCAP_DXFMT_R32G32_FLOAT                   224
#घोषणा SVGA3D_DEVCAP_DXFMT_R10G10B10A2_UNORM              225
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8B8A8_SNORM                 226
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16_FLOAT                   227
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16_UNORM                   228
#घोषणा SVGA3D_DEVCAP_DXFMT_R16G16_SNORM                   229
#घोषणा SVGA3D_DEVCAP_DXFMT_R32_FLOAT                      230
#घोषणा SVGA3D_DEVCAP_DXFMT_R8G8_SNORM                     231
#घोषणा SVGA3D_DEVCAP_DXFMT_R16_FLOAT                      232
#घोषणा SVGA3D_DEVCAP_DXFMT_D16_UNORM                      233
#घोषणा SVGA3D_DEVCAP_DXFMT_A8_UNORM                       234
#घोषणा SVGA3D_DEVCAP_DXFMT_BC1_UNORM                      235
#घोषणा SVGA3D_DEVCAP_DXFMT_BC2_UNORM                      236
#घोषणा SVGA3D_DEVCAP_DXFMT_BC3_UNORM                      237
#घोषणा SVGA3D_DEVCAP_DXFMT_B5G6R5_UNORM                   238
#घोषणा SVGA3D_DEVCAP_DXFMT_B5G5R5A1_UNORM                 239
#घोषणा SVGA3D_DEVCAP_DXFMT_B8G8R8A8_UNORM                 240
#घोषणा SVGA3D_DEVCAP_DXFMT_B8G8R8X8_UNORM                 241
#घोषणा SVGA3D_DEVCAP_DXFMT_BC4_UNORM                      242
#घोषणा SVGA3D_DEVCAP_DXFMT_BC5_UNORM                      243

/*
 * Advertises shaderModel 4.1 support, independent blend-states,
 * cube-map arrays, and a higher vertex input रेजिस्टरs limit.
 *
 * (See करोcumentation on SVGA3D_DEVCAP_DX_MAX_VERTEXBUFFERS.)
 */
#घोषणा SVGA3D_DEVCAP_SM41                                 244
#घोषणा SVGA3D_DEVCAP_MULTISAMPLE_2X                       245
#घोषणा SVGA3D_DEVCAP_MULTISAMPLE_4X                       246

/*
 * Indicates that the device has rendering support क्रम
 * the full multisample quality.  If this cap is not present,
 * the host may or may not support full quality rendering.
 *
 * See also SVGA_REG_MS_HINT_RESOLVED.
 */
#घोषणा SVGA3D_DEVCAP_MS_FULL_QUALITY                      247

/*
 * Advertises support क्रम the SVGA3D LogicOps commands.
 */
#घोषणा SVGA3D_DEVCAP_LOGICOPS                             248

/*
 * Advertises support क्रम using logicOps in the DXBlendStates.
 */
#घोषणा SVGA3D_DEVCAP_LOGIC_BLENDOPS                       249

/*
* Note DXFMT range is now non-contiguous.
*/
#घोषणा SVGA3D_DEVCAP_RESERVED_1                           250
#घोषणा SVGA3D_DEVCAP_DXFMT_BC6H_TYPELESS                  251
#घोषणा SVGA3D_DEVCAP_DXFMT_BC6H_UF16                      252
#घोषणा SVGA3D_DEVCAP_DXFMT_BC6H_SF16                      253
#घोषणा SVGA3D_DEVCAP_DXFMT_BC7_TYPELESS                   254
#घोषणा SVGA3D_DEVCAP_DXFMT_BC7_UNORM                      255
#घोषणा SVGA3D_DEVCAP_DXFMT_BC7_UNORM_SRGB                 256
#घोषणा SVGA3D_DEVCAP_RESERVED_2                           257

#घोषणा SVGA3D_DEVCAP_SM5                                  258
#घोषणा SVGA3D_DEVCAP_MULTISAMPLE_8X                       259

/* This must be the last index. */
#घोषणा SVGA3D_DEVCAP_MAX                                  260

/*
 * Bit definitions क्रम DXFMT devcaps
 *
 *
 * SUPPORTED: Can the क्रमmat be defined?
 * SHADER_SAMPLE: Can the क्रमmat be sampled from a shader?
 * COLOR_RENDERTARGET: Can the क्रमmat be a color render target?
 * DEPTH_RENDERTARGET: Can the क्रमmat be a depth render target?
 * BLENDABLE: Is the क्रमmat blendable?
 * MIPS: Does the क्रमmat support mip levels?
 * ARRAY: Does the क्रमmat support texture arrays?
 * VOLUME: Does the क्रमmat support having volume?
 * MULTISAMPLE: Does the क्रमmat support multisample?
 */
#घोषणा SVGA3D_DXFMT_SUPPORTED                (1 <<  0)
#घोषणा SVGA3D_DXFMT_SHADER_SAMPLE            (1 <<  1)
#घोषणा SVGA3D_DXFMT_COLOR_RENDERTARGET       (1 <<  2)
#घोषणा SVGA3D_DXFMT_DEPTH_RENDERTARGET       (1 <<  3)
#घोषणा SVGA3D_DXFMT_BLENDABLE                (1 <<  4)
#घोषणा SVGA3D_DXFMT_MIPS                     (1 <<  5)
#घोषणा SVGA3D_DXFMT_ARRAY                    (1 <<  6)
#घोषणा SVGA3D_DXFMT_VOLUME                   (1 <<  7)
#घोषणा SVGA3D_DXFMT_DX_VERTEX_BUFFER         (1 <<  8)
#घोषणा SVGA3D_DXFMT_MULTISAMPLE              (1 <<  9)
#घोषणा SVGA3D_DXFMT_MAX                      (1 << 10)

प्रकार जोड़ अणु
   SVGA3dBool b;
   uपूर्णांक32 u;
   पूर्णांक32 i;
   भग्न f;
पूर्ण SVGA3dDevCapResult;

#पूर्ण_अगर /* _SVGA3D_DEVCAPS_H_ */
