<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Purgatory code running between two kernels.
 *
 * Copyright IBM Corp. 2018
 *
 * Author(s): Philipp Ruकरो <pruकरो@linux.vnet.ibm.com>
 */

#समावेश <linux/kexec.h>
#समावेश <linux/माला.स>
#समावेश <crypto/sha2.h>
#समावेश <यंत्र/purgatory.h>

पूर्णांक verअगरy_sha256_digest(व्योम)
अणु
	काष्ठा kexec_sha_region *ptr, *end;
	u8 digest[SHA256_DIGEST_SIZE];
	काष्ठा sha256_state sctx;

	sha256_init(&sctx);
	end = purgatory_sha_regions + ARRAY_SIZE(purgatory_sha_regions);

	क्रम (ptr = purgatory_sha_regions; ptr < end; ptr++)
		sha256_update(&sctx, (uपूर्णांक8_t *)(ptr->start), ptr->len);

	sha256_final(&sctx, digest);

	अगर (स_भेद(digest, purgatory_sha256_digest, माप(digest)))
		वापस 1;

	वापस 0;
पूर्ण
