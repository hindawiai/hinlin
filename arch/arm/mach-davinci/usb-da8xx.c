<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DA8xx USB
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/da8xx-cfgchip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_data/clk-da8xx-cfgchip.h>
#समावेश <linux/platक्रमm_data/phy-da8xx-usb.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/musb.h>

#समावेश <mach/common.h>
#समावेश <mach/cputype.h>
#समावेश <mach/da8xx.h>

#समावेश "irqs.h"

#घोषणा DA8XX_USB0_BASE		0x01e00000
#घोषणा DA8XX_USB1_BASE		0x01e25000

#अगर_अघोषित CONFIG_COMMON_CLK
अटल काष्ठा clk *usb20_clk;
#पूर्ण_अगर

अटल काष्ठा da8xx_usb_phy_platक्रमm_data da8xx_usb_phy_pdata;

अटल काष्ठा platक्रमm_device da8xx_usb_phy = अणु
	.name		= "da8xx-usb-phy",
	.id		= -1,
	.dev		= अणु
		/*
		 * Setting init_name so that घड़ी lookup will work in
		 * da8xx_रेजिस्टर_usb11_phy_clk() even अगर this device is not
		 * रेजिस्टरed yet.
		 */
		.init_name	= "da8xx-usb-phy",
		.platक्रमm_data	= &da8xx_usb_phy_pdata,
	पूर्ण,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_usb_phy(व्योम)
अणु
	da8xx_usb_phy_pdata.cfgchip = da8xx_get_cfgchip();

	वापस platक्रमm_device_रेजिस्टर(&da8xx_usb_phy);
पूर्ण

अटल काष्ठा musb_hdrc_config musb_config = अणु
	.multipoपूर्णांक	= true,
	.num_eps	= 5,
	.ram_bits	= 10,
पूर्ण;

अटल काष्ठा musb_hdrc_platक्रमm_data usb_data = अणु
	/* OTG requires a Mini-AB connector */
	.mode           = MUSB_OTG,
	.घड़ी		= "usb20",
	.config		= &musb_config,
पूर्ण;

अटल काष्ठा resource da8xx_usb20_resources[] = अणु
	अणु
		.start		= DA8XX_USB0_BASE,
		.end		= DA8XX_USB0_BASE + SZ_64K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= DAVINCI_INTC_IRQ(IRQ_DA8XX_USB_INT),
		.flags		= IORESOURCE_IRQ,
		.name		= "mc",
	पूर्ण,
पूर्ण;

अटल u64 usb_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device da8xx_usb20_dev = अणु
	.name		= "musb-da8xx",
	.id             = -1,
	.dev = अणु
		.platक्रमm_data		= &usb_data,
		.dma_mask		= &usb_dmamask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= da8xx_usb20_resources,
	.num_resources	= ARRAY_SIZE(da8xx_usb20_resources),
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_usb20(अचिन्हित पूर्णांक mA, अचिन्हित पूर्णांक potpgt)
अणु
	usb_data.घातer	= mA > 510 ? 255 : mA / 2;
	usb_data.potpgt = (potpgt + 1) / 2;

	वापस platक्रमm_device_रेजिस्टर(&da8xx_usb20_dev);
पूर्ण

अटल काष्ठा resource da8xx_usb11_resources[] = अणु
	[0] = अणु
		.start	= DA8XX_USB1_BASE,
		.end	= DA8XX_USB1_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DA8XX_IRQN),
		.end	= DAVINCI_INTC_IRQ(IRQ_DA8XX_IRQN),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 da8xx_usb11_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device da8xx_usb11_device = अणु
	.name		= "ohci-da8xx",
	.id		= -1,
	.dev = अणु
		.dma_mask		= &da8xx_usb11_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources	= ARRAY_SIZE(da8xx_usb11_resources),
	.resource	= da8xx_usb11_resources,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_usb11(काष्ठा da8xx_ohci_root_hub *pdata)
अणु
	da8xx_usb11_device.dev.platक्रमm_data = pdata;
	वापस platक्रमm_device_रेजिस्टर(&da8xx_usb11_device);
पूर्ण

अटल काष्ठा platक्रमm_device da8xx_usb_phy_clks_device = अणु
	.name		= "da830-usb-phy-clks",
	.id		= -1,
पूर्ण;

पूर्णांक __init da8xx_रेजिस्टर_usb_phy_घड़ीs(व्योम)
अणु
	काष्ठा da8xx_cfgchip_clk_platक्रमm_data pdata;

	pdata.cfgchip = da8xx_get_cfgchip();
	da8xx_usb_phy_clks_device.dev.platक्रमm_data = &pdata;

	वापस platक्रमm_device_रेजिस्टर(&da8xx_usb_phy_clks_device);
पूर्ण
