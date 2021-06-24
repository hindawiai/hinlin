<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/ad5820.c
 *
 * AD5820 DAC driver क्रम camera voice coil focus.
 *
 * Copyright (C) 2008 Nokia Corporation
 * Copyright (C) 2007 Texas Instruments
 * Copyright (C) 2016 Pavel Machek <pavel@ucw.cz>
 *
 * Contact: Tuukka Toivonen <tuukkat76@gmail.com>
 *	    Sakari Ailus <sakari.ailus@iki.fi>
 *
 * Based on af_d88.c by Texas Instruments.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

/* Register definitions */
#घोषणा AD5820_POWER_DOWN		(1 << 15)
#घोषणा AD5820_DAC_SHIFT		4
#घोषणा AD5820_RAMP_MODE_LINEAR		(0 << 3)
#घोषणा AD5820_RAMP_MODE_64_16		(1 << 3)

#घोषणा CODE_TO_RAMP_US(s)	((s) == 0 ? 0 : (1 << ((s) - 1)) * 50)
#घोषणा RAMP_US_TO_CODE(c)	fls(((c) + ((c)>>1)) / 50)

#घोषणा to_ad5820_device(sd)	container_of(sd, काष्ठा ad5820_device, subdev)

काष्ठा ad5820_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा ad5820_platक्रमm_data *platक्रमm_data;
	काष्ठा regulator *vana;

	काष्ठा v4l2_ctrl_handler ctrls;
	u32 focus_असलolute;
	u32 focus_ramp_समय;
	u32 focus_ramp_mode;

	काष्ठा gpio_desc *enable_gpio;

	काष्ठा mutex घातer_lock;
	पूर्णांक घातer_count;

	bool standby;
पूर्ण;

अटल पूर्णांक ad5820_ग_लिखो(काष्ठा ad5820_device *coil, u16 data)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&coil->subdev);
	काष्ठा i2c_msg msg;
	__be16 be_data;
	पूर्णांक r;

	अगर (!client->adapter)
		वापस -ENODEV;

	be_data = cpu_to_be16(data);
	msg.addr  = client->addr;
	msg.flags = 0;
	msg.len   = 2;
	msg.buf   = (u8 *)&be_data;

	r = i2c_transfer(client->adapter, &msg, 1);
	अगर (r < 0) अणु
		dev_err(&client->dev, "write failed, error %d\n", r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Calculate status word and ग_लिखो it to the device based on current
 * values of V4L2 controls. It is assumed that the stored V4L2 control
 * values are properly limited and rounded.
 */
अटल पूर्णांक ad5820_update_hw(काष्ठा ad5820_device *coil)
अणु
	u16 status;

	status = RAMP_US_TO_CODE(coil->focus_ramp_समय);
	status |= coil->focus_ramp_mode
		? AD5820_RAMP_MODE_64_16 : AD5820_RAMP_MODE_LINEAR;
	status |= coil->focus_असलolute << AD5820_DAC_SHIFT;

	अगर (coil->standby)
		status |= AD5820_POWER_DOWN;

	वापस ad5820_ग_लिखो(coil, status);
पूर्ण

/*
 * Power handling
 */
अटल पूर्णांक ad5820_घातer_off(काष्ठा ad5820_device *coil, bool standby)
अणु
	पूर्णांक ret = 0, ret2;

	/*
	 * Go to standby first as real घातer off my be denied by the hardware
	 * (single घातer line control क्रम both coil and sensor).
	 */
	अगर (standby) अणु
		coil->standby = true;
		ret = ad5820_update_hw(coil);
	पूर्ण

	gpiod_set_value_cansleep(coil->enable_gpio, 0);

	ret2 = regulator_disable(coil->vana);
	अगर (ret)
		वापस ret;
	वापस ret2;
पूर्ण

अटल पूर्णांक ad5820_घातer_on(काष्ठा ad5820_device *coil, bool restore)
अणु
	पूर्णांक ret;

	ret = regulator_enable(coil->vana);
	अगर (ret < 0)
		वापस ret;

	gpiod_set_value_cansleep(coil->enable_gpio, 1);

	अगर (restore) अणु
		/* Restore the hardware settings. */
		coil->standby = false;
		ret = ad5820_update_hw(coil);
		अगर (ret)
			जाओ fail;
	पूर्ण
	वापस 0;

fail:
	gpiod_set_value_cansleep(coil->enable_gpio, 0);
	coil->standby = true;
	regulator_disable(coil->vana);

	वापस ret;
पूर्ण

/*
 * V4L2 controls
 */
अटल पूर्णांक ad5820_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ad5820_device *coil =
		container_of(ctrl->handler, काष्ठा ad5820_device, ctrls);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FOCUS_ABSOLUTE:
		coil->focus_असलolute = ctrl->val;
		वापस ad5820_update_hw(coil);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ad5820_ctrl_ops = अणु
	.s_ctrl = ad5820_set_ctrl,
पूर्ण;


अटल पूर्णांक ad5820_init_controls(काष्ठा ad5820_device *coil)
अणु
	v4l2_ctrl_handler_init(&coil->ctrls, 1);

	/*
	 * V4L2_CID_FOCUS_ABSOLUTE
	 *
	 * Minimum current is 0 mA, maximum is 100 mA. Thus, 1 code is
	 * equivalent to 100/1023 = 0.0978 mA. Nevertheless, we करो not use [mA]
	 * क्रम focus position, because it is meaningless क्रम user. Meaningful
	 * would be to use focus distance or even its inverse, but since the
	 * driver करोesn't have sufficiently knowledge to करो the conversion, we
	 * will just use असलtract codes here. In any हाल, smaller value = focus
	 * position farther from camera. The शेष zero value means focus at
	 * infinity, and also least current consumption.
	 */
	v4l2_ctrl_new_std(&coil->ctrls, &ad5820_ctrl_ops,
			  V4L2_CID_FOCUS_ABSOLUTE, 0, 1023, 1, 0);

	अगर (coil->ctrls.error)
		वापस coil->ctrls.error;

	coil->focus_असलolute = 0;
	coil->focus_ramp_समय = 0;
	coil->focus_ramp_mode = 0;

	coil->subdev.ctrl_handler = &coil->ctrls;

	वापस 0;
पूर्ण

/*
 * V4L2 subdev operations
 */
अटल पूर्णांक ad5820_रेजिस्टरed(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा ad5820_device *coil = to_ad5820_device(subdev);

	वापस ad5820_init_controls(coil);
पूर्ण

अटल पूर्णांक
ad5820_set_घातer(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा ad5820_device *coil = to_ad5820_device(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&coil->घातer_lock);

	/*
	 * If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (coil->घातer_count == !on) अणु
		ret = on ? ad5820_घातer_on(coil, true) :
			ad5820_घातer_off(coil, true);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	/* Update the घातer count. */
	coil->घातer_count += on ? 1 : -1;
	WARN_ON(coil->घातer_count < 0);

करोne:
	mutex_unlock(&coil->घातer_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5820_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस ad5820_set_घातer(sd, 1);
पूर्ण

अटल पूर्णांक ad5820_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस ad5820_set_घातer(sd, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ad5820_core_ops = अणु
	.s_घातer = ad5820_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ad5820_ops = अणु
	.core = &ad5820_core_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ad5820_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = ad5820_रेजिस्टरed,
	.खोलो = ad5820_खोलो,
	.बंद = ad5820_बंद,
पूर्ण;

/*
 * I2C driver
 */
अटल पूर्णांक __maybe_unused ad5820_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा ad5820_device *coil = to_ad5820_device(subdev);

	अगर (!coil->घातer_count)
		वापस 0;

	वापस ad5820_घातer_off(coil, false);
पूर्ण

अटल पूर्णांक __maybe_unused ad5820_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा ad5820_device *coil = to_ad5820_device(subdev);

	अगर (!coil->घातer_count)
		वापस 0;

	वापस ad5820_घातer_on(coil, true);
पूर्ण

अटल पूर्णांक ad5820_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *devid)
अणु
	काष्ठा ad5820_device *coil;
	पूर्णांक ret;

	coil = devm_kzalloc(&client->dev, माप(*coil), GFP_KERNEL);
	अगर (!coil)
		वापस -ENOMEM;

	coil->vana = devm_regulator_get(&client->dev, "VANA");
	अगर (IS_ERR(coil->vana)) अणु
		ret = PTR_ERR(coil->vana);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&client->dev, "could not get regulator for vana\n");
		वापस ret;
	पूर्ण

	coil->enable_gpio = devm_gpiod_get_optional(&client->dev, "enable",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(coil->enable_gpio)) अणु
		ret = PTR_ERR(coil->enable_gpio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&client->dev, "could not get enable gpio\n");
		वापस ret;
	पूर्ण

	mutex_init(&coil->घातer_lock);

	v4l2_i2c_subdev_init(&coil->subdev, client, &ad5820_ops);
	coil->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	coil->subdev.पूर्णांकernal_ops = &ad5820_पूर्णांकernal_ops;
	coil->subdev.entity.function = MEDIA_ENT_F_LENS;
	strscpy(coil->subdev.name, "ad5820 focus", माप(coil->subdev.name));

	ret = media_entity_pads_init(&coil->subdev.entity, 0, शून्य);
	अगर (ret < 0)
		जाओ cleanup2;

	ret = v4l2_async_रेजिस्टर_subdev(&coil->subdev);
	अगर (ret < 0)
		जाओ cleanup;

	वापस ret;

cleanup2:
	mutex_destroy(&coil->घातer_lock);
cleanup:
	media_entity_cleanup(&coil->subdev.entity);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5820_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ad5820_device *coil = to_ad5820_device(subdev);

	v4l2_async_unरेजिस्टर_subdev(&coil->subdev);
	v4l2_ctrl_handler_मुक्त(&coil->ctrls);
	media_entity_cleanup(&coil->subdev.entity);
	mutex_destroy(&coil->घातer_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad5820_id_table[] = अणु
	अणु "ad5820", 0 पूर्ण,
	अणु "ad5821", 0 पूर्ण,
	अणु "ad5823", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5820_id_table);

अटल स्थिर काष्ठा of_device_id ad5820_of_table[] = अणु
	अणु .compatible = "adi,ad5820" पूर्ण,
	अणु .compatible = "adi,ad5821" पूर्ण,
	अणु .compatible = "adi,ad5823" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5820_of_table);

अटल SIMPLE_DEV_PM_OPS(ad5820_pm, ad5820_suspend, ad5820_resume);

अटल काष्ठा i2c_driver ad5820_i2c_driver = अणु
	.driver		= अणु
		.name	= "ad5820",
		.pm	= &ad5820_pm,
		.of_match_table = ad5820_of_table,
	पूर्ण,
	.probe		= ad5820_probe,
	.हटाओ		= ad5820_हटाओ,
	.id_table	= ad5820_id_table,
पूर्ण;

module_i2c_driver(ad5820_i2c_driver);

MODULE_AUTHOR("Tuukka Toivonen");
MODULE_DESCRIPTION("AD5820 camera lens driver");
MODULE_LICENSE("GPL");
