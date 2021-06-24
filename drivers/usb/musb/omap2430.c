<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005-2007 by Texas Instruments
 * Some code has been taken from tusb6010.c
 * Copyrights क्रम that are attributable to:
 * Copyright (C) 2006 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 *
 * This file is part of the Inventra Controller Driver क्रम Linux.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/usb/musb.h>
#समावेश <linux/phy/omap_control_phy.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "musb_core.h"
#समावेश "omap2430.h"

काष्ठा omap2430_glue अणु
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*musb;
	क्रमागत musb_vbus_id_status status;
	काष्ठा work_काष्ठा	omap_musb_mailbox_work;
	काष्ठा device		*control_otghs;
पूर्ण;
#घोषणा glue_to_musb(g)		platक्रमm_get_drvdata(g->musb)

अटल काष्ठा omap2430_glue	*_glue;

अटल अंतरभूत व्योम omap2430_low_level_निकास(काष्ठा musb *musb)
अणु
	u32 l;

	/* in any role */
	l = musb_पढ़ोl(musb->mregs, OTG_FORCESTDBY);
	l |= ENABLEFORCE;	/* enable MSTANDBY */
	musb_ग_लिखोl(musb->mregs, OTG_FORCESTDBY, l);
पूर्ण

अटल अंतरभूत व्योम omap2430_low_level_init(काष्ठा musb *musb)
अणु
	u32 l;

	l = musb_पढ़ोl(musb->mregs, OTG_FORCESTDBY);
	l &= ~ENABLEFORCE;	/* disable MSTANDBY */
	musb_ग_लिखोl(musb->mregs, OTG_FORCESTDBY, l);
पूर्ण

अटल पूर्णांक omap2430_musb_mailbox(क्रमागत musb_vbus_id_status status)
अणु
	काष्ठा omap2430_glue	*glue = _glue;

	अगर (!glue) अणु
		pr_err("%s: musb core is not yet initialized\n", __func__);
		वापस -EPROBE_DEFER;
	पूर्ण
	glue->status = status;

	अगर (!glue_to_musb(glue)) अणु
		pr_err("%s: musb core is not yet ready\n", __func__);
		वापस -EPROBE_DEFER;
	पूर्ण

	schedule_work(&glue->omap_musb_mailbox_work);

	वापस 0;
पूर्ण

/*
 * HDRC controls CPEN, but beware current surges during device connect.
 * They can trigger transient overcurrent conditions that must be ignored.
 *
 * Note that we're skipping A_WAIT_VFALL -> A_IDLE and jumping right to B_IDLE
 * as set by musb_set_peripheral().
 */
अटल व्योम omap_musb_set_mailbox(काष्ठा omap2430_glue *glue)
अणु
	काष्ठा musb *musb = glue_to_musb(glue);
	पूर्णांक error;

	pm_runसमय_get_sync(musb->controller);

	dev_dbg(musb->controller, "VBUS %s, devctl %02x\n",
		usb_otg_state_string(musb->xceiv->otg->state),
		musb_पढ़ोb(musb->mregs, MUSB_DEVCTL));

	चयन (glue->status) अणु
	हाल MUSB_ID_GROUND:
		dev_dbg(musb->controller, "ID GND\n");
		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_IDLE:
			error = musb_set_host(musb);
			अगर (error)
				अवरोध;
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
			fallthrough;
		हाल OTG_STATE_A_WAIT_VRISE:
		हाल OTG_STATE_A_WAIT_BCON:
		हाल OTG_STATE_A_HOST:
			/*
			 * On multiple ID ground पूर्णांकerrupts just keep enabling
			 * VBUS. At least cpcap VBUS shuts करोwn otherwise.
			 */
			otg_set_vbus(musb->xceiv->otg, 1);
			अवरोध;
		शेष:
			musb->xceiv->otg->state = OTG_STATE_A_IDLE;
			musb->xceiv->last_event = USB_EVENT_ID;
			अगर (musb->gadget_driver) अणु
				omap_control_usb_set_mode(glue->control_otghs,
							  USB_MODE_HOST);
				otg_set_vbus(musb->xceiv->otg, 1);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल MUSB_VBUS_VALID:
		dev_dbg(musb->controller, "VBUS Connect\n");

		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		musb->xceiv->last_event = USB_EVENT_VBUS;
		omap_control_usb_set_mode(glue->control_otghs, USB_MODE_DEVICE);
		अवरोध;

	हाल MUSB_ID_FLOAT:
	हाल MUSB_VBUS_OFF:
		dev_dbg(musb->controller, "VBUS Disconnect\n");

		musb->xceiv->last_event = USB_EVENT_NONE;
		musb_set_peripheral(musb);
		otg_set_vbus(musb->xceiv->otg, 0);
		omap_control_usb_set_mode(glue->control_otghs,
			USB_MODE_DISCONNECT);
		अवरोध;
	शेष:
		dev_dbg(musb->controller, "ID float\n");
	पूर्ण
	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);
	atomic_notअगरier_call_chain(&musb->xceiv->notअगरier,
			musb->xceiv->last_event, शून्य);
पूर्ण


अटल व्योम omap_musb_mailbox_work(काष्ठा work_काष्ठा *mailbox_work)
अणु
	काष्ठा omap2430_glue *glue = container_of(mailbox_work,
				काष्ठा omap2430_glue, omap_musb_mailbox_work);

	omap_musb_set_mailbox(glue);
पूर्ण

अटल irqवापस_t omap2430_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *__hci)
अणु
	अचिन्हित दीर्घ   flags;
	irqवापस_t     retval = IRQ_NONE;
	काष्ठा musb     *musb = __hci;

	spin_lock_irqsave(&musb->lock, flags);

	musb->पूर्णांक_usb = musb_पढ़ोb(musb->mregs, MUSB_INTRUSB);
	musb->पूर्णांक_tx = musb_पढ़ोw(musb->mregs, MUSB_INTRTX);
	musb->पूर्णांक_rx = musb_पढ़ोw(musb->mregs, MUSB_INTRRX);

	अगर (musb->पूर्णांक_usb || musb->पूर्णांक_tx || musb->पूर्णांक_rx)
		retval = musb_पूर्णांकerrupt(musb);

	spin_unlock_irqrestore(&musb->lock, flags);

	वापस retval;
पूर्ण

अटल पूर्णांक omap2430_musb_init(काष्ठा musb *musb)
अणु
	u32 l;
	पूर्णांक status = 0;
	काष्ठा device *dev = musb->controller;
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा omap_musb_board_data *data = plat->board_data;

	/* We require some kind of बाह्यal transceiver, hooked
	 * up through ULPI.  TWL4030-family PMICs include one,
	 * which needs a driver, drivers aren't always needed.
	 */
	musb->phy = devm_phy_get(dev->parent, "usb2-phy");

	/* We can't totally हटाओ musb->xceiv as of now because
	 * musb core uses xceiv.state and xceiv.otg. Once we have
	 * a separate state machine to handle otg, these can be moved
	 * out of xceiv and then we can start using the generic PHY
	 * framework
	 */
	musb->xceiv = devm_usb_get_phy_by_phandle(dev->parent, "usb-phy", 0);

	अगर (IS_ERR(musb->xceiv)) अणु
		status = PTR_ERR(musb->xceiv);

		अगर (status == -ENXIO)
			वापस status;

		dev_dbg(dev, "HS USB OTG: no transceiver configured\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	अगर (IS_ERR(musb->phy)) अणु
		dev_err(dev, "HS USB OTG: no PHY configured\n");
		वापस PTR_ERR(musb->phy);
	पूर्ण
	musb->isr = omap2430_musb_पूर्णांकerrupt;
	phy_init(musb->phy);
	phy_घातer_on(musb->phy);

	l = musb_पढ़ोl(musb->mregs, OTG_INTERFSEL);

	अगर (data->पूर्णांकerface_type == MUSB_INTERFACE_UTMI) अणु
		/* OMAP4 uses Internal PHY GS70 which uses UTMI पूर्णांकerface */
		l &= ~ULPI_12PIN;       /* Disable ULPI */
		l |= UTMI_8BIT;         /* Enable UTMI  */
	पूर्ण अन्यथा अणु
		l |= ULPI_12PIN;
	पूर्ण

	musb_ग_लिखोl(musb->mregs, OTG_INTERFSEL, l);

	dev_dbg(dev, "HS USB OTG: revision 0x%x, sysconfig 0x%02x, "
			"sysstatus 0x%x, intrfsel 0x%x, simenable  0x%x\n",
			musb_पढ़ोl(musb->mregs, OTG_REVISION),
			musb_पढ़ोl(musb->mregs, OTG_SYSCONFIG),
			musb_पढ़ोl(musb->mregs, OTG_SYSSTATUS),
			musb_पढ़ोl(musb->mregs, OTG_INTERFSEL),
			musb_पढ़ोl(musb->mregs, OTG_SIMENABLE));

	वापस 0;
पूर्ण

अटल व्योम omap2430_musb_enable(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा omap2430_glue *glue = dev_get_drvdata(dev->parent);

	अगर (glue->status == MUSB_UNKNOWN)
		glue->status = MUSB_VBUS_OFF;
	omap_musb_set_mailbox(glue);
पूर्ण

अटल व्योम omap2430_musb_disable(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा omap2430_glue *glue = dev_get_drvdata(dev->parent);

	अगर (glue->status != MUSB_UNKNOWN)
		omap_control_usb_set_mode(glue->control_otghs,
			USB_MODE_DISCONNECT);
पूर्ण

अटल पूर्णांक omap2430_musb_निकास(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा omap2430_glue *glue = dev_get_drvdata(dev->parent);

	omap2430_low_level_निकास(musb);
	phy_घातer_off(musb->phy);
	phy_निकास(musb->phy);
	musb->phy = शून्य;
	cancel_work_sync(&glue->omap_musb_mailbox_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops omap2430_ops = अणु
	.quirks		= MUSB_DMA_INVENTRA,
#अगर_घोषित CONFIG_USB_INVENTRA_DMA
	.dma_init	= musbhs_dma_controller_create,
	.dma_निकास	= musbhs_dma_controller_destroy,
#पूर्ण_अगर
	.init		= omap2430_musb_init,
	.निकास		= omap2430_musb_निकास,

	.enable		= omap2430_musb_enable,
	.disable	= omap2430_musb_disable,

	.phy_callback	= omap2430_musb_mailbox,
पूर्ण;

अटल u64 omap2430_dmamask = DMA_BIT_MASK(32);

अटल पूर्णांक omap2430_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource			musb_resources[3];
	काष्ठा musb_hdrc_platक्रमm_data	*pdata = dev_get_platdata(&pdev->dev);
	काष्ठा omap_musb_board_data	*data;
	काष्ठा platक्रमm_device		*musb;
	काष्ठा omap2430_glue		*glue;
	काष्ठा device_node		*np = pdev->dev.of_node;
	काष्ठा musb_hdrc_config		*config;
	काष्ठा device_node		*control_node;
	काष्ठा platक्रमm_device		*control_pdev;
	पूर्णांक				ret = -ENOMEM, val;

	अगर (!np)
		वापस -ENODEV;

	glue = devm_kzalloc(&pdev->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		जाओ err0;

	musb = platक्रमm_device_alloc("musb-hdrc", PLATFORM_DEVID_AUTO);
	अगर (!musb) अणु
		dev_err(&pdev->dev, "failed to allocate musb device\n");
		जाओ err0;
	पूर्ण

	musb->dev.parent		= &pdev->dev;
	musb->dev.dma_mask		= &omap2430_dmamask;
	musb->dev.coherent_dma_mask	= omap2430_dmamask;

	glue->dev			= &pdev->dev;
	glue->musb			= musb;
	glue->status			= MUSB_UNKNOWN;
	glue->control_otghs = ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		जाओ err2;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ err2;

	config = devm_kzalloc(&pdev->dev, माप(*config), GFP_KERNEL);
	अगर (!config)
		जाओ err2;

	of_property_पढ़ो_u32(np, "mode", (u32 *)&pdata->mode);
	of_property_पढ़ो_u32(np, "interface-type",
			(u32 *)&data->पूर्णांकerface_type);
	of_property_पढ़ो_u32(np, "num-eps", (u32 *)&config->num_eps);
	of_property_पढ़ो_u32(np, "ram-bits", (u32 *)&config->ram_bits);
	of_property_पढ़ो_u32(np, "power", (u32 *)&pdata->घातer);

	ret = of_property_पढ़ो_u32(np, "multipoint", &val);
	अगर (!ret && val)
		config->multipoपूर्णांक = true;

	pdata->board_data	= data;
	pdata->config		= config;

	control_node = of_parse_phandle(np, "ctrl-module", 0);
	अगर (control_node) अणु
		control_pdev = of_find_device_by_node(control_node);
		अगर (!control_pdev) अणु
			dev_err(&pdev->dev, "Failed to get control device\n");
			ret = -EINVAL;
			जाओ err2;
		पूर्ण
		glue->control_otghs = &control_pdev->dev;
	पूर्ण

	pdata->platक्रमm_ops		= &omap2430_ops;

	platक्रमm_set_drvdata(pdev, glue);

	/*
	 * REVISIT अगर we ever have two instances of the wrapper, we will be
	 * in big trouble
	 */
	_glue	= glue;

	INIT_WORK(&glue->omap_musb_mailbox_work, omap_musb_mailbox_work);

	स_रखो(musb_resources, 0x00, माप(*musb_resources) *
			ARRAY_SIZE(musb_resources));

	musb_resources[0].name = pdev->resource[0].name;
	musb_resources[0].start = pdev->resource[0].start;
	musb_resources[0].end = pdev->resource[0].end;
	musb_resources[0].flags = pdev->resource[0].flags;

	musb_resources[1].name = pdev->resource[1].name;
	musb_resources[1].start = pdev->resource[1].start;
	musb_resources[1].end = pdev->resource[1].end;
	musb_resources[1].flags = pdev->resource[1].flags;

	musb_resources[2].name = pdev->resource[2].name;
	musb_resources[2].start = pdev->resource[2].start;
	musb_resources[2].end = pdev->resource[2].end;
	musb_resources[2].flags = pdev->resource[2].flags;

	ret = platक्रमm_device_add_resources(musb, musb_resources,
			ARRAY_SIZE(musb_resources));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add resources\n");
		जाओ err2;
	पूर्ण

	ret = platक्रमm_device_add_data(musb, pdata, माप(*pdata));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add platform_data\n");
		जाओ err2;
	पूर्ण

	pm_runसमय_enable(glue->dev);

	ret = platक्रमm_device_add(musb);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register musb device\n");
		जाओ err3;
	पूर्ण

	वापस 0;

err3:
	pm_runसमय_disable(glue->dev);

err2:
	platक्रमm_device_put(musb);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक omap2430_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap2430_glue *glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->musb);
	pm_runसमय_disable(glue->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक omap2430_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap2430_glue		*glue = dev_get_drvdata(dev);
	काष्ठा musb			*musb = glue_to_musb(glue);

	अगर (!musb)
		वापस 0;

	musb->context.otg_पूर्णांकerfsel = musb_पढ़ोl(musb->mregs,
						 OTG_INTERFSEL);

	omap2430_low_level_निकास(musb);

	phy_घातer_off(musb->phy);
	phy_निकास(musb->phy);

	वापस 0;
पूर्ण

अटल पूर्णांक omap2430_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा omap2430_glue		*glue = dev_get_drvdata(dev);
	काष्ठा musb			*musb = glue_to_musb(glue);

	अगर (!musb)
		वापस 0;

	phy_init(musb->phy);
	phy_घातer_on(musb->phy);

	omap2430_low_level_init(musb);
	musb_ग_लिखोl(musb->mregs, OTG_INTERFSEL,
		    musb->context.otg_पूर्णांकerfsel);

	/* Wait क्रम musb to get oriented. Otherwise we can get babble */
	usleep_range(200000, 250000);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap2430_pm_ops = अणु
	.runसमय_suspend = omap2430_runसमय_suspend,
	.runसमय_resume = omap2430_runसमय_resume,
पूर्ण;

#घोषणा DEV_PM_OPS	(&omap2430_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id omap2430_id_table[] = अणु
	अणु
		.compatible = "ti,omap4-musb"
	पूर्ण,
	अणु
		.compatible = "ti,omap3-musb"
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap2430_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver omap2430_driver = अणु
	.probe		= omap2430_probe,
	.हटाओ		= omap2430_हटाओ,
	.driver		= अणु
		.name	= "musb-omap2430",
		.pm	= DEV_PM_OPS,
		.of_match_table = of_match_ptr(omap2430_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap2430_driver);

MODULE_DESCRIPTION("OMAP2PLUS MUSB Glue Layer");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
