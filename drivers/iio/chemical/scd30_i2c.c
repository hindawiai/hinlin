<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sensirion SCD30 carbon dioxide sensor i2c driver
 *
 * Copyright (c) 2020 Tomasz Duszynski <tomasz.duszynski@octakon.com>
 *
 * I2C slave address: 0x61
 */
#समावेश <linux/crc8.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "scd30.h"

#घोषणा SCD30_I2C_MAX_BUF_SIZE 18
#घोषणा SCD30_I2C_CRC8_POLYNOMIAL 0x31

अटल u16 scd30_i2c_cmd_lookup_tbl[] = अणु
	[CMD_START_MEAS] = 0x0010,
	[CMD_STOP_MEAS] = 0x0104,
	[CMD_MEAS_INTERVAL] = 0x4600,
	[CMD_MEAS_READY] = 0x0202,
	[CMD_READ_MEAS] = 0x0300,
	[CMD_ASC] = 0x5306,
	[CMD_FRC] = 0x5204,
	[CMD_TEMP_OFFSET] = 0x5403,
	[CMD_FW_VERSION] = 0xd100,
	[CMD_RESET] = 0xd304,
पूर्ण;

DECLARE_CRC8_TABLE(scd30_i2c_crc8_tbl);

अटल पूर्णांक scd30_i2c_xfer(काष्ठा scd30_state *state, अक्षर *txbuf, पूर्णांक txsize,
			  अक्षर *rxbuf, पूर्णांक rxsize)
अणु
	काष्ठा i2c_client *client = to_i2c_client(state->dev);
	पूर्णांक ret;

	/*
	 * repeated start is not supported hence instead of sending two i2c
	 * messages in a row we send one by one
	 */
	ret = i2c_master_send(client, txbuf, txsize);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != txsize)
		वापस -EIO;

	अगर (!rxbuf)
		वापस 0;

	ret = i2c_master_recv(client, rxbuf, rxsize);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != rxsize)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक scd30_i2c_command(काष्ठा scd30_state *state, क्रमागत scd30_cmd cmd, u16 arg,
			     व्योम *response, पूर्णांक size)
अणु
	अक्षर buf[SCD30_I2C_MAX_BUF_SIZE];
	अक्षर *rsp = response;
	पूर्णांक i, ret;
	अक्षर crc;

	put_unaligned_be16(scd30_i2c_cmd_lookup_tbl[cmd], buf);
	i = 2;

	अगर (rsp) अणु
		/* each two bytes are followed by a crc8 */
		size += size / 2;
	पूर्ण अन्यथा अणु
		put_unaligned_be16(arg, buf + i);
		crc = crc8(scd30_i2c_crc8_tbl, buf + i, 2, CRC8_INIT_VALUE);
		i += 2;
		buf[i] = crc;
		i += 1;

		/* commands below करोn't take an argument */
		अगर ((cmd == CMD_STOP_MEAS) || (cmd == CMD_RESET))
			i -= 3;
	पूर्ण

	ret = scd30_i2c_xfer(state, buf, i, buf, size);
	अगर (ret)
		वापस ret;

	/* validate received data and strip off crc bytes */
	क्रम (i = 0; i < size; i += 3) अणु
		crc = crc8(scd30_i2c_crc8_tbl, buf + i, 2, CRC8_INIT_VALUE);
		अगर (crc != buf[i + 2]) अणु
			dev_err(state->dev, "data integrity check failed\n");
			वापस -EIO;
		पूर्ण

		*rsp++ = buf[i];
		*rsp++ = buf[i + 1];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scd30_i2c_probe(काष्ठा i2c_client *client)
अणु
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -EOPNOTSUPP;

	crc8_populate_msb(scd30_i2c_crc8_tbl, SCD30_I2C_CRC8_POLYNOMIAL);

	वापस scd30_probe(&client->dev, client->irq, client->name, शून्य, scd30_i2c_command);
पूर्ण

अटल स्थिर काष्ठा of_device_id scd30_i2c_of_match[] = अणु
	अणु .compatible = "sensirion,scd30" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, scd30_i2c_of_match);

अटल काष्ठा i2c_driver scd30_i2c_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = scd30_i2c_of_match,
		.pm = &scd30_pm_ops,
	पूर्ण,
	.probe_new = scd30_i2c_probe,
पूर्ण;
module_i2c_driver(scd30_i2c_driver);

MODULE_AUTHOR("Tomasz Duszynski <tomasz.duszynski@octakon.com>");
MODULE_DESCRIPTION("Sensirion SCD30 carbon dioxide sensor i2c driver");
MODULE_LICENSE("GPL v2");
