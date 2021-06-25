<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Key-agreement Protocol Primitives (KPP)
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvatore Benedetto <salvatore.benedetto@पूर्णांकel.com>
 */

#अगर_अघोषित _CRYPTO_KPP_
#घोषणा _CRYPTO_KPP_
#समावेश <linux/crypto.h>

/**
 * काष्ठा kpp_request
 *
 * @base:	Common attributes क्रम async crypto requests
 * @src:	Source data
 * @dst:	Destination data
 * @src_len:	Size of the input buffer
 * @dst_len:	Size of the output buffer. It needs to be at least
 *		as big as the expected result depending	on the operation
 *		After operation it will be updated with the actual size of the
 *		result. In हाल of error where the dst sgl size was insufficient,
 *		it will be updated to the size required क्रम the operation.
 * @__ctx:	Start of निजी context data
 */
काष्ठा kpp_request अणु
	काष्ठा crypto_async_request base;
	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;
	अचिन्हित पूर्णांक src_len;
	अचिन्हित पूर्णांक dst_len;
	व्योम *__ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

/**
 * काष्ठा crypto_kpp - user-instantiated object which encapsulate
 * algorithms and core processing logic
 *
 * @base:	Common crypto API algorithm data काष्ठाure
 */
काष्ठा crypto_kpp अणु
	काष्ठा crypto_tfm base;
पूर्ण;

/**
 * काष्ठा kpp_alg - generic key-agreement protocol primitives
 *
 * @set_secret:		Function invokes the protocol specअगरic function to
 *			store the secret निजी key aदीर्घ with parameters.
 *			The implementation knows how to decode the buffer
 * @generate_खुला_key: Function generate the खुला key to be sent to the
 *			counterpart. In हाल of error, where output is not big
 *			enough req->dst_len will be updated to the size
 *			required
 * @compute_shared_secret: Function compute the shared secret as defined by
 *			the algorithm. The result is given back to the user.
 *			In हाल of error, where output is not big enough,
 *			req->dst_len will be updated to the size required
 * @max_size:		Function वापसs the size of the output buffer
 * @init:		Initialize the object. This is called only once at
 *			instantiation समय. In हाल the cryptographic hardware
 *			needs to be initialized. Software fallback should be
 *			put in place here.
 * @निकास:		Unकरो everything @init did.
 *
 * @reqsize:		Request context size required by algorithm
 *			implementation
 * @base:		Common crypto API algorithm data काष्ठाure
 */
काष्ठा kpp_alg अणु
	पूर्णांक (*set_secret)(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buffer,
			  अचिन्हित पूर्णांक len);
	पूर्णांक (*generate_खुला_key)(काष्ठा kpp_request *req);
	पूर्णांक (*compute_shared_secret)(काष्ठा kpp_request *req);

	अचिन्हित पूर्णांक (*max_size)(काष्ठा crypto_kpp *tfm);

	पूर्णांक (*init)(काष्ठा crypto_kpp *tfm);
	व्योम (*निकास)(काष्ठा crypto_kpp *tfm);

	अचिन्हित पूर्णांक reqsize;
	काष्ठा crypto_alg base;
पूर्ण;

/**
 * DOC: Generic Key-agreement Protocol Primitives API
 *
 * The KPP API is used with the algorithm type
 * CRYPTO_ALG_TYPE_KPP (listed as type "kpp" in /proc/crypto)
 */

/**
 * crypto_alloc_kpp() - allocate KPP tfm handle
 * @alg_name: is the name of the kpp algorithm (e.g. "dh", "ecdh")
 * @type: specअगरies the type of the algorithm
 * @mask: specअगरies the mask क्रम the algorithm
 *
 * Allocate a handle क्रम kpp algorithm. The वापसed काष्ठा crypto_kpp
 * is required क्रम any following API invocation
 *
 * Return: allocated handle in हाल of success; IS_ERR() is true in हाल of
 *	   an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_kpp *crypto_alloc_kpp(स्थिर अक्षर *alg_name, u32 type, u32 mask);

अटल अंतरभूत काष्ठा crypto_tfm *crypto_kpp_tfm(काष्ठा crypto_kpp *tfm)
अणु
	वापस &tfm->base;
पूर्ण

अटल अंतरभूत काष्ठा kpp_alg *__crypto_kpp_alg(काष्ठा crypto_alg *alg)
अणु
	वापस container_of(alg, काष्ठा kpp_alg, base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_kpp *__crypto_kpp_tfm(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm, काष्ठा crypto_kpp, base);
पूर्ण

अटल अंतरभूत काष्ठा kpp_alg *crypto_kpp_alg(काष्ठा crypto_kpp *tfm)
अणु
	वापस __crypto_kpp_alg(crypto_kpp_tfm(tfm)->__crt_alg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_kpp_reqsize(काष्ठा crypto_kpp *tfm)
अणु
	वापस crypto_kpp_alg(tfm)->reqsize;
पूर्ण

अटल अंतरभूत व्योम kpp_request_set_tfm(काष्ठा kpp_request *req,
				       काष्ठा crypto_kpp *tfm)
अणु
	req->base.tfm = crypto_kpp_tfm(tfm);
पूर्ण

अटल अंतरभूत काष्ठा crypto_kpp *crypto_kpp_reqtfm(काष्ठा kpp_request *req)
अणु
	वापस __crypto_kpp_tfm(req->base.tfm);
पूर्ण

अटल अंतरभूत u32 crypto_kpp_get_flags(काष्ठा crypto_kpp *tfm)
अणु
	वापस crypto_tfm_get_flags(crypto_kpp_tfm(tfm));
पूर्ण

अटल अंतरभूत व्योम crypto_kpp_set_flags(काष्ठा crypto_kpp *tfm, u32 flags)
अणु
	crypto_tfm_set_flags(crypto_kpp_tfm(tfm), flags);
पूर्ण

/**
 * crypto_मुक्त_kpp() - मुक्त KPP tfm handle
 *
 * @tfm: KPP tfm handle allocated with crypto_alloc_kpp()
 *
 * If @tfm is a शून्य or error poपूर्णांकer, this function करोes nothing.
 */
अटल अंतरभूत व्योम crypto_मुक्त_kpp(काष्ठा crypto_kpp *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_kpp_tfm(tfm));
पूर्ण

/**
 * kpp_request_alloc() - allocates kpp request
 *
 * @tfm:	KPP tfm handle allocated with crypto_alloc_kpp()
 * @gfp:	allocation flags
 *
 * Return: allocated handle in हाल of success or शून्य in हाल of an error.
 */
अटल अंतरभूत काष्ठा kpp_request *kpp_request_alloc(काष्ठा crypto_kpp *tfm,
						    gfp_t gfp)
अणु
	काष्ठा kpp_request *req;

	req = kदो_स्मृति(माप(*req) + crypto_kpp_reqsize(tfm), gfp);
	अगर (likely(req))
		kpp_request_set_tfm(req, tfm);

	वापस req;
पूर्ण

/**
 * kpp_request_मुक्त() - zeroize and मुक्त kpp request
 *
 * @req:	request to मुक्त
 */
अटल अंतरभूत व्योम kpp_request_मुक्त(काष्ठा kpp_request *req)
अणु
	kमुक्त_sensitive(req);
पूर्ण

/**
 * kpp_request_set_callback() - Sets an asynchronous callback.
 *
 * Callback will be called when an asynchronous operation on a given
 * request is finished.
 *
 * @req:	request that the callback will be set क्रम
 * @flgs:	specअगरy क्रम instance अगर the operation may backlog
 * @cmpl:	callback which will be called
 * @data:	निजी data used by the caller
 */
अटल अंतरभूत व्योम kpp_request_set_callback(काष्ठा kpp_request *req,
					    u32 flgs,
					    crypto_completion_t cmpl,
					    व्योम *data)
अणु
	req->base.complete = cmpl;
	req->base.data = data;
	req->base.flags = flgs;
पूर्ण

/**
 * kpp_request_set_input() - Sets input buffer
 *
 * Sets parameters required by generate_खुला_key
 *
 * @req:	kpp request
 * @input:	ptr to input scatter list
 * @input_len:	size of the input scatter list
 */
अटल अंतरभूत व्योम kpp_request_set_input(काष्ठा kpp_request *req,
					 काष्ठा scatterlist *input,
					 अचिन्हित पूर्णांक input_len)
अणु
	req->src = input;
	req->src_len = input_len;
पूर्ण

/**
 * kpp_request_set_output() - Sets output buffer
 *
 * Sets parameters required by kpp operation
 *
 * @req:	kpp request
 * @output:	ptr to output scatter list
 * @output_len:	size of the output scatter list
 */
अटल अंतरभूत व्योम kpp_request_set_output(काष्ठा kpp_request *req,
					  काष्ठा scatterlist *output,
					  अचिन्हित पूर्णांक output_len)
अणु
	req->dst = output;
	req->dst_len = output_len;
पूर्ण

क्रमागत अणु
	CRYPTO_KPP_SECRET_TYPE_UNKNOWN,
	CRYPTO_KPP_SECRET_TYPE_DH,
	CRYPTO_KPP_SECRET_TYPE_ECDH,
पूर्ण;

/**
 * काष्ठा kpp_secret - small header क्रम packing secret buffer
 *
 * @type:	define type of secret. Each kpp type will define its own
 * @len:	specअगरy the len of the secret, include the header, that
 *		follows the काष्ठा
 */
काष्ठा kpp_secret अणु
	अचिन्हित लघु type;
	अचिन्हित लघु len;
पूर्ण;

/**
 * crypto_kpp_set_secret() - Invoke kpp operation
 *
 * Function invokes the specअगरic kpp operation क्रम a given alg.
 *
 * @tfm:	tfm handle
 * @buffer:	Buffer holding the packet representation of the निजी
 *		key. The काष्ठाure of the packet key depends on the particular
 *		KPP implementation. Packing and unpacking helpers are provided
 *		क्रम ECDH and DH (see the respective header files क्रम those
 *		implementations).
 * @len:	Length of the packet निजी key buffer.
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_kpp_set_secret(काष्ठा crypto_kpp *tfm,
					स्थिर व्योम *buffer, अचिन्हित पूर्णांक len)
अणु
	काष्ठा kpp_alg *alg = crypto_kpp_alg(tfm);
	काष्ठा crypto_alg *calg = tfm->base.__crt_alg;
	पूर्णांक ret;

	crypto_stats_get(calg);
	ret = alg->set_secret(tfm, buffer, len);
	crypto_stats_kpp_set_secret(calg, ret);
	वापस ret;
पूर्ण

/**
 * crypto_kpp_generate_खुला_key() - Invoke kpp operation
 *
 * Function invokes the specअगरic kpp operation क्रम generating the खुला part
 * क्रम a given kpp algorithm.
 *
 * To generate a निजी key, the caller should use a अक्रमom number generator.
 * The output of the requested length serves as the निजी key.
 *
 * @req:	kpp key request
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_kpp_generate_खुला_key(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा kpp_alg *alg = crypto_kpp_alg(tfm);
	काष्ठा crypto_alg *calg = tfm->base.__crt_alg;
	पूर्णांक ret;

	crypto_stats_get(calg);
	ret = alg->generate_खुला_key(req);
	crypto_stats_kpp_generate_खुला_key(calg, ret);
	वापस ret;
पूर्ण

/**
 * crypto_kpp_compute_shared_secret() - Invoke kpp operation
 *
 * Function invokes the specअगरic kpp operation क्रम computing the shared secret
 * क्रम a given kpp algorithm.
 *
 * @req:	kpp key request
 *
 * Return: zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_kpp_compute_shared_secret(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा kpp_alg *alg = crypto_kpp_alg(tfm);
	काष्ठा crypto_alg *calg = tfm->base.__crt_alg;
	पूर्णांक ret;

	crypto_stats_get(calg);
	ret = alg->compute_shared_secret(req);
	crypto_stats_kpp_compute_shared_secret(calg, ret);
	वापस ret;
पूर्ण

/**
 * crypto_kpp_maxsize() - Get len क्रम output buffer
 *
 * Function वापसs the output buffer size required क्रम a given key.
 * Function assumes that the key is alपढ़ोy set in the transक्रमmation. If this
 * function is called without a setkey or with a failed setkey, you will end up
 * in a शून्य dereference.
 *
 * @tfm:	KPP tfm handle allocated with crypto_alloc_kpp()
 */
अटल अंतरभूत अचिन्हित पूर्णांक crypto_kpp_maxsize(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा kpp_alg *alg = crypto_kpp_alg(tfm);

	वापस alg->max_size(tfm);
पूर्ण

#पूर्ण_अगर
