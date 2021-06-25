<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 Main Battery Charger Driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 *
 * Broken करोwn from monstrous PCF50633 driver मुख्यly by
 * Harald Welte, Andy Green and Werner Almesberger
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>

#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/mfd/pcf50633/mbc.h>

काष्ठा pcf50633_mbc अणु
	काष्ठा pcf50633 *pcf;

	पूर्णांक adapter_online;
	पूर्णांक usb_online;

	काष्ठा घातer_supply *usb;
	काष्ठा घातer_supply *adapter;
	काष्ठा घातer_supply *ac;
पूर्ण;

पूर्णांक pcf50633_mbc_usb_curlim_set(काष्ठा pcf50633 *pcf, पूर्णांक ma)
अणु
	काष्ठा pcf50633_mbc *mbc = platक्रमm_get_drvdata(pcf->mbc_pdev);
	पूर्णांक ret = 0;
	u8 bits;
	u8 mbcs2, chgmod;
	अचिन्हित पूर्णांक mbcc5;

	अगर (ma >= 1000) अणु
		bits = PCF50633_MBCC7_USB_1000mA;
		ma = 1000;
	पूर्ण अन्यथा अगर (ma >= 500) अणु
		bits = PCF50633_MBCC7_USB_500mA;
		ma = 500;
	पूर्ण अन्यथा अगर (ma >= 100) अणु
		bits = PCF50633_MBCC7_USB_100mA;
		ma = 100;
	पूर्ण अन्यथा अणु
		bits = PCF50633_MBCC7_USB_SUSPEND;
		ma = 0;
	पूर्ण

	ret = pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC7,
					PCF50633_MBCC7_USB_MASK, bits);
	अगर (ret)
		dev_err(pcf->dev, "error setting usb curlim to %d mA\n", ma);
	अन्यथा
		dev_info(pcf->dev, "usb curlim to %d mA\n", ma);

	/*
	 * We limit the अक्षरging current to be the USB current limit.
	 * The reason is that on pcf50633, when it enters PMU Standby mode,
	 * which it करोes when the device goes "off", the USB current limit
	 * reverts to the variant शेष.  In at least one common हाल, that
	 * शेष is 500mA.  By setting the अक्षरging current to be the same
	 * as the USB limit we set here beक्रमe PMU standby, we enक्रमce it only
	 * using the correct amount of current even when the USB current limit
	 * माला_लो reset to the wrong thing
	 */

	अगर (mbc->pcf->pdata->अक्षरger_reference_current_ma) अणु
		mbcc5 = (ma << 8) / mbc->pcf->pdata->अक्षरger_reference_current_ma;
		अगर (mbcc5 > 255)
			mbcc5 = 255;
		pcf50633_reg_ग_लिखो(mbc->pcf, PCF50633_REG_MBCC5, mbcc5);
	पूर्ण

	mbcs2 = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCS2);
	chgmod = (mbcs2 & PCF50633_MBCS2_MBC_MASK);

	/* If chgmod == BATFULL, setting chgena has no effect.
	 * Datasheet says we need to set resume instead but when स्वतःresume is
	 * used resume करोesn't work. Clear and set chgena instead.
	 */
	अगर (chgmod != PCF50633_MBCS2_MBC_BAT_FULL)
		pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA, PCF50633_MBCC1_CHGENA);
	अन्यथा अणु
		pcf50633_reg_clear_bits(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA);
		pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA, PCF50633_MBCC1_CHGENA);
	पूर्ण

	घातer_supply_changed(mbc->usb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_mbc_usb_curlim_set);

पूर्णांक pcf50633_mbc_get_status(काष्ठा pcf50633 *pcf)
अणु
	काष्ठा pcf50633_mbc *mbc  = platक्रमm_get_drvdata(pcf->mbc_pdev);
	पूर्णांक status = 0;
	u8 chgmod;

	अगर (!mbc)
		वापस 0;

	chgmod = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCS2)
		& PCF50633_MBCS2_MBC_MASK;

	अगर (mbc->usb_online)
		status |= PCF50633_MBC_USB_ONLINE;
	अगर (chgmod == PCF50633_MBCS2_MBC_USB_PRE ||
	    chgmod == PCF50633_MBCS2_MBC_USB_PRE_WAIT ||
	    chgmod == PCF50633_MBCS2_MBC_USB_FAST ||
	    chgmod == PCF50633_MBCS2_MBC_USB_FAST_WAIT)
		status |= PCF50633_MBC_USB_ACTIVE;
	अगर (mbc->adapter_online)
		status |= PCF50633_MBC_ADAPTER_ONLINE;
	अगर (chgmod == PCF50633_MBCS2_MBC_ADP_PRE ||
	    chgmod == PCF50633_MBCS2_MBC_ADP_PRE_WAIT ||
	    chgmod == PCF50633_MBCS2_MBC_ADP_FAST ||
	    chgmod == PCF50633_MBCS2_MBC_ADP_FAST_WAIT)
		status |= PCF50633_MBC_ADAPTER_ACTIVE;

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_mbc_get_status);

पूर्णांक pcf50633_mbc_get_usb_online_status(काष्ठा pcf50633 *pcf)
अणु
	काष्ठा pcf50633_mbc *mbc  = platक्रमm_get_drvdata(pcf->mbc_pdev);

	अगर (!mbc)
		वापस 0;

	वापस mbc->usb_online;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_mbc_get_usb_online_status);

अटल sमाप_प्रकार
show_chgmode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcf50633_mbc *mbc = dev_get_drvdata(dev);

	u8 mbcs2 = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCS2);
	u8 chgmod = (mbcs2 & PCF50633_MBCS2_MBC_MASK);

	वापस प्र_लिखो(buf, "%d\n", chgmod);
पूर्ण
अटल DEVICE_ATTR(chgmode, S_IRUGO, show_chgmode, शून्य);

अटल sमाप_प्रकार
show_usblim(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcf50633_mbc *mbc = dev_get_drvdata(dev);
	u8 usblim = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCC7) &
						PCF50633_MBCC7_USB_MASK;
	अचिन्हित पूर्णांक ma;

	अगर (usblim == PCF50633_MBCC7_USB_1000mA)
		ma = 1000;
	अन्यथा अगर (usblim == PCF50633_MBCC7_USB_500mA)
		ma = 500;
	अन्यथा अगर (usblim == PCF50633_MBCC7_USB_100mA)
		ma = 100;
	अन्यथा
		ma = 0;

	वापस प्र_लिखो(buf, "%u\n", ma);
पूर्ण

अटल sमाप_प्रकार set_usblim(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcf50633_mbc *mbc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ ma;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &ma);
	अगर (ret)
		वापस ret;

	pcf50633_mbc_usb_curlim_set(mbc->pcf, ma);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(usb_curlim, S_IRUGO | S_IWUSR, show_usblim, set_usblim);

अटल sमाप_प्रकार
show_chglim(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcf50633_mbc *mbc = dev_get_drvdata(dev);
	u8 mbcc5 = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCC5);
	अचिन्हित पूर्णांक ma;

	अगर (!mbc->pcf->pdata->अक्षरger_reference_current_ma)
		वापस -ENODEV;

	ma = (mbc->pcf->pdata->अक्षरger_reference_current_ma *  mbcc5) >> 8;

	वापस प्र_लिखो(buf, "%u\n", ma);
पूर्ण

अटल sमाप_प्रकार set_chglim(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcf50633_mbc *mbc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ ma;
	अचिन्हित पूर्णांक mbcc5;
	पूर्णांक ret;

	अगर (!mbc->pcf->pdata->अक्षरger_reference_current_ma)
		वापस -ENODEV;

	ret = kम_से_अदीर्घ(buf, 10, &ma);
	अगर (ret)
		वापस ret;

	mbcc5 = (ma << 8) / mbc->pcf->pdata->अक्षरger_reference_current_ma;
	अगर (mbcc5 > 255)
		mbcc5 = 255;
	pcf50633_reg_ग_लिखो(mbc->pcf, PCF50633_REG_MBCC5, mbcc5);

	वापस count;
पूर्ण

/*
 * This attribute allows to change MBC अक्षरging limit on the fly
 * independently of usb current limit. It also माला_लो set स्वतःmatically every
 * समय usb current limit is changed.
 */
अटल DEVICE_ATTR(chg_curlim, S_IRUGO | S_IWUSR, show_chglim, set_chglim);

अटल काष्ठा attribute *pcf50633_mbc_sysfs_attrs[] = अणु
	&dev_attr_chgmode.attr,
	&dev_attr_usb_curlim.attr,
	&dev_attr_chg_curlim.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(pcf50633_mbc_sysfs);

अटल व्योम
pcf50633_mbc_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pcf50633_mbc *mbc = data;

	/* USB */
	अगर (irq == PCF50633_IRQ_USBINS) अणु
		mbc->usb_online = 1;
	पूर्ण अन्यथा अगर (irq == PCF50633_IRQ_USBREM) अणु
		mbc->usb_online = 0;
		pcf50633_mbc_usb_curlim_set(mbc->pcf, 0);
	पूर्ण

	/* Adapter */
	अगर (irq == PCF50633_IRQ_ADPINS)
		mbc->adapter_online = 1;
	अन्यथा अगर (irq == PCF50633_IRQ_ADPREM)
		mbc->adapter_online = 0;

	घातer_supply_changed(mbc->ac);
	घातer_supply_changed(mbc->usb);
	घातer_supply_changed(mbc->adapter);

	अगर (mbc->pcf->pdata->mbc_event_callback)
		mbc->pcf->pdata->mbc_event_callback(mbc->pcf, irq);
पूर्ण

अटल पूर्णांक adapter_get_property(काष्ठा घातer_supply *psy,
			क्रमागत घातer_supply_property psp,
			जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pcf50633_mbc *mbc = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval =  mbc->adapter_online;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक usb_get_property(काष्ठा घातer_supply *psy,
			क्रमागत घातer_supply_property psp,
			जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pcf50633_mbc *mbc = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;
	u8 usblim = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCC7) &
						PCF50633_MBCC7_USB_MASK;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = mbc->usb_online &&
				(usblim <= PCF50633_MBCC7_USB_500mA);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ac_get_property(काष्ठा घातer_supply *psy,
			क्रमागत घातer_supply_property psp,
			जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pcf50633_mbc *mbc = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;
	u8 usblim = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCC7) &
						PCF50633_MBCC7_USB_MASK;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = mbc->usb_online &&
				(usblim == PCF50633_MBCC7_USB_1000mA);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property घातer_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल स्थिर u8 mbc_irq_handlers[] = अणु
	PCF50633_IRQ_ADPINS,
	PCF50633_IRQ_ADPREM,
	PCF50633_IRQ_USBINS,
	PCF50633_IRQ_USBREM,
	PCF50633_IRQ_BATFULL,
	PCF50633_IRQ_CHGHALT,
	PCF50633_IRQ_THLIMON,
	PCF50633_IRQ_THLIMOFF,
	PCF50633_IRQ_USBLIMON,
	PCF50633_IRQ_USBLIMOFF,
	PCF50633_IRQ_LOWSYS,
	PCF50633_IRQ_LOWBAT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pcf50633_mbc_adapter_desc = अणु
	.name		= "adapter",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= घातer_props,
	.num_properties	= ARRAY_SIZE(घातer_props),
	.get_property	= &adapter_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pcf50633_mbc_usb_desc = अणु
	.name		= "usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= घातer_props,
	.num_properties	= ARRAY_SIZE(घातer_props),
	.get_property	= usb_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pcf50633_mbc_ac_desc = अणु
	.name		= "ac",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= घातer_props,
	.num_properties	= ARRAY_SIZE(घातer_props),
	.get_property	= ac_get_property,
पूर्ण;

अटल पूर्णांक pcf50633_mbc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा घातer_supply_config usb_psy_cfg;
	काष्ठा pcf50633_mbc *mbc;
	पूर्णांक i;
	u8 mbcs1;

	mbc = devm_kzalloc(&pdev->dev, माप(*mbc), GFP_KERNEL);
	अगर (!mbc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mbc);
	mbc->pcf = dev_to_pcf50633(pdev->dev.parent);

	/* Set up IRQ handlers */
	क्रम (i = 0; i < ARRAY_SIZE(mbc_irq_handlers); i++)
		pcf50633_रेजिस्टर_irq(mbc->pcf, mbc_irq_handlers[i],
					pcf50633_mbc_irq_handler, mbc);

	psy_cfg.supplied_to		= mbc->pcf->pdata->batteries;
	psy_cfg.num_supplicants		= mbc->pcf->pdata->num_batteries;
	psy_cfg.drv_data		= mbc;

	/* Create घातer supplies */
	mbc->adapter = घातer_supply_रेजिस्टर(&pdev->dev,
					     &pcf50633_mbc_adapter_desc,
					     &psy_cfg);
	अगर (IS_ERR(mbc->adapter)) अणु
		dev_err(mbc->pcf->dev, "failed to register adapter\n");
		वापस PTR_ERR(mbc->adapter);
	पूर्ण

	usb_psy_cfg = psy_cfg;
	usb_psy_cfg.attr_grp = pcf50633_mbc_sysfs_groups;

	mbc->usb = घातer_supply_रेजिस्टर(&pdev->dev, &pcf50633_mbc_usb_desc,
					 &usb_psy_cfg);
	अगर (IS_ERR(mbc->usb)) अणु
		dev_err(mbc->pcf->dev, "failed to register usb\n");
		घातer_supply_unरेजिस्टर(mbc->adapter);
		वापस PTR_ERR(mbc->usb);
	पूर्ण

	mbc->ac = घातer_supply_रेजिस्टर(&pdev->dev, &pcf50633_mbc_ac_desc,
					&psy_cfg);
	अगर (IS_ERR(mbc->ac)) अणु
		dev_err(mbc->pcf->dev, "failed to register ac\n");
		घातer_supply_unरेजिस्टर(mbc->adapter);
		घातer_supply_unरेजिस्टर(mbc->usb);
		वापस PTR_ERR(mbc->ac);
	पूर्ण

	mbcs1 = pcf50633_reg_पढ़ो(mbc->pcf, PCF50633_REG_MBCS1);
	अगर (mbcs1 & PCF50633_MBCS1_USBPRES)
		pcf50633_mbc_irq_handler(PCF50633_IRQ_USBINS, mbc);
	अगर (mbcs1 & PCF50633_MBCS1_ADAPTPRES)
		pcf50633_mbc_irq_handler(PCF50633_IRQ_ADPINS, mbc);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_mbc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_mbc *mbc = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	/* Remove IRQ handlers */
	क्रम (i = 0; i < ARRAY_SIZE(mbc_irq_handlers); i++)
		pcf50633_मुक्त_irq(mbc->pcf, mbc_irq_handlers[i]);

	घातer_supply_unरेजिस्टर(mbc->usb);
	घातer_supply_unरेजिस्टर(mbc->adapter);
	घातer_supply_unरेजिस्टर(mbc->ac);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcf50633_mbc_driver = अणु
	.driver = अणु
		.name = "pcf50633-mbc",
	पूर्ण,
	.probe = pcf50633_mbc_probe,
	.हटाओ = pcf50633_mbc_हटाओ,
पूर्ण;

module_platक्रमm_driver(pcf50633_mbc_driver);

MODULE_AUTHOR("Balaji Rao <balajirrao@openmoko.org>");
MODULE_DESCRIPTION("PCF50633 mbc driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcf50633-mbc");
