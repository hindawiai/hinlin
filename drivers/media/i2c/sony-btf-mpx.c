<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/tuner.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <linux/slab.h>

MODULE_DESCRIPTION("sony-btf-mpx driver");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level 0=off(default) 1=on");

/* #घोषणा MPX_DEBUG */

/*
 * Note:
 *
 * AS(IF/MPX) pin:      LOW      HIGH/OPEN
 * IF/MPX address:   0x42/0x40   0x43/0x44
 */


अटल पूर्णांक क्रमce_mpx_mode = -1;
module_param(क्रमce_mpx_mode, पूर्णांक, 0644);

काष्ठा sony_btf_mpx अणु
	काष्ठा v4l2_subdev sd;
	पूर्णांक mpxmode;
	u32 audmode;
पूर्ण;

अटल अंतरभूत काष्ठा sony_btf_mpx *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा sony_btf_mpx, sd);
पूर्ण

अटल पूर्णांक mpx_ग_लिखो(काष्ठा i2c_client *client, पूर्णांक dev, पूर्णांक addr, पूर्णांक val)
अणु
	u8 buffer[5];
	काष्ठा i2c_msg msg;

	buffer[0] = dev;
	buffer[1] = addr >> 8;
	buffer[2] = addr & 0xff;
	buffer[3] = val >> 8;
	buffer[4] = val & 0xff;
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 5;
	msg.buf = buffer;
	i2c_transfer(client->adapter, &msg, 1);
	वापस 0;
पूर्ण

/*
 * MPX रेजिस्टर values क्रम the BTF-PG472Z:
 *
 *                                 FM_     NICAM_  SCART_
 *          MODUS  SOURCE    ACB   PRESCAL PRESCAL PRESCAL SYSTEM  VOLUME
 *         10/0030 12/0008 12/0013 12/000E 12/0010 12/0000 10/0020 12/0000
 *         ---------------------------------------------------------------
 * Auto     1003    0020    0100    2603    5000    XXXX    0001    7500
 *
 * B/G
 *  Mono    1003    0020    0100    2603    5000    XXXX    0003    7500
 *  A2      1003    0020    0100    2601    5000    XXXX    0003    7500
 *  NICAM   1003    0120    0100    2603    5000    XXXX    0008    7500
 *
 * I
 *  Mono    1003    0020    0100    2603    7900    XXXX    000A    7500
 *  NICAM   1003    0120    0100    2603    7900    XXXX    000A    7500
 *
 * D/K
 *  Mono    1003    0020    0100    2603    5000    XXXX    0004    7500
 *  A2-1    1003    0020    0100    2601    5000    XXXX    0004    7500
 *  A2-2    1003    0020    0100    2601    5000    XXXX    0005    7500
 *  A2-3    1003    0020    0100    2601    5000    XXXX    0007    7500
 *  NICAM   1003    0120    0100    2603    5000    XXXX    000B    7500
 *
 * L/L'
 *  Mono    0003    0200    0100    7C03    5000    2200    0009    7500
 *  NICAM   0003    0120    0100    7C03    5000    XXXX    0009    7500
 *
 * M
 *  Mono    1003    0200    0100    2B03    5000    2B00    0002    7500
 *
 * For Asia, replace the 0x26XX in FM_PRESCALE with 0x14XX.
 *
 * Bilingual selection in A2/NICAM:
 *
 *         High byte of SOURCE     Left chan   Right chan
 *                 0x01              MAIN         SUB
 *                 0x03              MAIN         MAIN
 *                 0x04              SUB          SUB
 *
 * Force mono in NICAM by setting the high byte of SOURCE to 0x02 (L/L') or
 * 0x00 (all other bands).  Force mono in A2 with FMONO_A2:
 *
 *                      FMONO_A2
 *                      10/0022
 *                      --------
 *     Forced mono ON     07F0
 *     Forced mono OFF    0190
 */

अटल स्थिर काष्ठा अणु
	क्रमागत अणु AUD_MONO, AUD_A2, AUD_NICAM, AUD_NICAM_L पूर्ण audio_mode;
	u16 modus;
	u16 source;
	u16 acb;
	u16 fm_prescale;
	u16 nicam_prescale;
	u16 scart_prescale;
	u16 प्रणाली;
	u16 volume;
पूर्ण mpx_audio_modes[] = अणु
	/* Auto */	अणु AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0001, 0x7500 पूर्ण,
	/* B/G Mono */	अणु AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0003, 0x7500 पूर्ण,
	/* B/G A2 */	अणु AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0003, 0x7500 पूर्ण,
	/* B/G NICAM */ अणु AUD_NICAM,	0x1003, 0x0120, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0008, 0x7500 पूर्ण,
	/* I Mono */	अणु AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x7900, 0x0000, 0x000A, 0x7500 पूर्ण,
	/* I NICAM */	अणु AUD_NICAM,	0x1003, 0x0120, 0x0100, 0x2603,
					0x7900, 0x0000, 0x000A, 0x7500 पूर्ण,
	/* D/K Mono */	अणु AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0004, 0x7500 पूर्ण,
	/* D/K A2-1 */	अणु AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0004, 0x7500 पूर्ण,
	/* D/K A2-2 */	अणु AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0005, 0x7500 पूर्ण,
	/* D/K A2-3 */	अणु AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0007, 0x7500 पूर्ण,
	/* D/K NICAM */	अणु AUD_NICAM,	0x1003, 0x0120, 0x0100, 0x2603,
					0x5000, 0x0000, 0x000B, 0x7500 पूर्ण,
	/* L/L' Mono */	अणु AUD_MONO,	0x0003, 0x0200, 0x0100, 0x7C03,
					0x5000, 0x2200, 0x0009, 0x7500 पूर्ण,
	/* L/L' NICAM */अणु AUD_NICAM_L,	0x0003, 0x0120, 0x0100, 0x7C03,
					0x5000, 0x0000, 0x0009, 0x7500 पूर्ण,
पूर्ण;

#घोषणा MPX_NUM_MODES	ARRAY_SIZE(mpx_audio_modes)

अटल पूर्णांक mpx_setup(काष्ठा sony_btf_mpx *t)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&t->sd);
	u16 source = 0;
	u8 buffer[3];
	काष्ठा i2c_msg msg;
	पूर्णांक mode = t->mpxmode;

	/* reset MPX */
	buffer[0] = 0x00;
	buffer[1] = 0x80;
	buffer[2] = 0x00;
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 3;
	msg.buf = buffer;
	i2c_transfer(client->adapter, &msg, 1);
	buffer[1] = 0x00;
	i2c_transfer(client->adapter, &msg, 1);

	अगर (t->audmode != V4L2_TUNER_MODE_MONO)
		mode++;

	अगर (mpx_audio_modes[mode].audio_mode != AUD_MONO) अणु
		चयन (t->audmode) अणु
		हाल V4L2_TUNER_MODE_MONO:
			चयन (mpx_audio_modes[mode].audio_mode) अणु
			हाल AUD_A2:
				source = mpx_audio_modes[mode].source;
				अवरोध;
			हाल AUD_NICAM:
				source = 0x0000;
				अवरोध;
			हाल AUD_NICAM_L:
				source = 0x0200;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल V4L2_TUNER_MODE_STEREO:
			source = mpx_audio_modes[mode].source;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1:
			source = 0x0300;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			source = 0x0400;
			अवरोध;
		पूर्ण
		source |= mpx_audio_modes[mode].source & 0x00ff;
	पूर्ण अन्यथा
		source = mpx_audio_modes[mode].source;

	mpx_ग_लिखो(client, 0x10, 0x0030, mpx_audio_modes[mode].modus);
	mpx_ग_लिखो(client, 0x12, 0x0008, source);
	mpx_ग_लिखो(client, 0x12, 0x0013, mpx_audio_modes[mode].acb);
	mpx_ग_लिखो(client, 0x12, 0x000e,
			mpx_audio_modes[mode].fm_prescale);
	mpx_ग_लिखो(client, 0x12, 0x0010,
			mpx_audio_modes[mode].nicam_prescale);
	mpx_ग_लिखो(client, 0x12, 0x000d,
			mpx_audio_modes[mode].scart_prescale);
	mpx_ग_लिखो(client, 0x10, 0x0020, mpx_audio_modes[mode].प्रणाली);
	mpx_ग_लिखो(client, 0x12, 0x0000, mpx_audio_modes[mode].volume);
	अगर (mpx_audio_modes[mode].audio_mode == AUD_A2)
		mpx_ग_लिखो(client, 0x10, 0x0022,
			t->audmode == V4L2_TUNER_MODE_MONO ? 0x07f0 : 0x0190);

#अगर_घोषित MPX_DEBUG
	अणु
		u8 buf1[3], buf2[2];
		काष्ठा i2c_msg msgs[2];

		v4l2_info(client,
			"MPX registers: %04x %04x %04x %04x %04x %04x %04x %04x\n",
			mpx_audio_modes[mode].modus,
			source,
			mpx_audio_modes[mode].acb,
			mpx_audio_modes[mode].fm_prescale,
			mpx_audio_modes[mode].nicam_prescale,
			mpx_audio_modes[mode].scart_prescale,
			mpx_audio_modes[mode].प्रणाली,
			mpx_audio_modes[mode].volume);
		buf1[0] = 0x11;
		buf1[1] = 0x00;
		buf1[2] = 0x7e;
		msgs[0].addr = client->addr;
		msgs[0].flags = 0;
		msgs[0].len = 3;
		msgs[0].buf = buf1;
		msgs[1].addr = client->addr;
		msgs[1].flags = I2C_M_RD;
		msgs[1].len = 2;
		msgs[1].buf = buf2;
		i2c_transfer(client->adapter, msgs, 2);
		v4l2_info(client, "MPX system: %02x%02x\n",
				buf2[0], buf2[1]);
		buf1[0] = 0x11;
		buf1[1] = 0x02;
		buf1[2] = 0x00;
		i2c_transfer(client->adapter, msgs, 2);
		v4l2_info(client, "MPX status: %02x%02x\n",
				buf2[0], buf2[1]);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण


अटल पूर्णांक sony_btf_mpx_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा sony_btf_mpx *t = to_state(sd);
	पूर्णांक शेष_mpx_mode = 0;

	अगर (std & V4L2_STD_PAL_BG)
		शेष_mpx_mode = 1;
	अन्यथा अगर (std & V4L2_STD_PAL_I)
		शेष_mpx_mode = 4;
	अन्यथा अगर (std & V4L2_STD_PAL_DK)
		शेष_mpx_mode = 6;
	अन्यथा अगर (std & V4L2_STD_SECAM_L)
		शेष_mpx_mode = 11;

	अगर (शेष_mpx_mode != t->mpxmode) अणु
		t->mpxmode = शेष_mpx_mode;
		mpx_setup(t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sony_btf_mpx_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा sony_btf_mpx *t = to_state(sd);

	vt->capability = V4L2_TUNER_CAP_NORM |
		V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LANG1 |
		V4L2_TUNER_CAP_LANG2;
	vt->rxsubchans = V4L2_TUNER_SUB_MONO |
		V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_LANG1 |
		V4L2_TUNER_SUB_LANG2;
	vt->audmode = t->audmode;
	वापस 0;
पूर्ण

अटल पूर्णांक sony_btf_mpx_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा sony_btf_mpx *t = to_state(sd);

	अगर (vt->type != V4L2_TUNER_ANALOG_TV)
		वापस -EINVAL;

	अगर (vt->audmode != t->audmode) अणु
		t->audmode = vt->audmode;
		mpx_setup(t);
	पूर्ण
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------*/

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops sony_btf_mpx_tuner_ops = अणु
	.s_tuner = sony_btf_mpx_s_tuner,
	.g_tuner = sony_btf_mpx_g_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops sony_btf_mpx_video_ops = अणु
	.s_std = sony_btf_mpx_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops sony_btf_mpx_ops = अणु
	.tuner = &sony_btf_mpx_tuner_ops,
	.video = &sony_btf_mpx_video_ops,
पूर्ण;

/* --------------------------------------------------------------------------*/

अटल पूर्णांक sony_btf_mpx_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sony_btf_mpx *t;
	काष्ठा v4l2_subdev *sd;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	t = devm_kzalloc(&client->dev, माप(*t), GFP_KERNEL);
	अगर (t == शून्य)
		वापस -ENOMEM;

	sd = &t->sd;
	v4l2_i2c_subdev_init(sd, client, &sony_btf_mpx_ops);

	/* Initialize sony_btf_mpx */
	t->mpxmode = 0;
	t->audmode = V4L2_TUNER_MODE_STEREO;

	वापस 0;
पूर्ण

अटल पूर्णांक sony_btf_mpx_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id sony_btf_mpx_id[] = अणु
	अणु "sony-btf-mpx", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sony_btf_mpx_id);

अटल काष्ठा i2c_driver sony_btf_mpx_driver = अणु
	.driver = अणु
		.name	= "sony-btf-mpx",
	पूर्ण,
	.probe = sony_btf_mpx_probe,
	.हटाओ = sony_btf_mpx_हटाओ,
	.id_table = sony_btf_mpx_id,
पूर्ण;
module_i2c_driver(sony_btf_mpx_driver);
