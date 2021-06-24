<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery driver क्रम Maxim MAX8925
 *
 * Copyright (c) 2009-2010 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/max8925.h>

/* रेजिस्टरs in GPM */
#घोषणा MAX8925_OUT5VEN			0x54
#घोषणा MAX8925_OUT3VEN			0x58
#घोषणा MAX8925_CHG_CNTL1		0x7c

/* bits definition */
#घोषणा MAX8925_CHG_STAT_VSYSLOW	(1 << 0)
#घोषणा MAX8925_CHG_STAT_MODE_MASK	(3 << 2)
#घोषणा MAX8925_CHG_STAT_EN_MASK	(1 << 4)
#घोषणा MAX8925_CHG_MBDET		(1 << 1)
#घोषणा MAX8925_CHG_AC_RANGE_MASK	(3 << 6)

/* रेजिस्टरs in ADC */
#घोषणा MAX8925_ADC_RES_CNFG1		0x06
#घोषणा MAX8925_ADC_AVG_CNFG1		0x07
#घोषणा MAX8925_ADC_ACQ_CNFG1		0x08
#घोषणा MAX8925_ADC_ACQ_CNFG2		0x09
/* 2 bytes रेजिस्टरs in below. MSB is 1st, LSB is 2nd. */
#घोषणा MAX8925_ADC_AUX2		0x62
#घोषणा MAX8925_ADC_VCHG		0x64
#घोषणा MAX8925_ADC_VBBATT		0x66
#घोषणा MAX8925_ADC_VMBATT		0x68
#घोषणा MAX8925_ADC_ISNS		0x6a
#घोषणा MAX8925_ADC_THM			0x6c
#घोषणा MAX8925_ADC_TDIE		0x6e
#घोषणा MAX8925_CMD_AUX2		0xc8
#घोषणा MAX8925_CMD_VCHG		0xd0
#घोषणा MAX8925_CMD_VBBATT		0xd8
#घोषणा MAX8925_CMD_VMBATT		0xe0
#घोषणा MAX8925_CMD_ISNS		0xe8
#घोषणा MAX8925_CMD_THM			0xf0
#घोषणा MAX8925_CMD_TDIE		0xf8

क्रमागत अणु
	MEASURE_AUX2,
	MEASURE_VCHG,
	MEASURE_VBBATT,
	MEASURE_VMBATT,
	MEASURE_ISNS,
	MEASURE_THM,
	MEASURE_TDIE,
	MEASURE_MAX,
पूर्ण;

काष्ठा max8925_घातer_info अणु
	काष्ठा max8925_chip	*chip;
	काष्ठा i2c_client	*gpm;
	काष्ठा i2c_client	*adc;

	काष्ठा घातer_supply	*ac;
	काष्ठा घातer_supply	*usb;
	काष्ठा घातer_supply	*battery;
	पूर्णांक			irq_base;
	अचिन्हित		ac_online:1;
	अचिन्हित		usb_online:1;
	अचिन्हित		bat_online:1;
	अचिन्हित		chg_mode:2;
	अचिन्हित		batt_detect:1;	/* detecing MB by ID pin */
	अचिन्हित		topoff_threshold:2;
	अचिन्हित		fast_अक्षरge:3;
	अचिन्हित		no_temp_support:1;
	अचिन्हित		no_insert_detect:1;

	पूर्णांक (*set_अक्षरger) (पूर्णांक);
पूर्ण;

अटल पूर्णांक __set_अक्षरger(काष्ठा max8925_घातer_info *info, पूर्णांक enable)
अणु
	काष्ठा max8925_chip *chip = info->chip;
	अगर (enable) अणु
		/* enable अक्षरger in platक्रमm */
		अगर (info->set_अक्षरger)
			info->set_अक्षरger(1);
		/* enable अक्षरger */
		max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 1 << 7, 0);
	पूर्ण अन्यथा अणु
		/* disable अक्षरge */
		max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 1 << 7, 1 << 7);
		अगर (info->set_अक्षरger)
			info->set_अक्षरger(0);
	पूर्ण
	dev_dbg(chip->dev, "%s\n", (enable) ? "Enable charger"
		: "Disable charger");
	वापस 0;
पूर्ण

अटल irqवापस_t max8925_अक्षरger_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8925_घातer_info *info = (काष्ठा max8925_घातer_info *)data;
	काष्ठा max8925_chip *chip = info->chip;

	चयन (irq - chip->irq_base) अणु
	हाल MAX8925_IRQ_VCHG_DC_R:
		info->ac_online = 1;
		__set_अक्षरger(info, 1);
		dev_dbg(chip->dev, "Adapter inserted\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_DC_F:
		info->ac_online = 0;
		__set_अक्षरger(info, 0);
		dev_dbg(chip->dev, "Adapter removed\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_THM_OK_F:
		/* Battery is not पढ़ोy yet */
		dev_dbg(chip->dev, "Battery temperature is out of range\n");
		fallthrough;
	हाल MAX8925_IRQ_VCHG_DC_OVP:
		dev_dbg(chip->dev, "Error detection\n");
		__set_अक्षरger(info, 0);
		अवरोध;
	हाल MAX8925_IRQ_VCHG_THM_OK_R:
		/* Battery is पढ़ोy now */
		dev_dbg(chip->dev, "Battery temperature is in range\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_SYSLOW_R:
		/* VSYS is low */
		dev_info(chip->dev, "Sys power is too low\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_SYSLOW_F:
		dev_dbg(chip->dev, "Sys power is above low threshold\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_DONE:
		__set_अक्षरger(info, 0);
		dev_dbg(chip->dev, "Charging is done\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_TOPOFF:
		dev_dbg(chip->dev, "Charging in top-off mode\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_TMR_FAULT:
		__set_अक्षरger(info, 0);
		dev_dbg(chip->dev, "Safe timer is expired\n");
		अवरोध;
	हाल MAX8925_IRQ_VCHG_RST:
		__set_अक्षरger(info, 0);
		dev_dbg(chip->dev, "Charger is reset\n");
		अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक start_measure(काष्ठा max8925_घातer_info *info, पूर्णांक type)
अणु
	अचिन्हित अक्षर buf[2] = अणु0, 0पूर्ण;
	पूर्णांक meas_cmd;
	पूर्णांक meas_reg = 0, ret;

	चयन (type) अणु
	हाल MEASURE_VCHG:
		meas_cmd = MAX8925_CMD_VCHG;
		meas_reg = MAX8925_ADC_VCHG;
		अवरोध;
	हाल MEASURE_VBBATT:
		meas_cmd = MAX8925_CMD_VBBATT;
		meas_reg = MAX8925_ADC_VBBATT;
		अवरोध;
	हाल MEASURE_VMBATT:
		meas_cmd = MAX8925_CMD_VMBATT;
		meas_reg = MAX8925_ADC_VMBATT;
		अवरोध;
	हाल MEASURE_ISNS:
		meas_cmd = MAX8925_CMD_ISNS;
		meas_reg = MAX8925_ADC_ISNS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	max8925_reg_ग_लिखो(info->adc, meas_cmd, 0);
	max8925_bulk_पढ़ो(info->adc, meas_reg, 2, buf);
	ret = ((buf[0]<<8) | buf[1]) >> 4;

	वापस ret;
पूर्ण

अटल पूर्णांक max8925_ac_get_prop(काष्ठा घातer_supply *psy,
			       क्रमागत घातer_supply_property psp,
			       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max8925_घातer_info *info = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = info->ac_online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (info->ac_online) अणु
			ret = start_measure(info, MEASURE_VCHG);
			अगर (ret >= 0) अणु
				val->पूर्णांकval = ret * 2000;	/* unit is uV */
				जाओ out;
			पूर्ण
		पूर्ण
		ret = -ENODATA;
		अवरोध;
	शेष:
		ret = -ENODEV;
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property max8925_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

अटल पूर्णांक max8925_usb_get_prop(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max8925_घातer_info *info = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = info->usb_online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (info->usb_online) अणु
			ret = start_measure(info, MEASURE_VCHG);
			अगर (ret >= 0) अणु
				val->पूर्णांकval = ret * 2000;	/* unit is uV */
				जाओ out;
			पूर्ण
		पूर्ण
		ret = -ENODATA;
		अवरोध;
	शेष:
		ret = -ENODEV;
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property max8925_usb_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

अटल पूर्णांक max8925_bat_get_prop(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max8925_घातer_info *info = dev_get_drvdata(psy->dev.parent);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = info->bat_online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (info->bat_online) अणु
			ret = start_measure(info, MEASURE_VMBATT);
			अगर (ret >= 0) अणु
				val->पूर्णांकval = ret * 2000;	/* unit is uV */
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		ret = -ENODATA;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		अगर (info->bat_online) अणु
			ret = start_measure(info, MEASURE_ISNS);
			अगर (ret >= 0) अणु
				/* assume r_sns is 0.02 */
				ret = ((ret * 6250) - 3125) /* uA */;
				val->पूर्णांकval = 0;
				अगर (ret > 0)
					val->पूर्णांकval = ret; /* unit is mA */
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		ret = -ENODATA;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		अगर (!info->bat_online) अणु
			ret = -ENODATA;
			अवरोध;
		पूर्ण
		ret = max8925_reg_पढ़ो(info->gpm, MAX8925_CHG_STATUS);
		ret = (ret & MAX8925_CHG_STAT_MODE_MASK) >> 2;
		चयन (ret) अणु
		हाल 1:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
			अवरोध;
		हाल 0:
		हाल 2:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			अवरोध;
		हाल 3:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			अवरोध;
		पूर्ण
		ret = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!info->bat_online) अणु
			ret = -ENODATA;
			अवरोध;
		पूर्ण
		ret = max8925_reg_पढ़ो(info->gpm, MAX8925_CHG_STATUS);
		अगर (info->usb_online || info->ac_online) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अगर (ret & MAX8925_CHG_STAT_EN_MASK)
				val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		ret = 0;
		अवरोध;
	शेष:
		ret = -ENODEV;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property max8925_battery_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_STATUS,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc ac_desc = अणु
	.name		= "max8925-ac",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= max8925_ac_props,
	.num_properties	= ARRAY_SIZE(max8925_ac_props),
	.get_property	= max8925_ac_get_prop,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc usb_desc = अणु
	.name		= "max8925-usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= max8925_usb_props,
	.num_properties	= ARRAY_SIZE(max8925_usb_props),
	.get_property	= max8925_usb_get_prop,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc battery_desc = अणु
	.name		= "max8925-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= max8925_battery_props,
	.num_properties	= ARRAY_SIZE(max8925_battery_props),
	.get_property	= max8925_bat_get_prop,
पूर्ण;

#घोषणा REQUEST_IRQ(_irq, _name)					\
करो अणु									\
	ret = request_thपढ़ोed_irq(chip->irq_base + _irq, शून्य,		\
				    max8925_अक्षरger_handler,		\
				    IRQF_ONESHOT, _name, info);		\
	अगर (ret)							\
		dev_err(chip->dev, "Failed to request IRQ #%d: %d\n",	\
			_irq, ret);					\
पूर्ण जबतक (0)

अटल पूर्णांक max8925_init_अक्षरger(काष्ठा max8925_chip *chip,
					  काष्ठा max8925_घातer_info *info)
अणु
	पूर्णांक ret;

	REQUEST_IRQ(MAX8925_IRQ_VCHG_DC_OVP, "ac-ovp");
	अगर (!info->no_insert_detect) अणु
		REQUEST_IRQ(MAX8925_IRQ_VCHG_DC_F, "ac-remove");
		REQUEST_IRQ(MAX8925_IRQ_VCHG_DC_R, "ac-insert");
	पूर्ण
	अगर (!info->no_temp_support) अणु
		REQUEST_IRQ(MAX8925_IRQ_VCHG_THM_OK_R, "batt-temp-in-range");
		REQUEST_IRQ(MAX8925_IRQ_VCHG_THM_OK_F, "batt-temp-out-range");
	पूर्ण
	REQUEST_IRQ(MAX8925_IRQ_VCHG_SYSLOW_F, "vsys-high");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_SYSLOW_R, "vsys-low");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_RST, "charger-reset");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_DONE, "charger-done");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_TOPOFF, "charger-topoff");
	REQUEST_IRQ(MAX8925_IRQ_VCHG_TMR_FAULT, "charger-timer-expire");

	info->usb_online = 0;
	info->bat_online = 0;

	/* check क्रम घातer - can miss पूर्णांकerrupt at boot समय */
	अगर (start_measure(info, MEASURE_VCHG) * 2000 > 500000)
		info->ac_online = 1;
	अन्यथा
		info->ac_online = 0;

	ret = max8925_reg_पढ़ो(info->gpm, MAX8925_CHG_STATUS);
	अगर (ret >= 0) अणु
		/*
		 * If battery detection is enabled, ID pin of battery is
		 * connected to MBDET pin of MAX8925. It could be used to
		 * detect battery presence.
		 * Otherwise, we have to assume that battery is always on.
		 */
		अगर (info->batt_detect)
			info->bat_online = (ret & MAX8925_CHG_MBDET) ? 0 : 1;
		अन्यथा
			info->bat_online = 1;
		अगर (ret & MAX8925_CHG_AC_RANGE_MASK)
			info->ac_online = 1;
		अन्यथा
			info->ac_online = 0;
	पूर्ण
	/* disable अक्षरge */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 1 << 7, 1 << 7);
	/* set अक्षरging current in अक्षरge topoff mode */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 3 << 5,
			 info->topoff_threshold << 5);
	/* set अक्षरing current in fast अक्षरge mode */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTL1, 7, info->fast_अक्षरge);

	वापस 0;
पूर्ण

अटल पूर्णांक max8925_deinit_अक्षरger(काष्ठा max8925_घातer_info *info)
अणु
	काष्ठा max8925_chip *chip = info->chip;
	पूर्णांक irq;

	irq = chip->irq_base + MAX8925_IRQ_VCHG_DC_OVP;
	क्रम (; irq <= chip->irq_base + MAX8925_IRQ_VCHG_TMR_FAULT; irq++)
		मुक्त_irq(irq, info);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा max8925_घातer_pdata *
max8925_घातer_dt_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *nproot = pdev->dev.parent->of_node;
	काष्ठा device_node *np;
	पूर्णांक batt_detect;
	पूर्णांक topoff_threshold;
	पूर्णांक fast_अक्षरge;
	पूर्णांक no_temp_support;
	पूर्णांक no_insert_detect;
	काष्ठा max8925_घातer_pdata *pdata;

	अगर (!nproot)
		वापस pdev->dev.platक्रमm_data;

	np = of_get_child_by_name(nproot, "charger");
	अगर (!np) अणु
		dev_err(&pdev->dev, "failed to find charger node\n");
		वापस शून्य;
	पूर्ण

	pdata = devm_kzalloc(&pdev->dev,
			माप(काष्ठा max8925_घातer_pdata),
			GFP_KERNEL);
	अगर (!pdata)
		जाओ ret;

	of_property_पढ़ो_u32(np, "topoff-threshold", &topoff_threshold);
	of_property_पढ़ो_u32(np, "batt-detect", &batt_detect);
	of_property_पढ़ो_u32(np, "fast-charge", &fast_अक्षरge);
	of_property_पढ़ो_u32(np, "no-insert-detect", &no_insert_detect);
	of_property_पढ़ो_u32(np, "no-temp-support", &no_temp_support);

	pdata->batt_detect = batt_detect;
	pdata->fast_अक्षरge = fast_अक्षरge;
	pdata->topoff_threshold = topoff_threshold;
	pdata->no_insert_detect = no_insert_detect;
	pdata->no_temp_support = no_temp_support;

ret:
	of_node_put(np);
	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा max8925_घातer_pdata *
max8925_घातer_dt_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस pdev->dev.platक्रमm_data;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक max8925_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण; /* Only क्रम ac and usb */
	काष्ठा max8925_घातer_pdata *pdata = शून्य;
	काष्ठा max8925_घातer_info *info;
	पूर्णांक ret;

	pdata = max8925_घातer_dt_init(pdev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "platform data isn't assigned to "
			"power supply\n");
		वापस -EINVAL;
	पूर्ण

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max8925_घातer_info),
				GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->chip = chip;
	info->gpm = chip->i2c;
	info->adc = chip->adc;
	platक्रमm_set_drvdata(pdev, info);

	psy_cfg.supplied_to = pdata->supplied_to;
	psy_cfg.num_supplicants = pdata->num_supplicants;

	info->ac = घातer_supply_रेजिस्टर(&pdev->dev, &ac_desc, &psy_cfg);
	अगर (IS_ERR(info->ac)) अणु
		ret = PTR_ERR(info->ac);
		जाओ out;
	पूर्ण
	info->ac->dev.parent = &pdev->dev;

	info->usb = घातer_supply_रेजिस्टर(&pdev->dev, &usb_desc, &psy_cfg);
	अगर (IS_ERR(info->usb)) अणु
		ret = PTR_ERR(info->usb);
		जाओ out_unरेजिस्टर_ac;
	पूर्ण
	info->usb->dev.parent = &pdev->dev;

	info->battery = घातer_supply_रेजिस्टर(&pdev->dev, &battery_desc, शून्य);
	अगर (IS_ERR(info->battery)) अणु
		ret = PTR_ERR(info->battery);
		जाओ out_unरेजिस्टर_usb;
	पूर्ण
	info->battery->dev.parent = &pdev->dev;

	info->batt_detect = pdata->batt_detect;
	info->topoff_threshold = pdata->topoff_threshold;
	info->fast_अक्षरge = pdata->fast_अक्षरge;
	info->set_अक्षरger = pdata->set_अक्षरger;
	info->no_temp_support = pdata->no_temp_support;
	info->no_insert_detect = pdata->no_insert_detect;

	max8925_init_अक्षरger(chip, info);
	वापस 0;
out_unरेजिस्टर_usb:
	घातer_supply_unरेजिस्टर(info->usb);
out_unरेजिस्टर_ac:
	घातer_supply_unरेजिस्टर(info->ac);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक max8925_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8925_घातer_info *info = platक्रमm_get_drvdata(pdev);

	अगर (info) अणु
		घातer_supply_unरेजिस्टर(info->ac);
		घातer_supply_unरेजिस्टर(info->usb);
		घातer_supply_unरेजिस्टर(info->battery);
		max8925_deinit_अक्षरger(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver max8925_घातer_driver = अणु
	.probe	= max8925_घातer_probe,
	.हटाओ	= max8925_घातer_हटाओ,
	.driver	= अणु
		.name	= "max8925-power",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(max8925_घातer_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Power supply driver for MAX8925");
MODULE_ALIAS("platform:max8925-power");
