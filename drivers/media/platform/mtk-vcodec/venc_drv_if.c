<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Daniel Hsiao <daniel.hsiao@mediatek.com>
 *	Jungchang Tsao <jungchang.tsao@mediatek.com>
 *	Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "venc_drv_base.h"
#समावेश "venc_drv_if.h"

#समावेश "mtk_vcodec_enc.h"
#समावेश "mtk_vcodec_enc_pm.h"

पूर्णांक venc_अगर_init(काष्ठा mtk_vcodec_ctx *ctx, अचिन्हित पूर्णांक fourcc)
अणु
	पूर्णांक ret = 0;

	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_VP8:
		ctx->enc_अगर = &venc_vp8_अगर;
		अवरोध;
	हाल V4L2_PIX_FMT_H264:
		ctx->enc_अगर = &venc_h264_अगर;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mtk_venc_lock(ctx);
	mtk_vcodec_enc_घड़ी_on(&ctx->dev->pm);
	ret = ctx->enc_अगर->init(ctx);
	mtk_vcodec_enc_घड़ी_off(&ctx->dev->pm);
	mtk_venc_unlock(ctx);

	वापस ret;
पूर्ण

पूर्णांक venc_अगर_set_param(काष्ठा mtk_vcodec_ctx *ctx,
		क्रमागत venc_set_param_type type, काष्ठा venc_enc_param *in)
अणु
	पूर्णांक ret = 0;

	mtk_venc_lock(ctx);
	mtk_vcodec_enc_घड़ी_on(&ctx->dev->pm);
	ret = ctx->enc_अगर->set_param(ctx->drv_handle, type, in);
	mtk_vcodec_enc_घड़ी_off(&ctx->dev->pm);
	mtk_venc_unlock(ctx);

	वापस ret;
पूर्ण

पूर्णांक venc_अगर_encode(काष्ठा mtk_vcodec_ctx *ctx,
		   क्रमागत venc_start_opt opt, काष्ठा venc_frm_buf *frm_buf,
		   काष्ठा mtk_vcodec_mem *bs_buf,
		   काष्ठा venc_करोne_result *result)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	mtk_venc_lock(ctx);

	spin_lock_irqsave(&ctx->dev->irqlock, flags);
	ctx->dev->curr_ctx = ctx;
	spin_unlock_irqrestore(&ctx->dev->irqlock, flags);

	mtk_vcodec_enc_घड़ी_on(&ctx->dev->pm);
	ret = ctx->enc_अगर->encode(ctx->drv_handle, opt, frm_buf,
				  bs_buf, result);
	mtk_vcodec_enc_घड़ी_off(&ctx->dev->pm);

	spin_lock_irqsave(&ctx->dev->irqlock, flags);
	ctx->dev->curr_ctx = शून्य;
	spin_unlock_irqrestore(&ctx->dev->irqlock, flags);

	mtk_venc_unlock(ctx);
	वापस ret;
पूर्ण

पूर्णांक venc_अगर_deinit(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	पूर्णांक ret = 0;

	अगर (!ctx->drv_handle)
		वापस 0;

	mtk_venc_lock(ctx);
	mtk_vcodec_enc_घड़ी_on(&ctx->dev->pm);
	ret = ctx->enc_अगर->deinit(ctx->drv_handle);
	mtk_vcodec_enc_घड़ी_off(&ctx->dev->pm);
	mtk_venc_unlock(ctx);

	ctx->drv_handle = शून्य;

	वापस ret;
पूर्ण
