<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NXP TDA10071 + Conexant CX24118A DVB-S/S2 demodulator + tuner driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#समावेश "tda10071_priv.h"

अटल स्थिर काष्ठा dvb_frontend_ops tda10071_ops;

/*
 * XXX: regmap_update_bits() करोes not fit our needs as it करोes not support
 * partially अस्थिर रेजिस्टरs. Also it perक्रमms रेजिस्टर पढ़ो even mask is as
 * wide as रेजिस्टर value.
 */
/* ग_लिखो single रेजिस्टर with mask */
अटल पूर्णांक tda10071_wr_reg_mask(काष्ठा tda10071_dev *dev,
				u8 reg, u8 val, u8 mask)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	/* no need क्रम पढ़ो अगर whole reg is written */
	अगर (mask != 0xff) अणु
		ret = regmap_bulk_पढ़ो(dev->regmap, reg, &पंचांगp, 1);
		अगर (ret)
			वापस ret;

		val &= mask;
		पंचांगp &= ~mask;
		val |= पंचांगp;
	पूर्ण

	वापस regmap_bulk_ग_लिखो(dev->regmap, reg, &val, 1);
पूर्ण

/* execute firmware command */
अटल पूर्णांक tda10071_cmd_execute(काष्ठा tda10071_dev *dev,
	काष्ठा tda10071_cmd *cmd)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uiपंचांगp;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	mutex_lock(&dev->cmd_execute_mutex);

	/* ग_लिखो cmd and args क्रम firmware */
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x00, cmd->args, cmd->len);
	अगर (ret)
		जाओ error_mutex_unlock;

	/* start cmd execution */
	ret = regmap_ग_लिखो(dev->regmap, 0x1f, 1);
	अगर (ret)
		जाओ error_mutex_unlock;

	/* रुको cmd execution terminate */
	क्रम (i = 1000, uiपंचांगp = 1; i && uiपंचांगp; i--) अणु
		ret = regmap_पढ़ो(dev->regmap, 0x1f, &uiपंचांगp);
		अगर (ret)
			जाओ error_mutex_unlock;

		usleep_range(200, 5000);
	पूर्ण

	mutex_unlock(&dev->cmd_execute_mutex);
	dev_dbg(&client->dev, "loop=%d\n", i);

	अगर (i == 0) अणु
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	वापस ret;
error_mutex_unlock:
	mutex_unlock(&dev->cmd_execute_mutex);
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_set_tone(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_tone_mode fe_sec_tone_mode)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret;
	u8 tone;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	dev_dbg(&client->dev, "tone_mode=%d\n", fe_sec_tone_mode);

	चयन (fe_sec_tone_mode) अणु
	हाल SEC_TONE_ON:
		tone = 1;
		अवरोध;
	हाल SEC_TONE_OFF:
		tone = 0;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid fe_sec_tone_mode\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	cmd.args[0] = CMD_LNB_PCB_CONFIG;
	cmd.args[1] = 0;
	cmd.args[2] = 0x00;
	cmd.args[3] = 0x00;
	cmd.args[4] = tone;
	cmd.len = 5;
	ret = tda10071_cmd_execute(dev, &cmd);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_set_voltage(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_voltage fe_sec_voltage)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret;
	u8 voltage;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	dev_dbg(&client->dev, "voltage=%d\n", fe_sec_voltage);

	चयन (fe_sec_voltage) अणु
	हाल SEC_VOLTAGE_13:
		voltage = 0;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		voltage = 1;
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		voltage = 0;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid fe_sec_voltage\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	cmd.args[0] = CMD_LNB_SET_DC_LEVEL;
	cmd.args[1] = 0;
	cmd.args[2] = voltage;
	cmd.len = 3;
	ret = tda10071_cmd_execute(dev, &cmd);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_diseqc_send_master_cmd(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_diseqc_master_cmd *diseqc_cmd)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uiपंचांगp;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	dev_dbg(&client->dev, "msg_len=%d\n", diseqc_cmd->msg_len);

	अगर (diseqc_cmd->msg_len < 3 || diseqc_cmd->msg_len > 6) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* रुको LNB TX */
	क्रम (i = 500, uiपंचांगp = 0; i && !uiपंचांगp; i--) अणु
		ret = regmap_पढ़ो(dev->regmap, 0x47, &uiपंचांगp);
		अगर (ret)
			जाओ error;
		uiपंचांगp = (uiपंचांगp >> 0) & 1;
		usleep_range(10000, 20000);
	पूर्ण

	dev_dbg(&client->dev, "loop=%d\n", i);

	अगर (i == 0) अणु
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	ret = regmap_update_bits(dev->regmap, 0x47, 0x01, 0x00);
	अगर (ret)
		जाओ error;

	cmd.args[0] = CMD_LNB_SEND_DISEQC;
	cmd.args[1] = 0;
	cmd.args[2] = 0;
	cmd.args[3] = 0;
	cmd.args[4] = 2;
	cmd.args[5] = 0;
	cmd.args[6] = diseqc_cmd->msg_len;
	स_नकल(&cmd.args[7], diseqc_cmd->msg, diseqc_cmd->msg_len);
	cmd.len = 7 + diseqc_cmd->msg_len;
	ret = tda10071_cmd_execute(dev, &cmd);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_diseqc_recv_slave_reply(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_diseqc_slave_reply *reply)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uiपंचांगp;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	dev_dbg(&client->dev, "\n");

	/* रुको LNB RX */
	क्रम (i = 500, uiपंचांगp = 0; i && !uiपंचांगp; i--) अणु
		ret = regmap_पढ़ो(dev->regmap, 0x47, &uiपंचांगp);
		अगर (ret)
			जाओ error;
		uiपंचांगp = (uiपंचांगp >> 1) & 1;
		usleep_range(10000, 20000);
	पूर्ण

	dev_dbg(&client->dev, "loop=%d\n", i);

	अगर (i == 0) अणु
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	/* reply len */
	ret = regmap_पढ़ो(dev->regmap, 0x46, &uiपंचांगp);
	अगर (ret)
		जाओ error;

	reply->msg_len = uiपंचांगp & 0x1f; /* [4:0] */
	अगर (reply->msg_len > माप(reply->msg))
		reply->msg_len = माप(reply->msg); /* truncate API max */

	/* पढ़ो reply */
	cmd.args[0] = CMD_LNB_UPDATE_REPLY;
	cmd.args[1] = 0;
	cmd.len = 2;
	ret = tda10071_cmd_execute(dev, &cmd);
	अगर (ret)
		जाओ error;

	ret = regmap_bulk_पढ़ो(dev->regmap, cmd.len, reply->msg,
			       reply->msg_len);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_diseqc_send_burst(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_mini_cmd fe_sec_mini_cmd)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uiपंचांगp;
	u8 burst;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	dev_dbg(&client->dev, "fe_sec_mini_cmd=%d\n", fe_sec_mini_cmd);

	चयन (fe_sec_mini_cmd) अणु
	हाल SEC_MINI_A:
		burst = 0;
		अवरोध;
	हाल SEC_MINI_B:
		burst = 1;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid fe_sec_mini_cmd\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* रुको LNB TX */
	क्रम (i = 500, uiपंचांगp = 0; i && !uiपंचांगp; i--) अणु
		ret = regmap_पढ़ो(dev->regmap, 0x47, &uiपंचांगp);
		अगर (ret)
			जाओ error;
		uiपंचांगp = (uiपंचांगp >> 0) & 1;
		usleep_range(10000, 20000);
	पूर्ण

	dev_dbg(&client->dev, "loop=%d\n", i);

	अगर (i == 0) अणु
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	ret = regmap_update_bits(dev->regmap, 0x47, 0x01, 0x00);
	अगर (ret)
		जाओ error;

	cmd.args[0] = CMD_LNB_SEND_TONEBURST;
	cmd.args[1] = 0;
	cmd.args[2] = burst;
	cmd.len = 3;
	ret = tda10071_cmd_execute(dev, &cmd);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uiपंचांगp;
	u8 buf[8];

	*status = 0;

	अगर (!dev->warm) अणु
		ret = 0;
		जाओ error;
	पूर्ण

	ret = regmap_पढ़ो(dev->regmap, 0x39, &uiपंचांगp);
	अगर (ret)
		जाओ error;

	/* 0x39[0] tuner PLL */
	अगर (uiपंचांगp & 0x02) /* demod PLL */
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;
	अगर (uiपंचांगp & 0x04) /* viterbi or LDPC*/
		*status |= FE_HAS_VITERBI;
	अगर (uiपंचांगp & 0x08) /* RS or BCH */
		*status |= FE_HAS_SYNC | FE_HAS_LOCK;

	dev->fe_status = *status;

	/* संकेत strength */
	अगर (dev->fe_status & FE_HAS_SIGNAL) अणु
		cmd.args[0] = CMD_GET_AGCACC;
		cmd.args[1] = 0;
		cmd.len = 2;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;

		/* input घातer estimate dBm */
		ret = regmap_पढ़ो(dev->regmap, 0x50, &uiपंचांगp);
		अगर (ret)
			जाओ error;

		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = (पूर्णांक) (uiपंचांगp - 256) * 1000;
	पूर्ण अन्यथा अणु
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (dev->fe_status & FE_HAS_VITERBI) अणु
		/* Es/No */
		ret = regmap_bulk_पढ़ो(dev->regmap, 0x3a, buf, 2);
		अगर (ret)
			जाओ error;

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = (buf[0] << 8 | buf[1] << 0) * 100;
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* UCB/PER/BER */
	अगर (dev->fe_status & FE_HAS_LOCK) अणु
		/* TODO: report total bits/packets */
		u8 delivery_प्रणाली, reg, len;

		चयन (dev->delivery_प्रणाली) अणु
		हाल SYS_DVBS:
			reg = 0x4c;
			len = 8;
			delivery_प्रणाली = 1;
			अवरोध;
		हाल SYS_DVBS2:
			reg = 0x4d;
			len = 4;
			delivery_प्रणाली = 0;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		ret = regmap_पढ़ो(dev->regmap, reg, &uiपंचांगp);
		अगर (ret)
			जाओ error;

		अगर (dev->meas_count == uiपंचांगp) अणु
			dev_dbg(&client->dev, "meas not ready=%02x\n", uiपंचांगp);
			ret = 0;
			जाओ error;
		पूर्ण अन्यथा अणु
			dev->meas_count = uiपंचांगp;
		पूर्ण

		cmd.args[0] = CMD_BER_UPDATE_COUNTERS;
		cmd.args[1] = 0;
		cmd.args[2] = delivery_प्रणाली;
		cmd.len = 3;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;

		ret = regmap_bulk_पढ़ो(dev->regmap, cmd.len, buf, len);
		अगर (ret)
			जाओ error;

		अगर (dev->delivery_प्रणाली == SYS_DVBS) अणु
			u32 bit_error = buf[0] << 24 | buf[1] << 16 |
					buf[2] << 8 | buf[3] << 0;

			dev->dvbv3_ber = bit_error;
			dev->post_bit_error += bit_error;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
			dev->block_error += buf[4] << 8 | buf[5] << 0;
			c->block_error.stat[0].scale = FE_SCALE_COUNTER;
			c->block_error.stat[0].uvalue = dev->block_error;
		पूर्ण अन्यथा अणु
			dev->dvbv3_ber = buf[0] << 8 | buf[1] << 0;
			dev->post_bit_error += buf[0] << 8 | buf[1] << 0;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
			c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->cnr.stat[0].scale == FE_SCALE_DECIBEL)
		*snr = भाग_s64(c->cnr.stat[0].svalue, 100);
	अन्यथा
		*snr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10071_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	अचिन्हित पूर्णांक uiपंचांगp;

	अगर (c->strength.stat[0].scale == FE_SCALE_DECIBEL) अणु
		uiपंचांगp = भाग_s64(c->strength.stat[0].svalue, 1000) + 256;
		uiपंचांगp = clamp(uiपंचांगp, 181U, 236U); /* -75dBm - -20dBm */
		/* scale value to 0x0000-0xffff */
		*strength = (uiपंचांगp-181) * 0xffff / (236-181);
	पूर्ण अन्यथा अणु
		*strength = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda10071_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;

	*ber = dev->dvbv3_ber;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10071_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->block_error.stat[0].scale == FE_SCALE_COUNTER)
		*ucblocks = c->block_error.stat[0].uvalue;
	अन्यथा
		*ucblocks = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10071_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा tda10071_cmd cmd;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	u8 mode, rolloff, pilot, inversion, भाग;
	क्रमागत fe_modulation modulation;

	dev_dbg(&client->dev,
		"delivery_system=%d modulation=%d frequency=%u symbol_rate=%d inversion=%d pilot=%d rolloff=%d\n",
		c->delivery_प्रणाली, c->modulation, c->frequency, c->symbol_rate,
		c->inversion, c->pilot, c->rolloff);

	dev->delivery_प्रणाली = SYS_UNDEFINED;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	चयन (c->inversion) अणु
	हाल INVERSION_OFF:
		inversion = 1;
		अवरोध;
	हाल INVERSION_ON:
		inversion = 0;
		अवरोध;
	हाल INVERSION_AUTO:
		/* 2 = स्वतः; try first on then off
		 * 3 = स्वतः; try first off then on */
		inversion = 3;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid inversion\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		modulation = QPSK;
		rolloff = 0;
		pilot = 2;
		अवरोध;
	हाल SYS_DVBS2:
		modulation = c->modulation;

		चयन (c->rolloff) अणु
		हाल ROLLOFF_20:
			rolloff = 2;
			अवरोध;
		हाल ROLLOFF_25:
			rolloff = 1;
			अवरोध;
		हाल ROLLOFF_35:
			rolloff = 0;
			अवरोध;
		हाल ROLLOFF_AUTO:
		शेष:
			dev_dbg(&client->dev, "invalid rolloff\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		चयन (c->pilot) अणु
		हाल PILOT_OFF:
			pilot = 0;
			अवरोध;
		हाल PILOT_ON:
			pilot = 1;
			अवरोध;
		हाल PILOT_AUTO:
			pilot = 2;
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid pilot\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid delivery_system\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	क्रम (i = 0, mode = 0xff; i < ARRAY_SIZE(TDA10071_MODCOD); i++) अणु
		अगर (c->delivery_प्रणाली == TDA10071_MODCOD[i].delivery_प्रणाली &&
			modulation == TDA10071_MODCOD[i].modulation &&
			c->fec_inner == TDA10071_MODCOD[i].fec) अणु
			mode = TDA10071_MODCOD[i].val;
			dev_dbg(&client->dev, "mode found=%02x\n", mode);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mode == 0xff) अणु
		dev_dbg(&client->dev, "invalid parameter combination\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (c->symbol_rate <= 5000000)
		भाग = 14;
	अन्यथा
		भाग = 4;

	ret = regmap_ग_लिखो(dev->regmap, 0x81, भाग);
	अगर (ret)
		जाओ error;

	ret = regmap_ग_लिखो(dev->regmap, 0xe3, भाग);
	अगर (ret)
		जाओ error;

	cmd.args[0] = CMD_CHANGE_CHANNEL;
	cmd.args[1] = 0;
	cmd.args[2] = mode;
	cmd.args[3] = (c->frequency >> 16) & 0xff;
	cmd.args[4] = (c->frequency >>  8) & 0xff;
	cmd.args[5] = (c->frequency >>  0) & 0xff;
	cmd.args[6] = ((c->symbol_rate / 1000) >> 8) & 0xff;
	cmd.args[7] = ((c->symbol_rate / 1000) >> 0) & 0xff;
	cmd.args[8] = ((tda10071_ops.info.frequency_tolerance_hz / 1000) >> 8) & 0xff;
	cmd.args[9] = ((tda10071_ops.info.frequency_tolerance_hz / 1000) >> 0) & 0xff;
	cmd.args[10] = rolloff;
	cmd.args[11] = inversion;
	cmd.args[12] = pilot;
	cmd.args[13] = 0x00;
	cmd.args[14] = 0x00;
	cmd.len = 15;
	ret = tda10071_cmd_execute(dev, &cmd);
	अगर (ret)
		जाओ error;

	dev->delivery_प्रणाली = c->delivery_प्रणाली;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;
	u8 buf[5], पंचांगp;

	अगर (!dev->warm || !(dev->fe_status & FE_HAS_LOCK)) अणु
		ret = 0;
		जाओ error;
	पूर्ण

	ret = regmap_bulk_पढ़ो(dev->regmap, 0x30, buf, 5);
	अगर (ret)
		जाओ error;

	पंचांगp = buf[0] & 0x3f;
	क्रम (i = 0; i < ARRAY_SIZE(TDA10071_MODCOD); i++) अणु
		अगर (पंचांगp == TDA10071_MODCOD[i].val) अणु
			c->modulation = TDA10071_MODCOD[i].modulation;
			c->fec_inner = TDA10071_MODCOD[i].fec;
			c->delivery_प्रणाली = TDA10071_MODCOD[i].delivery_प्रणाली;
		पूर्ण
	पूर्ण

	चयन ((buf[1] >> 0) & 0x01) अणु
	हाल 0:
		c->inversion = INVERSION_ON;
		अवरोध;
	हाल 1:
		c->inversion = INVERSION_OFF;
		अवरोध;
	पूर्ण

	चयन ((buf[1] >> 7) & 0x01) अणु
	हाल 0:
		c->pilot = PILOT_OFF;
		अवरोध;
	हाल 1:
		c->pilot = PILOT_ON;
		अवरोध;
	पूर्ण

	c->frequency = (buf[2] << 16) | (buf[3] << 8) | (buf[4] << 0);

	ret = regmap_bulk_पढ़ो(dev->regmap, 0x52, buf, 3);
	अगर (ret)
		जाओ error;

	c->symbol_rate = ((buf[0] << 16) | (buf[1] << 8) | (buf[2] << 0)) * 1000;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret, i, len, reमुख्यing, fw_size;
	अचिन्हित पूर्णांक uiपंचांगp;
	स्थिर काष्ठा firmware *fw;
	u8 *fw_file = TDA10071_FIRMWARE;
	u8 पंचांगp, buf[4];
	काष्ठा tda10071_reg_val_mask tab[] = अणु
		अणु 0xcd, 0x00, 0x07 पूर्ण,
		अणु 0x80, 0x00, 0x02 पूर्ण,
		अणु 0xcd, 0x00, 0xc0 पूर्ण,
		अणु 0xce, 0x00, 0x1b पूर्ण,
		अणु 0x9d, 0x00, 0x01 पूर्ण,
		अणु 0x9d, 0x00, 0x02 पूर्ण,
		अणु 0x9e, 0x00, 0x01 पूर्ण,
		अणु 0x87, 0x00, 0x80 पूर्ण,
		अणु 0xce, 0x00, 0x08 पूर्ण,
		अणु 0xce, 0x00, 0x10 पूर्ण,
	पूर्ण;
	काष्ठा tda10071_reg_val_mask tab2[] = अणु
		अणु 0xf1, 0x70, 0xff पूर्ण,
		अणु 0x88, dev->pll_multiplier, 0x3f पूर्ण,
		अणु 0x89, 0x00, 0x10 पूर्ण,
		अणु 0x89, 0x10, 0x10 पूर्ण,
		अणु 0xc0, 0x01, 0x01 पूर्ण,
		अणु 0xc0, 0x00, 0x01 पूर्ण,
		अणु 0xe0, 0xff, 0xff पूर्ण,
		अणु 0xe0, 0x00, 0xff पूर्ण,
		अणु 0x96, 0x1e, 0x7e पूर्ण,
		अणु 0x8b, 0x08, 0x08 पूर्ण,
		अणु 0x8b, 0x00, 0x08 पूर्ण,
		अणु 0x8f, 0x1a, 0x7e पूर्ण,
		अणु 0x8c, 0x68, 0xff पूर्ण,
		अणु 0x8d, 0x08, 0xff पूर्ण,
		अणु 0x8e, 0x4c, 0xff पूर्ण,
		अणु 0x8f, 0x01, 0x01 पूर्ण,
		अणु 0x8b, 0x04, 0x04 पूर्ण,
		अणु 0x8b, 0x00, 0x04 पूर्ण,
		अणु 0x87, 0x05, 0x07 पूर्ण,
		अणु 0x80, 0x00, 0x20 पूर्ण,
		अणु 0xc8, 0x01, 0xff पूर्ण,
		अणु 0xb4, 0x47, 0xff पूर्ण,
		अणु 0xb5, 0x9c, 0xff पूर्ण,
		अणु 0xb6, 0x7d, 0xff पूर्ण,
		अणु 0xba, 0x00, 0x03 पूर्ण,
		अणु 0xb7, 0x47, 0xff पूर्ण,
		अणु 0xb8, 0x9c, 0xff पूर्ण,
		अणु 0xb9, 0x7d, 0xff पूर्ण,
		अणु 0xba, 0x00, 0x0c पूर्ण,
		अणु 0xc8, 0x00, 0xff पूर्ण,
		अणु 0xcd, 0x00, 0x04 पूर्ण,
		अणु 0xcd, 0x00, 0x20 पूर्ण,
		अणु 0xe8, 0x02, 0xff पूर्ण,
		अणु 0xcf, 0x20, 0xff पूर्ण,
		अणु 0x9b, 0xd7, 0xff पूर्ण,
		अणु 0x9a, 0x01, 0x03 पूर्ण,
		अणु 0xa8, 0x05, 0x0f पूर्ण,
		अणु 0xa8, 0x65, 0xf0 पूर्ण,
		अणु 0xa6, 0xa0, 0xf0 पूर्ण,
		अणु 0x9d, 0x50, 0xfc पूर्ण,
		अणु 0x9e, 0x20, 0xe0 पूर्ण,
		अणु 0xa3, 0x1c, 0x7c पूर्ण,
		अणु 0xd5, 0x03, 0x03 पूर्ण,
	पूर्ण;

	अगर (dev->warm) अणु
		/* warm state - wake up device from sleep */

		क्रम (i = 0; i < ARRAY_SIZE(tab); i++) अणु
			ret = tda10071_wr_reg_mask(dev, tab[i].reg,
				tab[i].val, tab[i].mask);
			अगर (ret)
				जाओ error;
		पूर्ण

		cmd.args[0] = CMD_SET_SLEEP_MODE;
		cmd.args[1] = 0;
		cmd.args[2] = 0;
		cmd.len = 3;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;
	पूर्ण अन्यथा अणु
		/* cold state - try to करोwnload firmware */

		/* request the firmware, this will block and समयout */
		ret = request_firmware(&fw, fw_file, &client->dev);
		अगर (ret) अणु
			dev_err(&client->dev,
				"did not find the firmware file '%s' (status %d). You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware\n",
				fw_file, ret);
			जाओ error;
		पूर्ण

		/* init */
		क्रम (i = 0; i < ARRAY_SIZE(tab2); i++) अणु
			ret = tda10071_wr_reg_mask(dev, tab2[i].reg,
				tab2[i].val, tab2[i].mask);
			अगर (ret)
				जाओ error_release_firmware;
		पूर्ण

		/*  करोwnload firmware */
		ret = regmap_ग_लिखो(dev->regmap, 0xe0, 0x7f);
		अगर (ret)
			जाओ error_release_firmware;

		ret = regmap_ग_लिखो(dev->regmap, 0xf7, 0x81);
		अगर (ret)
			जाओ error_release_firmware;

		ret = regmap_ग_लिखो(dev->regmap, 0xf8, 0x00);
		अगर (ret)
			जाओ error_release_firmware;

		ret = regmap_ग_लिखो(dev->regmap, 0xf9, 0x00);
		अगर (ret)
			जाओ error_release_firmware;

		dev_info(&client->dev,
			 "found a '%s' in cold state, will try to load a firmware\n",
			 tda10071_ops.info.name);
		dev_info(&client->dev, "downloading firmware from file '%s'\n",
			 fw_file);

		/* करो not करोwnload last byte */
		fw_size = fw->size - 1;

		क्रम (reमुख्यing = fw_size; reमुख्यing > 0;
			reमुख्यing -= (dev->i2c_wr_max - 1)) अणु
			len = reमुख्यing;
			अगर (len > (dev->i2c_wr_max - 1))
				len = (dev->i2c_wr_max - 1);

			ret = regmap_bulk_ग_लिखो(dev->regmap, 0xfa,
				(u8 *) &fw->data[fw_size - reमुख्यing], len);
			अगर (ret) अणु
				dev_err(&client->dev,
					"firmware download failed=%d\n", ret);
				जाओ error_release_firmware;
			पूर्ण
		पूर्ण
		release_firmware(fw);

		ret = regmap_ग_लिखो(dev->regmap, 0xf7, 0x0c);
		अगर (ret)
			जाओ error;

		ret = regmap_ग_लिखो(dev->regmap, 0xe0, 0x00);
		अगर (ret)
			जाओ error;

		/* रुको firmware start */
		msleep(250);

		/* firmware status */
		ret = regmap_पढ़ो(dev->regmap, 0x51, &uiपंचांगp);
		अगर (ret)
			जाओ error;

		अगर (uiपंचांगp) अणु
			dev_info(&client->dev, "firmware did not run\n");
			ret = -EFAULT;
			जाओ error;
		पूर्ण अन्यथा अणु
			dev->warm = true;
		पूर्ण

		cmd.args[0] = CMD_GET_FW_VERSION;
		cmd.len = 1;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;

		ret = regmap_bulk_पढ़ो(dev->regmap, cmd.len, buf, 4);
		अगर (ret)
			जाओ error;

		dev_info(&client->dev, "firmware version %d.%d.%d.%d\n",
			 buf[0], buf[1], buf[2], buf[3]);
		dev_info(&client->dev, "found a '%s' in warm state\n",
			 tda10071_ops.info.name);

		ret = regmap_bulk_पढ़ो(dev->regmap, 0x81, buf, 2);
		अगर (ret)
			जाओ error;

		cmd.args[0] = CMD_DEMOD_INIT;
		cmd.args[1] = ((dev->clk / 1000) >> 8) & 0xff;
		cmd.args[2] = ((dev->clk / 1000) >> 0) & 0xff;
		cmd.args[3] = buf[0];
		cmd.args[4] = buf[1];
		cmd.args[5] = dev->pll_multiplier;
		cmd.args[6] = dev->spec_inv;
		cmd.args[7] = 0x00;
		cmd.len = 8;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;

		अगर (dev->tuner_i2c_addr)
			पंचांगp = dev->tuner_i2c_addr;
		अन्यथा
			पंचांगp = 0x14;

		cmd.args[0] = CMD_TUNER_INIT;
		cmd.args[1] = 0x00;
		cmd.args[2] = 0x00;
		cmd.args[3] = 0x00;
		cmd.args[4] = 0x00;
		cmd.args[5] = पंचांगp;
		cmd.args[6] = 0x00;
		cmd.args[7] = 0x03;
		cmd.args[8] = 0x02;
		cmd.args[9] = 0x02;
		cmd.args[10] = 0x00;
		cmd.args[11] = 0x00;
		cmd.args[12] = 0x00;
		cmd.args[13] = 0x00;
		cmd.args[14] = 0x00;
		cmd.len = 15;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;

		cmd.args[0] = CMD_MPEG_CONFIG;
		cmd.args[1] = 0;
		cmd.args[2] = dev->ts_mode;
		cmd.args[3] = 0x00;
		cmd.args[4] = 0x04;
		cmd.args[5] = 0x00;
		cmd.len = 6;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;

		ret = regmap_update_bits(dev->regmap, 0xf0, 0x01, 0x01);
		अगर (ret)
			जाओ error;

		cmd.args[0] = CMD_LNB_CONFIG;
		cmd.args[1] = 0;
		cmd.args[2] = 150;
		cmd.args[3] = 3;
		cmd.args[4] = 22;
		cmd.args[5] = 1;
		cmd.args[6] = 1;
		cmd.args[7] = 30;
		cmd.args[8] = 30;
		cmd.args[9] = 30;
		cmd.args[10] = 30;
		cmd.len = 11;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;

		cmd.args[0] = CMD_BER_CONTROL;
		cmd.args[1] = 0;
		cmd.args[2] = 14;
		cmd.args[3] = 14;
		cmd.len = 4;
		ret = tda10071_cmd_execute(dev, &cmd);
		अगर (ret)
			जाओ error;
	पूर्ण

	/* init stats here in order संकेत app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस ret;
error_release_firmware:
	release_firmware(fw);
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10071_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा tda10071_cmd cmd;
	पूर्णांक ret, i;
	काष्ठा tda10071_reg_val_mask tab[] = अणु
		अणु 0xcd, 0x07, 0x07 पूर्ण,
		अणु 0x80, 0x02, 0x02 पूर्ण,
		अणु 0xcd, 0xc0, 0xc0 पूर्ण,
		अणु 0xce, 0x1b, 0x1b पूर्ण,
		अणु 0x9d, 0x01, 0x01 पूर्ण,
		अणु 0x9d, 0x02, 0x02 पूर्ण,
		अणु 0x9e, 0x01, 0x01 पूर्ण,
		अणु 0x87, 0x80, 0x80 पूर्ण,
		अणु 0xce, 0x08, 0x08 पूर्ण,
		अणु 0xce, 0x10, 0x10 पूर्ण,
	पूर्ण;

	अगर (!dev->warm) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	cmd.args[0] = CMD_SET_SLEEP_MODE;
	cmd.args[1] = 0;
	cmd.args[2] = 1;
	cmd.len = 3;
	ret = tda10071_cmd_execute(dev, &cmd);
	अगर (ret)
		जाओ error;

	क्रम (i = 0; i < ARRAY_SIZE(tab); i++) अणु
		ret = tda10071_wr_reg_mask(dev, tab[i].reg, tab[i].val,
			tab[i].mask);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 8000;
	s->step_size = 0;
	s->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10071_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2 पूर्ण,
	.info = अणु
		.name = "NXP TDA10071",
		.frequency_min_hz    =  950 * MHz,
		.frequency_max_hz    = 2150 * MHz,
		.frequency_tolerance_hz = 5 * MHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_8_9 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_RECOVER |
			FE_CAN_2G_MODULATION
	पूर्ण,

	.get_tune_settings = tda10071_get_tune_settings,

	.init = tda10071_init,
	.sleep = tda10071_sleep,

	.set_frontend = tda10071_set_frontend,
	.get_frontend = tda10071_get_frontend,

	.पढ़ो_status = tda10071_पढ़ो_status,
	.पढ़ो_snr = tda10071_पढ़ो_snr,
	.पढ़ो_संकेत_strength = tda10071_पढ़ो_संकेत_strength,
	.पढ़ो_ber = tda10071_पढ़ो_ber,
	.पढ़ो_ucblocks = tda10071_पढ़ो_ucblocks,

	.diseqc_send_master_cmd = tda10071_diseqc_send_master_cmd,
	.diseqc_recv_slave_reply = tda10071_diseqc_recv_slave_reply,
	.diseqc_send_burst = tda10071_diseqc_send_burst,

	.set_tone = tda10071_set_tone,
	.set_voltage = tda10071_set_voltage,
पूर्ण;

अटल काष्ठा dvb_frontend *tda10071_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा tda10071_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &dev->fe;
पूर्ण

अटल पूर्णांक tda10071_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tda10071_dev *dev;
	काष्ठा tda10071_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uiपंचांगp;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->client = client;
	mutex_init(&dev->cmd_execute_mutex);
	dev->clk = pdata->clk;
	dev->i2c_wr_max = pdata->i2c_wr_max;
	dev->ts_mode = pdata->ts_mode;
	dev->spec_inv = pdata->spec_inv;
	dev->pll_multiplier = pdata->pll_multiplier;
	dev->tuner_i2c_addr = pdata->tuner_i2c_addr;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* chip ID */
	ret = regmap_पढ़ो(dev->regmap, 0xff, &uiपंचांगp);
	अगर (ret)
		जाओ err_kमुक्त;
	अगर (uiपंचांगp != 0x0f) अणु
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	/* chip type */
	ret = regmap_पढ़ो(dev->regmap, 0xdd, &uiपंचांगp);
	अगर (ret)
		जाओ err_kमुक्त;
	अगर (uiपंचांगp != 0x00) अणु
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	/* chip version */
	ret = regmap_पढ़ो(dev->regmap, 0xfe, &uiपंचांगp);
	अगर (ret)
		जाओ err_kमुक्त;
	अगर (uiपंचांगp != 0x01) अणु
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&dev->fe.ops, &tda10071_ops, माप(काष्ठा dvb_frontend_ops));
	dev->fe.demodulator_priv = dev;
	i2c_set_clientdata(client, dev);

	/* setup callbacks */
	pdata->get_dvb_frontend = tda10071_get_dvb_frontend;

	dev_info(&client->dev, "NXP TDA10071 successfully identified\n");
	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tda10071_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tda10071_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tda10071_id_table[] = अणु
	अणु"tda10071_cx24118", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda10071_id_table);

अटल काष्ठा i2c_driver tda10071_driver = अणु
	.driver = अणु
		.name	= "tda10071",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= tda10071_probe,
	.हटाओ		= tda10071_हटाओ,
	.id_table	= tda10071_id_table,
पूर्ण;

module_i2c_driver(tda10071_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("NXP TDA10071 DVB-S/S2 demodulator driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(TDA10071_FIRMWARE);
