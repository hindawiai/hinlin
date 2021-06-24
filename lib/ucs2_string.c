<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ucs2_माला.स>
#समावेश <linux/module.h>

/* Return the number of unicode अक्षरacters in data */
अचिन्हित दीर्घ
ucs2_strnlen(स्थिर ucs2_अक्षर_t *s, माप_प्रकार maxlength)
अणु
        अचिन्हित दीर्घ length = 0;

        जबतक (*s++ != 0 && length < maxlength)
                length++;
        वापस length;
पूर्ण
EXPORT_SYMBOL(ucs2_strnlen);

अचिन्हित दीर्घ
ucs2_म_माप(स्थिर ucs2_अक्षर_t *s)
अणु
        वापस ucs2_strnlen(s, ~0UL);
पूर्ण
EXPORT_SYMBOL(ucs2_म_माप);

/*
 * Return the number of bytes is the length of this string
 * Note: this is NOT the same as the number of unicode अक्षरacters
 */
अचिन्हित दीर्घ
ucs2_strsize(स्थिर ucs2_अक्षर_t *data, अचिन्हित दीर्घ maxlength)
अणु
        वापस ucs2_strnlen(data, maxlength/माप(ucs2_अक्षर_t)) * माप(ucs2_अक्षर_t);
पूर्ण
EXPORT_SYMBOL(ucs2_strsize);

पूर्णांक
ucs2_म_भेदन(स्थिर ucs2_अक्षर_t *a, स्थिर ucs2_अक्षर_t *b, माप_प्रकार len)
अणु
        जबतक (1) अणु
                अगर (len == 0)
                        वापस 0;
                अगर (*a < *b)
                        वापस -1;
                अगर (*a > *b)
                        वापस 1;
                अगर (*a == 0) /* implies *b == 0 */
                        वापस 0;
                a++;
                b++;
                len--;
        पूर्ण
पूर्ण
EXPORT_SYMBOL(ucs2_म_भेदन);

अचिन्हित दीर्घ
ucs2_utf8size(स्थिर ucs2_अक्षर_t *src)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ j = 0;

	क्रम (i = 0; src[i]; i++) अणु
		u16 c = src[i];

		अगर (c >= 0x800)
			j += 3;
		अन्यथा अगर (c >= 0x80)
			j += 2;
		अन्यथा
			j += 1;
	पूर्ण

	वापस j;
पूर्ण
EXPORT_SYMBOL(ucs2_utf8size);

/*
 * copy at most maxlength bytes of whole utf8 अक्षरacters to dest from the
 * ucs2 string src.
 *
 * The वापस value is the number of अक्षरacters copied, not including the
 * final NUL अक्षरacter.
 */
अचिन्हित दीर्घ
ucs2_as_utf8(u8 *dest, स्थिर ucs2_अक्षर_t *src, अचिन्हित दीर्घ maxlength)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ j = 0;
	अचिन्हित दीर्घ limit = ucs2_strnlen(src, maxlength);

	क्रम (i = 0; maxlength && i < limit; i++) अणु
		u16 c = src[i];

		अगर (c >= 0x800) अणु
			अगर (maxlength < 3)
				अवरोध;
			maxlength -= 3;
			dest[j++] = 0xe0 | (c & 0xf000) >> 12;
			dest[j++] = 0x80 | (c & 0x0fc0) >> 6;
			dest[j++] = 0x80 | (c & 0x003f);
		पूर्ण अन्यथा अगर (c >= 0x80) अणु
			अगर (maxlength < 2)
				अवरोध;
			maxlength -= 2;
			dest[j++] = 0xc0 | (c & 0x7c0) >> 6;
			dest[j++] = 0x80 | (c & 0x03f);
		पूर्ण अन्यथा अणु
			maxlength -= 1;
			dest[j++] = c & 0x7f;
		पूर्ण
	पूर्ण
	अगर (maxlength)
		dest[j] = '\0';
	वापस j;
पूर्ण
EXPORT_SYMBOL(ucs2_as_utf8);

MODULE_LICENSE("GPL v2");
