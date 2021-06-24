<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Elan I2C/SMBus Touchpad driver - I2C पूर्णांकerface
 *
 * Copyright (c) 2013 ELAN Microelectronics Corp.
 *
 * Author: ौौडॉघऐ (Duson Lin) <dusonlin@emc.com.tw>
 *
 * Based on cyapa driver:
 * copyright (c) 2011-2012 Cypress Semiconductor, Inc.
 * copyright (c) 2011-2012 Google, Inc.
 *
 * Trademarks are the property of their respective owners.
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "elan_i2c.h"

/* Elan i2c commands */
#घोषणा ETP_I2C_RESET			0x0100
#घोषणा ETP_I2C_WAKE_UP			0x0800
#घोषणा ETP_I2C_SLEEP			0x0801
#घोषणा ETP_I2C_DESC_CMD		0x0001
#घोषणा ETP_I2C_REPORT_DESC_CMD		0x0002
#घोषणा ETP_I2C_STAND_CMD		0x0005
#घोषणा ETP_I2C_PATTERN_CMD		0x0100
#घोषणा ETP_I2C_UNIQUEID_CMD		0x0101
#घोषणा ETP_I2C_FW_VERSION_CMD		0x0102
#घोषणा ETP_I2C_IC_TYPE_CMD		0x0103
#घोषणा ETP_I2C_OSM_VERSION_CMD		0x0103
#घोषणा ETP_I2C_NSM_VERSION_CMD		0x0104
#घोषणा ETP_I2C_XY_TRACENUM_CMD		0x0105
#घोषणा ETP_I2C_MAX_X_AXIS_CMD		0x0106
#घोषणा ETP_I2C_MAX_Y_AXIS_CMD		0x0107
#घोषणा ETP_I2C_RESOLUTION_CMD		0x0108
#घोषणा ETP_I2C_PRESSURE_CMD		0x010A
#घोषणा ETP_I2C_IAP_VERSION_CMD		0x0110
#घोषणा ETP_I2C_IC_TYPE_P0_CMD		0x0110
#घोषणा ETP_I2C_IAP_VERSION_P0_CMD	0x0111
#घोषणा ETP_I2C_SET_CMD			0x0300
#घोषणा ETP_I2C_POWER_CMD		0x0307
#घोषणा ETP_I2C_FW_CHECKSUM_CMD		0x030F
#घोषणा ETP_I2C_IAP_CTRL_CMD		0x0310
#घोषणा ETP_I2C_IAP_CMD			0x0311
#घोषणा ETP_I2C_IAP_RESET_CMD		0x0314
#घोषणा ETP_I2C_IAP_CHECKSUM_CMD	0x0315
#घोषणा ETP_I2C_CALIBRATE_CMD		0x0316
#घोषणा ETP_I2C_MAX_BASELINE_CMD	0x0317
#घोषणा ETP_I2C_MIN_BASELINE_CMD	0x0318
#घोषणा ETP_I2C_IAP_TYPE_REG		0x0040
#घोषणा ETP_I2C_IAP_TYPE_CMD		0x0304

#घोषणा ETP_I2C_REPORT_LEN		34
#घोषणा ETP_I2C_REPORT_LEN_ID2		39
#घोषणा ETP_I2C_REPORT_MAX_LEN		39
#घोषणा ETP_I2C_DESC_LENGTH		30
#घोषणा ETP_I2C_REPORT_DESC_LENGTH	158
#घोषणा ETP_I2C_INF_LENGTH		2
#घोषणा ETP_I2C_IAP_PASSWORD		0x1EA5
#घोषणा ETP_I2C_IAP_RESET		0xF0F0
#घोषणा ETP_I2C_MAIN_MODE_ON		(1 << 9)
#घोषणा ETP_I2C_IAP_REG_L		0x01
#घोषणा ETP_I2C_IAP_REG_H		0x06

अटल पूर्णांक elan_i2c_पढ़ो_block(काष्ठा i2c_client *client,
			       u16 reg, u8 *val, u16 len)
अणु
	__le16 buf[] = अणु
		cpu_to_le16(reg),
	पूर्ण;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client->addr,
			.flags = client->flags & I2C_M_TEN,
			.len = माप(buf),
			.buf = (u8 *)buf,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = (client->flags & I2C_M_TEN) | I2C_M_RD,
			.len = len,
			.buf = val,
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	वापस ret == ARRAY_SIZE(msgs) ? 0 : (ret < 0 ? ret : -EIO);
पूर्ण

अटल पूर्णांक elan_i2c_पढ़ो_cmd(काष्ठा i2c_client *client, u16 reg, u8 *val)
अणु
	पूर्णांक retval;

	retval = elan_i2c_पढ़ो_block(client, reg, val, ETP_I2C_INF_LENGTH);
	अगर (retval < 0) अणु
		dev_err(&client->dev, "reading cmd (0x%04x) fail.\n", reg);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_ग_लिखो_cmd(काष्ठा i2c_client *client, u16 reg, u16 cmd)
अणु
	__le16 buf[] = अणु
		cpu_to_le16(reg),
		cpu_to_le16(cmd),
	पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.flags = client->flags & I2C_M_TEN,
		.len = माप(buf),
		.buf = (u8 *)buf,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		अगर (ret >= 0)
			ret = -EIO;
		dev_err(&client->dev, "writing cmd (0x%04x) failed: %d\n",
			reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_initialize(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;
	u8 val[256];

	error = elan_i2c_ग_लिखो_cmd(client, ETP_I2C_STAND_CMD, ETP_I2C_RESET);
	अगर (error) अणु
		dev_err(dev, "device reset failed: %d\n", error);
		वापस error;
	पूर्ण

	/* Wait क्रम the device to reset */
	msleep(100);

	/* get reset acknowledgement 0000 */
	error = i2c_master_recv(client, val, ETP_I2C_INF_LENGTH);
	अगर (error < 0) अणु
		dev_err(dev, "failed to read reset response: %d\n", error);
		वापस error;
	पूर्ण

	error = elan_i2c_पढ़ो_block(client, ETP_I2C_DESC_CMD,
				    val, ETP_I2C_DESC_LENGTH);
	अगर (error) अणु
		dev_err(dev, "cannot get device descriptor: %d\n", error);
		वापस error;
	पूर्ण

	error = elan_i2c_पढ़ो_block(client, ETP_I2C_REPORT_DESC_CMD,
				    val, ETP_I2C_REPORT_DESC_LENGTH);
	अगर (error) अणु
		dev_err(dev, "fetching report descriptor failed.: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_sleep_control(काष्ठा i2c_client *client, bool sleep)
अणु
	वापस elan_i2c_ग_लिखो_cmd(client, ETP_I2C_STAND_CMD,
				  sleep ? ETP_I2C_SLEEP : ETP_I2C_WAKE_UP);
पूर्ण

अटल पूर्णांक elan_i2c_घातer_control(काष्ठा i2c_client *client, bool enable)
अणु
	u8 val[2];
	u16 reg;
	पूर्णांक error;

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_POWER_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to read current power state: %d\n",
			error);
		वापस error;
	पूर्ण

	reg = le16_to_cpup((__le16 *)val);
	अगर (enable)
		reg &= ~ETP_DISABLE_POWER;
	अन्यथा
		reg |= ETP_DISABLE_POWER;

	error = elan_i2c_ग_लिखो_cmd(client, ETP_I2C_POWER_CMD, reg);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to write current power state: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_set_mode(काष्ठा i2c_client *client, u8 mode)
अणु
	वापस elan_i2c_ग_लिखो_cmd(client, ETP_I2C_SET_CMD, mode);
पूर्ण


अटल पूर्णांक elan_i2c_calibrate(काष्ठा i2c_client *client)
अणु
	वापस elan_i2c_ग_लिखो_cmd(client, ETP_I2C_CALIBRATE_CMD, 1);
पूर्ण

अटल पूर्णांक elan_i2c_calibrate_result(काष्ठा i2c_client *client, u8 *val)
अणु
	वापस elan_i2c_पढ़ो_block(client, ETP_I2C_CALIBRATE_CMD, val, 1);
पूर्ण

अटल पूर्णांक elan_i2c_get_baseline_data(काष्ठा i2c_client *client,
				      bool max_baseline, u8 *value)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client,
				  max_baseline ? ETP_I2C_MAX_BASELINE_CMD :
						 ETP_I2C_MIN_BASELINE_CMD,
				  val);
	अगर (error)
		वापस error;

	*value = le16_to_cpup((__le16 *)val);

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_pattern(काष्ठा i2c_client *client, u8 *pattern)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_PATTERN_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get pattern: %d\n", error);
		वापस error;
	पूर्ण

	/*
	 * Not all versions of firmware implement "get pattern" command.
	 * When this command is not implemented the device will respond
	 * with 0xFF 0xFF, which we will treat as "old" pattern 0.
	 */
	*pattern = val[0] == 0xFF && val[1] == 0xFF ? 0 : val[1];

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_version(काष्ठा i2c_client *client,
				u8 pattern, bool iap, u8 *version)
अणु
	पूर्णांक error;
	u16 cmd;
	u8 val[3];

	अगर (!iap)
		cmd = ETP_I2C_FW_VERSION_CMD;
	अन्यथा अगर (pattern == 0)
		cmd = ETP_I2C_IAP_VERSION_P0_CMD;
	अन्यथा
		cmd = ETP_I2C_IAP_VERSION_CMD;

	error = elan_i2c_पढ़ो_cmd(client, cmd, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get %s version: %d\n",
			iap ? "IAP" : "FW", error);
		वापस error;
	पूर्ण

	अगर (pattern >= 0x01)
		*version = iap ? val[1] : val[0];
	अन्यथा
		*version = val[0];
	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_sm_version(काष्ठा i2c_client *client, u8 pattern,
				   u16 *ic_type, u8 *version, u8 *clickpad)
अणु
	पूर्णांक error;
	u8 val[3];

	अगर (pattern >= 0x01) अणु
		error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_IC_TYPE_CMD, val);
		अगर (error) अणु
			dev_err(&client->dev, "failed to get ic type: %d\n",
				error);
			वापस error;
		पूर्ण
		*ic_type = be16_to_cpup((__be16 *)val);

		error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_NSM_VERSION_CMD,
					  val);
		अगर (error) अणु
			dev_err(&client->dev, "failed to get SM version: %d\n",
				error);
			वापस error;
		पूर्ण
		*version = val[1];
		*clickpad = val[0] & 0x10;
	पूर्ण अन्यथा अणु
		error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_OSM_VERSION_CMD, val);
		अगर (error) अणु
			dev_err(&client->dev, "failed to get SM version: %d\n",
				error);
			वापस error;
		पूर्ण
		*version = val[0];

		error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_IC_TYPE_P0_CMD, val);
		अगर (error) अणु
			dev_err(&client->dev, "failed to get ic type: %d\n",
				error);
			वापस error;
		पूर्ण
		*ic_type = val[0];

		error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_NSM_VERSION_CMD,
					  val);
		अगर (error) अणु
			dev_err(&client->dev, "failed to get SM version: %d\n",
				error);
			वापस error;
		पूर्ण
		*clickpad = val[0] & 0x10;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_product_id(काष्ठा i2c_client *client, u16 *id)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_UNIQUEID_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get product ID: %d\n", error);
		वापस error;
	पूर्ण

	*id = le16_to_cpup((__le16 *)val);
	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_checksum(काष्ठा i2c_client *client,
				 bool iap, u16 *csum)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client,
				  iap ? ETP_I2C_IAP_CHECKSUM_CMD :
					ETP_I2C_FW_CHECKSUM_CMD,
				  val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get %s checksum: %d\n",
			iap ? "IAP" : "FW", error);
		वापस error;
	पूर्ण

	*csum = le16_to_cpup((__le16 *)val);
	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_max(काष्ठा i2c_client *client,
			    अचिन्हित पूर्णांक *max_x, अचिन्हित पूर्णांक *max_y)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_MAX_X_AXIS_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get X dimension: %d\n", error);
		वापस error;
	पूर्ण

	*max_x = le16_to_cpup((__le16 *)val);

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_MAX_Y_AXIS_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get Y dimension: %d\n", error);
		वापस error;
	पूर्ण

	*max_y = le16_to_cpup((__le16 *)val);

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_resolution(काष्ठा i2c_client *client,
				   u8 *hw_res_x, u8 *hw_res_y)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_RESOLUTION_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get resolution: %d\n", error);
		वापस error;
	पूर्ण

	*hw_res_x = val[0];
	*hw_res_y = val[1];

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_num_traces(काष्ठा i2c_client *client,
				   अचिन्हित पूर्णांक *x_traces,
				   अचिन्हित पूर्णांक *y_traces)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_XY_TRACENUM_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get trace info: %d\n", error);
		वापस error;
	पूर्ण

	*x_traces = val[0];
	*y_traces = val[1];

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_pressure_adjusपंचांगent(काष्ठा i2c_client *client,
					    पूर्णांक *adjusपंचांगent)
अणु
	पूर्णांक error;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_PRESSURE_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get pressure format: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर ((val[0] >> 4) & 0x1)
		*adjusपंचांगent = 0;
	अन्यथा
		*adjusपंचांगent = ETP_PRESSURE_OFFSET;

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_iap_get_mode(काष्ठा i2c_client *client, क्रमागत tp_mode *mode)
अणु
	पूर्णांक error;
	u16 स्थिरant;
	u8 val[3];

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_IAP_CTRL_CMD, val);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to read iap control register: %d\n",
			error);
		वापस error;
	पूर्ण

	स्थिरant = le16_to_cpup((__le16 *)val);
	dev_dbg(&client->dev, "iap control reg: 0x%04x.\n", स्थिरant);

	*mode = (स्थिरant & ETP_I2C_MAIN_MODE_ON) ? MAIN_MODE : IAP_MODE;

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_iap_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;

	error = elan_i2c_ग_लिखो_cmd(client, ETP_I2C_IAP_RESET_CMD,
				   ETP_I2C_IAP_RESET);
	अगर (error) अणु
		dev_err(&client->dev, "cannot reset IC: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_set_flash_key(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;

	error = elan_i2c_ग_लिखो_cmd(client, ETP_I2C_IAP_CMD,
				   ETP_I2C_IAP_PASSWORD);
	अगर (error) अणु
		dev_err(&client->dev, "cannot set flash key: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_पढ़ो_ग_लिखो_iap_type(काष्ठा i2c_client *client, u16 fw_page_size)
अणु
	पूर्णांक error;
	u16 स्थिरant;
	u8 val[3];
	पूर्णांक retry = 3;

	करो अणु
		error = elan_i2c_ग_लिखो_cmd(client, ETP_I2C_IAP_TYPE_CMD,
					   fw_page_size / 2);
		अगर (error) अणु
			dev_err(&client->dev,
				"cannot write iap type: %d\n", error);
			वापस error;
		पूर्ण

		error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_IAP_TYPE_CMD, val);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to read iap type register: %d\n",
				error);
			वापस error;
		पूर्ण
		स्थिरant = le16_to_cpup((__le16 *)val);
		dev_dbg(&client->dev, "iap type reg: 0x%04x\n", स्थिरant);

		अगर (स्थिरant == fw_page_size / 2)
			वापस 0;

	पूर्ण जबतक (--retry > 0);

	dev_err(&client->dev, "cannot set iap type\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक elan_i2c_prepare_fw_update(काष्ठा i2c_client *client, u16 ic_type,
				      u8 iap_version, u16 fw_page_size)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;
	क्रमागत tp_mode mode;
	u8 val[3];
	u16 password;

	/* Get FW in which mode	(IAP_MODE/MAIN_MODE)  */
	error = elan_i2c_iap_get_mode(client, &mode);
	अगर (error)
		वापस error;

	अगर (mode == IAP_MODE) अणु
		/* Reset IC */
		error = elan_i2c_iap_reset(client);
		अगर (error)
			वापस error;

		msleep(30);
	पूर्ण

	/* Set flash key*/
	error = elan_i2c_set_flash_key(client);
	अगर (error)
		वापस error;

	/* Wait क्रम F/W IAP initialization */
	msleep(mode == MAIN_MODE ? 100 : 30);

	/* Check अगर we are in IAP mode or not */
	error = elan_i2c_iap_get_mode(client, &mode);
	अगर (error)
		वापस error;

	अगर (mode == MAIN_MODE) अणु
		dev_err(dev, "wrong mode: %d\n", mode);
		वापस -EIO;
	पूर्ण

	अगर (ic_type >= 0x0D && iap_version >= 1) अणु
		error = elan_पढ़ो_ग_लिखो_iap_type(client, fw_page_size);
		अगर (error)
			वापस error;
	पूर्ण

	/* Set flash key again */
	error = elan_i2c_set_flash_key(client);
	अगर (error)
		वापस error;

	/* Wait क्रम F/W IAP initialization */
	msleep(30);

	/* पढ़ो back to check we actually enabled successfully. */
	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_IAP_CMD, val);
	अगर (error) अणु
		dev_err(dev, "cannot read iap password: %d\n",
			error);
		वापस error;
	पूर्ण

	password = le16_to_cpup((__le16 *)val);
	अगर (password != ETP_I2C_IAP_PASSWORD) अणु
		dev_err(dev, "wrong iap password: 0x%X\n", password);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_ग_लिखो_fw_block(काष्ठा i2c_client *client, u16 fw_page_size,
				   स्थिर u8 *page, u16 checksum, पूर्णांक idx)
अणु
	काष्ठा device *dev = &client->dev;
	u8 *page_store;
	u8 val[3];
	u16 result;
	पूर्णांक ret, error;

	page_store = kदो_स्मृति(fw_page_size + 4, GFP_KERNEL);
	अगर (!page_store)
		वापस -ENOMEM;

	page_store[0] = ETP_I2C_IAP_REG_L;
	page_store[1] = ETP_I2C_IAP_REG_H;
	स_नकल(&page_store[2], page, fw_page_size);
	/* recode checksum at last two bytes */
	put_unaligned_le16(checksum, &page_store[fw_page_size + 2]);

	ret = i2c_master_send(client, page_store, fw_page_size + 4);
	अगर (ret != fw_page_size + 4) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(dev, "Failed to write page %d: %d\n", idx, error);
		जाओ निकास;
	पूर्ण

	/* Wait क्रम F/W to update one page ROM data. */
	msleep(fw_page_size == ETP_FW_PAGE_SIZE_512 ? 50 : 35);

	error = elan_i2c_पढ़ो_cmd(client, ETP_I2C_IAP_CTRL_CMD, val);
	अगर (error) अणु
		dev_err(dev, "Failed to read IAP write result: %d\n", error);
		जाओ निकास;
	पूर्ण

	result = le16_to_cpup((__le16 *)val);
	अगर (result & (ETP_FW_IAP_PAGE_ERR | ETP_FW_IAP_INTF_ERR)) अणु
		dev_err(dev, "IAP reports failed write: %04hx\n",
			result);
		error = -EIO;
		जाओ निकास;
	पूर्ण

निकास:
	kमुक्त(page_store);
	वापस error;
पूर्ण

अटल पूर्णांक elan_i2c_finish_fw_update(काष्ठा i2c_client *client,
				     काष्ठा completion *completion)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक error = 0;
	पूर्णांक len;
	u8 buffer[ETP_I2C_REPORT_MAX_LEN];

	len = i2c_master_recv(client, buffer, ETP_I2C_REPORT_MAX_LEN);
	अगर (len <= 0) अणु
		error = len < 0 ? len : -EIO;
		dev_warn(dev, "failed to read I2C data after FW WDT reset: %d (%d)\n",
			error, len);
	पूर्ण

	reinit_completion(completion);
	enable_irq(client->irq);

	error = elan_i2c_ग_लिखो_cmd(client, ETP_I2C_STAND_CMD, ETP_I2C_RESET);
	अगर (error) अणु
		dev_err(dev, "device reset failed: %d\n", error);
	पूर्ण अन्यथा अगर (!रुको_क्रम_completion_समयout(completion,
						msecs_to_jअगरfies(300))) अणु
		dev_err(dev, "timeout waiting for device reset\n");
		error = -ETIMEDOUT;
	पूर्ण

	disable_irq(client->irq);

	अगर (error)
		वापस error;

	len = i2c_master_recv(client, buffer, ETP_I2C_INF_LENGTH);
	अगर (len != ETP_I2C_INF_LENGTH) अणु
		error = len < 0 ? len : -EIO;
		dev_err(dev, "failed to read INT signal: %d (%d)\n",
			error, len);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_report_features(काष्ठा i2c_client *client, u8 pattern,
					अचिन्हित पूर्णांक *features,
					अचिन्हित पूर्णांक *report_len)
अणु
	*features = ETP_FEATURE_REPORT_MK;
	*report_len = pattern <= 0x01 ?
			ETP_I2C_REPORT_LEN : ETP_I2C_REPORT_LEN_ID2;
	वापस 0;
पूर्ण

अटल पूर्णांक elan_i2c_get_report(काष्ठा i2c_client *client,
			       u8 *report, अचिन्हित पूर्णांक report_len)
अणु
	पूर्णांक len;

	len = i2c_master_recv(client, report, report_len);
	अगर (len < 0) अणु
		dev_err(&client->dev, "failed to read report data: %d\n", len);
		वापस len;
	पूर्ण

	अगर (len != report_len) अणु
		dev_err(&client->dev,
			"wrong report length (%d vs %d expected)\n",
			len, report_len);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा elan_transport_ops elan_i2c_ops = अणु
	.initialize		= elan_i2c_initialize,
	.sleep_control		= elan_i2c_sleep_control,
	.घातer_control		= elan_i2c_घातer_control,
	.set_mode		= elan_i2c_set_mode,

	.calibrate		= elan_i2c_calibrate,
	.calibrate_result	= elan_i2c_calibrate_result,

	.get_baseline_data	= elan_i2c_get_baseline_data,

	.get_version		= elan_i2c_get_version,
	.get_sm_version		= elan_i2c_get_sm_version,
	.get_product_id		= elan_i2c_get_product_id,
	.get_checksum		= elan_i2c_get_checksum,
	.get_pressure_adjusपंचांगent = elan_i2c_get_pressure_adjusपंचांगent,

	.get_max		= elan_i2c_get_max,
	.get_resolution		= elan_i2c_get_resolution,
	.get_num_traces		= elan_i2c_get_num_traces,

	.iap_get_mode		= elan_i2c_iap_get_mode,
	.iap_reset		= elan_i2c_iap_reset,

	.prepare_fw_update	= elan_i2c_prepare_fw_update,
	.ग_लिखो_fw_block		= elan_i2c_ग_लिखो_fw_block,
	.finish_fw_update	= elan_i2c_finish_fw_update,

	.get_pattern		= elan_i2c_get_pattern,

	.get_report_features	= elan_i2c_get_report_features,
	.get_report		= elan_i2c_get_report,
पूर्ण;
