<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2021  Maciej W. Rozycki
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/समय64.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/भाग64.h>

#घोषणा TEST_DIV64_N_ITER 1024

अटल स्थिर u64 test_भाग64_भागidends[] = अणु
	0x00000000ab275080,
	0x0000000fe73c1959,
	0x000000e54c0a74b1,
	0x00000d4398ff1ef9,
	0x0000a18c2ee1c097,
	0x00079fb80b072e4a,
	0x0072db27380dd689,
	0x0842f488162e2284,
	0xf66745411d8ab063,
पूर्ण;
#घोषणा SIZE_DIV64_DIVIDENDS ARRAY_SIZE(test_भाग64_भागidends)

#घोषणा TEST_DIV64_DIVISOR_0 0x00000009
#घोषणा TEST_DIV64_DIVISOR_1 0x0000007c
#घोषणा TEST_DIV64_DIVISOR_2 0x00000204
#घोषणा TEST_DIV64_DIVISOR_3 0x0000cb5b
#घोषणा TEST_DIV64_DIVISOR_4 0x00010000
#घोषणा TEST_DIV64_DIVISOR_5 0x0008a880
#घोषणा TEST_DIV64_DIVISOR_6 0x003fd3ae
#घोषणा TEST_DIV64_DIVISOR_7 0x0b658fac
#घोषणा TEST_DIV64_DIVISOR_8 0xdc08b349

अटल स्थिर u32 test_भाग64_भागisors[] = अणु
	TEST_DIV64_DIVISOR_0,
	TEST_DIV64_DIVISOR_1,
	TEST_DIV64_DIVISOR_2,
	TEST_DIV64_DIVISOR_3,
	TEST_DIV64_DIVISOR_4,
	TEST_DIV64_DIVISOR_5,
	TEST_DIV64_DIVISOR_6,
	TEST_DIV64_DIVISOR_7,
	TEST_DIV64_DIVISOR_8,
पूर्ण;
#घोषणा SIZE_DIV64_DIVISORS ARRAY_SIZE(test_भाग64_भागisors)

अटल स्थिर काष्ठा अणु
	u64 quotient;
	u32 reमुख्यder;
पूर्ण test_भाग64_results[SIZE_DIV64_DIVISORS][SIZE_DIV64_DIVIDENDS] = अणु
	अणु
		अणु 0x0000000013045e47, 0x00000001 पूर्ण,
		अणु 0x000000000161596c, 0x00000030 पूर्ण,
		अणु 0x000000000054e9d4, 0x00000130 पूर्ण,
		अणु 0x000000000000d776, 0x0000278e पूर्ण,
		अणु 0x000000000000ab27, 0x00005080 पूर्ण,
		अणु 0x00000000000013c4, 0x0004ce80 पूर्ण,
		अणु 0x00000000000002ae, 0x001e143c पूर्ण,
		अणु 0x000000000000000f, 0x0033e56c पूर्ण,
		अणु 0x0000000000000000, 0xab275080 पूर्ण,
	पूर्ण, अणु
		अणु 0x00000001c45c02d1, 0x00000000 पूर्ण,
		अणु 0x0000000020d5213c, 0x00000049 पूर्ण,
		अणु 0x0000000007e3d65f, 0x000001dd पूर्ण,
		अणु 0x0000000000140531, 0x000065ee पूर्ण,
		अणु 0x00000000000fe73c, 0x00001959 पूर्ण,
		अणु 0x000000000001d637, 0x0004e5d9 पूर्ण,
		अणु 0x0000000000003fc9, 0x000713bb पूर्ण,
		अणु 0x0000000000000165, 0x029abe7d पूर्ण,
		अणु 0x0000000000000012, 0x6e9f7e37 पूर्ण,
	पूर्ण, अणु
		अणु 0x000000197a3a0cf7, 0x00000002 पूर्ण,
		अणु 0x00000001d9632e5c, 0x00000021 पूर्ण,
		अणु 0x0000000071c28039, 0x000001cd पूर्ण,
		अणु 0x000000000120a844, 0x0000b885 पूर्ण,
		अणु 0x0000000000e54c0a, 0x000074b1 पूर्ण,
		अणु 0x00000000001a7bb3, 0x00072331 पूर्ण,
		अणु 0x00000000000397ad, 0x0002c61b पूर्ण,
		अणु 0x000000000000141e, 0x06ea2e89 पूर्ण,
		अणु 0x000000000000010a, 0xab002ad7 पूर्ण,
	पूर्ण, अणु
		अणु 0x0000017949e37538, 0x00000001 पूर्ण,
		अणु 0x0000001b62441f37, 0x00000055 पूर्ण,
		अणु 0x0000000694a3391d, 0x00000085 पूर्ण,
		अणु 0x0000000010b2a5d2, 0x0000a753 पूर्ण,
		अणु 0x000000000d4398ff, 0x00001ef9 पूर्ण,
		अणु 0x0000000001882ec6, 0x0005cbf9 पूर्ण,
		अणु 0x000000000035333b, 0x0017abdf पूर्ण,
		अणु 0x00000000000129f1, 0x0ab4520d पूर्ण,
		अणु 0x0000000000000f6e, 0x8ac0ce9b पूर्ण,
	पूर्ण, अणु
		अणु 0x000011f321a74e49, 0x00000006 पूर्ण,
		अणु 0x0000014d8481d211, 0x0000005b पूर्ण,
		अणु 0x0000005025cbd92d, 0x000001e3 पूर्ण,
		अणु 0x00000000cb5e71e3, 0x000043e6 पूर्ण,
		अणु 0x00000000a18c2ee1, 0x0000c097 पूर्ण,
		अणु 0x0000000012a88828, 0x00036c97 पूर्ण,
		अणु 0x000000000287f16f, 0x002c2a25 पूर्ण,
		अणु 0x00000000000e2cc7, 0x02d581e3 पूर्ण,
		अणु 0x000000000000bbf4, 0x1ba08c03 पूर्ण,
	पूर्ण, अणु
		अणु 0x0000d8db8f72935d, 0x00000005 पूर्ण,
		अणु 0x00000fbd5aed7a2e, 0x00000002 पूर्ण,
		अणु 0x000003c84b6ea64a, 0x00000122 पूर्ण,
		अणु 0x0000000998fa8829, 0x000044b7 पूर्ण,
		अणु 0x000000079fb80b07, 0x00002e4a पूर्ण,
		अणु 0x00000000e16b20fa, 0x0002a14a पूर्ण,
		अणु 0x000000001e940d22, 0x00353b2e पूर्ण,
		अणु 0x0000000000ab40ac, 0x06fba6ba पूर्ण,
		अणु 0x000000000008debd, 0x72d98365 पूर्ण,
	पूर्ण, अणु
		अणु 0x000cc3045b8fc281, 0x00000000 पूर्ण,
		अणु 0x0000ed1f48b5c9fc, 0x00000079 पूर्ण,
		अणु 0x000038fb9c63406a, 0x000000e1 पूर्ण,
		अणु 0x000000909705b825, 0x00000a62 पूर्ण,
		अणु 0x00000072db27380d, 0x0000d689 पूर्ण,
		अणु 0x0000000d43fce827, 0x00082b09 पूर्ण,
		अणु 0x00000001ccaba11a, 0x0037e8dd पूर्ण,
		अणु 0x000000000a13f729, 0x0566dffd पूर्ण,
		अणु 0x000000000085a14b, 0x23d36726 पूर्ण,
	पूर्ण, अणु
		अणु 0x00eafeb9c993592b, 0x00000001 पूर्ण,
		अणु 0x00110e5befa9a991, 0x00000048 पूर्ण,
		अणु 0x00041947b4a1d36a, 0x000000dc पूर्ण,
		अणु 0x00000a6679327311, 0x0000c079 पूर्ण,
		अणु 0x00000842f488162e, 0x00002284 पूर्ण,
		अणु 0x000000f4459740fc, 0x00084484 पूर्ण,
		अणु 0x0000002122c47bf9, 0x002ca446 पूर्ण,
		अणु 0x00000000b9936290, 0x004979c4 पूर्ण,
		अणु 0x00000000099ca89d, 0x9db446bf पूर्ण,
	पूर्ण, अणु
		अणु 0x1b60cece589da1d2, 0x00000001 पूर्ण,
		अणु 0x01fcb42be1453f5b, 0x0000004f पूर्ण,
		अणु 0x007a3f2457df0749, 0x0000013f पूर्ण,
		अणु 0x0001363130e3ec7b, 0x000017aa पूर्ण,
		अणु 0x0000f66745411d8a, 0x0000b063 पूर्ण,
		अणु 0x00001c757dfab350, 0x00048863 पूर्ण,
		अणु 0x000003dc4979c652, 0x00224ea7 पूर्ण,
		अणु 0x000000159edc3144, 0x06409ab3 पूर्ण,
		अणु 0x000000011eadfee3, 0xa99c48a8 पूर्ण,
	पूर्ण,
पूर्ण;

अटल अंतरभूत bool test_भाग64_verअगरy(u64 quotient, u32 reमुख्यder, पूर्णांक i, पूर्णांक j)
अणु
	वापस (quotient == test_भाग64_results[i][j].quotient &&
		reमुख्यder == test_भाग64_results[i][j].reमुख्यder);
पूर्ण

/*
 * This needs to be a macro, because we करोn't want to rely on the compiler
 * to करो स्थिरant propagation, and `करो_भाग' may take a dअगरferent path क्रम
 * स्थिरants, so we करो want to verअगरy that as well.
 */
#घोषणा test_भाग64_one(भागidend, भागisor, i, j) (अणु			\
	bool result = true;						\
	u64 quotient;							\
	u32 reमुख्यder;							\
									\
	quotient = भागidend;						\
	reमुख्यder = करो_भाग(quotient, भागisor);				\
	अगर (!test_भाग64_verअगरy(quotient, reमुख्यder, i, j)) अणु		\
		pr_err("ERROR: %016llx / %08x => %016llx,%08x\n",	\
		       भागidend, भागisor, quotient, reमुख्यder);		\
		pr_err("ERROR: expected value              => %016llx,%08x\n",\
		       test_भाग64_results[i][j].quotient,		\
		       test_भाग64_results[i][j].reमुख्यder);		\
		result = false;						\
	पूर्ण								\
	result;								\
पूर्ण)

/*
 * Run calculation क्रम the same भागisor value expressed as a स्थिरant
 * and as a variable, so as to verअगरy the implementation क्रम both हालs
 * should they be handled by dअगरferent code execution paths.
 */
अटल bool __init test_भाग64(व्योम)
अणु
	u64 भागidend;
	पूर्णांक i, j;

	क्रम (i = 0; i < SIZE_DIV64_DIVIDENDS; i++) अणु
		भागidend = test_भाग64_भागidends[i];
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_0, i, 0))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_1, i, 1))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_2, i, 2))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_3, i, 3))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_4, i, 4))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_5, i, 5))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_6, i, 6))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_7, i, 7))
			वापस false;
		अगर (!test_भाग64_one(भागidend, TEST_DIV64_DIVISOR_8, i, 8))
			वापस false;
		क्रम (j = 0; j < SIZE_DIV64_DIVISORS; j++) अणु
			अगर (!test_भाग64_one(भागidend, test_भाग64_भागisors[j],
					    i, j))
				वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक __init test_भाग64_init(व्योम)
अणु
	काष्ठा बारpec64 ts, ts0, ts1;
	पूर्णांक i;

	pr_info("Starting 64bit/32bit division and modulo test\n");
	kसमय_get_ts64(&ts0);

	क्रम (i = 0; i < TEST_DIV64_N_ITER; i++)
		अगर (!test_भाग64())
			अवरोध;

	kसमय_get_ts64(&ts1);
	ts = बारpec64_sub(ts1, ts0);
	pr_info("Completed 64bit/32bit division and modulo test, "
		"%llu.%09lus elapsed\n", ts.tv_sec, ts.tv_nsec);

	वापस 0;
पूर्ण

अटल व्योम __निकास test_भाग64_निकास(व्योम)
अणु
पूर्ण

module_init(test_भाग64_init);
module_निकास(test_भाग64_निकास);

MODULE_AUTHOR("Maciej W. Rozycki <macro@orcam.me.uk>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("64bit/32bit division and modulo test module");
