<शैली गुरु>
/*
 *
 *   Copyright (c) 2011, 2012, Qualcomm Atheros Communications Inc.
 *   Copyright (c) 2014, I2SE GmbH
 *
 *   Permission to use, copy, modअगरy, and/or distribute this software
 *   क्रम any purpose with or without fee is hereby granted, provided
 *   that the above copyright notice and this permission notice appear
 *   in all copies.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, सूचीECT, INसूचीECT, OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*   This module implements the Qualcomm Atheros SPI protocol क्रम
 *   kernel-based SPI device.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spi/spi.h>

#समावेश "qca_7k.h"

व्योम
qcaspi_spi_error(काष्ठा qcaspi *qca)
अणु
	अगर (qca->sync != QCASPI_SYNC_READY)
		वापस;

	netdev_err(qca->net_dev, "spi error\n");
	qca->sync = QCASPI_SYNC_UNKNOWN;
	qca->stats.spi_err++;
पूर्ण

पूर्णांक
qcaspi_पढ़ो_रेजिस्टर(काष्ठा qcaspi *qca, u16 reg, u16 *result)
अणु
	__be16 rx_data;
	__be16 tx_data;
	काष्ठा spi_transfer transfer[2];
	काष्ठा spi_message msg;
	पूर्णांक ret;

	स_रखो(transfer, 0, माप(transfer));

	spi_message_init(&msg);

	tx_data = cpu_to_be16(QCA7K_SPI_READ | QCA7K_SPI_INTERNAL | reg);
	*result = 0;

	transfer[0].tx_buf = &tx_data;
	transfer[0].len = QCASPI_CMD_LEN;
	transfer[1].rx_buf = &rx_data;
	transfer[1].len = QCASPI_CMD_LEN;

	spi_message_add_tail(&transfer[0], &msg);

	अगर (qca->legacy_mode) अणु
		spi_sync(qca->spi_dev, &msg);
		spi_message_init(&msg);
	पूर्ण
	spi_message_add_tail(&transfer[1], &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	अगर (!ret)
		ret = msg.status;

	अगर (ret)
		qcaspi_spi_error(qca);
	अन्यथा
		*result = be16_to_cpu(rx_data);

	वापस ret;
पूर्ण

अटल पूर्णांक
__qcaspi_ग_लिखो_रेजिस्टर(काष्ठा qcaspi *qca, u16 reg, u16 value)
अणु
	__be16 tx_data[2];
	काष्ठा spi_transfer transfer[2];
	काष्ठा spi_message msg;
	पूर्णांक ret;

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	tx_data[0] = cpu_to_be16(QCA7K_SPI_WRITE | QCA7K_SPI_INTERNAL | reg);
	tx_data[1] = cpu_to_be16(value);

	transfer[0].tx_buf = &tx_data[0];
	transfer[0].len = QCASPI_CMD_LEN;
	transfer[1].tx_buf = &tx_data[1];
	transfer[1].len = QCASPI_CMD_LEN;

	spi_message_add_tail(&transfer[0], &msg);
	अगर (qca->legacy_mode) अणु
		spi_sync(qca->spi_dev, &msg);
		spi_message_init(&msg);
	पूर्ण
	spi_message_add_tail(&transfer[1], &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	अगर (!ret)
		ret = msg.status;

	अगर (ret)
		qcaspi_spi_error(qca);

	वापस ret;
पूर्ण

पूर्णांक
qcaspi_ग_लिखो_रेजिस्टर(काष्ठा qcaspi *qca, u16 reg, u16 value, पूर्णांक retry)
अणु
	पूर्णांक ret, i = 0;
	u16 confirmed;

	करो अणु
		ret = __qcaspi_ग_लिखो_रेजिस्टर(qca, reg, value);
		अगर (ret)
			वापस ret;

		अगर (!retry)
			वापस 0;

		ret = qcaspi_पढ़ो_रेजिस्टर(qca, reg, &confirmed);
		अगर (ret)
			वापस ret;

		ret = confirmed != value;
		अगर (!ret)
			वापस 0;

		i++;
		qca->stats.ग_लिखो_verअगरy_failed++;

	पूर्ण जबतक (i <= retry);

	वापस ret;
पूर्ण
