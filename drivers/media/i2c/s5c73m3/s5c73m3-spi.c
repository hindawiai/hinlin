<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung LSI S5C73M3 8M pixel camera driver
 *
 * Copyright (C) 2012, Samsung Electronics, Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 * Andrzej Hajda <a.hajda@samsung.com>
 */

#समावेश <linux/sizes.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/media.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

#समावेश "s5c73m3.h"

#घोषणा S5C73M3_SPI_DRV_NAME "S5C73M3-SPI"

अटल स्थिर काष्ठा of_device_id s5c73m3_spi_ids[] = अणु
	अणु .compatible = "samsung,s5c73m3" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s5c73m3_spi_ids);

क्रमागत spi_direction अणु
	SPI_सूची_RX,
	SPI_सूची_TX
पूर्ण;

अटल पूर्णांक spi_xmit(काष्ठा spi_device *spi_dev, व्योम *addr, स्थिर पूर्णांक len,
							क्रमागत spi_direction dir)
अणु
	काष्ठा spi_message msg;
	पूर्णांक r;
	काष्ठा spi_transfer xfer = अणु
		.len	= len,
	पूर्ण;

	अगर (dir == SPI_सूची_TX)
		xfer.tx_buf = addr;
	अन्यथा
		xfer.rx_buf = addr;

	अगर (spi_dev == शून्य) अणु
		pr_err("SPI device is uninitialized\n");
		वापस -ENODEV;
	पूर्ण

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	r = spi_sync(spi_dev, &msg);
	अगर (r < 0)
		dev_err(&spi_dev->dev, "%s spi_sync failed %d\n", __func__, r);

	वापस r;
पूर्ण

पूर्णांक s5c73m3_spi_ग_लिखो(काष्ठा s5c73m3 *state, स्थिर व्योम *addr,
		      स्थिर अचिन्हित पूर्णांक len, स्थिर अचिन्हित पूर्णांक tx_size)
अणु
	काष्ठा spi_device *spi_dev = state->spi_dev;
	u32 count = len / tx_size;
	u32 extra = len % tx_size;
	अचिन्हित पूर्णांक i, j = 0;
	u8 padding[32];
	पूर्णांक r = 0;

	स_रखो(padding, 0, माप(padding));

	क्रम (i = 0; i < count; i++) अणु
		r = spi_xmit(spi_dev, (व्योम *)addr + j, tx_size, SPI_सूची_TX);
		अगर (r < 0)
			वापस r;
		j += tx_size;
	पूर्ण

	अगर (extra > 0) अणु
		r = spi_xmit(spi_dev, (व्योम *)addr + j, extra, SPI_सूची_TX);
		अगर (r < 0)
			वापस r;
	पूर्ण

	वापस spi_xmit(spi_dev, padding, माप(padding), SPI_सूची_TX);
पूर्ण

पूर्णांक s5c73m3_spi_पढ़ो(काष्ठा s5c73m3 *state, व्योम *addr,
		     स्थिर अचिन्हित पूर्णांक len, स्थिर अचिन्हित पूर्णांक tx_size)
अणु
	काष्ठा spi_device *spi_dev = state->spi_dev;
	u32 count = len / tx_size;
	u32 extra = len % tx_size;
	अचिन्हित पूर्णांक i, j = 0;
	पूर्णांक r = 0;

	क्रम (i = 0; i < count; i++) अणु
		r = spi_xmit(spi_dev, addr + j, tx_size, SPI_सूची_RX);
		अगर (r < 0)
			वापस r;
		j += tx_size;
	पूर्ण

	अगर (extra > 0)
		वापस spi_xmit(spi_dev, addr + j, extra, SPI_सूची_RX);

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक r;
	काष्ठा s5c73m3 *state = container_of(spi->dev.driver, काष्ठा s5c73m3,
					     spidrv.driver);
	spi->bits_per_word = 32;

	r = spi_setup(spi);
	अगर (r < 0) अणु
		dev_err(&spi->dev, "spi_setup() failed\n");
		वापस r;
	पूर्ण

	mutex_lock(&state->lock);
	state->spi_dev = spi;
	mutex_unlock(&state->lock);

	v4l2_info(&state->sensor_sd, "S5C73M3 SPI probed successfully\n");
	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस 0;
पूर्ण

पूर्णांक s5c73m3_रेजिस्टर_spi_driver(काष्ठा s5c73m3 *state)
अणु
	काष्ठा spi_driver *spidrv = &state->spidrv;

	spidrv->हटाओ = s5c73m3_spi_हटाओ;
	spidrv->probe = s5c73m3_spi_probe;
	spidrv->driver.name = S5C73M3_SPI_DRV_NAME;
	spidrv->driver.of_match_table = s5c73m3_spi_ids;

	वापस spi_रेजिस्टर_driver(spidrv);
पूर्ण

व्योम s5c73m3_unरेजिस्टर_spi_driver(काष्ठा s5c73m3 *state)
अणु
	spi_unरेजिस्टर_driver(&state->spidrv);
पूर्ण
