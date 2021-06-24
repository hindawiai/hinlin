<शैली गुरु>
/*
 * Copyright तऊ 2014 Broadcom
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित VC4_PACKET_H
#घोषणा VC4_PACKET_H

#समावेश "vc4_regs.h" /* क्रम VC4_MASK, VC4_GET_FIELD, VC4_SET_FIELD */

क्रमागत vc4_packet अणु
	VC4_PACKET_HALT = 0,
	VC4_PACKET_NOP = 1,

	VC4_PACKET_FLUSH = 4,
	VC4_PACKET_FLUSH_ALL = 5,
	VC4_PACKET_START_TILE_BINNING = 6,
	VC4_PACKET_INCREMENT_SEMAPHORE = 7,
	VC4_PACKET_WAIT_ON_SEMAPHORE = 8,

	VC4_PACKET_BRANCH = 16,
	VC4_PACKET_BRANCH_TO_SUB_LIST = 17,

	VC4_PACKET_STORE_MS_TILE_BUFFER = 24,
	VC4_PACKET_STORE_MS_TILE_BUFFER_AND_खातापूर्ण = 25,
	VC4_PACKET_STORE_FULL_RES_TILE_BUFFER = 26,
	VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER = 27,
	VC4_PACKET_STORE_TILE_BUFFER_GENERAL = 28,
	VC4_PACKET_LOAD_TILE_BUFFER_GENERAL = 29,

	VC4_PACKET_GL_INDEXED_PRIMITIVE = 32,
	VC4_PACKET_GL_ARRAY_PRIMITIVE = 33,

	VC4_PACKET_COMPRESSED_PRIMITIVE = 48,
	VC4_PACKET_CLIPPED_COMPRESSED_PRIMITIVE = 49,

	VC4_PACKET_PRIMITIVE_LIST_FORMAT = 56,

	VC4_PACKET_GL_SHADER_STATE = 64,
	VC4_PACKET_NV_SHADER_STATE = 65,
	VC4_PACKET_VG_SHADER_STATE = 66,

	VC4_PACKET_CONFIGURATION_BITS = 96,
	VC4_PACKET_FLAT_SHADE_FLAGS = 97,
	VC4_PACKET_POINT_SIZE = 98,
	VC4_PACKET_LINE_WIDTH = 99,
	VC4_PACKET_RHT_X_BOUNDARY = 100,
	VC4_PACKET_DEPTH_OFFSET = 101,
	VC4_PACKET_CLIP_WINDOW = 102,
	VC4_PACKET_VIEWPORT_OFFSET = 103,
	VC4_PACKET_Z_CLIPPING = 104,
	VC4_PACKET_CLIPPER_XY_SCALING = 105,
	VC4_PACKET_CLIPPER_Z_SCALING = 106,

	VC4_PACKET_TILE_BINNING_MODE_CONFIG = 112,
	VC4_PACKET_TILE_RENDERING_MODE_CONFIG = 113,
	VC4_PACKET_CLEAR_COLORS = 114,
	VC4_PACKET_TILE_COORDINATES = 115,

	/* Not an actual hardware packet -- this is what we use to put
	 * references to GEM bos in the command stream, since we need the u32
	 * पूर्णांक the actual address packet in order to store the offset from the
	 * start of the BO.
	 */
	VC4_PACKET_GEM_HANDLES = 254,
पूर्ण __attribute__ ((__packed__));

#घोषणा VC4_PACKET_HALT_SIZE						1
#घोषणा VC4_PACKET_NOP_SIZE						1
#घोषणा VC4_PACKET_FLUSH_SIZE						1
#घोषणा VC4_PACKET_FLUSH_ALL_SIZE					1
#घोषणा VC4_PACKET_START_TILE_BINNING_SIZE				1
#घोषणा VC4_PACKET_INCREMENT_SEMAPHORE_SIZE				1
#घोषणा VC4_PACKET_WAIT_ON_SEMAPHORE_SIZE				1
#घोषणा VC4_PACKET_BRANCH_SIZE						5
#घोषणा VC4_PACKET_BRANCH_TO_SUB_LIST_SIZE				5
#घोषणा VC4_PACKET_STORE_MS_TILE_BUFFER_SIZE				1
#घोषणा VC4_PACKET_STORE_MS_TILE_BUFFER_AND_खातापूर्ण_SIZE			1
#घोषणा VC4_PACKET_STORE_FULL_RES_TILE_BUFFER_SIZE			5
#घोषणा VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER_SIZE			5
#घोषणा VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE			7
#घोषणा VC4_PACKET_LOAD_TILE_BUFFER_GENERAL_SIZE			7
#घोषणा VC4_PACKET_GL_INDEXED_PRIMITIVE_SIZE				14
#घोषणा VC4_PACKET_GL_ARRAY_PRIMITIVE_SIZE				10
#घोषणा VC4_PACKET_COMPRESSED_PRIMITIVE_SIZE				1
#घोषणा VC4_PACKET_CLIPPED_COMPRESSED_PRIMITIVE_SIZE			1
#घोषणा VC4_PACKET_PRIMITIVE_LIST_FORMAT_SIZE				2
#घोषणा VC4_PACKET_GL_SHADER_STATE_SIZE					5
#घोषणा VC4_PACKET_NV_SHADER_STATE_SIZE					5
#घोषणा VC4_PACKET_VG_SHADER_STATE_SIZE					5
#घोषणा VC4_PACKET_CONFIGURATION_BITS_SIZE				4
#घोषणा VC4_PACKET_FLAT_SHADE_FLAGS_SIZE				5
#घोषणा VC4_PACKET_POINT_SIZE_SIZE					5
#घोषणा VC4_PACKET_LINE_WIDTH_SIZE					5
#घोषणा VC4_PACKET_RHT_X_BOUNDARY_SIZE					3
#घोषणा VC4_PACKET_DEPTH_OFFSET_SIZE					5
#घोषणा VC4_PACKET_CLIP_WINDOW_SIZE					9
#घोषणा VC4_PACKET_VIEWPORT_OFFSET_SIZE					5
#घोषणा VC4_PACKET_Z_CLIPPING_SIZE					9
#घोषणा VC4_PACKET_CLIPPER_XY_SCALING_SIZE				9
#घोषणा VC4_PACKET_CLIPPER_Z_SCALING_SIZE				9
#घोषणा VC4_PACKET_TILE_BINNING_MODE_CONFIG_SIZE			16
#घोषणा VC4_PACKET_TILE_RENDERING_MODE_CONFIG_SIZE			11
#घोषणा VC4_PACKET_CLEAR_COLORS_SIZE					14
#घोषणा VC4_PACKET_TILE_COORDINATES_SIZE				3
#घोषणा VC4_PACKET_GEM_HANDLES_SIZE					9

/* Number of multisamples supported. */
#घोषणा VC4_MAX_SAMPLES							4
/* Size of a full resolution color or Z tile buffer load/store. */
#घोषणा VC4_TILE_BUFFER_SIZE			(64 * 64 * 4)

/** @अणु
 * Bits used by packets like VC4_PACKET_STORE_TILE_BUFFER_GENERAL and
 * VC4_PACKET_TILE_RENDERING_MODE_CONFIG.
*/
#घोषणा VC4_TILING_FORMAT_LINEAR    0
#घोषणा VC4_TILING_FORMAT_T         1
#घोषणा VC4_TILING_FORMAT_LT        2
/** @पूर्ण */

/** @अणु
 *
 * low bits of VC4_PACKET_STORE_FULL_RES_TILE_BUFFER and
 * VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER.
 */
#घोषणा VC4_LOADSTORE_FULL_RES_खातापूर्ण                     BIT(3)
#घोषणा VC4_LOADSTORE_FULL_RES_DISABLE_CLEAR_ALL       BIT(2)
#घोषणा VC4_LOADSTORE_FULL_RES_DISABLE_ZS              BIT(1)
#घोषणा VC4_LOADSTORE_FULL_RES_DISABLE_COLOR           BIT(0)

/** @अणु
 *
 * low bits of VC4_PACKET_STORE_FULL_RES_TILE_BUFFER and
 * VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER.
 */
#घोषणा VC4_LOADSTORE_FULL_RES_खातापूर्ण                     BIT(3)
#घोषणा VC4_LOADSTORE_FULL_RES_DISABLE_CLEAR_ALL       BIT(2)
#घोषणा VC4_LOADSTORE_FULL_RES_DISABLE_ZS              BIT(1)
#घोषणा VC4_LOADSTORE_FULL_RES_DISABLE_COLOR           BIT(0)

/** @अणु
 *
 * byte 2 of VC4_PACKET_STORE_TILE_BUFFER_GENERAL and
 * VC4_PACKET_LOAD_TILE_BUFFER_GENERAL (low bits of the address)
 */

#घोषणा VC4_LOADSTORE_TILE_BUFFER_खातापूर्ण                  BIT(3)
#घोषणा VC4_LOADSTORE_TILE_BUFFER_DISABLE_FULL_VG_MASK BIT(2)
#घोषणा VC4_LOADSTORE_TILE_BUFFER_DISABLE_FULL_ZS      BIT(1)
#घोषणा VC4_LOADSTORE_TILE_BUFFER_DISABLE_FULL_COLOR   BIT(0)

/** @पूर्ण */

/** @अणु
 *
 * byte 0-1 of VC4_PACKET_STORE_TILE_BUFFER_GENERAL and
 * VC4_PACKET_LOAD_TILE_BUFFER_GENERAL
 */
#घोषणा VC4_STORE_TILE_BUFFER_DISABLE_VG_MASK_CLEAR BIT(15)
#घोषणा VC4_STORE_TILE_BUFFER_DISABLE_ZS_CLEAR     BIT(14)
#घोषणा VC4_STORE_TILE_BUFFER_DISABLE_COLOR_CLEAR  BIT(13)
#घोषणा VC4_STORE_TILE_BUFFER_DISABLE_SWAP         BIT(12)

#घोषणा VC4_LOADSTORE_TILE_BUFFER_FORMAT_MASK      VC4_MASK(9, 8)
#घोषणा VC4_LOADSTORE_TILE_BUFFER_FORMAT_SHIFT     8
#घोषणा VC4_LOADSTORE_TILE_BUFFER_RGBA8888         0
#घोषणा VC4_LOADSTORE_TILE_BUFFER_BGR565_DITHER    1
#घोषणा VC4_LOADSTORE_TILE_BUFFER_BGR565           2
/** @पूर्ण */

/** @अणु
 *
 * byte 0 of VC4_PACKET_STORE_TILE_BUFFER_GENERAL and
 * VC4_PACKET_LOAD_TILE_BUFFER_GENERAL
 */
#घोषणा VC4_STORE_TILE_BUFFER_MODE_MASK            VC4_MASK(7, 6)
#घोषणा VC4_STORE_TILE_BUFFER_MODE_SHIFT           6
#घोषणा VC4_STORE_TILE_BUFFER_MODE_SAMPLE0         (0 << 6)
#घोषणा VC4_STORE_TILE_BUFFER_MODE_DECIMATE_X4     (1 << 6)
#घोषणा VC4_STORE_TILE_BUFFER_MODE_DECIMATE_X16    (2 << 6)

/** The values of the field are VC4_TILING_FORMAT_* */
#घोषणा VC4_LOADSTORE_TILE_BUFFER_TILING_MASK      VC4_MASK(5, 4)
#घोषणा VC4_LOADSTORE_TILE_BUFFER_TILING_SHIFT     4

#घोषणा VC4_LOADSTORE_TILE_BUFFER_BUFFER_MASK      VC4_MASK(2, 0)
#घोषणा VC4_LOADSTORE_TILE_BUFFER_BUFFER_SHIFT     0
#घोषणा VC4_LOADSTORE_TILE_BUFFER_NONE             0
#घोषणा VC4_LOADSTORE_TILE_BUFFER_COLOR            1
#घोषणा VC4_LOADSTORE_TILE_BUFFER_ZS               2
#घोषणा VC4_LOADSTORE_TILE_BUFFER_Z                3
#घोषणा VC4_LOADSTORE_TILE_BUFFER_VG_MASK          4
#घोषणा VC4_LOADSTORE_TILE_BUFFER_FULL             5
/** @पूर्ण */

#घोषणा VC4_INDEX_BUFFER_U8                        (0 << 4)
#घोषणा VC4_INDEX_BUFFER_U16                       (1 << 4)

/* This flag is only present in NV shader state. */
#घोषणा VC4_SHADER_FLAG_SHADED_CLIP_COORDS         BIT(3)
#घोषणा VC4_SHADER_FLAG_ENABLE_CLIPPING            BIT(2)
#घोषणा VC4_SHADER_FLAG_VS_POINT_SIZE              BIT(1)
#घोषणा VC4_SHADER_FLAG_FS_SINGLE_THREAD           BIT(0)

/** @अणु byte 2 of config bits. */
#घोषणा VC4_CONFIG_BITS_EARLY_Z_UPDATE             BIT(1)
#घोषणा VC4_CONFIG_BITS_EARLY_Z                    BIT(0)
/** @पूर्ण */

/** @अणु byte 1 of config bits. */
#घोषणा VC4_CONFIG_BITS_Z_UPDATE                   BIT(7)
/** same values in this 3-bit field as PIPE_FUNC_* */
#घोषणा VC4_CONFIG_BITS_DEPTH_FUNC_SHIFT           4
#घोषणा VC4_CONFIG_BITS_COVERAGE_READ_LEAVE        BIT(3)

#घोषणा VC4_CONFIG_BITS_COVERAGE_UPDATE_NONZERO    (0 << 1)
#घोषणा VC4_CONFIG_BITS_COVERAGE_UPDATE_ODD        (1 << 1)
#घोषणा VC4_CONFIG_BITS_COVERAGE_UPDATE_OR         (2 << 1)
#घोषणा VC4_CONFIG_BITS_COVERAGE_UPDATE_ZERO       (3 << 1)

#घोषणा VC4_CONFIG_BITS_COVERAGE_PIPE_SELECT       BIT(0)
/** @पूर्ण */

/** @अणु byte 0 of config bits. */
#घोषणा VC4_CONFIG_BITS_RASTERIZER_OVERSAMPLE_NONE (0 << 6)
#घोषणा VC4_CONFIG_BITS_RASTERIZER_OVERSAMPLE_4X   (1 << 6)
#घोषणा VC4_CONFIG_BITS_RASTERIZER_OVERSAMPLE_16X  (2 << 6)

#घोषणा VC4_CONFIG_BITS_AA_POINTS_AND_LINES        BIT(4)
#घोषणा VC4_CONFIG_BITS_ENABLE_DEPTH_OFFSET        BIT(3)
#घोषणा VC4_CONFIG_BITS_CW_PRIMITIVES              BIT(2)
#घोषणा VC4_CONFIG_BITS_ENABLE_PRIM_BACK           BIT(1)
#घोषणा VC4_CONFIG_BITS_ENABLE_PRIM_FRONT          BIT(0)
/** @पूर्ण */

/** @अणु bits in the last u8 of VC4_PACKET_TILE_BINNING_MODE_CONFIG */
#घोषणा VC4_BIN_CONFIG_DB_NON_MS                   BIT(7)

#घोषणा VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_MASK       VC4_MASK(6, 5)
#घोषणा VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_SHIFT      5
#घोषणा VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_32         0
#घोषणा VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_64         1
#घोषणा VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_128        2
#घोषणा VC4_BIN_CONFIG_ALLOC_BLOCK_SIZE_256        3

#घोषणा VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_MASK  VC4_MASK(4, 3)
#घोषणा VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_SHIFT 3
#घोषणा VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_32    0
#घोषणा VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_64    1
#घोषणा VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_128   2
#घोषणा VC4_BIN_CONFIG_ALLOC_INIT_BLOCK_SIZE_256   3

#घोषणा VC4_BIN_CONFIG_AUTO_INIT_TSDA              BIT(2)
#घोषणा VC4_BIN_CONFIG_TILE_BUFFER_64BIT           BIT(1)
#घोषणा VC4_BIN_CONFIG_MS_MODE_4X                  BIT(0)
/** @पूर्ण */

/** @अणु bits in the last u16 of VC4_PACKET_TILE_RENDERING_MODE_CONFIG */
#घोषणा VC4_RENDER_CONFIG_DB_NON_MS                BIT(12)
#घोषणा VC4_RENDER_CONFIG_EARLY_Z_COVERAGE_DISABLE BIT(11)
#घोषणा VC4_RENDER_CONFIG_EARLY_Z_सूचीECTION_G      BIT(10)
#घोषणा VC4_RENDER_CONFIG_COVERAGE_MODE            BIT(9)
#घोषणा VC4_RENDER_CONFIG_ENABLE_VG_MASK           BIT(8)

/** The values of the field are VC4_TILING_FORMAT_* */
#घोषणा VC4_RENDER_CONFIG_MEMORY_FORMAT_MASK       VC4_MASK(7, 6)
#घोषणा VC4_RENDER_CONFIG_MEMORY_FORMAT_SHIFT      6

#घोषणा VC4_RENDER_CONFIG_DECIMATE_MODE_1X         (0 << 4)
#घोषणा VC4_RENDER_CONFIG_DECIMATE_MODE_4X         (1 << 4)
#घोषणा VC4_RENDER_CONFIG_DECIMATE_MODE_16X        (2 << 4)

#घोषणा VC4_RENDER_CONFIG_FORMAT_MASK              VC4_MASK(3, 2)
#घोषणा VC4_RENDER_CONFIG_FORMAT_SHIFT             2
#घोषणा VC4_RENDER_CONFIG_FORMAT_BGR565_DITHERED   0
#घोषणा VC4_RENDER_CONFIG_FORMAT_RGBA8888          1
#घोषणा VC4_RENDER_CONFIG_FORMAT_BGR565            2

#घोषणा VC4_RENDER_CONFIG_TILE_BUFFER_64BIT        BIT(1)
#घोषणा VC4_RENDER_CONFIG_MS_MODE_4X               BIT(0)

#घोषणा VC4_PRIMITIVE_LIST_FORMAT_16_INDEX         (1 << 4)
#घोषणा VC4_PRIMITIVE_LIST_FORMAT_32_XY            (3 << 4)
#घोषणा VC4_PRIMITIVE_LIST_FORMAT_TYPE_POINTS      (0 << 0)
#घोषणा VC4_PRIMITIVE_LIST_FORMAT_TYPE_LINES       (1 << 0)
#घोषणा VC4_PRIMITIVE_LIST_FORMAT_TYPE_TRIANGLES   (2 << 0)
#घोषणा VC4_PRIMITIVE_LIST_FORMAT_TYPE_RHT         (3 << 0)

क्रमागत vc4_texture_data_type अणु
	VC4_TEXTURE_TYPE_RGBA8888 = 0,
	VC4_TEXTURE_TYPE_RGBX8888 = 1,
	VC4_TEXTURE_TYPE_RGBA4444 = 2,
	VC4_TEXTURE_TYPE_RGBA5551 = 3,
	VC4_TEXTURE_TYPE_RGB565 = 4,
	VC4_TEXTURE_TYPE_LUMIन_अंकCE = 5,
	VC4_TEXTURE_TYPE_ALPHA = 6,
	VC4_TEXTURE_TYPE_LUMALPHA = 7,
	VC4_TEXTURE_TYPE_ETC1 = 8,
	VC4_TEXTURE_TYPE_S16F = 9,
	VC4_TEXTURE_TYPE_S8 = 10,
	VC4_TEXTURE_TYPE_S16 = 11,
	VC4_TEXTURE_TYPE_BW1 = 12,
	VC4_TEXTURE_TYPE_A4 = 13,
	VC4_TEXTURE_TYPE_A1 = 14,
	VC4_TEXTURE_TYPE_RGBA64 = 15,
	VC4_TEXTURE_TYPE_RGBA32R = 16,
	VC4_TEXTURE_TYPE_YUV422R = 17,
पूर्ण;

#घोषणा VC4_TEX_P0_OFFSET_MASK                     VC4_MASK(31, 12)
#घोषणा VC4_TEX_P0_OFFSET_SHIFT                    12
#घोषणा VC4_TEX_P0_CSWIZ_MASK                      VC4_MASK(11, 10)
#घोषणा VC4_TEX_P0_CSWIZ_SHIFT                     10
#घोषणा VC4_TEX_P0_CMMODE_MASK                     VC4_MASK(9, 9)
#घोषणा VC4_TEX_P0_CMMODE_SHIFT                    9
#घोषणा VC4_TEX_P0_FLIPY_MASK                      VC4_MASK(8, 8)
#घोषणा VC4_TEX_P0_FLIPY_SHIFT                     8
#घोषणा VC4_TEX_P0_TYPE_MASK                       VC4_MASK(7, 4)
#घोषणा VC4_TEX_P0_TYPE_SHIFT                      4
#घोषणा VC4_TEX_P0_MIPLVLS_MASK                    VC4_MASK(3, 0)
#घोषणा VC4_TEX_P0_MIPLVLS_SHIFT                   0

#घोषणा VC4_TEX_P1_TYPE4_MASK                      VC4_MASK(31, 31)
#घोषणा VC4_TEX_P1_TYPE4_SHIFT                     31
#घोषणा VC4_TEX_P1_HEIGHT_MASK                     VC4_MASK(30, 20)
#घोषणा VC4_TEX_P1_HEIGHT_SHIFT                    20
#घोषणा VC4_TEX_P1_ETCFLIP_MASK                    VC4_MASK(19, 19)
#घोषणा VC4_TEX_P1_ETCFLIP_SHIFT                   19
#घोषणा VC4_TEX_P1_WIDTH_MASK                      VC4_MASK(18, 8)
#घोषणा VC4_TEX_P1_WIDTH_SHIFT                     8

#घोषणा VC4_TEX_P1_MAGFILT_MASK                    VC4_MASK(7, 7)
#घोषणा VC4_TEX_P1_MAGFILT_SHIFT                   7
# define VC4_TEX_P1_MAGFILT_LINEAR                 0
# define VC4_TEX_P1_MAGFILT_NEAREST                1

#घोषणा VC4_TEX_P1_MINFILT_MASK                    VC4_MASK(6, 4)
#घोषणा VC4_TEX_P1_MINFILT_SHIFT                   4
# define VC4_TEX_P1_MINFILT_LINEAR                 0
# define VC4_TEX_P1_MINFILT_NEAREST                1
# define VC4_TEX_P1_MINFILT_NEAR_MIP_NEAR          2
# define VC4_TEX_P1_MINFILT_NEAR_MIP_LIN           3
# define VC4_TEX_P1_MINFILT_LIN_MIP_NEAR           4
# define VC4_TEX_P1_MINFILT_LIN_MIP_LIN            5

#घोषणा VC4_TEX_P1_WRAP_T_MASK                     VC4_MASK(3, 2)
#घोषणा VC4_TEX_P1_WRAP_T_SHIFT                    2
#घोषणा VC4_TEX_P1_WRAP_S_MASK                     VC4_MASK(1, 0)
#घोषणा VC4_TEX_P1_WRAP_S_SHIFT                    0
# define VC4_TEX_P1_WRAP_REPEAT                    0
# define VC4_TEX_P1_WRAP_CLAMP                     1
# define VC4_TEX_P1_WRAP_MIRROR                    2
# define VC4_TEX_P1_WRAP_BORDER                    3

#घोषणा VC4_TEX_P2_PTYPE_MASK                      VC4_MASK(31, 30)
#घोषणा VC4_TEX_P2_PTYPE_SHIFT                     30
# define VC4_TEX_P2_PTYPE_IGNORED                  0
# define VC4_TEX_P2_PTYPE_CUBE_MAP_STRIDE          1
# define VC4_TEX_P2_PTYPE_CHILD_IMAGE_DIMENSIONS   2
# define VC4_TEX_P2_PTYPE_CHILD_IMAGE_OFFSETS      3

/* VC4_TEX_P2_PTYPE_CUBE_MAP_STRIDE bits */
#घोषणा VC4_TEX_P2_CMST_MASK                       VC4_MASK(29, 12)
#घोषणा VC4_TEX_P2_CMST_SHIFT                      12
#घोषणा VC4_TEX_P2_BSLOD_MASK                      VC4_MASK(0, 0)
#घोषणा VC4_TEX_P2_BSLOD_SHIFT                     0

/* VC4_TEX_P2_PTYPE_CHILD_IMAGE_DIMENSIONS */
#घोषणा VC4_TEX_P2_CHEIGHT_MASK                    VC4_MASK(22, 12)
#घोषणा VC4_TEX_P2_CHEIGHT_SHIFT                   12
#घोषणा VC4_TEX_P2_CWIDTH_MASK                     VC4_MASK(10, 0)
#घोषणा VC4_TEX_P2_CWIDTH_SHIFT                    0

/* VC4_TEX_P2_PTYPE_CHILD_IMAGE_OFFSETS */
#घोषणा VC4_TEX_P2_CYOFF_MASK                      VC4_MASK(22, 12)
#घोषणा VC4_TEX_P2_CYOFF_SHIFT                     12
#घोषणा VC4_TEX_P2_CXOFF_MASK                      VC4_MASK(10, 0)
#घोषणा VC4_TEX_P2_CXOFF_SHIFT                     0

#पूर्ण_अगर /* VC4_PACKET_H */
