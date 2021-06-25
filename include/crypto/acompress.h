<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Asynchronous Compression operations
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Weigang Li <weigang.li@पूर्णांकel.com>
 *          Giovanni Cabiddu <giovanni.cabiddu@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_ACOMP_H
#घोषणा _CRYPTO_ACOMP_H
#समावेश <linux/crypto.h>

#घोषणा CRYPTO_ACOMP_ALLOC_OUTPUT	0x00000001

/**
 * काष्ठा acomp_req - asynchronous (de)compression request
 *
 * @base:	Common attributes क्रम asynchronous crypto requests
 * @src:	Source Data
 * @dst:	Destination data
 * @slen:	Size of the input buffer
 * @dlen:	Size of the output buffer and number of bytes produced
 * @flags:	Internal flags
 * @__ctx:	Start of निजी context data
 */
काष्ठा acomp_req अणु
	काष्ठा crypto_async_request base;
	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;
	अचिन्हित पूर्णांक slen;
	अचिन्हित पूर्णांक dlen;
	u32 flags;
	व्योम *__ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

/**
 * काष्ठा crypto_acomp - user-instantiated objects which encapsulate
 * algorithms and core processing logic
 *
 * @compress:		Function perक्रमms a compress operation
 * @decompress:		Function perक्रमms a de-compress operation
 * @dst_मुक्त:		Frees destination buffer अगर allocated inside the
 *			algorithm
 * @reqsize:		Context size क्रम (de)compression requests
 * @base:		Common crypto API algorithm data काष्ठाure
 */
काष्ठा crypto_acomp अणु
	पूर्णांक (*compress)(काष्ठा acomp_req *req);
	पूर्णांक (*decompress)(काष्ठा acomp_req *req);
	व्योम (*dst_मुक्त)(काष्ठा scatterlist *dst);
	अचिन्हित पूर्णांक reqsize;
	काष्ठा crypto_tfm base;
पूर्ण;

/**
 * काष्ठा acomp_alg - asynchronous compression algorithm
 *
 * @compress:	Function perक्रमms a compress operation
 * @decompress:	Function perक्रमms a de-compress operation
 * @dst_मुक्त:	Frees destination buffer अगर allocated inside the algorithm
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
 * @reqsize:	Context size क्रम (de)compression requests
 * @base:	Common crypto API algorithm data काष्ठाure
 */
काष्ठा acomp_alg अणु
	पूर्णांक (*compress)(काष्ठा acomp_req *req);
	पूर्णांक (*decompress)(काष्ठा acomp_req *req);
	व्योम (*dst_मुक्त)(काष्ठा scatterlist *dst);
	पूर्णांक (*init)(काष्ठा crypto_acomp *tfm);
	व्योम (*निकास)(काष्ठा crypto_acomp *tfm);
	अचिन्हित पूर्णांक reqsize;
	काष्ठा crypto_alg base;
पूर्ण;

/**
 * DOC: Asynchronous Compression API
 *
 * The Asynchronous Compression API is used with the algorithms of type
 * CRYPTO_ALG_TYPE_ACOMPRESS (listed as type "acomp" in /proc/crypto)
 */

/**
 * crypto_alloc_acomp() -- allocate ACOMPRESS tfm handle
 * @alg_name:	is the cra_name / name or cra_driver_name / driver name of the
 *		compression algorithm e.g. "deflate"
 * @type:	specअगरies the type of the algorithm
 * @mask:	specअगरies the mask क्रम the algorithm
 *
 * Allocate a handle क्रम a compression algorithm. The वापसed काष्ठा
 * crypto_acomp is the handle that is required क्रम any subsequent
 * API invocation क्रम the compression operations.
 *
 * Return:	allocated handle in हाल of success; IS_ERR() is true in हाल
 *		of an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_acomp *crypto_alloc_acomp(स्थिर अक्षर *alg_name, u32 type,
					u32 mask);
/**
 * crypto_alloc_acomp_node() -- allocate ACOMPRESS tfm handle with desired NUMA node
 * @alg_name:	is the cra_name / name or cra_driver_name / driver name of the
 *		compression algorithm e.g. "deflate"
 * @type:	specअगरies the type of the algorithm
 * @mask:	specअगरies the mask क्रम the algorithm
 * @node:	specअगरies the NUMA node the ZIP hardware beदीर्घs to
 *
 * Allocate a handle क्रम a compression algorithm. Drivers should try to use
 * (de)compressors on the specअगरied NUMA node.
 * The वापसed काष्ठा crypto_acomp is the handle that is required क्रम any
 * subsequent API invocation क्रम the compression operations.
 *
 * Return:	allocated handle in हाल of success; IS_ERR() is true in हाल
 *		of an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_acomp *crypto_alloc_acomp_node(स्थिर अक्षर *alg_name, u32 type,
					u32 mask, पूर्णांक node);

अटल अंतरभूत काष्ठा crypto_tfm *crypto_acomp_tfm(काष्ठा crypto_acomp *tfm)
अणु
	वापस &tfm->base;
पूर्ण

अटल अंतरभूत काष्ठा acomp_alg *__crypto_acomp_alg(काष्ठा crypto_alg *alg)
अणु
	वापस container_of(alg, काष्ठा acomp_alg, base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_acomp *__crypto_acomp_tfm(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm, काष्ठा crypto_acomp, base);
पूर्ण

अटल अंतरभूत काष्ठा acomp_alg *crypto_acomp_alg(काष्ठा crypto_acomp *tfm)
अणु
	वापस __crypto_acomp_alg(crypto_acomp_tfm(tfm)->__crt_alg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_acomp_reqsize(काष्ठा crypto_acomp *tfm)
अणु
	वापस tfm->reqsize;
पूर्ण

अटल अंतरभूत व्योम acomp_request_set_tfm(काष्ठा acomp_req *req,
					 काष्ठा crypto_acomp *tfm)
अणु
	req->base.tfm = crypto_acomp_tfm(tfm);
पूर्ण

अटल अंतरभूत काष्ठा crypto_acomp *crypto_acomp_reqtfm(काष्ठा acomp_req *req)
अणु
	वापस __crypto_acomp_tfm(req->base.tfm);
पूर्ण

/**
 * crypto_मुक्त_acomp() -- मुक्त ACOMPRESS tfm handle
 *
 * @tfm:	ACOMPRESS tfm handle allocated with crypto_alloc_acomp()
 *
 * If @tfm is a शून्य or error poपूर्णांकer, this function करोes nothing.
 */
अटल अंतरभूत व्योम crypto_मुक्त_acomp(काष्ठा crypto_acomp *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_acomp_tfm(tfm));
पूर्ण

अटल अंतरभूत पूर्णांक crypto_has_acomp(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	type &= ~CRYPTO_ALG_TYPE_MASK;
	type |= CRYPTO_ALG_TYPE_ACOMPRESS;
	mask |= CRYPTO_ALG_TYPE_ACOMPRESS_MASK;

	वापस crypto_has_alg(alg_name, type, mask);
पूर्ण

/**
 * acomp_request_alloc() -- allocates asynchronous (de)compression request
 *
 * @tfm:	ACOMPRESS tfm handle allocated with crypto_alloc_acomp()
 *
 * Return:	allocated handle in हाल of success or शून्य in हाल of an error
 */
काष्ठा acomp_req *acomp_request_alloc(काष्ठा crypto_acomp *tfm);

/**
 * acomp_request_मुक्त() -- zeroize and मुक्त asynchronous (de)compression
 *			   request as well as the output buffer अगर allocated
 *			   inside the algorithm
 *
 * @req:	request to मुक्त
 */
व्योम acomp_request_मुक्त(काष्ठा acomp_req *req);

/**
 * acomp_request_set_callback() -- Sets an asynchronous callback
 *
 * Callback will be called when an asynchronous operation on a given
 * request is finished.
 *
 * @req:	request that the callback will be set क्रम
 * @flgs:	specअगरy क्रम instance अगर the operation may backlog
 * @cmlp:	callback which will be called
 * @data:	निजी data used by the caller
 */
अटल अंतरभूत व्योम acomp_request_set_callback(काष्ठा acomp_req *req,
					      u32 flgs,
					      crypto_completion_t cmpl,
					      व्योम *data)
अणु
	req->base.complete = cmpl;
	req->base.data = data;
	req->base.flags = flgs;
पूर्ण

/**
 * acomp_request_set_params() -- Sets request parameters
 *
 * Sets parameters required by an acomp operation
 *
 * @req:	asynchronous compress request
 * @src:	poपूर्णांकer to input buffer scatterlist
 * @dst:	poपूर्णांकer to output buffer scatterlist. If this is शून्य, the
 *		acomp layer will allocate the output memory
 * @slen:	size of the input buffer
 * @dlen:	size of the output buffer. If dst is शून्य, this can be used by
 *		the user to specअगरy the maximum amount of memory to allocate
 */
अटल अंतरभूत व्योम acomp_request_set_params(काष्ठा acomp_req *req,
					    काष्ठा scatterlist *src,
					    काष्ठा scatterlist *dst,
					    अचिन्हित पूर्णांक slen,
					    अचिन्हित पूर्णांक dlen)
अणु
	req->src = src;
	req->dst = dst;
	req->slen = slen;
	req->dlen = dlen;

	अगर (!req->dst)
		req->flags |= CRYPTO_ACOMP_ALLOC_OUTPUT;
पूर्ण

/**
 * crypto_acomp_compress() -- Invoke asynchronous compress operation
 *
 * Function invokes the asynchronous compress operation
 *
 * @req:	asynchronous compress request
 *
 * Return:	zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_acomp_compress(काष्ठा acomp_req *req)
अणु
	काष्ठा crypto_acomp *tfm = crypto_acomp_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक slen = req->slen;
	पूर्णांक ret;

	crypto_stats_get(alg);
	ret = tfm->compress(req);
	crypto_stats_compress(slen, ret, alg);
	वापस ret;
पूर्ण

/**
 * crypto_acomp_decompress() -- Invoke asynchronous decompress operation
 *
 * Function invokes the asynchronous decompress operation
 *
 * @req:	asynchronous compress request
 *
 * Return:	zero on success; error code in हाल of error
 */
अटल अंतरभूत पूर्णांक crypto_acomp_decompress(काष्ठा acomp_req *req)
अणु
	काष्ठा crypto_acomp *tfm = crypto_acomp_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक slen = req->slen;
	पूर्णांक ret;

	crypto_stats_get(alg);
	ret = tfm->decompress(req);
	crypto_stats_decompress(slen, ret, alg);
	वापस ret;
पूर्ण

#पूर्ण_अगर
