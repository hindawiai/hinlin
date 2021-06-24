<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  adv7175 - adv7175a video encoder driver version 0.0.3
 *
 * Copyright (C) 1998 Dave Perks <dperks@ibm.net>
 * Copyright (C) 1999 Wolfgang Scherr <scherr@net4you.net>
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 *    - some corrections क्रम Pinnacle Systems Inc. DC10plus card.
 *
 * Changes by Ronald Bultje <rbultje@ronald.bitfreak.net>
 *    - moved over to linux>=2.4.x i2c protocol (9/9/2002)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>

MODULE_DESCRIPTION("Analog Devices ADV7175 video encoder driver");
MODULE_AUTHOR("Dave Perks");
MODULE_LICENSE("GPL");

#घोषणा   I2C_ADV7175        0xd4
#घोषणा   I2C_ADV7176        0x54


अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

/* ----------------------------------------------------------------------- */

काष्ठा adv7175 अणु
	काष्ठा v4l2_subdev sd;
	v4l2_std_id norm;
	पूर्णांक input;
पूर्ण;

अटल अंतरभूत काष्ठा adv7175 *to_adv7175(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा adv7175, sd);
पूर्ण

अटल अक्षर *inमाला_दो[] = अणु "pass_through", "play_back", "color_bar" पूर्ण;

अटल u32 adv7175_codes[] = अणु
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_UYVY8_1X16,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक adv7175_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक adv7175_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक adv7175_ग_लिखो_block(काष्ठा v4l2_subdev *sd,
		     स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = -1;
	u8 reg;

	/* the adv7175 has an स्वतःincrement function, use it अगर
	 * the adapter understands raw I2C */
	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		/* करो raw I2C, not smbus compatible */
		u8 block_data[32];
		पूर्णांक block_len;

		जबतक (len >= 2) अणु
			block_len = 0;
			block_data[block_len++] = reg = data[0];
			करो अणु
				block_data[block_len++] = data[1];
				reg++;
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
			ret = adv7175_ग_लिखो(sd, reg, *data++);
			अगर (ret < 0)
				अवरोध;
			len -= 2;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम set_subcarrier_freq(काष्ठा v4l2_subdev *sd, पूर्णांक pass_through)
अणु
	/* क्रम some reason pass_through NTSC needs
	 * a dअगरferent sub-carrier freq to reमुख्य stable. */
	अगर (pass_through)
		adv7175_ग_लिखो(sd, 0x02, 0x00);
	अन्यथा
		adv7175_ग_लिखो(sd, 0x02, 0x55);

	adv7175_ग_लिखो(sd, 0x03, 0x55);
	adv7175_ग_लिखो(sd, 0x04, 0x55);
	adv7175_ग_लिखो(sd, 0x05, 0x25);
पूर्ण

/* ----------------------------------------------------------------------- */
/* Output filter:  S-Video  Composite */

#घोषणा MR050       0x11	/* 0x09 */
#घोषणा MR060       0x14	/* 0x0c */

/* ----------------------------------------------------------------------- */

#घोषणा TR0MODE     0x46
#घोषणा TR0RST	    0x80

#घोषणा TR1CAPT	    0x80
#घोषणा TR1PLAY	    0x00

अटल स्थिर अचिन्हित अक्षर init_common[] = अणु

	0x00, MR050,		/* MR0, PAL enabled */
	0x01, 0x00,		/* MR1 */
	0x02, 0x0c,		/* subc. freq. */
	0x03, 0x8c,		/* subc. freq. */
	0x04, 0x79,		/* subc. freq. */
	0x05, 0x26,		/* subc. freq. */
	0x06, 0x40,		/* subc. phase */

	0x07, TR0MODE,		/* TR0, 16bit */
	0x08, 0x21,		/*  */
	0x09, 0x00,		/*  */
	0x0a, 0x00,		/*  */
	0x0b, 0x00,		/*  */
	0x0c, TR1CAPT,		/* TR1 */
	0x0d, 0x4f,		/* MR2 */
	0x0e, 0x00,		/*  */
	0x0f, 0x00,		/*  */
	0x10, 0x00,		/*  */
	0x11, 0x00,		/*  */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_pal[] = अणु
	0x00, MR050,		/* MR0, PAL enabled */
	0x01, 0x00,		/* MR1 */
	0x02, 0x0c,		/* subc. freq. */
	0x03, 0x8c,		/* subc. freq. */
	0x04, 0x79,		/* subc. freq. */
	0x05, 0x26,		/* subc. freq. */
	0x06, 0x40,		/* subc. phase */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_ntsc[] = अणु
	0x00, MR060,		/* MR0, NTSC enabled */
	0x01, 0x00,		/* MR1 */
	0x02, 0x55,		/* subc. freq. */
	0x03, 0x55,		/* subc. freq. */
	0x04, 0x55,		/* subc. freq. */
	0x05, 0x25,		/* subc. freq. */
	0x06, 0x1a,		/* subc. phase */
पूर्ण;

अटल पूर्णांक adv7175_init(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	/* This is just क्रम testing!!! */
	adv7175_ग_लिखो_block(sd, init_common, माप(init_common));
	adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
	adv7175_ग_लिखो(sd, 0x07, TR0MODE);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7175_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा adv7175 *encoder = to_adv7175(sd);

	अगर (std & V4L2_STD_NTSC) अणु
		adv7175_ग_लिखो_block(sd, init_ntsc, माप(init_ntsc));
		अगर (encoder->input == 0)
			adv7175_ग_लिखो(sd, 0x0d, 0x4f);	/* Enable genlock */
		adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE);
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
		adv7175_ग_लिखो_block(sd, init_pal, माप(init_pal));
		अगर (encoder->input == 0)
			adv7175_ग_लिखो(sd, 0x0d, 0x4f);	/* Enable genlock */
		adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE);
	पूर्ण अन्यथा अगर (std & V4L2_STD_SECAM) अणु
		/* This is an attempt to convert
		 * SECAM->PAL (typically it करोes not work
		 * due to genlock: when decoder is in SECAM
		 * and encoder in in PAL the subcarrier can
		 * not be synchronized with horizontal
		 * quency) */
		adv7175_ग_लिखो_block(sd, init_pal, माप(init_pal));
		अगर (encoder->input == 0)
			adv7175_ग_लिखो(sd, 0x0d, 0x49);	/* Disable genlock */
		adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE);
	पूर्ण अन्यथा अणु
		v4l2_dbg(1, debug, sd, "illegal norm: %llx\n",
				(अचिन्हित दीर्घ दीर्घ)std);
		वापस -EINVAL;
	पूर्ण
	v4l2_dbg(1, debug, sd, "switched to %llx\n", (अचिन्हित दीर्घ दीर्घ)std);
	encoder->norm = std;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7175_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	काष्ठा adv7175 *encoder = to_adv7175(sd);

	/* RJ: input = 0: input is from decoder
	   input = 1: input is from ZR36060
	   input = 2: color bar */

	चयन (input) अणु
	हाल 0:
		adv7175_ग_लिखो(sd, 0x01, 0x00);

		अगर (encoder->norm & V4L2_STD_NTSC)
			set_subcarrier_freq(sd, 1);

		adv7175_ग_लिखो(sd, 0x0c, TR1CAPT);	/* TR1 */
		अगर (encoder->norm & V4L2_STD_SECAM)
			adv7175_ग_लिखो(sd, 0x0d, 0x49);	/* Disable genlock */
		अन्यथा
			adv7175_ग_लिखो(sd, 0x0d, 0x4f);	/* Enable genlock */
		adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE);
		/*udelay(10);*/
		अवरोध;

	हाल 1:
		adv7175_ग_लिखो(sd, 0x01, 0x00);

		अगर (encoder->norm & V4L2_STD_NTSC)
			set_subcarrier_freq(sd, 0);

		adv7175_ग_लिखो(sd, 0x0c, TR1PLAY);	/* TR1 */
		adv7175_ग_लिखो(sd, 0x0d, 0x49);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE);
		/* udelay(10); */
		अवरोध;

	हाल 2:
		adv7175_ग_लिखो(sd, 0x01, 0x80);

		अगर (encoder->norm & V4L2_STD_NTSC)
			set_subcarrier_freq(sd, 0);

		adv7175_ग_लिखो(sd, 0x0d, 0x49);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
		adv7175_ग_लिखो(sd, 0x07, TR0MODE);
		/* udelay(10); */
		अवरोध;

	शेष:
		v4l2_dbg(1, debug, sd, "illegal input: %d\n", input);
		वापस -EINVAL;
	पूर्ण
	v4l2_dbg(1, debug, sd, "switched to %s\n", inमाला_दो[input]);
	encoder->input = input;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7175_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(adv7175_codes))
		वापस -EINVAL;

	code->code = adv7175_codes[code->index];
	वापस 0;
पूर्ण

अटल पूर्णांक adv7175_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	u8 val = adv7175_पढ़ो(sd, 0x7);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर ((val & 0x40) == (1 << 6))
		mf->code = MEDIA_BUS_FMT_UYVY8_1X16;
	अन्यथा
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;

	mf->colorspace  = V4L2_COLORSPACE_SMPTE170M;
	mf->width       = 0;
	mf->height      = 0;
	mf->field       = V4L2_FIELD_ANY;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7175_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	u8 val = adv7175_पढ़ो(sd, 0x7);
	पूर्णांक ret = 0;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	चयन (mf->code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		val &= ~0x40;
		अवरोध;

	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		val |= 0x40;
		अवरोध;

	शेष:
		v4l2_dbg(1, debug, sd,
			"illegal v4l2_mbus_framefmt code: %d\n", mf->code);
		वापस -EINVAL;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		ret = adv7175_ग_लिखो(sd, 0x7, val);

	वापस ret;
पूर्ण

अटल पूर्णांक adv7175_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	अगर (on)
		adv7175_ग_लिखो(sd, 0x01, 0x00);
	अन्यथा
		adv7175_ग_लिखो(sd, 0x01, 0x78);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops adv7175_core_ops = अणु
	.init = adv7175_init,
	.s_घातer = adv7175_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv7175_video_ops = अणु
	.s_std_output = adv7175_s_std_output,
	.s_routing = adv7175_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv7175_pad_ops = अणु
	.क्रमागत_mbus_code = adv7175_क्रमागत_mbus_code,
	.get_fmt = adv7175_get_fmt,
	.set_fmt = adv7175_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops adv7175_ops = अणु
	.core = &adv7175_core_ops,
	.video = &adv7175_video_ops,
	.pad = &adv7175_pad_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक adv7175_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक i;
	काष्ठा adv7175 *encoder;
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
	v4l2_i2c_subdev_init(sd, client, &adv7175_ops);
	encoder->norm = V4L2_STD_NTSC;
	encoder->input = 0;

	i = adv7175_ग_लिखो_block(sd, init_common, माप(init_common));
	अगर (i >= 0) अणु
		i = adv7175_ग_लिखो(sd, 0x07, TR0MODE | TR0RST);
		i = adv7175_ग_लिखो(sd, 0x07, TR0MODE);
		i = adv7175_पढ़ो(sd, 0x12);
		v4l2_dbg(1, debug, sd, "revision %d\n", i & 1);
	पूर्ण
	अगर (i < 0)
		v4l2_dbg(1, debug, sd, "init error 0x%x\n", i);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7175_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id adv7175_id[] = अणु
	अणु "adv7175", 0 पूर्ण,
	अणु "adv7176", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adv7175_id);

अटल काष्ठा i2c_driver adv7175_driver = अणु
	.driver = अणु
		.name	= "adv7175",
	पूर्ण,
	.probe		= adv7175_probe,
	.हटाओ		= adv7175_हटाओ,
	.id_table	= adv7175_id,
पूर्ण;

module_i2c_driver(adv7175_driver);
