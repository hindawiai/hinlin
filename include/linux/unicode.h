<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNICODE_H
#घोषणा _LINUX_UNICODE_H

#समावेश <linux/init.h>
#समावेश <linux/dcache.h>

काष्ठा unicode_map अणु
	स्थिर अक्षर *अक्षरset;
	पूर्णांक version;
पूर्ण;

पूर्णांक utf8_validate(स्थिर काष्ठा unicode_map *um, स्थिर काष्ठा qstr *str);

पूर्णांक utf8_म_भेदन(स्थिर काष्ठा unicode_map *um,
		 स्थिर काष्ठा qstr *s1, स्थिर काष्ठा qstr *s2);

पूर्णांक utf8_strnहालcmp(स्थिर काष्ठा unicode_map *um,
		 स्थिर काष्ठा qstr *s1, स्थिर काष्ठा qstr *s2);
पूर्णांक utf8_strnहालcmp_folded(स्थिर काष्ठा unicode_map *um,
			    स्थिर काष्ठा qstr *cf,
			    स्थिर काष्ठा qstr *s1);

पूर्णांक utf8_normalize(स्थिर काष्ठा unicode_map *um, स्थिर काष्ठा qstr *str,
		   अचिन्हित अक्षर *dest, माप_प्रकार dlen);

पूर्णांक utf8_हालfold(स्थिर काष्ठा unicode_map *um, स्थिर काष्ठा qstr *str,
		  अचिन्हित अक्षर *dest, माप_प्रकार dlen);

पूर्णांक utf8_हालfold_hash(स्थिर काष्ठा unicode_map *um, स्थिर व्योम *salt,
		       काष्ठा qstr *str);

काष्ठा unicode_map *utf8_load(स्थिर अक्षर *version);
व्योम utf8_unload(काष्ठा unicode_map *um);

#पूर्ण_अगर /* _LINUX_UNICODE_H */
