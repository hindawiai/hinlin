<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 IBM Corporation
 * Copyright (C) 2010 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 * Roberto Sassu <roberto.sassu@polito.it>
 *
 * See Documentation/security/keys/trusted-encrypted.rst
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/parser.h>
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <keys/user-type.h>
#समावेश <keys/trusted-type.h>
#समावेश <keys/encrypted-type.h>
#समावेश <linux/key-type.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/प्रकार.स>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/skcipher.h>

#समावेश "encrypted.h"
#समावेश "ecryptfs_format.h"

अटल स्थिर अक्षर KEY_TRUSTED_PREFIX[] = "trusted:";
अटल स्थिर अक्षर KEY_USER_PREFIX[] = "user:";
अटल स्थिर अक्षर hash_alg[] = "sha256";
अटल स्थिर अक्षर hmac_alg[] = "hmac(sha256)";
अटल स्थिर अक्षर blkcipher_alg[] = "cbc(aes)";
अटल स्थिर अक्षर key_क्रमmat_शेष[] = "default";
अटल स्थिर अक्षर key_क्रमmat_ecryptfs[] = "ecryptfs";
अटल स्थिर अक्षर key_क्रमmat_enc32[] = "enc32";
अटल अचिन्हित पूर्णांक ivsize;
अटल पूर्णांक blksize;

#घोषणा KEY_TRUSTED_PREFIX_LEN (माप (KEY_TRUSTED_PREFIX) - 1)
#घोषणा KEY_USER_PREFIX_LEN (माप (KEY_USER_PREFIX) - 1)
#घोषणा KEY_ECRYPTFS_DESC_LEN 16
#घोषणा HASH_SIZE SHA256_DIGEST_SIZE
#घोषणा MAX_DATA_SIZE 4096
#घोषणा MIN_DATA_SIZE  20
#घोषणा KEY_ENC32_PAYLOAD_LEN 32

अटल काष्ठा crypto_shash *hash_tfm;

क्रमागत अणु
	Opt_new, Opt_load, Opt_update, Opt_err
पूर्ण;

क्रमागत अणु
	Opt_शेष, Opt_ecryptfs, Opt_enc32, Opt_error
पूर्ण;

अटल स्थिर match_table_t key_क्रमmat_tokens = अणु
	अणुOpt_शेष, "default"पूर्ण,
	अणुOpt_ecryptfs, "ecryptfs"पूर्ण,
	अणुOpt_enc32, "enc32"पूर्ण,
	अणुOpt_error, शून्यपूर्ण
पूर्ण;

अटल स्थिर match_table_t key_tokens = अणु
	अणुOpt_new, "new"पूर्ण,
	अणुOpt_load, "load"पूर्ण,
	अणुOpt_update, "update"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक aes_get_sizes(व्योम)
अणु
	काष्ठा crypto_skcipher *tfm;

	tfm = crypto_alloc_skcipher(blkcipher_alg, 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm)) अणु
		pr_err("encrypted_key: failed to alloc_cipher (%ld)\n",
		       PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण
	ivsize = crypto_skcipher_ivsize(tfm);
	blksize = crypto_skcipher_blocksize(tfm);
	crypto_मुक्त_skcipher(tfm);
	वापस 0;
पूर्ण

/*
 * valid_ecryptfs_desc - verअगरy the description of a new/loaded encrypted key
 *
 * The description of a encrypted key with क्रमmat 'ecryptfs' must contain
 * exactly 16 hexadecimal अक्षरacters.
 *
 */
अटल पूर्णांक valid_ecryptfs_desc(स्थिर अक्षर *ecryptfs_desc)
अणु
	पूर्णांक i;

	अगर (म_माप(ecryptfs_desc) != KEY_ECRYPTFS_DESC_LEN) अणु
		pr_err("encrypted_key: key description must be %d hexadecimal "
		       "characters long\n", KEY_ECRYPTFS_DESC_LEN);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < KEY_ECRYPTFS_DESC_LEN; i++) अणु
		अगर (!है_षष्ठादशक(ecryptfs_desc[i])) अणु
			pr_err("encrypted_key: key description must contain "
			       "only hexadecimal characters\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * valid_master_desc - verअगरy the 'key-type:desc' of a new/updated master-key
 *
 * key-type:= "trusted:" | "user:"
 * desc:= master-key description
 *
 * Verअगरy that 'key-type' is valid and that 'desc' exists. On key update,
 * only the master key description is permitted to change, not the key-type.
 * The key-type reमुख्यs स्थिरant.
 *
 * On success वापसs 0, otherwise -EINVAL.
 */
अटल पूर्णांक valid_master_desc(स्थिर अक्षर *new_desc, स्थिर अक्षर *orig_desc)
अणु
	पूर्णांक prefix_len;

	अगर (!म_भेदन(new_desc, KEY_TRUSTED_PREFIX, KEY_TRUSTED_PREFIX_LEN))
		prefix_len = KEY_TRUSTED_PREFIX_LEN;
	अन्यथा अगर (!म_भेदन(new_desc, KEY_USER_PREFIX, KEY_USER_PREFIX_LEN))
		prefix_len = KEY_USER_PREFIX_LEN;
	अन्यथा
		वापस -EINVAL;

	अगर (!new_desc[prefix_len])
		वापस -EINVAL;

	अगर (orig_desc && म_भेदन(new_desc, orig_desc, prefix_len))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * datablob_parse - parse the keyctl data
 *
 * datablob क्रमmat:
 * new [<क्रमmat>] <master-key name> <decrypted data length>
 * load [<क्रमmat>] <master-key name> <decrypted data length>
 *     <encrypted iv + data>
 * update <new-master-key name>
 *
 * Tokenizes a copy of the keyctl data, वापसing a poपूर्णांकer to each token,
 * which is null terminated.
 *
 * On success वापसs 0, otherwise -EINVAL.
 */
अटल पूर्णांक datablob_parse(अक्षर *datablob, स्थिर अक्षर **क्रमmat,
			  अक्षर **master_desc, अक्षर **decrypted_datalen,
			  अक्षर **hex_encoded_iv)
अणु
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक ret = -EINVAL;
	पूर्णांक key_cmd;
	पूर्णांक key_क्रमmat;
	अक्षर *p, *keyword;

	keyword = strsep(&datablob, " \t");
	अगर (!keyword) अणु
		pr_info("encrypted_key: insufficient parameters specified\n");
		वापस ret;
	पूर्ण
	key_cmd = match_token(keyword, key_tokens, args);

	/* Get optional क्रमmat: शेष | ecryptfs */
	p = strsep(&datablob, " \t");
	अगर (!p) अणु
		pr_err("encrypted_key: insufficient parameters specified\n");
		वापस ret;
	पूर्ण

	key_क्रमmat = match_token(p, key_क्रमmat_tokens, args);
	चयन (key_क्रमmat) अणु
	हाल Opt_ecryptfs:
	हाल Opt_enc32:
	हाल Opt_शेष:
		*क्रमmat = p;
		*master_desc = strsep(&datablob, " \t");
		अवरोध;
	हाल Opt_error:
		*master_desc = p;
		अवरोध;
	पूर्ण

	अगर (!*master_desc) अणु
		pr_info("encrypted_key: master key parameter is missing\n");
		जाओ out;
	पूर्ण

	अगर (valid_master_desc(*master_desc, शून्य) < 0) अणु
		pr_info("encrypted_key: master key parameter \'%s\' "
			"is invalid\n", *master_desc);
		जाओ out;
	पूर्ण

	अगर (decrypted_datalen) अणु
		*decrypted_datalen = strsep(&datablob, " \t");
		अगर (!*decrypted_datalen) अणु
			pr_info("encrypted_key: keylen parameter is missing\n");
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (key_cmd) अणु
	हाल Opt_new:
		अगर (!decrypted_datalen) अणु
			pr_info("encrypted_key: keyword \'%s\' not allowed "
				"when called from .update method\n", keyword);
			अवरोध;
		पूर्ण
		ret = 0;
		अवरोध;
	हाल Opt_load:
		अगर (!decrypted_datalen) अणु
			pr_info("encrypted_key: keyword \'%s\' not allowed "
				"when called from .update method\n", keyword);
			अवरोध;
		पूर्ण
		*hex_encoded_iv = strsep(&datablob, " \t");
		अगर (!*hex_encoded_iv) अणु
			pr_info("encrypted_key: hex blob is missing\n");
			अवरोध;
		पूर्ण
		ret = 0;
		अवरोध;
	हाल Opt_update:
		अगर (decrypted_datalen) अणु
			pr_info("encrypted_key: keyword \'%s\' not allowed "
				"when called from .instantiate method\n",
				keyword);
			अवरोध;
		पूर्ण
		ret = 0;
		अवरोध;
	हाल Opt_err:
		pr_info("encrypted_key: keyword \'%s\' not recognized\n",
			keyword);
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * datablob_क्रमmat - क्रमmat as an ascii string, beक्रमe copying to userspace
 */
अटल अक्षर *datablob_क्रमmat(काष्ठा encrypted_key_payload *epayload,
			     माप_प्रकार asciiblob_len)
अणु
	अक्षर *ascii_buf, *bufp;
	u8 *iv = epayload->iv;
	पूर्णांक len;
	पूर्णांक i;

	ascii_buf = kदो_स्मृति(asciiblob_len + 1, GFP_KERNEL);
	अगर (!ascii_buf)
		जाओ out;

	ascii_buf[asciiblob_len] = '\0';

	/* copy datablob master_desc and datalen strings */
	len = प्र_लिखो(ascii_buf, "%s %s %s ", epayload->क्रमmat,
		      epayload->master_desc, epayload->datalen);

	/* convert the hex encoded iv, encrypted-data and HMAC to ascii */
	bufp = &ascii_buf[len];
	क्रम (i = 0; i < (asciiblob_len - len) / 2; i++)
		bufp = hex_byte_pack(bufp, iv[i]);
out:
	वापस ascii_buf;
पूर्ण

/*
 * request_user_key - request the user key
 *
 * Use a user provided key to encrypt/decrypt an encrypted-key.
 */
अटल काष्ठा key *request_user_key(स्थिर अक्षर *master_desc, स्थिर u8 **master_key,
				    माप_प्रकार *master_keylen)
अणु
	स्थिर काष्ठा user_key_payload *upayload;
	काष्ठा key *ukey;

	ukey = request_key(&key_type_user, master_desc, शून्य);
	अगर (IS_ERR(ukey))
		जाओ error;

	करोwn_पढ़ो(&ukey->sem);
	upayload = user_key_payload_locked(ukey);
	अगर (!upayload) अणु
		/* key was revoked beक्रमe we acquired its semaphore */
		up_पढ़ो(&ukey->sem);
		key_put(ukey);
		ukey = ERR_PTR(-EKEYREVOKED);
		जाओ error;
	पूर्ण
	*master_key = upayload->data;
	*master_keylen = upayload->datalen;
error:
	वापस ukey;
पूर्ण

अटल पूर्णांक calc_hmac(u8 *digest, स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
		     स्थिर u8 *buf, अचिन्हित पूर्णांक buflen)
अणु
	काष्ठा crypto_shash *tfm;
	पूर्णांक err;

	tfm = crypto_alloc_shash(hmac_alg, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_err("encrypted_key: can't alloc %s transform: %ld\n",
		       hmac_alg, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण

	err = crypto_shash_setkey(tfm, key, keylen);
	अगर (!err)
		err = crypto_shash_tfm_digest(tfm, buf, buflen, digest);
	crypto_मुक्त_shash(tfm);
	वापस err;
पूर्ण

क्रमागत derived_key_type अणु ENC_KEY, AUTH_KEY पूर्ण;

/* Derive authentication/encryption key from trusted key */
अटल पूर्णांक get_derived_key(u8 *derived_key, क्रमागत derived_key_type key_type,
			   स्थिर u8 *master_key, माप_प्रकार master_keylen)
अणु
	u8 *derived_buf;
	अचिन्हित पूर्णांक derived_buf_len;
	पूर्णांक ret;

	derived_buf_len = म_माप("AUTH_KEY") + 1 + master_keylen;
	अगर (derived_buf_len < HASH_SIZE)
		derived_buf_len = HASH_SIZE;

	derived_buf = kzalloc(derived_buf_len, GFP_KERNEL);
	अगर (!derived_buf)
		वापस -ENOMEM;

	अगर (key_type)
		म_नकल(derived_buf, "AUTH_KEY");
	अन्यथा
		म_नकल(derived_buf, "ENC_KEY");

	स_नकल(derived_buf + म_माप(derived_buf) + 1, master_key,
	       master_keylen);
	ret = crypto_shash_tfm_digest(hash_tfm, derived_buf, derived_buf_len,
				      derived_key);
	kमुक्त_sensitive(derived_buf);
	वापस ret;
पूर्ण

अटल काष्ठा skcipher_request *init_skcipher_req(स्थिर u8 *key,
						  अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा skcipher_request *req;
	काष्ठा crypto_skcipher *tfm;
	पूर्णांक ret;

	tfm = crypto_alloc_skcipher(blkcipher_alg, 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm)) अणु
		pr_err("encrypted_key: failed to load %s transform (%ld)\n",
		       blkcipher_alg, PTR_ERR(tfm));
		वापस ERR_CAST(tfm);
	पूर्ण

	ret = crypto_skcipher_setkey(tfm, key, key_len);
	अगर (ret < 0) अणु
		pr_err("encrypted_key: failed to setkey (%d)\n", ret);
		crypto_मुक्त_skcipher(tfm);
		वापस ERR_PTR(ret);
	पूर्ण

	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_err("encrypted_key: failed to allocate request for %s\n",
		       blkcipher_alg);
		crypto_मुक्त_skcipher(tfm);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	वापस req;
पूर्ण

अटल काष्ठा key *request_master_key(काष्ठा encrypted_key_payload *epayload,
				      स्थिर u8 **master_key, माप_प्रकार *master_keylen)
अणु
	काष्ठा key *mkey = ERR_PTR(-EINVAL);

	अगर (!म_भेदन(epayload->master_desc, KEY_TRUSTED_PREFIX,
		     KEY_TRUSTED_PREFIX_LEN)) अणु
		mkey = request_trusted_key(epayload->master_desc +
					   KEY_TRUSTED_PREFIX_LEN,
					   master_key, master_keylen);
	पूर्ण अन्यथा अगर (!म_भेदन(epayload->master_desc, KEY_USER_PREFIX,
			    KEY_USER_PREFIX_LEN)) अणु
		mkey = request_user_key(epayload->master_desc +
					KEY_USER_PREFIX_LEN,
					master_key, master_keylen);
	पूर्ण अन्यथा
		जाओ out;

	अगर (IS_ERR(mkey)) अणु
		पूर्णांक ret = PTR_ERR(mkey);

		अगर (ret == -ENOTSUPP)
			pr_info("encrypted_key: key %s not supported",
				epayload->master_desc);
		अन्यथा
			pr_info("encrypted_key: key %s not found",
				epayload->master_desc);
		जाओ out;
	पूर्ण

	dump_master_key(*master_key, *master_keylen);
out:
	वापस mkey;
पूर्ण

/* Beक्रमe वापसing data to userspace, encrypt decrypted data. */
अटल पूर्णांक derived_key_encrypt(काष्ठा encrypted_key_payload *epayload,
			       स्थिर u8 *derived_key,
			       अचिन्हित पूर्णांक derived_keylen)
अणु
	काष्ठा scatterlist sg_in[2];
	काष्ठा scatterlist sg_out[1];
	काष्ठा crypto_skcipher *tfm;
	काष्ठा skcipher_request *req;
	अचिन्हित पूर्णांक encrypted_datalen;
	u8 iv[AES_BLOCK_SIZE];
	पूर्णांक ret;

	encrypted_datalen = roundup(epayload->decrypted_datalen, blksize);

	req = init_skcipher_req(derived_key, derived_keylen);
	ret = PTR_ERR(req);
	अगर (IS_ERR(req))
		जाओ out;
	dump_decrypted_data(epayload);

	sg_init_table(sg_in, 2);
	sg_set_buf(&sg_in[0], epayload->decrypted_data,
		   epayload->decrypted_datalen);
	sg_set_page(&sg_in[1], ZERO_PAGE(0), AES_BLOCK_SIZE, 0);

	sg_init_table(sg_out, 1);
	sg_set_buf(sg_out, epayload->encrypted_data, encrypted_datalen);

	स_नकल(iv, epayload->iv, माप(iv));
	skcipher_request_set_crypt(req, sg_in, sg_out, encrypted_datalen, iv);
	ret = crypto_skcipher_encrypt(req);
	tfm = crypto_skcipher_reqtfm(req);
	skcipher_request_मुक्त(req);
	crypto_मुक्त_skcipher(tfm);
	अगर (ret < 0)
		pr_err("encrypted_key: failed to encrypt (%d)\n", ret);
	अन्यथा
		dump_encrypted_data(epayload, encrypted_datalen);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक datablob_hmac_append(काष्ठा encrypted_key_payload *epayload,
				स्थिर u8 *master_key, माप_प्रकार master_keylen)
अणु
	u8 derived_key[HASH_SIZE];
	u8 *digest;
	पूर्णांक ret;

	ret = get_derived_key(derived_key, AUTH_KEY, master_key, master_keylen);
	अगर (ret < 0)
		जाओ out;

	digest = epayload->क्रमmat + epayload->datablob_len;
	ret = calc_hmac(digest, derived_key, माप derived_key,
			epayload->क्रमmat, epayload->datablob_len);
	अगर (!ret)
		dump_hmac(शून्य, digest, HASH_SIZE);
out:
	memzero_explicit(derived_key, माप(derived_key));
	वापस ret;
पूर्ण

/* verअगरy HMAC beक्रमe decrypting encrypted key */
अटल पूर्णांक datablob_hmac_verअगरy(काष्ठा encrypted_key_payload *epayload,
				स्थिर u8 *क्रमmat, स्थिर u8 *master_key,
				माप_प्रकार master_keylen)
अणु
	u8 derived_key[HASH_SIZE];
	u8 digest[HASH_SIZE];
	पूर्णांक ret;
	अक्षर *p;
	अचिन्हित लघु len;

	ret = get_derived_key(derived_key, AUTH_KEY, master_key, master_keylen);
	अगर (ret < 0)
		जाओ out;

	len = epayload->datablob_len;
	अगर (!क्रमmat) अणु
		p = epayload->master_desc;
		len -= म_माप(epayload->क्रमmat) + 1;
	पूर्ण अन्यथा
		p = epayload->क्रमmat;

	ret = calc_hmac(digest, derived_key, माप derived_key, p, len);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_memneq(digest, epayload->क्रमmat + epayload->datablob_len,
			    माप(digest));
	अगर (ret) अणु
		ret = -EINVAL;
		dump_hmac("datablob",
			  epayload->क्रमmat + epayload->datablob_len,
			  HASH_SIZE);
		dump_hmac("calc", digest, HASH_SIZE);
	पूर्ण
out:
	memzero_explicit(derived_key, माप(derived_key));
	वापस ret;
पूर्ण

अटल पूर्णांक derived_key_decrypt(काष्ठा encrypted_key_payload *epayload,
			       स्थिर u8 *derived_key,
			       अचिन्हित पूर्णांक derived_keylen)
अणु
	काष्ठा scatterlist sg_in[1];
	काष्ठा scatterlist sg_out[2];
	काष्ठा crypto_skcipher *tfm;
	काष्ठा skcipher_request *req;
	अचिन्हित पूर्णांक encrypted_datalen;
	u8 iv[AES_BLOCK_SIZE];
	u8 *pad;
	पूर्णांक ret;

	/* Throwaway buffer to hold the unused zero padding at the end */
	pad = kदो_स्मृति(AES_BLOCK_SIZE, GFP_KERNEL);
	अगर (!pad)
		वापस -ENOMEM;

	encrypted_datalen = roundup(epayload->decrypted_datalen, blksize);
	req = init_skcipher_req(derived_key, derived_keylen);
	ret = PTR_ERR(req);
	अगर (IS_ERR(req))
		जाओ out;
	dump_encrypted_data(epayload, encrypted_datalen);

	sg_init_table(sg_in, 1);
	sg_init_table(sg_out, 2);
	sg_set_buf(sg_in, epayload->encrypted_data, encrypted_datalen);
	sg_set_buf(&sg_out[0], epayload->decrypted_data,
		   epayload->decrypted_datalen);
	sg_set_buf(&sg_out[1], pad, AES_BLOCK_SIZE);

	स_नकल(iv, epayload->iv, माप(iv));
	skcipher_request_set_crypt(req, sg_in, sg_out, encrypted_datalen, iv);
	ret = crypto_skcipher_decrypt(req);
	tfm = crypto_skcipher_reqtfm(req);
	skcipher_request_मुक्त(req);
	crypto_मुक्त_skcipher(tfm);
	अगर (ret < 0)
		जाओ out;
	dump_decrypted_data(epayload);
out:
	kमुक्त(pad);
	वापस ret;
पूर्ण

/* Allocate memory क्रम decrypted key and datablob. */
अटल काष्ठा encrypted_key_payload *encrypted_key_alloc(काष्ठा key *key,
							 स्थिर अक्षर *क्रमmat,
							 स्थिर अक्षर *master_desc,
							 स्थिर अक्षर *datalen)
अणु
	काष्ठा encrypted_key_payload *epayload = शून्य;
	अचिन्हित लघु datablob_len;
	अचिन्हित लघु decrypted_datalen;
	अचिन्हित लघु payload_datalen;
	अचिन्हित पूर्णांक encrypted_datalen;
	अचिन्हित पूर्णांक क्रमmat_len;
	दीर्घ dlen;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(datalen, 10, &dlen);
	अगर (ret < 0 || dlen < MIN_DATA_SIZE || dlen > MAX_DATA_SIZE)
		वापस ERR_PTR(-EINVAL);

	क्रमmat_len = (!क्रमmat) ? म_माप(key_क्रमmat_शेष) : म_माप(क्रमmat);
	decrypted_datalen = dlen;
	payload_datalen = decrypted_datalen;
	अगर (क्रमmat) अणु
		अगर (!म_भेद(क्रमmat, key_क्रमmat_ecryptfs)) अणु
			अगर (dlen != ECRYPTFS_MAX_KEY_BYTES) अणु
				pr_err("encrypted_key: keylen for the ecryptfs format must be equal to %d bytes\n",
					ECRYPTFS_MAX_KEY_BYTES);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
			decrypted_datalen = ECRYPTFS_MAX_KEY_BYTES;
			payload_datalen = माप(काष्ठा ecryptfs_auth_tok);
		पूर्ण अन्यथा अगर (!म_भेद(क्रमmat, key_क्रमmat_enc32)) अणु
			अगर (decrypted_datalen != KEY_ENC32_PAYLOAD_LEN) अणु
				pr_err("encrypted_key: enc32 key payload incorrect length: %d\n",
						decrypted_datalen);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
		पूर्ण
	पूर्ण

	encrypted_datalen = roundup(decrypted_datalen, blksize);

	datablob_len = क्रमmat_len + 1 + म_माप(master_desc) + 1
	    + म_माप(datalen) + 1 + ivsize + 1 + encrypted_datalen;

	ret = key_payload_reserve(key, payload_datalen + datablob_len
				  + HASH_SIZE + 1);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	epayload = kzalloc(माप(*epayload) + payload_datalen +
			   datablob_len + HASH_SIZE + 1, GFP_KERNEL);
	अगर (!epayload)
		वापस ERR_PTR(-ENOMEM);

	epayload->payload_datalen = payload_datalen;
	epayload->decrypted_datalen = decrypted_datalen;
	epayload->datablob_len = datablob_len;
	वापस epayload;
पूर्ण

अटल पूर्णांक encrypted_key_decrypt(काष्ठा encrypted_key_payload *epayload,
				 स्थिर अक्षर *क्रमmat, स्थिर अक्षर *hex_encoded_iv)
अणु
	काष्ठा key *mkey;
	u8 derived_key[HASH_SIZE];
	स्थिर u8 *master_key;
	u8 *hmac;
	स्थिर अक्षर *hex_encoded_data;
	अचिन्हित पूर्णांक encrypted_datalen;
	माप_प्रकार master_keylen;
	माप_प्रकार asciilen;
	पूर्णांक ret;

	encrypted_datalen = roundup(epayload->decrypted_datalen, blksize);
	asciilen = (ivsize + 1 + encrypted_datalen + HASH_SIZE) * 2;
	अगर (म_माप(hex_encoded_iv) != asciilen)
		वापस -EINVAL;

	hex_encoded_data = hex_encoded_iv + (2 * ivsize) + 2;
	ret = hex2bin(epayload->iv, hex_encoded_iv, ivsize);
	अगर (ret < 0)
		वापस -EINVAL;
	ret = hex2bin(epayload->encrypted_data, hex_encoded_data,
		      encrypted_datalen);
	अगर (ret < 0)
		वापस -EINVAL;

	hmac = epayload->क्रमmat + epayload->datablob_len;
	ret = hex2bin(hmac, hex_encoded_data + (encrypted_datalen * 2),
		      HASH_SIZE);
	अगर (ret < 0)
		वापस -EINVAL;

	mkey = request_master_key(epayload, &master_key, &master_keylen);
	अगर (IS_ERR(mkey))
		वापस PTR_ERR(mkey);

	ret = datablob_hmac_verअगरy(epayload, क्रमmat, master_key, master_keylen);
	अगर (ret < 0) अणु
		pr_err("encrypted_key: bad hmac (%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = get_derived_key(derived_key, ENC_KEY, master_key, master_keylen);
	अगर (ret < 0)
		जाओ out;

	ret = derived_key_decrypt(epayload, derived_key, माप derived_key);
	अगर (ret < 0)
		pr_err("encrypted_key: failed to decrypt key (%d)\n", ret);
out:
	up_पढ़ो(&mkey->sem);
	key_put(mkey);
	memzero_explicit(derived_key, माप(derived_key));
	वापस ret;
पूर्ण

अटल व्योम __ekey_init(काष्ठा encrypted_key_payload *epayload,
			स्थिर अक्षर *क्रमmat, स्थिर अक्षर *master_desc,
			स्थिर अक्षर *datalen)
अणु
	अचिन्हित पूर्णांक क्रमmat_len;

	क्रमmat_len = (!क्रमmat) ? म_माप(key_क्रमmat_शेष) : म_माप(क्रमmat);
	epayload->क्रमmat = epayload->payload_data + epayload->payload_datalen;
	epayload->master_desc = epayload->क्रमmat + क्रमmat_len + 1;
	epayload->datalen = epayload->master_desc + म_माप(master_desc) + 1;
	epayload->iv = epayload->datalen + म_माप(datalen) + 1;
	epayload->encrypted_data = epayload->iv + ivsize + 1;
	epayload->decrypted_data = epayload->payload_data;

	अगर (!क्रमmat)
		स_नकल(epayload->क्रमmat, key_क्रमmat_शेष, क्रमmat_len);
	अन्यथा अणु
		अगर (!म_भेद(क्रमmat, key_क्रमmat_ecryptfs))
			epayload->decrypted_data =
				ecryptfs_get_auth_tok_key((काष्ठा ecryptfs_auth_tok *)epayload->payload_data);

		स_नकल(epayload->क्रमmat, क्रमmat, क्रमmat_len);
	पूर्ण

	स_नकल(epayload->master_desc, master_desc, म_माप(master_desc));
	स_नकल(epayload->datalen, datalen, म_माप(datalen));
पूर्ण

/*
 * encrypted_init - initialize an encrypted key
 *
 * For a new key, use a अक्रमom number क्रम both the iv and data
 * itself.  For an old key, decrypt the hex encoded data.
 */
अटल पूर्णांक encrypted_init(काष्ठा encrypted_key_payload *epayload,
			  स्थिर अक्षर *key_desc, स्थिर अक्षर *क्रमmat,
			  स्थिर अक्षर *master_desc, स्थिर अक्षर *datalen,
			  स्थिर अक्षर *hex_encoded_iv)
अणु
	पूर्णांक ret = 0;

	अगर (क्रमmat && !म_भेद(क्रमmat, key_क्रमmat_ecryptfs)) अणु
		ret = valid_ecryptfs_desc(key_desc);
		अगर (ret < 0)
			वापस ret;

		ecryptfs_fill_auth_tok((काष्ठा ecryptfs_auth_tok *)epayload->payload_data,
				       key_desc);
	पूर्ण

	__ekey_init(epayload, क्रमmat, master_desc, datalen);
	अगर (!hex_encoded_iv) अणु
		get_अक्रमom_bytes(epayload->iv, ivsize);

		get_अक्रमom_bytes(epayload->decrypted_data,
				 epayload->decrypted_datalen);
	पूर्ण अन्यथा
		ret = encrypted_key_decrypt(epayload, क्रमmat, hex_encoded_iv);
	वापस ret;
पूर्ण

/*
 * encrypted_instantiate - instantiate an encrypted key
 *
 * Decrypt an existing encrypted datablob or create a new encrypted key
 * based on a kernel अक्रमom number.
 *
 * On success, वापस 0. Otherwise वापस त्रुटि_सं.
 */
अटल पूर्णांक encrypted_instantiate(काष्ठा key *key,
				 काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा encrypted_key_payload *epayload = शून्य;
	अक्षर *datablob = शून्य;
	स्थिर अक्षर *क्रमmat = शून्य;
	अक्षर *master_desc = शून्य;
	अक्षर *decrypted_datalen = शून्य;
	अक्षर *hex_encoded_iv = शून्य;
	माप_प्रकार datalen = prep->datalen;
	पूर्णांक ret;

	अगर (datalen <= 0 || datalen > 32767 || !prep->data)
		वापस -EINVAL;

	datablob = kदो_स्मृति(datalen + 1, GFP_KERNEL);
	अगर (!datablob)
		वापस -ENOMEM;
	datablob[datalen] = 0;
	स_नकल(datablob, prep->data, datalen);
	ret = datablob_parse(datablob, &क्रमmat, &master_desc,
			     &decrypted_datalen, &hex_encoded_iv);
	अगर (ret < 0)
		जाओ out;

	epayload = encrypted_key_alloc(key, क्रमmat, master_desc,
				       decrypted_datalen);
	अगर (IS_ERR(epayload)) अणु
		ret = PTR_ERR(epayload);
		जाओ out;
	पूर्ण
	ret = encrypted_init(epayload, key->description, क्रमmat, master_desc,
			     decrypted_datalen, hex_encoded_iv);
	अगर (ret < 0) अणु
		kमुक्त_sensitive(epayload);
		जाओ out;
	पूर्ण

	rcu_assign_keypoपूर्णांकer(key, epayload);
out:
	kमुक्त_sensitive(datablob);
	वापस ret;
पूर्ण

अटल व्योम encrypted_rcu_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा encrypted_key_payload *epayload;

	epayload = container_of(rcu, काष्ठा encrypted_key_payload, rcu);
	kमुक्त_sensitive(epayload);
पूर्ण

/*
 * encrypted_update - update the master key description
 *
 * Change the master key description क्रम an existing encrypted key.
 * The next पढ़ो will वापस an encrypted datablob using the new
 * master key description.
 *
 * On success, वापस 0. Otherwise वापस त्रुटि_सं.
 */
अटल पूर्णांक encrypted_update(काष्ठा key *key, काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा encrypted_key_payload *epayload = key->payload.data[0];
	काष्ठा encrypted_key_payload *new_epayload;
	अक्षर *buf;
	अक्षर *new_master_desc = शून्य;
	स्थिर अक्षर *क्रमmat = शून्य;
	माप_प्रकार datalen = prep->datalen;
	पूर्णांक ret = 0;

	अगर (key_is_negative(key))
		वापस -ENOKEY;
	अगर (datalen <= 0 || datalen > 32767 || !prep->data)
		वापस -EINVAL;

	buf = kदो_स्मृति(datalen + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[datalen] = 0;
	स_नकल(buf, prep->data, datalen);
	ret = datablob_parse(buf, &क्रमmat, &new_master_desc, शून्य, शून्य);
	अगर (ret < 0)
		जाओ out;

	ret = valid_master_desc(new_master_desc, epayload->master_desc);
	अगर (ret < 0)
		जाओ out;

	new_epayload = encrypted_key_alloc(key, epayload->क्रमmat,
					   new_master_desc, epayload->datalen);
	अगर (IS_ERR(new_epayload)) अणु
		ret = PTR_ERR(new_epayload);
		जाओ out;
	पूर्ण

	__ekey_init(new_epayload, epayload->क्रमmat, new_master_desc,
		    epayload->datalen);

	स_नकल(new_epayload->iv, epayload->iv, ivsize);
	स_नकल(new_epayload->payload_data, epayload->payload_data,
	       epayload->payload_datalen);

	rcu_assign_keypoपूर्णांकer(key, new_epayload);
	call_rcu(&epayload->rcu, encrypted_rcu_मुक्त);
out:
	kमुक्त_sensitive(buf);
	वापस ret;
पूर्ण

/*
 * encrypted_पढ़ो - क्रमmat and copy out the encrypted data
 *
 * The resulting datablob क्रमmat is:
 * <master-key name> <decrypted data length> <encrypted iv> <encrypted data>
 *
 * On success, वापस to userspace the encrypted key datablob size.
 */
अटल दीर्घ encrypted_पढ़ो(स्थिर काष्ठा key *key, अक्षर *buffer,
			   माप_प्रकार buflen)
अणु
	काष्ठा encrypted_key_payload *epayload;
	काष्ठा key *mkey;
	स्थिर u8 *master_key;
	माप_प्रकार master_keylen;
	अक्षर derived_key[HASH_SIZE];
	अक्षर *ascii_buf;
	माप_प्रकार asciiblob_len;
	पूर्णांक ret;

	epayload = dereference_key_locked(key);

	/* वापसs the hex encoded iv, encrypted-data, and hmac as ascii */
	asciiblob_len = epayload->datablob_len + ivsize + 1
	    + roundup(epayload->decrypted_datalen, blksize)
	    + (HASH_SIZE * 2);

	अगर (!buffer || buflen < asciiblob_len)
		वापस asciiblob_len;

	mkey = request_master_key(epayload, &master_key, &master_keylen);
	अगर (IS_ERR(mkey))
		वापस PTR_ERR(mkey);

	ret = get_derived_key(derived_key, ENC_KEY, master_key, master_keylen);
	अगर (ret < 0)
		जाओ out;

	ret = derived_key_encrypt(epayload, derived_key, माप derived_key);
	अगर (ret < 0)
		जाओ out;

	ret = datablob_hmac_append(epayload, master_key, master_keylen);
	अगर (ret < 0)
		जाओ out;

	ascii_buf = datablob_क्रमmat(epayload, asciiblob_len);
	अगर (!ascii_buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	up_पढ़ो(&mkey->sem);
	key_put(mkey);
	memzero_explicit(derived_key, माप(derived_key));

	स_नकल(buffer, ascii_buf, asciiblob_len);
	kमुक्त_sensitive(ascii_buf);

	वापस asciiblob_len;
out:
	up_पढ़ो(&mkey->sem);
	key_put(mkey);
	memzero_explicit(derived_key, माप(derived_key));
	वापस ret;
पूर्ण

/*
 * encrypted_destroy - clear and मुक्त the key's payload
 */
अटल व्योम encrypted_destroy(काष्ठा key *key)
अणु
	kमुक्त_sensitive(key->payload.data[0]);
पूर्ण

काष्ठा key_type key_type_encrypted = अणु
	.name = "encrypted",
	.instantiate = encrypted_instantiate,
	.update = encrypted_update,
	.destroy = encrypted_destroy,
	.describe = user_describe,
	.पढ़ो = encrypted_पढ़ो,
पूर्ण;
EXPORT_SYMBOL_GPL(key_type_encrypted);

अटल पूर्णांक __init init_encrypted(व्योम)
अणु
	पूर्णांक ret;

	hash_tfm = crypto_alloc_shash(hash_alg, 0, 0);
	अगर (IS_ERR(hash_tfm)) अणु
		pr_err("encrypted_key: can't allocate %s transform: %ld\n",
		       hash_alg, PTR_ERR(hash_tfm));
		वापस PTR_ERR(hash_tfm);
	पूर्ण

	ret = aes_get_sizes();
	अगर (ret < 0)
		जाओ out;
	ret = रेजिस्टर_key_type(&key_type_encrypted);
	अगर (ret < 0)
		जाओ out;
	वापस 0;
out:
	crypto_मुक्त_shash(hash_tfm);
	वापस ret;

पूर्ण

अटल व्योम __निकास cleanup_encrypted(व्योम)
अणु
	crypto_मुक्त_shash(hash_tfm);
	unरेजिस्टर_key_type(&key_type_encrypted);
पूर्ण

late_initcall(init_encrypted);
module_निकास(cleanup_encrypted);

MODULE_LICENSE("GPL");
