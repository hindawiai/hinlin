<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Public Key Encryption
 *
 * Copyright (c) 2015, Intel Corporation
 * Authors: Tadeusz Struk <tadeusz.struk@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_AKCIPHER_H
#घोषणा _CRYPTO_AKCIPHER_H
#समावेश <linux/crypto.h>

/**
 * काष्ठा akcipher_request - खुला key request
 *
 * @base:	Common attributes क्रम async crypto requests
 * @src:	Source data
 *		For verअगरy op this is signature + digest, in that हाल
 *		total size of @src is @src_len + @dst_len.
 * @dst:	Destination data (Should be शून्य क्रम verअगरy op)
 * @src_len:	Size of the input buffer
 *		For verअगरy op it's size of signature part of @src, this part
 *		is supposed to be operated by cipher.
 * @dst_len:	Size of @dst buffer (क्रम all ops except verअगरy).
 *		It needs to be at least	as big as the expected result
 *		depending on the operation.
 *		After operation it will be updated with the actual size of the
 *		result.
 *		In हाल of error where the dst sgl size was insufficient,
 *		it will be updated to the size required क्रम the operation.
 *		For verअगरy op this is size of digest part in @src.
 * @__ctx:	Start of निजी context data
 */
काष्ठा akcipher_request अणु
	काष्ठा crypto_async_request base;
	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;
	अचिन्हित पूर्णांक src_len;
	अचिन्हित पूर्णांक dst_len;
	व्योम *__ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

/**
 * काष्ठा crypto_akcipher - user-instantiated objects which encapsulate
 * algorithms and core processing logic
 *
 * @base:	Common crypto API algorithm data काष्ठाure
 */
काष्ठा crypto_akcipher अणु
	काष्ठा crypto_tfm base;
पूर्ण;

/**
 * काष्ठा akcipher_alg - generic खुला key algorithm
 *
 * @sign:	Function perक्रमms a sign operation as defined by खुला key
 *		algorithm. In हाल of error, where the dst_len was insufficient,
 *		the req->dst_len will be updated to the size required क्रम the
 *		operation
 * @verअगरy:	Function perक्रमms a complete verअगरy operation as defined by
 *		खुला key algorithm, वापसing verअगरication status. Requires
 *		digest value as input parameter.
 * @encrypt:	Function perक्रमms an encrypt operation as defined by खुला key
 *		algorithm. In हाल of error, where the dst_len was insufficient,
 *		the req->dst_len will be updated to the size required क्रम the
 *		operation
 * @decrypt:	Function perक्रमms a decrypt operation as defined by खुला key
 *		algorithm. In हाल of error, where the dst_len was insufficient,
 *		the req->dst_len will be updated to the size required क्रम the
 *		operation
 * @set_pub_key: Function invokes the algorithm specअगरic set खुला key
 *		function, which knows how to decode and पूर्णांकerpret
 *		the BER encoded खुला key and parameters
 * @set_priv_key: Function invokes the algorithm specअगरic set निजी key
 *		function, which knows how to decode and पूर्णांकerpret
 *		the BER encoded निजी key and parameters
 * @max_size:	Function वापसs dest buffer size required क्रम a given key.
 * @init:	Initialize the cryptographic transक्रमmation object.
 *		This function is used to initialize the cryptographic
 *		transक्रमmation object. This function is called only once at
 *		the instantiation समय, right after the transक्रमmation context
 *		was allocated. In हाल the cryptographic hardware has some
 *		special requirements which need to be handled by software, this
 *		function shall check क्रम the precise requirement of the
 *		transक्रमmation and put any software fallbacks in place.
 * @निकास:	Deinitialize the cryptographic transक्रमmation object. This is a
 *		counterpart to @init, used to हटाओ various changes set in
 *		@init.
 *
 * @reqsize:	Request context size required by algorithm implementation
 * @base:	Common crypto API algorithm data काष्ठाure
 */
काष्ठा akcipher_alg अणु
	पूर्णांक (*sign)(काष्ठा akcipher_request *req);
	पूर्णांक (*verअगरy)(काष्ठा akcipher_request *req);
	पूर्णांक (*encrypt)(काष्ठा akcipher_request *req);
	पूर्णांक (*decrypt)(काष्ठा akcipher_request *req);
	पूर्णांक (*set_pub_key)(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			   अचिन्हित पूर्णांक keylen);
	पूर्णांक (*set_priv_key)(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			    अचिन्हित पूर्णांक keylen);
	अचिन्हित पूर्णांक (*max_size)(काष्ठा crypto_akcipher *tfm);
	पूर्णांक (*init)(काष्ठा crypto_akcipher *tfm);
	व्योम (*निकास)(काष्ठा crypto_akcipher *tfm);

	अचिन्हित पूर्णांक reqsize;
	काष्ठा crypto_alg base;
पूर्ण;

/**
 * DOC: Generic Public Key API
 *
 * The Public Key API is used with the algorithms of type
 * CRYPTO_ALG_TYPE_AKCIPHER (listed as type "akcipher" in /proc/crypto)
 */

/**
 * crypto_alloc_akcipher() - allocate AKCIPHER tfm handle
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	      खुला key algorithm e.g. "rsa"
 * @type: specअगरies the type of the algorithm
 * @mask: specअगरies the mask क्रम the algorithm
 *
 * Allocate a handle क्रम खुला key algorithm. The वापसed काष्ठा
 * crypto_akcipher is the handle that is required क्रम any subsequent
 * API invocation क्रम the खुला key operations.
 *
 * Return: allocated handle in हाल of success; IS_ERR() is true in हाल
 *	   of an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_akcipher *crypto_alloc_akcipher(स्थिर अक्षर *alg_name, u32 type,
					      u32 mask);

अटल अंतरभूत काष्ठा crypto_tfm *crypto_akcipher_tfm(
	काष्ठा crypto_akcipher *tfm)
अणु
	वापस &tfm->base;
पूर्ण

अटल अंतरभूत काष्ठा akcipher_alg *__crypto_akcipher_alg(काष्ठा crypto_alg *alg)
अणु
	वापस container_of(alg, काष्ठा akcipher_alg, base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_akcipher *__crypto_akcipher_tfm(
	काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm, काष्ठा crypto_akcipher, base);
पूर्ण

अटल अंतरभूत काष्ठा akcipher_alg *crypto_akcipher_alg(
	काष्ठा crypto_akcipher *tfm)
अणु
	वापस __crypto_akcipher_alg(crypto_akcipher_tfm(tfm)->__crt_alg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_akcipher_reqsize(काष्ठा crypto_akcipher *tfm)
अणु
	वापस crypto_akcipher_alg(tfm)->reqsize;
पूर्ण

अटल अंतरभूत व्योम akcipher_request_set_tfm(काष्ठा akcipher_request *req,
					    काष्ठा crypto_akcipher *tfm)
अणु
	req->base.tfm = crypto_akcipher_tfm(tfm);
पूर्ण

अटल अंतरभूत काष्ठा crypto_akcipher *crypto_akcipher_reqtfm(
	काष्ठा akcipher_request *req)
अणु
	वापस __crypto_akcipher_tfm(req->base.tfm);
पूर्ण

/**
 * crypto_मुक्त_akcipher() - मुक्त AKCIPHER tfm handle
 *
 * @tfm: AKCIPHER tfm handle allocated with crypto_alloc_akcipher()
 *
 * If @tfm is a शून्य or error poपूर्णांकer, this function करोes nothing.
 */
अटल अंतरभूत व्योम crypto_मुक्त_akcipher(काष्ठा crypto_akcipher *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_akcipher_tfm(tfm));
पूर्ण

/**
 * akcipher_request_alloc() - allocates खुला key request
 *
 * @tfm:	AKCIPHER tfm handle allocated with crypto_alloc_akcipher()
 * @gfp:	allocation flags
 *
 * Return: allocated handle in हाल of success or शून्य in हाल of an error.
 */
अटल अंतरभूत काष्ठा akcipher_request *akcipher_request_alloc(
	काष्ठा crypto_akcipher *tfm, gfp_t gfp)
अणु
	काष्ठा akcipher_request *req;

	req = kदो_स्मृति(माप(*req) + crypto_akcipher_reqsize(tfm), gfp);
	अगर (likely(req))
		akcipher_request_set_tfm(req, tfm);

	वापस req;
पूर्ण

/**
 * akcipher_request_मुक्त() - zeroize and मुक्त खुला key request
 *
 * @req:	request to मुक्त
 */
अटल अंतरभूत व्योम akcipher_request_मुक्त(काष्ठा akcipher_request *req)
अणु
	kमुक्त_sensitive(req);
पूर्ण

/**
 * akcipher_request_set_callback() - Sets an asynchronous callback.
 *
 * Callback will be called when an asynchronous operation on a given
 * request is finished.
 *
 * @req:	request that the callback will be set क्रम
 * @flgs:	specअगरy क्रम instance अगर the operation may backlog
 * @cmpl:	callback which will be called
 * @data:	निजी data used by the caller
 */
अटल अंतरभूत व्योम akcipher_request_set_callback(काष्ठा akcipher_request *req,
						 u32 flgs,
						 crypto_completion_t cmpl,
						 व्योम *data)
अणु
	req->base.complete = cmpl;
	req->base.data = data;
	req->base.flags = flgs;
पूर्ण

/**
 * akcipher_request_set_crypt() - Sets request parameters
 *
 * Sets parameters required by crypto operation
 *
 * @req:	खुला key request
 * @src:	ptr to input scatter list
 * @dst:	ptr to output scatter list or शून्य क्रम verअगरy op
 * @src_len:	size of the src input scatter list to be processed
 * @dst_len:	size of the dst output scatter list or size of signature
 *		portion in @src क्रम verअगरy op
 */
अटल अंतरभूत व्योम akcipher_request_set_crypt(काष्ठा akcipher_request *req,
					      काष्ठा scatterlist *src,
					      काष्ठा scatterlist *dst,
					      अचिन्हित पूर्णांक src_len,
					      अचिन्हित पूर्णांक dst_len)
अणु
	req->src = src;
	req->dst = dst;
	req->src_len = src_len;
	req->dst_len = dst_len;
पूर्ण

/**
 * crypto_akcipher_maxsize() - Get len क्रम output buffer
 *
 * Function वापसs the dest buffer size required क्रम a given key.
 * Function assumes that the key is alपढ़ोy set in the transक्रमmation. If this
 * function is called without a setkey or with a failed setkey, you will end up
 * in a शून्य dereference.
 *
 * @tfm:	AKCIPHER tfm handle allocated with crypto_alloc_akcipher()
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_akcipher_maxsize(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(tfm);

	वापस alg->max_size(tfm);
पूर्ण

/**
 * crypto_akcipher_encrypt() - Invoke खुला key encrypt operation
 *
 * Function invokes the specअगरic खुला key encrypt operation क्रम a given
 * खुला key algorithm
 *
 * @req:	asymmetric key request
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_akcipher_encrypt(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(tfm);
	काष्ठा crypto_alg *calg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक src_len = req->src_len;
	पूर्णांक ret;

	crypto_stats_get(calg);
	ret = alg->encrypt(req);
	crypto_stats_akcipher_encrypt(src_len, ret, calg);
	वापस ret;
पूर्ण

/**
 * crypto_akcipher_decrypt() - Invoke खुला key decrypt operation
 *
 * Function invokes the specअगरic खुला key decrypt operation क्रम a given
 * खुला key algorithm
 *
 * @req:	asymmetric key request
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_akcipher_decrypt(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(tfm);
	काष्ठा crypto_alg *calg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक src_len = req->src_len;
	पूर्णांक ret;

	crypto_stats_get(calg);
	ret = alg->decrypt(req);
	crypto_stats_akcipher_decrypt(src_len, ret, calg);
	वापस ret;
पूर्ण

/**
 * crypto_akcipher_sign() - Invoke खुला key sign operation
 *
 * Function invokes the specअगरic खुला key sign operation क्रम a given
 * खुला key algorithm
 *
 * @req:	asymmetric key request
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_akcipher_sign(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(tfm);
	काष्ठा crypto_alg *calg = tfm->base.__crt_alg;
	पूर्णांक ret;

	crypto_stats_get(calg);
	ret = alg->sign(req);
	crypto_stats_akcipher_sign(ret, calg);
	वापस ret;
पूर्ण

/**
 * crypto_akcipher_verअगरy() - Invoke खुला key signature verअगरication
 *
 * Function invokes the specअगरic खुला key signature verअगरication operation
 * क्रम a given खुला key algorithm.
 *
 * @req:	asymmetric key request
 *
 * Note: req->dst should be शून्य, req->src should poपूर्णांक to SG of size
 * (req->src_size + req->dst_size), containing signature (of req->src_size
 * length) with appended digest (of req->dst_size length).
 *
 * Return: zero on verअगरication success; error code in हाल of error.
 */
अटल अंतरभूत पूर्णांक crypto_akcipher_verअगरy(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(tfm);
	काष्ठा crypto_alg *calg = tfm->base.__crt_alg;
	पूर्णांक ret;

	crypto_stats_get(calg);
	ret = alg->verअगरy(req);
	crypto_stats_akcipher_verअगरy(ret, calg);
	वापस ret;
पूर्ण

/**
 * crypto_akcipher_set_pub_key() - Invoke set खुला key operation
 *
 * Function invokes the algorithm specअगरic set key function, which knows
 * how to decode and पूर्णांकerpret the encoded key and parameters
 *
 * @tfm:	tfm handle
 * @key:	BER encoded खुला key, algo OID, paramlen, BER encoded
 *		parameters
 * @keylen:	length of the key (not including other data)
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_akcipher_set_pub_key(काष्ठा crypto_akcipher *tfm,
					      स्थिर व्योम *key,
					      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(tfm);

	वापस alg->set_pub_key(tfm, key, keylen);
पूर्ण

/**
 * crypto_akcipher_set_priv_key() - Invoke set निजी key operation
 *
 * Function invokes the algorithm specअगरic set key function, which knows
 * how to decode and पूर्णांकerpret the encoded key and parameters
 *
 * @tfm:	tfm handle
 * @key:	BER encoded निजी key, algo OID, paramlen, BER encoded
 *		parameters
 * @keylen:	length of the key (not including other data)
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_akcipher_set_priv_key(काष्ठा crypto_akcipher *tfm,
					       स्थिर व्योम *key,
					       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(tfm);

	वापस alg->set_priv_key(tfm, key, keylen);
पूर्ण
#पूर्ण_अगर
