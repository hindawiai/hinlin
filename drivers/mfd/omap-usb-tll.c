<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * omap-usb-tll.c - The USB TLL driver क्रम OMAP EHCI & OHCI
 *
 * Copyright (C) 2012-2013 Texas Instruments Incorporated - https://www.ti.com
 * Author: Keshava Munegowda <keshava_mgowda@ti.com>
 * Author: Roger Quadros <rogerq@ti.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_data/usb-omap.h>
#समावेश <linux/of.h>

#समावेश "omap-usb.h"

#घोषणा USBTLL_DRIVER_NAME	"usbhs_tll"

/* TLL Register Set */
#घोषणा	OMAP_USBTLL_REVISION				(0x00)
#घोषणा	OMAP_USBTLL_SYSCONFIG				(0x10)
#घोषणा	OMAP_USBTLL_SYSCONFIG_CACTIVITY			(1 << 8)
#घोषणा	OMAP_USBTLL_SYSCONFIG_SIDLEMODE			(1 << 3)
#घोषणा	OMAP_USBTLL_SYSCONFIG_ENAWAKEUP			(1 << 2)
#घोषणा	OMAP_USBTLL_SYSCONFIG_SOFTRESET			(1 << 1)
#घोषणा	OMAP_USBTLL_SYSCONFIG_AUTOIDLE			(1 << 0)

#घोषणा	OMAP_USBTLL_SYSSTATUS				(0x14)
#घोषणा	OMAP_USBTLL_SYSSTATUS_RESETDONE			(1 << 0)

#घोषणा	OMAP_USBTLL_IRQSTATUS				(0x18)
#घोषणा	OMAP_USBTLL_IRQENABLE				(0x1C)

#घोषणा	OMAP_TLL_SHARED_CONF				(0x30)
#घोषणा	OMAP_TLL_SHARED_CONF_USB_90D_DDR_EN		(1 << 6)
#घोषणा	OMAP_TLL_SHARED_CONF_USB_180D_SDR_EN		(1 << 5)
#घोषणा	OMAP_TLL_SHARED_CONF_USB_DIVRATION		(1 << 2)
#घोषणा	OMAP_TLL_SHARED_CONF_FCLK_REQ			(1 << 1)
#घोषणा	OMAP_TLL_SHARED_CONF_FCLK_IS_ON			(1 << 0)

#घोषणा	OMAP_TLL_CHANNEL_CONF(num)			(0x040 + 0x004 * num)
#घोषणा OMAP_TLL_CHANNEL_CONF_FSLSMODE_SHIFT		24
#घोषणा OMAP_TLL_CHANNEL_CONF_DRVVBUS			(1 << 16)
#घोषणा OMAP_TLL_CHANNEL_CONF_CHRGVBUS			(1 << 15)
#घोषणा	OMAP_TLL_CHANNEL_CONF_ULPINOBITSTUFF		(1 << 11)
#घोषणा	OMAP_TLL_CHANNEL_CONF_ULPI_ULPIAUTOIDLE		(1 << 10)
#घोषणा	OMAP_TLL_CHANNEL_CONF_UTMIAUTOIDLE		(1 << 9)
#घोषणा	OMAP_TLL_CHANNEL_CONF_ULPIDDRMODE		(1 << 8)
#घोषणा OMAP_TLL_CHANNEL_CONF_MODE_TRANSPARENT_UTMI	(2 << 1)
#घोषणा OMAP_TLL_CHANNEL_CONF_CHANMODE_FSLS		(1 << 1)
#घोषणा	OMAP_TLL_CHANNEL_CONF_CHANEN			(1 << 0)

#घोषणा OMAP_TLL_FSLSMODE_6PIN_PHY_DAT_SE0		0x0
#घोषणा OMAP_TLL_FSLSMODE_6PIN_PHY_DP_DM		0x1
#घोषणा OMAP_TLL_FSLSMODE_3PIN_PHY			0x2
#घोषणा OMAP_TLL_FSLSMODE_4PIN_PHY			0x3
#घोषणा OMAP_TLL_FSLSMODE_6PIN_TLL_DAT_SE0		0x4
#घोषणा OMAP_TLL_FSLSMODE_6PIN_TLL_DP_DM		0x5
#घोषणा OMAP_TLL_FSLSMODE_3PIN_TLL			0x6
#घोषणा OMAP_TLL_FSLSMODE_4PIN_TLL			0x7
#घोषणा OMAP_TLL_FSLSMODE_2PIN_TLL_DAT_SE0		0xA
#घोषणा OMAP_TLL_FSLSMODE_2PIN_DAT_DP_DM		0xB

#घोषणा	OMAP_TLL_ULPI_FUNCTION_CTRL(num)		(0x804 + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_INTERFACE_CTRL(num)		(0x807 + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_OTG_CTRL(num)			(0x80A + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_INT_EN_RISE(num)			(0x80D + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_INT_EN_FALL(num)			(0x810 + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_INT_STATUS(num)			(0x813 + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_INT_LATCH(num)			(0x814 + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_DEBUG(num)			(0x815 + 0x100 * num)
#घोषणा	OMAP_TLL_ULPI_SCRATCH_REGISTER(num)		(0x816 + 0x100 * num)

#घोषणा OMAP_REV2_TLL_CHANNEL_COUNT			2
#घोषणा OMAP_TLL_CHANNEL_COUNT				3
#घोषणा OMAP_TLL_CHANNEL_1_EN_MASK			(1 << 0)
#घोषणा OMAP_TLL_CHANNEL_2_EN_MASK			(1 << 1)
#घोषणा OMAP_TLL_CHANNEL_3_EN_MASK			(1 << 2)

/* Values of USBTLL_REVISION - Note: these are not given in the TRM */
#घोषणा OMAP_USBTLL_REV1		0x00000015	/* OMAP3 */
#घोषणा OMAP_USBTLL_REV2		0x00000018	/* OMAP 3630 */
#घोषणा OMAP_USBTLL_REV3		0x00000004	/* OMAP4 */
#घोषणा OMAP_USBTLL_REV4		0x00000006	/* OMAP5 */

#घोषणा is_ehci_tll_mode(x)	(x == OMAP_EHCI_PORT_MODE_TLL)

/* only PHY and UNUSED modes करोn't need TLL */
#घोषणा omap_usb_mode_needs_tll(x)	((x) != OMAP_USBHS_PORT_MODE_UNUSED &&\
					 (x) != OMAP_EHCI_PORT_MODE_PHY)

काष्ठा usbtll_omap अणु
	व्योम __iomem	*base;
	पूर्णांक		nch;		/* num. of channels */
	काष्ठा clk	*ch_clk[];	/* must be the last member */
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल स्थिर अक्षर usbtll_driver_name[] = USBTLL_DRIVER_NAME;
अटल काष्ठा device	*tll_dev;
अटल DEFINE_SPINLOCK(tll_lock);	/* serialize access to tll_dev */

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम usbtll_ग_लिखो(व्योम __iomem *base, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, base + reg);
पूर्ण

अटल अंतरभूत u32 usbtll_पढ़ो(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl_relaxed(base + reg);
पूर्ण

अटल अंतरभूत व्योम usbtll_ग_लिखोb(व्योम __iomem *base, u32 reg, u8 val)
अणु
	ग_लिखोb_relaxed(val, base + reg);
पूर्ण

अटल अंतरभूत u8 usbtll_पढ़ोb(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोb_relaxed(base + reg);
पूर्ण

/*-------------------------------------------------------------------------*/

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

/*
 * convert the port-mode क्रमागत to a value we can use in the FSLSMODE
 * field of USBTLL_CHANNEL_CONF
 */
अटल अचिन्हित ohci_omap3_fslsmode(क्रमागत usbhs_omap_port_mode mode)
अणु
	चयन (mode) अणु
	हाल OMAP_USBHS_PORT_MODE_UNUSED:
	हाल OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0:
		वापस OMAP_TLL_FSLSMODE_6PIN_PHY_DAT_SE0;

	हाल OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM:
		वापस OMAP_TLL_FSLSMODE_6PIN_PHY_DP_DM;

	हाल OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0:
		वापस OMAP_TLL_FSLSMODE_3PIN_PHY;

	हाल OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM:
		वापस OMAP_TLL_FSLSMODE_4PIN_PHY;

	हाल OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0:
		वापस OMAP_TLL_FSLSMODE_6PIN_TLL_DAT_SE0;

	हाल OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM:
		वापस OMAP_TLL_FSLSMODE_6PIN_TLL_DP_DM;

	हाल OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0:
		वापस OMAP_TLL_FSLSMODE_3PIN_TLL;

	हाल OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM:
		वापस OMAP_TLL_FSLSMODE_4PIN_TLL;

	हाल OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0:
		वापस OMAP_TLL_FSLSMODE_2PIN_TLL_DAT_SE0;

	हाल OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM:
		वापस OMAP_TLL_FSLSMODE_2PIN_DAT_DP_DM;
	शेष:
		pr_warn("Invalid port mode, using default\n");
		वापस OMAP_TLL_FSLSMODE_6PIN_PHY_DAT_SE0;
	पूर्ण
पूर्ण

/**
 * usbtll_omap_probe - initialize TI-based HCDs
 *
 * Allocates basic resources क्रम this USB host controller.
 *
 * @pdev: Poपूर्णांकer to this device's platक्रमm device काष्ठाure
 */
अटल पूर्णांक usbtll_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device				*dev =  &pdev->dev;
	काष्ठा resource				*res;
	काष्ठा usbtll_omap			*tll;
	व्योम __iomem				*base;
	पूर्णांक					i, nch, ver;

	dev_dbg(dev, "starting TI HSUSB TLL Controller\n");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	ver = usbtll_पढ़ो(base, OMAP_USBTLL_REVISION);
	चयन (ver) अणु
	हाल OMAP_USBTLL_REV1:
	हाल OMAP_USBTLL_REV4:
		nch = OMAP_TLL_CHANNEL_COUNT;
		अवरोध;
	हाल OMAP_USBTLL_REV2:
	हाल OMAP_USBTLL_REV3:
		nch = OMAP_REV2_TLL_CHANNEL_COUNT;
		अवरोध;
	शेष:
		nch = OMAP_TLL_CHANNEL_COUNT;
		dev_dbg(dev, "rev 0x%x not recognized, assuming %d channels\n",
			ver, nch);
		अवरोध;
	पूर्ण

	tll = devm_kzalloc(dev, माप(*tll) + माप(tll->ch_clk[nch]),
			   GFP_KERNEL);
	अगर (!tll) अणु
		pm_runसमय_put_sync(dev);
		pm_runसमय_disable(dev);
		वापस -ENOMEM;
	पूर्ण

	tll->base = base;
	tll->nch = nch;
	platक्रमm_set_drvdata(pdev, tll);

	क्रम (i = 0; i < nch; i++) अणु
		अक्षर clkname[] = "usb_tll_hs_usb_chx_clk";

		snम_लिखो(clkname, माप(clkname),
					"usb_tll_hs_usb_ch%d_clk", i);
		tll->ch_clk[i] = clk_get(dev, clkname);

		अगर (IS_ERR(tll->ch_clk[i]))
			dev_dbg(dev, "can't get clock : %s\n", clkname);
		अन्यथा
			clk_prepare(tll->ch_clk[i]);
	पूर्ण

	pm_runसमय_put_sync(dev);
	/* only after this can omap_tll_enable/disable work */
	spin_lock(&tll_lock);
	tll_dev = dev;
	spin_unlock(&tll_lock);

	वापस 0;
पूर्ण

/**
 * usbtll_omap_हटाओ - shutकरोwn processing क्रम UHH & TLL HCDs
 * @pdev: USB Host Controller being हटाओd
 *
 * Reverses the effect of usbtll_omap_probe().
 */
अटल पूर्णांक usbtll_omap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbtll_omap *tll = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	spin_lock(&tll_lock);
	tll_dev = शून्य;
	spin_unlock(&tll_lock);

	क्रम (i = 0; i < tll->nch; i++) अणु
		अगर (!IS_ERR(tll->ch_clk[i])) अणु
			clk_unprepare(tll->ch_clk[i]);
			clk_put(tll->ch_clk[i]);
		पूर्ण
	पूर्ण

	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id usbtll_omap_dt_ids[] = अणु
	अणु .compatible = "ti,usbhs-tll" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, usbtll_omap_dt_ids);

अटल काष्ठा platक्रमm_driver usbtll_omap_driver = अणु
	.driver = अणु
		.name		= usbtll_driver_name,
		.of_match_table = usbtll_omap_dt_ids,
	पूर्ण,
	.probe		= usbtll_omap_probe,
	.हटाओ		= usbtll_omap_हटाओ,
पूर्ण;

पूर्णांक omap_tll_init(काष्ठा usbhs_omap_platक्रमm_data *pdata)
अणु
	पूर्णांक i;
	bool needs_tll;
	अचिन्हित reg;
	काष्ठा usbtll_omap *tll;

	अगर (!tll_dev)
		वापस -ENODEV;

	pm_runसमय_get_sync(tll_dev);

	spin_lock(&tll_lock);
	tll = dev_get_drvdata(tll_dev);
	needs_tll = false;
	क्रम (i = 0; i < tll->nch; i++)
		needs_tll |= omap_usb_mode_needs_tll(pdata->port_mode[i]);

	अगर (needs_tll) अणु
		व्योम __iomem *base = tll->base;

		/* Program Common TLL रेजिस्टर */
		reg = usbtll_पढ़ो(base, OMAP_TLL_SHARED_CONF);
		reg |= (OMAP_TLL_SHARED_CONF_FCLK_IS_ON
			| OMAP_TLL_SHARED_CONF_USB_DIVRATION);
		reg &= ~OMAP_TLL_SHARED_CONF_USB_90D_DDR_EN;
		reg &= ~OMAP_TLL_SHARED_CONF_USB_180D_SDR_EN;

		usbtll_ग_लिखो(base, OMAP_TLL_SHARED_CONF, reg);

		/* Enable channels now */
		क्रम (i = 0; i < tll->nch; i++) अणु
			reg = usbtll_पढ़ो(base,	OMAP_TLL_CHANNEL_CONF(i));

			अगर (is_ohci_port(pdata->port_mode[i])) अणु
				reg |= ohci_omap3_fslsmode(pdata->port_mode[i])
				<< OMAP_TLL_CHANNEL_CONF_FSLSMODE_SHIFT;
				reg |= OMAP_TLL_CHANNEL_CONF_CHANMODE_FSLS;
			पूर्ण अन्यथा अगर (pdata->port_mode[i] ==
					OMAP_EHCI_PORT_MODE_TLL) अणु
				/*
				 * Disable UTMI AutoIdle, BitStuffing
				 * and use SDR Mode. Enable ULPI AutoIdle.
				 */
				reg &= ~(OMAP_TLL_CHANNEL_CONF_UTMIAUTOIDLE
					| OMAP_TLL_CHANNEL_CONF_ULPIDDRMODE);
				reg |= OMAP_TLL_CHANNEL_CONF_ULPINOBITSTUFF;
				reg |= OMAP_TLL_CHANNEL_CONF_ULPI_ULPIAUTOIDLE;
			पूर्ण अन्यथा अगर (pdata->port_mode[i] ==
					OMAP_EHCI_PORT_MODE_HSIC) अणु
				/*
				 * HSIC Mode requires UTMI port configurations
				 */
				reg |= OMAP_TLL_CHANNEL_CONF_DRVVBUS
				 | OMAP_TLL_CHANNEL_CONF_CHRGVBUS
				 | OMAP_TLL_CHANNEL_CONF_MODE_TRANSPARENT_UTMI
				 | OMAP_TLL_CHANNEL_CONF_ULPINOBITSTUFF;
			पूर्ण अन्यथा अणु
				जारी;
			पूर्ण
			reg |= OMAP_TLL_CHANNEL_CONF_CHANEN;
			usbtll_ग_लिखो(base, OMAP_TLL_CHANNEL_CONF(i), reg);

			usbtll_ग_लिखोb(base,
				      OMAP_TLL_ULPI_SCRATCH_REGISTER(i),
				      0xbe);
		पूर्ण
	पूर्ण

	spin_unlock(&tll_lock);
	pm_runसमय_put_sync(tll_dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_tll_init);

पूर्णांक omap_tll_enable(काष्ठा usbhs_omap_platक्रमm_data *pdata)
अणु
	पूर्णांक i;
	काष्ठा usbtll_omap *tll;

	अगर (!tll_dev)
		वापस -ENODEV;

	pm_runसमय_get_sync(tll_dev);

	spin_lock(&tll_lock);
	tll = dev_get_drvdata(tll_dev);

	क्रम (i = 0; i < tll->nch; i++) अणु
		अगर (omap_usb_mode_needs_tll(pdata->port_mode[i])) अणु
			पूर्णांक r;

			अगर (IS_ERR(tll->ch_clk[i]))
				जारी;

			r = clk_enable(tll->ch_clk[i]);
			अगर (r) अणु
				dev_err(tll_dev,
				 "Error enabling ch %d clock: %d\n", i, r);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock(&tll_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_tll_enable);

पूर्णांक omap_tll_disable(काष्ठा usbhs_omap_platक्रमm_data *pdata)
अणु
	पूर्णांक i;
	काष्ठा usbtll_omap *tll;

	अगर (!tll_dev)
		वापस -ENODEV;

	spin_lock(&tll_lock);
	tll = dev_get_drvdata(tll_dev);

	क्रम (i = 0; i < tll->nch; i++) अणु
		अगर (omap_usb_mode_needs_tll(pdata->port_mode[i])) अणु
			अगर (!IS_ERR(tll->ch_clk[i]))
				clk_disable(tll->ch_clk[i]);
		पूर्ण
	पूर्ण

	spin_unlock(&tll_lock);
	pm_runसमय_put_sync(tll_dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_tll_disable);

MODULE_AUTHOR("Keshava Munegowda <keshava_mgowda@ti.com>");
MODULE_AUTHOR("Roger Quadros <rogerq@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("usb tll driver for TI OMAP EHCI and OHCI controllers");

अटल पूर्णांक __init omap_usbtll_drvinit(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&usbtll_omap_driver);
पूर्ण

/*
 * init beक्रमe usbhs core driver;
 * The usbtll driver should be initialized beक्रमe
 * the usbhs core driver probe function is called.
 */
fs_initcall(omap_usbtll_drvinit);

अटल व्योम __निकास omap_usbtll_drvनिकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&usbtll_omap_driver);
पूर्ण
module_निकास(omap_usbtll_drvनिकास);
