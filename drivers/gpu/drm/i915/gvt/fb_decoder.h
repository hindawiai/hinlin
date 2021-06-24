<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *
 * Contributors:
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Xu Han <xu.han@पूर्णांकel.com>
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Xiaoguang Chen <xiaoguang.chen@पूर्णांकel.com>
 *    Yang Liu <yang2.liu@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_FB_DECODER_H_
#घोषणा _GVT_FB_DECODER_H_

#समावेश <linux/types.h>

#समावेश "display/intel_display.h"

काष्ठा पूर्णांकel_vgpu;

#घोषणा _PLANE_CTL_FORMAT_SHIFT		24
#घोषणा _PLANE_CTL_TILED_SHIFT		10
#घोषणा _PIPE_V_SRCSZ_SHIFT		0
#घोषणा _PIPE_V_SRCSZ_MASK		(0xfff << _PIPE_V_SRCSZ_SHIFT)
#घोषणा _PIPE_H_SRCSZ_SHIFT		16
#घोषणा _PIPE_H_SRCSZ_MASK		(0x1fff << _PIPE_H_SRCSZ_SHIFT)

#घोषणा _PRI_PLANE_FMT_SHIFT		26
#घोषणा _PRI_PLANE_STRIDE_MASK		(0x3ff << 6)
#घोषणा _PRI_PLANE_X_OFF_SHIFT		0
#घोषणा _PRI_PLANE_X_OFF_MASK		(0x1fff << _PRI_PLANE_X_OFF_SHIFT)
#घोषणा _PRI_PLANE_Y_OFF_SHIFT		16
#घोषणा _PRI_PLANE_Y_OFF_MASK		(0xfff << _PRI_PLANE_Y_OFF_SHIFT)

#घोषणा _CURSOR_MODE			0x3f
#घोषणा _CURSOR_ALPHA_FORCE_SHIFT	8
#घोषणा _CURSOR_ALPHA_FORCE_MASK	(0x3 << _CURSOR_ALPHA_FORCE_SHIFT)
#घोषणा _CURSOR_ALPHA_PLANE_SHIFT	10
#घोषणा _CURSOR_ALPHA_PLANE_MASK	(0x3 << _CURSOR_ALPHA_PLANE_SHIFT)
#घोषणा _CURSOR_POS_X_SHIFT		0
#घोषणा _CURSOR_POS_X_MASK		(0x1fff << _CURSOR_POS_X_SHIFT)
#घोषणा _CURSOR_SIGN_X_SHIFT		15
#घोषणा _CURSOR_SIGN_X_MASK		(1 << _CURSOR_SIGN_X_SHIFT)
#घोषणा _CURSOR_POS_Y_SHIFT		16
#घोषणा _CURSOR_POS_Y_MASK		(0xfff << _CURSOR_POS_Y_SHIFT)
#घोषणा _CURSOR_SIGN_Y_SHIFT		31
#घोषणा _CURSOR_SIGN_Y_MASK		(1 << _CURSOR_SIGN_Y_SHIFT)

#घोषणा _SPRITE_FMT_SHIFT		25
#घोषणा _SPRITE_COLOR_ORDER_SHIFT	20
#घोषणा _SPRITE_YUV_ORDER_SHIFT		16
#घोषणा _SPRITE_STRIDE_SHIFT		6
#घोषणा _SPRITE_STRIDE_MASK		(0x1ff << _SPRITE_STRIDE_SHIFT)
#घोषणा _SPRITE_SIZE_WIDTH_SHIFT	0
#घोषणा _SPRITE_SIZE_HEIGHT_SHIFT	16
#घोषणा _SPRITE_SIZE_WIDTH_MASK		(0x1fff << _SPRITE_SIZE_WIDTH_SHIFT)
#घोषणा _SPRITE_SIZE_HEIGHT_MASK	(0xfff << _SPRITE_SIZE_HEIGHT_SHIFT)
#घोषणा _SPRITE_POS_X_SHIFT		0
#घोषणा _SPRITE_POS_Y_SHIFT		16
#घोषणा _SPRITE_POS_X_MASK		(0x1fff << _SPRITE_POS_X_SHIFT)
#घोषणा _SPRITE_POS_Y_MASK		(0xfff << _SPRITE_POS_Y_SHIFT)
#घोषणा _SPRITE_OFFSET_START_X_SHIFT	0
#घोषणा _SPRITE_OFFSET_START_Y_SHIFT	16
#घोषणा _SPRITE_OFFSET_START_X_MASK	(0x1fff << _SPRITE_OFFSET_START_X_SHIFT)
#घोषणा _SPRITE_OFFSET_START_Y_MASK	(0xfff << _SPRITE_OFFSET_START_Y_SHIFT)

क्रमागत GVT_FB_EVENT अणु
	FB_MODE_SET_START = 1,
	FB_MODE_SET_END,
	FB_DISPLAY_FLIP,
पूर्ण;

क्रमागत DDI_PORT अणु
	DDI_PORT_NONE	= 0,
	DDI_PORT_B	= 1,
	DDI_PORT_C	= 2,
	DDI_PORT_D	= 3,
	DDI_PORT_E	= 4
पूर्ण;

/* color space conversion and gamma correction are not included */
काष्ठा पूर्णांकel_vgpu_primary_plane_क्रमmat अणु
	u8	enabled;	/* plane is enabled */
	u32	tiled;		/* tiling mode: linear, X-tiled, Y tiled, etc */
	u8	bpp;		/* bits per pixel */
	u32	hw_क्रमmat;	/* क्रमmat field in the PRI_CTL रेजिस्टर */
	u32	drm_क्रमmat;	/* क्रमmat in DRM definition */
	u32	base;		/* framebuffer base in graphics memory */
	u64     base_gpa;
	u32	x_offset;	/* in pixels */
	u32	y_offset;	/* in lines */
	u32	width;		/* in pixels */
	u32	height;		/* in lines */
	u32	stride;		/* in bytes */
पूर्ण;

काष्ठा पूर्णांकel_vgpu_sprite_plane_क्रमmat अणु
	u8	enabled;	/* plane is enabled */
	u8	tiled;		/* X-tiled */
	u8	bpp;		/* bits per pixel */
	u32	hw_क्रमmat;	/* क्रमmat field in the SPR_CTL रेजिस्टर */
	u32	drm_क्रमmat;	/* क्रमmat in DRM definition */
	u32	base;		/* sprite base in graphics memory */
	u64     base_gpa;
	u32	x_pos;		/* in pixels */
	u32	y_pos;		/* in lines */
	u32	x_offset;	/* in pixels */
	u32	y_offset;	/* in lines */
	u32	width;		/* in pixels */
	u32	height;		/* in lines */
	u32	stride;		/* in bytes */
पूर्ण;

काष्ठा पूर्णांकel_vgpu_cursor_plane_क्रमmat अणु
	u8	enabled;
	u8	mode;		/* cursor mode select */
	u8	bpp;		/* bits per pixel */
	u32	drm_क्रमmat;	/* क्रमmat in DRM definition */
	u32	base;		/* cursor base in graphics memory */
	u64     base_gpa;
	u32	x_pos;		/* in pixels */
	u32	y_pos;		/* in lines */
	u8	x_sign;		/* X Position Sign */
	u8	y_sign;		/* Y Position Sign */
	u32	width;		/* in pixels */
	u32	height;		/* in lines */
	u32	x_hot;		/* in pixels */
	u32	y_hot;		/* in pixels */
पूर्ण;

काष्ठा पूर्णांकel_vgpu_pipe_क्रमmat अणु
	काष्ठा पूर्णांकel_vgpu_primary_plane_क्रमmat	primary;
	काष्ठा पूर्णांकel_vgpu_sprite_plane_क्रमmat	sprite;
	काष्ठा पूर्णांकel_vgpu_cursor_plane_क्रमmat	cursor;
	क्रमागत DDI_PORT ddi_port;  /* the DDI port that pipe is connected to */
पूर्ण;

काष्ठा पूर्णांकel_vgpu_fb_क्रमmat अणु
	काष्ठा पूर्णांकel_vgpu_pipe_क्रमmat	pipes[I915_MAX_PIPES];
पूर्ण;

पूर्णांक पूर्णांकel_vgpu_decode_primary_plane(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_primary_plane_क्रमmat *plane);
पूर्णांक पूर्णांकel_vgpu_decode_cursor_plane(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_cursor_plane_क्रमmat *plane);
पूर्णांक पूर्णांकel_vgpu_decode_sprite_plane(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_sprite_plane_क्रमmat *plane);

#पूर्ण_अगर
