<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * omap-usb-host.c - The USBHS core driver क्रम OMAP EHCI & OHCI
 *
 * Copyright (C) 2011-2013 Texas Instruments Incorporated - https://www.ti.com
 * Author: Keshava Munegowda <keshava_mgowda@ti.com>
 * Author: Roger Quadros <rogerq@ti.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/usb-omap.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/err.h>

#समावेश "omap-usb.h"

#घोषणा USBHS_DRIVER_NAME	"usbhs_omap"
#घोषणा OMAP_EHCI_DEVICE	"ehci-omap"
#घोषणा OMAP_OHCI_DEVICE	"ohci-omap3"

/* OMAP USBHOST Register addresses  */

/* UHH Register Set */
#घोषणा	OMAP_UHH_REVISION				(0x00)
#घोषणा	OMAP_UHH_SYSCONFIG				(0x10)
#घोषणा	OMAP_UHH_SYSCONFIG_MIDLEMODE			(1 << 12)
#घोषणा	OMAP_UHH_SYSCONFIG_CACTIVITY			(1 << 8)
#घोषणा	OMAP_UHH_SYSCONFIG_SIDLEMODE			(1 << 3)
#घोषणा	OMAP_UHH_SYSCONFIG_ENAWAKEUP			(1 << 2)
#घोषणा	OMAP_UHH_SYSCONFIG_SOFTRESET			(1 << 1)
#घोषणा	OMAP_UHH_SYSCONFIG_AUTOIDLE			(1 << 0)

#घोषणा	OMAP_UHH_SYSSTATUS				(0x14)
#घोषणा	OMAP_UHH_HOSTCONFIG				(0x40)
#घोषणा	OMAP_UHH_HOSTCONFIG_ULPI_BYPASS			(1 << 0)
#घोषणा	OMAP_UHH_HOSTCONFIG_ULPI_P1_BYPASS		(1 << 0)
#घोषणा	OMAP_UHH_HOSTCONFIG_ULPI_P2_BYPASS		(1 << 11)
#घोषणा	OMAP_UHH_HOSTCONFIG_ULPI_P3_BYPASS		(1 << 12)
#घोषणा OMAP_UHH_HOSTCONFIG_INCR4_BURST_EN		(1 << 2)
#घोषणा OMAP_UHH_HOSTCONFIG_INCR8_BURST_EN		(1 << 3)
#घोषणा OMAP_UHH_HOSTCONFIG_INCR16_BURST_EN		(1 << 4)
#घोषणा OMAP_UHH_HOSTCONFIG_INCRX_ALIGN_EN		(1 << 5)
#घोषणा OMAP_UHH_HOSTCONFIG_P1_CONNECT_STATUS		(1 << 8)
#घोषणा OMAP_UHH_HOSTCONFIG_P2_CONNECT_STATUS		(1 << 9)
#घोषणा OMAP_UHH_HOSTCONFIG_P3_CONNECT_STATUS		(1 << 10)
#घोषणा OMAP4_UHH_HOSTCONFIG_APP_START_CLK		(1 << 31)

/* OMAP4-specअगरic defines */
#घोषणा OMAP4_UHH_SYSCONFIG_IDLEMODE_CLEAR		(3 << 2)
#घोषणा OMAP4_UHH_SYSCONFIG_NOIDLE			(1 << 2)
#घोषणा OMAP4_UHH_SYSCONFIG_STDBYMODE_CLEAR		(3 << 4)
#घोषणा OMAP4_UHH_SYSCONFIG_NOSTDBY			(1 << 4)
#घोषणा OMAP4_UHH_SYSCONFIG_SOFTRESET			(1 << 0)

#घोषणा OMAP4_P1_MODE_CLEAR				(3 << 16)
#घोषणा OMAP4_P1_MODE_TLL				(1 << 16)
#घोषणा OMAP4_P1_MODE_HSIC				(3 << 16)
#घोषणा OMAP4_P2_MODE_CLEAR				(3 << 18)
#घोषणा OMAP4_P2_MODE_TLL				(1 << 18)
#घोषणा OMAP4_P2_MODE_HSIC				(3 << 18)

#घोषणा	OMAP_UHH_DEBUG_CSR				(0x44)

/* Values of UHH_REVISION - Note: these are not given in the TRM */
#घोषणा OMAP_USBHS_REV1		0x00000010	/* OMAP3 */
#घोषणा OMAP_USBHS_REV2		0x50700100	/* OMAP4 */

#घोषणा is_omap_usbhs_rev1(x)	(x->usbhs_rev == OMAP_USBHS_REV1)
#घोषणा is_omap_usbhs_rev2(x)	(x->usbhs_rev == OMAP_USBHS_REV2)

#घोषणा is_ehci_phy_mode(x)	(x == OMAP_EHCI_PORT_MODE_PHY)
#घोषणा is_ehci_tll_mode(x)	(x == OMAP_EHCI_PORT_MODE_TLL)
#घोषणा is_ehci_hsic_mode(x)	(x == OMAP_EHCI_PORT_MODE_HSIC)


काष्ठा usbhs_hcd_omap अणु
	पूर्णांक				nports;
	काष्ठा clk			**uपंचांगi_clk;
	काष्ठा clk			**hsic60m_clk;
	काष्ठा clk			**hsic480m_clk;

	काष्ठा clk			*xclk60mhsp1_ck;
	काष्ठा clk			*xclk60mhsp2_ck;
	काष्ठा clk			*uपंचांगi_p1_gfclk;
	काष्ठा clk			*uपंचांगi_p2_gfclk;
	काष्ठा clk			*init_60m_fclk;
	काष्ठा clk			*ehci_logic_fck;

	व्योम __iomem			*uhh_base;

	काष्ठा usbhs_omap_platक्रमm_data	*pdata;

	u32				usbhs_rev;
पूर्ण;
/*-------------------------------------------------------------------------*/

अटल स्थिर अक्षर usbhs_driver_name[] = USBHS_DRIVER_NAME;
अटल u64 usbhs_dmamask = DMA_BIT_MASK(32);

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम usbhs_ग_लिखो(व्योम __iomem *base, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, base + reg);
पूर्ण

अटल अंतरभूत u32 usbhs_पढ़ो(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl_relaxed(base + reg);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Map 'enum usbhs_omap_port_mode' found in <linux/platक्रमm_data/usb-omap.h>
 * to the device tree binding portN-mode found in
 * 'Documentation/devicetree/bindings/mfd/omap-usb-host.txt'
 */
अटल स्थिर अक्षर * स्थिर port_modes[] = अणु
	[OMAP_USBHS_PORT_MODE_UNUSED]	= "",
	[OMAP_EHCI_PORT_MODE_PHY]	= "ehci-phy",
	[OMAP_EHCI_PORT_MODE_TLL]	= "ehci-tll",
	[OMAP_EHCI_PORT_MODE_HSIC]	= "ehci-hsic",
	[OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0]	= "ohci-phy-6pin-datse0",
	[OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM]	= "ohci-phy-6pin-dpdm",
	[OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0]	= "ohci-phy-3pin-datse0",
	[OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM]	= "ohci-phy-4pin-dpdm",
	[OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0]	= "ohci-tll-6pin-datse0",
	[OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM]	= "ohci-tll-6pin-dpdm",
	[OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0]	= "ohci-tll-3pin-datse0",
	[OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM]	= "ohci-tll-4pin-dpdm",
	[OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0]	= "ohci-tll-2pin-datse0",
	[OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM]	= "ohci-tll-2pin-dpdm",
पूर्ण;

अटल काष्ठा platक्रमm_device *omap_usbhs_alloc_child(स्थिर अक्षर *name,
			काष्ठा resource	*res, पूर्णांक num_resources, व्योम *pdata,
			माप_प्रकार pdata_size, काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device	*child;
	पूर्णांक			ret;

	child = platक्रमm_device_alloc(name, 0);

	अगर (!child) अणु
		dev_err(dev, "platform_device_alloc %s failed\n", name);
		जाओ err_end;
	पूर्ण

	ret = platक्रमm_device_add_resources(child, res, num_resources);
	अगर (ret) अणु
		dev_err(dev, "platform_device_add_resources failed\n");
		जाओ err_alloc;
	पूर्ण

	ret = platक्रमm_device_add_data(child, pdata, pdata_size);
	अगर (ret) अणु
		dev_err(dev, "platform_device_add_data failed\n");
		जाओ err_alloc;
	पूर्ण

	child->dev.dma_mask		= &usbhs_dmamask;
	dma_set_coherent_mask(&child->dev, DMA_BIT_MASK(32));
	child->dev.parent		= dev;

	ret = platक्रमm_device_add(child);
	अगर (ret) अणु
		dev_err(dev, "platform_device_add failed\n");
		जाओ err_alloc;
	पूर्ण

	वापस child;

err_alloc:
	platक्रमm_device_put(child);

err_end:
	वापस शून्य;
पूर्ण

अटल पूर्णांक omap_usbhs_alloc_children(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device				*dev = &pdev->dev;
	काष्ठा usbhs_omap_platक्रमm_data		*pdata = dev_get_platdata(dev);
	काष्ठा platक्रमm_device			*ehci;
	काष्ठा platक्रमm_device			*ohci;
	काष्ठा resource				*res;
	काष्ठा resource				resources[2];
	पूर्णांक					ret;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ehci");
	अगर (!res) अणु
		dev_err(dev, "EHCI get resource IORESOURCE_MEM failed\n");
		ret = -ENODEV;
		जाओ err_end;
	पूर्ण
	resources[0] = *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "ehci-irq");
	अगर (!res) अणु
		dev_err(dev, " EHCI get resource IORESOURCE_IRQ failed\n");
		ret = -ENODEV;
		जाओ err_end;
	पूर्ण
	resources[1] = *res;

	ehci = omap_usbhs_alloc_child(OMAP_EHCI_DEVICE, resources, 2, pdata,
		माप(*pdata), dev);

	अगर (!ehci) अणु
		dev_err(dev, "omap_usbhs_alloc_child failed\n");
		ret = -ENOMEM;
		जाओ err_end;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ohci");
	अगर (!res) अणु
		dev_err(dev, "OHCI get resource IORESOURCE_MEM failed\n");
		ret = -ENODEV;
		जाओ err_ehci;
	पूर्ण
	resources[0] = *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "ohci-irq");
	अगर (!res) अणु
		dev_err(dev, "OHCI get resource IORESOURCE_IRQ failed\n");
		ret = -ENODEV;
		जाओ err_ehci;
	पूर्ण
	resources[1] = *res;

	ohci = omap_usbhs_alloc_child(OMAP_OHCI_DEVICE, resources, 2, pdata,
		माप(*pdata), dev);
	अगर (!ohci) अणु
		dev_err(dev, "omap_usbhs_alloc_child failed\n");
		ret = -ENOMEM;
		जाओ err_ehci;
	पूर्ण

	वापस 0;

err_ehci:
	platक्रमm_device_unरेजिस्टर(ehci);

err_end:
	वापस ret;
पूर्ण

अटल bool is_ohci_port(क्रमागत usbhs_omap_port_mode pmode)
अणु
	चयन (pmode) अणु
	हाल OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0:
	हाल OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM:
	हाल OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0:
	हाल OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM:
	हाल OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0:
	हाल OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM:
	हाल OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0:
	हाल OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM:
	हाल OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0:
	हाल OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक usbhs_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा usbhs_hcd_omap		*omap = dev_get_drvdata(dev);
	काष्ठा usbhs_omap_platक्रमm_data	*pdata = omap->pdata;
	पूर्णांक i, r;

	dev_dbg(dev, "usbhs_runtime_resume\n");

	omap_tll_enable(pdata);

	अगर (!IS_ERR(omap->ehci_logic_fck))
		clk_prepare_enable(omap->ehci_logic_fck);

	क्रम (i = 0; i < omap->nports; i++) अणु
		चयन (pdata->port_mode[i]) अणु
		हाल OMAP_EHCI_PORT_MODE_HSIC:
			अगर (!IS_ERR(omap->hsic60m_clk[i])) अणु
				r = clk_prepare_enable(omap->hsic60m_clk[i]);
				अगर (r) अणु
					dev_err(dev,
					 "Can't enable port %d hsic60m clk:%d\n",
					 i, r);
				पूर्ण
			पूर्ण

			अगर (!IS_ERR(omap->hsic480m_clk[i])) अणु
				r = clk_prepare_enable(omap->hsic480m_clk[i]);
				अगर (r) अणु
					dev_err(dev,
					 "Can't enable port %d hsic480m clk:%d\n",
					 i, r);
				पूर्ण
			पूर्ण
			fallthrough;	/* as HSIC mode needs uपंचांगi_clk */

		हाल OMAP_EHCI_PORT_MODE_TLL:
			अगर (!IS_ERR(omap->uपंचांगi_clk[i])) अणु
				r = clk_prepare_enable(omap->uपंचांगi_clk[i]);
				अगर (r) अणु
					dev_err(dev,
					 "Can't enable port %d clk : %d\n",
					 i, r);
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbhs_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा usbhs_hcd_omap		*omap = dev_get_drvdata(dev);
	काष्ठा usbhs_omap_platक्रमm_data	*pdata = omap->pdata;
	पूर्णांक i;

	dev_dbg(dev, "usbhs_runtime_suspend\n");

	क्रम (i = 0; i < omap->nports; i++) अणु
		चयन (pdata->port_mode[i]) अणु
		हाल OMAP_EHCI_PORT_MODE_HSIC:
			अगर (!IS_ERR(omap->hsic60m_clk[i]))
				clk_disable_unprepare(omap->hsic60m_clk[i]);

			अगर (!IS_ERR(omap->hsic480m_clk[i]))
				clk_disable_unprepare(omap->hsic480m_clk[i]);
			fallthrough;	/* as uपंचांगi_clks were used in HSIC mode */

		हाल OMAP_EHCI_PORT_MODE_TLL:
			अगर (!IS_ERR(omap->uपंचांगi_clk[i]))
				clk_disable_unprepare(omap->uपंचांगi_clk[i]);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(omap->ehci_logic_fck))
		clk_disable_unprepare(omap->ehci_logic_fck);

	omap_tll_disable(pdata);

	वापस 0;
पूर्ण

अटल अचिन्हित omap_usbhs_rev1_hostconfig(काष्ठा usbhs_hcd_omap *omap,
						अचिन्हित reg)
अणु
	काष्ठा usbhs_omap_platक्रमm_data	*pdata = omap->pdata;
	पूर्णांक i;

	क्रम (i = 0; i < omap->nports; i++) अणु
		चयन (pdata->port_mode[i]) अणु
		हाल OMAP_USBHS_PORT_MODE_UNUSED:
			reg &= ~(OMAP_UHH_HOSTCONFIG_P1_CONNECT_STATUS << i);
			अवरोध;
		हाल OMAP_EHCI_PORT_MODE_PHY:
			अगर (pdata->single_ulpi_bypass)
				अवरोध;

			अगर (i == 0)
				reg &= ~OMAP_UHH_HOSTCONFIG_ULPI_P1_BYPASS;
			अन्यथा
				reg &= ~(OMAP_UHH_HOSTCONFIG_ULPI_P2_BYPASS
								<< (i-1));
			अवरोध;
		शेष:
			अगर (pdata->single_ulpi_bypass)
				अवरोध;

			अगर (i == 0)
				reg |= OMAP_UHH_HOSTCONFIG_ULPI_P1_BYPASS;
			अन्यथा
				reg |= OMAP_UHH_HOSTCONFIG_ULPI_P2_BYPASS
								<< (i-1);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pdata->single_ulpi_bypass) अणु
		/* bypass ULPI only अगर none of the ports use PHY mode */
		reg |= OMAP_UHH_HOSTCONFIG_ULPI_BYPASS;

		क्रम (i = 0; i < omap->nports; i++) अणु
			अगर (is_ehci_phy_mode(pdata->port_mode[i])) अणु
				reg &= ~OMAP_UHH_HOSTCONFIG_ULPI_BYPASS;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस reg;
पूर्ण

अटल अचिन्हित omap_usbhs_rev2_hostconfig(काष्ठा usbhs_hcd_omap *omap,
						अचिन्हित reg)
अणु
	काष्ठा usbhs_omap_platक्रमm_data	*pdata = omap->pdata;
	पूर्णांक i;

	क्रम (i = 0; i < omap->nports; i++) अणु
		/* Clear port mode fields क्रम PHY mode */
		reg &= ~(OMAP4_P1_MODE_CLEAR << 2 * i);

		अगर (is_ehci_tll_mode(pdata->port_mode[i]) ||
				(is_ohci_port(pdata->port_mode[i])))
			reg |= OMAP4_P1_MODE_TLL << 2 * i;
		अन्यथा अगर (is_ehci_hsic_mode(pdata->port_mode[i]))
			reg |= OMAP4_P1_MODE_HSIC << 2 * i;
	पूर्ण

	वापस reg;
पूर्ण

अटल व्योम omap_usbhs_init(काष्ठा device *dev)
अणु
	काष्ठा usbhs_hcd_omap		*omap = dev_get_drvdata(dev);
	अचिन्हित			reg;

	dev_dbg(dev, "starting TI HSUSB Controller\n");

	pm_runसमय_get_sync(dev);

	reg = usbhs_पढ़ो(omap->uhh_base, OMAP_UHH_HOSTCONFIG);
	/* setup ULPI bypass and burst configurations */
	reg |= (OMAP_UHH_HOSTCONFIG_INCR4_BURST_EN
			| OMAP_UHH_HOSTCONFIG_INCR8_BURST_EN
			| OMAP_UHH_HOSTCONFIG_INCR16_BURST_EN);
	reg |= OMAP4_UHH_HOSTCONFIG_APP_START_CLK;
	reg &= ~OMAP_UHH_HOSTCONFIG_INCRX_ALIGN_EN;

	चयन (omap->usbhs_rev) अणु
	हाल OMAP_USBHS_REV1:
		reg = omap_usbhs_rev1_hostconfig(omap, reg);
		अवरोध;

	हाल OMAP_USBHS_REV2:
		reg = omap_usbhs_rev2_hostconfig(omap, reg);
		अवरोध;

	शेष:	/* newer revisions */
		reg = omap_usbhs_rev2_hostconfig(omap, reg);
		अवरोध;
	पूर्ण

	usbhs_ग_लिखो(omap->uhh_base, OMAP_UHH_HOSTCONFIG, reg);
	dev_dbg(dev, "UHH setup done, uhh_hostconfig=%x\n", reg);

	pm_runसमय_put_sync(dev);
पूर्ण

अटल पूर्णांक usbhs_omap_get_dt_pdata(काष्ठा device *dev,
					काष्ठा usbhs_omap_platक्रमm_data *pdata)
अणु
	पूर्णांक ret, i;
	काष्ठा device_node *node = dev->of_node;

	ret = of_property_पढ़ो_u32(node, "num-ports", &pdata->nports);
	अगर (ret)
		pdata->nports = 0;

	अगर (pdata->nports > OMAP3_HS_USB_PORTS) अणु
		dev_warn(dev, "Too many num_ports <%d> in device tree. Max %d\n",
				pdata->nports, OMAP3_HS_USB_PORTS);
		वापस -ENODEV;
	पूर्ण

	/* get port modes */
	क्रम (i = 0; i < OMAP3_HS_USB_PORTS; i++) अणु
		अक्षर prop[11];
		स्थिर अक्षर *mode;

		pdata->port_mode[i] = OMAP_USBHS_PORT_MODE_UNUSED;

		snम_लिखो(prop, माप(prop), "port%d-mode", i + 1);
		ret = of_property_पढ़ो_string(node, prop, &mode);
		अगर (ret < 0)
			जारी;

		/* get 'enum usbhs_omap_port_mode' from port mode string */
		ret = match_string(port_modes, ARRAY_SIZE(port_modes), mode);
		अगर (ret < 0) अणु
			dev_warn(dev, "Invalid port%d-mode \"%s\" in device tree\n",
					i, mode);
			वापस -ENODEV;
		पूर्ण

		dev_dbg(dev, "port%d-mode: %s -> %d\n", i, mode, ret);
		pdata->port_mode[i] = ret;
	पूर्ण

	/* get flags */
	pdata->single_ulpi_bypass = of_property_पढ़ो_bool(node,
						"single-ulpi-bypass");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id usbhs_child_match_table[] = अणु
	अणु .compatible = "ti,ehci-omap", पूर्ण,
	अणु .compatible = "ti,ohci-omap3", पूर्ण,
	अणु पूर्ण
पूर्ण;

/**
 * usbhs_omap_probe - initialize TI-based HCDs
 *
 * Allocates basic resources क्रम this USB host controller.
 *
 * @pdev: Poपूर्णांकer to this device's platक्रमm device काष्ठाure
 */
अटल पूर्णांक usbhs_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device			*dev =  &pdev->dev;
	काष्ठा usbhs_omap_platक्रमm_data	*pdata = dev_get_platdata(dev);
	काष्ठा usbhs_hcd_omap		*omap;
	काष्ठा resource			*res;
	पूर्णांक				ret = 0;
	पूर्णांक				i;
	bool				need_logic_fck;

	अगर (dev->of_node) अणु
		/* For DT boot we populate platक्रमm data from OF node */
		pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		ret = usbhs_omap_get_dt_pdata(dev, pdata);
		अगर (ret)
			वापस ret;

		dev->platक्रमm_data = pdata;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(dev, "Missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdata->nports > OMAP3_HS_USB_PORTS) अणु
		dev_info(dev, "Too many num_ports <%d> in platform_data. Max %d\n",
				pdata->nports, OMAP3_HS_USB_PORTS);
		वापस -ENODEV;
	पूर्ण

	omap = devm_kzalloc(dev, माप(*omap), GFP_KERNEL);
	अगर (!omap) अणु
		dev_err(dev, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	omap->uhh_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(omap->uhh_base))
		वापस PTR_ERR(omap->uhh_base);

	omap->pdata = pdata;

	/* Initialize the TLL subप्रणाली */
	omap_tll_init(pdata);

	pm_runसमय_enable(dev);

	platक्रमm_set_drvdata(pdev, omap);
	pm_runसमय_get_sync(dev);

	omap->usbhs_rev = usbhs_पढ़ो(omap->uhh_base, OMAP_UHH_REVISION);

	/* we need to call runसमय suspend beक्रमe we update omap->nports
	 * to prevent unbalanced clk_disable()
	 */
	pm_runसमय_put_sync(dev);

	/*
	 * If platक्रमm data contains nports then use that
	 * अन्यथा make out number of ports from USBHS revision
	 */
	अगर (pdata->nports) अणु
		omap->nports = pdata->nports;
	पूर्ण अन्यथा अणु
		चयन (omap->usbhs_rev) अणु
		हाल OMAP_USBHS_REV1:
			omap->nports = 3;
			अवरोध;
		हाल OMAP_USBHS_REV2:
			omap->nports = 2;
			अवरोध;
		शेष:
			omap->nports = OMAP3_HS_USB_PORTS;
			dev_dbg(dev,
			 "USB HOST Rev:0x%x not recognized, assuming %d ports\n",
			 omap->usbhs_rev, omap->nports);
			अवरोध;
		पूर्ण
		pdata->nports = omap->nports;
	पूर्ण

	i = माप(काष्ठा clk *) * omap->nports;
	omap->uपंचांगi_clk = devm_kzalloc(dev, i, GFP_KERNEL);
	omap->hsic480m_clk = devm_kzalloc(dev, i, GFP_KERNEL);
	omap->hsic60m_clk = devm_kzalloc(dev, i, GFP_KERNEL);

	अगर (!omap->uपंचांगi_clk || !omap->hsic480m_clk || !omap->hsic60m_clk) अणु
		dev_err(dev, "Memory allocation failed\n");
		ret = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	/* Set all घड़ीs as invalid to begin with */
	omap->ehci_logic_fck = ERR_PTR(-ENODEV);
	omap->init_60m_fclk = ERR_PTR(-ENODEV);
	omap->uपंचांगi_p1_gfclk = ERR_PTR(-ENODEV);
	omap->uपंचांगi_p2_gfclk = ERR_PTR(-ENODEV);
	omap->xclk60mhsp1_ck = ERR_PTR(-ENODEV);
	omap->xclk60mhsp2_ck = ERR_PTR(-ENODEV);

	क्रम (i = 0; i < omap->nports; i++) अणु
		omap->uपंचांगi_clk[i] = ERR_PTR(-ENODEV);
		omap->hsic480m_clk[i] = ERR_PTR(-ENODEV);
		omap->hsic60m_clk[i] = ERR_PTR(-ENODEV);
	पूर्ण

	/* क्रम OMAP3 i.e. USBHS REV1 */
	अगर (omap->usbhs_rev == OMAP_USBHS_REV1) अणु
		need_logic_fck = false;
		क्रम (i = 0; i < omap->nports; i++) अणु
			अगर (is_ehci_phy_mode(pdata->port_mode[i]) ||
			    is_ehci_tll_mode(pdata->port_mode[i]) ||
			    is_ehci_hsic_mode(pdata->port_mode[i]))

				need_logic_fck |= true;
		पूर्ण

		अगर (need_logic_fck) अणु
			omap->ehci_logic_fck = devm_clk_get(dev,
							    "usbhost_120m_fck");
			अगर (IS_ERR(omap->ehci_logic_fck)) अणु
				ret = PTR_ERR(omap->ehci_logic_fck);
				dev_err(dev, "usbhost_120m_fck failed:%d\n",
					ret);
				जाओ err_mem;
			पूर्ण
		पूर्ण
		जाओ initialize;
	पूर्ण

	/* क्रम OMAP4+ i.e. USBHS REV2+ */
	omap->uपंचांगi_p1_gfclk = devm_clk_get(dev, "utmi_p1_gfclk");
	अगर (IS_ERR(omap->uपंचांगi_p1_gfclk)) अणु
		ret = PTR_ERR(omap->uपंचांगi_p1_gfclk);
		dev_err(dev, "utmi_p1_gfclk failed error:%d\n", ret);
		जाओ err_mem;
	पूर्ण

	omap->uपंचांगi_p2_gfclk = devm_clk_get(dev, "utmi_p2_gfclk");
	अगर (IS_ERR(omap->uपंचांगi_p2_gfclk)) अणु
		ret = PTR_ERR(omap->uपंचांगi_p2_gfclk);
		dev_err(dev, "utmi_p2_gfclk failed error:%d\n", ret);
		जाओ err_mem;
	पूर्ण

	omap->xclk60mhsp1_ck = devm_clk_get(dev, "refclk_60m_ext_p1");
	अगर (IS_ERR(omap->xclk60mhsp1_ck)) अणु
		ret = PTR_ERR(omap->xclk60mhsp1_ck);
		dev_err(dev, "refclk_60m_ext_p1 failed error:%d\n", ret);
		जाओ err_mem;
	पूर्ण

	omap->xclk60mhsp2_ck = devm_clk_get(dev, "refclk_60m_ext_p2");
	अगर (IS_ERR(omap->xclk60mhsp2_ck)) अणु
		ret = PTR_ERR(omap->xclk60mhsp2_ck);
		dev_err(dev, "refclk_60m_ext_p2 failed error:%d\n", ret);
		जाओ err_mem;
	पूर्ण

	omap->init_60m_fclk = devm_clk_get(dev, "refclk_60m_int");
	अगर (IS_ERR(omap->init_60m_fclk)) अणु
		ret = PTR_ERR(omap->init_60m_fclk);
		dev_err(dev, "refclk_60m_int failed error:%d\n", ret);
		जाओ err_mem;
	पूर्ण

	क्रम (i = 0; i < omap->nports; i++) अणु
		अक्षर clkname[30];

		/* घड़ी names are indexed from 1*/
		snम_लिखो(clkname, माप(clkname),
				"usb_host_hs_utmi_p%d_clk", i + 1);

		/* If a घड़ी is not found we won't bail out as not all
		 * platक्रमms have all घड़ीs and we can function without
		 * them
		 */
		omap->uपंचांगi_clk[i] = devm_clk_get(dev, clkname);
		अगर (IS_ERR(omap->uपंचांगi_clk[i])) अणु
			ret = PTR_ERR(omap->uपंचांगi_clk[i]);
			dev_err(dev, "Failed to get clock : %s : %d\n",
				clkname, ret);
			जाओ err_mem;
		पूर्ण

		snम_लिखो(clkname, माप(clkname),
				"usb_host_hs_hsic480m_p%d_clk", i + 1);
		omap->hsic480m_clk[i] = devm_clk_get(dev, clkname);
		अगर (IS_ERR(omap->hsic480m_clk[i])) अणु
			ret = PTR_ERR(omap->hsic480m_clk[i]);
			dev_err(dev, "Failed to get clock : %s : %d\n",
				clkname, ret);
			जाओ err_mem;
		पूर्ण

		snम_लिखो(clkname, माप(clkname),
				"usb_host_hs_hsic60m_p%d_clk", i + 1);
		omap->hsic60m_clk[i] = devm_clk_get(dev, clkname);
		अगर (IS_ERR(omap->hsic60m_clk[i])) अणु
			ret = PTR_ERR(omap->hsic60m_clk[i]);
			dev_err(dev, "Failed to get clock : %s : %d\n",
				clkname, ret);
			जाओ err_mem;
		पूर्ण
	पूर्ण

	अगर (is_ehci_phy_mode(pdata->port_mode[0])) अणु
		ret = clk_set_parent(omap->uपंचांगi_p1_gfclk,
					omap->xclk60mhsp1_ck);
		अगर (ret != 0) अणु
			dev_err(dev, "xclk60mhsp1_ck set parent failed: %d\n",
				ret);
			जाओ err_mem;
		पूर्ण
	पूर्ण अन्यथा अगर (is_ehci_tll_mode(pdata->port_mode[0])) अणु
		ret = clk_set_parent(omap->uपंचांगi_p1_gfclk,
					omap->init_60m_fclk);
		अगर (ret != 0) अणु
			dev_err(dev, "P0 init_60m_fclk set parent failed: %d\n",
				ret);
			जाओ err_mem;
		पूर्ण
	पूर्ण

	अगर (is_ehci_phy_mode(pdata->port_mode[1])) अणु
		ret = clk_set_parent(omap->uपंचांगi_p2_gfclk,
					omap->xclk60mhsp2_ck);
		अगर (ret != 0) अणु
			dev_err(dev, "xclk60mhsp2_ck set parent failed: %d\n",
				ret);
			जाओ err_mem;
		पूर्ण
	पूर्ण अन्यथा अगर (is_ehci_tll_mode(pdata->port_mode[1])) अणु
		ret = clk_set_parent(omap->uपंचांगi_p2_gfclk,
						omap->init_60m_fclk);
		अगर (ret != 0) अणु
			dev_err(dev, "P1 init_60m_fclk set parent failed: %d\n",
				ret);
			जाओ err_mem;
		पूर्ण
	पूर्ण

initialize:
	omap_usbhs_init(dev);

	अगर (dev->of_node) अणु
		ret = of_platक्रमm_populate(dev->of_node,
				usbhs_child_match_table, शून्य, dev);

		अगर (ret) अणु
			dev_err(dev, "Failed to create DT children: %d\n", ret);
			जाओ err_mem;
		पूर्ण

	पूर्ण अन्यथा अणु
		ret = omap_usbhs_alloc_children(pdev);
		अगर (ret) अणु
			dev_err(dev, "omap_usbhs_alloc_children failed: %d\n",
						ret);
			जाओ err_mem;
		पूर्ण
	पूर्ण

	वापस 0;

err_mem:
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक usbhs_omap_हटाओ_child(काष्ठा device *dev, व्योम *data)
अणु
	dev_info(dev, "unregistering\n");
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

/**
 * usbhs_omap_हटाओ - shutकरोwn processing क्रम UHH & TLL HCDs
 * @pdev: USB Host Controller being हटाओd
 *
 * Reverses the effect of usbhs_omap_probe().
 */
अटल पूर्णांक usbhs_omap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	/* हटाओ children */
	device_क्रम_each_child(&pdev->dev, शून्य, usbhs_omap_हटाओ_child);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops usbhsomap_dev_pm_ops = अणु
	.runसमय_suspend	= usbhs_runसमय_suspend,
	.runसमय_resume		= usbhs_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id usbhs_omap_dt_ids[] = अणु
	अणु .compatible = "ti,usbhs-host" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, usbhs_omap_dt_ids);


अटल काष्ठा platक्रमm_driver usbhs_omap_driver = अणु
	.driver = अणु
		.name		= usbhs_driver_name,
		.pm		= &usbhsomap_dev_pm_ops,
		.of_match_table = usbhs_omap_dt_ids,
	पूर्ण,
	.probe		= usbhs_omap_probe,
	.हटाओ		= usbhs_omap_हटाओ,
पूर्ण;

MODULE_AUTHOR("Keshava Munegowda <keshava_mgowda@ti.com>");
MODULE_AUTHOR("Roger Quadros <rogerq@ti.com>");
MODULE_ALIAS("platform:" USBHS_DRIVER_NAME);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("usb host common core driver for omap EHCI and OHCI");

अटल पूर्णांक omap_usbhs_drvinit(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&usbhs_omap_driver);
पूर्ण

/*
 * init beक्रमe ehci and ohci drivers;
 * The usbhs core driver should be initialized much beक्रमe
 * the omap ehci and ohci probe functions are called.
 * This usbhs core driver should be initialized after
 * usb tll driver
 */
fs_initcall_sync(omap_usbhs_drvinit);

अटल व्योम omap_usbhs_drvनिकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&usbhs_omap_driver);
पूर्ण
module_निकास(omap_usbhs_drvनिकास);
