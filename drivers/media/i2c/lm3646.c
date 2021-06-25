<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/lm3646.c
 * General device driver क्रम TI lm3646, Dual FLASH LED Driver
 *
 * Copyright (C) 2014 Texas Instruments
 *
 * Contact: Daniel Jeong <gshark.jeong@gmail.com>
 *			Ldd-Mlp <ldd-mlp@list.ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/videodev2.h>
#समावेश <media/i2c/lm3646.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

/* रेजिस्टरs definitions */
#घोषणा REG_ENABLE		0x01
#घोषणा REG_TORCH_BR	0x05
#घोषणा REG_FLASH_BR	0x05
#घोषणा REG_FLASH_TOUT	0x04
#घोषणा REG_FLAG		0x08
#घोषणा REG_STROBE_SRC	0x06
#घोषणा REG_LED1_FLASH_BR 0x06
#घोषणा REG_LED1_TORCH_BR 0x07

#घोषणा MASK_ENABLE		0x03
#घोषणा MASK_TORCH_BR	0x70
#घोषणा MASK_FLASH_BR	0x0F
#घोषणा MASK_FLASH_TOUT	0x07
#घोषणा MASK_FLAG		0xFF
#घोषणा MASK_STROBE_SRC	0x80

/* Fault Mask */
#घोषणा FAULT_TIMEOUT	(1<<0)
#घोषणा FAULT_SHORT_CIRCUIT	(1<<1)
#घोषणा FAULT_UVLO		(1<<2)
#घोषणा FAULT_IVFM		(1<<3)
#घोषणा FAULT_OCP		(1<<4)
#घोषणा FAULT_OVERTEMP	(1<<5)
#घोषणा FAULT_NTC_TRIP	(1<<6)
#घोषणा FAULT_OVP		(1<<7)

क्रमागत led_mode अणु
	MODE_SHDN = 0x0,
	MODE_TORCH = 0x2,
	MODE_FLASH = 0x3,
पूर्ण;

/*
 * काष्ठा lm3646_flash
 *
 * @pdata: platक्रमm data
 * @regmap: reg. map क्रम i2c
 * @lock: muxtex क्रम serial access.
 * @led_mode: V4L2 LED mode
 * @ctrls_led: V4L2 controls
 * @subdev_led: V4L2 subdev
 * @mode_reg : mode रेजिस्टर value
 */
काष्ठा lm3646_flash अणु
	काष्ठा device *dev;
	काष्ठा lm3646_platक्रमm_data *pdata;
	काष्ठा regmap *regmap;

	काष्ठा v4l2_ctrl_handler ctrls_led;
	काष्ठा v4l2_subdev subdev_led;

	u8 mode_reg;
पूर्ण;

#घोषणा to_lm3646_flash(_ctrl)	\
	container_of(_ctrl->handler, काष्ठा lm3646_flash, ctrls_led)

/* enable mode control */
अटल पूर्णांक lm3646_mode_ctrl(काष्ठा lm3646_flash *flash,
			    क्रमागत v4l2_flash_led_mode led_mode)
अणु
	चयन (led_mode) अणु
	हाल V4L2_FLASH_LED_MODE_NONE:
		वापस regmap_ग_लिखो(flash->regmap,
				    REG_ENABLE, flash->mode_reg | MODE_SHDN);
	हाल V4L2_FLASH_LED_MODE_TORCH:
		वापस regmap_ग_लिखो(flash->regmap,
				    REG_ENABLE, flash->mode_reg | MODE_TORCH);
	हाल V4L2_FLASH_LED_MODE_FLASH:
		वापस regmap_ग_लिखो(flash->regmap,
				    REG_ENABLE, flash->mode_reg | MODE_FLASH);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* V4L2 controls  */
अटल पूर्णांक lm3646_get_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा lm3646_flash *flash = to_lm3646_flash(ctrl);
	अचिन्हित पूर्णांक reg_val;
	पूर्णांक rval;

	अगर (ctrl->id != V4L2_CID_FLASH_FAULT)
		वापस -EINVAL;

	rval = regmap_पढ़ो(flash->regmap, REG_FLAG, &reg_val);
	अगर (rval < 0)
		वापस rval;

	ctrl->val = 0;
	अगर (reg_val & FAULT_TIMEOUT)
		ctrl->val |= V4L2_FLASH_FAULT_TIMEOUT;
	अगर (reg_val & FAULT_SHORT_CIRCUIT)
		ctrl->val |= V4L2_FLASH_FAULT_SHORT_CIRCUIT;
	अगर (reg_val & FAULT_UVLO)
		ctrl->val |= V4L2_FLASH_FAULT_UNDER_VOLTAGE;
	अगर (reg_val & FAULT_IVFM)
		ctrl->val |= V4L2_FLASH_FAULT_INPUT_VOLTAGE;
	अगर (reg_val & FAULT_OCP)
		ctrl->val |= V4L2_FLASH_FAULT_OVER_CURRENT;
	अगर (reg_val & FAULT_OVERTEMP)
		ctrl->val |= V4L2_FLASH_FAULT_OVER_TEMPERATURE;
	अगर (reg_val & FAULT_NTC_TRIP)
		ctrl->val |= V4L2_FLASH_FAULT_LED_OVER_TEMPERATURE;
	अगर (reg_val & FAULT_OVP)
		ctrl->val |= V4L2_FLASH_FAULT_OVER_VOLTAGE;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3646_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा lm3646_flash *flash = to_lm3646_flash(ctrl);
	अचिन्हित पूर्णांक reg_val;
	पूर्णांक rval;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FLASH_LED_MODE:

		अगर (ctrl->val != V4L2_FLASH_LED_MODE_FLASH)
			वापस lm3646_mode_ctrl(flash, ctrl->val);
		/* चयन to SHDN mode beक्रमe flash strobe on */
		वापस lm3646_mode_ctrl(flash, V4L2_FLASH_LED_MODE_NONE);

	हाल V4L2_CID_FLASH_STROBE_SOURCE:
		वापस regmap_update_bits(flash->regmap,
					  REG_STROBE_SRC, MASK_STROBE_SRC,
					  (ctrl->val) << 7);

	हाल V4L2_CID_FLASH_STROBE:

		/* पढ़ो and check current mode of chip to start flash */
		rval = regmap_पढ़ो(flash->regmap, REG_ENABLE, &reg_val);
		अगर (rval < 0 || ((reg_val & MASK_ENABLE) != MODE_SHDN))
			वापस rval;
		/* flash on */
		वापस lm3646_mode_ctrl(flash, V4L2_FLASH_LED_MODE_FLASH);

	हाल V4L2_CID_FLASH_STROBE_STOP:

		/*
		 * flash mode will be turned स्वतःmatically
		 * from FLASH mode to SHDN mode after flash duration समयout
		 * पढ़ो and check current mode of chip to stop flash
		 */
		rval = regmap_पढ़ो(flash->regmap, REG_ENABLE, &reg_val);
		अगर (rval < 0)
			वापस rval;
		अगर ((reg_val & MASK_ENABLE) == MODE_FLASH)
			वापस lm3646_mode_ctrl(flash,
						V4L2_FLASH_LED_MODE_NONE);
		वापस rval;

	हाल V4L2_CID_FLASH_TIMEOUT:
		वापस regmap_update_bits(flash->regmap,
					  REG_FLASH_TOUT, MASK_FLASH_TOUT,
					  LM3646_FLASH_TOUT_ms_TO_REG
					  (ctrl->val));

	हाल V4L2_CID_FLASH_INTENSITY:
		वापस regmap_update_bits(flash->regmap,
					  REG_FLASH_BR, MASK_FLASH_BR,
					  LM3646_TOTAL_FLASH_BRT_uA_TO_REG
					  (ctrl->val));

	हाल V4L2_CID_FLASH_TORCH_INTENSITY:
		वापस regmap_update_bits(flash->regmap,
					  REG_TORCH_BR, MASK_TORCH_BR,
					  LM3646_TOTAL_TORCH_BRT_uA_TO_REG
					  (ctrl->val) << 4);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops lm3646_led_ctrl_ops = अणु
	.g_अस्थिर_ctrl = lm3646_get_ctrl,
	.s_ctrl = lm3646_set_ctrl,
पूर्ण;

अटल पूर्णांक lm3646_init_controls(काष्ठा lm3646_flash *flash)
अणु
	काष्ठा v4l2_ctrl *fault;
	काष्ठा v4l2_ctrl_handler *hdl = &flash->ctrls_led;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &lm3646_led_ctrl_ops;

	v4l2_ctrl_handler_init(hdl, 8);
	/* flash mode */
	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_FLASH_LED_MODE,
			       V4L2_FLASH_LED_MODE_TORCH, ~0x7,
			       V4L2_FLASH_LED_MODE_NONE);

	/* flash source */
	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_FLASH_STROBE_SOURCE,
			       0x1, ~0x3, V4L2_FLASH_STROBE_SOURCE_SOFTWARE);

	/* flash strobe */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_STROBE, 0, 0, 0, 0);
	/* flash strobe stop */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_STROBE_STOP, 0, 0, 0, 0);

	/* flash strobe समयout */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_TIMEOUT,
			  LM3646_FLASH_TOUT_MIN,
			  LM3646_FLASH_TOUT_MAX,
			  LM3646_FLASH_TOUT_STEP, flash->pdata->flash_समयout);

	/* max flash current */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_INTENSITY,
			  LM3646_TOTAL_FLASH_BRT_MIN,
			  LM3646_TOTAL_FLASH_BRT_MAX,
			  LM3646_TOTAL_FLASH_BRT_STEP,
			  LM3646_TOTAL_FLASH_BRT_MAX);

	/* max torch current */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_TORCH_INTENSITY,
			  LM3646_TOTAL_TORCH_BRT_MIN,
			  LM3646_TOTAL_TORCH_BRT_MAX,
			  LM3646_TOTAL_TORCH_BRT_STEP,
			  LM3646_TOTAL_TORCH_BRT_MAX);

	/* fault */
	fault = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_FAULT, 0,
				  V4L2_FLASH_FAULT_OVER_VOLTAGE
				  | V4L2_FLASH_FAULT_OVER_TEMPERATURE
				  | V4L2_FLASH_FAULT_SHORT_CIRCUIT
				  | V4L2_FLASH_FAULT_TIMEOUT, 0, 0);
	अगर (fault != शून्य)
		fault->flags |= V4L2_CTRL_FLAG_VOLATILE;

	अगर (hdl->error)
		वापस hdl->error;

	flash->subdev_led.ctrl_handler = hdl;
	वापस 0;
पूर्ण

/* initialize device */
अटल स्थिर काष्ठा v4l2_subdev_ops lm3646_ops = अणु
	.core = शून्य,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lm3646_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xFF,
पूर्ण;

अटल पूर्णांक lm3646_subdev_init(काष्ठा lm3646_flash *flash)
अणु
	काष्ठा i2c_client *client = to_i2c_client(flash->dev);
	पूर्णांक rval;

	v4l2_i2c_subdev_init(&flash->subdev_led, client, &lm3646_ops);
	flash->subdev_led.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(flash->subdev_led.name, LM3646_NAME,
		माप(flash->subdev_led.name));
	rval = lm3646_init_controls(flash);
	अगर (rval)
		जाओ err_out;
	rval = media_entity_pads_init(&flash->subdev_led.entity, 0, शून्य);
	अगर (rval < 0)
		जाओ err_out;
	flash->subdev_led.entity.function = MEDIA_ENT_F_FLASH;
	वापस rval;

err_out:
	v4l2_ctrl_handler_मुक्त(&flash->ctrls_led);
	वापस rval;
पूर्ण

अटल पूर्णांक lm3646_init_device(काष्ठा lm3646_flash *flash)
अणु
	अचिन्हित पूर्णांक reg_val;
	पूर्णांक rval;

	/* पढ़ो the value of mode रेजिस्टर to reduce redundant i2c accesses */
	rval = regmap_पढ़ो(flash->regmap, REG_ENABLE, &reg_val);
	अगर (rval < 0)
		वापस rval;
	flash->mode_reg = reg_val & 0xfc;

	/* output disable */
	rval = lm3646_mode_ctrl(flash, V4L2_FLASH_LED_MODE_NONE);
	अगर (rval < 0)
		वापस rval;

	/*
	 * LED1 flash current setting
	 * LED2 flash current = Total(Max) flash current - LED1 flash current
	 */
	rval = regmap_update_bits(flash->regmap,
				  REG_LED1_FLASH_BR, 0x7F,
				  LM3646_LED1_FLASH_BRT_uA_TO_REG
				  (flash->pdata->led1_flash_brt));

	अगर (rval < 0)
		वापस rval;

	/*
	 * LED1 torch current setting
	 * LED2 torch current = Total(Max) torch current - LED1 torch current
	 */
	rval = regmap_update_bits(flash->regmap,
				  REG_LED1_TORCH_BR, 0x7F,
				  LM3646_LED1_TORCH_BRT_uA_TO_REG
				  (flash->pdata->led1_torch_brt));
	अगर (rval < 0)
		वापस rval;

	/* Reset flag रेजिस्टर */
	वापस regmap_पढ़ो(flash->regmap, REG_FLAG, &reg_val);
पूर्ण

अटल पूर्णांक lm3646_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *devid)
अणु
	काष्ठा lm3646_flash *flash;
	काष्ठा lm3646_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	पूर्णांक rval;

	flash = devm_kzalloc(&client->dev, माप(*flash), GFP_KERNEL);
	अगर (flash == शून्य)
		वापस -ENOMEM;

	flash->regmap = devm_regmap_init_i2c(client, &lm3646_regmap);
	अगर (IS_ERR(flash->regmap))
		वापस PTR_ERR(flash->regmap);

	/* check device tree अगर there is no platक्रमm data */
	अगर (pdata == शून्य) अणु
		pdata = devm_kzalloc(&client->dev,
				     माप(काष्ठा lm3646_platक्रमm_data),
				     GFP_KERNEL);
		अगर (pdata == शून्य)
			वापस -ENOMEM;
		/* use शेष data in हाल of no platक्रमm data */
		pdata->flash_समयout = LM3646_FLASH_TOUT_MAX;
		pdata->led1_torch_brt = LM3646_LED1_TORCH_BRT_MAX;
		pdata->led1_flash_brt = LM3646_LED1_FLASH_BRT_MAX;
	पूर्ण
	flash->pdata = pdata;
	flash->dev = &client->dev;

	rval = lm3646_subdev_init(flash);
	अगर (rval < 0)
		वापस rval;

	rval = lm3646_init_device(flash);
	अगर (rval < 0)
		वापस rval;

	i2c_set_clientdata(client, flash);

	वापस 0;
पूर्ण

अटल पूर्णांक lm3646_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3646_flash *flash = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(&flash->subdev_led);
	v4l2_ctrl_handler_मुक्त(&flash->ctrls_led);
	media_entity_cleanup(&flash->subdev_led.entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3646_id_table[] = अणु
	अणुLM3646_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lm3646_id_table);

अटल काष्ठा i2c_driver lm3646_i2c_driver = अणु
	.driver = अणु
		   .name = LM3646_NAME,
		   पूर्ण,
	.probe = lm3646_probe,
	.हटाओ = lm3646_हटाओ,
	.id_table = lm3646_id_table,
पूर्ण;

module_i2c_driver(lm3646_i2c_driver);

MODULE_AUTHOR("Daniel Jeong <gshark.jeong@gmail.com>");
MODULE_AUTHOR("Ldd Mlp <ldd-mlp@list.ti.com>");
MODULE_DESCRIPTION("Texas Instruments LM3646 Dual Flash LED driver");
MODULE_LICENSE("GPL");
