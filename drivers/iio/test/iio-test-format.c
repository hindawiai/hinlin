<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Unit tests क्रम IIO क्रमmatting functions
 *
 * Copyright (c) 2020 Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <kunit/test.h>
#समावेश <linux/iio/iपन.स>

#घोषणा IIO_TEST_FORMAT_EXPECT_EQ(_test, _buf, _ret, _val) करो अणु \
		KUNIT_EXPECT_EQ(_test, (पूर्णांक)म_माप(_buf), _ret); \
		KUNIT_EXPECT_STREQ(_test, (_buf), (_val)); \
	पूर्ण जबतक (0)

अटल व्योम iio_test_iio_क्रमmat_value_पूर्णांकeger(काष्ठा kunit *test)
अणु
	अक्षर *buf = kunit_kदो_स्मृति(test, PAGE_SIZE, GFP_KERNEL);
	पूर्णांक val;
	पूर्णांक ret;

	val = 42;
	ret = iio_क्रमmat_value(buf, IIO_VAL_INT, 1, &val);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "42\n");

	val = -23;
	ret = iio_क्रमmat_value(buf, IIO_VAL_INT, 1, &val);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-23\n");

	val = 0;
	ret = iio_क्रमmat_value(buf, IIO_VAL_INT, 1, &val);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0\n");

	val = पूर्णांक_उच्च;
	ret = iio_क्रमmat_value(buf, IIO_VAL_INT, 1, &val);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "2147483647\n");

	val = पूर्णांक_न्यून;
	ret = iio_क्रमmat_value(buf, IIO_VAL_INT, 1, &val);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-2147483648\n");
पूर्ण

अटल व्योम iio_test_iio_क्रमmat_value_fixedpoपूर्णांक(काष्ठा kunit *test)
अणु
	अक्षर *buf = kunit_kदो_स्मृति(test, PAGE_SIZE, GFP_KERNEL);
	पूर्णांक values[2];
	पूर्णांक ret;

	/* positive >= 1 */
	values[0] = 1;
	values[1] = 10;

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "1.000010\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO_DB, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "1.000010 dB\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_न_अंकO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "1.000000010\n");

	/* positive < 1 */
	values[0] = 0;
	values[1] = 12;

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0.000012\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO_DB, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0.000012 dB\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_न_अंकO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0.000000012\n");

	/* negative <= -1 */
	values[0] = -1;
	values[1] = 10;

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-1.000010\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO_DB, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-1.000010 dB\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_न_अंकO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-1.000000010\n");

	/* negative > -1 */
	values[0] = 0;
	values[1] = -123;
	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-0.000123\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO_DB, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-0.000123 dB\n");

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_न_अंकO, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-0.000000123\n");
पूर्ण

अटल व्योम iio_test_iio_क्रमmat_value_fractional(काष्ठा kunit *test)
अणु
	अक्षर *buf = kunit_kदो_स्मृति(test, PAGE_SIZE, GFP_KERNEL);
	पूर्णांक values[2];
	पूर्णांक ret;

	/* positive < 1 */
	values[0] = 1;
	values[1] = 10;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0.100000000\n");

	/* positive >= 1 */
	values[0] = 100;
	values[1] = 3;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "33.333333333\n");

	/* negative > -1 */
	values[0] = -1;
	values[1] = 1000000000;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-0.000000001\n");

	/* negative <= -1 */
	values[0] = -200;
	values[1] = 3;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-66.666666666\n");

	/* Zero */
	values[0] = 0;
	values[1] = -10;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0.000000000\n");
पूर्ण

अटल व्योम iio_test_iio_क्रमmat_value_fractional_log2(काष्ठा kunit *test)
अणु
	अक्षर *buf = kunit_kदो_स्मृति(test, PAGE_SIZE, GFP_KERNEL);
	पूर्णांक values[2];
	पूर्णांक ret;

	/* positive < 1 */
	values[0] = 123;
	values[1] = 10;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL_LOG2, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0.120117187\n");

	/* positive >= 1 */
	values[0] = 1234567;
	values[1] = 10;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL_LOG2, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "1205.631835937\n");

	/* negative > -1 */
	values[0] = -123;
	values[1] = 10;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL_LOG2, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-0.120117187\n");

	/* negative <= -1 */
	values[0] = -1234567;
	values[1] = 10;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL_LOG2, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "-1205.631835937\n");

	/* Zero */
	values[0] = 0;
	values[1] = 10;
	ret = iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL_LOG2, 2, values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "0.000000000\n");
पूर्ण

अटल व्योम iio_test_iio_क्रमmat_value_multiple(काष्ठा kunit *test)
अणु
	अक्षर *buf = kunit_kदो_स्मृति(test, PAGE_SIZE, GFP_KERNEL);
	पूर्णांक values[] = अणु1, -2, 3, -4, 5पूर्ण;
	पूर्णांक ret;

	ret = iio_क्रमmat_value(buf, IIO_VAL_INT_MULTIPLE,
			       ARRAY_SIZE(values), values);
	IIO_TEST_FORMAT_EXPECT_EQ(test, buf, ret, "1 -2 3 -4 5 \n");
पूर्ण

अटल काष्ठा kunit_हाल iio_क्रमmat_test_हालs[] = अणु
		KUNIT_CASE(iio_test_iio_क्रमmat_value_पूर्णांकeger),
		KUNIT_CASE(iio_test_iio_क्रमmat_value_fixedpoपूर्णांक),
		KUNIT_CASE(iio_test_iio_क्रमmat_value_fractional),
		KUNIT_CASE(iio_test_iio_क्रमmat_value_fractional_log2),
		KUNIT_CASE(iio_test_iio_क्रमmat_value_multiple),
		अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite iio_क्रमmat_test_suite = अणु
	.name = "iio-format",
	.test_हालs = iio_क्रमmat_test_हालs,
पूर्ण;
kunit_test_suite(iio_क्रमmat_test_suite);
