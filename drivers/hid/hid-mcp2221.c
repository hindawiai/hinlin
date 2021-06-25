<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MCP2221A - Microchip USB to I2C Host Protocol Bridge
 *
 * Copyright (c) 2020, Rishi Gupta <gupt21@gmail.com>
 *
 * Datasheet: https://ww1.microchip.com/करोwnloads/en/DeviceDoc/20005565B.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/hid.h>
#समावेश <linux/hidraw.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/driver.h>
#समावेश "hid-ids.h"

/* Commands codes in a raw output report */
क्रमागत अणु
	MCP2221_I2C_WR_DATA = 0x90,
	MCP2221_I2C_WR_NO_STOP = 0x94,
	MCP2221_I2C_RD_DATA = 0x91,
	MCP2221_I2C_RD_RPT_START = 0x93,
	MCP2221_I2C_GET_DATA = 0x40,
	MCP2221_I2C_PARAM_OR_STATUS	= 0x10,
	MCP2221_I2C_SET_SPEED = 0x20,
	MCP2221_I2C_CANCEL = 0x10,
	MCP2221_GPIO_SET = 0x50,
	MCP2221_GPIO_GET = 0x51,
पूर्ण;

/* Response codes in a raw input report */
क्रमागत अणु
	MCP2221_SUCCESS = 0x00,
	MCP2221_I2C_ENG_BUSY = 0x01,
	MCP2221_I2C_START_TOUT = 0x12,
	MCP2221_I2C_STOP_TOUT = 0x62,
	MCP2221_I2C_WRADDRL_TOUT = 0x23,
	MCP2221_I2C_WRDATA_TOUT = 0x44,
	MCP2221_I2C_WRADDRL_NACK = 0x25,
	MCP2221_I2C_MASK_ADDR_NACK = 0x40,
	MCP2221_I2C_WRADDRL_SEND = 0x21,
	MCP2221_I2C_ADDR_NACK = 0x25,
	MCP2221_I2C_READ_COMPL = 0x55,
	MCP2221_ALT_F_NOT_GPIOV = 0xEE,
	MCP2221_ALT_F_NOT_GPIOD = 0xEF,
पूर्ण;

/* MCP GPIO direction encoding */
क्रमागत अणु
	MCP2221_सूची_OUT = 0x00,
	MCP2221_सूची_IN = 0x01,
पूर्ण;

#घोषणा MCP_NGPIO	4

/* MCP GPIO set command layout */
काष्ठा mcp_set_gpio अणु
	u8 cmd;
	u8 dummy;
	काष्ठा अणु
		u8 change_value;
		u8 value;
		u8 change_direction;
		u8 direction;
	पूर्ण gpio[MCP_NGPIO];
पूर्ण __packed;

/* MCP GPIO get command layout */
काष्ठा mcp_get_gpio अणु
	u8 cmd;
	u8 dummy;
	काष्ठा अणु
		u8 direction;
		u8 value;
	पूर्ण gpio[MCP_NGPIO];
पूर्ण __packed;

/*
 * There is no way to distinguish responses. Thereक्रमe next command
 * is sent only after response to previous has been received. Mutex
 * lock is used क्रम this purpose मुख्यly.
 */
काष्ठा mcp2221 अणु
	काष्ठा hid_device *hdev;
	काष्ठा i2c_adapter adapter;
	काष्ठा mutex lock;
	काष्ठा completion रुको_in_report;
	u8 *rxbuf;
	u8 txbuf[64];
	पूर्णांक rxbuf_idx;
	पूर्णांक status;
	u8 cur_i2c_clk_भाग;
	काष्ठा gpio_chip *gc;
	u8 gp_idx;
	u8 gpio_dir;
पूर्ण;

/*
 * Default i2c bus घड़ी frequency 400 kHz. Modअगरy this अगर you
 * want to set some other frequency (min 50 kHz - max 400 kHz).
 */
अटल uपूर्णांक i2c_clk_freq = 400;

/* Synchronously send output report to the device */
अटल पूर्णांक mcp_send_report(काष्ठा mcp2221 *mcp,
					u8 *out_report, माप_प्रकार len)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(out_report, len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* mcp2221 uses पूर्णांकerrupt endpoपूर्णांक क्रम out reports */
	ret = hid_hw_output_report(mcp->hdev, buf, len);
	kमुक्त(buf);

	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

/*
 * Send o/p report to the device and रुको क्रम i/p report to be
 * received from the device. If the device करोes not respond,
 * we समयout.
 */
अटल पूर्णांक mcp_send_data_req_status(काष्ठा mcp2221 *mcp,
			u8 *out_report, पूर्णांक len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ t;

	reinit_completion(&mcp->रुको_in_report);

	ret = mcp_send_report(mcp, out_report, len);
	अगर (ret)
		वापस ret;

	t = रुको_क्रम_completion_समयout(&mcp->रुको_in_report,
							msecs_to_jअगरfies(4000));
	अगर (!t)
		वापस -ETIMEDOUT;

	वापस mcp->status;
पूर्ण

/* Check pass/fail क्रम actual communication with i2c slave */
अटल पूर्णांक mcp_chk_last_cmd_status(काष्ठा mcp2221 *mcp)
अणु
	स_रखो(mcp->txbuf, 0, 8);
	mcp->txbuf[0] = MCP2221_I2C_PARAM_OR_STATUS;

	वापस mcp_send_data_req_status(mcp, mcp->txbuf, 8);
पूर्ण

/* Cancels last command releasing i2c bus just in हाल occupied */
अटल पूर्णांक mcp_cancel_last_cmd(काष्ठा mcp2221 *mcp)
अणु
	स_रखो(mcp->txbuf, 0, 8);
	mcp->txbuf[0] = MCP2221_I2C_PARAM_OR_STATUS;
	mcp->txbuf[2] = MCP2221_I2C_CANCEL;

	वापस mcp_send_data_req_status(mcp, mcp->txbuf, 8);
पूर्ण

अटल पूर्णांक mcp_set_i2c_speed(काष्ठा mcp2221 *mcp)
अणु
	पूर्णांक ret;

	स_रखो(mcp->txbuf, 0, 8);
	mcp->txbuf[0] = MCP2221_I2C_PARAM_OR_STATUS;
	mcp->txbuf[3] = MCP2221_I2C_SET_SPEED;
	mcp->txbuf[4] = mcp->cur_i2c_clk_भाग;

	ret = mcp_send_data_req_status(mcp, mcp->txbuf, 8);
	अगर (ret) अणु
		/* Small delay is needed here */
		usleep_range(980, 1000);
		mcp_cancel_last_cmd(mcp);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * An output report can contain minimum 1 and maximum 60 user data
 * bytes. If the number of data bytes is more then 60, we send it
 * in chunks of 60 bytes. Last chunk may contain exactly 60 or less
 * bytes. Total number of bytes is inक्रमmed in very first report to
 * mcp2221, from that poपूर्णांक onwards it first collect all the data
 * from host and then send to i2c slave device.
 */
अटल पूर्णांक mcp_i2c_ग_लिखो(काष्ठा mcp2221 *mcp,
				काष्ठा i2c_msg *msg, पूर्णांक type, u8 last_status)
अणु
	पूर्णांक ret, len, idx, sent;

	idx = 0;
	sent  = 0;
	अगर (msg->len < 60)
		len = msg->len;
	अन्यथा
		len = 60;

	करो अणु
		mcp->txbuf[0] = type;
		mcp->txbuf[1] = msg->len & 0xff;
		mcp->txbuf[2] = msg->len >> 8;
		mcp->txbuf[3] = (u8)(msg->addr << 1);

		स_नकल(&mcp->txbuf[4], &msg->buf[idx], len);

		ret = mcp_send_data_req_status(mcp, mcp->txbuf, len + 4);
		अगर (ret)
			वापस ret;

		usleep_range(980, 1000);

		अगर (last_status) अणु
			ret = mcp_chk_last_cmd_status(mcp);
			अगर (ret)
				वापस ret;
		पूर्ण

		sent = sent + len;
		अगर (sent >= msg->len)
			अवरोध;

		idx = idx + len;
		अगर ((msg->len - sent) < 60)
			len = msg->len - sent;
		अन्यथा
			len = 60;

		/*
		 * Testing shows delay is needed between successive ग_लिखोs
		 * otherwise next ग_लिखो fails on first-try from i2c core.
		 * This value is obtained through स्वतःmated stress testing.
		 */
		usleep_range(980, 1000);
	पूर्ण जबतक (len > 0);

	वापस ret;
पूर्ण

/*
 * Device पढ़ोs all data (0 - 65535 bytes) from i2c slave device and
 * stores it in device itself. This data is पढ़ो back from device to
 * host in multiples of 60 bytes using input reports.
 */
अटल पूर्णांक mcp_i2c_smbus_पढ़ो(काष्ठा mcp2221 *mcp,
				काष्ठा i2c_msg *msg, पूर्णांक type, u16 smbus_addr,
				u8 smbus_len, u8 *smbus_buf)
अणु
	पूर्णांक ret;
	u16 total_len;

	mcp->txbuf[0] = type;
	अगर (msg) अणु
		mcp->txbuf[1] = msg->len & 0xff;
		mcp->txbuf[2] = msg->len >> 8;
		mcp->txbuf[3] = (u8)(msg->addr << 1);
		total_len = msg->len;
		mcp->rxbuf = msg->buf;
	पूर्ण अन्यथा अणु
		mcp->txbuf[1] = smbus_len;
		mcp->txbuf[2] = 0;
		mcp->txbuf[3] = (u8)(smbus_addr << 1);
		total_len = smbus_len;
		mcp->rxbuf = smbus_buf;
	पूर्ण

	ret = mcp_send_data_req_status(mcp, mcp->txbuf, 4);
	अगर (ret)
		वापस ret;

	mcp->rxbuf_idx = 0;

	करो अणु
		स_रखो(mcp->txbuf, 0, 4);
		mcp->txbuf[0] = MCP2221_I2C_GET_DATA;

		ret = mcp_send_data_req_status(mcp, mcp->txbuf, 1);
		अगर (ret)
			वापस ret;

		ret = mcp_chk_last_cmd_status(mcp);
		अगर (ret)
			वापस ret;

		usleep_range(980, 1000);
	पूर्ण जबतक (mcp->rxbuf_idx < total_len);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp_i2c_xfer(काष्ठा i2c_adapter *adapter,
				काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	पूर्णांक ret;
	काष्ठा mcp2221 *mcp = i2c_get_adapdata(adapter);

	hid_hw_घातer(mcp->hdev, PM_HINT_FULLON);

	mutex_lock(&mcp->lock);

	/* Setting speed beक्रमe every transaction is required क्रम mcp2221 */
	ret = mcp_set_i2c_speed(mcp);
	अगर (ret)
		जाओ निकास;

	अगर (num == 1) अणु
		अगर (msgs->flags & I2C_M_RD) अणु
			ret = mcp_i2c_smbus_पढ़ो(mcp, msgs, MCP2221_I2C_RD_DATA,
							0, 0, शून्य);
		पूर्ण अन्यथा अणु
			ret = mcp_i2c_ग_लिखो(mcp, msgs, MCP2221_I2C_WR_DATA, 1);
		पूर्ण
		अगर (ret)
			जाओ निकास;
		ret = num;
	पूर्ण अन्यथा अगर (num == 2) अणु
		/* Ex transaction; send reg address and पढ़ो its contents */
		अगर (msgs[0].addr == msgs[1].addr &&
			!(msgs[0].flags & I2C_M_RD) &&
			 (msgs[1].flags & I2C_M_RD)) अणु

			ret = mcp_i2c_ग_लिखो(mcp, &msgs[0],
						MCP2221_I2C_WR_NO_STOP, 0);
			अगर (ret)
				जाओ निकास;

			ret = mcp_i2c_smbus_पढ़ो(mcp, &msgs[1],
						MCP2221_I2C_RD_RPT_START,
						0, 0, शून्य);
			अगर (ret)
				जाओ निकास;
			ret = num;
		पूर्ण अन्यथा अणु
			dev_err(&adapter->dev,
				"unsupported multi-msg i2c transaction\n");
			ret = -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&adapter->dev,
			"unsupported multi-msg i2c transaction\n");
		ret = -EOPNOTSUPP;
	पूर्ण

निकास:
	hid_hw_घातer(mcp->hdev, PM_HINT_NORMAL);
	mutex_unlock(&mcp->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mcp_smbus_ग_लिखो(काष्ठा mcp2221 *mcp, u16 addr,
				u8 command, u8 *buf, u8 len, पूर्णांक type,
				u8 last_status)
अणु
	पूर्णांक data_len, ret;

	mcp->txbuf[0] = type;
	mcp->txbuf[1] = len + 1; /* 1 is due to command byte itself */
	mcp->txbuf[2] = 0;
	mcp->txbuf[3] = (u8)(addr << 1);
	mcp->txbuf[4] = command;

	चयन (len) अणु
	हाल 0:
		data_len = 5;
		अवरोध;
	हाल 1:
		mcp->txbuf[5] = buf[0];
		data_len = 6;
		अवरोध;
	हाल 2:
		mcp->txbuf[5] = buf[0];
		mcp->txbuf[6] = buf[1];
		data_len = 7;
		अवरोध;
	शेष:
		स_नकल(&mcp->txbuf[5], buf, len);
		data_len = len + 5;
	पूर्ण

	ret = mcp_send_data_req_status(mcp, mcp->txbuf, data_len);
	अगर (ret)
		वापस ret;

	अगर (last_status) अणु
		usleep_range(980, 1000);

		ret = mcp_chk_last_cmd_status(mcp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mcp_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
				अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
				u8 command, पूर्णांक size,
				जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक ret;
	काष्ठा mcp2221 *mcp = i2c_get_adapdata(adapter);

	hid_hw_घातer(mcp->hdev, PM_HINT_FULLON);

	mutex_lock(&mcp->lock);

	ret = mcp_set_i2c_speed(mcp);
	अगर (ret)
		जाओ निकास;

	चयन (size) अणु

	हाल I2C_SMBUS_QUICK:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			ret = mcp_i2c_smbus_पढ़ो(mcp, शून्य, MCP2221_I2C_RD_DATA,
						addr, 0, &data->byte);
		अन्यथा
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, शून्य,
						0, MCP2221_I2C_WR_DATA, 1);
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			ret = mcp_i2c_smbus_पढ़ो(mcp, शून्य, MCP2221_I2C_RD_DATA,
						addr, 1, &data->byte);
		अन्यथा
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, शून्य,
						0, MCP2221_I2C_WR_DATA, 1);
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, शून्य,
						0, MCP2221_I2C_WR_NO_STOP, 0);
			अगर (ret)
				जाओ निकास;

			ret = mcp_i2c_smbus_पढ़ो(mcp, शून्य,
						MCP2221_I2C_RD_RPT_START,
						addr, 1, &data->byte);
		पूर्ण अन्यथा अणु
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, &data->byte,
						1, MCP2221_I2C_WR_DATA, 1);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, शून्य,
						0, MCP2221_I2C_WR_NO_STOP, 0);
			अगर (ret)
				जाओ निकास;

			ret = mcp_i2c_smbus_पढ़ो(mcp, शून्य,
						MCP2221_I2C_RD_RPT_START,
						addr, 2, (u8 *)&data->word);
		पूर्ण अन्यथा अणु
			ret = mcp_smbus_ग_लिखो(mcp, addr, command,
						(u8 *)&data->word, 2,
						MCP2221_I2C_WR_DATA, 1);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, शून्य,
						0, MCP2221_I2C_WR_NO_STOP, 1);
			अगर (ret)
				जाओ निकास;

			mcp->rxbuf_idx = 0;
			mcp->rxbuf = data->block;
			mcp->txbuf[0] = MCP2221_I2C_GET_DATA;
			ret = mcp_send_data_req_status(mcp, mcp->txbuf, 1);
			अगर (ret)
				जाओ निकास;
		पूर्ण अन्यथा अणु
			अगर (!data->block[0]) अणु
				ret = -EINVAL;
				जाओ निकास;
			पूर्ण
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, data->block,
						data->block[0] + 1,
						MCP2221_I2C_WR_DATA, 1);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = mcp_smbus_ग_लिखो(mcp, addr, command, शून्य,
						0, MCP2221_I2C_WR_NO_STOP, 1);
			अगर (ret)
				जाओ निकास;

			mcp->rxbuf_idx = 0;
			mcp->rxbuf = data->block;
			mcp->txbuf[0] = MCP2221_I2C_GET_DATA;
			ret = mcp_send_data_req_status(mcp, mcp->txbuf, 1);
			अगर (ret)
				जाओ निकास;
		पूर्ण अन्यथा अणु
			अगर (!data->block[0]) अणु
				ret = -EINVAL;
				जाओ निकास;
			पूर्ण
			ret = mcp_smbus_ग_लिखो(mcp, addr, command,
						&data->block[1], data->block[0],
						MCP2221_I2C_WR_DATA, 1);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
		ret = mcp_smbus_ग_लिखो(mcp, addr, command,
						(u8 *)&data->word,
						2, MCP2221_I2C_WR_NO_STOP, 0);
		अगर (ret)
			जाओ निकास;

		ret = mcp_i2c_smbus_पढ़ो(mcp, शून्य,
						MCP2221_I2C_RD_RPT_START,
						addr, 2, (u8 *)&data->word);
		अवरोध;
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		ret = mcp_smbus_ग_लिखो(mcp, addr, command, data->block,
						data->block[0] + 1,
						MCP2221_I2C_WR_NO_STOP, 0);
		अगर (ret)
			जाओ निकास;

		ret = mcp_i2c_smbus_पढ़ो(mcp, शून्य,
						MCP2221_I2C_RD_RPT_START,
						addr, I2C_SMBUS_BLOCK_MAX,
						data->block);
		अवरोध;
	शेष:
		dev_err(&mcp->adapter.dev,
			"unsupported smbus transaction size:%d\n", size);
		ret = -EOPNOTSUPP;
	पूर्ण

निकास:
	hid_hw_घातer(mcp->hdev, PM_HINT_NORMAL);
	mutex_unlock(&mcp->lock);
	वापस ret;
पूर्ण

अटल u32 mcp_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C |
			I2C_FUNC_SMBUS_READ_BLOCK_DATA |
			I2C_FUNC_SMBUS_BLOCK_PROC_CALL |
			(I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_PEC);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mcp_i2c_algo = अणु
	.master_xfer = mcp_i2c_xfer,
	.smbus_xfer = mcp_smbus_xfer,
	.functionality = mcp_i2c_func,
पूर्ण;

अटल पूर्णांक mcp_gpio_get(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा mcp2221 *mcp = gpiochip_get_data(gc);

	mcp->txbuf[0] = MCP2221_GPIO_GET;

	mcp->gp_idx = दुरत्व(काष्ठा mcp_get_gpio, gpio[offset].value);

	mutex_lock(&mcp->lock);
	ret = mcp_send_data_req_status(mcp, mcp->txbuf, 1);
	mutex_unlock(&mcp->lock);

	वापस ret;
पूर्ण

अटल व्योम mcp_gpio_set(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा mcp2221 *mcp = gpiochip_get_data(gc);

	स_रखो(mcp->txbuf, 0, 18);
	mcp->txbuf[0] = MCP2221_GPIO_SET;

	mcp->gp_idx = दुरत्व(काष्ठा mcp_set_gpio, gpio[offset].value);

	mcp->txbuf[mcp->gp_idx - 1] = 1;
	mcp->txbuf[mcp->gp_idx] = !!value;

	mutex_lock(&mcp->lock);
	mcp_send_data_req_status(mcp, mcp->txbuf, 18);
	mutex_unlock(&mcp->lock);
पूर्ण

अटल पूर्णांक mcp_gpio_dir_set(काष्ठा mcp2221 *mcp,
				अचिन्हित पूर्णांक offset, u8 val)
अणु
	स_रखो(mcp->txbuf, 0, 18);
	mcp->txbuf[0] = MCP2221_GPIO_SET;

	mcp->gp_idx = दुरत्व(काष्ठा mcp_set_gpio, gpio[offset].direction);

	mcp->txbuf[mcp->gp_idx - 1] = 1;
	mcp->txbuf[mcp->gp_idx] = val;

	वापस mcp_send_data_req_status(mcp, mcp->txbuf, 18);
पूर्ण

अटल पूर्णांक mcp_gpio_direction_input(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा mcp2221 *mcp = gpiochip_get_data(gc);

	mutex_lock(&mcp->lock);
	ret = mcp_gpio_dir_set(mcp, offset, MCP2221_सूची_IN);
	mutex_unlock(&mcp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp_gpio_direction_output(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा mcp2221 *mcp = gpiochip_get_data(gc);

	mutex_lock(&mcp->lock);
	ret = mcp_gpio_dir_set(mcp, offset, MCP2221_सूची_OUT);
	mutex_unlock(&mcp->lock);

	/* Can't configure as output, bailout early */
	अगर (ret)
		वापस ret;

	mcp_gpio_set(gc, offset, value);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp_gpio_get_direction(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा mcp2221 *mcp = gpiochip_get_data(gc);

	mcp->txbuf[0] = MCP2221_GPIO_GET;

	mcp->gp_idx = दुरत्व(काष्ठा mcp_get_gpio, gpio[offset].direction);

	mutex_lock(&mcp->lock);
	ret = mcp_send_data_req_status(mcp, mcp->txbuf, 1);
	mutex_unlock(&mcp->lock);

	अगर (ret)
		वापस ret;

	अगर (mcp->gpio_dir == MCP2221_सूची_IN)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

/* Gives current state of i2c engine inside mcp2221 */
अटल पूर्णांक mcp_get_i2c_eng_state(काष्ठा mcp2221 *mcp,
				u8 *data, u8 idx)
अणु
	पूर्णांक ret;

	चयन (data[idx]) अणु
	हाल MCP2221_I2C_WRADDRL_NACK:
	हाल MCP2221_I2C_WRADDRL_SEND:
		ret = -ENXIO;
		अवरोध;
	हाल MCP2221_I2C_START_TOUT:
	हाल MCP2221_I2C_STOP_TOUT:
	हाल MCP2221_I2C_WRADDRL_TOUT:
	हाल MCP2221_I2C_WRDATA_TOUT:
		ret = -ETIMEDOUT;
		अवरोध;
	हाल MCP2221_I2C_ENG_BUSY:
		ret = -EAGAIN;
		अवरोध;
	हाल MCP2221_SUCCESS:
		ret = 0x00;
		अवरोध;
	शेष:
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * MCP2221 uses पूर्णांकerrupt endpoपूर्णांक क्रम input reports. This function
 * is called by HID layer when it receives i/p report from mcp2221,
 * which is actually a response to the previously sent command.
 *
 * MCP2221A firmware specअगरic वापस codes are parsed and 0 or
 * appropriate negative error code is वापसed. Delayed response
 * results in समयout error and stray reponses results in -EIO.
 */
अटल पूर्णांक mcp2221_raw_event(काष्ठा hid_device *hdev,
				काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	u8 *buf;
	काष्ठा mcp2221 *mcp = hid_get_drvdata(hdev);

	चयन (data[0]) अणु

	हाल MCP2221_I2C_WR_DATA:
	हाल MCP2221_I2C_WR_NO_STOP:
	हाल MCP2221_I2C_RD_DATA:
	हाल MCP2221_I2C_RD_RPT_START:
		चयन (data[1]) अणु
		हाल MCP2221_SUCCESS:
			mcp->status = 0;
			अवरोध;
		शेष:
			mcp->status = mcp_get_i2c_eng_state(mcp, data, 2);
		पूर्ण
		complete(&mcp->रुको_in_report);
		अवरोध;

	हाल MCP2221_I2C_PARAM_OR_STATUS:
		चयन (data[1]) अणु
		हाल MCP2221_SUCCESS:
			अगर ((mcp->txbuf[3] == MCP2221_I2C_SET_SPEED) &&
				(data[3] != MCP2221_I2C_SET_SPEED)) अणु
				mcp->status = -EAGAIN;
				अवरोध;
			पूर्ण
			अगर (data[20] & MCP2221_I2C_MASK_ADDR_NACK) अणु
				mcp->status = -ENXIO;
				अवरोध;
			पूर्ण
			mcp->status = mcp_get_i2c_eng_state(mcp, data, 8);
			अवरोध;
		शेष:
			mcp->status = -EIO;
		पूर्ण
		complete(&mcp->रुको_in_report);
		अवरोध;

	हाल MCP2221_I2C_GET_DATA:
		चयन (data[1]) अणु
		हाल MCP2221_SUCCESS:
			अगर (data[2] == MCP2221_I2C_ADDR_NACK) अणु
				mcp->status = -ENXIO;
				अवरोध;
			पूर्ण
			अगर (!mcp_get_i2c_eng_state(mcp, data, 2)
				&& (data[3] == 0)) अणु
				mcp->status = 0;
				अवरोध;
			पूर्ण
			अगर (data[3] == 127) अणु
				mcp->status = -EIO;
				अवरोध;
			पूर्ण
			अगर (data[2] == MCP2221_I2C_READ_COMPL) अणु
				buf = mcp->rxbuf;
				स_नकल(&buf[mcp->rxbuf_idx], &data[4], data[3]);
				mcp->rxbuf_idx = mcp->rxbuf_idx + data[3];
				mcp->status = 0;
				अवरोध;
			पूर्ण
			mcp->status = -EIO;
			अवरोध;
		शेष:
			mcp->status = -EIO;
		पूर्ण
		complete(&mcp->रुको_in_report);
		अवरोध;

	हाल MCP2221_GPIO_GET:
		चयन (data[1]) अणु
		हाल MCP2221_SUCCESS:
			अगर ((data[mcp->gp_idx] == MCP2221_ALT_F_NOT_GPIOV) ||
				(data[mcp->gp_idx + 1] == MCP2221_ALT_F_NOT_GPIOD)) अणु
				mcp->status = -ENOENT;
			पूर्ण अन्यथा अणु
				mcp->status = !!data[mcp->gp_idx];
				mcp->gpio_dir = data[mcp->gp_idx + 1];
			पूर्ण
			अवरोध;
		शेष:
			mcp->status = -EAGAIN;
		पूर्ण
		complete(&mcp->रुको_in_report);
		अवरोध;

	हाल MCP2221_GPIO_SET:
		चयन (data[1]) अणु
		हाल MCP2221_SUCCESS:
			अगर ((data[mcp->gp_idx] == MCP2221_ALT_F_NOT_GPIOV) ||
				(data[mcp->gp_idx - 1] == MCP2221_ALT_F_NOT_GPIOV)) अणु
				mcp->status = -ENOENT;
			पूर्ण अन्यथा अणु
				mcp->status = 0;
			पूर्ण
			अवरोध;
		शेष:
			mcp->status = -EAGAIN;
		पूर्ण
		complete(&mcp->रुको_in_report);
		अवरोध;

	शेष:
		mcp->status = -EIO;
		complete(&mcp->रुको_in_report);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक mcp2221_probe(काष्ठा hid_device *hdev,
					स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा mcp2221 *mcp;

	mcp = devm_kzalloc(&hdev->dev, माप(*mcp), GFP_KERNEL);
	अगर (!mcp)
		वापस -ENOMEM;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "can't parse reports\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret) अणु
		hid_err(hdev, "can't start hardware\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_खोलो(hdev);
	अगर (ret) अणु
		hid_err(hdev, "can't open device\n");
		जाओ err_hstop;
	पूर्ण

	mutex_init(&mcp->lock);
	init_completion(&mcp->रुको_in_report);
	hid_set_drvdata(hdev, mcp);
	mcp->hdev = hdev;

	/* Set I2C bus घड़ी भागiser */
	अगर (i2c_clk_freq > 400)
		i2c_clk_freq = 400;
	अगर (i2c_clk_freq < 50)
		i2c_clk_freq = 50;
	mcp->cur_i2c_clk_भाग = (12000000 / (i2c_clk_freq * 1000)) - 3;

	mcp->adapter.owner = THIS_MODULE;
	mcp->adapter.class = I2C_CLASS_HWMON;
	mcp->adapter.algo = &mcp_i2c_algo;
	mcp->adapter.retries = 1;
	mcp->adapter.dev.parent = &hdev->dev;
	snम_लिखो(mcp->adapter.name, माप(mcp->adapter.name),
			"MCP2221 usb-i2c bridge on hidraw%d",
			((काष्ठा hidraw *)hdev->hidraw)->minor);

	ret = i2c_add_adapter(&mcp->adapter);
	अगर (ret) अणु
		hid_err(hdev, "can't add usb-i2c adapter: %d\n", ret);
		जाओ err_i2c;
	पूर्ण
	i2c_set_adapdata(&mcp->adapter, mcp);

	/* Setup GPIO chip */
	mcp->gc = devm_kzalloc(&hdev->dev, माप(*mcp->gc), GFP_KERNEL);
	अगर (!mcp->gc) अणु
		ret = -ENOMEM;
		जाओ err_gc;
	पूर्ण

	mcp->gc->label = "mcp2221_gpio";
	mcp->gc->direction_input = mcp_gpio_direction_input;
	mcp->gc->direction_output = mcp_gpio_direction_output;
	mcp->gc->get_direction = mcp_gpio_get_direction;
	mcp->gc->set = mcp_gpio_set;
	mcp->gc->get = mcp_gpio_get;
	mcp->gc->ngpio = MCP_NGPIO;
	mcp->gc->base = -1;
	mcp->gc->can_sleep = 1;
	mcp->gc->parent = &hdev->dev;

	ret = devm_gpiochip_add_data(&hdev->dev, mcp->gc, mcp);
	अगर (ret)
		जाओ err_gc;

	वापस 0;

err_gc:
	i2c_del_adapter(&mcp->adapter);
err_i2c:
	hid_hw_बंद(mcp->hdev);
err_hstop:
	hid_hw_stop(mcp->hdev);
	वापस ret;
पूर्ण

अटल व्योम mcp2221_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा mcp2221 *mcp = hid_get_drvdata(hdev);

	i2c_del_adapter(&mcp->adapter);
	hid_hw_बंद(mcp->hdev);
	hid_hw_stop(mcp->hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id mcp2221_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROCHIP, USB_DEVICE_ID_MCP2221) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, mcp2221_devices);

अटल काष्ठा hid_driver mcp2221_driver = अणु
	.name		= "mcp2221",
	.id_table	= mcp2221_devices,
	.probe		= mcp2221_probe,
	.हटाओ		= mcp2221_हटाओ,
	.raw_event	= mcp2221_raw_event,
पूर्ण;

/* Register with HID core */
module_hid_driver(mcp2221_driver);

MODULE_AUTHOR("Rishi Gupta <gupt21@gmail.com>");
MODULE_DESCRIPTION("MCP2221 Microchip HID USB to I2C master bridge");
MODULE_LICENSE("GPL v2");
