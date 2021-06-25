<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * twl6030_usb - TWL6030 USB transceiver, talking to OMAP OTG driver.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: Hema HK <hemahk@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb/musb.h>
#समावेश <linux/usb/phy_companion.h>
#समावेश <linux/phy/omap_usb.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>

/* usb रेजिस्टर definitions */
#घोषणा USB_VENDOR_ID_LSB		0x00
#घोषणा USB_VENDOR_ID_MSB		0x01
#घोषणा USB_PRODUCT_ID_LSB		0x02
#घोषणा USB_PRODUCT_ID_MSB		0x03
#घोषणा USB_VBUS_CTRL_SET		0x04
#घोषणा USB_VBUS_CTRL_CLR		0x05
#घोषणा USB_ID_CTRL_SET			0x06
#घोषणा USB_ID_CTRL_CLR			0x07
#घोषणा USB_VBUS_INT_SRC		0x08
#घोषणा USB_VBUS_INT_LATCH_SET		0x09
#घोषणा USB_VBUS_INT_LATCH_CLR		0x0A
#घोषणा USB_VBUS_INT_EN_LO_SET		0x0B
#घोषणा USB_VBUS_INT_EN_LO_CLR		0x0C
#घोषणा USB_VBUS_INT_EN_HI_SET		0x0D
#घोषणा USB_VBUS_INT_EN_HI_CLR		0x0E
#घोषणा USB_ID_INT_SRC			0x0F
#घोषणा USB_ID_INT_LATCH_SET		0x10
#घोषणा USB_ID_INT_LATCH_CLR		0x11

#घोषणा USB_ID_INT_EN_LO_SET		0x12
#घोषणा USB_ID_INT_EN_LO_CLR		0x13
#घोषणा USB_ID_INT_EN_HI_SET		0x14
#घोषणा USB_ID_INT_EN_HI_CLR		0x15
#घोषणा USB_OTG_ADP_CTRL		0x16
#घोषणा USB_OTG_ADP_HIGH		0x17
#घोषणा USB_OTG_ADP_LOW			0x18
#घोषणा USB_OTG_ADP_RISE		0x19
#घोषणा USB_OTG_REVISION		0x1A

/* to be moved to LDO */
#घोषणा TWL6030_MISC2			0xE5
#घोषणा TWL6030_CFG_LDO_PD2		0xF5
#घोषणा TWL6030_BACKUP_REG		0xFA

#घोषणा STS_HW_CONDITIONS		0x21

/* In module TWL6030_MODULE_PM_MASTER */
#घोषणा STS_HW_CONDITIONS		0x21
#घोषणा STS_USB_ID			BIT(2)

/* In module TWL6030_MODULE_PM_RECEIVER */
#घोषणा VUSB_CFG_TRANS			0x71
#घोषणा VUSB_CFG_STATE			0x72
#घोषणा VUSB_CFG_VOLTAGE		0x73

/* in module TWL6030_MODULE_MAIN_CHARGE */

#घोषणा CHARGERUSB_CTRL1		0x8

#घोषणा CONTROLLER_STAT1		0x03
#घोषणा	VBUS_DET			BIT(2)

काष्ठा twl6030_usb अणु
	काष्ठा phy_companion	comparator;
	काष्ठा device		*dev;

	/* क्रम vbus reporting with irqs disabled */
	spinlock_t		lock;

	काष्ठा regulator		*usb3v3;

	/* used to check initial cable status after probe */
	काष्ठा delayed_work	get_status_work;

	/* used to set vbus, in atomic path */
	काष्ठा work_काष्ठा	set_vbus_work;

	पूर्णांक			irq1;
	पूर्णांक			irq2;
	क्रमागत musb_vbus_id_status linkstat;
	u8			asleep;
	bool			vbus_enable;
पूर्ण;

#घोषणा	comparator_to_twl(x) container_of((x), काष्ठा twl6030_usb, comparator)

/*-------------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक twl6030_ग_लिखोb(काष्ठा twl6030_usb *twl, u8 module,
						u8 data, u8 address)
अणु
	पूर्णांक ret = 0;

	ret = twl_i2c_ग_लिखो_u8(module, data, address);
	अगर (ret < 0)
		dev_err(twl->dev,
			"Write[0x%x] Error %d\n", address, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत u8 twl6030_पढ़ोb(काष्ठा twl6030_usb *twl, u8 module, u8 address)
अणु
	u8 data;
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो_u8(module, &data, address);
	अगर (ret >= 0)
		ret = data;
	अन्यथा
		dev_err(twl->dev,
			"readb[0x%x,0x%x] Error %d\n",
					module, address, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक twl6030_start_srp(काष्ठा phy_companion *comparator)
अणु
	काष्ठा twl6030_usb *twl = comparator_to_twl(comparator);

	twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x24, USB_VBUS_CTRL_SET);
	twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x84, USB_VBUS_CTRL_SET);

	mdelay(100);
	twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0xa0, USB_VBUS_CTRL_CLR);

	वापस 0;
पूर्ण

अटल पूर्णांक twl6030_usb_lकरो_init(काष्ठा twl6030_usb *twl)
अणु
	/* Set to OTG_REV 1.3 and turn on the ID_WAKEUP_COMP */
	twl6030_ग_लिखोb(twl, TWL6030_MODULE_ID0, 0x1, TWL6030_BACKUP_REG);

	/* Program CFG_LDO_PD2 रेजिस्टर and set VUSB bit */
	twl6030_ग_लिखोb(twl, TWL6030_MODULE_ID0, 0x1, TWL6030_CFG_LDO_PD2);

	/* Program MISC2 रेजिस्टर and set bit VUSB_IN_VBAT */
	twl6030_ग_लिखोb(twl, TWL6030_MODULE_ID0, 0x10, TWL6030_MISC2);

	twl->usb3v3 = regulator_get(twl->dev, "usb");
	अगर (IS_ERR(twl->usb3v3))
		वापस -ENODEV;

	/* Program the USB_VBUS_CTRL_SET and set VBUS_ACT_COMP bit */
	twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x4, USB_VBUS_CTRL_SET);

	/*
	 * Program the USB_ID_CTRL_SET रेजिस्टर to enable GND drive
	 * and the ID comparators
	 */
	twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x14, USB_ID_CTRL_SET);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार vbus_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा twl6030_usb *twl = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&twl->lock, flags);

	चयन (twl->linkstat) अणु
	हाल MUSB_VBUS_VALID:
	       ret = snम_लिखो(buf, PAGE_SIZE, "vbus\n");
	       अवरोध;
	हाल MUSB_ID_GROUND:
	       ret = snम_लिखो(buf, PAGE_SIZE, "id\n");
	       अवरोध;
	हाल MUSB_VBUS_OFF:
	       ret = snम_लिखो(buf, PAGE_SIZE, "none\n");
	       अवरोध;
	शेष:
	       ret = snम_लिखो(buf, PAGE_SIZE, "UNKNOWN\n");
	पूर्ण
	spin_unlock_irqrestore(&twl->lock, flags);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(vbus);

अटल काष्ठा attribute *twl6030_attrs[] = अणु
	&dev_attr_vbus.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(twl6030);

अटल irqवापस_t twl6030_usb_irq(पूर्णांक irq, व्योम *_twl)
अणु
	काष्ठा twl6030_usb *twl = _twl;
	क्रमागत musb_vbus_id_status status = MUSB_UNKNOWN;
	u8 vbus_state, hw_state;
	पूर्णांक ret;

	hw_state = twl6030_पढ़ोb(twl, TWL6030_MODULE_ID0, STS_HW_CONDITIONS);

	vbus_state = twl6030_पढ़ोb(twl, TWL_MODULE_MAIN_CHARGE,
						CONTROLLER_STAT1);
	अगर (!(hw_state & STS_USB_ID)) अणु
		अगर (vbus_state & VBUS_DET) अणु
			ret = regulator_enable(twl->usb3v3);
			अगर (ret)
				dev_err(twl->dev, "Failed to enable usb3v3\n");

			twl->asleep = 1;
			status = MUSB_VBUS_VALID;
			twl->linkstat = status;
			ret = musb_mailbox(status);
			अगर (ret)
				twl->linkstat = MUSB_UNKNOWN;
		पूर्ण अन्यथा अणु
			अगर (twl->linkstat != MUSB_UNKNOWN) अणु
				status = MUSB_VBUS_OFF;
				twl->linkstat = status;
				ret = musb_mailbox(status);
				अगर (ret)
					twl->linkstat = MUSB_UNKNOWN;
				अगर (twl->asleep) अणु
					regulator_disable(twl->usb3v3);
					twl->asleep = 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	sysfs_notअगरy(&twl->dev->kobj, शून्य, "vbus");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t twl6030_usbotg_irq(पूर्णांक irq, व्योम *_twl)
अणु
	काष्ठा twl6030_usb *twl = _twl;
	क्रमागत musb_vbus_id_status status = MUSB_UNKNOWN;
	u8 hw_state;
	पूर्णांक ret;

	hw_state = twl6030_पढ़ोb(twl, TWL6030_MODULE_ID0, STS_HW_CONDITIONS);

	अगर (hw_state & STS_USB_ID) अणु
		ret = regulator_enable(twl->usb3v3);
		अगर (ret)
			dev_err(twl->dev, "Failed to enable usb3v3\n");

		twl->asleep = 1;
		twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x1, USB_ID_INT_EN_HI_CLR);
		twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x10, USB_ID_INT_EN_HI_SET);
		status = MUSB_ID_GROUND;
		twl->linkstat = status;
		ret = musb_mailbox(status);
		अगर (ret)
			twl->linkstat = MUSB_UNKNOWN;
	पूर्ण अन्यथा  अणु
		twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x10, USB_ID_INT_EN_HI_CLR);
		twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x1, USB_ID_INT_EN_HI_SET);
	पूर्ण
	twl6030_ग_लिखोb(twl, TWL_MODULE_USB, status, USB_ID_INT_LATCH_CLR);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम twl6030_status_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा twl6030_usb *twl = container_of(work, काष्ठा twl6030_usb,
					       get_status_work.work);

	twl6030_usb_irq(twl->irq2, twl);
	twl6030_usbotg_irq(twl->irq1, twl);
पूर्ण

अटल पूर्णांक twl6030_enable_irq(काष्ठा twl6030_usb *twl)
अणु
	twl6030_ग_लिखोb(twl, TWL_MODULE_USB, 0x1, USB_ID_INT_EN_HI_SET);
	twl6030_पूर्णांकerrupt_unmask(0x05, REG_INT_MSK_LINE_C);
	twl6030_पूर्णांकerrupt_unmask(0x05, REG_INT_MSK_STS_C);

	twl6030_पूर्णांकerrupt_unmask(TWL6030_CHARGER_CTRL_INT_MASK,
				REG_INT_MSK_LINE_C);
	twl6030_पूर्णांकerrupt_unmask(TWL6030_CHARGER_CTRL_INT_MASK,
				REG_INT_MSK_STS_C);

	वापस 0;
पूर्ण

अटल व्योम otg_set_vbus_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा twl6030_usb *twl = container_of(data, काष्ठा twl6030_usb,
								set_vbus_work);

	/*
	 * Start driving VBUS. Set OPA_MODE bit in CHARGERUSB_CTRL1
	 * रेजिस्टर. This enables boost mode.
	 */

	अगर (twl->vbus_enable)
		twl6030_ग_लिखोb(twl, TWL_MODULE_MAIN_CHARGE, 0x40,
							CHARGERUSB_CTRL1);
	अन्यथा
		twl6030_ग_लिखोb(twl, TWL_MODULE_MAIN_CHARGE, 0x00,
							CHARGERUSB_CTRL1);
पूर्ण

अटल पूर्णांक twl6030_set_vbus(काष्ठा phy_companion *comparator, bool enabled)
अणु
	काष्ठा twl6030_usb *twl = comparator_to_twl(comparator);

	twl->vbus_enable = enabled;
	schedule_work(&twl->set_vbus_work);

	वापस 0;
पूर्ण

अटल पूर्णांक twl6030_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 ret;
	काष्ठा twl6030_usb	*twl;
	पूर्णांक			status, err;
	काष्ठा device_node	*np = pdev->dev.of_node;
	काष्ठा device		*dev = &pdev->dev;

	अगर (!np) अणु
		dev_err(dev, "no DT info\n");
		वापस -EINVAL;
	पूर्ण

	twl = devm_kzalloc(dev, माप(*twl), GFP_KERNEL);
	अगर (!twl)
		वापस -ENOMEM;

	twl->dev		= &pdev->dev;
	twl->irq1		= platक्रमm_get_irq(pdev, 0);
	twl->irq2		= platक्रमm_get_irq(pdev, 1);
	twl->linkstat		= MUSB_UNKNOWN;

	twl->comparator.set_vbus	= twl6030_set_vbus;
	twl->comparator.start_srp	= twl6030_start_srp;

	ret = omap_usb2_set_comparator(&twl->comparator);
	अगर (ret == -ENODEV) अणु
		dev_info(&pdev->dev, "phy not ready, deferring probe");
		वापस -EPROBE_DEFER;
	पूर्ण

	/* init spinlock क्रम workqueue */
	spin_lock_init(&twl->lock);

	err = twl6030_usb_lकरो_init(twl);
	अगर (err) अणु
		dev_err(&pdev->dev, "ldo init failed\n");
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, twl);

	INIT_WORK(&twl->set_vbus_work, otg_set_vbus_work);
	INIT_DELAYED_WORK(&twl->get_status_work, twl6030_status_work);

	status = request_thपढ़ोed_irq(twl->irq1, शून्य, twl6030_usbotg_irq,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			"twl6030_usb", twl);
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "can't get IRQ %d, err %d\n",
			twl->irq1, status);
		जाओ err_put_regulator;
	पूर्ण

	status = request_thपढ़ोed_irq(twl->irq2, शून्य, twl6030_usb_irq,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			"twl6030_usb", twl);
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "can't get IRQ %d, err %d\n",
			twl->irq2, status);
		जाओ err_मुक्त_irq1;
	पूर्ण

	twl->asleep = 0;
	twl6030_enable_irq(twl);
	schedule_delayed_work(&twl->get_status_work, HZ);
	dev_info(&pdev->dev, "Initialized TWL6030 USB module\n");

	वापस 0;

err_मुक्त_irq1:
	मुक्त_irq(twl->irq1, twl);
err_put_regulator:
	regulator_put(twl->usb3v3);

	वापस status;
पूर्ण

अटल पूर्णांक twl6030_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl6030_usb *twl = platक्रमm_get_drvdata(pdev);

	cancel_delayed_work_sync(&twl->get_status_work);
	twl6030_पूर्णांकerrupt_mask(TWL6030_USBOTG_INT_MASK,
		REG_INT_MSK_LINE_C);
	twl6030_पूर्णांकerrupt_mask(TWL6030_USBOTG_INT_MASK,
			REG_INT_MSK_STS_C);
	मुक्त_irq(twl->irq1, twl);
	मुक्त_irq(twl->irq2, twl);
	regulator_put(twl->usb3v3);
	cancel_work_sync(&twl->set_vbus_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id twl6030_usb_id_table[] = अणु
	अणु .compatible = "ti,twl6030-usb" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, twl6030_usb_id_table);

अटल काष्ठा platक्रमm_driver twl6030_usb_driver = अणु
	.probe		= twl6030_usb_probe,
	.हटाओ		= twl6030_usb_हटाओ,
	.driver		= अणु
		.name	= "twl6030_usb",
		.of_match_table = of_match_ptr(twl6030_usb_id_table),
		.dev_groups = twl6030_groups,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init twl6030_usb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&twl6030_usb_driver);
पूर्ण
subsys_initcall(twl6030_usb_init);

अटल व्योम __निकास twl6030_usb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&twl6030_usb_driver);
पूर्ण
module_निकास(twl6030_usb_निकास);

MODULE_ALIAS("platform:twl6030_usb");
MODULE_AUTHOR("Hema HK <hemahk@ti.com>");
MODULE_DESCRIPTION("TWL6030 USB transceiver driver");
MODULE_LICENSE("GPL");
