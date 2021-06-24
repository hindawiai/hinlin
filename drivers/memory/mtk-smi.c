<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Yong Wu <yong.wu@mediatek.com>
 */
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <soc/mediatek/smi.h>
#समावेश <dt-bindings/memory/mt2701-larb-port.h>
#समावेश <dt-bindings/memory/mtk-memory-port.h>

/* mt8173 */
#घोषणा SMI_LARB_MMU_EN		0xf00

/* mt8167 */
#घोषणा MT8167_SMI_LARB_MMU_EN	0xfc0

/* mt2701 */
#घोषणा REG_SMI_SECUR_CON_BASE		0x5c0

/* every रेजिस्टर control 8 port, रेजिस्टर offset 0x4 */
#घोषणा REG_SMI_SECUR_CON_OFFSET(id)	(((id) >> 3) << 2)
#घोषणा REG_SMI_SECUR_CON_ADDR(id)	\
	(REG_SMI_SECUR_CON_BASE + REG_SMI_SECUR_CON_OFFSET(id))

/*
 * every port have 4 bit to control, bit[port + 3] control भव or physical,
 * bit[port + 2 : port + 1] control the करोमुख्य, bit[port] control the security
 * or non-security.
 */
#घोषणा SMI_SECUR_CON_VAL_MSK(id)	(~(0xf << (((id) & 0x7) << 2)))
#घोषणा SMI_SECUR_CON_VAL_VIRT(id)	BIT((((id) & 0x7) << 2) + 3)
/* mt2701 करोमुख्य should be set to 3 */
#घोषणा SMI_SECUR_CON_VAL_DOMAIN(id)	(0x3 << ((((id) & 0x7) << 2) + 1))

/* mt2712 */
#घोषणा SMI_LARB_NONSEC_CON(id)	(0x380 + ((id) * 4))
#घोषणा F_MMU_EN		BIT(0)
#घोषणा BANK_SEL(id)		(अणु			\
	u32 _id = (id) & 0x3;				\
	(_id << 8 | _id << 10 | _id << 12 | _id << 14);	\
पूर्ण)

/* SMI COMMON */
#घोषणा SMI_BUS_SEL			0x220
#घोषणा SMI_BUS_LARB_SHIFT(larbid)	((larbid) << 1)
/* All are MMU0 शेषly. Only specialize mmu1 here. */
#घोषणा F_MMU1_LARB(larbid)		(0x1 << SMI_BUS_LARB_SHIFT(larbid))

क्रमागत mtk_smi_gen अणु
	MTK_SMI_GEN1,
	MTK_SMI_GEN2
पूर्ण;

काष्ठा mtk_smi_common_plat अणु
	क्रमागत mtk_smi_gen gen;
	bool             has_gals;
	u32              bus_sel; /* Balance some larbs to enter mmu0 or mmu1 */
पूर्ण;

काष्ठा mtk_smi_larb_gen अणु
	पूर्णांक port_in_larb[MTK_LARB_NR_MAX + 1];
	व्योम (*config_port)(काष्ठा device *dev);
	अचिन्हित पूर्णांक			larb_direct_to_common_mask;
	bool				has_gals;
पूर्ण;

काष्ठा mtk_smi अणु
	काष्ठा device			*dev;
	काष्ठा clk			*clk_apb, *clk_smi;
	काष्ठा clk			*clk_gals0, *clk_gals1;
	काष्ठा clk			*clk_async; /*only needed by mt2701*/
	जोड़ अणु
		व्योम __iomem		*smi_ao_base; /* only क्रम gen1 */
		व्योम __iomem		*base;	      /* only क्रम gen2 */
	पूर्ण;
	स्थिर काष्ठा mtk_smi_common_plat *plat;
पूर्ण;

काष्ठा mtk_smi_larb अणु /* larb: local arbiter */
	काष्ठा mtk_smi			smi;
	व्योम __iomem			*base;
	काष्ठा device			*smi_common_dev;
	स्थिर काष्ठा mtk_smi_larb_gen	*larb_gen;
	पूर्णांक				larbid;
	u32				*mmu;
	अचिन्हित अक्षर			*bank;
पूर्ण;

अटल पूर्णांक mtk_smi_clk_enable(स्थिर काष्ठा mtk_smi *smi)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(smi->clk_apb);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(smi->clk_smi);
	अगर (ret)
		जाओ err_disable_apb;

	ret = clk_prepare_enable(smi->clk_gals0);
	अगर (ret)
		जाओ err_disable_smi;

	ret = clk_prepare_enable(smi->clk_gals1);
	अगर (ret)
		जाओ err_disable_gals0;

	वापस 0;

err_disable_gals0:
	clk_disable_unprepare(smi->clk_gals0);
err_disable_smi:
	clk_disable_unprepare(smi->clk_smi);
err_disable_apb:
	clk_disable_unprepare(smi->clk_apb);
	वापस ret;
पूर्ण

अटल व्योम mtk_smi_clk_disable(स्थिर काष्ठा mtk_smi *smi)
अणु
	clk_disable_unprepare(smi->clk_gals1);
	clk_disable_unprepare(smi->clk_gals0);
	clk_disable_unprepare(smi->clk_smi);
	clk_disable_unprepare(smi->clk_apb);
पूर्ण

पूर्णांक mtk_smi_larb_get(काष्ठा device *larbdev)
अणु
	पूर्णांक ret = pm_runसमय_resume_and_get(larbdev);

	वापस (ret < 0) ? ret : 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_smi_larb_get);

व्योम mtk_smi_larb_put(काष्ठा device *larbdev)
अणु
	pm_runसमय_put_sync(larbdev);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_smi_larb_put);

अटल पूर्णांक
mtk_smi_larb_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा mtk_smi_larb *larb = dev_get_drvdata(dev);
	काष्ठा mtk_smi_larb_iommu *larb_mmu = data;
	अचिन्हित पूर्णांक         i;

	क्रम (i = 0; i < MTK_LARB_NR_MAX; i++) अणु
		अगर (dev == larb_mmu[i].dev) अणु
			larb->larbid = i;
			larb->mmu = &larb_mmu[i].mmu;
			larb->bank = larb_mmu[i].bank;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम mtk_smi_larb_config_port_gen2_general(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi_larb *larb = dev_get_drvdata(dev);
	u32 reg;
	पूर्णांक i;

	अगर (BIT(larb->larbid) & larb->larb_gen->larb_direct_to_common_mask)
		वापस;

	क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)larb->mmu, 32) अणु
		reg = पढ़ोl_relaxed(larb->base + SMI_LARB_NONSEC_CON(i));
		reg |= F_MMU_EN;
		reg |= BANK_SEL(larb->bank[i]);
		ग_लिखोl(reg, larb->base + SMI_LARB_NONSEC_CON(i));
	पूर्ण
पूर्ण

अटल व्योम mtk_smi_larb_config_port_mt8173(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi_larb *larb = dev_get_drvdata(dev);

	ग_लिखोl(*larb->mmu, larb->base + SMI_LARB_MMU_EN);
पूर्ण

अटल व्योम mtk_smi_larb_config_port_mt8167(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi_larb *larb = dev_get_drvdata(dev);

	ग_लिखोl(*larb->mmu, larb->base + MT8167_SMI_LARB_MMU_EN);
पूर्ण

अटल व्योम mtk_smi_larb_config_port_gen1(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi_larb *larb = dev_get_drvdata(dev);
	स्थिर काष्ठा mtk_smi_larb_gen *larb_gen = larb->larb_gen;
	काष्ठा mtk_smi *common = dev_get_drvdata(larb->smi_common_dev);
	पूर्णांक i, m4u_port_id, larb_port_num;
	u32 sec_con_val, reg_val;

	m4u_port_id = larb_gen->port_in_larb[larb->larbid];
	larb_port_num = larb_gen->port_in_larb[larb->larbid + 1]
			- larb_gen->port_in_larb[larb->larbid];

	क्रम (i = 0; i < larb_port_num; i++, m4u_port_id++) अणु
		अगर (*larb->mmu & BIT(i)) अणु
			/* bit[port + 3] controls the भव or physical */
			sec_con_val = SMI_SECUR_CON_VAL_VIRT(m4u_port_id);
		पूर्ण अन्यथा अणु
			/* करो not need to enable m4u क्रम this port */
			जारी;
		पूर्ण
		reg_val = पढ़ोl(common->smi_ao_base
			+ REG_SMI_SECUR_CON_ADDR(m4u_port_id));
		reg_val &= SMI_SECUR_CON_VAL_MSK(m4u_port_id);
		reg_val |= sec_con_val;
		reg_val |= SMI_SECUR_CON_VAL_DOMAIN(m4u_port_id);
		ग_लिखोl(reg_val,
			common->smi_ao_base
			+ REG_SMI_SECUR_CON_ADDR(m4u_port_id));
	पूर्ण
पूर्ण

अटल व्योम
mtk_smi_larb_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	/* Do nothing as the iommu is always enabled. */
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_smi_larb_component_ops = अणु
	.bind = mtk_smi_larb_bind,
	.unbind = mtk_smi_larb_unbind,
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_larb_gen mtk_smi_larb_mt8173 = अणु
	/* mt8173 करो not need the port in larb */
	.config_port = mtk_smi_larb_config_port_mt8173,
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_larb_gen mtk_smi_larb_mt8167 = अणु
	/* mt8167 करो not need the port in larb */
	.config_port = mtk_smi_larb_config_port_mt8167,
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_larb_gen mtk_smi_larb_mt2701 = अणु
	.port_in_larb = अणु
		LARB0_PORT_OFFSET, LARB1_PORT_OFFSET,
		LARB2_PORT_OFFSET, LARB3_PORT_OFFSET
	पूर्ण,
	.config_port = mtk_smi_larb_config_port_gen1,
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_larb_gen mtk_smi_larb_mt2712 = अणु
	.config_port                = mtk_smi_larb_config_port_gen2_general,
	.larb_direct_to_common_mask = BIT(8) | BIT(9),      /* bdpsys */
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_larb_gen mtk_smi_larb_mt6779 = अणु
	.config_port  = mtk_smi_larb_config_port_gen2_general,
	.larb_direct_to_common_mask =
		BIT(4) | BIT(6) | BIT(11) | BIT(12) | BIT(13),
		/* DUMMY | IPU0 | IPU1 | CCU | MDLA */
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_larb_gen mtk_smi_larb_mt8183 = अणु
	.has_gals                   = true,
	.config_port                = mtk_smi_larb_config_port_gen2_general,
	.larb_direct_to_common_mask = BIT(2) | BIT(3) | BIT(7),
				      /* IPU0 | IPU1 | CCU */
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_larb_gen mtk_smi_larb_mt8192 = अणु
	.config_port                = mtk_smi_larb_config_port_gen2_general,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_smi_larb_of_ids[] = अणु
	अणु
		.compatible = "mediatek,mt8167-smi-larb",
		.data = &mtk_smi_larb_mt8167
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8173-smi-larb",
		.data = &mtk_smi_larb_mt8173
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2701-smi-larb",
		.data = &mtk_smi_larb_mt2701
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2712-smi-larb",
		.data = &mtk_smi_larb_mt2712
	पूर्ण,
	अणु
		.compatible = "mediatek,mt6779-smi-larb",
		.data = &mtk_smi_larb_mt6779
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183-smi-larb",
		.data = &mtk_smi_larb_mt8183
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8192-smi-larb",
		.data = &mtk_smi_larb_mt8192
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक mtk_smi_larb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_smi_larb *larb;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *smi_node;
	काष्ठा platक्रमm_device *smi_pdev;
	काष्ठा device_link *link;

	larb = devm_kzalloc(dev, माप(*larb), GFP_KERNEL);
	अगर (!larb)
		वापस -ENOMEM;

	larb->larb_gen = of_device_get_match_data(dev);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	larb->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(larb->base))
		वापस PTR_ERR(larb->base);

	larb->smi.clk_apb = devm_clk_get(dev, "apb");
	अगर (IS_ERR(larb->smi.clk_apb))
		वापस PTR_ERR(larb->smi.clk_apb);

	larb->smi.clk_smi = devm_clk_get(dev, "smi");
	अगर (IS_ERR(larb->smi.clk_smi))
		वापस PTR_ERR(larb->smi.clk_smi);

	अगर (larb->larb_gen->has_gals) अणु
		/* The larbs may still haven't gals even अगर the SoC support.*/
		larb->smi.clk_gals0 = devm_clk_get(dev, "gals");
		अगर (PTR_ERR(larb->smi.clk_gals0) == -ENOENT)
			larb->smi.clk_gals0 = शून्य;
		अन्यथा अगर (IS_ERR(larb->smi.clk_gals0))
			वापस PTR_ERR(larb->smi.clk_gals0);
	पूर्ण
	larb->smi.dev = dev;

	smi_node = of_parse_phandle(dev->of_node, "mediatek,smi", 0);
	अगर (!smi_node)
		वापस -EINVAL;

	smi_pdev = of_find_device_by_node(smi_node);
	of_node_put(smi_node);
	अगर (smi_pdev) अणु
		अगर (!platक्रमm_get_drvdata(smi_pdev))
			वापस -EPROBE_DEFER;
		larb->smi_common_dev = &smi_pdev->dev;
		link = device_link_add(dev, larb->smi_common_dev,
				       DL_FLAG_PM_RUNTIME | DL_FLAG_STATELESS);
		अगर (!link) अणु
			dev_err(dev, "Unable to link smi-common dev\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "Failed to get the smi_common device\n");
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_enable(dev);
	platक्रमm_set_drvdata(pdev, larb);
	वापस component_add(dev, &mtk_smi_larb_component_ops);
पूर्ण

अटल पूर्णांक mtk_smi_larb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_smi_larb *larb = platक्रमm_get_drvdata(pdev);

	device_link_हटाओ(&pdev->dev, larb->smi_common_dev);
	pm_runसमय_disable(&pdev->dev);
	component_del(&pdev->dev, &mtk_smi_larb_component_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_smi_larb_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi_larb *larb = dev_get_drvdata(dev);
	स्थिर काष्ठा mtk_smi_larb_gen *larb_gen = larb->larb_gen;
	पूर्णांक ret;

	ret = mtk_smi_clk_enable(&larb->smi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable clock(%d).\n", ret);
		वापस ret;
	पूर्ण

	/* Configure the basic setting क्रम this larb */
	larb_gen->config_port(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_smi_larb_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi_larb *larb = dev_get_drvdata(dev);

	mtk_smi_clk_disable(&larb->smi);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops smi_larb_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mtk_smi_larb_suspend, mtk_smi_larb_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_smi_larb_driver = अणु
	.probe	= mtk_smi_larb_probe,
	.हटाओ	= mtk_smi_larb_हटाओ,
	.driver	= अणु
		.name = "mtk-smi-larb",
		.of_match_table = mtk_smi_larb_of_ids,
		.pm             = &smi_larb_pm_ops,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_common_plat mtk_smi_common_gen1 = अणु
	.gen = MTK_SMI_GEN1,
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_common_plat mtk_smi_common_gen2 = अणु
	.gen = MTK_SMI_GEN2,
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_common_plat mtk_smi_common_mt6779 = अणु
	.gen		= MTK_SMI_GEN2,
	.has_gals	= true,
	.bus_sel	= F_MMU1_LARB(1) | F_MMU1_LARB(2) | F_MMU1_LARB(4) |
			  F_MMU1_LARB(5) | F_MMU1_LARB(6) | F_MMU1_LARB(7),
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_common_plat mtk_smi_common_mt8183 = अणु
	.gen      = MTK_SMI_GEN2,
	.has_gals = true,
	.bus_sel  = F_MMU1_LARB(1) | F_MMU1_LARB(2) | F_MMU1_LARB(5) |
		    F_MMU1_LARB(7),
पूर्ण;

अटल स्थिर काष्ठा mtk_smi_common_plat mtk_smi_common_mt8192 = अणु
	.gen      = MTK_SMI_GEN2,
	.has_gals = true,
	.bus_sel  = F_MMU1_LARB(1) | F_MMU1_LARB(2) | F_MMU1_LARB(5) |
		    F_MMU1_LARB(6),
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_smi_common_of_ids[] = अणु
	अणु
		.compatible = "mediatek,mt8173-smi-common",
		.data = &mtk_smi_common_gen2,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8167-smi-common",
		.data = &mtk_smi_common_gen2,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2701-smi-common",
		.data = &mtk_smi_common_gen1,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2712-smi-common",
		.data = &mtk_smi_common_gen2,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt6779-smi-common",
		.data = &mtk_smi_common_mt6779,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183-smi-common",
		.data = &mtk_smi_common_mt8183,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8192-smi-common",
		.data = &mtk_smi_common_mt8192,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक mtk_smi_common_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_smi *common;
	काष्ठा resource *res;
	पूर्णांक ret;

	common = devm_kzalloc(dev, माप(*common), GFP_KERNEL);
	अगर (!common)
		वापस -ENOMEM;
	common->dev = dev;
	common->plat = of_device_get_match_data(dev);

	common->clk_apb = devm_clk_get(dev, "apb");
	अगर (IS_ERR(common->clk_apb))
		वापस PTR_ERR(common->clk_apb);

	common->clk_smi = devm_clk_get(dev, "smi");
	अगर (IS_ERR(common->clk_smi))
		वापस PTR_ERR(common->clk_smi);

	अगर (common->plat->has_gals) अणु
		common->clk_gals0 = devm_clk_get(dev, "gals0");
		अगर (IS_ERR(common->clk_gals0))
			वापस PTR_ERR(common->clk_gals0);

		common->clk_gals1 = devm_clk_get(dev, "gals1");
		अगर (IS_ERR(common->clk_gals1))
			वापस PTR_ERR(common->clk_gals1);
	पूर्ण

	/*
	 * क्रम mtk smi gen 1, we need to get the ao(always on) base to config
	 * m4u port, and we need to enable the aync घड़ी क्रम transक्रमm the smi
	 * घड़ी पूर्णांकo emi घड़ी करोमुख्य, but क्रम mtk smi gen2, there's no smi ao
	 * base.
	 */
	अगर (common->plat->gen == MTK_SMI_GEN1) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		common->smi_ao_base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(common->smi_ao_base))
			वापस PTR_ERR(common->smi_ao_base);

		common->clk_async = devm_clk_get(dev, "async");
		अगर (IS_ERR(common->clk_async))
			वापस PTR_ERR(common->clk_async);

		ret = clk_prepare_enable(common->clk_async);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		common->base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(common->base))
			वापस PTR_ERR(common->base);
	पूर्ण
	pm_runसमय_enable(dev);
	platक्रमm_set_drvdata(pdev, common);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_smi_common_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_smi_common_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi *common = dev_get_drvdata(dev);
	u32 bus_sel = common->plat->bus_sel;
	पूर्णांक ret;

	ret = mtk_smi_clk_enable(common);
	अगर (ret) अणु
		dev_err(common->dev, "Failed to enable clock(%d).\n", ret);
		वापस ret;
	पूर्ण

	अगर (common->plat->gen == MTK_SMI_GEN2 && bus_sel)
		ग_लिखोl(bus_sel, common->base + SMI_BUS_SEL);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_smi_common_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_smi *common = dev_get_drvdata(dev);

	mtk_smi_clk_disable(common);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops smi_common_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mtk_smi_common_suspend, mtk_smi_common_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_smi_common_driver = अणु
	.probe	= mtk_smi_common_probe,
	.हटाओ = mtk_smi_common_हटाओ,
	.driver	= अणु
		.name = "mtk-smi-common",
		.of_match_table = mtk_smi_common_of_ids,
		.pm             = &smi_common_pm_ops,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर smidrivers[] = अणु
	&mtk_smi_common_driver,
	&mtk_smi_larb_driver,
पूर्ण;

अटल पूर्णांक __init mtk_smi_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(smidrivers, ARRAY_SIZE(smidrivers));
पूर्ण
module_init(mtk_smi_init);

अटल व्योम __निकास mtk_smi_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(smidrivers, ARRAY_SIZE(smidrivers));
पूर्ण
module_निकास(mtk_smi_निकास);

MODULE_DESCRIPTION("MediaTek SMI driver");
MODULE_LICENSE("GPL v2");
