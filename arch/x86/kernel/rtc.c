<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC related functions
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/acpi.h>
#समावेश <linux/bcd.h>
#समावेश <linux/export.h>
#समावेश <linux/pnp.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/vsyscall.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पूर्णांकel-mid.h>
#समावेश <यंत्र/setup.h>

#अगर_घोषित CONFIG_X86_32
/*
 * This is a special lock that is owned by the CPU and holds the index
 * रेजिस्टर we are working with.  It is required क्रम NMI access to the
 * CMOS/RTC रेजिस्टरs.  See include/यंत्र-i386/mc146818rtc.h क्रम details.
 */
अस्थिर अचिन्हित दीर्घ cmos_lock;
EXPORT_SYMBOL(cmos_lock);
#पूर्ण_अगर /* CONFIG_X86_32 */

/* For two digit years assume समय is always after that */
#घोषणा CMOS_YEARS_OFFS 2000

DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);

/*
 * In order to set the CMOS घड़ी precisely, set_rtc_mmss has to be
 * called 500 ms after the second nowसमय has started, because when
 * nowसमय is written पूर्णांकo the रेजिस्टरs of the CMOS घड़ी, it will
 * jump to the next second precisely 500 ms later. Check the Motorola
 * MC146818A or Dallas DS12887 data sheet क्रम details.
 */
पूर्णांक mach_set_rtc_mmss(स्थिर काष्ठा बारpec64 *now)
अणु
	अचिन्हित दीर्घ दीर्घ nowसमय = now->tv_sec;
	काष्ठा rtc_समय पंचांग;
	पूर्णांक retval = 0;

	rtc_समय64_to_पंचांग(nowसमय, &पंचांग);
	अगर (!rtc_valid_पंचांग(&पंचांग)) अणु
		retval = mc146818_set_समय(&पंचांग);
		अगर (retval)
			prपूर्णांकk(KERN_ERR "%s: RTC write failed with error %d\n",
			       __func__, retval);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR
		       "%s: Invalid RTC value: write of %llx to RTC failed\n",
			__func__, nowसमय);
		retval = -EINVAL;
	पूर्ण
	वापस retval;
पूर्ण

व्योम mach_get_cmos_समय(काष्ठा बारpec64 *now)
अणु
	अचिन्हित पूर्णांक status, year, mon, day, hour, min, sec, century = 0;
	अचिन्हित दीर्घ flags;

	/*
	 * If pm_trace abused the RTC as storage, set the बारpec to 0,
	 * which tells the caller that this RTC value is unusable.
	 */
	अगर (!pm_trace_rtc_valid()) अणु
		now->tv_sec = now->tv_nsec = 0;
		वापस;
	पूर्ण

	spin_lock_irqsave(&rtc_lock, flags);

	/*
	 * If UIP is clear, then we have >= 244 microseconds beक्रमe
	 * RTC रेजिस्टरs will be updated.  Spec sheet says that this
	 * is the reliable way to पढ़ो RTC - रेजिस्टरs. If UIP is set
	 * then the रेजिस्टर access might be invalid.
	 */
	जबतक ((CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP))
		cpu_relax();

	sec = CMOS_READ(RTC_SECONDS);
	min = CMOS_READ(RTC_MINUTES);
	hour = CMOS_READ(RTC_HOURS);
	day = CMOS_READ(RTC_DAY_OF_MONTH);
	mon = CMOS_READ(RTC_MONTH);
	year = CMOS_READ(RTC_YEAR);

#अगर_घोषित CONFIG_ACPI
	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    acpi_gbl_FADT.century)
		century = CMOS_READ(acpi_gbl_FADT.century);
#पूर्ण_अगर

	status = CMOS_READ(RTC_CONTROL);
	WARN_ON_ONCE(RTC_ALWAYS_BCD && (status & RTC_DM_BINARY));

	spin_unlock_irqrestore(&rtc_lock, flags);

	अगर (RTC_ALWAYS_BCD || !(status & RTC_DM_BINARY)) अणु
		sec = bcd2bin(sec);
		min = bcd2bin(min);
		hour = bcd2bin(hour);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		year = bcd2bin(year);
	पूर्ण

	अगर (century) अणु
		century = bcd2bin(century);
		year += century * 100;
	पूर्ण अन्यथा
		year += CMOS_YEARS_OFFS;

	now->tv_sec = स_गढ़ो64(year, mon, day, hour, min, sec);
	now->tv_nsec = 0;
पूर्ण

/* Routines क्रम accessing the CMOS RAM/RTC. */
अचिन्हित अक्षर rtc_cmos_पढ़ो(अचिन्हित अक्षर addr)
अणु
	अचिन्हित अक्षर val;

	lock_cmos_prefix(addr);
	outb(addr, RTC_PORT(0));
	val = inb(RTC_PORT(1));
	lock_cmos_suffix(addr);

	वापस val;
पूर्ण
EXPORT_SYMBOL(rtc_cmos_पढ़ो);

व्योम rtc_cmos_ग_लिखो(अचिन्हित अक्षर val, अचिन्हित अक्षर addr)
अणु
	lock_cmos_prefix(addr);
	outb(addr, RTC_PORT(0));
	outb(val, RTC_PORT(1));
	lock_cmos_suffix(addr);
पूर्ण
EXPORT_SYMBOL(rtc_cmos_ग_लिखो);

पूर्णांक update_persistent_घड़ी64(काष्ठा बारpec64 now)
अणु
	वापस x86_platक्रमm.set_wallघड़ी(&now);
पूर्ण

/* not अटल: needed by APM */
व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	x86_platक्रमm.get_wallघड़ी(ts);
पूर्ण


अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= RTC_PORT(0),
		.end	= RTC_PORT(1),
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start	= RTC_IRQ,
		.end	= RTC_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "rtc_cmos",
	.id		= -1,
	.resource	= rtc_resources,
	.num_resources	= ARRAY_SIZE(rtc_resources),
पूर्ण;

अटल __init पूर्णांक add_rtc_cmos(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अटल स्थिर अक्षर * स्थिर ids[] __initस्थिर =
	    अणु "PNP0b00", "PNP0b01", "PNP0b02", पूर्ण;
	काष्ठा pnp_dev *dev;
	काष्ठा pnp_id *id;
	पूर्णांक i;

	pnp_क्रम_each_dev(dev) अणु
		क्रम (id = dev->id; id; id = id->next) अणु
			क्रम (i = 0; i < ARRAY_SIZE(ids); i++) अणु
				अगर (compare_pnp_id(id, ids[i]) != 0)
					वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (!x86_platक्रमm.legacy.rtc)
		वापस -ENODEV;

	platक्रमm_device_रेजिस्टर(&rtc_device);
	dev_info(&rtc_device.dev,
		 "registered platform RTC device (no PNP device found)\n");

	वापस 0;
पूर्ण
device_initcall(add_rtc_cmos);
