<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cedrus VPU driver
 *
 * Copyright (C) 2016 Florent Revest <florent.revest@मुक्त-electrons.com>
 * Copyright (C) 2018 Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 * Copyright (C) 2018 Bootlin
 *
 * Based on the vim2m driver, that is:
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/of_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/soc/sunxi/sunxi_sram.h>

#समावेश <media/videobuf2-core.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "cedrus.h"
#समावेश "cedrus_hw.h"
#समावेश "cedrus_regs.h"

पूर्णांक cedrus_engine_enable(काष्ठा cedrus_ctx *ctx, क्रमागत cedrus_codec codec)
अणु
	u32 reg = 0;

	/*
	 * FIXME: This is only valid on 32-bits DDR's, we should test
	 * it on the A13/A33.
	 */
	reg |= VE_MODE_REC_WR_MODE_2MB;
	reg |= VE_MODE_DDR_MODE_BW_128;

	चयन (codec) अणु
	हाल CEDRUS_CODEC_MPEG2:
		reg |= VE_MODE_DEC_MPEG;
		अवरोध;

	/* H.264 and VP8 both use the same decoding mode bit. */
	हाल CEDRUS_CODEC_H264:
	हाल CEDRUS_CODEC_VP8:
		reg |= VE_MODE_DEC_H264;
		अवरोध;

	हाल CEDRUS_CODEC_H265:
		reg |= VE_MODE_DEC_H265;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->src_fmt.width == 4096)
		reg |= VE_MODE_PIC_WIDTH_IS_4096;
	अगर (ctx->src_fmt.width > 2048)
		reg |= VE_MODE_PIC_WIDTH_MORE_2048;

	cedrus_ग_लिखो(ctx->dev, VE_MODE, reg);

	वापस 0;
पूर्ण

व्योम cedrus_engine_disable(काष्ठा cedrus_dev *dev)
अणु
	cedrus_ग_लिखो(dev, VE_MODE, VE_MODE_DISABLED);
पूर्ण

व्योम cedrus_dst_क्रमmat_set(काष्ठा cedrus_dev *dev,
			   काष्ठा v4l2_pix_क्रमmat *fmt)
अणु
	अचिन्हित पूर्णांक width = fmt->width;
	अचिन्हित पूर्णांक height = fmt->height;
	u32 chroma_size;
	u32 reg;

	चयन (fmt->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
		chroma_size = ALIGN(width, 16) * ALIGN(height, 16) / 2;

		reg = VE_PRIMARY_OUT_FMT_NV12;
		cedrus_ग_लिखो(dev, VE_PRIMARY_OUT_FMT, reg);

		reg = chroma_size / 2;
		cedrus_ग_लिखो(dev, VE_PRIMARY_CHROMA_BUF_LEN, reg);

		reg = VE_PRIMARY_FB_LINE_STRIDE_LUMA(ALIGN(width, 16)) |
		      VE_PRIMARY_FB_LINE_STRIDE_CHROMA(ALIGN(width, 16) / 2);
		cedrus_ग_लिखो(dev, VE_PRIMARY_FB_LINE_STRIDE, reg);

		अवरोध;
	हाल V4L2_PIX_FMT_SUNXI_TILED_NV12:
	शेष:
		reg = VE_PRIMARY_OUT_FMT_TILED_32_NV12;
		cedrus_ग_लिखो(dev, VE_PRIMARY_OUT_FMT, reg);

		reg = VE_SECONDARY_OUT_FMT_TILED_32_NV12;
		cedrus_ग_लिखो(dev, VE_CHROMA_BUF_LEN, reg);

		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t cedrus_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cedrus_dev *dev = data;
	काष्ठा cedrus_ctx *ctx;
	क्रमागत vb2_buffer_state state;
	क्रमागत cedrus_irq_status status;

	ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);
	अगर (!ctx) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Instance released before the end of transaction\n");
		वापस IRQ_NONE;
	पूर्ण

	status = dev->dec_ops[ctx->current_codec]->irq_status(ctx);
	अगर (status == CEDRUS_IRQ_NONE)
		वापस IRQ_NONE;

	dev->dec_ops[ctx->current_codec]->irq_disable(ctx);
	dev->dec_ops[ctx->current_codec]->irq_clear(ctx);

	अगर (status == CEDRUS_IRQ_ERROR)
		state = VB2_BUF_STATE_ERROR;
	अन्यथा
		state = VB2_BUF_STATE_DONE;

	v4l2_m2m_buf_करोne_and_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx,
					 state);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक cedrus_hw_suspend(काष्ठा device *device)
अणु
	काष्ठा cedrus_dev *dev = dev_get_drvdata(device);

	reset_control_निश्चित(dev->rstc);

	clk_disable_unprepare(dev->ram_clk);
	clk_disable_unprepare(dev->mod_clk);
	clk_disable_unprepare(dev->ahb_clk);

	वापस 0;
पूर्ण

पूर्णांक cedrus_hw_resume(काष्ठा device *device)
अणु
	काष्ठा cedrus_dev *dev = dev_get_drvdata(device);
	पूर्णांक ret;

	ret = clk_prepare_enable(dev->ahb_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable AHB clock\n");

		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dev->mod_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable MOD clock\n");

		जाओ err_ahb_clk;
	पूर्ण

	ret = clk_prepare_enable(dev->ram_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable RAM clock\n");

		जाओ err_mod_clk;
	पूर्ण

	ret = reset_control_reset(dev->rstc);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to apply reset\n");

		जाओ err_ram_clk;
	पूर्ण

	वापस 0;

err_ram_clk:
	clk_disable_unprepare(dev->ram_clk);
err_mod_clk:
	clk_disable_unprepare(dev->mod_clk);
err_ahb_clk:
	clk_disable_unprepare(dev->ahb_clk);

	वापस ret;
पूर्ण

पूर्णांक cedrus_hw_probe(काष्ठा cedrus_dev *dev)
अणु
	स्थिर काष्ठा cedrus_variant *variant;
	पूर्णांक irq_dec;
	पूर्णांक ret;

	variant = of_device_get_match_data(dev->dev);
	अगर (!variant)
		वापस -EINVAL;

	dev->capabilities = variant->capabilities;

	irq_dec = platक्रमm_get_irq(dev->pdev, 0);
	अगर (irq_dec <= 0)
		वापस irq_dec;
	ret = devm_request_irq(dev->dev, irq_dec, cedrus_irq,
			       0, dev_name(dev->dev), dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to request IRQ\n");

		वापस ret;
	पूर्ण

	ret = of_reserved_mem_device_init(dev->dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(dev->dev, "Failed to reserve memory\n");

		वापस ret;
	पूर्ण

	ret = sunxi_sram_claim(dev->dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to claim SRAM\n");

		जाओ err_mem;
	पूर्ण

	dev->ahb_clk = devm_clk_get(dev->dev, "ahb");
	अगर (IS_ERR(dev->ahb_clk)) अणु
		dev_err(dev->dev, "Failed to get AHB clock\n");

		ret = PTR_ERR(dev->ahb_clk);
		जाओ err_sram;
	पूर्ण

	dev->mod_clk = devm_clk_get(dev->dev, "mod");
	अगर (IS_ERR(dev->mod_clk)) अणु
		dev_err(dev->dev, "Failed to get MOD clock\n");

		ret = PTR_ERR(dev->mod_clk);
		जाओ err_sram;
	पूर्ण

	dev->ram_clk = devm_clk_get(dev->dev, "ram");
	अगर (IS_ERR(dev->ram_clk)) अणु
		dev_err(dev->dev, "Failed to get RAM clock\n");

		ret = PTR_ERR(dev->ram_clk);
		जाओ err_sram;
	पूर्ण

	dev->rstc = devm_reset_control_get(dev->dev, शून्य);
	अगर (IS_ERR(dev->rstc)) अणु
		dev_err(dev->dev, "Failed to get reset control\n");

		ret = PTR_ERR(dev->rstc);
		जाओ err_sram;
	पूर्ण

	dev->base = devm_platक्रमm_ioremap_resource(dev->pdev, 0);
	अगर (IS_ERR(dev->base)) अणु
		dev_err(dev->dev, "Failed to map registers\n");

		ret = PTR_ERR(dev->base);
		जाओ err_sram;
	पूर्ण

	ret = clk_set_rate(dev->mod_clk, variant->mod_rate);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to set clock rate\n");

		जाओ err_sram;
	पूर्ण

	pm_runसमय_enable(dev->dev);
	अगर (!pm_runसमय_enabled(dev->dev)) अणु
		ret = cedrus_hw_resume(dev->dev);
		अगर (ret)
			जाओ err_pm;
	पूर्ण

	वापस 0;

err_pm:
	pm_runसमय_disable(dev->dev);
err_sram:
	sunxi_sram_release(dev->dev);
err_mem:
	of_reserved_mem_device_release(dev->dev);

	वापस ret;
पूर्ण

व्योम cedrus_hw_हटाओ(काष्ठा cedrus_dev *dev)
अणु
	pm_runसमय_disable(dev->dev);
	अगर (!pm_runसमय_status_suspended(dev->dev))
		cedrus_hw_suspend(dev->dev);

	sunxi_sram_release(dev->dev);

	of_reserved_mem_device_release(dev->dev);
पूर्ण
