<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /* Algorithms supported by virtio crypto device
  *
  * Authors: Gonglei <arei.gonglei@huawei.com>
  *
  * Copyright 2016 HUAWEI TECHNOLOGIES CO., LTD.
  */

#समावेश <linux/scatterlist.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/err.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/atomic.h>

#समावेश <uapi/linux/virtio_crypto.h>
#समावेश "virtio_crypto_common.h"


काष्ठा virtio_crypto_skcipher_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	काष्ठा virtio_crypto *vcrypto;
	काष्ठा crypto_skcipher *tfm;

	काष्ठा virtio_crypto_sym_session_info enc_sess_info;
	काष्ठा virtio_crypto_sym_session_info dec_sess_info;
पूर्ण;

काष्ठा virtio_crypto_sym_request अणु
	काष्ठा virtio_crypto_request base;

	/* Cipher or aead */
	uपूर्णांक32_t type;
	काष्ठा virtio_crypto_skcipher_ctx *skcipher_ctx;
	काष्ठा skcipher_request *skcipher_req;
	uपूर्णांक8_t *iv;
	/* Encryption? */
	bool encrypt;
पूर्ण;

काष्ठा virtio_crypto_algo अणु
	uपूर्णांक32_t algonum;
	uपूर्णांक32_t service;
	अचिन्हित पूर्णांक active_devs;
	काष्ठा skcipher_alg algo;
पूर्ण;

/*
 * The algs_lock protects the below global virtio_crypto_active_devs
 * and crypto algorithms registion.
 */
अटल DEFINE_MUTEX(algs_lock);
अटल व्योम virtio_crypto_skcipher_finalize_req(
	काष्ठा virtio_crypto_sym_request *vc_sym_req,
	काष्ठा skcipher_request *req,
	पूर्णांक err);

अटल व्योम virtio_crypto_dataq_sym_callback
		(काष्ठा virtio_crypto_request *vc_req, पूर्णांक len)
अणु
	काष्ठा virtio_crypto_sym_request *vc_sym_req =
		container_of(vc_req, काष्ठा virtio_crypto_sym_request, base);
	काष्ठा skcipher_request *ablk_req;
	पूर्णांक error;

	/* Finish the encrypt or decrypt process */
	अगर (vc_sym_req->type == VIRTIO_CRYPTO_SYM_OP_CIPHER) अणु
		चयन (vc_req->status) अणु
		हाल VIRTIO_CRYPTO_OK:
			error = 0;
			अवरोध;
		हाल VIRTIO_CRYPTO_INVSESS:
		हाल VIRTIO_CRYPTO_ERR:
			error = -EINVAL;
			अवरोध;
		हाल VIRTIO_CRYPTO_BADMSG:
			error = -EBADMSG;
			अवरोध;
		शेष:
			error = -EIO;
			अवरोध;
		पूर्ण
		ablk_req = vc_sym_req->skcipher_req;
		virtio_crypto_skcipher_finalize_req(vc_sym_req,
							ablk_req, error);
	पूर्ण
पूर्ण

अटल u64 virtio_crypto_alg_sg_nents_length(काष्ठा scatterlist *sg)
अणु
	u64 total = 0;

	क्रम (total = 0; sg; sg = sg_next(sg))
		total += sg->length;

	वापस total;
पूर्ण

अटल पूर्णांक
virtio_crypto_alg_validate_key(पूर्णांक key_len, uपूर्णांक32_t *alg)
अणु
	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
	हाल AES_KEYSIZE_192:
	हाल AES_KEYSIZE_256:
		*alg = VIRTIO_CRYPTO_CIPHER_AES_CBC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_crypto_alg_skcipher_init_session(
		काष्ठा virtio_crypto_skcipher_ctx *ctx,
		uपूर्णांक32_t alg, स्थिर uपूर्णांक8_t *key,
		अचिन्हित पूर्णांक keylen,
		पूर्णांक encrypt)
अणु
	काष्ठा scatterlist outhdr, key_sg, inhdr, *sgs[3];
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा virtio_crypto *vcrypto = ctx->vcrypto;
	पूर्णांक op = encrypt ? VIRTIO_CRYPTO_OP_ENCRYPT : VIRTIO_CRYPTO_OP_DECRYPT;
	पूर्णांक err;
	अचिन्हित पूर्णांक num_out = 0, num_in = 0;

	/*
	 * Aव्योम to करो DMA from the stack, चयन to using
	 * dynamically-allocated क्रम the key
	 */
	uपूर्णांक8_t *cipher_key = kmemdup(key, keylen, GFP_ATOMIC);

	अगर (!cipher_key)
		वापस -ENOMEM;

	spin_lock(&vcrypto->ctrl_lock);
	/* Pad ctrl header */
	vcrypto->ctrl.header.opcode =
		cpu_to_le32(VIRTIO_CRYPTO_CIPHER_CREATE_SESSION);
	vcrypto->ctrl.header.algo = cpu_to_le32(alg);
	/* Set the शेष dataqueue id to 0 */
	vcrypto->ctrl.header.queue_id = 0;

	vcrypto->input.status = cpu_to_le32(VIRTIO_CRYPTO_ERR);
	/* Pad cipher's parameters */
	vcrypto->ctrl.u.sym_create_session.op_type =
		cpu_to_le32(VIRTIO_CRYPTO_SYM_OP_CIPHER);
	vcrypto->ctrl.u.sym_create_session.u.cipher.para.algo =
		vcrypto->ctrl.header.algo;
	vcrypto->ctrl.u.sym_create_session.u.cipher.para.keylen =
		cpu_to_le32(keylen);
	vcrypto->ctrl.u.sym_create_session.u.cipher.para.op =
		cpu_to_le32(op);

	sg_init_one(&outhdr, &vcrypto->ctrl, माप(vcrypto->ctrl));
	sgs[num_out++] = &outhdr;

	/* Set key */
	sg_init_one(&key_sg, cipher_key, keylen);
	sgs[num_out++] = &key_sg;

	/* Return status and session id back */
	sg_init_one(&inhdr, &vcrypto->input, माप(vcrypto->input));
	sgs[num_out + num_in++] = &inhdr;

	err = virtqueue_add_sgs(vcrypto->ctrl_vq, sgs, num_out,
				num_in, vcrypto, GFP_ATOMIC);
	अगर (err < 0) अणु
		spin_unlock(&vcrypto->ctrl_lock);
		kमुक्त_sensitive(cipher_key);
		वापस err;
	पूर्ण
	virtqueue_kick(vcrypto->ctrl_vq);

	/*
	 * Trapping पूर्णांकo the hypervisor, so the request should be
	 * handled immediately.
	 */
	जबतक (!virtqueue_get_buf(vcrypto->ctrl_vq, &पंचांगp) &&
	       !virtqueue_is_broken(vcrypto->ctrl_vq))
		cpu_relax();

	अगर (le32_to_cpu(vcrypto->input.status) != VIRTIO_CRYPTO_OK) अणु
		spin_unlock(&vcrypto->ctrl_lock);
		pr_err("virtio_crypto: Create session failed status: %u\n",
			le32_to_cpu(vcrypto->input.status));
		kमुक्त_sensitive(cipher_key);
		वापस -EINVAL;
	पूर्ण

	अगर (encrypt)
		ctx->enc_sess_info.session_id =
			le64_to_cpu(vcrypto->input.session_id);
	अन्यथा
		ctx->dec_sess_info.session_id =
			le64_to_cpu(vcrypto->input.session_id);

	spin_unlock(&vcrypto->ctrl_lock);

	kमुक्त_sensitive(cipher_key);
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_crypto_alg_skcipher_बंद_session(
		काष्ठा virtio_crypto_skcipher_ctx *ctx,
		पूर्णांक encrypt)
अणु
	काष्ठा scatterlist outhdr, status_sg, *sgs[2];
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा virtio_crypto_destroy_session_req *destroy_session;
	काष्ठा virtio_crypto *vcrypto = ctx->vcrypto;
	पूर्णांक err;
	अचिन्हित पूर्णांक num_out = 0, num_in = 0;

	spin_lock(&vcrypto->ctrl_lock);
	vcrypto->ctrl_status.status = VIRTIO_CRYPTO_ERR;
	/* Pad ctrl header */
	vcrypto->ctrl.header.opcode =
		cpu_to_le32(VIRTIO_CRYPTO_CIPHER_DESTROY_SESSION);
	/* Set the शेष virtqueue id to 0 */
	vcrypto->ctrl.header.queue_id = 0;

	destroy_session = &vcrypto->ctrl.u.destroy_session;

	अगर (encrypt)
		destroy_session->session_id =
			cpu_to_le64(ctx->enc_sess_info.session_id);
	अन्यथा
		destroy_session->session_id =
			cpu_to_le64(ctx->dec_sess_info.session_id);

	sg_init_one(&outhdr, &vcrypto->ctrl, माप(vcrypto->ctrl));
	sgs[num_out++] = &outhdr;

	/* Return status and session id back */
	sg_init_one(&status_sg, &vcrypto->ctrl_status.status,
		माप(vcrypto->ctrl_status.status));
	sgs[num_out + num_in++] = &status_sg;

	err = virtqueue_add_sgs(vcrypto->ctrl_vq, sgs, num_out,
			num_in, vcrypto, GFP_ATOMIC);
	अगर (err < 0) अणु
		spin_unlock(&vcrypto->ctrl_lock);
		वापस err;
	पूर्ण
	virtqueue_kick(vcrypto->ctrl_vq);

	जबतक (!virtqueue_get_buf(vcrypto->ctrl_vq, &पंचांगp) &&
	       !virtqueue_is_broken(vcrypto->ctrl_vq))
		cpu_relax();

	अगर (vcrypto->ctrl_status.status != VIRTIO_CRYPTO_OK) अणु
		spin_unlock(&vcrypto->ctrl_lock);
		pr_err("virtio_crypto: Close session failed status: %u, session_id: 0x%llx\n",
			vcrypto->ctrl_status.status,
			destroy_session->session_id);

		वापस -EINVAL;
	पूर्ण
	spin_unlock(&vcrypto->ctrl_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक virtio_crypto_alg_skcipher_init_sessions(
		काष्ठा virtio_crypto_skcipher_ctx *ctx,
		स्थिर uपूर्णांक8_t *key, अचिन्हित पूर्णांक keylen)
अणु
	uपूर्णांक32_t alg;
	पूर्णांक ret;
	काष्ठा virtio_crypto *vcrypto = ctx->vcrypto;

	अगर (keylen > vcrypto->max_cipher_key_len) अणु
		pr_err("virtio_crypto: the key is too long\n");
		वापस -EINVAL;
	पूर्ण

	अगर (virtio_crypto_alg_validate_key(keylen, &alg))
		वापस -EINVAL;

	/* Create encryption session */
	ret = virtio_crypto_alg_skcipher_init_session(ctx,
			alg, key, keylen, 1);
	अगर (ret)
		वापस ret;
	/* Create decryption session */
	ret = virtio_crypto_alg_skcipher_init_session(ctx,
			alg, key, keylen, 0);
	अगर (ret) अणु
		virtio_crypto_alg_skcipher_बंद_session(ctx, 1);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Note: kernel crypto API realization */
अटल पूर्णांक virtio_crypto_skcipher_setkey(काष्ठा crypto_skcipher *tfm,
					 स्थिर uपूर्णांक8_t *key,
					 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा virtio_crypto_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	uपूर्णांक32_t alg;
	पूर्णांक ret;

	ret = virtio_crypto_alg_validate_key(keylen, &alg);
	अगर (ret)
		वापस ret;

	अगर (!ctx->vcrypto) अणु
		/* New key */
		पूर्णांक node = virtio_crypto_get_current_node();
		काष्ठा virtio_crypto *vcrypto =
				      virtcrypto_get_dev_node(node,
				      VIRTIO_CRYPTO_SERVICE_CIPHER, alg);
		अगर (!vcrypto) अणु
			pr_err("virtio_crypto: Could not find a virtio device in the system or unsupported algo\n");
			वापस -ENODEV;
		पूर्ण

		ctx->vcrypto = vcrypto;
	पूर्ण अन्यथा अणु
		/* Rekeying, we should बंद the created sessions previously */
		virtio_crypto_alg_skcipher_बंद_session(ctx, 1);
		virtio_crypto_alg_skcipher_बंद_session(ctx, 0);
	पूर्ण

	ret = virtio_crypto_alg_skcipher_init_sessions(ctx, key, keylen);
	अगर (ret) अणु
		virtcrypto_dev_put(ctx->vcrypto);
		ctx->vcrypto = शून्य;

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
__virtio_crypto_skcipher_करो_req(काष्ठा virtio_crypto_sym_request *vc_sym_req,
		काष्ठा skcipher_request *req,
		काष्ठा data_queue *data_vq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा virtio_crypto_skcipher_ctx *ctx = vc_sym_req->skcipher_ctx;
	काष्ठा virtio_crypto_request *vc_req = &vc_sym_req->base;
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(tfm);
	काष्ठा virtio_crypto *vcrypto = ctx->vcrypto;
	काष्ठा virtio_crypto_op_data_req *req_data;
	पूर्णांक src_nents, dst_nents;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा scatterlist outhdr, iv_sg, status_sg, **sgs;
	u64 dst_len;
	अचिन्हित पूर्णांक num_out = 0, num_in = 0;
	पूर्णांक sg_total;
	uपूर्णांक8_t *iv;
	काष्ठा scatterlist *sg;

	src_nents = sg_nents_क्रम_len(req->src, req->cryptlen);
	अगर (src_nents < 0) अणु
		pr_err("Invalid number of src SG.\n");
		वापस src_nents;
	पूर्ण

	dst_nents = sg_nents(req->dst);

	pr_debug("virtio_crypto: Number of sgs (src_nents: %d, dst_nents: %d)\n",
			src_nents, dst_nents);

	/* Why 3?  outhdr + iv + inhdr */
	sg_total = src_nents + dst_nents + 3;
	sgs = kसुस्मृति_node(sg_total, माप(*sgs), GFP_KERNEL,
				dev_to_node(&vcrypto->vdev->dev));
	अगर (!sgs)
		वापस -ENOMEM;

	req_data = kzalloc_node(माप(*req_data), GFP_KERNEL,
				dev_to_node(&vcrypto->vdev->dev));
	अगर (!req_data) अणु
		kमुक्त(sgs);
		वापस -ENOMEM;
	पूर्ण

	vc_req->req_data = req_data;
	vc_sym_req->type = VIRTIO_CRYPTO_SYM_OP_CIPHER;
	/* Head of operation */
	अगर (vc_sym_req->encrypt) अणु
		req_data->header.session_id =
			cpu_to_le64(ctx->enc_sess_info.session_id);
		req_data->header.opcode =
			cpu_to_le32(VIRTIO_CRYPTO_CIPHER_ENCRYPT);
	पूर्ण अन्यथा अणु
		req_data->header.session_id =
			cpu_to_le64(ctx->dec_sess_info.session_id);
		req_data->header.opcode =
			cpu_to_le32(VIRTIO_CRYPTO_CIPHER_DECRYPT);
	पूर्ण
	req_data->u.sym_req.op_type = cpu_to_le32(VIRTIO_CRYPTO_SYM_OP_CIPHER);
	req_data->u.sym_req.u.cipher.para.iv_len = cpu_to_le32(ivsize);
	req_data->u.sym_req.u.cipher.para.src_data_len =
			cpu_to_le32(req->cryptlen);

	dst_len = virtio_crypto_alg_sg_nents_length(req->dst);
	अगर (unlikely(dst_len > U32_MAX)) अणु
		pr_err("virtio_crypto: The dst_len is beyond U32_MAX\n");
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	dst_len = min_t(अचिन्हित पूर्णांक, req->cryptlen, dst_len);
	pr_debug("virtio_crypto: src_len: %u, dst_len: %llu\n",
			req->cryptlen, dst_len);

	अगर (unlikely(req->cryptlen + dst_len + ivsize +
		माप(vc_req->status) > vcrypto->max_size)) अणु
		pr_err("virtio_crypto: The length is too big\n");
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	req_data->u.sym_req.u.cipher.para.dst_data_len =
			cpu_to_le32((uपूर्णांक32_t)dst_len);

	/* Outhdr */
	sg_init_one(&outhdr, req_data, माप(*req_data));
	sgs[num_out++] = &outhdr;

	/* IV */

	/*
	 * Aव्योम to करो DMA from the stack, चयन to using
	 * dynamically-allocated क्रम the IV
	 */
	iv = kzalloc_node(ivsize, GFP_ATOMIC,
				dev_to_node(&vcrypto->vdev->dev));
	अगर (!iv) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण
	स_नकल(iv, req->iv, ivsize);
	अगर (!vc_sym_req->encrypt)
		scatterwalk_map_and_copy(req->iv, req->src,
					 req->cryptlen - AES_BLOCK_SIZE,
					 AES_BLOCK_SIZE, 0);

	sg_init_one(&iv_sg, iv, ivsize);
	sgs[num_out++] = &iv_sg;
	vc_sym_req->iv = iv;

	/* Source data */
	क्रम (sg = req->src; src_nents; sg = sg_next(sg), src_nents--)
		sgs[num_out++] = sg;

	/* Destination data */
	क्रम (sg = req->dst; sg; sg = sg_next(sg))
		sgs[num_out + num_in++] = sg;

	/* Status */
	sg_init_one(&status_sg, &vc_req->status, माप(vc_req->status));
	sgs[num_out + num_in++] = &status_sg;

	vc_req->sgs = sgs;

	spin_lock_irqsave(&data_vq->lock, flags);
	err = virtqueue_add_sgs(data_vq->vq, sgs, num_out,
				num_in, vc_req, GFP_ATOMIC);
	virtqueue_kick(data_vq->vq);
	spin_unlock_irqrestore(&data_vq->lock, flags);
	अगर (unlikely(err < 0))
		जाओ मुक्त_iv;

	वापस 0;

मुक्त_iv:
	kमुक्त_sensitive(iv);
मुक्त:
	kमुक्त_sensitive(req_data);
	kमुक्त(sgs);
	वापस err;
पूर्ण

अटल पूर्णांक virtio_crypto_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *atfm = crypto_skcipher_reqtfm(req);
	काष्ठा virtio_crypto_skcipher_ctx *ctx = crypto_skcipher_ctx(atfm);
	काष्ठा virtio_crypto_sym_request *vc_sym_req =
				skcipher_request_ctx(req);
	काष्ठा virtio_crypto_request *vc_req = &vc_sym_req->base;
	काष्ठा virtio_crypto *vcrypto = ctx->vcrypto;
	/* Use the first data virtqueue as शेष */
	काष्ठा data_queue *data_vq = &vcrypto->data_vq[0];

	अगर (!req->cryptlen)
		वापस 0;
	अगर (req->cryptlen % AES_BLOCK_SIZE)
		वापस -EINVAL;

	vc_req->dataq = data_vq;
	vc_req->alg_cb = virtio_crypto_dataq_sym_callback;
	vc_sym_req->skcipher_ctx = ctx;
	vc_sym_req->skcipher_req = req;
	vc_sym_req->encrypt = true;

	वापस crypto_transfer_skcipher_request_to_engine(data_vq->engine, req);
पूर्ण

अटल पूर्णांक virtio_crypto_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *atfm = crypto_skcipher_reqtfm(req);
	काष्ठा virtio_crypto_skcipher_ctx *ctx = crypto_skcipher_ctx(atfm);
	काष्ठा virtio_crypto_sym_request *vc_sym_req =
				skcipher_request_ctx(req);
	काष्ठा virtio_crypto_request *vc_req = &vc_sym_req->base;
	काष्ठा virtio_crypto *vcrypto = ctx->vcrypto;
	/* Use the first data virtqueue as शेष */
	काष्ठा data_queue *data_vq = &vcrypto->data_vq[0];

	अगर (!req->cryptlen)
		वापस 0;
	अगर (req->cryptlen % AES_BLOCK_SIZE)
		वापस -EINVAL;

	vc_req->dataq = data_vq;
	vc_req->alg_cb = virtio_crypto_dataq_sym_callback;
	vc_sym_req->skcipher_ctx = ctx;
	vc_sym_req->skcipher_req = req;
	vc_sym_req->encrypt = false;

	वापस crypto_transfer_skcipher_request_to_engine(data_vq->engine, req);
पूर्ण

अटल पूर्णांक virtio_crypto_skcipher_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा virtio_crypto_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा virtio_crypto_sym_request));
	ctx->tfm = tfm;

	ctx->enginectx.op.करो_one_request = virtio_crypto_skcipher_crypt_req;
	ctx->enginectx.op.prepare_request = शून्य;
	ctx->enginectx.op.unprepare_request = शून्य;
	वापस 0;
पूर्ण

अटल व्योम virtio_crypto_skcipher_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा virtio_crypto_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (!ctx->vcrypto)
		वापस;

	virtio_crypto_alg_skcipher_बंद_session(ctx, 1);
	virtio_crypto_alg_skcipher_बंद_session(ctx, 0);
	virtcrypto_dev_put(ctx->vcrypto);
	ctx->vcrypto = शून्य;
पूर्ण

पूर्णांक virtio_crypto_skcipher_crypt_req(
	काष्ठा crypto_engine *engine, व्योम *vreq)
अणु
	काष्ठा skcipher_request *req = container_of(vreq, काष्ठा skcipher_request, base);
	काष्ठा virtio_crypto_sym_request *vc_sym_req =
				skcipher_request_ctx(req);
	काष्ठा virtio_crypto_request *vc_req = &vc_sym_req->base;
	काष्ठा data_queue *data_vq = vc_req->dataq;
	पूर्णांक ret;

	ret = __virtio_crypto_skcipher_करो_req(vc_sym_req, req, data_vq);
	अगर (ret < 0)
		वापस ret;

	virtqueue_kick(data_vq->vq);

	वापस 0;
पूर्ण

अटल व्योम virtio_crypto_skcipher_finalize_req(
	काष्ठा virtio_crypto_sym_request *vc_sym_req,
	काष्ठा skcipher_request *req,
	पूर्णांक err)
अणु
	अगर (vc_sym_req->encrypt)
		scatterwalk_map_and_copy(req->iv, req->dst,
					 req->cryptlen - AES_BLOCK_SIZE,
					 AES_BLOCK_SIZE, 0);
	kमुक्त_sensitive(vc_sym_req->iv);
	virtcrypto_clear_request(&vc_sym_req->base);

	crypto_finalize_skcipher_request(vc_sym_req->base.dataq->engine,
					   req, err);
पूर्ण

अटल काष्ठा virtio_crypto_algo virtio_crypto_algs[] = अणु अणु
	.algonum = VIRTIO_CRYPTO_CIPHER_AES_CBC,
	.service = VIRTIO_CRYPTO_SERVICE_CIPHER,
	.algo = अणु
		.base.cra_name		= "cbc(aes)",
		.base.cra_driver_name	= "virtio_crypto_aes_cbc",
		.base.cra_priority	= 150,
		.base.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा virtio_crypto_skcipher_ctx),
		.base.cra_module	= THIS_MODULE,
		.init			= virtio_crypto_skcipher_init,
		.निकास			= virtio_crypto_skcipher_निकास,
		.setkey			= virtio_crypto_skcipher_setkey,
		.decrypt		= virtio_crypto_skcipher_decrypt,
		.encrypt		= virtio_crypto_skcipher_encrypt,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
	पूर्ण,
पूर्ण पूर्ण;

पूर्णांक virtio_crypto_algs_रेजिस्टर(काष्ठा virtio_crypto *vcrypto)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i = 0;

	mutex_lock(&algs_lock);

	क्रम (i = 0; i < ARRAY_SIZE(virtio_crypto_algs); i++) अणु

		uपूर्णांक32_t service = virtio_crypto_algs[i].service;
		uपूर्णांक32_t algonum = virtio_crypto_algs[i].algonum;

		अगर (!virtcrypto_algo_is_supported(vcrypto, service, algonum))
			जारी;

		अगर (virtio_crypto_algs[i].active_devs == 0) अणु
			ret = crypto_रेजिस्टर_skcipher(&virtio_crypto_algs[i].algo);
			अगर (ret)
				जाओ unlock;
		पूर्ण

		virtio_crypto_algs[i].active_devs++;
		dev_info(&vcrypto->vdev->dev, "Registered algo %s\n",
			 virtio_crypto_algs[i].algo.base.cra_name);
	पूर्ण

unlock:
	mutex_unlock(&algs_lock);
	वापस ret;
पूर्ण

व्योम virtio_crypto_algs_unरेजिस्टर(काष्ठा virtio_crypto *vcrypto)
अणु
	पूर्णांक i = 0;

	mutex_lock(&algs_lock);

	क्रम (i = 0; i < ARRAY_SIZE(virtio_crypto_algs); i++) अणु

		uपूर्णांक32_t service = virtio_crypto_algs[i].service;
		uपूर्णांक32_t algonum = virtio_crypto_algs[i].algonum;

		अगर (virtio_crypto_algs[i].active_devs == 0 ||
		    !virtcrypto_algo_is_supported(vcrypto, service, algonum))
			जारी;

		अगर (virtio_crypto_algs[i].active_devs == 1)
			crypto_unरेजिस्टर_skcipher(&virtio_crypto_algs[i].algo);

		virtio_crypto_algs[i].active_devs--;
	पूर्ण

	mutex_unlock(&algs_lock);
पूर्ण
