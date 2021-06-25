<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common library क्रम ADIS16XXX devices
 *
 * Copyright 2012 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/imu/adis.h>

#घोषणा ADIS_MSC_CTRL_DATA_RDY_EN	BIT(2)
#घोषणा ADIS_MSC_CTRL_DATA_RDY_POL_HIGH	BIT(1)
#घोषणा ADIS_MSC_CTRL_DATA_RDY_DIO2	BIT(0)
#घोषणा ADIS_GLOB_CMD_SW_RESET		BIT(7)

/**
 * __adis_ग_लिखो_reg() - ग_लिखो N bytes to रेजिस्टर (unlocked version)
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @value: The value to ग_लिखो to device (up to 4 bytes)
 * @size: The size of the @value (in bytes)
 */
पूर्णांक __adis_ग_लिखो_reg(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक page = reg / ADIS_PAGE_SIZE;
	पूर्णांक ret, i;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = adis->tx,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay.value = adis->data->ग_लिखो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
			.cs_change_delay.value = adis->data->cs_change_delay,
			.cs_change_delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण, अणु
			.tx_buf = adis->tx + 2,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay.value = adis->data->ग_लिखो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
			.cs_change_delay.value = adis->data->cs_change_delay,
			.cs_change_delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण, अणु
			.tx_buf = adis->tx + 4,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay.value = adis->data->ग_लिखो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
			.cs_change_delay.value = adis->data->cs_change_delay,
			.cs_change_delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण, अणु
			.tx_buf = adis->tx + 6,
			.bits_per_word = 8,
			.len = 2,
			.delay.value = adis->data->ग_लिखो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण, अणु
			.tx_buf = adis->tx + 8,
			.bits_per_word = 8,
			.len = 2,
			.delay.value = adis->data->ग_लिखो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण,
	पूर्ण;

	spi_message_init(&msg);

	अगर (adis->current_page != page) अणु
		adis->tx[0] = ADIS_WRITE_REG(ADIS_REG_PAGE_ID);
		adis->tx[1] = page;
		spi_message_add_tail(&xfers[0], &msg);
	पूर्ण

	चयन (size) अणु
	हाल 4:
		adis->tx[8] = ADIS_WRITE_REG(reg + 3);
		adis->tx[9] = (value >> 24) & 0xff;
		adis->tx[6] = ADIS_WRITE_REG(reg + 2);
		adis->tx[7] = (value >> 16) & 0xff;
		fallthrough;
	हाल 2:
		adis->tx[4] = ADIS_WRITE_REG(reg + 1);
		adis->tx[5] = (value >> 8) & 0xff;
		fallthrough;
	हाल 1:
		adis->tx[2] = ADIS_WRITE_REG(reg);
		adis->tx[3] = value & 0xff;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	xfers[size].cs_change = 0;

	क्रम (i = 1; i <= size; i++)
		spi_message_add_tail(&xfers[i], &msg);

	ret = spi_sync(adis->spi, &msg);
	अगर (ret) अणु
		dev_err(&adis->spi->dev, "Failed to write register 0x%02X: %d\n",
				reg, ret);
	पूर्ण अन्यथा अणु
		adis->current_page = page;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__adis_ग_लिखो_reg);

/**
 * __adis_पढ़ो_reg() - पढ़ो N bytes from रेजिस्टर (unlocked version)
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @val: The value पढ़ो back from the device
 * @size: The size of the @val buffer
 */
पूर्णांक __adis_पढ़ो_reg(काष्ठा adis *adis, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक *val, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक page = reg / ADIS_PAGE_SIZE;
	काष्ठा spi_message msg;
	पूर्णांक ret;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = adis->tx,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay.value = adis->data->ग_लिखो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
			.cs_change_delay.value = adis->data->cs_change_delay,
			.cs_change_delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण, अणु
			.tx_buf = adis->tx + 2,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay.value = adis->data->पढ़ो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
			.cs_change_delay.value = adis->data->cs_change_delay,
			.cs_change_delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण, अणु
			.tx_buf = adis->tx + 4,
			.rx_buf = adis->rx,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay.value = adis->data->पढ़ो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
			.cs_change_delay.value = adis->data->cs_change_delay,
			.cs_change_delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण, अणु
			.rx_buf = adis->rx + 2,
			.bits_per_word = 8,
			.len = 2,
			.delay.value = adis->data->पढ़ो_delay,
			.delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण,
	पूर्ण;

	spi_message_init(&msg);

	अगर (adis->current_page != page) अणु
		adis->tx[0] = ADIS_WRITE_REG(ADIS_REG_PAGE_ID);
		adis->tx[1] = page;
		spi_message_add_tail(&xfers[0], &msg);
	पूर्ण

	चयन (size) अणु
	हाल 4:
		adis->tx[2] = ADIS_READ_REG(reg + 2);
		adis->tx[3] = 0;
		spi_message_add_tail(&xfers[1], &msg);
		fallthrough;
	हाल 2:
		adis->tx[4] = ADIS_READ_REG(reg);
		adis->tx[5] = 0;
		spi_message_add_tail(&xfers[2], &msg);
		spi_message_add_tail(&xfers[3], &msg);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = spi_sync(adis->spi, &msg);
	अगर (ret) अणु
		dev_err(&adis->spi->dev, "Failed to read register 0x%02X: %d\n",
				reg, ret);
		वापस ret;
	पूर्ण अन्यथा अणु
		adis->current_page = page;
	पूर्ण

	चयन (size) अणु
	हाल 4:
		*val = get_unaligned_be32(adis->rx);
		अवरोध;
	हाल 2:
		*val = get_unaligned_be16(adis->rx + 2);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__adis_पढ़ो_reg);
/**
 * __adis_update_bits_base() - ADIS Update bits function - Unlocked version
 * @adis: The adis device
 * @reg: The address of the lower of the two रेजिस्टरs
 * @mask: Biपंचांगask to change
 * @val: Value to be written
 * @size: Size of the रेजिस्टर to update
 *
 * Updates the desired bits of @reg in accordance with @mask and @val.
 */
पूर्णांक __adis_update_bits_base(काष्ठा adis *adis, अचिन्हित पूर्णांक reg, स्थिर u32 mask,
			    स्थिर u32 val, u8 size)
अणु
	पूर्णांक ret;
	u32 __val;

	ret = __adis_पढ़ो_reg(adis, reg, &__val, size);
	अगर (ret)
		वापस ret;

	__val = (__val & ~mask) | (val & mask);

	वापस __adis_ग_लिखो_reg(adis, reg, __val, size);
पूर्ण
EXPORT_SYMBOL_GPL(__adis_update_bits_base);

#अगर_घोषित CONFIG_DEBUG_FS

पूर्णांक adis_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा adis *adis = iio_device_get_drvdata(indio_dev);

	अगर (पढ़ोval) अणु
		uपूर्णांक16_t val16;
		पूर्णांक ret;

		ret = adis_पढ़ो_reg_16(adis, reg, &val16);
		अगर (ret == 0)
			*पढ़ोval = val16;

		वापस ret;
	पूर्ण अन्यथा अणु
		वापस adis_ग_लिखो_reg_16(adis, reg, ग_लिखोval);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(adis_debugfs_reg_access);

#पूर्ण_अगर

/**
 * adis_enable_irq() - Enable or disable data पढ़ोy IRQ
 * @adis: The adis device
 * @enable: Whether to enable the IRQ
 *
 * Returns 0 on success, negative error code otherwise
 */
पूर्णांक adis_enable_irq(काष्ठा adis *adis, bool enable)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक16_t msc;

	mutex_lock(&adis->state_lock);

	अगर (adis->data->enable_irq) अणु
		ret = adis->data->enable_irq(adis, enable);
		जाओ out_unlock;
	पूर्ण

	ret = __adis_पढ़ो_reg_16(adis, adis->data->msc_ctrl_reg, &msc);
	अगर (ret)
		जाओ out_unlock;

	msc |= ADIS_MSC_CTRL_DATA_RDY_POL_HIGH;
	msc &= ~ADIS_MSC_CTRL_DATA_RDY_DIO2;
	अगर (enable)
		msc |= ADIS_MSC_CTRL_DATA_RDY_EN;
	अन्यथा
		msc &= ~ADIS_MSC_CTRL_DATA_RDY_EN;

	ret = __adis_ग_लिखो_reg_16(adis, adis->data->msc_ctrl_reg, msc);

out_unlock:
	mutex_unlock(&adis->state_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(adis_enable_irq);

/**
 * __adis_check_status() - Check the device क्रम error conditions (unlocked)
 * @adis: The adis device
 *
 * Returns 0 on success, a negative error code otherwise
 */
पूर्णांक __adis_check_status(काष्ठा adis *adis)
अणु
	uपूर्णांक16_t status;
	पूर्णांक ret;
	पूर्णांक i;

	ret = __adis_पढ़ो_reg_16(adis, adis->data->diag_stat_reg, &status);
	अगर (ret)
		वापस ret;

	status &= adis->data->status_error_mask;

	अगर (status == 0)
		वापस 0;

	क्रम (i = 0; i < 16; ++i) अणु
		अगर (status & BIT(i)) अणु
			dev_err(&adis->spi->dev, "%s.\n",
				adis->data->status_error_msgs[i]);
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(__adis_check_status);

/**
 * __adis_reset() - Reset the device (unlocked version)
 * @adis: The adis device
 *
 * Returns 0 on success, a negative error code otherwise
 */
पूर्णांक __adis_reset(काष्ठा adis *adis)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा adis_समयout *समयouts = adis->data->समयouts;

	ret = __adis_ग_लिखो_reg_8(adis, adis->data->glob_cmd_reg,
			ADIS_GLOB_CMD_SW_RESET);
	अगर (ret) अणु
		dev_err(&adis->spi->dev, "Failed to reset device: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(समयouts->sw_reset_ms);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__adis_reset);

अटल पूर्णांक adis_self_test(काष्ठा adis *adis)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा adis_समयout *समयouts = adis->data->समयouts;

	ret = __adis_ग_लिखो_reg_16(adis, adis->data->self_test_reg,
				  adis->data->self_test_mask);
	अगर (ret) अणु
		dev_err(&adis->spi->dev, "Failed to initiate self test: %d\n",
			ret);
		वापस ret;
	पूर्ण

	msleep(समयouts->self_test_ms);

	ret = __adis_check_status(adis);

	अगर (adis->data->self_test_no_स्वतःclear)
		__adis_ग_लिखो_reg_16(adis, adis->data->self_test_reg, 0x00);

	वापस ret;
पूर्ण

/**
 * __adis_initial_startup() - Device initial setup
 * @adis: The adis device
 *
 * The function perक्रमms a HW reset via a reset pin that should be specअगरied
 * via GPIOLIB. If no pin is configured a SW reset will be perक्रमmed.
 * The RST pin क्रम the ADIS devices should be configured as ACTIVE_LOW.
 *
 * After the self-test operation is perक्रमmed, the function will also check
 * that the product ID is as expected. This assumes that drivers providing
 * 'prod_id_reg' will also provide the 'prod_id'.
 *
 * Returns 0 अगर the device is operational, a negative error code otherwise.
 *
 * This function should be called early on in the device initialization sequence
 * to ensure that the device is in a sane and known state and that it is usable.
 */
पूर्णांक __adis_initial_startup(काष्ठा adis *adis)
अणु
	स्थिर काष्ठा adis_समयout *समयouts = adis->data->समयouts;
	काष्ठा gpio_desc *gpio;
	uपूर्णांक16_t prod_id;
	पूर्णांक ret;

	/* check अगर the device has rst pin low */
	gpio = devm_gpiod_get_optional(&adis->spi->dev, "reset", GPIOD_ASIS);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	अगर (gpio) अणु
		gpiod_set_value_cansleep(gpio, 1);
		msleep(10);
		/* bring device out of reset */
		gpiod_set_value_cansleep(gpio, 0);
		msleep(समयouts->reset_ms);
	पूर्ण अन्यथा अणु
		ret = __adis_reset(adis);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = adis_self_test(adis);
	अगर (ret)
		वापस ret;

	अगर (!adis->data->prod_id_reg)
		वापस 0;

	ret = adis_पढ़ो_reg_16(adis, adis->data->prod_id_reg, &prod_id);
	अगर (ret)
		वापस ret;

	अगर (prod_id != adis->data->prod_id)
		dev_warn(&adis->spi->dev,
			 "Device ID(%u) and product ID(%u) do not match.\n",
			 adis->data->prod_id, prod_id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__adis_initial_startup);

/**
 * adis_single_conversion() - Perक्रमms a single sample conversion
 * @indio_dev: The IIO device
 * @chan: The IIO channel
 * @error_mask: Mask क्रम the error bit
 * @val: Result of the conversion
 *
 * Returns IIO_VAL_INT on success, a negative error code otherwise.
 *
 * The function perक्रमms a single conversion on a given channel and post
 * processes the value accordingly to the channel spec. If a error_mask is given
 * the function will check अगर the mask is set in the वापसed raw value. If it
 * is set the function will perक्रमm a self-check. If the device करोes not report
 * a error bit in the channels raw value set error_mask to 0.
 */
पूर्णांक adis_single_conversion(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक error_mask, पूर्णांक *val)
अणु
	काष्ठा adis *adis = iio_device_get_drvdata(indio_dev);
	अचिन्हित पूर्णांक uval;
	पूर्णांक ret;

	mutex_lock(&adis->state_lock);

	ret = __adis_पढ़ो_reg(adis, chan->address, &uval,
			chan->scan_type.storagebits / 8);
	अगर (ret)
		जाओ err_unlock;

	अगर (uval & error_mask) अणु
		ret = __adis_check_status(adis);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण

	अगर (chan->scan_type.sign == 's')
		*val = sign_extend32(uval, chan->scan_type.realbits - 1);
	अन्यथा
		*val = uval & ((1 << chan->scan_type.realbits) - 1);

	ret = IIO_VAL_INT;
err_unlock:
	mutex_unlock(&adis->state_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adis_single_conversion);

/**
 * adis_init() - Initialize adis device काष्ठाure
 * @adis:	The adis device
 * @indio_dev:	The iio device
 * @spi:	The spi device
 * @data:	Chip specअगरic data
 *
 * Returns 0 on success, a negative error code otherwise.
 *
 * This function must be called, beक्रमe any other adis helper function may be
 * called.
 */
पूर्णांक adis_init(काष्ठा adis *adis, काष्ठा iio_dev *indio_dev,
	काष्ठा spi_device *spi, स्थिर काष्ठा adis_data *data)
अणु
	अगर (!data || !data->समयouts) अणु
		dev_err(&spi->dev, "No config data or timeouts not defined!\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&adis->state_lock);
	adis->spi = spi;
	adis->data = data;
	iio_device_set_drvdata(indio_dev, adis);

	अगर (data->has_paging) अणु
		/* Need to set the page beक्रमe first पढ़ो/ग_लिखो */
		adis->current_page = -1;
	पूर्ण अन्यथा अणु
		/* Page will always be 0 */
		adis->current_page = 0;
	पूर्ण

	वापस adis_enable_irq(adis, false);
पूर्ण
EXPORT_SYMBOL_GPL(adis_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Common library code for ADIS16XXX devices");
