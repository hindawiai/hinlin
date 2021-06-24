<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI Driver क्रम Microchip MCP795 RTC
 *
 * Copyright (C) Josef Gajdusek <atx@atx.name>
 *
 * based on other Linux RTC drivers
 *
 * Device datasheet:
 * https://ww1.microchip.com/करोwnloads/en/DeviceDoc/22280A.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/rtc.h>
#समावेश <linux/of.h>
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>

/* MCP795 Inकाष्ठाions, see datasheet table 3-1 */
#घोषणा MCP795_EEREAD	0x03
#घोषणा MCP795_EEWRITE	0x02
#घोषणा MCP795_EEWRDI	0x04
#घोषणा MCP795_EEWREN	0x06
#घोषणा MCP795_SRREAD	0x05
#घोषणा MCP795_SRWRITE	0x01
#घोषणा MCP795_READ	0x13
#घोषणा MCP795_WRITE	0x12
#घोषणा MCP795_UNLOCK	0x14
#घोषणा MCP795_IDWRITE	0x32
#घोषणा MCP795_IDREAD	0x33
#घोषणा MCP795_CLRWDT	0x44
#घोषणा MCP795_CLRRAM	0x54

/* MCP795 RTCC रेजिस्टरs, see datasheet table 4-1 */
#घोषणा MCP795_REG_SECONDS	0x01
#घोषणा MCP795_REG_DAY		0x04
#घोषणा MCP795_REG_MONTH	0x06
#घोषणा MCP795_REG_CONTROL	0x08
#घोषणा MCP795_REG_ALM0_SECONDS	0x0C
#घोषणा MCP795_REG_ALM0_DAY	0x0F

#घोषणा MCP795_ST_BIT		BIT(7)
#घोषणा MCP795_24_BIT		BIT(6)
#घोषणा MCP795_LP_BIT		BIT(5)
#घोषणा MCP795_EXTOSC_BIT	BIT(3)
#घोषणा MCP795_OSCON_BIT	BIT(5)
#घोषणा MCP795_ALM0_BIT		BIT(4)
#घोषणा MCP795_ALM1_BIT		BIT(5)
#घोषणा MCP795_ALM0IF_BIT	BIT(3)
#घोषणा MCP795_ALM0C0_BIT	BIT(4)
#घोषणा MCP795_ALM0C1_BIT	BIT(5)
#घोषणा MCP795_ALM0C2_BIT	BIT(6)

#घोषणा SEC_PER_DAY		(24 * 60 * 60)

अटल पूर्णांक mcp795_rtcc_पढ़ो(काष्ठा device *dev, u8 addr, u8 *buf, u8 count)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक ret;
	u8 tx[2];

	tx[0] = MCP795_READ;
	tx[1] = addr;
	ret = spi_ग_लिखो_then_पढ़ो(spi, tx, माप(tx), buf, count);

	अगर (ret)
		dev_err(dev, "Failed reading %d bytes from address %x.\n",
					count, addr);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp795_rtcc_ग_लिखो(काष्ठा device *dev, u8 addr, u8 *data, u8 count)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक ret;
	u8 tx[257];

	tx[0] = MCP795_WRITE;
	tx[1] = addr;
	स_नकल(&tx[2], data, count);

	ret = spi_ग_लिखो(spi, tx, 2 + count);

	अगर (ret)
		dev_err(dev, "Failed to write %d bytes to address %x.\n",
					count, addr);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp795_rtcc_set_bits(काष्ठा device *dev, u8 addr, u8 mask, u8 state)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	ret = mcp795_rtcc_पढ़ो(dev, addr, &पंचांगp, 1);
	अगर (ret)
		वापस ret;

	अगर ((पंचांगp & mask) != state) अणु
		पंचांगp = (पंचांगp & ~mask) | state;
		ret = mcp795_rtcc_ग_लिखो(dev, addr, &पंचांगp, 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mcp795_stop_oscillator(काष्ठा device *dev, bool *extosc)
अणु
	पूर्णांक retries = 5;
	पूर्णांक ret;
	u8 data;

	ret = mcp795_rtcc_set_bits(dev, MCP795_REG_SECONDS, MCP795_ST_BIT, 0);
	अगर (ret)
		वापस ret;
	ret = mcp795_rtcc_पढ़ो(dev, MCP795_REG_CONTROL, &data, 1);
	अगर (ret)
		वापस ret;
	*extosc = !!(data & MCP795_EXTOSC_BIT);
	ret = mcp795_rtcc_set_bits(
				dev, MCP795_REG_CONTROL, MCP795_EXTOSC_BIT, 0);
	अगर (ret)
		वापस ret;
	/* रुको क्रम the OSCON bit to clear */
	करो अणु
		usleep_range(700, 800);
		ret = mcp795_rtcc_पढ़ो(dev, MCP795_REG_DAY, &data, 1);
		अगर (ret)
			अवरोध;
		अगर (!(data & MCP795_OSCON_BIT))
			अवरोध;

	पूर्ण जबतक (--retries);

	वापस !retries ? -EIO : ret;
पूर्ण

अटल पूर्णांक mcp795_start_oscillator(काष्ठा device *dev, bool *extosc)
अणु
	अगर (extosc) अणु
		u8 data = *extosc ? MCP795_EXTOSC_BIT : 0;
		पूर्णांक ret;

		ret = mcp795_rtcc_set_bits(
			dev, MCP795_REG_CONTROL, MCP795_EXTOSC_BIT, data);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस mcp795_rtcc_set_bits(
			dev, MCP795_REG_SECONDS, MCP795_ST_BIT, MCP795_ST_BIT);
पूर्ण

/* Enable or disable Alarm 0 in RTC */
अटल पूर्णांक mcp795_update_alarm(काष्ठा device *dev, bool enable)
अणु
	पूर्णांक ret;

	dev_dbg(dev, "%s alarm\n", enable ? "Enable" : "Disable");

	अगर (enable) अणु
		/* clear ALM0IF (Alarm 0 Interrupt Flag) bit */
		ret = mcp795_rtcc_set_bits(dev, MCP795_REG_ALM0_DAY,
					MCP795_ALM0IF_BIT, 0);
		अगर (ret)
			वापस ret;
		/* enable alarm 0 */
		ret = mcp795_rtcc_set_bits(dev, MCP795_REG_CONTROL,
					MCP795_ALM0_BIT, MCP795_ALM0_BIT);
	पूर्ण अन्यथा अणु
		/* disable alarm 0 and alarm 1 */
		ret = mcp795_rtcc_set_bits(dev, MCP795_REG_CONTROL,
					MCP795_ALM0_BIT | MCP795_ALM1_BIT, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mcp795_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *tim)
अणु
	पूर्णांक ret;
	u8 data[7];
	bool extosc;

	/* Stop RTC and store current value of EXTOSC bit */
	ret = mcp795_stop_oscillator(dev, &extosc);
	अगर (ret)
		वापस ret;

	/* Read first, so we can leave config bits untouched */
	ret = mcp795_rtcc_पढ़ो(dev, MCP795_REG_SECONDS, data, माप(data));

	अगर (ret)
		वापस ret;

	data[0] = (data[0] & 0x80) | bin2bcd(tim->पंचांग_sec);
	data[1] = (data[1] & 0x80) | bin2bcd(tim->पंचांग_min);
	data[2] = bin2bcd(tim->पंचांग_hour);
	data[3] = (data[3] & 0xF8) | bin2bcd(tim->पंचांग_wday + 1);
	data[4] = bin2bcd(tim->पंचांग_mday);
	data[5] = (data[5] & MCP795_LP_BIT) | bin2bcd(tim->पंचांग_mon + 1);

	अगर (tim->पंचांग_year > 100)
		tim->पंचांग_year -= 100;

	data[6] = bin2bcd(tim->पंचांग_year);

	/* Always ग_लिखो the date and month using a separate Write command.
	 * This is a workaround क्रम a know silicon issue that some combinations
	 * of date and month values may result in the date being reset to 1.
	 */
	ret = mcp795_rtcc_ग_लिखो(dev, MCP795_REG_SECONDS, data, 5);
	अगर (ret)
		वापस ret;

	ret = mcp795_rtcc_ग_लिखो(dev, MCP795_REG_MONTH, &data[5], 2);
	अगर (ret)
		वापस ret;

	/* Start back RTC and restore previous value of EXTOSC bit.
	 * There is no need to clear EXTOSC bit when the previous value was 0
	 * because it was alपढ़ोy cleared when stopping the RTC oscillator.
	 */
	ret = mcp795_start_oscillator(dev, extosc ? &extosc : शून्य);
	अगर (ret)
		वापस ret;

	dev_dbg(dev, "Set mcp795: %ptR\n", tim);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp795_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *tim)
अणु
	पूर्णांक ret;
	u8 data[7];

	ret = mcp795_rtcc_पढ़ो(dev, MCP795_REG_SECONDS, data, माप(data));

	अगर (ret)
		वापस ret;

	tim->पंचांग_sec	= bcd2bin(data[0] & 0x7F);
	tim->पंचांग_min	= bcd2bin(data[1] & 0x7F);
	tim->पंचांग_hour	= bcd2bin(data[2] & 0x3F);
	tim->पंचांग_wday	= bcd2bin(data[3] & 0x07) - 1;
	tim->पंचांग_mday	= bcd2bin(data[4] & 0x3F);
	tim->पंचांग_mon	= bcd2bin(data[5] & 0x1F) - 1;
	tim->पंचांग_year	= bcd2bin(data[6]) + 100; /* Assume we are in 20xx */

	dev_dbg(dev, "Read from mcp795: %ptR\n", tim);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp795_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा rtc_समय now_पंचांग;
	समय64_t now;
	समय64_t later;
	u8 पंचांगp[6];
	पूर्णांक ret;

	/* Read current समय from RTC hardware */
	ret = mcp795_पढ़ो_समय(dev, &now_पंचांग);
	अगर (ret)
		वापस ret;
	/* Get the number of seconds since 1970 */
	now = rtc_पंचांग_to_समय64(&now_पंचांग);
	later = rtc_पंचांग_to_समय64(&alm->समय);
	अगर (later <= now)
		वापस -EINVAL;
	/* make sure alarm fires within the next one year */
	अगर ((later - now) >=
		(SEC_PER_DAY * (365 + is_leap_year(alm->समय.पंचांग_year))))
		वापस -गलत_तर्क;
	/* disable alarm */
	ret = mcp795_update_alarm(dev, false);
	अगर (ret)
		वापस ret;
	/* Read रेजिस्टरs, so we can leave configuration bits untouched */
	ret = mcp795_rtcc_पढ़ो(dev, MCP795_REG_ALM0_SECONDS, पंचांगp, माप(पंचांगp));
	अगर (ret)
		वापस ret;

	alm->समय.पंचांग_year	= -1;
	alm->समय.पंचांग_isdst	= -1;
	alm->समय.पंचांग_yday	= -1;

	पंचांगp[0] = (पंचांगp[0] & 0x80) | bin2bcd(alm->समय.पंचांग_sec);
	पंचांगp[1] = (पंचांगp[1] & 0x80) | bin2bcd(alm->समय.पंचांग_min);
	पंचांगp[2] = (पंचांगp[2] & 0xE0) | bin2bcd(alm->समय.पंचांग_hour);
	पंचांगp[3] = (पंचांगp[3] & 0x80) | bin2bcd(alm->समय.पंचांग_wday + 1);
	/* set alarm match: seconds, minutes, hour, day, date and month */
	पंचांगp[3] |= (MCP795_ALM0C2_BIT | MCP795_ALM0C1_BIT | MCP795_ALM0C0_BIT);
	पंचांगp[4] = (पंचांगp[4] & 0xC0) | bin2bcd(alm->समय.पंचांग_mday);
	पंचांगp[5] = (पंचांगp[5] & 0xE0) | bin2bcd(alm->समय.पंचांग_mon + 1);

	ret = mcp795_rtcc_ग_लिखो(dev, MCP795_REG_ALM0_SECONDS, पंचांगp, माप(पंचांगp));
	अगर (ret)
		वापस ret;

	/* enable alarm अगर requested */
	अगर (alm->enabled) अणु
		ret = mcp795_update_alarm(dev, true);
		अगर (ret)
			वापस ret;
		dev_dbg(dev, "Alarm IRQ armed\n");
	पूर्ण
	dev_dbg(dev, "Set alarm: %ptRdr(%d) %ptRt\n",
		&alm->समय, alm->समय.पंचांग_wday, &alm->समय);
	वापस 0;
पूर्ण

अटल पूर्णांक mcp795_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	u8 data[6];
	पूर्णांक ret;

	ret = mcp795_rtcc_पढ़ो(
			dev, MCP795_REG_ALM0_SECONDS, data, माप(data));
	अगर (ret)
		वापस ret;

	alm->समय.पंचांग_sec	= bcd2bin(data[0] & 0x7F);
	alm->समय.पंचांग_min	= bcd2bin(data[1] & 0x7F);
	alm->समय.पंचांग_hour	= bcd2bin(data[2] & 0x1F);
	alm->समय.पंचांग_wday	= bcd2bin(data[3] & 0x07) - 1;
	alm->समय.पंचांग_mday	= bcd2bin(data[4] & 0x3F);
	alm->समय.पंचांग_mon	= bcd2bin(data[5] & 0x1F) - 1;
	alm->समय.पंचांग_year	= -1;
	alm->समय.पंचांग_isdst	= -1;
	alm->समय.पंचांग_yday	= -1;

	dev_dbg(dev, "Read alarm: %ptRdr(%d) %ptRt\n",
		&alm->समय, alm->समय.पंचांग_wday, &alm->समय);
	वापस 0;
पूर्ण

अटल पूर्णांक mcp795_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	वापस mcp795_update_alarm(dev, !!enabled);
पूर्ण

अटल irqवापस_t mcp795_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा spi_device *spi = data;
	काष्ठा rtc_device *rtc = spi_get_drvdata(spi);
	पूर्णांक ret;

	rtc_lock(rtc);

	/* Disable alarm.
	 * There is no need to clear ALM0IF (Alarm 0 Interrupt Flag) bit,
	 * because it is करोne every समय when alarm is enabled.
	 */
	ret = mcp795_update_alarm(&spi->dev, false);
	अगर (ret)
		dev_err(&spi->dev,
			"Failed to disable alarm in IRQ (ret=%d)\n", ret);
	rtc_update_irq(rtc, 1, RTC_AF | RTC_IRQF);

	rtc_unlock(rtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mcp795_rtc_ops = अणु
		.पढ़ो_समय = mcp795_पढ़ो_समय,
		.set_समय = mcp795_set_समय,
		.पढ़ो_alarm = mcp795_पढ़ो_alarm,
		.set_alarm = mcp795_set_alarm,
		.alarm_irq_enable = mcp795_alarm_irq_enable
पूर्ण;

अटल पूर्णांक mcp795_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	पूर्णांक ret;

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret) अणु
		dev_err(&spi->dev, "Unable to setup SPI\n");
		वापस ret;
	पूर्ण

	/* Start the oscillator but करोn't set the value of EXTOSC bit */
	mcp795_start_oscillator(&spi->dev, शून्य);
	/* Clear the 12 hour mode flag*/
	mcp795_rtcc_set_bits(&spi->dev, 0x03, MCP795_24_BIT, 0);

	rtc = devm_rtc_device_रेजिस्टर(&spi->dev, "rtc-mcp795",
					&mcp795_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	अगर (spi->irq > 0) अणु
		dev_dbg(&spi->dev, "Alarm support enabled\n");

		/* Clear any pending alarm (ALM0IF bit) beक्रमe requesting
		 * the पूर्णांकerrupt.
		 */
		mcp795_rtcc_set_bits(&spi->dev, MCP795_REG_ALM0_DAY,
					MCP795_ALM0IF_BIT, 0);
		ret = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq, शून्य,
				mcp795_irq, IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				dev_name(&rtc->dev), spi);
		अगर (ret)
			dev_err(&spi->dev, "Failed to request IRQ: %d: %d\n",
						spi->irq, ret);
		अन्यथा
			device_init_wakeup(&spi->dev, true);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mcp795_of_match[] = अणु
	अणु .compatible = "maxim,mcp795" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp795_of_match);
#पूर्ण_अगर

अटल काष्ठा spi_driver mcp795_driver = अणु
		.driver = अणु
				.name = "rtc-mcp795",
				.of_match_table = of_match_ptr(mcp795_of_match),
		पूर्ण,
		.probe = mcp795_probe,
पूर्ण;

module_spi_driver(mcp795_driver);

MODULE_DESCRIPTION("MCP795 RTC SPI Driver");
MODULE_AUTHOR("Josef Gajdusek <atx@atx.name>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:mcp795");
