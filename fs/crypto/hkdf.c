<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of HKDF ("HMAC-based Extract-and-Expand Key Derivation
 * Function"), aka RFC 5869.  See also the original paper (Krawczyk 2010):
 * "Cryptographic Extraction and Key Derivation: The HKDF Scheme".
 *
 * This is used to derive keys from the fscrypt master keys.
 *
 * Copyright 2019 Google LLC
 */

#समावेश <crypto/hash.h>
#समावेश <crypto/sha2.h>

#समावेश "fscrypt_private.h"

/*
 * HKDF supports any unkeyed cryptographic hash algorithm, but fscrypt uses
 * SHA-512 because it is reasonably secure and efficient; and since it produces
 * a 64-byte digest, deriving an AES-256-XTS key preserves all 64 bytes of
 * entropy from the master key and requires only one iteration of HKDF-Expand.
 */
#घोषणा HKDF_HMAC_ALG		"hmac(sha512)"
#घोषणा HKDF_HASHLEN		SHA512_DIGEST_SIZE

/*
 * HKDF consists of two steps:
 *
 * 1. HKDF-Extract: extract a pseuकरोअक्रमom key of length HKDF_HASHLEN bytes from
 *    the input keying material and optional salt.
 * 2. HKDF-Expand: expand the pseuकरोअक्रमom key पूर्णांकo output keying material of
 *    any length, parameterized by an application-specअगरic info string.
 *
 * HKDF-Extract can be skipped अगर the input is alपढ़ोy a pseuकरोअक्रमom key of
 * length HKDF_HASHLEN bytes.  However, cipher modes other than AES-256-XTS take
 * लघुer keys, and we करोn't want to क्रमce users of those modes to provide
 * unnecessarily दीर्घ master keys.  Thus fscrypt still करोes HKDF-Extract.  No
 * salt is used, since fscrypt master keys should alपढ़ोy be pseuकरोअक्रमom and
 * there's no way to persist a अक्रमom salt per master key from kernel mode.
 */

/* HKDF-Extract (RFC 5869 section 2.2), unsalted */
अटल पूर्णांक hkdf_extract(काष्ठा crypto_shash *hmac_tfm, स्थिर u8 *ikm,
			अचिन्हित पूर्णांक ikmlen, u8 prk[HKDF_HASHLEN])
अणु
	अटल स्थिर u8 शेष_salt[HKDF_HASHLEN];
	पूर्णांक err;

	err = crypto_shash_setkey(hmac_tfm, शेष_salt, HKDF_HASHLEN);
	अगर (err)
		वापस err;

	वापस crypto_shash_tfm_digest(hmac_tfm, ikm, ikmlen, prk);
पूर्ण

/*
 * Compute HKDF-Extract using the given master key as the input keying material,
 * and prepare an HMAC transक्रमm object keyed by the resulting pseuकरोअक्रमom key.
 *
 * Afterwards, the keyed HMAC transक्रमm object can be used क्रम HKDF-Expand many
 * बार without having to recompute HKDF-Extract each समय.
 */
पूर्णांक fscrypt_init_hkdf(काष्ठा fscrypt_hkdf *hkdf, स्थिर u8 *master_key,
		      अचिन्हित पूर्णांक master_key_size)
अणु
	काष्ठा crypto_shash *hmac_tfm;
	u8 prk[HKDF_HASHLEN];
	पूर्णांक err;

	hmac_tfm = crypto_alloc_shash(HKDF_HMAC_ALG, 0, 0);
	अगर (IS_ERR(hmac_tfm)) अणु
		fscrypt_err(शून्य, "Error allocating " HKDF_HMAC_ALG ": %ld",
			    PTR_ERR(hmac_tfm));
		वापस PTR_ERR(hmac_tfm);
	पूर्ण

	अगर (WARN_ON(crypto_shash_digestsize(hmac_tfm) != माप(prk))) अणु
		err = -EINVAL;
		जाओ err_मुक्त_tfm;
	पूर्ण

	err = hkdf_extract(hmac_tfm, master_key, master_key_size, prk);
	अगर (err)
		जाओ err_मुक्त_tfm;

	err = crypto_shash_setkey(hmac_tfm, prk, माप(prk));
	अगर (err)
		जाओ err_मुक्त_tfm;

	hkdf->hmac_tfm = hmac_tfm;
	जाओ out;

err_मुक्त_tfm:
	crypto_मुक्त_shash(hmac_tfm);
out:
	memzero_explicit(prk, माप(prk));
	वापस err;
पूर्ण

/*
 * HKDF-Expand (RFC 5869 section 2.3).  This expands the pseuकरोअक्रमom key, which
 * was alपढ़ोy keyed पूर्णांकo 'hkdf->hmac_tfm' by fscrypt_init_hkdf(), into 'okmlen'
 * bytes of output keying material parameterized by the application-specअगरic
 * 'info' of length 'infolen' bytes, prefixed by "fscrypt\0" and the 'context'
 * byte.  This is thपढ़ो-safe and may be called by multiple thपढ़ोs in parallel.
 *
 * ('context' isn't part of the HKDF specification; it's just a prefix fscrypt
 * adds to its application-specअगरic info strings to guarantee that it करोesn't
 * accidentally repeat an info string when using HKDF क्रम dअगरferent purposes.)
 */
पूर्णांक fscrypt_hkdf_expand(स्थिर काष्ठा fscrypt_hkdf *hkdf, u8 context,
			स्थिर u8 *info, अचिन्हित पूर्णांक infolen,
			u8 *okm, अचिन्हित पूर्णांक okmlen)
अणु
	SHASH_DESC_ON_STACK(desc, hkdf->hmac_tfm);
	u8 prefix[9];
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	स्थिर u8 *prev = शून्य;
	u8 counter = 1;
	u8 पंचांगp[HKDF_HASHLEN];

	अगर (WARN_ON(okmlen > 255 * HKDF_HASHLEN))
		वापस -EINVAL;

	desc->tfm = hkdf->hmac_tfm;

	स_नकल(prefix, "fscrypt\0", 8);
	prefix[8] = context;

	क्रम (i = 0; i < okmlen; i += HKDF_HASHLEN) अणु

		err = crypto_shash_init(desc);
		अगर (err)
			जाओ out;

		अगर (prev) अणु
			err = crypto_shash_update(desc, prev, HKDF_HASHLEN);
			अगर (err)
				जाओ out;
		पूर्ण

		err = crypto_shash_update(desc, prefix, माप(prefix));
		अगर (err)
			जाओ out;

		err = crypto_shash_update(desc, info, infolen);
		अगर (err)
			जाओ out;

		BUILD_BUG_ON(माप(counter) != 1);
		अगर (okmlen - i < HKDF_HASHLEN) अणु
			err = crypto_shash_finup(desc, &counter, 1, पंचांगp);
			अगर (err)
				जाओ out;
			स_नकल(&okm[i], पंचांगp, okmlen - i);
			memzero_explicit(पंचांगp, माप(पंचांगp));
		पूर्ण अन्यथा अणु
			err = crypto_shash_finup(desc, &counter, 1, &okm[i]);
			अगर (err)
				जाओ out;
		पूर्ण
		counter++;
		prev = &okm[i];
	पूर्ण
	err = 0;
out:
	अगर (unlikely(err))
		memzero_explicit(okm, okmlen); /* so caller करोesn't need to */
	shash_desc_zero(desc);
	वापस err;
पूर्ण

व्योम fscrypt_destroy_hkdf(काष्ठा fscrypt_hkdf *hkdf)
अणु
	crypto_मुक्त_shash(hkdf->hmac_tfm);
पूर्ण
