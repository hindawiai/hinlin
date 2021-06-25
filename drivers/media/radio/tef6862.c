<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tef6862.c Philips TEF6862 Car Radio Enhanced Selectivity Tuner
 * Copyright (c) 2009 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>

#घोषणा DRIVER_NAME "tef6862"

#घोषणा FREQ_MUL 16000

#घोषणा TEF6862_LO_FREQ (875U * FREQ_MUL / 10)
#घोषणा TEF6862_HI_FREQ (108U * FREQ_MUL)

/* Write mode sub addresses */
#घोषणा WM_SUB_BANDWIDTH	0x0
#घोषणा WM_SUB_PLLM		0x1
#घोषणा WM_SUB_PLLL		0x2
#घोषणा WM_SUB_DAA		0x3
#घोषणा WM_SUB_AGC		0x4
#घोषणा WM_SUB_BAND		0x5
#घोषणा WM_SUB_CONTROL		0x6
#घोषणा WM_SUB_LEVEL		0x7
#घोषणा WM_SUB_IFCF		0x8
#घोषणा WM_SUB_IFCAP		0x9
#घोषणा WM_SUB_ACD		0xA
#घोषणा WM_SUB_TEST		0xF

/* Dअगरferent modes of the MSA रेजिस्टर */
#घोषणा MSA_MODE_BUFFER		0x0
#घोषणा MSA_MODE_PRESET		0x1
#घोषणा MSA_MODE_SEARCH		0x2
#घोषणा MSA_MODE_AF_UPDATE	0x3
#घोषणा MSA_MODE_JUMP		0x4
#घोषणा MSA_MODE_CHECK		0x5
#घोषणा MSA_MODE_LOAD		0x6
#घोषणा MSA_MODE_END		0x7
#घोषणा MSA_MODE_SHIFT		5

काष्ठा tef6862_state अणु
	काष्ठा v4l2_subdev sd;
	अचिन्हित दीर्घ freq;
पूर्ण;

अटल अंतरभूत काष्ठा tef6862_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tef6862_state, sd);
पूर्ण

अटल u16 tef6862_sigstr(काष्ठा i2c_client *client)
अणु
	u8 buf[4];
	पूर्णांक err = i2c_master_recv(client, buf, माप(buf));
	अगर (err == माप(buf))
		वापस buf[3] << 8;
	वापस 0;
पूर्ण

अटल पूर्णांक tef6862_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *v)
अणु
	अगर (v->index > 0)
		वापस -EINVAL;

	/* only support FM क्रम now */
	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = TEF6862_LO_FREQ;
	v->rangehigh = TEF6862_HI_FREQ;
	v->rxsubchans = V4L2_TUNER_SUB_MONO;
	v->capability = V4L2_TUNER_CAP_LOW;
	v->audmode = V4L2_TUNER_MODE_STEREO;
	v->संकेत = tef6862_sigstr(v4l2_get_subdevdata(sd));

	वापस 0;
पूर्ण

अटल पूर्णांक tef6862_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *v)
अणु
	वापस v->index ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक tef6862_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा tef6862_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	अचिन्हित freq = f->frequency;
	u16 pll;
	u8 i2cmsg[3];
	पूर्णांक err;

	अगर (f->tuner != 0)
		वापस -EINVAL;

	freq = clamp(freq, TEF6862_LO_FREQ, TEF6862_HI_FREQ);
	pll = 1964 + ((freq - TEF6862_LO_FREQ) * 20) / FREQ_MUL;
	i2cmsg[0] = (MSA_MODE_PRESET << MSA_MODE_SHIFT) | WM_SUB_PLLM;
	i2cmsg[1] = (pll >> 8) & 0xff;
	i2cmsg[2] = pll & 0xff;

	err = i2c_master_send(client, i2cmsg, माप(i2cmsg));
	अगर (err != माप(i2cmsg))
		वापस err < 0 ? err : -EIO;

	state->freq = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक tef6862_g_frequency(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा tef6862_state *state = to_state(sd);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = state->freq;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops tef6862_tuner_ops = अणु
	.g_tuner = tef6862_g_tuner,
	.s_tuner = tef6862_s_tuner,
	.s_frequency = tef6862_s_frequency,
	.g_frequency = tef6862_g_frequency,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tef6862_ops = अणु
	.tuner = &tef6862_tuner_ops,
पूर्ण;

/*
 * Generic i2c probe
 * concerning the addresses: i2c wants 7 bit (without the r/w bit), so '>>1'
 */

अटल पूर्णांक tef6862_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tef6862_state *state;
	काष्ठा v4l2_subdev *sd;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = kzalloc(माप(काष्ठा tef6862_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	state->freq = TEF6862_LO_FREQ;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &tef6862_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक tef6862_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	kमुक्त(to_state(sd));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tef6862_id[] = अणु
	अणुDRIVER_NAME, 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tef6862_id);

अटल काष्ठा i2c_driver tef6862_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
	पूर्ण,
	.probe		= tef6862_probe,
	.हटाओ		= tef6862_हटाओ,
	.id_table	= tef6862_id,
पूर्ण;

module_i2c_driver(tef6862_driver);

MODULE_DESCRIPTION("TEF6862 Car Radio Enhanced Selectivity Tuner");
MODULE_AUTHOR("Mocean Laboratories");
MODULE_LICENSE("GPL v2");
