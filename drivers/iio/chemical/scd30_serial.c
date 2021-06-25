<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sensirion SCD30 carbon dioxide sensor serial driver
 *
 * Copyright (c) 2020 Tomasz Duszynski <tomasz.duszynski@octakon.com>
 */
#समावेश <linux/crc16.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/serdev.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "scd30.h"

#घोषणा SCD30_SERDEV_ADDR 0x61
#घोषणा SCD30_SERDEV_WRITE 0x06
#घोषणा SCD30_SERDEV_READ 0x03
#घोषणा SCD30_SERDEV_MAX_BUF_SIZE 17
#घोषणा SCD30_SERDEV_RX_HEADER_SIZE 3
#घोषणा SCD30_SERDEV_CRC_SIZE 2
#घोषणा SCD30_SERDEV_TIMEOUT msecs_to_jअगरfies(200)

काष्ठा scd30_serdev_priv अणु
	काष्ठा completion meas_पढ़ोy;
	अक्षर *buf;
	पूर्णांक num_expected;
	पूर्णांक num;
पूर्ण;

अटल u16 scd30_serdev_cmd_lookup_tbl[] = अणु
	[CMD_START_MEAS] = 0x0036,
	[CMD_STOP_MEAS] = 0x0037,
	[CMD_MEAS_INTERVAL] = 0x0025,
	[CMD_MEAS_READY] = 0x0027,
	[CMD_READ_MEAS] = 0x0028,
	[CMD_ASC] = 0x003a,
	[CMD_FRC] = 0x0039,
	[CMD_TEMP_OFFSET] = 0x003b,
	[CMD_FW_VERSION] = 0x0020,
	[CMD_RESET] = 0x0034,
पूर्ण;

अटल u16 scd30_serdev_calc_crc(स्थिर अक्षर *buf, पूर्णांक size)
अणु
	वापस crc16(0xffff, buf, size);
पूर्ण

अटल पूर्णांक scd30_serdev_xfer(काष्ठा scd30_state *state, अक्षर *txbuf, पूर्णांक txsize,
			     अक्षर *rxbuf, पूर्णांक rxsize)
अणु
	काष्ठा serdev_device *serdev = to_serdev_device(state->dev);
	काष्ठा scd30_serdev_priv *priv = state->priv;
	पूर्णांक ret;

	priv->buf = rxbuf;
	priv->num_expected = rxsize;
	priv->num = 0;

	ret = serdev_device_ग_लिखो(serdev, txbuf, txsize, SCD30_SERDEV_TIMEOUT);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != txsize)
		वापस -EIO;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&priv->meas_पढ़ोy, SCD30_SERDEV_TIMEOUT);
	अगर (ret < 0)
		वापस ret;
	अगर (!ret)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक scd30_serdev_command(काष्ठा scd30_state *state, क्रमागत scd30_cmd cmd, u16 arg,
				व्योम *response, पूर्णांक size)
अणु
	/*
	 * Communication over serial line is based on modbus protocol (or rather
	 * its variation called modbus over serial to be precise). Upon
	 * receiving a request device should reply with response.
	 *
	 * Frame below represents a request message. Each field takes
	 * exactly one byte.
	 *
	 * +------+------+-----+-----+-------+-------+-----+-----+
	 * | dev  | op   | reg | reg | byte1 | byte0 | crc | crc |
	 * | addr | code | msb | lsb |       |       | lsb | msb |
	 * +------+------+-----+-----+-------+-------+-----+-----+
	 *
	 * The message device replies with depends on the 'op code' field from
	 * the request. In हाल it was set to SCD30_SERDEV_WRITE sensor should
	 * reply with unchanged request. Otherwise 'op code' was set to
	 * SCD30_SERDEV_READ and response looks like the one below. As with
	 * request, each field takes one byte.
	 *
	 * +------+------+--------+-------+-----+-------+-----+-----+
	 * | dev  | op   | num of | byte0 | ... | byteN | crc | crc |
	 * | addr | code | bytes  |       |     |       | lsb | msb |
	 * +------+------+--------+-------+-----+-------+-----+-----+
	 */
	अक्षर txbuf[SCD30_SERDEV_MAX_BUF_SIZE] = अणु SCD30_SERDEV_ADDR पूर्ण,
	     rxbuf[SCD30_SERDEV_MAX_BUF_SIZE];
	पूर्णांक ret, rxsize, txsize = 2;
	अक्षर *rsp = response;
	u16 crc;

	put_unaligned_be16(scd30_serdev_cmd_lookup_tbl[cmd], txbuf + txsize);
	txsize += 2;

	अगर (rsp) अणु
		txbuf[1] = SCD30_SERDEV_READ;
		अगर (cmd == CMD_READ_MEAS)
			/* number of u16 words to पढ़ो */
			put_unaligned_be16(size / 2, txbuf + txsize);
		अन्यथा
			put_unaligned_be16(0x0001, txbuf + txsize);
		txsize += 2;
		crc = scd30_serdev_calc_crc(txbuf, txsize);
		put_unaligned_le16(crc, txbuf + txsize);
		txsize += 2;
		rxsize = SCD30_SERDEV_RX_HEADER_SIZE + size + SCD30_SERDEV_CRC_SIZE;
	पूर्ण अन्यथा अणु
		अगर ((cmd == CMD_STOP_MEAS) || (cmd == CMD_RESET))
			arg = 0x0001;

		txbuf[1] = SCD30_SERDEV_WRITE;
		put_unaligned_be16(arg, txbuf + txsize);
		txsize += 2;
		crc = scd30_serdev_calc_crc(txbuf, txsize);
		put_unaligned_le16(crc, txbuf + txsize);
		txsize += 2;
		rxsize = txsize;
	पूर्ण

	ret = scd30_serdev_xfer(state, txbuf, txsize, rxbuf, rxsize);
	अगर (ret)
		वापस ret;

	चयन (txbuf[1]) अणु
	हाल SCD30_SERDEV_WRITE:
		अगर (स_भेद(txbuf, rxbuf, txsize)) अणु
			dev_err(state->dev, "wrong message received\n");
			वापस -EIO;
		पूर्ण
		अवरोध;
	हाल SCD30_SERDEV_READ:
		अगर (rxbuf[2] != (rxsize - SCD30_SERDEV_RX_HEADER_SIZE - SCD30_SERDEV_CRC_SIZE)) अणु
			dev_err(state->dev, "received data size does not match header\n");
			वापस -EIO;
		पूर्ण

		rxsize -= SCD30_SERDEV_CRC_SIZE;
		crc = get_unaligned_le16(rxbuf + rxsize);
		अगर (crc != scd30_serdev_calc_crc(rxbuf, rxsize)) अणु
			dev_err(state->dev, "data integrity check failed\n");
			वापस -EIO;
		पूर्ण

		rxsize -= SCD30_SERDEV_RX_HEADER_SIZE;
		स_नकल(rsp, rxbuf + SCD30_SERDEV_RX_HEADER_SIZE, rxsize);
		अवरोध;
	शेष:
		dev_err(state->dev, "received unknown op code\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scd30_serdev_receive_buf(काष्ठा serdev_device *serdev,
				    स्थिर अचिन्हित अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा iio_dev *indio_dev = serdev_device_get_drvdata(serdev);
	काष्ठा scd30_serdev_priv *priv;
	काष्ठा scd30_state *state;
	पूर्णांक num;

	अगर (!indio_dev)
		वापस 0;

	state = iio_priv(indio_dev);
	priv = state->priv;

	/* just in हाल sensor माला_दो some unexpected bytes on the bus */
	अगर (!priv->buf)
		वापस 0;

	अगर (priv->num + size >= priv->num_expected)
		num = priv->num_expected - priv->num;
	अन्यथा
		num = size;

	स_नकल(priv->buf + priv->num, buf, num);
	priv->num += num;

	अगर (priv->num == priv->num_expected) अणु
		priv->buf = शून्य;
		complete(&priv->meas_पढ़ोy);
	पूर्ण

	वापस num;
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops scd30_serdev_ops = अणु
	.receive_buf = scd30_serdev_receive_buf,
	.ग_लिखो_wakeup = serdev_device_ग_लिखो_wakeup,
पूर्ण;

अटल पूर्णांक scd30_serdev_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा device *dev = &serdev->dev;
	काष्ठा scd30_serdev_priv *priv;
	पूर्णांक irq, ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	init_completion(&priv->meas_पढ़ोy);
	serdev_device_set_client_ops(serdev, &scd30_serdev_ops);

	ret = devm_serdev_device_खोलो(dev, serdev);
	अगर (ret)
		वापस ret;

	serdev_device_set_baudrate(serdev, 19200);
	serdev_device_set_flow_control(serdev, false);

	ret = serdev_device_set_parity(serdev, SERDEV_PARITY_NONE);
	अगर (ret)
		वापस ret;

	irq = fwnode_irq_get(dev_fwnode(dev), 0);

	वापस scd30_probe(dev, irq, KBUILD_MODNAME, priv, scd30_serdev_command);
पूर्ण

अटल स्थिर काष्ठा of_device_id scd30_serdev_of_match[] = अणु
	अणु .compatible = "sensirion,scd30" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, scd30_serdev_of_match);

अटल काष्ठा serdev_device_driver scd30_serdev_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = scd30_serdev_of_match,
		.pm = &scd30_pm_ops,
	पूर्ण,
	.probe = scd30_serdev_probe,
पूर्ण;
module_serdev_device_driver(scd30_serdev_driver);

MODULE_AUTHOR("Tomasz Duszynski <tomasz.duszynski@octakon.com>");
MODULE_DESCRIPTION("Sensirion SCD30 carbon dioxide sensor serial driver");
MODULE_LICENSE("GPL v2");
