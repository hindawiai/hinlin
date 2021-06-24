<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Backlight driver क्रम Analog Devices ADP8870 Backlight Devices
 *
 * Copyright 2009-2011 Analog Devices Inc.
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
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/adp8870.h>
#घोषणा ADP8870_EXT_FEATURES
#घोषणा ADP8870_USE_LEDS


#घोषणा ADP8870_MFDVID	0x00  /* Manufacturer and device ID */
#घोषणा ADP8870_MDCR	0x01  /* Device mode and status */
#घोषणा ADP8870_INT_STAT 0x02  /* Interrupts status */
#घोषणा ADP8870_INT_EN	0x03  /* Interrupts enable */
#घोषणा ADP8870_CFGR	0x04  /* Configuration रेजिस्टर */
#घोषणा ADP8870_BLSEL	0x05  /* Sink enable backlight or independent */
#घोषणा ADP8870_PWMLED	0x06  /* PWM Enable Selection Register */
#घोषणा ADP8870_BLOFF	0x07  /* Backlight off समयout */
#घोषणा ADP8870_BLDIM	0x08  /* Backlight dim समयout */
#घोषणा ADP8870_BLFR	0x09  /* Backlight fade in and out rates */
#घोषणा ADP8870_BLMX1	0x0A  /* Backlight (Brightness Level 1-daylight) maximum current */
#घोषणा ADP8870_BLDM1	0x0B  /* Backlight (Brightness Level 1-daylight) dim current */
#घोषणा ADP8870_BLMX2	0x0C  /* Backlight (Brightness Level 2-bright) maximum current */
#घोषणा ADP8870_BLDM2	0x0D  /* Backlight (Brightness Level 2-bright) dim current */
#घोषणा ADP8870_BLMX3	0x0E  /* Backlight (Brightness Level 3-office) maximum current */
#घोषणा ADP8870_BLDM3	0x0F  /* Backlight (Brightness Level 3-office) dim current */
#घोषणा ADP8870_BLMX4	0x10  /* Backlight (Brightness Level 4-inकरोor) maximum current */
#घोषणा ADP8870_BLDM4	0x11  /* Backlight (Brightness Level 4-inकरोor) dim current */
#घोषणा ADP8870_BLMX5	0x12  /* Backlight (Brightness Level 5-dark) maximum current */
#घोषणा ADP8870_BLDM5	0x13  /* Backlight (Brightness Level 5-dark) dim current */
#घोषणा ADP8870_ISCLAW	0x1A  /* Independent sink current fade law रेजिस्टर */
#घोषणा ADP8870_ISCC	0x1B  /* Independent sink current control रेजिस्टर */
#घोषणा ADP8870_ISCT1	0x1C  /* Independent Sink Current Timer Register LED[7:5] */
#घोषणा ADP8870_ISCT2	0x1D  /* Independent Sink Current Timer Register LED[4:1] */
#घोषणा ADP8870_ISCF	0x1E  /* Independent sink current fade रेजिस्टर */
#घोषणा ADP8870_ISC1	0x1F  /* Independent Sink Current LED1 */
#घोषणा ADP8870_ISC2	0x20  /* Independent Sink Current LED2 */
#घोषणा ADP8870_ISC3	0x21  /* Independent Sink Current LED3 */
#घोषणा ADP8870_ISC4	0x22  /* Independent Sink Current LED4 */
#घोषणा ADP8870_ISC5	0x23  /* Independent Sink Current LED5 */
#घोषणा ADP8870_ISC6	0x24  /* Independent Sink Current LED6 */
#घोषणा ADP8870_ISC7	0x25  /* Independent Sink Current LED7 (Brightness Level 1-daylight) */
#घोषणा ADP8870_ISC7_L2	0x26  /* Independent Sink Current LED7 (Brightness Level 2-bright) */
#घोषणा ADP8870_ISC7_L3	0x27  /* Independent Sink Current LED7 (Brightness Level 3-office) */
#घोषणा ADP8870_ISC7_L4	0x28  /* Independent Sink Current LED7 (Brightness Level 4-inकरोor) */
#घोषणा ADP8870_ISC7_L5	0x29  /* Independent Sink Current LED7 (Brightness Level 5-dark) */
#घोषणा ADP8870_CMP_CTL	0x2D  /* ALS Comparator Control Register */
#घोषणा ADP8870_ALS1_EN	0x2E  /* Main ALS comparator level enable */
#घोषणा ADP8870_ALS2_EN	0x2F  /* Second ALS comparator level enable */
#घोषणा ADP8870_ALS1_STAT 0x30  /* Main ALS Comparator Status Register */
#घोषणा ADP8870_ALS2_STAT 0x31  /* Second ALS Comparator Status Register */
#घोषणा ADP8870_L2TRP	0x32  /* L2 comparator reference */
#घोषणा ADP8870_L2HYS	0x33  /* L2 hysteresis */
#घोषणा ADP8870_L3TRP	0x34  /* L3 comparator reference */
#घोषणा ADP8870_L3HYS	0x35  /* L3 hysteresis */
#घोषणा ADP8870_L4TRP	0x36  /* L4 comparator reference */
#घोषणा ADP8870_L4HYS	0x37  /* L4 hysteresis */
#घोषणा ADP8870_L5TRP	0x38  /* L5 comparator reference */
#घोषणा ADP8870_L5HYS	0x39  /* L5 hysteresis */
#घोषणा ADP8870_PH1LEVL	0x40  /* First phototransistor ambient light level-low byte रेजिस्टर */
#घोषणा ADP8870_PH1LEVH	0x41  /* First phototransistor ambient light level-high byte रेजिस्टर */
#घोषणा ADP8870_PH2LEVL	0x42  /* Second phototransistor ambient light level-low byte रेजिस्टर */
#घोषणा ADP8870_PH2LEVH	0x43  /* Second phototransistor ambient light level-high byte रेजिस्टर */

#घोषणा ADP8870_MANUFID		0x3  /* Analog Devices AD8870 Manufacturer and device ID */
#घोषणा ADP8870_DEVID(x)	((x) & 0xF)
#घोषणा ADP8870_MANID(x)	((x) >> 4)

/* MDCR Device mode and status */
#घोषणा D7ALSEN			(1 << 7)
#घोषणा INT_CFG			(1 << 6)
#घोषणा NSTBY			(1 << 5)
#घोषणा DIM_EN			(1 << 4)
#घोषणा GDWN_DIS		(1 << 3)
#घोषणा SIS_EN			(1 << 2)
#घोषणा CMP_AUTOEN		(1 << 1)
#घोषणा BLEN			(1 << 0)

/* ADP8870_ALS1_EN Main ALS comparator level enable */
#घोषणा L5_EN			(1 << 3)
#घोषणा L4_EN			(1 << 2)
#घोषणा L3_EN			(1 << 1)
#घोषणा L2_EN			(1 << 0)

#घोषणा CFGR_BLV_SHIFT		3
#घोषणा CFGR_BLV_MASK		0x7
#घोषणा ADP8870_FLAG_LED_MASK	0xFF

#घोषणा FADE_VAL(in, out)	((0xF & (in)) | ((0xF & (out)) << 4))
#घोषणा BL_CFGR_VAL(law, blv)	((((blv) & CFGR_BLV_MASK) << CFGR_BLV_SHIFT) | ((0x3 & (law)) << 1))
#घोषणा ALS_CMPR_CFG_VAL(filt)	((0x7 & (filt)) << 1)

काष्ठा adp8870_bl अणु
	काष्ठा i2c_client *client;
	काष्ठा backlight_device *bl;
	काष्ठा adp8870_led *led;
	काष्ठा adp8870_backlight_platक्रमm_data *pdata;
	काष्ठा mutex lock;
	अचिन्हित दीर्घ cached_daylight_max;
	पूर्णांक id;
	पूर्णांक revid;
	पूर्णांक current_brightness;
पूर्ण;

काष्ठा adp8870_led अणु
	काष्ठा led_classdev	cdev;
	काष्ठा work_काष्ठा	work;
	काष्ठा i2c_client	*client;
	क्रमागत led_brightness	new_brightness;
	पूर्णांक			id;
	पूर्णांक			flags;
पूर्ण;

अटल पूर्णांक adp8870_पढ़ो(काष्ठा i2c_client *client, पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed reading at 0x%02x\n", reg);
		वापस ret;
	पूर्ण

	*val = ret;
	वापस 0;
पूर्ण


अटल पूर्णांक adp8870_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);

	अगर (ret)
		dev_err(&client->dev, "failed to write\n");

	वापस ret;
पूर्ण

अटल पूर्णांक adp8870_set_bits(काष्ठा i2c_client *client, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा adp8870_bl *data = i2c_get_clientdata(client);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	mutex_lock(&data->lock);

	ret = adp8870_पढ़ो(client, reg, &reg_val);

	अगर (!ret && ((reg_val & bit_mask) != bit_mask)) अणु
		reg_val |= bit_mask;
		ret = adp8870_ग_लिखो(client, reg, reg_val);
	पूर्ण

	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adp8870_clr_bits(काष्ठा i2c_client *client, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा adp8870_bl *data = i2c_get_clientdata(client);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	mutex_lock(&data->lock);

	ret = adp8870_पढ़ो(client, reg, &reg_val);

	अगर (!ret && (reg_val & bit_mask)) अणु
		reg_val &= ~bit_mask;
		ret = adp8870_ग_लिखो(client, reg, reg_val);
	पूर्ण

	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

/*
 * Independent sink / LED
 */
#अगर defined(ADP8870_USE_LEDS)
अटल व्योम adp8870_led_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adp8870_led *led = container_of(work, काष्ठा adp8870_led, work);

	adp8870_ग_लिखो(led->client, ADP8870_ISC1 + led->id - 1,
			 led->new_brightness >> 1);
पूर्ण

अटल व्योम adp8870_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा adp8870_led *led;

	led = container_of(led_cdev, काष्ठा adp8870_led, cdev);
	led->new_brightness = value;
	/*
	 * Use workqueue क्रम IO since I2C operations can sleep.
	 */
	schedule_work(&led->work);
पूर्ण

अटल पूर्णांक adp8870_led_setup(काष्ठा adp8870_led *led)
अणु
	काष्ठा i2c_client *client = led->client;
	पूर्णांक ret = 0;

	ret = adp8870_ग_लिखो(client, ADP8870_ISC1 + led->id - 1, 0);
	अगर (ret)
		वापस ret;

	ret = adp8870_set_bits(client, ADP8870_ISCC, 1 << (led->id - 1));
	अगर (ret)
		वापस ret;

	अगर (led->id > 4)
		ret = adp8870_set_bits(client, ADP8870_ISCT1,
				(led->flags & 0x3) << ((led->id - 5) * 2));
	अन्यथा
		ret = adp8870_set_bits(client, ADP8870_ISCT2,
				(led->flags & 0x3) << ((led->id - 1) * 2));

	वापस ret;
पूर्ण

अटल पूर्णांक adp8870_led_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा adp8870_backlight_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	काष्ठा adp8870_bl *data = i2c_get_clientdata(client);
	काष्ठा adp8870_led *led, *led_dat;
	काष्ठा led_info *cur_led;
	पूर्णांक ret, i;

	led = devm_kसुस्मृति(&client->dev, pdata->num_leds, माप(*led),
				GFP_KERNEL);
	अगर (led == शून्य)
		वापस -ENOMEM;

	ret = adp8870_ग_लिखो(client, ADP8870_ISCLAW, pdata->led_fade_law);
	अगर (ret)
		वापस ret;

	ret = adp8870_ग_लिखो(client, ADP8870_ISCT1,
			(pdata->led_on_समय & 0x3) << 6);
	अगर (ret)
		वापस ret;

	ret = adp8870_ग_लिखो(client, ADP8870_ISCF,
			FADE_VAL(pdata->led_fade_in, pdata->led_fade_out));
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < pdata->num_leds; ++i) अणु
		cur_led = &pdata->leds[i];
		led_dat = &led[i];

		led_dat->id = cur_led->flags & ADP8870_FLAG_LED_MASK;

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
		led_dat->cdev.brightness_set = adp8870_led_set;
		led_dat->cdev.brightness = LED_OFF;
		led_dat->flags = cur_led->flags >> FLAG_OFFT_SHIFT;
		led_dat->client = client;
		led_dat->new_brightness = LED_OFF;
		INIT_WORK(&led_dat->work, adp8870_led_work);

		ret = led_classdev_रेजिस्टर(&client->dev, &led_dat->cdev);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to register LED %d\n",
				led_dat->id);
			जाओ err;
		पूर्ण

		ret = adp8870_led_setup(led_dat);
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

अटल पूर्णांक adp8870_led_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adp8870_backlight_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	काष्ठा adp8870_bl *data = i2c_get_clientdata(client);
	पूर्णांक i;

	क्रम (i = 0; i < pdata->num_leds; i++) अणु
		led_classdev_unरेजिस्टर(&data->led[i].cdev);
		cancel_work_sync(&data->led[i].work);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक adp8870_led_probe(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक adp8870_led_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक adp8870_bl_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा adp8870_bl *data = bl_get_data(bl);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret = 0;

	अगर (data->pdata->en_ambl_sens) अणु
		अगर ((brightness > 0) && (brightness < ADP8870_MAX_BRIGHTNESS)) अणु
			/* Disable Ambient Light स्वतः adjust */
			ret = adp8870_clr_bits(client, ADP8870_MDCR,
					CMP_AUTOEN);
			अगर (ret)
				वापस ret;
			ret = adp8870_ग_लिखो(client, ADP8870_BLMX1, brightness);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			/*
			 * MAX_BRIGHTNESS -> Enable Ambient Light स्वतः adjust
			 * restore daylight l1 sysfs brightness
			 */
			ret = adp8870_ग_लिखो(client, ADP8870_BLMX1,
					 data->cached_daylight_max);
			अगर (ret)
				वापस ret;

			ret = adp8870_set_bits(client, ADP8870_MDCR,
					 CMP_AUTOEN);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = adp8870_ग_लिखो(client, ADP8870_BLMX1, brightness);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (data->current_brightness && brightness == 0)
		ret = adp8870_set_bits(client,
				ADP8870_MDCR, DIM_EN);
	अन्यथा अगर (data->current_brightness == 0 && brightness)
		ret = adp8870_clr_bits(client,
				ADP8870_MDCR, DIM_EN);

	अगर (!ret)
		data->current_brightness = brightness;

	वापस ret;
पूर्ण

अटल पूर्णांक adp8870_bl_update_status(काष्ठा backlight_device *bl)
अणु
	वापस adp8870_bl_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक adp8870_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा adp8870_bl *data = bl_get_data(bl);

	वापस data->current_brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops adp8870_bl_ops = अणु
	.update_status	= adp8870_bl_update_status,
	.get_brightness	= adp8870_bl_get_brightness,
पूर्ण;

अटल पूर्णांक adp8870_bl_setup(काष्ठा backlight_device *bl)
अणु
	काष्ठा adp8870_bl *data = bl_get_data(bl);
	काष्ठा i2c_client *client = data->client;
	काष्ठा adp8870_backlight_platक्रमm_data *pdata = data->pdata;
	पूर्णांक ret = 0;

	ret = adp8870_ग_लिखो(client, ADP8870_BLSEL, ~pdata->bl_led_assign);
	अगर (ret)
		वापस ret;

	ret = adp8870_ग_लिखो(client, ADP8870_PWMLED, pdata->pwm_assign);
	अगर (ret)
		वापस ret;

	ret = adp8870_ग_लिखो(client, ADP8870_BLMX1, pdata->l1_daylight_max);
	अगर (ret)
		वापस ret;

	ret = adp8870_ग_लिखो(client, ADP8870_BLDM1, pdata->l1_daylight_dim);
	अगर (ret)
		वापस ret;

	अगर (pdata->en_ambl_sens) अणु
		data->cached_daylight_max = pdata->l1_daylight_max;
		ret = adp8870_ग_लिखो(client, ADP8870_BLMX2,
						pdata->l2_bright_max);
		अगर (ret)
			वापस ret;
		ret = adp8870_ग_लिखो(client, ADP8870_BLDM2,
						pdata->l2_bright_dim);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_BLMX3,
						pdata->l3_office_max);
		अगर (ret)
			वापस ret;
		ret = adp8870_ग_लिखो(client, ADP8870_BLDM3,
						pdata->l3_office_dim);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_BLMX4,
						pdata->l4_inकरोor_max);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_BLDM4,
						pdata->l4_inकरोr_dim);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_BLMX5,
						pdata->l5_dark_max);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_BLDM5,
						pdata->l5_dark_dim);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L2TRP, pdata->l2_trip);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L2HYS, pdata->l2_hyst);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L3TRP, pdata->l3_trip);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L3HYS, pdata->l3_hyst);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L4TRP, pdata->l4_trip);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L4HYS, pdata->l4_hyst);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L5TRP, pdata->l5_trip);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_L5HYS, pdata->l5_hyst);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_ALS1_EN, L5_EN | L4_EN |
						L3_EN | L2_EN);
		अगर (ret)
			वापस ret;

		ret = adp8870_ग_लिखो(client, ADP8870_CMP_CTL,
			ALS_CMPR_CFG_VAL(pdata->abml_filt));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = adp8870_ग_लिखो(client, ADP8870_CFGR,
			BL_CFGR_VAL(pdata->bl_fade_law, 0));
	अगर (ret)
		वापस ret;

	ret = adp8870_ग_लिखो(client, ADP8870_BLFR, FADE_VAL(pdata->bl_fade_in,
			pdata->bl_fade_out));
	अगर (ret)
		वापस ret;
	/*
	 * ADP8870 Rev0 requires GDWN_DIS bit set
	 */

	ret = adp8870_set_bits(client, ADP8870_MDCR, BLEN | DIM_EN | NSTBY |
			(data->revid == 0 ? GDWN_DIS : 0));

	वापस ret;
पूर्ण

अटल sमाप_प्रकार adp8870_show(काष्ठा device *dev, अक्षर *buf, पूर्णांक reg)
अणु
	काष्ठा adp8870_bl *data = dev_get_drvdata(dev);
	पूर्णांक error;
	uपूर्णांक8_t reg_val;

	mutex_lock(&data->lock);
	error = adp8870_पढ़ो(data->client, reg, &reg_val);
	mutex_unlock(&data->lock);

	अगर (error < 0)
		वापस error;

	वापस प्र_लिखो(buf, "%u\n", reg_val);
पूर्ण

अटल sमाप_प्रकार adp8870_store(काष्ठा device *dev, स्थिर अक्षर *buf,
			 माप_प्रकार count, पूर्णांक reg)
अणु
	काष्ठा adp8870_bl *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->lock);
	adp8870_ग_लिखो(data->client, reg, val);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l5_dark_max_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLMX5);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l5_dark_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLMX5);
पूर्ण
अटल DEVICE_ATTR(l5_dark_max, 0664, adp8870_bl_l5_dark_max_show,
			adp8870_bl_l5_dark_max_store);


अटल sमाप_प्रकार adp8870_bl_l4_inकरोor_max_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLMX4);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l4_inकरोor_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLMX4);
पूर्ण
अटल DEVICE_ATTR(l4_inकरोor_max, 0664, adp8870_bl_l4_inकरोor_max_show,
			adp8870_bl_l4_inकरोor_max_store);


अटल sमाप_प्रकार adp8870_bl_l3_office_max_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLMX3);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l3_office_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLMX3);
पूर्ण

अटल DEVICE_ATTR(l3_office_max, 0664, adp8870_bl_l3_office_max_show,
			adp8870_bl_l3_office_max_store);

अटल sमाप_प्रकार adp8870_bl_l2_bright_max_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLMX2);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l2_bright_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLMX2);
पूर्ण
अटल DEVICE_ATTR(l2_bright_max, 0664, adp8870_bl_l2_bright_max_show,
			adp8870_bl_l2_bright_max_store);

अटल sमाप_प्रकार adp8870_bl_l1_daylight_max_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLMX1);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l1_daylight_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adp8870_bl *data = dev_get_drvdata(dev);
	पूर्णांक ret = kम_से_अदीर्घ(buf, 10, &data->cached_daylight_max);

	अगर (ret)
		वापस ret;

	वापस adp8870_store(dev, buf, count, ADP8870_BLMX1);
पूर्ण
अटल DEVICE_ATTR(l1_daylight_max, 0664, adp8870_bl_l1_daylight_max_show,
			adp8870_bl_l1_daylight_max_store);

अटल sमाप_प्रकार adp8870_bl_l5_dark_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLDM5);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l5_dark_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLDM5);
पूर्ण
अटल DEVICE_ATTR(l5_dark_dim, 0664, adp8870_bl_l5_dark_dim_show,
			adp8870_bl_l5_dark_dim_store);

अटल sमाप_प्रकार adp8870_bl_l4_inकरोor_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLDM4);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l4_inकरोor_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLDM4);
पूर्ण
अटल DEVICE_ATTR(l4_inकरोor_dim, 0664, adp8870_bl_l4_inकरोor_dim_show,
			adp8870_bl_l4_inकरोor_dim_store);


अटल sमाप_प्रकार adp8870_bl_l3_office_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLDM3);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l3_office_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLDM3);
पूर्ण
अटल DEVICE_ATTR(l3_office_dim, 0664, adp8870_bl_l3_office_dim_show,
			adp8870_bl_l3_office_dim_store);

अटल sमाप_प्रकार adp8870_bl_l2_bright_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLDM2);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l2_bright_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLDM2);
पूर्ण
अटल DEVICE_ATTR(l2_bright_dim, 0664, adp8870_bl_l2_bright_dim_show,
			adp8870_bl_l2_bright_dim_store);

अटल sमाप_प्रकार adp8870_bl_l1_daylight_dim_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp8870_show(dev, buf, ADP8870_BLDM1);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_l1_daylight_dim_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp8870_store(dev, buf, count, ADP8870_BLDM1);
पूर्ण
अटल DEVICE_ATTR(l1_daylight_dim, 0664, adp8870_bl_l1_daylight_dim_show,
			adp8870_bl_l1_daylight_dim_store);

#अगर_घोषित ADP8870_EXT_FEATURES
अटल sमाप_प्रकार adp8870_bl_ambient_light_level_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adp8870_bl *data = dev_get_drvdata(dev);
	पूर्णांक error;
	uपूर्णांक8_t reg_val;
	uपूर्णांक16_t ret_val;

	mutex_lock(&data->lock);
	error = adp8870_पढ़ो(data->client, ADP8870_PH1LEVL, &reg_val);
	अगर (error < 0) अणु
		mutex_unlock(&data->lock);
		वापस error;
	पूर्ण
	ret_val = reg_val;
	error = adp8870_पढ़ो(data->client, ADP8870_PH1LEVH, &reg_val);
	mutex_unlock(&data->lock);

	अगर (error < 0)
		वापस error;

	/* Return 13-bit conversion value क्रम the first light sensor */
	ret_val += (reg_val & 0x1F) << 8;

	वापस प्र_लिखो(buf, "%u\n", ret_val);
पूर्ण
अटल DEVICE_ATTR(ambient_light_level, 0444,
		adp8870_bl_ambient_light_level_show, शून्य);

अटल sमाप_प्रकार adp8870_bl_ambient_light_zone_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adp8870_bl *data = dev_get_drvdata(dev);
	पूर्णांक error;
	uपूर्णांक8_t reg_val;

	mutex_lock(&data->lock);
	error = adp8870_पढ़ो(data->client, ADP8870_CFGR, &reg_val);
	mutex_unlock(&data->lock);

	अगर (error < 0)
		वापस error;

	वापस प्र_लिखो(buf, "%u\n",
		((reg_val >> CFGR_BLV_SHIFT) & CFGR_BLV_MASK) + 1);
पूर्ण

अटल sमाप_प्रकार adp8870_bl_ambient_light_zone_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adp8870_bl *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val == 0) अणु
		/* Enable स्वतःmatic ambient light sensing */
		adp8870_set_bits(data->client, ADP8870_MDCR, CMP_AUTOEN);
	पूर्ण अन्यथा अगर ((val > 0) && (val < 6)) अणु
		/* Disable स्वतःmatic ambient light sensing */
		adp8870_clr_bits(data->client, ADP8870_MDCR, CMP_AUTOEN);

		/* Set user supplied ambient light zone */
		mutex_lock(&data->lock);
		ret = adp8870_पढ़ो(data->client, ADP8870_CFGR, &reg_val);
		अगर (!ret) अणु
			reg_val &= ~(CFGR_BLV_MASK << CFGR_BLV_SHIFT);
			reg_val |= (val - 1) << CFGR_BLV_SHIFT;
			adp8870_ग_लिखो(data->client, ADP8870_CFGR, reg_val);
		पूर्ण
		mutex_unlock(&data->lock);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(ambient_light_zone, 0664,
		adp8870_bl_ambient_light_zone_show,
		adp8870_bl_ambient_light_zone_store);
#पूर्ण_अगर

अटल काष्ठा attribute *adp8870_bl_attributes[] = अणु
	&dev_attr_l5_dark_max.attr,
	&dev_attr_l5_dark_dim.attr,
	&dev_attr_l4_inकरोor_max.attr,
	&dev_attr_l4_inकरोor_dim.attr,
	&dev_attr_l3_office_max.attr,
	&dev_attr_l3_office_dim.attr,
	&dev_attr_l2_bright_max.attr,
	&dev_attr_l2_bright_dim.attr,
	&dev_attr_l1_daylight_max.attr,
	&dev_attr_l1_daylight_dim.attr,
#अगर_घोषित ADP8870_EXT_FEATURES
	&dev_attr_ambient_light_level.attr,
	&dev_attr_ambient_light_zone.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adp8870_bl_attr_group = अणु
	.attrs = adp8870_bl_attributes,
पूर्ण;

अटल पूर्णांक adp8870_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bl;
	काष्ठा adp8870_bl *data;
	काष्ठा adp8870_backlight_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
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

	ret = adp8870_पढ़ो(client, ADP8870_MFDVID, &reg_val);
	अगर (ret < 0)
		वापस -EIO;

	अगर (ADP8870_MANID(reg_val) != ADP8870_MANUFID) अणु
		dev_err(&client->dev, "failed to probe\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	data->revid = ADP8870_DEVID(reg_val);
	data->client = client;
	data->pdata = pdata;
	data->id = id->driver_data;
	data->current_brightness = 0;
	i2c_set_clientdata(client, data);

	mutex_init(&data->lock);

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = props.brightness = ADP8870_MAX_BRIGHTNESS;
	bl = devm_backlight_device_रेजिस्टर(&client->dev,
				dev_driver_string(&client->dev),
				&client->dev, data, &adp8870_bl_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&client->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	data->bl = bl;

	अगर (pdata->en_ambl_sens) अणु
		ret = sysfs_create_group(&bl->dev.kobj,
			&adp8870_bl_attr_group);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to register sysfs\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = adp8870_bl_setup(bl);
	अगर (ret) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	backlight_update_status(bl);

	dev_info(&client->dev, "Rev.%d Backlight\n", data->revid);

	अगर (pdata->num_leds)
		adp8870_led_probe(client);

	वापस 0;

out:
	अगर (data->pdata->en_ambl_sens)
		sysfs_हटाओ_group(&data->bl->dev.kobj,
			&adp8870_bl_attr_group);

	वापस ret;
पूर्ण

अटल पूर्णांक adp8870_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adp8870_bl *data = i2c_get_clientdata(client);

	adp8870_clr_bits(client, ADP8870_MDCR, NSTBY);

	अगर (data->led)
		adp8870_led_हटाओ(client);

	अगर (data->pdata->en_ambl_sens)
		sysfs_हटाओ_group(&data->bl->dev.kobj,
			&adp8870_bl_attr_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक adp8870_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	adp8870_clr_bits(client, ADP8870_MDCR, NSTBY);

	वापस 0;
पूर्ण

अटल पूर्णांक adp8870_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	adp8870_set_bits(client, ADP8870_MDCR, NSTBY | BLEN);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(adp8870_i2c_pm_ops, adp8870_i2c_suspend,
			adp8870_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id adp8870_id[] = अणु
	अणु "adp8870", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adp8870_id);

अटल काष्ठा i2c_driver adp8870_driver = अणु
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm	= &adp8870_i2c_pm_ops,
	पूर्ण,
	.probe    = adp8870_probe,
	.हटाओ   = adp8870_हटाओ,
	.id_table = adp8870_id,
पूर्ण;

module_i2c_driver(adp8870_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("ADP8870 Backlight driver");
