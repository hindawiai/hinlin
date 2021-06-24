<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Backlight driver क्रम Analog Devices ADP8860 Backlight Devices
 *
 * Copyright 2009-2010 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/platक्रमm_data/adp8860.h>
#घोषणा ADP8860_EXT_FEATURES
#घोषणा ADP8860_USE_LEDS

#घोषणा ADP8860_MFDVID 0x00 /* Manufacturer and device ID */
#घोषणा ADP8860_MDCR 0x01 /* Device mode and status */
#घोषणा ADP8860_MDCR2 0x02 /* Device mode and Status Register 2 */
#घोषणा ADP8860_INTR_EN 0x03 /* Interrupts enable */
#घोषणा ADP8860_CFGR 0x04 /* Configuration रेजिस्टर */
#घोषणा ADP8860_BLSEN 0x05 /* Sink enable backlight or independent */
#घोषणा ADP8860_BLOFF 0x06 /* Backlight off समयout */
#घोषणा ADP8860_BLDIM 0x07 /* Backlight dim समयout */
#घोषणा ADP8860_BLFR 0x08 /* Backlight fade in and out rates */
#घोषणा ADP8860_BLMX1 0x09 /* Backlight (Brightness Level 1-daylight) maximum current */
#घोषणा ADP8860_BLDM1 0x0A /* Backlight (Brightness Level 1-daylight) dim current */
#घोषणा ADP8860_BLMX2 0x0B /* Backlight (Brightness Level 2-office) maximum current */
#घोषणा ADP8860_BLDM2 0x0C /* Backlight (Brightness Level 2-office) dim current */
#घोषणा ADP8860_BLMX3 0x0D /* Backlight (Brightness Level 3-dark) maximum current */
#घोषणा ADP8860_BLDM3 0x0E /* Backlight (Brightness Level 3-dark) dim current */
#घोषणा ADP8860_ISCFR 0x0F /* Independent sink current fade control रेजिस्टर */
#घोषणा ADP8860_ISCC 0x10 /* Independent sink current control रेजिस्टर */
#घोषणा ADP8860_ISCT1 0x11 /* Independent Sink Current Timer Register LED[7:5] */
#घोषणा ADP8860_ISCT2 0x12 /* Independent Sink Current Timer Register LED[4:1] */
#घोषणा ADP8860_ISCF 0x13 /* Independent sink current fade रेजिस्टर */
#घोषणा ADP8860_ISC7 0x14 /* Independent Sink Current LED7 */
#घोषणा ADP8860_ISC6 0x15 /* Independent Sink Current LED6 */
#घोषणा ADP8860_ISC5 0x16 /* Independent Sink Current LED5 */
#घोषणा ADP8860_ISC4 0x17 /* Independent Sink Current LED4 */
#घोषणा ADP8860_ISC3 0x18 /* Independent Sink Current LED3 */
#घोषणा ADP8860_ISC2 0x19 /* Independent Sink Current LED2 */
#घोषणा ADP8860_ISC1 0x1A /* Independent Sink Current LED1 */
#घोषणा ADP8860_CCFG 0x1B /* Comparator configuration */
#घोषणा ADP8860_CCFG2 0x1C /* Second comparator configuration */
#घोषणा ADP8860_L2_TRP 0x1D /* L2 comparator reference */
#घोषणा ADP8860_L2_HYS 0x1E /* L2 hysteresis */
#घोषणा ADP8860_L3_TRP 0x1F /* L3 comparator reference */
#घोषणा ADP8860_L3_HYS 0x20 /* L3 hysteresis */
#घोषणा ADP8860_PH1LEVL 0x21 /* First phototransistor ambient light level-low byte रेजिस्टर */
#घोषणा ADP8860_PH1LEVH 0x22 /* First phototransistor ambient light level-high byte रेजिस्टर */
#घोषणा ADP8860_PH2LEVL 0x23 /* Second phototransistor ambient light level-low byte रेजिस्टर */
#घोषणा ADP8860_PH2LEVH 0x24 /* Second phototransistor ambient light level-high byte रेजिस्टर */

#घोषणा ADP8860_MANUFID		0x0  /* Analog Devices ADP8860 Manufacturer ID */
#घोषणा ADP8861_MANUFID		0x4  /* Analog Devices ADP8861 Manufacturer ID */
#घोषणा ADP8863_MANUFID		0x2  /* Analog Devices ADP8863 Manufacturer ID */

#घोषणा ADP8860_DEVID(x)	((x) & 0xF)
#घोषणा ADP8860_MANID(x)	((x) >> 4)

/* MDCR Device mode and status */
#घोषणा INT_CFG			(1 << 6)
#घोषणा NSTBY			(1 << 5)
#घोषणा DIM_EN			(1 << 4)
#घोषणा GDWN_DIS		(1 << 3)
#घोषणा SIS_EN			(1 << 2)
#घोषणा CMP_AUTOEN		(1 << 1)
#घोषणा BLEN			(1 << 0)

/* ADP8860_CCFG Main ALS comparator level enable */
#घोषणा L3_EN			(1 << 1)
#घोषणा L2_EN			(1 << 0)

#घोषणा CFGR_BLV_SHIFT		3
#घोषणा CFGR_BLV_MASK		0x3
#घोषणा ADP8860_FLAG_LED_MASK	0xFF

#घोषणा FADE_VAL(in, out)	((0xF & (in)) | ((0xF & (out)) << 4))
#घोषणा BL_CFGR_VAL(law, blv)	((((blv) & CFGR_BLV_MASK) << CFGR_BLV_SHIFT) | ((0x3 & (law)) << 1))
#घोषणा ALS_CCFG_VAL(filt)	((0x7 & filt) << 5)

क्रमागत अणु
	adp8860,
	adp8861,
	adp8863
पूर्ण;

काष्ठा adp8860_led अणु
	काष्ठा led_classdev	cdev;
	काष्ठा work_काष्ठा	work;
	काष्ठा i2c_client	*client;
	क्रमागत led_brightness	new_brightness;
	पूर्णांक			id;
	पूर्णांक			flags;
पूर्ण;

काष्ठा adp8860_bl अणु
	काष्ठा i2c_client *client;
	काष्ठा backlight_device *bl;
	काष्ठा adp8860_led *led;
	काष्ठा adp8860_backlight_platक्रमm_data *pdata;
	काष्ठा mutex lock;
	अचिन्हित दीर्घ cached_daylight_max;
	पूर्णांक id;
	पूर्णांक revid;
	पूर्णांक current_brightness;
	अचिन्हित en_ambl_sens:1;
	अचिन्हित gdwn_dis:1;
पूर्ण;

अटल पूर्णांक adp8860_पढ़ो(काष्ठा i2c_client *client, पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed reading at 0x%02x\n", reg);
		वापस ret;
	पूर्ण

	*val = (uपूर्णांक8_t)ret;
	वापस 0;
पूर्ण

अटल पूर्णांक adp8860_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक adp8860_set_bits(काष्ठा i2c_client *client, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा adp8860_bl *data = i2c_get_clientdata(client);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	mutex_lock(&data->lock);

	ret = adp8860_पढ़ो(client, reg, &reg_val);

	अगर (!ret && ((reg_val & bit_mask) != bit_mask)) अणु
		reg_val |= bit_mask;
		ret = adp8860_ग_लिखो(client, reg, reg_val);
	पूर्ण

	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adp8860_clr_bits(काष्ठा i2c_client *client, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा adp8860_bl *data = i2c_get_clientdata(client);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	mutex_lock(&data->lock);

	ret = adp8860_पढ़ो(client, reg, &reg_val);

	अगर (!ret && (reg_val & bit_mask)) अणु
		reg_val &= ~bit_mask;
		ret = adp8860_ग_लिखो(client, reg, reg_val);
	पूर्ण

	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

/*
 * Independent sink / LED
 */
#अगर defined(ADP8860_USE_LEDS)
अटल व्योम adp8860_led_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adp8860_led *led = container_of(work, काष्ठा adp8860_led, work);

	adp8860_ग_लिखो(led->client, ADP8860_ISC1 - led->id + 1,
			 led->new_brightness >> 1);
पूर्ण

अटल व्योम adp8860_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा adp8860_led *led;

	led = container_of(led_cdev, काष्ठा adp8860_led, cdev);
	led->new_brightness = value;
	schedule_work(&led->work);
पूर्ण

अटल पूर्णांक adp8860_led_setup(काष्ठा adp8860_led *led)
अणु
	काष्ठा i2c_client *client = led->client;
	पूर्णांक ret = 0;

	ret = adp8860_ग_लिखो(client, ADP8860_ISC1 - led->id + 1, 0);
	ret |= adp8860_set_bits(client, ADP8860_ISCC, 1 << (led->id - 1));

	अगर (led->id > 4)
		ret |= adp8860_set_bits(client, ADP8860_ISCT1,
				(led->flags & 0x3) << ((led->id - 5) * 2));
	अन्यथा
		ret |= adp8860_set_bits(client, ADP8860_ISCT2,
				(led->flags & 0x3) << ((led->id - 1) * 2));

	वापस ret;
पूर्ण

अटल पूर्णांक adp8860_led_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा adp8860_backlight_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	काष्ठा adp8860_bl *data = i2c_get_clientdata(client);
	काष्ठा adp8860_led *led, *led_dat;
	काष्ठा led_info *cur_led;
	पूर्णांक ret, i;

	led = devm_kसुस्मृति(&client->dev, pdata->num_leds, माप(*led),
				GFP_KERNEL);
	अगर (led == शून्य)
		वापस -ENOMEM;

	ret = adp8860_ग_लिखो(client, ADP8860_ISCFR, pdata->led_fade_law);
	ret = adp8860_ग_लिखो(client, ADP8860_ISCT1,
			(pdata->led_on_समय & 0x3) << 6);
	ret |= adp8860_ग_लिखो(client, ADP8860_ISCF,
			FADE_VAL(pdata->led_fade_in, pdata->led_fade_out));

	अगर (ret) अणु
		dev_err(&client->dev, "failed to write\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < pdata->num_leds; ++i) अणु
		cur_led = &pdata->leds[i];
		led_dat = &led[i];

		led_dat->id = cur_led->flags & ADP8860_FLAG_LED_MASK;

		अगर (led_dat->id > 7 || led_dat->id < 1) अणु
			dev_err(&client->dev, "Invalid LED ID %d\n",
				led_dat->id);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (pdata->bl_led_assign & (1 << (led_dat->id - 1))) अणु
			dev_err(&client->dev, "LED %d used by Backlight\n",
				led_dat->id);
			ret = -EBUSY;
			जाओ err;
		पूर्ण

		led_dat->cdev.name = cur_led->name;
		led_dat->cdev.शेष_trigger = cur_led->शेष_trigger;
		led_dat->cdev.brightness_set = adp8860_led_set;
		led_dat->cdev.brightness = LED_OFF;
		led_dat->flags = cur_led->flags >> FLAG_OFFT_SHIFT;
		led_dat->client = client;
		led_dat->new_brightness = LED_OFF;
		INIT_WORK(&led_dat->work, adp8860_led_work);

		ret = led_classdev_रेजिस्टर(&client->dev, &led_dat->cdev);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to register LED %d\n",
				led_dat->id);
			जाओ err;
		पूर्ण

		ret = adp8860_led_setup(led_dat);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to write\n");
			i++;
			जाओ err;
		पूर्ण
	पूर्ण

	data->led = led;

	वापस 0;

 err:
	क्रम (i = i - 1; i >= 0; --i) अणु
		led_classdev_unरेजिस्टर(&led[i].cdev);
		cancel_work_sync(&led[i].work);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adp8860_led_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adp8860_backlight_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	काष्ठा adp8860_bl *data = i2c_get_clientdata(client);
	पूर्णांक i;

	क्रम (i = 0; i < pdata->num_leds; i++) अणु
		led_classdev_unरेजिस्टर(&data->led[i].cdev);
		cancel_work_sync(&data->led[i].work);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक adp8860_led_probe(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक adp8860_led_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक adp8860_bl_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा adp8860_bl *data = bl_get_data(bl);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret = 0;

	अगर (data->en_ambl_sens) अणु
		अगर ((brightness > 0) && (brightness < ADP8860_MAX_BRIGHTNESS)) अणु
			/* Disable Ambient Light स्वतः adjust */
			ret |= adp8860_clr_bits(client, ADP8860_MDCR,
					CMP_AUTOEN);
			ret |= adp8860_ग_लिखो(client, ADP8860_BLMX1, brightness);
		पूर्ण अन्यथा अणु
			/*
			 * MAX_BRIGHTNESS -> Enable Ambient Light स्वतः adjust
			 * restore daylight l1 sysfs brightness
			 */
			ret |= adp8860_ग_लिखो(client, ADP8860_BLMX1,
					 data->cached_daylight_max);
			ret |= adp8860_set_bits(client, ADP8860_MDCR,
					 CMP_AUTOEN);
		पूर्ण
	पूर्ण अन्यथा
		ret |= adp8860_ग_लिखो(client, ADP8860_BLMX1, brightness);

	अगर (data->current_brightness && brightness == 0)
		ret |= adp8860_set_bits(client,
				ADP8860_MDCR, DIM_EN);
	अन्यथा अगर (data->current_brightness == 0 && brightness)
		ret |= adp8860_clr_bits(client,
				ADP8860_MDCR, DIM_EN);

	अगर (!ret)
		data->current_brightness = brightness;

	वापस ret;
पूर्ण

अटल पूर्णांक adp8860_bl_update_status(काष्ठा backlight_device *bl)
अणु
	वापस adp8860_bl_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक adp8860_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा adp8860_bl *data = bl_get_data(bl);

	वापस data->current_brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops adp8860_bl_ops = अणु
	.update_status	= adp8860_bl_update_status,
	.get_brightness	= adp8860_bl_get_brightness,
पूर्ण;

अटल पूर्णांक adp8860_bl_setup(काष्ठा backlight_device *bl)
अणु
	काष्ठा adp8860_bl *data = bl_get_data(bl);
	काष्ठा i2c_client *client = data->client;
	काष्ठा adp8860_backlight_platक्रमm_data *pdata = data->pdata;
	पूर्णांक ret = 0;

	ret |= adp8860_ग_लिखो(client, ADP8860_BLSEN, ~pdata->bl_led_assign);
	ret |= adp8860_ग_लिखो(client, ADP8860_BLMX1, pdata->l1_daylight_max);
	ret |= adp8860_ग_लिखो(client, ADP8860_BLDM1, pdata->l1_daylight_dim);

	अगर (data->en_ambl_sens) अणु
		data->cached_daylight_max = pdata->l1_daylight_max;
		ret |= adp8860_ग_लिखो(client, ADP8860_BLMX2,
						pdata->l2_office_max);
		ret |= adp8860_ग_लिखो(client, ADP8860_BLDM2,
						pdata->l2_office_dim);
		ret |= adp8860_ग_लिखो(client, ADP8860_BLMX3,
						pdata->l3_dark_max);
		ret |= adp8860_ग_लिखो(client, ADP8860_BLDM3,
						pdata->l3_dark_dim);

		ret |= adp8860_ग_लिखो(client, ADP8860_L2_TRP, pdata->l2_trip);
		ret |= adp8860_ग_लिखो(client, ADP8860_L2_HYS, pdata->l2_hyst);
		ret |= adp8860_ग_लिखो(client, ADP8860_L3_TRP, pdata->l3_trip);
		ret |= adp8860_ग_लिखो(client, ADP8860_L3_HYS, pdata->l3_hyst);
		ret |= adp8860_ग_लिखो(client, ADP8860_CCFG, L2_EN | L3_EN |
						ALS_CCFG_VAL(pdata->abml_filt));
	पूर्ण

	ret |= adp8860_ग_लिखो(client, ADP8860_CFGR,
			BL_CFGR_VAL(pdata->bl_fade_law, 0));

	ret |= adp8860_ग_लिखो(client, ADP8860_BLFR, FADE_VAL(pdata->bl_fade_in,
			pdata->bl_fade_out));

	ret |= adp8860_set_bits(client, ADP8860_MDCR, BLEN | DIM_EN | NSTBY |
			(data->gdwn_dis ? GDWN_DIS : 0));

	वापस ret;
पूर्ण

अटल sमाप_प्रकार adp8860_show(काष्ठा device *dev, अक्षर *buf, पूर्णांक reg)
अणु
	काष्ठा adp8860_bl *data = dev_get_drvdata(dev);
	पूर्णांक error;
	uपूर्णांक8_t reg_val;

	mutex_lock(&data->lock);
	error = adp8860_पढ़ो(data->client, reg, &reg_val);
	mutex_unlock(&data->lock);

	अगर (error < 0)
		वापस error;

	वापस प्र_लिखो(buf, "%u\n", reg_val);
पूर्ण

अटल sमाप_प्रकार adp8860_store(काष्ठा device *dev, स्थिर अक्षर *buf,
			 माप_प्रकार count, पूर्णांक reg)
अणु
	काष्ठा adp8860_bl *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->lock);
	adp8860_ग_लिखो(data->client, reg, val);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार adp8860_bl_l3_dark_max_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8860_show(dev, buf, ADP8860_BLMX3);
पूर्ण

अटल sमाप_प्रकार adp8860_bl_l3_dark_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8860_store(dev, buf, count, ADP8860_BLMX3);
पूर्ण

अटल DEVICE_ATTR(l3_dark_max, 0664, adp8860_bl_l3_dark_max_show,
			adp8860_bl_l3_dark_max_store);

अटल sमाप_प्रकार adp8860_bl_l2_office_max_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8860_show(dev, buf, ADP8860_BLMX2);
पूर्ण

अटल sमाप_प्रकार adp8860_bl_l2_office_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8860_store(dev, buf, count, ADP8860_BLMX2);
पूर्ण
अटल DEVICE_ATTR(l2_office_max, 0664, adp8860_bl_l2_office_max_show,
			adp8860_bl_l2_office_max_store);

अटल sमाप_प्रकार adp8860_bl_l1_daylight_max_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8860_show(dev, buf, ADP8860_BLMX1);
पूर्ण

अटल sमाप_प्रकार adp8860_bl_l1_daylight_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adp8860_bl *data = dev_get_drvdata(dev);
	पूर्णांक ret = kम_से_अदीर्घ(buf, 10, &data->cached_daylight_max);

	अगर (ret)
		वापस ret;

	वापस adp8860_store(dev, buf, count, ADP8860_BLMX1);
पूर्ण
अटल DEVICE_ATTR(l1_daylight_max, 0664, adp8860_bl_l1_daylight_max_show,
			adp8860_bl_l1_daylight_max_store);

अटल sमाप_प्रकार adp8860_bl_l3_dark_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8860_show(dev, buf, ADP8860_BLDM3);
पूर्ण

अटल sमाप_प्रकार adp8860_bl_l3_dark_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8860_store(dev, buf, count, ADP8860_BLDM3);
पूर्ण
अटल DEVICE_ATTR(l3_dark_dim, 0664, adp8860_bl_l3_dark_dim_show,
			adp8860_bl_l3_dark_dim_store);

अटल sमाप_प्रकार adp8860_bl_l2_office_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8860_show(dev, buf, ADP8860_BLDM2);
पूर्ण

अटल sमाप_प्रकार adp8860_bl_l2_office_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8860_store(dev, buf, count, ADP8860_BLDM2);
पूर्ण
अटल DEVICE_ATTR(l2_office_dim, 0664, adp8860_bl_l2_office_dim_show,
			adp8860_bl_l2_office_dim_store);

अटल sमाप_प्रकार adp8860_bl_l1_daylight_dim_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8860_show(dev, buf, ADP8860_BLDM1);
पूर्ण

अटल sमाप_प्रकार adp8860_bl_l1_daylight_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8860_store(dev, buf, count, ADP8860_BLDM1);
पूर्ण
अटल DEVICE_ATTR(l1_daylight_dim, 0664, adp8860_bl_l1_daylight_dim_show,
			adp8860_bl_l1_daylight_dim_store);

#अगर_घोषित ADP8860_EXT_FEATURES
अटल sमाप_प्रकार adp8860_bl_ambient_light_level_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adp8860_bl *data = dev_get_drvdata(dev);
	पूर्णांक error;
	uपूर्णांक8_t reg_val;
	uपूर्णांक16_t ret_val;

	mutex_lock(&data->lock);
	error = adp8860_पढ़ो(data->client, ADP8860_PH1LEVL, &reg_val);
	अगर (!error) अणु
		ret_val = reg_val;
		error = adp8860_पढ़ो(data->client, ADP8860_PH1LEVH, &reg_val);
	पूर्ण
	mutex_unlock(&data->lock);

	अगर (error)
		वापस error;

	/* Return 13-bit conversion value क्रम the first light sensor */
	ret_val += (reg_val & 0x1F) << 8;

	वापस प्र_लिखो(buf, "%u\n", ret_val);
पूर्ण
अटल DEVICE_ATTR(ambient_light_level, 0444,
		adp8860_bl_ambient_light_level_show, शून्य);

अटल sमाप_प्रकार adp8860_bl_ambient_light_zone_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adp8860_bl *data = dev_get_drvdata(dev);
	पूर्णांक error;
	uपूर्णांक8_t reg_val;

	mutex_lock(&data->lock);
	error = adp8860_पढ़ो(data->client, ADP8860_CFGR, &reg_val);
	mutex_unlock(&data->lock);

	अगर (error < 0)
		वापस error;

	वापस प्र_लिखो(buf, "%u\n",
		((reg_val >> CFGR_BLV_SHIFT) & CFGR_BLV_MASK) + 1);
पूर्ण

अटल sमाप_प्रकार adp8860_bl_ambient_light_zone_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adp8860_bl *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val == 0) अणु
		/* Enable स्वतःmatic ambient light sensing */
		adp8860_set_bits(data->client, ADP8860_MDCR, CMP_AUTOEN);
	पूर्ण अन्यथा अगर ((val > 0) && (val <= 3)) अणु
		/* Disable स्वतःmatic ambient light sensing */
		adp8860_clr_bits(data->client, ADP8860_MDCR, CMP_AUTOEN);

		/* Set user supplied ambient light zone */
		mutex_lock(&data->lock);
		ret = adp8860_पढ़ो(data->client, ADP8860_CFGR, &reg_val);
		अगर (!ret) अणु
			reg_val &= ~(CFGR_BLV_MASK << CFGR_BLV_SHIFT);
			reg_val |= (val - 1) << CFGR_BLV_SHIFT;
			adp8860_ग_लिखो(data->client, ADP8860_CFGR, reg_val);
		पूर्ण
		mutex_unlock(&data->lock);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(ambient_light_zone, 0664,
		adp8860_bl_ambient_light_zone_show,
		adp8860_bl_ambient_light_zone_store);
#पूर्ण_अगर

अटल काष्ठा attribute *adp8860_bl_attributes[] = अणु
	&dev_attr_l3_dark_max.attr,
	&dev_attr_l3_dark_dim.attr,
	&dev_attr_l2_office_max.attr,
	&dev_attr_l2_office_dim.attr,
	&dev_attr_l1_daylight_max.attr,
	&dev_attr_l1_daylight_dim.attr,
#अगर_घोषित ADP8860_EXT_FEATURES
	&dev_attr_ambient_light_level.attr,
	&dev_attr_ambient_light_zone.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adp8860_bl_attr_group = अणु
	.attrs = adp8860_bl_attributes,
पूर्ण;

अटल पूर्णांक adp8860_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा backlight_device *bl;
	काष्ठा adp8860_bl *data;
	काष्ठा adp8860_backlight_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	काष्ठा backlight_properties props;
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		वापस -EIO;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&client->dev, "no platform data?\n");
		वापस -EINVAL;
	पूर्ण

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	ret = adp8860_पढ़ो(client, ADP8860_MFDVID, &reg_val);
	अगर (ret < 0)
		वापस ret;

	चयन (ADP8860_MANID(reg_val)) अणु
	हाल ADP8863_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
		fallthrough;
	हाल ADP8860_MANUFID:
		data->en_ambl_sens = !!pdata->en_ambl_sens;
		अवरोध;
	हाल ADP8861_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
		अवरोध;
	शेष:
		dev_err(&client->dev, "failed to probe\n");
		वापस -ENODEV;
	पूर्ण

	/* It's confirmed that the DEVID field is actually a REVID */

	data->revid = ADP8860_DEVID(reg_val);
	data->client = client;
	data->pdata = pdata;
	data->id = id->driver_data;
	data->current_brightness = 0;
	i2c_set_clientdata(client, data);

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = ADP8860_MAX_BRIGHTNESS;

	mutex_init(&data->lock);

	bl = devm_backlight_device_रेजिस्टर(&client->dev,
				dev_driver_string(&client->dev),
				&client->dev, data, &adp8860_bl_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&client->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	bl->props.brightness = ADP8860_MAX_BRIGHTNESS;

	data->bl = bl;

	अगर (data->en_ambl_sens)
		ret = sysfs_create_group(&bl->dev.kobj,
			&adp8860_bl_attr_group);

	अगर (ret) अणु
		dev_err(&client->dev, "failed to register sysfs\n");
		वापस ret;
	पूर्ण

	ret = adp8860_bl_setup(bl);
	अगर (ret) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	backlight_update_status(bl);

	dev_info(&client->dev, "%s Rev.%d Backlight\n",
		client->name, data->revid);

	अगर (pdata->num_leds)
		adp8860_led_probe(client);

	वापस 0;

out:
	अगर (data->en_ambl_sens)
		sysfs_हटाओ_group(&data->bl->dev.kobj,
			&adp8860_bl_attr_group);

	वापस ret;
पूर्ण

अटल पूर्णांक adp8860_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adp8860_bl *data = i2c_get_clientdata(client);

	adp8860_clr_bits(client, ADP8860_MDCR, NSTBY);

	अगर (data->led)
		adp8860_led_हटाओ(client);

	अगर (data->en_ambl_sens)
		sysfs_हटाओ_group(&data->bl->dev.kobj,
			&adp8860_bl_attr_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक adp8860_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	adp8860_clr_bits(client, ADP8860_MDCR, NSTBY);

	वापस 0;
पूर्ण

अटल पूर्णांक adp8860_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	adp8860_set_bits(client, ADP8860_MDCR, NSTBY | BLEN);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(adp8860_i2c_pm_ops, adp8860_i2c_suspend,
			adp8860_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id adp8860_id[] = अणु
	अणु "adp8860", adp8860 पूर्ण,
	अणु "adp8861", adp8861 पूर्ण,
	अणु "adp8863", adp8863 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adp8860_id);

अटल काष्ठा i2c_driver adp8860_driver = अणु
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm	= &adp8860_i2c_pm_ops,
	पूर्ण,
	.probe    = adp8860_probe,
	.हटाओ   = adp8860_हटाओ,
	.id_table = adp8860_id,
पूर्ण;

module_i2c_driver(adp8860_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("ADP8860 Backlight driver");
