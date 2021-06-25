<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_spi_device.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * SPI access functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश <linux/spi/spi.h>

#समावेश "cxd2880_spi_device.h"

अटल पूर्णांक cxd2880_spi_device_ग_लिखो(काष्ठा cxd2880_spi *spi,
				    स्थिर u8 *data, u32 size)
अणु
	काष्ठा cxd2880_spi_device *spi_device = शून्य;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx;
	पूर्णांक result = 0;

	अगर (!spi || !spi->user || !data || size == 0)
		वापस -EINVAL;

	spi_device = spi->user;

	स_रखो(&tx, 0, माप(tx));
	tx.tx_buf = data;
	tx.len = size;

	spi_message_init(&msg);
	spi_message_add_tail(&tx, &msg);
	result = spi_sync(spi_device->spi, &msg);

	अगर (result < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_spi_device_ग_लिखो_पढ़ो(काष्ठा cxd2880_spi *spi,
					 स्थिर u8 *tx_data,
					 u32 tx_size,
					 u8 *rx_data,
					 u32 rx_size)
अणु
	काष्ठा cxd2880_spi_device *spi_device = शून्य;
	पूर्णांक result = 0;

	अगर (!spi || !spi->user || !tx_data ||
	    !tx_size || !rx_data || !rx_size)
		वापस -EINVAL;

	spi_device = spi->user;

	result = spi_ग_लिखो_then_पढ़ो(spi_device->spi, tx_data,
				     tx_size, rx_data, rx_size);
	अगर (result < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक
cxd2880_spi_device_initialize(काष्ठा cxd2880_spi_device *spi_device,
			      क्रमागत cxd2880_spi_mode mode,
			      u32 speed_hz)
अणु
	पूर्णांक result = 0;
	काष्ठा spi_device *spi = spi_device->spi;

	चयन (mode) अणु
	हाल CXD2880_SPI_MODE_0:
		spi->mode = SPI_MODE_0;
		अवरोध;
	हाल CXD2880_SPI_MODE_1:
		spi->mode = SPI_MODE_1;
		अवरोध;
	हाल CXD2880_SPI_MODE_2:
		spi->mode = SPI_MODE_2;
		अवरोध;
	हाल CXD2880_SPI_MODE_3:
		spi->mode = SPI_MODE_3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spi->max_speed_hz = speed_hz;
	spi->bits_per_word = 8;
	result = spi_setup(spi);
	अगर (result != 0) अणु
		pr_err("spi_setup failed %d\n", result);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxd2880_spi_device_create_spi(काष्ठा cxd2880_spi *spi,
				  काष्ठा cxd2880_spi_device *spi_device)
अणु
	अगर (!spi || !spi_device)
		वापस -EINVAL;

	spi->पढ़ो = शून्य;
	spi->ग_लिखो = cxd2880_spi_device_ग_लिखो;
	spi->ग_लिखो_पढ़ो = cxd2880_spi_device_ग_लिखो_पढ़ो;
	spi->flags = 0;
	spi->user = spi_device;

	वापस 0;
पूर्ण
