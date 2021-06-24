<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <kunit/test.h>

#समावेश "protocol.h"

काष्ठा test_हाल अणु
	अक्षर *key;
	अक्षर *msg;
	अक्षर *result;
पूर्ण;

/* we can't reuse RFC 4231 test vectors, as we have स्थिरraपूर्णांक on the
 * input and key size.
 */
अटल काष्ठा test_हाल tests[] = अणु
	अणु
		.key = "0b0b0b0b0b0b0b0b",
		.msg = "48692054",
		.result = "8385e24fb4235ac37556b6b886db106284a1da671699f46db1f235ec622dcafa",
	पूर्ण,
	अणु
		.key = "aaaaaaaaaaaaaaaa",
		.msg = "dddddddd",
		.result = "2c5e219164ff1dca1c4a92318d847bb6b9d44492984e1eb71aff9022f71046e9",
	पूर्ण,
	अणु
		.key = "0102030405060708",
		.msg = "cdcdcdcd",
		.result = "e73b9ba9969969cefb04aa0d6df18ec2fcc075b6f23b4d8c4da736a5dbbc6e7d",
	पूर्ण,
पूर्ण;

अटल व्योम mptcp_crypto_test_basic(काष्ठा kunit *test)
अणु
	अक्षर hmac[32], hmac_hex[65];
	u32 nonce1, nonce2;
	u64 key1, key2;
	u8 msg[8];
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(tests); ++i) अणु
		/* mptcp hmap will convert to be beक्रमe computing the hmac */
		key1 = be64_to_cpu(*((__be64 *)&tests[i].key[0]));
		key2 = be64_to_cpu(*((__be64 *)&tests[i].key[8]));
		nonce1 = be32_to_cpu(*((__be32 *)&tests[i].msg[0]));
		nonce2 = be32_to_cpu(*((__be32 *)&tests[i].msg[4]));

		put_unaligned_be32(nonce1, &msg[0]);
		put_unaligned_be32(nonce2, &msg[4]);

		mptcp_crypto_hmac_sha(key1, key2, msg, 8, hmac);
		क्रम (j = 0; j < 32; ++j)
			प्र_लिखो(&hmac_hex[j << 1], "%02x", hmac[j] & 0xff);
		hmac_hex[64] = 0;

		KUNIT_EXPECT_STREQ(test, &hmac_hex[0], tests[i].result);
	पूर्ण
पूर्ण

अटल काष्ठा kunit_हाल mptcp_crypto_test_हालs[] = अणु
	KUNIT_CASE(mptcp_crypto_test_basic),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite mptcp_crypto_suite = अणु
	.name = "mptcp-crypto",
	.test_हालs = mptcp_crypto_test_हालs,
पूर्ण;

kunit_test_suite(mptcp_crypto_suite);

MODULE_LICENSE("GPL");
