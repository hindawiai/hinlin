<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * upd64031A - NEC Electronics Ghost Reduction क्रम NTSC in Japan
 *
 * 2003 by T.Adachi <tadachi@tadachi-net.com>
 * 2003 by Takeru KOMORIYA <komoriya@paken.org>
 * 2006 by Hans Verkuil <hverkuil@xs4all.nl>
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/i2c/upd64031a.h>

/* --------------------- पढ़ो रेजिस्टरs functions define -------------------- */

/* bit masks */
#घोषणा GR_MODE_MASK              0xc0
#घोषणा सूचीECT_3DYCS_CONNECT_MASK 0xc0
#घोषणा SYNC_CIRCUIT_MASK         0xa0

/* -------------------------------------------------------------------------- */

MODULE_DESCRIPTION("uPD64031A driver");
MODULE_AUTHOR("T. Adachi, Takeru KOMORIYA, Hans Verkuil");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(debug, "Debug level (0-1)");


क्रमागत अणु
	R00 = 0, R01, R02, R03, R04,
	R05, R06, R07, R08, R09,
	R0A, R0B, R0C, R0D, R0E, R0F,
	/* unused रेजिस्टरs
	 R10, R11, R12, R13, R14,
	 R15, R16, R17,
	 */
	TOT_REGS
पूर्ण;

काष्ठा upd64031a_state अणु
	काष्ठा v4l2_subdev sd;
	u8 regs[TOT_REGS];
	u8 gr_mode;
	u8 direct_3dycs_connect;
	u8 ext_comp_sync;
	u8 ext_vert_sync;
पूर्ण;

अटल अंतरभूत काष्ठा upd64031a_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा upd64031a_state, sd);
पूर्ण

अटल u8 upd64031a_init[] = अणु
	0x00, 0xb8, 0x48, 0xd2, 0xe6,
	0x03, 0x10, 0x0b, 0xaf, 0x7f,
	0x00, 0x00, 0x1d, 0x5e, 0x00,
	0xd0
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल u8 upd64031a_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[2];

	अगर (reg >= माप(buf))
		वापस 0xff;
	i2c_master_recv(client, buf, 2);
	वापस buf[reg];
पूर्ण

/* ------------------------------------------------------------------------ */

अटल व्योम upd64031a_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[2];

	buf[0] = reg;
	buf[1] = val;
	v4l2_dbg(1, debug, sd, "write reg: %02X val: %02X\n", reg, val);
	अगर (i2c_master_send(client, buf, 2) != 2)
		v4l2_err(sd, "I/O error write 0x%02x/0x%02x\n", reg, val);
पूर्ण

/* ------------------------------------------------------------------------ */

/* The input changed due to new input or channel changed */
अटल पूर्णांक upd64031a_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा upd64031a_state *state = to_state(sd);
	u8 reg = state->regs[R00];

	v4l2_dbg(1, debug, sd, "changed input or channel\n");
	upd64031a_ग_लिखो(sd, R00, reg | 0x10);
	upd64031a_ग_लिखो(sd, R00, reg & ~0x10);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक upd64031a_s_routing(काष्ठा v4l2_subdev *sd,
			       u32 input, u32 output, u32 config)
अणु
	काष्ठा upd64031a_state *state = to_state(sd);
	u8 r00, r05, r08;

	state->gr_mode = (input & 3) << 6;
	state->direct_3dycs_connect = (input & 0xc) << 4;
	state->ext_comp_sync =
		(input & UPD64031A_COMPOSITE_EXTERNAL) << 1;
	state->ext_vert_sync =
		(input & UPD64031A_VERTICAL_EXTERNAL) << 2;
	r00 = (state->regs[R00] & ~GR_MODE_MASK) | state->gr_mode;
	r05 = (state->regs[R00] & ~SYNC_CIRCUIT_MASK) |
		state->ext_comp_sync | state->ext_vert_sync;
	r08 = (state->regs[R08] & ~सूचीECT_3DYCS_CONNECT_MASK) |
		state->direct_3dycs_connect;
	upd64031a_ग_लिखो(sd, R00, r00);
	upd64031a_ग_लिखो(sd, R05, r05);
	upd64031a_ग_लिखो(sd, R08, r08);
	वापस upd64031a_s_frequency(sd, शून्य);
पूर्ण

अटल पूर्णांक upd64031a_log_status(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_info(sd, "Status: SA00=0x%02x SA01=0x%02x\n",
			upd64031a_पढ़ो(sd, 0), upd64031a_पढ़ो(sd, 1));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक upd64031a_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = upd64031a_पढ़ो(sd, reg->reg & 0xff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक upd64031a_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	upd64031a_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops upd64031a_core_ops = अणु
	.log_status = upd64031a_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = upd64031a_g_रेजिस्टर,
	.s_रेजिस्टर = upd64031a_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops upd64031a_tuner_ops = अणु
	.s_frequency = upd64031a_s_frequency,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops upd64031a_video_ops = अणु
	.s_routing = upd64031a_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops upd64031a_ops = अणु
	.core = &upd64031a_core_ops,
	.tuner = &upd64031a_tuner_ops,
	.video = &upd64031a_video_ops,
पूर्ण;

/* ------------------------------------------------------------------------ */

/* i2c implementation */

अटल पूर्णांक upd64031a_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा upd64031a_state *state;
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
	v4l2_i2c_subdev_init(sd, client, &upd64031a_ops);
	स_नकल(state->regs, upd64031a_init, माप(state->regs));
	state->gr_mode = UPD64031A_GR_ON << 6;
	state->direct_3dycs_connect = UPD64031A_3DYCS_COMPOSITE << 4;
	state->ext_comp_sync = state->ext_vert_sync = 0;
	क्रम (i = 0; i < TOT_REGS; i++)
		upd64031a_ग_लिखो(sd, i, state->regs[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक upd64031a_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id upd64031a_id[] = अणु
	अणु "upd64031a", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, upd64031a_id);

अटल काष्ठा i2c_driver upd64031a_driver = अणु
	.driver = अणु
		.name	= "upd64031a",
	पूर्ण,
	.probe		= upd64031a_probe,
	.हटाओ		= upd64031a_हटाओ,
	.id_table	= upd64031a_id,
पूर्ण;

module_i2c_driver(upd64031a_driver);
