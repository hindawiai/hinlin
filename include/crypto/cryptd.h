<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Software async crypto daemon
 *
 * Added AEAD support to cryptd.
 *    Authors: Tadeusz Struk (tadeusz.struk@पूर्णांकel.com)
 *             Adrian Hoban <adrian.hoban@पूर्णांकel.com>
 *             Gabriele Paoloni <gabriele.paoloni@पूर्णांकel.com>
 *             Aidan O'Mahony (aidan.o.mahony@पूर्णांकel.com)
 *    Copyright (c) 2010, Intel Corporation.
 */

#अगर_अघोषित _CRYPTO_CRYPT_H
#घोषणा _CRYPTO_CRYPT_H

#समावेश <linux/kernel.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>

काष्ठा cryptd_skcipher अणु
	काष्ठा crypto_skcipher base;
पूर्ण;

/* alg_name should be algorithm to be cryptd-ed */
काष्ठा cryptd_skcipher *cryptd_alloc_skcipher(स्थिर अक्षर *alg_name,
					      u32 type, u32 mask);
काष्ठा crypto_skcipher *cryptd_skcipher_child(काष्ठा cryptd_skcipher *tfm);
/* Must be called without moving CPUs. */
bool cryptd_skcipher_queued(काष्ठा cryptd_skcipher *tfm);
व्योम cryptd_मुक्त_skcipher(काष्ठा cryptd_skcipher *tfm);

काष्ठा cryptd_ahash अणु
	काष्ठा crypto_ahash base;
पूर्ण;

अटल अंतरभूत काष्ठा cryptd_ahash *__cryptd_ahash_cast(
	काष्ठा crypto_ahash *tfm)
अणु
	वापस (काष्ठा cryptd_ahash *)tfm;
पूर्ण

/* alg_name should be algorithm to be cryptd-ed */
काष्ठा cryptd_ahash *cryptd_alloc_ahash(स्थिर अक्षर *alg_name,
					u32 type, u32 mask);
काष्ठा crypto_shash *cryptd_ahash_child(काष्ठा cryptd_ahash *tfm);
काष्ठा shash_desc *cryptd_shash_desc(काष्ठा ahash_request *req);
/* Must be called without moving CPUs. */
bool cryptd_ahash_queued(काष्ठा cryptd_ahash *tfm);
व्योम cryptd_मुक्त_ahash(काष्ठा cryptd_ahash *tfm);

काष्ठा cryptd_aead अणु
	काष्ठा crypto_aead base;
पूर्ण;

अटल अंतरभूत काष्ठा cryptd_aead *__cryptd_aead_cast(
	काष्ठा crypto_aead *tfm)
अणु
	वापस (काष्ठा cryptd_aead *)tfm;
पूर्ण

काष्ठा cryptd_aead *cryptd_alloc_aead(स्थिर अक्षर *alg_name,
					  u32 type, u32 mask);

काष्ठा crypto_aead *cryptd_aead_child(काष्ठा cryptd_aead *tfm);
/* Must be called without moving CPUs. */
bool cryptd_aead_queued(काष्ठा cryptd_aead *tfm);

व्योम cryptd_मुक्त_aead(काष्ठा cryptd_aead *tfm);

#पूर्ण_अगर
