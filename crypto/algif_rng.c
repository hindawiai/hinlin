<शैली गुरु>
/*
 * algअगर_rng: User-space पूर्णांकerface क्रम अक्रमom number generators
 *
 * This file provides the user-space API क्रम अक्रमom number generators.
 *
 * Copyright (C) 2014, Stephan Mueller <smueller@chronox.de>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote
 *    products derived from this software without specअगरic prior
 *    written permission.
 *
 * ALTERNATIVELY, this product may be distributed under the terms of
 * the GNU General Public License, in which हाल the provisions of the GPL2
 * are required INSTEAD OF the above restrictions.  (This clause is
 * necessary due to a potential bad पूर्णांकeraction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <crypto/rng.h>
#समावेश <linux/अक्रमom.h>
#समावेश <crypto/अगर_alg.h>
#समावेश <linux/net.h>
#समावेश <net/sock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephan Mueller <smueller@chronox.de>");
MODULE_DESCRIPTION("User-space interface for random number generators");

काष्ठा rng_ctx अणु
#घोषणा MAXSIZE 128
	अचिन्हित पूर्णांक len;
	काष्ठा crypto_rng *drng;
	u8 *addtl;
	माप_प्रकार addtl_len;
पूर्ण;

काष्ठा rng_parent_ctx अणु
	काष्ठा crypto_rng *drng;
	u8 *entropy;
पूर्ण;

अटल व्योम rng_reset_addtl(काष्ठा rng_ctx *ctx)
अणु
	kमुक्त_sensitive(ctx->addtl);
	ctx->addtl = शून्य;
	ctx->addtl_len = 0;
पूर्ण

अटल पूर्णांक _rng_recvmsg(काष्ठा crypto_rng *drng, काष्ठा msghdr *msg, माप_प्रकार len,
			u8 *addtl, माप_प्रकार addtl_len)
अणु
	पूर्णांक err = 0;
	पूर्णांक genlen = 0;
	u8 result[MAXSIZE];

	अगर (len == 0)
		वापस 0;
	अगर (len > MAXSIZE)
		len = MAXSIZE;

	/*
	 * although not strictly needed, this is a precaution against coding
	 * errors
	 */
	स_रखो(result, 0, len);

	/*
	 * The enक्रमcement of a proper seeding of an RNG is करोne within an
	 * RNG implementation. Some RNGs (DRBG, krng) करो not need specअगरic
	 * seeding as they स्वतःmatically seed. The X9.31 DRNG will वापस
	 * an error अगर it was not seeded properly.
	 */
	genlen = crypto_rng_generate(drng, addtl, addtl_len, result, len);
	अगर (genlen < 0)
		वापस genlen;

	err = स_नकल_to_msg(msg, result, len);
	memzero_explicit(result, len);

	वापस err ? err : len;
पूर्ण

अटल पूर्णांक rng_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		       पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा rng_ctx *ctx = ask->निजी;

	वापस _rng_recvmsg(ctx->drng, msg, len, शून्य, 0);
पूर्ण

अटल पूर्णांक rng_test_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
			    पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा rng_ctx *ctx = ask->निजी;
	पूर्णांक ret;

	lock_sock(sock->sk);
	ret = _rng_recvmsg(ctx->drng, msg, len, ctx->addtl, ctx->addtl_len);
	rng_reset_addtl(ctx);
	release_sock(sock->sk);

	वापस ret;
पूर्ण

अटल पूर्णांक rng_test_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	पूर्णांक err;
	काष्ठा alg_sock *ask = alg_sk(sock->sk);
	काष्ठा rng_ctx *ctx = ask->निजी;

	lock_sock(sock->sk);
	अगर (len > MAXSIZE) अणु
		err = -EMSGSIZE;
		जाओ unlock;
	पूर्ण

	rng_reset_addtl(ctx);
	ctx->addtl = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!ctx->addtl) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	err = स_नकल_from_msg(ctx->addtl, msg, len);
	अगर (err) अणु
		rng_reset_addtl(ctx);
		जाओ unlock;
	पूर्ण
	ctx->addtl_len = len;

unlock:
	release_sock(sock->sk);
	वापस err ? err : len;
पूर्ण

अटल काष्ठा proto_ops algअगर_rng_ops = अणु
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
	.sendmsg	=	sock_no_sendmsg,
	.sendpage	=	sock_no_sendpage,

	.release	=	af_alg_release,
	.recvmsg	=	rng_recvmsg,
पूर्ण;

अटल काष्ठा proto_ops __maybe_unused algअगर_rng_test_ops = अणु
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
	.sendpage	=	sock_no_sendpage,

	.release	=	af_alg_release,
	.recvmsg	=	rng_test_recvmsg,
	.sendmsg	=	rng_test_sendmsg,
पूर्ण;

अटल व्योम *rng_bind(स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	काष्ठा rng_parent_ctx *pctx;
	काष्ठा crypto_rng *rng;

	pctx = kzalloc(माप(*pctx), GFP_KERNEL);
	अगर (!pctx)
		वापस ERR_PTR(-ENOMEM);

	rng = crypto_alloc_rng(name, type, mask);
	अगर (IS_ERR(rng)) अणु
		kमुक्त(pctx);
		वापस ERR_CAST(rng);
	पूर्ण

	pctx->drng = rng;
	वापस pctx;
पूर्ण

अटल व्योम rng_release(व्योम *निजी)
अणु
	काष्ठा rng_parent_ctx *pctx = निजी;

	अगर (unlikely(!pctx))
		वापस;
	crypto_मुक्त_rng(pctx->drng);
	kमुक्त_sensitive(pctx->entropy);
	kमुक्त_sensitive(pctx);
पूर्ण

अटल व्योम rng_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा rng_ctx *ctx = ask->निजी;

	rng_reset_addtl(ctx);
	sock_kमुक्त_s(sk, ctx, ctx->len);
	af_alg_release_parent(sk);
पूर्ण

अटल पूर्णांक rng_accept_parent(व्योम *निजी, काष्ठा sock *sk)
अणु
	काष्ठा rng_ctx *ctx;
	काष्ठा rng_parent_ctx *pctx = निजी;
	काष्ठा alg_sock *ask = alg_sk(sk);
	अचिन्हित पूर्णांक len = माप(*ctx);

	ctx = sock_kदो_स्मृति(sk, len, GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->len = len;
	ctx->addtl = शून्य;
	ctx->addtl_len = 0;

	/*
	 * No seeding करोne at that poपूर्णांक -- अगर multiple accepts are
	 * करोne on one RNG instance, each resulting FD poपूर्णांकs to the same
	 * state of the RNG.
	 */

	ctx->drng = pctx->drng;
	ask->निजी = ctx;
	sk->sk_deकाष्ठा = rng_sock_deकाष्ठा;

	/*
	 * Non शून्य pctx->entropy means that CAVP test has been initiated on
	 * this socket, replace proto_ops algअगर_rng_ops with algअगर_rng_test_ops.
	 */
	अगर (IS_ENABLED(CONFIG_CRYPTO_USER_API_RNG_CAVP) && pctx->entropy)
		sk->sk_socket->ops = &algअगर_rng_test_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक rng_setkey(व्योम *निजी, स्थिर u8 *seed, अचिन्हित पूर्णांक seedlen)
अणु
	काष्ठा rng_parent_ctx *pctx = निजी;
	/*
	 * Check whether seedlen is of sufficient size is करोne in RNG
	 * implementations.
	 */
	वापस crypto_rng_reset(pctx->drng, seed, seedlen);
पूर्ण

अटल पूर्णांक __maybe_unused rng_setentropy(व्योम *निजी, sockptr_t entropy,
					 अचिन्हित पूर्णांक len)
अणु
	काष्ठा rng_parent_ctx *pctx = निजी;
	u8 *kentropy = शून्य;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (pctx->entropy)
		वापस -EINVAL;

	अगर (len > MAXSIZE)
		वापस -EMSGSIZE;

	अगर (len) अणु
		kentropy = memdup_sockptr(entropy, len);
		अगर (IS_ERR(kentropy))
			वापस PTR_ERR(kentropy);
	पूर्ण

	crypto_rng_alg(pctx->drng)->set_ent(pctx->drng, kentropy, len);
	/*
	 * Since rng करोesn't perक्रमm any memory management क्रम the entropy
	 * buffer, save kentropy poपूर्णांकer to pctx now to मुक्त it after use.
	 */
	pctx->entropy = kentropy;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा af_alg_type algअगर_type_rng = अणु
	.bind		=	rng_bind,
	.release	=	rng_release,
	.accept		=	rng_accept_parent,
	.setkey		=	rng_setkey,
#अगर_घोषित CONFIG_CRYPTO_USER_API_RNG_CAVP
	.setentropy	=	rng_setentropy,
#पूर्ण_अगर
	.ops		=	&algअगर_rng_ops,
	.name		=	"rng",
	.owner		=	THIS_MODULE
पूर्ण;

अटल पूर्णांक __init rng_init(व्योम)
अणु
	वापस af_alg_रेजिस्टर_type(&algअगर_type_rng);
पूर्ण

अटल व्योम __निकास rng_निकास(व्योम)
अणु
	पूर्णांक err = af_alg_unरेजिस्टर_type(&algअगर_type_rng);
	BUG_ON(err);
पूर्ण

module_init(rng_init);
module_निकास(rng_निकास);
