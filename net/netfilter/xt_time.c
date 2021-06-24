<शैली गुरु>
/*
 *	xt_समय
 *	Copyright तऊ CC Computer Consultants GmbH, 2007
 *
 *	based on ipt_समय by Fabrice MARIE <fabrice@netfilter.org>
 *	This is a module which is used क्रम समय matching
 *	It is using some modअगरied code from dietlibc (स_स्थानीय() function)
 *	that you can find at https://www.fefe.de/dietlibc/
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from gnu.org/gpl.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_समय.स>

काष्ठा xपंचांग अणु
	u_पूर्णांक8_t month;    /* (1-12) */
	u_पूर्णांक8_t monthday; /* (1-31) */
	u_पूर्णांक8_t weekday;  /* (1-7) */
	u_पूर्णांक8_t hour;     /* (0-23) */
	u_पूर्णांक8_t minute;   /* (0-59) */
	u_पूर्णांक8_t second;   /* (0-59) */
	अचिन्हित पूर्णांक dse;
पूर्ण;

बाह्य काष्ठा समयzone sys_tz; /* ouch */

अटल स्थिर u_पूर्णांक16_t days_since_year[] = अणु
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
पूर्ण;

अटल स्थिर u_पूर्णांक16_t days_since_leapyear[] = अणु
	0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
पूर्ण;

/*
 * Since समय progresses क्रमward, it is best to organize this array in reverse,
 * to minimize lookup समय.
 */
क्रमागत अणु
	DSE_FIRST = 2039,
	SECONDS_PER_DAY = 86400,
पूर्ण;
अटल स्थिर u_पूर्णांक16_t days_since_epoch[] = अणु
	/* 2039 - 2030 */
	25202, 24837, 24472, 24106, 23741, 23376, 23011, 22645, 22280, 21915,
	/* 2029 - 2020 */
	21550, 21184, 20819, 20454, 20089, 19723, 19358, 18993, 18628, 18262,
	/* 2019 - 2010 */
	17897, 17532, 17167, 16801, 16436, 16071, 15706, 15340, 14975, 14610,
	/* 2009 - 2000 */
	14245, 13879, 13514, 13149, 12784, 12418, 12053, 11688, 11323, 10957,
	/* 1999 - 1990 */
	10592, 10227, 9862, 9496, 9131, 8766, 8401, 8035, 7670, 7305,
	/* 1989 - 1980 */
	6940, 6574, 6209, 5844, 5479, 5113, 4748, 4383, 4018, 3652,
	/* 1979 - 1970 */
	3287, 2922, 2557, 2191, 1826, 1461, 1096, 730, 365, 0,
पूर्ण;

अटल अंतरभूत bool is_leap(अचिन्हित पूर्णांक y)
अणु
	वापस y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
पूर्ण

/*
 * Each network packet has a (nano)seconds-since-the-epoch (SSTE) बारtamp.
 * Since we match against days and dayसमय, the SSTE value needs to be
 * computed back पूर्णांकo human-पढ़ोable dates.
 *
 * This is करोne in three separate functions so that the most expensive
 * calculations are करोne last, in हाल a "simple match" can be found earlier.
 */
अटल अंतरभूत अचिन्हित पूर्णांक स_स्थानीय_1(काष्ठा xपंचांग *r, समय64_t समय)
अणु
	अचिन्हित पूर्णांक v, w;

	/* Each day has 86400s, so finding the hour/minute is actually easy. */
	भाग_u64_rem(समय, SECONDS_PER_DAY, &v);
	r->second = v % 60;
	w         = v / 60;
	r->minute = w % 60;
	r->hour   = w / 60;
	वापस v;
पूर्ण

अटल अंतरभूत व्योम स_स्थानीय_2(काष्ठा xपंचांग *r, समय64_t समय)
अणु
	/*
	 * Here comes the rest (weekday, monthday). First, भागide the SSTE
	 * by seconds-per-day to get the number of _days_ since the epoch.
	 */
	r->dse = भाग_u64(समय, SECONDS_PER_DAY);

	/*
	 * 1970-01-01 (w=0) was a Thursday (4).
	 * -1 and +1 map Sunday properly onto 7.
	 */
	r->weekday = (4 + r->dse - 1) % 7 + 1;
पूर्ण

अटल व्योम स_स्थानीय_3(काष्ठा xपंचांग *r, समय64_t समय)
अणु
	अचिन्हित पूर्णांक year, i, w = r->dse;

	/*
	 * In each year, a certain number of days-since-the-epoch have passed.
	 * Find the year that is बंदst to said days.
	 *
	 * Consider, क्रम example, w=21612 (2029-03-04). Loop will पात on
	 * dse[i] <= w, which happens when dse[i] == 21550. This implies
	 * year == 2009. w will then be 62.
	 */
	क्रम (i = 0, year = DSE_FIRST; days_since_epoch[i] > w;
	    ++i, --year)
		/* just loop */;

	w -= days_since_epoch[i];

	/*
	 * By now we have the current year, and the day of the year.
	 * r->yearday = w;
	 *
	 * On to finding the month (like above). In each month, a certain
	 * number of days-since-New Year have passed, and find the बंदst
	 * one.
	 *
	 * Consider w=62 (in a non-leap year). Loop will पात on
	 * dsy[i] < w, which happens when dsy[i] == 31+28 (i == 2).
	 * Concludes i == 2, i.e. 3rd month => March.
	 *
	 * (A dअगरferent approach to use would be to subtract a monthlength
	 * from w repeatedly जबतक counting.)
	 */
	अगर (is_leap(year)) अणु
		/* use days_since_leapyear[] in a leap year */
		क्रम (i = ARRAY_SIZE(days_since_leapyear) - 1;
		    i > 0 && days_since_leapyear[i] > w; --i)
			/* just loop */;
		r->monthday = w - days_since_leapyear[i] + 1;
	पूर्ण अन्यथा अणु
		क्रम (i = ARRAY_SIZE(days_since_year) - 1;
		    i > 0 && days_since_year[i] > w; --i)
			/* just loop */;
		r->monthday = w - days_since_year[i] + 1;
	पूर्ण

	r->month    = i + 1;
पूर्ण

अटल bool
समय_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_समय_info *info = par->matchinfo;
	अचिन्हित पूर्णांक packet_समय;
	काष्ठा xपंचांग current_समय;
	समय64_t stamp;

	/*
	 * We need real समय here, but we can neither use skb->tstamp
	 * nor __net_बारtamp().
	 *
	 * skb->tstamp and skb->skb_mstamp_ns overlap, however, they
	 * use dअगरferent घड़ी types (real vs monotonic).
	 *
	 * Suppose you have two rules:
	 *	1. match beक्रमe 13:00
	 *	2. match after 13:00
	 *
	 * If you match against processing समय (kसमय_get_real_seconds) it
	 * may happen that the same packet matches both rules अगर
	 * it arrived at the right moment beक्रमe 13:00, so it would be
	 * better to check skb->tstamp and set it via __net_बारtamp()
	 * अगर needed.  This however अवरोधs outgoing packets tx बारtamp,
	 * and causes them to get delayed क्रमever by fq packet scheduler.
	 */
	stamp = kसमय_get_real_seconds();

	अगर (info->flags & XT_TIME_LOCAL_TZ)
		/* Adjust क्रम local समयzone */
		stamp -= 60 * sys_tz.tz_minuteswest;

	/*
	 * xt_समय will match when _all_ of the following hold:
	 *   - 'now' is in the global समय range date_start..date_end
	 *   - 'now' is in the monthday mask
	 *   - 'now' is in the weekday mask
	 *   - 'now' is in the dayसमय range समय_start..समय_end
	 * (and by शेष, libxt_समय will set these so as to match)
	 *
	 * note: info->date_start/stop are अचिन्हित 32-bit values that
	 *	 can hold values beyond y2038, but not after y2106.
	 */

	अगर (stamp < info->date_start || stamp > info->date_stop)
		वापस false;

	packet_समय = स_स्थानीय_1(&current_समय, stamp);

	अगर (info->dayसमय_start < info->dayसमय_stop) अणु
		अगर (packet_समय < info->dayसमय_start ||
		    packet_समय > info->dayसमय_stop)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (packet_समय < info->dayसमय_start &&
		    packet_समय > info->dayसमय_stop)
			वापस false;

		/** अगर user asked to ignore 'next day', then e.g.
		 *  '1 PM Wed, August 1st' should be treated
		 *  like 'Tue 1 PM July 31st'.
		 *
		 * This also causes
		 * 'Monday, "23:00 to 01:00", to match क्रम 2 hours, starting
		 * Monday 23:00 to Tuesday 01:00.
		 */
		अगर ((info->flags & XT_TIME_CONTIGUOUS) &&
		     packet_समय <= info->dayसमय_stop)
			stamp -= SECONDS_PER_DAY;
	पूर्ण

	स_स्थानीय_2(&current_समय, stamp);

	अगर (!(info->weekdays_match & (1 << current_समय.weekday)))
		वापस false;

	/* Do not spend समय computing monthday अगर all days match anyway */
	अगर (info->monthdays_match != XT_TIME_ALL_MONTHDAYS) अणु
		स_स्थानीय_3(&current_समय, stamp);
		अगर (!(info->monthdays_match & (1 << current_समय.monthday)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक समय_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_समय_info *info = par->matchinfo;

	अगर (info->dayसमय_start > XT_TIME_MAX_DAYTIME ||
	    info->dayसमय_stop > XT_TIME_MAX_DAYTIME) अणु
		pr_info_ratelimited("invalid argument - start or stop time greater than 23:59:59\n");
		वापस -गलत_तर्क;
	पूर्ण

	अगर (info->flags & ~XT_TIME_ALL_FLAGS) अणु
		pr_info_ratelimited("unknown flags 0x%x\n",
				    info->flags & ~XT_TIME_ALL_FLAGS);
		वापस -EINVAL;
	पूर्ण

	अगर ((info->flags & XT_TIME_CONTIGUOUS) &&
	     info->dayसमय_start < info->dayसमय_stop)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा xt_match xt_समय_mt_reg __पढ़ो_mostly = अणु
	.name       = "time",
	.family     = NFPROTO_UNSPEC,
	.match      = समय_mt,
	.checkentry = समय_mt_check,
	.matchsize  = माप(काष्ठा xt_समय_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init समय_mt_init(व्योम)
अणु
	पूर्णांक minutes = sys_tz.tz_minuteswest;

	अगर (minutes < 0) /* east of Greenwich */
		pr_info("kernel timezone is +%02d%02d\n",
			-minutes / 60, -minutes % 60);
	अन्यथा /* west of Greenwich */
		pr_info("kernel timezone is -%02d%02d\n",
			minutes / 60, minutes % 60);

	वापस xt_रेजिस्टर_match(&xt_समय_mt_reg);
पूर्ण

अटल व्योम __निकास समय_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_समय_mt_reg);
पूर्ण

module_init(समय_mt_init);
module_निकास(समय_mt_निकास);
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: time-based matching");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_time");
MODULE_ALIAS("ip6t_time");
