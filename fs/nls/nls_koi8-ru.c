<शैली गुरु>
/*
 * linux/fs/nls/nls_koi8-ru.c
 *
 * Charset koi8-ru translation based on अक्षरset koi8-u.
 * The Unicode to अक्षरset table has only exact mappings.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/nls.h>
#समावेश <linux/त्रुटिसं.स>

अटल काष्ठा nls_table *p_nls;

अटल पूर्णांक uni2अक्षर(स्थिर ब_अक्षर_प्रकार uni,
		    अचिन्हित अक्षर *out, पूर्णांक boundlen)
अणु
	अगर (boundlen <= 0)
		वापस -ENAMETOOLONG;

	अगर ((uni & 0xffaf) == 0x040e || (uni & 0xffce) == 0x254c) अणु
		/* koi8-ru and koi8-u dअगरfer only on two अक्षरacters */
		अगर (uni == 0x040e)
			out[0] = 0xbe;
		अन्यथा अगर (uni == 0x045e)
			out[0] = 0xae;
		अन्यथा अगर (uni == 0x255d || uni == 0x256c)
			वापस 0;
		अन्यथा
			वापस p_nls->uni2अक्षर(uni, out, boundlen);
		वापस 1;
	पूर्ण
	अन्यथा
		/* fast path */
		वापस p_nls->uni2अक्षर(uni, out, boundlen);
पूर्ण

अटल पूर्णांक अक्षर2uni(स्थिर अचिन्हित अक्षर *rawstring, पूर्णांक boundlen,
		    ब_अक्षर_प्रकार *uni)
अणु
	पूर्णांक n;

	अगर ((*rawstring & 0xef) != 0xae) अणु
		/* koi8-ru and koi8-u dअगरfer only on two अक्षरacters */
		*uni = (*rawstring & 0x10) ? 0x040e : 0x045e;
		वापस 1;
	पूर्ण

	n = p_nls->अक्षर2uni(rawstring, boundlen, uni);
	वापस n;
पूर्ण

अटल काष्ठा nls_table table = अणु
	.अक्षरset	= "koi8-ru",
	.uni2अक्षर	= uni2अक्षर,
	.अक्षर2uni	= अक्षर2uni,
पूर्ण;

अटल पूर्णांक __init init_nls_koi8_ru(व्योम)
अणु
	p_nls = load_nls("koi8-u");

	अगर (p_nls) अणु
		table.अक्षरset2upper = p_nls->अक्षरset2upper;
		table.अक्षरset2lower = p_nls->अक्षरset2lower;
		वापस रेजिस्टर_nls(&table);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम __निकास निकास_nls_koi8_ru(व्योम)
अणु
	unरेजिस्टर_nls(&table);
	unload_nls(p_nls);
पूर्ण

module_init(init_nls_koi8_ru)
module_निकास(निकास_nls_koi8_ru)

MODULE_LICENSE("Dual BSD/GPL");
