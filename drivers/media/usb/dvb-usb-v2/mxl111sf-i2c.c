<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  mxl111sf-i2c.c - driver क्रम the MaxLinear MXL111SF
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश "mxl111sf-i2c.h"
#समावेश "mxl111sf.h"

/* SW-I2C ----------------------------------------------------------------- */

#घोषणा SW_I2C_ADDR		0x1a
#घोषणा SW_I2C_EN		0x02
#घोषणा SW_SCL_OUT		0x04
#घोषणा SW_SDA_OUT		0x08
#घोषणा SW_SDA_IN		0x04

#घोषणा SW_I2C_BUSY_ADDR	0x2f
#घोषणा SW_I2C_BUSY		0x02

अटल पूर्णांक mxl111sf_i2c_bitbang_sendbyte(काष्ठा mxl111sf_state *state,
					 u8 byte)
अणु
	पूर्णांक i, ret;
	u8 data = 0;

	mxl_i2c("(0x%02x)", byte);

	ret = mxl111sf_पढ़ो_reg(state, SW_I2C_BUSY_ADDR, &data);
	अगर (mxl_fail(ret))
		जाओ fail;

	क्रम (i = 0; i < 8; i++) अणु

		data = (byte & (0x80 >> i)) ? SW_SDA_OUT : 0;

		ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
					 0x10 | SW_I2C_EN | data);
		अगर (mxl_fail(ret))
			जाओ fail;

		ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
					 0x10 | SW_I2C_EN | data | SW_SCL_OUT);
		अगर (mxl_fail(ret))
			जाओ fail;

		ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
					 0x10 | SW_I2C_EN | data);
		अगर (mxl_fail(ret))
			जाओ fail;
	पूर्ण

	/* last bit was 0 so we need to release SDA */
	अगर (!(byte & 1)) अणु
		ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
					 0x10 | SW_I2C_EN | SW_SDA_OUT);
		अगर (mxl_fail(ret))
			जाओ fail;
	पूर्ण

	/* CLK high क्रम ACK पढ़ोback */
	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SCL_OUT | SW_SDA_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_पढ़ो_reg(state, SW_I2C_BUSY_ADDR, &data);
	अगर (mxl_fail(ret))
		जाओ fail;

	/* drop the CLK after getting ACK, SDA will go high right away */
	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	अगर (data & SW_SDA_IN)
		ret = -EIO;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_i2c_bitbang_recvbyte(काष्ठा mxl111sf_state *state,
					 u8 *pbyte)
अणु
	पूर्णांक i, ret;
	u8 byte = 0;
	u8 data = 0;

	mxl_i2c("()");

	*pbyte = 0;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	क्रम (i = 0; i < 8; i++) अणु
		ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
					 0x10 | SW_I2C_EN |
					 SW_SCL_OUT | SW_SDA_OUT);
		अगर (mxl_fail(ret))
			जाओ fail;

		ret = mxl111sf_पढ़ो_reg(state, SW_I2C_BUSY_ADDR, &data);
		अगर (mxl_fail(ret))
			जाओ fail;

		अगर (data & SW_SDA_IN)
			byte |= (0x80 >> i);

		ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
					 0x10 | SW_I2C_EN | SW_SDA_OUT);
		अगर (mxl_fail(ret))
			जाओ fail;
	पूर्ण
	*pbyte = byte;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_i2c_start(काष्ठा mxl111sf_state *state)
अणु
	पूर्णांक ret;

	mxl_i2c("()");

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SCL_OUT | SW_SDA_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SCL_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN); /* start */
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_i2c_stop(काष्ठा mxl111sf_state *state)
अणु
	पूर्णांक ret;

	mxl_i2c("()");

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN); /* stop */
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SCL_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SCL_OUT | SW_SDA_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_SCL_OUT | SW_SDA_OUT);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_i2c_ack(काष्ठा mxl111sf_state *state)
अणु
	पूर्णांक ret;
	u8 b = 0;

	mxl_i2c("()");

	ret = mxl111sf_पढ़ो_reg(state, SW_I2C_BUSY_ADDR, &b);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN);
	अगर (mxl_fail(ret))
		जाओ fail;

	/* pull SDA low */
	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SCL_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_i2c_nack(काष्ठा mxl111sf_state *state)
अणु
	पूर्णांक ret;

	mxl_i2c("()");

	/* SDA high to संकेत last byte पढ़ो from slave */
	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SCL_OUT | SW_SDA_OUT);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, SW_I2C_ADDR,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक mxl111sf_i2c_sw_xfer_msg(काष्ठा mxl111sf_state *state,
				    काष्ठा i2c_msg *msg)
अणु
	पूर्णांक i, ret;

	mxl_i2c("()");

	अगर (msg->flags & I2C_M_RD) अणु

		ret = mxl111sf_i2c_start(state);
		अगर (mxl_fail(ret))
			जाओ fail;

		ret = mxl111sf_i2c_bitbang_sendbyte(state,
						    (msg->addr << 1) | 0x01);
		अगर (mxl_fail(ret)) अणु
			mxl111sf_i2c_stop(state);
			जाओ fail;
		पूर्ण

		क्रम (i = 0; i < msg->len; i++) अणु
			ret = mxl111sf_i2c_bitbang_recvbyte(state,
							    &msg->buf[i]);
			अगर (mxl_fail(ret)) अणु
				mxl111sf_i2c_stop(state);
				जाओ fail;
			पूर्ण

			अगर (i < msg->len - 1)
				mxl111sf_i2c_ack(state);
		पूर्ण

		mxl111sf_i2c_nack(state);

		ret = mxl111sf_i2c_stop(state);
		अगर (mxl_fail(ret))
			जाओ fail;

	पूर्ण अन्यथा अणु

		ret = mxl111sf_i2c_start(state);
		अगर (mxl_fail(ret))
			जाओ fail;

		ret = mxl111sf_i2c_bitbang_sendbyte(state,
						    (msg->addr << 1) & 0xfe);
		अगर (mxl_fail(ret)) अणु
			mxl111sf_i2c_stop(state);
			जाओ fail;
		पूर्ण

		क्रम (i = 0; i < msg->len; i++) अणु
			ret = mxl111sf_i2c_bitbang_sendbyte(state,
							    msg->buf[i]);
			अगर (mxl_fail(ret)) अणु
				mxl111sf_i2c_stop(state);
				जाओ fail;
			पूर्ण
		पूर्ण

		/* FIXME: we only want to करो this on the last transaction */
		mxl111sf_i2c_stop(state);
	पूर्ण
fail:
	वापस ret;
पूर्ण

/* HW-I2C ----------------------------------------------------------------- */

#घोषणा USB_WRITE_I2C_CMD     0x99
#घोषणा USB_READ_I2C_CMD      0xdd
#घोषणा USB_END_I2C_CMD       0xfe

#घोषणा USB_WRITE_I2C_CMD_LEN   26
#घोषणा USB_READ_I2C_CMD_LEN    24

#घोषणा I2C_MUX_REG           0x30
#घोषणा I2C_CONTROL_REG       0x00
#घोषणा I2C_SLAVE_ADDR_REG    0x08
#घोषणा I2C_DATA_REG          0x0c
#घोषणा I2C_INT_STATUS_REG    0x10

अटल पूर्णांक mxl111sf_i2c_send_data(काष्ठा mxl111sf_state *state,
				  u8 index, u8 *wdata)
अणु
	पूर्णांक ret = mxl111sf_ctrl_msg(state, wdata[0],
				    &wdata[1], 25, शून्य, 0);
	mxl_fail(ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_i2c_get_data(काष्ठा mxl111sf_state *state,
				 u8 index, u8 *wdata, u8 *rdata)
अणु
	पूर्णांक ret = mxl111sf_ctrl_msg(state, wdata[0],
				    &wdata[1], 25, rdata, 24);
	mxl_fail(ret);

	वापस ret;
पूर्ण

अटल u8 mxl111sf_i2c_check_status(काष्ठा mxl111sf_state *state)
अणु
	u8 status = 0;
	u8 buf[26];

	mxl_i2c_adv("()");

	buf[0] = USB_READ_I2C_CMD;
	buf[1] = 0x00;

	buf[2] = I2C_INT_STATUS_REG;
	buf[3] = 0x00;
	buf[4] = 0x00;

	buf[5] = USB_END_I2C_CMD;

	mxl111sf_i2c_get_data(state, 0, buf, buf);

	अगर (buf[1] & 0x04)
		status = 1;

	वापस status;
पूर्ण

अटल u8 mxl111sf_i2c_check_fअगरo(काष्ठा mxl111sf_state *state)
अणु
	u8 status = 0;
	u8 buf[26];

	mxl_i2c("()");

	buf[0] = USB_READ_I2C_CMD;
	buf[1] = 0x00;

	buf[2] = I2C_MUX_REG;
	buf[3] = 0x00;
	buf[4] = 0x00;

	buf[5] = I2C_INT_STATUS_REG;
	buf[6] = 0x00;
	buf[7] = 0x00;
	buf[8] = USB_END_I2C_CMD;

	mxl111sf_i2c_get_data(state, 0, buf, buf);

	अगर (0x08 == (buf[1] & 0x08))
		status = 1;

	अगर ((buf[5] & 0x02) == 0x02)
		mxl_i2c("(buf[5] & 0x02) == 0x02"); /* FIXME */

	वापस status;
पूर्ण

अटल पूर्णांक mxl111sf_i2c_पढ़ोagain(काष्ठा mxl111sf_state *state,
				  u8 count, u8 *rbuf)
अणु
	u8 i2c_w_data[26];
	u8 i2c_r_data[24];
	u8 i = 0;
	u8 fअगरo_status = 0;
	पूर्णांक status = 0;

	mxl_i2c("read %d bytes", count);

	जबतक ((fअगरo_status == 0) && (i++ < 5))
		fअगरo_status = mxl111sf_i2c_check_fअगरo(state);

	i2c_w_data[0] = 0xDD;
	i2c_w_data[1] = 0x00;

	क्रम (i = 2; i < 26; i++)
		i2c_w_data[i] = 0xFE;

	क्रम (i = 0; i < count; i++) अणु
		i2c_w_data[2+(i*3)] = 0x0C;
		i2c_w_data[3+(i*3)] = 0x00;
		i2c_w_data[4+(i*3)] = 0x00;
	पूर्ण

	mxl111sf_i2c_get_data(state, 0, i2c_w_data, i2c_r_data);

	/* Check क्रम I2C NACK status */
	अगर (mxl111sf_i2c_check_status(state) == 1) अणु
		mxl_i2c("error!");
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < count; i++) अणु
			rbuf[i] = i2c_r_data[(i*3)+1];
			mxl_i2c("%02x\t %02x",
				i2c_r_data[(i*3)+1],
				i2c_r_data[(i*3)+2]);
		पूर्ण

		status = 1;
	पूर्ण

	वापस status;
पूर्ण

#घोषणा HWI2C400 1
अटल पूर्णांक mxl111sf_i2c_hw_xfer_msg(काष्ठा mxl111sf_state *state,
				    काष्ठा i2c_msg *msg)
अणु
	पूर्णांक i, k, ret = 0;
	u16 index = 0;
	u8 buf[26];
	u8 i2c_r_data[24];
	u16 block_len;
	u16 left_over_len;
	u8 rd_status[8];
	u8 ret_status;
	u8 पढ़ोbuff[26];

	mxl_i2c("addr: 0x%02x, read buff len: %d, write buff len: %d",
		msg->addr, (msg->flags & I2C_M_RD) ? msg->len : 0,
		(!(msg->flags & I2C_M_RD)) ? msg->len : 0);

	क्रम (index = 0; index < 26; index++)
		buf[index] = USB_END_I2C_CMD;

	/* command to indicate data payload is destined क्रम I2C पूर्णांकerface */
	buf[0] = USB_WRITE_I2C_CMD;
	buf[1] = 0x00;

	/* enable I2C पूर्णांकerface */
	buf[2] = I2C_MUX_REG;
	buf[3] = 0x80;
	buf[4] = 0x00;

	/* enable I2C पूर्णांकerface */
	buf[5] = I2C_MUX_REG;
	buf[6] = 0x81;
	buf[7] = 0x00;

	/* set Timeout रेजिस्टर on I2C पूर्णांकerface */
	buf[8] = 0x14;
	buf[9] = 0xff;
	buf[10] = 0x00;
#अगर 0
	/* enable Interrupts on I2C पूर्णांकerface */
	buf[8] = 0x24;
	buf[9] = 0xF7;
	buf[10] = 0x00;
#पूर्ण_अगर
	buf[11] = 0x24;
	buf[12] = 0xF7;
	buf[13] = 0x00;

	ret = mxl111sf_i2c_send_data(state, 0, buf);

	/* ग_लिखो data on I2C bus */
	अगर (!(msg->flags & I2C_M_RD) && (msg->len > 0)) अणु
		mxl_i2c("%d\t%02x", msg->len, msg->buf[0]);

		/* control रेजिस्टर on I2C पूर्णांकerface to initialize I2C bus */
		buf[2] = I2C_CONTROL_REG;
		buf[3] = 0x5E;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

		/* I2C Slave device Address */
		buf[5] = I2C_SLAVE_ADDR_REG;
		buf[6] = (msg->addr);
		buf[7] = 0x00;
		buf[8] = USB_END_I2C_CMD;
		ret = mxl111sf_i2c_send_data(state, 0, buf);

		/* check क्रम slave device status */
		अगर (mxl111sf_i2c_check_status(state) == 1) अणु
			mxl_i2c("NACK writing slave address %02x",
				msg->addr);
			/* अगर NACK, stop I2C bus and निकास */
			buf[2] = I2C_CONTROL_REG;
			buf[3] = 0x4E;
			buf[4] = (HWI2C400) ? 0x03 : 0x0D;
			ret = -EIO;
			जाओ निकास;
		पूर्ण

		/* I2C पूर्णांकerface can करो I2C operations in block of 8 bytes of
		   I2C data. calculation to figure out number of blocks of i2c
		   data required to program */
		block_len = (msg->len / 8);
		left_over_len = (msg->len % 8);

		mxl_i2c("block_len %d, left_over_len %d",
			block_len, left_over_len);

		क्रम (index = 0; index < block_len; index++) अणु
			क्रम (i = 0; i < 8; i++) अणु
				/* ग_लिखो data on I2C पूर्णांकerface */
				buf[2+(i*3)] = I2C_DATA_REG;
				buf[3+(i*3)] = msg->buf[(index*8)+i];
				buf[4+(i*3)] = 0x00;
			पूर्ण

			ret = mxl111sf_i2c_send_data(state, 0, buf);

			/* check क्रम I2C NACK status */
			अगर (mxl111sf_i2c_check_status(state) == 1) अणु
				mxl_i2c("NACK writing slave address %02x",
					msg->addr);

				/* अगर NACK, stop I2C bus and निकास */
				buf[2] = I2C_CONTROL_REG;
				buf[3] = 0x4E;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				ret = -EIO;
				जाओ निकास;
			पूर्ण

		पूर्ण

		अगर (left_over_len) अणु
			क्रम (k = 0; k < 26; k++)
				buf[k] = USB_END_I2C_CMD;

			buf[0] = 0x99;
			buf[1] = 0x00;

			क्रम (i = 0; i < left_over_len; i++) अणु
				buf[2+(i*3)] = I2C_DATA_REG;
				buf[3+(i*3)] = msg->buf[(index*8)+i];
				mxl_i2c("index = %d %d data %d",
					index, i, msg->buf[(index*8)+i]);
				buf[4+(i*3)] = 0x00;
			पूर्ण
			ret = mxl111sf_i2c_send_data(state, 0, buf);

			/* check क्रम I2C NACK status */
			अगर (mxl111sf_i2c_check_status(state) == 1) अणु
				mxl_i2c("NACK writing slave address %02x",
					msg->addr);

				/* अगर NACK, stop I2C bus and निकास */
				buf[2] = I2C_CONTROL_REG;
				buf[3] = 0x4E;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				ret = -EIO;
				जाओ निकास;
			पूर्ण

		पूर्ण

		/* issue I2C STOP after ग_लिखो */
		buf[2] = I2C_CONTROL_REG;
		buf[3] = 0x4E;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

	पूर्ण

	/* पढ़ो data from I2C bus */
	अगर ((msg->flags & I2C_M_RD) && (msg->len > 0)) अणु
		mxl_i2c("read buf len %d", msg->len);

		/* command to indicate data payload is
		   destined क्रम I2C पूर्णांकerface */
		buf[2] = I2C_CONTROL_REG;
		buf[3] = 0xDF;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

		/* I2C xfer length */
		buf[5] = 0x14;
		buf[6] = (msg->len & 0xFF);
		buf[7] = 0;

		/* I2C slave device Address */
		buf[8] = I2C_SLAVE_ADDR_REG;
		buf[9] = msg->addr;
		buf[10] = 0x00;
		buf[11] = USB_END_I2C_CMD;
		ret = mxl111sf_i2c_send_data(state, 0, buf);

		/* check क्रम I2C NACK status */
		अगर (mxl111sf_i2c_check_status(state) == 1) अणु
			mxl_i2c("NACK reading slave address %02x",
				msg->addr);

			/* अगर NACK, stop I2C bus and निकास */
			buf[2] = I2C_CONTROL_REG;
			buf[3] = 0xC7;
			buf[4] = (HWI2C400) ? 0x03 : 0x0D;
			ret = -EIO;
			जाओ निकास;
		पूर्ण

		/* I2C पूर्णांकerface can करो I2C operations in block of 8 bytes of
		   I2C data. calculation to figure out number of blocks of
		   i2c data required to program */
		block_len = ((msg->len) / 8);
		left_over_len = ((msg->len) % 8);
		index = 0;

		mxl_i2c("block_len %d, left_over_len %d",
			block_len, left_over_len);

		/* command to पढ़ो data from I2C पूर्णांकerface */
		buf[0] = USB_READ_I2C_CMD;
		buf[1] = 0x00;

		क्रम (index = 0; index < block_len; index++) अणु
			/* setup I2C पढ़ो request packet on I2C पूर्णांकerface */
			क्रम (i = 0; i < 8; i++) अणु
				buf[2+(i*3)] = I2C_DATA_REG;
				buf[3+(i*3)] = 0x00;
				buf[4+(i*3)] = 0x00;
			पूर्ण

			ret = mxl111sf_i2c_get_data(state, 0, buf, i2c_r_data);

			/* check क्रम I2C NACK status */
			अगर (mxl111sf_i2c_check_status(state) == 1) अणु
				mxl_i2c("NACK reading slave address %02x",
					msg->addr);

				/* अगर NACK, stop I2C bus and निकास */
				buf[2] = I2C_CONTROL_REG;
				buf[3] = 0xC7;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				ret = -EIO;
				जाओ निकास;
			पूर्ण

			/* copy data from i2c data payload to पढ़ो buffer */
			क्रम (i = 0; i < 8; i++) अणु
				rd_status[i] = i2c_r_data[(i*3)+2];

				अगर (rd_status[i] == 0x04) अणु
					अगर (i < 7) अणु
						mxl_i2c("i2c fifo empty! @ %d",
							i);
						msg->buf[(index*8)+i] =
							i2c_r_data[(i*3)+1];
						/* पढ़ो again */
						ret_status =
							mxl111sf_i2c_पढ़ोagain(
								state, 8-(i+1),
								पढ़ोbuff);
						अगर (ret_status == 1) अणु
							क्रम (k = 0;
							     k < 8-(i+1);
							     k++) अणु

					msg->buf[(index*8)+(k+i+1)] =
						पढ़ोbuff[k];
					mxl_i2c("read data: %02x\t %02x",
						msg->buf[(index*8)+(k+i)],
						(index*8)+(k+i));
					mxl_i2c("read data: %02x\t %02x",
						msg->buf[(index*8)+(k+i+1)],
						पढ़ोbuff[k]);

							पूर्ण
							जाओ stop_copy;
						पूर्ण अन्यथा अणु
							mxl_i2c("readagain ERROR!");
						पूर्ण
					पूर्ण अन्यथा अणु
						msg->buf[(index*8)+i] =
							i2c_r_data[(i*3)+1];
					पूर्ण
				पूर्ण अन्यथा अणु
					msg->buf[(index*8)+i] =
						i2c_r_data[(i*3)+1];
				पूर्ण
			पूर्ण
stop_copy:
			;

		पूर्ण

		अगर (left_over_len) अणु
			क्रम (k = 0; k < 26; k++)
				buf[k] = USB_END_I2C_CMD;

			buf[0] = 0xDD;
			buf[1] = 0x00;

			क्रम (i = 0; i < left_over_len; i++) अणु
				buf[2+(i*3)] = I2C_DATA_REG;
				buf[3+(i*3)] = 0x00;
				buf[4+(i*3)] = 0x00;
			पूर्ण
			ret = mxl111sf_i2c_get_data(state, 0, buf,
						    i2c_r_data);

			/* check क्रम I2C NACK status */
			अगर (mxl111sf_i2c_check_status(state) == 1) अणु
				mxl_i2c("NACK reading slave address %02x",
					msg->addr);

				/* अगर NACK, stop I2C bus and निकास */
				buf[2] = I2C_CONTROL_REG;
				buf[3] = 0xC7;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				ret = -EIO;
				जाओ निकास;
			पूर्ण

			क्रम (i = 0; i < left_over_len; i++) अणु
				msg->buf[(block_len*8)+i] =
					i2c_r_data[(i*3)+1];
				mxl_i2c("read data: %02x\t %02x",
					i2c_r_data[(i*3)+1],
					i2c_r_data[(i*3)+2]);
			पूर्ण
		पूर्ण

		/* indicate I2C पूर्णांकerface to issue NACK
		   after next I2C पढ़ो op */
		buf[0] = USB_WRITE_I2C_CMD;
		buf[1] = 0x00;

		/* control रेजिस्टर */
		buf[2] = I2C_CONTROL_REG;
		buf[3] = 0x17;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

		buf[5] = USB_END_I2C_CMD;
		ret = mxl111sf_i2c_send_data(state, 0, buf);

		/* control रेजिस्टर */
		buf[2] = I2C_CONTROL_REG;
		buf[3] = 0xC7;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

	पूर्ण
निकास:
	/* STOP and disable I2C MUX */
	buf[0] = USB_WRITE_I2C_CMD;
	buf[1] = 0x00;

	/* de-initilize I2C BUS */
	buf[5] = USB_END_I2C_CMD;
	mxl111sf_i2c_send_data(state, 0, buf);

	/* Control Register */
	buf[2] = I2C_CONTROL_REG;
	buf[3] = 0xDF;
	buf[4] = 0x03;

	/* disable I2C पूर्णांकerface */
	buf[5] = I2C_MUX_REG;
	buf[6] = 0x00;
	buf[7] = 0x00;

	/* de-initilize I2C BUS */
	buf[8] = USB_END_I2C_CMD;
	mxl111sf_i2c_send_data(state, 0, buf);

	/* disable I2C पूर्णांकerface */
	buf[2] = I2C_MUX_REG;
	buf[3] = 0x81;
	buf[4] = 0x00;

	/* disable I2C पूर्णांकerface */
	buf[5] = I2C_MUX_REG;
	buf[6] = 0x00;
	buf[7] = 0x00;

	/* disable I2C पूर्णांकerface */
	buf[8] = I2C_MUX_REG;
	buf[9] = 0x00;
	buf[10] = 0x00;

	buf[11] = USB_END_I2C_CMD;
	mxl111sf_i2c_send_data(state, 0, buf);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

पूर्णांक mxl111sf_i2c_xfer(काष्ठा i2c_adapter *adap,
		      काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा mxl111sf_state *state = d->priv;
	पूर्णांक hwi2c = (state->chip_rev > MXL111SF_V6);
	पूर्णांक i, ret;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		ret = (hwi2c) ?
			mxl111sf_i2c_hw_xfer_msg(state, &msg[i]) :
			mxl111sf_i2c_sw_xfer_msg(state, &msg[i]);
		अगर (mxl_fail(ret)) अणु
			mxl_debug_adv("failed with error %d on i2c transaction %d of %d, %sing %d bytes to/from 0x%02x",
				      ret, i+1, num,
				      (msg[i].flags & I2C_M_RD) ?
				      "read" : "writ",
				      msg[i].len, msg[i].addr);

			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&d->i2c_mutex);

	वापस i == num ? num : -EREMOTEIO;
पूर्ण
