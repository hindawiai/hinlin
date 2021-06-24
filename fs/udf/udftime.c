<शैली गुरु>
/* Copyright (C) 1993, 1994, 1995, 1996, 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Paul Eggert (eggert@twinsun.com).

   The GNU C Library is मुक्त software; you can redistribute it and/or
   modअगरy it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License क्रम more details.

   You should have received a copy of the GNU Library General Public
   License aदीर्घ with the GNU C Library; see the file COPYING.LIB.  If not,
   ग_लिखो to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/*
 * dgb 10/02/98: ripped this from glibc source to help convert बारtamps
 *               to unix समय
 *     10/04/98: added new table-based lookup after seeing how ugly
 *               the gnu code is
 * blf 09/27/99: ripped out all the old code and inserted new table from
 *		 John Brockmeyer (without leap second corrections)
 *		 rewrote udf_stamp_to_समय and fixed समयzone accounting in
 *		 udf_समय_प्रकारo_stamp.
 */

/*
 * We करोn't take पूर्णांकo account leap seconds. This may be correct or incorrect.
 * For more NIST inक्रमmation (especially dealing with leap seconds), see:
 * http://www.boulder.nist.gov/समयfreq/pubs/bulletin/leapsecond.hपंचांग
 */

#समावेश "udfdecl.h"

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>

व्योम
udf_disk_stamp_to_समय(काष्ठा बारpec64 *dest, काष्ठा बारtamp src)
अणु
	u16 typeAndTimezone = le16_to_cpu(src.typeAndTimezone);
	u16 year = le16_to_cpu(src.year);
	uपूर्णांक8_t type = typeAndTimezone >> 12;
	पूर्णांक16_t offset;

	अगर (type == 1) अणु
		offset = typeAndTimezone << 4;
		/* sign extent offset */
		offset = (offset >> 4);
		अगर (offset == -2047) /* unspecअगरied offset */
			offset = 0;
	पूर्ण अन्यथा
		offset = 0;

	dest->tv_sec = स_गढ़ो64(year, src.month, src.day, src.hour, src.minute,
			src.second);
	dest->tv_sec -= offset * 60;
	dest->tv_nsec = 1000 * (src.centiseconds * 10000 +
			src.hundredsOfMicroseconds * 100 + src.microseconds);
	/*
	 * Sanitize nanosecond field since reportedly some fileप्रणालीs are
	 * recorded with bogus sub-second values.
	 */
	dest->tv_nsec %= NSEC_PER_SEC;
पूर्ण

व्योम
udf_समय_प्रकारo_disk_stamp(काष्ठा बारtamp *dest, काष्ठा बारpec64 ts)
अणु
	समय64_t seconds;
	पूर्णांक16_t offset;
	काष्ठा पंचांग पंचांग;

	offset = -sys_tz.tz_minuteswest;

	dest->typeAndTimezone = cpu_to_le16(0x1000 | (offset & 0x0FFF));

	seconds = ts.tv_sec + offset * 60;
	समय64_to_पंचांग(seconds, 0, &पंचांग);
	dest->year = cpu_to_le16(पंचांग.पंचांग_year + 1900);
	dest->month = पंचांग.पंचांग_mon + 1;
	dest->day = पंचांग.पंचांग_mday;
	dest->hour = पंचांग.पंचांग_hour;
	dest->minute = पंचांग.पंचांग_min;
	dest->second = पंचांग.पंचांग_sec;
	dest->centiseconds = ts.tv_nsec / 10000000;
	dest->hundredsOfMicroseconds = (ts.tv_nsec / 1000 -
					dest->centiseconds * 10000) / 100;
	dest->microseconds = (ts.tv_nsec / 1000 - dest->centiseconds * 10000 -
			      dest->hundredsOfMicroseconds * 100);
पूर्ण

/* खातापूर्ण */
