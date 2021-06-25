<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Afatech AF9035 DVB USB driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#समावेश "af9035.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल u16 af9035_checksum(स्थिर u8 *buf, माप_प्रकार len)
अणु
	माप_प्रकार i;
	u16 checksum = 0;

	क्रम (i = 1; i < len; i++) अणु
		अगर (i % 2)
			checksum += buf[i] << 8;
		अन्यथा
			checksum += buf[i];
	पूर्ण
	checksum = ~checksum;

	वापस checksum;
पूर्ण

अटल पूर्णांक af9035_ctrl_msg(काष्ठा dvb_usb_device *d, काष्ठा usb_req *req)
अणु
#घोषणा REQ_HDR_LEN 4 /* send header size */
#घोषणा ACK_HDR_LEN 3 /* rece header size */
#घोषणा CHECKSUM_LEN 2
#घोषणा USB_TIMEOUT 2000
	काष्ठा state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, wlen, rlen;
	u16 checksum, पंचांगp_checksum;

	mutex_lock(&d->usb_mutex);

	/* buffer overflow check */
	अगर (req->wlen > (BUF_LEN - REQ_HDR_LEN - CHECKSUM_LEN) ||
			req->rlen > (BUF_LEN - ACK_HDR_LEN - CHECKSUM_LEN)) अणु
		dev_err(&पूर्णांकf->dev, "too much data wlen=%d rlen=%d\n",
			req->wlen, req->rlen);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	state->buf[0] = REQ_HDR_LEN + req->wlen + CHECKSUM_LEN - 1;
	state->buf[1] = req->mbox;
	state->buf[2] = req->cmd;
	state->buf[3] = state->seq++;
	स_नकल(&state->buf[REQ_HDR_LEN], req->wbuf, req->wlen);

	wlen = REQ_HDR_LEN + req->wlen + CHECKSUM_LEN;
	rlen = ACK_HDR_LEN + req->rlen + CHECKSUM_LEN;

	/* calc and add checksum */
	checksum = af9035_checksum(state->buf, state->buf[0] - 1);
	state->buf[state->buf[0] - 1] = (checksum >> 8);
	state->buf[state->buf[0] - 0] = (checksum & 0xff);

	/* no ack क्रम these packets */
	अगर (req->cmd == CMD_FW_DL)
		rlen = 0;

	ret = dvb_usbv2_generic_rw_locked(d,
			state->buf, wlen, state->buf, rlen);
	अगर (ret)
		जाओ निकास;

	/* no ack क्रम those packets */
	अगर (req->cmd == CMD_FW_DL)
		जाओ निकास;

	/* verअगरy checksum */
	checksum = af9035_checksum(state->buf, rlen - 2);
	पंचांगp_checksum = (state->buf[rlen - 2] << 8) | state->buf[rlen - 1];
	अगर (पंचांगp_checksum != checksum) अणु
		dev_err(&पूर्णांकf->dev, "command=%02x checksum mismatch (%04x != %04x)\n",
			req->cmd, पंचांगp_checksum, checksum);
		ret = -EIO;
		जाओ निकास;
	पूर्ण

	/* check status */
	अगर (state->buf[2]) अणु
		/* fw वापसs status 1 when IR code was not received */
		अगर (req->cmd == CMD_IR_GET || state->buf[2] == 1) अणु
			ret = 1;
			जाओ निकास;
		पूर्ण

		dev_dbg(&पूर्णांकf->dev, "command=%02x failed fw error=%d\n",
			req->cmd, state->buf[2]);
		ret = -EIO;
		जाओ निकास;
	पूर्ण

	/* पढ़ो request, copy वापसed data to वापस buf */
	अगर (req->rlen)
		स_नकल(req->rbuf, &state->buf[ACK_HDR_LEN], req->rlen);
निकास:
	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

/* ग_लिखो multiple रेजिस्टरs */
अटल पूर्णांक af9035_wr_regs(काष्ठा dvb_usb_device *d, u32 reg, u8 *val, पूर्णांक len)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	u8 wbuf[MAX_XFER_SIZE];
	u8 mbox = (reg >> 16) & 0xff;
	काष्ठा usb_req req = अणु CMD_MEM_WR, mbox, 6 + len, wbuf, 0, शून्य पूर्ण;

	अगर (6 + len > माप(wbuf)) अणु
		dev_warn(&पूर्णांकf->dev, "i2c wr: len=%d is too big!\n", len);
		वापस -EOPNOTSUPP;
	पूर्ण

	wbuf[0] = len;
	wbuf[1] = 2;
	wbuf[2] = 0;
	wbuf[3] = 0;
	wbuf[4] = (reg >> 8) & 0xff;
	wbuf[5] = (reg >> 0) & 0xff;
	स_नकल(&wbuf[6], val, len);

	वापस af9035_ctrl_msg(d, &req);
पूर्ण

/* पढ़ो multiple रेजिस्टरs */
अटल पूर्णांक af9035_rd_regs(काष्ठा dvb_usb_device *d, u32 reg, u8 *val, पूर्णांक len)
अणु
	u8 wbuf[] = अणु len, 2, 0, 0, (reg >> 8) & 0xff, reg & 0xff पूर्ण;
	u8 mbox = (reg >> 16) & 0xff;
	काष्ठा usb_req req = अणु CMD_MEM_RD, mbox, माप(wbuf), wbuf, len, val पूर्ण;

	वापस af9035_ctrl_msg(d, &req);
पूर्ण

/* ग_लिखो single रेजिस्टर */
अटल पूर्णांक af9035_wr_reg(काष्ठा dvb_usb_device *d, u32 reg, u8 val)
अणु
	वापस af9035_wr_regs(d, reg, &val, 1);
पूर्ण

/* पढ़ो single रेजिस्टर */
अटल पूर्णांक af9035_rd_reg(काष्ठा dvb_usb_device *d, u32 reg, u8 *val)
अणु
	वापस af9035_rd_regs(d, reg, val, 1);
पूर्ण

/* ग_लिखो single रेजिस्टर with mask */
अटल पूर्णांक af9035_wr_reg_mask(काष्ठा dvb_usb_device *d, u32 reg, u8 val,
		u8 mask)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	/* no need क्रम पढ़ो अगर whole reg is written */
	अगर (mask != 0xff) अणु
		ret = af9035_rd_regs(d, reg, &पंचांगp, 1);
		अगर (ret)
			वापस ret;

		val &= mask;
		पंचांगp &= ~mask;
		val |= पंचांगp;
	पूर्ण

	वापस af9035_wr_regs(d, reg, &val, 1);
पूर्ण

अटल पूर्णांक af9035_add_i2c_dev(काष्ठा dvb_usb_device *d, स्थिर अक्षर *type,
		u8 addr, व्योम *platक्रमm_data, काष्ठा i2c_adapter *adapter)
अणु
	पूर्णांक ret, num;
	काष्ठा state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info board_info = अणु
		.addr = addr,
		.platक्रमm_data = platक्रमm_data,
	पूर्ण;

	strscpy(board_info.type, type, I2C_NAME_SIZE);

	/* find first मुक्त client */
	क्रम (num = 0; num < AF9035_I2C_CLIENT_MAX; num++) अणु
		अगर (state->i2c_client[num] == शून्य)
			अवरोध;
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "num=%d\n", num);

	अगर (num == AF9035_I2C_CLIENT_MAX) अणु
		dev_err(&पूर्णांकf->dev, "I2C client out of index\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	request_module("%s", board_info.type);

	/* रेजिस्टर I2C device */
	client = i2c_new_client_device(adapter, &board_info);
	अगर (!i2c_client_has_driver(client)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* increase I2C driver usage count */
	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	state->i2c_client[num] = client;
	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम af9035_del_i2c_dev(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक num;
	काष्ठा state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा i2c_client *client;

	/* find last used client */
	num = AF9035_I2C_CLIENT_MAX;
	जबतक (num--) अणु
		अगर (state->i2c_client[num] != शून्य)
			अवरोध;
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "num=%d\n", num);

	अगर (num == -1) अणु
		dev_err(&पूर्णांकf->dev, "I2C client out of index\n");
		जाओ err;
	पूर्ण

	client = state->i2c_client[num];

	/* decrease I2C driver usage count */
	module_put(client->dev.driver->owner);

	/* unरेजिस्टर I2C device */
	i2c_unरेजिस्टर_device(client);

	state->i2c_client[num] = शून्य;
	वापस;
err:
	dev_dbg(&पूर्णांकf->dev, "failed\n");
पूर्ण

अटल पूर्णांक af9035_i2c_master_xfer(काष्ठा i2c_adapter *adap,
		काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा state *state = d_to_priv(d);
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	/*
	 * AF9035 I2C sub header is 5 bytes दीर्घ. Meaning of those bytes are:
	 * 0: data len
	 * 1: I2C addr << 1
	 * 2: reg addr len
	 *    byte 3 and 4 can be used as reg addr
	 * 3: reg addr MSB
	 *    used when reg addr len is set to 2
	 * 4: reg addr LSB
	 *    used when reg addr len is set to 1 or 2
	 *
	 * For the simplअगरy we करो not use रेजिस्टर addr at all.
	 * NOTE: As a firmware knows tuner type there is very small possibility
	 * there could be some tuner I2C hacks करोne by firmware and this may
	 * lead problems अगर firmware expects those bytes are used.
	 *
	 * TODO: Here is few hacks. AF9035 chip पूर्णांकegrates AF9033 demodulator.
	 * IT9135 chip पूर्णांकegrates AF9033 demodulator and RF tuner. For dual
	 * tuner devices, there is also बाह्यal AF9033 demodulator connected
	 * via बाह्यal I2C bus. All AF9033 demod I2C traffic, both single and
	 * dual tuner configuration, is covered by firmware - actual USB IO
	 * looks just like a memory access.
	 * In हाल of IT913x chip, there is own tuner driver. It is implemented
	 * currently as a I2C driver, even tuner IP block is likely build
	 * directly पूर्णांकo the demodulator memory space and there is no own I2C
	 * bus. I2C subप्रणाली करोes not allow रेजिस्टर multiple devices to same
	 * bus, having same slave address. Due to that we reuse demod address,
	 * shअगरted by one bit, on that हाल.
	 *
	 * For IT930x we use a dअगरferent command and the sub header is
	 * dअगरferent as well:
	 * 0: data len
	 * 1: I2C bus (0x03 seems to be only value used)
	 * 2: I2C addr << 1
	 */
#घोषणा AF9035_IS_I2C_XFER_WRITE_READ(_msg, _num) \
	(_num == 2 && !(_msg[0].flags & I2C_M_RD) && (_msg[1].flags & I2C_M_RD))
#घोषणा AF9035_IS_I2C_XFER_WRITE(_msg, _num) \
	(_num == 1 && !(_msg[0].flags & I2C_M_RD))
#घोषणा AF9035_IS_I2C_XFER_READ(_msg, _num) \
	(_num == 1 && (_msg[0].flags & I2C_M_RD))

	अगर (AF9035_IS_I2C_XFER_WRITE_READ(msg, num)) अणु
		अगर (msg[0].len > 40 || msg[1].len > 40) अणु
			/* TODO: correct limits > 40 */
			ret = -EOPNOTSUPP;
		पूर्ण अन्यथा अगर ((msg[0].addr == state->af9033_i2c_addr[0]) ||
			   (msg[0].addr == state->af9033_i2c_addr[1])) अणु
			/* demod access via firmware पूर्णांकerface */
			u32 reg = msg[0].buf[0] << 16 | msg[0].buf[1] << 8 |
					msg[0].buf[2];

			अगर (msg[0].addr == state->af9033_i2c_addr[1])
				reg |= 0x100000;

			ret = af9035_rd_regs(d, reg, &msg[1].buf[0],
					msg[1].len);
		पूर्ण अन्यथा अगर (state->no_पढ़ो) अणु
			स_रखो(msg[1].buf, 0, msg[1].len);
			ret = 0;
		पूर्ण अन्यथा अणु
			/* I2C ग_लिखो + पढ़ो */
			u8 buf[MAX_XFER_SIZE];
			काष्ठा usb_req req = अणु CMD_I2C_RD, 0, 5 + msg[0].len,
					buf, msg[1].len, msg[1].buf पूर्ण;

			अगर (state->chip_type == 0x9306) अणु
				req.cmd = CMD_GENERIC_I2C_RD;
				req.wlen = 3 + msg[0].len;
			पूर्ण
			req.mbox |= ((msg[0].addr & 0x80)  >>  3);

			buf[0] = msg[1].len;
			अगर (state->chip_type == 0x9306) अणु
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addr << 1;
				स_नकल(&buf[3], msg[0].buf, msg[0].len);
			पूर्ण अन्यथा अणु
				buf[1] = msg[0].addr << 1;
				buf[3] = 0x00; /* reg addr MSB */
				buf[4] = 0x00; /* reg addr LSB */

				/* Keep prev behavior क्रम ग_लिखो req len > 2*/
				अगर (msg[0].len > 2) अणु
					buf[2] = 0x00; /* reg addr len */
					स_नकल(&buf[5], msg[0].buf, msg[0].len);

				/* Use reg addr fields अगर ग_लिखो req len <= 2 */
				पूर्ण अन्यथा अणु
					req.wlen = 5;
					buf[2] = msg[0].len;
					अगर (msg[0].len == 2) अणु
						buf[3] = msg[0].buf[0];
						buf[4] = msg[0].buf[1];
					पूर्ण अन्यथा अगर (msg[0].len == 1) अणु
						buf[4] = msg[0].buf[0];
					पूर्ण
				पूर्ण
			पूर्ण
			ret = af9035_ctrl_msg(d, &req);
		पूर्ण
	पूर्ण अन्यथा अगर (AF9035_IS_I2C_XFER_WRITE(msg, num)) अणु
		अगर (msg[0].len > 40) अणु
			/* TODO: correct limits > 40 */
			ret = -EOPNOTSUPP;
		पूर्ण अन्यथा अगर ((msg[0].addr == state->af9033_i2c_addr[0]) ||
			   (msg[0].addr == state->af9033_i2c_addr[1])) अणु
			/* demod access via firmware पूर्णांकerface */
			u32 reg = msg[0].buf[0] << 16 | msg[0].buf[1] << 8 |
					msg[0].buf[2];

			अगर (msg[0].addr == state->af9033_i2c_addr[1])
				reg |= 0x100000;

			ret = (msg[0].len >= 3) ? af9035_wr_regs(d, reg,
							         &msg[0].buf[3],
							         msg[0].len - 3)
					        : -EOPNOTSUPP;
		पूर्ण अन्यथा अणु
			/* I2C ग_लिखो */
			u8 buf[MAX_XFER_SIZE];
			काष्ठा usb_req req = अणु CMD_I2C_WR, 0, 5 + msg[0].len,
					buf, 0, शून्य पूर्ण;

			अगर (state->chip_type == 0x9306) अणु
				req.cmd = CMD_GENERIC_I2C_WR;
				req.wlen = 3 + msg[0].len;
			पूर्ण

			req.mbox |= ((msg[0].addr & 0x80)  >>  3);
			buf[0] = msg[0].len;
			अगर (state->chip_type == 0x9306) अणु
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addr << 1;
				स_नकल(&buf[3], msg[0].buf, msg[0].len);
			पूर्ण अन्यथा अणु
				buf[1] = msg[0].addr << 1;
				buf[2] = 0x00; /* reg addr len */
				buf[3] = 0x00; /* reg addr MSB */
				buf[4] = 0x00; /* reg addr LSB */
				स_नकल(&buf[5], msg[0].buf, msg[0].len);
			पूर्ण
			ret = af9035_ctrl_msg(d, &req);
		पूर्ण
	पूर्ण अन्यथा अगर (AF9035_IS_I2C_XFER_READ(msg, num)) अणु
		अगर (msg[0].len > 40) अणु
			/* TODO: correct limits > 40 */
			ret = -EOPNOTSUPP;
		पूर्ण अन्यथा अगर (state->no_पढ़ो) अणु
			स_रखो(msg[0].buf, 0, msg[0].len);
			ret = 0;
		पूर्ण अन्यथा अणु
			/* I2C पढ़ो */
			u8 buf[5];
			काष्ठा usb_req req = अणु CMD_I2C_RD, 0, माप(buf),
						buf, msg[0].len, msg[0].buf पूर्ण;

			अगर (state->chip_type == 0x9306) अणु
				req.cmd = CMD_GENERIC_I2C_RD;
				req.wlen = 3;
			पूर्ण
			req.mbox |= ((msg[0].addr & 0x80)  >>  3);
			buf[0] = msg[0].len;
			अगर (state->chip_type == 0x9306) अणु
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addr << 1;
			पूर्ण अन्यथा अणु
				buf[1] = msg[0].addr << 1;
				buf[2] = 0x00; /* reg addr len */
				buf[3] = 0x00; /* reg addr MSB */
				buf[4] = 0x00; /* reg addr LSB */
			पूर्ण
			ret = af9035_ctrl_msg(d, &req);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We support only three kind of I2C transactions:
		 * 1) 1 x ग_लिखो + 1 x पढ़ो (repeated start)
		 * 2) 1 x ग_लिखो
		 * 3) 1 x पढ़ो
		 */
		ret = -EOPNOTSUPP;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);

	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस num;
पूर्ण

अटल u32 af9035_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm af9035_i2c_algo = अणु
	.master_xfer = af9035_i2c_master_xfer,
	.functionality = af9035_i2c_functionality,
पूर्ण;

अटल पूर्णांक af9035_identअगरy_state(काष्ठा dvb_usb_device *d, स्थिर अक्षर **name)
अणु
	काष्ठा state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, i, ts_mode_invalid;
	अचिन्हित पूर्णांक uपंचांगp, eeprom_addr;
	u8 पंचांगp;
	u8 wbuf[1] = अणु 1 पूर्ण;
	u8 rbuf[4];
	काष्ठा usb_req req = अणु CMD_FW_QUERYINFO, 0, माप(wbuf), wbuf,
			माप(rbuf), rbuf पूर्ण;

	ret = af9035_rd_regs(d, 0x1222, rbuf, 3);
	अगर (ret < 0)
		जाओ err;

	state->chip_version = rbuf[0];
	state->chip_type = rbuf[2] << 8 | rbuf[1] << 0;

	ret = af9035_rd_reg(d, 0x384f, &state->prechip_version);
	अगर (ret < 0)
		जाओ err;

	dev_info(&पूर्णांकf->dev, "prechip_version=%02x chip_version=%02x chip_type=%04x\n",
		 state->prechip_version, state->chip_version, state->chip_type);

	अगर (state->chip_type == 0x9135) अणु
		अगर (state->chip_version == 0x02) अणु
			*name = AF9035_FIRMWARE_IT9135_V2;
			uपंचांगp = 0x00461d;
		पूर्ण अन्यथा अणु
			*name = AF9035_FIRMWARE_IT9135_V1;
			uपंचांगp = 0x00461b;
		पूर्ण

		/* Check अगर eeprom exists */
		ret = af9035_rd_reg(d, uपंचांगp, &पंचांगp);
		अगर (ret < 0)
			जाओ err;

		अगर (पंचांगp == 0x00) अणु
			dev_dbg(&पूर्णांकf->dev, "no eeprom\n");
			state->no_eeprom = true;
			जाओ check_firmware_status;
		पूर्ण

		eeprom_addr = EEPROM_BASE_IT9135;
	पूर्ण अन्यथा अगर (state->chip_type == 0x9306) अणु
		*name = AF9035_FIRMWARE_IT9303;
		state->no_eeprom = true;
		जाओ check_firmware_status;
	पूर्ण अन्यथा अणु
		*name = AF9035_FIRMWARE_AF9035;
		eeprom_addr = EEPROM_BASE_AF9035;
	पूर्ण

	/* Read and store eeprom */
	क्रम (i = 0; i < 256; i += 32) अणु
		ret = af9035_rd_regs(d, eeprom_addr + i, &state->eeprom[i], 32);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "eeprom dump:\n");
	क्रम (i = 0; i < 256; i += 16)
		dev_dbg(&पूर्णांकf->dev, "%*ph\n", 16, &state->eeprom[i]);

	/* check क्रम dual tuner mode */
	पंचांगp = state->eeprom[EEPROM_TS_MODE];
	ts_mode_invalid = 0;
	चयन (पंचांगp) अणु
	हाल 0:
		अवरोध;
	हाल 1:
	हाल 3:
		state->dual_mode = true;
		अवरोध;
	हाल 5:
		अगर (state->chip_type != 0x9135 && state->chip_type != 0x9306)
			state->dual_mode = true;	/* AF9035 */
		अन्यथा
			ts_mode_invalid = 1;
		अवरोध;
	शेष:
		ts_mode_invalid = 1;
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "ts mode=%d dual mode=%d\n", पंचांगp, state->dual_mode);

	अगर (ts_mode_invalid)
		dev_info(&पूर्णांकf->dev, "ts mode=%d not supported, defaulting to single tuner mode!", पंचांगp);

check_firmware_status:
	ret = af9035_ctrl_msg(d, &req);
	अगर (ret < 0)
		जाओ err;

	dev_dbg(&पूर्णांकf->dev, "reply=%*ph\n", 4, rbuf);
	अगर (rbuf[0] || rbuf[1] || rbuf[2] || rbuf[3])
		ret = WARM;
	अन्यथा
		ret = COLD;

	वापस ret;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_करोwnload_firmware_old(काष्ठा dvb_usb_device *d,
		स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, i, j, len;
	u8 wbuf[1];
	काष्ठा usb_req req = अणु 0, 0, 0, शून्य, 0, शून्य पूर्ण;
	काष्ठा usb_req req_fw_dl = अणु CMD_FW_DL, 0, 0, wbuf, 0, शून्य पूर्ण;
	u8 hdr_core;
	u16 hdr_addr, hdr_data_len, hdr_checksum;
	#घोषणा MAX_DATA 58
	#घोषणा HDR_SIZE 7

	/*
	 * Thanks to Daniel Glथघckner <daniel-gl@gmx.net> about that info!
	 *
	 * byte 0: MCS 51 core
	 *  There are two inside the AF9035 (1=Link and 2=OFDM) with separate
	 *  address spaces
	 * byte 1-2: Big endian destination address
	 * byte 3-4: Big endian number of data bytes following the header
	 * byte 5-6: Big endian header checksum, apparently ignored by the chip
	 *  Calculated as ~(h[0]*256+h[1]+h[2]*256+h[3]+h[4]*256)
	 */

	क्रम (i = fw->size; i > HDR_SIZE;) अणु
		hdr_core = fw->data[fw->size - i + 0];
		hdr_addr = fw->data[fw->size - i + 1] << 8;
		hdr_addr |= fw->data[fw->size - i + 2] << 0;
		hdr_data_len = fw->data[fw->size - i + 3] << 8;
		hdr_data_len |= fw->data[fw->size - i + 4] << 0;
		hdr_checksum = fw->data[fw->size - i + 5] << 8;
		hdr_checksum |= fw->data[fw->size - i + 6] << 0;

		dev_dbg(&पूर्णांकf->dev, "core=%d addr=%04x data_len=%d checksum=%04x\n",
			hdr_core, hdr_addr, hdr_data_len, hdr_checksum);

		अगर (((hdr_core != 1) && (hdr_core != 2)) ||
				(hdr_data_len > i)) अणु
			dev_dbg(&पूर्णांकf->dev, "bad firmware\n");
			अवरोध;
		पूर्ण

		/* करोwnload begin packet */
		req.cmd = CMD_FW_DL_BEGIN;
		ret = af9035_ctrl_msg(d, &req);
		अगर (ret < 0)
			जाओ err;

		/* करोwnload firmware packet(s) */
		क्रम (j = HDR_SIZE + hdr_data_len; j > 0; j -= MAX_DATA) अणु
			len = j;
			अगर (len > MAX_DATA)
				len = MAX_DATA;
			req_fw_dl.wlen = len;
			req_fw_dl.wbuf = (u8 *) &fw->data[fw->size - i +
					HDR_SIZE + hdr_data_len - j];
			ret = af9035_ctrl_msg(d, &req_fw_dl);
			अगर (ret < 0)
				जाओ err;
		पूर्ण

		/* करोwnload end packet */
		req.cmd = CMD_FW_DL_END;
		ret = af9035_ctrl_msg(d, &req);
		अगर (ret < 0)
			जाओ err;

		i -= hdr_data_len + HDR_SIZE;

		dev_dbg(&पूर्णांकf->dev, "data uploaded=%zu\n", fw->size - i);
	पूर्ण

	/* prपूर्णांक warn अगर firmware is bad, जारी and see what happens */
	अगर (i)
		dev_warn(&पूर्णांकf->dev, "bad firmware\n");

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_करोwnload_firmware_new(काष्ठा dvb_usb_device *d,
		स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, i, i_prev;
	काष्ठा usb_req req_fw_dl = अणु CMD_FW_SCATTER_WR, 0, 0, शून्य, 0, शून्य पूर्ण;
	#घोषणा HDR_SIZE 7

	/*
	 * There seems to be following firmware header. Meaning of bytes 0-3
	 * is unknown.
	 *
	 * 0: 3
	 * 1: 0, 1
	 * 2: 0
	 * 3: 1, 2, 3
	 * 4: addr MSB
	 * 5: addr LSB
	 * 6: count of data bytes ?
	 */
	क्रम (i = HDR_SIZE, i_prev = 0; i <= fw->size; i++) अणु
		अगर (i == fw->size ||
				(fw->data[i + 0] == 0x03 &&
				(fw->data[i + 1] == 0x00 ||
				fw->data[i + 1] == 0x01) &&
				fw->data[i + 2] == 0x00)) अणु
			req_fw_dl.wlen = i - i_prev;
			req_fw_dl.wbuf = (u8 *) &fw->data[i_prev];
			i_prev = i;
			ret = af9035_ctrl_msg(d, &req_fw_dl);
			अगर (ret < 0)
				जाओ err;

			dev_dbg(&पूर्णांकf->dev, "data uploaded=%d\n", i);
		पूर्ण
	पूर्ण

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_करोwnload_firmware(काष्ठा dvb_usb_device *d,
		स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा state *state = d_to_priv(d);
	पूर्णांक ret;
	u8 wbuf[1];
	u8 rbuf[4];
	u8 पंचांगp;
	काष्ठा usb_req req = अणु 0, 0, 0, शून्य, 0, शून्य पूर्ण;
	काष्ठा usb_req req_fw_ver = अणु CMD_FW_QUERYINFO, 0, 1, wbuf, 4, rbuf पूर्ण;

	dev_dbg(&पूर्णांकf->dev, "\n");

	/*
	 * In हाल of dual tuner configuration we need to करो some extra
	 * initialization in order to करोwnload firmware to slave demod too,
	 * which is करोne by master demod.
	 * Master feeds also घड़ी and controls घातer via GPIO.
	 */
	अगर (state->dual_mode) अणु
		/* configure gpioh1, reset & घातer slave demod */
		ret = af9035_wr_reg_mask(d, 0x00d8b0, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0x00d8b1, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0x00d8af, 0x00, 0x01);
		अगर (ret < 0)
			जाओ err;

		usleep_range(10000, 50000);

		ret = af9035_wr_reg_mask(d, 0x00d8af, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		/* tell the slave I2C address */
		पंचांगp = state->eeprom[EEPROM_2ND_DEMOD_ADDR];

		/* Use शेष I2C address अगर eeprom has no address set */
		अगर (!पंचांगp)
			पंचांगp = 0x1d << 1; /* 8-bit क्रमmat used by chip */

		अगर ((state->chip_type == 0x9135) ||
				(state->chip_type == 0x9306)) अणु
			ret = af9035_wr_reg(d, 0x004bfb, पंचांगp);
			अगर (ret < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			ret = af9035_wr_reg(d, 0x00417f, पंचांगp);
			अगर (ret < 0)
				जाओ err;

			/* enable घड़ी out */
			ret = af9035_wr_reg_mask(d, 0x00d81a, 0x01, 0x01);
			अगर (ret < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (fw->data[0] == 0x01)
		ret = af9035_करोwnload_firmware_old(d, fw);
	अन्यथा
		ret = af9035_करोwnload_firmware_new(d, fw);
	अगर (ret < 0)
		जाओ err;

	/* firmware loaded, request boot */
	req.cmd = CMD_FW_BOOT;
	ret = af9035_ctrl_msg(d, &req);
	अगर (ret < 0)
		जाओ err;

	/* ensure firmware starts */
	wbuf[0] = 1;
	ret = af9035_ctrl_msg(d, &req_fw_ver);
	अगर (ret < 0)
		जाओ err;

	अगर (!(rbuf[0] || rbuf[1] || rbuf[2] || rbuf[3])) अणु
		dev_err(&पूर्णांकf->dev, "firmware did not run\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	dev_info(&पूर्णांकf->dev, "firmware version=%d.%d.%d.%d",
		 rbuf[0], rbuf[1], rbuf[2], rbuf[3]);

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_पढ़ो_config(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा state *state = d_to_priv(d);
	पूर्णांक ret, i;
	u8 पंचांगp;
	u16 पंचांगp16;

	/* Demod I2C address */
	state->af9033_i2c_addr[0] = 0x1c;
	state->af9033_i2c_addr[1] = 0x1d;
	state->af9033_config[0].adc_multiplier = AF9033_ADC_MULTIPLIER_2X;
	state->af9033_config[1].adc_multiplier = AF9033_ADC_MULTIPLIER_2X;
	state->af9033_config[0].ts_mode = AF9033_TS_MODE_USB;
	state->af9033_config[1].ts_mode = AF9033_TS_MODE_SERIAL;
	state->it930x_addresses = 0;

	अगर (state->chip_type == 0x9135) अणु
		/* feed घड़ी क्रम पूर्णांकegrated RF tuner */
		state->af9033_config[0].dyn0_clk = true;
		state->af9033_config[1].dyn0_clk = true;

		अगर (state->chip_version == 0x02) अणु
			state->af9033_config[0].tuner = AF9033_TUNER_IT9135_60;
			state->af9033_config[1].tuner = AF9033_TUNER_IT9135_60;
		पूर्ण अन्यथा अणु
			state->af9033_config[0].tuner = AF9033_TUNER_IT9135_38;
			state->af9033_config[1].tuner = AF9033_TUNER_IT9135_38;
		पूर्ण

		अगर (state->no_eeprom) अणु
			/* Remote controller to NEC polling by शेष */
			state->ir_mode = 0x05;
			state->ir_type = 0x00;

			जाओ skip_eeprom;
		पूर्ण
	पूर्ण अन्यथा अगर (state->chip_type == 0x9306) अणु
		/*
		 * IT930x is an USB bridge, only single demod-single tuner
		 * configurations seen so far.
		 */
		अगर ((le16_to_cpu(d->udev->descriptor.idVenकरोr) == USB_VID_AVERMEDIA) &&
		    (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_AVERMEDIA_TD310)) अणु
			state->it930x_addresses = 1;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Remote controller */
	state->ir_mode = state->eeprom[EEPROM_IR_MODE];
	state->ir_type = state->eeprom[EEPROM_IR_TYPE];

	अगर (state->dual_mode) अणु
		/* Read 2nd demodulator I2C address. 8-bit क्रमmat on eeprom */
		पंचांगp = state->eeprom[EEPROM_2ND_DEMOD_ADDR];
		अगर (पंचांगp)
			state->af9033_i2c_addr[1] = पंचांगp >> 1;

		dev_dbg(&पूर्णांकf->dev, "2nd demod I2C addr=%02x\n",
			state->af9033_i2c_addr[1]);
	पूर्ण

	क्रम (i = 0; i < state->dual_mode + 1; i++) अणु
		अचिन्हित पूर्णांक eeprom_offset = 0;

		/* tuner */
		पंचांगp = state->eeprom[EEPROM_1_TUNER_ID + eeprom_offset];
		dev_dbg(&पूर्णांकf->dev, "[%d]tuner=%02x\n", i, पंचांगp);

		/* tuner sanity check */
		अगर (state->chip_type == 0x9135) अणु
			अगर (state->chip_version == 0x02) अणु
				/* IT9135 BX (v2) */
				चयन (पंचांगp) अणु
				हाल AF9033_TUNER_IT9135_60:
				हाल AF9033_TUNER_IT9135_61:
				हाल AF9033_TUNER_IT9135_62:
					state->af9033_config[i].tuner = पंचांगp;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* IT9135 AX (v1) */
				चयन (पंचांगp) अणु
				हाल AF9033_TUNER_IT9135_38:
				हाल AF9033_TUNER_IT9135_51:
				हाल AF9033_TUNER_IT9135_52:
					state->af9033_config[i].tuner = पंचांगp;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* AF9035 */
			state->af9033_config[i].tuner = पंचांगp;
		पूर्ण

		अगर (state->af9033_config[i].tuner != पंचांगp) अणु
			dev_info(&पूर्णांकf->dev, "[%d] overriding tuner from %02x to %02x\n",
				 i, पंचांगp, state->af9033_config[i].tuner);
		पूर्ण

		चयन (state->af9033_config[i].tuner) अणु
		हाल AF9033_TUNER_TUA9001:
		हाल AF9033_TUNER_FC0011:
		हाल AF9033_TUNER_MXL5007T:
		हाल AF9033_TUNER_TDA18218:
		हाल AF9033_TUNER_FC2580:
		हाल AF9033_TUNER_FC0012:
			state->af9033_config[i].spec_inv = 1;
			अवरोध;
		हाल AF9033_TUNER_IT9135_38:
		हाल AF9033_TUNER_IT9135_51:
		हाल AF9033_TUNER_IT9135_52:
		हाल AF9033_TUNER_IT9135_60:
		हाल AF9033_TUNER_IT9135_61:
		हाल AF9033_TUNER_IT9135_62:
			अवरोध;
		शेष:
			dev_warn(&पूर्णांकf->dev, "tuner id=%02x not supported, please report!",
				 पंचांगp);
		पूर्ण

		/* disable dual mode अगर driver करोes not support it */
		अगर (i == 1)
			चयन (state->af9033_config[i].tuner) अणु
			हाल AF9033_TUNER_FC0012:
			हाल AF9033_TUNER_IT9135_38:
			हाल AF9033_TUNER_IT9135_51:
			हाल AF9033_TUNER_IT9135_52:
			हाल AF9033_TUNER_IT9135_60:
			हाल AF9033_TUNER_IT9135_61:
			हाल AF9033_TUNER_IT9135_62:
			हाल AF9033_TUNER_MXL5007T:
				अवरोध;
			शेष:
				state->dual_mode = false;
				dev_info(&पूर्णांकf->dev, "driver does not support 2nd tuner and will disable it");
		पूर्ण

		/* tuner IF frequency */
		पंचांगp = state->eeprom[EEPROM_1_IF_L + eeprom_offset];
		पंचांगp16 = पंचांगp << 0;
		पंचांगp = state->eeprom[EEPROM_1_IF_H + eeprom_offset];
		पंचांगp16 |= पंचांगp << 8;
		dev_dbg(&पूर्णांकf->dev, "[%d]IF=%d\n", i, पंचांगp16);

		eeprom_offset += 0x10; /* shअगरt क्रम the 2nd tuner params */
	पूर्ण

skip_eeprom:
	/* get demod घड़ी */
	ret = af9035_rd_reg(d, 0x00d800, &पंचांगp);
	अगर (ret < 0)
		जाओ err;

	पंचांगp = (पंचांगp >> 0) & 0x0f;

	क्रम (i = 0; i < ARRAY_SIZE(state->af9033_config); i++) अणु
		अगर (state->chip_type == 0x9135)
			state->af9033_config[i].घड़ी = घड़ी_lut_it9135[पंचांगp];
		अन्यथा
			state->af9033_config[i].घड़ी = घड़ी_lut_af9035[पंचांगp];
	पूर्ण

	state->no_पढ़ो = false;
	/* Some MXL5007T devices cannot properly handle tuner I2C पढ़ो ops. */
	अगर (state->af9033_config[0].tuner == AF9033_TUNER_MXL5007T &&
		le16_to_cpu(d->udev->descriptor.idVenकरोr) == USB_VID_AVERMEDIA)

		चयन (le16_to_cpu(d->udev->descriptor.idProduct)) अणु
		हाल USB_PID_AVERMEDIA_A867:
		हाल USB_PID_AVERMEDIA_TWINSTAR:
			dev_info(&पूर्णांकf->dev,
				 "Device may have issues with I2C read operations. Enabling fix.\n");
			state->no_पढ़ो = true;
			अवरोध;
		पूर्ण

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_tua9001_tuner_callback(काष्ठा dvb_usb_device *d,
		पूर्णांक cmd, पूर्णांक arg)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u8 val;

	dev_dbg(&पूर्णांकf->dev, "cmd=%d arg=%d\n", cmd, arg);

	/*
	 * CEN     always enabled by hardware wiring
	 * RESETN  GPIOT3
	 * RXEN    GPIOT2
	 */

	चयन (cmd) अणु
	हाल TUA9001_CMD_RESETN:
		अगर (arg)
			val = 0x00;
		अन्यथा
			val = 0x01;

		ret = af9035_wr_reg_mask(d, 0x00d8e7, val, 0x01);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	हाल TUA9001_CMD_RXEN:
		अगर (arg)
			val = 0x01;
		अन्यथा
			val = 0x00;

		ret = af9035_wr_reg_mask(d, 0x00d8eb, val, 0x01);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	पूर्ण

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण


अटल पूर्णांक af9035_fc0011_tuner_callback(काष्ठा dvb_usb_device *d,
		पूर्णांक cmd, पूर्णांक arg)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल FC0011_FE_CALLBACK_POWER:
		/* Tuner enable */
		ret = af9035_wr_reg_mask(d, 0xd8eb, 1, 1);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0xd8ec, 1, 1);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0xd8ed, 1, 1);
		अगर (ret < 0)
			जाओ err;

		/* LED */
		ret = af9035_wr_reg_mask(d, 0xd8d0, 1, 1);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0xd8d1, 1, 1);
		अगर (ret < 0)
			जाओ err;

		usleep_range(10000, 50000);
		अवरोध;
	हाल FC0011_FE_CALLBACK_RESET:
		ret = af9035_wr_reg(d, 0xd8e9, 1);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg(d, 0xd8e8, 1);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg(d, 0xd8e7, 1);
		अगर (ret < 0)
			जाओ err;

		usleep_range(10000, 20000);

		ret = af9035_wr_reg(d, 0xd8e7, 0);
		अगर (ret < 0)
			जाओ err;

		usleep_range(10000, 20000);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_tuner_callback(काष्ठा dvb_usb_device *d, पूर्णांक cmd, पूर्णांक arg)
अणु
	काष्ठा state *state = d_to_priv(d);

	चयन (state->af9033_config[0].tuner) अणु
	हाल AF9033_TUNER_FC0011:
		वापस af9035_fc0011_tuner_callback(d, cmd, arg);
	हाल AF9033_TUNER_TUA9001:
		वापस af9035_tua9001_tuner_callback(d, cmd, arg);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक af9035_frontend_callback(व्योम *adapter_priv, पूर्णांक component,
				    पूर्णांक cmd, पूर्णांक arg)
अणु
	काष्ठा i2c_adapter *adap = adapter_priv;
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "component=%d cmd=%d arg=%d\n",
		component, cmd, arg);

	चयन (component) अणु
	हाल DVB_FRONTEND_COMPONENT_TUNER:
		वापस af9035_tuner_callback(d, cmd, arg);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक af9035_get_adapter_count(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा state *state = d_to_priv(d);

	वापस state->dual_mode + 1;
पूर्ण

अटल पूर्णांक af9035_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "adap->id=%d\n", adap->id);

	अगर (!state->af9033_config[adap->id].tuner) अणु
		/* unsupported tuner */
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	state->af9033_config[adap->id].fe = &adap->fe[0];
	state->af9033_config[adap->id].ops = &state->ops;
	ret = af9035_add_i2c_dev(d, "af9033", state->af9033_i2c_addr[adap->id],
			&state->af9033_config[adap->id], &d->i2c_adap);
	अगर (ret)
		जाओ err;

	अगर (adap->fe[0] == शून्य) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* disable I2C-gate */
	adap->fe[0]->ops.i2c_gate_ctrl = शून्य;
	adap->fe[0]->callback = af9035_frontend_callback;

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

/*
 * The I2C speed रेजिस्टर is calculated with:
 *	I2C speed रेजिस्टर = (1000000000 / (24.4 * 16 * I2C_speed))
 *
 * The शेष speed रेजिस्टर क्रम it930x is 7, with means a
 * speed of ~366 kbps
 */
#घोषणा I2C_SPEED_366K 7

अटल पूर्णांक it930x_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	काष्ठा si2168_config si2168_config;
	काष्ठा i2c_adapter *adapter;

	dev_dbg(&पूर्णांकf->dev, "adap->id=%d\n", adap->id);

	/* I2C master bus 2 घड़ी speed 366k */
	ret = af9035_wr_reg(d, 0x00f6a7, I2C_SPEED_366K);
	अगर (ret < 0)
		जाओ err;

	/* I2C master bus 1,3 घड़ी speed 366k */
	ret = af9035_wr_reg(d, 0x00f103, I2C_SPEED_366K);
	अगर (ret < 0)
		जाओ err;

	/* set gpio11 low */
	ret = af9035_wr_reg_mask(d, 0xd8d4, 0x01, 0x01);
	अगर (ret < 0)
		जाओ err;

	ret = af9035_wr_reg_mask(d, 0xd8d5, 0x01, 0x01);
	अगर (ret < 0)
		जाओ err;

	ret = af9035_wr_reg_mask(d, 0xd8d3, 0x01, 0x01);
	अगर (ret < 0)
		जाओ err;

	/* Tuner enable using gpiot2_en, gpiot2_on and gpiot2_o (reset) */
	ret = af9035_wr_reg_mask(d, 0xd8b8, 0x01, 0x01);
	अगर (ret < 0)
		जाओ err;

	ret = af9035_wr_reg_mask(d, 0xd8b9, 0x01, 0x01);
	अगर (ret < 0)
		जाओ err;

	ret = af9035_wr_reg_mask(d, 0xd8b7, 0x00, 0x01);
	अगर (ret < 0)
		जाओ err;

	msleep(200);

	ret = af9035_wr_reg_mask(d, 0xd8b7, 0x01, 0x01);
	अगर (ret < 0)
		जाओ err;

	स_रखो(&si2168_config, 0, माप(si2168_config));
	si2168_config.i2c_adapter = &adapter;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_SERIAL;

	state->af9033_config[adap->id].fe = &adap->fe[0];
	state->af9033_config[adap->id].ops = &state->ops;
	ret = af9035_add_i2c_dev(d, "si2168",
				 it930x_addresses_table[state->it930x_addresses].frontend_i2c_addr,
				 &si2168_config, &d->i2c_adap);
	अगर (ret)
		जाओ err;

	अगर (adap->fe[0] == शून्य) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	state->i2c_adapter_demod = adapter;

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_frontend_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "adap->id=%d\n", adap->id);

	अगर (adap->id == 1) अणु
		अगर (state->i2c_client[1])
			af9035_del_i2c_dev(d);
	पूर्ण अन्यथा अगर (adap->id == 0) अणु
		अगर (state->i2c_client[0])
			af9035_del_i2c_dev(d);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fc0011_config af9035_fc0011_config = अणु
	.i2c_address = 0x60,
पूर्ण;

अटल काष्ठा mxl5007t_config af9035_mxl5007t_config[] = अणु
	अणु
		.xtal_freq_hz = MxL_XTAL_24_MHZ,
		.अगर_freq_hz = MxL_IF_4_57_MHZ,
		.invert_अगर = 0,
		.loop_thru_enable = 0,
		.clk_out_enable = 0,
		.clk_out_amp = MxL_CLKOUT_AMP_0_94V,
	पूर्ण, अणु
		.xtal_freq_hz = MxL_XTAL_24_MHZ,
		.अगर_freq_hz = MxL_IF_4_57_MHZ,
		.invert_अगर = 0,
		.loop_thru_enable = 1,
		.clk_out_enable = 1,
		.clk_out_amp = MxL_CLKOUT_AMP_0_94V,
	पूर्ण
पूर्ण;

अटल काष्ठा tda18218_config af9035_tda18218_config = अणु
	.i2c_address = 0x60,
	.i2c_wr_max = 21,
पूर्ण;

अटल स्थिर काष्ठा fc0012_config af9035_fc0012_config[] = अणु
	अणु
		.i2c_address = 0x63,
		.xtal_freq = FC_XTAL_36_MHZ,
		.dual_master = true,
		.loop_through = true,
		.घड़ी_out = true,
	पूर्ण, अणु
		.i2c_address = 0x63 | 0x80, /* I2C bus select hack */
		.xtal_freq = FC_XTAL_36_MHZ,
		.dual_master = true,
	पूर्ण
पूर्ण;

अटल पूर्णांक af9035_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	काष्ठा dvb_frontend *fe;
	काष्ठा i2c_msg msg[1];
	u8 tuner_addr;

	dev_dbg(&पूर्णांकf->dev, "adap->id=%d\n", adap->id);

	/*
	 * XXX: Hack used in that function: we abuse unused I2C address bit [7]
	 * to carry info about used I2C bus क्रम dual tuner configuration.
	 */

	चयन (state->af9033_config[adap->id].tuner) अणु
	हाल AF9033_TUNER_TUA9001: अणु
		काष्ठा tua9001_platक्रमm_data tua9001_pdata = अणु
			.dvb_frontend = adap->fe[0],
		पूर्ण;

		/*
		 * AF9035 gpiot3 = TUA9001 RESETN
		 * AF9035 gpiot2 = TUA9001 RXEN
		 */

		/* configure gpiot2 and gpiot2 as output */
		ret = af9035_wr_reg_mask(d, 0x00d8ec, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0x00d8ed, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0x00d8e8, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0x00d8e9, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		/* attach tuner */
		ret = af9035_add_i2c_dev(d, "tua9001", 0x60, &tua9001_pdata,
					 &d->i2c_adap);
		अगर (ret)
			जाओ err;

		fe = adap->fe[0];
		अवरोध;
	पूर्ण
	हाल AF9033_TUNER_FC0011:
		fe = dvb_attach(fc0011_attach, adap->fe[0],
				&d->i2c_adap, &af9035_fc0011_config);
		अवरोध;
	हाल AF9033_TUNER_MXL5007T:
		अगर (adap->id == 0) अणु
			ret = af9035_wr_reg(d, 0x00d8e0, 1);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg(d, 0x00d8e1, 1);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg(d, 0x00d8df, 0);
			अगर (ret < 0)
				जाओ err;

			msleep(30);

			ret = af9035_wr_reg(d, 0x00d8df, 1);
			अगर (ret < 0)
				जाओ err;

			msleep(300);

			ret = af9035_wr_reg(d, 0x00d8c0, 1);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg(d, 0x00d8c1, 1);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg(d, 0x00d8bf, 0);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg(d, 0x00d8b4, 1);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg(d, 0x00d8b5, 1);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg(d, 0x00d8b3, 1);
			अगर (ret < 0)
				जाओ err;

			tuner_addr = 0x60;
		पूर्ण अन्यथा अणु
			tuner_addr = 0x60 | 0x80; /* I2C bus hack */
		पूर्ण

		/* attach tuner */
		fe = dvb_attach(mxl5007t_attach, adap->fe[0], &d->i2c_adap,
				tuner_addr, &af9035_mxl5007t_config[adap->id]);
		अवरोध;
	हाल AF9033_TUNER_TDA18218:
		/* attach tuner */
		fe = dvb_attach(tda18218_attach, adap->fe[0],
				&d->i2c_adap, &af9035_tda18218_config);
		अवरोध;
	हाल AF9033_TUNER_FC2580: अणु
		काष्ठा fc2580_platक्रमm_data fc2580_pdata = अणु
			.dvb_frontend = adap->fe[0],
		पूर्ण;

		/* Tuner enable using gpiot2_o, gpiot2_en and gpiot2_on  */
		ret = af9035_wr_reg_mask(d, 0xd8eb, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0xd8ec, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		ret = af9035_wr_reg_mask(d, 0xd8ed, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err;

		usleep_range(10000, 50000);
		/* attach tuner */
		ret = af9035_add_i2c_dev(d, "fc2580", 0x56, &fc2580_pdata,
					 &d->i2c_adap);
		अगर (ret)
			जाओ err;

		fe = adap->fe[0];
		अवरोध;
	पूर्ण
	हाल AF9033_TUNER_FC0012:
		/*
		 * AF9035 gpiot2 = FC0012 enable
		 * XXX: there seems to be something on gpioh8 too, but on my
		 * my test I didn't find any dअगरference.
		 */

		अगर (adap->id == 0) अणु
			/* configure gpiot2 as output and high */
			ret = af9035_wr_reg_mask(d, 0xd8eb, 0x01, 0x01);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg_mask(d, 0xd8ec, 0x01, 0x01);
			अगर (ret < 0)
				जाओ err;

			ret = af9035_wr_reg_mask(d, 0xd8ed, 0x01, 0x01);
			अगर (ret < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/*
			 * FIXME: That beदीर्घs क्रम the FC0012 driver.
			 * Write 02 to FC0012 master tuner रेजिस्टर 0d directly
			 * in order to make slave tuner working.
			 */
			msg[0].addr = 0x63;
			msg[0].flags = 0;
			msg[0].len = 2;
			msg[0].buf = "\x0d\x02";
			ret = i2c_transfer(&d->i2c_adap, msg, 1);
			अगर (ret < 0)
				जाओ err;
		पूर्ण

		usleep_range(10000, 50000);

		fe = dvb_attach(fc0012_attach, adap->fe[0], &d->i2c_adap,
				&af9035_fc0012_config[adap->id]);
		अवरोध;
	हाल AF9033_TUNER_IT9135_38:
	हाल AF9033_TUNER_IT9135_51:
	हाल AF9033_TUNER_IT9135_52:
	हाल AF9033_TUNER_IT9135_60:
	हाल AF9033_TUNER_IT9135_61:
	हाल AF9033_TUNER_IT9135_62:
	अणु
		काष्ठा platक्रमm_device *pdev;
		स्थिर अक्षर *name;
		काष्ठा it913x_platक्रमm_data it913x_pdata = अणु
			.regmap = state->af9033_config[adap->id].regmap,
			.fe = adap->fe[0],
		पूर्ण;

		चयन (state->af9033_config[adap->id].tuner) अणु
		हाल AF9033_TUNER_IT9135_38:
		हाल AF9033_TUNER_IT9135_51:
		हाल AF9033_TUNER_IT9135_52:
			name = "it9133ax-tuner";
			अवरोध;
		हाल AF9033_TUNER_IT9135_60:
		हाल AF9033_TUNER_IT9135_61:
		हाल AF9033_TUNER_IT9135_62:
			name = "it9133bx-tuner";
			अवरोध;
		शेष:
			ret = -ENODEV;
			जाओ err;
		पूर्ण

		अगर (state->dual_mode) अणु
			अगर (adap->id == 0)
				it913x_pdata.role = IT913X_ROLE_DUAL_MASTER;
			अन्यथा
				it913x_pdata.role = IT913X_ROLE_DUAL_SLAVE;
		पूर्ण अन्यथा अणु
			it913x_pdata.role = IT913X_ROLE_SINGLE;
		पूर्ण

		request_module("%s", "it913x");
		pdev = platक्रमm_device_रेजिस्टर_data(&d->पूर्णांकf->dev, name,
						     PLATFORM_DEVID_AUTO,
						     &it913x_pdata,
						     माप(it913x_pdata));
		अगर (IS_ERR(pdev) || !pdev->dev.driver) अणु
			ret = -ENODEV;
			जाओ err;
		पूर्ण
		अगर (!try_module_get(pdev->dev.driver->owner)) अणु
			platक्रमm_device_unरेजिस्टर(pdev);
			ret = -ENODEV;
			जाओ err;
		पूर्ण

		state->platक्रमm_device_tuner[adap->id] = pdev;
		fe = adap->fe[0];
		अवरोध;
	पूर्ण
	शेष:
		fe = शून्य;
	पूर्ण

	अगर (fe == शून्य) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक it930x_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	काष्ठा si2157_config si2157_config;

	dev_dbg(&पूर्णांकf->dev, "adap->id=%d\n", adap->id);

	स_रखो(&si2157_config, 0, माप(si2157_config));
	si2157_config.fe = adap->fe[0];

	/*
	 * HACK: The Logilink VG0022A and TerraTec TC2 Stick have
	 * a bug: when the si2157 firmware that came with the device
	 * is replaced by a new one, the I2C transfers to the tuner
	 * will वापस just 0xff.
	 *
	 * Probably, the venकरोr firmware has some patch specअगरically
	 * deचिन्हित क्रम this device. So, we can't replace by the
	 * generic firmware. The right solution would be to extract
	 * the si2157 firmware from the original driver and ask the
	 * driver to load the specअगरically deचिन्हित firmware, but,
	 * जबतक we करोn't have that, the next best solution is to just
	 * keep the original firmware at the device.
	 */
	अगर ((le16_to_cpu(d->udev->descriptor.idVenकरोr) == USB_VID_DEXATEK &&
	     le16_to_cpu(d->udev->descriptor.idProduct) == 0x0100) ||
	    (le16_to_cpu(d->udev->descriptor.idVenकरोr) == USB_VID_TERRATEC &&
	     le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_TERRATEC_CINERGY_TC2_STICK))
		si2157_config.करोnt_load_firmware = true;

	si2157_config.अगर_port = it930x_addresses_table[state->it930x_addresses].tuner_अगर_port;
	ret = af9035_add_i2c_dev(d, "si2157",
				 it930x_addresses_table[state->it930x_addresses].tuner_i2c_addr,
				 &si2157_config, state->i2c_adapter_demod);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण


अटल पूर्णांक it930x_tuner_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "adap->id=%d\n", adap->id);

	अगर (adap->id == 1) अणु
		अगर (state->i2c_client[3])
			af9035_del_i2c_dev(d);
	पूर्ण अन्यथा अगर (adap->id == 0) अणु
		अगर (state->i2c_client[1])
			af9035_del_i2c_dev(d);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक af9035_tuner_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "adap->id=%d\n", adap->id);

	चयन (state->af9033_config[adap->id].tuner) अणु
	हाल AF9033_TUNER_TUA9001:
	हाल AF9033_TUNER_FC2580:
		अगर (adap->id == 1) अणु
			अगर (state->i2c_client[3])
				af9035_del_i2c_dev(d);
		पूर्ण अन्यथा अगर (adap->id == 0) अणु
			अगर (state->i2c_client[1])
				af9035_del_i2c_dev(d);
		पूर्ण
		अवरोध;
	हाल AF9033_TUNER_IT9135_38:
	हाल AF9033_TUNER_IT9135_51:
	हाल AF9033_TUNER_IT9135_52:
	हाल AF9033_TUNER_IT9135_60:
	हाल AF9033_TUNER_IT9135_61:
	हाल AF9033_TUNER_IT9135_62:
	अणु
		काष्ठा platक्रमm_device *pdev;

		pdev = state->platक्रमm_device_tuner[adap->id];
		अगर (pdev) अणु
			module_put(pdev->dev.driver->owner);
			platक्रमm_device_unरेजिस्टर(pdev);
		पूर्ण
		अवरोध;
	पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक af9035_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, i;
	u16 frame_size = (d->udev->speed == USB_SPEED_FULL ? 5 : 87) * 188 / 4;
	u8 packet_size = (d->udev->speed == USB_SPEED_FULL ? 64 : 512) / 4;
	काष्ठा reg_val_mask tab[] = अणु
		अणु 0x80f99d, 0x01, 0x01 पूर्ण,
		अणु 0x80f9a4, 0x01, 0x01 पूर्ण,
		अणु 0x00dd11, 0x00, 0x20 पूर्ण,
		अणु 0x00dd11, 0x00, 0x40 पूर्ण,
		अणु 0x00dd13, 0x00, 0x20 पूर्ण,
		अणु 0x00dd13, 0x00, 0x40 पूर्ण,
		अणु 0x00dd11, 0x20, 0x20 पूर्ण,
		अणु 0x00dd88, (frame_size >> 0) & 0xff, 0xffपूर्ण,
		अणु 0x00dd89, (frame_size >> 8) & 0xff, 0xffपूर्ण,
		अणु 0x00dd0c, packet_size, 0xffपूर्ण,
		अणु 0x00dd11, state->dual_mode << 6, 0x40 पूर्ण,
		अणु 0x00dd8a, (frame_size >> 0) & 0xff, 0xffपूर्ण,
		अणु 0x00dd8b, (frame_size >> 8) & 0xff, 0xffपूर्ण,
		अणु 0x00dd0d, packet_size, 0xff पूर्ण,
		अणु 0x80f9a3, state->dual_mode, 0x01 पूर्ण,
		अणु 0x80f9cd, state->dual_mode, 0x01 पूर्ण,
		अणु 0x80f99d, 0x00, 0x01 पूर्ण,
		अणु 0x80f9a4, 0x00, 0x01 पूर्ण,
	पूर्ण;

	dev_dbg(&पूर्णांकf->dev, "USB speed=%d frame_size=%04x packet_size=%02x\n",
		d->udev->speed, frame_size, packet_size);

	/* init endpoपूर्णांकs */
	क्रम (i = 0; i < ARRAY_SIZE(tab); i++) अणु
		ret = af9035_wr_reg_mask(d, tab[i].reg, tab[i].val,
				tab[i].mask);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक it930x_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, i;
	u16 frame_size = (d->udev->speed == USB_SPEED_FULL ? 5 : 816) * 188 / 4;
	u8 packet_size = (d->udev->speed == USB_SPEED_FULL ? 64 : 512) / 4;
	काष्ठा reg_val_mask tab[] = अणु
		अणु 0x00da1a, 0x00, 0x01 पूर्ण, /* ignore_sync_byte */
		अणु 0x00f41f, 0x04, 0x04 पूर्ण, /* dvbt_पूर्णांकen */
		अणु 0x00da10, 0x00, 0x01 पूर्ण, /* mpeg_full_speed */
		अणु 0x00f41a, 0x01, 0x01 पूर्ण, /* dvbt_en */
		अणु 0x00da1d, 0x01, 0x01 पूर्ण, /* mp2_sw_rst, reset EP4 */
		अणु 0x00dd11, 0x00, 0x20 पूर्ण, /* ep4_tx_en, disable EP4 */
		अणु 0x00dd13, 0x00, 0x20 पूर्ण, /* ep4_tx_nak, disable EP4 NAK */
		अणु 0x00dd11, 0x20, 0x20 पूर्ण, /* ep4_tx_en, enable EP4 */
		अणु 0x00dd11, 0x00, 0x40 पूर्ण, /* ep5_tx_en, disable EP5 */
		अणु 0x00dd13, 0x00, 0x40 पूर्ण, /* ep5_tx_nak, disable EP5 NAK */
		अणु 0x00dd11, state->dual_mode << 6, 0x40 पूर्ण, /* enable EP5 */
		अणु 0x00dd88, (frame_size >> 0) & 0xff, 0xffपूर्ण,
		अणु 0x00dd89, (frame_size >> 8) & 0xff, 0xffपूर्ण,
		अणु 0x00dd0c, packet_size, 0xffपूर्ण,
		अणु 0x00dd8a, (frame_size >> 0) & 0xff, 0xffपूर्ण,
		अणु 0x00dd8b, (frame_size >> 8) & 0xff, 0xffपूर्ण,
		अणु 0x00dd0d, packet_size, 0xff पूर्ण,
		अणु 0x00da1d, 0x00, 0x01 पूर्ण, /* mp2_sw_rst, disable */
		अणु 0x00d833, 0x01, 0xff पूर्ण, /* slew rate ctrl: slew rate boosts */
		अणु 0x00d830, 0x00, 0xff पूर्ण, /* Bit 0 of output driving control */
		अणु 0x00d831, 0x01, 0xff पूर्ण, /* Bit 1 of output driving control */
		अणु 0x00d832, 0x00, 0xff पूर्ण, /* Bit 2 of output driving control */

		/* suspend gpio1 क्रम TS-C */
		अणु 0x00d8b0, 0x01, 0xff पूर्ण, /* gpio1 */
		अणु 0x00d8b1, 0x01, 0xff पूर्ण, /* gpio1 */
		अणु 0x00d8af, 0x00, 0xff पूर्ण, /* gpio1 */

		/* suspend gpio7 क्रम TS-D */
		अणु 0x00d8c4, 0x01, 0xff पूर्ण, /* gpio7 */
		अणु 0x00d8c5, 0x01, 0xff पूर्ण, /* gpio7 */
		अणु 0x00d8c3, 0x00, 0xff पूर्ण, /* gpio7 */

		/* suspend gpio13 क्रम TS-B */
		अणु 0x00d8dc, 0x01, 0xff पूर्ण, /* gpio13 */
		अणु 0x00d8dd, 0x01, 0xff पूर्ण, /* gpio13 */
		अणु 0x00d8db, 0x00, 0xff पूर्ण, /* gpio13 */

		/* suspend gpio14 क्रम TS-E */
		अणु 0x00d8e4, 0x01, 0xff पूर्ण, /* gpio14 */
		अणु 0x00d8e5, 0x01, 0xff पूर्ण, /* gpio14 */
		अणु 0x00d8e3, 0x00, 0xff पूर्ण, /* gpio14 */

		/* suspend gpio15 क्रम TS-A */
		अणु 0x00d8e8, 0x01, 0xff पूर्ण, /* gpio15 */
		अणु 0x00d8e9, 0x01, 0xff पूर्ण, /* gpio15 */
		अणु 0x00d8e7, 0x00, 0xff पूर्ण, /* gpio15 */

		अणु 0x00da58, 0x00, 0x01 पूर्ण, /* ts_in_src, serial */
		अणु 0x00da73, 0x01, 0xff पूर्ण, /* ts0_aggre_mode */
		अणु 0x00da78, 0x47, 0xff पूर्ण, /* ts0_sync_byte */
		अणु 0x00da4c, 0x01, 0xff पूर्ण, /* ts0_en */
		अणु 0x00da5a, 0x1f, 0xff पूर्ण, /* ts_fail_ignore */
	पूर्ण;

	dev_dbg(&पूर्णांकf->dev, "USB speed=%d frame_size=%04x packet_size=%02x\n",
		d->udev->speed, frame_size, packet_size);

	/* init endpoपूर्णांकs */
	क्रम (i = 0; i < ARRAY_SIZE(tab); i++) अणु
		ret = af9035_wr_reg_mask(d, tab[i].reg,
				tab[i].val, tab[i].mask);

		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण


#अगर IS_ENABLED(CONFIG_RC_CORE)
अटल पूर्णांक af9035_rc_query(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	क्रमागत rc_proto proto;
	u32 key;
	u8 buf[4];
	काष्ठा usb_req req = अणु CMD_IR_GET, 0, 0, शून्य, 4, buf पूर्ण;

	ret = af9035_ctrl_msg(d, &req);
	अगर (ret == 1)
		वापस 0;
	अन्यथा अगर (ret < 0)
		जाओ err;

	अगर ((buf[2] + buf[3]) == 0xff) अणु
		अगर ((buf[0] + buf[1]) == 0xff) अणु
			/* NEC standard 16bit */
			key = RC_SCANCODE_NEC(buf[0], buf[2]);
			proto = RC_PROTO_NEC;
		पूर्ण अन्यथा अणु
			/* NEC extended 24bit */
			key = RC_SCANCODE_NECX(buf[0] << 8 | buf[1], buf[2]);
			proto = RC_PROTO_NECX;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* NEC full code 32bit */
		key = RC_SCANCODE_NEC32(buf[0] << 24 | buf[1] << 16 |
					buf[2] << 8  | buf[3]);
		proto = RC_PROTO_NEC32;
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "%*ph\n", 4, buf);

	rc_keyकरोwn(d->rc_dev, proto, key, 0);

	वापस 0;

err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक af9035_get_rc_config(काष्ठा dvb_usb_device *d, काष्ठा dvb_usb_rc *rc)
अणु
	काष्ठा state *state = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "ir_mode=%02x ir_type=%02x\n",
		state->ir_mode, state->ir_type);

	/* करोn't activate rc अगर in HID mode or अगर not available */
	अगर (state->ir_mode == 0x05) अणु
		चयन (state->ir_type) अणु
		हाल 0: /* NEC */
		शेष:
			rc->allowed_protos = RC_PROTO_BIT_NEC |
					RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32;
			अवरोध;
		हाल 1: /* RC6 */
			rc->allowed_protos = RC_PROTO_BIT_RC6_MCE;
			अवरोध;
		पूर्ण

		rc->query = af9035_rc_query;
		rc->पूर्णांकerval = 500;

		/* load empty to enable rc */
		अगर (!rc->map_name)
			rc->map_name = RC_MAP_EMPTY;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
	#घोषणा af9035_get_rc_config शून्य
#पूर्ण_अगर

अटल पूर्णांक af9035_get_stream_config(काष्ठा dvb_frontend *fe, u8 *ts_type,
		काष्ठा usb_data_stream_properties *stream)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "adap=%d\n", fe_to_adap(fe)->id);

	अगर (d->udev->speed == USB_SPEED_FULL)
		stream->u.bulk.buffersize = 5 * 188;

	वापस 0;
पूर्ण

अटल पूर्णांक af9035_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा state *state = adap_to_priv(adap);

	वापस state->ops.pid_filter_ctrl(adap->fe[0], onoff);
पूर्ण

अटल पूर्णांक af9035_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index, u16 pid,
		पूर्णांक onoff)
अणु
	काष्ठा state *state = adap_to_priv(adap);

	वापस state->ops.pid_filter(adap->fe[0], index, pid, onoff);
पूर्ण

अटल पूर्णांक af9035_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	अक्षर manufacturer[माप("Afatech")];

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
		अगर (!म_भेद("Afatech", manufacturer)) अणु
			dev_dbg(&udev->dev, "rejecting device\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस dvb_usbv2_probe(पूर्णांकf, id);
पूर्ण

/* पूर्णांकerface 0 is used by DVB-T receiver and
   पूर्णांकerface 1 is क्रम remote controller (HID) */
अटल स्थिर काष्ठा dvb_usb_device_properties af9035_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.identअगरy_state = af9035_identअगरy_state,
	.करोwnload_firmware = af9035_करोwnload_firmware,

	.i2c_algo = &af9035_i2c_algo,
	.पढ़ो_config = af9035_पढ़ो_config,
	.frontend_attach = af9035_frontend_attach,
	.frontend_detach = af9035_frontend_detach,
	.tuner_attach = af9035_tuner_attach,
	.tuner_detach = af9035_tuner_detach,
	.init = af9035_init,
	.get_rc_config = af9035_get_rc_config,
	.get_stream_config = af9035_get_stream_config,

	.get_adapter_count = af9035_get_adapter_count,
	.adapter = अणु
		अणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER |
				DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

			.pid_filter_count = 32,
			.pid_filter_ctrl = af9035_pid_filter_ctrl,
			.pid_filter = af9035_pid_filter,

			.stream = DVB_USB_STREAM_BULK(0x84, 6, 87 * 188),
		पूर्ण, अणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER |
				DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

			.pid_filter_count = 32,
			.pid_filter_ctrl = af9035_pid_filter_ctrl,
			.pid_filter = af9035_pid_filter,

			.stream = DVB_USB_STREAM_BULK(0x85, 6, 87 * 188),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_properties it930x_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x02,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.identअगरy_state = af9035_identअगरy_state,
	.करोwnload_firmware = af9035_करोwnload_firmware,

	.i2c_algo = &af9035_i2c_algo,
	.पढ़ो_config = af9035_पढ़ो_config,
	.frontend_attach = it930x_frontend_attach,
	.frontend_detach = af9035_frontend_detach,
	.tuner_attach = it930x_tuner_attach,
	.tuner_detach = it930x_tuner_detach,
	.init = it930x_init,
	.get_stream_config = af9035_get_stream_config,

	.get_adapter_count = af9035_get_adapter_count,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x84, 4, 816 * 188),
		पूर्ण, अणु
			.stream = DVB_USB_STREAM_BULK(0x85, 4, 816 * 188),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id af9035_id_table[] = अणु
	/* AF9035 devices */
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_9035,
		&af9035_props, "Afatech AF9035 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1000,
		&af9035_props, "Afatech AF9035 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1001,
		&af9035_props, "Afatech AF9035 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1002,
		&af9035_props, "Afatech AF9035 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1003,
		&af9035_props, "Afatech AF9035 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_T_STICK,
		&af9035_props, "TerraTec Cinergy T Stick", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A835,
		&af9035_props, "AVerMedia AVerTV Volar HD/PRO (A835)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_B835,
		&af9035_props, "AVerMedia AVerTV Volar HD/PRO (A835)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_1867,
		&af9035_props, "AVerMedia HD Volar (A867)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A867,
		&af9035_props, "AVerMedia HD Volar (A867)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_TWINSTAR,
		&af9035_props, "AVerMedia Twinstar (A825)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_ASUS, USB_PID_ASUS_U3100MINI_PLUS,
		&af9035_props, "Asus U3100Mini Plus", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, 0x00aa,
		&af9035_props, "TerraTec Cinergy T Stick (rev. 2)", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, 0x0337,
		&af9035_props, "AVerMedia HD Volar (A867)", शून्य) पूर्ण,
       अणु DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_EVOLVEO_XTRATV_STICK,
	       &af9035_props, "EVOLVEO XtraTV stick", शून्य) पूर्ण,

	/* IT9135 devices */
	अणु DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9135,
		&af9035_props, "ITE 9135 Generic", RC_MAP_IT913X_V1) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9135_9005,
		&af9035_props, "ITE 9135(9005) Generic", RC_MAP_IT913X_V2) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9135_9006,
		&af9035_props, "ITE 9135(9006) Generic", RC_MAP_IT913X_V1) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A835B_1835,
		&af9035_props, "Avermedia A835B(1835)", RC_MAP_IT913X_V2) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A835B_2835,
		&af9035_props, "Avermedia A835B(2835)", RC_MAP_IT913X_V2) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A835B_3835,
		&af9035_props, "Avermedia A835B(3835)", RC_MAP_IT913X_V2) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A835B_4835,
		&af9035_props, "Avermedia A835B(4835)",	RC_MAP_IT913X_V2) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_TD110,
		&af9035_props, "Avermedia AverTV Volar HD 2 (TD110)", RC_MAP_AVERMEDIA_RM_KS) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_H335,
		&af9035_props, "Avermedia H335", RC_MAP_IT913X_V2) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_KWORLD_UB499_2T_T09,
		&af9035_props, "Kworld UB499-2T T09", RC_MAP_IT913X_V1) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_SVEON_STV22_IT9137,
		&af9035_props, "Sveon STV22 Dual DVB-T HDTV",
							RC_MAP_IT913X_V1) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_KWORLD_2, USB_PID_CTVDIGDUAL_V2,
		&af9035_props, "Digital Dual TV Receiver CTVDIGDUAL_V2",
							RC_MAP_IT913X_V1) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_T1,
		&af9035_props, "TerraTec T1", RC_MAP_IT913X_V1) पूर्ण,
	/* XXX: that same ID [0ccd:0099] is used by af9015 driver too */
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, 0x0099,
		&af9035_props, "TerraTec Cinergy T Stick Dual RC (rev. 2)",
		शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_LEADTEK, 0x6a05,
		&af9035_props, "Leadtek WinFast DTV Dongle Dual", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xf900,
		&af9035_props, "Hauppauge WinTV-MiniStick 2", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_PCTV, USB_PID_PCTV_78E,
		&af9035_props, "PCTV AndroiDTV (78e)", RC_MAP_IT913X_V1) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_PCTV, USB_PID_PCTV_79E,
		&af9035_props, "PCTV microStick (79e)", RC_MAP_IT913X_V2) पूर्ण,

	/* IT930x devices */
	अणु DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9303,
		&it930x_props, "ITE 9303 Generic", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_TD310,
		&it930x_props, "AVerMedia TD310 DVB-T2", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_DEXATEK, 0x0100,
		&it930x_props, "Logilink VG0022A", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_TC2_STICK,
		&it930x_props, "TerraTec Cinergy TC2 Stick", शून्य) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, af9035_id_table);

अटल काष्ठा usb_driver af9035_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = af9035_id_table,
	.probe = af9035_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(af9035_usb_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Afatech AF9035 driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(AF9035_FIRMWARE_AF9035);
MODULE_FIRMWARE(AF9035_FIRMWARE_IT9135_V1);
MODULE_FIRMWARE(AF9035_FIRMWARE_IT9135_V2);
MODULE_FIRMWARE(AF9035_FIRMWARE_IT9303);
