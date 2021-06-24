<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  bt819 - BT819A VideoStream Decoder (Rockwell Part)
 *
 * Copyright (C) 1999 Mike Bernson <mike@mlb.org>
 * Copyright (C) 1998 Dave Perks <dperks@ibm.net>
 *
 * Modअगरications क्रम LML33/DC10plus unअगरied driver
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 *
 * Changes by Ronald Bultje <rbultje@ronald.bitfreak.net>
 *    - moved over to linux>=2.4.x i2c protocol (9/9/2002)
 *
 * This code was modअगरy/ported from the saa7111 driver written
 * by Dave Perks.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/i2c/bt819.h>

MODULE_DESCRIPTION("Brooktree-819 video decoder driver");
MODULE_AUTHOR("Mike Bernson & Dave Perks");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");


/* ----------------------------------------------------------------------- */

काष्ठा bt819 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	अचिन्हित अक्षर reg[32];

	v4l2_std_id norm;
	पूर्णांक input;
	पूर्णांक enable;
पूर्ण;

अटल अंतरभूत काष्ठा bt819 *to_bt819(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा bt819, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा bt819, hdl)->sd;
पूर्ण

काष्ठा timing अणु
	पूर्णांक hactive;
	पूर्णांक hdelay;
	पूर्णांक vactive;
	पूर्णांक vdelay;
	पूर्णांक hscale;
	पूर्णांक vscale;
पूर्ण;

/* क्रम values, see the bt819 datasheet */
अटल काष्ठा timing timing_data[] = अणु
	अणु864 - 24, 20, 625 - 2, 1, 0x0504, 0x0000पूर्ण,
	अणु858 - 24, 20, 525 - 2, 1, 0x00f8, 0x0000पूर्ण,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक bt819_ग_लिखो(काष्ठा bt819 *decoder, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&decoder->sd);

	decoder->reg[reg] = value;
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक bt819_setbit(काष्ठा bt819 *decoder, u8 reg, u8 bit, u8 value)
अणु
	वापस bt819_ग_लिखो(decoder, reg,
		(decoder->reg[reg] & ~(1 << bit)) | (value ? (1 << bit) : 0));
पूर्ण

अटल पूर्णांक bt819_ग_लिखो_block(काष्ठा bt819 *decoder, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&decoder->sd);
	पूर्णांक ret = -1;
	u8 reg;

	/* the bt819 has an स्वतःincrement function, use it अगर
	 * the adapter understands raw I2C */
	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		/* करो raw I2C, not smbus compatible */
		u8 block_data[32];
		पूर्णांक block_len;

		जबतक (len >= 2) अणु
			block_len = 0;
			block_data[block_len++] = reg = data[0];
			करो अणु
				block_data[block_len++] =
				    decoder->reg[reg++] = data[1];
				len -= 2;
				data += 2;
			पूर्ण जबतक (len >= 2 && data[0] == reg && block_len < 32);
			ret = i2c_master_send(client, block_data, block_len);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* करो some slow I2C emulation kind of thing */
		जबतक (len >= 2) अणु
			reg = *data++;
			ret = bt819_ग_लिखो(decoder, reg, *data++);
			अगर (ret < 0)
				अवरोध;
			len -= 2;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक bt819_पढ़ो(काष्ठा bt819 *decoder, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&decoder->sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक bt819_init(काष्ठा v4l2_subdev *sd)
अणु
	अटल अचिन्हित अक्षर init[] = अणु
		/*0x1f, 0x00,*/     /* Reset */
		0x01, 0x59,	/* 0x01 input क्रमmat */
		0x02, 0x00,	/* 0x02 temporal decimation */
		0x03, 0x12,	/* 0x03 Cropping msb */
		0x04, 0x16,	/* 0x04 Vertical Delay, lsb */
		0x05, 0xe0,	/* 0x05 Vertical Active lsb */
		0x06, 0x80,	/* 0x06 Horizontal Delay lsb */
		0x07, 0xd0,	/* 0x07 Horizontal Active lsb */
		0x08, 0x00,	/* 0x08 Horizontal Scaling msb */
		0x09, 0xf8,	/* 0x09 Horizontal Scaling lsb */
		0x0a, 0x00,	/* 0x0a Brightness control */
		0x0b, 0x30,	/* 0x0b Miscellaneous control */
		0x0c, 0xd8,	/* 0x0c Luma Gain lsb */
		0x0d, 0xfe,	/* 0x0d Chroma Gain (U) lsb */
		0x0e, 0xb4,	/* 0x0e Chroma Gain (V) msb */
		0x0f, 0x00,	/* 0x0f Hue control */
		0x12, 0x04,	/* 0x12 Output Format */
		0x13, 0x20,	/* 0x13 Vertical Scaling msb 0x00
					   chroma comb OFF, line drop scaling, पूर्णांकerlace scaling
					   BUG? Why करोes turning the chroma comb on screw up color?
					   Bug in the bt819 stepping on my board?
					*/
		0x14, 0x00,	/* 0x14 Vertical Scaling lsb */
		0x16, 0x07,	/* 0x16 Video Timing Polarity
					   ACTIVE=active low
					   FIELD: high=odd,
					   vreset=active high,
					   hreset=active high */
		0x18, 0x68,	/* 0x18 AGC Delay */
		0x19, 0x5d,	/* 0x19 Burst Gate Delay */
		0x1a, 0x80,	/* 0x1a ADC Interface */
	पूर्ण;

	काष्ठा bt819 *decoder = to_bt819(sd);
	काष्ठा timing *timing = &timing_data[(decoder->norm & V4L2_STD_525_60) ? 1 : 0];

	init[0x03 * 2 - 1] =
	    (((timing->vdelay >> 8) & 0x03) << 6) |
	    (((timing->vactive >> 8) & 0x03) << 4) |
	    (((timing->hdelay >> 8) & 0x03) << 2) |
	    ((timing->hactive >> 8) & 0x03);
	init[0x04 * 2 - 1] = timing->vdelay & 0xff;
	init[0x05 * 2 - 1] = timing->vactive & 0xff;
	init[0x06 * 2 - 1] = timing->hdelay & 0xff;
	init[0x07 * 2 - 1] = timing->hactive & 0xff;
	init[0x08 * 2 - 1] = timing->hscale >> 8;
	init[0x09 * 2 - 1] = timing->hscale & 0xff;
	/* 0x15 in array is address 0x19 */
	init[0x15 * 2 - 1] = (decoder->norm & V4L2_STD_625_50) ? 115 : 93;	/* Chroma burst delay */
	/* reset */
	bt819_ग_लिखो(decoder, 0x1f, 0x00);
	mdelay(1);

	/* init */
	वापस bt819_ग_लिखो_block(decoder, init, माप(init));
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक bt819_status(काष्ठा v4l2_subdev *sd, u32 *pstatus, v4l2_std_id *pstd)
अणु
	काष्ठा bt819 *decoder = to_bt819(sd);
	पूर्णांक status = bt819_पढ़ो(decoder, 0x00);
	पूर्णांक res = V4L2_IN_ST_NO_SIGNAL;
	v4l2_std_id std = pstd ? *pstd : V4L2_STD_ALL;

	अगर ((status & 0x80))
		res = 0;
	अन्यथा
		std = V4L2_STD_UNKNOWN;

	अगर ((status & 0x10))
		std &= V4L2_STD_PAL;
	अन्यथा
		std &= V4L2_STD_NTSC;
	अगर (pstd)
		*pstd = std;
	अगर (pstatus)
		*pstatus = res;

	v4l2_dbg(1, debug, sd, "get status %x\n", status);
	वापस 0;
पूर्ण

अटल पूर्णांक bt819_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	वापस bt819_status(sd, शून्य, std);
पूर्ण

अटल पूर्णांक bt819_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	वापस bt819_status(sd, status, शून्य);
पूर्ण

अटल पूर्णांक bt819_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा bt819 *decoder = to_bt819(sd);
	काष्ठा timing *timing = शून्य;

	v4l2_dbg(1, debug, sd, "set norm %llx\n", (अचिन्हित दीर्घ दीर्घ)std);

	अगर (sd->v4l2_dev == शून्य || sd->v4l2_dev->notअगरy == शून्य)
		v4l2_err(sd, "no notify found!\n");

	अगर (std & V4L2_STD_NTSC) अणु
		v4l2_subdev_notअगरy(sd, BT819_FIFO_RESET_LOW, शून्य);
		bt819_setbit(decoder, 0x01, 0, 1);
		bt819_setbit(decoder, 0x01, 1, 0);
		bt819_setbit(decoder, 0x01, 5, 0);
		bt819_ग_लिखो(decoder, 0x18, 0x68);
		bt819_ग_लिखो(decoder, 0x19, 0x5d);
		/* bt819_setbit(decoder, 0x1a,  5, 1); */
		timing = &timing_data[1];
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
		v4l2_subdev_notअगरy(sd, BT819_FIFO_RESET_LOW, शून्य);
		bt819_setbit(decoder, 0x01, 0, 1);
		bt819_setbit(decoder, 0x01, 1, 1);
		bt819_setbit(decoder, 0x01, 5, 1);
		bt819_ग_लिखो(decoder, 0x18, 0x7f);
		bt819_ग_लिखो(decoder, 0x19, 0x72);
		/* bt819_setbit(decoder, 0x1a,  5, 0); */
		timing = &timing_data[0];
	पूर्ण अन्यथा अणु
		v4l2_dbg(1, debug, sd, "unsupported norm %llx\n",
				(अचिन्हित दीर्घ दीर्घ)std);
		वापस -EINVAL;
	पूर्ण
	bt819_ग_लिखो(decoder, 0x03,
			(((timing->vdelay >> 8) & 0x03) << 6) |
			(((timing->vactive >> 8) & 0x03) << 4) |
			(((timing->hdelay >> 8) & 0x03) << 2) |
			((timing->hactive >> 8) & 0x03));
	bt819_ग_लिखो(decoder, 0x04, timing->vdelay & 0xff);
	bt819_ग_लिखो(decoder, 0x05, timing->vactive & 0xff);
	bt819_ग_लिखो(decoder, 0x06, timing->hdelay & 0xff);
	bt819_ग_लिखो(decoder, 0x07, timing->hactive & 0xff);
	bt819_ग_लिखो(decoder, 0x08, (timing->hscale >> 8) & 0xff);
	bt819_ग_लिखो(decoder, 0x09, timing->hscale & 0xff);
	decoder->norm = std;
	v4l2_subdev_notअगरy(sd, BT819_FIFO_RESET_HIGH, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक bt819_s_routing(काष्ठा v4l2_subdev *sd,
			   u32 input, u32 output, u32 config)
अणु
	काष्ठा bt819 *decoder = to_bt819(sd);

	v4l2_dbg(1, debug, sd, "set input %x\n", input);

	अगर (input > 7)
		वापस -EINVAL;

	अगर (sd->v4l2_dev == शून्य || sd->v4l2_dev->notअगरy == शून्य)
		v4l2_err(sd, "no notify found!\n");

	अगर (decoder->input != input) अणु
		v4l2_subdev_notअगरy(sd, BT819_FIFO_RESET_LOW, शून्य);
		decoder->input = input;
		/* select mode */
		अगर (decoder->input == 0) अणु
			bt819_setbit(decoder, 0x0b, 6, 0);
			bt819_setbit(decoder, 0x1a, 1, 1);
		पूर्ण अन्यथा अणु
			bt819_setbit(decoder, 0x0b, 6, 1);
			bt819_setbit(decoder, 0x1a, 1, 0);
		पूर्ण
		v4l2_subdev_notअगरy(sd, BT819_FIFO_RESET_HIGH, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bt819_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा bt819 *decoder = to_bt819(sd);

	v4l2_dbg(1, debug, sd, "enable output %x\n", enable);

	अगर (decoder->enable != enable) अणु
		decoder->enable = enable;
		bt819_setbit(decoder, 0x16, 7, !enable);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bt819_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा bt819 *decoder = to_bt819(sd);
	पूर्णांक temp;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		bt819_ग_लिखो(decoder, 0x0a, ctrl->val);
		अवरोध;

	हाल V4L2_CID_CONTRAST:
		bt819_ग_लिखो(decoder, 0x0c, ctrl->val & 0xff);
		bt819_setbit(decoder, 0x0b, 2, ((ctrl->val >> 8) & 0x01));
		अवरोध;

	हाल V4L2_CID_SATURATION:
		bt819_ग_लिखो(decoder, 0x0d, (ctrl->val >> 7) & 0xff);
		bt819_setbit(decoder, 0x0b, 1, ((ctrl->val >> 15) & 0x01));

		/* Ratio between U gain and V gain must stay the same as
		   the ratio between the शेष U and V gain values. */
		temp = (ctrl->val * 180) / 254;
		bt819_ग_लिखो(decoder, 0x0e, (temp >> 7) & 0xff);
		bt819_setbit(decoder, 0x0b, 0, (temp >> 15) & 0x01);
		अवरोध;

	हाल V4L2_CID_HUE:
		bt819_ग_लिखो(decoder, 0x0f, ctrl->val);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops bt819_ctrl_ops = अणु
	.s_ctrl = bt819_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops bt819_video_ops = अणु
	.s_std = bt819_s_std,
	.s_routing = bt819_s_routing,
	.s_stream = bt819_s_stream,
	.querystd = bt819_querystd,
	.g_input_status = bt819_g_input_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops bt819_ops = अणु
	.video = &bt819_video_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक bt819_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक i, ver;
	काष्ठा bt819 *decoder;
	काष्ठा v4l2_subdev *sd;
	स्थिर अक्षर *name;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	decoder = devm_kzalloc(&client->dev, माप(*decoder), GFP_KERNEL);
	अगर (decoder == शून्य)
		वापस -ENOMEM;
	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &bt819_ops);

	ver = bt819_पढ़ो(decoder, 0x17);
	चयन (ver & 0xf0) अणु
	हाल 0x70:
		name = "bt819a";
		अवरोध;
	हाल 0x60:
		name = "bt817a";
		अवरोध;
	हाल 0x20:
		name = "bt815a";
		अवरोध;
	शेष:
		v4l2_dbg(1, debug, sd,
			"unknown chip version 0x%02x\n", ver);
		वापस -ENODEV;
	पूर्ण

	v4l_info(client, "%s found @ 0x%x (%s)\n", name,
			client->addr << 1, client->adapter->name);

	decoder->norm = V4L2_STD_NTSC;
	decoder->input = 0;
	decoder->enable = 1;

	i = bt819_init(sd);
	अगर (i < 0)
		v4l2_dbg(1, debug, sd, "init status %d\n", i);

	v4l2_ctrl_handler_init(&decoder->hdl, 4);
	v4l2_ctrl_new_std(&decoder->hdl, &bt819_ctrl_ops,
			V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(&decoder->hdl, &bt819_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 511, 1, 0xd8);
	v4l2_ctrl_new_std(&decoder->hdl, &bt819_ctrl_ops,
			V4L2_CID_SATURATION, 0, 511, 1, 0xfe);
	v4l2_ctrl_new_std(&decoder->hdl, &bt819_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	sd->ctrl_handler = &decoder->hdl;
	अगर (decoder->hdl.error) अणु
		पूर्णांक err = decoder->hdl.error;

		v4l2_ctrl_handler_मुक्त(&decoder->hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_handler_setup(&decoder->hdl);
	वापस 0;
पूर्ण

अटल पूर्णांक bt819_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा bt819 *decoder = to_bt819(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&decoder->hdl);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id bt819_id[] = अणु
	अणु "bt819a", 0 पूर्ण,
	अणु "bt817a", 0 पूर्ण,
	अणु "bt815a", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bt819_id);

अटल काष्ठा i2c_driver bt819_driver = अणु
	.driver = अणु
		.name	= "bt819",
	पूर्ण,
	.probe		= bt819_probe,
	.हटाओ		= bt819_हटाओ,
	.id_table	= bt819_id,
पूर्ण;

module_i2c_driver(bt819_driver);
