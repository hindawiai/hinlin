<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An SPI driver क्रम the Philips PCF2123 RTC
 * Copyright 2009 Cyber Switching, Inc.
 *
 * Author: Chris Verges <chrisv@cyberचयनing.com>
 * Maपूर्णांकainers: http://www.cyberचयनing.com
 *
 * based on the RS5C348 driver in this same directory.
 *
 * Thanks to Christian Pellegrin <chripell@fsfe.org> क्रम
 * the sysfs contributions to this driver.
 *
 * Please note that the CS is active high, so platक्रमm data
 * should look something like:
 *
 * अटल काष्ठा spi_board_info ek_spi_devices[] = अणु
 *	...
 *	अणु
 *		.modalias		= "rtc-pcf2123",
 *		.chip_select		= 1,
 *		.controller_data	= (व्योम *)AT91_PIN_PA10,
 *		.max_speed_hz		= 1000 * 1000,
 *		.mode			= SPI_CS_HIGH,
 *		.bus_num		= 0,
 *	पूर्ण,
 *	...
 *पूर्ण;
 */

#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

/* REGISTERS */
#घोषणा PCF2123_REG_CTRL1	(0x00)	/* Control Register 1 */
#घोषणा PCF2123_REG_CTRL2	(0x01)	/* Control Register 2 */
#घोषणा PCF2123_REG_SC		(0x02)	/* dateसमय */
#घोषणा PCF2123_REG_MN		(0x03)
#घोषणा PCF2123_REG_HR		(0x04)
#घोषणा PCF2123_REG_DM		(0x05)
#घोषणा PCF2123_REG_DW		(0x06)
#घोषणा PCF2123_REG_MO		(0x07)
#घोषणा PCF2123_REG_YR		(0x08)
#घोषणा PCF2123_REG_ALRM_MN	(0x09)	/* Alarm Registers */
#घोषणा PCF2123_REG_ALRM_HR	(0x0a)
#घोषणा PCF2123_REG_ALRM_DM	(0x0b)
#घोषणा PCF2123_REG_ALRM_DW	(0x0c)
#घोषणा PCF2123_REG_OFFSET	(0x0d)	/* Clock Rate Offset Register */
#घोषणा PCF2123_REG_TMR_CLKOUT	(0x0e)	/* Timer Registers */
#घोषणा PCF2123_REG_CTDWN_TMR	(0x0f)

/* PCF2123_REG_CTRL1 BITS */
#घोषणा CTRL1_CLEAR		(0)	/* Clear */
#घोषणा CTRL1_CORR_INT		BIT(1)	/* Correction irq enable */
#घोषणा CTRL1_12_HOUR		BIT(2)	/* 12 hour समय */
#घोषणा CTRL1_SW_RESET	(BIT(3) | BIT(4) | BIT(6))	/* Software reset */
#घोषणा CTRL1_STOP		BIT(5)	/* Stop the घड़ी */
#घोषणा CTRL1_EXT_TEST		BIT(7)	/* External घड़ी test mode */

/* PCF2123_REG_CTRL2 BITS */
#घोषणा CTRL2_TIE		BIT(0)	/* Countकरोwn समयr irq enable */
#घोषणा CTRL2_AIE		BIT(1)	/* Alarm irq enable */
#घोषणा CTRL2_TF		BIT(2)	/* Countकरोwn समयr flag */
#घोषणा CTRL2_AF		BIT(3)	/* Alarm flag */
#घोषणा CTRL2_TI_TP		BIT(4)	/* Irq pin generates pulse */
#घोषणा CTRL2_MSF		BIT(5)	/* Minute or second irq flag */
#घोषणा CTRL2_SI		BIT(6)	/* Second irq enable */
#घोषणा CTRL2_MI		BIT(7)	/* Minute irq enable */

/* PCF2123_REG_SC BITS */
#घोषणा OSC_HAS_STOPPED		BIT(7)	/* Clock has been stopped */

/* PCF2123_REG_ALRM_XX BITS */
#घोषणा ALRM_DISABLE		BIT(7)	/* MN, HR, DM, or DW alarm matching */

/* PCF2123_REG_TMR_CLKOUT BITS */
#घोषणा CD_TMR_4096KHZ		(0)	/* 4096 KHz countकरोwn समयr */
#घोषणा CD_TMR_64HZ		(1)	/* 64 Hz countकरोwn समयr */
#घोषणा CD_TMR_1HZ		(2)	/* 1 Hz countकरोwn समयr */
#घोषणा CD_TMR_60th_HZ		(3)	/* 60th Hz countकरोwn समयr */
#घोषणा CD_TMR_TE		BIT(3)	/* Countकरोwn समयr enable */

/* PCF2123_REG_OFFSET BITS */
#घोषणा OFFSET_SIGN_BIT		6	/* 2's complement sign bit */
#घोषणा OFFSET_COARSE		BIT(7)	/* Coarse mode offset */
#घोषणा OFFSET_STEP		(2170)	/* Offset step in parts per billion */
#घोषणा OFFSET_MASK		GENMASK(6, 0)	/* Offset value */

/* READ/WRITE ADDRESS BITS */
#घोषणा PCF2123_WRITE		BIT(4)
#घोषणा PCF2123_READ		(BIT(4) | BIT(7))


अटल काष्ठा spi_driver pcf2123_driver;

काष्ठा pcf2123_data अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap *map;
पूर्ण;

अटल स्थिर काष्ठा regmap_config pcf2123_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.पढ़ो_flag_mask = PCF2123_READ,
	.ग_लिखो_flag_mask = PCF2123_WRITE,
	.max_रेजिस्टर = PCF2123_REG_CTDWN_TMR,
पूर्ण;

अटल पूर्णांक pcf2123_पढ़ो_offset(काष्ठा device *dev, दीर्घ *offset)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	पूर्णांक ret, val;
	अचिन्हित पूर्णांक reg;

	ret = regmap_पढ़ो(pcf2123->map, PCF2123_REG_OFFSET, &reg);
	अगर (ret)
		वापस ret;

	val = sign_extend32((reg & OFFSET_MASK), OFFSET_SIGN_BIT);

	अगर (reg & OFFSET_COARSE)
		val *= 2;

	*offset = ((दीर्घ)val) * OFFSET_STEP;

	वापस 0;
पूर्ण

/*
 * The offset रेजिस्टर is a 7 bit चिन्हित value with a coarse bit in bit 7.
 * The मुख्य dअगरference between the two is normal offset adjusts the first
 * second of n minutes every other hour, with 61, 62 and 63 being shoved
 * पूर्णांकo the 60th minute.
 * The coarse adjusपंचांगent करोes the same, but every hour.
 * the two overlap, with every even normal offset value corresponding
 * to a coarse offset. Based on this algorithm, it seems that despite the
 * name, coarse offset is a better fit क्रम overlapping values.
 */
अटल पूर्णांक pcf2123_set_offset(काष्ठा device *dev, दीर्घ offset)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	s8 reg;

	अगर (offset > OFFSET_STEP * 127)
		reg = 127;
	अन्यथा अगर (offset < OFFSET_STEP * -128)
		reg = -128;
	अन्यथा
		reg = DIV_ROUND_CLOSEST(offset, OFFSET_STEP);

	/* choose fine offset only क्रम odd values in the normal range */
	अगर (reg & 1 && reg <= 63 && reg >= -64) अणु
		/* Normal offset. Clear the coarse bit */
		reg &= ~OFFSET_COARSE;
	पूर्ण अन्यथा अणु
		/* Coarse offset. Divide by 2 and set the coarse bit */
		reg >>= 1;
		reg |= OFFSET_COARSE;
	पूर्ण

	वापस regmap_ग_लिखो(pcf2123->map, PCF2123_REG_OFFSET, (अचिन्हित पूर्णांक)reg);
पूर्ण

अटल पूर्णांक pcf2123_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	u8 rxbuf[7];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(pcf2123->map, PCF2123_REG_SC, rxbuf,
				माप(rxbuf));
	अगर (ret)
		वापस ret;

	अगर (rxbuf[0] & OSC_HAS_STOPPED) अणु
		dev_info(dev, "clock was stopped. Time is not valid\n");
		वापस -EINVAL;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(rxbuf[0] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(rxbuf[1] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(rxbuf[2] & 0x3F); /* rtc hr 0-23 */
	पंचांग->पंचांग_mday = bcd2bin(rxbuf[3] & 0x3F);
	पंचांग->पंचांग_wday = rxbuf[4] & 0x07;
	पंचांग->पंचांग_mon = bcd2bin(rxbuf[5] & 0x1F) - 1; /* rtc mn 1-12 */
	पंचांग->पंचांग_year = bcd2bin(rxbuf[6]) + 100;

	dev_dbg(dev, "%s: tm is %ptR\n", __func__, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2123_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	u8 txbuf[7];
	पूर्णांक ret;

	dev_dbg(dev, "%s: tm is %ptR\n", __func__, पंचांग);

	/* Stop the counter first */
	ret = regmap_ग_लिखो(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_STOP);
	अगर (ret)
		वापस ret;

	/* Set the new समय */
	txbuf[0] = bin2bcd(पंचांग->पंचांग_sec & 0x7F);
	txbuf[1] = bin2bcd(पंचांग->पंचांग_min & 0x7F);
	txbuf[2] = bin2bcd(पंचांग->पंचांग_hour & 0x3F);
	txbuf[3] = bin2bcd(पंचांग->पंचांग_mday & 0x3F);
	txbuf[4] = पंचांग->पंचांग_wday & 0x07;
	txbuf[5] = bin2bcd((पंचांग->पंचांग_mon + 1) & 0x1F); /* rtc mn 1-12 */
	txbuf[6] = bin2bcd(पंचांग->पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(pcf2123->map, PCF2123_REG_SC, txbuf,
				माप(txbuf));
	अगर (ret)
		वापस ret;

	/* Start the counter */
	ret = regmap_ग_लिखो(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_CLEAR);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2123_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक en)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);

	वापस regmap_update_bits(pcf2123->map, PCF2123_REG_CTRL2, CTRL2_AIE,
				  en ? CTRL2_AIE : 0);
पूर्ण

अटल पूर्णांक pcf2123_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	u8 rxbuf[4];
	पूर्णांक ret;
	अचिन्हित पूर्णांक val = 0;

	ret = regmap_bulk_पढ़ो(pcf2123->map, PCF2123_REG_ALRM_MN, rxbuf,
				माप(rxbuf));
	अगर (ret)
		वापस ret;

	alm->समय.पंचांग_min = bcd2bin(rxbuf[0] & 0x7F);
	alm->समय.पंचांग_hour = bcd2bin(rxbuf[1] & 0x3F);
	alm->समय.पंचांग_mday = bcd2bin(rxbuf[2] & 0x3F);
	alm->समय.पंचांग_wday = bcd2bin(rxbuf[3] & 0x07);

	dev_dbg(dev, "%s: alm is %ptR\n", __func__, &alm->समय);

	ret = regmap_पढ़ो(pcf2123->map, PCF2123_REG_CTRL2, &val);
	अगर (ret)
		वापस ret;

	alm->enabled = !!(val & CTRL2_AIE);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2123_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	u8 txbuf[4];
	पूर्णांक ret;

	dev_dbg(dev, "%s: alm is %ptR\n", __func__, &alm->समय);

	/* Disable alarm पूर्णांकerrupt */
	ret = regmap_update_bits(pcf2123->map, PCF2123_REG_CTRL2, CTRL2_AIE, 0);
	अगर (ret)
		वापस ret;

	/* Ensure alarm flag is clear */
	ret = regmap_update_bits(pcf2123->map, PCF2123_REG_CTRL2, CTRL2_AF, 0);
	अगर (ret)
		वापस ret;

	/* Set new alarm */
	txbuf[0] = bin2bcd(alm->समय.पंचांग_min & 0x7F);
	txbuf[1] = bin2bcd(alm->समय.पंचांग_hour & 0x3F);
	txbuf[2] = bin2bcd(alm->समय.पंचांग_mday & 0x3F);
	txbuf[3] = ALRM_DISABLE;

	ret = regmap_bulk_ग_लिखो(pcf2123->map, PCF2123_REG_ALRM_MN, txbuf,
				माप(txbuf));
	अगर (ret)
		वापस ret;

	वापस pcf2123_rtc_alarm_irq_enable(dev, alm->enabled);
पूर्ण

अटल irqवापस_t pcf2123_rtc_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret = IRQ_NONE;

	rtc_lock(pcf2123->rtc);
	regmap_पढ़ो(pcf2123->map, PCF2123_REG_CTRL2, &val);

	/* Alarm? */
	अगर (val & CTRL2_AF) अणु
		ret = IRQ_HANDLED;

		/* Clear alarm flag */
		regmap_update_bits(pcf2123->map, PCF2123_REG_CTRL2, CTRL2_AF, 0);

		rtc_update_irq(pcf2123->rtc, 1, RTC_IRQF | RTC_AF);
	पूर्ण

	rtc_unlock(pcf2123->rtc);

	वापस ret;
पूर्ण

अटल पूर्णांक pcf2123_reset(काष्ठा device *dev)
अणु
	काष्ठा pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val = 0;

	ret = regmap_ग_लिखो(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_SW_RESET);
	अगर (ret)
		वापस ret;

	/* Stop the counter */
	dev_dbg(dev, "stopping RTC\n");
	ret = regmap_ग_लिखो(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_STOP);
	अगर (ret)
		वापस ret;

	/* See अगर the counter was actually stopped */
	dev_dbg(dev, "checking for presence of RTC\n");
	ret = regmap_पढ़ो(pcf2123->map, PCF2123_REG_CTRL1, &val);
	अगर (ret)
		वापस ret;

	dev_dbg(dev, "received data from RTC (0x%08X)\n", val);
	अगर (!(val & CTRL1_STOP))
		वापस -ENODEV;

	/* Start the counter */
	ret = regmap_ग_लिखो(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_CLEAR);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pcf2123_rtc_ops = अणु
	.पढ़ो_समय	= pcf2123_rtc_पढ़ो_समय,
	.set_समय	= pcf2123_rtc_set_समय,
	.पढ़ो_offset	= pcf2123_पढ़ो_offset,
	.set_offset	= pcf2123_set_offset,
	.पढ़ो_alarm	= pcf2123_rtc_पढ़ो_alarm,
	.set_alarm	= pcf2123_rtc_set_alarm,
	.alarm_irq_enable = pcf2123_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक pcf2123_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rtc_device *rtc;
	काष्ठा rtc_समय पंचांग;
	काष्ठा pcf2123_data *pcf2123;
	पूर्णांक ret = 0;

	pcf2123 = devm_kzalloc(&spi->dev, माप(काष्ठा pcf2123_data),
				GFP_KERNEL);
	अगर (!pcf2123)
		वापस -ENOMEM;

	dev_set_drvdata(&spi->dev, pcf2123);

	pcf2123->map = devm_regmap_init_spi(spi, &pcf2123_regmap_config);
	अगर (IS_ERR(pcf2123->map)) अणु
		dev_err(&spi->dev, "regmap init failed.\n");
		वापस PTR_ERR(pcf2123->map);
	पूर्ण

	ret = pcf2123_rtc_पढ़ो_समय(&spi->dev, &पंचांग);
	अगर (ret < 0) अणु
		ret = pcf2123_reset(&spi->dev);
		अगर (ret < 0) अणु
			dev_err(&spi->dev, "chip not found\n");
			वापस ret;
		पूर्ण
	पूर्ण

	dev_info(&spi->dev, "spiclk %u KHz.\n",
			(spi->max_speed_hz + 500) / 1000);

	/* Finalize the initialization */
	rtc = devm_rtc_allocate_device(&spi->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	pcf2123->rtc = rtc;

	/* Register alarm irq */
	अगर (spi->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq, शून्य,
				pcf2123_rtc_irq,
				IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				pcf2123_driver.driver.name, &spi->dev);
		अगर (!ret)
			device_init_wakeup(&spi->dev, true);
		अन्यथा
			dev_err(&spi->dev, "could not request irq.\n");
	पूर्ण

	/* The PCF2123's alarm only has minute accuracy. Must add समयr
	 * support to this driver to generate पूर्णांकerrupts more than once
	 * per minute.
	 */
	rtc->uie_unsupported = 1;
	rtc->ops = &pcf2123_rtc_ops;
	rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->range_max = RTC_TIMESTAMP_END_2099;
	rtc->set_start_समय = true;

	ret = devm_rtc_रेजिस्टर_device(rtc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcf2123_dt_ids[] = अणु
	अणु .compatible = "nxp,pcf2123", पूर्ण,
	अणु .compatible = "microcrystal,rv2123", पूर्ण,
	/* Deprecated, करो not use */
	अणु .compatible = "nxp,rtc-pcf2123", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcf2123_dt_ids);
#पूर्ण_अगर

अटल काष्ठा spi_driver pcf2123_driver = अणु
	.driver	= अणु
			.name	= "rtc-pcf2123",
			.of_match_table = of_match_ptr(pcf2123_dt_ids),
	पूर्ण,
	.probe	= pcf2123_probe,
पूर्ण;

module_spi_driver(pcf2123_driver);

MODULE_AUTHOR("Chris Verges <chrisv@cyberswitching.com>");
MODULE_DESCRIPTION("NXP PCF2123 RTC driver");
MODULE_LICENSE("GPL");
