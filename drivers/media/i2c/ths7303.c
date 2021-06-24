<शैली गुरु>
/*
 * ths7303/53- THS7303/53 Video Amplअगरier driver
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates.
 *
 * Author: Chaithrika U S <chaithrika@ti.com>
 *
 * Contributors:
 *     Hans Verkuil <hans.verkuil@cisco.com>
 *     Lad, Prabhakar <prabhakar.lad@ti.com>
 *     Martin Bugge <marbugge@cisco.com>
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

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <media/i2c/ths7303.h>
#समावेश <media/v4l2-device.h>

#घोषणा THS7303_CHANNEL_1	1
#घोषणा THS7303_CHANNEL_2	2
#घोषणा THS7303_CHANNEL_3	3

काष्ठा ths7303_state अणु
	काष्ठा v4l2_subdev		sd;
	स्थिर काष्ठा ths7303_platक्रमm_data *pdata;
	काष्ठा v4l2_bt_timings		bt;
	पूर्णांक std_id;
	पूर्णांक stream_on;
पूर्ण;

क्रमागत ths7303_filter_mode अणु
	THS7303_FILTER_MODE_480I_576I,
	THS7303_FILTER_MODE_480P_576P,
	THS7303_FILTER_MODE_720P_1080I,
	THS7303_FILTER_MODE_1080P,
	THS7303_FILTER_MODE_DISABLE
पूर्ण;

MODULE_DESCRIPTION("TI THS7303 video amplifier driver");
MODULE_AUTHOR("Chaithrika U S");
MODULE_LICENSE("GPL");

अटल अंतरभूत काष्ठा ths7303_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ths7303_state, sd);
पूर्ण

अटल पूर्णांक ths7303_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक ths7303_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	वापस ret;
पूर्ण

/* following function is used to set ths7303 */
अटल पूर्णांक ths7303_setval(काष्ठा v4l2_subdev *sd,
			  क्रमागत ths7303_filter_mode mode)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ths7303_state *state = to_state(sd);
	स्थिर काष्ठा ths7303_platक्रमm_data *pdata = state->pdata;
	u8 val, sel = 0;
	पूर्णांक err, disable = 0;

	अगर (!client)
		वापस -EINVAL;

	चयन (mode) अणु
	हाल THS7303_FILTER_MODE_1080P:
		sel = 0x3;	/*1080p and SXGA/UXGA */
		अवरोध;
	हाल THS7303_FILTER_MODE_720P_1080I:
		sel = 0x2;	/*720p, 1080i and SVGA/XGA */
		अवरोध;
	हाल THS7303_FILTER_MODE_480P_576P:
		sel = 0x1;	/* EDTV 480p/576p and VGA */
		अवरोध;
	हाल THS7303_FILTER_MODE_480I_576I:
		sel = 0x0;	/* SDTV, S-Video, 480i/576i */
		अवरोध;
	शेष:
		/* disable all channels */
		disable = 1;
	पूर्ण

	val = (sel << 6) | (sel << 3);
	अगर (!disable)
		val |= (pdata->ch_1 & 0x27);
	err = ths7303_ग_लिखो(sd, THS7303_CHANNEL_1, val);
	अगर (err)
		जाओ out;

	val = (sel << 6) | (sel << 3);
	अगर (!disable)
		val |= (pdata->ch_2 & 0x27);
	err = ths7303_ग_लिखो(sd, THS7303_CHANNEL_2, val);
	अगर (err)
		जाओ out;

	val = (sel << 6) | (sel << 3);
	अगर (!disable)
		val |= (pdata->ch_3 & 0x27);
	err = ths7303_ग_लिखो(sd, THS7303_CHANNEL_3, val);
	अगर (err)
		जाओ out;

	वापस 0;
out:
	pr_info("write byte data failed\n");
	वापस err;
पूर्ण

अटल पूर्णांक ths7303_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा ths7303_state *state = to_state(sd);

	अगर (norm & (V4L2_STD_ALL & ~V4L2_STD_SECAM)) अणु
		state->std_id = 1;
		state->bt.pixelघड़ी = 0;
		वापस ths7303_setval(sd, THS7303_FILTER_MODE_480I_576I);
	पूर्ण

	वापस ths7303_setval(sd, THS7303_FILTER_MODE_DISABLE);
पूर्ण

अटल पूर्णांक ths7303_config(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ths7303_state *state = to_state(sd);
	पूर्णांक res;

	अगर (!state->stream_on) अणु
		ths7303_ग_लिखो(sd, THS7303_CHANNEL_1,
			      (ths7303_पढ़ो(sd, THS7303_CHANNEL_1) & 0xf8) |
			      0x00);
		ths7303_ग_लिखो(sd, THS7303_CHANNEL_2,
			      (ths7303_पढ़ो(sd, THS7303_CHANNEL_2) & 0xf8) |
			      0x00);
		ths7303_ग_लिखो(sd, THS7303_CHANNEL_3,
			      (ths7303_पढ़ो(sd, THS7303_CHANNEL_3) & 0xf8) |
			      0x00);
		वापस 0;
	पूर्ण

	अगर (state->bt.pixelघड़ी > 120000000)
		res = ths7303_setval(sd, THS7303_FILTER_MODE_1080P);
	अन्यथा अगर (state->bt.pixelघड़ी > 70000000)
		res = ths7303_setval(sd, THS7303_FILTER_MODE_720P_1080I);
	अन्यथा अगर (state->bt.pixelघड़ी > 20000000)
		res = ths7303_setval(sd, THS7303_FILTER_MODE_480P_576P);
	अन्यथा अगर (state->std_id)
		res = ths7303_setval(sd, THS7303_FILTER_MODE_480I_576I);
	अन्यथा
		/* disable all channels */
		res = ths7303_setval(sd, THS7303_FILTER_MODE_DISABLE);

	वापस res;

पूर्ण

अटल पूर्णांक ths7303_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ths7303_state *state = to_state(sd);

	state->stream_on = enable;

	वापस ths7303_config(sd);
पूर्ण

/* क्रम setting filter क्रम HD output */
अटल पूर्णांक ths7303_s_dv_timings(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_dv_timings *dv_timings)
अणु
	काष्ठा ths7303_state *state = to_state(sd);

	अगर (!dv_timings || dv_timings->type != V4L2_DV_BT_656_1120)
		वापस -EINVAL;

	state->bt = dv_timings->bt;
	state->std_id = 0;

	वापस ths7303_config(sd);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ths7303_video_ops = अणु
	.s_stream	= ths7303_s_stream,
	.s_std_output	= ths7303_s_std_output,
	.s_dv_timings   = ths7303_s_dv_timings,
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG

अटल पूर्णांक ths7303_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->size = 1;
	reg->val = ths7303_पढ़ो(sd, reg->reg);
	वापस 0;
पूर्ण

अटल पूर्णांक ths7303_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	ths7303_ग_लिखो(sd, reg->reg, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर stc_lpf_sel_txt[4] = अणु
	"500-kHz Filter",
	"2.5-MHz Filter",
	"5-MHz Filter",
	"5-MHz Filter",
पूर्ण;

अटल स्थिर अक्षर * स्थिर in_mux_sel_txt[2] = अणु
	"Input A Select",
	"Input B Select",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lpf_freq_sel_txt[4] = अणु
	"9-MHz LPF",
	"16-MHz LPF",
	"35-MHz LPF",
	"Bypass LPF",
पूर्ण;

अटल स्थिर अक्षर * स्थिर in_bias_sel_dis_cont_txt[8] = अणु
	"Disable Channel",
	"Mute Function - No Output",
	"DC Bias Select",
	"DC Bias + 250 mV Offset Select",
	"AC Bias Select",
	"Sync Tip Clamp with low bias",
	"Sync Tip Clamp with mid bias",
	"Sync Tip Clamp with high bias",
पूर्ण;

अटल व्योम ths7303_log_channel_status(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	u8 val = ths7303_पढ़ो(sd, reg);

	अगर ((val & 0x7) == 0) अणु
		v4l2_info(sd, "Channel %d Off\n", reg);
		वापस;
	पूर्ण

	v4l2_info(sd, "Channel %d On\n", reg);
	v4l2_info(sd, "  value 0x%x\n", val);
	v4l2_info(sd, "  %s\n", stc_lpf_sel_txt[(val >> 6) & 0x3]);
	v4l2_info(sd, "  %s\n", in_mux_sel_txt[(val >> 5) & 0x1]);
	v4l2_info(sd, "  %s\n", lpf_freq_sel_txt[(val >> 3) & 0x3]);
	v4l2_info(sd, "  %s\n", in_bias_sel_dis_cont_txt[(val >> 0) & 0x7]);
पूर्ण

अटल पूर्णांक ths7303_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ths7303_state *state = to_state(sd);

	v4l2_info(sd, "stream %s\n", state->stream_on ? "On" : "Off");

	अगर (state->bt.pixelघड़ी) अणु
		काष्ठा v4l2_bt_timings *bt = &state->bt;
		u32 frame_width, frame_height;

		frame_width = V4L2_DV_BT_FRAME_WIDTH(bt);
		frame_height = V4L2_DV_BT_FRAME_HEIGHT(bt);
		v4l2_info(sd,
			  "timings: %dx%d%s%d (%dx%d). Pix freq. = %d Hz. Polarities = 0x%x\n",
			  bt->width, bt->height, bt->पूर्णांकerlaced ? "i" : "p",
			  (frame_height * frame_width) > 0 ?
			  (पूर्णांक)bt->pixelघड़ी /
			  (frame_height * frame_width) : 0,
			  frame_width, frame_height,
			  (पूर्णांक)bt->pixelघड़ी, bt->polarities);
	पूर्ण अन्यथा अणु
		v4l2_info(sd, "no timings set\n");
	पूर्ण

	ths7303_log_channel_status(sd, THS7303_CHANNEL_1);
	ths7303_log_channel_status(sd, THS7303_CHANNEL_2);
	ths7303_log_channel_status(sd, THS7303_CHANNEL_3);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ths7303_core_ops = अणु
	.log_status = ths7303_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = ths7303_g_रेजिस्टर,
	.s_रेजिस्टर = ths7303_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ths7303_ops = अणु
	.core	= &ths7303_core_ops,
	.video	= &ths7303_video_ops,
पूर्ण;

अटल पूर्णांक ths7303_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ths7303_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा ths7303_state *state;
	काष्ठा v4l2_subdev *sd;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(काष्ठा ths7303_state),
			     GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->pdata = pdata;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &ths7303_ops);

	/* set to शेष 480I_576I filter mode */
	अगर (ths7303_setval(sd, THS7303_FILTER_MODE_480I_576I) < 0) अणु
		v4l_err(client, "Setting to 480I_576I filter mode failed!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ths7303_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ths7303_id[] = अणु
	अणु"ths7303", 0पूर्ण,
	अणु"ths7353", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ths7303_id);

अटल काष्ठा i2c_driver ths7303_driver = अणु
	.driver = अणु
		.name	= "ths73x3",
	पूर्ण,
	.probe		= ths7303_probe,
	.हटाओ		= ths7303_हटाओ,
	.id_table	= ths7303_id,
पूर्ण;

module_i2c_driver(ths7303_driver);
