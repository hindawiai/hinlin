<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NXP SC18IS602/603 SPI driver
 *
 * Copyright (C) Guenter Roeck <linux@roeck-us.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/sc18is602.h>
#समावेश <linux/gpio/consumer.h>

क्रमागत chips अणु sc18is602, sc18is602b, sc18is603 पूर्ण;

#घोषणा SC18IS602_बफ_मान		200
#घोषणा SC18IS602_CLOCK			7372000

#घोषणा SC18IS602_MODE_CPHA		BIT(2)
#घोषणा SC18IS602_MODE_CPOL		BIT(3)
#घोषणा SC18IS602_MODE_LSB_FIRST	BIT(5)
#घोषणा SC18IS602_MODE_CLOCK_DIV_4	0x0
#घोषणा SC18IS602_MODE_CLOCK_DIV_16	0x1
#घोषणा SC18IS602_MODE_CLOCK_DIV_64	0x2
#घोषणा SC18IS602_MODE_CLOCK_DIV_128	0x3

काष्ठा sc18is602 अणु
	काष्ठा spi_master	*master;
	काष्ठा device		*dev;
	u8			ctrl;
	u32			freq;
	u32			speed;

	/* I2C data */
	काष्ठा i2c_client	*client;
	क्रमागत chips		id;
	u8			buffer[SC18IS602_बफ_मान + 1];
	पूर्णांक			tlen;	/* Data queued क्रम tx in buffer */
	पूर्णांक			rindex;	/* Receive data index in buffer */

	काष्ठा gpio_desc	*reset;
पूर्ण;

अटल पूर्णांक sc18is602_रुको_पढ़ोy(काष्ठा sc18is602 *hw, पूर्णांक len)
अणु
	पूर्णांक i, err;
	पूर्णांक usecs = 1000000 * len / hw->speed + 1;
	u8 dummy[1];

	क्रम (i = 0; i < 10; i++) अणु
		err = i2c_master_recv(hw->client, dummy, 1);
		अगर (err >= 0)
			वापस 0;
		usleep_range(usecs, usecs * 2);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sc18is602_txrx(काष्ठा sc18is602 *hw, काष्ठा spi_message *msg,
			  काष्ठा spi_transfer *t, bool करो_transfer)
अणु
	अचिन्हित पूर्णांक len = t->len;
	पूर्णांक ret;

	अगर (hw->tlen == 0) अणु
		/* First byte (I2C command) is chip select */
		hw->buffer[0] = 1 << msg->spi->chip_select;
		hw->tlen = 1;
		hw->rindex = 0;
	पूर्ण
	/*
	 * We can not immediately send data to the chip, since each I2C message
	 * resembles a full SPI message (from CS active to CS inactive).
	 * Enqueue messages up to the first पढ़ो or until करो_transfer is true.
	 */
	अगर (t->tx_buf) अणु
		स_नकल(&hw->buffer[hw->tlen], t->tx_buf, len);
		hw->tlen += len;
		अगर (t->rx_buf)
			करो_transfer = true;
		अन्यथा
			hw->rindex = hw->tlen - 1;
	पूर्ण अन्यथा अगर (t->rx_buf) अणु
		/*
		 * For receive-only transfers we still need to perक्रमm a dummy
		 * ग_लिखो to receive data from the SPI chip.
		 * Read data starts at the end of transmit data (minus 1 to
		 * account क्रम CS).
		 */
		hw->rindex = hw->tlen - 1;
		स_रखो(&hw->buffer[hw->tlen], 0, len);
		hw->tlen += len;
		करो_transfer = true;
	पूर्ण

	अगर (करो_transfer && hw->tlen > 1) अणु
		ret = sc18is602_रुको_पढ़ोy(hw, SC18IS602_बफ_मान);
		अगर (ret < 0)
			वापस ret;
		ret = i2c_master_send(hw->client, hw->buffer, hw->tlen);
		अगर (ret < 0)
			वापस ret;
		अगर (ret != hw->tlen)
			वापस -EIO;

		अगर (t->rx_buf) अणु
			पूर्णांक rlen = hw->rindex + len;

			ret = sc18is602_रुको_पढ़ोy(hw, hw->tlen);
			अगर (ret < 0)
				वापस ret;
			ret = i2c_master_recv(hw->client, hw->buffer, rlen);
			अगर (ret < 0)
				वापस ret;
			अगर (ret != rlen)
				वापस -EIO;
			स_नकल(t->rx_buf, &hw->buffer[hw->rindex], len);
		पूर्ण
		hw->tlen = 0;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक sc18is602_setup_transfer(काष्ठा sc18is602 *hw, u32 hz, u8 mode)
अणु
	u8 ctrl = 0;
	पूर्णांक ret;

	अगर (mode & SPI_CPHA)
		ctrl |= SC18IS602_MODE_CPHA;
	अगर (mode & SPI_CPOL)
		ctrl |= SC18IS602_MODE_CPOL;
	अगर (mode & SPI_LSB_FIRST)
		ctrl |= SC18IS602_MODE_LSB_FIRST;

	/* Find the बंदst घड़ी speed */
	अगर (hz >= hw->freq / 4) अणु
		ctrl |= SC18IS602_MODE_CLOCK_DIV_4;
		hw->speed = hw->freq / 4;
	पूर्ण अन्यथा अगर (hz >= hw->freq / 16) अणु
		ctrl |= SC18IS602_MODE_CLOCK_DIV_16;
		hw->speed = hw->freq / 16;
	पूर्ण अन्यथा अगर (hz >= hw->freq / 64) अणु
		ctrl |= SC18IS602_MODE_CLOCK_DIV_64;
		hw->speed = hw->freq / 64;
	पूर्ण अन्यथा अणु
		ctrl |= SC18IS602_MODE_CLOCK_DIV_128;
		hw->speed = hw->freq / 128;
	पूर्ण

	/*
	 * Don't करो anything अगर the control value did not change. The initial
	 * value of 0xff क्रम hw->ctrl ensures that the correct mode will be set
	 * with the first call to this function.
	 */
	अगर (ctrl == hw->ctrl)
		वापस 0;

	ret = i2c_smbus_ग_लिखो_byte_data(hw->client, 0xf0, ctrl);
	अगर (ret < 0)
		वापस ret;

	hw->ctrl = ctrl;

	वापस 0;
पूर्ण

अटल पूर्णांक sc18is602_check_transfer(काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *t, पूर्णांक tlen)
अणु
	अगर (t && t->len + tlen > SC18IS602_बफ_मान + 1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sc18is602_transfer_one(काष्ठा spi_master *master,
				  काष्ठा spi_message *m)
अणु
	काष्ठा sc18is602 *hw = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = m->spi;
	काष्ठा spi_transfer *t;
	पूर्णांक status = 0;

	hw->tlen = 0;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		bool करो_transfer;

		status = sc18is602_check_transfer(spi, t, hw->tlen);
		अगर (status < 0)
			अवरोध;

		status = sc18is602_setup_transfer(hw, t->speed_hz, spi->mode);
		अगर (status < 0)
			अवरोध;

		करो_transfer = t->cs_change || list_is_last(&t->transfer_list,
							   &m->transfers);

		अगर (t->len) अणु
			status = sc18is602_txrx(hw, m, t, करो_transfer);
			अगर (status < 0)
				अवरोध;
			m->actual_length += status;
		पूर्ण
		status = 0;

		spi_transfer_delay_exec(t);
	पूर्ण
	m->status = status;
	spi_finalize_current_message(master);

	वापस status;
पूर्ण

अटल माप_प्रकार sc18is602_max_transfer_size(काष्ठा spi_device *spi)
अणु
	वापस SC18IS602_बफ_मान;
पूर्ण

अटल पूर्णांक sc18is602_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा sc18is602 *hw = spi_master_get_devdata(spi->master);

	/* SC18IS602 करोes not support CS2 */
	अगर (hw->id == sc18is602 && spi->chip_select == 2)
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sc18is602_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sc18is602_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा sc18is602 *hw;
	काष्ठा spi_master *master;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -EINVAL;

	master = devm_spi_alloc_master(dev, माप(काष्ठा sc18is602));
	अगर (!master)
		वापस -ENOMEM;

	hw = spi_master_get_devdata(master);
	i2c_set_clientdata(client, hw);

	/* निश्चित reset and then release */
	hw->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(hw->reset))
		वापस PTR_ERR(hw->reset);
	gpiod_set_value_cansleep(hw->reset, 0);

	hw->master = master;
	hw->client = client;
	hw->dev = dev;
	hw->ctrl = 0xff;

	अगर (client->dev.of_node)
		hw->id = (क्रमागत chips)of_device_get_match_data(&client->dev);
	अन्यथा
		hw->id = id->driver_data;

	चयन (hw->id) अणु
	हाल sc18is602:
	हाल sc18is602b:
		master->num_chipselect = 4;
		hw->freq = SC18IS602_CLOCK;
		अवरोध;
	हाल sc18is603:
		master->num_chipselect = 2;
		अगर (pdata) अणु
			hw->freq = pdata->घड़ी_frequency;
		पूर्ण अन्यथा अणु
			स्थिर __be32 *val;
			पूर्णांक len;

			val = of_get_property(np, "clock-frequency", &len);
			अगर (val && len >= माप(__be32))
				hw->freq = be32_to_cpup(val);
		पूर्ण
		अगर (!hw->freq)
			hw->freq = SC18IS602_CLOCK;
		अवरोध;
	पूर्ण
	master->bus_num = np ? -1 : client->adapter->nr;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_LSB_FIRST;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->setup = sc18is602_setup;
	master->transfer_one_message = sc18is602_transfer_one;
	master->max_transfer_size = sc18is602_max_transfer_size;
	master->max_message_size = sc18is602_max_transfer_size;
	master->dev.of_node = np;
	master->min_speed_hz = hw->freq / 128;
	master->max_speed_hz = hw->freq / 4;

	वापस devm_spi_रेजिस्टर_master(dev, master);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sc18is602_id[] = अणु
	अणु "sc18is602", sc18is602 पूर्ण,
	अणु "sc18is602b", sc18is602b पूर्ण,
	अणु "sc18is603", sc18is603 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sc18is602_id);

अटल स्थिर काष्ठा of_device_id sc18is602_of_match[] = अणु
	अणु
		.compatible = "nxp,sc18is602",
		.data = (व्योम *)sc18is602
	पूर्ण,
	अणु
		.compatible = "nxp,sc18is602b",
		.data = (व्योम *)sc18is602b
	पूर्ण,
	अणु
		.compatible = "nxp,sc18is603",
		.data = (व्योम *)sc18is603
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sc18is602_of_match);

अटल काष्ठा i2c_driver sc18is602_driver = अणु
	.driver = अणु
		.name = "sc18is602",
		.of_match_table = of_match_ptr(sc18is602_of_match),
	पूर्ण,
	.probe = sc18is602_probe,
	.id_table = sc18is602_id,
पूर्ण;

module_i2c_driver(sc18is602_driver);

MODULE_DESCRIPTION("SC18IS602/603 SPI Master Driver");
MODULE_AUTHOR("Guenter Roeck");
MODULE_LICENSE("GPL");
