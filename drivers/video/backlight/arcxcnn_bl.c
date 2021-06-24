<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight driver क्रम ArcticSand ARC_X_C_0N_0N Devices
 *
 * Copyright 2016 ArcticSand, Inc.
 * Author : Brian Dodge <bकरोdge@arcticsand.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

क्रमागत arcxcnn_chip_id अणु
	ARC2C0608
पूर्ण;

/**
 * काष्ठा arcxcnn_platक्रमm_data
 * @name		: Backlight driver name (शून्य will use शेष)
 * @initial_brightness	: initial value of backlight brightness
 * @leden		: initial LED string enables, upper bit is global on/off
 * @led_config_0	: fading speed (period between पूर्णांकensity steps)
 * @led_config_1	: misc settings, see datasheet
 * @dim_freq		: pwm dimming frequency अगर in pwm mode
 * @comp_config		: misc config, see datasheet
 * @filter_config	: RC/PWM filter config, see datasheet
 * @trim_config		: full scale current trim, see datasheet
 */
काष्ठा arcxcnn_platक्रमm_data अणु
	स्थिर अक्षर *name;
	u16 initial_brightness;
	u8	leden;
	u8	led_config_0;
	u8	led_config_1;
	u8	dim_freq;
	u8	comp_config;
	u8	filter_config;
	u8	trim_config;
पूर्ण;

#घोषणा ARCXCNN_CMD		0x00	/* Command Register */
#घोषणा ARCXCNN_CMD_STDBY	0x80	/*   I2C Standby */
#घोषणा ARCXCNN_CMD_RESET	0x40	/*   Reset */
#घोषणा ARCXCNN_CMD_BOOST	0x10	/*   Boost */
#घोषणा ARCXCNN_CMD_OVP_MASK	0x0C	/*   --- Over Voltage Threshold */
#घोषणा ARCXCNN_CMD_OVP_XXV	0x0C	/*   <rsvrd> Over Voltage Threshold */
#घोषणा ARCXCNN_CMD_OVP_20V	0x08	/*   20v Over Voltage Threshold */
#घोषणा ARCXCNN_CMD_OVP_24V	0x04	/*   24v Over Voltage Threshold */
#घोषणा ARCXCNN_CMD_OVP_31V	0x00	/*   31.4v Over Voltage Threshold */
#घोषणा ARCXCNN_CMD_EXT_COMP	0x01	/*   part (0) or full (1) ext. comp */

#घोषणा ARCXCNN_CONFIG		0x01	/* Configuration */
#घोषणा ARCXCNN_STATUS1		0x02	/* Status 1 */
#घोषणा ARCXCNN_STATUS2		0x03	/* Status 2 */
#घोषणा ARCXCNN_FADECTRL	0x04	/* Fading Control */
#घोषणा ARCXCNN_ILED_CONFIG	0x05	/* ILED Configuration */
#घोषणा ARCXCNN_ILED_DIM_PWM	0x00	/*   config dim mode pwm */
#घोषणा ARCXCNN_ILED_DIM_INT	0x04	/*   config dim mode पूर्णांकernal */
#घोषणा ARCXCNN_LEDEN		0x06	/* LED Enable Register */
#घोषणा ARCXCNN_LEDEN_ISETEXT	0x80	/*   Full-scale current set बाह्य */
#घोषणा ARCXCNN_LEDEN_MASK	0x3F	/*   LED string enables mask */
#घोषणा ARCXCNN_LEDEN_BITS	0x06	/*   Bits of LED string enables */
#घोषणा ARCXCNN_LEDEN_LED1	0x01
#घोषणा ARCXCNN_LEDEN_LED2	0x02
#घोषणा ARCXCNN_LEDEN_LED3	0x04
#घोषणा ARCXCNN_LEDEN_LED4	0x08
#घोषणा ARCXCNN_LEDEN_LED5	0x10
#घोषणा ARCXCNN_LEDEN_LED6	0x20

#घोषणा ARCXCNN_WLED_ISET_LSB	0x07	/* LED ISET LSB (in upper nibble) */
#घोषणा ARCXCNN_WLED_ISET_LSB_SHIFT 0x04  /* ISET LSB Left Shअगरt */
#घोषणा ARCXCNN_WLED_ISET_MSB	0x08	/* LED ISET MSB (8 bits) */

#घोषणा ARCXCNN_DIMFREQ		0x09
#घोषणा ARCXCNN_COMP_CONFIG	0x0A
#घोषणा ARCXCNN_FILT_CONFIG	0x0B
#घोषणा ARCXCNN_IMAXTUNE	0x0C
#घोषणा ARCXCNN_ID_MSB		0x1E
#घोषणा ARCXCNN_ID_LSB		0x1F

#घोषणा MAX_BRIGHTNESS		4095
#घोषणा INIT_BRIGHT		60

काष्ठा arcxcnn अणु
	काष्ठा i2c_client *client;
	काष्ठा backlight_device *bl;
	काष्ठा device *dev;
	काष्ठा arcxcnn_platक्रमm_data *pdata;
पूर्ण;

अटल पूर्णांक arcxcnn_update_field(काष्ठा arcxcnn *lp, u8 reg, u8 mask, u8 data)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	ret = i2c_smbus_पढ़ो_byte_data(lp->client, reg);
	अगर (ret < 0) अणु
		dev_err(lp->dev, "failed to read 0x%.2x\n", reg);
		वापस ret;
	पूर्ण

	पंचांगp = (u8)ret;
	पंचांगp &= ~mask;
	पंचांगp |= data & mask;

	वापस i2c_smbus_ग_लिखो_byte_data(lp->client, reg, पंचांगp);
पूर्ण

अटल पूर्णांक arcxcnn_set_brightness(काष्ठा arcxcnn *lp, u32 brightness)
अणु
	पूर्णांक ret;
	u8 val;

	/* lower nibble of brightness goes in upper nibble of LSB रेजिस्टर */
	val = (brightness & 0xF) << ARCXCNN_WLED_ISET_LSB_SHIFT;
	ret = i2c_smbus_ग_लिखो_byte_data(lp->client,
		ARCXCNN_WLED_ISET_LSB, val);
	अगर (ret < 0)
		वापस ret;

	/* reमुख्यing 8 bits of brightness go in MSB रेजिस्टर */
	val = (brightness >> 4);
	वापस i2c_smbus_ग_लिखो_byte_data(lp->client,
		ARCXCNN_WLED_ISET_MSB, val);
पूर्ण

अटल पूर्णांक arcxcnn_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा arcxcnn *lp = bl_get_data(bl);
	u32 brightness = bl->props.brightness;
	पूर्णांक ret;

	अगर (bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	ret = arcxcnn_set_brightness(lp, brightness);
	अगर (ret)
		वापस ret;

	/* set घातer-on/off/save modes */
	वापस arcxcnn_update_field(lp, ARCXCNN_CMD, ARCXCNN_CMD_STDBY,
		(bl->props.घातer == 0) ? 0 : ARCXCNN_CMD_STDBY);
पूर्ण

अटल स्थिर काष्ठा backlight_ops arcxcnn_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = arcxcnn_bl_update_status,
पूर्ण;

अटल पूर्णांक arcxcnn_backlight_रेजिस्टर(काष्ठा arcxcnn *lp)
अणु
	काष्ठा backlight_properties *props;
	स्थिर अक्षर *name = lp->pdata->name ? : "arctic_bl";

	props = devm_kzalloc(lp->dev, माप(*props), GFP_KERNEL);
	अगर (!props)
		वापस -ENOMEM;

	props->type = BACKLIGHT_PLATFORM;
	props->max_brightness = MAX_BRIGHTNESS;

	अगर (lp->pdata->initial_brightness > props->max_brightness)
		lp->pdata->initial_brightness = props->max_brightness;

	props->brightness = lp->pdata->initial_brightness;

	lp->bl = devm_backlight_device_रेजिस्टर(lp->dev, name, lp->dev, lp,
				       &arcxcnn_bl_ops, props);
	वापस PTR_ERR_OR_ZERO(lp->bl);
पूर्ण

अटल व्योम arcxcnn_parse_dt(काष्ठा arcxcnn *lp)
अणु
	काष्ठा device *dev = lp->dev;
	काष्ठा device_node *node = dev->of_node;
	u32 prog_val, num_entry, entry, sources[ARCXCNN_LEDEN_BITS];
	पूर्णांक ret;

	/* device tree entry isn't required, शेषs are OK */
	अगर (!node)
		वापस;

	ret = of_property_पढ़ो_string(node, "label", &lp->pdata->name);
	अगर (ret < 0)
		lp->pdata->name = शून्य;

	ret = of_property_पढ़ो_u32(node, "default-brightness", &prog_val);
	अगर (ret == 0)
		lp->pdata->initial_brightness = prog_val;

	ret = of_property_पढ़ो_u32(node, "arc,led-config-0", &prog_val);
	अगर (ret == 0)
		lp->pdata->led_config_0 = (u8)prog_val;

	ret = of_property_पढ़ो_u32(node, "arc,led-config-1", &prog_val);
	अगर (ret == 0)
		lp->pdata->led_config_1 = (u8)prog_val;

	ret = of_property_पढ़ो_u32(node, "arc,dim-freq", &prog_val);
	अगर (ret == 0)
		lp->pdata->dim_freq = (u8)prog_val;

	ret = of_property_पढ़ो_u32(node, "arc,comp-config", &prog_val);
	अगर (ret == 0)
		lp->pdata->comp_config = (u8)prog_val;

	ret = of_property_पढ़ो_u32(node, "arc,filter-config", &prog_val);
	अगर (ret == 0)
		lp->pdata->filter_config = (u8)prog_val;

	ret = of_property_पढ़ो_u32(node, "arc,trim-config", &prog_val);
	अगर (ret == 0)
		lp->pdata->trim_config = (u8)prog_val;

	ret = of_property_count_u32_elems(node, "led-sources");
	अगर (ret < 0) अणु
		lp->pdata->leden = ARCXCNN_LEDEN_MASK; /* all on is शेष */
	पूर्ण अन्यथा अणु
		num_entry = ret;
		अगर (num_entry > ARCXCNN_LEDEN_BITS)
			num_entry = ARCXCNN_LEDEN_BITS;

		ret = of_property_पढ़ो_u32_array(node, "led-sources", sources,
					num_entry);
		अगर (ret < 0) अणु
			dev_err(dev, "led-sources node is invalid.\n");
			वापस;
		पूर्ण

		lp->pdata->leden = 0;

		/* क्रम each enable in source, set bit in led enable */
		क्रम (entry = 0; entry < num_entry; entry++) अणु
			u8 onbit = 1 << sources[entry];

			lp->pdata->leden |= onbit;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक arcxcnn_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा arcxcnn *lp;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(cl->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	lp = devm_kzalloc(&cl->dev, माप(*lp), GFP_KERNEL);
	अगर (!lp)
		वापस -ENOMEM;

	lp->client = cl;
	lp->dev = &cl->dev;
	lp->pdata = dev_get_platdata(&cl->dev);

	/* reset the device */
	ret = i2c_smbus_ग_लिखो_byte_data(lp->client,
		ARCXCNN_CMD, ARCXCNN_CMD_RESET);
	अगर (ret)
		जाओ probe_err;

	अगर (!lp->pdata) अणु
		lp->pdata = devm_kzalloc(lp->dev,
				माप(*lp->pdata), GFP_KERNEL);
		अगर (!lp->pdata)
			वापस -ENOMEM;

		/* Setup शेषs based on घातer-on शेषs */
		lp->pdata->name = शून्य;
		lp->pdata->initial_brightness = INIT_BRIGHT;
		lp->pdata->leden = ARCXCNN_LEDEN_MASK;

		lp->pdata->led_config_0 = i2c_smbus_पढ़ो_byte_data(
			lp->client, ARCXCNN_FADECTRL);

		lp->pdata->led_config_1 = i2c_smbus_पढ़ो_byte_data(
			lp->client, ARCXCNN_ILED_CONFIG);
		/* insure dim mode is not शेष pwm */
		lp->pdata->led_config_1 |= ARCXCNN_ILED_DIM_INT;

		lp->pdata->dim_freq = i2c_smbus_पढ़ो_byte_data(
			lp->client, ARCXCNN_DIMFREQ);

		lp->pdata->comp_config = i2c_smbus_पढ़ो_byte_data(
			lp->client, ARCXCNN_COMP_CONFIG);

		lp->pdata->filter_config = i2c_smbus_पढ़ो_byte_data(
			lp->client, ARCXCNN_FILT_CONFIG);

		lp->pdata->trim_config = i2c_smbus_पढ़ो_byte_data(
			lp->client, ARCXCNN_IMAXTUNE);

		अगर (IS_ENABLED(CONFIG_OF))
			arcxcnn_parse_dt(lp);
	पूर्ण

	i2c_set_clientdata(cl, lp);

	/* स्थिरrain settings to what is possible */
	अगर (lp->pdata->initial_brightness > MAX_BRIGHTNESS)
		lp->pdata->initial_brightness = MAX_BRIGHTNESS;

	/* set initial brightness */
	ret = arcxcnn_set_brightness(lp, lp->pdata->initial_brightness);
	अगर (ret)
		जाओ probe_err;

	/* set other रेजिस्टर values directly */
	ret = i2c_smbus_ग_लिखो_byte_data(lp->client, ARCXCNN_FADECTRL,
		lp->pdata->led_config_0);
	अगर (ret)
		जाओ probe_err;

	ret = i2c_smbus_ग_लिखो_byte_data(lp->client, ARCXCNN_ILED_CONFIG,
		lp->pdata->led_config_1);
	अगर (ret)
		जाओ probe_err;

	ret = i2c_smbus_ग_लिखो_byte_data(lp->client, ARCXCNN_DIMFREQ,
		lp->pdata->dim_freq);
	अगर (ret)
		जाओ probe_err;

	ret = i2c_smbus_ग_लिखो_byte_data(lp->client, ARCXCNN_COMP_CONFIG,
		lp->pdata->comp_config);
	अगर (ret)
		जाओ probe_err;

	ret = i2c_smbus_ग_लिखो_byte_data(lp->client, ARCXCNN_FILT_CONFIG,
		lp->pdata->filter_config);
	अगर (ret)
		जाओ probe_err;

	ret = i2c_smbus_ग_लिखो_byte_data(lp->client, ARCXCNN_IMAXTUNE,
		lp->pdata->trim_config);
	अगर (ret)
		जाओ probe_err;

	/* set initial LED Enables */
	arcxcnn_update_field(lp, ARCXCNN_LEDEN,
		ARCXCNN_LEDEN_MASK, lp->pdata->leden);

	ret = arcxcnn_backlight_रेजिस्टर(lp);
	अगर (ret)
		जाओ probe_रेजिस्टर_err;

	backlight_update_status(lp->bl);

	वापस 0;

probe_रेजिस्टर_err:
	dev_err(lp->dev,
		"failed to register backlight.\n");

probe_err:
	dev_err(lp->dev,
		"failure ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक arcxcnn_हटाओ(काष्ठा i2c_client *cl)
अणु
	काष्ठा arcxcnn *lp = i2c_get_clientdata(cl);

	/* disable all strings (ignore errors) */
	i2c_smbus_ग_लिखो_byte_data(lp->client,
		ARCXCNN_LEDEN, 0x00);
	/* reset the device (ignore errors) */
	i2c_smbus_ग_लिखो_byte_data(lp->client,
		ARCXCNN_CMD, ARCXCNN_CMD_RESET);

	lp->bl->props.brightness = 0;

	backlight_update_status(lp->bl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id arcxcnn_dt_ids[] = अणु
	अणु .compatible = "arc,arc2c0608" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, arcxcnn_dt_ids);

अटल स्थिर काष्ठा i2c_device_id arcxcnn_ids[] = अणु
	अणु"arc2c0608", ARC2C0608पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, arcxcnn_ids);

अटल काष्ठा i2c_driver arcxcnn_driver = अणु
	.driver = अणु
		.name = "arcxcnn_bl",
		.of_match_table = of_match_ptr(arcxcnn_dt_ids),
	पूर्ण,
	.probe = arcxcnn_probe,
	.हटाओ = arcxcnn_हटाओ,
	.id_table = arcxcnn_ids,
पूर्ण;
module_i2c_driver(arcxcnn_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Brian Dodge <bdodge@arcticsand.com>");
MODULE_DESCRIPTION("ARCXCNN Backlight driver");
