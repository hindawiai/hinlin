<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2003-2004, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2014-2015, Qualcomm Atheros, Inc.
 *
 * Reग_लिखो: Copyright (C) 2013 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/aead.h>

#समावेश "aead_api.h"

पूर्णांक aead_encrypt(काष्ठा crypto_aead *tfm, u8 *b_0, u8 *aad, माप_प्रकार aad_len,
		 u8 *data, माप_प्रकार data_len, u8 *mic)
अणु
	माप_प्रकार mic_len = crypto_aead_authsize(tfm);
	काष्ठा scatterlist sg[3];
	काष्ठा aead_request *aead_req;
	पूर्णांक reqsize = माप(*aead_req) + crypto_aead_reqsize(tfm);
	u8 *__aad;
	पूर्णांक ret;

	aead_req = kzalloc(reqsize + aad_len, GFP_ATOMIC);
	अगर (!aead_req)
		वापस -ENOMEM;

	__aad = (u8 *)aead_req + reqsize;
	स_नकल(__aad, aad, aad_len);

	sg_init_table(sg, 3);
	sg_set_buf(&sg[0], __aad, aad_len);
	sg_set_buf(&sg[1], data, data_len);
	sg_set_buf(&sg[2], mic, mic_len);

	aead_request_set_tfm(aead_req, tfm);
	aead_request_set_crypt(aead_req, sg, sg, data_len, b_0);
	aead_request_set_ad(aead_req, sg[0].length);

	ret = crypto_aead_encrypt(aead_req);
	kमुक्त_sensitive(aead_req);

	वापस ret;
पूर्ण

पूर्णांक aead_decrypt(काष्ठा crypto_aead *tfm, u8 *b_0, u8 *aad, माप_प्रकार aad_len,
		 u8 *data, माप_प्रकार data_len, u8 *mic)
अणु
	माप_प्रकार mic_len = crypto_aead_authsize(tfm);
	काष्ठा scatterlist sg[3];
	काष्ठा aead_request *aead_req;
	पूर्णांक reqsize = माप(*aead_req) + crypto_aead_reqsize(tfm);
	u8 *__aad;
	पूर्णांक err;

	अगर (data_len == 0)
		वापस -EINVAL;

	aead_req = kzalloc(reqsize + aad_len, GFP_ATOMIC);
	अगर (!aead_req)
		वापस -ENOMEM;

	__aad = (u8 *)aead_req + reqsize;
	स_नकल(__aad, aad, aad_len);

	sg_init_table(sg, 3);
	sg_set_buf(&sg[0], __aad, aad_len);
	sg_set_buf(&sg[1], data, data_len);
	sg_set_buf(&sg[2], mic, mic_len);

	aead_request_set_tfm(aead_req, tfm);
	aead_request_set_crypt(aead_req, sg, sg, data_len + mic_len, b_0);
	aead_request_set_ad(aead_req, sg[0].length);

	err = crypto_aead_decrypt(aead_req);
	kमुक्त_sensitive(aead_req);

	वापस err;
पूर्ण

काष्ठा crypto_aead *
aead_key_setup_encrypt(स्थिर अक्षर *alg, स्थिर u8 key[],
		       माप_प्रकार key_len, माप_प्रकार mic_len)
अणु
	काष्ठा crypto_aead *tfm;
	पूर्णांक err;

	tfm = crypto_alloc_aead(alg, 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		वापस tfm;

	err = crypto_aead_setkey(tfm, key, key_len);
	अगर (err)
		जाओ मुक्त_aead;
	err = crypto_aead_setauthsize(tfm, mic_len);
	अगर (err)
		जाओ मुक्त_aead;

	वापस tfm;

मुक्त_aead:
	crypto_मुक्त_aead(tfm);
	वापस ERR_PTR(err);
पूर्ण

व्योम aead_key_मुक्त(काष्ठा crypto_aead *tfm)
अणु
	crypto_मुक्त_aead(tfm);
पूर्ण
