<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (C) 2011 Google, Inc.
 *
 * Author:
 *	Jay Cheng <jacheng@nvidia.com>
 *	James Wylder <james.wylder@motorola.com>
 *	Benoit Goby <benoit@android.com>
 *	Colin Cross <ccross@android.com>
 *	Hiroshi DOYU <hकरोyu@nvidia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <soc/tegra/ahb.h>

#घोषणा DRV_NAME "tegra-ahb"

#घोषणा AHB_ARBITRATION_DISABLE		0x04
#घोषणा AHB_ARBITRATION_PRIORITY_CTRL	0x08
#घोषणा   AHB_PRIORITY_WEIGHT(x)	(((x) & 0x7) << 29)
#घोषणा   PRIORITY_SELECT_USB BIT(6)
#घोषणा   PRIORITY_SELECT_USB2 BIT(18)
#घोषणा   PRIORITY_SELECT_USB3 BIT(17)

#घोषणा AHB_GIZMO_AHB_MEM		0x10
#घोषणा   ENB_FAST_REARBITRATE BIT(2)
#घोषणा   DONT_SPLIT_AHB_WR     BIT(7)

#घोषणा AHB_GIZMO_APB_DMA		0x14
#घोषणा AHB_GIZMO_IDE			0x1c
#घोषणा AHB_GIZMO_USB			0x20
#घोषणा AHB_GIZMO_AHB_XBAR_BRIDGE	0x24
#घोषणा AHB_GIZMO_CPU_AHB_BRIDGE	0x28
#घोषणा AHB_GIZMO_COP_AHB_BRIDGE	0x2c
#घोषणा AHB_GIZMO_XBAR_APB_CTLR		0x30
#घोषणा AHB_GIZMO_VCP_AHB_BRIDGE	0x34
#घोषणा AHB_GIZMO_न_अंकD			0x40
#घोषणा AHB_GIZMO_SDMMC4		0x48
#घोषणा AHB_GIZMO_XIO			0x4c
#घोषणा AHB_GIZMO_BSEV			0x64
#घोषणा AHB_GIZMO_BSEA			0x74
#घोषणा AHB_GIZMO_NOR			0x78
#घोषणा AHB_GIZMO_USB2			0x7c
#घोषणा AHB_GIZMO_USB3			0x80
#घोषणा   IMMEDIATE	BIT(18)

#घोषणा AHB_GIZMO_SDMMC1		0x84
#घोषणा AHB_GIZMO_SDMMC2		0x88
#घोषणा AHB_GIZMO_SDMMC3		0x8c
#घोषणा AHB_MEM_PREFETCH_CFG_X		0xdc
#घोषणा AHB_ARBITRATION_XBAR_CTRL	0xe0
#घोषणा AHB_MEM_PREFETCH_CFG3		0xe4
#घोषणा AHB_MEM_PREFETCH_CFG4		0xe8
#घोषणा AHB_MEM_PREFETCH_CFG1		0xf0
#घोषणा AHB_MEM_PREFETCH_CFG2		0xf4
#घोषणा   PREFETCH_ENB	BIT(31)
#घोषणा   MST_ID(x)	(((x) & 0x1f) << 26)
#घोषणा   AHBDMA_MST_ID	MST_ID(5)
#घोषणा   USB_MST_ID	MST_ID(6)
#घोषणा   USB2_MST_ID	MST_ID(18)
#घोषणा   USB3_MST_ID	MST_ID(17)
#घोषणा   ADDR_BNDRY(x)	(((x) & 0xf) << 21)
#घोषणा   INACTIVITY_TIMEOUT(x)	(((x) & 0xffff) << 0)

#घोषणा AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID	0xfc

#घोषणा AHB_ARBITRATION_XBAR_CTRL_SMMU_INIT_DONE BIT(17)

/*
 * INCORRECT_BASE_ADDR_LOW_BYTE: Legacy kernel DT files क्रम Tegra SoCs
 * prior to Tegra124 generally use a physical base address ending in
 * 0x4 क्रम the AHB IP block.  According to the TRM, the low byte
 * should be 0x0.  During device probing, this macro is used to detect
 * whether the passed-in physical address is incorrect, and अगर so, to
 * correct it.
 */
#घोषणा INCORRECT_BASE_ADDR_LOW_BYTE		0x4

अटल काष्ठा platक्रमm_driver tegra_ahb_driver;

अटल स्थिर u32 tegra_ahb_gizmo[] = अणु
	AHB_ARBITRATION_DISABLE,
	AHB_ARBITRATION_PRIORITY_CTRL,
	AHB_GIZMO_AHB_MEM,
	AHB_GIZMO_APB_DMA,
	AHB_GIZMO_IDE,
	AHB_GIZMO_USB,
	AHB_GIZMO_AHB_XBAR_BRIDGE,
	AHB_GIZMO_CPU_AHB_BRIDGE,
	AHB_GIZMO_COP_AHB_BRIDGE,
	AHB_GIZMO_XBAR_APB_CTLR,
	AHB_GIZMO_VCP_AHB_BRIDGE,
	AHB_GIZMO_न_अंकD,
	AHB_GIZMO_SDMMC4,
	AHB_GIZMO_XIO,
	AHB_GIZMO_BSEV,
	AHB_GIZMO_BSEA,
	AHB_GIZMO_NOR,
	AHB_GIZMO_USB2,
	AHB_GIZMO_USB3,
	AHB_GIZMO_SDMMC1,
	AHB_GIZMO_SDMMC2,
	AHB_GIZMO_SDMMC3,
	AHB_MEM_PREFETCH_CFG_X,
	AHB_ARBITRATION_XBAR_CTRL,
	AHB_MEM_PREFETCH_CFG3,
	AHB_MEM_PREFETCH_CFG4,
	AHB_MEM_PREFETCH_CFG1,
	AHB_MEM_PREFETCH_CFG2,
	AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID,
पूर्ण;

काष्ठा tegra_ahb अणु
	व्योम __iomem	*regs;
	काष्ठा device	*dev;
	u32		ctx[];
पूर्ण;

अटल अंतरभूत u32 gizmo_पढ़ोl(काष्ठा tegra_ahb *ahb, u32 offset)
अणु
	वापस पढ़ोl(ahb->regs + offset);
पूर्ण

अटल अंतरभूत व्योम gizmo_ग_लिखोl(काष्ठा tegra_ahb *ahb, u32 value, u32 offset)
अणु
	ग_लिखोl(value, ahb->regs + offset);
पूर्ण

#अगर_घोषित CONFIG_TEGRA_IOMMU_SMMU
पूर्णांक tegra_ahb_enable_smmu(काष्ठा device_node *dn)
अणु
	काष्ठा device *dev;
	u32 val;
	काष्ठा tegra_ahb *ahb;

	dev = driver_find_device_by_of_node(&tegra_ahb_driver.driver, dn);
	अगर (!dev)
		वापस -EPROBE_DEFER;
	ahb = dev_get_drvdata(dev);
	val = gizmo_पढ़ोl(ahb, AHB_ARBITRATION_XBAR_CTRL);
	val |= AHB_ARBITRATION_XBAR_CTRL_SMMU_INIT_DONE;
	gizmo_ग_लिखोl(ahb, val, AHB_ARBITRATION_XBAR_CTRL);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_ahb_enable_smmu);
#पूर्ण_अगर

अटल पूर्णांक __maybe_unused tegra_ahb_suspend(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा tegra_ahb *ahb = dev_get_drvdata(dev);

	क्रम (i = 0; i < ARRAY_SIZE(tegra_ahb_gizmo); i++)
		ahb->ctx[i] = gizmo_पढ़ोl(ahb, tegra_ahb_gizmo[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_ahb_resume(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा tegra_ahb *ahb = dev_get_drvdata(dev);

	क्रम (i = 0; i < ARRAY_SIZE(tegra_ahb_gizmo); i++)
		gizmo_ग_लिखोl(ahb, ahb->ctx[i], tegra_ahb_gizmo[i]);
	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(tegra_ahb_pm,
			    tegra_ahb_suspend,
			    tegra_ahb_resume, शून्य);

अटल व्योम tegra_ahb_gizmo_init(काष्ठा tegra_ahb *ahb)
अणु
	u32 val;

	val = gizmo_पढ़ोl(ahb, AHB_GIZMO_AHB_MEM);
	val |= ENB_FAST_REARBITRATE | IMMEDIATE | DONT_SPLIT_AHB_WR;
	gizmo_ग_लिखोl(ahb, val, AHB_GIZMO_AHB_MEM);

	val = gizmo_पढ़ोl(ahb, AHB_GIZMO_USB);
	val |= IMMEDIATE;
	gizmo_ग_लिखोl(ahb, val, AHB_GIZMO_USB);

	val = gizmo_पढ़ोl(ahb, AHB_GIZMO_USB2);
	val |= IMMEDIATE;
	gizmo_ग_लिखोl(ahb, val, AHB_GIZMO_USB2);

	val = gizmo_पढ़ोl(ahb, AHB_GIZMO_USB3);
	val |= IMMEDIATE;
	gizmo_ग_लिखोl(ahb, val, AHB_GIZMO_USB3);

	val = gizmo_पढ़ोl(ahb, AHB_ARBITRATION_PRIORITY_CTRL);
	val |= PRIORITY_SELECT_USB |
		PRIORITY_SELECT_USB2 |
		PRIORITY_SELECT_USB3 |
		AHB_PRIORITY_WEIGHT(7);
	gizmo_ग_लिखोl(ahb, val, AHB_ARBITRATION_PRIORITY_CTRL);

	val = gizmo_पढ़ोl(ahb, AHB_MEM_PREFETCH_CFG1);
	val &= ~MST_ID(~0);
	val |= PREFETCH_ENB |
		AHBDMA_MST_ID |
		ADDR_BNDRY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_ग_लिखोl(ahb, val, AHB_MEM_PREFETCH_CFG1);

	val = gizmo_पढ़ोl(ahb, AHB_MEM_PREFETCH_CFG2);
	val &= ~MST_ID(~0);
	val |= PREFETCH_ENB |
		USB_MST_ID |
		ADDR_BNDRY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_ग_लिखोl(ahb, val, AHB_MEM_PREFETCH_CFG2);

	val = gizmo_पढ़ोl(ahb, AHB_MEM_PREFETCH_CFG3);
	val &= ~MST_ID(~0);
	val |= PREFETCH_ENB |
		USB3_MST_ID |
		ADDR_BNDRY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_ग_लिखोl(ahb, val, AHB_MEM_PREFETCH_CFG3);

	val = gizmo_पढ़ोl(ahb, AHB_MEM_PREFETCH_CFG4);
	val &= ~MST_ID(~0);
	val |= PREFETCH_ENB |
		USB2_MST_ID |
		ADDR_BNDRY(0xc) |
		INACTIVITY_TIMEOUT(0x1000);
	gizmo_ग_लिखोl(ahb, val, AHB_MEM_PREFETCH_CFG4);
पूर्ण

अटल पूर्णांक tegra_ahb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा tegra_ahb *ahb;
	माप_प्रकार bytes;

	bytes = माप(*ahb) + माप(u32) * ARRAY_SIZE(tegra_ahb_gizmo);
	ahb = devm_kzalloc(&pdev->dev, bytes, GFP_KERNEL);
	अगर (!ahb)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	/* Correct the IP block base address अगर necessary */
	अगर (res &&
	    (res->start & INCORRECT_BASE_ADDR_LOW_BYTE) ==
	    INCORRECT_BASE_ADDR_LOW_BYTE) अणु
		dev_warn(&pdev->dev, "incorrect AHB base address in DT data - enabling workaround\n");
		res->start -= INCORRECT_BASE_ADDR_LOW_BYTE;
	पूर्ण

	ahb->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ahb->regs))
		वापस PTR_ERR(ahb->regs);

	ahb->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ahb);
	tegra_ahb_gizmo_init(ahb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_ahb_of_match[] = अणु
	अणु .compatible = "nvidia,tegra30-ahb", पूर्ण,
	अणु .compatible = "nvidia,tegra20-ahb", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_ahb_driver = अणु
	.probe = tegra_ahb_probe,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = tegra_ahb_of_match,
		.pm = &tegra_ahb_pm,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_ahb_driver);

MODULE_AUTHOR("Hiroshi DOYU <hdoyu@nvidia.com>");
MODULE_DESCRIPTION("Tegra AHB driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
