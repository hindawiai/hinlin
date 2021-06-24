<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors:
 *	YoungJun Cho <yj44.cho@samsung.com>
 *	Eunchul Kim <chulspro.kim@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sizes.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_ipp.h"
#समावेश "regs-rotator.h"

/*
 * Rotator supports image crop/rotator and input/output DMA operations.
 * input DMA पढ़ोs image data from the memory.
 * output DMA ग_लिखोs image data to memory.
 */

#घोषणा ROTATOR_AUTOSUSPEND_DELAY	2000

#घोषणा rot_पढ़ो(offset)	पढ़ोl(rot->regs + (offset))
#घोषणा rot_ग_लिखो(cfg, offset)	ग_लिखोl(cfg, rot->regs + (offset))

क्रमागत rot_irq_status अणु
	ROT_IRQ_STATUS_COMPLETE	= 8,
	ROT_IRQ_STATUS_ILLEGAL	= 9,
पूर्ण;

काष्ठा rot_variant अणु
	स्थिर काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats;
	अचिन्हित पूर्णांक	num_क्रमmats;
पूर्ण;

/*
 * A काष्ठाure of rotator context.
 * @ippdrv: prepare initialization using ippdrv.
 * @regs: memory mapped io रेजिस्टरs.
 * @घड़ी: rotator gate घड़ी.
 * @limit_tbl: limitation of rotator.
 * @irq: irq number.
 */
काष्ठा rot_context अणु
	काष्ठा exynos_drm_ipp ipp;
	काष्ठा drm_device *drm_dev;
	व्योम		*dma_priv;
	काष्ठा device	*dev;
	व्योम __iomem	*regs;
	काष्ठा clk	*घड़ी;
	स्थिर काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats;
	अचिन्हित पूर्णांक	num_क्रमmats;
	काष्ठा exynos_drm_ipp_task	*task;
पूर्ण;

अटल व्योम rotator_reg_set_irq(काष्ठा rot_context *rot, bool enable)
अणु
	u32 val = rot_पढ़ो(ROT_CONFIG);

	अगर (enable == true)
		val |= ROT_CONFIG_IRQ;
	अन्यथा
		val &= ~ROT_CONFIG_IRQ;

	rot_ग_लिखो(val, ROT_CONFIG);
पूर्ण

अटल क्रमागत rot_irq_status rotator_reg_get_irq_status(काष्ठा rot_context *rot)
अणु
	u32 val = rot_पढ़ो(ROT_STATUS);

	val = ROT_STATUS_IRQ(val);

	अगर (val == ROT_STATUS_IRQ_VAL_COMPLETE)
		वापस ROT_IRQ_STATUS_COMPLETE;

	वापस ROT_IRQ_STATUS_ILLEGAL;
पूर्ण

अटल irqवापस_t rotator_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा rot_context *rot = arg;
	क्रमागत rot_irq_status irq_status;
	u32 val;

	/* Get execution result */
	irq_status = rotator_reg_get_irq_status(rot);

	/* clear status */
	val = rot_पढ़ो(ROT_STATUS);
	val |= ROT_STATUS_IRQ_PENDING((u32)irq_status);
	rot_ग_लिखो(val, ROT_STATUS);

	अगर (rot->task) अणु
		काष्ठा exynos_drm_ipp_task *task = rot->task;

		rot->task = शून्य;
		pm_runसमय_mark_last_busy(rot->dev);
		pm_runसमय_put_स्वतःsuspend(rot->dev);
		exynos_drm_ipp_task_करोne(task,
			irq_status == ROT_IRQ_STATUS_COMPLETE ? 0 : -EINVAL);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rotator_src_set_fmt(काष्ठा rot_context *rot, u32 fmt)
अणु
	u32 val;

	val = rot_पढ़ो(ROT_CONTROL);
	val &= ~ROT_CONTROL_FMT_MASK;

	चयन (fmt) अणु
	हाल DRM_FORMAT_NV12:
		val |= ROT_CONTROL_FMT_YCBCR420_2P;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		val |= ROT_CONTROL_FMT_RGB888;
		अवरोध;
	पूर्ण

	rot_ग_लिखो(val, ROT_CONTROL);
पूर्ण

अटल व्योम rotator_src_set_buf(काष्ठा rot_context *rot,
				काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	u32 val;

	/* Set buffer size configuration */
	val = ROT_SET_BUF_SIZE_H(buf->buf.height) |
	      ROT_SET_BUF_SIZE_W(buf->buf.pitch[0] / buf->क्रमmat->cpp[0]);
	rot_ग_लिखो(val, ROT_SRC_BUF_SIZE);

	/* Set crop image position configuration */
	val = ROT_CROP_POS_Y(buf->rect.y) | ROT_CROP_POS_X(buf->rect.x);
	rot_ग_लिखो(val, ROT_SRC_CROP_POS);
	val = ROT_SRC_CROP_SIZE_H(buf->rect.h) |
	      ROT_SRC_CROP_SIZE_W(buf->rect.w);
	rot_ग_लिखो(val, ROT_SRC_CROP_SIZE);

	/* Set buffer DMA address */
	rot_ग_लिखो(buf->dma_addr[0], ROT_SRC_BUF_ADDR(0));
	rot_ग_लिखो(buf->dma_addr[1], ROT_SRC_BUF_ADDR(1));
पूर्ण

अटल व्योम rotator_dst_set_transf(काष्ठा rot_context *rot,
				   अचिन्हित पूर्णांक rotation)
अणु
	u32 val;

	/* Set transक्रमm configuration */
	val = rot_पढ़ो(ROT_CONTROL);
	val &= ~ROT_CONTROL_FLIP_MASK;

	अगर (rotation & DRM_MODE_REFLECT_X)
		val |= ROT_CONTROL_FLIP_VERTICAL;
	अगर (rotation & DRM_MODE_REFLECT_Y)
		val |= ROT_CONTROL_FLIP_HORIZONTAL;

	val &= ~ROT_CONTROL_ROT_MASK;

	अगर (rotation & DRM_MODE_ROTATE_90)
		val |= ROT_CONTROL_ROT_90;
	अन्यथा अगर (rotation & DRM_MODE_ROTATE_180)
		val |= ROT_CONTROL_ROT_180;
	अन्यथा अगर (rotation & DRM_MODE_ROTATE_270)
		val |= ROT_CONTROL_ROT_270;

	rot_ग_लिखो(val, ROT_CONTROL);
पूर्ण

अटल व्योम rotator_dst_set_buf(काष्ठा rot_context *rot,
				काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	u32 val;

	/* Set buffer size configuration */
	val = ROT_SET_BUF_SIZE_H(buf->buf.height) |
	      ROT_SET_BUF_SIZE_W(buf->buf.pitch[0] / buf->क्रमmat->cpp[0]);
	rot_ग_लिखो(val, ROT_DST_BUF_SIZE);

	/* Set crop image position configuration */
	val = ROT_CROP_POS_Y(buf->rect.y) | ROT_CROP_POS_X(buf->rect.x);
	rot_ग_लिखो(val, ROT_DST_CROP_POS);

	/* Set buffer DMA address */
	rot_ग_लिखो(buf->dma_addr[0], ROT_DST_BUF_ADDR(0));
	rot_ग_लिखो(buf->dma_addr[1], ROT_DST_BUF_ADDR(1));
पूर्ण

अटल व्योम rotator_start(काष्ठा rot_context *rot)
अणु
	u32 val;

	/* Set पूर्णांकerrupt enable */
	rotator_reg_set_irq(rot, true);

	val = rot_पढ़ो(ROT_CONTROL);
	val |= ROT_CONTROL_START;
	rot_ग_लिखो(val, ROT_CONTROL);
पूर्ण

अटल पूर्णांक rotator_commit(काष्ठा exynos_drm_ipp *ipp,
			  काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा rot_context *rot =
			container_of(ipp, काष्ठा rot_context, ipp);

	pm_runसमय_get_sync(rot->dev);
	rot->task = task;

	rotator_src_set_fmt(rot, task->src.buf.fourcc);
	rotator_src_set_buf(rot, &task->src);
	rotator_dst_set_transf(rot, task->transक्रमm.rotation);
	rotator_dst_set_buf(rot, &task->dst);
	rotator_start(rot);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा exynos_drm_ipp_funcs ipp_funcs = अणु
	.commit = rotator_commit,
पूर्ण;

अटल पूर्णांक rotator_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा rot_context *rot = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_ipp *ipp = &rot->ipp;

	rot->drm_dev = drm_dev;
	ipp->drm_dev = drm_dev;
	exynos_drm_रेजिस्टर_dma(drm_dev, dev, &rot->dma_priv);

	exynos_drm_ipp_रेजिस्टर(dev, ipp, &ipp_funcs,
			   DRM_EXYNOS_IPP_CAP_CROP | DRM_EXYNOS_IPP_CAP_ROTATE,
			   rot->क्रमmats, rot->num_क्रमmats, "rotator");

	dev_info(dev, "The exynos rotator has been probed successfully\n");

	वापस 0;
पूर्ण

अटल व्योम rotator_unbind(काष्ठा device *dev, काष्ठा device *master,
			व्योम *data)
अणु
	काष्ठा rot_context *rot = dev_get_drvdata(dev);
	काष्ठा exynos_drm_ipp *ipp = &rot->ipp;

	exynos_drm_ipp_unरेजिस्टर(dev, ipp);
	exynos_drm_unरेजिस्टर_dma(rot->drm_dev, rot->dev, &rot->dma_priv);
पूर्ण

अटल स्थिर काष्ठा component_ops rotator_component_ops = अणु
	.bind	= rotator_bind,
	.unbind = rotator_unbind,
पूर्ण;

अटल पूर्णांक rotator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource	*regs_res;
	काष्ठा rot_context *rot;
	स्थिर काष्ठा rot_variant *variant;
	पूर्णांक irq;
	पूर्णांक ret;

	rot = devm_kzalloc(dev, माप(*rot), GFP_KERNEL);
	अगर (!rot)
		वापस -ENOMEM;

	variant = of_device_get_match_data(dev);
	rot->क्रमmats = variant->क्रमmats;
	rot->num_क्रमmats = variant->num_क्रमmats;
	rot->dev = dev;
	regs_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rot->regs = devm_ioremap_resource(dev, regs_res);
	अगर (IS_ERR(rot->regs))
		वापस PTR_ERR(rot->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, rotator_irq_handler, 0, dev_name(dev),
			       rot);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	rot->घड़ी = devm_clk_get(dev, "rotator");
	अगर (IS_ERR(rot->घड़ी)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(rot->घड़ी);
	पूर्ण

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, ROTATOR_AUTOSUSPEND_DELAY);
	pm_runसमय_enable(dev);
	platक्रमm_set_drvdata(pdev, rot);

	ret = component_add(dev, &rotator_component_ops);
	अगर (ret)
		जाओ err_component;

	वापस 0;

err_component:
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक rotator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	component_del(dev, &rotator_component_ops);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rotator_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rot_context *rot = dev_get_drvdata(dev);

	clk_disable_unprepare(rot->घड़ी);
	वापस 0;
पूर्ण

अटल पूर्णांक rotator_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rot_context *rot = dev_get_drvdata(dev);

	वापस clk_prepare_enable(rot->घड़ी);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा drm_exynos_ipp_limit rotator_s5pv210_rbg888_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 8, SZ_16K पूर्ण, .v = अणु 8, SZ_16K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 2, .v.align = 2) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit rotator_4210_rbg888_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 8, SZ_16K पूर्ण, .v = अणु 8, SZ_16K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 4, .v.align = 4) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit rotator_4412_rbg888_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 8, SZ_8K पूर्ण, .v = अणु 8, SZ_8K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 4, .v.align = 4) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit rotator_5250_rbg888_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 8, SZ_8K पूर्ण, .v = अणु 8, SZ_8K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 2, .v.align = 2) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit rotator_s5pv210_yuv_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 32, SZ_64K पूर्ण, .v = अणु 32, SZ_64K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 8, .v.align = 8) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit rotator_4210_yuv_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 32, SZ_64K पूर्ण, .v = अणु 32, SZ_64K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 8, .v.align = 8) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit rotator_4412_yuv_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 32, SZ_32K पूर्ण, .v = अणु 32, SZ_32K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 8, .v.align = 8) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा exynos_drm_ipp_क्रमmats rotator_s5pv210_क्रमmats[] = अणु
	अणु IPP_SRCDST_FORMAT(XRGB8888, rotator_s5pv210_rbg888_limits) पूर्ण,
	अणु IPP_SRCDST_FORMAT(NV12, rotator_s5pv210_yuv_limits) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा exynos_drm_ipp_क्रमmats rotator_4210_क्रमmats[] = अणु
	अणु IPP_SRCDST_FORMAT(XRGB8888, rotator_4210_rbg888_limits) पूर्ण,
	अणु IPP_SRCDST_FORMAT(NV12, rotator_4210_yuv_limits) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा exynos_drm_ipp_क्रमmats rotator_4412_क्रमmats[] = अणु
	अणु IPP_SRCDST_FORMAT(XRGB8888, rotator_4412_rbg888_limits) पूर्ण,
	अणु IPP_SRCDST_FORMAT(NV12, rotator_4412_yuv_limits) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा exynos_drm_ipp_क्रमmats rotator_5250_क्रमmats[] = अणु
	अणु IPP_SRCDST_FORMAT(XRGB8888, rotator_5250_rbg888_limits) पूर्ण,
	अणु IPP_SRCDST_FORMAT(NV12, rotator_4412_yuv_limits) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rot_variant rotator_s5pv210_data = अणु
	.क्रमmats = rotator_s5pv210_क्रमmats,
	.num_क्रमmats = ARRAY_SIZE(rotator_s5pv210_क्रमmats),
पूर्ण;

अटल स्थिर काष्ठा rot_variant rotator_4210_data = अणु
	.क्रमmats = rotator_4210_क्रमmats,
	.num_क्रमmats = ARRAY_SIZE(rotator_4210_क्रमmats),
पूर्ण;

अटल स्थिर काष्ठा rot_variant rotator_4412_data = अणु
	.क्रमmats = rotator_4412_क्रमmats,
	.num_क्रमmats = ARRAY_SIZE(rotator_4412_क्रमmats),
पूर्ण;

अटल स्थिर काष्ठा rot_variant rotator_5250_data = अणु
	.क्रमmats = rotator_5250_क्रमmats,
	.num_क्रमmats = ARRAY_SIZE(rotator_5250_क्रमmats),
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_rotator_match[] = अणु
	अणु
		.compatible = "samsung,s5pv210-rotator",
		.data = &rotator_s5pv210_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-rotator",
		.data = &rotator_4210_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos4212-rotator",
		.data = &rotator_4412_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-rotator",
		.data = &rotator_5250_data,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_rotator_match);

अटल स्थिर काष्ठा dev_pm_ops rotator_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(rotator_runसमय_suspend, rotator_runसमय_resume,
									शून्य)
पूर्ण;

काष्ठा platक्रमm_driver rotator_driver = अणु
	.probe		= rotator_probe,
	.हटाओ		= rotator_हटाओ,
	.driver		= अणु
		.name	= "exynos-rotator",
		.owner	= THIS_MODULE,
		.pm	= &rotator_pm_ops,
		.of_match_table = exynos_rotator_match,
	पूर्ण,
पूर्ण;
