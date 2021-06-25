<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright 2008-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

/*
 * svga3d_surfacedefs.h --
 *
 *      Surface definitions and अंतरभूतable utilities क्रम SVGA3d.
 */

#अगर_अघोषित _SVGA3D_SURFACEDEFS_H_
#घोषणा _SVGA3D_SURFACEDEFS_H_

#घोषणा INCLUDE_ALLOW_USERLEVEL
#घोषणा INCLUDE_ALLOW_MODULE
#समावेश "includeCheck.h"

#समावेश <linux/kernel.h>
#समावेश <drm/vmwgfx_drm.h>

#समावेश "svga3d_reg.h"

#घोषणा surf_size_काष्ठा काष्ठा drm_vmw_size

/*
 * क्रमागत svga3d_block_desc - describes generic properties about क्रमmats.
 */
क्रमागत svga3d_block_desc अणु
	/* Nothing special can be said about this क्रमmat. */
	SVGA3DBLOCKDESC_NONE        = 0,

	/* Format contains Blue/U data */
	SVGA3DBLOCKDESC_BLUE        = 1 << 0,
	SVGA3DBLOCKDESC_W           = 1 << 0,
	SVGA3DBLOCKDESC_BUMP_L      = 1 << 0,

	/* Format contains Green/V data */
	SVGA3DBLOCKDESC_GREEN       = 1 << 1,
	SVGA3DBLOCKDESC_V           = 1 << 1,

	/* Format contains Red/W/Luminance data */
	SVGA3DBLOCKDESC_RED         = 1 << 2,
	SVGA3DBLOCKDESC_U           = 1 << 2,
	SVGA3DBLOCKDESC_LUMIन_अंकCE   = 1 << 2,

	/* Format contains Alpha/Q data */
	SVGA3DBLOCKDESC_ALPHA       = 1 << 3,
	SVGA3DBLOCKDESC_Q           = 1 << 3,

	/* Format is a buffer */
	SVGA3DBLOCKDESC_BUFFER      = 1 << 4,

	/* Format is compressed */
	SVGA3DBLOCKDESC_COMPRESSED  = 1 << 5,

	/* Format uses IEEE भग्नing poपूर्णांक */
	SVGA3DBLOCKDESC_FP          = 1 << 6,

	/* Three separate blocks store data. */
	SVGA3DBLOCKDESC_PLANAR_YUV  = 1 << 7,

	/* 2 planes of Y, UV, e.g., NV12. */
	SVGA3DBLOCKDESC_2PLANAR_YUV = 1 << 8,

	/* 3 planes of separate Y, U, V, e.g., YV12. */
	SVGA3DBLOCKDESC_3PLANAR_YUV = 1 << 9,

	/* Block with a stencil channel */
	SVGA3DBLOCKDESC_STENCIL     = 1 << 11,

	/* Typeless क्रमmat */
	SVGA3DBLOCKDESC_TYPELESS    = 1 << 12,

	/* Channels are चिन्हित पूर्णांकegers */
	SVGA3DBLOCKDESC_SINT        = 1 << 13,

	/* Channels are अचिन्हित पूर्णांकegers */
	SVGA3DBLOCKDESC_UINT        = 1 << 14,

	/* Channels are normalized (when sampling) */
	SVGA3DBLOCKDESC_NORM        = 1 << 15,

	/* Channels are in SRGB */
	SVGA3DBLOCKDESC_SRGB        = 1 << 16,

	/* Shared exponent */
	SVGA3DBLOCKDESC_EXP         = 1 << 17,

	/* Format contains color data. */
	SVGA3DBLOCKDESC_COLOR       = 1 << 18,
	/* Format contains depth data. */
	SVGA3DBLOCKDESC_DEPTH       = 1 << 19,
	/* Format contains bump data. */
	SVGA3DBLOCKDESC_BUMP        = 1 << 20,

	/* Format contains YUV video data. */
	SVGA3DBLOCKDESC_YUV_VIDEO   = 1 << 21,

	/* For mixed अचिन्हित/चिन्हित क्रमmats. */
	SVGA3DBLOCKDESC_MIXED       = 1 << 22,

	/* For distingushing CxV8U8. */
	SVGA3DBLOCKDESC_CX          = 1 << 23,

	/* Dअगरferent compressed क्रमmat groups. */
	SVGA3DBLOCKDESC_BC1         = 1 << 24,
	SVGA3DBLOCKDESC_BC2         = 1 << 25,
	SVGA3DBLOCKDESC_BC3         = 1 << 26,
	SVGA3DBLOCKDESC_BC4         = 1 << 27,
	SVGA3DBLOCKDESC_BC5         = 1 << 28,
	SVGA3DBLOCKDESC_BC6H        = 1 << 29,
	SVGA3DBLOCKDESC_BC7         = 1 << 30,

	SVGA3DBLOCKDESC_A_UINT    = SVGA3DBLOCKDESC_ALPHA |
				    SVGA3DBLOCKDESC_UINT |
				    SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_A_UNORM   = SVGA3DBLOCKDESC_A_UINT |
				    SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_R_UINT    = SVGA3DBLOCKDESC_RED |
				    SVGA3DBLOCKDESC_UINT |
				    SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_R_UNORM   = SVGA3DBLOCKDESC_R_UINT |
				    SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_R_SINT    = SVGA3DBLOCKDESC_RED |
				    SVGA3DBLOCKDESC_SINT |
				    SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_R_SNORM   = SVGA3DBLOCKDESC_R_SINT |
				    SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_G_UINT    = SVGA3DBLOCKDESC_GREEN |
				    SVGA3DBLOCKDESC_UINT |
				    SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RG_UINT    = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_UINT |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RG_UNORM   = SVGA3DBLOCKDESC_RG_UINT |
				     SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_RG_SINT    = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_SINT |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RG_SNORM   = SVGA3DBLOCKDESC_RG_SINT |
				     SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_RGB_UINT   = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_BLUE |
				     SVGA3DBLOCKDESC_UINT |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RGB_SINT   = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_BLUE |
				     SVGA3DBLOCKDESC_SINT |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RGB_UNORM   = SVGA3DBLOCKDESC_RGB_UINT |
				      SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_RGB_UNORM_SRGB = SVGA3DBLOCKDESC_RGB_UNORM |
					 SVGA3DBLOCKDESC_SRGB,
	SVGA3DBLOCKDESC_RGBA_UINT  = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_BLUE |
				     SVGA3DBLOCKDESC_ALPHA |
				     SVGA3DBLOCKDESC_UINT |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RGBA_UNORM = SVGA3DBLOCKDESC_RGBA_UINT |
				     SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_RGBA_UNORM_SRGB = SVGA3DBLOCKDESC_RGBA_UNORM |
					  SVGA3DBLOCKDESC_SRGB,
	SVGA3DBLOCKDESC_RGBA_SINT  = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_BLUE |
				     SVGA3DBLOCKDESC_ALPHA |
				     SVGA3DBLOCKDESC_SINT |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RGBA_SNORM = SVGA3DBLOCKDESC_RGBA_SINT |
				     SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_RGBA_FP    = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_BLUE |
				     SVGA3DBLOCKDESC_ALPHA |
				     SVGA3DBLOCKDESC_FP |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_UV         = SVGA3DBLOCKDESC_U |
				     SVGA3DBLOCKDESC_V |
				     SVGA3DBLOCKDESC_BUMP,
	SVGA3DBLOCKDESC_UVL        = SVGA3DBLOCKDESC_UV |
				     SVGA3DBLOCKDESC_BUMP_L |
				     SVGA3DBLOCKDESC_MIXED |
				     SVGA3DBLOCKDESC_BUMP,
	SVGA3DBLOCKDESC_UVW        = SVGA3DBLOCKDESC_UV |
				     SVGA3DBLOCKDESC_W |
				     SVGA3DBLOCKDESC_BUMP,
	SVGA3DBLOCKDESC_UVWA       = SVGA3DBLOCKDESC_UVW |
				     SVGA3DBLOCKDESC_ALPHA |
				     SVGA3DBLOCKDESC_MIXED |
				     SVGA3DBLOCKDESC_BUMP,
	SVGA3DBLOCKDESC_UVWQ       = SVGA3DBLOCKDESC_U |
				     SVGA3DBLOCKDESC_V |
				     SVGA3DBLOCKDESC_W |
				     SVGA3DBLOCKDESC_Q |
				     SVGA3DBLOCKDESC_BUMP,
	SVGA3DBLOCKDESC_L_UNORM    = SVGA3DBLOCKDESC_LUMIन_अंकCE |
				     SVGA3DBLOCKDESC_UINT |
				     SVGA3DBLOCKDESC_NORM |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_LA_UNORM   = SVGA3DBLOCKDESC_LUMIन_अंकCE |
				     SVGA3DBLOCKDESC_ALPHA |
				     SVGA3DBLOCKDESC_UINT |
				     SVGA3DBLOCKDESC_NORM |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_R_FP       = SVGA3DBLOCKDESC_RED |
				     SVGA3DBLOCKDESC_FP |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RG_FP      = SVGA3DBLOCKDESC_R_FP |
				     SVGA3DBLOCKDESC_GREEN |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RGB_FP     = SVGA3DBLOCKDESC_RG_FP |
				     SVGA3DBLOCKDESC_BLUE |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_YUV        = SVGA3DBLOCKDESC_YUV_VIDEO |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_AYUV       = SVGA3DBLOCKDESC_ALPHA |
				     SVGA3DBLOCKDESC_YUV_VIDEO |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_RGB_EXP       = SVGA3DBLOCKDESC_RED |
					SVGA3DBLOCKDESC_GREEN |
					SVGA3DBLOCKDESC_BLUE |
					SVGA3DBLOCKDESC_EXP |
					SVGA3DBLOCKDESC_COLOR,

	SVGA3DBLOCKDESC_COMP_TYPELESS = SVGA3DBLOCKDESC_COMPRESSED |
					SVGA3DBLOCKDESC_TYPELESS,
	SVGA3DBLOCKDESC_COMP_UNORM = SVGA3DBLOCKDESC_COMPRESSED |
				     SVGA3DBLOCKDESC_UINT |
				     SVGA3DBLOCKDESC_NORM |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_COMP_SNORM = SVGA3DBLOCKDESC_COMPRESSED |
				     SVGA3DBLOCKDESC_SINT |
				     SVGA3DBLOCKDESC_NORM |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_COMP_UNORM_SRGB = SVGA3DBLOCKDESC_COMP_UNORM |
					  SVGA3DBLOCKDESC_SRGB,
	SVGA3DBLOCKDESC_BC1_COMP_TYPELESS = SVGA3DBLOCKDESC_BC1 |
					    SVGA3DBLOCKDESC_COMP_TYPELESS,
	SVGA3DBLOCKDESC_BC1_COMP_UNORM = SVGA3DBLOCKDESC_BC1 |
					 SVGA3DBLOCKDESC_COMP_UNORM,
	SVGA3DBLOCKDESC_BC1_COMP_UNORM_SRGB = SVGA3DBLOCKDESC_BC1_COMP_UNORM |
					      SVGA3DBLOCKDESC_SRGB,
	SVGA3DBLOCKDESC_BC2_COMP_TYPELESS = SVGA3DBLOCKDESC_BC2 |
					    SVGA3DBLOCKDESC_COMP_TYPELESS,
	SVGA3DBLOCKDESC_BC2_COMP_UNORM = SVGA3DBLOCKDESC_BC2 |
					 SVGA3DBLOCKDESC_COMP_UNORM,
	SVGA3DBLOCKDESC_BC2_COMP_UNORM_SRGB = SVGA3DBLOCKDESC_BC2_COMP_UNORM |
					      SVGA3DBLOCKDESC_SRGB,
	SVGA3DBLOCKDESC_BC3_COMP_TYPELESS = SVGA3DBLOCKDESC_BC3 |
					    SVGA3DBLOCKDESC_COMP_TYPELESS,
	SVGA3DBLOCKDESC_BC3_COMP_UNORM = SVGA3DBLOCKDESC_BC3 |
					 SVGA3DBLOCKDESC_COMP_UNORM,
	SVGA3DBLOCKDESC_BC3_COMP_UNORM_SRGB = SVGA3DBLOCKDESC_BC3_COMP_UNORM |
					      SVGA3DBLOCKDESC_SRGB,
	SVGA3DBLOCKDESC_BC4_COMP_TYPELESS = SVGA3DBLOCKDESC_BC4 |
					    SVGA3DBLOCKDESC_COMP_TYPELESS,
	SVGA3DBLOCKDESC_BC4_COMP_UNORM = SVGA3DBLOCKDESC_BC4 |
					 SVGA3DBLOCKDESC_COMP_UNORM,
	SVGA3DBLOCKDESC_BC4_COMP_SNORM = SVGA3DBLOCKDESC_BC4 |
					 SVGA3DBLOCKDESC_COMP_SNORM,
	SVGA3DBLOCKDESC_BC5_COMP_TYPELESS = SVGA3DBLOCKDESC_BC5 |
					    SVGA3DBLOCKDESC_COMP_TYPELESS,
	SVGA3DBLOCKDESC_BC5_COMP_UNORM = SVGA3DBLOCKDESC_BC5 |
					 SVGA3DBLOCKDESC_COMP_UNORM,
	SVGA3DBLOCKDESC_BC5_COMP_SNORM = SVGA3DBLOCKDESC_BC5 |
					 SVGA3DBLOCKDESC_COMP_SNORM,
	SVGA3DBLOCKDESC_BC6H_COMP_TYPELESS = SVGA3DBLOCKDESC_BC6H |
					     SVGA3DBLOCKDESC_COMP_TYPELESS,
	SVGA3DBLOCKDESC_BC6H_COMP_UF16 = SVGA3DBLOCKDESC_BC6H |
					 SVGA3DBLOCKDESC_COMPRESSED,
	SVGA3DBLOCKDESC_BC6H_COMP_SF16 = SVGA3DBLOCKDESC_BC6H |
					 SVGA3DBLOCKDESC_COMPRESSED,
	SVGA3DBLOCKDESC_BC7_COMP_TYPELESS = SVGA3DBLOCKDESC_BC7 |
					    SVGA3DBLOCKDESC_COMP_TYPELESS,
	SVGA3DBLOCKDESC_BC7_COMP_UNORM = SVGA3DBLOCKDESC_BC7 |
					 SVGA3DBLOCKDESC_COMP_UNORM,
	SVGA3DBLOCKDESC_BC7_COMP_UNORM_SRGB = SVGA3DBLOCKDESC_BC7_COMP_UNORM |
					      SVGA3DBLOCKDESC_SRGB,

	SVGA3DBLOCKDESC_NV12       = SVGA3DBLOCKDESC_YUV_VIDEO |
				     SVGA3DBLOCKDESC_PLANAR_YUV |
				     SVGA3DBLOCKDESC_2PLANAR_YUV |
				     SVGA3DBLOCKDESC_COLOR,
	SVGA3DBLOCKDESC_YV12       = SVGA3DBLOCKDESC_YUV_VIDEO |
				     SVGA3DBLOCKDESC_PLANAR_YUV |
				     SVGA3DBLOCKDESC_3PLANAR_YUV |
				     SVGA3DBLOCKDESC_COLOR,

	SVGA3DBLOCKDESC_DEPTH_UINT = SVGA3DBLOCKDESC_DEPTH |
				     SVGA3DBLOCKDESC_UINT,
	SVGA3DBLOCKDESC_DEPTH_UNORM = SVGA3DBLOCKDESC_DEPTH_UINT |
				     SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_DS      =    SVGA3DBLOCKDESC_DEPTH |
				     SVGA3DBLOCKDESC_STENCIL,
	SVGA3DBLOCKDESC_DS_UINT =    SVGA3DBLOCKDESC_DEPTH |
				     SVGA3DBLOCKDESC_STENCIL |
				     SVGA3DBLOCKDESC_UINT,
	SVGA3DBLOCKDESC_DS_UNORM =   SVGA3DBLOCKDESC_DS_UINT |
				     SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_DEPTH_FP   = SVGA3DBLOCKDESC_DEPTH |
				     SVGA3DBLOCKDESC_FP,

	SVGA3DBLOCKDESC_UV_UINT    = SVGA3DBLOCKDESC_UV |
				     SVGA3DBLOCKDESC_UINT,
	SVGA3DBLOCKDESC_UV_SNORM   = SVGA3DBLOCKDESC_UV |
				     SVGA3DBLOCKDESC_SINT |
				     SVGA3DBLOCKDESC_NORM,
	SVGA3DBLOCKDESC_UVCX_SNORM = SVGA3DBLOCKDESC_UV_SNORM |
				     SVGA3DBLOCKDESC_CX,
	SVGA3DBLOCKDESC_UVWQ_SNORM = SVGA3DBLOCKDESC_UVWQ |
				     SVGA3DBLOCKDESC_SINT |
				     SVGA3DBLOCKDESC_NORM,
पूर्ण;

काष्ठा svga3d_channel_def अणु
	जोड़ अणु
		u8 blue;
		u8 w_bump;
		u8 l_bump;
		u8 uv_video;
		u8 u_video;
	पूर्ण;
	जोड़ अणु
		u8 green;
		u8 stencil;
		u8 v_bump;
		u8 v_video;
	पूर्ण;
	जोड़ अणु
		u8 red;
		u8 u_bump;
		u8 luminance;
		u8 y_video;
		u8 depth;
		u8 data;
	पूर्ण;
	जोड़ अणु
		u8 alpha;
		u8 q_bump;
		u8 exp;
	पूर्ण;
पूर्ण;

/*
 * काष्ठा svga3d_surface_desc - describes the actual pixel data.
 *
 * @क्रमmat: Format
 * @block_desc: Block description
 * @block_size: Dimensions in pixels of a block
 * @bytes_per_block: Size of block in bytes
 * @pitch_bytes_per_block: Size of a block in bytes क्रम purposes of pitch
 * @bit_depth: Channel bit depths
 * @bit_offset: Channel bit masks (in bits offset from the start of the poपूर्णांकer)
 */
काष्ठा svga3d_surface_desc अणु
	SVGA3dSurfaceFormat क्रमmat;
	क्रमागत svga3d_block_desc block_desc;

	surf_size_काष्ठा block_size;
	u32 bytes_per_block;
	u32 pitch_bytes_per_block;

	काष्ठा svga3d_channel_def bit_depth;
	काष्ठा svga3d_channel_def bit_offset;
पूर्ण;

अटल स्थिर काष्ठा svga3d_surface_desc svga3d_surface_descs[] = अणु
   अणुSVGA3D_FORMAT_INVALID, SVGA3DBLOCKDESC_NONE,
      अणु1, 1, 1पूर्ण,  0, 0,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_X8R8G8B8, SVGA3DBLOCKDESC_RGB_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_A8R8G8B8, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R5G6B5, SVGA3DBLOCKDESC_RGB_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु5पूर्ण, अणु6पूर्ण, अणु5पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु5पूर्ण, अणु11पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_X1R5G5B5, SVGA3DBLOCKDESC_RGB_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु5पूर्ण, अणु5पूर्ण, अणु5पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु5पूर्ण, अणु10पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_A1R5G5B5, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु5पूर्ण, अणु5पूर्ण, अणु5पूर्ण, अणु1पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु5पूर्ण, अणु10पूर्ण, अणु15पूर्णपूर्णपूर्ण,

   अणुSVGA3D_A4R4G4B4, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु4पूर्ण, अणु4पूर्ण, अणु4पूर्ण, अणु4पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु4पूर्ण, अणु8पूर्ण, अणु12पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_D32, SVGA3DBLOCKDESC_DEPTH_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_D16, SVGA3DBLOCKDESC_DEPTH_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_D24S8, SVGA3DBLOCKDESC_DS_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु24पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_D15S1, SVGA3DBLOCKDESC_DS_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु1पूर्ण, अणु15पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु1पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_LUMIन_अंकCE8, SVGA3DBLOCKDESC_L_UNORM,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_LUMIन_अंकCE4_ALPHA4, SVGA3DBLOCKDESC_LA_UNORM,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु4पूर्ण, अणु4पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु4पूर्णपूर्णपूर्ण,

   अणुSVGA3D_LUMIन_अंकCE16, SVGA3DBLOCKDESC_L_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_LUMIन_अंकCE8_ALPHA8, SVGA3DBLOCKDESC_LA_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु8पूर्णपूर्णपूर्ण,

   अणुSVGA3D_DXT1, SVGA3DBLOCKDESC_BC1_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_DXT2, SVGA3DBLOCKDESC_BC2_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_DXT3, SVGA3DBLOCKDESC_BC2_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_DXT4, SVGA3DBLOCKDESC_BC3_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_DXT5, SVGA3DBLOCKDESC_BC3_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BUMPU8V8, SVGA3DBLOCKDESC_UV_SNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BUMPL6V5U5, SVGA3DBLOCKDESC_UVL,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु6पूर्ण, अणु5पूर्ण, अणु5पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु10पूर्ण, अणु5पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BUMPX8L8V8U8, SVGA3DBLOCKDESC_UVL,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_FORMAT_DEAD1, SVGA3DBLOCKDESC_NONE,
      अणु1, 1, 1पूर्ण,  3, 3,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_ARGB_S10E5, SVGA3DBLOCKDESC_RGBA_FP,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_ARGB_S23E8, SVGA3DBLOCKDESC_RGBA_FP,
      अणु1, 1, 1पूर्ण,  16, 16,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु32पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु96पूर्णपूर्णपूर्ण,

   अणुSVGA3D_A2R10G10B10, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु10पूर्ण, अणु10पूर्ण, अणु10पूर्ण, अणु2पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु10पूर्ण, अणु20पूर्ण, अणु30पूर्णपूर्णपूर्ण,

   अणुSVGA3D_V8U8, SVGA3DBLOCKDESC_UV_SNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Q8W8V8U8, SVGA3DBLOCKDESC_UVWQ_SNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_CxV8U8, SVGA3DBLOCKDESC_UVCX_SNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_X8L8V8U8, SVGA3DBLOCKDESC_UVL,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_A2W10V10U10, SVGA3DBLOCKDESC_UVWA,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु10पूर्ण, अणु10पूर्ण, अणु10पूर्ण, अणु2पूर्णपूर्ण,
      अणुअणु20पूर्ण, अणु10पूर्ण, अणु0पूर्ण, अणु30पूर्णपूर्णपूर्ण,

   अणुSVGA3D_ALPHA8, SVGA3DBLOCKDESC_A_UNORM,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R_S10E5, SVGA3DBLOCKDESC_R_FP,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R_S23E8, SVGA3DBLOCKDESC_R_FP,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_RG_S10E5, SVGA3DBLOCKDESC_RG_FP,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_RG_S23E8, SVGA3DBLOCKDESC_RG_FP,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BUFFER, SVGA3DBLOCKDESC_BUFFER,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_D24X8, SVGA3DBLOCKDESC_DEPTH_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु24पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_V16U16, SVGA3DBLOCKDESC_UV_SNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_G16R16, SVGA3DBLOCKDESC_RG_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_A16B16G16R16, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_UYVY, SVGA3DBLOCKDESC_YUV,
      अणु2, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_YUY2, SVGA3DBLOCKDESC_YUV,
      अणु2, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु8पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_NV12, SVGA3DBLOCKDESC_NV12,
      अणु2, 2, 1पूर्ण,  6, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु48पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_FORMAT_DEAD2, SVGA3DBLOCKDESC_NONE,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32A32_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  16, 16,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु32पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु96पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32A32_UINT, SVGA3DBLOCKDESC_RGBA_UINT,
      अणु1, 1, 1पूर्ण,  16, 16,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु32पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु96पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32A32_SINT, SVGA3DBLOCKDESC_RGBA_SINT,
      अणु1, 1, 1पूर्ण,  16, 16,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु32पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु96पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  12, 12,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32_FLOAT, SVGA3DBLOCKDESC_RGB_FP,
      अणु1, 1, 1पूर्ण,  12, 12,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32_UINT, SVGA3DBLOCKDESC_RGB_UINT,
      अणु1, 1, 1पूर्ण,  12, 12,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32_SINT, SVGA3DBLOCKDESC_RGB_SINT,
      अणु1, 1, 1पूर्ण,  12, 12,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16B16A16_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16B16A16_UINT, SVGA3DBLOCKDESC_RGBA_UINT,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16B16A16_SNORM, SVGA3DBLOCKDESC_RGBA_SNORM,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16B16A16_SINT, SVGA3DBLOCKDESC_RGBA_SINT,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32_UINT, SVGA3DBLOCKDESC_RG_UINT,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32_SINT, SVGA3DBLOCKDESC_RG_SINT,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G8X24_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_D32_FLOAT_S8X24_UINT, SVGA3DBLOCKDESC_DS,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32_FLOAT_X8X24, SVGA3DBLOCKDESC_R_FP,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_X32_G8X24_UINT, SVGA3DBLOCKDESC_G_UINT,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R10G10B10A2_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु10पूर्ण, अणु10पूर्ण, अणु10पूर्ण, अणु2पूर्णपूर्ण,
      अणुअणु20पूर्ण, अणु10पूर्ण, अणु0पूर्ण, अणु30पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R10G10B10A2_UINT, SVGA3DBLOCKDESC_RGBA_UINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु10पूर्ण, अणु10पूर्ण, अणु10पूर्ण, अणु2पूर्णपूर्ण,
      अणुअणु20पूर्ण, अणु10पूर्ण, अणु0पूर्ण, अणु30पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R11G11B10_FLOAT, SVGA3DBLOCKDESC_RGB_FP,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु10पूर्ण, अणु11पूर्ण, अणु11पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु22पूर्ण, अणु11पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8B8A8_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8B8A8_UNORM, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8B8A8_UNORM_SRGB, SVGA3DBLOCKDESC_RGBA_UNORM_SRGB,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8B8A8_UINT, SVGA3DBLOCKDESC_RGBA_UINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8B8A8_SINT, SVGA3DBLOCKDESC_RGBA_SINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16_UINT, SVGA3DBLOCKDESC_RG_UINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16_SINT, SVGA3DBLOCKDESC_RG_SINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_D32_FLOAT, SVGA3DBLOCKDESC_DEPTH_FP,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32_UINT, SVGA3DBLOCKDESC_R_UINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32_SINT, SVGA3DBLOCKDESC_R_SINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R24G8_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु24पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु24पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_D24_UNORM_S8_UINT, SVGA3DBLOCKDESC_DS_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु24पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु24पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R24_UNORM_X8, SVGA3DBLOCKDESC_R_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु24पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_X24_G8_UINT, SVGA3DBLOCKDESC_G_UINT,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु24पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8_UNORM, SVGA3DBLOCKDESC_RG_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8_UINT, SVGA3DBLOCKDESC_RG_UINT,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8_SINT, SVGA3DBLOCKDESC_RG_SINT,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16_UNORM, SVGA3DBLOCKDESC_R_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16_UINT, SVGA3DBLOCKDESC_R_UINT,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16_SNORM, SVGA3DBLOCKDESC_R_SNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16_SINT, SVGA3DBLOCKDESC_R_SINT,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8_UNORM, SVGA3DBLOCKDESC_R_UNORM,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8_UINT, SVGA3DBLOCKDESC_R_UINT,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8_SNORM, SVGA3DBLOCKDESC_R_SNORM,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8_SINT, SVGA3DBLOCKDESC_R_SINT,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_P8, SVGA3DBLOCKDESC_NONE,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R9G9B9E5_SHAREDEXP, SVGA3DBLOCKDESC_RGB_EXP,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु9पूर्ण, अणु9पूर्ण, अणु9पूर्ण, अणु5पूर्णपूर्ण,
      अणुअणु18पूर्ण, अणु9पूर्ण, अणु0पूर्ण, अणु27पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8_B8G8_UNORM, SVGA3DBLOCKDESC_NONE,
      अणु2, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_G8R8_G8B8_UNORM, SVGA3DBLOCKDESC_NONE,
      अणु2, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC1_TYPELESS, SVGA3DBLOCKDESC_BC1_COMP_TYPELESS,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC1_UNORM_SRGB, SVGA3DBLOCKDESC_BC1_COMP_UNORM_SRGB,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC2_TYPELESS, SVGA3DBLOCKDESC_BC2_COMP_TYPELESS,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC2_UNORM_SRGB, SVGA3DBLOCKDESC_BC2_COMP_UNORM_SRGB,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC3_TYPELESS, SVGA3DBLOCKDESC_BC3_COMP_TYPELESS,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC3_UNORM_SRGB, SVGA3DBLOCKDESC_BC3_COMP_UNORM_SRGB,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC4_TYPELESS, SVGA3DBLOCKDESC_BC4_COMP_TYPELESS,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_ATI1, SVGA3DBLOCKDESC_BC4_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC4_SNORM, SVGA3DBLOCKDESC_BC4_COMP_SNORM,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC5_TYPELESS, SVGA3DBLOCKDESC_BC5_COMP_TYPELESS,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_ATI2, SVGA3DBLOCKDESC_BC5_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC5_SNORM, SVGA3DBLOCKDESC_BC5_COMP_SNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R10G10B10_XR_BIAS_A2_UNORM, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु10पूर्ण, अणु10पूर्ण, अणु10पूर्ण, अणु2पूर्णपूर्ण,
     अणुअणु20पूर्ण, अणु10पूर्ण, अणु0पूर्ण, अणु30पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B8G8R8A8_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B8G8R8A8_UNORM_SRGB, SVGA3DBLOCKDESC_RGBA_UNORM_SRGB,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B8G8R8X8_TYPELESS, SVGA3DBLOCKDESC_TYPELESS,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B8G8R8X8_UNORM_SRGB, SVGA3DBLOCKDESC_RGB_UNORM_SRGB,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_DF16, SVGA3DBLOCKDESC_DEPTH_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_DF24, SVGA3DBLOCKDESC_DEPTH_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु24पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_Z_D24S8_INT, SVGA3DBLOCKDESC_DS_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु24पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_YV12, SVGA3DBLOCKDESC_YV12,
      अणु2, 2, 1पूर्ण,  6, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु48पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32B32A32_FLOAT, SVGA3DBLOCKDESC_RGBA_FP,
      अणु1, 1, 1पूर्ण,  16, 16,
      अणुअणु32पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु32पूर्णपूर्ण,
      अणुअणु64पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु96पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16B16A16_FLOAT, SVGA3DBLOCKDESC_RGBA_FP,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16B16A16_UNORM, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु16पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु16पूर्णपूर्ण,
      अणुअणु32पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु48पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32G32_FLOAT, SVGA3DBLOCKDESC_RG_FP,
      अणु1, 1, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु32पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R10G10B10A2_UNORM, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु10पूर्ण, अणु10पूर्ण, अणु10पूर्ण, अणु2पूर्णपूर्ण,
      अणुअणु20पूर्ण, अणु10पूर्ण, अणु0पूर्ण, अणु30पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8B8A8_SNORM, SVGA3DBLOCKDESC_RGBA_SNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु16पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16_FLOAT, SVGA3DBLOCKDESC_RG_FP,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16_UNORM, SVGA3DBLOCKDESC_RG_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16G16_SNORM, SVGA3DBLOCKDESC_RG_SNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु16पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R32_FLOAT, SVGA3DBLOCKDESC_R_FP,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु32पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R8G8_SNORM, SVGA3DBLOCKDESC_RG_SNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_R16_FLOAT, SVGA3DBLOCKDESC_R_FP,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_D16_UNORM, SVGA3DBLOCKDESC_DEPTH_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु16पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_A8_UNORM, SVGA3DBLOCKDESC_A_UNORM,
      अणु1, 1, 1पूर्ण,  1, 1,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC1_UNORM, SVGA3DBLOCKDESC_BC1_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC2_UNORM, SVGA3DBLOCKDESC_BC2_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC3_UNORM, SVGA3DBLOCKDESC_BC3_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B5G6R5_UNORM, SVGA3DBLOCKDESC_RGB_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु5पूर्ण, अणु6पूर्ण, अणु5पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु5पूर्ण, अणु11पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B5G5R5A1_UNORM, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु5पूर्ण, अणु5पूर्ण, अणु5पूर्ण, अणु1पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु5पूर्ण, अणु10पूर्ण, अणु15पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B8G8R8A8_UNORM, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B8G8R8X8_UNORM, SVGA3DBLOCKDESC_RGB_UNORM,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC4_UNORM, SVGA3DBLOCKDESC_BC4_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  8, 8,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु64पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC5_UNORM, SVGA3DBLOCKDESC_BC5_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_B4G4R4A4_UNORM, SVGA3DBLOCKDESC_RGBA_UNORM,
      अणु1, 1, 1पूर्ण,  2, 2,
      अणुअणु4पूर्ण, अणु4पूर्ण, अणु4पूर्ण, अणु4पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु4पूर्ण, अणु8पूर्ण, अणु12पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC6H_TYPELESS, SVGA3DBLOCKDESC_BC6H_COMP_TYPELESS,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC6H_UF16, SVGA3DBLOCKDESC_BC6H_COMP_UF16,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC6H_SF16, SVGA3DBLOCKDESC_BC6H_COMP_SF16,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC7_TYPELESS, SVGA3DBLOCKDESC_BC7_COMP_TYPELESS,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC7_UNORM, SVGA3DBLOCKDESC_BC7_COMP_UNORM,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_BC7_UNORM_SRGB, SVGA3DBLOCKDESC_BC7_COMP_UNORM_SRGB,
      अणु4, 4, 1पूर्ण,  16, 16,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु128पूर्ण, अणु0पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु0पूर्ण, अणु0पूर्ण, अणु0पूर्णपूर्णपूर्ण,

   अणुSVGA3D_AYUV, SVGA3DBLOCKDESC_AYUV,
      अणु1, 1, 1पूर्ण,  4, 4,
      अणुअणु8पूर्ण, अणु8पूर्ण, अणु8पूर्ण, अणु8पूर्णपूर्ण,
      अणुअणु0पूर्ण, अणु8पूर्ण, अणु16पूर्ण, अणु24पूर्णपूर्णपूर्ण,
पूर्ण;

अटल अंतरभूत u32 clamped_umul32(u32 a, u32 b)
अणु
	uपूर्णांक64_t पंचांगp = (uपूर्णांक64_t) a*b;
	वापस (पंचांगp > (uपूर्णांक64_t) ((u32) -1)) ? (u32) -1 : पंचांगp;
पूर्ण

/**
 * svga3dsurface_get_desc - Look up the appropriate SVGA3dSurfaceDesc क्रम the
 * given क्रमmat.
 */
अटल अंतरभूत स्थिर काष्ठा svga3d_surface_desc *
svga3dsurface_get_desc(SVGA3dSurfaceFormat क्रमmat)
अणु
	अगर (क्रमmat < ARRAY_SIZE(svga3d_surface_descs))
		वापस &svga3d_surface_descs[क्रमmat];

	वापस &svga3d_surface_descs[SVGA3D_FORMAT_INVALID];
पूर्ण

/**
 * svga3dsurface_get_mip_size -  Given a base level size and the mip level,
 * compute the size of the mip level.
 */
अटल अंतरभूत surf_size_काष्ठा
svga3dsurface_get_mip_size(surf_size_काष्ठा base_level, u32 mip_level)
अणु
	surf_size_काष्ठा size;

	size.width = max_t(u32, base_level.width >> mip_level, 1);
	size.height = max_t(u32, base_level.height >> mip_level, 1);
	size.depth = max_t(u32, base_level.depth >> mip_level, 1);
	size.pad64 = 0;

	वापस size;
पूर्ण

अटल अंतरभूत व्योम
svga3dsurface_get_size_in_blocks(स्थिर काष्ठा svga3d_surface_desc *desc,
				 स्थिर surf_size_काष्ठा *pixel_size,
				 surf_size_काष्ठा *block_size)
अणु
	block_size->width = __KERNEL_DIV_ROUND_UP(pixel_size->width,
						  desc->block_size.width);
	block_size->height = __KERNEL_DIV_ROUND_UP(pixel_size->height,
						   desc->block_size.height);
	block_size->depth = __KERNEL_DIV_ROUND_UP(pixel_size->depth,
						  desc->block_size.depth);
पूर्ण

अटल अंतरभूत bool
svga3dsurface_is_planar_surface(स्थिर काष्ठा svga3d_surface_desc *desc)
अणु
	वापस (desc->block_desc & SVGA3DBLOCKDESC_PLANAR_YUV) != 0;
पूर्ण

अटल अंतरभूत u32
svga3dsurface_calculate_pitch(स्थिर काष्ठा svga3d_surface_desc *desc,
			      स्थिर surf_size_काष्ठा *size)
अणु
	u32 pitch;
	surf_size_काष्ठा blocks;

	svga3dsurface_get_size_in_blocks(desc, size, &blocks);

	pitch = blocks.width * desc->pitch_bytes_per_block;

	वापस pitch;
पूर्ण

/**
 * svga3dsurface_get_image_buffer_size - Calculates image buffer size.
 *
 * Return the number of bytes of buffer space required to store one image of a
 * surface, optionally using the specअगरied pitch.
 *
 * If pitch is zero, it is assumed that rows are tightly packed.
 *
 * This function is overflow-safe. If the result would have overflowed, instead
 * we वापस MAX_UINT32.
 */
अटल अंतरभूत u32
svga3dsurface_get_image_buffer_size(स्थिर काष्ठा svga3d_surface_desc *desc,
				    स्थिर surf_size_काष्ठा *size,
				    u32 pitch)
अणु
	surf_size_काष्ठा image_blocks;
	u32 slice_size, total_size;

	svga3dsurface_get_size_in_blocks(desc, size, &image_blocks);

	अगर (svga3dsurface_is_planar_surface(desc)) अणु
		total_size = clamped_umul32(image_blocks.width,
					    image_blocks.height);
		total_size = clamped_umul32(total_size, image_blocks.depth);
		total_size = clamped_umul32(total_size, desc->bytes_per_block);
		वापस total_size;
	पूर्ण

	अगर (pitch == 0)
		pitch = svga3dsurface_calculate_pitch(desc, size);

	slice_size = clamped_umul32(image_blocks.height, pitch);
	total_size = clamped_umul32(slice_size, image_blocks.depth);

	वापस total_size;
पूर्ण

/**
 * svga3dsurface_get_serialized_size - Get the serialized size क्रम the image.
 */
अटल अंतरभूत u32
svga3dsurface_get_serialized_size(SVGA3dSurfaceFormat क्रमmat,
				  surf_size_काष्ठा base_level_size,
				  u32 num_mip_levels,
				  u32 num_layers)
अणु
	स्थिर काष्ठा svga3d_surface_desc *desc = svga3dsurface_get_desc(क्रमmat);
	u32 total_size = 0;
	u32 mip;

	क्रम (mip = 0; mip < num_mip_levels; mip++) अणु
		surf_size_काष्ठा size =
			svga3dsurface_get_mip_size(base_level_size, mip);
		total_size += svga3dsurface_get_image_buffer_size(desc,
								  &size, 0);
	पूर्ण

	वापस total_size * num_layers;
पूर्ण

/**
 * svga3dsurface_get_serialized_size_extended - Returns the number of bytes
 * required क्रम a surface with given parameters. Support क्रम sample count.
 */
अटल अंतरभूत u32
svga3dsurface_get_serialized_size_extended(SVGA3dSurfaceFormat क्रमmat,
					   surf_size_काष्ठा base_level_size,
					   u32 num_mip_levels,
					   u32 num_layers,
					   u32 num_samples)
अणु
	uपूर्णांक64_t total_size =
		svga3dsurface_get_serialized_size(क्रमmat,
						  base_level_size,
						  num_mip_levels,
						  num_layers);
	total_size *= max_t(u32, 1, num_samples);

	वापस min_t(uपूर्णांक64_t, total_size, (uपूर्णांक64_t)U32_MAX);
पूर्ण

/**
 * svga3dsurface_get_pixel_offset - Compute the offset (in bytes) to a pixel
 * in an image (or volume).
 *
 * @width: The image width in pixels.
 * @height: The image height in pixels
 */
अटल अंतरभूत u32
svga3dsurface_get_pixel_offset(SVGA3dSurfaceFormat क्रमmat,
			       u32 width, u32 height,
			       u32 x, u32 y, u32 z)
अणु
	स्थिर काष्ठा svga3d_surface_desc *desc = svga3dsurface_get_desc(क्रमmat);
	स्थिर u32 bw = desc->block_size.width, bh = desc->block_size.height;
	स्थिर u32 bd = desc->block_size.depth;
	स्थिर u32 rowstride = __KERNEL_DIV_ROUND_UP(width, bw) *
			      desc->bytes_per_block;
	स्थिर u32 imgstride = __KERNEL_DIV_ROUND_UP(height, bh) * rowstride;
	स्थिर u32 offset = (z / bd * imgstride +
			    y / bh * rowstride +
			    x / bw * desc->bytes_per_block);
	वापस offset;
पूर्ण

अटल अंतरभूत u32
svga3dsurface_get_image_offset(SVGA3dSurfaceFormat क्रमmat,
			       surf_size_काष्ठा baseLevelSize,
			       u32 numMipLevels,
			       u32 face,
			       u32 mip)

अणु
	u32 offset;
	u32 mipChainBytes;
	u32 mipChainBytesToLevel;
	u32 i;
	स्थिर काष्ठा svga3d_surface_desc *desc;
	surf_size_काष्ठा mipSize;
	u32 bytes;

	desc = svga3dsurface_get_desc(क्रमmat);

	mipChainBytes = 0;
	mipChainBytesToLevel = 0;
	क्रम (i = 0; i < numMipLevels; i++) अणु
		mipSize = svga3dsurface_get_mip_size(baseLevelSize, i);
		bytes = svga3dsurface_get_image_buffer_size(desc, &mipSize, 0);
		mipChainBytes += bytes;
		अगर (i < mip)
			mipChainBytesToLevel += bytes;
	पूर्ण

	offset = mipChainBytes * face + mipChainBytesToLevel;

	वापस offset;
पूर्ण


/**
 * svga3dsurface_is_gb_screen_target_क्रमmat - Is the specअगरied क्रमmat usable as
 *                                            a ScreenTarget?
 *                                            (with just the GBObjects cap-bit
 *                                             set)
 * @क्रमmat: क्रमmat to queried
 *
 * RETURNS:
 * true अगर queried क्रमmat is valid क्रम screen tarमाला_लो
 */
अटल अंतरभूत bool
svga3dsurface_is_gb_screen_target_क्रमmat(SVGA3dSurfaceFormat क्रमmat)
अणु
	वापस (क्रमmat == SVGA3D_X8R8G8B8 ||
		क्रमmat == SVGA3D_A8R8G8B8 ||
		क्रमmat == SVGA3D_R5G6B5   ||
		क्रमmat == SVGA3D_X1R5G5B5 ||
		क्रमmat == SVGA3D_A1R5G5B5 ||
		क्रमmat == SVGA3D_P8);
पूर्ण


/**
 * svga3dsurface_is_dx_screen_target_क्रमmat - Is the specअगरied क्रमmat usable as
 *                                            a ScreenTarget?
 *                                            (with DX10 enabled)
 *
 * @क्रमmat: क्रमmat to queried
 *
 * Results:
 * true अगर queried क्रमmat is valid क्रम screen tarमाला_लो
 */
अटल अंतरभूत bool
svga3dsurface_is_dx_screen_target_क्रमmat(SVGA3dSurfaceFormat क्रमmat)
अणु
	वापस (क्रमmat == SVGA3D_R8G8B8A8_UNORM ||
		क्रमmat == SVGA3D_B8G8R8A8_UNORM ||
		क्रमmat == SVGA3D_B8G8R8X8_UNORM);
पूर्ण


/**
 * svga3dsurface_is_screen_target_क्रमmat - Is the specअगरied क्रमmat usable as a
 *                                         ScreenTarget?
 *                                         (क्रम some combination of caps)
 *
 * @क्रमmat: क्रमmat to queried
 *
 * Results:
 * true अगर queried क्रमmat is valid क्रम screen tarमाला_लो
 */
अटल अंतरभूत bool
svga3dsurface_is_screen_target_क्रमmat(SVGA3dSurfaceFormat क्रमmat)
अणु
	अगर (svga3dsurface_is_gb_screen_target_क्रमmat(क्रमmat)) अणु
		वापस true;
	पूर्ण
	वापस svga3dsurface_is_dx_screen_target_क्रमmat(क्रमmat);
पूर्ण

/**
 * काष्ठा svga3dsurface_mip - Mimpmap level inक्रमmation
 * @bytes: Bytes required in the backing store of this mipmap level.
 * @img_stride: Byte stride per image.
 * @row_stride: Byte stride per block row.
 * @size: The size of the mipmap.
 */
काष्ठा svga3dsurface_mip अणु
	माप_प्रकार bytes;
	माप_प्रकार img_stride;
	माप_प्रकार row_stride;
	काष्ठा drm_vmw_size size;

पूर्ण;

/**
 * काष्ठा svga3dsurface_cache - Cached surface inक्रमmation
 * @desc: Poपूर्णांकer to the surface descriptor
 * @mip: Array of mipmap level inक्रमmation. Valid size is @num_mip_levels.
 * @mip_chain_bytes: Bytes required in the backing store क्रम the whole chain
 * of mip levels.
 * @sheet_bytes: Bytes required in the backing store क्रम a sheet
 * representing a single sample.
 * @num_mip_levels: Valid size of the @mip array. Number of mipmap levels in
 * a chain.
 * @num_layers: Number of slices in an array texture or number of faces in
 * a cubemap texture.
 */
काष्ठा svga3dsurface_cache अणु
	स्थिर काष्ठा svga3d_surface_desc *desc;
	काष्ठा svga3dsurface_mip mip[DRM_VMW_MAX_MIP_LEVELS];
	माप_प्रकार mip_chain_bytes;
	माप_प्रकार sheet_bytes;
	u32 num_mip_levels;
	u32 num_layers;
पूर्ण;

/**
 * काष्ठा svga3dsurface_loc - Surface location
 * @sub_resource: Surface subresource. Defined as layer * num_mip_levels +
 * mip_level.
 * @x: X coordinate.
 * @y: Y coordinate.
 * @z: Z coordinate.
 */
काष्ठा svga3dsurface_loc अणु
	u32 sub_resource;
	u32 x, y, z;
पूर्ण;

/**
 * svga3dsurface_subres - Compute the subresource from layer and mipmap.
 * @cache: Surface layout data.
 * @mip_level: The mipmap level.
 * @layer: The surface layer (face or array slice).
 *
 * Return: The subresource.
 */
अटल अंतरभूत u32 svga3dsurface_subres(स्थिर काष्ठा svga3dsurface_cache *cache,
				       u32 mip_level, u32 layer)
अणु
	वापस cache->num_mip_levels * layer + mip_level;
पूर्ण

/**
 * svga3dsurface_setup_cache - Build a surface cache entry
 * @size: The surface base level dimensions.
 * @क्रमmat: The surface क्रमmat.
 * @num_mip_levels: Number of mipmap levels.
 * @num_layers: Number of layers.
 * @cache: Poपूर्णांकer to a काष्ठा svga3dsurface_cach object to be filled in.
 *
 * Return: Zero on success, -EINVAL on invalid surface layout.
 */
अटल अंतरभूत पूर्णांक svga3dsurface_setup_cache(स्थिर काष्ठा drm_vmw_size *size,
					    SVGA3dSurfaceFormat क्रमmat,
					    u32 num_mip_levels,
					    u32 num_layers,
					    u32 num_samples,
					    काष्ठा svga3dsurface_cache *cache)
अणु
	स्थिर काष्ठा svga3d_surface_desc *desc;
	u32 i;

	स_रखो(cache, 0, माप(*cache));
	cache->desc = desc = svga3dsurface_get_desc(क्रमmat);
	cache->num_mip_levels = num_mip_levels;
	cache->num_layers = num_layers;
	क्रम (i = 0; i < cache->num_mip_levels; i++) अणु
		काष्ठा svga3dsurface_mip *mip = &cache->mip[i];

		mip->size = svga3dsurface_get_mip_size(*size, i);
		mip->bytes = svga3dsurface_get_image_buffer_size
			(desc, &mip->size, 0);
		mip->row_stride =
			__KERNEL_DIV_ROUND_UP(mip->size.width,
					      desc->block_size.width) *
			desc->bytes_per_block * num_samples;
		अगर (!mip->row_stride)
			जाओ invalid_dim;

		mip->img_stride =
			__KERNEL_DIV_ROUND_UP(mip->size.height,
					      desc->block_size.height) *
			mip->row_stride;
		अगर (!mip->img_stride)
			जाओ invalid_dim;

		cache->mip_chain_bytes += mip->bytes;
	पूर्ण
	cache->sheet_bytes = cache->mip_chain_bytes * num_layers;
	अगर (!cache->sheet_bytes)
		जाओ invalid_dim;

	वापस 0;

invalid_dim:
	VMW_DEBUG_USER("Invalid surface layout for dirty tracking.\n");
	वापस -EINVAL;
पूर्ण

/**
 * svga3dsurface_get_loc - Get a surface location from an offset पूर्णांकo the
 * backing store
 * @cache: Surface layout data.
 * @loc: Poपूर्णांकer to a काष्ठा svga3dsurface_loc to be filled in.
 * @offset: Offset पूर्णांकo the surface backing store.
 */
अटल अंतरभूत व्योम
svga3dsurface_get_loc(स्थिर काष्ठा svga3dsurface_cache *cache,
		      काष्ठा svga3dsurface_loc *loc,
		      माप_प्रकार offset)
अणु
	स्थिर काष्ठा svga3dsurface_mip *mip = &cache->mip[0];
	स्थिर काष्ठा svga3d_surface_desc *desc = cache->desc;
	u32 layer;
	पूर्णांक i;

	अगर (offset >= cache->sheet_bytes)
		offset %= cache->sheet_bytes;

	layer = offset / cache->mip_chain_bytes;
	offset -= layer * cache->mip_chain_bytes;
	क्रम (i = 0; i < cache->num_mip_levels; ++i, ++mip) अणु
		अगर (mip->bytes > offset)
			अवरोध;
		offset -= mip->bytes;
	पूर्ण

	loc->sub_resource = svga3dsurface_subres(cache, i, layer);
	loc->z = offset / mip->img_stride;
	offset -= loc->z * mip->img_stride;
	loc->z *= desc->block_size.depth;
	loc->y = offset / mip->row_stride;
	offset -= loc->y * mip->row_stride;
	loc->y *= desc->block_size.height;
	loc->x = offset / desc->bytes_per_block;
	loc->x *= desc->block_size.width;
पूर्ण

/**
 * svga3dsurface_inc_loc - Clamp increment a surface location with one block
 * size
 * in each dimension.
 * @loc: Poपूर्णांकer to a काष्ठा svga3dsurface_loc to be incremented.
 *
 * When computing the size of a range as size = end - start, the range करोes not
 * include the end element. However a location representing the last byte
 * of a touched region in the backing store *is* included in the range.
 * This function modअगरies such a location to match the end definition
 * given as start + size which is the one used in a SVGA3dBox.
 */
अटल अंतरभूत व्योम
svga3dsurface_inc_loc(स्थिर काष्ठा svga3dsurface_cache *cache,
		      काष्ठा svga3dsurface_loc *loc)
अणु
	स्थिर काष्ठा svga3d_surface_desc *desc = cache->desc;
	u32 mip = loc->sub_resource % cache->num_mip_levels;
	स्थिर काष्ठा drm_vmw_size *size = &cache->mip[mip].size;

	loc->sub_resource++;
	loc->x += desc->block_size.width;
	अगर (loc->x > size->width)
		loc->x = size->width;
	loc->y += desc->block_size.height;
	अगर (loc->y > size->height)
		loc->y = size->height;
	loc->z += desc->block_size.depth;
	अगर (loc->z > size->depth)
		loc->z = size->depth;
पूर्ण

/**
 * svga3dsurface_min_loc - The start location in a subresource
 * @cache: Surface layout data.
 * @sub_resource: The subresource.
 * @loc: Poपूर्णांकer to a काष्ठा svga3dsurface_loc to be filled in.
 */
अटल अंतरभूत व्योम
svga3dsurface_min_loc(स्थिर काष्ठा svga3dsurface_cache *cache,
		      u32 sub_resource,
		      काष्ठा svga3dsurface_loc *loc)
अणु
	loc->sub_resource = sub_resource;
	loc->x = loc->y = loc->z = 0;
पूर्ण

/**
 * svga3dsurface_min_loc - The end location in a subresource
 * @cache: Surface layout data.
 * @sub_resource: The subresource.
 * @loc: Poपूर्णांकer to a काष्ठा svga3dsurface_loc to be filled in.
 *
 * Following the end definition given in svga3dsurface_inc_loc(),
 * Compute the end location of a surface subresource.
 */
अटल अंतरभूत व्योम
svga3dsurface_max_loc(स्थिर काष्ठा svga3dsurface_cache *cache,
		      u32 sub_resource,
		      काष्ठा svga3dsurface_loc *loc)
अणु
	स्थिर काष्ठा drm_vmw_size *size;
	u32 mip;

	loc->sub_resource = sub_resource + 1;
	mip = sub_resource % cache->num_mip_levels;
	size = &cache->mip[mip].size;
	loc->x = size->width;
	loc->y = size->height;
	loc->z = size->depth;
पूर्ण

#पूर्ण_अगर /* _SVGA3D_SURFACEDEFS_H_ */
