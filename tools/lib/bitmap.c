<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * From lib/biपंचांगap.c
 * Helper functions क्रम biपंचांगap.h.
 */
#समावेश <linux/biपंचांगap.h>

पूर्णांक __biपंचांगap_weight(स्थिर अचिन्हित दीर्घ *biपंचांगap, पूर्णांक bits)
अणु
	पूर्णांक k, w = 0, lim = bits/BITS_PER_LONG;

	क्रम (k = 0; k < lim; k++)
		w += hweight_दीर्घ(biपंचांगap[k]);

	अगर (bits % BITS_PER_LONG)
		w += hweight_दीर्घ(biपंचांगap[k] & BITMAP_LAST_WORD_MASK(bits));

	वापस w;
पूर्ण

व्योम __biपंचांगap_or(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		 स्थिर अचिन्हित दीर्घ *biपंचांगap2, पूर्णांक bits)
अणु
	पूर्णांक k;
	पूर्णांक nr = BITS_TO_LONGS(bits);

	क्रम (k = 0; k < nr; k++)
		dst[k] = biपंचांगap1[k] | biपंचांगap2[k];
पूर्ण

माप_प्रकार biपंचांगap_scnम_लिखो(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits,
			अक्षर *buf, माप_प्रकार size)
अणु
	/* current bit is 'cur', most recently seen range is [rbot, rtop] */
	अचिन्हित पूर्णांक cur, rbot, rtop;
	bool first = true;
	माप_प्रकार ret = 0;

	rbot = cur = find_first_bit(biपंचांगap, nbits);
	जबतक (cur < nbits) अणु
		rtop = cur;
		cur = find_next_bit(biपंचांगap, nbits, cur + 1);
		अगर (cur < nbits && cur <= rtop + 1)
			जारी;

		अगर (!first)
			ret += scnम_लिखो(buf + ret, size - ret, ",");

		first = false;

		ret += scnम_लिखो(buf + ret, size - ret, "%d", rbot);
		अगर (rbot < rtop)
			ret += scnम_लिखो(buf + ret, size - ret, "-%d", rtop);

		rbot = cur;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक __biपंचांगap_and(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		 स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक lim = bits/BITS_PER_LONG;
	अचिन्हित दीर्घ result = 0;

	क्रम (k = 0; k < lim; k++)
		result |= (dst[k] = biपंचांगap1[k] & biपंचांगap2[k]);
	अगर (bits % BITS_PER_LONG)
		result |= (dst[k] = biपंचांगap1[k] & biपंचांगap2[k] &
			   BITMAP_LAST_WORD_MASK(bits));
	वापस result != 0;
पूर्ण

पूर्णांक __biपंचांगap_equal(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k, lim = bits/BITS_PER_LONG;
	क्रम (k = 0; k < lim; ++k)
		अगर (biपंचांगap1[k] != biपंचांगap2[k])
			वापस 0;

	अगर (bits % BITS_PER_LONG)
		अगर ((biपंचांगap1[k] ^ biपंचांगap2[k]) & BITMAP_LAST_WORD_MASK(bits))
			वापस 0;

	वापस 1;
पूर्ण
