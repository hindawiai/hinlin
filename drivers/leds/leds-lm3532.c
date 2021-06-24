<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// TI LM3532 LED driver
// Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com/
// https://www.ti.com/lit/ds/symlink/lm3532.pdf

#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>
#समावेश <uapi/linux/uleds.h>
#समावेश <linux/gpio/consumer.h>

#घोषणा LM3532_NAME "lm3532-led"
#घोषणा LM3532_BL_MODE_MANUAL	0x00
#घोषणा LM3532_BL_MODE_ALS	0x01

#घोषणा LM3532_REG_OUTPUT_CFG	0x10
#घोषणा LM3532_REG_STARTSHUT_RAMP	0x11
#घोषणा LM3532_REG_RT_RAMP	0x12
#घोषणा LM3532_REG_PWM_A_CFG	0x13
#घोषणा LM3532_REG_PWM_B_CFG	0x14
#घोषणा LM3532_REG_PWM_C_CFG	0x15
#घोषणा LM3532_REG_ZONE_CFG_A	0x16
#घोषणा LM3532_REG_CTRL_A_FS_CURR	0x17
#घोषणा LM3532_REG_ZONE_CFG_B	0x18
#घोषणा LM3532_REG_CTRL_B_FS_CURR	0x19
#घोषणा LM3532_REG_ZONE_CFG_C	0x1a
#घोषणा LM3532_REG_CTRL_C_FS_CURR	0x1b
#घोषणा LM3532_REG_ENABLE	0x1d
#घोषणा LM3532_ALS_CONFIG	0x23
#घोषणा LM3532_REG_ZN_0_HI	0x60
#घोषणा LM3532_REG_ZN_0_LO	0x61
#घोषणा LM3532_REG_ZN_1_HI	0x62
#घोषणा LM3532_REG_ZN_1_LO	0x63
#घोषणा LM3532_REG_ZN_2_HI	0x64
#घोषणा LM3532_REG_ZN_2_LO	0x65
#घोषणा LM3532_REG_ZN_3_HI	0x66
#घोषणा LM3532_REG_ZN_3_LO	0x67
#घोषणा LM3532_REG_ZONE_TRGT_A	0x70
#घोषणा LM3532_REG_ZONE_TRGT_B	0x75
#घोषणा LM3532_REG_ZONE_TRGT_C	0x7a
#घोषणा LM3532_REG_MAX		0x7e

/* Control Enable */
#घोषणा LM3532_CTRL_A_ENABLE	BIT(0)
#घोषणा LM3532_CTRL_B_ENABLE	BIT(1)
#घोषणा LM3532_CTRL_C_ENABLE	BIT(2)

/* PWM Zone Control */
#घोषणा LM3532_PWM_ZONE_MASK	0x7c
#घोषणा LM3532_PWM_ZONE_0_EN	BIT(2)
#घोषणा LM3532_PWM_ZONE_1_EN	BIT(3)
#घोषणा LM3532_PWM_ZONE_2_EN	BIT(4)
#घोषणा LM3532_PWM_ZONE_3_EN	BIT(5)
#घोषणा LM3532_PWM_ZONE_4_EN	BIT(6)

/* Brightness Configuration */
#घोषणा LM3532_I2C_CTRL		BIT(0)
#घोषणा LM3532_ALS_CTRL		0
#घोषणा LM3532_LINEAR_MAP	BIT(1)
#घोषणा LM3532_ZONE_MASK	(BIT(2) | BIT(3) | BIT(4))
#घोषणा LM3532_ZONE_0		0
#घोषणा LM3532_ZONE_1		BIT(2)
#घोषणा LM3532_ZONE_2		BIT(3)
#घोषणा LM3532_ZONE_3		(BIT(2) | BIT(3))
#घोषणा LM3532_ZONE_4		BIT(4)

#घोषणा LM3532_ENABLE_ALS	BIT(3)
#घोषणा LM3532_ALS_SEL_SHIFT	6

/* Zone Boundary Register */
#घोषणा LM3532_ALS_WINDOW_mV	2000
#घोषणा LM3532_ALS_ZB_MAX	4
#घोषणा LM3532_ALS_OFFSET_mV	2

#घोषणा LM3532_CONTROL_A	0
#घोषणा LM3532_CONTROL_B	1
#घोषणा LM3532_CONTROL_C	2
#घोषणा LM3532_MAX_CONTROL_BANKS 3
#घोषणा LM3532_MAX_LED_STRINGS	3

#घोषणा LM3532_OUTPUT_CFG_MASK	0x3
#घोषणा LM3532_BRT_VAL_ADJUST	8
#घोषणा LM3532_RAMP_DOWN_SHIFT	3

#घोषणा LM3532_NUM_RAMP_VALS	8
#घोषणा LM3532_NUM_AVG_VALS	8
#घोषणा LM3532_NUM_IMP_VALS	32

#घोषणा LM3532_FS_CURR_MIN	5000
#घोषणा LM3532_FS_CURR_MAX	29800
#घोषणा LM3532_FS_CURR_STEP	800

/*
 * काष्ठा lm3532_als_data
 * @config: value of ALS configuration रेजिस्टर
 * @als1_imp_sel: value of ALS1 resistor select रेजिस्टर
 * @als2_imp_sel: value of ALS2 resistor select रेजिस्टर
 * @als_avrg_समय: ALS averaging समय
 * @als_input_mode: ALS input mode क्रम brightness control
 * @als_vmin: Minimum ALS voltage
 * @als_vmax: Maximum ALS voltage
 * @zone_lo: values of ALS lo ZB(Zone Boundary) रेजिस्टरs
 * @zone_hi: values of ALS hi ZB(Zone Boundary) रेजिस्टरs
 */
काष्ठा lm3532_als_data अणु
	u8 config;
	u8 als1_imp_sel;
	u8 als2_imp_sel;
	u8 als_avrg_समय;
	u8 als_input_mode;
	u32 als_vmin;
	u32 als_vmax;
	u8 zones_lo[LM3532_ALS_ZB_MAX];
	u8 zones_hi[LM3532_ALS_ZB_MAX];
पूर्ण;

/**
 * काष्ठा lm3532_led
 * @led_dev: led class device
 * @priv: Poपूर्णांकer the device data काष्ठाure
 * @control_bank: Control bank the LED is associated to
 * @mode: Mode of the LED string
 * @ctrl_brt_poपूर्णांकer: Zone target रेजिस्टर that controls the sink
 * @num_leds: Number of LED strings are supported in this array
 * @full_scale_current: The full-scale current setting क्रम the current sink.
 * @led_strings: The LED strings supported in this array
 * @enabled: Enabled status
 */
काष्ठा lm3532_led अणु
	काष्ठा led_classdev led_dev;
	काष्ठा lm3532_data *priv;

	पूर्णांक control_bank;
	पूर्णांक mode;
	पूर्णांक ctrl_brt_poपूर्णांकer;
	पूर्णांक num_leds;
	पूर्णांक full_scale_current;
	अचिन्हित पूर्णांक enabled:1;
	u32 led_strings[LM3532_MAX_CONTROL_BANKS];
पूर्ण;

/**
 * काष्ठा lm3532_data
 * @enable_gpio: Hardware enable gpio
 * @regulator: regulator
 * @client: i2c client
 * @regmap: Devices रेजिस्टर map
 * @dev: Poपूर्णांकer to the devices device काष्ठा
 * @lock: Lock क्रम पढ़ोing/writing the device
 * @als_data: Poपूर्णांकer to the als data काष्ठा
 * @runसमय_ramp_up: Runसमय ramp up setting
 * @runसमय_ramp_करोwn: Runसमय ramp करोwn setting
 * @leds: Array of LED strings
 */
काष्ठा lm3532_data अणु
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *regulator;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा mutex lock;

	काष्ठा lm3532_als_data *als_data;

	u32 runसमय_ramp_up;
	u32 runसमय_ramp_करोwn;

	काष्ठा lm3532_led leds[];
पूर्ण;

अटल स्थिर काष्ठा reg_शेष lm3532_reg_defs[] = अणु
	अणुLM3532_REG_OUTPUT_CFG, 0xe4पूर्ण,
	अणुLM3532_REG_STARTSHUT_RAMP, 0xc0पूर्ण,
	अणुLM3532_REG_RT_RAMP, 0xc0पूर्ण,
	अणुLM3532_REG_PWM_A_CFG, 0x82पूर्ण,
	अणुLM3532_REG_PWM_B_CFG, 0x82पूर्ण,
	अणुLM3532_REG_PWM_C_CFG, 0x82पूर्ण,
	अणुLM3532_REG_ZONE_CFG_A, 0xf1पूर्ण,
	अणुLM3532_REG_CTRL_A_FS_CURR, 0xf3पूर्ण,
	अणुLM3532_REG_ZONE_CFG_B, 0xf1पूर्ण,
	अणुLM3532_REG_CTRL_B_FS_CURR, 0xf3पूर्ण,
	अणुLM3532_REG_ZONE_CFG_C, 0xf1पूर्ण,
	अणुLM3532_REG_CTRL_C_FS_CURR, 0xf3पूर्ण,
	अणुLM3532_REG_ENABLE, 0xf8पूर्ण,
	अणुLM3532_ALS_CONFIG, 0x44पूर्ण,
	अणुLM3532_REG_ZN_0_HI, 0x35पूर्ण,
	अणुLM3532_REG_ZN_0_LO, 0x33पूर्ण,
	अणुLM3532_REG_ZN_1_HI, 0x6aपूर्ण,
	अणुLM3532_REG_ZN_1_LO, 0x66पूर्ण,
	अणुLM3532_REG_ZN_2_HI, 0xa1पूर्ण,
	अणुLM3532_REG_ZN_2_LO, 0x99पूर्ण,
	अणुLM3532_REG_ZN_3_HI, 0xdcपूर्ण,
	अणुLM3532_REG_ZN_3_LO, 0xccपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lm3532_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LM3532_REG_MAX,
	.reg_शेषs = lm3532_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lm3532_reg_defs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर पूर्णांक als_imp_table[LM3532_NUM_IMP_VALS] = अणु37000, 18500, 12330,
						       92500, 7400, 6170, 5290,
						       4630, 4110, 3700, 3360,
						       3080, 2850, 2640, 2440,
						       2310, 2180, 2060, 1950,
						       1850, 1760, 1680, 1610,
						       1540, 1480, 1420, 1370,
						       1320, 1280, 1230, 1190पूर्ण;
अटल पूर्णांक lm3532_get_als_imp_index(पूर्णांक als_imped)
अणु
	पूर्णांक i;

	अगर (als_imped > als_imp_table[1])
		वापस 0;

	अगर (als_imped < als_imp_table[LM3532_NUM_IMP_VALS - 1])
		वापस LM3532_NUM_IMP_VALS - 1;

	क्रम (i = 1; i < LM3532_NUM_IMP_VALS; i++) अणु
		अगर (als_imped == als_imp_table[i])
			वापस i;

		/* Find an approximate index by looking up the table */
		अगर (als_imped < als_imp_table[i - 1] &&
		    als_imped > als_imp_table[i]) अणु
			अगर (als_imped - als_imp_table[i - 1] <
			    als_imp_table[i] - als_imped)
				वापस i + 1;
			अन्यथा
				वापस i;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक lm3532_get_index(स्थिर पूर्णांक table[], पूर्णांक size, पूर्णांक value)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < size; i++) अणु
		अगर (value == table[i])
			वापस i;

		/* Find an approximate index by looking up the table */
		अगर (value > table[i - 1] &&
		    value < table[i]) अणु
			अगर (value - table[i - 1] < table[i] - value)
				वापस i - 1;
			अन्यथा
				वापस i;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर पूर्णांक als_avrg_table[LM3532_NUM_AVG_VALS] = अणु17920, 35840, 71680,
							1433360, 286720, 573440,
							1146880, 2293760पूर्ण;
अटल पूर्णांक lm3532_get_als_avg_index(पूर्णांक avg_समय)
अणु
	अगर (avg_समय <= als_avrg_table[0])
		वापस 0;

	अगर (avg_समय > als_avrg_table[LM3532_NUM_AVG_VALS - 1])
		वापस LM3532_NUM_AVG_VALS - 1;

	वापस lm3532_get_index(&als_avrg_table[0], LM3532_NUM_AVG_VALS,
				avg_समय);
पूर्ण

अटल स्थिर पूर्णांक ramp_table[LM3532_NUM_RAMP_VALS] = अणु 8, 1024, 2048, 4096, 8192,
						     16384, 32768, 65536पूर्ण;
अटल पूर्णांक lm3532_get_ramp_index(पूर्णांक ramp_समय)
अणु
	अगर (ramp_समय <= ramp_table[0])
		वापस 0;

	अगर (ramp_समय > ramp_table[LM3532_NUM_RAMP_VALS - 1])
		वापस LM3532_NUM_RAMP_VALS - 1;

	वापस lm3532_get_index(&ramp_table[0], LM3532_NUM_RAMP_VALS,
				ramp_समय);
पूर्ण

/* Caller must take care of locking */
अटल पूर्णांक lm3532_led_enable(काष्ठा lm3532_led *led_data)
अणु
	पूर्णांक ctrl_en_val = BIT(led_data->control_bank);
	पूर्णांक ret;

	अगर (led_data->enabled)
		वापस 0;

	ret = regmap_update_bits(led_data->priv->regmap, LM3532_REG_ENABLE,
					 ctrl_en_val, ctrl_en_val);
	अगर (ret) अणु
		dev_err(led_data->priv->dev, "Failed to set ctrl:%d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_enable(led_data->priv->regulator);
	अगर (ret < 0)
		वापस ret;

	led_data->enabled = 1;

	वापस 0;
पूर्ण

/* Caller must take care of locking */
अटल पूर्णांक lm3532_led_disable(काष्ठा lm3532_led *led_data)
अणु
	पूर्णांक ctrl_en_val = BIT(led_data->control_bank);
	पूर्णांक ret;

	अगर (!led_data->enabled)
		वापस 0;

	ret = regmap_update_bits(led_data->priv->regmap, LM3532_REG_ENABLE,
					 ctrl_en_val, 0);
	अगर (ret) अणु
		dev_err(led_data->priv->dev, "Failed to set ctrl:%d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_disable(led_data->priv->regulator);
	अगर (ret < 0)
		वापस ret;

	led_data->enabled = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3532_brightness_set(काष्ठा led_classdev *led_cdev,
				 क्रमागत led_brightness brt_val)
अणु
	काष्ठा lm3532_led *led =
			container_of(led_cdev, काष्ठा lm3532_led, led_dev);
	u8 brightness_reg;
	पूर्णांक ret;

	mutex_lock(&led->priv->lock);

	अगर (led->mode == LM3532_ALS_CTRL) अणु
		अगर (brt_val > LED_OFF)
			ret = lm3532_led_enable(led);
		अन्यथा
			ret = lm3532_led_disable(led);

		जाओ unlock;
	पूर्ण

	अगर (brt_val == LED_OFF) अणु
		ret = lm3532_led_disable(led);
		जाओ unlock;
	पूर्ण

	ret = lm3532_led_enable(led);
	अगर (ret)
		जाओ unlock;

	brightness_reg = LM3532_REG_ZONE_TRGT_A + led->control_bank * 5 +
			 (led->ctrl_brt_poपूर्णांकer >> 2);

	ret = regmap_ग_लिखो(led->priv->regmap, brightness_reg, brt_val);

unlock:
	mutex_unlock(&led->priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lm3532_init_रेजिस्टरs(काष्ठा lm3532_led *led)
अणु
	काष्ठा lm3532_data *drvdata = led->priv;
	अचिन्हित पूर्णांक runसमय_ramp_val;
	अचिन्हित पूर्णांक output_cfg_val = 0;
	अचिन्हित पूर्णांक output_cfg_shअगरt = 0;
	अचिन्हित पूर्णांक output_cfg_mask = 0;
	अचिन्हित पूर्णांक brightness_config_reg;
	अचिन्हित पूर्णांक brightness_config_val;
	पूर्णांक fs_current_reg;
	पूर्णांक fs_current_val;
	पूर्णांक ret, i;

	अगर (drvdata->enable_gpio)
		gpiod_direction_output(drvdata->enable_gpio, 1);

	brightness_config_reg = LM3532_REG_ZONE_CFG_A + led->control_bank * 2;
	/*
	 * This could be hard coded to the शेष value but the control
	 * brightness रेजिस्टर may have changed during boot.
	 */
	ret = regmap_पढ़ो(drvdata->regmap, brightness_config_reg,
			  &led->ctrl_brt_poपूर्णांकer);
	अगर (ret)
		वापस ret;

	led->ctrl_brt_poपूर्णांकer &= LM3532_ZONE_MASK;
	brightness_config_val = led->ctrl_brt_poपूर्णांकer | led->mode;
	ret = regmap_ग_लिखो(drvdata->regmap, brightness_config_reg,
			   brightness_config_val);
	अगर (ret)
		वापस ret;

	अगर (led->full_scale_current) अणु
		fs_current_reg = LM3532_REG_CTRL_A_FS_CURR + led->control_bank * 2;
		fs_current_val = (led->full_scale_current - LM3532_FS_CURR_MIN) /
				 LM3532_FS_CURR_STEP;

		ret = regmap_ग_लिखो(drvdata->regmap, fs_current_reg,
				   fs_current_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < led->num_leds; i++) अणु
		output_cfg_shअगरt = led->led_strings[i] * 2;
		output_cfg_val |= (led->control_bank << output_cfg_shअगरt);
		output_cfg_mask |= LM3532_OUTPUT_CFG_MASK << output_cfg_shअगरt;
	पूर्ण

	ret = regmap_update_bits(drvdata->regmap, LM3532_REG_OUTPUT_CFG,
				 output_cfg_mask, output_cfg_val);
	अगर (ret)
		वापस ret;

	runसमय_ramp_val = drvdata->runसमय_ramp_up |
			 (drvdata->runसमय_ramp_करोwn << LM3532_RAMP_DOWN_SHIFT);

	वापस regmap_ग_लिखो(drvdata->regmap, LM3532_REG_RT_RAMP,
			    runसमय_ramp_val);
पूर्ण

अटल पूर्णांक lm3532_als_configure(काष्ठा lm3532_data *priv,
				काष्ठा lm3532_led *led)
अणु
	काष्ठा lm3532_als_data *als = priv->als_data;
	u32 als_vmin, als_vmax, als_vstep;
	पूर्णांक zone_reg = LM3532_REG_ZN_0_HI;
	पूर्णांक ret;
	पूर्णांक i;

	als_vmin = als->als_vmin;
	als_vmax = als->als_vmax;

	als_vstep = (als_vmax - als_vmin) / ((LM3532_ALS_ZB_MAX + 1) * 2);

	क्रम (i = 0; i < LM3532_ALS_ZB_MAX; i++) अणु
		als->zones_lo[i] = ((als_vmin + als_vstep + (i * als_vstep)) *
				LED_FULL) / 1000;
		als->zones_hi[i] = ((als_vmin + LM3532_ALS_OFFSET_mV +
				als_vstep + (i * als_vstep)) * LED_FULL) / 1000;

		zone_reg = LM3532_REG_ZN_0_HI + i * 2;
		ret = regmap_ग_लिखो(priv->regmap, zone_reg, als->zones_lo[i]);
		अगर (ret)
			वापस ret;

		zone_reg += 1;
		ret = regmap_ग_लिखो(priv->regmap, zone_reg, als->zones_hi[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	als->config = (als->als_avrg_समय | (LM3532_ENABLE_ALS) |
		(als->als_input_mode << LM3532_ALS_SEL_SHIFT));

	वापस regmap_ग_लिखो(priv->regmap, LM3532_ALS_CONFIG, als->config);
पूर्ण

अटल पूर्णांक lm3532_parse_als(काष्ठा lm3532_data *priv)
अणु
	काष्ठा lm3532_als_data *als;
	पूर्णांक als_avg_समय;
	पूर्णांक als_impedance;
	पूर्णांक ret;

	als = devm_kzalloc(priv->dev, माप(*als), GFP_KERNEL);
	अगर (als == शून्य)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_u32(&priv->client->dev, "ti,als-vmin",
				       &als->als_vmin);
	अगर (ret)
		als->als_vmin = 0;

	ret = device_property_पढ़ो_u32(&priv->client->dev, "ti,als-vmax",
				       &als->als_vmax);
	अगर (ret)
		als->als_vmax = LM3532_ALS_WINDOW_mV;

	अगर (als->als_vmax > LM3532_ALS_WINDOW_mV) अणु
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(&priv->client->dev, "ti,als1-imp-sel",
				      &als_impedance);
	अगर (ret)
		als->als1_imp_sel = 0;
	अन्यथा
		als->als1_imp_sel = lm3532_get_als_imp_index(als_impedance);

	ret = device_property_पढ़ो_u32(&priv->client->dev, "ti,als2-imp-sel",
				      &als_impedance);
	अगर (ret)
		als->als2_imp_sel = 0;
	अन्यथा
		als->als2_imp_sel = lm3532_get_als_imp_index(als_impedance);

	ret = device_property_पढ़ो_u32(&priv->client->dev, "ti,als-avrg-time-us",
				      &als_avg_समय);
	अगर (ret)
		als->als_avrg_समय = 0;
	अन्यथा
		als->als_avrg_समय = lm3532_get_als_avg_index(als_avg_समय);

	ret = device_property_पढ़ो_u8(&priv->client->dev, "ti,als-input-mode",
				      &als->als_input_mode);
	अगर (ret)
		als->als_input_mode = 0;

	अगर (als->als_input_mode > LM3532_BL_MODE_ALS) अणु
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	priv->als_data = als;

	वापस ret;
पूर्ण

अटल पूर्णांक lm3532_parse_node(काष्ठा lm3532_data *priv)
अणु
	काष्ठा fwnode_handle *child = शून्य;
	काष्ठा lm3532_led *led;
	पूर्णांक control_bank;
	u32 ramp_समय;
	माप_प्रकार i = 0;
	पूर्णांक ret;

	priv->enable_gpio = devm_gpiod_get_optional(&priv->client->dev,
						   "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->enable_gpio))
		priv->enable_gpio = शून्य;

	priv->regulator = devm_regulator_get(&priv->client->dev, "vin");
	अगर (IS_ERR(priv->regulator))
		priv->regulator = शून्य;

	ret = device_property_पढ़ो_u32(&priv->client->dev, "ramp-up-us",
				       &ramp_समय);
	अगर (ret)
		dev_info(&priv->client->dev, "ramp-up-ms property missing\n");
	अन्यथा
		priv->runसमय_ramp_up = lm3532_get_ramp_index(ramp_समय);

	ret = device_property_पढ़ो_u32(&priv->client->dev, "ramp-down-us",
				       &ramp_समय);
	अगर (ret)
		dev_info(&priv->client->dev, "ramp-down-ms property missing\n");
	अन्यथा
		priv->runसमय_ramp_करोwn = lm3532_get_ramp_index(ramp_समय);

	device_क्रम_each_child_node(priv->dev, child) अणु
		काष्ठा led_init_data idata = अणु
			.fwnode = child,
			.शेष_label = ":",
			.devicename = priv->client->name,
		पूर्ण;

		led = &priv->leds[i];

		ret = fwnode_property_पढ़ो_u32(child, "reg", &control_bank);
		अगर (ret) अणु
			dev_err(&priv->client->dev, "reg property missing\n");
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		अगर (control_bank > LM3532_CONTROL_C) अणु
			dev_err(&priv->client->dev, "Control bank invalid\n");
			जारी;
		पूर्ण

		led->control_bank = control_bank;

		ret = fwnode_property_पढ़ो_u32(child, "ti,led-mode",
					       &led->mode);
		अगर (ret) अणु
			dev_err(&priv->client->dev, "ti,led-mode property missing\n");
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		अगर (fwnode_property_present(child, "led-max-microamp") &&
		    fwnode_property_पढ़ो_u32(child, "led-max-microamp",
					     &led->full_scale_current))
			dev_err(&priv->client->dev,
				"Failed getting led-max-microamp\n");
		अन्यथा
			led->full_scale_current = min(led->full_scale_current,
						      LM3532_FS_CURR_MAX);

		अगर (led->mode == LM3532_BL_MODE_ALS) अणु
			led->mode = LM3532_ALS_CTRL;
			ret = lm3532_parse_als(priv);
			अगर (ret)
				dev_err(&priv->client->dev, "Failed to parse als\n");
			अन्यथा
				lm3532_als_configure(priv, led);
		पूर्ण अन्यथा अणु
			led->mode = LM3532_I2C_CTRL;
		पूर्ण

		led->num_leds = fwnode_property_count_u32(child, "led-sources");
		अगर (led->num_leds > LM3532_MAX_LED_STRINGS) अणु
			dev_err(&priv->client->dev, "Too many LED string defined\n");
			जारी;
		पूर्ण

		ret = fwnode_property_पढ़ो_u32_array(child, "led-sources",
						    led->led_strings,
						    led->num_leds);
		अगर (ret) अणु
			dev_err(&priv->client->dev, "led-sources property missing\n");
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		led->priv = priv;
		led->led_dev.brightness_set_blocking = lm3532_brightness_set;

		ret = devm_led_classdev_रेजिस्टर_ext(priv->dev, &led->led_dev, &idata);
		अगर (ret) अणु
			dev_err(&priv->client->dev, "led register err: %d\n",
				ret);
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		ret = lm3532_init_रेजिस्टरs(led);
		अगर (ret) अणु
			dev_err(&priv->client->dev, "register init err: %d\n",
				ret);
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		i++;
	पूर्ण

child_out:
	वापस ret;
पूर्ण

अटल पूर्णांक lm3532_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm3532_data *drvdata;
	पूर्णांक ret = 0;
	पूर्णांक count;

	count = device_get_child_node_count(&client->dev);
	अगर (!count) अणु
		dev_err(&client->dev, "LEDs are not defined in device tree!");
		वापस -ENODEV;
	पूर्ण

	drvdata = devm_kzalloc(&client->dev, काष्ठा_size(drvdata, leds, count),
			   GFP_KERNEL);
	अगर (drvdata == शून्य)
		वापस -ENOMEM;

	drvdata->client = client;
	drvdata->dev = &client->dev;

	drvdata->regmap = devm_regmap_init_i2c(client, &lm3532_regmap_config);
	अगर (IS_ERR(drvdata->regmap)) अणु
		ret = PTR_ERR(drvdata->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	mutex_init(&drvdata->lock);
	i2c_set_clientdata(client, drvdata);

	ret = lm3532_parse_node(drvdata);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to parse node\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lm3532_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3532_data *drvdata = i2c_get_clientdata(client);

	mutex_destroy(&drvdata->lock);

	अगर (drvdata->enable_gpio)
		gpiod_direction_output(drvdata->enable_gpio, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_lm3532_leds_match[] = अणु
	अणु .compatible = "ti,lm3532", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lm3532_leds_match);

अटल स्थिर काष्ठा i2c_device_id lm3532_id[] = अणु
	अणुLM3532_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm3532_id);

अटल काष्ठा i2c_driver lm3532_i2c_driver = अणु
	.probe = lm3532_probe,
	.हटाओ = lm3532_हटाओ,
	.id_table = lm3532_id,
	.driver = अणु
		.name = LM3532_NAME,
		.of_match_table = of_lm3532_leds_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(lm3532_i2c_driver);

MODULE_DESCRIPTION("Back Light driver for LM3532");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
