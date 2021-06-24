<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip / Aपंचांगel ECC (I2C) driver.
 *
 * Copyright (c) 2017, Microchip Technology Inc.
 * Author: Tuकरोr Ambarus <tuकरोr.ambarus@microchip.com>
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/crc16.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश "atmel-i2c.h"

अटल स्थिर काष्ठा अणु
	u8 value;
	स्थिर अक्षर *error_text;
पूर्ण error_list[] = अणु
	अणु 0x01, "CheckMac or Verify miscompare" पूर्ण,
	अणु 0x03, "Parse Error" पूर्ण,
	अणु 0x05, "ECC Fault" पूर्ण,
	अणु 0x0F, "Execution Error" पूर्ण,
	अणु 0xEE, "Watchdog about to expire" पूर्ण,
	अणु 0xFF, "CRC or other communication error" पूर्ण,
पूर्ण;

/**
 * aपंचांगel_i2c_checksum() - Generate 16-bit CRC as required by ATMEL ECC.
 * CRC16 verअगरication of the count, opcode, param1, param2 and data bytes.
 * The checksum is saved in little-endian क्रमmat in the least signअगरicant
 * two bytes of the command. CRC polynomial is 0x8005 and the initial रेजिस्टर
 * value should be zero.
 *
 * @cmd : काष्ठाure used क्रम communicating with the device.
 */
अटल व्योम aपंचांगel_i2c_checksum(काष्ठा aपंचांगel_i2c_cmd *cmd)
अणु
	u8 *data = &cmd->count;
	माप_प्रकार len = cmd->count - CRC_SIZE;
	__le16 *__crc16 = (__le16 *)(data + len);

	*__crc16 = cpu_to_le16(bitrev16(crc16(0, data, len)));
पूर्ण

व्योम aपंचांगel_i2c_init_पढ़ो_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd)
अणु
	cmd->word_addr = COMMAND;
	cmd->opcode = OPCODE_READ;
	/*
	 * Read the word from Configuration zone that contains the lock bytes
	 * (UserExtra, Selector, LockValue, LockConfig).
	 */
	cmd->param1 = CONFIG_ZONE;
	cmd->param2 = cpu_to_le16(DEVICE_LOCK_ADDR);
	cmd->count = READ_COUNT;

	aपंचांगel_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_READ;
	cmd->rxsize = READ_RSP_SIZE;
पूर्ण
EXPORT_SYMBOL(aपंचांगel_i2c_init_पढ़ो_cmd);

व्योम aपंचांगel_i2c_init_अक्रमom_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd)
अणु
	cmd->word_addr = COMMAND;
	cmd->opcode = OPCODE_RANDOM;
	cmd->param1 = 0;
	cmd->param2 = 0;
	cmd->count = RANDOM_COUNT;

	aपंचांगel_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_RANDOM;
	cmd->rxsize = RANDOM_RSP_SIZE;
पूर्ण
EXPORT_SYMBOL(aपंचांगel_i2c_init_अक्रमom_cmd);

व्योम aपंचांगel_i2c_init_genkey_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd, u16 keyid)
अणु
	cmd->word_addr = COMMAND;
	cmd->count = GENKEY_COUNT;
	cmd->opcode = OPCODE_GENKEY;
	cmd->param1 = GENKEY_MODE_PRIVATE;
	/* a अक्रमom निजी key will be generated and stored in slot keyID */
	cmd->param2 = cpu_to_le16(keyid);

	aपंचांगel_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_GENKEY;
	cmd->rxsize = GENKEY_RSP_SIZE;
पूर्ण
EXPORT_SYMBOL(aपंचांगel_i2c_init_genkey_cmd);

पूर्णांक aपंचांगel_i2c_init_ecdh_cmd(काष्ठा aपंचांगel_i2c_cmd *cmd,
			    काष्ठा scatterlist *pubkey)
अणु
	माप_प्रकार copied;

	cmd->word_addr = COMMAND;
	cmd->count = ECDH_COUNT;
	cmd->opcode = OPCODE_ECDH;
	cmd->param1 = ECDH_PREFIX_MODE;
	/* निजी key slot */
	cmd->param2 = cpu_to_le16(DATA_SLOT_2);

	/*
	 * The device only supports NIST P256 ECC keys. The खुला key size will
	 * always be the same. Use a macro क्रम the key size to aव्योम unnecessary
	 * computations.
	 */
	copied = sg_copy_to_buffer(pubkey,
				   sg_nents_क्रम_len(pubkey,
						    ATMEL_ECC_PUBKEY_SIZE),
				   cmd->data, ATMEL_ECC_PUBKEY_SIZE);
	अगर (copied != ATMEL_ECC_PUBKEY_SIZE)
		वापस -EINVAL;

	aपंचांगel_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_ECDH;
	cmd->rxsize = ECDH_RSP_SIZE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(aपंचांगel_i2c_init_ecdh_cmd);

/*
 * After wake and after execution of a command, there will be error, status, or
 * result bytes in the device's output रेजिस्टर that can be retrieved by the
 * प्रणाली. When the length of that group is four bytes, the codes वापसed are
 * detailed in error_list.
 */
अटल पूर्णांक aपंचांगel_i2c_status(काष्ठा device *dev, u8 *status)
अणु
	माप_प्रकार err_list_len = ARRAY_SIZE(error_list);
	पूर्णांक i;
	u8 err_id = status[1];

	अगर (*status != STATUS_SIZE)
		वापस 0;

	अगर (err_id == STATUS_WAKE_SUCCESSFUL || err_id == STATUS_NOERR)
		वापस 0;

	क्रम (i = 0; i < err_list_len; i++)
		अगर (error_list[i].value == err_id)
			अवरोध;

	/* अगर err_id is not in the error_list then ignore it */
	अगर (i != err_list_len) अणु
		dev_err(dev, "%02x: %s:\n", err_id, error_list[i].error_text);
		वापस err_id;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_i2c_wakeup(काष्ठा i2c_client *client)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);
	u8 status[STATUS_RSP_SIZE];
	पूर्णांक ret;

	/*
	 * The device ignores any levels or transitions on the SCL pin when the
	 * device is idle, asleep or during waking up. Don't check क्रम error
	 * when waking up the device.
	 */
	i2c_transfer_buffer_flags(client, i2c_priv->wake_token,
				i2c_priv->wake_token_sz, I2C_M_IGNORE_NAK);

	/*
	 * Wait to wake the device. Typical execution बार क्रम ecdh and genkey
	 * are around tens of milliseconds. Delta is chosen to 50 microseconds.
	 */
	usleep_range(TWHI_MIN, TWHI_MAX);

	ret = i2c_master_recv(client, status, STATUS_SIZE);
	अगर (ret < 0)
		वापस ret;

	वापस aपंचांगel_i2c_status(&client->dev, status);
पूर्ण

अटल पूर्णांक aपंचांगel_i2c_sleep(काष्ठा i2c_client *client)
अणु
	u8 sleep = SLEEP_TOKEN;

	वापस i2c_master_send(client, &sleep, 1);
पूर्ण

/*
 * aपंचांगel_i2c_send_receive() - send a command to the device and receive its
 *                            response.
 * @client: i2c client device
 * @cmd   : काष्ठाure used to communicate with the device
 *
 * After the device receives a Wake token, a watchकरोg counter starts within the
 * device. After the watchकरोg समयr expires, the device enters sleep mode
 * regardless of whether some I/O transmission or command execution is in
 * progress. If a command is attempted when insufficient समय reमुख्यs prior to
 * watchकरोg समयr execution, the device will वापस the watchकरोg समयout error
 * code without attempting to execute the command. There is no way to reset the
 * counter other than to put the device पूर्णांकo sleep or idle mode and then
 * wake it up again.
 */
पूर्णांक aपंचांगel_i2c_send_receive(काष्ठा i2c_client *client, काष्ठा aपंचांगel_i2c_cmd *cmd)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);
	पूर्णांक ret;

	mutex_lock(&i2c_priv->lock);

	ret = aपंचांगel_i2c_wakeup(client);
	अगर (ret)
		जाओ err;

	/* send the command */
	ret = i2c_master_send(client, (u8 *)cmd, cmd->count + WORD_ADDR_SIZE);
	अगर (ret < 0)
		जाओ err;

	/* delay the appropriate amount of समय क्रम command to execute */
	msleep(cmd->msecs);

	/* receive the response */
	ret = i2c_master_recv(client, cmd->data, cmd->rxsize);
	अगर (ret < 0)
		जाओ err;

	/* put the device पूर्णांकo low-घातer mode */
	ret = aपंचांगel_i2c_sleep(client);
	अगर (ret < 0)
		जाओ err;

	mutex_unlock(&i2c_priv->lock);
	वापस aपंचांगel_i2c_status(&client->dev, cmd->data);
err:
	mutex_unlock(&i2c_priv->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(aपंचांगel_i2c_send_receive);

अटल व्योम aपंचांगel_i2c_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aपंचांगel_i2c_work_data *work_data =
			container_of(work, काष्ठा aपंचांगel_i2c_work_data, work);
	काष्ठा aपंचांगel_i2c_cmd *cmd = &work_data->cmd;
	काष्ठा i2c_client *client = work_data->client;
	पूर्णांक status;

	status = aपंचांगel_i2c_send_receive(client, cmd);
	work_data->cbk(work_data, work_data->areq, status);
पूर्ण

व्योम aपंचांगel_i2c_enqueue(काष्ठा aपंचांगel_i2c_work_data *work_data,
		       व्योम (*cbk)(काष्ठा aपंचांगel_i2c_work_data *work_data,
				   व्योम *areq, पूर्णांक status),
		       व्योम *areq)
अणु
	work_data->cbk = (व्योम *)cbk;
	work_data->areq = areq;

	INIT_WORK(&work_data->work, aपंचांगel_i2c_work_handler);
	schedule_work(&work_data->work);
पूर्ण
EXPORT_SYMBOL(aपंचांगel_i2c_enqueue);

अटल अंतरभूत माप_प्रकार aपंचांगel_i2c_wake_token_sz(u32 bus_clk_rate)
अणु
	u32 no_of_bits = DIV_ROUND_UP(TWLO_USEC * bus_clk_rate, USEC_PER_SEC);

	/* वापस the size of the wake_token in bytes */
	वापस DIV_ROUND_UP(no_of_bits, 8);
पूर्ण

अटल पूर्णांक device_sanity_check(काष्ठा i2c_client *client)
अणु
	काष्ठा aपंचांगel_i2c_cmd *cmd;
	पूर्णांक ret;

	cmd = kदो_स्मृति(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	aपंचांगel_i2c_init_पढ़ो_cmd(cmd);

	ret = aपंचांगel_i2c_send_receive(client, cmd);
	अगर (ret)
		जाओ मुक्त_cmd;

	/*
	 * It is vital that the Configuration, Data and OTP zones be locked
	 * prior to release पूर्णांकo the field of the प्रणाली containing the device.
	 * Failure to lock these zones may permit modअगरication of any secret
	 * keys and may lead to other security problems.
	 */
	अगर (cmd->data[LOCK_CONFIG_IDX] || cmd->data[LOCK_VALUE_IDX]) अणु
		dev_err(&client->dev, "Configuration or Data and OTP zones are unlocked!\n");
		ret = -ENOTSUPP;
	पूर्ण

	/* fall through */
मुक्त_cmd:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक aपंचांगel_i2c_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;
	u32 bus_clk_rate;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(dev, "I2C_FUNC_I2C not supported\n");
		वापस -ENODEV;
	पूर्ण

	bus_clk_rate = i2c_acpi_find_bus_speed(&client->adapter->dev);
	अगर (!bus_clk_rate) अणु
		ret = device_property_पढ़ो_u32(&client->adapter->dev,
					       "clock-frequency", &bus_clk_rate);
		अगर (ret) अणु
			dev_err(dev, "failed to read clock-frequency property\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (bus_clk_rate > 1000000L) अणु
		dev_err(dev, "%u exceeds maximum supported clock frequency (1MHz)\n",
			bus_clk_rate);
		वापस -EINVAL;
	पूर्ण

	i2c_priv = devm_kदो_स्मृति(dev, माप(*i2c_priv), GFP_KERNEL);
	अगर (!i2c_priv)
		वापस -ENOMEM;

	i2c_priv->client = client;
	mutex_init(&i2c_priv->lock);

	/*
	 * WAKE_TOKEN_MAX_SIZE was calculated क्रम the maximum bus_clk_rate -
	 * 1MHz. The previous bus_clk_rate check ensures us that wake_token_sz
	 * will always be smaller than or equal to WAKE_TOKEN_MAX_SIZE.
	 */
	i2c_priv->wake_token_sz = aपंचांगel_i2c_wake_token_sz(bus_clk_rate);

	स_रखो(i2c_priv->wake_token, 0, माप(i2c_priv->wake_token));

	atomic_set(&i2c_priv->tfm_count, 0);

	i2c_set_clientdata(client, i2c_priv);

	ret = device_sanity_check(client);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(aपंचांगel_i2c_probe);

MODULE_AUTHOR("Tudor Ambarus <tudor.ambarus@microchip.com>");
MODULE_DESCRIPTION("Microchip / Atmel ECC (I2C) driver");
MODULE_LICENSE("GPL v2");
