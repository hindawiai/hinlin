<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is क्रम all the tests related to refcount bugs (e.g. overflow,
 * underflow, reaching zero untested, etc).
 */
#समावेश "lkdtm.h"
#समावेश <linux/refcount.h>

अटल व्योम overflow_check(refcount_t *ref)
अणु
	चयन (refcount_पढ़ो(ref)) अणु
	हाल REFCOUNT_SATURATED:
		pr_info("Overflow detected: saturated\n");
		अवरोध;
	हाल REFCOUNT_MAX:
		pr_warn("Overflow detected: unsafely reset to max\n");
		अवरोध;
	शेष:
		pr_err("Fail: refcount wrapped to %d\n", refcount_पढ़ो(ref));
	पूर्ण
पूर्ण

/*
 * A refcount_inc() above the maximum value of the refcount implementation,
 * should at least saturate, and at most also WARN.
 */
व्योम lkdपंचांग_REFCOUNT_INC_OVERFLOW(व्योम)
अणु
	refcount_t over = REFCOUNT_INIT(REFCOUNT_MAX - 1);

	pr_info("attempting good refcount_inc() without overflow\n");
	refcount_dec(&over);
	refcount_inc(&over);

	pr_info("attempting bad refcount_inc() overflow\n");
	refcount_inc(&over);
	refcount_inc(&over);

	overflow_check(&over);
पूर्ण

/* refcount_add() should behave just like refcount_inc() above. */
व्योम lkdपंचांग_REFCOUNT_ADD_OVERFLOW(व्योम)
अणु
	refcount_t over = REFCOUNT_INIT(REFCOUNT_MAX - 1);

	pr_info("attempting good refcount_add() without overflow\n");
	refcount_dec(&over);
	refcount_dec(&over);
	refcount_dec(&over);
	refcount_dec(&over);
	refcount_add(4, &over);

	pr_info("attempting bad refcount_add() overflow\n");
	refcount_add(4, &over);

	overflow_check(&over);
पूर्ण

/* refcount_inc_not_zero() should behave just like refcount_inc() above. */
व्योम lkdपंचांग_REFCOUNT_INC_NOT_ZERO_OVERFLOW(व्योम)
अणु
	refcount_t over = REFCOUNT_INIT(REFCOUNT_MAX);

	pr_info("attempting bad refcount_inc_not_zero() overflow\n");
	अगर (!refcount_inc_not_zero(&over))
		pr_warn("Weird: refcount_inc_not_zero() reported zero\n");

	overflow_check(&over);
पूर्ण

/* refcount_add_not_zero() should behave just like refcount_inc() above. */
व्योम lkdपंचांग_REFCOUNT_ADD_NOT_ZERO_OVERFLOW(व्योम)
अणु
	refcount_t over = REFCOUNT_INIT(REFCOUNT_MAX);

	pr_info("attempting bad refcount_add_not_zero() overflow\n");
	अगर (!refcount_add_not_zero(6, &over))
		pr_warn("Weird: refcount_add_not_zero() reported zero\n");

	overflow_check(&over);
पूर्ण

अटल व्योम check_zero(refcount_t *ref)
अणु
	चयन (refcount_पढ़ो(ref)) अणु
	हाल REFCOUNT_SATURATED:
		pr_info("Zero detected: saturated\n");
		अवरोध;
	हाल REFCOUNT_MAX:
		pr_warn("Zero detected: unsafely reset to max\n");
		अवरोध;
	हाल 0:
		pr_warn("Still at zero: refcount_inc/add() must not inc-from-0\n");
		अवरोध;
	शेष:
		pr_err("Fail: refcount went crazy: %d\n", refcount_पढ़ो(ref));
	पूर्ण
पूर्ण

/*
 * A refcount_dec(), as opposed to a refcount_dec_and_test(), when it hits
 * zero it should either saturate (when inc-from-zero isn't रक्षित)
 * or stay at zero (when inc-from-zero is रक्षित) and should WARN क्रम both.
 */
व्योम lkdपंचांग_REFCOUNT_DEC_ZERO(व्योम)
अणु
	refcount_t zero = REFCOUNT_INIT(2);

	pr_info("attempting good refcount_dec()\n");
	refcount_dec(&zero);

	pr_info("attempting bad refcount_dec() to zero\n");
	refcount_dec(&zero);

	check_zero(&zero);
पूर्ण

अटल व्योम check_negative(refcount_t *ref, पूर्णांक start)
अणु
	/*
	 * refcount_t refuses to move a refcount at all on an
	 * over-sub, so we have to track our starting position instead of
	 * looking only at zero-pinning.
	 */
	अगर (refcount_पढ़ो(ref) == start) अणु
		pr_warn("Still at %d: refcount_inc/add() must not inc-from-0\n",
			start);
		वापस;
	पूर्ण

	चयन (refcount_पढ़ो(ref)) अणु
	हाल REFCOUNT_SATURATED:
		pr_info("Negative detected: saturated\n");
		अवरोध;
	हाल REFCOUNT_MAX:
		pr_warn("Negative detected: unsafely reset to max\n");
		अवरोध;
	शेष:
		pr_err("Fail: refcount went crazy: %d\n", refcount_पढ़ो(ref));
	पूर्ण
पूर्ण

/* A refcount_dec() going negative should saturate and may WARN. */
व्योम lkdपंचांग_REFCOUNT_DEC_NEGATIVE(व्योम)
अणु
	refcount_t neg = REFCOUNT_INIT(0);

	pr_info("attempting bad refcount_dec() below zero\n");
	refcount_dec(&neg);

	check_negative(&neg, 0);
पूर्ण

/*
 * A refcount_dec_and_test() should act like refcount_dec() above when
 * going negative.
 */
व्योम lkdपंचांग_REFCOUNT_DEC_AND_TEST_NEGATIVE(व्योम)
अणु
	refcount_t neg = REFCOUNT_INIT(0);

	pr_info("attempting bad refcount_dec_and_test() below zero\n");
	अगर (refcount_dec_and_test(&neg))
		pr_warn("Weird: refcount_dec_and_test() reported zero\n");

	check_negative(&neg, 0);
पूर्ण

/*
 * A refcount_sub_and_test() should act like refcount_dec_and_test()
 * above when going negative.
 */
व्योम lkdपंचांग_REFCOUNT_SUB_AND_TEST_NEGATIVE(व्योम)
अणु
	refcount_t neg = REFCOUNT_INIT(3);

	pr_info("attempting bad refcount_sub_and_test() below zero\n");
	अगर (refcount_sub_and_test(5, &neg))
		pr_warn("Weird: refcount_sub_and_test() reported zero\n");

	check_negative(&neg, 3);
पूर्ण

अटल व्योम check_from_zero(refcount_t *ref)
अणु
	चयन (refcount_पढ़ो(ref)) अणु
	हाल 0:
		pr_info("Zero detected: stayed at zero\n");
		अवरोध;
	हाल REFCOUNT_SATURATED:
		pr_info("Zero detected: saturated\n");
		अवरोध;
	हाल REFCOUNT_MAX:
		pr_warn("Zero detected: unsafely reset to max\n");
		अवरोध;
	शेष:
		pr_info("Fail: zero not detected, incremented to %d\n",
			refcount_पढ़ो(ref));
	पूर्ण
पूर्ण

/*
 * A refcount_inc() from zero should pin to zero or saturate and may WARN.
 */
व्योम lkdपंचांग_REFCOUNT_INC_ZERO(व्योम)
अणु
	refcount_t zero = REFCOUNT_INIT(0);

	pr_info("attempting safe refcount_inc_not_zero() from zero\n");
	अगर (!refcount_inc_not_zero(&zero)) अणु
		pr_info("Good: zero detected\n");
		अगर (refcount_पढ़ो(&zero) == 0)
			pr_info("Correctly stayed at zero\n");
		अन्यथा
			pr_err("Fail: refcount went past zero!\n");
	पूर्ण अन्यथा अणु
		pr_err("Fail: Zero not detected!?\n");
	पूर्ण

	pr_info("attempting bad refcount_inc() from zero\n");
	refcount_inc(&zero);

	check_from_zero(&zero);
पूर्ण

/*
 * A refcount_add() should act like refcount_inc() above when starting
 * at zero.
 */
व्योम lkdपंचांग_REFCOUNT_ADD_ZERO(व्योम)
अणु
	refcount_t zero = REFCOUNT_INIT(0);

	pr_info("attempting safe refcount_add_not_zero() from zero\n");
	अगर (!refcount_add_not_zero(3, &zero)) अणु
		pr_info("Good: zero detected\n");
		अगर (refcount_पढ़ो(&zero) == 0)
			pr_info("Correctly stayed at zero\n");
		अन्यथा
			pr_err("Fail: refcount went past zero\n");
	पूर्ण अन्यथा अणु
		pr_err("Fail: Zero not detected!?\n");
	पूर्ण

	pr_info("attempting bad refcount_add() from zero\n");
	refcount_add(3, &zero);

	check_from_zero(&zero);
पूर्ण

अटल व्योम check_saturated(refcount_t *ref)
अणु
	चयन (refcount_पढ़ो(ref)) अणु
	हाल REFCOUNT_SATURATED:
		pr_info("Saturation detected: still saturated\n");
		अवरोध;
	हाल REFCOUNT_MAX:
		pr_warn("Saturation detected: unsafely reset to max\n");
		अवरोध;
	शेष:
		pr_err("Fail: refcount went crazy: %d\n", refcount_पढ़ो(ref));
	पूर्ण
पूर्ण

/*
 * A refcount_inc() from a saturated value should at most warn about
 * being saturated alपढ़ोy.
 */
व्योम lkdपंचांग_REFCOUNT_INC_SATURATED(व्योम)
अणु
	refcount_t sat = REFCOUNT_INIT(REFCOUNT_SATURATED);

	pr_info("attempting bad refcount_inc() from saturated\n");
	refcount_inc(&sat);

	check_saturated(&sat);
पूर्ण

/* Should act like refcount_inc() above from saturated. */
व्योम lkdपंचांग_REFCOUNT_DEC_SATURATED(व्योम)
अणु
	refcount_t sat = REFCOUNT_INIT(REFCOUNT_SATURATED);

	pr_info("attempting bad refcount_dec() from saturated\n");
	refcount_dec(&sat);

	check_saturated(&sat);
पूर्ण

/* Should act like refcount_inc() above from saturated. */
व्योम lkdपंचांग_REFCOUNT_ADD_SATURATED(व्योम)
अणु
	refcount_t sat = REFCOUNT_INIT(REFCOUNT_SATURATED);

	pr_info("attempting bad refcount_dec() from saturated\n");
	refcount_add(8, &sat);

	check_saturated(&sat);
पूर्ण

/* Should act like refcount_inc() above from saturated. */
व्योम lkdपंचांग_REFCOUNT_INC_NOT_ZERO_SATURATED(व्योम)
अणु
	refcount_t sat = REFCOUNT_INIT(REFCOUNT_SATURATED);

	pr_info("attempting bad refcount_inc_not_zero() from saturated\n");
	अगर (!refcount_inc_not_zero(&sat))
		pr_warn("Weird: refcount_inc_not_zero() reported zero\n");

	check_saturated(&sat);
पूर्ण

/* Should act like refcount_inc() above from saturated. */
व्योम lkdपंचांग_REFCOUNT_ADD_NOT_ZERO_SATURATED(व्योम)
अणु
	refcount_t sat = REFCOUNT_INIT(REFCOUNT_SATURATED);

	pr_info("attempting bad refcount_add_not_zero() from saturated\n");
	अगर (!refcount_add_not_zero(7, &sat))
		pr_warn("Weird: refcount_add_not_zero() reported zero\n");

	check_saturated(&sat);
पूर्ण

/* Should act like refcount_inc() above from saturated. */
व्योम lkdपंचांग_REFCOUNT_DEC_AND_TEST_SATURATED(व्योम)
अणु
	refcount_t sat = REFCOUNT_INIT(REFCOUNT_SATURATED);

	pr_info("attempting bad refcount_dec_and_test() from saturated\n");
	अगर (refcount_dec_and_test(&sat))
		pr_warn("Weird: refcount_dec_and_test() reported zero\n");

	check_saturated(&sat);
पूर्ण

/* Should act like refcount_inc() above from saturated. */
व्योम lkdपंचांग_REFCOUNT_SUB_AND_TEST_SATURATED(व्योम)
अणु
	refcount_t sat = REFCOUNT_INIT(REFCOUNT_SATURATED);

	pr_info("attempting bad refcount_sub_and_test() from saturated\n");
	अगर (refcount_sub_and_test(8, &sat))
		pr_warn("Weird: refcount_sub_and_test() reported zero\n");

	check_saturated(&sat);
पूर्ण

/* Used to समय the existing atomic_t when used क्रम reference counting */
व्योम lkdपंचांग_ATOMIC_TIMING(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	atomic_t count = ATOMIC_INIT(1);

	क्रम (i = 0; i < पूर्णांक_उच्च - 1; i++)
		atomic_inc(&count);

	क्रम (i = पूर्णांक_उच्च; i > 0; i--)
		अगर (atomic_dec_and_test(&count))
			अवरोध;

	अगर (i != 1)
		pr_err("atomic timing: out of sync up/down cycle: %u\n", i - 1);
	अन्यथा
		pr_info("atomic timing: done\n");
पूर्ण

/*
 * This can be compared to ATOMIC_TIMING when implementing fast refcount
 * protections. Looking at the number of CPU cycles tells the real story
 * about perक्रमmance. For example:
 *    cd /sys/kernel/debug/provoke-crash
 *    perf stat -B -- cat <(echo REFCOUNT_TIMING) > सूचीECT
 */
व्योम lkdपंचांग_REFCOUNT_TIMING(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	refcount_t count = REFCOUNT_INIT(1);

	क्रम (i = 0; i < पूर्णांक_उच्च - 1; i++)
		refcount_inc(&count);

	क्रम (i = पूर्णांक_उच्च; i > 0; i--)
		अगर (refcount_dec_and_test(&count))
			अवरोध;

	अगर (i != 1)
		pr_err("refcount: out of sync up/down cycle: %u\n", i - 1);
	अन्यथा
		pr_info("refcount timing: done\n");
पूर्ण
