<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * leds-bd2802.c - RGB LED Driver
 *
 * Copyright (C) 2009 Samsung Electronics
 * Kim Kyuwon <q1.kim@samsung.com>
 *
 * Datasheet: http://www.rohm.com/products/databook/driver/pdf/bd2802gu-e.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/leds.h>
#समावेश <linux/leds-bd2802.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>

#घोषणा LED_CTL(rgb2en, rgb1en) ((rgb2en) << 4 | ((rgb1en) << 0))

#घोषणा BD2802_LED_OFFSET		0xa
#घोषणा BD2802_COLOR_OFFSET		0x3

#घोषणा BD2802_REG_CLKSETUP		0x00
#घोषणा BD2802_REG_CONTROL		0x01
#घोषणा BD2802_REG_HOURSETUP		0x02
#घोषणा BD2802_REG_CURRENT1SETUP	0x03
#घोषणा BD2802_REG_CURRENT2SETUP	0x04
#घोषणा BD2802_REG_WAVEPATTERN		0x05

#घोषणा BD2802_CURRENT_032		0x10 /* 3.2mA */
#घोषणा BD2802_CURRENT_000		0x00 /* 0.0mA */

#घोषणा BD2802_PATTERN_FULL		0x07
#घोषणा BD2802_PATTERN_HALF		0x03

क्रमागत led_ids अणु
	LED1,
	LED2,
	LED_NUM,
पूर्ण;

क्रमागत led_colors अणु
	RED,
	GREEN,
	BLUE,
पूर्ण;

क्रमागत led_bits अणु
	BD2802_OFF,
	BD2802_BLINK,
	BD2802_ON,
पूर्ण;

/*
 * State '0' : 'off'
 * State '1' : 'blink'
 * State '2' : 'on'.
 */
काष्ठा led_state अणु
	अचिन्हित r:2;
	अचिन्हित g:2;
	अचिन्हित b:2;
पूर्ण;

काष्ठा bd2802_led अणु
	काष्ठा bd2802_led_platक्रमm_data	*pdata;
	काष्ठा i2c_client		*client;
	काष्ठा gpio_desc		*reset;
	काष्ठा rw_semaphore		rwsem;

	काष्ठा led_state		led[2];

	/*
	 * Making led_classdev as array is not recommended, because array
	 * members prevent using 'container_of' macro. So repetitive works
	 * are needed.
	 */
	काष्ठा led_classdev		cdev_led1r;
	काष्ठा led_classdev		cdev_led1g;
	काष्ठा led_classdev		cdev_led1b;
	काष्ठा led_classdev		cdev_led2r;
	काष्ठा led_classdev		cdev_led2g;
	काष्ठा led_classdev		cdev_led2b;

	/*
	 * Advanced Configuration Function(ADF) mode:
	 * In ADF mode, user can set रेजिस्टरs of BD2802GU directly,
	 * thereक्रमe BD2802GU करोesn't enter reset state.
	 */
	पूर्णांक				adf_on;

	क्रमागत led_ids			led_id;
	क्रमागत led_colors			color;
	क्रमागत led_bits			state;

	/* General attributes of RGB LEDs */
	पूर्णांक				wave_pattern;
	पूर्णांक				rgb_current;
पूर्ण;


/*--------------------------------------------------------------*/
/*	BD2802GU helper functions					*/
/*--------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक bd2802_is_rgb_off(काष्ठा bd2802_led *led, क्रमागत led_ids id,
							क्रमागत led_colors color)
अणु
	चयन (color) अणु
	हाल RED:
		वापस !led->led[id].r;
	हाल GREEN:
		वापस !led->led[id].g;
	हाल BLUE:
		वापस !led->led[id].b;
	शेष:
		dev_err(&led->client->dev, "%s: Invalid color\n", __func__);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक bd2802_is_led_off(काष्ठा bd2802_led *led, क्रमागत led_ids id)
अणु
	अगर (led->led[id].r || led->led[id].g || led->led[id].b)
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक bd2802_is_all_off(काष्ठा bd2802_led *led)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LED_NUM; i++)
		अगर (!bd2802_is_led_off(led, i))
			वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत u8 bd2802_get_base_offset(क्रमागत led_ids id, क्रमागत led_colors color)
अणु
	वापस id * BD2802_LED_OFFSET + color * BD2802_COLOR_OFFSET;
पूर्ण

अटल अंतरभूत u8 bd2802_get_reg_addr(क्रमागत led_ids id, क्रमागत led_colors color,
								u8 reg_offset)
अणु
	वापस reg_offset + bd2802_get_base_offset(id, color);
पूर्ण


/*--------------------------------------------------------------*/
/*	BD2802GU core functions					*/
/*--------------------------------------------------------------*/

अटल पूर्णांक bd2802_ग_लिखो_byte(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
	अगर (ret >= 0)
		वापस 0;

	dev_err(&client->dev, "%s: reg 0x%x, val 0x%x, err %d\n",
						__func__, reg, val, ret);

	वापस ret;
पूर्ण

अटल व्योम bd2802_update_state(काष्ठा bd2802_led *led, क्रमागत led_ids id,
				क्रमागत led_colors color, क्रमागत led_bits led_bit)
अणु
	पूर्णांक i;
	u8 value;

	क्रम (i = 0; i < LED_NUM; i++) अणु
		अगर (i == id) अणु
			चयन (color) अणु
			हाल RED:
				led->led[i].r = led_bit;
				अवरोध;
			हाल GREEN:
				led->led[i].g = led_bit;
				अवरोध;
			हाल BLUE:
				led->led[i].b = led_bit;
				अवरोध;
			शेष:
				dev_err(&led->client->dev,
					"%s: Invalid color\n", __func__);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (led_bit == BD2802_BLINK || led_bit == BD2802_ON)
		वापस;

	अगर (!bd2802_is_led_off(led, id))
		वापस;

	अगर (bd2802_is_all_off(led) && !led->adf_on) अणु
		gpiod_set_value(led->reset, 1);
		वापस;
	पूर्ण

	/*
	 * In this हाल, other led is turned on, and current led is turned
	 * off. So set RGB LED Control रेजिस्टर to stop the current RGB LED
	 */
	value = (id == LED1) ? LED_CTL(1, 0) : LED_CTL(0, 1);
	bd2802_ग_लिखो_byte(led->client, BD2802_REG_CONTROL, value);
पूर्ण

अटल व्योम bd2802_configure(काष्ठा bd2802_led *led)
अणु
	काष्ठा bd2802_led_platक्रमm_data *pdata = led->pdata;
	u8 reg;

	reg = bd2802_get_reg_addr(LED1, RED, BD2802_REG_HOURSETUP);
	bd2802_ग_लिखो_byte(led->client, reg, pdata->rgb_समय);

	reg = bd2802_get_reg_addr(LED2, RED, BD2802_REG_HOURSETUP);
	bd2802_ग_लिखो_byte(led->client, reg, pdata->rgb_समय);
पूर्ण

अटल व्योम bd2802_reset_cancel(काष्ठा bd2802_led *led)
अणु
	gpiod_set_value(led->reset, 0);
	udelay(100);
	bd2802_configure(led);
पूर्ण

अटल व्योम bd2802_enable(काष्ठा bd2802_led *led, क्रमागत led_ids id)
अणु
	क्रमागत led_ids other_led = (id == LED1) ? LED2 : LED1;
	u8 value, other_led_on;

	other_led_on = !bd2802_is_led_off(led, other_led);
	अगर (id == LED1)
		value = LED_CTL(other_led_on, 1);
	अन्यथा
		value = LED_CTL(1 , other_led_on);

	bd2802_ग_लिखो_byte(led->client, BD2802_REG_CONTROL, value);
पूर्ण

अटल व्योम bd2802_set_on(काष्ठा bd2802_led *led, क्रमागत led_ids id,
							क्रमागत led_colors color)
अणु
	u8 reg;

	अगर (bd2802_is_all_off(led) && !led->adf_on)
		bd2802_reset_cancel(led);

	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT1SETUP);
	bd2802_ग_लिखो_byte(led->client, reg, led->rgb_current);
	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT2SETUP);
	bd2802_ग_लिखो_byte(led->client, reg, BD2802_CURRENT_000);
	reg = bd2802_get_reg_addr(id, color, BD2802_REG_WAVEPATTERN);
	bd2802_ग_लिखो_byte(led->client, reg, BD2802_PATTERN_FULL);

	bd2802_enable(led, id);
	bd2802_update_state(led, id, color, BD2802_ON);
पूर्ण

अटल व्योम bd2802_set_blink(काष्ठा bd2802_led *led, क्रमागत led_ids id,
							क्रमागत led_colors color)
अणु
	u8 reg;

	अगर (bd2802_is_all_off(led) && !led->adf_on)
		bd2802_reset_cancel(led);

	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT1SETUP);
	bd2802_ग_लिखो_byte(led->client, reg, BD2802_CURRENT_000);
	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT2SETUP);
	bd2802_ग_लिखो_byte(led->client, reg, led->rgb_current);
	reg = bd2802_get_reg_addr(id, color, BD2802_REG_WAVEPATTERN);
	bd2802_ग_लिखो_byte(led->client, reg, led->wave_pattern);

	bd2802_enable(led, id);
	bd2802_update_state(led, id, color, BD2802_BLINK);
पूर्ण

अटल व्योम bd2802_turn_on(काष्ठा bd2802_led *led, क्रमागत led_ids id,
				क्रमागत led_colors color, क्रमागत led_bits led_bit)
अणु
	अगर (led_bit == BD2802_OFF) अणु
		dev_err(&led->client->dev,
					"Only 'blink' and 'on' are allowed\n");
		वापस;
	पूर्ण

	अगर (led_bit == BD2802_BLINK)
		bd2802_set_blink(led, id, color);
	अन्यथा
		bd2802_set_on(led, id, color);
पूर्ण

अटल व्योम bd2802_turn_off(काष्ठा bd2802_led *led, क्रमागत led_ids id,
							क्रमागत led_colors color)
अणु
	u8 reg;

	अगर (bd2802_is_rgb_off(led, id, color))
		वापस;

	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT1SETUP);
	bd2802_ग_लिखो_byte(led->client, reg, BD2802_CURRENT_000);
	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT2SETUP);
	bd2802_ग_लिखो_byte(led->client, reg, BD2802_CURRENT_000);

	bd2802_update_state(led, id, color, BD2802_OFF);
पूर्ण

#घोषणा BD2802_SET_REGISTER(reg_addr, reg_name)				\
अटल sमाप_प्रकार bd2802_store_reg##reg_addr(काष्ठा device *dev,		\
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु									\
	काष्ठा bd2802_led *led = i2c_get_clientdata(to_i2c_client(dev));\
	अचिन्हित दीर्घ val;						\
	पूर्णांक ret;							\
	अगर (!count)							\
		वापस -EINVAL;						\
	ret = kम_से_अदीर्घ(buf, 16, &val);					\
	अगर (ret)							\
		वापस ret;						\
	करोwn_ग_लिखो(&led->rwsem);					\
	bd2802_ग_लिखो_byte(led->client, reg_addr, (u8) val);		\
	up_ग_लिखो(&led->rwsem);						\
	वापस count;							\
पूर्ण									\
अटल काष्ठा device_attribute bd2802_reg##reg_addr##_attr = अणु		\
	.attr = अणु.name = reg_name, .mode = 0644पूर्ण,			\
	.store = bd2802_store_reg##reg_addr,				\
पूर्ण;

BD2802_SET_REGISTER(0x00, "0x00");
BD2802_SET_REGISTER(0x01, "0x01");
BD2802_SET_REGISTER(0x02, "0x02");
BD2802_SET_REGISTER(0x03, "0x03");
BD2802_SET_REGISTER(0x04, "0x04");
BD2802_SET_REGISTER(0x05, "0x05");
BD2802_SET_REGISTER(0x06, "0x06");
BD2802_SET_REGISTER(0x07, "0x07");
BD2802_SET_REGISTER(0x08, "0x08");
BD2802_SET_REGISTER(0x09, "0x09");
BD2802_SET_REGISTER(0x0a, "0x0a");
BD2802_SET_REGISTER(0x0b, "0x0b");
BD2802_SET_REGISTER(0x0c, "0x0c");
BD2802_SET_REGISTER(0x0d, "0x0d");
BD2802_SET_REGISTER(0x0e, "0x0e");
BD2802_SET_REGISTER(0x0f, "0x0f");
BD2802_SET_REGISTER(0x10, "0x10");
BD2802_SET_REGISTER(0x11, "0x11");
BD2802_SET_REGISTER(0x12, "0x12");
BD2802_SET_REGISTER(0x13, "0x13");
BD2802_SET_REGISTER(0x14, "0x14");
BD2802_SET_REGISTER(0x15, "0x15");

अटल काष्ठा device_attribute *bd2802_addr_attributes[] = अणु
	&bd2802_reg0x00_attr,
	&bd2802_reg0x01_attr,
	&bd2802_reg0x02_attr,
	&bd2802_reg0x03_attr,
	&bd2802_reg0x04_attr,
	&bd2802_reg0x05_attr,
	&bd2802_reg0x06_attr,
	&bd2802_reg0x07_attr,
	&bd2802_reg0x08_attr,
	&bd2802_reg0x09_attr,
	&bd2802_reg0x0a_attr,
	&bd2802_reg0x0b_attr,
	&bd2802_reg0x0c_attr,
	&bd2802_reg0x0d_attr,
	&bd2802_reg0x0e_attr,
	&bd2802_reg0x0f_attr,
	&bd2802_reg0x10_attr,
	&bd2802_reg0x11_attr,
	&bd2802_reg0x12_attr,
	&bd2802_reg0x13_attr,
	&bd2802_reg0x14_attr,
	&bd2802_reg0x15_attr,
पूर्ण;

अटल व्योम bd2802_enable_adv_conf(काष्ठा bd2802_led *led)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(bd2802_addr_attributes); i++) अणु
		ret = device_create_file(&led->client->dev,
						bd2802_addr_attributes[i]);
		अगर (ret) अणु
			dev_err(&led->client->dev, "failed: sysfs file %s\n",
					bd2802_addr_attributes[i]->attr.name);
			जाओ failed_हटाओ_files;
		पूर्ण
	पूर्ण

	अगर (bd2802_is_all_off(led))
		bd2802_reset_cancel(led);

	led->adf_on = 1;

	वापस;

failed_हटाओ_files:
	क्रम (i--; i >= 0; i--)
		device_हटाओ_file(&led->client->dev,
						bd2802_addr_attributes[i]);
पूर्ण

अटल व्योम bd2802_disable_adv_conf(काष्ठा bd2802_led *led)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bd2802_addr_attributes); i++)
		device_हटाओ_file(&led->client->dev,
						bd2802_addr_attributes[i]);

	अगर (bd2802_is_all_off(led))
		gpiod_set_value(led->reset, 1);

	led->adf_on = 0;
पूर्ण

अटल sमाप_प्रकार bd2802_show_adv_conf(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bd2802_led *led = i2c_get_clientdata(to_i2c_client(dev));
	sमाप_प्रकार ret;

	करोwn_पढ़ो(&led->rwsem);
	अगर (led->adf_on)
		ret = प्र_लिखो(buf, "on\n");
	अन्यथा
		ret = प्र_लिखो(buf, "off\n");
	up_पढ़ो(&led->rwsem);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार bd2802_store_adv_conf(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bd2802_led *led = i2c_get_clientdata(to_i2c_client(dev));

	अगर (!count)
		वापस -EINVAL;

	करोwn_ग_लिखो(&led->rwsem);
	अगर (!led->adf_on && !म_भेदन(buf, "on", 2))
		bd2802_enable_adv_conf(led);
	अन्यथा अगर (led->adf_on && !म_भेदन(buf, "off", 3))
		bd2802_disable_adv_conf(led);
	up_ग_लिखो(&led->rwsem);

	वापस count;
पूर्ण

अटल काष्ठा device_attribute bd2802_adv_conf_attr = अणु
	.attr = अणु
		.name = "advanced_configuration",
		.mode = 0644,
	पूर्ण,
	.show = bd2802_show_adv_conf,
	.store = bd2802_store_adv_conf,
पूर्ण;

#घोषणा BD2802_CONTROL_ATTR(attr_name, name_str)			\
अटल sमाप_प्रकार bd2802_show_##attr_name(काष्ठा device *dev,		\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा bd2802_led *led = i2c_get_clientdata(to_i2c_client(dev));\
	sमाप_प्रकार ret;							\
	करोwn_पढ़ो(&led->rwsem);						\
	ret = प्र_लिखो(buf, "0x%02x\n", led->attr_name);			\
	up_पढ़ो(&led->rwsem);						\
	वापस ret;							\
पूर्ण									\
अटल sमाप_प्रकार bd2802_store_##attr_name(काष्ठा device *dev,		\
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु									\
	काष्ठा bd2802_led *led = i2c_get_clientdata(to_i2c_client(dev));\
	अचिन्हित दीर्घ val;						\
	पूर्णांक ret;							\
	अगर (!count)							\
		वापस -EINVAL;						\
	ret = kम_से_अदीर्घ(buf, 16, &val);					\
	अगर (ret)							\
		वापस ret;						\
	करोwn_ग_लिखो(&led->rwsem);					\
	led->attr_name = val;						\
	up_ग_लिखो(&led->rwsem);						\
	वापस count;							\
पूर्ण									\
अटल काष्ठा device_attribute bd2802_##attr_name##_attr = अणु		\
	.attr = अणु							\
		.name = name_str,					\
		.mode = 0644,						\
	पूर्ण,								\
	.show = bd2802_show_##attr_name,				\
	.store = bd2802_store_##attr_name,				\
पूर्ण;

BD2802_CONTROL_ATTR(wave_pattern, "wave_pattern");
BD2802_CONTROL_ATTR(rgb_current, "rgb_current");

अटल काष्ठा device_attribute *bd2802_attributes[] = अणु
	&bd2802_adv_conf_attr,
	&bd2802_wave_pattern_attr,
	&bd2802_rgb_current_attr,
पूर्ण;

#घोषणा BD2802_CONTROL_RGBS(name, id, clr)				\
अटल पूर्णांक bd2802_set_##name##_brightness(काष्ठा led_classdev *led_cdev,\
					क्रमागत led_brightness value)	\
अणु									\
	काष्ठा bd2802_led *led =					\
		container_of(led_cdev, काष्ठा bd2802_led, cdev_##name);	\
	led->led_id = id;						\
	led->color = clr;						\
	अगर (value == LED_OFF) अणु						\
		led->state = BD2802_OFF;				\
		bd2802_turn_off(led, led->led_id, led->color);		\
	पूर्ण अन्यथा अणु							\
		led->state = BD2802_ON;					\
		bd2802_turn_on(led, led->led_id, led->color, BD2802_ON);\
	पूर्ण								\
	वापस 0;							\
पूर्ण									\
अटल पूर्णांक bd2802_set_##name##_blink(काष्ठा led_classdev *led_cdev,	\
		अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)	\
अणु									\
	काष्ठा bd2802_led *led =					\
		container_of(led_cdev, काष्ठा bd2802_led, cdev_##name);	\
	अगर (*delay_on == 0 || *delay_off == 0)				\
		वापस -EINVAL;						\
	led->led_id = id;						\
	led->color = clr;						\
	led->state = BD2802_BLINK;					\
	bd2802_turn_on(led, led->led_id, led->color, BD2802_BLINK);	\
	वापस 0;							\
पूर्ण

BD2802_CONTROL_RGBS(led1r, LED1, RED);
BD2802_CONTROL_RGBS(led1g, LED1, GREEN);
BD2802_CONTROL_RGBS(led1b, LED1, BLUE);
BD2802_CONTROL_RGBS(led2r, LED2, RED);
BD2802_CONTROL_RGBS(led2g, LED2, GREEN);
BD2802_CONTROL_RGBS(led2b, LED2, BLUE);

अटल पूर्णांक bd2802_रेजिस्टर_led_classdev(काष्ठा bd2802_led *led)
अणु
	पूर्णांक ret;

	led->cdev_led1r.name = "led1_R";
	led->cdev_led1r.brightness = LED_OFF;
	led->cdev_led1r.brightness_set_blocking = bd2802_set_led1r_brightness;
	led->cdev_led1r.blink_set = bd2802_set_led1r_blink;

	ret = led_classdev_रेजिस्टर(&led->client->dev, &led->cdev_led1r);
	अगर (ret < 0) अणु
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led1r.name);
		जाओ failed_unरेजिस्टर_led1_R;
	पूर्ण

	led->cdev_led1g.name = "led1_G";
	led->cdev_led1g.brightness = LED_OFF;
	led->cdev_led1g.brightness_set_blocking = bd2802_set_led1g_brightness;
	led->cdev_led1g.blink_set = bd2802_set_led1g_blink;

	ret = led_classdev_रेजिस्टर(&led->client->dev, &led->cdev_led1g);
	अगर (ret < 0) अणु
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led1g.name);
		जाओ failed_unरेजिस्टर_led1_G;
	पूर्ण

	led->cdev_led1b.name = "led1_B";
	led->cdev_led1b.brightness = LED_OFF;
	led->cdev_led1b.brightness_set_blocking = bd2802_set_led1b_brightness;
	led->cdev_led1b.blink_set = bd2802_set_led1b_blink;

	ret = led_classdev_रेजिस्टर(&led->client->dev, &led->cdev_led1b);
	अगर (ret < 0) अणु
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led1b.name);
		जाओ failed_unरेजिस्टर_led1_B;
	पूर्ण

	led->cdev_led2r.name = "led2_R";
	led->cdev_led2r.brightness = LED_OFF;
	led->cdev_led2r.brightness_set_blocking = bd2802_set_led2r_brightness;
	led->cdev_led2r.blink_set = bd2802_set_led2r_blink;

	ret = led_classdev_रेजिस्टर(&led->client->dev, &led->cdev_led2r);
	अगर (ret < 0) अणु
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led2r.name);
		जाओ failed_unरेजिस्टर_led2_R;
	पूर्ण

	led->cdev_led2g.name = "led2_G";
	led->cdev_led2g.brightness = LED_OFF;
	led->cdev_led2g.brightness_set_blocking = bd2802_set_led2g_brightness;
	led->cdev_led2g.blink_set = bd2802_set_led2g_blink;

	ret = led_classdev_रेजिस्टर(&led->client->dev, &led->cdev_led2g);
	अगर (ret < 0) अणु
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led2g.name);
		जाओ failed_unरेजिस्टर_led2_G;
	पूर्ण

	led->cdev_led2b.name = "led2_B";
	led->cdev_led2b.brightness = LED_OFF;
	led->cdev_led2b.brightness_set_blocking = bd2802_set_led2b_brightness;
	led->cdev_led2b.blink_set = bd2802_set_led2b_blink;
	led->cdev_led2b.flags |= LED_CORE_SUSPENDRESUME;

	ret = led_classdev_रेजिस्टर(&led->client->dev, &led->cdev_led2b);
	अगर (ret < 0) अणु
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led2b.name);
		जाओ failed_unरेजिस्टर_led2_B;
	पूर्ण

	वापस 0;

failed_unरेजिस्टर_led2_B:
	led_classdev_unरेजिस्टर(&led->cdev_led2g);
failed_unरेजिस्टर_led2_G:
	led_classdev_unरेजिस्टर(&led->cdev_led2r);
failed_unरेजिस्टर_led2_R:
	led_classdev_unरेजिस्टर(&led->cdev_led1b);
failed_unरेजिस्टर_led1_B:
	led_classdev_unरेजिस्टर(&led->cdev_led1g);
failed_unरेजिस्टर_led1_G:
	led_classdev_unरेजिस्टर(&led->cdev_led1r);
failed_unरेजिस्टर_led1_R:

	वापस ret;
पूर्ण

अटल व्योम bd2802_unरेजिस्टर_led_classdev(काष्ठा bd2802_led *led)
अणु
	led_classdev_unरेजिस्टर(&led->cdev_led2b);
	led_classdev_unरेजिस्टर(&led->cdev_led2g);
	led_classdev_unरेजिस्टर(&led->cdev_led2r);
	led_classdev_unरेजिस्टर(&led->cdev_led1b);
	led_classdev_unरेजिस्टर(&led->cdev_led1g);
	led_classdev_unरेजिस्टर(&led->cdev_led1r);
पूर्ण

अटल पूर्णांक bd2802_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bd2802_led *led;
	पूर्णांक ret, i;

	led = devm_kzalloc(&client->dev, माप(काष्ठा bd2802_led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->client = client;
	i2c_set_clientdata(client, led);

	/*
	 * Configure RESET GPIO (L: RESET, H: RESET cancel)
	 *
	 * We request the reset GPIO as OUT_LOW which means de-निश्चितed,
	 * board files specअगरying this GPIO line in a machine descriptor
	 * table should take care to specअगरy GPIO_ACTIVE_LOW क्रम this line.
	 */
	led->reset = devm_gpiod_get(&client->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(led->reset))
		वापस PTR_ERR(led->reset);

	/* Tacss = min 0.1ms */
	udelay(100);

	/* Detect BD2802GU */
	ret = bd2802_ग_लिखो_byte(client, BD2802_REG_CLKSETUP, 0x00);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to detect device\n");
		वापस ret;
	पूर्ण अन्यथा
		dev_info(&client->dev, "return 0x%02x\n", ret);

	/* To save the घातer, reset BD2802 after detecting */
	gpiod_set_value(led->reset, 1);

	/* Default attributes */
	led->wave_pattern = BD2802_PATTERN_HALF;
	led->rgb_current = BD2802_CURRENT_032;

	init_rwsem(&led->rwsem);

	क्रम (i = 0; i < ARRAY_SIZE(bd2802_attributes); i++) अणु
		ret = device_create_file(&led->client->dev,
						bd2802_attributes[i]);
		अगर (ret) अणु
			dev_err(&led->client->dev, "failed: sysfs file %s\n",
					bd2802_attributes[i]->attr.name);
			जाओ failed_unरेजिस्टर_dev_file;
		पूर्ण
	पूर्ण

	ret = bd2802_रेजिस्टर_led_classdev(led);
	अगर (ret < 0)
		जाओ failed_unरेजिस्टर_dev_file;

	वापस 0;

failed_unरेजिस्टर_dev_file:
	क्रम (i--; i >= 0; i--)
		device_हटाओ_file(&led->client->dev, bd2802_attributes[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक bd2802_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bd2802_led *led = i2c_get_clientdata(client);
	पूर्णांक i;

	gpiod_set_value(led->reset, 1);
	bd2802_unरेजिस्टर_led_classdev(led);
	अगर (led->adf_on)
		bd2802_disable_adv_conf(led);
	क्रम (i = 0; i < ARRAY_SIZE(bd2802_attributes); i++)
		device_हटाओ_file(&led->client->dev, bd2802_attributes[i]);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम bd2802_restore_state(काष्ठा bd2802_led *led)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LED_NUM; i++) अणु
		अगर (led->led[i].r)
			bd2802_turn_on(led, i, RED, led->led[i].r);
		अगर (led->led[i].g)
			bd2802_turn_on(led, i, GREEN, led->led[i].g);
		अगर (led->led[i].b)
			bd2802_turn_on(led, i, BLUE, led->led[i].b);
	पूर्ण
पूर्ण

अटल पूर्णांक bd2802_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bd2802_led *led = i2c_get_clientdata(client);

	gpiod_set_value(led->reset, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक bd2802_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bd2802_led *led = i2c_get_clientdata(client);

	अगर (!bd2802_is_all_off(led) || led->adf_on) अणु
		bd2802_reset_cancel(led);
		bd2802_restore_state(led);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(bd2802_pm, bd2802_suspend, bd2802_resume);

अटल स्थिर काष्ठा i2c_device_id bd2802_id[] = अणु
	अणु "BD2802", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bd2802_id);

अटल काष्ठा i2c_driver bd2802_i2c_driver = अणु
	.driver	= अणु
		.name	= "BD2802",
		.pm	= &bd2802_pm,
	पूर्ण,
	.probe		= bd2802_probe,
	.हटाओ		= bd2802_हटाओ,
	.id_table	= bd2802_id,
पूर्ण;

module_i2c_driver(bd2802_i2c_driver);

MODULE_AUTHOR("Kim Kyuwon <q1.kim@samsung.com>");
MODULE_DESCRIPTION("BD2802 LED driver");
MODULE_LICENSE("GPL v2");
