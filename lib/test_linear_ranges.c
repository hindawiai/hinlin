<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KUnit test क्रम the linear_ranges helper.
 *
 * Copyright (C) 2020, ROHM Semiconductors.
 * Author: Matti Vaittinen <matti.vaittien@fi.rohmeurope.com>
 */
#समावेश <kunit/test.h>

#समावेश <linux/linear_range.h>

/* First things first. I deeply dislike unit-tests. I have seen all the hell
 * अवरोधing loose when people who think the unit tests are "the silver bullet"
 * to समाप्त bugs get to decide how a company should implement testing strategy...
 *
 * Believe me, it may get _really_ ridiculous. It is tempting to think that
 * walking through all the possible execution branches will nail करोwn 100% of
 * bugs. This may lead to ideas about demands to get certain % of "test
 * coverage" - measured as line coverage. And that is one of the worst things
 * you can करो.
 *
 * Ask people to provide line coverage and they करो. I've seen clever tools
 * which generate test हालs to test the existing functions - and by शेष
 * these tools expect code to be correct and just generate checks which are
 * passing when ran against current code-base. Run this generator and you'll get
 * tests that करो not test code is correct but just verअगरy nothing changes.
 * Problem is that testing working code is poपूर्णांकless. And अगर it is not
 * working, your test must not assume it is working. You won't catch any bugs
 * by such tests. What you can करो is to generate a huge amount of tests.
 * Especially अगर you were are asked to proivde 100% line-coverage x_x. So what
 * करोes these tests - which are not finding any bugs now - करो?
 *
 * They add inertia to every future development. I think it was Terry Pratchet
 * who wrote someone having same impact as thick syrup has to chronometre.
 * Excessive amount of unit-tests have this effect to development. If you करो
 * actually find _any_ bug from code in such environment and try fixing it...
 * ...chances are you also need to fix the test हालs. In sunny day you fix one
 * test. But I've करोne refactoring which resulted 500+ broken tests (which had
 * really zero value other than proving to managers that we करो करो "quality")...
 *
 * After this being said - there are situations where UTs can be handy. If you
 * have algorithms which take some input and should produce output - then you
 * can implement few, carefully selected simple UT-हालs which test this. I've
 * previously used this क्रम example क्रम netlink and device-tree data parsing
 * functions. Feed some data examples to functions and verअगरy the output is as
 * expected. I am not covering all the हालs but I will see the logic should be
 * working.
 *
 * Here we also करो some minor testing. I करोn't want to go through all branches
 * or test more or less obvious things - but I want to see the मुख्य logic is
 * working. And I definitely करोn't want to add 500+ test हालs that अवरोध when
 * some simple fix is करोne x_x. So - let's only add few, well selected tests
 * which ensure as much logic is good as possible.
 */

/*
 * Test Range 1:
 * selectors:	2	3	4	5	6
 * values (5):	10	20	30	40	50
 *
 * Test Range 2:
 * selectors:	7	8	9	10
 * values (4):	100	150	200	250
 */

#घोषणा RANGE1_MIN 10
#घोषणा RANGE1_MIN_SEL 2
#घोषणा RANGE1_STEP 10

/* 2, 3, 4, 5, 6 */
अटल स्थिर अचिन्हित पूर्णांक range1_sels[] = अणु RANGE1_MIN_SEL, RANGE1_MIN_SEL + 1,
					    RANGE1_MIN_SEL + 2,
					    RANGE1_MIN_SEL + 3,
					    RANGE1_MIN_SEL + 4 पूर्ण;
/* 10, 20, 30, 40, 50 */
अटल स्थिर अचिन्हित पूर्णांक range1_vals[] = अणु RANGE1_MIN, RANGE1_MIN +
					    RANGE1_STEP,
					    RANGE1_MIN + RANGE1_STEP * 2,
					    RANGE1_MIN + RANGE1_STEP * 3,
					    RANGE1_MIN + RANGE1_STEP * 4 पूर्ण;

#घोषणा RANGE2_MIN 100
#घोषणा RANGE2_MIN_SEL 7
#घोषणा RANGE2_STEP 50

/*  7, 8, 9, 10 */
अटल स्थिर अचिन्हित पूर्णांक range2_sels[] = अणु RANGE2_MIN_SEL, RANGE2_MIN_SEL + 1,
					    RANGE2_MIN_SEL + 2,
					    RANGE2_MIN_SEL + 3 पूर्ण;
/* 100, 150, 200, 250 */
अटल स्थिर अचिन्हित पूर्णांक range2_vals[] = अणु RANGE2_MIN, RANGE2_MIN +
					    RANGE2_STEP,
					    RANGE2_MIN + RANGE2_STEP * 2,
					    RANGE2_MIN + RANGE2_STEP * 3 पूर्ण;

#घोषणा RANGE1_NUM_VALS (ARRAY_SIZE(range1_vals))
#घोषणा RANGE2_NUM_VALS (ARRAY_SIZE(range2_vals))
#घोषणा RANGE_NUM_VALS (RANGE1_NUM_VALS + RANGE2_NUM_VALS)

#घोषणा RANGE1_MAX_SEL (RANGE1_MIN_SEL + RANGE1_NUM_VALS - 1)
#घोषणा RANGE1_MAX_VAL (range1_vals[RANGE1_NUM_VALS - 1])

#घोषणा RANGE2_MAX_SEL (RANGE2_MIN_SEL + RANGE2_NUM_VALS - 1)
#घोषणा RANGE2_MAX_VAL (range2_vals[RANGE2_NUM_VALS - 1])

#घोषणा SMALLEST_SEL RANGE1_MIN_SEL
#घोषणा SMALLEST_VAL RANGE1_MIN

अटल काष्ठा linear_range testr[] = अणु
	अणु
		.min = RANGE1_MIN,
		.min_sel = RANGE1_MIN_SEL,
		.max_sel = RANGE1_MAX_SEL,
		.step = RANGE1_STEP,
	पूर्ण, अणु
		.min = RANGE2_MIN,
		.min_sel = RANGE2_MIN_SEL,
		.max_sel = RANGE2_MAX_SEL,
		.step = RANGE2_STEP
	पूर्ण,
पूर्ण;

अटल व्योम range_test_get_value(काष्ठा kunit *test)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक sel, val;

	क्रम (i = 0; i < RANGE1_NUM_VALS; i++) अणु
		sel = range1_sels[i];
		ret = linear_range_get_value_array(&testr[0], 2, sel, &val);
		KUNIT_EXPECT_EQ(test, 0, ret);
		KUNIT_EXPECT_EQ(test, val, range1_vals[i]);
	पूर्ण
	क्रम (i = 0; i < RANGE2_NUM_VALS; i++) अणु
		sel = range2_sels[i];
		ret = linear_range_get_value_array(&testr[0], 2, sel, &val);
		KUNIT_EXPECT_EQ(test, 0, ret);
		KUNIT_EXPECT_EQ(test, val, range2_vals[i]);
	पूर्ण
	ret = linear_range_get_value_array(&testr[0], 2, sel + 1, &val);
	KUNIT_EXPECT_NE(test, 0, ret);
पूर्ण

अटल व्योम range_test_get_selector_high(काष्ठा kunit *test)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक sel;
	bool found;

	क्रम (i = 0; i < RANGE1_NUM_VALS; i++) अणु
		ret = linear_range_get_selector_high(&testr[0], range1_vals[i],
						     &sel, &found);
		KUNIT_EXPECT_EQ(test, 0, ret);
		KUNIT_EXPECT_EQ(test, sel, range1_sels[i]);
		KUNIT_EXPECT_TRUE(test, found);
	पूर्ण

	ret = linear_range_get_selector_high(&testr[0], RANGE1_MAX_VAL + 1,
					     &sel, &found);
	KUNIT_EXPECT_LE(test, ret, 0);

	ret = linear_range_get_selector_high(&testr[0], RANGE1_MIN - 1,
					     &sel, &found);
	KUNIT_EXPECT_EQ(test, 0, ret);
	KUNIT_EXPECT_FALSE(test, found);
	KUNIT_EXPECT_EQ(test, sel, range1_sels[0]);
पूर्ण

अटल व्योम range_test_get_value_amount(काष्ठा kunit *test)
अणु
	पूर्णांक ret;

	ret = linear_range_values_in_range_array(&testr[0], 2);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)RANGE_NUM_VALS, ret);
पूर्ण

अटल व्योम range_test_get_selector_low(काष्ठा kunit *test)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक sel;
	bool found;

	क्रम (i = 0; i < RANGE1_NUM_VALS; i++) अणु
		ret = linear_range_get_selector_low_array(&testr[0], 2,
							  range1_vals[i], &sel,
							  &found);
		KUNIT_EXPECT_EQ(test, 0, ret);
		KUNIT_EXPECT_EQ(test, sel, range1_sels[i]);
		KUNIT_EXPECT_TRUE(test, found);
	पूर्ण
	क्रम (i = 0; i < RANGE2_NUM_VALS; i++) अणु
		ret = linear_range_get_selector_low_array(&testr[0], 2,
							  range2_vals[i], &sel,
							  &found);
		KUNIT_EXPECT_EQ(test, 0, ret);
		KUNIT_EXPECT_EQ(test, sel, range2_sels[i]);
		KUNIT_EXPECT_TRUE(test, found);
	पूर्ण

	/*
	 * Seek value greater than range max => get_selector_*_low should
	 * वापस Ok - but set found to false as value is not in range
	 */
	ret = linear_range_get_selector_low_array(&testr[0], 2,
					range2_vals[RANGE2_NUM_VALS - 1] + 1,
					&sel, &found);

	KUNIT_EXPECT_EQ(test, 0, ret);
	KUNIT_EXPECT_EQ(test, sel, range2_sels[RANGE2_NUM_VALS - 1]);
	KUNIT_EXPECT_FALSE(test, found);
पूर्ण

अटल काष्ठा kunit_हाल range_test_हालs[] = अणु
	KUNIT_CASE(range_test_get_value_amount),
	KUNIT_CASE(range_test_get_selector_high),
	KUNIT_CASE(range_test_get_selector_low),
	KUNIT_CASE(range_test_get_value),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा kunit_suite range_test_module = अणु
	.name = "linear-ranges-test",
	.test_हालs = range_test_हालs,
पूर्ण;

kunit_test_suites(&range_test_module);

MODULE_LICENSE("GPL");
