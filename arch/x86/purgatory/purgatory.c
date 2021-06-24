<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * purgatory: Runs between two kernels
 *
 * Copyright (C) 2014 Red Hat Inc.
 *
 * Author:
 *       Vivek Goyal <vgoyal@redhat.com>
 */

#समावेश <linux/bug.h>
#समावेश <crypto/sha2.h>
#समावेश <यंत्र/purgatory.h>

#समावेश "../boot/string.h"

u8 purgatory_sha256_digest[SHA256_DIGEST_SIZE] __section(".kexec-purgatory");

काष्ठा kexec_sha_region purgatory_sha_regions[KEXEC_SEGMENT_MAX] __section(".kexec-purgatory");

अटल पूर्णांक verअगरy_sha256_digest(व्योम)
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

व्योम purgatory(व्योम)
अणु
	पूर्णांक ret;

	ret = verअगरy_sha256_digest();
	अगर (ret) अणु
		/* loop क्रमever */
		क्रम (;;)
			;
	पूर्ण
पूर्ण

/*
 * Defined in order to reuse स_नकल() and स_रखो() from
 * arch/x86/boot/compressed/string.c
 */
व्योम warn(स्थिर अक्षर *msg) अणुपूर्ण
