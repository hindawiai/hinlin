<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MaxLinear MxL301RF OFDM tuner driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

/*
 * NOTICE:
 * This driver is incomplete and lacks init/config of the chips,
 * as the necessary info is not disबंदd.
 * Other features like get_अगर_frequency() are missing as well.
 * It assumes that users of this driver (such as a PCI bridge of
 * DTV receiver cards) properly init and configure the chip
 * via I2C *beक्रमe* calling this driver's init() function.
 *
 * Currently, PT3 driver is the only one that uses this driver,
 * and contains init/config code in its firmware.
 * Thus some part of the code might be dependent on PT3 specअगरic config.
 */

#समावेश <linux/kernel.h>
#समावेश "mxl301rf.h"

काष्ठा mxl301rf_state अणु
	काष्ठा mxl301rf_config cfg;
	काष्ठा i2c_client *i2c;
पूर्ण;

अटल काष्ठा mxl301rf_state *cfg_to_state(काष्ठा mxl301rf_config *c)
अणु
	वापस container_of(c, काष्ठा mxl301rf_state, cfg);
पूर्ण

अटल पूर्णांक raw_ग_लिखो(काष्ठा mxl301rf_state *state, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;

	ret = i2c_master_send(state->i2c, buf, len);
	अगर (ret >= 0 && ret < len)
		ret = -EIO;
	वापस (ret == len) ? 0 : ret;
पूर्ण

अटल पूर्णांक reg_ग_लिखो(काष्ठा mxl301rf_state *state, u8 reg, u8 val)
अणु
	u8 buf[2] = अणु reg, val पूर्ण;

	वापस raw_ग_लिखो(state, buf, 2);
पूर्ण

अटल पूर्णांक reg_पढ़ो(काष्ठा mxl301rf_state *state, u8 reg, u8 *val)
अणु
	u8 wbuf[2] = अणु 0xfb, reg पूर्ण;
	पूर्णांक ret;

	ret = raw_ग_लिखो(state, wbuf, माप(wbuf));
	अगर (ret == 0)
		ret = i2c_master_recv(state->i2c, val, 1);
	अगर (ret >= 0 && ret < 1)
		ret = -EIO;
	वापस (ret == 1) ? 0 : ret;
पूर्ण

/* tuner_ops */

/* get RSSI and update propery cache, set to *out in % */
अटल पूर्णांक mxl301rf_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *out)
अणु
	काष्ठा mxl301rf_state *state;
	पूर्णांक ret;
	u8  rf_in1, rf_in2, rf_off1, rf_off2;
	u16 rf_in, rf_off;
	s64 level;
	काष्ठा dtv_fe_stats *rssi;

	rssi = &fe->dtv_property_cache.strength;
	rssi->len = 1;
	rssi->stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	*out = 0;

	state = fe->tuner_priv;
	ret = reg_ग_लिखो(state, 0x14, 0x01);
	अगर (ret < 0)
		वापस ret;
	usleep_range(1000, 2000);

	ret = reg_पढ़ो(state, 0x18, &rf_in1);
	अगर (ret == 0)
		ret = reg_पढ़ो(state, 0x19, &rf_in2);
	अगर (ret == 0)
		ret = reg_पढ़ो(state, 0xd6, &rf_off1);
	अगर (ret == 0)
		ret = reg_पढ़ो(state, 0xd7, &rf_off2);
	अगर (ret != 0)
		वापस ret;

	rf_in = (rf_in2 & 0x07) << 8 | rf_in1;
	rf_off = (rf_off2 & 0x0f) << 5 | (rf_off1 >> 3);
	level = rf_in - rf_off - (113 << 3); /* x8 dBm */
	level = level * 1000 / 8;
	rssi->stat[0].svalue = level;
	rssi->stat[0].scale = FE_SCALE_DECIBEL;
	/* *out = (level - min) * 100 / (max - min) */
	*out = (rf_in - rf_off + (1 << 9) - 1) * 100 / ((5 << 9) - 2);
	वापस 0;
पूर्ण

/* spur shअगरt parameters */
काष्ठा shf अणु
	u32	freq;		/* Channel center frequency */
	u32	ofst_th;	/* Offset frequency threshold */
	u8	shf_val;	/* Spur shअगरt value */
	u8	shf_dir;	/* Spur shअगरt direction */
पूर्ण;

अटल स्थिर काष्ठा shf shf_tab[] = अणु
	अणु  64500, 500, 0x92, 0x07 पूर्ण,
	अणु 191500, 300, 0xe2, 0x07 पूर्ण,
	अणु 205500, 500, 0x2c, 0x04 पूर्ण,
	अणु 212500, 500, 0x1e, 0x04 पूर्ण,
	अणु 226500, 500, 0xd4, 0x07 पूर्ण,
	अणु  99143, 500, 0x9c, 0x07 पूर्ण,
	अणु 173143, 500, 0xd4, 0x07 पूर्ण,
	अणु 191143, 300, 0xd4, 0x07 पूर्ण,
	अणु 207143, 500, 0xce, 0x07 पूर्ण,
	अणु 225143, 500, 0xce, 0x07 पूर्ण,
	अणु 243143, 500, 0xd4, 0x07 पूर्ण,
	अणु 261143, 500, 0xd4, 0x07 पूर्ण,
	अणु 291143, 500, 0xd4, 0x07 पूर्ण,
	अणु 339143, 500, 0x2c, 0x04 पूर्ण,
	अणु 117143, 500, 0x7a, 0x07 पूर्ण,
	अणु 135143, 300, 0x7a, 0x07 पूर्ण,
	अणु 153143, 500, 0x01, 0x07 पूर्ण
पूर्ण;

काष्ठा reg_val अणु
	u8 reg;
	u8 val;
पूर्ण __attribute__ ((__packed__));

अटल स्थिर काष्ठा reg_val set_idac[] = अणु
	अणु 0x0d, 0x00 पूर्ण,
	अणु 0x0c, 0x67 पूर्ण,
	अणु 0x6f, 0x89 पूर्ण,
	अणु 0x70, 0x0c पूर्ण,
	अणु 0x6f, 0x8a पूर्ण,
	अणु 0x70, 0x0e पूर्ण,
	अणु 0x6f, 0x8b पूर्ण,
	अणु 0x70, 0x1c पूर्ण,
पूर्ण;

अटल पूर्णांक mxl301rf_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा reg_val tune0[] = अणु
		अणु 0x13, 0x00 पूर्ण,		/* पात tuning */
		अणु 0x3b, 0xc0 पूर्ण,
		अणु 0x3b, 0x80 पूर्ण,
		अणु 0x10, 0x95 पूर्ण,		/* BW */
		अणु 0x1a, 0x05 पूर्ण,
		अणु 0x61, 0x00 पूर्ण,		/* spur shअगरt value (placeholder) */
		अणु 0x62, 0xa0 पूर्ण		/* spur shअगरt direction (placeholder) */
	पूर्ण;

	काष्ठा reg_val tune1[] = अणु
		अणु 0x11, 0x40 पूर्ण,		/* RF frequency L (placeholder) */
		अणु 0x12, 0x0e पूर्ण,		/* RF frequency H (placeholder) */
		अणु 0x13, 0x01 पूर्ण		/* start tune */
	पूर्ण;

	काष्ठा mxl301rf_state *state;
	u32 freq;
	u16 f;
	u32 पंचांगp, भाग;
	पूर्णांक i, ret;

	state = fe->tuner_priv;
	freq = fe->dtv_property_cache.frequency;

	/* spur shअगरt function (क्रम analog) */
	क्रम (i = 0; i < ARRAY_SIZE(shf_tab); i++) अणु
		अगर (freq >= (shf_tab[i].freq - shf_tab[i].ofst_th) * 1000 &&
		    freq <= (shf_tab[i].freq + shf_tab[i].ofst_th) * 1000) अणु
			tune0[5].val = shf_tab[i].shf_val;
			tune0[6].val = 0xa0 | shf_tab[i].shf_dir;
			अवरोध;
		पूर्ण
	पूर्ण
	ret = raw_ग_लिखो(state, (u8 *) tune0, माप(tune0));
	अगर (ret < 0)
		जाओ failed;
	usleep_range(3000, 4000);

	/* convert freq to 10.6 fixed poपूर्णांक भग्न [MHz] */
	f = freq / 1000000;
	पंचांगp = freq % 1000000;
	भाग = 1000000;
	क्रम (i = 0; i < 6; i++) अणु
		f <<= 1;
		भाग >>= 1;
		अगर (पंचांगp > भाग) अणु
			पंचांगp -= भाग;
			f |= 1;
		पूर्ण
	पूर्ण
	अगर (पंचांगp > 7812)
		f++;
	tune1[0].val = f & 0xff;
	tune1[1].val = f >> 8;
	ret = raw_ग_लिखो(state, (u8 *) tune1, माप(tune1));
	अगर (ret < 0)
		जाओ failed;
	msleep(31);

	ret = reg_ग_लिखो(state, 0x1a, 0x0d);
	अगर (ret < 0)
		जाओ failed;
	ret = raw_ग_लिखो(state, (u8 *) set_idac, माप(set_idac));
	अगर (ret < 0)
		जाओ failed;
	वापस 0;

failed:
	dev_warn(&state->i2c->dev, "(%s) failed. [adap%d-fe%d]\n",
		__func__, fe->dvb->num, fe->id);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reg_val standby_data[] = अणु
	अणु 0x01, 0x00 पूर्ण,
	अणु 0x13, 0x00 पूर्ण
पूर्ण;

अटल पूर्णांक mxl301rf_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl301rf_state *state;
	पूर्णांक ret;

	state = fe->tuner_priv;
	ret = raw_ग_लिखो(state, (u8 *)standby_data, माप(standby_data));
	अगर (ret < 0)
		dev_warn(&state->i2c->dev, "(%s) failed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
	वापस ret;
पूर्ण


/* init sequence is not खुला.
 * the parent must have init'ed the device.
 * just wake up here.
 */
अटल पूर्णांक mxl301rf_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl301rf_state *state;
	पूर्णांक ret;

	state = fe->tuner_priv;

	ret = reg_ग_लिखो(state, 0x01, 0x01);
	अगर (ret < 0) अणु
		dev_warn(&state->i2c->dev, "(%s) failed. [adap%d-fe%d]\n",
			 __func__, fe->dvb->num, fe->id);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* I2C driver functions */

अटल स्थिर काष्ठा dvb_tuner_ops mxl301rf_ops = अणु
	.info = अणु
		.name = "MaxLinear MxL301RF",

		.frequency_min_hz =  93 * MHz,
		.frequency_max_hz = 803 * MHz + 142857,
	पूर्ण,

	.init = mxl301rf_init,
	.sleep = mxl301rf_sleep,

	.set_params = mxl301rf_set_params,
	.get_rf_strength = mxl301rf_get_rf_strength,
पूर्ण;


अटल पूर्णांक mxl301rf_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mxl301rf_state *state;
	काष्ठा mxl301rf_config *cfg;
	काष्ठा dvb_frontend *fe;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->i2c = client;
	cfg = client->dev.platक्रमm_data;

	स_नकल(&state->cfg, cfg, माप(state->cfg));
	fe = cfg->fe;
	fe->tuner_priv = state;
	स_नकल(&fe->ops.tuner_ops, &mxl301rf_ops, माप(mxl301rf_ops));

	i2c_set_clientdata(client, &state->cfg);
	dev_info(&client->dev, "MaxLinear MxL301RF attached.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक mxl301rf_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mxl301rf_state *state;

	state = cfg_to_state(i2c_get_clientdata(client));
	state->cfg.fe->tuner_priv = शून्य;
	kमुक्त(state);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id mxl301rf_id[] = अणु
	अणु"mxl301rf", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mxl301rf_id);

अटल काष्ठा i2c_driver mxl301rf_driver = अणु
	.driver = अणु
		.name	= "mxl301rf",
	पूर्ण,
	.probe		= mxl301rf_probe,
	.हटाओ		= mxl301rf_हटाओ,
	.id_table	= mxl301rf_id,
पूर्ण;

module_i2c_driver(mxl301rf_driver);

MODULE_DESCRIPTION("MaxLinear MXL301RF tuner");
MODULE_AUTHOR("Akihiro TSUKADA");
MODULE_LICENSE("GPL");
