<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    bt866 - BT866 Digital Video Encoder (Rockwell Part)

    Copyright (C) 1999 Mike Bernson <mike@mlb.org>
    Copyright (C) 1998 Dave Perks <dperks@ibm.net>

    Modअगरications क्रम LML33/DC10plus unअगरied driver
    Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>

    This code was modअगरy/ported from the saa7111 driver written
    by Dave Perks.

    This code was adapted क्रम the bt866 by Christer Weinigel and ported
    to 2.6 by Martin Samuelsson.

*/

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>

MODULE_DESCRIPTION("Brooktree-866 video encoder driver");
MODULE_AUTHOR("Mike Bernson & Dave Perks");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");


/* ----------------------------------------------------------------------- */

काष्ठा bt866 अणु
	काष्ठा v4l2_subdev sd;
	u8 reg[256];
पूर्ण;

अटल अंतरभूत काष्ठा bt866 *to_bt866(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा bt866, sd);
पूर्ण

अटल पूर्णांक bt866_ग_लिखो(काष्ठा bt866 *encoder, u8 subaddr, u8 data)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&encoder->sd);
	u8 buffer[2];
	पूर्णांक err;

	buffer[0] = subaddr;
	buffer[1] = data;

	encoder->reg[subaddr] = data;

	v4l_dbg(1, debug, client, "write 0x%02x = 0x%02x\n", subaddr, data);

	क्रम (err = 0; err < 3;) अणु
		अगर (i2c_master_send(client, buffer, 2) == 2)
			अवरोध;
		err++;
		v4l_warn(client, "error #%d writing to 0x%02x\n",
				err, subaddr);
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));
	पूर्ण
	अगर (err == 3) अणु
		v4l_warn(client, "giving up\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bt866_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	v4l2_dbg(1, debug, sd, "set norm %llx\n", (अचिन्हित दीर्घ दीर्घ)std);

	/* Only PAL supported by this driver at the moment! */
	अगर (!(std & V4L2_STD_NTSC))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक bt866_s_routing(काष्ठा v4l2_subdev *sd,
			   u32 input, u32 output, u32 config)
अणु
	अटल स्थिर __u8 init[] = अणु
		0xc8, 0xcc, /* CRSCALE */
		0xca, 0x91, /* CBSCALE */
		0xcc, 0x24, /* YC16 | OSDNUM */
		0xda, 0x00, /*  */
		0xdc, 0x24, /* SETMODE | PAL */
		0xde, 0x02, /* EACTIVE */

		/* overlay colors */
		0x70, 0xEB, 0x90, 0x80, 0xB0, 0x80, /* white */
		0x72, 0xA2, 0x92, 0x8E, 0xB2, 0x2C, /* yellow */
		0x74, 0x83, 0x94, 0x2C, 0xB4, 0x9C, /* cyan */
		0x76, 0x70, 0x96, 0x3A, 0xB6, 0x48, /* green */
		0x78, 0x54, 0x98, 0xC6, 0xB8, 0xB8, /* magenta */
		0x7A, 0x41, 0x9A, 0xD4, 0xBA, 0x64, /* red */
		0x7C, 0x23, 0x9C, 0x72, 0xBC, 0xD4, /* blue */
		0x7E, 0x10, 0x9E, 0x80, 0xBE, 0x80, /* black */

		0x60, 0xEB, 0x80, 0x80, 0xc0, 0x80, /* white */
		0x62, 0xA2, 0x82, 0x8E, 0xc2, 0x2C, /* yellow */
		0x64, 0x83, 0x84, 0x2C, 0xc4, 0x9C, /* cyan */
		0x66, 0x70, 0x86, 0x3A, 0xc6, 0x48, /* green */
		0x68, 0x54, 0x88, 0xC6, 0xc8, 0xB8, /* magenta */
		0x6A, 0x41, 0x8A, 0xD4, 0xcA, 0x64, /* red */
		0x6C, 0x23, 0x8C, 0x72, 0xcC, 0xD4, /* blue */
		0x6E, 0x10, 0x8E, 0x80, 0xcE, 0x80, /* black */
	पूर्ण;
	काष्ठा bt866 *encoder = to_bt866(sd);
	u8 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(init) / 2; i += 2)
		bt866_ग_लिखो(encoder, init[i], init[i+1]);

	val = encoder->reg[0xdc];

	अगर (input == 0)
		val |= 0x40; /* CBSWAP */
	अन्यथा
		val &= ~0x40; /* !CBSWAP */

	bt866_ग_लिखो(encoder, 0xdc, val);

	val = encoder->reg[0xcc];
	अगर (input == 2)
		val |= 0x01; /* OSDBAR */
	अन्यथा
		val &= ~0x01; /* !OSDBAR */
	bt866_ग_लिखो(encoder, 0xcc, val);

	v4l2_dbg(1, debug, sd, "set input %d\n", input);

	चयन (input) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर 0
/* Code to setup square pixels, might be of some use in the future,
   but is currently unused. */
	val = encoder->reg[0xdc];
	अगर (*iarg)
		val |= 1; /* SQUARE */
	अन्यथा
		val &= ~1; /* !SQUARE */
	bt866_ग_लिखो(client, 0xdc, val);
#पूर्ण_अगर

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_video_ops bt866_video_ops = अणु
	.s_std_output = bt866_s_std_output,
	.s_routing = bt866_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops bt866_ops = अणु
	.video = &bt866_video_ops,
पूर्ण;

अटल पूर्णांक bt866_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bt866 *encoder;
	काष्ठा v4l2_subdev *sd;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	encoder = devm_kzalloc(&client->dev, माप(*encoder), GFP_KERNEL);
	अगर (encoder == शून्य)
		वापस -ENOMEM;
	sd = &encoder->sd;
	v4l2_i2c_subdev_init(sd, client, &bt866_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक bt866_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bt866_id[] = अणु
	अणु "bt866", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bt866_id);

अटल काष्ठा i2c_driver bt866_driver = अणु
	.driver = अणु
		.name	= "bt866",
	पूर्ण,
	.probe		= bt866_probe,
	.हटाओ		= bt866_हटाओ,
	.id_table	= bt866_id,
पूर्ण;

module_i2c_driver(bt866_driver);
