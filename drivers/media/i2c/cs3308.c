<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cirrus Logic cs3308 8-Channel Analog Volume Control
 *
 * Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 * Copyright (C) 2012 Steven Toth <stoth@kernelद_असल.com>
 *
 * Derived from cs5345.c Copyright (C) 2007 Hans Verkuil
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>

MODULE_DESCRIPTION("i2c device driver for cs3308 8-channel volume control");
MODULE_AUTHOR("Devin Heitmueller");
MODULE_LICENSE("GPL");

अटल अंतरभूत पूर्णांक cs3308_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक cs3308_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक cs3308_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = cs3308_पढ़ो(sd, reg->reg & 0xffff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक cs3308_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	cs3308_ग_लिखो(sd, reg->reg & 0xffff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops cs3308_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = cs3308_g_रेजिस्टर,
	.s_रेजिस्टर = cs3308_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops cs3308_ops = अणु
	.core = &cs3308_core_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक cs3308_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा v4l2_subdev *sd;
	अचिन्हित i;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	अगर ((i2c_smbus_पढ़ो_byte_data(client, 0x1c) & 0xf0) != 0xe0)
		वापस -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
		 client->addr << 1, client->adapter->name);

	sd = kzalloc(माप(काष्ठा v4l2_subdev), GFP_KERNEL);
	अगर (sd == शून्य)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(sd, client, &cs3308_ops);

	/* Set some reasonable शेषs */
	cs3308_ग_लिखो(sd, 0x0d, 0x00); /* Power up all channels */
	cs3308_ग_लिखो(sd, 0x0e, 0x00); /* Master Power */
	cs3308_ग_लिखो(sd, 0x0b, 0x00); /* Device Configuration */
	/* Set volume क्रम each channel */
	क्रम (i = 1; i <= 8; i++)
		cs3308_ग_लिखो(sd, i, 0xd2);
	cs3308_ग_लिखो(sd, 0x0a, 0x00); /* Unmute all channels */
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक cs3308_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	kमुक्त(sd);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id cs3308_id[] = अणु
	अणु "cs3308", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs3308_id);

अटल काष्ठा i2c_driver cs3308_driver = अणु
	.driver = अणु
		.name   = "cs3308",
	पूर्ण,
	.probe          = cs3308_probe,
	.हटाओ         = cs3308_हटाओ,
	.id_table       = cs3308_id,
पूर्ण;

module_i2c_driver(cs3308_driver);
