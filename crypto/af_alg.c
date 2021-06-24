<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * af_alg: User-space algorithm पूर्णांकerface
 *
 * This file provides the user-space API क्रम algorithms.
 *
 * Copyright (c) 2010 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/atomic.h>
#समावेश <crypto/अगर_alg.h>
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/security.h>

काष्ठा alg_type_list अणु
	स्थिर काष्ठा af_alg_type *type;
	काष्ठा list_head list;
पूर्ण;

अटल atomic_दीर्घ_t alg_memory_allocated;

अटल काष्ठा proto alg_proto = अणु
	.name			= "ALG",
	.owner			= THIS_MODULE,
	.memory_allocated	= &alg_memory_allocated,
	.obj_size		= माप(काष्ठा alg_sock),
पूर्ण;

अटल LIST_HEAD(alg_types);
अटल DECLARE_RWSEM(alg_types_sem);

अटल स्थिर काष्ठा af_alg_type *alg_get_type(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा af_alg_type *type = ERR_PTR(-ENOENT);
	काष्ठा alg_type_list *node;

	करोwn_पढ़ो(&alg_types_sem);
	list_क्रम_each_entry(node, &alg_types, list) अणु
		अगर (म_भेद(node->type->name, name))
			जारी;

		अगर (try_module_get(node->type->owner))
			type = node->type;
		अवरोध;
	पूर्ण
	up_पढ़ो(&alg_types_sem);

	वापस type;
पूर्ण

पूर्णांक af_alg_रेजिस्टर_type(स्थिर काष्ठा af_alg_type *type)
अणु
	काष्ठा alg_type_list *node;
	पूर्णांक err = -EEXIST;

	करोwn_ग_लिखो(&alg_types_sem);
	list_क्रम_each_entry(node, &alg_types, list) अणु
		अगर (!म_भेद(node->type->name, type->name))
			जाओ unlock;
	पूर्ण

	node = kदो_स्मृति(माप(*node), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!node)
		जाओ unlock;

	type->ops->owner = THIS_MODULE;
	अगर (type->ops_nokey)
		type->ops_nokey->owner = THIS_MODULE;
	node->type = type;
	list_add(&node->list, &alg_types);
	err = 0;

unlock:
	up_ग_लिखो(&alg_types_sem);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_रेजिस्टर_type);

पूर्णांक af_alg_unरेजिस्टर_type(स्थिर काष्ठा af_alg_type *type)
अणु
	काष्ठा alg_type_list *node;
	पूर्णांक err = -ENOENT;

	करोwn_ग_लिखो(&alg_types_sem);
	list_क्रम_each_entry(node, &alg_types, list) अणु
		अगर (म_भेद(node->type->name, type->name))
			जारी;

		list_del(&node->list);
		kमुक्त(node);
		err = 0;
		अवरोध;
	पूर्ण
	up_ग_लिखो(&alg_types_sem);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_unरेजिस्टर_type);

अटल व्योम alg_करो_release(स्थिर काष्ठा af_alg_type *type, व्योम *निजी)
अणु
	अगर (!type)
		वापस;

	type->release(निजी);
	module_put(type->owner);
पूर्ण

पूर्णांक af_alg_release(काष्ठा socket *sock)
अणु
	अगर (sock->sk) अणु
		sock_put(sock->sk);
		sock->sk = शून्य;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_release);

व्योम af_alg_release_parent(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	अचिन्हित पूर्णांक nokey = atomic_पढ़ो(&ask->nokey_refcnt);

	sk = ask->parent;
	ask = alg_sk(sk);

	अगर (nokey)
		atomic_dec(&ask->nokey_refcnt);

	अगर (atomic_dec_and_test(&ask->refcnt))
		sock_put(sk);
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_release_parent);

अटल पूर्णांक alg_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	स्थिर u32 allowed = CRYPTO_ALG_KERN_DRIVER_ONLY;
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा sockaddr_alg_new *sa = (व्योम *)uaddr;
	स्थिर काष्ठा af_alg_type *type;
	व्योम *निजी;
	पूर्णांक err;

	अगर (sock->state == SS_CONNECTED)
		वापस -EINVAL;

	BUILD_BUG_ON(दुरत्व(काष्ठा sockaddr_alg_new, salg_name) !=
		     दुरत्व(काष्ठा sockaddr_alg, salg_name));
	BUILD_BUG_ON(दुरत्व(काष्ठा sockaddr_alg, salg_name) != माप(*sa));

	अगर (addr_len < माप(*sa) + 1)
		वापस -EINVAL;

	/* If caller uses non-allowed flag, वापस error. */
	अगर ((sa->salg_feat & ~allowed) || (sa->salg_mask & ~allowed))
		वापस -EINVAL;

	sa->salg_type[माप(sa->salg_type) - 1] = 0;
	sa->salg_name[addr_len - माप(*sa) - 1] = 0;

	type = alg_get_type(sa->salg_type);
	अगर (PTR_ERR(type) == -ENOENT) अणु
		request_module("algif-%s", sa->salg_type);
		type = alg_get_type(sa->salg_type);
	पूर्ण

	अगर (IS_ERR(type))
		वापस PTR_ERR(type);

	निजी = type->bind(sa->salg_name, sa->salg_feat, sa->salg_mask);
	अगर (IS_ERR(निजी)) अणु
		module_put(type->owner);
		वापस PTR_ERR(निजी);
	पूर्ण

	err = -EBUSY;
	lock_sock(sk);
	अगर (atomic_पढ़ो(&ask->refcnt))
		जाओ unlock;

	swap(ask->type, type);
	swap(ask->निजी, निजी);

	err = 0;

unlock:
	release_sock(sk);

	alg_करो_release(type, निजी);

	वापस err;
पूर्ण

अटल पूर्णांक alg_setkey(काष्ठा sock *sk, sockptr_t ukey, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	स्थिर काष्ठा af_alg_type *type = ask->type;
	u8 *key;
	पूर्णांक err;

	key = sock_kदो_स्मृति(sk, keylen, GFP_KERNEL);
	अगर (!key)
		वापस -ENOMEM;

	err = -EFAULT;
	अगर (copy_from_sockptr(key, ukey, keylen))
		जाओ out;

	err = type->setkey(ask->निजी, key, keylen);

out:
	sock_kzमुक्त_s(sk, key, keylen);

	वापस err;
पूर्ण

अटल पूर्णांक alg_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	स्थिर काष्ठा af_alg_type *type;
	पूर्णांक err = -EBUSY;

	lock_sock(sk);
	अगर (atomic_पढ़ो(&ask->refcnt) != atomic_पढ़ो(&ask->nokey_refcnt))
		जाओ unlock;

	type = ask->type;

	err = -ENOPROTOOPT;
	अगर (level != SOL_ALG || !type)
		जाओ unlock;

	चयन (optname) अणु
	हाल ALG_SET_KEY:
		अगर (sock->state == SS_CONNECTED)
			जाओ unlock;
		अगर (!type->setkey)
			जाओ unlock;

		err = alg_setkey(sk, optval, optlen);
		अवरोध;
	हाल ALG_SET_AEAD_AUTHSIZE:
		अगर (sock->state == SS_CONNECTED)
			जाओ unlock;
		अगर (!type->setauthsize)
			जाओ unlock;
		err = type->setauthsize(ask->निजी, optlen);
		अवरोध;
	हाल ALG_SET_DRBG_ENTROPY:
		अगर (sock->state == SS_CONNECTED)
			जाओ unlock;
		अगर (!type->setentropy)
			जाओ unlock;

		err = type->setentropy(ask->निजी, optval, optlen);
	पूर्ण

unlock:
	release_sock(sk);

	वापस err;
पूर्ण

पूर्णांक af_alg_accept(काष्ठा sock *sk, काष्ठा socket *newsock, bool kern)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	स्थिर काष्ठा af_alg_type *type;
	काष्ठा sock *sk2;
	अचिन्हित पूर्णांक nokey;
	पूर्णांक err;

	lock_sock(sk);
	type = ask->type;

	err = -EINVAL;
	अगर (!type)
		जाओ unlock;

	sk2 = sk_alloc(sock_net(sk), PF_ALG, GFP_KERNEL, &alg_proto, kern);
	err = -ENOMEM;
	अगर (!sk2)
		जाओ unlock;

	sock_init_data(newsock, sk2);
	security_sock_graft(sk2, newsock);
	security_sk_clone(sk, sk2);

	/*
	 * newsock->ops asचिन्हित here to allow type->accept call to override
	 * them when required.
	 */
	newsock->ops = type->ops;
	err = type->accept(ask->निजी, sk2);

	nokey = err == -ENOKEY;
	अगर (nokey && type->accept_nokey)
		err = type->accept_nokey(ask->निजी, sk2);

	अगर (err)
		जाओ unlock;

	अगर (atomic_inc_वापस_relaxed(&ask->refcnt) == 1)
		sock_hold(sk);
	अगर (nokey) अणु
		atomic_inc(&ask->nokey_refcnt);
		atomic_set(&alg_sk(sk2)->nokey_refcnt, 1);
	पूर्ण
	alg_sk(sk2)->parent = sk;
	alg_sk(sk2)->type = type;

	newsock->state = SS_CONNECTED;

	अगर (nokey)
		newsock->ops = type->ops_nokey;

	err = 0;

unlock:
	release_sock(sk);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_accept);

अटल पूर्णांक alg_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		      bool kern)
अणु
	वापस af_alg_accept(sock->sk, newsock, kern);
पूर्ण

अटल स्थिर काष्ठा proto_ops alg_proto_ops = अणु
	.family		=	PF_ALG,
	.owner		=	THIS_MODULE,

	.connect	=	sock_no_connect,
	.socketpair	=	sock_no_socketpair,
	.getname	=	sock_no_getname,
	.ioctl		=	sock_no_ioctl,
	.listen		=	sock_no_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.mmap		=	sock_no_mmap,
	.sendpage	=	sock_no_sendpage,
	.sendmsg	=	sock_no_sendmsg,
	.recvmsg	=	sock_no_recvmsg,

	.bind		=	alg_bind,
	.release	=	af_alg_release,
	.setsockopt	=	alg_setsockopt,
	.accept		=	alg_accept,
पूर्ण;

अटल व्योम alg_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);

	alg_करो_release(ask->type, ask->निजी);
पूर्ण

अटल पूर्णांक alg_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	पूर्णांक err;

	अगर (sock->type != SOCK_SEQPACKET)
		वापस -ESOCKTNOSUPPORT;
	अगर (protocol != 0)
		वापस -EPROTONOSUPPORT;

	err = -ENOMEM;
	sk = sk_alloc(net, PF_ALG, GFP_KERNEL, &alg_proto, kern);
	अगर (!sk)
		जाओ out;

	sock->ops = &alg_proto_ops;
	sock_init_data(sock, sk);

	sk->sk_deकाष्ठा = alg_sock_deकाष्ठा;

	वापस 0;
out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_proto_family alg_family = अणु
	.family	=	PF_ALG,
	.create	=	alg_create,
	.owner	=	THIS_MODULE,
पूर्ण;

पूर्णांक af_alg_make_sg(काष्ठा af_alg_sgl *sgl, काष्ठा iov_iter *iter, पूर्णांक len)
अणु
	माप_प्रकार off;
	sमाप_प्रकार n;
	पूर्णांक npages, i;

	n = iov_iter_get_pages(iter, sgl->pages, len, ALG_MAX_PAGES, &off);
	अगर (n < 0)
		वापस n;

	npages = (off + n + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अगर (WARN_ON(npages == 0))
		वापस -EINVAL;
	/* Add one extra क्रम linking */
	sg_init_table(sgl->sg, npages + 1);

	क्रम (i = 0, len = n; i < npages; i++) अणु
		पूर्णांक plen = min_t(पूर्णांक, len, PAGE_SIZE - off);

		sg_set_page(sgl->sg + i, sgl->pages[i], plen, off);

		off = 0;
		len -= plen;
	पूर्ण
	sg_mark_end(sgl->sg + npages - 1);
	sgl->npages = npages;

	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_make_sg);

अटल व्योम af_alg_link_sg(काष्ठा af_alg_sgl *sgl_prev,
			   काष्ठा af_alg_sgl *sgl_new)
अणु
	sg_unmark_end(sgl_prev->sg + sgl_prev->npages - 1);
	sg_chain(sgl_prev->sg, sgl_prev->npages + 1, sgl_new->sg);
पूर्ण

व्योम af_alg_मुक्त_sg(काष्ठा af_alg_sgl *sgl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sgl->npages; i++)
		put_page(sgl->pages[i]);
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_मुक्त_sg);

अटल पूर्णांक af_alg_cmsg_send(काष्ठा msghdr *msg, काष्ठा af_alg_control *con)
अणु
	काष्ठा cmsghdr *cmsg;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;
		अगर (cmsg->cmsg_level != SOL_ALG)
			जारी;

		चयन (cmsg->cmsg_type) अणु
		हाल ALG_SET_IV:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(*con->iv)))
				वापस -EINVAL;
			con->iv = (व्योम *)CMSG_DATA(cmsg);
			अगर (cmsg->cmsg_len < CMSG_LEN(con->iv->ivlen +
						      माप(*con->iv)))
				वापस -EINVAL;
			अवरोध;

		हाल ALG_SET_OP:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(u32)))
				वापस -EINVAL;
			con->op = *(u32 *)CMSG_DATA(cmsg);
			अवरोध;

		हाल ALG_SET_AEAD_ASSOCLEN:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(u32)))
				वापस -EINVAL;
			con->aead_assoclen = *(u32 *)CMSG_DATA(cmsg);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * af_alg_alloc_tsgl - allocate the TX SGL
 *
 * @sk: socket of connection to user space
 * Return: 0 upon success, < 0 upon error
 */
अटल पूर्णांक af_alg_alloc_tsgl(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा af_alg_tsgl *sgl;
	काष्ठा scatterlist *sg = शून्य;

	sgl = list_entry(ctx->tsgl_list.prev, काष्ठा af_alg_tsgl, list);
	अगर (!list_empty(&ctx->tsgl_list))
		sg = sgl->sg;

	अगर (!sg || sgl->cur >= MAX_SGL_ENTS) अणु
		sgl = sock_kदो_स्मृति(sk,
				   काष्ठा_size(sgl, sg, (MAX_SGL_ENTS + 1)),
				   GFP_KERNEL);
		अगर (!sgl)
			वापस -ENOMEM;

		sg_init_table(sgl->sg, MAX_SGL_ENTS + 1);
		sgl->cur = 0;

		अगर (sg)
			sg_chain(sg, MAX_SGL_ENTS + 1, sgl->sg);

		list_add_tail(&sgl->list, &ctx->tsgl_list);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * af_alg_count_tsgl - Count number of TX SG entries
 *
 * The counting starts from the beginning of the SGL to @bytes. If
 * an @offset is provided, the counting of the SG entries starts at the @offset.
 *
 * @sk: socket of connection to user space
 * @bytes: Count the number of SG entries holding given number of bytes.
 * @offset: Start the counting of SG entries from the given offset.
 * Return: Number of TX SG entries found given the स्थिरraपूर्णांकs
 */
अचिन्हित पूर्णांक af_alg_count_tsgl(काष्ठा sock *sk, माप_प्रकार bytes, माप_प्रकार offset)
अणु
	स्थिर काष्ठा alg_sock *ask = alg_sk(sk);
	स्थिर काष्ठा af_alg_ctx *ctx = ask->निजी;
	स्थिर काष्ठा af_alg_tsgl *sgl;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक sgl_count = 0;

	अगर (!bytes)
		वापस 0;

	list_क्रम_each_entry(sgl, &ctx->tsgl_list, list) अणु
		स्थिर काष्ठा scatterlist *sg = sgl->sg;

		क्रम (i = 0; i < sgl->cur; i++) अणु
			माप_प्रकार bytes_count;

			/* Skip offset */
			अगर (offset >= sg[i].length) अणु
				offset -= sg[i].length;
				bytes -= sg[i].length;
				जारी;
			पूर्ण

			bytes_count = sg[i].length - offset;

			offset = 0;
			sgl_count++;

			/* If we have seen requested number of bytes, stop */
			अगर (bytes_count >= bytes)
				वापस sgl_count;

			bytes -= bytes_count;
		पूर्ण
	पूर्ण

	वापस sgl_count;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_count_tsgl);

/**
 * af_alg_pull_tsgl - Release the specअगरied buffers from TX SGL
 *
 * If @dst is non-null, reassign the pages to @dst. The caller must release
 * the pages. If @dst_offset is given only reassign the pages to @dst starting
 * at the @dst_offset (byte). The caller must ensure that @dst is large
 * enough (e.g. by using af_alg_count_tsgl with the same offset).
 *
 * @sk: socket of connection to user space
 * @used: Number of bytes to pull from TX SGL
 * @dst: If non-शून्य, buffer is reasचिन्हित to dst SGL instead of releasing. The
 *	 caller must release the buffers in dst.
 * @dst_offset: Reassign the TX SGL from given offset. All buffers beक्रमe
 *	        reaching the offset is released.
 */
व्योम af_alg_pull_tsgl(काष्ठा sock *sk, माप_प्रकार used, काष्ठा scatterlist *dst,
		      माप_प्रकार dst_offset)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा af_alg_tsgl *sgl;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i, j = 0;

	जबतक (!list_empty(&ctx->tsgl_list)) अणु
		sgl = list_first_entry(&ctx->tsgl_list, काष्ठा af_alg_tsgl,
				       list);
		sg = sgl->sg;

		क्रम (i = 0; i < sgl->cur; i++) अणु
			माप_प्रकार plen = min_t(माप_प्रकार, used, sg[i].length);
			काष्ठा page *page = sg_page(sg + i);

			अगर (!page)
				जारी;

			/*
			 * Assumption: caller created af_alg_count_tsgl(len)
			 * SG entries in dst.
			 */
			अगर (dst) अणु
				अगर (dst_offset >= plen) अणु
					/* discard page beक्रमe offset */
					dst_offset -= plen;
				पूर्ण अन्यथा अणु
					/* reassign page to dst after offset */
					get_page(page);
					sg_set_page(dst + j, page,
						    plen - dst_offset,
						    sg[i].offset + dst_offset);
					dst_offset = 0;
					j++;
				पूर्ण
			पूर्ण

			sg[i].length -= plen;
			sg[i].offset += plen;

			used -= plen;
			ctx->used -= plen;

			अगर (sg[i].length)
				वापस;

			put_page(page);
			sg_assign_page(sg + i, शून्य);
		पूर्ण

		list_del(&sgl->list);
		sock_kमुक्त_s(sk, sgl, काष्ठा_size(sgl, sg, MAX_SGL_ENTS + 1));
	पूर्ण

	अगर (!ctx->used)
		ctx->merge = 0;
	ctx->init = ctx->more;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_pull_tsgl);

/**
 * af_alg_मुक्त_areq_sgls - Release TX and RX SGLs of the request
 *
 * @areq: Request holding the TX and RX SGL
 */
अटल व्योम af_alg_मुक्त_areq_sgls(काष्ठा af_alg_async_req *areq)
अणु
	काष्ठा sock *sk = areq->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा af_alg_rsgl *rsgl, *पंचांगp;
	काष्ठा scatterlist *tsgl;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	list_क्रम_each_entry_safe(rsgl, पंचांगp, &areq->rsgl_list, list) अणु
		atomic_sub(rsgl->sg_num_bytes, &ctx->rcvused);
		af_alg_मुक्त_sg(&rsgl->sgl);
		list_del(&rsgl->list);
		अगर (rsgl != &areq->first_rsgl)
			sock_kमुक्त_s(sk, rsgl, माप(*rsgl));
	पूर्ण

	tsgl = areq->tsgl;
	अगर (tsgl) अणु
		क्रम_each_sg(tsgl, sg, areq->tsgl_entries, i) अणु
			अगर (!sg_page(sg))
				जारी;
			put_page(sg_page(sg));
		पूर्ण

		sock_kमुक्त_s(sk, tsgl, areq->tsgl_entries * माप(*tsgl));
	पूर्ण
पूर्ण

/**
 * af_alg_रुको_क्रम_wmem - रुको क्रम availability of writable memory
 *
 * @sk: socket of connection to user space
 * @flags: If MSG_DONTWAIT is set, then only report अगर function would sleep
 * Return: 0 when writable memory is available, < 0 upon error
 */
अटल पूर्णांक af_alg_रुको_क्रम_wmem(काष्ठा sock *sk, अचिन्हित पूर्णांक flags)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	पूर्णांक err = -ERESTARTSYS;
	दीर्घ समयout;

	अगर (flags & MSG_DONTWAIT)
		वापस -EAGAIN;

	sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	add_रुको_queue(sk_sleep(sk), &रुको);
	क्रम (;;) अणु
		अगर (संकेत_pending(current))
			अवरोध;
		समयout = MAX_SCHEDULE_TIMEOUT;
		अगर (sk_रुको_event(sk, &समयout, af_alg_writable(sk), &रुको)) अणु
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	वापस err;
पूर्ण

/**
 * af_alg_wmem_wakeup - wakeup caller when writable memory is available
 *
 * @sk: socket of connection to user space
 */
व्योम af_alg_wmem_wakeup(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	अगर (!af_alg_writable(sk))
		वापस;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLIN |
							   EPOLLRDNORM |
							   EPOLLRDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_wmem_wakeup);

/**
 * af_alg_रुको_क्रम_data - रुको क्रम availability of TX data
 *
 * @sk: socket of connection to user space
 * @flags: If MSG_DONTWAIT is set, then only report अगर function would sleep
 * @min: Set to minimum request size अगर partial requests are allowed.
 * Return: 0 when writable memory is available, < 0 upon error
 */
पूर्णांक af_alg_रुको_क्रम_data(काष्ठा sock *sk, अचिन्हित flags, अचिन्हित min)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	दीर्घ समयout;
	पूर्णांक err = -ERESTARTSYS;

	अगर (flags & MSG_DONTWAIT)
		वापस -EAGAIN;

	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);

	add_रुको_queue(sk_sleep(sk), &रुको);
	क्रम (;;) अणु
		अगर (संकेत_pending(current))
			अवरोध;
		समयout = MAX_SCHEDULE_TIMEOUT;
		अगर (sk_रुको_event(sk, &समयout,
				  ctx->init && (!ctx->more ||
						(min && ctx->used >= min)),
				  &रुको)) अणु
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_रुको_क्रम_data);

/**
 * af_alg_data_wakeup - wakeup caller when new data can be sent to kernel
 *
 * @sk: socket of connection to user space
 */
अटल व्योम af_alg_data_wakeup(काष्ठा sock *sk)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा socket_wq *wq;

	अगर (!ctx->used)
		वापस;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLOUT |
							   EPOLLRDNORM |
							   EPOLLRDBAND);
	sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * af_alg_sendmsg - implementation of sendmsg प्रणाली call handler
 *
 * The sendmsg प्रणाली call handler obtains the user data and stores it
 * in ctx->tsgl_list. This implies allocation of the required numbers of
 * काष्ठा af_alg_tsgl.
 *
 * In addition, the ctx is filled with the inक्रमmation sent via CMSG.
 *
 * @sock: socket of connection to user space
 * @msg: message from user space
 * @size: size of message from user space
 * @ivsize: the size of the IV क्रम the cipher operation to verअगरy that the
 *	   user-space-provided IV has the right size
 * Return: the number of copied data upon success, < 0 upon error
 */
पूर्णांक af_alg_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		   अचिन्हित पूर्णांक ivsize)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा af_alg_tsgl *sgl;
	काष्ठा af_alg_control con = अणुपूर्ण;
	दीर्घ copied = 0;
	bool enc = false;
	bool init = false;
	पूर्णांक err = 0;

	अगर (msg->msg_controllen) अणु
		err = af_alg_cmsg_send(msg, &con);
		अगर (err)
			वापस err;

		init = true;
		चयन (con.op) अणु
		हाल ALG_OP_ENCRYPT:
			enc = true;
			अवरोध;
		हाल ALG_OP_DECRYPT:
			enc = false;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (con.iv && con.iv->ivlen != ivsize)
			वापस -EINVAL;
	पूर्ण

	lock_sock(sk);
	अगर (ctx->init && !ctx->more) अणु
		अगर (ctx->used) अणु
			err = -EINVAL;
			जाओ unlock;
		पूर्ण

		pr_info_once(
			"%s sent an empty control message without MSG_MORE.\n",
			current->comm);
	पूर्ण
	ctx->init = true;

	अगर (init) अणु
		ctx->enc = enc;
		अगर (con.iv)
			स_नकल(ctx->iv, con.iv->iv, ivsize);

		ctx->aead_assoclen = con.aead_assoclen;
	पूर्ण

	जबतक (size) अणु
		काष्ठा scatterlist *sg;
		माप_प्रकार len = size;
		माप_प्रकार plen;

		/* use the existing memory in an allocated page */
		अगर (ctx->merge) अणु
			sgl = list_entry(ctx->tsgl_list.prev,
					 काष्ठा af_alg_tsgl, list);
			sg = sgl->sg + sgl->cur - 1;
			len = min_t(माप_प्रकार, len,
				    PAGE_SIZE - sg->offset - sg->length);

			err = स_नकल_from_msg(page_address(sg_page(sg)) +
					      sg->offset + sg->length,
					      msg, len);
			अगर (err)
				जाओ unlock;

			sg->length += len;
			ctx->merge = (sg->offset + sg->length) &
				     (PAGE_SIZE - 1);

			ctx->used += len;
			copied += len;
			size -= len;
			जारी;
		पूर्ण

		अगर (!af_alg_writable(sk)) अणु
			err = af_alg_रुको_क्रम_wmem(sk, msg->msg_flags);
			अगर (err)
				जाओ unlock;
		पूर्ण

		/* allocate a new page */
		len = min_t(अचिन्हित दीर्घ, len, af_alg_sndbuf(sk));

		err = af_alg_alloc_tsgl(sk);
		अगर (err)
			जाओ unlock;

		sgl = list_entry(ctx->tsgl_list.prev, काष्ठा af_alg_tsgl,
				 list);
		sg = sgl->sg;
		अगर (sgl->cur)
			sg_unmark_end(sg + sgl->cur - 1);

		करो अणु
			अचिन्हित पूर्णांक i = sgl->cur;

			plen = min_t(माप_प्रकार, len, PAGE_SIZE);

			sg_assign_page(sg + i, alloc_page(GFP_KERNEL));
			अगर (!sg_page(sg + i)) अणु
				err = -ENOMEM;
				जाओ unlock;
			पूर्ण

			err = स_नकल_from_msg(page_address(sg_page(sg + i)),
					      msg, plen);
			अगर (err) अणु
				__मुक्त_page(sg_page(sg + i));
				sg_assign_page(sg + i, शून्य);
				जाओ unlock;
			पूर्ण

			sg[i].length = plen;
			len -= plen;
			ctx->used += plen;
			copied += plen;
			size -= plen;
			sgl->cur++;
		पूर्ण जबतक (len && sgl->cur < MAX_SGL_ENTS);

		अगर (!size)
			sg_mark_end(sg + sgl->cur - 1);

		ctx->merge = plen & (PAGE_SIZE - 1);
	पूर्ण

	err = 0;

	ctx->more = msg->msg_flags & MSG_MORE;

unlock:
	af_alg_data_wakeup(sk);
	release_sock(sk);

	वापस copied ?: err;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_sendmsg);

/**
 * af_alg_sendpage - sendpage प्रणाली call handler
 * @sock: socket of connection to user space to ग_लिखो to
 * @page: data to send
 * @offset: offset पूर्णांकo page to begin sending
 * @size: length of data
 * @flags: message send/receive flags
 *
 * This is a generic implementation of sendpage to fill ctx->tsgl_list.
 */
sमाप_प्रकार af_alg_sendpage(काष्ठा socket *sock, काष्ठा page *page,
			पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	काष्ठा af_alg_tsgl *sgl;
	पूर्णांक err = -EINVAL;

	अगर (flags & MSG_SENDPAGE_NOTLAST)
		flags |= MSG_MORE;

	lock_sock(sk);
	अगर (!ctx->more && ctx->used)
		जाओ unlock;

	अगर (!size)
		जाओ करोne;

	अगर (!af_alg_writable(sk)) अणु
		err = af_alg_रुको_क्रम_wmem(sk, flags);
		अगर (err)
			जाओ unlock;
	पूर्ण

	err = af_alg_alloc_tsgl(sk);
	अगर (err)
		जाओ unlock;

	ctx->merge = 0;
	sgl = list_entry(ctx->tsgl_list.prev, काष्ठा af_alg_tsgl, list);

	अगर (sgl->cur)
		sg_unmark_end(sgl->sg + sgl->cur - 1);

	sg_mark_end(sgl->sg + sgl->cur);

	get_page(page);
	sg_set_page(sgl->sg + sgl->cur, page, size, offset);
	sgl->cur++;
	ctx->used += size;

करोne:
	ctx->more = flags & MSG_MORE;

unlock:
	af_alg_data_wakeup(sk);
	release_sock(sk);

	वापस err ?: size;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_sendpage);

/**
 * af_alg_मुक्त_resources - release resources required क्रम crypto request
 * @areq: Request holding the TX and RX SGL
 */
व्योम af_alg_मुक्त_resources(काष्ठा af_alg_async_req *areq)
अणु
	काष्ठा sock *sk = areq->sk;

	af_alg_मुक्त_areq_sgls(areq);
	sock_kमुक्त_s(sk, areq, areq->areqlen);
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_मुक्त_resources);

/**
 * af_alg_async_cb - AIO callback handler
 * @_req: async request info
 * @err: अगर non-zero, error result to be वापसed via ki_complete();
 *       otherwise वापस the AIO output length via ki_complete().
 *
 * This handler cleans up the काष्ठा af_alg_async_req upon completion of the
 * AIO operation.
 *
 * The number of bytes to be generated with the AIO operation must be set
 * in areq->outlen beक्रमe the AIO callback handler is invoked.
 */
व्योम af_alg_async_cb(काष्ठा crypto_async_request *_req, पूर्णांक err)
अणु
	काष्ठा af_alg_async_req *areq = _req->data;
	काष्ठा sock *sk = areq->sk;
	काष्ठा kiocb *iocb = areq->iocb;
	अचिन्हित पूर्णांक resultlen;

	/* Buffer size written by crypto operation. */
	resultlen = areq->outlen;

	af_alg_मुक्त_resources(areq);
	sock_put(sk);

	iocb->ki_complete(iocb, err ? err : (पूर्णांक)resultlen, 0);
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_async_cb);

/**
 * af_alg_poll - poll प्रणाली call handler
 * @file: file poपूर्णांकer
 * @sock: socket to poll
 * @रुको: poll_table
 */
__poll_t af_alg_poll(काष्ठा file *file, काष्ठा socket *sock,
			 poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	__poll_t mask;

	sock_poll_रुको(file, sock, रुको);
	mask = 0;

	अगर (!ctx->more || ctx->used)
		mask |= EPOLLIN | EPOLLRDNORM;

	अगर (af_alg_writable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	वापस mask;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_poll);

/**
 * af_alg_alloc_areq - allocate काष्ठा af_alg_async_req
 *
 * @sk: socket of connection to user space
 * @areqlen: size of काष्ठा af_alg_async_req + crypto_*_reqsize
 * Return: allocated data काष्ठाure or ERR_PTR upon error
 */
काष्ठा af_alg_async_req *af_alg_alloc_areq(काष्ठा sock *sk,
					   अचिन्हित पूर्णांक areqlen)
अणु
	काष्ठा af_alg_async_req *areq = sock_kदो_स्मृति(sk, areqlen, GFP_KERNEL);

	अगर (unlikely(!areq))
		वापस ERR_PTR(-ENOMEM);

	areq->areqlen = areqlen;
	areq->sk = sk;
	areq->last_rsgl = शून्य;
	INIT_LIST_HEAD(&areq->rsgl_list);
	areq->tsgl = शून्य;
	areq->tsgl_entries = 0;

	वापस areq;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_alloc_areq);

/**
 * af_alg_get_rsgl - create the RX SGL क्रम the output data from the crypto
 *		     operation
 *
 * @sk: socket of connection to user space
 * @msg: user space message
 * @flags: flags used to invoke recvmsg with
 * @areq: instance of the cryptographic request that will hold the RX SGL
 * @maxsize: maximum number of bytes to be pulled from user space
 * @outlen: number of bytes in the RX SGL
 * Return: 0 on success, < 0 upon error
 */
पूर्णांक af_alg_get_rsgl(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक flags,
		    काष्ठा af_alg_async_req *areq, माप_प्रकार maxsize,
		    माप_प्रकार *outlen)
अणु
	काष्ठा alg_sock *ask = alg_sk(sk);
	काष्ठा af_alg_ctx *ctx = ask->निजी;
	माप_प्रकार len = 0;

	जबतक (maxsize > len && msg_data_left(msg)) अणु
		काष्ठा af_alg_rsgl *rsgl;
		माप_प्रकार seglen;
		पूर्णांक err;

		/* limit the amount of पढ़ोable buffers */
		अगर (!af_alg_पढ़ोable(sk))
			अवरोध;

		seglen = min_t(माप_प्रकार, (maxsize - len),
			       msg_data_left(msg));

		अगर (list_empty(&areq->rsgl_list)) अणु
			rsgl = &areq->first_rsgl;
		पूर्ण अन्यथा अणु
			rsgl = sock_kदो_स्मृति(sk, माप(*rsgl), GFP_KERNEL);
			अगर (unlikely(!rsgl))
				वापस -ENOMEM;
		पूर्ण

		rsgl->sgl.npages = 0;
		list_add_tail(&rsgl->list, &areq->rsgl_list);

		/* make one iovec available as scatterlist */
		err = af_alg_make_sg(&rsgl->sgl, &msg->msg_iter, seglen);
		अगर (err < 0) अणु
			rsgl->sg_num_bytes = 0;
			वापस err;
		पूर्ण

		/* chain the new scatterlist with previous one */
		अगर (areq->last_rsgl)
			af_alg_link_sg(&areq->last_rsgl->sgl, &rsgl->sgl);

		areq->last_rsgl = rsgl;
		len += err;
		atomic_add(err, &ctx->rcvused);
		rsgl->sg_num_bytes = err;
		iov_iter_advance(&msg->msg_iter, err);
	पूर्ण

	*outlen = len;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(af_alg_get_rsgl);

अटल पूर्णांक __init af_alg_init(व्योम)
अणु
	पूर्णांक err = proto_रेजिस्टर(&alg_proto, 0);

	अगर (err)
		जाओ out;

	err = sock_रेजिस्टर(&alg_family);
	अगर (err != 0)
		जाओ out_unरेजिस्टर_proto;

out:
	वापस err;

out_unरेजिस्टर_proto:
	proto_unरेजिस्टर(&alg_proto);
	जाओ out;
पूर्ण

अटल व्योम __निकास af_alg_निकास(व्योम)
अणु
	sock_unरेजिस्टर(PF_ALG);
	proto_unरेजिस्टर(&alg_proto);
पूर्ण

module_init(af_alg_init);
module_निकास(af_alg_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(AF_ALG);
