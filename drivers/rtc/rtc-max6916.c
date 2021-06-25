<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* rtc-max6916.c
 *
 * Driver क्रम MAXIM  max6916 Low Current, SPI Compatible
 * Real Time Clock
 *
 * Author : Venkat Prashanth B U <venkat.prashanth2498@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>

/* Registers in max6916 rtc */

#घोषणा MAX6916_SECONDS_REG	0x01
#घोषणा MAX6916_MINUTES_REG	0x02
#घोषणा MAX6916_HOURS_REG	0x03
#घोषणा MAX6916_DATE_REG	0x04
#घोषणा MAX6916_MONTH_REG	0x05
#घोषणा MAX6916_DAY_REG	0x06
#घोषणा MAX6916_YEAR_REG	0x07
#घोषणा MAX6916_CONTROL_REG	0x08
#घोषणा MAX6916_STATUS_REG	0x0C
#घोषणा MAX6916_CLOCK_BURST	0x3F

अटल पूर्णांक max6916_पढ़ो_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
			    अचिन्हित अक्षर *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	*data = address | 0x80;

	वापस spi_ग_लिखो_then_पढ़ो(spi, data, 1, data, 1);
पूर्ण

अटल पूर्णांक max6916_ग_लिखो_reg(काष्ठा device *dev, अचिन्हित अक्षर address,
			     अचिन्हित अक्षर data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[2];

	buf[0] = address & 0x7F;
	buf[1] = data;

	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, 2, शून्य, 0);
पूर्ण

अटल पूर्णांक max6916_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक err;
	अचिन्हित अक्षर buf[8];

	buf[0] = MAX6916_CLOCK_BURST | 0x80;

	err = spi_ग_लिखो_then_पढ़ो(spi, buf, 1, buf, 8);

	अगर (err)
		वापस err;

	dt->पंचांग_sec = bcd2bin(buf[0]);
	dt->पंचांग_min = bcd2bin(buf[1]);
	dt->पंचांग_hour = bcd2bin(buf[2] & 0x3F);
	dt->पंचांग_mday = bcd2bin(buf[3]);
	dt->पंचांग_mon = bcd2bin(buf[4]) - 1;
	dt->पंचांग_wday = bcd2bin(buf[5]) - 1;
	dt->पंचांग_year = bcd2bin(buf[6]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक max6916_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[9];

	अगर (dt->पंचांग_year < 100 || dt->पंचांग_year > 199) अणु
		dev_err(&spi->dev, "Year must be between 2000 and 2099. It's %d.\n",
			dt->पंचांग_year + 1900);
		वापस -EINVAL;
	पूर्ण

	buf[0] = MAX6916_CLOCK_BURST & 0x7F;
	buf[1] = bin2bcd(dt->पंचांग_sec);
	buf[2] = bin2bcd(dt->पंचांग_min);
	buf[3] = (bin2bcd(dt->पंचांग_hour) & 0X3F);
	buf[4] = bin2bcd(dt->पंचांग_mday);
	buf[5] = bin2bcd(dt->पंचांग_mon + 1);
	buf[6] = bin2bcd(dt->पंचांग_wday + 1);
	buf[7] = bin2bcd(dt->पंचांग_year % 100);
	buf[8] = bin2bcd(0x00);

	/* ग_लिखो the rtc settings */
	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, 9, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max6916_rtc_ops = अणु
	.पढ़ो_समय = max6916_पढ़ो_समय,
	.set_समय = max6916_set_समय,
पूर्ण;

अटल पूर्णांक max6916_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	अचिन्हित अक्षर data;
	पूर्णांक res;

	/* spi setup with max6916 in mode 3 and bits per word as 8 */
	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	/* RTC Settings */
	res = max6916_पढ़ो_reg(&spi->dev, MAX6916_SECONDS_REG, &data);
	अगर (res)
		वापस res;

	/* Disable the ग_लिखो protect of rtc */
	max6916_पढ़ो_reg(&spi->dev, MAX6916_CONTROL_REG, &data);
	data = data & ~(1 << 7);
	max6916_ग_लिखो_reg(&spi->dev, MAX6916_CONTROL_REG, data);

	/*Enable oscillator,disable oscillator stop flag, glitch filter*/
	max6916_पढ़ो_reg(&spi->dev, MAX6916_STATUS_REG, &data);
	data = data & 0x1B;
	max6916_ग_लिखो_reg(&spi->dev, MAX6916_STATUS_REG, data);

	/* display the settings */
	max6916_पढ़ो_reg(&spi->dev, MAX6916_CONTROL_REG, &data);
	dev_info(&spi->dev, "MAX6916 RTC CTRL Reg = 0x%02x\n", data);

	max6916_पढ़ो_reg(&spi->dev, MAX6916_STATUS_REG, &data);
	dev_info(&spi->dev, "MAX6916 RTC Status Reg = 0x%02x\n", data);

	rtc = devm_rtc_device_रेजिस्टर(&spi->dev, "max6916",
				       &max6916_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver max6916_driver = अणु
	.driver = अणु
		.name = "max6916",
	पूर्ण,
	.probe = max6916_probe,
पूर्ण;
module_spi_driver(max6916_driver);

MODULE_DESCRIPTION("MAX6916 SPI RTC DRIVER");
MODULE_AUTHOR("Venkat Prashanth B U <venkat.prashanth2498@gmail.com>");
MODULE_LICENSE("GPL v2");
