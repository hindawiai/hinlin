<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8775 - driver version 0.0.1
 *
 * Copyright (C) 2004 Ulf Eklund <ivtv at eklund.to>
 *
 * Based on saa7115 driver
 *
 * Copyright (C) 2005 Hans Verkuil <hverkuil@xs4all.nl>
 * - Cleanup
 * - V4L2 API update
 * - sound fixes
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/i2c/wm8775.h>

MODULE_DESCRIPTION("wm8775 driver");
MODULE_AUTHOR("Ulf Eklund, Hans Verkuil");
MODULE_LICENSE("GPL");



/* ----------------------------------------------------------------------- */

क्रमागत अणु
	R7 = 7, R11 = 11,
	R12, R13, R14, R15, R16, R17, R18, R19, R20, R21, R23 = 23,
	TOT_REGS
पूर्ण;

#घोषणा ALC_HOLD 0x85 /* R17: use zero cross detection, ALC hold समय 42.6 ms */
#घोषणा ALC_EN 0x100  /* R17: ALC enable */

काष्ठा wm8775_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *mute;
	काष्ठा v4l2_ctrl *vol;
	काष्ठा v4l2_ctrl *bal;
	काष्ठा v4l2_ctrl *loud;
	u8 input;		/* Last selected input (0-0xf) */
पूर्ण;

अटल अंतरभूत काष्ठा wm8775_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा wm8775_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा wm8775_state, hdl)->sd;
पूर्ण

अटल पूर्णांक wm8775_ग_लिखो(काष्ठा v4l2_subdev *sd, पूर्णांक reg, u16 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक i;

	अगर (reg < 0 || reg >= TOT_REGS) अणु
		v4l2_err(sd, "Invalid register R%d\n", reg);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		अगर (i2c_smbus_ग_लिखो_byte_data(client,
				(reg << 1) | (val >> 8), val & 0xff) == 0)
			वापस 0;
	v4l2_err(sd, "I2C: cannot write %03x to register R%d\n", val, reg);
	वापस -1;
पूर्ण

अटल व्योम wm8775_set_audio(काष्ठा v4l2_subdev *sd, पूर्णांक quietly)
अणु
	काष्ठा wm8775_state *state = to_state(sd);
	u8 vol_l, vol_r;
	पूर्णांक muted = 0 != state->mute->val;
	u16 volume = (u16)state->vol->val;
	u16 balance = (u16)state->bal->val;

	/* normalize ( 65535 to 0 -> 255 to 0 (+24dB to -103dB) ) */
	vol_l = (min(65536 - balance, 32768) * volume) >> 23;
	vol_r = (min(balance, (u16)32768) * volume) >> 23;

	/* Mute */
	अगर (muted || quietly)
		wm8775_ग_लिखो(sd, R21, 0x0c0 | state->input);

	wm8775_ग_लिखो(sd, R14, vol_l | 0x100); /* 0x100= Left channel ADC zero cross enable */
	wm8775_ग_लिखो(sd, R15, vol_r | 0x100); /* 0x100= Right channel ADC zero cross enable */

	/* Un-mute */
	अगर (!muted)
		wm8775_ग_लिखो(sd, R21, state->input);
पूर्ण

अटल पूर्णांक wm8775_s_routing(काष्ठा v4l2_subdev *sd,
			    u32 input, u32 output, u32 config)
अणु
	काष्ठा wm8775_state *state = to_state(sd);

	/* There are 4 inमाला_दो and one output. Zero or more inमाला_दो
	   are multiplexed together to the output. Hence there are
	   16 combinations.
	   If only one input is active (the normal हाल) then the
	   input values 1, 2, 4 or 8 should be used. */
	अगर (input > 15) अणु
		v4l2_err(sd, "Invalid input %d.\n", input);
		वापस -EINVAL;
	पूर्ण
	state->input = input;
	अगर (v4l2_ctrl_g_ctrl(state->mute))
		वापस 0;
	अगर (!v4l2_ctrl_g_ctrl(state->vol))
		वापस 0;
	wm8775_set_audio(sd, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8775_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
	हाल V4L2_CID_AUDIO_VOLUME:
	हाल V4L2_CID_AUDIO_BALANCE:
		wm8775_set_audio(sd, 0);
		वापस 0;
	हाल V4L2_CID_AUDIO_LOUDNESS:
		wm8775_ग_लिखो(sd, R17, (ctrl->val ? ALC_EN : 0) | ALC_HOLD);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8775_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा wm8775_state *state = to_state(sd);

	v4l2_info(sd, "Input: %d\n", state->input);
	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8775_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *freq)
अणु
	wm8775_set_audio(sd, 0);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops wm8775_ctrl_ops = अणु
	.s_ctrl = wm8775_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops wm8775_core_ops = अणु
	.log_status = wm8775_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops wm8775_tuner_ops = अणु
	.s_frequency = wm8775_s_frequency,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops wm8775_audio_ops = अणु
	.s_routing = wm8775_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops wm8775_ops = अणु
	.core = &wm8775_core_ops,
	.tuner = &wm8775_tuner_ops,
	.audio = &wm8775_audio_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

/* i2c implementation */

/*
 * Generic i2c probe
 * concerning the addresses: i2c wants 7 bit (without the r/w bit), so '>>1'
 */

अटल पूर्णांक wm8775_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8775_state *state;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक err;
	bool is_nova_s = false;

	अगर (client->dev.platक्रमm_data) अणु
		काष्ठा wm8775_platक्रमm_data *data = client->dev.platक्रमm_data;
		is_nova_s = data->is_nova_s;
	पूर्ण

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &wm8775_ops);
	state->input = 2;

	v4l2_ctrl_handler_init(&state->hdl, 4);
	state->mute = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	state->vol = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 65535, (65535+99)/100, 0xCF00); /* 0dB*/
	state->bal = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE, 0, 65535, (65535+99)/100, 32768);
	state->loud = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_LOUDNESS, 0, 1, 1, 1);
	sd->ctrl_handler = &state->hdl;
	err = state->hdl.error;
	अगर (err) अणु
		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण

	/* Initialize wm8775 */

	/* RESET */
	wm8775_ग_लिखो(sd, R23, 0x000);
	/* Disable zero cross detect समयout */
	wm8775_ग_लिखो(sd, R7, 0x000);
	/* HPF enable, left justअगरied, 24-bit (Philips) mode */
	wm8775_ग_लिखो(sd, R11, 0x021);
	/* Master mode, घड़ी ratio 256fs */
	wm8775_ग_लिखो(sd, R12, 0x102);
	/* Powered up */
	wm8775_ग_लिखो(sd, R13, 0x000);

	अगर (!is_nova_s) अणु
		/* ADC gain +2.5dB, enable zero cross */
		wm8775_ग_लिखो(sd, R14, 0x1d4);
		/* ADC gain +2.5dB, enable zero cross */
		wm8775_ग_लिखो(sd, R15, 0x1d4);
		/* ALC Stereo, ALC target level -1dB FS max gain +8dB */
		wm8775_ग_लिखो(sd, R16, 0x1bf);
		/* Enable gain control, use zero cross detection,
		   ALC hold समय 42.6 ms */
		wm8775_ग_लिखो(sd, R17, 0x185);
	पूर्ण अन्यथा अणु
		/* ALC stereo, ALC target level -5dB FS, ALC max gain +8dB */
		wm8775_ग_लिखो(sd, R16, 0x1bb);
		/* Set ALC mode and hold समय */
		wm8775_ग_लिखो(sd, R17, (state->loud->val ? ALC_EN : 0) | ALC_HOLD);
	पूर्ण
	/* ALC gain ramp up delay 34 s, ALC gain ramp करोwn delay 33 ms */
	wm8775_ग_लिखो(sd, R18, 0x0a2);
	/* Enable noise gate, threshold -72dBfs */
	wm8775_ग_लिखो(sd, R19, 0x005);
	अगर (!is_nova_s) अणु
		/* Transient winकरोw 4ms, lower PGA gain limit -1dB */
		wm8775_ग_लिखो(sd, R20, 0x07a);
		/* LRBOTH = 1, use input 2. */
		wm8775_ग_लिखो(sd, R21, 0x102);
	पूर्ण अन्यथा अणु
		/* Transient winकरोw 4ms, ALC min gain -5dB  */
		wm8775_ग_लिखो(sd, R20, 0x0fb);

		wm8775_set_audio(sd, 1);      /* set volume/mute/mux */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8775_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा wm8775_state *state = to_state(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8775_id[] = अणु
	अणु "wm8775", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8775_id);

अटल काष्ठा i2c_driver wm8775_driver = अणु
	.driver = अणु
		.name	= "wm8775",
	पूर्ण,
	.probe		= wm8775_probe,
	.हटाओ		= wm8775_हटाओ,
	.id_table	= wm8775_id,
पूर्ण;

module_i2c_driver(wm8775_driver);
