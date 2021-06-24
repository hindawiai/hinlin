<शैली गुरु>
/* r128_state.c -- State support क्रम r128 -*- linux-c -*-
 * Created: Thu Jan 27 02:53:43 2000 by gareth@valinux.com
 */
/*
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
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
 *    Gareth Hughes <gareth@valinux.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/r128_drm.h>

#समावेश "r128_drv.h"

/* ================================================================
 * CCE hardware state programming functions
 */

अटल व्योम r128_emit_clip_rects(drm_r128_निजी_t *dev_priv,
				 काष्ठा drm_clip_rect *boxes, पूर्णांक count)
अणु
	u32 aux_sc_cntl = 0x00000000;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING((count < 3 ? count : 3) * 5 + 2);

	अगर (count >= 1) अणु
		OUT_RING(CCE_PACKET0(R128_AUX1_SC_LEFT, 3));
		OUT_RING(boxes[0].x1);
		OUT_RING(boxes[0].x2 - 1);
		OUT_RING(boxes[0].y1);
		OUT_RING(boxes[0].y2 - 1);

		aux_sc_cntl |= (R128_AUX1_SC_EN | R128_AUX1_SC_MODE_OR);
	पूर्ण
	अगर (count >= 2) अणु
		OUT_RING(CCE_PACKET0(R128_AUX2_SC_LEFT, 3));
		OUT_RING(boxes[1].x1);
		OUT_RING(boxes[1].x2 - 1);
		OUT_RING(boxes[1].y1);
		OUT_RING(boxes[1].y2 - 1);

		aux_sc_cntl |= (R128_AUX2_SC_EN | R128_AUX2_SC_MODE_OR);
	पूर्ण
	अगर (count >= 3) अणु
		OUT_RING(CCE_PACKET0(R128_AUX3_SC_LEFT, 3));
		OUT_RING(boxes[2].x1);
		OUT_RING(boxes[2].x2 - 1);
		OUT_RING(boxes[2].y1);
		OUT_RING(boxes[2].y2 - 1);

		aux_sc_cntl |= (R128_AUX3_SC_EN | R128_AUX3_SC_MODE_OR);
	पूर्ण

	OUT_RING(CCE_PACKET0(R128_AUX_SC_CNTL, 0));
	OUT_RING(aux_sc_cntl);

	ADVANCE_RING();
पूर्ण

अटल __अंतरभूत__ व्योम r128_emit_core(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_context_regs_t *ctx = &sarea_priv->context_state;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_SCALE_3D_CNTL, 0));
	OUT_RING(ctx->scale_3d_cntl);

	ADVANCE_RING();
पूर्ण

अटल __अंतरभूत__ व्योम r128_emit_context(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_context_regs_t *ctx = &sarea_priv->context_state;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(13);

	OUT_RING(CCE_PACKET0(R128_DST_PITCH_OFFSET_C, 11));
	OUT_RING(ctx->dst_pitch_offset_c);
	OUT_RING(ctx->dp_gui_master_cntl_c);
	OUT_RING(ctx->sc_top_left_c);
	OUT_RING(ctx->sc_bottom_right_c);
	OUT_RING(ctx->z_offset_c);
	OUT_RING(ctx->z_pitch_c);
	OUT_RING(ctx->z_sten_cntl_c);
	OUT_RING(ctx->tex_cntl_c);
	OUT_RING(ctx->misc_3d_state_cntl_reg);
	OUT_RING(ctx->texture_clr_cmp_clr_c);
	OUT_RING(ctx->texture_clr_cmp_msk_c);
	OUT_RING(ctx->fog_color_c);

	ADVANCE_RING();
पूर्ण

अटल __अंतरभूत__ व्योम r128_emit_setup(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_context_regs_t *ctx = &sarea_priv->context_state;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(3);

	OUT_RING(CCE_PACKET1(R128_SETUP_CNTL, R128_PM4_VC_FPU_SETUP));
	OUT_RING(ctx->setup_cntl);
	OUT_RING(ctx->pm4_vc_fpu_setup);

	ADVANCE_RING();
पूर्ण

अटल __अंतरभूत__ व्योम r128_emit_masks(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_context_regs_t *ctx = &sarea_priv->context_state;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(5);

	OUT_RING(CCE_PACKET0(R128_DP_WRITE_MASK, 0));
	OUT_RING(ctx->dp_ग_लिखो_mask);

	OUT_RING(CCE_PACKET0(R128_STEN_REF_MASK_C, 1));
	OUT_RING(ctx->sten_ref_mask_c);
	OUT_RING(ctx->plane_3d_mask_c);

	ADVANCE_RING();
पूर्ण

अटल __अंतरभूत__ व्योम r128_emit_winकरोw(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_context_regs_t *ctx = &sarea_priv->context_state;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_WINDOW_XY_OFFSET, 0));
	OUT_RING(ctx->winकरोw_xy_offset);

	ADVANCE_RING();
पूर्ण

अटल __अंतरभूत__ व्योम r128_emit_tex0(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_context_regs_t *ctx = &sarea_priv->context_state;
	drm_r128_texture_regs_t *tex = &sarea_priv->tex_state[0];
	पूर्णांक i;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(7 + R128_MAX_TEXTURE_LEVELS);

	OUT_RING(CCE_PACKET0(R128_PRIM_TEX_CNTL_C,
			     2 + R128_MAX_TEXTURE_LEVELS));
	OUT_RING(tex->tex_cntl);
	OUT_RING(tex->tex_combine_cntl);
	OUT_RING(ctx->tex_size_pitch_c);
	क्रम (i = 0; i < R128_MAX_TEXTURE_LEVELS; i++)
		OUT_RING(tex->tex_offset[i]);

	OUT_RING(CCE_PACKET0(R128_CONSTANT_COLOR_C, 1));
	OUT_RING(ctx->स्थिरant_color_c);
	OUT_RING(tex->tex_border_color);

	ADVANCE_RING();
पूर्ण

अटल __अंतरभूत__ व्योम r128_emit_tex1(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_r128_texture_regs_t *tex = &sarea_priv->tex_state[1];
	पूर्णांक i;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(5 + R128_MAX_TEXTURE_LEVELS);

	OUT_RING(CCE_PACKET0(R128_SEC_TEX_CNTL_C, 1 + R128_MAX_TEXTURE_LEVELS));
	OUT_RING(tex->tex_cntl);
	OUT_RING(tex->tex_combine_cntl);
	क्रम (i = 0; i < R128_MAX_TEXTURE_LEVELS; i++)
		OUT_RING(tex->tex_offset[i]);

	OUT_RING(CCE_PACKET0(R128_SEC_TEXTURE_BORDER_COLOR_C, 0));
	OUT_RING(tex->tex_border_color);

	ADVANCE_RING();
पूर्ण

अटल व्योम r128_emit_state(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित पूर्णांक dirty = sarea_priv->dirty;

	DRM_DEBUG("dirty=0x%08x\n", dirty);

	अगर (dirty & R128_UPLOAD_CORE) अणु
		r128_emit_core(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_CORE;
	पूर्ण

	अगर (dirty & R128_UPLOAD_CONTEXT) अणु
		r128_emit_context(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_CONTEXT;
	पूर्ण

	अगर (dirty & R128_UPLOAD_SETUP) अणु
		r128_emit_setup(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_SETUP;
	पूर्ण

	अगर (dirty & R128_UPLOAD_MASKS) अणु
		r128_emit_masks(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_MASKS;
	पूर्ण

	अगर (dirty & R128_UPLOAD_WINDOW) अणु
		r128_emit_winकरोw(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_WINDOW;
	पूर्ण

	अगर (dirty & R128_UPLOAD_TEX0) अणु
		r128_emit_tex0(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_TEX0;
	पूर्ण

	अगर (dirty & R128_UPLOAD_TEX1) अणु
		r128_emit_tex1(dev_priv);
		sarea_priv->dirty &= ~R128_UPLOAD_TEX1;
	पूर्ण

	/* Turn off the texture cache flushing */
	sarea_priv->context_state.tex_cntl_c &= ~R128_TEX_CACHE_FLUSH;

	sarea_priv->dirty &= ~R128_REQUIRE_QUIESCENCE;
पूर्ण

#अगर R128_PERFORMANCE_BOXES
/* ================================================================
 * Perक्रमmance monitoring functions
 */

अटल व्योम r128_clear_box(drm_r128_निजी_t *dev_priv,
			   पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, पूर्णांक r, पूर्णांक g, पूर्णांक b)
अणु
	u32 pitch, offset;
	u32 fb_bpp, color;
	RING_LOCALS;

	चयन (dev_priv->fb_bpp) अणु
	हाल 16:
		fb_bpp = R128_GMC_DST_16BPP;
		color = (((r & 0xf8) << 8) |
			 ((g & 0xfc) << 3) | ((b & 0xf8) >> 3));
		अवरोध;
	हाल 24:
		fb_bpp = R128_GMC_DST_24BPP;
		color = ((r << 16) | (g << 8) | b);
		अवरोध;
	हाल 32:
		fb_bpp = R128_GMC_DST_32BPP;
		color = (((0xff) << 24) | (r << 16) | (g << 8) | b);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	offset = dev_priv->back_offset;
	pitch = dev_priv->back_pitch >> 3;

	BEGIN_RING(6);

	OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
	OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
		 R128_GMC_BRUSH_SOLID_COLOR |
		 fb_bpp |
		 R128_GMC_SRC_DATATYPE_COLOR |
		 R128_ROP3_P |
		 R128_GMC_CLR_CMP_CNTL_DIS | R128_GMC_AUX_CLIP_DIS);

	OUT_RING((pitch << 21) | (offset >> 5));
	OUT_RING(color);

	OUT_RING((x << 16) | y);
	OUT_RING((w << 16) | h);

	ADVANCE_RING();
पूर्ण

अटल व्योम r128_cce_perक्रमmance_boxes(drm_r128_निजी_t *dev_priv)
अणु
	अगर (atomic_पढ़ो(&dev_priv->idle_count) == 0)
		r128_clear_box(dev_priv, 64, 4, 8, 8, 0, 255, 0);
	अन्यथा
		atomic_set(&dev_priv->idle_count, 0);
पूर्ण

#पूर्ण_अगर

/* ================================================================
 * CCE command dispatch functions
 */

अटल व्योम r128_prपूर्णांक_dirty(स्थिर अक्षर *msg, अचिन्हित पूर्णांक flags)
अणु
	DRM_INFO("%s: (0x%x) %s%s%s%s%s%s%s%s%s\n",
		 msg,
		 flags,
		 (flags & R128_UPLOAD_CORE) ? "core, " : "",
		 (flags & R128_UPLOAD_CONTEXT) ? "context, " : "",
		 (flags & R128_UPLOAD_SETUP) ? "setup, " : "",
		 (flags & R128_UPLOAD_TEX0) ? "tex0, " : "",
		 (flags & R128_UPLOAD_TEX1) ? "tex1, " : "",
		 (flags & R128_UPLOAD_MASKS) ? "masks, " : "",
		 (flags & R128_UPLOAD_WINDOW) ? "window, " : "",
		 (flags & R128_UPLOAD_CLIPRECTS) ? "cliprects, " : "",
		 (flags & R128_REQUIRE_QUIESCENCE) ? "quiescence, " : "");
पूर्ण

अटल व्योम r128_cce_dispatch_clear(काष्ठा drm_device *dev,
				    drm_r128_clear_t *clear)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	पूर्णांक nbox = sarea_priv->nbox;
	काष्ठा drm_clip_rect *pbox = sarea_priv->boxes;
	अचिन्हित पूर्णांक flags = clear->flags;
	पूर्णांक i;
	RING_LOCALS;
	DRM_DEBUG("\n");

	अगर (dev_priv->page_flipping && dev_priv->current_page == 1) अणु
		अचिन्हित पूर्णांक पंचांगp = flags;

		flags &= ~(R128_FRONT | R128_BACK);
		अगर (पंचांगp & R128_FRONT)
			flags |= R128_BACK;
		अगर (पंचांगp & R128_BACK)
			flags |= R128_FRONT;
	पूर्ण

	क्रम (i = 0; i < nbox; i++) अणु
		पूर्णांक x = pbox[i].x1;
		पूर्णांक y = pbox[i].y1;
		पूर्णांक w = pbox[i].x2 - x;
		पूर्णांक h = pbox[i].y2 - y;

		DRM_DEBUG("dispatch clear %d,%d-%d,%d flags 0x%x\n",
			  pbox[i].x1, pbox[i].y1, pbox[i].x2,
			  pbox[i].y2, flags);

		अगर (flags & (R128_FRONT | R128_BACK)) अणु
			BEGIN_RING(2);

			OUT_RING(CCE_PACKET0(R128_DP_WRITE_MASK, 0));
			OUT_RING(clear->color_mask);

			ADVANCE_RING();
		पूर्ण

		अगर (flags & R128_FRONT) अणु
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->color_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_AUX_CLIP_DIS);

			OUT_RING(dev_priv->front_pitch_offset_c);
			OUT_RING(clear->clear_color);

			OUT_RING((x << 16) | y);
			OUT_RING((w << 16) | h);

			ADVANCE_RING();
		पूर्ण

		अगर (flags & R128_BACK) अणु
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->color_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_AUX_CLIP_DIS);

			OUT_RING(dev_priv->back_pitch_offset_c);
			OUT_RING(clear->clear_color);

			OUT_RING((x << 16) | y);
			OUT_RING((w << 16) | h);

			ADVANCE_RING();
		पूर्ण

		अगर (flags & R128_DEPTH) अणु
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->depth_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_AUX_CLIP_DIS | R128_GMC_WR_MSK_DIS);

			OUT_RING(dev_priv->depth_pitch_offset_c);
			OUT_RING(clear->clear_depth);

			OUT_RING((x << 16) | y);
			OUT_RING((w << 16) | h);

			ADVANCE_RING();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r128_cce_dispatch_swap(काष्ठा drm_device *dev)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	पूर्णांक nbox = sarea_priv->nbox;
	काष्ठा drm_clip_rect *pbox = sarea_priv->boxes;
	पूर्णांक i;
	RING_LOCALS;
	DRM_DEBUG("\n");

#अगर R128_PERFORMANCE_BOXES
	/* Do some trivial perक्रमmance monitoring...
	 */
	r128_cce_perक्रमmance_boxes(dev_priv);
#पूर्ण_अगर

	क्रम (i = 0; i < nbox; i++) अणु
		पूर्णांक x = pbox[i].x1;
		पूर्णांक y = pbox[i].y1;
		पूर्णांक w = pbox[i].x2 - x;
		पूर्णांक h = pbox[i].y2 - y;

		BEGIN_RING(7);

		OUT_RING(CCE_PACKET3(R128_CNTL_BITBLT_MULTI, 5));
		OUT_RING(R128_GMC_SRC_PITCH_OFFSET_CNTL |
			 R128_GMC_DST_PITCH_OFFSET_CNTL |
			 R128_GMC_BRUSH_NONE |
			 (dev_priv->color_fmt << 8) |
			 R128_GMC_SRC_DATATYPE_COLOR |
			 R128_ROP3_S |
			 R128_DP_SRC_SOURCE_MEMORY |
			 R128_GMC_CLR_CMP_CNTL_DIS |
			 R128_GMC_AUX_CLIP_DIS | R128_GMC_WR_MSK_DIS);

		/* Make this work even अगर front & back are flipped:
		 */
		अगर (dev_priv->current_page == 0) अणु
			OUT_RING(dev_priv->back_pitch_offset_c);
			OUT_RING(dev_priv->front_pitch_offset_c);
		पूर्ण अन्यथा अणु
			OUT_RING(dev_priv->front_pitch_offset_c);
			OUT_RING(dev_priv->back_pitch_offset_c);
		पूर्ण

		OUT_RING((x << 16) | y);
		OUT_RING((x << 16) | y);
		OUT_RING((w << 16) | h);

		ADVANCE_RING();
	पूर्ण

	/* Increment the frame counter.  The client-side 3D driver must
	 * throttle the framerate by रुकोing क्रम this value beक्रमe
	 * perक्रमming the swapbuffer ioctl.
	 */
	dev_priv->sarea_priv->last_frame++;

	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_LAST_FRAME_REG, 0));
	OUT_RING(dev_priv->sarea_priv->last_frame);

	ADVANCE_RING();
पूर्ण

अटल व्योम r128_cce_dispatch_flip(काष्ठा drm_device *dev)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	RING_LOCALS;
	DRM_DEBUG("page=%d pfCurrentPage=%d\n",
		  dev_priv->current_page, dev_priv->sarea_priv->pfCurrentPage);

#अगर R128_PERFORMANCE_BOXES
	/* Do some trivial perक्रमmance monitoring...
	 */
	r128_cce_perक्रमmance_boxes(dev_priv);
#पूर्ण_अगर

	BEGIN_RING(4);

	R128_WAIT_UNTIL_PAGE_FLIPPED();
	OUT_RING(CCE_PACKET0(R128_CRTC_OFFSET, 0));

	अगर (dev_priv->current_page == 0)
		OUT_RING(dev_priv->back_offset);
	अन्यथा
		OUT_RING(dev_priv->front_offset);

	ADVANCE_RING();

	/* Increment the frame counter.  The client-side 3D driver must
	 * throttle the framerate by रुकोing क्रम this value beक्रमe
	 * perक्रमming the swapbuffer ioctl.
	 */
	dev_priv->sarea_priv->last_frame++;
	dev_priv->sarea_priv->pfCurrentPage = dev_priv->current_page =
	    1 - dev_priv->current_page;

	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_LAST_FRAME_REG, 0));
	OUT_RING(dev_priv->sarea_priv->last_frame);

	ADVANCE_RING();
पूर्ण

अटल व्योम r128_cce_dispatch_vertex(काष्ठा drm_device *dev, काष्ठा drm_buf *buf)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	पूर्णांक क्रमmat = sarea_priv->vc_क्रमmat;
	पूर्णांक offset = buf->bus_address;
	पूर्णांक size = buf->used;
	पूर्णांक prim = buf_priv->prim;
	पूर्णांक i = 0;
	RING_LOCALS;
	DRM_DEBUG("buf=%d nbox=%d\n", buf->idx, sarea_priv->nbox);

	अगर (0)
		r128_prपूर्णांक_dirty("dispatch_vertex", sarea_priv->dirty);

	अगर (buf->used) अणु
		buf_priv->dispatched = 1;

		अगर (sarea_priv->dirty & ~R128_UPLOAD_CLIPRECTS)
			r128_emit_state(dev_priv);

		करो अणु
			/* Emit the next set of up to three cliprects */
			अगर (i < sarea_priv->nbox) अणु
				r128_emit_clip_rects(dev_priv,
						     &sarea_priv->boxes[i],
						     sarea_priv->nbox - i);
			पूर्ण

			/* Emit the vertex buffer rendering commands */
			BEGIN_RING(5);

			OUT_RING(CCE_PACKET3(R128_3D_RNDR_GEN_INDX_PRIM, 3));
			OUT_RING(offset);
			OUT_RING(size);
			OUT_RING(क्रमmat);
			OUT_RING(prim | R128_CCE_VC_CNTL_PRIM_WALK_LIST |
				 (size << R128_CCE_VC_CNTL_NUM_SHIFT));

			ADVANCE_RING();

			i += 3;
		पूर्ण जबतक (i < sarea_priv->nbox);
	पूर्ण

	अगर (buf_priv->discard) अणु
		buf_priv->age = dev_priv->sarea_priv->last_dispatch;

		/* Emit the vertex buffer age */
		BEGIN_RING(2);

		OUT_RING(CCE_PACKET0(R128_LAST_DISPATCH_REG, 0));
		OUT_RING(buf_priv->age);

		ADVANCE_RING();

		buf->pending = 1;
		buf->used = 0;
		/* FIXME: Check dispatched field */
		buf_priv->dispatched = 0;
	पूर्ण

	dev_priv->sarea_priv->last_dispatch++;

	sarea_priv->dirty &= ~R128_UPLOAD_CLIPRECTS;
	sarea_priv->nbox = 0;
पूर्ण

अटल व्योम r128_cce_dispatch_indirect(काष्ठा drm_device *dev,
				       काष्ठा drm_buf *buf, पूर्णांक start, पूर्णांक end)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_buf_priv_t *buf_priv = buf->dev_निजी;
	RING_LOCALS;
	DRM_DEBUG("indirect: buf=%d s=0x%x e=0x%x\n", buf->idx, start, end);

	अगर (start != end) अणु
		पूर्णांक offset = buf->bus_address + start;
		पूर्णांक dwords = (end - start + 3) / माप(u32);

		/* Indirect buffer data must be an even number of
		 * dwords, so अगर we've been given an odd number we must
		 * pad the data with a Type-2 CCE packet.
		 */
		अगर (dwords & 1) अणु
			u32 *data = (u32 *)
			    ((अक्षर *)dev->agp_buffer_map->handle
			     + buf->offset + start);
			data[dwords++] = cpu_to_le32(R128_CCE_PACKET2);
		पूर्ण

		buf_priv->dispatched = 1;

		/* Fire off the indirect buffer */
		BEGIN_RING(3);

		OUT_RING(CCE_PACKET0(R128_PM4_IW_INDOFF, 1));
		OUT_RING(offset);
		OUT_RING(dwords);

		ADVANCE_RING();
	पूर्ण

	अगर (buf_priv->discard) अणु
		buf_priv->age = dev_priv->sarea_priv->last_dispatch;

		/* Emit the indirect buffer age */
		BEGIN_RING(2);

		OUT_RING(CCE_PACKET0(R128_LAST_DISPATCH_REG, 0));
		OUT_RING(buf_priv->age);

		ADVANCE_RING();

		buf->pending = 1;
		buf->used = 0;
		/* FIXME: Check dispatched field */
		buf_priv->dispatched = 0;
	पूर्ण

	dev_priv->sarea_priv->last_dispatch++;
पूर्ण

अटल व्योम r128_cce_dispatch_indices(काष्ठा drm_device *dev,
				      काष्ठा drm_buf *buf,
				      पूर्णांक start, पूर्णांक end, पूर्णांक count)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	पूर्णांक क्रमmat = sarea_priv->vc_क्रमmat;
	पूर्णांक offset = dev->agp_buffer_map->offset - dev_priv->cce_buffers_offset;
	पूर्णांक prim = buf_priv->prim;
	u32 *data;
	पूर्णांक dwords;
	पूर्णांक i = 0;
	RING_LOCALS;
	DRM_DEBUG("indices: s=%d e=%d c=%d\n", start, end, count);

	अगर (0)
		r128_prपूर्णांक_dirty("dispatch_indices", sarea_priv->dirty);

	अगर (start != end) अणु
		buf_priv->dispatched = 1;

		अगर (sarea_priv->dirty & ~R128_UPLOAD_CLIPRECTS)
			r128_emit_state(dev_priv);

		dwords = (end - start + 3) / माप(u32);

		data = (u32 *) ((अक्षर *)dev->agp_buffer_map->handle
				+ buf->offset + start);

		data[0] = cpu_to_le32(CCE_PACKET3(R128_3D_RNDR_GEN_INDX_PRIM,
						  dwords - 2));

		data[1] = cpu_to_le32(offset);
		data[2] = cpu_to_le32(R128_MAX_VB_VERTS);
		data[3] = cpu_to_le32(क्रमmat);
		data[4] = cpu_to_le32((prim | R128_CCE_VC_CNTL_PRIM_WALK_IND |
				       (count << 16)));

		अगर (count & 0x1) अणु
#अगर_घोषित __LITTLE_ENDIAN
			data[dwords - 1] &= 0x0000ffff;
#अन्यथा
			data[dwords - 1] &= 0xffff0000;
#पूर्ण_अगर
		पूर्ण

		करो अणु
			/* Emit the next set of up to three cliprects */
			अगर (i < sarea_priv->nbox) अणु
				r128_emit_clip_rects(dev_priv,
						     &sarea_priv->boxes[i],
						     sarea_priv->nbox - i);
			पूर्ण

			r128_cce_dispatch_indirect(dev, buf, start, end);

			i += 3;
		पूर्ण जबतक (i < sarea_priv->nbox);
	पूर्ण

	अगर (buf_priv->discard) अणु
		buf_priv->age = dev_priv->sarea_priv->last_dispatch;

		/* Emit the vertex buffer age */
		BEGIN_RING(2);

		OUT_RING(CCE_PACKET0(R128_LAST_DISPATCH_REG, 0));
		OUT_RING(buf_priv->age);

		ADVANCE_RING();

		buf->pending = 1;
		/* FIXME: Check dispatched field */
		buf_priv->dispatched = 0;
	पूर्ण

	dev_priv->sarea_priv->last_dispatch++;

	sarea_priv->dirty &= ~R128_UPLOAD_CLIPRECTS;
	sarea_priv->nbox = 0;
पूर्ण

अटल पूर्णांक r128_cce_dispatch_blit(काष्ठा drm_device *dev,
				  काष्ठा drm_file *file_priv,
				  drm_r128_blit_t *blit)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_r128_buf_priv_t *buf_priv;
	u32 *data;
	पूर्णांक dword_shअगरt, dwords;
	RING_LOCALS;
	DRM_DEBUG("\n");

	/* The compiler won't optimize away a भागision by a variable,
	 * even अगर the only legal values are घातers of two.  Thus, we'll
	 * use a shअगरt instead.
	 */
	चयन (blit->क्रमmat) अणु
	हाल R128_DATATYPE_ARGB8888:
		dword_shअगरt = 0;
		अवरोध;
	हाल R128_DATATYPE_ARGB1555:
	हाल R128_DATATYPE_RGB565:
	हाल R128_DATATYPE_ARGB4444:
	हाल R128_DATATYPE_YVYU422:
	हाल R128_DATATYPE_VYUY422:
		dword_shअगरt = 1;
		अवरोध;
	हाल R128_DATATYPE_CI8:
	हाल R128_DATATYPE_RGB8:
		dword_shअगरt = 2;
		अवरोध;
	शेष:
		DRM_ERROR("invalid blit format %d\n", blit->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* Flush the pixel cache, and mark the contents as Read Invalid.
	 * This ensures no pixel data माला_लो mixed up with the texture
	 * data from the host data blit, otherwise part of the texture
	 * image may be corrupted.
	 */
	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_PC_GUI_CTLSTAT, 0));
	OUT_RING(R128_PC_RI_GUI | R128_PC_FLUSH_GUI);

	ADVANCE_RING();

	/* Dispatch the indirect buffer.
	 */
	buf = dma->buflist[blit->idx];
	buf_priv = buf->dev_निजी;

	अगर (buf->file_priv != file_priv) अणु
		DRM_ERROR("process %d using buffer owned by %p\n",
			  task_pid_nr(current), buf->file_priv);
		वापस -EINVAL;
	पूर्ण
	अगर (buf->pending) अणु
		DRM_ERROR("sending pending buffer %d\n", blit->idx);
		वापस -EINVAL;
	पूर्ण

	buf_priv->discard = 1;

	dwords = (blit->width * blit->height) >> dword_shअगरt;

	data = (u32 *) ((अक्षर *)dev->agp_buffer_map->handle + buf->offset);

	data[0] = cpu_to_le32(CCE_PACKET3(R128_CNTL_HOSTDATA_BLT, dwords + 6));
	data[1] = cpu_to_le32((R128_GMC_DST_PITCH_OFFSET_CNTL |
			       R128_GMC_BRUSH_NONE |
			       (blit->क्रमmat << 8) |
			       R128_GMC_SRC_DATATYPE_COLOR |
			       R128_ROP3_S |
			       R128_DP_SRC_SOURCE_HOST_DATA |
			       R128_GMC_CLR_CMP_CNTL_DIS |
			       R128_GMC_AUX_CLIP_DIS | R128_GMC_WR_MSK_DIS));

	data[2] = cpu_to_le32((blit->pitch << 21) | (blit->offset >> 5));
	data[3] = cpu_to_le32(0xffffffff);
	data[4] = cpu_to_le32(0xffffffff);
	data[5] = cpu_to_le32((blit->y << 16) | blit->x);
	data[6] = cpu_to_le32((blit->height << 16) | blit->width);
	data[7] = cpu_to_le32(dwords);

	buf->used = (dwords + 8) * माप(u32);

	r128_cce_dispatch_indirect(dev, buf, 0, buf->used);

	/* Flush the pixel cache after the blit completes.  This ensures
	 * the texture data is written out to memory beक्रमe rendering
	 * जारीs.
	 */
	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_PC_GUI_CTLSTAT, 0));
	OUT_RING(R128_PC_FLUSH_GUI);

	ADVANCE_RING();

	वापस 0;
पूर्ण

/* ================================================================
 * Tiled depth buffer management
 *
 * FIXME: These should all set the destination ग_लिखो mask क्रम when we
 * have hardware stencil support.
 */

अटल पूर्णांक r128_cce_dispatch_ग_लिखो_span(काष्ठा drm_device *dev,
					drm_r128_depth_t *depth)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक count, x, y;
	u32 *buffer;
	u8 *mask;
	पूर्णांक i, buffer_size, mask_size;
	RING_LOCALS;
	DRM_DEBUG("\n");

	count = depth->n;
	अगर (count > 4096 || count <= 0)
		वापस -EMSGSIZE;

	अगर (copy_from_user(&x, depth->x, माप(x)))
		वापस -EFAULT;
	अगर (copy_from_user(&y, depth->y, माप(y)))
		वापस -EFAULT;

	buffer_size = depth->n * माप(u32);
	buffer = memdup_user(depth->buffer, buffer_size);
	अगर (IS_ERR(buffer))
		वापस PTR_ERR(buffer);

	mask_size = depth->n;
	अगर (depth->mask) अणु
		mask = memdup_user(depth->mask, mask_size);
		अगर (IS_ERR(mask)) अणु
			kमुक्त(buffer);
			वापस PTR_ERR(mask);
		पूर्ण

		क्रम (i = 0; i < count; i++, x++) अणु
			अगर (mask[i]) अणु
				BEGIN_RING(6);

				OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
				OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
					 R128_GMC_BRUSH_SOLID_COLOR |
					 (dev_priv->depth_fmt << 8) |
					 R128_GMC_SRC_DATATYPE_COLOR |
					 R128_ROP3_P |
					 R128_GMC_CLR_CMP_CNTL_DIS |
					 R128_GMC_WR_MSK_DIS);

				OUT_RING(dev_priv->depth_pitch_offset_c);
				OUT_RING(buffer[i]);

				OUT_RING((x << 16) | y);
				OUT_RING((1 << 16) | 1);

				ADVANCE_RING();
			पूर्ण
		पूर्ण

		kमुक्त(mask);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < count; i++, x++) अणु
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->depth_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_WR_MSK_DIS);

			OUT_RING(dev_priv->depth_pitch_offset_c);
			OUT_RING(buffer[i]);

			OUT_RING((x << 16) | y);
			OUT_RING((1 << 16) | 1);

			ADVANCE_RING();
		पूर्ण
	पूर्ण

	kमुक्त(buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_dispatch_ग_लिखो_pixels(काष्ठा drm_device *dev,
					  drm_r128_depth_t *depth)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक count, *x, *y;
	u32 *buffer;
	u8 *mask;
	पूर्णांक i, xbuf_size, ybuf_size, buffer_size, mask_size;
	RING_LOCALS;
	DRM_DEBUG("\n");

	count = depth->n;
	अगर (count > 4096 || count <= 0)
		वापस -EMSGSIZE;

	xbuf_size = count * माप(*x);
	ybuf_size = count * माप(*y);
	x = memdup_user(depth->x, xbuf_size);
	अगर (IS_ERR(x))
		वापस PTR_ERR(x);
	y = memdup_user(depth->y, ybuf_size);
	अगर (IS_ERR(y)) अणु
		kमुक्त(x);
		वापस PTR_ERR(y);
	पूर्ण
	buffer_size = depth->n * माप(u32);
	buffer = memdup_user(depth->buffer, buffer_size);
	अगर (IS_ERR(buffer)) अणु
		kमुक्त(x);
		kमुक्त(y);
		वापस PTR_ERR(buffer);
	पूर्ण

	अगर (depth->mask) अणु
		mask_size = depth->n;
		mask = memdup_user(depth->mask, mask_size);
		अगर (IS_ERR(mask)) अणु
			kमुक्त(x);
			kमुक्त(y);
			kमुक्त(buffer);
			वापस PTR_ERR(mask);
		पूर्ण

		क्रम (i = 0; i < count; i++) अणु
			अगर (mask[i]) अणु
				BEGIN_RING(6);

				OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
				OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
					 R128_GMC_BRUSH_SOLID_COLOR |
					 (dev_priv->depth_fmt << 8) |
					 R128_GMC_SRC_DATATYPE_COLOR |
					 R128_ROP3_P |
					 R128_GMC_CLR_CMP_CNTL_DIS |
					 R128_GMC_WR_MSK_DIS);

				OUT_RING(dev_priv->depth_pitch_offset_c);
				OUT_RING(buffer[i]);

				OUT_RING((x[i] << 16) | y[i]);
				OUT_RING((1 << 16) | 1);

				ADVANCE_RING();
			पूर्ण
		पूर्ण

		kमुक्त(mask);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < count; i++) अणु
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->depth_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_WR_MSK_DIS);

			OUT_RING(dev_priv->depth_pitch_offset_c);
			OUT_RING(buffer[i]);

			OUT_RING((x[i] << 16) | y[i]);
			OUT_RING((1 << 16) | 1);

			ADVANCE_RING();
		पूर्ण
	पूर्ण

	kमुक्त(x);
	kमुक्त(y);
	kमुक्त(buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_dispatch_पढ़ो_span(काष्ठा drm_device *dev,
				       drm_r128_depth_t *depth)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक count, x, y;
	RING_LOCALS;
	DRM_DEBUG("\n");

	count = depth->n;
	अगर (count > 4096 || count <= 0)
		वापस -EMSGSIZE;

	अगर (copy_from_user(&x, depth->x, माप(x)))
		वापस -EFAULT;
	अगर (copy_from_user(&y, depth->y, माप(y)))
		वापस -EFAULT;

	BEGIN_RING(7);

	OUT_RING(CCE_PACKET3(R128_CNTL_BITBLT_MULTI, 5));
	OUT_RING(R128_GMC_SRC_PITCH_OFFSET_CNTL |
		 R128_GMC_DST_PITCH_OFFSET_CNTL |
		 R128_GMC_BRUSH_NONE |
		 (dev_priv->depth_fmt << 8) |
		 R128_GMC_SRC_DATATYPE_COLOR |
		 R128_ROP3_S |
		 R128_DP_SRC_SOURCE_MEMORY |
		 R128_GMC_CLR_CMP_CNTL_DIS | R128_GMC_WR_MSK_DIS);

	OUT_RING(dev_priv->depth_pitch_offset_c);
	OUT_RING(dev_priv->span_pitch_offset_c);

	OUT_RING((x << 16) | y);
	OUT_RING((0 << 16) | 0);
	OUT_RING((count << 16) | 1);

	ADVANCE_RING();

	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_dispatch_पढ़ो_pixels(काष्ठा drm_device *dev,
					 drm_r128_depth_t *depth)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक count, *x, *y;
	पूर्णांक i, xbuf_size, ybuf_size;
	RING_LOCALS;
	DRM_DEBUG("\n");

	count = depth->n;
	अगर (count > 4096 || count <= 0)
		वापस -EMSGSIZE;

	अगर (count > dev_priv->depth_pitch)
		count = dev_priv->depth_pitch;

	xbuf_size = count * माप(*x);
	ybuf_size = count * माप(*y);
	x = kदो_स्मृति(xbuf_size, GFP_KERNEL);
	अगर (x == शून्य)
		वापस -ENOMEM;
	y = kदो_स्मृति(ybuf_size, GFP_KERNEL);
	अगर (y == शून्य) अणु
		kमुक्त(x);
		वापस -ENOMEM;
	पूर्ण
	अगर (copy_from_user(x, depth->x, xbuf_size)) अणु
		kमुक्त(x);
		kमुक्त(y);
		वापस -EFAULT;
	पूर्ण
	अगर (copy_from_user(y, depth->y, ybuf_size)) अणु
		kमुक्त(x);
		kमुक्त(y);
		वापस -EFAULT;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		BEGIN_RING(7);

		OUT_RING(CCE_PACKET3(R128_CNTL_BITBLT_MULTI, 5));
		OUT_RING(R128_GMC_SRC_PITCH_OFFSET_CNTL |
			 R128_GMC_DST_PITCH_OFFSET_CNTL |
			 R128_GMC_BRUSH_NONE |
			 (dev_priv->depth_fmt << 8) |
			 R128_GMC_SRC_DATATYPE_COLOR |
			 R128_ROP3_S |
			 R128_DP_SRC_SOURCE_MEMORY |
			 R128_GMC_CLR_CMP_CNTL_DIS | R128_GMC_WR_MSK_DIS);

		OUT_RING(dev_priv->depth_pitch_offset_c);
		OUT_RING(dev_priv->span_pitch_offset_c);

		OUT_RING((x[i] << 16) | y[i]);
		OUT_RING((i << 16) | 0);
		OUT_RING((1 << 16) | 1);

		ADVANCE_RING();
	पूर्ण

	kमुक्त(x);
	kमुक्त(y);

	वापस 0;
पूर्ण

/* ================================================================
 * Polygon stipple
 */

अटल व्योम r128_cce_dispatch_stipple(काष्ठा drm_device *dev, u32 *stipple)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक i;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(33);

	OUT_RING(CCE_PACKET0(R128_BRUSH_DATA0, 31));
	क्रम (i = 0; i < 32; i++)
		OUT_RING(stipple[i]);

	ADVANCE_RING();
पूर्ण

/* ================================================================
 * IOCTL functions
 */

अटल पूर्णांक r128_cce_clear(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_sarea_t *sarea_priv;
	drm_r128_clear_t *clear = data;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	sarea_priv = dev_priv->sarea_priv;

	अगर (sarea_priv->nbox > R128_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = R128_NR_SAREA_CLIPRECTS;

	r128_cce_dispatch_clear(dev, clear);
	COMMIT_RING();

	/* Make sure we restore the 3D state next समय.
	 */
	dev_priv->sarea_priv->dirty |= R128_UPLOAD_CONTEXT | R128_UPLOAD_MASKS;

	वापस 0;
पूर्ण

अटल पूर्णांक r128_करो_init_pageflip(काष्ठा drm_device *dev)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	DRM_DEBUG("\n");

	dev_priv->crtc_offset = R128_READ(R128_CRTC_OFFSET);
	dev_priv->crtc_offset_cntl = R128_READ(R128_CRTC_OFFSET_CNTL);

	R128_WRITE(R128_CRTC_OFFSET, dev_priv->front_offset);
	R128_WRITE(R128_CRTC_OFFSET_CNTL,
		   dev_priv->crtc_offset_cntl | R128_CRTC_OFFSET_FLIP_CNTL);

	dev_priv->page_flipping = 1;
	dev_priv->current_page = 0;
	dev_priv->sarea_priv->pfCurrentPage = dev_priv->current_page;

	वापस 0;
पूर्ण

अटल पूर्णांक r128_करो_cleanup_pageflip(काष्ठा drm_device *dev)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	DRM_DEBUG("\n");

	R128_WRITE(R128_CRTC_OFFSET, dev_priv->crtc_offset);
	R128_WRITE(R128_CRTC_OFFSET_CNTL, dev_priv->crtc_offset_cntl);

	अगर (dev_priv->current_page != 0) अणु
		r128_cce_dispatch_flip(dev);
		COMMIT_RING();
	पूर्ण

	dev_priv->page_flipping = 0;
	वापस 0;
पूर्ण

/* Swapping and flipping are dअगरferent operations, need dअगरferent ioctls.
 * They can & should be पूर्णांकermixed to support multiple 3d winकरोws.
 */

अटल पूर्णांक r128_cce_flip(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	अगर (!dev_priv->page_flipping)
		r128_करो_init_pageflip(dev);

	r128_cce_dispatch_flip(dev);

	COMMIT_RING();
	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_swap(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	अगर (sarea_priv->nbox > R128_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = R128_NR_SAREA_CLIPRECTS;

	r128_cce_dispatch_swap(dev);
	dev_priv->sarea_priv->dirty |= (R128_UPLOAD_CONTEXT |
					R128_UPLOAD_MASKS);

	COMMIT_RING();
	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_vertex(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_r128_buf_priv_t *buf_priv;
	drm_r128_vertex_t *vertex = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	DRM_DEBUG("pid=%d index=%d count=%d discard=%d\n",
		  task_pid_nr(current), vertex->idx, vertex->count, vertex->discard);

	अगर (vertex->idx < 0 || vertex->idx >= dma->buf_count) अणु
		DRM_ERROR("buffer index %d (of %d max)\n",
			  vertex->idx, dma->buf_count - 1);
		वापस -EINVAL;
	पूर्ण
	अगर (vertex->prim < 0 ||
	    vertex->prim > R128_CCE_VC_CNTL_PRIM_TYPE_TRI_TYPE2) अणु
		DRM_ERROR("buffer prim %d\n", vertex->prim);
		वापस -EINVAL;
	पूर्ण

	RING_SPACE_TEST_WITH_RETURN(dev_priv);
	VB_AGE_TEST_WITH_RETURN(dev_priv);

	buf = dma->buflist[vertex->idx];
	buf_priv = buf->dev_निजी;

	अगर (buf->file_priv != file_priv) अणु
		DRM_ERROR("process %d using buffer owned by %p\n",
			  task_pid_nr(current), buf->file_priv);
		वापस -EINVAL;
	पूर्ण
	अगर (buf->pending) अणु
		DRM_ERROR("sending pending buffer %d\n", vertex->idx);
		वापस -EINVAL;
	पूर्ण

	buf->used = vertex->count;
	buf_priv->prim = vertex->prim;
	buf_priv->discard = vertex->discard;

	r128_cce_dispatch_vertex(dev, buf);

	COMMIT_RING();
	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_indices(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_r128_buf_priv_t *buf_priv;
	drm_r128_indices_t *elts = data;
	पूर्णांक count;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	DRM_DEBUG("pid=%d buf=%d s=%d e=%d d=%d\n", task_pid_nr(current),
		  elts->idx, elts->start, elts->end, elts->discard);

	अगर (elts->idx < 0 || elts->idx >= dma->buf_count) अणु
		DRM_ERROR("buffer index %d (of %d max)\n",
			  elts->idx, dma->buf_count - 1);
		वापस -EINVAL;
	पूर्ण
	अगर (elts->prim < 0 ||
	    elts->prim > R128_CCE_VC_CNTL_PRIM_TYPE_TRI_TYPE2) अणु
		DRM_ERROR("buffer prim %d\n", elts->prim);
		वापस -EINVAL;
	पूर्ण

	RING_SPACE_TEST_WITH_RETURN(dev_priv);
	VB_AGE_TEST_WITH_RETURN(dev_priv);

	buf = dma->buflist[elts->idx];
	buf_priv = buf->dev_निजी;

	अगर (buf->file_priv != file_priv) अणु
		DRM_ERROR("process %d using buffer owned by %p\n",
			  task_pid_nr(current), buf->file_priv);
		वापस -EINVAL;
	पूर्ण
	अगर (buf->pending) अणु
		DRM_ERROR("sending pending buffer %d\n", elts->idx);
		वापस -EINVAL;
	पूर्ण

	count = (elts->end - elts->start) / माप(u16);
	elts->start -= R128_INDEX_PRIM_OFFSET;

	अगर (elts->start & 0x7) अणु
		DRM_ERROR("misaligned buffer 0x%x\n", elts->start);
		वापस -EINVAL;
	पूर्ण
	अगर (elts->start < buf->used) अणु
		DRM_ERROR("no header 0x%x - 0x%x\n", elts->start, buf->used);
		वापस -EINVAL;
	पूर्ण

	buf->used = elts->end;
	buf_priv->prim = elts->prim;
	buf_priv->discard = elts->discard;

	r128_cce_dispatch_indices(dev, buf, elts->start, elts->end, count);

	COMMIT_RING();
	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_blit(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_blit_t *blit = data;
	पूर्णांक ret;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	DRM_DEBUG("pid=%d index=%d\n", task_pid_nr(current), blit->idx);

	अगर (blit->idx < 0 || blit->idx >= dma->buf_count) अणु
		DRM_ERROR("buffer index %d (of %d max)\n",
			  blit->idx, dma->buf_count - 1);
		वापस -EINVAL;
	पूर्ण

	RING_SPACE_TEST_WITH_RETURN(dev_priv);
	VB_AGE_TEST_WITH_RETURN(dev_priv);

	ret = r128_cce_dispatch_blit(dev, file_priv, blit);

	COMMIT_RING();
	वापस ret;
पूर्ण

पूर्णांक r128_cce_depth(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_depth_t *depth = data;
	पूर्णांक ret;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	ret = -EINVAL;
	चयन (depth->func) अणु
	हाल R128_WRITE_SPAN:
		ret = r128_cce_dispatch_ग_लिखो_span(dev, depth);
		अवरोध;
	हाल R128_WRITE_PIXELS:
		ret = r128_cce_dispatch_ग_लिखो_pixels(dev, depth);
		अवरोध;
	हाल R128_READ_SPAN:
		ret = r128_cce_dispatch_पढ़ो_span(dev, depth);
		अवरोध;
	हाल R128_READ_PIXELS:
		ret = r128_cce_dispatch_पढ़ो_pixels(dev, depth);
		अवरोध;
	पूर्ण

	COMMIT_RING();
	वापस ret;
पूर्ण

पूर्णांक r128_cce_stipple(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_stipple_t *stipple = data;
	u32 mask[32];

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	अगर (copy_from_user(&mask, stipple->mask, 32 * माप(u32)))
		वापस -EFAULT;

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	r128_cce_dispatch_stipple(dev, mask);

	COMMIT_RING();
	वापस 0;
पूर्ण

अटल पूर्णांक r128_cce_indirect(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_r128_buf_priv_t *buf_priv;
	drm_r128_indirect_t *indirect = data;
#अगर 0
	RING_LOCALS;
#पूर्ण_अगर

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	DRM_DEBUG("idx=%d s=%d e=%d d=%d\n",
		  indirect->idx, indirect->start, indirect->end,
		  indirect->discard);

	अगर (indirect->idx < 0 || indirect->idx >= dma->buf_count) अणु
		DRM_ERROR("buffer index %d (of %d max)\n",
			  indirect->idx, dma->buf_count - 1);
		वापस -EINVAL;
	पूर्ण

	buf = dma->buflist[indirect->idx];
	buf_priv = buf->dev_निजी;

	अगर (buf->file_priv != file_priv) अणु
		DRM_ERROR("process %d using buffer owned by %p\n",
			  task_pid_nr(current), buf->file_priv);
		वापस -EINVAL;
	पूर्ण
	अगर (buf->pending) अणु
		DRM_ERROR("sending pending buffer %d\n", indirect->idx);
		वापस -EINVAL;
	पूर्ण

	अगर (indirect->start < buf->used) अणु
		DRM_ERROR("reusing indirect: start=0x%x actual=0x%x\n",
			  indirect->start, buf->used);
		वापस -EINVAL;
	पूर्ण

	RING_SPACE_TEST_WITH_RETURN(dev_priv);
	VB_AGE_TEST_WITH_RETURN(dev_priv);

	buf->used = indirect->end;
	buf_priv->discard = indirect->discard;

#अगर 0
	/* Wait क्रम the 3D stream to idle beक्रमe the indirect buffer
	 * containing 2D acceleration commands is processed.
	 */
	BEGIN_RING(2);
	RADEON_WAIT_UNTIL_3D_IDLE();
	ADVANCE_RING();
#पूर्ण_अगर

	/* Dispatch the indirect buffer full of commands from the
	 * X server.  This is insecure and is thus only available to
	 * privileged clients.
	 */
	r128_cce_dispatch_indirect(dev, buf, indirect->start, indirect->end);

	COMMIT_RING();
	वापस 0;
पूर्ण

पूर्णांक r128_getparam(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_getparam_t *param = data;
	पूर्णांक value;

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	DRM_DEBUG("pid=%d\n", task_pid_nr(current));

	चयन (param->param) अणु
	हाल R128_PARAM_IRQ_NR:
		value = dev->pdev->irq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (copy_to_user(param->value, &value, माप(पूर्णांक))) अणु
		DRM_ERROR("copy_to_user\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

व्योम r128_driver_preबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	अगर (dev->dev_निजी) अणु
		drm_r128_निजी_t *dev_priv = dev->dev_निजी;
		अगर (dev_priv->page_flipping)
			r128_करो_cleanup_pageflip(dev);
	पूर्ण
पूर्ण
व्योम r128_driver_lastबंद(काष्ठा drm_device *dev)
अणु
	r128_करो_cleanup_cce(dev);
पूर्ण

स्थिर काष्ठा drm_ioctl_desc r128_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(R128_INIT, r128_cce_init, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(R128_CCE_START, r128_cce_start, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(R128_CCE_STOP, r128_cce_stop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(R128_CCE_RESET, r128_cce_reset, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(R128_CCE_IDLE, r128_cce_idle, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_RESET, r128_engine_reset, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_FULLSCREEN, r128_fullscreen, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_SWAP, r128_cce_swap, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_FLIP, r128_cce_flip, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_CLEAR, r128_cce_clear, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_VERTEX, r128_cce_vertex, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_INDICES, r128_cce_indices, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_BLIT, r128_cce_blit, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_DEPTH, r128_cce_depth, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_STIPPLE, r128_cce_stipple, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(R128_INसूचीECT, r128_cce_indirect, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(R128_GETPARAM, r128_getparam, DRM_AUTH),
पूर्ण;

पूर्णांक r128_max_ioctl = ARRAY_SIZE(r128_ioctls);
