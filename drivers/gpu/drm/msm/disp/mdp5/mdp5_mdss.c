<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>

#समावेश "msm_drv.h"
#समावेश "mdp5_kms.h"

#घोषणा to_mdp5_mdss(x) container_of(x, काष्ठा mdp5_mdss, base)

काष्ठा mdp5_mdss अणु
	काष्ठा msm_mdss base;

	व्योम __iomem *mmio, *vbअगर;

	काष्ठा regulator *vdd;

	काष्ठा clk *ahb_clk;
	काष्ठा clk *axi_clk;
	काष्ठा clk *vsync_clk;

	काष्ठा अणु
		अस्थिर अचिन्हित दीर्घ enabled_mask;
		काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्ण irqcontroller;
पूर्ण;

अटल अंतरभूत व्योम mdss_ग_लिखो(काष्ठा mdp5_mdss *mdp5_mdss, u32 reg, u32 data)
अणु
	msm_ग_लिखोl(data, mdp5_mdss->mmio + reg);
पूर्ण

अटल अंतरभूत u32 mdss_पढ़ो(काष्ठा mdp5_mdss *mdp5_mdss, u32 reg)
अणु
	वापस msm_पढ़ोl(mdp5_mdss->mmio + reg);
पूर्ण

अटल irqवापस_t mdss_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा mdp5_mdss *mdp5_mdss = arg;
	u32 पूर्णांकr;

	पूर्णांकr = mdss_पढ़ो(mdp5_mdss, REG_MDSS_HW_INTR_STATUS);

	VERB("intr=%08x", पूर्णांकr);

	जबतक (पूर्णांकr) अणु
		irq_hw_number_t hwirq = fls(पूर्णांकr) - 1;

		generic_handle_irq(irq_find_mapping(
				mdp5_mdss->irqcontroller.करोमुख्य, hwirq));
		पूर्णांकr &= ~(1 << hwirq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * पूर्णांकerrupt-controller implementation, so sub-blocks (MDP/HDMI/eDP/DSI/etc)
 * can रेजिस्टर to get their irq's delivered
 */

#घोषणा VALID_IRQS  (MDSS_HW_INTR_STATUS_INTR_MDP | \
		MDSS_HW_INTR_STATUS_INTR_DSI0 | \
		MDSS_HW_INTR_STATUS_INTR_DSI1 | \
		MDSS_HW_INTR_STATUS_INTR_HDMI | \
		MDSS_HW_INTR_STATUS_INTR_EDP)

अटल व्योम mdss_hw_mask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा mdp5_mdss *mdp5_mdss = irq_data_get_irq_chip_data(irqd);

	smp_mb__beक्रमe_atomic();
	clear_bit(irqd->hwirq, &mdp5_mdss->irqcontroller.enabled_mask);
	smp_mb__after_atomic();
पूर्ण

अटल व्योम mdss_hw_unmask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा mdp5_mdss *mdp5_mdss = irq_data_get_irq_chip_data(irqd);

	smp_mb__beक्रमe_atomic();
	set_bit(irqd->hwirq, &mdp5_mdss->irqcontroller.enabled_mask);
	smp_mb__after_atomic();
पूर्ण

अटल काष्ठा irq_chip mdss_hw_irq_chip = अणु
	.name		= "mdss",
	.irq_mask	= mdss_hw_mask_irq,
	.irq_unmask	= mdss_hw_unmask_irq,
पूर्ण;

अटल पूर्णांक mdss_hw_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				 irq_hw_number_t hwirq)
अणु
	काष्ठा mdp5_mdss *mdp5_mdss = d->host_data;

	अगर (!(VALID_IRQS & (1 << hwirq)))
		वापस -EPERM;

	irq_set_chip_and_handler(irq, &mdss_hw_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, mdp5_mdss);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mdss_hw_irqकरोमुख्य_ops = अणु
	.map = mdss_hw_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;


अटल पूर्णांक mdss_irq_करोमुख्य_init(काष्ठा mdp5_mdss *mdp5_mdss)
अणु
	काष्ठा device *dev = mdp5_mdss->base.dev->dev;
	काष्ठा irq_करोमुख्य *d;

	d = irq_करोमुख्य_add_linear(dev->of_node, 32, &mdss_hw_irqकरोमुख्य_ops,
				  mdp5_mdss);
	अगर (!d) अणु
		DRM_DEV_ERROR(dev, "mdss irq domain add failed\n");
		वापस -ENXIO;
	पूर्ण

	mdp5_mdss->irqcontroller.enabled_mask = 0;
	mdp5_mdss->irqcontroller.करोमुख्य = d;

	वापस 0;
पूर्ण

अटल पूर्णांक mdp5_mdss_enable(काष्ठा msm_mdss *mdss)
अणु
	काष्ठा mdp5_mdss *mdp5_mdss = to_mdp5_mdss(mdss);
	DBG("");

	clk_prepare_enable(mdp5_mdss->ahb_clk);
	अगर (mdp5_mdss->axi_clk)
		clk_prepare_enable(mdp5_mdss->axi_clk);
	अगर (mdp5_mdss->vsync_clk)
		clk_prepare_enable(mdp5_mdss->vsync_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mdp5_mdss_disable(काष्ठा msm_mdss *mdss)
अणु
	काष्ठा mdp5_mdss *mdp5_mdss = to_mdp5_mdss(mdss);
	DBG("");

	अगर (mdp5_mdss->vsync_clk)
		clk_disable_unprepare(mdp5_mdss->vsync_clk);
	अगर (mdp5_mdss->axi_clk)
		clk_disable_unprepare(mdp5_mdss->axi_clk);
	clk_disable_unprepare(mdp5_mdss->ahb_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_mdss_get_घड़ीs(काष्ठा mdp5_mdss *mdp5_mdss)
अणु
	काष्ठा platक्रमm_device *pdev =
			to_platक्रमm_device(mdp5_mdss->base.dev->dev);

	mdp5_mdss->ahb_clk = msm_clk_get(pdev, "iface");
	अगर (IS_ERR(mdp5_mdss->ahb_clk))
		mdp5_mdss->ahb_clk = शून्य;

	mdp5_mdss->axi_clk = msm_clk_get(pdev, "bus");
	अगर (IS_ERR(mdp5_mdss->axi_clk))
		mdp5_mdss->axi_clk = शून्य;

	mdp5_mdss->vsync_clk = msm_clk_get(pdev, "vsync");
	अगर (IS_ERR(mdp5_mdss->vsync_clk))
		mdp5_mdss->vsync_clk = शून्य;

	वापस 0;
पूर्ण

अटल व्योम mdp5_mdss_destroy(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा mdp5_mdss *mdp5_mdss = to_mdp5_mdss(priv->mdss);

	अगर (!mdp5_mdss)
		वापस;

	irq_करोमुख्य_हटाओ(mdp5_mdss->irqcontroller.करोमुख्य);
	mdp5_mdss->irqcontroller.करोमुख्य = शून्य;

	regulator_disable(mdp5_mdss->vdd);

	pm_runसमय_disable(dev->dev);
पूर्ण

अटल स्थिर काष्ठा msm_mdss_funcs mdss_funcs = अणु
	.enable	= mdp5_mdss_enable,
	.disable = mdp5_mdss_disable,
	.destroy = mdp5_mdss_destroy,
पूर्ण;

पूर्णांक mdp5_mdss_init(काष्ठा drm_device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा mdp5_mdss *mdp5_mdss;
	पूर्णांक ret;

	DBG("");

	अगर (!of_device_is_compatible(dev->dev->of_node, "qcom,mdss"))
		वापस 0;

	mdp5_mdss = devm_kzalloc(dev->dev, माप(*mdp5_mdss), GFP_KERNEL);
	अगर (!mdp5_mdss) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	mdp5_mdss->base.dev = dev;

	mdp5_mdss->mmio = msm_ioremap(pdev, "mdss_phys", "MDSS");
	अगर (IS_ERR(mdp5_mdss->mmio)) अणु
		ret = PTR_ERR(mdp5_mdss->mmio);
		जाओ fail;
	पूर्ण

	mdp5_mdss->vbअगर = msm_ioremap(pdev, "vbif_phys", "VBIF");
	अगर (IS_ERR(mdp5_mdss->vbअगर)) अणु
		ret = PTR_ERR(mdp5_mdss->vbअगर);
		जाओ fail;
	पूर्ण

	ret = msm_mdss_get_घड़ीs(mdp5_mdss);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to get clocks: %d\n", ret);
		जाओ fail;
	पूर्ण

	/* Regulator to enable GDSCs in करोwnstream kernels */
	mdp5_mdss->vdd = devm_regulator_get(dev->dev, "vdd");
	अगर (IS_ERR(mdp5_mdss->vdd)) अणु
		ret = PTR_ERR(mdp5_mdss->vdd);
		जाओ fail;
	पूर्ण

	ret = regulator_enable(mdp5_mdss->vdd);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to enable regulator vdd: %d\n",
			ret);
		जाओ fail;
	पूर्ण

	ret = devm_request_irq(dev->dev, platक्रमm_get_irq(pdev, 0),
			       mdss_irq, 0, "mdss_isr", mdp5_mdss);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to init irq: %d\n", ret);
		जाओ fail_irq;
	पूर्ण

	ret = mdss_irq_करोमुख्य_init(mdp5_mdss);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to init sub-block irqs: %d\n", ret);
		जाओ fail_irq;
	पूर्ण

	mdp5_mdss->base.funcs = &mdss_funcs;
	priv->mdss = &mdp5_mdss->base;

	pm_runसमय_enable(dev->dev);

	वापस 0;
fail_irq:
	regulator_disable(mdp5_mdss->vdd);
fail:
	वापस ret;
पूर्ण
