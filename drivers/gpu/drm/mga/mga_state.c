<शैली गुरु>
/* mga_state.c -- State support क्रम MGA G200/G400 -*- linux-c -*-
 * Created: Thu Jan 27 02:53:43 2000 by jharपंचांगann@precisioninsight.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Jeff Harपंचांगann <jharपंचांगann@valinux.com>
 *    Keith Whitwell <keith@tungstengraphics.com>
 *
 * Rewritten by:
 *    Gareth Hughes <gareth@valinux.com>
 */

#समावेश "mga_drv.h"

/* ================================================================
 * DMA hardware state programming functions
 */

अटल व्योम mga_emit_clip_rect(drm_mga_निजी_t *dev_priv,
			       काष्ठा drm_clip_rect *box)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	अचिन्हित पूर्णांक pitch = dev_priv->front_pitch;
	DMA_LOCALS;

	BEGIN_DMA(2);

	/* Force reset of DWGCTL on G400 (eliminates clip disable bit).
	 */
	अगर (dev_priv->chipset >= MGA_CARD_TYPE_G400) अणु
		DMA_BLOCK(MGA_DWGCTL, ctx->dwgctl,
			  MGA_LEN + MGA_EXEC, 0x80000000,
			  MGA_DWGCTL, ctx->dwgctl,
			  MGA_LEN + MGA_EXEC, 0x80000000);
	पूर्ण
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_CXBNDRY, ((box->x2 - 1) << 16) | box->x1,
		  MGA_YTOP, box->y1 * pitch, MGA_YBOT, (box->y2 - 1) * pitch);

	ADVANCE_DMA();
पूर्ण

अटल __अंतरभूत__ व्योम mga_g200_emit_context(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	DMA_LOCALS;

	BEGIN_DMA(3);

	DMA_BLOCK(MGA_DSTORG, ctx->dstorg,
		  MGA_MACCESS, ctx->maccess,
		  MGA_PLNWT, ctx->plnwt, MGA_DWGCTL, ctx->dwgctl);

	DMA_BLOCK(MGA_ALPHACTRL, ctx->alphactrl,
		  MGA_FOGCOL, ctx->fogcolor,
		  MGA_WFLAG, ctx->wflag, MGA_ZORG, dev_priv->depth_offset);

	DMA_BLOCK(MGA_FCOL, ctx->fcol,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();
पूर्ण

अटल __अंतरभूत__ व्योम mga_g400_emit_context(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	DMA_LOCALS;

	BEGIN_DMA(4);

	DMA_BLOCK(MGA_DSTORG, ctx->dstorg,
		  MGA_MACCESS, ctx->maccess,
		  MGA_PLNWT, ctx->plnwt, MGA_DWGCTL, ctx->dwgctl);

	DMA_BLOCK(MGA_ALPHACTRL, ctx->alphactrl,
		  MGA_FOGCOL, ctx->fogcolor,
		  MGA_WFLAG, ctx->wflag, MGA_ZORG, dev_priv->depth_offset);

	DMA_BLOCK(MGA_WFLAG1, ctx->wflag,
		  MGA_TDUALSTAGE0, ctx->tdualstage0,
		  MGA_TDUALSTAGE1, ctx->tdualstage1, MGA_FCOL, ctx->fcol);

	DMA_BLOCK(MGA_STENCIL, ctx->stencil,
		  MGA_STENCILCTL, ctx->stencilctl,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();
पूर्ण

अटल __अंतरभूत__ व्योम mga_g200_emit_tex0(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_texture_regs_t *tex = &sarea_priv->tex_state[0];
	DMA_LOCALS;

	BEGIN_DMA(4);

	DMA_BLOCK(MGA_TEXCTL2, tex->texctl2,
		  MGA_TEXCTL, tex->texctl,
		  MGA_TEXFILTER, tex->texfilter,
		  MGA_TEXBORDERCOL, tex->texbordercol);

	DMA_BLOCK(MGA_TEXORG, tex->texorg,
		  MGA_TEXORG1, tex->texorg1,
		  MGA_TEXORG2, tex->texorg2, MGA_TEXORG3, tex->texorg3);

	DMA_BLOCK(MGA_TEXORG4, tex->texorg4,
		  MGA_TEXWIDTH, tex->texwidth,
		  MGA_TEXHEIGHT, tex->texheight, MGA_WR24, tex->texwidth);

	DMA_BLOCK(MGA_WR34, tex->texheight,
		  MGA_TEXTRANS, 0x0000ffff,
		  MGA_TEXTRANSHIGH, 0x0000ffff, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();
पूर्ण

अटल __अंतरभूत__ व्योम mga_g400_emit_tex0(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_texture_regs_t *tex = &sarea_priv->tex_state[0];
	DMA_LOCALS;

/*	prपूर्णांकk("mga_g400_emit_tex0 %x %x %x\n", tex->texorg, */
/*	       tex->texctl, tex->texctl2); */

	BEGIN_DMA(6);

	DMA_BLOCK(MGA_TEXCTL2, tex->texctl2 | MGA_G400_TC2_MAGIC,
		  MGA_TEXCTL, tex->texctl,
		  MGA_TEXFILTER, tex->texfilter,
		  MGA_TEXBORDERCOL, tex->texbordercol);

	DMA_BLOCK(MGA_TEXORG, tex->texorg,
		  MGA_TEXORG1, tex->texorg1,
		  MGA_TEXORG2, tex->texorg2, MGA_TEXORG3, tex->texorg3);

	DMA_BLOCK(MGA_TEXORG4, tex->texorg4,
		  MGA_TEXWIDTH, tex->texwidth,
		  MGA_TEXHEIGHT, tex->texheight, MGA_WR49, 0x00000000);

	DMA_BLOCK(MGA_WR57, 0x00000000,
		  MGA_WR53, 0x00000000,
		  MGA_WR61, 0x00000000, MGA_WR52, MGA_G400_WR_MAGIC);

	DMA_BLOCK(MGA_WR60, MGA_G400_WR_MAGIC,
		  MGA_WR54, tex->texwidth | MGA_G400_WR_MAGIC,
		  MGA_WR62, tex->texheight | MGA_G400_WR_MAGIC,
		  MGA_DMAPAD, 0x00000000);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_TEXTRANS, 0x0000ffff, MGA_TEXTRANSHIGH, 0x0000ffff);

	ADVANCE_DMA();
पूर्ण

अटल __अंतरभूत__ व्योम mga_g400_emit_tex1(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_texture_regs_t *tex = &sarea_priv->tex_state[1];
	DMA_LOCALS;

/*	prपूर्णांकk("mga_g400_emit_tex1 %x %x %x\n", tex->texorg,  */
/*	       tex->texctl, tex->texctl2); */

	BEGIN_DMA(5);

	DMA_BLOCK(MGA_TEXCTL2, (tex->texctl2 |
				MGA_MAP1_ENABLE |
				MGA_G400_TC2_MAGIC),
		  MGA_TEXCTL, tex->texctl,
		  MGA_TEXFILTER, tex->texfilter,
		  MGA_TEXBORDERCOL, tex->texbordercol);

	DMA_BLOCK(MGA_TEXORG, tex->texorg,
		  MGA_TEXORG1, tex->texorg1,
		  MGA_TEXORG2, tex->texorg2, MGA_TEXORG3, tex->texorg3);

	DMA_BLOCK(MGA_TEXORG4, tex->texorg4,
		  MGA_TEXWIDTH, tex->texwidth,
		  MGA_TEXHEIGHT, tex->texheight, MGA_WR49, 0x00000000);

	DMA_BLOCK(MGA_WR57, 0x00000000,
		  MGA_WR53, 0x00000000,
		  MGA_WR61, 0x00000000,
		  MGA_WR52, tex->texwidth | MGA_G400_WR_MAGIC);

	DMA_BLOCK(MGA_WR60, tex->texheight | MGA_G400_WR_MAGIC,
		  MGA_TEXTRANS, 0x0000ffff,
		  MGA_TEXTRANSHIGH, 0x0000ffff,
		  MGA_TEXCTL2, tex->texctl2 | MGA_G400_TC2_MAGIC);

	ADVANCE_DMA();
पूर्ण

अटल __अंतरभूत__ व्योम mga_g200_emit_pipe(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित पूर्णांक pipe = sarea_priv->warp_pipe;
	DMA_LOCALS;

	BEGIN_DMA(3);

	DMA_BLOCK(MGA_WIADDR, MGA_WMODE_SUSPEND,
		  MGA_WVRTXSZ, 0x00000007,
		  MGA_WFLAG, 0x00000000, MGA_WR24, 0x00000000);

	DMA_BLOCK(MGA_WR25, 0x00000100,
		  MGA_WR34, 0x00000000,
		  MGA_WR42, 0x0000ffff, MGA_WR60, 0x0000ffff);

	/* Padding required due to hardware bug.
	 */
	DMA_BLOCK(MGA_DMAPAD, 0xffffffff,
		  MGA_DMAPAD, 0xffffffff,
		  MGA_DMAPAD, 0xffffffff,
		  MGA_WIADDR, (dev_priv->warp_pipe_phys[pipe] |
			       MGA_WMODE_START | dev_priv->wagp_enable));

	ADVANCE_DMA();
पूर्ण

अटल __अंतरभूत__ व्योम mga_g400_emit_pipe(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित पूर्णांक pipe = sarea_priv->warp_pipe;
	DMA_LOCALS;

/*	prपूर्णांकk("mga_g400_emit_pipe %x\n", pipe); */

	BEGIN_DMA(10);

	DMA_BLOCK(MGA_WIADDR2, MGA_WMODE_SUSPEND,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	अगर (pipe & MGA_T2) अणु
		DMA_BLOCK(MGA_WVRTXSZ, 0x00001e09,
			  MGA_DMAPAD, 0x00000000,
			  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

		DMA_BLOCK(MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x1e000000);
	पूर्ण अन्यथा अणु
		अगर (dev_priv->warp_pipe & MGA_T2) अणु
			/* Flush the WARP pipe */
			DMA_BLOCK(MGA_YDST, 0x00000000,
				  MGA_FXLEFT, 0x00000000,
				  MGA_FXRIGHT, 0x00000001,
				  MGA_DWGCTL, MGA_DWGCTL_FLUSH);

			DMA_BLOCK(MGA_LEN + MGA_EXEC, 0x00000001,
				  MGA_DWGSYNC, 0x00007000,
				  MGA_TEXCTL2, MGA_G400_TC2_MAGIC,
				  MGA_LEN + MGA_EXEC, 0x00000000);

			DMA_BLOCK(MGA_TEXCTL2, (MGA_DUALTEX |
						MGA_G400_TC2_MAGIC),
				  MGA_LEN + MGA_EXEC, 0x00000000,
				  MGA_TEXCTL2, MGA_G400_TC2_MAGIC,
				  MGA_DMAPAD, 0x00000000);
		पूर्ण

		DMA_BLOCK(MGA_WVRTXSZ, 0x00001807,
			  MGA_DMAPAD, 0x00000000,
			  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

		DMA_BLOCK(MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x18000000);
	पूर्ण

	DMA_BLOCK(MGA_WFLAG, 0x00000000,
		  MGA_WFLAG1, 0x00000000,
		  MGA_WR56, MGA_G400_WR56_MAGIC, MGA_DMAPAD, 0x00000000);

	DMA_BLOCK(MGA_WR49, 0x00000000,	/* tex0              */
		  MGA_WR57, 0x00000000,	/* tex0              */
		  MGA_WR53, 0x00000000,	/* tex1              */
		  MGA_WR61, 0x00000000);	/* tex1              */

	DMA_BLOCK(MGA_WR54, MGA_G400_WR_MAGIC,	/* tex0 width        */
		  MGA_WR62, MGA_G400_WR_MAGIC,	/* tex0 height       */
		  MGA_WR52, MGA_G400_WR_MAGIC,	/* tex1 width        */
		  MGA_WR60, MGA_G400_WR_MAGIC);	/* tex1 height       */

	/* Padding required due to hardware bug */
	DMA_BLOCK(MGA_DMAPAD, 0xffffffff,
		  MGA_DMAPAD, 0xffffffff,
		  MGA_DMAPAD, 0xffffffff,
		  MGA_WIADDR2, (dev_priv->warp_pipe_phys[pipe] |
				MGA_WMODE_START | dev_priv->wagp_enable));

	ADVANCE_DMA();
पूर्ण

अटल व्योम mga_g200_emit_state(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित पूर्णांक dirty = sarea_priv->dirty;

	अगर (sarea_priv->warp_pipe != dev_priv->warp_pipe) अणु
		mga_g200_emit_pipe(dev_priv);
		dev_priv->warp_pipe = sarea_priv->warp_pipe;
	पूर्ण

	अगर (dirty & MGA_UPLOAD_CONTEXT) अणु
		mga_g200_emit_context(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_CONTEXT;
	पूर्ण

	अगर (dirty & MGA_UPLOAD_TEX0) अणु
		mga_g200_emit_tex0(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_TEX0;
	पूर्ण
पूर्ण

अटल व्योम mga_g400_emit_state(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित पूर्णांक dirty = sarea_priv->dirty;
	पूर्णांक multitex = sarea_priv->warp_pipe & MGA_T2;

	अगर (sarea_priv->warp_pipe != dev_priv->warp_pipe) अणु
		mga_g400_emit_pipe(dev_priv);
		dev_priv->warp_pipe = sarea_priv->warp_pipe;
	पूर्ण

	अगर (dirty & MGA_UPLOAD_CONTEXT) अणु
		mga_g400_emit_context(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_CONTEXT;
	पूर्ण

	अगर (dirty & MGA_UPLOAD_TEX0) अणु
		mga_g400_emit_tex0(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_TEX0;
	पूर्ण

	अगर ((dirty & MGA_UPLOAD_TEX1) && multitex) अणु
		mga_g400_emit_tex1(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_TEX1;
	पूर्ण
पूर्ण

/* ================================================================
 * SAREA state verअगरication
 */

/* Disallow all ग_लिखो destinations except the front and backbuffer.
 */
अटल पूर्णांक mga_verअगरy_context(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;

	अगर (ctx->dstorg != dev_priv->front_offset &&
	    ctx->dstorg != dev_priv->back_offset) अणु
		DRM_ERROR("*** bad DSTORG: %x (front %x, back %x)\n\n",
			  ctx->dstorg, dev_priv->front_offset,
			  dev_priv->back_offset);
		ctx->dstorg = 0;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Disallow texture पढ़ोs from PCI space.
 */
अटल पूर्णांक mga_verअगरy_tex(drm_mga_निजी_t *dev_priv, पूर्णांक unit)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_texture_regs_t *tex = &sarea_priv->tex_state[unit];
	अचिन्हित पूर्णांक org;

	org = tex->texorg & (MGA_TEXORGMAP_MASK | MGA_TEXORGACC_MASK);

	अगर (org == (MGA_TEXORGMAP_SYSMEM | MGA_TEXORGACC_PCI)) अणु
		DRM_ERROR("*** bad TEXORG: 0x%x, unit %d\n", tex->texorg, unit);
		tex->texorg = 0;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mga_verअगरy_state(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित पूर्णांक dirty = sarea_priv->dirty;
	पूर्णांक ret = 0;

	अगर (sarea_priv->nbox > MGA_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = MGA_NR_SAREA_CLIPRECTS;

	अगर (dirty & MGA_UPLOAD_CONTEXT)
		ret |= mga_verअगरy_context(dev_priv);

	अगर (dirty & MGA_UPLOAD_TEX0)
		ret |= mga_verअगरy_tex(dev_priv, 0);

	अगर (dev_priv->chipset >= MGA_CARD_TYPE_G400) अणु
		अगर (dirty & MGA_UPLOAD_TEX1)
			ret |= mga_verअगरy_tex(dev_priv, 1);

		अगर (dirty & MGA_UPLOAD_PIPE)
			ret |= (sarea_priv->warp_pipe > MGA_MAX_G400_PIPES);
	पूर्ण अन्यथा अणु
		अगर (dirty & MGA_UPLOAD_PIPE)
			ret |= (sarea_priv->warp_pipe > MGA_MAX_G200_PIPES);
	पूर्ण

	वापस (ret == 0);
पूर्ण

अटल पूर्णांक mga_verअगरy_iload(drm_mga_निजी_t *dev_priv,
			    अचिन्हित पूर्णांक dstorg, अचिन्हित पूर्णांक length)
अणु
	अगर (dstorg < dev_priv->texture_offset ||
	    dstorg + length > (dev_priv->texture_offset +
			       dev_priv->texture_size)) अणु
		DRM_ERROR("*** bad iload DSTORG: 0x%x\n", dstorg);
		वापस -EINVAL;
	पूर्ण

	अगर (length & MGA_ILOAD_MASK) अणु
		DRM_ERROR("*** bad iload length: 0x%x\n",
			  length & MGA_ILOAD_MASK);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mga_verअगरy_blit(drm_mga_निजी_t *dev_priv,
			   अचिन्हित पूर्णांक srcorg, अचिन्हित पूर्णांक dstorg)
अणु
	अगर ((srcorg & 0x3) == (MGA_SRCACC_PCI | MGA_SRCMAP_SYSMEM) ||
	    (dstorg & 0x3) == (MGA_SRCACC_PCI | MGA_SRCMAP_SYSMEM)) अणु
		DRM_ERROR("*** bad blit: src=0x%x dst=0x%x\n", srcorg, dstorg);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ================================================================
 *
 */

अटल व्योम mga_dma_dispatch_clear(काष्ठा drm_device *dev, drm_mga_clear_t *clear)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	काष्ठा drm_clip_rect *pbox = sarea_priv->boxes;
	पूर्णांक nbox = sarea_priv->nbox;
	पूर्णांक i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_DMA(1);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	ADVANCE_DMA();

	क्रम (i = 0; i < nbox; i++) अणु
		काष्ठा drm_clip_rect *box = &pbox[i];
		u32 height = box->y2 - box->y1;

		DRM_DEBUG("   from=%d,%d to=%d,%d\n",
			  box->x1, box->y1, box->x2, box->y2);

		अगर (clear->flags & MGA_FRONT) अणु
			BEGIN_DMA(2);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_PLNWT, clear->color_mask,
				  MGA_YDSTLEN, (box->y1 << 16) | height,
				  MGA_FXBNDRY, (box->x2 << 16) | box->x1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_FCOL, clear->clear_color,
				  MGA_DSTORG, dev_priv->front_offset,
				  MGA_DWGCTL + MGA_EXEC, dev_priv->clear_cmd);

			ADVANCE_DMA();
		पूर्ण

		अगर (clear->flags & MGA_BACK) अणु
			BEGIN_DMA(2);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_PLNWT, clear->color_mask,
				  MGA_YDSTLEN, (box->y1 << 16) | height,
				  MGA_FXBNDRY, (box->x2 << 16) | box->x1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_FCOL, clear->clear_color,
				  MGA_DSTORG, dev_priv->back_offset,
				  MGA_DWGCTL + MGA_EXEC, dev_priv->clear_cmd);

			ADVANCE_DMA();
		पूर्ण

		अगर (clear->flags & MGA_DEPTH) अणु
			BEGIN_DMA(2);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_PLNWT, clear->depth_mask,
				  MGA_YDSTLEN, (box->y1 << 16) | height,
				  MGA_FXBNDRY, (box->x2 << 16) | box->x1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_FCOL, clear->clear_depth,
				  MGA_DSTORG, dev_priv->depth_offset,
				  MGA_DWGCTL + MGA_EXEC, dev_priv->clear_cmd);

			ADVANCE_DMA();
		पूर्ण

	पूर्ण

	BEGIN_DMA(1);

	/* Force reset of DWGCTL */
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, ctx->plnwt, MGA_DWGCTL, ctx->dwgctl);

	ADVANCE_DMA();

	FLUSH_DMA();
पूर्ण

अटल व्योम mga_dma_dispatch_swap(काष्ठा drm_device *dev)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	काष्ठा drm_clip_rect *pbox = sarea_priv->boxes;
	पूर्णांक nbox = sarea_priv->nbox;
	पूर्णांक i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	sarea_priv->last_frame.head = dev_priv->prim.tail;
	sarea_priv->last_frame.wrap = dev_priv->prim.last_wrap;

	BEGIN_DMA(4 + nbox);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	DMA_BLOCK(MGA_DSTORG, dev_priv->front_offset,
		  MGA_MACCESS, dev_priv->maccess,
		  MGA_SRCORG, dev_priv->back_offset,
		  MGA_AR5, dev_priv->front_pitch);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, 0xffffffff, MGA_DWGCTL, MGA_DWGCTL_COPY);

	क्रम (i = 0; i < nbox; i++) अणु
		काष्ठा drm_clip_rect *box = &pbox[i];
		u32 height = box->y2 - box->y1;
		u32 start = box->y1 * dev_priv->front_pitch;

		DRM_DEBUG("   from=%d,%d to=%d,%d\n",
			  box->x1, box->y1, box->x2, box->y2);

		DMA_BLOCK(MGA_AR0, start + box->x2 - 1,
			  MGA_AR3, start + box->x1,
			  MGA_FXBNDRY, ((box->x2 - 1) << 16) | box->x1,
			  MGA_YDSTLEN + MGA_EXEC, (box->y1 << 16) | height);
	पूर्ण

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, ctx->plnwt,
		  MGA_SRCORG, dev_priv->front_offset, MGA_DWGCTL, ctx->dwgctl);

	ADVANCE_DMA();

	FLUSH_DMA();

	DRM_DEBUG("... done.\n");
पूर्ण

अटल व्योम mga_dma_dispatch_vertex(काष्ठा drm_device *dev, काष्ठा drm_buf *buf)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	u32 address = (u32) buf->bus_address;
	u32 length = (u32) buf->used;
	पूर्णांक i = 0;
	DMA_LOCALS;
	DRM_DEBUG("buf=%d used=%d\n", buf->idx, buf->used);

	अगर (buf->used) अणु
		buf_priv->dispatched = 1;

		MGA_EMIT_STATE(dev_priv, sarea_priv->dirty);

		करो अणु
			अगर (i < sarea_priv->nbox) अणु
				mga_emit_clip_rect(dev_priv,
						   &sarea_priv->boxes[i]);
			पूर्ण

			BEGIN_DMA(1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_DMAPAD, 0x00000000,
				  MGA_SECADDRESS, (address |
						   MGA_DMA_VERTEX),
				  MGA_SECEND, ((address + length) |
					       dev_priv->dma_access));

			ADVANCE_DMA();
		पूर्ण जबतक (++i < sarea_priv->nbox);
	पूर्ण

	अगर (buf_priv->discard) अणु
		AGE_BUFFER(buf_priv);
		buf->pending = 0;
		buf->used = 0;
		buf_priv->dispatched = 0;

		mga_मुक्तlist_put(dev, buf);
	पूर्ण

	FLUSH_DMA();
पूर्ण

अटल व्योम mga_dma_dispatch_indices(काष्ठा drm_device *dev, काष्ठा drm_buf *buf,
				     अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	u32 address = (u32) buf->bus_address;
	पूर्णांक i = 0;
	DMA_LOCALS;
	DRM_DEBUG("buf=%d start=%d end=%d\n", buf->idx, start, end);

	अगर (start != end) अणु
		buf_priv->dispatched = 1;

		MGA_EMIT_STATE(dev_priv, sarea_priv->dirty);

		करो अणु
			अगर (i < sarea_priv->nbox) अणु
				mga_emit_clip_rect(dev_priv,
						   &sarea_priv->boxes[i]);
			पूर्ण

			BEGIN_DMA(1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_DMAPAD, 0x00000000,
				  MGA_SETUPADDRESS, address + start,
				  MGA_SETUPEND, ((address + end) |
						 dev_priv->dma_access));

			ADVANCE_DMA();
		पूर्ण जबतक (++i < sarea_priv->nbox);
	पूर्ण

	अगर (buf_priv->discard) अणु
		AGE_BUFFER(buf_priv);
		buf->pending = 0;
		buf->used = 0;
		buf_priv->dispatched = 0;

		mga_मुक्तlist_put(dev, buf);
	पूर्ण

	FLUSH_DMA();
पूर्ण

/* This copies a 64 byte aligned agp region to the frambuffer with a
 * standard blit, the ioctl needs to करो checking.
 */
अटल व्योम mga_dma_dispatch_iload(काष्ठा drm_device *dev, काष्ठा drm_buf *buf,
				   अचिन्हित पूर्णांक dstorg, अचिन्हित पूर्णांक length)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_mga_context_regs_t *ctx = &dev_priv->sarea_priv->context_state;
	u32 srcorg =
	    buf->bus_address | dev_priv->dma_access | MGA_SRCMAP_SYSMEM;
	u32 y2;
	DMA_LOCALS;
	DRM_DEBUG("buf=%d used=%d\n", buf->idx, buf->used);

	y2 = length / 64;

	BEGIN_DMA(5);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	DMA_BLOCK(MGA_DSTORG, dstorg,
		  MGA_MACCESS, 0x00000000, MGA_SRCORG, srcorg, MGA_AR5, 64);

	DMA_BLOCK(MGA_PITCH, 64,
		  MGA_PLNWT, 0xffffffff,
		  MGA_DMAPAD, 0x00000000, MGA_DWGCTL, MGA_DWGCTL_COPY);

	DMA_BLOCK(MGA_AR0, 63,
		  MGA_AR3, 0,
		  MGA_FXBNDRY, (63 << 16) | 0, MGA_YDSTLEN + MGA_EXEC, y2);

	DMA_BLOCK(MGA_PLNWT, ctx->plnwt,
		  MGA_SRCORG, dev_priv->front_offset,
		  MGA_PITCH, dev_priv->front_pitch, MGA_DWGSYNC, 0x00007000);

	ADVANCE_DMA();

	AGE_BUFFER(buf_priv);

	buf->pending = 0;
	buf->used = 0;
	buf_priv->dispatched = 0;

	mga_मुक्तlist_put(dev, buf);

	FLUSH_DMA();
पूर्ण

अटल व्योम mga_dma_dispatch_blit(काष्ठा drm_device *dev, drm_mga_blit_t *blit)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	काष्ठा drm_clip_rect *pbox = sarea_priv->boxes;
	पूर्णांक nbox = sarea_priv->nbox;
	u32 scandir = 0, i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_DMA(4 + nbox);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	DMA_BLOCK(MGA_DWGCTL, MGA_DWGCTL_COPY,
		  MGA_PLNWT, blit->planemask,
		  MGA_SRCORG, blit->srcorg, MGA_DSTORG, blit->dstorg);

	DMA_BLOCK(MGA_SGN, scandir,
		  MGA_MACCESS, dev_priv->maccess,
		  MGA_AR5, blit->ydir * blit->src_pitch,
		  MGA_PITCH, blit->dst_pitch);

	क्रम (i = 0; i < nbox; i++) अणु
		पूर्णांक srcx = pbox[i].x1 + blit->delta_sx;
		पूर्णांक srcy = pbox[i].y1 + blit->delta_sy;
		पूर्णांक dstx = pbox[i].x1 + blit->delta_dx;
		पूर्णांक dsty = pbox[i].y1 + blit->delta_dy;
		पूर्णांक h = pbox[i].y2 - pbox[i].y1;
		पूर्णांक w = pbox[i].x2 - pbox[i].x1 - 1;
		पूर्णांक start;

		अगर (blit->ydir == -1)
			srcy = blit->height - srcy - 1;

		start = srcy * blit->src_pitch + srcx;

		DMA_BLOCK(MGA_AR0, start + w,
			  MGA_AR3, start,
			  MGA_FXBNDRY, ((dstx + w) << 16) | (dstx & 0xffff),
			  MGA_YDSTLEN + MGA_EXEC, (dsty << 16) | h);
	पूर्ण

	/* Do something to flush AGP?
	 */

	/* Force reset of DWGCTL */
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, ctx->plnwt,
		  MGA_PITCH, dev_priv->front_pitch, MGA_DWGCTL, ctx->dwgctl);

	ADVANCE_DMA();
पूर्ण

/* ================================================================
 *
 */

अटल पूर्णांक mga_dma_clear(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_clear_t *clear = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (sarea_priv->nbox > MGA_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = MGA_NR_SAREA_CLIPRECTS;

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_clear(dev, clear);

	/* Make sure we restore the 3D state next समय.
	 */
	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	वापस 0;
पूर्ण

अटल पूर्णांक mga_dma_swap(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (sarea_priv->nbox > MGA_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = MGA_NR_SAREA_CLIPRECTS;

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_swap(dev);

	/* Make sure we restore the 3D state next समय.
	 */
	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	वापस 0;
पूर्ण

अटल पूर्णांक mga_dma_vertex(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_mga_buf_priv_t *buf_priv;
	drm_mga_vertex_t *vertex = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (vertex->idx < 0 || vertex->idx > dma->buf_count)
		वापस -EINVAL;
	buf = dma->buflist[vertex->idx];
	buf_priv = buf->dev_निजी;

	buf->used = vertex->used;
	buf_priv->discard = vertex->discard;

	अगर (!mga_verअगरy_state(dev_priv)) अणु
		अगर (vertex->discard) अणु
			अगर (buf_priv->dispatched == 1)
				AGE_BUFFER(buf_priv);
			buf_priv->dispatched = 0;
			mga_मुक्तlist_put(dev, buf);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_vertex(dev, buf);

	वापस 0;
पूर्ण

अटल पूर्णांक mga_dma_indices(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_mga_buf_priv_t *buf_priv;
	drm_mga_indices_t *indices = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (indices->idx < 0 || indices->idx > dma->buf_count)
		वापस -EINVAL;

	buf = dma->buflist[indices->idx];
	buf_priv = buf->dev_निजी;

	buf_priv->discard = indices->discard;

	अगर (!mga_verअगरy_state(dev_priv)) अणु
		अगर (indices->discard) अणु
			अगर (buf_priv->dispatched == 1)
				AGE_BUFFER(buf_priv);
			buf_priv->dispatched = 0;
			mga_मुक्तlist_put(dev, buf);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_indices(dev, buf, indices->start, indices->end);

	वापस 0;
पूर्ण

अटल पूर्णांक mga_dma_iload(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_buf *buf;
	drm_mga_iload_t *iload = data;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

#अगर 0
	अगर (mga_करो_रुको_क्रम_idle(dev_priv) < 0) अणु
		अगर (MGA_DMA_DEBUG)
			DRM_INFO("-EBUSY\n");
		वापस -EBUSY;
	पूर्ण
#पूर्ण_अगर
	अगर (iload->idx < 0 || iload->idx > dma->buf_count)
		वापस -EINVAL;

	buf = dma->buflist[iload->idx];

	अगर (mga_verअगरy_iload(dev_priv, iload->dstorg, iload->length)) अणु
		mga_मुक्तlist_put(dev, buf);
		वापस -EINVAL;
	पूर्ण

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_iload(dev, buf, iload->dstorg, iload->length);

	/* Make sure we restore the 3D state next समय.
	 */
	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	वापस 0;
पूर्ण

अटल पूर्णांक mga_dma_blit(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_blit_t *blit = data;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (sarea_priv->nbox > MGA_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = MGA_NR_SAREA_CLIPRECTS;

	अगर (mga_verअगरy_blit(dev_priv, blit->srcorg, blit->dstorg))
		वापस -EINVAL;

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_blit(dev, blit);

	/* Make sure we restore the 3D state next समय.
	 */
	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	वापस 0;
पूर्ण

पूर्णांक mga_getparam(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_getparam_t *param = data;
	पूर्णांक value;

	अगर (!dev_priv) अणु
		DRM_ERROR("called with no initialization\n");
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG("pid=%d\n", task_pid_nr(current));

	चयन (param->param) अणु
	हाल MGA_PARAM_IRQ_NR:
		value = dev->pdev->irq;
		अवरोध;
	हाल MGA_PARAM_CARD_TYPE:
		value = dev_priv->chipset;
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

अटल पूर्णांक mga_set_fence(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	u32 *fence = data;
	DMA_LOCALS;

	अगर (!dev_priv) अणु
		DRM_ERROR("called with no initialization\n");
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG("pid=%d\n", task_pid_nr(current));

	/* I would normal करो this assignment in the declaration of fence,
	 * but dev_priv may be शून्य.
	 */

	*fence = dev_priv->next_fence_to_post;
	dev_priv->next_fence_to_post++;

	BEGIN_DMA(1);
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_SOFTRAP, 0x00000000);
	ADVANCE_DMA();

	वापस 0;
पूर्ण

अटल पूर्णांक mga_रुको_fence(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *
file_priv)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	u32 *fence = data;

	अगर (!dev_priv) अणु
		DRM_ERROR("called with no initialization\n");
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG("pid=%d\n", task_pid_nr(current));

	mga_driver_fence_रुको(dev, fence);
	वापस 0;
पूर्ण

स्थिर काष्ठा drm_ioctl_desc mga_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(MGA_INIT, mga_dma_init, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(MGA_FLUSH, mga_dma_flush, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_RESET, mga_dma_reset, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_SWAP, mga_dma_swap, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_CLEAR, mga_dma_clear, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_VERTEX, mga_dma_vertex, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_INDICES, mga_dma_indices, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_ILOAD, mga_dma_iload, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_BLIT, mga_dma_blit, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_GETPARAM, mga_getparam, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_SET_FENCE, mga_set_fence, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_WAIT_FENCE, mga_रुको_fence, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(MGA_DMA_BOOTSTRAP, mga_dma_bootstrap, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
पूर्ण;

पूर्णांक mga_max_ioctl = ARRAY_SIZE(mga_ioctls);
