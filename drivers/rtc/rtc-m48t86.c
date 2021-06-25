<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST M48T86 / Dallas DS12887 RTC driver
 * Copyright (c) 2006 Tower Technologies
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * This drivers only supports the घड़ी running in BCD and 24H mode.
 * If it will be ever adapted to binary and 12H mode, care must be taken
 * to not पूर्णांकroduce bugs.
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcd.h>
#समावेश <linux/पन.स>

#घोषणा M48T86_SEC		0x00
#घोषणा M48T86_SECALRM		0x01
#घोषणा M48T86_MIN		0x02
#घोषणा M48T86_MINALRM		0x03
#घोषणा M48T86_HOUR		0x04
#घोषणा M48T86_HOURALRM		0x05
#घोषणा M48T86_DOW		0x06 /* 1 = sunday */
#घोषणा M48T86_DOM		0x07
#घोषणा M48T86_MONTH		0x08 /* 1 - 12 */
#घोषणा M48T86_YEAR		0x09 /* 0 - 99 */
#घोषणा M48T86_A		0x0a
#घोषणा M48T86_B		0x0b
#घोषणा M48T86_B_SET		BIT(7)
#घोषणा M48T86_B_DM		BIT(2)
#घोषणा M48T86_B_H24		BIT(1)
#घोषणा M48T86_C		0x0c
#घोषणा M48T86_D		0x0d
#घोषणा M48T86_D_VRT		BIT(7)
#घोषणा M48T86_NVRAM(x)		(0x0e + (x))
#घोषणा M48T86_NVRAM_LEN	114

काष्ठा m48t86_rtc_info अणु
	व्योम __iomem *index_reg;
	व्योम __iomem *data_reg;
	काष्ठा rtc_device *rtc;
पूर्ण;

अटल अचिन्हित अक्षर m48t86_पढ़ोb(काष्ठा device *dev, अचिन्हित दीर्घ addr)
अणु
	काष्ठा m48t86_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर value;

	ग_लिखोb(addr, info->index_reg);
	value = पढ़ोb(info->data_reg);

	वापस value;
पूर्ण

अटल व्योम m48t86_ग_लिखोb(काष्ठा device *dev,
			  अचिन्हित अक्षर value, अचिन्हित दीर्घ addr)
अणु
	काष्ठा m48t86_rtc_info *info = dev_get_drvdata(dev);

	ग_लिखोb(addr, info->index_reg);
	ग_लिखोb(value, info->data_reg);
पूर्ण

अटल पूर्णांक m48t86_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर reg;

	reg = m48t86_पढ़ोb(dev, M48T86_B);

	अगर (reg & M48T86_B_DM) अणु
		/* data (binary) mode */
		पंचांग->पंचांग_sec	= m48t86_पढ़ोb(dev, M48T86_SEC);
		पंचांग->पंचांग_min	= m48t86_पढ़ोb(dev, M48T86_MIN);
		पंचांग->पंचांग_hour	= m48t86_पढ़ोb(dev, M48T86_HOUR) & 0x3f;
		पंचांग->पंचांग_mday	= m48t86_पढ़ोb(dev, M48T86_DOM);
		/* पंचांग_mon is 0-11 */
		पंचांग->पंचांग_mon	= m48t86_पढ़ोb(dev, M48T86_MONTH) - 1;
		पंचांग->पंचांग_year	= m48t86_पढ़ोb(dev, M48T86_YEAR) + 100;
		पंचांग->पंचांग_wday	= m48t86_पढ़ोb(dev, M48T86_DOW);
	पूर्ण अन्यथा अणु
		/* bcd mode */
		पंचांग->पंचांग_sec	= bcd2bin(m48t86_पढ़ोb(dev, M48T86_SEC));
		पंचांग->पंचांग_min	= bcd2bin(m48t86_पढ़ोb(dev, M48T86_MIN));
		पंचांग->पंचांग_hour	= bcd2bin(m48t86_पढ़ोb(dev, M48T86_HOUR) &
					  0x3f);
		पंचांग->पंचांग_mday	= bcd2bin(m48t86_पढ़ोb(dev, M48T86_DOM));
		/* पंचांग_mon is 0-11 */
		पंचांग->पंचांग_mon	= bcd2bin(m48t86_पढ़ोb(dev, M48T86_MONTH)) - 1;
		पंचांग->पंचांग_year	= bcd2bin(m48t86_पढ़ोb(dev, M48T86_YEAR)) + 100;
		पंचांग->पंचांग_wday	= bcd2bin(m48t86_पढ़ोb(dev, M48T86_DOW));
	पूर्ण

	/* correct the hour अगर the घड़ी is in 12h mode */
	अगर (!(reg & M48T86_B_H24))
		अगर (m48t86_पढ़ोb(dev, M48T86_HOUR) & 0x80)
			पंचांग->पंचांग_hour += 12;

	वापस 0;
पूर्ण

अटल पूर्णांक m48t86_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर reg;

	reg = m48t86_पढ़ोb(dev, M48T86_B);

	/* update flag and 24h mode */
	reg |= M48T86_B_SET | M48T86_B_H24;
	m48t86_ग_लिखोb(dev, reg, M48T86_B);

	अगर (reg & M48T86_B_DM) अणु
		/* data (binary) mode */
		m48t86_ग_लिखोb(dev, पंचांग->पंचांग_sec, M48T86_SEC);
		m48t86_ग_लिखोb(dev, पंचांग->पंचांग_min, M48T86_MIN);
		m48t86_ग_लिखोb(dev, पंचांग->पंचांग_hour, M48T86_HOUR);
		m48t86_ग_लिखोb(dev, पंचांग->पंचांग_mday, M48T86_DOM);
		m48t86_ग_लिखोb(dev, पंचांग->पंचांग_mon + 1, M48T86_MONTH);
		m48t86_ग_लिखोb(dev, पंचांग->पंचांग_year % 100, M48T86_YEAR);
		m48t86_ग_लिखोb(dev, पंचांग->पंचांग_wday, M48T86_DOW);
	पूर्ण अन्यथा अणु
		/* bcd mode */
		m48t86_ग_लिखोb(dev, bin2bcd(पंचांग->पंचांग_sec), M48T86_SEC);
		m48t86_ग_लिखोb(dev, bin2bcd(पंचांग->पंचांग_min), M48T86_MIN);
		m48t86_ग_लिखोb(dev, bin2bcd(पंचांग->पंचांग_hour), M48T86_HOUR);
		m48t86_ग_लिखोb(dev, bin2bcd(पंचांग->पंचांग_mday), M48T86_DOM);
		m48t86_ग_लिखोb(dev, bin2bcd(पंचांग->पंचांग_mon + 1), M48T86_MONTH);
		m48t86_ग_लिखोb(dev, bin2bcd(पंचांग->पंचांग_year % 100), M48T86_YEAR);
		m48t86_ग_लिखोb(dev, bin2bcd(पंचांग->पंचांग_wday), M48T86_DOW);
	पूर्ण

	/* update ended */
	reg &= ~M48T86_B_SET;
	m48t86_ग_लिखोb(dev, reg, M48T86_B);

	वापस 0;
पूर्ण

अटल पूर्णांक m48t86_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	अचिन्हित अक्षर reg;

	reg = m48t86_पढ़ोb(dev, M48T86_B);

	seq_म_लिखो(seq, "mode\t\t: %s\n",
		   (reg & M48T86_B_DM) ? "binary" : "bcd");

	reg = m48t86_पढ़ोb(dev, M48T86_D);

	seq_म_लिखो(seq, "battery\t\t: %s\n",
		   (reg & M48T86_D_VRT) ? "ok" : "exhausted");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops m48t86_rtc_ops = अणु
	.पढ़ो_समय	= m48t86_rtc_पढ़ो_समय,
	.set_समय	= m48t86_rtc_set_समय,
	.proc		= m48t86_rtc_proc,
पूर्ण;

अटल पूर्णांक m48t86_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *buf,
			     माप_प्रकार count)
अणु
	काष्ठा device *dev = priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		((u8 *)buf)[i] = m48t86_पढ़ोb(dev, M48T86_NVRAM(off + i));

	वापस 0;
पूर्ण

अटल पूर्णांक m48t86_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *buf,
			      माप_प्रकार count)
अणु
	काष्ठा device *dev = priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		m48t86_ग_लिखोb(dev, ((u8 *)buf)[i], M48T86_NVRAM(off + i));

	वापस 0;
पूर्ण

/*
 * The RTC is an optional feature at purchase समय on some Technologic Systems
 * boards. Verअगरy that it actually exists by checking अगर the last two bytes
 * of the NVRAM can be changed.
 *
 * This is based on the method used in their rtc7800.c example.
 */
अटल bool m48t86_verअगरy_chip(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक offset0 = M48T86_NVRAM(M48T86_NVRAM_LEN - 2);
	अचिन्हित पूर्णांक offset1 = M48T86_NVRAM(M48T86_NVRAM_LEN - 1);
	अचिन्हित अक्षर पंचांगp0, पंचांगp1;

	पंचांगp0 = m48t86_पढ़ोb(&pdev->dev, offset0);
	पंचांगp1 = m48t86_पढ़ोb(&pdev->dev, offset1);

	m48t86_ग_लिखोb(&pdev->dev, 0x00, offset0);
	m48t86_ग_लिखोb(&pdev->dev, 0x55, offset1);
	अगर (m48t86_पढ़ोb(&pdev->dev, offset1) == 0x55) अणु
		m48t86_ग_लिखोb(&pdev->dev, 0xaa, offset1);
		अगर (m48t86_पढ़ोb(&pdev->dev, offset1) == 0xaa &&
		    m48t86_पढ़ोb(&pdev->dev, offset0) == 0x00) अणु
			m48t86_ग_लिखोb(&pdev->dev, पंचांगp0, offset0);
			m48t86_ग_लिखोb(&pdev->dev, पंचांगp1, offset1);

			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक m48t86_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा m48t86_rtc_info *info;
	अचिन्हित अक्षर reg;
	पूर्णांक err;
	काष्ठा nvmem_config m48t86_nvmem_cfg = अणु
		.name = "m48t86_nvram",
		.word_size = 1,
		.stride = 1,
		.size = M48T86_NVRAM_LEN,
		.reg_पढ़ो = m48t86_nvram_पढ़ो,
		.reg_ग_लिखो = m48t86_nvram_ग_लिखो,
		.priv = &pdev->dev,
	पूर्ण;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->index_reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->index_reg))
		वापस PTR_ERR(info->index_reg);

	info->data_reg = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(info->data_reg))
		वापस PTR_ERR(info->data_reg);

	dev_set_drvdata(&pdev->dev, info);

	अगर (!m48t86_verअगरy_chip(pdev)) अणु
		dev_info(&pdev->dev, "RTC not present\n");
		वापस -ENODEV;
	पूर्ण

	info->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(info->rtc))
		वापस PTR_ERR(info->rtc);

	info->rtc->ops = &m48t86_rtc_ops;

	err = devm_rtc_रेजिस्टर_device(info->rtc);
	अगर (err)
		वापस err;

	devm_rtc_nvmem_रेजिस्टर(info->rtc, &m48t86_nvmem_cfg);

	/* पढ़ो battery status */
	reg = m48t86_पढ़ोb(&pdev->dev, M48T86_D);
	dev_info(&pdev->dev, "battery %s\n",
		 (reg & M48T86_D_VRT) ? "ok" : "exhausted");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver m48t86_rtc_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "rtc-m48t86",
	पूर्ण,
	.probe		= m48t86_rtc_probe,
पूर्ण;

module_platक्रमm_driver(m48t86_rtc_platक्रमm_driver);

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("M48T86 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-m48t86");
