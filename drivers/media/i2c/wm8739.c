<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8739
 *
 * Copyright (C) 2005 T. Adachi <tadachi@tadachi-net.com>
 *
 * Copyright (C) 2005 Hans Verkuil <hverkuil@xs4all.nl>
 * - Cleanup
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

MODULE_DESCRIPTION("wm8739 driver");
MODULE_AUTHOR("T. Adachi, Hans Verkuil");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;

module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(debug, "Debug level (0-1)");


/* ------------------------------------------------------------------------ */

क्रमागत अणु
	R0 = 0, R1,
	R5 = 5, R6, R7, R8, R9, R15 = 15,
	TOT_REGS
पूर्ण;

काष्ठा wm8739_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* audio cluster */
		काष्ठा v4l2_ctrl *volume;
		काष्ठा v4l2_ctrl *mute;
		काष्ठा v4l2_ctrl *balance;
	पूर्ण;
	u32 घड़ी_freq;
पूर्ण;

अटल अंतरभूत काष्ठा wm8739_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा wm8739_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा wm8739_state, hdl)->sd;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक wm8739_ग_लिखो(काष्ठा v4l2_subdev *sd, पूर्णांक reg, u16 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक i;

	अगर (reg < 0 || reg >= TOT_REGS) अणु
		v4l2_err(sd, "Invalid register R%d\n", reg);
		वापस -1;
	पूर्ण

	v4l2_dbg(1, debug, sd, "write: %02x %02x\n", reg, val);

	क्रम (i = 0; i < 3; i++)
		अगर (i2c_smbus_ग_लिखो_byte_data(client,
				(reg << 1) | (val >> 8), val & 0xff) == 0)
			वापस 0;
	v4l2_err(sd, "I2C: cannot write %03x to register R%d\n", val, reg);
	वापस -1;
पूर्ण

अटल पूर्णांक wm8739_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा wm8739_state *state = to_state(sd);
	अचिन्हित पूर्णांक work_l, work_r;
	u8 vol_l;	/* +12dB to -34.5dB 1.5dB step (5bit) def:0dB */
	u8 vol_r;	/* +12dB to -34.5dB 1.5dB step (5bit) def:0dB */
	u16 mute;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_VOLUME:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* normalize ( 65535 to 0 -> 31 to 0 (12dB to -34.5dB) ) */
	work_l = (min(65536 - state->balance->val, 32768) * state->volume->val) / 32768;
	work_r = (min(state->balance->val, 32768) * state->volume->val) / 32768;

	vol_l = (दीर्घ)work_l * 31 / 65535;
	vol_r = (दीर्घ)work_r * 31 / 65535;

	/* set audio volume etc. */
	mute = state->mute->val ? 0x80 : 0;

	/* Volume setting: bits 0-4, 0x1f = 12 dB, 0x00 = -34.5 dB
	 * Default setting: 0x17 = 0 dB
	 */
	wm8739_ग_लिखो(sd, R0, (vol_l & 0x1f) | mute);
	wm8739_ग_लिखो(sd, R1, (vol_r & 0x1f) | mute);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक wm8739_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 audiofreq)
अणु
	काष्ठा wm8739_state *state = to_state(sd);

	state->घड़ी_freq = audiofreq;
	/* de-activate */
	wm8739_ग_लिखो(sd, R9, 0x000);
	चयन (audiofreq) अणु
	हाल 44100:
		/* 256fps, fs=44.1k */
		wm8739_ग_लिखो(sd, R8, 0x020);
		अवरोध;
	हाल 48000:
		/* 256fps, fs=48k */
		wm8739_ग_लिखो(sd, R8, 0x000);
		अवरोध;
	हाल 32000:
		/* 256fps, fs=32k */
		wm8739_ग_लिखो(sd, R8, 0x018);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* activate */
	wm8739_ग_लिखो(sd, R9, 0x001);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8739_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा wm8739_state *state = to_state(sd);

	v4l2_info(sd, "Frequency: %u Hz\n", state->घड़ी_freq);
	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops wm8739_ctrl_ops = अणु
	.s_ctrl = wm8739_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops wm8739_core_ops = अणु
	.log_status = wm8739_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops wm8739_audio_ops = अणु
	.s_घड़ी_freq = wm8739_s_घड़ी_freq,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops wm8739_ops = अणु
	.core = &wm8739_core_ops,
	.audio = &wm8739_audio_ops,
पूर्ण;

/* ------------------------------------------------------------------------ */

/* i2c implementation */

अटल पूर्णांक wm8739_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8739_state *state;
	काष्ठा v4l2_subdev *sd;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &wm8739_ops);
	v4l2_ctrl_handler_init(&state->hdl, 2);
	state->volume = v4l2_ctrl_new_std(&state->hdl, &wm8739_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 65535, 65535 / 100, 50736);
	state->mute = v4l2_ctrl_new_std(&state->hdl, &wm8739_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	state->balance = v4l2_ctrl_new_std(&state->hdl, &wm8739_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE, 0, 65535, 65535 / 100, 32768);
	sd->ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		पूर्णांक err = state->hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_cluster(3, &state->volume);

	state->घड़ी_freq = 48000;

	/* Initialize wm8739 */

	/* reset */
	wm8739_ग_लिखो(sd, R15, 0x00);
	/* filter setting, high path, offet clear */
	wm8739_ग_लिखो(sd, R5, 0x000);
	/* ADC, OSC, Power Off mode Disable */
	wm8739_ग_लिखो(sd, R6, 0x000);
	/* Digital Audio पूर्णांकerface क्रमmat:
	   Enable Master mode, 24 bit, MSB first/left justअगरied */
	wm8739_ग_लिखो(sd, R7, 0x049);
	/* sampling control: normal, 256fs, 48KHz sampling rate */
	wm8739_ग_लिखो(sd, R8, 0x000);
	/* activate */
	wm8739_ग_लिखो(sd, R9, 0x001);
	/* set volume/mute */
	v4l2_ctrl_handler_setup(&state->hdl);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8739_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा wm8739_state *state = to_state(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8739_id[] = अणु
	अणु "wm8739", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8739_id);

अटल काष्ठा i2c_driver wm8739_driver = अणु
	.driver = अणु
		.name	= "wm8739",
	पूर्ण,
	.probe		= wm8739_probe,
	.हटाओ		= wm8739_हटाओ,
	.id_table	= wm8739_id,
पूर्ण;

module_i2c_driver(wm8739_driver);
