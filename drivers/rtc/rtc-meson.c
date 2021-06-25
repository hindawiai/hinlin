<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC driver क्रम the पूर्णांकeral RTC block in the Amlogic Meson6, Meson8,
 * Meson8b and Meson8m2 SoCs.
 *
 * The RTC is split in to two parts, the AHB front end and a simple serial
 * connection to the actual रेजिस्टरs. This driver manages both parts.
 *
 * Copyright (c) 2018 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 * Copyright (c) 2015 Ben Dooks <ben.करोoks@codethink.co.uk> क्रम Codethink Ltd
 * Based on origin by Carlo Caione <carlo@endlessm.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/rtc.h>

/* रेजिस्टरs accessed from cpu bus */
#घोषणा RTC_ADDR0				0x00
	#घोषणा RTC_ADDR0_LINE_SCLK		BIT(0)
	#घोषणा RTC_ADDR0_LINE_SEN		BIT(1)
	#घोषणा RTC_ADDR0_LINE_SDI		BIT(2)
	#घोषणा RTC_ADDR0_START_SER		BIT(17)
	#घोषणा RTC_ADDR0_WAIT_SER		BIT(22)
	#घोषणा RTC_ADDR0_DATA			GENMASK(31, 24)

#घोषणा RTC_ADDR1				0x04
	#घोषणा RTC_ADDR1_SDO			BIT(0)
	#घोषणा RTC_ADDR1_S_READY		BIT(1)

#घोषणा RTC_ADDR2				0x08
#घोषणा RTC_ADDR3				0x0c

#घोषणा RTC_REG4				0x10
	#घोषणा RTC_REG4_STATIC_VALUE		GENMASK(7, 0)

/* rtc रेजिस्टरs accessed via rtc-serial पूर्णांकerface */
#घोषणा RTC_COUNTER		(0)
#घोषणा RTC_SEC_ADJ		(2)
#घोषणा RTC_REGMEM_0		(4)
#घोषणा RTC_REGMEM_1		(5)
#घोषणा RTC_REGMEM_2		(6)
#घोषणा RTC_REGMEM_3		(7)

#घोषणा RTC_ADDR_BITS		(3)	/* number of address bits to send */
#घोषणा RTC_DATA_BITS		(32)	/* number of data bits to tx/rx */

#घोषणा MESON_STATIC_BIAS_CUR	(0x5 << 1)
#घोषणा MESON_STATIC_VOLTAGE	(0x3 << 11)
#घोषणा MESON_STATIC_DEFAULT    (MESON_STATIC_BIAS_CUR | MESON_STATIC_VOLTAGE)

काष्ठा meson_rtc अणु
	काष्ठा rtc_device	*rtc;		/* rtc device we created */
	काष्ठा device		*dev;		/* device we bound from */
	काष्ठा reset_control	*reset;		/* reset source */
	काष्ठा regulator	*vdd;		/* voltage input */
	काष्ठा regmap		*peripheral;	/* peripheral रेजिस्टरs */
	काष्ठा regmap		*serial;	/* serial रेजिस्टरs */
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson_rtc_peripheral_regmap_config = अणु
	.name		= "peripheral-registers",
	.reg_bits	= 8,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= RTC_REG4,
	.fast_io	= true,
पूर्ण;

/* RTC front-end serialiser controls */

अटल व्योम meson_rtc_sclk_pulse(काष्ठा meson_rtc *rtc)
अणु
	udelay(5);
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SCLK, 0);
	udelay(5);
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SCLK,
			   RTC_ADDR0_LINE_SCLK);
पूर्ण

अटल व्योम meson_rtc_send_bit(काष्ठा meson_rtc *rtc, अचिन्हित पूर्णांक bit)
अणु
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SDI,
			   bit ? RTC_ADDR0_LINE_SDI : 0);
	meson_rtc_sclk_pulse(rtc);
पूर्ण

अटल व्योम meson_rtc_send_bits(काष्ठा meson_rtc *rtc, u32 data,
				अचिन्हित पूर्णांक nr)
अणु
	u32 bit = 1 << (nr - 1);

	जबतक (bit) अणु
		meson_rtc_send_bit(rtc, data & bit);
		bit >>= 1;
	पूर्ण
पूर्ण

अटल व्योम meson_rtc_set_dir(काष्ठा meson_rtc *rtc, u32 mode)
अणु
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SEN, 0);
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SDI, 0);
	meson_rtc_send_bit(rtc, mode);
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SDI, 0);
पूर्ण

अटल u32 meson_rtc_get_data(काष्ठा meson_rtc *rtc)
अणु
	u32 पंचांगp, val = 0;
	पूर्णांक bit;

	क्रम (bit = 0; bit < RTC_DATA_BITS; bit++) अणु
		meson_rtc_sclk_pulse(rtc);
		val <<= 1;

		regmap_पढ़ो(rtc->peripheral, RTC_ADDR1, &पंचांगp);
		val |= पंचांगp & RTC_ADDR1_SDO;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक meson_rtc_get_bus(काष्ठा meson_rtc *rtc)
अणु
	पूर्णांक ret, retries;
	u32 val;

	/* prepare bus क्रम transfers, set all lines low */
	val = RTC_ADDR0_LINE_SDI | RTC_ADDR0_LINE_SEN | RTC_ADDR0_LINE_SCLK;
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, val, 0);

	क्रम (retries = 0; retries < 3; retries++) अणु
		/* रुको क्रम the bus to be पढ़ोy */
		अगर (!regmap_पढ़ो_poll_समयout(rtc->peripheral, RTC_ADDR1, val,
					      val & RTC_ADDR1_S_READY, 10,
					      10000))
			वापस 0;

		dev_warn(rtc->dev, "failed to get bus, resetting RTC\n");

		ret = reset_control_reset(rtc->reset);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_err(rtc->dev, "bus is not ready\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक meson_rtc_serial_bus_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
					 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा meson_rtc *rtc = context;
	पूर्णांक ret;

	ret = meson_rtc_get_bus(rtc);
	अगर (ret)
		वापस ret;

	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SEN,
			   RTC_ADDR0_LINE_SEN);
	meson_rtc_send_bits(rtc, reg, RTC_ADDR_BITS);
	meson_rtc_set_dir(rtc, 0);
	*data = meson_rtc_get_data(rtc);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_rtc_serial_bus_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
					  अचिन्हित पूर्णांक data)
अणु
	काष्ठा meson_rtc *rtc = context;
	पूर्णांक ret;

	ret = meson_rtc_get_bus(rtc);
	अगर (ret)
		वापस ret;

	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SEN,
			   RTC_ADDR0_LINE_SEN);
	meson_rtc_send_bits(rtc, data, RTC_DATA_BITS);
	meson_rtc_send_bits(rtc, reg, RTC_ADDR_BITS);
	meson_rtc_set_dir(rtc, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_bus meson_rtc_serial_bus = अणु
	.reg_पढ़ो	= meson_rtc_serial_bus_reg_पढ़ो,
	.reg_ग_लिखो	= meson_rtc_serial_bus_reg_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson_rtc_serial_regmap_config = अणु
	.name		= "serial-registers",
	.reg_bits	= 4,
	.reg_stride	= 1,
	.val_bits	= 32,
	.max_रेजिस्टर	= RTC_REGMEM_3,
	.fast_io	= false,
पूर्ण;

अटल पूर्णांक meson_rtc_ग_लिखो_अटल(काष्ठा meson_rtc *rtc, u32 data)
अणु
	u32 पंचांगp;

	regmap_ग_लिखो(rtc->peripheral, RTC_REG4,
		     FIELD_PREP(RTC_REG4_STATIC_VALUE, (data >> 8)));

	/* ग_लिखो the अटल value and start the स्वतः serializer */
	पंचांगp = FIELD_PREP(RTC_ADDR0_DATA, (data & 0xff)) | RTC_ADDR0_START_SER;
	regmap_update_bits(rtc->peripheral, RTC_ADDR0,
			   RTC_ADDR0_DATA | RTC_ADDR0_START_SER, पंचांगp);

	/* रुको क्रम the स्वतः serializer to complete */
	वापस regmap_पढ़ो_poll_समयout(rtc->peripheral, RTC_REG4, पंचांगp,
					!(पंचांगp & RTC_ADDR0_WAIT_SER), 10,
					10000);
पूर्ण

/* RTC पूर्णांकerface layer functions */

अटल पूर्णांक meson_rtc_समय_लो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा meson_rtc *rtc = dev_get_drvdata(dev);
	u32 समय;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rtc->serial, RTC_COUNTER, &समय);
	अगर (!ret)
		rtc_समय64_to_पंचांग(समय, पंचांग);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा meson_rtc *rtc = dev_get_drvdata(dev);

	वापस regmap_ग_लिखो(rtc->serial, RTC_COUNTER, rtc_पंचांग_to_समय64(पंचांग));
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops meson_rtc_ops = अणु
	.पढ़ो_समय	= meson_rtc_समय_लो,
	.set_समय	= meson_rtc_समय_रखो,
पूर्ण;

/* NVMEM पूर्णांकerface layer functions */

अटल पूर्णांक meson_rtc_regmem_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
				 व्योम *buf, माप_प्रकार bytes)
अणु
	काष्ठा meson_rtc *rtc = context;
	अचिन्हित पूर्णांक पढ़ो_offset, पढ़ो_size;

	पढ़ो_offset = RTC_REGMEM_0 + (offset / 4);
	पढ़ो_size = bytes / 4;

	वापस regmap_bulk_पढ़ो(rtc->serial, पढ़ो_offset, buf, पढ़ो_size);
पूर्ण

अटल पूर्णांक meson_rtc_regmem_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक offset,
				  व्योम *buf, माप_प्रकार bytes)
अणु
	काष्ठा meson_rtc *rtc = context;
	अचिन्हित पूर्णांक ग_लिखो_offset, ग_लिखो_size;

	ग_लिखो_offset = RTC_REGMEM_0 + (offset / 4);
	ग_लिखो_size = bytes / 4;

	वापस regmap_bulk_ग_लिखो(rtc->serial, ग_लिखो_offset, buf, ग_लिखो_size);
पूर्ण

अटल पूर्णांक meson_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvmem_config meson_rtc_nvmem_config = अणु
		.name = "meson-rtc-regmem",
		.type = NVMEM_TYPE_BATTERY_BACKED,
		.word_size = 4,
		.stride = 4,
		.size = 4 * 4,
		.reg_पढ़ो = meson_rtc_regmem_पढ़ो,
		.reg_ग_लिखो = meson_rtc_regmem_ग_लिखो,
	पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_rtc *rtc;
	व्योम __iomem *base;
	पूर्णांक ret;
	u32 पंचांग;

	rtc = devm_kzalloc(dev, माप(काष्ठा meson_rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(rtc->rtc))
		वापस PTR_ERR(rtc->rtc);

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->dev = dev;

	rtc->rtc->ops = &meson_rtc_ops;
	rtc->rtc->range_max = U32_MAX;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	rtc->peripheral = devm_regmap_init_mmio(dev, base,
					&meson_rtc_peripheral_regmap_config);
	अगर (IS_ERR(rtc->peripheral)) अणु
		dev_err(dev, "failed to create peripheral regmap\n");
		वापस PTR_ERR(rtc->peripheral);
	पूर्ण

	rtc->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(rtc->reset)) अणु
		dev_err(dev, "missing reset line\n");
		वापस PTR_ERR(rtc->reset);
	पूर्ण

	rtc->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(rtc->vdd)) अणु
		dev_err(dev, "failed to get the vdd-supply\n");
		वापस PTR_ERR(rtc->vdd);
	पूर्ण

	ret = regulator_enable(rtc->vdd);
	अगर (ret) अणु
		dev_err(dev, "failed to enable vdd-supply\n");
		वापस ret;
	पूर्ण

	ret = meson_rtc_ग_लिखो_अटल(rtc, MESON_STATIC_DEFAULT);
	अगर (ret) अणु
		dev_err(dev, "failed to set static values\n");
		जाओ out_disable_vdd;
	पूर्ण

	rtc->serial = devm_regmap_init(dev, &meson_rtc_serial_bus, rtc,
				       &meson_rtc_serial_regmap_config);
	अगर (IS_ERR(rtc->serial)) अणु
		dev_err(dev, "failed to create serial regmap\n");
		ret = PTR_ERR(rtc->serial);
		जाओ out_disable_vdd;
	पूर्ण

	/*
	 * check अगर we can पढ़ो RTC counter, अगर not then the RTC is probably
	 * not functional. If it isn't probably best to not bind.
	 */
	ret = regmap_पढ़ो(rtc->serial, RTC_COUNTER, &पंचांग);
	अगर (ret) अणु
		dev_err(dev, "cannot read RTC counter, RTC not functional\n");
		जाओ out_disable_vdd;
	पूर्ण

	meson_rtc_nvmem_config.priv = rtc;
	ret = devm_rtc_nvmem_रेजिस्टर(rtc->rtc, &meson_rtc_nvmem_config);
	अगर (ret)
		जाओ out_disable_vdd;

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (ret)
		जाओ out_disable_vdd;

	वापस 0;

out_disable_vdd:
	regulator_disable(rtc->vdd);
	वापस ret;
पूर्ण

अटल स्थिर __maybe_unused काष्ठा of_device_id meson_rtc_dt_match[] = अणु
	अणु .compatible = "amlogic,meson6-rtc", पूर्ण,
	अणु .compatible = "amlogic,meson8-rtc", पूर्ण,
	अणु .compatible = "amlogic,meson8b-rtc", पूर्ण,
	अणु .compatible = "amlogic,meson8m2-rtc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_rtc_dt_match);

अटल काष्ठा platक्रमm_driver meson_rtc_driver = अणु
	.probe		= meson_rtc_probe,
	.driver		= अणु
		.name		= "meson-rtc",
		.of_match_table	= of_match_ptr(meson_rtc_dt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_rtc_driver);

MODULE_DESCRIPTION("Amlogic Meson RTC Driver");
MODULE_AUTHOR("Ben Dooks <ben.doosk@codethink.co.uk>");
MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:meson-rtc");
