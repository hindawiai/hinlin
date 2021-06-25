<शैली गुरु>
/*
 * adv7393 - ADV7393 Video Encoder Driver
 *
 * The encoder hardware करोes not support SECAM.
 *
 * Copyright (C) 2010-2012 ADVANSEE - http://www.advansee.com/
 * Benoथऍt Thथऊbaudeau <benoit.thebaudeau@advansee.com>
 *
 * Based on ADV7343 driver,
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/uaccess.h>

#समावेश <media/i2c/adv7393.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "adv7393_regs.h"

MODULE_DESCRIPTION("ADV7393 video encoder driver");
MODULE_LICENSE("GPL");

अटल bool debug;
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Debug level 0-1");

काष्ठा adv7393_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	u8 reg00;
	u8 reg01;
	u8 reg02;
	u8 reg35;
	u8 reg80;
	u8 reg82;
	u32 output;
	v4l2_std_id std;
पूर्ण;

अटल अंतरभूत काष्ठा adv7393_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा adv7393_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा adv7393_state, hdl)->sd;
पूर्ण

अटल अंतरभूत पूर्णांक adv7393_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल स्थिर u8 adv7393_init_reg_val[] = अणु
	ADV7393_SOFT_RESET, ADV7393_SOFT_RESET_DEFAULT,
	ADV7393_POWER_MODE_REG, ADV7393_POWER_MODE_REG_DEFAULT,

	ADV7393_HD_MODE_REG1, ADV7393_HD_MODE_REG1_DEFAULT,
	ADV7393_HD_MODE_REG2, ADV7393_HD_MODE_REG2_DEFAULT,
	ADV7393_HD_MODE_REG3, ADV7393_HD_MODE_REG3_DEFAULT,
	ADV7393_HD_MODE_REG4, ADV7393_HD_MODE_REG4_DEFAULT,
	ADV7393_HD_MODE_REG5, ADV7393_HD_MODE_REG5_DEFAULT,
	ADV7393_HD_MODE_REG6, ADV7393_HD_MODE_REG6_DEFAULT,
	ADV7393_HD_MODE_REG7, ADV7393_HD_MODE_REG7_DEFAULT,

	ADV7393_SD_MODE_REG1, ADV7393_SD_MODE_REG1_DEFAULT,
	ADV7393_SD_MODE_REG2, ADV7393_SD_MODE_REG2_DEFAULT,
	ADV7393_SD_MODE_REG3, ADV7393_SD_MODE_REG3_DEFAULT,
	ADV7393_SD_MODE_REG4, ADV7393_SD_MODE_REG4_DEFAULT,
	ADV7393_SD_MODE_REG5, ADV7393_SD_MODE_REG5_DEFAULT,
	ADV7393_SD_MODE_REG6, ADV7393_SD_MODE_REG6_DEFAULT,
	ADV7393_SD_MODE_REG7, ADV7393_SD_MODE_REG7_DEFAULT,
	ADV7393_SD_MODE_REG8, ADV7393_SD_MODE_REG8_DEFAULT,

	ADV7393_SD_TIMING_REG0, ADV7393_SD_TIMING_REG0_DEFAULT,

	ADV7393_SD_HUE_ADJUST, ADV7393_SD_HUE_ADJUST_DEFAULT,
	ADV7393_SD_CGMS_WSS0, ADV7393_SD_CGMS_WSS0_DEFAULT,
	ADV7393_SD_BRIGHTNESS_WSS, ADV7393_SD_BRIGHTNESS_WSS_DEFAULT,
पूर्ण;

/*
 *			    2^32
 * FSC(reg) =  FSC (HZ) * --------
 *			  27000000
 */
अटल स्थिर काष्ठा adv7393_std_info मानक_निवेशfo[] = अणु
	अणु
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_NTSC, 705268427, V4L2_STD_NTSC_443,
	पूर्ण, अणु
		/* FSC(Hz) = 3,579,545.45 Hz */
		SD_STD_NTSC, 569408542, V4L2_STD_NTSC,
	पूर्ण, अणु
		/* FSC(Hz) = 3,575,611.00 Hz */
		SD_STD_PAL_M, 568782678, V4L2_STD_PAL_M,
	पूर्ण, अणु
		/* FSC(Hz) = 3,582,056.00 Hz */
		SD_STD_PAL_N, 569807903, V4L2_STD_PAL_Nc,
	पूर्ण, अणु
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAL_N, 705268427, V4L2_STD_PAL_N,
	पूर्ण, अणु
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAL_M, 705268427, V4L2_STD_PAL_60,
	पूर्ण, अणु
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAL_BDGHI, 705268427, V4L2_STD_PAL,
	पूर्ण,
पूर्ण;

अटल पूर्णांक adv7393_setstd(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा adv7393_state *state = to_state(sd);
	स्थिर काष्ठा adv7393_std_info *std_info;
	पूर्णांक num_std;
	u8 reg;
	u32 val;
	पूर्णांक err = 0;
	पूर्णांक i;

	num_std = ARRAY_SIZE(मानक_निवेशfo);

	क्रम (i = 0; i < num_std; i++) अणु
		अगर (मानक_निवेशfo[i].stdid & std)
			अवरोध;
	पूर्ण

	अगर (i == num_std) अणु
		v4l2_dbg(1, debug, sd,
				"Invalid std or std is not supported: %llx\n",
						(अचिन्हित दीर्घ दीर्घ)std);
		वापस -EINVAL;
	पूर्ण

	std_info = &मानक_निवेशfo[i];

	/* Set the standard */
	val = state->reg80 & ~SD_STD_MASK;
	val |= std_info->standard_val3;
	err = adv7393_ग_लिखो(sd, ADV7393_SD_MODE_REG1, val);
	अगर (err < 0)
		जाओ setstd_निकास;

	state->reg80 = val;

	/* Configure the input mode रेजिस्टर */
	val = state->reg01 & ~INPUT_MODE_MASK;
	val |= SD_INPUT_MODE;
	err = adv7393_ग_लिखो(sd, ADV7393_MODE_SELECT_REG, val);
	अगर (err < 0)
		जाओ setstd_निकास;

	state->reg01 = val;

	/* Program the sub carrier frequency रेजिस्टरs */
	val = std_info->fsc_val;
	क्रम (reg = ADV7393_FSC_REG0; reg <= ADV7393_FSC_REG3; reg++) अणु
		err = adv7393_ग_लिखो(sd, reg, val);
		अगर (err < 0)
			जाओ setstd_निकास;
		val >>= 8;
	पूर्ण

	val = state->reg82;

	/* Pedestal settings */
	अगर (std & (V4L2_STD_NTSC | V4L2_STD_NTSC_443))
		val |= SD_PEDESTAL_EN;
	अन्यथा
		val &= SD_PEDESTAL_DI;

	err = adv7393_ग_लिखो(sd, ADV7393_SD_MODE_REG2, val);
	अगर (err < 0)
		जाओ setstd_निकास;

	state->reg82 = val;

setstd_निकास:
	अगर (err != 0)
		v4l2_err(sd, "Error setting std, write failed\n");

	वापस err;
पूर्ण

अटल पूर्णांक adv7393_setoutput(काष्ठा v4l2_subdev *sd, u32 output_type)
अणु
	काष्ठा adv7393_state *state = to_state(sd);
	u8 val;
	पूर्णांक err = 0;

	अगर (output_type > ADV7393_SVIDEO_ID) अणु
		v4l2_dbg(1, debug, sd,
			"Invalid output type or output type not supported:%d\n",
								output_type);
		वापस -EINVAL;
	पूर्ण

	/* Enable Appropriate DAC */
	val = state->reg00 & 0x03;

	अगर (output_type == ADV7393_COMPOSITE_ID)
		val |= ADV7393_COMPOSITE_POWER_VALUE;
	अन्यथा अगर (output_type == ADV7393_COMPONENT_ID)
		val |= ADV7393_COMPONENT_POWER_VALUE;
	अन्यथा
		val |= ADV7393_SVIDEO_POWER_VALUE;

	err = adv7393_ग_लिखो(sd, ADV7393_POWER_MODE_REG, val);
	अगर (err < 0)
		जाओ setoutput_निकास;

	state->reg00 = val;

	/* Enable YUV output */
	val = state->reg02 | YUV_OUTPUT_SELECT;
	err = adv7393_ग_लिखो(sd, ADV7393_MODE_REG0, val);
	अगर (err < 0)
		जाओ setoutput_निकास;

	state->reg02 = val;

	/* configure SD DAC Output 1 bit */
	val = state->reg82;
	अगर (output_type == ADV7393_COMPONENT_ID)
		val &= SD_DAC_OUT1_DI;
	अन्यथा
		val |= SD_DAC_OUT1_EN;
	err = adv7393_ग_लिखो(sd, ADV7393_SD_MODE_REG2, val);
	अगर (err < 0)
		जाओ setoutput_निकास;

	state->reg82 = val;

	/* configure ED/HD Color DAC Swap bit to zero */
	val = state->reg35 & HD_DAC_SWAP_DI;
	err = adv7393_ग_लिखो(sd, ADV7393_HD_MODE_REG6, val);
	अगर (err < 0)
		जाओ setoutput_निकास;

	state->reg35 = val;

setoutput_निकास:
	अगर (err != 0)
		v4l2_err(sd, "Error setting output, write failed\n");

	वापस err;
पूर्ण

अटल पूर्णांक adv7393_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7393_state *state = to_state(sd);

	v4l2_info(sd, "Standard: %llx\n", (अचिन्हित दीर्घ दीर्घ)state->std);
	v4l2_info(sd, "Output: %s\n", (state->output == 0) ? "Composite" :
			((state->output == 1) ? "Component" : "S-Video"));
	वापस 0;
पूर्ण

अटल पूर्णांक adv7393_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		वापस adv7393_ग_लिखो(sd, ADV7393_SD_BRIGHTNESS_WSS,
					ctrl->val & SD_BRIGHTNESS_VALUE_MASK);

	हाल V4L2_CID_HUE:
		वापस adv7393_ग_लिखो(sd, ADV7393_SD_HUE_ADJUST,
					ctrl->val - ADV7393_HUE_MIN);

	हाल V4L2_CID_GAIN:
		वापस adv7393_ग_लिखो(sd, ADV7393_DAC123_OUTPUT_LEVEL,
					ctrl->val);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops adv7393_ctrl_ops = अणु
	.s_ctrl = adv7393_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops adv7393_core_ops = अणु
	.log_status = adv7393_log_status,
पूर्ण;

अटल पूर्णांक adv7393_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा adv7393_state *state = to_state(sd);
	पूर्णांक err = 0;

	अगर (state->std == std)
		वापस 0;

	err = adv7393_setstd(sd, std);
	अगर (!err)
		state->std = std;

	वापस err;
पूर्ण

अटल पूर्णांक adv7393_s_routing(काष्ठा v4l2_subdev *sd,
		u32 input, u32 output, u32 config)
अणु
	काष्ठा adv7393_state *state = to_state(sd);
	पूर्णांक err = 0;

	अगर (state->output == output)
		वापस 0;

	err = adv7393_setoutput(sd, output);
	अगर (!err)
		state->output = output;

	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv7393_video_ops = अणु
	.s_std_output	= adv7393_s_std_output,
	.s_routing	= adv7393_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops adv7393_ops = अणु
	.core	= &adv7393_core_ops,
	.video	= &adv7393_video_ops,
पूर्ण;

अटल पूर्णांक adv7393_initialize(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7393_state *state = to_state(sd);
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adv7393_init_reg_val); i += 2) अणु

		err = adv7393_ग_लिखो(sd, adv7393_init_reg_val[i],
					adv7393_init_reg_val[i+1]);
		अगर (err) अणु
			v4l2_err(sd, "Error initializing\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* Configure क्रम शेष video standard */
	err = adv7393_setoutput(sd, state->output);
	अगर (err < 0) अणु
		v4l2_err(sd, "Error setting output during init\n");
		वापस -EINVAL;
	पूर्ण

	err = adv7393_setstd(sd, state->std);
	अगर (err < 0) अणु
		v4l2_err(sd, "Error setting std during init\n");
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक adv7393_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adv7393_state *state;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;

	state->reg00	= ADV7393_POWER_MODE_REG_DEFAULT;
	state->reg01	= 0x00;
	state->reg02	= 0x20;
	state->reg35	= ADV7393_HD_MODE_REG6_DEFAULT;
	state->reg80	= ADV7393_SD_MODE_REG1_DEFAULT;
	state->reg82	= ADV7393_SD_MODE_REG2_DEFAULT;

	state->output = ADV7393_COMPOSITE_ID;
	state->std = V4L2_STD_NTSC;

	v4l2_i2c_subdev_init(&state->sd, client, &adv7393_ops);

	v4l2_ctrl_handler_init(&state->hdl, 3);
	v4l2_ctrl_new_std(&state->hdl, &adv7393_ctrl_ops,
			V4L2_CID_BRIGHTNESS, ADV7393_BRIGHTNESS_MIN,
					     ADV7393_BRIGHTNESS_MAX, 1,
					     ADV7393_BRIGHTNESS_DEF);
	v4l2_ctrl_new_std(&state->hdl, &adv7393_ctrl_ops,
			V4L2_CID_HUE, ADV7393_HUE_MIN,
				      ADV7393_HUE_MAX, 1,
				      ADV7393_HUE_DEF);
	v4l2_ctrl_new_std(&state->hdl, &adv7393_ctrl_ops,
			V4L2_CID_GAIN, ADV7393_GAIN_MIN,
				       ADV7393_GAIN_MAX, 1,
				       ADV7393_GAIN_DEF);
	state->sd.ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		पूर्णांक err = state->hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_handler_setup(&state->hdl);

	err = adv7393_initialize(&state->sd);
	अगर (err)
		v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस err;
पूर्ण

अटल पूर्णांक adv7393_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा adv7393_state *state = to_state(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adv7393_id[] = अणु
	अणु"adv7393", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adv7393_id);

अटल काष्ठा i2c_driver adv7393_driver = अणु
	.driver = अणु
		.name	= "adv7393",
	पूर्ण,
	.probe		= adv7393_probe,
	.हटाओ		= adv7393_हटाओ,
	.id_table	= adv7393_id,
पूर्ण;
module_i2c_driver(adv7393_driver);
