<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mach-davinci/devices.c
 *
 * DaVinci platक्रमm device setup/initialization
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <linux/platक्रमm_data/mmc-davinci.h>
#समावेश <linux/platक्रमm_data/edma.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>

#समावेश <mach/hardware.h>
#समावेश <mach/cputype.h>
#समावेश <mach/mux.h>

#समावेश "davinci.h"
#समावेश "irqs.h"

#घोषणा DAVINCI_I2C_BASE	     0x01C21000
#घोषणा DAVINCI_ATA_BASE	     0x01C66000
#घोषणा DAVINCI_MMCSD0_BASE	     0x01E10000
#घोषणा DM355_MMCSD0_BASE	     0x01E11000
#घोषणा DM355_MMCSD1_BASE	     0x01E00000
#घोषणा DM365_MMCSD0_BASE	     0x01D11000
#घोषणा DM365_MMCSD1_BASE	     0x01D00000

व्योम __iomem  *davinci_sysmod_base;

व्योम davinci_map_sysmod(व्योम)
अणु
	davinci_sysmod_base = ioremap(DAVINCI_SYSTEM_MODULE_BASE,
					      0x800);
	/*
	 * Throw a bug since a lot of board initialization code depends
	 * on प्रणाली module availability. ioremap() failing this early
	 * need careful looking पूर्णांकo anyway.
	 */
	BUG_ON(!davinci_sysmod_base);
पूर्ण

अटल काष्ठा resource i2c_resources[] = अणु
	अणु
		.start		= DAVINCI_I2C_BASE,
		.end		= DAVINCI_I2C_BASE + 0x40,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= DAVINCI_INTC_IRQ(IRQ_I2C),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_i2c_device = अणु
	.name           = "i2c_davinci",
	.id             = 1,
	.num_resources	= ARRAY_SIZE(i2c_resources),
	.resource	= i2c_resources,
पूर्ण;

व्योम __init davinci_init_i2c(काष्ठा davinci_i2c_platक्रमm_data *pdata)
अणु
	अगर (cpu_is_davinci_dm644x())
		davinci_cfg_reg(DM644X_I2C);

	davinci_i2c_device.dev.platक्रमm_data = pdata;
	(व्योम) platक्रमm_device_रेजिस्टर(&davinci_i2c_device);
पूर्ण

अटल काष्ठा resource ide_resources[] = अणु
	अणु
		.start		= DAVINCI_ATA_BASE,
		.end		= DAVINCI_ATA_BASE + 0x7ff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= DAVINCI_INTC_IRQ(IRQ_IDE),
		.end		= DAVINCI_INTC_IRQ(IRQ_IDE),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 ide_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device ide_device = अणु
	.name           = "palm_bk3710",
	.id             = -1,
	.resource       = ide_resources,
	.num_resources  = ARRAY_SIZE(ide_resources),
	.dev = अणु
		.dma_mask		= &ide_dma_mask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init davinci_init_ide(व्योम)
अणु
	अगर (cpu_is_davinci_dm644x()) अणु
		davinci_cfg_reg(DM644X_HPIEN_DISABLE);
		davinci_cfg_reg(DM644X_ATAEN);
		davinci_cfg_reg(DM644X_HसूचीEN);
	पूर्ण अन्यथा अगर (cpu_is_davinci_dm646x()) अणु
		/* IRQ_DM646X_IDE is the same as IRQ_IDE */
		davinci_cfg_reg(DM646X_ATAEN);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	platक्रमm_device_रेजिस्टर(&ide_device);
पूर्ण

#अगर IS_ENABLED(CONFIG_MMC_DAVINCI)

अटल u64 mmcsd0_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource mmcsd0_resources[] = अणु
	अणु
		/* dअगरferent on dm355 */
		.start = DAVINCI_MMCSD0_BASE,
		.end   = DAVINCI_MMCSD0_BASE + SZ_4K - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	/* IRQs:  MMC/SD, then SDIO */
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_MMCINT),
		.flags = IORESOURCE_IRQ,
	पूर्ण, अणु
		/* dअगरferent on dm355 */
		.start = DAVINCI_INTC_IRQ(IRQ_SDIOINT),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_mmcsd0_device = अणु
	.name = "dm6441-mmc",
	.id = 0,
	.dev = अणु
		.dma_mask = &mmcsd0_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources = ARRAY_SIZE(mmcsd0_resources),
	.resource = mmcsd0_resources,
पूर्ण;

अटल u64 mmcsd1_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource mmcsd1_resources[] = अणु
	अणु
		.start = DM355_MMCSD1_BASE,
		.end   = DM355_MMCSD1_BASE + SZ_4K - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	/* IRQs:  MMC/SD, then SDIO */
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DM355_MMCINT1),
		.flags = IORESOURCE_IRQ,
	पूर्ण, अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DM355_SDIOINT1),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_mmcsd1_device = अणु
	.name = "dm6441-mmc",
	.id = 1,
	.dev = अणु
		.dma_mask = &mmcsd1_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources = ARRAY_SIZE(mmcsd1_resources),
	.resource = mmcsd1_resources,
पूर्ण;


व्योम __init davinci_setup_mmc(पूर्णांक module, काष्ठा davinci_mmc_config *config)
अणु
	काष्ठा platक्रमm_device	*pdev = शून्य;

	अगर (WARN_ON(cpu_is_davinci_dm646x()))
		वापस;

	/* REVISIT: update PINMUX, ARM_IRQMUX, and EDMA_EVTMUX here too;
	 * क्रम example अगर MMCSD1 is used क्रम SDIO, maybe DAT2 is unused.
	 *
	 * FIXME dm6441 (no MMC/SD), dm357 (one), and dm335 (two) are
	 * not handled right here ...
	 */
	चयन (module) अणु
	हाल 1:
		अगर (cpu_is_davinci_dm355()) अणु
			/* REVISIT we may not need all these pins अगर e.g. this
			 * is a hard-wired SDIO device...
			 */
			davinci_cfg_reg(DM355_SD1_CMD);
			davinci_cfg_reg(DM355_SD1_CLK);
			davinci_cfg_reg(DM355_SD1_DATA0);
			davinci_cfg_reg(DM355_SD1_DATA1);
			davinci_cfg_reg(DM355_SD1_DATA2);
			davinci_cfg_reg(DM355_SD1_DATA3);
		पूर्ण अन्यथा अगर (cpu_is_davinci_dm365()) अणु
			/* Configure pull करोwn control */
			अचिन्हित v;

			v = __raw_पढ़ोl(DAVINCI_SYSMOD_VIRT(SYSMOD_PUPDCTL1));
			__raw_ग_लिखोl(v & ~0xfc0,
					DAVINCI_SYSMOD_VIRT(SYSMOD_PUPDCTL1));

			mmcsd1_resources[0].start = DM365_MMCSD1_BASE;
			mmcsd1_resources[0].end = DM365_MMCSD1_BASE +
							SZ_4K - 1;
			mmcsd1_resources[2].start = DAVINCI_INTC_IRQ(
							IRQ_DM365_SDIOINT1);
			davinci_mmcsd1_device.name = "da830-mmc";
		पूर्ण अन्यथा
			अवरोध;

		pdev = &davinci_mmcsd1_device;
		अवरोध;
	हाल 0:
		अगर (cpu_is_davinci_dm355()) अणु
			mmcsd0_resources[0].start = DM355_MMCSD0_BASE;
			mmcsd0_resources[0].end = DM355_MMCSD0_BASE + SZ_4K - 1;
			mmcsd0_resources[2].start = DAVINCI_INTC_IRQ(
							IRQ_DM355_SDIOINT0);

			/* expose all 6 MMC0 संकेतs:  CLK, CMD, DATA[0..3] */
			davinci_cfg_reg(DM355_MMCSD0);

			/* enable RX EDMA */
			davinci_cfg_reg(DM355_EVT26_MMC0_RX);
		पूर्ण अन्यथा अगर (cpu_is_davinci_dm365()) अणु
			mmcsd0_resources[0].start = DM365_MMCSD0_BASE;
			mmcsd0_resources[0].end = DM365_MMCSD0_BASE +
							SZ_4K - 1;
			mmcsd0_resources[2].start = DAVINCI_INTC_IRQ(
							IRQ_DM365_SDIOINT0);
			davinci_mmcsd0_device.name = "da830-mmc";
		पूर्ण अन्यथा अगर (cpu_is_davinci_dm644x()) अणु
			/* REVISIT: should this be in board-init code? */
			/* Power-on 3.3V IO cells */
			__raw_ग_लिखोl(0,
				DAVINCI_SYSMOD_VIRT(SYSMOD_VDD3P3VPWDN));
			/*Set up the pull regiter क्रम MMC */
			davinci_cfg_reg(DM644X_MSTK);
		पूर्ण

		pdev = &davinci_mmcsd0_device;
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!pdev))
		वापस;

	pdev->dev.platक्रमm_data = config;
	platक्रमm_device_रेजिस्टर(pdev);
पूर्ण

#अन्यथा

व्योम __init davinci_setup_mmc(पूर्णांक module, काष्ठा davinci_mmc_config *config)
अणु
पूर्ण

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल काष्ठा resource wdt_resources[] = अणु
	अणु
		.start	= DAVINCI_WDOG_BASE,
		.end	= DAVINCI_WDOG_BASE + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_wdt_device = अणु
	.name		= "davinci-wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(wdt_resources),
	.resource	= wdt_resources,
पूर्ण;

पूर्णांक davinci_init_wdt(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&davinci_wdt_device);
पूर्ण

अटल काष्ठा platक्रमm_device davinci_gpio_device = अणु
	.name	= "davinci_gpio",
	.id	= -1,
पूर्ण;

पूर्णांक davinci_gpio_रेजिस्टर(काष्ठा resource *res, पूर्णांक size, व्योम *pdata)
अणु
	davinci_gpio_device.resource = res;
	davinci_gpio_device.num_resources = size;
	davinci_gpio_device.dev.platक्रमm_data = pdata;
	वापस platक्रमm_device_रेजिस्टर(&davinci_gpio_device);
पूर्ण
