<शैली गुरु>
/*
 * ECDH helper functions - KPP wrappings
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
 * CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
 * COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
 * SOFTWARE IS DISCLAIMED.
 */
#समावेश "ecdh_helper.h"

#समावेश <linux/scatterlist.h>
#समावेश <crypto/ecdh.h>

काष्ठा ecdh_completion अणु
	काष्ठा completion completion;
	पूर्णांक err;
पूर्ण;

अटल व्योम ecdh_complete(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा ecdh_completion *res = req->data;

	अगर (err == -EINPROGRESS)
		वापस;

	res->err = err;
	complete(&res->completion);
पूर्ण

अटल अंतरभूत व्योम swap_digits(u64 *in, u64 *out, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++)
		out[i] = __swab64(in[ndigits - 1 - i]);
पूर्ण

/* compute_ecdh_secret() - function assumes that the निजी key was
 *                         alपढ़ोy set.
 * @tfm:          KPP tfm handle allocated with crypto_alloc_kpp().
 * @खुला_key:   pair's ecc खुला key.
 * secret:        memory where the ecdh computed shared secret will be saved.
 *
 * Return: zero on success; error code in हाल of error.
 */
पूर्णांक compute_ecdh_secret(काष्ठा crypto_kpp *tfm, स्थिर u8 खुला_key[64],
			u8 secret[32])
अणु
	काष्ठा kpp_request *req;
	u8 *पंचांगp;
	काष्ठा ecdh_completion result;
	काष्ठा scatterlist src, dst;
	पूर्णांक err;

	पंचांगp = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	req = kpp_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ मुक्त_पंचांगp;
	पूर्ण

	init_completion(&result.completion);

	swap_digits((u64 *)खुला_key, (u64 *)पंचांगp, 4); /* x */
	swap_digits((u64 *)&खुला_key[32], (u64 *)&पंचांगp[32], 4); /* y */

	sg_init_one(&src, पंचांगp, 64);
	sg_init_one(&dst, secret, 32);
	kpp_request_set_input(req, &src, 64);
	kpp_request_set_output(req, &dst, 32);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 ecdh_complete, &result);
	err = crypto_kpp_compute_shared_secret(req);
	अगर (err == -EINPROGRESS) अणु
		रुको_क्रम_completion(&result.completion);
		err = result.err;
	पूर्ण
	अगर (err < 0) अणु
		pr_err("alg: ecdh: compute shared secret failed. err %d\n",
		       err);
		जाओ मुक्त_all;
	पूर्ण

	swap_digits((u64 *)secret, (u64 *)पंचांगp, 4);
	स_नकल(secret, पंचांगp, 32);

मुक्त_all:
	kpp_request_मुक्त(req);
मुक्त_पंचांगp:
	kमुक्त_sensitive(पंचांगp);
	वापस err;
पूर्ण

/* set_ecdh_privkey() - set or generate ecc निजी key.
 *
 * Function generates an ecc निजी key in the crypto subप्रणाली when receiving
 * a शून्य निजी key or sets the received key when not शून्य.
 *
 * @tfm:           KPP tfm handle allocated with crypto_alloc_kpp().
 * @निजी_key:   user's ecc निजी key. When not शून्य, the key is expected
 *                 in little endian क्रमmat.
 *
 * Return: zero on success; error code in हाल of error.
 */
पूर्णांक set_ecdh_privkey(काष्ठा crypto_kpp *tfm, स्थिर u8 निजी_key[32])
अणु
	u8 *buf, *पंचांगp = शून्य;
	अचिन्हित पूर्णांक buf_len;
	पूर्णांक err;
	काष्ठा ecdh p = अणु0पूर्ण;

	अगर (निजी_key) अणु
		पंचांगp = kदो_स्मृति(32, GFP_KERNEL);
		अगर (!पंचांगp)
			वापस -ENOMEM;
		swap_digits((u64 *)निजी_key, (u64 *)पंचांगp, 4);
		p.key = पंचांगp;
		p.key_size = 32;
	पूर्ण

	buf_len = crypto_ecdh_key_len(&p);
	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ मुक्त_पंचांगp;
	पूर्ण

	err = crypto_ecdh_encode_key(buf, buf_len, &p);
	अगर (err)
		जाओ मुक्त_all;

	err = crypto_kpp_set_secret(tfm, buf, buf_len);
	/* fall through */
मुक्त_all:
	kमुक्त_sensitive(buf);
मुक्त_पंचांगp:
	kमुक्त_sensitive(पंचांगp);
	वापस err;
पूर्ण

/* generate_ecdh_खुला_key() - function assumes that the निजी key was
 *                              alपढ़ोy set.
 *
 * @tfm:          KPP tfm handle allocated with crypto_alloc_kpp().
 * @खुला_key:   memory where the computed ecc खुला key will be saved.
 *
 * Return: zero on success; error code in हाल of error.
 */
पूर्णांक generate_ecdh_खुला_key(काष्ठा crypto_kpp *tfm, u8 खुला_key[64])
अणु
	काष्ठा kpp_request *req;
	u8 *पंचांगp;
	काष्ठा ecdh_completion result;
	काष्ठा scatterlist dst;
	पूर्णांक err;

	पंचांगp = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	req = kpp_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ मुक्त_पंचांगp;
	पूर्ण

	init_completion(&result.completion);
	sg_init_one(&dst, पंचांगp, 64);
	kpp_request_set_input(req, शून्य, 0);
	kpp_request_set_output(req, &dst, 64);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 ecdh_complete, &result);

	err = crypto_kpp_generate_खुला_key(req);
	अगर (err == -EINPROGRESS) अणु
		रुको_क्रम_completion(&result.completion);
		err = result.err;
	पूर्ण
	अगर (err < 0)
		जाओ मुक्त_all;

	/* The खुला key is handed back in little endian as expected by
	 * the Security Manager Protocol.
	 */
	swap_digits((u64 *)पंचांगp, (u64 *)खुला_key, 4); /* x */
	swap_digits((u64 *)&पंचांगp[32], (u64 *)&खुला_key[32], 4); /* y */

मुक्त_all:
	kpp_request_मुक्त(req);
मुक्त_पंचांगp:
	kमुक्त(पंचांगp);
	वापस err;
पूर्ण

/* generate_ecdh_keys() - generate ecc key pair.
 *
 * @tfm:          KPP tfm handle allocated with crypto_alloc_kpp().
 * @खुला_key:   memory where the computed ecc खुला key will be saved.
 *
 * Return: zero on success; error code in हाल of error.
 */
पूर्णांक generate_ecdh_keys(काष्ठा crypto_kpp *tfm, u8 खुला_key[64])
अणु
	पूर्णांक err;

	err = set_ecdh_privkey(tfm, शून्य);
	अगर (err)
		वापस err;

	वापस generate_ecdh_खुला_key(tfm, खुला_key);
पूर्ण
