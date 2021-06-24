<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Silicon Lअसल Si2146/2147/2148/2157/2158 silicon tuner driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#समावेश "si2157_priv.h"

अटल स्थिर काष्ठा dvb_tuner_ops si2157_ops;

अटल पूर्णांक tuner_lock_debug;
module_param(tuner_lock_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(tuner_lock_debug, "if set, signal lock is briefly waited on after setting params");

/* execute firmware command */
अटल पूर्णांक si2157_cmd_execute(काष्ठा i2c_client *client, काष्ठा si2157_cmd *cmd)
अणु
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);
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
		#घोषणा TIMEOUT 80
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

		dev_dbg(&client->dev, "cmd execution took %d ms, status=%x\n",
			jअगरfies_to_msecs(jअगरfies) -
			(jअगरfies_to_msecs(समयout) - TIMEOUT),
			cmd->args[0]);

		अगर (!((cmd->args[0] >> 7) & 0x01)) अणु
			ret = -ETIMEDOUT;
			जाओ err_mutex_unlock;
		पूर्ण
		/* check error status bit */
		अगर (cmd->args[0] & 0x40) अणु
			ret = -EAGAIN;
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

अटल पूर्णांक si2157_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, len, reमुख्यing;
	काष्ठा si2157_cmd cmd;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	अचिन्हित पूर्णांक chip_id, xtal_trim;

	dev_dbg(&client->dev, "\n");

	/* Try to get Xtal trim property, to verअगरy tuner still running */
	स_नकल(cmd.args, "\x15\x00\x04\x02", 4);
	cmd.wlen = 4;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);

	xtal_trim = cmd.args[2] | (cmd.args[3] << 8);

	अगर (ret == 0 && xtal_trim < 16)
		जाओ warm;

	dev->अगर_frequency = 0; /* we no दीर्घer know current tuner state */

	/* घातer up */
	अगर (dev->chiptype == SI2157_CHIPTYPE_SI2146) अणु
		स_नकल(cmd.args, "\xc0\x05\x01\x00\x00\x0b\x00\x00\x01", 9);
		cmd.wlen = 9;
	पूर्ण अन्यथा अगर (dev->chiptype == SI2157_CHIPTYPE_SI2141) अणु
		स_नकल(cmd.args, "\xc0\x00\x0d\x0e\x00\x01\x01\x01\x01\x03", 10);
		cmd.wlen = 10;
	पूर्ण अन्यथा अणु
		स_नकल(cmd.args, "\xc0\x00\x0c\x00\x00\x01\x01\x01\x01\x01\x01\x02\x00\x00\x01", 15);
		cmd.wlen = 15;
	पूर्ण
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret && (dev->chiptype != SI2157_CHIPTYPE_SI2141 || ret != -EAGAIN))
		जाओ err;

	/* Si2141 needs a second command beक्रमe it answers the revision query */
	अगर (dev->chiptype == SI2157_CHIPTYPE_SI2141) अणु
		स_नकल(cmd.args, "\xc0\x08\x01\x02\x00\x00\x01", 7);
		cmd.wlen = 7;
		ret = si2157_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (dev->करोnt_load_firmware) अणु
		dev_info(&client->dev, "device is buggy, skipping firmware download\n");
		जाओ skip_fw_करोwnload;
	पूर्ण

	/* query chip revision */
	स_नकल(cmd.args, "\x02", 1);
	cmd.wlen = 1;
	cmd.rlen = 13;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	chip_id = cmd.args[1] << 24 | cmd.args[2] << 16 | cmd.args[3] << 8 |
			cmd.args[4] << 0;

	#घोषणा SI2177_A30 ('A' << 24 | 77 << 16 | '3' << 8 | '0' << 0)
	#घोषणा SI2158_A20 ('A' << 24 | 58 << 16 | '2' << 8 | '0' << 0)
	#घोषणा SI2148_A20 ('A' << 24 | 48 << 16 | '2' << 8 | '0' << 0)
	#घोषणा SI2157_A30 ('A' << 24 | 57 << 16 | '3' << 8 | '0' << 0)
	#घोषणा SI2147_A30 ('A' << 24 | 47 << 16 | '3' << 8 | '0' << 0)
	#घोषणा SI2146_A10 ('A' << 24 | 46 << 16 | '1' << 8 | '0' << 0)
	#घोषणा SI2141_A10 ('A' << 24 | 41 << 16 | '1' << 8 | '0' << 0)

	चयन (chip_id) अणु
	हाल SI2158_A20:
	हाल SI2148_A20:
		fw_name = SI2158_A20_FIRMWARE;
		अवरोध;
	हाल SI2141_A10:
		fw_name = SI2141_A10_FIRMWARE;
		अवरोध;
	हाल SI2177_A30:
		fw_name = SI2157_A30_FIRMWARE;
		अवरोध;
	हाल SI2157_A30:
	हाल SI2147_A30:
	हाल SI2146_A10:
		fw_name = शून्य;
		अवरोध;
	शेष:
		dev_err(&client->dev, "unknown chip version Si21%d-%c%c%c\n",
				cmd.args[2], cmd.args[1],
				cmd.args[3], cmd.args[4]);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "found a 'Silicon Labs Si21%d-%c%c%c'\n",
			cmd.args[2], cmd.args[1], cmd.args[3], cmd.args[4]);

	अगर (fw_name == शून्य)
		जाओ skip_fw_करोwnload;

	/* request the firmware, this will block and समयout */
	ret = request_firmware(&fw, fw_name, &client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "firmware file '%s' not found\n",
				fw_name);
		जाओ err;
	पूर्ण

	/* firmware should be n chunks of 17 bytes */
	अगर (fw->size % 17 != 0) अणु
		dev_err(&client->dev, "firmware file '%s' is invalid\n",
				fw_name);
		ret = -EINVAL;
		जाओ err_release_firmware;
	पूर्ण

	dev_info(&client->dev, "downloading firmware from file '%s'\n",
			fw_name);

	क्रम (reमुख्यing = fw->size; reमुख्यing > 0; reमुख्यing -= 17) अणु
		len = fw->data[fw->size - reमुख्यing];
		अगर (len > SI2157_ARGLEN) अणु
			dev_err(&client->dev, "Bad firmware length\n");
			ret = -EINVAL;
			जाओ err_release_firmware;
		पूर्ण
		स_नकल(cmd.args, &fw->data[(fw->size - reमुख्यing) + 1], len);
		cmd.wlen = len;
		cmd.rlen = 1;
		ret = si2157_cmd_execute(client, &cmd);
		अगर (ret) अणु
			dev_err(&client->dev, "firmware download failed %d\n",
					ret);
			जाओ err_release_firmware;
		पूर्ण
	पूर्ण

	release_firmware(fw);

skip_fw_करोwnload:
	/* reboot the tuner with new firmware? */
	स_नकल(cmd.args, "\x01\x01", 2);
	cmd.wlen = 2;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* query firmware version */
	स_नकल(cmd.args, "\x11", 1);
	cmd.wlen = 1;
	cmd.rlen = 10;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	dev_info(&client->dev, "firmware version: %c.%c.%d\n",
			cmd.args[6], cmd.args[7], cmd.args[8]);

	/* enable tuner status flags */
	स_नकल(cmd.args, "\x14\x00\x01\x05\x01\x00", 6);
	cmd.wlen = 6;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	स_नकल(cmd.args, "\x14\x00\x01\x06\x01\x00", 6);
	cmd.wlen = 6;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	स_नकल(cmd.args, "\x14\x00\x01\x07\x01\x00", 6);
	cmd.wlen = 6;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;
warm:
	/* init statistics in order संकेत app which are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	/* start statistics polling */
	schedule_delayed_work(&dev->stat_work, msecs_to_jअगरfies(1000));

	dev->active = true;
	वापस 0;
err_release_firmware:
	release_firmware(fw);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2157_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	काष्ठा si2157_cmd cmd;

	dev_dbg(&client->dev, "\n");

	dev->active = false;

	/* stop statistics polling */
	cancel_delayed_work_sync(&dev->stat_work);

	/* standby */
	स_नकल(cmd.args, "\x16\x00", 2);
	cmd.wlen = 2;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2157_tune_रुको(काष्ठा i2c_client *client, u8 is_digital)
अणु
#घोषणा TUN_TIMEOUT 40
#घोषणा DIG_TIMEOUT 30
#घोषणा ANALOG_TIMEOUT 150
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ start_समय;
	u8 रुको_status;
	u8  tune_lock_mask;

	अगर (is_digital)
		tune_lock_mask = 0x04;
	अन्यथा
		tune_lock_mask = 0x02;

	mutex_lock(&dev->i2c_mutex);

	/* रुको tuner command complete */
	start_समय = jअगरfies;
	समयout = start_समय + msecs_to_jअगरfies(TUN_TIMEOUT);
	जबतक (1) अणु
		ret = i2c_master_recv(client, &रुको_status,
				      माप(रुको_status));
		अगर (ret < 0) अणु
			जाओ err_mutex_unlock;
		पूर्ण अन्यथा अगर (ret != माप(रुको_status)) अणु
			ret = -EREMOTEIO;
			जाओ err_mutex_unlock;
		पूर्ण

		अगर (समय_after(jअगरfies, समयout))
			अवरोध;

		/* tuner करोne? */
		अगर ((रुको_status & 0x81) == 0x81)
			अवरोध;
		usleep_range(5000, 10000);
	पूर्ण

	dev_dbg(&client->dev, "tuning took %d ms, status=0x%x\n",
		jअगरfies_to_msecs(jअगरfies) - jअगरfies_to_msecs(start_समय),
		रुको_status);

	/* अगर we tuned ok, रुको a bit क्रम tuner lock */
	अगर (tuner_lock_debug && (रुको_status & 0x81) == 0x81) अणु
		अगर (is_digital)
			समयout = jअगरfies + msecs_to_jअगरfies(DIG_TIMEOUT);
		अन्यथा
			समयout = jअगरfies + msecs_to_jअगरfies(ANALOG_TIMEOUT);

		जबतक (!समय_after(jअगरfies, समयout)) अणु
			ret = i2c_master_recv(client, &रुको_status,
					      माप(रुको_status));
			अगर (ret < 0) अणु
				जाओ err_mutex_unlock;
			पूर्ण अन्यथा अगर (ret != माप(रुको_status)) अणु
				ret = -EREMOTEIO;
				जाओ err_mutex_unlock;
			पूर्ण

			/* tuner locked? */
			अगर (रुको_status & tune_lock_mask)
				अवरोध;
			usleep_range(5000, 10000);
		पूर्ण

		dev_dbg(&client->dev, "tuning+lock took %d ms, status=0x%x\n",
			jअगरfies_to_msecs(jअगरfies) - jअगरfies_to_msecs(start_समय),
			रुको_status);
	पूर्ण

	अगर ((रुको_status & 0xc0) != 0x80) अणु
		ret = -ETIMEDOUT;
		जाओ err_mutex_unlock;
	पूर्ण

	mutex_unlock(&dev->i2c_mutex);
	वापस 0;

err_mutex_unlock:
	mutex_unlock(&dev->i2c_mutex);
	dev_err(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2157_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	काष्ठा si2157_cmd cmd;
	u8 bandwidth, delivery_प्रणाली;
	u32 अगर_frequency = 5000000;

	dev_dbg(&client->dev,
			"delivery_system=%d frequency=%u bandwidth_hz=%u\n",
			c->delivery_प्रणाली, c->frequency, c->bandwidth_hz);

	अगर (!dev->active) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	अगर (c->bandwidth_hz <= 6000000)
		bandwidth = 0x06;
	अन्यथा अगर (c->bandwidth_hz <= 7000000)
		bandwidth = 0x07;
	अन्यथा अगर (c->bandwidth_hz <= 8000000)
		bandwidth = 0x08;
	अन्यथा
		bandwidth = 0x0f;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
			delivery_प्रणाली = 0x00;
			अगर_frequency = 3250000;
			अवरोध;
	हाल SYS_DVBC_ANNEX_B:
			delivery_प्रणाली = 0x10;
			अगर_frequency = 4000000;
			अवरोध;
	हाल SYS_DVBT:
	हाल SYS_DVBT2: /* it seems DVB-T and DVB-T2 both are 0x20 here */
			delivery_प्रणाली = 0x20;
			अवरोध;
	हाल SYS_DVBC_ANNEX_A:
			delivery_प्रणाली = 0x30;
			अवरोध;
	शेष:
			ret = -EINVAL;
			जाओ err;
	पूर्ण

	स_नकल(cmd.args, "\x14\x00\x03\x07\x00\x00", 6);
	cmd.args[4] = delivery_प्रणाली | bandwidth;
	अगर (dev->inversion)
		cmd.args[5] = 0x01;
	cmd.wlen = 6;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	अगर (dev->chiptype == SI2157_CHIPTYPE_SI2146)
		स_नकल(cmd.args, "\x14\x00\x02\x07\x00\x01", 6);
	अन्यथा
		स_नकल(cmd.args, "\x14\x00\x02\x07\x00\x00", 6);
	cmd.args[4] = dev->अगर_port;
	cmd.wlen = 6;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* set digital अगर frequency अगर needed */
	अगर (अगर_frequency != dev->अगर_frequency) अणु
		स_नकल(cmd.args, "\x14\x00\x06\x07", 4);
		cmd.args[4] = (अगर_frequency / 1000) & 0xff;
		cmd.args[5] = ((अगर_frequency / 1000) >> 8) & 0xff;
		cmd.wlen = 6;
		cmd.rlen = 4;
		ret = si2157_cmd_execute(client, &cmd);
		अगर (ret)
			जाओ err;

		dev->अगर_frequency = अगर_frequency;
	पूर्ण

	/* set digital frequency */
	स_नकल(cmd.args, "\x41\x00\x00\x00\x00\x00\x00\x00", 8);
	cmd.args[4] = (c->frequency >>  0) & 0xff;
	cmd.args[5] = (c->frequency >>  8) & 0xff;
	cmd.args[6] = (c->frequency >> 16) & 0xff;
	cmd.args[7] = (c->frequency >> 24) & 0xff;
	cmd.wlen = 8;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	dev->bandwidth = bandwidth;
	dev->frequency = c->frequency;

	si2157_tune_रुको(client, 1); /* रुको to complete, ignore any errors */

	वापस 0;
err:
	dev->bandwidth = 0;
	dev->frequency = 0;
	dev->अगर_frequency = 0;
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2157_set_analog_params(काष्ठा dvb_frontend *fe,
				    काष्ठा analog_parameters *params)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);
	अक्षर *std; /* क्रम debugging */
	पूर्णांक ret;
	काष्ठा si2157_cmd cmd;
	u32 bandwidth = 0;
	u32 अगर_frequency = 0;
	u32 freq = 0;
	u64 पंचांगp_lval = 0;
	u8 प्रणाली = 0;
	u8 color = 0;    /* 0=NTSC/PAL, 0x10=SECAM */
	u8 invert_analog = 1; /* analog tuner spectrum; 0=normal, 1=inverted */

	अगर (dev->chiptype != SI2157_CHIPTYPE_SI2157) अणु
		dev_info(&client->dev, "Analog tuning not supported for chiptype=%u\n",
			 dev->chiptype);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (!dev->active)
		si2157_init(fe);

	अगर (!dev->active) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण
	अगर (params->mode == V4L2_TUNER_RADIO) अणु
	/*
	 * std = "fm";
	 * bandwidth = 1700000; //best can करो क्रम FM, AGC will be a mess though
	 * अगर_frequency = 1250000;  //HVR-225x(saa7164), HVR-12xx(cx23885)
	 * अगर_frequency = 6600000;  //HVR-9xx(cx231xx)
	 * अगर_frequency = 5500000;  //HVR-19xx(pvrusb2)
	 */
		dev_err(&client->dev, "si2157 does not currently support FM radio\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	पंचांगp_lval = params->frequency * 625LL;
	करो_भाग(पंचांगp_lval, 10); /* convert to HZ */
	freq = (u32)पंचांगp_lval;

	अगर (freq < 1000000) /* is freq in KHz */
		freq = freq * 1000;
	dev->frequency = freq;

	/* अगर_frequency values based on tda187271C2 */
	अगर (params->std & (V4L2_STD_B | V4L2_STD_GH)) अणु
		अगर (freq >= 470000000) अणु
			std = "palGH";
			bandwidth = 8000000;
			अगर_frequency = 6000000;
			प्रणाली = 1;
			अगर (params->std &
			    (V4L2_STD_SECAM_G | V4L2_STD_SECAM_H)) अणु
				std = "secamGH";
				color = 0x10;
			पूर्ण
		पूर्ण अन्यथा अणु
			std = "palB";
			bandwidth = 7000000;
			अगर_frequency = 6000000;
			प्रणाली = 0;
			अगर (params->std & V4L2_STD_SECAM_B) अणु
				std = "secamB";
				color = 0x10;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_MN) अणु
		std = "MN";
		bandwidth = 6000000;
		अगर_frequency = 5400000;
		प्रणाली = 2;
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_I) अणु
		std = "palI";
		bandwidth = 8000000;
		अगर_frequency = 7250000; /* TODO: करोes not work yet */
		प्रणाली = 4;
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_DK) अणु
		std = "palDK";
		bandwidth = 8000000;
		अगर_frequency = 6900000; /* TODO: करोes not work yet */
		प्रणाली = 5;
		अगर (params->std & V4L2_STD_SECAM_DK) अणु
			std = "secamDK";
			color = 0x10;
		पूर्ण
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_L) अणु
		std = "secamL";
		bandwidth = 8000000;
		अगर_frequency = 6750000; /* TODO: untested */
		प्रणाली = 6;
		color = 0x10;
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_LC) अणु
		std = "secamL'";
		bandwidth = 7000000;
		अगर_frequency = 1250000; /* TODO: untested */
		प्रणाली = 7;
		color = 0x10;
	पूर्ण अन्यथा अणु
		std = "unknown";
	पूर्ण
	/* calc channel center freq */
	freq = freq - 1250000 + (bandwidth / 2);

	dev_dbg(&client->dev,
		"mode=%d system=%u std='%s' params->frequency=%u center freq=%u if=%u bandwidth=%u\n",
		params->mode, प्रणाली, std, params->frequency,
		freq, अगर_frequency, bandwidth);

	/* set analog IF port */
	स_नकल(cmd.args, "\x14\x00\x03\x06\x08\x02", 6);
	/* in using dev->अगर_port, we assume analog and digital IF's */
	/*   are always on dअगरferent ports */
	/* assumes अगर_port definition is 0 or 1 क्रम digital out */
	cmd.args[4] = (dev->अगर_port == 1) ? 8 : 10;
	/* Analog AGC assumed बाह्यal */
	cmd.args[5] = (dev->अगर_port == 1) ? 2 : 1;
	cmd.wlen = 6;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* set analog IF output config */
	स_नकल(cmd.args, "\x14\x00\x0d\x06\x94\x64", 6);
	cmd.wlen = 6;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* make this distinct from a digital IF */
	dev->अगर_frequency = अगर_frequency | 1;

	/* calc and set tuner analog अगर center frequency */
	अगर_frequency = अगर_frequency + 1250000 - (bandwidth / 2);
	dev_dbg(&client->dev, "IF Ctr freq=%d\n", अगर_frequency);

	स_नकल(cmd.args, "\x14\x00\x0C\x06", 4);
	cmd.args[4] = (अगर_frequency / 1000) & 0xff;
	cmd.args[5] = ((अगर_frequency / 1000) >> 8) & 0xff;
	cmd.wlen = 6;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* set analog AGC config */
	स_नकल(cmd.args, "\x14\x00\x07\x06\x32\xc8", 6);
	cmd.wlen = 6;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* set analog video mode */
	स_नकल(cmd.args, "\x14\x00\x04\x06\x00\x00", 6);
	cmd.args[4] = प्रणाली | color;
	/* can use dev->inversion अगर assumed applies to both digital/analog */
	अगर (invert_analog)
		cmd.args[5] |= 0x02;
	cmd.wlen = 6;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	/* set analog frequency */
	स_नकल(cmd.args, "\x41\x01\x00\x00\x00\x00\x00\x00", 8);
	cmd.args[4] = (freq >>  0) & 0xff;
	cmd.args[5] = (freq >>  8) & 0xff;
	cmd.args[6] = (freq >> 16) & 0xff;
	cmd.args[7] = (freq >> 24) & 0xff;
	cmd.wlen = 8;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	dev->bandwidth = bandwidth;

	si2157_tune_रुको(client, 0); /* रुको to complete, ignore any errors */

	वापस 0;
err:
	dev->bandwidth = 0;
	dev->frequency = 0;
	dev->अगर_frequency = 0;
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2157_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);

	*frequency = dev->frequency;
	dev_dbg(&client->dev, "freq=%u\n", dev->frequency);
	वापस 0;
पूर्ण

अटल पूर्णांक si2157_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);

	*bandwidth = dev->bandwidth;
	dev_dbg(&client->dev, "bandwidth=%u\n", dev->bandwidth);
	वापस 0;
पूर्ण

अटल पूर्णांक si2157_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);

	*frequency = dev->अगर_frequency & ~1; /* strip analog IF indicator bit */
	dev_dbg(&client->dev, "if_frequency=%u\n", *frequency);
	वापस 0;
पूर्ण

अटल पूर्णांक si2157_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *rssi)
अणु
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा si2157_cmd cmd;
	पूर्णांक ret;
	पूर्णांक strength;

	dev_dbg(&client->dev, "\n");

	स_नकल(cmd.args, "\x42\x00", 2);
	cmd.wlen = 2;
	cmd.rlen = 12;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].svalue = (s8)cmd.args[3] * 1000;

	/* normalize values based on Silicon Lअसल reference
	 * add 100, then anything > 80 is 100% संकेत
	 */
	strength = (s8)cmd.args[3] + 100;
	strength = clamp_val(strength, 0, 80);
	*rssi = (u16)(strength * 0xffff / 80);

	dev_dbg(&client->dev, "strength=%d rssi=%u\n",
		(s8)cmd.args[3], *rssi);

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops si2157_ops = अणु
	.info = अणु
		.name             = "Silicon Labs Si2141/Si2146/2147/2148/2157/2158",
		.frequency_min_hz =  42 * MHz,
		.frequency_max_hz = 870 * MHz,
	पूर्ण,

	.init = si2157_init,
	.sleep = si2157_sleep,
	.set_params = si2157_set_params,
	.set_analog_params = si2157_set_analog_params,
	.get_frequency     = si2157_get_frequency,
	.get_bandwidth     = si2157_get_bandwidth,
	.get_अगर_frequency  = si2157_get_अगर_frequency,

	.get_rf_strength   = si2157_get_rf_strength,
पूर्ण;

अटल व्योम si2157_stat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा si2157_dev *dev = container_of(work, काष्ठा si2157_dev, stat_work.work);
	काष्ठा dvb_frontend *fe = dev->fe;
	काष्ठा i2c_client *client = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा si2157_cmd cmd;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	स_नकल(cmd.args, "\x42\x00", 2);
	cmd.wlen = 2;
	cmd.rlen = 12;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret)
		जाओ err;

	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].svalue = (s8) cmd.args[3] * 1000;

	schedule_delayed_work(&dev->stat_work, msecs_to_jअगरfies(2000));
	वापस;
err:
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	dev_dbg(&client->dev, "failed=%d\n", ret);
पूर्ण

अटल पूर्णांक si2157_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा si2157_config *cfg = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = cfg->fe;
	काष्ठा si2157_dev *dev;
	काष्ठा si2157_cmd cmd;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		dev_err(&client->dev, "kzalloc() failed\n");
		जाओ err;
	पूर्ण

	i2c_set_clientdata(client, dev);
	dev->fe = cfg->fe;
	dev->inversion = cfg->inversion;
	dev->करोnt_load_firmware = cfg->करोnt_load_firmware;
	dev->अगर_port = cfg->अगर_port;
	dev->chiptype = (u8)id->driver_data;
	dev->अगर_frequency = 5000000; /* शेष value of property 0x0706 */
	mutex_init(&dev->i2c_mutex);
	INIT_DELAYED_WORK(&dev->stat_work, si2157_stat_work);

	/* check अगर the tuner is there */
	cmd.wlen = 0;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	अगर (ret && ret != -EAGAIN)
		जाओ err_kमुक्त;

	स_नकल(&fe->ops.tuner_ops, &si2157_ops, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = client;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	अगर (cfg->mdev) अणु
		dev->mdev = cfg->mdev;

		dev->ent.name = KBUILD_MODNAME;
		dev->ent.function = MEDIA_ENT_F_TUNER;

		dev->pad[SI2157_PAD_RF_INPUT].flags = MEDIA_PAD_FL_SINK;
		dev->pad[SI2157_PAD_RF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
		dev->pad[SI2157_PAD_VID_OUT].flags = MEDIA_PAD_FL_SOURCE;
		dev->pad[SI2157_PAD_VID_OUT].sig_type = PAD_SIGNAL_ANALOG;
		dev->pad[SI2157_PAD_AUD_OUT].flags = MEDIA_PAD_FL_SOURCE;
		dev->pad[SI2157_PAD_AUD_OUT].sig_type = PAD_SIGNAL_AUDIO;

		ret = media_entity_pads_init(&dev->ent, SI2157_NUM_PADS,
					     &dev->pad[0]);

		अगर (ret)
			जाओ err_kमुक्त;

		ret = media_device_रेजिस्टर_entity(cfg->mdev, &dev->ent);
		अगर (ret) अणु
			media_entity_cleanup(&dev->ent);
			जाओ err_kमुक्त;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	dev_info(&client->dev, "Silicon Labs %s successfully attached\n",
			dev->chiptype == SI2157_CHIPTYPE_SI2141 ?  "Si2141" :
			dev->chiptype == SI2157_CHIPTYPE_SI2146 ?
			"Si2146" : "Si2147/2148/2157/2158");

	वापस 0;

err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2157_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा si2157_dev *dev = i2c_get_clientdata(client);
	काष्ठा dvb_frontend *fe = dev->fe;

	dev_dbg(&client->dev, "\n");

	/* stop statistics polling */
	cancel_delayed_work_sync(&dev->stat_work);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	अगर (dev->mdev)
		media_device_unरेजिस्टर_entity(&dev->ent);
#पूर्ण_अगर

	स_रखो(&fe->ops.tuner_ops, 0, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = शून्य;
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si2157_id_table[] = अणु
	अणु"si2157", SI2157_CHIPTYPE_SI2157पूर्ण,
	अणु"si2146", SI2157_CHIPTYPE_SI2146पूर्ण,
	अणु"si2141", SI2157_CHIPTYPE_SI2141पूर्ण,
	अणु"si2177", SI2157_CHIPTYPE_SI2177पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si2157_id_table);

अटल काष्ठा i2c_driver si2157_driver = अणु
	.driver = अणु
		.name		     = "si2157",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= si2157_probe,
	.हटाओ		= si2157_हटाओ,
	.id_table	= si2157_id_table,
पूर्ण;

module_i2c_driver(si2157_driver);

MODULE_DESCRIPTION("Silicon Labs Si2141/Si2146/2147/2148/2157/2158 silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(SI2158_A20_FIRMWARE);
MODULE_FIRMWARE(SI2141_A10_FIRMWARE);
MODULE_FIRMWARE(SI2157_A30_FIRMWARE);
