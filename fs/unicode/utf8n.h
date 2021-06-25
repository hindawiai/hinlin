<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 SGI.
 * All rights reserved.
 */

#अगर_अघोषित UTF8NORM_H
#घोषणा UTF8NORM_H

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>

/* Encoding a unicode version number as a single अचिन्हित पूर्णांक. */
#घोषणा UNICODE_MAJ_SHIFT		(16)
#घोषणा UNICODE_MIN_SHIFT		(8)

#घोषणा UNICODE_AGE(MAJ, MIN, REV)			\
	(((अचिन्हित पूर्णांक)(MAJ) << UNICODE_MAJ_SHIFT) |	\
	 ((अचिन्हित पूर्णांक)(MIN) << UNICODE_MIN_SHIFT) |	\
	 ((अचिन्हित पूर्णांक)(REV)))

/* Highest unicode version supported by the data tables. */
बाह्य पूर्णांक utf8version_is_supported(u8 maj, u8 min, u8 rev);
बाह्य पूर्णांक utf8version_latest(व्योम);

/*
 * Look क्रम the correct स्थिर काष्ठा utf8data क्रम a unicode version.
 * Returns शून्य अगर the version requested is too new.
 *
 * Two normalization क्रमms are supported: nfdi and nfdicf.
 *
 * nfdi:
 *  - Apply unicode normalization क्रमm NFD.
 *  - Remove any Default_Ignorable_Code_Poपूर्णांक.
 *
 * nfdicf:
 *  - Apply unicode normalization क्रमm NFD.
 *  - Remove any Default_Ignorable_Code_Poपूर्णांक.
 *  - Apply a full हालfold (C + F).
 */
बाह्य स्थिर काष्ठा utf8data *utf8nfdi(अचिन्हित पूर्णांक maxage);
बाह्य स्थिर काष्ठा utf8data *utf8nfdicf(अचिन्हित पूर्णांक maxage);

/*
 * Determine the maximum age of any unicode अक्षरacter in the string.
 * Returns 0 अगर only unasचिन्हित code poपूर्णांकs are present.
 * Returns -1 अगर the input is not valid UTF-8.
 */
बाह्य पूर्णांक utf8agemax(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s);
बाह्य पूर्णांक utf8nagemax(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s, माप_प्रकार len);

/*
 * Determine the minimum age of any unicode अक्षरacter in the string.
 * Returns 0 अगर any unasचिन्हित code poपूर्णांकs are present.
 * Returns -1 अगर the input is not valid UTF-8.
 */
बाह्य पूर्णांक utf8agemin(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s);
बाह्य पूर्णांक utf8nagemin(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s, माप_प्रकार len);

/*
 * Determine the length of the normalized from of the string,
 * excluding any terminating शून्य byte.
 * Returns 0 अगर only ignorable code poपूर्णांकs are present.
 * Returns -1 अगर the input is not valid UTF-8.
 */
बाह्य sमाप_प्रकार utf8len(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s);
बाह्य sमाप_प्रकार utf8nlen(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s, माप_प्रकार len);

/* Needed in काष्ठा utf8cursor below. */
#घोषणा UTF8HANGULLEAF	(12)

/*
 * Cursor काष्ठाure used by the normalizer.
 */
काष्ठा utf8cursor अणु
	स्थिर काष्ठा utf8data	*data;
	स्थिर अक्षर	*s;
	स्थिर अक्षर	*p;
	स्थिर अक्षर	*ss;
	स्थिर अक्षर	*sp;
	अचिन्हित पूर्णांक	len;
	अचिन्हित पूर्णांक	slen;
	लघु पूर्णांक	ccc;
	लघु पूर्णांक	nccc;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];
पूर्ण;

/*
 * Initialize a utf8cursor to normalize a string.
 * Returns 0 on success.
 * Returns -1 on failure.
 */
बाह्य पूर्णांक utf8cursor(काष्ठा utf8cursor *u8c, स्थिर काष्ठा utf8data *data,
		      स्थिर अक्षर *s);
बाह्य पूर्णांक utf8ncursor(काष्ठा utf8cursor *u8c, स्थिर काष्ठा utf8data *data,
		       स्थिर अक्षर *s, माप_प्रकार len);

/*
 * Get the next byte in the normalization.
 * Returns a value > 0 && < 256 on success.
 * Returns 0 when the end of the normalization is reached.
 * Returns -1 अगर the string being normalized is not valid UTF-8.
 */
बाह्य पूर्णांक utf8byte(काष्ठा utf8cursor *u8c);

#पूर्ण_अगर /* UTF8NORM_H */
