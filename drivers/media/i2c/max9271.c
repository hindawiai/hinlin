<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017-2020 Jacopo Mondi
 * Copyright (C) 2017-2020 Kieran Bingham
 * Copyright (C) 2017-2020 Laurent Pinअक्षरt
 * Copyright (C) 2017-2020 Niklas Sथघderlund
 * Copyright (C) 2016 Renesas Electronics Corporation
 * Copyright (C) 2015 Cogent Embedded, Inc.
 *
 * This file exports functions to control the Maxim MAX9271 GMSL serializer
 * chip. This is not a self-contained driver, as MAX9271 is usually embedded in
 * camera modules with at least one image sensor and optional additional
 * components, such as uController units or ISPs/DSPs.
 *
 * Drivers क्रम the camera modules (i.e. rdacm20/21) are expected to use
 * functions exported from this library driver to maximize code re-use.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>

#समावेश "max9271.h"

अटल पूर्णांक max9271_पढ़ो(काष्ठा max9271_device *dev, u8 reg)
अणु
	पूर्णांक ret;

	dev_dbg(&dev->client->dev, "%s(0x%02x)\n", __func__, reg);

	ret = i2c_smbus_पढ़ो_byte_data(dev->client, reg);
	अगर (ret < 0)
		dev_dbg(&dev->client->dev,
			"%s: register 0x%02x read failed (%d)\n",
			__func__, reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max9271_ग_लिखो(काष्ठा max9271_device *dev, u8 reg, u8 val)
अणु
	पूर्णांक ret;

	dev_dbg(&dev->client->dev, "%s(0x%02x, 0x%02x)\n", __func__, reg, val);

	ret = i2c_smbus_ग_लिखो_byte_data(dev->client, reg, val);
	अगर (ret < 0)
		dev_err(&dev->client->dev,
			"%s: register 0x%02x write failed (%d)\n",
			__func__, reg, ret);

	वापस ret;
पूर्ण

/*
 * max9271_pclk_detect() - Detect valid pixel घड़ी from image sensor
 *
 * Wait up to 10ms क्रम a valid pixel घड़ी.
 *
 * Returns 0 क्रम success, < 0 क्रम pixel घड़ी not properly detected
 */
अटल पूर्णांक max9271_pclk_detect(काष्ठा max9271_device *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < 100; i++) अणु
		ret = max9271_पढ़ो(dev, 0x15);
		अगर (ret < 0)
			वापस ret;

		अगर (ret & MAX9271_PCLKDET)
			वापस 0;

		usleep_range(50, 100);
	पूर्ण

	dev_err(&dev->client->dev, "Unable to detect valid pixel clock\n");

	वापस -EIO;
पूर्ण

पूर्णांक max9271_set_serial_link(काष्ठा max9271_device *dev, bool enable)
अणु
	पूर्णांक ret;
	u8 val = MAX9271_REVCCEN | MAX9271_FWDCCEN;

	अगर (enable) अणु
		ret = max9271_pclk_detect(dev);
		अगर (ret)
			वापस ret;

		val |= MAX9271_SEREN;
	पूर्ण अन्यथा अणु
		val |= MAX9271_CLINKEN;
	पूर्ण

	/*
	 * The serializer temporarily disables the reverse control channel क्रम
	 * 350तगs after starting/stopping the क्रमward serial link, but the
	 * deserializer synchronization समय isn't clearly करोcumented.
	 *
	 * According to the serializer datasheet we should रुको 3ms, जबतक
	 * according to the deserializer datasheet we should रुको 5ms.
	 *
	 * Short delays here appear to show bit-errors in the ग_लिखोs following.
	 * Thereक्रमe a conservative delay seems best here.
	 */
	max9271_ग_लिखो(dev, 0x04, val);
	usleep_range(5000, 8000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_set_serial_link);

पूर्णांक max9271_configure_i2c(काष्ठा max9271_device *dev, u8 i2c_config)
अणु
	पूर्णांक ret;

	ret = max9271_ग_लिखो(dev, 0x0d, i2c_config);
	अगर (ret)
		वापस ret;

	/* The delay required after an I2C bus configuration change is not
	 * अक्षरacterized in the serializer manual. Sleep up to 5msec to
	 * stay safe.
	 */
	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_configure_i2c);

पूर्णांक max9271_set_high_threshold(काष्ठा max9271_device *dev, bool enable)
अणु
	पूर्णांक ret;

	ret = max9271_पढ़ो(dev, 0x08);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Enable or disable reverse channel high threshold to increase
	 * immunity to घातer supply noise.
	 */
	max9271_ग_लिखो(dev, 0x08, enable ? ret | BIT(0) : ret & ~BIT(0));
	usleep_range(2000, 2500);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_set_high_threshold);

पूर्णांक max9271_configure_gmsl_link(काष्ठा max9271_device *dev)
अणु
	/*
	 * Configure the GMSL link:
	 *
	 * - Double input mode, high data rate, 24-bit mode
	 * - Latch input data on PCLKIN rising edge
	 * - Enable HS/VS encoding
	 * - 1-bit parity error detection
	 *
	 * TODO: Make the GMSL link configuration parametric.
	 */
	max9271_ग_लिखो(dev, 0x07, MAX9271_DBL | MAX9271_HVEN |
		      MAX9271_EDC_1BIT_PARITY);
	usleep_range(5000, 8000);

	/*
	 * Adjust spपढ़ो spectrum to +4% and स्वतः-detect pixel घड़ी
	 * and serial link rate.
	 */
	max9271_ग_लिखो(dev, 0x02, MAX9271_SPREAD_SPECT_4 | MAX9271_R02_RES |
		      MAX9271_PCLK_AUTODETECT | MAX9271_SERIAL_AUTODETECT);
	usleep_range(5000, 8000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_configure_gmsl_link);

पूर्णांक max9271_set_gpios(काष्ठा max9271_device *dev, u8 gpio_mask)
अणु
	पूर्णांक ret;

	ret = max9271_पढ़ो(dev, 0x0f);
	अगर (ret < 0)
		वापस 0;

	ret |= gpio_mask;
	ret = max9271_ग_लिखो(dev, 0x0f, ret);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev, "Failed to set gpio (%d)\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_set_gpios);

पूर्णांक max9271_clear_gpios(काष्ठा max9271_device *dev, u8 gpio_mask)
अणु
	पूर्णांक ret;

	ret = max9271_पढ़ो(dev, 0x0f);
	अगर (ret < 0)
		वापस 0;

	ret &= ~gpio_mask;
	ret = max9271_ग_लिखो(dev, 0x0f, ret);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev, "Failed to clear gpio (%d)\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_clear_gpios);

पूर्णांक max9271_enable_gpios(काष्ठा max9271_device *dev, u8 gpio_mask)
अणु
	पूर्णांक ret;

	ret = max9271_पढ़ो(dev, 0x0e);
	अगर (ret < 0)
		वापस 0;

	/* BIT(0) reserved: GPO is always enabled. */
	ret |= (gpio_mask & ~BIT(0));
	ret = max9271_ग_लिखो(dev, 0x0e, ret);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev, "Failed to enable gpio (%d)\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_enable_gpios);

पूर्णांक max9271_disable_gpios(काष्ठा max9271_device *dev, u8 gpio_mask)
अणु
	पूर्णांक ret;

	ret = max9271_पढ़ो(dev, 0x0e);
	अगर (ret < 0)
		वापस 0;

	/* BIT(0) reserved: GPO cannot be disabled */
	ret &= ~(gpio_mask | BIT(0));
	ret = max9271_ग_लिखो(dev, 0x0e, ret);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev, "Failed to disable gpio (%d)\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_disable_gpios);

पूर्णांक max9271_verअगरy_id(काष्ठा max9271_device *dev)
अणु
	पूर्णांक ret;

	ret = max9271_पढ़ो(dev, 0x1e);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev, "MAX9271 ID read failed (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (ret != MAX9271_ID) अणु
		dev_err(&dev->client->dev, "MAX9271 ID mismatch (0x%02x)\n",
			ret);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_verअगरy_id);

पूर्णांक max9271_set_address(काष्ठा max9271_device *dev, u8 addr)
अणु
	पूर्णांक ret;

	ret = max9271_ग_लिखो(dev, 0x00, addr << 1);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev,
			"MAX9271 I2C address change failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_set_address);

पूर्णांक max9271_set_deserializer_address(काष्ठा max9271_device *dev, u8 addr)
अणु
	पूर्णांक ret;

	ret = max9271_ग_लिखो(dev, 0x01, addr << 1);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev,
			"MAX9271 deserializer address set failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_set_deserializer_address);

पूर्णांक max9271_set_translation(काष्ठा max9271_device *dev, u8 source, u8 dest)
अणु
	पूर्णांक ret;

	ret = max9271_ग_लिखो(dev, 0x09, source << 1);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev,
			"MAX9271 I2C translation setup failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	usleep_range(3500, 5000);

	ret = max9271_ग_लिखो(dev, 0x0a, dest << 1);
	अगर (ret < 0) अणु
		dev_err(&dev->client->dev,
			"MAX9271 I2C translation setup failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	usleep_range(3500, 5000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max9271_set_translation);

MODULE_DESCRIPTION("Maxim MAX9271 GMSL Serializer");
MODULE_AUTHOR("Jacopo Mondi");
MODULE_LICENSE("GPL v2");
