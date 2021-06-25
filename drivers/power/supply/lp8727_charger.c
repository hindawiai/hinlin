<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम LP8727 Micro/Mini USB IC with पूर्णांकegrated अक्षरger
 *
 *			Copyright (C) 2011 Texas Instruments
 *			Copyright (C) 2011 National Semiconductor
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/platक्रमm_data/lp8727.h>
#समावेश <linux/of.h>

#घोषणा LP8788_NUM_INTREGS	2
#घोषणा DEFAULT_DEBOUNCE_MSEC	270

/* Registers */
#घोषणा LP8727_CTRL1		0x1
#घोषणा LP8727_CTRL2		0x2
#घोषणा LP8727_SWCTRL		0x3
#घोषणा LP8727_INT1		0x4
#घोषणा LP8727_INT2		0x5
#घोषणा LP8727_STATUS1		0x6
#घोषणा LP8727_STATUS2		0x7
#घोषणा LP8727_CHGCTRL2		0x9

/* CTRL1 रेजिस्टर */
#घोषणा LP8727_CP_EN		BIT(0)
#घोषणा LP8727_ADC_EN		BIT(1)
#घोषणा LP8727_ID200_EN		BIT(4)

/* CTRL2 रेजिस्टर */
#घोषणा LP8727_CHGDET_EN	BIT(1)
#घोषणा LP8727_INT_EN		BIT(6)

/* SWCTRL रेजिस्टर */
#घोषणा LP8727_SW_DM1_DM	(0x0 << 0)
#घोषणा LP8727_SW_DM1_HiZ	(0x7 << 0)
#घोषणा LP8727_SW_DP2_DP	(0x0 << 3)
#घोषणा LP8727_SW_DP2_HiZ	(0x7 << 3)

/* INT1 रेजिस्टर */
#घोषणा LP8727_IDNO		(0xF << 0)
#घोषणा LP8727_VBUS		BIT(4)

/* STATUS1 रेजिस्टर */
#घोषणा LP8727_CHGSTAT		(3 << 4)
#घोषणा LP8727_CHPORT		BIT(6)
#घोषणा LP8727_DCPORT		BIT(7)
#घोषणा LP8727_STAT_EOC		0x30

/* STATUS2 रेजिस्टर */
#घोषणा LP8727_TEMP_STAT	(3 << 5)
#घोषणा LP8727_TEMP_SHIFT	5

/* CHGCTRL2 रेजिस्टर */
#घोषणा LP8727_ICHG_SHIFT	4

क्रमागत lp8727_dev_id अणु
	LP8727_ID_NONE,
	LP8727_ID_TA,
	LP8727_ID_DEDICATED_CHG,
	LP8727_ID_USB_CHG,
	LP8727_ID_USB_DS,
	LP8727_ID_MAX,
पूर्ण;

क्रमागत lp8727_die_temp अणु
	LP8788_TEMP_75C,
	LP8788_TEMP_95C,
	LP8788_TEMP_115C,
	LP8788_TEMP_135C,
पूर्ण;

काष्ठा lp8727_psy अणु
	काष्ठा घातer_supply *ac;
	काष्ठा घातer_supply *usb;
	काष्ठा घातer_supply *batt;
पूर्ण;

काष्ठा lp8727_chg अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा mutex xfer_lock;
	काष्ठा lp8727_psy *psy;
	काष्ठा lp8727_platक्रमm_data *pdata;

	/* Charger Data */
	क्रमागत lp8727_dev_id devid;
	काष्ठा lp8727_chg_param *chg_param;

	/* Interrupt Handling */
	पूर्णांक irq;
	काष्ठा delayed_work work;
	अचिन्हित दीर्घ debounce_jअगरfies;
पूर्ण;

अटल पूर्णांक lp8727_पढ़ो_bytes(काष्ठा lp8727_chg *pchg, u8 reg, u8 *data, u8 len)
अणु
	s32 ret;

	mutex_lock(&pchg->xfer_lock);
	ret = i2c_smbus_पढ़ो_i2c_block_data(pchg->client, reg, len, data);
	mutex_unlock(&pchg->xfer_lock);

	वापस (ret != len) ? -EIO : 0;
पूर्ण

अटल अंतरभूत पूर्णांक lp8727_पढ़ो_byte(काष्ठा lp8727_chg *pchg, u8 reg, u8 *data)
अणु
	वापस lp8727_पढ़ो_bytes(pchg, reg, data, 1);
पूर्ण

अटल पूर्णांक lp8727_ग_लिखो_byte(काष्ठा lp8727_chg *pchg, u8 reg, u8 data)
अणु
	पूर्णांक ret;

	mutex_lock(&pchg->xfer_lock);
	ret = i2c_smbus_ग_लिखो_byte_data(pchg->client, reg, data);
	mutex_unlock(&pchg->xfer_lock);

	वापस ret;
पूर्ण

अटल bool lp8727_is_अक्षरger_attached(स्थिर अक्षर *name, पूर्णांक id)
अणु
	अगर (!म_भेद(name, "ac"))
		वापस id == LP8727_ID_TA || id == LP8727_ID_DEDICATED_CHG;
	अन्यथा अगर (!म_भेद(name, "usb"))
		वापस id == LP8727_ID_USB_CHG;

	वापस id >= LP8727_ID_TA && id <= LP8727_ID_USB_CHG;
पूर्ण

अटल पूर्णांक lp8727_init_device(काष्ठा lp8727_chg *pchg)
अणु
	u8 val;
	पूर्णांक ret;
	u8 पूर्णांकstat[LP8788_NUM_INTREGS];

	/* clear पूर्णांकerrupts */
	ret = lp8727_पढ़ो_bytes(pchg, LP8727_INT1, पूर्णांकstat, LP8788_NUM_INTREGS);
	अगर (ret)
		वापस ret;

	val = LP8727_ID200_EN | LP8727_ADC_EN | LP8727_CP_EN;
	ret = lp8727_ग_लिखो_byte(pchg, LP8727_CTRL1, val);
	अगर (ret)
		वापस ret;

	val = LP8727_INT_EN | LP8727_CHGDET_EN;
	वापस lp8727_ग_लिखो_byte(pchg, LP8727_CTRL2, val);
पूर्ण

अटल पूर्णांक lp8727_is_dedicated_अक्षरger(काष्ठा lp8727_chg *pchg)
अणु
	u8 val;

	lp8727_पढ़ो_byte(pchg, LP8727_STATUS1, &val);
	वापस val & LP8727_DCPORT;
पूर्ण

अटल पूर्णांक lp8727_is_usb_अक्षरger(काष्ठा lp8727_chg *pchg)
अणु
	u8 val;

	lp8727_पढ़ो_byte(pchg, LP8727_STATUS1, &val);
	वापस val & LP8727_CHPORT;
पूर्ण

अटल अंतरभूत व्योम lp8727_ctrl_चयन(काष्ठा lp8727_chg *pchg, u8 sw)
अणु
	lp8727_ग_लिखो_byte(pchg, LP8727_SWCTRL, sw);
पूर्ण

अटल व्योम lp8727_id_detection(काष्ठा lp8727_chg *pchg, u8 id, पूर्णांक vbusin)
अणु
	काष्ठा lp8727_platक्रमm_data *pdata = pchg->pdata;
	u8 devid = LP8727_ID_NONE;
	u8 swctrl = LP8727_SW_DM1_HiZ | LP8727_SW_DP2_HiZ;

	चयन (id) अणु
	हाल 0x5:
		devid = LP8727_ID_TA;
		pchg->chg_param = pdata ? pdata->ac : शून्य;
		अवरोध;
	हाल 0xB:
		अगर (lp8727_is_dedicated_अक्षरger(pchg)) अणु
			pchg->chg_param = pdata ? pdata->ac : शून्य;
			devid = LP8727_ID_DEDICATED_CHG;
		पूर्ण अन्यथा अगर (lp8727_is_usb_अक्षरger(pchg)) अणु
			pchg->chg_param = pdata ? pdata->usb : शून्य;
			devid = LP8727_ID_USB_CHG;
			swctrl = LP8727_SW_DM1_DM | LP8727_SW_DP2_DP;
		पूर्ण अन्यथा अगर (vbusin) अणु
			devid = LP8727_ID_USB_DS;
			swctrl = LP8727_SW_DM1_DM | LP8727_SW_DP2_DP;
		पूर्ण
		अवरोध;
	शेष:
		devid = LP8727_ID_NONE;
		pchg->chg_param = शून्य;
		अवरोध;
	पूर्ण

	pchg->devid = devid;
	lp8727_ctrl_चयन(pchg, swctrl);
पूर्ण

अटल व्योम lp8727_enable_chgdet(काष्ठा lp8727_chg *pchg)
अणु
	u8 val;

	lp8727_पढ़ो_byte(pchg, LP8727_CTRL2, &val);
	val |= LP8727_CHGDET_EN;
	lp8727_ग_लिखो_byte(pchg, LP8727_CTRL2, val);
पूर्ण

अटल व्योम lp8727_delayed_func(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा lp8727_chg *pchg = container_of(_work, काष्ठा lp8727_chg,
						work.work);
	u8 पूर्णांकstat[LP8788_NUM_INTREGS];
	u8 idno;
	u8 vbus;

	अगर (lp8727_पढ़ो_bytes(pchg, LP8727_INT1, पूर्णांकstat, LP8788_NUM_INTREGS)) अणु
		dev_err(pchg->dev, "can not read INT registers\n");
		वापस;
	पूर्ण

	idno = पूर्णांकstat[0] & LP8727_IDNO;
	vbus = पूर्णांकstat[0] & LP8727_VBUS;

	lp8727_id_detection(pchg, idno, vbus);
	lp8727_enable_chgdet(pchg);

	घातer_supply_changed(pchg->psy->ac);
	घातer_supply_changed(pchg->psy->usb);
	घातer_supply_changed(pchg->psy->batt);
पूर्ण

अटल irqवापस_t lp8727_isr_func(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा lp8727_chg *pchg = ptr;

	schedule_delayed_work(&pchg->work, pchg->debounce_jअगरfies);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lp8727_setup_irq(काष्ठा lp8727_chg *pchg)
अणु
	पूर्णांक ret;
	पूर्णांक irq = pchg->client->irq;
	अचिन्हित delay_msec = pchg->pdata ? pchg->pdata->debounce_msec :
						DEFAULT_DEBOUNCE_MSEC;

	INIT_DELAYED_WORK(&pchg->work, lp8727_delayed_func);

	अगर (irq <= 0) अणु
		dev_warn(pchg->dev, "invalid irq number: %d\n", irq);
		वापस 0;
	पूर्ण

	ret = request_thपढ़ोed_irq(irq,	शून्य, lp8727_isr_func,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"lp8727_irq", pchg);

	अगर (ret)
		वापस ret;

	pchg->irq = irq;
	pchg->debounce_jअगरfies = msecs_to_jअगरfies(delay_msec);

	वापस 0;
पूर्ण

अटल व्योम lp8727_release_irq(काष्ठा lp8727_chg *pchg)
अणु
	cancel_delayed_work_sync(&pchg->work);

	अगर (pchg->irq)
		मुक्त_irq(pchg->irq, pchg);
पूर्ण

अटल क्रमागत घातer_supply_property lp8727_अक्षरger_prop[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property lp8727_battery_prop[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल अक्षर *battery_supplied_to[] = अणु
	"main_batt",
पूर्ण;

अटल पूर्णांक lp8727_अक्षरger_get_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lp8727_chg *pchg = dev_get_drvdata(psy->dev.parent);

	अगर (psp != POWER_SUPPLY_PROP_ONLINE)
		वापस -EINVAL;

	val->पूर्णांकval = lp8727_is_अक्षरger_attached(psy->desc->name, pchg->devid);

	वापस 0;
पूर्ण

अटल bool lp8727_is_high_temperature(क्रमागत lp8727_die_temp temp)
अणु
	चयन (temp) अणु
	हाल LP8788_TEMP_95C:
	हाल LP8788_TEMP_115C:
	हाल LP8788_TEMP_135C:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक lp8727_battery_get_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lp8727_chg *pchg = dev_get_drvdata(psy->dev.parent);
	काष्ठा lp8727_platक्रमm_data *pdata = pchg->pdata;
	क्रमागत lp8727_die_temp temp;
	u8 पढ़ो;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!lp8727_is_अक्षरger_attached(psy->desc->name, pchg->devid)) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
			वापस 0;
		पूर्ण

		lp8727_पढ़ो_byte(pchg, LP8727_STATUS1, &पढ़ो);

		val->पूर्णांकval = (पढ़ो & LP8727_CHGSTAT) == LP8727_STAT_EOC ?
				POWER_SUPPLY_STATUS_FULL :
				POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		lp8727_पढ़ो_byte(pchg, LP8727_STATUS2, &पढ़ो);
		temp = (पढ़ो & LP8727_TEMP_STAT) >> LP8727_TEMP_SHIFT;

		val->पूर्णांकval = lp8727_is_high_temperature(temp) ?
			POWER_SUPPLY_HEALTH_OVERHEAT :
			POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		अगर (!pdata)
			वापस -EINVAL;

		अगर (pdata->get_batt_present)
			val->पूर्णांकval = pdata->get_batt_present();
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (!pdata)
			वापस -EINVAL;

		अगर (pdata->get_batt_level)
			val->पूर्णांकval = pdata->get_batt_level();
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		अगर (!pdata)
			वापस -EINVAL;

		अगर (pdata->get_batt_capacity)
			val->पूर्णांकval = pdata->get_batt_capacity();
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		अगर (!pdata)
			वापस -EINVAL;

		अगर (pdata->get_batt_temp)
			val->पूर्णांकval = pdata->get_batt_temp();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lp8727_अक्षरger_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा lp8727_chg *pchg = dev_get_drvdata(psy->dev.parent);
	u8 eoc_level;
	u8 ichg;
	u8 val;

	/* skip अगर no अक्षरger exists */
	अगर (!lp8727_is_अक्षरger_attached(psy->desc->name, pchg->devid))
		वापस;

	/* update अक्षरging parameters */
	अगर (pchg->chg_param) अणु
		eoc_level = pchg->chg_param->eoc_level;
		ichg = pchg->chg_param->ichg;
		val = (ichg << LP8727_ICHG_SHIFT) | eoc_level;
		lp8727_ग_लिखो_byte(pchg, LP8727_CHGCTRL2, val);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc lp8727_ac_desc = अणु
	.name			= "ac",
	.type			= POWER_SUPPLY_TYPE_MAINS,
	.properties		= lp8727_अक्षरger_prop,
	.num_properties		= ARRAY_SIZE(lp8727_अक्षरger_prop),
	.get_property		= lp8727_अक्षरger_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc lp8727_usb_desc = अणु
	.name			= "usb",
	.type			= POWER_SUPPLY_TYPE_USB,
	.properties		= lp8727_अक्षरger_prop,
	.num_properties		= ARRAY_SIZE(lp8727_अक्षरger_prop),
	.get_property		= lp8727_अक्षरger_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc lp8727_batt_desc = अणु
	.name			= "main_batt",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= lp8727_battery_prop,
	.num_properties		= ARRAY_SIZE(lp8727_battery_prop),
	.get_property		= lp8727_battery_get_property,
	.बाह्यal_घातer_changed	= lp8727_अक्षरger_changed,
पूर्ण;

अटल पूर्णांक lp8727_रेजिस्टर_psy(काष्ठा lp8727_chg *pchg)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण; /* Only क्रम ac and usb */
	काष्ठा lp8727_psy *psy;

	psy = devm_kzalloc(pchg->dev, माप(*psy), GFP_KERNEL);
	अगर (!psy)
		वापस -ENOMEM;

	pchg->psy = psy;

	psy_cfg.supplied_to = battery_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(battery_supplied_to);

	psy->ac = घातer_supply_रेजिस्टर(pchg->dev, &lp8727_ac_desc, &psy_cfg);
	अगर (IS_ERR(psy->ac))
		जाओ err_psy_ac;

	psy->usb = घातer_supply_रेजिस्टर(pchg->dev, &lp8727_usb_desc,
					 &psy_cfg);
	अगर (IS_ERR(psy->usb))
		जाओ err_psy_usb;

	psy->batt = घातer_supply_रेजिस्टर(pchg->dev, &lp8727_batt_desc, शून्य);
	अगर (IS_ERR(psy->batt))
		जाओ err_psy_batt;

	वापस 0;

err_psy_batt:
	घातer_supply_unरेजिस्टर(psy->usb);
err_psy_usb:
	घातer_supply_unरेजिस्टर(psy->ac);
err_psy_ac:
	वापस -EPERM;
पूर्ण

अटल व्योम lp8727_unरेजिस्टर_psy(काष्ठा lp8727_chg *pchg)
अणु
	काष्ठा lp8727_psy *psy = pchg->psy;

	अगर (!psy)
		वापस;

	घातer_supply_unरेजिस्टर(psy->ac);
	घातer_supply_unरेजिस्टर(psy->usb);
	घातer_supply_unरेजिस्टर(psy->batt);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा lp8727_chg_param
*lp8727_parse_अक्षरge_pdata(काष्ठा device *dev, काष्ठा device_node *np)
अणु
	काष्ठा lp8727_chg_param *param;

	param = devm_kzalloc(dev, माप(*param), GFP_KERNEL);
	अगर (!param)
		जाओ out;

	of_property_पढ़ो_u8(np, "eoc-level", (u8 *)&param->eoc_level);
	of_property_पढ़ो_u8(np, "charging-current", (u8 *)&param->ichg);
out:
	वापस param;
पूर्ण

अटल काष्ठा lp8727_platक्रमm_data *lp8727_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	काष्ठा lp8727_platक्रमm_data *pdata;
	स्थिर अक्षर *type;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	of_property_पढ़ो_u32(np, "debounce-ms", &pdata->debounce_msec);

	/* If अक्षरging parameter is not defined, just skip parsing the dt */
	अगर (of_get_child_count(np) == 0)
		वापस pdata;

	क्रम_each_child_of_node(np, child) अणु
		of_property_पढ़ो_string(child, "charger-type", &type);

		अगर (!म_भेद(type, "ac"))
			pdata->ac = lp8727_parse_अक्षरge_pdata(dev, child);

		अगर (!म_भेद(type, "usb"))
			pdata->usb = lp8727_parse_अक्षरge_pdata(dev, child);
	पूर्ण

	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा lp8727_platक्रमm_data *lp8727_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lp8727_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lp8727_chg *pchg;
	काष्ठा lp8727_platक्रमm_data *pdata;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(cl->adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -EIO;

	अगर (cl->dev.of_node) अणु
		pdata = lp8727_parse_dt(&cl->dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण अन्यथा अणु
		pdata = dev_get_platdata(&cl->dev);
	पूर्ण

	pchg = devm_kzalloc(&cl->dev, माप(*pchg), GFP_KERNEL);
	अगर (!pchg)
		वापस -ENOMEM;

	pchg->client = cl;
	pchg->dev = &cl->dev;
	pchg->pdata = pdata;
	i2c_set_clientdata(cl, pchg);

	mutex_init(&pchg->xfer_lock);

	ret = lp8727_init_device(pchg);
	अगर (ret) अणु
		dev_err(pchg->dev, "i2c communication err: %d", ret);
		वापस ret;
	पूर्ण

	ret = lp8727_रेजिस्टर_psy(pchg);
	अगर (ret) अणु
		dev_err(pchg->dev, "power supplies register err: %d", ret);
		वापस ret;
	पूर्ण

	ret = lp8727_setup_irq(pchg);
	अगर (ret) अणु
		dev_err(pchg->dev, "irq handler err: %d", ret);
		lp8727_unरेजिस्टर_psy(pchg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8727_हटाओ(काष्ठा i2c_client *cl)
अणु
	काष्ठा lp8727_chg *pchg = i2c_get_clientdata(cl);

	lp8727_release_irq(pchg);
	lp8727_unरेजिस्टर_psy(pchg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lp8727_dt_ids[] = अणु
	अणु .compatible = "ti,lp8727", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lp8727_dt_ids);

अटल स्थिर काष्ठा i2c_device_id lp8727_ids[] = अणु
	अणु"lp8727", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp8727_ids);

अटल काष्ठा i2c_driver lp8727_driver = अणु
	.driver = अणु
		   .name = "lp8727",
		   .of_match_table = of_match_ptr(lp8727_dt_ids),
		   पूर्ण,
	.probe = lp8727_probe,
	.हटाओ = lp8727_हटाओ,
	.id_table = lp8727_ids,
पूर्ण;
module_i2c_driver(lp8727_driver);

MODULE_DESCRIPTION("TI/National Semiconductor LP8727 charger driver");
MODULE_AUTHOR("Milo Kim <milo.kim@ti.com>, Daniel Jeong <daniel.jeong@ti.com>");
MODULE_LICENSE("GPL");
