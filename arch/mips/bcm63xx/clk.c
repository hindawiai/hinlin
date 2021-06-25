<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_reset.h>

काष्ठा clk अणु
	व्योम		(*set)(काष्ठा clk *, पूर्णांक);
	अचिन्हित पूर्णांक	rate;
	अचिन्हित पूर्णांक	usage;
	पूर्णांक		id;
पूर्ण;

अटल DEFINE_MUTEX(घड़ीs_mutex);


अटल व्योम clk_enable_unlocked(काष्ठा clk *clk)
अणु
	अगर (clk->set && (clk->usage++) == 0)
		clk->set(clk, 1);
पूर्ण

अटल व्योम clk_disable_unlocked(काष्ठा clk *clk)
अणु
	अगर (clk->set && (--clk->usage) == 0)
		clk->set(clk, 0);
पूर्ण

अटल व्योम bcm_hwघड़ी_set(u32 mask, पूर्णांक enable)
अणु
	u32 reg;

	reg = bcm_perf_पढ़ोl(PERF_CKCTL_REG);
	अगर (enable)
		reg |= mask;
	अन्यथा
		reg &= ~mask;
	bcm_perf_ग_लिखोl(reg, PERF_CKCTL_REG);
पूर्ण

/*
 * Ethernet MAC "misc" घड़ी: dma घड़ीs and मुख्य घड़ी on 6348
 */
अटल व्योम enet_misc_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	u32 mask;

	अगर (BCMCPU_IS_6338())
		mask = CKCTL_6338_ENET_EN;
	अन्यथा अगर (BCMCPU_IS_6345())
		mask = CKCTL_6345_ENET_EN;
	अन्यथा अगर (BCMCPU_IS_6348())
		mask = CKCTL_6348_ENET_EN;
	अन्यथा
		/* BCMCPU_IS_6358 */
		mask = CKCTL_6358_EMUSB_EN;
	bcm_hwघड़ी_set(mask, enable);
पूर्ण

अटल काष्ठा clk clk_enet_misc = अणु
	.set	= enet_misc_set,
पूर्ण;

/*
 * Ethernet MAC घड़ीs: only relevant on 6358, silently enable misc
 * घड़ीs
 */
अटल व्योम enetx_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (enable)
		clk_enable_unlocked(&clk_enet_misc);
	अन्यथा
		clk_disable_unlocked(&clk_enet_misc);

	अगर (BCMCPU_IS_3368() || BCMCPU_IS_6358()) अणु
		u32 mask;

		अगर (clk->id == 0)
			mask = CKCTL_6358_ENET0_EN;
		अन्यथा
			mask = CKCTL_6358_ENET1_EN;
		bcm_hwघड़ी_set(mask, enable);
	पूर्ण
पूर्ण

अटल काष्ठा clk clk_enet0 = अणु
	.id	= 0,
	.set	= enetx_set,
पूर्ण;

अटल काष्ठा clk clk_enet1 = अणु
	.id	= 1,
	.set	= enetx_set,
पूर्ण;

/*
 * Ethernet PHY घड़ी
 */
अटल व्योम ephy_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_3368() || BCMCPU_IS_6358())
		bcm_hwघड़ी_set(CKCTL_6358_EPHY_EN, enable);
पूर्ण


अटल काष्ठा clk clk_ephy = अणु
	.set	= ephy_set,
पूर्ण;

/*
 * Ethernet चयन SAR घड़ी
 */
अटल व्योम swpkt_sar_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_6368())
		bcm_hwघड़ी_set(CKCTL_6368_SWPKT_SAR_EN, enable);
	अन्यथा
		वापस;
पूर्ण

अटल काष्ठा clk clk_swpkt_sar = अणु
	.set	= swpkt_sar_set,
पूर्ण;

/*
 * Ethernet चयन USB घड़ी
 */
अटल व्योम swpkt_usb_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_6368())
		bcm_hwघड़ी_set(CKCTL_6368_SWPKT_USB_EN, enable);
	अन्यथा
		वापस;
पूर्ण

अटल काष्ठा clk clk_swpkt_usb = अणु
	.set	= swpkt_usb_set,
पूर्ण;

/*
 * Ethernet चयन घड़ी
 */
अटल व्योम enetsw_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_6328()) अणु
		bcm_hwघड़ी_set(CKCTL_6328_ROBOSW_EN, enable);
	पूर्ण अन्यथा अगर (BCMCPU_IS_6362()) अणु
		bcm_hwघड़ी_set(CKCTL_6362_ROBOSW_EN, enable);
	पूर्ण अन्यथा अगर (BCMCPU_IS_6368()) अणु
		अगर (enable) अणु
			clk_enable_unlocked(&clk_swpkt_sar);
			clk_enable_unlocked(&clk_swpkt_usb);
		पूर्ण अन्यथा अणु
			clk_disable_unlocked(&clk_swpkt_usb);
			clk_disable_unlocked(&clk_swpkt_sar);
		पूर्ण
		bcm_hwघड़ी_set(CKCTL_6368_ROBOSW_EN, enable);
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	अगर (enable) अणु
		/* reset चयन core afer घड़ी change */
		bcm63xx_core_set_reset(BCM63XX_RESET_ENETSW, 1);
		msleep(10);
		bcm63xx_core_set_reset(BCM63XX_RESET_ENETSW, 0);
		msleep(10);
	पूर्ण
पूर्ण

अटल काष्ठा clk clk_enetsw = अणु
	.set	= enetsw_set,
पूर्ण;

/*
 * PCM घड़ी
 */
अटल व्योम pcm_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_3368())
		bcm_hwघड़ी_set(CKCTL_3368_PCM_EN, enable);
	अगर (BCMCPU_IS_6358())
		bcm_hwघड़ी_set(CKCTL_6358_PCM_EN, enable);
पूर्ण

अटल काष्ठा clk clk_pcm = अणु
	.set	= pcm_set,
पूर्ण;

/*
 * USB host घड़ी
 */
अटल व्योम usbh_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_6328())
		bcm_hwघड़ी_set(CKCTL_6328_USBH_EN, enable);
	अन्यथा अगर (BCMCPU_IS_6348())
		bcm_hwघड़ी_set(CKCTL_6348_USBH_EN, enable);
	अन्यथा अगर (BCMCPU_IS_6362())
		bcm_hwघड़ी_set(CKCTL_6362_USBH_EN, enable);
	अन्यथा अगर (BCMCPU_IS_6368())
		bcm_hwघड़ी_set(CKCTL_6368_USBH_EN, enable);
पूर्ण

अटल काष्ठा clk clk_usbh = अणु
	.set	= usbh_set,
पूर्ण;

/*
 * USB device घड़ी
 */
अटल व्योम usbd_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_6328())
		bcm_hwघड़ी_set(CKCTL_6328_USBD_EN, enable);
	अन्यथा अगर (BCMCPU_IS_6362())
		bcm_hwघड़ी_set(CKCTL_6362_USBD_EN, enable);
	अन्यथा अगर (BCMCPU_IS_6368())
		bcm_hwघड़ी_set(CKCTL_6368_USBD_EN, enable);
पूर्ण

अटल काष्ठा clk clk_usbd = अणु
	.set	= usbd_set,
पूर्ण;

/*
 * SPI घड़ी
 */
अटल व्योम spi_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	u32 mask;

	अगर (BCMCPU_IS_6338())
		mask = CKCTL_6338_SPI_EN;
	अन्यथा अगर (BCMCPU_IS_6348())
		mask = CKCTL_6348_SPI_EN;
	अन्यथा अगर (BCMCPU_IS_3368() || BCMCPU_IS_6358())
		mask = CKCTL_6358_SPI_EN;
	अन्यथा अगर (BCMCPU_IS_6362())
		mask = CKCTL_6362_SPI_EN;
	अन्यथा
		/* BCMCPU_IS_6368 */
		mask = CKCTL_6368_SPI_EN;
	bcm_hwघड़ी_set(mask, enable);
पूर्ण

अटल काष्ठा clk clk_spi = अणु
	.set	= spi_set,
पूर्ण;

/*
 * HSSPI घड़ी
 */
अटल व्योम hsspi_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	u32 mask;

	अगर (BCMCPU_IS_6328())
		mask = CKCTL_6328_HSSPI_EN;
	अन्यथा अगर (BCMCPU_IS_6362())
		mask = CKCTL_6362_HSSPI_EN;
	अन्यथा
		वापस;

	bcm_hwघड़ी_set(mask, enable);
पूर्ण

अटल काष्ठा clk clk_hsspi = अणु
	.set	= hsspi_set,
पूर्ण;

/*
 * HSSPI PLL
 */
अटल काष्ठा clk clk_hsspi_pll;

/*
 * XTM घड़ी
 */
अटल व्योम xपंचांग_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (!BCMCPU_IS_6368())
		वापस;

	अगर (enable)
		clk_enable_unlocked(&clk_swpkt_sar);
	अन्यथा
		clk_disable_unlocked(&clk_swpkt_sar);

	bcm_hwघड़ी_set(CKCTL_6368_SAR_EN, enable);

	अगर (enable) अणु
		/* reset sar core afer घड़ी change */
		bcm63xx_core_set_reset(BCM63XX_RESET_SAR, 1);
		mdelay(1);
		bcm63xx_core_set_reset(BCM63XX_RESET_SAR, 0);
		mdelay(1);
	पूर्ण
पूर्ण


अटल काष्ठा clk clk_xपंचांग = अणु
	.set	= xपंचांग_set,
पूर्ण;

/*
 * IPsec घड़ी
 */
अटल व्योम ipsec_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_6362())
		bcm_hwघड़ी_set(CKCTL_6362_IPSEC_EN, enable);
	अन्यथा अगर (BCMCPU_IS_6368())
		bcm_hwघड़ी_set(CKCTL_6368_IPSEC_EN, enable);
पूर्ण

अटल काष्ठा clk clk_ipsec = अणु
	.set	= ipsec_set,
पूर्ण;

/*
 * PCIe घड़ी
 */

अटल व्योम pcie_set(काष्ठा clk *clk, पूर्णांक enable)
अणु
	अगर (BCMCPU_IS_6328())
		bcm_hwघड़ी_set(CKCTL_6328_PCIE_EN, enable);
	अन्यथा अगर (BCMCPU_IS_6362())
		bcm_hwघड़ी_set(CKCTL_6362_PCIE_EN, enable);
पूर्ण

अटल काष्ठा clk clk_pcie = अणु
	.set	= pcie_set,
पूर्ण;

/*
 * Internal peripheral घड़ी
 */
अटल काष्ठा clk clk_periph = अणु
	.rate	= (50 * 1000 * 1000),
पूर्ण;


/*
 * Linux घड़ी API implementation
 */
पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	mutex_lock(&घड़ीs_mutex);
	clk_enable_unlocked(clk);
	mutex_unlock(&घड़ीs_mutex);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(clk_enable);

व्योम clk_disable(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस;

	mutex_lock(&घड़ीs_mutex);
	clk_disable_unlocked(clk);
	mutex_unlock(&घड़ीs_mutex);
पूर्ण

EXPORT_SYMBOL(clk_disable);

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk->rate;
पूर्ण

EXPORT_SYMBOL(clk_get_rate);

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_rate);

दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_round_rate);

अटल काष्ठा clk_lookup bcm3368_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.1", "refclk", &clk_periph),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enet0", &clk_enet0),
	CLKDEV_INIT(शून्य, "enet1", &clk_enet1),
	CLKDEV_INIT(शून्य, "ephy", &clk_ephy),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "spi", &clk_spi),
	CLKDEV_INIT(शून्य, "pcm", &clk_pcm),
	CLKDEV_INIT("bcm63xx_enet.0", "enet", &clk_enet0),
	CLKDEV_INIT("bcm63xx_enet.1", "enet", &clk_enet1),
पूर्ण;

अटल काष्ठा clk_lookup bcm6328_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.1", "refclk", &clk_periph),
	CLKDEV_INIT("bcm63xx-hsspi.0", "pll", &clk_hsspi_pll),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enetsw", &clk_enetsw),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "hsspi", &clk_hsspi),
	CLKDEV_INIT(शून्य, "pcie", &clk_pcie),
पूर्ण;

अटल काष्ठा clk_lookup bcm6338_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enet0", &clk_enet0),
	CLKDEV_INIT(शून्य, "enet1", &clk_enet1),
	CLKDEV_INIT(शून्य, "ephy", &clk_ephy),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "spi", &clk_spi),
	CLKDEV_INIT("bcm63xx_enet.0", "enet", &clk_enet_misc),
पूर्ण;

अटल काष्ठा clk_lookup bcm6345_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enet0", &clk_enet0),
	CLKDEV_INIT(शून्य, "enet1", &clk_enet1),
	CLKDEV_INIT(शून्य, "ephy", &clk_ephy),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "spi", &clk_spi),
	CLKDEV_INIT("bcm63xx_enet.0", "enet", &clk_enet_misc),
पूर्ण;

अटल काष्ठा clk_lookup bcm6348_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enet0", &clk_enet0),
	CLKDEV_INIT(शून्य, "enet1", &clk_enet1),
	CLKDEV_INIT(शून्य, "ephy", &clk_ephy),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "spi", &clk_spi),
	CLKDEV_INIT("bcm63xx_enet.0", "enet", &clk_enet_misc),
	CLKDEV_INIT("bcm63xx_enet.1", "enet", &clk_enet_misc),
पूर्ण;

अटल काष्ठा clk_lookup bcm6358_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.1", "refclk", &clk_periph),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enet0", &clk_enet0),
	CLKDEV_INIT(शून्य, "enet1", &clk_enet1),
	CLKDEV_INIT(शून्य, "ephy", &clk_ephy),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "spi", &clk_spi),
	CLKDEV_INIT(शून्य, "pcm", &clk_pcm),
	CLKDEV_INIT(शून्य, "swpkt_sar", &clk_swpkt_sar),
	CLKDEV_INIT(शून्य, "swpkt_usb", &clk_swpkt_usb),
	CLKDEV_INIT("bcm63xx_enet.0", "enet", &clk_enet0),
	CLKDEV_INIT("bcm63xx_enet.1", "enet", &clk_enet1),
पूर्ण;

अटल काष्ठा clk_lookup bcm6362_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.1", "refclk", &clk_periph),
	CLKDEV_INIT("bcm63xx-hsspi.0", "pll", &clk_hsspi_pll),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enetsw", &clk_enetsw),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "spi", &clk_spi),
	CLKDEV_INIT(शून्य, "hsspi", &clk_hsspi),
	CLKDEV_INIT(शून्य, "pcie", &clk_pcie),
	CLKDEV_INIT(शून्य, "ipsec", &clk_ipsec),
पूर्ण;

अटल काष्ठा clk_lookup bcm6368_clks[] = अणु
	/* fixed rate घड़ीs */
	CLKDEV_INIT(शून्य, "periph", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.0", "refclk", &clk_periph),
	CLKDEV_INIT("bcm63xx_uart.1", "refclk", &clk_periph),
	/* gated घड़ीs */
	CLKDEV_INIT(शून्य, "enetsw", &clk_enetsw),
	CLKDEV_INIT(शून्य, "usbh", &clk_usbh),
	CLKDEV_INIT(शून्य, "usbd", &clk_usbd),
	CLKDEV_INIT(शून्य, "spi", &clk_spi),
	CLKDEV_INIT(शून्य, "xtm", &clk_xपंचांग),
	CLKDEV_INIT(शून्य, "ipsec", &clk_ipsec),
पूर्ण;

#घोषणा HSSPI_PLL_HZ_6328	133333333
#घोषणा HSSPI_PLL_HZ_6362	400000000

अटल पूर्णांक __init bcm63xx_clk_init(व्योम)
अणु
	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM3368_CPU_ID:
		clkdev_add_table(bcm3368_clks, ARRAY_SIZE(bcm3368_clks));
		अवरोध;
	हाल BCM6328_CPU_ID:
		clk_hsspi_pll.rate = HSSPI_PLL_HZ_6328;
		clkdev_add_table(bcm6328_clks, ARRAY_SIZE(bcm6328_clks));
		अवरोध;
	हाल BCM6338_CPU_ID:
		clkdev_add_table(bcm6338_clks, ARRAY_SIZE(bcm6338_clks));
		अवरोध;
	हाल BCM6345_CPU_ID:
		clkdev_add_table(bcm6345_clks, ARRAY_SIZE(bcm6345_clks));
		अवरोध;
	हाल BCM6348_CPU_ID:
		clkdev_add_table(bcm6348_clks, ARRAY_SIZE(bcm6348_clks));
		अवरोध;
	हाल BCM6358_CPU_ID:
		clkdev_add_table(bcm6358_clks, ARRAY_SIZE(bcm6358_clks));
		अवरोध;
	हाल BCM6362_CPU_ID:
		clk_hsspi_pll.rate = HSSPI_PLL_HZ_6362;
		clkdev_add_table(bcm6362_clks, ARRAY_SIZE(bcm6362_clks));
		अवरोध;
	हाल BCM6368_CPU_ID:
		clkdev_add_table(bcm6368_clks, ARRAY_SIZE(bcm6368_clks));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
arch_initcall(bcm63xx_clk_init);
