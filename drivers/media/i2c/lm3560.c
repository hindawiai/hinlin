<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/lm3560.c
 * General device driver क्रम TI lm3559, lm3560, FLASH LED Driver
 *
 * Copyright (C) 2013 Texas Instruments
 *
 * Contact: Daniel Jeong <gshark.jeong@gmail.com>
 *			Ldd-Mlp <ldd-mlp@list.ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/videodev2.h>
#समावेश <media/i2c/lm3560.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

/* रेजिस्टरs definitions */
#घोषणा REG_ENABLE		0x10
#घोषणा REG_TORCH_BR	0xa0
#घोषणा REG_FLASH_BR	0xb0
#घोषणा REG_FLASH_TOUT	0xc0
#घोषणा REG_FLAG		0xd0
#घोषणा REG_CONFIG1		0xe0

/* fault mask */
#घोषणा FAULT_TIMEOUT	(1<<0)
#घोषणा FAULT_OVERTEMP	(1<<1)
#घोषणा FAULT_SHORT_CIRCUIT	(1<<2)

क्रमागत led_enable अणु
	MODE_SHDN = 0x0,
	MODE_TORCH = 0x2,
	MODE_FLASH = 0x3,
पूर्ण;

/**
 * काष्ठा lm3560_flash
 *
 * @dev: poपूर्णांकer to &काष्ठा device
 * @pdata: platक्रमm data
 * @regmap: reg. map क्रम i2c
 * @lock: muxtex क्रम serial access.
 * @led_mode: V4L2 LED mode
 * @ctrls_led: V4L2 controls
 * @subdev_led: V4L2 subdev
 */
काष्ठा lm3560_flash अणु
	काष्ठा device *dev;
	काष्ठा lm3560_platक्रमm_data *pdata;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;

	क्रमागत v4l2_flash_led_mode led_mode;
	काष्ठा v4l2_ctrl_handler ctrls_led[LM3560_LED_MAX];
	काष्ठा v4l2_subdev subdev_led[LM3560_LED_MAX];
पूर्ण;

#घोषणा to_lm3560_flash(_ctrl, _no)	\
	container_of(_ctrl->handler, काष्ठा lm3560_flash, ctrls_led[_no])

/* enable mode control */
अटल पूर्णांक lm3560_mode_ctrl(काष्ठा lm3560_flash *flash)
अणु
	पूर्णांक rval = -EINVAL;

	चयन (flash->led_mode) अणु
	हाल V4L2_FLASH_LED_MODE_NONE:
		rval = regmap_update_bits(flash->regmap,
					  REG_ENABLE, 0x03, MODE_SHDN);
		अवरोध;
	हाल V4L2_FLASH_LED_MODE_TORCH:
		rval = regmap_update_bits(flash->regmap,
					  REG_ENABLE, 0x03, MODE_TORCH);
		अवरोध;
	हाल V4L2_FLASH_LED_MODE_FLASH:
		rval = regmap_update_bits(flash->regmap,
					  REG_ENABLE, 0x03, MODE_FLASH);
		अवरोध;
	पूर्ण
	वापस rval;
पूर्ण

/* led1/2 enable/disable */
अटल पूर्णांक lm3560_enable_ctrl(काष्ठा lm3560_flash *flash,
			      क्रमागत lm3560_led_id led_no, bool on)
अणु
	पूर्णांक rval;

	अगर (led_no == LM3560_LED0) अणु
		अगर (on)
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x08, 0x08);
		अन्यथा
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x08, 0x00);
	पूर्ण अन्यथा अणु
		अगर (on)
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x10, 0x10);
		अन्यथा
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x10, 0x00);
	पूर्ण
	वापस rval;
पूर्ण

/* torch1/2 brightness control */
अटल पूर्णांक lm3560_torch_brt_ctrl(काष्ठा lm3560_flash *flash,
				 क्रमागत lm3560_led_id led_no, अचिन्हित पूर्णांक brt)
अणु
	पूर्णांक rval;
	u8 br_bits;

	अगर (brt < LM3560_TORCH_BRT_MIN)
		वापस lm3560_enable_ctrl(flash, led_no, false);
	अन्यथा
		rval = lm3560_enable_ctrl(flash, led_no, true);

	br_bits = LM3560_TORCH_BRT_uA_TO_REG(brt);
	अगर (led_no == LM3560_LED0)
		rval = regmap_update_bits(flash->regmap,
					  REG_TORCH_BR, 0x07, br_bits);
	अन्यथा
		rval = regmap_update_bits(flash->regmap,
					  REG_TORCH_BR, 0x38, br_bits << 3);

	वापस rval;
पूर्ण

/* flash1/2 brightness control */
अटल पूर्णांक lm3560_flash_brt_ctrl(काष्ठा lm3560_flash *flash,
				 क्रमागत lm3560_led_id led_no, अचिन्हित पूर्णांक brt)
अणु
	पूर्णांक rval;
	u8 br_bits;

	अगर (brt < LM3560_FLASH_BRT_MIN)
		वापस lm3560_enable_ctrl(flash, led_no, false);
	अन्यथा
		rval = lm3560_enable_ctrl(flash, led_no, true);

	br_bits = LM3560_FLASH_BRT_uA_TO_REG(brt);
	अगर (led_no == LM3560_LED0)
		rval = regmap_update_bits(flash->regmap,
					  REG_FLASH_BR, 0x0f, br_bits);
	अन्यथा
		rval = regmap_update_bits(flash->regmap,
					  REG_FLASH_BR, 0xf0, br_bits << 4);

	वापस rval;
पूर्ण

/* v4l2 controls  */
अटल पूर्णांक lm3560_get_ctrl(काष्ठा v4l2_ctrl *ctrl, क्रमागत lm3560_led_id led_no)
अणु
	काष्ठा lm3560_flash *flash = to_lm3560_flash(ctrl, led_no);
	पूर्णांक rval = -EINVAL;

	mutex_lock(&flash->lock);

	अगर (ctrl->id == V4L2_CID_FLASH_FAULT) अणु
		s32 fault = 0;
		अचिन्हित पूर्णांक reg_val;
		rval = regmap_पढ़ो(flash->regmap, REG_FLAG, &reg_val);
		अगर (rval < 0)
			जाओ out;
		अगर (reg_val & FAULT_SHORT_CIRCUIT)
			fault |= V4L2_FLASH_FAULT_SHORT_CIRCUIT;
		अगर (reg_val & FAULT_OVERTEMP)
			fault |= V4L2_FLASH_FAULT_OVER_TEMPERATURE;
		अगर (reg_val & FAULT_TIMEOUT)
			fault |= V4L2_FLASH_FAULT_TIMEOUT;
		ctrl->cur.val = fault;
	पूर्ण

out:
	mutex_unlock(&flash->lock);
	वापस rval;
पूर्ण

अटल पूर्णांक lm3560_set_ctrl(काष्ठा v4l2_ctrl *ctrl, क्रमागत lm3560_led_id led_no)
अणु
	काष्ठा lm3560_flash *flash = to_lm3560_flash(ctrl, led_no);
	u8 tout_bits;
	पूर्णांक rval = -EINVAL;

	mutex_lock(&flash->lock);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FLASH_LED_MODE:
		flash->led_mode = ctrl->val;
		अगर (flash->led_mode != V4L2_FLASH_LED_MODE_FLASH)
			rval = lm3560_mode_ctrl(flash);
		अवरोध;

	हाल V4L2_CID_FLASH_STROBE_SOURCE:
		rval = regmap_update_bits(flash->regmap,
					  REG_CONFIG1, 0x04, (ctrl->val) << 2);
		अगर (rval < 0)
			जाओ err_out;
		अवरोध;

	हाल V4L2_CID_FLASH_STROBE:
		अगर (flash->led_mode != V4L2_FLASH_LED_MODE_FLASH) अणु
			rval = -EBUSY;
			जाओ err_out;
		पूर्ण
		flash->led_mode = V4L2_FLASH_LED_MODE_FLASH;
		rval = lm3560_mode_ctrl(flash);
		अवरोध;

	हाल V4L2_CID_FLASH_STROBE_STOP:
		अगर (flash->led_mode != V4L2_FLASH_LED_MODE_FLASH) अणु
			rval = -EBUSY;
			जाओ err_out;
		पूर्ण
		flash->led_mode = V4L2_FLASH_LED_MODE_NONE;
		rval = lm3560_mode_ctrl(flash);
		अवरोध;

	हाल V4L2_CID_FLASH_TIMEOUT:
		tout_bits = LM3560_FLASH_TOUT_ms_TO_REG(ctrl->val);
		rval = regmap_update_bits(flash->regmap,
					  REG_FLASH_TOUT, 0x1f, tout_bits);
		अवरोध;

	हाल V4L2_CID_FLASH_INTENSITY:
		rval = lm3560_flash_brt_ctrl(flash, led_no, ctrl->val);
		अवरोध;

	हाल V4L2_CID_FLASH_TORCH_INTENSITY:
		rval = lm3560_torch_brt_ctrl(flash, led_no, ctrl->val);
		अवरोध;
	पूर्ण

err_out:
	mutex_unlock(&flash->lock);
	वापस rval;
पूर्ण

अटल पूर्णांक lm3560_led1_get_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस lm3560_get_ctrl(ctrl, LM3560_LED1);
पूर्ण

अटल पूर्णांक lm3560_led1_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस lm3560_set_ctrl(ctrl, LM3560_LED1);
पूर्ण

अटल पूर्णांक lm3560_led0_get_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस lm3560_get_ctrl(ctrl, LM3560_LED0);
पूर्ण

अटल पूर्णांक lm3560_led0_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस lm3560_set_ctrl(ctrl, LM3560_LED0);
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops lm3560_led_ctrl_ops[LM3560_LED_MAX] = अणु
	[LM3560_LED0] = अणु
			 .g_अस्थिर_ctrl = lm3560_led0_get_ctrl,
			 .s_ctrl = lm3560_led0_set_ctrl,
			 पूर्ण,
	[LM3560_LED1] = अणु
			 .g_अस्थिर_ctrl = lm3560_led1_get_ctrl,
			 .s_ctrl = lm3560_led1_set_ctrl,
			 पूर्ण
पूर्ण;

अटल पूर्णांक lm3560_init_controls(काष्ठा lm3560_flash *flash,
				क्रमागत lm3560_led_id led_no)
अणु
	काष्ठा v4l2_ctrl *fault;
	u32 max_flash_brt = flash->pdata->max_flash_brt[led_no];
	u32 max_torch_brt = flash->pdata->max_torch_brt[led_no];
	काष्ठा v4l2_ctrl_handler *hdl = &flash->ctrls_led[led_no];
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &lm3560_led_ctrl_ops[led_no];

	v4l2_ctrl_handler_init(hdl, 8);

	/* flash mode */
	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_FLASH_LED_MODE,
			       V4L2_FLASH_LED_MODE_TORCH, ~0x7,
			       V4L2_FLASH_LED_MODE_NONE);
	flash->led_mode = V4L2_FLASH_LED_MODE_NONE;

	/* flash source */
	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_FLASH_STROBE_SOURCE,
			       0x1, ~0x3, V4L2_FLASH_STROBE_SOURCE_SOFTWARE);

	/* flash strobe */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_STROBE, 0, 0, 0, 0);

	/* flash strobe stop */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_STROBE_STOP, 0, 0, 0, 0);

	/* flash strobe समयout */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_TIMEOUT,
			  LM3560_FLASH_TOUT_MIN,
			  flash->pdata->max_flash_समयout,
			  LM3560_FLASH_TOUT_STEP,
			  flash->pdata->max_flash_समयout);

	/* flash brt */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_INTENSITY,
			  LM3560_FLASH_BRT_MIN, max_flash_brt,
			  LM3560_FLASH_BRT_STEP, max_flash_brt);

	/* torch brt */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_TORCH_INTENSITY,
			  LM3560_TORCH_BRT_MIN, max_torch_brt,
			  LM3560_TORCH_BRT_STEP, max_torch_brt);

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

	flash->subdev_led[led_no].ctrl_handler = hdl;
	वापस 0;
पूर्ण

/* initialize device */
अटल स्थिर काष्ठा v4l2_subdev_ops lm3560_ops = अणु
	.core = शून्य,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lm3560_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xFF,
पूर्ण;

अटल पूर्णांक lm3560_subdev_init(काष्ठा lm3560_flash *flash,
			      क्रमागत lm3560_led_id led_no, अक्षर *led_name)
अणु
	काष्ठा i2c_client *client = to_i2c_client(flash->dev);
	पूर्णांक rval;

	v4l2_i2c_subdev_init(&flash->subdev_led[led_no], client, &lm3560_ops);
	flash->subdev_led[led_no].flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(flash->subdev_led[led_no].name, led_name,
		माप(flash->subdev_led[led_no].name));
	rval = lm3560_init_controls(flash, led_no);
	अगर (rval)
		जाओ err_out;
	rval = media_entity_pads_init(&flash->subdev_led[led_no].entity, 0, शून्य);
	अगर (rval < 0)
		जाओ err_out;
	flash->subdev_led[led_no].entity.function = MEDIA_ENT_F_FLASH;

	वापस rval;

err_out:
	v4l2_ctrl_handler_मुक्त(&flash->ctrls_led[led_no]);
	वापस rval;
पूर्ण

अटल पूर्णांक lm3560_init_device(काष्ठा lm3560_flash *flash)
अणु
	पूर्णांक rval;
	अचिन्हित पूर्णांक reg_val;

	/* set peak current */
	rval = regmap_update_bits(flash->regmap,
				  REG_FLASH_TOUT, 0x60, flash->pdata->peak);
	अगर (rval < 0)
		वापस rval;
	/* output disable */
	flash->led_mode = V4L2_FLASH_LED_MODE_NONE;
	rval = lm3560_mode_ctrl(flash);
	अगर (rval < 0)
		वापस rval;
	/* reset faults */
	rval = regmap_पढ़ो(flash->regmap, REG_FLAG, &reg_val);
	वापस rval;
पूर्ण

अटल पूर्णांक lm3560_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *devid)
अणु
	काष्ठा lm3560_flash *flash;
	काष्ठा lm3560_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	पूर्णांक rval;

	flash = devm_kzalloc(&client->dev, माप(*flash), GFP_KERNEL);
	अगर (flash == शून्य)
		वापस -ENOMEM;

	flash->regmap = devm_regmap_init_i2c(client, &lm3560_regmap);
	अगर (IS_ERR(flash->regmap)) अणु
		rval = PTR_ERR(flash->regmap);
		वापस rval;
	पूर्ण

	/* अगर there is no platक्रमm data, use chip शेष value */
	अगर (pdata == शून्य) अणु
		pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
		अगर (pdata == शून्य)
			वापस -ENODEV;
		pdata->peak = LM3560_PEAK_3600mA;
		pdata->max_flash_समयout = LM3560_FLASH_TOUT_MAX;
		/* led 1 */
		pdata->max_flash_brt[LM3560_LED0] = LM3560_FLASH_BRT_MAX;
		pdata->max_torch_brt[LM3560_LED0] = LM3560_TORCH_BRT_MAX;
		/* led 2 */
		pdata->max_flash_brt[LM3560_LED1] = LM3560_FLASH_BRT_MAX;
		pdata->max_torch_brt[LM3560_LED1] = LM3560_TORCH_BRT_MAX;
	पूर्ण
	flash->pdata = pdata;
	flash->dev = &client->dev;
	mutex_init(&flash->lock);

	rval = lm3560_subdev_init(flash, LM3560_LED0, "lm3560-led0");
	अगर (rval < 0)
		वापस rval;

	rval = lm3560_subdev_init(flash, LM3560_LED1, "lm3560-led1");
	अगर (rval < 0)
		वापस rval;

	rval = lm3560_init_device(flash);
	अगर (rval < 0)
		वापस rval;

	i2c_set_clientdata(client, flash);

	वापस 0;
पूर्ण

अटल पूर्णांक lm3560_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3560_flash *flash = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक i;

	क्रम (i = LM3560_LED0; i < LM3560_LED_MAX; i++) अणु
		v4l2_device_unरेजिस्टर_subdev(&flash->subdev_led[i]);
		v4l2_ctrl_handler_मुक्त(&flash->ctrls_led[i]);
		media_entity_cleanup(&flash->subdev_led[i].entity);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3560_id_table[] = अणु
	अणुLM3559_NAME, 0पूर्ण,
	अणुLM3560_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lm3560_id_table);

अटल काष्ठा i2c_driver lm3560_i2c_driver = अणु
	.driver = अणु
		   .name = LM3560_NAME,
		   .pm = शून्य,
		   पूर्ण,
	.probe = lm3560_probe,
	.हटाओ = lm3560_हटाओ,
	.id_table = lm3560_id_table,
पूर्ण;

module_i2c_driver(lm3560_i2c_driver);

MODULE_AUTHOR("Daniel Jeong <gshark.jeong@gmail.com>");
MODULE_AUTHOR("Ldd Mlp <ldd-mlp@list.ti.com>");
MODULE_DESCRIPTION("Texas Instruments LM3560 LED flash driver");
MODULE_LICENSE("GPL");
