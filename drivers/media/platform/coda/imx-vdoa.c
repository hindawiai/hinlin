<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i.MX6 Video Data Order Adapter (VDOA)
 *
 * Copyright (C) 2014 Philipp Zabel
 * Copyright (C) 2016 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>

#समावेश "imx-vdoa.h"

#घोषणा VDOA_NAME "imx-vdoa"

#घोषणा VDOAC		0x00
#घोषणा VDOASRR		0x04
#घोषणा VDOAIE		0x08
#घोषणा VDOAIST		0x0c
#घोषणा VDOAFP		0x10
#घोषणा VDOAIEBA00	0x14
#घोषणा VDOAIEBA01	0x18
#घोषणा VDOAIEBA02	0x1c
#घोषणा VDOAIEBA10	0x20
#घोषणा VDOAIEBA11	0x24
#घोषणा VDOAIEBA12	0x28
#घोषणा VDOASL		0x2c
#घोषणा VDOAIUBO	0x30
#घोषणा VDOAVEBA0	0x34
#घोषणा VDOAVEBA1	0x38
#घोषणा VDOAVEBA2	0x3c
#घोषणा VDOAVUBO	0x40
#घोषणा VDOASR		0x44

#घोषणा VDOAC_ISEL		BIT(6)
#घोषणा VDOAC_PFS		BIT(5)
#घोषणा VDOAC_SO		BIT(4)
#घोषणा VDOAC_SYNC		BIT(3)
#घोषणा VDOAC_NF		BIT(2)
#घोषणा VDOAC_BNDM_MASK		0x3
#घोषणा VDOAC_BAND_HEIGHT_8	0x0
#घोषणा VDOAC_BAND_HEIGHT_16	0x1
#घोषणा VDOAC_BAND_HEIGHT_32	0x2

#घोषणा VDOASRR_START		BIT(1)
#घोषणा VDOASRR_SWRST		BIT(0)

#घोषणा VDOAIE_EITERR		BIT(1)
#घोषणा VDOAIE_EIEOT		BIT(0)

#घोषणा VDOAIST_TERR		BIT(1)
#घोषणा VDOAIST_EOT		BIT(0)

#घोषणा VDOAFP_FH_MASK		(0x1fff << 16)
#घोषणा VDOAFP_FW_MASK		(0x3fff)

#घोषणा VDOASL_VSLY_MASK	(0x3fff << 16)
#घोषणा VDOASL_ISLY_MASK	(0x7fff)

#घोषणा VDOASR_ERRW		BIT(4)
#घोषणा VDOASR_EOB		BIT(3)
#घोषणा VDOASR_CURRENT_FRAME	(0x3 << 1)
#घोषणा VDOASR_CURRENT_BUFFER	BIT(1)

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

काष्ठा vकरोa_data अणु
	काष्ठा vकरोa_ctx		*curr_ctx;
	काष्ठा device		*dev;
	काष्ठा clk		*vकरोa_clk;
	व्योम __iomem		*regs;
पूर्ण;

काष्ठा vकरोa_q_data अणु
	अचिन्हित पूर्णांक	width;
	अचिन्हित पूर्णांक	height;
	अचिन्हित पूर्णांक	bytesperline;
	अचिन्हित पूर्णांक	sizeimage;
	u32		pixelक्रमmat;
पूर्ण;

काष्ठा vकरोa_ctx अणु
	काष्ठा vकरोa_data	*vकरोa;
	काष्ठा completion	completion;
	काष्ठा vकरोa_q_data	q_data[2];
	अचिन्हित पूर्णांक		submitted_job;
	अचिन्हित पूर्णांक		completed_job;
पूर्ण;

अटल irqवापस_t vकरोa_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vकरोa_data *vकरोa = data;
	काष्ठा vकरोa_ctx *curr_ctx;
	u32 val;

	/* Disable पूर्णांकerrupts */
	ग_लिखोl(0, vकरोa->regs + VDOAIE);

	curr_ctx = vकरोa->curr_ctx;
	अगर (!curr_ctx) अणु
		dev_warn(vकरोa->dev,
			"Instance released before the end of transaction\n");
		वापस IRQ_HANDLED;
	पूर्ण

	val = पढ़ोl(vकरोa->regs + VDOAIST);
	ग_लिखोl(val, vकरोa->regs + VDOAIST);
	अगर (val & VDOAIST_TERR) अणु
		val = पढ़ोl(vकरोa->regs + VDOASR) & VDOASR_ERRW;
		dev_err(vकरोa->dev, "AXI %s error\n", val ? "write" : "read");
	पूर्ण अन्यथा अगर (!(val & VDOAIST_EOT)) अणु
		dev_warn(vकरोa->dev, "Spurious interrupt\n");
	पूर्ण
	curr_ctx->completed_job++;
	complete(&curr_ctx->completion);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक vकरोa_रुको_क्रम_completion(काष्ठा vकरोa_ctx *ctx)
अणु
	काष्ठा vकरोa_data *vकरोa = ctx->vकरोa;

	अगर (ctx->submitted_job == ctx->completed_job)
		वापस 0;

	अगर (!रुको_क्रम_completion_समयout(&ctx->completion,
					 msecs_to_jअगरfies(300))) अणु
		dev_err(vकरोa->dev,
			"Timeout waiting for transfer result\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vकरोa_रुको_क्रम_completion);

व्योम vकरोa_device_run(काष्ठा vकरोa_ctx *ctx, dma_addr_t dst, dma_addr_t src)
अणु
	काष्ठा vकरोa_q_data *src_q_data, *dst_q_data;
	काष्ठा vकरोa_data *vकरोa = ctx->vकरोa;
	u32 val;

	अगर (vकरोa->curr_ctx)
		vकरोa_रुको_क्रम_completion(vकरोa->curr_ctx);

	vकरोa->curr_ctx = ctx;

	reinit_completion(&ctx->completion);
	ctx->submitted_job++;

	src_q_data = &ctx->q_data[V4L2_M2M_SRC];
	dst_q_data = &ctx->q_data[V4L2_M2M_DST];

	/* Progressive, no sync, 1 frame per run */
	अगर (dst_q_data->pixelक्रमmat == V4L2_PIX_FMT_YUYV)
		val = VDOAC_PFS;
	अन्यथा
		val = 0;
	ग_लिखोl(val, vकरोa->regs + VDOAC);

	ग_लिखोl(dst_q_data->height << 16 | dst_q_data->width,
	       vकरोa->regs + VDOAFP);

	val = dst;
	ग_लिखोl(val, vकरोa->regs + VDOAIEBA00);

	ग_लिखोl(src_q_data->bytesperline << 16 | dst_q_data->bytesperline,
	       vकरोa->regs + VDOASL);

	अगर (dst_q_data->pixelक्रमmat == V4L2_PIX_FMT_NV12 ||
	    dst_q_data->pixelक्रमmat == V4L2_PIX_FMT_NV21)
		val = dst_q_data->bytesperline * dst_q_data->height;
	अन्यथा
		val = 0;
	ग_लिखोl(val, vकरोa->regs + VDOAIUBO);

	val = src;
	ग_लिखोl(val, vकरोa->regs + VDOAVEBA0);
	val = round_up(src_q_data->bytesperline * src_q_data->height, 4096);
	ग_लिखोl(val, vकरोa->regs + VDOAVUBO);

	/* Enable पूर्णांकerrupts and start transfer */
	ग_लिखोl(VDOAIE_EITERR | VDOAIE_EIEOT, vकरोa->regs + VDOAIE);
	ग_लिखोl(VDOASRR_START, vकरोa->regs + VDOASRR);
पूर्ण
EXPORT_SYMBOL(vकरोa_device_run);

काष्ठा vकरोa_ctx *vकरोa_context_create(काष्ठा vकरोa_data *vकरोa)
अणु
	काष्ठा vकरोa_ctx *ctx;
	पूर्णांक err;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	err = clk_prepare_enable(vकरोa->vकरोa_clk);
	अगर (err) अणु
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण

	init_completion(&ctx->completion);
	ctx->vकरोa = vकरोa;

	वापस ctx;
पूर्ण
EXPORT_SYMBOL(vकरोa_context_create);

व्योम vकरोa_context_destroy(काष्ठा vकरोa_ctx *ctx)
अणु
	काष्ठा vकरोa_data *vकरोa = ctx->vकरोa;

	अगर (vकरोa->curr_ctx == ctx) अणु
		vकरोa_रुको_क्रम_completion(vकरोa->curr_ctx);
		vकरोa->curr_ctx = शून्य;
	पूर्ण

	clk_disable_unprepare(vकरोa->vकरोa_clk);
	kमुक्त(ctx);
पूर्ण
EXPORT_SYMBOL(vकरोa_context_destroy);

पूर्णांक vकरोa_context_configure(काष्ठा vकरोa_ctx *ctx,
			   अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
			   u32 pixelक्रमmat)
अणु
	काष्ठा vकरोa_q_data *src_q_data;
	काष्ठा vकरोa_q_data *dst_q_data;

	अगर (width < 16 || width  > 8192 || width % 16 != 0 ||
	    height < 16 || height > 4096 || height % 16 != 0)
		वापस -EINVAL;

	अगर (pixelक्रमmat != V4L2_PIX_FMT_YUYV &&
	    pixelक्रमmat != V4L2_PIX_FMT_NV12)
		वापस -EINVAL;

	/* If no context is passed, only check अगर the क्रमmat is valid */
	अगर (!ctx)
		वापस 0;

	src_q_data = &ctx->q_data[V4L2_M2M_SRC];
	dst_q_data = &ctx->q_data[V4L2_M2M_DST];

	src_q_data->width = width;
	src_q_data->height = height;
	src_q_data->bytesperline = width;
	src_q_data->sizeimage =
		round_up(src_q_data->bytesperline * height, 4096) +
		src_q_data->bytesperline * height / 2;

	dst_q_data->width = width;
	dst_q_data->height = height;
	dst_q_data->pixelक्रमmat = pixelक्रमmat;
	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
		dst_q_data->bytesperline = width * 2;
		dst_q_data->sizeimage = dst_q_data->bytesperline * height;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
	शेष:
		dst_q_data->bytesperline = width;
		dst_q_data->sizeimage =
			dst_q_data->bytesperline * height * 3 / 2;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vकरोa_context_configure);

अटल पूर्णांक vकरोa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vकरोa_data *vकरोa;
	काष्ठा resource *res;
	पूर्णांक ret;

	dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	vकरोa = devm_kzalloc(&pdev->dev, माप(*vकरोa), GFP_KERNEL);
	अगर (!vकरोa)
		वापस -ENOMEM;

	vकरोa->dev = &pdev->dev;

	vकरोa->vकरोa_clk = devm_clk_get(vकरोa->dev, शून्य);
	अगर (IS_ERR(vकरोa->vकरोa_clk)) अणु
		dev_err(vकरोa->dev, "Failed to get clock\n");
		वापस PTR_ERR(vकरोa->vकरोa_clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	vकरोa->regs = devm_ioremap_resource(vकरोa->dev, res);
	अगर (IS_ERR(vकरोa->regs))
		वापस PTR_ERR(vकरोa->regs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res)
		वापस -EINVAL;
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, res->start, शून्य,
					vकरोa_irq_handler, IRQF_ONESHOT,
					"vdoa", vकरोa);
	अगर (ret < 0) अणु
		dev_err(vकरोa->dev, "Failed to get irq\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, vकरोa);

	वापस 0;
पूर्ण

अटल पूर्णांक vकरोa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vकरोa_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-vdoa" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vकरोa_dt_ids);

अटल काष्ठा platक्रमm_driver vकरोa_driver = अणु
	.probe		= vकरोa_probe,
	.हटाओ		= vकरोa_हटाओ,
	.driver		= अणु
		.name	= VDOA_NAME,
		.of_match_table = vकरोa_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vकरोa_driver);

MODULE_DESCRIPTION("Video Data Order Adapter");
MODULE_AUTHOR("Philipp Zabel <philipp.zabel@gmail.com>");
MODULE_ALIAS("platform:imx-vdoa");
MODULE_LICENSE("GPL");
