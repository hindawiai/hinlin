<शैली गुरु>
/* radeon_drm.h -- Public header क्रम the radeon driver -*- linux-c -*-
 *
 * Copyright 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Fremont, Calअगरornia.
 * Copyright 2002 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All rights reserved.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Kevin E. Martin <martin@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 *    Keith Whitwell <keith@tungstengraphics.com>
 */

#अगर_अघोषित __RADEON_DRM_H__
#घोषणा __RADEON_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* WARNING: If you change any of these defines, make sure to change the
 * defines in the X server file (radeon_sarea.h)
 */
#अगर_अघोषित __RADEON_SAREA_DEFINES__
#घोषणा __RADEON_SAREA_DEFINES__

/* Old style state flags, required क्रम sarea पूर्णांकerface (1.1 and 1.2
 * clears) and 1.2 drm_vertex2 ioctl.
 */
#घोषणा RADEON_UPLOAD_CONTEXT		0x00000001
#घोषणा RADEON_UPLOAD_VERTFMT		0x00000002
#घोषणा RADEON_UPLOAD_LINE		0x00000004
#घोषणा RADEON_UPLOAD_BUMPMAP		0x00000008
#घोषणा RADEON_UPLOAD_MASKS		0x00000010
#घोषणा RADEON_UPLOAD_VIEWPORT		0x00000020
#घोषणा RADEON_UPLOAD_SETUP		0x00000040
#घोषणा RADEON_UPLOAD_TCL		0x00000080
#घोषणा RADEON_UPLOAD_MISC		0x00000100
#घोषणा RADEON_UPLOAD_TEX0		0x00000200
#घोषणा RADEON_UPLOAD_TEX1		0x00000400
#घोषणा RADEON_UPLOAD_TEX2		0x00000800
#घोषणा RADEON_UPLOAD_TEX0IMAGES	0x00001000
#घोषणा RADEON_UPLOAD_TEX1IMAGES	0x00002000
#घोषणा RADEON_UPLOAD_TEX2IMAGES	0x00004000
#घोषणा RADEON_UPLOAD_CLIPRECTS		0x00008000	/* handled client-side */
#घोषणा RADEON_REQUIRE_QUIESCENCE	0x00010000
#घोषणा RADEON_UPLOAD_ZBIAS		0x00020000	/* version 1.2 and newer */
#घोषणा RADEON_UPLOAD_ALL		0x003effff
#घोषणा RADEON_UPLOAD_CONTEXT_ALL       0x003e01ff

/* New style per-packet identअगरiers क्रम use in cmd_buffer ioctl with
 * the RADEON_EMIT_PACKET command.  Comments relate new packets to old
 * state bits and the packet size:
 */
#घोषणा RADEON_EMIT_PP_MISC                         0	/* context/7 */
#घोषणा RADEON_EMIT_PP_CNTL                         1	/* context/3 */
#घोषणा RADEON_EMIT_RB3D_COLORPITCH                 2	/* context/1 */
#घोषणा RADEON_EMIT_RE_LINE_PATTERN                 3	/* line/2 */
#घोषणा RADEON_EMIT_SE_LINE_WIDTH                   4	/* line/1 */
#घोषणा RADEON_EMIT_PP_LUM_MATRIX                   5	/* bumpmap/1 */
#घोषणा RADEON_EMIT_PP_ROT_MATRIX_0                 6	/* bumpmap/2 */
#घोषणा RADEON_EMIT_RB3D_STENCILREFMASK             7	/* masks/3 */
#घोषणा RADEON_EMIT_SE_VPORT_XSCALE                 8	/* viewport/6 */
#घोषणा RADEON_EMIT_SE_CNTL                         9	/* setup/2 */
#घोषणा RADEON_EMIT_SE_CNTL_STATUS                  10	/* setup/1 */
#घोषणा RADEON_EMIT_RE_MISC                         11	/* misc/1 */
#घोषणा RADEON_EMIT_PP_TXFILTER_0                   12	/* tex0/6 */
#घोषणा RADEON_EMIT_PP_BORDER_COLOR_0               13	/* tex0/1 */
#घोषणा RADEON_EMIT_PP_TXFILTER_1                   14	/* tex1/6 */
#घोषणा RADEON_EMIT_PP_BORDER_COLOR_1               15	/* tex1/1 */
#घोषणा RADEON_EMIT_PP_TXFILTER_2                   16	/* tex2/6 */
#घोषणा RADEON_EMIT_PP_BORDER_COLOR_2               17	/* tex2/1 */
#घोषणा RADEON_EMIT_SE_ZBIAS_FACTOR                 18	/* zbias/2 */
#घोषणा RADEON_EMIT_SE_TCL_OUTPUT_VTX_FMT           19	/* tcl/11 */
#घोषणा RADEON_EMIT_SE_TCL_MATERIAL_EMMISSIVE_RED   20	/* material/17 */
#घोषणा R200_EMIT_PP_TXCBLEND_0                     21	/* tex0/4 */
#घोषणा R200_EMIT_PP_TXCBLEND_1                     22	/* tex1/4 */
#घोषणा R200_EMIT_PP_TXCBLEND_2                     23	/* tex2/4 */
#घोषणा R200_EMIT_PP_TXCBLEND_3                     24	/* tex3/4 */
#घोषणा R200_EMIT_PP_TXCBLEND_4                     25	/* tex4/4 */
#घोषणा R200_EMIT_PP_TXCBLEND_5                     26	/* tex5/4 */
#घोषणा R200_EMIT_PP_TXCBLEND_6                     27	/* /4 */
#घोषणा R200_EMIT_PP_TXCBLEND_7                     28	/* /4 */
#घोषणा R200_EMIT_TCL_LIGHT_MODEL_CTL_0             29	/* tcl/7 */
#घोषणा R200_EMIT_TFACTOR_0                         30	/* tf/7 */
#घोषणा R200_EMIT_VTX_FMT_0                         31	/* vtx/5 */
#घोषणा R200_EMIT_VAP_CTL                           32	/* vap/1 */
#घोषणा R200_EMIT_MATRIX_SELECT_0                   33	/* msl/5 */
#घोषणा R200_EMIT_TEX_PROC_CTL_2                    34	/* tcg/5 */
#घोषणा R200_EMIT_TCL_UCP_VERT_BLEND_CTL            35	/* tcl/1 */
#घोषणा R200_EMIT_PP_TXFILTER_0                     36	/* tex0/6 */
#घोषणा R200_EMIT_PP_TXFILTER_1                     37	/* tex1/6 */
#घोषणा R200_EMIT_PP_TXFILTER_2                     38	/* tex2/6 */
#घोषणा R200_EMIT_PP_TXFILTER_3                     39	/* tex3/6 */
#घोषणा R200_EMIT_PP_TXFILTER_4                     40	/* tex4/6 */
#घोषणा R200_EMIT_PP_TXFILTER_5                     41	/* tex5/6 */
#घोषणा R200_EMIT_PP_TXOFFSET_0                     42	/* tex0/1 */
#घोषणा R200_EMIT_PP_TXOFFSET_1                     43	/* tex1/1 */
#घोषणा R200_EMIT_PP_TXOFFSET_2                     44	/* tex2/1 */
#घोषणा R200_EMIT_PP_TXOFFSET_3                     45	/* tex3/1 */
#घोषणा R200_EMIT_PP_TXOFFSET_4                     46	/* tex4/1 */
#घोषणा R200_EMIT_PP_TXOFFSET_5                     47	/* tex5/1 */
#घोषणा R200_EMIT_VTE_CNTL                          48	/* vte/1 */
#घोषणा R200_EMIT_OUTPUT_VTX_COMP_SEL               49	/* vtx/1 */
#घोषणा R200_EMIT_PP_TAM_DEBUG3                     50	/* tam/1 */
#घोषणा R200_EMIT_PP_CNTL_X                         51	/* cst/1 */
#घोषणा R200_EMIT_RB3D_DEPTHXY_OFFSET               52	/* cst/1 */
#घोषणा R200_EMIT_RE_AUX_SCISSOR_CNTL               53	/* cst/1 */
#घोषणा R200_EMIT_RE_SCISSOR_TL_0                   54	/* cst/2 */
#घोषणा R200_EMIT_RE_SCISSOR_TL_1                   55	/* cst/2 */
#घोषणा R200_EMIT_RE_SCISSOR_TL_2                   56	/* cst/2 */
#घोषणा R200_EMIT_SE_VAP_CNTL_STATUS                57	/* cst/1 */
#घोषणा R200_EMIT_SE_VTX_STATE_CNTL                 58	/* cst/1 */
#घोषणा R200_EMIT_RE_POINTSIZE                      59	/* cst/1 */
#घोषणा R200_EMIT_TCL_INPUT_VTX_VECTOR_ADDR_0       60	/* cst/4 */
#घोषणा R200_EMIT_PP_CUBIC_FACES_0                  61
#घोषणा R200_EMIT_PP_CUBIC_OFFSETS_0                62
#घोषणा R200_EMIT_PP_CUBIC_FACES_1                  63
#घोषणा R200_EMIT_PP_CUBIC_OFFSETS_1                64
#घोषणा R200_EMIT_PP_CUBIC_FACES_2                  65
#घोषणा R200_EMIT_PP_CUBIC_OFFSETS_2                66
#घोषणा R200_EMIT_PP_CUBIC_FACES_3                  67
#घोषणा R200_EMIT_PP_CUBIC_OFFSETS_3                68
#घोषणा R200_EMIT_PP_CUBIC_FACES_4                  69
#घोषणा R200_EMIT_PP_CUBIC_OFFSETS_4                70
#घोषणा R200_EMIT_PP_CUBIC_FACES_5                  71
#घोषणा R200_EMIT_PP_CUBIC_OFFSETS_5                72
#घोषणा RADEON_EMIT_PP_TEX_SIZE_0                   73
#घोषणा RADEON_EMIT_PP_TEX_SIZE_1                   74
#घोषणा RADEON_EMIT_PP_TEX_SIZE_2                   75
#घोषणा R200_EMIT_RB3D_BLENDCOLOR                   76
#घोषणा R200_EMIT_TCL_POINT_SPRITE_CNTL             77
#घोषणा RADEON_EMIT_PP_CUBIC_FACES_0                78
#घोषणा RADEON_EMIT_PP_CUBIC_OFFSETS_T0             79
#घोषणा RADEON_EMIT_PP_CUBIC_FACES_1                80
#घोषणा RADEON_EMIT_PP_CUBIC_OFFSETS_T1             81
#घोषणा RADEON_EMIT_PP_CUBIC_FACES_2                82
#घोषणा RADEON_EMIT_PP_CUBIC_OFFSETS_T2             83
#घोषणा R200_EMIT_PP_TRI_PERF_CNTL                  84
#घोषणा R200_EMIT_PP_AFS_0                          85
#घोषणा R200_EMIT_PP_AFS_1                          86
#घोषणा R200_EMIT_ATF_TFACTOR                       87
#घोषणा R200_EMIT_PP_TXCTLALL_0                     88
#घोषणा R200_EMIT_PP_TXCTLALL_1                     89
#घोषणा R200_EMIT_PP_TXCTLALL_2                     90
#घोषणा R200_EMIT_PP_TXCTLALL_3                     91
#घोषणा R200_EMIT_PP_TXCTLALL_4                     92
#घोषणा R200_EMIT_PP_TXCTLALL_5                     93
#घोषणा R200_EMIT_VAP_PVS_CNTL                      94
#घोषणा RADEON_MAX_STATE_PACKETS                    95

/* Commands understood by cmd_buffer ioctl.  More can be added but
 * obviously these can't be हटाओd or changed:
 */
#घोषणा RADEON_CMD_PACKET      1	/* emit one of the रेजिस्टर packets above */
#घोषणा RADEON_CMD_SCALARS     2	/* emit scalar data */
#घोषणा RADEON_CMD_VECTORS     3	/* emit vector data */
#घोषणा RADEON_CMD_DMA_DISCARD 4	/* discard current dma buf */
#घोषणा RADEON_CMD_PACKET3     5	/* emit hw packet */
#घोषणा RADEON_CMD_PACKET3_CLIP 6	/* emit hw packet wrapped in cliprects */
#घोषणा RADEON_CMD_SCALARS2     7	/* r200 stopgap */
#घोषणा RADEON_CMD_WAIT         8	/* emit hw रुको commands -- note:
					 *  करोesn't make the cpu रुको, just
					 *  the graphics hardware */
#घोषणा RADEON_CMD_VECLINEAR	9       /* another r200 stopgap */

प्रकार जोड़ अणु
	पूर्णांक i;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, pad0, pad1, pad2;
	पूर्ण header;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, packet_id, pad0, pad1;
	पूर्ण packet;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, offset, stride, count;
	पूर्ण scalars;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, offset, stride, count;
	पूर्ण vectors;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, addr_lo, addr_hi, count;
	पूर्ण veclinear;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, buf_idx, pad0, pad1;
	पूर्ण dma;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, flags, pad0, pad1;
	पूर्ण रुको;
पूर्ण drm_radeon_cmd_header_t;

#घोषणा RADEON_WAIT_2D  0x1
#घोषणा RADEON_WAIT_3D  0x2

/* Allowed parameters क्रम R300_CMD_PACKET3
 */
#घोषणा R300_CMD_PACKET3_CLEAR		0
#घोषणा R300_CMD_PACKET3_RAW		1

/* Commands understood by cmd_buffer ioctl क्रम R300.
 * The पूर्णांकerface has not been stabilized, so some of these may be हटाओd
 * and eventually reordered beक्रमe stabilization.
 */
#घोषणा R300_CMD_PACKET0		1
#घोषणा R300_CMD_VPU			2	/* emit vertex program upload */
#घोषणा R300_CMD_PACKET3		3	/* emit a packet3 */
#घोषणा R300_CMD_END3D			4	/* emit sequence ending 3d rendering */
#घोषणा R300_CMD_CP_DELAY		5
#घोषणा R300_CMD_DMA_DISCARD		6
#घोषणा R300_CMD_WAIT			7
#	define R300_WAIT_2D		0x1
#	define R300_WAIT_3D		0x2
/* these two defines are DOING IT WRONG - however
 * we have userspace which relies on using these.
 * The रुको पूर्णांकerface is backwards compat new 
 * code should use the NEW_WAIT defines below
 * THESE ARE NOT BIT FIELDS
 */
#	define R300_WAIT_2D_CLEAN	0x3
#	define R300_WAIT_3D_CLEAN	0x4

#	define R300_NEW_WAIT_2D_3D	0x3
#	define R300_NEW_WAIT_2D_2D_CLEAN	0x4
#	define R300_NEW_WAIT_3D_3D_CLEAN	0x6
#	define R300_NEW_WAIT_2D_2D_CLEAN_3D_3D_CLEAN	0x8

#घोषणा R300_CMD_SCRATCH		8
#घोषणा R300_CMD_R500FP                 9

प्रकार जोड़ अणु
	अचिन्हित पूर्णांक u;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, pad0, pad1, pad2;
	पूर्ण header;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, count, reglo, reghi;
	पूर्ण packet0;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, count, adrlo, adrhi;
	पूर्ण vpu;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, packet, pad0, pad1;
	पूर्ण packet3;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, packet;
		अचिन्हित लघु count;	/* amount of packet2 to emit */
	पूर्ण delay;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, buf_idx, pad0, pad1;
	पूर्ण dma;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, flags, pad0, pad1;
	पूर्ण रुको;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, reg, n_bufs, flags;
	पूर्ण scratch;
	काष्ठा अणु
		अचिन्हित अक्षर cmd_type, count, adrlo, adrhi_flags;
	पूर्ण r500fp;
पूर्ण drm_r300_cmd_header_t;

#घोषणा RADEON_FRONT			0x1
#घोषणा RADEON_BACK			0x2
#घोषणा RADEON_DEPTH			0x4
#घोषणा RADEON_STENCIL			0x8
#घोषणा RADEON_CLEAR_FASTZ		0x80000000
#घोषणा RADEON_USE_HIERZ		0x40000000
#घोषणा RADEON_USE_COMP_ZBUF		0x20000000

#घोषणा R500FP_CONSTANT_TYPE  (1 << 1)
#घोषणा R500FP_CONSTANT_CLAMP (1 << 2)

/* Primitive types
 */
#घोषणा RADEON_POINTS			0x1
#घोषणा RADEON_LINES			0x2
#घोषणा RADEON_LINE_STRIP		0x3
#घोषणा RADEON_TRIANGLES		0x4
#घोषणा RADEON_TRIANGLE_FAN		0x5
#घोषणा RADEON_TRIANGLE_STRIP		0x6

/* Vertex/indirect buffer size
 */
#घोषणा RADEON_BUFFER_SIZE		65536

/* Byte offsets क्रम indirect buffer data
 */
#घोषणा RADEON_INDEX_PRIM_OFFSET	20

#घोषणा RADEON_SCRATCH_REG_OFFSET	32

#घोषणा R600_SCRATCH_REG_OFFSET         256

#घोषणा RADEON_NR_SAREA_CLIPRECTS	12

/* There are 2 heaps (local/GART).  Each region within a heap is a
 * minimum of 64k, and there are at most 64 of them per heap.
 */
#घोषणा RADEON_LOCAL_TEX_HEAP		0
#घोषणा RADEON_GART_TEX_HEAP		1
#घोषणा RADEON_NR_TEX_HEAPS		2
#घोषणा RADEON_NR_TEX_REGIONS		64
#घोषणा RADEON_LOG_TEX_GRANULARITY	16

#घोषणा RADEON_MAX_TEXTURE_LEVELS	12
#घोषणा RADEON_MAX_TEXTURE_UNITS	3

#घोषणा RADEON_MAX_SURFACES		8

/* Blits have strict offset rules.  All blit offset must be aligned on
 * a 1K-byte boundary.
 */
#घोषणा RADEON_OFFSET_SHIFT             10
#घोषणा RADEON_OFFSET_ALIGN             (1 << RADEON_OFFSET_SHIFT)
#घोषणा RADEON_OFFSET_MASK              (RADEON_OFFSET_ALIGN - 1)

#पूर्ण_अगर				/* __RADEON_SAREA_DEFINES__ */

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक red;
	अचिन्हित पूर्णांक green;
	अचिन्हित पूर्णांक blue;
	अचिन्हित पूर्णांक alpha;
पूर्ण radeon_color_regs_t;

प्रकार काष्ठा अणु
	/* Context state */
	अचिन्हित पूर्णांक pp_misc;	/* 0x1c14 */
	अचिन्हित पूर्णांक pp_fog_color;
	अचिन्हित पूर्णांक re_solid_color;
	अचिन्हित पूर्णांक rb3d_blendcntl;
	अचिन्हित पूर्णांक rb3d_depthoffset;
	अचिन्हित पूर्णांक rb3d_depthpitch;
	अचिन्हित पूर्णांक rb3d_zstencilcntl;

	अचिन्हित पूर्णांक pp_cntl;	/* 0x1c38 */
	अचिन्हित पूर्णांक rb3d_cntl;
	अचिन्हित पूर्णांक rb3d_coloroffset;
	अचिन्हित पूर्णांक re_width_height;
	अचिन्हित पूर्णांक rb3d_colorpitch;
	अचिन्हित पूर्णांक se_cntl;

	/* Vertex क्रमmat state */
	अचिन्हित पूर्णांक se_coord_fmt;	/* 0x1c50 */

	/* Line state */
	अचिन्हित पूर्णांक re_line_pattern;	/* 0x1cd0 */
	अचिन्हित पूर्णांक re_line_state;

	अचिन्हित पूर्णांक se_line_width;	/* 0x1db8 */

	/* Bumpmap state */
	अचिन्हित पूर्णांक pp_lum_matrix;	/* 0x1d00 */

	अचिन्हित पूर्णांक pp_rot_matrix_0;	/* 0x1d58 */
	अचिन्हित पूर्णांक pp_rot_matrix_1;

	/* Mask state */
	अचिन्हित पूर्णांक rb3d_stencilrefmask;	/* 0x1d7c */
	अचिन्हित पूर्णांक rb3d_ropcntl;
	अचिन्हित पूर्णांक rb3d_planemask;

	/* Viewport state */
	अचिन्हित पूर्णांक se_vport_xscale;	/* 0x1d98 */
	अचिन्हित पूर्णांक se_vport_xoffset;
	अचिन्हित पूर्णांक se_vport_yscale;
	अचिन्हित पूर्णांक se_vport_yoffset;
	अचिन्हित पूर्णांक se_vport_zscale;
	अचिन्हित पूर्णांक se_vport_zoffset;

	/* Setup state */
	अचिन्हित पूर्णांक se_cntl_status;	/* 0x2140 */

	/* Misc state */
	अचिन्हित पूर्णांक re_top_left;	/* 0x26c0 */
	अचिन्हित पूर्णांक re_misc;
पूर्ण drm_radeon_context_regs_t;

प्रकार काष्ठा अणु
	/* Zbias state */
	अचिन्हित पूर्णांक se_zbias_factor;	/* 0x1dac */
	अचिन्हित पूर्णांक se_zbias_स्थिरant;
पूर्ण drm_radeon_context2_regs_t;

/* Setup रेजिस्टरs क्रम each texture unit
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक pp_txfilter;
	अचिन्हित पूर्णांक pp_txक्रमmat;
	अचिन्हित पूर्णांक pp_txoffset;
	अचिन्हित पूर्णांक pp_txcblend;
	अचिन्हित पूर्णांक pp_txablend;
	अचिन्हित पूर्णांक pp_tfactor;
	अचिन्हित पूर्णांक pp_border_color;
पूर्ण drm_radeon_texture_regs_t;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक finish;
	अचिन्हित पूर्णांक prim:8;
	अचिन्हित पूर्णांक stateidx:8;
	अचिन्हित पूर्णांक numverts:16;	/* overloaded as offset/64 क्रम elt prims */
	अचिन्हित पूर्णांक vc_क्रमmat;	/* vertex क्रमmat */
पूर्ण drm_radeon_prim_t;

प्रकार काष्ठा अणु
	drm_radeon_context_regs_t context;
	drm_radeon_texture_regs_t tex[RADEON_MAX_TEXTURE_UNITS];
	drm_radeon_context2_regs_t context2;
	अचिन्हित पूर्णांक dirty;
पूर्ण drm_radeon_state_t;

प्रकार काष्ठा अणु
	/* The channel क्रम communication of state inक्रमmation to the
	 * kernel on firing a vertex buffer with either of the
	 * obsoleted vertex/index ioctls.
	 */
	drm_radeon_context_regs_t context_state;
	drm_radeon_texture_regs_t tex_state[RADEON_MAX_TEXTURE_UNITS];
	अचिन्हित पूर्णांक dirty;
	अचिन्हित पूर्णांक vertsize;
	अचिन्हित पूर्णांक vc_क्रमmat;

	/* The current cliprects, or a subset thereof.
	 */
	काष्ठा drm_clip_rect boxes[RADEON_NR_SAREA_CLIPRECTS];
	अचिन्हित पूर्णांक nbox;

	/* Counters क्रम client-side throttling of rendering clients.
	 */
	अचिन्हित पूर्णांक last_frame;
	अचिन्हित पूर्णांक last_dispatch;
	अचिन्हित पूर्णांक last_clear;

	काष्ठा drm_tex_region tex_list[RADEON_NR_TEX_HEAPS][RADEON_NR_TEX_REGIONS +
						       1];
	अचिन्हित पूर्णांक tex_age[RADEON_NR_TEX_HEAPS];
	पूर्णांक ctx_owner;
	पूर्णांक pfState;		/* number of 3d winकरोws (0,1,2ormore) */
	पूर्णांक pfCurrentPage;	/* which buffer is being displayed? */
	पूर्णांक crtc2_base;		/* CRTC2 frame offset */
	पूर्णांक tiling_enabled;	/* set by drm, पढ़ो by 2d + 3d clients */
पूर्ण drm_radeon_sarea_t;

/* WARNING: If you change any of these defines, make sure to change the
 * defines in the Xserver file (xf86drmRadeon.h)
 *
 * KW: actually it's illegal to change any of this (backwards compatibility).
 */

/* Radeon specअगरic ioctls
 * The device specअगरic ioctl range is 0x40 to 0x79.
 */
#घोषणा DRM_RADEON_CP_INIT    0x00
#घोषणा DRM_RADEON_CP_START   0x01
#घोषणा DRM_RADEON_CP_STOP    0x02
#घोषणा DRM_RADEON_CP_RESET   0x03
#घोषणा DRM_RADEON_CP_IDLE    0x04
#घोषणा DRM_RADEON_RESET      0x05
#घोषणा DRM_RADEON_FULLSCREEN 0x06
#घोषणा DRM_RADEON_SWAP       0x07
#घोषणा DRM_RADEON_CLEAR      0x08
#घोषणा DRM_RADEON_VERTEX     0x09
#घोषणा DRM_RADEON_INDICES    0x0A
#घोषणा DRM_RADEON_NOT_USED
#घोषणा DRM_RADEON_STIPPLE    0x0C
#घोषणा DRM_RADEON_INसूचीECT   0x0D
#घोषणा DRM_RADEON_TEXTURE    0x0E
#घोषणा DRM_RADEON_VERTEX2    0x0F
#घोषणा DRM_RADEON_CMDBUF     0x10
#घोषणा DRM_RADEON_GETPARAM   0x11
#घोषणा DRM_RADEON_FLIP       0x12
#घोषणा DRM_RADEON_ALLOC      0x13
#घोषणा DRM_RADEON_FREE       0x14
#घोषणा DRM_RADEON_INIT_HEAP  0x15
#घोषणा DRM_RADEON_IRQ_EMIT   0x16
#घोषणा DRM_RADEON_IRQ_WAIT   0x17
#घोषणा DRM_RADEON_CP_RESUME  0x18
#घोषणा DRM_RADEON_SETPARAM   0x19
#घोषणा DRM_RADEON_SURF_ALLOC 0x1a
#घोषणा DRM_RADEON_SURF_FREE  0x1b
/* KMS ioctl */
#घोषणा DRM_RADEON_GEM_INFO		0x1c
#घोषणा DRM_RADEON_GEM_CREATE		0x1d
#घोषणा DRM_RADEON_GEM_MMAP		0x1e
#घोषणा DRM_RADEON_GEM_PREAD		0x21
#घोषणा DRM_RADEON_GEM_PWRITE		0x22
#घोषणा DRM_RADEON_GEM_SET_DOMAIN	0x23
#घोषणा DRM_RADEON_GEM_WAIT_IDLE	0x24
#घोषणा DRM_RADEON_CS			0x26
#घोषणा DRM_RADEON_INFO			0x27
#घोषणा DRM_RADEON_GEM_SET_TILING	0x28
#घोषणा DRM_RADEON_GEM_GET_TILING	0x29
#घोषणा DRM_RADEON_GEM_BUSY		0x2a
#घोषणा DRM_RADEON_GEM_VA		0x2b
#घोषणा DRM_RADEON_GEM_OP		0x2c
#घोषणा DRM_RADEON_GEM_USERPTR		0x2d

#घोषणा DRM_IOCTL_RADEON_CP_INIT    DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_CP_INIT, drm_radeon_init_t)
#घोषणा DRM_IOCTL_RADEON_CP_START   DRM_IO(  DRM_COMMAND_BASE + DRM_RADEON_CP_START)
#घोषणा DRM_IOCTL_RADEON_CP_STOP    DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_CP_STOP, drm_radeon_cp_stop_t)
#घोषणा DRM_IOCTL_RADEON_CP_RESET   DRM_IO(  DRM_COMMAND_BASE + DRM_RADEON_CP_RESET)
#घोषणा DRM_IOCTL_RADEON_CP_IDLE    DRM_IO(  DRM_COMMAND_BASE + DRM_RADEON_CP_IDLE)
#घोषणा DRM_IOCTL_RADEON_RESET      DRM_IO(  DRM_COMMAND_BASE + DRM_RADEON_RESET)
#घोषणा DRM_IOCTL_RADEON_FULLSCREEN DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_FULLSCREEN, drm_radeon_fullscreen_t)
#घोषणा DRM_IOCTL_RADEON_SWAP       DRM_IO(  DRM_COMMAND_BASE + DRM_RADEON_SWAP)
#घोषणा DRM_IOCTL_RADEON_CLEAR      DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_CLEAR, drm_radeon_clear_t)
#घोषणा DRM_IOCTL_RADEON_VERTEX     DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_VERTEX, drm_radeon_vertex_t)
#घोषणा DRM_IOCTL_RADEON_INDICES    DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_INDICES, drm_radeon_indices_t)
#घोषणा DRM_IOCTL_RADEON_STIPPLE    DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_STIPPLE, drm_radeon_stipple_t)
#घोषणा DRM_IOCTL_RADEON_INसूचीECT   DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_INसूचीECT, drm_radeon_indirect_t)
#घोषणा DRM_IOCTL_RADEON_TEXTURE    DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_TEXTURE, drm_radeon_texture_t)
#घोषणा DRM_IOCTL_RADEON_VERTEX2    DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_VERTEX2, drm_radeon_vertex2_t)
#घोषणा DRM_IOCTL_RADEON_CMDBUF     DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_CMDBUF, drm_radeon_cmd_buffer_t)
#घोषणा DRM_IOCTL_RADEON_GETPARAM   DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GETPARAM, drm_radeon_getparam_t)
#घोषणा DRM_IOCTL_RADEON_FLIP       DRM_IO(  DRM_COMMAND_BASE + DRM_RADEON_FLIP)
#घोषणा DRM_IOCTL_RADEON_ALLOC      DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_ALLOC, drm_radeon_mem_alloc_t)
#घोषणा DRM_IOCTL_RADEON_FREE       DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_FREE, drm_radeon_mem_मुक्त_t)
#घोषणा DRM_IOCTL_RADEON_INIT_HEAP  DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_INIT_HEAP, drm_radeon_mem_init_heap_t)
#घोषणा DRM_IOCTL_RADEON_IRQ_EMIT   DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_IRQ_EMIT, drm_radeon_irq_emit_t)
#घोषणा DRM_IOCTL_RADEON_IRQ_WAIT   DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_IRQ_WAIT, drm_radeon_irq_रुको_t)
#घोषणा DRM_IOCTL_RADEON_CP_RESUME  DRM_IO(  DRM_COMMAND_BASE + DRM_RADEON_CP_RESUME)
#घोषणा DRM_IOCTL_RADEON_SETPARAM   DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_SETPARAM, drm_radeon_setparam_t)
#घोषणा DRM_IOCTL_RADEON_SURF_ALLOC DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_SURF_ALLOC, drm_radeon_surface_alloc_t)
#घोषणा DRM_IOCTL_RADEON_SURF_FREE  DRM_IOW( DRM_COMMAND_BASE + DRM_RADEON_SURF_FREE, drm_radeon_surface_मुक्त_t)
/* KMS */
#घोषणा DRM_IOCTL_RADEON_GEM_INFO	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_INFO, काष्ठा drm_radeon_gem_info)
#घोषणा DRM_IOCTL_RADEON_GEM_CREATE	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_CREATE, काष्ठा drm_radeon_gem_create)
#घोषणा DRM_IOCTL_RADEON_GEM_MMAP	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_MMAP, काष्ठा drm_radeon_gem_mmap)
#घोषणा DRM_IOCTL_RADEON_GEM_PREAD	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_PREAD, काष्ठा drm_radeon_gem_pपढ़ो)
#घोषणा DRM_IOCTL_RADEON_GEM_PWRITE	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_PWRITE, काष्ठा drm_radeon_gem_pग_लिखो)
#घोषणा DRM_IOCTL_RADEON_GEM_SET_DOMAIN	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_SET_DOMAIN, काष्ठा drm_radeon_gem_set_करोमुख्य)
#घोषणा DRM_IOCTL_RADEON_GEM_WAIT_IDLE	DRM_IOW(DRM_COMMAND_BASE + DRM_RADEON_GEM_WAIT_IDLE, काष्ठा drm_radeon_gem_रुको_idle)
#घोषणा DRM_IOCTL_RADEON_CS		DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_CS, काष्ठा drm_radeon_cs)
#घोषणा DRM_IOCTL_RADEON_INFO		DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_INFO, काष्ठा drm_radeon_info)
#घोषणा DRM_IOCTL_RADEON_GEM_SET_TILING	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_SET_TILING, काष्ठा drm_radeon_gem_set_tiling)
#घोषणा DRM_IOCTL_RADEON_GEM_GET_TILING	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_GET_TILING, काष्ठा drm_radeon_gem_get_tiling)
#घोषणा DRM_IOCTL_RADEON_GEM_BUSY	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_BUSY, काष्ठा drm_radeon_gem_busy)
#घोषणा DRM_IOCTL_RADEON_GEM_VA		DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_VA, काष्ठा drm_radeon_gem_va)
#घोषणा DRM_IOCTL_RADEON_GEM_OP		DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_OP, काष्ठा drm_radeon_gem_op)
#घोषणा DRM_IOCTL_RADEON_GEM_USERPTR	DRM_IOWR(DRM_COMMAND_BASE + DRM_RADEON_GEM_USERPTR, काष्ठा drm_radeon_gem_userptr)

प्रकार काष्ठा drm_radeon_init अणु
	क्रमागत अणु
		RADEON_INIT_CP = 0x01,
		RADEON_CLEANUP_CP = 0x02,
		RADEON_INIT_R200_CP = 0x03,
		RADEON_INIT_R300_CP = 0x04,
		RADEON_INIT_R600_CP = 0x05
	पूर्ण func;
	अचिन्हित दीर्घ sarea_priv_offset;
	पूर्णांक is_pci;
	पूर्णांक cp_mode;
	पूर्णांक gart_size;
	पूर्णांक ring_size;
	पूर्णांक usec_समयout;

	अचिन्हित पूर्णांक fb_bpp;
	अचिन्हित पूर्णांक front_offset, front_pitch;
	अचिन्हित पूर्णांक back_offset, back_pitch;
	अचिन्हित पूर्णांक depth_bpp;
	अचिन्हित पूर्णांक depth_offset, depth_pitch;

	अचिन्हित दीर्घ fb_offset;
	अचिन्हित दीर्घ mmio_offset;
	अचिन्हित दीर्घ ring_offset;
	अचिन्हित दीर्घ ring_rptr_offset;
	अचिन्हित दीर्घ buffers_offset;
	अचिन्हित दीर्घ gart_textures_offset;
पूर्ण drm_radeon_init_t;

प्रकार काष्ठा drm_radeon_cp_stop अणु
	पूर्णांक flush;
	पूर्णांक idle;
पूर्ण drm_radeon_cp_stop_t;

प्रकार काष्ठा drm_radeon_fullscreen अणु
	क्रमागत अणु
		RADEON_INIT_FULLSCREEN = 0x01,
		RADEON_CLEANUP_FULLSCREEN = 0x02
	पूर्ण func;
पूर्ण drm_radeon_fullscreen_t;

#घोषणा CLEAR_X1	0
#घोषणा CLEAR_Y1	1
#घोषणा CLEAR_X2	2
#घोषणा CLEAR_Y2	3
#घोषणा CLEAR_DEPTH	4

प्रकार जोड़ drm_radeon_clear_rect अणु
	भग्न f[5];
	अचिन्हित पूर्णांक ui[5];
पूर्ण drm_radeon_clear_rect_t;

प्रकार काष्ठा drm_radeon_clear अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक clear_color;
	अचिन्हित पूर्णांक clear_depth;
	अचिन्हित पूर्णांक color_mask;
	अचिन्हित पूर्णांक depth_mask;	/* misnamed field:  should be stencil */
	drm_radeon_clear_rect_t __user *depth_boxes;
पूर्ण drm_radeon_clear_t;

प्रकार काष्ठा drm_radeon_vertex अणु
	पूर्णांक prim;
	पूर्णांक idx;		/* Index of vertex buffer */
	पूर्णांक count;		/* Number of vertices in buffer */
	पूर्णांक discard;		/* Client finished with buffer? */
पूर्ण drm_radeon_vertex_t;

प्रकार काष्ठा drm_radeon_indices अणु
	पूर्णांक prim;
	पूर्णांक idx;
	पूर्णांक start;
	पूर्णांक end;
	पूर्णांक discard;		/* Client finished with buffer? */
पूर्ण drm_radeon_indices_t;

/* v1.2 - obsoletes drm_radeon_vertex and drm_radeon_indices
 *      - allows multiple primitives and state changes in a single ioctl
 *      - supports driver change to emit native primitives
 */
प्रकार काष्ठा drm_radeon_vertex2 अणु
	पूर्णांक idx;		/* Index of vertex buffer */
	पूर्णांक discard;		/* Client finished with buffer? */
	पूर्णांक nr_states;
	drm_radeon_state_t __user *state;
	पूर्णांक nr_prims;
	drm_radeon_prim_t __user *prim;
पूर्ण drm_radeon_vertex2_t;

/* v1.3 - obsoletes drm_radeon_vertex2
 *      - allows arbitrarily large cliprect list
 *      - allows updating of tcl packet, vector and scalar state
 *      - allows memory-efficient description of state updates
 *      - allows state to be emitted without a primitive
 *           (क्रम clears, ctx चयनes)
 *      - allows more than one dma buffer to be referenced per ioctl
 *      - supports tcl driver
 *      - may be extended in future versions with new cmd types, packets
 */
प्रकार काष्ठा drm_radeon_cmd_buffer अणु
	पूर्णांक bufsz;
	अक्षर __user *buf;
	पूर्णांक nbox;
	काष्ठा drm_clip_rect __user *boxes;
पूर्ण drm_radeon_cmd_buffer_t;

प्रकार काष्ठा drm_radeon_tex_image अणु
	अचिन्हित पूर्णांक x, y;	/* Blit coordinates */
	अचिन्हित पूर्णांक width, height;
	स्थिर व्योम __user *data;
पूर्ण drm_radeon_tex_image_t;

प्रकार काष्ठा drm_radeon_texture अणु
	अचिन्हित पूर्णांक offset;
	पूर्णांक pitch;
	पूर्णांक क्रमmat;
	पूर्णांक width;		/* Texture image coordinates */
	पूर्णांक height;
	drm_radeon_tex_image_t __user *image;
पूर्ण drm_radeon_texture_t;

प्रकार काष्ठा drm_radeon_stipple अणु
	अचिन्हित पूर्णांक __user *mask;
पूर्ण drm_radeon_stipple_t;

प्रकार काष्ठा drm_radeon_indirect अणु
	पूर्णांक idx;
	पूर्णांक start;
	पूर्णांक end;
	पूर्णांक discard;
पूर्ण drm_radeon_indirect_t;

/* क्रमागत क्रम card type parameters */
#घोषणा RADEON_CARD_PCI 0
#घोषणा RADEON_CARD_AGP 1
#घोषणा RADEON_CARD_PCIE 2

/* 1.3: An ioctl to get parameters that aren't available to the 3d
 * client any other way.
 */
#घोषणा RADEON_PARAM_GART_BUFFER_OFFSET    1	/* card offset of 1st GART buffer */
#घोषणा RADEON_PARAM_LAST_FRAME            2
#घोषणा RADEON_PARAM_LAST_DISPATCH         3
#घोषणा RADEON_PARAM_LAST_CLEAR            4
/* Added with DRM version 1.6. */
#घोषणा RADEON_PARAM_IRQ_NR                5
#घोषणा RADEON_PARAM_GART_BASE             6	/* card offset of GART base */
/* Added with DRM version 1.8. */
#घोषणा RADEON_PARAM_REGISTER_HANDLE       7	/* क्रम drmMap() */
#घोषणा RADEON_PARAM_STATUS_HANDLE         8
#घोषणा RADEON_PARAM_SAREA_HANDLE          9
#घोषणा RADEON_PARAM_GART_TEX_HANDLE       10
#घोषणा RADEON_PARAM_SCRATCH_OFFSET        11
#घोषणा RADEON_PARAM_CARD_TYPE             12
#घोषणा RADEON_PARAM_VBLANK_CRTC           13   /* VBLANK CRTC */
#घोषणा RADEON_PARAM_FB_LOCATION           14   /* FB location */
#घोषणा RADEON_PARAM_NUM_GB_PIPES          15   /* num GB pipes */
#घोषणा RADEON_PARAM_DEVICE_ID             16
#घोषणा RADEON_PARAM_NUM_Z_PIPES           17   /* num Z pipes */

प्रकार काष्ठा drm_radeon_getparam अणु
	पूर्णांक param;
	व्योम __user *value;
पूर्ण drm_radeon_getparam_t;

/* 1.6: Set up a memory manager क्रम regions of shared memory:
 */
#घोषणा RADEON_MEM_REGION_GART 1
#घोषणा RADEON_MEM_REGION_FB   2

प्रकार काष्ठा drm_radeon_mem_alloc अणु
	पूर्णांक region;
	पूर्णांक alignment;
	पूर्णांक size;
	पूर्णांक __user *region_offset;	/* offset from start of fb or GART */
पूर्ण drm_radeon_mem_alloc_t;

प्रकार काष्ठा drm_radeon_mem_मुक्त अणु
	पूर्णांक region;
	पूर्णांक region_offset;
पूर्ण drm_radeon_mem_मुक्त_t;

प्रकार काष्ठा drm_radeon_mem_init_heap अणु
	पूर्णांक region;
	पूर्णांक size;
	पूर्णांक start;
पूर्ण drm_radeon_mem_init_heap_t;

/* 1.6: Userspace can request & रुको on irq's:
 */
प्रकार काष्ठा drm_radeon_irq_emit अणु
	पूर्णांक __user *irq_seq;
पूर्ण drm_radeon_irq_emit_t;

प्रकार काष्ठा drm_radeon_irq_रुको अणु
	पूर्णांक irq_seq;
पूर्ण drm_radeon_irq_रुको_t;

/* 1.10: Clients tell the DRM where they think the framebuffer is located in
 * the card's address space, via a new generic ioctl to set parameters
 */

प्रकार काष्ठा drm_radeon_setparam अणु
	अचिन्हित पूर्णांक param;
	__s64 value;
पूर्ण drm_radeon_setparam_t;

#घोषणा RADEON_SETPARAM_FB_LOCATION    1	/* determined framebuffer location */
#घोषणा RADEON_SETPARAM_SWITCH_TILING  2	/* enable/disable color tiling */
#घोषणा RADEON_SETPARAM_PCIGART_LOCATION 3	/* PCI Gart Location */
#घोषणा RADEON_SETPARAM_NEW_MEMMAP 4		/* Use new memory map */
#घोषणा RADEON_SETPARAM_PCIGART_TABLE_SIZE 5    /* PCI GART Table Size */
#घोषणा RADEON_SETPARAM_VBLANK_CRTC 6           /* VBLANK CRTC */
/* 1.14: Clients can allocate/मुक्त a surface
 */
प्रकार काष्ठा drm_radeon_surface_alloc अणु
	अचिन्हित पूर्णांक address;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक flags;
पूर्ण drm_radeon_surface_alloc_t;

प्रकार काष्ठा drm_radeon_surface_मुक्त अणु
	अचिन्हित पूर्णांक address;
पूर्ण drm_radeon_surface_मुक्त_t;

#घोषणा	DRM_RADEON_VBLANK_CRTC1		1
#घोषणा	DRM_RADEON_VBLANK_CRTC2		2

/*
 * Kernel modesetting world below.
 */
#घोषणा RADEON_GEM_DOMAIN_CPU		0x1
#घोषणा RADEON_GEM_DOMAIN_GTT		0x2
#घोषणा RADEON_GEM_DOMAIN_VRAM		0x4

काष्ठा drm_radeon_gem_info अणु
	__u64	gart_size;
	__u64	vram_size;
	__u64	vram_visible;
पूर्ण;

#घोषणा RADEON_GEM_NO_BACKING_STORE	(1 << 0)
#घोषणा RADEON_GEM_GTT_UC		(1 << 1)
#घोषणा RADEON_GEM_GTT_WC		(1 << 2)
/* BO is expected to be accessed by the CPU */
#घोषणा RADEON_GEM_CPU_ACCESS		(1 << 3)
/* CPU access is not expected to work क्रम this BO */
#घोषणा RADEON_GEM_NO_CPU_ACCESS	(1 << 4)

काष्ठा drm_radeon_gem_create अणु
	__u64	size;
	__u64	alignment;
	__u32	handle;
	__u32	initial_करोमुख्य;
	__u32	flags;
पूर्ण;

/*
 * This is not a reliable API and you should expect it to fail क्रम any
 * number of reasons and have fallback path that करो not use userptr to
 * perक्रमm any operation.
 */
#घोषणा RADEON_GEM_USERPTR_READONLY	(1 << 0)
#घोषणा RADEON_GEM_USERPTR_ANONONLY	(1 << 1)
#घोषणा RADEON_GEM_USERPTR_VALIDATE	(1 << 2)
#घोषणा RADEON_GEM_USERPTR_REGISTER	(1 << 3)

काष्ठा drm_radeon_gem_userptr अणु
	__u64		addr;
	__u64		size;
	__u32		flags;
	__u32		handle;
पूर्ण;

#घोषणा RADEON_TILING_MACRO				0x1
#घोषणा RADEON_TILING_MICRO				0x2
#घोषणा RADEON_TILING_SWAP_16BIT			0x4
#घोषणा RADEON_TILING_SWAP_32BIT			0x8
/* this object requires a surface when mapped - i.e. front buffer */
#घोषणा RADEON_TILING_SURFACE				0x10
#घोषणा RADEON_TILING_MICRO_SQUARE			0x20
#घोषणा RADEON_TILING_EG_BANKW_SHIFT			8
#घोषणा RADEON_TILING_EG_BANKW_MASK			0xf
#घोषणा RADEON_TILING_EG_BANKH_SHIFT			12
#घोषणा RADEON_TILING_EG_BANKH_MASK			0xf
#घोषणा RADEON_TILING_EG_MACRO_TILE_ASPECT_SHIFT	16
#घोषणा RADEON_TILING_EG_MACRO_TILE_ASPECT_MASK		0xf
#घोषणा RADEON_TILING_EG_TILE_SPLIT_SHIFT		24
#घोषणा RADEON_TILING_EG_TILE_SPLIT_MASK		0xf
#घोषणा RADEON_TILING_EG_STENCIL_TILE_SPLIT_SHIFT	28
#घोषणा RADEON_TILING_EG_STENCIL_TILE_SPLIT_MASK	0xf

काष्ठा drm_radeon_gem_set_tiling अणु
	__u32	handle;
	__u32	tiling_flags;
	__u32	pitch;
पूर्ण;

काष्ठा drm_radeon_gem_get_tiling अणु
	__u32	handle;
	__u32	tiling_flags;
	__u32	pitch;
पूर्ण;

काष्ठा drm_radeon_gem_mmap अणु
	__u32	handle;
	__u32	pad;
	__u64	offset;
	__u64	size;
	__u64	addr_ptr;
पूर्ण;

काष्ठा drm_radeon_gem_set_करोमुख्य अणु
	__u32	handle;
	__u32	पढ़ो_करोमुख्यs;
	__u32	ग_लिखो_करोमुख्य;
पूर्ण;

काष्ठा drm_radeon_gem_रुको_idle अणु
	__u32	handle;
	__u32	pad;
पूर्ण;

काष्ठा drm_radeon_gem_busy अणु
	__u32	handle;
	__u32        करोमुख्य;
पूर्ण;

काष्ठा drm_radeon_gem_pपढ़ो अणु
	/** Handle क्रम the object being पढ़ो. */
	__u32 handle;
	__u32 pad;
	/** Offset पूर्णांकo the object to पढ़ो from */
	__u64 offset;
	/** Length of data to पढ़ो */
	__u64 size;
	/** Poपूर्णांकer to ग_लिखो the data पूर्णांकo. */
	/* व्योम *, but poपूर्णांकers are not 32/64 compatible */
	__u64 data_ptr;
पूर्ण;

काष्ठा drm_radeon_gem_pग_लिखो अणु
	/** Handle क्रम the object being written to. */
	__u32 handle;
	__u32 pad;
	/** Offset पूर्णांकo the object to ग_लिखो to */
	__u64 offset;
	/** Length of data to ग_लिखो */
	__u64 size;
	/** Poपूर्णांकer to पढ़ो the data from. */
	/* व्योम *, but poपूर्णांकers are not 32/64 compatible */
	__u64 data_ptr;
पूर्ण;

/* Sets or वापसs a value associated with a buffer. */
काष्ठा drm_radeon_gem_op अणु
	__u32	handle; /* buffer */
	__u32	op;     /* RADEON_GEM_OP_* */
	__u64	value;  /* input or वापस value */
पूर्ण;

#घोषणा RADEON_GEM_OP_GET_INITIAL_DOMAIN	0
#घोषणा RADEON_GEM_OP_SET_INITIAL_DOMAIN	1

#घोषणा RADEON_VA_MAP			1
#घोषणा RADEON_VA_UNMAP			2

#घोषणा RADEON_VA_RESULT_OK		0
#घोषणा RADEON_VA_RESULT_ERROR		1
#घोषणा RADEON_VA_RESULT_VA_EXIST	2

#घोषणा RADEON_VM_PAGE_VALID		(1 << 0)
#घोषणा RADEON_VM_PAGE_READABLE		(1 << 1)
#घोषणा RADEON_VM_PAGE_WRITEABLE	(1 << 2)
#घोषणा RADEON_VM_PAGE_SYSTEM		(1 << 3)
#घोषणा RADEON_VM_PAGE_SNOOPED		(1 << 4)

काष्ठा drm_radeon_gem_va अणु
	__u32		handle;
	__u32		operation;
	__u32		vm_id;
	__u32		flags;
	__u64		offset;
पूर्ण;

#घोषणा RADEON_CHUNK_ID_RELOCS	0x01
#घोषणा RADEON_CHUNK_ID_IB	0x02
#घोषणा RADEON_CHUNK_ID_FLAGS	0x03
#घोषणा RADEON_CHUNK_ID_CONST_IB	0x04

/* The first dword of RADEON_CHUNK_ID_FLAGS is a uपूर्णांक32 of these flags: */
#घोषणा RADEON_CS_KEEP_TILING_FLAGS 0x01
#घोषणा RADEON_CS_USE_VM            0x02
#घोषणा RADEON_CS_END_OF_FRAME      0x04 /* a hपूर्णांक from userspace which CS is the last one */
/* The second dword of RADEON_CHUNK_ID_FLAGS is a uपूर्णांक32 that sets the ring type */
#घोषणा RADEON_CS_RING_GFX          0
#घोषणा RADEON_CS_RING_COMPUTE      1
#घोषणा RADEON_CS_RING_DMA          2
#घोषणा RADEON_CS_RING_UVD          3
#घोषणा RADEON_CS_RING_VCE          4
/* The third dword of RADEON_CHUNK_ID_FLAGS is a sपूर्णांक32 that sets the priority */
/* 0 = normal, + = higher priority, - = lower priority */

काष्ठा drm_radeon_cs_chunk अणु
	__u32		chunk_id;
	__u32		length_dw;
	__u64		chunk_data;
पूर्ण;

/* drm_radeon_cs_reloc.flags */
#घोषणा RADEON_RELOC_PRIO_MASK		(0xf << 0)

काष्ठा drm_radeon_cs_reloc अणु
	__u32		handle;
	__u32		पढ़ो_करोमुख्यs;
	__u32		ग_लिखो_करोमुख्य;
	__u32		flags;
पूर्ण;

काष्ठा drm_radeon_cs अणु
	__u32		num_chunks;
	__u32		cs_id;
	/* this poपूर्णांकs to __u64 * which poपूर्णांक to cs chunks */
	__u64		chunks;
	/* updates to the limits after this CS ioctl */
	__u64		gart_limit;
	__u64		vram_limit;
पूर्ण;

#घोषणा RADEON_INFO_DEVICE_ID		0x00
#घोषणा RADEON_INFO_NUM_GB_PIPES	0x01
#घोषणा RADEON_INFO_NUM_Z_PIPES 	0x02
#घोषणा RADEON_INFO_ACCEL_WORKING	0x03
#घोषणा RADEON_INFO_CRTC_FROM_ID	0x04
#घोषणा RADEON_INFO_ACCEL_WORKING2	0x05
#घोषणा RADEON_INFO_TILING_CONFIG	0x06
#घोषणा RADEON_INFO_WANT_HYPERZ		0x07
#घोषणा RADEON_INFO_WANT_CMASK		0x08 /* get access to CMASK on r300 */
#घोषणा RADEON_INFO_CLOCK_CRYSTAL_FREQ	0x09 /* घड़ी crystal frequency */
#घोषणा RADEON_INFO_NUM_BACKENDS	0x0a /* DB/backends क्रम r600+ - need क्रम OQ */
#घोषणा RADEON_INFO_NUM_TILE_PIPES	0x0b /* tile pipes क्रम r600+ */
#घोषणा RADEON_INFO_FUSION_GART_WORKING	0x0c /* fusion ग_लिखोs to GTT were broken beक्रमe this */
#घोषणा RADEON_INFO_BACKEND_MAP		0x0d /* pipe to backend map, needed by mesa */
/* भव address start, va < start are reserved by the kernel */
#घोषणा RADEON_INFO_VA_START		0x0e
/* maximum size of ib using the भव memory cs */
#घोषणा RADEON_INFO_IB_VM_MAX_SIZE	0x0f
/* max pipes - needed क्रम compute shaders */
#घोषणा RADEON_INFO_MAX_PIPES		0x10
/* बारtamp क्रम GL_ARB_समयr_query (OpenGL), वापसs the current GPU घड़ी */
#घोषणा RADEON_INFO_TIMESTAMP		0x11
/* max shader engines (SE) - needed क्रम geometry shaders, etc. */
#घोषणा RADEON_INFO_MAX_SE		0x12
/* max SH per SE */
#घोषणा RADEON_INFO_MAX_SH_PER_SE	0x13
/* fast fb access is enabled */
#घोषणा RADEON_INFO_FASTFB_WORKING	0x14
/* query अगर a RADEON_CS_RING_* submission is supported */
#घोषणा RADEON_INFO_RING_WORKING	0x15
/* SI tile mode array */
#घोषणा RADEON_INFO_SI_TILE_MODE_ARRAY	0x16
/* query अगर CP DMA is supported on the compute ring */
#घोषणा RADEON_INFO_SI_CP_DMA_COMPUTE	0x17
/* CIK macrotile mode array */
#घोषणा RADEON_INFO_CIK_MACROTILE_MODE_ARRAY	0x18
/* query the number of render backends */
#घोषणा RADEON_INFO_SI_BACKEND_ENABLED_MASK	0x19
/* max engine घड़ी - needed क्रम OpenCL */
#घोषणा RADEON_INFO_MAX_SCLK		0x1a
/* version of VCE firmware */
#घोषणा RADEON_INFO_VCE_FW_VERSION	0x1b
/* version of VCE feedback */
#घोषणा RADEON_INFO_VCE_FB_VERSION	0x1c
#घोषणा RADEON_INFO_NUM_BYTES_MOVED	0x1d
#घोषणा RADEON_INFO_VRAM_USAGE		0x1e
#घोषणा RADEON_INFO_GTT_USAGE		0x1f
#घोषणा RADEON_INFO_ACTIVE_CU_COUNT	0x20
#घोषणा RADEON_INFO_CURRENT_GPU_TEMP	0x21
#घोषणा RADEON_INFO_CURRENT_GPU_SCLK	0x22
#घोषणा RADEON_INFO_CURRENT_GPU_MCLK	0x23
#घोषणा RADEON_INFO_READ_REG		0x24
#घोषणा RADEON_INFO_VA_UNMAP_WORKING	0x25
#घोषणा RADEON_INFO_GPU_RESET_COUNTER	0x26

काष्ठा drm_radeon_info अणु
	__u32		request;
	__u32		pad;
	__u64		value;
पूर्ण;

/* Those correspond to the tile index to use, this is to explicitly state
 * the API that is implicitly defined by the tile mode array.
 */
#घोषणा SI_TILE_MODE_COLOR_LINEAR_ALIGNED	8
#घोषणा SI_TILE_MODE_COLOR_1D			13
#घोषणा SI_TILE_MODE_COLOR_1D_SCANOUT		9
#घोषणा SI_TILE_MODE_COLOR_2D_8BPP		14
#घोषणा SI_TILE_MODE_COLOR_2D_16BPP		15
#घोषणा SI_TILE_MODE_COLOR_2D_32BPP		16
#घोषणा SI_TILE_MODE_COLOR_2D_64BPP		17
#घोषणा SI_TILE_MODE_COLOR_2D_SCANOUT_16BPP	11
#घोषणा SI_TILE_MODE_COLOR_2D_SCANOUT_32BPP	12
#घोषणा SI_TILE_MODE_DEPTH_STENCIL_1D		4
#घोषणा SI_TILE_MODE_DEPTH_STENCIL_2D		0
#घोषणा SI_TILE_MODE_DEPTH_STENCIL_2D_2AA	3
#घोषणा SI_TILE_MODE_DEPTH_STENCIL_2D_4AA	3
#घोषणा SI_TILE_MODE_DEPTH_STENCIL_2D_8AA	2

#घोषणा CIK_TILE_MODE_DEPTH_STENCIL_1D		5

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
