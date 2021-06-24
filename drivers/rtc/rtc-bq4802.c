<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* rtc-bq4802.c: TI BQ4802 RTC driver.
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>

MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_DESCRIPTION("TI BQ4802 RTC driver");
MODULE_LICENSE("GPL");

काष्ठा bq4802 अणु
	व्योम __iomem		*regs;
	अचिन्हित दीर्घ		ioport;
	काष्ठा rtc_device	*rtc;
	spinlock_t		lock;
	काष्ठा resource		*r;
	u8 (*पढ़ो)(काष्ठा bq4802 *, पूर्णांक);
	व्योम (*ग_लिखो)(काष्ठा bq4802 *, पूर्णांक, u8);
पूर्ण;

अटल u8 bq4802_पढ़ो_io(काष्ठा bq4802 *p, पूर्णांक off)
अणु
	वापस inb(p->ioport + off);
पूर्ण

अटल व्योम bq4802_ग_लिखो_io(काष्ठा bq4802 *p, पूर्णांक off, u8 val)
अणु
	outb(val, p->ioport + off);
पूर्ण

अटल u8 bq4802_पढ़ो_mem(काष्ठा bq4802 *p, पूर्णांक off)
अणु
	वापस पढ़ोb(p->regs + off);
पूर्ण

अटल व्योम bq4802_ग_लिखो_mem(काष्ठा bq4802 *p, पूर्णांक off, u8 val)
अणु
	ग_लिखोb(val, p->regs + off);
पूर्ण

अटल पूर्णांक bq4802_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा bq4802 *p = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक century;
	u8 val;

	spin_lock_irqsave(&p->lock, flags);

	val = p->पढ़ो(p, 0x0e);
	p->ग_लिखो(p, 0xe, val | 0x08);

	पंचांग->पंचांग_sec = p->पढ़ो(p, 0x00);
	पंचांग->पंचांग_min = p->पढ़ो(p, 0x02);
	पंचांग->पंचांग_hour = p->पढ़ो(p, 0x04);
	पंचांग->पंचांग_mday = p->पढ़ो(p, 0x06);
	पंचांग->पंचांग_mon = p->पढ़ो(p, 0x09);
	पंचांग->पंचांग_year = p->पढ़ो(p, 0x0a);
	पंचांग->पंचांग_wday = p->पढ़ो(p, 0x08);
	century = p->पढ़ो(p, 0x0f);

	p->ग_लिखो(p, 0x0e, val);

	spin_unlock_irqrestore(&p->lock, flags);

	पंचांग->पंचांग_sec = bcd2bin(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bcd2bin(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bcd2bin(पंचांग->पंचांग_hour);
	पंचांग->पंचांग_mday = bcd2bin(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bcd2bin(पंचांग->पंचांग_mon);
	पंचांग->पंचांग_year = bcd2bin(पंचांग->पंचांग_year);
	पंचांग->पंचांग_wday = bcd2bin(पंचांग->पंचांग_wday);
	century = bcd2bin(century);

	पंचांग->पंचांग_year += (century * 100);
	पंचांग->पंचांग_year -= 1900;

	पंचांग->पंचांग_mon--;

	वापस 0;
पूर्ण

अटल पूर्णांक bq4802_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा bq4802 *p = dev_get_drvdata(dev);
	u8 sec, min, hrs, day, mon, yrs, century, val;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक year;

	year = पंचांग->पंचांग_year + 1900;
	century = year / 100;
	yrs = year % 100;

	mon = पंचांग->पंचांग_mon + 1;   /* पंचांग_mon starts at zero */
	day = पंचांग->पंचांग_mday;
	hrs = पंचांग->पंचांग_hour;
	min = पंचांग->पंचांग_min;
	sec = पंचांग->पंचांग_sec;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hrs = bin2bcd(hrs);
	day = bin2bcd(day);
	mon = bin2bcd(mon);
	yrs = bin2bcd(yrs);
	century = bin2bcd(century);

	spin_lock_irqsave(&p->lock, flags);

	val = p->पढ़ो(p, 0x0e);
	p->ग_लिखो(p, 0x0e, val | 0x08);

	p->ग_लिखो(p, 0x00, sec);
	p->ग_लिखो(p, 0x02, min);
	p->ग_लिखो(p, 0x04, hrs);
	p->ग_लिखो(p, 0x06, day);
	p->ग_लिखो(p, 0x09, mon);
	p->ग_लिखो(p, 0x0a, yrs);
	p->ग_लिखो(p, 0x0f, century);

	p->ग_लिखो(p, 0x0e, val);

	spin_unlock_irqrestore(&p->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops bq4802_ops = अणु
	.पढ़ो_समय	= bq4802_पढ़ो_समय,
	.set_समय	= bq4802_set_समय,
पूर्ण;

अटल पूर्णांक bq4802_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bq4802 *p = devm_kzalloc(&pdev->dev, माप(*p), GFP_KERNEL);
	पूर्णांक err = -ENOMEM;

	अगर (!p)
		जाओ out;

	spin_lock_init(&p->lock);

	p->r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!p->r) अणु
		p->r = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
		err = -EINVAL;
		अगर (!p->r)
			जाओ out;
	पूर्ण
	अगर (p->r->flags & IORESOURCE_IO) अणु
		p->ioport = p->r->start;
		p->पढ़ो = bq4802_पढ़ो_io;
		p->ग_लिखो = bq4802_ग_लिखो_io;
	पूर्ण अन्यथा अगर (p->r->flags & IORESOURCE_MEM) अणु
		p->regs = devm_ioremap(&pdev->dev, p->r->start,
					resource_size(p->r));
		अगर (!p->regs)अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		p->पढ़ो = bq4802_पढ़ो_mem;
		p->ग_लिखो = bq4802_ग_लिखो_mem;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	platक्रमm_set_drvdata(pdev, p);

	p->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "bq4802",
					&bq4802_ops, THIS_MODULE);
	अगर (IS_ERR(p->rtc)) अणु
		err = PTR_ERR(p->rtc);
		जाओ out;
	पूर्ण

	err = 0;
out:
	वापस err;

पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:rtc-bq4802");

अटल काष्ठा platक्रमm_driver bq4802_driver = अणु
	.driver		= अणु
		.name	= "rtc-bq4802",
	पूर्ण,
	.probe		= bq4802_probe,
पूर्ण;

module_platक्रमm_driver(bq4802_driver);
