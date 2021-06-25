<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KCSAN लघु boot-समय selftests.
 *
 * Copyright (C) 2019, Google LLC.
 */

#घोषणा pr_fmt(fmt) "kcsan: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/types.h>

#समावेश "encoding.h"

#घोषणा ITERS_PER_TEST 2000

/* Test requirements. */
अटल bool test_requires(व्योम)
अणु
	/* अक्रमom should be initialized क्रम the below tests */
	वापस pअक्रमom_u32() + pअक्रमom_u32() != 0;
पूर्ण

/*
 * Test watchpoपूर्णांक encode and decode: check that encoding some access's info,
 * and then subsequent decode preserves the access's info.
 */
अटल bool test_encode_decode(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ITERS_PER_TEST; ++i) अणु
		माप_प्रकार size = pअक्रमom_u32_max(MAX_ENCODABLE_SIZE) + 1;
		bool is_ग_लिखो = !!pअक्रमom_u32_max(2);
		अचिन्हित दीर्घ addr;

		pअक्रमom_bytes(&addr, माप(addr));
		अगर (addr < PAGE_SIZE)
			addr = PAGE_SIZE;

		अगर (WARN_ON(!check_encodable(addr, size)))
			वापस false;

		/* Encode and decode */
		अणु
			स्थिर दीर्घ encoded_watchpoपूर्णांक =
				encode_watchpoपूर्णांक(addr, size, is_ग_लिखो);
			अचिन्हित दीर्घ verअगर_masked_addr;
			माप_प्रकार verअगर_size;
			bool verअगर_is_ग_लिखो;

			/* Check special watchpoपूर्णांकs */
			अगर (WARN_ON(decode_watchpoपूर्णांक(
				    INVALID_WATCHPOINT, &verअगर_masked_addr,
				    &verअगर_size, &verअगर_is_ग_लिखो)))
				वापस false;
			अगर (WARN_ON(decode_watchpoपूर्णांक(
				    CONSUMED_WATCHPOINT, &verअगर_masked_addr,
				    &verअगर_size, &verअगर_is_ग_लिखो)))
				वापस false;

			/* Check decoding watchpoपूर्णांक वापसs same data */
			अगर (WARN_ON(!decode_watchpoपूर्णांक(
				    encoded_watchpoपूर्णांक, &verअगर_masked_addr,
				    &verअगर_size, &verअगर_is_ग_लिखो)))
				वापस false;
			अगर (WARN_ON(verअगर_masked_addr !=
				    (addr & WATCHPOINT_ADDR_MASK)))
				जाओ fail;
			अगर (WARN_ON(verअगर_size != size))
				जाओ fail;
			अगर (WARN_ON(is_ग_लिखो != verअगर_is_ग_लिखो))
				जाओ fail;

			जारी;
fail:
			pr_err("%s fail: %s %zu bytes @ %lx -> encoded: %lx -> %s %zu bytes @ %lx\n",
			       __func__, is_ग_लिखो ? "write" : "read", size,
			       addr, encoded_watchpoपूर्णांक,
			       verअगर_is_ग_लिखो ? "write" : "read", verअगर_size,
			       verअगर_masked_addr);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/* Test access matching function. */
अटल bool test_matching_access(व्योम)
अणु
	अगर (WARN_ON(!matching_access(10, 1, 10, 1)))
		वापस false;
	अगर (WARN_ON(!matching_access(10, 2, 11, 1)))
		वापस false;
	अगर (WARN_ON(!matching_access(10, 1, 9, 2)))
		वापस false;
	अगर (WARN_ON(matching_access(10, 1, 11, 1)))
		वापस false;
	अगर (WARN_ON(matching_access(9, 1, 10, 1)))
		वापस false;

	/*
	 * An access of size 0 could match another access, as demonstrated here.
	 * Rather than add more comparisons to 'matching_access()', which would
	 * end up in the fast-path क्रम *all* checks, check_access() simply
	 * वापसs क्रम all accesses of size 0.
	 */
	अगर (WARN_ON(!matching_access(8, 8, 12, 0)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init kcsan_selftest(व्योम)
अणु
	पूर्णांक passed = 0;
	पूर्णांक total = 0;

#घोषणा RUN_TEST(करो_test)                                                      \
	करो अणु                                                                   \
		++total;                                                       \
		अगर (करो_test())                                                 \
			++passed;                                              \
		अन्यथा                                                           \
			pr_err("selftest: " #करो_test " failed");               \
	पूर्ण जबतक (0)

	RUN_TEST(test_requires);
	RUN_TEST(test_encode_decode);
	RUN_TEST(test_matching_access);

	pr_info("selftest: %d/%d tests passed\n", passed, total);
	अगर (passed != total)
		panic("selftests failed");
	वापस 0;
पूर्ण
postcore_initcall(kcsan_selftest);
