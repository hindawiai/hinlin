<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * algअगर_aead: User-space पूर्णांकerface क्रम AEAD algorithms
 *
 * Copyright (C) 2014, Stephan Mueller <smueller@chronox.de>
 *
 * This file provides the user-space API क्रम AEAD ciphers.
 *
 * The following concept of the memory management is used:
 *
 * The kernel मुख्यtains two SGLs, the TX SGL and the RX SGL. The TX SGL is
 * filled by user space with the data submitted via sendpage/sendmsg. Filling
 * up the TX SGL करोes not cause a crypto operation -- the data will only be
 * tracked by the kernel. Upon receipt of one recvmsg call, the caller must
 * provide a buffer which is tracked with the RX SGL.
 *
 * During the processing of the recvmsg operation, the cipher request is
 * allocated and prepared. As part of the recvmsg operation, the processed
 * TX buffers are extracted from the TX SGL पूर्णांकo a separate SGL.
 *
 * After the completion of the crypto operation, the RX SGL and the cipher
 * request is released. The extracted TX SGL parts are released together with
 * the RX SGL release.
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/अगर_alg.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/null.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <net/sock.h>

काष्ठा aead_tfm अणु
	काष्ठा crypto_aead *aead;
	काष्ठा crypto_sync_skcipher *null_tfm;
पूर्ण;

अटल अंतरभूत bool aead_sufficient_data(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा sock *psk = ask->parent;
	काष्ठा alg_sock *pask = alg_sk(psk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा aead_tfm *aeadc = pask->निजी;
	काष्ठा crypto_aead *tfm = aeadc->aead;
	अचिन्हित पूर्णांक as = crypto_aead_authsize(tfm);

	/*
	 * The minimum amount of memory needed क्रम an AEAD cipher is
	 * the AAD and in हाल of decryption the tag.
	 */
	वापस ctx->used >= ctx->aead_assoclen + (ctx->enc ? 0 : as);
पूर्ण

अटल पूर्णांक aead_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा sock *psk = ask->parent;
	काष्ठा alg_sock *pask = alg_sk(psk);
	काष्ठा aead_tfm *aeadc = pask->निजी;
	काष्ठा crypto_aead *tfm = aeadc->aead;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(tfm);

	वापस af_alg_sendmsg(sock, msg, size, ivsize);
पूर्ण

अटल पूर्णांक crypto_aead_copy_sgl(काष्ठा crypto_sync_skcipher *null_tfm,
				काष्ठा scatterlist *src,
				काष्ठा scatterlist *dst, अचिन्हित पूर्णांक len)
अणु
	SYNC_SKCIPHER_REQUEST_ON_STACK(skreq, null_tfm);

	skcipher_request_set_sync_tfm(skreq, null_tfm);
	skcipher_request_set_callback(skreq, CRYPTO_TFM_REQ_MAY_SLEEP,
				      शून्य, शून्य);
	skcipher_request_set_crypt(skreq, src, dst, len, शून्य);

	वापस crypto_skcipher_encrypt(skreq);
पूर्ण

अटल पूर्णांक _aead_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			 माप_प्रकार ignored, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा sock *psk = ask->parent;
	काष्ठा alg_sock *pask = alg_sk(psk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा aead_tfm *aeadc = pask->निजी;
	काष्ठा crypto_aead *tfm = aeadc->aead;
	काष्ठा crypto_sync_skcipher *null_tfm = aeadc->null_tfm;
	अचिन्हित पूर्णांक i, as = crypto_aead_authsize(tfm);
	काष्ठा af_alg_async_req *areq;
	काष्ठा af_alg_tsgl *tsgl, *पंचांगp;
	काष्ठा scatterlist *rsgl_src, *tsgl_src = शून्य;
	पूर्णांक err = 0;
	माप_प्रकार used = 0;		/* [in]  TX bufs to be en/decrypted */
	माप_प्रकार outlen = 0;		/* [out] RX bufs produced by kernel */
	माप_प्रकार usedpages = 0;		/* [in]  RX bufs to be used from user */
	माप_प्रकार processed = 0;		/* [in]  TX bufs to be consumed */

	अगर (!ctx->init || ctx->more) अणु
		err = af_alg_रुको_क्रम_data(sk, flags, 0);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Data length provided by caller via sendmsg/sendpage that has not
	 * yet been processed.
	 */
	used = ctx->used;

	/*
	 * Make sure sufficient data is present -- note, the same check is
	 * also present in sendmsg/sendpage. The checks in sendpage/sendmsg
	 * shall provide an inक्रमmation to the data sender that something is
	 * wrong, but they are irrelevant to मुख्यtain the kernel पूर्णांकegrity.
	 * We need this check here too in हाल user space decides to not honor
	 * the error message in sendmsg/sendpage and still call recvmsg. This
	 * check here protects the kernel पूर्णांकegrity.
	 */
	अगर (!aead_sufficient_data(sk))
		वापस -EINVAL;

	/*
	 * Calculate the minimum output buffer size holding the result of the
	 * cipher operation. When encrypting data, the receiving buffer is
	 * larger by the tag length compared to the input buffer as the
	 * encryption operation generates the tag. For decryption, the input
	 * buffer provides the tag which is consumed resulting in only the
	 * plaपूर्णांकext without a buffer क्रम the tag वापसed to the caller.
	 */
	अगर (ctx->enc)
		outlen = used + as;
	अन्यथा
		outlen = used - as;

	/*
	 * The cipher operation input data is reduced by the associated data
	 * length as this data is processed separately later on.
	 */
	used -= ctx->aead_assoclen;

	/* Allocate cipher request क्रम current operation. */
	areq = af_alg_alloc_areq(sk, माप(काष्ठा af_alg_async_req) +
				     crypto_aead_reqsize(tfm));
	अगर (IS_ERR(areq))
		वापस PTR_ERR(areq);

	/* convert iovecs of output buffers पूर्णांकo RX SGL */
	err = af_alg_get_rsgl(sk, msg, flags, areq, outlen, &usedpages);
	अगर (err)
		जाओ मुक्त;

	/*
	 * Ensure output buffer is sufficiently large. If the caller provides
	 * less buffer space, only use the relative required input size. This
	 * allows AIO operation where the caller sent all data to be processed
	 * and the AIO operation perक्रमms the operation on the dअगरferent chunks
	 * of the input data.
	 */
	अगर (usedpages < outlen) अणु
		माप_प्रकार less = outlen - usedpages;

		अगर (used < less) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण
		used -= less;
		outlen -= less;
	पूर्ण

	processed = used + ctx->aead_assoclen;
	list_क्रम_each_entry_safe(tsgl, पंचांगp, &ctx->tsgl_list, list) अणु
		क्रम (i = 0; i < tsgl->cur; i++) अणु
			काष्ठा scatterlist *process_sg = tsgl->sg + i;

			अगर (!(process_sg->length) || !sg_page(process_sg))
				जारी;
			tsgl_src = process_sg;
			अवरोध;
		पूर्ण
		अगर (tsgl_src)
			अवरोध;
	पूर्ण
	अगर (processed && !tsgl_src) अणु
		err = -EFAULT;
		जाओ मुक्त;
	पूर्ण

	/*
	 * Copy of AAD from source to destination
	 *
	 * The AAD is copied to the destination buffer without change. Even
	 * when user space uses an in-place cipher operation, the kernel
	 * will copy the data as it करोes not see whether such in-place operation
	 * is initiated.
	 *
	 * To ensure efficiency, the following implementation ensure that the
	 * ciphers are invoked to perक्रमm a crypto operation in-place. This
	 * is achieved by memory management specअगरied as follows.
	 */

	/* Use the RX SGL as source (and destination) क्रम crypto op. */
	rsgl_src = areq->first_rsgl.sgl.sg;

	अगर (ctx->enc) अणु
		/*
		 * Encryption operation - The in-place cipher operation is
		 * achieved by the following operation:
		 *
		 * TX SGL: AAD || PT
		 *	    |	   |
		 *	    | copy |
		 *	    v	   v
		 * RX SGL: AAD || PT || Tag
		 */
		err = crypto_aead_copy_sgl(null_tfm, tsgl_src,
					   areq->first_rsgl.sgl.sg, processed);
		अगर (err)
			जाओ मुक्त;
		af_alg_pull_tsgl(sk, processed, शून्य, 0);
	पूर्ण अन्यथा अणु
		/*
		 * Decryption operation - To achieve an in-place cipher
		 * operation, the following  SGL काष्ठाure is used:
		 *
		 * TX SGL: AAD || CT || Tag
		 *	    |	   |	 ^
		 *	    | copy |	 | Create SGL link.
		 *	    v	   v	 |
		 * RX SGL: AAD || CT ----+
		 */

		 /* Copy AAD || CT to RX SGL buffer क्रम in-place operation. */
		err = crypto_aead_copy_sgl(null_tfm, tsgl_src,
					   areq->first_rsgl.sgl.sg, outlen);
		अगर (err)
			जाओ मुक्त;

		/* Create TX SGL क्रम tag and chain it to RX SGL. */
		areq->tsgl_entries = af_alg_count_tsgl(sk, processed,
						       processed - as);
		अगर (!areq->tsgl_entries)
			areq->tsgl_entries = 1;
		areq->tsgl = sock_kदो_स्मृति(sk, array_size(माप(*areq->tsgl),
							 areq->tsgl_entries),
					  GFP_KERNEL);
		अगर (!areq->tsgl) अणु
			err = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
		sg_init_table(areq->tsgl, areq->tsgl_entries);

		/* Release TX SGL, except क्रम tag data and reassign tag data. */
		af_alg_pull_tsgl(sk, processed, areq->tsgl, processed - as);

		/* chain the areq TX SGL holding the tag with RX SGL */
		अगर (usedpages) अणु
			/* RX SGL present */
			काष्ठा af_alg_sgl *sgl_prev = &areq->last_rsgl->sgl;

			sg_unmark_end(sgl_prev->sg + sgl_prev->npages - 1);
			sg_chain(sgl_prev->sg, sgl_prev->npages + 1,
				 areq->tsgl);
		पूर्ण अन्यथा
			/* no RX SGL present (e.g. authentication only) */
			rsgl_src = areq->tsgl;
	पूर्ण

	/* Initialize the crypto operation */
	aead_request_set_crypt(&areq->cra_u.aead_req, rsgl_src,
			       areq->first_rsgl.sgl.sg, used, ctx->iv);
	aead_request_set_ad(&areq->cra_u.aead_req, ctx->aead_assoclen);
	aead_request_set_tfm(&areq->cra_u.aead_req, tfm);

	अगर (msg->msg_iocb && !is_sync_kiocb(msg->msg_iocb)) अणु
		/* AIO operation */
		sock_hold(sk);
		areq->iocb = msg->msg_iocb;

		/* Remember output size that will be generated. */
		areq->outlen = outlen;

		aead_request_set_callback(&areq->cra_u.aead_req,
					  CRYPTO_TFM_REQ_MAY_SLEEP,
					  af_alg_async_cb, areq);
		err = ctx->enc ? crypto_aead_encrypt(&areq->cra_u.aead_req) :
				 crypto_aead_decrypt(&areq->cra_u.aead_req);

		/* AIO operation in progress */
		अगर (err == -EINPROGRESS)
			वापस -EIOCBQUEUED;

		sock_put(sk);
	पूर्ण अन्यथा अणु
		/* Synchronous operation */
		aead_request_set_callback(&areq->cra_u.aead_req,
					  CRYPTO_TFM_REQ_MAY_SLEEP |
					  CRYPTO_TFM_REQ_MAY_BACKLOG,
					  crypto_req_करोne, &ctx->रुको);
		err = crypto_रुको_req(ctx->enc ?
				crypto_aead_encrypt(&areq->cra_u.aead_req) :
				crypto_aead_decrypt(&areq->cra_u.aead_req),
				&ctx->रुको);
	पूर्ण


मुक्त:
	af_alg_मुक्त_resources(areq);

	वापस err ? err : outlen;
पूर्ण

अटल पूर्णांक aead_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			माप_प्रकार ignored, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक ret = 0;

	lock_sock(sk);
	जबतक (msg_data_left(msg)) अणु
		पूर्णांक err = _aead_recvmsg(sock, msg, ignored, flags);

		/*
		 * This error covers -EIOCBQUEUED which implies that we can
		 * only handle one AIO request. If the caller wants to have
		 * multiple AIO requests in parallel, he must make multiple
		 * separate AIO calls.
		 *
		 * Also वापस the error अगर no data has been processed so far.
		 */
		अगर (err <= 0) अणु
			अगर (err == -EIOCBQUEUED || err == -EBADMSG || !ret)
				ret = err;
			जाओ out;
		पूर्ण

		ret += err;
	पूर्ण

out:
	af_alg_wmem_wakeup(sk);
	release_sock(sk);
	वापस ret;
पूर्ण

अटल काष्ठा proto_ops algअगर_aead_ops = अणु
	.family		=	PF_ALG,

	.connect	=	sock_no_connect,
	.socketpair	=	sock_no_socketpair,
	.getname	=	sock_no_getname,
	.ioctl		=	sock_no_ioctl,
	.listen		=	sock_no_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,
	.accept		=	sock_no_accept,

	.release	=	af_alg_release,
	.sendmsg	=	aead_sendmsg,
	.sendpage	=	af_alg_sendpage,
	.recvmsg	=	aead_recvmsg,
	.poll		=	af_alg_poll,
पूर्ण;

अटल पूर्णांक aead_check_key(काष्ठा socket *sock)
अणु
	पूर्णांक err = 0;
	काष्ठा sock *psk;
	काष्ठा alg_sock *pask;
	काष्ठा aead_tfm *tfm;
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);

	lock_sock(sk);
	अगर (!atomic_पढ़ो(&ask->nokey_refcnt))
		जाओ unlock_child;

	psk = ask->parent;
	pask = alg_sk(ask->parent);
	tfm = pask->निजी;

	err = -ENOKEY;
	lock_sock_nested(psk, SINGLE_DEPTH_NESTING);
	अगर (crypto_aead_get_flags(tfm->aead) & CRYPTO_TFM_NEED_KEY)
		जाओ unlock;

	atomic_dec(&pask->nokey_refcnt);
	atomic_set(&ask->nokey_refcnt, 0);

	err = 0;

unlock:
	release_sock(psk);
unlock_child:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक aead_sendmsg_nokey(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  माप_प्रकार size)
अणु
	पूर्णांक err;

	err = aead_check_key(sock);
	अगर (err)
		वापस err;

	वापस aead_sendmsg(sock, msg, size);
पूर्ण

अटल sमाप_प्रकार aead_sendpage_nokey(काष्ठा socket *sock, काष्ठा page *page,
				       पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = aead_check_key(sock);
	अगर (err)
		वापस err;

	वापस af_alg_sendpage(sock, page, offset, size, flags);
पूर्ण

अटल पूर्णांक aead_recvmsg_nokey(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  माप_प्रकार ignored, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = aead_check_key(sock);
	अगर (err)
		वापस err;

	वापस aead_recvmsg(sock, msg, ignored, flags);
पूर्ण

अटल काष्ठा proto_ops algअगर_aead_ops_nokey = अणु
	.family		=	PF_ALG,

	.connect	=	sock_no_connect,
	.socketpair	=	sock_no_socketpair,
	.getname	=	sock_no_getname,
	.ioctl		=	sock_no_ioctl,
	.listen		=	sock_no_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,
	.accept		=	sock_no_accept,

	.release	=	af_alg_release,
	.sendmsg	=	aead_sendmsg_nokey,
	.sendpage	=	aead_sendpage_nokey,
	.recvmsg	=	aead_recvmsg_nokey,
	.poll		=	af_alg_poll,
पूर्ण;

अटल व्योम *aead_bind(स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	काष्ठा aead_tfm *tfm;
	काष्ठा crypto_aead *aead;
	काष्ठा crypto_sync_skcipher *null_tfm;

	tfm = kzalloc(माप(*tfm), GFP_KERNEL);
	अगर (!tfm)
		वापस ERR_PTR(-ENOMEM);

	aead = crypto_alloc_aead(name, type, mask);
	अगर (IS_ERR(aead)) अणु
		kमुक्त(tfm);
		वापस ERR_CAST(aead);
	पूर्ण

	null_tfm = crypto_get_शेष_null_skcipher();
	अगर (IS_ERR(null_tfm)) अणु
		crypto_मुक्त_aead(aead);
		kमुक्त(tfm);
		वापस ERR_CAST(null_tfm);
	पूर्ण

	tfm->aead = aead;
	tfm->null_tfm = null_tfm;

	वापस tfm;
पूर्ण

अटल व्योम aead_release(व्योम *निजी)
अणु
	काष्ठा aead_tfm *tfm = निजी;

	crypto_मुक्त_aead(tfm->aead);
	crypto_put_शेष_null_skcipher();
	kमुक्त(tfm);
पूर्ण

अटल पूर्णांक aead_setauthsize(व्योम *निजी, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा aead_tfm *tfm = निजी;

	वापस crypto_aead_setauthsize(tfm->aead, authsize);
पूर्ण

अटल पूर्णांक aead_setkey(व्योम *निजी, स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aead_tfm *tfm = निजी;

	वापस crypto_aead_setkey(tfm->aead, key, keylen);
पूर्ण

अटल व्योम aead_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा sock *psk = ask->parent;
	काष्ठा alg_sock *pask = alg_sk(psk);
	काष्ठा aead_tfm *aeadc = pask->निजी;
	काष्ठा crypto_aead *tfm = aeadc->aead;
	अचिन्हित पूर्णांक ivlen = crypto_aead_ivsize(tfm);

	af_alg_pull_tsgl(sk, ctx->used, शून्य, 0);
	sock_kzमुक्त_s(sk, ctx->iv, ivlen);
	sock_kमुक्त_s(sk, ctx, ctx->len);
	af_alg_release_parent(sk);
पूर्ण

अटल पूर्णांक aead_accept_parent_nokey(व्योम *निजी, काष्ठा sock *sk)
अणु
	काष्ठा af_alg_ctx *ctx;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा aead_tfm *tfm = निजी;
	काष्ठा crypto_aead *aead = tfm->aead;
	अचिन्हित पूर्णांक len = माप(*ctx);
	अचिन्हित पूर्णांक ivlen = crypto_aead_ivsize(aead);

	ctx = sock_kदो_स्मृति(sk, len, GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	स_रखो(ctx, 0, len);

	ctx->iv = sock_kदो_स्मृति(sk, ivlen, GFP_KERNEL);
	अगर (!ctx->iv) अणु
		sock_kमुक्त_s(sk, ctx, len);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(ctx->iv, 0, ivlen);

	INIT_LIST_HEAD(&ctx->tsgl_list);
	ctx->len = len;
	crypto_init_रुको(&ctx->रुको);

	ask->निजी = ctx;

	sk->sk_deकाष्ठा = aead_sock_deकाष्ठा;

	वापस 0;
पूर्ण

अटल पूर्णांक aead_accept_parent(व्योम *निजी, काष्ठा sock *sk)
अणु
	काष्ठा aead_tfm *tfm = निजी;

	अगर (crypto_aead_get_flags(tfm->aead) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	वापस aead_accept_parent_nokey(निजी, sk);
पूर्ण

अटल स्थिर काष्ठा af_alg_type algअगर_type_aead = अणु
	.bind		=	aead_bind,
	.release	=	aead_release,
	.setkey		=	aead_setkey,
	.setauthsize	=	aead_setauthsize,
	.accept		=	aead_accept_parent,
	.accept_nokey	=	aead_accept_parent_nokey,
	.ops		=	&algअगर_aead_ops,
	.ops_nokey	=	&algअगर_aead_ops_nokey,
	.name		=	"aead",
	.owner		=	THIS_MODULE
पूर्ण;

अटल पूर्णांक __init algअगर_aead_init(व्योम)
अणु
	वापस af_alg_रेजिस्टर_type(&algअगर_type_aead);
पूर्ण

अटल व्योम __निकास algअगर_aead_निकास(व्योम)
अणु
	पूर्णांक err = af_alg_unरेजिस्टर_type(&algअगर_type_aead);
	BUG_ON(err);
पूर्ण

module_init(algअगर_aead_init);
module_निकास(algअगर_aead_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephan Mueller <smueller@chronox.de>");
MODULE_DESCRIPTION("AEAD kernel crypto API user space interface");
