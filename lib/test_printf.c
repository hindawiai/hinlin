<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test हालs क्रम म_लिखो facility.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/dcache.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>

#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>

#समावेश <linux/property.h>

#समावेश "../tools/testing/selftests/kselftest_module.h"

#घोषणा BUF_SIZE 256
#घोषणा PAD_SIZE 16
#घोषणा FILL_CHAR '$'

KSTM_MODULE_GLOBALS();

अटल अक्षर *test_buffer __initdata;
अटल अक्षर *alloced_buffer __initdata;

बाह्य bool no_hash_poपूर्णांकers;

अटल पूर्णांक __म_लिखो(4, 0) __init
करो_test(पूर्णांक bufsize, स्थिर अक्षर *expect, पूर्णांक elen,
	स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	बहु_सूची aq;
	पूर्णांक ret, written;

	total_tests++;

	स_रखो(alloced_buffer, FILL_CHAR, BUF_SIZE + 2*PAD_SIZE);
	va_copy(aq, ap);
	ret = vsnम_लिखो(test_buffer, bufsize, fmt, aq);
	बहु_पूर्ण(aq);

	अगर (ret != elen) अणु
		pr_warn("vsnprintf(buf, %d, \"%s\", ...) returned %d, expected %d\n",
			bufsize, fmt, ret, elen);
		वापस 1;
	पूर्ण

	अगर (स_प्रथम_inv(alloced_buffer, FILL_CHAR, PAD_SIZE)) अणु
		pr_warn("vsnprintf(buf, %d, \"%s\", ...) wrote before buffer\n", bufsize, fmt);
		वापस 1;
	पूर्ण

	अगर (!bufsize) अणु
		अगर (स_प्रथम_inv(test_buffer, FILL_CHAR, BUF_SIZE + PAD_SIZE)) अणु
			pr_warn("vsnprintf(buf, 0, \"%s\", ...) wrote to buffer\n",
				fmt);
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण

	written = min(bufsize-1, elen);
	अगर (test_buffer[written]) अणु
		pr_warn("vsnprintf(buf, %d, \"%s\", ...) did not nul-terminate buffer\n",
			bufsize, fmt);
		वापस 1;
	पूर्ण

	अगर (स_प्रथम_inv(test_buffer + written + 1, FILL_CHAR, BUF_SIZE + PAD_SIZE - (written + 1))) अणु
		pr_warn("vsnprintf(buf, %d, \"%s\", ...) wrote beyond the nul-terminator\n",
			bufsize, fmt);
		वापस 1;
	पूर्ण

	अगर (स_भेद(test_buffer, expect, written)) अणु
		pr_warn("vsnprintf(buf, %d, \"%s\", ...) wrote '%s', expected '%.*s'\n",
			bufsize, fmt, test_buffer, written, expect);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __म_लिखो(3, 4) __init
__test(स्थिर अक्षर *expect, पूर्णांक elen, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक अक्रम;
	अक्षर *p;

	अगर (elen >= BUF_SIZE) अणु
		pr_err("error in test suite: expected output length %d too long. Format was '%s'.\n",
		       elen, fmt);
		failed_tests++;
		वापस;
	पूर्ण

	बहु_शुरू(ap, fmt);

	/*
	 * Every fmt+args is subjected to four tests: Three where we
	 * tell vsnम_लिखो varying buffer sizes (plenty, not quite
	 * enough and 0), and then we also test that kvaप्र_लिखो would
	 * be able to prपूर्णांक it as expected.
	 */
	failed_tests += करो_test(BUF_SIZE, expect, elen, fmt, ap);
	अक्रम = 1 + pअक्रमom_u32_max(elen+1);
	/* Since elen < BUF_SIZE, we have 1 <= अक्रम <= BUF_SIZE. */
	failed_tests += करो_test(अक्रम, expect, elen, fmt, ap);
	failed_tests += करो_test(0, expect, elen, fmt, ap);

	p = kvaप्र_लिखो(GFP_KERNEL, fmt, ap);
	अगर (p) अणु
		total_tests++;
		अगर (स_भेद(p, expect, elen+1)) अणु
			pr_warn("kvasprintf(..., \"%s\", ...) returned '%s', expected '%s'\n",
				fmt, p, expect);
			failed_tests++;
		पूर्ण
		kमुक्त(p);
	पूर्ण
	बहु_पूर्ण(ap);
पूर्ण

#घोषणा test(expect, fmt, ...)					\
	__test(expect, म_माप(expect), fmt, ##__VA_ARGS__)

अटल व्योम __init
test_basic(व्योम)
अणु
	/* Work around annoying "warning: zero-length gnu_printf format string". */
	अक्षर nul = '\0';

	test("", &nul);
	test("100%", "100%%");
	test("xxx%yyy", "xxx%cyyy", '%');
	__test("xxx\0yyy", 7, "xxx%cyyy", '\0');
पूर्ण

अटल व्योम __init
test_number(व्योम)
अणु
	test("0x1234abcd  ", "%#-12x", 0x1234abcd);
	test("  0x1234abcd", "%#12x", 0x1234abcd);
	test("0|001| 12|+123| 1234|-123|-1234", "%d|%03d|%3d|%+d|% d|%+d|% d", 0, 1, 12, 123, 1234, -123, -1234);
	test("0|1|1|128|255", "%hhu|%hhu|%hhu|%hhu|%hhu", 0, 1, 257, 128, -1);
	test("0|1|1|-128|-1", "%hhd|%hhd|%hhd|%hhd|%hhd", 0, 1, 257, 128, -1);
	test("2015122420151225", "%ho%ho%#ho", 1037, 5282, -11627);
	/*
	 * POSIX/C99: तझThe result of converting zero with an explicit
	 * precision of zero shall be no अक्षरacters.त+ Hence the output
	 * from the below test should really be "00|0||| ". However,
	 * the kernel's म_लिखो also produces a single 0 in that
	 * हाल. This test हाल simply करोcuments the current
	 * behaviour.
	 */
	test("00|0|0|0|0", "%.2d|%.1d|%.0d|%.*d|%1.0d", 0, 0, 0, 0, 0, 0);
#अगर_अघोषित __CHAR_UNSIGNED__
	अणु
		/*
		 * Passing a 'char' to a %02x specifier doesn't करो
		 * what was presumably the पूर्णांकention when अक्षर is
		 * चिन्हित and the value is negative. One must either &
		 * with 0xff or cast to u8.
		 */
		अक्षर val = -16;
		test("0xfffffff0|0xf0|0xf0", "%#02x|%#02x|%#02x", val, val & 0xff, (u8)val);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init
test_string(व्योम)
अणु
	test("", "%s%.0s", "", "123");
	test("ABCD|abc|123", "%s|%.3s|%.*s", "ABCD", "abcdef", 3, "123456");
	test("1  |  2|3  |  4|5  ", "%-3s|%3s|%-*s|%*s|%*s", "1", "2", 3, "3", 3, "4", -3, "5");
	test("1234      ", "%-10.4s", "123456");
	test("      1234", "%10.4s", "123456");
	/*
	 * POSIX and C99 say that a negative precision (which is only
	 * possible to pass via a * argument) should be treated as अगर
	 * the precision wasn't present, and that अगर the precision is
	 * omitted (as in %.s), the precision should be taken to be
	 * 0. However, the kernel's म_लिखो behave exactly opposite,
	 * treating a negative precision as 0 and treating an omitted
	 * precision specअगरier as अगर no precision was given.
	 *
	 * These test हालs करोcument the current behaviour; should
	 * anyone ever feel the need to follow the standards more
	 * बंदly, this can be revisited.
	 */
	test("    ", "%4.*s", -5, "123456");
	test("123456", "%.s", "123456");
	test("a||", "%.s|%.0s|%.*s", "a", "b", 0, "c");
	test("a  |   |   ", "%-3.s|%-3.0s|%-3.*s", "a", "b", 0, "c");
पूर्ण

#घोषणा PLAIN_BUF_SIZE 64	/* leave some space so we करोn't oops */

#अगर BITS_PER_LONG == 64

#घोषणा PTR_WIDTH 16
#घोषणा PTR ((व्योम *)0xffff0123456789abUL)
#घोषणा PTR_STR "ffff0123456789ab"
#घोषणा PTR_VAL_NO_CRNG "(____ptrval____)"
#घोषणा ZEROS "00000000"	/* hex 32 zero bits */
#घोषणा ONES "ffffffff"		/* hex 32 one bits */

अटल पूर्णांक __init
plain_क्रमmat(व्योम)
अणु
	अक्षर buf[PLAIN_BUF_SIZE];
	पूर्णांक nअक्षरs;

	nअक्षरs = snम_लिखो(buf, PLAIN_BUF_SIZE, "%p", PTR);

	अगर (nअक्षरs != PTR_WIDTH)
		वापस -1;

	अगर (म_भेदन(buf, PTR_VAL_NO_CRNG, PTR_WIDTH) == 0) अणु
		pr_warn("crng possibly not yet initialized. plain 'p' buffer contains \"%s\"",
			PTR_VAL_NO_CRNG);
		वापस 0;
	पूर्ण

	अगर (म_भेदन(buf, ZEROS, म_माप(ZEROS)) != 0)
		वापस -1;

	वापस 0;
पूर्ण

#अन्यथा

#घोषणा PTR_WIDTH 8
#घोषणा PTR ((व्योम *)0x456789ab)
#घोषणा PTR_STR "456789ab"
#घोषणा PTR_VAL_NO_CRNG "(ptrval)"
#घोषणा ZEROS ""
#घोषणा ONES ""

अटल पूर्णांक __init
plain_क्रमmat(व्योम)
अणु
	/* Format is implicitly tested क्रम 32 bit machines by plain_hash() */
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* BITS_PER_LONG == 64 */

अटल पूर्णांक __init
plain_hash_to_buffer(स्थिर व्योम *p, अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक nअक्षरs;

	nअक्षरs = snम_लिखो(buf, len, "%p", p);

	अगर (nअक्षरs != PTR_WIDTH)
		वापस -1;

	अगर (म_भेदन(buf, PTR_VAL_NO_CRNG, PTR_WIDTH) == 0) अणु
		pr_warn("crng possibly not yet initialized. plain 'p' buffer contains \"%s\"",
			PTR_VAL_NO_CRNG);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init
plain_hash(व्योम)
अणु
	अक्षर buf[PLAIN_BUF_SIZE];
	पूर्णांक ret;

	ret = plain_hash_to_buffer(PTR, buf, PLAIN_BUF_SIZE);
	अगर (ret)
		वापस ret;

	अगर (म_भेदन(buf, PTR_STR, PTR_WIDTH) == 0)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * We can't use test() to test %p because we don't know what output to expect
 * after an address is hashed.
 */
अटल व्योम __init
plain(व्योम)
अणु
	पूर्णांक err;

	अगर (no_hash_poपूर्णांकers) अणु
		pr_warn("skipping plain 'p' tests");
		skipped_tests += 2;
		वापस;
	पूर्ण

	err = plain_hash();
	अगर (err) अणु
		pr_warn("plain 'p' does not appear to be hashed\n");
		failed_tests++;
		वापस;
	पूर्ण

	err = plain_क्रमmat();
	अगर (err) अणु
		pr_warn("hashing plain 'p' has unexpected format\n");
		failed_tests++;
	पूर्ण
पूर्ण

अटल व्योम __init
test_hashed(स्थिर अक्षर *fmt, स्थिर व्योम *p)
अणु
	अक्षर buf[PLAIN_BUF_SIZE];
	पूर्णांक ret;

	/*
	 * No need to increase failed test counter since this is assumed
	 * to be called after plain().
	 */
	ret = plain_hash_to_buffer(p, buf, PLAIN_BUF_SIZE);
	अगर (ret)
		वापस;

	test(buf, fmt, p);
पूर्ण

/*
 * शून्य poपूर्णांकers aren't hashed.
 */
अटल व्योम __init
null_poपूर्णांकer(व्योम)
अणु
	test(ZEROS "00000000", "%p", शून्य);
	test(ZEROS "00000000", "%px", शून्य);
	test("(null)", "%pE", शून्य);
पूर्ण

/*
 * Error poपूर्णांकers aren't hashed.
 */
अटल व्योम __init
error_poपूर्णांकer(व्योम)
अणु
	test(ONES "fffffff5", "%p", ERR_PTR(-11));
	test(ONES "fffffff5", "%px", ERR_PTR(-11));
	test("(efault)", "%pE", ERR_PTR(-11));
पूर्ण

#घोषणा PTR_INVALID ((व्योम *)0x000000ab)

अटल व्योम __init
invalid_poपूर्णांकer(व्योम)
अणु
	test_hashed("%p", PTR_INVALID);
	test(ZEROS "000000ab", "%px", PTR_INVALID);
	test("(efault)", "%pE", PTR_INVALID);
पूर्ण

अटल व्योम __init
symbol_ptr(व्योम)
अणु
पूर्ण

अटल व्योम __init
kernel_ptr(व्योम)
अणु
	/* We can't test this without access to kptr_restrict. */
पूर्ण

अटल व्योम __init
काष्ठा_resource(व्योम)
अणु
पूर्ण

अटल व्योम __init
addr(व्योम)
अणु
पूर्ण

अटल व्योम __init
escaped_str(व्योम)
अणु
पूर्ण

अटल व्योम __init
hex_string(व्योम)
अणु
	स्थिर अक्षर buf[3] = अणु0xc0, 0xff, 0xeeपूर्ण;

	test("c0 ff ee|c0:ff:ee|c0-ff-ee|c0ffee",
	     "%3ph|%3phC|%3phD|%3phN", buf, buf, buf, buf);
	test("c0 ff ee|c0:ff:ee|c0-ff-ee|c0ffee",
	     "%*ph|%*phC|%*phD|%*phN", 3, buf, 3, buf, 3, buf, 3, buf);
पूर्ण

अटल व्योम __init
mac(व्योम)
अणु
	स्थिर u8 addr[6] = अणु0x2d, 0x48, 0xd6, 0xfc, 0x7a, 0x05पूर्ण;

	test("2d:48:d6:fc:7a:05", "%pM", addr);
	test("05:7a:fc:d6:48:2d", "%pMR", addr);
	test("2d-48-d6-fc-7a-05", "%pMF", addr);
	test("2d48d6fc7a05", "%pm", addr);
	test("057afcd6482d", "%pmR", addr);
पूर्ण

अटल व्योम __init
ip4(व्योम)
अणु
	काष्ठा sockaddr_in sa;

	sa.sin_family = AF_INET;
	sa.sin_port = cpu_to_be16(12345);
	sa.sin_addr.s_addr = cpu_to_be32(0x7f000001);

	test("127.000.000.001|127.0.0.1", "%pi4|%pI4", &sa.sin_addr, &sa.sin_addr);
	test("127.000.000.001|127.0.0.1", "%piS|%pIS", &sa, &sa);
	sa.sin_addr.s_addr = cpu_to_be32(0x01020304);
	test("001.002.003.004:12345|1.2.3.4:12345", "%piSp|%pISp", &sa, &sa);
पूर्ण

अटल व्योम __init
ip6(व्योम)
अणु
पूर्ण

अटल व्योम __init
ip(व्योम)
अणु
	ip4();
	ip6();
पूर्ण

अटल व्योम __init
uuid(व्योम)
अणु
	स्थिर अक्षर uuid[16] = अणु0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
			       0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xfपूर्ण;

	test("00010203-0405-0607-0809-0a0b0c0d0e0f", "%pUb", uuid);
	test("00010203-0405-0607-0809-0A0B0C0D0E0F", "%pUB", uuid);
	test("03020100-0504-0706-0809-0a0b0c0d0e0f", "%pUl", uuid);
	test("03020100-0504-0706-0809-0A0B0C0D0E0F", "%pUL", uuid);
पूर्ण

अटल काष्ठा dentry test_dentry[4] __initdata = अणु
	अणु .d_parent = &test_dentry[0],
	  .d_name = QSTR_INIT(test_dentry[0].d_iname, 3),
	  .d_iname = "foo" पूर्ण,
	अणु .d_parent = &test_dentry[0],
	  .d_name = QSTR_INIT(test_dentry[1].d_iname, 5),
	  .d_iname = "bravo" पूर्ण,
	अणु .d_parent = &test_dentry[1],
	  .d_name = QSTR_INIT(test_dentry[2].d_iname, 4),
	  .d_iname = "alfa" पूर्ण,
	अणु .d_parent = &test_dentry[2],
	  .d_name = QSTR_INIT(test_dentry[3].d_iname, 5),
	  .d_iname = "romeo" पूर्ण,
पूर्ण;

अटल व्योम __init
dentry(व्योम)
अणु
	test("foo", "%pd", &test_dentry[0]);
	test("foo", "%pd2", &test_dentry[0]);

	test("(null)", "%pd", शून्य);
	test("(efault)", "%pd", PTR_INVALID);
	test("(null)", "%pD", शून्य);
	test("(efault)", "%pD", PTR_INVALID);

	test("romeo", "%pd", &test_dentry[3]);
	test("alfa/romeo", "%pd2", &test_dentry[3]);
	test("bravo/alfa/romeo", "%pd3", &test_dentry[3]);
	test("/bravo/alfa/romeo", "%pd4", &test_dentry[3]);
	test("/bravo/alfa", "%pd4", &test_dentry[2]);

	test("bravo/alfa  |bravo/alfa  ", "%-12pd2|%*pd2", &test_dentry[2], -12, &test_dentry[2]);
	test("  bravo/alfa|  bravo/alfa", "%12pd2|%*pd2", &test_dentry[2], 12, &test_dentry[2]);
पूर्ण

अटल व्योम __init
काष्ठा_va_क्रमmat(व्योम)
अणु
पूर्ण

अटल व्योम __init
समय_and_date(व्योम)
अणु
	/* 1543210543 */
	स्थिर काष्ठा rtc_समय पंचांग = अणु
		.पंचांग_sec = 43,
		.पंचांग_min = 35,
		.पंचांग_hour = 5,
		.पंचांग_mday = 26,
		.पंचांग_mon = 10,
		.पंचांग_year = 118,
	पूर्ण;
	/* 2019-01-04T15:32:23 */
	समय64_t t = 1546615943;

	test("(%pt?)", "%pt", &पंचांग);
	test("2018-11-26T05:35:43", "%ptR", &पंचांग);
	test("0118-10-26T05:35:43", "%ptRr", &पंचांग);
	test("05:35:43|2018-11-26", "%ptRt|%ptRd", &पंचांग, &पंचांग);
	test("05:35:43|0118-10-26", "%ptRtr|%ptRdr", &पंचांग, &पंचांग);
	test("05:35:43|2018-11-26", "%ptRttr|%ptRdtr", &पंचांग, &पंचांग);
	test("05:35:43 tr|2018-11-26 tr", "%ptRt tr|%ptRd tr", &पंचांग, &पंचांग);

	test("2019-01-04T15:32:23", "%ptT", &t);
	test("0119-00-04T15:32:23", "%ptTr", &t);
	test("15:32:23|2019-01-04", "%ptTt|%ptTd", &t, &t);
	test("15:32:23|0119-00-04", "%ptTtr|%ptTdr", &t, &t);
पूर्ण

अटल व्योम __init
काष्ठा_clk(व्योम)
अणु
पूर्ण

अटल व्योम __init
large_biपंचांगap(व्योम)
अणु
	स्थिर पूर्णांक nbits = 1 << 16;
	अचिन्हित दीर्घ *bits = biपंचांगap_zalloc(nbits, GFP_KERNEL);
	अगर (!bits)
		वापस;

	biपंचांगap_set(bits, 1, 20);
	biपंचांगap_set(bits, 60000, 15);
	test("1-20,60000-60014", "%*pbl", nbits, bits);
	biपंचांगap_मुक्त(bits);
पूर्ण

अटल व्योम __init
biपंचांगap(व्योम)
अणु
	DECLARE_BITMAP(bits, 20);
	स्थिर पूर्णांक primes[] = अणु2,3,5,7,11,13,17,19पूर्ण;
	पूर्णांक i;

	biपंचांगap_zero(bits, 20);
	test("00000|00000", "%20pb|%*pb", bits, 20, bits);
	test("|", "%20pbl|%*pbl", bits, 20, bits);

	क्रम (i = 0; i < ARRAY_SIZE(primes); ++i)
		set_bit(primes[i], bits);
	test("a28ac|a28ac", "%20pb|%*pb", bits, 20, bits);
	test("2-3,5,7,11,13,17,19|2-3,5,7,11,13,17,19", "%20pbl|%*pbl", bits, 20, bits);

	biपंचांगap_fill(bits, 20);
	test("fffff|fffff", "%20pb|%*pb", bits, 20, bits);
	test("0-19|0-19", "%20pbl|%*pbl", bits, 20, bits);

	large_biपंचांगap();
पूर्ण

अटल व्योम __init
netdev_features(व्योम)
अणु
पूर्ण

काष्ठा page_flags_test अणु
	पूर्णांक width;
	पूर्णांक shअगरt;
	पूर्णांक mask;
	अचिन्हित दीर्घ value;
	स्थिर अक्षर *fmt;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा page_flags_test pft[] = अणु
	अणुSECTIONS_WIDTH, SECTIONS_PGSHIFT, SECTIONS_MASK,
	 0, "%d", "section"पूर्ण,
	अणुNODES_WIDTH, NODES_PGSHIFT, NODES_MASK,
	 0, "%d", "node"पूर्ण,
	अणुZONES_WIDTH, ZONES_PGSHIFT, ZONES_MASK,
	 0, "%d", "zone"पूर्ण,
	अणुLAST_CPUPID_WIDTH, LAST_CPUPID_PGSHIFT, LAST_CPUPID_MASK,
	 0, "%#x", "lastcpupid"पूर्ण,
	अणुKASAN_TAG_WIDTH, KASAN_TAG_PGSHIFT, KASAN_TAG_MASK,
	 0, "%#x", "kasantag"पूर्ण,
पूर्ण;

अटल व्योम __init
page_flags_test(पूर्णांक section, पूर्णांक node, पूर्णांक zone, पूर्णांक last_cpupid,
		पूर्णांक kasan_tag, पूर्णांक flags, स्थिर अक्षर *name, अक्षर *cmp_buf)
अणु
	अचिन्हित दीर्घ values[] = अणुsection, node, zone, last_cpupid, kasan_tagपूर्ण;
	अचिन्हित दीर्घ page_flags = 0;
	अचिन्हित दीर्घ size = 0;
	bool append = false;
	पूर्णांक i;

	flags &= BIT(NR_PAGEFLAGS) - 1;
	अगर (flags) अणु
		page_flags |= flags;
		snम_लिखो(cmp_buf + size, BUF_SIZE - size, "%s", name);
		size = म_माप(cmp_buf);
#अगर SECTIONS_WIDTH || NODES_WIDTH || ZONES_WIDTH || \
	LAST_CPUPID_WIDTH || KASAN_TAG_WIDTH
		/* Other inक्रमmation also included in page flags */
		snम_लिखो(cmp_buf + size, BUF_SIZE - size, "|");
		size = म_माप(cmp_buf);
#पूर्ण_अगर
	पूर्ण

	/* Set the test value */
	क्रम (i = 0; i < ARRAY_SIZE(pft); i++)
		pft[i].value = values[i];

	क्रम (i = 0; i < ARRAY_SIZE(pft); i++) अणु
		अगर (!pft[i].width)
			जारी;

		अगर (append) अणु
			snम_लिखो(cmp_buf + size, BUF_SIZE - size, "|");
			size = म_माप(cmp_buf);
		पूर्ण

		page_flags |= (pft[i].value & pft[i].mask) << pft[i].shअगरt;
		snम_लिखो(cmp_buf + size, BUF_SIZE - size, "%s=", pft[i].name);
		size = म_माप(cmp_buf);
		snम_लिखो(cmp_buf + size, BUF_SIZE - size, pft[i].fmt,
			 pft[i].value & pft[i].mask);
		size = म_माप(cmp_buf);
		append = true;
	पूर्ण

	test(cmp_buf, "%pGp", &page_flags);
पूर्ण

अटल व्योम __init
flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर *cmp_buffer;
	gfp_t gfp;

	cmp_buffer = kदो_स्मृति(BUF_SIZE, GFP_KERNEL);
	अगर (!cmp_buffer)
		वापस;

	flags = 0;
	page_flags_test(0, 0, 0, 0, 0, flags, "", cmp_buffer);

	flags = 1UL << NR_PAGEFLAGS;
	page_flags_test(0, 0, 0, 0, 0, flags, "", cmp_buffer);

	flags |= 1UL << PG_uptodate | 1UL << PG_dirty | 1UL << PG_lru
		| 1UL << PG_active | 1UL << PG_swapbacked;
	page_flags_test(1, 1, 1, 0x1fffff, 1, flags,
			"uptodate|dirty|lru|active|swapbacked",
			cmp_buffer);

	flags = VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC
			| VM_DENYWRITE;
	test("read|exec|mayread|maywrite|mayexec|denywrite", "%pGv", &flags);

	gfp = GFP_TRANSHUGE;
	test("GFP_TRANSHUGE", "%pGg", &gfp);

	gfp = GFP_ATOMIC|__GFP_DMA;
	test("GFP_ATOMIC|GFP_DMA", "%pGg", &gfp);

	gfp = __GFP_ATOMIC;
	test("__GFP_ATOMIC", "%pGg", &gfp);

	/* Any flags not translated by the table should reमुख्य numeric */
	gfp = ~__GFP_BITS_MASK;
	snम_लिखो(cmp_buffer, BUF_SIZE, "%#lx", (अचिन्हित दीर्घ) gfp);
	test(cmp_buffer, "%pGg", &gfp);

	snम_लिखो(cmp_buffer, BUF_SIZE, "__GFP_ATOMIC|%#lx",
							(अचिन्हित दीर्घ) gfp);
	gfp |= __GFP_ATOMIC;
	test(cmp_buffer, "%pGg", &gfp);

	kमुक्त(cmp_buffer);
पूर्ण

अटल व्योम __init fwnode_poपूर्णांकer(व्योम)
अणु
	स्थिर काष्ठा software_node softnodes[] = अणु
		अणु .name = "first", पूर्ण,
		अणु .name = "second", .parent = &softnodes[0], पूर्ण,
		अणु .name = "third", .parent = &softnodes[1], पूर्ण,
		अणु शून्य /* Guardian */ पूर्ण
	पूर्ण;
	स्थिर अक्षर * स्थिर full_name = "first/second/third";
	स्थिर अक्षर * स्थिर full_name_second = "first/second";
	स्थिर अक्षर * स्थिर second_name = "second";
	स्थिर अक्षर * स्थिर third_name = "third";
	पूर्णांक rval;

	rval = software_node_रेजिस्टर_nodes(softnodes);
	अगर (rval) अणु
		pr_warn("cannot register softnodes; rval %d\n", rval);
		वापस;
	पूर्ण

	test(full_name_second, "%pfw", software_node_fwnode(&softnodes[1]));
	test(full_name, "%pfw", software_node_fwnode(&softnodes[2]));
	test(full_name, "%pfwf", software_node_fwnode(&softnodes[2]));
	test(second_name, "%pfwP", software_node_fwnode(&softnodes[1]));
	test(third_name, "%pfwP", software_node_fwnode(&softnodes[2]));

	software_node_unरेजिस्टर_nodes(softnodes);
पूर्ण

अटल व्योम __init fourcc_poपूर्णांकer(व्योम)
अणु
	काष्ठा अणु
		u32 code;
		अक्षर *str;
	पूर्ण स्थिर try[] = अणु
		अणु 0x3231564e, "NV12 little-endian (0x3231564e)", पूर्ण,
		अणु 0xb231564e, "NV12 big-endian (0xb231564e)", पूर्ण,
		अणु 0x10111213, ".... little-endian (0x10111213)", पूर्ण,
		अणु 0x20303159, "Y10  little-endian (0x20303159)", पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(try); i++)
		test(try[i].str, "%p4cc", &try[i].code);
पूर्ण

अटल व्योम __init
errptr(व्योम)
अणु
	test("-1234", "%pe", ERR_PTR(-1234));

	/* Check that %pe with a non-ERR_PTR माला_लो treated as ordinary %p. */
	BUILD_BUG_ON(IS_ERR(PTR));
	test_hashed("%pe", PTR);

#अगर_घोषित CONFIG_SYMBOLIC_ERRNAME
	test("(-ENOTSOCK)", "(%pe)", ERR_PTR(-ENOTSOCK));
	test("(-EAGAIN)", "(%pe)", ERR_PTR(-EAGAIN));
	BUILD_BUG_ON(EAGAIN != EWOULDBLOCK);
	test("(-EAGAIN)", "(%pe)", ERR_PTR(-EWOULDBLOCK));
	test("[-EIO    ]", "[%-8pe]", ERR_PTR(-EIO));
	test("[    -EIO]", "[%8pe]", ERR_PTR(-EIO));
	test("-EPROBE_DEFER", "%pe", ERR_PTR(-EPROBE_DEFER));
#पूर्ण_अगर
पूर्ण

अटल व्योम __init
test_poपूर्णांकer(व्योम)
अणु
	plain();
	null_poपूर्णांकer();
	error_poपूर्णांकer();
	invalid_poपूर्णांकer();
	symbol_ptr();
	kernel_ptr();
	काष्ठा_resource();
	addr();
	escaped_str();
	hex_string();
	mac();
	ip();
	uuid();
	dentry();
	काष्ठा_va_क्रमmat();
	समय_and_date();
	काष्ठा_clk();
	biपंचांगap();
	netdev_features();
	flags();
	errptr();
	fwnode_poपूर्णांकer();
	fourcc_poपूर्णांकer();
पूर्ण

अटल व्योम __init selftest(व्योम)
अणु
	alloced_buffer = kदो_स्मृति(BUF_SIZE + 2*PAD_SIZE, GFP_KERNEL);
	अगर (!alloced_buffer)
		वापस;
	test_buffer = alloced_buffer + PAD_SIZE;

	test_basic();
	test_number();
	test_string();
	test_poपूर्णांकer();

	kमुक्त(alloced_buffer);
पूर्ण

KSTM_MODULE_LOADERS(test_म_लिखो);
MODULE_AUTHOR("Rasmus Villemoes <linux@rasmusvillemoes.dk>");
MODULE_LICENSE("GPL");
