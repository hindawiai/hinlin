<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	PF_INET6 socket protocol family
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Adapted from linux/net/ipv4/af_inet.c
 *
 *	Fixes:
 *	piggy, Karl Knutson	:	Socket protocol table
 *	Hideaki YOSHIFUJI	:	sin6_scope_id support
 *	Arnalकरो Melo		:	check proc_net_create वापस, cleanups
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>
#समावेश <net/udplite.h>
#समावेश <net/tcp.h>
#समावेश <net/ping.h>
#समावेश <net/protocol.h>
#समावेश <net/inet_common.h>
#समावेश <net/route.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/ndisc.h>
#अगर_घोषित CONFIG_IPV6_TUNNEL
#समावेश <net/ip6_tunnel.h>
#पूर्ण_अगर
#समावेश <net/calipso.h>
#समावेश <net/seg6.h>
#समावेश <net/rpl.h>
#समावेश <net/compat.h>
#समावेश <net/xfrm.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/mroute6.h>

#समावेश "ip6_offload.h"

MODULE_AUTHOR("Cast of dozens");
MODULE_DESCRIPTION("IPv6 protocol stack for Linux");
MODULE_LICENSE("GPL");

/* The inetsw6 table contains everything that inet6_create needs to
 * build a new socket.
 */
अटल काष्ठा list_head inetsw6[SOCK_MAX];
अटल DEFINE_SPINLOCK(inetsw6_lock);

काष्ठा ipv6_params ipv6_शेषs = अणु
	.disable_ipv6 = 0,
	.स्वतःconf = 1,
पूर्ण;

अटल पूर्णांक disable_ipv6_mod;

module_param_named(disable, disable_ipv6_mod, पूर्णांक, 0444);
MODULE_PARM_DESC(disable, "Disable IPv6 module such that it is non-functional");

module_param_named(disable_ipv6, ipv6_शेषs.disable_ipv6, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_ipv6, "Disable IPv6 on all interfaces");

module_param_named(स्वतःconf, ipv6_शेषs.स्वतःconf, पूर्णांक, 0444);
MODULE_PARM_DESC(स्वतःconf, "Enable IPv6 address autoconfiguration on all interfaces");

bool ipv6_mod_enabled(व्योम)
अणु
	वापस disable_ipv6_mod == 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_mod_enabled);

अटल __अंतरभूत__ काष्ठा ipv6_pinfo *inet6_sk_generic(काष्ठा sock *sk)
अणु
	स्थिर पूर्णांक offset = sk->sk_prot->obj_size - माप(काष्ठा ipv6_pinfo);

	वापस (काष्ठा ipv6_pinfo *)(((u8 *)sk) + offset);
पूर्ण

अटल पूर्णांक inet6_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			पूर्णांक kern)
अणु
	काष्ठा inet_sock *inet;
	काष्ठा ipv6_pinfo *np;
	काष्ठा sock *sk;
	काष्ठा inet_protosw *answer;
	काष्ठा proto *answer_prot;
	अचिन्हित अक्षर answer_flags;
	पूर्णांक try_loading_module = 0;
	पूर्णांक err;

	अगर (protocol < 0 || protocol >= IPPROTO_MAX)
		वापस -EINVAL;

	/* Look क्रम the requested type/protocol pair. */
lookup_protocol:
	err = -ESOCKTNOSUPPORT;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(answer, &inetsw6[sock->type], list) अणु

		err = 0;
		/* Check the non-wild match. */
		अगर (protocol == answer->protocol) अणु
			अगर (protocol != IPPROTO_IP)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* Check क्रम the two wild हालs. */
			अगर (IPPROTO_IP == protocol) अणु
				protocol = answer->protocol;
				अवरोध;
			पूर्ण
			अगर (IPPROTO_IP == answer->protocol)
				अवरोध;
		पूर्ण
		err = -EPROTONOSUPPORT;
	पूर्ण

	अगर (err) अणु
		अगर (try_loading_module < 2) अणु
			rcu_पढ़ो_unlock();
			/*
			 * Be more specअगरic, e.g. net-pf-10-proto-132-type-1
			 * (net-pf-PF_INET6-proto-IPPROTO_SCTP-type-SOCK_STREAM)
			 */
			अगर (++try_loading_module == 1)
				request_module("net-pf-%d-proto-%d-type-%d",
						PF_INET6, protocol, sock->type);
			/*
			 * Fall back to generic, e.g. net-pf-10-proto-132
			 * (net-pf-PF_INET6-proto-IPPROTO_SCTP)
			 */
			अन्यथा
				request_module("net-pf-%d-proto-%d",
						PF_INET6, protocol);
			जाओ lookup_protocol;
		पूर्ण अन्यथा
			जाओ out_rcu_unlock;
	पूर्ण

	err = -EPERM;
	अगर (sock->type == SOCK_RAW && !kern &&
	    !ns_capable(net->user_ns, CAP_NET_RAW))
		जाओ out_rcu_unlock;

	sock->ops = answer->ops;
	answer_prot = answer->prot;
	answer_flags = answer->flags;
	rcu_पढ़ो_unlock();

	WARN_ON(!answer_prot->slab);

	err = -ENOBUFS;
	sk = sk_alloc(net, PF_INET6, GFP_KERNEL, answer_prot, kern);
	अगर (!sk)
		जाओ out;

	sock_init_data(sock, sk);

	err = 0;
	अगर (INET_PROTOSW_REUSE & answer_flags)
		sk->sk_reuse = SK_CAN_REUSE;

	inet = inet_sk(sk);
	inet->is_icsk = (INET_PROTOSW_ICSK & answer_flags) != 0;

	अगर (SOCK_RAW == sock->type) अणु
		inet->inet_num = protocol;
		अगर (IPPROTO_RAW == protocol)
			inet->hdrincl = 1;
	पूर्ण

	sk->sk_deकाष्ठा		= inet_sock_deकाष्ठा;
	sk->sk_family		= PF_INET6;
	sk->sk_protocol		= protocol;

	sk->sk_backlog_rcv	= answer->prot->backlog_rcv;

	inet_sk(sk)->pinet6 = np = inet6_sk_generic(sk);
	np->hop_limit	= -1;
	np->mcast_hops	= IPV6_DEFAULT_MCASTHOPS;
	np->mc_loop	= 1;
	np->mc_all	= 1;
	np->pmtudisc	= IPV6_PMTUDISC_WANT;
	np->repflow	= net->ipv6.sysctl.flowlabel_reflect & FLOWLABEL_REFLECT_ESTABLISHED;
	sk->sk_ipv6only	= net->ipv6.sysctl.bindv6only;

	/* Init the ipv4 part of the socket since we can have sockets
	 * using v6 API क्रम ipv4.
	 */
	inet->uc_ttl	= -1;

	inet->mc_loop	= 1;
	inet->mc_ttl	= 1;
	inet->mc_index	= 0;
	RCU_INIT_POINTER(inet->mc_list, शून्य);
	inet->rcv_tos	= 0;

	अगर (net->ipv4.sysctl_ip_no_pmtu_disc)
		inet->pmtudisc = IP_PMTUDISC_DONT;
	अन्यथा
		inet->pmtudisc = IP_PMTUDISC_WANT;
	/*
	 * Increment only the relevant sk_prot->socks debug field, this changes
	 * the previous behaviour of incrementing both the equivalent to
	 * answer->prot->socks (inet6_sock_nr) and inet_sock_nr.
	 *
	 * This allows better debug granularity as we'll know exactly how many
	 * UDPv6, TCPv6, etc socks were allocated, not the sum of all IPv6
	 * transport protocol socks. -acme
	 */
	sk_refcnt_debug_inc(sk);

	अगर (inet->inet_num) अणु
		/* It assumes that any protocol which allows
		 * the user to assign a number at socket
		 * creation समय स्वतःmatically shares.
		 */
		inet->inet_sport = htons(inet->inet_num);
		err = sk->sk_prot->hash(sk);
		अगर (err) अणु
			sk_common_release(sk);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (sk->sk_prot->init) अणु
		err = sk->sk_prot->init(sk);
		अगर (err) अणु
			sk_common_release(sk);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!kern) अणु
		err = BPF_CGROUP_RUN_PROG_INET_SOCK(sk);
		अगर (err) अणु
			sk_common_release(sk);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस err;
out_rcu_unlock:
	rcu_पढ़ो_unlock();
	जाओ out;
पूर्ण

अटल पूर्णांक __inet6_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len,
			u32 flags)
अणु
	काष्ठा sockaddr_in6 *addr = (काष्ठा sockaddr_in6 *)uaddr;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net *net = sock_net(sk);
	__be32 v4addr = 0;
	अचिन्हित लघु snum;
	bool saved_ipv6only;
	पूर्णांक addr_type = 0;
	पूर्णांक err = 0;

	अगर (addr->sin6_family != AF_INET6)
		वापस -EAFNOSUPPORT;

	addr_type = ipv6_addr_type(&addr->sin6_addr);
	अगर ((addr_type & IPV6_ADDR_MULTICAST) && sk->sk_type == SOCK_STREAM)
		वापस -EINVAL;

	snum = ntohs(addr->sin6_port);
	अगर (!(flags & BIND_NO_CAP_NET_BIND_SERVICE) &&
	    snum && inet_port_requires_bind_service(net, snum) &&
	    !ns_capable(net->user_ns, CAP_NET_BIND_SERVICE))
		वापस -EACCES;

	अगर (flags & BIND_WITH_LOCK)
		lock_sock(sk);

	/* Check these errors (active socket, द्विगुन bind). */
	अगर (sk->sk_state != TCP_CLOSE || inet->inet_num) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Check अगर the address beदीर्घs to the host. */
	अगर (addr_type == IPV6_ADDR_MAPPED) अणु
		काष्ठा net_device *dev = शून्य;
		पूर्णांक chk_addr_ret;

		/* Binding to v4-mapped address on a v6-only socket
		 * makes no sense
		 */
		अगर (sk->sk_ipv6only) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		rcu_पढ़ो_lock();
		अगर (sk->sk_bound_dev_अगर) अणु
			dev = dev_get_by_index_rcu(net, sk->sk_bound_dev_अगर);
			अगर (!dev) अणु
				err = -ENODEV;
				जाओ out_unlock;
			पूर्ण
		पूर्ण

		/* Reproduce AF_INET checks to make the bindings consistent */
		v4addr = addr->sin6_addr.s6_addr32[3];
		chk_addr_ret = inet_addr_type_dev_table(net, dev, v4addr);
		rcu_पढ़ो_unlock();

		अगर (!inet_can_nonlocal_bind(net, inet) &&
		    v4addr != htonl(INADDR_ANY) &&
		    chk_addr_ret != RTN_LOCAL &&
		    chk_addr_ret != RTN_MULTICAST &&
		    chk_addr_ret != RTN_BROADCAST) अणु
			err = -EADDRNOTAVAIL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (addr_type != IPV6_ADDR_ANY) अणु
			काष्ठा net_device *dev = शून्य;

			rcu_पढ़ो_lock();
			अगर (__ipv6_addr_needs_scope_id(addr_type)) अणु
				अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
				    addr->sin6_scope_id) अणु
					/* Override any existing binding, अगर another one
					 * is supplied by user.
					 */
					sk->sk_bound_dev_अगर = addr->sin6_scope_id;
				पूर्ण

				/* Binding to link-local address requires an पूर्णांकerface */
				अगर (!sk->sk_bound_dev_अगर) अणु
					err = -EINVAL;
					जाओ out_unlock;
				पूर्ण
			पूर्ण

			अगर (sk->sk_bound_dev_अगर) अणु
				dev = dev_get_by_index_rcu(net, sk->sk_bound_dev_अगर);
				अगर (!dev) अणु
					err = -ENODEV;
					जाओ out_unlock;
				पूर्ण
			पूर्ण

			/* ipv4 addr of the socket is invalid.  Only the
			 * unspecअगरied and mapped address have a v4 equivalent.
			 */
			v4addr = LOOPBACK4_IPV6;
			अगर (!(addr_type & IPV6_ADDR_MULTICAST))	अणु
				अगर (!ipv6_can_nonlocal_bind(net, inet) &&
				    !ipv6_chk_addr(net, &addr->sin6_addr,
						   dev, 0)) अणु
					err = -EADDRNOTAVAIL;
					जाओ out_unlock;
				पूर्ण
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण
	पूर्ण

	inet->inet_rcv_saddr = v4addr;
	inet->inet_saddr = v4addr;

	sk->sk_v6_rcv_saddr = addr->sin6_addr;

	अगर (!(addr_type & IPV6_ADDR_MULTICAST))
		np->saddr = addr->sin6_addr;

	saved_ipv6only = sk->sk_ipv6only;
	अगर (addr_type != IPV6_ADDR_ANY && addr_type != IPV6_ADDR_MAPPED)
		sk->sk_ipv6only = 1;

	/* Make sure we are allowed to bind here. */
	अगर (snum || !(inet->bind_address_no_port ||
		      (flags & BIND_FORCE_ADDRESS_NO_PORT))) अणु
		अगर (sk->sk_prot->get_port(sk, snum)) अणु
			sk->sk_ipv6only = saved_ipv6only;
			inet_reset_saddr(sk);
			err = -EADDRINUSE;
			जाओ out;
		पूर्ण
		अगर (!(flags & BIND_FROM_BPF)) अणु
			err = BPF_CGROUP_RUN_PROG_INET6_POST_BIND(sk);
			अगर (err) अणु
				sk->sk_ipv6only = saved_ipv6only;
				inet_reset_saddr(sk);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (addr_type != IPV6_ADDR_ANY)
		sk->sk_userlocks |= SOCK_BINDADDR_LOCK;
	अगर (snum)
		sk->sk_userlocks |= SOCK_BINDPORT_LOCK;
	inet->inet_sport = htons(inet->inet_num);
	inet->inet_dport = 0;
	inet->inet_daddr = 0;
out:
	अगर (flags & BIND_WITH_LOCK)
		release_sock(sk);
	वापस err;
out_unlock:
	rcu_पढ़ो_unlock();
	जाओ out;
पूर्ण

/* bind क्रम INET6 API */
पूर्णांक inet6_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	u32 flags = BIND_WITH_LOCK;
	पूर्णांक err = 0;

	/* If the socket has its own bind function then use it. */
	अगर (sk->sk_prot->bind)
		वापस sk->sk_prot->bind(sk, uaddr, addr_len);

	अगर (addr_len < SIN6_LEN_RFC2133)
		वापस -EINVAL;

	/* BPF prog is run beक्रमe any checks are करोne so that अगर the prog
	 * changes context in a wrong way it will be caught.
	 */
	err = BPF_CGROUP_RUN_PROG_INET_BIND_LOCK(sk, uaddr,
						 BPF_CGROUP_INET6_BIND, &flags);
	अगर (err)
		वापस err;

	वापस __inet6_bind(sk, uaddr, addr_len, flags);
पूर्ण
EXPORT_SYMBOL(inet6_bind);

पूर्णांक inet6_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (!sk)
		वापस -EINVAL;

	/* Free mc lists */
	ipv6_sock_mc_बंद(sk);

	/* Free ac lists */
	ipv6_sock_ac_बंद(sk);

	वापस inet_release(sock);
पूर्ण
EXPORT_SYMBOL(inet6_release);

व्योम inet6_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा ipv6_txoptions *opt;

	/* Release rx options */

	skb = xchg(&np->pktoptions, शून्य);
	kमुक्त_skb(skb);

	skb = xchg(&np->rxpmtu, शून्य);
	kमुक्त_skb(skb);

	/* Free flowlabels */
	fl6_मुक्त_socklist(sk);

	/* Free tx options */

	opt = xchg((__क्रमce काष्ठा ipv6_txoptions **)&np->opt, शून्य);
	अगर (opt) अणु
		atomic_sub(opt->tot_len, &sk->sk_omem_alloc);
		txopt_put(opt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(inet6_destroy_sock);

/*
 *	This करोes both peername and sockname.
 */
पूर्णांक inet6_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		  पूर्णांक peer)
अणु
	काष्ठा sockaddr_in6 *sin = (काष्ठा sockaddr_in6 *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	sin->sin6_family = AF_INET6;
	sin->sin6_flowinfo = 0;
	sin->sin6_scope_id = 0;
	अगर (peer) अणु
		अगर (!inet->inet_dport)
			वापस -ENOTCONN;
		अगर (((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_SYN_SENT)) &&
		    peer == 1)
			वापस -ENOTCONN;
		sin->sin6_port = inet->inet_dport;
		sin->sin6_addr = sk->sk_v6_daddr;
		अगर (np->sndflow)
			sin->sin6_flowinfo = np->flow_label;
		BPF_CGROUP_RUN_SA_PROG_LOCK(sk, (काष्ठा sockaddr *)sin,
					    BPF_CGROUP_INET6_GETPEERNAME,
					    शून्य);
	पूर्ण अन्यथा अणु
		अगर (ipv6_addr_any(&sk->sk_v6_rcv_saddr))
			sin->sin6_addr = np->saddr;
		अन्यथा
			sin->sin6_addr = sk->sk_v6_rcv_saddr;
		sin->sin6_port = inet->inet_sport;
		BPF_CGROUP_RUN_SA_PROG_LOCK(sk, (काष्ठा sockaddr *)sin,
					    BPF_CGROUP_INET6_GETSOCKNAME,
					    शून्य);
	पूर्ण
	sin->sin6_scope_id = ipv6_अगरace_scope_id(&sin->sin6_addr,
						 sk->sk_bound_dev_अगर);
	वापस माप(*sin);
पूर्ण
EXPORT_SYMBOL(inet6_getname);

पूर्णांक inet6_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);

	चयन (cmd) अणु
	हाल SIOCADDRT:
	हाल SIOCDELRT: अणु
		काष्ठा in6_rपंचांगsg rपंचांगsg;

		अगर (copy_from_user(&rपंचांगsg, argp, माप(rपंचांगsg)))
			वापस -EFAULT;
		वापस ipv6_route_ioctl(net, cmd, &rपंचांगsg);
	पूर्ण
	हाल SIOCSIFADDR:
		वापस addrconf_add_अगरaddr(net, argp);
	हाल SIOCDIFADDR:
		वापस addrconf_del_अगरaddr(net, argp);
	हाल SIOCSIFDSTADDR:
		वापस addrconf_set_dstaddr(net, argp);
	शेष:
		अगर (!sk->sk_prot->ioctl)
			वापस -ENOIOCTLCMD;
		वापस sk->sk_prot->ioctl(sk, cmd, arg);
	पूर्ण
	/*NOTREACHED*/
	वापस 0;
पूर्ण
EXPORT_SYMBOL(inet6_ioctl);

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_in6_rपंचांगsg अणु
	काष्ठा in6_addr		rपंचांगsg_dst;
	काष्ठा in6_addr		rपंचांगsg_src;
	काष्ठा in6_addr		rपंचांगsg_gateway;
	u32			rपंचांगsg_type;
	u16			rपंचांगsg_dst_len;
	u16			rपंचांगsg_src_len;
	u32			rपंचांगsg_metric;
	u32			rपंचांगsg_info;
	u32			rपंचांगsg_flags;
	s32			rपंचांगsg_अगरindex;
पूर्ण;

अटल पूर्णांक inet6_compat_routing_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd,
		काष्ठा compat_in6_rपंचांगsg __user *ur)
अणु
	काष्ठा in6_rपंचांगsg rt;

	अगर (copy_from_user(&rt.rपंचांगsg_dst, &ur->rपंचांगsg_dst,
			3 * माप(काष्ठा in6_addr)) ||
	    get_user(rt.rपंचांगsg_type, &ur->rपंचांगsg_type) ||
	    get_user(rt.rपंचांगsg_dst_len, &ur->rपंचांगsg_dst_len) ||
	    get_user(rt.rपंचांगsg_src_len, &ur->rपंचांगsg_src_len) ||
	    get_user(rt.rपंचांगsg_metric, &ur->rपंचांगsg_metric) ||
	    get_user(rt.rपंचांगsg_info, &ur->rपंचांगsg_info) ||
	    get_user(rt.rपंचांगsg_flags, &ur->rपंचांगsg_flags) ||
	    get_user(rt.rपंचांगsg_अगरindex, &ur->rपंचांगsg_अगरindex))
		वापस -EFAULT;


	वापस ipv6_route_ioctl(sock_net(sk), cmd, &rt);
पूर्ण

पूर्णांक inet6_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	काष्ठा sock *sk = sock->sk;

	चयन (cmd) अणु
	हाल SIOCADDRT:
	हाल SIOCDELRT:
		वापस inet6_compat_routing_ioctl(sk, cmd, argp);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(inet6_compat_ioctl);
#पूर्ण_अगर /* CONFIG_COMPAT */

INसूचीECT_CALLABLE_DECLARE(पूर्णांक udpv6_sendmsg(काष्ठा sock *, काष्ठा msghdr *,
					    माप_प्रकार));
पूर्णांक inet6_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (unlikely(inet_send_prepare(sk)))
		वापस -EAGAIN;

	वापस INसूचीECT_CALL_2(sk->sk_prot->sendmsg, tcp_sendmsg, udpv6_sendmsg,
			       sk, msg, size);
पूर्ण

INसूचीECT_CALLABLE_DECLARE(पूर्णांक udpv6_recvmsg(काष्ठा sock *, काष्ठा msghdr *,
					    माप_प्रकार, पूर्णांक, पूर्णांक, पूर्णांक *));
पूर्णांक inet6_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		  पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक addr_len = 0;
	पूर्णांक err;

	अगर (likely(!(flags & MSG_ERRQUEUE)))
		sock_rps_record_flow(sk);

	err = INसूचीECT_CALL_2(sk->sk_prot->recvmsg, tcp_recvmsg, udpv6_recvmsg,
			      sk, msg, size, flags & MSG_DONTWAIT,
			      flags & ~MSG_DONTWAIT, &addr_len);
	अगर (err >= 0)
		msg->msg_namelen = addr_len;
	वापस err;
पूर्ण

स्थिर काष्ठा proto_ops inet6_stream_ops = अणु
	.family		   = PF_INET6,
	.owner		   = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = inet6_bind,
	.connect	   = inet_stream_connect,	/* ok		*/
	.socketpair	   = sock_no_socketpair,	/* a करो nothing	*/
	.accept		   = inet_accept,		/* ok		*/
	.getname	   = inet6_getname,
	.poll		   = tcp_poll,			/* ok		*/
	.ioctl		   = inet6_ioctl,		/* must change  */
	.gettstamp	   = sock_gettstamp,
	.listen		   = inet_listen,		/* ok		*/
	.shutकरोwn	   = inet_shutकरोwn,		/* ok		*/
	.setsockopt	   = sock_common_setsockopt,	/* ok		*/
	.माला_लोockopt	   = sock_common_माला_लोockopt,	/* ok		*/
	.sendmsg	   = inet6_sendmsg,		/* retpoline's sake */
	.recvmsg	   = inet6_recvmsg,		/* retpoline's sake */
#अगर_घोषित CONFIG_MMU
	.mmap		   = tcp_mmap,
#पूर्ण_अगर
	.sendpage	   = inet_sendpage,
	.sendmsg_locked    = tcp_sendmsg_locked,
	.sendpage_locked   = tcp_sendpage_locked,
	.splice_पढ़ो	   = tcp_splice_पढ़ो,
	.पढ़ो_sock	   = tcp_पढ़ो_sock,
	.peek_len	   = tcp_peek_len,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet6_compat_ioctl,
#पूर्ण_अगर
	.set_rcvlowat	   = tcp_set_rcvlowat,
पूर्ण;

स्थिर काष्ठा proto_ops inet6_dgram_ops = अणु
	.family		   = PF_INET6,
	.owner		   = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = inet6_bind,
	.connect	   = inet_dgram_connect,	/* ok		*/
	.socketpair	   = sock_no_socketpair,	/* a करो nothing	*/
	.accept		   = sock_no_accept,		/* a करो nothing	*/
	.getname	   = inet6_getname,
	.poll		   = udp_poll,			/* ok		*/
	.ioctl		   = inet6_ioctl,		/* must change  */
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,		/* ok		*/
	.shutकरोwn	   = inet_shutकरोwn,		/* ok		*/
	.setsockopt	   = sock_common_setsockopt,	/* ok		*/
	.माला_लोockopt	   = sock_common_माला_लोockopt,	/* ok		*/
	.sendmsg	   = inet6_sendmsg,		/* retpoline's sake */
	.recvmsg	   = inet6_recvmsg,		/* retpoline's sake */
	.पढ़ो_sock	   = udp_पढ़ो_sock,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
	.set_peek_off	   = sk_set_peek_off,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet6_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_proto_family inet6_family_ops = अणु
	.family = PF_INET6,
	.create = inet6_create,
	.owner	= THIS_MODULE,
पूर्ण;

पूर्णांक inet6_रेजिस्टर_protosw(काष्ठा inet_protosw *p)
अणु
	काष्ठा list_head *lh;
	काष्ठा inet_protosw *answer;
	काष्ठा list_head *last_perm;
	पूर्णांक protocol = p->protocol;
	पूर्णांक ret;

	spin_lock_bh(&inetsw6_lock);

	ret = -EINVAL;
	अगर (p->type >= SOCK_MAX)
		जाओ out_illegal;

	/* If we are trying to override a permanent protocol, bail. */
	answer = शून्य;
	ret = -EPERM;
	last_perm = &inetsw6[p->type];
	list_क्रम_each(lh, &inetsw6[p->type]) अणु
		answer = list_entry(lh, काष्ठा inet_protosw, list);

		/* Check only the non-wild match. */
		अगर (INET_PROTOSW_PERMANENT & answer->flags) अणु
			अगर (protocol == answer->protocol)
				अवरोध;
			last_perm = lh;
		पूर्ण

		answer = शून्य;
	पूर्ण
	अगर (answer)
		जाओ out_permanent;

	/* Add the new entry after the last permanent entry अगर any, so that
	 * the new entry करोes not override a permanent entry when matched with
	 * a wild-card protocol. But it is allowed to override any existing
	 * non-permanent entry.  This means that when we हटाओ this entry, the
	 * प्रणाली स्वतःmatically वापसs to the old behavior.
	 */
	list_add_rcu(&p->list, last_perm);
	ret = 0;
out:
	spin_unlock_bh(&inetsw6_lock);
	वापस ret;

out_permanent:
	pr_err("Attempt to override permanent protocol %d\n", protocol);
	जाओ out;

out_illegal:
	pr_err("Ignoring attempt to register invalid socket type %d\n",
	       p->type);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(inet6_रेजिस्टर_protosw);

व्योम
inet6_unरेजिस्टर_protosw(काष्ठा inet_protosw *p)
अणु
	अगर (INET_PROTOSW_PERMANENT & p->flags) अणु
		pr_err("Attempt to unregister permanent protocol %d\n",
		       p->protocol);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&inetsw6_lock);
		list_del_rcu(&p->list);
		spin_unlock_bh(&inetsw6_lock);

		synchronize_net();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(inet6_unरेजिस्टर_protosw);

पूर्णांक inet6_sk_rebuild_header(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा dst_entry *dst;

	dst = __sk_dst_check(sk, np->dst_cookie);

	अगर (!dst) अणु
		काष्ठा inet_sock *inet = inet_sk(sk);
		काष्ठा in6_addr *final_p, final;
		काष्ठा flowi6 fl6;

		स_रखो(&fl6, 0, माप(fl6));
		fl6.flowi6_proto = sk->sk_protocol;
		fl6.daddr = sk->sk_v6_daddr;
		fl6.saddr = np->saddr;
		fl6.flowlabel = np->flow_label;
		fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;
		fl6.flowi6_mark = sk->sk_mark;
		fl6.fl6_dport = inet->inet_dport;
		fl6.fl6_sport = inet->inet_sport;
		fl6.flowi6_uid = sk->sk_uid;
		security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(&fl6));

		rcu_पढ़ो_lock();
		final_p = fl6_update_dst(&fl6, rcu_dereference(np->opt),
					 &final);
		rcu_पढ़ो_unlock();

		dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
		अगर (IS_ERR(dst)) अणु
			sk->sk_route_caps = 0;
			sk->sk_err_soft = -PTR_ERR(dst);
			वापस PTR_ERR(dst);
		पूर्ण

		ip6_dst_store(sk, dst, शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(inet6_sk_rebuild_header);

bool ipv6_opt_accepted(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb,
		       स्थिर काष्ठा inet6_skb_parm *opt)
अणु
	स्थिर काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	अगर (np->rxopt.all) अणु
		अगर (((opt->flags & IP6SKB_HOPBYHOP) &&
		     (np->rxopt.bits.hopopts || np->rxopt.bits.ohopopts)) ||
		    (ip6_flowinfo((काष्ठा ipv6hdr *) skb_network_header(skb)) &&
		     np->rxopt.bits.rxflow) ||
		    (opt->srcrt && (np->rxopt.bits.srcrt ||
		     np->rxopt.bits.osrcrt)) ||
		    ((opt->dst1 || opt->dst0) &&
		     (np->rxopt.bits.dstopts || np->rxopt.bits.odstopts)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_opt_accepted);

अटल काष्ठा packet_type ipv6_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_IPV6),
	.func = ipv6_rcv,
	.list_func = ipv6_list_rcv,
पूर्ण;

अटल पूर्णांक __init ipv6_packet_init(व्योम)
अणु
	dev_add_pack(&ipv6_packet_type);
	वापस 0;
पूर्ण

अटल व्योम ipv6_packet_cleanup(व्योम)
अणु
	dev_हटाओ_pack(&ipv6_packet_type);
पूर्ण

अटल पूर्णांक __net_init ipv6_init_mibs(काष्ठा net *net)
अणु
	पूर्णांक i;

	net->mib.udp_stats_in6 = alloc_percpu(काष्ठा udp_mib);
	अगर (!net->mib.udp_stats_in6)
		वापस -ENOMEM;
	net->mib.udplite_stats_in6 = alloc_percpu(काष्ठा udp_mib);
	अगर (!net->mib.udplite_stats_in6)
		जाओ err_udplite_mib;
	net->mib.ipv6_statistics = alloc_percpu(काष्ठा ipstats_mib);
	अगर (!net->mib.ipv6_statistics)
		जाओ err_ip_mib;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ipstats_mib *af_inet6_stats;
		af_inet6_stats = per_cpu_ptr(net->mib.ipv6_statistics, i);
		u64_stats_init(&af_inet6_stats->syncp);
	पूर्ण


	net->mib.icmpv6_statistics = alloc_percpu(काष्ठा icmpv6_mib);
	अगर (!net->mib.icmpv6_statistics)
		जाओ err_icmp_mib;
	net->mib.icmpv6msg_statistics = kzalloc(माप(काष्ठा icmpv6msg_mib),
						GFP_KERNEL);
	अगर (!net->mib.icmpv6msg_statistics)
		जाओ err_icmpmsg_mib;
	वापस 0;

err_icmpmsg_mib:
	मुक्त_percpu(net->mib.icmpv6_statistics);
err_icmp_mib:
	मुक्त_percpu(net->mib.ipv6_statistics);
err_ip_mib:
	मुक्त_percpu(net->mib.udplite_stats_in6);
err_udplite_mib:
	मुक्त_percpu(net->mib.udp_stats_in6);
	वापस -ENOMEM;
पूर्ण

अटल व्योम ipv6_cleanup_mibs(काष्ठा net *net)
अणु
	मुक्त_percpu(net->mib.udp_stats_in6);
	मुक्त_percpu(net->mib.udplite_stats_in6);
	मुक्त_percpu(net->mib.ipv6_statistics);
	मुक्त_percpu(net->mib.icmpv6_statistics);
	kमुक्त(net->mib.icmpv6msg_statistics);
पूर्ण

अटल पूर्णांक __net_init inet6_net_init(काष्ठा net *net)
अणु
	पूर्णांक err = 0;

	net->ipv6.sysctl.bindv6only = 0;
	net->ipv6.sysctl.icmpv6_समय = 1*HZ;
	net->ipv6.sysctl.icmpv6_echo_ignore_all = 0;
	net->ipv6.sysctl.icmpv6_echo_ignore_multicast = 0;
	net->ipv6.sysctl.icmpv6_echo_ignore_anycast = 0;

	/* By शेष, rate limit error messages.
	 * Except क्रम pmtu discovery, it would अवरोध it.
	 * proc_करो_large_biपंचांगap needs poपूर्णांकer to the biपंचांगap.
	 */
	biपंचांगap_set(net->ipv6.sysctl.icmpv6_ratemask, 0, ICMPV6_ERRMSG_MAX + 1);
	biपंचांगap_clear(net->ipv6.sysctl.icmpv6_ratemask, ICMPV6_PKT_TOOBIG, 1);
	net->ipv6.sysctl.icmpv6_ratemask_ptr = net->ipv6.sysctl.icmpv6_ratemask;

	net->ipv6.sysctl.flowlabel_consistency = 1;
	net->ipv6.sysctl.स्वतः_flowlabels = IP6_DEFAULT_AUTO_FLOW_LABELS;
	net->ipv6.sysctl.idgen_retries = 3;
	net->ipv6.sysctl.idgen_delay = 1 * HZ;
	net->ipv6.sysctl.flowlabel_state_ranges = 0;
	net->ipv6.sysctl.max_dst_opts_cnt = IP6_DEFAULT_MAX_DST_OPTS_CNT;
	net->ipv6.sysctl.max_hbh_opts_cnt = IP6_DEFAULT_MAX_HBH_OPTS_CNT;
	net->ipv6.sysctl.max_dst_opts_len = IP6_DEFAULT_MAX_DST_OPTS_LEN;
	net->ipv6.sysctl.max_hbh_opts_len = IP6_DEFAULT_MAX_HBH_OPTS_LEN;
	net->ipv6.sysctl.fib_notअगरy_on_flag_change = 0;
	atomic_set(&net->ipv6.fib6_sernum, 1);

	err = ipv6_init_mibs(net);
	अगर (err)
		वापस err;
#अगर_घोषित CONFIG_PROC_FS
	err = udp6_proc_init(net);
	अगर (err)
		जाओ out;
	err = tcp6_proc_init(net);
	अगर (err)
		जाओ proc_tcp6_fail;
	err = ac6_proc_init(net);
	अगर (err)
		जाओ proc_ac6_fail;
#पूर्ण_अगर
	वापस err;

#अगर_घोषित CONFIG_PROC_FS
proc_ac6_fail:
	tcp6_proc_निकास(net);
proc_tcp6_fail:
	udp6_proc_निकास(net);
out:
	ipv6_cleanup_mibs(net);
	वापस err;
#पूर्ण_अगर
पूर्ण

अटल व्योम __net_निकास inet6_net_निकास(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	udp6_proc_निकास(net);
	tcp6_proc_निकास(net);
	ac6_proc_निकास(net);
#पूर्ण_अगर
	ipv6_cleanup_mibs(net);
पूर्ण

अटल काष्ठा pernet_operations inet6_net_ops = अणु
	.init = inet6_net_init,
	.निकास = inet6_net_निकास,
पूर्ण;

अटल पूर्णांक ipv6_route_input(काष्ठा sk_buff *skb)
अणु
	ip6_route_input(skb);
	वापस skb_dst(skb)->error;
पूर्ण

अटल स्थिर काष्ठा ipv6_stub ipv6_stub_impl = अणु
	.ipv6_sock_mc_join = ipv6_sock_mc_join,
	.ipv6_sock_mc_drop = ipv6_sock_mc_drop,
	.ipv6_dst_lookup_flow = ip6_dst_lookup_flow,
	.ipv6_route_input  = ipv6_route_input,
	.fib6_get_table	   = fib6_get_table,
	.fib6_table_lookup = fib6_table_lookup,
	.fib6_lookup       = fib6_lookup,
	.fib6_select_path  = fib6_select_path,
	.ip6_mtu_from_fib6 = ip6_mtu_from_fib6,
	.fib6_nh_init	   = fib6_nh_init,
	.fib6_nh_release   = fib6_nh_release,
	.fib6_update_sernum = fib6_update_sernum_stub,
	.fib6_rt_update	   = fib6_rt_update,
	.ip6_del_rt	   = ip6_del_rt,
	.udpv6_encap_enable = udpv6_encap_enable,
	.ndisc_send_na = ndisc_send_na,
#अगर IS_ENABLED(CONFIG_XFRM)
	.xfrm6_local_rxpmtu = xfrm6_local_rxpmtu,
	.xfrm6_udp_encap_rcv = xfrm6_udp_encap_rcv,
	.xfrm6_rcv_encap = xfrm6_rcv_encap,
#पूर्ण_अगर
	.nd_tbl	= &nd_tbl,
	.ipv6_fragment = ip6_fragment,
	.ipv6_dev_find = ipv6_dev_find,
पूर्ण;

अटल स्थिर काष्ठा ipv6_bpf_stub ipv6_bpf_stub_impl = अणु
	.inet6_bind = __inet6_bind,
	.udp6_lib_lookup = __udp6_lib_lookup,
पूर्ण;

अटल पूर्णांक __init inet6_init(व्योम)
अणु
	काष्ठा list_head *r;
	पूर्णांक err = 0;

	sock_skb_cb_check_size(माप(काष्ठा inet6_skb_parm));

	/* Register the socket-side inक्रमmation क्रम inet6_create.  */
	क्रम (r = &inetsw6[0]; r < &inetsw6[SOCK_MAX]; ++r)
		INIT_LIST_HEAD(r);

	अगर (disable_ipv6_mod) अणु
		pr_info("Loaded, but administratively disabled, reboot required to enable\n");
		जाओ out;
	पूर्ण

	err = proto_रेजिस्टर(&tcpv6_prot, 1);
	अगर (err)
		जाओ out;

	err = proto_रेजिस्टर(&udpv6_prot, 1);
	अगर (err)
		जाओ out_unरेजिस्टर_tcp_proto;

	err = proto_रेजिस्टर(&udplitev6_prot, 1);
	अगर (err)
		जाओ out_unरेजिस्टर_udp_proto;

	err = proto_रेजिस्टर(&rawv6_prot, 1);
	अगर (err)
		जाओ out_unरेजिस्टर_udplite_proto;

	err = proto_रेजिस्टर(&pingv6_prot, 1);
	अगर (err)
		जाओ out_unरेजिस्टर_raw_proto;

	/* We MUST रेजिस्टर RAW sockets beक्रमe we create the ICMP6,
	 * IGMP6, or NDISC control sockets.
	 */
	err = rawv6_init();
	अगर (err)
		जाओ out_unरेजिस्टर_ping_proto;

	/* Register the family here so that the init calls below will
	 * be able to create sockets. (?? is this dangerous ??)
	 */
	err = sock_रेजिस्टर(&inet6_family_ops);
	अगर (err)
		जाओ out_sock_रेजिस्टर_fail;

	/*
	 *	ipngwg API draft makes clear that the correct semantics
	 *	क्रम TCP and UDP is to consider one TCP and UDP instance
	 *	in a host available by both INET and INET6 APIs and
	 *	able to communicate via both network protocols.
	 */

	err = रेजिस्टर_pernet_subsys(&inet6_net_ops);
	अगर (err)
		जाओ रेजिस्टर_pernet_fail;
	err = ip6_mr_init();
	अगर (err)
		जाओ ipmr_fail;
	err = icmpv6_init();
	अगर (err)
		जाओ icmp_fail;
	err = ndisc_init();
	अगर (err)
		जाओ ndisc_fail;
	err = igmp6_init();
	अगर (err)
		जाओ igmp_fail;

	err = ipv6_netfilter_init();
	अगर (err)
		जाओ netfilter_fail;
	/* Create /proc/foo6 entries. */
#अगर_घोषित CONFIG_PROC_FS
	err = -ENOMEM;
	अगर (raw6_proc_init())
		जाओ proc_raw6_fail;
	अगर (udplite6_proc_init())
		जाओ proc_udplite6_fail;
	अगर (ipv6_misc_proc_init())
		जाओ proc_misc6_fail;
	अगर (अगर6_proc_init())
		जाओ proc_अगर6_fail;
#पूर्ण_अगर
	err = ip6_route_init();
	अगर (err)
		जाओ ip6_route_fail;
	err = ndisc_late_init();
	अगर (err)
		जाओ ndisc_late_fail;
	err = ip6_flowlabel_init();
	अगर (err)
		जाओ ip6_flowlabel_fail;
	err = ipv6_anycast_init();
	अगर (err)
		जाओ ipv6_anycast_fail;
	err = addrconf_init();
	अगर (err)
		जाओ addrconf_fail;

	/* Init v6 extension headers. */
	err = ipv6_exthdrs_init();
	अगर (err)
		जाओ ipv6_exthdrs_fail;

	err = ipv6_frag_init();
	अगर (err)
		जाओ ipv6_frag_fail;

	/* Init v6 transport protocols. */
	err = udpv6_init();
	अगर (err)
		जाओ udpv6_fail;

	err = udplitev6_init();
	अगर (err)
		जाओ udplitev6_fail;

	err = udpv6_offload_init();
	अगर (err)
		जाओ udpv6_offload_fail;

	err = tcpv6_init();
	अगर (err)
		जाओ tcpv6_fail;

	err = ipv6_packet_init();
	अगर (err)
		जाओ ipv6_packet_fail;

	err = pingv6_init();
	अगर (err)
		जाओ pingv6_fail;

	err = calipso_init();
	अगर (err)
		जाओ calipso_fail;

	err = seg6_init();
	अगर (err)
		जाओ seg6_fail;

	err = rpl_init();
	अगर (err)
		जाओ rpl_fail;

	err = igmp6_late_init();
	अगर (err)
		जाओ igmp6_late_err;

#अगर_घोषित CONFIG_SYSCTL
	err = ipv6_sysctl_रेजिस्टर();
	अगर (err)
		जाओ sysctl_fail;
#पूर्ण_अगर

	/* ensure that ipv6 stubs are visible only after ipv6 is पढ़ोy */
	wmb();
	ipv6_stub = &ipv6_stub_impl;
	ipv6_bpf_stub = &ipv6_bpf_stub_impl;
out:
	वापस err;

#अगर_घोषित CONFIG_SYSCTL
sysctl_fail:
	igmp6_late_cleanup();
#पूर्ण_अगर
igmp6_late_err:
	rpl_निकास();
rpl_fail:
	seg6_निकास();
seg6_fail:
	calipso_निकास();
calipso_fail:
	pingv6_निकास();
pingv6_fail:
	ipv6_packet_cleanup();
ipv6_packet_fail:
	tcpv6_निकास();
tcpv6_fail:
	udpv6_offload_निकास();
udpv6_offload_fail:
	udplitev6_निकास();
udplitev6_fail:
	udpv6_निकास();
udpv6_fail:
	ipv6_frag_निकास();
ipv6_frag_fail:
	ipv6_exthdrs_निकास();
ipv6_exthdrs_fail:
	addrconf_cleanup();
addrconf_fail:
	ipv6_anycast_cleanup();
ipv6_anycast_fail:
	ip6_flowlabel_cleanup();
ip6_flowlabel_fail:
	ndisc_late_cleanup();
ndisc_late_fail:
	ip6_route_cleanup();
ip6_route_fail:
#अगर_घोषित CONFIG_PROC_FS
	अगर6_proc_निकास();
proc_अगर6_fail:
	ipv6_misc_proc_निकास();
proc_misc6_fail:
	udplite6_proc_निकास();
proc_udplite6_fail:
	raw6_proc_निकास();
proc_raw6_fail:
#पूर्ण_अगर
	ipv6_netfilter_fini();
netfilter_fail:
	igmp6_cleanup();
igmp_fail:
	ndisc_cleanup();
ndisc_fail:
	icmpv6_cleanup();
icmp_fail:
	ip6_mr_cleanup();
ipmr_fail:
	unरेजिस्टर_pernet_subsys(&inet6_net_ops);
रेजिस्टर_pernet_fail:
	sock_unरेजिस्टर(PF_INET6);
	rtnl_unरेजिस्टर_all(PF_INET6);
out_sock_रेजिस्टर_fail:
	rawv6_निकास();
out_unरेजिस्टर_ping_proto:
	proto_unरेजिस्टर(&pingv6_prot);
out_unरेजिस्टर_raw_proto:
	proto_unरेजिस्टर(&rawv6_prot);
out_unरेजिस्टर_udplite_proto:
	proto_unरेजिस्टर(&udplitev6_prot);
out_unरेजिस्टर_udp_proto:
	proto_unरेजिस्टर(&udpv6_prot);
out_unरेजिस्टर_tcp_proto:
	proto_unरेजिस्टर(&tcpv6_prot);
	जाओ out;
पूर्ण
module_init(inet6_init);

MODULE_ALIAS_NETPROTO(PF_INET6);
