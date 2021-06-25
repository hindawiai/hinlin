<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Analog Devices AD-FMCOMMS1-EBZ board I2C-SPI bridge driver
 *
 * Copyright 2012 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा SPI_XCOMM_SETTINGS_LEN_OFFSET		10
#घोषणा SPI_XCOMM_SETTINGS_3WIRE		BIT(6)
#घोषणा SPI_XCOMM_SETTINGS_CS_HIGH		BIT(5)
#घोषणा SPI_XCOMM_SETTINGS_SAMPLE_END		BIT(4)
#घोषणा SPI_XCOMM_SETTINGS_CPHA			BIT(3)
#घोषणा SPI_XCOMM_SETTINGS_CPOL			BIT(2)
#घोषणा SPI_XCOMM_SETTINGS_CLOCK_DIV_MASK	0x3
#घोषणा SPI_XCOMM_SETTINGS_CLOCK_DIV_64		0x2
#घोषणा SPI_XCOMM_SETTINGS_CLOCK_DIV_16		0x1
#घोषणा SPI_XCOMM_SETTINGS_CLOCK_DIV_4		0x0

#घोषणा SPI_XCOMM_CMD_UPDATE_CONFIG	0x03
#घोषणा SPI_XCOMM_CMD_WRITE		0x04

#घोषणा SPI_XCOMM_CLOCK 48000000

काष्ठा spi_xcomm अणु
	काष्ठा i2c_client *i2c;

	uपूर्णांक16_t settings;
	uपूर्णांक16_t chipselect;

	अचिन्हित पूर्णांक current_speed;

	uपूर्णांक8_t buf[63];
पूर्ण;

अटल पूर्णांक spi_xcomm_sync_config(काष्ठा spi_xcomm *spi_xcomm, अचिन्हित पूर्णांक len)
अणु
	uपूर्णांक16_t settings;
	uपूर्णांक8_t *buf = spi_xcomm->buf;

	settings = spi_xcomm->settings;
	settings |= len << SPI_XCOMM_SETTINGS_LEN_OFFSET;

	buf[0] = SPI_XCOMM_CMD_UPDATE_CONFIG;
	put_unaligned_be16(settings, &buf[1]);
	put_unaligned_be16(spi_xcomm->chipselect, &buf[3]);

	वापस i2c_master_send(spi_xcomm->i2c, buf, 5);
पूर्ण

अटल व्योम spi_xcomm_chipselect(काष्ठा spi_xcomm *spi_xcomm,
	काष्ठा spi_device *spi, पूर्णांक is_active)
अणु
	अचिन्हित दीर्घ cs = spi->chip_select;
	uपूर्णांक16_t chipselect = spi_xcomm->chipselect;

	अगर (is_active)
		chipselect |= BIT(cs);
	अन्यथा
		chipselect &= ~BIT(cs);

	spi_xcomm->chipselect = chipselect;
पूर्ण

अटल पूर्णांक spi_xcomm_setup_transfer(काष्ठा spi_xcomm *spi_xcomm,
	काष्ठा spi_device *spi, काष्ठा spi_transfer *t, अचिन्हित पूर्णांक *settings)
अणु
	अगर (t->len > 62)
		वापस -EINVAL;

	अगर (t->speed_hz != spi_xcomm->current_speed) अणु
		अचिन्हित पूर्णांक भागider;

		भागider = DIV_ROUND_UP(SPI_XCOMM_CLOCK, t->speed_hz);
		अगर (भागider >= 64)
			*settings |= SPI_XCOMM_SETTINGS_CLOCK_DIV_64;
		अन्यथा अगर (भागider >= 16)
			*settings |= SPI_XCOMM_SETTINGS_CLOCK_DIV_16;
		अन्यथा
			*settings |= SPI_XCOMM_SETTINGS_CLOCK_DIV_4;

		spi_xcomm->current_speed = t->speed_hz;
	पूर्ण

	अगर (spi->mode & SPI_CPOL)
		*settings |= SPI_XCOMM_SETTINGS_CPOL;
	अन्यथा
		*settings &= ~SPI_XCOMM_SETTINGS_CPOL;

	अगर (spi->mode & SPI_CPHA)
		*settings &= ~SPI_XCOMM_SETTINGS_CPHA;
	अन्यथा
		*settings |= SPI_XCOMM_SETTINGS_CPHA;

	अगर (spi->mode & SPI_3WIRE)
		*settings |= SPI_XCOMM_SETTINGS_3WIRE;
	अन्यथा
		*settings &= ~SPI_XCOMM_SETTINGS_3WIRE;

	वापस 0;
पूर्ण

अटल पूर्णांक spi_xcomm_txrx_bufs(काष्ठा spi_xcomm *spi_xcomm,
	काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	पूर्णांक ret;

	अगर (t->tx_buf) अणु
		spi_xcomm->buf[0] = SPI_XCOMM_CMD_WRITE;
		स_नकल(spi_xcomm->buf + 1, t->tx_buf, t->len);

		ret = i2c_master_send(spi_xcomm->i2c, spi_xcomm->buf, t->len + 1);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret != t->len + 1)
			वापस -EIO;
	पूर्ण अन्यथा अगर (t->rx_buf) अणु
		ret = i2c_master_recv(spi_xcomm->i2c, t->rx_buf, t->len);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret != t->len)
			वापस -EIO;
	पूर्ण

	वापस t->len;
पूर्ण

अटल पूर्णांक spi_xcomm_transfer_one(काष्ठा spi_master *master,
	काष्ठा spi_message *msg)
अणु
	काष्ठा spi_xcomm *spi_xcomm = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक settings = spi_xcomm->settings;
	काष्ठा spi_device *spi = msg->spi;
	अचिन्हित cs_change = 0;
	काष्ठा spi_transfer *t;
	bool is_first = true;
	पूर्णांक status = 0;
	bool is_last;

	spi_xcomm_chipselect(spi_xcomm, spi, true);

	list_क्रम_each_entry(t, &msg->transfers, transfer_list) अणु

		अगर (!t->tx_buf && !t->rx_buf && t->len) अणु
			status = -EINVAL;
			अवरोध;
		पूर्ण

		status = spi_xcomm_setup_transfer(spi_xcomm, spi, t, &settings);
		अगर (status < 0)
			अवरोध;

		is_last = list_is_last(&t->transfer_list, &msg->transfers);
		cs_change = t->cs_change;

		अगर (cs_change ^ is_last)
			settings |= BIT(5);
		अन्यथा
			settings &= ~BIT(5);

		अगर (t->rx_buf) अणु
			spi_xcomm->settings = settings;
			status = spi_xcomm_sync_config(spi_xcomm, t->len);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (settings != spi_xcomm->settings || is_first) अणु
			spi_xcomm->settings = settings;
			status = spi_xcomm_sync_config(spi_xcomm, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		अगर (t->len) अणु
			status = spi_xcomm_txrx_bufs(spi_xcomm, spi, t);

			अगर (status < 0)
				अवरोध;

			अगर (status > 0)
				msg->actual_length += status;
		पूर्ण
		status = 0;

		spi_transfer_delay_exec(t);

		is_first = false;
	पूर्ण

	अगर (status != 0 || !cs_change)
		spi_xcomm_chipselect(spi_xcomm, spi, false);

	msg->status = status;
	spi_finalize_current_message(master);

	वापस status;
पूर्ण

अटल पूर्णांक spi_xcomm_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा spi_xcomm *spi_xcomm;
	काष्ठा spi_master *master;
	पूर्णांक ret;

	master = spi_alloc_master(&i2c->dev, माप(*spi_xcomm));
	अगर (!master)
		वापस -ENOMEM;

	spi_xcomm = spi_master_get_devdata(master);
	spi_xcomm->i2c = i2c;

	master->num_chipselect = 16;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_3WIRE;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->transfer_one_message = spi_xcomm_transfer_one;
	master->dev.of_node = i2c->dev.of_node;
	i2c_set_clientdata(i2c, master);

	ret = devm_spi_रेजिस्टर_master(&i2c->dev, master);
	अगर (ret < 0)
		spi_master_put(master);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id spi_xcomm_ids[] = अणु
	अणु "spi-xcomm" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, spi_xcomm_ids);

अटल काष्ठा i2c_driver spi_xcomm_driver = अणु
	.driver = अणु
		.name	= "spi-xcomm",
	पूर्ण,
	.id_table	= spi_xcomm_ids,
	.probe		= spi_xcomm_probe,
पूर्ण;
module_i2c_driver(spi_xcomm_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD-FMCOMMS1-EBZ board I2C-SPI bridge driver");
