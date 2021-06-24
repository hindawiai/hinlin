<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * geniv: IV generation
 *
 * Copyright (c) 2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_INTERNAL_GENIV_H
#घोषणा _CRYPTO_INTERNAL_GENIV_H

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

काष्ठा aead_geniv_ctx अणु
	spinlock_t lock;
	काष्ठा crypto_aead *child;
	काष्ठा crypto_sync_skcipher *sknull;
	u8 salt[] __attribute__ ((aligned(__alignof__(u32))));
पूर्ण;

काष्ठा aead_instance *aead_geniv_alloc(काष्ठा crypto_ढाँचा *पंचांगpl,
				       काष्ठा rtattr **tb);
पूर्णांक aead_init_geniv(काष्ठा crypto_aead *tfm);
व्योम aead_निकास_geniv(काष्ठा crypto_aead *tfm);

#पूर्ण_अगर	/* _CRYPTO_INTERNAL_GENIV_H */
