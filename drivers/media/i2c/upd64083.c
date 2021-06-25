<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * upd6408x - NEC Electronics 3-Dimensional Y/C separation driver
 *
 * 2003 by T.Adachi (tadachi@tadachi-net.com)
 * 2003 by Takeru KOMORIYA <komoriya@paken.org>
 * 2006 by Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/i2c/upd64083.h>

MODULE_DESCRIPTION("uPD64083 driver");
MODULE_AUTHOR("T. Adachi, Takeru KOMORIYA, Hans Verkuil");
MODULE_LICENSE("GPL");

अटल bool debug;
module_param(debug, bool, 0644);

MODULE_PARM_DESC(debug, "Debug level (0-1)");


क्रमागत अणु
	R00 = 0, R01, R02, R03, R04,
	R05, R06, R07, R08, R09,
	R0A, R0B, R0C, R0D, R0E, R0F,
	R10, R11, R12, R13, R14,
	R15, R16,
	TOT_REGS
पूर्ण;

काष्ठा upd64083_state अणु
	काष्ठा v4l2_subdev sd;
	u8 mode;
	u8 ext_y_adc;
	u8 regs[TOT_REGS];
पूर्ण;

अटल अंतरभूत काष्ठा upd64083_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा upd64083_state, sd);
पूर्ण

/* Initial values when used in combination with the
   NEC upd64031a ghost reduction chip. */
अटल u8 upd64083_init[] = अणु
	0x1f, 0x01, 0xa0, 0x2d, 0x29,  /* we use EXCSS=0 */
	0x36, 0xdd, 0x05, 0x56, 0x48,
	0x00, 0x3a, 0xa0, 0x05, 0x08,
	0x44, 0x60, 0x08, 0x52, 0xf8,
	0x53, 0x60, 0x10
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल व्योम upd64083_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[2];

	buf[0] = reg;
	buf[1] = val;
	v4l2_dbg(1, debug, sd, "write reg: %02x val: %02x\n", reg, val);
	अगर (i2c_master_send(client, buf, 2) != 2)
		v4l2_err(sd, "I/O error write 0x%02x/0x%02x\n", reg, val);
पूर्ण

/* ------------------------------------------------------------------------ */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल u8 upd64083_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[7];

	अगर (reg >= माप(buf))
		वापस 0xff;
	i2c_master_recv(client, buf, माप(buf));
	वापस buf[reg];
पूर्ण
#पूर्ण_अगर

/* ------------------------------------------------------------------------ */

अटल पूर्णांक upd64083_s_routing(काष्ठा v4l2_subdev *sd,
			      u32 input, u32 output, u32 config)
अणु
	काष्ठा upd64083_state *state = to_state(sd);
	u8 r00, r02;

	अगर (input > 7 || (input & 6) == 6)
		वापस -EINVAL;
	state->mode = (input & 3) << 6;
	state->ext_y_adc = (input & UPD64083_EXT_Y_ADC) << 3;
	r00 = (state->regs[R00] & ~(3 << 6)) | state->mode;
	r02 = (state->regs[R02] & ~(1 << 5)) | state->ext_y_adc;
	upd64083_ग_लिखो(sd, R00, r00);
	upd64083_ग_लिखो(sd, R02, r02);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक upd64083_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = upd64083_पढ़ो(sd, reg->reg & 0xff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक upd64083_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	upd64083_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक upd64083_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[7];

	i2c_master_recv(client, buf, 7);
	v4l2_info(sd, "Status: SA00=%02x SA01=%02x SA02=%02x SA03=%02x "
		      "SA04=%02x SA05=%02x SA06=%02x\n",
		buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops upd64083_core_ops = अणु
	.log_status = upd64083_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = upd64083_g_रेजिस्टर,
	.s_रेजिस्टर = upd64083_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops upd64083_video_ops = अणु
	.s_routing = upd64083_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops upd64083_ops = अणु
	.core = &upd64083_core_ops,
	.video = &upd64083_video_ops,
पूर्ण;

/* ------------------------------------------------------------------------ */

/* i2c implementation */

अटल पूर्णांक upd64083_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा upd64083_state *state;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक i;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &upd64083_ops);
	/* Initially assume that a ghost reduction chip is present */
	state->mode = 0;  /* YCS mode */
	state->ext_y_adc = (1 << 5);
	स_नकल(state->regs, upd64083_init, TOT_REGS);
	क्रम (i = 0; i < TOT_REGS; i++)
		upd64083_ग_लिखो(sd, i, state->regs[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक upd64083_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id upd64083_id[] = अणु
	अणु "upd64083", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, upd64083_id);

अटल काष्ठा i2c_driver upd64083_driver = अणु
	.driver = अणु
		.name	= "upd64083",
	पूर्ण,
	.probe		= upd64083_probe,
	.हटाओ		= upd64083_हटाओ,
	.id_table	= upd64083_id,
पूर्ण;

module_i2c_driver(upd64083_driver);
