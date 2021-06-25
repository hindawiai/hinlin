<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/pxa3xx-ulpi.c
 *
 * code specअगरic to pxa3xx aka Monahans
 *
 * Copyright (C) 2010 CompuLab Ltd.
 *
 * 2010-13-07: Igor Grinberg <grinberg@compulab.co.il>
 *             initial version: pxa310 USB Host mode support
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/otg.h>

#समावेश <mach/hardware.h>
#समावेश "regs-u2d.h"
#समावेश <linux/platक्रमm_data/usb-pxa3xx-ulpi.h>

काष्ठा pxa3xx_u2d_ulpi अणु
	काष्ठा clk		*clk;
	व्योम __iomem		*mmio_base;

	काष्ठा usb_phy		*otg;
	अचिन्हित पूर्णांक		ulpi_mode;
पूर्ण;

अटल काष्ठा pxa3xx_u2d_ulpi *u2d;

अटल अंतरभूत u32 u2d_पढ़ोl(u32 reg)
अणु
	वापस __raw_पढ़ोl(u2d->mmio_base + reg);
पूर्ण

अटल अंतरभूत व्योम u2d_ग_लिखोl(u32 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, u2d->mmio_base + reg);
पूर्ण

#अगर defined(CONFIG_PXA310_ULPI)
क्रमागत u2d_ulpi_phy_mode अणु
	SYNCH		= 0,
	CARKIT		= (1 << 0),
	SER_3PIN	= (1 << 1),
	SER_6PIN	= (1 << 2),
	LOWPOWER	= (1 << 3),
पूर्ण;

अटल अंतरभूत क्रमागत u2d_ulpi_phy_mode pxa310_ulpi_get_phymode(व्योम)
अणु
	वापस (u2d_पढ़ोl(U2DOTGUSR) >> 28) & 0xF;
पूर्ण

अटल पूर्णांक pxa310_ulpi_poll(व्योम)
अणु
	पूर्णांक समयout = 50000;

	जबतक (समयout--) अणु
		अगर (!(u2d_पढ़ोl(U2DOTGUCR) & U2DOTGUCR_RUN))
			वापस 0;

		cpu_relax();
	पूर्ण

	pr_warn("%s: ULPI access timed out!\n", __func__);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक pxa310_ulpi_पढ़ो(काष्ठा usb_phy *otg, u32 reg)
अणु
	पूर्णांक err;

	अगर (pxa310_ulpi_get_phymode() != SYNCH) अणु
		pr_warn("%s: PHY is not in SYNCH mode!\n", __func__);
		वापस -EBUSY;
	पूर्ण

	u2d_ग_लिखोl(U2DOTGUCR, U2DOTGUCR_RUN | U2DOTGUCR_RNW | (reg << 16));
	msleep(5);

	err = pxa310_ulpi_poll();
	अगर (err)
		वापस err;

	वापस u2d_पढ़ोl(U2DOTGUCR) & U2DOTGUCR_RDATA;
पूर्ण

अटल पूर्णांक pxa310_ulpi_ग_लिखो(काष्ठा usb_phy *otg, u32 val, u32 reg)
अणु
	अगर (pxa310_ulpi_get_phymode() != SYNCH) अणु
		pr_warn("%s: PHY is not in SYNCH mode!\n", __func__);
		वापस -EBUSY;
	पूर्ण

	u2d_ग_लिखोl(U2DOTGUCR, U2DOTGUCR_RUN | (reg << 16) | (val << 8));
	msleep(5);

	वापस pxa310_ulpi_poll();
पूर्ण

काष्ठा usb_phy_io_ops pxa310_ulpi_access_ops = अणु
	.पढ़ो	= pxa310_ulpi_पढ़ो,
	.ग_लिखो	= pxa310_ulpi_ग_लिखो,
पूर्ण;

अटल व्योम pxa310_otg_transceiver_rtsm(व्योम)
अणु
	u32 u2करोtgcr;

	/* put PHY to sync mode */
	u2करोtgcr = u2d_पढ़ोl(U2DOTGCR);
	u2करोtgcr |=  U2DOTGCR_RTSM | U2DOTGCR_UTMID;
	u2d_ग_लिखोl(U2DOTGCR, u2करोtgcr);
	msleep(10);

	/* setup OTG sync mode */
	u2करोtgcr = u2d_पढ़ोl(U2DOTGCR);
	u2करोtgcr |= U2DOTGCR_ULAF;
	u2करोtgcr &= ~(U2DOTGCR_SMAF | U2DOTGCR_CKAF);
	u2d_ग_लिखोl(U2DOTGCR, u2करोtgcr);
पूर्ण

अटल पूर्णांक pxa310_start_otg_host_transcvr(काष्ठा usb_bus *host)
अणु
	पूर्णांक err;

	pxa310_otg_transceiver_rtsm();

	err = usb_phy_init(u2d->otg);
	अगर (err) अणु
		pr_err("OTG transceiver init failed");
		वापस err;
	पूर्ण

	err = otg_set_vbus(u2d->otg->otg, 1);
	अगर (err) अणु
		pr_err("OTG transceiver VBUS set failed");
		वापस err;
	पूर्ण

	err = otg_set_host(u2d->otg->otg, host);
	अगर (err)
		pr_err("OTG transceiver Host mode set failed");

	वापस err;
पूर्ण

अटल पूर्णांक pxa310_start_otg_hc(काष्ठा usb_bus *host)
अणु
	u32 u2करोtgcr;
	पूर्णांक err;

	/* disable USB device controller */
	u2d_ग_लिखोl(U2DCR, u2d_पढ़ोl(U2DCR) & ~U2DCR_UDE);
	u2d_ग_लिखोl(U2DOTGCR, u2d_पढ़ोl(U2DOTGCR) | U2DOTGCR_UTMID);
	u2d_ग_लिखोl(U2DOTGICR, u2d_पढ़ोl(U2DOTGICR) & ~0x37F7F);

	err = pxa310_start_otg_host_transcvr(host);
	अगर (err)
		वापस err;

	/* set xceiver mode */
	अगर (u2d->ulpi_mode & ULPI_IC_6PIN_SERIAL)
		u2d_ग_लिखोl(U2DP3CR, u2d_पढ़ोl(U2DP3CR) & ~U2DP3CR_P2SS);
	अन्यथा अगर (u2d->ulpi_mode & ULPI_IC_3PIN_SERIAL)
		u2d_ग_लिखोl(U2DP3CR, u2d_पढ़ोl(U2DP3CR) | U2DP3CR_P2SS);

	/* start OTG host controller */
	u2करोtgcr = u2d_पढ़ोl(U2DOTGCR) | U2DOTGCR_SMAF;
	u2d_ग_लिखोl(U2DOTGCR, u2करोtgcr & ~(U2DOTGCR_ULAF | U2DOTGCR_CKAF));

	वापस 0;
पूर्ण

अटल व्योम pxa310_stop_otg_hc(व्योम)
अणु
	pxa310_otg_transceiver_rtsm();

	otg_set_host(u2d->otg->otg, शून्य);
	otg_set_vbus(u2d->otg->otg, 0);
	usb_phy_shutकरोwn(u2d->otg);
पूर्ण

अटल व्योम pxa310_u2d_setup_otg_hc(व्योम)
अणु
	u32 u2करोtgcr;

	u2करोtgcr = u2d_पढ़ोl(U2DOTGCR);
	u2करोtgcr |= U2DOTGCR_ULAF | U2DOTGCR_UTMID;
	u2करोtgcr &= ~(U2DOTGCR_SMAF | U2DOTGCR_CKAF);
	u2d_ग_लिखोl(U2DOTGCR, u2करोtgcr);
	msleep(5);
	u2d_ग_लिखोl(U2DOTGCR, u2करोtgcr | U2DOTGCR_ULE);
	msleep(5);
	u2d_ग_लिखोl(U2DOTGICR, u2d_पढ़ोl(U2DOTGICR) & ~0x37F7F);
पूर्ण

अटल पूर्णांक pxa310_otg_init(काष्ठा pxa3xx_u2d_platक्रमm_data *pdata)
अणु
	अचिन्हित पूर्णांक ulpi_mode = ULPI_OTG_DRVVBUS;

	अगर (pdata) अणु
		अगर (pdata->ulpi_mode & ULPI_SER_6PIN)
			ulpi_mode |= ULPI_IC_6PIN_SERIAL;
		अन्यथा अगर (pdata->ulpi_mode & ULPI_SER_3PIN)
			ulpi_mode |= ULPI_IC_3PIN_SERIAL;
	पूर्ण

	u2d->ulpi_mode = ulpi_mode;

	u2d->otg = otg_ulpi_create(&pxa310_ulpi_access_ops, ulpi_mode);
	अगर (!u2d->otg)
		वापस -ENOMEM;

	u2d->otg->io_priv = u2d->mmio_base;

	वापस 0;
पूर्ण

अटल व्योम pxa310_otg_निकास(व्योम)
अणु
	kमुक्त(u2d->otg);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxa310_u2d_setup_otg_hc(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक pxa310_start_otg_hc(काष्ठा usb_bus *host)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम pxa310_stop_otg_hc(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक pxa310_otg_init(काष्ठा pxa3xx_u2d_platक्रमm_data *pdata)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम pxa310_otg_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PXA310_ULPI */

पूर्णांक pxa3xx_u2d_start_hc(काष्ठा usb_bus *host)
अणु
	पूर्णांक err = 0;

	/* In हाल the PXA3xx ULPI isn't used, करो nothing. */
	अगर (!u2d)
		वापस 0;

	clk_prepare_enable(u2d->clk);

	अगर (cpu_is_pxa310()) अणु
		pxa310_u2d_setup_otg_hc();
		err = pxa310_start_otg_hc(host);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(pxa3xx_u2d_start_hc);

व्योम pxa3xx_u2d_stop_hc(काष्ठा usb_bus *host)
अणु
	/* In हाल the PXA3xx ULPI isn't used, करो nothing. */
	अगर (!u2d)
		वापस;

	अगर (cpu_is_pxa310())
		pxa310_stop_otg_hc();

	clk_disable_unprepare(u2d->clk);
पूर्ण
EXPORT_SYMBOL_GPL(pxa3xx_u2d_stop_hc);

अटल पूर्णांक pxa3xx_u2d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa3xx_u2d_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा resource *r;
	पूर्णांक err;

	u2d = kzalloc(माप(*u2d), GFP_KERNEL);
	अगर (!u2d)
		वापस -ENOMEM;

	u2d->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(u2d->clk)) अणु
		dev_err(&pdev->dev, "failed to get u2d clock\n");
		err = PTR_ERR(u2d->clk);
		जाओ err_मुक्त_mem;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "no IO memory resource defined\n");
		err = -ENODEV;
		जाओ err_put_clk;
	पूर्ण

        r = request_mem_region(r->start, resource_size(r), pdev->name);
        अगर (!r) अणु
                dev_err(&pdev->dev, "failed to request memory resource\n");
                err = -EBUSY;
                जाओ err_put_clk;
        पूर्ण

	u2d->mmio_base = ioremap(r->start, resource_size(r));
	अगर (!u2d->mmio_base) अणु
		dev_err(&pdev->dev, "ioremap() failed\n");
		err = -ENODEV;
		जाओ err_मुक्त_res;
	पूर्ण

	अगर (pdata->init) अणु
		err = pdata->init(&pdev->dev);
		अगर (err)
			जाओ err_मुक्त_io;
	पूर्ण

	/* Only PXA310 U2D has OTG functionality */
	अगर (cpu_is_pxa310()) अणु
		err = pxa310_otg_init(pdata);
		अगर (err)
			जाओ err_मुक्त_plat;
	पूर्ण

	platक्रमm_set_drvdata(pdev, u2d);

	वापस 0;

err_मुक्त_plat:
	अगर (pdata->निकास)
		pdata->निकास(&pdev->dev);
err_मुक्त_io:
	iounmap(u2d->mmio_base);
err_मुक्त_res:
	release_mem_region(r->start, resource_size(r));
err_put_clk:
	clk_put(u2d->clk);
err_मुक्त_mem:
	kमुक्त(u2d);
	वापस err;
पूर्ण

अटल पूर्णांक pxa3xx_u2d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa3xx_u2d_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा resource *r;

	अगर (cpu_is_pxa310()) अणु
		pxa310_stop_otg_hc();
		pxa310_otg_निकास();
	पूर्ण

	अगर (pdata->निकास)
		pdata->निकास(&pdev->dev);

	platक्रमm_set_drvdata(pdev, शून्य);
	iounmap(u2d->mmio_base);
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(r->start, resource_size(r));

	clk_put(u2d->clk);

	kमुक्त(u2d);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxa3xx_u2d_ulpi_driver = अणु
        .driver		= अणु
                .name   = "pxa3xx-u2d",
        पूर्ण,
        .probe          = pxa3xx_u2d_probe,
        .हटाओ         = pxa3xx_u2d_हटाओ,
पूर्ण;
module_platक्रमm_driver(pxa3xx_u2d_ulpi_driver);

MODULE_DESCRIPTION("PXA3xx U2D ULPI driver");
MODULE_AUTHOR("Igor Grinberg");
MODULE_LICENSE("GPL v2");
