<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/parser.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unicode.h>
#समावेश <linux/stringhash.h>

#समावेश "utf8n.h"

पूर्णांक utf8_validate(स्थिर काष्ठा unicode_map *um, स्थिर काष्ठा qstr *str)
अणु
	स्थिर काष्ठा utf8data *data = utf8nfdi(um->version);

	अगर (utf8nlen(data, str->name, str->len) < 0)
		वापस -1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(utf8_validate);

पूर्णांक utf8_म_भेदन(स्थिर काष्ठा unicode_map *um,
		 स्थिर काष्ठा qstr *s1, स्थिर काष्ठा qstr *s2)
अणु
	स्थिर काष्ठा utf8data *data = utf8nfdi(um->version);
	काष्ठा utf8cursor cur1, cur2;
	पूर्णांक c1, c2;

	अगर (utf8ncursor(&cur1, data, s1->name, s1->len) < 0)
		वापस -EINVAL;

	अगर (utf8ncursor(&cur2, data, s2->name, s2->len) < 0)
		वापस -EINVAL;

	करो अणु
		c1 = utf8byte(&cur1);
		c2 = utf8byte(&cur2);

		अगर (c1 < 0 || c2 < 0)
			वापस -EINVAL;
		अगर (c1 != c2)
			वापस 1;
	पूर्ण जबतक (c1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(utf8_म_भेदन);

पूर्णांक utf8_strnहालcmp(स्थिर काष्ठा unicode_map *um,
		     स्थिर काष्ठा qstr *s1, स्थिर काष्ठा qstr *s2)
अणु
	स्थिर काष्ठा utf8data *data = utf8nfdicf(um->version);
	काष्ठा utf8cursor cur1, cur2;
	पूर्णांक c1, c2;

	अगर (utf8ncursor(&cur1, data, s1->name, s1->len) < 0)
		वापस -EINVAL;

	अगर (utf8ncursor(&cur2, data, s2->name, s2->len) < 0)
		वापस -EINVAL;

	करो अणु
		c1 = utf8byte(&cur1);
		c2 = utf8byte(&cur2);

		अगर (c1 < 0 || c2 < 0)
			वापस -EINVAL;
		अगर (c1 != c2)
			वापस 1;
	पूर्ण जबतक (c1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(utf8_strnहालcmp);

/* String cf is expected to be a valid UTF-8 हालfolded
 * string.
 */
पूर्णांक utf8_strnहालcmp_folded(स्थिर काष्ठा unicode_map *um,
			    स्थिर काष्ठा qstr *cf,
			    स्थिर काष्ठा qstr *s1)
अणु
	स्थिर काष्ठा utf8data *data = utf8nfdicf(um->version);
	काष्ठा utf8cursor cur1;
	पूर्णांक c1, c2;
	पूर्णांक i = 0;

	अगर (utf8ncursor(&cur1, data, s1->name, s1->len) < 0)
		वापस -EINVAL;

	करो अणु
		c1 = utf8byte(&cur1);
		c2 = cf->name[i++];
		अगर (c1 < 0)
			वापस -EINVAL;
		अगर (c1 != c2)
			वापस 1;
	पूर्ण जबतक (c1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(utf8_strnहालcmp_folded);

पूर्णांक utf8_हालfold(स्थिर काष्ठा unicode_map *um, स्थिर काष्ठा qstr *str,
		  अचिन्हित अक्षर *dest, माप_प्रकार dlen)
अणु
	स्थिर काष्ठा utf8data *data = utf8nfdicf(um->version);
	काष्ठा utf8cursor cur;
	माप_प्रकार nlen = 0;

	अगर (utf8ncursor(&cur, data, str->name, str->len) < 0)
		वापस -EINVAL;

	क्रम (nlen = 0; nlen < dlen; nlen++) अणु
		पूर्णांक c = utf8byte(&cur);

		dest[nlen] = c;
		अगर (!c)
			वापस nlen;
		अगर (c == -1)
			अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(utf8_हालfold);

पूर्णांक utf8_हालfold_hash(स्थिर काष्ठा unicode_map *um, स्थिर व्योम *salt,
		       काष्ठा qstr *str)
अणु
	स्थिर काष्ठा utf8data *data = utf8nfdicf(um->version);
	काष्ठा utf8cursor cur;
	पूर्णांक c;
	अचिन्हित दीर्घ hash = init_name_hash(salt);

	अगर (utf8ncursor(&cur, data, str->name, str->len) < 0)
		वापस -EINVAL;

	जबतक ((c = utf8byte(&cur))) अणु
		अगर (c < 0)
			वापस -EINVAL;
		hash = partial_name_hash((अचिन्हित अक्षर)c, hash);
	पूर्ण
	str->hash = end_name_hash(hash);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(utf8_हालfold_hash);

पूर्णांक utf8_normalize(स्थिर काष्ठा unicode_map *um, स्थिर काष्ठा qstr *str,
		   अचिन्हित अक्षर *dest, माप_प्रकार dlen)
अणु
	स्थिर काष्ठा utf8data *data = utf8nfdi(um->version);
	काष्ठा utf8cursor cur;
	sमाप_प्रकार nlen = 0;

	अगर (utf8ncursor(&cur, data, str->name, str->len) < 0)
		वापस -EINVAL;

	क्रम (nlen = 0; nlen < dlen; nlen++) अणु
		पूर्णांक c = utf8byte(&cur);

		dest[nlen] = c;
		अगर (!c)
			वापस nlen;
		अगर (c == -1)
			अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

EXPORT_SYMBOL(utf8_normalize);

अटल पूर्णांक utf8_parse_version(स्थिर अक्षर *version, अचिन्हित पूर्णांक *maj,
			      अचिन्हित पूर्णांक *min, अचिन्हित पूर्णांक *rev)
अणु
	substring_t args[3];
	अक्षर version_string[12];
	अटल स्थिर काष्ठा match_token token[] = अणु
		अणु1, "%d.%d.%d"पूर्ण,
		अणु0, शून्यपूर्ण
	पूर्ण;

	म_नकलन(version_string, version, माप(version_string));

	अगर (match_token(version_string, token, args) != 1)
		वापस -EINVAL;

	अगर (match_पूर्णांक(&args[0], maj) || match_पूर्णांक(&args[1], min) ||
	    match_पूर्णांक(&args[2], rev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

काष्ठा unicode_map *utf8_load(स्थिर अक्षर *version)
अणु
	काष्ठा unicode_map *um = शून्य;
	पूर्णांक unicode_version;

	अगर (version) अणु
		अचिन्हित पूर्णांक maj, min, rev;

		अगर (utf8_parse_version(version, &maj, &min, &rev) < 0)
			वापस ERR_PTR(-EINVAL);

		अगर (!utf8version_is_supported(maj, min, rev))
			वापस ERR_PTR(-EINVAL);

		unicode_version = UNICODE_AGE(maj, min, rev);
	पूर्ण अन्यथा अणु
		unicode_version = utf8version_latest();
		prपूर्णांकk(KERN_WARNING"UTF-8 version not specified. "
		       "Assuming latest supported version (%d.%d.%d).",
		       (unicode_version >> 16) & 0xff,
		       (unicode_version >> 8) & 0xff,
		       (unicode_version & 0xff));
	पूर्ण

	um = kzalloc(माप(काष्ठा unicode_map), GFP_KERNEL);
	अगर (!um)
		वापस ERR_PTR(-ENOMEM);

	um->अक्षरset = "UTF-8";
	um->version = unicode_version;

	वापस um;
पूर्ण
EXPORT_SYMBOL(utf8_load);

व्योम utf8_unload(काष्ठा unicode_map *um)
अणु
	kमुक्त(um);
पूर्ण
EXPORT_SYMBOL(utf8_unload);

MODULE_LICENSE("GPL v2");
