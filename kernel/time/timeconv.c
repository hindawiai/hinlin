<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.0+
/*
 * Copyright (C) 1993, 1994, 1995, 1996, 1997 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 * Contributed by Paul Eggert (eggert@twinsun.com).
 *
 * The GNU C Library is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License aदीर्घ with the GNU C Library; see the file COPYING.LIB.  If not,
 * ग_लिखो to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Converts the calendar समय to broken-करोwn समय representation
 * Based on code from glibc-2.6
 *
 * 2009-7-14:
 *   Moved from glibc-2.6 to kernel by Zhaolei<zhaolei@cn.fujitsu.com>
 */

#समावेश <linux/समय.स>
#समावेश <linux/module.h>

/*
 * Nonzero अगर YEAR is a leap year (every 4 years,
 * except every 100th isn't, and every 400th is).
 */
अटल पूर्णांक __isleap(दीर्घ year)
अणु
	वापस (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
पूर्ण

/* करो a mathभाग क्रम दीर्घ type */
अटल दीर्घ math_भाग(दीर्घ a, दीर्घ b)
अणु
	वापस a / b - (a % b < 0);
पूर्ण

/* How many leap years between y1 and y2, y1 must less or equal to y2 */
अटल दीर्घ leaps_between(दीर्घ y1, दीर्घ y2)
अणु
	दीर्घ leaps1 = math_भाग(y1 - 1, 4) - math_भाग(y1 - 1, 100)
		+ math_भाग(y1 - 1, 400);
	दीर्घ leaps2 = math_भाग(y2 - 1, 4) - math_भाग(y2 - 1, 100)
		+ math_भाग(y2 - 1, 400);
	वापस leaps2 - leaps1;
पूर्ण

/* How many days come beक्रमe each month (0-12). */
अटल स्थिर अचिन्हित लघु __mon_yday[2][13] = अणु
	/* Normal years. */
	अणु0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365पूर्ण,
	/* Leap years. */
	अणु0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366पूर्ण
पूर्ण;

#घोषणा SECS_PER_HOUR	(60 * 60)
#घोषणा SECS_PER_DAY	(SECS_PER_HOUR * 24)

/**
 * समय64_to_पंचांग - converts the calendar समय to local broken-करोwn समय
 *
 * @totalsecs:	the number of seconds elapsed since 00:00:00 on January 1, 1970,
 *		Coordinated Universal Time (UTC).
 * @offset:	offset seconds adding to totalsecs.
 * @result:	poपूर्णांकer to काष्ठा पंचांग variable to receive broken-करोwn समय
 */
व्योम समय64_to_पंचांग(समय64_t totalsecs, पूर्णांक offset, काष्ठा पंचांग *result)
अणु
	दीर्घ days, rem, y;
	पूर्णांक reमुख्यder;
	स्थिर अचिन्हित लघु *ip;

	days = भाग_s64_rem(totalsecs, SECS_PER_DAY, &reमुख्यder);
	rem = reमुख्यder;
	rem += offset;
	जबतक (rem < 0) अणु
		rem += SECS_PER_DAY;
		--days;
	पूर्ण
	जबतक (rem >= SECS_PER_DAY) अणु
		rem -= SECS_PER_DAY;
		++days;
	पूर्ण

	result->पंचांग_hour = rem / SECS_PER_HOUR;
	rem %= SECS_PER_HOUR;
	result->पंचांग_min = rem / 60;
	result->पंचांग_sec = rem % 60;

	/* January 1, 1970 was a Thursday. */
	result->पंचांग_wday = (4 + days) % 7;
	अगर (result->पंचांग_wday < 0)
		result->पंचांग_wday += 7;

	y = 1970;

	जबतक (days < 0 || days >= (__isleap(y) ? 366 : 365)) अणु
		/* Guess a corrected year, assuming 365 days per year. */
		दीर्घ yg = y + math_भाग(days, 365);

		/* Adjust DAYS and Y to match the guessed year. */
		days -= (yg - y) * 365 + leaps_between(y, yg);
		y = yg;
	पूर्ण

	result->पंचांग_year = y - 1900;

	result->पंचांग_yday = days;

	ip = __mon_yday[__isleap(y)];
	क्रम (y = 11; days < ip[y]; y--)
		जारी;
	days -= ip[y];

	result->पंचांग_mon = y;
	result->पंचांग_mday = days + 1;
पूर्ण
EXPORT_SYMBOL(समय64_to_पंचांग);
