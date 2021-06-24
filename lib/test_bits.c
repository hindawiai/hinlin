<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Test हालs क्रम functions and macros in bits.h
 */

#समावेश <kunit/test.h>
#समावेश <linux/bits.h>


अटल व्योम genmask_test(काष्ठा kunit *test)
अणु
	KUNIT_EXPECT_EQ(test, 1ul, GENMASK(0, 0));
	KUNIT_EXPECT_EQ(test, 3ul, GENMASK(1, 0));
	KUNIT_EXPECT_EQ(test, 6ul, GENMASK(2, 1));
	KUNIT_EXPECT_EQ(test, 0xFFFFFFFFul, GENMASK(31, 0));

#अगर_घोषित TEST_GENMASK_FAILURES
	/* these should fail compilation */
	GENMASK(0, 1);
	GENMASK(0, 10);
	GENMASK(9, 10);
#पूर्ण_अगर


पूर्ण

अटल व्योम genmask_ull_test(काष्ठा kunit *test)
अणु
	KUNIT_EXPECT_EQ(test, 1ull, GENMASK_ULL(0, 0));
	KUNIT_EXPECT_EQ(test, 3ull, GENMASK_ULL(1, 0));
	KUNIT_EXPECT_EQ(test, 0x000000ffffe00000ull, GENMASK_ULL(39, 21));
	KUNIT_EXPECT_EQ(test, 0xffffffffffffffffull, GENMASK_ULL(63, 0));

#अगर_घोषित TEST_GENMASK_FAILURES
	/* these should fail compilation */
	GENMASK_ULL(0, 1);
	GENMASK_ULL(0, 10);
	GENMASK_ULL(9, 10);
#पूर्ण_अगर
पूर्ण

अटल व्योम genmask_input_check_test(काष्ठा kunit *test)
अणु
	अचिन्हित पूर्णांक x, y;
	पूर्णांक z, w;

	/* Unknown input */
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(x, 0));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(0, x));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(x, y));

	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(z, 0));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(0, z));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(z, w));

	/* Valid input */
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(1, 1));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(39, 21));
पूर्ण


अटल काष्ठा kunit_हाल bits_test_हालs[] = अणु
	KUNIT_CASE(genmask_test),
	KUNIT_CASE(genmask_ull_test),
	KUNIT_CASE(genmask_input_check_test),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite bits_test_suite = अणु
	.name = "bits-test",
	.test_हालs = bits_test_हालs,
पूर्ण;
kunit_test_suite(bits_test_suite);

MODULE_LICENSE("GPL");
