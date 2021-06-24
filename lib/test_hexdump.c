<शैली गुरु>
/*
 * Test हालs क्रम lib/hexdump.c module.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>

अटल स्थिर अचिन्हित अक्षर data_b[] = अणु
	'\xbe', '\x32', '\xdb', '\x7b', '\x0a', '\x18', '\x93', '\xb2',	/* 00 - 07 */
	'\x70', '\xba', '\xc4', '\x24', '\x7d', '\x83', '\x34', '\x9b',	/* 08 - 0f */
	'\xa6', '\x9c', '\x31', '\xad', '\x9c', '\x0f', '\xac', '\xe9',	/* 10 - 17 */
	'\x4c', '\xd1', '\x19', '\x99', '\x43', '\xb1', '\xaf', '\x0c',	/* 18 - 1f */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर data_a[] = ".2.{....p..$}.4...1.....L...C...";

अटल स्थिर अक्षर * स्थिर test_data_1[] __initस्थिर = अणु
	"be", "32", "db", "7b", "0a", "18", "93", "b2",
	"70", "ba", "c4", "24", "7d", "83", "34", "9b",
	"a6", "9c", "31", "ad", "9c", "0f", "ac", "e9",
	"4c", "d1", "19", "99", "43", "b1", "af", "0c",
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_data_2_le[] __initस्थिर = अणु
	"32be", "7bdb", "180a", "b293",
	"ba70", "24c4", "837d", "9b34",
	"9ca6", "ad31", "0f9c", "e9ac",
	"d14c", "9919", "b143", "0caf",
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_data_2_be[] __initस्थिर = अणु
	"be32", "db7b", "0a18", "93b2",
	"70ba", "c424", "7d83", "349b",
	"a69c", "31ad", "9c0f", "ace9",
	"4cd1", "1999", "43b1", "af0c",
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_data_4_le[] __initस्थिर = अणु
	"7bdb32be", "b293180a", "24c4ba70", "9b34837d",
	"ad319ca6", "e9ac0f9c", "9919d14c", "0cafb143",
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_data_4_be[] __initस्थिर = अणु
	"be32db7b", "0a1893b2", "70bac424", "7d83349b",
	"a69c31ad", "9c0face9", "4cd11999", "43b1af0c",
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_data_8_le[] __initस्थिर = अणु
	"b293180a7bdb32be", "9b34837d24c4ba70",
	"e9ac0f9cad319ca6", "0cafb1439919d14c",
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_data_8_be[] __initस्थिर = अणु
	"be32db7b0a1893b2", "70bac4247d83349b",
	"a69c31ad9c0face9", "4cd1199943b1af0c",
पूर्ण;

#घोषणा FILL_CHAR	'#'

अटल अचिन्हित total_tests __initdata;
अटल अचिन्हित failed_tests __initdata;

अटल व्योम __init test_hexdump_prepare_test(माप_प्रकार len, पूर्णांक rowsize,
					     पूर्णांक groupsize, अक्षर *test,
					     माप_प्रकार testlen, bool ascii)
अणु
	अक्षर *p;
	स्थिर अक्षर * स्थिर *result;
	माप_प्रकार l = len;
	पूर्णांक gs = groupsize, rs = rowsize;
	अचिन्हित पूर्णांक i;
	स्थिर bool is_be = IS_ENABLED(CONFIG_CPU_BIG_ENDIAN);

	अगर (rs != 16 && rs != 32)
		rs = 16;

	अगर (l > rs)
		l = rs;

	अगर (!is_घातer_of_2(gs) || gs > 8 || (len % gs != 0))
		gs = 1;

	अगर (gs == 8)
		result = is_be ? test_data_8_be : test_data_8_le;
	अन्यथा अगर (gs == 4)
		result = is_be ? test_data_4_be : test_data_4_le;
	अन्यथा अगर (gs == 2)
		result = is_be ? test_data_2_be : test_data_2_le;
	अन्यथा
		result = test_data_1;

	/* hex dump */
	p = test;
	क्रम (i = 0; i < l / gs; i++) अणु
		स्थिर अक्षर *q = *result++;
		माप_प्रकार amount = म_माप(q);

		स_नकल(p, q, amount);
		p += amount;

		*p++ = ' ';
	पूर्ण
	अगर (i)
		p--;

	/* ASCII part */
	अगर (ascii) अणु
		करो अणु
			*p++ = ' ';
		पूर्ण जबतक (p < test + rs * 2 + rs / gs + 1);

		म_नकलन(p, data_a, l);
		p += l;
	पूर्ण

	*p = '\0';
पूर्ण

#घोषणा TEST_HEXDUMP_BUF_SIZE		(32 * 3 + 2 + 32 + 1)

अटल व्योम __init test_hexdump(माप_प्रकार len, पूर्णांक rowsize, पूर्णांक groupsize,
				bool ascii)
अणु
	अक्षर test[TEST_HEXDUMP_BUF_SIZE];
	अक्षर real[TEST_HEXDUMP_BUF_SIZE];

	total_tests++;

	स_रखो(real, FILL_CHAR, माप(real));
	hex_dump_to_buffer(data_b, len, rowsize, groupsize, real, माप(real),
			   ascii);

	स_रखो(test, FILL_CHAR, माप(test));
	test_hexdump_prepare_test(len, rowsize, groupsize, test, माप(test),
				  ascii);

	अगर (स_भेद(test, real, TEST_HEXDUMP_BUF_SIZE)) अणु
		pr_err("Len: %zu row: %d group: %d\n", len, rowsize, groupsize);
		pr_err("Result: '%s'\n", real);
		pr_err("Expect: '%s'\n", test);
		failed_tests++;
	पूर्ण
पूर्ण

अटल व्योम __init test_hexdump_set(पूर्णांक rowsize, bool ascii)
अणु
	माप_प्रकार d = min_t(माप_प्रकार, माप(data_b), rowsize);
	माप_प्रकार len = get_अक्रमom_पूर्णांक() % d + 1;

	test_hexdump(len, rowsize, 4, ascii);
	test_hexdump(len, rowsize, 2, ascii);
	test_hexdump(len, rowsize, 8, ascii);
	test_hexdump(len, rowsize, 1, ascii);
पूर्ण

अटल व्योम __init test_hexdump_overflow(माप_प्रकार buflen, माप_प्रकार len,
					 पूर्णांक rowsize, पूर्णांक groupsize,
					 bool ascii)
अणु
	अक्षर test[TEST_HEXDUMP_BUF_SIZE];
	अक्षर buf[TEST_HEXDUMP_BUF_SIZE];
	पूर्णांक rs = rowsize, gs = groupsize;
	पूर्णांक ae, he, e, f, r;
	bool a;

	total_tests++;

	स_रखो(buf, FILL_CHAR, माप(buf));

	r = hex_dump_to_buffer(data_b, len, rs, gs, buf, buflen, ascii);

	/*
	 * Caller must provide the data length multiple of groupsize. The
	 * calculations below are made with that assumption in mind.
	 */
	ae = rs * 2 /* hex */ + rs / gs /* spaces */ + 1 /* space */ + len /* ascii */;
	he = (gs * 2 /* hex */ + 1 /* space */) * len / gs - 1 /* no trailing space */;

	अगर (ascii)
		e = ae;
	अन्यथा
		e = he;

	f = min_t(पूर्णांक, e + 1, buflen);
	अगर (buflen) अणु
		test_hexdump_prepare_test(len, rs, gs, test, माप(test), ascii);
		test[f - 1] = '\0';
	पूर्ण
	स_रखो(test + f, FILL_CHAR, माप(test) - f);

	a = r == e && !स_भेद(test, buf, TEST_HEXDUMP_BUF_SIZE);

	buf[माप(buf) - 1] = '\0';

	अगर (!a) अणु
		pr_err("Len: %zu buflen: %zu strlen: %zu\n",
			len, buflen, strnlen(buf, माप(buf)));
		pr_err("Result: %d '%s'\n", r, buf);
		pr_err("Expect: %d '%s'\n", e, test);
		failed_tests++;
	पूर्ण
पूर्ण

अटल व्योम __init test_hexdump_overflow_set(माप_प्रकार buflen, bool ascii)
अणु
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक rs = (get_अक्रमom_पूर्णांक() % 2 + 1) * 16;

	करो अणु
		पूर्णांक gs = 1 << i;
		माप_प्रकार len = get_अक्रमom_पूर्णांक() % rs + gs;

		test_hexdump_overflow(buflen, roundकरोwn(len, gs), rs, gs, ascii);
	पूर्ण जबतक (i++ < 3);
पूर्ण

अटल पूर्णांक __init test_hexdump_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rowsize;

	rowsize = (get_अक्रमom_पूर्णांक() % 2 + 1) * 16;
	क्रम (i = 0; i < 16; i++)
		test_hexdump_set(rowsize, false);

	rowsize = (get_अक्रमom_पूर्णांक() % 2 + 1) * 16;
	क्रम (i = 0; i < 16; i++)
		test_hexdump_set(rowsize, true);

	क्रम (i = 0; i <= TEST_HEXDUMP_BUF_SIZE; i++)
		test_hexdump_overflow_set(i, false);

	क्रम (i = 0; i <= TEST_HEXDUMP_BUF_SIZE; i++)
		test_hexdump_overflow_set(i, true);

	अगर (failed_tests == 0)
		pr_info("all %u tests passed\n", total_tests);
	अन्यथा
		pr_err("failed %u out of %u tests\n", failed_tests, total_tests);

	वापस failed_tests ? -EINVAL : 0;
पूर्ण
module_init(test_hexdump_init);

अटल व्योम __निकास test_hexdump_निकास(व्योम)
अणु
	/* करो nothing */
पूर्ण
module_निकास(test_hexdump_निकास);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_LICENSE("Dual BSD/GPL");
