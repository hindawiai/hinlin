<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V4L2 flash LED sub-device registration helpers.
 *
 *	Copyright (C) 2015 Samsung Electronics Co., Ltd
 *	Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#समावेश <linux/led-class-flash.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-flash-led-class.h>

#घोषणा has_flash_op(v4l2_flash, op)				\
	(v4l2_flash && v4l2_flash->ops && v4l2_flash->ops->op)

#घोषणा call_flash_op(v4l2_flash, op, arg)			\
		(has_flash_op(v4l2_flash, op) ?			\
			v4l2_flash->ops->op(v4l2_flash, arg) :	\
			-EINVAL)

क्रमागत ctrl_init_data_id अणु
	LED_MODE,
	TORCH_INTENSITY,
	FLASH_INTENSITY,
	INDICATOR_INTENSITY,
	FLASH_TIMEOUT,
	STROBE_SOURCE,
	/*
	 * Only above values are applicable to
	 * the 'ctrls' array in the काष्ठा v4l2_flash.
	 */
	FLASH_STROBE,
	STROBE_STOP,
	STROBE_STATUS,
	FLASH_FAULT,
	NUM_FLASH_CTRLS,
पूर्ण;

अटल क्रमागत led_brightness __पूर्णांकensity_to_led_brightness(
					काष्ठा v4l2_ctrl *ctrl, s32 पूर्णांकensity)
अणु
	पूर्णांकensity -= ctrl->minimum;
	पूर्णांकensity /= (u32) ctrl->step;

	/*
	 * Indicator LEDs, unlike torch LEDs, are turned on/off basing on
	 * the state of V4L2_CID_FLASH_INDICATOR_INTENSITY control only.
	 * Thereक्रमe it must be possible to set it to 0 level which in
	 * the LED subप्रणाली reflects LED_OFF state.
	 */
	अगर (ctrl->minimum)
		++पूर्णांकensity;

	वापस पूर्णांकensity;
पूर्ण

अटल s32 __led_brightness_to_पूर्णांकensity(काष्ठा v4l2_ctrl *ctrl,
					 क्रमागत led_brightness brightness)
अणु
	/*
	 * Indicator LEDs, unlike torch LEDs, are turned on/off basing on
	 * the state of V4L2_CID_FLASH_INDICATOR_INTENSITY control only.
	 * Do not decrement brightness पढ़ो from the LED subप्रणाली क्रम
	 * indicator LED as it may equal 0. For torch LEDs this function
	 * is called only when V4L2_FLASH_LED_MODE_TORCH is set and the
	 * brightness पढ़ो is guaranteed to be greater than 0. In the mode
	 * V4L2_FLASH_LED_MODE_NONE the cached torch पूर्णांकensity value is used.
	 */
	अगर (ctrl->id != V4L2_CID_FLASH_INDICATOR_INTENSITY)
		--brightness;

	वापस (brightness * ctrl->step) + ctrl->minimum;
पूर्ण

अटल व्योम v4l2_flash_set_led_brightness(काष्ठा v4l2_flash *v4l2_flash,
					काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_ctrl **ctrls = v4l2_flash->ctrls;
	क्रमागत led_brightness brightness;

	अगर (has_flash_op(v4l2_flash, पूर्णांकensity_to_led_brightness))
		brightness = call_flash_op(v4l2_flash,
					पूर्णांकensity_to_led_brightness,
					ctrl->val);
	अन्यथा
		brightness = __पूर्णांकensity_to_led_brightness(ctrl, ctrl->val);
	/*
	 * In हाल a LED Flash class driver provides ops क्रम custom
	 * brightness <-> पूर्णांकensity conversion, it also must have defined
	 * related v4l2 control step == 1. In such a हाल a backward conversion
	 * from led brightness to v4l2 पूर्णांकensity is required to find out the
	 * the aligned पूर्णांकensity value.
	 */
	अगर (has_flash_op(v4l2_flash, led_brightness_to_पूर्णांकensity))
		ctrl->val = call_flash_op(v4l2_flash,
					led_brightness_to_पूर्णांकensity,
					brightness);

	अगर (ctrl == ctrls[TORCH_INTENSITY]) अणु
		अगर (ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_TORCH)
			वापस;

		led_set_brightness_sync(&v4l2_flash->fled_cdev->led_cdev,
					brightness);
	पूर्ण अन्यथा अणु
		led_set_brightness_sync(v4l2_flash->iled_cdev,
					brightness);
	पूर्ण
पूर्ण

अटल पूर्णांक v4l2_flash_update_led_brightness(काष्ठा v4l2_flash *v4l2_flash,
					काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_ctrl **ctrls = v4l2_flash->ctrls;
	काष्ठा led_classdev *led_cdev;
	पूर्णांक ret;

	अगर (ctrl == ctrls[TORCH_INTENSITY]) अणु
		/*
		 * Update torch brightness only अगर in TORCH_MODE. In other modes
		 * torch led is turned off, which would spuriously inक्रमm the
		 * user space that V4L2_CID_FLASH_TORCH_INTENSITY control value
		 * has changed to 0.
		 */
		अगर (ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_TORCH)
			वापस 0;
		led_cdev = &v4l2_flash->fled_cdev->led_cdev;
	पूर्ण अन्यथा अणु
		led_cdev = v4l2_flash->iled_cdev;
	पूर्ण

	ret = led_update_brightness(led_cdev);
	अगर (ret < 0)
		वापस ret;

	अगर (has_flash_op(v4l2_flash, led_brightness_to_पूर्णांकensity))
		ctrl->val = call_flash_op(v4l2_flash,
						led_brightness_to_पूर्णांकensity,
						led_cdev->brightness);
	अन्यथा
		ctrl->val = __led_brightness_to_पूर्णांकensity(ctrl,
						led_cdev->brightness);

	वापस 0;
पूर्ण

अटल पूर्णांक v4l2_flash_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *c)
अणु
	काष्ठा v4l2_flash *v4l2_flash = v4l2_ctrl_to_v4l2_flash(c);
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	bool is_strobing;
	पूर्णांक ret;

	चयन (c->id) अणु
	हाल V4L2_CID_FLASH_TORCH_INTENSITY:
	हाल V4L2_CID_FLASH_INDICATOR_INTENSITY:
		वापस v4l2_flash_update_led_brightness(v4l2_flash, c);
	हाल V4L2_CID_FLASH_INTENSITY:
		ret = led_update_flash_brightness(fled_cdev);
		अगर (ret < 0)
			वापस ret;
		/*
		 * No conversion is needed as LED Flash class also uses
		 * microamperes क्रम flash पूर्णांकensity units.
		 */
		c->val = fled_cdev->brightness.val;
		वापस 0;
	हाल V4L2_CID_FLASH_STROBE_STATUS:
		ret = led_get_flash_strobe(fled_cdev, &is_strobing);
		अगर (ret < 0)
			वापस ret;
		c->val = is_strobing;
		वापस 0;
	हाल V4L2_CID_FLASH_FAULT:
		/* LED faults map directly to V4L2 flash faults */
		वापस led_get_flash_fault(fled_cdev, &c->val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool __software_strobe_mode_inactive(काष्ठा v4l2_ctrl **ctrls)
अणु
	वापस ((ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_FLASH) ||
		(ctrls[STROBE_SOURCE] && (ctrls[STROBE_SOURCE]->val !=
				V4L2_FLASH_STROBE_SOURCE_SOFTWARE)));
पूर्ण

अटल पूर्णांक v4l2_flash_s_ctrl(काष्ठा v4l2_ctrl *c)
अणु
	काष्ठा v4l2_flash *v4l2_flash = v4l2_ctrl_to_v4l2_flash(c);
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा led_classdev *led_cdev = fled_cdev ? &fled_cdev->led_cdev : शून्य;
	काष्ठा v4l2_ctrl **ctrls = v4l2_flash->ctrls;
	bool बाह्यal_strobe;
	पूर्णांक ret = 0;

	चयन (c->id) अणु
	हाल V4L2_CID_FLASH_LED_MODE:
		चयन (c->val) अणु
		हाल V4L2_FLASH_LED_MODE_NONE:
			led_set_brightness_sync(led_cdev, LED_OFF);
			वापस led_set_flash_strobe(fled_cdev, false);
		हाल V4L2_FLASH_LED_MODE_FLASH:
			/* Turn the torch LED off */
			led_set_brightness_sync(led_cdev, LED_OFF);
			अगर (ctrls[STROBE_SOURCE]) अणु
				बाह्यal_strobe = (ctrls[STROBE_SOURCE]->val ==
					V4L2_FLASH_STROBE_SOURCE_EXTERNAL);

				ret = call_flash_op(v4l2_flash,
						बाह्यal_strobe_set,
						बाह्यal_strobe);
			पूर्ण
			वापस ret;
		हाल V4L2_FLASH_LED_MODE_TORCH:
			अगर (ctrls[STROBE_SOURCE]) अणु
				ret = call_flash_op(v4l2_flash,
						बाह्यal_strobe_set,
						false);
				अगर (ret < 0)
					वापस ret;
			पूर्ण
			/* Stop flash strobing */
			ret = led_set_flash_strobe(fled_cdev, false);
			अगर (ret < 0)
				वापस ret;

			v4l2_flash_set_led_brightness(v4l2_flash,
							ctrls[TORCH_INTENSITY]);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_FLASH_STROBE_SOURCE:
		बाह्यal_strobe = (c->val == V4L2_FLASH_STROBE_SOURCE_EXTERNAL);
		/*
		 * For some hardware arrangements setting strobe source may
		 * affect torch mode. Thereक्रमe, अगर not in the flash mode,
		 * cache only this setting. It will be applied upon चयनing
		 * to flash mode.
		 */
		अगर (ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_FLASH)
			वापस 0;

		वापस call_flash_op(v4l2_flash, बाह्यal_strobe_set,
					बाह्यal_strobe);
	हाल V4L2_CID_FLASH_STROBE:
		अगर (__software_strobe_mode_inactive(ctrls))
			वापस -EBUSY;
		वापस led_set_flash_strobe(fled_cdev, true);
	हाल V4L2_CID_FLASH_STROBE_STOP:
		अगर (__software_strobe_mode_inactive(ctrls))
			वापस -EBUSY;
		वापस led_set_flash_strobe(fled_cdev, false);
	हाल V4L2_CID_FLASH_TIMEOUT:
		/*
		 * No conversion is needed as LED Flash class also uses
		 * microseconds क्रम flash समयout units.
		 */
		वापस led_set_flash_समयout(fled_cdev, c->val);
	हाल V4L2_CID_FLASH_INTENSITY:
		/*
		 * No conversion is needed as LED Flash class also uses
		 * microamperes क्रम flash पूर्णांकensity units.
		 */
		वापस led_set_flash_brightness(fled_cdev, c->val);
	हाल V4L2_CID_FLASH_TORCH_INTENSITY:
	हाल V4L2_CID_FLASH_INDICATOR_INTENSITY:
		v4l2_flash_set_led_brightness(v4l2_flash, c);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops v4l2_flash_ctrl_ops = अणु
	.g_अस्थिर_ctrl = v4l2_flash_g_अस्थिर_ctrl,
	.s_ctrl = v4l2_flash_s_ctrl,
पूर्ण;

अटल व्योम __lfs_to_v4l2_ctrl_config(काष्ठा led_flash_setting *s,
				काष्ठा v4l2_ctrl_config *c)
अणु
	c->min = s->min;
	c->max = s->max;
	c->step = s->step;
	c->def = s->val;
पूर्ण

अटल व्योम __fill_ctrl_init_data(काष्ठा v4l2_flash *v4l2_flash,
			  काष्ठा v4l2_flash_config *flash_cfg,
			  काष्ठा v4l2_flash_ctrl_data *ctrl_init_data)
अणु
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा led_classdev *led_cdev = fled_cdev ? &fled_cdev->led_cdev : शून्य;
	काष्ठा v4l2_ctrl_config *ctrl_cfg;
	u32 mask;

	/* Init INDICATOR_INTENSITY ctrl data */
	अगर (v4l2_flash->iled_cdev) अणु
		ctrl_init_data[INDICATOR_INTENSITY].cid =
					V4L2_CID_FLASH_INDICATOR_INTENSITY;
		ctrl_cfg = &ctrl_init_data[INDICATOR_INTENSITY].config;
		__lfs_to_v4l2_ctrl_config(&flash_cfg->पूर्णांकensity,
					  ctrl_cfg);
		ctrl_cfg->id = V4L2_CID_FLASH_INDICATOR_INTENSITY;
		ctrl_cfg->min = 0;
		ctrl_cfg->flags = V4L2_CTRL_FLAG_VOLATILE |
				  V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
	पूर्ण

	अगर (!led_cdev || WARN_ON(!(led_cdev->flags & LED_DEV_CAP_FLASH)))
		वापस;

	/* Init FLASH_FAULT ctrl data */
	अगर (flash_cfg->flash_faults) अणु
		ctrl_init_data[FLASH_FAULT].cid = V4L2_CID_FLASH_FAULT;
		ctrl_cfg = &ctrl_init_data[FLASH_FAULT].config;
		ctrl_cfg->id = V4L2_CID_FLASH_FAULT;
		ctrl_cfg->max = flash_cfg->flash_faults;
		ctrl_cfg->flags = V4L2_CTRL_FLAG_VOLATILE |
				  V4L2_CTRL_FLAG_READ_ONLY;
	पूर्ण

	/* Init FLASH_LED_MODE ctrl data */
	mask = 1 << V4L2_FLASH_LED_MODE_NONE |
	       1 << V4L2_FLASH_LED_MODE_TORCH;
	अगर (led_cdev->flags & LED_DEV_CAP_FLASH)
		mask |= 1 << V4L2_FLASH_LED_MODE_FLASH;

	ctrl_init_data[LED_MODE].cid = V4L2_CID_FLASH_LED_MODE;
	ctrl_cfg = &ctrl_init_data[LED_MODE].config;
	ctrl_cfg->id = V4L2_CID_FLASH_LED_MODE;
	ctrl_cfg->max = V4L2_FLASH_LED_MODE_TORCH;
	ctrl_cfg->menu_skip_mask = ~mask;
	ctrl_cfg->def = V4L2_FLASH_LED_MODE_NONE;
	ctrl_cfg->flags = 0;

	/* Init TORCH_INTENSITY ctrl data */
	ctrl_init_data[TORCH_INTENSITY].cid = V4L2_CID_FLASH_TORCH_INTENSITY;
	ctrl_cfg = &ctrl_init_data[TORCH_INTENSITY].config;
	__lfs_to_v4l2_ctrl_config(&flash_cfg->पूर्णांकensity, ctrl_cfg);
	ctrl_cfg->id = V4L2_CID_FLASH_TORCH_INTENSITY;
	ctrl_cfg->flags = V4L2_CTRL_FLAG_VOLATILE |
			  V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;

	/* Init FLASH_STROBE ctrl data */
	ctrl_init_data[FLASH_STROBE].cid = V4L2_CID_FLASH_STROBE;
	ctrl_cfg = &ctrl_init_data[FLASH_STROBE].config;
	ctrl_cfg->id = V4L2_CID_FLASH_STROBE;

	/* Init STROBE_STOP ctrl data */
	ctrl_init_data[STROBE_STOP].cid = V4L2_CID_FLASH_STROBE_STOP;
	ctrl_cfg = &ctrl_init_data[STROBE_STOP].config;
	ctrl_cfg->id = V4L2_CID_FLASH_STROBE_STOP;

	/* Init FLASH_STROBE_SOURCE ctrl data */
	अगर (flash_cfg->has_बाह्यal_strobe) अणु
		mask = (1 << V4L2_FLASH_STROBE_SOURCE_SOFTWARE) |
		       (1 << V4L2_FLASH_STROBE_SOURCE_EXTERNAL);
		ctrl_init_data[STROBE_SOURCE].cid =
					V4L2_CID_FLASH_STROBE_SOURCE;
		ctrl_cfg = &ctrl_init_data[STROBE_SOURCE].config;
		ctrl_cfg->id = V4L2_CID_FLASH_STROBE_SOURCE;
		ctrl_cfg->max = V4L2_FLASH_STROBE_SOURCE_EXTERNAL;
		ctrl_cfg->menu_skip_mask = ~mask;
		ctrl_cfg->def = V4L2_FLASH_STROBE_SOURCE_SOFTWARE;
	पूर्ण

	/* Init STROBE_STATUS ctrl data */
	अगर (has_flash_op(fled_cdev, strobe_get)) अणु
		ctrl_init_data[STROBE_STATUS].cid =
					V4L2_CID_FLASH_STROBE_STATUS;
		ctrl_cfg = &ctrl_init_data[STROBE_STATUS].config;
		ctrl_cfg->id = V4L2_CID_FLASH_STROBE_STATUS;
		ctrl_cfg->flags = V4L2_CTRL_FLAG_VOLATILE |
				  V4L2_CTRL_FLAG_READ_ONLY;
	पूर्ण

	/* Init FLASH_TIMEOUT ctrl data */
	अगर (has_flash_op(fled_cdev, समयout_set)) अणु
		ctrl_init_data[FLASH_TIMEOUT].cid = V4L2_CID_FLASH_TIMEOUT;
		ctrl_cfg = &ctrl_init_data[FLASH_TIMEOUT].config;
		__lfs_to_v4l2_ctrl_config(&fled_cdev->समयout, ctrl_cfg);
		ctrl_cfg->id = V4L2_CID_FLASH_TIMEOUT;
	पूर्ण

	/* Init FLASH_INTENSITY ctrl data */
	अगर (has_flash_op(fled_cdev, flash_brightness_set)) अणु
		ctrl_init_data[FLASH_INTENSITY].cid = V4L2_CID_FLASH_INTENSITY;
		ctrl_cfg = &ctrl_init_data[FLASH_INTENSITY].config;
		__lfs_to_v4l2_ctrl_config(&fled_cdev->brightness, ctrl_cfg);
		ctrl_cfg->id = V4L2_CID_FLASH_INTENSITY;
		ctrl_cfg->flags = V4L2_CTRL_FLAG_VOLATILE |
				  V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
	पूर्ण
पूर्ण

अटल पूर्णांक v4l2_flash_init_controls(काष्ठा v4l2_flash *v4l2_flash,
				काष्ठा v4l2_flash_config *flash_cfg)

अणु
	काष्ठा v4l2_flash_ctrl_data *ctrl_init_data;
	काष्ठा v4l2_ctrl *ctrl;
	काष्ठा v4l2_ctrl_config *ctrl_cfg;
	पूर्णांक i, ret, num_ctrls = 0;

	v4l2_flash->ctrls = devm_kसुस्मृति(v4l2_flash->sd.dev,
					STROBE_SOURCE + 1,
					माप(*v4l2_flash->ctrls),
					GFP_KERNEL);
	अगर (!v4l2_flash->ctrls)
		वापस -ENOMEM;

	/* allocate memory dynamically so as not to exceed stack frame size */
	ctrl_init_data = kसुस्मृति(NUM_FLASH_CTRLS, माप(*ctrl_init_data),
					GFP_KERNEL);
	अगर (!ctrl_init_data)
		वापस -ENOMEM;

	__fill_ctrl_init_data(v4l2_flash, flash_cfg, ctrl_init_data);

	क्रम (i = 0; i < NUM_FLASH_CTRLS; ++i)
		अगर (ctrl_init_data[i].cid)
			++num_ctrls;

	v4l2_ctrl_handler_init(&v4l2_flash->hdl, num_ctrls);

	क्रम (i = 0; i < NUM_FLASH_CTRLS; ++i) अणु
		ctrl_cfg = &ctrl_init_data[i].config;
		अगर (!ctrl_init_data[i].cid)
			जारी;

		अगर (ctrl_cfg->id == V4L2_CID_FLASH_LED_MODE ||
		    ctrl_cfg->id == V4L2_CID_FLASH_STROBE_SOURCE)
			ctrl = v4l2_ctrl_new_std_menu(&v4l2_flash->hdl,
						&v4l2_flash_ctrl_ops,
						ctrl_cfg->id,
						ctrl_cfg->max,
						ctrl_cfg->menu_skip_mask,
						ctrl_cfg->def);
		अन्यथा
			ctrl = v4l2_ctrl_new_std(&v4l2_flash->hdl,
						&v4l2_flash_ctrl_ops,
						ctrl_cfg->id,
						ctrl_cfg->min,
						ctrl_cfg->max,
						ctrl_cfg->step,
						ctrl_cfg->def);

		अगर (ctrl)
			ctrl->flags |= ctrl_cfg->flags;

		अगर (i <= STROBE_SOURCE)
			v4l2_flash->ctrls[i] = ctrl;
	पूर्ण

	kमुक्त(ctrl_init_data);

	अगर (v4l2_flash->hdl.error) अणु
		ret = v4l2_flash->hdl.error;
		जाओ error_मुक्त_handler;
	पूर्ण

	v4l2_ctrl_handler_setup(&v4l2_flash->hdl);

	v4l2_flash->sd.ctrl_handler = &v4l2_flash->hdl;

	वापस 0;

error_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(&v4l2_flash->hdl);
	वापस ret;
पूर्ण

अटल पूर्णांक __sync_device_with_v4l2_controls(काष्ठा v4l2_flash *v4l2_flash)
अणु
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा v4l2_ctrl **ctrls = v4l2_flash->ctrls;
	पूर्णांक ret = 0;

	अगर (ctrls[TORCH_INTENSITY])
		v4l2_flash_set_led_brightness(v4l2_flash,
					      ctrls[TORCH_INTENSITY]);

	अगर (ctrls[INDICATOR_INTENSITY])
		v4l2_flash_set_led_brightness(v4l2_flash,
						ctrls[INDICATOR_INTENSITY]);

	अगर (ctrls[FLASH_TIMEOUT]) अणु
		ret = led_set_flash_समयout(fled_cdev,
					ctrls[FLASH_TIMEOUT]->val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (ctrls[FLASH_INTENSITY]) अणु
		ret = led_set_flash_brightness(fled_cdev,
					ctrls[FLASH_INTENSITY]->val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * For some hardware arrangements setting strobe source may affect
	 * torch mode. Synchronize strobe source setting only अगर not in torch
	 * mode. For torch mode हाल it will get synchronized upon चयनing
	 * to flash mode.
	 */
	अगर (ctrls[STROBE_SOURCE] &&
	    ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_TORCH)
		ret = call_flash_op(v4l2_flash, बाह्यal_strobe_set,
					ctrls[STROBE_SOURCE]->val);

	वापस ret;
पूर्ण

/*
 * V4L2 subdev पूर्णांकernal operations
 */

अटल पूर्णांक v4l2_flash_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_flash *v4l2_flash = v4l2_subdev_to_v4l2_flash(sd);
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा led_classdev *led_cdev = fled_cdev ? &fled_cdev->led_cdev : शून्य;
	काष्ठा led_classdev *led_cdev_ind = v4l2_flash->iled_cdev;
	पूर्णांक ret = 0;

	अगर (!v4l2_fh_is_singular(&fh->vfh))
		वापस 0;

	अगर (led_cdev) अणु
		mutex_lock(&led_cdev->led_access);

		led_sysfs_disable(led_cdev);
		led_trigger_हटाओ(led_cdev);

		mutex_unlock(&led_cdev->led_access);
	पूर्ण

	अगर (led_cdev_ind) अणु
		mutex_lock(&led_cdev_ind->led_access);

		led_sysfs_disable(led_cdev_ind);
		led_trigger_हटाओ(led_cdev_ind);

		mutex_unlock(&led_cdev_ind->led_access);
	पूर्ण

	ret = __sync_device_with_v4l2_controls(v4l2_flash);
	अगर (ret < 0)
		जाओ out_sync_device;

	वापस 0;
out_sync_device:
	अगर (led_cdev) अणु
		mutex_lock(&led_cdev->led_access);
		led_sysfs_enable(led_cdev);
		mutex_unlock(&led_cdev->led_access);
	पूर्ण

	अगर (led_cdev_ind) अणु
		mutex_lock(&led_cdev_ind->led_access);
		led_sysfs_enable(led_cdev_ind);
		mutex_unlock(&led_cdev_ind->led_access);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक v4l2_flash_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_flash *v4l2_flash = v4l2_subdev_to_v4l2_flash(sd);
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा led_classdev *led_cdev = fled_cdev ? &fled_cdev->led_cdev : शून्य;
	काष्ठा led_classdev *led_cdev_ind = v4l2_flash->iled_cdev;
	पूर्णांक ret = 0;

	अगर (!v4l2_fh_is_singular(&fh->vfh))
		वापस 0;

	अगर (led_cdev) अणु
		mutex_lock(&led_cdev->led_access);

		अगर (v4l2_flash->ctrls[STROBE_SOURCE])
			ret = v4l2_ctrl_s_ctrl(
				v4l2_flash->ctrls[STROBE_SOURCE],
				V4L2_FLASH_STROBE_SOURCE_SOFTWARE);
		led_sysfs_enable(led_cdev);

		mutex_unlock(&led_cdev->led_access);
	पूर्ण

	अगर (led_cdev_ind) अणु
		mutex_lock(&led_cdev_ind->led_access);
		led_sysfs_enable(led_cdev_ind);
		mutex_unlock(&led_cdev_ind->led_access);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops v4l2_flash_subdev_पूर्णांकernal_ops = अणु
	.खोलो = v4l2_flash_खोलो,
	.बंद = v4l2_flash_बंद,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops v4l2_flash_subdev_ops;

अटल काष्ठा v4l2_flash *__v4l2_flash_init(
	काष्ठा device *dev, काष्ठा fwnode_handle *fwn,
	काष्ठा led_classdev_flash *fled_cdev, काष्ठा led_classdev *iled_cdev,
	स्थिर काष्ठा v4l2_flash_ops *ops, काष्ठा v4l2_flash_config *config)
अणु
	काष्ठा v4l2_flash *v4l2_flash;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	अगर (!config)
		वापस ERR_PTR(-EINVAL);

	v4l2_flash = devm_kzalloc(dev, माप(*v4l2_flash), GFP_KERNEL);
	अगर (!v4l2_flash)
		वापस ERR_PTR(-ENOMEM);

	sd = &v4l2_flash->sd;
	v4l2_flash->fled_cdev = fled_cdev;
	v4l2_flash->iled_cdev = iled_cdev;
	v4l2_flash->ops = ops;
	sd->dev = dev;
	sd->fwnode = fwn ? fwn : dev_fwnode(dev);
	v4l2_subdev_init(sd, &v4l2_flash_subdev_ops);
	sd->पूर्णांकernal_ops = &v4l2_flash_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(sd->name, config->dev_name, माप(sd->name));

	ret = media_entity_pads_init(&sd->entity, 0, शून्य);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	sd->entity.function = MEDIA_ENT_F_FLASH;

	ret = v4l2_flash_init_controls(v4l2_flash, config);
	अगर (ret < 0)
		जाओ err_init_controls;

	fwnode_handle_get(sd->fwnode);

	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret < 0)
		जाओ err_async_रेजिस्टर_sd;

	वापस v4l2_flash;

err_async_रेजिस्टर_sd:
	fwnode_handle_put(sd->fwnode);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
err_init_controls:
	media_entity_cleanup(&sd->entity);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा v4l2_flash *v4l2_flash_init(
	काष्ठा device *dev, काष्ठा fwnode_handle *fwn,
	काष्ठा led_classdev_flash *fled_cdev,
	स्थिर काष्ठा v4l2_flash_ops *ops,
	काष्ठा v4l2_flash_config *config)
अणु
	वापस __v4l2_flash_init(dev, fwn, fled_cdev, शून्य, ops, config);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_flash_init);

काष्ठा v4l2_flash *v4l2_flash_indicator_init(
	काष्ठा device *dev, काष्ठा fwnode_handle *fwn,
	काष्ठा led_classdev *iled_cdev,
	काष्ठा v4l2_flash_config *config)
अणु
	वापस __v4l2_flash_init(dev, fwn, शून्य, iled_cdev, शून्य, config);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_flash_indicator_init);

व्योम v4l2_flash_release(काष्ठा v4l2_flash *v4l2_flash)
अणु
	काष्ठा v4l2_subdev *sd;

	अगर (IS_ERR_OR_शून्य(v4l2_flash))
		वापस;

	sd = &v4l2_flash->sd;

	v4l2_async_unरेजिस्टर_subdev(sd);

	fwnode_handle_put(sd->fwnode);

	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	media_entity_cleanup(&sd->entity);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_flash_release);

MODULE_AUTHOR("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODULE_DESCRIPTION("V4L2 Flash sub-device helpers");
MODULE_LICENSE("GPL v2");
