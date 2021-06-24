<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rtc-dm355evm.c - access battery-backed counter in MSP430 firmware
 *
 * Copyright (c) 2008 by David Brownell
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/dm355evm_msp.h>
#समावेश <linux/module.h>


/*
 * The MSP430 firmware on the DM355 EVM uses a watch crystal to feed
 * a 1 Hz counter.  When a backup battery is supplied, that makes a
 * reasonable RTC क्रम applications where alarms and non-NTP drअगरt
 * compensation aren't important.
 *
 * The only real glitch is the inability to पढ़ो or ग_लिखो all four
 * counter bytes atomically:  the count may increment in the middle
 * of an operation, causing trouble when the LSB rolls over.
 *
 * This driver was tested with firmware revision A4.
 */
जोड़ evm_समय अणु
	u8	bytes[4];
	u32	value;
पूर्ण;

अटल पूर्णांक dm355evm_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	जोड़ evm_समय	समय;
	पूर्णांक		status;
	पूर्णांक		tries = 0;

	करो अणु
		/*
		 * Read LSB(0) to MSB(3) bytes.  Defend against the counter
		 * rolling over by re-पढ़ोing until the value is stable,
		 * and assuming the four पढ़ोs take at most a few seconds.
		 */
		status = dm355evm_msp_पढ़ो(DM355EVM_MSP_RTC_0);
		अगर (status < 0)
			वापस status;
		अगर (tries && समय.bytes[0] == status)
			अवरोध;
		समय.bytes[0] = status;

		status = dm355evm_msp_पढ़ो(DM355EVM_MSP_RTC_1);
		अगर (status < 0)
			वापस status;
		अगर (tries && समय.bytes[1] == status)
			अवरोध;
		समय.bytes[1] = status;

		status = dm355evm_msp_पढ़ो(DM355EVM_MSP_RTC_2);
		अगर (status < 0)
			वापस status;
		अगर (tries && समय.bytes[2] == status)
			अवरोध;
		समय.bytes[2] = status;

		status = dm355evm_msp_पढ़ो(DM355EVM_MSP_RTC_3);
		अगर (status < 0)
			वापस status;
		अगर (tries && समय.bytes[3] == status)
			अवरोध;
		समय.bytes[3] = status;

	पूर्ण जबतक (++tries < 5);

	dev_dbg(dev, "read timestamp %08x\n", समय.value);

	rtc_समय64_to_पंचांग(le32_to_cpu(समय.value), पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक dm355evm_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	जोड़ evm_समय	समय;
	अचिन्हित दीर्घ	value;
	पूर्णांक		status;

	value = rtc_पंचांग_to_समय64(पंचांग);
	समय.value = cpu_to_le32(value);

	dev_dbg(dev, "write timestamp %08x\n", समय.value);

	/*
	 * REVISIT handle non-atomic ग_लिखोs ... maybe just retry until
	 * byte[1] sticks (no rollover)?
	 */
	status = dm355evm_msp_ग_लिखो(समय.bytes[0], DM355EVM_MSP_RTC_0);
	अगर (status < 0)
		वापस status;

	status = dm355evm_msp_ग_लिखो(समय.bytes[1], DM355EVM_MSP_RTC_1);
	अगर (status < 0)
		वापस status;

	status = dm355evm_msp_ग_लिखो(समय.bytes[2], DM355EVM_MSP_RTC_2);
	अगर (status < 0)
		वापस status;

	status = dm355evm_msp_ग_लिखो(समय.bytes[3], DM355EVM_MSP_RTC_3);
	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops dm355evm_rtc_ops = अणु
	.पढ़ो_समय	= dm355evm_rtc_पढ़ो_समय,
	.set_समय	= dm355evm_rtc_set_समय,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल पूर्णांक dm355evm_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->ops = &dm355evm_rtc_ops;
	rtc->range_max = U32_MAX;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

/*
 * I2C is used to talk to the MSP430, but this platक्रमm device is
 * exposed by an MFD driver that manages I2C communications.
 */
अटल काष्ठा platक्रमm_driver rtc_dm355evm_driver = अणु
	.probe		= dm355evm_rtc_probe,
	.driver		= अणु
		.name	= "rtc-dm355evm",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rtc_dm355evm_driver);

MODULE_LICENSE("GPL");
