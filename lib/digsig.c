<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Nokia Corporation
 * Copyright (C) 2011 Intel Corporation
 *
 * Author:
 * Dmitry Kasatkin <dmitry.kasatkin@nokia.com>
 *                 <dmitry.kasatkin@पूर्णांकel.com>
 *
 * File: sign.c
 *	implements signature (RSA) verअगरication
 *	pkcs decoding is based on LibTomCrypt code
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/key.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <keys/user-type.h>
#समावेश <linux/mpi.h>
#समावेश <linux/digsig.h>

अटल काष्ठा crypto_shash *shash;

अटल स्थिर अक्षर *pkcs_1_v1_5_decode_emsa(स्थिर अचिन्हित अक्षर *msg,
						अचिन्हित दीर्घ  msglen,
						अचिन्हित दीर्घ  modulus_bitlen,
						अचिन्हित दीर्घ *outlen)
अणु
	अचिन्हित दीर्घ modulus_len, ps_len, i;

	modulus_len = (modulus_bitlen >> 3) + (modulus_bitlen & 7 ? 1 : 0);

	/* test message size */
	अगर ((msglen > modulus_len) || (modulus_len < 11))
		वापस शून्य;

	/* separate encoded message */
	अगर (msg[0] != 0x00 || msg[1] != 0x01)
		वापस शून्य;

	क्रम (i = 2; i < modulus_len - 1; i++)
		अगर (msg[i] != 0xFF)
			अवरोध;

	/* separator check */
	अगर (msg[i] != 0)
		/* There was no octet with hexadecimal value 0x00
		to separate ps from m. */
		वापस शून्य;

	ps_len = i - 2;

	*outlen = (msglen - (2 + ps_len + 1));

	वापस msg + 2 + ps_len + 1;
पूर्ण

/*
 * RSA Signature verअगरication with खुला key
 */
अटल पूर्णांक digsig_verअगरy_rsa(काष्ठा key *key,
		    स्थिर अक्षर *sig, पूर्णांक siglen,
		       स्थिर अक्षर *h, पूर्णांक hlen)
अणु
	पूर्णांक err = -EINVAL;
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ mlen, mblen;
	अचिन्हित nret, l;
	पूर्णांक head, i;
	अचिन्हित अक्षर *out1 = शून्य;
	स्थिर अक्षर *m;
	MPI in = शून्य, res = शून्य, pkey[2];
	uपूर्णांक8_t *p, *datap;
	स्थिर uपूर्णांक8_t *endp;
	स्थिर काष्ठा user_key_payload *ukp;
	काष्ठा pubkey_hdr *pkh;

	करोwn_पढ़ो(&key->sem);
	ukp = user_key_payload_locked(key);

	अगर (!ukp) अणु
		/* key was revoked beक्रमe we acquired its semaphore */
		err = -EKEYREVOKED;
		जाओ err1;
	पूर्ण

	अगर (ukp->datalen < माप(*pkh))
		जाओ err1;

	pkh = (काष्ठा pubkey_hdr *)ukp->data;

	अगर (pkh->version != 1)
		जाओ err1;

	अगर (pkh->algo != PUBKEY_ALGO_RSA)
		जाओ err1;

	अगर (pkh->nmpi != 2)
		जाओ err1;

	datap = pkh->mpi;
	endp = ukp->data + ukp->datalen;

	क्रम (i = 0; i < pkh->nmpi; i++) अणु
		अचिन्हित पूर्णांक reमुख्यing = endp - datap;
		pkey[i] = mpi_पढ़ो_from_buffer(datap, &reमुख्यing);
		अगर (IS_ERR(pkey[i])) अणु
			err = PTR_ERR(pkey[i]);
			जाओ err;
		पूर्ण
		datap += reमुख्यing;
	पूर्ण

	mblen = mpi_get_nbits(pkey[0]);
	mlen = DIV_ROUND_UP(mblen, 8);

	अगर (mlen == 0) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = -ENOMEM;

	out1 = kzalloc(mlen, GFP_KERNEL);
	अगर (!out1)
		जाओ err;

	nret = siglen;
	in = mpi_पढ़ो_from_buffer(sig, &nret);
	अगर (IS_ERR(in)) अणु
		err = PTR_ERR(in);
		जाओ err;
	पूर्ण

	res = mpi_alloc(mpi_get_nlimbs(in) * 2);
	अगर (!res)
		जाओ err;

	err = mpi_घातm(res, in, pkey[1], pkey[0]);
	अगर (err)
		जाओ err;

	अगर (mpi_get_nlimbs(res) * BYTES_PER_MPI_LIMB > mlen) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	p = mpi_get_buffer(res, &l, शून्य);
	अगर (!p) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	len = mlen;
	head = len - l;
	स_रखो(out1, 0, head);
	स_नकल(out1 + head, p, l);

	kमुक्त(p);

	m = pkcs_1_v1_5_decode_emsa(out1, len, mblen, &len);

	अगर (!m || len != hlen || स_भेद(m, h, hlen))
		err = -EINVAL;

err:
	mpi_मुक्त(in);
	mpi_मुक्त(res);
	kमुक्त(out1);
	जबतक (--i >= 0)
		mpi_मुक्त(pkey[i]);
err1:
	up_पढ़ो(&key->sem);

	वापस err;
पूर्ण

/**
 * digsig_verअगरy() - digital signature verअगरication with खुला key
 * @keyring:	keyring to search key in
 * @sig:	digital signature
 * @siglen:	length of the signature
 * @data:	data
 * @datalen:	length of the data
 *
 * Returns 0 on success, -EINVAL otherwise
 *
 * Verअगरies data पूर्णांकegrity against digital signature.
 * Currently only RSA is supported.
 * Normally hash of the content is used as a data क्रम this function.
 *
 */
पूर्णांक digsig_verअगरy(काष्ठा key *keyring, स्थिर अक्षर *sig, पूर्णांक siglen,
						स्थिर अक्षर *data, पूर्णांक datalen)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा signature_hdr *sh = (काष्ठा signature_hdr *)sig;
	काष्ठा shash_desc *desc = शून्य;
	अचिन्हित अक्षर hash[SHA1_DIGEST_SIZE];
	काष्ठा key *key;
	अक्षर name[20];

	अगर (siglen < माप(*sh) + 2)
		वापस -EINVAL;

	अगर (sh->algo != PUBKEY_ALGO_RSA)
		वापस -ENOTSUPP;

	प्र_लिखो(name, "%llX", __be64_to_cpup((uपूर्णांक64_t *)sh->keyid));

	अगर (keyring) अणु
		/* search in specअगरic keyring */
		key_ref_t kref;
		kref = keyring_search(make_key_ref(keyring, 1UL),
				      &key_type_user, name, true);
		अगर (IS_ERR(kref))
			key = ERR_CAST(kref);
		अन्यथा
			key = key_ref_to_ptr(kref);
	पूर्ण अन्यथा अणु
		key = request_key(&key_type_user, name, शून्य);
	पूर्ण
	अगर (IS_ERR(key)) अणु
		pr_err("key not found, id: %s\n", name);
		वापस PTR_ERR(key);
	पूर्ण

	desc = kzalloc(माप(*desc) + crypto_shash_descsize(shash),
		       GFP_KERNEL);
	अगर (!desc)
		जाओ err;

	desc->tfm = shash;

	crypto_shash_init(desc);
	crypto_shash_update(desc, data, datalen);
	crypto_shash_update(desc, sig, माप(*sh));
	crypto_shash_final(desc, hash);

	kमुक्त(desc);

	/* pass signature mpis address */
	err = digsig_verअगरy_rsa(key, sig + माप(*sh), siglen - माप(*sh),
			     hash, माप(hash));

err:
	key_put(key);

	वापस err ? -EINVAL : 0;
पूर्ण
EXPORT_SYMBOL_GPL(digsig_verअगरy);

अटल पूर्णांक __init digsig_init(व्योम)
अणु
	shash = crypto_alloc_shash("sha1", 0, 0);
	अगर (IS_ERR(shash)) अणु
		pr_err("shash allocation failed\n");
		वापस  PTR_ERR(shash);
	पूर्ण

	वापस 0;

पूर्ण

अटल व्योम __निकास digsig_cleanup(व्योम)
अणु
	crypto_मुक्त_shash(shash);
पूर्ण

module_init(digsig_init);
module_निकास(digsig_cleanup);

MODULE_LICENSE("GPL");
