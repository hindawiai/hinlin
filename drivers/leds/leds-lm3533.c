<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * leds-lm3533.c -- LM3533 LED driver
 *
 * Copyright (C) 2011-2012 Texas Instruments
 *
 * Author: Johan Hovold <jhovold@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/leds.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/lm3533.h>


#घोषणा LM3533_LVCTRLBANK_MIN		2
#घोषणा LM3533_LVCTRLBANK_MAX		5
#घोषणा LM3533_LVCTRLBANK_COUNT		4
#घोषणा LM3533_RISEFALLTIME_MAX		7
#घोषणा LM3533_ALS_CHANNEL_LV_MIN	1
#घोषणा LM3533_ALS_CHANNEL_LV_MAX	2

#घोषणा LM3533_REG_CTRLBANK_BCONF_BASE		0x1b
#घोषणा LM3533_REG_PATTERN_ENABLE		0x28
#घोषणा LM3533_REG_PATTERN_LOW_TIME_BASE	0x71
#घोषणा LM3533_REG_PATTERN_HIGH_TIME_BASE	0x72
#घोषणा LM3533_REG_PATTERN_RISETIME_BASE	0x74
#घोषणा LM3533_REG_PATTERN_FALLTIME_BASE	0x75

#घोषणा LM3533_REG_PATTERN_STEP			0x10

#घोषणा LM3533_REG_CTRLBANK_BCONF_MAPPING_MASK		0x04
#घोषणा LM3533_REG_CTRLBANK_BCONF_ALS_EN_MASK		0x02
#घोषणा LM3533_REG_CTRLBANK_BCONF_ALS_CHANNEL_MASK	0x01

#घोषणा LM3533_LED_FLAG_PATTERN_ENABLE		1


काष्ठा lm3533_led अणु
	काष्ठा lm3533 *lm3533;
	काष्ठा lm3533_ctrlbank cb;
	काष्ठा led_classdev cdev;
	पूर्णांक id;

	काष्ठा mutex mutex;
	अचिन्हित दीर्घ flags;
पूर्ण;


अटल अंतरभूत काष्ठा lm3533_led *to_lm3533_led(काष्ठा led_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा lm3533_led, cdev);
पूर्ण

अटल अंतरभूत पूर्णांक lm3533_led_get_ctrlbank_id(काष्ठा lm3533_led *led)
अणु
	वापस led->id + 2;
पूर्ण

अटल अंतरभूत u8 lm3533_led_get_lv_reg(काष्ठा lm3533_led *led, u8 base)
अणु
	वापस base + led->id;
पूर्ण

अटल अंतरभूत u8 lm3533_led_get_pattern(काष्ठा lm3533_led *led)
अणु
	वापस led->id;
पूर्ण

अटल अंतरभूत u8 lm3533_led_get_pattern_reg(काष्ठा lm3533_led *led,
								u8 base)
अणु
	वापस base + lm3533_led_get_pattern(led) * LM3533_REG_PATTERN_STEP;
पूर्ण

अटल पूर्णांक lm3533_led_pattern_enable(काष्ठा lm3533_led *led, पूर्णांक enable)
अणु
	u8 mask;
	u8 val;
	पूर्णांक pattern;
	पूर्णांक state;
	पूर्णांक ret = 0;

	dev_dbg(led->cdev.dev, "%s - %d\n", __func__, enable);

	mutex_lock(&led->mutex);

	state = test_bit(LM3533_LED_FLAG_PATTERN_ENABLE, &led->flags);
	अगर ((enable && state) || (!enable && !state))
		जाओ out;

	pattern = lm3533_led_get_pattern(led);
	mask = 1 << (2 * pattern);

	अगर (enable)
		val = mask;
	अन्यथा
		val = 0;

	ret = lm3533_update(led->lm3533, LM3533_REG_PATTERN_ENABLE, val, mask);
	अगर (ret) अणु
		dev_err(led->cdev.dev, "failed to enable pattern %d (%d)\n",
							pattern, enable);
		जाओ out;
	पूर्ण

	__change_bit(LM3533_LED_FLAG_PATTERN_ENABLE, &led->flags);
out:
	mutex_unlock(&led->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_led_set(काष्ठा led_classdev *cdev,
						क्रमागत led_brightness value)
अणु
	काष्ठा lm3533_led *led = to_lm3533_led(cdev);

	dev_dbg(led->cdev.dev, "%s - %d\n", __func__, value);

	अगर (value == 0)
		lm3533_led_pattern_enable(led, 0);	/* disable blink */

	वापस lm3533_ctrlbank_set_brightness(&led->cb, value);
पूर्ण

अटल क्रमागत led_brightness lm3533_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा lm3533_led *led = to_lm3533_led(cdev);
	u8 val;
	पूर्णांक ret;

	ret = lm3533_ctrlbank_get_brightness(&led->cb, &val);
	अगर (ret)
		वापस ret;

	dev_dbg(led->cdev.dev, "%s - %u\n", __func__, val);

	वापस val;
पूर्ण

/* Pattern generator defines (delays in us). */
#घोषणा LM3533_LED_DELAY1_VMIN	0x00
#घोषणा LM3533_LED_DELAY2_VMIN	0x3d
#घोषणा LM3533_LED_DELAY3_VMIN	0x80

#घोषणा LM3533_LED_DELAY1_VMAX	(LM3533_LED_DELAY2_VMIN - 1)
#घोषणा LM3533_LED_DELAY2_VMAX	(LM3533_LED_DELAY3_VMIN - 1)
#घोषणा LM3533_LED_DELAY3_VMAX	0xff

#घोषणा LM3533_LED_DELAY1_TMIN	16384U
#घोषणा LM3533_LED_DELAY2_TMIN	1130496U
#घोषणा LM3533_LED_DELAY3_TMIN	10305536U

#घोषणा LM3533_LED_DELAY1_TMAX	999424U
#घोषणा LM3533_LED_DELAY2_TMAX	9781248U
#घोषणा LM3533_LED_DELAY3_TMAX	76890112U

/* t_step = (t_max - t_min) / (v_max - v_min) */
#घोषणा LM3533_LED_DELAY1_TSTEP	16384
#घोषणा LM3533_LED_DELAY2_TSTEP	131072
#घोषणा LM3533_LED_DELAY3_TSTEP	524288

/* Delay limits क्रम hardware accelerated blinking (in ms). */
#घोषणा LM3533_LED_DELAY_ON_MAX \
	((LM3533_LED_DELAY2_TMAX + LM3533_LED_DELAY2_TSTEP / 2) / 1000)
#घोषणा LM3533_LED_DELAY_OFF_MAX \
	((LM3533_LED_DELAY3_TMAX + LM3533_LED_DELAY3_TSTEP / 2) / 1000)

/*
 * Returns linear map of *t from [t_min,t_max] to [v_min,v_max] with a step
 * size of t_step, where
 *
 *	t_step = (t_max - t_min) / (v_max - v_min)
 *
 * and updates *t to reflect the mapped value.
 */
अटल u8 समय_प्रकारo_val(अचिन्हित *t, अचिन्हित t_min, अचिन्हित t_step,
							u8 v_min, u8 v_max)
अणु
	अचिन्हित val;

	val = (*t + t_step / 2 - t_min) / t_step + v_min;

	*t = t_step * (val - v_min) + t_min;

	वापस (u8)val;
पूर्ण

/*
 * Returns समय code corresponding to *delay (in ms) and updates *delay to
 * reflect actual hardware delay.
 *
 * Hardware supports 256 discrete delay बार, भागided पूर्णांकo three groups with
 * the following ranges and step-sizes:
 *
 *	[   16,   999]	[0x00, 0x3e]	step  16 ms
 *	[ 1130,  9781]	[0x3d, 0x7f]	step 131 ms
 *	[10306, 76890]	[0x80, 0xff]	step 524 ms
 *
 * Note that delay group 3 is only available क्रम delay_off.
 */
अटल u8 lm3533_led_get_hw_delay(अचिन्हित *delay)
अणु
	अचिन्हित t;
	u8 val;

	t = *delay * 1000;

	अगर (t >= (LM3533_LED_DELAY2_TMAX + LM3533_LED_DELAY3_TMIN) / 2) अणु
		t = clamp(t, LM3533_LED_DELAY3_TMIN, LM3533_LED_DELAY3_TMAX);
		val = समय_प्रकारo_val(&t,	LM3533_LED_DELAY3_TMIN,
					LM3533_LED_DELAY3_TSTEP,
					LM3533_LED_DELAY3_VMIN,
					LM3533_LED_DELAY3_VMAX);
	पूर्ण अन्यथा अगर (t >= (LM3533_LED_DELAY1_TMAX + LM3533_LED_DELAY2_TMIN) / 2) अणु
		t = clamp(t, LM3533_LED_DELAY2_TMIN, LM3533_LED_DELAY2_TMAX);
		val = समय_प्रकारo_val(&t,	LM3533_LED_DELAY2_TMIN,
					LM3533_LED_DELAY2_TSTEP,
					LM3533_LED_DELAY2_VMIN,
					LM3533_LED_DELAY2_VMAX);
	पूर्ण अन्यथा अणु
		t = clamp(t, LM3533_LED_DELAY1_TMIN, LM3533_LED_DELAY1_TMAX);
		val = समय_प्रकारo_val(&t,	LM3533_LED_DELAY1_TMIN,
					LM3533_LED_DELAY1_TSTEP,
					LM3533_LED_DELAY1_VMIN,
					LM3533_LED_DELAY1_VMAX);
	पूर्ण

	*delay = (t + 500) / 1000;

	वापस val;
पूर्ण

/*
 * Set delay रेजिस्टर base to *delay (in ms) and update *delay to reflect
 * actual hardware delay used.
 */
अटल u8 lm3533_led_delay_set(काष्ठा lm3533_led *led, u8 base,
							अचिन्हित दीर्घ *delay)
अणु
	अचिन्हित t;
	u8 val;
	u8 reg;
	पूर्णांक ret;

	t = (अचिन्हित)*delay;

	/* Delay group 3 is only available क्रम low समय (delay off). */
	अगर (base != LM3533_REG_PATTERN_LOW_TIME_BASE)
		t = min(t, LM3533_LED_DELAY2_TMAX / 1000);

	val = lm3533_led_get_hw_delay(&t);

	dev_dbg(led->cdev.dev, "%s - %lu: %u (0x%02x)\n", __func__,
							*delay, t, val);
	reg = lm3533_led_get_pattern_reg(led, base);
	ret = lm3533_ग_लिखो(led->lm3533, reg, val);
	अगर (ret)
		dev_err(led->cdev.dev, "failed to set delay (%02x)\n", reg);

	*delay = t;

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_led_delay_on_set(काष्ठा lm3533_led *led, अचिन्हित दीर्घ *t)
अणु
	वापस lm3533_led_delay_set(led, LM3533_REG_PATTERN_HIGH_TIME_BASE, t);
पूर्ण

अटल पूर्णांक lm3533_led_delay_off_set(काष्ठा lm3533_led *led, अचिन्हित दीर्घ *t)
अणु
	वापस lm3533_led_delay_set(led, LM3533_REG_PATTERN_LOW_TIME_BASE, t);
पूर्ण

अटल पूर्णांक lm3533_led_blink_set(काष्ठा led_classdev *cdev,
				अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा lm3533_led *led = to_lm3533_led(cdev);
	पूर्णांक ret;

	dev_dbg(led->cdev.dev, "%s - on = %lu, off = %lu\n", __func__,
							*delay_on, *delay_off);

	अगर (*delay_on > LM3533_LED_DELAY_ON_MAX ||
					*delay_off > LM3533_LED_DELAY_OFF_MAX)
		वापस -EINVAL;

	अगर (*delay_on == 0 && *delay_off == 0) अणु
		*delay_on = 500;
		*delay_off = 500;
	पूर्ण

	ret = lm3533_led_delay_on_set(led, delay_on);
	अगर (ret)
		वापस ret;

	ret = lm3533_led_delay_off_set(led, delay_off);
	अगर (ret)
		वापस ret;

	वापस lm3533_led_pattern_enable(led, 1);
पूर्ण

अटल sमाप_प्रकार show_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", led->id);
पूर्ण

/*
 * Pattern generator rise/fall बार:
 *
 *   0 - 2048 us (शेष)
 *   1 - 262 ms
 *   2 - 524 ms
 *   3 - 1.049 s
 *   4 - 2.097 s
 *   5 - 4.194 s
 *   6 - 8.389 s
 *   7 - 16.78 s
 */
अटल sमाप_प्रकार show_risefallसमय(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf, u8 base)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	sमाप_प्रकार ret;
	u8 reg;
	u8 val;

	reg = lm3533_led_get_pattern_reg(led, base);
	ret = lm3533_पढ़ो(led->lm3533, reg, &val);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%x\n", val);
पूर्ण

अटल sमाप_प्रकार show_riseसमय(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_risefallसमय(dev, attr, buf,
					LM3533_REG_PATTERN_RISETIME_BASE);
पूर्ण

अटल sमाप_प्रकार show_fallसमय(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_risefallसमय(dev, attr, buf,
					LM3533_REG_PATTERN_FALLTIME_BASE);
पूर्ण

अटल sमाप_प्रकार store_risefallसमय(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len, u8 base)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	u8 val;
	u8 reg;
	पूर्णांक ret;

	अगर (kstrtou8(buf, 0, &val) || val > LM3533_RISEFALLTIME_MAX)
		वापस -EINVAL;

	reg = lm3533_led_get_pattern_reg(led, base);
	ret = lm3533_ग_लिखो(led->lm3533, reg, val);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार store_riseसमय(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_risefallसमय(dev, attr, buf, len,
					LM3533_REG_PATTERN_RISETIME_BASE);
पूर्ण

अटल sमाप_प्रकार store_fallसमय(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_risefallसमय(dev, attr, buf, len,
					LM3533_REG_PATTERN_FALLTIME_BASE);
पूर्ण

अटल sमाप_प्रकार show_als_channel(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	अचिन्हित channel;
	u8 reg;
	u8 val;
	पूर्णांक ret;

	reg = lm3533_led_get_lv_reg(led, LM3533_REG_CTRLBANK_BCONF_BASE);
	ret = lm3533_पढ़ो(led->lm3533, reg, &val);
	अगर (ret)
		वापस ret;

	channel = (val & LM3533_REG_CTRLBANK_BCONF_ALS_CHANNEL_MASK) + 1;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", channel);
पूर्ण

अटल sमाप_प्रकार store_als_channel(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	अचिन्हित channel;
	u8 reg;
	u8 val;
	u8 mask;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक(buf, 0, &channel))
		वापस -EINVAL;

	अगर (channel < LM3533_ALS_CHANNEL_LV_MIN ||
					channel > LM3533_ALS_CHANNEL_LV_MAX)
		वापस -EINVAL;

	reg = lm3533_led_get_lv_reg(led, LM3533_REG_CTRLBANK_BCONF_BASE);
	mask = LM3533_REG_CTRLBANK_BCONF_ALS_CHANNEL_MASK;
	val = channel - 1;

	ret = lm3533_update(led->lm3533, reg, val, mask);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार show_als_en(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	bool enable;
	u8 reg;
	u8 val;
	पूर्णांक ret;

	reg = lm3533_led_get_lv_reg(led, LM3533_REG_CTRLBANK_BCONF_BASE);
	ret = lm3533_पढ़ो(led->lm3533, reg, &val);
	अगर (ret)
		वापस ret;

	enable = val & LM3533_REG_CTRLBANK_BCONF_ALS_EN_MASK;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", enable);
पूर्ण

अटल sमाप_प्रकार store_als_en(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	अचिन्हित enable;
	u8 reg;
	u8 mask;
	u8 val;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक(buf, 0, &enable))
		वापस -EINVAL;

	reg = lm3533_led_get_lv_reg(led, LM3533_REG_CTRLBANK_BCONF_BASE);
	mask = LM3533_REG_CTRLBANK_BCONF_ALS_EN_MASK;

	अगर (enable)
		val = mask;
	अन्यथा
		val = 0;

	ret = lm3533_update(led->lm3533, reg, val, mask);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार show_linear(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	u8 reg;
	u8 val;
	पूर्णांक linear;
	पूर्णांक ret;

	reg = lm3533_led_get_lv_reg(led, LM3533_REG_CTRLBANK_BCONF_BASE);
	ret = lm3533_पढ़ो(led->lm3533, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (val & LM3533_REG_CTRLBANK_BCONF_MAPPING_MASK)
		linear = 1;
	अन्यथा
		linear = 0;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%x\n", linear);
पूर्ण

अटल sमाप_प्रकार store_linear(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	अचिन्हित दीर्घ linear;
	u8 reg;
	u8 mask;
	u8 val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 0, &linear))
		वापस -EINVAL;

	reg = lm3533_led_get_lv_reg(led, LM3533_REG_CTRLBANK_BCONF_BASE);
	mask = LM3533_REG_CTRLBANK_BCONF_MAPPING_MASK;

	अगर (linear)
		val = mask;
	अन्यथा
		val = 0;

	ret = lm3533_update(led->lm3533, reg, val, mask);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	u8 val;
	पूर्णांक ret;

	ret = lm3533_ctrlbank_get_pwm(&led->cb, &val);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार store_pwm(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	u8 val;
	पूर्णांक ret;

	अगर (kstrtou8(buf, 0, &val))
		वापस -EINVAL;

	ret = lm3533_ctrlbank_set_pwm(&led->cb, val);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल LM3533_ATTR_RW(als_channel);
अटल LM3533_ATTR_RW(als_en);
अटल LM3533_ATTR_RW(fallसमय);
अटल LM3533_ATTR_RO(id);
अटल LM3533_ATTR_RW(linear);
अटल LM3533_ATTR_RW(pwm);
अटल LM3533_ATTR_RW(riseसमय);

अटल काष्ठा attribute *lm3533_led_attributes[] = अणु
	&dev_attr_als_channel.attr,
	&dev_attr_als_en.attr,
	&dev_attr_fallसमय.attr,
	&dev_attr_id.attr,
	&dev_attr_linear.attr,
	&dev_attr_pwm.attr,
	&dev_attr_riseसमय.attr,
	शून्य,
पूर्ण;

अटल umode_t lm3533_led_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3533_led *led = to_lm3533_led(led_cdev);
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_als_channel.attr ||
					attr == &dev_attr_als_en.attr) अणु
		अगर (!led->lm3533->have_als)
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm3533_led_attribute_group = अणु
	.is_visible	= lm3533_led_attr_is_visible,
	.attrs		= lm3533_led_attributes
पूर्ण;

अटल स्थिर काष्ठा attribute_group *lm3533_led_attribute_groups[] = अणु
	&lm3533_led_attribute_group,
	शून्य
पूर्ण;

अटल पूर्णांक lm3533_led_setup(काष्ठा lm3533_led *led,
					काष्ठा lm3533_led_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = lm3533_ctrlbank_set_max_current(&led->cb, pdata->max_current);
	अगर (ret)
		वापस ret;

	वापस lm3533_ctrlbank_set_pwm(&led->cb, pdata->pwm);
पूर्ण

अटल पूर्णांक lm3533_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lm3533 *lm3533;
	काष्ठा lm3533_led_platक्रमm_data *pdata;
	काष्ठा lm3533_led *led;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	lm3533 = dev_get_drvdata(pdev->dev.parent);
	अगर (!lm3533)
		वापस -EINVAL;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdev->id < 0 || pdev->id >= LM3533_LVCTRLBANK_COUNT) अणु
		dev_err(&pdev->dev, "illegal LED id %d\n", pdev->id);
		वापस -EINVAL;
	पूर्ण

	led = devm_kzalloc(&pdev->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->lm3533 = lm3533;
	led->cdev.name = pdata->name;
	led->cdev.शेष_trigger = pdata->शेष_trigger;
	led->cdev.brightness_set_blocking = lm3533_led_set;
	led->cdev.brightness_get = lm3533_led_get;
	led->cdev.blink_set = lm3533_led_blink_set;
	led->cdev.brightness = LED_OFF;
	led->cdev.groups = lm3533_led_attribute_groups;
	led->id = pdev->id;

	mutex_init(&led->mutex);

	/* The class framework makes a callback to get brightness during
	 * registration so use parent device (क्रम error reporting) until
	 * रेजिस्टरed.
	 */
	led->cb.lm3533 = lm3533;
	led->cb.id = lm3533_led_get_ctrlbank_id(led);
	led->cb.dev = lm3533->dev;

	platक्रमm_set_drvdata(pdev, led);

	ret = led_classdev_रेजिस्टर(pdev->dev.parent, &led->cdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register LED %d\n", pdev->id);
		वापस ret;
	पूर्ण

	led->cb.dev = led->cdev.dev;

	ret = lm3533_led_setup(led, pdata);
	अगर (ret)
		जाओ err_deरेजिस्टर;

	ret = lm3533_ctrlbank_enable(&led->cb);
	अगर (ret)
		जाओ err_deरेजिस्टर;

	वापस 0;

err_deरेजिस्टर:
	led_classdev_unरेजिस्टर(&led->cdev);

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lm3533_led *led = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s\n", __func__);

	lm3533_ctrlbank_disable(&led->cb);
	led_classdev_unरेजिस्टर(&led->cdev);

	वापस 0;
पूर्ण

अटल व्योम lm3533_led_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु

	काष्ठा lm3533_led *led = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s\n", __func__);

	lm3533_ctrlbank_disable(&led->cb);
	lm3533_led_set(&led->cdev, LED_OFF);		/* disable blink */
पूर्ण

अटल काष्ठा platक्रमm_driver lm3533_led_driver = अणु
	.driver = अणु
		.name = "lm3533-leds",
	पूर्ण,
	.probe		= lm3533_led_probe,
	.हटाओ		= lm3533_led_हटाओ,
	.shutकरोwn	= lm3533_led_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(lm3533_led_driver);

MODULE_AUTHOR("Johan Hovold <jhovold@gmail.com>");
MODULE_DESCRIPTION("LM3533 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lm3533-leds");
