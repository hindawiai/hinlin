<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Flash class driver क्रम the flash cell of max77693 mfd.
 *
 *	Copyright (C) 2015, Samsung Electronics Co., Ltd.
 *
 *	Authors: Jacek Anaszewski <j.anaszewski@samsung.com>
 *		 Andrzej Hajda <a.hajda@samsung.com>
 */

#समावेश <linux/led-class-flash.h>
#समावेश <linux/mfd/max77693.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77693-निजी.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-flash-led-class.h>

#घोषणा MODE_OFF		0
#घोषणा MODE_FLASH(a)		(1 << (a))
#घोषणा MODE_TORCH(a)		(1 << (2 + (a)))
#घोषणा MODE_FLASH_EXTERNAL(a)	(1 << (4 + (a)))

#घोषणा MODE_FLASH_MASK		(MODE_FLASH(FLED1) | MODE_FLASH(FLED2) | \
				 MODE_FLASH_EXTERNAL(FLED1) | \
				 MODE_FLASH_EXTERNAL(FLED2))
#घोषणा MODE_TORCH_MASK		(MODE_TORCH(FLED1) | MODE_TORCH(FLED2))

#घोषणा FLED1_IOUT		(1 << 0)
#घोषणा FLED2_IOUT		(1 << 1)

क्रमागत max77693_fled अणु
	FLED1,
	FLED2,
पूर्ण;

क्रमागत max77693_led_mode अणु
	FLASH,
	TORCH,
पूर्ण;

काष्ठा max77693_led_config_data अणु
	स्थिर अक्षर *label[2];
	u32 iout_torch_max[2];
	u32 iout_flash_max[2];
	u32 flash_समयout_max[2];
	u32 num_leds;
	u32 boost_mode;
	u32 boost_vout;
	u32 low_vsys;
पूर्ण;

काष्ठा max77693_sub_led अणु
	/* corresponding FLED output identअगरier */
	पूर्णांक fled_id;
	/* corresponding LED Flash class device */
	काष्ठा led_classdev_flash fled_cdev;
	/* V4L2 Flash device */
	काष्ठा v4l2_flash *v4l2_flash;

	/* brightness cache */
	अचिन्हित पूर्णांक torch_brightness;
	/* flash समयout cache */
	अचिन्हित पूर्णांक flash_समयout;
	/* flash faults that may have occurred */
	u32 flash_faults;
पूर्ण;

काष्ठा max77693_led_device अणु
	/* parent mfd regmap */
	काष्ठा regmap *regmap;
	/* platक्रमm device data */
	काष्ठा platक्रमm_device *pdev;
	/* secures access to the device */
	काष्ठा mutex lock;

	/* sub led data */
	काष्ठा max77693_sub_led sub_leds[2];

	/* maximum torch current values क्रम FLED outमाला_दो */
	u32 iout_torch_max[2];
	/* maximum flash current values क्रम FLED outमाला_दो */
	u32 iout_flash_max[2];

	/* current flash समयout cache */
	अचिन्हित पूर्णांक current_flash_समयout;
	/* ITORCH रेजिस्टर cache */
	u8 torch_iout_reg;
	/* mode of fled outमाला_दो */
	अचिन्हित पूर्णांक mode_flags;
	/* recently strobed fled */
	पूर्णांक strobing_sub_led_id;
	/* biपंचांगask of FLED outमाला_दो use state (bit 0. - FLED1, bit 1. - FLED2) */
	u8 fled_mask;
	/* FLED modes that can be set */
	u8 allowed_modes;

	/* arrangement of current outमाला_दो */
	bool iout_joपूर्णांक;
पूर्ण;

अटल u8 max77693_led_iout_to_reg(u32 ua)
अणु
	अगर (ua < FLASH_IOUT_MIN)
		ua = FLASH_IOUT_MIN;
	वापस (ua - FLASH_IOUT_MIN) / FLASH_IOUT_STEP;
पूर्ण

अटल u8 max77693_flash_समयout_to_reg(u32 us)
अणु
	वापस (us - FLASH_TIMEOUT_MIN) / FLASH_TIMEOUT_STEP;
पूर्ण

अटल अंतरभूत काष्ठा max77693_sub_led *flcdev_to_sub_led(
					काष्ठा led_classdev_flash *fled_cdev)
अणु
	वापस container_of(fled_cdev, काष्ठा max77693_sub_led, fled_cdev);
पूर्ण

अटल अंतरभूत काष्ठा max77693_led_device *sub_led_to_led(
					काष्ठा max77693_sub_led *sub_led)
अणु
	वापस container_of(sub_led, काष्ठा max77693_led_device,
				sub_leds[sub_led->fled_id]);
पूर्ण

अटल अंतरभूत u8 max77693_led_vsys_to_reg(u32 mv)
अणु
	वापस ((mv - MAX_FLASH1_VSYS_MIN) / MAX_FLASH1_VSYS_STEP) << 2;
पूर्ण

अटल अंतरभूत u8 max77693_led_vout_to_reg(u32 mv)
अणु
	वापस (mv - FLASH_VOUT_MIN) / FLASH_VOUT_STEP + FLASH_VOUT_RMIN;
पूर्ण

अटल अंतरभूत bool max77693_fled_used(काष्ठा max77693_led_device *led,
					 पूर्णांक fled_id)
अणु
	u8 fled_bit = (fled_id == FLED1) ? FLED1_IOUT : FLED2_IOUT;

	वापस led->fled_mask & fled_bit;
पूर्ण

अटल पूर्णांक max77693_set_mode_reg(काष्ठा max77693_led_device *led, u8 mode)
अणु
	काष्ठा regmap *rmap = led->regmap;
	पूर्णांक ret, v = 0, i;

	क्रम (i = FLED1; i <= FLED2; ++i) अणु
		अगर (mode & MODE_TORCH(i))
			v |= FLASH_EN_ON << TORCH_EN_SHIFT(i);

		अगर (mode & MODE_FLASH(i)) अणु
			v |= FLASH_EN_ON << FLASH_EN_SHIFT(i);
		पूर्ण अन्यथा अगर (mode & MODE_FLASH_EXTERNAL(i)) अणु
			v |= FLASH_EN_FLASH << FLASH_EN_SHIFT(i);
			/*
			 * Enable hw triggering also क्रम torch mode, as some
			 * camera sensors use torch led to fathom ambient light
			 * conditions beक्रमe strobing the flash.
			 */
			v |= FLASH_EN_TORCH << TORCH_EN_SHIFT(i);
		पूर्ण
	पूर्ण

	/* Reset the रेजिस्टर only prior setting flash modes */
	अगर (mode & ~(MODE_TORCH(FLED1) | MODE_TORCH(FLED2))) अणु
		ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_FLASH_EN, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस regmap_ग_लिखो(rmap, MAX77693_LED_REG_FLASH_EN, v);
पूर्ण

अटल पूर्णांक max77693_add_mode(काष्ठा max77693_led_device *led, u8 mode)
अणु
	u8 new_mode_flags;
	पूर्णांक i, ret;

	अगर (led->iout_joपूर्णांक)
		/* Span the mode on FLED2 क्रम joपूर्णांक iouts हाल */
		mode |= (mode << 1);

	/*
	 * FLASH_EXTERNAL mode activates FLASHEN and TORCHEN pins in the device.
	 * Corresponding रेजिस्टर bit fields पूर्णांकerfere with SW triggered modes,
	 * thus clear them to ensure proper device configuration.
	 */
	क्रम (i = FLED1; i <= FLED2; ++i)
		अगर (mode & MODE_FLASH_EXTERNAL(i))
			led->mode_flags &= (~MODE_TORCH(i) & ~MODE_FLASH(i));

	new_mode_flags = mode | led->mode_flags;
	new_mode_flags &= led->allowed_modes;

	अगर (new_mode_flags ^ led->mode_flags)
		led->mode_flags = new_mode_flags;
	अन्यथा
		वापस 0;

	ret = max77693_set_mode_reg(led, led->mode_flags);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Clear flash mode flag after setting the mode to aव्योम spurious flash
	 * strobing on each subsequent torch mode setting.
	 */
	अगर (mode & MODE_FLASH_MASK)
		led->mode_flags &= ~mode;

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_clear_mode(काष्ठा max77693_led_device *led,
				u8 mode)
अणु
	अगर (led->iout_joपूर्णांक)
		/* Clear mode also on FLED2 क्रम joपूर्णांक iouts हाल */
		mode |= (mode << 1);

	led->mode_flags &= ~mode;

	वापस max77693_set_mode_reg(led, led->mode_flags);
पूर्ण

अटल व्योम max77693_add_allowed_modes(काष्ठा max77693_led_device *led,
				पूर्णांक fled_id, क्रमागत max77693_led_mode mode)
अणु
	अगर (mode == FLASH)
		led->allowed_modes |= (MODE_FLASH(fled_id) |
				       MODE_FLASH_EXTERNAL(fled_id));
	अन्यथा
		led->allowed_modes |= MODE_TORCH(fled_id);
पूर्ण

अटल व्योम max77693_distribute_currents(काष्ठा max77693_led_device *led,
				पूर्णांक fled_id, क्रमागत max77693_led_mode mode,
				u32 micro_amp, u32 iout_max[2], u32 iout[2])
अणु
	अगर (!led->iout_joपूर्णांक) अणु
		iout[fled_id] = micro_amp;
		max77693_add_allowed_modes(led, fled_id, mode);
		वापस;
	पूर्ण

	iout[FLED1] = min(micro_amp, iout_max[FLED1]);
	iout[FLED2] = micro_amp - iout[FLED1];

	अगर (mode == FLASH)
		led->allowed_modes &= ~MODE_FLASH_MASK;
	अन्यथा
		led->allowed_modes &= ~MODE_TORCH_MASK;

	max77693_add_allowed_modes(led, FLED1, mode);

	अगर (iout[FLED2])
		max77693_add_allowed_modes(led, FLED2, mode);
पूर्ण

अटल पूर्णांक max77693_set_torch_current(काष्ठा max77693_led_device *led,
				पूर्णांक fled_id, u32 micro_amp)
अणु
	काष्ठा regmap *rmap = led->regmap;
	u8 iout1_reg = 0, iout2_reg = 0;
	u32 iout[2];

	max77693_distribute_currents(led, fled_id, TORCH, micro_amp,
					led->iout_torch_max, iout);

	अगर (fled_id == FLED1 || led->iout_joपूर्णांक) अणु
		iout1_reg = max77693_led_iout_to_reg(iout[FLED1]);
		led->torch_iout_reg &= TORCH_IOUT_MASK(TORCH_IOUT2_SHIFT);
	पूर्ण
	अगर (fled_id == FLED2 || led->iout_joपूर्णांक) अणु
		iout2_reg = max77693_led_iout_to_reg(iout[FLED2]);
		led->torch_iout_reg &= TORCH_IOUT_MASK(TORCH_IOUT1_SHIFT);
	पूर्ण

	led->torch_iout_reg |= ((iout1_reg << TORCH_IOUT1_SHIFT) |
				(iout2_reg << TORCH_IOUT2_SHIFT));

	वापस regmap_ग_लिखो(rmap, MAX77693_LED_REG_ITORCH,
						led->torch_iout_reg);
पूर्ण

अटल पूर्णांक max77693_set_flash_current(काष्ठा max77693_led_device *led,
					पूर्णांक fled_id,
					u32 micro_amp)
अणु
	काष्ठा regmap *rmap = led->regmap;
	u8 iout1_reg, iout2_reg;
	u32 iout[2];
	पूर्णांक ret = -EINVAL;

	max77693_distribute_currents(led, fled_id, FLASH, micro_amp,
					led->iout_flash_max, iout);

	अगर (fled_id == FLED1 || led->iout_joपूर्णांक) अणु
		iout1_reg = max77693_led_iout_to_reg(iout[FLED1]);
		ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_IFLASH1,
							iout1_reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (fled_id == FLED2 || led->iout_joपूर्णांक) अणु
		iout2_reg = max77693_led_iout_to_reg(iout[FLED2]);
		ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_IFLASH2,
							iout2_reg);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_set_समयout(काष्ठा max77693_led_device *led, u32 microsec)
अणु
	काष्ठा regmap *rmap = led->regmap;
	u8 v;
	पूर्णांक ret;

	v = max77693_flash_समयout_to_reg(microsec) | FLASH_TMR_LEVEL;

	ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_FLASH_TIMER, v);
	अगर (ret < 0)
		वापस ret;

	led->current_flash_समयout = microsec;

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_get_strobe_status(काष्ठा max77693_led_device *led,
					bool *state)
अणु
	काष्ठा regmap *rmap = led->regmap;
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rmap, MAX77693_LED_REG_FLASH_STATUS, &v);
	अगर (ret < 0)
		वापस ret;

	*state = v & FLASH_STATUS_FLASH_ON;

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_get_flash_faults(काष्ठा max77693_sub_led *sub_led)
अणु
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	काष्ठा regmap *rmap = led->regmap;
	अचिन्हित पूर्णांक v;
	u8 fault_खोलो_mask, fault_लघु_mask;
	पूर्णांक ret;

	sub_led->flash_faults = 0;

	अगर (led->iout_joपूर्णांक) अणु
		fault_खोलो_mask = FLASH_INT_FLED1_OPEN | FLASH_INT_FLED2_OPEN;
		fault_लघु_mask = FLASH_INT_FLED1_SHORT |
							FLASH_INT_FLED2_SHORT;
	पूर्ण अन्यथा अणु
		fault_खोलो_mask = (sub_led->fled_id == FLED1) ?
						FLASH_INT_FLED1_OPEN :
						FLASH_INT_FLED2_OPEN;
		fault_लघु_mask = (sub_led->fled_id == FLED1) ?
						FLASH_INT_FLED1_SHORT :
						FLASH_INT_FLED2_SHORT;
	पूर्ण

	ret = regmap_पढ़ो(rmap, MAX77693_LED_REG_FLASH_INT, &v);
	अगर (ret < 0)
		वापस ret;

	अगर (v & fault_खोलो_mask)
		sub_led->flash_faults |= LED_FAULT_OVER_VOLTAGE;
	अगर (v & fault_लघु_mask)
		sub_led->flash_faults |= LED_FAULT_SHORT_CIRCUIT;
	अगर (v & FLASH_INT_OVER_CURRENT)
		sub_led->flash_faults |= LED_FAULT_OVER_CURRENT;

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_setup(काष्ठा max77693_led_device *led,
			 काष्ठा max77693_led_config_data *led_cfg)
अणु
	काष्ठा regmap *rmap = led->regmap;
	पूर्णांक i, first_led, last_led, ret;
	u32 max_flash_curr[2];
	u8 v;

	/*
	 * Initialize only flash current. Torch current करोesn't
	 * require initialization as ITORCH रेजिस्टर is written with
	 * new value each समय brightness_set op is called.
	 */
	अगर (led->iout_joपूर्णांक) अणु
		first_led = FLED1;
		last_led = FLED1;
		max_flash_curr[FLED1] = led_cfg->iout_flash_max[FLED1] +
					led_cfg->iout_flash_max[FLED2];
	पूर्ण अन्यथा अणु
		first_led = max77693_fled_used(led, FLED1) ? FLED1 : FLED2;
		last_led = max77693_fled_used(led, FLED2) ? FLED2 : FLED1;
		max_flash_curr[FLED1] = led_cfg->iout_flash_max[FLED1];
		max_flash_curr[FLED2] = led_cfg->iout_flash_max[FLED2];
	पूर्ण

	क्रम (i = first_led; i <= last_led; ++i) अणु
		ret = max77693_set_flash_current(led, i,
					max_flash_curr[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	v = TORCH_TMR_NO_TIMER | MAX77693_LED_TRIG_TYPE_LEVEL;
	ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_ITORCHTIMER, v);
	अगर (ret < 0)
		वापस ret;

	अगर (led_cfg->low_vsys > 0)
		v = max77693_led_vsys_to_reg(led_cfg->low_vsys) |
						MAX_FLASH1_MAX_FL_EN;
	अन्यथा
		v = 0;

	ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_MAX_FLASH1, v);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_MAX_FLASH2, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (led_cfg->boost_mode == MAX77693_LED_BOOST_FIXED)
		v = FLASH_BOOST_FIXED;
	अन्यथा
		v = led_cfg->boost_mode | led_cfg->boost_mode << 1;

	अगर (max77693_fled_used(led, FLED1) && max77693_fled_used(led, FLED2))
		v |= FLASH_BOOST_LEDNUM_2;

	ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_VOUT_CNTL, v);
	अगर (ret < 0)
		वापस ret;

	v = max77693_led_vout_to_reg(led_cfg->boost_vout);
	ret = regmap_ग_लिखो(rmap, MAX77693_LED_REG_VOUT_FLASH1, v);
	अगर (ret < 0)
		वापस ret;

	वापस max77693_set_mode_reg(led, MODE_OFF);
पूर्ण

/* LED subप्रणाली callbacks */
अटल पूर्णांक max77693_led_brightness_set(काष्ठा led_classdev *led_cdev,
					क्रमागत led_brightness value)
अणु
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	काष्ठा max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	पूर्णांक fled_id = sub_led->fled_id, ret;

	mutex_lock(&led->lock);

	अगर (value == 0) अणु
		ret = max77693_clear_mode(led, MODE_TORCH(fled_id));
		अगर (ret < 0)
			dev_dbg(&led->pdev->dev,
				"Failed to clear torch mode (%d)\n",
				ret);
		जाओ unlock;
	पूर्ण

	ret = max77693_set_torch_current(led, fled_id, value * TORCH_IOUT_STEP);
	अगर (ret < 0) अणु
		dev_dbg(&led->pdev->dev,
			"Failed to set torch current (%d)\n",
			ret);
		जाओ unlock;
	पूर्ण

	ret = max77693_add_mode(led, MODE_TORCH(fled_id));
	अगर (ret < 0)
		dev_dbg(&led->pdev->dev,
			"Failed to set torch mode (%d)\n",
			ret);
unlock:
	mutex_unlock(&led->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_led_flash_brightness_set(
				काष्ठा led_classdev_flash *fled_cdev,
				u32 brightness)
अणु
	काष्ठा max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	पूर्णांक ret;

	mutex_lock(&led->lock);
	ret = max77693_set_flash_current(led, sub_led->fled_id, brightness);
	mutex_unlock(&led->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_led_flash_strobe_set(
				काष्ठा led_classdev_flash *fled_cdev,
				bool state)
अणु
	काष्ठा max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	पूर्णांक fled_id = sub_led->fled_id;
	पूर्णांक ret;

	mutex_lock(&led->lock);

	अगर (!state) अणु
		ret = max77693_clear_mode(led, MODE_FLASH(fled_id));
		जाओ unlock;
	पूर्ण

	अगर (sub_led->flash_समयout != led->current_flash_समयout) अणु
		ret = max77693_set_समयout(led, sub_led->flash_समयout);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

	led->strobing_sub_led_id = fled_id;

	ret = max77693_add_mode(led, MODE_FLASH(fled_id));
	अगर (ret < 0)
		जाओ unlock;

	ret = max77693_get_flash_faults(sub_led);

unlock:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max77693_led_flash_fault_get(
				काष्ठा led_classdev_flash *fled_cdev,
				u32 *fault)
अणु
	काष्ठा max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);

	*fault = sub_led->flash_faults;

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_led_flash_strobe_get(
				काष्ठा led_classdev_flash *fled_cdev,
				bool *state)
अणु
	काष्ठा max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	पूर्णांक ret;

	अगर (!state)
		वापस -EINVAL;

	mutex_lock(&led->lock);

	ret = max77693_get_strobe_status(led, state);

	*state = !!(*state && (led->strobing_sub_led_id == sub_led->fled_id));

	mutex_unlock(&led->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_led_flash_समयout_set(
				काष्ठा led_classdev_flash *fled_cdev,
				u32 समयout)
अणु
	काष्ठा max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);

	mutex_lock(&led->lock);
	sub_led->flash_समयout = समयout;
	mutex_unlock(&led->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_led_parse_dt(काष्ठा max77693_led_device *led,
				काष्ठा max77693_led_config_data *cfg,
				काष्ठा device_node **sub_nodes)
अणु
	काष्ठा device *dev = &led->pdev->dev;
	काष्ठा max77693_sub_led *sub_leds = led->sub_leds;
	काष्ठा device_node *node = dev_of_node(dev), *child_node;
	काष्ठा property *prop;
	u32 led_sources[2];
	पूर्णांक i, ret, fled_id;

	of_property_पढ़ो_u32(node, "maxim,boost-mode", &cfg->boost_mode);
	of_property_पढ़ो_u32(node, "maxim,boost-mvout", &cfg->boost_vout);
	of_property_पढ़ो_u32(node, "maxim,mvsys-min", &cfg->low_vsys);

	क्रम_each_available_child_of_node(node, child_node) अणु
		prop = of_find_property(child_node, "led-sources", शून्य);
		अगर (prop) अणु
			स्थिर __be32 *srcs = शून्य;

			क्रम (i = 0; i < ARRAY_SIZE(led_sources); ++i) अणु
				srcs = of_prop_next_u32(prop, srcs,
							&led_sources[i]);
				अगर (!srcs)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"led-sources DT property missing\n");
			of_node_put(child_node);
			वापस -EINVAL;
		पूर्ण

		अगर (i == 2) अणु
			fled_id = FLED1;
			led->fled_mask = FLED1_IOUT | FLED2_IOUT;
		पूर्ण अन्यथा अगर (led_sources[0] == FLED1) अणु
			fled_id = FLED1;
			led->fled_mask |= FLED1_IOUT;
		पूर्ण अन्यथा अगर (led_sources[0] == FLED2) अणु
			fled_id = FLED2;
			led->fled_mask |= FLED2_IOUT;
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"Wrong led-sources DT property value.\n");
			of_node_put(child_node);
			वापस -EINVAL;
		पूर्ण

		अगर (sub_nodes[fled_id]) अणु
			dev_err(dev,
				"Conflicting \"led-sources\" DT properties\n");
			of_node_put(child_node);
			वापस -EINVAL;
		पूर्ण

		sub_nodes[fled_id] = child_node;
		sub_leds[fled_id].fled_id = fled_id;

		cfg->label[fled_id] =
			of_get_property(child_node, "label", शून्य) ? :
						child_node->name;

		ret = of_property_पढ़ो_u32(child_node, "led-max-microamp",
					&cfg->iout_torch_max[fled_id]);
		अगर (ret < 0) अणु
			cfg->iout_torch_max[fled_id] = TORCH_IOUT_MIN;
			dev_warn(dev, "led-max-microamp DT property missing\n");
		पूर्ण

		ret = of_property_पढ़ो_u32(child_node, "flash-max-microamp",
					&cfg->iout_flash_max[fled_id]);
		अगर (ret < 0) अणु
			cfg->iout_flash_max[fled_id] = FLASH_IOUT_MIN;
			dev_warn(dev,
				 "flash-max-microamp DT property missing\n");
		पूर्ण

		ret = of_property_पढ़ो_u32(child_node, "flash-max-timeout-us",
					&cfg->flash_समयout_max[fled_id]);
		अगर (ret < 0) अणु
			cfg->flash_समयout_max[fled_id] = FLASH_TIMEOUT_MIN;
			dev_warn(dev,
				 "flash-max-timeout-us DT property missing\n");
		पूर्ण

		अगर (++cfg->num_leds == 2 ||
		    (max77693_fled_used(led, FLED1) &&
		     max77693_fled_used(led, FLED2))) अणु
			of_node_put(child_node);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cfg->num_leds == 0) अणु
		dev_err(dev, "No DT child node found for connected LED(s).\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clamp_align(u32 *v, u32 min, u32 max, u32 step)
अणु
	*v = clamp_val(*v, min, max);
	अगर (step > 1)
		*v = (*v - min) / step * step + min;
पूर्ण

अटल व्योम max77693_align_iout_current(काष्ठा max77693_led_device *led,
					u32 *iout, u32 min, u32 max, u32 step)
अणु
	पूर्णांक i;

	अगर (led->iout_joपूर्णांक) अणु
		अगर (iout[FLED1] > min) अणु
			iout[FLED1] /= 2;
			iout[FLED2] = iout[FLED1];
		पूर्ण अन्यथा अणु
			iout[FLED1] = min;
			iout[FLED2] = 0;
			वापस;
		पूर्ण
	पूर्ण

	क्रम (i = FLED1; i <= FLED2; ++i)
		अगर (max77693_fled_used(led, i))
			clamp_align(&iout[i], min, max, step);
		अन्यथा
			iout[i] = 0;
पूर्ण

अटल व्योम max77693_led_validate_configuration(काष्ठा max77693_led_device *led,
					काष्ठा max77693_led_config_data *cfg)
अणु
	u32 flash_iout_max = cfg->boost_mode ? FLASH_IOUT_MAX_2LEDS :
					       FLASH_IOUT_MAX_1LED;
	पूर्णांक i;

	अगर (cfg->num_leds == 1 &&
	    max77693_fled_used(led, FLED1) && max77693_fled_used(led, FLED2))
		led->iout_joपूर्णांक = true;

	cfg->boost_mode = clamp_val(cfg->boost_mode, MAX77693_LED_BOOST_NONE,
			    MAX77693_LED_BOOST_FIXED);

	/* Boost must be enabled अगर both current outमाला_दो are used */
	अगर ((cfg->boost_mode == MAX77693_LED_BOOST_NONE) && led->iout_joपूर्णांक)
		cfg->boost_mode = MAX77693_LED_BOOST_FIXED;

	max77693_align_iout_current(led, cfg->iout_torch_max,
			TORCH_IOUT_MIN, TORCH_IOUT_MAX, TORCH_IOUT_STEP);

	max77693_align_iout_current(led, cfg->iout_flash_max,
			FLASH_IOUT_MIN, flash_iout_max, FLASH_IOUT_STEP);

	क्रम (i = 0; i < ARRAY_SIZE(cfg->flash_समयout_max); ++i)
		clamp_align(&cfg->flash_समयout_max[i], FLASH_TIMEOUT_MIN,
				FLASH_TIMEOUT_MAX, FLASH_TIMEOUT_STEP);

	clamp_align(&cfg->boost_vout, FLASH_VOUT_MIN, FLASH_VOUT_MAX,
							FLASH_VOUT_STEP);

	अगर (cfg->low_vsys)
		clamp_align(&cfg->low_vsys, MAX_FLASH1_VSYS_MIN,
				MAX_FLASH1_VSYS_MAX, MAX_FLASH1_VSYS_STEP);
पूर्ण

अटल पूर्णांक max77693_led_get_configuration(काष्ठा max77693_led_device *led,
				काष्ठा max77693_led_config_data *cfg,
				काष्ठा device_node **sub_nodes)
अणु
	पूर्णांक ret;

	ret = max77693_led_parse_dt(led, cfg, sub_nodes);
	अगर (ret < 0)
		वापस ret;

	max77693_led_validate_configuration(led, cfg);

	स_नकल(led->iout_torch_max, cfg->iout_torch_max,
				माप(led->iout_torch_max));
	स_नकल(led->iout_flash_max, cfg->iout_flash_max,
				माप(led->iout_flash_max));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा led_flash_ops flash_ops = अणु
	.flash_brightness_set	= max77693_led_flash_brightness_set,
	.strobe_set		= max77693_led_flash_strobe_set,
	.strobe_get		= max77693_led_flash_strobe_get,
	.समयout_set		= max77693_led_flash_समयout_set,
	.fault_get		= max77693_led_flash_fault_get,
पूर्ण;

अटल व्योम max77693_init_flash_settings(काष्ठा max77693_sub_led *sub_led,
				 काष्ठा max77693_led_config_data *led_cfg)
अणु
	काष्ठा led_classdev_flash *fled_cdev = &sub_led->fled_cdev;
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	पूर्णांक fled_id = sub_led->fled_id;
	काष्ठा led_flash_setting *setting;

	/* Init flash पूर्णांकensity setting */
	setting = &fled_cdev->brightness;
	setting->min = FLASH_IOUT_MIN;
	setting->max = led->iout_joपूर्णांक ?
		led_cfg->iout_flash_max[FLED1] +
		led_cfg->iout_flash_max[FLED2] :
		led_cfg->iout_flash_max[fled_id];
	setting->step = FLASH_IOUT_STEP;
	setting->val = setting->max;

	/* Init flash समयout setting */
	setting = &fled_cdev->समयout;
	setting->min = FLASH_TIMEOUT_MIN;
	setting->max = led_cfg->flash_समयout_max[fled_id];
	setting->step = FLASH_TIMEOUT_STEP;
	setting->val = setting->max;
पूर्ण

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)

अटल पूर्णांक max77693_led_बाह्यal_strobe_set(
				काष्ठा v4l2_flash *v4l2_flash,
				bool enable)
अणु
	काष्ठा max77693_sub_led *sub_led =
				flcdev_to_sub_led(v4l2_flash->fled_cdev);
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	पूर्णांक fled_id = sub_led->fled_id;
	पूर्णांक ret;

	mutex_lock(&led->lock);

	अगर (enable)
		ret = max77693_add_mode(led, MODE_FLASH_EXTERNAL(fled_id));
	अन्यथा
		ret = max77693_clear_mode(led, MODE_FLASH_EXTERNAL(fled_id));

	mutex_unlock(&led->lock);

	वापस ret;
पूर्ण

अटल व्योम max77693_init_v4l2_flash_config(काष्ठा max77693_sub_led *sub_led,
				काष्ठा max77693_led_config_data *led_cfg,
				काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	काष्ठा device *dev = &led->pdev->dev;
	काष्ठा max77693_dev *iodev = dev_get_drvdata(dev->parent);
	काष्ठा i2c_client *i2c = iodev->i2c;
	काष्ठा led_flash_setting *s;

	snम_लिखो(v4l2_sd_cfg->dev_name, माप(v4l2_sd_cfg->dev_name),
		 "%s %d-%04x", sub_led->fled_cdev.led_cdev.name,
		 i2c_adapter_id(i2c->adapter), i2c->addr);

	s = &v4l2_sd_cfg->पूर्णांकensity;
	s->min = TORCH_IOUT_MIN;
	s->max = sub_led->fled_cdev.led_cdev.max_brightness * TORCH_IOUT_STEP;
	s->step = TORCH_IOUT_STEP;
	s->val = s->max;

	/* Init flash faults config */
	v4l2_sd_cfg->flash_faults = LED_FAULT_OVER_VOLTAGE |
				LED_FAULT_SHORT_CIRCUIT |
				LED_FAULT_OVER_CURRENT;

	v4l2_sd_cfg->has_बाह्यal_strobe = true;
पूर्ण

अटल स्थिर काष्ठा v4l2_flash_ops v4l2_flash_ops = अणु
	.बाह्यal_strobe_set = max77693_led_बाह्यal_strobe_set,
पूर्ण;
#अन्यथा
अटल अंतरभूत व्योम max77693_init_v4l2_flash_config(
				काष्ठा max77693_sub_led *sub_led,
				काष्ठा max77693_led_config_data *led_cfg,
				काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
पूर्ण
अटल स्थिर काष्ठा v4l2_flash_ops v4l2_flash_ops;
#पूर्ण_अगर

अटल व्योम max77693_init_fled_cdev(काष्ठा max77693_sub_led *sub_led,
				काष्ठा max77693_led_config_data *led_cfg)
अणु
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	पूर्णांक fled_id = sub_led->fled_id;
	काष्ठा led_classdev_flash *fled_cdev;
	काष्ठा led_classdev *led_cdev;

	/* Initialize LED Flash class device */
	fled_cdev = &sub_led->fled_cdev;
	fled_cdev->ops = &flash_ops;
	led_cdev = &fled_cdev->led_cdev;

	led_cdev->name = led_cfg->label[fled_id];

	led_cdev->brightness_set_blocking = max77693_led_brightness_set;
	led_cdev->max_brightness = (led->iout_joपूर्णांक ?
					led_cfg->iout_torch_max[FLED1] +
					led_cfg->iout_torch_max[FLED2] :
					led_cfg->iout_torch_max[fled_id]) /
				   TORCH_IOUT_STEP;
	led_cdev->flags |= LED_DEV_CAP_FLASH;

	max77693_init_flash_settings(sub_led, led_cfg);

	/* Init flash समयout cache */
	sub_led->flash_समयout = fled_cdev->समयout.val;
पूर्ण

अटल पूर्णांक max77693_रेजिस्टर_led(काष्ठा max77693_sub_led *sub_led,
				 काष्ठा max77693_led_config_data *led_cfg,
				 काष्ठा device_node *sub_node)
अणु
	काष्ठा max77693_led_device *led = sub_led_to_led(sub_led);
	काष्ठा led_classdev_flash *fled_cdev = &sub_led->fled_cdev;
	काष्ठा device *dev = &led->pdev->dev;
	काष्ठा v4l2_flash_config v4l2_sd_cfg = अणुपूर्ण;
	पूर्णांक ret;

	/* Register in the LED subप्रणाली */
	ret = led_classdev_flash_रेजिस्टर(dev, fled_cdev);
	अगर (ret < 0)
		वापस ret;

	max77693_init_v4l2_flash_config(sub_led, led_cfg, &v4l2_sd_cfg);

	/* Register in the V4L2 subप्रणाली. */
	sub_led->v4l2_flash = v4l2_flash_init(dev, of_fwnode_handle(sub_node),
					      fled_cdev, &v4l2_flash_ops,
					      &v4l2_sd_cfg);
	अगर (IS_ERR(sub_led->v4l2_flash)) अणु
		ret = PTR_ERR(sub_led->v4l2_flash);
		जाओ err_v4l2_flash_init;
	पूर्ण

	वापस 0;

err_v4l2_flash_init:
	led_classdev_flash_unरेजिस्टर(fled_cdev);
	वापस ret;
पूर्ण

अटल पूर्णांक max77693_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा max77693_dev *iodev = dev_get_drvdata(dev->parent);
	काष्ठा max77693_led_device *led;
	काष्ठा max77693_sub_led *sub_leds;
	काष्ठा device_node *sub_nodes[2] = अणुपूर्ण;
	काष्ठा max77693_led_config_data led_cfg = अणुपूर्ण;
	पूर्णांक init_fled_cdev[2], i, ret;

	led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->pdev = pdev;
	led->regmap = iodev->regmap;
	led->allowed_modes = MODE_FLASH_MASK;
	sub_leds = led->sub_leds;

	platक्रमm_set_drvdata(pdev, led);
	ret = max77693_led_get_configuration(led, &led_cfg, sub_nodes);
	अगर (ret < 0)
		वापस ret;

	ret = max77693_setup(led, &led_cfg);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&led->lock);

	init_fled_cdev[FLED1] =
			led->iout_joपूर्णांक || max77693_fled_used(led, FLED1);
	init_fled_cdev[FLED2] =
			!led->iout_joपूर्णांक && max77693_fled_used(led, FLED2);

	क्रम (i = FLED1; i <= FLED2; ++i) अणु
		अगर (!init_fled_cdev[i])
			जारी;

		/* Initialize LED Flash class device */
		max77693_init_fled_cdev(&sub_leds[i], &led_cfg);

		/*
		 * Register LED Flash class device and corresponding
		 * V4L2 Flash device.
		 */
		ret = max77693_रेजिस्टर_led(&sub_leds[i], &led_cfg,
						sub_nodes[i]);
		अगर (ret < 0) अणु
			/*
			 * At this moment FLED1 might have been alपढ़ोy
			 * रेजिस्टरed and it needs to be released.
			 */
			अगर (i == FLED2)
				जाओ err_रेजिस्टर_led2;
			अन्यथा
				जाओ err_रेजिस्टर_led1;
		पूर्ण
	पूर्ण

	वापस 0;

err_रेजिस्टर_led2:
	/* It is possible than only FLED2 was to be रेजिस्टरed */
	अगर (!init_fled_cdev[FLED1])
		जाओ err_रेजिस्टर_led1;
	v4l2_flash_release(sub_leds[FLED1].v4l2_flash);
	led_classdev_flash_unरेजिस्टर(&sub_leds[FLED1].fled_cdev);
err_रेजिस्टर_led1:
	mutex_destroy(&led->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77693_led_device *led = platक्रमm_get_drvdata(pdev);
	काष्ठा max77693_sub_led *sub_leds = led->sub_leds;

	अगर (led->iout_joपूर्णांक || max77693_fled_used(led, FLED1)) अणु
		v4l2_flash_release(sub_leds[FLED1].v4l2_flash);
		led_classdev_flash_unरेजिस्टर(&sub_leds[FLED1].fled_cdev);
	पूर्ण

	अगर (!led->iout_joपूर्णांक && max77693_fled_used(led, FLED2)) अणु
		v4l2_flash_release(sub_leds[FLED2].v4l2_flash);
		led_classdev_flash_unरेजिस्टर(&sub_leds[FLED2].fled_cdev);
	पूर्ण

	mutex_destroy(&led->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max77693_led_dt_match[] = अणु
	अणु .compatible = "maxim,max77693-led" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max77693_led_dt_match);

अटल काष्ठा platक्रमm_driver max77693_led_driver = अणु
	.probe		= max77693_led_probe,
	.हटाओ		= max77693_led_हटाओ,
	.driver		= अणु
		.name	= "max77693-led",
		.of_match_table = max77693_led_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(max77693_led_driver);

MODULE_AUTHOR("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODULE_AUTHOR("Andrzej Hajda <a.hajda@samsung.com>");
MODULE_DESCRIPTION("Maxim MAX77693 led flash driver");
MODULE_LICENSE("GPL v2");
