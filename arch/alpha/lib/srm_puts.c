<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	arch/alpha/lib/srm_माला_दो.c
 */

#समावेश <linux/माला.स>
#समावेश <यंत्र/console.h>

दीर्घ
srm_माला_दो(स्थिर अक्षर *str, दीर्घ len)
अणु
	दीर्घ reमुख्यing, written;

	अगर (!callback_init_करोne)
		वापस len;

	क्रम (reमुख्यing = len; reमुख्यing > 0; reमुख्यing -= written)
	अणु
		written = callback_माला_दो(0, str, reमुख्यing);
		written &= 0xffffffff;
		str += written;
	पूर्ण
	वापस len;
पूर्ण
