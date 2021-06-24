<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
 *
 * kselftest_harness.h: simple C unit test helper.
 *
 * See करोcumentation in Documentation/dev-tools/kselftest.rst
 *
 * API inspired by code.google.com/p/googletest
 */

/**
 * DOC: example
 *
 * .. code-block:: c
 *
 *    #समावेश "../kselftest_harness.h"
 *
 *    TEST(standalone_test) अणु
 *      करो_some_stuff;
 *      EXPECT_GT(10, stuff) अणु
 *         stuff_state_t state;
 *         क्रमागतerate_stuff_state(&state);
 *         TH_LOG("expectation failed with state: %s", state.msg);
 *      पूर्ण
 *      more_stuff;
 *      ASSERT_NE(some_stuff, शून्य) TH_LOG("how did it happen?!");
 *      last_stuff;
 *      EXPECT_EQ(0, last_stuff);
 *    पूर्ण
 *
 *    FIXTURE(my_fixture) अणु
 *      mytype_t *data;
 *      पूर्णांक awesomeness_level;
 *    पूर्ण;
 *    FIXTURE_SETUP(my_fixture) अणु
 *      self->data = mytype_new();
 *      ASSERT_NE(शून्य, self->data);
 *    पूर्ण
 *    FIXTURE_TEARDOWN(my_fixture) अणु
 *      mytype_मुक्त(self->data);
 *    पूर्ण
 *    TEST_F(my_fixture, data_is_good) अणु
 *      EXPECT_EQ(1, is_my_data_good(self->data));
 *    पूर्ण
 *
 *    TEST_HARNESS_MAIN
 */

#अगर_अघोषित __KSELFTEST_HARNESS_H
#घोषणा __KSELFTEST_HARNESS_H

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <यंत्र/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "kselftest.h"

#घोषणा TEST_TIMEOUT_DEFAULT 30

/* Utilities exposed to the test definitions */
#अगर_अघोषित TH_LOG_STREAM
#  define TH_LOG_STREAM मानक_त्रुटि
#पूर्ण_अगर

#अगर_अघोषित TH_LOG_ENABLED
#  define TH_LOG_ENABLED 1
#पूर्ण_अगर

/**
 * TH_LOG()
 *
 * @fmt: क्रमmat string
 * @...: optional arguments
 *
 * .. code-block:: c
 *
 *     TH_LOG(क्रमmat, ...)
 *
 * Optional debug logging function available क्रम use in tests.
 * Logging may be enabled or disabled by defining TH_LOG_ENABLED.
 * E.g., #घोषणा TH_LOG_ENABLED 1
 *
 * If no definition is provided, logging is enabled by शेष.
 *
 * If there is no way to prपूर्णांक an error message क्रम the process running the
 * test (e.g. not allowed to ग_लिखो to मानक_त्रुटि), it is still possible to get the
 * ASSERT_* number क्रम which the test failed.  This behavior can be enabled by
 * writing `_metadata->no_prपूर्णांक = true;` beक्रमe the check sequence that is
 * unable to prपूर्णांक.  When an error occur, instead of prपूर्णांकing an error message
 * and calling `पात(3)`, the test process call `_निकास(2)` with the निश्चित
 * number as argument, which is then prपूर्णांकed by the parent process.
 */
#घोषणा TH_LOG(fmt, ...) करो अणु \
	अगर (TH_LOG_ENABLED) \
		__TH_LOG(fmt, ##__VA_ARGS__); \
पूर्ण जबतक (0)

/* Unconditional logger क्रम पूर्णांकernal use. */
#घोषणा __TH_LOG(fmt, ...) \
		ख_लिखो(TH_LOG_STREAM, "# %s:%d:%s:" fmt "\n", \
			__खाता__, __LINE__, _metadata->name, ##__VA_ARGS__)

/**
 * SKIP()
 *
 * @statement: statement to run after reporting SKIP
 * @fmt: क्रमmat string
 * @...: optional arguments
 *
 * .. code-block:: c
 *
 *     SKIP(statement, fmt, ...);
 *
 * This क्रमces a "pass" after reporting why something is being skipped
 * and runs "statement", which is usually "return" or "goto skip".
 */
#घोषणा SKIP(statement, fmt, ...) करो अणु \
	snम_लिखो(_metadata->results->reason, \
		 माप(_metadata->results->reason), fmt, ##__VA_ARGS__); \
	अगर (TH_LOG_ENABLED) अणु \
		ख_लिखो(TH_LOG_STREAM, "#      SKIP      %s\n", \
			_metadata->results->reason); \
	पूर्ण \
	_metadata->passed = 1; \
	_metadata->skip = 1; \
	_metadata->trigger = 0; \
	statement; \
पूर्ण जबतक (0)

/**
 * TEST() - Defines the test function and creates the registration
 * stub
 *
 * @test_name: test name
 *
 * .. code-block:: c
 *
 *     TEST(name) अणु implementation पूर्ण
 *
 * Defines a test by name.
 * Names must be unique and tests must not be run in parallel.  The
 * implementation containing block is a function and scoping should be treated
 * as such.  Returning early may be perक्रमmed with a bare "return;" statement.
 *
 * EXPECT_* and ASSERT_* are valid in a TEST() अणु पूर्ण context.
 */
#घोषणा TEST(test_name) __TEST_IMPL(test_name, -1)

/**
 * TEST_SIGNAL()
 *
 * @test_name: test name
 * @संकेत: संकेत number
 *
 * .. code-block:: c
 *
 *     TEST_SIGNAL(name, संकेत) अणु implementation पूर्ण
 *
 * Defines a test by name and the expected term संकेत.
 * Names must be unique and tests must not be run in parallel.  The
 * implementation containing block is a function and scoping should be treated
 * as such.  Returning early may be perक्रमmed with a bare "return;" statement.
 *
 * EXPECT_* and ASSERT_* are valid in a TEST() अणु पूर्ण context.
 */
#घोषणा TEST_SIGNAL(test_name, संकेत) __TEST_IMPL(test_name, संकेत)

#घोषणा __TEST_IMPL(test_name, _संकेत) \
	अटल व्योम test_name(काष्ठा __test_metadata *_metadata); \
	अटल अंतरभूत व्योम wrapper_##test_name( \
		काष्ठा __test_metadata *_metadata, \
		काष्ठा __fixture_variant_metadata *variant) \
	अणु \
		test_name(_metadata); \
	पूर्ण \
	अटल काष्ठा __test_metadata _##test_name##_object = \
		अणु .name = #test_name, \
		  .fn = &wrapper_##test_name, \
		  .fixture = &_fixture_global, \
		  .termsig = _संकेत, \
		  .समयout = TEST_TIMEOUT_DEFAULT, पूर्ण; \
	अटल व्योम __attribute__((स्थिरructor)) _रेजिस्टर_##test_name(व्योम) \
	अणु \
		__रेजिस्टर_test(&_##test_name##_object); \
	पूर्ण \
	अटल व्योम test_name( \
		काष्ठा __test_metadata __attribute__((unused)) *_metadata)

/**
 * FIXTURE_DATA() - Wraps the काष्ठा name so we have one less
 * argument to pass around
 *
 * @datatype_name: datatype name
 *
 * .. code-block:: c
 *
 *     FIXTURE_DATA(datatype_name)
 *
 * Almost always, you want just FIXTURE() instead (see below).
 * This call may be used when the type of the fixture data
 * is needed.  In general, this should not be needed unless
 * the *self* is being passed to a helper directly.
 */
#घोषणा FIXTURE_DATA(datatype_name) काष्ठा _test_data_##datatype_name

/**
 * FIXTURE() - Called once per fixture to setup the data and
 * रेजिस्टर
 *
 * @fixture_name: fixture name
 *
 * .. code-block:: c
 *
 *     FIXTURE(fixture_name) अणु
 *       type property1;
 *       ...
 *     पूर्ण;
 *
 * Defines the data provided to TEST_F()-defined tests as *self*.  It should be
 * populated and cleaned up using FIXTURE_SETUP() and FIXTURE_TEARDOWN().
 */
#घोषणा FIXTURE(fixture_name) \
	FIXTURE_VARIANT(fixture_name); \
	अटल काष्ठा __fixture_metadata _##fixture_name##_fixture_object = \
		अणु .name =  #fixture_name, पूर्ण; \
	अटल व्योम __attribute__((स्थिरructor)) \
	_रेजिस्टर_##fixture_name##_data(व्योम) \
	अणु \
		__रेजिस्टर_fixture(&_##fixture_name##_fixture_object); \
	पूर्ण \
	FIXTURE_DATA(fixture_name)

/**
 * FIXTURE_SETUP() - Prepares the setup function क्रम the fixture.
 * *_metadata* is included so that EXPECT_* and ASSERT_* work correctly.
 *
 * @fixture_name: fixture name
 *
 * .. code-block:: c
 *
 *     FIXTURE_SETUP(fixture_name) अणु implementation पूर्ण
 *
 * Populates the required "setup" function क्रम a fixture.  An instance of the
 * datatype defined with FIXTURE_DATA() will be exposed as *self* क्रम the
 * implementation.
 *
 * ASSERT_* are valid क्रम use in this context and will prempt the execution
 * of any dependent fixture tests.
 *
 * A bare "return;" statement may be used to वापस early.
 */
#घोषणा FIXTURE_SETUP(fixture_name) \
	व्योम fixture_name##_setup( \
		काष्ठा __test_metadata __attribute__((unused)) *_metadata, \
		FIXTURE_DATA(fixture_name) __attribute__((unused)) *self, \
		स्थिर FIXTURE_VARIANT(fixture_name) \
			__attribute__((unused)) *variant)

/**
 * FIXTURE_TEARDOWN()
 * *_metadata* is included so that EXPECT_* and ASSERT_* work correctly.
 *
 * @fixture_name: fixture name
 *
 * .. code-block:: c
 *
 *     FIXTURE_TEARDOWN(fixture_name) अणु implementation पूर्ण
 *
 * Populates the required "teardown" function क्रम a fixture.  An instance of the
 * datatype defined with FIXTURE_DATA() will be exposed as *self* क्रम the
 * implementation to clean up.
 *
 * A bare "return;" statement may be used to वापस early.
 */
#घोषणा FIXTURE_TEARDOWN(fixture_name) \
	व्योम fixture_name##_tearकरोwn( \
		काष्ठा __test_metadata __attribute__((unused)) *_metadata, \
		FIXTURE_DATA(fixture_name) __attribute__((unused)) *self)

/**
 * FIXTURE_VARIANT() - Optionally called once per fixture
 * to declare fixture variant
 *
 * @fixture_name: fixture name
 *
 * .. code-block:: c
 *
 *     FIXTURE_VARIANT(fixture_name) अणु
 *       type property1;
 *       ...
 *     पूर्ण;
 *
 * Defines type of स्थिरant parameters provided to FIXTURE_SETUP() and TEST_F()
 * as *variant*. Variants allow the same tests to be run with dअगरferent
 * arguments.
 */
#घोषणा FIXTURE_VARIANT(fixture_name) काष्ठा _fixture_variant_##fixture_name

/**
 * FIXTURE_VARIANT_ADD() - Called once per fixture
 * variant to setup and रेजिस्टर the data
 *
 * @fixture_name: fixture name
 * @variant_name: name of the parameter set
 *
 * .. code-block:: c
 *
 *     FIXTURE_VARIANT_ADD(fixture_name, variant_name) अणु
 *       .property1 = val1,
 *       ...
 *     पूर्ण;
 *
 * Defines a variant of the test fixture, provided to FIXTURE_SETUP() and
 * TEST_F() as *variant*. Tests of each fixture will be run once क्रम each
 * variant.
 */
#घोषणा FIXTURE_VARIANT_ADD(fixture_name, variant_name) \
	बाह्य FIXTURE_VARIANT(fixture_name) \
		_##fixture_name##_##variant_name##_variant; \
	अटल काष्ठा __fixture_variant_metadata \
		_##fixture_name##_##variant_name##_object = \
		अणु .name = #variant_name, \
		  .data = &_##fixture_name##_##variant_name##_variantपूर्ण; \
	अटल व्योम __attribute__((स्थिरructor)) \
		_रेजिस्टर_##fixture_name##_##variant_name(व्योम) \
	अणु \
		__रेजिस्टर_fixture_variant(&_##fixture_name##_fixture_object, \
			&_##fixture_name##_##variant_name##_object);	\
	पूर्ण \
	FIXTURE_VARIANT(fixture_name) \
		_##fixture_name##_##variant_name##_variant =

/**
 * TEST_F() - Emits test registration and helpers क्रम
 * fixture-based test हालs
 *
 * @fixture_name: fixture name
 * @test_name: test name
 *
 * .. code-block:: c
 *
 *     TEST_F(fixture, name) अणु implementation पूर्ण
 *
 * Defines a test that depends on a fixture (e.g., is part of a test हाल).
 * Very similar to TEST() except that *self* is the setup instance of fixture's
 * datatype exposed क्रम use by the implementation.
 *
 * Warning: use of ASSERT_* here will skip TEARDOWN.
 */
/* TODO(wad) रेजिस्टर fixtures on dedicated test lists. */
#घोषणा TEST_F(fixture_name, test_name) \
	__TEST_F_IMPL(fixture_name, test_name, -1, TEST_TIMEOUT_DEFAULT)

#घोषणा TEST_F_SIGNAL(fixture_name, test_name, संकेत) \
	__TEST_F_IMPL(fixture_name, test_name, संकेत, TEST_TIMEOUT_DEFAULT)

#घोषणा TEST_F_TIMEOUT(fixture_name, test_name, समयout) \
	__TEST_F_IMPL(fixture_name, test_name, -1, समयout)

#घोषणा __TEST_F_IMPL(fixture_name, test_name, संकेत, पंचांगout) \
	अटल व्योम fixture_name##_##test_name( \
		काष्ठा __test_metadata *_metadata, \
		FIXTURE_DATA(fixture_name) *self, \
		स्थिर FIXTURE_VARIANT(fixture_name) *variant); \
	अटल अंतरभूत व्योम wrapper_##fixture_name##_##test_name( \
		काष्ठा __test_metadata *_metadata, \
		काष्ठा __fixture_variant_metadata *variant) \
	अणु \
		/* fixture data is alloced, setup, and torn करोwn per call. */ \
		FIXTURE_DATA(fixture_name) self; \
		स_रखो(&self, 0, माप(FIXTURE_DATA(fixture_name))); \
		fixture_name##_setup(_metadata, &self, variant->data); \
		/* Let setup failure terminate early. */ \
		अगर (!_metadata->passed) \
			वापस; \
		fixture_name##_##test_name(_metadata, &self, variant->data); \
		fixture_name##_tearकरोwn(_metadata, &self); \
	पूर्ण \
	अटल काष्ठा __test_metadata \
		      _##fixture_name##_##test_name##_object = अणु \
		.name = #test_name, \
		.fn = &wrapper_##fixture_name##_##test_name, \
		.fixture = &_##fixture_name##_fixture_object, \
		.termsig = संकेत, \
		.समयout = पंचांगout, \
	 पूर्ण; \
	अटल व्योम __attribute__((स्थिरructor)) \
			_रेजिस्टर_##fixture_name##_##test_name(व्योम) \
	अणु \
		__रेजिस्टर_test(&_##fixture_name##_##test_name##_object); \
	पूर्ण \
	अटल व्योम fixture_name##_##test_name( \
		काष्ठा __test_metadata __attribute__((unused)) *_metadata, \
		FIXTURE_DATA(fixture_name) __attribute__((unused)) *self, \
		स्थिर FIXTURE_VARIANT(fixture_name) \
			__attribute__((unused)) *variant)

/**
 * TEST_HARNESS_MAIN - Simple wrapper to run the test harness
 *
 * .. code-block:: c
 *
 *     TEST_HARNESS_MAIN
 *
 * Use once to append a मुख्य() to the test file.
 */
#घोषणा TEST_HARNESS_MAIN \
	अटल व्योम __attribute__((स्थिरructor)) \
	__स्थिरructor_order_last(व्योम) \
	अणु \
		अगर (!__स्थिरructor_order) \
			__स्थिरructor_order = _CONSTRUCTOR_ORDER_BACKWARD; \
	पूर्ण \
	पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv) अणु \
		वापस test_harness_run(argc, argv); \
	पूर्ण

/**
 * DOC: चालकs
 *
 * Operators क्रम use in TEST() and TEST_F().
 * ASSERT_* calls will stop test execution immediately.
 * EXPECT_* calls will emit a failure warning, note it, and जारी.
 */

/**
 * ASSERT_EQ()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_EQ(expected, measured): expected == measured
 */
#घोषणा ASSERT_EQ(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, ==, 1)

/**
 * ASSERT_NE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_NE(expected, measured): expected != measured
 */
#घोषणा ASSERT_NE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, !=, 1)

/**
 * ASSERT_LT()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_LT(expected, measured): expected < measured
 */
#घोषणा ASSERT_LT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <, 1)

/**
 * ASSERT_LE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_LE(expected, measured): expected <= measured
 */
#घोषणा ASSERT_LE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <=, 1)

/**
 * ASSERT_GT()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_GT(expected, measured): expected > measured
 */
#घोषणा ASSERT_GT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >, 1)

/**
 * ASSERT_GE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_GE(expected, measured): expected >= measured
 */
#घोषणा ASSERT_GE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >=, 1)

/**
 * ASSERT_शून्य()
 *
 * @seen: measured value
 *
 * ASSERT_शून्य(measured): शून्य == measured
 */
#घोषणा ASSERT_शून्य(seen) \
	__EXPECT(शून्य, "NULL", seen, #seen, ==, 1)

/**
 * ASSERT_TRUE()
 *
 * @seen: measured value
 *
 * ASSERT_TRUE(measured): measured != 0
 */
#घोषणा ASSERT_TRUE(seen) \
	__EXPECT(0, "0", seen, #seen, !=, 1)

/**
 * ASSERT_FALSE()
 *
 * @seen: measured value
 *
 * ASSERT_FALSE(measured): measured == 0
 */
#घोषणा ASSERT_FALSE(seen) \
	__EXPECT(0, "0", seen, #seen, ==, 1)

/**
 * ASSERT_STREQ()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_STREQ(expected, measured): !म_भेद(expected, measured)
 */
#घोषणा ASSERT_STREQ(expected, seen) \
	__EXPECT_STR(expected, seen, ==, 1)

/**
 * ASSERT_STRNE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * ASSERT_STRNE(expected, measured): म_भेद(expected, measured)
 */
#घोषणा ASSERT_STRNE(expected, seen) \
	__EXPECT_STR(expected, seen, !=, 1)

/**
 * EXPECT_EQ()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_EQ(expected, measured): expected == measured
 */
#घोषणा EXPECT_EQ(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, ==, 0)

/**
 * EXPECT_NE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_NE(expected, measured): expected != measured
 */
#घोषणा EXPECT_NE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, !=, 0)

/**
 * EXPECT_LT()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_LT(expected, measured): expected < measured
 */
#घोषणा EXPECT_LT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <, 0)

/**
 * EXPECT_LE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_LE(expected, measured): expected <= measured
 */
#घोषणा EXPECT_LE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <=, 0)

/**
 * EXPECT_GT()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_GT(expected, measured): expected > measured
 */
#घोषणा EXPECT_GT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >, 0)

/**
 * EXPECT_GE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_GE(expected, measured): expected >= measured
 */
#घोषणा EXPECT_GE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >=, 0)

/**
 * EXPECT_शून्य()
 *
 * @seen: measured value
 *
 * EXPECT_शून्य(measured): शून्य == measured
 */
#घोषणा EXPECT_शून्य(seen) \
	__EXPECT(शून्य, "NULL", seen, #seen, ==, 0)

/**
 * EXPECT_TRUE()
 *
 * @seen: measured value
 *
 * EXPECT_TRUE(measured): 0 != measured
 */
#घोषणा EXPECT_TRUE(seen) \
	__EXPECT(0, "0", seen, #seen, !=, 0)

/**
 * EXPECT_FALSE()
 *
 * @seen: measured value
 *
 * EXPECT_FALSE(measured): 0 == measured
 */
#घोषणा EXPECT_FALSE(seen) \
	__EXPECT(0, "0", seen, #seen, ==, 0)

/**
 * EXPECT_STREQ()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_STREQ(expected, measured): !म_भेद(expected, measured)
 */
#घोषणा EXPECT_STREQ(expected, seen) \
	__EXPECT_STR(expected, seen, ==, 0)

/**
 * EXPECT_STRNE()
 *
 * @expected: expected value
 * @seen: measured value
 *
 * EXPECT_STRNE(expected, measured): म_भेद(expected, measured)
 */
#घोषणा EXPECT_STRNE(expected, seen) \
	__EXPECT_STR(expected, seen, !=, 0)

#घोषणा ARRAY_SIZE(a)	(माप(a) / माप(a[0]))

/* Support an optional handler after and ASSERT_* or EXPECT_*.  The approach is
 * not thपढ़ो-safe, but it should be fine in most sane test scenarios.
 *
 * Using __bail(), which optionally पात()s, is the easiest way to early
 * वापस जबतक still providing an optional block to the API consumer.
 */
#घोषणा OPTIONAL_HANDLER(_निश्चित) \
	क्रम (; _metadata->trigger; _metadata->trigger = \
			__bail(_निश्चित, _metadata->no_prपूर्णांक, _metadata->step))

#घोषणा __INC_STEP(_metadata) \
	/* Keep "step" below 255 (which is used क्रम "SKIP" reporting). */	\
	अगर (_metadata->passed && _metadata->step < 253) \
		_metadata->step++;

#घोषणा is_चिन्हित_type(var)       (!!(((__typeof__(var))(-1)) < (__typeof__(var))1))

#घोषणा __EXPECT(_expected, _expected_str, _seen, _seen_str, _t, _निश्चित) करो अणु \
	/* Aव्योम multiple evaluation of the हालs */ \
	__typeof__(_expected) __exp = (_expected); \
	__typeof__(_seen) __seen = (_seen); \
	अगर (_निश्चित) __INC_STEP(_metadata); \
	अगर (!(__exp _t __seen)) अणु \
		/* Report with actual चिन्हितness to aव्योम weird output. */ \
		चयन (is_चिन्हित_type(__exp) * 2 + is_चिन्हित_type(__seen)) अणु \
		हाल 0: अणु \
			अचिन्हित दीर्घ दीर्घ __exp_prपूर्णांक = (uपूर्णांकptr_t)__exp; \
			अचिन्हित दीर्घ दीर्घ __seen_prपूर्णांक = (uपूर्णांकptr_t)__seen; \
			__TH_LOG("Expected %s (%llu) %s %s (%llu)", \
				 _expected_str, __exp_prपूर्णांक, #_t, \
				 _seen_str, __seen_prपूर्णांक); \
			अवरोध; \
			पूर्ण \
		हाल 1: अणु \
			अचिन्हित दीर्घ दीर्घ __exp_prपूर्णांक = (uपूर्णांकptr_t)__exp; \
			दीर्घ दीर्घ __seen_prपूर्णांक = (पूर्णांकptr_t)__seen; \
			__TH_LOG("Expected %s (%llu) %s %s (%lld)", \
				 _expected_str, __exp_prपूर्णांक, #_t, \
				 _seen_str, __seen_prपूर्णांक); \
			अवरोध; \
			पूर्ण \
		हाल 2: अणु \
			दीर्घ दीर्घ __exp_prपूर्णांक = (पूर्णांकptr_t)__exp; \
			अचिन्हित दीर्घ दीर्घ __seen_prपूर्णांक = (uपूर्णांकptr_t)__seen; \
			__TH_LOG("Expected %s (%lld) %s %s (%llu)", \
				 _expected_str, __exp_prपूर्णांक, #_t, \
				 _seen_str, __seen_prपूर्णांक); \
			अवरोध; \
			पूर्ण \
		हाल 3: अणु \
			दीर्घ दीर्घ __exp_prपूर्णांक = (पूर्णांकptr_t)__exp; \
			दीर्घ दीर्घ __seen_prपूर्णांक = (पूर्णांकptr_t)__seen; \
			__TH_LOG("Expected %s (%lld) %s %s (%lld)", \
				 _expected_str, __exp_prपूर्णांक, #_t, \
				 _seen_str, __seen_prपूर्णांक); \
			अवरोध; \
			पूर्ण \
		पूर्ण \
		_metadata->passed = 0; \
		/* Ensure the optional handler is triggered */ \
		_metadata->trigger = 1; \
	पूर्ण \
पूर्ण जबतक (0); OPTIONAL_HANDLER(_निश्चित)

#घोषणा __EXPECT_STR(_expected, _seen, _t, _निश्चित) करो अणु \
	स्थिर अक्षर *__exp = (_expected); \
	स्थिर अक्षर *__seen = (_seen); \
	अगर (_निश्चित) __INC_STEP(_metadata); \
	अगर (!(म_भेद(__exp, __seen) _t 0))  अणु \
		__TH_LOG("Expected '%s' %s '%s'.", __exp, #_t, __seen); \
		_metadata->passed = 0; \
		_metadata->trigger = 1; \
	पूर्ण \
पूर्ण जबतक (0); OPTIONAL_HANDLER(_निश्चित)

/* List helpers */
#घोषणा __LIST_APPEND(head, item) \
अणु \
	/* Circular linked list where only prev is circular. */ \
	अगर (head == शून्य) अणु \
		head = item; \
		item->next = शून्य; \
		item->prev = item; \
		वापस;	\
	पूर्ण \
	अगर (__स्थिरructor_order == _CONSTRUCTOR_ORDER_FORWARD) अणु \
		item->next = शून्य; \
		item->prev = head->prev; \
		item->prev->next = item; \
		head->prev = item; \
	पूर्ण अन्यथा अणु \
		item->next = head; \
		item->next->prev = item; \
		item->prev = item; \
		head = item; \
	पूर्ण \
पूर्ण

काष्ठा __test_results अणु
	अक्षर reason[1024];	/* Reason क्रम test result */
पूर्ण;

काष्ठा __test_metadata;
काष्ठा __fixture_variant_metadata;

/* Contains all the inक्रमmation about a fixture. */
काष्ठा __fixture_metadata अणु
	स्थिर अक्षर *name;
	काष्ठा __test_metadata *tests;
	काष्ठा __fixture_variant_metadata *variant;
	काष्ठा __fixture_metadata *prev, *next;
पूर्ण _fixture_global __attribute__((unused)) = अणु
	.name = "global",
	.prev = &_fixture_global,
पूर्ण;

अटल काष्ठा __fixture_metadata *__fixture_list = &_fixture_global;
अटल पूर्णांक __स्थिरructor_order;

#घोषणा _CONSTRUCTOR_ORDER_FORWARD   1
#घोषणा _CONSTRUCTOR_ORDER_BACKWARD -1

अटल अंतरभूत व्योम __रेजिस्टर_fixture(काष्ठा __fixture_metadata *f)
अणु
	__LIST_APPEND(__fixture_list, f);
पूर्ण

काष्ठा __fixture_variant_metadata अणु
	स्थिर अक्षर *name;
	स्थिर व्योम *data;
	काष्ठा __fixture_variant_metadata *prev, *next;
पूर्ण;

अटल अंतरभूत व्योम
__रेजिस्टर_fixture_variant(काष्ठा __fixture_metadata *f,
			   काष्ठा __fixture_variant_metadata *variant)
अणु
	__LIST_APPEND(f->variant, variant);
पूर्ण

/* Contains all the inक्रमmation क्रम test execution and status checking. */
काष्ठा __test_metadata अणु
	स्थिर अक्षर *name;
	व्योम (*fn)(काष्ठा __test_metadata *,
		   काष्ठा __fixture_variant_metadata *);
	pid_t pid;	/* pid of test when being run */
	काष्ठा __fixture_metadata *fixture;
	पूर्णांक termsig;
	पूर्णांक passed;
	पूर्णांक skip;	/* did SKIP get used? */
	पूर्णांक trigger; /* extra handler after the evaluation */
	पूर्णांक समयout;	/* seconds to रुको क्रम test समयout */
	bool समयd_out;	/* did this test समयout instead of निकासing? */
	__u8 step;
	bool no_prपूर्णांक; /* manual trigger when TH_LOG_STREAM is not available */
	काष्ठा __test_results *results;
	काष्ठा __test_metadata *prev, *next;
पूर्ण;

/*
 * Since स्थिरructors are called in reverse order, reverse the test
 * list so tests are run in source declaration order.
 * https://gcc.gnu.org/onlineकरोcs/gccपूर्णांक/Initialization.hपंचांगl
 * However, it seems not all toolchains करो this correctly, so use
 * __स्थिरructor_order to detect which direction is called first
 * and adjust list building logic to get things running in the right
 * direction.
 */
अटल अंतरभूत व्योम __रेजिस्टर_test(काष्ठा __test_metadata *t)
अणु
	__LIST_APPEND(t->fixture->tests, t);
पूर्ण

अटल अंतरभूत पूर्णांक __bail(पूर्णांक क्रम_realz, bool no_prपूर्णांक, __u8 step)
अणु
	अगर (क्रम_realz) अणु
		अगर (no_prपूर्णांक)
			_निकास(step);
		पात();
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा __test_metadata *__active_test;
अटल व्योम __समयout_handler(पूर्णांक sig, siginfo_t *info, व्योम *ucontext)
अणु
	काष्ठा __test_metadata *t = __active_test;

	/* Sanity check handler execution environment. */
	अगर (!t) अणु
		ख_लिखो(TH_LOG_STREAM,
			"# no active test in SIGALRM handler!?\n");
		पात();
	पूर्ण
	अगर (sig != SIGALRM || sig != info->si_signo) अणु
		ख_लिखो(TH_LOG_STREAM,
			"# %s: SIGALRM handler caught signal %d!?\n",
			t->name, sig != SIGALRM ? sig : info->si_signo);
		पात();
	पूर्ण

	t->समयd_out = true;
	समाप्त(t->pid, SIGKILL);
पूर्ण

व्योम __रुको_क्रम_test(काष्ठा __test_metadata *t)
अणु
	काष्ठा sigaction action = अणु
		.sa_sigaction = __समयout_handler,
		.sa_flags = SA_SIGINFO,
	पूर्ण;
	काष्ठा sigaction saved_action;
	पूर्णांक status;

	अगर (sigaction(SIGALRM, &action, &saved_action)) अणु
		t->passed = 0;
		ख_लिखो(TH_LOG_STREAM,
			"# %s: unable to install SIGALRM handler\n",
			t->name);
		वापस;
	पूर्ण
	__active_test = t;
	t->समयd_out = false;
	alarm(t->समयout);
	रुकोpid(t->pid, &status, 0);
	alarm(0);
	अगर (sigaction(SIGALRM, &saved_action, शून्य)) अणु
		t->passed = 0;
		ख_लिखो(TH_LOG_STREAM,
			"# %s: unable to uninstall SIGALRM handler\n",
			t->name);
		वापस;
	पूर्ण
	__active_test = शून्य;

	अगर (t->समयd_out) अणु
		t->passed = 0;
		ख_लिखो(TH_LOG_STREAM,
			"# %s: Test terminated by timeout\n", t->name);
	पूर्ण अन्यथा अगर (WIFEXITED(status)) अणु
		अगर (t->termsig != -1) अणु
			t->passed = 0;
			ख_लिखो(TH_LOG_STREAM,
				"# %s: Test exited normally instead of by signal (code: %d)\n",
				t->name,
				WEXITSTATUS(status));
		पूर्ण अन्यथा अणु
			चयन (WEXITSTATUS(status)) अणु
			/* Success */
			हाल 0:
				t->passed = 1;
				अवरोध;
			/* SKIP */
			हाल 255:
				t->passed = 1;
				t->skip = 1;
				अवरोध;
			/* Other failure, assume step report. */
			शेष:
				t->passed = 0;
				ख_लिखो(TH_LOG_STREAM,
					"# %s: Test failed at step #%d\n",
					t->name,
					WEXITSTATUS(status));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (WIFSIGNALED(status)) अणु
		t->passed = 0;
		अगर (WTERMSIG(status) == SIGABRT) अणु
			ख_लिखो(TH_LOG_STREAM,
				"# %s: Test terminated by assertion\n",
				t->name);
		पूर्ण अन्यथा अगर (WTERMSIG(status) == t->termsig) अणु
			t->passed = 1;
		पूर्ण अन्यथा अणु
			ख_लिखो(TH_LOG_STREAM,
				"# %s: Test terminated unexpectedly by signal %d\n",
				t->name,
				WTERMSIG(status));
		पूर्ण
	पूर्ण अन्यथा अणु
		ख_लिखो(TH_LOG_STREAM,
			"# %s: Test ended in some other way [%u]\n",
			t->name,
			status);
	पूर्ण
पूर्ण

व्योम __run_test(काष्ठा __fixture_metadata *f,
		काष्ठा __fixture_variant_metadata *variant,
		काष्ठा __test_metadata *t)
अणु
	/* reset test काष्ठा */
	t->passed = 1;
	t->skip = 0;
	t->trigger = 0;
	t->step = 0;
	t->no_prपूर्णांक = 0;
	स_रखो(t->results->reason, 0, माप(t->results->reason));

	ksft_prपूर्णांक_msg(" RUN           %s%s%s.%s ...\n",
	       f->name, variant->name[0] ? "." : "", variant->name, t->name);

	/* Make sure output buffers are flushed beक्रमe विभाजन */
	ख_साफ(मानक_निकास);
	ख_साफ(मानक_त्रुटि);

	t->pid = विभाजन();
	अगर (t->pid < 0) अणु
		ksft_prपूर्णांक_msg("ERROR SPAWNING TEST CHILD\n");
		t->passed = 0;
	पूर्ण अन्यथा अगर (t->pid == 0) अणु
		t->fn(t, variant);
		अगर (t->skip)
			_निकास(255);
		/* Pass is निकास 0 */
		अगर (t->passed)
			_निकास(0);
		/* Something अन्यथा happened, report the step. */
		_निकास(t->step);
	पूर्ण अन्यथा अणु
		__रुको_क्रम_test(t);
	पूर्ण
	ksft_prपूर्णांक_msg("         %4s  %s%s%s.%s\n", t->passed ? "OK" : "FAIL",
	       f->name, variant->name[0] ? "." : "", variant->name, t->name);

	अगर (t->skip)
		ksft_test_result_skip("%s\n", t->results->reason[0] ?
					t->results->reason : "unknown");
	अन्यथा
		ksft_test_result(t->passed, "%s%s%s.%s\n",
			f->name, variant->name[0] ? "." : "", variant->name, t->name);
पूर्ण

अटल पूर्णांक test_harness_run(पूर्णांक __attribute__((unused)) argc,
			    अक्षर __attribute__((unused)) **argv)
अणु
	काष्ठा __fixture_variant_metadata no_variant = अणु .name = "", पूर्ण;
	काष्ठा __fixture_variant_metadata *v;
	काष्ठा __fixture_metadata *f;
	काष्ठा __test_results *results;
	काष्ठा __test_metadata *t;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक हाल_count = 0, test_count = 0;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक pass_count = 0;

	क्रम (f = __fixture_list; f; f = f->next) अणु
		क्रम (v = f->variant ?: &no_variant; v; v = v->next) अणु
			हाल_count++;
			क्रम (t = f->tests; t; t = t->next)
				test_count++;
		पूर्ण
	पूर्ण

	results = mmap(शून्य, माप(*results), PROT_READ | PROT_WRITE,
		       MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	ksft_prपूर्णांक_header();
	ksft_set_plan(test_count);
	ksft_prपूर्णांक_msg("Starting %u tests from %u test cases.\n",
	       test_count, हाल_count);
	क्रम (f = __fixture_list; f; f = f->next) अणु
		क्रम (v = f->variant ?: &no_variant; v; v = v->next) अणु
			क्रम (t = f->tests; t; t = t->next) अणु
				count++;
				t->results = results;
				__run_test(f, v, t);
				t->results = शून्य;
				अगर (t->passed)
					pass_count++;
				अन्यथा
					ret = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	munmap(results, माप(*results));

	ksft_prपूर्णांक_msg("%s: %u / %u tests passed.\n", ret ? "FAILED" : "PASSED",
			pass_count, count);
	ksft_निकास(ret == 0);

	/* unreachable */
	वापस KSFT_FAIL;
पूर्ण

अटल व्योम __attribute__((स्थिरructor)) __स्थिरructor_order_first(व्योम)
अणु
	अगर (!__स्थिरructor_order)
		__स्थिरructor_order = _CONSTRUCTOR_ORDER_FORWARD;
पूर्ण

#पूर्ण_अगर  /* __KSELFTEST_HARNESS_H */
