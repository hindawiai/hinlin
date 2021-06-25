<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/bug.h>
#समावेश <linux/biपंचांगap.h>

/**
 * memweight - count the total number of bits set in memory area
 * @ptr: poपूर्णांकer to the start of the area
 * @bytes: the size of the area
 */
माप_प्रकार memweight(स्थिर व्योम *ptr, माप_प्रकार bytes)
अणु
	माप_प्रकार ret = 0;
	माप_प्रकार दीर्घs;
	स्थिर अचिन्हित अक्षर *biपंचांगap = ptr;

	क्रम (; bytes > 0 && ((अचिन्हित दीर्घ)biपंचांगap) % माप(दीर्घ);
			bytes--, biपंचांगap++)
		ret += hweight8(*biपंचांगap);

	दीर्घs = bytes / माप(दीर्घ);
	अगर (दीर्घs) अणु
		BUG_ON(दीर्घs >= पूर्णांक_उच्च / BITS_PER_LONG);
		ret += biपंचांगap_weight((अचिन्हित दीर्घ *)biपंचांगap,
				दीर्घs * BITS_PER_LONG);
		bytes -= दीर्घs * माप(दीर्घ);
		biपंचांगap += दीर्घs * माप(दीर्घ);
	पूर्ण
	/*
	 * The reason that this last loop is distinct from the preceding
	 * biपंचांगap_weight() call is to compute 1-bits in the last region smaller
	 * than माप(दीर्घ) properly on big-endian प्रणालीs.
	 */
	क्रम (; bytes > 0; bytes--, biपंचांगap++)
		ret += hweight8(*biपंचांगap);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(memweight);
