<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Register पूर्णांकerface file क्रम Samsung Camera Interface (FIMC) driver
 *
 * Copyright (C) 2010 - 2013 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
*/

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/regmap.h>

#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>
#समावेश "media-dev.h"

#समावेश "fimc-reg.h"
#समावेश "fimc-core.h"

व्योम fimc_hw_reset(काष्ठा fimc_dev *dev)
अणु
	u32 cfg;

	cfg = पढ़ोl(dev->regs + FIMC_REG_CISRCFMT);
	cfg |= FIMC_REG_CISRCFMT_ITU601_8BIT;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CISRCFMT);

	/* Software reset. */
	cfg = पढ़ोl(dev->regs + FIMC_REG_CIGCTRL);
	cfg |= (FIMC_REG_CIGCTRL_SWRST | FIMC_REG_CIGCTRL_IRQ_LEVEL);
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIGCTRL);
	udelay(10);

	cfg = पढ़ोl(dev->regs + FIMC_REG_CIGCTRL);
	cfg &= ~FIMC_REG_CIGCTRL_SWRST;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIGCTRL);

	अगर (dev->drv_data->out_buf_count > 4)
		fimc_hw_set_dma_seq(dev, 0xF);
पूर्ण

अटल u32 fimc_hw_get_in_flip(काष्ठा fimc_ctx *ctx)
अणु
	u32 flip = FIMC_REG_MSCTRL_FLIP_NORMAL;

	अगर (ctx->hflip)
		flip = FIMC_REG_MSCTRL_FLIP_Y_MIRROR;
	अगर (ctx->vflip)
		flip = FIMC_REG_MSCTRL_FLIP_X_MIRROR;

	अगर (ctx->rotation <= 90)
		वापस flip;

	वापस (flip ^ FIMC_REG_MSCTRL_FLIP_180) & FIMC_REG_MSCTRL_FLIP_180;
पूर्ण

अटल u32 fimc_hw_get_target_flip(काष्ठा fimc_ctx *ctx)
अणु
	u32 flip = FIMC_REG_CITRGFMT_FLIP_NORMAL;

	अगर (ctx->hflip)
		flip |= FIMC_REG_CITRGFMT_FLIP_Y_MIRROR;
	अगर (ctx->vflip)
		flip |= FIMC_REG_CITRGFMT_FLIP_X_MIRROR;

	अगर (ctx->rotation <= 90)
		वापस flip;

	वापस (flip ^ FIMC_REG_CITRGFMT_FLIP_180) & FIMC_REG_CITRGFMT_FLIP_180;
पूर्ण

व्योम fimc_hw_set_rotation(काष्ठा fimc_ctx *ctx)
अणु
	u32 cfg, flip;
	काष्ठा fimc_dev *dev = ctx->fimc_dev;

	cfg = पढ़ोl(dev->regs + FIMC_REG_CITRGFMT);
	cfg &= ~(FIMC_REG_CITRGFMT_INROT90 | FIMC_REG_CITRGFMT_OUTROT90 |
		 FIMC_REG_CITRGFMT_FLIP_180);

	/*
	 * The input and output rotator cannot work simultaneously.
	 * Use the output rotator in output DMA mode or the input rotator
	 * in direct fअगरo output mode.
	 */
	अगर (ctx->rotation == 90 || ctx->rotation == 270) अणु
		अगर (ctx->out_path == FIMC_IO_LCDFIFO)
			cfg |= FIMC_REG_CITRGFMT_INROT90;
		अन्यथा
			cfg |= FIMC_REG_CITRGFMT_OUTROT90;
	पूर्ण

	अगर (ctx->out_path == FIMC_IO_DMA) अणु
		cfg |= fimc_hw_get_target_flip(ctx);
		ग_लिखोl(cfg, dev->regs + FIMC_REG_CITRGFMT);
	पूर्ण अन्यथा अणु
		/* LCD FIFO path */
		flip = पढ़ोl(dev->regs + FIMC_REG_MSCTRL);
		flip &= ~FIMC_REG_MSCTRL_FLIP_MASK;
		flip |= fimc_hw_get_in_flip(ctx);
		ग_लिखोl(flip, dev->regs + FIMC_REG_MSCTRL);
	पूर्ण
पूर्ण

व्योम fimc_hw_set_target_क्रमmat(काष्ठा fimc_ctx *ctx)
अणु
	u32 cfg;
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_frame *frame = &ctx->d_frame;

	dbg("w= %d, h= %d color: %d", frame->width,
	    frame->height, frame->fmt->color);

	cfg = पढ़ोl(dev->regs + FIMC_REG_CITRGFMT);
	cfg &= ~(FIMC_REG_CITRGFMT_FMT_MASK | FIMC_REG_CITRGFMT_HSIZE_MASK |
		 FIMC_REG_CITRGFMT_VSIZE_MASK);

	चयन (frame->fmt->color) अणु
	हाल FIMC_FMT_RGB444...FIMC_FMT_RGB888:
		cfg |= FIMC_REG_CITRGFMT_RGB;
		अवरोध;
	हाल FIMC_FMT_YCBCR420:
		cfg |= FIMC_REG_CITRGFMT_YCBCR420;
		अवरोध;
	हाल FIMC_FMT_YCBYCR422...FIMC_FMT_CRYCBY422:
		अगर (frame->fmt->colplanes == 1)
			cfg |= FIMC_REG_CITRGFMT_YCBCR422_1P;
		अन्यथा
			cfg |= FIMC_REG_CITRGFMT_YCBCR422;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ctx->rotation == 90 || ctx->rotation == 270)
		cfg |= (frame->height << 16) | frame->width;
	अन्यथा
		cfg |= (frame->width << 16) | frame->height;

	ग_लिखोl(cfg, dev->regs + FIMC_REG_CITRGFMT);

	cfg = पढ़ोl(dev->regs + FIMC_REG_CITAREA);
	cfg &= ~FIMC_REG_CITAREA_MASK;
	cfg |= (frame->width * frame->height);
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CITAREA);
पूर्ण

अटल व्योम fimc_hw_set_out_dma_size(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_frame *frame = &ctx->d_frame;
	u32 cfg;

	cfg = (frame->f_height << 16) | frame->f_width;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_ORGOSIZE);

	/* Select color space conversion equation (HD/SD size).*/
	cfg = पढ़ोl(dev->regs + FIMC_REG_CIGCTRL);
	अगर (frame->f_width >= 1280) /* HD */
		cfg |= FIMC_REG_CIGCTRL_CSC_ITU601_709;
	अन्यथा	/* SD */
		cfg &= ~FIMC_REG_CIGCTRL_CSC_ITU601_709;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIGCTRL);

पूर्ण

व्योम fimc_hw_set_out_dma(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_frame *frame = &ctx->d_frame;
	काष्ठा fimc_dma_offset *offset = &frame->dma_offset;
	काष्ठा fimc_fmt *fmt = frame->fmt;
	u32 cfg;

	/* Set the input dma offsets. */
	cfg = (offset->y_v << 16) | offset->y_h;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIOYOFF);

	cfg = (offset->cb_v << 16) | offset->cb_h;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIOCBOFF);

	cfg = (offset->cr_v << 16) | offset->cr_h;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIOCROFF);

	fimc_hw_set_out_dma_size(ctx);

	/* Configure chroma components order. */
	cfg = पढ़ोl(dev->regs + FIMC_REG_CIOCTRL);

	cfg &= ~(FIMC_REG_CIOCTRL_ORDER2P_MASK |
		 FIMC_REG_CIOCTRL_ORDER422_MASK |
		 FIMC_REG_CIOCTRL_YCBCR_PLANE_MASK |
		 FIMC_REG_CIOCTRL_RGB16FMT_MASK);

	अगर (fmt->colplanes == 1)
		cfg |= ctx->out_order_1p;
	अन्यथा अगर (fmt->colplanes == 2)
		cfg |= ctx->out_order_2p | FIMC_REG_CIOCTRL_YCBCR_2PLANE;
	अन्यथा अगर (fmt->colplanes == 3)
		cfg |= FIMC_REG_CIOCTRL_YCBCR_3PLANE;

	अगर (fmt->color == FIMC_FMT_RGB565)
		cfg |= FIMC_REG_CIOCTRL_RGB565;
	अन्यथा अगर (fmt->color == FIMC_FMT_RGB555)
		cfg |= FIMC_REG_CIOCTRL_ARGB1555;
	अन्यथा अगर (fmt->color == FIMC_FMT_RGB444)
		cfg |= FIMC_REG_CIOCTRL_ARGB4444;

	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIOCTRL);
पूर्ण

अटल व्योम fimc_hw_en_स्वतःload(काष्ठा fimc_dev *dev, पूर्णांक enable)
अणु
	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_ORGISIZE);
	अगर (enable)
		cfg |= FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN;
	अन्यथा
		cfg &= ~FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_ORGISIZE);
पूर्ण

व्योम fimc_hw_en_lastirq(काष्ठा fimc_dev *dev, पूर्णांक enable)
अणु
	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_CIOCTRL);
	अगर (enable)
		cfg |= FIMC_REG_CIOCTRL_LASTIRQ_ENABLE;
	अन्यथा
		cfg &= ~FIMC_REG_CIOCTRL_LASTIRQ_ENABLE;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIOCTRL);
पूर्ण

व्योम fimc_hw_set_prescaler(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev =  ctx->fimc_dev;
	काष्ठा fimc_scaler *sc = &ctx->scaler;
	u32 cfg, shfactor;

	shfactor = 10 - (sc->hfactor + sc->vfactor);
	cfg = shfactor << 28;

	cfg |= (sc->pre_hratio << 16) | sc->pre_vratio;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CISCPRERATIO);

	cfg = (sc->pre_dst_width << 16) | sc->pre_dst_height;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CISCPREDST);
पूर्ण

अटल व्योम fimc_hw_set_scaler(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_scaler *sc = &ctx->scaler;
	काष्ठा fimc_frame *src_frame = &ctx->s_frame;
	काष्ठा fimc_frame *dst_frame = &ctx->d_frame;

	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_CISCCTRL);

	cfg &= ~(FIMC_REG_CISCCTRL_CSCR2Y_WIDE | FIMC_REG_CISCCTRL_CSCY2R_WIDE |
		 FIMC_REG_CISCCTRL_SCALEUP_H | FIMC_REG_CISCCTRL_SCALEUP_V |
		 FIMC_REG_CISCCTRL_SCALERBYPASS | FIMC_REG_CISCCTRL_ONE2ONE |
		 FIMC_REG_CISCCTRL_INRGB_FMT_MASK | FIMC_REG_CISCCTRL_OUTRGB_FMT_MASK |
		 FIMC_REG_CISCCTRL_INTERLACE | FIMC_REG_CISCCTRL_RGB_EXT);

	अगर (!(ctx->flags & FIMC_COLOR_RANGE_NARROW))
		cfg |= (FIMC_REG_CISCCTRL_CSCR2Y_WIDE |
			FIMC_REG_CISCCTRL_CSCY2R_WIDE);

	अगर (!sc->enabled)
		cfg |= FIMC_REG_CISCCTRL_SCALERBYPASS;

	अगर (sc->scaleup_h)
		cfg |= FIMC_REG_CISCCTRL_SCALEUP_H;

	अगर (sc->scaleup_v)
		cfg |= FIMC_REG_CISCCTRL_SCALEUP_V;

	अगर (sc->copy_mode)
		cfg |= FIMC_REG_CISCCTRL_ONE2ONE;

	अगर (ctx->in_path == FIMC_IO_DMA) अणु
		चयन (src_frame->fmt->color) अणु
		हाल FIMC_FMT_RGB565:
			cfg |= FIMC_REG_CISCCTRL_INRGB_FMT_RGB565;
			अवरोध;
		हाल FIMC_FMT_RGB666:
			cfg |= FIMC_REG_CISCCTRL_INRGB_FMT_RGB666;
			अवरोध;
		हाल FIMC_FMT_RGB888:
			cfg |= FIMC_REG_CISCCTRL_INRGB_FMT_RGB888;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ctx->out_path == FIMC_IO_DMA) अणु
		u32 color = dst_frame->fmt->color;

		अगर (color >= FIMC_FMT_RGB444 && color <= FIMC_FMT_RGB565)
			cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB565;
		अन्यथा अगर (color == FIMC_FMT_RGB666)
			cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB666;
		अन्यथा अगर (color == FIMC_FMT_RGB888)
			cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB888;
	पूर्ण अन्यथा अणु
		cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB888;

		अगर (ctx->flags & FIMC_SCAN_MODE_INTERLACED)
			cfg |= FIMC_REG_CISCCTRL_INTERLACE;
	पूर्ण

	ग_लिखोl(cfg, dev->regs + FIMC_REG_CISCCTRL);
पूर्ण

व्योम fimc_hw_set_मुख्यscaler(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	स्थिर काष्ठा fimc_variant *variant = dev->variant;
	काष्ठा fimc_scaler *sc = &ctx->scaler;
	u32 cfg;

	dbg("main_hratio= 0x%X  main_vratio= 0x%X",
	    sc->मुख्य_hratio, sc->मुख्य_vratio);

	fimc_hw_set_scaler(ctx);

	cfg = पढ़ोl(dev->regs + FIMC_REG_CISCCTRL);
	cfg &= ~(FIMC_REG_CISCCTRL_MHRATIO_MASK |
		 FIMC_REG_CISCCTRL_MVRATIO_MASK);

	अगर (variant->has_मुख्यscaler_ext) अणु
		cfg |= FIMC_REG_CISCCTRL_MHRATIO_EXT(sc->मुख्य_hratio);
		cfg |= FIMC_REG_CISCCTRL_MVRATIO_EXT(sc->मुख्य_vratio);
		ग_लिखोl(cfg, dev->regs + FIMC_REG_CISCCTRL);

		cfg = पढ़ोl(dev->regs + FIMC_REG_CIEXTEN);

		cfg &= ~(FIMC_REG_CIEXTEN_MVRATIO_EXT_MASK |
			 FIMC_REG_CIEXTEN_MHRATIO_EXT_MASK);
		cfg |= FIMC_REG_CIEXTEN_MHRATIO_EXT(sc->मुख्य_hratio);
		cfg |= FIMC_REG_CIEXTEN_MVRATIO_EXT(sc->मुख्य_vratio);
		ग_लिखोl(cfg, dev->regs + FIMC_REG_CIEXTEN);
	पूर्ण अन्यथा अणु
		cfg |= FIMC_REG_CISCCTRL_MHRATIO(sc->मुख्य_hratio);
		cfg |= FIMC_REG_CISCCTRL_MVRATIO(sc->मुख्य_vratio);
		ग_लिखोl(cfg, dev->regs + FIMC_REG_CISCCTRL);
	पूर्ण
पूर्ण

व्योम fimc_hw_enable_capture(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + FIMC_REG_CIIMGCPT);
	cfg |= FIMC_REG_CIIMGCPT_CPT_FREN_ENABLE;

	अगर (ctx->scaler.enabled)
		cfg |= FIMC_REG_CIIMGCPT_IMGCPTEN_SC;
	अन्यथा
		cfg &= FIMC_REG_CIIMGCPT_IMGCPTEN_SC;

	cfg |= FIMC_REG_CIIMGCPT_IMGCPTEN;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIIMGCPT);
पूर्ण

व्योम fimc_hw_disable_capture(काष्ठा fimc_dev *dev)
अणु
	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_CIIMGCPT);
	cfg &= ~(FIMC_REG_CIIMGCPT_IMGCPTEN |
		 FIMC_REG_CIIMGCPT_IMGCPTEN_SC);
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIIMGCPT);
पूर्ण

व्योम fimc_hw_set_effect(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_effect *effect = &ctx->effect;
	u32 cfg = 0;

	अगर (effect->type != FIMC_REG_CIIMGEFF_FIN_BYPASS) अणु
		cfg |= FIMC_REG_CIIMGEFF_IE_SC_AFTER |
			FIMC_REG_CIIMGEFF_IE_ENABLE;
		cfg |= effect->type;
		अगर (effect->type == FIMC_REG_CIIMGEFF_FIN_ARBITRARY)
			cfg |= (effect->pat_cb << 13) | effect->pat_cr;
	पूर्ण

	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIIMGEFF);
पूर्ण

व्योम fimc_hw_set_rgb_alpha(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_frame *frame = &ctx->d_frame;
	u32 cfg;

	अगर (!(frame->fmt->flags & FMT_HAS_ALPHA))
		वापस;

	cfg = पढ़ोl(dev->regs + FIMC_REG_CIOCTRL);
	cfg &= ~FIMC_REG_CIOCTRL_ALPHA_OUT_MASK;
	cfg |= (frame->alpha << 4);
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIOCTRL);
पूर्ण

अटल व्योम fimc_hw_set_in_dma_size(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_frame *frame = &ctx->s_frame;
	u32 cfg_o = 0;
	u32 cfg_r = 0;

	अगर (FIMC_IO_LCDFIFO == ctx->out_path)
		cfg_r |= FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN;

	cfg_o |= (frame->f_height << 16) | frame->f_width;
	cfg_r |= (frame->height << 16) | frame->width;

	ग_लिखोl(cfg_o, dev->regs + FIMC_REG_ORGISIZE);
	ग_लिखोl(cfg_r, dev->regs + FIMC_REG_CIREAL_ISIZE);
पूर्ण

व्योम fimc_hw_set_in_dma(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;
	काष्ठा fimc_frame *frame = &ctx->s_frame;
	काष्ठा fimc_dma_offset *offset = &frame->dma_offset;
	u32 cfg;

	/* Set the pixel offsets. */
	cfg = (offset->y_v << 16) | offset->y_h;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIIYOFF);

	cfg = (offset->cb_v << 16) | offset->cb_h;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIICBOFF);

	cfg = (offset->cr_v << 16) | offset->cr_h;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIICROFF);

	/* Input original and real size. */
	fimc_hw_set_in_dma_size(ctx);

	/* Use DMA स्वतःload only in FIFO mode. */
	fimc_hw_en_स्वतःload(dev, ctx->out_path == FIMC_IO_LCDFIFO);

	/* Set the input DMA to process single frame only. */
	cfg = पढ़ोl(dev->regs + FIMC_REG_MSCTRL);
	cfg &= ~(FIMC_REG_MSCTRL_INFORMAT_MASK
		 | FIMC_REG_MSCTRL_IN_BURST_COUNT_MASK
		 | FIMC_REG_MSCTRL_INPUT_MASK
		 | FIMC_REG_MSCTRL_C_INT_IN_MASK
		 | FIMC_REG_MSCTRL_2P_IN_ORDER_MASK
		 | FIMC_REG_MSCTRL_ORDER422_MASK);

	cfg |= (FIMC_REG_MSCTRL_IN_BURST_COUNT(4)
		| FIMC_REG_MSCTRL_INPUT_MEMORY
		| FIMC_REG_MSCTRL_FIFO_CTRL_FULL);

	चयन (frame->fmt->color) अणु
	हाल FIMC_FMT_RGB565...FIMC_FMT_RGB888:
		cfg |= FIMC_REG_MSCTRL_INFORMAT_RGB;
		अवरोध;
	हाल FIMC_FMT_YCBCR420:
		cfg |= FIMC_REG_MSCTRL_INFORMAT_YCBCR420;

		अगर (frame->fmt->colplanes == 2)
			cfg |= ctx->in_order_2p | FIMC_REG_MSCTRL_C_INT_IN_2PLANE;
		अन्यथा
			cfg |= FIMC_REG_MSCTRL_C_INT_IN_3PLANE;

		अवरोध;
	हाल FIMC_FMT_YCBYCR422...FIMC_FMT_CRYCBY422:
		अगर (frame->fmt->colplanes == 1) अणु
			cfg |= ctx->in_order_1p
				| FIMC_REG_MSCTRL_INFORMAT_YCBCR422_1P;
		पूर्ण अन्यथा अणु
			cfg |= FIMC_REG_MSCTRL_INFORMAT_YCBCR422;

			अगर (frame->fmt->colplanes == 2)
				cfg |= ctx->in_order_2p
					| FIMC_REG_MSCTRL_C_INT_IN_2PLANE;
			अन्यथा
				cfg |= FIMC_REG_MSCTRL_C_INT_IN_3PLANE;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(cfg, dev->regs + FIMC_REG_MSCTRL);

	/* Input/output DMA linear/tiled mode. */
	cfg = पढ़ोl(dev->regs + FIMC_REG_CIDMAPARAM);
	cfg &= ~FIMC_REG_CIDMAPARAM_TILE_MASK;

	अगर (tiled_fmt(ctx->s_frame.fmt))
		cfg |= FIMC_REG_CIDMAPARAM_R_64X32;

	अगर (tiled_fmt(ctx->d_frame.fmt))
		cfg |= FIMC_REG_CIDMAPARAM_W_64X32;

	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIDMAPARAM);
पूर्ण


व्योम fimc_hw_set_input_path(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;

	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_MSCTRL);
	cfg &= ~FIMC_REG_MSCTRL_INPUT_MASK;

	अगर (ctx->in_path == FIMC_IO_DMA)
		cfg |= FIMC_REG_MSCTRL_INPUT_MEMORY;
	अन्यथा
		cfg |= FIMC_REG_MSCTRL_INPUT_EXTCAM;

	ग_लिखोl(cfg, dev->regs + FIMC_REG_MSCTRL);
पूर्ण

व्योम fimc_hw_set_output_path(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *dev = ctx->fimc_dev;

	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_CISCCTRL);
	cfg &= ~FIMC_REG_CISCCTRL_LCDPATHEN_FIFO;
	अगर (ctx->out_path == FIMC_IO_LCDFIFO)
		cfg |= FIMC_REG_CISCCTRL_LCDPATHEN_FIFO;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CISCCTRL);
पूर्ण

व्योम fimc_hw_set_input_addr(काष्ठा fimc_dev *dev, काष्ठा fimc_addr *addr)
अणु
	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_CIREAL_ISIZE);
	cfg |= FIMC_REG_CIREAL_ISIZE_ADDR_CH_DIS;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIREAL_ISIZE);

	ग_लिखोl(addr->y, dev->regs + FIMC_REG_CIIYSA(0));
	ग_लिखोl(addr->cb, dev->regs + FIMC_REG_CIICBSA(0));
	ग_लिखोl(addr->cr, dev->regs + FIMC_REG_CIICRSA(0));

	cfg &= ~FIMC_REG_CIREAL_ISIZE_ADDR_CH_DIS;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIREAL_ISIZE);
पूर्ण

व्योम fimc_hw_set_output_addr(काष्ठा fimc_dev *dev,
			     काष्ठा fimc_addr *addr, पूर्णांक index)
अणु
	पूर्णांक i = (index == -1) ? 0 : index;
	करो अणु
		ग_लिखोl(addr->y, dev->regs + FIMC_REG_CIOYSA(i));
		ग_लिखोl(addr->cb, dev->regs + FIMC_REG_CIOCBSA(i));
		ग_लिखोl(addr->cr, dev->regs + FIMC_REG_CIOCRSA(i));
		dbg("dst_buf[%d]: 0x%X, cb: 0x%X, cr: 0x%X",
		    i, addr->y, addr->cb, addr->cr);
	पूर्ण जबतक (index == -1 && ++i < FIMC_MAX_OUT_BUFS);
पूर्ण

पूर्णांक fimc_hw_set_camera_polarity(काष्ठा fimc_dev *fimc,
				काष्ठा fimc_source_info *cam)
अणु
	u32 cfg = पढ़ोl(fimc->regs + FIMC_REG_CIGCTRL);

	cfg &= ~(FIMC_REG_CIGCTRL_INVPOLPCLK | FIMC_REG_CIGCTRL_INVPOLVSYNC |
		 FIMC_REG_CIGCTRL_INVPOLHREF | FIMC_REG_CIGCTRL_INVPOLHSYNC |
		 FIMC_REG_CIGCTRL_INVPOLFIELD);

	अगर (cam->flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		cfg |= FIMC_REG_CIGCTRL_INVPOLPCLK;

	अगर (cam->flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLVSYNC;

	अगर (cam->flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLHREF;

	अगर (cam->flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLHSYNC;

	अगर (cam->flags & V4L2_MBUS_FIELD_EVEN_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLFIELD;

	ग_लिखोl(cfg, fimc->regs + FIMC_REG_CIGCTRL);

	वापस 0;
पूर्ण

काष्ठा mbus_pixfmt_desc अणु
	u32 pixelcode;
	u32 cisrcfmt;
	u16 bus_width;
पूर्ण;

अटल स्थिर काष्ठा mbus_pixfmt_desc pix_desc[] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_2X8, FIMC_REG_CISRCFMT_ORDER422_YCBYCR, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, FIMC_REG_CISRCFMT_ORDER422_YCRYCB, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, FIMC_REG_CISRCFMT_ORDER422_CRYCBY, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, FIMC_REG_CISRCFMT_ORDER422_CBYCRY, 8 पूर्ण,
पूर्ण;

पूर्णांक fimc_hw_set_camera_source(काष्ठा fimc_dev *fimc,
			      काष्ठा fimc_source_info *source)
अणु
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा fimc_frame *f = &vc->ctx->s_frame;
	u32 bus_width, cfg = 0;
	पूर्णांक i;

	चयन (source->fimc_bus_type) अणु
	हाल FIMC_BUS_TYPE_ITU_601:
	हाल FIMC_BUS_TYPE_ITU_656:
		अगर (fimc_fmt_is_user_defined(f->fmt->color)) अणु
			cfg |= FIMC_REG_CISRCFMT_ITU601_8BIT;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(pix_desc); i++) अणु
			अगर (vc->ci_fmt.code == pix_desc[i].pixelcode) अणु
				cfg = pix_desc[i].cisrcfmt;
				bus_width = pix_desc[i].bus_width;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == ARRAY_SIZE(pix_desc)) अणु
			v4l2_err(&vc->ve.vdev,
				 "Camera color format not supported: %d\n",
				 vc->ci_fmt.code);
			वापस -EINVAL;
		पूर्ण

		अगर (source->fimc_bus_type == FIMC_BUS_TYPE_ITU_601) अणु
			अगर (bus_width == 8)
				cfg |= FIMC_REG_CISRCFMT_ITU601_8BIT;
			अन्यथा अगर (bus_width == 16)
				cfg |= FIMC_REG_CISRCFMT_ITU601_16BIT;
		पूर्ण /* अन्यथा शेषs to ITU-R BT.656 8-bit */
		अवरोध;
	हाल FIMC_BUS_TYPE_MIPI_CSI2:
		अगर (fimc_fmt_is_user_defined(f->fmt->color))
			cfg |= FIMC_REG_CISRCFMT_ITU601_8BIT;
		अवरोध;
	शेष:
	हाल FIMC_BUS_TYPE_ISP_WRITEBACK:
		/* Anything to करो here ? */
		अवरोध;
	पूर्ण

	cfg |= (f->o_width << 16) | f->o_height;
	ग_लिखोl(cfg, fimc->regs + FIMC_REG_CISRCFMT);
	वापस 0;
पूर्ण

व्योम fimc_hw_set_camera_offset(काष्ठा fimc_dev *fimc, काष्ठा fimc_frame *f)
अणु
	u32 hoff2, voff2;

	u32 cfg = पढ़ोl(fimc->regs + FIMC_REG_CIWDOFST);

	cfg &= ~(FIMC_REG_CIWDOFST_HOROFF_MASK | FIMC_REG_CIWDOFST_VEROFF_MASK);
	cfg |=  FIMC_REG_CIWDOFST_OFF_EN |
		(f->offs_h << 16) | f->offs_v;

	ग_लिखोl(cfg, fimc->regs + FIMC_REG_CIWDOFST);

	/* See CIWDOFSTn रेजिस्टर description in the datasheet क्रम details. */
	hoff2 = f->o_width - f->width - f->offs_h;
	voff2 = f->o_height - f->height - f->offs_v;
	cfg = (hoff2 << 16) | voff2;
	ग_लिखोl(cfg, fimc->regs + FIMC_REG_CIWDOFST2);
पूर्ण

पूर्णांक fimc_hw_set_camera_type(काष्ठा fimc_dev *fimc,
			    काष्ठा fimc_source_info *source)
अणु
	काष्ठा fimc_vid_cap *vid_cap = &fimc->vid_cap;
	u32 csis_data_alignment = 32;
	u32 cfg, पंचांगp;

	cfg = पढ़ोl(fimc->regs + FIMC_REG_CIGCTRL);

	/* Select ITU B पूर्णांकerface, disable Writeback path and test pattern. */
	cfg &= ~(FIMC_REG_CIGCTRL_TESTPAT_MASK | FIMC_REG_CIGCTRL_SELCAM_ITU_A |
		FIMC_REG_CIGCTRL_SELCAM_MIPI | FIMC_REG_CIGCTRL_CAMIF_SELWB |
		FIMC_REG_CIGCTRL_SELCAM_MIPI_A | FIMC_REG_CIGCTRL_CAM_JPEG |
		FIMC_REG_CIGCTRL_SELWB_A);

	चयन (source->fimc_bus_type) अणु
	हाल FIMC_BUS_TYPE_MIPI_CSI2:
		cfg |= FIMC_REG_CIGCTRL_SELCAM_MIPI;

		अगर (source->mux_id == 0)
			cfg |= FIMC_REG_CIGCTRL_SELCAM_MIPI_A;

		/* TODO: add reमुख्यing supported क्रमmats. */
		चयन (vid_cap->ci_fmt.code) अणु
		हाल MEDIA_BUS_FMT_VYUY8_2X8:
			पंचांगp = FIMC_REG_CSIIMGFMT_YCBCR422_8BIT;
			अवरोध;
		हाल MEDIA_BUS_FMT_JPEG_1X8:
		हाल MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8:
			पंचांगp = FIMC_REG_CSIIMGFMT_USER(1);
			cfg |= FIMC_REG_CIGCTRL_CAM_JPEG;
			अवरोध;
		शेष:
			v4l2_err(&vid_cap->ve.vdev,
				 "Not supported camera pixel format: %#x\n",
				 vid_cap->ci_fmt.code);
			वापस -EINVAL;
		पूर्ण
		पंचांगp |= (csis_data_alignment == 32) << 8;

		ग_लिखोl(पंचांगp, fimc->regs + FIMC_REG_CSIIMGFMT);
		अवरोध;
	हाल FIMC_BUS_TYPE_ITU_601...FIMC_BUS_TYPE_ITU_656:
		अगर (source->mux_id == 0) /* ITU-A, ITU-B: 0, 1 */
			cfg |= FIMC_REG_CIGCTRL_SELCAM_ITU_A;
		अगर (vid_cap->ci_fmt.code == MEDIA_BUS_FMT_JPEG_1X8)
			cfg |= FIMC_REG_CIGCTRL_CAM_JPEG;
		अवरोध;
	हाल FIMC_BUS_TYPE_LCD_WRITEBACK_A:
		cfg |= FIMC_REG_CIGCTRL_CAMIF_SELWB;
		fallthrough;
	हाल FIMC_BUS_TYPE_ISP_WRITEBACK:
		अगर (fimc->variant->has_isp_wb)
			cfg |= FIMC_REG_CIGCTRL_CAMIF_SELWB;
		अन्यथा
			WARN_ONCE(1, "ISP Writeback input is not supported\n");
		अवरोध;
	शेष:
		v4l2_err(&vid_cap->ve.vdev,
			 "Invalid FIMC bus type selected: %d\n",
			 source->fimc_bus_type);
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(cfg, fimc->regs + FIMC_REG_CIGCTRL);

	वापस 0;
पूर्ण

व्योम fimc_hw_clear_irq(काष्ठा fimc_dev *dev)
अणु
	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_CIGCTRL);
	cfg |= FIMC_REG_CIGCTRL_IRQ_CLR;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CIGCTRL);
पूर्ण

व्योम fimc_hw_enable_scaler(काष्ठा fimc_dev *dev, bool on)
अणु
	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_CISCCTRL);
	अगर (on)
		cfg |= FIMC_REG_CISCCTRL_SCALERSTART;
	अन्यथा
		cfg &= ~FIMC_REG_CISCCTRL_SCALERSTART;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_CISCCTRL);
पूर्ण

व्योम fimc_hw_activate_input_dma(काष्ठा fimc_dev *dev, bool on)
अणु
	u32 cfg = पढ़ोl(dev->regs + FIMC_REG_MSCTRL);
	अगर (on)
		cfg |= FIMC_REG_MSCTRL_ENVID;
	अन्यथा
		cfg &= ~FIMC_REG_MSCTRL_ENVID;
	ग_लिखोl(cfg, dev->regs + FIMC_REG_MSCTRL);
पूर्ण

/* Return an index to the buffer actually being written. */
s32 fimc_hw_get_frame_index(काष्ठा fimc_dev *dev)
अणु
	s32 reg;

	अगर (dev->drv_data->cistatus2) अणु
		reg = पढ़ोl(dev->regs + FIMC_REG_CISTATUS2) & 0x3f;
		वापस reg - 1;
	पूर्ण

	reg = पढ़ोl(dev->regs + FIMC_REG_CISTATUS);

	वापस (reg & FIMC_REG_CISTATUS_FRAMECNT_MASK) >>
		FIMC_REG_CISTATUS_FRAMECNT_SHIFT;
पूर्ण

/* Return an index to the buffer being written previously. */
s32 fimc_hw_get_prev_frame_index(काष्ठा fimc_dev *dev)
अणु
	s32 reg;

	अगर (!dev->drv_data->cistatus2)
		वापस -1;

	reg = पढ़ोl(dev->regs + FIMC_REG_CISTATUS2);
	वापस ((reg >> 7) & 0x3f) - 1;
पूर्ण

/* Locking: the caller holds fimc->slock */
व्योम fimc_activate_capture(काष्ठा fimc_ctx *ctx)
अणु
	fimc_hw_enable_scaler(ctx->fimc_dev, ctx->scaler.enabled);
	fimc_hw_enable_capture(ctx);
पूर्ण

व्योम fimc_deactivate_capture(काष्ठा fimc_dev *fimc)
अणु
	fimc_hw_en_lastirq(fimc, true);
	fimc_hw_disable_capture(fimc);
	fimc_hw_enable_scaler(fimc, false);
	fimc_hw_en_lastirq(fimc, false);
पूर्ण

पूर्णांक fimc_hw_camblk_cfg_ग_लिखोback(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा regmap *map = fimc->sysreg;
	अचिन्हित पूर्णांक mask, val, camblk_cfg;
	पूर्णांक ret;

	अगर (map == शून्य)
		वापस 0;

	ret = regmap_पढ़ो(map, SYSREG_CAMBLK, &camblk_cfg);
	अगर (ret < 0 || ((camblk_cfg & 0x00700000) >> 20 != 0x3))
		वापस ret;

	अगर (!WARN(fimc->id >= 3, "not supported id: %d\n", fimc->id))
		val = 0x1 << (fimc->id + 20);
	अन्यथा
		val = 0;

	mask = SYSREG_CAMBLK_FIFORST_ISP | SYSREG_CAMBLK_ISPWB_FULL_EN;
	ret = regmap_update_bits(map, SYSREG_CAMBLK, mask, val);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 2000);

	val |= SYSREG_CAMBLK_FIFORST_ISP;
	ret = regmap_update_bits(map, SYSREG_CAMBLK, mask, val);
	अगर (ret < 0)
		वापस ret;

	mask = SYSREG_ISPBLK_FIFORST_CAM_BLK;
	ret = regmap_update_bits(map, SYSREG_ISPBLK, mask, ~mask);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 2000);

	वापस regmap_update_bits(map, SYSREG_ISPBLK, mask, mask);
पूर्ण
