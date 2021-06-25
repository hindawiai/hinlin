<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/err.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/key-type.h>
#समावेश <linux/sched/mm.h>

#समावेश <keys/ceph-type.h>
#समावेश <keys/user-type.h>
#समावेश <linux/ceph/decode.h>
#समावेश "crypto.h"

/*
 * Set ->key and ->tfm.  The rest of the key should be filled in beक्रमe
 * this function is called.
 */
अटल पूर्णांक set_secret(काष्ठा ceph_crypto_key *key, व्योम *buf)
अणु
	अचिन्हित पूर्णांक noio_flag;
	पूर्णांक ret;

	key->key = शून्य;
	key->tfm = शून्य;

	चयन (key->type) अणु
	हाल CEPH_CRYPTO_NONE:
		वापस 0; /* nothing to करो */
	हाल CEPH_CRYPTO_AES:
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!key->len)
		वापस -EINVAL;

	key->key = kmemdup(buf, key->len, GFP_NOIO);
	अगर (!key->key) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* crypto_alloc_sync_skcipher() allocates with GFP_KERNEL */
	noio_flag = meदो_स्मृति_noio_save();
	key->tfm = crypto_alloc_sync_skcipher("cbc(aes)", 0, 0);
	meदो_स्मृति_noio_restore(noio_flag);
	अगर (IS_ERR(key->tfm)) अणु
		ret = PTR_ERR(key->tfm);
		key->tfm = शून्य;
		जाओ fail;
	पूर्ण

	ret = crypto_sync_skcipher_setkey(key->tfm, key->key, key->len);
	अगर (ret)
		जाओ fail;

	वापस 0;

fail:
	ceph_crypto_key_destroy(key);
	वापस ret;
पूर्ण

पूर्णांक ceph_crypto_key_clone(काष्ठा ceph_crypto_key *dst,
			  स्थिर काष्ठा ceph_crypto_key *src)
अणु
	स_नकल(dst, src, माप(काष्ठा ceph_crypto_key));
	वापस set_secret(dst, src->key);
पूर्ण

पूर्णांक ceph_crypto_key_encode(काष्ठा ceph_crypto_key *key, व्योम **p, व्योम *end)
अणु
	अगर (*p + माप(u16) + माप(key->created) +
	    माप(u16) + key->len > end)
		वापस -दुस्फल;
	ceph_encode_16(p, key->type);
	ceph_encode_copy(p, &key->created, माप(key->created));
	ceph_encode_16(p, key->len);
	ceph_encode_copy(p, key->key, key->len);
	वापस 0;
पूर्ण

पूर्णांक ceph_crypto_key_decode(काष्ठा ceph_crypto_key *key, व्योम **p, व्योम *end)
अणु
	पूर्णांक ret;

	ceph_decode_need(p, end, 2*माप(u16) + माप(key->created), bad);
	key->type = ceph_decode_16(p);
	ceph_decode_copy(p, &key->created, माप(key->created));
	key->len = ceph_decode_16(p);
	ceph_decode_need(p, end, key->len, bad);
	ret = set_secret(key, *p);
	memzero_explicit(*p, key->len);
	*p += key->len;
	वापस ret;

bad:
	करोut("failed to decode crypto key\n");
	वापस -EINVAL;
पूर्ण

पूर्णांक ceph_crypto_key_unarmor(काष्ठा ceph_crypto_key *key, स्थिर अक्षर *inkey)
अणु
	पूर्णांक inlen = म_माप(inkey);
	पूर्णांक blen = inlen * 3 / 4;
	व्योम *buf, *p;
	पूर्णांक ret;

	करोut("crypto_key_unarmor %s\n", inkey);
	buf = kदो_स्मृति(blen, GFP_NOFS);
	अगर (!buf)
		वापस -ENOMEM;
	blen = ceph_unarmor(buf, inkey, inkey+inlen);
	अगर (blen < 0) अणु
		kमुक्त(buf);
		वापस blen;
	पूर्ण

	p = buf;
	ret = ceph_crypto_key_decode(key, &p, p + blen);
	kमुक्त(buf);
	अगर (ret)
		वापस ret;
	करोut("crypto_key_unarmor key %p type %d len %d\n", key,
	     key->type, key->len);
	वापस 0;
पूर्ण

व्योम ceph_crypto_key_destroy(काष्ठा ceph_crypto_key *key)
अणु
	अगर (key) अणु
		kमुक्त_sensitive(key->key);
		key->key = शून्य;
		अगर (key->tfm) अणु
			crypto_मुक्त_sync_skcipher(key->tfm);
			key->tfm = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर u8 *aes_iv = (u8 *)CEPH_AES_IV;

/*
 * Should be used क्रम buffers allocated with ceph_kvदो_स्मृति().
 * Currently these are encrypt out-buffer (ceph_buffer) and decrypt
 * in-buffer (msg front).
 *
 * Dispose of @sgt with tearकरोwn_sgtable().
 *
 * @pपुनः_स्मृति_sg is to aव्योम memory allocation inside sg_alloc_table()
 * in हालs where a single sg is sufficient.  No attempt to reduce the
 * number of sgs by squeezing physically contiguous pages together is
 * made though, क्रम simplicity.
 */
अटल पूर्णांक setup_sgtable(काष्ठा sg_table *sgt, काष्ठा scatterlist *pपुनः_स्मृति_sg,
			 स्थिर व्योम *buf, अचिन्हित पूर्णांक buf_len)
अणु
	काष्ठा scatterlist *sg;
	स्थिर bool is_vदो_स्मृति = is_vदो_स्मृति_addr(buf);
	अचिन्हित पूर्णांक off = offset_in_page(buf);
	अचिन्हित पूर्णांक chunk_cnt = 1;
	अचिन्हित पूर्णांक chunk_len = PAGE_ALIGN(off + buf_len);
	पूर्णांक i;
	पूर्णांक ret;

	अगर (buf_len == 0) अणु
		स_रखो(sgt, 0, माप(*sgt));
		वापस -EINVAL;
	पूर्ण

	अगर (is_vदो_स्मृति) अणु
		chunk_cnt = chunk_len >> PAGE_SHIFT;
		chunk_len = PAGE_SIZE;
	पूर्ण

	अगर (chunk_cnt > 1) अणु
		ret = sg_alloc_table(sgt, chunk_cnt, GFP_NOFS);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		WARN_ON(chunk_cnt != 1);
		sg_init_table(pपुनः_स्मृति_sg, 1);
		sgt->sgl = pपुनः_स्मृति_sg;
		sgt->nents = sgt->orig_nents = 1;
	पूर्ण

	क्रम_each_sg(sgt->sgl, sg, sgt->orig_nents, i) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक len = min(chunk_len - off, buf_len);

		अगर (is_vदो_स्मृति)
			page = vदो_स्मृति_to_page(buf);
		अन्यथा
			page = virt_to_page(buf);

		sg_set_page(sg, page, len, off);

		off = 0;
		buf += len;
		buf_len -= len;
	पूर्ण
	WARN_ON(buf_len != 0);

	वापस 0;
पूर्ण

अटल व्योम tearकरोwn_sgtable(काष्ठा sg_table *sgt)
अणु
	अगर (sgt->orig_nents > 1)
		sg_मुक्त_table(sgt);
पूर्ण

अटल पूर्णांक ceph_aes_crypt(स्थिर काष्ठा ceph_crypto_key *key, bool encrypt,
			  व्योम *buf, पूर्णांक buf_len, पूर्णांक in_len, पूर्णांक *pout_len)
अणु
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, key->tfm);
	काष्ठा sg_table sgt;
	काष्ठा scatterlist pपुनः_स्मृति_sg;
	अक्षर iv[AES_BLOCK_SIZE] __aligned(8);
	पूर्णांक pad_byte = AES_BLOCK_SIZE - (in_len & (AES_BLOCK_SIZE - 1));
	पूर्णांक crypt_len = encrypt ? in_len + pad_byte : in_len;
	पूर्णांक ret;

	WARN_ON(crypt_len > buf_len);
	अगर (encrypt)
		स_रखो(buf + in_len, pad_byte, pad_byte);
	ret = setup_sgtable(&sgt, &pपुनः_स्मृति_sg, buf, crypt_len);
	अगर (ret)
		वापस ret;

	स_नकल(iv, aes_iv, AES_BLOCK_SIZE);
	skcipher_request_set_sync_tfm(req, key->tfm);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sgt.sgl, sgt.sgl, crypt_len, iv);

	/*
	prपूर्णांक_hex_dump(KERN_ERR, "key: ", DUMP_PREFIX_NONE, 16, 1,
		       key->key, key->len, 1);
	prपूर्णांक_hex_dump(KERN_ERR, " in: ", DUMP_PREFIX_NONE, 16, 1,
		       buf, crypt_len, 1);
	*/
	अगर (encrypt)
		ret = crypto_skcipher_encrypt(req);
	अन्यथा
		ret = crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);
	अगर (ret) अणु
		pr_err("%s %scrypt failed: %d\n", __func__,
		       encrypt ? "en" : "de", ret);
		जाओ out_sgt;
	पूर्ण
	/*
	prपूर्णांक_hex_dump(KERN_ERR, "out: ", DUMP_PREFIX_NONE, 16, 1,
		       buf, crypt_len, 1);
	*/

	अगर (encrypt) अणु
		*pout_len = crypt_len;
	पूर्ण अन्यथा अणु
		pad_byte = *(अक्षर *)(buf + in_len - 1);
		अगर (pad_byte > 0 && pad_byte <= AES_BLOCK_SIZE &&
		    in_len >= pad_byte) अणु
			*pout_len = in_len - pad_byte;
		पूर्ण अन्यथा अणु
			pr_err("%s got bad padding %d on in_len %d\n",
			       __func__, pad_byte, in_len);
			ret = -EPERM;
			जाओ out_sgt;
		पूर्ण
	पूर्ण

out_sgt:
	tearकरोwn_sgtable(&sgt);
	वापस ret;
पूर्ण

पूर्णांक ceph_crypt(स्थिर काष्ठा ceph_crypto_key *key, bool encrypt,
	       व्योम *buf, पूर्णांक buf_len, पूर्णांक in_len, पूर्णांक *pout_len)
अणु
	चयन (key->type) अणु
	हाल CEPH_CRYPTO_NONE:
		*pout_len = in_len;
		वापस 0;
	हाल CEPH_CRYPTO_AES:
		वापस ceph_aes_crypt(key, encrypt, buf, buf_len, in_len,
				      pout_len);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ceph_key_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा ceph_crypto_key *ckey;
	माप_प्रकार datalen = prep->datalen;
	पूर्णांक ret;
	व्योम *p;

	ret = -EINVAL;
	अगर (datalen <= 0 || datalen > 32767 || !prep->data)
		जाओ err;

	ret = -ENOMEM;
	ckey = kदो_स्मृति(माप(*ckey), GFP_KERNEL);
	अगर (!ckey)
		जाओ err;

	/* TODO ceph_crypto_key_decode should really take स्थिर input */
	p = (व्योम *)prep->data;
	ret = ceph_crypto_key_decode(ckey, &p, (अक्षर*)prep->data+datalen);
	अगर (ret < 0)
		जाओ err_ckey;

	prep->payload.data[0] = ckey;
	prep->quotalen = datalen;
	वापस 0;

err_ckey:
	kमुक्त(ckey);
err:
	वापस ret;
पूर्ण

अटल व्योम ceph_key_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा ceph_crypto_key *ckey = prep->payload.data[0];
	ceph_crypto_key_destroy(ckey);
	kमुक्त(ckey);
पूर्ण

अटल व्योम ceph_key_destroy(काष्ठा key *key)
अणु
	काष्ठा ceph_crypto_key *ckey = key->payload.data[0];

	ceph_crypto_key_destroy(ckey);
	kमुक्त(ckey);
पूर्ण

काष्ठा key_type key_type_ceph = अणु
	.name		= "ceph",
	.preparse	= ceph_key_preparse,
	.मुक्त_preparse	= ceph_key_मुक्त_preparse,
	.instantiate	= generic_key_instantiate,
	.destroy	= ceph_key_destroy,
पूर्ण;

पूर्णांक __init ceph_crypto_init(व्योम)
अणु
	वापस रेजिस्टर_key_type(&key_type_ceph);
पूर्ण

व्योम ceph_crypto_shutकरोwn(व्योम)
अणु
	unरेजिस्टर_key_type(&key_type_ceph);
पूर्ण
