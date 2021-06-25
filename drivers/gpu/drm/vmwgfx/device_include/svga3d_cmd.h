<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**********************************************************
 * Copyright 1998-2020 VMware, Inc.
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
 * svga3d_cmd.h --
 *
 *       SVGA 3d hardware cmd definitions
 */

#अगर_अघोषित _SVGA3D_CMD_H_
#घोषणा _SVGA3D_CMD_H_

#घोषणा INCLUDE_ALLOW_MODULE
#घोषणा INCLUDE_ALLOW_USERLEVEL
#घोषणा INCLUDE_ALLOW_VMCORE

#समावेश "includeCheck.h"
#समावेश "svga3d_types.h"

/*
 * Identअगरiers क्रम commands in the command FIFO.
 *
 * IDs between 1000 and 1039 (inclusive) were used by obsolete versions of
 * the SVGA3D protocol and reमुख्य reserved; they should not be used in the
 * future.
 *
 * IDs between 1040 and 2999 (inclusive) are available क्रम use by the
 * current SVGA3D protocol.
 *
 * FIFO clients other than SVGA3D should stay below 1000, or at 3000
 * and up.
 */

प्रकार क्रमागत अणु
   SVGA_3D_CMD_LEGACY_BASE                                = 1000,
   SVGA_3D_CMD_BASE                                       = 1040,

   SVGA_3D_CMD_SURFACE_DEFINE                             = 1040,
   SVGA_3D_CMD_SURFACE_DESTROY                            = 1041,
   SVGA_3D_CMD_SURFACE_COPY                               = 1042,
   SVGA_3D_CMD_SURFACE_STRETCHBLT                         = 1043,
   SVGA_3D_CMD_SURFACE_DMA                                = 1044,
   SVGA_3D_CMD_CONTEXT_DEFINE                             = 1045,
   SVGA_3D_CMD_CONTEXT_DESTROY                            = 1046,
   SVGA_3D_CMD_SETTRANSFORM                               = 1047,
   SVGA_3D_CMD_SETZRANGE                                  = 1048,
   SVGA_3D_CMD_SETRENDERSTATE                             = 1049,
   SVGA_3D_CMD_SETRENDERTARGET                            = 1050,
   SVGA_3D_CMD_SETTEXTURESTATE                            = 1051,
   SVGA_3D_CMD_SETMATERIAL                                = 1052,
   SVGA_3D_CMD_SETLIGHTDATA                               = 1053,
   SVGA_3D_CMD_SETLIGHTENABLED                            = 1054,
   SVGA_3D_CMD_SETVIEWPORT                                = 1055,
   SVGA_3D_CMD_SETCLIPPLANE                               = 1056,
   SVGA_3D_CMD_CLEAR                                      = 1057,
   SVGA_3D_CMD_PRESENT                                    = 1058,
   SVGA_3D_CMD_SHADER_DEFINE                              = 1059,
   SVGA_3D_CMD_SHADER_DESTROY                             = 1060,
   SVGA_3D_CMD_SET_SHADER                                 = 1061,
   SVGA_3D_CMD_SET_SHADER_CONST                           = 1062,
   SVGA_3D_CMD_DRAW_PRIMITIVES                            = 1063,
   SVGA_3D_CMD_SETSCISSORRECT                             = 1064,
   SVGA_3D_CMD_BEGIN_QUERY                                = 1065,
   SVGA_3D_CMD_END_QUERY                                  = 1066,
   SVGA_3D_CMD_WAIT_FOR_QUERY                             = 1067,
   SVGA_3D_CMD_PRESENT_READBACK                           = 1068,
   SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN                     = 1069,
   SVGA_3D_CMD_SURFACE_DEFINE_V2                          = 1070,
   SVGA_3D_CMD_GENERATE_MIPMAPS                           = 1071,
   SVGA_3D_CMD_DEAD4                                      = 1072,
   SVGA_3D_CMD_DEAD5                                      = 1073,
   SVGA_3D_CMD_DEAD6                                      = 1074,
   SVGA_3D_CMD_DEAD7                                      = 1075,
   SVGA_3D_CMD_DEAD8                                      = 1076,
   SVGA_3D_CMD_DEAD9                                      = 1077,
   SVGA_3D_CMD_DEAD10                                     = 1078,
   SVGA_3D_CMD_DEAD11                                     = 1079,
   SVGA_3D_CMD_ACTIVATE_SURFACE                           = 1080,
   SVGA_3D_CMD_DEACTIVATE_SURFACE                         = 1081,
   SVGA_3D_CMD_SCREEN_DMA                                 = 1082,
   SVGA_3D_CMD_DEAD1                                      = 1083,
   SVGA_3D_CMD_DEAD2                                      = 1084,

   SVGA_3D_CMD_DEAD12                                     = 1085,
   SVGA_3D_CMD_DEAD13                                     = 1086,
   SVGA_3D_CMD_DEAD14                                     = 1087,
   SVGA_3D_CMD_DEAD15                                     = 1088,
   SVGA_3D_CMD_DEAD16                                     = 1089,
   SVGA_3D_CMD_DEAD17                                     = 1090,

   SVGA_3D_CMD_SET_OTABLE_BASE                            = 1091,
   SVGA_3D_CMD_READBACK_OTABLE                            = 1092,

   SVGA_3D_CMD_DEFINE_GB_MOB                              = 1093,
   SVGA_3D_CMD_DESTROY_GB_MOB                             = 1094,
   SVGA_3D_CMD_DEAD3                                      = 1095,
   SVGA_3D_CMD_UPDATE_GB_MOB_MAPPING                      = 1096,

   SVGA_3D_CMD_DEFINE_GB_SURFACE                          = 1097,
   SVGA_3D_CMD_DESTROY_GB_SURFACE                         = 1098,
   SVGA_3D_CMD_BIND_GB_SURFACE                            = 1099,
   SVGA_3D_CMD_COND_BIND_GB_SURFACE                       = 1100,
   SVGA_3D_CMD_UPDATE_GB_IMAGE                            = 1101,
   SVGA_3D_CMD_UPDATE_GB_SURFACE                          = 1102,
   SVGA_3D_CMD_READBACK_GB_IMAGE                          = 1103,
   SVGA_3D_CMD_READBACK_GB_SURFACE                        = 1104,
   SVGA_3D_CMD_INVALIDATE_GB_IMAGE                        = 1105,
   SVGA_3D_CMD_INVALIDATE_GB_SURFACE                      = 1106,

   SVGA_3D_CMD_DEFINE_GB_CONTEXT                          = 1107,
   SVGA_3D_CMD_DESTROY_GB_CONTEXT                         = 1108,
   SVGA_3D_CMD_BIND_GB_CONTEXT                            = 1109,
   SVGA_3D_CMD_READBACK_GB_CONTEXT                        = 1110,
   SVGA_3D_CMD_INVALIDATE_GB_CONTEXT                      = 1111,

   SVGA_3D_CMD_DEFINE_GB_SHADER                           = 1112,
   SVGA_3D_CMD_DESTROY_GB_SHADER                          = 1113,
   SVGA_3D_CMD_BIND_GB_SHADER                             = 1114,

   SVGA_3D_CMD_SET_OTABLE_BASE64                          = 1115,

   SVGA_3D_CMD_BEGIN_GB_QUERY                             = 1116,
   SVGA_3D_CMD_END_GB_QUERY                               = 1117,
   SVGA_3D_CMD_WAIT_FOR_GB_QUERY                          = 1118,

   SVGA_3D_CMD_NOP                                        = 1119,

   SVGA_3D_CMD_ENABLE_GART                                = 1120,
   SVGA_3D_CMD_DISABLE_GART                               = 1121,
   SVGA_3D_CMD_MAP_MOB_INTO_GART                          = 1122,
   SVGA_3D_CMD_UNMAP_GART_RANGE                           = 1123,

   SVGA_3D_CMD_DEFINE_GB_SCREENTARGET                     = 1124,
   SVGA_3D_CMD_DESTROY_GB_SCREENTARGET                    = 1125,
   SVGA_3D_CMD_BIND_GB_SCREENTARGET                       = 1126,
   SVGA_3D_CMD_UPDATE_GB_SCREENTARGET                     = 1127,

   SVGA_3D_CMD_READBACK_GB_IMAGE_PARTIAL                  = 1128,
   SVGA_3D_CMD_INVALIDATE_GB_IMAGE_PARTIAL                = 1129,

   SVGA_3D_CMD_SET_GB_SHADERCONSTS_INLINE                 = 1130,

   SVGA_3D_CMD_GB_SCREEN_DMA                              = 1131,
   SVGA_3D_CMD_BIND_GB_SURFACE_WITH_PITCH                 = 1132,
   SVGA_3D_CMD_GB_MOB_FENCE                               = 1133,
   SVGA_3D_CMD_DEFINE_GB_SURFACE_V2                       = 1134,
   SVGA_3D_CMD_DEFINE_GB_MOB64                            = 1135,
   SVGA_3D_CMD_REDEFINE_GB_MOB64                          = 1136,
   SVGA_3D_CMD_NOP_ERROR                                  = 1137,

   SVGA_3D_CMD_SET_VERTEX_STREAMS                         = 1138,
   SVGA_3D_CMD_SET_VERTEX_DECLS                           = 1139,
   SVGA_3D_CMD_SET_VERTEX_DIVISORS                        = 1140,
   SVGA_3D_CMD_DRAW                                       = 1141,
   SVGA_3D_CMD_DRAW_INDEXED                               = 1142,

   /*
    * DX10 Commands
    */
   SVGA_3D_CMD_DX_MIN                                     = 1143,
   SVGA_3D_CMD_DX_DEFINE_CONTEXT                          = 1143,
   SVGA_3D_CMD_DX_DESTROY_CONTEXT                         = 1144,
   SVGA_3D_CMD_DX_BIND_CONTEXT                            = 1145,
   SVGA_3D_CMD_DX_READBACK_CONTEXT                        = 1146,
   SVGA_3D_CMD_DX_INVALIDATE_CONTEXT                      = 1147,
   SVGA_3D_CMD_DX_SET_SINGLE_CONSTANT_BUFFER              = 1148,
   SVGA_3D_CMD_DX_SET_SHADER_RESOURCES                    = 1149,
   SVGA_3D_CMD_DX_SET_SHADER                              = 1150,
   SVGA_3D_CMD_DX_SET_SAMPLERS                            = 1151,
   SVGA_3D_CMD_DX_DRAW                                    = 1152,
   SVGA_3D_CMD_DX_DRAW_INDEXED                            = 1153,
   SVGA_3D_CMD_DX_DRAW_INSTANCED                          = 1154,
   SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED                  = 1155,
   SVGA_3D_CMD_DX_DRAW_AUTO                               = 1156,
   SVGA_3D_CMD_DX_SET_INPUT_LAYOUT                        = 1157,
   SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS                      = 1158,
   SVGA_3D_CMD_DX_SET_INDEX_BUFFER                        = 1159,
   SVGA_3D_CMD_DX_SET_TOPOLOGY                            = 1160,
   SVGA_3D_CMD_DX_SET_RENDERTARGETS                       = 1161,
   SVGA_3D_CMD_DX_SET_BLEND_STATE                         = 1162,
   SVGA_3D_CMD_DX_SET_DEPTHSTENCIL_STATE                  = 1163,
   SVGA_3D_CMD_DX_SET_RASTERIZER_STATE                    = 1164,
   SVGA_3D_CMD_DX_DEFINE_QUERY                            = 1165,
   SVGA_3D_CMD_DX_DESTROY_QUERY                           = 1166,
   SVGA_3D_CMD_DX_BIND_QUERY                              = 1167,
   SVGA_3D_CMD_DX_SET_QUERY_OFFSET                        = 1168,
   SVGA_3D_CMD_DX_BEGIN_QUERY                             = 1169,
   SVGA_3D_CMD_DX_END_QUERY                               = 1170,
   SVGA_3D_CMD_DX_READBACK_QUERY                          = 1171,
   SVGA_3D_CMD_DX_SET_PREDICATION                         = 1172,
   SVGA_3D_CMD_DX_SET_SOTARGETS                           = 1173,
   SVGA_3D_CMD_DX_SET_VIEWPORTS                           = 1174,
   SVGA_3D_CMD_DX_SET_SCISSORRECTS                        = 1175,
   SVGA_3D_CMD_DX_CLEAR_RENDERTARGET_VIEW                 = 1176,
   SVGA_3D_CMD_DX_CLEAR_DEPTHSTENCIL_VIEW                 = 1177,
   SVGA_3D_CMD_DX_PRED_COPY_REGION                        = 1178,
   SVGA_3D_CMD_DX_PRED_COPY                               = 1179,
   SVGA_3D_CMD_DX_PRESENTBLT                              = 1180,
   SVGA_3D_CMD_DX_GENMIPS                                 = 1181,
   SVGA_3D_CMD_DX_UPDATE_SUBRESOURCE                      = 1182,
   SVGA_3D_CMD_DX_READBACK_SUBRESOURCE                    = 1183,
   SVGA_3D_CMD_DX_INVALIDATE_SUBRESOURCE                  = 1184,
   SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW              = 1185,
   SVGA_3D_CMD_DX_DESTROY_SHADERRESOURCE_VIEW             = 1186,
   SVGA_3D_CMD_DX_DEFINE_RENDERTARGET_VIEW                = 1187,
   SVGA_3D_CMD_DX_DESTROY_RENDERTARGET_VIEW               = 1188,
   SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW                = 1189,
   SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_VIEW               = 1190,
   SVGA_3D_CMD_DX_DEFINE_ELEMENTLAYOUT                    = 1191,
   SVGA_3D_CMD_DX_DESTROY_ELEMENTLAYOUT                   = 1192,
   SVGA_3D_CMD_DX_DEFINE_BLEND_STATE                      = 1193,
   SVGA_3D_CMD_DX_DESTROY_BLEND_STATE                     = 1194,
   SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_STATE               = 1195,
   SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_STATE              = 1196,
   SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE                 = 1197,
   SVGA_3D_CMD_DX_DESTROY_RASTERIZER_STATE                = 1198,
   SVGA_3D_CMD_DX_DEFINE_SAMPLER_STATE                    = 1199,
   SVGA_3D_CMD_DX_DESTROY_SAMPLER_STATE                   = 1200,
   SVGA_3D_CMD_DX_DEFINE_SHADER                           = 1201,
   SVGA_3D_CMD_DX_DESTROY_SHADER                          = 1202,
   SVGA_3D_CMD_DX_BIND_SHADER                             = 1203,
   SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT                     = 1204,
   SVGA_3D_CMD_DX_DESTROY_STREAMOUTPUT                    = 1205,
   SVGA_3D_CMD_DX_SET_STREAMOUTPUT                        = 1206,
   SVGA_3D_CMD_DX_SET_COTABLE                             = 1207,
   SVGA_3D_CMD_DX_READBACK_COTABLE                        = 1208,
   SVGA_3D_CMD_DX_BUFFER_COPY                             = 1209,
   SVGA_3D_CMD_DX_TRANSFER_FROM_BUFFER                    = 1210,
   SVGA_3D_CMD_DX_SURFACE_COPY_AND_READBACK               = 1211,
   SVGA_3D_CMD_DX_MOVE_QUERY                              = 1212,
   SVGA_3D_CMD_DX_BIND_ALL_QUERY                          = 1213,
   SVGA_3D_CMD_DX_READBACK_ALL_QUERY                      = 1214,
   SVGA_3D_CMD_DX_PRED_TRANSFER_FROM_BUFFER               = 1215,
   SVGA_3D_CMD_DX_MOB_FENCE_64                            = 1216,
   SVGA_3D_CMD_DX_BIND_ALL_SHADER                         = 1217,
   SVGA_3D_CMD_DX_HINT                                    = 1218,
   SVGA_3D_CMD_DX_BUFFER_UPDATE                           = 1219,
   SVGA_3D_CMD_DX_SET_VS_CONSTANT_BUFFER_OFFSET           = 1220,
   SVGA_3D_CMD_DX_SET_PS_CONSTANT_BUFFER_OFFSET           = 1221,
   SVGA_3D_CMD_DX_SET_GS_CONSTANT_BUFFER_OFFSET           = 1222,
   SVGA_3D_CMD_DX_SET_HS_CONSTANT_BUFFER_OFFSET           = 1223,
   SVGA_3D_CMD_DX_SET_DS_CONSTANT_BUFFER_OFFSET           = 1224,
   SVGA_3D_CMD_DX_SET_CS_CONSTANT_BUFFER_OFFSET           = 1225,

   SVGA_3D_CMD_DX_COND_BIND_ALL_SHADER                    = 1226,
   SVGA_3D_CMD_DX_MAX                                     = 1227,

   SVGA_3D_CMD_SCREEN_COPY                                = 1227,

   SVGA_3D_CMD_RESERVED1                                  = 1228,
   SVGA_3D_CMD_RESERVED2                                  = 1229,
   SVGA_3D_CMD_RESERVED3                                  = 1230,
   SVGA_3D_CMD_RESERVED4                                  = 1231,
   SVGA_3D_CMD_RESERVED5                                  = 1232,
   SVGA_3D_CMD_RESERVED6                                  = 1233,
   SVGA_3D_CMD_RESERVED7                                  = 1234,
   SVGA_3D_CMD_RESERVED8                                  = 1235,

   SVGA_3D_CMD_GROW_OTABLE                                = 1236,
   SVGA_3D_CMD_DX_GROW_COTABLE                            = 1237,
   SVGA_3D_CMD_INTRA_SURFACE_COPY                         = 1238,

   SVGA_3D_CMD_DEFINE_GB_SURFACE_V3                       = 1239,

   SVGA_3D_CMD_DX_RESOLVE_COPY                            = 1240,
   SVGA_3D_CMD_DX_PRED_RESOLVE_COPY                       = 1241,
   SVGA_3D_CMD_DX_PRED_CONVERT_REGION                     = 1242,
   SVGA_3D_CMD_DX_PRED_CONVERT                            = 1243,
   SVGA_3D_CMD_WHOLE_SURFACE_COPY                         = 1244,

   SVGA_3D_CMD_DX_DEFINE_UA_VIEW                          = 1245,
   SVGA_3D_CMD_DX_DESTROY_UA_VIEW                         = 1246,
   SVGA_3D_CMD_DX_CLEAR_UA_VIEW_UINT                      = 1247,
   SVGA_3D_CMD_DX_CLEAR_UA_VIEW_FLOAT                     = 1248,
   SVGA_3D_CMD_DX_COPY_STRUCTURE_COUNT                    = 1249,
   SVGA_3D_CMD_DX_SET_UA_VIEWS                            = 1250,

   SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED_INसूचीECT         = 1251,
   SVGA_3D_CMD_DX_DRAW_INSTANCED_INसूचीECT                 = 1252,
   SVGA_3D_CMD_DX_DISPATCH                                = 1253,
   SVGA_3D_CMD_DX_DISPATCH_INसूचीECT                       = 1254,

   SVGA_3D_CMD_WRITE_ZERO_SURFACE                         = 1255,
   SVGA_3D_CMD_HINT_ZERO_SURFACE                          = 1256,
   SVGA_3D_CMD_DX_TRANSFER_TO_BUFFER                      = 1257,
   SVGA_3D_CMD_DX_SET_STRUCTURE_COUNT                     = 1258,

   SVGA_3D_CMD_LOGICOPS_BITBLT                            = 1259,
   SVGA_3D_CMD_LOGICOPS_TRANSBLT                          = 1260,
   SVGA_3D_CMD_LOGICOPS_STRETCHBLT                        = 1261,
   SVGA_3D_CMD_LOGICOPS_COLORFILL                         = 1262,
   SVGA_3D_CMD_LOGICOPS_ALPHABLEND                        = 1263,
   SVGA_3D_CMD_LOGICOPS_CLEARTYPEBLEND                    = 1264,

   SVGA_3D_CMD_RESERVED2_1                                = 1265,

   SVGA_3D_CMD_RESERVED2_2                                = 1266,
   SVGA_3D_CMD_DEFINE_GB_SURFACE_V4                       = 1267,
   SVGA_3D_CMD_DX_SET_CS_UA_VIEWS                         = 1268,
   SVGA_3D_CMD_DX_SET_MIN_LOD                             = 1269,
   SVGA_3D_CMD_RESERVED2_3                                = 1270,
   SVGA_3D_CMD_RESERVED2_4                                = 1271,
   SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW_V2             = 1272,
   SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT_WITH_MOB            = 1273,
   SVGA_3D_CMD_DX_SET_SHADER_IFACE                        = 1274,
   SVGA_3D_CMD_DX_BIND_STREAMOUTPUT                       = 1275,
   SVGA_3D_CMD_SURFACE_STRETCHBLT_NON_MS_TO_MS            = 1276,
   SVGA_3D_CMD_DX_BIND_SHADER_IFACE                       = 1277,

   SVGA_3D_CMD_MAX                                        = 1278,
   SVGA_3D_CMD_FUTURE_MAX                                 = 3000
पूर्ण SVGAFअगरo3dCmdId;

#घोषणा SVGA_NUM_3D_CMD (SVGA_3D_CMD_MAX - SVGA_3D_CMD_BASE)

/*
 * FIFO command क्रमmat definitions:
 */

/*
 * The data size header following cmdNum क्रम every 3d command
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               id;
   uपूर्णांक32               size;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdHeader;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               numMipLevels;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dSurfaceFace;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32                      sid;
   SVGA3dSurface1Flags         surfaceFlags;
   SVGA3dSurfaceFormat         क्रमmat;

   /*
    * If surfaceFlags has SVGA3D_SURFACE_CUBEMAP bit set, all SVGA3dSurfaceFace
    * काष्ठाures must have the same value of numMipLevels field.
    * Otherwise, all but the first SVGA3dSurfaceFace काष्ठाures must have the
    * numMipLevels set to 0.
    */
   SVGA3dSurfaceFace           face[SVGA3D_MAX_SURFACE_FACES];

   /*
    * Followed by an SVGA3dSize काष्ठाure क्रम each mip level in each face.
    *
    * A note on surface sizes: Sizes are always specअगरied in pixels,
    * even अगर the true surface size is not a multiple of the minimum
    * block size of the surface's क्रमmat. For example, a 3x3x1 DXT1
    * compressed texture would actually be stored as a 4x4x1 image in
    * memory.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineSurface;       /* SVGA_3D_CMD_SURFACE_DEFINE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32                      sid;
   SVGA3dSurface1Flags         surfaceFlags;
   SVGA3dSurfaceFormat         क्रमmat;

   /*
    * If surfaceFlags has SVGA3D_SURFACE_CUBEMAP bit set, all SVGA3dSurfaceFace
    * काष्ठाures must have the same value of numMipLevels field.
    * Otherwise, all but the first SVGA3dSurfaceFace काष्ठाures must have the
    * numMipLevels set to 0.
    */
   SVGA3dSurfaceFace           face[SVGA3D_MAX_SURFACE_FACES];
   uपूर्णांक32                      multisampleCount;
   SVGA3dTextureFilter         स्वतःgenFilter;

   /*
    * Followed by an SVGA3dSize काष्ठाure क्रम each mip level in each face.
    *
    * A note on surface sizes: Sizes are always specअगरied in pixels,
    * even अगर the true surface size is not a multiple of the minimum
    * block size of the surface's क्रमmat. For example, a 3x3x1 DXT1
    * compressed texture would actually be stored as a 4x4x1 image in
    * memory.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineSurface_v2;     /* SVGA_3D_CMD_SURFACE_DEFINE_V2 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroySurface;      /* SVGA_3D_CMD_SURFACE_DESTROY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineContext;       /* SVGA_3D_CMD_CONTEXT_DEFINE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroyContext;      /* SVGA_3D_CMD_CONTEXT_DESTROY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dClearFlag      clearFlag;
   uपूर्णांक32               color;
   भग्न                depth;
   uपूर्णांक32               stencil;
   /* Followed by variable number of SVGA3dRect काष्ठाures */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdClear;               /* SVGA_3D_CMD_CLEAR */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dLightType      type;
   SVGA3dBool           inWorldSpace;
   भग्न                dअगरfuse[4];
   भग्न                specular[4];
   भग्न                ambient[4];
   भग्न                position[4];
   भग्न                direction[4];
   भग्न                range;
   भग्न                falloff;
   भग्न                attenuation0;
   भग्न                attenuation1;
   भग्न                attenuation2;
   भग्न                theta;
   भग्न                phi;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dLightData;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               sid;
   /* Followed by variable number of SVGA3dCopyRect काष्ठाures */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdPresent;             /* SVGA_3D_CMD_PRESENT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dRenderStateName   state;
   जोड़ अणु
      uपूर्णांक32               uपूर्णांकValue;
      भग्न                भग्नValue;
   पूर्ण;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dRenderState;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   /* Followed by variable number of SVGA3dRenderState काष्ठाures */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetRenderState;      /* SVGA_3D_CMD_SETRENDERSTATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32                 cid;
   SVGA3dRenderTargetType type;
   SVGA3dSurfaceImageId   target;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetRenderTarget;     /* SVGA_3D_CMD_SETRENDERTARGET */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceImageId  src;
   SVGA3dSurfaceImageId  dest;
   /* Followed by variable number of SVGA3dCopyBox काष्ठाures */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSurfaceCopy;               /* SVGA_3D_CMD_SURFACE_COPY */

/*
 * Perक्रमm a surface copy within the same image.
 * The src/dest boxes are allowed to overlap.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceImageId  surface;
   SVGA3dCopyBox box;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdIntraSurfaceCopy;               /* SVGA_3D_CMD_INTRA_SURFACE_COPY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 srcSid;
   uपूर्णांक32 destSid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdWholeSurfaceCopy;               /* SVGA_3D_CMD_WHOLE_SURFACE_COPY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceImageId  src;
   SVGA3dSurfaceImageId  dest;
   SVGA3dBox boxSrc;
   SVGA3dBox boxDest;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSurfaceStretchBltNonMSToMS;
/* SVGA_3D_CMD_SURFACE_STRETCHBLT_NON_MS_TO_MS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceImageId  src;
   SVGA3dSurfaceImageId  dest;
   SVGA3dBox             boxSrc;
   SVGA3dBox             boxDest;
   SVGA3dStretchBltMode  mode;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSurfaceStretchBlt;         /* SVGA_3D_CMD_SURFACE_STRETCHBLT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   /*
    * If the discard flag is present in a surface DMA operation, the host may
    * discard the contents of the current mipmap level and face of the target
    * surface beक्रमe applying the surface DMA contents.
    */
   uपूर्णांक32 discard : 1;

   /*
    * If the unsynchronized flag is present, the host may perक्रमm this upload
    * without syncing to pending पढ़ोs on this surface.
    */
   uपूर्णांक32 unsynchronized : 1;

   /*
    * Guests *MUST* set the reserved bits to 0 beक्रमe submitting the command
    * suffix as future flags may occupy these bits.
    */
   uपूर्णांक32 reserved : 30;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dSurfaceDMAFlags;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAGuestImage guest;
   SVGA3dSurfaceImageId host;
   SVGA3dTransferType transfer;

   /*
    * Followed by variable number of SVGA3dCopyBox काष्ठाures. For consistency
    * in all clipping logic and coordinate translation, we define the
    * "source" in each copyBox as the guest image and the
    * "destination" as the host image, regardless of transfer
    * direction.
    *
    * For efficiency, the SVGA3D device is मुक्त to copy more data than
    * specअगरied. For example, it may round copy boxes outwards such
    * that they lie on particular alignment boundaries.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSurfaceDMA;                /* SVGA_3D_CMD_SURFACE_DMA */

/*
 * SVGA3dCmdSurfaceDMASuffix --
 *
 *    This is a command suffix that will appear after a SurfaceDMA command in
 *    the FIFO.  It contains some extra inक्रमmation that hosts may use to
 *    optimize perक्रमmance or protect the guest.  This suffix exists to preserve
 *    backwards compatibility जबतक also allowing क्रम new functionality to be
 *    implemented.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 suffixSize;

   /*
    * The maximum offset is used to determine the maximum offset from the
    * guestPtr base address that will be accessed or written to during this
    * surfaceDMA.  If the suffix is supported, the host will respect this
    * boundary जबतक perक्रमming surface DMAs.
    *
    * Defaults to MAX_UINT32
    */
   uपूर्णांक32 maximumOffset;

   /*
    * A set of flags that describes optimizations that the host may perक्रमm
    * जबतक perक्रमming this surface DMA operation.  The guest should never rely
    * on behaviour that is dअगरferent when these flags are set क्रम correctness.
    *
    * Defaults to 0
    */
   SVGA3dSurfaceDMAFlags flags;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSurfaceDMASuffix;

/*
 * SVGA_3D_CMD_DRAW_PRIMITIVES --
 *
 *   This command is the SVGA3D device's generic drawing entry poपूर्णांक.
 *   It can draw multiple ranges of primitives, optionally using an
 *   index buffer, using an arbitrary collection of vertex buffers.
 *
 *   Each SVGA3dVertexDecl defines a distinct vertex array to bind
 *   during this draw call. The declarations specअगरy which surface
 *   the vertex data lives in, what that vertex data is used क्रम,
 *   and how to पूर्णांकerpret it.
 *
 *   Each SVGA3dPrimitiveRange defines a collection of primitives
 *   to render using the same vertex arrays. An index buffer is
 *   optional.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   /*
    * A range hपूर्णांक is an optional specअगरication क्रम the range of indices
    * in an SVGA3dArray that will be used. If 'last' is zero, it is assumed
    * that the entire array will be used.
    *
    * These are only hपूर्णांकs. The SVGA3D device may use them क्रम
    * perक्रमmance optimization अगर possible, but it's also allowed to
    * ignore these values.
    */
   uपूर्णांक32               first;
   uपूर्णांक32               last;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dArrayRangeHपूर्णांक;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   /*
    * Define the origin and shape of a vertex or index array. Both
    * 'offset' and 'stride' are in bytes. The provided surface will be
    * reपूर्णांकerpreted as a flat array of bytes in the same क्रमmat used
    * by surface DMA operations. To aव्योम unnecessary conversions, the
    * surface should be created with the SVGA3D_BUFFER क्रमmat.
    *
    * Index 0 in the array starts 'offset' bytes पूर्णांकo the surface.
    * Index 1 begins at byte 'offset + stride', etc. Array indices may
    * not be negative.
    */
   uपूर्णांक32               surfaceId;
   uपूर्णांक32               offset;
   uपूर्णांक32               stride;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dArray;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   /*
    * Describe a vertex array's data type, and define how it is to be
    * used by the fixed function pipeline or the vertex shader. It
    * isn't useful to have two VertexDecls with the same
    * VertexArrayIdentity in one draw call.
    */
   SVGA3dDeclType       type;
   SVGA3dDeclMethod     method;
   SVGA3dDeclUsage      usage;
   uपूर्णांक32               usageIndex;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dVertexArrayIdentity;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dVertexDecl अणु
   SVGA3dVertexArrayIdentity  identity;
   SVGA3dArray                array;
   SVGA3dArrayRangeHपूर्णांक       rangeHपूर्णांक;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dVertexDecl;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dPrimitiveRange अणु
   /*
    * Define a group of primitives to render, from sequential indices.
    *
    * The value of 'primitiveType' and 'primitiveCount' imply the
    * total number of vertices that will be rendered.
    */
   SVGA3dPrimitiveType  primType;
   uपूर्णांक32               primitiveCount;

   /*
    * Optional index buffer. If indexArray.surfaceId is
    * SVGA3D_INVALID_ID, we render without an index buffer. Rendering
    * without an index buffer is identical to rendering with an index
    * buffer containing the sequence [0, 1, 2, 3, ...].
    *
    * If an index buffer is in use, indexWidth specअगरies the width in
    * bytes of each index value. It must be less than or equal to
    * indexArray.stride.
    *
    * (Currently, the SVGA3D device requires index buffers to be tightly
    * packed. In other words, indexWidth == indexArray.stride)
    */
   SVGA3dArray          indexArray;
   uपूर्णांक32               indexWidth;

   /*
    * Optional index bias. This number is added to all indices from
    * indexArray beक्रमe they are used as vertex array indices. This
    * can be used in multiple ways:
    *
    *  - When not using an indexArray, this bias can be used to
    *    specअगरy where in the vertex arrays to begin rendering.
    *
    *  - A positive number here is equivalent to increasing the
    *    offset in each vertex array.
    *
    *  - A negative number can be used to render using a small
    *    vertex array and an index buffer that contains large
    *    values. This may be used by some applications that
    *    crop a vertex buffer without modअगरying their index
    *    buffer.
    *
    * Note that rendering with a negative bias value may be slower and
    * use more memory than rendering with a positive or zero bias.
    */
   पूर्णांक32                indexBias;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dPrimitiveRange;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   uपूर्णांक32               numVertexDecls;
   uपूर्णांक32               numRanges;

   /*
    * There are two variable size arrays after the
    * SVGA3dCmdDrawPrimitives काष्ठाure. In order,
    * they are:
    *
    * 1. SVGA3dVertexDecl, quantity 'numVertexDecls', but no more than
    *    SVGA3D_MAX_VERTEX_ARRAYS;
    * 2. SVGA3dPrimitiveRange, quantity 'numRanges', but no more than
    *    SVGA3D_MAX_DRAW_PRIMITIVE_RANGES;
    * 3. Optionally, SVGA3dVertexDivisor, quantity 'numVertexDecls' (contains
    *    the frequency भागisor क्रम the corresponding vertex decl).
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDrawPrimitives;      /* SVGA_3D_CMD_DRAWPRIMITIVES */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 cid;

   uपूर्णांक32 primitiveCount;        /* How many primitives to render */
   uपूर्णांक32 startVertexLocation;   /* Which vertex करो we start rendering at. */

   uपूर्णांक8 primitiveType;          /* SVGA3dPrimitiveType */
   uपूर्णांक8 padding[3];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDraw;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 cid;

   uपूर्णांक8 primitiveType;       /* SVGA3dPrimitiveType */

   uपूर्णांक32 indexBufferSid;     /* Valid index buffer sid. */
   uपूर्णांक32 indexBufferOffset;  /* Byte offset पूर्णांकo the vertex buffer, almost */
                              /* always 0 क्रम pre SM guests, non-zero क्रम OpenGL */
                              /* guests.  We can't represent non-multiple of */
                              /* stride offsets in D3D9Renderer... */
   uपूर्णांक8 indexBufferStride;   /* Allowable values = 1, 2, or 4 */

   पूर्णांक32 baseVertexLocation;  /* Bias applied to the index when selecting a */
                              /* vertex from the streams, may be negative */

   uपूर्णांक32 primitiveCount;     /* How many primitives to render */
   uपूर्णांक32 pad0;
   uपूर्णांक16 pad1;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDrawIndexed;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   /*
    * Describe a vertex array's data type, and define how it is to be
    * used by the fixed function pipeline or the vertex shader. It
    * isn't useful to have two VertexDecls with the same
    * VertexArrayIdentity in one draw call.
    */
   uपूर्णांक16 streamOffset;
   uपूर्णांक8 stream;
   uपूर्णांक8 type;          /* SVGA3dDeclType */
   uपूर्णांक8 method;        /* SVGA3dDeclMethod */
   uपूर्णांक8 usage;         /* SVGA3dDeclUsage */
   uपूर्णांक8 usageIndex;
   uपूर्णांक8 padding;

पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dVertexElement;

/*
 * Should the vertex element respect the stream value?  The high bit of the
 * stream should be set to indicate that the stream should be respected.  If
 * the high bit is not set, the stream will be ignored and replaced by the index
 * of the position of the currently considered vertex element.
 *
 * All guests should set this bit and correctly specअगरy the stream going
 * क्रमward.
 */
#घोषणा SVGA3D_VERTEX_ELEMENT_RESPECT_STREAM (1 << 7)

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 cid;

   uपूर्णांक32 numElements;

   /*
    * Followed by numElements SVGA3dVertexElement काष्ठाures.
    *
    * If numElements < SVGA3D_MAX_VERTEX_ARRAYS, the reमुख्यing elements
    * are cleared and will not be used by following draws.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetVertexDecls;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 sid;
   uपूर्णांक32 stride;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dVertexStream;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 cid;

   uपूर्णांक32 numStreams;
   /*
    * Followed by numStream SVGA3dVertexStream काष्ठाures.
    *
    * If numStreams < SVGA3D_MAX_VERTEX_ARRAYS, the reमुख्यing streams
    * are cleared and will not be used by following draws.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetVertexStreams;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 cid;
   uपूर्णांक32 numDivisors;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetVertexDivisors;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32                   stage;
   SVGA3dTextureStateName   name;
   जोड़ अणु
      uपूर्णांक32                value;
      भग्न                 भग्नValue;
   पूर्ण;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dTextureState;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   /* Followed by variable number of SVGA3dTextureState काष्ठाures */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetTextureState;      /* SVGA_3D_CMD_SETTEXTURESTATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32                   cid;
   SVGA3dTransक्रमmType      type;
   भग्न                    matrix[16];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetTransक्रमm;          /* SVGA_3D_CMD_SETTRANSFORM */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   भग्न                min;
   भग्न                max;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dZRange;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dZRange         zRange;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetZRange;             /* SVGA_3D_CMD_SETZRANGE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   भग्न                dअगरfuse[4];
   भग्न                ambient[4];
   भग्न                specular[4];
   भग्न                emissive[4];
   भग्न                shininess;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dMaterial;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dFace           face;
   SVGA3dMaterial       material;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetMaterial;           /* SVGA_3D_CMD_SETMATERIAL */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   uपूर्णांक32               index;
   SVGA3dLightData      data;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetLightData;           /* SVGA_3D_CMD_SETLIGHTDATA */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   uपूर्णांक32               index;
   uपूर्णांक32               enabled;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetLightEnabled;      /* SVGA_3D_CMD_SETLIGHTENABLED */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dRect           rect;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetViewport;           /* SVGA_3D_CMD_SETVIEWPORT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dRect           rect;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetScissorRect;         /* SVGA_3D_CMD_SETSCISSORRECT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   uपूर्णांक32               index;
   भग्न                plane[4];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetClipPlane;           /* SVGA_3D_CMD_SETCLIPPLANE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   uपूर्णांक32               shid;
   SVGA3dShaderType     type;
   /* Followed by variable number of DWORDs क्रम shader bycode */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineShader;           /* SVGA_3D_CMD_SHADER_DEFINE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   uपूर्णांक32               shid;
   SVGA3dShaderType     type;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroyShader;         /* SVGA_3D_CMD_SHADER_DESTROY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32                  cid;
   uपूर्णांक32                  reg;     /* रेजिस्टर number */
   SVGA3dShaderType        type;
   SVGA3dShaderConstType   ctype;
   uपूर्णांक32                  values[4];

   /*
    * Followed by a variable number of additional values.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetShaderConst;        /* SVGA_3D_CMD_SET_SHADER_CONST */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dShaderType     type;
   uपूर्णांक32               shid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetShader;       /* SVGA_3D_CMD_SET_SHADER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dQueryType      type;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBeginQuery;           /* SVGA_3D_CMD_BEGIN_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dQueryType      type;
   SVGAGuestPtr         guestResult;   /* Poपूर्णांकs to an SVGA3dQueryResult काष्ठाure */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdEndQuery;                  /* SVGA_3D_CMD_END_QUERY */


/*
 * SVGA3D_CMD_WAIT_FOR_QUERY --
 *
 *    Will पढ़ो the SVGA3dQueryResult काष्ठाure poपूर्णांकed to by guestResult,
 *    and अगर the state member is set to anything अन्यथा than
 *    SVGA3D_QUERYSTATE_PENDING, this command will always be a no-op.
 *
 *    Otherwise, in addition to the query explicitly रुकोed क्रम,
 *    All queries with the same type and issued with the same cid, क्रम which
 *    an SVGA_3D_CMD_END_QUERY command has previously been sent, will
 *    be finished after execution of this command.
 *
 *    A query will be identअगरied by the gmrId and offset of the guestResult
 *    member. If the device can't find an SVGA_3D_CMD_END_QUERY that has
 *    been sent previously with an indentical gmrId and offset, it will
 *    effectively end all queries with an identical type issued with the
 *    same cid, and the SVGA3dQueryResult काष्ठाure poपूर्णांकed to by
 *    guestResult will not be written to. This property can be used to
 *    implement a query barrier क्रम a given cid and query type.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;        /* Same parameters passed to END_QUERY */
   SVGA3dQueryType      type;
   SVGAGuestPtr         guestResult;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdWaitForQuery;              /* SVGA_3D_CMD_WAIT_FOR_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               totalSize;    /* Set by guest beक्रमe query is ended. */
   SVGA3dQueryState     state;        /* Set by host or guest. See SVGA3dQueryState. */
   जोड़ अणु                            /* Set by host on निकास from PENDING state */
      uपूर्णांक32            result32;
      uपूर्णांक32            queryCookie; /* May be used to identअगरy which QueryGetData this
                                        result corresponds to. */
   पूर्ण;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dQueryResult;


/*
 * SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN --
 *
 *    This is a blit from an SVGA3D surface to a Screen Object.
 *    This blit must be directed at a specअगरic screen.
 *
 *    The blit copies from a rectangular region of an SVGA3D surface
 *    image to a rectangular region of a screen.
 *
 *    This command takes an optional variable-length list of clipping
 *    rectangles after the body of the command. If no rectangles are
 *    specअगरied, there is no clipping region. The entire destRect is
 *    drawn to. If one or more rectangles are included, they describe
 *    a clipping region. The clip rectangle coordinates are measured
 *    relative to the top-left corner of destRect.
 *
 *    The srcImage must be from mip=0 face=0.
 *
 *    This supports scaling अगर the src and dest are of dअगरferent sizes.
 *
 * Availability:
 *    SVGA_FIFO_CAP_SCREEN_OBJECT
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceImageId srcImage;
   SVGASignedRect       srcRect;
   uपूर्णांक32               destScreenId; /* Screen Object ID */
   SVGASignedRect       destRect;
   /* Clipping: zero or more SVGASignedRects follow */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBlitSurfaceToScreen;         /* SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               sid;
   SVGA3dTextureFilter  filter;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdGenerateMipmaps;             /* SVGA_3D_CMD_GENERATE_MIPMAPS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdActivateSurface;               /* SVGA_3D_CMD_ACTIVATE_SURFACE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDeactivateSurface;             /* SVGA_3D_CMD_DEACTIVATE_SURFACE */

/*
 * Screen DMA command
 *
 * Available with SVGA_FIFO_CAP_SCREEN_OBJECT_2.  The SVGA_CAP_3D device
 * cap bit is not required.
 *
 * - refBuffer and destBuffer are 32bit BGRX; refBuffer and destBuffer could
 *   be dअगरferent, but it is required that guest makes sure refBuffer has
 *   exactly the same contents that were written to when last समय screen DMA
 *   command is received by host.
 *
 * - changemap is generated by lib/blit, and it has the changes from last
 *   received screen DMA or more.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdScreenDMA अणु
   uपूर्णांक32 screenId;
   SVGAGuestImage refBuffer;
   SVGAGuestImage destBuffer;
   SVGAGuestImage changeMap;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdScreenDMA;        /* SVGA_3D_CMD_SCREEN_DMA */

/*
 * Logic ops
 */

#घोषणा SVGA3D_LOTRANSBLT_HONORALPHA     (0x01)
#घोषणा SVGA3D_LOSTRETCHBLT_MIRRORX      (0x01)
#घोषणा SVGA3D_LOSTRETCHBLT_MIRRORY      (0x02)
#घोषणा SVGA3D_LOALPHABLEND_SRCHASALPHA  (0x01)

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdLogicOpsBitBlt अणु
   /*
    * All LogicOps surfaces are one-level
    * surfaces so mipmap & face should always
    * be zero.
    */
   SVGA3dSurfaceImageId src;
   SVGA3dSurfaceImageId dst;
   SVGA3dLogicOp logicOp;
   SVGA3dLogicOpRop3 logicOpRop3;
   /* Followed by variable number of SVGA3dCopyBox काष्ठाures */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdLogicOpsBitBlt;   /* SVGA_3D_CMD_LOGICOPS_BITBLT */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdLogicOpsTransBlt अणु
   /*
    * All LogicOps surfaces are one-level
    * surfaces so mipmap & face should always
    * be zero.
    */
   SVGA3dSurfaceImageId src;
   SVGA3dSurfaceImageId dst;
   uपूर्णांक32 color;
   uपूर्णांक32 flags;
   SVGA3dBox srcBox;
   SVGA3dSignedBox dstBox;
   SVGA3dBox clipBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdLogicOpsTransBlt;   /* SVGA_3D_CMD_LOGICOPS_TRANSBLT */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdLogicOpsStretchBlt अणु
   /*
    * All LogicOps surfaces are one-level
    * surfaces so mipmap & face should always
    * be zero.
    */
   SVGA3dSurfaceImageId src;
   SVGA3dSurfaceImageId dst;
   uपूर्णांक16 mode;
   uपूर्णांक16 flags;
   SVGA3dBox srcBox;
   SVGA3dSignedBox dstBox;
   SVGA3dBox clipBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdLogicOpsStretchBlt;   /* SVGA_3D_CMD_LOGICOPS_STRETCHBLT */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdLogicOpsColorFill अणु
   /*
    * All LogicOps surfaces are one-level
    * surfaces so mipmap & face should always
    * be zero.
    */
   SVGA3dSurfaceImageId dst;
   uपूर्णांक32 color;
   SVGA3dLogicOp logicOp;
   SVGA3dLogicOpRop3 logicOpRop3;
   /* Followed by variable number of SVGA3dRect काष्ठाures. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdLogicOpsColorFill;   /* SVGA_3D_CMD_LOGICOPS_COLORFILL */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdLogicOpsAlphaBlend अणु
   /*
    * All LogicOps surfaces are one-level
    * surfaces so mipmap & face should always
    * be zero.
    */
   SVGA3dSurfaceImageId src;
   SVGA3dSurfaceImageId dst;
   uपूर्णांक32 alphaVal;
   uपूर्णांक32 flags;
   SVGA3dBox srcBox;
   SVGA3dSignedBox dstBox;
   SVGA3dBox clipBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdLogicOpsAlphaBlend;   /* SVGA_3D_CMD_LOGICOPS_ALPHABLEND */

#घोषणा SVGA3D_CLEARTYPE_INVALID_GAMMA_INDEX 0xFFFFFFFF

#घोषणा SVGA3D_CLEARTYPE_GAMMA_WIDTH  512
#घोषणा SVGA3D_CLEARTYPE_GAMMA_HEIGHT 16

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdLogicOpsClearTypeBlend अणु
   /*
    * All LogicOps surfaces are one-level
    * surfaces so mipmap & face should always
    * be zero.
    */
   SVGA3dSurfaceImageId पंचांगp;
   SVGA3dSurfaceImageId dst;
   SVGA3dSurfaceImageId gammaSurf;
   SVGA3dSurfaceImageId alphaSurf;
   uपूर्णांक32 gamma;
   uपूर्णांक32 color;
   uपूर्णांक32 color2;
   पूर्णांक32 alphaOffsetX;
   पूर्णांक32 alphaOffsetY;
   /* Followed by variable number of SVGA3dBox काष्ठाures */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdLogicOpsClearTypeBlend;   /* SVGA_3D_CMD_LOGICOPS_CLEARTYPEBLEND */


/*
 * Guest-backed objects definitions.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAMobFormat ptDepth;
   uपूर्णांक32 sizeInBytes;
   PPN64 base;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAOTableMobEntry;
#घोषणा SVGA3D_OTABLE_MOB_ENTRY_SIZE (माप(SVGAOTableMobEntry))

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dSurface1Flags surface1Flags;
   uपूर्णांक32 numMipLevels;
   uपूर्णांक32 multisampleCount;
   SVGA3dTextureFilter स्वतःgenFilter;
   SVGA3dSize size;
   SVGAMobId mobid;
   uपूर्णांक32 arraySize;
   uपूर्णांक32 mobPitch;
   SVGA3dSurface2Flags surface2Flags;
   uपूर्णांक8 multisamplePattern;
   uपूर्णांक8 qualityLevel;
   uपूर्णांक16 bufferByteStride;
   भग्न minLOD;
   uपूर्णांक32 pad0[2];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAOTableSurfaceEntry;
#घोषणा SVGA3D_OTABLE_SURFACE_ENTRY_SIZE (माप(SVGAOTableSurfaceEntry))

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 cid;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAOTableContextEntry;
#घोषणा SVGA3D_OTABLE_CONTEXT_ENTRY_SIZE (माप(SVGAOTableContextEntry))

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dShaderType type;
   uपूर्णांक32 sizeInBytes;
   uपूर्णांक32 offsetInBytes;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAOTableShaderEntry;
#घोषणा SVGA3D_OTABLE_SHADER_ENTRY_SIZE (माप(SVGAOTableShaderEntry))

#घोषणा SVGA_STFLAG_PRIMARY  (1 << 0)
#घोषणा SVGA_STFLAG_RESERVED (1 << 1) /* Added with cap SVGA_CAP_HP_CMD_QUEUE */
प्रकार uपूर्णांक32 SVGAScreenTargetFlags;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceImageId image;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   पूर्णांक32 xRoot;
   पूर्णांक32 yRoot;
   SVGAScreenTargetFlags flags;
   uपूर्णांक32 dpi;
   uपूर्णांक32 pad[7];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAOTableScreenTargetEntry;
#घोषणा SVGA3D_OTABLE_SCREEN_TARGET_ENTRY_SIZE \
	(माप(SVGAOTableScreenTargetEntry))

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   भग्न value[4];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dShaderConstFloat;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   पूर्णांक32 value[4];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dShaderConstInt;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 value;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dShaderConstBool;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक16 streamOffset;
   uपूर्णांक8 stream;
   uपूर्णांक8 type;
   uपूर्णांक8 methodUsage;
   uपूर्णांक8 usageIndex;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGBVertexElement;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 sid;
   uपूर्णांक16 stride;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGBVertexStream;
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dRect viewport;
   SVGA3dRect scissorRect;
   SVGA3dZRange zRange;

   SVGA3dSurfaceImageId renderTarमाला_लो[SVGA3D_RT_MAX];
   SVGAGBVertexElement decl1[4];

   uपूर्णांक32 renderStates[SVGA3D_RS_MAX];
   SVGAGBVertexElement decl2[18];
   uपूर्णांक32 pad0[2];

   काष्ठा अणु
      SVGA3dFace face;
      SVGA3dMaterial material;
   पूर्ण material;

   भग्न clipPlanes[SVGA3D_NUM_CLIPPLANES][4];
   भग्न matrices[SVGA3D_TRANSFORM_MAX][16];

   SVGA3dBool lightEnabled[SVGA3D_NUM_LIGHTS];
   SVGA3dLightData lightData[SVGA3D_NUM_LIGHTS];

   /*
    * Shaders currently bound
    */
   uपूर्णांक32 shaders[SVGA3D_NUM_SHADERTYPE_PREDX];
   SVGAGBVertexElement decl3[10];
   uपूर्णांक32 pad1[3];

   uपूर्णांक32 occQueryActive;
   uपूर्णांक32 occQueryValue;

   /*
    * Int/Bool Shader स्थिरants
    */
   SVGA3dShaderConstInt pShaderIValues[SVGA3D_CONSTINTREG_MAX];
   SVGA3dShaderConstInt vShaderIValues[SVGA3D_CONSTINTREG_MAX];
   uपूर्णांक16 pShaderBValues;
   uपूर्णांक16 vShaderBValues;


   SVGAGBVertexStream streams[SVGA3D_MAX_VERTEX_ARRAYS];
   SVGA3dVertexDivisor भागisors[SVGA3D_MAX_VERTEX_ARRAYS];
   uपूर्णांक32 numVertexDecls;
   uपूर्णांक32 numVertexStreams;
   uपूर्णांक32 numVertexDivisors;
   uपूर्णांक32 pad2[30];

   /*
    * Texture Stages
    *
    * SVGA3D_TS_INVALID through SVGA3D_TS_CONSTANT are in the
    * textureStages array.
    * SVGA3D_TS_COLOR_KEY is in tsColorKey.
    */
   uपूर्णांक32 tsColorKey[SVGA3D_NUM_TEXTURE_UNITS];
   uपूर्णांक32 textureStages[SVGA3D_NUM_TEXTURE_UNITS][SVGA3D_TS_CONSTANT + 1];
   uपूर्णांक32 tsColorKeyEnable[SVGA3D_NUM_TEXTURE_UNITS];

   /*
    * Float Shader स्थिरants.
    */
   SVGA3dShaderConstFloat pShaderFValues[SVGA3D_CONSTREG_MAX];
   SVGA3dShaderConstFloat vShaderFValues[SVGA3D_CONSTREG_MAX];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAGBContextData;
#घोषणा SVGA3D_CONTEXT_DATA_SIZE (माप(SVGAGBContextData))

/*
 * SVGA3dCmdSetOTableBase --
 *
 * This command allows the guest to specअगरy the base PPN of the
 * specअगरied object table.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAOTableType type;
   PPN32 baseAddress;
   uपूर्णांक32 sizeInBytes;
   uपूर्णांक32 validSizeInBytes;
   SVGAMobFormat ptDepth;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetOTableBase;  /* SVGA_3D_CMD_SET_OTABLE_BASE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAOTableType type;
   PPN64 baseAddress;
   uपूर्णांक32 sizeInBytes;
   uपूर्णांक32 validSizeInBytes;
   SVGAMobFormat ptDepth;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetOTableBase64;  /* SVGA_3D_CMD_SET_OTABLE_BASE64 */

/*
 * Guests using SVGA_3D_CMD_GROW_OTABLE are promising that
 * the new OTable contains the same contents as the old one, except possibly
 * क्रम some new invalid entries at the end.
 *
 * (Otherwise, guests should use one of the SetOTableBase commands.)
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAOTableType type;
   PPN64 baseAddress;
   uपूर्णांक32 sizeInBytes;
   uपूर्णांक32 validSizeInBytes;
   SVGAMobFormat ptDepth;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdGrowOTable;  /* SVGA_3D_CMD_GROW_OTABLE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAOTableType type;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdReadbackOTable;  /* SVGA_3D_CMD_READBACK_OTABLE */

/*
 * Define a memory object (Mob) in the OTable.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBMob अणु
   SVGAMobId mobid;
   SVGAMobFormat ptDepth;
   PPN32 base;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBMob;   /* SVGA_3D_CMD_DEFINE_GB_MOB */


/*
 * Destroys an object in the OTable.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDestroyGBMob अणु
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroyGBMob;   /* SVGA_3D_CMD_DESTROY_GB_MOB */

/*
 * Define a memory object (Mob) in the OTable with a PPN64 base.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBMob64 अणु
   SVGAMobId mobid;
   SVGAMobFormat ptDepth;
   PPN64 base;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBMob64;   /* SVGA_3D_CMD_DEFINE_GB_MOB64 */

/*
 * Redefine an object in the OTable with PPN64 base.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdRedefineGBMob64 अणु
   SVGAMobId mobid;
   SVGAMobFormat ptDepth;
   PPN64 base;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdRedefineGBMob64;   /* SVGA_3D_CMD_REDEFINE_GB_MOB64 */

/*
 * Notअगरication that the page tables have been modअगरied.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdUpdateGBMobMapping अणु
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdUpdateGBMobMapping;   /* SVGA_3D_CMD_UPDATE_GB_MOB_MAPPING */

/*
 * Define a guest-backed surface.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBSurface अणु
   uपूर्णांक32 sid;
   SVGA3dSurface1Flags surfaceFlags;
   SVGA3dSurfaceFormat क्रमmat;
   uपूर्णांक32 numMipLevels;
   uपूर्णांक32 multisampleCount;
   SVGA3dTextureFilter स्वतःgenFilter;
   SVGA3dSize size;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBSurface;   /* SVGA_3D_CMD_DEFINE_GB_SURFACE */

/*
 * Defines a guest-backed surface, adding the arraySize field.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBSurface_v2 अणु
   uपूर्णांक32 sid;
   SVGA3dSurface1Flags surfaceFlags;
   SVGA3dSurfaceFormat क्रमmat;
   uपूर्णांक32 numMipLevels;
   uपूर्णांक32 multisampleCount;
   SVGA3dTextureFilter स्वतःgenFilter;
   SVGA3dSize size;
   uपूर्णांक32 arraySize;
   uपूर्णांक32 pad;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBSurface_v2;   /* SVGA_3D_CMD_DEFINE_GB_SURFACE_V2 */

/*
 * Defines a guest-backed surface, adding the larger flags.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBSurface_v3 अणु
   uपूर्णांक32 sid;
   SVGA3dSurfaceAllFlags surfaceFlags;
   SVGA3dSurfaceFormat क्रमmat;
   uपूर्णांक32 numMipLevels;
   uपूर्णांक32 multisampleCount;
   SVGA3dMSPattern multisamplePattern;
   SVGA3dMSQualityLevel qualityLevel;
   SVGA3dTextureFilter स्वतःgenFilter;
   SVGA3dSize size;
   uपूर्णांक32 arraySize;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBSurface_v3;   /* SVGA_3D_CMD_DEFINE_GB_SURFACE_V3 */

/*
 * Defines a guest-backed surface, adding buffer byte stride.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBSurface_v4 अणु
   uपूर्णांक32 sid;
   SVGA3dSurfaceAllFlags surfaceFlags;
   SVGA3dSurfaceFormat क्रमmat;
   uपूर्णांक32 numMipLevels;
   uपूर्णांक32 multisampleCount;
   SVGA3dMSPattern multisamplePattern;
   SVGA3dMSQualityLevel qualityLevel;
   SVGA3dTextureFilter स्वतःgenFilter;
   SVGA3dSize size;
   uपूर्णांक32 arraySize;
   uपूर्णांक32 bufferByteStride;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBSurface_v4;   /* SVGA_3D_CMD_DEFINE_GB_SURFACE_V4 */

/*
 * Destroy a guest-backed surface.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDestroyGBSurface अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroyGBSurface;   /* SVGA_3D_CMD_DESTROY_GB_SURFACE */

/*
 * Bind a guest-backed surface to a mob.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdBindGBSurface अणु
   uपूर्णांक32 sid;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBindGBSurface;   /* SVGA_3D_CMD_BIND_GB_SURFACE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdBindGBSurfaceWithPitch अणु
   uपूर्णांक32 sid;
   SVGAMobId mobid;
   uपूर्णांक32 baseLevelPitch;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBindGBSurfaceWithPitch;   /* SVGA_3D_CMD_BIND_GB_SURFACE_WITH_PITCH */

/*
 * Conditionally bind a mob to a guest-backed surface अगर testMobid
 * matches the currently bound mob.  Optionally issue a
 * पढ़ोback/update on the surface जबतक it is still bound to the old
 * mobid अगर the mobid is changed by this command.
 */

#घोषणा SVGA3D_COND_BIND_GB_SURFACE_FLAG_READBACK (1 << 0)
#घोषणा SVGA3D_COND_BIND_GB_SURFACE_FLAG_UPDATE   (1 << 1)

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdCondBindGBSurface अणु
   uपूर्णांक32 sid;
   SVGAMobId testMobid;
   SVGAMobId mobid;
   uपूर्णांक32 flags;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdCondBindGBSurface;          /* SVGA_3D_CMD_COND_BIND_GB_SURFACE */

/*
 * Update an image in a guest-backed surface.
 * (Inक्रमm the device that the guest-contents have been updated.)
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdUpdateGBImage अणु
   SVGA3dSurfaceImageId image;
   SVGA3dBox box;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdUpdateGBImage;   /* SVGA_3D_CMD_UPDATE_GB_IMAGE */

/*
 * Update an entire guest-backed surface.
 * (Inक्रमm the device that the guest-contents have been updated.)
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdUpdateGBSurface अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdUpdateGBSurface;   /* SVGA_3D_CMD_UPDATE_GB_SURFACE */

/*
 * Readback an image in a guest-backed surface.
 * (Request the device to flush the dirty contents पूर्णांकo the guest.)
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdReadbackGBImage अणु
   SVGA3dSurfaceImageId image;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdReadbackGBImage;   /* SVGA_3D_CMD_READBACK_GB_IMAGE */

/*
 * Readback an entire guest-backed surface.
 * (Request the device to flush the dirty contents पूर्णांकo the guest.)
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdReadbackGBSurface अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdReadbackGBSurface;   /* SVGA_3D_CMD_READBACK_GB_SURFACE */

/*
 * Readback a sub rect of an image in a guest-backed surface.  After
 * issuing this command the driver is required to issue an update call
 * of the same region beक्रमe issuing any other commands that reference
 * this surface or rendering is not guaranteed.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdReadbackGBImagePartial अणु
   SVGA3dSurfaceImageId image;
   SVGA3dBox box;
   uपूर्णांक32 invertBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdReadbackGBImagePartial; /* SVGA_3D_CMD_READBACK_GB_IMAGE_PARTIAL */


/*
 * Invalidate an image in a guest-backed surface.
 * (Notअगरy the device that the contents can be lost.)
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdInvalidateGBImage अणु
   SVGA3dSurfaceImageId image;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdInvalidateGBImage;   /* SVGA_3D_CMD_INVALIDATE_GB_IMAGE */

/*
 * Invalidate an entire guest-backed surface.
 * (Notअगरy the device that the contents अगर all images can be lost.)
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdInvalidateGBSurface अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdInvalidateGBSurface; /* SVGA_3D_CMD_INVALIDATE_GB_SURFACE */

/*
 * Invalidate a sub rect of an image in a guest-backed surface.  After
 * issuing this command the driver is required to issue an update call
 * of the same region beक्रमe issuing any other commands that reference
 * this surface or rendering is not guaranteed.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdInvalidateGBImagePartial अणु
   SVGA3dSurfaceImageId image;
   SVGA3dBox box;
   uपूर्णांक32 invertBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdInvalidateGBImagePartial; /* SVGA_3D_CMD_INVALIDATE_GB_IMAGE_PARTIAL */


/*
 * Define a guest-backed context.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBContext;   /* SVGA_3D_CMD_DEFINE_GB_CONTEXT */

/*
 * Destroy a guest-backed context.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDestroyGBContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroyGBContext;   /* SVGA_3D_CMD_DESTROY_GB_CONTEXT */

/*
 * Bind a guest-backed context.
 *
 * validContents should be set to 0 क्रम new contexts,
 * and 1 अगर this is an old context which is getting paged
 * back on to the device.
 *
 * For new contexts, it is recommended that the driver
 * issue commands to initialize all पूर्णांकeresting state
 * prior to rendering.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdBindGBContext अणु
   uपूर्णांक32 cid;
   SVGAMobId mobid;
   uपूर्णांक32 validContents;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBindGBContext;   /* SVGA_3D_CMD_BIND_GB_CONTEXT */

/*
 * Readback a guest-backed context.
 * (Request that the device flush the contents back पूर्णांकo guest memory.)
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdReadbackGBContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdReadbackGBContext;   /* SVGA_3D_CMD_READBACK_GB_CONTEXT */

/*
 * Invalidate a guest-backed context.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdInvalidateGBContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdInvalidateGBContext;   /* SVGA_3D_CMD_INVALIDATE_GB_CONTEXT */

/*
 * Define a guest-backed shader.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDefineGBShader अणु
   uपूर्णांक32 shid;
   SVGA3dShaderType type;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBShader;   /* SVGA_3D_CMD_DEFINE_GB_SHADER */

/*
 * Bind a guest-backed shader.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdBindGBShader अणु
   uपूर्णांक32 shid;
   SVGAMobId mobid;
   uपूर्णांक32 offsetInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBindGBShader;   /* SVGA_3D_CMD_BIND_GB_SHADER */

/*
 * Destroy a guest-backed shader.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDestroyGBShader अणु
   uपूर्णांक32 shid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroyGBShader;   /* SVGA_3D_CMD_DESTROY_GB_SHADER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32                  cid;
   uपूर्णांक32                  regStart;
   SVGA3dShaderType        shaderType;
   SVGA3dShaderConstType   स्थिरType;

   /*
    * Followed by a variable number of shader स्थिरants.
    *
    * Note that FLOAT and INT स्थिरants are 4-dwords in length, जबतक
    * BOOL स्थिरants are 1-dword in length.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdSetGBShaderConstInline;   /* SVGA_3D_CMD_SET_GB_SHADERCONSTS_INLINE */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dQueryType      type;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBeginGBQuery;           /* SVGA_3D_CMD_BEGIN_GB_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dQueryType      type;
   SVGAMobId mobid;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdEndGBQuery;                  /* SVGA_3D_CMD_END_GB_QUERY */


/*
 * SVGA_3D_CMD_WAIT_FOR_GB_QUERY --
 *
 *    The semantics of this command are identical to the
 *    SVGA_3D_CMD_WAIT_FOR_QUERY except that the results are written
 *    to a Mob instead of a GMR.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32               cid;
   SVGA3dQueryType      type;
   SVGAMobId mobid;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdWaitForGBQuery;          /* SVGA_3D_CMD_WAIT_FOR_GB_QUERY */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAMobId mobid;
   uपूर्णांक32 mustBeZero;
   uपूर्णांक32 initialized;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdEnableGart;              /* SVGA_3D_CMD_ENABLE_GART */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGAMobId mobid;
   uपूर्णांक32 gartOffset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdMapMobIntoGart;          /* SVGA_3D_CMD_MAP_MOB_INTO_GART */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 gartOffset;
   uपूर्णांक32 numPages;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdUnmapGartRange;          /* SVGA_3D_CMD_UNMAP_GART_RANGE */


/*
 * Screen Tarमाला_लो
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 stid;
   uपूर्णांक32 width;
   uपूर्णांक32 height;
   पूर्णांक32 xRoot;
   पूर्णांक32 yRoot;
   SVGAScreenTargetFlags flags;

   /*
    * The physical DPI that the guest expects this screen displayed at.
    *
    * Guests which are not DPI-aware should set this to zero.
    */
   uपूर्णांक32 dpi;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDefineGBScreenTarget;    /* SVGA_3D_CMD_DEFINE_GB_SCREENTARGET */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 stid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDestroyGBScreenTarget;  /* SVGA_3D_CMD_DESTROY_GB_SCREENTARGET */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 stid;
   SVGA3dSurfaceImageId image;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdBindGBScreenTarget;  /* SVGA_3D_CMD_BIND_GB_SCREENTARGET */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 stid;
   SVGA3dRect rect;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdUpdateGBScreenTarget;  /* SVGA_3D_CMD_UPDATE_GB_SCREENTARGET */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdGBScreenDMA अणु
   uपूर्णांक32 screenId;
   uपूर्णांक32 dead;
   SVGAMobId destMobID;
   uपूर्णांक32 destPitch;
   SVGAMobId changeMapMobID;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdGBScreenDMA;        /* SVGA_3D_CMD_GB_SCREEN_DMA */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 value;
   uपूर्णांक32 mobId;
   uपूर्णांक32 mobOffset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdGBMobFence;  /* SVGA_3D_CMD_GB_MOB_FENCE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 stid;
   SVGA3dSurfaceImageId dest;

   uपूर्णांक32 statusMobId;
   uपूर्णांक32 statusMobOffset;

   /* Reserved fields */
   uपूर्णांक32 mustBeInvalidId;
   uपूर्णांक32 mustBeZero;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdScreenCopy;  /* SVGA_3D_CMD_SCREEN_COPY */

#घोषणा SVGA_SCREEN_COPY_STATUS_FAILURE 0x00
#घोषणा SVGA_SCREEN_COPY_STATUS_SUCCESS 0x01
#घोषणा SVGA_SCREEN_COPY_STATUS_INVALID 0xFFFFFFFF

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdWriteZeroSurface;  /* SVGA_3D_CMD_WRITE_ZERO_SURFACE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 sid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdHपूर्णांकZeroSurface;  /* SVGA_3D_CMD_HINT_ZERO_SURFACE */

#पूर्ण_अगर /* _SVGA3D_CMD_H_ */
