<शैली गुरु>
/*
 * Test हालs क्रम lib/string_helpers.c module.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>
#समावेश <linux/string_helpers.h>

अटल __init bool test_string_check_buf(स्थिर अक्षर *name, अचिन्हित पूर्णांक flags,
					 अक्षर *in, माप_प्रकार p,
					 अक्षर *out_real, माप_प्रकार q_real,
					 अक्षर *out_test, माप_प्रकार q_test)
अणु
	अगर (q_real == q_test && !स_भेद(out_test, out_real, q_test))
		वापस true;

	pr_warn("Test '%s' failed: flags = %u\n", name, flags);

	prपूर्णांक_hex_dump(KERN_WARNING, "Input: ", DUMP_PREFIX_NONE, 16, 1,
		       in, p, true);
	prपूर्णांक_hex_dump(KERN_WARNING, "Expected: ", DUMP_PREFIX_NONE, 16, 1,
		       out_test, q_test, true);
	prपूर्णांक_hex_dump(KERN_WARNING, "Got: ", DUMP_PREFIX_NONE, 16, 1,
		       out_real, q_real, true);

	वापस false;
पूर्ण

काष्ठा test_string अणु
	स्थिर अक्षर *in;
	स्थिर अक्षर *out;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा test_string strings[] __initस्थिर = अणु
	अणु
		.in = "\\f\\ \\n\\r\\t\\v",
		.out = "\f\\ \n\r\t\v",
		.flags = UNESCAPE_SPACE,
	पूर्ण,
	अणु
		.in = "\\40\\1\\387\\0064\\05\\040\\8a\\110\\777",
		.out = " \001\00387\0064\005 \\8aH?7",
		.flags = UNESCAPE_OCTAL,
	पूर्ण,
	अणु
		.in = "\\xv\\xa\\x2c\\xD\\x6f2",
		.out = "\\xv\n,\ro2",
		.flags = UNESCAPE_HEX,
	पूर्ण,
	अणु
		.in = "\\h\\\\\\\"\\a\\e\\",
		.out = "\\h\\\"\a\e\\",
		.flags = UNESCAPE_SPECIAL,
	पूर्ण,
पूर्ण;

अटल व्योम __init test_string_unescape(स्थिर अक्षर *name, अचिन्हित पूर्णांक flags,
					bool inplace)
अणु
	पूर्णांक q_real = 256;
	अक्षर *in = kदो_स्मृति(q_real, GFP_KERNEL);
	अक्षर *out_test = kदो_स्मृति(q_real, GFP_KERNEL);
	अक्षर *out_real = kदो_स्मृति(q_real, GFP_KERNEL);
	पूर्णांक i, p = 0, q_test = 0;

	अगर (!in || !out_test || !out_real)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(strings); i++) अणु
		स्थिर अक्षर *s = strings[i].in;
		पूर्णांक len = म_माप(strings[i].in);

		/* Copy string to in buffer */
		स_नकल(&in[p], s, len);
		p += len;

		/* Copy expected result क्रम given flags */
		अगर (flags & strings[i].flags) अणु
			s = strings[i].out;
			len = म_माप(strings[i].out);
		पूर्ण
		स_नकल(&out_test[q_test], s, len);
		q_test += len;
	पूर्ण
	in[p++] = '\0';

	/* Call string_unescape and compare result */
	अगर (inplace) अणु
		स_नकल(out_real, in, p);
		अगर (flags == UNESCAPE_ANY)
			q_real = string_unescape_any_inplace(out_real);
		अन्यथा
			q_real = string_unescape_inplace(out_real, flags);
	पूर्ण अन्यथा अगर (flags == UNESCAPE_ANY) अणु
		q_real = string_unescape_any(in, out_real, q_real);
	पूर्ण अन्यथा अणु
		q_real = string_unescape(in, out_real, q_real, flags);
	पूर्ण

	test_string_check_buf(name, flags, in, p - 1, out_real, q_real,
			      out_test, q_test);
out:
	kमुक्त(out_real);
	kमुक्त(out_test);
	kमुक्त(in);
पूर्ण

काष्ठा test_string_1 अणु
	स्थिर अक्षर *out;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा	TEST_STRING_2_MAX_S1		32
काष्ठा test_string_2 अणु
	स्थिर अक्षर *in;
	काष्ठा test_string_1 s1[TEST_STRING_2_MAX_S1];
पूर्ण;

#घोषणा	TEST_STRING_2_DICT_0		शून्य
अटल स्थिर काष्ठा test_string_2 escape0[] __initस्थिर = अणुअणु
	.in = "\f\\ \n\r\t\v",
	.s1 = अणुअणु
		.out = "\\f\\ \\n\\r\\t\\v",
		.flags = ESCAPE_SPACE,
	पूर्ण,अणु
		.out = "\\f\\134\\040\\n\\r\\t\\v",
		.flags = ESCAPE_SPACE | ESCAPE_OCTAL,
	पूर्ण,अणु
		.out = "\\f\\x5c\\x20\\n\\r\\t\\v",
		.flags = ESCAPE_SPACE | ESCAPE_HEX,
	पूर्ण,अणु
		/* terminator */
	पूर्णपूर्ण,
पूर्ण,अणु
	.in = "\\h\\\"\a\e\\",
	.s1 = अणुअणु
		.out = "\\\\h\\\\\"\\a\\e\\\\",
		.flags = ESCAPE_SPECIAL,
	पूर्ण,अणु
		.out = "\\\\\\150\\\\\\042\\a\\e\\\\",
		.flags = ESCAPE_SPECIAL | ESCAPE_OCTAL,
	पूर्ण,अणु
		.out = "\\\\\\x68\\\\\\x22\\a\\e\\\\",
		.flags = ESCAPE_SPECIAL | ESCAPE_HEX,
	पूर्ण,अणु
		/* terminator */
	पूर्णपूर्ण,
पूर्ण,अणु
	.in = "\eb \\C\007\"\x90\r]",
	.s1 = अणुअणु
		.out = "\eb \\C\007\"\x90\\r]",
		.flags = ESCAPE_SPACE,
	पूर्ण,अणु
		.out = "\\eb \\\\C\\a\"\x90\r]",
		.flags = ESCAPE_SPECIAL,
	पूर्ण,अणु
		.out = "\\eb \\\\C\\a\"\x90\\r]",
		.flags = ESCAPE_SPACE | ESCAPE_SPECIAL,
	पूर्ण,अणु
		.out = "\\033\\142\\040\\134\\103\\007\\042\\220\\015\\135",
		.flags = ESCAPE_OCTAL,
	पूर्ण,अणु
		.out = "\\033\\142\\040\\134\\103\\007\\042\\220\\r\\135",
		.flags = ESCAPE_SPACE | ESCAPE_OCTAL,
	पूर्ण,अणु
		.out = "\\e\\142\\040\\\\\\103\\a\\042\\220\\015\\135",
		.flags = ESCAPE_SPECIAL | ESCAPE_OCTAL,
	पूर्ण,अणु
		.out = "\\e\\142\\040\\\\\\103\\a\\042\\220\\r\\135",
		.flags = ESCAPE_SPACE | ESCAPE_SPECIAL | ESCAPE_OCTAL,
	पूर्ण,अणु
		.out = "\eb \\C\007\"\x90\r]",
		.flags = ESCAPE_NP,
	पूर्ण,अणु
		.out = "\eb \\C\007\"\x90\\r]",
		.flags = ESCAPE_SPACE | ESCAPE_NP,
	पूर्ण,अणु
		.out = "\\eb \\C\\a\"\x90\r]",
		.flags = ESCAPE_SPECIAL | ESCAPE_NP,
	पूर्ण,अणु
		.out = "\\eb \\C\\a\"\x90\\r]",
		.flags = ESCAPE_SPACE | ESCAPE_SPECIAL | ESCAPE_NP,
	पूर्ण,अणु
		.out = "\\033b \\C\\007\"\\220\\015]",
		.flags = ESCAPE_OCTAL | ESCAPE_NP,
	पूर्ण,अणु
		.out = "\\033b \\C\\007\"\\220\\r]",
		.flags = ESCAPE_SPACE | ESCAPE_OCTAL | ESCAPE_NP,
	पूर्ण,अणु
		.out = "\\eb \\C\\a\"\\220\\r]",
		.flags = ESCAPE_SPECIAL | ESCAPE_SPACE | ESCAPE_OCTAL |
			 ESCAPE_NP,
	पूर्ण,अणु
		.out = "\\x1bb \\C\\x07\"\\x90\\x0d]",
		.flags = ESCAPE_NP | ESCAPE_HEX,
	पूर्ण,अणु
		/* terminator */
	पूर्णपूर्ण,
पूर्ण,अणु
	/* terminator */
पूर्णपूर्ण;

#घोषणा	TEST_STRING_2_DICT_1		"b\\ \t\r"
अटल स्थिर काष्ठा test_string_2 escape1[] __initस्थिर = अणुअणु
	.in = "\f\\ \n\r\t\v",
	.s1 = अणुअणु
		.out = "\f\\134\\040\n\\015\\011\v",
		.flags = ESCAPE_OCTAL,
	पूर्ण,अणु
		.out = "\f\\x5c\\x20\n\\x0d\\x09\v",
		.flags = ESCAPE_HEX,
	पूर्ण,अणु
		/* terminator */
	पूर्णपूर्ण,
पूर्ण,अणु
	.in = "\\h\\\"\a\e\\",
	.s1 = अणुअणु
		.out = "\\134h\\134\"\a\e\\134",
		.flags = ESCAPE_OCTAL,
	पूर्ण,अणु
		/* terminator */
	पूर्णपूर्ण,
पूर्ण,अणु
	.in = "\eb \\C\007\"\x90\r]",
	.s1 = अणुअणु
		.out = "\e\\142\\040\\134C\007\"\x90\\015]",
		.flags = ESCAPE_OCTAL,
	पूर्ण,अणु
		/* terminator */
	पूर्णपूर्ण,
पूर्ण,अणु
	/* terminator */
पूर्णपूर्ण;

अटल स्थिर काष्ठा test_string strings_upper[] __initस्थिर = अणु
	अणु
		.in = "abcdefgh1234567890test",
		.out = "ABCDEFGH1234567890TEST",
	पूर्ण,
	अणु
		.in = "abCdeFgH1234567890TesT",
		.out = "ABCDEFGH1234567890TEST",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा test_string strings_lower[] __initस्थिर = अणु
	अणु
		.in = "ABCDEFGH1234567890TEST",
		.out = "abcdefgh1234567890test",
	पूर्ण,
	अणु
		.in = "abCdeFgH1234567890TesT",
		.out = "abcdefgh1234567890test",
	पूर्ण,
पूर्ण;

अटल __init स्थिर अक्षर *test_string_find_match(स्थिर काष्ठा test_string_2 *s2,
						 अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा test_string_1 *s1 = s2->s1;
	अचिन्हित पूर्णांक i;

	अगर (!flags)
		वापस s2->in;

	/* Test हालs are शून्य-aware */
	flags &= ~ESCAPE_शून्य;

	/* ESCAPE_OCTAL has a higher priority */
	अगर (flags & ESCAPE_OCTAL)
		flags &= ~ESCAPE_HEX;

	क्रम (i = 0; i < TEST_STRING_2_MAX_S1 && s1->out; i++, s1++)
		अगर (s1->flags == flags)
			वापस s1->out;
	वापस शून्य;
पूर्ण

अटल __init व्योम
test_string_escape_overflow(स्थिर अक्षर *in, पूर्णांक p, अचिन्हित पूर्णांक flags, स्थिर अक्षर *esc,
			    पूर्णांक q_test, स्थिर अक्षर *name)
अणु
	पूर्णांक q_real;

	q_real = string_escape_mem(in, p, शून्य, 0, flags, esc);
	अगर (q_real != q_test)
		pr_warn("Test '%s' failed: flags = %u, osz = 0, expected %d, got %d\n",
			name, flags, q_test, q_real);
पूर्ण

अटल __init व्योम test_string_escape(स्थिर अक्षर *name,
				      स्थिर काष्ठा test_string_2 *s2,
				      अचिन्हित पूर्णांक flags, स्थिर अक्षर *esc)
अणु
	माप_प्रकार out_size = 512;
	अक्षर *out_test = kदो_स्मृति(out_size, GFP_KERNEL);
	अक्षर *out_real = kदो_स्मृति(out_size, GFP_KERNEL);
	अक्षर *in = kदो_स्मृति(256, GFP_KERNEL);
	पूर्णांक p = 0, q_test = 0;
	पूर्णांक q_real;

	अगर (!out_test || !out_real || !in)
		जाओ out;

	क्रम (; s2->in; s2++) अणु
		स्थिर अक्षर *out;
		पूर्णांक len;

		/* शून्य injection */
		अगर (flags & ESCAPE_शून्य) अणु
			in[p++] = '\0';
			out_test[q_test++] = '\\';
			out_test[q_test++] = '0';
		पूर्ण

		/* Don't try strings that have no output */
		out = test_string_find_match(s2, flags);
		अगर (!out)
			जारी;

		/* Copy string to in buffer */
		len = म_माप(s2->in);
		स_नकल(&in[p], s2->in, len);
		p += len;

		/* Copy expected result क्रम given flags */
		len = म_माप(out);
		स_नकल(&out_test[q_test], out, len);
		q_test += len;
	पूर्ण

	q_real = string_escape_mem(in, p, out_real, out_size, flags, esc);

	test_string_check_buf(name, flags, in, p, out_real, q_real, out_test,
			      q_test);

	test_string_escape_overflow(in, p, flags, esc, q_test, name);

out:
	kमुक्त(in);
	kमुक्त(out_real);
	kमुक्त(out_test);
पूर्ण

#घोषणा string_get_size_maxbuf 16
#घोषणा test_string_get_size_one(size, blk_size, exp_result10, exp_result2)    \
	करो अणु                                                                   \
		BUILD_BUG_ON(माप(exp_result10) >= string_get_size_maxbuf);  \
		BUILD_BUG_ON(माप(exp_result2) >= string_get_size_maxbuf);   \
		__test_string_get_size((size), (blk_size), (exp_result10),     \
				       (exp_result2));                         \
	पूर्ण जबतक (0)


अटल __init व्योम test_string_get_size_check(स्थिर अक्षर *units,
					      स्थिर अक्षर *exp,
					      अक्षर *res,
					      स्थिर u64 size,
					      स्थिर u64 blk_size)
अणु
	अगर (!स_भेद(res, exp, म_माप(exp) + 1))
		वापस;

	res[string_get_size_maxbuf - 1] = '\0';

	pr_warn("Test 'test_string_get_size' failed!\n");
	pr_warn("string_get_size(size = %llu, blk_size = %llu, units = %s)\n",
		size, blk_size, units);
	pr_warn("expected: '%s', got '%s'\n", exp, res);
पूर्ण

अटल __init व्योम __test_string_get_size(स्थिर u64 size, स्थिर u64 blk_size,
					  स्थिर अक्षर *exp_result10,
					  स्थिर अक्षर *exp_result2)
अणु
	अक्षर buf10[string_get_size_maxbuf];
	अक्षर buf2[string_get_size_maxbuf];

	string_get_size(size, blk_size, STRING_UNITS_10, buf10, माप(buf10));
	string_get_size(size, blk_size, STRING_UNITS_2, buf2, माप(buf2));

	test_string_get_size_check("STRING_UNITS_10", exp_result10, buf10,
				   size, blk_size);

	test_string_get_size_check("STRING_UNITS_2", exp_result2, buf2,
				   size, blk_size);
पूर्ण

अटल __init व्योम test_string_get_size(व्योम)
अणु
	/* small values */
	test_string_get_size_one(0, 512, "0 B", "0 B");
	test_string_get_size_one(1, 512, "512 B", "512 B");
	test_string_get_size_one(1100, 1, "1.10 kB", "1.07 KiB");

	/* normal values */
	test_string_get_size_one(16384, 512, "8.39 MB", "8.00 MiB");
	test_string_get_size_one(500118192, 512, "256 GB", "238 GiB");
	test_string_get_size_one(8192, 4096, "33.6 MB", "32.0 MiB");

	/* weird block sizes */
	test_string_get_size_one(3000, 1900, "5.70 MB", "5.44 MiB");

	/* huge values */
	test_string_get_size_one(U64_MAX, 4096, "75.6 ZB", "64.0 ZiB");
	test_string_get_size_one(4096, U64_MAX, "75.6 ZB", "64.0 ZiB");
पूर्ण

अटल व्योम __init test_string_upper_lower(व्योम)
अणु
	अक्षर *dst;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(strings_upper); i++) अणु
		स्थिर अक्षर *s = strings_upper[i].in;
		पूर्णांक len = म_माप(strings_upper[i].in) + 1;

		dst = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!dst)
			वापस;

		string_upper(dst, s);
		अगर (स_भेद(dst, strings_upper[i].out, len)) अणु
			pr_warn("Test 'string_upper' failed : expected %s, got %s!\n",
				strings_upper[i].out, dst);
			kमुक्त(dst);
			वापस;
		पूर्ण
		kमुक्त(dst);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(strings_lower); i++) अणु
		स्थिर अक्षर *s = strings_lower[i].in;
		पूर्णांक len = म_माप(strings_lower[i].in) + 1;

		dst = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!dst)
			वापस;

		string_lower(dst, s);
		अगर (स_भेद(dst, strings_lower[i].out, len)) अणु
			pr_warn("Test 'string_lower failed : : expected %s, got %s!\n",
				strings_lower[i].out, dst);
			kमुक्त(dst);
			वापस;
		पूर्ण
		kमुक्त(dst);
	पूर्ण
पूर्ण

अटल पूर्णांक __init test_string_helpers_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	pr_info("Running tests...\n");
	क्रम (i = 0; i < UNESCAPE_ANY + 1; i++)
		test_string_unescape("unescape", i, false);
	test_string_unescape("unescape inplace",
			     get_अक्रमom_पूर्णांक() % (UNESCAPE_ANY + 1), true);

	/* Without dictionary */
	क्रम (i = 0; i < (ESCAPE_ANY_NP | ESCAPE_HEX) + 1; i++)
		test_string_escape("escape 0", escape0, i, TEST_STRING_2_DICT_0);

	/* With dictionary */
	क्रम (i = 0; i < (ESCAPE_ANY_NP | ESCAPE_HEX) + 1; i++)
		test_string_escape("escape 1", escape1, i, TEST_STRING_2_DICT_1);

	/* Test string_get_size() */
	test_string_get_size();

	/* Test string upper(), string_lower() */
	test_string_upper_lower();

	वापस -EINVAL;
पूर्ण
module_init(test_string_helpers_init);
MODULE_LICENSE("Dual BSD/GPL");
