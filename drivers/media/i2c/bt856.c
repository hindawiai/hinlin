<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * bt856 - BT856A Digital Video Encoder (Rockwell Part)
 *
 * Copyright (C) 1999 Mike Bernson <mike@mlb.org>
 * Copyright (C) 1998 Dave Perks <dperks@ibm.net>
 *
 * Modअगरications क्रम LML33/DC10plus unअगरied driver
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 *
 * This code was modअगरy/ported from the saa7111 driver written
 * by Dave Perks.
 *
 * Changes by Ronald Bultje <rbultje@ronald.bitfreak.net>
 *   - moved over to linux>=2.4.x i2c protocol (9/9/2002)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>

MODULE_DESCRIPTION("Brooktree-856A video encoder driver");
MODULE_AUTHOR("Mike Bernson & Dave Perks");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");


/* ----------------------------------------------------------------------- */

#घोषणा BT856_REG_OFFSET	0xDA
#घोषणा BT856_NR_REG		6

काष्ठा bt856 अणु
	काष्ठा v4l2_subdev sd;
	अचिन्हित अक्षर reg[BT856_NR_REG];

	v4l2_std_id norm;
पूर्ण;

अटल अंतरभूत काष्ठा bt856 *to_bt856(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा bt856, sd);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक bt856_ग_लिखो(काष्ठा bt856 *encoder, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&encoder->sd);

	encoder->reg[reg - BT856_REG_OFFSET] = value;
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक bt856_setbit(काष्ठा bt856 *encoder, u8 reg, u8 bit, u8 value)
अणु
	वापस bt856_ग_लिखो(encoder, reg,
		(encoder->reg[reg - BT856_REG_OFFSET] & ~(1 << bit)) |
				(value ? (1 << bit) : 0));
पूर्ण

अटल व्योम bt856_dump(काष्ठा bt856 *encoder)
अणु
	पूर्णांक i;

	v4l2_info(&encoder->sd, "register dump:\n");
	क्रम (i = 0; i < BT856_NR_REG; i += 2)
		prपूर्णांकk(KERN_CONT " %02x", encoder->reg[i]);
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक bt856_init(काष्ठा v4l2_subdev *sd, u32 arg)
अणु
	काष्ठा bt856 *encoder = to_bt856(sd);

	/* This is just क्रम testing!!! */
	v4l2_dbg(1, debug, sd, "init\n");
	bt856_ग_लिखो(encoder, 0xdc, 0x18);
	bt856_ग_लिखो(encoder, 0xda, 0);
	bt856_ग_लिखो(encoder, 0xde, 0);

	bt856_setbit(encoder, 0xdc, 3, 1);
	/*bt856_setbit(encoder, 0xdc, 6, 0);*/
	bt856_setbit(encoder, 0xdc, 4, 1);

	अगर (encoder->norm & V4L2_STD_NTSC)
		bt856_setbit(encoder, 0xdc, 2, 0);
	अन्यथा
		bt856_setbit(encoder, 0xdc, 2, 1);

	bt856_setbit(encoder, 0xdc, 1, 1);
	bt856_setbit(encoder, 0xde, 4, 0);
	bt856_setbit(encoder, 0xde, 3, 1);
	अगर (debug != 0)
		bt856_dump(encoder);
	वापस 0;
पूर्ण

अटल पूर्णांक bt856_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा bt856 *encoder = to_bt856(sd);

	v4l2_dbg(1, debug, sd, "set norm %llx\n", (अचिन्हित दीर्घ दीर्घ)std);

	अगर (std & V4L2_STD_NTSC) अणु
		bt856_setbit(encoder, 0xdc, 2, 0);
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
		bt856_setbit(encoder, 0xdc, 2, 1);
		bt856_setbit(encoder, 0xda, 0, 0);
		/*bt856_setbit(encoder, 0xda, 0, 1);*/
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	encoder->norm = std;
	अगर (debug != 0)
		bt856_dump(encoder);
	वापस 0;
पूर्ण

अटल पूर्णांक bt856_s_routing(काष्ठा v4l2_subdev *sd,
			   u32 input, u32 output, u32 config)
अणु
	काष्ठा bt856 *encoder = to_bt856(sd);

	v4l2_dbg(1, debug, sd, "set input %d\n", input);

	/* We only have video bus.
	 * input= 0: input is from bt819
	 * input= 1: input is from ZR36060 */
	चयन (input) अणु
	हाल 0:
		bt856_setbit(encoder, 0xde, 4, 0);
		bt856_setbit(encoder, 0xde, 3, 1);
		bt856_setbit(encoder, 0xdc, 3, 1);
		bt856_setbit(encoder, 0xdc, 6, 0);
		अवरोध;
	हाल 1:
		bt856_setbit(encoder, 0xde, 4, 0);
		bt856_setbit(encoder, 0xde, 3, 1);
		bt856_setbit(encoder, 0xdc, 3, 1);
		bt856_setbit(encoder, 0xdc, 6, 1);
		अवरोध;
	हाल 2:	/* Color bar */
		bt856_setbit(encoder, 0xdc, 3, 0);
		bt856_setbit(encoder, 0xde, 4, 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (debug != 0)
		bt856_dump(encoder);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops bt856_core_ops = अणु
	.init = bt856_init,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops bt856_video_ops = अणु
	.s_std_output = bt856_s_std_output,
	.s_routing = bt856_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops bt856_ops = अणु
	.core = &bt856_core_ops,
	.video = &bt856_video_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक bt856_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bt856 *encoder;
	काष्ठा v4l2_subdev *sd;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	encoder = devm_kzalloc(&client->dev, माप(*encoder), GFP_KERNEL);
	अगर (encoder == शून्य)
		वापस -ENOMEM;
	sd = &encoder->sd;
	v4l2_i2c_subdev_init(sd, client, &bt856_ops);
	encoder->norm = V4L2_STD_NTSC;

	bt856_ग_लिखो(encoder, 0xdc, 0x18);
	bt856_ग_लिखो(encoder, 0xda, 0);
	bt856_ग_लिखो(encoder, 0xde, 0);

	bt856_setbit(encoder, 0xdc, 3, 1);
	/*bt856_setbit(encoder, 0xdc, 6, 0);*/
	bt856_setbit(encoder, 0xdc, 4, 1);

	अगर (encoder->norm & V4L2_STD_NTSC)
		bt856_setbit(encoder, 0xdc, 2, 0);
	अन्यथा
		bt856_setbit(encoder, 0xdc, 2, 1);

	bt856_setbit(encoder, 0xdc, 1, 1);
	bt856_setbit(encoder, 0xde, 4, 0);
	bt856_setbit(encoder, 0xde, 3, 1);

	अगर (debug != 0)
		bt856_dump(encoder);
	वापस 0;
पूर्ण

अटल पूर्णांक bt856_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bt856_id[] = अणु
	अणु "bt856", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bt856_id);

अटल काष्ठा i2c_driver bt856_driver = अणु
	.driver = अणु
		.name	= "bt856",
	पूर्ण,
	.probe		= bt856_probe,
	.हटाओ		= bt856_हटाओ,
	.id_table	= bt856_id,
पूर्ण;

module_i2c_driver(bt856_driver);
