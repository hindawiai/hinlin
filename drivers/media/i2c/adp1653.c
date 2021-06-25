<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/adp1653.c
 *
 * Copyright (C) 2008--2011 Nokia Corporation
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 *
 * Contributors:
 *	Sakari Ailus <sakari.ailus@iki.fi>
 *	Tuukka Toivonen <tuukkat76@gmail.com>
 *	Pavel Machek <pavel@ucw.cz>
 *
 * TODO:
 * - fault पूर्णांकerrupt handling
 * - hardware strobe
 * - घातer करोesn't need to be ON अगर all lights are off
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <media/i2c/adp1653.h>
#समावेश <media/v4l2-device.h>

#घोषणा TIMEOUT_MAX		820000
#घोषणा TIMEOUT_STEP		54600
#घोषणा TIMEOUT_MIN		(TIMEOUT_MAX - ADP1653_REG_CONFIG_TMR_SET_MAX \
				 * TIMEOUT_STEP)
#घोषणा TIMEOUT_US_TO_CODE(t)	((TIMEOUT_MAX + (TIMEOUT_STEP / 2) - (t)) \
				 / TIMEOUT_STEP)
#घोषणा TIMEOUT_CODE_TO_US(c)	(TIMEOUT_MAX - (c) * TIMEOUT_STEP)

/* Write values पूर्णांकo ADP1653 रेजिस्टरs. */
अटल पूर्णांक adp1653_update_hw(काष्ठा adp1653_flash *flash)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->subdev);
	u8 out_sel;
	u8 config = 0;
	पूर्णांक rval;

	out_sel = ADP1653_INDICATOR_INTENSITY_uA_TO_REG(
		flash->indicator_पूर्णांकensity->val)
		<< ADP1653_REG_OUT_SEL_ILED_SHIFT;

	चयन (flash->led_mode->val) अणु
	हाल V4L2_FLASH_LED_MODE_NONE:
		अवरोध;
	हाल V4L2_FLASH_LED_MODE_FLASH:
		/* Flash mode, light on with strobe, duration from समयr */
		config = ADP1653_REG_CONFIG_TMR_CFG;
		config |= TIMEOUT_US_TO_CODE(flash->flash_समयout->val)
			  << ADP1653_REG_CONFIG_TMR_SET_SHIFT;
		अवरोध;
	हाल V4L2_FLASH_LED_MODE_TORCH:
		/* Torch mode, light immediately on, duration indefinite */
		out_sel |= ADP1653_FLASH_INTENSITY_mA_TO_REG(
			flash->torch_पूर्णांकensity->val)
			<< ADP1653_REG_OUT_SEL_HPLED_SHIFT;
		अवरोध;
	पूर्ण

	rval = i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_OUT_SEL, out_sel);
	अगर (rval < 0)
		वापस rval;

	rval = i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_CONFIG, config);
	अगर (rval < 0)
		वापस rval;

	वापस 0;
पूर्ण

अटल पूर्णांक adp1653_get_fault(काष्ठा adp1653_flash *flash)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->subdev);
	पूर्णांक fault;
	पूर्णांक rval;

	fault = i2c_smbus_पढ़ो_byte_data(client, ADP1653_REG_FAULT);
	अगर (fault < 0)
		वापस fault;

	flash->fault |= fault;

	अगर (!flash->fault)
		वापस 0;

	/* Clear faults. */
	rval = i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_OUT_SEL, 0);
	अगर (rval < 0)
		वापस rval;

	flash->led_mode->val = V4L2_FLASH_LED_MODE_NONE;

	rval = adp1653_update_hw(flash);
	अगर (rval)
		वापस rval;

	वापस flash->fault;
पूर्ण

अटल पूर्णांक adp1653_strobe(काष्ठा adp1653_flash *flash, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->subdev);
	u8 out_sel = ADP1653_INDICATOR_INTENSITY_uA_TO_REG(
		flash->indicator_पूर्णांकensity->val)
		<< ADP1653_REG_OUT_SEL_ILED_SHIFT;
	पूर्णांक rval;

	अगर (flash->led_mode->val != V4L2_FLASH_LED_MODE_FLASH)
		वापस -EBUSY;

	अगर (!enable)
		वापस i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_OUT_SEL,
						 out_sel);

	out_sel |= ADP1653_FLASH_INTENSITY_mA_TO_REG(
		flash->flash_पूर्णांकensity->val)
		<< ADP1653_REG_OUT_SEL_HPLED_SHIFT;
	rval = i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_OUT_SEL, out_sel);
	अगर (rval)
		वापस rval;

	/* Software strobe using i2c */
	rval = i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_SW_STROBE,
		ADP1653_REG_SW_STROBE_SW_STROBE);
	अगर (rval)
		वापस rval;
	वापस i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_SW_STROBE, 0);
पूर्ण

/* --------------------------------------------------------------------------
 * V4L2 controls
 */

अटल पूर्णांक adp1653_get_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा adp1653_flash *flash =
		container_of(ctrl->handler, काष्ठा adp1653_flash, ctrls);
	पूर्णांक rval;

	rval = adp1653_get_fault(flash);
	अगर (rval)
		वापस rval;

	ctrl->cur.val = 0;

	अगर (flash->fault & ADP1653_REG_FAULT_FLT_SCP)
		ctrl->cur.val |= V4L2_FLASH_FAULT_SHORT_CIRCUIT;
	अगर (flash->fault & ADP1653_REG_FAULT_FLT_OT)
		ctrl->cur.val |= V4L2_FLASH_FAULT_OVER_TEMPERATURE;
	अगर (flash->fault & ADP1653_REG_FAULT_FLT_TMR)
		ctrl->cur.val |= V4L2_FLASH_FAULT_TIMEOUT;
	अगर (flash->fault & ADP1653_REG_FAULT_FLT_OV)
		ctrl->cur.val |= V4L2_FLASH_FAULT_OVER_VOLTAGE;

	flash->fault = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक adp1653_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा adp1653_flash *flash =
		container_of(ctrl->handler, काष्ठा adp1653_flash, ctrls);
	पूर्णांक rval;

	rval = adp1653_get_fault(flash);
	अगर (rval)
		वापस rval;
	अगर ((rval & (ADP1653_REG_FAULT_FLT_SCP |
		     ADP1653_REG_FAULT_FLT_OT |
		     ADP1653_REG_FAULT_FLT_OV)) &&
	    (ctrl->id == V4L2_CID_FLASH_STROBE ||
	     ctrl->id == V4L2_CID_FLASH_TORCH_INTENSITY ||
	     ctrl->id == V4L2_CID_FLASH_LED_MODE))
		वापस -EBUSY;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FLASH_STROBE:
		वापस adp1653_strobe(flash, 1);
	हाल V4L2_CID_FLASH_STROBE_STOP:
		वापस adp1653_strobe(flash, 0);
	पूर्ण

	वापस adp1653_update_hw(flash);
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops adp1653_ctrl_ops = अणु
	.g_अस्थिर_ctrl = adp1653_get_ctrl,
	.s_ctrl = adp1653_set_ctrl,
पूर्ण;

अटल पूर्णांक adp1653_init_controls(काष्ठा adp1653_flash *flash)
अणु
	काष्ठा v4l2_ctrl *fault;

	v4l2_ctrl_handler_init(&flash->ctrls, 9);

	flash->led_mode =
		v4l2_ctrl_new_std_menu(&flash->ctrls, &adp1653_ctrl_ops,
				       V4L2_CID_FLASH_LED_MODE,
				       V4L2_FLASH_LED_MODE_TORCH, ~0x7, 0);
	v4l2_ctrl_new_std_menu(&flash->ctrls, &adp1653_ctrl_ops,
			       V4L2_CID_FLASH_STROBE_SOURCE,
			       V4L2_FLASH_STROBE_SOURCE_SOFTWARE, ~0x1, 0);
	v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
			  V4L2_CID_FLASH_STROBE, 0, 0, 0, 0);
	v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
			  V4L2_CID_FLASH_STROBE_STOP, 0, 0, 0, 0);
	flash->flash_समयout =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_TIMEOUT, TIMEOUT_MIN,
				  flash->platक्रमm_data->max_flash_समयout,
				  TIMEOUT_STEP,
				  flash->platक्रमm_data->max_flash_समयout);
	flash->flash_पूर्णांकensity =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_INTENSITY,
				  ADP1653_FLASH_INTENSITY_MIN,
				  flash->platक्रमm_data->max_flash_पूर्णांकensity,
				  1, flash->platक्रमm_data->max_flash_पूर्णांकensity);
	flash->torch_पूर्णांकensity =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_TORCH_INTENSITY,
				  ADP1653_TORCH_INTENSITY_MIN,
				  flash->platक्रमm_data->max_torch_पूर्णांकensity,
				  ADP1653_FLASH_INTENSITY_STEP,
				  flash->platक्रमm_data->max_torch_पूर्णांकensity);
	flash->indicator_पूर्णांकensity =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_INDICATOR_INTENSITY,
				  ADP1653_INDICATOR_INTENSITY_MIN,
				  flash->platक्रमm_data->max_indicator_पूर्णांकensity,
				  ADP1653_INDICATOR_INTENSITY_STEP,
				  ADP1653_INDICATOR_INTENSITY_MIN);
	fault = v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_FAULT, 0,
				  V4L2_FLASH_FAULT_OVER_VOLTAGE
				  | V4L2_FLASH_FAULT_OVER_TEMPERATURE
				  | V4L2_FLASH_FAULT_SHORT_CIRCUIT, 0, 0);

	अगर (flash->ctrls.error)
		वापस flash->ctrls.error;

	fault->flags |= V4L2_CTRL_FLAG_VOLATILE;

	flash->subdev.ctrl_handler = &flash->ctrls;
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
 * V4L2 subdev operations
 */

अटल पूर्णांक
adp1653_init_device(काष्ठा adp1653_flash *flash)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->subdev);
	पूर्णांक rval;

	/* Clear FAULT रेजिस्टर by writing zero to OUT_SEL */
	rval = i2c_smbus_ग_लिखो_byte_data(client, ADP1653_REG_OUT_SEL, 0);
	अगर (rval < 0) अणु
		dev_err(&client->dev, "failed writing fault register\n");
		वापस -EIO;
	पूर्ण

	mutex_lock(flash->ctrls.lock);
	/* Reset faults beक्रमe पढ़ोing new ones. */
	flash->fault = 0;
	rval = adp1653_get_fault(flash);
	mutex_unlock(flash->ctrls.lock);
	अगर (rval > 0) अणु
		dev_err(&client->dev, "faults detected: 0x%1.1x\n", rval);
		वापस -EIO;
	पूर्ण

	mutex_lock(flash->ctrls.lock);
	rval = adp1653_update_hw(flash);
	mutex_unlock(flash->ctrls.lock);
	अगर (rval) अणु
		dev_err(&client->dev,
			"adp1653_update_hw failed at %s\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
__adp1653_set_घातer(काष्ठा adp1653_flash *flash, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (flash->platक्रमm_data->घातer) अणु
		ret = flash->platक्रमm_data->घातer(&flash->subdev, on);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		gpiod_set_value(flash->platक्रमm_data->enable_gpio, on);
		अगर (on)
			/* Some delay is apparently required. */
			udelay(20);
	पूर्ण

	अगर (!on)
		वापस 0;

	ret = adp1653_init_device(flash);
	अगर (ret >= 0)
		वापस ret;

	अगर (flash->platक्रमm_data->घातer)
		flash->platक्रमm_data->घातer(&flash->subdev, 0);
	अन्यथा
		gpiod_set_value(flash->platक्रमm_data->enable_gpio, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक
adp1653_set_घातer(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा adp1653_flash *flash = to_adp1653_flash(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&flash->घातer_lock);

	/* If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (flash->घातer_count == !on) अणु
		ret = __adp1653_set_घातer(flash, !!on);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	/* Update the घातer count. */
	flash->घातer_count += on ? 1 : -1;
	WARN_ON(flash->घातer_count < 0);

करोne:
	mutex_unlock(&flash->घातer_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adp1653_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस adp1653_set_घातer(sd, 1);
पूर्ण

अटल पूर्णांक adp1653_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस adp1653_set_घातer(sd, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops adp1653_core_ops = अणु
	.s_घातer = adp1653_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops adp1653_ops = अणु
	.core = &adp1653_core_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops adp1653_पूर्णांकernal_ops = अणु
	.खोलो = adp1653_खोलो,
	.बंद = adp1653_बंद,
पूर्ण;

/* --------------------------------------------------------------------------
 * I2C driver
 */
#अगर_घोषित CONFIG_PM

अटल पूर्णांक adp1653_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा adp1653_flash *flash = to_adp1653_flash(subdev);

	अगर (!flash->घातer_count)
		वापस 0;

	वापस __adp1653_set_घातer(flash, 0);
पूर्ण

अटल पूर्णांक adp1653_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा adp1653_flash *flash = to_adp1653_flash(subdev);

	अगर (!flash->घातer_count)
		वापस 0;

	वापस __adp1653_set_घातer(flash, 1);
पूर्ण

#अन्यथा

#घोषणा adp1653_suspend	शून्य
#घोषणा adp1653_resume	शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक adp1653_of_init(काष्ठा i2c_client *client,
			   काष्ठा adp1653_flash *flash,
			   काष्ठा device_node *node)
अणु
	काष्ठा adp1653_platक्रमm_data *pd;
	काष्ठा device_node *child;

	pd = devm_kzalloc(&client->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;
	flash->platक्रमm_data = pd;

	child = of_get_child_by_name(node, "flash");
	अगर (!child)
		वापस -EINVAL;

	अगर (of_property_पढ़ो_u32(child, "flash-timeout-us",
				 &pd->max_flash_समयout))
		जाओ err;

	अगर (of_property_पढ़ो_u32(child, "flash-max-microamp",
				 &pd->max_flash_पूर्णांकensity))
		जाओ err;

	pd->max_flash_पूर्णांकensity /= 1000;

	अगर (of_property_पढ़ो_u32(child, "led-max-microamp",
				 &pd->max_torch_पूर्णांकensity))
		जाओ err;

	pd->max_torch_पूर्णांकensity /= 1000;
	of_node_put(child);

	child = of_get_child_by_name(node, "indicator");
	अगर (!child)
		वापस -EINVAL;

	अगर (of_property_पढ़ो_u32(child, "led-max-microamp",
				 &pd->max_indicator_पूर्णांकensity))
		जाओ err;

	of_node_put(child);

	pd->enable_gpio = devm_gpiod_get(&client->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(pd->enable_gpio)) अणु
		dev_err(&client->dev, "Error getting GPIO\n");
		वापस PTR_ERR(pd->enable_gpio);
	पूर्ण

	वापस 0;
err:
	dev_err(&client->dev, "Required property not found\n");
	of_node_put(child);
	वापस -EINVAL;
पूर्ण


अटल पूर्णांक adp1653_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *devid)
अणु
	काष्ठा adp1653_flash *flash;
	पूर्णांक ret;

	flash = devm_kzalloc(&client->dev, माप(*flash), GFP_KERNEL);
	अगर (flash == शून्य)
		वापस -ENOMEM;

	अगर (client->dev.of_node) अणु
		ret = adp1653_of_init(client, flash, client->dev.of_node);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (!client->dev.platक्रमm_data) अणु
			dev_err(&client->dev,
				"Neither DT not platform data provided\n");
			वापस -EINVAL;
		पूर्ण
		flash->platक्रमm_data = client->dev.platक्रमm_data;
	पूर्ण

	mutex_init(&flash->घातer_lock);

	v4l2_i2c_subdev_init(&flash->subdev, client, &adp1653_ops);
	flash->subdev.पूर्णांकernal_ops = &adp1653_पूर्णांकernal_ops;
	flash->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	ret = adp1653_init_controls(flash);
	अगर (ret)
		जाओ मुक्त_and_quit;

	ret = media_entity_pads_init(&flash->subdev.entity, 0, शून्य);
	अगर (ret < 0)
		जाओ मुक्त_and_quit;

	flash->subdev.entity.function = MEDIA_ENT_F_FLASH;

	वापस 0;

मुक्त_and_quit:
	dev_err(&client->dev, "adp1653: failed to register device\n");
	v4l2_ctrl_handler_मुक्त(&flash->ctrls);
	वापस ret;
पूर्ण

अटल पूर्णांक adp1653_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा adp1653_flash *flash = to_adp1653_flash(subdev);

	v4l2_device_unरेजिस्टर_subdev(&flash->subdev);
	v4l2_ctrl_handler_मुक्त(&flash->ctrls);
	media_entity_cleanup(&flash->subdev.entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adp1653_id_table[] = अणु
	अणु ADP1653_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adp1653_id_table);

अटल स्थिर काष्ठा dev_pm_ops adp1653_pm_ops = अणु
	.suspend	= adp1653_suspend,
	.resume		= adp1653_resume,
पूर्ण;

अटल काष्ठा i2c_driver adp1653_i2c_driver = अणु
	.driver		= अणु
		.name	= ADP1653_NAME,
		.pm	= &adp1653_pm_ops,
	पूर्ण,
	.probe		= adp1653_probe,
	.हटाओ		= adp1653_हटाओ,
	.id_table	= adp1653_id_table,
पूर्ण;

module_i2c_driver(adp1653_i2c_driver);

MODULE_AUTHOR("Sakari Ailus <sakari.ailus@nokia.com>");
MODULE_DESCRIPTION("Analog Devices ADP1653 LED flash driver");
MODULE_LICENSE("GPL");
