<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2021
 * Author(s): Giulio Benetti <giulio.benetti@benettiengineering.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/irq.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा HY46XX_CHKSUM_CODE		0x1
#घोषणा HY46XX_FINGER_NUM		0x2
#घोषणा HY46XX_CHKSUM_LEN		0x7
#घोषणा HY46XX_THRESHOLD		0x80
#घोषणा HY46XX_GLOVE_EN			0x84
#घोषणा HY46XX_REPORT_SPEED		0x88
#घोषणा HY46XX_PWR_NOISE_EN		0x89
#घोषणा HY46XX_FILTER_DATA		0x8A
#घोषणा HY46XX_GAIN			0x92
#घोषणा HY46XX_EDGE_OFFSET		0x93
#घोषणा HY46XX_RX_NR_USED		0x94
#घोषणा HY46XX_TX_NR_USED		0x95
#घोषणा HY46XX_PWR_MODE			0xA5
#घोषणा HY46XX_FW_VERSION		0xA6
#घोषणा HY46XX_LIB_VERSION		0xA7
#घोषणा HY46XX_TP_INFO			0xA8
#घोषणा HY46XX_TP_CHIP_ID		0xA9
#घोषणा HY46XX_BOOT_VER			0xB0

#घोषणा HY46XX_TPLEN			0x6
#घोषणा HY46XX_REPORT_PKT_LEN		0x44

#घोषणा HY46XX_MAX_SUPPORTED_POINTS	11

#घोषणा TOUCH_EVENT_DOWN		0x00
#घोषणा TOUCH_EVENT_UP			0x01
#घोषणा TOUCH_EVENT_CONTACT		0x02
#घोषणा TOUCH_EVENT_RESERVED		0x03

काष्ठा hycon_hy46xx_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा touchscreen_properties prop;
	काष्ठा regulator *vcc;

	काष्ठा gpio_desc *reset_gpio;

	काष्ठा mutex mutex;
	काष्ठा regmap *regmap;

	पूर्णांक threshold;
	bool glove_enable;
	पूर्णांक report_speed;
	bool noise_filter_enable;
	पूर्णांक filter_data;
	पूर्णांक gain;
	पूर्णांक edge_offset;
	पूर्णांक rx_number_used;
	पूर्णांक tx_number_used;
	पूर्णांक घातer_mode;
	पूर्णांक fw_version;
	पूर्णांक lib_version;
	पूर्णांक tp_inक्रमmation;
	पूर्णांक tp_chip_id;
	पूर्णांक bootloader_version;
पूर्ण;

अटल स्थिर काष्ठा regmap_config hycon_hy46xx_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल bool hycon_hy46xx_check_checksum(काष्ठा hycon_hy46xx_data *tsdata, u8 *buf)
अणु
	u8 chksum = 0;
	पूर्णांक i;

	क्रम (i = 2; i < buf[HY46XX_CHKSUM_LEN]; i++)
		chksum += buf[i];

	अगर (chksum == buf[HY46XX_CHKSUM_CODE])
		वापस true;

	dev_err_ratelimited(&tsdata->client->dev,
			    "checksum error: 0x%02x expected, got 0x%02x\n",
			    chksum, buf[HY46XX_CHKSUM_CODE]);

	वापस false;
पूर्ण

अटल irqवापस_t hycon_hy46xx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hycon_hy46xx_data *tsdata = dev_id;
	काष्ठा device *dev = &tsdata->client->dev;
	u8 rdbuf[HY46XX_REPORT_PKT_LEN];
	पूर्णांक i, x, y, id;
	पूर्णांक error;

	स_रखो(rdbuf, 0, माप(rdbuf));

	error = regmap_bulk_पढ़ो(tsdata->regmap, 0, rdbuf, माप(rdbuf));
	अगर (error) अणु
		dev_err_ratelimited(dev, "Unable to fetch data, error: %d\n",
				    error);
		जाओ out;
	पूर्ण

	अगर (!hycon_hy46xx_check_checksum(tsdata, rdbuf))
		जाओ out;

	क्रम (i = 0; i < HY46XX_MAX_SUPPORTED_POINTS; i++) अणु
		u8 *buf = &rdbuf[3 + (HY46XX_TPLEN * i)];
		पूर्णांक type = buf[0] >> 6;

		अगर (type == TOUCH_EVENT_RESERVED)
			जारी;

		x = get_unaligned_be16(buf) & 0x0fff;
		y = get_unaligned_be16(buf + 2) & 0x0fff;

		id = buf[2] >> 4;

		input_mt_slot(tsdata->input, id);
		अगर (input_mt_report_slot_state(tsdata->input, MT_TOOL_FINGER,
					       type != TOUCH_EVENT_UP))
			touchscreen_report_pos(tsdata->input, &tsdata->prop,
					       x, y, true);
	पूर्ण

	input_mt_report_poपूर्णांकer_emulation(tsdata->input, false);
	input_sync(tsdata->input);

out:
	वापस IRQ_HANDLED;
पूर्ण

काष्ठा hycon_hy46xx_attribute अणु
	काष्ठा device_attribute dattr;
	माप_प्रकार field_offset;
	u8 address;
	u8 limit_low;
	u8 limit_high;
पूर्ण;

#घोषणा HYCON_ATTR_U8(_field, _mode, _address, _limit_low, _limit_high)	\
	काष्ठा hycon_hy46xx_attribute hycon_hy46xx_attr_##_field = अणु		\
		.dattr = __ATTR(_field, _mode,				\
				hycon_hy46xx_setting_show,			\
				hycon_hy46xx_setting_store),			\
		.field_offset = दुरत्व(काष्ठा hycon_hy46xx_data, _field),	\
		.address = _address,					\
		.limit_low = _limit_low,				\
		.limit_high = _limit_high,				\
	पूर्ण

#घोषणा HYCON_ATTR_BOOL(_field, _mode, _address)			\
	काष्ठा hycon_hy46xx_attribute hycon_hy46xx_attr_##_field = अणु		\
		.dattr = __ATTR(_field, _mode,				\
				hycon_hy46xx_setting_show,			\
				hycon_hy46xx_setting_store),			\
		.field_offset = दुरत्व(काष्ठा hycon_hy46xx_data, _field),	\
		.address = _address,					\
		.limit_low = false,					\
		.limit_high = true,					\
	पूर्ण

अटल sमाप_प्रकार hycon_hy46xx_setting_show(काष्ठा device *dev,
				   काष्ठा device_attribute *dattr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा hycon_hy46xx_data *tsdata = i2c_get_clientdata(client);
	काष्ठा hycon_hy46xx_attribute *attr =
			container_of(dattr, काष्ठा hycon_hy46xx_attribute, dattr);
	u8 *field = (u8 *)tsdata + attr->field_offset;
	माप_प्रकार count = 0;
	पूर्णांक error = 0;
	पूर्णांक val;

	mutex_lock(&tsdata->mutex);

	error = regmap_पढ़ो(tsdata->regmap, attr->address, &val);
	अगर (error < 0) अणु
		dev_err(&tsdata->client->dev,
			"Failed to fetch attribute %s, error %d\n",
			dattr->attr.name, error);
		जाओ out;
	पूर्ण

	अगर (val != *field) अणु
		dev_warn(&tsdata->client->dev,
			 "%s: read (%d) and stored value (%d) differ\n",
			 dattr->attr.name, val, *field);
		*field = val;
	पूर्ण

	count = scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);

out:
	mutex_unlock(&tsdata->mutex);
	वापस error ?: count;
पूर्ण

अटल sमाप_प्रकार hycon_hy46xx_setting_store(काष्ठा device *dev,
					काष्ठा device_attribute *dattr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा hycon_hy46xx_data *tsdata = i2c_get_clientdata(client);
	काष्ठा hycon_hy46xx_attribute *attr =
			container_of(dattr, काष्ठा hycon_hy46xx_attribute, dattr);
	u8 *field = (u8 *)tsdata + attr->field_offset;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	mutex_lock(&tsdata->mutex);

	error = kstrtouपूर्णांक(buf, 0, &val);
	अगर (error)
		जाओ out;

	अगर (val < attr->limit_low || val > attr->limit_high) अणु
		error = -दुस्फल;
		जाओ out;
	पूर्ण

	error = regmap_ग_लिखो(tsdata->regmap, attr->address, val);
	अगर (error < 0) अणु
		dev_err(&tsdata->client->dev,
			"Failed to update attribute %s, error: %d\n",
			dattr->attr.name, error);
		जाओ out;
	पूर्ण
	*field = val;

out:
	mutex_unlock(&tsdata->mutex);
	वापस error ?: count;
पूर्ण

अटल HYCON_ATTR_U8(threshold, 0644, HY46XX_THRESHOLD, 0, 255);
अटल HYCON_ATTR_BOOL(glove_enable, 0644, HY46XX_GLOVE_EN);
अटल HYCON_ATTR_U8(report_speed, 0644, HY46XX_REPORT_SPEED, 0, 255);
अटल HYCON_ATTR_BOOL(noise_filter_enable, 0644, HY46XX_PWR_NOISE_EN);
अटल HYCON_ATTR_U8(filter_data, 0644, HY46XX_FILTER_DATA, 0, 5);
अटल HYCON_ATTR_U8(gain, 0644, HY46XX_GAIN, 0, 5);
अटल HYCON_ATTR_U8(edge_offset, 0644, HY46XX_EDGE_OFFSET, 0, 5);
अटल HYCON_ATTR_U8(fw_version, 0444, HY46XX_FW_VERSION, 0, 255);
अटल HYCON_ATTR_U8(lib_version, 0444, HY46XX_LIB_VERSION, 0, 255);
अटल HYCON_ATTR_U8(tp_inक्रमmation, 0444, HY46XX_TP_INFO, 0, 255);
अटल HYCON_ATTR_U8(tp_chip_id, 0444, HY46XX_TP_CHIP_ID, 0, 255);
अटल HYCON_ATTR_U8(bootloader_version, 0444, HY46XX_BOOT_VER, 0, 255);

अटल काष्ठा attribute *hycon_hy46xx_attrs[] = अणु
	&hycon_hy46xx_attr_threshold.dattr.attr,
	&hycon_hy46xx_attr_glove_enable.dattr.attr,
	&hycon_hy46xx_attr_report_speed.dattr.attr,
	&hycon_hy46xx_attr_noise_filter_enable.dattr.attr,
	&hycon_hy46xx_attr_filter_data.dattr.attr,
	&hycon_hy46xx_attr_gain.dattr.attr,
	&hycon_hy46xx_attr_edge_offset.dattr.attr,
	&hycon_hy46xx_attr_fw_version.dattr.attr,
	&hycon_hy46xx_attr_lib_version.dattr.attr,
	&hycon_hy46xx_attr_tp_inक्रमmation.dattr.attr,
	&hycon_hy46xx_attr_tp_chip_id.dattr.attr,
	&hycon_hy46xx_attr_bootloader_version.dattr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hycon_hy46xx_attr_group = अणु
	.attrs = hycon_hy46xx_attrs,
पूर्ण;

अटल व्योम hycon_hy46xx_get_शेषs(काष्ठा device *dev, काष्ठा hycon_hy46xx_data *tsdata)
अणु
	bool val_bool;
	पूर्णांक error;
	u32 val;

	error = device_property_पढ़ो_u32(dev, "hycon,threshold", &val);
	अगर (!error) अणु
		error = regmap_ग_लिखो(tsdata->regmap, HY46XX_THRESHOLD, val);
		अगर (error < 0)
			जाओ out;

		tsdata->threshold = val;
	पूर्ण

	val_bool = device_property_पढ़ो_bool(dev, "hycon,glove-enable");
	error = regmap_ग_लिखो(tsdata->regmap, HY46XX_GLOVE_EN, val_bool);
	अगर (error < 0)
		जाओ out;
	tsdata->glove_enable = val_bool;

	error = device_property_पढ़ो_u32(dev, "hycon,report-speed-hz", &val);
	अगर (!error) अणु
		error = regmap_ग_लिखो(tsdata->regmap, HY46XX_REPORT_SPEED, val);
		अगर (error < 0)
			जाओ out;

		tsdata->report_speed = val;
	पूर्ण

	val_bool = device_property_पढ़ो_bool(dev, "hycon,noise-filter-enable");
	error = regmap_ग_लिखो(tsdata->regmap, HY46XX_PWR_NOISE_EN, val_bool);
	अगर (error < 0)
		जाओ out;
	tsdata->noise_filter_enable = val_bool;

	error = device_property_पढ़ो_u32(dev, "hycon,filter-data", &val);
	अगर (!error) अणु
		error = regmap_ग_लिखो(tsdata->regmap, HY46XX_FILTER_DATA, val);
		अगर (error < 0)
			जाओ out;

		tsdata->filter_data = val;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "hycon,gain", &val);
	अगर (!error) अणु
		error = regmap_ग_लिखो(tsdata->regmap, HY46XX_GAIN, val);
		अगर (error < 0)
			जाओ out;

		tsdata->gain = val;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "hycon,edge-offset", &val);
	अगर (!error) अणु
		error = regmap_ग_लिखो(tsdata->regmap, HY46XX_EDGE_OFFSET, val);
		अगर (error < 0)
			जाओ out;

		tsdata->edge_offset = val;
	पूर्ण

	वापस;
out:
	dev_err(&tsdata->client->dev, "Failed to set default settings");
पूर्ण

अटल व्योम hycon_hy46xx_get_parameters(काष्ठा hycon_hy46xx_data *tsdata)
अणु
	पूर्णांक error;
	u32 val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_THRESHOLD, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->threshold = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_GLOVE_EN, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->glove_enable = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_REPORT_SPEED, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->report_speed = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_PWR_NOISE_EN, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->noise_filter_enable = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_FILTER_DATA, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->filter_data = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_GAIN, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->gain = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_EDGE_OFFSET, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->edge_offset = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_RX_NR_USED, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->rx_number_used = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_TX_NR_USED, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->tx_number_used = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_PWR_MODE, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->घातer_mode = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_FW_VERSION, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->fw_version = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_LIB_VERSION, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->lib_version = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_TP_INFO, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->tp_inक्रमmation = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_TP_CHIP_ID, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->tp_chip_id = val;

	error = regmap_पढ़ो(tsdata->regmap, HY46XX_BOOT_VER, &val);
	अगर (error < 0)
		जाओ out;
	tsdata->bootloader_version = val;

	वापस;
out:
	dev_err(&tsdata->client->dev, "Failed to read default settings");
पूर्ण

अटल व्योम hycon_hy46xx_disable_regulator(व्योम *arg)
अणु
	काष्ठा hycon_hy46xx_data *data = arg;

	regulator_disable(data->vcc);
पूर्ण

अटल पूर्णांक hycon_hy46xx_probe(काष्ठा i2c_client *client,
					 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा hycon_hy46xx_data *tsdata;
	काष्ठा input_dev *input;
	पूर्णांक error;

	dev_dbg(&client->dev, "probing for HYCON HY46XX I2C\n");

	tsdata = devm_kzalloc(&client->dev, माप(*tsdata), GFP_KERNEL);
	अगर (!tsdata)
		वापस -ENOMEM;

	tsdata->vcc = devm_regulator_get(&client->dev, "vcc");
	अगर (IS_ERR(tsdata->vcc)) अणु
		error = PTR_ERR(tsdata->vcc);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to request regulator: %d\n", error);
		वापस error;
	पूर्ण

	error = regulator_enable(tsdata->vcc);
	अगर (error < 0) अणु
		dev_err(&client->dev, "failed to enable vcc: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev,
					 hycon_hy46xx_disable_regulator,
					 tsdata);
	अगर (error)
		वापस error;

	tsdata->reset_gpio = devm_gpiod_get_optional(&client->dev,
						     "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(tsdata->reset_gpio)) अणु
		error = PTR_ERR(tsdata->reset_gpio);
		dev_err(&client->dev,
			"Failed to request GPIO reset pin, error %d\n", error);
		वापस error;
	पूर्ण

	अगर (tsdata->reset_gpio) अणु
		usleep_range(5000, 6000);
		gpiod_set_value_cansleep(tsdata->reset_gpio, 1);
		usleep_range(5000, 6000);
		gpiod_set_value_cansleep(tsdata->reset_gpio, 0);
		msleep(1000);
	पूर्ण

	input = devm_input_allocate_device(&client->dev);
	अगर (!input) अणु
		dev_err(&client->dev, "failed to allocate input device.\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&tsdata->mutex);
	tsdata->client = client;
	tsdata->input = input;

	tsdata->regmap = devm_regmap_init_i2c(client,
					      &hycon_hy46xx_i2c_regmap_config);
	अगर (IS_ERR(tsdata->regmap)) अणु
		dev_err(&client->dev, "regmap allocation failed\n");
		वापस PTR_ERR(tsdata->regmap);
	पूर्ण

	hycon_hy46xx_get_शेषs(&client->dev, tsdata);
	hycon_hy46xx_get_parameters(tsdata);

	input->name = "Hycon Capacitive Touch";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0, -1, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, -1, 0, 0);

	touchscreen_parse_properties(input, true, &tsdata->prop);

	error = input_mt_init_slots(input, HY46XX_MAX_SUPPORTED_POINTS,
				    INPUT_MT_सूचीECT);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to init MT slots.\n");
		वापस error;
	पूर्ण

	i2c_set_clientdata(client, tsdata);

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, hycon_hy46xx_isr, IRQF_ONESHOT,
					  client->name, tsdata);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev, &hycon_hy46xx_attr_group);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	dev_dbg(&client->dev,
		"HYCON HY46XX initialized: IRQ %d, Reset pin %d.\n",
		client->irq,
		tsdata->reset_gpio ? desc_to_gpio(tsdata->reset_gpio) : -1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hycon_hy46xx_id[] = अणु
	अणु .name = "hy4613" पूर्ण,
	अणु .name = "hy4614" पूर्ण,
	अणु .name = "hy4621" पूर्ण,
	अणु .name = "hy4623" पूर्ण,
	अणु .name = "hy4633" पूर्ण,
	अणु .name = "hy4635" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hycon_hy46xx_id);

अटल स्थिर काष्ठा of_device_id hycon_hy46xx_of_match[] = अणु
	अणु .compatible = "hycon,hy4613" पूर्ण,
	अणु .compatible = "hycon,hy4614" पूर्ण,
	अणु .compatible = "hycon,hy4621" पूर्ण,
	अणु .compatible = "hycon,hy4623" पूर्ण,
	अणु .compatible = "hycon,hy4633" पूर्ण,
	अणु .compatible = "hycon,hy4635" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hycon_hy46xx_of_match);

अटल काष्ठा i2c_driver hycon_hy46xx_driver = अणु
	.driver = अणु
		.name = "hycon_hy46xx",
		.of_match_table = hycon_hy46xx_of_match,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.id_table = hycon_hy46xx_id,
	.probe    = hycon_hy46xx_probe,
पूर्ण;

module_i2c_driver(hycon_hy46xx_driver);

MODULE_AUTHOR("Giulio Benetti <giulio.benetti@benettiengineering.com>");
MODULE_DESCRIPTION("HYCON HY46XX I2C Touchscreen Driver");
MODULE_LICENSE("GPL v2");
