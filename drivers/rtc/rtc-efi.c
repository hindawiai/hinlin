<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rtc-efi: RTC Class Driver क्रम EFI-based प्रणालीs
 *
 * Copyright (C) 2009 Hewlett-Packard Development Company, L.P.
 *
 * Author: dann frazier <dannf@dannf.org>
 * Based on efirtc.c by Stephane Eranian
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/समय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/efi.h>

#घोषणा EFI_ISDST (EFI_TIME_ADJUST_DAYLIGHT|EFI_TIME_IN_DAYLIGHT)

/*
 * वापसs day of the year [0-365]
 */
अटल अंतरभूत पूर्णांक
compute_yday(efi_समय_प्रकार *eft)
अणु
	/* efi_समय_प्रकार.month is in the [1-12] so, we need -1 */
	वापस rtc_year_days(eft->day, eft->month - 1, eft->year);
पूर्ण

/*
 * वापसs day of the week [0-6] 0=Sunday
 */
अटल पूर्णांक
compute_wday(efi_समय_प्रकार *eft, पूर्णांक yday)
अणु
	पूर्णांक ndays = eft->year * (365 % 7)
		    + (eft->year - 1) / 4
		    - (eft->year - 1) / 100
		    + (eft->year - 1) / 400
		    + yday;

	/*
	 * 1/1/0000 may or may not have been a Sunday (अगर it ever existed at
	 * all) but assuming it was makes this calculation work correctly.
	 */
	वापस ndays % 7;
पूर्ण

अटल व्योम
convert_to_efi_समय(काष्ठा rtc_समय *wसमय, efi_समय_प्रकार *eft)
अणु
	eft->year	= wसमय->पंचांग_year + 1900;
	eft->month	= wसमय->पंचांग_mon + 1;
	eft->day	= wसमय->पंचांग_mday;
	eft->hour	= wसमय->पंचांग_hour;
	eft->minute	= wसमय->पंचांग_min;
	eft->second	= wसमय->पंचांग_sec;
	eft->nanosecond = 0;
	eft->daylight	= wसमय->पंचांग_isdst ? EFI_ISDST : 0;
	eft->समयzone	= EFI_UNSPECIFIED_TIMEZONE;
पूर्ण

अटल bool
convert_from_efi_समय(efi_समय_प्रकार *eft, काष्ठा rtc_समय *wसमय)
अणु
	स_रखो(wसमय, 0, माप(*wसमय));

	अगर (eft->second >= 60)
		वापस false;
	wसमय->पंचांग_sec  = eft->second;

	अगर (eft->minute >= 60)
		वापस false;
	wसमय->पंचांग_min  = eft->minute;

	अगर (eft->hour >= 24)
		वापस false;
	wसमय->पंचांग_hour = eft->hour;

	अगर (!eft->day || eft->day > 31)
		वापस false;
	wसमय->पंचांग_mday = eft->day;

	अगर (!eft->month || eft->month > 12)
		वापस false;
	wसमय->पंचांग_mon  = eft->month - 1;

	अगर (eft->year < 1900 || eft->year > 9999)
		वापस false;
	wसमय->पंचांग_year = eft->year - 1900;

	/* day in the year [1-365]*/
	wसमय->पंचांग_yday = compute_yday(eft);

	/* day of the week [0-6], Sunday=0 */
	wसमय->पंचांग_wday = compute_wday(eft, wसमय->पंचांग_yday);

	चयन (eft->daylight & EFI_ISDST) अणु
	हाल EFI_ISDST:
		wसमय->पंचांग_isdst = 1;
		अवरोध;
	हाल EFI_TIME_ADJUST_DAYLIGHT:
		wसमय->पंचांग_isdst = 0;
		अवरोध;
	शेष:
		wसमय->पंचांग_isdst = -1;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक efi_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	efi_समय_प्रकार eft;
	efi_status_t status;

	/*
	 * As of EFI v1.10, this call always वापसs an unsupported status
	 */
	status = efi.get_wakeup_समय((efi_bool_t *)&wkalrm->enabled,
				     (efi_bool_t *)&wkalrm->pending, &eft);

	अगर (status != EFI_SUCCESS)
		वापस -EINVAL;

	अगर (!convert_from_efi_समय(&eft, &wkalrm->समय))
		वापस -EIO;

	वापस rtc_valid_पंचांग(&wkalrm->समय);
पूर्ण

अटल पूर्णांक efi_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	efi_समय_प्रकार eft;
	efi_status_t status;

	convert_to_efi_समय(&wkalrm->समय, &eft);

	/*
	 * XXX Fixme:
	 * As of EFI 0.92 with the firmware I have on my
	 * machine this call करोes not seem to work quite
	 * right
	 *
	 * As of v1.10, this call always वापसs an unsupported status
	 */
	status = efi.set_wakeup_समय((efi_bool_t)wkalrm->enabled, &eft);

	dev_warn(dev, "write status is %d\n", (पूर्णांक)status);

	वापस status == EFI_SUCCESS ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक efi_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	efi_status_t status;
	efi_समय_प्रकार eft;
	efi_समय_cap_t cap;

	status = efi.get_समय(&eft, &cap);

	अगर (status != EFI_SUCCESS) अणु
		/* should never happen */
		dev_err(dev, "can't read time\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!convert_from_efi_समय(&eft, पंचांग))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक efi_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	efi_status_t status;
	efi_समय_प्रकार eft;

	convert_to_efi_समय(पंचांग, &eft);

	status = efi.set_समय(&eft);

	वापस status == EFI_SUCCESS ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक efi_procfs(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	efi_समय_प्रकार      eft, alm;
	efi_समय_cap_t  cap;
	efi_bool_t      enabled, pending;

	स_रखो(&eft, 0, माप(eft));
	स_रखो(&alm, 0, माप(alm));
	स_रखो(&cap, 0, माप(cap));

	efi.get_समय(&eft, &cap);
	efi.get_wakeup_समय(&enabled, &pending, &alm);

	seq_म_लिखो(seq,
		   "Time\t\t: %u:%u:%u.%09u\n"
		   "Date\t\t: %u-%u-%u\n"
		   "Daylight\t: %u\n",
		   eft.hour, eft.minute, eft.second, eft.nanosecond,
		   eft.year, eft.month, eft.day,
		   eft.daylight);

	अगर (eft.समयzone == EFI_UNSPECIFIED_TIMEZONE)
		seq_माला_दो(seq, "Timezone\t: unspecified\n");
	अन्यथा
		/* XXX fixme: convert to string? */
		seq_म_लिखो(seq, "Timezone\t: %u\n", eft.समयzone);

	seq_म_लिखो(seq,
		   "Alarm Time\t: %u:%u:%u.%09u\n"
		   "Alarm Date\t: %u-%u-%u\n"
		   "Alarm Daylight\t: %u\n"
		   "Enabled\t\t: %s\n"
		   "Pending\t\t: %s\n",
		   alm.hour, alm.minute, alm.second, alm.nanosecond,
		   alm.year, alm.month, alm.day,
		   alm.daylight,
		   enabled == 1 ? "yes" : "no",
		   pending == 1 ? "yes" : "no");

	अगर (eft.समयzone == EFI_UNSPECIFIED_TIMEZONE)
		seq_माला_दो(seq, "Timezone\t: unspecified\n");
	अन्यथा
		/* XXX fixme: convert to string? */
		seq_म_लिखो(seq, "Timezone\t: %u\n", alm.समयzone);

	/*
	 * now prपूर्णांकs the capabilities
	 */
	seq_म_लिखो(seq,
		   "Resolution\t: %u\n"
		   "Accuracy\t: %u\n"
		   "SetstoZero\t: %u\n",
		   cap.resolution, cap.accuracy, cap.sets_to_zero);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops efi_rtc_ops = अणु
	.पढ़ो_समय	= efi_पढ़ो_समय,
	.set_समय	= efi_set_समय,
	.पढ़ो_alarm	= efi_पढ़ो_alarm,
	.set_alarm	= efi_set_alarm,
	.proc		= efi_procfs,
पूर्ण;

अटल पूर्णांक __init efi_rtc_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rtc_device *rtc;
	efi_समय_प्रकार eft;
	efi_समय_cap_t cap;

	/* First check अगर the RTC is usable */
	अगर (efi.get_समय(&eft, &cap) != EFI_SUCCESS)
		वापस -ENODEV;

	rtc = devm_rtc_device_रेजिस्टर(&dev->dev, "rtc-efi", &efi_rtc_ops,
					THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->uie_unsupported = 1;
	platक्रमm_set_drvdata(dev, rtc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver efi_rtc_driver = अणु
	.driver = अणु
		.name = "rtc-efi",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(efi_rtc_driver, efi_rtc_probe);

MODULE_ALIAS("platform:rtc-efi");
MODULE_AUTHOR("dann frazier <dannf@dannf.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("EFI RTC driver");
MODULE_ALIAS("platform:rtc-efi");
