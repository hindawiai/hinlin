<शैली गुरु>
/*
 * 1-Wire implementation क्रम Maxim Semiconductor
 * MAX7211/MAX17215 standalone fuel gauge chip
 *
 * Copyright (C) 2017 Radioavionica Corporation
 * Author: Alex A. Mihaylov <minimumlaw@rambler.ru>
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/w1.h>
#समावेश <linux/regmap.h>
#समावेश <linux/घातer_supply.h>

#घोषणा W1_MAX1721X_FAMILY_ID		0x26
#घोषणा DEF_DEV_NAME_MAX17211		"MAX17211"
#घोषणा DEF_DEV_NAME_MAX17215		"MAX17215"
#घोषणा DEF_DEV_NAME_UNKNOWN		"UNKNOWN"
#घोषणा DEF_MFG_NAME			"MAXIM"

#घोषणा PSY_MAX_NAME_LEN	32

/* Number of valid रेजिस्टर addresses in W1 mode */
#घोषणा MAX1721X_MAX_REG_NR	0x1EF

/* Factory settings (nonअस्थिर रेजिस्टरs) (W1 specअगरic) */
#घोषणा MAX1721X_REG_NRSENSE	0x1CF	/* RSense in 10^-5 Ohm */
/* Strings */
#घोषणा MAX1721X_REG_MFG_STR	0x1CC
#घोषणा MAX1721X_REG_MFG_NUMB	3
#घोषणा MAX1721X_REG_DEV_STR	0x1DB
#घोषणा MAX1721X_REG_DEV_NUMB	5
/* HEX Strings */
#घोषणा MAX1721X_REG_SER_HEX	0x1D8

/* MAX172XX Output Registers क्रम W1 chips */
#घोषणा MAX172XX_REG_STATUS	0x000	/* status reg */
#घोषणा MAX172XX_BAT_PRESENT	(1<<4)	/* battery connected bit */
#घोषणा MAX172XX_REG_DEVNAME	0x021	/* chip config */
#घोषणा MAX172XX_DEV_MASK	0x000F	/* chip type mask */
#घोषणा MAX172X1_DEV		0x0001
#घोषणा MAX172X5_DEV		0x0005
#घोषणा MAX172XX_REG_TEMP	0x008	/* Temperature */
#घोषणा MAX172XX_REG_BATT	0x0DA	/* Battery voltage */
#घोषणा MAX172XX_REG_CURRENT	0x00A	/* Actual current */
#घोषणा MAX172XX_REG_AVGCURRENT	0x00B	/* Average current */
#घोषणा MAX172XX_REG_REPSOC	0x006	/* Percentage of अक्षरge */
#घोषणा MAX172XX_REG_DESIGNCAP	0x018	/* Design capacity */
#घोषणा MAX172XX_REG_REPCAP	0x005	/* Average capacity */
#घोषणा MAX172XX_REG_TTE	0x011	/* Time to empty */
#घोषणा MAX172XX_REG_TTF	0x020	/* Time to full */

काष्ठा max17211_device_info अणु
	अक्षर name[PSY_MAX_NAME_LEN];
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा device *w1_dev;
	काष्ठा regmap *regmap;
	/* battery design क्रमmat */
	अचिन्हित पूर्णांक rsense; /* in tenths uOhm */
	अक्षर DeviceName[2 * MAX1721X_REG_DEV_NUMB + 1];
	अक्षर ManufacturerName[2 * MAX1721X_REG_MFG_NUMB + 1];
	अक्षर SerialNumber[13]; /* see get_sn_str() later क्रम comment */
पूर्ण;

/* Convert regs value to घातer_supply units */

अटल अंतरभूत पूर्णांक max172xx_समय_प्रकारo_ps(अचिन्हित पूर्णांक reg)
अणु
	वापस reg * 5625 / 1000;	/* in sec. */
पूर्ण

अटल अंतरभूत पूर्णांक max172xx_percent_to_ps(अचिन्हित पूर्णांक reg)
अणु
	वापस reg / 256;	/* in percent from 0 to 100 */
पूर्ण

अटल अंतरभूत पूर्णांक max172xx_voltage_to_ps(अचिन्हित पूर्णांक reg)
अणु
	वापस reg * 1250;	/* in uV */
पूर्ण

अटल अंतरभूत पूर्णांक max172xx_capacity_to_ps(अचिन्हित पूर्णांक reg)
अणु
	वापस reg * 500;	/* in uAh */
पूर्ण

/*
 * Current and temperature is चिन्हित values, so अचिन्हित regs
 * value must be converted to चिन्हित type
 */

अटल अंतरभूत पूर्णांक max172xx_temperature_to_ps(अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक val = (पूर्णांक16_t)(reg);

	वापस val * 10 / 256; /* in tenths of deg. C */
पूर्ण

/*
 * Calculating current रेजिस्टरs resolution:
 *
 * RSense stored in 10^-5 Ohm, so measurement voltage must be
 * in 10^-11 Volts क्रम get current in uA.
 * 16 bit current reg fullscale +/-51.2mV is 102400 uV.
 * So: 102400 / 65535 * 10^5 = 156252
 */
अटल अंतरभूत पूर्णांक max172xx_current_to_voltage(अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक val = (पूर्णांक16_t)(reg);

	वापस val * 156252;
पूर्ण


अटल अंतरभूत काष्ठा max17211_device_info *
to_device_info(काष्ठा घातer_supply *psy)
अणु
	वापस घातer_supply_get_drvdata(psy);
पूर्ण

अटल पूर्णांक max1721x_battery_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max17211_device_info *info = to_device_info(psy);
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		/*
		 * POWER_SUPPLY_PROP_PRESENT will always पढ़ोable via
		 * sysfs पूर्णांकerface. Value वापस 0 अगर battery not
		 * present or unaccessible via W1.
		 */
		val->पूर्णांकval =
			regmap_पढ़ो(info->regmap, MAX172XX_REG_STATUS,
			&reg) ? 0 : !(reg & MAX172XX_BAT_PRESENT);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_REPSOC, &reg);
		val->पूर्णांकval = max172xx_percent_to_ps(reg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_BATT, &reg);
		val->पूर्णांकval = max172xx_voltage_to_ps(reg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_DESIGNCAP, &reg);
		val->पूर्णांकval = max172xx_capacity_to_ps(reg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_AVG:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_REPCAP, &reg);
		val->पूर्णांकval = max172xx_capacity_to_ps(reg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_TTE, &reg);
		val->पूर्णांकval = max172xx_समय_प्रकारo_ps(reg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_FULL_AVG:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_TTF, &reg);
		val->पूर्णांकval = max172xx_समय_प्रकारo_ps(reg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_TEMP, &reg);
		val->पूर्णांकval = max172xx_temperature_to_ps(reg);
		अवरोध;
	/* We need चिन्हित current, so must cast info->rsense to चिन्हित type */
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_CURRENT, &reg);
		val->पूर्णांकval =
			max172xx_current_to_voltage(reg) / (पूर्णांक)info->rsense;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = regmap_पढ़ो(info->regmap, MAX172XX_REG_AVGCURRENT, &reg);
		val->पूर्णांकval =
			max172xx_current_to_voltage(reg) / (पूर्णांक)info->rsense;
		अवरोध;
	/*
	 * Strings alपढ़ोy received and inited by probe.
	 * We करो dummy पढ़ो क्रम check battery still available.
	 */
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		ret = regmap_पढ़ो(info->regmap, MAX1721X_REG_DEV_STR, &reg);
		val->strval = info->DeviceName;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		ret = regmap_पढ़ो(info->regmap, MAX1721X_REG_MFG_STR, &reg);
		val->strval = info->ManufacturerName;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		ret = regmap_पढ़ो(info->regmap, MAX1721X_REG_SER_HEX, &reg);
		val->strval = info->SerialNumber;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property max1721x_battery_props[] = अणु
	/* पूर्णांक */
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_AVG,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_AVG,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	/* strings */
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
पूर्ण;

अटल पूर्णांक get_string(काष्ठा max17211_device_info *info,
			uपूर्णांक16_t reg, uपूर्णांक8_t nr, अक्षर *str)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!str || !(reg == MAX1721X_REG_MFG_STR ||
			reg == MAX1721X_REG_DEV_STR))
		वापस -EFAULT;

	जबतक (nr--) अणु
		अगर (regmap_पढ़ो(info->regmap, reg++, &val))
			वापस -EFAULT;
		*str++ = val>>8 & 0x00FF;
		*str++ = val & 0x00FF;
	पूर्ण
	वापस 0;
पूर्ण

/* Maxim say: Serial number is a hex string up to 12 hex अक्षरacters */
अटल पूर्णांक get_sn_string(काष्ठा max17211_device_info *info, अक्षर *str)
अणु
	अचिन्हित पूर्णांक val[3];

	अगर (!str)
		वापस -EFAULT;

	अगर (regmap_पढ़ो(info->regmap, MAX1721X_REG_SER_HEX, &val[0]))
		वापस -EFAULT;
	अगर (regmap_पढ़ो(info->regmap, MAX1721X_REG_SER_HEX + 1, &val[1]))
		वापस -EFAULT;
	अगर (regmap_पढ़ो(info->regmap, MAX1721X_REG_SER_HEX + 2, &val[2]))
		वापस -EFAULT;

	snम_लिखो(str, 13, "%04X%04X%04X", val[0], val[1], val[2]);
	वापस 0;
पूर्ण

/*
 * MAX1721x रेजिस्टरs description क्रम w1-regmap
 */
अटल स्थिर काष्ठा regmap_range max1721x_allow_range[] = अणु
	regmap_reg_range(0, 0xDF),	/* अस्थिर data */
	regmap_reg_range(0x180, 0x1DF),	/* non-अस्थिर memory */
	regmap_reg_range(0x1E0, 0x1EF),	/* non-अस्थिर history (unused) */
पूर्ण;

अटल स्थिर काष्ठा regmap_range max1721x_deny_range[] = अणु
	/* अस्थिर data unused रेजिस्टरs */
	regmap_reg_range(0x24, 0x26),
	regmap_reg_range(0x30, 0x31),
	regmap_reg_range(0x33, 0x34),
	regmap_reg_range(0x37, 0x37),
	regmap_reg_range(0x3B, 0x3C),
	regmap_reg_range(0x40, 0x41),
	regmap_reg_range(0x43, 0x44),
	regmap_reg_range(0x47, 0x49),
	regmap_reg_range(0x4B, 0x4C),
	regmap_reg_range(0x4E, 0xAF),
	regmap_reg_range(0xB1, 0xB3),
	regmap_reg_range(0xB5, 0xB7),
	regmap_reg_range(0xBF, 0xD0),
	regmap_reg_range(0xDB, 0xDB),
	/* hole between अस्थिर and non-अस्थिर रेजिस्टरs */
	regmap_reg_range(0xE0, 0x17F),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max1721x_regs = अणु
	.yes_ranges	= max1721x_allow_range,
	.n_yes_ranges	= ARRAY_SIZE(max1721x_allow_range),
	.no_ranges	= max1721x_deny_range,
	.n_no_ranges	= ARRAY_SIZE(max1721x_deny_range),
पूर्ण;

/*
 * Model Gauge M5 Algorithm output रेजिस्टर
 * Volatile data (must not be cached)
 */
अटल स्थिर काष्ठा regmap_range max1721x_अस्थिर_allow[] = अणु
	regmap_reg_range(0, 0xDF),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max1721x_अस्थिर_regs = अणु
	.yes_ranges	= max1721x_अस्थिर_allow,
	.n_yes_ranges	= ARRAY_SIZE(max1721x_अस्थिर_allow),
पूर्ण;

/*
 * W1-regmap config
 */
अटल स्थिर काष्ठा regmap_config max1721x_regmap_w1_config = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.rd_table = &max1721x_regs,
	.अस्थिर_table = &max1721x_अस्थिर_regs,
	.max_रेजिस्टर = MAX1721X_MAX_REG_NR,
पूर्ण;

अटल पूर्णांक devm_w1_max1721x_add_device(काष्ठा w1_slave *sl)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा max17211_device_info *info;

	info = devm_kzalloc(&sl->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	sl->family_data = (व्योम *)info;
	info->w1_dev = &sl->dev;

	/*
	 * घातer_supply class battery name translated from W1 slave device
	 * unique ID (look like 26-0123456789AB) to "max1721x-0123456789AB\0"
	 * so, 26 (device family) correspond to max1721x devices.
	 * Device name still unique क्रम any number of connected devices.
	 */
	snम_लिखो(info->name, माप(info->name),
		"max1721x-%012X", (अचिन्हित पूर्णांक)sl->reg_num.id);
	info->bat_desc.name = info->name;

	/*
	 * FixMe: battery device name exceed max len क्रम thermal_zone device
	 * name and translation to thermal_zone must be disabled.
	 */
	info->bat_desc.no_thermal = true;
	info->bat_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	info->bat_desc.properties = max1721x_battery_props;
	info->bat_desc.num_properties = ARRAY_SIZE(max1721x_battery_props);
	info->bat_desc.get_property = max1721x_battery_get_property;
	psy_cfg.drv_data = info;

	/* regmap init */
	info->regmap = devm_regmap_init_w1(info->w1_dev,
					&max1721x_regmap_w1_config);
	अगर (IS_ERR(info->regmap)) अणु
		पूर्णांक err = PTR_ERR(info->regmap);

		dev_err(info->w1_dev, "Failed to allocate register map: %d\n",
			err);
		वापस err;
	पूर्ण

	/* rsense init */
	info->rsense = 0;
	अगर (regmap_पढ़ो(info->regmap, MAX1721X_REG_NRSENSE, &info->rsense)) अणु
		dev_err(info->w1_dev, "Can't read RSense. Hardware error.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!info->rsense) अणु
		dev_warn(info->w1_dev, "RSense not calibrated, set 10 mOhms!\n");
		info->rsense = 1000; /* in regs in 10^-5 */
	पूर्ण
	dev_info(info->w1_dev, "RSense: %d mOhms.\n", info->rsense / 100);

	अगर (get_string(info, MAX1721X_REG_MFG_STR,
			MAX1721X_REG_MFG_NUMB, info->ManufacturerName)) अणु
		dev_err(info->w1_dev, "Can't read manufacturer. Hardware error.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!info->ManufacturerName[0])
		म_नकलन(info->ManufacturerName, DEF_MFG_NAME,
			2 * MAX1721X_REG_MFG_NUMB);

	अगर (get_string(info, MAX1721X_REG_DEV_STR,
			MAX1721X_REG_DEV_NUMB, info->DeviceName)) अणु
		dev_err(info->w1_dev, "Can't read device. Hardware error.\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!info->DeviceName[0]) अणु
		अचिन्हित पूर्णांक dev_name;

		अगर (regmap_पढ़ो(info->regmap,
				MAX172XX_REG_DEVNAME, &dev_name)) अणु
			dev_err(info->w1_dev, "Can't read device name reg.\n");
			वापस -ENODEV;
		पूर्ण

		चयन (dev_name & MAX172XX_DEV_MASK) अणु
		हाल MAX172X1_DEV:
			म_नकलन(info->DeviceName, DEF_DEV_NAME_MAX17211,
				2 * MAX1721X_REG_DEV_NUMB);
			अवरोध;
		हाल MAX172X5_DEV:
			म_नकलन(info->DeviceName, DEF_DEV_NAME_MAX17215,
				2 * MAX1721X_REG_DEV_NUMB);
			अवरोध;
		शेष:
			म_नकलन(info->DeviceName, DEF_DEV_NAME_UNKNOWN,
				2 * MAX1721X_REG_DEV_NUMB);
		पूर्ण
	पूर्ण

	अगर (get_sn_string(info, info->SerialNumber)) अणु
		dev_err(info->w1_dev, "Can't read serial. Hardware error.\n");
		वापस -ENODEV;
	पूर्ण

	info->bat = devm_घातer_supply_रेजिस्टर(&sl->dev, &info->bat_desc,
						&psy_cfg);
	अगर (IS_ERR(info->bat)) अणु
		dev_err(info->w1_dev, "failed to register battery\n");
		वापस PTR_ERR(info->bat);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा w1_family_ops w1_max1721x_fops = अणु
	.add_slave = devm_w1_max1721x_add_device,
पूर्ण;

अटल काष्ठा w1_family w1_max1721x_family = अणु
	.fid = W1_MAX1721X_FAMILY_ID,
	.fops = &w1_max1721x_fops,
पूर्ण;

module_w1_family(w1_max1721x_family);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex A. Mihaylov <minimumlaw@rambler.ru>");
MODULE_DESCRIPTION("Maxim MAX17211/MAX17215 Fuel Gauage IC driver");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_MAX1721X_FAMILY_ID));
