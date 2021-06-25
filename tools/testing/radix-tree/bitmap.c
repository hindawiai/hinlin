<शैली गुरु>
/* lib/biपंचांगap.c pulls in at least two other files. */

#समावेश <linux/biपंचांगap.h>

व्योम biपंचांगap_clear(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start, पूर्णांक len)
अणु
	अचिन्हित दीर्घ *p = map + BIT_WORD(start);
	स्थिर अचिन्हित पूर्णांक size = start + len;
	पूर्णांक bits_to_clear = BITS_PER_LONG - (start % BITS_PER_LONG);
	अचिन्हित दीर्घ mask_to_clear = BITMAP_FIRST_WORD_MASK(start);

	जबतक (len - bits_to_clear >= 0) अणु
		*p &= ~mask_to_clear;
		len -= bits_to_clear;
		bits_to_clear = BITS_PER_LONG;
		mask_to_clear = ~0UL;
		p++;
	पूर्ण
	अगर (len) अणु
		mask_to_clear &= BITMAP_LAST_WORD_MASK(size);
		*p &= ~mask_to_clear;
	पूर्ण
पूर्ण
