<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Intel Corporation
 *
 * Author:
 * Dmitry Kasatkin <dmitry.kasatkin@पूर्णांकel.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/key-type.h>
#समावेश <crypto/खुला_key.h>
#समावेश <crypto/hash_info.h>
#समावेश <keys/asymmetric-type.h>
#समावेश <keys/प्रणाली_keyring.h>

#समावेश "integrity.h"

/*
 * Request an asymmetric key.
 */
अटल काष्ठा key *request_asymmetric_key(काष्ठा key *keyring, uपूर्णांक32_t keyid)
अणु
	काष्ठा key *key;
	अक्षर name[12];

	प्र_लिखो(name, "id:%08x", keyid);

	pr_debug("key search: \"%s\"\n", name);

	key = get_ima_blacklist_keyring();
	अगर (key) अणु
		key_ref_t kref;

		kref = keyring_search(make_key_ref(key, 1),
				      &key_type_asymmetric, name, true);
		अगर (!IS_ERR(kref)) अणु
			pr_err("Key '%s' is in ima_blacklist_keyring\n", name);
			वापस ERR_PTR(-EKEYREJECTED);
		पूर्ण
	पूर्ण

	अगर (keyring) अणु
		/* search in specअगरic keyring */
		key_ref_t kref;

		kref = keyring_search(make_key_ref(keyring, 1),
				      &key_type_asymmetric, name, true);
		अगर (IS_ERR(kref))
			key = ERR_CAST(kref);
		अन्यथा
			key = key_ref_to_ptr(kref);
	पूर्ण अन्यथा अणु
		key = request_key(&key_type_asymmetric, name, शून्य);
	पूर्ण

	अगर (IS_ERR(key)) अणु
		अगर (keyring)
			pr_err_ratelimited("Request for unknown key '%s' in '%s' keyring. err %ld\n",
					   name, keyring->description,
					   PTR_ERR(key));
		अन्यथा
			pr_err_ratelimited("Request for unknown key '%s' err %ld\n",
					   name, PTR_ERR(key));

		चयन (PTR_ERR(key)) अणु
			/* Hide some search errors */
		हाल -EACCES:
		हाल -ENOTसूची:
		हाल -EAGAIN:
			वापस ERR_PTR(-ENOKEY);
		शेष:
			वापस key;
		पूर्ण
	पूर्ण

	pr_debug("%s() = 0 [%x]\n", __func__, key_serial(key));

	वापस key;
पूर्ण

पूर्णांक asymmetric_verअगरy(काष्ठा key *keyring, स्थिर अक्षर *sig,
		      पूर्णांक siglen, स्थिर अक्षर *data, पूर्णांक datalen)
अणु
	काष्ठा खुला_key_signature pks;
	काष्ठा signature_v2_hdr *hdr = (काष्ठा signature_v2_hdr *)sig;
	स्थिर काष्ठा खुला_key *pk;
	काष्ठा key *key;
	पूर्णांक ret;

	अगर (siglen <= माप(*hdr))
		वापस -EBADMSG;

	siglen -= माप(*hdr);

	अगर (siglen != be16_to_cpu(hdr->sig_size))
		वापस -EBADMSG;

	अगर (hdr->hash_algo >= HASH_ALGO__LAST)
		वापस -ENOPKG;

	key = request_asymmetric_key(keyring, be32_to_cpu(hdr->keyid));
	अगर (IS_ERR(key))
		वापस PTR_ERR(key);

	स_रखो(&pks, 0, माप(pks));

	pks.hash_algo = hash_algo_name[hdr->hash_algo];

	pk = asymmetric_key_खुला_key(key);
	pks.pkey_algo = pk->pkey_algo;
	अगर (!म_भेद(pk->pkey_algo, "rsa"))
		pks.encoding = "pkcs1";
	अन्यथा अगर (!म_भेदन(pk->pkey_algo, "ecdsa-", 6))
		/* edcsa-nist-p192 etc. */
		pks.encoding = "x962";
	अन्यथा अगर (!म_भेद(pk->pkey_algo, "ecrdsa") ||
		   !म_भेद(pk->pkey_algo, "sm2"))
		pks.encoding = "raw";
	अन्यथा
		वापस -ENOPKG;

	pks.digest = (u8 *)data;
	pks.digest_size = datalen;
	pks.s = hdr->sig;
	pks.s_size = siglen;
	ret = verअगरy_signature(key, &pks);
	key_put(key);
	pr_debug("%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

/**
 * पूर्णांकegrity_kernel_module_request - prevent crypto-pkcs1pad(rsa,*) requests
 * @kmod_name: kernel module name
 *
 * We have situation, when खुला_key_verअगरy_signature() in हाल of RSA
 * algorithm use alg_name to store पूर्णांकernal inक्रमmation in order to
 * स्थिरruct an algorithm on the fly, but crypto_larval_lookup() will try
 * to use alg_name in order to load kernel module with same name.
 * Since we करोn't have any real "crypto-pkcs1pad(rsa,*)" kernel modules,
 * we are safe to fail such module request from crypto_larval_lookup().
 *
 * In this way we prevent modprobe execution during digsig verअगरication
 * and aव्योम possible deadlock अगर modprobe and/or it's dependencies
 * also चिन्हित with digsig.
 */
पूर्णांक पूर्णांकegrity_kernel_module_request(अक्षर *kmod_name)
अणु
	अगर (म_भेदन(kmod_name, "crypto-pkcs1pad(rsa,", 20) == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण
