<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NOP USB transceiver क्रम all USB transceiver which are either built-in
 * पूर्णांकo USB IP or which are mostly स्वतःnomous.
 *
 * Copyright (C) 2009 Texas Instruments Inc
 * Author: Ajay Kumar Gupta <ajay.gupta@ti.com>
 *
 * Current status:
 *	This provides a "nop" transceiver क्रम PHYs which are
 *	स्वतःnomous such as isp1504, isp1707, etc.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/usb_phy_generic.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>

#समावेश "phy-generic.h"

#घोषणा VBUS_IRQ_FLAGS \
	(IRQF_SHARED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | \
		IRQF_ONESHOT)

काष्ठा platक्रमm_device *usb_phy_generic_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर_simple("usb_phy_generic",
			PLATFORM_DEVID_AUTO, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_generic_रेजिस्टर);

व्योम usb_phy_generic_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_generic_unरेजिस्टर);

अटल पूर्णांक nop_set_suspend(काष्ठा usb_phy *x, पूर्णांक suspend)
अणु
	काष्ठा usb_phy_generic *nop = dev_get_drvdata(x->dev);

	अगर (!IS_ERR(nop->clk)) अणु
		अगर (suspend)
			clk_disable_unprepare(nop->clk);
		अन्यथा
			clk_prepare_enable(nop->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nop_reset(काष्ठा usb_phy_generic *nop)
अणु
	अगर (!nop->gpiod_reset)
		वापस;

	gpiod_set_value_cansleep(nop->gpiod_reset, 1);
	usleep_range(10000, 20000);
	gpiod_set_value_cansleep(nop->gpiod_reset, 0);
पूर्ण

/* पूर्णांकerface to regulator framework */
अटल व्योम nop_set_vbus_draw(काष्ठा usb_phy_generic *nop, अचिन्हित mA)
अणु
	काष्ठा regulator *vbus_draw = nop->vbus_draw;
	पूर्णांक enabled;
	पूर्णांक ret;

	अगर (!vbus_draw)
		वापस;

	enabled = nop->vbus_draw_enabled;
	अगर (mA) अणु
		regulator_set_current_limit(vbus_draw, 0, 1000 * mA);
		अगर (!enabled) अणु
			ret = regulator_enable(vbus_draw);
			अगर (ret < 0)
				वापस;
			nop->vbus_draw_enabled = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (enabled) अणु
			ret = regulator_disable(vbus_draw);
			अगर (ret < 0)
				वापस;
			nop->vbus_draw_enabled = 0;
		पूर्ण
	पूर्ण
	nop->mA = mA;
पूर्ण


अटल irqवापस_t nop_gpio_vbus_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा usb_phy_generic *nop = data;
	काष्ठा usb_otg *otg = nop->phy.otg;
	पूर्णांक vbus, status;

	vbus = gpiod_get_value(nop->gpiod_vbus);
	अगर ((vbus ^ nop->vbus) == 0)
		वापस IRQ_HANDLED;
	nop->vbus = vbus;

	अगर (vbus) अणु
		status = USB_EVENT_VBUS;
		otg->state = OTG_STATE_B_PERIPHERAL;
		nop->phy.last_event = status;

		/* drawing a "unit load" is *always* OK, except क्रम OTG */
		nop_set_vbus_draw(nop, 100);

		atomic_notअगरier_call_chain(&nop->phy.notअगरier, status,
					   otg->gadget);
	पूर्ण अन्यथा अणु
		nop_set_vbus_draw(nop, 0);

		status = USB_EVENT_NONE;
		otg->state = OTG_STATE_B_IDLE;
		nop->phy.last_event = status;

		atomic_notअगरier_call_chain(&nop->phy.notअगरier, status,
					   otg->gadget);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक usb_gen_phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा usb_phy_generic *nop = dev_get_drvdata(phy->dev);
	पूर्णांक ret;

	अगर (!IS_ERR(nop->vcc)) अणु
		अगर (regulator_enable(nop->vcc))
			dev_err(phy->dev, "Failed to enable power\n");
	पूर्ण

	अगर (!IS_ERR(nop->clk)) अणु
		ret = clk_prepare_enable(nop->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	nop_reset(nop);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gen_phy_init);

व्योम usb_gen_phy_shutकरोwn(काष्ठा usb_phy *phy)
अणु
	काष्ठा usb_phy_generic *nop = dev_get_drvdata(phy->dev);

	gpiod_set_value_cansleep(nop->gpiod_reset, 1);

	अगर (!IS_ERR(nop->clk))
		clk_disable_unprepare(nop->clk);

	अगर (!IS_ERR(nop->vcc)) अणु
		अगर (regulator_disable(nop->vcc))
			dev_err(phy->dev, "Failed to disable power\n");
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_gen_phy_shutकरोwn);

अटल पूर्णांक nop_set_peripheral(काष्ठा usb_otg *otg, काष्ठा usb_gadget *gadget)
अणु
	अगर (!otg)
		वापस -ENODEV;

	अगर (!gadget) अणु
		otg->gadget = शून्य;
		वापस -ENODEV;
	पूर्ण

	otg->gadget = gadget;
	अगर (otg->state == OTG_STATE_B_PERIPHERAL)
		atomic_notअगरier_call_chain(&otg->usb_phy->notअगरier,
					   USB_EVENT_VBUS, otg->gadget);
	अन्यथा
		otg->state = OTG_STATE_B_IDLE;
	वापस 0;
पूर्ण

अटल पूर्णांक nop_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	अगर (!otg)
		वापस -ENODEV;

	अगर (!host) अणु
		otg->host = शून्य;
		वापस -ENODEV;
	पूर्ण

	otg->host = host;
	वापस 0;
पूर्ण

पूर्णांक usb_phy_gen_create_phy(काष्ठा device *dev, काष्ठा usb_phy_generic *nop)
अणु
	क्रमागत usb_phy_type type = USB_PHY_TYPE_USB2;
	पूर्णांक err = 0;

	u32 clk_rate = 0;
	bool needs_vcc = false, needs_clk = false;

	अगर (dev->of_node) अणु
		काष्ठा device_node *node = dev->of_node;

		अगर (of_property_पढ़ो_u32(node, "clock-frequency", &clk_rate))
			clk_rate = 0;

		needs_vcc = of_property_पढ़ो_bool(node, "vcc-supply");
		needs_clk = of_property_पढ़ो_bool(node, "clocks");
	पूर्ण
	nop->gpiod_reset = devm_gpiod_get_optional(dev, "reset",
						   GPIOD_ASIS);
	err = PTR_ERR_OR_ZERO(nop->gpiod_reset);
	अगर (!err) अणु
		nop->gpiod_vbus = devm_gpiod_get_optional(dev,
						 "vbus-detect",
						 GPIOD_ASIS);
		err = PTR_ERR_OR_ZERO(nop->gpiod_vbus);
	पूर्ण

	अगर (err == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (err) अणु
		dev_err(dev, "Error requesting RESET or VBUS GPIO\n");
		वापस err;
	पूर्ण
	अगर (nop->gpiod_reset)
		gpiod_direction_output(nop->gpiod_reset, 1);

	nop->phy.otg = devm_kzalloc(dev, माप(*nop->phy.otg),
			GFP_KERNEL);
	अगर (!nop->phy.otg)
		वापस -ENOMEM;

	nop->clk = devm_clk_get(dev, "main_clk");
	अगर (IS_ERR(nop->clk)) अणु
		dev_dbg(dev, "Can't get phy clock: %ld\n",
					PTR_ERR(nop->clk));
		अगर (needs_clk)
			वापस PTR_ERR(nop->clk);
	पूर्ण

	अगर (!IS_ERR(nop->clk) && clk_rate) अणु
		err = clk_set_rate(nop->clk, clk_rate);
		अगर (err) अणु
			dev_err(dev, "Error setting clock rate\n");
			वापस err;
		पूर्ण
	पूर्ण

	nop->vcc = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(nop->vcc)) अणु
		dev_dbg(dev, "Error getting vcc regulator: %ld\n",
					PTR_ERR(nop->vcc));
		अगर (needs_vcc)
			वापस -EPROBE_DEFER;
	पूर्ण

	nop->dev		= dev;
	nop->phy.dev		= nop->dev;
	nop->phy.label		= "nop-xceiv";
	nop->phy.set_suspend	= nop_set_suspend;
	nop->phy.type		= type;

	nop->phy.otg->state		= OTG_STATE_UNDEFINED;
	nop->phy.otg->usb_phy		= &nop->phy;
	nop->phy.otg->set_host		= nop_set_host;
	nop->phy.otg->set_peripheral	= nop_set_peripheral;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_gen_create_phy);

अटल पूर्णांक usb_phy_generic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb_phy_generic	*nop;
	पूर्णांक err;

	nop = devm_kzalloc(dev, माप(*nop), GFP_KERNEL);
	अगर (!nop)
		वापस -ENOMEM;

	err = usb_phy_gen_create_phy(dev, nop);
	अगर (err)
		वापस err;
	अगर (nop->gpiod_vbus) अणु
		err = devm_request_thपढ़ोed_irq(&pdev->dev,
						gpiod_to_irq(nop->gpiod_vbus),
						शून्य, nop_gpio_vbus_thपढ़ो,
						VBUS_IRQ_FLAGS, "vbus_detect",
						nop);
		अगर (err) अणु
			dev_err(&pdev->dev, "can't request irq %i, err: %d\n",
				gpiod_to_irq(nop->gpiod_vbus), err);
			वापस err;
		पूर्ण
		nop->phy.otg->state = gpiod_get_value(nop->gpiod_vbus) ?
			OTG_STATE_B_PERIPHERAL : OTG_STATE_B_IDLE;
	पूर्ण

	nop->phy.init		= usb_gen_phy_init;
	nop->phy.shutकरोwn	= usb_gen_phy_shutकरोwn;

	err = usb_add_phy_dev(&nop->phy);
	अगर (err) अणु
		dev_err(&pdev->dev, "can't register transceiver, err: %d\n",
			err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, nop);

	वापस 0;
पूर्ण

अटल पूर्णांक usb_phy_generic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_phy_generic *nop = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&nop->phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nop_xceiv_dt_ids[] = अणु
	अणु .compatible = "usb-nop-xceiv" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, nop_xceiv_dt_ids);

अटल काष्ठा platक्रमm_driver usb_phy_generic_driver = अणु
	.probe		= usb_phy_generic_probe,
	.हटाओ		= usb_phy_generic_हटाओ,
	.driver		= अणु
		.name	= "usb_phy_generic",
		.of_match_table = nop_xceiv_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init usb_phy_generic_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&usb_phy_generic_driver);
पूर्ण
subsys_initcall(usb_phy_generic_init);

अटल व्योम __निकास usb_phy_generic_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&usb_phy_generic_driver);
पूर्ण
module_निकास(usb_phy_generic_निकास);

MODULE_ALIAS("platform:usb_phy_generic");
MODULE_AUTHOR("Texas Instruments Inc");
MODULE_DESCRIPTION("NOP USB Transceiver driver");
MODULE_LICENSE("GPL");
