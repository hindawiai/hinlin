<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LP5521/LP5523/LP55231/LP5562 Common Driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 *
 * Derived from leds-lp5521.c, leds-lp5523.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/leds-lp55xx.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "leds-lp55xx-common.h"

/* External घड़ी rate */
#घोषणा LP55XX_CLK_32K			32768

अटल काष्ठा lp55xx_led *cdev_to_lp55xx_led(काष्ठा led_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा lp55xx_led, cdev);
पूर्ण

अटल काष्ठा lp55xx_led *dev_to_lp55xx_led(काष्ठा device *dev)
अणु
	वापस cdev_to_lp55xx_led(dev_get_drvdata(dev));
पूर्ण

अटल काष्ठा lp55xx_led *mcled_cdev_to_led(काष्ठा led_classdev_mc *mc_cdev)
अणु
	वापस container_of(mc_cdev, काष्ठा lp55xx_led, mc_cdev);
पूर्ण

अटल व्योम lp55xx_reset_device(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा lp55xx_device_config *cfg = chip->cfg;
	u8 addr = cfg->reset.addr;
	u8 val  = cfg->reset.val;

	/* no error checking here because no ACK from the device after reset */
	lp55xx_ग_लिखो(chip, addr, val);
पूर्ण

अटल पूर्णांक lp55xx_detect_device(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा lp55xx_device_config *cfg = chip->cfg;
	u8 addr = cfg->enable.addr;
	u8 val  = cfg->enable.val;
	पूर्णांक ret;

	ret = lp55xx_ग_लिखो(chip, addr, val);
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = lp55xx_पढ़ो(chip, addr, &val);
	अगर (ret)
		वापस ret;

	अगर (val != cfg->enable.val)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक lp55xx_post_init_device(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा lp55xx_device_config *cfg = chip->cfg;

	अगर (!cfg->post_init_device)
		वापस 0;

	वापस cfg->post_init_device(chip);
पूर्ण

अटल sमाप_प्रकार led_current_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा lp55xx_led *led = dev_to_lp55xx_led(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", led->led_current);
पूर्ण

अटल sमाप_प्रकार led_current_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lp55xx_led *led = dev_to_lp55xx_led(dev);
	काष्ठा lp55xx_chip *chip = led->chip;
	अचिन्हित दीर्घ curr;

	अगर (kम_से_अदीर्घ(buf, 0, &curr))
		वापस -EINVAL;

	अगर (curr > led->max_current)
		वापस -EINVAL;

	अगर (!chip->cfg->set_led_current)
		वापस len;

	mutex_lock(&chip->lock);
	chip->cfg->set_led_current(led, (u8)curr);
	mutex_unlock(&chip->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार max_current_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा lp55xx_led *led = dev_to_lp55xx_led(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", led->max_current);
पूर्ण

अटल DEVICE_ATTR_RW(led_current);
अटल DEVICE_ATTR_RO(max_current);

अटल काष्ठा attribute *lp55xx_led_attrs[] = अणु
	&dev_attr_led_current.attr,
	&dev_attr_max_current.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(lp55xx_led);

अटल पूर्णांक lp55xx_set_mc_brightness(काष्ठा led_classdev *cdev,
				    क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_mc *mc_dev = lcdev_to_mccdev(cdev);
	काष्ठा lp55xx_led *led = mcled_cdev_to_led(mc_dev);
	काष्ठा lp55xx_device_config *cfg = led->chip->cfg;

	led_mc_calc_color_components(&led->mc_cdev, brightness);
	वापस cfg->multicolor_brightness_fn(led);

पूर्ण

अटल पूर्णांक lp55xx_set_brightness(काष्ठा led_classdev *cdev,
			     क्रमागत led_brightness brightness)
अणु
	काष्ठा lp55xx_led *led = cdev_to_lp55xx_led(cdev);
	काष्ठा lp55xx_device_config *cfg = led->chip->cfg;

	led->brightness = (u8)brightness;
	वापस cfg->brightness_fn(led);
पूर्ण

अटल पूर्णांक lp55xx_init_led(काष्ठा lp55xx_led *led,
			काष्ठा lp55xx_chip *chip, पूर्णांक chan)
अणु
	काष्ठा lp55xx_platक्रमm_data *pdata = chip->pdata;
	काष्ठा lp55xx_device_config *cfg = chip->cfg;
	काष्ठा device *dev = &chip->cl->dev;
	पूर्णांक max_channel = cfg->max_channel;
	काष्ठा mc_subled *mc_led_info;
	काष्ठा led_classdev *led_cdev;
	अक्षर name[32];
	पूर्णांक i, j = 0;
	पूर्णांक ret;

	अगर (chan >= max_channel) अणु
		dev_err(dev, "invalid channel: %d / %d\n", chan, max_channel);
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->led_config[chan].led_current == 0)
		वापस 0;

	अगर (pdata->led_config[chan].name) अणु
		led->cdev.name = pdata->led_config[chan].name;
	पूर्ण अन्यथा अणु
		snम_लिखो(name, माप(name), "%s:channel%d",
			pdata->label ? : chip->cl->name, chan);
		led->cdev.name = name;
	पूर्ण

	अगर (pdata->led_config[chan].num_colors > 1) अणु
		mc_led_info = devm_kसुस्मृति(dev,
					   pdata->led_config[chan].num_colors,
					   माप(*mc_led_info), GFP_KERNEL);
		अगर (!mc_led_info)
			वापस -ENOMEM;

		led_cdev = &led->mc_cdev.led_cdev;
		led_cdev->name = led->cdev.name;
		led_cdev->brightness_set_blocking = lp55xx_set_mc_brightness;
		led->mc_cdev.num_colors = pdata->led_config[chan].num_colors;
		क्रम (i = 0; i < led->mc_cdev.num_colors; i++) अणु
			mc_led_info[i].color_index =
				pdata->led_config[chan].color_id[i];
			mc_led_info[i].channel =
					pdata->led_config[chan].output_num[i];
			j++;
		पूर्ण

		led->mc_cdev.subled_info = mc_led_info;
	पूर्ण अन्यथा अणु
		led->cdev.brightness_set_blocking = lp55xx_set_brightness;
	पूर्ण

	led->cdev.groups = lp55xx_led_groups;
	led->cdev.शेष_trigger = pdata->led_config[chan].शेष_trigger;
	led->led_current = pdata->led_config[chan].led_current;
	led->max_current = pdata->led_config[chan].max_current;
	led->chan_nr = pdata->led_config[chan].chan_nr;

	अगर (led->chan_nr >= max_channel) अणु
		dev_err(dev, "Use channel numbers between 0 and %d\n",
			max_channel - 1);
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->led_config[chan].num_colors > 1)
		ret = devm_led_classdev_multicolor_रेजिस्टर(dev, &led->mc_cdev);
	अन्यथा
		ret = devm_led_classdev_रेजिस्टर(dev, &led->cdev);

	अगर (ret) अणु
		dev_err(dev, "led register err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lp55xx_firmware_loaded(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा lp55xx_chip *chip = context;
	काष्ठा device *dev = &chip->cl->dev;
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;

	अगर (!fw) अणु
		dev_err(dev, "firmware request failed\n");
		वापस;
	पूर्ण

	/* handling firmware data is chip dependent */
	mutex_lock(&chip->lock);

	chip->engines[idx - 1].mode = LP55XX_ENGINE_LOAD;
	chip->fw = fw;
	अगर (chip->cfg->firmware_cb)
		chip->cfg->firmware_cb(chip);

	mutex_unlock(&chip->lock);

	/* firmware should be released क्रम other channel use */
	release_firmware(chip->fw);
	chip->fw = शून्य;
पूर्ण

अटल पूर्णांक lp55xx_request_firmware(काष्ठा lp55xx_chip *chip)
अणु
	स्थिर अक्षर *name = chip->cl->name;
	काष्ठा device *dev = &chip->cl->dev;

	वापस request_firmware_noरुको(THIS_MODULE, false, name, dev,
				GFP_KERNEL, chip, lp55xx_firmware_loaded);
पूर्ण

अटल sमाप_प्रकार select_engine_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;

	वापस प्र_लिखो(buf, "%d\n", chip->engine_idx);
पूर्ण

अटल sमाप_प्रकार select_engine_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	/* select the engine to be run */

	चयन (val) अणु
	हाल LP55XX_ENGINE_1:
	हाल LP55XX_ENGINE_2:
	हाल LP55XX_ENGINE_3:
		mutex_lock(&chip->lock);
		chip->engine_idx = val;
		ret = lp55xx_request_firmware(chip);
		mutex_unlock(&chip->lock);
		अवरोध;
	शेष:
		dev_err(dev, "%lu: invalid engine index. (1, 2, 3)\n", val);
		वापस -EINVAL;
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "request firmware err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस len;
पूर्ण

अटल अंतरभूत व्योम lp55xx_run_engine(काष्ठा lp55xx_chip *chip, bool start)
अणु
	अगर (chip->cfg->run_engine)
		chip->cfg->run_engine(chip, start);
पूर्ण

अटल sमाप_प्रकार run_engine_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	/* run or stop the selected engine */

	अगर (val <= 0) अणु
		lp55xx_run_engine(chip, false);
		वापस len;
	पूर्ण

	mutex_lock(&chip->lock);
	lp55xx_run_engine(chip, true);
	mutex_unlock(&chip->lock);

	वापस len;
पूर्ण

अटल DEVICE_ATTR_RW(select_engine);
अटल DEVICE_ATTR_WO(run_engine);

अटल काष्ठा attribute *lp55xx_engine_attributes[] = अणु
	&dev_attr_select_engine.attr,
	&dev_attr_run_engine.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lp55xx_engine_attr_group = अणु
	.attrs = lp55xx_engine_attributes,
पूर्ण;

पूर्णांक lp55xx_ग_लिखो(काष्ठा lp55xx_chip *chip, u8 reg, u8 val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(chip->cl, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_ग_लिखो);

पूर्णांक lp55xx_पढ़ो(काष्ठा lp55xx_chip *chip, u8 reg, u8 *val)
अणु
	s32 ret;

	ret = i2c_smbus_पढ़ो_byte_data(chip->cl, reg);
	अगर (ret < 0)
		वापस ret;

	*val = ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_पढ़ो);

पूर्णांक lp55xx_update_bits(काष्ठा lp55xx_chip *chip, u8 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	ret = lp55xx_पढ़ो(chip, reg, &पंचांगp);
	अगर (ret)
		वापस ret;

	पंचांगp &= ~mask;
	पंचांगp |= val & mask;

	वापस lp55xx_ग_लिखो(chip, reg, पंचांगp);
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_update_bits);

bool lp55xx_is_extclk_used(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा clk *clk;
	पूर्णांक err;

	clk = devm_clk_get(&chip->cl->dev, "32k_clk");
	अगर (IS_ERR(clk))
		जाओ use_पूर्णांकernal_clk;

	err = clk_prepare_enable(clk);
	अगर (err)
		जाओ use_पूर्णांकernal_clk;

	अगर (clk_get_rate(clk) != LP55XX_CLK_32K) अणु
		clk_disable_unprepare(clk);
		जाओ use_पूर्णांकernal_clk;
	पूर्ण

	dev_info(&chip->cl->dev, "%dHz external clock used\n",	LP55XX_CLK_32K);

	chip->clk = clk;
	वापस true;

use_पूर्णांकernal_clk:
	dev_info(&chip->cl->dev, "internal clock used\n");
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_is_extclk_used);

पूर्णांक lp55xx_init_device(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा lp55xx_platक्रमm_data *pdata;
	काष्ठा lp55xx_device_config *cfg;
	काष्ठा device *dev = &chip->cl->dev;
	पूर्णांक ret = 0;

	WARN_ON(!chip);

	pdata = chip->pdata;
	cfg = chip->cfg;

	अगर (!pdata || !cfg)
		वापस -EINVAL;

	अगर (pdata->enable_gpiod) अणु
		gpiod_set_consumer_name(pdata->enable_gpiod, "LP55xx enable");
		gpiod_set_value(pdata->enable_gpiod, 0);
		usleep_range(1000, 2000); /* Keep enable करोwn at least 1ms */
		gpiod_set_value(pdata->enable_gpiod, 1);
		usleep_range(1000, 2000); /* 500us असल min. */
	पूर्ण

	lp55xx_reset_device(chip);

	/*
	 * Exact value is not available. 10 - 20ms
	 * appears to be enough क्रम reset.
	 */
	usleep_range(10000, 20000);

	ret = lp55xx_detect_device(chip);
	अगर (ret) अणु
		dev_err(dev, "device detection err: %d\n", ret);
		जाओ err;
	पूर्ण

	/* chip specअगरic initialization */
	ret = lp55xx_post_init_device(chip);
	अगर (ret) अणु
		dev_err(dev, "post init device err: %d\n", ret);
		जाओ err_post_init;
	पूर्ण

	वापस 0;

err_post_init:
	lp55xx_deinit_device(chip);
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_init_device);

व्योम lp55xx_deinit_device(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा lp55xx_platक्रमm_data *pdata = chip->pdata;

	अगर (chip->clk)
		clk_disable_unprepare(chip->clk);

	अगर (pdata->enable_gpiod)
		gpiod_set_value(pdata->enable_gpiod, 0);
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_deinit_device);

पूर्णांक lp55xx_रेजिस्टर_leds(काष्ठा lp55xx_led *led, काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा lp55xx_platक्रमm_data *pdata = chip->pdata;
	काष्ठा lp55xx_device_config *cfg = chip->cfg;
	पूर्णांक num_channels = pdata->num_channels;
	काष्ठा lp55xx_led *each;
	u8 led_current;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!cfg->brightness_fn) अणु
		dev_err(&chip->cl->dev, "empty brightness configuration\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_channels; i++) अणु

		/* करो not initialize channels that are not connected */
		अगर (pdata->led_config[i].led_current == 0)
			जारी;

		led_current = pdata->led_config[i].led_current;
		each = led + i;
		ret = lp55xx_init_led(each, chip, i);
		अगर (ret)
			जाओ err_init_led;

		chip->num_leds++;
		each->chip = chip;

		/* setting led current at each channel */
		अगर (cfg->set_led_current)
			cfg->set_led_current(each, led_current);
	पूर्ण

	वापस 0;

err_init_led:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_रेजिस्टर_leds);

पूर्णांक lp55xx_रेजिस्टर_sysfs(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा device *dev = &chip->cl->dev;
	काष्ठा lp55xx_device_config *cfg = chip->cfg;
	पूर्णांक ret;

	अगर (!cfg->run_engine || !cfg->firmware_cb)
		जाओ dev_specअगरic_attrs;

	ret = sysfs_create_group(&dev->kobj, &lp55xx_engine_attr_group);
	अगर (ret)
		वापस ret;

dev_specअगरic_attrs:
	वापस cfg->dev_attr_group ?
		sysfs_create_group(&dev->kobj, cfg->dev_attr_group) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_रेजिस्टर_sysfs);

व्योम lp55xx_unरेजिस्टर_sysfs(काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा device *dev = &chip->cl->dev;
	काष्ठा lp55xx_device_config *cfg = chip->cfg;

	अगर (cfg->dev_attr_group)
		sysfs_हटाओ_group(&dev->kobj, cfg->dev_attr_group);

	sysfs_हटाओ_group(&dev->kobj, &lp55xx_engine_attr_group);
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_unरेजिस्टर_sysfs);

अटल पूर्णांक lp55xx_parse_common_child(काष्ठा device_node *np,
				     काष्ठा lp55xx_led_config *cfg,
				     पूर्णांक led_number, पूर्णांक *chan_nr)
अणु
	पूर्णांक ret;

	of_property_पढ़ो_string(np, "chan-name",
				&cfg[led_number].name);
	of_property_पढ़ो_u8(np, "led-cur",
			    &cfg[led_number].led_current);
	of_property_पढ़ो_u8(np, "max-cur",
			    &cfg[led_number].max_current);

	ret = of_property_पढ़ो_u32(np, "reg", chan_nr);
	अगर (ret)
		वापस ret;

	अगर (*chan_nr < 0 || *chan_nr > cfg->max_channel)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक lp55xx_parse_multi_led_child(काष्ठा device_node *child,
					 काष्ठा lp55xx_led_config *cfg,
					 पूर्णांक child_number, पूर्णांक color_number)
अणु
	पूर्णांक chan_nr, color_id, ret;

	ret = lp55xx_parse_common_child(child, cfg, child_number, &chan_nr);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32(child, "color", &color_id);
	अगर (ret)
		वापस ret;

	cfg[child_number].color_id[color_number] = color_id;
	cfg[child_number].output_num[color_number] = chan_nr;

	वापस 0;
पूर्ण

अटल पूर्णांक lp55xx_parse_multi_led(काष्ठा device_node *np,
				  काष्ठा lp55xx_led_config *cfg,
				  पूर्णांक child_number)
अणु
	काष्ठा device_node *child;
	पूर्णांक num_colors = 0, ret;

	क्रम_each_available_child_of_node(np, child) अणु
		ret = lp55xx_parse_multi_led_child(child, cfg, child_number,
						   num_colors);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
		num_colors++;
	पूर्ण

	cfg[child_number].num_colors = num_colors;

	वापस 0;
पूर्ण

अटल पूर्णांक lp55xx_parse_logical_led(काष्ठा device_node *np,
				   काष्ठा lp55xx_led_config *cfg,
				   पूर्णांक child_number)
अणु
	पूर्णांक led_color, ret;
	पूर्णांक chan_nr = 0;

	cfg[child_number].शेष_trigger =
		of_get_property(np, "linux,default-trigger", शून्य);

	ret = of_property_पढ़ो_u32(np, "color", &led_color);
	अगर (ret)
		वापस ret;

	अगर (led_color == LED_COLOR_ID_RGB)
		वापस lp55xx_parse_multi_led(np, cfg, child_number);

	ret =  lp55xx_parse_common_child(np, cfg, child_number, &chan_nr);
	अगर (ret < 0)
		वापस ret;

	cfg[child_number].chan_nr = chan_nr;

	वापस ret;
पूर्ण

काष्ठा lp55xx_platक्रमm_data *lp55xx_of_populate_pdata(काष्ठा device *dev,
						      काष्ठा device_node *np,
						      काष्ठा lp55xx_chip *chip)
अणु
	काष्ठा device_node *child;
	काष्ठा lp55xx_platक्रमm_data *pdata;
	काष्ठा lp55xx_led_config *cfg;
	पूर्णांक num_channels;
	पूर्णांक i = 0;
	पूर्णांक ret;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	num_channels = of_get_available_child_count(np);
	अगर (num_channels == 0) अणु
		dev_err(dev, "no LED channels\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cfg = devm_kसुस्मृति(dev, num_channels, माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस ERR_PTR(-ENOMEM);

	pdata->led_config = &cfg[0];
	pdata->num_channels = num_channels;
	cfg->max_channel = chip->cfg->max_channel;

	क्रम_each_available_child_of_node(np, child) अणु
		ret = lp55xx_parse_logical_led(child, cfg, i);
		अगर (ret) अणु
			of_node_put(child);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		i++;
	पूर्ण

	of_property_पढ़ो_string(np, "label", &pdata->label);
	of_property_पढ़ो_u8(np, "clock-mode", &pdata->घड़ी_mode);

	pdata->enable_gpiod = devm_gpiod_get_optional(dev, "enable",
						      GPIOD_ASIS);
	अगर (IS_ERR(pdata->enable_gpiod))
		वापस ERR_CAST(pdata->enable_gpiod);

	/* LP8501 specअगरic */
	of_property_पढ़ो_u8(np, "pwr-sel", (u8 *)&pdata->pwr_sel);

	वापस pdata;
पूर्ण
EXPORT_SYMBOL_GPL(lp55xx_of_populate_pdata);

MODULE_AUTHOR("Milo Kim <milo.kim@ti.com>");
MODULE_DESCRIPTION("LP55xx Common Driver");
MODULE_LICENSE("GPL");
