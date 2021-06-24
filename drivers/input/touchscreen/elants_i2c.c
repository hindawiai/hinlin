<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Elan Microelectronics touch panels with I2C पूर्णांकerface
 *
 * Copyright (C) 2014 Elan Microelectronics Corporation.
 * Scott Liu <scott.liu@emc.com.tw>
 *
 * This code is partly based on hid-multitouch.c:
 *
 *  Copyright (c) 2010-2012 Stephane Chatty <chatty@enac.fr>
 *  Copyright (c) 2010-2012 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 *  Copyright (c) 2010-2012 Ecole Nationale de l'Aviation Civile, France
 *
 * This code is partly based on i2c-hid.c:
 *
 * Copyright (c) 2012 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 * Copyright (c) 2012 Ecole Nationale de l'Aviation Civile, France
 * Copyright (c) 2012 Red Hat, Inc
 */


#समावेश <linux/bits.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/async.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/uuid.h>
#समावेश <यंत्र/unaligned.h>

/* Device, Driver inक्रमmation */
#घोषणा DEVICE_NAME	"elants_i2c"

/* Convert from rows or columns पूर्णांकo resolution */
#घोषणा ELAN_TS_RESOLUTION(n, m)   (((n) - 1) * (m))

/* FW header data */
#घोषणा HEADER_SIZE		4
#घोषणा FW_HDR_TYPE		0
#घोषणा FW_HDR_COUNT		1
#घोषणा FW_HDR_LENGTH		2

/* Buffer mode Queue Header inक्रमmation */
#घोषणा QUEUE_HEADER_SINGLE	0x62
#घोषणा QUEUE_HEADER_NORMAL	0X63
#घोषणा QUEUE_HEADER_WAIT	0x64
#घोषणा QUEUE_HEADER_NORMAL2	0x66

/* Command header definition */
#घोषणा CMD_HEADER_WRITE	0x54
#घोषणा CMD_HEADER_READ		0x53
#घोषणा CMD_HEADER_6B_READ	0x5B
#घोषणा CMD_HEADER_ROM_READ	0x96
#घोषणा CMD_HEADER_RESP		0x52
#घोषणा CMD_HEADER_6B_RESP	0x9B
#घोषणा CMD_HEADER_ROM_RESP	0x95
#घोषणा CMD_HEADER_HELLO	0x55
#घोषणा CMD_HEADER_REK		0x66

/* FW position data */
#घोषणा PACKET_SIZE_OLD		40
#घोषणा PACKET_SIZE		55
#घोषणा MAX_CONTACT_NUM		10
#घोषणा FW_POS_HEADER		0
#घोषणा FW_POS_STATE		1
#घोषणा FW_POS_TOTAL		2
#घोषणा FW_POS_XY		3
#घोषणा FW_POS_TOOL_TYPE	33
#घोषणा FW_POS_CHECKSUM		34
#घोषणा FW_POS_WIDTH		35
#घोषणा FW_POS_PRESSURE		45

#घोषणा HEADER_REPORT_10_FINGER	0x62

/* Header (4 bytes) plus 3 full 10-finger packets */
#घोषणा MAX_PACKET_SIZE		169

#घोषणा BOOT_TIME_DELAY_MS	50

/* FW पढ़ो command, 0x53 0x?? 0x0, 0x01 */
#घोषणा E_ELAN_INFO_FW_VER	0x00
#घोषणा E_ELAN_INFO_BC_VER	0x10
#घोषणा E_ELAN_INFO_X_RES	0x60
#घोषणा E_ELAN_INFO_Y_RES	0x63
#घोषणा E_ELAN_INFO_REK		0xD0
#घोषणा E_ELAN_INFO_TEST_VER	0xE0
#घोषणा E_ELAN_INFO_FW_ID	0xF0
#घोषणा E_INFO_OSR		0xD6
#घोषणा E_INFO_PHY_SCAN		0xD7
#घोषणा E_INFO_PHY_DRIVER	0xD8

/* FW ग_लिखो command, 0x54 0x?? 0x0, 0x01 */
#घोषणा E_POWER_STATE_SLEEP	0x50
#घोषणा E_POWER_STATE_RESUME	0x58

#घोषणा MAX_RETRIES		3
#घोषणा MAX_FW_UPDATE_RETRIES	30

#घोषणा ELAN_FW_PAGESIZE	132

/* calibration समयout definition */
#घोषणा ELAN_CALI_TIMEOUT_MSEC	12000

#घोषणा ELAN_POWERON_DELAY_USEC	500
#घोषणा ELAN_RESET_DELAY_MSEC	20

क्रमागत elants_chip_id अणु
	EKTH3500,
	EKTF3624,
पूर्ण;

क्रमागत elants_state अणु
	ELAN_STATE_NORMAL,
	ELAN_WAIT_QUEUE_HEADER,
	ELAN_WAIT_RECALIBRATION,
पूर्ण;

क्रमागत elants_iap_mode अणु
	ELAN_IAP_OPERATIONAL,
	ELAN_IAP_RECOVERY,
पूर्ण;

/* काष्ठा elants_data - represents state of Elan touchscreen device */
काष्ठा elants_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;

	काष्ठा regulator *vcc33;
	काष्ठा regulator *vccio;
	काष्ठा gpio_desc *reset_gpio;

	u16 fw_version;
	u8 test_version;
	u8 solution_version;
	u8 bc_version;
	u8 iap_version;
	u16 hw_version;
	u8 major_res;
	अचिन्हित पूर्णांक x_res;	/* resolution in units/mm */
	अचिन्हित पूर्णांक y_res;
	अचिन्हित पूर्णांक x_max;
	अचिन्हित पूर्णांक y_max;
	अचिन्हित पूर्णांक phy_x;
	अचिन्हित पूर्णांक phy_y;
	काष्ठा touchscreen_properties prop;

	क्रमागत elants_state state;
	क्रमागत elants_chip_id chip_id;
	क्रमागत elants_iap_mode iap_mode;

	/* Guards against concurrent access to the device via sysfs */
	काष्ठा mutex sysfs_mutex;

	u8 cmd_resp[HEADER_SIZE];
	काष्ठा completion cmd_करोne;

	bool wake_irq_enabled;
	bool keep_घातer_in_suspend;

	/* Must be last to be used क्रम DMA operations */
	u8 buf[MAX_PACKET_SIZE] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक elants_i2c_send(काष्ठा i2c_client *client,
			   स्थिर व्योम *data, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = i2c_master_send(client, data, size);
	अगर (ret == size)
		वापस 0;

	अगर (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "%s failed (%*ph): %d\n",
		__func__, (पूर्णांक)size, data, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक elants_i2c_पढ़ो(काष्ठा i2c_client *client, व्योम *data, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = i2c_master_recv(client, data, size);
	अगर (ret == size)
		वापस 0;

	अगर (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "%s failed: %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक elants_i2c_execute_command(काष्ठा i2c_client *client,
				      स्थिर u8 *cmd, माप_प्रकार cmd_size,
				      u8 *resp, माप_प्रकार resp_size,
				      पूर्णांक retries, स्थिर अक्षर *cmd_name)
अणु
	काष्ठा i2c_msg msgs[2];
	पूर्णांक ret;
	u8 expected_response;

	चयन (cmd[0]) अणु
	हाल CMD_HEADER_READ:
		expected_response = CMD_HEADER_RESP;
		अवरोध;

	हाल CMD_HEADER_6B_READ:
		expected_response = CMD_HEADER_6B_RESP;
		अवरोध;

	हाल CMD_HEADER_ROM_READ:
		expected_response = CMD_HEADER_ROM_RESP;
		अवरोध;

	शेष:
		dev_err(&client->dev, "(%s): invalid command: %*ph\n",
			cmd_name, (पूर्णांक)cmd_size, cmd);
		वापस -EINVAL;
	पूर्ण

	क्रम (;;) अणु
		msgs[0].addr = client->addr;
		msgs[0].flags = client->flags & I2C_M_TEN;
		msgs[0].len = cmd_size;
		msgs[0].buf = (u8 *)cmd;

		msgs[1].addr = client->addr;
		msgs[1].flags = (client->flags & I2C_M_TEN) | I2C_M_RD;
		msgs[1].flags |= I2C_M_RD;
		msgs[1].len = resp_size;
		msgs[1].buf = resp;

		ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
		अगर (ret < 0) अणु
			अगर (--retries > 0) अणु
				dev_dbg(&client->dev,
					"(%s) I2C transfer failed: %pe (retrying)\n",
					cmd_name, ERR_PTR(ret));
				जारी;
			पूर्ण

			dev_err(&client->dev,
				"(%s) I2C transfer failed: %pe\n",
				cmd_name, ERR_PTR(ret));
			वापस ret;
		पूर्ण

		अगर (ret != ARRAY_SIZE(msgs) ||
		    resp[FW_HDR_TYPE] != expected_response) अणु
			अगर (--retries > 0) अणु
				dev_dbg(&client->dev,
					"(%s) unexpected response: %*ph (retrying)\n",
					cmd_name, ret, resp);
				जारी;
			पूर्ण

			dev_err(&client->dev,
				"(%s) unexpected response: %*ph\n",
				cmd_name, ret, resp);
			वापस -EIO;
		पूर्ण

		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक elants_i2c_calibrate(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret, error;
	अटल स्थिर u8 w_flashkey[] = अणु CMD_HEADER_WRITE, 0xC0, 0xE1, 0x5A पूर्ण;
	अटल स्थिर u8 rek[] = अणु CMD_HEADER_WRITE, 0x29, 0x00, 0x01 पूर्ण;
	अटल स्थिर u8 rek_resp[] = अणु CMD_HEADER_REK, 0x66, 0x66, 0x66 पूर्ण;

	disable_irq(client->irq);

	ts->state = ELAN_WAIT_RECALIBRATION;
	reinit_completion(&ts->cmd_करोne);

	elants_i2c_send(client, w_flashkey, माप(w_flashkey));
	elants_i2c_send(client, rek, माप(rek));

	enable_irq(client->irq);

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ts->cmd_करोne,
				msecs_to_jअगरfies(ELAN_CALI_TIMEOUT_MSEC));

	ts->state = ELAN_STATE_NORMAL;

	अगर (ret <= 0) अणु
		error = ret < 0 ? ret : -ETIMEDOUT;
		dev_err(&client->dev,
			"error while waiting for calibration to complete: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर (स_भेद(rek_resp, ts->cmd_resp, माप(rek_resp))) अणु
		dev_err(&client->dev,
			"unexpected calibration response: %*ph\n",
			(पूर्णांक)माप(ts->cmd_resp), ts->cmd_resp);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_sw_reset(काष्ठा i2c_client *client)
अणु
	स्थिर u8 soft_rst_cmd[] = अणु 0x77, 0x77, 0x77, 0x77 पूर्ण;
	पूर्णांक error;

	error = elants_i2c_send(client, soft_rst_cmd,
				माप(soft_rst_cmd));
	अगर (error) अणु
		dev_err(&client->dev, "software reset failed: %d\n", error);
		वापस error;
	पूर्ण

	/*
	 * We should रुको at least 10 msec (but no more than 40) beक्रमe
	 * sending fastboot or IAP command to the device.
	 */
	msleep(30);

	वापस 0;
पूर्ण

अटल u16 elants_i2c_parse_version(u8 *buf)
अणु
	वापस get_unaligned_be32(buf) >> 4;
पूर्ण

अटल पूर्णांक elants_i2c_query_hw_version(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक retry_cnt = MAX_RETRIES;
	स्थिर u8 cmd[] = अणु CMD_HEADER_READ, E_ELAN_INFO_FW_ID, 0x00, 0x01 पूर्ण;
	u8 resp[HEADER_SIZE];
	पूर्णांक error;

	जबतक (retry_cnt--) अणु
		error = elants_i2c_execute_command(client, cmd, माप(cmd),
						   resp, माप(resp), 1,
						   "read fw id");
		अगर (error)
			वापस error;

		ts->hw_version = elants_i2c_parse_version(resp);
		अगर (ts->hw_version != 0xffff)
			वापस 0;
	पूर्ण

	dev_err(&client->dev, "Invalid fw id: %#04x\n", ts->hw_version);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक elants_i2c_query_fw_version(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक retry_cnt = MAX_RETRIES;
	स्थिर u8 cmd[] = अणु CMD_HEADER_READ, E_ELAN_INFO_FW_VER, 0x00, 0x01 पूर्ण;
	u8 resp[HEADER_SIZE];
	पूर्णांक error;

	जबतक (retry_cnt--) अणु
		error = elants_i2c_execute_command(client, cmd, माप(cmd),
						   resp, माप(resp), 1,
						   "read fw version");
		अगर (error)
			वापस error;

		ts->fw_version = elants_i2c_parse_version(resp);
		अगर (ts->fw_version != 0x0000 && ts->fw_version != 0xffff)
			वापस 0;

		dev_dbg(&client->dev, "(read fw version) resp %*phC\n",
			(पूर्णांक)माप(resp), resp);
	पूर्ण

	dev_err(&client->dev, "Invalid fw ver: %#04x\n", ts->fw_version);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक elants_i2c_query_test_version(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error;
	u16 version;
	स्थिर u8 cmd[] = अणु CMD_HEADER_READ, E_ELAN_INFO_TEST_VER, 0x00, 0x01 पूर्ण;
	u8 resp[HEADER_SIZE];

	error = elants_i2c_execute_command(client, cmd, माप(cmd),
					   resp, माप(resp), MAX_RETRIES,
					   "read test version");
	अगर (error) अणु
		dev_err(&client->dev, "Failed to read test version\n");
		वापस error;
	पूर्ण

	version = elants_i2c_parse_version(resp);
	ts->test_version = version >> 8;
	ts->solution_version = version & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_query_bc_version(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर u8 cmd[] = अणु CMD_HEADER_READ, E_ELAN_INFO_BC_VER, 0x00, 0x01 पूर्ण;
	u8 resp[HEADER_SIZE];
	u16 version;
	पूर्णांक error;

	error = elants_i2c_execute_command(client, cmd, माप(cmd),
					   resp, माप(resp), 1,
					   "read BC version");
	अगर (error)
		वापस error;

	version = elants_i2c_parse_version(resp);
	ts->bc_version = version >> 8;
	ts->iap_version = version & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_query_ts_info_ektf(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error;
	u8 resp[4];
	u16 phy_x, phy_y;
	स्थिर u8 get_xres_cmd[] = अणु
		CMD_HEADER_READ, E_ELAN_INFO_X_RES, 0x00, 0x00
	पूर्ण;
	स्थिर u8 get_yres_cmd[] = अणु
		CMD_HEADER_READ, E_ELAN_INFO_Y_RES, 0x00, 0x00
	पूर्ण;

	/* Get X/Y size in mm */
	error = elants_i2c_execute_command(client, get_xres_cmd,
					   माप(get_xres_cmd),
					   resp, माप(resp), 1,
					   "get X size");
	अगर (error)
		वापस error;

	phy_x = resp[2] | ((resp[3] & 0xF0) << 4);

	error = elants_i2c_execute_command(client, get_yres_cmd,
					   माप(get_yres_cmd),
					   resp, माप(resp), 1,
					   "get Y size");
	अगर (error)
		वापस error;

	phy_y = resp[2] | ((resp[3] & 0xF0) << 4);

	dev_dbg(&client->dev, "phy_x=%d, phy_y=%d\n", phy_x, phy_y);

	ts->phy_x = phy_x;
	ts->phy_y = phy_y;

	/* eKTF करोesn't report max size, set it to शेष values */
	ts->x_max = 2240 - 1;
	ts->y_max = 1408 - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_query_ts_info_ekth(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error;
	u8 resp[17];
	u16 phy_x, phy_y, rows, cols, osr;
	स्थिर u8 get_resolution_cmd[] = अणु
		CMD_HEADER_6B_READ, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	स्थिर u8 get_osr_cmd[] = अणु
		CMD_HEADER_READ, E_INFO_OSR, 0x00, 0x01
	पूर्ण;
	स्थिर u8 get_physical_scan_cmd[] = अणु
		CMD_HEADER_READ, E_INFO_PHY_SCAN, 0x00, 0x01
	पूर्ण;
	स्थिर u8 get_physical_drive_cmd[] = अणु
		CMD_HEADER_READ, E_INFO_PHY_DRIVER, 0x00, 0x01
	पूर्ण;

	/* Get trace number */
	error = elants_i2c_execute_command(client,
					   get_resolution_cmd,
					   माप(get_resolution_cmd),
					   resp, माप(resp), 1,
					   "get resolution");
	अगर (error)
		वापस error;

	rows = resp[2] + resp[6] + resp[10];
	cols = resp[3] + resp[7] + resp[11];

	/* Get report resolution value of ABS_MT_TOUCH_MAJOR */
	ts->major_res = resp[16];

	/* Process mm_to_pixel inक्रमmation */
	error = elants_i2c_execute_command(client,
					   get_osr_cmd, माप(get_osr_cmd),
					   resp, माप(resp), 1, "get osr");
	अगर (error)
		वापस error;

	osr = resp[3];

	error = elants_i2c_execute_command(client,
					   get_physical_scan_cmd,
					   माप(get_physical_scan_cmd),
					   resp, माप(resp), 1,
					   "get physical scan");
	अगर (error)
		वापस error;

	phy_x = get_unaligned_be16(&resp[2]);

	error = elants_i2c_execute_command(client,
					   get_physical_drive_cmd,
					   माप(get_physical_drive_cmd),
					   resp, माप(resp), 1,
					   "get physical drive");
	अगर (error)
		वापस error;

	phy_y = get_unaligned_be16(&resp[2]);

	dev_dbg(&client->dev, "phy_x=%d, phy_y=%d\n", phy_x, phy_y);

	अगर (rows == 0 || cols == 0 || osr == 0) अणु
		dev_warn(&client->dev,
			 "invalid trace number data: %d, %d, %d\n",
			 rows, cols, osr);
	पूर्ण अन्यथा अणु
		/* translate trace number to TS resolution */
		ts->x_max = ELAN_TS_RESOLUTION(rows, osr);
		ts->x_res = DIV_ROUND_CLOSEST(ts->x_max, phy_x);
		ts->y_max = ELAN_TS_RESOLUTION(cols, osr);
		ts->y_res = DIV_ROUND_CLOSEST(ts->y_max, phy_y);
		ts->phy_x = phy_x;
		ts->phy_y = phy_y;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_fastboot(काष्ठा i2c_client *client)
अणु
	स्थिर u8 boot_cmd[] = अणु 0x4D, 0x61, 0x69, 0x6E पूर्ण;
	पूर्णांक error;

	error = elants_i2c_send(client, boot_cmd, माप(boot_cmd));
	अगर (error) अणु
		dev_err(&client->dev, "boot failed: %d\n", error);
		वापस error;
	पूर्ण

	dev_dbg(&client->dev, "boot success -- 0x%x\n", client->addr);
	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_initialize(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error, error2, retry_cnt;
	स्थिर u8 hello_packet[] = अणु 0x55, 0x55, 0x55, 0x55 पूर्ण;
	स्थिर u8 recov_packet[] = अणु 0x55, 0x55, 0x80, 0x80 पूर्ण;
	u8 buf[HEADER_SIZE];

	क्रम (retry_cnt = 0; retry_cnt < MAX_RETRIES; retry_cnt++) अणु
		error = elants_i2c_sw_reset(client);
		अगर (error) अणु
			/* Continue initializing अगर it's the last try */
			अगर (retry_cnt < MAX_RETRIES - 1)
				जारी;
		पूर्ण

		error = elants_i2c_fastboot(client);
		अगर (error) अणु
			/* Continue initializing अगर it's the last try */
			अगर (retry_cnt < MAX_RETRIES - 1)
				जारी;
		पूर्ण

		/* Wait क्रम Hello packet */
		msleep(BOOT_TIME_DELAY_MS);

		error = elants_i2c_पढ़ो(client, buf, माप(buf));
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to read 'hello' packet: %d\n", error);
		पूर्ण अन्यथा अगर (!स_भेद(buf, hello_packet, माप(hello_packet))) अणु
			ts->iap_mode = ELAN_IAP_OPERATIONAL;
			अवरोध;
		पूर्ण अन्यथा अगर (!स_भेद(buf, recov_packet, माप(recov_packet))) अणु
			/*
			 * Setting error code will mark device
			 * in recovery mode below.
			 */
			error = -EIO;
			अवरोध;
		पूर्ण अन्यथा अणु
			error = -EINVAL;
			dev_err(&client->dev,
				"invalid 'hello' packet: %*ph\n",
				(पूर्णांक)माप(buf), buf);
		पूर्ण
	पूर्ण

	/* hw version is available even अगर device in recovery state */
	error2 = elants_i2c_query_hw_version(ts);
	अगर (!error2)
		error2 = elants_i2c_query_bc_version(ts);
	अगर (!error)
		error = error2;

	अगर (!error)
		error = elants_i2c_query_fw_version(ts);
	अगर (!error)
		error = elants_i2c_query_test_version(ts);

	चयन (ts->chip_id) अणु
	हाल EKTH3500:
		अगर (!error)
			error = elants_i2c_query_ts_info_ekth(ts);
		अवरोध;
	हाल EKTF3624:
		अगर (!error)
			error = elants_i2c_query_ts_info_ektf(ts);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (error)
		ts->iap_mode = ELAN_IAP_RECOVERY;

	वापस 0;
पूर्ण

/*
 * Firmware update पूर्णांकerface.
 */

अटल पूर्णांक elants_i2c_fw_ग_लिखो_page(काष्ठा i2c_client *client,
				    स्थिर व्योम *page)
अणु
	स्थिर u8 ack_ok[] = अणु 0xaa, 0xaa पूर्ण;
	u8 buf[2];
	पूर्णांक retry;
	पूर्णांक error;

	क्रम (retry = 0; retry < MAX_FW_UPDATE_RETRIES; retry++) अणु
		error = elants_i2c_send(client, page, ELAN_FW_PAGESIZE);
		अगर (error) अणु
			dev_err(&client->dev,
				"IAP Write Page failed: %d\n", error);
			जारी;
		पूर्ण

		error = elants_i2c_पढ़ो(client, buf, 2);
		अगर (error) अणु
			dev_err(&client->dev,
				"IAP Ack read failed: %d\n", error);
			वापस error;
		पूर्ण

		अगर (!स_भेद(buf, ack_ok, माप(ack_ok)))
			वापस 0;

		error = -EIO;
		dev_err(&client->dev,
			"IAP Get Ack Error [%02x:%02x]\n",
			buf[0], buf[1]);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक elants_i2c_validate_remark_id(काष्ठा elants_data *ts,
					 स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error;
	स्थिर u8 cmd[] = अणु CMD_HEADER_ROM_READ, 0x80, 0x1F, 0x00, 0x00, 0x21 पूर्ण;
	u8 resp[6] = अणु 0 पूर्ण;
	u16 ts_remark_id = 0;
	u16 fw_remark_id = 0;

	/* Compare TS Remark ID and FW Remark ID */
	error = elants_i2c_execute_command(client, cmd, माप(cmd),
					   resp, माप(resp),
					   1, "read Remark ID");
	अगर (error)
		वापस error;

	ts_remark_id = get_unaligned_be16(&resp[3]);

	fw_remark_id = get_unaligned_le16(&fw->data[fw->size - 4]);

	अगर (fw_remark_id != ts_remark_id) अणु
		dev_err(&client->dev,
			"Remark ID Mismatched: ts_remark_id=0x%04x, fw_remark_id=0x%04x.\n",
			ts_remark_id, fw_remark_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_करो_update_firmware(काष्ठा i2c_client *client,
					 स्थिर काष्ठा firmware *fw,
					 bool क्रमce)
अणु
	काष्ठा elants_data *ts = i2c_get_clientdata(client);
	स्थिर u8 enter_iap[] = अणु 0x45, 0x49, 0x41, 0x50 पूर्ण;
	स्थिर u8 enter_iap2[] = अणु 0x54, 0x00, 0x12, 0x34 पूर्ण;
	स्थिर u8 iap_ack[] = अणु 0x55, 0xaa, 0x33, 0xcc पूर्ण;
	स्थिर u8 बंद_idle[] = अणु 0x54, 0x2c, 0x01, 0x01 पूर्ण;
	u8 buf[HEADER_SIZE];
	u16 send_id;
	पूर्णांक page, n_fw_pages;
	पूर्णांक error;
	bool check_remark_id = ts->iap_version >= 0x60;

	/* Recovery mode detection! */
	अगर (क्रमce) अणु
		dev_dbg(&client->dev, "Recovery mode procedure\n");

		अगर (check_remark_id) अणु
			error = elants_i2c_validate_remark_id(ts, fw);
			अगर (error)
				वापस error;
		पूर्ण

		error = elants_i2c_send(client, enter_iap2, माप(enter_iap2));
		अगर (error) अणु
			dev_err(&client->dev, "failed to enter IAP mode: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Start IAP Procedure */
		dev_dbg(&client->dev, "Normal IAP procedure\n");

		/* Close idle mode */
		error = elants_i2c_send(client, बंद_idle, माप(बंद_idle));
		अगर (error)
			dev_err(&client->dev, "Failed close idle: %d\n", error);
		msleep(60);

		elants_i2c_sw_reset(client);
		msleep(20);

		अगर (check_remark_id) अणु
			error = elants_i2c_validate_remark_id(ts, fw);
			अगर (error)
				वापस error;
		पूर्ण

		error = elants_i2c_send(client, enter_iap, माप(enter_iap));
		अगर (error) अणु
			dev_err(&client->dev, "failed to enter IAP mode: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	msleep(20);

	/* check IAP state */
	error = elants_i2c_पढ़ो(client, buf, 4);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to read IAP acknowledgement: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर (स_भेद(buf, iap_ack, माप(iap_ack))) अणु
		dev_err(&client->dev,
			"failed to enter IAP: %*ph (expected %*ph)\n",
			(पूर्णांक)माप(buf), buf, (पूर्णांक)माप(iap_ack), iap_ack);
		वापस -EIO;
	पूर्ण

	dev_info(&client->dev, "successfully entered IAP mode");

	send_id = client->addr;
	error = elants_i2c_send(client, &send_id, 1);
	अगर (error) अणु
		dev_err(&client->dev, "sending dummy byte failed: %d\n",
			error);
		वापस error;
	पूर्ण

	/* Clear the last page of Master */
	error = elants_i2c_send(client, fw->data, ELAN_FW_PAGESIZE);
	अगर (error) अणु
		dev_err(&client->dev, "clearing of the last page failed: %d\n",
			error);
		वापस error;
	पूर्ण

	error = elants_i2c_पढ़ो(client, buf, 2);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to read ACK for clearing the last page: %d\n",
			error);
		वापस error;
	पूर्ण

	n_fw_pages = fw->size / ELAN_FW_PAGESIZE;
	dev_dbg(&client->dev, "IAP Pages = %d\n", n_fw_pages);

	क्रम (page = 0; page < n_fw_pages; page++) अणु
		error = elants_i2c_fw_ग_लिखो_page(client,
					fw->data + page * ELAN_FW_PAGESIZE);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to write FW page %d: %d\n",
				page, error);
			वापस error;
		पूर्ण
	पूर्ण

	/* Old iap needs to रुको 200ms क्रम WDT and rest is क्रम hello packets */
	msleep(300);

	dev_info(&client->dev, "firmware update completed\n");
	वापस 0;
पूर्ण

अटल पूर्णांक elants_i2c_fw_update(काष्ठा elants_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर काष्ठा firmware *fw;
	अक्षर *fw_name;
	पूर्णांक error;

	fw_name = kaप्र_लिखो(GFP_KERNEL, "elants_i2c_%04x.bin", ts->hw_version);
	अगर (!fw_name)
		वापस -ENOMEM;

	dev_info(&client->dev, "requesting fw name = %s\n", fw_name);
	error = request_firmware(&fw, fw_name, &client->dev);
	kमुक्त(fw_name);
	अगर (error) अणु
		dev_err(&client->dev, "failed to request firmware: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर (fw->size % ELAN_FW_PAGESIZE) अणु
		dev_err(&client->dev, "invalid firmware length: %zu\n",
			fw->size);
		error = -EINVAL;
		जाओ out;
	पूर्ण

	disable_irq(client->irq);

	error = elants_i2c_करो_update_firmware(client, fw,
					ts->iap_mode == ELAN_IAP_RECOVERY);
	अगर (error) अणु
		dev_err(&client->dev, "firmware update failed: %d\n", error);
		ts->iap_mode = ELAN_IAP_RECOVERY;
		जाओ out_enable_irq;
	पूर्ण

	error = elants_i2c_initialize(ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to initialize device after firmware update: %d\n",
			error);
		ts->iap_mode = ELAN_IAP_RECOVERY;
		जाओ out_enable_irq;
	पूर्ण

	ts->iap_mode = ELAN_IAP_OPERATIONAL;

out_enable_irq:
	ts->state = ELAN_STATE_NORMAL;
	enable_irq(client->irq);
	msleep(100);

	अगर (!error)
		elants_i2c_calibrate(ts);
out:
	release_firmware(fw);
	वापस error;
पूर्ण

/*
 * Event reporting.
 */

अटल व्योम elants_i2c_mt_event(काष्ठा elants_data *ts, u8 *buf,
				माप_प्रकार packet_size)
अणु
	काष्ठा input_dev *input = ts->input;
	अचिन्हित पूर्णांक n_fingers;
	अचिन्हित पूर्णांक tool_type;
	u16 finger_state;
	पूर्णांक i;

	n_fingers = buf[FW_POS_STATE + 1] & 0x0f;
	finger_state = ((buf[FW_POS_STATE + 1] & 0x30) << 4) |
			buf[FW_POS_STATE];

	dev_dbg(&ts->client->dev,
		"n_fingers: %u, state: %04x\n",  n_fingers, finger_state);

	/* Note: all fingers have the same tool type */
	tool_type = buf[FW_POS_TOOL_TYPE] & BIT(0) ?
			MT_TOOL_FINGER : MT_TOOL_PALM;

	क्रम (i = 0; i < MAX_CONTACT_NUM && n_fingers; i++) अणु
		अगर (finger_state & 1) अणु
			अचिन्हित पूर्णांक x, y, p, w;
			u8 *pos;

			pos = &buf[FW_POS_XY + i * 3];
			x = (((u16)pos[0] & 0xf0) << 4) | pos[1];
			y = (((u16)pos[0] & 0x0f) << 8) | pos[2];

			/*
			 * eKTF3624 may have use "old" touch-report क्रमmat,
			 * depending on a device and TS firmware version.
			 * For example, ASUS Transक्रमmer devices use the "old"
			 * क्रमmat, जबतक ASUS Nexus 7 uses the "new" क्रमmant.
			 */
			अगर (packet_size == PACKET_SIZE_OLD &&
			    ts->chip_id == EKTF3624) अणु
				w = buf[FW_POS_WIDTH + i / 2];
				w >>= 4 * (~i & 1);
				w |= w << 4;
				w |= !w;
				p = w;
			पूर्ण अन्यथा अणु
				p = buf[FW_POS_PRESSURE + i];
				w = buf[FW_POS_WIDTH + i];
			पूर्ण

			dev_dbg(&ts->client->dev, "i=%d x=%d y=%d p=%d w=%d\n",
				i, x, y, p, w);

			input_mt_slot(input, i);
			input_mt_report_slot_state(input, tool_type, true);
			touchscreen_report_pos(input, &ts->prop, x, y, true);
			input_event(input, EV_ABS, ABS_MT_PRESSURE, p);
			input_event(input, EV_ABS, ABS_MT_TOUCH_MAJOR, w);

			n_fingers--;
		पूर्ण

		finger_state >>= 1;
	पूर्ण

	input_mt_sync_frame(input);
	input_sync(input);
पूर्ण

अटल u8 elants_i2c_calculate_checksum(u8 *buf)
अणु
	u8 checksum = 0;
	u8 i;

	क्रम (i = 0; i < FW_POS_CHECKSUM; i++)
		checksum += buf[i];

	वापस checksum;
पूर्ण

अटल व्योम elants_i2c_event(काष्ठा elants_data *ts, u8 *buf,
			     माप_प्रकार packet_size)
अणु
	u8 checksum = elants_i2c_calculate_checksum(buf);

	अगर (unlikely(buf[FW_POS_CHECKSUM] != checksum))
		dev_warn(&ts->client->dev,
			 "%s: invalid checksum for packet %02x: %02x vs. %02x\n",
			 __func__, buf[FW_POS_HEADER],
			 checksum, buf[FW_POS_CHECKSUM]);
	अन्यथा अगर (unlikely(buf[FW_POS_HEADER] != HEADER_REPORT_10_FINGER))
		dev_warn(&ts->client->dev,
			 "%s: unknown packet type: %02x\n",
			 __func__, buf[FW_POS_HEADER]);
	अन्यथा
		elants_i2c_mt_event(ts, buf, packet_size);
पूर्ण

अटल irqवापस_t elants_i2c_irq(पूर्णांक irq, व्योम *_dev)
अणु
	स्थिर u8 रुको_packet[] = अणु 0x64, 0x64, 0x64, 0x64 पूर्ण;
	काष्ठा elants_data *ts = _dev;
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक report_count, report_len;
	पूर्णांक i;
	पूर्णांक len;

	len = i2c_master_recv_dmasafe(client, ts->buf, माप(ts->buf));
	अगर (len < 0) अणु
		dev_err(&client->dev, "%s: failed to read data: %d\n",
			__func__, len);
		जाओ out;
	पूर्ण

	dev_dbg(&client->dev, "%s: packet %*ph\n",
		__func__, HEADER_SIZE, ts->buf);

	चयन (ts->state) अणु
	हाल ELAN_WAIT_RECALIBRATION:
		अगर (ts->buf[FW_HDR_TYPE] == CMD_HEADER_REK) अणु
			स_नकल(ts->cmd_resp, ts->buf, माप(ts->cmd_resp));
			complete(&ts->cmd_करोne);
			ts->state = ELAN_STATE_NORMAL;
		पूर्ण
		अवरोध;

	हाल ELAN_WAIT_QUEUE_HEADER:
		अगर (ts->buf[FW_HDR_TYPE] != QUEUE_HEADER_NORMAL)
			अवरोध;

		ts->state = ELAN_STATE_NORMAL;
		fallthrough;

	हाल ELAN_STATE_NORMAL:

		चयन (ts->buf[FW_HDR_TYPE]) अणु
		हाल CMD_HEADER_HELLO:
		हाल CMD_HEADER_RESP:
			अवरोध;

		हाल QUEUE_HEADER_WAIT:
			अगर (स_भेद(ts->buf, रुको_packet, माप(रुको_packet))) अणु
				dev_err(&client->dev,
					"invalid wait packet %*ph\n",
					HEADER_SIZE, ts->buf);
			पूर्ण अन्यथा अणु
				ts->state = ELAN_WAIT_QUEUE_HEADER;
				udelay(30);
			पूर्ण
			अवरोध;

		हाल QUEUE_HEADER_SINGLE:
			elants_i2c_event(ts, &ts->buf[HEADER_SIZE],
					 ts->buf[FW_HDR_LENGTH]);
			अवरोध;

		हाल QUEUE_HEADER_NORMAL2: /* CMD_HEADER_REK */
			/*
			 * Depending on firmware version, eKTF3624 touchscreens
			 * may utilize one of these opcodes क्रम the touch events:
			 * 0x63 (NORMAL) and 0x66 (NORMAL2).  The 0x63 is used by
			 * older firmware version and dअगरfers from 0x66 such that
			 * touch pressure value needs to be adjusted.  The 0x66
			 * opcode of newer firmware is equal to 0x63 of eKTH3500.
			 */
			अगर (ts->chip_id != EKTF3624)
				अवरोध;

			fallthrough;

		हाल QUEUE_HEADER_NORMAL:
			report_count = ts->buf[FW_HDR_COUNT];
			अगर (report_count == 0 || report_count > 3) अणु
				dev_err(&client->dev,
					"bad report count: %*ph\n",
					HEADER_SIZE, ts->buf);
				अवरोध;
			पूर्ण

			report_len = ts->buf[FW_HDR_LENGTH] / report_count;

			अगर (report_len == PACKET_SIZE_OLD &&
			    ts->chip_id == EKTF3624) अणु
				dev_dbg_once(&client->dev,
					     "using old report format\n");
			पूर्ण अन्यथा अगर (report_len != PACKET_SIZE) अणु
				dev_err(&client->dev,
					"mismatching report length: %*ph\n",
					HEADER_SIZE, ts->buf);
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < report_count; i++) अणु
				u8 *buf = ts->buf + HEADER_SIZE +
							i * report_len;
				elants_i2c_event(ts, buf, report_len);
			पूर्ण
			अवरोध;

		शेष:
			dev_err(&client->dev, "unknown packet %*ph\n",
				HEADER_SIZE, ts->buf);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * sysfs पूर्णांकerface
 */
अटल sमाप_प्रकार calibrate_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elants_data *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&ts->sysfs_mutex);
	अगर (error)
		वापस error;

	error = elants_i2c_calibrate(ts);

	mutex_unlock(&ts->sysfs_mutex);
	वापस error ?: count;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_update_fw(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elants_data *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&ts->sysfs_mutex);
	अगर (error)
		वापस error;

	error = elants_i2c_fw_update(ts);
	dev_dbg(dev, "firmware update result: %d\n", error);

	mutex_unlock(&ts->sysfs_mutex);
	वापस error ?: count;
पूर्ण

अटल sमाप_प्रकार show_iap_mode(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elants_data *ts = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%s\n",
		       ts->iap_mode == ELAN_IAP_OPERATIONAL ?
				"Normal" : "Recovery");
पूर्ण

अटल sमाप_प्रकार show_calibration_count(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	स्थिर u8 cmd[] = अणु CMD_HEADER_READ, E_ELAN_INFO_REK, 0x00, 0x01 पूर्ण;
	u8 resp[HEADER_SIZE];
	u16 rek_count;
	पूर्णांक error;

	error = elants_i2c_execute_command(client, cmd, माप(cmd),
					   resp, माप(resp), 1,
					   "read ReK status");
	अगर (error)
		वापस प्र_लिखो(buf, "%d\n", error);

	rek_count = get_unaligned_be16(&resp[2]);
	वापस प्र_लिखो(buf, "0x%04x\n", rek_count);
पूर्ण

अटल DEVICE_ATTR_WO(calibrate);
अटल DEVICE_ATTR(iap_mode, S_IRUGO, show_iap_mode, शून्य);
अटल DEVICE_ATTR(calibration_count, S_IRUGO, show_calibration_count, शून्य);
अटल DEVICE_ATTR(update_fw, S_IWUSR, शून्य, ग_लिखो_update_fw);

काष्ठा elants_version_attribute अणु
	काष्ठा device_attribute dattr;
	माप_प्रकार field_offset;
	माप_प्रकार field_size;
पूर्ण;

#घोषणा __ELANTS_FIELD_SIZE(_field)					\
	माप(((काष्ठा elants_data *)शून्य)->_field)
#घोषणा __ELANTS_VERIFY_SIZE(_field)					\
	(BUILD_BUG_ON_ZERO(__ELANTS_FIELD_SIZE(_field) > 2) +		\
	 __ELANTS_FIELD_SIZE(_field))
#घोषणा ELANTS_VERSION_ATTR(_field)					\
	काष्ठा elants_version_attribute elants_ver_attr_##_field = अणु	\
		.dattr = __ATTR(_field, S_IRUGO,			\
				elants_version_attribute_show, शून्य),	\
		.field_offset = दुरत्व(काष्ठा elants_data, _field),	\
		.field_size = __ELANTS_VERIFY_SIZE(_field),		\
	पूर्ण

अटल sमाप_प्रकार elants_version_attribute_show(काष्ठा device *dev,
					     काष्ठा device_attribute *dattr,
					     अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elants_data *ts = i2c_get_clientdata(client);
	काष्ठा elants_version_attribute *attr =
		container_of(dattr, काष्ठा elants_version_attribute, dattr);
	u8 *field = (u8 *)((अक्षर *)ts + attr->field_offset);
	अचिन्हित पूर्णांक fmt_size;
	अचिन्हित पूर्णांक val;

	अगर (attr->field_size == 1) अणु
		val = *field;
		fmt_size = 2; /* 2 HEX digits */
	पूर्ण अन्यथा अणु
		val = *(u16 *)field;
		fmt_size = 4; /* 4 HEX digits */
	पूर्ण

	वापस प्र_लिखो(buf, "%0*x\n", fmt_size, val);
पूर्ण

अटल ELANTS_VERSION_ATTR(fw_version);
अटल ELANTS_VERSION_ATTR(hw_version);
अटल ELANTS_VERSION_ATTR(test_version);
अटल ELANTS_VERSION_ATTR(solution_version);
अटल ELANTS_VERSION_ATTR(bc_version);
अटल ELANTS_VERSION_ATTR(iap_version);

अटल काष्ठा attribute *elants_attributes[] = अणु
	&dev_attr_calibrate.attr,
	&dev_attr_update_fw.attr,
	&dev_attr_iap_mode.attr,
	&dev_attr_calibration_count.attr,

	&elants_ver_attr_fw_version.dattr.attr,
	&elants_ver_attr_hw_version.dattr.attr,
	&elants_ver_attr_test_version.dattr.attr,
	&elants_ver_attr_solution_version.dattr.attr,
	&elants_ver_attr_bc_version.dattr.attr,
	&elants_ver_attr_iap_version.dattr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group elants_attribute_group = अणु
	.attrs = elants_attributes,
पूर्ण;

अटल पूर्णांक elants_i2c_घातer_on(काष्ठा elants_data *ts)
अणु
	पूर्णांक error;

	/*
	 * If we करो not have reset gpio assume platक्रमm firmware
	 * controls regulators and करोes घातer them on क्रम us.
	 */
	अगर (IS_ERR_OR_शून्य(ts->reset_gpio))
		वापस 0;

	gpiod_set_value_cansleep(ts->reset_gpio, 1);

	error = regulator_enable(ts->vcc33);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"failed to enable vcc33 regulator: %d\n",
			error);
		जाओ release_reset_gpio;
	पूर्ण

	error = regulator_enable(ts->vccio);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"failed to enable vccio regulator: %d\n",
			error);
		regulator_disable(ts->vcc33);
		जाओ release_reset_gpio;
	पूर्ण

	/*
	 * We need to रुको a bit after घातering on controller beक्रमe
	 * we are allowed to release reset GPIO.
	 */
	udelay(ELAN_POWERON_DELAY_USEC);

release_reset_gpio:
	gpiod_set_value_cansleep(ts->reset_gpio, 0);
	अगर (error)
		वापस error;

	msleep(ELAN_RESET_DELAY_MSEC);

	वापस 0;
पूर्ण

अटल व्योम elants_i2c_घातer_off(व्योम *_data)
अणु
	काष्ठा elants_data *ts = _data;

	अगर (!IS_ERR_OR_शून्य(ts->reset_gpio)) अणु
		/*
		 * Activate reset gpio to prevent leakage through the
		 * pin once we shut off घातer to the controller.
		 */
		gpiod_set_value_cansleep(ts->reset_gpio, 1);
		regulator_disable(ts->vccio);
		regulator_disable(ts->vcc33);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id i2c_hid_ids[] = अणु
	अणु"ACPI0C50", 0 पूर्ण,
	अणु"PNP0C50", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर guid_t i2c_hid_guid =
	GUID_INIT(0x3CDFF6F7, 0x4267, 0x4555,
		  0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE);

अटल bool elants_acpi_is_hid_device(काष्ठा device *dev)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object *obj;

	अगर (acpi_match_device_ids(ACPI_COMPANION(dev), i2c_hid_ids))
		वापस false;

	obj = acpi_evaluate_dsm_typed(handle, &i2c_hid_guid, 1, 1, शून्य, ACPI_TYPE_INTEGER);
	अगर (obj) अणु
		ACPI_FREE(obj);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा
अटल bool elants_acpi_is_hid_device(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक elants_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	जोड़ i2c_smbus_data dummy;
	काष्ठा elants_data *ts;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक error;

	/* Don't bind to i2c-hid compatible devices, these are handled by the i2c-hid drv. */
	अगर (elants_acpi_is_hid_device(&client->dev)) अणु
		dev_warn(&client->dev, "This device appears to be an I2C-HID device, not binding\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "I2C check functionality error\n");
		वापस -ENXIO;
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(काष्ठा elants_data), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	mutex_init(&ts->sysfs_mutex);
	init_completion(&ts->cmd_करोne);

	ts->client = client;
	ts->chip_id = (क्रमागत elants_chip_id)id->driver_data;
	i2c_set_clientdata(client, ts);

	ts->vcc33 = devm_regulator_get(&client->dev, "vcc33");
	अगर (IS_ERR(ts->vcc33)) अणु
		error = PTR_ERR(ts->vcc33);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'vcc33' regulator: %d\n",
				error);
		वापस error;
	पूर्ण

	ts->vccio = devm_regulator_get(&client->dev, "vccio");
	अगर (IS_ERR(ts->vccio)) अणु
		error = PTR_ERR(ts->vccio);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'vccio' regulator: %d\n",
				error);
		वापस error;
	पूर्ण

	ts->reset_gpio = devm_gpiod_get(&client->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ts->reset_gpio)) अणु
		error = PTR_ERR(ts->reset_gpio);

		अगर (error == -EPROBE_DEFER)
			वापस error;

		अगर (error != -ENOENT && error != -ENOSYS) अणु
			dev_err(&client->dev,
				"failed to get reset gpio: %d\n",
				error);
			वापस error;
		पूर्ण

		ts->keep_घातer_in_suspend = true;
	पूर्ण

	error = elants_i2c_घातer_on(ts);
	अगर (error)
		वापस error;

	error = devm_add_action(&client->dev, elants_i2c_घातer_off, ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to install power off action: %d\n", error);
		elants_i2c_घातer_off(ts);
		वापस error;
	पूर्ण

	/* Make sure there is something at this address */
	अगर (i2c_smbus_xfer(client->adapter, client->addr, 0,
			   I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &dummy) < 0) अणु
		dev_err(&client->dev, "nothing at this address\n");
		वापस -ENXIO;
	पूर्ण

	error = elants_i2c_initialize(ts);
	अगर (error) अणु
		dev_err(&client->dev, "failed to initialize: %d\n", error);
		वापस error;
	पूर्ण

	ts->input = devm_input_allocate_device(&client->dev);
	अगर (!ts->input) अणु
		dev_err(&client->dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ts->input->name = "Elan Touchscreen";
	ts->input->id.bustype = BUS_I2C;

	/* Multitouch input params setup */

	input_set_असल_params(ts->input, ABS_MT_POSITION_X, 0, ts->x_max, 0, 0);
	input_set_असल_params(ts->input, ABS_MT_POSITION_Y, 0, ts->y_max, 0, 0);
	input_set_असल_params(ts->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(ts->input, ABS_MT_PRESSURE, 0, 255, 0, 0);
	input_set_असल_params(ts->input, ABS_MT_TOOL_TYPE,
			     0, MT_TOOL_PALM, 0, 0);

	touchscreen_parse_properties(ts->input, true, &ts->prop);

	अगर (ts->chip_id == EKTF3624 && ts->phy_x && ts->phy_y) अणु
		/* calculate resolution from size */
		ts->x_res = DIV_ROUND_CLOSEST(ts->prop.max_x, ts->phy_x);
		ts->y_res = DIV_ROUND_CLOSEST(ts->prop.max_y, ts->phy_y);
	पूर्ण

	input_असल_set_res(ts->input, ABS_MT_POSITION_X, ts->x_res);
	input_असल_set_res(ts->input, ABS_MT_POSITION_Y, ts->y_res);
	input_असल_set_res(ts->input, ABS_MT_TOUCH_MAJOR, ts->major_res);

	error = input_mt_init_slots(ts->input, MAX_CONTACT_NUM,
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

	/*
	 * Platक्रमm code (ACPI, DTS) should normally set up पूर्णांकerrupt
	 * क्रम us, but in हाल it did not let's fall back to using falling
	 * edge to be compatible with older Chromebooks.
	 */
	irqflags = irq_get_trigger_type(client->irq);
	अगर (!irqflags)
		irqflags = IRQF_TRIGGER_FALLING;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, elants_i2c_irq,
					  irqflags | IRQF_ONESHOT,
					  client->name, ts);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	/*
	 * Systems using device tree should set up wakeup via DTS,
	 * the rest will configure device as wakeup source by शेष.
	 */
	अगर (!client->dev.of_node)
		device_init_wakeup(&client->dev, true);

	error = devm_device_add_group(&client->dev, &elants_attribute_group);
	अगर (error) अणु
		dev_err(&client->dev, "failed to create sysfs attributes: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused elants_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elants_data *ts = i2c_get_clientdata(client);
	स्थिर u8 set_sleep_cmd[] = अणु
		CMD_HEADER_WRITE, E_POWER_STATE_SLEEP, 0x00, 0x01
	पूर्ण;
	पूर्णांक retry_cnt;
	पूर्णांक error;

	/* Command not support in IAP recovery mode */
	अगर (ts->iap_mode != ELAN_IAP_OPERATIONAL)
		वापस -EBUSY;

	disable_irq(client->irq);

	अगर (device_may_wakeup(dev)) अणु
		/*
		 * The device will स्वतःmatically enter idle mode
		 * that has reduced घातer consumption.
		 */
		ts->wake_irq_enabled = (enable_irq_wake(client->irq) == 0);
	पूर्ण अन्यथा अगर (ts->keep_घातer_in_suspend) अणु
		क्रम (retry_cnt = 0; retry_cnt < MAX_RETRIES; retry_cnt++) अणु
			error = elants_i2c_send(client, set_sleep_cmd,
						माप(set_sleep_cmd));
			अगर (!error)
				अवरोध;

			dev_err(&client->dev,
				"suspend command failed: %d\n", error);
		पूर्ण
	पूर्ण अन्यथा अणु
		elants_i2c_घातer_off(ts);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused elants_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elants_data *ts = i2c_get_clientdata(client);
	स्थिर u8 set_active_cmd[] = अणु
		CMD_HEADER_WRITE, E_POWER_STATE_RESUME, 0x00, 0x01
	पूर्ण;
	पूर्णांक retry_cnt;
	पूर्णांक error;

	अगर (device_may_wakeup(dev)) अणु
		अगर (ts->wake_irq_enabled)
			disable_irq_wake(client->irq);
		elants_i2c_sw_reset(client);
	पूर्ण अन्यथा अगर (ts->keep_घातer_in_suspend) अणु
		क्रम (retry_cnt = 0; retry_cnt < MAX_RETRIES; retry_cnt++) अणु
			error = elants_i2c_send(client, set_active_cmd,
						माप(set_active_cmd));
			अगर (!error)
				अवरोध;

			dev_err(&client->dev,
				"resume command failed: %d\n", error);
		पूर्ण
	पूर्ण अन्यथा अणु
		elants_i2c_घातer_on(ts);
		elants_i2c_initialize(ts);
	पूर्ण

	ts->state = ELAN_STATE_NORMAL;
	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(elants_i2c_pm_ops,
			 elants_i2c_suspend, elants_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id elants_i2c_id[] = अणु
	अणु DEVICE_NAME, EKTH3500 पूर्ण,
	अणु "ekth3500", EKTH3500 पूर्ण,
	अणु "ektf3624", EKTF3624 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, elants_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id elants_acpi_id[] = अणु
	अणु "ELAN0001", EKTH3500 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, elants_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id elants_of_match[] = अणु
	अणु .compatible = "elan,ekth3500" पूर्ण,
	अणु .compatible = "elan,ektf3624" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, elants_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver elants_i2c_driver = अणु
	.probe = elants_i2c_probe,
	.id_table = elants_i2c_id,
	.driver = अणु
		.name = DEVICE_NAME,
		.pm = &elants_i2c_pm_ops,
		.acpi_match_table = ACPI_PTR(elants_acpi_id),
		.of_match_table = of_match_ptr(elants_of_match),
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_i2c_driver(elants_i2c_driver);

MODULE_AUTHOR("Scott Liu <scott.liu@emc.com.tw>");
MODULE_DESCRIPTION("Elan I2c Touchscreen driver");
MODULE_LICENSE("GPL");
