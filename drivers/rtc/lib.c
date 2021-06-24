<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rtc and date/समय utility functions
 *
 * Copyright (C) 2005-06 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * based on arch/arm/common/rtस_समय.c and other bits
 */

#समावेश <linux/export.h>
#समावेश <linux/rtc.h>

अटल स्थिर अचिन्हित अक्षर rtc_days_in_month[] = अणु
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
पूर्ण;

अटल स्थिर अचिन्हित लघु rtc_ydays[2][13] = अणु
	/* Normal years */
	अणु 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 पूर्ण,
	/* Leap years */
	अणु 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 पूर्ण
पूर्ण;

#घोषणा LEAPS_THRU_END_OF(y) ((y) / 4 - (y) / 100 + (y) / 400)

/*
 * The number of days in the month.
 */
पूर्णांक rtc_month_days(अचिन्हित पूर्णांक month, अचिन्हित पूर्णांक year)
अणु
	वापस rtc_days_in_month[month] + (is_leap_year(year) && month == 1);
पूर्ण
EXPORT_SYMBOL(rtc_month_days);

/*
 * The number of days since January 1. (0 to 365)
 */
पूर्णांक rtc_year_days(अचिन्हित पूर्णांक day, अचिन्हित पूर्णांक month, अचिन्हित पूर्णांक year)
अणु
	वापस rtc_ydays[is_leap_year(year)][month] + day - 1;
पूर्ण
EXPORT_SYMBOL(rtc_year_days);

/*
 * rtc_समय64_to_पंचांग - Converts समय64_t to rtc_समय.
 * Convert seconds since 01-01-1970 00:00:00 to Gregorian date.
 */
व्योम rtc_समय64_to_पंचांग(समय64_t समय, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित पूर्णांक month, year, secs;
	पूर्णांक days;

	/* समय must be positive */
	days = भाग_s64_rem(समय, 86400, &secs);

	/* day of the week, 1970-01-01 was a Thursday */
	पंचांग->पंचांग_wday = (days + 4) % 7;

	year = 1970 + days / 365;
	days -= (year - 1970) * 365
		+ LEAPS_THRU_END_OF(year - 1)
		- LEAPS_THRU_END_OF(1970 - 1);
	जबतक (days < 0) अणु
		year -= 1;
		days += 365 + is_leap_year(year);
	पूर्ण
	पंचांग->पंचांग_year = year - 1900;
	पंचांग->पंचांग_yday = days + 1;

	क्रम (month = 0; month < 11; month++) अणु
		पूर्णांक newdays;

		newdays = days - rtc_month_days(month, year);
		अगर (newdays < 0)
			अवरोध;
		days = newdays;
	पूर्ण
	पंचांग->पंचांग_mon = month;
	पंचांग->पंचांग_mday = days + 1;

	पंचांग->पंचांग_hour = secs / 3600;
	secs -= पंचांग->पंचांग_hour * 3600;
	पंचांग->पंचांग_min = secs / 60;
	पंचांग->पंचांग_sec = secs - पंचांग->पंचांग_min * 60;

	पंचांग->पंचांग_isdst = 0;
पूर्ण
EXPORT_SYMBOL(rtc_समय64_to_पंचांग);

/*
 * Does the rtc_समय represent a valid date/समय?
 */
पूर्णांक rtc_valid_पंचांग(काष्ठा rtc_समय *पंचांग)
अणु
	अगर (पंचांग->पंचांग_year < 70 ||
	    पंचांग->पंचांग_year > (पूर्णांक_उच्च - 1900) ||
	    ((अचिन्हित पूर्णांक)पंचांग->पंचांग_mon) >= 12 ||
	    पंचांग->पंचांग_mday < 1 ||
	    पंचांग->पंचांग_mday > rtc_month_days(पंचांग->पंचांग_mon,
					 ((अचिन्हित पूर्णांक)पंचांग->पंचांग_year + 1900)) ||
	    ((अचिन्हित पूर्णांक)पंचांग->पंचांग_hour) >= 24 ||
	    ((अचिन्हित पूर्णांक)पंचांग->पंचांग_min) >= 60 ||
	    ((अचिन्हित पूर्णांक)पंचांग->पंचांग_sec) >= 60)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtc_valid_पंचांग);

/*
 * rtc_पंचांग_to_समय64 - Converts rtc_समय to समय64_t.
 * Convert Gregorian date to seconds since 01-01-1970 00:00:00.
 */
समय64_t rtc_पंचांग_to_समय64(काष्ठा rtc_समय *पंचांग)
अणु
	वापस स_गढ़ो64(((अचिन्हित पूर्णांक)पंचांग->पंचांग_year + 1900), पंचांग->पंचांग_mon + 1,
			पंचांग->पंचांग_mday, पंचांग->पंचांग_hour, पंचांग->पंचांग_min, पंचांग->पंचांग_sec);
पूर्ण
EXPORT_SYMBOL(rtc_पंचांग_to_समय64);

/*
 * Convert rtc_समय to kसमय
 */
kसमय_प्रकार rtc_पंचांग_to_kसमय(काष्ठा rtc_समय पंचांग)
अणु
	वापस kसमय_set(rtc_पंचांग_to_समय64(&पंचांग), 0);
पूर्ण
EXPORT_SYMBOL_GPL(rtc_पंचांग_to_kसमय);

/*
 * Convert kसमय to rtc_समय
 */
काष्ठा rtc_समय rtc_kसमय_प्रकारo_पंचांग(kसमय_प्रकार kt)
अणु
	काष्ठा बारpec64 ts;
	काष्ठा rtc_समय ret;

	ts = kसमय_प्रकारo_बारpec64(kt);
	/* Round up any ns */
	अगर (ts.tv_nsec)
		ts.tv_sec++;
	rtc_समय64_to_पंचांग(ts.tv_sec, &ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rtc_kसमय_प्रकारo_पंचांग);
