<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Elan I2C/SMBus Touchpad driver - SMBus पूर्णांकerface
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

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>

#समावेश "elan_i2c.h"

/* Elan SMbus commands */
#घोषणा ETP_SMBUS_IAP_CMD		0x00
#घोषणा ETP_SMBUS_ENABLE_TP		0x20
#घोषणा ETP_SMBUS_SLEEP_CMD		0x21
#घोषणा ETP_SMBUS_IAP_PASSWORD_WRITE	0x29
#घोषणा ETP_SMBUS_IAP_PASSWORD_READ	0x80
#घोषणा ETP_SMBUS_WRITE_FW_BLOCK	0x2A
#घोषणा ETP_SMBUS_IAP_RESET_CMD		0x2B
#घोषणा ETP_SMBUS_RANGE_CMD		0xA0
#घोषणा ETP_SMBUS_FW_VERSION_CMD	0xA1
#घोषणा ETP_SMBUS_XY_TRACENUM_CMD	0xA2
#घोषणा ETP_SMBUS_SM_VERSION_CMD	0xA3
#घोषणा ETP_SMBUS_UNIQUEID_CMD		0xA3
#घोषणा ETP_SMBUS_RESOLUTION_CMD	0xA4
#घोषणा ETP_SMBUS_HELLOPACKET_CMD	0xA7
#घोषणा ETP_SMBUS_PACKET_QUERY		0xA8
#घोषणा ETP_SMBUS_IAP_VERSION_CMD	0xAC
#घोषणा ETP_SMBUS_IAP_CTRL_CMD		0xAD
#घोषणा ETP_SMBUS_IAP_CHECKSUM_CMD	0xAE
#घोषणा ETP_SMBUS_FW_CHECKSUM_CMD	0xAF
#घोषणा ETP_SMBUS_MAX_BASELINE_CMD	0xC3
#घोषणा ETP_SMBUS_MIN_BASELINE_CMD	0xC4
#घोषणा ETP_SMBUS_CALIBRATE_QUERY	0xC5

#घोषणा ETP_SMBUS_REPORT_LEN		32
#घोषणा ETP_SMBUS_REPORT_LEN2		7
#घोषणा ETP_SMBUS_REPORT_OFFSET		2
#घोषणा ETP_SMBUS_HELLOPACKET_LEN	5
#घोषणा ETP_SMBUS_IAP_PASSWORD		0x1234
#घोषणा ETP_SMBUS_IAP_MODE_ON		(1 << 6)

अटल पूर्णांक elan_smbus_initialize(काष्ठा i2c_client *client)
अणु
	u8 check[ETP_SMBUS_HELLOPACKET_LEN] = अणु 0x55, 0x55, 0x55, 0x55, 0x55 पूर्ण;
	u8 values[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;
	पूर्णांक len, error;

	/* Get hello packet */
	len = i2c_smbus_पढ़ो_block_data(client,
					ETP_SMBUS_HELLOPACKET_CMD, values);
	अगर (len != ETP_SMBUS_HELLOPACKET_LEN) अणु
		dev_err(&client->dev, "hello packet length fail: %d\n", len);
		error = len < 0 ? len : -EIO;
		वापस error;
	पूर्ण

	/* compare hello packet */
	अगर (स_भेद(values, check, ETP_SMBUS_HELLOPACKET_LEN)) अणु
		dev_err(&client->dev, "hello packet fail [%*ph]\n",
			ETP_SMBUS_HELLOPACKET_LEN, values);
		वापस -ENXIO;
	पूर्ण

	/* enable tp */
	error = i2c_smbus_ग_लिखो_byte(client, ETP_SMBUS_ENABLE_TP);
	अगर (error) अणु
		dev_err(&client->dev, "failed to enable touchpad: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_set_mode(काष्ठा i2c_client *client, u8 mode)
अणु
	u8 cmd[4] = अणु 0x00, 0x07, 0x00, mode पूर्ण;

	वापस i2c_smbus_ग_लिखो_block_data(client, ETP_SMBUS_IAP_CMD,
					  माप(cmd), cmd);
पूर्ण

अटल पूर्णांक elan_smbus_sleep_control(काष्ठा i2c_client *client, bool sleep)
अणु
	अगर (sleep)
		वापस i2c_smbus_ग_लिखो_byte(client, ETP_SMBUS_SLEEP_CMD);
	अन्यथा
		वापस 0; /* XXX should we send ETP_SMBUS_ENABLE_TP here? */
पूर्ण

अटल पूर्णांक elan_smbus_घातer_control(काष्ठा i2c_client *client, bool enable)
अणु
	वापस 0; /* A no-op */
पूर्ण

अटल पूर्णांक elan_smbus_calibrate(काष्ठा i2c_client *client)
अणु
	u8 cmd[4] = अणु 0x00, 0x08, 0x00, 0x01 पूर्ण;

	वापस i2c_smbus_ग_लिखो_block_data(client, ETP_SMBUS_IAP_CMD,
					  माप(cmd), cmd);
पूर्ण

अटल पूर्णांक elan_smbus_calibrate_result(काष्ठा i2c_client *client, u8 *val)
अणु
	पूर्णांक error;
	u8 buf[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	BUILD_BUG_ON(ETP_CALIBRATE_MAX_LEN > माप(buf));

	error = i2c_smbus_पढ़ो_block_data(client,
					  ETP_SMBUS_CALIBRATE_QUERY, buf);
	अगर (error < 0)
		वापस error;

	स_नकल(val, buf, ETP_CALIBRATE_MAX_LEN);
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_baseline_data(काष्ठा i2c_client *client,
					bool max_baseline, u8 *value)
अणु
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	error = i2c_smbus_पढ़ो_block_data(client,
					  max_baseline ?
						ETP_SMBUS_MAX_BASELINE_CMD :
						ETP_SMBUS_MIN_BASELINE_CMD,
					  val);
	अगर (error < 0)
		वापस error;

	*value = be16_to_cpup((__be16 *)val);

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_version(काष्ठा i2c_client *client,
				  u8 pattern, bool iap, u8 *version)
अणु
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	error = i2c_smbus_पढ़ो_block_data(client,
					  iap ? ETP_SMBUS_IAP_VERSION_CMD :
						ETP_SMBUS_FW_VERSION_CMD,
					  val);
	अगर (error < 0) अणु
		dev_err(&client->dev, "failed to get %s version: %d\n",
			iap ? "IAP" : "FW", error);
		वापस error;
	पूर्ण

	*version = val[2];
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_sm_version(काष्ठा i2c_client *client, u8 pattern,
				     u16 *ic_type, u8 *version, u8 *clickpad)
अणु
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	error = i2c_smbus_पढ़ो_block_data(client,
					  ETP_SMBUS_SM_VERSION_CMD, val);
	अगर (error < 0) अणु
		dev_err(&client->dev, "failed to get SM version: %d\n", error);
		वापस error;
	पूर्ण

	*version = val[0];
	*ic_type = val[1];
	*clickpad = val[0] & 0x10;
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_product_id(काष्ठा i2c_client *client, u16 *id)
अणु
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	error = i2c_smbus_पढ़ो_block_data(client,
					  ETP_SMBUS_UNIQUEID_CMD, val);
	अगर (error < 0) अणु
		dev_err(&client->dev, "failed to get product ID: %d\n", error);
		वापस error;
	पूर्ण

	*id = be16_to_cpup((__be16 *)val);
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_checksum(काष्ठा i2c_client *client,
				   bool iap, u16 *csum)
अणु
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	error = i2c_smbus_पढ़ो_block_data(client,
					  iap ? ETP_SMBUS_FW_CHECKSUM_CMD :
						ETP_SMBUS_IAP_CHECKSUM_CMD,
					  val);
	अगर (error < 0) अणु
		dev_err(&client->dev, "failed to get %s checksum: %d\n",
			iap ? "IAP" : "FW", error);
		वापस error;
	पूर्ण

	*csum = be16_to_cpup((__be16 *)val);
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_max(काष्ठा i2c_client *client,
			      अचिन्हित पूर्णांक *max_x, अचिन्हित पूर्णांक *max_y)
अणु
	पूर्णांक ret;
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	ret = i2c_smbus_पढ़ो_block_data(client, ETP_SMBUS_RANGE_CMD, val);
	अगर (ret != 3) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&client->dev, "failed to get dimensions: %d\n", error);
		वापस error;
	पूर्ण

	*max_x = (0x0f & val[0]) << 8 | val[1];
	*max_y = (0xf0 & val[0]) << 4 | val[2];

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_resolution(काष्ठा i2c_client *client,
				     u8 *hw_res_x, u8 *hw_res_y)
अणु
	पूर्णांक ret;
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	ret = i2c_smbus_पढ़ो_block_data(client, ETP_SMBUS_RESOLUTION_CMD, val);
	अगर (ret != 3) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&client->dev, "failed to get resolution: %d\n", error);
		वापस error;
	पूर्ण

	*hw_res_x = val[1] & 0x0F;
	*hw_res_y = (val[1] & 0xF0) >> 4;

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_num_traces(काष्ठा i2c_client *client,
				     अचिन्हित पूर्णांक *x_traces,
				     अचिन्हित पूर्णांक *y_traces)
अणु
	पूर्णांक ret;
	पूर्णांक error;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	ret = i2c_smbus_पढ़ो_block_data(client, ETP_SMBUS_XY_TRACENUM_CMD, val);
	अगर (ret != 3) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&client->dev, "failed to get trace info: %d\n", error);
		वापस error;
	पूर्ण

	*x_traces = val[1];
	*y_traces = val[2];

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_pressure_adjusपंचांगent(काष्ठा i2c_client *client,
					      पूर्णांक *adjusपंचांगent)
अणु
	*adjusपंचांगent = ETP_PRESSURE_OFFSET;
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_iap_get_mode(काष्ठा i2c_client *client,
				   क्रमागत tp_mode *mode)
अणु
	पूर्णांक error;
	u16 स्थिरant;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	error = i2c_smbus_पढ़ो_block_data(client, ETP_SMBUS_IAP_CTRL_CMD, val);
	अगर (error < 0) अणु
		dev_err(&client->dev, "failed to read iap ctrol register: %d\n",
			error);
		वापस error;
	पूर्ण

	स्थिरant = be16_to_cpup((__be16 *)val);
	dev_dbg(&client->dev, "iap control reg: 0x%04x.\n", स्थिरant);

	*mode = (स्थिरant & ETP_SMBUS_IAP_MODE_ON) ? IAP_MODE : MAIN_MODE;

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_iap_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte(client, ETP_SMBUS_IAP_RESET_CMD);
	अगर (error) अणु
		dev_err(&client->dev, "cannot reset IC: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_set_flash_key(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;
	u8 cmd[4] = अणु 0x00, 0x0B, 0x00, 0x5A पूर्ण;

	error = i2c_smbus_ग_लिखो_block_data(client, ETP_SMBUS_IAP_CMD,
					   माप(cmd), cmd);
	अगर (error) अणु
		dev_err(&client->dev, "cannot set flash key: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_prepare_fw_update(काष्ठा i2c_client *client, u16 ic_type,
					u8 iap_version, u16 fw_page_size)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक len;
	पूर्णांक error;
	क्रमागत tp_mode mode;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;
	u8 cmd[4] = अणु0x0F, 0x78, 0x00, 0x06पूर्ण;
	u16 password;

	/* Get FW in which mode	(IAP_MODE/MAIN_MODE)  */
	error = elan_smbus_iap_get_mode(client, &mode);
	अगर (error)
		वापस error;

	अगर (mode == MAIN_MODE) अणु

		/* set flash key */
		error = elan_smbus_set_flash_key(client);
		अगर (error)
			वापस error;

		/* ग_लिखो iap password */
		अगर (i2c_smbus_ग_लिखो_byte(client,
					 ETP_SMBUS_IAP_PASSWORD_WRITE) < 0) अणु
			dev_err(dev, "cannot write iap password\n");
			वापस -EIO;
		पूर्ण

		error = i2c_smbus_ग_लिखो_block_data(client, ETP_SMBUS_IAP_CMD,
						   माप(cmd), cmd);
		अगर (error) अणु
			dev_err(dev, "failed to write iap password: %d\n",
				error);
			वापस error;
		पूर्ण

		/*
		 * Read back password to make sure we enabled flash
		 * successfully.
		 */
		len = i2c_smbus_पढ़ो_block_data(client,
						ETP_SMBUS_IAP_PASSWORD_READ,
						val);
		अगर (len < (पूर्णांक)माप(u16)) अणु
			error = len < 0 ? len : -EIO;
			dev_err(dev, "failed to read iap password: %d\n",
				error);
			वापस error;
		पूर्ण

		password = be16_to_cpup((__be16 *)val);
		अगर (password != ETP_SMBUS_IAP_PASSWORD) अणु
			dev_err(dev, "wrong iap password = 0x%X\n", password);
			वापस -EIO;
		पूर्ण

		/* Wait 30ms क्रम MAIN_MODE change to IAP_MODE */
		msleep(30);
	पूर्ण

	error = elan_smbus_set_flash_key(client);
	अगर (error)
		वापस error;

	/* Reset IC */
	error = elan_smbus_iap_reset(client);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण


अटल पूर्णांक elan_smbus_ग_लिखो_fw_block(काष्ठा i2c_client *client, u16 fw_page_size,
				     स्थिर u8 *page, u16 checksum, पूर्णांक idx)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;
	u16 result;
	u8 val[I2C_SMBUS_BLOCK_MAX] = अणु0पूर्ण;

	/*
	 * Due to the limitation of smbus protocol limiting
	 * transfer to 32 bytes at a समय, we must split block
	 * in 2 transfers.
	 */
	error = i2c_smbus_ग_लिखो_block_data(client,
					   ETP_SMBUS_WRITE_FW_BLOCK,
					   fw_page_size / 2,
					   page);
	अगर (error) अणु
		dev_err(dev, "Failed to write page %d (part %d): %d\n",
			idx, 1, error);
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_block_data(client,
					   ETP_SMBUS_WRITE_FW_BLOCK,
					   fw_page_size / 2,
					   page + fw_page_size / 2);
	अगर (error) अणु
		dev_err(dev, "Failed to write page %d (part %d): %d\n",
			idx, 2, error);
		वापस error;
	पूर्ण


	/* Wait क्रम F/W to update one page ROM data. */
	usleep_range(8000, 10000);

	error = i2c_smbus_पढ़ो_block_data(client,
					  ETP_SMBUS_IAP_CTRL_CMD, val);
	अगर (error < 0) अणु
		dev_err(dev, "Failed to read IAP write result: %d\n",
			error);
		वापस error;
	पूर्ण

	result = be16_to_cpup((__be16 *)val);
	अगर (result & (ETP_FW_IAP_PAGE_ERR | ETP_FW_IAP_INTF_ERR)) अणु
		dev_err(dev, "IAP reports failed write: %04hx\n",
			result);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_report_features(काष्ठा i2c_client *client, u8 pattern,
					  अचिन्हित पूर्णांक *features,
					  अचिन्हित पूर्णांक *report_len)
अणु
	/*
	 * SMBus controllers with pattern 2 lack area info, as newer
	 * high-precision packets use that space क्रम coordinates.
	 */
	*features = pattern <= 0x01 ? ETP_FEATURE_REPORT_MK : 0;
	*report_len = ETP_SMBUS_REPORT_LEN;
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_report(काष्ठा i2c_client *client,
				 u8 *report, अचिन्हित पूर्णांक report_len)
अणु
	पूर्णांक len;

	BUILD_BUG_ON(I2C_SMBUS_BLOCK_MAX > ETP_SMBUS_REPORT_LEN);

	len = i2c_smbus_पढ़ो_block_data(client,
					ETP_SMBUS_PACKET_QUERY,
					&report[ETP_SMBUS_REPORT_OFFSET]);
	अगर (len < 0) अणु
		dev_err(&client->dev, "failed to read report data: %d\n", len);
		वापस len;
	पूर्ण

	अगर (report[ETP_REPORT_ID_OFFSET] == ETP_TP_REPORT_ID2)
		report_len = ETP_SMBUS_REPORT_LEN2;

	अगर (len != report_len) अणु
		dev_err(&client->dev,
			"wrong report length (%d vs %d expected)\n",
			len, report_len);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_finish_fw_update(काष्ठा i2c_client *client,
				       काष्ठा completion *fw_completion)
अणु
	/* No special handling unlike I2C transport */
	वापस 0;
पूर्ण

अटल पूर्णांक elan_smbus_get_pattern(काष्ठा i2c_client *client, u8 *pattern)
अणु
	*pattern = 0;
	वापस 0;
पूर्ण

स्थिर काष्ठा elan_transport_ops elan_smbus_ops = अणु
	.initialize		= elan_smbus_initialize,
	.sleep_control		= elan_smbus_sleep_control,
	.घातer_control		= elan_smbus_घातer_control,
	.set_mode		= elan_smbus_set_mode,

	.calibrate		= elan_smbus_calibrate,
	.calibrate_result	= elan_smbus_calibrate_result,

	.get_baseline_data	= elan_smbus_get_baseline_data,

	.get_version		= elan_smbus_get_version,
	.get_sm_version		= elan_smbus_get_sm_version,
	.get_product_id		= elan_smbus_get_product_id,
	.get_checksum		= elan_smbus_get_checksum,
	.get_pressure_adjusपंचांगent = elan_smbus_get_pressure_adjusपंचांगent,

	.get_max		= elan_smbus_get_max,
	.get_resolution		= elan_smbus_get_resolution,
	.get_num_traces		= elan_smbus_get_num_traces,

	.iap_get_mode		= elan_smbus_iap_get_mode,
	.iap_reset		= elan_smbus_iap_reset,

	.prepare_fw_update	= elan_smbus_prepare_fw_update,
	.ग_लिखो_fw_block		= elan_smbus_ग_लिखो_fw_block,
	.finish_fw_update	= elan_smbus_finish_fw_update,

	.get_report_features	= elan_smbus_get_report_features,
	.get_report		= elan_smbus_get_report,
	.get_pattern		= elan_smbus_get_pattern,
पूर्ण;
