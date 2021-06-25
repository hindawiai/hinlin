<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Technologic Systems TS-5500 Single Board Computer support
 *
 * Copyright (C) 2013-2014 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *
 * This driver रेजिस्टरs the Technologic Systems TS-5500 Single Board Computer
 * (SBC) and its devices, and exposes inक्रमmation to userspace such as jumpers'
 * state or available options. For further inक्रमmation about sysfs entries, see
 * Documentation/ABI/testing/sysfs-platक्रमm-ts5500.
 *
 * This code may be extended to support similar x86-based platक्रमms.
 * Actually, the TS-5500 and TS-5400 are supported.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_data/max197.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* Product code रेजिस्टर */
#घोषणा TS5500_PRODUCT_CODE_ADDR	0x74
#घोषणा TS5500_PRODUCT_CODE		0x60	/* TS-5500 product code */
#घोषणा TS5400_PRODUCT_CODE		0x40	/* TS-5400 product code */

/* SRAM/RS-485/ADC options, and RS-485 RTS/Automatic RS-485 flags रेजिस्टर */
#घोषणा TS5500_SRAM_RS485_ADC_ADDR	0x75
#घोषणा TS5500_SRAM			BIT(0)	/* SRAM option */
#घोषणा TS5500_RS485			BIT(1)	/* RS-485 option */
#घोषणा TS5500_ADC			BIT(2)	/* A/D converter option */
#घोषणा TS5500_RS485_RTS		BIT(6)	/* RTS क्रम RS-485 */
#घोषणा TS5500_RS485_AUTO		BIT(7)	/* Automatic RS-485 */

/* External Reset/Industrial Temperature Range options रेजिस्टर */
#घोषणा TS5500_ERESET_ITR_ADDR		0x76
#घोषणा TS5500_ERESET			BIT(0)	/* External Reset option */
#घोषणा TS5500_ITR			BIT(1)	/* Indust. Temp. Range option */

/* LED/Jumpers रेजिस्टर */
#घोषणा TS5500_LED_JP_ADDR		0x77
#घोषणा TS5500_LED			BIT(0)	/* LED flag */
#घोषणा TS5500_JP1			BIT(1)	/* Automatic CMOS */
#घोषणा TS5500_JP2			BIT(2)	/* Enable Serial Console */
#घोषणा TS5500_JP3			BIT(3)	/* Write Enable Drive A */
#घोषणा TS5500_JP4			BIT(4)	/* Fast Console (115K baud) */
#घोषणा TS5500_JP5			BIT(5)	/* User Jumper */
#घोषणा TS5500_JP6			BIT(6)	/* Console on COM1 (req. JP2) */
#घोषणा TS5500_JP7			BIT(7)	/* Unकरोcumented (Unused) */

/* A/D Converter रेजिस्टरs */
#घोषणा TS5500_ADC_CONV_BUSY_ADDR	0x195	/* Conversion state रेजिस्टर */
#घोषणा TS5500_ADC_CONV_BUSY		BIT(0)
#घोषणा TS5500_ADC_CONV_INIT_LSB_ADDR	0x196	/* Start conv. / LSB रेजिस्टर */
#घोषणा TS5500_ADC_CONV_MSB_ADDR	0x197	/* MSB रेजिस्टर */
#घोषणा TS5500_ADC_CONV_DELAY		12	/* usec */

/**
 * काष्ठा ts5500_sbc - TS-5500 board description
 * @name:	Board model name.
 * @id:		Board product ID.
 * @sram:	Flag क्रम SRAM option.
 * @rs485:	Flag क्रम RS-485 option.
 * @adc:	Flag क्रम Analog/Digital converter option.
 * @ereset:	Flag क्रम External Reset option.
 * @itr:	Flag क्रम Industrial Temperature Range option.
 * @jumpers:	Bitfield क्रम jumpers' state.
 */
काष्ठा ts5500_sbc अणु
	स्थिर अक्षर *name;
	पूर्णांक	id;
	bool	sram;
	bool	rs485;
	bool	adc;
	bool	ereset;
	bool	itr;
	u8	jumpers;
पूर्ण;

/* Board signatures in BIOS shaकरोw RAM */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर * स्थिर string;
	स्थिर sमाप_प्रकार offset;
पूर्ण ts5500_signatures[] __initस्थिर = अणु
	अणु "TS-5x00 AMD Elan", 0xb14 पूर्ण,
पूर्ण;

अटल पूर्णांक __init ts5500_check_signature(व्योम)
अणु
	व्योम __iomem *bios;
	पूर्णांक i, ret = -ENODEV;

	bios = ioremap(0xf0000, 0x10000);
	अगर (!bios)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(ts5500_signatures); i++) अणु
		अगर (check_signature(bios + ts5500_signatures[i].offset,
				    ts5500_signatures[i].string,
				    म_माप(ts5500_signatures[i].string))) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	iounmap(bios);
	वापस ret;
पूर्ण

अटल पूर्णांक __init ts5500_detect_config(काष्ठा ts5500_sbc *sbc)
अणु
	u8 पंचांगp;
	पूर्णांक ret = 0;

	अगर (!request_region(TS5500_PRODUCT_CODE_ADDR, 4, "ts5500"))
		वापस -EBUSY;

	sbc->id = inb(TS5500_PRODUCT_CODE_ADDR);
	अगर (sbc->id == TS5500_PRODUCT_CODE) अणु
		sbc->name = "TS-5500";
	पूर्ण अन्यथा अगर (sbc->id == TS5400_PRODUCT_CODE) अणु
		sbc->name = "TS-5400";
	पूर्ण अन्यथा अणु
		pr_err("ts5500: unknown product code 0x%x\n", sbc->id);
		ret = -ENODEV;
		जाओ cleanup;
	पूर्ण

	पंचांगp = inb(TS5500_SRAM_RS485_ADC_ADDR);
	sbc->sram = पंचांगp & TS5500_SRAM;
	sbc->rs485 = पंचांगp & TS5500_RS485;
	sbc->adc = पंचांगp & TS5500_ADC;

	पंचांगp = inb(TS5500_ERESET_ITR_ADDR);
	sbc->ereset = पंचांगp & TS5500_ERESET;
	sbc->itr = पंचांगp & TS5500_ITR;

	पंचांगp = inb(TS5500_LED_JP_ADDR);
	sbc->jumpers = पंचांगp & ~TS5500_LED;

cleanup:
	release_region(TS5500_PRODUCT_CODE_ADDR, 4);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा ts5500_sbc *sbc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", sbc->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा ts5500_sbc *sbc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%.2x\n", sbc->id);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार jumpers_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा ts5500_sbc *sbc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%.2x\n", sbc->jumpers >> 1);
पूर्ण
अटल DEVICE_ATTR_RO(jumpers);

#घोषणा TS5500_ATTR_BOOL(_field)					\
	अटल sमाप_प्रकार _field##_show(काष्ठा device *dev,		\
			काष्ठा device_attribute *attr, अक्षर *buf)	\
	अणु								\
		काष्ठा ts5500_sbc *sbc = dev_get_drvdata(dev);		\
									\
		वापस प्र_लिखो(buf, "%d\n", sbc->_field);		\
	पूर्ण								\
	अटल DEVICE_ATTR_RO(_field)

TS5500_ATTR_BOOL(sram);
TS5500_ATTR_BOOL(rs485);
TS5500_ATTR_BOOL(adc);
TS5500_ATTR_BOOL(ereset);
TS5500_ATTR_BOOL(itr);

अटल काष्ठा attribute *ts5500_attributes[] = अणु
	&dev_attr_id.attr,
	&dev_attr_name.attr,
	&dev_attr_jumpers.attr,
	&dev_attr_sram.attr,
	&dev_attr_rs485.attr,
	&dev_attr_adc.attr,
	&dev_attr_ereset.attr,
	&dev_attr_itr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ts5500_attr_group = अणु
	.attrs = ts5500_attributes,
पूर्ण;

अटल काष्ठा resource ts5500_dio1_resource[] = अणु
	DEFINE_RES_IRQ_NAMED(7, "DIO1 interrupt"),
पूर्ण;

अटल काष्ठा platक्रमm_device ts5500_dio1_pdev = अणु
	.name = "ts5500-dio1",
	.id = -1,
	.resource = ts5500_dio1_resource,
	.num_resources = 1,
पूर्ण;

अटल काष्ठा resource ts5500_dio2_resource[] = अणु
	DEFINE_RES_IRQ_NAMED(6, "DIO2 interrupt"),
पूर्ण;

अटल काष्ठा platक्रमm_device ts5500_dio2_pdev = अणु
	.name = "ts5500-dio2",
	.id = -1,
	.resource = ts5500_dio2_resource,
	.num_resources = 1,
पूर्ण;

अटल व्योम ts5500_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness brightness)
अणु
	outb(!!brightness, TS5500_LED_JP_ADDR);
पूर्ण

अटल क्रमागत led_brightness ts5500_led_get(काष्ठा led_classdev *led_cdev)
अणु
	वापस (inb(TS5500_LED_JP_ADDR) & TS5500_LED) ? LED_FULL : LED_OFF;
पूर्ण

अटल काष्ठा led_classdev ts5500_led_cdev = अणु
	.name = "ts5500:green:",
	.brightness_set = ts5500_led_set,
	.brightness_get = ts5500_led_get,
पूर्ण;

अटल पूर्णांक ts5500_adc_convert(u8 ctrl)
अणु
	u8 lsb, msb;

	/* Start conversion (ensure the 3 MSB are set to 0) */
	outb(ctrl & 0x1f, TS5500_ADC_CONV_INIT_LSB_ADDR);

	/*
	 * The platक्रमm has CPLD logic driving the A/D converter.
	 * The conversion must complete within 11 microseconds,
	 * otherwise we have to re-initiate a conversion.
	 */
	udelay(TS5500_ADC_CONV_DELAY);
	अगर (inb(TS5500_ADC_CONV_BUSY_ADDR) & TS5500_ADC_CONV_BUSY)
		वापस -EBUSY;

	/* Read the raw data */
	lsb = inb(TS5500_ADC_CONV_INIT_LSB_ADDR);
	msb = inb(TS5500_ADC_CONV_MSB_ADDR);

	वापस (msb << 8) | lsb;
पूर्ण

अटल काष्ठा max197_platक्रमm_data ts5500_adc_pdata = अणु
	.convert = ts5500_adc_convert,
पूर्ण;

अटल काष्ठा platक्रमm_device ts5500_adc_pdev = अणु
	.name = "max197",
	.id = -1,
	.dev = अणु
		.platक्रमm_data = &ts5500_adc_pdata,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ts5500_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा ts5500_sbc *sbc;
	पूर्णांक err;

	/*
	 * There is no DMI available or PCI bridge subvenकरोr info,
	 * only the BIOS provides a 16-bit identअगरication call.
	 * It is safer to find a signature in the BIOS shaकरोw RAM.
	 */
	err = ts5500_check_signature();
	अगर (err)
		वापस err;

	pdev = platक्रमm_device_रेजिस्टर_simple("ts5500", -1, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	sbc = devm_kzalloc(&pdev->dev, माप(काष्ठा ts5500_sbc), GFP_KERNEL);
	अगर (!sbc) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	err = ts5500_detect_config(sbc);
	अगर (err)
		जाओ error;

	platक्रमm_set_drvdata(pdev, sbc);

	err = sysfs_create_group(&pdev->dev.kobj, &ts5500_attr_group);
	अगर (err)
		जाओ error;

	अगर (sbc->id == TS5500_PRODUCT_CODE) अणु
		ts5500_dio1_pdev.dev.parent = &pdev->dev;
		अगर (platक्रमm_device_रेजिस्टर(&ts5500_dio1_pdev))
			dev_warn(&pdev->dev, "DIO1 block registration failed\n");
		ts5500_dio2_pdev.dev.parent = &pdev->dev;
		अगर (platक्रमm_device_रेजिस्टर(&ts5500_dio2_pdev))
			dev_warn(&pdev->dev, "DIO2 block registration failed\n");
	पूर्ण

	अगर (led_classdev_रेजिस्टर(&pdev->dev, &ts5500_led_cdev))
		dev_warn(&pdev->dev, "LED registration failed\n");

	अगर (sbc->adc) अणु
		ts5500_adc_pdev.dev.parent = &pdev->dev;
		अगर (platक्रमm_device_रेजिस्टर(&ts5500_adc_pdev))
			dev_warn(&pdev->dev, "ADC registration failed\n");
	पूर्ण

	वापस 0;
error:
	platक्रमm_device_unरेजिस्टर(pdev);
	वापस err;
पूर्ण
device_initcall(ts5500_init);
