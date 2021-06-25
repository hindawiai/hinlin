<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KUnit test of ext4 inode that verअगरy the seconds part of [a/c/m]
 * बारtamps in ext4 inode काष्ठाs are decoded correctly.
 */

#समावेश <kunit/test.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय64.h>

#समावेश "ext4.h"

/*
 * For स्थिरructing the nonnegative बारtamp lower bound value.
 * binary: 00000000 00000000 00000000 00000000
 */
#घोषणा LOWER_MSB_0 0L
/*
 * For स्थिरructing the nonnegative बारtamp upper bound value.
 * binary: 01111111 11111111 11111111 11111111
 *
 */
#घोषणा UPPER_MSB_0 0x7fffffffL
/*
 * For स्थिरructing the negative बारtamp lower bound value.
 * binary: 10000000 00000000 00000000 00000000
 */
#घोषणा LOWER_MSB_1 (-(UPPER_MSB_0) - 1L)  /* aव्योम overflow */
/*
 * For स्थिरructing the negative बारtamp upper bound value.
 * binary: 11111111 11111111 11111111 11111111
 */
#घोषणा UPPER_MSB_1 (-1L)
/*
 * Upper bound क्रम nanoseconds value supported by the encoding.
 * binary: 00111111 11111111 11111111 11111111
 */
#घोषणा MAX_न_अंकOSECONDS ((1L << 30) - 1)

#घोषणा CASE_NAME_FORMAT "%s: msb:%x lower_bound:%x extra_bits: %x"

#घोषणा LOWER_BOUND_NEG_NO_EXTRA_BITS_CASE\
	"1901-12-13 Lower bound of 32bit < 0 timestamp, no extra bits"
#घोषणा UPPER_BOUND_NEG_NO_EXTRA_BITS_CASE\
	"1969-12-31 Upper bound of 32bit < 0 timestamp, no extra bits"
#घोषणा LOWER_BOUND_NONNEG_NO_EXTRA_BITS_CASE\
	"1970-01-01 Lower bound of 32bit >=0 timestamp, no extra bits"
#घोषणा UPPER_BOUND_NONNEG_NO_EXTRA_BITS_CASE\
	"2038-01-19 Upper bound of 32bit >=0 timestamp, no extra bits"
#घोषणा LOWER_BOUND_NEG_LO_1_CASE\
	"2038-01-19 Lower bound of 32bit <0 timestamp, lo extra sec bit on"
#घोषणा UPPER_BOUND_NEG_LO_1_CASE\
	"2106-02-07 Upper bound of 32bit <0 timestamp, lo extra sec bit on"
#घोषणा LOWER_BOUND_NONNEG_LO_1_CASE\
	"2106-02-07 Lower bound of 32bit >=0 timestamp, lo extra sec bit on"
#घोषणा UPPER_BOUND_NONNEG_LO_1_CASE\
	"2174-02-25 Upper bound of 32bit >=0 timestamp, lo extra sec bit on"
#घोषणा LOWER_BOUND_NEG_HI_1_CASE\
	"2174-02-25 Lower bound of 32bit <0 timestamp, hi extra sec bit on"
#घोषणा UPPER_BOUND_NEG_HI_1_CASE\
	"2242-03-16 Upper bound of 32bit <0 timestamp, hi extra sec bit on"
#घोषणा LOWER_BOUND_NONNEG_HI_1_CASE\
	"2242-03-16 Lower bound of 32bit >=0 timestamp, hi extra sec bit on"
#घोषणा UPPER_BOUND_NONNEG_HI_1_CASE\
	"2310-04-04 Upper bound of 32bit >=0 timestamp, hi extra sec bit on"
#घोषणा UPPER_BOUND_NONNEG_HI_1_NS_1_CASE\
	"2310-04-04 Upper bound of 32bit>=0 timestamp, hi extra sec bit 1. 1 ns"
#घोषणा LOWER_BOUND_NONNEG_HI_1_NS_MAX_CASE\
	"2378-04-22 Lower bound of 32bit>= timestamp. Extra sec bits 1. Max ns"
#घोषणा LOWER_BOUND_NONNEG_EXTRA_BITS_1_CASE\
	"2378-04-22 Lower bound of 32bit >=0 timestamp. All extra sec bits on"
#घोषणा UPPER_BOUND_NONNEG_EXTRA_BITS_1_CASE\
	"2446-05-10 Upper bound of 32bit >=0 timestamp. All extra sec bits on"

काष्ठा बारtamp_expectation अणु
	स्थिर अक्षर *test_हाल_name;
	काष्ठा बारpec64 expected;
	u32 extra_bits;
	bool msb_set;
	bool lower_bound;
पूर्ण;

अटल स्थिर काष्ठा बारtamp_expectation test_data[] = अणु
	अणु
		.test_हाल_name = LOWER_BOUND_NEG_NO_EXTRA_BITS_CASE,
		.msb_set = true,
		.lower_bound = true,
		.extra_bits = 0,
		.expected = अणु.tv_sec = -0x80000000LL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NEG_NO_EXTRA_BITS_CASE,
		.msb_set = true,
		.lower_bound = false,
		.extra_bits = 0,
		.expected = अणु.tv_sec = -1LL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = LOWER_BOUND_NONNEG_NO_EXTRA_BITS_CASE,
		.msb_set = false,
		.lower_bound = true,
		.extra_bits = 0,
		.expected = अणु0LL, 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NONNEG_NO_EXTRA_BITS_CASE,
		.msb_set = false,
		.lower_bound = false,
		.extra_bits = 0,
		.expected = अणु.tv_sec = 0x7fffffffLL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = LOWER_BOUND_NEG_LO_1_CASE,
		.msb_set = true,
		.lower_bound = true,
		.extra_bits = 1,
		.expected = अणु.tv_sec = 0x80000000LL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NEG_LO_1_CASE,
		.msb_set = true,
		.lower_bound = false,
		.extra_bits = 1,
		.expected = अणु.tv_sec = 0xffffffffLL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = LOWER_BOUND_NONNEG_LO_1_CASE,
		.msb_set = false,
		.lower_bound = true,
		.extra_bits = 1,
		.expected = अणु.tv_sec = 0x100000000LL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NONNEG_LO_1_CASE,
		.msb_set = false,
		.lower_bound = false,
		.extra_bits = 1,
		.expected = अणु.tv_sec = 0x17fffffffLL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = LOWER_BOUND_NEG_HI_1_CASE,
		.msb_set = true,
		.lower_bound = true,
		.extra_bits =  2,
		.expected = अणु.tv_sec = 0x180000000LL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NEG_HI_1_CASE,
		.msb_set = true,
		.lower_bound = false,
		.extra_bits = 2,
		.expected = अणु.tv_sec = 0x1ffffffffLL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = LOWER_BOUND_NONNEG_HI_1_CASE,
		.msb_set = false,
		.lower_bound = true,
		.extra_bits = 2,
		.expected = अणु.tv_sec = 0x200000000LL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NONNEG_HI_1_CASE,
		.msb_set = false,
		.lower_bound = false,
		.extra_bits = 2,
		.expected = अणु.tv_sec = 0x27fffffffLL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NONNEG_HI_1_NS_1_CASE,
		.msb_set = false,
		.lower_bound = false,
		.extra_bits = 6,
		.expected = अणु.tv_sec = 0x27fffffffLL, .tv_nsec = 1Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = LOWER_BOUND_NONNEG_HI_1_NS_MAX_CASE,
		.msb_set = false,
		.lower_bound = true,
		.extra_bits = 0xFFFFFFFF,
		.expected = अणु.tv_sec = 0x300000000LL,
			     .tv_nsec = MAX_न_अंकOSECONDSपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = LOWER_BOUND_NONNEG_EXTRA_BITS_1_CASE,
		.msb_set = false,
		.lower_bound = true,
		.extra_bits = 3,
		.expected = अणु.tv_sec = 0x300000000LL, .tv_nsec = 0Lपूर्ण,
	पूर्ण,

	अणु
		.test_हाल_name = UPPER_BOUND_NONNEG_EXTRA_BITS_1_CASE,
		.msb_set = false,
		.lower_bound = false,
		.extra_bits = 3,
		.expected = अणु.tv_sec = 0x37fffffffLL, .tv_nsec = 0Lपूर्ण,
	पूर्ण
पूर्ण;

अटल व्योम बारtamp_expectation_to_desc(स्थिर काष्ठा बारtamp_expectation *t,
					  अक्षर *desc)
अणु
	strscpy(desc, t->test_हाल_name, KUNIT_PARAM_DESC_SIZE);
पूर्ण

KUNIT_ARRAY_PARAM(ext4_inode, test_data, बारtamp_expectation_to_desc);

अटल समय64_t get_32bit_समय(स्थिर काष्ठा बारtamp_expectation * स्थिर test)
अणु
	अगर (test->msb_set) अणु
		अगर (test->lower_bound)
			वापस LOWER_MSB_1;

		वापस UPPER_MSB_1;
	पूर्ण

	अगर (test->lower_bound)
		वापस LOWER_MSB_0;
	वापस UPPER_MSB_0;
पूर्ण


/*
 *  Test data is derived from the table in the Inode Timestamps section of
 *  Documentation/fileप्रणालीs/ext4/inodes.rst.
 */
अटल व्योम inode_test_xबारtamp_decoding(काष्ठा kunit *test)
अणु
	काष्ठा बारpec64 बारtamp;

	काष्ठा बारtamp_expectation *test_param =
			(काष्ठा बारtamp_expectation *)(test->param_value);

	बारtamp.tv_sec = get_32bit_समय(test_param);
	ext4_decode_extra_समय(&बारtamp,
			       cpu_to_le32(test_param->extra_bits));

	KUNIT_EXPECT_EQ_MSG(test,
			    test_param->expected.tv_sec,
			    बारtamp.tv_sec,
			    CASE_NAME_FORMAT,
			    test_param->test_हाल_name,
			    test_param->msb_set,
			    test_param->lower_bound,
			    test_param->extra_bits);
	KUNIT_EXPECT_EQ_MSG(test,
			    test_param->expected.tv_nsec,
			    बारtamp.tv_nsec,
			    CASE_NAME_FORMAT,
			    test_param->test_हाल_name,
			    test_param->msb_set,
			    test_param->lower_bound,
			    test_param->extra_bits);
पूर्ण

अटल काष्ठा kunit_हाल ext4_inode_test_हालs[] = अणु
	KUNIT_CASE_PARAM(inode_test_xबारtamp_decoding, ext4_inode_gen_params),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite ext4_inode_test_suite = अणु
	.name = "ext4_inode_test",
	.test_हालs = ext4_inode_test_हालs,
पूर्ण;

kunit_test_suites(&ext4_inode_test_suite);

MODULE_LICENSE("GPL v2");
