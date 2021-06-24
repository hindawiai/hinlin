<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <byteswap.h>
#समावेश "utils.h"
#समावेश "subunit.h"

#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#घोषणा cpu_to_be32(x)		bswap_32(x)
#घोषणा be32_to_cpu(x)		bswap_32(x)
#घोषणा be16_to_cpup(x)		bswap_16(*x)
#घोषणा cpu_to_be64(x)		bswap_64(x)
#अन्यथा
#घोषणा cpu_to_be32(x)		(x)
#घोषणा be32_to_cpu(x)		(x)
#घोषणा be16_to_cpup(x)		(*x)
#घोषणा cpu_to_be64(x)		(x)
#पूर्ण_अगर

#समावेश "vphn.c"

अटल काष्ठा test अणु
	अक्षर *descr;
	दीर्घ input[VPHN_REGISTER_COUNT];
	u32 expected[VPHN_ASSOC_बफ_मानE];
पूर्ण all_tests[] = अणु
	अणु
		"vphn: no data",
		अणु
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
		पूर्ण,
		अणु
			0x00000000
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 1 x 16-bit value",
		अणु
			0x8001ffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
		पूर्ण,
		अणु
			0x00000001,
			0x00000001
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 2 x 16-bit values",
		अणु
			0x80018002ffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
		पूर्ण,
		अणु
			0x00000002,
			0x00000001,
			0x00000002
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 3 x 16-bit values",
		अणु
			0x800180028003ffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
		पूर्ण,
		अणु
			0x00000003,
			0x00000001,
			0x00000002,
			0x00000003
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 4 x 16-bit values",
		अणु
			0x8001800280038004,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
		पूर्ण,
		अणु
			0x00000004,
			0x00000001,
			0x00000002,
			0x00000003,
			0x00000004
		पूर्ण
	पूर्ण,
	अणु
		/* Parsing the next 16-bit value out of the next 64-bit input
		 * value.
		 */
		"vphn: 5 x 16-bit values",
		अणु
			0x8001800280038004,
			0x8005ffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
		पूर्ण,
		अणु
			0x00000005,
			0x00000001,
			0x00000002,
			0x00000003,
			0x00000004,
			0x00000005
		पूर्ण
	पूर्ण,
	अणु
		/* Parse at most 6 x 64-bit input values */
		"vphn: 24 x 16-bit values",
		अणु
			0x8001800280038004,
			0x8005800680078008,
			0x8009800a800b800c,
			0x800d800e800f8010,
			0x8011801280138014,
			0x8015801680178018
		पूर्ण,
		अणु
			0x00000018,
			0x00000001,
			0x00000002,
			0x00000003,
			0x00000004,
			0x00000005,
			0x00000006,
			0x00000007,
			0x00000008,
			0x00000009,
			0x0000000a,
			0x0000000b,
			0x0000000c,
			0x0000000d,
			0x0000000e,
			0x0000000f,
			0x00000010,
			0x00000011,
			0x00000012,
			0x00000013,
			0x00000014,
			0x00000015,
			0x00000016,
			0x00000017,
			0x00000018
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 1 x 32-bit value",
		अणु
			0x00000001ffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
		पूर्ण,
		अणु
			0x00000001,
			0x00000001
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 2 x 32-bit values",
		अणु
			0x0000000100000002,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
		पूर्ण,
		अणु
			0x00000002,
			0x00000001,
			0x00000002
		पूर्ण
	पूर्ण,
	अणु
		/* Parsing the next 32-bit value out of the next 64-bit input
		 * value.
		 */
		"vphn: 3 x 32-bit values",
		अणु
			0x0000000100000002,
			0x00000003ffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
		पूर्ण,
		अणु
			0x00000003,
			0x00000001,
			0x00000002,
			0x00000003
		पूर्ण
	पूर्ण,
	अणु
		/* Parse at most 6 x 64-bit input values */
		"vphn: 12 x 32-bit values",
		अणु
			0x0000000100000002,
			0x0000000300000004,
			0x0000000500000006,
			0x0000000700000008,
			0x000000090000000a,
			0x0000000b0000000c
		पूर्ण,
		अणु
			0x0000000c,
			0x00000001,
			0x00000002,
			0x00000003,
			0x00000004,
			0x00000005,
			0x00000006,
			0x00000007,
			0x00000008,
			0x00000009,
			0x0000000a,
			0x0000000b,
			0x0000000c
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 16-bit value followed by 32-bit value",
		अणु
			0x800100000002ffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
		पूर्ण,
		अणु
			0x00000002,
			0x00000001,
			0x00000002
		पूर्ण
	पूर्ण,
	अणु
		"vphn: 32-bit value followed by 16-bit value",
		अणु
			0x000000018002ffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
		पूर्ण,
		अणु
			0x00000002,
			0x00000001,
			0x00000002
		पूर्ण
	पूर्ण,
	अणु
		/* Parse a 32-bit value split accross two consecutives 64-bit
		 * input values.
		 */
		"vphn: 16-bit value followed by 2 x 32-bit values",
		अणु
			0x8001000000020000,
			0x0003ffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
		पूर्ण,
		अणु
			0x00000003,
			0x00000001,
			0x00000002,
			0x00000003,
			0x00000004,
			0x00000005
		पूर्ण
	पूर्ण,
	अणु
		/* The lower bits in 0x0001ffff करोn't get mixed up with the
		 * 0xffff terminator.
		 */
		"vphn: 32-bit value has all ones in 16 lower bits",
		अणु
			0x0001ffff80028003,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
		पूर्ण,
		अणु
			0x00000003,
			0x0001ffff,
			0x00000002,
			0x00000003
		पूर्ण
	पूर्ण,
	अणु
		/* The following input करोesn't follow the specअगरication.
		 */
		"vphn: last 32-bit value is truncated",
		अणु
			0x0000000100000002,
			0x0000000300000004,
			0x0000000500000006,
			0x0000000700000008,
			0x000000090000000a,
			0x0000000b800c2bad
		पूर्ण,
		अणु
			0x0000000c,
			0x00000001,
			0x00000002,
			0x00000003,
			0x00000004,
			0x00000005,
			0x00000006,
			0x00000007,
			0x00000008,
			0x00000009,
			0x0000000a,
			0x0000000b,
			0x0000000c
		पूर्ण
	पूर्ण,
	अणु
		"vphn: garbage after terminator",
		अणु
			0xffff2bad2bad2bad,
			0x2bad2bad2bad2bad,
			0x2bad2bad2bad2bad,
			0x2bad2bad2bad2bad,
			0x2bad2bad2bad2bad,
			0x2bad2bad2bad2bad
		पूर्ण,
		अणु
			0x00000000
		पूर्ण
	पूर्ण,
	अणु
		शून्य
	पूर्ण
पूर्ण;

अटल पूर्णांक test_one(काष्ठा test *test)
अणु
	__be32 output[VPHN_ASSOC_बफ_मानE] = अणु 0 पूर्ण;
	पूर्णांक i, len;

	vphn_unpack_associativity(test->input, output);

	len = be32_to_cpu(output[0]);
	अगर (len != test->expected[0]) अणु
		म_लिखो("expected %d elements, got %d\n", test->expected[0],
		       len);
		वापस 1;
	पूर्ण

	क्रम (i = 1; i < len; i++) अणु
		u32 val = be32_to_cpu(output[i]);
		अगर (val != test->expected[i]) अणु
			म_लिखो("element #%d is 0x%x, should be 0x%x\n", i, val,
			       test->expected[i]);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_vphn(व्योम)
अणु
	अटल काष्ठा test *test;

	क्रम (test = all_tests; test->descr; test++) अणु
		पूर्णांक ret;

		ret = test_one(test);
		test_finish(test->descr, ret);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	वापस test_harness(test_vphn, "test-vphn");
पूर्ण
