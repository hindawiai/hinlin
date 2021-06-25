<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 *         Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "vdec_drv_if.h"
#समावेश "mtk_vcodec_dec.h"
#समावेश "vdec_drv_base.h"
#समावेश "mtk_vcodec_dec_pm.h"

पूर्णांक vdec_अगर_init(काष्ठा mtk_vcodec_ctx *ctx, अचिन्हित पूर्णांक fourcc)
अणु
	पूर्णांक ret = 0;

	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_H264:
		ctx->dec_अगर = &vdec_h264_अगर;
		अवरोध;
	हाल V4L2_PIX_FMT_VP8:
		ctx->dec_अगर = &vdec_vp8_अगर;
		अवरोध;
	हाल V4L2_PIX_FMT_VP9:
		ctx->dec_अगर = &vdec_vp9_अगर;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mtk_vdec_lock(ctx);
	mtk_vcodec_dec_घड़ी_on(&ctx->dev->pm);
	ret = ctx->dec_अगर->init(ctx);
	mtk_vcodec_dec_घड़ी_off(&ctx->dev->pm);
	mtk_vdec_unlock(ctx);

	वापस ret;
पूर्ण

पूर्णांक vdec_अगर_decode(काष्ठा mtk_vcodec_ctx *ctx, काष्ठा mtk_vcodec_mem *bs,
		   काष्ठा vdec_fb *fb, bool *res_chg)
अणु
	पूर्णांक ret = 0;

	अगर (bs) अणु
		अगर ((bs->dma_addr & 63) != 0) अणु
			mtk_v4l2_err("bs dma_addr should 64 byte align");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (fb) अणु
		अगर (((fb->base_y.dma_addr & 511) != 0) ||
		    ((fb->base_c.dma_addr & 511) != 0)) अणु
			mtk_v4l2_err("frame buffer dma_addr should 512 byte align");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!ctx->drv_handle)
		वापस -EIO;

	mtk_vdec_lock(ctx);

	mtk_vcodec_set_curr_ctx(ctx->dev, ctx);
	mtk_vcodec_dec_घड़ी_on(&ctx->dev->pm);
	enable_irq(ctx->dev->dec_irq);
	ret = ctx->dec_अगर->decode(ctx->drv_handle, bs, fb, res_chg);
	disable_irq(ctx->dev->dec_irq);
	mtk_vcodec_dec_घड़ी_off(&ctx->dev->pm);
	mtk_vcodec_set_curr_ctx(ctx->dev, शून्य);

	mtk_vdec_unlock(ctx);

	वापस ret;
पूर्ण

पूर्णांक vdec_अगर_get_param(काष्ठा mtk_vcodec_ctx *ctx, क्रमागत vdec_get_param_type type,
		      व्योम *out)
अणु
	पूर्णांक ret = 0;

	अगर (!ctx->drv_handle)
		वापस -EIO;

	mtk_vdec_lock(ctx);
	ret = ctx->dec_अगर->get_param(ctx->drv_handle, type, out);
	mtk_vdec_unlock(ctx);

	वापस ret;
पूर्ण

व्योम vdec_अगर_deinit(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	अगर (!ctx->drv_handle)
		वापस;

	mtk_vdec_lock(ctx);
	mtk_vcodec_dec_घड़ी_on(&ctx->dev->pm);
	ctx->dec_अगर->deinit(ctx->drv_handle);
	mtk_vcodec_dec_घड़ी_off(&ctx->dev->pm);
	mtk_vdec_unlock(ctx);

	ctx->drv_handle = शून्य;
पूर्ण
