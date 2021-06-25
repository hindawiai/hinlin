<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Montage Technology DS3000 - DVBS/S2 Demodulator driver
    Copyright (C) 2009-2012 Konstantin Dimitrov <kosio.dimitrov@gmail.com>

    Copyright (C) 2009-2012 TurboSight.com

 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/firmware.h>

#समावेश <media/dvb_frontend.h>
#समावेश "ts2020.h"
#समावेश "ds3000.h"

अटल पूर्णांक debug;

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(args); \
	पूर्ण जबतक (0)

/* as of March 2009 current DS3000 firmware version is 1.78 */
/* DS3000 FW v1.78 MD5: a32d17910c4f370073f9346e71d34b80 */
#घोषणा DS3000_DEFAULT_FIRMWARE "dvb-fe-ds3000.fw"

#घोषणा DS3000_SAMPLE_RATE 96000 /* in kHz */

/* Register values to initialise the demod in DVB-S mode */
अटल u8 ds3000_dvbs_init_tab[] = अणु
	0x23, 0x05,
	0x08, 0x03,
	0x0c, 0x00,
	0x21, 0x54,
	0x25, 0x82,
	0x27, 0x31,
	0x30, 0x08,
	0x31, 0x40,
	0x32, 0x32,
	0x33, 0x35,
	0x35, 0xff,
	0x3a, 0x00,
	0x37, 0x10,
	0x38, 0x10,
	0x39, 0x02,
	0x42, 0x60,
	0x4a, 0x40,
	0x4b, 0x04,
	0x4d, 0x91,
	0x5d, 0xc8,
	0x50, 0x77,
	0x51, 0x77,
	0x52, 0x36,
	0x53, 0x36,
	0x56, 0x01,
	0x63, 0x43,
	0x64, 0x30,
	0x65, 0x40,
	0x68, 0x26,
	0x69, 0x4c,
	0x70, 0x20,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x40,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x60,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x80,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0xa0,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x1f,
	0x76, 0x00,
	0x77, 0xd1,
	0x78, 0x0c,
	0x79, 0x80,
	0x7f, 0x04,
	0x7c, 0x00,
	0x80, 0x86,
	0x81, 0xa6,
	0x85, 0x04,
	0xcd, 0xf4,
	0x90, 0x33,
	0xa0, 0x44,
	0xc0, 0x18,
	0xc3, 0x10,
	0xc4, 0x08,
	0xc5, 0x80,
	0xc6, 0x80,
	0xc7, 0x0a,
	0xc8, 0x1a,
	0xc9, 0x80,
	0xfe, 0x92,
	0xe0, 0xf8,
	0xe6, 0x8b,
	0xd0, 0x40,
	0xf8, 0x20,
	0xfa, 0x0f,
	0xfd, 0x20,
	0xad, 0x20,
	0xae, 0x07,
	0xb8, 0x00,
पूर्ण;

/* Register values to initialise the demod in DVB-S2 mode */
अटल u8 ds3000_dvbs2_init_tab[] = अणु
	0x23, 0x0f,
	0x08, 0x07,
	0x0c, 0x00,
	0x21, 0x54,
	0x25, 0x82,
	0x27, 0x31,
	0x30, 0x08,
	0x31, 0x32,
	0x32, 0x32,
	0x33, 0x35,
	0x35, 0xff,
	0x3a, 0x00,
	0x37, 0x10,
	0x38, 0x10,
	0x39, 0x02,
	0x42, 0x60,
	0x4a, 0x80,
	0x4b, 0x04,
	0x4d, 0x81,
	0x5d, 0x88,
	0x50, 0x36,
	0x51, 0x36,
	0x52, 0x36,
	0x53, 0x36,
	0x63, 0x60,
	0x64, 0x10,
	0x65, 0x10,
	0x68, 0x04,
	0x69, 0x29,
	0x70, 0x20,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x40,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x60,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x80,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0xa0,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x1f,
	0xa0, 0x44,
	0xc0, 0x08,
	0xc1, 0x10,
	0xc2, 0x08,
	0xc3, 0x10,
	0xc4, 0x08,
	0xc5, 0xf0,
	0xc6, 0xf0,
	0xc7, 0x0a,
	0xc8, 0x1a,
	0xc9, 0x80,
	0xca, 0x23,
	0xcb, 0x24,
	0xce, 0x74,
	0x90, 0x03,
	0x76, 0x80,
	0x77, 0x42,
	0x78, 0x0a,
	0x79, 0x80,
	0xad, 0x40,
	0xae, 0x07,
	0x7f, 0xd4,
	0x7c, 0x00,
	0x80, 0xa8,
	0x81, 0xda,
	0x7c, 0x01,
	0x80, 0xda,
	0x81, 0xec,
	0x7c, 0x02,
	0x80, 0xca,
	0x81, 0xeb,
	0x7c, 0x03,
	0x80, 0xba,
	0x81, 0xdb,
	0x85, 0x08,
	0x86, 0x00,
	0x87, 0x02,
	0x89, 0x80,
	0x8b, 0x44,
	0x8c, 0xaa,
	0x8a, 0x10,
	0xba, 0x00,
	0xf5, 0x04,
	0xfe, 0x44,
	0xd2, 0x32,
	0xb8, 0x00,
पूर्ण;

काष्ठा ds3000_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा ds3000_config *config;
	काष्ठा dvb_frontend frontend;
	/* previous uncorrected block counter क्रम DVB-S2 */
	u16 prevUCBS2;
पूर्ण;

अटल पूर्णांक ds3000_ग_लिखोreg(काष्ठा ds3000_state *state, पूर्णांक reg, पूर्णांक data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address,
		.flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक err;

	dprपूर्णांकk("%s: write reg 0x%02x, value 0x%02x\n", __func__, reg, data);

	err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1) अणु
		prपूर्णांकk(KERN_ERR "%s: writereg error(err == %i, reg == 0x%02x, value == 0x%02x)\n",
		       __func__, err, reg, data);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds3000_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;

	अगर (enable)
		ds3000_ग_लिखोreg(state, 0x03, 0x12);
	अन्यथा
		ds3000_ग_लिखोreg(state, 0x03, 0x02);

	वापस 0;
पूर्ण

/* I2C ग_लिखो क्रम 8k firmware load */
अटल पूर्णांक ds3000_ग_लिखोFW(काष्ठा ds3000_state *state, पूर्णांक reg,
				स्थिर u8 *data, u16 len)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा i2c_msg msg;
	u8 *buf;

	buf = kदो_स्मृति(33, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	*(buf) = reg;

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = 33;

	क्रम (i = 0; i < len; i += 32) अणु
		स_नकल(buf + 1, data + i, 32);

		dprपूर्णांकk("%s: write reg 0x%02x, len = %d\n", __func__, reg, len);

		ret = i2c_transfer(state->i2c, &msg, 1);
		अगर (ret != 1) अणु
			prपूर्णांकk(KERN_ERR "%s: write error(err == %i, reg == 0x%02x\n",
			       __func__, ret, reg);
			ret = -EREMOTEIO;
			जाओ error;
		पूर्ण
	पूर्ण
	ret = 0;

error:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक ds3000_पढ़ोreg(काष्ठा ds3000_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->config->demod_address,
			.flags = 0,
			.buf = b0,
			.len = 1
		पूर्ण, अणु
			.addr = state->config->demod_address,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 1
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		prपूर्णांकk(KERN_ERR "%s: reg=0x%x(error=%d)\n", __func__, reg, ret);
		वापस ret;
	पूर्ण

	dprपूर्णांकk("%s: read reg 0x%02x, value 0x%02x\n", __func__, reg, b1[0]);

	वापस b1[0];
पूर्ण

अटल पूर्णांक ds3000_load_firmware(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा firmware *fw);

अटल पूर्णांक ds3000_firmware_ondemand(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = 0;

	dprपूर्णांकk("%s()\n", __func__);

	ret = ds3000_पढ़ोreg(state, 0xb2);
	अगर (ret < 0)
		वापस ret;

	/* Load firmware */
	/* request the firmware, this will block until someone uploads it */
	prपूर्णांकk(KERN_INFO "%s: Waiting for firmware upload (%s)...\n", __func__,
				DS3000_DEFAULT_FIRMWARE);
	ret = request_firmware(&fw, DS3000_DEFAULT_FIRMWARE,
				state->i2c->dev.parent);
	prपूर्णांकk(KERN_INFO "%s: Waiting for firmware upload(2)...\n", __func__);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: No firmware uploaded (timeout or file not found?)\n",
		       __func__);
		वापस ret;
	पूर्ण

	ret = ds3000_load_firmware(fe, fw);
	अगर (ret)
		prपूर्णांकk("%s: Writing firmware to device failed\n", __func__);

	release_firmware(fw);

	dprपूर्णांकk("%s: Firmware upload %s\n", __func__,
			ret == 0 ? "complete" : "failed");

	वापस ret;
पूर्ण

अटल पूर्णांक ds3000_load_firmware(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	पूर्णांक ret = 0;

	dprपूर्णांकk("%s\n", __func__);
	dprपूर्णांकk("Firmware is %zu bytes (%02x %02x .. %02x %02x)\n",
			fw->size,
			fw->data[0],
			fw->data[1],
			fw->data[fw->size - 2],
			fw->data[fw->size - 1]);

	/* Begin the firmware load process */
	ds3000_ग_लिखोreg(state, 0xb2, 0x01);
	/* ग_लिखो the entire firmware */
	ret = ds3000_ग_लिखोFW(state, 0xb0, fw->data, fw->size);
	ds3000_ग_लिखोreg(state, 0xb2, 0x00);

	वापस ret;
पूर्ण

अटल पूर्णांक ds3000_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	u8 data;

	dprपूर्णांकk("%s(%d)\n", __func__, voltage);

	data = ds3000_पढ़ोreg(state, 0xa2);
	data |= 0x03; /* bit0 V/H, bit1 off/on */

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_18:
		data &= ~0x03;
		अवरोध;
	हाल SEC_VOLTAGE_13:
		data &= ~0x03;
		data |= 0x01;
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		अवरोध;
	पूर्ण

	ds3000_ग_लिखोreg(state, 0xa2, data);

	वापस 0;
पूर्ण

अटल पूर्णांक ds3000_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक lock;

	*status = 0;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		lock = ds3000_पढ़ोreg(state, 0xd1);
		अगर ((lock & 0x07) == 0x07)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC |
				FE_HAS_LOCK;

		अवरोध;
	हाल SYS_DVBS2:
		lock = ds3000_पढ़ोreg(state, 0x0d);
		अगर ((lock & 0x8f) == 0x8f)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC |
				FE_HAS_LOCK;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (state->config->set_lock_led)
		state->config->set_lock_led(fe, *status == 0 ? 0 : 1);

	dprपूर्णांकk("%s: status = 0x%02x\n", __func__, lock);

	वापस 0;
पूर्ण

/* पढ़ो DS3000 BER value */
अटल पूर्णांक ds3000_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32* ber)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 data;
	u32 ber_पढ़ोing, lpdc_frames;

	dprपूर्णांकk("%s()\n", __func__);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		/* set the number of bytes checked during
		BER estimation */
		ds3000_ग_लिखोreg(state, 0xf9, 0x04);
		/* पढ़ो BER estimation status */
		data = ds3000_पढ़ोreg(state, 0xf8);
		/* check अगर BER estimation is पढ़ोy */
		अगर ((data & 0x10) == 0) अणु
			/* this is the number of error bits,
			to calculate the bit error rate
			भागide to 8388608 */
			*ber = (ds3000_पढ़ोreg(state, 0xf7) << 8) |
				ds3000_पढ़ोreg(state, 0xf6);
			/* start counting error bits */
			/* need to be set twice
			otherwise it fails someबार */
			data |= 0x10;
			ds3000_ग_लिखोreg(state, 0xf8, data);
			ds3000_ग_लिखोreg(state, 0xf8, data);
		पूर्ण अन्यथा
			/* used to indicate that BER estimation
			is not पढ़ोy, i.e. BER is unknown */
			*ber = 0xffffffff;
		अवरोध;
	हाल SYS_DVBS2:
		/* पढ़ो the number of LPDC decoded frames */
		lpdc_frames = (ds3000_पढ़ोreg(state, 0xd7) << 16) |
				(ds3000_पढ़ोreg(state, 0xd6) << 8) |
				ds3000_पढ़ोreg(state, 0xd5);
		/* पढ़ो the number of packets with bad CRC */
		ber_पढ़ोing = (ds3000_पढ़ोreg(state, 0xf8) << 8) |
				ds3000_पढ़ोreg(state, 0xf7);
		अगर (lpdc_frames > 750) अणु
			/* clear LPDC frame counters */
			ds3000_ग_लिखोreg(state, 0xd1, 0x01);
			/* clear bad packets counter */
			ds3000_ग_लिखोreg(state, 0xf9, 0x01);
			/* enable bad packets counter */
			ds3000_ग_लिखोreg(state, 0xf9, 0x00);
			/* enable LPDC frame counters */
			ds3000_ग_लिखोreg(state, 0xd1, 0x00);
			*ber = ber_पढ़ोing;
		पूर्ण अन्यथा
			/* used to indicate that BER estimation is not पढ़ोy,
			i.e. BER is unknown */
			*ber = 0xffffffff;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds3000_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
						u16 *संकेत_strength)
अणु
	अगर (fe->ops.tuner_ops.get_rf_strength)
		fe->ops.tuner_ops.get_rf_strength(fe, संकेत_strength);

	वापस 0;
पूर्ण

/* calculate DS3000 snr value in dB */
अटल पूर्णांक ds3000_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 snr_पढ़ोing, snr_value;
	u32 dvbs2_संकेत_पढ़ोing, dvbs2_noise_पढ़ोing, पंचांगp;
	अटल स्थिर u16 dvbs_snr_tab[] = अणु /* 20 x Table (rounded up) */
		0x0000, 0x1b13, 0x2aea, 0x3627, 0x3ede, 0x45fe, 0x4c03,
		0x513a, 0x55d4, 0x59f2, 0x5dab, 0x6111, 0x6431, 0x6717,
		0x69c9, 0x6c4e, 0x6eac, 0x70e8, 0x7304, 0x7505
	पूर्ण;
	अटल स्थिर u16 dvbs2_snr_tab[] = अणु /* 80 x Table (rounded up) */
		0x0000, 0x0bc2, 0x12a3, 0x1785, 0x1b4e, 0x1e65, 0x2103,
		0x2347, 0x2546, 0x2710, 0x28ae, 0x2a28, 0x2b83, 0x2cc5,
		0x2df1, 0x2f09, 0x3010, 0x3109, 0x31f4, 0x32d2, 0x33a6,
		0x3470, 0x3531, 0x35ea, 0x369b, 0x3746, 0x37ea, 0x3888,
		0x3920, 0x39b3, 0x3a42, 0x3acc, 0x3b51, 0x3bd3, 0x3c51,
		0x3ccb, 0x3d42, 0x3db6, 0x3e27, 0x3e95, 0x3f00, 0x3f68,
		0x3fcf, 0x4033, 0x4094, 0x40f4, 0x4151, 0x41ac, 0x4206,
		0x425e, 0x42b4, 0x4308, 0x435b, 0x43ac, 0x43fc, 0x444a,
		0x4497, 0x44e2, 0x452d, 0x4576, 0x45bd, 0x4604, 0x4649,
		0x468e, 0x46d1, 0x4713, 0x4755, 0x4795, 0x47d4, 0x4813,
		0x4851, 0x488d, 0x48c9, 0x4904, 0x493f, 0x4978, 0x49b1,
		0x49e9, 0x4a20, 0x4a57
	पूर्ण;

	dprपूर्णांकk("%s()\n", __func__);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		snr_पढ़ोing = ds3000_पढ़ोreg(state, 0xff);
		snr_पढ़ोing /= 8;
		अगर (snr_पढ़ोing == 0)
			*snr = 0x0000;
		अन्यथा अणु
			अगर (snr_पढ़ोing > 20)
				snr_पढ़ोing = 20;
			snr_value = dvbs_snr_tab[snr_पढ़ोing - 1] * 10 / 23026;
			/* cook the value to be suitable क्रम szap-s2
			human पढ़ोable output */
			*snr = snr_value * 8 * 655;
		पूर्ण
		dprपूर्णांकk("%s: raw / cooked = 0x%02x / 0x%04x\n", __func__,
				snr_पढ़ोing, *snr);
		अवरोध;
	हाल SYS_DVBS2:
		dvbs2_noise_पढ़ोing = (ds3000_पढ़ोreg(state, 0x8c) & 0x3f) +
				(ds3000_पढ़ोreg(state, 0x8d) << 4);
		dvbs2_संकेत_पढ़ोing = ds3000_पढ़ोreg(state, 0x8e);
		पंचांगp = dvbs2_संकेत_पढ़ोing * dvbs2_संकेत_पढ़ोing >> 1;
		अगर (पंचांगp == 0) अणु
			*snr = 0x0000;
			वापस 0;
		पूर्ण
		अगर (dvbs2_noise_पढ़ोing == 0) अणु
			snr_value = 0x0013;
			/* cook the value to be suitable क्रम szap-s2
			human पढ़ोable output */
			*snr = 0xffff;
			वापस 0;
		पूर्ण
		अगर (पंचांगp > dvbs2_noise_पढ़ोing) अणु
			snr_पढ़ोing = पंचांगp / dvbs2_noise_पढ़ोing;
			अगर (snr_पढ़ोing > 80)
				snr_पढ़ोing = 80;
			snr_value = dvbs2_snr_tab[snr_पढ़ोing - 1] / 1000;
			/* cook the value to be suitable क्रम szap-s2
			human पढ़ोable output */
			*snr = snr_value * 5 * 655;
		पूर्ण अन्यथा अणु
			snr_पढ़ोing = dvbs2_noise_पढ़ोing / पंचांगp;
			अगर (snr_पढ़ोing > 80)
				snr_पढ़ोing = 80;
			*snr = -(dvbs2_snr_tab[snr_पढ़ोing - 1] / 1000);
		पूर्ण
		dprपूर्णांकk("%s: raw / cooked = 0x%02x / 0x%04x\n", __func__,
				snr_पढ़ोing, *snr);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* पढ़ो DS3000 uncorrected blocks */
अटल पूर्णांक ds3000_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 data;
	u16 _ucblocks;

	dprपूर्णांकk("%s()\n", __func__);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		*ucblocks = (ds3000_पढ़ोreg(state, 0xf5) << 8) |
				ds3000_पढ़ोreg(state, 0xf4);
		data = ds3000_पढ़ोreg(state, 0xf8);
		/* clear packet counters */
		data &= ~0x20;
		ds3000_ग_लिखोreg(state, 0xf8, data);
		/* enable packet counters */
		data |= 0x20;
		ds3000_ग_लिखोreg(state, 0xf8, data);
		अवरोध;
	हाल SYS_DVBS2:
		_ucblocks = (ds3000_पढ़ोreg(state, 0xe2) << 8) |
				ds3000_पढ़ोreg(state, 0xe1);
		अगर (_ucblocks > state->prevUCBS2)
			*ucblocks = _ucblocks - state->prevUCBS2;
		अन्यथा
			*ucblocks = state->prevUCBS2 - _ucblocks;
		state->prevUCBS2 = _ucblocks;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds3000_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	u8 data;

	dprपूर्णांकk("%s(%d)\n", __func__, tone);
	अगर ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) अणु
		prपूर्णांकk(KERN_ERR "%s: Invalid, tone=%d\n", __func__, tone);
		वापस -EINVAL;
	पूर्ण

	data = ds3000_पढ़ोreg(state, 0xa2);
	data &= ~0xc0;
	ds3000_ग_लिखोreg(state, 0xa2, data);

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		dprपूर्णांकk("%s: setting tone on\n", __func__);
		data = ds3000_पढ़ोreg(state, 0xa1);
		data &= ~0x43;
		data |= 0x04;
		ds3000_ग_लिखोreg(state, 0xa1, data);
		अवरोध;
	हाल SEC_TONE_OFF:
		dprपूर्णांकk("%s: setting tone off\n", __func__);
		data = ds3000_पढ़ोreg(state, 0xa2);
		data |= 0x80;
		ds3000_ग_लिखोreg(state, 0xa2, data);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds3000_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				काष्ठा dvb_diseqc_master_cmd *d)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	पूर्णांक i;
	u8 data;

	/* Dump DiSEqC message */
	dprपूर्णांकk("%s(", __func__);
	क्रम (i = 0 ; i < d->msg_len;) अणु
		dprपूर्णांकk("0x%02x", d->msg[i]);
		अगर (++i < d->msg_len)
			dprपूर्णांकk(", ");
	पूर्ण

	/* enable DiSEqC message send pin */
	data = ds3000_पढ़ोreg(state, 0xa2);
	data &= ~0xc0;
	ds3000_ग_लिखोreg(state, 0xa2, data);

	/* DiSEqC message */
	क्रम (i = 0; i < d->msg_len; i++)
		ds3000_ग_लिखोreg(state, 0xa3 + i, d->msg[i]);

	data = ds3000_पढ़ोreg(state, 0xa1);
	/* clear DiSEqC message length and status,
	enable DiSEqC message send */
	data &= ~0xf8;
	/* set DiSEqC mode, modulation active during 33 pulses,
	set DiSEqC message length */
	data |= ((d->msg_len - 1) << 3) | 0x07;
	ds3000_ग_लिखोreg(state, 0xa1, data);

	/* रुको up to 150ms क्रम DiSEqC transmission to complete */
	क्रम (i = 0; i < 15; i++) अणु
		data = ds3000_पढ़ोreg(state, 0xa1);
		अगर ((data & 0x40) == 0)
			अवरोध;
		msleep(10);
	पूर्ण

	/* DiSEqC समयout after 150ms */
	अगर (i == 15) अणु
		data = ds3000_पढ़ोreg(state, 0xa1);
		data &= ~0x80;
		data |= 0x40;
		ds3000_ग_लिखोreg(state, 0xa1, data);

		data = ds3000_पढ़ोreg(state, 0xa2);
		data &= ~0xc0;
		data |= 0x80;
		ds3000_ग_लिखोreg(state, 0xa2, data);

		वापस -ETIMEDOUT;
	पूर्ण

	data = ds3000_पढ़ोreg(state, 0xa2);
	data &= ~0xc0;
	data |= 0x80;
	ds3000_ग_लिखोreg(state, 0xa2, data);

	वापस 0;
पूर्ण

/* Send DiSEqC burst */
अटल पूर्णांक ds3000_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	पूर्णांक i;
	u8 data;

	dprपूर्णांकk("%s()\n", __func__);

	data = ds3000_पढ़ोreg(state, 0xa2);
	data &= ~0xc0;
	ds3000_ग_लिखोreg(state, 0xa2, data);

	/* DiSEqC burst */
	अगर (burst == SEC_MINI_A)
		/* Unmodulated tone burst */
		ds3000_ग_लिखोreg(state, 0xa1, 0x02);
	अन्यथा अगर (burst == SEC_MINI_B)
		/* Modulated tone burst */
		ds3000_ग_लिखोreg(state, 0xa1, 0x01);
	अन्यथा
		वापस -EINVAL;

	msleep(13);
	क्रम (i = 0; i < 5; i++) अणु
		data = ds3000_पढ़ोreg(state, 0xa1);
		अगर ((data & 0x40) == 0)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 5) अणु
		data = ds3000_पढ़ोreg(state, 0xa1);
		data &= ~0x80;
		data |= 0x40;
		ds3000_ग_लिखोreg(state, 0xa1, data);

		data = ds3000_पढ़ोreg(state, 0xa2);
		data &= ~0xc0;
		data |= 0x80;
		ds3000_ग_लिखोreg(state, 0xa2, data);

		वापस -ETIMEDOUT;
	पूर्ण

	data = ds3000_पढ़ोreg(state, 0xa2);
	data &= ~0xc0;
	data |= 0x80;
	ds3000_ग_लिखोreg(state, 0xa2, data);

	वापस 0;
पूर्ण

अटल व्योम ds3000_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;

	अगर (state->config->set_lock_led)
		state->config->set_lock_led(fe, 0);

	dprपूर्णांकk("%s\n", __func__);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ds3000_ops;

काष्ठा dvb_frontend *ds3000_attach(स्थिर काष्ठा ds3000_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा ds3000_state *state;
	पूर्णांक ret;

	dprपूर्णांकk("%s\n", __func__);

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->config = config;
	state->i2c = i2c;
	state->prevUCBS2 = 0;

	/* check अगर the demod is present */
	ret = ds3000_पढ़ोreg(state, 0x00) & 0xfe;
	अगर (ret != 0xe0) अणु
		kमुक्त(state);
		prपूर्णांकk(KERN_ERR "Invalid probe, probably not a DS3000\n");
		वापस शून्य;
	पूर्ण

	prपूर्णांकk(KERN_INFO "DS3000 chip version: %d.%d attached.\n",
			ds3000_पढ़ोreg(state, 0x02),
			ds3000_पढ़ोreg(state, 0x01));

	स_नकल(&state->frontend.ops, &ds3000_ops,
			माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/*
	 * Some devices like T480 starts with voltage on. Be sure
	 * to turn voltage off during init, as this can otherwise
	 * पूर्णांकerfere with Unicable SCR प्रणालीs.
	 */
	ds3000_set_voltage(&state->frontend, SEC_VOLTAGE_OFF);
	वापस &state->frontend;
पूर्ण
EXPORT_SYMBOL(ds3000_attach);

अटल पूर्णांक ds3000_set_carrier_offset(काष्ठा dvb_frontend *fe,
					s32 carrier_offset_khz)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	s32 पंचांगp;

	पंचांगp = carrier_offset_khz;
	पंचांगp *= 65536;
	पंचांगp = (2 * पंचांगp + DS3000_SAMPLE_RATE) / (2 * DS3000_SAMPLE_RATE);

	अगर (पंचांगp < 0)
		पंचांगp += 65536;

	ds3000_ग_लिखोreg(state, 0x5f, पंचांगp >> 8);
	ds3000_ग_लिखोreg(state, 0x5e, पंचांगp & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक ds3000_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	पूर्णांक i;
	क्रमागत fe_status status;
	s32 offset_khz;
	u32 frequency;
	u16 value;

	dprपूर्णांकk("%s() ", __func__);

	अगर (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);
	/* Tune */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* ds3000 global reset */
	ds3000_ग_लिखोreg(state, 0x07, 0x80);
	ds3000_ग_लिखोreg(state, 0x07, 0x00);
	/* ds3000 built-in uC reset */
	ds3000_ग_लिखोreg(state, 0xb2, 0x01);
	/* ds3000 software reset */
	ds3000_ग_लिखोreg(state, 0x00, 0x01);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		/* initialise the demod in DVB-S mode */
		क्रम (i = 0; i < माप(ds3000_dvbs_init_tab); i += 2)
			ds3000_ग_लिखोreg(state,
				ds3000_dvbs_init_tab[i],
				ds3000_dvbs_init_tab[i + 1]);
		value = ds3000_पढ़ोreg(state, 0xfe);
		value &= 0xc0;
		value |= 0x1b;
		ds3000_ग_लिखोreg(state, 0xfe, value);
		अवरोध;
	हाल SYS_DVBS2:
		/* initialise the demod in DVB-S2 mode */
		क्रम (i = 0; i < माप(ds3000_dvbs2_init_tab); i += 2)
			ds3000_ग_लिखोreg(state,
				ds3000_dvbs2_init_tab[i],
				ds3000_dvbs2_init_tab[i + 1]);
		अगर (c->symbol_rate >= 30000000)
			ds3000_ग_लिखोreg(state, 0xfe, 0x54);
		अन्यथा
			ds3000_ग_लिखोreg(state, 0xfe, 0x98);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* enable 27MHz घड़ी output */
	ds3000_ग_लिखोreg(state, 0x29, 0x80);
	/* enable ac coupling */
	ds3000_ग_लिखोreg(state, 0x25, 0x8a);

	अगर ((c->symbol_rate < ds3000_ops.info.symbol_rate_min) ||
			(c->symbol_rate > ds3000_ops.info.symbol_rate_max)) अणु
		dprपूर्णांकk("%s() symbol_rate %u out of range (%u ... %u)\n",
				__func__, c->symbol_rate,
				ds3000_ops.info.symbol_rate_min,
				ds3000_ops.info.symbol_rate_max);
		वापस -EINVAL;
	पूर्ण

	/* enhance symbol rate perक्रमmance */
	अगर ((c->symbol_rate / 1000) <= 5000) अणु
		value = 29777 / (c->symbol_rate / 1000) + 1;
		अगर (value % 2 != 0)
			value++;
		ds3000_ग_लिखोreg(state, 0xc3, 0x0d);
		ds3000_ग_लिखोreg(state, 0xc8, value);
		ds3000_ग_लिखोreg(state, 0xc4, 0x10);
		ds3000_ग_लिखोreg(state, 0xc7, 0x0e);
	पूर्ण अन्यथा अगर ((c->symbol_rate / 1000) <= 10000) अणु
		value = 92166 / (c->symbol_rate / 1000) + 1;
		अगर (value % 2 != 0)
			value++;
		ds3000_ग_लिखोreg(state, 0xc3, 0x07);
		ds3000_ग_लिखोreg(state, 0xc8, value);
		ds3000_ग_लिखोreg(state, 0xc4, 0x09);
		ds3000_ग_लिखोreg(state, 0xc7, 0x12);
	पूर्ण अन्यथा अगर ((c->symbol_rate / 1000) <= 20000) अणु
		value = 64516 / (c->symbol_rate / 1000) + 1;
		ds3000_ग_लिखोreg(state, 0xc3, value);
		ds3000_ग_लिखोreg(state, 0xc8, 0x0e);
		ds3000_ग_लिखोreg(state, 0xc4, 0x07);
		ds3000_ग_लिखोreg(state, 0xc7, 0x18);
	पूर्ण अन्यथा अणु
		value = 129032 / (c->symbol_rate / 1000) + 1;
		ds3000_ग_लिखोreg(state, 0xc3, value);
		ds3000_ग_लिखोreg(state, 0xc8, 0x0a);
		ds3000_ग_लिखोreg(state, 0xc4, 0x05);
		ds3000_ग_लिखोreg(state, 0xc7, 0x24);
	पूर्ण

	/* normalized symbol rate rounded to the बंदst पूर्णांकeger */
	value = (((c->symbol_rate / 1000) << 16) +
			(DS3000_SAMPLE_RATE / 2)) / DS3000_SAMPLE_RATE;
	ds3000_ग_लिखोreg(state, 0x61, value & 0x00ff);
	ds3000_ग_लिखोreg(state, 0x62, (value & 0xff00) >> 8);

	/* co-channel पूर्णांकerference cancellation disabled */
	ds3000_ग_लिखोreg(state, 0x56, 0x00);

	/* equalizer disabled */
	ds3000_ग_लिखोreg(state, 0x76, 0x00);

	/*ds3000_ग_लिखोreg(state, 0x08, 0x03);
	ds3000_ग_लिखोreg(state, 0xfd, 0x22);
	ds3000_ग_लिखोreg(state, 0x08, 0x07);
	ds3000_ग_लिखोreg(state, 0xfd, 0x42);
	ds3000_ग_लिखोreg(state, 0x08, 0x07);*/

	अगर (state->config->ci_mode) अणु
		चयन (c->delivery_प्रणाली) अणु
		हाल SYS_DVBS:
		शेष:
			ds3000_ग_लिखोreg(state, 0xfd, 0x80);
		अवरोध;
		हाल SYS_DVBS2:
			ds3000_ग_लिखोreg(state, 0xfd, 0x01);
			अवरोध;
		पूर्ण
	पूर्ण

	/* ds3000 out of software reset */
	ds3000_ग_लिखोreg(state, 0x00, 0x00);
	/* start ds3000 built-in uC */
	ds3000_ग_लिखोreg(state, 0xb2, 0x00);

	अगर (fe->ops.tuner_ops.get_frequency) अणु
		fe->ops.tuner_ops.get_frequency(fe, &frequency);
		offset_khz = frequency - c->frequency;
		ds3000_set_carrier_offset(fe, offset_khz);
	पूर्ण

	क्रम (i = 0; i < 30 ; i++) अणु
		ds3000_पढ़ो_status(fe, &status);
		अगर (status & FE_HAS_LOCK)
			अवरोध;

		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds3000_tune(काष्ठा dvb_frontend *fe,
			bool re_tune,
			अचिन्हित पूर्णांक mode_flags,
			अचिन्हित पूर्णांक *delay,
			क्रमागत fe_status *status)
अणु
	अगर (re_tune) अणु
		पूर्णांक ret = ds3000_set_frontend(fe);
		अगर (ret)
			वापस ret;
	पूर्ण

	*delay = HZ / 5;

	वापस ds3000_पढ़ो_status(fe, status);
पूर्ण

अटल क्रमागत dvbfe_algo ds3000_get_algo(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;

	अगर (state->config->set_lock_led)
		state->config->set_lock_led(fe, 0);

	dprपूर्णांकk("%s()\n", __func__);
	वापस DVBFE_ALGO_HW;
पूर्ण

/*
 * Initialise or wake up device
 *
 * Power config will reset and load initial firmware अगर required
 */
अटल पूर्णांक ds3000_initfe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ds3000_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	dprपूर्णांकk("%s()\n", __func__);
	/* hard reset */
	ds3000_ग_लिखोreg(state, 0x08, 0x01 | ds3000_पढ़ोreg(state, 0x08));
	msleep(1);

	/* Load the firmware अगर required */
	ret = ds3000_firmware_ondemand(fe);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Unable initialize firmware\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ds3000_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2 पूर्ण,
	.info = अणु
		.name = "Montage Technology DS3000",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		.frequency_stepsize_hz = 1011 * kHz,
		.frequency_tolerance_hz = 5 * MHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_2G_MODULATION |
			FE_CAN_QPSK | FE_CAN_RECOVER
	पूर्ण,

	.release = ds3000_release,

	.init = ds3000_initfe,
	.i2c_gate_ctrl = ds3000_i2c_gate_ctrl,
	.पढ़ो_status = ds3000_पढ़ो_status,
	.पढ़ो_ber = ds3000_पढ़ो_ber,
	.पढ़ो_संकेत_strength = ds3000_पढ़ो_संकेत_strength,
	.पढ़ो_snr = ds3000_पढ़ो_snr,
	.पढ़ो_ucblocks = ds3000_पढ़ो_ucblocks,
	.set_voltage = ds3000_set_voltage,
	.set_tone = ds3000_set_tone,
	.diseqc_send_master_cmd = ds3000_send_diseqc_msg,
	.diseqc_send_burst = ds3000_diseqc_send_burst,
	.get_frontend_algo = ds3000_get_algo,

	.set_frontend = ds3000_set_frontend,
	.tune = ds3000_tune,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Activates frontend debugging (default:0)");

MODULE_DESCRIPTION("DVB Frontend module for Montage Technology DS3000 hardware");
MODULE_AUTHOR("Konstantin Dimitrov <kosio.dimitrov@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(DS3000_DEFAULT_FIRMWARE);
