<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2017 IBM Corp.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pmbus.h>

#समावेश "pmbus.h"

#घोषणा CFFPS_FRU_CMD				0x9A
#घोषणा CFFPS_PN_CMD				0x9B
#घोषणा CFFPS_HEADER_CMD			0x9C
#घोषणा CFFPS_SN_CMD				0x9E
#घोषणा CFFPS_MAX_POWER_OUT_CMD			0xA7
#घोषणा CFFPS_CCIN_CMD				0xBD
#घोषणा CFFPS_FW_CMD				0xFA
#घोषणा CFFPS1_FW_NUM_BYTES			4
#घोषणा CFFPS2_FW_NUM_WORDS			3
#घोषणा CFFPS_SYS_CONFIG_CMD			0xDA
#घोषणा CFFPS_12VCS_VOUT_CMD			0xDE

#घोषणा CFFPS_INPUT_HISTORY_CMD			0xD6
#घोषणा CFFPS_INPUT_HISTORY_SIZE		100

#घोषणा CFFPS_CCIN_REVISION			GENMASK(7, 0)
#घोषणा  CFFPS_CCIN_REVISION_LEGACY		 0xde
#घोषणा CFFPS_CCIN_VERSION			GENMASK(15, 8)
#घोषणा CFFPS_CCIN_VERSION_1			 0x2b
#घोषणा CFFPS_CCIN_VERSION_2			 0x2e
#घोषणा CFFPS_CCIN_VERSION_3			 0x51

/* STATUS_MFR_SPECIFIC bits */
#घोषणा CFFPS_MFR_FAN_FAULT			BIT(0)
#घोषणा CFFPS_MFR_THERMAL_FAULT			BIT(1)
#घोषणा CFFPS_MFR_OV_FAULT			BIT(2)
#घोषणा CFFPS_MFR_UV_FAULT			BIT(3)
#घोषणा CFFPS_MFR_PS_KILL			BIT(4)
#घोषणा CFFPS_MFR_OC_FAULT			BIT(5)
#घोषणा CFFPS_MFR_VAUX_FAULT			BIT(6)
#घोषणा CFFPS_MFR_CURRENT_SHARE_WARNING		BIT(7)

#घोषणा CFFPS_LED_BLINK				BIT(0)
#घोषणा CFFPS_LED_ON				BIT(1)
#घोषणा CFFPS_LED_OFF				BIT(2)
#घोषणा CFFPS_BLINK_RATE_MS			250

क्रमागत अणु
	CFFPS_DEBUGFS_INPUT_HISTORY = 0,
	CFFPS_DEBUGFS_FRU,
	CFFPS_DEBUGFS_PN,
	CFFPS_DEBUGFS_HEADER,
	CFFPS_DEBUGFS_SN,
	CFFPS_DEBUGFS_MAX_POWER_OUT,
	CFFPS_DEBUGFS_CCIN,
	CFFPS_DEBUGFS_FW,
	CFFPS_DEBUGFS_ON_OFF_CONFIG,
	CFFPS_DEBUGFS_NUM_ENTRIES
पूर्ण;

क्रमागत versions अणु cffps1, cffps2, cffps_unknown पूर्ण;

काष्ठा ibm_cffps_input_history अणु
	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_update;

	u8 byte_count;
	u8 data[CFFPS_INPUT_HISTORY_SIZE];
पूर्ण;

काष्ठा ibm_cffps अणु
	क्रमागत versions version;
	काष्ठा i2c_client *client;

	काष्ठा ibm_cffps_input_history input_history;

	पूर्णांक debugfs_entries[CFFPS_DEBUGFS_NUM_ENTRIES];

	अक्षर led_name[32];
	u8 led_state;
	काष्ठा led_classdev led;
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ibm_cffps_id[];

#घोषणा to_psu(x, y) container_of((x), काष्ठा ibm_cffps, debugfs_entries[(y)])

अटल sमाप_प्रकार ibm_cffps_पढ़ो_input_history(काष्ठा ibm_cffps *psu,
					    अक्षर __user *buf, माप_प्रकार count,
					    loff_t *ppos)
अणु
	पूर्णांक rc;
	u8 msgbuf0[1] = अणु CFFPS_INPUT_HISTORY_CMD पूर्ण;
	u8 msgbuf1[CFFPS_INPUT_HISTORY_SIZE + 1] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = psu->client->addr,
			.flags = psu->client->flags,
			.len = 1,
			.buf = msgbuf0,
		पूर्ण, अणु
			.addr = psu->client->addr,
			.flags = psu->client->flags | I2C_M_RD,
			.len = CFFPS_INPUT_HISTORY_SIZE + 1,
			.buf = msgbuf1,
		पूर्ण,
	पूर्ण;

	अगर (!*ppos) अणु
		mutex_lock(&psu->input_history.update_lock);
		अगर (समय_after(jअगरfies, psu->input_history.last_update + HZ)) अणु
			/*
			 * Use a raw i2c transfer, since we need more bytes
			 * than Linux I2C supports through smbus xfr (only 32).
			 */
			rc = i2c_transfer(psu->client->adapter, msg, 2);
			अगर (rc < 0) अणु
				mutex_unlock(&psu->input_history.update_lock);
				वापस rc;
			पूर्ण

			psu->input_history.byte_count = msgbuf1[0];
			स_नकल(psu->input_history.data, &msgbuf1[1],
			       CFFPS_INPUT_HISTORY_SIZE);
			psu->input_history.last_update = jअगरfies;
		पूर्ण

		mutex_unlock(&psu->input_history.update_lock);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(buf, count, ppos,
				       psu->input_history.data,
				       psu->input_history.byte_count);
पूर्ण

अटल sमाप_प्रकार ibm_cffps_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	u8 cmd;
	पूर्णांक i, rc;
	पूर्णांक *idxp = file->निजी_data;
	पूर्णांक idx = *idxp;
	काष्ठा ibm_cffps *psu = to_psu(idxp, idx);
	अक्षर data[I2C_SMBUS_BLOCK_MAX + 2] = अणु 0 पूर्ण;

	pmbus_set_page(psu->client, 0, 0xff);

	चयन (idx) अणु
	हाल CFFPS_DEBUGFS_INPUT_HISTORY:
		वापस ibm_cffps_पढ़ो_input_history(psu, buf, count, ppos);
	हाल CFFPS_DEBUGFS_FRU:
		cmd = CFFPS_FRU_CMD;
		अवरोध;
	हाल CFFPS_DEBUGFS_PN:
		cmd = CFFPS_PN_CMD;
		अवरोध;
	हाल CFFPS_DEBUGFS_HEADER:
		cmd = CFFPS_HEADER_CMD;
		अवरोध;
	हाल CFFPS_DEBUGFS_SN:
		cmd = CFFPS_SN_CMD;
		अवरोध;
	हाल CFFPS_DEBUGFS_MAX_POWER_OUT:
		rc = i2c_smbus_पढ़ो_word_swapped(psu->client,
						 CFFPS_MAX_POWER_OUT_CMD);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, I2C_SMBUS_BLOCK_MAX, "%d", rc);
		जाओ करोne;
	हाल CFFPS_DEBUGFS_CCIN:
		rc = i2c_smbus_पढ़ो_word_swapped(psu->client, CFFPS_CCIN_CMD);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 5, "%04X", rc);
		जाओ करोne;
	हाल CFFPS_DEBUGFS_FW:
		चयन (psu->version) अणु
		हाल cffps1:
			क्रम (i = 0; i < CFFPS1_FW_NUM_BYTES; ++i) अणु
				rc = i2c_smbus_पढ़ो_byte_data(psu->client,
							      CFFPS_FW_CMD +
								i);
				अगर (rc < 0)
					वापस rc;

				snम_लिखो(&data[i * 2], 3, "%02X", rc);
			पूर्ण

			rc = i * 2;
			अवरोध;
		हाल cffps2:
			क्रम (i = 0; i < CFFPS2_FW_NUM_WORDS; ++i) अणु
				rc = i2c_smbus_पढ़ो_word_data(psu->client,
							      CFFPS_FW_CMD +
								i);
				अगर (rc < 0)
					वापस rc;

				snम_लिखो(&data[i * 4], 5, "%04X", rc);
			पूर्ण

			rc = i * 4;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		जाओ करोne;
	हाल CFFPS_DEBUGFS_ON_OFF_CONFIG:
		rc = i2c_smbus_पढ़ो_byte_data(psu->client,
					      PMBUS_ON_OFF_CONFIG);
		अगर (rc < 0)
			वापस rc;

		rc = snम_लिखो(data, 3, "%02x", rc);
		जाओ करोne;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rc = i2c_smbus_पढ़ो_block_data(psu->client, cmd, data);
	अगर (rc < 0)
		वापस rc;

करोne:
	data[rc] = '\n';
	rc += 2;

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, data, rc);
पूर्ण

अटल sमाप_प्रकार ibm_cffps_debugfs_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *buf, माप_प्रकार count,
				       loff_t *ppos)
अणु
	u8 data;
	sमाप_प्रकार rc;
	पूर्णांक *idxp = file->निजी_data;
	पूर्णांक idx = *idxp;
	काष्ठा ibm_cffps *psu = to_psu(idxp, idx);

	चयन (idx) अणु
	हाल CFFPS_DEBUGFS_ON_OFF_CONFIG:
		pmbus_set_page(psu->client, 0, 0xff);

		rc = simple_ग_लिखो_to_buffer(&data, 1, ppos, buf, count);
		अगर (rc <= 0)
			वापस rc;

		rc = i2c_smbus_ग_लिखो_byte_data(psu->client,
					       PMBUS_ON_OFF_CONFIG, data);
		अगर (rc)
			वापस rc;

		rc = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations ibm_cffps_fops = अणु
	.llseek = noop_llseek,
	.पढ़ो = ibm_cffps_debugfs_पढ़ो,
	.ग_लिखो = ibm_cffps_debugfs_ग_लिखो,
	.खोलो = simple_खोलो,
पूर्ण;

अटल पूर्णांक ibm_cffps_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक reg)
अणु
	पूर्णांक rc, mfr;

	चयन (reg) अणु
	हाल PMBUS_STATUS_VOUT:
	हाल PMBUS_STATUS_IOUT:
	हाल PMBUS_STATUS_TEMPERATURE:
	हाल PMBUS_STATUS_FAN_12:
		rc = pmbus_पढ़ो_byte_data(client, page, reg);
		अगर (rc < 0)
			वापस rc;

		mfr = pmbus_पढ़ो_byte_data(client, page,
					   PMBUS_STATUS_MFR_SPECIFIC);
		अगर (mfr < 0)
			/*
			 * Return the status रेजिस्टर instead of an error,
			 * since we successfully पढ़ो status.
			 */
			वापस rc;

		/* Add MFR_SPECIFIC bits to the standard pmbus status regs. */
		अगर (reg == PMBUS_STATUS_FAN_12) अणु
			अगर (mfr & CFFPS_MFR_FAN_FAULT)
				rc |= PB_FAN_FAN1_FAULT;
		पूर्ण अन्यथा अगर (reg == PMBUS_STATUS_TEMPERATURE) अणु
			अगर (mfr & CFFPS_MFR_THERMAL_FAULT)
				rc |= PB_TEMP_OT_FAULT;
		पूर्ण अन्यथा अगर (reg == PMBUS_STATUS_VOUT) अणु
			अगर (mfr & (CFFPS_MFR_OV_FAULT | CFFPS_MFR_VAUX_FAULT))
				rc |= PB_VOLTAGE_OV_FAULT;
			अगर (mfr & CFFPS_MFR_UV_FAULT)
				rc |= PB_VOLTAGE_UV_FAULT;
		पूर्ण अन्यथा अगर (reg == PMBUS_STATUS_IOUT) अणु
			अगर (mfr & CFFPS_MFR_OC_FAULT)
				rc |= PB_IOUT_OC_FAULT;
			अगर (mfr & CFFPS_MFR_CURRENT_SHARE_WARNING)
				rc |= PB_CURRENT_SHARE_FAULT;
		पूर्ण
		अवरोध;
	शेष:
		rc = -ENODATA;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ibm_cffps_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक rc, mfr;

	चयन (reg) अणु
	हाल PMBUS_STATUS_WORD:
		rc = pmbus_पढ़ो_word_data(client, page, phase, reg);
		अगर (rc < 0)
			वापस rc;

		mfr = pmbus_पढ़ो_byte_data(client, page,
					   PMBUS_STATUS_MFR_SPECIFIC);
		अगर (mfr < 0)
			/*
			 * Return the status रेजिस्टर instead of an error,
			 * since we successfully पढ़ो status.
			 */
			वापस rc;

		अगर (mfr & CFFPS_MFR_PS_KILL)
			rc |= PB_STATUS_OFF;
		अवरोध;
	हाल PMBUS_VIRT_READ_VMON:
		rc = pmbus_पढ़ो_word_data(client, page, phase,
					  CFFPS_12VCS_VOUT_CMD);
		अवरोध;
	शेष:
		rc = -ENODATA;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ibm_cffps_led_brightness_set(काष्ठा led_classdev *led_cdev,
					क्रमागत led_brightness brightness)
अणु
	पूर्णांक rc;
	u8 next_led_state;
	काष्ठा ibm_cffps *psu = container_of(led_cdev, काष्ठा ibm_cffps, led);

	अगर (brightness == LED_OFF) अणु
		next_led_state = CFFPS_LED_OFF;
	पूर्ण अन्यथा अणु
		brightness = LED_FULL;

		अगर (psu->led_state != CFFPS_LED_BLINK)
			next_led_state = CFFPS_LED_ON;
		अन्यथा
			next_led_state = CFFPS_LED_BLINK;
	पूर्ण

	dev_dbg(&psu->client->dev, "LED brightness set: %d. Command: %d.\n",
		brightness, next_led_state);

	pmbus_set_page(psu->client, 0, 0xff);

	rc = i2c_smbus_ग_लिखो_byte_data(psu->client, CFFPS_SYS_CONFIG_CMD,
				       next_led_state);
	अगर (rc < 0)
		वापस rc;

	psu->led_state = next_led_state;
	led_cdev->brightness = brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक ibm_cffps_led_blink_set(काष्ठा led_classdev *led_cdev,
				   अचिन्हित दीर्घ *delay_on,
				   अचिन्हित दीर्घ *delay_off)
अणु
	पूर्णांक rc;
	काष्ठा ibm_cffps *psu = container_of(led_cdev, काष्ठा ibm_cffps, led);

	dev_dbg(&psu->client->dev, "LED blink set.\n");

	pmbus_set_page(psu->client, 0, 0xff);

	rc = i2c_smbus_ग_लिखो_byte_data(psu->client, CFFPS_SYS_CONFIG_CMD,
				       CFFPS_LED_BLINK);
	अगर (rc < 0)
		वापस rc;

	psu->led_state = CFFPS_LED_BLINK;
	led_cdev->brightness = LED_FULL;
	*delay_on = CFFPS_BLINK_RATE_MS;
	*delay_off = CFFPS_BLINK_RATE_MS;

	वापस 0;
पूर्ण

अटल व्योम ibm_cffps_create_led_class(काष्ठा ibm_cffps *psu)
अणु
	पूर्णांक rc;
	काष्ठा i2c_client *client = psu->client;
	काष्ठा device *dev = &client->dev;

	snम_लिखो(psu->led_name, माप(psu->led_name), "%s-%02x", client->name,
		 client->addr);
	psu->led.name = psu->led_name;
	psu->led.max_brightness = LED_FULL;
	psu->led.brightness_set_blocking = ibm_cffps_led_brightness_set;
	psu->led.blink_set = ibm_cffps_led_blink_set;

	rc = devm_led_classdev_रेजिस्टर(dev, &psu->led);
	अगर (rc)
		dev_warn(dev, "failed to register led class: %d\n", rc);
	अन्यथा
		i2c_smbus_ग_लिखो_byte_data(client, CFFPS_SYS_CONFIG_CMD,
					  CFFPS_LED_OFF);
पूर्ण

अटल काष्ठा pmbus_driver_info ibm_cffps_info[] = अणु
	[cffps1] = अणु
		.pages = 1,
		.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_PIN | PMBUS_HAVE_FAN12 | PMBUS_HAVE_TEMP |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
			PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_FAN12,
		.पढ़ो_byte_data = ibm_cffps_पढ़ो_byte_data,
		.पढ़ो_word_data = ibm_cffps_पढ़ो_word_data,
	पूर्ण,
	[cffps2] = अणु
		.pages = 2,
		.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_PIN | PMBUS_HAVE_FAN12 | PMBUS_HAVE_TEMP |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
			PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_FAN12 | PMBUS_HAVE_VMON,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
			PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT,
		.पढ़ो_byte_data = ibm_cffps_पढ़ो_byte_data,
		.पढ़ो_word_data = ibm_cffps_पढ़ो_word_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा pmbus_platक्रमm_data ibm_cffps_pdata = अणु
	.flags = PMBUS_SKIP_STATUS_CHECK | PMBUS_NO_CAPABILITY,
पूर्ण;

अटल पूर्णांक ibm_cffps_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक i, rc;
	क्रमागत versions vs = cffps_unknown;
	काष्ठा dentry *debugfs;
	काष्ठा dentry *ibm_cffps_dir;
	काष्ठा ibm_cffps *psu;
	स्थिर व्योम *md = of_device_get_match_data(&client->dev);
	स्थिर काष्ठा i2c_device_id *id;

	अगर (md) अणु
		vs = (क्रमागत versions)md;
	पूर्ण अन्यथा अणु
		id = i2c_match_id(ibm_cffps_id, client);
		अगर (id)
			vs = (क्रमागत versions)id->driver_data;
	पूर्ण

	अगर (vs == cffps_unknown) अणु
		u16 ccin_revision = 0;
		u16 ccin_version = CFFPS_CCIN_VERSION_1;
		पूर्णांक ccin = i2c_smbus_पढ़ो_word_swapped(client, CFFPS_CCIN_CMD);

		अगर (ccin > 0) अणु
			ccin_revision = FIELD_GET(CFFPS_CCIN_REVISION, ccin);
			ccin_version = FIELD_GET(CFFPS_CCIN_VERSION, ccin);
		पूर्ण

		चयन (ccin_version) अणु
		शेष:
		हाल CFFPS_CCIN_VERSION_1:
			vs = cffps1;
			अवरोध;
		हाल CFFPS_CCIN_VERSION_2:
			vs = cffps2;
			अवरोध;
		हाल CFFPS_CCIN_VERSION_3:
			अगर (ccin_revision == CFFPS_CCIN_REVISION_LEGACY)
				vs = cffps1;
			अन्यथा
				vs = cffps2;
			अवरोध;
		पूर्ण

		/* Set the client name to include the version number. */
		snम_लिखो(client->name, I2C_NAME_SIZE, "cffps%d", vs + 1);
	पूर्ण

	client->dev.platक्रमm_data = &ibm_cffps_pdata;
	rc = pmbus_करो_probe(client, &ibm_cffps_info[vs]);
	अगर (rc)
		वापस rc;

	/*
	 * Don't fail the probe if there isn't enough memory क्रम leds and
	 * debugfs.
	 */
	psu = devm_kzalloc(&client->dev, माप(*psu), GFP_KERNEL);
	अगर (!psu)
		वापस 0;

	psu->version = vs;
	psu->client = client;
	mutex_init(&psu->input_history.update_lock);
	psu->input_history.last_update = jअगरfies - HZ;

	ibm_cffps_create_led_class(psu);

	/* Don't fail the probe if we can't create debugfs */
	debugfs = pmbus_get_debugfs_dir(client);
	अगर (!debugfs)
		वापस 0;

	ibm_cffps_dir = debugfs_create_dir(client->name, debugfs);
	अगर (!ibm_cffps_dir)
		वापस 0;

	क्रम (i = 0; i < CFFPS_DEBUGFS_NUM_ENTRIES; ++i)
		psu->debugfs_entries[i] = i;

	debugfs_create_file("input_history", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_INPUT_HISTORY],
			    &ibm_cffps_fops);
	debugfs_create_file("fru", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_FRU],
			    &ibm_cffps_fops);
	debugfs_create_file("part_number", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_PN],
			    &ibm_cffps_fops);
	debugfs_create_file("header", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_HEADER],
			    &ibm_cffps_fops);
	debugfs_create_file("serial_number", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_SN],
			    &ibm_cffps_fops);
	debugfs_create_file("max_power_out", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_MAX_POWER_OUT],
			    &ibm_cffps_fops);
	debugfs_create_file("ccin", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_CCIN],
			    &ibm_cffps_fops);
	debugfs_create_file("fw_version", 0444, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_FW],
			    &ibm_cffps_fops);
	debugfs_create_file("on_off_config", 0644, ibm_cffps_dir,
			    &psu->debugfs_entries[CFFPS_DEBUGFS_ON_OFF_CONFIG],
			    &ibm_cffps_fops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ibm_cffps_id[] = अणु
	अणु "ibm_cffps1", cffps1 पूर्ण,
	अणु "ibm_cffps2", cffps2 पूर्ण,
	अणु "ibm_cffps", cffps_unknown पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ibm_cffps_id);

अटल स्थिर काष्ठा of_device_id ibm_cffps_of_match[] = अणु
	अणु
		.compatible = "ibm,cffps1",
		.data = (व्योम *)cffps1
	पूर्ण,
	अणु
		.compatible = "ibm,cffps2",
		.data = (व्योम *)cffps2
	पूर्ण,
	अणु
		.compatible = "ibm,cffps",
		.data = (व्योम *)cffps_unknown
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ibm_cffps_of_match);

अटल काष्ठा i2c_driver ibm_cffps_driver = अणु
	.driver = अणु
		.name = "ibm-cffps",
		.of_match_table = ibm_cffps_of_match,
	पूर्ण,
	.probe_new = ibm_cffps_probe,
	.id_table = ibm_cffps_id,
पूर्ण;

module_i2c_driver(ibm_cffps_driver);

MODULE_AUTHOR("Eddie James");
MODULE_DESCRIPTION("PMBus driver for IBM Common Form Factor power supplies");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
