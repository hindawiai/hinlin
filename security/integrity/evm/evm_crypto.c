<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2010 IBM Corporation
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * File: evm_crypto.c
 *	 Using root's kernel master key (kmk), calculate the HMAC
 */

#समावेश <linux/export.h>
#समावेश <linux/crypto.h>
#समावेश <linux/xattr.h>
#समावेश <linux/evm.h>
#समावेश <keys/encrypted-type.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/hash_info.h>
#समावेश "evm.h"

#घोषणा EVMKEY "evm-key"
#घोषणा MAX_KEY_SIZE 128
अटल अचिन्हित अक्षर evmkey[MAX_KEY_SIZE];
अटल स्थिर पूर्णांक evmkey_len = MAX_KEY_SIZE;

काष्ठा crypto_shash *hmac_tfm;
अटल काष्ठा crypto_shash *evm_tfm[HASH_ALGO__LAST];

अटल DEFINE_MUTEX(mutex);

#घोषणा EVM_SET_KEY_BUSY 0

अटल अचिन्हित दीर्घ evm_set_key_flags;

अटल स्थिर अक्षर evm_hmac[] = "hmac(sha1)";

/**
 * evm_set_key() - set EVM HMAC key from the kernel
 * @key: poपूर्णांकer to a buffer with the key data
 * @size: length of the key data
 *
 * This function allows setting the EVM HMAC key from the kernel
 * without using the "encrypted" key subप्रणाली keys. It can be used
 * by the crypto HW kernel module which has its own way of managing
 * keys.
 *
 * key length should be between 32 and 128 bytes दीर्घ
 */
पूर्णांक evm_set_key(व्योम *key, माप_प्रकार keylen)
अणु
	पूर्णांक rc;

	rc = -EBUSY;
	अगर (test_and_set_bit(EVM_SET_KEY_BUSY, &evm_set_key_flags))
		जाओ busy;
	rc = -EINVAL;
	अगर (keylen > MAX_KEY_SIZE)
		जाओ inval;
	स_नकल(evmkey, key, keylen);
	evm_initialized |= EVM_INIT_HMAC;
	pr_info("key initialized\n");
	वापस 0;
inval:
	clear_bit(EVM_SET_KEY_BUSY, &evm_set_key_flags);
busy:
	pr_err("key initialization failed\n");
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(evm_set_key);

अटल काष्ठा shash_desc *init_desc(अक्षर type, uपूर्णांक8_t hash_algo)
अणु
	दीर्घ rc;
	स्थिर अक्षर *algo;
	काष्ठा crypto_shash **tfm, *पंचांगp_tfm = शून्य;
	काष्ठा shash_desc *desc;

	अगर (type == EVM_XATTR_HMAC) अणु
		अगर (!(evm_initialized & EVM_INIT_HMAC)) अणु
			pr_err_once("HMAC key is not set\n");
			वापस ERR_PTR(-ENOKEY);
		पूर्ण
		tfm = &hmac_tfm;
		algo = evm_hmac;
	पूर्ण अन्यथा अणु
		अगर (hash_algo >= HASH_ALGO__LAST)
			वापस ERR_PTR(-EINVAL);

		tfm = &evm_tfm[hash_algo];
		algo = hash_algo_name[hash_algo];
	पूर्ण

	अगर (*tfm)
		जाओ alloc;
	mutex_lock(&mutex);
	अगर (*tfm)
		जाओ unlock;

	पंचांगp_tfm = crypto_alloc_shash(algo, 0, CRYPTO_NOLOAD);
	अगर (IS_ERR(पंचांगp_tfm)) अणु
		pr_err("Can not allocate %s (reason: %ld)\n", algo,
		       PTR_ERR(पंचांगp_tfm));
		mutex_unlock(&mutex);
		वापस ERR_CAST(पंचांगp_tfm);
	पूर्ण
	अगर (type == EVM_XATTR_HMAC) अणु
		rc = crypto_shash_setkey(पंचांगp_tfm, evmkey, evmkey_len);
		अगर (rc) अणु
			crypto_मुक्त_shash(पंचांगp_tfm);
			mutex_unlock(&mutex);
			वापस ERR_PTR(rc);
		पूर्ण
	पूर्ण
	*tfm = पंचांगp_tfm;
unlock:
	mutex_unlock(&mutex);
alloc:
	desc = kदो_स्मृति(माप(*desc) + crypto_shash_descsize(*tfm),
			GFP_KERNEL);
	अगर (!desc) अणु
		crypto_मुक्त_shash(पंचांगp_tfm);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	desc->tfm = *tfm;

	rc = crypto_shash_init(desc);
	अगर (rc) अणु
		crypto_मुक्त_shash(पंचांगp_tfm);
		kमुक्त(desc);
		वापस ERR_PTR(rc);
	पूर्ण
	वापस desc;
पूर्ण

/* Protect against 'cutting & pasting' security.evm xattr, include inode
 * specअगरic info.
 *
 * (Additional directory/file metadata needs to be added क्रम more complete
 * protection.)
 */
अटल व्योम hmac_add_misc(काष्ठा shash_desc *desc, काष्ठा inode *inode,
			  अक्षर type, अक्षर *digest)
अणु
	काष्ठा h_misc अणु
		अचिन्हित दीर्घ ino;
		__u32 generation;
		uid_t uid;
		gid_t gid;
		umode_t mode;
	पूर्ण hmac_misc;

	स_रखो(&hmac_misc, 0, माप(hmac_misc));
	/* Don't include the inode or generation number in portable
	 * signatures
	 */
	अगर (type != EVM_XATTR_PORTABLE_DIGSIG) अणु
		hmac_misc.ino = inode->i_ino;
		hmac_misc.generation = inode->i_generation;
	पूर्ण
	/* The hmac uid and gid must be encoded in the initial user
	 * namespace (not the fileप्रणालीs user namespace) as encoding
	 * them in the fileप्रणालीs user namespace allows an attack
	 * where first they are written in an unprivileged fuse mount
	 * of a fileप्रणाली and then the प्रणाली is tricked to mount the
	 * fileप्रणाली क्रम real on next boot and trust it because
	 * everything is चिन्हित.
	 */
	hmac_misc.uid = from_kuid(&init_user_ns, inode->i_uid);
	hmac_misc.gid = from_kgid(&init_user_ns, inode->i_gid);
	hmac_misc.mode = inode->i_mode;
	crypto_shash_update(desc, (स्थिर u8 *)&hmac_misc, माप(hmac_misc));
	अगर ((evm_hmac_attrs & EVM_ATTR_FSUUID) &&
	    type != EVM_XATTR_PORTABLE_DIGSIG)
		crypto_shash_update(desc, (u8 *)&inode->i_sb->s_uuid, UUID_SIZE);
	crypto_shash_final(desc, digest);
पूर्ण

/*
 * Calculate the HMAC value across the set of रक्षित security xattrs.
 *
 * Instead of retrieving the requested xattr, क्रम perक्रमmance, calculate
 * the hmac using the requested xattr value. Don't alloc/मुक्त memory क्रम
 * each xattr, but attempt to re-use the previously allocated memory.
 */
अटल पूर्णांक evm_calc_hmac_or_hash(काष्ठा dentry *dentry,
				 स्थिर अक्षर *req_xattr_name,
				 स्थिर अक्षर *req_xattr_value,
				 माप_प्रकार req_xattr_value_len,
				 uपूर्णांक8_t type, काष्ठा evm_digest *data)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा xattr_list *xattr;
	काष्ठा shash_desc *desc;
	माप_प्रकार xattr_size = 0;
	अक्षर *xattr_value = शून्य;
	पूर्णांक error;
	पूर्णांक size;
	bool ima_present = false;

	अगर (!(inode->i_opflags & IOP_XATTR) ||
	    inode->i_sb->s_user_ns != &init_user_ns)
		वापस -EOPNOTSUPP;

	desc = init_desc(type, data->hdr.algo);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	data->hdr.length = crypto_shash_digestsize(desc->tfm);

	error = -ENODATA;
	list_क्रम_each_entry_lockless(xattr, &evm_config_xattrnames, list) अणु
		bool is_ima = false;

		अगर (म_भेद(xattr->name, XATTR_NAME_IMA) == 0)
			is_ima = true;

		अगर ((req_xattr_name && req_xattr_value)
		    && !म_भेद(xattr->name, req_xattr_name)) अणु
			error = 0;
			crypto_shash_update(desc, (स्थिर u8 *)req_xattr_value,
					     req_xattr_value_len);
			अगर (is_ima)
				ima_present = true;
			जारी;
		पूर्ण
		size = vfs_getxattr_alloc(&init_user_ns, dentry, xattr->name,
					  &xattr_value, xattr_size, GFP_NOFS);
		अगर (size == -ENOMEM) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		अगर (size < 0)
			जारी;

		error = 0;
		xattr_size = size;
		crypto_shash_update(desc, (स्थिर u8 *)xattr_value, xattr_size);
		अगर (is_ima)
			ima_present = true;
	पूर्ण
	hmac_add_misc(desc, inode, type, data->digest);

	/* Portable EVM signatures must include an IMA hash */
	अगर (type == EVM_XATTR_PORTABLE_DIGSIG && !ima_present)
		error = -EPERM;
out:
	kमुक्त(xattr_value);
	kमुक्त(desc);
	वापस error;
पूर्ण

पूर्णांक evm_calc_hmac(काष्ठा dentry *dentry, स्थिर अक्षर *req_xattr_name,
		  स्थिर अक्षर *req_xattr_value, माप_प्रकार req_xattr_value_len,
		  काष्ठा evm_digest *data)
अणु
	वापस evm_calc_hmac_or_hash(dentry, req_xattr_name, req_xattr_value,
				    req_xattr_value_len, EVM_XATTR_HMAC, data);
पूर्ण

पूर्णांक evm_calc_hash(काष्ठा dentry *dentry, स्थिर अक्षर *req_xattr_name,
		  स्थिर अक्षर *req_xattr_value, माप_प्रकार req_xattr_value_len,
		  अक्षर type, काष्ठा evm_digest *data)
अणु
	वापस evm_calc_hmac_or_hash(dentry, req_xattr_name, req_xattr_value,
				     req_xattr_value_len, type, data);
पूर्ण

अटल पूर्णांक evm_is_immutable(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	स्थिर काष्ठा evm_ima_xattr_data *xattr_data = शून्य;
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;
	पूर्णांक rc = 0;

	iपूर्णांक = पूर्णांकegrity_iपूर्णांक_find(inode);
	अगर (iपूर्णांक && (iपूर्णांक->flags & EVM_IMMUTABLE_DIGSIG))
		वापस 1;

	/* Do this the hard way */
	rc = vfs_getxattr_alloc(&init_user_ns, dentry, XATTR_NAME_EVM,
				(अक्षर **)&xattr_data, 0, GFP_NOFS);
	अगर (rc <= 0) अणु
		अगर (rc == -ENODATA)
			वापस 0;
		वापस rc;
	पूर्ण
	अगर (xattr_data->type == EVM_XATTR_PORTABLE_DIGSIG)
		rc = 1;
	अन्यथा
		rc = 0;

	kमुक्त(xattr_data);
	वापस rc;
पूर्ण


/*
 * Calculate the hmac and update security.evm xattr
 *
 * Expects to be called with i_mutex locked.
 */
पूर्णांक evm_update_evmxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name,
			स्थिर अक्षर *xattr_value, माप_प्रकार xattr_value_len)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा evm_digest data;
	पूर्णांक rc = 0;

	/*
	 * Don't permit any transक्रमmation of the EVM xattr अगर the signature
	 * is of an immutable type
	 */
	rc = evm_is_immutable(dentry, inode);
	अगर (rc < 0)
		वापस rc;
	अगर (rc)
		वापस -EPERM;

	data.hdr.algo = HASH_ALGO_SHA1;
	rc = evm_calc_hmac(dentry, xattr_name, xattr_value,
			   xattr_value_len, &data);
	अगर (rc == 0) अणु
		data.hdr.xattr.sha1.type = EVM_XATTR_HMAC;
		rc = __vfs_setxattr_noperm(&init_user_ns, dentry,
					   XATTR_NAME_EVM,
					   &data.hdr.xattr.data[1],
					   SHA1_DIGEST_SIZE + 1, 0);
	पूर्ण अन्यथा अगर (rc == -ENODATA && (inode->i_opflags & IOP_XATTR)) अणु
		rc = __vfs_हटाओxattr(&init_user_ns, dentry, XATTR_NAME_EVM);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक evm_init_hmac(काष्ठा inode *inode, स्थिर काष्ठा xattr *lsm_xattr,
		  अक्षर *hmac_val)
अणु
	काष्ठा shash_desc *desc;

	desc = init_desc(EVM_XATTR_HMAC, HASH_ALGO_SHA1);
	अगर (IS_ERR(desc)) अणु
		pr_info("init_desc failed\n");
		वापस PTR_ERR(desc);
	पूर्ण

	crypto_shash_update(desc, lsm_xattr->value, lsm_xattr->value_len);
	hmac_add_misc(desc, inode, EVM_XATTR_HMAC, hmac_val);
	kमुक्त(desc);
	वापस 0;
पूर्ण

/*
 * Get the key from the TPM क्रम the SHA1-HMAC
 */
पूर्णांक evm_init_key(व्योम)
अणु
	काष्ठा key *evm_key;
	काष्ठा encrypted_key_payload *ekp;
	पूर्णांक rc;

	evm_key = request_key(&key_type_encrypted, EVMKEY, शून्य);
	अगर (IS_ERR(evm_key))
		वापस -ENOENT;

	करोwn_पढ़ो(&evm_key->sem);
	ekp = evm_key->payload.data[0];

	rc = evm_set_key(ekp->decrypted_data, ekp->decrypted_datalen);

	/* burn the original key contents */
	स_रखो(ekp->decrypted_data, 0, ekp->decrypted_datalen);
	up_पढ़ो(&evm_key->sem);
	key_put(evm_key);
	वापस rc;
पूर्ण
