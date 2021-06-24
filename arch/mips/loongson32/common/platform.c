<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011-2016 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/sizes.h>
#समावेश <linux/phy.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/sपंचांगmac.h>
#समावेश <linux/usb/ehci_pdriver.h>

#समावेश <platक्रमm.h>
#समावेश <loongson1.h>
#समावेश <cpufreq.h>
#समावेश <dma.h>
#समावेश <nand.h>

/* 8250/16550 compatible UART */
#घोषणा LS1X_UART(_id)						\
	अणु							\
		.mapbase	= LS1X_UART ## _id ## _BASE,	\
		.irq		= LS1X_UART ## _id ## _IRQ,	\
		.iotype		= UPIO_MEM,			\
		.flags		= UPF_IOREMAP | UPF_FIXED_TYPE, \
		.type		= PORT_16550A,			\
	पूर्ण

अटल काष्ठा plat_serial8250_port ls1x_serial8250_pdata[] = अणु
	LS1X_UART(0),
	LS1X_UART(1),
	LS1X_UART(2),
	LS1X_UART(3),
	अणुपूर्ण,
पूर्ण;

काष्ठा platक्रमm_device ls1x_uart_pdev = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
		.platक्रमm_data = ls1x_serial8250_pdata,
	पूर्ण,
पूर्ण;

व्योम __init ls1x_serial_set_uartclk(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *clk;
	काष्ठा plat_serial8250_port *p;

	clk = clk_get(&pdev->dev, pdev->name);
	अगर (IS_ERR(clk)) अणु
		pr_err("unable to get %s clock, err=%ld",
		       pdev->name, PTR_ERR(clk));
		वापस;
	पूर्ण
	clk_prepare_enable(clk);

	क्रम (p = pdev->dev.platक्रमm_data; p->flags != 0; ++p)
		p->uartclk = clk_get_rate(clk);
पूर्ण

/* CPUFreq */
अटल काष्ठा plat_ls1x_cpufreq ls1x_cpufreq_pdata = अणु
	.clk_name	= "cpu_clk",
	.osc_clk_name	= "osc_clk",
	.max_freq	= 266 * 1000,
	.min_freq	= 33 * 1000,
पूर्ण;

काष्ठा platक्रमm_device ls1x_cpufreq_pdev = अणु
	.name		= "ls1x-cpufreq",
	.dev		= अणु
		.platक्रमm_data = &ls1x_cpufreq_pdata,
	पूर्ण,
पूर्ण;

/* Synopsys Ethernet GMAC */
अटल काष्ठा sपंचांगmac_mdio_bus_data ls1x_mdio_bus_data = अणु
	.phy_mask	= 0,
पूर्ण;

अटल काष्ठा sपंचांगmac_dma_cfg ls1x_eth_dma_cfg = अणु
	.pbl		= 1,
पूर्ण;

पूर्णांक ls1x_eth_mux_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat = शून्य;
	u32 val;

	val = __raw_पढ़ोl(LS1X_MUX_CTRL1);

#अगर defined(CONFIG_LOONGSON1_LS1B)
	plat_dat = dev_get_platdata(&pdev->dev);
	अगर (plat_dat->bus_id) अणु
		__raw_ग_लिखोl(__raw_पढ़ोl(LS1X_MUX_CTRL0) | GMAC1_USE_UART1 |
			     GMAC1_USE_UART0, LS1X_MUX_CTRL0);
		चयन (plat_dat->पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_RGMII:
			val &= ~(GMAC1_USE_TXCLK | GMAC1_USE_PWM23);
			अवरोध;
		हाल PHY_INTERFACE_MODE_MII:
			val |= (GMAC1_USE_TXCLK | GMAC1_USE_PWM23);
			अवरोध;
		शेष:
			pr_err("unsupported mii mode %d\n",
			       plat_dat->पूर्णांकerface);
			वापस -ENOTSUPP;
		पूर्ण
		val &= ~GMAC1_SHUT;
	पूर्ण अन्यथा अणु
		चयन (plat_dat->पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_RGMII:
			val &= ~(GMAC0_USE_TXCLK | GMAC0_USE_PWM01);
			अवरोध;
		हाल PHY_INTERFACE_MODE_MII:
			val |= (GMAC0_USE_TXCLK | GMAC0_USE_PWM01);
			अवरोध;
		शेष:
			pr_err("unsupported mii mode %d\n",
			       plat_dat->पूर्णांकerface);
			वापस -ENOTSUPP;
		पूर्ण
		val &= ~GMAC0_SHUT;
	पूर्ण
	__raw_ग_लिखोl(val, LS1X_MUX_CTRL1);
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
	plat_dat = dev_get_platdata(&pdev->dev);

	val &= ~PHY_INTF_SELI;
	अगर (plat_dat->पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
		val |= 0x4 << PHY_INTF_SELI_SHIFT;
	__raw_ग_लिखोl(val, LS1X_MUX_CTRL1);

	val = __raw_पढ़ोl(LS1X_MUX_CTRL0);
	__raw_ग_लिखोl(val & (~GMAC_SHUT), LS1X_MUX_CTRL0);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल काष्ठा plat_sपंचांगmacenet_data ls1x_eth0_pdata = अणु
	.bus_id			= 0,
	.phy_addr		= -1,
#अगर defined(CONFIG_LOONGSON1_LS1B)
	.पूर्णांकerface		= PHY_INTERFACE_MODE_MII,
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
	.पूर्णांकerface		= PHY_INTERFACE_MODE_RMII,
#पूर्ण_अगर
	.mdio_bus_data		= &ls1x_mdio_bus_data,
	.dma_cfg		= &ls1x_eth_dma_cfg,
	.has_gmac		= 1,
	.tx_coe			= 1,
	.rx_queues_to_use	= 1,
	.tx_queues_to_use	= 1,
	.init			= ls1x_eth_mux_init,
पूर्ण;

अटल काष्ठा resource ls1x_eth0_resources[] = अणु
	[0] = अणु
		.start	= LS1X_GMAC0_BASE,
		.end	= LS1X_GMAC0_BASE + SZ_64K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "macirq",
		.start	= LS1X_GMAC0_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device ls1x_eth0_pdev = अणु
	.name		= "stmmaceth",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(ls1x_eth0_resources),
	.resource	= ls1x_eth0_resources,
	.dev		= अणु
		.platक्रमm_data = &ls1x_eth0_pdata,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_LOONGSON1_LS1B
अटल काष्ठा plat_sपंचांगmacenet_data ls1x_eth1_pdata = अणु
	.bus_id			= 1,
	.phy_addr		= -1,
	.पूर्णांकerface		= PHY_INTERFACE_MODE_MII,
	.mdio_bus_data		= &ls1x_mdio_bus_data,
	.dma_cfg		= &ls1x_eth_dma_cfg,
	.has_gmac		= 1,
	.tx_coe			= 1,
	.rx_queues_to_use	= 1,
	.tx_queues_to_use	= 1,
	.init			= ls1x_eth_mux_init,
पूर्ण;

अटल काष्ठा resource ls1x_eth1_resources[] = अणु
	[0] = अणु
		.start	= LS1X_GMAC1_BASE,
		.end	= LS1X_GMAC1_BASE + SZ_64K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "macirq",
		.start	= LS1X_GMAC1_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device ls1x_eth1_pdev = अणु
	.name		= "stmmaceth",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(ls1x_eth1_resources),
	.resource	= ls1x_eth1_resources,
	.dev		= अणु
		.platक्रमm_data = &ls1x_eth1_pdata,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर	/* CONFIG_LOONGSON1_LS1B */

/* GPIO */
अटल काष्ठा resource ls1x_gpio0_resources[] = अणु
	[0] = अणु
		.start	= LS1X_GPIO0_BASE,
		.end	= LS1X_GPIO0_BASE + SZ_4 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device ls1x_gpio0_pdev = अणु
	.name		= "ls1x-gpio",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(ls1x_gpio0_resources),
	.resource	= ls1x_gpio0_resources,
पूर्ण;

अटल काष्ठा resource ls1x_gpio1_resources[] = अणु
	[0] = अणु
		.start	= LS1X_GPIO1_BASE,
		.end	= LS1X_GPIO1_BASE + SZ_4 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device ls1x_gpio1_pdev = अणु
	.name		= "ls1x-gpio",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(ls1x_gpio1_resources),
	.resource	= ls1x_gpio1_resources,
पूर्ण;

/* USB EHCI */
अटल u64 ls1x_ehci_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा resource ls1x_ehci_resources[] = अणु
	[0] = अणु
		.start	= LS1X_EHCI_BASE,
		.end	= LS1X_EHCI_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= LS1X_EHCI_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा usb_ehci_pdata ls1x_ehci_pdata = अणु
पूर्ण;

काष्ठा platक्रमm_device ls1x_ehci_pdev = अणु
	.name		= "ehci-platform",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ls1x_ehci_resources),
	.resource	= ls1x_ehci_resources,
	.dev		= अणु
		.dma_mask = &ls1x_ehci_dmamask,
		.platक्रमm_data = &ls1x_ehci_pdata,
	पूर्ण,
पूर्ण;

/* Real Time Clock */
व्योम __init ls1x_rtc_set_extclk(काष्ठा platक्रमm_device *pdev)
अणु
	u32 val = __raw_पढ़ोl(LS1X_RTC_CTRL);

	अगर (!(val & RTC_EXTCLK_OK))
		__raw_ग_लिखोl(val | RTC_EXTCLK_EN, LS1X_RTC_CTRL);
पूर्ण

काष्ठा platक्रमm_device ls1x_rtc_pdev = अणु
	.name		= "ls1x-rtc",
	.id		= -1,
पूर्ण;

/* Watchकरोg */
अटल काष्ठा resource ls1x_wdt_resources[] = अणु
	अणु
		.start	= LS1X_WDT_BASE,
		.end	= LS1X_WDT_BASE + SZ_16 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device ls1x_wdt_pdev = अणु
	.name		= "ls1x-wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ls1x_wdt_resources),
	.resource	= ls1x_wdt_resources,
पूर्ण;
