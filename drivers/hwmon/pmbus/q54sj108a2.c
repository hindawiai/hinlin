<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Delta modules, Q54SJ108A2 series 1/4 Brick DC/DC
 * Regulated Power Module
 *
 * Copyright 2020 Delta LLC.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश "pmbus.h"

#घोषणा STORE_DEFAULT_ALL		0x11
#घोषणा ERASE_BLACKBOX_DATA		0xD1
#घोषणा READ_HISTORY_EVENT_NUMBER	0xD2
#घोषणा READ_HISTORY_EVENTS		0xE0
#घोषणा SET_HISTORY_EVENT_OFFSET	0xE1
#घोषणा PMBUS_FLASH_KEY_WRITE		0xEC

क्रमागत chips अणु
	q54sj108a2
पूर्ण;

क्रमागत अणु
	Q54SJ108A2_DEBUGFS_OPERATION = 0,
	Q54SJ108A2_DEBUGFS_CLEARFAULT,
	Q54SJ108A2_DEBUGFS_WRITEPROTECT,
	Q54SJ108A2_DEBUGFS_STOREDEFAULT,
	Q54SJ108A2_DEBUGFS_VOOV_RESPONSE,
	Q54SJ108A2_DEBUGFS_IOOC_RESPONSE,
	Q54SJ108A2_DEBUGFS_PMBUS_VERSION,
	Q54SJ108A2_DEBUGFS_MFR_ID,
	Q54SJ108A2_DEBUGFS_MFR_MODEL,
	Q54SJ108A2_DEBUGFS_MFR_REVISION,
	Q54SJ108A2_DEBUGFS_MFR_LOCATION,
	Q54SJ108A2_DEBUGFS_BLACKBOX_ERASE,
	Q54SJ108A2_DEBUGFS_BLACKBOX_READ_OFFSET,
	Q54SJ108A2_DEBUGFS_BLACKBOX_SET_OFFSET,
	Q54SJ108A2_DEBUGFS_BLACKBOX_READ,
	Q54SJ108A2_DEBUGFS_FLASH_KEY,
	Q54SJ108A2_DEBUGFS_NUM_ENTRIES
पूर्ण;

काष्ठा q54sj108a2_data अणु
	क्रमागत chips chip;
	काष्ठा i2c_client *client;

	पूर्णांक debugfs_entries[Q54SJ108A2_DEBUGFS_NUM_ENTRIES];
पूर्ण;

#घोषणा to_psu(x, y) container_of((x), काष्ठा q54sj108a2_data, debugfs_entries[(y)])

अटल काष्ठा pmbus_driver_info q54sj108a2_info[] = अणु
	[q54sj108a2] = अणु
		.pages = 1,

		/* Source : Delta Q54SJ108A2 */
		.क्रमmat[PSC_TEMPERATURE] = linear,
		.क्रमmat[PSC_VOLTAGE_IN] = linear,
		.क्रमmat[PSC_CURRENT_OUT] = linear,

		.func[0] = PMBUS_HAVE_VIN |
		PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_STATUS_INPUT,
	पूर्ण,
पूर्ण;

अटल sमाप_प्रकार q54sj108a2_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc;
	पूर्णांक *idxp = file->निजी_data;
	पूर्णांक idx = *idxp;
	काष्ठा q54sj108a2_data *psu = to_psu(idxp, idx);
	अक्षर data[I2C_SMBUS_BLOCK_MAX + 2] = अणु 0 पूर्ण;
	अक्षर data_अक्षर[I2C_SMBUS_BLOCK_MAX + 2] = अणु 0 पूर्ण;
	अक्षर *res;

	चयन (idx) अणु
	हाल Q54SJ108A2_DEBUGFS_OPERATION:
		rc = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_OPERATION);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 3, "%02x", rc);
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_WRITEPROTECT:
		rc = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_WRITE_PROTECT);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 3, "%02x", rc);
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_VOOV_RESPONSE:
		rc = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_VOUT_OV_FAULT_RESPONSE);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 3, "%02x", rc);
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_IOOC_RESPONSE:
		rc = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_IOUT_OC_FAULT_RESPONSE);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 3, "%02x", rc);
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_PMBUS_VERSION:
		rc = i2c_smbus_पढ़ो_byte_data(psu->client, PMBUS_REVISION);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 3, "%02x", rc);
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_MFR_ID:
		rc = i2c_smbus_पढ़ो_block_data(psu->client, PMBUS_MFR_ID, data);
		अगर (rc < 0)
			वापस rc;
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_MFR_MODEL:
		rc = i2c_smbus_पढ़ो_block_data(psu->client, PMBUS_MFR_MODEL, data);
		अगर (rc < 0)
			वापस rc;
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_MFR_REVISION:
		rc = i2c_smbus_पढ़ो_block_data(psu->client, PMBUS_MFR_REVISION, data);
		अगर (rc < 0)
			वापस rc;
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_MFR_LOCATION:
		rc = i2c_smbus_पढ़ो_block_data(psu->client, PMBUS_MFR_LOCATION, data);
		अगर (rc < 0)
			वापस rc;
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_BLACKBOX_READ_OFFSET:
		rc = i2c_smbus_पढ़ो_byte_data(psu->client, READ_HISTORY_EVENT_NUMBER);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 3, "%02x", rc);
		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_BLACKBOX_READ:
		rc = i2c_smbus_पढ़ो_block_data(psu->client, READ_HISTORY_EVENTS, data);
		अगर (rc < 0)
			वापस rc;

		res = bin2hex(data, data_अक्षर, 32);
		rc = res - data;

		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_FLASH_KEY:
		rc = i2c_smbus_पढ़ो_block_data(psu->client, PMBUS_FLASH_KEY_WRITE, data);
		अगर (rc < 0)
			वापस rc;

		res = bin2hex(data, data_अक्षर, 4);
		rc = res - data;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data[rc] = '\n';
	rc += 2;

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, data, rc);
पूर्ण

अटल sमाप_प्रकार q54sj108a2_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	u8 flash_key[4];
	u8 dst_data;
	sमाप_प्रकार rc;
	पूर्णांक *idxp = file->निजी_data;
	पूर्णांक idx = *idxp;
	काष्ठा q54sj108a2_data *psu = to_psu(idxp, idx);

	rc = i2c_smbus_ग_लिखो_byte_data(psu->client, PMBUS_WRITE_PROTECT, 0);
	अगर (rc)
		वापस rc;

	चयन (idx) अणु
	हाल Q54SJ108A2_DEBUGFS_OPERATION:
		rc = kstrtou8_from_user(buf, count, 0, &dst_data);
		अगर (rc < 0)
			वापस rc;

		rc = i2c_smbus_ग_लिखो_byte_data(psu->client, PMBUS_OPERATION, dst_data);
		अगर (rc < 0)
			वापस rc;

		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_CLEARFAULT:
		rc = i2c_smbus_ग_लिखो_byte(psu->client, PMBUS_CLEAR_FAULTS);
		अगर (rc < 0)
			वापस rc;

		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_STOREDEFAULT:
		flash_key[0] = 0x7E;
		flash_key[1] = 0x15;
		flash_key[2] = 0xDC;
		flash_key[3] = 0x42;
		rc = i2c_smbus_ग_लिखो_block_data(psu->client, PMBUS_FLASH_KEY_WRITE, 4, flash_key);
		अगर (rc < 0)
			वापस rc;

		rc = i2c_smbus_ग_लिखो_byte(psu->client, STORE_DEFAULT_ALL);
		अगर (rc < 0)
			वापस rc;

		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_VOOV_RESPONSE:
		rc = kstrtou8_from_user(buf, count, 0, &dst_data);
		अगर (rc < 0)
			वापस rc;

		rc = i2c_smbus_ग_लिखो_byte_data(psu->client, PMBUS_VOUT_OV_FAULT_RESPONSE, dst_data);
		अगर (rc < 0)
			वापस rc;

		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_IOOC_RESPONSE:
		rc = kstrtou8_from_user(buf, count, 0, &dst_data);
		अगर (rc < 0)
			वापस rc;

		rc = i2c_smbus_ग_लिखो_byte_data(psu->client, PMBUS_IOUT_OC_FAULT_RESPONSE, dst_data);
		अगर (rc < 0)
			वापस rc;

		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_BLACKBOX_ERASE:
		rc = i2c_smbus_ग_लिखो_byte(psu->client, ERASE_BLACKBOX_DATA);
		अगर (rc < 0)
			वापस rc;

		अवरोध;
	हाल Q54SJ108A2_DEBUGFS_BLACKBOX_SET_OFFSET:
		rc = kstrtou8_from_user(buf, count, 0, &dst_data);
		अगर (rc < 0)
			वापस rc;

		rc = i2c_smbus_ग_लिखो_byte_data(psu->client, SET_HISTORY_EVENT_OFFSET, dst_data);
		अगर (rc < 0)
			वापस rc;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations q54sj108a2_fops = अणु
	.llseek = noop_llseek,
	.पढ़ो = q54sj108a2_debugfs_पढ़ो,
	.ग_लिखो = q54sj108a2_debugfs_ग_लिखो,
	.खोलो = simple_खोलो,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id q54sj108a2_id[] = अणु
	अणु "q54sj108a2", q54sj108a2 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, q54sj108a2_id);

अटल पूर्णांक q54sj108a2_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	u8 buf[I2C_SMBUS_BLOCK_MAX + 1];
	क्रमागत chips chip_id;
	पूर्णांक ret, i;
	काष्ठा dentry *debugfs;
	काष्ठा dentry *q54sj108a2_dir;
	काष्ठा q54sj108a2_data *psu;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA |
				     I2C_FUNC_SMBUS_BLOCK_DATA))
		वापस -ENODEV;

	अगर (client->dev.of_node)
		chip_id = (क्रमागत chips)(अचिन्हित दीर्घ)of_device_get_match_data(dev);
	अन्यथा
		chip_id = i2c_match_id(q54sj108a2_id, client)->driver_data;

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_ID, buf);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read Manufacturer ID\n");
		वापस ret;
	पूर्ण
	अगर (ret != 6 || म_भेदन(buf, "DELTA", 5)) अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported Manufacturer ID '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण

	/*
	 * The chips support पढ़ोing PMBUS_MFR_MODEL.
	 */
	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, buf);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read Manufacturer Model\n");
		वापस ret;
	पूर्ण
	अगर (ret != 14 || म_भेदन(buf, "Q54SJ108A2", 10)) अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported Manufacturer Model '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_REVISION, buf);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read Manufacturer Revision\n");
		वापस ret;
	पूर्ण
	अगर (ret != 4 || buf[0] != 'S') अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported Manufacturer Revision '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण

	ret = pmbus_करो_probe(client, &q54sj108a2_info[chip_id]);
	अगर (ret)
		वापस ret;

	psu = devm_kzalloc(&client->dev, माप(*psu), GFP_KERNEL);
	अगर (!psu)
		वापस 0;

	psu->client = client;

	debugfs = pmbus_get_debugfs_dir(client);

	q54sj108a2_dir = debugfs_create_dir(client->name, debugfs);

	क्रम (i = 0; i < Q54SJ108A2_DEBUGFS_NUM_ENTRIES; ++i)
		psu->debugfs_entries[i] = i;

	debugfs_create_file("operation", 0644, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_OPERATION],
			    &q54sj108a2_fops);
	debugfs_create_file("clear_fault", 0200, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_CLEARFAULT],
			    &q54sj108a2_fops);
	debugfs_create_file("write_protect", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_WRITEPROTECT],
			    &q54sj108a2_fops);
	debugfs_create_file("store_default", 0200, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_STOREDEFAULT],
			    &q54sj108a2_fops);
	debugfs_create_file("vo_ov_response", 0644, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_VOOV_RESPONSE],
			    &q54sj108a2_fops);
	debugfs_create_file("io_oc_response", 0644, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_IOOC_RESPONSE],
			    &q54sj108a2_fops);
	debugfs_create_file("pmbus_revision", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_PMBUS_VERSION],
			    &q54sj108a2_fops);
	debugfs_create_file("mfr_id", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_MFR_ID],
			    &q54sj108a2_fops);
	debugfs_create_file("mfr_model", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_MFR_MODEL],
			    &q54sj108a2_fops);
	debugfs_create_file("mfr_revision", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_MFR_REVISION],
			    &q54sj108a2_fops);
	debugfs_create_file("mfr_location", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_MFR_LOCATION],
			    &q54sj108a2_fops);
	debugfs_create_file("blackbox_erase", 0200, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_BLACKBOX_ERASE],
			    &q54sj108a2_fops);
	debugfs_create_file("blackbox_read_offset", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_BLACKBOX_READ_OFFSET],
			    &q54sj108a2_fops);
	debugfs_create_file("blackbox_set_offset", 0200, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_BLACKBOX_SET_OFFSET],
			    &q54sj108a2_fops);
	debugfs_create_file("blackbox_read", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_BLACKBOX_READ],
			    &q54sj108a2_fops);
	debugfs_create_file("flash_key", 0444, q54sj108a2_dir,
			    &psu->debugfs_entries[Q54SJ108A2_DEBUGFS_FLASH_KEY],
			    &q54sj108a2_fops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id q54sj108a2_of_match[] = अणु
	अणु .compatible = "delta,q54sj108a2", .data = (व्योम *)q54sj108a2 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, q54sj108a2_of_match);

अटल काष्ठा i2c_driver q54sj108a2_driver = अणु
	.driver = अणु
		.name = "q54sj108a2",
		.of_match_table = q54sj108a2_of_match,
	पूर्ण,
	.probe_new = q54sj108a2_probe,
	.id_table = q54sj108a2_id,
पूर्ण;

module_i2c_driver(q54sj108a2_driver);

MODULE_AUTHOR("Xiao.Ma <xiao.mx.ma@deltaww.com>");
MODULE_DESCRIPTION("PMBus driver for Delta Q54SJ108A2 series modules");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
