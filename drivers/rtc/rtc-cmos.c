<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RTC class driver क्रम "CMOS RTC":  PCs, ACPI, etc
 *
 * Copyright (C) 1996 Paul Gorपंचांगaker (drivers/अक्षर/rtc.c)
 * Copyright (C) 2006 David Brownell (convert to new framework)
 */

/*
 * The original "cmos clock" chip was an MC146818 chip, now obsolete.
 * That defined the रेजिस्टर पूर्णांकerface now provided by all PCs, some
 * non-PC प्रणालीs, and incorporated पूर्णांकo ACPI.  Modern PC chipsets
 * पूर्णांकegrate an MC146818 clone in their southbridge, and boards use
 * that instead of discrete clones like the DS12887 or M48T86.  There
 * are also clones that connect using the LPC bus.
 *
 * That रेजिस्टर API is also used directly by various other drivers
 * (notably क्रम पूर्णांकegrated NVRAM), infraकाष्ठाure (x86 has code to
 * bypass the RTC framework, directly पढ़ोing the RTC during boot
 * and updating minutes/seconds क्रम प्रणालीs using NTP synch) and
 * utilities (like userspace 'hwclock', अगर no /dev node exists).
 *
 * So **ALL** calls to CMOS_READ and CMOS_WRITE must be करोne with
 * पूर्णांकerrupts disabled, holding the global rtc_lock, to exclude those
 * other drivers and utilities on correctly configured प्रणालीs.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/log2.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/dmi.h>
#पूर्ण_अगर

/* this is क्रम "generic access to PC-style RTC" using CMOS_READ/CMOS_WRITE */
#समावेश <linux/mc146818rtc.h>

#अगर_घोषित CONFIG_ACPI
/*
 * Use ACPI SCI to replace HPET पूर्णांकerrupt क्रम RTC Alarm event
 *
 * If cleared, ACPI SCI is only used to wake up the प्रणाली from suspend
 *
 * If set, ACPI SCI is used to handle UIE/AIE and प्रणाली wakeup
 */

अटल bool use_acpi_alarm;
module_param(use_acpi_alarm, bool, 0444);

अटल अंतरभूत पूर्णांक cmos_use_acpi_alarm(व्योम)
अणु
	वापस use_acpi_alarm;
पूर्ण
#अन्यथा /* !CONFIG_ACPI */

अटल अंतरभूत पूर्णांक cmos_use_acpi_alarm(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा cmos_rtc अणु
	काष्ठा rtc_device	*rtc;
	काष्ठा device		*dev;
	पूर्णांक			irq;
	काष्ठा resource		*iomem;
	समय64_t		alarm_expires;

	व्योम			(*wake_on)(काष्ठा device *);
	व्योम			(*wake_off)(काष्ठा device *);

	u8			enabled_wake;
	u8			suspend_ctrl;

	/* newer hardware extends the original रेजिस्टर set */
	u8			day_alrm;
	u8			mon_alrm;
	u8			century;

	काष्ठा rtc_wkalrm	saved_wkalrm;
पूर्ण;

/* both platक्रमm and pnp busses use negative numbers क्रम invalid irqs */
#घोषणा is_valid_irq(n)		((n) > 0)

अटल स्थिर अक्षर driver_name[] = "rtc_cmos";

/* The RTC_INTR रेजिस्टर may have e.g. RTC_PF set even अगर RTC_PIE is clear;
 * always mask it against the irq enable bits in RTC_CONTROL.  Bit values
 * are the same: PF==PIE, AF=AIE, UF=UIE; so RTC_IRQMASK works with both.
 */
#घोषणा	RTC_IRQMASK	(RTC_PF | RTC_AF | RTC_UF)

अटल अंतरभूत पूर्णांक is_पूर्णांकr(u8 rtc_पूर्णांकr)
अणु
	अगर (!(rtc_पूर्णांकr & RTC_IRQF))
		वापस 0;
	वापस rtc_पूर्णांकr & RTC_IRQMASK;
पूर्ण

/*----------------------------------------------------------------*/

/* Much modern x86 hardware has HPETs (10+ MHz समयrs) which, because
 * many BIOS programmers करोn't set up "sane mode" IRQ routing, are mostly
 * used in a broken "legacy replacement" mode.  The अवरोधage includes
 * HPET #1 hijacking the IRQ क्रम this RTC, and being unavailable क्रम
 * other (better) use.
 *
 * When that broken mode is in use, platक्रमm glue provides a partial
 * emulation of hardware RTC IRQ facilities using HPET #1.  We करोn't
 * want to use HPET क्रम anything except those IRQs though...
 */
#अगर_घोषित CONFIG_HPET_EMULATE_RTC
#समावेश <यंत्र/hpet.h>
#अन्यथा

अटल अंतरभूत पूर्णांक is_hpet_enabled(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hpet_mask_rtc_irq_bit(अचिन्हित दीर्घ mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hpet_set_rtc_irq_bit(अचिन्हित दीर्घ mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
hpet_set_alarm_समय(अचिन्हित अक्षर hrs, अचिन्हित अक्षर min, अचिन्हित अक्षर sec)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hpet_set_periodic_freq(अचिन्हित दीर्घ freq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hpet_rtc_dropped_irq(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hpet_rtc_समयr_init(व्योम)
अणु
	वापस 0;
पूर्ण

बाह्य irq_handler_t hpet_rtc_पूर्णांकerrupt;

अटल अंतरभूत पूर्णांक hpet_रेजिस्टर_irq_handler(irq_handler_t handler)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hpet_unरेजिस्टर_irq_handler(irq_handler_t handler)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

/* Don't use HPET क्रम RTC Alarm event अगर ACPI Fixed event is used */
अटल अंतरभूत पूर्णांक use_hpet_alarm(व्योम)
अणु
	वापस is_hpet_enabled() && !cmos_use_acpi_alarm();
पूर्ण

/*----------------------------------------------------------------*/

#अगर_घोषित RTC_PORT

/* Most newer x86 प्रणालीs have two रेजिस्टर banks, the first used
 * क्रम RTC and NVRAM and the second only क्रम NVRAM.  Caller must
 * own rtc_lock ... and we won't worry about access during NMI.
 */
#घोषणा can_bank2	true

अटल अंतरभूत अचिन्हित अक्षर cmos_पढ़ो_bank2(अचिन्हित अक्षर addr)
अणु
	outb(addr, RTC_PORT(2));
	वापस inb(RTC_PORT(3));
पूर्ण

अटल अंतरभूत व्योम cmos_ग_लिखो_bank2(अचिन्हित अक्षर val, अचिन्हित अक्षर addr)
अणु
	outb(addr, RTC_PORT(2));
	outb(val, RTC_PORT(3));
पूर्ण

#अन्यथा

#घोषणा can_bank2	false

अटल अंतरभूत अचिन्हित अक्षर cmos_पढ़ो_bank2(अचिन्हित अक्षर addr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cmos_ग_लिखो_bank2(अचिन्हित अक्षर val, अचिन्हित अक्षर addr)
अणु
पूर्ण

#पूर्ण_अगर

/*----------------------------------------------------------------*/

अटल पूर्णांक cmos_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	/*
	 * If pm_trace abused the RTC क्रम storage, set the बारpec to 0,
	 * which tells the caller that this RTC value is unusable.
	 */
	अगर (!pm_trace_rtc_valid())
		वापस -EIO;

	/* REVISIT:  अगर the घड़ी has a "century" रेजिस्टर, use
	 * that instead of the heuristic in mc146818_get_समय().
	 * That'll make Y3K compatility (year > 2070) easy!
	 */
	mc146818_get_समय(t);
	वापस 0;
पूर्ण

अटल पूर्णांक cmos_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	/* REVISIT:  set the "century" रेजिस्टर अगर available
	 *
	 * NOTE: this ignores the issue whereby updating the seconds
	 * takes effect exactly 500ms after we ग_लिखो the रेजिस्टर.
	 * (Also queueing and other delays beक्रमe we get this far.)
	 */
	वापस mc146818_set_समय(t);
पूर्ण

अटल पूर्णांक cmos_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	अचिन्हित अक्षर	rtc_control;

	/* This not only a rtc_op, but also called directly */
	अगर (!is_valid_irq(cmos->irq))
		वापस -EIO;

	/* Basic alarms only support hour, minute, and seconds fields.
	 * Some also support day and month, क्रम alarms up to a year in
	 * the future.
	 */

	spin_lock_irq(&rtc_lock);
	t->समय.पंचांग_sec = CMOS_READ(RTC_SECONDS_ALARM);
	t->समय.पंचांग_min = CMOS_READ(RTC_MINUTES_ALARM);
	t->समय.पंचांग_hour = CMOS_READ(RTC_HOURS_ALARM);

	अगर (cmos->day_alrm) अणु
		/* ignore upper bits on पढ़ोback per ACPI spec */
		t->समय.पंचांग_mday = CMOS_READ(cmos->day_alrm) & 0x3f;
		अगर (!t->समय.पंचांग_mday)
			t->समय.पंचांग_mday = -1;

		अगर (cmos->mon_alrm) अणु
			t->समय.पंचांग_mon = CMOS_READ(cmos->mon_alrm);
			अगर (!t->समय.पंचांग_mon)
				t->समय.पंचांग_mon = -1;
		पूर्ण
	पूर्ण

	rtc_control = CMOS_READ(RTC_CONTROL);
	spin_unlock_irq(&rtc_lock);

	अगर (!(rtc_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		अगर (((अचिन्हित)t->समय.पंचांग_sec) < 0x60)
			t->समय.पंचांग_sec = bcd2bin(t->समय.पंचांग_sec);
		अन्यथा
			t->समय.पंचांग_sec = -1;
		अगर (((अचिन्हित)t->समय.पंचांग_min) < 0x60)
			t->समय.पंचांग_min = bcd2bin(t->समय.पंचांग_min);
		अन्यथा
			t->समय.पंचांग_min = -1;
		अगर (((अचिन्हित)t->समय.पंचांग_hour) < 0x24)
			t->समय.पंचांग_hour = bcd2bin(t->समय.पंचांग_hour);
		अन्यथा
			t->समय.पंचांग_hour = -1;

		अगर (cmos->day_alrm) अणु
			अगर (((अचिन्हित)t->समय.पंचांग_mday) <= 0x31)
				t->समय.पंचांग_mday = bcd2bin(t->समय.पंचांग_mday);
			अन्यथा
				t->समय.पंचांग_mday = -1;

			अगर (cmos->mon_alrm) अणु
				अगर (((अचिन्हित)t->समय.पंचांग_mon) <= 0x12)
					t->समय.पंचांग_mon = bcd2bin(t->समय.पंचांग_mon)-1;
				अन्यथा
					t->समय.पंचांग_mon = -1;
			पूर्ण
		पूर्ण
	पूर्ण

	t->enabled = !!(rtc_control & RTC_AIE);
	t->pending = 0;

	वापस 0;
पूर्ण

अटल व्योम cmos_checkपूर्णांकr(काष्ठा cmos_rtc *cmos, अचिन्हित अक्षर rtc_control)
अणु
	अचिन्हित अक्षर	rtc_पूर्णांकr;

	/* NOTE after changing RTC_xIE bits we always पढ़ो INTR_FLAGS;
	 * allegedly some older rtcs need that to handle irqs properly
	 */
	rtc_पूर्णांकr = CMOS_READ(RTC_INTR_FLAGS);

	अगर (use_hpet_alarm())
		वापस;

	rtc_पूर्णांकr &= (rtc_control & RTC_IRQMASK) | RTC_IRQF;
	अगर (is_पूर्णांकr(rtc_पूर्णांकr))
		rtc_update_irq(cmos->rtc, 1, rtc_पूर्णांकr);
पूर्ण

अटल व्योम cmos_irq_enable(काष्ठा cmos_rtc *cmos, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर	rtc_control;

	/* flush any pending IRQ status, notably क्रम update irqs,
	 * beक्रमe we enable new IRQs
	 */
	rtc_control = CMOS_READ(RTC_CONTROL);
	cmos_checkपूर्णांकr(cmos, rtc_control);

	rtc_control |= mask;
	CMOS_WRITE(rtc_control, RTC_CONTROL);
	अगर (use_hpet_alarm())
		hpet_set_rtc_irq_bit(mask);

	अगर ((mask & RTC_AIE) && cmos_use_acpi_alarm()) अणु
		अगर (cmos->wake_on)
			cmos->wake_on(cmos->dev);
	पूर्ण

	cmos_checkपूर्णांकr(cmos, rtc_control);
पूर्ण

अटल व्योम cmos_irq_disable(काष्ठा cmos_rtc *cmos, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर	rtc_control;

	rtc_control = CMOS_READ(RTC_CONTROL);
	rtc_control &= ~mask;
	CMOS_WRITE(rtc_control, RTC_CONTROL);
	अगर (use_hpet_alarm())
		hpet_mask_rtc_irq_bit(mask);

	अगर ((mask & RTC_AIE) && cmos_use_acpi_alarm()) अणु
		अगर (cmos->wake_off)
			cmos->wake_off(cmos->dev);
	पूर्ण

	cmos_checkपूर्णांकr(cmos, rtc_control);
पूर्ण

अटल पूर्णांक cmos_validate_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा cmos_rtc *cmos = dev_get_drvdata(dev);
	काष्ठा rtc_समय now;

	cmos_पढ़ो_समय(dev, &now);

	अगर (!cmos->day_alrm) अणु
		समय64_t t_max_date;
		समय64_t t_alrm;

		t_max_date = rtc_पंचांग_to_समय64(&now);
		t_max_date += 24 * 60 * 60 - 1;
		t_alrm = rtc_पंचांग_to_समय64(&t->समय);
		अगर (t_alrm > t_max_date) अणु
			dev_err(dev,
				"Alarms can be up to one day in the future\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (!cmos->mon_alrm) अणु
		काष्ठा rtc_समय max_date = now;
		समय64_t t_max_date;
		समय64_t t_alrm;
		पूर्णांक max_mday;

		अगर (max_date.पंचांग_mon == 11) अणु
			max_date.पंचांग_mon = 0;
			max_date.पंचांग_year += 1;
		पूर्ण अन्यथा अणु
			max_date.पंचांग_mon += 1;
		पूर्ण
		max_mday = rtc_month_days(max_date.पंचांग_mon, max_date.पंचांग_year);
		अगर (max_date.पंचांग_mday > max_mday)
			max_date.पंचांग_mday = max_mday;

		t_max_date = rtc_पंचांग_to_समय64(&max_date);
		t_max_date -= 1;
		t_alrm = rtc_पंचांग_to_समय64(&t->समय);
		अगर (t_alrm > t_max_date) अणु
			dev_err(dev,
				"Alarms can be up to one month in the future\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा rtc_समय max_date = now;
		समय64_t t_max_date;
		समय64_t t_alrm;
		पूर्णांक max_mday;

		max_date.पंचांग_year += 1;
		max_mday = rtc_month_days(max_date.पंचांग_mon, max_date.पंचांग_year);
		अगर (max_date.पंचांग_mday > max_mday)
			max_date.पंचांग_mday = max_mday;

		t_max_date = rtc_पंचांग_to_समय64(&max_date);
		t_max_date -= 1;
		t_alrm = rtc_पंचांग_to_समय64(&t->समय);
		अगर (t_alrm > t_max_date) अणु
			dev_err(dev,
				"Alarms can be up to one year in the future\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cmos_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	अचिन्हित अक्षर mon, mday, hrs, min, sec, rtc_control;
	पूर्णांक ret;

	/* This not only a rtc_op, but also called directly */
	अगर (!is_valid_irq(cmos->irq))
		वापस -EIO;

	ret = cmos_validate_alarm(dev, t);
	अगर (ret < 0)
		वापस ret;

	mon = t->समय.पंचांग_mon + 1;
	mday = t->समय.पंचांग_mday;
	hrs = t->समय.पंचांग_hour;
	min = t->समय.पंचांग_min;
	sec = t->समय.पंचांग_sec;

	rtc_control = CMOS_READ(RTC_CONTROL);
	अगर (!(rtc_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		/* Writing 0xff means "don't care" or "match all".  */
		mon = (mon <= 12) ? bin2bcd(mon) : 0xff;
		mday = (mday >= 1 && mday <= 31) ? bin2bcd(mday) : 0xff;
		hrs = (hrs < 24) ? bin2bcd(hrs) : 0xff;
		min = (min < 60) ? bin2bcd(min) : 0xff;
		sec = (sec < 60) ? bin2bcd(sec) : 0xff;
	पूर्ण

	spin_lock_irq(&rtc_lock);

	/* next rtc irq must not be from previous alarm setting */
	cmos_irq_disable(cmos, RTC_AIE);

	/* update alarm */
	CMOS_WRITE(hrs, RTC_HOURS_ALARM);
	CMOS_WRITE(min, RTC_MINUTES_ALARM);
	CMOS_WRITE(sec, RTC_SECONDS_ALARM);

	/* the प्रणाली may support an "enhanced" alarm */
	अगर (cmos->day_alrm) अणु
		CMOS_WRITE(mday, cmos->day_alrm);
		अगर (cmos->mon_alrm)
			CMOS_WRITE(mon, cmos->mon_alrm);
	पूर्ण

	अगर (use_hpet_alarm()) अणु
		/*
		 * FIXME the HPET alarm glue currently ignores day_alrm
		 * and mon_alrm ...
		 */
		hpet_set_alarm_समय(t->समय.पंचांग_hour, t->समय.पंचांग_min,
				    t->समय.पंचांग_sec);
	पूर्ण

	अगर (t->enabled)
		cmos_irq_enable(cmos, RTC_AIE);

	spin_unlock_irq(&rtc_lock);

	cmos->alarm_expires = rtc_पंचांग_to_समय64(&t->समय);

	वापस 0;
पूर्ण

अटल पूर्णांक cmos_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&rtc_lock, flags);

	अगर (enabled)
		cmos_irq_enable(cmos, RTC_AIE);
	अन्यथा
		cmos_irq_disable(cmos, RTC_AIE);

	spin_unlock_irqrestore(&rtc_lock, flags);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_RTC_INTF_PROC)

अटल पूर्णांक cmos_procfs(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	अचिन्हित अक्षर	rtc_control, valid;

	spin_lock_irq(&rtc_lock);
	rtc_control = CMOS_READ(RTC_CONTROL);
	valid = CMOS_READ(RTC_VALID);
	spin_unlock_irq(&rtc_lock);

	/* NOTE:  at least ICH6 reports battery status using a dअगरferent
	 * (non-RTC) bit; and SQWE is ignored on many current प्रणालीs.
	 */
	seq_म_लिखो(seq,
		   "periodic_IRQ\t: %s\n"
		   "update_IRQ\t: %s\n"
		   "HPET_emulated\t: %s\n"
		   // "square_wave\t: %s\n"
		   "BCD\t\t: %s\n"
		   "DST_enable\t: %s\n"
		   "periodic_freq\t: %d\n"
		   "batt_status\t: %s\n",
		   (rtc_control & RTC_PIE) ? "yes" : "no",
		   (rtc_control & RTC_UIE) ? "yes" : "no",
		   use_hpet_alarm() ? "yes" : "no",
		   // (rtc_control & RTC_SQWE) ? "yes" : "no",
		   (rtc_control & RTC_DM_BINARY) ? "no" : "yes",
		   (rtc_control & RTC_DST_EN) ? "yes" : "no",
		   cmos->rtc->irq_freq,
		   (valid & RTC_VRT) ? "okay" : "dead");

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा	cmos_procfs	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा rtc_class_ops cmos_rtc_ops = अणु
	.पढ़ो_समय		= cmos_पढ़ो_समय,
	.set_समय		= cmos_set_समय,
	.पढ़ो_alarm		= cmos_पढ़ो_alarm,
	.set_alarm		= cmos_set_alarm,
	.proc			= cmos_procfs,
	.alarm_irq_enable	= cmos_alarm_irq_enable,
पूर्ण;

/*----------------------------------------------------------------*/

/*
 * All these chips have at least 64 bytes of address space, shared by
 * RTC रेजिस्टरs and NVRAM.  Most of those bytes of NVRAM are used
 * by boot firmware.  Modern chips have 128 or 256 bytes.
 */

#घोषणा NVRAM_OFFSET	(RTC_REG_D + 1)

अटल पूर्णांक cmos_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val,
			   माप_प्रकार count)
अणु
	अचिन्हित अक्षर *buf = val;
	पूर्णांक	retval;

	off += NVRAM_OFFSET;
	spin_lock_irq(&rtc_lock);
	क्रम (retval = 0; count; count--, off++, retval++) अणु
		अगर (off < 128)
			*buf++ = CMOS_READ(off);
		अन्यथा अगर (can_bank2)
			*buf++ = cmos_पढ़ो_bank2(off);
		अन्यथा
			अवरोध;
	पूर्ण
	spin_unlock_irq(&rtc_lock);

	वापस retval;
पूर्ण

अटल पूर्णांक cmos_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val,
			    माप_प्रकार count)
अणु
	काष्ठा cmos_rtc	*cmos = priv;
	अचिन्हित अक्षर	*buf = val;
	पूर्णांक		retval;

	/* NOTE:  on at least PCs and Ataris, the boot firmware uses a
	 * checksum on part of the NVRAM data.  That's currently ignored
	 * here.  If userspace is smart enough to know what fields of
	 * NVRAM to update, updating checksums is also part of its job.
	 */
	off += NVRAM_OFFSET;
	spin_lock_irq(&rtc_lock);
	क्रम (retval = 0; count; count--, off++, retval++) अणु
		/* करोn't trash RTC रेजिस्टरs */
		अगर (off == cmos->day_alrm
				|| off == cmos->mon_alrm
				|| off == cmos->century)
			buf++;
		अन्यथा अगर (off < 128)
			CMOS_WRITE(*buf++, off);
		अन्यथा अगर (can_bank2)
			cmos_ग_लिखो_bank2(*buf++, off);
		अन्यथा
			अवरोध;
	पूर्ण
	spin_unlock_irq(&rtc_lock);

	वापस retval;
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा cmos_rtc	cmos_rtc;

अटल irqवापस_t cmos_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	u8		irqstat;
	u8		rtc_control;

	spin_lock(&rtc_lock);

	/* When the HPET पूर्णांकerrupt handler calls us, the पूर्णांकerrupt
	 * status is passed as arg1 instead of the irq number.  But
	 * always clear irq status, even when HPET is in the way.
	 *
	 * Note that HPET and RTC are almost certainly out of phase,
	 * giving dअगरferent IRQ status ...
	 */
	irqstat = CMOS_READ(RTC_INTR_FLAGS);
	rtc_control = CMOS_READ(RTC_CONTROL);
	अगर (use_hpet_alarm())
		irqstat = (अचिन्हित दीर्घ)irq & 0xF0;

	/* If we were suspended, RTC_CONTROL may not be accurate since the
	 * bios may have cleared it.
	 */
	अगर (!cmos_rtc.suspend_ctrl)
		irqstat &= (rtc_control & RTC_IRQMASK) | RTC_IRQF;
	अन्यथा
		irqstat &= (cmos_rtc.suspend_ctrl & RTC_IRQMASK) | RTC_IRQF;

	/* All Linux RTC alarms should be treated as अगर they were oneshot.
	 * Similar code may be needed in प्रणाली wakeup paths, in हाल the
	 * alarm woke the प्रणाली.
	 */
	अगर (irqstat & RTC_AIE) अणु
		cmos_rtc.suspend_ctrl &= ~RTC_AIE;
		rtc_control &= ~RTC_AIE;
		CMOS_WRITE(rtc_control, RTC_CONTROL);
		अगर (use_hpet_alarm())
			hpet_mask_rtc_irq_bit(RTC_AIE);
		CMOS_READ(RTC_INTR_FLAGS);
	पूर्ण
	spin_unlock(&rtc_lock);

	अगर (is_पूर्णांकr(irqstat)) अणु
		rtc_update_irq(p, 1, irqstat);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;
पूर्ण

#अगर_घोषित	CONFIG_PNP
#घोषणा	INITSECTION

#अन्यथा
#घोषणा	INITSECTION	__init
#पूर्ण_अगर

अटल पूर्णांक INITSECTION
cmos_करो_probe(काष्ठा device *dev, काष्ठा resource *ports, पूर्णांक rtc_irq)
अणु
	काष्ठा cmos_rtc_board_info	*info = dev_get_platdata(dev);
	पूर्णांक				retval = 0;
	अचिन्हित अक्षर			rtc_control;
	अचिन्हित			address_space;
	u32				flags = 0;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "cmos_nvram",
		.word_size = 1,
		.stride = 1,
		.reg_पढ़ो = cmos_nvram_पढ़ो,
		.reg_ग_लिखो = cmos_nvram_ग_लिखो,
		.priv = &cmos_rtc,
	पूर्ण;

	/* there can be only one ... */
	अगर (cmos_rtc.dev)
		वापस -EBUSY;

	अगर (!ports)
		वापस -ENODEV;

	/* Claim I/O ports ASAP, minimizing conflict with legacy driver.
	 *
	 * REVISIT non-x86 प्रणालीs may instead use memory space resources
	 * (needing ioremap etc), not i/o space resources like this ...
	 */
	अगर (RTC_IOMAPPED)
		ports = request_region(ports->start, resource_size(ports),
				       driver_name);
	अन्यथा
		ports = request_mem_region(ports->start, resource_size(ports),
					   driver_name);
	अगर (!ports) अणु
		dev_dbg(dev, "i/o registers already in use\n");
		वापस -EBUSY;
	पूर्ण

	cmos_rtc.irq = rtc_irq;
	cmos_rtc.iomem = ports;

	/* Heuristic to deduce NVRAM size ... करो what the legacy NVRAM
	 * driver did, but करोn't reject unknown configs.   Old hardware
	 * won't address 128 bytes.  Newer chips have multiple banks,
	 * though they may not be listed in one I/O resource.
	 */
#अगर	defined(CONFIG_ATARI)
	address_space = 64;
#या_अगर defined(__i386__) || defined(__x86_64__) || defined(__arm__) \
			|| defined(__sparc__) || defined(__mips__) \
			|| defined(__घातerpc__)
	address_space = 128;
#अन्यथा
#warning Assuming 128 bytes of RTC+NVRAM address space, not 64 bytes.
	address_space = 128;
#पूर्ण_अगर
	अगर (can_bank2 && ports->end > (ports->start + 1))
		address_space = 256;

	/* For ACPI प्रणालीs extension info comes from the FADT.  On others,
	 * board specअगरic setup provides it as appropriate.  Systems where
	 * the alarm IRQ isn't स्वतःmatically a wakeup IRQ (like ACPI, and
	 * some almost-clones) can provide hooks to make that behave.
	 *
	 * Note that ACPI करोesn't preclude putting these रेजिस्टरs पूर्णांकo
	 * "extended" areas of the chip, including some that we won't yet
	 * expect CMOS_READ and मित्रs to handle.
	 */
	अगर (info) अणु
		अगर (info->flags)
			flags = info->flags;
		अगर (info->address_space)
			address_space = info->address_space;

		अगर (info->rtc_day_alarm && info->rtc_day_alarm < 128)
			cmos_rtc.day_alrm = info->rtc_day_alarm;
		अगर (info->rtc_mon_alarm && info->rtc_mon_alarm < 128)
			cmos_rtc.mon_alrm = info->rtc_mon_alarm;
		अगर (info->rtc_century && info->rtc_century < 128)
			cmos_rtc.century = info->rtc_century;

		अगर (info->wake_on && info->wake_off) अणु
			cmos_rtc.wake_on = info->wake_on;
			cmos_rtc.wake_off = info->wake_off;
		पूर्ण
	पूर्ण

	cmos_rtc.dev = dev;
	dev_set_drvdata(dev, &cmos_rtc);

	cmos_rtc.rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(cmos_rtc.rtc)) अणु
		retval = PTR_ERR(cmos_rtc.rtc);
		जाओ cleanup0;
	पूर्ण

	नाम_region(ports, dev_name(&cmos_rtc.rtc->dev));

	spin_lock_irq(&rtc_lock);

	/* Ensure that the RTC is accessible. Bit 6 must be 0! */
	अगर ((CMOS_READ(RTC_VALID) & 0x40) != 0) अणु
		spin_unlock_irq(&rtc_lock);
		dev_warn(dev, "not accessible\n");
		retval = -ENXIO;
		जाओ cleanup1;
	पूर्ण

	अगर (!(flags & CMOS_RTC_FLAGS_NOFREQ)) अणु
		/* क्रमce periodic irq to CMOS reset शेष of 1024Hz;
		 *
		 * REVISIT it's been reported that at least one x86_64 ALI
		 * mobo करोesn't use 32KHz here ... क्रम portability we might
		 * need to करो something about other घड़ी frequencies.
		 */
		cmos_rtc.rtc->irq_freq = 1024;
		अगर (use_hpet_alarm())
			hpet_set_periodic_freq(cmos_rtc.rtc->irq_freq);
		CMOS_WRITE(RTC_REF_CLCK_32KHZ | 0x06, RTC_FREQ_SELECT);
	पूर्ण

	/* disable irqs */
	अगर (is_valid_irq(rtc_irq))
		cmos_irq_disable(&cmos_rtc, RTC_PIE | RTC_AIE | RTC_UIE);

	rtc_control = CMOS_READ(RTC_CONTROL);

	spin_unlock_irq(&rtc_lock);

	अगर (is_valid_irq(rtc_irq) && !(rtc_control & RTC_24H)) अणु
		dev_warn(dev, "only 24-hr supported\n");
		retval = -ENXIO;
		जाओ cleanup1;
	पूर्ण

	अगर (use_hpet_alarm())
		hpet_rtc_समयr_init();

	अगर (is_valid_irq(rtc_irq)) अणु
		irq_handler_t rtc_cmos_पूर्णांक_handler;

		अगर (use_hpet_alarm()) अणु
			rtc_cmos_पूर्णांक_handler = hpet_rtc_पूर्णांकerrupt;
			retval = hpet_रेजिस्टर_irq_handler(cmos_पूर्णांकerrupt);
			अगर (retval) अणु
				hpet_mask_rtc_irq_bit(RTC_IRQMASK);
				dev_warn(dev, "hpet_register_irq_handler "
						" failed in rtc_init().");
				जाओ cleanup1;
			पूर्ण
		पूर्ण अन्यथा
			rtc_cmos_पूर्णांक_handler = cmos_पूर्णांकerrupt;

		retval = request_irq(rtc_irq, rtc_cmos_पूर्णांक_handler,
				0, dev_name(&cmos_rtc.rtc->dev),
				cmos_rtc.rtc);
		अगर (retval < 0) अणु
			dev_dbg(dev, "IRQ %d is already in use\n", rtc_irq);
			जाओ cleanup1;
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_bit(RTC_FEATURE_ALARM, cmos_rtc.rtc->features);
	पूर्ण

	cmos_rtc.rtc->ops = &cmos_rtc_ops;

	retval = devm_rtc_रेजिस्टर_device(cmos_rtc.rtc);
	अगर (retval)
		जाओ cleanup2;

	/* Set the sync offset क्रम the periodic 11min update correct */
	cmos_rtc.rtc->set_offset_nsec = NSEC_PER_SEC / 2;

	/* export at least the first block of NVRAM */
	nvmem_cfg.size = address_space - NVRAM_OFFSET;
	devm_rtc_nvmem_रेजिस्टर(cmos_rtc.rtc, &nvmem_cfg);

	dev_info(dev, "%s%s, %d bytes nvram%s\n",
		 !is_valid_irq(rtc_irq) ? "no alarms" :
		 cmos_rtc.mon_alrm ? "alarms up to one year" :
		 cmos_rtc.day_alrm ? "alarms up to one month" :
		 "alarms up to one day",
		 cmos_rtc.century ? ", y3k" : "",
		 nvmem_cfg.size,
		 use_hpet_alarm() ? ", hpet irqs" : "");

	वापस 0;

cleanup2:
	अगर (is_valid_irq(rtc_irq))
		मुक्त_irq(rtc_irq, cmos_rtc.rtc);
cleanup1:
	cmos_rtc.dev = शून्य;
cleanup0:
	अगर (RTC_IOMAPPED)
		release_region(ports->start, resource_size(ports));
	अन्यथा
		release_mem_region(ports->start, resource_size(ports));
	वापस retval;
पूर्ण

अटल व्योम cmos_करो_shutकरोwn(पूर्णांक rtc_irq)
अणु
	spin_lock_irq(&rtc_lock);
	अगर (is_valid_irq(rtc_irq))
		cmos_irq_disable(&cmos_rtc, RTC_IRQMASK);
	spin_unlock_irq(&rtc_lock);
पूर्ण

अटल व्योम cmos_करो_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	काष्ठा resource *ports;

	cmos_करो_shutकरोwn(cmos->irq);

	अगर (is_valid_irq(cmos->irq)) अणु
		मुक्त_irq(cmos->irq, cmos->rtc);
		अगर (use_hpet_alarm())
			hpet_unरेजिस्टर_irq_handler(cmos_पूर्णांकerrupt);
	पूर्ण

	cmos->rtc = शून्य;

	ports = cmos->iomem;
	अगर (RTC_IOMAPPED)
		release_region(ports->start, resource_size(ports));
	अन्यथा
		release_mem_region(ports->start, resource_size(ports));
	cmos->iomem = शून्य;

	cmos->dev = शून्य;
पूर्ण

अटल पूर्णांक cmos_aie_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	काष्ठा rtc_समय now;
	समय64_t t_now;
	पूर्णांक retval = 0;
	अचिन्हित अक्षर rtc_control;

	अगर (!cmos->alarm_expires)
		वापस -EINVAL;

	spin_lock_irq(&rtc_lock);
	rtc_control = CMOS_READ(RTC_CONTROL);
	spin_unlock_irq(&rtc_lock);

	/* We only care about the situation where AIE is disabled. */
	अगर (rtc_control & RTC_AIE)
		वापस -EBUSY;

	cmos_पढ़ो_समय(dev, &now);
	t_now = rtc_पंचांग_to_समय64(&now);

	/*
	 * When enabling "RTC wake-up" in BIOS setup, the machine reboots
	 * स्वतःmatically right after shutकरोwn on some buggy boxes.
	 * This स्वतःmatic rebooting issue won't happen when the alarm
	 * समय is larger than now+1 seconds.
	 *
	 * If the alarm समय is equal to now+1 seconds, the issue can be
	 * prevented by cancelling the alarm.
	 */
	अगर (cmos->alarm_expires == t_now + 1) अणु
		काष्ठा rtc_wkalrm alarm;

		/* Cancel the AIE समयr by configuring the past समय. */
		rtc_समय64_to_पंचांग(t_now - 1, &alarm.समय);
		alarm.enabled = 0;
		retval = cmos_set_alarm(dev, &alarm);
	पूर्ण अन्यथा अगर (cmos->alarm_expires > t_now + 1) अणु
		retval = -EBUSY;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक cmos_suspend(काष्ठा device *dev)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	अचिन्हित अक्षर	पंचांगp;

	/* only the alarm might be a wakeup event source */
	spin_lock_irq(&rtc_lock);
	cmos->suspend_ctrl = पंचांगp = CMOS_READ(RTC_CONTROL);
	अगर (पंचांगp & (RTC_PIE|RTC_AIE|RTC_UIE)) अणु
		अचिन्हित अक्षर	mask;

		अगर (device_may_wakeup(dev))
			mask = RTC_IRQMASK & ~RTC_AIE;
		अन्यथा
			mask = RTC_IRQMASK;
		पंचांगp &= ~mask;
		CMOS_WRITE(पंचांगp, RTC_CONTROL);
		अगर (use_hpet_alarm())
			hpet_mask_rtc_irq_bit(mask);
		cmos_checkपूर्णांकr(cmos, पंचांगp);
	पूर्ण
	spin_unlock_irq(&rtc_lock);

	अगर ((पंचांगp & RTC_AIE) && !cmos_use_acpi_alarm()) अणु
		cmos->enabled_wake = 1;
		अगर (cmos->wake_on)
			cmos->wake_on(dev);
		अन्यथा
			enable_irq_wake(cmos->irq);
	पूर्ण

	स_रखो(&cmos->saved_wkalrm, 0, माप(काष्ठा rtc_wkalrm));
	cmos_पढ़ो_alarm(dev, &cmos->saved_wkalrm);

	dev_dbg(dev, "suspend%s, ctrl %02x\n",
			(पंचांगp & RTC_AIE) ? ", alarm may wake" : "",
			पंचांगp);

	वापस 0;
पूर्ण

/* We want RTC alarms to wake us from e.g. ACPI G2/S5 "soft off", even
 * after a detour through G3 "mechanical off", although the ACPI spec
 * says wakeup should only work from G1/S4 "hibernate".  To most users,
 * distinctions between S4 and S5 are poपूर्णांकless.  So when the hardware
 * allows, करोn't draw that distinction.
 */
अटल अंतरभूत पूर्णांक cmos_घातeroff(काष्ठा device *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_PM))
		वापस -ENOSYS;

	वापस cmos_suspend(dev);
पूर्ण

अटल व्योम cmos_check_wkalrm(काष्ठा device *dev)
अणु
	काष्ठा cmos_rtc *cmos = dev_get_drvdata(dev);
	काष्ठा rtc_wkalrm current_alarm;
	समय64_t t_now;
	समय64_t t_current_expires;
	समय64_t t_saved_expires;
	काष्ठा rtc_समय now;

	/* Check अगर we have RTC Alarm armed */
	अगर (!(cmos->suspend_ctrl & RTC_AIE))
		वापस;

	cmos_पढ़ो_समय(dev, &now);
	t_now = rtc_पंचांग_to_समय64(&now);

	/*
	 * ACPI RTC wake event is cleared after resume from STR,
	 * ACK the rtc irq here
	 */
	अगर (t_now >= cmos->alarm_expires && cmos_use_acpi_alarm()) अणु
		cmos_पूर्णांकerrupt(0, (व्योम *)cmos->rtc);
		वापस;
	पूर्ण

	स_रखो(&current_alarm, 0, माप(काष्ठा rtc_wkalrm));
	cmos_पढ़ो_alarm(dev, &current_alarm);
	t_current_expires = rtc_पंचांग_to_समय64(&current_alarm.समय);
	t_saved_expires = rtc_पंचांग_to_समय64(&cmos->saved_wkalrm.समय);
	अगर (t_current_expires != t_saved_expires ||
	    cmos->saved_wkalrm.enabled != current_alarm.enabled) अणु
		cmos_set_alarm(dev, &cmos->saved_wkalrm);
	पूर्ण
पूर्ण

अटल व्योम cmos_check_acpi_rtc_status(काष्ठा device *dev,
				       अचिन्हित अक्षर *rtc_control);

अटल पूर्णांक __maybe_unused cmos_resume(काष्ठा device *dev)
अणु
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);
	अचिन्हित अक्षर पंचांगp;

	अगर (cmos->enabled_wake && !cmos_use_acpi_alarm()) अणु
		अगर (cmos->wake_off)
			cmos->wake_off(dev);
		अन्यथा
			disable_irq_wake(cmos->irq);
		cmos->enabled_wake = 0;
	पूर्ण

	/* The BIOS might have changed the alarm, restore it */
	cmos_check_wkalrm(dev);

	spin_lock_irq(&rtc_lock);
	पंचांगp = cmos->suspend_ctrl;
	cmos->suspend_ctrl = 0;
	/* re-enable any irqs previously active */
	अगर (पंचांगp & RTC_IRQMASK) अणु
		अचिन्हित अक्षर	mask;

		अगर (device_may_wakeup(dev) && use_hpet_alarm())
			hpet_rtc_समयr_init();

		करो अणु
			CMOS_WRITE(पंचांगp, RTC_CONTROL);
			अगर (use_hpet_alarm())
				hpet_set_rtc_irq_bit(पंचांगp & RTC_IRQMASK);

			mask = CMOS_READ(RTC_INTR_FLAGS);
			mask &= (पंचांगp & RTC_IRQMASK) | RTC_IRQF;
			अगर (!use_hpet_alarm() || !is_पूर्णांकr(mask))
				अवरोध;

			/* क्रमce one-shot behavior अगर HPET blocked
			 * the wake alarm's irq
			 */
			rtc_update_irq(cmos->rtc, 1, mask);
			पंचांगp &= ~RTC_AIE;
			hpet_mask_rtc_irq_bit(RTC_AIE);
		पूर्ण जबतक (mask & RTC_AIE);

		अगर (पंचांगp & RTC_AIE)
			cmos_check_acpi_rtc_status(dev, &पंचांगp);
	पूर्ण
	spin_unlock_irq(&rtc_lock);

	dev_dbg(dev, "resume, ctrl %02x\n", पंचांगp);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cmos_pm_ops, cmos_suspend, cmos_resume);

/*----------------------------------------------------------------*/

/* On non-x86 प्रणालीs, a "CMOS" RTC lives most naturally on platक्रमm_bus.
 * ACPI प्रणालीs always list these as PNPACPI devices, and pre-ACPI PCs
 * probably list them in similar PNPBIOS tables; so PNP is more common.
 *
 * We करोn't use legacy "poke at the hardware" probing.  Ancient PCs that
 * predate even PNPBIOS should set up platक्रमm_bus devices.
 */

#अगर_घोषित	CONFIG_ACPI

#समावेश <linux/acpi.h>

अटल u32 rtc_handler(व्योम *context)
अणु
	काष्ठा device *dev = context;
	काष्ठा cmos_rtc *cmos = dev_get_drvdata(dev);
	अचिन्हित अक्षर rtc_control = 0;
	अचिन्हित अक्षर rtc_पूर्णांकr;
	अचिन्हित दीर्घ flags;


	/*
	 * Always update rtc irq when ACPI is used as RTC Alarm.
	 * Or अन्यथा, ACPI SCI is enabled during suspend/resume only,
	 * update rtc irq in that हाल.
	 */
	अगर (cmos_use_acpi_alarm())
		cmos_पूर्णांकerrupt(0, (व्योम *)cmos->rtc);
	अन्यथा अणु
		/* Fix me: can we use cmos_पूर्णांकerrupt() here as well? */
		spin_lock_irqsave(&rtc_lock, flags);
		अगर (cmos_rtc.suspend_ctrl)
			rtc_control = CMOS_READ(RTC_CONTROL);
		अगर (rtc_control & RTC_AIE) अणु
			cmos_rtc.suspend_ctrl &= ~RTC_AIE;
			CMOS_WRITE(rtc_control, RTC_CONTROL);
			rtc_पूर्णांकr = CMOS_READ(RTC_INTR_FLAGS);
			rtc_update_irq(cmos->rtc, 1, rtc_पूर्णांकr);
		पूर्ण
		spin_unlock_irqrestore(&rtc_lock, flags);
	पूर्ण

	pm_wakeup_hard_event(dev);
	acpi_clear_event(ACPI_EVENT_RTC);
	acpi_disable_event(ACPI_EVENT_RTC, 0);
	वापस ACPI_INTERRUPT_HANDLED;
पूर्ण

अटल अंतरभूत व्योम rtc_wake_setup(काष्ठा device *dev)
अणु
	acpi_install_fixed_event_handler(ACPI_EVENT_RTC, rtc_handler, dev);
	/*
	 * After the RTC handler is installed, the Fixed_RTC event should
	 * be disabled. Only when the RTC alarm is set will it be enabled.
	 */
	acpi_clear_event(ACPI_EVENT_RTC);
	acpi_disable_event(ACPI_EVENT_RTC, 0);
पूर्ण

अटल व्योम rtc_wake_on(काष्ठा device *dev)
अणु
	acpi_clear_event(ACPI_EVENT_RTC);
	acpi_enable_event(ACPI_EVENT_RTC, 0);
पूर्ण

अटल व्योम rtc_wake_off(काष्ठा device *dev)
अणु
	acpi_disable_event(ACPI_EVENT_RTC, 0);
पूर्ण

#अगर_घोषित CONFIG_X86
/* Enable use_acpi_alarm mode क्रम Intel platक्रमms no earlier than 2015 */
अटल व्योम use_acpi_alarm_quirks(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस;

	अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0))
		वापस;

	अगर (!is_hpet_enabled())
		वापस;

	अगर (dmi_get_bios_year() < 2015)
		वापस;

	use_acpi_alarm = true;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम use_acpi_alarm_quirks(व्योम) अणु पूर्ण
#पूर्ण_अगर

/* Every ACPI platक्रमm has a mc146818 compatible "cmos rtc".  Here we find
 * its device node and pass extra config data.  This helps its driver use
 * capabilities that the now-obsolete mc146818 didn't have, and inक्रमms it
 * that this board's RTC is wakeup-capable (per ACPI spec).
 */
अटल काष्ठा cmos_rtc_board_info acpi_rtc_info;

अटल व्योम cmos_wake_setup(काष्ठा device *dev)
अणु
	अगर (acpi_disabled)
		वापस;

	use_acpi_alarm_quirks();

	rtc_wake_setup(dev);
	acpi_rtc_info.wake_on = rtc_wake_on;
	acpi_rtc_info.wake_off = rtc_wake_off;

	/* workaround bug in some ACPI tables */
	अगर (acpi_gbl_FADT.month_alarm && !acpi_gbl_FADT.day_alarm) अणु
		dev_dbg(dev, "bogus FADT month_alarm (%d)\n",
			acpi_gbl_FADT.month_alarm);
		acpi_gbl_FADT.month_alarm = 0;
	पूर्ण

	acpi_rtc_info.rtc_day_alarm = acpi_gbl_FADT.day_alarm;
	acpi_rtc_info.rtc_mon_alarm = acpi_gbl_FADT.month_alarm;
	acpi_rtc_info.rtc_century = acpi_gbl_FADT.century;

	/* NOTE:  S4_RTC_WAKE is NOT currently useful to Linux */
	अगर (acpi_gbl_FADT.flags & ACPI_FADT_S4_RTC_WAKE)
		dev_info(dev, "RTC can wake from S4\n");

	dev->platक्रमm_data = &acpi_rtc_info;

	/* RTC always wakes from S1/S2/S3, and often S4/STD */
	device_init_wakeup(dev, 1);
पूर्ण

अटल व्योम cmos_check_acpi_rtc_status(काष्ठा device *dev,
				       अचिन्हित अक्षर *rtc_control)
अणु
	काष्ठा cmos_rtc *cmos = dev_get_drvdata(dev);
	acpi_event_status rtc_status;
	acpi_status status;

	अगर (acpi_gbl_FADT.flags & ACPI_FADT_FIXED_RTC)
		वापस;

	status = acpi_get_event_status(ACPI_EVENT_RTC, &rtc_status);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "Could not get RTC status\n");
	पूर्ण अन्यथा अगर (rtc_status & ACPI_EVENT_FLAG_SET) अणु
		अचिन्हित अक्षर mask;
		*rtc_control &= ~RTC_AIE;
		CMOS_WRITE(*rtc_control, RTC_CONTROL);
		mask = CMOS_READ(RTC_INTR_FLAGS);
		rtc_update_irq(cmos->rtc, 1, mask);
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम cmos_wake_setup(काष्ठा device *dev)
अणु
पूर्ण

अटल व्योम cmos_check_acpi_rtc_status(काष्ठा device *dev,
				       अचिन्हित अक्षर *rtc_control)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित	CONFIG_PNP

#समावेश <linux/pnp.h>

अटल पूर्णांक cmos_pnp_probe(काष्ठा pnp_dev *pnp, स्थिर काष्ठा pnp_device_id *id)
अणु
	cmos_wake_setup(&pnp->dev);

	अगर (pnp_port_start(pnp, 0) == 0x70 && !pnp_irq_valid(pnp, 0)) अणु
		अचिन्हित पूर्णांक irq = 0;
#अगर_घोषित CONFIG_X86
		/* Some machines contain a PNP entry क्रम the RTC, but
		 * करोn't define the IRQ. It should always be safe to
		 * hardcode it on प्रणालीs with a legacy PIC.
		 */
		अगर (nr_legacy_irqs())
			irq = RTC_IRQ;
#पूर्ण_अगर
		वापस cmos_करो_probe(&pnp->dev,
				pnp_get_resource(pnp, IORESOURCE_IO, 0), irq);
	पूर्ण अन्यथा अणु
		वापस cmos_करो_probe(&pnp->dev,
				pnp_get_resource(pnp, IORESOURCE_IO, 0),
				pnp_irq(pnp, 0));
	पूर्ण
पूर्ण

अटल व्योम cmos_pnp_हटाओ(काष्ठा pnp_dev *pnp)
अणु
	cmos_करो_हटाओ(&pnp->dev);
पूर्ण

अटल व्योम cmos_pnp_shutकरोwn(काष्ठा pnp_dev *pnp)
अणु
	काष्ठा device *dev = &pnp->dev;
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		पूर्णांक retval = cmos_घातeroff(dev);

		अगर (cmos_aie_घातeroff(dev) < 0 && !retval)
			वापस;
	पूर्ण

	cmos_करो_shutकरोwn(cmos->irq);
पूर्ण

अटल स्थिर काष्ठा pnp_device_id rtc_ids[] = अणु
	अणु .id = "PNP0b00", पूर्ण,
	अणु .id = "PNP0b01", पूर्ण,
	अणु .id = "PNP0b02", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pnp, rtc_ids);

अटल काष्ठा pnp_driver cmos_pnp_driver = अणु
	.name		= driver_name,
	.id_table	= rtc_ids,
	.probe		= cmos_pnp_probe,
	.हटाओ		= cmos_pnp_हटाओ,
	.shutकरोwn	= cmos_pnp_shutकरोwn,

	/* flag ensures resume() माला_लो called, and stops syslog spam */
	.flags		= PNP_DRIVER_RES_DO_NOT_CHANGE,
	.driver		= अणु
			.pm = &cmos_pm_ops,
	पूर्ण,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_PNP */

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_cmos_match[] = अणु
	अणु
		.compatible = "motorola,mc146818",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_cmos_match);

अटल __init व्योम cmos_of_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर __be32 *val;

	अगर (!node)
		वापस;

	val = of_get_property(node, "ctrl-reg", शून्य);
	अगर (val)
		CMOS_WRITE(be32_to_cpup(val), RTC_CONTROL);

	val = of_get_property(node, "freq-reg", शून्य);
	अगर (val)
		CMOS_WRITE(be32_to_cpup(val), RTC_FREQ_SELECT);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cmos_of_init(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
#पूर्ण_अगर
/*----------------------------------------------------------------*/

/* Platक्रमm setup should have set up an RTC device, when PNP is
 * unavailable ... this could happen even on (older) PCs.
 */

अटल पूर्णांक __init cmos_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *resource;
	पूर्णांक irq;

	cmos_of_init(pdev);
	cmos_wake_setup(&pdev->dev);

	अगर (RTC_IOMAPPED)
		resource = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अन्यथा
		resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		irq = -1;

	वापस cmos_करो_probe(&pdev->dev, resource, irq);
पूर्ण

अटल पूर्णांक cmos_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cmos_करो_हटाओ(&pdev->dev);
	वापस 0;
पूर्ण

अटल व्योम cmos_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cmos_rtc	*cmos = dev_get_drvdata(dev);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		पूर्णांक retval = cmos_घातeroff(dev);

		अगर (cmos_aie_घातeroff(dev) < 0 && !retval)
			वापस;
	पूर्ण

	cmos_करो_shutकरोwn(cmos->irq);
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:rtc_cmos");

अटल काष्ठा platक्रमm_driver cmos_platक्रमm_driver = अणु
	.हटाओ		= cmos_platक्रमm_हटाओ,
	.shutकरोwn	= cmos_platक्रमm_shutकरोwn,
	.driver = अणु
		.name		= driver_name,
		.pm		= &cmos_pm_ops,
		.of_match_table = of_match_ptr(of_cmos_match),
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल bool pnp_driver_रेजिस्टरed;
#पूर्ण_अगर
अटल bool platक्रमm_driver_रेजिस्टरed;

अटल पूर्णांक __init cmos_init(व्योम)
अणु
	पूर्णांक retval = 0;

#अगर_घोषित	CONFIG_PNP
	retval = pnp_रेजिस्टर_driver(&cmos_pnp_driver);
	अगर (retval == 0)
		pnp_driver_रेजिस्टरed = true;
#पूर्ण_अगर

	अगर (!cmos_rtc.dev) अणु
		retval = platक्रमm_driver_probe(&cmos_platक्रमm_driver,
					       cmos_platक्रमm_probe);
		अगर (retval == 0)
			platक्रमm_driver_रेजिस्टरed = true;
	पूर्ण

	अगर (retval == 0)
		वापस 0;

#अगर_घोषित	CONFIG_PNP
	अगर (pnp_driver_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&cmos_pnp_driver);
#पूर्ण_अगर
	वापस retval;
पूर्ण
module_init(cmos_init);

अटल व्योम __निकास cmos_निकास(व्योम)
अणु
#अगर_घोषित	CONFIG_PNP
	अगर (pnp_driver_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&cmos_pnp_driver);
#पूर्ण_अगर
	अगर (platक्रमm_driver_रेजिस्टरed)
		platक्रमm_driver_unरेजिस्टर(&cmos_platक्रमm_driver);
पूर्ण
module_निकास(cmos_निकास);


MODULE_AUTHOR("David Brownell");
MODULE_DESCRIPTION("Driver for PC-style 'CMOS' RTCs");
MODULE_LICENSE("GPL");
