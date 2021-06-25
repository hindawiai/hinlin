<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST M48T59 RTC driver
 *
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * Author: Mark Zhan <rongkai.zhan@windriver.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/rtc/m48t59.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>

#अगर_अघोषित NO_IRQ
#घोषणा NO_IRQ	(-1)
#पूर्ण_अगर

#घोषणा M48T59_READ(reg) (pdata->पढ़ो_byte(dev, pdata->offset + reg))
#घोषणा M48T59_WRITE(val, reg) \
	(pdata->ग_लिखो_byte(dev, pdata->offset + reg, val))

#घोषणा M48T59_SET_BITS(mask, reg)	\
	M48T59_WRITE((M48T59_READ(reg) | (mask)), (reg))
#घोषणा M48T59_CLEAR_BITS(mask, reg)	\
	M48T59_WRITE((M48T59_READ(reg) & ~(mask)), (reg))

काष्ठा m48t59_निजी अणु
	व्योम __iomem *ioaddr;
	पूर्णांक irq;
	काष्ठा rtc_device *rtc;
	spinlock_t lock; /* serialize the NVRAM and RTC access */
पूर्ण;

/*
 * This is the generic access method when the chip is memory-mapped
 */
अटल व्योम
m48t59_mem_ग_लिखोb(काष्ठा device *dev, u32 ofs, u8 val)
अणु
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);

	ग_लिखोb(val, m48t59->ioaddr+ofs);
पूर्ण

अटल u8
m48t59_mem_पढ़ोb(काष्ठा device *dev, u32 ofs)
अणु
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);

	वापस पढ़ोb(m48t59->ioaddr+ofs);
पूर्ण

/*
 * NOTE: M48T59 only uses BCD mode
 */
अटल पूर्णांक m48t59_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u8 val;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the READ command */
	M48T59_SET_BITS(M48T59_CNTL_READ, M48T59_CNTL);

	पंचांग->पंचांग_year	= bcd2bin(M48T59_READ(M48T59_YEAR));
	/* पंचांग_mon is 0-11 */
	पंचांग->पंचांग_mon	= bcd2bin(M48T59_READ(M48T59_MONTH)) - 1;
	पंचांग->पंचांग_mday	= bcd2bin(M48T59_READ(M48T59_MDAY));

	val = M48T59_READ(M48T59_WDAY);
	अगर ((pdata->type == M48T59RTC_TYPE_M48T59) &&
	    (val & M48T59_WDAY_CEB) && (val & M48T59_WDAY_CB)) अणु
		dev_dbg(dev, "Century bit is enabled\n");
		पंचांग->पंचांग_year += 100;	/* one century */
	पूर्ण
#अगर_घोषित CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	पंचांग->पंचांग_year += 68;
#पूर्ण_अगर

	पंचांग->पंचांग_wday	= bcd2bin(val & 0x07);
	पंचांग->पंचांग_hour	= bcd2bin(M48T59_READ(M48T59_HOUR) & 0x3F);
	पंचांग->पंचांग_min	= bcd2bin(M48T59_READ(M48T59_MIN) & 0x7F);
	पंचांग->पंचांग_sec	= bcd2bin(M48T59_READ(M48T59_SEC) & 0x7F);

	/* Clear the READ bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_READ, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	dev_dbg(dev, "RTC read time %ptR\n", पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक m48t59_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u8 val = 0;
	पूर्णांक year = पंचांग->पंचांग_year;

#अगर_घोषित CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	year -= 68;
#पूर्ण_अगर

	dev_dbg(dev, "RTC set time %04d-%02d-%02d %02d/%02d/%02d\n",
		year + 1900, पंचांग->पंचांग_mon, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_min, पंचांग->पंचांग_sec);

	अगर (year < 0)
		वापस -EINVAL;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the WRITE command */
	M48T59_SET_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);

	M48T59_WRITE((bin2bcd(पंचांग->पंचांग_sec) & 0x7F), M48T59_SEC);
	M48T59_WRITE((bin2bcd(पंचांग->पंचांग_min) & 0x7F), M48T59_MIN);
	M48T59_WRITE((bin2bcd(पंचांग->पंचांग_hour) & 0x3F), M48T59_HOUR);
	M48T59_WRITE((bin2bcd(पंचांग->पंचांग_mday) & 0x3F), M48T59_MDAY);
	/* पंचांग_mon is 0-11 */
	M48T59_WRITE((bin2bcd(पंचांग->पंचांग_mon + 1) & 0x1F), M48T59_MONTH);
	M48T59_WRITE(bin2bcd(year % 100), M48T59_YEAR);

	अगर (pdata->type == M48T59RTC_TYPE_M48T59 && (year / 100))
		val = (M48T59_WDAY_CEB | M48T59_WDAY_CB);
	val |= (bin2bcd(पंचांग->पंचांग_wday) & 0x07);
	M48T59_WRITE(val, M48T59_WDAY);

	/* Clear the WRITE bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);
	वापस 0;
पूर्ण

/*
 * Read alarm समय and date in RTC
 */
अटल पूर्णांक m48t59_rtc_पढ़ोalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	अचिन्हित दीर्घ flags;
	u8 val;

	/* If no irq, we करोn't support ALARM */
	अगर (m48t59->irq == NO_IRQ)
		वापस -EIO;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the READ command */
	M48T59_SET_BITS(M48T59_CNTL_READ, M48T59_CNTL);

	पंचांग->पंचांग_year = bcd2bin(M48T59_READ(M48T59_YEAR));
#अगर_घोषित CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	पंचांग->पंचांग_year += 68;
#पूर्ण_अगर
	/* पंचांग_mon is 0-11 */
	पंचांग->पंचांग_mon = bcd2bin(M48T59_READ(M48T59_MONTH)) - 1;

	val = M48T59_READ(M48T59_WDAY);
	अगर ((val & M48T59_WDAY_CEB) && (val & M48T59_WDAY_CB))
		पंचांग->पंचांग_year += 100;	/* one century */

	पंचांग->पंचांग_mday = bcd2bin(M48T59_READ(M48T59_ALARM_DATE));
	पंचांग->पंचांग_hour = bcd2bin(M48T59_READ(M48T59_ALARM_HOUR));
	पंचांग->पंचांग_min = bcd2bin(M48T59_READ(M48T59_ALARM_MIN));
	पंचांग->पंचांग_sec = bcd2bin(M48T59_READ(M48T59_ALARM_SEC));

	/* Clear the READ bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_READ, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	dev_dbg(dev, "RTC read alarm time %ptR\n", पंचांग);
	वापस rtc_valid_पंचांग(पंचांग);
पूर्ण

/*
 * Set alarm समय and date in RTC
 */
अटल पूर्णांक m48t59_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	u8 mday, hour, min, sec;
	अचिन्हित दीर्घ flags;
	पूर्णांक year = पंचांग->पंचांग_year;

#अगर_घोषित CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	year -= 68;
#पूर्ण_अगर

	/* If no irq, we करोn't support ALARM */
	अगर (m48t59->irq == NO_IRQ)
		वापस -EIO;

	अगर (year < 0)
		वापस -EINVAL;

	/*
	 * 0xff means "always match"
	 */
	mday = पंचांग->पंचांग_mday;
	mday = (mday >= 1 && mday <= 31) ? bin2bcd(mday) : 0xff;
	अगर (mday == 0xff)
		mday = M48T59_READ(M48T59_MDAY);

	hour = पंचांग->पंचांग_hour;
	hour = (hour < 24) ? bin2bcd(hour) : 0x00;

	min = पंचांग->पंचांग_min;
	min = (min < 60) ? bin2bcd(min) : 0x00;

	sec = पंचांग->पंचांग_sec;
	sec = (sec < 60) ? bin2bcd(sec) : 0x00;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the WRITE command */
	M48T59_SET_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);

	M48T59_WRITE(mday, M48T59_ALARM_DATE);
	M48T59_WRITE(hour, M48T59_ALARM_HOUR);
	M48T59_WRITE(min, M48T59_ALARM_MIN);
	M48T59_WRITE(sec, M48T59_ALARM_SEC);

	/* Clear the WRITE bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	dev_dbg(dev, "RTC set alarm time %04d-%02d-%02d %02d/%02d/%02d\n",
		year + 1900, पंचांग->पंचांग_mon, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_min, पंचांग->पंचांग_sec);
	वापस 0;
पूर्ण

/*
 * Handle commands from user-space
 */
अटल पूर्णांक m48t59_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m48t59->lock, flags);
	अगर (enabled)
		M48T59_WRITE(M48T59_INTR_AFE, M48T59_INTR);
	अन्यथा
		M48T59_WRITE(0x00, M48T59_INTR);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक m48t59_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u8 val;

	spin_lock_irqsave(&m48t59->lock, flags);
	val = M48T59_READ(M48T59_FLAGS);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	seq_म_लिखो(seq, "battery\t\t: %s\n",
		 (val & M48T59_FLAGS_BF) ? "low" : "normal");
	वापस 0;
पूर्ण

/*
 * IRQ handler क्रम the RTC
 */
अटल irqवापस_t m48t59_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा device *dev = (काष्ठा device *)dev_id;
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा m48t59_निजी *m48t59 = dev_get_drvdata(dev);
	u8 event;

	spin_lock(&m48t59->lock);
	event = M48T59_READ(M48T59_FLAGS);
	spin_unlock(&m48t59->lock);

	अगर (event & M48T59_FLAGS_AF) अणु
		rtc_update_irq(m48t59->rtc, 1, (RTC_AF | RTC_IRQF));
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops m48t59_rtc_ops = अणु
	.पढ़ो_समय	= m48t59_rtc_पढ़ो_समय,
	.set_समय	= m48t59_rtc_set_समय,
	.पढ़ो_alarm	= m48t59_rtc_पढ़ोalarm,
	.set_alarm	= m48t59_rtc_setalarm,
	.proc		= m48t59_rtc_proc,
	.alarm_irq_enable = m48t59_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक m48t59_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार size)
अणु
	काष्ठा platक्रमm_device *pdev = priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा m48t59_निजी *m48t59 = platक्रमm_get_drvdata(pdev);
	sमाप_प्रकार cnt = 0;
	अचिन्हित दीर्घ flags;
	u8 *buf = val;

	spin_lock_irqsave(&m48t59->lock, flags);

	क्रम (; cnt < size; cnt++)
		*buf++ = M48T59_READ(cnt);

	spin_unlock_irqrestore(&m48t59->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक m48t59_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार size)
अणु
	काष्ठा platक्रमm_device *pdev = priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा m48t59_निजी *m48t59 = platक्रमm_get_drvdata(pdev);
	sमाप_प्रकार cnt = 0;
	अचिन्हित दीर्घ flags;
	u8 *buf = val;

	spin_lock_irqsave(&m48t59->lock, flags);

	क्रम (; cnt < size; cnt++)
		M48T59_WRITE(*buf++, cnt);

	spin_unlock_irqrestore(&m48t59->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक m48t59_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा m48t59_plat_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा m48t59_निजी *m48t59 = शून्य;
	काष्ठा resource *res;
	पूर्णांक ret = -ENOMEM;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "m48t59-",
		.word_size = 1,
		.stride = 1,
		.reg_पढ़ो = m48t59_nvram_पढ़ो,
		.reg_ग_लिखो = m48t59_nvram_ग_लिखो,
		.priv = pdev,
	पूर्ण;

	/* This chip could be memory-mapped or I/O-mapped */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
		अगर (!res)
			वापस -EINVAL;
	पूर्ण

	अगर (res->flags & IORESOURCE_IO) अणु
		/* If we are I/O-mapped, the platक्रमm should provide
		 * the operations accessing chip रेजिस्टरs.
		 */
		अगर (!pdata || !pdata->ग_लिखो_byte || !pdata->पढ़ो_byte)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (res->flags & IORESOURCE_MEM) अणु
		/* we are memory-mapped */
		अगर (!pdata) अणु
			pdata = devm_kzalloc(&pdev->dev, माप(*pdata),
						GFP_KERNEL);
			अगर (!pdata)
				वापस -ENOMEM;
			/* Ensure we only kदो_स्मृति platक्रमm data once */
			pdev->dev.platक्रमm_data = pdata;
		पूर्ण
		अगर (!pdata->type)
			pdata->type = M48T59RTC_TYPE_M48T59;

		/* Try to use the generic memory पढ़ो/ग_लिखो ops */
		अगर (!pdata->ग_लिखो_byte)
			pdata->ग_लिखो_byte = m48t59_mem_ग_लिखोb;
		अगर (!pdata->पढ़ो_byte)
			pdata->पढ़ो_byte = m48t59_mem_पढ़ोb;
	पूर्ण

	m48t59 = devm_kzalloc(&pdev->dev, माप(*m48t59), GFP_KERNEL);
	अगर (!m48t59)
		वापस -ENOMEM;

	m48t59->ioaddr = pdata->ioaddr;

	अगर (!m48t59->ioaddr) अणु
		/* ioaddr not mapped बाह्यally */
		m48t59->ioaddr = devm_ioremap(&pdev->dev, res->start,
						resource_size(res));
		अगर (!m48t59->ioaddr)
			वापस ret;
	पूर्ण

	/* Try to get irq number. We also can work in
	 * the mode without IRQ.
	 */
	m48t59->irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (m48t59->irq <= 0)
		m48t59->irq = NO_IRQ;

	अगर (m48t59->irq != NO_IRQ) अणु
		ret = devm_request_irq(&pdev->dev, m48t59->irq,
				m48t59_rtc_पूर्णांकerrupt, IRQF_SHARED,
				"rtc-m48t59", &pdev->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	m48t59->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(m48t59->rtc))
		वापस PTR_ERR(m48t59->rtc);

	चयन (pdata->type) अणु
	हाल M48T59RTC_TYPE_M48T59:
		pdata->offset = 0x1ff0;
		अवरोध;
	हाल M48T59RTC_TYPE_M48T02:
		clear_bit(RTC_FEATURE_ALARM, m48t59->rtc->features);
		pdata->offset = 0x7f0;
		अवरोध;
	हाल M48T59RTC_TYPE_M48T08:
		clear_bit(RTC_FEATURE_ALARM, m48t59->rtc->features);
		pdata->offset = 0x1ff0;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown RTC type\n");
		वापस -ENODEV;
	पूर्ण

	spin_lock_init(&m48t59->lock);
	platक्रमm_set_drvdata(pdev, m48t59);

	m48t59->rtc->ops = &m48t59_rtc_ops;

	nvmem_cfg.size = pdata->offset;
	ret = devm_rtc_nvmem_रेजिस्टर(m48t59->rtc, &nvmem_cfg);
	अगर (ret)
		वापस ret;

	ret = devm_rtc_रेजिस्टर_device(m48t59->rtc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:rtc-m48t59");

अटल काष्ठा platक्रमm_driver m48t59_rtc_driver = अणु
	.driver		= अणु
		.name	= "rtc-m48t59",
	पूर्ण,
	.probe		= m48t59_rtc_probe,
पूर्ण;

module_platक्रमm_driver(m48t59_rtc_driver);

MODULE_AUTHOR("Mark Zhan <rongkai.zhan@windriver.com>");
MODULE_DESCRIPTION("M48T59/M48T02/M48T08 RTC driver");
MODULE_LICENSE("GPL");
