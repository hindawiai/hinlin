<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * algअगर_hash: User-space पूर्णांकerface क्रम hash algorithms
 *
 * This file provides the user-space API क्रम hash algorithms.
 *
 * Copyright (c) 2010 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/hash.h>
#समावेश <crypto/अगर_alg.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <net/sock.h>

काष्ठा hash_ctx अणु
	काष्ठा af_alg_sgl sgl;

	u8 *result;

	काष्ठा crypto_रुको रुको;

	अचिन्हित पूर्णांक len;
	bool more;

	काष्ठा ahash_request req;
पूर्ण;

अटल पूर्णांक hash_alloc_result(काष्ठा sock *sk, काष्ठा hash_ctx *ctx)
अणु
	अचिन्हित ds;

	अगर (ctx->result)
		वापस 0;

	ds = crypto_ahash_digestsize(crypto_ahash_reqtfm(&ctx->req));

	ctx->result = sock_kदो_स्मृति(sk, ds, GFP_KERNEL);
	अगर (!ctx->result)
		वापस -ENOMEM;

	स_रखो(ctx->result, 0, ds);

	वापस 0;
पूर्ण

अटल व्योम hash_मुक्त_result(काष्ठा sock *sk, काष्ठा hash_ctx *ctx)
अणु
	अचिन्हित ds;

	अगर (!ctx->result)
		वापस;

	ds = crypto_ahash_digestsize(crypto_ahash_reqtfm(&ctx->req));

	sock_kzमुक्त_s(sk, ctx->result, ds);
	ctx->result = शून्य;
पूर्ण

अटल पूर्णांक hash_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			माप_प्रकार ignored)
अणु
	पूर्णांक limit = ALG_MAX_PAGES * PAGE_SIZE;
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा hash_ctx *ctx = ask->निजी;
	दीर्घ copied = 0;
	पूर्णांक err;

	अगर (limit > sk->sk_sndbuf)
		limit = sk->sk_sndbuf;

	lock_sock(sk);
	अगर (!ctx->more) अणु
		अगर ((msg->msg_flags & MSG_MORE))
			hash_मुक्त_result(sk, ctx);

		err = crypto_रुको_req(crypto_ahash_init(&ctx->req), &ctx->रुको);
		अगर (err)
			जाओ unlock;
	पूर्ण

	ctx->more = false;

	जबतक (msg_data_left(msg)) अणु
		पूर्णांक len = msg_data_left(msg);

		अगर (len > limit)
			len = limit;

		len = af_alg_make_sg(&ctx->sgl, &msg->msg_iter, len);
		अगर (len < 0) अणु
			err = copied ? 0 : len;
			जाओ unlock;
		पूर्ण

		ahash_request_set_crypt(&ctx->req, ctx->sgl.sg, शून्य, len);

		err = crypto_रुको_req(crypto_ahash_update(&ctx->req),
				      &ctx->रुको);
		af_alg_मुक्त_sg(&ctx->sgl);
		अगर (err)
			जाओ unlock;

		copied += len;
		iov_iter_advance(&msg->msg_iter, len);
	पूर्ण

	err = 0;

	ctx->more = msg->msg_flags & MSG_MORE;
	अगर (!ctx->more) अणु
		err = hash_alloc_result(sk, ctx);
		अगर (err)
			जाओ unlock;

		ahash_request_set_crypt(&ctx->req, शून्य, ctx->result, 0);
		err = crypto_रुको_req(crypto_ahash_final(&ctx->req),
				      &ctx->रुको);
	पूर्ण

unlock:
	release_sock(sk);

	वापस err ?: copied;
पूर्ण

अटल sमाप_प्रकार hash_sendpage(काष्ठा socket *sock, काष्ठा page *page,
			     पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा hash_ctx *ctx = ask->निजी;
	पूर्णांक err;

	अगर (flags & MSG_SENDPAGE_NOTLAST)
		flags |= MSG_MORE;

	lock_sock(sk);
	sg_init_table(ctx->sgl.sg, 1);
	sg_set_page(ctx->sgl.sg, page, size, offset);

	अगर (!(flags & MSG_MORE)) अणु
		err = hash_alloc_result(sk, ctx);
		अगर (err)
			जाओ unlock;
	पूर्ण अन्यथा अगर (!ctx->more)
		hash_मुक्त_result(sk, ctx);

	ahash_request_set_crypt(&ctx->req, ctx->sgl.sg, ctx->result, size);

	अगर (!(flags & MSG_MORE)) अणु
		अगर (ctx->more)
			err = crypto_ahash_finup(&ctx->req);
		अन्यथा
			err = crypto_ahash_digest(&ctx->req);
	पूर्ण अन्यथा अणु
		अगर (!ctx->more) अणु
			err = crypto_ahash_init(&ctx->req);
			err = crypto_रुको_req(err, &ctx->रुको);
			अगर (err)
				जाओ unlock;
		पूर्ण

		err = crypto_ahash_update(&ctx->req);
	पूर्ण

	err = crypto_रुको_req(err, &ctx->रुको);
	अगर (err)
		जाओ unlock;

	ctx->more = flags & MSG_MORE;

unlock:
	release_sock(sk);

	वापस err ?: size;
पूर्ण

अटल पूर्णांक hash_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
			पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा hash_ctx *ctx = ask->निजी;
	अचिन्हित ds = crypto_ahash_digestsize(crypto_ahash_reqtfm(&ctx->req));
	bool result;
	पूर्णांक err;

	अगर (len > ds)
		len = ds;
	अन्यथा अगर (len < ds)
		msg->msg_flags |= MSG_TRUNC;

	lock_sock(sk);
	result = ctx->result;
	err = hash_alloc_result(sk, ctx);
	अगर (err)
		जाओ unlock;

	ahash_request_set_crypt(&ctx->req, शून्य, ctx->result, 0);

	अगर (!result && !ctx->more) अणु
		err = crypto_रुको_req(crypto_ahash_init(&ctx->req),
				      &ctx->रुको);
		अगर (err)
			जाओ unlock;
	पूर्ण

	अगर (!result || ctx->more) अणु
		ctx->more = false;
		err = crypto_रुको_req(crypto_ahash_final(&ctx->req),
				      &ctx->रुको);
		अगर (err)
			जाओ unlock;
	पूर्ण

	err = स_नकल_to_msg(msg, ctx->result, len);

unlock:
	hash_मुक्त_result(sk, ctx);
	release_sock(sk);

	वापस err ?: len;
पूर्ण

अटल पूर्णांक hash_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		       bool kern)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा hash_ctx *ctx = ask->निजी;
	काष्ठा ahash_request *req = &ctx->req;
	अक्षर state[HASH_MAX_STATESIZE];
	काष्ठा sock *sk2;
	काष्ठा alg_sock *ask2;
	काष्ठा hash_ctx *ctx2;
	bool more;
	पूर्णांक err;

	lock_sock(sk);
	more = ctx->more;
	err = more ? crypto_ahash_export(req, state) : 0;
	release_sock(sk);

	अगर (err)
		वापस err;

	err = af_alg_accept(ask->parent, newsock, kern);
	अगर (err)
		वापस err;

	sk2 = newsock->sk;
	ask2 = alg_sk(sk2);
	ctx2 = ask2->निजी;
	ctx2->more = more;

	अगर (!more)
		वापस err;

	err = crypto_ahash_import(&ctx2->req, state);
	अगर (err) अणु
		sock_orphan(sk2);
		sock_put(sk2);
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा proto_ops algअगर_hash_ops = अणु
	.family		=	PF_ALG,

	.connect	=	sock_no_connect,
	.socketpair	=	sock_no_socketpair,
	.getname	=	sock_no_getname,
	.ioctl		=	sock_no_ioctl,
	.listen		=	sock_no_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,

	.release	=	af_alg_release,
	.sendmsg	=	hash_sendmsg,
	.sendpage	=	hash_sendpage,
	.recvmsg	=	hash_recvmsg,
	.accept		=	hash_accept,
पूर्ण;

अटल पूर्णांक hash_check_key(काष्ठा socket *sock)
अणु
	पूर्णांक err = 0;
	काष्ठा sock *psk;
	काष्ठा alg_sock *pask;
	काष्ठा crypto_ahash *tfm;
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
	अगर (crypto_ahash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
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

अटल पूर्णांक hash_sendmsg_nokey(काष्ठा socket *sock, काष्ठा msghdr *msg,
			      माप_प्रकार size)
अणु
	पूर्णांक err;

	err = hash_check_key(sock);
	अगर (err)
		वापस err;

	वापस hash_sendmsg(sock, msg, size);
पूर्ण

अटल sमाप_प्रकार hash_sendpage_nokey(काष्ठा socket *sock, काष्ठा page *page,
				   पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = hash_check_key(sock);
	अगर (err)
		वापस err;

	वापस hash_sendpage(sock, page, offset, size, flags);
पूर्ण

अटल पूर्णांक hash_recvmsg_nokey(काष्ठा socket *sock, काष्ठा msghdr *msg,
			      माप_प्रकार ignored, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = hash_check_key(sock);
	अगर (err)
		वापस err;

	वापस hash_recvmsg(sock, msg, ignored, flags);
पूर्ण

अटल पूर्णांक hash_accept_nokey(काष्ठा socket *sock, काष्ठा socket *newsock,
			     पूर्णांक flags, bool kern)
अणु
	पूर्णांक err;

	err = hash_check_key(sock);
	अगर (err)
		वापस err;

	वापस hash_accept(sock, newsock, flags, kern);
पूर्ण

अटल काष्ठा proto_ops algअगर_hash_ops_nokey = अणु
	.family		=	PF_ALG,

	.connect	=	sock_no_connect,
	.socketpair	=	sock_no_socketpair,
	.getname	=	sock_no_getname,
	.ioctl		=	sock_no_ioctl,
	.listen		=	sock_no_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,

	.release	=	af_alg_release,
	.sendmsg	=	hash_sendmsg_nokey,
	.sendpage	=	hash_sendpage_nokey,
	.recvmsg	=	hash_recvmsg_nokey,
	.accept		=	hash_accept_nokey,
पूर्ण;

अटल व्योम *hash_bind(स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	वापस crypto_alloc_ahash(name, type, mask);
पूर्ण

अटल व्योम hash_release(व्योम *निजी)
अणु
	crypto_मुक्त_ahash(निजी);
पूर्ण

अटल पूर्णांक hash_setkey(व्योम *निजी, स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस crypto_ahash_setkey(निजी, key, keylen);
पूर्ण

अटल व्योम hash_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा hash_ctx *ctx = ask->निजी;

	hash_मुक्त_result(sk, ctx);
	sock_kमुक्त_s(sk, ctx, ctx->len);
	af_alg_release_parent(sk);
पूर्ण

अटल पूर्णांक hash_accept_parent_nokey(व्योम *निजी, काष्ठा sock *sk)
अणु
	काष्ठा crypto_ahash *tfm = निजी;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा hash_ctx *ctx;
	अचिन्हित पूर्णांक len = माप(*ctx) + crypto_ahash_reqsize(tfm);

	ctx = sock_kदो_स्मृति(sk, len, GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->result = शून्य;
	ctx->len = len;
	ctx->more = false;
	crypto_init_रुको(&ctx->रुको);

	ask->निजी = ctx;

	ahash_request_set_tfm(&ctx->req, tfm);
	ahash_request_set_callback(&ctx->req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &ctx->रुको);

	sk->sk_deकाष्ठा = hash_sock_deकाष्ठा;

	वापस 0;
पूर्ण

अटल पूर्णांक hash_accept_parent(व्योम *निजी, काष्ठा sock *sk)
अणु
	काष्ठा crypto_ahash *tfm = निजी;

	अगर (crypto_ahash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	वापस hash_accept_parent_nokey(निजी, sk);
पूर्ण

अटल स्थिर काष्ठा af_alg_type algअगर_type_hash = अणु
	.bind		=	hash_bind,
	.release	=	hash_release,
	.setkey		=	hash_setkey,
	.accept		=	hash_accept_parent,
	.accept_nokey	=	hash_accept_parent_nokey,
	.ops		=	&algअगर_hash_ops,
	.ops_nokey	=	&algअगर_hash_ops_nokey,
	.name		=	"hash",
	.owner		=	THIS_MODULE
पूर्ण;

अटल पूर्णांक __init algअगर_hash_init(व्योम)
अणु
	वापस af_alg_रेजिस्टर_type(&algअगर_type_hash);
पूर्ण

अटल व्योम __निकास algअगर_hash_निकास(व्योम)
अणु
	पूर्णांक err = af_alg_unरेजिस्टर_type(&algअगर_type_hash);
	BUG_ON(err);
पूर्ण

module_init(algअगर_hash_init);
module_निकास(algअगर_hash_निकास);
MODULE_LICENSE("GPL");
