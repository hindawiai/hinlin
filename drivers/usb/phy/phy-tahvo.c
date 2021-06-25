<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tahvo USB transceiver driver
 *
 * Copyright (C) 2005-2006 Nokia Corporation
 *
 * Parts copied from isp1301_omap.c.
 * Copyright (C) 2004 Texas Instruments
 * Copyright (C) 2004 David Brownell
 *
 * Original driver written by Juha Yrjथघlथअ, Tony Lindgren and Timo Terथअs.
 * Modअगरied क्रम Retu/Tahvo MFD by Aaro Koskinen.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/usb.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/mfd/retu.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRIVER_NAME     "tahvo-usb"

#घोषणा TAHVO_REG_IDSR	0x02
#घोषणा TAHVO_REG_USBR	0x06

#घोषणा USBR_SLAVE_CONTROL	(1 << 8)
#घोषणा USBR_VPPVIO_SW		(1 << 7)
#घोषणा USBR_SPEED		(1 << 6)
#घोषणा USBR_REGOUT		(1 << 5)
#घोषणा USBR_MASTER_SW2		(1 << 4)
#घोषणा USBR_MASTER_SW1		(1 << 3)
#घोषणा USBR_SLAVE_SW		(1 << 2)
#घोषणा USBR_NSUSPEND		(1 << 1)
#घोषणा USBR_SEMODE		(1 << 0)

#घोषणा TAHVO_MODE_HOST		0
#घोषणा TAHVO_MODE_PERIPHERAL	1

काष्ठा tahvo_usb अणु
	काष्ठा platक्रमm_device	*pt_dev;
	काष्ठा usb_phy		phy;
	पूर्णांक			vbus_state;
	काष्ठा mutex		serialize;
	काष्ठा clk		*ick;
	पूर्णांक			irq;
	पूर्णांक			tahvo_mode;
	काष्ठा extcon_dev	*extcon;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tahvo_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,

	EXTCON_NONE,
पूर्ण;

अटल sमाप_प्रकार vbus_show(काष्ठा device *device,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tahvo_usb *tu = dev_get_drvdata(device);
	वापस प्र_लिखो(buf, "%s\n", tu->vbus_state ? "on" : "off");
पूर्ण
अटल DEVICE_ATTR_RO(vbus);

अटल व्योम check_vbus_state(काष्ठा tahvo_usb *tu)
अणु
	काष्ठा retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);
	पूर्णांक reg, prev_state;

	reg = retu_पढ़ो(rdev, TAHVO_REG_IDSR);
	अगर (reg & TAHVO_STAT_VBUS) अणु
		चयन (tu->phy.otg->state) अणु
		हाल OTG_STATE_B_IDLE:
			/* Enable the gadget driver */
			अगर (tu->phy.otg->gadget)
				usb_gadget_vbus_connect(tu->phy.otg->gadget);
			tu->phy.otg->state = OTG_STATE_B_PERIPHERAL;
			usb_phy_set_event(&tu->phy, USB_EVENT_ENUMERATED);
			अवरोध;
		हाल OTG_STATE_A_IDLE:
			/*
			 * Session is now valid assuming the USB hub is driving
			 * Vbus.
			 */
			tu->phy.otg->state = OTG_STATE_A_HOST;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		dev_info(&tu->pt_dev->dev, "USB cable connected\n");
	पूर्ण अन्यथा अणु
		चयन (tu->phy.otg->state) अणु
		हाल OTG_STATE_B_PERIPHERAL:
			अगर (tu->phy.otg->gadget)
				usb_gadget_vbus_disconnect(tu->phy.otg->gadget);
			tu->phy.otg->state = OTG_STATE_B_IDLE;
			usb_phy_set_event(&tu->phy, USB_EVENT_NONE);
			अवरोध;
		हाल OTG_STATE_A_HOST:
			tu->phy.otg->state = OTG_STATE_A_IDLE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		dev_info(&tu->pt_dev->dev, "USB cable disconnected\n");
	पूर्ण

	prev_state = tu->vbus_state;
	tu->vbus_state = reg & TAHVO_STAT_VBUS;
	अगर (prev_state != tu->vbus_state) अणु
		extcon_set_state_sync(tu->extcon, EXTCON_USB, tu->vbus_state);
		sysfs_notअगरy(&tu->pt_dev->dev.kobj, शून्य, "vbus_state");
	पूर्ण
पूर्ण

अटल व्योम tahvo_usb_become_host(काष्ठा tahvo_usb *tu)
अणु
	काष्ठा retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);

	extcon_set_state_sync(tu->extcon, EXTCON_USB_HOST, true);

	/* Power up the transceiver in USB host mode */
	retu_ग_लिखो(rdev, TAHVO_REG_USBR, USBR_REGOUT | USBR_NSUSPEND |
		   USBR_MASTER_SW2 | USBR_MASTER_SW1);
	tu->phy.otg->state = OTG_STATE_A_IDLE;

	check_vbus_state(tu);
पूर्ण

अटल व्योम tahvo_usb_stop_host(काष्ठा tahvo_usb *tu)
अणु
	tu->phy.otg->state = OTG_STATE_A_IDLE;
पूर्ण

अटल व्योम tahvo_usb_become_peripheral(काष्ठा tahvo_usb *tu)
अणु
	काष्ठा retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);

	extcon_set_state_sync(tu->extcon, EXTCON_USB_HOST, false);

	/* Power up transceiver and set it in USB peripheral mode */
	retu_ग_लिखो(rdev, TAHVO_REG_USBR, USBR_SLAVE_CONTROL | USBR_REGOUT |
		   USBR_NSUSPEND | USBR_SLAVE_SW);
	tu->phy.otg->state = OTG_STATE_B_IDLE;

	check_vbus_state(tu);
पूर्ण

अटल व्योम tahvo_usb_stop_peripheral(काष्ठा tahvo_usb *tu)
अणु
	अगर (tu->phy.otg->gadget)
		usb_gadget_vbus_disconnect(tu->phy.otg->gadget);
	tu->phy.otg->state = OTG_STATE_B_IDLE;
पूर्ण

अटल व्योम tahvo_usb_घातer_off(काष्ठा tahvo_usb *tu)
अणु
	काष्ठा retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);

	/* Disable gadget controller अगर any */
	अगर (tu->phy.otg->gadget)
		usb_gadget_vbus_disconnect(tu->phy.otg->gadget);

	/* Power off transceiver */
	retu_ग_लिखो(rdev, TAHVO_REG_USBR, 0);
	tu->phy.otg->state = OTG_STATE_UNDEFINED;
पूर्ण

अटल पूर्णांक tahvo_usb_set_suspend(काष्ठा usb_phy *dev, पूर्णांक suspend)
अणु
	काष्ठा tahvo_usb *tu = container_of(dev, काष्ठा tahvo_usb, phy);
	काष्ठा retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);
	u16 w;

	dev_dbg(&tu->pt_dev->dev, "%s\n", __func__);

	w = retu_पढ़ो(rdev, TAHVO_REG_USBR);
	अगर (suspend)
		w &= ~USBR_NSUSPEND;
	अन्यथा
		w |= USBR_NSUSPEND;
	retu_ग_लिखो(rdev, TAHVO_REG_USBR, w);

	वापस 0;
पूर्ण

अटल पूर्णांक tahvo_usb_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	काष्ठा tahvo_usb *tu = container_of(otg->usb_phy, काष्ठा tahvo_usb,
					    phy);

	dev_dbg(&tu->pt_dev->dev, "%s %p\n", __func__, host);

	mutex_lock(&tu->serialize);

	अगर (host == शून्य) अणु
		अगर (tu->tahvo_mode == TAHVO_MODE_HOST)
			tahvo_usb_घातer_off(tu);
		otg->host = शून्य;
		mutex_unlock(&tu->serialize);
		वापस 0;
	पूर्ण

	अगर (tu->tahvo_mode == TAHVO_MODE_HOST) अणु
		otg->host = शून्य;
		tahvo_usb_become_host(tu);
	पूर्ण

	otg->host = host;

	mutex_unlock(&tu->serialize);

	वापस 0;
पूर्ण

अटल पूर्णांक tahvo_usb_set_peripheral(काष्ठा usb_otg *otg,
				    काष्ठा usb_gadget *gadget)
अणु
	काष्ठा tahvo_usb *tu = container_of(otg->usb_phy, काष्ठा tahvo_usb,
					    phy);

	dev_dbg(&tu->pt_dev->dev, "%s %p\n", __func__, gadget);

	mutex_lock(&tu->serialize);

	अगर (!gadget) अणु
		अगर (tu->tahvo_mode == TAHVO_MODE_PERIPHERAL)
			tahvo_usb_घातer_off(tu);
		tu->phy.otg->gadget = शून्य;
		mutex_unlock(&tu->serialize);
		वापस 0;
	पूर्ण

	tu->phy.otg->gadget = gadget;
	अगर (tu->tahvo_mode == TAHVO_MODE_PERIPHERAL)
		tahvo_usb_become_peripheral(tu);

	mutex_unlock(&tu->serialize);

	वापस 0;
पूर्ण

अटल irqवापस_t tahvo_usb_vbus_पूर्णांकerrupt(पूर्णांक irq, व्योम *_tu)
अणु
	काष्ठा tahvo_usb *tu = _tu;

	mutex_lock(&tu->serialize);
	check_vbus_state(tu);
	mutex_unlock(&tu->serialize);

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार otg_mode_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tahvo_usb *tu = dev_get_drvdata(device);

	चयन (tu->tahvo_mode) अणु
	हाल TAHVO_MODE_HOST:
		वापस प्र_लिखो(buf, "host\n");
	हाल TAHVO_MODE_PERIPHERAL:
		वापस प्र_लिखो(buf, "peripheral\n");
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार otg_mode_store(काष्ठा device *device,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tahvo_usb *tu = dev_get_drvdata(device);
	पूर्णांक r;

	mutex_lock(&tu->serialize);
	अगर (count >= 4 && म_भेदन(buf, "host", 4) == 0) अणु
		अगर (tu->tahvo_mode == TAHVO_MODE_PERIPHERAL)
			tahvo_usb_stop_peripheral(tu);
		tu->tahvo_mode = TAHVO_MODE_HOST;
		अगर (tu->phy.otg->host) अणु
			dev_info(device, "HOST mode: host controller present\n");
			tahvo_usb_become_host(tu);
		पूर्ण अन्यथा अणु
			dev_info(device, "HOST mode: no host controller, powering off\n");
			tahvo_usb_घातer_off(tu);
		पूर्ण
		r = म_माप(buf);
	पूर्ण अन्यथा अगर (count >= 10 && म_भेदन(buf, "peripheral", 10) == 0) अणु
		अगर (tu->tahvo_mode == TAHVO_MODE_HOST)
			tahvo_usb_stop_host(tu);
		tu->tahvo_mode = TAHVO_MODE_PERIPHERAL;
		अगर (tu->phy.otg->gadget) अणु
			dev_info(device, "PERIPHERAL mode: gadget driver present\n");
			tahvo_usb_become_peripheral(tu);
		पूर्ण अन्यथा अणु
			dev_info(device, "PERIPHERAL mode: no gadget driver, powering off\n");
			tahvo_usb_घातer_off(tu);
		पूर्ण
		r = म_माप(buf);
	पूर्ण अन्यथा अणु
		r = -EINVAL;
	पूर्ण
	mutex_unlock(&tu->serialize);

	वापस r;
पूर्ण
अटल DEVICE_ATTR_RW(otg_mode);

अटल काष्ठा attribute *tahvo_attrs[] = अणु
	&dev_attr_vbus.attr,
	&dev_attr_otg_mode.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(tahvo);

अटल पूर्णांक tahvo_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा retu_dev *rdev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tahvo_usb *tu;
	पूर्णांक ret;

	tu = devm_kzalloc(&pdev->dev, माप(*tu), GFP_KERNEL);
	अगर (!tu)
		वापस -ENOMEM;

	tu->phy.otg = devm_kzalloc(&pdev->dev, माप(*tu->phy.otg),
				   GFP_KERNEL);
	अगर (!tu->phy.otg)
		वापस -ENOMEM;

	tu->pt_dev = pdev;

	/* Default mode */
#अगर_घोषित CONFIG_TAHVO_USB_HOST_BY_DEFAULT
	tu->tahvo_mode = TAHVO_MODE_HOST;
#अन्यथा
	tu->tahvo_mode = TAHVO_MODE_PERIPHERAL;
#पूर्ण_अगर

	mutex_init(&tu->serialize);

	tu->ick = devm_clk_get(&pdev->dev, "usb_l4_ick");
	अगर (!IS_ERR(tu->ick))
		clk_enable(tu->ick);

	/*
	 * Set initial state, so that we generate kevents only on state changes.
	 */
	tu->vbus_state = retu_पढ़ो(rdev, TAHVO_REG_IDSR) & TAHVO_STAT_VBUS;

	tu->extcon = devm_extcon_dev_allocate(&pdev->dev, tahvo_cable);
	अगर (IS_ERR(tu->extcon)) अणु
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		ret = PTR_ERR(tu->extcon);
		जाओ err_disable_clk;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(&pdev->dev, tu->extcon);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register extcon device: %d\n",
			ret);
		जाओ err_disable_clk;
	पूर्ण

	/* Set the initial cable state. */
	extcon_set_state_sync(tu->extcon, EXTCON_USB_HOST,
			       tu->tahvo_mode == TAHVO_MODE_HOST);
	extcon_set_state_sync(tu->extcon, EXTCON_USB, tu->vbus_state);

	/* Create OTG पूर्णांकerface */
	tahvo_usb_घातer_off(tu);
	tu->phy.dev = &pdev->dev;
	tu->phy.otg->state = OTG_STATE_UNDEFINED;
	tu->phy.label = DRIVER_NAME;
	tu->phy.set_suspend = tahvo_usb_set_suspend;

	tu->phy.otg->usb_phy = &tu->phy;
	tu->phy.otg->set_host = tahvo_usb_set_host;
	tu->phy.otg->set_peripheral = tahvo_usb_set_peripheral;

	ret = usb_add_phy(&tu->phy, USB_PHY_TYPE_USB2);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot register USB transceiver: %d\n",
			ret);
		जाओ err_disable_clk;
	पूर्ण

	dev_set_drvdata(&pdev->dev, tu);

	tu->irq = platक्रमm_get_irq(pdev, 0);
	ret = request_thपढ़ोed_irq(tu->irq, शून्य, tahvo_usb_vbus_पूर्णांकerrupt,
				   IRQF_ONESHOT,
				   "tahvo-vbus", tu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register tahvo-vbus irq: %d\n",
			ret);
		जाओ err_हटाओ_phy;
	पूर्ण

	वापस 0;

err_हटाओ_phy:
	usb_हटाओ_phy(&tu->phy);
err_disable_clk:
	अगर (!IS_ERR(tu->ick))
		clk_disable(tu->ick);

	वापस ret;
पूर्ण

अटल पूर्णांक tahvo_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tahvo_usb *tu = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(tu->irq, tu);
	usb_हटाओ_phy(&tu->phy);
	अगर (!IS_ERR(tu->ick))
		clk_disable(tu->ick);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tahvo_usb_driver = अणु
	.probe		= tahvo_usb_probe,
	.हटाओ		= tahvo_usb_हटाओ,
	.driver		= अणु
		.name	= "tahvo-usb",
		.dev_groups = tahvo_groups,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tahvo_usb_driver);

MODULE_DESCRIPTION("Tahvo USB transceiver driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Juha Yrjथघlथअ, Tony Lindgren, and Timo Terथअs");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
