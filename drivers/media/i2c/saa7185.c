<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * saa7185 - Philips SAA7185B video encoder driver version 0.0.3
 *
 * Copyright (C) 1998 Dave Perks <dperks@ibm.net>
 *
 * Slight changes क्रम video timing and attachment output by
 * Wolfgang Scherr <scherr@net4you.net>
 *
 * Changes by Ronald Bultje <rbultje@ronald.bitfreak.net>
 *    - moved over to linux>=2.4.x i2c protocol (1/1/2003)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>

MODULE_DESCRIPTION("Philips SAA7185 video encoder driver");
MODULE_AUTHOR("Dave Perks");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");


/* ----------------------------------------------------------------------- */

काष्ठा saa7185 अणु
	काष्ठा v4l2_subdev sd;
	अचिन्हित अक्षर reg[128];

	v4l2_std_id norm;
पूर्ण;

अटल अंतरभूत काष्ठा saa7185 *to_saa7185(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa7185, sd);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक saa7185_पढ़ो(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte(client);
पूर्ण

अटल पूर्णांक saa7185_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा saa7185 *encoder = to_saa7185(sd);

	v4l2_dbg(1, debug, sd, "%02x set to %02x\n", reg, value);
	encoder->reg[reg] = value;
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल पूर्णांक saa7185_ग_लिखो_block(काष्ठा v4l2_subdev *sd,
		स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा saa7185 *encoder = to_saa7185(sd);
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
				block_data[block_len++] =
				    encoder->reg[reg++] = data[1];
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
			ret = saa7185_ग_लिखो(sd, reg, *data++);
			अगर (ret < 0)
				अवरोध;
			len -= 2;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर अचिन्हित अक्षर init_common[] = अणु
	0x3a, 0x0f,		/* CBENB=0, V656=0, VY2C=1,
				 * YUV2C=1, MY2C=1, MUV2C=1 */

	0x42, 0x6b,		/* OVLY0=107 */
	0x43, 0x00,		/* OVLU0=0     white */
	0x44, 0x00,		/* OVLV0=0   */
	0x45, 0x22,		/* OVLY1=34  */
	0x46, 0xac,		/* OVLU1=172   yellow */
	0x47, 0x0e,		/* OVLV1=14  */
	0x48, 0x03,		/* OVLY2=3   */
	0x49, 0x1d,		/* OVLU2=29    cyan */
	0x4a, 0xac,		/* OVLV2=172 */
	0x4b, 0xf0,		/* OVLY3=240 */
	0x4c, 0xc8,		/* OVLU3=200   green */
	0x4d, 0xb9,		/* OVLV3=185 */
	0x4e, 0xd4,		/* OVLY4=212 */
	0x4f, 0x38,		/* OVLU4=56    magenta */
	0x50, 0x47,		/* OVLV4=71  */
	0x51, 0xc1,		/* OVLY5=193 */
	0x52, 0xe3,		/* OVLU5=227   red */
	0x53, 0x54,		/* OVLV5=84  */
	0x54, 0xa3,		/* OVLY6=163 */
	0x55, 0x54,		/* OVLU6=84    blue */
	0x56, 0xf2,		/* OVLV6=242 */
	0x57, 0x90,		/* OVLY7=144 */
	0x58, 0x00,		/* OVLU7=0     black */
	0x59, 0x00,		/* OVLV7=0   */

	0x5a, 0x00,		/* CHPS=0    */
	0x5b, 0x76,		/* GAINU=118 */
	0x5c, 0xa5,		/* GAINV=165 */
	0x5d, 0x3c,		/* BLCKL=60  */
	0x5e, 0x3a,		/* BLNNL=58  */
	0x5f, 0x3a,		/* CCRS=0, BLNVB=58 */
	0x60, 0x00,		/* शून्य      */

	/* 0x61 - 0x66 set according to norm */

	0x67, 0x00,		/* 0 : caption 1st byte odd  field */
	0x68, 0x00,		/* 0 : caption 2nd byte odd  field */
	0x69, 0x00,		/* 0 : caption 1st byte even field */
	0x6a, 0x00,		/* 0 : caption 2nd byte even field */

	0x6b, 0x91,		/* MODIN=2, PCREF=0, SCCLN=17 */
	0x6c, 0x20,		/* SRCV1=0, TRCV2=1, ORCV1=0, PRCV1=0,
				 * CBLF=0, ORCV2=0, PRCV2=0 */
	0x6d, 0x00,		/* SRCM1=0, CCEN=0 */

	0x6e, 0x0e,		/* HTRIG=0x005, approx. centered, at
				 * least क्रम PAL */
	0x6f, 0x00,		/* HTRIG upper bits */
	0x70, 0x20,		/* PHRES=0, SBLN=1, VTRIG=0 */

	/* The following should not be needed */

	0x71, 0x15,		/* BMRQ=0x115 */
	0x72, 0x90,		/* EMRQ=0x690 */
	0x73, 0x61,		/* EMRQ=0x690, BMRQ=0x115 */
	0x74, 0x00,		/* शून्य       */
	0x75, 0x00,		/* शून्य       */
	0x76, 0x00,		/* शून्य       */
	0x77, 0x15,		/* BRCV=0x115 */
	0x78, 0x90,		/* ERCV=0x690 */
	0x79, 0x61,		/* ERCV=0x690, BRCV=0x115 */

	/* Field length controls */

	0x7a, 0x70,		/* FLC=0 */

	/* The following should not be needed अगर SBLN = 1 */

	0x7b, 0x16,		/* FAL=22 */
	0x7c, 0x35,		/* LAL=244 */
	0x7d, 0x20,		/* LAL=244, FAL=22 */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_pal[] = अणु
	0x61, 0x1e,		/* FISE=0, PAL=1, SCBW=1, RTCE=1,
				 * YGS=1, INPI=0, DOWN=0 */
	0x62, 0xc8,		/* DECTYP=1, BSTA=72 */
	0x63, 0xcb,		/* FSC0 */
	0x64, 0x8a,		/* FSC1 */
	0x65, 0x09,		/* FSC2 */
	0x66, 0x2a,		/* FSC3 */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_ntsc[] = अणु
	0x61, 0x1d,		/* FISE=1, PAL=0, SCBW=1, RTCE=1,
				 * YGS=1, INPI=0, DOWN=0 */
	0x62, 0xe6,		/* DECTYP=1, BSTA=102 */
	0x63, 0x1f,		/* FSC0 */
	0x64, 0x7c,		/* FSC1 */
	0x65, 0xf0,		/* FSC2 */
	0x66, 0x21,		/* FSC3 */
पूर्ण;


अटल पूर्णांक saa7185_init(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा saa7185 *encoder = to_saa7185(sd);

	saa7185_ग_लिखो_block(sd, init_common, माप(init_common));
	अगर (encoder->norm & V4L2_STD_NTSC)
		saa7185_ग_लिखो_block(sd, init_ntsc, माप(init_ntsc));
	अन्यथा
		saa7185_ग_लिखो_block(sd, init_pal, माप(init_pal));
	वापस 0;
पूर्ण

अटल पूर्णांक saa7185_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa7185 *encoder = to_saa7185(sd);

	अगर (std & V4L2_STD_NTSC)
		saa7185_ग_लिखो_block(sd, init_ntsc, माप(init_ntsc));
	अन्यथा अगर (std & V4L2_STD_PAL)
		saa7185_ग_लिखो_block(sd, init_pal, माप(init_pal));
	अन्यथा
		वापस -EINVAL;
	encoder->norm = std;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7185_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	काष्ठा saa7185 *encoder = to_saa7185(sd);

	/* RJ: input = 0: input is from SA7111
	 input = 1: input is from ZR36060 */

	चयन (input) अणु
	हाल 0:
		/* turn off colorbar */
		saa7185_ग_लिखो(sd, 0x3a, 0x0f);
		/* Switch RTCE to 1 */
		saa7185_ग_लिखो(sd, 0x61, (encoder->reg[0x61] & 0xf7) | 0x08);
		saa7185_ग_लिखो(sd, 0x6e, 0x01);
		अवरोध;

	हाल 1:
		/* turn off colorbar */
		saa7185_ग_लिखो(sd, 0x3a, 0x0f);
		/* Switch RTCE to 0 */
		saa7185_ग_लिखो(sd, 0x61, (encoder->reg[0x61] & 0xf7) | 0x00);
		/* SW: a slight sync problem... */
		saa7185_ग_लिखो(sd, 0x6e, 0x00);
		अवरोध;

	हाल 2:
		/* turn on colorbar */
		saa7185_ग_लिखो(sd, 0x3a, 0x8f);
		/* Switch RTCE to 0 */
		saa7185_ग_लिखो(sd, 0x61, (encoder->reg[0x61] & 0xf7) | 0x08);
		/* SW: a slight sync problem... */
		saa7185_ग_लिखो(sd, 0x6e, 0x01);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops saa7185_core_ops = अणु
	.init = saa7185_init,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops saa7185_video_ops = अणु
	.s_std_output = saa7185_s_std_output,
	.s_routing = saa7185_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa7185_ops = अणु
	.core = &saa7185_core_ops,
	.video = &saa7185_video_ops,
पूर्ण;


/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7185_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक i;
	काष्ठा saa7185 *encoder;
	काष्ठा v4l2_subdev *sd;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	encoder = devm_kzalloc(&client->dev, माप(*encoder), GFP_KERNEL);
	अगर (encoder == शून्य)
		वापस -ENOMEM;
	encoder->norm = V4L2_STD_NTSC;
	sd = &encoder->sd;
	v4l2_i2c_subdev_init(sd, client, &saa7185_ops);

	i = saa7185_ग_लिखो_block(sd, init_common, माप(init_common));
	अगर (i >= 0)
		i = saa7185_ग_लिखो_block(sd, init_ntsc, माप(init_ntsc));
	अगर (i < 0)
		v4l2_dbg(1, debug, sd, "init error %d\n", i);
	अन्यथा
		v4l2_dbg(1, debug, sd, "revision 0x%x\n",
				saa7185_पढ़ो(sd) >> 5);
	वापस 0;
पूर्ण

अटल पूर्णांक saa7185_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा saa7185 *encoder = to_saa7185(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	/* SW: output off is active */
	saa7185_ग_लिखो(sd, 0x61, (encoder->reg[0x61]) | 0x40);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id saa7185_id[] = अणु
	अणु "saa7185", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, saa7185_id);

अटल काष्ठा i2c_driver saa7185_driver = अणु
	.driver = अणु
		.name	= "saa7185",
	पूर्ण,
	.probe		= saa7185_probe,
	.हटाओ		= saa7185_हटाओ,
	.id_table	= saa7185_id,
पूर्ण;

module_i2c_driver(saa7185_driver);
