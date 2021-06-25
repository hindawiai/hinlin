<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Lights protocol driver.
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/greybus.h>
#समावेश <media/v4l2-flash-led-class.h>

#घोषणा NAMES_MAX	32

काष्ठा gb_channel अणु
	u8				id;
	u32				flags;
	u32				color;
	अक्षर				*color_name;
	u8				fade_in;
	u8				fade_out;
	u32				mode;
	अक्षर				*mode_name;
	काष्ठा attribute		**attrs;
	काष्ठा attribute_group		*attr_group;
	स्थिर काष्ठा attribute_group	**attr_groups;
	काष्ठा led_classdev		*led;
#अगर IS_REACHABLE(CONFIG_LEDS_CLASS_FLASH)
	काष्ठा led_classdev_flash	fled;
	काष्ठा led_flash_setting	पूर्णांकensity_uA;
	काष्ठा led_flash_setting	समयout_us;
#अन्यथा
	काष्ठा led_classdev		cled;
#पूर्ण_अगर
	काष्ठा gb_light			*light;
	bool				is_रेजिस्टरed;
	bool				releasing;
	bool				strobe_state;
	bool				active;
	काष्ठा mutex			lock;
पूर्ण;

काष्ठा gb_light अणु
	u8			id;
	अक्षर			*name;
	काष्ठा gb_lights	*glights;
	u32			flags;
	u8			channels_count;
	काष्ठा gb_channel	*channels;
	bool			has_flash;
	bool			पढ़ोy;
#अगर IS_REACHABLE(CONFIG_V4L2_FLASH_LED_CLASS)
	काष्ठा v4l2_flash	*v4l2_flash;
	काष्ठा v4l2_flash	*v4l2_flash_ind;
#पूर्ण_अगर
पूर्ण;

काष्ठा gb_lights अणु
	काष्ठा gb_connection	*connection;
	u8			lights_count;
	काष्ठा gb_light		*lights;
	काष्ठा mutex		lights_lock;
पूर्ण;

अटल व्योम gb_lights_channel_मुक्त(काष्ठा gb_channel *channel);

अटल काष्ठा gb_connection *get_conn_from_channel(काष्ठा gb_channel *channel)
अणु
	वापस channel->light->glights->connection;
पूर्ण

अटल काष्ठा gb_connection *get_conn_from_light(काष्ठा gb_light *light)
अणु
	वापस light->glights->connection;
पूर्ण

अटल bool is_channel_flash(काष्ठा gb_channel *channel)
अणु
	वापस !!(channel->mode & (GB_CHANNEL_MODE_FLASH | GB_CHANNEL_MODE_TORCH
				   | GB_CHANNEL_MODE_INDICATOR));
पूर्ण

#अगर IS_REACHABLE(CONFIG_LEDS_CLASS_FLASH)
अटल काष्ठा gb_channel *get_channel_from_cdev(काष्ठा led_classdev *cdev)
अणु
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(cdev);

	वापस container_of(fled_cdev, काष्ठा gb_channel, fled);
पूर्ण

अटल काष्ठा led_classdev *get_channel_cdev(काष्ठा gb_channel *channel)
अणु
	वापस &channel->fled.led_cdev;
पूर्ण

अटल काष्ठा gb_channel *get_channel_from_mode(काष्ठा gb_light *light,
						u32 mode)
अणु
	काष्ठा gb_channel *channel = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < light->channels_count; i++) अणु
		channel = &light->channels[i];
		अगर (channel && channel->mode == mode)
			अवरोध;
	पूर्ण
	वापस channel;
पूर्ण

अटल पूर्णांक __gb_lights_flash_पूर्णांकensity_set(काष्ठा gb_channel *channel,
					   u32 पूर्णांकensity)
अणु
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	काष्ठा gb_lights_set_flash_पूर्णांकensity_request req;
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस -ESHUTDOWN;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		वापस ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.पूर्णांकensity_uA = cpu_to_le32(पूर्णांकensity);

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_FLASH_INTENSITY,
				&req, माप(req), शून्य, 0);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक __gb_lights_flash_brightness_set(काष्ठा gb_channel *channel)
अणु
	u32 पूर्णांकensity;

	/* If the channel is flash we need to get the attached torch channel */
	अगर (channel->mode & GB_CHANNEL_MODE_FLASH)
		channel = get_channel_from_mode(channel->light,
						GB_CHANNEL_MODE_TORCH);

	/* For not flash we need to convert brightness to पूर्णांकensity */
	पूर्णांकensity = channel->पूर्णांकensity_uA.min +
			(channel->पूर्णांकensity_uA.step * channel->led->brightness);

	वापस __gb_lights_flash_पूर्णांकensity_set(channel, पूर्णांकensity);
पूर्ण
#अन्यथा
अटल काष्ठा gb_channel *get_channel_from_cdev(काष्ठा led_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा gb_channel, cled);
पूर्ण

अटल काष्ठा led_classdev *get_channel_cdev(काष्ठा gb_channel *channel)
अणु
	वापस &channel->cled;
पूर्ण

अटल पूर्णांक __gb_lights_flash_brightness_set(काष्ठा gb_channel *channel)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक gb_lights_color_set(काष्ठा gb_channel *channel, u32 color);
अटल पूर्णांक gb_lights_fade_set(काष्ठा gb_channel *channel);

अटल व्योम led_lock(काष्ठा led_classdev *cdev)
अणु
	mutex_lock(&cdev->led_access);
पूर्ण

अटल व्योम led_unlock(काष्ठा led_classdev *cdev)
अणु
	mutex_unlock(&cdev->led_access);
पूर्ण

#घोषणा gb_lights_fade_attr(__dir)					\
अटल sमाप_प्रकार fade_##__dir##_show(काष्ठा device *dev,			\
				   काष्ठा device_attribute *attr,	\
				   अक्षर *buf)				\
अणु									\
	काष्ठा led_classdev *cdev = dev_get_drvdata(dev);		\
	काष्ठा gb_channel *channel = get_channel_from_cdev(cdev);	\
									\
	वापस प्र_लिखो(buf, "%u\n", channel->fade_##__dir);		\
पूर्ण									\
									\
अटल sमाप_प्रकार fade_##__dir##_store(काष्ठा device *dev,			\
				    काष्ठा device_attribute *attr,	\
				    स्थिर अक्षर *buf, माप_प्रकार size)	\
अणु									\
	काष्ठा led_classdev *cdev = dev_get_drvdata(dev);		\
	काष्ठा gb_channel *channel = get_channel_from_cdev(cdev);	\
	u8 fade;							\
	पूर्णांक ret;							\
									\
	led_lock(cdev);							\
	अगर (led_sysfs_is_disabled(cdev)) अणु				\
		ret = -EBUSY;						\
		जाओ unlock;						\
	पूर्ण								\
									\
	ret = kstrtou8(buf, 0, &fade);					\
	अगर (ret < 0) अणु							\
		dev_err(dev, "could not parse fade value %d\n", ret);	\
		जाओ unlock;						\
	पूर्ण								\
	अगर (channel->fade_##__dir == fade)				\
		जाओ unlock;						\
	channel->fade_##__dir = fade;					\
									\
	ret = gb_lights_fade_set(channel);				\
	अगर (ret < 0)							\
		जाओ unlock;						\
									\
	ret = size;							\
unlock:									\
	led_unlock(cdev);						\
	वापस ret;							\
पूर्ण									\
अटल DEVICE_ATTR_RW(fade_##__dir)

gb_lights_fade_attr(in);
gb_lights_fade_attr(out);

अटल sमाप_प्रकार color_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा led_classdev *cdev = dev_get_drvdata(dev);
	काष्ठा gb_channel *channel = get_channel_from_cdev(cdev);

	वापस प्र_लिखो(buf, "0x%08x\n", channel->color);
पूर्ण

अटल sमाप_प्रकार color_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *cdev = dev_get_drvdata(dev);
	काष्ठा gb_channel *channel = get_channel_from_cdev(cdev);
	u32 color;
	पूर्णांक ret;

	led_lock(cdev);
	अगर (led_sysfs_is_disabled(cdev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण
	ret = kstrtou32(buf, 0, &color);
	अगर (ret < 0) अणु
		dev_err(dev, "could not parse color value %d\n", ret);
		जाओ unlock;
	पूर्ण

	ret = gb_lights_color_set(channel, color);
	अगर (ret < 0)
		जाओ unlock;

	channel->color = color;
	ret = size;
unlock:
	led_unlock(cdev);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(color);

अटल पूर्णांक channel_attr_groups_set(काष्ठा gb_channel *channel,
				   काष्ठा led_classdev *cdev)
अणु
	पूर्णांक attr = 0;
	पूर्णांक size = 0;

	अगर (channel->flags & GB_LIGHT_CHANNEL_MULTICOLOR)
		size++;
	अगर (channel->flags & GB_LIGHT_CHANNEL_FADER)
		size += 2;

	अगर (!size)
		वापस 0;

	/* Set attributes based in the channel flags */
	channel->attrs = kसुस्मृति(size + 1, माप(*channel->attrs), GFP_KERNEL);
	अगर (!channel->attrs)
		वापस -ENOMEM;
	channel->attr_group = kzalloc(माप(*channel->attr_group), GFP_KERNEL);
	अगर (!channel->attr_group)
		वापस -ENOMEM;
	channel->attr_groups = kसुस्मृति(2, माप(*channel->attr_groups),
				       GFP_KERNEL);
	अगर (!channel->attr_groups)
		वापस -ENOMEM;

	अगर (channel->flags & GB_LIGHT_CHANNEL_MULTICOLOR)
		channel->attrs[attr++] = &dev_attr_color.attr;
	अगर (channel->flags & GB_LIGHT_CHANNEL_FADER) अणु
		channel->attrs[attr++] = &dev_attr_fade_in.attr;
		channel->attrs[attr++] = &dev_attr_fade_out.attr;
	पूर्ण

	channel->attr_group->attrs = channel->attrs;

	channel->attr_groups[0] = channel->attr_group;

	cdev->groups = channel->attr_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_lights_fade_set(काष्ठा gb_channel *channel)
अणु
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	काष्ठा gb_lights_set_fade_request req;
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस -ESHUTDOWN;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		वापस ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.fade_in = channel->fade_in;
	req.fade_out = channel->fade_out;
	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_FADE,
				&req, माप(req), शून्य, 0);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_lights_color_set(काष्ठा gb_channel *channel, u32 color)
अणु
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	काष्ठा gb_lights_set_color_request req;
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस -ESHUTDOWN;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		वापस ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.color = cpu_to_le32(color);
	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_COLOR,
				&req, माप(req), शून्य, 0);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक __gb_lights_led_brightness_set(काष्ठा gb_channel *channel)
अणु
	काष्ठा gb_lights_set_brightness_request req;
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	bool old_active;
	पूर्णांक ret;

	mutex_lock(&channel->lock);
	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		जाओ out_unlock;

	old_active = channel->active;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.brightness = (u8)channel->led->brightness;

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_BRIGHTNESS,
				&req, माप(req), शून्य, 0);
	अगर (ret < 0)
		जाओ out_pm_put;

	अगर (channel->led->brightness)
		channel->active = true;
	अन्यथा
		channel->active = false;

	/* we need to keep module alive when turning to active state */
	अगर (!old_active && channel->active)
		जाओ out_unlock;

	/*
	 * on the other hand अगर going to inactive we still hold a reference and
	 * need to put it, so we could go to suspend.
	 */
	अगर (old_active && !channel->active)
		gb_pm_runसमय_put_स्वतःsuspend(bundle);

out_pm_put:
	gb_pm_runसमय_put_स्वतःsuspend(bundle);
out_unlock:
	mutex_unlock(&channel->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __gb_lights_brightness_set(काष्ठा gb_channel *channel)
अणु
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस 0;

	अगर (is_channel_flash(channel))
		ret = __gb_lights_flash_brightness_set(channel);
	अन्यथा
		ret = __gb_lights_led_brightness_set(channel);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_brightness_set(काष्ठा led_classdev *cdev,
			     क्रमागत led_brightness value)
अणु
	काष्ठा gb_channel *channel = get_channel_from_cdev(cdev);

	channel->led->brightness = value;

	वापस __gb_lights_brightness_set(channel);
पूर्ण

अटल क्रमागत led_brightness gb_brightness_get(काष्ठा led_classdev *cdev)

अणु
	काष्ठा gb_channel *channel = get_channel_from_cdev(cdev);

	वापस channel->led->brightness;
पूर्ण

अटल पूर्णांक gb_blink_set(काष्ठा led_classdev *cdev, अचिन्हित दीर्घ *delay_on,
			अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा gb_channel *channel = get_channel_from_cdev(cdev);
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	काष्ठा gb_lights_blink_request req;
	bool old_active;
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस -ESHUTDOWN;

	अगर (!delay_on || !delay_off)
		वापस -EINVAL;

	mutex_lock(&channel->lock);
	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		जाओ out_unlock;

	old_active = channel->active;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.समय_on_ms = cpu_to_le16(*delay_on);
	req.समय_off_ms = cpu_to_le16(*delay_off);

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_BLINK, &req,
				माप(req), शून्य, 0);
	अगर (ret < 0)
		जाओ out_pm_put;

	अगर (*delay_on)
		channel->active = true;
	अन्यथा
		channel->active = false;

	/* we need to keep module alive when turning to active state */
	अगर (!old_active && channel->active)
		जाओ out_unlock;

	/*
	 * on the other hand अगर going to inactive we still hold a reference and
	 * need to put it, so we could go to suspend.
	 */
	अगर (old_active && !channel->active)
		gb_pm_runसमय_put_स्वतःsuspend(bundle);

out_pm_put:
	gb_pm_runसमय_put_स्वतःsuspend(bundle);
out_unlock:
	mutex_unlock(&channel->lock);

	वापस ret;
पूर्ण

अटल व्योम gb_lights_led_operations_set(काष्ठा gb_channel *channel,
					 काष्ठा led_classdev *cdev)
अणु
	cdev->brightness_get = gb_brightness_get;
	cdev->brightness_set_blocking = gb_brightness_set;

	अगर (channel->flags & GB_LIGHT_CHANNEL_BLINK)
		cdev->blink_set = gb_blink_set;
पूर्ण

#अगर IS_REACHABLE(CONFIG_V4L2_FLASH_LED_CLASS)
/* V4L2 specअगरic helpers */
अटल स्थिर काष्ठा v4l2_flash_ops v4l2_flash_ops;

अटल व्योम __gb_lights_channel_v4l2_config(काष्ठा led_flash_setting *channel_s,
					    काष्ठा led_flash_setting *v4l2_s)
अणु
	v4l2_s->min = channel_s->min;
	v4l2_s->max = channel_s->max;
	v4l2_s->step = channel_s->step;
	/* For v4l2 val is the शेष value */
	v4l2_s->val = channel_s->max;
पूर्ण

अटल पूर्णांक gb_lights_light_v4l2_रेजिस्टर(काष्ठा gb_light *light)
अणु
	काष्ठा gb_connection *connection = get_conn_from_light(light);
	काष्ठा device *dev = &connection->bundle->dev;
	काष्ठा v4l2_flash_config sd_cfg = अणु अणु0पूर्ण पूर्ण, sd_cfg_ind = अणु अणु0पूर्ण पूर्ण;
	काष्ठा led_classdev_flash *fled;
	काष्ठा led_classdev *iled = शून्य;
	काष्ठा gb_channel *channel_torch, *channel_ind, *channel_flash;

	channel_torch = get_channel_from_mode(light, GB_CHANNEL_MODE_TORCH);
	अगर (channel_torch)
		__gb_lights_channel_v4l2_config(&channel_torch->पूर्णांकensity_uA,
						&sd_cfg.पूर्णांकensity);

	channel_ind = get_channel_from_mode(light, GB_CHANNEL_MODE_INDICATOR);
	अगर (channel_ind) अणु
		__gb_lights_channel_v4l2_config(&channel_ind->पूर्णांकensity_uA,
						&sd_cfg_ind.पूर्णांकensity);
		iled = &channel_ind->fled.led_cdev;
	पूर्ण

	channel_flash = get_channel_from_mode(light, GB_CHANNEL_MODE_FLASH);
	WARN_ON(!channel_flash);

	fled = &channel_flash->fled;

	snम_लिखो(sd_cfg.dev_name, माप(sd_cfg.dev_name), "%s", light->name);
	snम_लिखो(sd_cfg_ind.dev_name, माप(sd_cfg_ind.dev_name),
		 "%s indicator", light->name);

	/* Set the possible values to faults, in our हाल all faults */
	sd_cfg.flash_faults = LED_FAULT_OVER_VOLTAGE | LED_FAULT_TIMEOUT |
		LED_FAULT_OVER_TEMPERATURE | LED_FAULT_SHORT_CIRCUIT |
		LED_FAULT_OVER_CURRENT | LED_FAULT_INDICATOR |
		LED_FAULT_UNDER_VOLTAGE | LED_FAULT_INPUT_VOLTAGE |
		LED_FAULT_LED_OVER_TEMPERATURE;

	light->v4l2_flash = v4l2_flash_init(dev, शून्य, fled, &v4l2_flash_ops,
					    &sd_cfg);
	अगर (IS_ERR(light->v4l2_flash))
		वापस PTR_ERR(light->v4l2_flash);

	अगर (channel_ind) अणु
		light->v4l2_flash_ind =
			v4l2_flash_indicator_init(dev, शून्य, iled, &sd_cfg_ind);
		अगर (IS_ERR(light->v4l2_flash_ind)) अणु
			v4l2_flash_release(light->v4l2_flash);
			वापस PTR_ERR(light->v4l2_flash_ind);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gb_lights_light_v4l2_unरेजिस्टर(काष्ठा gb_light *light)
अणु
	v4l2_flash_release(light->v4l2_flash_ind);
	v4l2_flash_release(light->v4l2_flash);
पूर्ण
#अन्यथा
अटल पूर्णांक gb_lights_light_v4l2_रेजिस्टर(काष्ठा gb_light *light)
अणु
	काष्ठा gb_connection *connection = get_conn_from_light(light);

	dev_err(&connection->bundle->dev, "no support for v4l2 subdevices\n");
	वापस 0;
पूर्ण

अटल व्योम gb_lights_light_v4l2_unरेजिस्टर(काष्ठा gb_light *light)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_REACHABLE(CONFIG_LEDS_CLASS_FLASH)
/* Flash specअगरic operations */
अटल पूर्णांक gb_lights_flash_पूर्णांकensity_set(काष्ठा led_classdev_flash *fcdev,
					 u32 brightness)
अणु
	काष्ठा gb_channel *channel = container_of(fcdev, काष्ठा gb_channel,
						  fled);
	पूर्णांक ret;

	ret = __gb_lights_flash_पूर्णांकensity_set(channel, brightness);
	अगर (ret < 0)
		वापस ret;

	fcdev->brightness.val = brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_lights_flash_पूर्णांकensity_get(काष्ठा led_classdev_flash *fcdev,
					 u32 *brightness)
अणु
	*brightness = fcdev->brightness.val;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_lights_flash_strobe_set(काष्ठा led_classdev_flash *fcdev,
				      bool state)
अणु
	काष्ठा gb_channel *channel = container_of(fcdev, काष्ठा gb_channel,
						  fled);
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	काष्ठा gb_lights_set_flash_strobe_request req;
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस -ESHUTDOWN;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		वापस ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.state = state ? 1 : 0;

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_FLASH_STROBE,
				&req, माप(req), शून्य, 0);
	अगर (!ret)
		channel->strobe_state = state;

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_lights_flash_strobe_get(काष्ठा led_classdev_flash *fcdev,
				      bool *state)
अणु
	काष्ठा gb_channel *channel = container_of(fcdev, काष्ठा gb_channel,
						  fled);

	*state = channel->strobe_state;
	वापस 0;
पूर्ण

अटल पूर्णांक gb_lights_flash_समयout_set(काष्ठा led_classdev_flash *fcdev,
				       u32 समयout)
अणु
	काष्ठा gb_channel *channel = container_of(fcdev, काष्ठा gb_channel,
						  fled);
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	काष्ठा gb_lights_set_flash_समयout_request req;
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस -ESHUTDOWN;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		वापस ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.समयout_us = cpu_to_le32(समयout);

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_FLASH_TIMEOUT,
				&req, माप(req), शून्य, 0);
	अगर (!ret)
		fcdev->समयout.val = समयout;

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_lights_flash_fault_get(काष्ठा led_classdev_flash *fcdev,
				     u32 *fault)
अणु
	काष्ठा gb_channel *channel = container_of(fcdev, काष्ठा gb_channel,
						  fled);
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_bundle *bundle = connection->bundle;
	काष्ठा gb_lights_get_flash_fault_request req;
	काष्ठा gb_lights_get_flash_fault_response resp;
	पूर्णांक ret;

	अगर (channel->releasing)
		वापस -ESHUTDOWN;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		वापस ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_GET_FLASH_FAULT,
				&req, माप(req), &resp, माप(resp));
	अगर (!ret)
		*fault = le32_to_cpu(resp.fault);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा led_flash_ops gb_lights_flash_ops = अणु
	.flash_brightness_set	= gb_lights_flash_पूर्णांकensity_set,
	.flash_brightness_get	= gb_lights_flash_पूर्णांकensity_get,
	.strobe_set		= gb_lights_flash_strobe_set,
	.strobe_get		= gb_lights_flash_strobe_get,
	.समयout_set		= gb_lights_flash_समयout_set,
	.fault_get		= gb_lights_flash_fault_get,
पूर्ण;

अटल पूर्णांक __gb_lights_channel_torch_attach(काष्ठा gb_channel *channel,
					    काष्ठा gb_channel *channel_torch)
अणु
	अक्षर *name;

	/* we can only attach torch to a flash channel */
	अगर (!(channel->mode & GB_CHANNEL_MODE_FLASH))
		वापस 0;

	/* Move torch brightness to the destination */
	channel->led->max_brightness = channel_torch->led->max_brightness;

	/* append mode name to flash name */
	name = kaप्र_लिखो(GFP_KERNEL, "%s_%s", channel->led->name,
			 channel_torch->mode_name);
	अगर (!name)
		वापस -ENOMEM;
	kमुक्त(channel->led->name);
	channel->led->name = name;

	channel_torch->led = channel->led;

	वापस 0;
पूर्ण

अटल पूर्णांक __gb_lights_flash_led_रेजिस्टर(काष्ठा gb_channel *channel)
अणु
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा led_classdev_flash *fled = &channel->fled;
	काष्ठा led_flash_setting *fset;
	काष्ठा gb_channel *channel_torch;
	पूर्णांक ret;

	fled->ops = &gb_lights_flash_ops;

	fled->led_cdev.flags |= LED_DEV_CAP_FLASH;

	fset = &fled->brightness;
	fset->min = channel->पूर्णांकensity_uA.min;
	fset->max = channel->पूर्णांकensity_uA.max;
	fset->step = channel->पूर्णांकensity_uA.step;
	fset->val = channel->पूर्णांकensity_uA.max;

	/* Only the flash mode have the समयout स्थिरraपूर्णांकs settings */
	अगर (channel->mode & GB_CHANNEL_MODE_FLASH) अणु
		fset = &fled->समयout;
		fset->min = channel->समयout_us.min;
		fset->max = channel->समयout_us.max;
		fset->step = channel->समयout_us.step;
		fset->val = channel->समयout_us.max;
	पूर्ण

	/*
	 * If light have torch mode channel, this channel will be the led
	 * classdev of the रेजिस्टरed above flash classdev
	 */
	channel_torch = get_channel_from_mode(channel->light,
					      GB_CHANNEL_MODE_TORCH);
	अगर (channel_torch) अणु
		ret = __gb_lights_channel_torch_attach(channel, channel_torch);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	ret = led_classdev_flash_रेजिस्टर(&connection->bundle->dev, fled);
	अगर (ret < 0)
		जाओ fail;

	channel->is_रेजिस्टरed = true;
	वापस 0;
fail:
	channel->led = शून्य;
	वापस ret;
पूर्ण

अटल व्योम __gb_lights_flash_led_unरेजिस्टर(काष्ठा gb_channel *channel)
अणु
	अगर (!channel->is_रेजिस्टरed)
		वापस;

	led_classdev_flash_unरेजिस्टर(&channel->fled);
पूर्ण

अटल पूर्णांक gb_lights_channel_flash_config(काष्ठा gb_channel *channel)
अणु
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा gb_lights_get_channel_flash_config_request req;
	काष्ठा gb_lights_get_channel_flash_config_response conf;
	काष्ठा led_flash_setting *fset;
	पूर्णांक ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;

	ret = gb_operation_sync(connection,
				GB_LIGHTS_TYPE_GET_CHANNEL_FLASH_CONFIG,
				&req, माप(req), &conf, माप(conf));
	अगर (ret < 0)
		वापस ret;

	/*
	 * Intensity स्थिरraपूर्णांकs क्रम flash related modes: flash, torch,
	 * indicator.  They will be needed क्रम v4l2 registration.
	 */
	fset = &channel->पूर्णांकensity_uA;
	fset->min = le32_to_cpu(conf.पूर्णांकensity_min_uA);
	fset->max = le32_to_cpu(conf.पूर्णांकensity_max_uA);
	fset->step = le32_to_cpu(conf.पूर्णांकensity_step_uA);

	/*
	 * On flash type, max brightness is set as the number of पूर्णांकensity steps
	 * available.
	 */
	channel->led->max_brightness = (fset->max - fset->min) / fset->step;

	/* Only the flash mode have the समयout स्थिरraपूर्णांकs settings */
	अगर (channel->mode & GB_CHANNEL_MODE_FLASH) अणु
		fset = &channel->समयout_us;
		fset->min = le32_to_cpu(conf.समयout_min_us);
		fset->max = le32_to_cpu(conf.समयout_max_us);
		fset->step = le32_to_cpu(conf.समयout_step_us);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक gb_lights_channel_flash_config(काष्ठा gb_channel *channel)
अणु
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);

	dev_err(&connection->bundle->dev, "no support for flash devices\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __gb_lights_flash_led_रेजिस्टर(काष्ठा gb_channel *channel)
अणु
	वापस 0;
पूर्ण

अटल व्योम __gb_lights_flash_led_unरेजिस्टर(काष्ठा gb_channel *channel)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __gb_lights_led_रेजिस्टर(काष्ठा gb_channel *channel)
अणु
	काष्ठा gb_connection *connection = get_conn_from_channel(channel);
	काष्ठा led_classdev *cdev = get_channel_cdev(channel);
	पूर्णांक ret;

	ret = led_classdev_रेजिस्टर(&connection->bundle->dev, cdev);
	अगर (ret < 0)
		channel->led = शून्य;
	अन्यथा
		channel->is_रेजिस्टरed = true;
	वापस ret;
पूर्ण

अटल पूर्णांक gb_lights_channel_रेजिस्टर(काष्ठा gb_channel *channel)
अणु
	/* Normal LED channel, just रेजिस्टर in led classdev and we are करोne */
	अगर (!is_channel_flash(channel))
		वापस __gb_lights_led_रेजिस्टर(channel);

	/*
	 * Flash Type need more work, रेजिस्टर flash classdev, indicator as
	 * flash classdev, torch will be led classdev of the flash classdev.
	 */
	अगर (!(channel->mode & GB_CHANNEL_MODE_TORCH))
		वापस __gb_lights_flash_led_रेजिस्टर(channel);

	वापस 0;
पूर्ण

अटल व्योम __gb_lights_led_unरेजिस्टर(काष्ठा gb_channel *channel)
अणु
	काष्ठा led_classdev *cdev = get_channel_cdev(channel);

	अगर (!channel->is_रेजिस्टरed)
		वापस;

	led_classdev_unरेजिस्टर(cdev);
	kमुक्त(cdev->name);
	cdev->name = शून्य;
	channel->led = शून्य;
पूर्ण

अटल व्योम gb_lights_channel_unरेजिस्टर(काष्ठा gb_channel *channel)
अणु
	/* The same as रेजिस्टर, handle channels dअगरferently */
	अगर (!is_channel_flash(channel)) अणु
		__gb_lights_led_unरेजिस्टर(channel);
		वापस;
	पूर्ण

	अगर (channel->mode & GB_CHANNEL_MODE_TORCH)
		__gb_lights_led_unरेजिस्टर(channel);
	अन्यथा
		__gb_lights_flash_led_unरेजिस्टर(channel);
पूर्ण

अटल पूर्णांक gb_lights_channel_config(काष्ठा gb_light *light,
				    काष्ठा gb_channel *channel)
अणु
	काष्ठा gb_lights_get_channel_config_response conf;
	काष्ठा gb_lights_get_channel_config_request req;
	काष्ठा gb_connection *connection = get_conn_from_light(light);
	काष्ठा led_classdev *cdev = get_channel_cdev(channel);
	अक्षर *name;
	पूर्णांक ret;

	req.light_id = light->id;
	req.channel_id = channel->id;

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_GET_CHANNEL_CONFIG,
				&req, माप(req), &conf, माप(conf));
	अगर (ret < 0)
		वापस ret;

	channel->light = light;
	channel->mode = le32_to_cpu(conf.mode);
	channel->flags = le32_to_cpu(conf.flags);
	channel->color = le32_to_cpu(conf.color);
	channel->color_name = kstrndup(conf.color_name, NAMES_MAX, GFP_KERNEL);
	अगर (!channel->color_name)
		वापस -ENOMEM;
	channel->mode_name = kstrndup(conf.mode_name, NAMES_MAX, GFP_KERNEL);
	अगर (!channel->mode_name)
		वापस -ENOMEM;

	channel->led = cdev;

	name = kaप्र_लिखो(GFP_KERNEL, "%s:%s:%s", light->name,
			 channel->color_name, channel->mode_name);
	अगर (!name)
		वापस -ENOMEM;

	cdev->name = name;

	cdev->max_brightness = conf.max_brightness;

	ret = channel_attr_groups_set(channel, cdev);
	अगर (ret < 0)
		वापस ret;

	gb_lights_led_operations_set(channel, cdev);

	/*
	 * If it is not a flash related channel (flash, torch or indicator) we
	 * are करोne here. If not, जारी and fetch flash related
	 * configurations.
	 */
	अगर (!is_channel_flash(channel))
		वापस ret;

	light->has_flash = true;

	वापस gb_lights_channel_flash_config(channel);
पूर्ण

अटल पूर्णांक gb_lights_light_config(काष्ठा gb_lights *glights, u8 id)
अणु
	काष्ठा gb_light *light = &glights->lights[id];
	काष्ठा gb_lights_get_light_config_request req;
	काष्ठा gb_lights_get_light_config_response conf;
	पूर्णांक ret;
	पूर्णांक i;

	light->glights = glights;
	light->id = id;

	req.id = id;

	ret = gb_operation_sync(glights->connection,
				GB_LIGHTS_TYPE_GET_LIGHT_CONFIG,
				&req, माप(req), &conf, माप(conf));
	अगर (ret < 0)
		वापस ret;

	अगर (!conf.channel_count)
		वापस -EINVAL;
	अगर (!म_माप(conf.name))
		वापस -EINVAL;

	light->channels_count = conf.channel_count;
	light->name = kstrndup(conf.name, NAMES_MAX, GFP_KERNEL);
	अगर (!light->name)
		वापस -ENOMEM;
	light->channels = kसुस्मृति(light->channels_count,
				  माप(काष्ठा gb_channel), GFP_KERNEL);
	अगर (!light->channels)
		वापस -ENOMEM;

	/* First we collect all the configurations क्रम all channels */
	क्रम (i = 0; i < light->channels_count; i++) अणु
		light->channels[i].id = i;
		ret = gb_lights_channel_config(light, &light->channels[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_lights_light_रेजिस्टर(काष्ठा gb_light *light)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Then, अगर everything went ok in getting configurations, we रेजिस्टर
	 * the classdev, flash classdev and v4l2 subप्रणाली, अगर a flash device is
	 * found.
	 */
	क्रम (i = 0; i < light->channels_count; i++) अणु
		ret = gb_lights_channel_रेजिस्टर(&light->channels[i]);
		अगर (ret < 0)
			वापस ret;

		mutex_init(&light->channels[i].lock);
	पूर्ण

	light->पढ़ोy = true;

	अगर (light->has_flash) अणु
		ret = gb_lights_light_v4l2_रेजिस्टर(light);
		अगर (ret < 0) अणु
			light->has_flash = false;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gb_lights_channel_मुक्त(काष्ठा gb_channel *channel)
अणु
	kमुक्त(channel->attrs);
	kमुक्त(channel->attr_group);
	kमुक्त(channel->attr_groups);
	kमुक्त(channel->color_name);
	kमुक्त(channel->mode_name);
	mutex_destroy(&channel->lock);
पूर्ण

अटल व्योम gb_lights_channel_release(काष्ठा gb_channel *channel)
अणु
	channel->releasing = true;

	gb_lights_channel_unरेजिस्टर(channel);

	gb_lights_channel_मुक्त(channel);
पूर्ण

अटल व्योम gb_lights_light_release(काष्ठा gb_light *light)
अणु
	पूर्णांक i;

	light->पढ़ोy = false;

	अगर (light->has_flash)
		gb_lights_light_v4l2_unरेजिस्टर(light);
	light->has_flash = false;

	क्रम (i = 0; i < light->channels_count; i++)
		gb_lights_channel_release(&light->channels[i]);
	light->channels_count = 0;

	kमुक्त(light->channels);
	light->channels = शून्य;
	kमुक्त(light->name);
	light->name = शून्य;
पूर्ण

अटल व्योम gb_lights_release(काष्ठा gb_lights *glights)
अणु
	पूर्णांक i;

	अगर (!glights)
		वापस;

	mutex_lock(&glights->lights_lock);
	अगर (!glights->lights)
		जाओ मुक्त_glights;

	क्रम (i = 0; i < glights->lights_count; i++)
		gb_lights_light_release(&glights->lights[i]);

	kमुक्त(glights->lights);

मुक्त_glights:
	mutex_unlock(&glights->lights_lock);
	mutex_destroy(&glights->lights_lock);
	kमुक्त(glights);
पूर्ण

अटल पूर्णांक gb_lights_get_count(काष्ठा gb_lights *glights)
अणु
	काष्ठा gb_lights_get_lights_response resp;
	पूर्णांक ret;

	ret = gb_operation_sync(glights->connection, GB_LIGHTS_TYPE_GET_LIGHTS,
				शून्य, 0, &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	अगर (!resp.lights_count)
		वापस -EINVAL;

	glights->lights_count = resp.lights_count;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_lights_create_all(काष्ठा gb_lights *glights)
अणु
	काष्ठा gb_connection *connection = glights->connection;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&glights->lights_lock);
	ret = gb_lights_get_count(glights);
	अगर (ret < 0)
		जाओ out;

	glights->lights = kसुस्मृति(glights->lights_count,
				  माप(काष्ठा gb_light), GFP_KERNEL);
	अगर (!glights->lights) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < glights->lights_count; i++) अणु
		ret = gb_lights_light_config(glights, i);
		अगर (ret < 0) अणु
			dev_err(&connection->bundle->dev,
				"Fail to configure lights device\n");
			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&glights->lights_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_lights_रेजिस्टर_all(काष्ठा gb_lights *glights)
अणु
	काष्ठा gb_connection *connection = glights->connection;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&glights->lights_lock);
	क्रम (i = 0; i < glights->lights_count; i++) अणु
		ret = gb_lights_light_रेजिस्टर(&glights->lights[i]);
		अगर (ret < 0) अणु
			dev_err(&connection->bundle->dev,
				"Fail to enable lights device\n");
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&glights->lights_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_lights_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा device *dev = &connection->bundle->dev;
	काष्ठा gb_lights *glights = gb_connection_get_data(connection);
	काष्ठा gb_light *light;
	काष्ठा gb_message *request;
	काष्ठा gb_lights_event_request *payload;
	पूर्णांक ret =  0;
	u8 light_id;
	u8 event;

	अगर (op->type != GB_LIGHTS_TYPE_EVENT) अणु
		dev_err(dev, "Unsupported unsolicited event: %u\n", op->type);
		वापस -EINVAL;
	पूर्ण

	request = op->request;

	अगर (request->payload_size < माप(*payload)) अणु
		dev_err(dev, "Wrong event size received (%zu < %zu)\n",
			request->payload_size, माप(*payload));
		वापस -EINVAL;
	पूर्ण

	payload = request->payload;
	light_id = payload->light_id;

	अगर (light_id >= glights->lights_count ||
	    !glights->lights[light_id].पढ़ोy) अणु
		dev_err(dev, "Event received for unconfigured light id: %d\n",
			light_id);
		वापस -EINVAL;
	पूर्ण

	event = payload->event;

	अगर (event & GB_LIGHTS_LIGHT_CONFIG) अणु
		light = &glights->lights[light_id];

		mutex_lock(&glights->lights_lock);
		gb_lights_light_release(light);
		ret = gb_lights_light_config(glights, light_id);
		अगर (!ret)
			ret = gb_lights_light_रेजिस्टर(light);
		अगर (ret < 0)
			gb_lights_light_release(light);
		mutex_unlock(&glights->lights_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gb_lights_probe(काष्ठा gb_bundle *bundle,
			   स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_lights *glights;
	पूर्णांक ret;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_LIGHTS)
		वापस -ENODEV;

	glights = kzalloc(माप(*glights), GFP_KERNEL);
	अगर (!glights)
		वापस -ENOMEM;

	mutex_init(&glights->lights_lock);

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_lights_request_handler);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ out;
	पूर्ण

	glights->connection = connection;
	gb_connection_set_data(connection, glights);

	greybus_set_drvdata(bundle, glights);

	/* We aren't पढ़ोy to receive an incoming request yet */
	ret = gb_connection_enable_tx(connection);
	अगर (ret)
		जाओ error_connection_destroy;

	/*
	 * Setup all the lights devices over this connection, अगर anything goes
	 * wrong tear करोwn all lights
	 */
	ret = gb_lights_create_all(glights);
	अगर (ret < 0)
		जाओ error_connection_disable;

	/* We are पढ़ोy to receive an incoming request now, enable RX as well */
	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ error_connection_disable;

	/* Enable & रेजिस्टर lights */
	ret = gb_lights_रेजिस्टर_all(glights);
	अगर (ret < 0)
		जाओ error_connection_disable;

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;

error_connection_disable:
	gb_connection_disable(connection);
error_connection_destroy:
	gb_connection_destroy(connection);
out:
	gb_lights_release(glights);
	वापस ret;
पूर्ण

अटल व्योम gb_lights_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_lights *glights = greybus_get_drvdata(bundle);

	अगर (gb_pm_runसमय_get_sync(bundle))
		gb_pm_runसमय_get_noresume(bundle);

	gb_connection_disable(glights->connection);
	gb_connection_destroy(glights->connection);

	gb_lights_release(glights);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_lights_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_LIGHTS) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_lights_id_table);

अटल काष्ठा greybus_driver gb_lights_driver = अणु
	.name		= "lights",
	.probe		= gb_lights_probe,
	.disconnect	= gb_lights_disconnect,
	.id_table	= gb_lights_id_table,
पूर्ण;
module_greybus_driver(gb_lights_driver);

MODULE_LICENSE("GPL v2");
