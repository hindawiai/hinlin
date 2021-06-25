<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CNS3xxx common devices
 *
 * Copyright 2008 Cavium Networks
 *		  Scott Shu
 * Copyright 2010 MontaVista Software, LLC.
 *		  Anton Vorontsov <avorontsov@mvista.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/compiler.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "cns3xxx.h"
#समावेश "pm.h"
#समावेश "core.h"
#समावेश "devices.h"

/*
 * AHCI
 */
अटल काष्ठा resource cns3xxx_ahci_resource[] = अणु
	[0] = अणु
		.start	= CNS3XXX_SATA2_BASE,
		.end	= CNS3XXX_SATA2_BASE + CNS3XXX_SATA2_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_CNS3XXX_SATA,
		.end	= IRQ_CNS3XXX_SATA,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 cns3xxx_ahci_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device cns3xxx_ahci_pdev = अणु
	.name		= "ahci",
	.id		= 0,
	.resource	= cns3xxx_ahci_resource,
	.num_resources	= ARRAY_SIZE(cns3xxx_ahci_resource),
	.dev		= अणु
		.dma_mask		= &cns3xxx_ahci_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init cns3xxx_ahci_init(व्योम)
अणु
	u32 पंचांगp;

	पंचांगp = __raw_पढ़ोl(MISC_SATA_POWER_MODE);
	पंचांगp |= 0x1 << 16; /* Disable SATA PHY 0 from SLUMBER Mode */
	पंचांगp |= 0x1 << 17; /* Disable SATA PHY 1 from SLUMBER Mode */
	__raw_ग_लिखोl(पंचांगp, MISC_SATA_POWER_MODE);

	/* Enable SATA PHY */
	cns3xxx_pwr_घातer_up(0x1 << PM_PLL_HM_PD_CTRL_REG_OFFSET_SATA_PHY0);
	cns3xxx_pwr_घातer_up(0x1 << PM_PLL_HM_PD_CTRL_REG_OFFSET_SATA_PHY1);

	/* Enable SATA Clock */
	cns3xxx_pwr_clk_en(0x1 << PM_CLK_GATE_REG_OFFSET_SATA);

	/* De-Asscer SATA Reset */
	cns3xxx_pwr_soft_rst(CNS3XXX_PWR_SOFTWARE_RST(SATA));

	platक्रमm_device_रेजिस्टर(&cns3xxx_ahci_pdev);
पूर्ण

/*
 * SDHCI
 */
अटल काष्ठा resource cns3xxx_sdhci_resources[] = अणु
	[0] = अणु
		.start = CNS3XXX_SDIO_BASE,
		.end   = CNS3XXX_SDIO_BASE + SZ_4K - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = IRQ_CNS3XXX_SDIO,
		.end   = IRQ_CNS3XXX_SDIO,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cns3xxx_sdhci_pdev = अणु
	.name		= "sdhci-cns3xxx",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(cns3xxx_sdhci_resources),
	.resource	= cns3xxx_sdhci_resources,
पूर्ण;

व्योम __init cns3xxx_sdhci_init(व्योम)
अणु
	u32 __iomem *gpioa = IOMEM(CNS3XXX_MISC_BASE_VIRT + 0x0014);
	u32 gpioa_pins = __raw_पढ़ोl(gpioa);

	/* MMC/SD pins share with GPIOA */
	gpioa_pins |= 0x1fff0004;
	__raw_ग_लिखोl(gpioa_pins, gpioa);

	cns3xxx_pwr_clk_en(CNS3XXX_PWR_CLK_EN(SDIO));
	cns3xxx_pwr_soft_rst(CNS3XXX_PWR_SOFTWARE_RST(SDIO));

	platक्रमm_device_रेजिस्टर(&cns3xxx_sdhci_pdev);
पूर्ण
