<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NLS_H
#घोषणा _LINUX_NLS_H

#समावेश <linux/init.h>

/* Unicode has changed over the years.  Unicode code poपूर्णांकs no दीर्घer
 * fit पूर्णांकo 16 bits; as of Unicode 5 valid code poपूर्णांकs range from 0
 * to 0x10ffff (17 planes, where each plane holds 65536 code poपूर्णांकs).
 *
 * The original decision to represent Unicode अक्षरacters as 16-bit
 * ब_अक्षर_प्रकार values is now outdated.  But plane 0 still includes the
 * most commonly used अक्षरacters, so we will retain it.  The newer
 * 32-bit unicode_t type can be used when it is necessary to
 * represent the full Unicode अक्षरacter set.
 */

/* Plane-0 Unicode अक्षरacter */
प्रकार u16 ब_अक्षर_प्रकार;
#घोषणा MAX_WCHAR_T	0xffff

/* Arbitrary Unicode अक्षरacter */
प्रकार u32 unicode_t;

काष्ठा nls_table अणु
	स्थिर अक्षर *अक्षरset;
	स्थिर अक्षर *alias;
	पूर्णांक (*uni2अक्षर) (ब_अक्षर_प्रकार uni, अचिन्हित अक्षर *out, पूर्णांक boundlen);
	पूर्णांक (*अक्षर2uni) (स्थिर अचिन्हित अक्षर *rawstring, पूर्णांक boundlen,
			 ब_अक्षर_प्रकार *uni);
	स्थिर अचिन्हित अक्षर *अक्षरset2lower;
	स्थिर अचिन्हित अक्षर *अक्षरset2upper;
	काष्ठा module *owner;
	काष्ठा nls_table *next;
पूर्ण;

/* this value hold the maximum octet of अक्षरset */
#घोषणा NLS_MAX_CHARSET_SIZE 6 /* क्रम UTF-8 */

/* Byte order क्रम UTF-16 strings */
क्रमागत utf16_endian अणु
	UTF16_HOST_ENDIAN,
	UTF16_LITTLE_ENDIAN,
	UTF16_BIG_ENDIAN
पूर्ण;

/* nls_base.c */
बाह्य पूर्णांक __रेजिस्टर_nls(काष्ठा nls_table *, काष्ठा module *);
बाह्य पूर्णांक unरेजिस्टर_nls(काष्ठा nls_table *);
बाह्य काष्ठा nls_table *load_nls(अक्षर *);
बाह्य व्योम unload_nls(काष्ठा nls_table *);
बाह्य काष्ठा nls_table *load_nls_शेष(व्योम);
#घोषणा रेजिस्टर_nls(nls) __रेजिस्टर_nls((nls), THIS_MODULE)

बाह्य पूर्णांक utf8_to_utf32(स्थिर u8 *s, पूर्णांक len, unicode_t *pu);
बाह्य पूर्णांक utf32_to_utf8(unicode_t u, u8 *s, पूर्णांक maxlen);
बाह्य पूर्णांक utf8s_to_utf16s(स्थिर u8 *s, पूर्णांक len,
		क्रमागत utf16_endian endian, ब_अक्षर_प्रकार *pwcs, पूर्णांक maxlen);
बाह्य पूर्णांक utf16s_to_utf8s(स्थिर ब_अक्षर_प्रकार *pwcs, पूर्णांक len,
		क्रमागत utf16_endian endian, u8 *s, पूर्णांक maxlen);

अटल अंतरभूत अचिन्हित अक्षर nls_छोटे(काष्ठा nls_table *t, अचिन्हित अक्षर c)
अणु
	अचिन्हित अक्षर nc = t->अक्षरset2lower[c];

	वापस nc ? nc : c;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर nls_बड़े(काष्ठा nls_table *t, अचिन्हित अक्षर c)
अणु
	अचिन्हित अक्षर nc = t->अक्षरset2upper[c];

	वापस nc ? nc : c;
पूर्ण

अटल अंतरभूत पूर्णांक nls_strnicmp(काष्ठा nls_table *t, स्थिर अचिन्हित अक्षर *s1,
		स्थिर अचिन्हित अक्षर *s2, पूर्णांक len)
अणु
	जबतक (len--) अणु
		अगर (nls_छोटे(t, *s1++) != nls_छोटे(t, *s2++))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * nls_nullsize - वापस length of null अक्षरacter क्रम codepage
 * @codepage - codepage क्रम which to वापस length of शून्य terminator
 *
 * Since we can't guarantee that the null terminator will be a particular
 * length, we have to check against the codepage. If there's a problem
 * determining it, assume a single-byte शून्य terminator.
 */
अटल अंतरभूत पूर्णांक
nls_nullsize(स्थिर काष्ठा nls_table *codepage)
अणु
	पूर्णांक अक्षरlen;
	अक्षर पंचांगp[NLS_MAX_CHARSET_SIZE];

	अक्षरlen = codepage->uni2अक्षर(0, पंचांगp, NLS_MAX_CHARSET_SIZE);

	वापस अक्षरlen > 0 ? अक्षरlen : 1;
पूर्ण

#घोषणा MODULE_ALIAS_NLS(name)	MODULE_ALIAS("nls_" __stringअगरy(name))

#पूर्ण_अगर /* _LINUX_NLS_H */

