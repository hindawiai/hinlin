<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test हालs क्रम biपंचांगap API.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>

#समावेश "../tools/testing/selftests/kselftest_module.h"

KSTM_MODULE_GLOBALS();

अटल अक्षर pbl_buffer[PAGE_SIZE] __initdata;

अटल स्थिर अचिन्हित दीर्घ exp1[] __initस्थिर = अणु
	BITMAP_FROM_U64(1),
	BITMAP_FROM_U64(2),
	BITMAP_FROM_U64(0x0000ffff),
	BITMAP_FROM_U64(0xffff0000),
	BITMAP_FROM_U64(0x55555555),
	BITMAP_FROM_U64(0xaaaaaaaa),
	BITMAP_FROM_U64(0x11111111),
	BITMAP_FROM_U64(0x22222222),
	BITMAP_FROM_U64(0xffffffff),
	BITMAP_FROM_U64(0xfffffffe),
	BITMAP_FROM_U64(0x3333333311111111ULL),
	BITMAP_FROM_U64(0xffffffff77777777ULL),
	BITMAP_FROM_U64(0),
	BITMAP_FROM_U64(0x00008000),
	BITMAP_FROM_U64(0x80000000),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ exp2[] __initस्थिर = अणु
	BITMAP_FROM_U64(0x3333333311111111ULL),
	BITMAP_FROM_U64(0xffffffff77777777ULL),
पूर्ण;

/* Fibonacci sequence */
अटल स्थिर अचिन्हित दीर्घ exp2_to_exp3_mask[] __initस्थिर = अणु
	BITMAP_FROM_U64(0x008000020020212eULL),
पूर्ण;
/* exp3_0_1 = (exp2[0] & ~exp2_to_exp3_mask) | (exp2[1] & exp2_to_exp3_mask) */
अटल स्थिर अचिन्हित दीर्घ exp3_0_1[] __initस्थिर = अणु
	BITMAP_FROM_U64(0x33b3333311313137ULL),
पूर्ण;
/* exp3_1_0 = (exp2[1] & ~exp2_to_exp3_mask) | (exp2[0] & exp2_to_exp3_mask) */
अटल स्थिर अचिन्हित दीर्घ exp3_1_0[] __initस्थिर = अणु
	BITMAP_FROM_U64(0xff7fffff77575751ULL),
पूर्ण;

अटल bool __init
__check_eq_uपूर्णांक(स्थिर अक्षर *srcfile, अचिन्हित पूर्णांक line,
		स्थिर अचिन्हित पूर्णांक exp_uपूर्णांक, अचिन्हित पूर्णांक x)
अणु
	अगर (exp_uपूर्णांक != x) अणु
		pr_err("[%s:%u] expected %u, got %u\n",
			srcfile, line, exp_uपूर्णांक, x);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण


अटल bool __init
__check_eq_biपंचांगap(स्थिर अक्षर *srcfile, अचिन्हित पूर्णांक line,
		  स्थिर अचिन्हित दीर्घ *exp_bmap, स्थिर अचिन्हित दीर्घ *bmap,
		  अचिन्हित पूर्णांक nbits)
अणु
	अगर (!biपंचांगap_equal(exp_bmap, bmap, nbits)) अणु
		pr_warn("[%s:%u] bitmaps contents differ: expected \"%*pbl\", got \"%*pbl\"\n",
			srcfile, line,
			nbits, exp_bmap, nbits, bmap);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool __init
__check_eq_pbl(स्थिर अक्षर *srcfile, अचिन्हित पूर्णांक line,
	       स्थिर अक्षर *expected_pbl,
	       स्थिर अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits)
अणु
	snम_लिखो(pbl_buffer, माप(pbl_buffer), "%*pbl", nbits, biपंचांगap);
	अगर (म_भेद(expected_pbl, pbl_buffer)) अणु
		pr_warn("[%s:%u] expected \"%s\", got \"%s\"\n",
			srcfile, line,
			expected_pbl, pbl_buffer);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool __init
__check_eq_u32_array(स्थिर अक्षर *srcfile, अचिन्हित पूर्णांक line,
		     स्थिर u32 *exp_arr, अचिन्हित पूर्णांक exp_len,
		     स्थिर u32 *arr, अचिन्हित पूर्णांक len) __used;
अटल bool __init
__check_eq_u32_array(स्थिर अक्षर *srcfile, अचिन्हित पूर्णांक line,
		     स्थिर u32 *exp_arr, अचिन्हित पूर्णांक exp_len,
		     स्थिर u32 *arr, अचिन्हित पूर्णांक len)
अणु
	अगर (exp_len != len) अणु
		pr_warn("[%s:%u] array length differ: expected %u, got %u\n",
			srcfile, line,
			exp_len, len);
		वापस false;
	पूर्ण

	अगर (स_भेद(exp_arr, arr, len*माप(*arr))) अणु
		pr_warn("[%s:%u] array contents differ\n", srcfile, line);
		prपूर्णांक_hex_dump(KERN_WARNING, "  exp:  ", DUMP_PREFIX_OFFSET,
			       32, 4, exp_arr, exp_len*माप(*exp_arr), false);
		prपूर्णांक_hex_dump(KERN_WARNING, "  got:  ", DUMP_PREFIX_OFFSET,
			       32, 4, arr, len*माप(*arr), false);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool __init __check_eq_clump8(स्थिर अक्षर *srcfile, अचिन्हित पूर्णांक line,
				    स्थिर अचिन्हित पूर्णांक offset,
				    स्थिर अचिन्हित पूर्णांक size,
				    स्थिर अचिन्हित अक्षर *स्थिर clump_exp,
				    स्थिर अचिन्हित दीर्घ *स्थिर clump)
अणु
	अचिन्हित दीर्घ exp;

	अगर (offset >= size) अणु
		pr_warn("[%s:%u] bit offset for clump out-of-bounds: expected less than %u, got %u\n",
			srcfile, line, size, offset);
		वापस false;
	पूर्ण

	exp = clump_exp[offset / 8];
	अगर (!exp) अणु
		pr_warn("[%s:%u] bit offset for zero clump: expected nonzero clump, got bit offset %u with clump value 0",
			srcfile, line, offset);
		वापस false;
	पूर्ण

	अगर (*clump != exp) अणु
		pr_warn("[%s:%u] expected clump value of 0x%lX, got clump value of 0x%lX",
			srcfile, line, exp, *clump);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

#घोषणा __expect_eq(suffix, ...)					\
	(अणु								\
		पूर्णांक result = 0;						\
		total_tests++;						\
		अगर (!__check_eq_ ## suffix(__खाता__, __LINE__,		\
					   ##__VA_ARGS__)) अणु		\
			failed_tests++;					\
			result = 1;					\
		पूर्ण							\
		result;							\
	पूर्ण)

#घोषणा expect_eq_uपूर्णांक(...)		__expect_eq(uपूर्णांक, ##__VA_ARGS__)
#घोषणा expect_eq_biपंचांगap(...)		__expect_eq(biपंचांगap, ##__VA_ARGS__)
#घोषणा expect_eq_pbl(...)		__expect_eq(pbl, ##__VA_ARGS__)
#घोषणा expect_eq_u32_array(...)	__expect_eq(u32_array, ##__VA_ARGS__)
#घोषणा expect_eq_clump8(...)		__expect_eq(clump8, ##__VA_ARGS__)

अटल व्योम __init test_zero_clear(व्योम)
अणु
	DECLARE_BITMAP(bmap, 1024);

	/* Known way to set all bits */
	स_रखो(bmap, 0xff, 128);

	expect_eq_pbl("0-22", bmap, 23);
	expect_eq_pbl("0-1023", bmap, 1024);

	/* single-word biपंचांगaps */
	biपंचांगap_clear(bmap, 0, 9);
	expect_eq_pbl("9-1023", bmap, 1024);

	biपंचांगap_zero(bmap, 35);
	expect_eq_pbl("64-1023", bmap, 1024);

	/* cross boundaries operations */
	biपंचांगap_clear(bmap, 79, 19);
	expect_eq_pbl("64-78,98-1023", bmap, 1024);

	biपंचांगap_zero(bmap, 115);
	expect_eq_pbl("128-1023", bmap, 1024);

	/* Zeroing entire area */
	biपंचांगap_zero(bmap, 1024);
	expect_eq_pbl("", bmap, 1024);
पूर्ण

अटल व्योम __init test_fill_set(व्योम)
अणु
	DECLARE_BITMAP(bmap, 1024);

	/* Known way to clear all bits */
	स_रखो(bmap, 0x00, 128);

	expect_eq_pbl("", bmap, 23);
	expect_eq_pbl("", bmap, 1024);

	/* single-word biपंचांगaps */
	biपंचांगap_set(bmap, 0, 9);
	expect_eq_pbl("0-8", bmap, 1024);

	biपंचांगap_fill(bmap, 35);
	expect_eq_pbl("0-63", bmap, 1024);

	/* cross boundaries operations */
	biपंचांगap_set(bmap, 79, 19);
	expect_eq_pbl("0-63,79-97", bmap, 1024);

	biपंचांगap_fill(bmap, 115);
	expect_eq_pbl("0-127", bmap, 1024);

	/* Zeroing entire area */
	biपंचांगap_fill(bmap, 1024);
	expect_eq_pbl("0-1023", bmap, 1024);
पूर्ण

अटल व्योम __init test_copy(व्योम)
अणु
	DECLARE_BITMAP(bmap1, 1024);
	DECLARE_BITMAP(bmap2, 1024);

	biपंचांगap_zero(bmap1, 1024);
	biपंचांगap_zero(bmap2, 1024);

	/* single-word biपंचांगaps */
	biपंचांगap_set(bmap1, 0, 19);
	biपंचांगap_copy(bmap2, bmap1, 23);
	expect_eq_pbl("0-18", bmap2, 1024);

	biपंचांगap_set(bmap2, 0, 23);
	biपंचांगap_copy(bmap2, bmap1, 23);
	expect_eq_pbl("0-18", bmap2, 1024);

	/* multi-word biपंचांगaps */
	biपंचांगap_set(bmap1, 0, 109);
	biपंचांगap_copy(bmap2, bmap1, 1024);
	expect_eq_pbl("0-108", bmap2, 1024);

	biपंचांगap_fill(bmap2, 1024);
	biपंचांगap_copy(bmap2, bmap1, 1024);
	expect_eq_pbl("0-108", bmap2, 1024);

	/* the following tests assume a 32- or 64-bit arch (even 128b
	 * अगर we care)
	 */

	biपंचांगap_fill(bmap2, 1024);
	biपंचांगap_copy(bmap2, bmap1, 109);  /* ... but 0-padded til word length */
	expect_eq_pbl("0-108,128-1023", bmap2, 1024);

	biपंचांगap_fill(bmap2, 1024);
	biपंचांगap_copy(bmap2, bmap1, 97);  /* ... but aligned on word length */
	expect_eq_pbl("0-108,128-1023", bmap2, 1024);
पूर्ण

#घोषणा EXP2_IN_BITS	(माप(exp2) * 8)

अटल व्योम __init test_replace(व्योम)
अणु
	अचिन्हित पूर्णांक nbits = 64;
	अचिन्हित पूर्णांक nदीर्घs = DIV_ROUND_UP(nbits, BITS_PER_LONG);
	DECLARE_BITMAP(bmap, 1024);

	BUILD_BUG_ON(EXP2_IN_BITS < nbits * 2);

	biपंचांगap_zero(bmap, 1024);
	biपंचांगap_replace(bmap, &exp2[0 * nदीर्घs], &exp2[1 * nदीर्घs], exp2_to_exp3_mask, nbits);
	expect_eq_biपंचांगap(bmap, exp3_0_1, nbits);

	biपंचांगap_zero(bmap, 1024);
	biपंचांगap_replace(bmap, &exp2[1 * nदीर्घs], &exp2[0 * nदीर्घs], exp2_to_exp3_mask, nbits);
	expect_eq_biपंचांगap(bmap, exp3_1_0, nbits);

	biपंचांगap_fill(bmap, 1024);
	biपंचांगap_replace(bmap, &exp2[0 * nदीर्घs], &exp2[1 * nदीर्घs], exp2_to_exp3_mask, nbits);
	expect_eq_biपंचांगap(bmap, exp3_0_1, nbits);

	biपंचांगap_fill(bmap, 1024);
	biपंचांगap_replace(bmap, &exp2[1 * nदीर्घs], &exp2[0 * nदीर्घs], exp2_to_exp3_mask, nbits);
	expect_eq_biपंचांगap(bmap, exp3_1_0, nbits);
पूर्ण

#घोषणा PARSE_TIME	0x1
#घोषणा NO_LEN		0x2

काष्ठा test_biपंचांगap_parselistअणु
	स्थिर पूर्णांक त्रुटि_सं;
	स्थिर अक्षर *in;
	स्थिर अचिन्हित दीर्घ *expected;
	स्थिर पूर्णांक nbits;
	स्थिर पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा test_biपंचांगap_parselist parselist_tests[] __initस्थिर = अणु
#घोषणा step (माप(u64) / माप(अचिन्हित दीर्घ))

	अणु0, "0",			&exp1[0], 8, 0पूर्ण,
	अणु0, "1",			&exp1[1 * step], 8, 0पूर्ण,
	अणु0, "0-15",			&exp1[2 * step], 32, 0पूर्ण,
	अणु0, "16-31",			&exp1[3 * step], 32, 0पूर्ण,
	अणु0, "0-31:1/2",			&exp1[4 * step], 32, 0पूर्ण,
	अणु0, "1-31:1/2",			&exp1[5 * step], 32, 0पूर्ण,
	अणु0, "0-31:1/4",			&exp1[6 * step], 32, 0पूर्ण,
	अणु0, "1-31:1/4",			&exp1[7 * step], 32, 0पूर्ण,
	अणु0, "0-31:4/4",			&exp1[8 * step], 32, 0पूर्ण,
	अणु0, "1-31:4/4",			&exp1[9 * step], 32, 0पूर्ण,
	अणु0, "0-31:1/4,32-63:2/4",	&exp1[10 * step], 64, 0पूर्ण,
	अणु0, "0-31:3/4,32-63:4/4",	&exp1[11 * step], 64, 0पूर्ण,
	अणु0, "  ,,  0-31:3/4  ,, 32-63:4/4  ,,  ",	&exp1[11 * step], 64, 0पूर्ण,

	अणु0, "0-31:1/4,32-63:2/4,64-95:3/4,96-127:4/4",	exp2, 128, 0पूर्ण,

	अणु0, "0-2047:128/256", शून्य, 2048, PARSE_TIMEपूर्ण,

	अणु0, "",				&exp1[12 * step], 8, 0पूर्ण,
	अणु0, "\n",			&exp1[12 * step], 8, 0पूर्ण,
	अणु0, ",,  ,,  , ,  ,",		&exp1[12 * step], 8, 0पूर्ण,
	अणु0, " ,  ,,  , ,   ",		&exp1[12 * step], 8, 0पूर्ण,
	अणु0, " ,  ,,  , ,   \n",		&exp1[12 * step], 8, 0पूर्ण,

	अणु0, "0-0",			&exp1[0], 32, 0पूर्ण,
	अणु0, "1-1",			&exp1[1 * step], 32, 0पूर्ण,
	अणु0, "15-15",			&exp1[13 * step], 32, 0पूर्ण,
	अणु0, "31-31",			&exp1[14 * step], 32, 0पूर्ण,

	अणु0, "0-0:0/1",			&exp1[12 * step], 32, 0पूर्ण,
	अणु0, "0-0:1/1",			&exp1[0], 32, 0पूर्ण,
	अणु0, "0-0:1/31",			&exp1[0], 32, 0पूर्ण,
	अणु0, "0-0:31/31",		&exp1[0], 32, 0पूर्ण,
	अणु0, "1-1:1/1",			&exp1[1 * step], 32, 0पूर्ण,
	अणु0, "0-15:16/31",		&exp1[2 * step], 32, 0पूर्ण,
	अणु0, "15-15:1/2",		&exp1[13 * step], 32, 0पूर्ण,
	अणु0, "15-15:31/31",		&exp1[13 * step], 32, 0पूर्ण,
	अणु0, "15-31:1/31",		&exp1[13 * step], 32, 0पूर्ण,
	अणु0, "16-31:16/31",		&exp1[3 * step], 32, 0पूर्ण,
	अणु0, "31-31:31/31",		&exp1[14 * step], 32, 0पूर्ण,

	अणु0, "N-N",			&exp1[14 * step], 32, 0पूर्ण,
	अणु0, "0-0:1/N",			&exp1[0], 32, 0पूर्ण,
	अणु0, "0-0:N/N",			&exp1[0], 32, 0पूर्ण,
	अणु0, "0-15:16/N",		&exp1[2 * step], 32, 0पूर्ण,
	अणु0, "15-15:N/N",		&exp1[13 * step], 32, 0पूर्ण,
	अणु0, "15-N:1/N",			&exp1[13 * step], 32, 0पूर्ण,
	अणु0, "16-N:16/N",		&exp1[3 * step], 32, 0पूर्ण,
	अणु0, "N-N:N/N",			&exp1[14 * step], 32, 0पूर्ण,

	अणु0, "0-N:1/3,1-N:1/3,2-N:1/3",		&exp1[8 * step], 32, 0पूर्ण,
	अणु0, "0-31:1/3,1-31:1/3,2-31:1/3",	&exp1[8 * step], 32, 0पूर्ण,
	अणु0, "1-10:8/12,8-31:24/29,0-31:0/3",	&exp1[9 * step], 32, 0पूर्ण,

	अणु-EINVAL, "-1",	शून्य, 8, 0पूर्ण,
	अणु-EINVAL, "-0",	शून्य, 8, 0पूर्ण,
	अणु-EINVAL, "10-1", शून्य, 8, 0पूर्ण,
	अणु-दुस्फल, "8-8", शून्य, 8, 0पूर्ण,
	अणु-दुस्फल, "0-31", शून्य, 8, 0पूर्ण,
	अणु-EINVAL, "0-31:", शून्य, 32, 0पूर्ण,
	अणु-EINVAL, "0-31:0", शून्य, 32, 0पूर्ण,
	अणु-EINVAL, "0-31:0/", शून्य, 32, 0पूर्ण,
	अणु-EINVAL, "0-31:0/0", शून्य, 32, 0पूर्ण,
	अणु-EINVAL, "0-31:1/0", शून्य, 32, 0पूर्ण,
	अणु-EINVAL, "0-31:10/1", शून्य, 32, 0पूर्ण,
	अणु-EOVERFLOW, "0-98765432123456789:10/1", शून्य, 8, 0पूर्ण,

	अणु-EINVAL, "a-31", शून्य, 8, 0पूर्ण,
	अणु-EINVAL, "0-a1", शून्य, 8, 0पूर्ण,
	अणु-EINVAL, "a-31:10/1", शून्य, 8, 0पूर्ण,
	अणु-EINVAL, "0-31:a/1", शून्य, 8, 0पूर्ण,
	अणु-EINVAL, "0-\n", शून्य, 8, 0पूर्ण,

पूर्ण;

अटल व्योम __init test_biपंचांगap_parselist(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक err;
	kसमय_प्रकार समय;
	DECLARE_BITMAP(bmap, 2048);

	क्रम (i = 0; i < ARRAY_SIZE(parselist_tests); i++) अणु
#घोषणा ptest parselist_tests[i]

		समय = kसमय_get();
		err = biपंचांगap_parselist(ptest.in, bmap, ptest.nbits);
		समय = kसमय_get() - समय;

		अगर (err != ptest.त्रुटि_सं) अणु
			pr_err("parselist: %d: input is %s, errno is %d, expected %d\n",
					i, ptest.in, err, ptest.त्रुटि_सं);
			जारी;
		पूर्ण

		अगर (!err && ptest.expected
			 && !__biपंचांगap_equal(bmap, ptest.expected, ptest.nbits)) अणु
			pr_err("parselist: %d: input is %s, result is 0x%lx, expected 0x%lx\n",
					i, ptest.in, bmap[0],
					*ptest.expected);
			जारी;
		पूर्ण

		अगर (ptest.flags & PARSE_TIME)
			pr_err("parselist: %d: input is '%s' OK, Time: %llu\n",
					i, ptest.in, समय);

#अघोषित ptest
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित दीर्घ parse_test[] __initस्थिर = अणु
	BITMAP_FROM_U64(0),
	BITMAP_FROM_U64(1),
	BITMAP_FROM_U64(0xdeadbeef),
	BITMAP_FROM_U64(0x100000000ULL),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ parse_test2[] __initस्थिर = अणु
	BITMAP_FROM_U64(0x100000000ULL), BITMAP_FROM_U64(0xdeadbeef),
	BITMAP_FROM_U64(0x100000000ULL), BITMAP_FROM_U64(0xbaadf00ddeadbeef),
	BITMAP_FROM_U64(0x100000000ULL), BITMAP_FROM_U64(0x0badf00ddeadbeef),
पूर्ण;

अटल स्थिर काष्ठा test_biपंचांगap_parselist parse_tests[] __initस्थिर = अणु
	अणु0, "",				&parse_test[0 * step], 32, 0पूर्ण,
	अणु0, " ",			&parse_test[0 * step], 32, 0पूर्ण,
	अणु0, "0",			&parse_test[0 * step], 32, 0पूर्ण,
	अणु0, "0\n",			&parse_test[0 * step], 32, 0पूर्ण,
	अणु0, "1",			&parse_test[1 * step], 32, 0पूर्ण,
	अणु0, "deadbeef",			&parse_test[2 * step], 32, 0पूर्ण,
	अणु0, "1,0",			&parse_test[3 * step], 33, 0पूर्ण,
	अणु0, "deadbeef,\n,0,1",		&parse_test[2 * step], 96, 0पूर्ण,

	अणु0, "deadbeef,1,0",		&parse_test2[0 * 2 * step], 96, 0पूर्ण,
	अणु0, "baadf00d,deadbeef,1,0",	&parse_test2[1 * 2 * step], 128, 0पूर्ण,
	अणु0, "badf00d,deadbeef,1,0",	&parse_test2[2 * 2 * step], 124, 0पूर्ण,
	अणु0, "badf00d,deadbeef,1,0",	&parse_test2[2 * 2 * step], 124, NO_LENपूर्ण,
	अणु0, "  badf00d,deadbeef,1,0  ",	&parse_test2[2 * 2 * step], 124, 0पूर्ण,
	अणु0, " , badf00d,deadbeef,1,0 , ",	&parse_test2[2 * 2 * step], 124, 0पूर्ण,
	अणु0, " , badf00d, ,, ,,deadbeef,1,0 , ",	&parse_test2[2 * 2 * step], 124, 0पूर्ण,

	अणु-EINVAL,    "goodfood,deadbeef,1,0",	शून्य, 128, 0पूर्ण,
	अणु-EOVERFLOW, "3,0",			शून्य, 33, 0पूर्ण,
	अणु-EOVERFLOW, "123badf00d,deadbeef,1,0",	शून्य, 128, 0पूर्ण,
	अणु-EOVERFLOW, "badf00d,deadbeef,1,0",	शून्य, 90, 0पूर्ण,
	अणु-EOVERFLOW, "fbadf00d,deadbeef,1,0",	शून्य, 95, 0पूर्ण,
	अणु-EOVERFLOW, "badf00d,deadbeef,1,0",	शून्य, 100, 0पूर्ण,
#अघोषित step
पूर्ण;

अटल व्योम __init test_biपंचांगap_parse(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक err;
	kसमय_प्रकार समय;
	DECLARE_BITMAP(bmap, 2048);

	क्रम (i = 0; i < ARRAY_SIZE(parse_tests); i++) अणु
		काष्ठा test_biपंचांगap_parselist test = parse_tests[i];
		माप_प्रकार len = test.flags & NO_LEN ? अच_पूर्णांक_उच्च : म_माप(test.in);

		समय = kसमय_get();
		err = biपंचांगap_parse(test.in, len, bmap, test.nbits);
		समय = kसमय_get() - समय;

		अगर (err != test.त्रुटि_सं) अणु
			pr_err("parse: %d: input is %s, errno is %d, expected %d\n",
					i, test.in, err, test.त्रुटि_सं);
			जारी;
		पूर्ण

		अगर (!err && test.expected
			 && !__biपंचांगap_equal(bmap, test.expected, test.nbits)) अणु
			pr_err("parse: %d: input is %s, result is 0x%lx, expected 0x%lx\n",
					i, test.in, bmap[0],
					*test.expected);
			जारी;
		पूर्ण

		अगर (test.flags & PARSE_TIME)
			pr_err("parse: %d: input is '%s' OK, Time: %llu\n",
					i, test.in, समय);
	पूर्ण
पूर्ण

#घोषणा EXP1_IN_BITS	(माप(exp1) * 8)

अटल व्योम __init test_biपंचांगap_arr32(व्योम)
अणु
	अचिन्हित पूर्णांक nbits, next_bit;
	u32 arr[EXP1_IN_BITS / 32];
	DECLARE_BITMAP(bmap2, EXP1_IN_BITS);

	स_रखो(arr, 0xa5, माप(arr));

	क्रम (nbits = 0; nbits < EXP1_IN_BITS; ++nbits) अणु
		biपंचांगap_to_arr32(arr, exp1, nbits);
		biपंचांगap_from_arr32(bmap2, arr, nbits);
		expect_eq_biपंचांगap(bmap2, exp1, nbits);

		next_bit = find_next_bit(bmap2,
				round_up(nbits, BITS_PER_LONG), nbits);
		अगर (next_bit < round_up(nbits, BITS_PER_LONG))
			pr_err("bitmap_copy_arr32(nbits == %d:"
				" tail is not safely cleared: %d\n",
				nbits, next_bit);

		अगर (nbits < EXP1_IN_BITS - 32)
			expect_eq_uपूर्णांक(arr[DIV_ROUND_UP(nbits, 32)],
								0xa5a5a5a5);
	पूर्ण
पूर्ण

अटल व्योम noअंतरभूत __init test_mem_optimisations(व्योम)
अणु
	DECLARE_BITMAP(bmap1, 1024);
	DECLARE_BITMAP(bmap2, 1024);
	अचिन्हित पूर्णांक start, nbits;

	क्रम (start = 0; start < 1024; start += 8) अणु
		क्रम (nbits = 0; nbits < 1024 - start; nbits += 8) अणु
			स_रखो(bmap1, 0x5a, माप(bmap1));
			स_रखो(bmap2, 0x5a, माप(bmap2));

			biपंचांगap_set(bmap1, start, nbits);
			__biपंचांगap_set(bmap2, start, nbits);
			अगर (!biपंचांगap_equal(bmap1, bmap2, 1024)) अणु
				prपूर्णांकk("set not equal %d %d\n", start, nbits);
				failed_tests++;
			पूर्ण
			अगर (!__biपंचांगap_equal(bmap1, bmap2, 1024)) अणु
				prपूर्णांकk("set not __equal %d %d\n", start, nbits);
				failed_tests++;
			पूर्ण

			biपंचांगap_clear(bmap1, start, nbits);
			__biपंचांगap_clear(bmap2, start, nbits);
			अगर (!biपंचांगap_equal(bmap1, bmap2, 1024)) अणु
				prपूर्णांकk("clear not equal %d %d\n", start, nbits);
				failed_tests++;
			पूर्ण
			अगर (!__biपंचांगap_equal(bmap1, bmap2, 1024)) अणु
				prपूर्णांकk("clear not __equal %d %d\n", start,
									nbits);
				failed_tests++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित अक्षर clump_exp[] __initस्थिर = अणु
	0x01,	/* 1 bit set */
	0x02,	/* non-edge 1 bit set */
	0x00,	/* zero bits set */
	0x38,	/* 3 bits set across 4-bit boundary */
	0x38,	/* Repeated clump */
	0x0F,	/* 4 bits set */
	0xFF,	/* all bits set */
	0x05,	/* non-adjacent 2 bits set */
पूर्ण;

अटल व्योम __init test_क्रम_each_set_clump8(व्योम)
अणु
#घोषणा CLUMP_EXP_NUMBITS 64
	DECLARE_BITMAP(bits, CLUMP_EXP_NUMBITS);
	अचिन्हित पूर्णांक start;
	अचिन्हित दीर्घ clump;

	/* set biपंचांगap to test हाल */
	biपंचांगap_zero(bits, CLUMP_EXP_NUMBITS);
	biपंचांगap_set(bits, 0, 1);		/* 0x01 */
	biपंचांगap_set(bits, 9, 1);		/* 0x02 */
	biपंचांगap_set(bits, 27, 3);	/* 0x28 */
	biपंचांगap_set(bits, 35, 3);	/* 0x28 */
	biपंचांगap_set(bits, 40, 4);	/* 0x0F */
	biपंचांगap_set(bits, 48, 8);	/* 0xFF */
	biपंचांगap_set(bits, 56, 1);	/* 0x05 - part 1 */
	biपंचांगap_set(bits, 58, 1);	/* 0x05 - part 2 */

	क्रम_each_set_clump8(start, clump, bits, CLUMP_EXP_NUMBITS)
		expect_eq_clump8(start, CLUMP_EXP_NUMBITS, clump_exp, &clump);
पूर्ण

काष्ठा test_biपंचांगap_cut अणु
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक cut;
	अचिन्हित पूर्णांक nbits;
	अचिन्हित दीर्घ in[4];
	अचिन्हित दीर्घ expected[4];
पूर्ण;

अटल काष्ठा test_biपंचांगap_cut test_cut[] = अणु
	अणु  0,  0,  8, अणु 0x0000000aUL, पूर्ण, अणु 0x0000000aUL, पूर्ण, पूर्ण,
	अणु  0,  0, 32, अणु 0xdadadeadUL, पूर्ण, अणु 0xdadadeadUL, पूर्ण, पूर्ण,
	अणु  0,  3,  8, अणु 0x000000aaUL, पूर्ण, अणु 0x00000015UL, पूर्ण, पूर्ण,
	अणु  3,  3,  8, अणु 0x000000aaUL, पूर्ण, अणु 0x00000012UL, पूर्ण, पूर्ण,
	अणु  0,  1, 32, अणु 0xa5a5a5a5UL, पूर्ण, अणु 0x52d2d2d2UL, पूर्ण, पूर्ण,
	अणु  0,  8, 32, अणु 0xdeadc0deUL, पूर्ण, अणु 0x00deadc0UL, पूर्ण, पूर्ण,
	अणु  1,  1, 32, अणु 0x5a5a5a5aUL, पूर्ण, अणु 0x2d2d2d2cUL, पूर्ण, पूर्ण,
	अणु  0, 15, 32, अणु 0xa5a5a5a5UL, पूर्ण, अणु 0x00014b4bUL, पूर्ण, पूर्ण,
	अणु  0, 16, 32, अणु 0xa5a5a5a5UL, पूर्ण, अणु 0x0000a5a5UL, पूर्ण, पूर्ण,
	अणु 15, 15, 32, अणु 0xa5a5a5a5UL, पूर्ण, अणु 0x000125a5UL, पूर्ण, पूर्ण,
	अणु 15, 16, 32, अणु 0xa5a5a5a5UL, पूर्ण, अणु 0x0000a5a5UL, पूर्ण, पूर्ण,
	अणु 16, 15, 32, अणु 0xa5a5a5a5UL, पूर्ण, अणु 0x0001a5a5UL, पूर्ण, पूर्ण,

	अणु BITS_PER_LONG, BITS_PER_LONG, BITS_PER_LONG,
		अणु 0xa5a5a5a5UL, 0xa5a5a5a5UL, पूर्ण,
		अणु 0xa5a5a5a5UL, 0xa5a5a5a5UL, पूर्ण,
	पूर्ण,
	अणु 1, BITS_PER_LONG - 1, BITS_PER_LONG,
		अणु 0xa5a5a5a5UL, 0xa5a5a5a5UL, पूर्ण,
		अणु 0x00000001UL, 0x00000001UL, पूर्ण,
	पूर्ण,

	अणु 0, BITS_PER_LONG * 2, BITS_PER_LONG * 2 + 1,
		अणु 0xa5a5a5a5UL, 0x00000001UL, 0x00000001UL, 0x00000001UL पूर्ण,
		अणु 0x00000001UL, पूर्ण,
	पूर्ण,
	अणु 16, BITS_PER_LONG * 2 + 1, BITS_PER_LONG * 2 + 1 + 16,
		अणु 0x0000ffffUL, 0x5a5a5a5aUL, 0x5a5a5a5aUL, 0x5a5a5a5aUL पूर्ण,
		अणु 0x2d2dffffUL, पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init test_biपंचांगap_cut(व्योम)
अणु
	अचिन्हित दीर्घ b[5], *in = &b[1], *out = &b[0];	/* Partial overlap */
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(test_cut); i++) अणु
		काष्ठा test_biपंचांगap_cut *t = &test_cut[i];

		स_नकल(in, t->in, माप(t->in));

		biपंचांगap_cut(out, in, t->first, t->cut, t->nbits);

		expect_eq_biपंचांगap(t->expected, out, t->nbits);
	पूर्ण
पूर्ण

अटल व्योम __init selftest(व्योम)
अणु
	test_zero_clear();
	test_fill_set();
	test_copy();
	test_replace();
	test_biपंचांगap_arr32();
	test_biपंचांगap_parse();
	test_biपंचांगap_parselist();
	test_mem_optimisations();
	test_क्रम_each_set_clump8();
	test_biपंचांगap_cut();
पूर्ण

KSTM_MODULE_LOADERS(test_biपंचांगap);
MODULE_AUTHOR("david decotigny <david.decotigny@googlers.com>");
MODULE_LICENSE("GPL");
