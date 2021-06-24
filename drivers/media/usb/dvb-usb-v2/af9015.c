<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DVB USB Linux driver क्रम Afatech AF9015 DVB-T USB2.0 receiver
 *
 * Copyright (C) 2007 Antti Palosaari <crope@iki.fi>
 *
 * Thanks to Afatech who kindly provided inक्रमmation.
 */

#समावेश "af9015.h"

अटल पूर्णांक dvb_usb_af9015_remote;
module_param_named(remote, dvb_usb_af9015_remote, पूर्णांक, 0644);
MODULE_PARM_DESC(remote, "select remote");
DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक af9015_ctrl_msg(काष्ठा dvb_usb_device *d, काष्ठा req_t *req)
अणु
#घोषणा REQ_HDR_LEN 8 /* send header size */
#घोषणा ACK_HDR_LEN 2 /* rece header size */
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, wlen, rlen;
	u8 ग_लिखो = 1;

	mutex_lock(&d->usb_mutex);

	state->buf[0] = req->cmd;
	state->buf[1] = state->seq++;
	state->buf[2] = req->i2c_addr << 1;
	state->buf[3] = req->addr >> 8;
	state->buf[4] = req->addr & 0xff;
	state->buf[5] = req->mbox;
	state->buf[6] = req->addr_len;
	state->buf[7] = req->data_len;

	चयन (req->cmd) अणु
	हाल GET_CONFIG:
	हाल READ_MEMORY:
	हाल RECONNECT_USB:
		ग_लिखो = 0;
		अवरोध;
	हाल READ_I2C:
		ग_लिखो = 0;
		state->buf[2] |= 0x01; /* set I2C direction */
		fallthrough;
	हाल WRITE_I2C:
		state->buf[0] = READ_WRITE_I2C;
		अवरोध;
	हाल WRITE_MEMORY:
		अगर (((req->addr & 0xff00) == 0xff00) ||
		    ((req->addr & 0xff00) == 0xae00))
			state->buf[0] = WRITE_VIRTUAL_MEMORY;
		अवरोध;
	हाल WRITE_VIRTUAL_MEMORY:
	हाल COPY_FIRMWARE:
	हाल DOWNLOAD_FIRMWARE:
	हाल BOOT:
		अवरोध;
	शेष:
		dev_err(&पूर्णांकf->dev, "unknown cmd %d\n", req->cmd);
		ret = -EIO;
		जाओ error;
	पूर्ण

	/* Buffer overflow check */
	अगर ((ग_लिखो && (req->data_len > BUF_LEN - REQ_HDR_LEN)) ||
	    (!ग_लिखो && (req->data_len > BUF_LEN - ACK_HDR_LEN))) अणु
		dev_err(&पूर्णांकf->dev, "too much data, cmd %u, len %u\n",
			req->cmd, req->data_len);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/*
	 * Write receives seq + status = 2 bytes
	 * Read receives seq + status + data = 2 + N bytes
	 */
	wlen = REQ_HDR_LEN;
	rlen = ACK_HDR_LEN;
	अगर (ग_लिखो) अणु
		wlen += req->data_len;
		स_नकल(&state->buf[REQ_HDR_LEN], req->data, req->data_len);
	पूर्ण अन्यथा अणु
		rlen += req->data_len;
	पूर्ण

	/* no ack क्रम these packets */
	अगर (req->cmd == DOWNLOAD_FIRMWARE || req->cmd == RECONNECT_USB)
		rlen = 0;

	ret = dvb_usbv2_generic_rw_locked(d, state->buf, wlen,
					  state->buf, rlen);
	अगर (ret)
		जाओ error;

	/* check status */
	अगर (rlen && state->buf[1]) अणु
		dev_err(&पूर्णांकf->dev, "cmd failed %u\n", state->buf[1]);
		ret = -EIO;
		जाओ error;
	पूर्ण

	/* पढ़ो request, copy वापसed data to वापस buf */
	अगर (!ग_लिखो)
		स_नकल(req->data, &state->buf[ACK_HDR_LEN], req->data_len);
error:
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_ग_लिखो_reg_i2c(काष्ठा dvb_usb_device *d, u8 addr, u16 reg,
				u8 val)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा req_t req = अणुWRITE_I2C, addr, reg, 1, 1, 1, &valपूर्ण;

	अगर (addr == state->af9013_i2c_addr[0] ||
	    addr == state->af9013_i2c_addr[1])
		req.addr_len = 3;

	वापस af9015_ctrl_msg(d, &req);
पूर्ण

अटल पूर्णांक af9015_पढ़ो_reg_i2c(काष्ठा dvb_usb_device *d, u8 addr, u16 reg,
			       u8 *val)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा req_t req = अणुREAD_I2C, addr, reg, 0, 1, 1, valपूर्ण;

	अगर (addr == state->af9013_i2c_addr[0] ||
	    addr == state->af9013_i2c_addr[1])
		req.addr_len = 3;

	वापस af9015_ctrl_msg(d, &req);
पूर्ण

अटल पूर्णांक af9015_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
			   पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u16 addr;
	u8 mbox, addr_len;
	काष्ठा req_t req;

	/*
	 * I2C multiplexing:
	 * There could be two tuners, both using same I2C address. Demodulator
	 * I2C-gate is only possibility to select correct tuner.
	 *
	 * ...........................................
	 * . AF9015 पूर्णांकegrates AF9013 demodulator    .
	 * . ____________               ____________ .             ____________
	 * .|   USB IF   |             |   demod    |.            |   tuner    |
	 * .|------------|             |------------|.            |------------|
	 * .|   AF9015   |             |   AF9013   |.            |   MXL5003  |
	 * .|            |--+--I2C-----|-----/ -----|.----I2C-----|            |
	 * .|            |  |          | addr 0x1c  |.            |  addr 0x63 |
	 * .|____________|  |          |____________|.            |____________|
	 * .................|.........................
	 *                  |           ____________               ____________
	 *                  |          |   demod    |             |   tuner    |
	 *                  |          |------------|             |------------|
	 *                  |          |   AF9013   |             |   MXL5003  |
	 *                  +--I2C-----|-----/ -----|-----I2C-----|            |
	 *                             | addr 0x1d  |             |  addr 0x63 |
	 *                             |____________|             |____________|
	 */

	अगर (msg[0].len == 0 || msg[0].flags & I2C_M_RD) अणु
		addr = 0x0000;
		mbox = 0;
		addr_len = 0;
	पूर्ण अन्यथा अगर (msg[0].len == 1) अणु
		addr = msg[0].buf[0];
		mbox = 0;
		addr_len = 1;
	पूर्ण अन्यथा अगर (msg[0].len == 2) अणु
		addr = msg[0].buf[0] << 8 | msg[0].buf[1] << 0;
		mbox = 0;
		addr_len = 2;
	पूर्ण अन्यथा अणु
		addr = msg[0].buf[0] << 8 | msg[0].buf[1] << 0;
		mbox = msg[0].buf[2];
		addr_len = 3;
	पूर्ण

	अगर (num == 1 && !(msg[0].flags & I2C_M_RD)) अणु
		/* i2c ग_लिखो */
		अगर (msg[0].len > 21) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण
		अगर (msg[0].addr == state->af9013_i2c_addr[0])
			req.cmd = WRITE_MEMORY;
		अन्यथा
			req.cmd = WRITE_I2C;
		req.i2c_addr = msg[0].addr;
		req.addr = addr;
		req.mbox = mbox;
		req.addr_len = addr_len;
		req.data_len = msg[0].len - addr_len;
		req.data = &msg[0].buf[addr_len];
		ret = af9015_ctrl_msg(d, &req);
	पूर्ण अन्यथा अगर (num == 2 && !(msg[0].flags & I2C_M_RD) &&
		   (msg[1].flags & I2C_M_RD)) अणु
		/* i2c ग_लिखो + पढ़ो */
		अगर (msg[0].len > 3 || msg[1].len > 61) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण
		अगर (msg[0].addr == state->af9013_i2c_addr[0])
			req.cmd = READ_MEMORY;
		अन्यथा
			req.cmd = READ_I2C;
		req.i2c_addr = msg[0].addr;
		req.addr = addr;
		req.mbox = mbox;
		req.addr_len = addr_len;
		req.data_len = msg[1].len;
		req.data = &msg[1].buf[0];
		ret = af9015_ctrl_msg(d, &req);
	पूर्ण अन्यथा अगर (num == 1 && (msg[0].flags & I2C_M_RD)) अणु
		/* i2c पढ़ो */
		अगर (msg[0].len > 61) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण
		अगर (msg[0].addr == state->af9013_i2c_addr[0]) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		req.cmd = READ_I2C;
		req.i2c_addr = msg[0].addr;
		req.addr = addr;
		req.mbox = mbox;
		req.addr_len = addr_len;
		req.data_len = msg[0].len;
		req.data = &msg[0].buf[0];
		ret = af9015_ctrl_msg(d, &req);
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP;
		dev_dbg(&पूर्णांकf->dev, "unknown msg, num %u\n", num);
	पूर्ण
	अगर (ret)
		जाओ err;

	वापस num;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल u32 af9015_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm af9015_i2c_algo = अणु
	.master_xfer = af9015_i2c_xfer,
	.functionality = af9015_i2c_func,
पूर्ण;

अटल पूर्णांक af9015_identअगरy_state(काष्ठा dvb_usb_device *d, स्थिर अक्षर **name)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u8 reply;
	काष्ठा req_t req = अणुGET_CONFIG, 0, 0, 0, 0, 1, &replyपूर्ण;

	ret = af9015_ctrl_msg(d, &req);
	अगर (ret)
		वापस ret;

	dev_dbg(&पूर्णांकf->dev, "reply %02x\n", reply);

	अगर (reply == 0x02)
		ret = WARM;
	अन्यथा
		ret = COLD;

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_करोwnload_firmware(काष्ठा dvb_usb_device *d,
				    स्थिर काष्ठा firmware *firmware)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, i, rem;
	काष्ठा req_t req = अणुDOWNLOAD_FIRMWARE, 0, 0, 0, 0, 0, शून्यपूर्ण;
	u16 checksum;

	dev_dbg(&पूर्णांकf->dev, "\n");

	/* Calc checksum, we need it when copy firmware to slave demod */
	क्रम (i = 0, checksum = 0; i < firmware->size; i++)
		checksum += firmware->data[i];

	state->firmware_size = firmware->size;
	state->firmware_checksum = checksum;

	#घोषणा LEN_MAX (BUF_LEN - REQ_HDR_LEN) /* Max payload size */
	क्रम (rem = firmware->size; rem > 0; rem -= LEN_MAX) अणु
		req.data_len = min(LEN_MAX, rem);
		req.data = (u8 *)&firmware->data[firmware->size - rem];
		req.addr = 0x5100 + firmware->size - rem;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret) अणु
			dev_err(&पूर्णांकf->dev, "firmware download failed %d\n",
				ret);
			जाओ err;
		पूर्ण
	पूर्ण

	req.cmd = BOOT;
	req.data_len = 0;
	ret = af9015_ctrl_msg(d, &req);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "firmware boot failed %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

#घोषणा AF9015_EEPROM_SIZE 256
/* 2^31 + 2^29 - 2^25 + 2^22 - 2^19 - 2^16 + 1 */
#घोषणा GOLDEN_RATIO_PRIME_32 0x9e370001UL

/* hash (and dump) eeprom */
अटल पूर्णांक af9015_eeprom_hash(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, i;
	u8 buf[AF9015_EEPROM_SIZE];
	काष्ठा req_t req = अणुREAD_I2C, AF9015_I2C_EEPROM, 0, 0, 1, 1, शून्यपूर्ण;

	/* पढ़ो eeprom */
	क्रम (i = 0; i < AF9015_EEPROM_SIZE; i++) अणु
		req.addr = i;
		req.data = &buf[i];
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	/* calculate checksum */
	क्रम (i = 0; i < AF9015_EEPROM_SIZE / माप(u32); i++) अणु
		state->eeprom_sum *= GOLDEN_RATIO_PRIME_32;
		state->eeprom_sum += le32_to_cpu(((__le32 *)buf)[i]);
	पूर्ण

	क्रम (i = 0; i < AF9015_EEPROM_SIZE; i += 16)
		dev_dbg(&पूर्णांकf->dev, "%*ph\n", 16, buf + i);

	dev_dbg(&पूर्णांकf->dev, "eeprom sum %.8x\n", state->eeprom_sum);
	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9015_पढ़ो_config(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u8 val, i, offset = 0;
	काष्ठा req_t req = अणुREAD_I2C, AF9015_I2C_EEPROM, 0, 0, 1, 1, &valपूर्ण;

	dev_dbg(&पूर्णांकf->dev, "\n");

	/* IR remote controller */
	req.addr = AF9015_EEPROM_IR_MODE;
	/* first message will समयout often due to possible hw bug */
	क्रम (i = 0; i < 4; i++) अणु
		ret = af9015_ctrl_msg(d, &req);
		अगर (!ret)
			अवरोध;
	पूर्ण
	अगर (ret)
		जाओ error;

	ret = af9015_eeprom_hash(d);
	अगर (ret)
		जाओ error;

	state->ir_mode = val;
	dev_dbg(&पूर्णांकf->dev, "ir mode %02x\n", val);

	/* TS mode - one or two receivers */
	req.addr = AF9015_EEPROM_TS_MODE;
	ret = af9015_ctrl_msg(d, &req);
	अगर (ret)
		जाओ error;

	state->dual_mode = val;
	dev_dbg(&पूर्णांकf->dev, "ts mode %02x\n", state->dual_mode);

	state->af9013_i2c_addr[0] = AF9015_I2C_DEMOD;

	अगर (state->dual_mode) अणु
		/* पढ़ो 2nd demodulator I2C address */
		req.addr = AF9015_EEPROM_DEMOD2_I2C;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret)
			जाओ error;

		state->af9013_i2c_addr[1] = val >> 1;
	पूर्ण

	क्रम (i = 0; i < state->dual_mode + 1; i++) अणु
		अगर (i == 1)
			offset = AF9015_EEPROM_OFFSET;
		/* xtal */
		req.addr = AF9015_EEPROM_XTAL_TYPE1 + offset;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret)
			जाओ error;
		चयन (val) अणु
		हाल 0:
			state->af9013_pdata[i].clk = 28800000;
			अवरोध;
		हाल 1:
			state->af9013_pdata[i].clk = 20480000;
			अवरोध;
		हाल 2:
			state->af9013_pdata[i].clk = 28000000;
			अवरोध;
		हाल 3:
			state->af9013_pdata[i].clk = 25000000;
			अवरोध;
		पूर्ण
		dev_dbg(&पूर्णांकf->dev, "[%d] xtal %02x, clk %u\n",
			i, val, state->af9013_pdata[i].clk);

		/* IF frequency */
		req.addr = AF9015_EEPROM_IF1H + offset;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret)
			जाओ error;

		state->af9013_pdata[i].अगर_frequency = val << 8;

		req.addr = AF9015_EEPROM_IF1L + offset;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret)
			जाओ error;

		state->af9013_pdata[i].अगर_frequency += val;
		state->af9013_pdata[i].अगर_frequency *= 1000;
		dev_dbg(&पूर्णांकf->dev, "[%d] if frequency %u\n",
			i, state->af9013_pdata[i].अगर_frequency);

		/* MT2060 IF1 */
		req.addr = AF9015_EEPROM_MT2060_IF1H  + offset;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret)
			जाओ error;
		state->mt2060_अगर1[i] = val << 8;
		req.addr = AF9015_EEPROM_MT2060_IF1L + offset;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret)
			जाओ error;
		state->mt2060_अगर1[i] += val;
		dev_dbg(&पूर्णांकf->dev, "[%d] MT2060 IF1 %u\n",
			i, state->mt2060_अगर1[i]);

		/* tuner */
		req.addr =  AF9015_EEPROM_TUNER_ID1 + offset;
		ret = af9015_ctrl_msg(d, &req);
		अगर (ret)
			जाओ error;
		चयन (val) अणु
		हाल AF9013_TUNER_ENV77H11D5:
		हाल AF9013_TUNER_MT2060:
		हाल AF9013_TUNER_QT1010:
		हाल AF9013_TUNER_UNKNOWN:
		हाल AF9013_TUNER_MT2060_2:
		हाल AF9013_TUNER_TDA18271:
		हाल AF9013_TUNER_QT1010A:
		हाल AF9013_TUNER_TDA18218:
			state->af9013_pdata[i].spec_inv = 1;
			अवरोध;
		हाल AF9013_TUNER_MXL5003D:
		हाल AF9013_TUNER_MXL5005D:
		हाल AF9013_TUNER_MXL5005R:
		हाल AF9013_TUNER_MXL5007T:
			state->af9013_pdata[i].spec_inv = 0;
			अवरोध;
		हाल AF9013_TUNER_MC44S803:
			state->af9013_pdata[i].gpio[1] = AF9013_GPIO_LO;
			state->af9013_pdata[i].spec_inv = 1;
			अवरोध;
		शेष:
			dev_err(&पूर्णांकf->dev,
				"tuner id %02x not supported, please report!\n",
				val);
			वापस -ENODEV;
		पूर्ण

		state->af9013_pdata[i].tuner = val;
		dev_dbg(&पूर्णांकf->dev, "[%d] tuner id %02x\n", i, val);
	पूर्ण

error:
	अगर (ret)
		dev_err(&पूर्णांकf->dev, "eeprom read failed %d\n", ret);

	/*
	 * AverMedia AVerTV Volar Black HD (A850) device have bad EEPROM
	 * content :-( Override some wrong values here. Ditto क्रम the
	 * AVerTV Red HD+ (A850T) device.
	 */
	अगर (le16_to_cpu(d->udev->descriptor.idVenकरोr) == USB_VID_AVERMEDIA &&
	    ((le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_AVERMEDIA_A850) ||
	    (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_AVERMEDIA_A850T))) अणु
		dev_dbg(&पूर्णांकf->dev, "AverMedia A850: overriding config\n");
		/* disable dual mode */
		state->dual_mode = 0;

		/* set correct IF */
		state->af9013_pdata[0].अगर_frequency = 4570000;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_get_stream_config(काष्ठा dvb_frontend *fe, u8 *ts_type,
				    काष्ठा usb_data_stream_properties *stream)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "adap %u\n", fe_to_adap(fe)->id);

	अगर (d->udev->speed == USB_SPEED_FULL)
		stream->u.bulk.buffersize = 5 * 188;

	वापस 0;
पूर्ण

अटल पूर्णांक af9015_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp1, uपंचांगp2, reg1, reg2;
	u8 buf[2];
	स्थिर अचिन्हित पूर्णांक adap_id = fe_to_adap(fe)->id;

	dev_dbg(&पूर्णांकf->dev, "adap id %d, onoff %d\n", adap_id, onoff);

	अगर (!state->usb_ts_अगर_configured[adap_id]) अणु
		dev_dbg(&पूर्णांकf->dev, "set usb and ts interface\n");

		/* USB IF stream settings */
		uपंचांगp1 = (d->udev->speed == USB_SPEED_FULL ? 5 : 87) * 188 / 4;
		uपंचांगp2 = (d->udev->speed == USB_SPEED_FULL ? 64 : 512) / 4;

		buf[0] = (uपंचांगp1 >> 0) & 0xff;
		buf[1] = (uपंचांगp1 >> 8) & 0xff;
		अगर (adap_id == 0) अणु
			/* 1st USB IF (EP4) stream settings */
			reg1 = 0xdd88;
			reg2 = 0xdd0c;
		पूर्ण अन्यथा अणु
			/* 2nd USB IF (EP5) stream settings */
			reg1 = 0xdd8a;
			reg2 = 0xdd0d;
		पूर्ण
		ret = regmap_bulk_ग_लिखो(state->regmap, reg1, buf, 2);
		अगर (ret)
			जाओ err;
		ret = regmap_ग_लिखो(state->regmap, reg2, uपंचांगp2);
		अगर (ret)
			जाओ err;

		/* TS IF settings */
		अगर (state->dual_mode) अणु
			uपंचांगp1 = 0x01;
			uपंचांगp2 = 0x10;
		पूर्ण अन्यथा अणु
			uपंचांगp1 = 0x00;
			uपंचांगp2 = 0x00;
		पूर्ण
		ret = regmap_update_bits(state->regmap, 0xd50b, 0x01, uपंचांगp1);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xd520, 0x10, uपंचांगp2);
		अगर (ret)
			जाओ err;

		state->usb_ts_अगर_configured[adap_id] = true;
	पूर्ण

	अगर (adap_id == 0 && onoff) अणु
		/* Adapter 0 stream on. EP4: clear NAK, enable, clear reset */
		ret = regmap_update_bits(state->regmap, 0xdd13, 0x20, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xdd11, 0x20, 0x20);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xd507, 0x04, 0x00);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (adap_id == 1 && onoff) अणु
		/* Adapter 1 stream on. EP5: clear NAK, enable, clear reset */
		ret = regmap_update_bits(state->regmap, 0xdd13, 0x40, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xdd11, 0x40, 0x40);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xd50b, 0x02, 0x00);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (adap_id == 0 && !onoff) अणु
		/* Adapter 0 stream off. EP4: set reset, disable, set NAK */
		ret = regmap_update_bits(state->regmap, 0xd507, 0x04, 0x04);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xdd11, 0x20, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xdd13, 0x20, 0x20);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (adap_id == 1 && !onoff) अणु
		/* Adapter 1 stream off. EP5: set reset, disable, set NAK */
		ret = regmap_update_bits(state->regmap, 0xd50b, 0x02, 0x02);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xdd11, 0x40, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(state->regmap, 0xdd13, 0x40, 0x40);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9015_get_adapter_count(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);

	वापस state->dual_mode + 1;
पूर्ण

/* override demod callbacks क्रम resource locking */
अटल पूर्णांक af9015_af9013_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा af9015_state *state = fe_to_priv(fe);

	अगर (mutex_lock_पूर्णांकerruptible(&state->fe_mutex))
		वापस -EAGAIN;

	ret = state->set_frontend[fe_to_adap(fe)->id](fe);

	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

/* override demod callbacks क्रम resource locking */
अटल पूर्णांक af9015_af9013_पढ़ो_status(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_status *status)
अणु
	पूर्णांक ret;
	काष्ठा af9015_state *state = fe_to_priv(fe);

	अगर (mutex_lock_पूर्णांकerruptible(&state->fe_mutex))
		वापस -EAGAIN;

	ret = state->पढ़ो_status[fe_to_adap(fe)->id](fe, status);

	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

/* override demod callbacks क्रम resource locking */
अटल पूर्णांक af9015_af9013_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा af9015_state *state = fe_to_priv(fe);

	अगर (mutex_lock_पूर्णांकerruptible(&state->fe_mutex))
		वापस -EAGAIN;

	ret = state->init[fe_to_adap(fe)->id](fe);

	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

/* override demod callbacks क्रम resource locking */
अटल पूर्णांक af9015_af9013_sleep(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा af9015_state *state = fe_to_priv(fe);

	अगर (mutex_lock_पूर्णांकerruptible(&state->fe_mutex))
		वापस -EAGAIN;

	ret = state->sleep[fe_to_adap(fe)->id](fe);

	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

/* override tuner callbacks क्रम resource locking */
अटल पूर्णांक af9015_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा af9015_state *state = fe_to_priv(fe);

	अगर (mutex_lock_पूर्णांकerruptible(&state->fe_mutex))
		वापस -EAGAIN;

	ret = state->tuner_init[fe_to_adap(fe)->id](fe);

	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

/* override tuner callbacks क्रम resource locking */
अटल पूर्णांक af9015_tuner_sleep(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा af9015_state *state = fe_to_priv(fe);

	अगर (mutex_lock_पूर्णांकerruptible(&state->fe_mutex))
		वापस -EAGAIN;

	ret = state->tuner_sleep[fe_to_adap(fe)->id](fe);

	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_copy_firmware(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	u8 val, firmware_info[4];
	काष्ठा req_t req = अणुCOPY_FIRMWARE, 0, 0x5100, 0, 0, 4, firmware_infoपूर्ण;

	dev_dbg(&पूर्णांकf->dev, "\n");

	firmware_info[0] = (state->firmware_size >> 8) & 0xff;
	firmware_info[1] = (state->firmware_size >> 0) & 0xff;
	firmware_info[2] = (state->firmware_checksum >> 8) & 0xff;
	firmware_info[3] = (state->firmware_checksum >> 0) & 0xff;

	/* Check whether firmware is alपढ़ोy running */
	ret = af9015_पढ़ो_reg_i2c(d, state->af9013_i2c_addr[1], 0x98be, &val);
	अगर (ret)
		जाओ err;

	dev_dbg(&पूर्णांकf->dev, "firmware status %02x\n", val);

	अगर (val == 0x0c)
		वापस 0;

	/* Set i2c घड़ी to 625kHz to speed up firmware copy */
	ret = regmap_ग_लिखो(state->regmap, 0xd416, 0x04);
	अगर (ret)
		जाओ err;

	/* Copy firmware from master demod to slave demod */
	ret = af9015_ctrl_msg(d, &req);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "firmware copy cmd failed %d\n", ret);
		जाओ err;
	पूर्ण

	/* Set i2c घड़ी to 125kHz */
	ret = regmap_ग_लिखो(state->regmap, 0xd416, 0x14);
	अगर (ret)
		जाओ err;

	/* Boot firmware */
	ret = af9015_ग_लिखो_reg_i2c(d, state->af9013_i2c_addr[1], 0xe205, 0x01);
	अगर (ret)
		जाओ err;

	/* Poll firmware पढ़ोy */
	क्रम (val = 0x00, समयout = jअगरfies + msecs_to_jअगरfies(1000);
	     !समय_after(jअगरfies, समयout) && val != 0x0c && val != 0x04;) अणु
		msleep(20);

		/* Check firmware status. 0c=OK, 04=fail */
		ret = af9015_पढ़ो_reg_i2c(d, state->af9013_i2c_addr[1],
					  0x98be, &val);
		अगर (ret)
			जाओ err;

		dev_dbg(&पूर्णांकf->dev, "firmware status %02x\n", val);
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "firmware boot took %u ms\n",
		jअगरfies_to_msecs(jअगरfies) - (jअगरfies_to_msecs(समयout) - 1000));

	अगर (val == 0x04) अणु
		ret = -ENODEV;
		dev_err(&पूर्णांकf->dev, "firmware did not run\n");
		जाओ err;
	पूर्ण अन्यथा अगर (val != 0x0c) अणु
		ret = -ETIMEDOUT;
		dev_err(&पूर्णांकf->dev, "firmware boot timeout\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9015_af9013_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा af9015_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "adap id %u\n", adap->id);

	अगर (adap->id == 0) अणु
		state->af9013_pdata[0].ts_mode = AF9013_TS_MODE_USB;
		स_नकल(state->af9013_pdata[0].api_version, "\x0\x1\x9\x0", 4);
		state->af9013_pdata[0].gpio[0] = AF9013_GPIO_HI;
		state->af9013_pdata[0].gpio[3] = AF9013_GPIO_TUNER_ON;
	पूर्ण अन्यथा अगर (adap->id == 1) अणु
		state->af9013_pdata[1].ts_mode = AF9013_TS_MODE_SERIAL;
		state->af9013_pdata[1].ts_output_pin = 7;
		स_नकल(state->af9013_pdata[1].api_version, "\x0\x1\x9\x0", 4);
		state->af9013_pdata[1].gpio[0] = AF9013_GPIO_TUNER_ON;
		state->af9013_pdata[1].gpio[1] = AF9013_GPIO_LO;

		/* copy firmware to 2nd demodulator */
		अगर (state->dual_mode) अणु
			/* Wait 2nd demodulator पढ़ोy */
			msleep(100);

			ret = af9015_copy_firmware(adap_to_d(adap));
			अगर (ret) अणु
				dev_err(&पूर्णांकf->dev,
					"firmware copy to 2nd frontend failed, will disable it\n");
				state->dual_mode = 0;
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -ENODEV;
			जाओ err;
		पूर्ण
	पूर्ण

	/* Add I2C demod */
	client = dvb_module_probe("af9013", शून्य, &d->i2c_adap,
				  state->af9013_i2c_addr[adap->id],
				  &state->af9013_pdata[adap->id]);
	अगर (!client) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	adap->fe[0] = state->af9013_pdata[adap->id].get_dvb_frontend(client);
	state->demod_i2c_client[adap->id] = client;

	/*
	 * AF9015 firmware करोes not like अगर it माला_लो पूर्णांकerrupted by I2C adapter
	 * request on some critical phases. During normal operation I2C adapter
	 * is used only 2nd demodulator and tuner on dual tuner devices.
	 * Override demodulator callbacks and use mutex क्रम limit access to
	 * those "critical" paths to keep AF9015 happy.
	 */
	अगर (adap->fe[0]) अणु
		state->set_frontend[adap->id] = adap->fe[0]->ops.set_frontend;
		adap->fe[0]->ops.set_frontend = af9015_af9013_set_frontend;
		state->पढ़ो_status[adap->id] = adap->fe[0]->ops.पढ़ो_status;
		adap->fe[0]->ops.पढ़ो_status = af9015_af9013_पढ़ो_status;
		state->init[adap->id] = adap->fe[0]->ops.init;
		adap->fe[0]->ops.init = af9015_af9013_init;
		state->sleep[adap->id] = adap->fe[0]->ops.sleep;
		adap->fe[0]->ops.sleep = af9015_af9013_sleep;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9015_frontend_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा af9015_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा i2c_client *client;

	dev_dbg(&पूर्णांकf->dev, "adap id %u\n", adap->id);

	/* Remove I2C demod */
	client = state->demod_i2c_client[adap->id];
	dvb_module_release(client);

	वापस 0;
पूर्ण

अटल काष्ठा mt2060_config af9015_mt2060_config = अणु
	.i2c_address = 0x60,
	.घड़ी_out = 0,
पूर्ण;

अटल काष्ठा qt1010_config af9015_qt1010_config = अणु
	.i2c_address = 0x62,
पूर्ण;

अटल काष्ठा tda18271_config af9015_tda18271_config = अणु
	.gate = TDA18271_GATE_DIGITAL,
	.small_i2c = TDA18271_16_BYTE_CHUNK_INIT,
पूर्ण;

अटल काष्ठा mxl5005s_config af9015_mxl5003_config = अणु
	.i2c_address     = 0x63,
	.अगर_freq         = IF_FREQ_4570000HZ,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_DEFAULT,
	.rssi_enable     = MXL_RSSI_ENABLE,
	.cap_select      = MXL_CAP_SEL_ENABLE,
	.भाग_out         = MXL_DIV_OUT_4,
	.घड़ी_out       = MXL_CLOCK_OUT_DISABLE,
	.output_load     = MXL5005S_IF_OUTPUT_LOAD_200_OHM,
	.top		 = MXL5005S_TOP_25P2,
	.mod_mode        = MXL_DIGITAL_MODE,
	.अगर_mode         = MXL_ZERO_IF,
	.AgcMasterByte   = 0x00,
पूर्ण;

अटल काष्ठा mxl5005s_config af9015_mxl5005_config = अणु
	.i2c_address     = 0x63,
	.अगर_freq         = IF_FREQ_4570000HZ,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_OFF,
	.rssi_enable     = MXL_RSSI_ENABLE,
	.cap_select      = MXL_CAP_SEL_ENABLE,
	.भाग_out         = MXL_DIV_OUT_4,
	.घड़ी_out       = MXL_CLOCK_OUT_DISABLE,
	.output_load     = MXL5005S_IF_OUTPUT_LOAD_200_OHM,
	.top		 = MXL5005S_TOP_25P2,
	.mod_mode        = MXL_DIGITAL_MODE,
	.अगर_mode         = MXL_ZERO_IF,
	.AgcMasterByte   = 0x00,
पूर्ण;

अटल काष्ठा mc44s803_config af9015_mc44s803_config = अणु
	.i2c_address = 0x60,
	.dig_out = 1,
पूर्ण;

अटल काष्ठा tda18218_config af9015_tda18218_config = अणु
	.i2c_address = 0x60,
	.i2c_wr_max = 21, /* max wr bytes AF9015 I2C adap can handle at once */
पूर्ण;

अटल काष्ठा mxl5007t_config af9015_mxl5007t_config = अणु
	.xtal_freq_hz = MxL_XTAL_24_MHZ,
	.अगर_freq_hz = MxL_IF_4_57_MHZ,
पूर्ण;

अटल पूर्णांक af9015_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा i2c_client *client;
	काष्ठा i2c_adapter *adapter;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "adap id %u\n", adap->id);

	client = state->demod_i2c_client[adap->id];
	adapter = state->af9013_pdata[adap->id].get_i2c_adapter(client);

	चयन (state->af9013_pdata[adap->id].tuner) अणु
	हाल AF9013_TUNER_MT2060:
	हाल AF9013_TUNER_MT2060_2:
		ret = dvb_attach(mt2060_attach, adap->fe[0], adapter,
				 &af9015_mt2060_config,
				 state->mt2060_अगर1[adap->id]) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_QT1010:
	हाल AF9013_TUNER_QT1010A:
		ret = dvb_attach(qt1010_attach, adap->fe[0], adapter,
				 &af9015_qt1010_config) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_TDA18271:
		ret = dvb_attach(tda18271_attach, adap->fe[0], 0x60, adapter,
				 &af9015_tda18271_config) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_TDA18218:
		ret = dvb_attach(tda18218_attach, adap->fe[0], adapter,
				 &af9015_tda18218_config) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_MXL5003D:
		ret = dvb_attach(mxl5005s_attach, adap->fe[0], adapter,
				 &af9015_mxl5003_config) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_MXL5005D:
	हाल AF9013_TUNER_MXL5005R:
		ret = dvb_attach(mxl5005s_attach, adap->fe[0], adapter,
				 &af9015_mxl5005_config) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_ENV77H11D5:
		ret = dvb_attach(dvb_pll_attach, adap->fe[0], 0x60, adapter,
				 DVB_PLL_TDA665X) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_MC44S803:
		ret = dvb_attach(mc44s803_attach, adap->fe[0], adapter,
				 &af9015_mc44s803_config) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_MXL5007T:
		ret = dvb_attach(mxl5007t_attach, adap->fe[0], adapter,
				 0x60, &af9015_mxl5007t_config) == शून्य ? -ENODEV : 0;
		अवरोध;
	हाल AF9013_TUNER_UNKNOWN:
	शेष:
		dev_err(&पूर्णांकf->dev, "unknown tuner, tuner id %02x\n",
			state->af9013_pdata[adap->id].tuner);
		ret = -ENODEV;
	पूर्ण

	अगर (adap->fe[0]->ops.tuner_ops.init) अणु
		state->tuner_init[adap->id] =
			adap->fe[0]->ops.tuner_ops.init;
		adap->fe[0]->ops.tuner_ops.init = af9015_tuner_init;
	पूर्ण

	अगर (adap->fe[0]->ops.tuner_ops.sleep) अणु
		state->tuner_sleep[adap->id] =
			adap->fe[0]->ops.tuner_ops.sleep;
		adap->fe[0]->ops.tuner_ops.sleep = af9015_tuner_sleep;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा af9015_state *state = adap_to_priv(adap);
	काष्ठा af9013_platक्रमm_data *pdata = &state->af9013_pdata[adap->id];
	पूर्णांक ret;

	mutex_lock(&state->fe_mutex);
	ret = pdata->pid_filter_ctrl(adap->fe[0], onoff);
	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index,
			     u16 pid, पूर्णांक onoff)
अणु
	काष्ठा af9015_state *state = adap_to_priv(adap);
	काष्ठा af9013_platक्रमm_data *pdata = &state->af9013_pdata[adap->id];
	पूर्णांक ret;

	mutex_lock(&state->fe_mutex);
	ret = pdata->pid_filter(adap->fe[0], index, pid, onoff);
	mutex_unlock(&state->fe_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "\n");

	mutex_init(&state->fe_mutex);

	/* init RC canary */
	ret = regmap_ग_लिखो(state->regmap, 0x98e9, 0xff);
	अगर (ret)
		जाओ error;

error:
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_RC_CORE)
काष्ठा af9015_rc_setup अणु
	अचिन्हित पूर्णांक id;
	अक्षर *rc_codes;
पूर्ण;

अटल अक्षर *af9015_rc_setup_match(अचिन्हित पूर्णांक id,
				   स्थिर काष्ठा af9015_rc_setup *table)
अणु
	क्रम (; table->rc_codes; table++)
		अगर (table->id == id)
			वापस table->rc_codes;
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा af9015_rc_setup af9015_rc_setup_modparam[] = अणु
	अणु AF9015_REMOTE_A_LINK_DTU_M, RC_MAP_ALINK_DTU_M पूर्ण,
	अणु AF9015_REMOTE_MSI_DIGIVOX_MINI_II_V3, RC_MAP_MSI_DIGIVOX_II पूर्ण,
	अणु AF9015_REMOTE_MYGICTV_U718, RC_MAP_TOTAL_MEDIA_IN_HAND पूर्ण,
	अणु AF9015_REMOTE_DIGITTRADE_DVB_T, RC_MAP_DIGITTRADE पूर्ण,
	अणु AF9015_REMOTE_AVERMEDIA_KS, RC_MAP_AVERMEDIA_RM_KS पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा af9015_rc_setup af9015_rc_setup_hashes[] = अणु
	अणु 0xb8feb708, RC_MAP_MSI_DIGIVOX_II पूर्ण,
	अणु 0xa3703d00, RC_MAP_ALINK_DTU_M पूर्ण,
	अणु 0x9b7dc64e, RC_MAP_TOTAL_MEDIA_IN_HAND पूर्ण, /* MYGICTV U718 */
	अणु 0x5d49e3db, RC_MAP_DIGITTRADE पूर्ण, /* LC-Power LC-USB-DVBT */
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक af9015_rc_query(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u8 buf[17];

	/* पढ़ो रेजिस्टरs needed to detect remote controller code */
	ret = regmap_bulk_पढ़ो(state->regmap, 0x98d9, buf, माप(buf));
	अगर (ret)
		जाओ error;

	/* If any of these are non-zero, assume invalid data */
	अगर (buf[1] || buf[2] || buf[3]) अणु
		dev_dbg(&पूर्णांकf->dev, "invalid data\n");
		वापस ret;
	पूर्ण

	/* Check क्रम repeat of previous code */
	अगर ((state->rc_repeat != buf[6] || buf[0]) &&
	    !स_भेद(&buf[12], state->rc_last, 4)) अणु
		dev_dbg(&पूर्णांकf->dev, "key repeated\n");
		rc_repeat(d->rc_dev);
		state->rc_repeat = buf[6];
		वापस ret;
	पूर्ण

	/* Only process key अगर canary समाप्तed */
	अगर (buf[16] != 0xff && buf[0] != 0x01) अणु
		क्रमागत rc_proto proto;

		dev_dbg(&पूर्णांकf->dev, "key pressed %*ph\n", 4, buf + 12);

		/* Reset the canary */
		ret = regmap_ग_लिखो(state->regmap, 0x98e9, 0xff);
		अगर (ret)
			जाओ error;

		/* Remember this key */
		स_नकल(state->rc_last, &buf[12], 4);
		अगर (buf[14] == (u8)~buf[15]) अणु
			अगर (buf[12] == (u8)~buf[13]) अणु
				/* NEC */
				state->rc_keycode = RC_SCANCODE_NEC(buf[12],
								    buf[14]);
				proto = RC_PROTO_NEC;
			पूर्ण अन्यथा अणु
				/* NEC extended*/
				state->rc_keycode = RC_SCANCODE_NECX(buf[12] << 8 |
								     buf[13],
								     buf[14]);
				proto = RC_PROTO_NECX;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* 32 bit NEC */
			state->rc_keycode = RC_SCANCODE_NEC32(buf[12] << 24 |
							      buf[13] << 16 |
							      buf[14] << 8  |
							      buf[15]);
			proto = RC_PROTO_NEC32;
		पूर्ण
		rc_keyकरोwn(d->rc_dev, proto, state->rc_keycode, 0);
	पूर्ण अन्यथा अणु
		dev_dbg(&पूर्णांकf->dev, "no key press\n");
		/* Invalidate last keypress */
		/* Not really needed, but helps with debug */
		state->rc_last[2] = state->rc_last[3];
	पूर्ण

	state->rc_repeat = buf[6];
	state->rc_failed = false;

error:
	अगर (ret) अणु
		dev_warn(&पूर्णांकf->dev, "rc query failed %d\n", ret);

		/* allow अक्रमom errors as dvb-usb will stop polling on error */
		अगर (!state->rc_failed)
			ret = 0;

		state->rc_failed = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक af9015_get_rc_config(काष्ठा dvb_usb_device *d, काष्ठा dvb_usb_rc *rc)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	u16 vid = le16_to_cpu(d->udev->descriptor.idVenकरोr);

	अगर (state->ir_mode == AF9015_IR_MODE_DISABLED)
		वापस 0;

	/* try to load remote based module param */
	अगर (!rc->map_name)
		rc->map_name = af9015_rc_setup_match(dvb_usb_af9015_remote,
						     af9015_rc_setup_modparam);

	/* try to load remote based eeprom hash */
	अगर (!rc->map_name)
		rc->map_name = af9015_rc_setup_match(state->eeprom_sum,
						     af9015_rc_setup_hashes);

	/* try to load remote based USB iManufacturer string */
	अगर (!rc->map_name && vid == USB_VID_AFATECH) अणु
		/*
		 * Check USB manufacturer and product strings and try
		 * to determine correct remote in हाल of chip venकरोr
		 * reference IDs are used.
		 * DO NOT ADD ANYTHING NEW HERE. Use hashes instead.
		 */
		अक्षर manufacturer[10];

		स_रखो(manufacturer, 0, माप(manufacturer));
		usb_string(d->udev, d->udev->descriptor.iManufacturer,
			   manufacturer, माप(manufacturer));
		अगर (!म_भेद("MSI", manufacturer)) अणु
			/*
			 * iManufacturer 1 MSI
			 * iProduct      2 MSI K-VOX
			 */
			rc->map_name = af9015_rc_setup_match(AF9015_REMOTE_MSI_DIGIVOX_MINI_II_V3,
							     af9015_rc_setup_modparam);
		पूर्ण
	पूर्ण

	/* load empty to enable rc */
	अगर (!rc->map_name)
		rc->map_name = RC_MAP_EMPTY;

	rc->allowed_protos = RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX |
						RC_PROTO_BIT_NEC32;
	rc->query = af9015_rc_query;
	rc->पूर्णांकerval = 500;

	वापस 0;
पूर्ण
#अन्यथा
	#घोषणा af9015_get_rc_config शून्य
#पूर्ण_अगर

अटल पूर्णांक af9015_regmap_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा dvb_usb_device *d = context;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u16 reg = ((u8 *)data)[0] << 8 | ((u8 *)data)[1] << 0;
	u8 *val = &((u8 *)data)[2];
	स्थिर अचिन्हित पूर्णांक len = count - 2;
	काष्ठा req_t req = अणुWRITE_MEMORY, 0, reg, 0, 0, len, valपूर्ण;

	ret = af9015_ctrl_msg(d, &req);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9015_regmap_पढ़ो(व्योम *context, स्थिर व्योम *reg_buf,
			      माप_प्रकार reg_size, व्योम *val_buf, माप_प्रकार val_size)
अणु
	काष्ठा dvb_usb_device *d = context;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u16 reg = ((u8 *)reg_buf)[0] << 8 | ((u8 *)reg_buf)[1] << 0;
	u8 *val = &((u8 *)val_buf)[0];
	स्थिर अचिन्हित पूर्णांक len = val_size;
	काष्ठा req_t req = अणुREAD_MEMORY, 0, reg, 0, 0, len, valपूर्ण;

	ret = af9015_ctrl_msg(d, &req);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9015_probe(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक ret;
	अक्षर manufacturer[माप("ITE Technologies, Inc.")];
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits    =  16,
		.val_bits    =  8,
	पूर्ण;
	अटल स्थिर काष्ठा regmap_bus regmap_bus = अणु
		.पढ़ो = af9015_regmap_पढ़ो,
		.ग_लिखो = af9015_regmap_ग_लिखो,
	पूर्ण;

	dev_dbg(&पूर्णांकf->dev, "\n");

	स_रखो(manufacturer, 0, माप(manufacturer));
	usb_string(udev, udev->descriptor.iManufacturer,
		   manufacturer, माप(manufacturer));
	/*
	 * There is two devices having same ID but dअगरferent chipset. One uses
	 * AF9015 and the other IT9135 chipset. Only dअगरference seen on lsusb
	 * is iManufacturer string.
	 *
	 * idVenकरोr           0x0ccd TerraTec Electronic GmbH
	 * idProduct          0x0099
	 * bcdDevice            2.00
	 * iManufacturer           1 Afatech
	 * iProduct                2 DVB-T 2
	 *
	 * idVenकरोr           0x0ccd TerraTec Electronic GmbH
	 * idProduct          0x0099
	 * bcdDevice            2.00
	 * iManufacturer           1 ITE Technologies, Inc.
	 * iProduct                2 DVB-T TV Stick
	 */
	अगर ((le16_to_cpu(udev->descriptor.idVenकरोr) == USB_VID_TERRATEC) &&
	    (le16_to_cpu(udev->descriptor.idProduct) == 0x0099)) अणु
		अगर (!म_भेद("ITE Technologies, Inc.", manufacturer)) अणु
			ret = -ENODEV;
			dev_dbg(&पूर्णांकf->dev, "rejecting device\n");
			जाओ err;
		पूर्ण
	पूर्ण

	state->regmap = regmap_init(&पूर्णांकf->dev, &regmap_bus, d, &regmap_config);
	अगर (IS_ERR(state->regmap)) अणु
		ret = PTR_ERR(state->regmap);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम af9015_disconnect(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9015_state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "\n");

	regmap_निकास(state->regmap);
पूर्ण

/*
 * Interface 0 is used by DVB-T receiver and
 * पूर्णांकerface 1 is क्रम remote controller (HID)
 */
अटल स्थिर काष्ठा dvb_usb_device_properties af9015_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा af9015_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.probe = af9015_probe,
	.disconnect = af9015_disconnect,
	.identअगरy_state = af9015_identअगरy_state,
	.firmware = AF9015_FIRMWARE,
	.करोwnload_firmware = af9015_करोwnload_firmware,

	.i2c_algo = &af9015_i2c_algo,
	.पढ़ो_config = af9015_पढ़ो_config,
	.frontend_attach = af9015_af9013_frontend_attach,
	.frontend_detach = af9015_frontend_detach,
	.tuner_attach = af9015_tuner_attach,
	.init = af9015_init,
	.get_rc_config = af9015_get_rc_config,
	.get_stream_config = af9015_get_stream_config,
	.streaming_ctrl = af9015_streaming_ctrl,

	.get_adapter_count = af9015_get_adapter_count,
	.adapter = अणु
		अणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER |
				DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter_count = 32,
			.pid_filter = af9015_pid_filter,
			.pid_filter_ctrl = af9015_pid_filter_ctrl,

			.stream = DVB_USB_STREAM_BULK(0x84, 6, 87 * 188),
		पूर्ण, अणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER |
				DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter_count = 32,
			.pid_filter = af9015_pid_filter,
			.pid_filter_ctrl = af9015_pid_filter_ctrl,

			.stream = DVB_USB_STREAM_BULK(0x85, 6, 87 * 188),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id af9015_id_table[] = अणु
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9015_9015,
		&af9015_props, "Afatech AF9015 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9015_9016,
		&af9015_props, "Afatech AF9015 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_LEADTEK, USB_PID_WINFAST_DTV_DONGLE_GOLD,
		&af9015_props, "Leadtek WinFast DTV Dongle Gold", RC_MAP_LEADTEK_Y04G0051) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_PINNACLE, USB_PID_PINNACLE_PCTV71E,
		&af9015_props, "Pinnacle PCTV 71e", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_399U,
		&af9015_props, "KWorld PlusTV Dual DVB-T Stick (DVB-T 399U)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_TINYTWIN,
		&af9015_props, "DigitalNow TinyTwin", RC_MAP_AZUREWAVE_AD_TU700) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_AZUREWAVE_AD_TU700,
		&af9015_props, "TwinHan AzureWave AD-TU700(704J)", RC_MAP_AZUREWAVE_AD_TU700) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_T_USB_XE_REV2,
		&af9015_props, "TerraTec Cinergy T USB XE", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_PC160_2T,
		&af9015_props, "KWorld PlusTV Dual DVB-T PCI (DVB-T PC160-2T)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_VOLAR_X,
		&af9015_props, "AVerMedia AVerTV DVB-T Volar X", RC_MAP_AVERMEDIA_M135A) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_XTENSIONS, USB_PID_XTENSIONS_XD_380,
		&af9015_props, "Xtensions XD-380", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_MSI_2, USB_PID_MSI_DIGIVOX_DUO,
		&af9015_props, "MSI DIGIVOX Duo", RC_MAP_MSI_DIGIVOX_III) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_VOLAR_X_2,
		&af9015_props, "Fujitsu-Siemens Slim Mobile USB DVB-T", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TELESTAR,  USB_PID_TELESTAR_STARSTICK_2,
		&af9015_props, "Telestar Starstick 2", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A309,
		&af9015_props, "AVerMedia A309", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_MSI_2, USB_PID_MSI_DIGI_VOX_MINI_III,
		&af9015_props, "MSI Digi VOX mini III", RC_MAP_MSI_DIGIVOX_III) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_395U,
		&af9015_props, "KWorld USB DVB-T TV Stick II (VS-DVB-T 395U)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_395U_2,
		&af9015_props, "KWorld USB DVB-T TV Stick II (VS-DVB-T 395U)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_395U_3,
		&af9015_props, "KWorld USB DVB-T TV Stick II (VS-DVB-T 395U)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_TREKSTOR_DVBT,
		&af9015_props, "TrekStor DVB-T USB Stick", RC_MAP_TREKSTOR) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A850,
		&af9015_props, "AverMedia AVerTV Volar Black HD (A850)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A805,
		&af9015_props, "AverMedia AVerTV Volar GPS 805 (A805)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_CONCEPTRONIC_CTVDIGRCU,
		&af9015_props, "Conceptronic USB2.0 DVB-T CTVDIGRCU V3.0", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_MC810,
		&af9015_props, "KWorld Digital MC-810", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KYE, USB_PID_GENIUS_TVGO_DVB_T03,
		&af9015_props, "Genius TVGo DVB-T03", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_399U_2,
		&af9015_props, "KWorld PlusTV Dual DVB-T Stick (DVB-T 399U)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_PC160_T,
		&af9015_props, "KWorld PlusTV DVB-T PCI Pro Card (DVB-T PC160-T)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_SVEON_STV20,
		&af9015_props, "Sveon STV20 Tuner USB DVB-T HDTV", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_TINYTWIN_2,
		&af9015_props, "DigitalNow TinyTwin v2", RC_MAP_DIGITALNOW_TINYTWIN) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_LEADTEK, USB_PID_WINFAST_DTV2000DS,
		&af9015_props, "Leadtek WinFast DTV2000DS", RC_MAP_LEADTEK_Y04G0051) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_UB383_T,
		&af9015_props, "KWorld USB DVB-T Stick Mobile (UB383-T)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_395U_4,
		&af9015_props, "KWorld USB DVB-T TV Stick II (VS-DVB-T 395U)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A815M,
		&af9015_props, "AverMedia AVerTV Volar M (A815Mac)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_T_STICK_RC,
		&af9015_props, "TerraTec Cinergy T Stick RC", RC_MAP_TERRATEC_SLIM_2) पूर्ण,
	/* XXX: that same ID [0ccd:0099] is used by af9035 driver too */
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_T_STICK_DUAL_RC,
		&af9015_props, "TerraTec Cinergy T Stick Dual RC", RC_MAP_TERRATEC_SLIM) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A850T,
		&af9015_props, "AverMedia AVerTV Red HD+ (A850T)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_TINYTWIN_3,
		&af9015_props, "DigitalNow TinyTwin v3", RC_MAP_DIGITALNOW_TINYTWIN) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_SVEON_STV22,
		&af9015_props, "Sveon STV22 Dual USB DVB-T Tuner HDTV", RC_MAP_MSI_DIGIVOX_III) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, af9015_id_table);

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver af9015_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = af9015_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(af9015_usb_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Afatech AF9015 driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(AF9015_FIRMWARE);
