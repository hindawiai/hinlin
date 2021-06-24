<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DA8XX/OMAP L1XX platक्रमm device data
 *
 * Copyright (c) 2007-2009, MontaVista Software, Inc. <source@mvista.com>
 * Derived from code that was:
 *	Copyright (C) 2006 Komal Shah <komal_shah802003@yahoo.com>
 */
#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/serial_8250.h>

#समावेश <mach/common.h>
#समावेश <mach/cputype.h>
#समावेश <mach/da8xx.h>

#समावेश "asp.h"
#समावेश "cpuidle.h"
#समावेश "irqs.h"
#समावेश "sram.h"

#घोषणा DA8XX_TPCC_BASE			0x01c00000
#घोषणा DA8XX_TPTC0_BASE		0x01c08000
#घोषणा DA8XX_TPTC1_BASE		0x01c08400
#घोषणा DA8XX_WDOG_BASE			0x01c21000 /* DA8XX_TIMER64P1_BASE */
#घोषणा DA8XX_I2C0_BASE			0x01c22000
#घोषणा DA8XX_RTC_BASE			0x01c23000
#घोषणा DA8XX_PRUSS_MEM_BASE		0x01c30000
#घोषणा DA8XX_MMCSD0_BASE		0x01c40000
#घोषणा DA8XX_SPI0_BASE			0x01c41000
#घोषणा DA830_SPI1_BASE			0x01e12000
#घोषणा DA8XX_LCD_CNTRL_BASE		0x01e13000
#घोषणा DA850_SATA_BASE			0x01e18000
#घोषणा DA850_MMCSD1_BASE		0x01e1b000
#घोषणा DA8XX_EMAC_CPPI_PORT_BASE	0x01e20000
#घोषणा DA8XX_EMAC_CPGMACSS_BASE	0x01e22000
#घोषणा DA8XX_EMAC_CPGMAC_BASE		0x01e23000
#घोषणा DA8XX_EMAC_MDIO_BASE		0x01e24000
#घोषणा DA8XX_I2C1_BASE			0x01e28000
#घोषणा DA850_TPCC1_BASE		0x01e30000
#घोषणा DA850_TPTC2_BASE		0x01e38000
#घोषणा DA850_SPI1_BASE			0x01f0e000
#घोषणा DA8XX_DDR2_CTL_BASE		0xb0000000

#घोषणा DA8XX_EMAC_CTRL_REG_OFFSET	0x3000
#घोषणा DA8XX_EMAC_MOD_REG_OFFSET	0x2000
#घोषणा DA8XX_EMAC_RAM_OFFSET		0x0000
#घोषणा DA8XX_EMAC_CTRL_RAM_SIZE	SZ_8K

व्योम __iomem *da8xx_syscfg0_base;
व्योम __iomem *da8xx_syscfg1_base;

अटल काष्ठा plat_serial8250_port da8xx_serial0_pdata[] = अणु
	अणु
		.mapbase	= DA8XX_UART0_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_DA8XX_UARTINT0),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
					UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;
अटल काष्ठा plat_serial8250_port da8xx_serial1_pdata[] = अणु
	अणु
		.mapbase	= DA8XX_UART1_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_DA8XX_UARTINT1),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
					UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;
अटल काष्ठा plat_serial8250_port da8xx_serial2_pdata[] = अणु
	अणु
		.mapbase	= DA8XX_UART2_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_DA8XX_UARTINT2),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
					UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device da8xx_serial_device[] = अणु
	अणु
		.name	= "serial8250",
		.id	= PLAT8250_DEV_PLATFORM,
		.dev	= अणु
			.platक्रमm_data	= da8xx_serial0_pdata,
		पूर्ण
	पूर्ण,
	अणु
		.name	= "serial8250",
		.id	= PLAT8250_DEV_PLATFORM1,
		.dev	= अणु
			.platक्रमm_data	= da8xx_serial1_pdata,
		पूर्ण
	पूर्ण,
	अणु
		.name	= "serial8250",
		.id	= PLAT8250_DEV_PLATFORM2,
		.dev	= अणु
			.platक्रमm_data	= da8xx_serial2_pdata,
		पूर्ण
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल s8 da8xx_queue_priority_mapping[][2] = अणु
	/* अणुevent queue no, Priorityपूर्ण */
	अणु0, 3पूर्ण,
	अणु1, 7पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल s8 da850_queue_priority_mapping[][2] = अणु
	/* अणुevent queue no, Priorityपूर्ण */
	अणु0, 3पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल काष्ठा edma_soc_info da8xx_edma0_pdata = अणु
	.queue_priority_mapping	= da8xx_queue_priority_mapping,
	.शेष_queue		= EVENTQ_1,
पूर्ण;

अटल काष्ठा edma_soc_info da850_edma1_pdata = अणु
	.queue_priority_mapping	= da850_queue_priority_mapping,
	.शेष_queue		= EVENTQ_0,
पूर्ण;

अटल काष्ठा resource da8xx_edma0_resources[] = अणु
	अणु
		.name	= "edma3_cc",
		.start	= DA8XX_TPCC_BASE,
		.end	= DA8XX_TPCC_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_tc0",
		.start	= DA8XX_TPTC0_BASE,
		.end	= DA8XX_TPTC0_BASE + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_tc1",
		.start	= DA8XX_TPTC1_BASE,
		.end	= DA8XX_TPTC1_BASE + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_ccint",
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_CCINT0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "edma3_ccerrint",
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_CCERRINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource da850_edma1_resources[] = अणु
	अणु
		.name	= "edma3_cc",
		.start	= DA850_TPCC1_BASE,
		.end	= DA850_TPCC1_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_tc0",
		.start	= DA850_TPTC2_BASE,
		.end	= DA850_TPTC2_BASE + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_ccint",
		.start	= DAVINCI_INTC_IRQ(IRQ_DA850_CCINT1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "edma3_ccerrint",
		.start	= DAVINCI_INTC_IRQ(IRQ_DA850_CCERRINT1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info da8xx_edma0_device __initस्थिर = अणु
	.name		= "edma",
	.id		= 0,
	.dma_mask	= DMA_BIT_MASK(32),
	.res		= da8xx_edma0_resources,
	.num_res	= ARRAY_SIZE(da8xx_edma0_resources),
	.data		= &da8xx_edma0_pdata,
	.size_data	= माप(da8xx_edma0_pdata),
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info da850_edma1_device __initस्थिर = अणु
	.name		= "edma",
	.id		= 1,
	.dma_mask	= DMA_BIT_MASK(32),
	.res		= da850_edma1_resources,
	.num_res	= ARRAY_SIZE(da850_edma1_resources),
	.data		= &da850_edma1_pdata,
	.size_data	= माप(da850_edma1_pdata),
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map da830_edma_map[] = अणु
	अणु "davinci-mcasp.0", "rx", EDMA_FILTER_PARAM(0, 0) पूर्ण,
	अणु "davinci-mcasp.0", "tx", EDMA_FILTER_PARAM(0, 1) पूर्ण,
	अणु "davinci-mcasp.1", "rx", EDMA_FILTER_PARAM(0, 2) पूर्ण,
	अणु "davinci-mcasp.1", "tx", EDMA_FILTER_PARAM(0, 3) पूर्ण,
	अणु "davinci-mcasp.2", "rx", EDMA_FILTER_PARAM(0, 4) पूर्ण,
	अणु "davinci-mcasp.2", "tx", EDMA_FILTER_PARAM(0, 5) पूर्ण,
	अणु "spi_davinci.0", "rx", EDMA_FILTER_PARAM(0, 14) पूर्ण,
	अणु "spi_davinci.0", "tx", EDMA_FILTER_PARAM(0, 15) पूर्ण,
	अणु "da830-mmc.0", "rx", EDMA_FILTER_PARAM(0, 16) पूर्ण,
	अणु "da830-mmc.0", "tx", EDMA_FILTER_PARAM(0, 17) पूर्ण,
	अणु "spi_davinci.1", "rx", EDMA_FILTER_PARAM(0, 18) पूर्ण,
	अणु "spi_davinci.1", "tx", EDMA_FILTER_PARAM(0, 19) पूर्ण,
पूर्ण;

पूर्णांक __init da830_रेजिस्टर_edma(काष्ठा edma_rsv_info *rsv)
अणु
	काष्ठा platक्रमm_device *edma_pdev;

	da8xx_edma0_pdata.rsv = rsv;

	da8xx_edma0_pdata.slave_map = da830_edma_map;
	da8xx_edma0_pdata.slavecnt = ARRAY_SIZE(da830_edma_map);

	edma_pdev = platक्रमm_device_रेजिस्टर_full(&da8xx_edma0_device);
	वापस PTR_ERR_OR_ZERO(edma_pdev);
पूर्ण

अटल स्थिर काष्ठा dma_slave_map da850_edma0_map[] = अणु
	अणु "davinci-mcasp.0", "rx", EDMA_FILTER_PARAM(0, 0) पूर्ण,
	अणु "davinci-mcasp.0", "tx", EDMA_FILTER_PARAM(0, 1) पूर्ण,
	अणु "davinci-mcbsp.0", "rx", EDMA_FILTER_PARAM(0, 2) पूर्ण,
	अणु "davinci-mcbsp.0", "tx", EDMA_FILTER_PARAM(0, 3) पूर्ण,
	अणु "davinci-mcbsp.1", "rx", EDMA_FILTER_PARAM(0, 4) पूर्ण,
	अणु "davinci-mcbsp.1", "tx", EDMA_FILTER_PARAM(0, 5) पूर्ण,
	अणु "spi_davinci.0", "rx", EDMA_FILTER_PARAM(0, 14) पूर्ण,
	अणु "spi_davinci.0", "tx", EDMA_FILTER_PARAM(0, 15) पूर्ण,
	अणु "da830-mmc.0", "rx", EDMA_FILTER_PARAM(0, 16) पूर्ण,
	अणु "da830-mmc.0", "tx", EDMA_FILTER_PARAM(0, 17) पूर्ण,
	अणु "spi_davinci.1", "rx", EDMA_FILTER_PARAM(0, 18) पूर्ण,
	अणु "spi_davinci.1", "tx", EDMA_FILTER_PARAM(0, 19) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map da850_edma1_map[] = अणु
	अणु "da830-mmc.1", "rx", EDMA_FILTER_PARAM(1, 28) पूर्ण,
	अणु "da830-mmc.1", "tx", EDMA_FILTER_PARAM(1, 29) पूर्ण,
पूर्ण;

पूर्णांक __init da850_रेजिस्टर_edma(काष्ठा edma_rsv_info *rsv[2])
अणु
	काष्ठा platक्रमm_device *edma_pdev;

	अगर (rsv) अणु
		da8xx_edma0_pdata.rsv = rsv[0];
		da850_edma1_pdata.rsv = rsv[1];
	पूर्ण

	da8xx_edma0_pdata.slave_map = da850_edma0_map;
	da8xx_edma0_pdata.slavecnt = ARRAY_SIZE(da850_edma0_map);

	edma_pdev = platक्रमm_device_रेजिस्टर_full(&da8xx_edma0_device);
	अगर (IS_ERR(edma_pdev)) अणु
		pr_warn("%s: Failed to register eDMA0\n", __func__);
		वापस PTR_ERR(edma_pdev);
	पूर्ण

	da850_edma1_pdata.slave_map = da850_edma1_map;
	da850_edma1_pdata.slavecnt = ARRAY_SIZE(da850_edma1_map);

	edma_pdev = platक्रमm_device_रेजिस्टर_full(&da850_edma1_device);
	वापस PTR_ERR_OR_ZERO(edma_pdev);
पूर्ण

अटल काष्ठा resource da8xx_i2c_resources0[] = अणु
	अणु
		.start	= DA8XX_I2C0_BASE,
		.end	= DA8XX_I2C0_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_I2CINT0),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_I2CINT0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_i2c_device0 = अणु
	.name		= "i2c_davinci",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(da8xx_i2c_resources0),
	.resource	= da8xx_i2c_resources0,
पूर्ण;

अटल काष्ठा resource da8xx_i2c_resources1[] = अणु
	अणु
		.start	= DA8XX_I2C1_BASE,
		.end	= DA8XX_I2C1_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_I2CINT1),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_I2CINT1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_i2c_device1 = अणु
	.name		= "i2c_davinci",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(da8xx_i2c_resources1),
	.resource	= da8xx_i2c_resources1,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_i2c(पूर्णांक instance,
		काष्ठा davinci_i2c_platक्रमm_data *pdata)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (instance == 0)
		pdev = &da8xx_i2c_device0;
	अन्यथा अगर (instance == 1)
		pdev = &da8xx_i2c_device1;
	अन्यथा
		वापस -EINVAL;

	pdev->dev.platक्रमm_data = pdata;
	वापस platक्रमm_device_रेजिस्टर(pdev);
पूर्ण

अटल काष्ठा resource da8xx_watchकरोg_resources[] = अणु
	अणु
		.start	= DA8XX_WDOG_BASE,
		.end	= DA8XX_WDOG_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_wdt_device = अणु
	.name		= "davinci-wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(da8xx_watchकरोg_resources),
	.resource	= da8xx_watchकरोg_resources,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_watchकरोg(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&da8xx_wdt_device);
पूर्ण

अटल काष्ठा resource da8xx_emac_resources[] = अणु
	अणु
		.start	= DA8XX_EMAC_CPPI_PORT_BASE,
		.end	= DA8XX_EMAC_CPPI_PORT_BASE + SZ_16K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_RX_THRESH_PULSE),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_RX_THRESH_PULSE),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_RX_PULSE),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_RX_PULSE),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_TX_PULSE),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_TX_PULSE),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_MISC_PULSE),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_C0_MISC_PULSE),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा emac_platक्रमm_data da8xx_emac_pdata = अणु
	.ctrl_reg_offset	= DA8XX_EMAC_CTRL_REG_OFFSET,
	.ctrl_mod_reg_offset	= DA8XX_EMAC_MOD_REG_OFFSET,
	.ctrl_ram_offset	= DA8XX_EMAC_RAM_OFFSET,
	.ctrl_ram_size		= DA8XX_EMAC_CTRL_RAM_SIZE,
	.version		= EMAC_VERSION_2,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_emac_device = अणु
	.name		= "davinci_emac",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data	= &da8xx_emac_pdata,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(da8xx_emac_resources),
	.resource	= da8xx_emac_resources,
पूर्ण;

अटल काष्ठा resource da8xx_mdio_resources[] = अणु
	अणु
		.start	= DA8XX_EMAC_MDIO_BASE,
		.end	= DA8XX_EMAC_MDIO_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_mdio_device = अणु
	.name		= "davinci_mdio",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(da8xx_mdio_resources),
	.resource	= da8xx_mdio_resources,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_emac(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_device_रेजिस्टर(&da8xx_mdio_device);
	अगर (ret < 0)
		वापस ret;

	वापस platक्रमm_device_रेजिस्टर(&da8xx_emac_device);
पूर्ण

अटल काष्ठा resource da830_mcasp1_resources[] = अणु
	अणु
		.name	= "mpu",
		.start	= DAVINCI_DA830_MCASP1_REG_BASE,
		.end	= DAVINCI_DA830_MCASP1_REG_BASE + (SZ_1K * 12) - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	/* TX event */
	अणु
		.name	= "tx",
		.start	= DAVINCI_DA830_DMA_MCASP1_AXEVT,
		.end	= DAVINCI_DA830_DMA_MCASP1_AXEVT,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	/* RX event */
	अणु
		.name	= "rx",
		.start	= DAVINCI_DA830_DMA_MCASP1_AREVT,
		.end	= DAVINCI_DA830_DMA_MCASP1_AREVT,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.name	= "common",
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_MCASPINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da830_mcasp1_device = अणु
	.name		= "davinci-mcasp",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(da830_mcasp1_resources),
	.resource	= da830_mcasp1_resources,
पूर्ण;

अटल काष्ठा resource da830_mcasp2_resources[] = अणु
	अणु
		.name	= "mpu",
		.start	= DAVINCI_DA830_MCASP2_REG_BASE,
		.end	= DAVINCI_DA830_MCASP2_REG_BASE + (SZ_1K * 12) - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	/* TX event */
	अणु
		.name	= "tx",
		.start	= DAVINCI_DA830_DMA_MCASP2_AXEVT,
		.end	= DAVINCI_DA830_DMA_MCASP2_AXEVT,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	/* RX event */
	अणु
		.name	= "rx",
		.start	= DAVINCI_DA830_DMA_MCASP2_AREVT,
		.end	= DAVINCI_DA830_DMA_MCASP2_AREVT,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.name	= "common",
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_MCASPINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da830_mcasp2_device = अणु
	.name		= "davinci-mcasp",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(da830_mcasp2_resources),
	.resource	= da830_mcasp2_resources,
पूर्ण;

अटल काष्ठा resource da850_mcasp_resources[] = अणु
	अणु
		.name	= "mpu",
		.start	= DAVINCI_DA8XX_MCASP0_REG_BASE,
		.end	= DAVINCI_DA8XX_MCASP0_REG_BASE + (SZ_1K * 12) - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	/* TX event */
	अणु
		.name	= "tx",
		.start	= DAVINCI_DA8XX_DMA_MCASP0_AXEVT,
		.end	= DAVINCI_DA8XX_DMA_MCASP0_AXEVT,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	/* RX event */
	अणु
		.name	= "rx",
		.start	= DAVINCI_DA8XX_DMA_MCASP0_AREVT,
		.end	= DAVINCI_DA8XX_DMA_MCASP0_AREVT,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.name	= "common",
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_MCASPINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_mcasp_device = अणु
	.name		= "davinci-mcasp",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(da850_mcasp_resources),
	.resource	= da850_mcasp_resources,
पूर्ण;

व्योम __init da8xx_रेजिस्टर_mcasp(पूर्णांक id, काष्ठा snd_platक्रमm_data *pdata)
अणु
	काष्ठा platक्रमm_device *pdev;

	चयन (id) अणु
	हाल 0:
		/* Valid क्रम DA830/OMAP-L137 or DA850/OMAP-L138 */
		pdev = &da850_mcasp_device;
		अवरोध;
	हाल 1:
		/* Valid क्रम DA830/OMAP-L137 only */
		अगर (!cpu_is_davinci_da830())
			वापस;
		pdev = &da830_mcasp1_device;
		अवरोध;
	हाल 2:
		/* Valid क्रम DA830/OMAP-L137 only */
		अगर (!cpu_is_davinci_da830())
			वापस;
		pdev = &da830_mcasp2_device;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	pdev->dev.platक्रमm_data = pdata;
	platक्रमm_device_रेजिस्टर(pdev);
पूर्ण

अटल काष्ठा resource da8xx_pruss_resources[] = अणु
	अणु
		.start	= DA8XX_PRUSS_MEM_BASE,
		.end	= DA8XX_PRUSS_MEM_BASE + 0xFFFF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT0),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT1),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT2),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT2),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT3),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT3),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT4),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT4),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT5),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT5),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT6),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT6),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT7),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_EVTOUT7),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा uio_pruss_pdata da8xx_uio_pruss_pdata = अणु
	.pपूर्णांकc_base	= 0x4000,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_uio_pruss_dev = अणु
	.name		= "pruss_uio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(da8xx_pruss_resources),
	.resource	= da8xx_pruss_resources,
	.dev		= अणु
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &da8xx_uio_pruss_pdata,
	पूर्ण
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_uio_pruss(व्योम)
अणु
	da8xx_uio_pruss_pdata.sram_pool = sram_get_gen_pool();
	वापस platक्रमm_device_रेजिस्टर(&da8xx_uio_pruss_dev);
पूर्ण

अटल काष्ठा lcd_ctrl_config lcd_cfg = अणु
	.panel_shade		= COLOR_ACTIVE,
	.bpp			= 16,
पूर्ण;

काष्ठा da8xx_lcdc_platक्रमm_data sharp_lcd035q3dg01_pdata = अणु
	.manu_name		= "sharp",
	.controller_data	= &lcd_cfg,
	.type			= "Sharp_LCD035Q3DG01",
पूर्ण;

काष्ठा da8xx_lcdc_platक्रमm_data sharp_lk043t1dg01_pdata = अणु
	.manu_name		= "sharp",
	.controller_data	= &lcd_cfg,
	.type			= "Sharp_LK043T1DG01",
पूर्ण;

अटल काष्ठा resource da8xx_lcdc_resources[] = अणु
	[0] = अणु /* रेजिस्टरs */
		.start  = DA8XX_LCD_CNTRL_BASE,
		.end    = DA8XX_LCD_CNTRL_BASE + SZ_4K - 1,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु /* पूर्णांकerrupt */
		.start  = DAVINCI_INTC_IRQ(IRQ_DA8XX_LCDINT),
		.end    = DAVINCI_INTC_IRQ(IRQ_DA8XX_LCDINT),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_lcdc_device = अणु
	.name		= "da8xx_lcdc",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(da8xx_lcdc_resources),
	.resource	= da8xx_lcdc_resources,
	.dev		= अणु
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_lcdc(काष्ठा da8xx_lcdc_platक्रमm_data *pdata)
अणु
	da8xx_lcdc_device.dev.platक्रमm_data = pdata;
	वापस platक्रमm_device_रेजिस्टर(&da8xx_lcdc_device);
पूर्ण

अटल काष्ठा resource da8xx_gpio_resources[] = अणु
	अणु /* रेजिस्टरs */
		.start	= DA8XX_GPIO_BASE,
		.end	= DA8XX_GPIO_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु /* पूर्णांकerrupt */
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO0),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO1),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO2),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO2),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO3),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO3),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO4),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO4),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO5),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO5),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO6),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO6),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO7),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO7),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO8),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_GPIO8),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_gpio_device = अणु
	.name		= "davinci_gpio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(da8xx_gpio_resources),
	.resource	= da8xx_gpio_resources,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_gpio(व्योम *pdata)
अणु
	da8xx_gpio_device.dev.platक्रमm_data = pdata;
	वापस platक्रमm_device_रेजिस्टर(&da8xx_gpio_device);
पूर्ण

अटल काष्ठा resource da8xx_mmcsd0_resources[] = अणु
	अणु		/* रेजिस्टरs */
		.start	= DA8XX_MMCSD0_BASE,
		.end	= DA8XX_MMCSD0_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु		/* पूर्णांकerrupt */
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_MMCSDINT0),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_MMCSDINT0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_mmcsd0_device = अणु
	.name		= "da830-mmc",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(da8xx_mmcsd0_resources),
	.resource	= da8xx_mmcsd0_resources,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_mmcsd0(काष्ठा davinci_mmc_config *config)
अणु
	da8xx_mmcsd0_device.dev.platक्रमm_data = config;
	वापस platक्रमm_device_रेजिस्टर(&da8xx_mmcsd0_device);
पूर्ण

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
अटल काष्ठा resource da850_mmcsd1_resources[] = अणु
	अणु		/* रेजिस्टरs */
		.start	= DA850_MMCSD1_BASE,
		.end	= DA850_MMCSD1_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु		/* पूर्णांकerrupt */
		.start	= DAVINCI_INTC_IRQ(IRQ_DA850_MMCSDINT0_1),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA850_MMCSDINT0_1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_mmcsd1_device = अणु
	.name		= "da830-mmc",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(da850_mmcsd1_resources),
	.resource	= da850_mmcsd1_resources,
पूर्ण;

पूर्णांक __init da850_रेजिस्टर_mmcsd1(काष्ठा davinci_mmc_config *config)
अणु
	da850_mmcsd1_device.dev.platक्रमm_data = config;
	वापस platक्रमm_device_रेजिस्टर(&da850_mmcsd1_device);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा resource da8xx_rproc_resources[] = अणु
	अणु /* DSP boot address */
		.name		= "host1cfg",
		.start		= DA8XX_SYSCFG0_BASE + DA8XX_HOST1CFG_REG,
		.end		= DA8XX_SYSCFG0_BASE + DA8XX_HOST1CFG_REG + 3,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु /* DSP पूर्णांकerrupt रेजिस्टरs */
		.name		= "chipsig",
		.start		= DA8XX_SYSCFG0_BASE + DA8XX_CHIPSIG_REG,
		.end		= DA8XX_SYSCFG0_BASE + DA8XX_CHIPSIG_REG + 7,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु /* DSP L2 RAM */
		.name		= "l2sram",
		.start		= DA8XX_DSP_L2_RAM_BASE,
		.end		= DA8XX_DSP_L2_RAM_BASE + SZ_256K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु /* DSP L1P RAM */
		.name		= "l1pram",
		.start		= DA8XX_DSP_L1P_RAM_BASE,
		.end		= DA8XX_DSP_L1P_RAM_BASE + SZ_32K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु /* DSP L1D RAM */
		.name		= "l1dram",
		.start		= DA8XX_DSP_L1D_RAM_BASE,
		.end		= DA8XX_DSP_L1D_RAM_BASE + SZ_32K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु /* dsp irq */
		.start		= DAVINCI_INTC_IRQ(IRQ_DA8XX_CHIPINT0),
		.end		= DAVINCI_INTC_IRQ(IRQ_DA8XX_CHIPINT0),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_dsp = अणु
	.name	= "davinci-rproc",
	.dev	= अणु
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources	= ARRAY_SIZE(da8xx_rproc_resources),
	.resource	= da8xx_rproc_resources,
पूर्ण;

अटल bool rproc_mem_inited __initdata;

#अगर IS_ENABLED(CONFIG_DA8XX_REMOTEPROC)

अटल phys_addr_t rproc_base __initdata;
अटल अचिन्हित दीर्घ rproc_size __initdata;

अटल पूर्णांक __init early_rproc_mem(अक्षर *p)
अणु
	अक्षर *endp;

	अगर (p == शून्य)
		वापस 0;

	rproc_size = memparse(p, &endp);
	अगर (*endp == '@')
		rproc_base = memparse(endp + 1, शून्य);

	वापस 0;
पूर्ण
early_param("rproc_mem", early_rproc_mem);

व्योम __init da8xx_rproc_reserve_cma(व्योम)
अणु
	काष्ठा cma *cma;
	पूर्णांक ret;

	अगर (!rproc_base || !rproc_size) अणु
		pr_err("%s: 'rproc_mem=nn@address' badly specified\n"
		       "    'nn' and 'address' must both be non-zero\n",
		       __func__);

		वापस;
	पूर्ण

	pr_info("%s: reserving 0x%lx @ 0x%lx...\n",
		__func__, rproc_size, (अचिन्हित दीर्घ)rproc_base);

	ret = dma_contiguous_reserve_area(rproc_size, rproc_base, 0, &cma,
			true);
	अगर (ret) अणु
		pr_err("%s: dma_contiguous_reserve_area failed %d\n",
			__func__, ret);
		वापस;
	पूर्ण
	da8xx_dsp.dev.cma_area = cma;
	rproc_mem_inited = true;
पूर्ण
#अन्यथा

व्योम __init da8xx_rproc_reserve_cma(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

पूर्णांक __init da8xx_रेजिस्टर_rproc(व्योम)
अणु
	पूर्णांक ret;

	अगर (!rproc_mem_inited) अणु
		pr_warn("%s: memory not reserved for DSP, not registering DSP device\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	ret = platक्रमm_device_रेजिस्टर(&da8xx_dsp);
	अगर (ret)
		pr_err("%s: can't register DSP device: %d\n", __func__, ret);

	वापस ret;
पूर्ण;

अटल काष्ठा resource da8xx_rtc_resources[] = अणु
	अणु
		.start		= DA8XX_RTC_BASE,
		.end		= DA8XX_RTC_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु /* समयr irq */
		.start		= DAVINCI_INTC_IRQ(IRQ_DA8XX_RTC),
		.end		= DAVINCI_INTC_IRQ(IRQ_DA8XX_RTC),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु /* alarm irq */
		.start		= DAVINCI_INTC_IRQ(IRQ_DA8XX_RTC),
		.end		= DAVINCI_INTC_IRQ(IRQ_DA8XX_RTC),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_rtc_device = अणु
	.name           = "da830-rtc",
	.id             = -1,
	.num_resources	= ARRAY_SIZE(da8xx_rtc_resources),
	.resource	= da8xx_rtc_resources,
पूर्ण;

पूर्णांक da8xx_रेजिस्टर_rtc(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&da8xx_rtc_device);
पूर्ण

अटल व्योम __iomem *da8xx_ddr2_ctlr_base;
व्योम __iomem * __init da8xx_get_mem_ctlr(व्योम)
अणु
	अगर (da8xx_ddr2_ctlr_base)
		वापस da8xx_ddr2_ctlr_base;

	da8xx_ddr2_ctlr_base = ioremap(DA8XX_DDR2_CTL_BASE, SZ_32K);
	अगर (!da8xx_ddr2_ctlr_base)
		pr_warn("%s: Unable to map DDR2 controller", __func__);

	वापस da8xx_ddr2_ctlr_base;
पूर्ण

अटल काष्ठा resource da8xx_cpuidle_resources[] = अणु
	अणु
		.start		= DA8XX_DDR2_CTL_BASE,
		.end		= DA8XX_DDR2_CTL_BASE + SZ_32K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

/* DA8XX devices support DDR2 घातer करोwn */
अटल काष्ठा davinci_cpuidle_config da8xx_cpuidle_pdata = अणु
	.ddr2_pकरोwn	= 1,
पूर्ण;


अटल काष्ठा platक्रमm_device da8xx_cpuidle_device = अणु
	.name			= "cpuidle-davinci",
	.num_resources		= ARRAY_SIZE(da8xx_cpuidle_resources),
	.resource		= da8xx_cpuidle_resources,
	.dev = अणु
		.platक्रमm_data	= &da8xx_cpuidle_pdata,
	पूर्ण,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_cpuidle(व्योम)
अणु
	da8xx_cpuidle_pdata.ddr2_ctlr_base = da8xx_get_mem_ctlr();

	वापस platक्रमm_device_रेजिस्टर(&da8xx_cpuidle_device);
पूर्ण

अटल काष्ठा resource da8xx_spi0_resources[] = अणु
	[0] = अणु
		.start	= DA8XX_SPI0_BASE,
		.end	= DA8XX_SPI0_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_SPINT0),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_SPINT0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource da8xx_spi1_resources[] = अणु
	[0] = अणु
		.start	= DA830_SPI1_BASE,
		.end	= DA830_SPI1_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_SPINT1),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_SPINT1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_spi_platक्रमm_data da8xx_spi_pdata[] = अणु
	[0] = अणु
		.version	= SPI_VERSION_2,
		.पूर्णांकr_line	= 1,
		.dma_event_q	= EVENTQ_0,
		.prescaler_limit = 2,
	पूर्ण,
	[1] = अणु
		.version	= SPI_VERSION_2,
		.पूर्णांकr_line	= 1,
		.dma_event_q	= EVENTQ_0,
		.prescaler_limit = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da8xx_spi_device[] = अणु
	[0] = अणु
		.name		= "spi_davinci",
		.id		= 0,
		.num_resources	= ARRAY_SIZE(da8xx_spi0_resources),
		.resource	= da8xx_spi0_resources,
		.dev		= अणु
			.platक्रमm_data = &da8xx_spi_pdata[0],
		पूर्ण,
	पूर्ण,
	[1] = अणु
		.name		= "spi_davinci",
		.id		= 1,
		.num_resources	= ARRAY_SIZE(da8xx_spi1_resources),
		.resource	= da8xx_spi1_resources,
		.dev		= अणु
			.platक्रमm_data = &da8xx_spi_pdata[1],
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_spi_bus(पूर्णांक instance, अचिन्हित num_chipselect)
अणु
	अगर (instance < 0 || instance > 1)
		वापस -EINVAL;

	da8xx_spi_pdata[instance].num_chipselect = num_chipselect;

	अगर (instance == 1 && cpu_is_davinci_da850()) अणु
		da8xx_spi1_resources[0].start = DA850_SPI1_BASE;
		da8xx_spi1_resources[0].end = DA850_SPI1_BASE + SZ_4K - 1;
	पूर्ण

	वापस platक्रमm_device_रेजिस्टर(&da8xx_spi_device[instance]);
पूर्ण

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
पूर्णांक __init da850_रेजिस्टर_sata_refclk(पूर्णांक rate)
अणु
	काष्ठा clk *clk;

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "sata_refclk", शून्य, 0, rate);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	वापस clk_रेजिस्टर_clkdev(clk, "refclk", "ahci_da850");
पूर्ण

अटल काष्ठा resource da850_sata_resources[] = अणु
	अणु
		.start	= DA850_SATA_BASE,
		.end	= DA850_SATA_BASE + 0x1fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DA8XX_SYSCFG1_BASE + DA8XX_PWRDN_REG,
		.end	= DA8XX_SYSCFG1_BASE + DA8XX_PWRDN_REG + 0x3,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA850_SATAINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 da850_sata_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device da850_sata_device = अणु
	.name	= "ahci_da850",
	.id	= -1,
	.dev	= अणु
		.dma_mask		= &da850_sata_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources	= ARRAY_SIZE(da850_sata_resources),
	.resource	= da850_sata_resources,
पूर्ण;

पूर्णांक __init da850_रेजिस्टर_sata(अचिन्हित दीर्घ refclkpn)
अणु
	पूर्णांक ret;

	ret = da850_रेजिस्टर_sata_refclk(refclkpn);
	अगर (ret)
		वापस ret;

	वापस platक्रमm_device_रेजिस्टर(&da850_sata_device);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा regmap *da8xx_cfgchip;

अटल स्थिर काष्ठा regmap_config da8xx_cfgchip_config __initस्थिर = अणु
	.name		= "cfgchip",
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= DA8XX_CFGCHIP4_REG - DA8XX_CFGCHIP0_REG,
पूर्ण;

/**
 * da8xx_get_cfgchip - Lazy माला_लो CFGCHIP as regmap
 *
 * This is क्रम use on non-DT boards only. For DT boards, use
 * syscon_regmap_lookup_by_compatible("ti,da830-cfgchip")
 *
 * Returns: Poपूर्णांकer to the CFGCHIP regmap or negative error code.
 */
काष्ठा regmap * __init da8xx_get_cfgchip(व्योम)
अणु
	अगर (IS_ERR_OR_शून्य(da8xx_cfgchip))
		da8xx_cfgchip = regmap_init_mmio(शून्य,
					DA8XX_SYSCFG0_VIRT(DA8XX_CFGCHIP0_REG),
					&da8xx_cfgchip_config);

	वापस da8xx_cfgchip;
पूर्ण
