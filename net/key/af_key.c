<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/key/af_key.c	An implementation of PF_KEYv2 sockets.
 *
 * Authors:	Maxim Giryaev	<gem@asplinux.ru>
 *		David S. Miller	<davem@redhat.com>
 *		Alexey Kuznetsov <kuznet@ms2.inr.ac.ru>
 *		Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 *		Kazunori MIYAZAWA / USAGI Project <miyazawa@linux-ipv6.org>
 *		Derek Atkins <derek@ihtfp.com>
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/socket.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/ipsec.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/xfrm.h>

#समावेश <net/sock.h>

#घोषणा _X2KEY(x) ((x) == XFRM_INF ? 0 : (x))
#घोषणा _KEY2X(x) ((x) == 0 ? XFRM_INF : (x))

अटल अचिन्हित पूर्णांक pfkey_net_id __पढ़ो_mostly;
काष्ठा netns_pfkey अणु
	/* List of all pfkey sockets. */
	काष्ठा hlist_head table;
	atomic_t socks_nr;
पूर्ण;
अटल DEFINE_MUTEX(pfkey_mutex);

#घोषणा DUMMY_MARK 0
अटल स्थिर काष्ठा xfrm_mark dummy_mark = अणु0, 0पूर्ण;
काष्ठा pfkey_sock अणु
	/* काष्ठा sock must be the first member of काष्ठा pfkey_sock */
	काष्ठा sock	sk;
	पूर्णांक		रेजिस्टरed;
	पूर्णांक		promisc;

	काष्ठा अणु
		uपूर्णांक8_t		msg_version;
		uपूर्णांक32_t	msg_portid;
		पूर्णांक		(*dump)(काष्ठा pfkey_sock *sk);
		व्योम		(*करोne)(काष्ठा pfkey_sock *sk);
		जोड़ अणु
			काष्ठा xfrm_policy_walk	policy;
			काष्ठा xfrm_state_walk	state;
		पूर्ण u;
		काष्ठा sk_buff	*skb;
	पूर्ण dump;
	काष्ठा mutex dump_lock;
पूर्ण;

अटल पूर्णांक parse_sockaddr_pair(काष्ठा sockaddr *sa, पूर्णांक ext_len,
			       xfrm_address_t *saddr, xfrm_address_t *daddr,
			       u16 *family);

अटल अंतरभूत काष्ठा pfkey_sock *pfkey_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा pfkey_sock *)sk;
पूर्ण

अटल पूर्णांक pfkey_can_dump(स्थिर काष्ठा sock *sk)
अणु
	अगर (3 * atomic_पढ़ो(&sk->sk_rmem_alloc) <= 2 * sk->sk_rcvbuf)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम pfkey_terminate_dump(काष्ठा pfkey_sock *pfk)
अणु
	अगर (pfk->dump.dump) अणु
		अगर (pfk->dump.skb) अणु
			kमुक्त_skb(pfk->dump.skb);
			pfk->dump.skb = शून्य;
		पूर्ण
		pfk->dump.करोne(pfk);
		pfk->dump.dump = शून्य;
		pfk->dump.करोne = शून्य;
	पूर्ण
पूर्ण

अटल व्योम pfkey_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	pfkey_terminate_dump(pfkey_sk(sk));
	skb_queue_purge(&sk->sk_receive_queue);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_err("Attempt to release alive pfkey socket: %p\n", sk);
		वापस;
	पूर्ण

	WARN_ON(atomic_पढ़ो(&sk->sk_rmem_alloc));
	WARN_ON(refcount_पढ़ो(&sk->sk_wmem_alloc));

	atomic_dec(&net_pfkey->socks_nr);
पूर्ण

अटल स्थिर काष्ठा proto_ops pfkey_ops;

अटल व्योम pfkey_insert(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	mutex_lock(&pfkey_mutex);
	sk_add_node_rcu(sk, &net_pfkey->table);
	mutex_unlock(&pfkey_mutex);
पूर्ण

अटल व्योम pfkey_हटाओ(काष्ठा sock *sk)
अणु
	mutex_lock(&pfkey_mutex);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&pfkey_mutex);
पूर्ण

अटल काष्ठा proto key_proto = अणु
	.name	  = "KEY",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा pfkey_sock),
पूर्ण;

अटल पूर्णांक pfkey_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			पूर्णांक kern)
अणु
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);
	काष्ठा sock *sk;
	काष्ठा pfkey_sock *pfk;
	पूर्णांक err;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;
	अगर (protocol != PF_KEY_V2)
		वापस -EPROTONOSUPPORT;

	err = -ENOMEM;
	sk = sk_alloc(net, PF_KEY, GFP_KERNEL, &key_proto, kern);
	अगर (sk == शून्य)
		जाओ out;

	pfk = pfkey_sk(sk);
	mutex_init(&pfk->dump_lock);

	sock->ops = &pfkey_ops;
	sock_init_data(sock, sk);

	sk->sk_family = PF_KEY;
	sk->sk_deकाष्ठा = pfkey_sock_deकाष्ठा;

	atomic_inc(&net_pfkey->socks_nr);

	pfkey_insert(sk);

	वापस 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक pfkey_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (!sk)
		वापस 0;

	pfkey_हटाओ(sk);

	sock_orphan(sk);
	sock->sk = शून्य;
	skb_queue_purge(&sk->sk_ग_लिखो_queue);

	synchronize_rcu();
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_broadcast_one(काष्ठा sk_buff *skb, gfp_t allocation,
			       काष्ठा sock *sk)
अणु
	पूर्णांक err = -ENOBUFS;

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) > sk->sk_rcvbuf)
		वापस err;

	skb = skb_clone(skb, allocation);

	अगर (skb) अणु
		skb_set_owner_r(skb, sk);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_data_पढ़ोy(sk);
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

/* Send SKB to all pfkey sockets matching selected criteria.  */
#घोषणा BROADCAST_ALL		0
#घोषणा BROADCAST_ONE		1
#घोषणा BROADCAST_REGISTERED	2
#घोषणा BROADCAST_PROMISC_ONLY	4
अटल पूर्णांक pfkey_broadcast(काष्ठा sk_buff *skb, gfp_t allocation,
			   पूर्णांक broadcast_flags, काष्ठा sock *one_sk,
			   काष्ठा net *net)
अणु
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);
	काष्ठा sock *sk;
	पूर्णांक err = -ESRCH;

	/* XXX Do we need something like netlink_overrun?  I think
	 * XXX PF_KEY socket apps will not mind current behavior.
	 */
	अगर (!skb)
		वापस -ENOMEM;

	rcu_पढ़ो_lock();
	sk_क्रम_each_rcu(sk, &net_pfkey->table) अणु
		काष्ठा pfkey_sock *pfk = pfkey_sk(sk);
		पूर्णांक err2;

		/* Yes, it means that अगर you are meant to receive this
		 * pfkey message you receive it twice as promiscuous
		 * socket.
		 */
		अगर (pfk->promisc)
			pfkey_broadcast_one(skb, GFP_ATOMIC, sk);

		/* the exact target will be processed later */
		अगर (sk == one_sk)
			जारी;
		अगर (broadcast_flags != BROADCAST_ALL) अणु
			अगर (broadcast_flags & BROADCAST_PROMISC_ONLY)
				जारी;
			अगर ((broadcast_flags & BROADCAST_REGISTERED) &&
			    !pfk->रेजिस्टरed)
				जारी;
			अगर (broadcast_flags & BROADCAST_ONE)
				जारी;
		पूर्ण

		err2 = pfkey_broadcast_one(skb, GFP_ATOMIC, sk);

		/* Error is cleared after successful sending to at least one
		 * रेजिस्टरed KM */
		अगर ((broadcast_flags & BROADCAST_REGISTERED) && err)
			err = err2;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (one_sk != शून्य)
		err = pfkey_broadcast_one(skb, allocation, one_sk);

	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक pfkey_करो_dump(काष्ठा pfkey_sock *pfk)
अणु
	काष्ठा sadb_msg *hdr;
	पूर्णांक rc;

	mutex_lock(&pfk->dump_lock);
	अगर (!pfk->dump.dump) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	rc = pfk->dump.dump(pfk);
	अगर (rc == -ENOBUFS) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (pfk->dump.skb) अणु
		अगर (!pfkey_can_dump(&pfk->sk)) अणु
			rc = 0;
			जाओ out;
		पूर्ण

		hdr = (काष्ठा sadb_msg *) pfk->dump.skb->data;
		hdr->sadb_msg_seq = 0;
		hdr->sadb_msg_त्रुटि_सं = rc;
		pfkey_broadcast(pfk->dump.skb, GFP_ATOMIC, BROADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
		pfk->dump.skb = शून्य;
	पूर्ण

	pfkey_terminate_dump(pfk);

out:
	mutex_unlock(&pfk->dump_lock);
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम pfkey_hdr_dup(काष्ठा sadb_msg *new,
				 स्थिर काष्ठा sadb_msg *orig)
अणु
	*new = *orig;
पूर्ण

अटल पूर्णांक pfkey_error(स्थिर काष्ठा sadb_msg *orig, पूर्णांक err, काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb = alloc_skb(माप(काष्ठा sadb_msg) + 16, GFP_KERNEL);
	काष्ठा sadb_msg *hdr;

	अगर (!skb)
		वापस -ENOBUFS;

	/* Woe be to the platक्रमm trying to support PFKEY yet
	 * having normal त्रुटि_संs outside the 1-255 range, inclusive.
	 */
	err = -err;
	अगर (err == ERESTARTSYS ||
	    err == ERESTARTNOHAND ||
	    err == ERESTARTNOINTR)
		err = EINTR;
	अगर (err >= 512)
		err = EINVAL;
	BUG_ON(err <= 0 || err >= 256);

	hdr = skb_put(skb, माप(काष्ठा sadb_msg));
	pfkey_hdr_dup(hdr, orig);
	hdr->sadb_msg_त्रुटि_सं = (uपूर्णांक8_t) err;
	hdr->sadb_msg_len = (माप(काष्ठा sadb_msg) /
			     माप(uपूर्णांक64_t));

	pfkey_broadcast(skb, GFP_KERNEL, BROADCAST_ONE, sk, sock_net(sk));

	वापस 0;
पूर्ण

अटल स्थिर u8 sadb_ext_min_len[] = अणु
	[SADB_EXT_RESERVED]		= (u8) 0,
	[SADB_EXT_SA]			= (u8) माप(काष्ठा sadb_sa),
	[SADB_EXT_LIFETIME_CURRENT]	= (u8) माप(काष्ठा sadb_lअगरeसमय),
	[SADB_EXT_LIFETIME_HARD]	= (u8) माप(काष्ठा sadb_lअगरeसमय),
	[SADB_EXT_LIFETIME_SOFT]	= (u8) माप(काष्ठा sadb_lअगरeसमय),
	[SADB_EXT_ADDRESS_SRC]		= (u8) माप(काष्ठा sadb_address),
	[SADB_EXT_ADDRESS_DST]		= (u8) माप(काष्ठा sadb_address),
	[SADB_EXT_ADDRESS_PROXY]	= (u8) माप(काष्ठा sadb_address),
	[SADB_EXT_KEY_AUTH]		= (u8) माप(काष्ठा sadb_key),
	[SADB_EXT_KEY_ENCRYPT]		= (u8) माप(काष्ठा sadb_key),
	[SADB_EXT_IDENTITY_SRC]		= (u8) माप(काष्ठा sadb_ident),
	[SADB_EXT_IDENTITY_DST]		= (u8) माप(काष्ठा sadb_ident),
	[SADB_EXT_SENSITIVITY]		= (u8) माप(काष्ठा sadb_sens),
	[SADB_EXT_PROPOSAL]		= (u8) माप(काष्ठा sadb_prop),
	[SADB_EXT_SUPPORTED_AUTH]	= (u8) माप(काष्ठा sadb_supported),
	[SADB_EXT_SUPPORTED_ENCRYPT]	= (u8) माप(काष्ठा sadb_supported),
	[SADB_EXT_SPIRANGE]		= (u8) माप(काष्ठा sadb_spirange),
	[SADB_X_EXT_KMPRIVATE]		= (u8) माप(काष्ठा sadb_x_kmनिजी),
	[SADB_X_EXT_POLICY]		= (u8) माप(काष्ठा sadb_x_policy),
	[SADB_X_EXT_SA2]		= (u8) माप(काष्ठा sadb_x_sa2),
	[SADB_X_EXT_NAT_T_TYPE]		= (u8) माप(काष्ठा sadb_x_nat_t_type),
	[SADB_X_EXT_NAT_T_SPORT]	= (u8) माप(काष्ठा sadb_x_nat_t_port),
	[SADB_X_EXT_NAT_T_DPORT]	= (u8) माप(काष्ठा sadb_x_nat_t_port),
	[SADB_X_EXT_NAT_T_OA]		= (u8) माप(काष्ठा sadb_address),
	[SADB_X_EXT_SEC_CTX]		= (u8) माप(काष्ठा sadb_x_sec_ctx),
	[SADB_X_EXT_KMADDRESS]		= (u8) माप(काष्ठा sadb_x_kmaddress),
	[SADB_X_EXT_FILTER]		= (u8) माप(काष्ठा sadb_x_filter),
पूर्ण;

/* Verअगरy sadb_address_अणुlen,prefixlenपूर्ण against sa_family.  */
अटल पूर्णांक verअगरy_address_len(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा sadb_address *sp = p;
	स्थिर काष्ठा sockaddr *addr = (स्थिर काष्ठा sockaddr *)(sp + 1);
	स्थिर काष्ठा sockaddr_in *sin;
#अगर IS_ENABLED(CONFIG_IPV6)
	स्थिर काष्ठा sockaddr_in6 *sin6;
#पूर्ण_अगर
	पूर्णांक len;

	अगर (sp->sadb_address_len <
	    DIV_ROUND_UP(माप(*sp) + दुरत्वend(typeof(*addr), sa_family),
			 माप(uपूर्णांक64_t)))
		वापस -EINVAL;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		len = DIV_ROUND_UP(माप(*sp) + माप(*sin), माप(uपूर्णांक64_t));
		अगर (sp->sadb_address_len != len ||
		    sp->sadb_address_prefixlen > 32)
			वापस -EINVAL;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		len = DIV_ROUND_UP(माप(*sp) + माप(*sin6), माप(uपूर्णांक64_t));
		अगर (sp->sadb_address_len != len ||
		    sp->sadb_address_prefixlen > 128)
			वापस -EINVAL;
		अवरोध;
#पूर्ण_अगर
	शेष:
		/* It is user using kernel to keep track of security
		 * associations क्रम another protocol, such as
		 * OSPF/RSVP/RIPV2/MIP.  It is user's job to verअगरy
		 * lengths.
		 *
		 * XXX Actually, association/policy database is not yet
		 * XXX able to cope with arbitrary sockaddr families.
		 * XXX When it can, हटाओ this -EINVAL.  -DaveM
		 */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sadb_key_len(स्थिर काष्ठा sadb_key *key)
अणु
	पूर्णांक key_bytes = DIV_ROUND_UP(key->sadb_key_bits, 8);

	वापस DIV_ROUND_UP(माप(काष्ठा sadb_key) + key_bytes,
			    माप(uपूर्णांक64_t));
पूर्ण

अटल पूर्णांक verअगरy_key_len(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा sadb_key *key = p;

	अगर (sadb_key_len(key) > key->sadb_key_len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pfkey_sec_ctx_len(स्थिर काष्ठा sadb_x_sec_ctx *sec_ctx)
अणु
	वापस DIV_ROUND_UP(माप(काष्ठा sadb_x_sec_ctx) +
			    sec_ctx->sadb_x_ctx_len,
			    माप(uपूर्णांक64_t));
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_sec_ctx_len(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा sadb_x_sec_ctx *sec_ctx = p;
	पूर्णांक len = sec_ctx->sadb_x_ctx_len;

	अगर (len > PAGE_SIZE)
		वापस -EINVAL;

	len = pfkey_sec_ctx_len(sec_ctx);

	अगर (sec_ctx->sadb_x_sec_len != len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा xfrm_user_sec_ctx *pfkey_sadb2xfrm_user_sec_ctx(स्थिर काष्ठा sadb_x_sec_ctx *sec_ctx,
								     gfp_t gfp)
अणु
	काष्ठा xfrm_user_sec_ctx *uctx = शून्य;
	पूर्णांक ctx_size = sec_ctx->sadb_x_ctx_len;

	uctx = kदो_स्मृति((माप(*uctx)+ctx_size), gfp);

	अगर (!uctx)
		वापस शून्य;

	uctx->len = pfkey_sec_ctx_len(sec_ctx);
	uctx->exttype = sec_ctx->sadb_x_sec_exttype;
	uctx->ctx_करोi = sec_ctx->sadb_x_ctx_करोi;
	uctx->ctx_alg = sec_ctx->sadb_x_ctx_alg;
	uctx->ctx_len = sec_ctx->sadb_x_ctx_len;
	स_नकल(uctx + 1, sec_ctx + 1,
	       uctx->ctx_len);

	वापस uctx;
पूर्ण

अटल पूर्णांक present_and_same_family(स्थिर काष्ठा sadb_address *src,
				   स्थिर काष्ठा sadb_address *dst)
अणु
	स्थिर काष्ठा sockaddr *s_addr, *d_addr;

	अगर (!src || !dst)
		वापस 0;

	s_addr = (स्थिर काष्ठा sockaddr *)(src + 1);
	d_addr = (स्थिर काष्ठा sockaddr *)(dst + 1);
	अगर (s_addr->sa_family != d_addr->sa_family)
		वापस 0;
	अगर (s_addr->sa_family != AF_INET
#अगर IS_ENABLED(CONFIG_IPV6)
	    && s_addr->sa_family != AF_INET6
#पूर्ण_अगर
		)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक parse_exthdrs(काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम **ext_hdrs)
अणु
	स्थिर अक्षर *p = (अक्षर *) hdr;
	पूर्णांक len = skb->len;

	len -= माप(*hdr);
	p += माप(*hdr);
	जबतक (len > 0) अणु
		स्थिर काष्ठा sadb_ext *ehdr = (स्थिर काष्ठा sadb_ext *) p;
		uपूर्णांक16_t ext_type;
		पूर्णांक ext_len;

		अगर (len < माप(*ehdr))
			वापस -EINVAL;

		ext_len  = ehdr->sadb_ext_len;
		ext_len *= माप(uपूर्णांक64_t);
		ext_type = ehdr->sadb_ext_type;
		अगर (ext_len < माप(uपूर्णांक64_t) ||
		    ext_len > len ||
		    ext_type == SADB_EXT_RESERVED)
			वापस -EINVAL;

		अगर (ext_type <= SADB_EXT_MAX) अणु
			पूर्णांक min = (पूर्णांक) sadb_ext_min_len[ext_type];
			अगर (ext_len < min)
				वापस -EINVAL;
			अगर (ext_hdrs[ext_type-1] != शून्य)
				वापस -EINVAL;
			चयन (ext_type) अणु
			हाल SADB_EXT_ADDRESS_SRC:
			हाल SADB_EXT_ADDRESS_DST:
			हाल SADB_EXT_ADDRESS_PROXY:
			हाल SADB_X_EXT_NAT_T_OA:
				अगर (verअगरy_address_len(p))
					वापस -EINVAL;
				अवरोध;
			हाल SADB_X_EXT_SEC_CTX:
				अगर (verअगरy_sec_ctx_len(p))
					वापस -EINVAL;
				अवरोध;
			हाल SADB_EXT_KEY_AUTH:
			हाल SADB_EXT_KEY_ENCRYPT:
				अगर (verअगरy_key_len(p))
					वापस -EINVAL;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			ext_hdrs[ext_type-1] = (व्योम *) p;
		पूर्ण
		p   += ext_len;
		len -= ext_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t
pfkey_satype2proto(uपूर्णांक8_t satype)
अणु
	चयन (satype) अणु
	हाल SADB_SATYPE_UNSPEC:
		वापस IPSEC_PROTO_ANY;
	हाल SADB_SATYPE_AH:
		वापस IPPROTO_AH;
	हाल SADB_SATYPE_ESP:
		वापस IPPROTO_ESP;
	हाल SADB_X_SATYPE_IPCOMP:
		वापस IPPROTO_COMP;
	शेष:
		वापस 0;
	पूर्ण
	/* NOTREACHED */
पूर्ण

अटल uपूर्णांक8_t
pfkey_proto2satype(uपूर्णांक16_t proto)
अणु
	चयन (proto) अणु
	हाल IPPROTO_AH:
		वापस SADB_SATYPE_AH;
	हाल IPPROTO_ESP:
		वापस SADB_SATYPE_ESP;
	हाल IPPROTO_COMP:
		वापस SADB_X_SATYPE_IPCOMP;
	शेष:
		वापस 0;
	पूर्ण
	/* NOTREACHED */
पूर्ण

/* BTW, this scheme means that there is no way with PFKEY2 sockets to
 * say specअगरically 'just raw sockets' as we encode them as 255.
 */

अटल uपूर्णांक8_t pfkey_proto_to_xfrm(uपूर्णांक8_t proto)
अणु
	वापस proto == IPSEC_PROTO_ANY ? 0 : proto;
पूर्ण

अटल uपूर्णांक8_t pfkey_proto_from_xfrm(uपूर्णांक8_t proto)
अणु
	वापस proto ? proto : IPSEC_PROTO_ANY;
पूर्ण

अटल अंतरभूत पूर्णांक pfkey_sockaddr_len(sa_family_t family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस माप(काष्ठा sockaddr_in);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		वापस माप(काष्ठा sockaddr_in6);
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक pfkey_sockaddr_extract(स्थिर काष्ठा sockaddr *sa, xfrm_address_t *xaddr)
अणु
	चयन (sa->sa_family) अणु
	हाल AF_INET:
		xaddr->a4 =
			((काष्ठा sockaddr_in *)sa)->sin_addr.s_addr;
		वापस AF_INET;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		स_नकल(xaddr->a6,
		       &((काष्ठा sockaddr_in6 *)sa)->sin6_addr,
		       माप(काष्ठा in6_addr));
		वापस AF_INET6;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक pfkey_sadb_addr2xfrm_addr(स्थिर काष्ठा sadb_address *addr, xfrm_address_t *xaddr)
अणु
	वापस pfkey_sockaddr_extract((काष्ठा sockaddr *)(addr + 1),
				      xaddr);
पूर्ण

अटल काष्ठा  xfrm_state *pfkey_xfrm_state_lookup(काष्ठा net *net, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	स्थिर काष्ठा sadb_sa *sa;
	स्थिर काष्ठा sadb_address *addr;
	uपूर्णांक16_t proto;
	अचिन्हित लघु family;
	xfrm_address_t *xaddr;

	sa = ext_hdrs[SADB_EXT_SA - 1];
	अगर (sa == शून्य)
		वापस शून्य;

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	अगर (proto == 0)
		वापस शून्य;

	/* sadb_address_len should be checked by caller */
	addr = ext_hdrs[SADB_EXT_ADDRESS_DST - 1];
	अगर (addr == शून्य)
		वापस शून्य;

	family = ((स्थिर काष्ठा sockaddr *)(addr + 1))->sa_family;
	चयन (family) अणु
	हाल AF_INET:
		xaddr = (xfrm_address_t *)&((स्थिर काष्ठा sockaddr_in *)(addr + 1))->sin_addr;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		xaddr = (xfrm_address_t *)&((स्थिर काष्ठा sockaddr_in6 *)(addr + 1))->sin6_addr;
		अवरोध;
#पूर्ण_अगर
	शेष:
		xaddr = शून्य;
	पूर्ण

	अगर (!xaddr)
		वापस शून्य;

	वापस xfrm_state_lookup(net, DUMMY_MARK, xaddr, sa->sadb_sa_spi, proto, family);
पूर्ण

#घोषणा PFKEY_ALIGN8(a) (1 + (((a) - 1) | (8 - 1)))

अटल पूर्णांक
pfkey_sockaddr_size(sa_family_t family)
अणु
	वापस PFKEY_ALIGN8(pfkey_sockaddr_len(family));
पूर्ण

अटल अंतरभूत पूर्णांक pfkey_mode_from_xfrm(पूर्णांक mode)
अणु
	चयन(mode) अणु
	हाल XFRM_MODE_TRANSPORT:
		वापस IPSEC_MODE_TRANSPORT;
	हाल XFRM_MODE_TUNNEL:
		वापस IPSEC_MODE_TUNNEL;
	हाल XFRM_MODE_BEET:
		वापस IPSEC_MODE_BEET;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक pfkey_mode_to_xfrm(पूर्णांक mode)
अणु
	चयन(mode) अणु
	हाल IPSEC_MODE_ANY:	/*XXX*/
	हाल IPSEC_MODE_TRANSPORT:
		वापस XFRM_MODE_TRANSPORT;
	हाल IPSEC_MODE_TUNNEL:
		वापस XFRM_MODE_TUNNEL;
	हाल IPSEC_MODE_BEET:
		वापस XFRM_MODE_BEET;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक pfkey_sockaddr_fill(स्थिर xfrm_address_t *xaddr, __be16 port,
					काष्ठा sockaddr *sa,
					अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल AF_INET:
	    अणु
		काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sa;
		sin->sin_family = AF_INET;
		sin->sin_port = port;
		sin->sin_addr.s_addr = xaddr->a4;
		स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
		वापस 32;
	    पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
	    अणु
		काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sa;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_port = port;
		sin6->sin6_flowinfo = 0;
		sin6->sin6_addr = xaddr->in6;
		sin6->sin6_scope_id = 0;
		वापस 128;
	    पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *__pfkey_xfrm_state2msg(स्थिर काष्ठा xfrm_state *x,
					      पूर्णांक add_keys, पूर्णांक hsc)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;
	काष्ठा sadb_sa *sa;
	काष्ठा sadb_lअगरeसमय *lअगरeसमय;
	काष्ठा sadb_address *addr;
	काष्ठा sadb_key *key;
	काष्ठा sadb_x_sa2 *sa2;
	काष्ठा sadb_x_sec_ctx *sec_ctx;
	काष्ठा xfrm_sec_ctx *xfrm_ctx;
	पूर्णांक ctx_size = 0;
	पूर्णांक size;
	पूर्णांक auth_key_size = 0;
	पूर्णांक encrypt_key_size = 0;
	पूर्णांक sockaddr_size;
	काष्ठा xfrm_encap_पंचांगpl *natt = शून्य;
	पूर्णांक mode;

	/* address family check */
	sockaddr_size = pfkey_sockaddr_size(x->props.family);
	अगर (!sockaddr_size)
		वापस ERR_PTR(-EINVAL);

	/* base, SA, (lअगरeसमय (HSC),) address(SD), (address(P),)
	   key(AE), (identity(SD),) (sensitivity)> */
	size = माप(काष्ठा sadb_msg) +माप(काष्ठा sadb_sa) +
		माप(काष्ठा sadb_lअगरeसमय) +
		((hsc & 1) ? माप(काष्ठा sadb_lअगरeसमय) : 0) +
		((hsc & 2) ? माप(काष्ठा sadb_lअगरeसमय) : 0) +
			माप(काष्ठा sadb_address)*2 +
				sockaddr_size*2 +
					माप(काष्ठा sadb_x_sa2);

	अगर ((xfrm_ctx = x->security)) अणु
		ctx_size = PFKEY_ALIGN8(xfrm_ctx->ctx_len);
		size += माप(काष्ठा sadb_x_sec_ctx) + ctx_size;
	पूर्ण

	/* identity & sensitivity */
	अगर (!xfrm_addr_equal(&x->sel.saddr, &x->props.saddr, x->props.family))
		size += माप(काष्ठा sadb_address) + sockaddr_size;

	अगर (add_keys) अणु
		अगर (x->aalg && x->aalg->alg_key_len) अणु
			auth_key_size =
				PFKEY_ALIGN8((x->aalg->alg_key_len + 7) / 8);
			size += माप(काष्ठा sadb_key) + auth_key_size;
		पूर्ण
		अगर (x->ealg && x->ealg->alg_key_len) अणु
			encrypt_key_size =
				PFKEY_ALIGN8((x->ealg->alg_key_len+7) / 8);
			size += माप(काष्ठा sadb_key) + encrypt_key_size;
		पूर्ण
	पूर्ण
	अगर (x->encap)
		natt = x->encap;

	अगर (natt && natt->encap_type) अणु
		size += माप(काष्ठा sadb_x_nat_t_type);
		size += माप(काष्ठा sadb_x_nat_t_port);
		size += माप(काष्ठा sadb_x_nat_t_port);
	पूर्ण

	skb =  alloc_skb(size + 16, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस ERR_PTR(-ENOBUFS);

	/* call should fill header later */
	hdr = skb_put(skb, माप(काष्ठा sadb_msg));
	स_रखो(hdr, 0, size);	/* XXX करो we need this ? */
	hdr->sadb_msg_len = size / माप(uपूर्णांक64_t);

	/* sa */
	sa = skb_put(skb, माप(काष्ठा sadb_sa));
	sa->sadb_sa_len = माप(काष्ठा sadb_sa)/माप(uपूर्णांक64_t);
	sa->sadb_sa_exttype = SADB_EXT_SA;
	sa->sadb_sa_spi = x->id.spi;
	sa->sadb_sa_replay = x->props.replay_winकरोw;
	चयन (x->km.state) अणु
	हाल XFRM_STATE_VALID:
		sa->sadb_sa_state = x->km.dying ?
			SADB_SASTATE_DYING : SADB_SASTATE_MATURE;
		अवरोध;
	हाल XFRM_STATE_ACQ:
		sa->sadb_sa_state = SADB_SASTATE_LARVAL;
		अवरोध;
	शेष:
		sa->sadb_sa_state = SADB_SASTATE_DEAD;
		अवरोध;
	पूर्ण
	sa->sadb_sa_auth = 0;
	अगर (x->aalg) अणु
		काष्ठा xfrm_algo_desc *a = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
		sa->sadb_sa_auth = (a && a->pfkey_supported) ?
					a->desc.sadb_alg_id : 0;
	पूर्ण
	sa->sadb_sa_encrypt = 0;
	BUG_ON(x->ealg && x->calg);
	अगर (x->ealg) अणु
		काष्ठा xfrm_algo_desc *a = xfrm_ealg_get_byname(x->ealg->alg_name, 0);
		sa->sadb_sa_encrypt = (a && a->pfkey_supported) ?
					a->desc.sadb_alg_id : 0;
	पूर्ण
	/* KAME compatible: sadb_sa_encrypt is overloaded with calg id */
	अगर (x->calg) अणु
		काष्ठा xfrm_algo_desc *a = xfrm_calg_get_byname(x->calg->alg_name, 0);
		sa->sadb_sa_encrypt = (a && a->pfkey_supported) ?
					a->desc.sadb_alg_id : 0;
	पूर्ण

	sa->sadb_sa_flags = 0;
	अगर (x->props.flags & XFRM_STATE_NOECN)
		sa->sadb_sa_flags |= SADB_SAFLAGS_NOECN;
	अगर (x->props.flags & XFRM_STATE_DECAP_DSCP)
		sa->sadb_sa_flags |= SADB_SAFLAGS_DECAP_DSCP;
	अगर (x->props.flags & XFRM_STATE_NOPMTUDISC)
		sa->sadb_sa_flags |= SADB_SAFLAGS_NOPMTUDISC;

	/* hard समय */
	अगर (hsc & 2) अणु
		lअगरeसमय = skb_put(skb, माप(काष्ठा sadb_lअगरeसमय));
		lअगरeसमय->sadb_lअगरeसमय_len =
			माप(काष्ठा sadb_lअगरeसमय)/माप(uपूर्णांक64_t);
		lअगरeसमय->sadb_lअगरeसमय_exttype = SADB_EXT_LIFETIME_HARD;
		lअगरeसमय->sadb_lअगरeसमय_allocations =  _X2KEY(x->lft.hard_packet_limit);
		lअगरeसमय->sadb_lअगरeसमय_bytes = _X2KEY(x->lft.hard_byte_limit);
		lअगरeसमय->sadb_lअगरeसमय_addसमय = x->lft.hard_add_expires_seconds;
		lअगरeसमय->sadb_lअगरeसमय_useसमय = x->lft.hard_use_expires_seconds;
	पूर्ण
	/* soft समय */
	अगर (hsc & 1) अणु
		lअगरeसमय = skb_put(skb, माप(काष्ठा sadb_lअगरeसमय));
		lअगरeसमय->sadb_lअगरeसमय_len =
			माप(काष्ठा sadb_lअगरeसमय)/माप(uपूर्णांक64_t);
		lअगरeसमय->sadb_lअगरeसमय_exttype = SADB_EXT_LIFETIME_SOFT;
		lअगरeसमय->sadb_lअगरeसमय_allocations =  _X2KEY(x->lft.soft_packet_limit);
		lअगरeसमय->sadb_lअगरeसमय_bytes = _X2KEY(x->lft.soft_byte_limit);
		lअगरeसमय->sadb_lअगरeसमय_addसमय = x->lft.soft_add_expires_seconds;
		lअगरeसमय->sadb_lअगरeसमय_useसमय = x->lft.soft_use_expires_seconds;
	पूर्ण
	/* current समय */
	lअगरeसमय = skb_put(skb, माप(काष्ठा sadb_lअगरeसमय));
	lअगरeसमय->sadb_lअगरeसमय_len =
		माप(काष्ठा sadb_lअगरeसमय)/माप(uपूर्णांक64_t);
	lअगरeसमय->sadb_lअगरeसमय_exttype = SADB_EXT_LIFETIME_CURRENT;
	lअगरeसमय->sadb_lअगरeसमय_allocations = x->curlft.packets;
	lअगरeसमय->sadb_lअगरeसमय_bytes = x->curlft.bytes;
	lअगरeसमय->sadb_lअगरeसमय_addसमय = x->curlft.add_समय;
	lअगरeसमय->sadb_lअगरeसमय_useसमय = x->curlft.use_समय;
	/* src address */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_SRC;
	/* "अगर the ports are non-zero, then the sadb_address_proto field,
	   normally zero, MUST be filled in with the transport
	   protocol's number." - RFC2367 */
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;

	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->props.saddr, 0,
				    (काष्ठा sockaddr *) (addr + 1),
				    x->props.family);
	BUG_ON(!addr->sadb_address_prefixlen);

	/* dst address */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_DST;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;

	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->id.daddr, 0,
				    (काष्ठा sockaddr *) (addr + 1),
				    x->props.family);
	BUG_ON(!addr->sadb_address_prefixlen);

	अगर (!xfrm_addr_equal(&x->sel.saddr, &x->props.saddr,
			     x->props.family)) अणु
		addr = skb_put(skb,
			       माप(काष्ठा sadb_address) + sockaddr_size);
		addr->sadb_address_len =
			(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
		addr->sadb_address_exttype = SADB_EXT_ADDRESS_PROXY;
		addr->sadb_address_proto =
			pfkey_proto_from_xfrm(x->sel.proto);
		addr->sadb_address_prefixlen = x->sel.prefixlen_s;
		addr->sadb_address_reserved = 0;

		pfkey_sockaddr_fill(&x->sel.saddr, x->sel.sport,
				    (काष्ठा sockaddr *) (addr + 1),
				    x->props.family);
	पूर्ण

	/* auth key */
	अगर (add_keys && auth_key_size) अणु
		key = skb_put(skb, माप(काष्ठा sadb_key) + auth_key_size);
		key->sadb_key_len = (माप(काष्ठा sadb_key) + auth_key_size) /
			माप(uपूर्णांक64_t);
		key->sadb_key_exttype = SADB_EXT_KEY_AUTH;
		key->sadb_key_bits = x->aalg->alg_key_len;
		key->sadb_key_reserved = 0;
		स_नकल(key + 1, x->aalg->alg_key, (x->aalg->alg_key_len+7)/8);
	पूर्ण
	/* encrypt key */
	अगर (add_keys && encrypt_key_size) अणु
		key = skb_put(skb, माप(काष्ठा sadb_key) + encrypt_key_size);
		key->sadb_key_len = (माप(काष्ठा sadb_key) +
				     encrypt_key_size) / माप(uपूर्णांक64_t);
		key->sadb_key_exttype = SADB_EXT_KEY_ENCRYPT;
		key->sadb_key_bits = x->ealg->alg_key_len;
		key->sadb_key_reserved = 0;
		स_नकल(key + 1, x->ealg->alg_key,
		       (x->ealg->alg_key_len+7)/8);
	पूर्ण

	/* sa */
	sa2 = skb_put(skb, माप(काष्ठा sadb_x_sa2));
	sa2->sadb_x_sa2_len = माप(काष्ठा sadb_x_sa2)/माप(uपूर्णांक64_t);
	sa2->sadb_x_sa2_exttype = SADB_X_EXT_SA2;
	अगर ((mode = pfkey_mode_from_xfrm(x->props.mode)) < 0) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	sa2->sadb_x_sa2_mode = mode;
	sa2->sadb_x_sa2_reserved1 = 0;
	sa2->sadb_x_sa2_reserved2 = 0;
	sa2->sadb_x_sa2_sequence = 0;
	sa2->sadb_x_sa2_reqid = x->props.reqid;

	अगर (natt && natt->encap_type) अणु
		काष्ठा sadb_x_nat_t_type *n_type;
		काष्ठा sadb_x_nat_t_port *n_port;

		/* type */
		n_type = skb_put(skb, माप(*n_type));
		n_type->sadb_x_nat_t_type_len = माप(*n_type)/माप(uपूर्णांक64_t);
		n_type->sadb_x_nat_t_type_exttype = SADB_X_EXT_NAT_T_TYPE;
		n_type->sadb_x_nat_t_type_type = natt->encap_type;
		n_type->sadb_x_nat_t_type_reserved[0] = 0;
		n_type->sadb_x_nat_t_type_reserved[1] = 0;
		n_type->sadb_x_nat_t_type_reserved[2] = 0;

		/* source port */
		n_port = skb_put(skb, माप(*n_port));
		n_port->sadb_x_nat_t_port_len = माप(*n_port)/माप(uपूर्णांक64_t);
		n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_SPORT;
		n_port->sadb_x_nat_t_port_port = natt->encap_sport;
		n_port->sadb_x_nat_t_port_reserved = 0;

		/* dest port */
		n_port = skb_put(skb, माप(*n_port));
		n_port->sadb_x_nat_t_port_len = माप(*n_port)/माप(uपूर्णांक64_t);
		n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_DPORT;
		n_port->sadb_x_nat_t_port_port = natt->encap_dport;
		n_port->sadb_x_nat_t_port_reserved = 0;
	पूर्ण

	/* security context */
	अगर (xfrm_ctx) अणु
		sec_ctx = skb_put(skb,
				  माप(काष्ठा sadb_x_sec_ctx) + ctx_size);
		sec_ctx->sadb_x_sec_len =
		  (माप(काष्ठा sadb_x_sec_ctx) + ctx_size) / माप(uपूर्णांक64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_करोi = xfrm_ctx->ctx_करोi;
		sec_ctx->sadb_x_ctx_alg = xfrm_ctx->ctx_alg;
		sec_ctx->sadb_x_ctx_len = xfrm_ctx->ctx_len;
		स_नकल(sec_ctx + 1, xfrm_ctx->ctx_str,
		       xfrm_ctx->ctx_len);
	पूर्ण

	वापस skb;
पूर्ण


अटल अंतरभूत काष्ठा sk_buff *pfkey_xfrm_state2msg(स्थिर काष्ठा xfrm_state *x)
अणु
	काष्ठा sk_buff *skb;

	skb = __pfkey_xfrm_state2msg(x, 1, 3);

	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *pfkey_xfrm_state2msg_expire(स्थिर काष्ठा xfrm_state *x,
							  पूर्णांक hsc)
अणु
	वापस __pfkey_xfrm_state2msg(x, 0, hsc);
पूर्ण

अटल काष्ठा xfrm_state * pfkey_msg2xfrm_state(काष्ठा net *net,
						स्थिर काष्ठा sadb_msg *hdr,
						व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा xfrm_state *x;
	स्थिर काष्ठा sadb_lअगरeसमय *lअगरeसमय;
	स्थिर काष्ठा sadb_sa *sa;
	स्थिर काष्ठा sadb_key *key;
	स्थिर काष्ठा sadb_x_sec_ctx *sec_ctx;
	uपूर्णांक16_t proto;
	पूर्णांक err;


	sa = ext_hdrs[SADB_EXT_SA - 1];
	अगर (!sa ||
	    !present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST-1]))
		वापस ERR_PTR(-EINVAL);
	अगर (hdr->sadb_msg_satype == SADB_SATYPE_ESP &&
	    !ext_hdrs[SADB_EXT_KEY_ENCRYPT-1])
		वापस ERR_PTR(-EINVAL);
	अगर (hdr->sadb_msg_satype == SADB_SATYPE_AH &&
	    !ext_hdrs[SADB_EXT_KEY_AUTH-1])
		वापस ERR_PTR(-EINVAL);
	अगर (!!ext_hdrs[SADB_EXT_LIFETIME_HARD-1] !=
	    !!ext_hdrs[SADB_EXT_LIFETIME_SOFT-1])
		वापस ERR_PTR(-EINVAL);

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	अगर (proto == 0)
		वापस ERR_PTR(-EINVAL);

	/* शेष error is no buffer space */
	err = -ENOBUFS;

	/* RFC2367:

   Only SADB_SASTATE_MATURE SAs may be submitted in an SADB_ADD message.
   SADB_SASTATE_LARVAL SAs are created by SADB_GETSPI and it is not
   sensible to add a new SA in the DYING or SADB_SASTATE_DEAD state.
   Thereक्रमe, the sadb_sa_state field of all submitted SAs MUST be
   SADB_SASTATE_MATURE and the kernel MUST वापस an error अगर this is
   not true.

	   However, KAME setkey always uses SADB_SASTATE_LARVAL.
	   Hence, we have to _ignore_ sadb_sa_state, which is also reasonable.
	 */
	अगर (sa->sadb_sa_auth > SADB_AALG_MAX ||
	    (hdr->sadb_msg_satype == SADB_X_SATYPE_IPCOMP &&
	     sa->sadb_sa_encrypt > SADB_X_CALG_MAX) ||
	    sa->sadb_sa_encrypt > SADB_EALG_MAX)
		वापस ERR_PTR(-EINVAL);
	key = ext_hdrs[SADB_EXT_KEY_AUTH - 1];
	अगर (key != शून्य &&
	    sa->sadb_sa_auth != SADB_X_AALG_शून्य &&
	    key->sadb_key_bits == 0)
		वापस ERR_PTR(-EINVAL);
	key = ext_hdrs[SADB_EXT_KEY_ENCRYPT-1];
	अगर (key != शून्य &&
	    sa->sadb_sa_encrypt != SADB_EALG_शून्य &&
	    key->sadb_key_bits == 0)
		वापस ERR_PTR(-EINVAL);

	x = xfrm_state_alloc(net);
	अगर (x == शून्य)
		वापस ERR_PTR(-ENOBUFS);

	x->id.proto = proto;
	x->id.spi = sa->sadb_sa_spi;
	x->props.replay_winकरोw = min_t(अचिन्हित पूर्णांक, sa->sadb_sa_replay,
					(माप(x->replay.biपंचांगap) * 8));
	अगर (sa->sadb_sa_flags & SADB_SAFLAGS_NOECN)
		x->props.flags |= XFRM_STATE_NOECN;
	अगर (sa->sadb_sa_flags & SADB_SAFLAGS_DECAP_DSCP)
		x->props.flags |= XFRM_STATE_DECAP_DSCP;
	अगर (sa->sadb_sa_flags & SADB_SAFLAGS_NOPMTUDISC)
		x->props.flags |= XFRM_STATE_NOPMTUDISC;

	lअगरeसमय = ext_hdrs[SADB_EXT_LIFETIME_HARD - 1];
	अगर (lअगरeसमय != शून्य) अणु
		x->lft.hard_packet_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_allocations);
		x->lft.hard_byte_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_bytes);
		x->lft.hard_add_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_addसमय;
		x->lft.hard_use_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_useसमय;
	पूर्ण
	lअगरeसमय = ext_hdrs[SADB_EXT_LIFETIME_SOFT - 1];
	अगर (lअगरeसमय != शून्य) अणु
		x->lft.soft_packet_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_allocations);
		x->lft.soft_byte_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_bytes);
		x->lft.soft_add_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_addसमय;
		x->lft.soft_use_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_useसमय;
	पूर्ण

	sec_ctx = ext_hdrs[SADB_X_EXT_SEC_CTX - 1];
	अगर (sec_ctx != शून्य) अणु
		काष्ठा xfrm_user_sec_ctx *uctx = pfkey_sadb2xfrm_user_sec_ctx(sec_ctx, GFP_KERNEL);

		अगर (!uctx)
			जाओ out;

		err = security_xfrm_state_alloc(x, uctx);
		kमुक्त(uctx);

		अगर (err)
			जाओ out;
	पूर्ण

	err = -ENOBUFS;
	key = ext_hdrs[SADB_EXT_KEY_AUTH - 1];
	अगर (sa->sadb_sa_auth) अणु
		पूर्णांक keysize = 0;
		काष्ठा xfrm_algo_desc *a = xfrm_aalg_get_byid(sa->sadb_sa_auth);
		अगर (!a || !a->pfkey_supported) अणु
			err = -ENOSYS;
			जाओ out;
		पूर्ण
		अगर (key)
			keysize = (key->sadb_key_bits + 7) / 8;
		x->aalg = kदो_स्मृति(माप(*x->aalg) + keysize, GFP_KERNEL);
		अगर (!x->aalg) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		म_नकल(x->aalg->alg_name, a->name);
		x->aalg->alg_key_len = 0;
		अगर (key) अणु
			x->aalg->alg_key_len = key->sadb_key_bits;
			स_नकल(x->aalg->alg_key, key+1, keysize);
		पूर्ण
		x->aalg->alg_trunc_len = a->uinfo.auth.icv_truncbits;
		x->props.aalgo = sa->sadb_sa_auth;
		/* x->algo.flags = sa->sadb_sa_flags; */
	पूर्ण
	अगर (sa->sadb_sa_encrypt) अणु
		अगर (hdr->sadb_msg_satype == SADB_X_SATYPE_IPCOMP) अणु
			काष्ठा xfrm_algo_desc *a = xfrm_calg_get_byid(sa->sadb_sa_encrypt);
			अगर (!a || !a->pfkey_supported) अणु
				err = -ENOSYS;
				जाओ out;
			पूर्ण
			x->calg = kदो_स्मृति(माप(*x->calg), GFP_KERNEL);
			अगर (!x->calg) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण
			म_नकल(x->calg->alg_name, a->name);
			x->props.calgo = sa->sadb_sa_encrypt;
		पूर्ण अन्यथा अणु
			पूर्णांक keysize = 0;
			काष्ठा xfrm_algo_desc *a = xfrm_ealg_get_byid(sa->sadb_sa_encrypt);
			अगर (!a || !a->pfkey_supported) अणु
				err = -ENOSYS;
				जाओ out;
			पूर्ण
			key = (काष्ठा sadb_key*) ext_hdrs[SADB_EXT_KEY_ENCRYPT-1];
			अगर (key)
				keysize = (key->sadb_key_bits + 7) / 8;
			x->ealg = kदो_स्मृति(माप(*x->ealg) + keysize, GFP_KERNEL);
			अगर (!x->ealg) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण
			म_नकल(x->ealg->alg_name, a->name);
			x->ealg->alg_key_len = 0;
			अगर (key) अणु
				x->ealg->alg_key_len = key->sadb_key_bits;
				स_नकल(x->ealg->alg_key, key+1, keysize);
			पूर्ण
			x->props.ealgo = sa->sadb_sa_encrypt;
			x->geniv = a->uinfo.encr.geniv;
		पूर्ण
	पूर्ण
	/* x->algo.flags = sa->sadb_sa_flags; */

	x->props.family = pfkey_sadb_addr2xfrm_addr((काष्ठा sadb_address *) ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
						    &x->props.saddr);
	pfkey_sadb_addr2xfrm_addr((काष्ठा sadb_address *) ext_hdrs[SADB_EXT_ADDRESS_DST-1],
				  &x->id.daddr);

	अगर (ext_hdrs[SADB_X_EXT_SA2-1]) अणु
		स्थिर काष्ठा sadb_x_sa2 *sa2 = ext_hdrs[SADB_X_EXT_SA2-1];
		पूर्णांक mode = pfkey_mode_to_xfrm(sa2->sadb_x_sa2_mode);
		अगर (mode < 0) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		x->props.mode = mode;
		x->props.reqid = sa2->sadb_x_sa2_reqid;
	पूर्ण

	अगर (ext_hdrs[SADB_EXT_ADDRESS_PROXY-1]) अणु
		स्थिर काष्ठा sadb_address *addr = ext_hdrs[SADB_EXT_ADDRESS_PROXY-1];

		/* Nobody uses this, but we try. */
		x->sel.family = pfkey_sadb_addr2xfrm_addr(addr, &x->sel.saddr);
		x->sel.prefixlen_s = addr->sadb_address_prefixlen;
	पूर्ण

	अगर (!x->sel.family)
		x->sel.family = x->props.family;

	अगर (ext_hdrs[SADB_X_EXT_NAT_T_TYPE-1]) अणु
		स्थिर काष्ठा sadb_x_nat_t_type* n_type;
		काष्ठा xfrm_encap_पंचांगpl *natt;

		x->encap = kदो_स्मृति(माप(*x->encap), GFP_KERNEL);
		अगर (!x->encap) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		natt = x->encap;
		n_type = ext_hdrs[SADB_X_EXT_NAT_T_TYPE-1];
		natt->encap_type = n_type->sadb_x_nat_t_type_type;

		अगर (ext_hdrs[SADB_X_EXT_NAT_T_SPORT-1]) अणु
			स्थिर काष्ठा sadb_x_nat_t_port *n_port =
				ext_hdrs[SADB_X_EXT_NAT_T_SPORT-1];
			natt->encap_sport = n_port->sadb_x_nat_t_port_port;
		पूर्ण
		अगर (ext_hdrs[SADB_X_EXT_NAT_T_DPORT-1]) अणु
			स्थिर काष्ठा sadb_x_nat_t_port *n_port =
				ext_hdrs[SADB_X_EXT_NAT_T_DPORT-1];
			natt->encap_dport = n_port->sadb_x_nat_t_port_port;
		पूर्ण
		स_रखो(&natt->encap_oa, 0, माप(natt->encap_oa));
	पूर्ण

	err = xfrm_init_state(x);
	अगर (err)
		जाओ out;

	x->km.seq = hdr->sadb_msg_seq;
	वापस x;

out:
	x->km.state = XFRM_STATE_DEAD;
	xfrm_state_put(x);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक pfkey_reserved(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pfkey_माला_लोpi(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा sk_buff *resp_skb;
	काष्ठा sadb_x_sa2 *sa2;
	काष्ठा sadb_address *saddr, *daddr;
	काष्ठा sadb_msg *out_hdr;
	काष्ठा sadb_spirange *range;
	काष्ठा xfrm_state *x = शून्य;
	पूर्णांक mode;
	पूर्णांक err;
	u32 min_spi, max_spi;
	u32 reqid;
	u8 proto;
	अचिन्हित लघु family;
	xfrm_address_t *xsaddr = शून्य, *xdaddr = शून्य;

	अगर (!present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST-1]))
		वापस -EINVAL;

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	अगर (proto == 0)
		वापस -EINVAL;

	अगर ((sa2 = ext_hdrs[SADB_X_EXT_SA2-1]) != शून्य) अणु
		mode = pfkey_mode_to_xfrm(sa2->sadb_x_sa2_mode);
		अगर (mode < 0)
			वापस -EINVAL;
		reqid = sa2->sadb_x_sa2_reqid;
	पूर्ण अन्यथा अणु
		mode = 0;
		reqid = 0;
	पूर्ण

	saddr = ext_hdrs[SADB_EXT_ADDRESS_SRC-1];
	daddr = ext_hdrs[SADB_EXT_ADDRESS_DST-1];

	family = ((काष्ठा sockaddr *)(saddr + 1))->sa_family;
	चयन (family) अणु
	हाल AF_INET:
		xdaddr = (xfrm_address_t *)&((काष्ठा sockaddr_in *)(daddr + 1))->sin_addr.s_addr;
		xsaddr = (xfrm_address_t *)&((काष्ठा sockaddr_in *)(saddr + 1))->sin_addr.s_addr;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		xdaddr = (xfrm_address_t *)&((काष्ठा sockaddr_in6 *)(daddr + 1))->sin6_addr;
		xsaddr = (xfrm_address_t *)&((काष्ठा sockaddr_in6 *)(saddr + 1))->sin6_addr;
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (hdr->sadb_msg_seq) अणु
		x = xfrm_find_acq_byseq(net, DUMMY_MARK, hdr->sadb_msg_seq);
		अगर (x && !xfrm_addr_equal(&x->id.daddr, xdaddr, family)) अणु
			xfrm_state_put(x);
			x = शून्य;
		पूर्ण
	पूर्ण

	अगर (!x)
		x = xfrm_find_acq(net, &dummy_mark, mode, reqid, 0, proto, xdaddr, xsaddr, 1, family);

	अगर (x == शून्य)
		वापस -ENOENT;

	min_spi = 0x100;
	max_spi = 0x0fffffff;

	range = ext_hdrs[SADB_EXT_SPIRANGE-1];
	अगर (range) अणु
		min_spi = range->sadb_spirange_min;
		max_spi = range->sadb_spirange_max;
	पूर्ण

	err = verअगरy_spi_info(x->id.proto, min_spi, max_spi);
	अगर (err) अणु
		xfrm_state_put(x);
		वापस err;
	पूर्ण

	err = xfrm_alloc_spi(x, min_spi, max_spi);
	resp_skb = err ? ERR_PTR(err) : pfkey_xfrm_state2msg(x);

	अगर (IS_ERR(resp_skb)) अणु
		xfrm_state_put(x);
		वापस  PTR_ERR(resp_skb);
	पूर्ण

	out_hdr = (काष्ठा sadb_msg *) resp_skb->data;
	out_hdr->sadb_msg_version = hdr->sadb_msg_version;
	out_hdr->sadb_msg_type = SADB_GETSPI;
	out_hdr->sadb_msg_satype = pfkey_proto2satype(proto);
	out_hdr->sadb_msg_त्रुटि_सं = 0;
	out_hdr->sadb_msg_reserved = 0;
	out_hdr->sadb_msg_seq = hdr->sadb_msg_seq;
	out_hdr->sadb_msg_pid = hdr->sadb_msg_pid;

	xfrm_state_put(x);

	pfkey_broadcast(resp_skb, GFP_KERNEL, BROADCAST_ONE, sk, net);

	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_acquire(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा xfrm_state *x;

	अगर (hdr->sadb_msg_len != माप(काष्ठा sadb_msg)/8)
		वापस -EOPNOTSUPP;

	अगर (hdr->sadb_msg_seq == 0 || hdr->sadb_msg_त्रुटि_सं == 0)
		वापस 0;

	x = xfrm_find_acq_byseq(net, DUMMY_MARK, hdr->sadb_msg_seq);
	अगर (x == शून्य)
		वापस 0;

	spin_lock_bh(&x->lock);
	अगर (x->km.state == XFRM_STATE_ACQ)
		x->km.state = XFRM_STATE_ERROR;

	spin_unlock_bh(&x->lock);
	xfrm_state_put(x);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक event2poltype(पूर्णांक event)
अणु
	चयन (event) अणु
	हाल XFRM_MSG_DELPOLICY:
		वापस SADB_X_SPDDELETE;
	हाल XFRM_MSG_NEWPOLICY:
		वापस SADB_X_SPDADD;
	हाल XFRM_MSG_UPDPOLICY:
		वापस SADB_X_SPDUPDATE;
	हाल XFRM_MSG_POLEXPIRE:
	//	वापस SADB_X_SPDEXPIRE;
	शेष:
		pr_err("pfkey: Unknown policy event %d\n", event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक event2keytype(पूर्णांक event)
अणु
	चयन (event) अणु
	हाल XFRM_MSG_DELSA:
		वापस SADB_DELETE;
	हाल XFRM_MSG_NEWSA:
		वापस SADB_ADD;
	हाल XFRM_MSG_UPDSA:
		वापस SADB_UPDATE;
	हाल XFRM_MSG_EXPIRE:
		वापस SADB_EXPIRE;
	शेष:
		pr_err("pfkey: Unknown SA event %d\n", event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* ADD/UPD/DEL */
अटल पूर्णांक key_notअगरy_sa(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;

	skb = pfkey_xfrm_state2msg(x);

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	hdr = (काष्ठा sadb_msg *) skb->data;
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_type = event2keytype(c->event);
	hdr->sadb_msg_satype = pfkey_proto2satype(x->id.proto);
	hdr->sadb_msg_त्रुटि_सं = 0;
	hdr->sadb_msg_reserved = 0;
	hdr->sadb_msg_seq = c->seq;
	hdr->sadb_msg_pid = c->portid;

	pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_ALL, शून्य, xs_net(x));

	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_add(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा xfrm_state *x;
	पूर्णांक err;
	काष्ठा km_event c;

	x = pfkey_msg2xfrm_state(net, hdr, ext_hdrs);
	अगर (IS_ERR(x))
		वापस PTR_ERR(x);

	xfrm_state_hold(x);
	अगर (hdr->sadb_msg_type == SADB_ADD)
		err = xfrm_state_add(x);
	अन्यथा
		err = xfrm_state_update(x);

	xfrm_audit_state_add(x, err ? 0 : 1, true);

	अगर (err < 0) अणु
		x->km.state = XFRM_STATE_DEAD;
		__xfrm_state_put(x);
		जाओ out;
	पूर्ण

	अगर (hdr->sadb_msg_type == SADB_ADD)
		c.event = XFRM_MSG_NEWSA;
	अन्यथा
		c.event = XFRM_MSG_UPDSA;
	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;
	km_state_notअगरy(x, &c);
out:
	xfrm_state_put(x);
	वापस err;
पूर्ण

अटल पूर्णांक pfkey_delete(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा xfrm_state *x;
	काष्ठा km_event c;
	पूर्णांक err;

	अगर (!ext_hdrs[SADB_EXT_SA-1] ||
	    !present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST-1]))
		वापस -EINVAL;

	x = pfkey_xfrm_state_lookup(net, hdr, ext_hdrs);
	अगर (x == शून्य)
		वापस -ESRCH;

	अगर ((err = security_xfrm_state_delete(x)))
		जाओ out;

	अगर (xfrm_state_kern(x)) अणु
		err = -EPERM;
		जाओ out;
	पूर्ण

	err = xfrm_state_delete(x);

	अगर (err < 0)
		जाओ out;

	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;
	c.event = XFRM_MSG_DELSA;
	km_state_notअगरy(x, &c);
out:
	xfrm_audit_state_delete(x, err ? 0 : 1, true);
	xfrm_state_put(x);

	वापस err;
पूर्ण

अटल पूर्णांक pfkey_get(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	__u8 proto;
	काष्ठा sk_buff *out_skb;
	काष्ठा sadb_msg *out_hdr;
	काष्ठा xfrm_state *x;

	अगर (!ext_hdrs[SADB_EXT_SA-1] ||
	    !present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST-1]))
		वापस -EINVAL;

	x = pfkey_xfrm_state_lookup(net, hdr, ext_hdrs);
	अगर (x == शून्य)
		वापस -ESRCH;

	out_skb = pfkey_xfrm_state2msg(x);
	proto = x->id.proto;
	xfrm_state_put(x);
	अगर (IS_ERR(out_skb))
		वापस  PTR_ERR(out_skb);

	out_hdr = (काष्ठा sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = hdr->sadb_msg_version;
	out_hdr->sadb_msg_type = SADB_GET;
	out_hdr->sadb_msg_satype = pfkey_proto2satype(proto);
	out_hdr->sadb_msg_त्रुटि_सं = 0;
	out_hdr->sadb_msg_reserved = 0;
	out_hdr->sadb_msg_seq = hdr->sadb_msg_seq;
	out_hdr->sadb_msg_pid = hdr->sadb_msg_pid;
	pfkey_broadcast(out_skb, GFP_ATOMIC, BROADCAST_ONE, sk, sock_net(sk));

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *compose_sadb_supported(स्थिर काष्ठा sadb_msg *orig,
					      gfp_t allocation)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;
	पूर्णांक len, auth_len, enc_len, i;

	auth_len = xfrm_count_pfkey_auth_supported();
	अगर (auth_len) अणु
		auth_len *= माप(काष्ठा sadb_alg);
		auth_len += माप(काष्ठा sadb_supported);
	पूर्ण

	enc_len = xfrm_count_pfkey_enc_supported();
	अगर (enc_len) अणु
		enc_len *= माप(काष्ठा sadb_alg);
		enc_len += माप(काष्ठा sadb_supported);
	पूर्ण

	len = enc_len + auth_len + माप(काष्ठा sadb_msg);

	skb = alloc_skb(len + 16, allocation);
	अगर (!skb)
		जाओ out_put_algs;

	hdr = skb_put(skb, माप(*hdr));
	pfkey_hdr_dup(hdr, orig);
	hdr->sadb_msg_त्रुटि_सं = 0;
	hdr->sadb_msg_len = len / माप(uपूर्णांक64_t);

	अगर (auth_len) अणु
		काष्ठा sadb_supported *sp;
		काष्ठा sadb_alg *ap;

		sp = skb_put(skb, auth_len);
		ap = (काष्ठा sadb_alg *) (sp + 1);

		sp->sadb_supported_len = auth_len / माप(uपूर्णांक64_t);
		sp->sadb_supported_exttype = SADB_EXT_SUPPORTED_AUTH;

		क्रम (i = 0; ; i++) अणु
			काष्ठा xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(i);
			अगर (!aalg)
				अवरोध;
			अगर (!aalg->pfkey_supported)
				जारी;
			अगर (aalg->available)
				*ap++ = aalg->desc;
		पूर्ण
	पूर्ण

	अगर (enc_len) अणु
		काष्ठा sadb_supported *sp;
		काष्ठा sadb_alg *ap;

		sp = skb_put(skb, enc_len);
		ap = (काष्ठा sadb_alg *) (sp + 1);

		sp->sadb_supported_len = enc_len / माप(uपूर्णांक64_t);
		sp->sadb_supported_exttype = SADB_EXT_SUPPORTED_ENCRYPT;

		क्रम (i = 0; ; i++) अणु
			काष्ठा xfrm_algo_desc *ealg = xfrm_ealg_get_byidx(i);
			अगर (!ealg)
				अवरोध;
			अगर (!ealg->pfkey_supported)
				जारी;
			अगर (ealg->available)
				*ap++ = ealg->desc;
		पूर्ण
	पूर्ण

out_put_algs:
	वापस skb;
पूर्ण

अटल पूर्णांक pfkey_रेजिस्टर(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा pfkey_sock *pfk = pfkey_sk(sk);
	काष्ठा sk_buff *supp_skb;

	अगर (hdr->sadb_msg_satype > SADB_SATYPE_MAX)
		वापस -EINVAL;

	अगर (hdr->sadb_msg_satype != SADB_SATYPE_UNSPEC) अणु
		अगर (pfk->रेजिस्टरed&(1<<hdr->sadb_msg_satype))
			वापस -EEXIST;
		pfk->रेजिस्टरed |= (1<<hdr->sadb_msg_satype);
	पूर्ण

	xfrm_probe_algs();

	supp_skb = compose_sadb_supported(hdr, GFP_KERNEL);
	अगर (!supp_skb) अणु
		अगर (hdr->sadb_msg_satype != SADB_SATYPE_UNSPEC)
			pfk->रेजिस्टरed &= ~(1<<hdr->sadb_msg_satype);

		वापस -ENOBUFS;
	पूर्ण

	pfkey_broadcast(supp_skb, GFP_KERNEL, BROADCAST_REGISTERED, sk,
			sock_net(sk));
	वापस 0;
पूर्ण

अटल पूर्णांक unicast_flush_resp(काष्ठा sock *sk, स्थिर काष्ठा sadb_msg *ihdr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;

	skb = alloc_skb(माप(काष्ठा sadb_msg) + 16, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOBUFS;

	hdr = skb_put_data(skb, ihdr, माप(काष्ठा sadb_msg));
	hdr->sadb_msg_त्रुटि_सं = (uपूर्णांक8_t) 0;
	hdr->sadb_msg_len = (माप(काष्ठा sadb_msg) / माप(uपूर्णांक64_t));

	वापस pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_ONE, sk,
			       sock_net(sk));
पूर्ण

अटल पूर्णांक key_notअगरy_sa_flush(स्थिर काष्ठा km_event *c)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;

	skb = alloc_skb(माप(काष्ठा sadb_msg) + 16, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOBUFS;
	hdr = skb_put(skb, माप(काष्ठा sadb_msg));
	hdr->sadb_msg_satype = pfkey_proto2satype(c->data.proto);
	hdr->sadb_msg_type = SADB_FLUSH;
	hdr->sadb_msg_seq = c->seq;
	hdr->sadb_msg_pid = c->portid;
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_त्रुटि_सं = (uपूर्णांक8_t) 0;
	hdr->sadb_msg_len = (माप(काष्ठा sadb_msg) / माप(uपूर्णांक64_t));
	hdr->sadb_msg_reserved = 0;

	pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_ALL, शून्य, c->net);

	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_flush(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	अचिन्हित पूर्णांक proto;
	काष्ठा km_event c;
	पूर्णांक err, err2;

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	अगर (proto == 0)
		वापस -EINVAL;

	err = xfrm_state_flush(net, proto, true, false);
	err2 = unicast_flush_resp(sk, hdr);
	अगर (err || err2) अणु
		अगर (err == -ESRCH) /* empty table - go quietly */
			err = 0;
		वापस err ? err : err2;
	पूर्ण

	c.data.proto = proto;
	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;
	c.event = XFRM_MSG_FLUSHSA;
	c.net = net;
	km_state_notअगरy(शून्य, &c);

	वापस 0;
पूर्ण

अटल पूर्णांक dump_sa(काष्ठा xfrm_state *x, पूर्णांक count, व्योम *ptr)
अणु
	काष्ठा pfkey_sock *pfk = ptr;
	काष्ठा sk_buff *out_skb;
	काष्ठा sadb_msg *out_hdr;

	अगर (!pfkey_can_dump(&pfk->sk))
		वापस -ENOBUFS;

	out_skb = pfkey_xfrm_state2msg(x);
	अगर (IS_ERR(out_skb))
		वापस PTR_ERR(out_skb);

	out_hdr = (काष्ठा sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = pfk->dump.msg_version;
	out_hdr->sadb_msg_type = SADB_DUMP;
	out_hdr->sadb_msg_satype = pfkey_proto2satype(x->id.proto);
	out_hdr->sadb_msg_त्रुटि_सं = 0;
	out_hdr->sadb_msg_reserved = 0;
	out_hdr->sadb_msg_seq = count + 1;
	out_hdr->sadb_msg_pid = pfk->dump.msg_portid;

	अगर (pfk->dump.skb)
		pfkey_broadcast(pfk->dump.skb, GFP_ATOMIC, BROADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
	pfk->dump.skb = out_skb;

	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_dump_sa(काष्ठा pfkey_sock *pfk)
अणु
	काष्ठा net *net = sock_net(&pfk->sk);
	वापस xfrm_state_walk(net, &pfk->dump.u.state, dump_sa, (व्योम *) pfk);
पूर्ण

अटल व्योम pfkey_dump_sa_करोne(काष्ठा pfkey_sock *pfk)
अणु
	काष्ठा net *net = sock_net(&pfk->sk);

	xfrm_state_walk_करोne(&pfk->dump.u.state, net);
पूर्ण

अटल पूर्णांक pfkey_dump(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	u8 proto;
	काष्ठा xfrm_address_filter *filter = शून्य;
	काष्ठा pfkey_sock *pfk = pfkey_sk(sk);

	mutex_lock(&pfk->dump_lock);
	अगर (pfk->dump.dump != शून्य) अणु
		mutex_unlock(&pfk->dump_lock);
		वापस -EBUSY;
	पूर्ण

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	अगर (proto == 0) अणु
		mutex_unlock(&pfk->dump_lock);
		वापस -EINVAL;
	पूर्ण

	अगर (ext_hdrs[SADB_X_EXT_FILTER - 1]) अणु
		काष्ठा sadb_x_filter *xfilter = ext_hdrs[SADB_X_EXT_FILTER - 1];

		अगर ((xfilter->sadb_x_filter_splen >=
			(माप(xfrm_address_t) << 3)) ||
		    (xfilter->sadb_x_filter_dplen >=
			(माप(xfrm_address_t) << 3))) अणु
			mutex_unlock(&pfk->dump_lock);
			वापस -EINVAL;
		पूर्ण
		filter = kदो_स्मृति(माप(*filter), GFP_KERNEL);
		अगर (filter == शून्य) अणु
			mutex_unlock(&pfk->dump_lock);
			वापस -ENOMEM;
		पूर्ण

		स_नकल(&filter->saddr, &xfilter->sadb_x_filter_saddr,
		       माप(xfrm_address_t));
		स_नकल(&filter->daddr, &xfilter->sadb_x_filter_daddr,
		       माप(xfrm_address_t));
		filter->family = xfilter->sadb_x_filter_family;
		filter->splen = xfilter->sadb_x_filter_splen;
		filter->dplen = xfilter->sadb_x_filter_dplen;
	पूर्ण

	pfk->dump.msg_version = hdr->sadb_msg_version;
	pfk->dump.msg_portid = hdr->sadb_msg_pid;
	pfk->dump.dump = pfkey_dump_sa;
	pfk->dump.करोne = pfkey_dump_sa_करोne;
	xfrm_state_walk_init(&pfk->dump.u.state, proto, filter);
	mutex_unlock(&pfk->dump_lock);

	वापस pfkey_करो_dump(pfk);
पूर्ण

अटल पूर्णांक pfkey_promisc(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा pfkey_sock *pfk = pfkey_sk(sk);
	पूर्णांक satype = hdr->sadb_msg_satype;
	bool reset_त्रुटि_सं = false;

	अगर (hdr->sadb_msg_len == (माप(*hdr) / माप(uपूर्णांक64_t))) अणु
		reset_त्रुटि_सं = true;
		अगर (satype != 0 && satype != 1)
			वापस -EINVAL;
		pfk->promisc = satype;
	पूर्ण
	अगर (reset_त्रुटि_सं && skb_cloned(skb))
		skb = skb_copy(skb, GFP_KERNEL);
	अन्यथा
		skb = skb_clone(skb, GFP_KERNEL);

	अगर (reset_त्रुटि_सं && skb) अणु
		काष्ठा sadb_msg *new_hdr = (काष्ठा sadb_msg *) skb->data;
		new_hdr->sadb_msg_त्रुटि_सं = 0;
	पूर्ण

	pfkey_broadcast(skb, GFP_KERNEL, BROADCAST_ALL, शून्य, sock_net(sk));
	वापस 0;
पूर्ण

अटल पूर्णांक check_reqid(काष्ठा xfrm_policy *xp, पूर्णांक dir, पूर्णांक count, व्योम *ptr)
अणु
	पूर्णांक i;
	u32 reqid = *(u32*)ptr;

	क्रम (i=0; i<xp->xfrm_nr; i++) अणु
		अगर (xp->xfrm_vec[i].reqid == reqid)
			वापस -EEXIST;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 gen_reqid(काष्ठा net *net)
अणु
	काष्ठा xfrm_policy_walk walk;
	u32 start;
	पूर्णांक rc;
	अटल u32 reqid = IPSEC_MANUAL_REQID_MAX;

	start = reqid;
	करो अणु
		++reqid;
		अगर (reqid == 0)
			reqid = IPSEC_MANUAL_REQID_MAX+1;
		xfrm_policy_walk_init(&walk, XFRM_POLICY_TYPE_MAIN);
		rc = xfrm_policy_walk(net, &walk, check_reqid, (व्योम*)&reqid);
		xfrm_policy_walk_करोne(&walk, net);
		अगर (rc != -EEXIST)
			वापस reqid;
	पूर्ण जबतक (reqid != start);
	वापस 0;
पूर्ण

अटल पूर्णांक
parse_ipsecrequest(काष्ठा xfrm_policy *xp, काष्ठा sadb_x_ipsecrequest *rq)
अणु
	काष्ठा net *net = xp_net(xp);
	काष्ठा xfrm_पंचांगpl *t = xp->xfrm_vec + xp->xfrm_nr;
	पूर्णांक mode;

	अगर (xp->xfrm_nr >= XFRM_MAX_DEPTH)
		वापस -ELOOP;

	अगर (rq->sadb_x_ipsecrequest_mode == 0)
		वापस -EINVAL;
	अगर (!xfrm_id_proto_valid(rq->sadb_x_ipsecrequest_proto))
		वापस -EINVAL;

	t->id.proto = rq->sadb_x_ipsecrequest_proto;
	अगर ((mode = pfkey_mode_to_xfrm(rq->sadb_x_ipsecrequest_mode)) < 0)
		वापस -EINVAL;
	t->mode = mode;
	अगर (rq->sadb_x_ipsecrequest_level == IPSEC_LEVEL_USE)
		t->optional = 1;
	अन्यथा अगर (rq->sadb_x_ipsecrequest_level == IPSEC_LEVEL_UNIQUE) अणु
		t->reqid = rq->sadb_x_ipsecrequest_reqid;
		अगर (t->reqid > IPSEC_MANUAL_REQID_MAX)
			t->reqid = 0;
		अगर (!t->reqid && !(t->reqid = gen_reqid(net)))
			वापस -ENOBUFS;
	पूर्ण

	/* addresses present only in tunnel mode */
	अगर (t->mode == XFRM_MODE_TUNNEL) अणु
		पूर्णांक err;

		err = parse_sockaddr_pair(
			(काष्ठा sockaddr *)(rq + 1),
			rq->sadb_x_ipsecrequest_len - माप(*rq),
			&t->saddr, &t->id.daddr, &t->encap_family);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		t->encap_family = xp->family;

	/* No way to set this via kame pfkey */
	t->allalgs = 1;
	xp->xfrm_nr++;
	वापस 0;
पूर्ण

अटल पूर्णांक
parse_ipsecrequests(काष्ठा xfrm_policy *xp, काष्ठा sadb_x_policy *pol)
अणु
	पूर्णांक err;
	पूर्णांक len = pol->sadb_x_policy_len*8 - माप(काष्ठा sadb_x_policy);
	काष्ठा sadb_x_ipsecrequest *rq = (व्योम*)(pol+1);

	अगर (pol->sadb_x_policy_len * 8 < माप(काष्ठा sadb_x_policy))
		वापस -EINVAL;

	जबतक (len >= माप(*rq)) अणु
		अगर (len < rq->sadb_x_ipsecrequest_len ||
		    rq->sadb_x_ipsecrequest_len < माप(*rq))
			वापस -EINVAL;

		अगर ((err = parse_ipsecrequest(xp, rq)) < 0)
			वापस err;
		len -= rq->sadb_x_ipsecrequest_len;
		rq = (व्योम*)((u8*)rq + rq->sadb_x_ipsecrequest_len);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pfkey_xfrm_policy2sec_ctx_size(स्थिर काष्ठा xfrm_policy *xp)
अणु
	काष्ठा xfrm_sec_ctx *xfrm_ctx = xp->security;

	अगर (xfrm_ctx) अणु
		पूर्णांक len = माप(काष्ठा sadb_x_sec_ctx);
		len += xfrm_ctx->ctx_len;
		वापस PFKEY_ALIGN8(len);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_xfrm_policy2msg_size(स्थिर काष्ठा xfrm_policy *xp)
अणु
	स्थिर काष्ठा xfrm_पंचांगpl *t;
	पूर्णांक sockaddr_size = pfkey_sockaddr_size(xp->family);
	पूर्णांक socklen = 0;
	पूर्णांक i;

	क्रम (i=0; i<xp->xfrm_nr; i++) अणु
		t = xp->xfrm_vec + i;
		socklen += pfkey_sockaddr_len(t->encap_family);
	पूर्ण

	वापस माप(काष्ठा sadb_msg) +
		(माप(काष्ठा sadb_lअगरeसमय) * 3) +
		(माप(काष्ठा sadb_address) * 2) +
		(sockaddr_size * 2) +
		माप(काष्ठा sadb_x_policy) +
		(xp->xfrm_nr * माप(काष्ठा sadb_x_ipsecrequest)) +
		(socklen * 2) +
		pfkey_xfrm_policy2sec_ctx_size(xp);
पूर्ण

अटल काष्ठा sk_buff * pfkey_xfrm_policy2msg_prep(स्थिर काष्ठा xfrm_policy *xp)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक size;

	size = pfkey_xfrm_policy2msg_size(xp);

	skb =  alloc_skb(size + 16, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस ERR_PTR(-ENOBUFS);

	वापस skb;
पूर्ण

अटल पूर्णांक pfkey_xfrm_policy2msg(काष्ठा sk_buff *skb, स्थिर काष्ठा xfrm_policy *xp, पूर्णांक dir)
अणु
	काष्ठा sadb_msg *hdr;
	काष्ठा sadb_address *addr;
	काष्ठा sadb_lअगरeसमय *lअगरeसमय;
	काष्ठा sadb_x_policy *pol;
	काष्ठा sadb_x_sec_ctx *sec_ctx;
	काष्ठा xfrm_sec_ctx *xfrm_ctx;
	पूर्णांक i;
	पूर्णांक size;
	पूर्णांक sockaddr_size = pfkey_sockaddr_size(xp->family);
	पूर्णांक socklen = pfkey_sockaddr_len(xp->family);

	size = pfkey_xfrm_policy2msg_size(xp);

	/* call should fill header later */
	hdr = skb_put(skb, माप(काष्ठा sadb_msg));
	स_रखो(hdr, 0, size);	/* XXX करो we need this ? */

	/* src address */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_SRC;
	addr->sadb_address_proto = pfkey_proto_from_xfrm(xp->selector.proto);
	addr->sadb_address_prefixlen = xp->selector.prefixlen_s;
	addr->sadb_address_reserved = 0;
	अगर (!pfkey_sockaddr_fill(&xp->selector.saddr,
				 xp->selector.sport,
				 (काष्ठा sockaddr *) (addr + 1),
				 xp->family))
		BUG();

	/* dst address */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_DST;
	addr->sadb_address_proto = pfkey_proto_from_xfrm(xp->selector.proto);
	addr->sadb_address_prefixlen = xp->selector.prefixlen_d;
	addr->sadb_address_reserved = 0;

	pfkey_sockaddr_fill(&xp->selector.daddr, xp->selector.dport,
			    (काष्ठा sockaddr *) (addr + 1),
			    xp->family);

	/* hard समय */
	lअगरeसमय = skb_put(skb, माप(काष्ठा sadb_lअगरeसमय));
	lअगरeसमय->sadb_lअगरeसमय_len =
		माप(काष्ठा sadb_lअगरeसमय)/माप(uपूर्णांक64_t);
	lअगरeसमय->sadb_lअगरeसमय_exttype = SADB_EXT_LIFETIME_HARD;
	lअगरeसमय->sadb_lअगरeसमय_allocations =  _X2KEY(xp->lft.hard_packet_limit);
	lअगरeसमय->sadb_lअगरeसमय_bytes = _X2KEY(xp->lft.hard_byte_limit);
	lअगरeसमय->sadb_lअगरeसमय_addसमय = xp->lft.hard_add_expires_seconds;
	lअगरeसमय->sadb_lअगरeसमय_useसमय = xp->lft.hard_use_expires_seconds;
	/* soft समय */
	lअगरeसमय = skb_put(skb, माप(काष्ठा sadb_lअगरeसमय));
	lअगरeसमय->sadb_lअगरeसमय_len =
		माप(काष्ठा sadb_lअगरeसमय)/माप(uपूर्णांक64_t);
	lअगरeसमय->sadb_lअगरeसमय_exttype = SADB_EXT_LIFETIME_SOFT;
	lअगरeसमय->sadb_lअगरeसमय_allocations =  _X2KEY(xp->lft.soft_packet_limit);
	lअगरeसमय->sadb_lअगरeसमय_bytes = _X2KEY(xp->lft.soft_byte_limit);
	lअगरeसमय->sadb_lअगरeसमय_addसमय = xp->lft.soft_add_expires_seconds;
	lअगरeसमय->sadb_lअगरeसमय_useसमय = xp->lft.soft_use_expires_seconds;
	/* current समय */
	lअगरeसमय = skb_put(skb, माप(काष्ठा sadb_lअगरeसमय));
	lअगरeसमय->sadb_lअगरeसमय_len =
		माप(काष्ठा sadb_lअगरeसमय)/माप(uपूर्णांक64_t);
	lअगरeसमय->sadb_lअगरeसमय_exttype = SADB_EXT_LIFETIME_CURRENT;
	lअगरeसमय->sadb_lअगरeसमय_allocations = xp->curlft.packets;
	lअगरeसमय->sadb_lअगरeसमय_bytes = xp->curlft.bytes;
	lअगरeसमय->sadb_lअगरeसमय_addसमय = xp->curlft.add_समय;
	lअगरeसमय->sadb_lअगरeसमय_useसमय = xp->curlft.use_समय;

	pol = skb_put(skb, माप(काष्ठा sadb_x_policy));
	pol->sadb_x_policy_len = माप(काष्ठा sadb_x_policy)/माप(uपूर्णांक64_t);
	pol->sadb_x_policy_exttype = SADB_X_EXT_POLICY;
	pol->sadb_x_policy_type = IPSEC_POLICY_DISCARD;
	अगर (xp->action == XFRM_POLICY_ALLOW) अणु
		अगर (xp->xfrm_nr)
			pol->sadb_x_policy_type = IPSEC_POLICY_IPSEC;
		अन्यथा
			pol->sadb_x_policy_type = IPSEC_POLICY_NONE;
	पूर्ण
	pol->sadb_x_policy_dir = dir+1;
	pol->sadb_x_policy_reserved = 0;
	pol->sadb_x_policy_id = xp->index;
	pol->sadb_x_policy_priority = xp->priority;

	क्रम (i=0; i<xp->xfrm_nr; i++) अणु
		स्थिर काष्ठा xfrm_पंचांगpl *t = xp->xfrm_vec + i;
		काष्ठा sadb_x_ipsecrequest *rq;
		पूर्णांक req_size;
		पूर्णांक mode;

		req_size = माप(काष्ठा sadb_x_ipsecrequest);
		अगर (t->mode == XFRM_MODE_TUNNEL) अणु
			socklen = pfkey_sockaddr_len(t->encap_family);
			req_size += socklen * 2;
		पूर्ण अन्यथा अणु
			size -= 2*socklen;
		पूर्ण
		rq = skb_put(skb, req_size);
		pol->sadb_x_policy_len += req_size/8;
		स_रखो(rq, 0, माप(*rq));
		rq->sadb_x_ipsecrequest_len = req_size;
		rq->sadb_x_ipsecrequest_proto = t->id.proto;
		अगर ((mode = pfkey_mode_from_xfrm(t->mode)) < 0)
			वापस -EINVAL;
		rq->sadb_x_ipsecrequest_mode = mode;
		rq->sadb_x_ipsecrequest_level = IPSEC_LEVEL_REQUIRE;
		अगर (t->reqid)
			rq->sadb_x_ipsecrequest_level = IPSEC_LEVEL_UNIQUE;
		अगर (t->optional)
			rq->sadb_x_ipsecrequest_level = IPSEC_LEVEL_USE;
		rq->sadb_x_ipsecrequest_reqid = t->reqid;

		अगर (t->mode == XFRM_MODE_TUNNEL) अणु
			u8 *sa = (व्योम *)(rq + 1);
			pfkey_sockaddr_fill(&t->saddr, 0,
					    (काष्ठा sockaddr *)sa,
					    t->encap_family);
			pfkey_sockaddr_fill(&t->id.daddr, 0,
					    (काष्ठा sockaddr *) (sa + socklen),
					    t->encap_family);
		पूर्ण
	पूर्ण

	/* security context */
	अगर ((xfrm_ctx = xp->security)) अणु
		पूर्णांक ctx_size = pfkey_xfrm_policy2sec_ctx_size(xp);

		sec_ctx = skb_put(skb, ctx_size);
		sec_ctx->sadb_x_sec_len = ctx_size / माप(uपूर्णांक64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_करोi = xfrm_ctx->ctx_करोi;
		sec_ctx->sadb_x_ctx_alg = xfrm_ctx->ctx_alg;
		sec_ctx->sadb_x_ctx_len = xfrm_ctx->ctx_len;
		स_नकल(sec_ctx + 1, xfrm_ctx->ctx_str,
		       xfrm_ctx->ctx_len);
	पूर्ण

	hdr->sadb_msg_len = size / माप(uपूर्णांक64_t);
	hdr->sadb_msg_reserved = refcount_पढ़ो(&xp->refcnt);

	वापस 0;
पूर्ण

अटल पूर्णांक key_notअगरy_policy(काष्ठा xfrm_policy *xp, पूर्णांक dir, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा sk_buff *out_skb;
	काष्ठा sadb_msg *out_hdr;
	पूर्णांक err;

	out_skb = pfkey_xfrm_policy2msg_prep(xp);
	अगर (IS_ERR(out_skb))
		वापस PTR_ERR(out_skb);

	err = pfkey_xfrm_policy2msg(out_skb, xp, dir);
	अगर (err < 0) अणु
		kमुक्त_skb(out_skb);
		वापस err;
	पूर्ण

	out_hdr = (काष्ठा sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = PF_KEY_V2;

	अगर (c->data.byid && c->event == XFRM_MSG_DELPOLICY)
		out_hdr->sadb_msg_type = SADB_X_SPDDELETE2;
	अन्यथा
		out_hdr->sadb_msg_type = event2poltype(c->event);
	out_hdr->sadb_msg_त्रुटि_सं = 0;
	out_hdr->sadb_msg_seq = c->seq;
	out_hdr->sadb_msg_pid = c->portid;
	pfkey_broadcast(out_skb, GFP_ATOMIC, BROADCAST_ALL, शून्य, xp_net(xp));
	वापस 0;

पूर्ण

अटल पूर्णांक pfkey_spdadd(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	पूर्णांक err = 0;
	काष्ठा sadb_lअगरeसमय *lअगरeसमय;
	काष्ठा sadb_address *sa;
	काष्ठा sadb_x_policy *pol;
	काष्ठा xfrm_policy *xp;
	काष्ठा km_event c;
	काष्ठा sadb_x_sec_ctx *sec_ctx;

	अगर (!present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST-1]) ||
	    !ext_hdrs[SADB_X_EXT_POLICY-1])
		वापस -EINVAL;

	pol = ext_hdrs[SADB_X_EXT_POLICY-1];
	अगर (pol->sadb_x_policy_type > IPSEC_POLICY_IPSEC)
		वापस -EINVAL;
	अगर (!pol->sadb_x_policy_dir || pol->sadb_x_policy_dir >= IPSEC_सूची_MAX)
		वापस -EINVAL;

	xp = xfrm_policy_alloc(net, GFP_KERNEL);
	अगर (xp == शून्य)
		वापस -ENOBUFS;

	xp->action = (pol->sadb_x_policy_type == IPSEC_POLICY_DISCARD ?
		      XFRM_POLICY_BLOCK : XFRM_POLICY_ALLOW);
	xp->priority = pol->sadb_x_policy_priority;

	sa = ext_hdrs[SADB_EXT_ADDRESS_SRC-1];
	xp->family = pfkey_sadb_addr2xfrm_addr(sa, &xp->selector.saddr);
	xp->selector.family = xp->family;
	xp->selector.prefixlen_s = sa->sadb_address_prefixlen;
	xp->selector.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);
	xp->selector.sport = ((काष्ठा sockaddr_in *)(sa+1))->sin_port;
	अगर (xp->selector.sport)
		xp->selector.sport_mask = htons(0xffff);

	sa = ext_hdrs[SADB_EXT_ADDRESS_DST-1];
	pfkey_sadb_addr2xfrm_addr(sa, &xp->selector.daddr);
	xp->selector.prefixlen_d = sa->sadb_address_prefixlen;

	/* Amusing, we set this twice.  KAME apps appear to set same value
	 * in both addresses.
	 */
	xp->selector.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);

	xp->selector.dport = ((काष्ठा sockaddr_in *)(sa+1))->sin_port;
	अगर (xp->selector.dport)
		xp->selector.dport_mask = htons(0xffff);

	sec_ctx = ext_hdrs[SADB_X_EXT_SEC_CTX - 1];
	अगर (sec_ctx != शून्य) अणु
		काष्ठा xfrm_user_sec_ctx *uctx = pfkey_sadb2xfrm_user_sec_ctx(sec_ctx, GFP_KERNEL);

		अगर (!uctx) अणु
			err = -ENOBUFS;
			जाओ out;
		पूर्ण

		err = security_xfrm_policy_alloc(&xp->security, uctx, GFP_KERNEL);
		kमुक्त(uctx);

		अगर (err)
			जाओ out;
	पूर्ण

	xp->lft.soft_byte_limit = XFRM_INF;
	xp->lft.hard_byte_limit = XFRM_INF;
	xp->lft.soft_packet_limit = XFRM_INF;
	xp->lft.hard_packet_limit = XFRM_INF;
	अगर ((lअगरeसमय = ext_hdrs[SADB_EXT_LIFETIME_HARD-1]) != शून्य) अणु
		xp->lft.hard_packet_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_allocations);
		xp->lft.hard_byte_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_bytes);
		xp->lft.hard_add_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_addसमय;
		xp->lft.hard_use_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_useसमय;
	पूर्ण
	अगर ((lअगरeसमय = ext_hdrs[SADB_EXT_LIFETIME_SOFT-1]) != शून्य) अणु
		xp->lft.soft_packet_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_allocations);
		xp->lft.soft_byte_limit = _KEY2X(lअगरeसमय->sadb_lअगरeसमय_bytes);
		xp->lft.soft_add_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_addसमय;
		xp->lft.soft_use_expires_seconds = lअगरeसमय->sadb_lअगरeसमय_useसमय;
	पूर्ण
	xp->xfrm_nr = 0;
	अगर (pol->sadb_x_policy_type == IPSEC_POLICY_IPSEC &&
	    (err = parse_ipsecrequests(xp, pol)) < 0)
		जाओ out;

	err = xfrm_policy_insert(pol->sadb_x_policy_dir-1, xp,
				 hdr->sadb_msg_type != SADB_X_SPDUPDATE);

	xfrm_audit_policy_add(xp, err ? 0 : 1, true);

	अगर (err)
		जाओ out;

	अगर (hdr->sadb_msg_type == SADB_X_SPDUPDATE)
		c.event = XFRM_MSG_UPDPOLICY;
	अन्यथा
		c.event = XFRM_MSG_NEWPOLICY;

	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;

	km_policy_notअगरy(xp, pol->sadb_x_policy_dir-1, &c);
	xfrm_pol_put(xp);
	वापस 0;

out:
	xp->walk.dead = 1;
	xfrm_policy_destroy(xp);
	वापस err;
पूर्ण

अटल पूर्णांक pfkey_spddelete(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	पूर्णांक err;
	काष्ठा sadb_address *sa;
	काष्ठा sadb_x_policy *pol;
	काष्ठा xfrm_policy *xp;
	काष्ठा xfrm_selector sel;
	काष्ठा km_event c;
	काष्ठा sadb_x_sec_ctx *sec_ctx;
	काष्ठा xfrm_sec_ctx *pol_ctx = शून्य;

	अगर (!present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST-1]) ||
	    !ext_hdrs[SADB_X_EXT_POLICY-1])
		वापस -EINVAL;

	pol = ext_hdrs[SADB_X_EXT_POLICY-1];
	अगर (!pol->sadb_x_policy_dir || pol->sadb_x_policy_dir >= IPSEC_सूची_MAX)
		वापस -EINVAL;

	स_रखो(&sel, 0, माप(sel));

	sa = ext_hdrs[SADB_EXT_ADDRESS_SRC-1];
	sel.family = pfkey_sadb_addr2xfrm_addr(sa, &sel.saddr);
	sel.prefixlen_s = sa->sadb_address_prefixlen;
	sel.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);
	sel.sport = ((काष्ठा sockaddr_in *)(sa+1))->sin_port;
	अगर (sel.sport)
		sel.sport_mask = htons(0xffff);

	sa = ext_hdrs[SADB_EXT_ADDRESS_DST-1];
	pfkey_sadb_addr2xfrm_addr(sa, &sel.daddr);
	sel.prefixlen_d = sa->sadb_address_prefixlen;
	sel.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);
	sel.dport = ((काष्ठा sockaddr_in *)(sa+1))->sin_port;
	अगर (sel.dport)
		sel.dport_mask = htons(0xffff);

	sec_ctx = ext_hdrs[SADB_X_EXT_SEC_CTX - 1];
	अगर (sec_ctx != शून्य) अणु
		काष्ठा xfrm_user_sec_ctx *uctx = pfkey_sadb2xfrm_user_sec_ctx(sec_ctx, GFP_KERNEL);

		अगर (!uctx)
			वापस -ENOMEM;

		err = security_xfrm_policy_alloc(&pol_ctx, uctx, GFP_KERNEL);
		kमुक्त(uctx);
		अगर (err)
			वापस err;
	पूर्ण

	xp = xfrm_policy_bysel_ctx(net, &dummy_mark, 0, XFRM_POLICY_TYPE_MAIN,
				   pol->sadb_x_policy_dir - 1, &sel, pol_ctx,
				   1, &err);
	security_xfrm_policy_मुक्त(pol_ctx);
	अगर (xp == शून्य)
		वापस -ENOENT;

	xfrm_audit_policy_delete(xp, err ? 0 : 1, true);

	अगर (err)
		जाओ out;

	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;
	c.data.byid = 0;
	c.event = XFRM_MSG_DELPOLICY;
	km_policy_notअगरy(xp, pol->sadb_x_policy_dir-1, &c);

out:
	xfrm_pol_put(xp);
	वापस err;
पूर्ण

अटल पूर्णांक key_pol_get_resp(काष्ठा sock *sk, काष्ठा xfrm_policy *xp, स्थिर काष्ठा sadb_msg *hdr, पूर्णांक dir)
अणु
	पूर्णांक err;
	काष्ठा sk_buff *out_skb;
	काष्ठा sadb_msg *out_hdr;
	err = 0;

	out_skb = pfkey_xfrm_policy2msg_prep(xp);
	अगर (IS_ERR(out_skb)) अणु
		err =  PTR_ERR(out_skb);
		जाओ out;
	पूर्ण
	err = pfkey_xfrm_policy2msg(out_skb, xp, dir);
	अगर (err < 0) अणु
		kमुक्त_skb(out_skb);
		जाओ out;
	पूर्ण

	out_hdr = (काष्ठा sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = hdr->sadb_msg_version;
	out_hdr->sadb_msg_type = hdr->sadb_msg_type;
	out_hdr->sadb_msg_satype = 0;
	out_hdr->sadb_msg_त्रुटि_सं = 0;
	out_hdr->sadb_msg_seq = hdr->sadb_msg_seq;
	out_hdr->sadb_msg_pid = hdr->sadb_msg_pid;
	pfkey_broadcast(out_skb, GFP_ATOMIC, BROADCAST_ONE, sk, xp_net(xp));
	err = 0;

out:
	वापस err;
पूर्ण

अटल पूर्णांक pfkey_sockaddr_pair_size(sa_family_t family)
अणु
	वापस PFKEY_ALIGN8(pfkey_sockaddr_len(family) * 2);
पूर्ण

अटल पूर्णांक parse_sockaddr_pair(काष्ठा sockaddr *sa, पूर्णांक ext_len,
			       xfrm_address_t *saddr, xfrm_address_t *daddr,
			       u16 *family)
अणु
	पूर्णांक af, socklen;

	अगर (ext_len < 2 || ext_len < pfkey_sockaddr_pair_size(sa->sa_family))
		वापस -EINVAL;

	af = pfkey_sockaddr_extract(sa, saddr);
	अगर (!af)
		वापस -EINVAL;

	socklen = pfkey_sockaddr_len(af);
	अगर (pfkey_sockaddr_extract((काष्ठा sockaddr *) (((u8 *)sa) + socklen),
				   daddr) != af)
		वापस -EINVAL;

	*family = af;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_KEY_MIGRATE
अटल पूर्णांक ipsecrequests_to_migrate(काष्ठा sadb_x_ipsecrequest *rq1, पूर्णांक len,
				    काष्ठा xfrm_migrate *m)
अणु
	पूर्णांक err;
	काष्ठा sadb_x_ipsecrequest *rq2;
	पूर्णांक mode;

	अगर (len < माप(*rq1) ||
	    len < rq1->sadb_x_ipsecrequest_len ||
	    rq1->sadb_x_ipsecrequest_len < माप(*rq1))
		वापस -EINVAL;

	/* old enकरोपूर्णांकs */
	err = parse_sockaddr_pair((काष्ठा sockaddr *)(rq1 + 1),
				  rq1->sadb_x_ipsecrequest_len - माप(*rq1),
				  &m->old_saddr, &m->old_daddr,
				  &m->old_family);
	अगर (err)
		वापस err;

	rq2 = (काष्ठा sadb_x_ipsecrequest *)((u8 *)rq1 + rq1->sadb_x_ipsecrequest_len);
	len -= rq1->sadb_x_ipsecrequest_len;

	अगर (len <= माप(*rq2) ||
	    len < rq2->sadb_x_ipsecrequest_len ||
	    rq2->sadb_x_ipsecrequest_len < माप(*rq2))
		वापस -EINVAL;

	/* new endpoपूर्णांकs */
	err = parse_sockaddr_pair((काष्ठा sockaddr *)(rq2 + 1),
				  rq2->sadb_x_ipsecrequest_len - माप(*rq2),
				  &m->new_saddr, &m->new_daddr,
				  &m->new_family);
	अगर (err)
		वापस err;

	अगर (rq1->sadb_x_ipsecrequest_proto != rq2->sadb_x_ipsecrequest_proto ||
	    rq1->sadb_x_ipsecrequest_mode != rq2->sadb_x_ipsecrequest_mode ||
	    rq1->sadb_x_ipsecrequest_reqid != rq2->sadb_x_ipsecrequest_reqid)
		वापस -EINVAL;

	m->proto = rq1->sadb_x_ipsecrequest_proto;
	अगर ((mode = pfkey_mode_to_xfrm(rq1->sadb_x_ipsecrequest_mode)) < 0)
		वापस -EINVAL;
	m->mode = mode;
	m->reqid = rq1->sadb_x_ipsecrequest_reqid;

	वापस ((पूर्णांक)(rq1->sadb_x_ipsecrequest_len +
		      rq2->sadb_x_ipsecrequest_len));
पूर्ण

अटल पूर्णांक pfkey_migrate(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	पूर्णांक i, len, ret, err = -EINVAL;
	u8 dir;
	काष्ठा sadb_address *sa;
	काष्ठा sadb_x_kmaddress *kma;
	काष्ठा sadb_x_policy *pol;
	काष्ठा sadb_x_ipsecrequest *rq;
	काष्ठा xfrm_selector sel;
	काष्ठा xfrm_migrate m[XFRM_MAX_DEPTH];
	काष्ठा xfrm_kmaddress k;
	काष्ठा net *net = sock_net(sk);

	अगर (!present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC - 1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST - 1]) ||
	    !ext_hdrs[SADB_X_EXT_POLICY - 1]) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	kma = ext_hdrs[SADB_X_EXT_KMADDRESS - 1];
	pol = ext_hdrs[SADB_X_EXT_POLICY - 1];

	अगर (pol->sadb_x_policy_dir >= IPSEC_सूची_MAX) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (kma) अणु
		/* convert sadb_x_kmaddress to xfrm_kmaddress */
		k.reserved = kma->sadb_x_kmaddress_reserved;
		ret = parse_sockaddr_pair((काष्ठा sockaddr *)(kma + 1),
					  8*(kma->sadb_x_kmaddress_len) - माप(*kma),
					  &k.local, &k.remote, &k.family);
		अगर (ret < 0) अणु
			err = ret;
			जाओ out;
		पूर्ण
	पूर्ण

	dir = pol->sadb_x_policy_dir - 1;
	स_रखो(&sel, 0, माप(sel));

	/* set source address info of selector */
	sa = ext_hdrs[SADB_EXT_ADDRESS_SRC - 1];
	sel.family = pfkey_sadb_addr2xfrm_addr(sa, &sel.saddr);
	sel.prefixlen_s = sa->sadb_address_prefixlen;
	sel.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);
	sel.sport = ((काष्ठा sockaddr_in *)(sa + 1))->sin_port;
	अगर (sel.sport)
		sel.sport_mask = htons(0xffff);

	/* set destination address info of selector */
	sa = ext_hdrs[SADB_EXT_ADDRESS_DST - 1];
	pfkey_sadb_addr2xfrm_addr(sa, &sel.daddr);
	sel.prefixlen_d = sa->sadb_address_prefixlen;
	sel.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);
	sel.dport = ((काष्ठा sockaddr_in *)(sa + 1))->sin_port;
	अगर (sel.dport)
		sel.dport_mask = htons(0xffff);

	rq = (काष्ठा sadb_x_ipsecrequest *)(pol + 1);

	/* extract ipsecrequests */
	i = 0;
	len = pol->sadb_x_policy_len * 8 - माप(काष्ठा sadb_x_policy);

	जबतक (len > 0 && i < XFRM_MAX_DEPTH) अणु
		ret = ipsecrequests_to_migrate(rq, len, &m[i]);
		अगर (ret < 0) अणु
			err = ret;
			जाओ out;
		पूर्ण अन्यथा अणु
			rq = (काष्ठा sadb_x_ipsecrequest *)((u8 *)rq + ret);
			len -= ret;
			i++;
		पूर्ण
	पूर्ण

	अगर (!i || len > 0) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	वापस xfrm_migrate(&sel, dir, XFRM_POLICY_TYPE_MAIN, m, i,
			    kma ? &k : शून्य, net, शून्य);

 out:
	वापस err;
पूर्ण
#अन्यथा
अटल पूर्णांक pfkey_migrate(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	वापस -ENOPROTOOPT;
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक pfkey_spdget(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	अचिन्हित पूर्णांक dir;
	पूर्णांक err = 0, delete;
	काष्ठा sadb_x_policy *pol;
	काष्ठा xfrm_policy *xp;
	काष्ठा km_event c;

	अगर ((pol = ext_hdrs[SADB_X_EXT_POLICY-1]) == शून्य)
		वापस -EINVAL;

	dir = xfrm_policy_id2dir(pol->sadb_x_policy_id);
	अगर (dir >= XFRM_POLICY_MAX)
		वापस -EINVAL;

	delete = (hdr->sadb_msg_type == SADB_X_SPDDELETE2);
	xp = xfrm_policy_byid(net, &dummy_mark, 0, XFRM_POLICY_TYPE_MAIN,
			      dir, pol->sadb_x_policy_id, delete, &err);
	अगर (xp == शून्य)
		वापस -ENOENT;

	अगर (delete) अणु
		xfrm_audit_policy_delete(xp, err ? 0 : 1, true);

		अगर (err)
			जाओ out;
		c.seq = hdr->sadb_msg_seq;
		c.portid = hdr->sadb_msg_pid;
		c.data.byid = 1;
		c.event = XFRM_MSG_DELPOLICY;
		km_policy_notअगरy(xp, dir, &c);
	पूर्ण अन्यथा अणु
		err = key_pol_get_resp(sk, xp, hdr, dir);
	पूर्ण

out:
	xfrm_pol_put(xp);
	वापस err;
पूर्ण

अटल पूर्णांक dump_sp(काष्ठा xfrm_policy *xp, पूर्णांक dir, पूर्णांक count, व्योम *ptr)
अणु
	काष्ठा pfkey_sock *pfk = ptr;
	काष्ठा sk_buff *out_skb;
	काष्ठा sadb_msg *out_hdr;
	पूर्णांक err;

	अगर (!pfkey_can_dump(&pfk->sk))
		वापस -ENOBUFS;

	out_skb = pfkey_xfrm_policy2msg_prep(xp);
	अगर (IS_ERR(out_skb))
		वापस PTR_ERR(out_skb);

	err = pfkey_xfrm_policy2msg(out_skb, xp, dir);
	अगर (err < 0) अणु
		kमुक्त_skb(out_skb);
		वापस err;
	पूर्ण

	out_hdr = (काष्ठा sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = pfk->dump.msg_version;
	out_hdr->sadb_msg_type = SADB_X_SPDDUMP;
	out_hdr->sadb_msg_satype = SADB_SATYPE_UNSPEC;
	out_hdr->sadb_msg_त्रुटि_सं = 0;
	out_hdr->sadb_msg_seq = count + 1;
	out_hdr->sadb_msg_pid = pfk->dump.msg_portid;

	अगर (pfk->dump.skb)
		pfkey_broadcast(pfk->dump.skb, GFP_ATOMIC, BROADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
	pfk->dump.skb = out_skb;

	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_dump_sp(काष्ठा pfkey_sock *pfk)
अणु
	काष्ठा net *net = sock_net(&pfk->sk);
	वापस xfrm_policy_walk(net, &pfk->dump.u.policy, dump_sp, (व्योम *) pfk);
पूर्ण

अटल व्योम pfkey_dump_sp_करोne(काष्ठा pfkey_sock *pfk)
अणु
	काष्ठा net *net = sock_net((काष्ठा sock *)pfk);

	xfrm_policy_walk_करोne(&pfk->dump.u.policy, net);
पूर्ण

अटल पूर्णांक pfkey_spddump(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा pfkey_sock *pfk = pfkey_sk(sk);

	mutex_lock(&pfk->dump_lock);
	अगर (pfk->dump.dump != शून्य) अणु
		mutex_unlock(&pfk->dump_lock);
		वापस -EBUSY;
	पूर्ण

	pfk->dump.msg_version = hdr->sadb_msg_version;
	pfk->dump.msg_portid = hdr->sadb_msg_pid;
	pfk->dump.dump = pfkey_dump_sp;
	pfk->dump.करोne = pfkey_dump_sp_करोne;
	xfrm_policy_walk_init(&pfk->dump.u.policy, XFRM_POLICY_TYPE_MAIN);
	mutex_unlock(&pfk->dump_lock);

	वापस pfkey_करो_dump(pfk);
पूर्ण

अटल पूर्णांक key_notअगरy_policy_flush(स्थिर काष्ठा km_event *c)
अणु
	काष्ठा sk_buff *skb_out;
	काष्ठा sadb_msg *hdr;

	skb_out = alloc_skb(माप(काष्ठा sadb_msg) + 16, GFP_ATOMIC);
	अगर (!skb_out)
		वापस -ENOBUFS;
	hdr = skb_put(skb_out, माप(काष्ठा sadb_msg));
	hdr->sadb_msg_type = SADB_X_SPDFLUSH;
	hdr->sadb_msg_seq = c->seq;
	hdr->sadb_msg_pid = c->portid;
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_त्रुटि_सं = (uपूर्णांक8_t) 0;
	hdr->sadb_msg_satype = SADB_SATYPE_UNSPEC;
	hdr->sadb_msg_len = (माप(काष्ठा sadb_msg) / माप(uपूर्णांक64_t));
	hdr->sadb_msg_reserved = 0;
	pfkey_broadcast(skb_out, GFP_ATOMIC, BROADCAST_ALL, शून्य, c->net);
	वापस 0;

पूर्ण

अटल पूर्णांक pfkey_spdflush(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा km_event c;
	पूर्णांक err, err2;

	err = xfrm_policy_flush(net, XFRM_POLICY_TYPE_MAIN, true);
	err2 = unicast_flush_resp(sk, hdr);
	अगर (err || err2) अणु
		अगर (err == -ESRCH) /* empty table - old silent behavior */
			वापस 0;
		वापस err;
	पूर्ण

	c.data.type = XFRM_POLICY_TYPE_MAIN;
	c.event = XFRM_MSG_FLUSHPOLICY;
	c.portid = hdr->sadb_msg_pid;
	c.seq = hdr->sadb_msg_seq;
	c.net = net;
	km_policy_notअगरy(शून्य, 0, &c);

	वापस 0;
पूर्ण

प्रकार पूर्णांक (*pfkey_handler)(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			     स्थिर काष्ठा sadb_msg *hdr, व्योम * स्थिर *ext_hdrs);
अटल स्थिर pfkey_handler pfkey_funcs[SADB_MAX + 1] = अणु
	[SADB_RESERVED]		= pfkey_reserved,
	[SADB_GETSPI]		= pfkey_माला_लोpi,
	[SADB_UPDATE]		= pfkey_add,
	[SADB_ADD]		= pfkey_add,
	[SADB_DELETE]		= pfkey_delete,
	[SADB_GET]		= pfkey_get,
	[SADB_ACQUIRE]		= pfkey_acquire,
	[SADB_REGISTER]		= pfkey_रेजिस्टर,
	[SADB_EXPIRE]		= शून्य,
	[SADB_FLUSH]		= pfkey_flush,
	[SADB_DUMP]		= pfkey_dump,
	[SADB_X_PROMISC]	= pfkey_promisc,
	[SADB_X_PCHANGE]	= शून्य,
	[SADB_X_SPDUPDATE]	= pfkey_spdadd,
	[SADB_X_SPDADD]		= pfkey_spdadd,
	[SADB_X_SPDDELETE]	= pfkey_spddelete,
	[SADB_X_SPDGET]		= pfkey_spdget,
	[SADB_X_SPDACQUIRE]	= शून्य,
	[SADB_X_SPDDUMP]	= pfkey_spddump,
	[SADB_X_SPDFLUSH]	= pfkey_spdflush,
	[SADB_X_SPDSETIDX]	= pfkey_spdadd,
	[SADB_X_SPDDELETE2]	= pfkey_spdget,
	[SADB_X_MIGRATE]	= pfkey_migrate,
पूर्ण;

अटल पूर्णांक pfkey_process(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर काष्ठा sadb_msg *hdr)
अणु
	व्योम *ext_hdrs[SADB_EXT_MAX];
	पूर्णांक err;

	pfkey_broadcast(skb_clone(skb, GFP_KERNEL), GFP_KERNEL,
			BROADCAST_PROMISC_ONLY, शून्य, sock_net(sk));

	स_रखो(ext_hdrs, 0, माप(ext_hdrs));
	err = parse_exthdrs(skb, hdr, ext_hdrs);
	अगर (!err) अणु
		err = -EOPNOTSUPP;
		अगर (pfkey_funcs[hdr->sadb_msg_type])
			err = pfkey_funcs[hdr->sadb_msg_type](sk, skb, hdr, ext_hdrs);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा sadb_msg *pfkey_get_base_msg(काष्ठा sk_buff *skb, पूर्णांक *errp)
अणु
	काष्ठा sadb_msg *hdr = शून्य;

	अगर (skb->len < माप(*hdr)) अणु
		*errp = -EMSGSIZE;
	पूर्ण अन्यथा अणु
		hdr = (काष्ठा sadb_msg *) skb->data;
		अगर (hdr->sadb_msg_version != PF_KEY_V2 ||
		    hdr->sadb_msg_reserved != 0 ||
		    (hdr->sadb_msg_type <= SADB_RESERVED ||
		     hdr->sadb_msg_type > SADB_MAX)) अणु
			hdr = शून्य;
			*errp = -EINVAL;
		पूर्ण अन्यथा अगर (hdr->sadb_msg_len != (skb->len /
						 माप(uपूर्णांक64_t)) ||
			   hdr->sadb_msg_len < (माप(काष्ठा sadb_msg) /
						माप(uपूर्णांक64_t))) अणु
			hdr = शून्य;
			*errp = -EMSGSIZE;
		पूर्ण अन्यथा अणु
			*errp = 0;
		पूर्ण
	पूर्ण
	वापस hdr;
पूर्ण

अटल अंतरभूत पूर्णांक aalg_पंचांगpl_set(स्थिर काष्ठा xfrm_पंचांगpl *t,
				स्थिर काष्ठा xfrm_algo_desc *d)
अणु
	अचिन्हित पूर्णांक id = d->desc.sadb_alg_id;

	अगर (id >= माप(t->aalgos) * 8)
		वापस 0;

	वापस (t->aalgos >> id) & 1;
पूर्ण

अटल अंतरभूत पूर्णांक ealg_पंचांगpl_set(स्थिर काष्ठा xfrm_पंचांगpl *t,
				स्थिर काष्ठा xfrm_algo_desc *d)
अणु
	अचिन्हित पूर्णांक id = d->desc.sadb_alg_id;

	अगर (id >= माप(t->ealgos) * 8)
		वापस 0;

	वापस (t->ealgos >> id) & 1;
पूर्ण

अटल पूर्णांक count_ah_combs(स्थिर काष्ठा xfrm_पंचांगpl *t)
अणु
	पूर्णांक i, sz = 0;

	क्रम (i = 0; ; i++) अणु
		स्थिर काष्ठा xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(i);
		अगर (!aalg)
			अवरोध;
		अगर (!aalg->pfkey_supported)
			जारी;
		अगर (aalg_पंचांगpl_set(t, aalg))
			sz += माप(काष्ठा sadb_comb);
	पूर्ण
	वापस sz + माप(काष्ठा sadb_prop);
पूर्ण

अटल पूर्णांक count_esp_combs(स्थिर काष्ठा xfrm_पंचांगpl *t)
अणु
	पूर्णांक i, k, sz = 0;

	क्रम (i = 0; ; i++) अणु
		स्थिर काष्ठा xfrm_algo_desc *ealg = xfrm_ealg_get_byidx(i);
		अगर (!ealg)
			अवरोध;

		अगर (!ealg->pfkey_supported)
			जारी;

		अगर (!(ealg_पंचांगpl_set(t, ealg)))
			जारी;

		क्रम (k = 1; ; k++) अणु
			स्थिर काष्ठा xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(k);
			अगर (!aalg)
				अवरोध;

			अगर (!aalg->pfkey_supported)
				जारी;

			अगर (aalg_पंचांगpl_set(t, aalg))
				sz += माप(काष्ठा sadb_comb);
		पूर्ण
	पूर्ण
	वापस sz + माप(काष्ठा sadb_prop);
पूर्ण

अटल व्योम dump_ah_combs(काष्ठा sk_buff *skb, स्थिर काष्ठा xfrm_पंचांगpl *t)
अणु
	काष्ठा sadb_prop *p;
	पूर्णांक i;

	p = skb_put(skb, माप(काष्ठा sadb_prop));
	p->sadb_prop_len = माप(काष्ठा sadb_prop)/8;
	p->sadb_prop_exttype = SADB_EXT_PROPOSAL;
	p->sadb_prop_replay = 32;
	स_रखो(p->sadb_prop_reserved, 0, माप(p->sadb_prop_reserved));

	क्रम (i = 0; ; i++) अणु
		स्थिर काष्ठा xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(i);
		अगर (!aalg)
			अवरोध;

		अगर (!aalg->pfkey_supported)
			जारी;

		अगर (aalg_पंचांगpl_set(t, aalg) && aalg->available) अणु
			काष्ठा sadb_comb *c;
			c = skb_put_zero(skb, माप(काष्ठा sadb_comb));
			p->sadb_prop_len += माप(काष्ठा sadb_comb)/8;
			c->sadb_comb_auth = aalg->desc.sadb_alg_id;
			c->sadb_comb_auth_minbits = aalg->desc.sadb_alg_minbits;
			c->sadb_comb_auth_maxbits = aalg->desc.sadb_alg_maxbits;
			c->sadb_comb_hard_addसमय = 24*60*60;
			c->sadb_comb_soft_addसमय = 20*60*60;
			c->sadb_comb_hard_useसमय = 8*60*60;
			c->sadb_comb_soft_useसमय = 7*60*60;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dump_esp_combs(काष्ठा sk_buff *skb, स्थिर काष्ठा xfrm_पंचांगpl *t)
अणु
	काष्ठा sadb_prop *p;
	पूर्णांक i, k;

	p = skb_put(skb, माप(काष्ठा sadb_prop));
	p->sadb_prop_len = माप(काष्ठा sadb_prop)/8;
	p->sadb_prop_exttype = SADB_EXT_PROPOSAL;
	p->sadb_prop_replay = 32;
	स_रखो(p->sadb_prop_reserved, 0, माप(p->sadb_prop_reserved));

	क्रम (i=0; ; i++) अणु
		स्थिर काष्ठा xfrm_algo_desc *ealg = xfrm_ealg_get_byidx(i);
		अगर (!ealg)
			अवरोध;

		अगर (!ealg->pfkey_supported)
			जारी;

		अगर (!(ealg_पंचांगpl_set(t, ealg) && ealg->available))
			जारी;

		क्रम (k = 1; ; k++) अणु
			काष्ठा sadb_comb *c;
			स्थिर काष्ठा xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(k);
			अगर (!aalg)
				अवरोध;
			अगर (!aalg->pfkey_supported)
				जारी;
			अगर (!(aalg_पंचांगpl_set(t, aalg) && aalg->available))
				जारी;
			c = skb_put(skb, माप(काष्ठा sadb_comb));
			स_रखो(c, 0, माप(*c));
			p->sadb_prop_len += माप(काष्ठा sadb_comb)/8;
			c->sadb_comb_auth = aalg->desc.sadb_alg_id;
			c->sadb_comb_auth_minbits = aalg->desc.sadb_alg_minbits;
			c->sadb_comb_auth_maxbits = aalg->desc.sadb_alg_maxbits;
			c->sadb_comb_encrypt = ealg->desc.sadb_alg_id;
			c->sadb_comb_encrypt_minbits = ealg->desc.sadb_alg_minbits;
			c->sadb_comb_encrypt_maxbits = ealg->desc.sadb_alg_maxbits;
			c->sadb_comb_hard_addसमय = 24*60*60;
			c->sadb_comb_soft_addसमय = 20*60*60;
			c->sadb_comb_hard_useसमय = 8*60*60;
			c->sadb_comb_soft_useसमय = 7*60*60;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक key_notअगरy_policy_expire(काष्ठा xfrm_policy *xp, स्थिर काष्ठा km_event *c)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक key_notअगरy_sa_expire(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा sk_buff *out_skb;
	काष्ठा sadb_msg *out_hdr;
	पूर्णांक hard;
	पूर्णांक hsc;

	hard = c->data.hard;
	अगर (hard)
		hsc = 2;
	अन्यथा
		hsc = 1;

	out_skb = pfkey_xfrm_state2msg_expire(x, hsc);
	अगर (IS_ERR(out_skb))
		वापस PTR_ERR(out_skb);

	out_hdr = (काष्ठा sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = PF_KEY_V2;
	out_hdr->sadb_msg_type = SADB_EXPIRE;
	out_hdr->sadb_msg_satype = pfkey_proto2satype(x->id.proto);
	out_hdr->sadb_msg_त्रुटि_सं = 0;
	out_hdr->sadb_msg_reserved = 0;
	out_hdr->sadb_msg_seq = 0;
	out_hdr->sadb_msg_pid = 0;

	pfkey_broadcast(out_skb, GFP_ATOMIC, BROADCAST_REGISTERED, शून्य,
			xs_net(x));
	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_send_notअगरy(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा net *net = x ? xs_net(x) : c->net;
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	अगर (atomic_पढ़ो(&net_pfkey->socks_nr) == 0)
		वापस 0;

	चयन (c->event) अणु
	हाल XFRM_MSG_EXPIRE:
		वापस key_notअगरy_sa_expire(x, c);
	हाल XFRM_MSG_DELSA:
	हाल XFRM_MSG_NEWSA:
	हाल XFRM_MSG_UPDSA:
		वापस key_notअगरy_sa(x, c);
	हाल XFRM_MSG_FLUSHSA:
		वापस key_notअगरy_sa_flush(c);
	हाल XFRM_MSG_NEWAE: /* not yet supported */
		अवरोध;
	शेष:
		pr_err("pfkey: Unknown SA event %d\n", c->event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pfkey_send_policy_notअगरy(काष्ठा xfrm_policy *xp, पूर्णांक dir, स्थिर काष्ठा km_event *c)
अणु
	अगर (xp && xp->type != XFRM_POLICY_TYPE_MAIN)
		वापस 0;

	चयन (c->event) अणु
	हाल XFRM_MSG_POLEXPIRE:
		वापस key_notअगरy_policy_expire(xp, c);
	हाल XFRM_MSG_DELPOLICY:
	हाल XFRM_MSG_NEWPOLICY:
	हाल XFRM_MSG_UPDPOLICY:
		वापस key_notअगरy_policy(xp, dir, c);
	हाल XFRM_MSG_FLUSHPOLICY:
		अगर (c->data.type != XFRM_POLICY_TYPE_MAIN)
			अवरोध;
		वापस key_notअगरy_policy_flush(c);
	शेष:
		pr_err("pfkey: Unknown policy event %d\n", c->event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 get_acqseq(व्योम)
अणु
	u32 res;
	अटल atomic_t acqseq;

	करो अणु
		res = atomic_inc_वापस(&acqseq);
	पूर्ण जबतक (!res);
	वापस res;
पूर्ण

अटल bool pfkey_is_alive(स्थिर काष्ठा km_event *c)
अणु
	काष्ठा netns_pfkey *net_pfkey = net_generic(c->net, pfkey_net_id);
	काष्ठा sock *sk;
	bool is_alive = false;

	rcu_पढ़ो_lock();
	sk_क्रम_each_rcu(sk, &net_pfkey->table) अणु
		अगर (pfkey_sk(sk)->रेजिस्टरed) अणु
			is_alive = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस is_alive;
पूर्ण

अटल पूर्णांक pfkey_send_acquire(काष्ठा xfrm_state *x, काष्ठा xfrm_पंचांगpl *t, काष्ठा xfrm_policy *xp)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;
	काष्ठा sadb_address *addr;
	काष्ठा sadb_x_policy *pol;
	पूर्णांक sockaddr_size;
	पूर्णांक size;
	काष्ठा sadb_x_sec_ctx *sec_ctx;
	काष्ठा xfrm_sec_ctx *xfrm_ctx;
	पूर्णांक ctx_size = 0;

	sockaddr_size = pfkey_sockaddr_size(x->props.family);
	अगर (!sockaddr_size)
		वापस -EINVAL;

	size = माप(काष्ठा sadb_msg) +
		(माप(काष्ठा sadb_address) * 2) +
		(sockaddr_size * 2) +
		माप(काष्ठा sadb_x_policy);

	अगर (x->id.proto == IPPROTO_AH)
		size += count_ah_combs(t);
	अन्यथा अगर (x->id.proto == IPPROTO_ESP)
		size += count_esp_combs(t);

	अगर ((xfrm_ctx = x->security)) अणु
		ctx_size = PFKEY_ALIGN8(xfrm_ctx->ctx_len);
		size +=  माप(काष्ठा sadb_x_sec_ctx) + ctx_size;
	पूर्ण

	skb =  alloc_skb(size + 16, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(काष्ठा sadb_msg));
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_type = SADB_ACQUIRE;
	hdr->sadb_msg_satype = pfkey_proto2satype(x->id.proto);
	hdr->sadb_msg_len = size / माप(uपूर्णांक64_t);
	hdr->sadb_msg_त्रुटि_सं = 0;
	hdr->sadb_msg_reserved = 0;
	hdr->sadb_msg_seq = x->km.seq = get_acqseq();
	hdr->sadb_msg_pid = 0;

	/* src address */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_SRC;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;
	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->props.saddr, 0,
				    (काष्ठा sockaddr *) (addr + 1),
				    x->props.family);
	अगर (!addr->sadb_address_prefixlen)
		BUG();

	/* dst address */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_DST;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;
	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->id.daddr, 0,
				    (काष्ठा sockaddr *) (addr + 1),
				    x->props.family);
	अगर (!addr->sadb_address_prefixlen)
		BUG();

	pol = skb_put(skb, माप(काष्ठा sadb_x_policy));
	pol->sadb_x_policy_len = माप(काष्ठा sadb_x_policy)/माप(uपूर्णांक64_t);
	pol->sadb_x_policy_exttype = SADB_X_EXT_POLICY;
	pol->sadb_x_policy_type = IPSEC_POLICY_IPSEC;
	pol->sadb_x_policy_dir = XFRM_POLICY_OUT + 1;
	pol->sadb_x_policy_reserved = 0;
	pol->sadb_x_policy_id = xp->index;
	pol->sadb_x_policy_priority = xp->priority;

	/* Set sadb_comb's. */
	अगर (x->id.proto == IPPROTO_AH)
		dump_ah_combs(skb, t);
	अन्यथा अगर (x->id.proto == IPPROTO_ESP)
		dump_esp_combs(skb, t);

	/* security context */
	अगर (xfrm_ctx) अणु
		sec_ctx = skb_put(skb,
				  माप(काष्ठा sadb_x_sec_ctx) + ctx_size);
		sec_ctx->sadb_x_sec_len =
		  (माप(काष्ठा sadb_x_sec_ctx) + ctx_size) / माप(uपूर्णांक64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_करोi = xfrm_ctx->ctx_करोi;
		sec_ctx->sadb_x_ctx_alg = xfrm_ctx->ctx_alg;
		sec_ctx->sadb_x_ctx_len = xfrm_ctx->ctx_len;
		स_नकल(sec_ctx + 1, xfrm_ctx->ctx_str,
		       xfrm_ctx->ctx_len);
	पूर्ण

	वापस pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_REGISTERED, शून्य,
			       xs_net(x));
पूर्ण

अटल काष्ठा xfrm_policy *pfkey_compile_policy(काष्ठा sock *sk, पूर्णांक opt,
						u8 *data, पूर्णांक len, पूर्णांक *dir)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा xfrm_policy *xp;
	काष्ठा sadb_x_policy *pol = (काष्ठा sadb_x_policy*)data;
	काष्ठा sadb_x_sec_ctx *sec_ctx;

	चयन (sk->sk_family) अणु
	हाल AF_INET:
		अगर (opt != IP_IPSEC_POLICY) अणु
			*dir = -EOPNOTSUPP;
			वापस शून्य;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		अगर (opt != IPV6_IPSEC_POLICY) अणु
			*dir = -EOPNOTSUPP;
			वापस शून्य;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		*dir = -EINVAL;
		वापस शून्य;
	पूर्ण

	*dir = -EINVAL;

	अगर (len < माप(काष्ठा sadb_x_policy) ||
	    pol->sadb_x_policy_len*8 > len ||
	    pol->sadb_x_policy_type > IPSEC_POLICY_BYPASS ||
	    (!pol->sadb_x_policy_dir || pol->sadb_x_policy_dir > IPSEC_सूची_OUTBOUND))
		वापस शून्य;

	xp = xfrm_policy_alloc(net, GFP_ATOMIC);
	अगर (xp == शून्य) अणु
		*dir = -ENOBUFS;
		वापस शून्य;
	पूर्ण

	xp->action = (pol->sadb_x_policy_type == IPSEC_POLICY_DISCARD ?
		      XFRM_POLICY_BLOCK : XFRM_POLICY_ALLOW);

	xp->lft.soft_byte_limit = XFRM_INF;
	xp->lft.hard_byte_limit = XFRM_INF;
	xp->lft.soft_packet_limit = XFRM_INF;
	xp->lft.hard_packet_limit = XFRM_INF;
	xp->family = sk->sk_family;

	xp->xfrm_nr = 0;
	अगर (pol->sadb_x_policy_type == IPSEC_POLICY_IPSEC &&
	    (*dir = parse_ipsecrequests(xp, pol)) < 0)
		जाओ out;

	/* security context too */
	अगर (len >= (pol->sadb_x_policy_len*8 +
	    माप(काष्ठा sadb_x_sec_ctx))) अणु
		अक्षर *p = (अक्षर *)pol;
		काष्ठा xfrm_user_sec_ctx *uctx;

		p += pol->sadb_x_policy_len*8;
		sec_ctx = (काष्ठा sadb_x_sec_ctx *)p;
		अगर (len < pol->sadb_x_policy_len*8 +
		    sec_ctx->sadb_x_sec_len*8) अणु
			*dir = -EINVAL;
			जाओ out;
		पूर्ण
		अगर ((*dir = verअगरy_sec_ctx_len(p)))
			जाओ out;
		uctx = pfkey_sadb2xfrm_user_sec_ctx(sec_ctx, GFP_ATOMIC);
		*dir = security_xfrm_policy_alloc(&xp->security, uctx, GFP_ATOMIC);
		kमुक्त(uctx);

		अगर (*dir)
			जाओ out;
	पूर्ण

	*dir = pol->sadb_x_policy_dir-1;
	वापस xp;

out:
	xp->walk.dead = 1;
	xfrm_policy_destroy(xp);
	वापस शून्य;
पूर्ण

अटल पूर्णांक pfkey_send_new_mapping(काष्ठा xfrm_state *x, xfrm_address_t *ipaddr, __be16 sport)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;
	काष्ठा sadb_sa *sa;
	काष्ठा sadb_address *addr;
	काष्ठा sadb_x_nat_t_port *n_port;
	पूर्णांक sockaddr_size;
	पूर्णांक size;
	__u8 satype = (x->id.proto == IPPROTO_ESP ? SADB_SATYPE_ESP : 0);
	काष्ठा xfrm_encap_पंचांगpl *natt = शून्य;

	sockaddr_size = pfkey_sockaddr_size(x->props.family);
	अगर (!sockaddr_size)
		वापस -EINVAL;

	अगर (!satype)
		वापस -EINVAL;

	अगर (!x->encap)
		वापस -EINVAL;

	natt = x->encap;

	/* Build an SADB_X_NAT_T_NEW_MAPPING message:
	 *
	 * HDR | SA | ADDRESS_SRC (old addr) | NAT_T_SPORT (old port) |
	 * ADDRESS_DST (new addr) | NAT_T_DPORT (new port)
	 */

	size = माप(काष्ठा sadb_msg) +
		माप(काष्ठा sadb_sa) +
		(माप(काष्ठा sadb_address) * 2) +
		(sockaddr_size * 2) +
		(माप(काष्ठा sadb_x_nat_t_port) * 2);

	skb =  alloc_skb(size + 16, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(काष्ठा sadb_msg));
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_type = SADB_X_NAT_T_NEW_MAPPING;
	hdr->sadb_msg_satype = satype;
	hdr->sadb_msg_len = size / माप(uपूर्णांक64_t);
	hdr->sadb_msg_त्रुटि_सं = 0;
	hdr->sadb_msg_reserved = 0;
	hdr->sadb_msg_seq = x->km.seq = get_acqseq();
	hdr->sadb_msg_pid = 0;

	/* SA */
	sa = skb_put(skb, माप(काष्ठा sadb_sa));
	sa->sadb_sa_len = माप(काष्ठा sadb_sa)/माप(uपूर्णांक64_t);
	sa->sadb_sa_exttype = SADB_EXT_SA;
	sa->sadb_sa_spi = x->id.spi;
	sa->sadb_sa_replay = 0;
	sa->sadb_sa_state = 0;
	sa->sadb_sa_auth = 0;
	sa->sadb_sa_encrypt = 0;
	sa->sadb_sa_flags = 0;

	/* ADDRESS_SRC (old addr) */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_SRC;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;
	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->props.saddr, 0,
				    (काष्ठा sockaddr *) (addr + 1),
				    x->props.family);
	अगर (!addr->sadb_address_prefixlen)
		BUG();

	/* NAT_T_SPORT (old port) */
	n_port = skb_put(skb, माप(*n_port));
	n_port->sadb_x_nat_t_port_len = माप(*n_port)/माप(uपूर्णांक64_t);
	n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_SPORT;
	n_port->sadb_x_nat_t_port_port = natt->encap_sport;
	n_port->sadb_x_nat_t_port_reserved = 0;

	/* ADDRESS_DST (new addr) */
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sockaddr_size);
	addr->sadb_address_len =
		(माप(काष्ठा sadb_address)+sockaddr_size)/
			माप(uपूर्णांक64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_DST;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;
	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(ipaddr, 0,
				    (काष्ठा sockaddr *) (addr + 1),
				    x->props.family);
	अगर (!addr->sadb_address_prefixlen)
		BUG();

	/* NAT_T_DPORT (new port) */
	n_port = skb_put(skb, माप(*n_port));
	n_port->sadb_x_nat_t_port_len = माप(*n_port)/माप(uपूर्णांक64_t);
	n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_DPORT;
	n_port->sadb_x_nat_t_port_port = sport;
	n_port->sadb_x_nat_t_port_reserved = 0;

	वापस pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_REGISTERED, शून्य,
			       xs_net(x));
पूर्ण

#अगर_घोषित CONFIG_NET_KEY_MIGRATE
अटल पूर्णांक set_sadb_address(काष्ठा sk_buff *skb, पूर्णांक sasize, पूर्णांक type,
			    स्थिर काष्ठा xfrm_selector *sel)
अणु
	काष्ठा sadb_address *addr;
	addr = skb_put(skb, माप(काष्ठा sadb_address) + sasize);
	addr->sadb_address_len = (माप(काष्ठा sadb_address) + sasize)/8;
	addr->sadb_address_exttype = type;
	addr->sadb_address_proto = sel->proto;
	addr->sadb_address_reserved = 0;

	चयन (type) अणु
	हाल SADB_EXT_ADDRESS_SRC:
		addr->sadb_address_prefixlen = sel->prefixlen_s;
		pfkey_sockaddr_fill(&sel->saddr, 0,
				    (काष्ठा sockaddr *)(addr + 1),
				    sel->family);
		अवरोध;
	हाल SADB_EXT_ADDRESS_DST:
		addr->sadb_address_prefixlen = sel->prefixlen_d;
		pfkey_sockaddr_fill(&sel->daddr, 0,
				    (काष्ठा sockaddr *)(addr + 1),
				    sel->family);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक set_sadb_kmaddress(काष्ठा sk_buff *skb, स्थिर काष्ठा xfrm_kmaddress *k)
अणु
	काष्ठा sadb_x_kmaddress *kma;
	u8 *sa;
	पूर्णांक family = k->family;
	पूर्णांक socklen = pfkey_sockaddr_len(family);
	पूर्णांक size_req;

	size_req = (माप(काष्ठा sadb_x_kmaddress) +
		    pfkey_sockaddr_pair_size(family));

	kma = skb_put_zero(skb, size_req);
	kma->sadb_x_kmaddress_len = size_req / 8;
	kma->sadb_x_kmaddress_exttype = SADB_X_EXT_KMADDRESS;
	kma->sadb_x_kmaddress_reserved = k->reserved;

	sa = (u8 *)(kma + 1);
	अगर (!pfkey_sockaddr_fill(&k->local, 0, (काष्ठा sockaddr *)sa, family) ||
	    !pfkey_sockaddr_fill(&k->remote, 0, (काष्ठा sockaddr *)(sa+socklen), family))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक set_ipsecrequest(काष्ठा sk_buff *skb,
			    uपूर्णांक8_t proto, uपूर्णांक8_t mode, पूर्णांक level,
			    uपूर्णांक32_t reqid, uपूर्णांक8_t family,
			    स्थिर xfrm_address_t *src, स्थिर xfrm_address_t *dst)
अणु
	काष्ठा sadb_x_ipsecrequest *rq;
	u8 *sa;
	पूर्णांक socklen = pfkey_sockaddr_len(family);
	पूर्णांक size_req;

	size_req = माप(काष्ठा sadb_x_ipsecrequest) +
		   pfkey_sockaddr_pair_size(family);

	rq = skb_put_zero(skb, size_req);
	rq->sadb_x_ipsecrequest_len = size_req;
	rq->sadb_x_ipsecrequest_proto = proto;
	rq->sadb_x_ipsecrequest_mode = mode;
	rq->sadb_x_ipsecrequest_level = level;
	rq->sadb_x_ipsecrequest_reqid = reqid;

	sa = (u8 *) (rq + 1);
	अगर (!pfkey_sockaddr_fill(src, 0, (काष्ठा sockaddr *)sa, family) ||
	    !pfkey_sockaddr_fill(dst, 0, (काष्ठा sockaddr *)(sa + socklen), family))
		वापस -EINVAL;

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_KEY_MIGRATE
अटल पूर्णांक pfkey_send_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
			      स्थिर काष्ठा xfrm_migrate *m, पूर्णांक num_bundles,
			      स्थिर काष्ठा xfrm_kmaddress *k,
			      स्थिर काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	पूर्णांक i;
	पूर्णांक sasize_sel;
	पूर्णांक size = 0;
	पूर्णांक size_pol = 0;
	काष्ठा sk_buff *skb;
	काष्ठा sadb_msg *hdr;
	काष्ठा sadb_x_policy *pol;
	स्थिर काष्ठा xfrm_migrate *mp;

	अगर (type != XFRM_POLICY_TYPE_MAIN)
		वापस 0;

	अगर (num_bundles <= 0 || num_bundles > XFRM_MAX_DEPTH)
		वापस -EINVAL;

	अगर (k != शून्य) अणु
		/* addresses क्रम KM */
		size += PFKEY_ALIGN8(माप(काष्ठा sadb_x_kmaddress) +
				     pfkey_sockaddr_pair_size(k->family));
	पूर्ण

	/* selector */
	sasize_sel = pfkey_sockaddr_size(sel->family);
	अगर (!sasize_sel)
		वापस -EINVAL;
	size += (माप(काष्ठा sadb_address) + sasize_sel) * 2;

	/* policy info */
	size_pol += माप(काष्ठा sadb_x_policy);

	/* ipsecrequests */
	क्रम (i = 0, mp = m; i < num_bundles; i++, mp++) अणु
		/* old locator pair */
		size_pol += माप(काष्ठा sadb_x_ipsecrequest) +
			    pfkey_sockaddr_pair_size(mp->old_family);
		/* new locator pair */
		size_pol += माप(काष्ठा sadb_x_ipsecrequest) +
			    pfkey_sockaddr_pair_size(mp->new_family);
	पूर्ण

	size += माप(काष्ठा sadb_msg) + size_pol;

	/* alloc buffer */
	skb = alloc_skb(size, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(काष्ठा sadb_msg));
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_type = SADB_X_MIGRATE;
	hdr->sadb_msg_satype = pfkey_proto2satype(m->proto);
	hdr->sadb_msg_len = size / 8;
	hdr->sadb_msg_त्रुटि_सं = 0;
	hdr->sadb_msg_reserved = 0;
	hdr->sadb_msg_seq = 0;
	hdr->sadb_msg_pid = 0;

	/* Addresses to be used by KM क्रम negotiation, अगर ext is available */
	अगर (k != शून्य && (set_sadb_kmaddress(skb, k) < 0))
		जाओ err;

	/* selector src */
	set_sadb_address(skb, sasize_sel, SADB_EXT_ADDRESS_SRC, sel);

	/* selector dst */
	set_sadb_address(skb, sasize_sel, SADB_EXT_ADDRESS_DST, sel);

	/* policy inक्रमmation */
	pol = skb_put(skb, माप(काष्ठा sadb_x_policy));
	pol->sadb_x_policy_len = size_pol / 8;
	pol->sadb_x_policy_exttype = SADB_X_EXT_POLICY;
	pol->sadb_x_policy_type = IPSEC_POLICY_IPSEC;
	pol->sadb_x_policy_dir = dir + 1;
	pol->sadb_x_policy_reserved = 0;
	pol->sadb_x_policy_id = 0;
	pol->sadb_x_policy_priority = 0;

	क्रम (i = 0, mp = m; i < num_bundles; i++, mp++) अणु
		/* old ipsecrequest */
		पूर्णांक mode = pfkey_mode_from_xfrm(mp->mode);
		अगर (mode < 0)
			जाओ err;
		अगर (set_ipsecrequest(skb, mp->proto, mode,
				     (mp->reqid ?  IPSEC_LEVEL_UNIQUE : IPSEC_LEVEL_REQUIRE),
				     mp->reqid, mp->old_family,
				     &mp->old_saddr, &mp->old_daddr) < 0)
			जाओ err;

		/* new ipsecrequest */
		अगर (set_ipsecrequest(skb, mp->proto, mode,
				     (mp->reqid ? IPSEC_LEVEL_UNIQUE : IPSEC_LEVEL_REQUIRE),
				     mp->reqid, mp->new_family,
				     &mp->new_saddr, &mp->new_daddr) < 0)
			जाओ err;
	पूर्ण

	/* broadcast migrate message to sockets */
	pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_ALL, शून्य, &init_net);

	वापस 0;

err:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण
#अन्यथा
अटल पूर्णांक pfkey_send_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
			      स्थिर काष्ठा xfrm_migrate *m, पूर्णांक num_bundles,
			      स्थिर काष्ठा xfrm_kmaddress *k,
			      स्थिर काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	वापस -ENOPROTOOPT;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pfkey_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा sadb_msg *hdr = शून्य;
	पूर्णांक err;
	काष्ठा net *net = sock_net(sk);

	err = -EOPNOTSUPP;
	अगर (msg->msg_flags & MSG_OOB)
		जाओ out;

	err = -EMSGSIZE;
	अगर ((अचिन्हित पूर्णांक)len > sk->sk_sndbuf - 32)
		जाओ out;

	err = -ENOBUFS;
	skb = alloc_skb(len, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ out;

	err = -EFAULT;
	अगर (स_नकल_from_msg(skb_put(skb,len), msg, len))
		जाओ out;

	hdr = pfkey_get_base_msg(skb, &err);
	अगर (!hdr)
		जाओ out;

	mutex_lock(&net->xfrm.xfrm_cfg_mutex);
	err = pfkey_process(sk, skb, hdr);
	mutex_unlock(&net->xfrm.xfrm_cfg_mutex);

out:
	अगर (err && hdr && pfkey_error(hdr, err, sk) == 0)
		err = 0;
	kमुक्त_skb(skb);

	वापस err ? : len;
पूर्ण

अटल पूर्णांक pfkey_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
			 पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pfkey_sock *pfk = pfkey_sk(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक copied, err;

	err = -EINVAL;
	अगर (flags & ~(MSG_PEEK|MSG_DONTWAIT|MSG_TRUNC|MSG_CMSG_COMPAT))
		जाओ out;

	skb = skb_recv_datagram(sk, flags, flags & MSG_DONTWAIT, &err);
	अगर (skb == शून्य)
		जाओ out;

	copied = skb->len;
	अगर (copied > len) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	skb_reset_transport_header(skb);
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ out_मुक्त;

	sock_recv_ts_and_drops(msg, sk, skb);

	err = (flags & MSG_TRUNC) ? skb->len : copied;

	अगर (pfk->dump.dump != शून्य &&
	    3 * atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf)
		pfkey_करो_dump(pfk);

out_मुक्त:
	skb_मुक्त_datagram(sk, skb);
out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proto_ops pfkey_ops = अणु
	.family		=	PF_KEY,
	.owner		=	THIS_MODULE,
	/* Operations that make no sense on pfkey sockets. */
	.bind		=	sock_no_bind,
	.connect	=	sock_no_connect,
	.socketpair	=	sock_no_socketpair,
	.accept		=	sock_no_accept,
	.getname	=	sock_no_getname,
	.ioctl		=	sock_no_ioctl,
	.listen		=	sock_no_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.mmap		=	sock_no_mmap,
	.sendpage	=	sock_no_sendpage,

	/* Now the operations that really occur. */
	.release	=	pfkey_release,
	.poll		=	datagram_poll,
	.sendmsg	=	pfkey_sendmsg,
	.recvmsg	=	pfkey_recvmsg,
पूर्ण;

अटल स्थिर काष्ठा net_proto_family pfkey_family_ops = अणु
	.family	=	PF_KEY,
	.create	=	pfkey_create,
	.owner	=	THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक pfkey_seq_show(काष्ठा seq_file *f, व्योम *v)
अणु
	काष्ठा sock *s = sk_entry(v);

	अगर (v == SEQ_START_TOKEN)
		seq_म_लिखो(f ,"sk       RefCnt Rmem   Wmem   User   Inode\n");
	अन्यथा
		seq_म_लिखो(f, "%pK %-6d %-6u %-6u %-6u %-6lu\n",
			       s,
			       refcount_पढ़ो(&s->sk_refcnt),
			       sk_rmem_alloc_get(s),
			       sk_wmem_alloc_get(s),
			       from_kuid_munged(seq_user_ns(f), sock_i_uid(s)),
			       sock_i_ino(s)
			       );
	वापस 0;
पूर्ण

अटल व्योम *pfkey_seq_start(काष्ठा seq_file *f, loff_t *ppos)
	__acquires(rcu)
अणु
	काष्ठा net *net = seq_file_net(f);
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	rcu_पढ़ो_lock();
	वापस seq_hlist_start_head_rcu(&net_pfkey->table, *ppos);
पूर्ण

अटल व्योम *pfkey_seq_next(काष्ठा seq_file *f, व्योम *v, loff_t *ppos)
अणु
	काष्ठा net *net = seq_file_net(f);
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	वापस seq_hlist_next_rcu(v, &net_pfkey->table, ppos);
पूर्ण

अटल व्योम pfkey_seq_stop(काष्ठा seq_file *f, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations pfkey_seq_ops = अणु
	.start	= pfkey_seq_start,
	.next	= pfkey_seq_next,
	.stop	= pfkey_seq_stop,
	.show	= pfkey_seq_show,
पूर्ण;

अटल पूर्णांक __net_init pfkey_init_proc(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *e;

	e = proc_create_net("pfkey", 0, net->proc_net, &pfkey_seq_ops,
			माप(काष्ठा seq_net_निजी));
	अगर (e == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास pfkey_निकास_proc(काष्ठा net *net)
अणु
	हटाओ_proc_entry("pfkey", net->proc_net);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pfkey_init_proc(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pfkey_निकास_proc(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल काष्ठा xfrm_mgr pfkeyv2_mgr =
अणु
	.notअगरy		= pfkey_send_notअगरy,
	.acquire	= pfkey_send_acquire,
	.compile_policy	= pfkey_compile_policy,
	.new_mapping	= pfkey_send_new_mapping,
	.notअगरy_policy	= pfkey_send_policy_notअगरy,
	.migrate	= pfkey_send_migrate,
	.is_alive	= pfkey_is_alive,
पूर्ण;

अटल पूर्णांक __net_init pfkey_net_init(काष्ठा net *net)
अणु
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);
	पूर्णांक rv;

	INIT_HLIST_HEAD(&net_pfkey->table);
	atomic_set(&net_pfkey->socks_nr, 0);

	rv = pfkey_init_proc(net);

	वापस rv;
पूर्ण

अटल व्योम __net_निकास pfkey_net_निकास(काष्ठा net *net)
अणु
	काष्ठा netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	pfkey_निकास_proc(net);
	WARN_ON(!hlist_empty(&net_pfkey->table));
पूर्ण

अटल काष्ठा pernet_operations pfkey_net_ops = अणु
	.init = pfkey_net_init,
	.निकास = pfkey_net_निकास,
	.id   = &pfkey_net_id,
	.size = माप(काष्ठा netns_pfkey),
पूर्ण;

अटल व्योम __निकास ipsec_pfkey_निकास(व्योम)
अणु
	xfrm_unरेजिस्टर_km(&pfkeyv2_mgr);
	sock_unरेजिस्टर(PF_KEY);
	unरेजिस्टर_pernet_subsys(&pfkey_net_ops);
	proto_unरेजिस्टर(&key_proto);
पूर्ण

अटल पूर्णांक __init ipsec_pfkey_init(व्योम)
अणु
	पूर्णांक err = proto_रेजिस्टर(&key_proto, 0);

	अगर (err != 0)
		जाओ out;

	err = रेजिस्टर_pernet_subsys(&pfkey_net_ops);
	अगर (err != 0)
		जाओ out_unरेजिस्टर_key_proto;
	err = sock_रेजिस्टर(&pfkey_family_ops);
	अगर (err != 0)
		जाओ out_unरेजिस्टर_pernet;
	err = xfrm_रेजिस्टर_km(&pfkeyv2_mgr);
	अगर (err != 0)
		जाओ out_sock_unरेजिस्टर;
out:
	वापस err;

out_sock_unरेजिस्टर:
	sock_unरेजिस्टर(PF_KEY);
out_unरेजिस्टर_pernet:
	unरेजिस्टर_pernet_subsys(&pfkey_net_ops);
out_unरेजिस्टर_key_proto:
	proto_unरेजिस्टर(&key_proto);
	जाओ out;
पूर्ण

module_init(ipsec_pfkey_init);
module_निकास(ipsec_pfkey_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_KEY);
