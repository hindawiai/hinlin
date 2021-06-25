<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * gpio-vbus.c - simple GPIO VBUS sensing driver क्रम B peripheral devices
 *
 * Copyright (c) 2008 Philipp Zabel <philipp.zabel@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/regulator/consumer.h>

#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>


/*
 * A simple GPIO VBUS sensing driver क्रम B peripheral only devices
 * with पूर्णांकernal transceivers. It can control a D+ pullup GPIO and
 * a regulator to limit the current drawn from VBUS.
 *
 * Needs to be loaded beक्रमe the UDC driver that will use it.
 */
काष्ठा gpio_vbus_data अणु
	काष्ठा gpio_desc	*vbus_gpiod;
	काष्ठा gpio_desc	*pullup_gpiod;
	काष्ठा usb_phy		phy;
	काष्ठा device          *dev;
	काष्ठा regulator       *vbus_draw;
	पूर्णांक			vbus_draw_enabled;
	अचिन्हित		mA;
	काष्ठा delayed_work	work;
	पूर्णांक			vbus;
	पूर्णांक			irq;
पूर्ण;


/*
 * This driver relies on "both edges" triggering.  VBUS has 100 msec to
 * stabilize, so the peripheral controller driver may need to cope with
 * some bouncing due to current surges (e.g. अक्षरging local capacitance)
 * and contact chatter.
 *
 * REVISIT in desperate straits, toggling between rising and falling
 * edges might be workable.
 */
#घोषणा VBUS_IRQ_FLAGS \
	(IRQF_SHARED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)


/* पूर्णांकerface to regulator framework */
अटल व्योम set_vbus_draw(काष्ठा gpio_vbus_data *gpio_vbus, अचिन्हित mA)
अणु
	काष्ठा regulator *vbus_draw = gpio_vbus->vbus_draw;
	पूर्णांक enabled;
	पूर्णांक ret;

	अगर (!vbus_draw)
		वापस;

	enabled = gpio_vbus->vbus_draw_enabled;
	अगर (mA) अणु
		regulator_set_current_limit(vbus_draw, 0, 1000 * mA);
		अगर (!enabled) अणु
			ret = regulator_enable(vbus_draw);
			अगर (ret < 0)
				वापस;
			gpio_vbus->vbus_draw_enabled = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (enabled) अणु
			ret = regulator_disable(vbus_draw);
			अगर (ret < 0)
				वापस;
			gpio_vbus->vbus_draw_enabled = 0;
		पूर्ण
	पूर्ण
	gpio_vbus->mA = mA;
पूर्ण

अटल पूर्णांक is_vbus_घातered(काष्ठा gpio_vbus_data *gpio_vbus)
अणु
	वापस gpiod_get_value(gpio_vbus->vbus_gpiod);
पूर्ण

अटल व्योम gpio_vbus_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus =
		container_of(work, काष्ठा gpio_vbus_data, work.work);
	पूर्णांक status, vbus;

	अगर (!gpio_vbus->phy.otg->gadget)
		वापस;

	vbus = is_vbus_घातered(gpio_vbus);
	अगर ((vbus ^ gpio_vbus->vbus) == 0)
		वापस;
	gpio_vbus->vbus = vbus;

	/* Peripheral controllers which manage the pullup themselves won't have
	 * a pullup GPIO configured here.  If it's configured here, we'll करो
	 * what isp1301_omap::b_peripheral() करोes and enable the pullup here...
	 * although that may complicate usb_gadget_अणु,disपूर्णconnect() support.
	 */

	अगर (vbus) अणु
		status = USB_EVENT_VBUS;
		gpio_vbus->phy.otg->state = OTG_STATE_B_PERIPHERAL;
		gpio_vbus->phy.last_event = status;
		usb_gadget_vbus_connect(gpio_vbus->phy.otg->gadget);

		/* drawing a "unit load" is *always* OK, except क्रम OTG */
		set_vbus_draw(gpio_vbus, 100);

		/* optionally enable D+ pullup */
		अगर (gpio_vbus->pullup_gpiod)
			gpiod_set_value(gpio_vbus->pullup_gpiod, 1);

		atomic_notअगरier_call_chain(&gpio_vbus->phy.notअगरier,
					   status, gpio_vbus->phy.otg->gadget);
		usb_phy_set_event(&gpio_vbus->phy, USB_EVENT_ENUMERATED);
	पूर्ण अन्यथा अणु
		/* optionally disable D+ pullup */
		अगर (gpio_vbus->pullup_gpiod)
			gpiod_set_value(gpio_vbus->pullup_gpiod, 0);

		set_vbus_draw(gpio_vbus, 0);

		usb_gadget_vbus_disconnect(gpio_vbus->phy.otg->gadget);
		status = USB_EVENT_NONE;
		gpio_vbus->phy.otg->state = OTG_STATE_B_IDLE;
		gpio_vbus->phy.last_event = status;

		atomic_notअगरier_call_chain(&gpio_vbus->phy.notअगरier,
					   status, gpio_vbus->phy.otg->gadget);
		usb_phy_set_event(&gpio_vbus->phy, USB_EVENT_NONE);
	पूर्ण
पूर्ण

/* VBUS change IRQ handler */
अटल irqवापस_t gpio_vbus_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = data;
	काष्ठा gpio_vbus_data *gpio_vbus = platक्रमm_get_drvdata(pdev);
	काष्ठा usb_otg *otg = gpio_vbus->phy.otg;

	dev_dbg(&pdev->dev, "VBUS %s (gadget: %s)\n",
		is_vbus_घातered(gpio_vbus) ? "supplied" : "inactive",
		otg->gadget ? otg->gadget->name : "none");

	अगर (otg->gadget)
		schedule_delayed_work(&gpio_vbus->work, msecs_to_jअगरfies(100));

	वापस IRQ_HANDLED;
पूर्ण

/* OTG transceiver पूर्णांकerface */

/* bind/unbind the peripheral controller */
अटल पूर्णांक gpio_vbus_set_peripheral(काष्ठा usb_otg *otg,
					काष्ठा usb_gadget *gadget)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus;
	काष्ठा platक्रमm_device *pdev;

	gpio_vbus = container_of(otg->usb_phy, काष्ठा gpio_vbus_data, phy);
	pdev = to_platक्रमm_device(gpio_vbus->dev);

	अगर (!gadget) अणु
		dev_dbg(&pdev->dev, "unregistering gadget '%s'\n",
			otg->gadget->name);

		/* optionally disable D+ pullup */
		अगर (gpio_vbus->pullup_gpiod)
			gpiod_set_value(gpio_vbus->pullup_gpiod, 0);

		set_vbus_draw(gpio_vbus, 0);

		usb_gadget_vbus_disconnect(otg->gadget);
		otg->state = OTG_STATE_UNDEFINED;

		otg->gadget = शून्य;
		वापस 0;
	पूर्ण

	otg->gadget = gadget;
	dev_dbg(&pdev->dev, "registered gadget '%s'\n", gadget->name);

	/* initialize connection state */
	gpio_vbus->vbus = 0; /* start with disconnected */
	gpio_vbus_irq(gpio_vbus->irq, pdev);
	वापस 0;
पूर्ण

/* effective क्रम B devices, ignored क्रम A-peripheral */
अटल पूर्णांक gpio_vbus_set_घातer(काष्ठा usb_phy *phy, अचिन्हित mA)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus;

	gpio_vbus = container_of(phy, काष्ठा gpio_vbus_data, phy);

	अगर (phy->otg->state == OTG_STATE_B_PERIPHERAL)
		set_vbus_draw(gpio_vbus, mA);
	वापस 0;
पूर्ण

/* क्रम non-OTG B devices: set/clear transceiver suspend mode */
अटल पूर्णांक gpio_vbus_set_suspend(काष्ठा usb_phy *phy, पूर्णांक suspend)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus;

	gpio_vbus = container_of(phy, काष्ठा gpio_vbus_data, phy);

	/* draw max 0 mA from vbus in suspend mode; or the previously
	 * recorded amount of current अगर not suspended
	 *
	 * NOTE: high घातered configs (mA > 100) may draw up to 2.5 mA
	 * अगर they're wake-enabled ... we don't handle that yet.
	 */
	वापस gpio_vbus_set_घातer(phy, suspend ? 0 : gpio_vbus->mA);
पूर्ण

/* platक्रमm driver पूर्णांकerface */

अटल पूर्णांक gpio_vbus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err, irq;
	अचिन्हित दीर्घ irqflags;

	gpio_vbus = devm_kzalloc(&pdev->dev, माप(काष्ठा gpio_vbus_data),
				 GFP_KERNEL);
	अगर (!gpio_vbus)
		वापस -ENOMEM;

	gpio_vbus->phy.otg = devm_kzalloc(&pdev->dev, माप(काष्ठा usb_otg),
					  GFP_KERNEL);
	अगर (!gpio_vbus->phy.otg)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, gpio_vbus);
	gpio_vbus->dev = &pdev->dev;
	gpio_vbus->phy.label = "gpio-vbus";
	gpio_vbus->phy.dev = gpio_vbus->dev;
	gpio_vbus->phy.set_घातer = gpio_vbus_set_घातer;
	gpio_vbus->phy.set_suspend = gpio_vbus_set_suspend;

	gpio_vbus->phy.otg->state = OTG_STATE_UNDEFINED;
	gpio_vbus->phy.otg->usb_phy = &gpio_vbus->phy;
	gpio_vbus->phy.otg->set_peripheral = gpio_vbus_set_peripheral;

	/* Look up the VBUS sensing GPIO */
	gpio_vbus->vbus_gpiod = devm_gpiod_get(dev, "vbus", GPIOD_IN);
	अगर (IS_ERR(gpio_vbus->vbus_gpiod)) अणु
		err = PTR_ERR(gpio_vbus->vbus_gpiod);
		dev_err(&pdev->dev, "can't request vbus gpio, err: %d\n", err);
		वापस err;
	पूर्ण
	gpiod_set_consumer_name(gpio_vbus->vbus_gpiod, "vbus_detect");

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res) अणु
		irq = res->start;
		irqflags = (res->flags & IRQF_TRIGGER_MASK) | IRQF_SHARED;
	पूर्ण अन्यथा अणु
		irq = gpiod_to_irq(gpio_vbus->vbus_gpiod);
		irqflags = VBUS_IRQ_FLAGS;
	पूर्ण

	gpio_vbus->irq = irq;

	/*
	 * The VBUS sensing GPIO should have a pullकरोwn, which will normally be
	 * part of a resistor ladder turning a 4.0V-5.25V level on VBUS पूर्णांकo a
	 * value the GPIO detects as active. Some प्रणालीs will use comparators.
	 * Get the optional D+ or D- pullup GPIO. If the data line pullup is
	 * in use, initialize it to "not pulling up"
	 */
	gpio_vbus->pullup_gpiod = devm_gpiod_get_optional(dev, "pullup",
							  GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio_vbus->pullup_gpiod)) अणु
		err = PTR_ERR(gpio_vbus->pullup_gpiod);
		dev_err(&pdev->dev, "can't request pullup gpio, err: %d\n",
			err);
		वापस err;
	पूर्ण
	अगर (gpio_vbus->pullup_gpiod)
		gpiod_set_consumer_name(gpio_vbus->pullup_gpiod, "udc_pullup");

	err = devm_request_irq(&pdev->dev, irq, gpio_vbus_irq, irqflags,
			       "vbus_detect", pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "can't request irq %i, err: %d\n",
			irq, err);
		वापस err;
	पूर्ण

	INIT_DELAYED_WORK(&gpio_vbus->work, gpio_vbus_work);

	gpio_vbus->vbus_draw = devm_regulator_get(&pdev->dev, "vbus_draw");
	अगर (IS_ERR(gpio_vbus->vbus_draw)) अणु
		dev_dbg(&pdev->dev, "can't get vbus_draw regulator, err: %ld\n",
			PTR_ERR(gpio_vbus->vbus_draw));
		gpio_vbus->vbus_draw = शून्य;
	पूर्ण

	/* only active when a gadget is रेजिस्टरed */
	err = usb_add_phy(&gpio_vbus->phy, USB_PHY_TYPE_USB2);
	अगर (err) अणु
		dev_err(&pdev->dev, "can't register transceiver, err: %d\n",
			err);
		वापस err;
	पूर्ण

	/* TODO: wakeup could be enabled here with device_init_wakeup(dev, 1) */

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_vbus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus = platक्रमm_get_drvdata(pdev);

	device_init_wakeup(&pdev->dev, 0);
	cancel_delayed_work_sync(&gpio_vbus->work);

	usb_हटाओ_phy(&gpio_vbus->phy);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gpio_vbus_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(gpio_vbus->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_vbus_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_vbus_data *gpio_vbus = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(gpio_vbus->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gpio_vbus_dev_pm_ops = अणु
	.suspend	= gpio_vbus_pm_suspend,
	.resume		= gpio_vbus_pm_resume,
पूर्ण;
#पूर्ण_अगर

MODULE_ALIAS("platform:gpio-vbus");

अटल काष्ठा platक्रमm_driver gpio_vbus_driver = अणु
	.driver = अणु
		.name  = "gpio-vbus",
#अगर_घोषित CONFIG_PM
		.pm = &gpio_vbus_dev_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe		= gpio_vbus_probe,
	.हटाओ		= gpio_vbus_हटाओ,
पूर्ण;

module_platक्रमm_driver(gpio_vbus_driver);

MODULE_DESCRIPTION("simple GPIO controlled OTG transceiver driver");
MODULE_AUTHOR("Philipp Zabel");
MODULE_LICENSE("GPL");
