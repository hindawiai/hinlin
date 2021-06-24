<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Crypto operations using stored keys
 *
 * Copyright (c) 2016, Intel Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/dh.h>
#समावेश <keys/user-type.h>
#समावेश "internal.h"

अटल sमाप_प्रकार dh_data_from_key(key_serial_t keyid, व्योम **data)
अणु
	काष्ठा key *key;
	key_ref_t key_ref;
	दीर्घ status;
	sमाप_प्रकार ret;

	key_ref = lookup_user_key(keyid, 0, KEY_NEED_READ);
	अगर (IS_ERR(key_ref)) अणु
		ret = -ENOKEY;
		जाओ error;
	पूर्ण

	key = key_ref_to_ptr(key_ref);

	ret = -EOPNOTSUPP;
	अगर (key->type == &key_type_user) अणु
		करोwn_पढ़ो(&key->sem);
		status = key_validate(key);
		अगर (status == 0) अणु
			स्थिर काष्ठा user_key_payload *payload;
			uपूर्णांक8_t *duplicate;

			payload = user_key_payload_locked(key);

			duplicate = kmemdup(payload->data, payload->datalen,
					    GFP_KERNEL);
			अगर (duplicate) अणु
				*data = duplicate;
				ret = payload->datalen;
			पूर्ण अन्यथा अणु
				ret = -ENOMEM;
			पूर्ण
		पूर्ण
		up_पढ़ो(&key->sem);
	पूर्ण

	key_put(key);
error:
	वापस ret;
पूर्ण

अटल व्योम dh_मुक्त_data(काष्ठा dh *dh)
अणु
	kमुक्त_sensitive(dh->key);
	kमुक्त_sensitive(dh->p);
	kमुक्त_sensitive(dh->g);
पूर्ण

काष्ठा dh_completion अणु
	काष्ठा completion completion;
	पूर्णांक err;
पूर्ण;

अटल व्योम dh_crypto_करोne(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा dh_completion *compl = req->data;

	अगर (err == -EINPROGRESS)
		वापस;

	compl->err = err;
	complete(&compl->completion);
पूर्ण

काष्ठा kdf_sdesc अणु
	काष्ठा shash_desc shash;
	अक्षर ctx[];
पूर्ण;

अटल पूर्णांक kdf_alloc(काष्ठा kdf_sdesc **sdesc_ret, अक्षर *hashname)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा kdf_sdesc *sdesc;
	पूर्णांक size;
	पूर्णांक err;

	/* allocate synchronous hash */
	tfm = crypto_alloc_shash(hashname, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_info("could not allocate digest TFM handle %s\n", hashname);
		वापस PTR_ERR(tfm);
	पूर्ण

	err = -EINVAL;
	अगर (crypto_shash_digestsize(tfm) == 0)
		जाओ out_मुक्त_tfm;

	err = -ENOMEM;
	size = माप(काष्ठा shash_desc) + crypto_shash_descsize(tfm);
	sdesc = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!sdesc)
		जाओ out_मुक्त_tfm;
	sdesc->shash.tfm = tfm;

	*sdesc_ret = sdesc;

	वापस 0;

out_मुक्त_tfm:
	crypto_मुक्त_shash(tfm);
	वापस err;
पूर्ण

अटल व्योम kdf_dealloc(काष्ठा kdf_sdesc *sdesc)
अणु
	अगर (!sdesc)
		वापस;

	अगर (sdesc->shash.tfm)
		crypto_मुक्त_shash(sdesc->shash.tfm);

	kमुक्त_sensitive(sdesc);
पूर्ण

/*
 * Implementation of the KDF in counter mode according to SP800-108 section 5.1
 * as well as SP800-56A section 5.8.1 (Single-step KDF).
 *
 * SP800-56A:
 * The src poपूर्णांकer is defined as Z || other info where Z is the shared secret
 * from DH and other info is an arbitrary string (see SP800-56A section
 * 5.8.1.2).
 *
 * 'dlen' must be a multiple of the digest size.
 */
अटल पूर्णांक kdf_ctr(काष्ठा kdf_sdesc *sdesc, स्थिर u8 *src, अचिन्हित पूर्णांक slen,
		   u8 *dst, अचिन्हित पूर्णांक dlen, अचिन्हित पूर्णांक zlen)
अणु
	काष्ठा shash_desc *desc = &sdesc->shash;
	अचिन्हित पूर्णांक h = crypto_shash_digestsize(desc->tfm);
	पूर्णांक err = 0;
	u8 *dst_orig = dst;
	__be32 counter = cpu_to_be32(1);

	जबतक (dlen) अणु
		err = crypto_shash_init(desc);
		अगर (err)
			जाओ err;

		err = crypto_shash_update(desc, (u8 *)&counter, माप(__be32));
		अगर (err)
			जाओ err;

		अगर (zlen && h) अणु
			u8 पंचांगpbuffer[32];
			माप_प्रकार chunk = min_t(माप_प्रकार, zlen, माप(पंचांगpbuffer));
			स_रखो(पंचांगpbuffer, 0, chunk);

			करो अणु
				err = crypto_shash_update(desc, पंचांगpbuffer,
							  chunk);
				अगर (err)
					जाओ err;

				zlen -= chunk;
				chunk = min_t(माप_प्रकार, zlen, माप(पंचांगpbuffer));
			पूर्ण जबतक (zlen);
		पूर्ण

		अगर (src && slen) अणु
			err = crypto_shash_update(desc, src, slen);
			अगर (err)
				जाओ err;
		पूर्ण

		err = crypto_shash_final(desc, dst);
		अगर (err)
			जाओ err;

		dlen -= h;
		dst += h;
		counter = cpu_to_be32(be32_to_cpu(counter) + 1);
	पूर्ण

	वापस 0;

err:
	memzero_explicit(dst_orig, dlen);
	वापस err;
पूर्ण

अटल पूर्णांक keyctl_dh_compute_kdf(काष्ठा kdf_sdesc *sdesc,
				 अक्षर __user *buffer, माप_प्रकार buflen,
				 uपूर्णांक8_t *kbuf, माप_प्रकार kbuflen, माप_प्रकार lzero)
अणु
	uपूर्णांक8_t *outbuf = शून्य;
	पूर्णांक ret;
	माप_प्रकार outbuf_len = roundup(buflen,
				    crypto_shash_digestsize(sdesc->shash.tfm));

	outbuf = kदो_स्मृति(outbuf_len, GFP_KERNEL);
	अगर (!outbuf) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = kdf_ctr(sdesc, kbuf, kbuflen, outbuf, outbuf_len, lzero);
	अगर (ret)
		जाओ err;

	ret = buflen;
	अगर (copy_to_user(buffer, outbuf, buflen) != 0)
		ret = -EFAULT;

err:
	kमुक्त_sensitive(outbuf);
	वापस ret;
पूर्ण

दीर्घ __keyctl_dh_compute(काष्ठा keyctl_dh_params __user *params,
			 अक्षर __user *buffer, माप_प्रकार buflen,
			 काष्ठा keyctl_kdf_params *kdfcopy)
अणु
	दीर्घ ret;
	sमाप_प्रकार dlen;
	पूर्णांक secretlen;
	पूर्णांक outlen;
	काष्ठा keyctl_dh_params pcopy;
	काष्ठा dh dh_inमाला_दो;
	काष्ठा scatterlist outsg;
	काष्ठा dh_completion compl;
	काष्ठा crypto_kpp *tfm;
	काष्ठा kpp_request *req;
	uपूर्णांक8_t *secret;
	uपूर्णांक8_t *outbuf;
	काष्ठा kdf_sdesc *sdesc = शून्य;

	अगर (!params || (!buffer && buflen)) अणु
		ret = -EINVAL;
		जाओ out1;
	पूर्ण
	अगर (copy_from_user(&pcopy, params, माप(pcopy)) != 0) अणु
		ret = -EFAULT;
		जाओ out1;
	पूर्ण

	अगर (kdfcopy) अणु
		अक्षर *hashname;

		अगर (स_प्रथम_inv(kdfcopy->__spare, 0, माप(kdfcopy->__spare))) अणु
			ret = -EINVAL;
			जाओ out1;
		पूर्ण

		अगर (buflen > KEYCTL_KDF_MAX_OUTPUT_LEN ||
		    kdfcopy->otherinfolen > KEYCTL_KDF_MAX_OI_LEN) अणु
			ret = -EMSGSIZE;
			जाओ out1;
		पूर्ण

		/* get KDF name string */
		hashname = strndup_user(kdfcopy->hashname, CRYPTO_MAX_ALG_NAME);
		अगर (IS_ERR(hashname)) अणु
			ret = PTR_ERR(hashname);
			जाओ out1;
		पूर्ण

		/* allocate KDF from the kernel crypto API */
		ret = kdf_alloc(&sdesc, hashname);
		kमुक्त(hashname);
		अगर (ret)
			जाओ out1;
	पूर्ण

	स_रखो(&dh_inमाला_दो, 0, माप(dh_inमाला_दो));

	dlen = dh_data_from_key(pcopy.prime, &dh_inमाला_दो.p);
	अगर (dlen < 0) अणु
		ret = dlen;
		जाओ out1;
	पूर्ण
	dh_inमाला_दो.p_size = dlen;

	dlen = dh_data_from_key(pcopy.base, &dh_inमाला_दो.g);
	अगर (dlen < 0) अणु
		ret = dlen;
		जाओ out2;
	पूर्ण
	dh_inमाला_दो.g_size = dlen;

	dlen = dh_data_from_key(pcopy.निजी, &dh_inमाला_दो.key);
	अगर (dlen < 0) अणु
		ret = dlen;
		जाओ out2;
	पूर्ण
	dh_inमाला_दो.key_size = dlen;

	secretlen = crypto_dh_key_len(&dh_inमाला_दो);
	secret = kदो_स्मृति(secretlen, GFP_KERNEL);
	अगर (!secret) अणु
		ret = -ENOMEM;
		जाओ out2;
	पूर्ण
	ret = crypto_dh_encode_key(secret, secretlen, &dh_inमाला_दो);
	अगर (ret)
		जाओ out3;

	tfm = crypto_alloc_kpp("dh", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		ret = PTR_ERR(tfm);
		जाओ out3;
	पूर्ण

	ret = crypto_kpp_set_secret(tfm, secret, secretlen);
	अगर (ret)
		जाओ out4;

	outlen = crypto_kpp_maxsize(tfm);

	अगर (!kdfcopy) अणु
		/*
		 * When not using a KDF, buflen 0 is used to पढ़ो the
		 * required buffer length
		 */
		अगर (buflen == 0) अणु
			ret = outlen;
			जाओ out4;
		पूर्ण अन्यथा अगर (outlen > buflen) अणु
			ret = -EOVERFLOW;
			जाओ out4;
		पूर्ण
	पूर्ण

	outbuf = kzalloc(kdfcopy ? (outlen + kdfcopy->otherinfolen) : outlen,
			 GFP_KERNEL);
	अगर (!outbuf) अणु
		ret = -ENOMEM;
		जाओ out4;
	पूर्ण

	sg_init_one(&outsg, outbuf, outlen);

	req = kpp_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		ret = -ENOMEM;
		जाओ out5;
	पूर्ण

	kpp_request_set_input(req, शून्य, 0);
	kpp_request_set_output(req, &outsg, outlen);
	init_completion(&compl.completion);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
				 CRYPTO_TFM_REQ_MAY_SLEEP,
				 dh_crypto_करोne, &compl);

	/*
	 * For DH, generate_खुला_key and generate_shared_secret are
	 * the same calculation
	 */
	ret = crypto_kpp_generate_खुला_key(req);
	अगर (ret == -EINPROGRESS) अणु
		रुको_क्रम_completion(&compl.completion);
		ret = compl.err;
		अगर (ret)
			जाओ out6;
	पूर्ण

	अगर (kdfcopy) अणु
		/*
		 * Concatenate SP800-56A otherinfo past DH shared secret -- the
		 * input to the KDF is (DH shared secret || otherinfo)
		 */
		अगर (copy_from_user(outbuf + req->dst_len, kdfcopy->otherinfo,
				   kdfcopy->otherinfolen) != 0) अणु
			ret = -EFAULT;
			जाओ out6;
		पूर्ण

		ret = keyctl_dh_compute_kdf(sdesc, buffer, buflen, outbuf,
					    req->dst_len + kdfcopy->otherinfolen,
					    outlen - req->dst_len);
	पूर्ण अन्यथा अगर (copy_to_user(buffer, outbuf, req->dst_len) == 0) अणु
		ret = req->dst_len;
	पूर्ण अन्यथा अणु
		ret = -EFAULT;
	पूर्ण

out6:
	kpp_request_मुक्त(req);
out5:
	kमुक्त_sensitive(outbuf);
out4:
	crypto_मुक्त_kpp(tfm);
out3:
	kमुक्त_sensitive(secret);
out2:
	dh_मुक्त_data(&dh_inमाला_दो);
out1:
	kdf_dealloc(sdesc);
	वापस ret;
पूर्ण

दीर्घ keyctl_dh_compute(काष्ठा keyctl_dh_params __user *params,
		       अक्षर __user *buffer, माप_प्रकार buflen,
		       काष्ठा keyctl_kdf_params __user *kdf)
अणु
	काष्ठा keyctl_kdf_params kdfcopy;

	अगर (!kdf)
		वापस __keyctl_dh_compute(params, buffer, buflen, शून्य);

	अगर (copy_from_user(&kdfcopy, kdf, माप(kdfcopy)) != 0)
		वापस -EFAULT;

	वापस __keyctl_dh_compute(params, buffer, buflen, &kdfcopy);
पूर्ण
