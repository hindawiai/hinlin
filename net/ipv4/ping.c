<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		"Ping" sockets
 *
 * Based on ipv4/udp.c code.
 *
 * Authors:	Vasiliy Kulikov / Openwall (क्रम Linux 2.6),
 *		Pavel Kankovsky (क्रम Linux 2.4.32)
 *
 * Pavel gave all rights to bugs to Vasiliy,
 * none of the bugs are Pavel's now.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <net/snmp.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/protocol.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/export.h>
#समावेश <net/sock.h>
#समावेश <net/ping.h>
#समावेश <net/udp.h>
#समावेश <net/route.h>
#समावेश <net/inet_common.h>
#समावेश <net/checksum.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/in6.h>
#समावेश <linux/icmpv6.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6.h>
#समावेश <net/transp_v6.h>
#पूर्ण_अगर

काष्ठा ping_table अणु
	काष्ठा hlist_nulls_head	hash[PING_HTABLE_SIZE];
	rwlock_t		lock;
पूर्ण;

अटल काष्ठा ping_table ping_table;
काष्ठा pingv6_ops pingv6_ops;
EXPORT_SYMBOL_GPL(pingv6_ops);

अटल u16 ping_port_rover;

अटल अंतरभूत u32 ping_hashfn(स्थिर काष्ठा net *net, u32 num, u32 mask)
अणु
	u32 res = (num + net_hash_mix(net)) & mask;

	pr_debug("hash(%u) = %u\n", num, res);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(ping_hash);

अटल अंतरभूत काष्ठा hlist_nulls_head *ping_hashslot(काष्ठा ping_table *table,
					     काष्ठा net *net, अचिन्हित पूर्णांक num)
अणु
	वापस &table->hash[ping_hashfn(net, num, PING_HTABLE_MASK)];
पूर्ण

पूर्णांक ping_get_port(काष्ठा sock *sk, अचिन्हित लघु ident)
अणु
	काष्ठा hlist_nulls_node *node;
	काष्ठा hlist_nulls_head *hlist;
	काष्ठा inet_sock *isk, *isk2;
	काष्ठा sock *sk2 = शून्य;

	isk = inet_sk(sk);
	ग_लिखो_lock_bh(&ping_table.lock);
	अगर (ident == 0) अणु
		u32 i;
		u16 result = ping_port_rover + 1;

		क्रम (i = 0; i < (1L << 16); i++, result++) अणु
			अगर (!result)
				result++; /* aव्योम zero */
			hlist = ping_hashslot(&ping_table, sock_net(sk),
					    result);
			ping_portaddr_क्रम_each_entry(sk2, node, hlist) अणु
				isk2 = inet_sk(sk2);

				अगर (isk2->inet_num == result)
					जाओ next_port;
			पूर्ण

			/* found */
			ping_port_rover = ident = result;
			अवरोध;
next_port:
			;
		पूर्ण
		अगर (i >= (1L << 16))
			जाओ fail;
	पूर्ण अन्यथा अणु
		hlist = ping_hashslot(&ping_table, sock_net(sk), ident);
		ping_portaddr_क्रम_each_entry(sk2, node, hlist) अणु
			isk2 = inet_sk(sk2);

			/* BUG? Why is this reuse and not reuseaddr? ping.c
			 * करोesn't turn off SO_REUSEADDR, and it doesn't expect
			 * that other ping processes can steal its packets.
			 */
			अगर ((isk2->inet_num == ident) &&
			    (sk2 != sk) &&
			    (!sk2->sk_reuse || !sk->sk_reuse))
				जाओ fail;
		पूर्ण
	पूर्ण

	pr_debug("found port/ident = %d\n", ident);
	isk->inet_num = ident;
	अगर (sk_unhashed(sk)) अणु
		pr_debug("was not hashed\n");
		sock_hold(sk);
		hlist_nulls_add_head(&sk->sk_nulls_node, hlist);
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	पूर्ण
	ग_लिखो_unlock_bh(&ping_table.lock);
	वापस 0;

fail:
	ग_लिखो_unlock_bh(&ping_table.lock);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ping_get_port);

पूर्णांक ping_hash(काष्ठा sock *sk)
अणु
	pr_debug("ping_hash(sk->port=%u)\n", inet_sk(sk)->inet_num);
	BUG(); /* "Please do not press this button again." */

	वापस 0;
पूर्ण

व्योम ping_unhash(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *isk = inet_sk(sk);

	pr_debug("ping_unhash(isk=%p,isk->num=%u)\n", isk, isk->inet_num);
	ग_लिखो_lock_bh(&ping_table.lock);
	अगर (sk_hashed(sk)) अणु
		hlist_nulls_del(&sk->sk_nulls_node);
		sk_nulls_node_init(&sk->sk_nulls_node);
		sock_put(sk);
		isk->inet_num = 0;
		isk->inet_sport = 0;
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	पूर्ण
	ग_लिखो_unlock_bh(&ping_table.lock);
पूर्ण
EXPORT_SYMBOL_GPL(ping_unhash);

अटल काष्ठा sock *ping_lookup(काष्ठा net *net, काष्ठा sk_buff *skb, u16 ident)
अणु
	काष्ठा hlist_nulls_head *hslot = ping_hashslot(&ping_table, net, ident);
	काष्ठा sock *sk = शून्य;
	काष्ठा inet_sock *isk;
	काष्ठा hlist_nulls_node *hnode;
	पूर्णांक dअगर = skb->dev->अगरindex;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		pr_debug("try to find: num = %d, daddr = %pI4, dif = %d\n",
			 (पूर्णांक)ident, &ip_hdr(skb)->daddr, dअगर);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		pr_debug("try to find: num = %d, daddr = %pI6c, dif = %d\n",
			 (पूर्णांक)ident, &ipv6_hdr(skb)->daddr, dअगर);
#पूर्ण_अगर
	पूर्ण

	पढ़ो_lock_bh(&ping_table.lock);

	ping_portaddr_क्रम_each_entry(sk, hnode, hslot) अणु
		isk = inet_sk(sk);

		pr_debug("iterate\n");
		अगर (isk->inet_num != ident)
			जारी;

		अगर (skb->protocol == htons(ETH_P_IP) &&
		    sk->sk_family == AF_INET) अणु
			pr_debug("found: %p: num=%d, daddr=%pI4, dif=%d\n", sk,
				 (पूर्णांक) isk->inet_num, &isk->inet_rcv_saddr,
				 sk->sk_bound_dev_अगर);

			अगर (isk->inet_rcv_saddr &&
			    isk->inet_rcv_saddr != ip_hdr(skb)->daddr)
				जारी;
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6) &&
			   sk->sk_family == AF_INET6) अणु

			pr_debug("found: %p: num=%d, daddr=%pI6c, dif=%d\n", sk,
				 (पूर्णांक) isk->inet_num,
				 &sk->sk_v6_rcv_saddr,
				 sk->sk_bound_dev_अगर);

			अगर (!ipv6_addr_any(&sk->sk_v6_rcv_saddr) &&
			    !ipv6_addr_equal(&sk->sk_v6_rcv_saddr,
					     &ipv6_hdr(skb)->daddr))
				जारी;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण

		अगर (sk->sk_bound_dev_अगर && sk->sk_bound_dev_अगर != dअगर)
			जारी;

		sock_hold(sk);
		जाओ निकास;
	पूर्ण

	sk = शून्य;
निकास:
	पढ़ो_unlock_bh(&ping_table.lock);

	वापस sk;
पूर्ण

अटल व्योम inet_get_ping_group_range_net(काष्ठा net *net, kgid_t *low,
					  kgid_t *high)
अणु
	kgid_t *data = net->ipv4.ping_group_range.range;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqbegin(&net->ipv4.ping_group_range.lock);

		*low = data[0];
		*high = data[1];
	पूर्ण जबतक (पढ़ो_seqretry(&net->ipv4.ping_group_range.lock, seq));
पूर्ण


पूर्णांक ping_init_sock(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	kgid_t group = current_egid();
	काष्ठा group_info *group_info;
	पूर्णांक i;
	kgid_t low, high;
	पूर्णांक ret = 0;

	अगर (sk->sk_family == AF_INET6)
		sk->sk_ipv6only = 1;

	inet_get_ping_group_range_net(net, &low, &high);
	अगर (gid_lte(low, group) && gid_lte(group, high))
		वापस 0;

	group_info = get_current_groups();
	क्रम (i = 0; i < group_info->ngroups; i++) अणु
		kgid_t gid = group_info->gid[i];

		अगर (gid_lte(low, gid) && gid_lte(gid, high))
			जाओ out_release_group;
	पूर्ण

	ret = -EACCES;

out_release_group:
	put_group_info(group_info);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ping_init_sock);

व्योम ping_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	pr_debug("ping_close(sk=%p,sk->num=%u)\n",
		 inet_sk(sk), inet_sk(sk)->inet_num);
	pr_debug("isk->refcnt = %d\n", refcount_पढ़ो(&sk->sk_refcnt));

	sk_common_release(sk);
पूर्ण
EXPORT_SYMBOL_GPL(ping_बंद);

/* Checks the bind address and possibly modअगरies sk->sk_bound_dev_अगर. */
अटल पूर्णांक ping_check_bind_addr(काष्ठा sock *sk, काष्ठा inet_sock *isk,
				काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा net *net = sock_net(sk);
	अगर (sk->sk_family == AF_INET) अणु
		काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *) uaddr;
		पूर्णांक chk_addr_ret;

		अगर (addr_len < माप(*addr))
			वापस -EINVAL;

		अगर (addr->sin_family != AF_INET &&
		    !(addr->sin_family == AF_UNSPEC &&
		      addr->sin_addr.s_addr == htonl(INADDR_ANY)))
			वापस -EAFNOSUPPORT;

		pr_debug("ping_check_bind_addr(sk=%p,addr=%pI4,port=%d)\n",
			 sk, &addr->sin_addr.s_addr, ntohs(addr->sin_port));

		अगर (addr->sin_addr.s_addr == htonl(INADDR_ANY))
			chk_addr_ret = RTN_LOCAL;
		अन्यथा
			chk_addr_ret = inet_addr_type(net, addr->sin_addr.s_addr);

		अगर ((!inet_can_nonlocal_bind(net, isk) &&
		     chk_addr_ret != RTN_LOCAL) ||
		    chk_addr_ret == RTN_MULTICAST ||
		    chk_addr_ret == RTN_BROADCAST)
			वापस -EADDRNOTAVAIL;

#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (sk->sk_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *addr = (काष्ठा sockaddr_in6 *) uaddr;
		पूर्णांक addr_type, scoped, has_addr;
		काष्ठा net_device *dev = शून्य;

		अगर (addr_len < माप(*addr))
			वापस -EINVAL;

		अगर (addr->sin6_family != AF_INET6)
			वापस -EAFNOSUPPORT;

		pr_debug("ping_check_bind_addr(sk=%p,addr=%pI6c,port=%d)\n",
			 sk, addr->sin6_addr.s6_addr, ntohs(addr->sin6_port));

		addr_type = ipv6_addr_type(&addr->sin6_addr);
		scoped = __ipv6_addr_needs_scope_id(addr_type);
		अगर ((addr_type != IPV6_ADDR_ANY &&
		     !(addr_type & IPV6_ADDR_UNICAST)) ||
		    (scoped && !addr->sin6_scope_id))
			वापस -EINVAL;

		rcu_पढ़ो_lock();
		अगर (addr->sin6_scope_id) अणु
			dev = dev_get_by_index_rcu(net, addr->sin6_scope_id);
			अगर (!dev) अणु
				rcu_पढ़ो_unlock();
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		has_addr = pingv6_ops.ipv6_chk_addr(net, &addr->sin6_addr, dev,
						    scoped);
		rcu_पढ़ो_unlock();

		अगर (!(ipv6_can_nonlocal_bind(net, isk) || has_addr ||
		      addr_type == IPV6_ADDR_ANY))
			वापस -EADDRNOTAVAIL;

		अगर (scoped)
			sk->sk_bound_dev_अगर = addr->sin6_scope_id;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस -EAFNOSUPPORT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ping_set_saddr(काष्ठा sock *sk, काष्ठा sockaddr *saddr)
अणु
	अगर (saddr->sa_family == AF_INET) अणु
		काष्ठा inet_sock *isk = inet_sk(sk);
		काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *) saddr;
		isk->inet_rcv_saddr = isk->inet_saddr = addr->sin_addr.s_addr;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (saddr->sa_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *addr = (काष्ठा sockaddr_in6 *) saddr;
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);
		sk->sk_v6_rcv_saddr = np->saddr = addr->sin6_addr;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * We need our own bind because there are no privileged id's == local ports.
 * Moreover, we करोn't allow binding to multi- and broadcast addresses.
 */

पूर्णांक ping_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा inet_sock *isk = inet_sk(sk);
	अचिन्हित लघु snum;
	पूर्णांक err;
	पूर्णांक dअगर = sk->sk_bound_dev_अगर;

	err = ping_check_bind_addr(sk, isk, uaddr, addr_len);
	अगर (err)
		वापस err;

	lock_sock(sk);

	err = -EINVAL;
	अगर (isk->inet_num != 0)
		जाओ out;

	err = -EADDRINUSE;
	snum = ntohs(((काष्ठा sockaddr_in *)uaddr)->sin_port);
	अगर (ping_get_port(sk, snum) != 0) अणु
		/* Restore possibly modअगरied sk->sk_bound_dev_अगर by ping_check_bind_addr(). */
		sk->sk_bound_dev_अगर = dअगर;
		जाओ out;
	पूर्ण
	ping_set_saddr(sk, uaddr);

	pr_debug("after bind(): num = %hu, dif = %d\n",
		 isk->inet_num,
		 sk->sk_bound_dev_अगर);

	err = 0;
	अगर (sk->sk_family == AF_INET && isk->inet_rcv_saddr)
		sk->sk_userlocks |= SOCK_BINDADDR_LOCK;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6 && !ipv6_addr_any(&sk->sk_v6_rcv_saddr))
		sk->sk_userlocks |= SOCK_BINDADDR_LOCK;
#पूर्ण_अगर

	अगर (snum)
		sk->sk_userlocks |= SOCK_BINDPORT_LOCK;
	isk->inet_sport = htons(isk->inet_num);
	isk->inet_daddr = 0;
	isk->inet_dport = 0;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		स_रखो(&sk->sk_v6_daddr, 0, माप(sk->sk_v6_daddr));
#पूर्ण_अगर

	sk_dst_reset(sk);
out:
	release_sock(sk);
	pr_debug("ping_v4_bind -> %d\n", err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ping_bind);

/*
 * Is this a supported type of ICMP message?
 */

अटल अंतरभूत पूर्णांक ping_supported(पूर्णांक family, पूर्णांक type, पूर्णांक code)
अणु
	वापस (family == AF_INET && type == ICMP_ECHO && code == 0) ||
	       (family == AF_INET && type == ICMP_EXT_ECHO && code == 0) ||
	       (family == AF_INET6 && type == ICMPV6_ECHO_REQUEST && code == 0) ||
	       (family == AF_INET6 && type == ICMPV6_EXT_ECHO_REQUEST && code == 0);
पूर्ण

/*
 * This routine is called by the ICMP module when it माला_लो some
 * sort of error condition.
 */

व्योम ping_err(काष्ठा sk_buff *skb, पूर्णांक offset, u32 info)
अणु
	पूर्णांक family;
	काष्ठा icmphdr *icmph;
	काष्ठा inet_sock *inet_sock;
	पूर्णांक type;
	पूर्णांक code;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा sock *sk;
	पूर्णांक harderr;
	पूर्णांक err;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		family = AF_INET;
		type = icmp_hdr(skb)->type;
		code = icmp_hdr(skb)->code;
		icmph = (काष्ठा icmphdr *)(skb->data + offset);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		family = AF_INET6;
		type = icmp6_hdr(skb)->icmp6_type;
		code = icmp6_hdr(skb)->icmp6_code;
		icmph = (काष्ठा icmphdr *) (skb->data + offset);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	/* We assume the packet has alपढ़ोy been checked by icmp_unreach */

	अगर (!ping_supported(family, icmph->type, icmph->code))
		वापस;

	pr_debug("ping_err(proto=0x%x,type=%d,code=%d,id=%04x,seq=%04x)\n",
		 skb->protocol, type, code, ntohs(icmph->un.echo.id),
		 ntohs(icmph->un.echo.sequence));

	sk = ping_lookup(net, skb, ntohs(icmph->un.echo.id));
	अगर (!sk) अणु
		pr_debug("no socket, dropping\n");
		वापस;	/* No socket क्रम error */
	पूर्ण
	pr_debug("err on socket %p\n", sk);

	err = 0;
	harderr = 0;
	inet_sock = inet_sk(sk);

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		चयन (type) अणु
		शेष:
		हाल ICMP_TIME_EXCEEDED:
			err = EHOSTUNREACH;
			अवरोध;
		हाल ICMP_SOURCE_QUENCH:
			/* This is not a real error but ping wants to see it.
			 * Report it with some fake त्रुटि_सं.
			 */
			err = EREMOTEIO;
			अवरोध;
		हाल ICMP_PARAMETERPROB:
			err = EPROTO;
			harderr = 1;
			अवरोध;
		हाल ICMP_DEST_UNREACH:
			अगर (code == ICMP_FRAG_NEEDED) अणु /* Path MTU discovery */
				ipv4_sk_update_pmtu(skb, sk, info);
				अगर (inet_sock->pmtudisc != IP_PMTUDISC_DONT) अणु
					err = EMSGSIZE;
					harderr = 1;
					अवरोध;
				पूर्ण
				जाओ out;
			पूर्ण
			err = EHOSTUNREACH;
			अगर (code <= NR_ICMP_UNREACH) अणु
				harderr = icmp_err_convert[code].fatal;
				err = icmp_err_convert[code].त्रुटि_सं;
			पूर्ण
			अवरोध;
		हाल ICMP_REसूचीECT:
			/* See ICMP_SOURCE_QUENCH */
			ipv4_sk_redirect(skb, sk);
			err = EREMOTEIO;
			अवरोध;
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		harderr = pingv6_ops.icmpv6_err_convert(type, code, &err);
#पूर्ण_अगर
	पूर्ण

	/*
	 *      RFC1122: OK.  Passes ICMP errors back to application, as per
	 *	4.1.3.3.
	 */
	अगर ((family == AF_INET && !inet_sock->recverr) ||
	    (family == AF_INET6 && !inet6_sk(sk)->recverr)) अणु
		अगर (!harderr || sk->sk_state != TCP_ESTABLISHED)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (family == AF_INET) अणु
			ip_icmp_error(sk, skb, err, 0 /* no remote port */,
				      info, (u8 *)icmph);
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण अन्यथा अगर (family == AF_INET6) अणु
			pingv6_ops.ipv6_icmp_error(sk, skb, err, 0,
						   info, (u8 *)icmph);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	sk->sk_err = err;
	sk->sk_error_report(sk);
out:
	sock_put(sk);
पूर्ण
EXPORT_SYMBOL_GPL(ping_err);

/*
 *	Copy and checksum an ICMP Echo packet from user space पूर्णांकo a buffer
 *	starting from the payload.
 */

पूर्णांक ping_getfrag(व्योम *from, अक्षर *to,
		 पूर्णांक offset, पूर्णांक fraglen, पूर्णांक odd, काष्ठा sk_buff *skb)
अणु
	काष्ठा pingfakehdr *pfh = (काष्ठा pingfakehdr *)from;

	अगर (offset == 0) अणु
		fraglen -= माप(काष्ठा icmphdr);
		अगर (fraglen < 0)
			BUG();
		अगर (!csum_and_copy_from_iter_full(to + माप(काष्ठा icmphdr),
			    fraglen, &pfh->wcheck,
			    &pfh->msg->msg_iter))
			वापस -EFAULT;
	पूर्ण अन्यथा अगर (offset < माप(काष्ठा icmphdr)) अणु
			BUG();
	पूर्ण अन्यथा अणु
		अगर (!csum_and_copy_from_iter_full(to, fraglen, &pfh->wcheck,
					    &pfh->msg->msg_iter))
			वापस -EFAULT;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
	/* For IPv6, checksum each skb as we go aदीर्घ, as expected by
	 * icmpv6_push_pending_frames. For IPv4, accumulate the checksum in
	 * wcheck, it will be finalized in ping_v4_push_pending_frames.
	 */
	अगर (pfh->family == AF_INET6) अणु
		skb->csum = pfh->wcheck;
		skb->ip_summed = CHECKSUM_NONE;
		pfh->wcheck = 0;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ping_getfrag);

अटल पूर्णांक ping_v4_push_pending_frames(काष्ठा sock *sk, काष्ठा pingfakehdr *pfh,
				       काष्ठा flowi4 *fl4)
अणु
	काष्ठा sk_buff *skb = skb_peek(&sk->sk_ग_लिखो_queue);

	अगर (!skb)
		वापस 0;
	pfh->wcheck = csum_partial((अक्षर *)&pfh->icmph,
		माप(काष्ठा icmphdr), pfh->wcheck);
	pfh->icmph.checksum = csum_fold(pfh->wcheck);
	स_नकल(icmp_hdr(skb), &pfh->icmph, माप(काष्ठा icmphdr));
	skb->ip_summed = CHECKSUM_NONE;
	वापस ip_push_pending_frames(sk, fl4);
पूर्ण

पूर्णांक ping_common_sendmsg(पूर्णांक family, काष्ठा msghdr *msg, माप_प्रकार len,
			व्योम *user_icmph, माप_प्रकार icmph_len)
अणु
	u8 type, code;

	अगर (len > 0xFFFF)
		वापस -EMSGSIZE;

	/* Must have at least a full ICMP header. */
	अगर (len < icmph_len)
		वापस -EINVAL;

	/*
	 *	Check the flags.
	 */

	/* Mirror BSD error message compatibility */
	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	/*
	 *	Fetch the ICMP header provided by the userland.
	 *	iovec is modअगरied! The ICMP header is consumed.
	 */
	अगर (स_नकल_from_msg(user_icmph, msg, icmph_len))
		वापस -EFAULT;

	अगर (family == AF_INET) अणु
		type = ((काष्ठा icmphdr *) user_icmph)->type;
		code = ((काष्ठा icmphdr *) user_icmph)->code;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (family == AF_INET6) अणु
		type = ((काष्ठा icmp6hdr *) user_icmph)->icmp6_type;
		code = ((काष्ठा icmp6hdr *) user_icmph)->icmp6_code;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	अगर (!ping_supported(family, type, code))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ping_common_sendmsg);

अटल पूर्णांक ping_v4_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा flowi4 fl4;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipcm_cookie ipc;
	काष्ठा icmphdr user_icmph;
	काष्ठा pingfakehdr pfh;
	काष्ठा rtable *rt = शून्य;
	काष्ठा ip_options_data opt_copy;
	पूर्णांक मुक्त = 0;
	__be32 saddr, daddr, faddr;
	u8  tos;
	पूर्णांक err;

	pr_debug("ping_v4_sendmsg(sk=%p,sk->num=%u)\n", inet, inet->inet_num);

	err = ping_common_sendmsg(AF_INET, msg, len, &user_icmph,
				  माप(user_icmph));
	अगर (err)
		वापस err;

	/*
	 *	Get and verअगरy the address.
	 */

	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_in *, usin, msg->msg_name);
		अगर (msg->msg_namelen < माप(*usin))
			वापस -EINVAL;
		अगर (usin->sin_family != AF_INET)
			वापस -EAFNOSUPPORT;
		daddr = usin->sin_addr.s_addr;
		/* no remote port */
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -EDESTADDRREQ;
		daddr = inet->inet_daddr;
		/* no remote port */
	पूर्ण

	ipcm_init_sk(&ipc, inet);

	अगर (msg->msg_controllen) अणु
		err = ip_cmsg_send(sk, msg, &ipc, false);
		अगर (unlikely(err)) अणु
			kमुक्त(ipc.opt);
			वापस err;
		पूर्ण
		अगर (ipc.opt)
			मुक्त = 1;
	पूर्ण
	अगर (!ipc.opt) अणु
		काष्ठा ip_options_rcu *inet_opt;

		rcu_पढ़ो_lock();
		inet_opt = rcu_dereference(inet->inet_opt);
		अगर (inet_opt) अणु
			स_नकल(&opt_copy, inet_opt,
			       माप(*inet_opt) + inet_opt->opt.optlen);
			ipc.opt = &opt_copy.opt;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	saddr = ipc.addr;
	ipc.addr = faddr = daddr;

	अगर (ipc.opt && ipc.opt->opt.srr) अणु
		अगर (!daddr) अणु
			err = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		faddr = ipc.opt->opt.faddr;
	पूर्ण
	tos = get_rttos(&ipc, inet);
	अगर (sock_flag(sk, SOCK_LOCALROUTE) ||
	    (msg->msg_flags & MSG_DONTROUTE) ||
	    (ipc.opt && ipc.opt->opt.is_strictroute)) अणु
		tos |= RTO_ONLINK;
	पूर्ण

	अगर (ipv4_is_multicast(daddr)) अणु
		अगर (!ipc.oअगर || netअगर_index_is_l3_master(sock_net(sk), ipc.oअगर))
			ipc.oअगर = inet->mc_index;
		अगर (!saddr)
			saddr = inet->mc_addr;
	पूर्ण अन्यथा अगर (!ipc.oअगर)
		ipc.oअगर = inet->uc_index;

	flowi4_init_output(&fl4, ipc.oअगर, ipc.sockc.mark, tos,
			   RT_SCOPE_UNIVERSE, sk->sk_protocol,
			   inet_sk_flowi_flags(sk), faddr, saddr, 0, 0,
			   sk->sk_uid);

	fl4.fl4_icmp_type = user_icmph.type;
	fl4.fl4_icmp_code = user_icmph.code;

	security_sk_classअगरy_flow(sk, flowi4_to_flowi_common(&fl4));
	rt = ip_route_output_flow(net, &fl4, sk);
	अगर (IS_ERR(rt)) अणु
		err = PTR_ERR(rt);
		rt = शून्य;
		अगर (err == -ENETUNREACH)
			IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
		जाओ out;
	पूर्ण

	err = -EACCES;
	अगर ((rt->rt_flags & RTCF_BROADCAST) &&
	    !sock_flag(sk, SOCK_BROADCAST))
		जाओ out;

	अगर (msg->msg_flags & MSG_CONFIRM)
		जाओ करो_confirm;
back_from_confirm:

	अगर (!ipc.addr)
		ipc.addr = fl4.daddr;

	lock_sock(sk);

	pfh.icmph.type = user_icmph.type; /* alपढ़ोy checked */
	pfh.icmph.code = user_icmph.code; /* ditto */
	pfh.icmph.checksum = 0;
	pfh.icmph.un.echo.id = inet->inet_sport;
	pfh.icmph.un.echo.sequence = user_icmph.un.echo.sequence;
	pfh.msg = msg;
	pfh.wcheck = 0;
	pfh.family = AF_INET;

	err = ip_append_data(sk, &fl4, ping_getfrag, &pfh, len,
			0, &ipc, &rt, msg->msg_flags);
	अगर (err)
		ip_flush_pending_frames(sk);
	अन्यथा
		err = ping_v4_push_pending_frames(sk, &pfh, &fl4);
	release_sock(sk);

out:
	ip_rt_put(rt);
out_मुक्त:
	अगर (मुक्त)
		kमुक्त(ipc.opt);
	अगर (!err) अणु
		icmp_out_count(sock_net(sk), user_icmph.type);
		वापस len;
	पूर्ण
	वापस err;

करो_confirm:
	अगर (msg->msg_flags & MSG_PROBE)
		dst_confirm_neigh(&rt->dst, &fl4.daddr);
	अगर (!(msg->msg_flags & MSG_PROBE) || len)
		जाओ back_from_confirm;
	err = 0;
	जाओ out;
पूर्ण

पूर्णांक ping_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक noblock,
		 पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा inet_sock *isk = inet_sk(sk);
	पूर्णांक family = sk->sk_family;
	काष्ठा sk_buff *skb;
	पूर्णांक copied, err;

	pr_debug("ping_recvmsg(sk=%p,sk->num=%u)\n", isk, isk->inet_num);

	err = -EOPNOTSUPP;
	अगर (flags & MSG_OOB)
		जाओ out;

	अगर (flags & MSG_ERRQUEUE)
		वापस inet_recv_error(sk, msg, len, addr_len);

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (copied > len) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	/* Don't bother checking the checksum */
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ करोne;

	sock_recv_बारtamp(msg, sk, skb);

	/* Copy the address and add cmsg data. */
	अगर (family == AF_INET) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_in *, sin, msg->msg_name);

		अगर (sin) अणु
			sin->sin_family = AF_INET;
			sin->sin_port = 0 /* skb->h.uh->source */;
			sin->sin_addr.s_addr = ip_hdr(skb)->saddr;
			स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
			*addr_len = माप(*sin);
		पूर्ण

		अगर (isk->cmsg_flags)
			ip_cmsg_recv(msg, skb);

#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (family == AF_INET6) अणु
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);
		काष्ठा ipv6hdr *ip6 = ipv6_hdr(skb);
		DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, msg->msg_name);

		अगर (sin6) अणु
			sin6->sin6_family = AF_INET6;
			sin6->sin6_port = 0;
			sin6->sin6_addr = ip6->saddr;
			sin6->sin6_flowinfo = 0;
			अगर (np->sndflow)
				sin6->sin6_flowinfo = ip6_flowinfo(ip6);
			sin6->sin6_scope_id =
				ipv6_अगरace_scope_id(&sin6->sin6_addr,
						    inet6_iअगर(skb));
			*addr_len = माप(*sin6);
		पूर्ण

		अगर (inet6_sk(sk)->rxopt.all)
			pingv6_ops.ip6_datagram_recv_common_ctl(sk, msg, skb);
		अगर (skb->protocol == htons(ETH_P_IPV6) &&
		    inet6_sk(sk)->rxopt.all)
			pingv6_ops.ip6_datagram_recv_specअगरic_ctl(sk, msg, skb);
		अन्यथा अगर (skb->protocol == htons(ETH_P_IP) && isk->cmsg_flags)
			ip_cmsg_recv(msg, skb);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	err = copied;

करोne:
	skb_मुक्त_datagram(sk, skb);
out:
	pr_debug("ping_recvmsg -> %d\n", err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ping_recvmsg);

पूर्णांक ping_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	pr_debug("ping_queue_rcv_skb(sk=%p,sk->num=%d,skb=%p)\n",
		 inet_sk(sk), inet_sk(sk)->inet_num, skb);
	अगर (sock_queue_rcv_skb(sk, skb) < 0) अणु
		kमुक्त_skb(skb);
		pr_debug("ping_queue_rcv_skb -> failed\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ping_queue_rcv_skb);


/*
 *	All we need to करो is get the socket.
 */

bool ping_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा icmphdr *icmph = icmp_hdr(skb);
	bool rc = false;

	/* We assume the packet has alपढ़ोy been checked by icmp_rcv */

	pr_debug("ping_rcv(skb=%p,id=%04x,seq=%04x)\n",
		 skb, ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.sequence));

	/* Push ICMP header back */
	skb_push(skb, skb->data - (u8 *)icmph);

	sk = ping_lookup(net, skb, ntohs(icmph->un.echo.id));
	अगर (sk) अणु
		काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

		pr_debug("rcv on socket %p\n", sk);
		अगर (skb2 && !ping_queue_rcv_skb(sk, skb2))
			rc = true;
		sock_put(sk);
	पूर्ण

	अगर (!rc)
		pr_debug("no socket, dropping\n");

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ping_rcv);

काष्ठा proto ping_prot = अणु
	.name =		"PING",
	.owner =	THIS_MODULE,
	.init =		ping_init_sock,
	.बंद =	ping_बंद,
	.connect =	ip4_datagram_connect,
	.disconnect =	__udp_disconnect,
	.setsockopt =	ip_setsockopt,
	.माला_लोockopt =	ip_माला_लोockopt,
	.sendmsg =	ping_v4_sendmsg,
	.recvmsg =	ping_recvmsg,
	.bind =		ping_bind,
	.backlog_rcv =	ping_queue_rcv_skb,
	.release_cb =	ip4_datagram_release_cb,
	.hash =		ping_hash,
	.unhash =	ping_unhash,
	.get_port =	ping_get_port,
	.obj_size =	माप(काष्ठा inet_sock),
पूर्ण;
EXPORT_SYMBOL(ping_prot);

#अगर_घोषित CONFIG_PROC_FS

अटल काष्ठा sock *ping_get_first(काष्ठा seq_file *seq, पूर्णांक start)
अणु
	काष्ठा sock *sk;
	काष्ठा ping_iter_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);

	क्रम (state->bucket = start; state->bucket < PING_HTABLE_SIZE;
	     ++state->bucket) अणु
		काष्ठा hlist_nulls_node *node;
		काष्ठा hlist_nulls_head *hslot;

		hslot = &ping_table.hash[state->bucket];

		अगर (hlist_nulls_empty(hslot))
			जारी;

		sk_nulls_क्रम_each(sk, node, hslot) अणु
			अगर (net_eq(sock_net(sk), net) &&
			    sk->sk_family == state->family)
				जाओ found;
		पूर्ण
	पूर्ण
	sk = शून्य;
found:
	वापस sk;
पूर्ण

अटल काष्ठा sock *ping_get_next(काष्ठा seq_file *seq, काष्ठा sock *sk)
अणु
	काष्ठा ping_iter_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);

	करो अणु
		sk = sk_nulls_next(sk);
	पूर्ण जबतक (sk && (!net_eq(sock_net(sk), net)));

	अगर (!sk)
		वापस ping_get_first(seq, state->bucket + 1);
	वापस sk;
पूर्ण

अटल काष्ठा sock *ping_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा sock *sk = ping_get_first(seq, 0);

	अगर (sk)
		जबतक (pos && (sk = ping_get_next(seq, sk)) != शून्य)
			--pos;
	वापस pos ? शून्य : sk;
पूर्ण

व्योम *ping_seq_start(काष्ठा seq_file *seq, loff_t *pos, sa_family_t family)
	__acquires(ping_table.lock)
अणु
	काष्ठा ping_iter_state *state = seq->निजी;
	state->bucket = 0;
	state->family = family;

	पढ़ो_lock_bh(&ping_table.lock);

	वापस *pos ? ping_get_idx(seq, *pos-1) : SEQ_START_TOKEN;
पूर्ण
EXPORT_SYMBOL_GPL(ping_seq_start);

अटल व्योम *ping_v4_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस ping_seq_start(seq, pos, AF_INET);
पूर्ण

व्योम *ping_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा sock *sk;

	अगर (v == SEQ_START_TOKEN)
		sk = ping_get_idx(seq, 0);
	अन्यथा
		sk = ping_get_next(seq, v);

	++*pos;
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(ping_seq_next);

व्योम ping_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(ping_table.lock)
अणु
	पढ़ो_unlock_bh(&ping_table.lock);
पूर्ण
EXPORT_SYMBOL_GPL(ping_seq_stop);

अटल व्योम ping_v4_क्रमmat_sock(काष्ठा sock *sp, काष्ठा seq_file *f,
		पूर्णांक bucket)
अणु
	काष्ठा inet_sock *inet = inet_sk(sp);
	__be32 dest = inet->inet_daddr;
	__be32 src = inet->inet_rcv_saddr;
	__u16 destp = ntohs(inet->inet_dport);
	__u16 srcp = ntohs(inet->inet_sport);

	seq_म_लिखो(f, "%5d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %u",
		bucket, src, srcp, dest, destp, sp->sk_state,
		sk_wmem_alloc_get(sp),
		sk_rmem_alloc_get(sp),
		0, 0L, 0,
		from_kuid_munged(seq_user_ns(f), sock_i_uid(sp)),
		0, sock_i_ino(sp),
		refcount_पढ़ो(&sp->sk_refcnt), sp,
		atomic_पढ़ो(&sp->sk_drops));
पूर्ण

अटल पूर्णांक ping_v4_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	seq_setwidth(seq, 127);
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "  sl  local_address rem_address   st tx_queue "
			   "rx_queue tr tm->when retrnsmt   uid  timeout "
			   "inode ref pointer drops");
	अन्यथा अणु
		काष्ठा ping_iter_state *state = seq->निजी;

		ping_v4_क्रमmat_sock(v, seq, state->bucket);
	पूर्ण
	seq_pad(seq, '\n');
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ping_v4_seq_ops = अणु
	.start		= ping_v4_seq_start,
	.show		= ping_v4_seq_show,
	.next		= ping_seq_next,
	.stop		= ping_seq_stop,
पूर्ण;

अटल पूर्णांक __net_init ping_v4_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net("icmp", 0444, net->proc_net, &ping_v4_seq_ops,
			माप(काष्ठा ping_iter_state)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ping_v4_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("icmp", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations ping_v4_net_ops = अणु
	.init = ping_v4_proc_init_net,
	.निकास = ping_v4_proc_निकास_net,
पूर्ण;

पूर्णांक __init ping_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&ping_v4_net_ops);
पूर्ण

व्योम ping_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ping_v4_net_ops);
पूर्ण

#पूर्ण_अगर

व्योम __init ping_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PING_HTABLE_SIZE; i++)
		INIT_HLIST_शून्यS_HEAD(&ping_table.hash[i], i);
	rwlock_init(&ping_table.lock);
पूर्ण
