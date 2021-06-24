<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2010 ST-Ericsson AB
 * Mian Yousaf Kaukab <mian.yousaf.kaukab@stericsson.com>
 *
 * Based on omap2430.c
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/musb-ux500.h>

#समावेश "musb_core.h"

अटल स्थिर काष्ठा musb_hdrc_config ux500_musb_hdrc_config = अणु
	.multipoपूर्णांक	= true,
	.dyn_fअगरo	= true,
	.num_eps	= 16,
	.ram_bits	= 16,
पूर्ण;

काष्ठा ux500_glue अणु
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*musb;
	काष्ठा clk		*clk;
पूर्ण;
#घोषणा glue_to_musb(g)	platक्रमm_get_drvdata(g->musb)

अटल व्योम ux500_musb_set_vbus(काष्ठा musb *musb, पूर्णांक is_on)
अणु
	u8            devctl;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	/* HDRC controls CPEN, but beware current surges during device
	 * connect.  They can trigger transient overcurrent conditions
	 * that must be ignored.
	 */

	devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);

	अगर (is_on) अणु
		अगर (musb->xceiv->otg->state == OTG_STATE_A_IDLE) अणु
			/* start the session */
			devctl |= MUSB_DEVCTL_SESSION;
			musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);
			/*
			 * Wait क्रम the musb to set as A device to enable the
			 * VBUS
			 */
			जबतक (musb_पढ़ोb(musb->mregs, MUSB_DEVCTL) & 0x80) अणु

				अगर (समय_after(jअगरfies, समयout)) अणु
					dev_err(musb->controller,
					"configured as A device timeout");
					अवरोध;
				पूर्ण
			पूर्ण

		पूर्ण अन्यथा अणु
			musb->is_active = 1;
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
			devctl |= MUSB_DEVCTL_SESSION;
			MUSB_HST_MODE(musb);
		पूर्ण
	पूर्ण अन्यथा अणु
		musb->is_active = 0;

		/* NOTE: we're skipping A_WAIT_VFALL -> A_IDLE and jumping
		 * right to B_IDLE...
		 */
		devctl &= ~MUSB_DEVCTL_SESSION;
		MUSB_DEV_MODE(musb);
	पूर्ण
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);

	/*
	 * Devctl values will be updated after vbus goes below
	 * session_valid. The समय taken depends on the capacitance
	 * on VBUS line. The max disअक्षरge समय can be upto 1 sec
	 * as per the spec. Typically on our platक्रमm, it is 200ms
	 */
	अगर (!is_on)
		mdelay(200);

	dev_dbg(musb->controller, "VBUS %s, devctl %02x\n",
		usb_otg_state_string(musb->xceiv->otg->state),
		musb_पढ़ोb(musb->mregs, MUSB_DEVCTL));
पूर्ण

अटल पूर्णांक musb_otg_notअगरications(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *unused)
अणु
	काष्ठा musb *musb = container_of(nb, काष्ठा musb, nb);

	dev_dbg(musb->controller, "musb_otg_notifications %ld %s\n",
			event, usb_otg_state_string(musb->xceiv->otg->state));

	चयन (event) अणु
	हाल UX500_MUSB_ID:
		dev_dbg(musb->controller, "ID GND\n");
		ux500_musb_set_vbus(musb, 1);
		अवरोध;
	हाल UX500_MUSB_VBUS:
		dev_dbg(musb->controller, "VBUS Connect\n");
		अवरोध;
	हाल UX500_MUSB_NONE:
		dev_dbg(musb->controller, "VBUS Disconnect\n");
		अगर (is_host_active(musb))
			ux500_musb_set_vbus(musb, 0);
		अन्यथा
			musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		अवरोध;
	शेष:
		dev_dbg(musb->controller, "ID float\n");
		वापस NOTIFY_DONE;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल irqवापस_t ux500_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *__hci)
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

अटल पूर्णांक ux500_musb_init(काष्ठा musb *musb)
अणु
	पूर्णांक status;

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	अगर (IS_ERR_OR_शून्य(musb->xceiv)) अणु
		pr_err("HS USB OTG: no transceiver configured\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	musb->nb.notअगरier_call = musb_otg_notअगरications;
	status = usb_रेजिस्टर_notअगरier(musb->xceiv, &musb->nb);
	अगर (status < 0) अणु
		dev_dbg(musb->controller, "notification register failed\n");
		वापस status;
	पूर्ण

	musb->isr = ux500_musb_पूर्णांकerrupt;

	वापस 0;
पूर्ण

अटल पूर्णांक ux500_musb_निकास(काष्ठा musb *musb)
अणु
	usb_unरेजिस्टर_notअगरier(musb->xceiv, &musb->nb);

	usb_put_phy(musb->xceiv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops ux500_ops = अणु
	.quirks		= MUSB_DMA_UX500 | MUSB_INDEXED_EP,
#अगर_घोषित CONFIG_USB_UX500_DMA
	.dma_init	= ux500_dma_controller_create,
	.dma_निकास	= ux500_dma_controller_destroy,
#पूर्ण_अगर
	.init		= ux500_musb_init,
	.निकास		= ux500_musb_निकास,
	.fअगरo_mode	= 5,

	.set_vbus	= ux500_musb_set_vbus,
पूर्ण;

अटल काष्ठा musb_hdrc_platक्रमm_data *
ux500_of_probe(काष्ठा platक्रमm_device *pdev, काष्ठा device_node *np)
अणु
	काष्ठा musb_hdrc_platक्रमm_data *pdata;
	स्थिर अक्षर *mode;
	पूर्णांक म_माप;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	mode = of_get_property(np, "dr_mode", &म_माप);
	अगर (!mode) अणु
		dev_err(&pdev->dev, "No 'dr_mode' property found\n");
		वापस शून्य;
	पूर्ण

	अगर (म_माप > 0) अणु
		अगर (!म_भेद(mode, "host"))
			pdata->mode = MUSB_HOST;
		अगर (!म_भेद(mode, "otg"))
			pdata->mode = MUSB_OTG;
		अगर (!म_भेद(mode, "peripheral"))
			pdata->mode = MUSB_PERIPHERAL;
	पूर्ण

	वापस pdata;
पूर्ण

अटल पूर्णांक ux500_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource musb_resources[2];
	काष्ठा musb_hdrc_platक्रमm_data	*pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node		*np = pdev->dev.of_node;
	काष्ठा platक्रमm_device		*musb;
	काष्ठा ux500_glue		*glue;
	काष्ठा clk			*clk;
	पूर्णांक				ret = -ENOMEM;

	अगर (!pdata) अणु
		अगर (np) अणु
			pdata = ux500_of_probe(pdev, np);
			अगर (!pdata)
				जाओ err0;

			pdev->dev.platक्रमm_data = pdata;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "no pdata or device tree found\n");
			जाओ err0;
		पूर्ण
	पूर्ण

	glue = devm_kzalloc(&pdev->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		जाओ err0;

	musb = platक्रमm_device_alloc("musb-hdrc", PLATFORM_DEVID_AUTO);
	अगर (!musb) अणु
		dev_err(&pdev->dev, "failed to allocate musb device\n");
		जाओ err0;
	पूर्ण

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		ret = PTR_ERR(clk);
		जाओ err1;
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		जाओ err1;
	पूर्ण

	musb->dev.parent		= &pdev->dev;
	musb->dev.dma_mask		= &pdev->dev.coherent_dma_mask;
	musb->dev.coherent_dma_mask	= pdev->dev.coherent_dma_mask;

	glue->dev			= &pdev->dev;
	glue->musb			= musb;
	glue->clk			= clk;

	pdata->platक्रमm_ops		= &ux500_ops;
	pdata->config 			= &ux500_musb_hdrc_config;

	platक्रमm_set_drvdata(pdev, glue);

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

	ret = platक्रमm_device_add(musb);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register musb device\n");
		जाओ err2;
	पूर्ण

	वापस 0;

err2:
	clk_disable_unprepare(clk);

err1:
	platक्रमm_device_put(musb);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक ux500_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ux500_glue	*glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->musb);
	clk_disable_unprepare(glue->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ux500_suspend(काष्ठा device *dev)
अणु
	काष्ठा ux500_glue	*glue = dev_get_drvdata(dev);
	काष्ठा musb		*musb = glue_to_musb(glue);

	अगर (musb)
		usb_phy_set_suspend(musb->xceiv, 1);

	clk_disable_unprepare(glue->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक ux500_resume(काष्ठा device *dev)
अणु
	काष्ठा ux500_glue	*glue = dev_get_drvdata(dev);
	काष्ठा musb		*musb = glue_to_musb(glue);
	पूर्णांक			ret;

	ret = clk_prepare_enable(glue->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	अगर (musb)
		usb_phy_set_suspend(musb->xceiv, 0);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ux500_pm_ops, ux500_suspend, ux500_resume);

अटल स्थिर काष्ठा of_device_id ux500_match[] = अणु
        अणु .compatible = "stericsson,db8500-musb", पूर्ण,
        अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ux500_match);

अटल काष्ठा platक्रमm_driver ux500_driver = अणु
	.probe		= ux500_probe,
	.हटाओ		= ux500_हटाओ,
	.driver		= अणु
		.name	= "musb-ux500",
		.pm	= &ux500_pm_ops,
		.of_match_table = ux500_match,
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("UX500 MUSB Glue Layer");
MODULE_AUTHOR("Mian Yousaf Kaukab <mian.yousaf.kaukab@stericsson.com>");
MODULE_LICENSE("GPL v2");
module_platक्रमm_driver(ux500_driver);
