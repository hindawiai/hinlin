<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DS1286 Real Time Clock पूर्णांकerface क्रम Linux
 *
 * Copyright (C) 1998, 1999, 2000 Ralf Baechle
 * Copyright (C) 2008 Thomas Bogenकरोerfer
 *
 * Based on code written by Paul Gorपंचांगaker.
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc/ds1286.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

काष्ठा ds1286_priv अणु
	काष्ठा rtc_device *rtc;
	u32 __iomem *rtcregs;
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत u8 ds1286_rtc_पढ़ो(काष्ठा ds1286_priv *priv, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(&priv->rtcregs[reg]) & 0xff;
पूर्ण

अटल अंतरभूत व्योम ds1286_rtc_ग_लिखो(काष्ठा ds1286_priv *priv, u8 data, पूर्णांक reg)
अणु
	__raw_ग_लिखोl(data, &priv->rtcregs[reg]);
पूर्ण


अटल पूर्णांक ds1286_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds1286_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;

	/* Allow or mask alarm पूर्णांकerrupts */
	spin_lock_irqsave(&priv->lock, flags);
	val = ds1286_rtc_पढ़ो(priv, RTC_CMD);
	अगर (enabled)
		val &=  ~RTC_TDM;
	अन्यथा
		val |=  RTC_TDM;
	ds1286_rtc_ग_लिखो(priv, val, RTC_CMD);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RTC_INTF_DEV

अटल पूर्णांक ds1286_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ds1286_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;

	चयन (cmd) अणु
	हाल RTC_WIE_OFF:
		/* Mask watchकरोg पूर्णांक. enab. bit	*/
		spin_lock_irqsave(&priv->lock, flags);
		val = ds1286_rtc_पढ़ो(priv, RTC_CMD);
		val |= RTC_WAM;
		ds1286_rtc_ग_लिखो(priv, val, RTC_CMD);
		spin_unlock_irqrestore(&priv->lock, flags);
		अवरोध;
	हाल RTC_WIE_ON:
		/* Allow watchकरोg पूर्णांकerrupts.	*/
		spin_lock_irqsave(&priv->lock, flags);
		val = ds1286_rtc_पढ़ो(priv, RTC_CMD);
		val &= ~RTC_WAM;
		ds1286_rtc_ग_लिखो(priv, val, RTC_CMD);
		spin_unlock_irqrestore(&priv->lock, flags);
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

#अन्यथा
#घोषणा ds1286_ioctl    शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS

अटल पूर्णांक ds1286_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा ds1286_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर month, cmd, amode;
	स्थिर अक्षर *s;

	month = ds1286_rtc_पढ़ो(priv, RTC_MONTH);
	seq_म_लिखो(seq,
		   "oscillator\t: %s\n"
		   "square_wave\t: %s\n",
		   (month & RTC_EOSC) ? "disabled" : "enabled",
		   (month & RTC_ESQW) ? "disabled" : "enabled");

	amode = ((ds1286_rtc_पढ़ो(priv, RTC_MINUTES_ALARM) & 0x80) >> 5) |
		((ds1286_rtc_पढ़ो(priv, RTC_HOURS_ALARM) & 0x80) >> 6) |
		((ds1286_rtc_पढ़ो(priv, RTC_DAY_ALARM) & 0x80) >> 7);
	चयन (amode) अणु
	हाल 7:
		s = "each minute";
		अवरोध;
	हाल 3:
		s = "minutes match";
		अवरोध;
	हाल 1:
		s = "hours and minutes match";
		अवरोध;
	हाल 0:
		s = "days, hours and minutes match";
		अवरोध;
	शेष:
		s = "invalid";
		अवरोध;
	पूर्ण
	seq_म_लिखो(seq, "alarm_mode\t: %s\n", s);

	cmd = ds1286_rtc_पढ़ो(priv, RTC_CMD);
	seq_म_लिखो(seq,
		   "alarm_enable\t: %s\n"
		   "wdog_alarm\t: %s\n"
		   "alarm_mask\t: %s\n"
		   "wdog_alarm_mask\t: %s\n"
		   "interrupt_mode\t: %s\n"
		   "INTB_mode\t: %s_active\n"
		   "interrupt_pins\t: %s\n",
		   (cmd & RTC_TDF) ? "yes" : "no",
		   (cmd & RTC_WAF) ? "yes" : "no",
		   (cmd & RTC_TDM) ? "disabled" : "enabled",
		   (cmd & RTC_WAM) ? "disabled" : "enabled",
		   (cmd & RTC_PU_LVL) ? "pulse" : "level",
		   (cmd & RTC_IBH_LO) ? "low" : "high",
		   (cmd & RTC_IPSW) ? "unswapped" : "swapped");
	वापस 0;
पूर्ण

#अन्यथा
#घोषणा ds1286_proc     शून्य
#पूर्ण_अगर

अटल पूर्णांक ds1286_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ds1286_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर save_control;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ uip_watchकरोg = jअगरfies;

	/*
	 * पढ़ो RTC once any update in progress is करोne. The update
	 * can take just over 2ms. We रुको 10 to 20ms. There is no need to
	 * to poll-रुको (up to 1s - eeccch) क्रम the falling edge of RTC_UIP.
	 * If you need to know *exactly* when a second has started, enable
	 * periodic update complete पूर्णांकerrupts, (via ioctl) and then
	 * immediately पढ़ो /dev/rtc which will block until you get the IRQ.
	 * Once the पढ़ो clears, पढ़ो the RTC समय (again via ioctl). Easy.
	 */

	अगर (ds1286_rtc_पढ़ो(priv, RTC_CMD) & RTC_TE)
		जबतक (समय_beक्रमe(jअगरfies, uip_watchकरोg + 2*HZ/100))
			barrier();

	/*
	 * Only the values that we पढ़ो from the RTC are set. We leave
	 * पंचांग_wday, पंचांग_yday and पंचांग_isdst untouched. Even though the
	 * RTC has RTC_DAY_OF_WEEK, we ignore it, as it is only updated
	 * by the RTC when initially set to a non-zero value.
	 */
	spin_lock_irqsave(&priv->lock, flags);
	save_control = ds1286_rtc_पढ़ो(priv, RTC_CMD);
	ds1286_rtc_ग_लिखो(priv, (save_control|RTC_TE), RTC_CMD);

	पंचांग->पंचांग_sec = ds1286_rtc_पढ़ो(priv, RTC_SECONDS);
	पंचांग->पंचांग_min = ds1286_rtc_पढ़ो(priv, RTC_MINUTES);
	पंचांग->पंचांग_hour = ds1286_rtc_पढ़ो(priv, RTC_HOURS) & 0x3f;
	पंचांग->पंचांग_mday = ds1286_rtc_पढ़ो(priv, RTC_DATE);
	पंचांग->पंचांग_mon = ds1286_rtc_पढ़ो(priv, RTC_MONTH) & 0x1f;
	पंचांग->पंचांग_year = ds1286_rtc_पढ़ो(priv, RTC_YEAR);

	ds1286_rtc_ग_लिखो(priv, save_control, RTC_CMD);
	spin_unlock_irqrestore(&priv->lock, flags);

	पंचांग->पंचांग_sec = bcd2bin(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bcd2bin(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bcd2bin(पंचांग->पंचांग_hour);
	पंचांग->पंचांग_mday = bcd2bin(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bcd2bin(पंचांग->पंचांग_mon);
	पंचांग->पंचांग_year = bcd2bin(पंचांग->पंचांग_year);

	/*
	 * Account क्रम dअगरferences between how the RTC uses the values
	 * and how they are defined in a काष्ठा rtc_समय;
	 */
	अगर (पंचांग->पंचांग_year < 45)
		पंचांग->पंचांग_year += 30;
	पंचांग->पंचांग_year += 40;
	अगर (पंचांग->पंचांग_year < 70)
		पंचांग->पंचांग_year += 100;

	पंचांग->पंचांग_mon--;

	वापस 0;
पूर्ण

अटल पूर्णांक ds1286_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ds1286_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर mon, day, hrs, min, sec;
	अचिन्हित अक्षर save_control;
	अचिन्हित पूर्णांक yrs;
	अचिन्हित दीर्घ flags;

	yrs = पंचांग->पंचांग_year + 1900;
	mon = पंचांग->पंचांग_mon + 1;   /* पंचांग_mon starts at zero */
	day = पंचांग->पंचांग_mday;
	hrs = पंचांग->पंचांग_hour;
	min = पंचांग->पंचांग_min;
	sec = पंचांग->पंचांग_sec;

	अगर (yrs < 1970)
		वापस -EINVAL;

	yrs -= 1940;
	अगर (yrs > 255)    /* They are अचिन्हित */
		वापस -EINVAL;

	अगर (yrs >= 100)
		yrs -= 100;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hrs = bin2bcd(hrs);
	day = bin2bcd(day);
	mon = bin2bcd(mon);
	yrs = bin2bcd(yrs);

	spin_lock_irqsave(&priv->lock, flags);
	save_control = ds1286_rtc_पढ़ो(priv, RTC_CMD);
	ds1286_rtc_ग_लिखो(priv, (save_control|RTC_TE), RTC_CMD);

	ds1286_rtc_ग_लिखो(priv, yrs, RTC_YEAR);
	ds1286_rtc_ग_लिखो(priv, mon, RTC_MONTH);
	ds1286_rtc_ग_लिखो(priv, day, RTC_DATE);
	ds1286_rtc_ग_लिखो(priv, hrs, RTC_HOURS);
	ds1286_rtc_ग_लिखो(priv, min, RTC_MINUTES);
	ds1286_rtc_ग_लिखो(priv, sec, RTC_SECONDS);
	ds1286_rtc_ग_लिखो(priv, 0, RTC_HUNDREDTH_SECOND);

	ds1286_rtc_ग_लिखो(priv, save_control, RTC_CMD);
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1286_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा ds1286_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	/*
	 * Only the values that we पढ़ो from the RTC are set. That
	 * means only पंचांग_wday, पंचांग_hour, पंचांग_min.
	 */
	spin_lock_irqsave(&priv->lock, flags);
	alm->समय.पंचांग_min = ds1286_rtc_पढ़ो(priv, RTC_MINUTES_ALARM) & 0x7f;
	alm->समय.पंचांग_hour = ds1286_rtc_पढ़ो(priv, RTC_HOURS_ALARM)  & 0x1f;
	alm->समय.पंचांग_wday = ds1286_rtc_पढ़ो(priv, RTC_DAY_ALARM)    & 0x07;
	ds1286_rtc_पढ़ो(priv, RTC_CMD);
	spin_unlock_irqrestore(&priv->lock, flags);

	alm->समय.पंचांग_min = bcd2bin(alm->समय.पंचांग_min);
	alm->समय.पंचांग_hour = bcd2bin(alm->समय.पंचांग_hour);
	alm->समय.पंचांग_sec = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ds1286_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा ds1286_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर hrs, min, sec;

	hrs = alm->समय.पंचांग_hour;
	min = alm->समय.पंचांग_min;
	sec = alm->समय.पंचांग_sec;

	अगर (hrs >= 24)
		hrs = 0xff;

	अगर (min >= 60)
		min = 0xff;

	अगर (sec != 0)
		वापस -EINVAL;

	min = bin2bcd(min);
	hrs = bin2bcd(hrs);

	spin_lock(&priv->lock);
	ds1286_rtc_ग_लिखो(priv, hrs, RTC_HOURS_ALARM);
	ds1286_rtc_ग_लिखो(priv, min, RTC_MINUTES_ALARM);
	spin_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1286_ops = अणु
	.ioctl		= ds1286_ioctl,
	.proc		= ds1286_proc,
	.पढ़ो_समय	= ds1286_पढ़ो_समय,
	.set_समय	= ds1286_set_समय,
	.पढ़ो_alarm	= ds1286_पढ़ो_alarm,
	.set_alarm	= ds1286_set_alarm,
	.alarm_irq_enable = ds1286_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक ds1286_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;
	काष्ठा ds1286_priv *priv;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा ds1286_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->rtcregs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->rtcregs))
		वापस PTR_ERR(priv->rtcregs);

	spin_lock_init(&priv->lock);
	platक्रमm_set_drvdata(pdev, priv);
	rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "ds1286", &ds1286_ops,
					THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);
	priv->rtc = rtc;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ds1286_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "rtc-ds1286",
	पूर्ण,
	.probe		= ds1286_probe,
पूर्ण;

module_platक्रमm_driver(ds1286_platक्रमm_driver);

MODULE_AUTHOR("Thomas Bogendoerfer <tsbogend@alpha.franken.de>");
MODULE_DESCRIPTION("DS1286 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-ds1286");
