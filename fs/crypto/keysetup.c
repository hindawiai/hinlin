<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Key setup facility क्रम FS encryption support.
 *
 * Copyright (C) 2015, Google, Inc.
 *
 * Originally written by Michael Halcrow, Ildar Muslukhov, and Uday Savagaonkar.
 * Heavily modअगरied since then.
 */

#समावेश <crypto/skcipher.h>
#समावेश <linux/key.h>
#समावेश <linux/अक्रमom.h>

#समावेश "fscrypt_private.h"

काष्ठा fscrypt_mode fscrypt_modes[] = अणु
	[FSCRYPT_MODE_AES_256_XTS] = अणु
		.मित्रly_name = "AES-256-XTS",
		.cipher_str = "xts(aes)",
		.keysize = 64,
		.ivsize = 16,
		.blk_crypto_mode = BLK_ENCRYPTION_MODE_AES_256_XTS,
	पूर्ण,
	[FSCRYPT_MODE_AES_256_CTS] = अणु
		.मित्रly_name = "AES-256-CTS-CBC",
		.cipher_str = "cts(cbc(aes))",
		.keysize = 32,
		.ivsize = 16,
	पूर्ण,
	[FSCRYPT_MODE_AES_128_CBC] = अणु
		.मित्रly_name = "AES-128-CBC-ESSIV",
		.cipher_str = "essiv(cbc(aes),sha256)",
		.keysize = 16,
		.ivsize = 16,
		.blk_crypto_mode = BLK_ENCRYPTION_MODE_AES_128_CBC_ESSIV,
	पूर्ण,
	[FSCRYPT_MODE_AES_128_CTS] = अणु
		.मित्रly_name = "AES-128-CTS-CBC",
		.cipher_str = "cts(cbc(aes))",
		.keysize = 16,
		.ivsize = 16,
	पूर्ण,
	[FSCRYPT_MODE_ADIANTUM] = अणु
		.मित्रly_name = "Adiantum",
		.cipher_str = "adiantum(xchacha12,aes)",
		.keysize = 32,
		.ivsize = 32,
		.blk_crypto_mode = BLK_ENCRYPTION_MODE_ADIANTUM,
	पूर्ण,
पूर्ण;

अटल DEFINE_MUTEX(fscrypt_mode_key_setup_mutex);

अटल काष्ठा fscrypt_mode *
select_encryption_mode(स्थिर जोड़ fscrypt_policy *policy,
		       स्थिर काष्ठा inode *inode)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(fscrypt_modes) != FSCRYPT_MODE_MAX + 1);

	अगर (S_ISREG(inode->i_mode))
		वापस &fscrypt_modes[fscrypt_policy_contents_mode(policy)];

	अगर (S_ISसूची(inode->i_mode) || S_ISLNK(inode->i_mode))
		वापस &fscrypt_modes[fscrypt_policy_fnames_mode(policy)];

	WARN_ONCE(1, "fscrypt: filesystem tried to load encryption info for inode %lu, which is not encryptable (file type %d)\n",
		  inode->i_ino, (inode->i_mode & S_IFMT));
	वापस ERR_PTR(-EINVAL);
पूर्ण

/* Create a symmetric cipher object क्रम the given encryption mode and key */
अटल काष्ठा crypto_skcipher *
fscrypt_allocate_skcipher(काष्ठा fscrypt_mode *mode, स्थिर u8 *raw_key,
			  स्थिर काष्ठा inode *inode)
अणु
	काष्ठा crypto_skcipher *tfm;
	पूर्णांक err;

	tfm = crypto_alloc_skcipher(mode->cipher_str, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		अगर (PTR_ERR(tfm) == -ENOENT) अणु
			fscrypt_warn(inode,
				     "Missing crypto API support for %s (API name: \"%s\")",
				     mode->मित्रly_name, mode->cipher_str);
			वापस ERR_PTR(-ENOPKG);
		पूर्ण
		fscrypt_err(inode, "Error allocating '%s' transform: %ld",
			    mode->cipher_str, PTR_ERR(tfm));
		वापस tfm;
	पूर्ण
	अगर (!xchg(&mode->logged_impl_name, 1)) अणु
		/*
		 * fscrypt perक्रमmance can vary greatly depending on which
		 * crypto algorithm implementation is used.  Help people debug
		 * perक्रमmance problems by logging the ->cra_driver_name the
		 * first समय a mode is used.
		 */
		pr_info("fscrypt: %s using implementation \"%s\"\n",
			mode->मित्रly_name, crypto_skcipher_driver_name(tfm));
	पूर्ण
	अगर (WARN_ON(crypto_skcipher_ivsize(tfm) != mode->ivsize)) अणु
		err = -EINVAL;
		जाओ err_मुक्त_tfm;
	पूर्ण
	crypto_skcipher_set_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	err = crypto_skcipher_setkey(tfm, raw_key, mode->keysize);
	अगर (err)
		जाओ err_मुक्त_tfm;

	वापस tfm;

err_मुक्त_tfm:
	crypto_मुक्त_skcipher(tfm);
	वापस ERR_PTR(err);
पूर्ण

/*
 * Prepare the crypto transक्रमm object or blk-crypto key in @prep_key, given the
 * raw key, encryption mode, and flag indicating which encryption implementation
 * (fs-layer or blk-crypto) will be used.
 */
पूर्णांक fscrypt_prepare_key(काष्ठा fscrypt_prepared_key *prep_key,
			स्थिर u8 *raw_key, स्थिर काष्ठा fscrypt_info *ci)
अणु
	काष्ठा crypto_skcipher *tfm;

	अगर (fscrypt_using_अंतरभूत_encryption(ci))
		वापस fscrypt_prepare_अंतरभूत_crypt_key(prep_key, raw_key, ci);

	tfm = fscrypt_allocate_skcipher(ci->ci_mode, raw_key, ci->ci_inode);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);
	/*
	 * Pairs with the smp_load_acquire() in fscrypt_is_key_prepared().
	 * I.e., here we publish ->tfm with a RELEASE barrier so that
	 * concurrent tasks can ACQUIRE it.  Note that this concurrency is only
	 * possible क्रम per-mode keys, not क्रम per-file keys.
	 */
	smp_store_release(&prep_key->tfm, tfm);
	वापस 0;
पूर्ण

/* Destroy a crypto transक्रमm object and/or blk-crypto key. */
व्योम fscrypt_destroy_prepared_key(काष्ठा fscrypt_prepared_key *prep_key)
अणु
	crypto_मुक्त_skcipher(prep_key->tfm);
	fscrypt_destroy_अंतरभूत_crypt_key(prep_key);
पूर्ण

/* Given a per-file encryption key, set up the file's crypto transक्रमm object */
पूर्णांक fscrypt_set_per_file_enc_key(काष्ठा fscrypt_info *ci, स्थिर u8 *raw_key)
अणु
	ci->ci_owns_key = true;
	वापस fscrypt_prepare_key(&ci->ci_enc_key, raw_key, ci);
पूर्ण

अटल पूर्णांक setup_per_mode_enc_key(काष्ठा fscrypt_info *ci,
				  काष्ठा fscrypt_master_key *mk,
				  काष्ठा fscrypt_prepared_key *keys,
				  u8 hkdf_context, bool include_fs_uuid)
अणु
	स्थिर काष्ठा inode *inode = ci->ci_inode;
	स्थिर काष्ठा super_block *sb = inode->i_sb;
	काष्ठा fscrypt_mode *mode = ci->ci_mode;
	स्थिर u8 mode_num = mode - fscrypt_modes;
	काष्ठा fscrypt_prepared_key *prep_key;
	u8 mode_key[FSCRYPT_MAX_KEY_SIZE];
	u8 hkdf_info[माप(mode_num) + माप(sb->s_uuid)];
	अचिन्हित पूर्णांक hkdf_infolen = 0;
	पूर्णांक err;

	अगर (WARN_ON(mode_num > FSCRYPT_MODE_MAX))
		वापस -EINVAL;

	prep_key = &keys[mode_num];
	अगर (fscrypt_is_key_prepared(prep_key, ci)) अणु
		ci->ci_enc_key = *prep_key;
		वापस 0;
	पूर्ण

	mutex_lock(&fscrypt_mode_key_setup_mutex);

	अगर (fscrypt_is_key_prepared(prep_key, ci))
		जाओ करोne_unlock;

	BUILD_BUG_ON(माप(mode_num) != 1);
	BUILD_BUG_ON(माप(sb->s_uuid) != 16);
	BUILD_BUG_ON(माप(hkdf_info) != 17);
	hkdf_info[hkdf_infolen++] = mode_num;
	अगर (include_fs_uuid) अणु
		स_नकल(&hkdf_info[hkdf_infolen], &sb->s_uuid,
		       माप(sb->s_uuid));
		hkdf_infolen += माप(sb->s_uuid);
	पूर्ण
	err = fscrypt_hkdf_expand(&mk->mk_secret.hkdf,
				  hkdf_context, hkdf_info, hkdf_infolen,
				  mode_key, mode->keysize);
	अगर (err)
		जाओ out_unlock;
	err = fscrypt_prepare_key(prep_key, mode_key, ci);
	memzero_explicit(mode_key, mode->keysize);
	अगर (err)
		जाओ out_unlock;
करोne_unlock:
	ci->ci_enc_key = *prep_key;
	err = 0;
out_unlock:
	mutex_unlock(&fscrypt_mode_key_setup_mutex);
	वापस err;
पूर्ण

पूर्णांक fscrypt_derive_dirhash_key(काष्ठा fscrypt_info *ci,
			       स्थिर काष्ठा fscrypt_master_key *mk)
अणु
	पूर्णांक err;

	err = fscrypt_hkdf_expand(&mk->mk_secret.hkdf, HKDF_CONTEXT_सूचीHASH_KEY,
				  ci->ci_nonce, FSCRYPT_खाता_NONCE_SIZE,
				  (u8 *)&ci->ci_dirhash_key,
				  माप(ci->ci_dirhash_key));
	अगर (err)
		वापस err;
	ci->ci_dirhash_key_initialized = true;
	वापस 0;
पूर्ण

व्योम fscrypt_hash_inode_number(काष्ठा fscrypt_info *ci,
			       स्थिर काष्ठा fscrypt_master_key *mk)
अणु
	WARN_ON(ci->ci_inode->i_ino == 0);
	WARN_ON(!mk->mk_ino_hash_key_initialized);

	ci->ci_hashed_ino = (u32)siphash_1u64(ci->ci_inode->i_ino,
					      &mk->mk_ino_hash_key);
पूर्ण

अटल पूर्णांक fscrypt_setup_iv_ino_lblk_32_key(काष्ठा fscrypt_info *ci,
					    काष्ठा fscrypt_master_key *mk)
अणु
	पूर्णांक err;

	err = setup_per_mode_enc_key(ci, mk, mk->mk_iv_ino_lblk_32_keys,
				     HKDF_CONTEXT_IV_INO_LBLK_32_KEY, true);
	अगर (err)
		वापस err;

	/* pairs with smp_store_release() below */
	अगर (!smp_load_acquire(&mk->mk_ino_hash_key_initialized)) अणु

		mutex_lock(&fscrypt_mode_key_setup_mutex);

		अगर (mk->mk_ino_hash_key_initialized)
			जाओ unlock;

		err = fscrypt_hkdf_expand(&mk->mk_secret.hkdf,
					  HKDF_CONTEXT_INODE_HASH_KEY, शून्य, 0,
					  (u8 *)&mk->mk_ino_hash_key,
					  माप(mk->mk_ino_hash_key));
		अगर (err)
			जाओ unlock;
		/* pairs with smp_load_acquire() above */
		smp_store_release(&mk->mk_ino_hash_key_initialized, true);
unlock:
		mutex_unlock(&fscrypt_mode_key_setup_mutex);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * New inodes may not have an inode number asचिन्हित yet.
	 * Hashing their inode number is delayed until later.
	 */
	अगर (ci->ci_inode->i_ino)
		fscrypt_hash_inode_number(ci, mk);
	वापस 0;
पूर्ण

अटल पूर्णांक fscrypt_setup_v2_file_key(काष्ठा fscrypt_info *ci,
				     काष्ठा fscrypt_master_key *mk,
				     bool need_dirhash_key)
अणु
	पूर्णांक err;

	अगर (ci->ci_policy.v2.flags & FSCRYPT_POLICY_FLAG_सूचीECT_KEY) अणु
		/*
		 * सूचीECT_KEY: instead of deriving per-file encryption keys, the
		 * per-file nonce will be included in all the IVs.  But unlike
		 * v1 policies, क्रम v2 policies in this हाल we करोn't encrypt
		 * with the master key directly but rather derive a per-mode
		 * encryption key.  This ensures that the master key is
		 * consistently used only क्रम HKDF, aव्योमing key reuse issues.
		 */
		err = setup_per_mode_enc_key(ci, mk, mk->mk_direct_keys,
					     HKDF_CONTEXT_सूचीECT_KEY, false);
	पूर्ण अन्यथा अगर (ci->ci_policy.v2.flags &
		   FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64) अणु
		/*
		 * IV_INO_LBLK_64: encryption keys are derived from (master_key,
		 * mode_num, fileप्रणाली_uuid), and inode number is included in
		 * the IVs.  This क्रमmat is optimized क्रम use with अंतरभूत
		 * encryption hardware compliant with the UFS standard.
		 */
		err = setup_per_mode_enc_key(ci, mk, mk->mk_iv_ino_lblk_64_keys,
					     HKDF_CONTEXT_IV_INO_LBLK_64_KEY,
					     true);
	पूर्ण अन्यथा अगर (ci->ci_policy.v2.flags &
		   FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32) अणु
		err = fscrypt_setup_iv_ino_lblk_32_key(ci, mk);
	पूर्ण अन्यथा अणु
		u8 derived_key[FSCRYPT_MAX_KEY_SIZE];

		err = fscrypt_hkdf_expand(&mk->mk_secret.hkdf,
					  HKDF_CONTEXT_PER_खाता_ENC_KEY,
					  ci->ci_nonce, FSCRYPT_खाता_NONCE_SIZE,
					  derived_key, ci->ci_mode->keysize);
		अगर (err)
			वापस err;

		err = fscrypt_set_per_file_enc_key(ci, derived_key);
		memzero_explicit(derived_key, ci->ci_mode->keysize);
	पूर्ण
	अगर (err)
		वापस err;

	/* Derive a secret dirhash key क्रम directories that need it. */
	अगर (need_dirhash_key) अणु
		err = fscrypt_derive_dirhash_key(ci, mk);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Find the master key, then set up the inode's actual encryption key.
 *
 * If the master key is found in the fileप्रणाली-level keyring, then the
 * corresponding 'struct key' is वापसed in *master_key_ret with its semaphore
 * पढ़ो-locked.  This is needed to ensure that only one task links the
 * fscrypt_info पूर्णांकo ->mk_decrypted_inodes (as multiple tasks may race to create
 * an fscrypt_info क्रम the same inode), and to synchronize the master key being
 * हटाओd with a new inode starting to use it.
 */
अटल पूर्णांक setup_file_encryption_key(काष्ठा fscrypt_info *ci,
				     bool need_dirhash_key,
				     काष्ठा key **master_key_ret)
अणु
	काष्ठा key *key;
	काष्ठा fscrypt_master_key *mk = शून्य;
	काष्ठा fscrypt_key_specअगरier mk_spec;
	पूर्णांक err;

	err = fscrypt_select_encryption_impl(ci);
	अगर (err)
		वापस err;

	चयन (ci->ci_policy.version) अणु
	हाल FSCRYPT_POLICY_V1:
		mk_spec.type = FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR;
		स_नकल(mk_spec.u.descriptor,
		       ci->ci_policy.v1.master_key_descriptor,
		       FSCRYPT_KEY_DESCRIPTOR_SIZE);
		अवरोध;
	हाल FSCRYPT_POLICY_V2:
		mk_spec.type = FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER;
		स_नकल(mk_spec.u.identअगरier,
		       ci->ci_policy.v2.master_key_identअगरier,
		       FSCRYPT_KEY_IDENTIFIER_SIZE);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	key = fscrypt_find_master_key(ci->ci_inode->i_sb, &mk_spec);
	अगर (IS_ERR(key)) अणु
		अगर (key != ERR_PTR(-ENOKEY) ||
		    ci->ci_policy.version != FSCRYPT_POLICY_V1)
			वापस PTR_ERR(key);

		/*
		 * As a legacy fallback क्रम v1 policies, search क्रम the key in
		 * the current task's subscribed keyrings too.  Don't move this
		 * to beक्रमe the search of ->s_master_keys, since users
		 * shouldn't be able to override fileप्रणाली-level keys.
		 */
		वापस fscrypt_setup_v1_file_key_via_subscribed_keyrings(ci);
	पूर्ण

	mk = key->payload.data[0];
	करोwn_पढ़ो(&key->sem);

	/* Has the secret been हटाओd (via FS_IOC_REMOVE_ENCRYPTION_KEY)? */
	अगर (!is_master_key_secret_present(&mk->mk_secret)) अणु
		err = -ENOKEY;
		जाओ out_release_key;
	पूर्ण

	/*
	 * Require that the master key be at least as दीर्घ as the derived key.
	 * Otherwise, the derived key cannot possibly contain as much entropy as
	 * that required by the encryption mode it will be used क्रम.  For v1
	 * policies it's also required क्रम the KDF to work at all.
	 */
	अगर (mk->mk_secret.size < ci->ci_mode->keysize) अणु
		fscrypt_warn(शून्य,
			     "key with %s %*phN is too short (got %u bytes, need %u+ bytes)",
			     master_key_spec_type(&mk_spec),
			     master_key_spec_len(&mk_spec), (u8 *)&mk_spec.u,
			     mk->mk_secret.size, ci->ci_mode->keysize);
		err = -ENOKEY;
		जाओ out_release_key;
	पूर्ण

	चयन (ci->ci_policy.version) अणु
	हाल FSCRYPT_POLICY_V1:
		err = fscrypt_setup_v1_file_key(ci, mk->mk_secret.raw);
		अवरोध;
	हाल FSCRYPT_POLICY_V2:
		err = fscrypt_setup_v2_file_key(ci, mk, need_dirhash_key);
		अवरोध;
	शेष:
		WARN_ON(1);
		err = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (err)
		जाओ out_release_key;

	*master_key_ret = key;
	वापस 0;

out_release_key:
	up_पढ़ो(&key->sem);
	key_put(key);
	वापस err;
पूर्ण

अटल व्योम put_crypt_info(काष्ठा fscrypt_info *ci)
अणु
	काष्ठा key *key;

	अगर (!ci)
		वापस;

	अगर (ci->ci_direct_key)
		fscrypt_put_direct_key(ci->ci_direct_key);
	अन्यथा अगर (ci->ci_owns_key)
		fscrypt_destroy_prepared_key(&ci->ci_enc_key);

	key = ci->ci_master_key;
	अगर (key) अणु
		काष्ठा fscrypt_master_key *mk = key->payload.data[0];

		/*
		 * Remove this inode from the list of inodes that were unlocked
		 * with the master key.
		 *
		 * In addition, अगर we're removing the last inode from a key that
		 * alपढ़ोy had its secret हटाओd, invalidate the key so that it
		 * माला_लो हटाओd from ->s_master_keys.
		 */
		spin_lock(&mk->mk_decrypted_inodes_lock);
		list_del(&ci->ci_master_key_link);
		spin_unlock(&mk->mk_decrypted_inodes_lock);
		अगर (refcount_dec_and_test(&mk->mk_refcount))
			key_invalidate(key);
		key_put(key);
	पूर्ण
	memzero_explicit(ci, माप(*ci));
	kmem_cache_मुक्त(fscrypt_info_cachep, ci);
पूर्ण

अटल पूर्णांक
fscrypt_setup_encryption_info(काष्ठा inode *inode,
			      स्थिर जोड़ fscrypt_policy *policy,
			      स्थिर u8 nonce[FSCRYPT_खाता_NONCE_SIZE],
			      bool need_dirhash_key)
अणु
	काष्ठा fscrypt_info *crypt_info;
	काष्ठा fscrypt_mode *mode;
	काष्ठा key *master_key = शून्य;
	पूर्णांक res;

	res = fscrypt_initialize(inode->i_sb->s_cop->flags);
	अगर (res)
		वापस res;

	crypt_info = kmem_cache_zalloc(fscrypt_info_cachep, GFP_KERNEL);
	अगर (!crypt_info)
		वापस -ENOMEM;

	crypt_info->ci_inode = inode;
	crypt_info->ci_policy = *policy;
	स_नकल(crypt_info->ci_nonce, nonce, FSCRYPT_खाता_NONCE_SIZE);

	mode = select_encryption_mode(&crypt_info->ci_policy, inode);
	अगर (IS_ERR(mode)) अणु
		res = PTR_ERR(mode);
		जाओ out;
	पूर्ण
	WARN_ON(mode->ivsize > FSCRYPT_MAX_IV_SIZE);
	crypt_info->ci_mode = mode;

	res = setup_file_encryption_key(crypt_info, need_dirhash_key,
					&master_key);
	अगर (res)
		जाओ out;

	/*
	 * For existing inodes, multiple tasks may race to set ->i_crypt_info.
	 * So use cmpxchg_release().  This pairs with the smp_load_acquire() in
	 * fscrypt_get_info().  I.e., here we publish ->i_crypt_info with a
	 * RELEASE barrier so that other tasks can ACQUIRE it.
	 */
	अगर (cmpxchg_release(&inode->i_crypt_info, शून्य, crypt_info) == शून्य) अणु
		/*
		 * We won the race and set ->i_crypt_info to our crypt_info.
		 * Now link it पूर्णांकo the master key's inode list.
		 */
		अगर (master_key) अणु
			काष्ठा fscrypt_master_key *mk =
				master_key->payload.data[0];

			refcount_inc(&mk->mk_refcount);
			crypt_info->ci_master_key = key_get(master_key);
			spin_lock(&mk->mk_decrypted_inodes_lock);
			list_add(&crypt_info->ci_master_key_link,
				 &mk->mk_decrypted_inodes);
			spin_unlock(&mk->mk_decrypted_inodes_lock);
		पूर्ण
		crypt_info = शून्य;
	पूर्ण
	res = 0;
out:
	अगर (master_key) अणु
		up_पढ़ो(&master_key->sem);
		key_put(master_key);
	पूर्ण
	put_crypt_info(crypt_info);
	वापस res;
पूर्ण

/**
 * fscrypt_get_encryption_info() - set up an inode's encryption key
 * @inode: the inode to set up the key क्रम.  Must be encrypted.
 * @allow_unsupported: अगर %true, treat an unsupported encryption policy (or
 *		       unrecognized encryption context) the same way as the key
 *		       being unavailable, instead of वापसing an error.  Use
 *		       %false unless the operation being perक्रमmed is needed in
 *		       order क्रम files (or directories) to be deleted.
 *
 * Set up ->i_crypt_info, अगर it hasn't alपढ़ोy been करोne.
 *
 * Note: unless ->i_crypt_info is alपढ़ोy set, this isn't %GFP_NOFS-safe.  So
 * generally this shouldn't be called from within a fileप्रणाली transaction.
 *
 * Return: 0 अगर ->i_crypt_info was set or was alपढ़ोy set, *or* अगर the
 *	   encryption key is unavailable.  (Use fscrypt_has_encryption_key() to
 *	   distinguish these हालs.)  Also can वापस another -त्रुटि_सं code.
 */
पूर्णांक fscrypt_get_encryption_info(काष्ठा inode *inode, bool allow_unsupported)
अणु
	पूर्णांक res;
	जोड़ fscrypt_context ctx;
	जोड़ fscrypt_policy policy;

	अगर (fscrypt_has_encryption_key(inode))
		वापस 0;

	res = inode->i_sb->s_cop->get_context(inode, &ctx, माप(ctx));
	अगर (res < 0) अणु
		अगर (res == -दुस्फल && allow_unsupported)
			वापस 0;
		fscrypt_warn(inode, "Error %d getting encryption context", res);
		वापस res;
	पूर्ण

	res = fscrypt_policy_from_context(&policy, &ctx, res);
	अगर (res) अणु
		अगर (allow_unsupported)
			वापस 0;
		fscrypt_warn(inode,
			     "Unrecognized or corrupt encryption context");
		वापस res;
	पूर्ण

	अगर (!fscrypt_supported_policy(&policy, inode)) अणु
		अगर (allow_unsupported)
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	res = fscrypt_setup_encryption_info(inode, &policy,
					    fscrypt_context_nonce(&ctx),
					    IS_CASEFOLDED(inode) &&
					    S_ISसूची(inode->i_mode));

	अगर (res == -ENOPKG && allow_unsupported) /* Algorithm unavailable? */
		res = 0;
	अगर (res == -ENOKEY)
		res = 0;
	वापस res;
पूर्ण

/**
 * fscrypt_prepare_new_inode() - prepare to create a new inode in a directory
 * @dir: a possibly-encrypted directory
 * @inode: the new inode.  ->i_mode must be set alपढ़ोy.
 *	   ->i_ino करोesn't need to be set yet.
 * @encrypt_ret: (output) set to %true अगर the new inode will be encrypted
 *
 * If the directory is encrypted, set up its ->i_crypt_info in preparation क्रम
 * encrypting the name of the new file.  Also, अगर the new inode will be
 * encrypted, set up its ->i_crypt_info and set *encrypt_ret=true.
 *
 * This isn't %GFP_NOFS-safe, and thereक्रमe it should be called beक्रमe starting
 * any fileप्रणाली transaction to create the inode.  For this reason, ->i_ino
 * isn't required to be set yet, as the fileप्रणाली may not have set it yet.
 *
 * This करोesn't persist the new inode's encryption context.  That still needs to
 * be करोne later by calling fscrypt_set_context().
 *
 * Return: 0 on success, -ENOKEY अगर the encryption key is missing, or another
 *	   -त्रुटि_सं code
 */
पूर्णांक fscrypt_prepare_new_inode(काष्ठा inode *dir, काष्ठा inode *inode,
			      bool *encrypt_ret)
अणु
	स्थिर जोड़ fscrypt_policy *policy;
	u8 nonce[FSCRYPT_खाता_NONCE_SIZE];

	policy = fscrypt_policy_to_inherit(dir);
	अगर (policy == शून्य)
		वापस 0;
	अगर (IS_ERR(policy))
		वापस PTR_ERR(policy);

	अगर (WARN_ON_ONCE(inode->i_mode == 0))
		वापस -EINVAL;

	/*
	 * Only regular files, directories, and symlinks are encrypted.
	 * Special files like device nodes and named pipes aren't.
	 */
	अगर (!S_ISREG(inode->i_mode) &&
	    !S_ISसूची(inode->i_mode) &&
	    !S_ISLNK(inode->i_mode))
		वापस 0;

	*encrypt_ret = true;

	get_अक्रमom_bytes(nonce, FSCRYPT_खाता_NONCE_SIZE);
	वापस fscrypt_setup_encryption_info(inode, policy, nonce,
					     IS_CASEFOLDED(dir) &&
					     S_ISसूची(inode->i_mode));
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_prepare_new_inode);

/**
 * fscrypt_put_encryption_info() - मुक्त most of an inode's fscrypt data
 * @inode: an inode being evicted
 *
 * Free the inode's fscrypt_info.  Fileप्रणालीs must call this when the inode is
 * being evicted.  An RCU grace period need not have elapsed yet.
 */
व्योम fscrypt_put_encryption_info(काष्ठा inode *inode)
अणु
	put_crypt_info(inode->i_crypt_info);
	inode->i_crypt_info = शून्य;
पूर्ण
EXPORT_SYMBOL(fscrypt_put_encryption_info);

/**
 * fscrypt_मुक्त_inode() - मुक्त an inode's fscrypt data requiring RCU delay
 * @inode: an inode being मुक्तd
 *
 * Free the inode's cached decrypted symlink target, अगर any.  Fileप्रणालीs must
 * call this after an RCU grace period, just beक्रमe they मुक्त the inode.
 */
व्योम fscrypt_मुक्त_inode(काष्ठा inode *inode)
अणु
	अगर (IS_ENCRYPTED(inode) && S_ISLNK(inode->i_mode)) अणु
		kमुक्त(inode->i_link);
		inode->i_link = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fscrypt_मुक्त_inode);

/**
 * fscrypt_drop_inode() - check whether the inode's master key has been हटाओd
 * @inode: an inode being considered क्रम eviction
 *
 * Fileप्रणालीs supporting fscrypt must call this from their ->drop_inode()
 * method so that encrypted inodes are evicted as soon as they're no दीर्घer in
 * use and their master key has been हटाओd.
 *
 * Return: 1 अगर fscrypt wants the inode to be evicted now, otherwise 0
 */
पूर्णांक fscrypt_drop_inode(काष्ठा inode *inode)
अणु
	स्थिर काष्ठा fscrypt_info *ci = fscrypt_get_info(inode);
	स्थिर काष्ठा fscrypt_master_key *mk;

	/*
	 * If ci is शून्य, then the inode करोesn't have an encryption key set up
	 * so it's irrelevant.  If ci_master_key is शून्य, then the master key
	 * was provided via the legacy mechanism of the process-subscribed
	 * keyrings, so we करोn't know whether it's been हटाओd or not.
	 */
	अगर (!ci || !ci->ci_master_key)
		वापस 0;
	mk = ci->ci_master_key->payload.data[0];

	/*
	 * With proper, non-racy use of FS_IOC_REMOVE_ENCRYPTION_KEY, all inodes
	 * रक्षित by the key were cleaned by sync_fileप्रणाली().  But अगर
	 * userspace is still using the files, inodes can be dirtied between
	 * then and now.  We mustn't lose any ग_लिखोs, so skip dirty inodes here.
	 */
	अगर (inode->i_state & I_सूचीTY_ALL)
		वापस 0;

	/*
	 * Note: since we aren't holding the key semaphore, the result here can
	 * immediately become outdated.  But there's no correctness problem with
	 * unnecessarily evicting.  Nor is there a correctness problem with not
	 * evicting जबतक iput() is racing with the key being हटाओd, since
	 * then the thपढ़ो removing the key will either evict the inode itself
	 * or will correctly detect that it wasn't evicted due to the race.
	 */
	वापस !is_master_key_secret_present(&mk->mk_secret);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_drop_inode);
