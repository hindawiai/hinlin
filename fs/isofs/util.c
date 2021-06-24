<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/isofs/util.c
 */

#समावेश <linux/समय.स>
#समावेश "isofs.h"

/* 
 * We have to convert from a MM/DD/YY क्रमmat to the Unix स_समय क्रमmat.
 * We have to take पूर्णांकo account leap years and all of that good stuff.
 * Unक्रमtunately, the kernel करोes not have the inक्रमmation on hand to
 * take पूर्णांकo account daylight savings समय, but it shouldn't matter.
 * The समय stored should be स_स्थानीय (with or without DST in effect),
 * and the समयzone offset should hold the offset required to get back
 * to GMT.  Thus  we should always be correct.
 */

पूर्णांक iso_date(u8 *p, पूर्णांक flag)
अणु
	पूर्णांक year, month, day, hour, minute, second, tz;
	पूर्णांक crसमय;

	year = p[0];
	month = p[1];
	day = p[2];
	hour = p[3];
	minute = p[4];
	second = p[5];
	अगर (flag == 0) tz = p[6]; /* High sierra has no समय zone */
	अन्यथा tz = 0;
	
	अगर (year < 0) अणु
		crसमय = 0;
	पूर्ण अन्यथा अणु
		crसमय = स_गढ़ो64(year+1900, month, day, hour, minute, second);

		/* sign extend */
		अगर (tz & 0x80)
			tz |= (-1 << 8);
		
		/* 
		 * The समयzone offset is unreliable on some disks,
		 * so we make a sanity check.  In no हाल is it ever
		 * more than 13 hours from GMT, which is 52*15min.
		 * The समय is always stored in स_स्थानीय with the
		 * समयzone offset being what get added to GMT to
		 * get to स_स्थानीय.  Thus we need to subtract the offset
		 * to get to true GMT, which is what we store the समय
		 * as पूर्णांकernally.  On the local प्रणाली, the user may set
		 * their समयzone any way they wish, of course, so GMT
		 * माला_लो converted back to स_स्थानीय on the receiving
		 * प्रणाली.
		 *
		 * NOTE: mkisofs in versions prior to mkisofs-1.10 had
		 * the sign wrong on the समयzone offset.  This has now
		 * been corrected there too, but अगर you are getting screwy
		 * results this may be the explanation.  If enough people
		 * complain, a user configuration option could be added
		 * to add the समयzone offset in with the wrong sign
		 * क्रम 'compatibility' with older discs, but I cannot see how
		 * it will matter that much.
		 *
		 * Thanks to kuhlmav@elec.canterbury.ac.nz (Volker Kuhlmann)
		 * क्रम poपूर्णांकing out the sign error.
		 */
		अगर (-52 <= tz && tz <= 52)
			crसमय -= tz * 15 * 60;
	पूर्ण
	वापस crसमय;
पूर्ण		
