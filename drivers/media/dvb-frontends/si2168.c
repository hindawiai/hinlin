<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Silicon Lअसल Si2168 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#समावेश <linux/delay.h>

#समावेश "si2168_priv.h"

अटल स्थिर काष्ठा dvb_frontend_ops si2168_ops;

अटल व्योम cmd_init(काष्ठा si2168_cmd *cmd, स्थिर u8 *buf, पूर्णांक wlen, पूर्णांक rlen)
अणु
	स_नकल(cmd->args, buf, wlen);
	cmd->wlen = wlen;
	cmd->rlen = rlen;
पूर्ण

/* execute firmware command */
अटल पूर्णांक si2168_cmd_execute(काष्ठा i2c_client *client, काष्ठा si2168_cmd *cmd)
अणु
	काष्ठा si2168_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	mutex_lock(&dev->i2c_mutex);

	अगर (cmd->wlen) अणु
		/* ग_लिखो cmd and args क्रम firmware */
		ret = i2c_master_send(client, cmd->args, cmd->wlen);
		अगर (ret < 0) अणु
			जाओ err_mutex_unlock;
		पूर्ण अन्यथा अगर (ret != cmd->wlen) अणु
			ret = -EREMOTEIO;
			जाओ err_mutex_unlock;
		पूर्ण
	पूर्ण

	अगर (cmd->rlen) अणु
		/* रुको cmd execution terminate */
		#घोषणा TIMEOUT 70
		समयout = jअगरfies + msecs_to_jअगरfies(TIMEOUT);
		जबतक (!समय_after(jअगरfies, समयout)) अणु
			ret = i2c_master_recv(client, cmd->args, cmd->rlen);
			अगर (ret < 0) अणु
				जाओ err_mutex_unlock;
			पूर्ण अन्यथा अगर (ret != cmd->rlen) अणु
				ret = -EREMOTEIO;
				जाओ err_mutex_unlock;
			पूर्ण

			/* firmware पढ़ोy? */
			अगर ((cmd->args[0] >> 7) & 0x01)
				अवरोध;
		पूर्ण

		dev_dbg(&client->dev, "cmd execution took %d ms\n",
				jअगरfies_to_msecs(jअगरfies) -
				(jअगरfies_to_msecs(समयout) - TIMEOUT));

		/* error bit set? */
		अगर ((cmd->args[0] >> 6) & 0x01) अणु
			ret = -EREMOTEIO;
			जाओ err_mutex_unlock;
		पूर्ण

		अगर (!((cmd->args[0] >> 7) & 0x01)) अणु
			ret = -ETIMEDOUT;
			जाओ err_mutex_unlock;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->i2c_mutex);
	वापस 0;
err_mutex_unlock:
	mutex_unlock(&dev->i2c_mutex);
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2168_ts_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा si2168_dev *dev = i2c_get_clientdata(client);
	काष्ठा si2168_cmd cmd;
	पूर्णांक ret = 0;

	dev_dbg(&client->dev, "%s acquire: %d\n", __func__, acquire);

	/* set manual value */
	अगर (dev->ts_mode & SI2168_TS_CLK_MANUAL) अणु
		cmd_init(&cmd, "\x14\x00\x0d\x10\xe8\x03", 6, 4);
		ret = si2168_cmd_execute(client, &cmd);
		अगर (ret)
			वापस ret;
	पूर्ण
	/* set TS_MODE property */
	cmd_init(&cmd, "\x14\x00\x01\x10\x10\x00", 6, 4);
	अगर (dev->ts_mode & SI2168_TS_CLK_MANUAL)
		cmd.args[4] = SI2168_TS_CLK_MANUAL;
	अगर (acquire)
		cmd.args[4] |= dev->ts_mode;
	अन्यथा
		cmd.args[4] |= SI2168_TS_TRISTATE;
	अगर (dev->ts_घड़ी_gapped)
		cmd.args[4] |= 0x40;
	ret = si2168_cmd_execute(client, &cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक si2168_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा si2168_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1, uपंचांगp2;
	काष्ठा si2168_cmd cmd;

	*status = 0;

	अगर (!dev->active) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		cmd_init(&cmd, "\xa0\x01", 2, 13);
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		cmd_init(&cmd, "\x90\x01", 2, 9);
		अवरोध;
	हाल SYS_DVBT2:
		cmd_init(&cmd, "\x50\x01", 2, 14);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	चयन ((cmd.args[2] >> 1) & 0x03) अणु
	हाल 0x01:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		अवरोध;
	हाल 0x03:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI |
				FE_HAS_SYNC | FE_HAS_LOCK;
		अवरोध;
	पूर्ण

	dev->fe_status = *status;

	अगर (*status & FE_HAS_LOCK) अणु
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = cmd.args[3] * 1000 / 4;
	पूर्ण अन्यथा अणु
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	dev_dbg(&client->dev, "status=%02x args=%*ph\n",
			*status, cmd.rlen, cmd.args);

	/* BER */
	अगर (*status & FE_HAS_VITERBI) अणु
		cmd_init(&cmd, "\x82\x00", 2, 3);
		ret = si2168_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;

		/*
		 * Firmware वापसs [0, 255] mantissa and [0, 8] exponent.
		 * Convert to DVB API: mantissa * 10^(8 - exponent) / 10^8
		 */
		uपंचांगp = clamp(8 - cmd.args[1], 0, 8);
		क्रम (i = 0, uपंचांगp1 = 1; i < uपंचांगp; i++)
			uपंचांगp1 = uपंचांगp1 * 10;

		uपंचांगp1 = cmd.args[2] * uपंचांगp1;
		uपंचांगp2 = 100000000; /* 10^8 */

		dev_dbg(&client->dev,
			"post_bit_error=%u post_bit_count=%u ber=%u*10^-%u\न",
			uपंचांगp1, uपंचांगp2, cmd.args[2], cmd.args[1]);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += uपंचांगp1;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += uपंचांगp2;
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* UCB */
	अगर (*status & FE_HAS_SYNC) अणु
		cmd_init(&cmd, "\x84\x01", 2, 3);
		ret = si2168_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;

		uपंचांगp1 = cmd.args[2] << 8 | cmd.args[1] << 0;
		dev_dbg(&client->dev, "block_error=%u\n", uपंचांगp1);

		/* Someबार firmware वापसs bogus value */
		अगर (uपंचांगp1 == 0xffff)
			uपंचांगp1 = 0;

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue += uपंचांगp1;
	पूर्ण अन्यथा अणु
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2168_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा si2168_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	काष्ठा si2168_cmd cmd;
	u8 bandwidth, delivery_प्रणाली;

	dev_dbg(&client->dev,
			"delivery_system=%u modulation=%u frequency=%u bandwidth_hz=%u symbol_rate=%u inversion=%u stream_id=%u\n",
			c->delivery_प्रणाली, c->modulation, c->frequency,
			c->bandwidth_hz, c->symbol_rate, c->inversion,
			c->stream_id);

	अगर (!dev->active) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		delivery_प्रणाली = 0x20;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		delivery_प्रणाली = 0x30;
		अवरोध;
	हाल SYS_DVBT2:
		delivery_प्रणाली = 0x70;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (c->bandwidth_hz == 0) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण अन्यथा अगर (c->bandwidth_hz <= 2000000)
		bandwidth = 0x02;
	अन्यथा अगर (c->bandwidth_hz <= 5000000)
		bandwidth = 0x05;
	अन्यथा अगर (c->bandwidth_hz <= 6000000)
		bandwidth = 0x06;
	अन्यथा अगर (c->bandwidth_hz <= 7000000)
		bandwidth = 0x07;
	अन्यथा अगर (c->bandwidth_hz <= 8000000)
		bandwidth = 0x08;
	अन्यथा अगर (c->bandwidth_hz <= 9000000)
		bandwidth = 0x09;
	अन्यथा अगर (c->bandwidth_hz <= 10000000)
		bandwidth = 0x0a;
	अन्यथा
		bandwidth = 0x0f;

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (ret)
			जाओ err;
	पूर्ण

	cmd_init(&cmd, "\x88\x02\x02\x02\x02", 5, 5);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* that has no big effect */
	अगर (c->delivery_प्रणाली == SYS_DVBT)
		cmd_init(&cmd, "\x89\x21\x06\x11\xff\x98", 6, 3);
	अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBC_ANNEX_A)
		cmd_init(&cmd, "\x89\x21\x06\x11\x89\xf0", 6, 3);
	अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2)
		cmd_init(&cmd, "\x89\x21\x06\x11\x89\x20", 6, 3);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
		/* select PLP */
		cmd.args[0] = 0x52;
		cmd.args[1] = c->stream_id & 0xff;
		cmd.args[2] = c->stream_id == NO_STREAM_ID_FILTER ? 0 : 1;
		cmd.wlen = 3;
		cmd.rlen = 1;
		ret = si2168_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;
	पूर्ण

	cmd_init(&cmd, "\x51\x03", 2, 12);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x12\x08\x04", 3, 3);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x0c\x10\x12\x00", 6, 4);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x06\x10\x24\x00", 6, 4);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x07\x10\x00\x24", 6, 4);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x0a\x10\x00\x00", 6, 4);
	cmd.args[4] = delivery_प्रणाली | bandwidth;
	अगर (dev->spectral_inversion)
		cmd.args[5] |= 1;
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* set DVB-C symbol rate */
	अगर (c->delivery_प्रणाली == SYS_DVBC_ANNEX_A) अणु
		cmd_init(&cmd, "\x14\x00\x02\x11\x00\x00", 6, 4);
		cmd.args[4] = ((c->symbol_rate / 1000) >> 0) & 0xff;
		cmd.args[5] = ((c->symbol_rate / 1000) >> 8) & 0xff;
		ret = si2168_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;
	पूर्ण

	cmd_init(&cmd, "\x14\x00\x0f\x10\x10\x00", 6, 4);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x09\x10\xe3\x08", 6, 4);
	cmd.args[5] |= dev->ts_घड़ी_inv ? 0x00 : 0x10;
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x08\x10\xd7\x05", 6, 4);
	cmd.args[5] |= dev->ts_घड़ी_inv ? 0x00 : 0x10;
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x01\x12\x00\x00", 6, 4);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x14\x00\x01\x03\x0c\x00", 6, 4);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	cmd_init(&cmd, "\x85", 1, 1);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	dev->delivery_प्रणाली = c->delivery_प्रणाली;

	/* enable ts bus */
	ret = si2168_ts_bus_ctrl(fe, 1);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2168_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा si2168_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, len, reमुख्यing;
	स्थिर काष्ठा firmware *fw;
	काष्ठा si2168_cmd cmd;

	dev_dbg(&client->dev, "\n");

	/* initialize */
	cmd_init(&cmd, "\xc0\x12\x00\x0c\x00\x0d\x16\x00\x00\x00\x00\x00\x00",
		 13, 0);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	अगर (dev->warm) अणु
		/* resume */
		cmd_init(&cmd, "\xc0\x06\x08\x0f\x00\x20\x21\x01", 8, 1);
		ret = si2168_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;

		udelay(100);
		cmd_init(&cmd, "\x85", 1, 1);
		ret = si2168_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;

		जाओ warm;
	पूर्ण

	/* घातer up */
	cmd_init(&cmd, "\xc0\x06\x01\x0f\x00\x20\x20\x01", 8, 1);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* request the firmware, this will block and समयout */
	ret = request_firmware(&fw, dev->firmware_name, &client->dev);
	अगर (ret) अणु
		/* fallback mechanism to handle old name क्रम Si2168 B40 fw */
		अगर (dev->chip_id == SI2168_CHIP_ID_B40) अणु
			dev->firmware_name = SI2168_B40_FIRMWARE_FALLBACK;
			ret = request_firmware(&fw, dev->firmware_name,
					       &client->dev);
		पूर्ण

		अगर (ret == 0) अणु
			dev_notice(&client->dev,
					"please install firmware file '%s'\n",
					SI2168_B40_FIRMWARE);
		पूर्ण अन्यथा अणु
			dev_err(&client->dev,
					"firmware file '%s' not found\n",
					dev->firmware_name);
			जाओ err_release_firmware;
		पूर्ण
	पूर्ण

	dev_info(&client->dev, "downloading firmware from file '%s'\n",
			dev->firmware_name);

	अगर ((fw->size % 17 == 0) && (fw->data[0] > 5)) अणु
		/* firmware is in the new क्रमmat */
		क्रम (reमुख्यing = fw->size; reमुख्यing > 0; reमुख्यing -= 17) अणु
			len = fw->data[fw->size - reमुख्यing];
			अगर (len > SI2168_ARGLEN) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			cmd_init(&cmd, &fw->data[(fw->size - reमुख्यing) + 1],
				 len, 1);
			ret = si2168_cmd_execute(client, &cmd);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (fw->size % 8 == 0) अणु
		/* firmware is in the old क्रमmat */
		क्रम (reमुख्यing = fw->size; reमुख्यing > 0; reमुख्यing -= 8) अणु
			cmd_init(&cmd, &fw->data[fw->size - reमुख्यing], 8, 1);
			ret = si2168_cmd_execute(client, &cmd);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* bad or unknown firmware क्रमmat */
		ret = -EINVAL;
	पूर्ण

	अगर (ret) अणु
		dev_err(&client->dev, "firmware download failed %d\n", ret);
		जाओ err_release_firmware;
	पूर्ण

	release_firmware(fw);

	cmd_init(&cmd, "\x01\x01", 2, 1);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* query firmware version */
	cmd_init(&cmd, "\x11", 1, 10);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	dev->version = (cmd.args[9] + '@') << 24 | (cmd.args[6] - '0') << 16 |
		       (cmd.args[7] - '0') << 8 | (cmd.args[8]) << 0;
	dev_info(&client->dev, "firmware version: %c %d.%d.%d\n",
		 dev->version >> 24 & 0xff, dev->version >> 16 & 0xff,
		 dev->version >> 8 & 0xff, dev->version >> 0 & 0xff);

	/* set ts mode */
	ret = si2168_ts_bus_ctrl(fe, 1);
	अगर (ret)
		जाओ err;

	dev->warm = true;
warm:
	/* Init stats here to indicate which stats are supported */
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dev->active = true;

	वापस 0;
err_release_firmware:
	release_firmware(fw);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2168_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा si2168_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	काष्ठा si2168_cmd cmd;

	dev_dbg(&client->dev, "\n");

	dev->active = false;

	/* tri-state data bus */
	ret = si2168_ts_bus_ctrl(fe, 0);
	अगर (ret)
		जाओ err;

	/* Firmware later than B 4.0-11 loses warm state during sleep */
	अगर (dev->version > ('B' << 24 | 4 << 16 | 0 << 8 | 11 << 0))
		dev->warm = false;

	cmd_init(&cmd, "\x13", 1, 0);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2168_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 900;

	वापस 0;
पूर्ण

अटल पूर्णांक si2168_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा i2c_client *client = i2c_mux_priv(muxc);
	पूर्णांक ret;
	काष्ठा si2168_cmd cmd;

	/* खोलो I2C gate */
	cmd_init(&cmd, "\xc0\x0d\x01", 3, 0);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2168_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा i2c_client *client = i2c_mux_priv(muxc);
	पूर्णांक ret;
	काष्ठा si2168_cmd cmd;

	/* बंद I2C gate */
	cmd_init(&cmd, "\xc0\x0d\x00", 3, 0);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops si2168_ops = अणु
	.delsys = अणुSYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_Aपूर्ण,
	.info = अणु
		.name = "Silicon Labs Si2168",
		.frequency_min_hz      =  48 * MHz,
		.frequency_max_hz      = 870 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min       = 1000000,
		.symbol_rate_max       = 7200000,
		.caps =	FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_MUTE_TS |
			FE_CAN_2G_MODULATION |
			FE_CAN_MULTISTREAM
	पूर्ण,

	.get_tune_settings = si2168_get_tune_settings,

	.init = si2168_init,
	.sleep = si2168_sleep,

	.set_frontend = si2168_set_frontend,

	.पढ़ो_status = si2168_पढ़ो_status,
पूर्ण;

अटल पूर्णांक si2168_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा si2168_config *config = client->dev.platक्रमm_data;
	काष्ठा si2168_dev *dev;
	पूर्णांक ret;
	काष्ठा si2168_cmd cmd;

	dev_dbg(&client->dev, "\n");

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	i2c_set_clientdata(client, dev);
	mutex_init(&dev->i2c_mutex);

	/* Initialize */
	cmd_init(&cmd, "\xc0\x12\x00\x0c\x00\x0d\x16\x00\x00\x00\x00\x00\x00",
		 13, 0);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err_kमुक्त;

	/* Power up */
	cmd_init(&cmd, "\xc0\x06\x01\x0f\x00\x20\x20\x01", 8, 1);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err_kमुक्त;

	/* Query chip revision */
	cmd_init(&cmd, "\x02", 1, 13);
	ret = si2168_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err_kमुक्त;

	dev->chip_id = cmd.args[1] << 24 | cmd.args[2] << 16 |
		       cmd.args[3] << 8 | cmd.args[4] << 0;

	चयन (dev->chip_id) अणु
	हाल SI2168_CHIP_ID_A20:
		dev->firmware_name = SI2168_A20_FIRMWARE;
		अवरोध;
	हाल SI2168_CHIP_ID_A30:
		dev->firmware_name = SI2168_A30_FIRMWARE;
		अवरोध;
	हाल SI2168_CHIP_ID_B40:
		dev->firmware_name = SI2168_B40_FIRMWARE;
		अवरोध;
	हाल SI2168_CHIP_ID_D60:
		dev->firmware_name = SI2168_D60_FIRMWARE;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "unknown chip version Si21%d-%c%c%c\n",
			cmd.args[2], cmd.args[1], cmd.args[3], cmd.args[4]);
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	dev->version = (cmd.args[1]) << 24 | (cmd.args[3] - '0') << 16 |
		       (cmd.args[4] - '0') << 8 | (cmd.args[5]) << 0;

	/* create mux i2c adapter क्रम tuner */
	dev->muxc = i2c_mux_alloc(client->adapter, &client->dev,
				  1, 0, I2C_MUX_LOCKED,
				  si2168_select, si2168_deselect);
	अगर (!dev->muxc) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त;
	पूर्ण
	dev->muxc->priv = client;
	ret = i2c_mux_add_adapter(dev->muxc, 0, 0, 0);
	अगर (ret)
		जाओ err_kमुक्त;

	/* create dvb_frontend */
	स_नकल(&dev->fe.ops, &si2168_ops, माप(काष्ठा dvb_frontend_ops));
	dev->fe.demodulator_priv = client;
	*config->i2c_adapter = dev->muxc->adapter[0];
	*config->fe = &dev->fe;
	dev->ts_mode = config->ts_mode;
	dev->ts_घड़ी_inv = config->ts_घड़ी_inv;
	dev->ts_घड़ी_gapped = config->ts_घड़ी_gapped;
	dev->spectral_inversion = config->spectral_inversion;

	dev_info(&client->dev, "Silicon Labs Si2168-%c%d%d successfully identified\n",
		 dev->version >> 24 & 0xff, dev->version >> 16 & 0xff,
		 dev->version >> 8 & 0xff);
	dev_info(&client->dev, "firmware version: %c %d.%d.%d\n",
		 dev->version >> 24 & 0xff, dev->version >> 16 & 0xff,
		 dev->version >> 8 & 0xff, dev->version >> 0 & 0xff);

	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_warn(&client->dev, "probe failed = %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2168_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा si2168_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	i2c_mux_del_adapters(dev->muxc);

	dev->fe.ops.release = शून्य;
	dev->fe.demodulator_priv = शून्य;

	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si2168_id_table[] = अणु
	अणु"si2168", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si2168_id_table);

अटल काष्ठा i2c_driver si2168_driver = अणु
	.driver = अणु
		.name                = "si2168",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= si2168_probe,
	.हटाओ		= si2168_हटाओ,
	.id_table	= si2168_id_table,
पूर्ण;

module_i2c_driver(si2168_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Silicon Labs Si2168 DVB-T/T2/C demodulator driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(SI2168_A20_FIRMWARE);
MODULE_FIRMWARE(SI2168_A30_FIRMWARE);
MODULE_FIRMWARE(SI2168_B40_FIRMWARE);
MODULE_FIRMWARE(SI2168_D60_FIRMWARE);
