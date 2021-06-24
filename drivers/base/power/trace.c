<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/trace.c
 *
 * Copyright (C) 2006 Linus Torvalds
 *
 * Trace facility क्रम suspend/resume problems, when none of the
 * devices may be working.
 */
#घोषणा pr_fmt(fmt) "PM: " fmt

#समावेश <linux/pm-trace.h>
#समावेश <linux/export.h>
#समावेश <linux/rtc.h>
#समावेश <linux/suspend.h>

#समावेश <linux/mc146818rtc.h>

#समावेश "power.h"

/*
 * Horrid, horrid, horrid.
 *
 * It turns out that the _only_ piece of hardware that actually
 * keeps its value across a hard boot (and, more importantly, the
 * POST init sequence) is literally the realसमय घड़ी.
 *
 * Never mind that an RTC chip has 114 bytes (and often a whole
 * other bank of an additional 128 bytes) of nice SRAM that is
 * _deचिन्हित_ to keep data - the POST will clear it. So we literally
 * can just use the few bytes of actual समय data, which means that
 * we're really limited.
 *
 * It means, क्रम example, that we can't use the seconds at all
 * (since the समय between the hang and the boot might be more
 * than a minute), and we'd better not depend on the low bits of
 * the minutes either.
 *
 * There are the wday fields etc, but I wouldn't guarantee those
 * are dependable either. And अगर the date isn't valid, either the
 * hw or POST will करो strange things.
 *
 * So we're left with:
 *  - year: 0-99
 *  - month: 0-11
 *  - day-of-month: 1-28
 *  - hour: 0-23
 *  - min: (0-30)*2
 *
 * Giving us a total range of 0-16128000 (0xf61800), ie less
 * than 24 bits of actual data we can save across reboots.
 *
 * And अगर your box can't boot in less than three minutes,
 * you're screwed.
 *
 * Now, almost 24 bits of data is pitअगरully small, so we need
 * to be pretty dense अगर we want to use it क्रम anything nice.
 * What we करो is that instead of saving off nice पढ़ोable info,
 * we save off _hashes_ of inक्रमmation that we can hopefully
 * regenerate after the reboot.
 *
 * In particular, this means that we might be unlucky, and hit
 * a हाल where we have a hash collision, and we end up not
 * being able to tell क्रम certain exactly which हाल happened.
 * But that's hopefully unlikely.
 *
 * What we करो is to take the bits we can fit, and split them
 * पूर्णांकo three parts (16*997*1009 = 16095568), and use the values
 * क्रम:
 *  - 0-15: user-settable
 *  - 0-996: file + line number
 *  - 0-1008: device
 */
#घोषणा USERHASH (16)
#घोषणा खाताHASH (997)
#घोषणा DEVHASH (1009)

#घोषणा DEVSEED (7919)

bool pm_trace_rtc_abused __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(pm_trace_rtc_abused);

अटल अचिन्हित पूर्णांक dev_hash_value;

अटल पूर्णांक set_magic_समय(अचिन्हित पूर्णांक user, अचिन्हित पूर्णांक file, अचिन्हित पूर्णांक device)
अणु
	अचिन्हित पूर्णांक n = user + USERHASH*(file + खाताHASH*device);

	// June 7th, 2006
	अटल काष्ठा rtc_समय समय = अणु
		.पंचांग_sec = 0,
		.पंचांग_min = 0,
		.पंचांग_hour = 0,
		.पंचांग_mday = 7,
		.पंचांग_mon = 5,	// June - counting from zero
		.पंचांग_year = 106,
		.पंचांग_wday = 3,
		.पंचांग_yday = 160,
		.पंचांग_isdst = 1
	पूर्ण;

	समय.पंचांग_year = (n % 100);
	n /= 100;
	समय.पंचांग_mon = (n % 12);
	n /= 12;
	समय.पंचांग_mday = (n % 28) + 1;
	n /= 28;
	समय.पंचांग_hour = (n % 24);
	n /= 24;
	समय.पंचांग_min = (n % 20) * 3;
	n /= 20;
	mc146818_set_समय(&समय);
	pm_trace_rtc_abused = true;
	वापस n ? -1 : 0;
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो_magic_समय(व्योम)
अणु
	काष्ठा rtc_समय समय;
	अचिन्हित पूर्णांक val;

	mc146818_get_समय(&समय);
	pr_info("RTC time: %ptRt, date: %ptRd\n", &समय, &समय);
	val = समय.पंचांग_year;				/* 100 years */
	अगर (val > 100)
		val -= 100;
	val += समय.पंचांग_mon * 100;			/* 12 months */
	val += (समय.पंचांग_mday-1) * 100 * 12;		/* 28 month-days */
	val += समय.पंचांग_hour * 100 * 12 * 28;		/* 24 hours */
	val += (समय.पंचांग_min / 3) * 100 * 12 * 28 * 24;	/* 20 3-minute पूर्णांकervals */
	वापस val;
पूर्ण

/*
 * This is just the sdbm hash function with a user-supplied
 * seed and final size parameter.
 */
अटल अचिन्हित पूर्णांक hash_string(अचिन्हित पूर्णांक seed, स्थिर अक्षर *data, अचिन्हित पूर्णांक mod)
अणु
	अचिन्हित अक्षर c;
	जबतक ((c = *data++) != 0) अणु
		seed = (seed << 16) + (seed << 6) - seed + c;
	पूर्ण
	वापस seed % mod;
पूर्ण

व्योम set_trace_device(काष्ठा device *dev)
अणु
	dev_hash_value = hash_string(DEVSEED, dev_name(dev), DEVHASH);
पूर्ण
EXPORT_SYMBOL(set_trace_device);

/*
 * We could just take the "tracedata" index पूर्णांकo the .tracedata
 * section instead. Generating a hash of the data gives us a
 * chance to work across kernel versions, and perhaps more
 * importantly it also gives us valid/invalid check (ie we will
 * likely not give totally bogus reports - अगर the hash matches,
 * it's not any guarantee, but it's a high _likelihood_ that
 * the match is valid).
 */
व्योम generate_pm_trace(स्थिर व्योम *tracedata, अचिन्हित पूर्णांक user)
अणु
	अचिन्हित लघु lineno = *(अचिन्हित लघु *)tracedata;
	स्थिर अक्षर *file = *(स्थिर अक्षर **)(tracedata + 2);
	अचिन्हित पूर्णांक user_hash_value, file_hash_value;

	user_hash_value = user % USERHASH;
	file_hash_value = hash_string(lineno, file, खाताHASH);
	set_magic_समय(user_hash_value, file_hash_value, dev_hash_value);
पूर्ण
EXPORT_SYMBOL(generate_pm_trace);

बाह्य अक्षर __tracedata_start[], __tracedata_end[];
अटल पूर्णांक show_file_hash(अचिन्हित पूर्णांक value)
अणु
	पूर्णांक match;
	अक्षर *tracedata;

	match = 0;
	क्रम (tracedata = __tracedata_start ; tracedata < __tracedata_end ;
			tracedata += 2 + माप(अचिन्हित दीर्घ)) अणु
		अचिन्हित लघु lineno = *(अचिन्हित लघु *)tracedata;
		स्थिर अक्षर *file = *(स्थिर अक्षर **)(tracedata + 2);
		अचिन्हित पूर्णांक hash = hash_string(lineno, file, खाताHASH);
		अगर (hash != value)
			जारी;
		pr_info("  hash matches %s:%u\n", file, lineno);
		match++;
	पूर्ण
	वापस match;
पूर्ण

अटल पूर्णांक show_dev_hash(अचिन्हित पूर्णांक value)
अणु
	पूर्णांक match = 0;
	काष्ठा list_head *entry;

	device_pm_lock();
	entry = dpm_list.prev;
	जबतक (entry != &dpm_list) अणु
		काष्ठा device * dev = to_device(entry);
		अचिन्हित पूर्णांक hash = hash_string(DEVSEED, dev_name(dev), DEVHASH);
		अगर (hash == value) अणु
			dev_info(dev, "hash matches\n");
			match++;
		पूर्ण
		entry = entry->prev;
	पूर्ण
	device_pm_unlock();
	वापस match;
पूर्ण

अटल अचिन्हित पूर्णांक hash_value_early_पढ़ो;

पूर्णांक show_trace_dev_match(अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक value = hash_value_early_पढ़ो / (USERHASH * खाताHASH);
	पूर्णांक ret = 0;
	काष्ठा list_head *entry;

	/*
	 * It's possible that multiple devices will match the hash and we can't
	 * tell which is the culprit, so it's best to output them all.
	 */
	device_pm_lock();
	entry = dpm_list.prev;
	जबतक (size && entry != &dpm_list) अणु
		काष्ठा device *dev = to_device(entry);
		अचिन्हित पूर्णांक hash = hash_string(DEVSEED, dev_name(dev),
						DEVHASH);
		अगर (hash == value) अणु
			पूर्णांक len = snम_लिखो(buf, size, "%s\n",
					    dev_driver_string(dev));
			अगर (len > size)
				len = size;
			buf += len;
			ret += len;
			size -= len;
		पूर्ण
		entry = entry->prev;
	पूर्ण
	device_pm_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक
pm_trace_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ mode, व्योम *_unused)
अणु
	चयन (mode) अणु
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_SUSPEND:
		अगर (pm_trace_rtc_abused) अणु
			pm_trace_rtc_abused = false;
			pr_warn("Possible incorrect RTC due to pm_trace, please use 'ntpdate' or 'rdate' to reset it.\n");
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block pm_trace_nb = अणु
	.notअगरier_call = pm_trace_notअगरy,
पूर्ण;

अटल पूर्णांक __init early_resume_init(व्योम)
अणु
	hash_value_early_पढ़ो = पढ़ो_magic_समय();
	रेजिस्टर_pm_notअगरier(&pm_trace_nb);
	वापस 0;
पूर्ण

अटल पूर्णांक __init late_resume_init(व्योम)
अणु
	अचिन्हित पूर्णांक val = hash_value_early_पढ़ो;
	अचिन्हित पूर्णांक user, file, dev;

	user = val % USERHASH;
	val = val / USERHASH;
	file = val % खाताHASH;
	val = val / खाताHASH;
	dev = val /* % DEVHASH */;

	pr_info("  Magic number: %d:%d:%d\n", user, file, dev);
	show_file_hash(file);
	show_dev_hash(dev);
	वापस 0;
पूर्ण

core_initcall(early_resume_init);
late_initcall(late_resume_init);
