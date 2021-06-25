<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Key setup क्रम v1 encryption policies
 *
 * Copyright 2015, 2019 Google LLC
 */

/*
 * This file implements compatibility functions क्रम the original encryption
 * policy version ("v1"), including:
 *
 * - Deriving per-file encryption keys using the AES-128-ECB based KDF
 *   (rather than the new method of using HKDF-SHA512)
 *
 * - Retrieving fscrypt master keys from process-subscribed keyrings
 *   (rather than the new method of using a fileप्रणाली-level keyring)
 *
 * - Handling policies with the सूचीECT_KEY flag set using a master key table
 *   (rather than the new method of implementing सूचीECT_KEY with per-mode keys
 *    managed aदीर्घside the master keys in the fileप्रणाली-level keyring)
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/skcipher.h>
#समावेश <keys/user-type.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/scatterlist.h>

#समावेश "fscrypt_private.h"

/* Table of keys referenced by सूचीECT_KEY policies */
अटल DEFINE_HASHTABLE(fscrypt_direct_keys, 6); /* 6 bits = 64 buckets */
अटल DEFINE_SPINLOCK(fscrypt_direct_keys_lock);

/*
 * v1 key derivation function.  This generates the derived key by encrypting the
 * master key with AES-128-ECB using the nonce as the AES key.  This provides a
 * unique derived key with sufficient entropy क्रम each inode.  However, it's
 * nonstandard, non-extensible, करोesn't evenly distribute the entropy from the
 * master key, and is trivially reversible: an attacker who compromises a
 * derived key can "decrypt" it to get back to the master key, then derive any
 * other key.  For all new code, use HKDF instead.
 *
 * The master key must be at least as दीर्घ as the derived key.  If the master
 * key is दीर्घer, then only the first 'derived_keysize' bytes are used.
 */
अटल पूर्णांक derive_key_aes(स्थिर u8 *master_key,
			  स्थिर u8 nonce[FSCRYPT_खाता_NONCE_SIZE],
			  u8 *derived_key, अचिन्हित पूर्णांक derived_keysize)
अणु
	पूर्णांक res = 0;
	काष्ठा skcipher_request *req = शून्य;
	DECLARE_CRYPTO_WAIT(रुको);
	काष्ठा scatterlist src_sg, dst_sg;
	काष्ठा crypto_skcipher *tfm = crypto_alloc_skcipher("ecb(aes)", 0, 0);

	अगर (IS_ERR(tfm)) अणु
		res = PTR_ERR(tfm);
		tfm = शून्य;
		जाओ out;
	पूर्ण
	crypto_skcipher_set_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		res = -ENOMEM;
		जाओ out;
	पूर्ण
	skcipher_request_set_callback(req,
			CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
			crypto_req_करोne, &रुको);
	res = crypto_skcipher_setkey(tfm, nonce, FSCRYPT_खाता_NONCE_SIZE);
	अगर (res < 0)
		जाओ out;

	sg_init_one(&src_sg, master_key, derived_keysize);
	sg_init_one(&dst_sg, derived_key, derived_keysize);
	skcipher_request_set_crypt(req, &src_sg, &dst_sg, derived_keysize,
				   शून्य);
	res = crypto_रुको_req(crypto_skcipher_encrypt(req), &रुको);
out:
	skcipher_request_मुक्त(req);
	crypto_मुक्त_skcipher(tfm);
	वापस res;
पूर्ण

/*
 * Search the current task's subscribed keyrings क्रम a "logon" key with
 * description prefix:descriptor, and अगर found acquire a पढ़ो lock on it and
 * वापस a poपूर्णांकer to its validated payload in *payload_ret.
 */
अटल काष्ठा key *
find_and_lock_process_key(स्थिर अक्षर *prefix,
			  स्थिर u8 descriptor[FSCRYPT_KEY_DESCRIPTOR_SIZE],
			  अचिन्हित पूर्णांक min_keysize,
			  स्थिर काष्ठा fscrypt_key **payload_ret)
अणु
	अक्षर *description;
	काष्ठा key *key;
	स्थिर काष्ठा user_key_payload *ukp;
	स्थिर काष्ठा fscrypt_key *payload;

	description = kaप्र_लिखो(GFP_KERNEL, "%s%*phN", prefix,
				FSCRYPT_KEY_DESCRIPTOR_SIZE, descriptor);
	अगर (!description)
		वापस ERR_PTR(-ENOMEM);

	key = request_key(&key_type_logon, description, शून्य);
	kमुक्त(description);
	अगर (IS_ERR(key))
		वापस key;

	करोwn_पढ़ो(&key->sem);
	ukp = user_key_payload_locked(key);

	अगर (!ukp) /* was the key revoked beक्रमe we acquired its semaphore? */
		जाओ invalid;

	payload = (स्थिर काष्ठा fscrypt_key *)ukp->data;

	अगर (ukp->datalen != माप(काष्ठा fscrypt_key) ||
	    payload->size < 1 || payload->size > FSCRYPT_MAX_KEY_SIZE) अणु
		fscrypt_warn(शून्य,
			     "key with description '%s' has invalid payload",
			     key->description);
		जाओ invalid;
	पूर्ण

	अगर (payload->size < min_keysize) अणु
		fscrypt_warn(शून्य,
			     "key with description '%s' is too short (got %u bytes, need %u+ bytes)",
			     key->description, payload->size, min_keysize);
		जाओ invalid;
	पूर्ण

	*payload_ret = payload;
	वापस key;

invalid:
	up_पढ़ो(&key->sem);
	key_put(key);
	वापस ERR_PTR(-ENOKEY);
पूर्ण

/* Master key referenced by सूचीECT_KEY policy */
काष्ठा fscrypt_direct_key अणु
	काष्ठा hlist_node		dk_node;
	refcount_t			dk_refcount;
	स्थिर काष्ठा fscrypt_mode	*dk_mode;
	काष्ठा fscrypt_prepared_key	dk_key;
	u8				dk_descriptor[FSCRYPT_KEY_DESCRIPTOR_SIZE];
	u8				dk_raw[FSCRYPT_MAX_KEY_SIZE];
पूर्ण;

अटल व्योम मुक्त_direct_key(काष्ठा fscrypt_direct_key *dk)
अणु
	अगर (dk) अणु
		fscrypt_destroy_prepared_key(&dk->dk_key);
		kमुक्त_sensitive(dk);
	पूर्ण
पूर्ण

व्योम fscrypt_put_direct_key(काष्ठा fscrypt_direct_key *dk)
अणु
	अगर (!refcount_dec_and_lock(&dk->dk_refcount, &fscrypt_direct_keys_lock))
		वापस;
	hash_del(&dk->dk_node);
	spin_unlock(&fscrypt_direct_keys_lock);

	मुक्त_direct_key(dk);
पूर्ण

/*
 * Find/insert the given key पूर्णांकo the fscrypt_direct_keys table.  If found, it
 * is वापसed with elevated refcount, and 'to_insert' is मुक्तd अगर non-शून्य.  If
 * not found, 'to_insert' is inserted and returned if it's non-शून्य; otherwise
 * शून्य is वापसed.
 */
अटल काष्ठा fscrypt_direct_key *
find_or_insert_direct_key(काष्ठा fscrypt_direct_key *to_insert,
			  स्थिर u8 *raw_key, स्थिर काष्ठा fscrypt_info *ci)
अणु
	अचिन्हित दीर्घ hash_key;
	काष्ठा fscrypt_direct_key *dk;

	/*
	 * Careful: to aव्योम potentially leaking secret key bytes via timing
	 * inक्रमmation, we must key the hash table by descriptor rather than by
	 * raw key, and use crypto_memneq() when comparing raw keys.
	 */

	BUILD_BUG_ON(माप(hash_key) > FSCRYPT_KEY_DESCRIPTOR_SIZE);
	स_नकल(&hash_key, ci->ci_policy.v1.master_key_descriptor,
	       माप(hash_key));

	spin_lock(&fscrypt_direct_keys_lock);
	hash_क्रम_each_possible(fscrypt_direct_keys, dk, dk_node, hash_key) अणु
		अगर (स_भेद(ci->ci_policy.v1.master_key_descriptor,
			   dk->dk_descriptor, FSCRYPT_KEY_DESCRIPTOR_SIZE) != 0)
			जारी;
		अगर (ci->ci_mode != dk->dk_mode)
			जारी;
		अगर (!fscrypt_is_key_prepared(&dk->dk_key, ci))
			जारी;
		अगर (crypto_memneq(raw_key, dk->dk_raw, ci->ci_mode->keysize))
			जारी;
		/* using existing tfm with same (descriptor, mode, raw_key) */
		refcount_inc(&dk->dk_refcount);
		spin_unlock(&fscrypt_direct_keys_lock);
		मुक्त_direct_key(to_insert);
		वापस dk;
	पूर्ण
	अगर (to_insert)
		hash_add(fscrypt_direct_keys, &to_insert->dk_node, hash_key);
	spin_unlock(&fscrypt_direct_keys_lock);
	वापस to_insert;
पूर्ण

/* Prepare to encrypt directly using the master key in the given mode */
अटल काष्ठा fscrypt_direct_key *
fscrypt_get_direct_key(स्थिर काष्ठा fscrypt_info *ci, स्थिर u8 *raw_key)
अणु
	काष्ठा fscrypt_direct_key *dk;
	पूर्णांक err;

	/* Is there alपढ़ोy a tfm क्रम this key? */
	dk = find_or_insert_direct_key(शून्य, raw_key, ci);
	अगर (dk)
		वापस dk;

	/* Nope, allocate one. */
	dk = kzalloc(माप(*dk), GFP_KERNEL);
	अगर (!dk)
		वापस ERR_PTR(-ENOMEM);
	refcount_set(&dk->dk_refcount, 1);
	dk->dk_mode = ci->ci_mode;
	err = fscrypt_prepare_key(&dk->dk_key, raw_key, ci);
	अगर (err)
		जाओ err_मुक्त_dk;
	स_नकल(dk->dk_descriptor, ci->ci_policy.v1.master_key_descriptor,
	       FSCRYPT_KEY_DESCRIPTOR_SIZE);
	स_नकल(dk->dk_raw, raw_key, ci->ci_mode->keysize);

	वापस find_or_insert_direct_key(dk, raw_key, ci);

err_मुक्त_dk:
	मुक्त_direct_key(dk);
	वापस ERR_PTR(err);
पूर्ण

/* v1 policy, सूचीECT_KEY: use the master key directly */
अटल पूर्णांक setup_v1_file_key_direct(काष्ठा fscrypt_info *ci,
				    स्थिर u8 *raw_master_key)
अणु
	काष्ठा fscrypt_direct_key *dk;

	dk = fscrypt_get_direct_key(ci, raw_master_key);
	अगर (IS_ERR(dk))
		वापस PTR_ERR(dk);
	ci->ci_direct_key = dk;
	ci->ci_enc_key = dk->dk_key;
	वापस 0;
पूर्ण

/* v1 policy, !सूचीECT_KEY: derive the file's encryption key */
अटल पूर्णांक setup_v1_file_key_derived(काष्ठा fscrypt_info *ci,
				     स्थिर u8 *raw_master_key)
अणु
	u8 *derived_key;
	पूर्णांक err;

	/*
	 * This cannot be a stack buffer because it will be passed to the
	 * scatterlist crypto API during derive_key_aes().
	 */
	derived_key = kदो_स्मृति(ci->ci_mode->keysize, GFP_KERNEL);
	अगर (!derived_key)
		वापस -ENOMEM;

	err = derive_key_aes(raw_master_key, ci->ci_nonce,
			     derived_key, ci->ci_mode->keysize);
	अगर (err)
		जाओ out;

	err = fscrypt_set_per_file_enc_key(ci, derived_key);
out:
	kमुक्त_sensitive(derived_key);
	वापस err;
पूर्ण

पूर्णांक fscrypt_setup_v1_file_key(काष्ठा fscrypt_info *ci, स्थिर u8 *raw_master_key)
अणु
	अगर (ci->ci_policy.v1.flags & FSCRYPT_POLICY_FLAG_सूचीECT_KEY)
		वापस setup_v1_file_key_direct(ci, raw_master_key);
	अन्यथा
		वापस setup_v1_file_key_derived(ci, raw_master_key);
पूर्ण

पूर्णांक fscrypt_setup_v1_file_key_via_subscribed_keyrings(काष्ठा fscrypt_info *ci)
अणु
	काष्ठा key *key;
	स्थिर काष्ठा fscrypt_key *payload;
	पूर्णांक err;

	key = find_and_lock_process_key(FSCRYPT_KEY_DESC_PREFIX,
					ci->ci_policy.v1.master_key_descriptor,
					ci->ci_mode->keysize, &payload);
	अगर (key == ERR_PTR(-ENOKEY) && ci->ci_inode->i_sb->s_cop->key_prefix) अणु
		key = find_and_lock_process_key(ci->ci_inode->i_sb->s_cop->key_prefix,
						ci->ci_policy.v1.master_key_descriptor,
						ci->ci_mode->keysize, &payload);
	पूर्ण
	अगर (IS_ERR(key))
		वापस PTR_ERR(key);

	err = fscrypt_setup_v1_file_key(ci, payload->raw);
	up_पढ़ो(&key->sem);
	key_put(key);
	वापस err;
पूर्ण
