<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 - 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung EXYNOS5 SoC series G-Scaler driver
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश "gsc-core.h"

व्योम gsc_hw_set_sw_reset(काष्ठा gsc_dev *dev)
अणु
	ग_लिखोl(GSC_SW_RESET_SRESET, dev->regs + GSC_SW_RESET);
पूर्ण

पूर्णांक gsc_रुको_reset(काष्ठा gsc_dev *dev)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(50);
	u32 cfg;

	जबतक (समय_beक्रमe(jअगरfies, end)) अणु
		cfg = पढ़ोl(dev->regs + GSC_SW_RESET);
		अगर (!cfg)
			वापस 0;
		usleep_range(10, 20);
	पूर्ण

	वापस -EBUSY;
पूर्ण

व्योम gsc_hw_set_frm_करोne_irq_mask(काष्ठा gsc_dev *dev, bool mask)
अणु
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_IRQ);
	अगर (mask)
		cfg |= GSC_IRQ_FRMDONE_MASK;
	अन्यथा
		cfg &= ~GSC_IRQ_FRMDONE_MASK;
	ग_लिखोl(cfg, dev->regs + GSC_IRQ);
पूर्ण

व्योम gsc_hw_set_gsc_irq_enable(काष्ठा gsc_dev *dev, bool mask)
अणु
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_IRQ);
	अगर (mask)
		cfg |= GSC_IRQ_ENABLE;
	अन्यथा
		cfg &= ~GSC_IRQ_ENABLE;
	ग_लिखोl(cfg, dev->regs + GSC_IRQ);
पूर्ण

व्योम gsc_hw_set_input_buf_masking(काष्ठा gsc_dev *dev, u32 shअगरt,
				bool enable)
अणु
	u32 cfg = पढ़ोl(dev->regs + GSC_IN_BASE_ADDR_Y_MASK);
	u32 mask = 1 << shअगरt;

	cfg &= ~mask;
	cfg |= enable << shअगरt;

	ग_लिखोl(cfg, dev->regs + GSC_IN_BASE_ADDR_Y_MASK);
	ग_लिखोl(cfg, dev->regs + GSC_IN_BASE_ADDR_CB_MASK);
	ग_लिखोl(cfg, dev->regs + GSC_IN_BASE_ADDR_CR_MASK);
पूर्ण

व्योम gsc_hw_set_output_buf_masking(काष्ठा gsc_dev *dev, u32 shअगरt,
				bool enable)
अणु
	u32 cfg = पढ़ोl(dev->regs + GSC_OUT_BASE_ADDR_Y_MASK);
	u32 mask = 1 << shअगरt;

	cfg &= ~mask;
	cfg |= enable << shअगरt;

	ग_लिखोl(cfg, dev->regs + GSC_OUT_BASE_ADDR_Y_MASK);
	ग_लिखोl(cfg, dev->regs + GSC_OUT_BASE_ADDR_CB_MASK);
	ग_लिखोl(cfg, dev->regs + GSC_OUT_BASE_ADDR_CR_MASK);
पूर्ण

व्योम gsc_hw_set_input_addr(काष्ठा gsc_dev *dev, काष्ठा gsc_addr *addr,
				पूर्णांक index)
अणु
	pr_debug("src_buf[%d]: %pad, cb: %pad, cr: %pad", index,
			&addr->y, &addr->cb, &addr->cr);
	ग_लिखोl(addr->y, dev->regs + GSC_IN_BASE_ADDR_Y(index));
	ग_लिखोl(addr->cb, dev->regs + GSC_IN_BASE_ADDR_CB(index));
	ग_लिखोl(addr->cr, dev->regs + GSC_IN_BASE_ADDR_CR(index));

पूर्ण

व्योम gsc_hw_set_output_addr(काष्ठा gsc_dev *dev,
			     काष्ठा gsc_addr *addr, पूर्णांक index)
अणु
	pr_debug("dst_buf[%d]: %pad, cb: %pad, cr: %pad",
			index, &addr->y, &addr->cb, &addr->cr);
	ग_लिखोl(addr->y, dev->regs + GSC_OUT_BASE_ADDR_Y(index));
	ग_लिखोl(addr->cb, dev->regs + GSC_OUT_BASE_ADDR_CB(index));
	ग_लिखोl(addr->cr, dev->regs + GSC_OUT_BASE_ADDR_CR(index));
पूर्ण

व्योम gsc_hw_set_input_path(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;

	u32 cfg = पढ़ोl(dev->regs + GSC_IN_CON);
	cfg &= ~(GSC_IN_PATH_MASK | GSC_IN_LOCAL_SEL_MASK);

	अगर (ctx->in_path == GSC_DMA)
		cfg |= GSC_IN_PATH_MEMORY;

	ग_लिखोl(cfg, dev->regs + GSC_IN_CON);
पूर्ण

व्योम gsc_hw_set_in_size(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_frame *frame = &ctx->s_frame;
	u32 cfg;

	/* Set input pixel offset */
	cfg = GSC_SRCIMG_OFFSET_X(frame->crop.left);
	cfg |= GSC_SRCIMG_OFFSET_Y(frame->crop.top);
	ग_लिखोl(cfg, dev->regs + GSC_SRCIMG_OFFSET);

	/* Set input original size */
	cfg = GSC_SRCIMG_WIDTH(frame->f_width);
	cfg |= GSC_SRCIMG_HEIGHT(frame->f_height);
	ग_लिखोl(cfg, dev->regs + GSC_SRCIMG_SIZE);

	/* Set input cropped size */
	cfg = GSC_CROPPED_WIDTH(frame->crop.width);
	cfg |= GSC_CROPPED_HEIGHT(frame->crop.height);
	ग_लिखोl(cfg, dev->regs + GSC_CROPPED_SIZE);
पूर्ण

व्योम gsc_hw_set_in_image_rgb(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_frame *frame = &ctx->s_frame;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_IN_CON);
	अगर (frame->colorspace == V4L2_COLORSPACE_REC709)
		cfg |= GSC_IN_RGB_HD_WIDE;
	अन्यथा
		cfg |= GSC_IN_RGB_SD_WIDE;

	अगर (frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_RGB565X)
		cfg |= GSC_IN_RGB565;
	अन्यथा अगर (frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_RGB32)
		cfg |= GSC_IN_XRGB8888;

	ग_लिखोl(cfg, dev->regs + GSC_IN_CON);
पूर्ण

व्योम gsc_hw_set_in_image_क्रमmat(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_frame *frame = &ctx->s_frame;
	u32 i, depth = 0;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_IN_CON);
	cfg &= ~(GSC_IN_RGB_TYPE_MASK | GSC_IN_YUV422_1P_ORDER_MASK |
		 GSC_IN_CHROMA_ORDER_MASK | GSC_IN_FORMAT_MASK |
		 GSC_IN_TILE_TYPE_MASK | GSC_IN_TILE_MODE);
	ग_लिखोl(cfg, dev->regs + GSC_IN_CON);

	अगर (is_rgb(frame->fmt->color)) अणु
		gsc_hw_set_in_image_rgb(ctx);
		वापस;
	पूर्ण
	क्रम (i = 0; i < frame->fmt->num_planes; i++)
		depth += frame->fmt->depth[i];

	चयन (frame->fmt->num_comp) अणु
	हाल 1:
		cfg |= GSC_IN_YUV422_1P;
		अगर (frame->fmt->yorder == GSC_LSB_Y)
			cfg |= GSC_IN_YUV422_1P_ORDER_LSB_Y;
		अन्यथा
			cfg |= GSC_IN_YUV422_1P_OEDER_LSB_C;
		अगर (frame->fmt->corder == GSC_CBCR)
			cfg |= GSC_IN_CHROMA_ORDER_CBCR;
		अन्यथा
			cfg |= GSC_IN_CHROMA_ORDER_CRCB;
		अवरोध;
	हाल 2:
		अगर (depth == 12)
			cfg |= GSC_IN_YUV420_2P;
		अन्यथा
			cfg |= GSC_IN_YUV422_2P;
		अगर (frame->fmt->corder == GSC_CBCR)
			cfg |= GSC_IN_CHROMA_ORDER_CBCR;
		अन्यथा
			cfg |= GSC_IN_CHROMA_ORDER_CRCB;
		अवरोध;
	हाल 3:
		अगर (depth == 12)
			cfg |= GSC_IN_YUV420_3P;
		अन्यथा
			cfg |= GSC_IN_YUV422_3P;
		अवरोध;
	पूर्ण

	अगर (is_tiled(frame->fmt))
		cfg |= GSC_IN_TILE_C_16x8 | GSC_IN_TILE_MODE;

	ग_लिखोl(cfg, dev->regs + GSC_IN_CON);
पूर्ण

व्योम gsc_hw_set_output_path(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;

	u32 cfg = पढ़ोl(dev->regs + GSC_OUT_CON);
	cfg &= ~GSC_OUT_PATH_MASK;

	अगर (ctx->out_path == GSC_DMA)
		cfg |= GSC_OUT_PATH_MEMORY;
	अन्यथा
		cfg |= GSC_OUT_PATH_LOCAL;

	ग_लिखोl(cfg, dev->regs + GSC_OUT_CON);
पूर्ण

व्योम gsc_hw_set_out_size(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_frame *frame = &ctx->d_frame;
	u32 cfg;

	/* Set output original size */
	अगर (ctx->out_path == GSC_DMA) अणु
		cfg = GSC_DSTIMG_OFFSET_X(frame->crop.left);
		cfg |= GSC_DSTIMG_OFFSET_Y(frame->crop.top);
		ग_लिखोl(cfg, dev->regs + GSC_DSTIMG_OFFSET);

		cfg = GSC_DSTIMG_WIDTH(frame->f_width);
		cfg |= GSC_DSTIMG_HEIGHT(frame->f_height);
		ग_लिखोl(cfg, dev->regs + GSC_DSTIMG_SIZE);
	पूर्ण

	/* Set output scaled size */
	अगर (ctx->gsc_ctrls.rotate->val == 90 ||
	    ctx->gsc_ctrls.rotate->val == 270) अणु
		cfg = GSC_SCALED_WIDTH(frame->crop.height);
		cfg |= GSC_SCALED_HEIGHT(frame->crop.width);
	पूर्ण अन्यथा अणु
		cfg = GSC_SCALED_WIDTH(frame->crop.width);
		cfg |= GSC_SCALED_HEIGHT(frame->crop.height);
	पूर्ण
	ग_लिखोl(cfg, dev->regs + GSC_SCALED_SIZE);
पूर्ण

व्योम gsc_hw_set_out_image_rgb(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_frame *frame = &ctx->d_frame;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_OUT_CON);
	अगर (frame->colorspace == V4L2_COLORSPACE_REC709)
		cfg |= GSC_OUT_RGB_HD_WIDE;
	अन्यथा
		cfg |= GSC_OUT_RGB_SD_WIDE;

	अगर (frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_RGB565X)
		cfg |= GSC_OUT_RGB565;
	अन्यथा अगर (frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_RGB32)
		cfg |= GSC_OUT_XRGB8888;

	ग_लिखोl(cfg, dev->regs + GSC_OUT_CON);
पूर्ण

व्योम gsc_hw_set_out_image_क्रमmat(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_frame *frame = &ctx->d_frame;
	u32 i, depth = 0;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_OUT_CON);
	cfg &= ~(GSC_OUT_RGB_TYPE_MASK | GSC_OUT_YUV422_1P_ORDER_MASK |
		 GSC_OUT_CHROMA_ORDER_MASK | GSC_OUT_FORMAT_MASK |
		 GSC_OUT_TILE_TYPE_MASK | GSC_OUT_TILE_MODE);
	ग_लिखोl(cfg, dev->regs + GSC_OUT_CON);

	अगर (is_rgb(frame->fmt->color)) अणु
		gsc_hw_set_out_image_rgb(ctx);
		वापस;
	पूर्ण

	अगर (ctx->out_path != GSC_DMA) अणु
		cfg |= GSC_OUT_YUV444;
		जाओ end_set;
	पूर्ण

	क्रम (i = 0; i < frame->fmt->num_planes; i++)
		depth += frame->fmt->depth[i];

	चयन (frame->fmt->num_comp) अणु
	हाल 1:
		cfg |= GSC_OUT_YUV422_1P;
		अगर (frame->fmt->yorder == GSC_LSB_Y)
			cfg |= GSC_OUT_YUV422_1P_ORDER_LSB_Y;
		अन्यथा
			cfg |= GSC_OUT_YUV422_1P_OEDER_LSB_C;
		अगर (frame->fmt->corder == GSC_CBCR)
			cfg |= GSC_OUT_CHROMA_ORDER_CBCR;
		अन्यथा
			cfg |= GSC_OUT_CHROMA_ORDER_CRCB;
		अवरोध;
	हाल 2:
		अगर (depth == 12)
			cfg |= GSC_OUT_YUV420_2P;
		अन्यथा
			cfg |= GSC_OUT_YUV422_2P;
		अगर (frame->fmt->corder == GSC_CBCR)
			cfg |= GSC_OUT_CHROMA_ORDER_CBCR;
		अन्यथा
			cfg |= GSC_OUT_CHROMA_ORDER_CRCB;
		अवरोध;
	हाल 3:
		cfg |= GSC_OUT_YUV420_3P;
		अवरोध;
	पूर्ण

	अगर (is_tiled(frame->fmt))
		cfg |= GSC_OUT_TILE_C_16x8 | GSC_OUT_TILE_MODE;

end_set:
	ग_लिखोl(cfg, dev->regs + GSC_OUT_CON);
पूर्ण

व्योम gsc_hw_set_prescaler(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_scaler *sc = &ctx->scaler;
	u32 cfg;

	cfg = GSC_PRESC_SHFACTOR(sc->pre_shfactor);
	cfg |= GSC_PRESC_H_RATIO(sc->pre_hratio);
	cfg |= GSC_PRESC_V_RATIO(sc->pre_vratio);
	ग_लिखोl(cfg, dev->regs + GSC_PRE_SCALE_RATIO);
पूर्ण

व्योम gsc_hw_set_मुख्यscaler(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_scaler *sc = &ctx->scaler;
	u32 cfg;

	cfg = GSC_MAIN_H_RATIO_VALUE(sc->मुख्य_hratio);
	ग_लिखोl(cfg, dev->regs + GSC_MAIN_H_RATIO);

	cfg = GSC_MAIN_V_RATIO_VALUE(sc->मुख्य_vratio);
	ग_लिखोl(cfg, dev->regs + GSC_MAIN_V_RATIO);
पूर्ण

व्योम gsc_hw_set_rotation(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_IN_CON);
	cfg &= ~GSC_IN_ROT_MASK;

	चयन (ctx->gsc_ctrls.rotate->val) अणु
	हाल 270:
		cfg |= GSC_IN_ROT_270;
		अवरोध;
	हाल 180:
		cfg |= GSC_IN_ROT_180;
		अवरोध;
	हाल 90:
		अगर (ctx->gsc_ctrls.hflip->val)
			cfg |= GSC_IN_ROT_90_XFLIP;
		अन्यथा अगर (ctx->gsc_ctrls.vflip->val)
			cfg |= GSC_IN_ROT_90_YFLIP;
		अन्यथा
			cfg |= GSC_IN_ROT_90;
		अवरोध;
	हाल 0:
		अगर (ctx->gsc_ctrls.hflip->val)
			cfg |= GSC_IN_ROT_XFLIP;
		अन्यथा अगर (ctx->gsc_ctrls.vflip->val)
			cfg |= GSC_IN_ROT_YFLIP;
	पूर्ण

	ग_लिखोl(cfg, dev->regs + GSC_IN_CON);
पूर्ण

व्योम gsc_hw_set_global_alpha(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	काष्ठा gsc_frame *frame = &ctx->d_frame;
	u32 cfg;

	अगर (!is_rgb(frame->fmt->color)) अणु
		pr_debug("Not a RGB format");
		वापस;
	पूर्ण

	cfg = पढ़ोl(dev->regs + GSC_OUT_CON);
	cfg &= ~GSC_OUT_GLOBAL_ALPHA_MASK;

	cfg |= GSC_OUT_GLOBAL_ALPHA(ctx->gsc_ctrls.global_alpha->val);
	ग_लिखोl(cfg, dev->regs + GSC_OUT_CON);
पूर्ण

व्योम gsc_hw_set_sfr_update(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_dev *dev = ctx->gsc_dev;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + GSC_ENABLE);
	cfg |= GSC_ENABLE_SFR_UPDATE;
	ग_लिखोl(cfg, dev->regs + GSC_ENABLE);
पूर्ण
