<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: PC Chen <pc.chen@mediatek.com>
*	Tअगरfany Lin <tअगरfany.lin@mediatek.com>
*/

#समावेश <linux/module.h>

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_util.h"

/* For encoder, this will enable logs in venc/*/
bool mtk_vcodec_dbg;
EXPORT_SYMBOL(mtk_vcodec_dbg);

/* The log level of v4l2 encoder or decoder driver.
 * That is, files under mtk-vcodec/.
 */
पूर्णांक mtk_v4l2_dbg_level;
EXPORT_SYMBOL(mtk_v4l2_dbg_level);

व्योम __iomem *mtk_vcodec_get_reg_addr(काष्ठा mtk_vcodec_ctx *data,
					अचिन्हित पूर्णांक reg_idx)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = (काष्ठा mtk_vcodec_ctx *)data;

	अगर (!data || reg_idx >= NUM_MAX_VCODEC_REG_BASE) अणु
		mtk_v4l2_err("Invalid arguments, reg_idx=%d", reg_idx);
		वापस शून्य;
	पूर्ण
	वापस ctx->dev->reg_base[reg_idx];
पूर्ण
EXPORT_SYMBOL(mtk_vcodec_get_reg_addr);

पूर्णांक mtk_vcodec_mem_alloc(काष्ठा mtk_vcodec_ctx *data,
			काष्ठा mtk_vcodec_mem *mem)
अणु
	अचिन्हित दीर्घ size = mem->size;
	काष्ठा mtk_vcodec_ctx *ctx = (काष्ठा mtk_vcodec_ctx *)data;
	काष्ठा device *dev = &ctx->dev->plat_dev->dev;

	mem->va = dma_alloc_coherent(dev, size, &mem->dma_addr, GFP_KERNEL);
	अगर (!mem->va) अणु
		mtk_v4l2_err("%s dma_alloc size=%ld failed!", dev_name(dev),
			     size);
		वापस -ENOMEM;
	पूर्ण

	mtk_v4l2_debug(3, "[%d]  - va      = %p", ctx->id, mem->va);
	mtk_v4l2_debug(3, "[%d]  - dma     = 0x%lx", ctx->id,
		       (अचिन्हित दीर्घ)mem->dma_addr);
	mtk_v4l2_debug(3, "[%d]    size = 0x%lx", ctx->id, size);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mtk_vcodec_mem_alloc);

व्योम mtk_vcodec_mem_मुक्त(काष्ठा mtk_vcodec_ctx *data,
			काष्ठा mtk_vcodec_mem *mem)
अणु
	अचिन्हित दीर्घ size = mem->size;
	काष्ठा mtk_vcodec_ctx *ctx = (काष्ठा mtk_vcodec_ctx *)data;
	काष्ठा device *dev = &ctx->dev->plat_dev->dev;

	अगर (!mem->va) अणु
		mtk_v4l2_err("%s dma_free size=%ld failed!", dev_name(dev),
			     size);
		वापस;
	पूर्ण

	mtk_v4l2_debug(3, "[%d]  - va      = %p", ctx->id, mem->va);
	mtk_v4l2_debug(3, "[%d]  - dma     = 0x%lx", ctx->id,
		       (अचिन्हित दीर्घ)mem->dma_addr);
	mtk_v4l2_debug(3, "[%d]    size = 0x%lx", ctx->id, size);

	dma_मुक्त_coherent(dev, size, mem->va, mem->dma_addr);
	mem->va = शून्य;
	mem->dma_addr = 0;
	mem->size = 0;
पूर्ण
EXPORT_SYMBOL(mtk_vcodec_mem_मुक्त);

व्योम mtk_vcodec_set_curr_ctx(काष्ठा mtk_vcodec_dev *dev,
	काष्ठा mtk_vcodec_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->irqlock, flags);
	dev->curr_ctx = ctx;
	spin_unlock_irqrestore(&dev->irqlock, flags);
पूर्ण
EXPORT_SYMBOL(mtk_vcodec_set_curr_ctx);

काष्ठा mtk_vcodec_ctx *mtk_vcodec_get_curr_ctx(काष्ठा mtk_vcodec_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mtk_vcodec_ctx *ctx;

	spin_lock_irqsave(&dev->irqlock, flags);
	ctx = dev->curr_ctx;
	spin_unlock_irqrestore(&dev->irqlock, flags);
	वापस ctx;
पूर्ण
EXPORT_SYMBOL(mtk_vcodec_get_curr_ctx);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Mediatek video codec driver");
