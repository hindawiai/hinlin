<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * algअगर_skcipher: User-space पूर्णांकerface क्रम skcipher algorithms
 *
 * This file provides the user-space API क्रम symmetric key ciphers.
 *
 * Copyright (c) 2010 Herbert Xu <herbert@gonकरोr.apana.org.au>
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

#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/अगर_alg.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <net/sock.h>

अटल पूर्णांक skcipher_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा sock *psk = ask->parent;
	काष्ठा alg_sock *pask = alg_sk(psk);
	काष्ठा crypto_skcipher *tfm = pask->निजी;
	अचिन्हित ivsize = crypto_skcipher_ivsize(tfm);

	वापस af_alg_sendmsg(sock, msg, size, ivsize);
पूर्ण

अटल पूर्णांक _skcipher_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			     माप_प्रकार ignored, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा sock *psk = ask->parent;
	काष्ठा alg_sock *pask = alg_sk(psk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा crypto_skcipher *tfm = pask->निजी;
	अचिन्हित पूर्णांक bs = crypto_skcipher_chunksize(tfm);
	काष्ठा af_alg_async_req *areq;
	पूर्णांक err = 0;
	माप_प्रकार len = 0;

	अगर (!ctx->init || (ctx->more && ctx->used < bs)) अणु
		err = af_alg_रुको_क्रम_data(sk, flags, bs);
		अगर (err)
			वापस err;
	पूर्ण

	/* Allocate cipher request क्रम current operation. */
	areq = af_alg_alloc_areq(sk, माप(काष्ठा af_alg_async_req) +
				     crypto_skcipher_reqsize(tfm));
	अगर (IS_ERR(areq))
		वापस PTR_ERR(areq);

	/* convert iovecs of output buffers पूर्णांकo RX SGL */
	err = af_alg_get_rsgl(sk, msg, flags, areq, ctx->used, &len);
	अगर (err)
		जाओ मुक्त;

	/*
	 * If more buffers are to be expected to be processed, process only
	 * full block size buffers.
	 */
	अगर (ctx->more || len < ctx->used)
		len -= len % bs;

	/*
	 * Create a per request TX SGL क्रम this request which tracks the
	 * SG entries from the global TX SGL.
	 */
	areq->tsgl_entries = af_alg_count_tsgl(sk, len, 0);
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
	af_alg_pull_tsgl(sk, len, areq->tsgl, 0);

	/* Initialize the crypto operation */
	skcipher_request_set_tfm(&areq->cra_u.skcipher_req, tfm);
	skcipher_request_set_crypt(&areq->cra_u.skcipher_req, areq->tsgl,
				   areq->first_rsgl.sgl.sg, len, ctx->iv);

	अगर (msg->msg_iocb && !is_sync_kiocb(msg->msg_iocb)) अणु
		/* AIO operation */
		sock_hold(sk);
		areq->iocb = msg->msg_iocb;

		/* Remember output size that will be generated. */
		areq->outlen = len;

		skcipher_request_set_callback(&areq->cra_u.skcipher_req,
					      CRYPTO_TFM_REQ_MAY_SLEEP,
					      af_alg_async_cb, areq);
		err = ctx->enc ?
			crypto_skcipher_encrypt(&areq->cra_u.skcipher_req) :
			crypto_skcipher_decrypt(&areq->cra_u.skcipher_req);

		/* AIO operation in progress */
		अगर (err == -EINPROGRESS)
			वापस -EIOCBQUEUED;

		sock_put(sk);
	पूर्ण अन्यथा अणु
		/* Synchronous operation */
		skcipher_request_set_callback(&areq->cra_u.skcipher_req,
					      CRYPTO_TFM_REQ_MAY_SLEEP |
					      CRYPTO_TFM_REQ_MAY_BACKLOG,
					      crypto_req_करोne, &ctx->रुको);
		err = crypto_रुको_req(ctx->enc ?
			crypto_skcipher_encrypt(&areq->cra_u.skcipher_req) :
			crypto_skcipher_decrypt(&areq->cra_u.skcipher_req),
						 &ctx->रुको);
	पूर्ण


मुक्त:
	af_alg_मुक्त_resources(areq);

	वापस err ? err : len;
पूर्ण

अटल पूर्णांक skcipher_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार ignored, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक ret = 0;

	lock_sock(sk);
	जबतक (msg_data_left(msg)) अणु
		पूर्णांक err = _skcipher_recvmsg(sock, msg, ignored, flags);

		/*
		 * This error covers -EIOCBQUEUED which implies that we can
		 * only handle one AIO request. If the caller wants to have
		 * multiple AIO requests in parallel, he must make multiple
		 * separate AIO calls.
		 *
		 * Also वापस the error अगर no data has been processed so far.
		 */
		अगर (err <= 0) अणु
			अगर (err == -EIOCBQUEUED || !ret)
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

अटल काष्ठा proto_ops algअगर_skcipher_ops = अणु
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
	.sendmsg	=	skcipher_sendmsg,
	.sendpage	=	af_alg_sendpage,
	.recvmsg	=	skcipher_recvmsg,
	.poll		=	af_alg_poll,
पूर्ण;

अटल पूर्णांक skcipher_check_key(काष्ठा socket *sock)
अणु
	पूर्णांक err = 0;
	काष्ठा sock *psk;
	काष्ठा alg_sock *pask;
	काष्ठा crypto_skcipher *tfm;
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
	अगर (crypto_skcipher_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
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

अटल पूर्णांक skcipher_sendmsg_nokey(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  माप_प्रकार size)
अणु
	पूर्णांक err;

	err = skcipher_check_key(sock);
	अगर (err)
		वापस err;

	वापस skcipher_sendmsg(sock, msg, size);
पूर्ण

अटल sमाप_प्रकार skcipher_sendpage_nokey(काष्ठा socket *sock, काष्ठा page *page,
				       पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = skcipher_check_key(sock);
	अगर (err)
		वापस err;

	वापस af_alg_sendpage(sock, page, offset, size, flags);
पूर्ण

अटल पूर्णांक skcipher_recvmsg_nokey(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  माप_प्रकार ignored, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = skcipher_check_key(sock);
	अगर (err)
		वापस err;

	वापस skcipher_recvmsg(sock, msg, ignored, flags);
पूर्ण

अटल काष्ठा proto_ops algअगर_skcipher_ops_nokey = अणु
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
	.sendmsg	=	skcipher_sendmsg_nokey,
	.sendpage	=	skcipher_sendpage_nokey,
	.recvmsg	=	skcipher_recvmsg_nokey,
	.poll		=	af_alg_poll,
पूर्ण;

अटल व्योम *skcipher_bind(स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	वापस crypto_alloc_skcipher(name, type, mask);
पूर्ण

अटल व्योम skcipher_release(व्योम *निजी)
अणु
	crypto_मुक्त_skcipher(निजी);
पूर्ण

अटल पूर्णांक skcipher_setkey(व्योम *निजी, स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस crypto_skcipher_setkey(निजी, key, keylen);
पूर्ण

अटल व्योम skcipher_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा sock *psk = ask->parent;
	काष्ठा alg_sock *pask = alg_sk(psk);
	काष्ठा crypto_skcipher *tfm = pask->निजी;

	af_alg_pull_tsgl(sk, ctx->used, शून्य, 0);
	sock_kzमुक्त_s(sk, ctx->iv, crypto_skcipher_ivsize(tfm));
	sock_kमुक्त_s(sk, ctx, ctx->len);
	af_alg_release_parent(sk);
पूर्ण

अटल पूर्णांक skcipher_accept_parent_nokey(व्योम *निजी, काष्ठा sock *sk)
अणु
	काष्ठा af_alg_ctx *ctx;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा crypto_skcipher *tfm = निजी;
	अचिन्हित पूर्णांक len = माप(*ctx);

	ctx = sock_kदो_स्मृति(sk, len, GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	स_रखो(ctx, 0, len);

	ctx->iv = sock_kदो_स्मृति(sk, crypto_skcipher_ivsize(tfm),
			       GFP_KERNEL);
	अगर (!ctx->iv) अणु
		sock_kमुक्त_s(sk, ctx, len);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(ctx->iv, 0, crypto_skcipher_ivsize(tfm));

	INIT_LIST_HEAD(&ctx->tsgl_list);
	ctx->len = len;
	crypto_init_रुको(&ctx->रुको);

	ask->निजी = ctx;

	sk->sk_deकाष्ठा = skcipher_sock_deकाष्ठा;

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_accept_parent(व्योम *निजी, काष्ठा sock *sk)
अणु
	काष्ठा crypto_skcipher *tfm = निजी;

	अगर (crypto_skcipher_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	वापस skcipher_accept_parent_nokey(निजी, sk);
पूर्ण

अटल स्थिर काष्ठा af_alg_type algअगर_type_skcipher = अणु
	.bind		=	skcipher_bind,
	.release	=	skcipher_release,
	.setkey		=	skcipher_setkey,
	.accept		=	skcipher_accept_parent,
	.accept_nokey	=	skcipher_accept_parent_nokey,
	.ops		=	&algअगर_skcipher_ops,
	.ops_nokey	=	&algअगर_skcipher_ops_nokey,
	.name		=	"skcipher",
	.owner		=	THIS_MODULE
पूर्ण;

अटल पूर्णांक __init algअगर_skcipher_init(व्योम)
अणु
	वापस af_alg_रेजिस्टर_type(&algअगर_type_skcipher);
पूर्ण

अटल व्योम __निकास algअगर_skcipher_निकास(व्योम)
अणु
	पूर्णांक err = af_alg_unरेजिस्टर_type(&algअगर_type_skcipher);
	BUG_ON(err);
पूर्ण

module_init(algअगर_skcipher_init);
module_निकास(algअगर_skcipher_निकास);
MODULE_LICENSE("GPL");
