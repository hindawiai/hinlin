<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2017-2020 Jacopo Mondi
 * Copyright (C) 2017-2020 Kieran Bingham
 * Copyright (C) 2017-2020 Laurent Pinअक्षरt
 * Copyright (C) 2017-2020 Niklas Sथघderlund
 * Copyright (C) 2016 Renesas Electronics Corporation
 * Copyright (C) 2015 Cogent Embedded, Inc.
 */

#समावेश <linux/i2c.h>

#घोषणा MAX9271_DEFAULT_ADDR	0x40

/* Register 0x02 */
#घोषणा MAX9271_SPREAD_SPECT_0		(0 << 5)
#घोषणा MAX9271_SPREAD_SPECT_05		(1 << 5)
#घोषणा MAX9271_SPREAD_SPECT_15		(2 << 5)
#घोषणा MAX9271_SPREAD_SPECT_1		(5 << 5)
#घोषणा MAX9271_SPREAD_SPECT_2		(3 << 5)
#घोषणा MAX9271_SPREAD_SPECT_3		(6 << 5)
#घोषणा MAX9271_SPREAD_SPECT_4		(7 << 5)
#घोषणा MAX9271_R02_RES			BIT(4)
#घोषणा MAX9271_PCLK_AUTODETECT		(3 << 2)
#घोषणा MAX9271_SERIAL_AUTODETECT	(0x03)
/* Register 0x04 */
#घोषणा MAX9271_SEREN			BIT(7)
#घोषणा MAX9271_CLINKEN			BIT(6)
#घोषणा MAX9271_PRBSEN			BIT(5)
#घोषणा MAX9271_SLEEP			BIT(4)
#घोषणा MAX9271_INTTYPE_I2C		(0 << 2)
#घोषणा MAX9271_INTTYPE_UART		(1 << 2)
#घोषणा MAX9271_INTTYPE_NONE		(2 << 2)
#घोषणा MAX9271_REVCCEN			BIT(1)
#घोषणा MAX9271_FWDCCEN			BIT(0)
/* Register 0x07 */
#घोषणा MAX9271_DBL			BIT(7)
#घोषणा MAX9271_DRS			BIT(6)
#घोषणा MAX9271_BWS			BIT(5)
#घोषणा MAX9271_ES			BIT(4)
#घोषणा MAX9271_HVEN			BIT(2)
#घोषणा MAX9271_EDC_1BIT_PARITY		(0 << 0)
#घोषणा MAX9271_EDC_6BIT_CRC		(1 << 0)
#घोषणा MAX9271_EDC_6BIT_HAMMING	(2 << 0)
/* Register 0x08 */
#घोषणा MAX9271_INVVS			BIT(7)
#घोषणा MAX9271_INVHS			BIT(6)
#घोषणा MAX9271_REV_LOGAIN		BIT(3)
#घोषणा MAX9271_REV_HIVTH		BIT(0)
/* Register 0x09 */
#घोषणा MAX9271_ID			0x09
/* Register 0x0d */
#घोषणा MAX9271_I2CLOCACK		BIT(7)
#घोषणा MAX9271_I2CSLVSH_1046NS_469NS	(3 << 5)
#घोषणा MAX9271_I2CSLVSH_938NS_352NS	(2 << 5)
#घोषणा MAX9271_I2CSLVSH_469NS_234NS	(1 << 5)
#घोषणा MAX9271_I2CSLVSH_352NS_117NS	(0 << 5)
#घोषणा MAX9271_I2CMSTBT_837KBPS	(7 << 2)
#घोषणा MAX9271_I2CMSTBT_533KBPS	(6 << 2)
#घोषणा MAX9271_I2CMSTBT_339KBPS	(5 << 2)
#घोषणा MAX9271_I2CMSTBT_173KBPS	(4 << 2)
#घोषणा MAX9271_I2CMSTBT_105KBPS	(3 << 2)
#घोषणा MAX9271_I2CMSTBT_84KBPS		(2 << 2)
#घोषणा MAX9271_I2CMSTBT_28KBPS		(1 << 2)
#घोषणा MAX9271_I2CMSTBT_8KBPS		(0 << 2)
#घोषणा MAX9271_I2CSLVTO_NONE		(3 << 0)
#घोषणा MAX9271_I2CSLVTO_1024US		(2 << 0)
#घोषणा MAX9271_I2CSLVTO_256US		(1 << 0)
#घोषणा MAX9271_I2CSLVTO_64US		(0 << 0)
/* Register 0x0f */
#घोषणा MAX9271_GPIO5OUT		BIT(5)
#घोषणा MAX9271_GPIO4OUT		BIT(4)
#घोषणा MAX9271_GPIO3OUT		BIT(3)
#घोषणा MAX9271_GPIO2OUT		BIT(2)
#घोषणा MAX9271_GPIO1OUT		BIT(1)
#घोषणा MAX9271_GPO			BIT(0)
/* Register 0x15 */
#घोषणा MAX9271_PCLKDET			BIT(0)

/**
 * काष्ठा max9271_device - max9271 device
 * @client: The i2c client क्रम the max9271 instance
 */
काष्ठा max9271_device अणु
	काष्ठा i2c_client *client;
पूर्ण;

/**
 * max9271_set_serial_link() - Enable/disable serial link
 * @dev: The max9271 device
 * @enable: Serial link enable/disable flag
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_set_serial_link(काष्ठा max9271_device *dev, bool enable);

/**
 * max9271_configure_i2c() - Configure I2C bus parameters
 * @dev: The max9271 device
 * @i2c_config: The I2C bus configuration bit mask
 *
 * Configure MAX9271 I2C पूर्णांकerface. The bus configuration provided in the
 * @i2c_config parameter shall be assembled using bit values defined by the
 * MAX9271_I2C* macros.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_configure_i2c(काष्ठा max9271_device *dev, u8 i2c_config);

/**
 * max9271_set_high_threshold() - Enable or disable reverse channel high
 *				  threshold
 * @dev: The max9271 device
 * @enable: High threshold enable/disable flag
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_set_high_threshold(काष्ठा max9271_device *dev, bool enable);

/**
 * max9271_configure_gmsl_link() - Configure the GMSL link
 * @dev: The max9271 device
 *
 * FIXME: the GMSL link configuration is currently hardcoded and perक्रमmed
 * by programming रेजिस्टरs 0x04, 0x07 and 0x02.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_configure_gmsl_link(काष्ठा max9271_device *dev);

/**
 * max9271_set_gpios() - Set gpio lines to physical high value
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio lines to set to high value
 *
 * The @gpio_mask parameter shall be assembled using the MAX9271_GP[IO|O]*
 * bit values.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_set_gpios(काष्ठा max9271_device *dev, u8 gpio_mask);

/**
 * max9271_clear_gpios() - Set gpio lines to physical low value
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio lines to set to low value
 *
 * The @gpio_mask parameter shall be assembled using the MAX9271_GP[IO|O]*
 * bit values.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_clear_gpios(काष्ठा max9271_device *dev, u8 gpio_mask);

/**
 * max9271_enable_gpios() - Enable gpio lines
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio lines to enable
 *
 * The @gpio_mask parameter shall be assembled using the MAX9271_GPIO*
 * bit values. GPO line is always enabled by शेष.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_enable_gpios(काष्ठा max9271_device *dev, u8 gpio_mask);

/**
 * max9271_disable_gpios() - Disable gpio lines
 * @dev: The max9271 device
 * @gpio_mask: The mask of gpio lines to disable
 *
 * The @gpio_mask parameter shall be assembled using the MAX9271_GPIO*
 * bit values. GPO line is always enabled by शेष and cannot be disabled.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_disable_gpios(काष्ठा max9271_device *dev, u8 gpio_mask);

/**
 * max9271_verअगरy_id() - Read and verअगरy MAX9271 id
 * @dev: The max9271 device
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_verअगरy_id(काष्ठा max9271_device *dev);

/**
 * max9271_set_address() - Program a new I2C address
 * @dev: The max9271 device
 * @addr: The new I2C address in 7-bit क्रमmat
 *
 * This function only takes care of programming the new I2C address @addr to
 * in the MAX9271 chip रेजिस्टरs, it is responsiblity of the caller to set
 * the i2c address client to the @addr value to be able to communicate with
 * the MAX9271 chip using the I2C framework APIs after this function वापसs.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_set_address(काष्ठा max9271_device *dev, u8 addr);

/**
 * max9271_set_deserializer_address() - Program the remote deserializer address
 * @dev: The max9271 device
 * @addr: The deserializer I2C address in 7-bit क्रमmat
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_set_deserializer_address(काष्ठा max9271_device *dev, u8 addr);

/**
 * max9271_set_translation() - Program I2C address translation
 * @dev: The max9271 device
 * @source: The I2C source address
 * @dest: The I2C destination address
 *
 * Program address translation from @source to @dest. This is required to
 * communicate with local devices that करो not support address reprogramming.
 *
 * TODO: The device supports translation of two address, this function currently
 * supports a single one.
 *
 * Return 0 on success or a negative error code on failure
 */
पूर्णांक max9271_set_translation(काष्ठा max9271_device *dev, u8 source, u8 dest);
