<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * saa7110 - Philips SAA7110(A) video decoder driver
 *
 * Copyright (C) 1998 Pauline Middelink <middelin@polyware.nl>
 *
 * Copyright (C) 1999 Wolfgang Scherr <scherr@net4you.net>
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 *    - some corrections क्रम Pinnacle Systems Inc. DC10plus card.
 *
 * Changes by Ronald Bultje <rbultje@ronald.bitfreak.net>
 *    - moved over to linux>=2.4.x i2c protocol (1/1/2003)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

MODULE_DESCRIPTION("Philips SAA7110 video decoder driver");
MODULE_AUTHOR("Pauline Middelink");
MODULE_LICENSE("GPL");


अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

#घोषणा SAA7110_MAX_INPUT	9	/* 6 CVBS, 3 SVHS */
#घोषणा SAA7110_MAX_OUTPUT	1	/* 1 YUV */

#घोषणा SAA7110_NR_REG		0x35

काष्ठा saa7110 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	u8 reg[SAA7110_NR_REG];

	v4l2_std_id norm;
	पूर्णांक input;
	पूर्णांक enable;

	रुको_queue_head_t wq;
पूर्ण;

अटल अंतरभूत काष्ठा saa7110 *to_saa7110(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa7110, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा saa7110, hdl)->sd;
पूर्ण

/* ----------------------------------------------------------------------- */
/* I2C support functions						   */
/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7110_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा saa7110 *decoder = to_saa7110(sd);

	decoder->reg[reg] = value;
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल पूर्णांक saa7110_ग_लिखो_block(काष्ठा v4l2_subdev *sd, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा saa7110 *decoder = to_saa7110(sd);
	पूर्णांक ret = -1;
	u8 reg = *data;		/* first रेजिस्टर to ग_लिखो to */

	/* Sanity check */
	अगर (reg + (len - 1) > SAA7110_NR_REG)
		वापस ret;

	/* the saa7110 has an स्वतःincrement function, use it अगर
	 * the adapter understands raw I2C */
	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		ret = i2c_master_send(client, data, len);

		/* Cache the written data */
		स_नकल(decoder->reg + reg, data + 1, len - 1);
	पूर्ण अन्यथा अणु
		क्रम (++data, --len; len; len--) अणु
			ret = saa7110_ग_लिखो(sd, reg++, *data++);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक saa7110_पढ़ो(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte(client);
पूर्ण

/* ----------------------------------------------------------------------- */
/* SAA7110 functions							   */
/* ----------------------------------------------------------------------- */

#घोषणा FRESP_06H_COMPST 0x03	/*0x13*/
#घोषणा FRESP_06H_SVIDEO 0x83	/*0xC0*/


अटल पूर्णांक saa7110_selmux(काष्ठा v4l2_subdev *sd, पूर्णांक chan)
अणु
	अटल स्थिर अचिन्हित अक्षर modes[9][8] = अणु
		/* mode 0 */
		अणुFRESP_06H_COMPST, 0xD9, 0x17, 0x40, 0x03,
			      0x44, 0x75, 0x16पूर्ण,
		/* mode 1 */
		अणुFRESP_06H_COMPST, 0xD8, 0x17, 0x40, 0x03,
			      0x44, 0x75, 0x16पूर्ण,
		/* mode 2 */
		अणुFRESP_06H_COMPST, 0xBA, 0x07, 0x91, 0x03,
			      0x60, 0xB5, 0x05पूर्ण,
		/* mode 3 */
		अणुFRESP_06H_COMPST, 0xB8, 0x07, 0x91, 0x03,
			      0x60, 0xB5, 0x05पूर्ण,
		/* mode 4 */
		अणुFRESP_06H_COMPST, 0x7C, 0x07, 0xD2, 0x83,
			      0x60, 0xB5, 0x03पूर्ण,
		/* mode 5 */
		अणुFRESP_06H_COMPST, 0x78, 0x07, 0xD2, 0x83,
			      0x60, 0xB5, 0x03पूर्ण,
		/* mode 6 */
		अणुFRESP_06H_SVIDEO, 0x59, 0x17, 0x42, 0xA3,
			      0x44, 0x75, 0x12पूर्ण,
		/* mode 7 */
		अणुFRESP_06H_SVIDEO, 0x9A, 0x17, 0xB1, 0x13,
			      0x60, 0xB5, 0x14पूर्ण,
		/* mode 8 */
		अणुFRESP_06H_SVIDEO, 0x3C, 0x27, 0xC1, 0x23,
			      0x44, 0x75, 0x21पूर्ण
	पूर्ण;
	काष्ठा saa7110 *decoder = to_saa7110(sd);
	स्थिर अचिन्हित अक्षर *ptr = modes[chan];

	saa7110_ग_लिखो(sd, 0x06, ptr[0]);	/* Luminance control    */
	saa7110_ग_लिखो(sd, 0x20, ptr[1]);	/* Analog Control #1    */
	saa7110_ग_लिखो(sd, 0x21, ptr[2]);	/* Analog Control #2    */
	saa7110_ग_लिखो(sd, 0x22, ptr[3]);	/* Mixer Control #1     */
	saa7110_ग_लिखो(sd, 0x2C, ptr[4]);	/* Mixer Control #2     */
	saa7110_ग_लिखो(sd, 0x30, ptr[5]);	/* ADCs gain control    */
	saa7110_ग_लिखो(sd, 0x31, ptr[6]);	/* Mixer Control #3     */
	saa7110_ग_लिखो(sd, 0x21, ptr[7]);	/* Analog Control #2    */
	decoder->input = chan;

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर initseq[1 + SAA7110_NR_REG] = अणु
	0, 0x4C, 0x3C, 0x0D, 0xEF, 0xBD, 0xF2, 0x03, 0x00,
	/* 0x08 */ 0xF8, 0xF8, 0x60, 0x60, 0x00, 0x86, 0x18, 0x90,
	/* 0x10 */ 0x00, 0x59, 0x40, 0x46, 0x42, 0x1A, 0xFF, 0xDA,
	/* 0x18 */ 0xF2, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* 0x20 */ 0xD9, 0x16, 0x40, 0x41, 0x80, 0x41, 0x80, 0x4F,
	/* 0x28 */ 0xFE, 0x01, 0xCF, 0x0F, 0x03, 0x01, 0x03, 0x0C,
	/* 0x30 */ 0x44, 0x71, 0x02, 0x8C, 0x02
पूर्ण;

अटल v4l2_std_id determine_norm(काष्ठा v4l2_subdev *sd)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा saa7110 *decoder = to_saa7110(sd);
	पूर्णांक status;

	/* mode changed, start स्वतःmatic detection */
	saa7110_ग_लिखो_block(sd, initseq, माप(initseq));
	saa7110_selmux(sd, decoder->input);
	prepare_to_रुको(&decoder->wq, &रुको, TASK_UNINTERRUPTIBLE);
	schedule_समयout(msecs_to_jअगरfies(250));
	finish_रुको(&decoder->wq, &रुको);
	status = saa7110_पढ़ो(sd);
	अगर (status & 0x40) अणु
		v4l2_dbg(1, debug, sd, "status=0x%02x (no signal)\n", status);
		वापस V4L2_STD_UNKNOWN;
	पूर्ण
	अगर ((status & 3) == 0) अणु
		saa7110_ग_लिखो(sd, 0x06, 0x83);
		अगर (status & 0x20) अणु
			v4l2_dbg(1, debug, sd, "status=0x%02x (NTSC/no color)\n", status);
			/*saa7110_ग_लिखो(sd,0x2E,0x81);*/
			वापस V4L2_STD_NTSC;
		पूर्ण
		v4l2_dbg(1, debug, sd, "status=0x%02x (PAL/no color)\n", status);
		/*saa7110_ग_लिखो(sd,0x2E,0x9A);*/
		वापस V4L2_STD_PAL;
	पूर्ण
	/*saa7110_ग_लिखो(sd,0x06,0x03);*/
	अगर (status & 0x20) अणु	/* 60Hz */
		v4l2_dbg(1, debug, sd, "status=0x%02x (NTSC)\n", status);
		saa7110_ग_लिखो(sd, 0x0D, 0x86);
		saa7110_ग_लिखो(sd, 0x0F, 0x50);
		saa7110_ग_लिखो(sd, 0x11, 0x2C);
		/*saa7110_ग_लिखो(sd,0x2E,0x81);*/
		वापस V4L2_STD_NTSC;
	पूर्ण

	/* 50Hz -> PAL/SECAM */
	saa7110_ग_लिखो(sd, 0x0D, 0x86);
	saa7110_ग_लिखो(sd, 0x0F, 0x10);
	saa7110_ग_लिखो(sd, 0x11, 0x59);
	/*saa7110_ग_लिखो(sd,0x2E,0x9A);*/

	prepare_to_रुको(&decoder->wq, &रुको, TASK_UNINTERRUPTIBLE);
	schedule_समयout(msecs_to_jअगरfies(250));
	finish_रुको(&decoder->wq, &रुको);

	status = saa7110_पढ़ो(sd);
	अगर ((status & 0x03) == 0x01) अणु
		v4l2_dbg(1, debug, sd, "status=0x%02x (SECAM)\n", status);
		saa7110_ग_लिखो(sd, 0x0D, 0x87);
		वापस V4L2_STD_SECAM;
	पूर्ण
	v4l2_dbg(1, debug, sd, "status=0x%02x (PAL)\n", status);
	वापस V4L2_STD_PAL;
पूर्ण

अटल पूर्णांक saa7110_g_input_status(काष्ठा v4l2_subdev *sd, u32 *pstatus)
अणु
	काष्ठा saa7110 *decoder = to_saa7110(sd);
	पूर्णांक res = V4L2_IN_ST_NO_SIGNAL;
	पूर्णांक status = saa7110_पढ़ो(sd);

	v4l2_dbg(1, debug, sd, "status=0x%02x norm=%llx\n",
		       status, (अचिन्हित दीर्घ दीर्घ)decoder->norm);
	अगर (!(status & 0x40))
		res = 0;
	अगर (!(status & 0x03))
		res |= V4L2_IN_ST_NO_COLOR;

	*pstatus = res;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7110_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	*std &= determine_norm(sd);
	वापस 0;
पूर्ण

अटल पूर्णांक saa7110_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa7110 *decoder = to_saa7110(sd);

	अगर (decoder->norm != std) अणु
		decoder->norm = std;
		/*saa7110_ग_लिखो(sd, 0x06, 0x03);*/
		अगर (std & V4L2_STD_NTSC) अणु
			saa7110_ग_लिखो(sd, 0x0D, 0x86);
			saa7110_ग_लिखो(sd, 0x0F, 0x50);
			saa7110_ग_लिखो(sd, 0x11, 0x2C);
			/*saa7110_ग_लिखो(sd, 0x2E, 0x81);*/
			v4l2_dbg(1, debug, sd, "switched to NTSC\n");
		पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
			saa7110_ग_लिखो(sd, 0x0D, 0x86);
			saa7110_ग_लिखो(sd, 0x0F, 0x10);
			saa7110_ग_लिखो(sd, 0x11, 0x59);
			/*saa7110_ग_लिखो(sd, 0x2E, 0x9A);*/
			v4l2_dbg(1, debug, sd, "switched to PAL\n");
		पूर्ण अन्यथा अगर (std & V4L2_STD_SECAM) अणु
			saa7110_ग_लिखो(sd, 0x0D, 0x87);
			saa7110_ग_लिखो(sd, 0x0F, 0x10);
			saa7110_ग_लिखो(sd, 0x11, 0x59);
			/*saa7110_ग_लिखो(sd, 0x2E, 0x9A);*/
			v4l2_dbg(1, debug, sd, "switched to SECAM\n");
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7110_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	काष्ठा saa7110 *decoder = to_saa7110(sd);

	अगर (input >= SAA7110_MAX_INPUT) अणु
		v4l2_dbg(1, debug, sd, "input=%d not available\n", input);
		वापस -EINVAL;
	पूर्ण
	अगर (decoder->input != input) अणु
		saa7110_selmux(sd, input);
		v4l2_dbg(1, debug, sd, "switched to input=%d\n", input);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7110_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा saa7110 *decoder = to_saa7110(sd);

	अगर (decoder->enable != enable) अणु
		decoder->enable = enable;
		saa7110_ग_लिखो(sd, 0x0E, enable ? 0x18 : 0x80);
		v4l2_dbg(1, debug, sd, "YUV %s\n", enable ? "on" : "off");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7110_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		saa7110_ग_लिखो(sd, 0x19, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		saa7110_ग_लिखो(sd, 0x13, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		saa7110_ग_लिखो(sd, 0x12, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		saa7110_ग_लिखो(sd, 0x07, ctrl->val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops saa7110_ctrl_ops = अणु
	.s_ctrl = saa7110_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops saa7110_video_ops = अणु
	.s_std = saa7110_s_std,
	.s_routing = saa7110_s_routing,
	.s_stream = saa7110_s_stream,
	.querystd = saa7110_querystd,
	.g_input_status = saa7110_g_input_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa7110_ops = अणु
	.video = &saa7110_video_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7110_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा saa7110 *decoder;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक rv;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter,
		I2C_FUNC_SMBUS_READ_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	decoder = devm_kzalloc(&client->dev, माप(*decoder), GFP_KERNEL);
	अगर (!decoder)
		वापस -ENOMEM;
	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &saa7110_ops);
	decoder->norm = V4L2_STD_PAL;
	decoder->input = 0;
	decoder->enable = 1;
	v4l2_ctrl_handler_init(&decoder->hdl, 2);
	v4l2_ctrl_new_std(&decoder->hdl, &saa7110_ctrl_ops,
		V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&decoder->hdl, &saa7110_ctrl_ops,
		V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&decoder->hdl, &saa7110_ctrl_ops,
		V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&decoder->hdl, &saa7110_ctrl_ops,
		V4L2_CID_HUE, -128, 127, 1, 0);
	sd->ctrl_handler = &decoder->hdl;
	अगर (decoder->hdl.error) अणु
		पूर्णांक err = decoder->hdl.error;

		v4l2_ctrl_handler_मुक्त(&decoder->hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_handler_setup(&decoder->hdl);

	init_रुकोqueue_head(&decoder->wq);

	rv = saa7110_ग_लिखो_block(sd, initseq, माप(initseq));
	अगर (rv < 0) अणु
		v4l2_dbg(1, debug, sd, "init status %d\n", rv);
	पूर्ण अन्यथा अणु
		पूर्णांक ver, status;
		saa7110_ग_लिखो(sd, 0x21, 0x10);
		saa7110_ग_लिखो(sd, 0x0e, 0x18);
		saa7110_ग_लिखो(sd, 0x0D, 0x04);
		ver = saa7110_पढ़ो(sd);
		saa7110_ग_लिखो(sd, 0x0D, 0x06);
		/*mdelay(150);*/
		status = saa7110_पढ़ो(sd);
		v4l2_dbg(1, debug, sd, "version %x, status=0x%02x\n",
			       ver, status);
		saa7110_ग_लिखो(sd, 0x0D, 0x86);
		saa7110_ग_लिखो(sd, 0x0F, 0x10);
		saa7110_ग_लिखो(sd, 0x11, 0x59);
		/*saa7110_ग_लिखो(sd, 0x2E, 0x9A);*/
	पूर्ण

	/*saa7110_selmux(sd,0);*/
	/*determine_norm(sd);*/
	/* setup and implicit mode 0 select has been perक्रमmed */

	वापस 0;
पूर्ण

अटल पूर्णांक saa7110_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा saa7110 *decoder = to_saa7110(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&decoder->hdl);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id saa7110_id[] = अणु
	अणु "saa7110", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, saa7110_id);

अटल काष्ठा i2c_driver saa7110_driver = अणु
	.driver = अणु
		.name	= "saa7110",
	पूर्ण,
	.probe		= saa7110_probe,
	.हटाओ		= saa7110_हटाओ,
	.id_table	= saa7110_id,
पूर्ण;

module_i2c_driver(saa7110_driver);
