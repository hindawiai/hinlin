<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Testsuite क्रम atomic64_t functions
 *
 * Copyright तऊ 2010  Luca Barbieri
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/atomic.h>
#समावेश <linux/module.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/cpufeature.h>	/* क्रम boot_cpu_has below */
#पूर्ण_अगर

#घोषणा TEST(bit, op, c_op, val)				\
करो अणु								\
	atomic##bit##_set(&v, v0);				\
	r = v0;							\
	atomic##bit##_##op(val, &v);				\
	r c_op val;						\
	WARN(atomic##bit##_पढ़ो(&v) != r, "%Lx != %Lx\n",	\
		(अचिन्हित दीर्घ दीर्घ)atomic##bit##_पढ़ो(&v),	\
		(अचिन्हित दीर्घ दीर्घ)r);				\
पूर्ण जबतक (0)

/*
 * Test क्रम a atomic operation family,
 * @test should be a macro accepting parameters (bit, op, ...)
 */

#घोषणा FAMILY_TEST(test, bit, op, args...)	\
करो अणु						\
	test(bit, op, ##args);		\
	test(bit, op##_acquire, ##args);	\
	test(bit, op##_release, ##args);	\
	test(bit, op##_relaxed, ##args);	\
पूर्ण जबतक (0)

#घोषणा TEST_RETURN(bit, op, c_op, val)				\
करो अणु								\
	atomic##bit##_set(&v, v0);				\
	r = v0;							\
	r c_op val;						\
	BUG_ON(atomic##bit##_##op(val, &v) != r);		\
	BUG_ON(atomic##bit##_पढ़ो(&v) != r);			\
पूर्ण जबतक (0)

#घोषणा TEST_FETCH(bit, op, c_op, val)				\
करो अणु								\
	atomic##bit##_set(&v, v0);				\
	r = v0;							\
	r c_op val;						\
	BUG_ON(atomic##bit##_##op(val, &v) != v0);		\
	BUG_ON(atomic##bit##_पढ़ो(&v) != r);			\
पूर्ण जबतक (0)

#घोषणा RETURN_FAMILY_TEST(bit, op, c_op, val)			\
करो अणु								\
	FAMILY_TEST(TEST_RETURN, bit, op, c_op, val);		\
पूर्ण जबतक (0)

#घोषणा FETCH_FAMILY_TEST(bit, op, c_op, val)			\
करो अणु								\
	FAMILY_TEST(TEST_FETCH, bit, op, c_op, val);		\
पूर्ण जबतक (0)

#घोषणा TEST_ARGS(bit, op, init, ret, expect, args...)		\
करो अणु								\
	atomic##bit##_set(&v, init);				\
	BUG_ON(atomic##bit##_##op(&v, ##args) != ret);		\
	BUG_ON(atomic##bit##_पढ़ो(&v) != expect);		\
पूर्ण जबतक (0)

#घोषणा XCHG_FAMILY_TEST(bit, init, new)				\
करो अणु									\
	FAMILY_TEST(TEST_ARGS, bit, xchg, init, init, new, new);	\
पूर्ण जबतक (0)

#घोषणा CMPXCHG_FAMILY_TEST(bit, init, new, wrong)			\
करो अणु									\
	FAMILY_TEST(TEST_ARGS, bit, cmpxchg, 				\
			init, init, new, init, new);			\
	FAMILY_TEST(TEST_ARGS, bit, cmpxchg,				\
			init, init, init, wrong, new);			\
पूर्ण जबतक (0)

#घोषणा INC_RETURN_FAMILY_TEST(bit, i)			\
करो अणु							\
	FAMILY_TEST(TEST_ARGS, bit, inc_वापस,		\
			i, (i) + one, (i) + one);	\
पूर्ण जबतक (0)

#घोषणा DEC_RETURN_FAMILY_TEST(bit, i)			\
करो अणु							\
	FAMILY_TEST(TEST_ARGS, bit, dec_वापस,		\
			i, (i) - one, (i) - one);	\
पूर्ण जबतक (0)

अटल __init व्योम test_atomic(व्योम)
अणु
	पूर्णांक v0 = 0xaaa31337;
	पूर्णांक v1 = 0xdeadbeef;
	पूर्णांक onestwos = 0x11112222;
	पूर्णांक one = 1;

	atomic_t v;
	पूर्णांक r;

	TEST(, add, +=, onestwos);
	TEST(, add, +=, -one);
	TEST(, sub, -=, onestwos);
	TEST(, sub, -=, -one);
	TEST(, or, |=, v1);
	TEST(, and, &=, v1);
	TEST(, xor, ^=, v1);
	TEST(, andnot, &= ~, v1);

	RETURN_FAMILY_TEST(, add_वापस, +=, onestwos);
	RETURN_FAMILY_TEST(, add_वापस, +=, -one);
	RETURN_FAMILY_TEST(, sub_वापस, -=, onestwos);
	RETURN_FAMILY_TEST(, sub_वापस, -=, -one);

	FETCH_FAMILY_TEST(, fetch_add, +=, onestwos);
	FETCH_FAMILY_TEST(, fetch_add, +=, -one);
	FETCH_FAMILY_TEST(, fetch_sub, -=, onestwos);
	FETCH_FAMILY_TEST(, fetch_sub, -=, -one);

	FETCH_FAMILY_TEST(, fetch_or,  |=, v1);
	FETCH_FAMILY_TEST(, fetch_and, &=, v1);
	FETCH_FAMILY_TEST(, fetch_andnot, &= ~, v1);
	FETCH_FAMILY_TEST(, fetch_xor, ^=, v1);

	INC_RETURN_FAMILY_TEST(, v0);
	DEC_RETURN_FAMILY_TEST(, v0);

	XCHG_FAMILY_TEST(, v0, v1);
	CMPXCHG_FAMILY_TEST(, v0, v1, onestwos);

पूर्ण

#घोषणा INIT(c) करो अणु atomic64_set(&v, c); r = c; पूर्ण जबतक (0)
अटल __init व्योम test_atomic64(व्योम)
अणु
	दीर्घ दीर्घ v0 = 0xaaa31337c001d00dLL;
	दीर्घ दीर्घ v1 = 0xdeadbeefdeafcafeLL;
	दीर्घ दीर्घ v2 = 0xfaceabadf00df001LL;
	दीर्घ दीर्घ v3 = 0x8000000000000000LL;
	दीर्घ दीर्घ onestwos = 0x1111111122222222LL;
	दीर्घ दीर्घ one = 1LL;
	पूर्णांक r_पूर्णांक;

	atomic64_t v = ATOMIC64_INIT(v0);
	दीर्घ दीर्घ r = v0;
	BUG_ON(v.counter != r);

	atomic64_set(&v, v1);
	r = v1;
	BUG_ON(v.counter != r);
	BUG_ON(atomic64_पढ़ो(&v) != r);

	TEST(64, add, +=, onestwos);
	TEST(64, add, +=, -one);
	TEST(64, sub, -=, onestwos);
	TEST(64, sub, -=, -one);
	TEST(64, or, |=, v1);
	TEST(64, and, &=, v1);
	TEST(64, xor, ^=, v1);
	TEST(64, andnot, &= ~, v1);

	RETURN_FAMILY_TEST(64, add_वापस, +=, onestwos);
	RETURN_FAMILY_TEST(64, add_वापस, +=, -one);
	RETURN_FAMILY_TEST(64, sub_वापस, -=, onestwos);
	RETURN_FAMILY_TEST(64, sub_वापस, -=, -one);

	FETCH_FAMILY_TEST(64, fetch_add, +=, onestwos);
	FETCH_FAMILY_TEST(64, fetch_add, +=, -one);
	FETCH_FAMILY_TEST(64, fetch_sub, -=, onestwos);
	FETCH_FAMILY_TEST(64, fetch_sub, -=, -one);

	FETCH_FAMILY_TEST(64, fetch_or,  |=, v1);
	FETCH_FAMILY_TEST(64, fetch_and, &=, v1);
	FETCH_FAMILY_TEST(64, fetch_andnot, &= ~, v1);
	FETCH_FAMILY_TEST(64, fetch_xor, ^=, v1);

	INIT(v0);
	atomic64_inc(&v);
	r += one;
	BUG_ON(v.counter != r);

	INIT(v0);
	atomic64_dec(&v);
	r -= one;
	BUG_ON(v.counter != r);

	INC_RETURN_FAMILY_TEST(64, v0);
	DEC_RETURN_FAMILY_TEST(64, v0);

	XCHG_FAMILY_TEST(64, v0, v1);
	CMPXCHG_FAMILY_TEST(64, v0, v1, v2);

	INIT(v0);
	BUG_ON(atomic64_add_unless(&v, one, v0));
	BUG_ON(v.counter != r);

	INIT(v0);
	BUG_ON(!atomic64_add_unless(&v, one, v1));
	r += one;
	BUG_ON(v.counter != r);

	INIT(onestwos);
	BUG_ON(atomic64_dec_अगर_positive(&v) != (onestwos - 1));
	r -= one;
	BUG_ON(v.counter != r);

	INIT(0);
	BUG_ON(atomic64_dec_अगर_positive(&v) != -one);
	BUG_ON(v.counter != r);

	INIT(-one);
	BUG_ON(atomic64_dec_अगर_positive(&v) != (-one - one));
	BUG_ON(v.counter != r);

	INIT(onestwos);
	BUG_ON(!atomic64_inc_not_zero(&v));
	r += one;
	BUG_ON(v.counter != r);

	INIT(0);
	BUG_ON(atomic64_inc_not_zero(&v));
	BUG_ON(v.counter != r);

	INIT(-one);
	BUG_ON(!atomic64_inc_not_zero(&v));
	r += one;
	BUG_ON(v.counter != r);

	/* Confirm the वापस value fits in an पूर्णांक, even अगर the value करोesn't */
	INIT(v3);
	r_पूर्णांक = atomic64_inc_not_zero(&v);
	BUG_ON(!r_पूर्णांक);
पूर्ण

अटल __init पूर्णांक test_atomics_init(व्योम)
अणु
	test_atomic();
	test_atomic64();

#अगर_घोषित CONFIG_X86
	pr_info("passed for %s platform %s CX8 and %s SSE\n",
#अगर_घोषित CONFIG_X86_64
		"x86-64",
#या_अगर defined(CONFIG_X86_CMPXCHG64)
		"i586+",
#अन्यथा
		"i386+",
#पूर्ण_अगर
	       boot_cpu_has(X86_FEATURE_CX8) ? "with" : "without",
	       boot_cpu_has(X86_FEATURE_XMM) ? "with" : "without");
#अन्यथा
	pr_info("passed\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल __निकास व्योम test_atomics_निकास(व्योम) अणुपूर्ण

module_init(test_atomics_init);
module_निकास(test_atomics_निकास);

MODULE_LICENSE("GPL");
