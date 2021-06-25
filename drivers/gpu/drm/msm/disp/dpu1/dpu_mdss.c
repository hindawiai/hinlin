<शैली गुरु>
/*
 * SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2018, The Linux Foundation
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश "dpu_kms.h"

#घोषणा to_dpu_mdss(x) container_of(x, काष्ठा dpu_mdss, base)

#घोषणा HW_REV				0x0
#घोषणा HW_INTR_STATUS			0x0010

#घोषणा UBWC_STATIC			0x144
#घोषणा UBWC_CTRL_2			0x150
#घोषणा UBWC_PREDICTION_MODE		0x154

/* Max BW defined in KBps */
#घोषणा MAX_BW				6800000

काष्ठा dpu_irq_controller अणु
	अचिन्हित दीर्घ enabled_mask;
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

काष्ठा dpu_mdss अणु
	काष्ठा msm_mdss base;
	व्योम __iomem *mmio;
	काष्ठा dss_module_घातer mp;
	काष्ठा dpu_irq_controller irq_controller;
पूर्ण;

अटल व्योम dpu_mdss_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा dpu_mdss *dpu_mdss = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 पूर्णांकerrupts;

	chained_irq_enter(chip, desc);

	पूर्णांकerrupts = पढ़ोl_relaxed(dpu_mdss->mmio + HW_INTR_STATUS);

	जबतक (पूर्णांकerrupts) अणु
		irq_hw_number_t hwirq = fls(पूर्णांकerrupts) - 1;
		अचिन्हित पूर्णांक mapping;
		पूर्णांक rc;

		mapping = irq_find_mapping(dpu_mdss->irq_controller.करोमुख्य,
					   hwirq);
		अगर (mapping == 0) अणु
			DRM_ERROR("couldn't find irq mapping for %lu\n", hwirq);
			अवरोध;
		पूर्ण

		rc = generic_handle_irq(mapping);
		अगर (rc < 0) अणु
			DRM_ERROR("handle irq fail: irq=%lu mapping=%u rc=%d\n",
				  hwirq, mapping, rc);
			अवरोध;
		पूर्ण

		पूर्णांकerrupts &= ~(1 << hwirq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम dpu_mdss_irq_mask(काष्ठा irq_data *irqd)
अणु
	काष्ठा dpu_mdss *dpu_mdss = irq_data_get_irq_chip_data(irqd);

	/* memory barrier */
	smp_mb__beक्रमe_atomic();
	clear_bit(irqd->hwirq, &dpu_mdss->irq_controller.enabled_mask);
	/* memory barrier */
	smp_mb__after_atomic();
पूर्ण

अटल व्योम dpu_mdss_irq_unmask(काष्ठा irq_data *irqd)
अणु
	काष्ठा dpu_mdss *dpu_mdss = irq_data_get_irq_chip_data(irqd);

	/* memory barrier */
	smp_mb__beक्रमe_atomic();
	set_bit(irqd->hwirq, &dpu_mdss->irq_controller.enabled_mask);
	/* memory barrier */
	smp_mb__after_atomic();
पूर्ण

अटल काष्ठा irq_chip dpu_mdss_irq_chip = अणु
	.name = "dpu_mdss",
	.irq_mask = dpu_mdss_irq_mask,
	.irq_unmask = dpu_mdss_irq_unmask,
पूर्ण;

अटल काष्ठा lock_class_key dpu_mdss_lock_key, dpu_mdss_request_key;

अटल पूर्णांक dpu_mdss_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *करोमुख्य,
		अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	काष्ठा dpu_mdss *dpu_mdss = करोमुख्य->host_data;

	irq_set_lockdep_class(irq, &dpu_mdss_lock_key, &dpu_mdss_request_key);
	irq_set_chip_and_handler(irq, &dpu_mdss_irq_chip, handle_level_irq);
	वापस irq_set_chip_data(irq, dpu_mdss);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops dpu_mdss_irqकरोमुख्य_ops = अणु
	.map = dpu_mdss_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक _dpu_mdss_irq_करोमुख्य_add(काष्ठा dpu_mdss *dpu_mdss)
अणु
	काष्ठा device *dev;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	dev = dpu_mdss->base.dev->dev;

	करोमुख्य = irq_करोमुख्य_add_linear(dev->of_node, 32,
			&dpu_mdss_irqकरोमुख्य_ops, dpu_mdss);
	अगर (!करोमुख्य) अणु
		DPU_ERROR("failed to add irq_domain\n");
		वापस -EINVAL;
	पूर्ण

	dpu_mdss->irq_controller.enabled_mask = 0;
	dpu_mdss->irq_controller.करोमुख्य = करोमुख्य;

	वापस 0;
पूर्ण

अटल व्योम _dpu_mdss_irq_करोमुख्य_fini(काष्ठा dpu_mdss *dpu_mdss)
अणु
	अगर (dpu_mdss->irq_controller.करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(dpu_mdss->irq_controller.करोमुख्य);
		dpu_mdss->irq_controller.करोमुख्य = शून्य;
	पूर्ण
पूर्ण
अटल पूर्णांक dpu_mdss_enable(काष्ठा msm_mdss *mdss)
अणु
	काष्ठा dpu_mdss *dpu_mdss = to_dpu_mdss(mdss);
	काष्ठा dss_module_घातer *mp = &dpu_mdss->mp;
	पूर्णांक ret;

	ret = msm_dss_enable_clk(mp->clk_config, mp->num_clk, true);
	अगर (ret) अणु
		DPU_ERROR("clock enable failed, ret:%d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * ubwc config is part of the "mdss" region which is not accessible
	 * from the rest of the driver. hardcode known configurations here
	 */
	चयन (पढ़ोl_relaxed(dpu_mdss->mmio + HW_REV)) अणु
	हाल DPU_HW_VER_500:
	हाल DPU_HW_VER_501:
		ग_लिखोl_relaxed(0x420, dpu_mdss->mmio + UBWC_STATIC);
		अवरोध;
	हाल DPU_HW_VER_600:
		/* TODO: 0x102e क्रम LP_DDR4 */
		ग_लिखोl_relaxed(0x103e, dpu_mdss->mmio + UBWC_STATIC);
		ग_लिखोl_relaxed(2, dpu_mdss->mmio + UBWC_CTRL_2);
		ग_लिखोl_relaxed(1, dpu_mdss->mmio + UBWC_PREDICTION_MODE);
		अवरोध;
	हाल DPU_HW_VER_620:
		ग_लिखोl_relaxed(0x1e, dpu_mdss->mmio + UBWC_STATIC);
		अवरोध;
	हाल DPU_HW_VER_720:
		ग_लिखोl_relaxed(0x101e, dpu_mdss->mmio + UBWC_STATIC);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dpu_mdss_disable(काष्ठा msm_mdss *mdss)
अणु
	काष्ठा dpu_mdss *dpu_mdss = to_dpu_mdss(mdss);
	काष्ठा dss_module_घातer *mp = &dpu_mdss->mp;
	पूर्णांक ret;

	ret = msm_dss_enable_clk(mp->clk_config, mp->num_clk, false);
	अगर (ret)
		DPU_ERROR("clock disable failed, ret:%d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम dpu_mdss_destroy(काष्ठा drm_device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा dpu_mdss *dpu_mdss = to_dpu_mdss(priv->mdss);
	काष्ठा dss_module_घातer *mp = &dpu_mdss->mp;
	पूर्णांक irq;

	pm_runसमय_suspend(dev->dev);
	pm_runसमय_disable(dev->dev);
	_dpu_mdss_irq_करोमुख्य_fini(dpu_mdss);
	irq = platक्रमm_get_irq(pdev, 0);
	irq_set_chained_handler_and_data(irq, शून्य, शून्य);
	msm_dss_put_clk(mp->clk_config, mp->num_clk);
	devm_kमुक्त(&pdev->dev, mp->clk_config);

	अगर (dpu_mdss->mmio)
		devm_iounmap(&pdev->dev, dpu_mdss->mmio);
	dpu_mdss->mmio = शून्य;
	priv->mdss = शून्य;
पूर्ण

अटल स्थिर काष्ठा msm_mdss_funcs mdss_funcs = अणु
	.enable	= dpu_mdss_enable,
	.disable = dpu_mdss_disable,
	.destroy = dpu_mdss_destroy,
पूर्ण;

पूर्णांक dpu_mdss_init(काष्ठा drm_device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा dpu_mdss *dpu_mdss;
	काष्ठा dss_module_घातer *mp;
	पूर्णांक ret = 0;
	पूर्णांक irq;

	dpu_mdss = devm_kzalloc(dev->dev, माप(*dpu_mdss), GFP_KERNEL);
	अगर (!dpu_mdss)
		वापस -ENOMEM;

	dpu_mdss->mmio = msm_ioremap(pdev, "mdss", "mdss");
	अगर (IS_ERR(dpu_mdss->mmio))
		वापस PTR_ERR(dpu_mdss->mmio);

	DRM_DEBUG("mapped mdss address space @%pK\n", dpu_mdss->mmio);

	mp = &dpu_mdss->mp;
	ret = msm_dss_parse_घड़ी(pdev, mp);
	अगर (ret) अणु
		DPU_ERROR("failed to parse clocks, ret=%d\n", ret);
		जाओ clk_parse_err;
	पूर्ण

	dpu_mdss->base.dev = dev;
	dpu_mdss->base.funcs = &mdss_funcs;

	ret = _dpu_mdss_irq_करोमुख्य_add(dpu_mdss);
	अगर (ret)
		जाओ irq_करोमुख्य_error;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		जाओ irq_error;

	irq_set_chained_handler_and_data(irq, dpu_mdss_irq,
					 dpu_mdss);

	priv->mdss = &dpu_mdss->base;

	pm_runसमय_enable(dev->dev);

	वापस ret;

irq_error:
	_dpu_mdss_irq_करोमुख्य_fini(dpu_mdss);
irq_करोमुख्य_error:
	msm_dss_put_clk(mp->clk_config, mp->num_clk);
clk_parse_err:
	devm_kमुक्त(&pdev->dev, mp->clk_config);
	अगर (dpu_mdss->mmio)
		devm_iounmap(&pdev->dev, dpu_mdss->mmio);
	dpu_mdss->mmio = शून्य;
	वापस ret;
पूर्ण
