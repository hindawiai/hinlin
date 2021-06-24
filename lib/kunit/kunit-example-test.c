<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Example KUnit test to show how to use KUnit.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#समावेश <kunit/test.h>

/*
 * This is the most fundamental element of KUnit, the test हाल. A test हाल
 * makes a set EXPECTATIONs and ASSERTIONs about the behavior of some code; अगर
 * any expectations or निश्चितions are not met, the test fails; otherwise, the
 * test passes.
 *
 * In KUnit, a test हाल is just a function with the signature
 * `व्योम (*)(काष्ठा kunit *)`. `काष्ठा kunit` is a context object that stores
 * inक्रमmation about the current test.
 */
अटल व्योम example_simple_test(काष्ठा kunit *test)
अणु
	/*
	 * This is an EXPECTATION; it is how KUnit tests things. When you want
	 * to test a piece of code, you set some expectations about what the
	 * code should करो. KUnit then runs the test and verअगरies that the code's
	 * behavior matched what was expected.
	 */
	KUNIT_EXPECT_EQ(test, 1 + 1, 2);
पूर्ण

/*
 * This is run once beक्रमe each test हाल, see the comment on
 * example_test_suite क्रम more inक्रमmation.
 */
अटल पूर्णांक example_test_init(काष्ठा kunit *test)
अणु
	kunit_info(test, "initializing\n");

	वापस 0;
पूर्ण

/*
 * Here we make a list of all the test हालs we want to add to the test suite
 * below.
 */
अटल काष्ठा kunit_हाल example_test_हालs[] = अणु
	/*
	 * This is a helper to create a test हाल object from a test हाल
	 * function; its exact function is not important to understand how to
	 * use KUnit, just know that this is how you associate test हालs with a
	 * test suite.
	 */
	KUNIT_CASE(example_simple_test),
	अणुपूर्ण
पूर्ण;

/*
 * This defines a suite or grouping of tests.
 *
 * Test हालs are defined as beदीर्घing to the suite by adding them to
 * `kunit_हालs`.
 *
 * Often it is desirable to run some function which will set up things which
 * will be used by every test; this is accomplished with an `init` function
 * which runs beक्रमe each test हाल is invoked. Similarly, an `निकास` function
 * may be specअगरied which runs after every test हाल and can be used to क्रम
 * cleanup. For clarity, running tests in a test suite would behave as follows:
 *
 * suite.init(test);
 * suite.test_हाल[0](test);
 * suite.निकास(test);
 * suite.init(test);
 * suite.test_हाल[1](test);
 * suite.निकास(test);
 * ...;
 */
अटल काष्ठा kunit_suite example_test_suite = अणु
	.name = "example",
	.init = example_test_init,
	.test_हालs = example_test_हालs,
पूर्ण;

/*
 * This रेजिस्टरs the above test suite telling KUnit that this is a suite of
 * tests that need to be run.
 */
kunit_test_suites(&example_test_suite);

MODULE_LICENSE("GPL v2");
