<शैली गुरु>
/*
 * Module क्रम handling utf8 just like any other अक्षरset.
 * By Urban Widmark 2000
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/nls.h>
#समावेश <linux/त्रुटिसं.स>

अटल अचिन्हित अक्षर identity[256];

अटल पूर्णांक uni2अक्षर(ब_अक्षर_प्रकार uni, अचिन्हित अक्षर *out, पूर्णांक boundlen)
अणु
	पूर्णांक n;

	अगर (boundlen <= 0)
		वापस -ENAMETOOLONG;

	n = utf32_to_utf8(uni, out, boundlen);
	अगर (n < 0) अणु
		*out = '?';
		वापस -EINVAL;
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक अक्षर2uni(स्थिर अचिन्हित अक्षर *rawstring, पूर्णांक boundlen, ब_अक्षर_प्रकार *uni)
अणु
	पूर्णांक n;
	unicode_t u;

	n = utf8_to_utf32(rawstring, boundlen, &u);
	अगर (n < 0 || u > MAX_WCHAR_T) अणु
		*uni = 0x003f;	/* ? */
		वापस -EINVAL;
	पूर्ण
	*uni = (ब_अक्षर_प्रकार) u;
	वापस n;
पूर्ण

अटल काष्ठा nls_table table = अणु
	.अक्षरset	= "utf8",
	.uni2अक्षर	= uni2अक्षर,
	.अक्षर2uni	= अक्षर2uni,
	.अक्षरset2lower	= identity,	/* no conversion */
	.अक्षरset2upper	= identity,
पूर्ण;

अटल पूर्णांक __init init_nls_utf8(व्योम)
अणु
	पूर्णांक i;
	क्रम (i=0; i<256; i++)
		identity[i] = i;

        वापस रेजिस्टर_nls(&table);
पूर्ण

अटल व्योम __निकास निकास_nls_utf8(व्योम)
अणु
        unरेजिस्टर_nls(&table);
पूर्ण

module_init(init_nls_utf8)
module_निकास(निकास_nls_utf8)
MODULE_LICENSE("Dual BSD/GPL");
