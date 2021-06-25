<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Raydium touchscreen I2C driver.
 *
 * Copyright (C) 2012-2014, Raydium Semiconductor Corporation.
 *
 * Raydium reserves the right to make changes without further notice
 * to the materials described herein. Raydium करोes not assume any
 * liability arising out of the application described herein.
 *
 * Contact Raydium Semiconductor Corporation at www.rad-ic.com
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

/* Slave I2C mode */
#घोषणा RM_BOOT_BLDR		0x02
#घोषणा RM_BOOT_MAIN		0x03

/* I2C bootoloader commands */
#घोषणा RM_CMD_BOOT_PAGE_WRT	0x0B		/* send bl page ग_लिखो */
#घोषणा RM_CMD_BOOT_WRT		0x11		/* send bl ग_लिखो */
#घोषणा RM_CMD_BOOT_ACK		0x22		/* send ack*/
#घोषणा RM_CMD_BOOT_CHK		0x33		/* send data check */
#घोषणा RM_CMD_BOOT_READ	0x44		/* send रुको bl data पढ़ोy*/

#घोषणा RM_BOOT_RDY		0xFF		/* bl data पढ़ोy */

/* I2C मुख्य commands */
#घोषणा RM_CMD_QUERY_BANK	0x2B
#घोषणा RM_CMD_DATA_BANK	0x4D
#घोषणा RM_CMD_ENTER_SLEEP	0x4E
#घोषणा RM_CMD_BANK_SWITCH	0xAA

#घोषणा RM_RESET_MSG_ADDR	0x40000004

#घोषणा RM_MAX_READ_SIZE	56
#घोषणा RM_PACKET_CRC_SIZE	2

/* Touch relative info */
#घोषणा RM_MAX_RETRIES		3
#घोषणा RM_RETRY_DELAY_MS	20
#घोषणा RM_MAX_TOUCH_NUM	10
#घोषणा RM_BOOT_DELAY_MS	100

/* Offsets in contact data */
#घोषणा RM_CONTACT_STATE_POS	0
#घोषणा RM_CONTACT_X_POS	1
#घोषणा RM_CONTACT_Y_POS	3
#घोषणा RM_CONTACT_PRESSURE_POS	5
#घोषणा RM_CONTACT_WIDTH_X_POS	6
#घोषणा RM_CONTACT_WIDTH_Y_POS	7

/* Bootloader relative info */
#घोषणा RM_BL_WRT_CMD_SIZE	3	/* bl flash wrt cmd size */
#घोषणा RM_BL_WRT_PKG_SIZE	32	/* bl wrt pkg size */
#घोषणा RM_BL_WRT_LEN		(RM_BL_WRT_PKG_SIZE + RM_BL_WRT_CMD_SIZE)
#घोषणा RM_FW_PAGE_SIZE		128
#घोषणा RM_MAX_FW_RETRIES	30
#घोषणा RM_MAX_FW_SIZE		0xD000

#घोषणा RM_POWERON_DELAY_USEC	500
#घोषणा RM_RESET_DELAY_MSEC	50

क्रमागत raydium_bl_cmd अणु
	BL_HEADER = 0,
	BL_PAGE_STR,
	BL_PKG_IDX,
	BL_DATA_STR,
पूर्ण;

क्रमागत raydium_bl_ack अणु
	RAYDIUM_ACK_शून्य = 0,
	RAYDIUM_WAIT_READY,
	RAYDIUM_PATH_READY,
पूर्ण;

क्रमागत raydium_boot_mode अणु
	RAYDIUM_TS_MAIN = 0,
	RAYDIUM_TS_BLDR,
पूर्ण;

/* Response to RM_CMD_DATA_BANK request */
काष्ठा raydium_data_info अणु
	__le32 data_bank_addr;
	u8 pkg_size;
	u8 tp_info_size;
पूर्ण;

काष्ठा raydium_info अणु
	__le32 hw_ver;		/*device version */
	u8 मुख्य_ver;
	u8 sub_ver;
	__le16 ft_ver;		/* test version */
	u8 x_num;
	u8 y_num;
	__le16 x_max;
	__le16 y_max;
	u8 x_res;		/* units/mm */
	u8 y_res;		/* units/mm */
पूर्ण;

/* काष्ठा raydium_data - represents state of Raydium touchscreen device */
काष्ठा raydium_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;

	काष्ठा regulator *avdd;
	काष्ठा regulator *vccio;
	काष्ठा gpio_desc *reset_gpio;

	काष्ठा raydium_info info;

	काष्ठा mutex sysfs_mutex;

	u8 *report_data;

	u32 data_bank_addr;
	u8 report_size;
	u8 contact_size;
	u8 pkg_size;

	क्रमागत raydium_boot_mode boot_mode;

	bool wake_irq_enabled;
पूर्ण;

/*
 * Header to be sent क्रम RM_CMD_BANK_SWITCH command. This is used by
 * raydium_i2c_अणुपढ़ो|sendपूर्ण below.
 */
काष्ठा __packed raydium_bank_चयन_header अणु
	u8 cmd;
	__be32 be_addr;
पूर्ण;

अटल पूर्णांक raydium_i2c_xfer(काष्ठा i2c_client *client, u32 addr,
			    काष्ठा i2c_msg *xfer, माप_प्रकार xfer_count)
अणु
	पूर्णांक ret;
	/*
	 * If address is greater than 255, then RM_CMD_BANK_SWITCH needs to be
	 * sent first. Else, skip the header i.e. xfer[0].
	 */
	पूर्णांक xfer_start_idx = (addr > 0xff) ? 0 : 1;
	xfer_count -= xfer_start_idx;

	ret = i2c_transfer(client->adapter, &xfer[xfer_start_idx], xfer_count);
	अगर (likely(ret == xfer_count))
		वापस 0;

	वापस ret < 0 ? ret : -EIO;
पूर्ण

अटल पूर्णांक raydium_i2c_send(काष्ठा i2c_client *client,
			    u32 addr, स्थिर व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक tries = 0;
	पूर्णांक error;
	u8 *tx_buf;
	u8 reg_addr = addr & 0xff;

	tx_buf = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!tx_buf)
		वापस -ENOMEM;

	tx_buf[0] = reg_addr;
	स_नकल(tx_buf + 1, data, len);

	करो अणु
		काष्ठा raydium_bank_चयन_header header = अणु
			.cmd = RM_CMD_BANK_SWITCH,
			.be_addr = cpu_to_be32(addr),
		पूर्ण;

		/*
		 * Perक्रमm as a single i2c_transfer transaction to ensure that
		 * no other I2C transactions are initiated on the bus to any
		 * other device in between. Initiating transacations to other
		 * devices after RM_CMD_BANK_SWITCH is sent is known to cause
		 * issues. This is also why regmap infraकाष्ठाure cannot be used
		 * क्रम this driver. Regmap handles page(bank) चयन and पढ़ोs
		 * as separate i2c_transfer() operations. This can result in
		 * problems अगर the Raydium device is on a shared I2C bus.
		 */
		काष्ठा i2c_msg xfer[] = अणु
			अणु
				.addr = client->addr,
				.len = माप(header),
				.buf = (u8 *)&header,
			पूर्ण,
			अणु
				.addr = client->addr,
				.len = len + 1,
				.buf = tx_buf,
			पूर्ण,
		पूर्ण;

		error = raydium_i2c_xfer(client, addr, xfer, ARRAY_SIZE(xfer));
		अगर (likely(!error))
			वापस 0;

		msleep(RM_RETRY_DELAY_MS);
	पूर्ण जबतक (++tries < RM_MAX_RETRIES);

	dev_err(&client->dev, "%s failed: %d\n", __func__, error);
	वापस error;
पूर्ण

अटल पूर्णांक raydium_i2c_पढ़ो(काष्ठा i2c_client *client,
			    u32 addr, व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक error;

	जबतक (len) अणु
		u8 reg_addr = addr & 0xff;
		काष्ठा raydium_bank_चयन_header header = अणु
			.cmd = RM_CMD_BANK_SWITCH,
			.be_addr = cpu_to_be32(addr),
		पूर्ण;
		माप_प्रकार xfer_len = min_t(माप_प्रकार, len, RM_MAX_READ_SIZE);

		/*
		 * Perक्रमm as a single i2c_transfer transaction to ensure that
		 * no other I2C transactions are initiated on the bus to any
		 * other device in between. Initiating transacations to other
		 * devices after RM_CMD_BANK_SWITCH is sent is known to cause
		 * issues. This is also why regmap infraकाष्ठाure cannot be used
		 * क्रम this driver. Regmap handles page(bank) चयन and ग_लिखोs
		 * as separate i2c_transfer() operations. This can result in
		 * problems अगर the Raydium device is on a shared I2C bus.
		 */
		काष्ठा i2c_msg xfer[] = अणु
			अणु
				.addr = client->addr,
				.len = माप(header),
				.buf = (u8 *)&header,
			पूर्ण,
			अणु
				.addr = client->addr,
				.len = 1,
				.buf = &reg_addr,
			पूर्ण,
			अणु
				.addr = client->addr,
				.len = xfer_len,
				.buf = data,
				.flags = I2C_M_RD,
			पूर्ण
		पूर्ण;

		error = raydium_i2c_xfer(client, addr, xfer, ARRAY_SIZE(xfer));
		अगर (unlikely(error))
			वापस error;

		len -= xfer_len;
		data += xfer_len;
		addr += xfer_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_sw_reset(काष्ठा i2c_client *client)
अणु
	स्थिर u8 soft_rst_cmd = 0x01;
	पूर्णांक error;

	error = raydium_i2c_send(client, RM_RESET_MSG_ADDR, &soft_rst_cmd,
				 माप(soft_rst_cmd));
	अगर (error) अणु
		dev_err(&client->dev, "software reset failed: %d\n", error);
		वापस error;
	पूर्ण

	msleep(RM_RESET_DELAY_MSEC);

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_query_ts_info(काष्ठा raydium_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	काष्ठा raydium_data_info data_info;
	__le32 query_bank_addr;

	पूर्णांक error, retry_cnt;

	क्रम (retry_cnt = 0; retry_cnt < RM_MAX_RETRIES; retry_cnt++) अणु
		error = raydium_i2c_पढ़ो(client, RM_CMD_DATA_BANK,
					 &data_info, माप(data_info));
		अगर (error)
			जारी;

		/*
		 * Warn user अगर we alपढ़ोy allocated memory क्रम reports and
		 * then the size changed (due to firmware update?) and keep
		 * old size instead.
		 */
		अगर (ts->report_data && ts->pkg_size != data_info.pkg_size) अणु
			dev_warn(&client->dev,
				 "report size changes, was: %d, new: %d\n",
				 ts->pkg_size, data_info.pkg_size);
		पूर्ण अन्यथा अणु
			ts->pkg_size = data_info.pkg_size;
			ts->report_size = ts->pkg_size - RM_PACKET_CRC_SIZE;
		पूर्ण

		ts->contact_size = data_info.tp_info_size;
		ts->data_bank_addr = le32_to_cpu(data_info.data_bank_addr);

		dev_dbg(&client->dev,
			"data_bank_addr: %#08x, report_size: %d, contact_size: %d\n",
			ts->data_bank_addr, ts->report_size, ts->contact_size);

		error = raydium_i2c_पढ़ो(client, RM_CMD_QUERY_BANK,
					 &query_bank_addr,
					 माप(query_bank_addr));
		अगर (error)
			जारी;

		error = raydium_i2c_पढ़ो(client, le32_to_cpu(query_bank_addr),
					 &ts->info, माप(ts->info));
		अगर (error)
			जारी;

		वापस 0;
	पूर्ण

	dev_err(&client->dev, "failed to query device parameters: %d\n", error);
	वापस error;
पूर्ण

अटल पूर्णांक raydium_i2c_check_fw_status(काष्ठा raydium_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	अटल स्थिर u8 bl_ack = 0x62;
	अटल स्थिर u8 मुख्य_ack = 0x66;
	u8 buf[4];
	पूर्णांक error;

	error = raydium_i2c_पढ़ो(client, RM_CMD_BOOT_READ, buf, माप(buf));
	अगर (!error) अणु
		अगर (buf[0] == bl_ack)
			ts->boot_mode = RAYDIUM_TS_BLDR;
		अन्यथा अगर (buf[0] == मुख्य_ack)
			ts->boot_mode = RAYDIUM_TS_MAIN;
		वापस 0;
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक raydium_i2c_initialize(काष्ठा raydium_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error, retry_cnt;

	क्रम (retry_cnt = 0; retry_cnt < RM_MAX_RETRIES; retry_cnt++) अणु
		/* Wait क्रम Hello packet */
		msleep(RM_BOOT_DELAY_MS);

		error = raydium_i2c_check_fw_status(ts);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to read 'hello' packet: %d\n", error);
			जारी;
		पूर्ण

		अगर (ts->boot_mode == RAYDIUM_TS_BLDR ||
		    ts->boot_mode == RAYDIUM_TS_MAIN) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (error)
		ts->boot_mode = RAYDIUM_TS_BLDR;

	अगर (ts->boot_mode == RAYDIUM_TS_BLDR) अणु
		ts->info.hw_ver = cpu_to_le32(0xffffffffUL);
		ts->info.मुख्य_ver = 0xff;
		ts->info.sub_ver = 0xff;
	पूर्ण अन्यथा अणु
		raydium_i2c_query_ts_info(ts);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक raydium_i2c_bl_chk_state(काष्ठा i2c_client *client,
				    क्रमागत raydium_bl_ack state)
अणु
	अटल स्थिर u8 ack_ok[] = अणु 0xFF, 0x39, 0x30, 0x30, 0x54 पूर्ण;
	u8 rbuf[माप(ack_ok)];
	u8 retry;
	पूर्णांक error;

	क्रम (retry = 0; retry < RM_MAX_FW_RETRIES; retry++) अणु
		चयन (state) अणु
		हाल RAYDIUM_ACK_शून्य:
			वापस 0;

		हाल RAYDIUM_WAIT_READY:
			error = raydium_i2c_पढ़ो(client, RM_CMD_BOOT_CHK,
						 &rbuf[0], 1);
			अगर (!error && rbuf[0] == RM_BOOT_RDY)
				वापस 0;

			अवरोध;

		हाल RAYDIUM_PATH_READY:
			error = raydium_i2c_पढ़ो(client, RM_CMD_BOOT_CHK,
						 rbuf, माप(rbuf));
			अगर (!error && !स_भेद(rbuf, ack_ok, माप(ack_ok)))
				वापस 0;

			अवरोध;

		शेष:
			dev_err(&client->dev, "%s: invalid target state %d\n",
				__func__, state);
			वापस -EINVAL;
		पूर्ण

		msleep(20);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक raydium_i2c_ग_लिखो_object(काष्ठा i2c_client *client,
				    स्थिर व्योम *data, माप_प्रकार len,
				    क्रमागत raydium_bl_ack state)
अणु
	पूर्णांक error;
	अटल स्थिर u8 cmd[] = अणु 0xFF, 0x39 पूर्ण;

	error = raydium_i2c_send(client, RM_CMD_BOOT_WRT, data, len);
	अगर (error) अणु
		dev_err(&client->dev, "WRT obj command failed: %d\n",
			error);
		वापस error;
	पूर्ण

	error = raydium_i2c_send(client, RM_CMD_BOOT_ACK, cmd, माप(cmd));
	अगर (error) अणु
		dev_err(&client->dev, "Ack obj command failed: %d\n", error);
		वापस error;
	पूर्ण

	error = raydium_i2c_bl_chk_state(client, state);
	अगर (error) अणु
		dev_err(&client->dev, "BL check state failed: %d\n", error);
		वापस error;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_boot_trigger(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 cmd[7][6] = अणु
		अणु 0x08, 0x0C, 0x09, 0x00, 0x50, 0xD7 पूर्ण,
		अणु 0x08, 0x04, 0x09, 0x00, 0x50, 0xA5 पूर्ण,
		अणु 0x08, 0x04, 0x09, 0x00, 0x50, 0x00 पूर्ण,
		अणु 0x08, 0x04, 0x09, 0x00, 0x50, 0xA5 पूर्ण,
		अणु 0x08, 0x0C, 0x09, 0x00, 0x50, 0x00 पूर्ण,
		अणु 0x06, 0x01, 0x00, 0x00, 0x00, 0x00 पूर्ण,
		अणु 0x02, 0xA2, 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण;
	पूर्णांक i;
	पूर्णांक error;

	क्रम (i = 0; i < 7; i++) अणु
		error = raydium_i2c_ग_लिखो_object(client, cmd[i], माप(cmd[i]),
						 RAYDIUM_WAIT_READY);
		अगर (error) अणु
			dev_err(&client->dev,
				"boot trigger failed at step %d: %d\n",
				i, error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_fw_trigger(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 cmd[5][11] = अणु
		अणु 0, 0x09, 0x71, 0x0C, 0x09, 0x00, 0x50, 0xD7, 0, 0, 0 पूर्ण,
		अणु 0, 0x09, 0x71, 0x04, 0x09, 0x00, 0x50, 0xA5, 0, 0, 0 पूर्ण,
		अणु 0, 0x09, 0x71, 0x04, 0x09, 0x00, 0x50, 0x00, 0, 0, 0 पूर्ण,
		अणु 0, 0x09, 0x71, 0x04, 0x09, 0x00, 0x50, 0xA5, 0, 0, 0 पूर्ण,
		अणु 0, 0x09, 0x71, 0x0C, 0x09, 0x00, 0x50, 0x00, 0, 0, 0 पूर्ण,
	पूर्ण;
	पूर्णांक i;
	पूर्णांक error;

	क्रम (i = 0; i < 5; i++) अणु
		error = raydium_i2c_ग_लिखो_object(client, cmd[i], माप(cmd[i]),
						 RAYDIUM_ACK_शून्य);
		अगर (error) अणु
			dev_err(&client->dev,
				"fw trigger failed at step %d: %d\n",
				i, error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_check_path(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 cmd[] = अणु 0x09, 0x00, 0x09, 0x00, 0x50, 0x10, 0x00 पूर्ण;
	पूर्णांक error;

	error = raydium_i2c_ग_लिखो_object(client, cmd, माप(cmd),
					 RAYDIUM_PATH_READY);
	अगर (error) अणु
		dev_err(&client->dev, "check path command failed: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_enter_bl(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 cal_cmd[] = अणु 0x00, 0x01, 0x52 पूर्ण;
	पूर्णांक error;

	error = raydium_i2c_ग_लिखो_object(client, cal_cmd, माप(cal_cmd),
					 RAYDIUM_ACK_शून्य);
	अगर (error) अणु
		dev_err(&client->dev, "enter bl command failed: %d\n", error);
		वापस error;
	पूर्ण

	msleep(RM_BOOT_DELAY_MS);
	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_leave_bl(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 leave_cmd[] = अणु 0x05, 0x00 पूर्ण;
	पूर्णांक error;

	error = raydium_i2c_ग_लिखो_object(client, leave_cmd, माप(leave_cmd),
					 RAYDIUM_ACK_शून्य);
	अगर (error) अणु
		dev_err(&client->dev, "leave bl command failed: %d\n", error);
		वापस error;
	पूर्ण

	msleep(RM_BOOT_DELAY_MS);
	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_ग_लिखो_checksum(काष्ठा i2c_client *client,
				      माप_प्रकार length, u16 checksum)
अणु
	u8 checksum_cmd[] = अणु 0x00, 0x05, 0x6D, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	पूर्णांक error;

	put_unaligned_le16(length, &checksum_cmd[3]);
	put_unaligned_le16(checksum, &checksum_cmd[5]);

	error = raydium_i2c_ग_लिखो_object(client,
					 checksum_cmd, माप(checksum_cmd),
					 RAYDIUM_ACK_शून्य);
	अगर (error) अणु
		dev_err(&client->dev, "failed to write checksum: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_disable_watch_करोg(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 cmd[] = अणु 0x0A, 0xAA पूर्ण;
	पूर्णांक error;

	error = raydium_i2c_ग_लिखो_object(client, cmd, माप(cmd),
					 RAYDIUM_WAIT_READY);
	अगर (error) अणु
		dev_err(&client->dev, "disable watchdog command failed: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_fw_ग_लिखो_page(काष्ठा i2c_client *client,
				     u16 page_idx, स्थिर व्योम *data, माप_प्रकार len)
अणु
	u8 buf[RM_BL_WRT_LEN];
	माप_प्रकार xfer_len;
	पूर्णांक error;
	पूर्णांक i;

	BUILD_BUG_ON((RM_FW_PAGE_SIZE % RM_BL_WRT_PKG_SIZE) != 0);

	क्रम (i = 0; i < RM_FW_PAGE_SIZE / RM_BL_WRT_PKG_SIZE; i++) अणु
		buf[BL_HEADER] = RM_CMD_BOOT_PAGE_WRT;
		buf[BL_PAGE_STR] = page_idx ? 0xff : 0;
		buf[BL_PKG_IDX] = i + 1;

		xfer_len = min_t(माप_प्रकार, len, RM_BL_WRT_PKG_SIZE);
		स_नकल(&buf[BL_DATA_STR], data, xfer_len);
		अगर (len < RM_BL_WRT_PKG_SIZE)
			स_रखो(&buf[BL_DATA_STR + xfer_len], 0xff,
				RM_BL_WRT_PKG_SIZE - xfer_len);

		error = raydium_i2c_ग_लिखो_object(client, buf, RM_BL_WRT_LEN,
						 RAYDIUM_WAIT_READY);
		अगर (error) अणु
			dev_err(&client->dev,
				"page write command failed for page %d, chunk %d: %d\n",
				page_idx, i, error);
			वापस error;
		पूर्ण

		data += xfer_len;
		len -= xfer_len;
	पूर्ण

	वापस error;
पूर्ण

अटल u16 raydium_calc_chksum(स्थिर u8 *buf, u16 len)
अणु
	u16 checksum = 0;
	u16 i;

	क्रम (i = 0; i < len; i++)
		checksum += buf[i];

	वापस checksum;
पूर्ण

अटल पूर्णांक raydium_i2c_करो_update_firmware(काष्ठा raydium_data *ts,
					 स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर व्योम *data;
	माप_प्रकार data_len;
	माप_प्रकार len;
	पूर्णांक page_nr;
	पूर्णांक i;
	पूर्णांक error;
	u16 fw_checksum;

	अगर (fw->size == 0 || fw->size > RM_MAX_FW_SIZE) अणु
		dev_err(&client->dev, "Invalid firmware length\n");
		वापस -EINVAL;
	पूर्ण

	error = raydium_i2c_check_fw_status(ts);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to access IC %d\n", error);
		वापस error;
	पूर्ण

	अगर (ts->boot_mode == RAYDIUM_TS_MAIN) अणु
		क्रम (i = 0; i < RM_MAX_RETRIES; i++) अणु
			error = raydium_i2c_enter_bl(client);
			अगर (!error) अणु
				error = raydium_i2c_check_fw_status(ts);
				अगर (error) अणु
					dev_err(&client->dev,
						"unable to access IC: %d\n",
						error);
					वापस error;
				पूर्ण

				अगर (ts->boot_mode == RAYDIUM_TS_BLDR)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (ts->boot_mode == RAYDIUM_TS_MAIN) अणु
			dev_err(&client->dev,
				"failed to jump to boot loader: %d\n",
				error);
			वापस -EIO;
		पूर्ण
	पूर्ण

	error = raydium_i2c_disable_watch_करोg(client);
	अगर (error)
		वापस error;

	error = raydium_i2c_check_path(client);
	अगर (error)
		वापस error;

	error = raydium_i2c_boot_trigger(client);
	अगर (error) अणु
		dev_err(&client->dev, "send boot trigger fail: %d\n", error);
		वापस error;
	पूर्ण

	msleep(RM_BOOT_DELAY_MS);

	data = fw->data;
	data_len = fw->size;
	page_nr = 0;

	जबतक (data_len) अणु
		len = min_t(माप_प्रकार, data_len, RM_FW_PAGE_SIZE);

		error = raydium_i2c_fw_ग_लिखो_page(client, page_nr++, data, len);
		अगर (error)
			वापस error;

		msleep(20);

		data += len;
		data_len -= len;
	पूर्ण

	error = raydium_i2c_leave_bl(client);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to leave boot loader: %d\n", error);
		वापस error;
	पूर्ण

	dev_dbg(&client->dev, "left boot loader mode\n");
	msleep(RM_BOOT_DELAY_MS);

	error = raydium_i2c_check_fw_status(ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to check fw status after write: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर (ts->boot_mode != RAYDIUM_TS_MAIN) अणु
		dev_err(&client->dev,
			"failed to switch to main fw after writing firmware: %d\n",
			error);
		वापस -EINVAL;
	पूर्ण

	error = raydium_i2c_fw_trigger(client);
	अगर (error) अणु
		dev_err(&client->dev, "failed to trigger fw: %d\n", error);
		वापस error;
	पूर्ण

	fw_checksum = raydium_calc_chksum(fw->data, fw->size);

	error = raydium_i2c_ग_लिखो_checksum(client, fw->size, fw_checksum);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक raydium_i2c_fw_update(काष्ठा raydium_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर काष्ठा firmware *fw = शून्य;
	अक्षर *fw_file;
	पूर्णांक error;

	fw_file = kaप्र_लिखो(GFP_KERNEL, "raydium_%#04x.fw",
			    le32_to_cpu(ts->info.hw_ver));
	अगर (!fw_file)
		वापस -ENOMEM;

	dev_dbg(&client->dev, "firmware name: %s\n", fw_file);

	error = request_firmware(&fw, fw_file, &client->dev);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to open firmware %s\n", fw_file);
		जाओ out_मुक्त_fw_file;
	पूर्ण

	disable_irq(client->irq);

	error = raydium_i2c_करो_update_firmware(ts, fw);
	अगर (error) अणु
		dev_err(&client->dev, "firmware update failed: %d\n", error);
		ts->boot_mode = RAYDIUM_TS_BLDR;
		जाओ out_enable_irq;
	पूर्ण

	error = raydium_i2c_initialize(ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to initialize device after firmware update: %d\n",
			error);
		ts->boot_mode = RAYDIUM_TS_BLDR;
		जाओ out_enable_irq;
	पूर्ण

	ts->boot_mode = RAYDIUM_TS_MAIN;

out_enable_irq:
	enable_irq(client->irq);
	msleep(100);

	release_firmware(fw);

out_मुक्त_fw_file:
	kमुक्त(fw_file);

	वापस error;
पूर्ण

अटल व्योम raydium_mt_event(काष्ठा raydium_data *ts)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ts->report_size / ts->contact_size; i++) अणु
		u8 *contact = &ts->report_data[ts->contact_size * i];
		bool state = contact[RM_CONTACT_STATE_POS];
		u8 wx, wy;

		input_mt_slot(ts->input, i);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, state);

		अगर (!state)
			जारी;

		input_report_असल(ts->input, ABS_MT_POSITION_X,
				get_unaligned_le16(&contact[RM_CONTACT_X_POS]));
		input_report_असल(ts->input, ABS_MT_POSITION_Y,
				get_unaligned_le16(&contact[RM_CONTACT_Y_POS]));
		input_report_असल(ts->input, ABS_MT_PRESSURE,
				contact[RM_CONTACT_PRESSURE_POS]);

		wx = contact[RM_CONTACT_WIDTH_X_POS];
		wy = contact[RM_CONTACT_WIDTH_Y_POS];

		input_report_असल(ts->input, ABS_MT_TOUCH_MAJOR, max(wx, wy));
		input_report_असल(ts->input, ABS_MT_TOUCH_MINOR, min(wx, wy));
	पूर्ण

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
पूर्ण

अटल irqवापस_t raydium_i2c_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा raydium_data *ts = _dev;
	पूर्णांक error;
	u16 fw_crc;
	u16 calc_crc;

	अगर (ts->boot_mode != RAYDIUM_TS_MAIN)
		जाओ out;

	error = raydium_i2c_पढ़ो(ts->client, ts->data_bank_addr,
				 ts->report_data, ts->pkg_size);
	अगर (error)
		जाओ out;

	fw_crc = get_unaligned_le16(&ts->report_data[ts->report_size]);
	calc_crc = raydium_calc_chksum(ts->report_data, ts->report_size);
	अगर (unlikely(fw_crc != calc_crc)) अणु
		dev_warn(&ts->client->dev,
			 "%s: invalid packet crc %#04x vs %#04x\n",
			 __func__, calc_crc, fw_crc);
		जाओ out;
	पूर्ण

	raydium_mt_event(ts);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार raydium_i2c_fw_ver_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा raydium_data *ts = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d.%d\n", ts->info.मुख्य_ver, ts->info.sub_ver);
पूर्ण

अटल sमाप_प्रकार raydium_i2c_hw_ver_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा raydium_data *ts = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%#04x\n", le32_to_cpu(ts->info.hw_ver));
पूर्ण

अटल sमाप_प्रकार raydium_i2c_boot_mode_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा raydium_data *ts = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%s\n",
		       ts->boot_mode == RAYDIUM_TS_MAIN ?
				"Normal" : "Recovery");
पूर्ण

अटल sमाप_प्रकार raydium_i2c_update_fw_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा raydium_data *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&ts->sysfs_mutex);
	अगर (error)
		वापस error;

	error = raydium_i2c_fw_update(ts);

	mutex_unlock(&ts->sysfs_mutex);

	वापस error ?: count;
पूर्ण

अटल sमाप_प्रकार raydium_i2c_calibrate_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा raydium_data *ts = i2c_get_clientdata(client);
	अटल स्थिर u8 cal_cmd[] = अणु 0x00, 0x01, 0x9E पूर्ण;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&ts->sysfs_mutex);
	अगर (error)
		वापस error;

	error = raydium_i2c_ग_लिखो_object(client, cal_cmd, माप(cal_cmd),
					 RAYDIUM_WAIT_READY);
	अगर (error)
		dev_err(&client->dev, "calibrate command failed: %d\n", error);

	mutex_unlock(&ts->sysfs_mutex);
	वापस error ?: count;
पूर्ण

अटल DEVICE_ATTR(fw_version, S_IRUGO, raydium_i2c_fw_ver_show, शून्य);
अटल DEVICE_ATTR(hw_version, S_IRUGO, raydium_i2c_hw_ver_show, शून्य);
अटल DEVICE_ATTR(boot_mode, S_IRUGO, raydium_i2c_boot_mode_show, शून्य);
अटल DEVICE_ATTR(update_fw, S_IWUSR, शून्य, raydium_i2c_update_fw_store);
अटल DEVICE_ATTR(calibrate, S_IWUSR, शून्य, raydium_i2c_calibrate_store);

अटल काष्ठा attribute *raydium_i2c_attributes[] = अणु
	&dev_attr_update_fw.attr,
	&dev_attr_boot_mode.attr,
	&dev_attr_fw_version.attr,
	&dev_attr_hw_version.attr,
	&dev_attr_calibrate.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group raydium_i2c_attribute_group = अणु
	.attrs = raydium_i2c_attributes,
पूर्ण;

अटल पूर्णांक raydium_i2c_घातer_on(काष्ठा raydium_data *ts)
अणु
	पूर्णांक error;

	अगर (!ts->reset_gpio)
		वापस 0;

	gpiod_set_value_cansleep(ts->reset_gpio, 1);

	error = regulator_enable(ts->avdd);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"failed to enable avdd regulator: %d\n", error);
		जाओ release_reset_gpio;
	पूर्ण

	error = regulator_enable(ts->vccio);
	अगर (error) अणु
		regulator_disable(ts->avdd);
		dev_err(&ts->client->dev,
			"failed to enable vccio regulator: %d\n", error);
		जाओ release_reset_gpio;
	पूर्ण

	udelay(RM_POWERON_DELAY_USEC);

release_reset_gpio:
	gpiod_set_value_cansleep(ts->reset_gpio, 0);

	अगर (error)
		वापस error;

	msleep(RM_RESET_DELAY_MSEC);

	वापस 0;
पूर्ण

अटल व्योम raydium_i2c_घातer_off(व्योम *_data)
अणु
	काष्ठा raydium_data *ts = _data;

	अगर (ts->reset_gpio) अणु
		gpiod_set_value_cansleep(ts->reset_gpio, 1);
		regulator_disable(ts->vccio);
		regulator_disable(ts->avdd);
	पूर्ण
पूर्ण

अटल पूर्णांक raydium_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	जोड़ i2c_smbus_data dummy;
	काष्ठा raydium_data *ts;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev,
			"i2c check functionality error (need I2C_FUNC_I2C)\n");
		वापस -ENXIO;
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	mutex_init(&ts->sysfs_mutex);

	ts->client = client;
	i2c_set_clientdata(client, ts);

	ts->avdd = devm_regulator_get(&client->dev, "avdd");
	अगर (IS_ERR(ts->avdd)) अणु
		error = PTR_ERR(ts->avdd);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'avdd' regulator: %d\n", error);
		वापस error;
	पूर्ण

	ts->vccio = devm_regulator_get(&client->dev, "vccio");
	अगर (IS_ERR(ts->vccio)) अणु
		error = PTR_ERR(ts->vccio);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'vccio' regulator: %d\n", error);
		वापस error;
	पूर्ण

	ts->reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(ts->reset_gpio)) अणु
		error = PTR_ERR(ts->reset_gpio);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to get reset gpio: %d\n", error);
		वापस error;
	पूर्ण

	error = raydium_i2c_घातer_on(ts);
	अगर (error)
		वापस error;

	error = devm_add_action(&client->dev, raydium_i2c_घातer_off, ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to install power off action: %d\n", error);
		raydium_i2c_घातer_off(ts);
		वापस error;
	पूर्ण

	/* Make sure there is something at this address */
	अगर (i2c_smbus_xfer(client->adapter, client->addr, 0,
			   I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &dummy) < 0) अणु
		dev_err(&client->dev, "nothing at this address\n");
		वापस -ENXIO;
	पूर्ण

	error = raydium_i2c_initialize(ts);
	अगर (error) अणु
		dev_err(&client->dev, "failed to initialize: %d\n", error);
		वापस error;
	पूर्ण

	ts->report_data = devm_kदो_स्मृति(&client->dev,
				       ts->pkg_size, GFP_KERNEL);
	अगर (!ts->report_data)
		वापस -ENOMEM;

	ts->input = devm_input_allocate_device(&client->dev);
	अगर (!ts->input) अणु
		dev_err(&client->dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ts->input->name = "Raydium Touchscreen";
	ts->input->id.bustype = BUS_I2C;

	input_set_असल_params(ts->input, ABS_MT_POSITION_X,
			     0, le16_to_cpu(ts->info.x_max), 0, 0);
	input_set_असल_params(ts->input, ABS_MT_POSITION_Y,
			     0, le16_to_cpu(ts->info.y_max), 0, 0);
	input_असल_set_res(ts->input, ABS_MT_POSITION_X, ts->info.x_res);
	input_असल_set_res(ts->input, ABS_MT_POSITION_Y, ts->info.y_res);

	input_set_असल_params(ts->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(ts->input, ABS_MT_PRESSURE, 0, 255, 0, 0);

	error = input_mt_init_slots(ts->input, RM_MAX_TOUCH_NUM,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to initialize MT slots: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(ts->input);
	अगर (error) अणु
		dev_err(&client->dev,
			"unable to register input device: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, raydium_i2c_irq,
					  IRQF_ONESHOT, client->name, ts);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev,
				   &raydium_i2c_attribute_group);
	अगर (error) अणु
		dev_err(&client->dev, "failed to create sysfs attributes: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __maybe_unused raydium_enter_sleep(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 sleep_cmd[] = अणु 0x5A, 0xff, 0x00, 0x0f पूर्ण;
	पूर्णांक error;

	error = raydium_i2c_send(client, RM_CMD_ENTER_SLEEP,
				 sleep_cmd, माप(sleep_cmd));
	अगर (error)
		dev_err(&client->dev,
			"sleep command failed: %d\n", error);
पूर्ण

अटल पूर्णांक __maybe_unused raydium_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा raydium_data *ts = i2c_get_clientdata(client);

	/* Sleep is not available in BLDR recovery mode */
	अगर (ts->boot_mode != RAYDIUM_TS_MAIN)
		वापस -EBUSY;

	disable_irq(client->irq);

	अगर (device_may_wakeup(dev)) अणु
		raydium_enter_sleep(client);

		ts->wake_irq_enabled = (enable_irq_wake(client->irq) == 0);
	पूर्ण अन्यथा अणु
		raydium_i2c_घातer_off(ts);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused raydium_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा raydium_data *ts = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev)) अणु
		अगर (ts->wake_irq_enabled)
			disable_irq_wake(client->irq);
		raydium_i2c_sw_reset(client);
	पूर्ण अन्यथा अणु
		raydium_i2c_घातer_on(ts);
		raydium_i2c_initialize(ts);
	पूर्ण

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(raydium_i2c_pm_ops,
			 raydium_i2c_suspend, raydium_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id raydium_i2c_id[] = अणु
	अणु "raydium_i2c" , 0 पूर्ण,
	अणु "rm32380", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, raydium_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id raydium_acpi_id[] = अणु
	अणु "RAYD0001", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, raydium_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id raydium_of_match[] = अणु
	अणु .compatible = "raydium,rm32380", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, raydium_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver raydium_i2c_driver = अणु
	.probe = raydium_i2c_probe,
	.id_table = raydium_i2c_id,
	.driver = अणु
		.name = "raydium_ts",
		.pm = &raydium_i2c_pm_ops,
		.acpi_match_table = ACPI_PTR(raydium_acpi_id),
		.of_match_table = of_match_ptr(raydium_of_match),
	पूर्ण,
पूर्ण;
module_i2c_driver(raydium_i2c_driver);

MODULE_AUTHOR("Raydium");
MODULE_DESCRIPTION("Raydium I2c Touchscreen driver");
MODULE_LICENSE("GPL v2");
