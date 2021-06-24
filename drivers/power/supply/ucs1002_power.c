<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम UCS1002 Programmable USB Port Power Controller
 *
 * Copyright (C) 2019 Zodiac Inflight Innovations
 */
#समावेश <linux/bits.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

/* UCS1002 Registers */
#घोषणा UCS1002_REG_CURRENT_MEASUREMENT	0x00

/*
 * The Total Accumulated Charge रेजिस्टरs store the total accumulated
 * अक्षरge delivered from the VS source to a portable device. The total
 * value is calculated using four रेजिस्टरs, from 01h to 04h. The bit
 * weighting of the रेजिस्टरs is given in mA/hrs.
 */
#घोषणा UCS1002_REG_TOTAL_ACC_CHARGE	0x01

/* Other Status Register */
#घोषणा UCS1002_REG_OTHER_STATUS	0x0f
#  define F_ADET_PIN			BIT(4)
#  define F_CHG_ACT			BIT(3)

/* Interrupt Status */
#घोषणा UCS1002_REG_INTERRUPT_STATUS	0x10
#  define F_ERR				BIT(7)
#  define F_DISCHARGE_ERR		BIT(6)
#  define F_RESET			BIT(5)
#  define F_MIN_KEEP_OUT		BIT(4)
#  define F_TSD				BIT(3)
#  define F_OVER_VOLT			BIT(2)
#  define F_BACK_VOLT			BIT(1)
#  define F_OVER_ILIM			BIT(0)

/* Pin Status Register */
#घोषणा UCS1002_REG_PIN_STATUS		0x14
#  define UCS1002_PWR_STATE_MASK	0x03
#  define F_PWR_EN_PIN			BIT(6)
#  define F_M2_PIN			BIT(5)
#  define F_M1_PIN			BIT(4)
#  define F_EM_EN_PIN			BIT(3)
#  define F_SEL_PIN			BIT(2)
#  define F_ACTIVE_MODE_MASK		GENMASK(5, 3)
#  define F_ACTIVE_MODE_PASSTHROUGH	F_M2_PIN
#  define F_ACTIVE_MODE_DEDICATED	F_EM_EN_PIN
#  define F_ACTIVE_MODE_BC12_DCP	(F_M2_PIN | F_EM_EN_PIN)
#  define F_ACTIVE_MODE_BC12_SDP	F_M1_PIN
#  define F_ACTIVE_MODE_BC12_CDP	(F_M1_PIN | F_M2_PIN | F_EM_EN_PIN)

/* General Configuration Register */
#घोषणा UCS1002_REG_GENERAL_CFG		0x15
#  define F_RATION_EN			BIT(3)

/* Emulation Configuration Register */
#घोषणा UCS1002_REG_EMU_CFG		0x16

/* Switch Configuration Register */
#घोषणा UCS1002_REG_SWITCH_CFG		0x17
#  define F_PIN_IGNORE			BIT(7)
#  define F_EM_EN_SET			BIT(5)
#  define F_M2_SET			BIT(4)
#  define F_M1_SET			BIT(3)
#  define F_S0_SET			BIT(2)
#  define F_PWR_EN_SET			BIT(1)
#  define F_LATCH_SET			BIT(0)
#  define V_SET_ACTIVE_MODE_MASK	GENMASK(5, 3)
#  define V_SET_ACTIVE_MODE_PASSTHROUGH	F_M2_SET
#  define V_SET_ACTIVE_MODE_DEDICATED	F_EM_EN_SET
#  define V_SET_ACTIVE_MODE_BC12_DCP	(F_M2_SET | F_EM_EN_SET)
#  define V_SET_ACTIVE_MODE_BC12_SDP	F_M1_SET
#  define V_SET_ACTIVE_MODE_BC12_CDP	(F_M1_SET | F_M2_SET | F_EM_EN_SET)

/* Current Limit Register */
#घोषणा UCS1002_REG_ILIMIT		0x19
#  define UCS1002_ILIM_SW_MASK		GENMASK(3, 0)

/* Product ID */
#घोषणा UCS1002_REG_PRODUCT_ID		0xfd
#  define UCS1002_PRODUCT_ID		0x4e

/* Manufacture name */
#घोषणा UCS1002_MANUFACTURER		"SMSC"

काष्ठा ucs1002_info अणु
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा regulator_desc *regulator_descriptor;
	काष्ठा regulator_dev *rdev;
	bool present;
	bool output_disable;
	काष्ठा delayed_work health_poll;
	पूर्णांक health;

पूर्ण;

अटल क्रमागत घातer_supply_property ucs1002_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_PRESENT, /* the presence of PED */
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
पूर्ण;

अटल पूर्णांक ucs1002_get_online(काष्ठा ucs1002_info *info,
			      जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_OTHER_STATUS, &reg);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = !!(reg & F_CHG_ACT);

	वापस 0;
पूर्ण

अटल पूर्णांक ucs1002_get_अक्षरge(काष्ठा ucs1002_info *info,
			      जोड़ घातer_supply_propval *val)
अणु
	/*
	 * To fit within 32 bits some values are rounded (uA/h)
	 *
	 * For Total Accumulated Charge Middle Low Byte रेजिस्टर, addr
	 * 03h, byte 2
	 *
	 *   B0: 0.01084 mA/h rounded to 11 uA/h
	 *   B1: 0.02169 mA/h rounded to 22 uA/h
	 *   B2: 0.04340 mA/h rounded to 43 uA/h
	 *   B3: 0.08676 mA/h rounded to 87 uA/h
	 *   B4: 0.17350 mA/h rounded to 173 uथ/h
	 *
	 * For Total Accumulated Charge Low Byte रेजिस्टर, addr 04h,
	 * byte 3
	 *
	 *   B6: 0.00271 mA/h rounded to 3 uA/h
	 *   B7: 0.005422 mA/h rounded to 5 uA/h
	 */
	अटल स्थिर पूर्णांक bit_weights_uAh[BITS_PER_TYPE(u32)] = अणु
		/*
		 * Bit corresponding to low byte (offset 0x04)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		0, 0, 0, 0, 0, 0, 3, 5,
		/*
		 * Bit corresponding to middle low byte (offset 0x03)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		11, 22, 43, 87, 173, 347, 694, 1388,
		/*
		 * Bit corresponding to middle high byte (offset 0x02)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		2776, 5552, 11105, 22210, 44420, 88840, 177700, 355400,
		/*
		 * Bit corresponding to high byte (offset 0x01)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		710700, 1421000, 2843000, 5685000, 11371000, 22742000,
		45484000, 90968000,
	पूर्ण;
	अचिन्हित दीर्घ total_acc_अक्षरger;
	अचिन्हित पूर्णांक reg;
	पूर्णांक i, ret;

	ret = regmap_bulk_पढ़ो(info->regmap, UCS1002_REG_TOTAL_ACC_CHARGE,
			       &reg, माप(u32));
	अगर (ret)
		वापस ret;

	total_acc_अक्षरger = be32_to_cpu(reg); /* BE as per offsets above */
	val->पूर्णांकval = 0;

	क्रम_each_set_bit(i, &total_acc_अक्षरger, ARRAY_SIZE(bit_weights_uAh))
		val->पूर्णांकval += bit_weights_uAh[i];

	वापस 0;
पूर्ण

अटल पूर्णांक ucs1002_get_current(काष्ठा ucs1002_info *info,
			       जोड़ घातer_supply_propval *val)
अणु
	/*
	 * The Current Measurement रेजिस्टर stores the measured
	 * current value delivered to the portable device. The range
	 * is from 9.76 mA to 2.5 A.
	 */
	अटल स्थिर पूर्णांक bit_weights_uA[BITS_PER_TYPE(u8)] = अणु
		9760, 19500, 39000, 78100, 156200, 312300, 624600, 1249300,
	पूर्ण;
	अचिन्हित दीर्घ current_measurement;
	अचिन्हित पूर्णांक reg;
	पूर्णांक i, ret;

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_CURRENT_MEASUREMENT, &reg);
	अगर (ret)
		वापस ret;

	current_measurement = reg;
	val->पूर्णांकval = 0;

	क्रम_each_set_bit(i, &current_measurement, ARRAY_SIZE(bit_weights_uA))
		val->पूर्णांकval += bit_weights_uA[i];

	वापस 0;
पूर्ण

/*
 * The Current Limit रेजिस्टर stores the maximum current used by the
 * port चयन. The range is from 500mA to 2.5 A.
 */
अटल स्थिर u32 ucs1002_current_limit_uA[] = अणु
	500000, 900000, 1000000, 1200000, 1500000, 1800000, 2000000, 2500000,
पूर्ण;

अटल पूर्णांक ucs1002_get_max_current(काष्ठा ucs1002_info *info,
				   जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	अगर (info->output_disable) अणु
		val->पूर्णांकval = 0;
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_ILIMIT, &reg);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = ucs1002_current_limit_uA[reg & UCS1002_ILIM_SW_MASK];

	वापस 0;
पूर्ण

अटल पूर्णांक ucs1002_set_max_current(काष्ठा ucs1002_info *info, u32 val)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret, idx;

	अगर (val == 0) अणु
		info->output_disable = true;
		regulator_disable_regmap(info->rdev);
		वापस 0;
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(ucs1002_current_limit_uA); idx++) अणु
		अगर (val == ucs1002_current_limit_uA[idx])
			अवरोध;
	पूर्ण

	अगर (idx == ARRAY_SIZE(ucs1002_current_limit_uA))
		वापस -EINVAL;

	ret = regmap_ग_लिखो(info->regmap, UCS1002_REG_ILIMIT, idx);
	अगर (ret)
		वापस ret;
	/*
	 * Any current limit setting exceeding the one set via ILIM
	 * pin will be rejected, so we पढ़ो out freshly changed limit
	 * to make sure that it took effect.
	 */
	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_ILIMIT, &reg);
	अगर (ret)
		वापस ret;

	अगर (reg != idx)
		वापस -EINVAL;

	info->output_disable = false;

	अगर (info->rdev && info->rdev->use_count &&
	    !regulator_is_enabled_regmap(info->rdev))
		regulator_enable_regmap(info->rdev);

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_usb_type ucs1002_usb_types[] = अणु
	POWER_SUPPLY_USB_TYPE_PD,
	POWER_SUPPLY_USB_TYPE_SDP,
	POWER_SUPPLY_USB_TYPE_DCP,
	POWER_SUPPLY_USB_TYPE_CDP,
	POWER_SUPPLY_USB_TYPE_UNKNOWN,
पूर्ण;

अटल पूर्णांक ucs1002_set_usb_type(काष्ठा ucs1002_info *info, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक mode;

	अगर (val < 0 || val >= ARRAY_SIZE(ucs1002_usb_types))
		वापस -EINVAL;

	चयन (ucs1002_usb_types[val]) अणु
	हाल POWER_SUPPLY_USB_TYPE_PD:
		mode = V_SET_ACTIVE_MODE_DEDICATED;
		अवरोध;
	हाल POWER_SUPPLY_USB_TYPE_SDP:
		mode = V_SET_ACTIVE_MODE_BC12_SDP;
		अवरोध;
	हाल POWER_SUPPLY_USB_TYPE_DCP:
		mode = V_SET_ACTIVE_MODE_BC12_DCP;
		अवरोध;
	हाल POWER_SUPPLY_USB_TYPE_CDP:
		mode = V_SET_ACTIVE_MODE_BC12_CDP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(info->regmap, UCS1002_REG_SWITCH_CFG,
				  V_SET_ACTIVE_MODE_MASK, mode);
पूर्ण

अटल पूर्णांक ucs1002_get_usb_type(काष्ठा ucs1002_info *info,
				जोड़ घातer_supply_propval *val)
अणु
	क्रमागत घातer_supply_usb_type type;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_PIN_STATUS, &reg);
	अगर (ret)
		वापस ret;

	चयन (reg & F_ACTIVE_MODE_MASK) अणु
	शेष:
		type = POWER_SUPPLY_USB_TYPE_UNKNOWN;
		अवरोध;
	हाल F_ACTIVE_MODE_DEDICATED:
		type = POWER_SUPPLY_USB_TYPE_PD;
		अवरोध;
	हाल F_ACTIVE_MODE_BC12_SDP:
		type = POWER_SUPPLY_USB_TYPE_SDP;
		अवरोध;
	हाल F_ACTIVE_MODE_BC12_DCP:
		type = POWER_SUPPLY_USB_TYPE_DCP;
		अवरोध;
	हाल F_ACTIVE_MODE_BC12_CDP:
		type = POWER_SUPPLY_USB_TYPE_CDP;
		अवरोध;
	पूर्ण

	val->पूर्णांकval = type;

	वापस 0;
पूर्ण

अटल पूर्णांक ucs1002_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ucs1002_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		वापस ucs1002_get_online(info, val);
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		वापस ucs1002_get_अक्षरge(info, val);
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		वापस ucs1002_get_current(info, val);
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		वापस ucs1002_get_max_current(info, val);
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		वापस ucs1002_get_usb_type(info, val);
	हाल POWER_SUPPLY_PROP_HEALTH:
		वापस val->पूर्णांकval = info->health;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = info->present;
		वापस 0;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = UCS1002_MANUFACTURER;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ucs1002_set_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ucs1002_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		वापस ucs1002_set_max_current(info, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		वापस ucs1002_set_usb_type(info, val->पूर्णांकval);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ucs1002_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc ucs1002_अक्षरger_desc = अणु
	.name			= "ucs1002",
	.type			= POWER_SUPPLY_TYPE_USB,
	.usb_types		= ucs1002_usb_types,
	.num_usb_types		= ARRAY_SIZE(ucs1002_usb_types),
	.get_property		= ucs1002_get_property,
	.set_property		= ucs1002_set_property,
	.property_is_ग_लिखोable	= ucs1002_property_is_ग_लिखोable,
	.properties		= ucs1002_props,
	.num_properties		= ARRAY_SIZE(ucs1002_props),
पूर्ण;

अटल व्योम ucs1002_health_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ucs1002_info *info = container_of(work, काष्ठा ucs1002_info,
						 health_poll.work);
	पूर्णांक ret;
	u32 reg;

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_INTERRUPT_STATUS, &reg);
	अगर (ret)
		वापस;

	/* bad health and no status change, just schedule us again in a जबतक */
	अगर ((reg & F_ERR) && info->health != POWER_SUPPLY_HEALTH_GOOD) अणु
		schedule_delayed_work(&info->health_poll,
				      msecs_to_jअगरfies(2000));
		वापस;
	पूर्ण

	अगर (reg & F_TSD)
		info->health = POWER_SUPPLY_HEALTH_OVERHEAT;
	अन्यथा अगर (reg & (F_OVER_VOLT | F_BACK_VOLT))
		info->health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	अन्यथा अगर (reg & F_OVER_ILIM)
		info->health = POWER_SUPPLY_HEALTH_OVERCURRENT;
	अन्यथा अगर (reg & (F_DISCHARGE_ERR | F_MIN_KEEP_OUT))
		info->health = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
	अन्यथा
		info->health = POWER_SUPPLY_HEALTH_GOOD;

	sysfs_notअगरy(&info->अक्षरger->dev.kobj, शून्य, "health");
पूर्ण

अटल irqवापस_t ucs1002_अक्षरger_irq(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक ret, regval;
	bool present;
	काष्ठा ucs1002_info *info = data;

	present = info->present;

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_OTHER_STATUS, &regval);
	अगर (ret)
		वापस IRQ_HANDLED;

	/* update attached status */
	info->present = regval & F_ADET_PIN;

	/* notअगरy the change */
	अगर (present != info->present)
		घातer_supply_changed(info->अक्षरger);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ucs1002_alert_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ucs1002_info *info = data;

	mod_delayed_work(प्रणाली_wq, &info->health_poll, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ucs1002_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा ucs1002_info *info = rdev_get_drvdata(rdev);

	/*
	 * If the output is disabled due to 0 maximum current, just pretend the
	 * enable did work. The regulator will be enabled as soon as we get a
	 * a non-zero maximum current budget.
	 */
	अगर (info->output_disable)
		वापस 0;

	वापस regulator_enable_regmap(rdev);
पूर्ण

अटल स्थिर काष्ठा regulator_ops ucs1002_regulator_ops = अणु
	.is_enabled	= regulator_is_enabled_regmap,
	.enable		= ucs1002_regulator_enable,
	.disable	= regulator_disable_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc ucs1002_regulator_descriptor = अणु
	.name		= "ucs1002-vbus",
	.ops		= &ucs1002_regulator_ops,
	.type		= REGULATOR_VOLTAGE,
	.owner		= THIS_MODULE,
	.enable_reg	= UCS1002_REG_SWITCH_CFG,
	.enable_mask	= F_PWR_EN_SET,
	.enable_val	= F_PWR_EN_SET,
	.fixed_uV	= 5000000,
	.n_voltages	= 1,
पूर्ण;

अटल पूर्णांक ucs1002_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *dev_id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा घातer_supply_config अक्षरger_config = अणुपूर्ण;
	स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;
	काष्ठा regulator_config regulator_config = अणुपूर्ण;
	पूर्णांक irq_a_det, irq_alert, ret;
	काष्ठा ucs1002_info *info;
	अचिन्हित पूर्णांक regval;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->regmap = devm_regmap_init_i2c(client, &regmap_config);
	ret = PTR_ERR_OR_ZERO(info->regmap);
	अगर (ret) अणु
		dev_err(dev, "Regmap initialization failed: %d\n", ret);
		वापस ret;
	पूर्ण

	info->client = client;

	irq_a_det = of_irq_get_byname(dev->of_node, "a_det");
	irq_alert = of_irq_get_byname(dev->of_node, "alert");

	अक्षरger_config.of_node = dev->of_node;
	अक्षरger_config.drv_data = info;

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_PRODUCT_ID, &regval);
	अगर (ret) अणु
		dev_err(dev, "Failed to read product ID: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (regval != UCS1002_PRODUCT_ID) अणु
		dev_err(dev,
			"Product ID does not match (0x%02x != 0x%02x)\n",
			regval, UCS1002_PRODUCT_ID);
		वापस -ENODEV;
	पूर्ण

	/* Enable अक्षरge rationing by शेष */
	ret = regmap_update_bits(info->regmap, UCS1002_REG_GENERAL_CFG,
				 F_RATION_EN, F_RATION_EN);
	अगर (ret) अणु
		dev_err(dev, "Failed to read general config: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Ignore the M1, M2, PWR_EN, and EM_EN pin states. Set active
	 * mode selection to BC1.2 CDP.
	 */
	ret = regmap_update_bits(info->regmap, UCS1002_REG_SWITCH_CFG,
				 V_SET_ACTIVE_MODE_MASK | F_PIN_IGNORE,
				 V_SET_ACTIVE_MODE_BC12_CDP | F_PIN_IGNORE);
	अगर (ret) अणु
		dev_err(dev, "Failed to configure default mode: %d\n", ret);
		वापस ret;
	पूर्ण
	/*
	 * Be safe and set initial current limit to 500mA
	 */
	ret = ucs1002_set_max_current(info, 500000);
	अगर (ret) अणु
		dev_err(dev, "Failed to set max current default: %d\n", ret);
		वापस ret;
	पूर्ण

	info->अक्षरger = devm_घातer_supply_रेजिस्टर(dev, &ucs1002_अक्षरger_desc,
						   &अक्षरger_config);
	ret = PTR_ERR_OR_ZERO(info->अक्षरger);
	अगर (ret) अणु
		dev_err(dev, "Failed to register power supply: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, UCS1002_REG_PIN_STATUS, &regval);
	अगर (ret) अणु
		dev_err(dev, "Failed to read pin status: %d\n", ret);
		वापस ret;
	पूर्ण

	info->regulator_descriptor =
		devm_kmemdup(dev, &ucs1002_regulator_descriptor,
			     माप(ucs1002_regulator_descriptor),
			     GFP_KERNEL);
	अगर (!info->regulator_descriptor)
		वापस -ENOMEM;

	info->regulator_descriptor->enable_is_inverted = !(regval & F_SEL_PIN);

	regulator_config.dev = dev;
	regulator_config.of_node = dev->of_node;
	regulator_config.regmap = info->regmap;
	regulator_config.driver_data = info;

	info->rdev = devm_regulator_रेजिस्टर(dev, info->regulator_descriptor,
				       &regulator_config);
	ret = PTR_ERR_OR_ZERO(info->rdev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register VBUS regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	info->health = POWER_SUPPLY_HEALTH_GOOD;
	INIT_DELAYED_WORK(&info->health_poll, ucs1002_health_poll);

	अगर (irq_a_det > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, irq_a_det, शून्य,
						ucs1002_अक्षरger_irq,
						IRQF_ONESHOT,
						"ucs1002-a_det", info);
		अगर (ret) अणु
			dev_err(dev, "Failed to request A_DET threaded irq: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (irq_alert > 0) अणु
		ret = devm_request_irq(dev, irq_alert, ucs1002_alert_irq,
				       0,"ucs1002-alert", info);
		अगर (ret) अणु
			dev_err(dev, "Failed to request ALERT threaded irq: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ucs1002_of_match[] = अणु
	अणु .compatible = "microchip,ucs1002", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ucs1002_of_match);

अटल काष्ठा i2c_driver ucs1002_driver = अणु
	.driver = अणु
		   .name = "ucs1002",
		   .of_match_table = ucs1002_of_match,
	पूर्ण,
	.probe = ucs1002_probe,
पूर्ण;
module_i2c_driver(ucs1002_driver);

MODULE_DESCRIPTION("Microchip UCS1002 Programmable USB Port Power Controller");
MODULE_AUTHOR("Enric Balletbo Serra <enric.balletbo@collabora.com>");
MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_LICENSE("GPL");
