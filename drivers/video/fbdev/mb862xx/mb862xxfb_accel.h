<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MB826XXFB_ACCEL_H__
#घोषणा __MB826XXFB_ACCEL_H__

/* रेजिस्टरs */
#घोषणा GDC_GEO_REG_INPUT_FIFO 0x00000400L

/* Special Registers */
#घोषणा GDC_REG_CTRL                0x00000400L
#घोषणा GDC_REG_FIFO_STATUS         0x00000404L
#घोषणा GDC_REG_FIFO_COUNT          0x00000408L
#घोषणा GDC_REG_SETUP_STATUS        0x0000040CL
#घोषणा GDC_REG_DDA_STATUS          0x00000410L
#घोषणा GDC_REG_ENGINE_STATUS       0x00000414L
#घोषणा GDC_REG_ERROR_STATUS        0x00000418L
#घोषणा GDC_REG_MODE_MISC           0x00000420L	/* MDR0 */
#घोषणा GDC_REG_MODE_LINE           0x00000424L	/* MDR1 */
#घोषणा GDC_REG_MODE_POLYGON        0x00000428L	/* MDR2 */
#घोषणा GDC_REG_MODE_TEXTURE        0x0000042CL	/* MDR3 */
#घोषणा GDC_REG_MODE_BITMAP         0x00000430L	/* MDR4 */
#घोषणा GDC_REG_MODE_EXTENSION      0x0000043CL	/* MDR7 */

/* Configuration Registers */
#घोषणा GDC_REG_DRAW_BASE           0x00000440L
#घोषणा GDC_REG_X_RESOLUTION        0x00000444L
#घोषणा GDC_REG_Z_BASE              0x00000448L
#घोषणा GDC_REG_TEXTURE_BASE        0x0000044CL
#घोषणा GDC_REG_POLYGON_FLAG_BASE   0x00000450L
#घोषणा GDC_REG_CLIP_XMIN           0x00000454L
#घोषणा GDC_REG_CLIP_XMAX           0x00000458L
#घोषणा GDC_REG_CLIP_YMIN           0x0000045CL
#घोषणा GDC_REG_CLIP_YMAX           0x00000460L
#घोषणा GDC_REG_TEXURE_SIZE         0x00000464L
#घोषणा GDC_REG_TILE_SIZE           0x00000468L
#घोषणा GDC_REG_TEX_BUF_OFFSET      0x0000046CL

/* क्रम MB86293 or later */
#घोषणा GDC_REG_ALPHA_MAP_BASE      0x00000474L	/* ABR */

/* Constant Registers */
#घोषणा GDC_REG_FOREGROUND_COLOR    0x00000480L
#घोषणा GDC_REG_BACKGROUND_COLOR    0x00000484L
#घोषणा GDC_REG_ALPHA               0x00000488L
#घोषणा GDC_REG_LINE_PATTERN        0x0000048CL
#घोषणा GDC_REG_TEX_BORDER_COLOR    0x00000494L
#घोषणा GDC_REG_LINE_PATTERN_OFFSET 0x000003E0L

/* Coomand Code */
#घोषणा GDC_CMD_PIXEL                   0x00000000L
#घोषणा GDC_CMD_PIXEL_Z                 0x00000001L

#घोषणा GDC_CMD_X_VECTOR                0x00000020L
#घोषणा GDC_CMD_Y_VECTOR                0x00000021L
#घोषणा GDC_CMD_X_VECTOR_NOEND          0x00000022L
#घोषणा GDC_CMD_Y_VECTOR_NOEND          0x00000023L
#घोषणा GDC_CMD_X_VECTOR_BLPO           0x00000024L
#घोषणा GDC_CMD_Y_VECTOR_BLPO           0x00000025L
#घोषणा GDC_CMD_X_VECTOR_NOEND_BLPO     0x00000026L
#घोषणा GDC_CMD_Y_VECTOR_NOEND_BLPO     0x00000027L
#घोषणा GDC_CMD_AA_X_VECTOR             0x00000028L
#घोषणा GDC_CMD_AA_Y_VECTOR             0x00000029L
#घोषणा GDC_CMD_AA_X_VECTOR_NOEND       0x0000002AL
#घोषणा GDC_CMD_AA_Y_VECTOR_NOEND       0x0000002BL
#घोषणा GDC_CMD_AA_X_VECTOR_BLPO        0x0000002CL
#घोषणा GDC_CMD_AA_Y_VECTOR_BLPO        0x0000002DL
#घोषणा GDC_CMD_AA_X_VECTOR_NOEND_BLPO  0x0000002EL
#घोषणा GDC_CMD_AA_Y_VECTOR_NOEND_BLPO  0x0000002FL

#घोषणा GDC_CMD_0_VECTOR                0x00000030L
#घोषणा GDC_CMD_1_VECTOR                0x00000031L
#घोषणा GDC_CMD_0_VECTOR_NOEND          0x00000032L
#घोषणा GDC_CMD_1_VECTOR_NOEND          0x00000033L
#घोषणा GDC_CMD_0_VECTOR_BLPO           0x00000034L
#घोषणा GDC_CMD_1_VECTOR_BLPO           0x00000035L
#घोषणा GDC_CMD_0_VECTOR_NOEND_BLPO     0x00000036L
#घोषणा GDC_CMD_1_VECTOR_NOEND_BLPO     0x00000037L
#घोषणा GDC_CMD_AA_0_VECTOR             0x00000038L
#घोषणा GDC_CMD_AA_1_VECTOR             0x00000039L
#घोषणा GDC_CMD_AA_0_VECTOR_NOEND       0x0000003AL
#घोषणा GDC_CMD_AA_1_VECTOR_NOEND       0x0000003BL
#घोषणा GDC_CMD_AA_0_VECTOR_BLPO        0x0000003CL
#घोषणा GDC_CMD_AA_1_VECTOR_BLPO        0x0000003DL
#घोषणा GDC_CMD_AA_0_VECTOR_NOEND_BLPO  0x0000003EL
#घोषणा GDC_CMD_AA_1_VECTOR_NOEND_BLPO  0x0000003FL

#घोषणा GDC_CMD_BLT_FILL                0x00000041L
#घोषणा GDC_CMD_BLT_DRAW                0x00000042L
#घोषणा GDC_CMD_BITMAP                  0x00000043L
#घोषणा GDC_CMD_BLTCOPY_TOP_LEFT        0x00000044L
#घोषणा GDC_CMD_BLTCOPY_TOP_RIGHT       0x00000045L
#घोषणा GDC_CMD_BLTCOPY_BOTTOM_LEFT     0x00000046L
#घोषणा GDC_CMD_BLTCOPY_BOTTOM_RIGHT    0x00000047L
#घोषणा GDC_CMD_LOAD_TEXTURE            0x00000048L
#घोषणा GDC_CMD_LOAD_TILE               0x00000049L

#घोषणा GDC_CMD_TRAP_RIGHT              0x00000060L
#घोषणा GDC_CMD_TRAP_LEFT               0x00000061L
#घोषणा GDC_CMD_TRIANGLE_FAN            0x00000062L
#घोषणा GDC_CMD_FLAG_TRIANGLE_FAN       0x00000063L

#घोषणा GDC_CMD_FLUSH_FB                0x000000C1L
#घोषणा GDC_CMD_FLUSH_Z                 0x000000C2L

#घोषणा GDC_CMD_POLYGON_BEGIN           0x000000E0L
#घोषणा GDC_CMD_POLYGON_END             0x000000E1L
#घोषणा GDC_CMD_CLEAR_POLY_FLAG         0x000000E2L
#घोषणा GDC_CMD_NORMAL                  0x000000FFL

#घोषणा GDC_CMD_VECTOR_BLPO_FLAG        0x00040000L
#घोषणा GDC_CMD_FAST_VECTOR_BLPO_FLAG   0x00000004L

/* क्रम MB86293 or later */
#घोषणा GDC_CMD_MDR1                            0x00000000L
#घोषणा GDC_CMD_MDR1S                           0x00000002L
#घोषणा GDC_CMD_MDR1B                           0x00000004L
#घोषणा GDC_CMD_MDR2                            0x00000001L
#घोषणा GDC_CMD_MDR2S                           0x00000003L
#घोषणा GDC_CMD_MDR2TL                          0x00000007L
#घोषणा GDC_CMD_GMDR1E                          0x00000010L
#घोषणा GDC_CMD_GMDR2E                          0x00000020L
#घोषणा GDC_CMD_OVERLAP_SHADOW_XY               0x00000000L
#घोषणा GDC_CMD_OVERLAP_SHADOW_XY_COMPOSITION   0x00000001L
#घोषणा GDC_CMD_OVERLAP_Z_PACKED_ONBS           0x00000007L
#घोषणा GDC_CMD_OVERLAP_Z_ORIGIN                0x00000000L
#घोषणा GDC_CMD_OVERLAP_Z_NON_TOPLEFT           0x00000001L
#घोषणा GDC_CMD_OVERLAP_Z_BORDER                0x00000002L
#घोषणा GDC_CMD_OVERLAP_Z_SHADOW                0x00000003L
#घोषणा GDC_CMD_BLTCOPY_ALT_ALPHA               0x00000000L	/* Reserverd */
#घोषणा GDC_CMD_DC_LOGOUT                       0x00000000L	/* Reserverd */
#घोषणा GDC_CMD_BODY_FORE_COLOR                 0x00000000L
#घोषणा GDC_CMD_BODY_BACK_COLOR                 0x00000001L
#घोषणा GDC_CMD_SHADOW_FORE_COLOR               0x00000002L
#घोषणा GDC_CMD_SHADOW_BACK_COLOR               0x00000003L
#घोषणा GDC_CMD_BORDER_FORE_COLOR               0x00000004L
#घोषणा GDC_CMD_BORDER_BACK_COLOR               0x00000005L

/* Type Code Table */
#घोषणा GDC_TYPE_G_NOP                                  0x00000020L
#घोषणा GDC_TYPE_G_BEGIN                                0x00000021L
#घोषणा GDC_TYPE_G_BEGINCONT                            0x00000022L
#घोषणा GDC_TYPE_G_END                                  0x00000023L
#घोषणा GDC_TYPE_G_VERTEX                               0x00000030L
#घोषणा GDC_TYPE_G_VERTEXLOG                            0x00000032L
#घोषणा GDC_TYPE_G_VERTEXNOPLOG                         0x00000033L
#घोषणा GDC_TYPE_G_INIT                                 0x00000040L
#घोषणा GDC_TYPE_G_VIEWPORT                             0x00000041L
#घोषणा GDC_TYPE_G_DEPTHRANGE                           0x00000042L
#घोषणा GDC_TYPE_G_LOADMATRIX                           0x00000043L
#घोषणा GDC_TYPE_G_VIEWVOLUMEXYCLIP                     0x00000044L
#घोषणा GDC_TYPE_G_VIEWVOLUMEZCLIP                      0x00000045L
#घोषणा GDC_TYPE_G_VIEWVOLUMEWCLIP                      0x00000046L
#घोषणा GDC_TYPE_SETLVERTEX2I                           0x00000072L
#घोषणा GDC_TYPE_SETLVERTEX2IP                          0x00000073L
#घोषणा GDC_TYPE_SETMODEREGISTER                        0x000000C0L
#घोषणा GDC_TYPE_SETGMODEREGISTER                       0x000000C1L
#घोषणा GDC_TYPE_OVERLAPXYOFFT                          0x000000C8L
#घोषणा GDC_TYPE_OVERLAPZOFFT                           0x000000C9L
#घोषणा GDC_TYPE_DC_LOGOUTADDR                          0x000000CCL
#घोषणा GDC_TYPE_SETCOLORREGISTER                       0x000000CEL
#घोषणा GDC_TYPE_G_BEGINE                               0x000000E1L
#घोषणा GDC_TYPE_G_BEGINCONTE                           0x000000E2L
#घोषणा GDC_TYPE_G_ENDE                                 0x000000E3L
#घोषणा GDC_TYPE_DRAWPIXEL                              0x00000000L
#घोषणा GDC_TYPE_DRAWPIXELZ                             0x00000001L
#घोषणा GDC_TYPE_DRAWLINE                               0x00000002L
#घोषणा GDC_TYPE_DRAWLINE2I                             0x00000003L
#घोषणा GDC_TYPE_DRAWLINE2IP                            0x00000004L
#घोषणा GDC_TYPE_DRAWTRAP                               0x00000005L
#घोषणा GDC_TYPE_DRAWVERTEX2I                           0x00000006L
#घोषणा GDC_TYPE_DRAWVERTEX2IP                          0x00000007L
#घोषणा GDC_TYPE_DRAWRECTP                              0x00000009L
#घोषणा GDC_TYPE_DRAWBITMAPP                            0x0000000BL
#घोषणा GDC_TYPE_BLTCOPYP                               0x0000000DL
#घोषणा GDC_TYPE_BLTCOPYALTERNATEP                      0x0000000FL
#घोषणा GDC_TYPE_LOADTEXTUREP                           0x00000011L
#घोषणा GDC_TYPE_BLTTEXTUREP                            0x00000013L
#घोषणा GDC_TYPE_BLTCOPYALTALPHABLENDP                  0x0000001FL
#घोषणा GDC_TYPE_SETVERTEX2I                            0x00000070L
#घोषणा GDC_TYPE_SETVERTEX2IP                           0x00000071L
#घोषणा GDC_TYPE_DRAW                                   0x000000F0L
#घोषणा GDC_TYPE_SETREGISTER                            0x000000F1L
#घोषणा GDC_TYPE_SYNC                                   0x000000FCL
#घोषणा GDC_TYPE_INTERRUPT                              0x000000FDL
#घोषणा GDC_TYPE_NOP                                    0x0

/* Raster operation */
#घोषणा GDC_ROP_CLEAR                   0x0000
#घोषणा GDC_ROP_AND                     0x0001
#घोषणा GDC_ROP_AND_REVERSE             0x0002
#घोषणा GDC_ROP_COPY                    0x0003
#घोषणा GDC_ROP_AND_INVERTED            0x0004
#घोषणा GDC_ROP_NOP                     0x0005
#घोषणा GDC_ROP_XOR                     0x0006
#घोषणा GDC_ROP_OR                      0x0007
#घोषणा GDC_ROP_NOR                     0x0008
#घोषणा GDC_ROP_EQUIV                   0x0009
#घोषणा GDC_ROP_INVERT                  0x000A
#घोषणा GDC_ROP_OR_REVERSE              0x000B
#घोषणा GDC_ROP_COPY_INVERTED           0x000C
#घोषणा GDC_ROP_OR_INVERTED             0x000D
#घोषणा GDC_ROP_न_अंकD                    0x000E
#घोषणा GDC_ROP_SET                     0x000F

#पूर्ण_अगर
