<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Elan I2C/SMBus Touchpad driver
 *
 * Copyright (c) 2013 ELAN Microelectronics Corp.
 *
 * Author: ौौडॉघऐ (Duson Lin) <dusonlin@emc.com.tw>
 * Author: KT Liao <kt.liao@emc.com.tw>
 * Version: 1.6.3
 *
 * Based on cyapa driver:
 * copyright (c) 2011-2012 Cypress Semiconductor, Inc.
 * copyright (c) 2011-2012 Google, Inc.
 *
 * Trademarks are the property of their respective owners.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/input.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/completion.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "elan_i2c.h"

#घोषणा DRIVER_NAME		"elan_i2c"
#घोषणा ELAN_VENDOR_ID		0x04f3
#घोषणा ETP_MAX_PRESSURE	255
#घोषणा ETP_FWIDTH_REDUCE	90
#घोषणा ETP_FINGER_WIDTH	15
#घोषणा ETP_RETRY_COUNT		3

/* quirks to control the device */
#घोषणा ETP_QUIRK_QUICK_WAKEUP	BIT(0)

/* The मुख्य device काष्ठाure */
काष्ठा elan_tp_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input;
	काष्ठा input_dev	*tp_input; /* trackpoपूर्णांक input node */
	काष्ठा regulator	*vcc;

	स्थिर काष्ठा elan_transport_ops *ops;

	/* क्रम fw update */
	काष्ठा completion	fw_completion;
	bool			in_fw_update;

	काष्ठा mutex		sysfs_mutex;

	अचिन्हित पूर्णांक		max_x;
	अचिन्हित पूर्णांक		max_y;
	अचिन्हित पूर्णांक		width_x;
	अचिन्हित पूर्णांक		width_y;
	अचिन्हित पूर्णांक		x_res;
	अचिन्हित पूर्णांक		y_res;

	u8			pattern;
	u16			product_id;
	u8			fw_version;
	u8			sm_version;
	u8			iap_version;
	u16			fw_checksum;
	अचिन्हित पूर्णांक		report_features;
	अचिन्हित पूर्णांक		report_len;
	पूर्णांक			pressure_adjusपंचांगent;
	u8			mode;
	u16			ic_type;
	u16			fw_validpage_count;
	u16			fw_page_size;
	u32			fw_signature_address;

	bool			irq_wake;

	u8			min_baseline;
	u8			max_baseline;
	bool			baseline_पढ़ोy;
	u8			clickpad;
	bool			middle_button;

	u32			quirks;		/* Various quirks */
पूर्ण;

अटल u32 elan_i2c_lookup_quirks(u16 ic_type, u16 product_id)
अणु
	अटल स्थिर काष्ठा अणु
		u16 ic_type;
		u16 product_id;
		u32 quirks;
	पूर्ण elan_i2c_quirks[] = अणु
		अणु 0x0D, ETP_PRODUCT_ID_DELBIN, ETP_QUIRK_QUICK_WAKEUP पूर्ण,
		अणु 0x10, ETP_PRODUCT_ID_VOXEL, ETP_QUIRK_QUICK_WAKEUP पूर्ण,
		अणु 0x14, ETP_PRODUCT_ID_MAGPIE, ETP_QUIRK_QUICK_WAKEUP पूर्ण,
		अणु 0x14, ETP_PRODUCT_ID_BOBBA, ETP_QUIRK_QUICK_WAKEUP पूर्ण,
	पूर्ण;
	u32 quirks = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(elan_i2c_quirks); i++) अणु
		अगर (elan_i2c_quirks[i].ic_type == ic_type &&
		    elan_i2c_quirks[i].product_id == product_id) अणु
			quirks = elan_i2c_quirks[i].quirks;
		पूर्ण
	पूर्ण

	अगर (ic_type >= 0x0D && product_id >= 0x123)
		quirks |= ETP_QUIRK_QUICK_WAKEUP;

	वापस quirks;
पूर्ण

अटल पूर्णांक elan_get_fwinfo(u16 ic_type, u8 iap_version, u16 *validpage_count,
			   u32 *signature_address, u16 *page_size)
अणु
	चयन (ic_type) अणु
	हाल 0x00:
	हाल 0x06:
	हाल 0x08:
		*validpage_count = 512;
		अवरोध;
	हाल 0x03:
	हाल 0x07:
	हाल 0x09:
	हाल 0x0A:
	हाल 0x0B:
	हाल 0x0C:
		*validpage_count = 768;
		अवरोध;
	हाल 0x0D:
		*validpage_count = 896;
		अवरोध;
	हाल 0x0E:
		*validpage_count = 640;
		अवरोध;
	हाल 0x10:
		*validpage_count = 1024;
		अवरोध;
	हाल 0x11:
		*validpage_count = 1280;
		अवरोध;
	हाल 0x13:
		*validpage_count = 2048;
		अवरोध;
	हाल 0x14:
	हाल 0x15:
		*validpage_count = 1024;
		अवरोध;
	शेष:
		/* unknown ic type clear value */
		*validpage_count = 0;
		*signature_address = 0;
		*page_size = 0;
		वापस -ENXIO;
	पूर्ण

	*signature_address =
		(*validpage_count * ETP_FW_PAGE_SIZE) - ETP_FW_SIGNATURE_SIZE;

	अगर ((ic_type == 0x14 || ic_type == 0x15) && iap_version >= 2) अणु
		*validpage_count /= 8;
		*page_size = ETP_FW_PAGE_SIZE_512;
	पूर्ण अन्यथा अगर (ic_type >= 0x0D && iap_version >= 1) अणु
		*validpage_count /= 2;
		*page_size = ETP_FW_PAGE_SIZE_128;
	पूर्ण अन्यथा अणु
		*page_size = ETP_FW_PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_enable_घातer(काष्ठा elan_tp_data *data)
अणु
	पूर्णांक repeat = ETP_RETRY_COUNT;
	पूर्णांक error;

	error = regulator_enable(data->vcc);
	अगर (error) अणु
		dev_err(&data->client->dev,
			"failed to enable regulator: %d\n", error);
		वापस error;
	पूर्ण

	करो अणु
		error = data->ops->घातer_control(data->client, true);
		अगर (error >= 0)
			वापस 0;

		msleep(30);
	पूर्ण जबतक (--repeat > 0);

	dev_err(&data->client->dev, "failed to enable power: %d\n", error);
	वापस error;
पूर्ण

अटल पूर्णांक elan_disable_घातer(काष्ठा elan_tp_data *data)
अणु
	पूर्णांक repeat = ETP_RETRY_COUNT;
	पूर्णांक error;

	करो अणु
		error = data->ops->घातer_control(data->client, false);
		अगर (!error) अणु
			error = regulator_disable(data->vcc);
			अगर (error) अणु
				dev_err(&data->client->dev,
					"failed to disable regulator: %d\n",
					error);
				/* Attempt to घातer the chip back up */
				data->ops->घातer_control(data->client, true);
				अवरोध;
			पूर्ण

			वापस 0;
		पूर्ण

		msleep(30);
	पूर्ण जबतक (--repeat > 0);

	dev_err(&data->client->dev, "failed to disable power: %d\n", error);
	वापस error;
पूर्ण

अटल पूर्णांक elan_sleep(काष्ठा elan_tp_data *data)
अणु
	पूर्णांक repeat = ETP_RETRY_COUNT;
	पूर्णांक error;

	करो अणु
		error = data->ops->sleep_control(data->client, true);
		अगर (!error)
			वापस 0;

		msleep(30);
	पूर्ण जबतक (--repeat > 0);

	वापस error;
पूर्ण

अटल पूर्णांक elan_query_product(काष्ठा elan_tp_data *data)
अणु
	पूर्णांक error;

	error = data->ops->get_product_id(data->client, &data->product_id);
	अगर (error)
		वापस error;

	error = data->ops->get_pattern(data->client, &data->pattern);
	अगर (error)
		वापस error;

	error = data->ops->get_sm_version(data->client, data->pattern,
					  &data->ic_type, &data->sm_version,
					  &data->clickpad);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक elan_check_ASUS_special_fw(काष्ठा elan_tp_data *data)
अणु
	अगर (data->ic_type == 0x0E) अणु
		चयन (data->product_id) अणु
		हाल 0x05 ... 0x07:
		हाल 0x09:
		हाल 0x13:
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अगर (data->ic_type == 0x08 && data->product_id == 0x26) अणु
		/* ASUS EeeBook X205TA */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __elan_initialize(काष्ठा elan_tp_data *data, bool skip_reset)
अणु
	काष्ठा i2c_client *client = data->client;
	bool woken_up = false;
	पूर्णांक error;

	अगर (!skip_reset) अणु
		error = data->ops->initialize(client);
		अगर (error) अणु
			dev_err(&client->dev, "device initialize failed: %d\n", error);
			वापस error;
		पूर्ण
	पूर्ण

	error = elan_query_product(data);
	अगर (error)
		वापस error;

	/*
	 * Some ASUS devices were shipped with firmware that requires
	 * touchpads to be woken up first, beक्रमe attempting to चयन
	 * them पूर्णांकo असलolute reporting mode.
	 */
	अगर (elan_check_ASUS_special_fw(data)) अणु
		error = data->ops->sleep_control(client, false);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to wake device up: %d\n", error);
			वापस error;
		पूर्ण

		msleep(200);
		woken_up = true;
	पूर्ण

	data->mode |= ETP_ENABLE_ABS;
	error = data->ops->set_mode(client, data->mode);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to switch to absolute mode: %d\n", error);
		वापस error;
	पूर्ण

	अगर (!woken_up) अणु
		error = data->ops->sleep_control(client, false);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to wake device up: %d\n", error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_initialize(काष्ठा elan_tp_data *data, bool skip_reset)
अणु
	पूर्णांक repeat = ETP_RETRY_COUNT;
	पूर्णांक error;

	करो अणु
		error = __elan_initialize(data, skip_reset);
		अगर (!error)
			वापस 0;

		skip_reset = false;
		msleep(30);
	पूर्ण जबतक (--repeat > 0);

	वापस error;
पूर्ण

अटल पूर्णांक elan_query_device_info(काष्ठा elan_tp_data *data)
अणु
	पूर्णांक error;

	error = data->ops->get_version(data->client, data->pattern, false,
				       &data->fw_version);
	अगर (error)
		वापस error;

	error = data->ops->get_checksum(data->client, false,
					&data->fw_checksum);
	अगर (error)
		वापस error;

	error = data->ops->get_version(data->client, data->pattern,
				       true, &data->iap_version);
	अगर (error)
		वापस error;

	error = data->ops->get_pressure_adjusपंचांगent(data->client,
						   &data->pressure_adjusपंचांगent);
	अगर (error)
		वापस error;

	error = data->ops->get_report_features(data->client, data->pattern,
					       &data->report_features,
					       &data->report_len);
	अगर (error)
		वापस error;

	data->quirks = elan_i2c_lookup_quirks(data->ic_type, data->product_id);

	error = elan_get_fwinfo(data->ic_type, data->iap_version,
				&data->fw_validpage_count,
				&data->fw_signature_address,
				&data->fw_page_size);
	अगर (error)
		dev_warn(&data->client->dev,
			 "unexpected iap version %#04x (ic type: %#04x), firmware update will not work\n",
			 data->iap_version, data->ic_type);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक elan_convert_resolution(u8 val, u8 pattern)
अणु
	/*
	 * pattern <= 0x01:
	 *	(value from firmware) * 10 + 790 = dpi
	 * अन्यथा
	 *	((value from firmware) + 3) * 100 = dpi
	 */
	पूर्णांक res = pattern <= 0x01 ?
		(पूर्णांक)(अक्षर)val * 10 + 790 : ((पूर्णांक)(अक्षर)val + 3) * 100;
	/*
	 * We also have to convert dpi to करोts/mm (*10/254 to aव्योम भग्नing
	 * poपूर्णांक).
	 */
	वापस res * 10 / 254;
पूर्ण

अटल पूर्णांक elan_query_device_parameters(काष्ठा elan_tp_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	अचिन्हित पूर्णांक x_traces, y_traces;
	u32 x_mm, y_mm;
	u8 hw_x_res, hw_y_res;
	पूर्णांक error;

	अगर (device_property_पढ़ो_u32(&client->dev,
				     "touchscreen-size-x", &data->max_x) ||
	    device_property_पढ़ो_u32(&client->dev,
				     "touchscreen-size-y", &data->max_y)) अणु
		error = data->ops->get_max(data->client,
					   &data->max_x,
					   &data->max_y);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		/* size is the maximum + 1 */
		--data->max_x;
		--data->max_y;
	पूर्ण

	अगर (device_property_पढ़ो_u32(&client->dev,
				     "elan,x_traces",
				     &x_traces) ||
	    device_property_पढ़ो_u32(&client->dev,
				     "elan,y_traces",
				     &y_traces)) अणु
		error = data->ops->get_num_traces(data->client,
						  &x_traces, &y_traces);
		अगर (error)
			वापस error;
	पूर्ण
	data->width_x = data->max_x / x_traces;
	data->width_y = data->max_y / y_traces;

	अगर (device_property_पढ़ो_u32(&client->dev,
				     "touchscreen-x-mm", &x_mm) ||
	    device_property_पढ़ो_u32(&client->dev,
				     "touchscreen-y-mm", &y_mm)) अणु
		error = data->ops->get_resolution(data->client,
						  &hw_x_res, &hw_y_res);
		अगर (error)
			वापस error;

		data->x_res = elan_convert_resolution(hw_x_res, data->pattern);
		data->y_res = elan_convert_resolution(hw_y_res, data->pattern);
	पूर्ण अन्यथा अणु
		data->x_res = (data->max_x + 1) / x_mm;
		data->y_res = (data->max_y + 1) / y_mm;
	पूर्ण

	अगर (device_property_पढ़ो_bool(&client->dev, "elan,clickpad"))
		data->clickpad = 1;

	अगर (device_property_पढ़ो_bool(&client->dev, "elan,middle-button"))
		data->middle_button = true;

	वापस 0;
पूर्ण

/*
 **********************************************************
 * IAP firmware updater related routines
 **********************************************************
 */
अटल पूर्णांक elan_ग_लिखो_fw_block(काष्ठा elan_tp_data *data, u16 page_size,
			       स्थिर u8 *page, u16 checksum, पूर्णांक idx)
अणु
	पूर्णांक retry = ETP_RETRY_COUNT;
	पूर्णांक error;

	करो अणु
		error = data->ops->ग_लिखो_fw_block(data->client, page_size,
						  page, checksum, idx);
		अगर (!error)
			वापस 0;

		dev_dbg(&data->client->dev,
			"IAP retrying page %d (error: %d)\n", idx, error);
	पूर्ण जबतक (--retry > 0);

	वापस error;
पूर्ण

अटल पूर्णांक __elan_update_firmware(काष्ठा elan_tp_data *data,
				  स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_client *client = data->client;
	काष्ठा device *dev = &client->dev;
	पूर्णांक i, j;
	पूर्णांक error;
	u16 iap_start_addr;
	u16 boot_page_count;
	u16 sw_checksum = 0, fw_checksum = 0;

	error = data->ops->prepare_fw_update(client, data->ic_type,
					     data->iap_version,
					     data->fw_page_size);
	अगर (error)
		वापस error;

	iap_start_addr = get_unaligned_le16(&fw->data[ETP_IAP_START_ADDR * 2]);

	boot_page_count = (iap_start_addr * 2) / data->fw_page_size;
	क्रम (i = boot_page_count; i < data->fw_validpage_count; i++) अणु
		u16 checksum = 0;
		स्थिर u8 *page = &fw->data[i * data->fw_page_size];

		क्रम (j = 0; j < data->fw_page_size; j += 2)
			checksum += ((page[j + 1] << 8) | page[j]);

		error = elan_ग_लिखो_fw_block(data, data->fw_page_size,
					    page, checksum, i);
		अगर (error) अणु
			dev_err(dev, "write page %d fail: %d\n", i, error);
			वापस error;
		पूर्ण

		sw_checksum += checksum;
	पूर्ण

	/* Wait WDT reset and घातer on reset */
	msleep(600);

	error = data->ops->finish_fw_update(client, &data->fw_completion);
	अगर (error)
		वापस error;

	error = data->ops->get_checksum(client, true, &fw_checksum);
	अगर (error)
		वापस error;

	अगर (sw_checksum != fw_checksum) अणु
		dev_err(dev, "checksum diff sw=[%04X], fw=[%04X]\n",
			sw_checksum, fw_checksum);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elan_update_firmware(काष्ठा elan_tp_data *data,
				स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक retval;

	dev_dbg(&client->dev, "Starting firmware update....\n");

	disable_irq(client->irq);
	data->in_fw_update = true;

	retval = __elan_update_firmware(data, fw);
	अगर (retval) अणु
		dev_err(&client->dev, "firmware update failed: %d\n", retval);
		data->ops->iap_reset(client);
	पूर्ण अन्यथा अणु
		/* Reinitialize TP after fw is updated */
		elan_initialize(data, false);
		elan_query_device_info(data);
	पूर्ण

	data->in_fw_update = false;
	enable_irq(client->irq);

	वापस retval;
पूर्ण

/*
 *******************************************************************
 * SYSFS attributes
 *******************************************************************
 */
अटल sमाप_प्रकार elan_sysfs_पढ़ो_fw_checksum(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "0x%04x\n", data->fw_checksum);
पूर्ण

अटल sमाप_प्रकार elan_sysfs_पढ़ो_product_id(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, ETP_PRODUCT_ID_FORMAT_STRING "\n",
		       data->product_id);
पूर्ण

अटल sमाप_प्रकार elan_sysfs_पढ़ो_fw_ver(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d.0\n", data->fw_version);
पूर्ण

अटल sमाप_प्रकार elan_sysfs_पढ़ो_sm_ver(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d.0\n", data->sm_version);
पूर्ण

अटल sमाप_प्रकार elan_sysfs_पढ़ो_iap_ver(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d.0\n", data->iap_version);
पूर्ण

अटल sमाप_प्रकार elan_sysfs_update_fw(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा elan_tp_data *data = dev_get_drvdata(dev);
	स्थिर काष्ठा firmware *fw;
	अक्षर *fw_name;
	पूर्णांक error;
	स्थिर u8 *fw_signature;
	अटल स्थिर u8 signature[] = अणु0xAA, 0x55, 0xCC, 0x33, 0xFF, 0xFFपूर्ण;

	अगर (data->fw_validpage_count == 0)
		वापस -EINVAL;

	/* Look क्रम a firmware with the product id appended. */
	fw_name = kaप्र_लिखो(GFP_KERNEL, ETP_FW_NAME, data->product_id);
	अगर (!fw_name) अणु
		dev_err(dev, "failed to allocate memory for firmware name\n");
		वापस -ENOMEM;
	पूर्ण

	dev_info(dev, "requesting fw '%s'\n", fw_name);
	error = request_firmware(&fw, fw_name, dev);
	kमुक्त(fw_name);
	अगर (error) अणु
		dev_err(dev, "failed to request firmware: %d\n", error);
		वापस error;
	पूर्ण

	/* Firmware file must match signature data */
	fw_signature = &fw->data[data->fw_signature_address];
	अगर (स_भेद(fw_signature, signature, माप(signature)) != 0) अणु
		dev_err(dev, "signature mismatch (expected %*ph, got %*ph)\n",
			(पूर्णांक)माप(signature), signature,
			(पूर्णांक)माप(signature), fw_signature);
		error = -EBADF;
		जाओ out_release_fw;
	पूर्ण

	error = mutex_lock_पूर्णांकerruptible(&data->sysfs_mutex);
	अगर (error)
		जाओ out_release_fw;

	error = elan_update_firmware(data, fw);

	mutex_unlock(&data->sysfs_mutex);

out_release_fw:
	release_firmware(fw);
	वापस error ?: count;
पूर्ण

अटल sमाप_प्रकार calibrate_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);
	पूर्णांक tries = 20;
	पूर्णांक retval;
	पूर्णांक error;
	u8 val[ETP_CALIBRATE_MAX_LEN];

	retval = mutex_lock_पूर्णांकerruptible(&data->sysfs_mutex);
	अगर (retval)
		वापस retval;

	disable_irq(client->irq);

	data->mode |= ETP_ENABLE_CALIBRATE;
	retval = data->ops->set_mode(client, data->mode);
	अगर (retval) अणु
		dev_err(dev, "failed to enable calibration mode: %d\n",
			retval);
		जाओ out;
	पूर्ण

	retval = data->ops->calibrate(client);
	अगर (retval) अणु
		dev_err(dev, "failed to start calibration: %d\n",
			retval);
		जाओ out_disable_calibrate;
	पूर्ण

	val[0] = 0xff;
	करो अणु
		/* Wait 250ms beक्रमe checking अगर calibration has completed. */
		msleep(250);

		retval = data->ops->calibrate_result(client, val);
		अगर (retval)
			dev_err(dev, "failed to check calibration result: %d\n",
				retval);
		अन्यथा अगर (val[0] == 0)
			अवरोध; /* calibration करोne */

	पूर्ण जबतक (--tries);

	अगर (tries == 0) अणु
		dev_err(dev, "failed to calibrate. Timeout.\n");
		retval = -ETIMEDOUT;
	पूर्ण

out_disable_calibrate:
	data->mode &= ~ETP_ENABLE_CALIBRATE;
	error = data->ops->set_mode(data->client, data->mode);
	अगर (error) अणु
		dev_err(dev, "failed to disable calibration mode: %d\n",
			error);
		अगर (!retval)
			retval = error;
	पूर्ण
out:
	enable_irq(client->irq);
	mutex_unlock(&data->sysfs_mutex);
	वापस retval ?: count;
पूर्ण

अटल sमाप_प्रकार elan_sysfs_पढ़ो_mode(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);
	पूर्णांक error;
	क्रमागत tp_mode mode;

	error = mutex_lock_पूर्णांकerruptible(&data->sysfs_mutex);
	अगर (error)
		वापस error;

	error = data->ops->iap_get_mode(data->client, &mode);

	mutex_unlock(&data->sysfs_mutex);

	अगर (error)
		वापस error;

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)mode);
पूर्ण

अटल DEVICE_ATTR(product_id, S_IRUGO, elan_sysfs_पढ़ो_product_id, शून्य);
अटल DEVICE_ATTR(firmware_version, S_IRUGO, elan_sysfs_पढ़ो_fw_ver, शून्य);
अटल DEVICE_ATTR(sample_version, S_IRUGO, elan_sysfs_पढ़ो_sm_ver, शून्य);
अटल DEVICE_ATTR(iap_version, S_IRUGO, elan_sysfs_पढ़ो_iap_ver, शून्य);
अटल DEVICE_ATTR(fw_checksum, S_IRUGO, elan_sysfs_पढ़ो_fw_checksum, शून्य);
अटल DEVICE_ATTR(mode, S_IRUGO, elan_sysfs_पढ़ो_mode, शून्य);
अटल DEVICE_ATTR(update_fw, S_IWUSR, शून्य, elan_sysfs_update_fw);

अटल DEVICE_ATTR_WO(calibrate);

अटल काष्ठा attribute *elan_sysfs_entries[] = अणु
	&dev_attr_product_id.attr,
	&dev_attr_firmware_version.attr,
	&dev_attr_sample_version.attr,
	&dev_attr_iap_version.attr,
	&dev_attr_fw_checksum.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_mode.attr,
	&dev_attr_update_fw.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group elan_sysfs_group = अणु
	.attrs = elan_sysfs_entries,
पूर्ण;

अटल sमाप_प्रकार acquire_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);
	पूर्णांक error;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&data->sysfs_mutex);
	अगर (retval)
		वापस retval;

	disable_irq(client->irq);

	data->baseline_पढ़ोy = false;

	data->mode |= ETP_ENABLE_CALIBRATE;
	retval = data->ops->set_mode(data->client, data->mode);
	अगर (retval) अणु
		dev_err(dev, "Failed to enable calibration mode to get baseline: %d\n",
			retval);
		जाओ out;
	पूर्ण

	msleep(250);

	retval = data->ops->get_baseline_data(data->client, true,
					      &data->max_baseline);
	अगर (retval) अणु
		dev_err(dev, "Failed to read max baseline form device: %d\n",
			retval);
		जाओ out_disable_calibrate;
	पूर्ण

	retval = data->ops->get_baseline_data(data->client, false,
					      &data->min_baseline);
	अगर (retval) अणु
		dev_err(dev, "Failed to read min baseline form device: %d\n",
			retval);
		जाओ out_disable_calibrate;
	पूर्ण

	data->baseline_पढ़ोy = true;

out_disable_calibrate:
	data->mode &= ~ETP_ENABLE_CALIBRATE;
	error = data->ops->set_mode(data->client, data->mode);
	अगर (error) अणु
		dev_err(dev, "Failed to disable calibration mode after acquiring baseline: %d\n",
			error);
		अगर (!retval)
			retval = error;
	पूर्ण
out:
	enable_irq(client->irq);
	mutex_unlock(&data->sysfs_mutex);
	वापस retval ?: count;
पूर्ण

अटल sमाप_प्रकार min_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&data->sysfs_mutex);
	अगर (retval)
		वापस retval;

	अगर (!data->baseline_पढ़ोy) अणु
		retval = -ENODATA;
		जाओ out;
	पूर्ण

	retval = snम_लिखो(buf, PAGE_SIZE, "%d", data->min_baseline);

out:
	mutex_unlock(&data->sysfs_mutex);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार max_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&data->sysfs_mutex);
	अगर (retval)
		वापस retval;

	अगर (!data->baseline_पढ़ोy) अणु
		retval = -ENODATA;
		जाओ out;
	पूर्ण

	retval = snम_लिखो(buf, PAGE_SIZE, "%d", data->max_baseline);

out:
	mutex_unlock(&data->sysfs_mutex);
	वापस retval;
पूर्ण


अटल DEVICE_ATTR_WO(acquire);
अटल DEVICE_ATTR_RO(min);
अटल DEVICE_ATTR_RO(max);

अटल काष्ठा attribute *elan_baseline_sysfs_entries[] = अणु
	&dev_attr_acquire.attr,
	&dev_attr_min.attr,
	&dev_attr_max.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group elan_baseline_sysfs_group = अणु
	.name = "baseline",
	.attrs = elan_baseline_sysfs_entries,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *elan_sysfs_groups[] = अणु
	&elan_sysfs_group,
	&elan_baseline_sysfs_group,
	शून्य
पूर्ण;

/*
 ******************************************************************
 * Elan isr functions
 ******************************************************************
 */
अटल व्योम elan_report_contact(काष्ठा elan_tp_data *data, पूर्णांक contact_num,
				bool contact_valid, bool high_precision,
				u8 *packet, u8 *finger_data)
अणु
	काष्ठा input_dev *input = data->input;
	अचिन्हित पूर्णांक pos_x, pos_y;
	अचिन्हित पूर्णांक pressure, scaled_pressure;

	अगर (contact_valid) अणु
		अगर (high_precision) अणु
			pos_x = get_unaligned_be16(&finger_data[0]);
			pos_y = get_unaligned_be16(&finger_data[2]);
		पूर्ण अन्यथा अणु
			pos_x = ((finger_data[0] & 0xf0) << 4) | finger_data[1];
			pos_y = ((finger_data[0] & 0x0f) << 8) | finger_data[2];
		पूर्ण

		अगर (pos_x > data->max_x || pos_y > data->max_y) अणु
			dev_dbg(input->dev.parent,
				"[%d] x=%d y=%d over max (%d, %d)",
				contact_num, pos_x, pos_y,
				data->max_x, data->max_y);
			वापस;
		पूर्ण

		pressure = finger_data[4];
		scaled_pressure = pressure + data->pressure_adjusपंचांगent;
		अगर (scaled_pressure > ETP_MAX_PRESSURE)
			scaled_pressure = ETP_MAX_PRESSURE;

		input_mt_slot(input, contact_num);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_असल(input, ABS_MT_POSITION_X, pos_x);
		input_report_असल(input, ABS_MT_POSITION_Y, data->max_y - pos_y);
		input_report_असल(input, ABS_MT_PRESSURE, scaled_pressure);

		अगर (data->report_features & ETP_FEATURE_REPORT_MK) अणु
			अचिन्हित पूर्णांक mk_x, mk_y, area_x, area_y;
			u8 mk_data = high_precision ?
				packet[ETP_MK_DATA_OFFSET + contact_num] :
				finger_data[3];

			mk_x = mk_data & 0x0f;
			mk_y = mk_data >> 4;

			/*
			 * To aव्योम treating large finger as palm, let's reduce
			 * the width x and y per trace.
			 */
			area_x = mk_x * (data->width_x - ETP_FWIDTH_REDUCE);
			area_y = mk_y * (data->width_y - ETP_FWIDTH_REDUCE);

			input_report_असल(input, ABS_TOOL_WIDTH, mk_x);
			input_report_असल(input, ABS_MT_TOUCH_MAJOR,
					 max(area_x, area_y));
			input_report_असल(input, ABS_MT_TOUCH_MINOR,
					 min(area_x, area_y));
		पूर्ण
	पूर्ण अन्यथा अणु
		input_mt_slot(input, contact_num);
		input_mt_report_slot_inactive(input);
	पूर्ण
पूर्ण

अटल व्योम elan_report_असलolute(काष्ठा elan_tp_data *data, u8 *packet,
				 bool high_precision)
अणु
	काष्ठा input_dev *input = data->input;
	u8 *finger_data = &packet[ETP_FINGER_DATA_OFFSET];
	पूर्णांक i;
	u8 tp_info = packet[ETP_TOUCH_INFO_OFFSET];
	u8 hover_info = packet[ETP_HOVER_INFO_OFFSET];
	bool contact_valid, hover_event;

	pm_wakeup_event(&data->client->dev, 0);

	hover_event = hover_info & BIT(6);

	क्रम (i = 0; i < ETP_MAX_FINGERS; i++) अणु
		contact_valid = tp_info & BIT(3 + i);
		elan_report_contact(data, i, contact_valid, high_precision,
				    packet, finger_data);
		अगर (contact_valid)
			finger_data += ETP_FINGER_DATA_LEN;
	पूर्ण

	input_report_key(input, BTN_LEFT,   tp_info & BIT(0));
	input_report_key(input, BTN_MIDDLE, tp_info & BIT(2));
	input_report_key(input, BTN_RIGHT,  tp_info & BIT(1));
	input_report_असल(input, ABS_DISTANCE, hover_event != 0);
	input_mt_report_poपूर्णांकer_emulation(input, true);
	input_sync(input);
पूर्ण

अटल व्योम elan_report_trackpoपूर्णांक(काष्ठा elan_tp_data *data, u8 *report)
अणु
	काष्ठा input_dev *input = data->tp_input;
	u8 *packet = &report[ETP_REPORT_ID_OFFSET + 1];
	पूर्णांक x, y;

	pm_wakeup_event(&data->client->dev, 0);

	अगर (!data->tp_input) अणु
		dev_warn_once(&data->client->dev,
			      "received a trackpoint report while no trackpoint device has been created. Please report upstream.\n");
		वापस;
	पूर्ण

	input_report_key(input, BTN_LEFT, packet[0] & 0x01);
	input_report_key(input, BTN_RIGHT, packet[0] & 0x02);
	input_report_key(input, BTN_MIDDLE, packet[0] & 0x04);

	अगर ((packet[3] & 0x0F) == 0x06) अणु
		x = packet[4] - (पूर्णांक)((packet[1] ^ 0x80) << 1);
		y = (पूर्णांक)((packet[2] ^ 0x80) << 1) - packet[5];

		input_report_rel(input, REL_X, x);
		input_report_rel(input, REL_Y, y);
	पूर्ण

	input_sync(input);
पूर्ण

अटल irqवापस_t elan_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा elan_tp_data *data = dev_id;
	पूर्णांक error;
	u8 report[ETP_MAX_REPORT_LEN];

	/*
	 * When device is connected to i2c bus, when all IAP page ग_लिखोs
	 * complete, the driver will receive पूर्णांकerrupt and must पढ़ो
	 * 0000 to confirm that IAP is finished.
	*/
	अगर (data->in_fw_update) अणु
		complete(&data->fw_completion);
		जाओ out;
	पूर्ण

	error = data->ops->get_report(data->client, report, data->report_len);
	अगर (error)
		जाओ out;

	चयन (report[ETP_REPORT_ID_OFFSET]) अणु
	हाल ETP_REPORT_ID:
		elan_report_असलolute(data, report, false);
		अवरोध;
	हाल ETP_REPORT_ID2:
		elan_report_असलolute(data, report, true);
		अवरोध;
	हाल ETP_TP_REPORT_ID:
	हाल ETP_TP_REPORT_ID2:
		elan_report_trackpoपूर्णांक(data, report);
		अवरोध;
	शेष:
		dev_err(&data->client->dev, "invalid report id data (%x)\n",
			report[ETP_REPORT_ID_OFFSET]);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 ******************************************************************
 * Elan initialization functions
 ******************************************************************
 */

अटल पूर्णांक elan_setup_trackpoपूर्णांक_input_device(काष्ठा elan_tp_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा input_dev *input;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Elan TrackPoint";
	input->id.bustype = BUS_I2C;
	input->id.venकरोr = ELAN_VENDOR_ID;
	input->id.product = data->product_id;
	input_set_drvdata(input, data);

	input_set_capability(input, EV_REL, REL_X);
	input_set_capability(input, EV_REL, REL_Y);
	input_set_capability(input, EV_KEY, BTN_LEFT);
	input_set_capability(input, EV_KEY, BTN_RIGHT);
	input_set_capability(input, EV_KEY, BTN_MIDDLE);

	__set_bit(INPUT_PROP_POINTER, input->propbit);
	__set_bit(INPUT_PROP_POINTING_STICK, input->propbit);

	data->tp_input = input;

	वापस 0;
पूर्ण

अटल पूर्णांक elan_setup_input_device(काष्ठा elan_tp_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा input_dev *input;
	अचिन्हित पूर्णांक max_width = max(data->width_x, data->width_y);
	अचिन्हित पूर्णांक min_width = min(data->width_x, data->width_y);
	पूर्णांक error;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Elan Touchpad";
	input->id.bustype = BUS_I2C;
	input->id.venकरोr = ELAN_VENDOR_ID;
	input->id.product = data->product_id;
	input_set_drvdata(input, data);

	error = input_mt_init_slots(input, ETP_MAX_FINGERS,
				    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(dev, "failed to initialize MT slots: %d\n", error);
		वापस error;
	पूर्ण

	__set_bit(EV_ABS, input->evbit);
	__set_bit(INPUT_PROP_POINTER, input->propbit);
	अगर (data->clickpad) अणु
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);
	पूर्ण अन्यथा अणु
		__set_bit(BTN_RIGHT, input->keybit);
		अगर (data->middle_button)
			__set_bit(BTN_MIDDLE, input->keybit);
	पूर्ण
	__set_bit(BTN_LEFT, input->keybit);

	/* Set up ST parameters */
	input_set_असल_params(input, ABS_X, 0, data->max_x, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, data->max_y, 0, 0);
	input_असल_set_res(input, ABS_X, data->x_res);
	input_असल_set_res(input, ABS_Y, data->y_res);
	input_set_असल_params(input, ABS_PRESSURE, 0, ETP_MAX_PRESSURE, 0, 0);
	अगर (data->report_features & ETP_FEATURE_REPORT_MK)
		input_set_असल_params(input, ABS_TOOL_WIDTH,
				     0, ETP_FINGER_WIDTH, 0, 0);
	input_set_असल_params(input, ABS_DISTANCE, 0, 1, 0, 0);

	/* And MT parameters */
	input_set_असल_params(input, ABS_MT_POSITION_X, 0, data->max_x, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, data->max_y, 0, 0);
	input_असल_set_res(input, ABS_MT_POSITION_X, data->x_res);
	input_असल_set_res(input, ABS_MT_POSITION_Y, data->y_res);
	input_set_असल_params(input, ABS_MT_PRESSURE, 0,
			     ETP_MAX_PRESSURE, 0, 0);
	अगर (data->report_features & ETP_FEATURE_REPORT_MK) अणु
		input_set_असल_params(input, ABS_MT_TOUCH_MAJOR,
				     0, ETP_FINGER_WIDTH * max_width, 0, 0);
		input_set_असल_params(input, ABS_MT_TOUCH_MINOR,
				     0, ETP_FINGER_WIDTH * min_width, 0, 0);
	पूर्ण

	data->input = input;

	वापस 0;
पूर्ण

अटल व्योम elan_disable_regulator(व्योम *_data)
अणु
	काष्ठा elan_tp_data *data = _data;

	regulator_disable(data->vcc);
पूर्ण

अटल पूर्णांक elan_probe(काष्ठा i2c_client *client,
		      स्थिर काष्ठा i2c_device_id *dev_id)
अणु
	स्थिर काष्ठा elan_transport_ops *transport_ops;
	काष्ठा device *dev = &client->dev;
	काष्ठा elan_tp_data *data;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक error;

	अगर (IS_ENABLED(CONFIG_MOUSE_ELAN_I2C_I2C) &&
	    i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		transport_ops = &elan_i2c_ops;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_MOUSE_ELAN_I2C_SMBUS) &&
		   i2c_check_functionality(client->adapter,
					   I2C_FUNC_SMBUS_BYTE_DATA |
						I2C_FUNC_SMBUS_BLOCK_DATA |
						I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		transport_ops = &elan_smbus_ops;
	पूर्ण अन्यथा अणु
		dev_err(dev, "not a supported I2C/SMBus adapter\n");
		वापस -EIO;
	पूर्ण

	data = devm_kzalloc(dev, माप(काष्ठा elan_tp_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);

	data->ops = transport_ops;
	data->client = client;
	init_completion(&data->fw_completion);
	mutex_init(&data->sysfs_mutex);

	data->vcc = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(data->vcc)) अणु
		error = PTR_ERR(data->vcc);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'vcc' regulator: %d\n",
				error);
		वापस error;
	पूर्ण

	error = regulator_enable(data->vcc);
	अगर (error) अणु
		dev_err(dev, "Failed to enable regulator: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(dev, elan_disable_regulator, data);
	अगर (error) अणु
		dev_err(dev, "Failed to add disable regulator action: %d\n",
			error);
		वापस error;
	पूर्ण

	/* Make sure there is something at this address */
	error = i2c_smbus_पढ़ो_byte(client);
	अगर (error < 0) अणु
		dev_dbg(&client->dev, "nothing at this address: %d\n", error);
		वापस -ENXIO;
	पूर्ण

	/* Initialize the touchpad. */
	error = elan_initialize(data, false);
	अगर (error)
		वापस error;

	error = elan_query_device_info(data);
	अगर (error)
		वापस error;

	error = elan_query_device_parameters(data);
	अगर (error)
		वापस error;

	dev_info(dev,
		 "Elan Touchpad: Module ID: 0x%04x, Firmware: 0x%04x, Sample: 0x%04x, IAP: 0x%04x\n",
		 data->product_id,
		 data->fw_version,
		 data->sm_version,
		 data->iap_version);

	dev_dbg(dev,
		"Elan Touchpad Extra Information:\n"
		"    Max ABS X,Y:   %d,%d\n"
		"    Width X,Y:   %d,%d\n"
		"    Resolution X,Y:   %d,%d (dots/mm)\n"
		"    ic type: 0x%x\n"
		"    info pattern: 0x%x\n",
		data->max_x, data->max_y,
		data->width_x, data->width_y,
		data->x_res, data->y_res,
		data->ic_type, data->pattern);

	/* Set up input device properties based on queried parameters. */
	error = elan_setup_input_device(data);
	अगर (error)
		वापस error;

	अगर (device_property_पढ़ो_bool(&client->dev, "elan,trackpoint")) अणु
		error = elan_setup_trackpoपूर्णांक_input_device(data);
		अगर (error)
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

	error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, elan_isr,
					  irqflags | IRQF_ONESHOT,
					  client->name, data);
	अगर (error) अणु
		dev_err(dev, "cannot register irq=%d\n", client->irq);
		वापस error;
	पूर्ण

	error = devm_device_add_groups(dev, elan_sysfs_groups);
	अगर (error) अणु
		dev_err(dev, "failed to create sysfs attributes: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(data->input);
	अगर (error) अणु
		dev_err(dev, "failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	अगर (data->tp_input) अणु
		error = input_रेजिस्टर_device(data->tp_input);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to register TrackPoint input device: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	/*
	 * Systems using device tree should set up wakeup via DTS,
	 * the rest will configure device as wakeup source by शेष.
	 */
	अगर (!dev->of_node)
		device_init_wakeup(dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused elan_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);
	पूर्णांक ret;

	/*
	 * We are taking the mutex to make sure sysfs operations are
	 * complete beक्रमe we attempt to bring the device पूर्णांकo low[er]
	 * घातer mode.
	 */
	ret = mutex_lock_पूर्णांकerruptible(&data->sysfs_mutex);
	अगर (ret)
		वापस ret;

	disable_irq(client->irq);

	अगर (device_may_wakeup(dev)) अणु
		ret = elan_sleep(data);
		/* Enable wake from IRQ */
		data->irq_wake = (enable_irq_wake(client->irq) == 0);
	पूर्ण अन्यथा अणु
		ret = elan_disable_घातer(data);
	पूर्ण

	mutex_unlock(&data->sysfs_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused elan_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा elan_tp_data *data = i2c_get_clientdata(client);
	पूर्णांक error;

	अगर (device_may_wakeup(dev) && data->irq_wake) अणु
		disable_irq_wake(client->irq);
		data->irq_wake = false;
	पूर्ण

	error = elan_enable_घातer(data);
	अगर (error) अणु
		dev_err(dev, "power up when resuming failed: %d\n", error);
		जाओ err;
	पूर्ण

	error = elan_initialize(data, data->quirks & ETP_QUIRK_QUICK_WAKEUP);
	अगर (error)
		dev_err(dev, "initialize when resuming failed: %d\n", error);

err:
	enable_irq(data->client->irq);
	वापस error;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(elan_pm_ops, elan_suspend, elan_resume);

अटल स्थिर काष्ठा i2c_device_id elan_id[] = अणु
	अणु DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, elan_id);

#अगर_घोषित CONFIG_ACPI
#समावेश <linux/input/elan-i2c-ids.h>
MODULE_DEVICE_TABLE(acpi, elan_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id elan_of_match[] = अणु
	अणु .compatible = "elan,ekth3000" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, elan_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver elan_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.pm	= &elan_pm_ops,
		.acpi_match_table = ACPI_PTR(elan_acpi_id),
		.of_match_table = of_match_ptr(elan_of_match),
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe		= elan_probe,
	.id_table	= elan_id,
पूर्ण;

module_i2c_driver(elan_driver);

MODULE_AUTHOR("Duson Lin <dusonlin@emc.com.tw>");
MODULE_DESCRIPTION("Elan I2C/SMBus Touchpad driver");
MODULE_LICENSE("GPL");
