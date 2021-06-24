<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP cryptographic functions
 * Copyright (c) 2017 - 2019, Intel Corporation.
 *
 * Note: This code is based on mptcp_ctrl.c, mptcp_ipv4.c, and
 *       mptcp_ipv6 from multipath-tcp.org, authored by:
 *
 *       Sथऊbastien Barrथऊ <sebastien.barre@uclouvain.be>
 *       Christoph Paasch <christoph.paasch@uclouvain.be>
 *       Jaakko Korkeaniemi <jaakko.korkeaniemi@aalto.fi>
 *       Gregory Detal <gregory.detal@uclouvain.be>
 *       Fabien Duchथऋne <fabien.duchene@uclouvain.be>
 *       Andreas Seelinger <Andreas.Seelinger@rwth-aachen.de>
 *       Lavkesh Lahngir <lavkesh51@gmail.com>
 *       Andreas Ripke <ripke@neclab.eu>
 *       Vlad Dogaru <vlad.करोgaru@पूर्णांकel.com>
 *       Octavian Purdila <octavian.purdila@पूर्णांकel.com>
 *       John Ronan <jronan@tssg.org>
 *       Catalin Nicutar <catalin.nicutar@gmail.com>
 *       Bअक्रमon Heller <bअक्रमonh@stanक्रमd.edu>
 */

#समावेश <linux/kernel.h>
#समावेश <crypto/sha2.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "protocol.h"

#घोषणा SHA256_DIGEST_WORDS (SHA256_DIGEST_SIZE / 4)

व्योम mptcp_crypto_key_sha(u64 key, u32 *token, u64 *idsn)
अणु
	__be32 mptcp_hashed_key[SHA256_DIGEST_WORDS];
	__be64 input = cpu_to_be64(key);

	sha256((__क्रमce u8 *)&input, माप(input), (u8 *)mptcp_hashed_key);

	अगर (token)
		*token = be32_to_cpu(mptcp_hashed_key[0]);
	अगर (idsn)
		*idsn = be64_to_cpu(*((__be64 *)&mptcp_hashed_key[6]));
पूर्ण

व्योम mptcp_crypto_hmac_sha(u64 key1, u64 key2, u8 *msg, पूर्णांक len, व्योम *hmac)
अणु
	u8 input[SHA256_BLOCK_SIZE + SHA256_DIGEST_SIZE];
	u8 key1be[8];
	u8 key2be[8];
	पूर्णांक i;

	अगर (WARN_ON_ONCE(len > SHA256_DIGEST_SIZE))
		len = SHA256_DIGEST_SIZE;

	put_unaligned_be64(key1, key1be);
	put_unaligned_be64(key2, key2be);

	/* Generate key xored with ipad */
	स_रखो(input, 0x36, SHA256_BLOCK_SIZE);
	क्रम (i = 0; i < 8; i++)
		input[i] ^= key1be[i];
	क्रम (i = 0; i < 8; i++)
		input[i + 8] ^= key2be[i];

	स_नकल(&input[SHA256_BLOCK_SIZE], msg, len);

	/* emit sha256(K1 || msg) on the second input block, so we can
	 * reuse 'input' क्रम the last hashing
	 */
	sha256(input, SHA256_BLOCK_SIZE + len, &input[SHA256_BLOCK_SIZE]);

	/* Prepare second part of hmac */
	स_रखो(input, 0x5C, SHA256_BLOCK_SIZE);
	क्रम (i = 0; i < 8; i++)
		input[i] ^= key1be[i];
	क्रम (i = 0; i < 8; i++)
		input[i + 8] ^= key2be[i];

	sha256(input, SHA256_BLOCK_SIZE + SHA256_DIGEST_SIZE, hmac);
पूर्ण

#अगर IS_MODULE(CONFIG_MPTCP_KUNIT_TEST)
EXPORT_SYMBOL_GPL(mptcp_crypto_hmac_sha);
#पूर्ण_अगर
