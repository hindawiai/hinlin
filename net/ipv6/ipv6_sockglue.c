<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 BSD socket options पूर्णांकerface
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Based on linux/net/ipv4/ip_sockglue.c
 *
 *	FIXME: Make the setsockopt code POSIX compliant: That is
 *
 *	o	Truncate माला_लोockopt वापसs
 *	o	Return an optlen of the truncated length अगर need be
 *
 *	Changes:
 *	David L Stevens <dlstevens@us.ibm.com>:
 *		- added multicast source filtering API क्रम MLDv2
 */

#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/mroute6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>

#समावेश <net/sock.h>
#समावेश <net/snmp.h>
#समावेश <net/ipv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/inet_common.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/udplite.h>
#समावेश <net/xfrm.h>
#समावेश <net/compat.h>
#समावेश <net/seg6.h>

#समावेश <linux/uaccess.h>

काष्ठा ip6_ra_chain *ip6_ra_chain;
DEFINE_RWLOCK(ip6_ra_lock);

पूर्णांक ip6_ra_control(काष्ठा sock *sk, पूर्णांक sel)
अणु
	काष्ठा ip6_ra_chain *ra, *new_ra, **rap;

	/* RA packet may be delivered ONLY to IPPROTO_RAW socket */
	अगर (sk->sk_type != SOCK_RAW || inet_sk(sk)->inet_num != IPPROTO_RAW)
		वापस -ENOPROTOOPT;

	new_ra = (sel >= 0) ? kदो_स्मृति(माप(*new_ra), GFP_KERNEL) : शून्य;
	अगर (sel >= 0 && !new_ra)
		वापस -ENOMEM;

	ग_लिखो_lock_bh(&ip6_ra_lock);
	क्रम (rap = &ip6_ra_chain; (ra = *rap) != शून्य; rap = &ra->next) अणु
		अगर (ra->sk == sk) अणु
			अगर (sel >= 0) अणु
				ग_लिखो_unlock_bh(&ip6_ra_lock);
				kमुक्त(new_ra);
				वापस -EADDRINUSE;
			पूर्ण

			*rap = ra->next;
			ग_लिखो_unlock_bh(&ip6_ra_lock);

			sock_put(sk);
			kमुक्त(ra);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (!new_ra) अणु
		ग_लिखो_unlock_bh(&ip6_ra_lock);
		वापस -ENOBUFS;
	पूर्ण
	new_ra->sk = sk;
	new_ra->sel = sel;
	new_ra->next = ra;
	*rap = new_ra;
	sock_hold(sk);
	ग_लिखो_unlock_bh(&ip6_ra_lock);
	वापस 0;
पूर्ण

काष्ठा ipv6_txoptions *ipv6_update_options(काष्ठा sock *sk,
					   काष्ठा ipv6_txoptions *opt)
अणु
	अगर (inet_sk(sk)->is_icsk) अणु
		अगर (opt &&
		    !((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE)) &&
		    inet_sk(sk)->inet_daddr != LOOPBACK4_IPV6) अणु
			काष्ठा inet_connection_sock *icsk = inet_csk(sk);
			icsk->icsk_ext_hdr_len = opt->opt_flen + opt->opt_nflen;
			icsk->icsk_sync_mss(sk, icsk->icsk_pmtu_cookie);
		पूर्ण
	पूर्ण
	opt = xchg((__क्रमce काष्ठा ipv6_txoptions **)&inet6_sk(sk)->opt,
		   opt);
	sk_dst_reset(sk);

	वापस opt;
पूर्ण

अटल bool setsockopt_needs_rtnl(पूर्णांक optname)
अणु
	चयन (optname) अणु
	हाल IPV6_ADDRFORM:
	हाल IPV6_ADD_MEMBERSHIP:
	हाल IPV6_DROP_MEMBERSHIP:
	हाल IPV6_JOIN_ANYCAST:
	हाल IPV6_LEAVE_ANYCAST:
	हाल MCAST_JOIN_GROUP:
	हाल MCAST_LEAVE_GROUP:
	हाल MCAST_JOIN_SOURCE_GROUP:
	हाल MCAST_LEAVE_SOURCE_GROUP:
	हाल MCAST_BLOCK_SOURCE:
	हाल MCAST_UNBLOCK_SOURCE:
	हाल MCAST_MSFILTER:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक copy_group_source_from_sockptr(काष्ठा group_source_req *greqs,
		sockptr_t optval, पूर्णांक optlen)
अणु
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_group_source_req gr32;

		अगर (optlen < माप(gr32))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&gr32, optval, माप(gr32)))
			वापस -EFAULT;
		greqs->gsr_पूर्णांकerface = gr32.gsr_पूर्णांकerface;
		greqs->gsr_group = gr32.gsr_group;
		greqs->gsr_source = gr32.gsr_source;
	पूर्ण अन्यथा अणु
		अगर (optlen < माप(*greqs))
			वापस -EINVAL;
		अगर (copy_from_sockptr(greqs, optval, माप(*greqs)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_ipv6_mcast_group_source(काष्ठा sock *sk, पूर्णांक optname,
		sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा group_source_req greqs;
	पूर्णांक omode, add;
	पूर्णांक ret;

	ret = copy_group_source_from_sockptr(&greqs, optval, optlen);
	अगर (ret)
		वापस ret;

	अगर (greqs.gsr_group.ss_family != AF_INET6 ||
	    greqs.gsr_source.ss_family != AF_INET6)
		वापस -EADDRNOTAVAIL;

	अगर (optname == MCAST_BLOCK_SOURCE) अणु
		omode = MCAST_EXCLUDE;
		add = 1;
	पूर्ण अन्यथा अगर (optname == MCAST_UNBLOCK_SOURCE) अणु
		omode = MCAST_EXCLUDE;
		add = 0;
	पूर्ण अन्यथा अगर (optname == MCAST_JOIN_SOURCE_GROUP) अणु
		काष्ठा sockaddr_in6 *psin6;
		पूर्णांक retv;

		psin6 = (काष्ठा sockaddr_in6 *)&greqs.gsr_group;
		retv = ipv6_sock_mc_join_ssm(sk, greqs.gsr_पूर्णांकerface,
					     &psin6->sin6_addr,
					     MCAST_INCLUDE);
		/* prior join w/ dअगरferent source is ok */
		अगर (retv && retv != -EADDRINUSE)
			वापस retv;
		omode = MCAST_INCLUDE;
		add = 1;
	पूर्ण अन्यथा /* MCAST_LEAVE_SOURCE_GROUP */ अणु
		omode = MCAST_INCLUDE;
		add = 0;
	पूर्ण
	वापस ip6_mc_source(add, omode, sk, &greqs);
पूर्ण

अटल पूर्णांक ipv6_set_mcast_msfilter(काष्ठा sock *sk, sockptr_t optval,
		पूर्णांक optlen)
अणु
	काष्ठा group_filter *gsf;
	पूर्णांक ret;

	अगर (optlen < GROUP_FILTER_SIZE(0))
		वापस -EINVAL;
	अगर (optlen > sysctl_opपंचांगem_max)
		वापस -ENOBUFS;

	gsf = memdup_sockptr(optval, optlen);
	अगर (IS_ERR(gsf))
		वापस PTR_ERR(gsf);

	/* numsrc >= (4G-140)/128 overflow in 32 bits */
	ret = -ENOBUFS;
	अगर (gsf->gf_numsrc >= 0x1ffffffU ||
	    gsf->gf_numsrc > sysctl_mld_max_msf)
		जाओ out_मुक्त_gsf;

	ret = -EINVAL;
	अगर (GROUP_FILTER_SIZE(gsf->gf_numsrc) > optlen)
		जाओ out_मुक्त_gsf;

	ret = ip6_mc_msfilter(sk, gsf, gsf->gf_slist);
out_मुक्त_gsf:
	kमुक्त(gsf);
	वापस ret;
पूर्ण

अटल पूर्णांक compat_ipv6_set_mcast_msfilter(काष्ठा sock *sk, sockptr_t optval,
		पूर्णांक optlen)
अणु
	स्थिर पूर्णांक size0 = दुरत्व(काष्ठा compat_group_filter, gf_slist);
	काष्ठा compat_group_filter *gf32;
	व्योम *p;
	पूर्णांक ret;
	पूर्णांक n;

	अगर (optlen < size0)
		वापस -EINVAL;
	अगर (optlen > sysctl_opपंचांगem_max - 4)
		वापस -ENOBUFS;

	p = kदो_स्मृति(optlen + 4, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	gf32 = p + 4; /* we want ->gf_group and ->gf_slist aligned */
	ret = -EFAULT;
	अगर (copy_from_sockptr(gf32, optval, optlen))
		जाओ out_मुक्त_p;

	/* numsrc >= (4G-140)/128 overflow in 32 bits */
	ret = -ENOBUFS;
	n = gf32->gf_numsrc;
	अगर (n >= 0x1ffffffU || n > sysctl_mld_max_msf)
		जाओ out_मुक्त_p;

	ret = -EINVAL;
	अगर (दुरत्व(काष्ठा compat_group_filter, gf_slist[n]) > optlen)
		जाओ out_मुक्त_p;

	ret = ip6_mc_msfilter(sk, &(काष्ठा group_filter)अणु
			.gf_पूर्णांकerface = gf32->gf_पूर्णांकerface,
			.gf_group = gf32->gf_group,
			.gf_भ_शेषe = gf32->gf_भ_शेषe,
			.gf_numsrc = gf32->gf_numsrcपूर्ण, gf32->gf_slist);

out_मुक्त_p:
	kमुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक ipv6_mcast_join_leave(काष्ठा sock *sk, पूर्णांक optname,
		sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा sockaddr_in6 *psin6;
	काष्ठा group_req greq;

	अगर (optlen < माप(greq))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&greq, optval, माप(greq)))
		वापस -EFAULT;

	अगर (greq.gr_group.ss_family != AF_INET6)
		वापस -EADDRNOTAVAIL;
	psin6 = (काष्ठा sockaddr_in6 *)&greq.gr_group;
	अगर (optname == MCAST_JOIN_GROUP)
		वापस ipv6_sock_mc_join(sk, greq.gr_पूर्णांकerface,
					 &psin6->sin6_addr);
	वापस ipv6_sock_mc_drop(sk, greq.gr_पूर्णांकerface, &psin6->sin6_addr);
पूर्ण

अटल पूर्णांक compat_ipv6_mcast_join_leave(काष्ठा sock *sk, पूर्णांक optname,
		sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा compat_group_req gr32;
	काष्ठा sockaddr_in6 *psin6;

	अगर (optlen < माप(gr32))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&gr32, optval, माप(gr32)))
		वापस -EFAULT;

	अगर (gr32.gr_group.ss_family != AF_INET6)
		वापस -EADDRNOTAVAIL;
	psin6 = (काष्ठा sockaddr_in6 *)&gr32.gr_group;
	अगर (optname == MCAST_JOIN_GROUP)
		वापस ipv6_sock_mc_join(sk, gr32.gr_पूर्णांकerface,
					&psin6->sin6_addr);
	वापस ipv6_sock_mc_drop(sk, gr32.gr_पूर्णांकerface, &psin6->sin6_addr);
पूर्ण

अटल पूर्णांक ipv6_set_opt_hdr(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
		पूर्णांक optlen)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_opt_hdr *new = शून्य;
	काष्ठा net *net = sock_net(sk);
	काष्ठा ipv6_txoptions *opt;
	पूर्णांक err;

	/* hop-by-hop / destination options are privileged option */
	अगर (optname != IPV6_RTHDR && !ns_capable(net->user_ns, CAP_NET_RAW))
		वापस -EPERM;

	/* हटाओ any sticky options header with a zero option
	 * length, per RFC3542.
	 */
	अगर (optlen > 0) अणु
		अगर (sockptr_is_null(optval))
			वापस -EINVAL;
		अगर (optlen < माप(काष्ठा ipv6_opt_hdr) ||
		    optlen & 0x7 ||
		    optlen > 8 * 255)
			वापस -EINVAL;

		new = memdup_sockptr(optval, optlen);
		अगर (IS_ERR(new))
			वापस PTR_ERR(new);
		अगर (unlikely(ipv6_optlen(new) > optlen)) अणु
			kमुक्त(new);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	opt = rcu_dereference_रक्षित(np->opt, lockdep_sock_is_held(sk));
	opt = ipv6_renew_options(sk, opt, optname, new);
	kमुक्त(new);
	अगर (IS_ERR(opt))
		वापस PTR_ERR(opt);

	/* routing header option needs extra check */
	err = -EINVAL;
	अगर (optname == IPV6_RTHDR && opt && opt->srcrt) अणु
		काष्ठा ipv6_rt_hdr *rthdr = opt->srcrt;
		चयन (rthdr->type) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		हाल IPV6_SRCRT_TYPE_2:
			अगर (rthdr->hdrlen != 2 || rthdr->segments_left != 1)
				जाओ sticky_करोne;
			अवरोध;
#पूर्ण_अगर
		हाल IPV6_SRCRT_TYPE_4:
		अणु
			काष्ठा ipv6_sr_hdr *srh =
				(काष्ठा ipv6_sr_hdr *)opt->srcrt;

			अगर (!seg6_validate_srh(srh, optlen, false))
				जाओ sticky_करोne;
			अवरोध;
		पूर्ण
		शेष:
			जाओ sticky_करोne;
		पूर्ण
	पूर्ण

	err = 0;
	opt = ipv6_update_options(sk, opt);
sticky_करोne:
	अगर (opt) अणु
		atomic_sub(opt->tot_len, &sk->sk_omem_alloc);
		txopt_put(opt);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक करो_ipv6_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		   sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक val, valbool;
	पूर्णांक retv = -ENOPROTOOPT;
	bool needs_rtnl = setsockopt_needs_rtnl(optname);

	अगर (sockptr_is_null(optval))
		val = 0;
	अन्यथा अणु
		अगर (optlen >= माप(पूर्णांक)) अणु
			अगर (copy_from_sockptr(&val, optval, माप(val)))
				वापस -EFAULT;
		पूर्ण अन्यथा
			val = 0;
	पूर्ण

	valbool = (val != 0);

	अगर (ip6_mroute_opt(optname))
		वापस ip6_mroute_setsockopt(sk, optname, optval, optlen);

	अगर (needs_rtnl)
		rtnl_lock();
	lock_sock(sk);

	चयन (optname) अणु

	हाल IPV6_ADDRFORM:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val == PF_INET) अणु
			काष्ठा ipv6_txoptions *opt;
			काष्ठा sk_buff *pktopt;

			अगर (sk->sk_type == SOCK_RAW)
				अवरोध;

			अगर (sk->sk_protocol == IPPROTO_UDP ||
			    sk->sk_protocol == IPPROTO_UDPLITE) अणु
				काष्ठा udp_sock *up = udp_sk(sk);
				अगर (up->pending == AF_INET6) अणु
					retv = -EBUSY;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (sk->sk_protocol == IPPROTO_TCP) अणु
				अगर (sk->sk_prot != &tcpv6_prot) अणु
					retv = -EBUSY;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण

			अगर (sk->sk_state != TCP_ESTABLISHED) अणु
				retv = -ENOTCONN;
				अवरोध;
			पूर्ण

			अगर (ipv6_only_sock(sk) ||
			    !ipv6_addr_v4mapped(&sk->sk_v6_daddr)) अणु
				retv = -EADDRNOTAVAIL;
				अवरोध;
			पूर्ण

			fl6_मुक्त_socklist(sk);
			__ipv6_sock_mc_बंद(sk);
			__ipv6_sock_ac_बंद(sk);

			/*
			 * Sock is moving from IPv6 to IPv4 (sk_prot), so
			 * हटाओ it from the refcnt debug socks count in the
			 * original family...
			 */
			sk_refcnt_debug_dec(sk);

			अगर (sk->sk_protocol == IPPROTO_TCP) अणु
				काष्ठा inet_connection_sock *icsk = inet_csk(sk);
				local_bh_disable();
				sock_prot_inuse_add(net, sk->sk_prot, -1);
				sock_prot_inuse_add(net, &tcp_prot, 1);
				local_bh_enable();
				sk->sk_prot = &tcp_prot;
				icsk->icsk_af_ops = &ipv4_specअगरic;
				sk->sk_socket->ops = &inet_stream_ops;
				sk->sk_family = PF_INET;
				tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
			पूर्ण अन्यथा अणु
				काष्ठा proto *prot = &udp_prot;

				अगर (sk->sk_protocol == IPPROTO_UDPLITE)
					prot = &udplite_prot;
				local_bh_disable();
				sock_prot_inuse_add(net, sk->sk_prot, -1);
				sock_prot_inuse_add(net, prot, 1);
				local_bh_enable();
				sk->sk_prot = prot;
				sk->sk_socket->ops = &inet_dgram_ops;
				sk->sk_family = PF_INET;
			पूर्ण
			opt = xchg((__क्रमce काष्ठा ipv6_txoptions **)&np->opt,
				   शून्य);
			अगर (opt) अणु
				atomic_sub(opt->tot_len, &sk->sk_omem_alloc);
				txopt_put(opt);
			पूर्ण
			pktopt = xchg(&np->pktoptions, शून्य);
			kमुक्त_skb(pktopt);

			/*
			 * ... and add it to the refcnt debug socks count
			 * in the new family. -acme
			 */
			sk_refcnt_debug_inc(sk);
			module_put(THIS_MODULE);
			retv = 0;
			अवरोध;
		पूर्ण
		जाओ e_inval;

	हाल IPV6_V6ONLY:
		अगर (optlen < माप(पूर्णांक) ||
		    inet_sk(sk)->inet_num)
			जाओ e_inval;
		sk->sk_ipv6only = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVPKTINFO:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxinfo = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_2292PKTINFO:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxoinfo = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVHOPLIMIT:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxhlim = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_2292HOPLIMIT:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxohlim = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVRTHDR:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.srcrt = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_2292RTHDR:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.osrcrt = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVHOPOPTS:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.hopopts = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_2292HOPOPTS:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.ohopopts = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVDSTOPTS:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.dstopts = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_2292DSTOPTS:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.odstopts = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_TCLASS:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val < -1 || val > 0xff)
			जाओ e_inval;
		/* RFC 3542, 6.5: शेष traffic class of 0x0 */
		अगर (val == -1)
			val = 0;
		np->tclass = val;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVTCLASS:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxtclass = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_FLOWINFO:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxflow = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVPATHMTU:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxpmtu = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_TRANSPARENT:
		अगर (valbool && !ns_capable(net->user_ns, CAP_NET_RAW) &&
		    !ns_capable(net->user_ns, CAP_NET_ADMIN)) अणु
			retv = -EPERM;
			अवरोध;
		पूर्ण
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		/* we करोn't have a separate transparent bit क्रम IPV6 we use the one in the IPv4 socket */
		inet_sk(sk)->transparent = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_FREEBIND:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		/* we also करोn't have a separate मुक्तbind bit क्रम IPV6 */
		inet_sk(sk)->मुक्तbind = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_RECVORIGDSTADDR:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rxopt.bits.rxorigdstaddr = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_HOPOPTS:
	हाल IPV6_RTHDRDSTOPTS:
	हाल IPV6_RTHDR:
	हाल IPV6_DSTOPTS:
		retv = ipv6_set_opt_hdr(sk, optname, optval, optlen);
		अवरोध;

	हाल IPV6_PKTINFO:
	अणु
		काष्ठा in6_pktinfo pkt;

		अगर (optlen == 0)
			जाओ e_inval;
		अन्यथा अगर (optlen < माप(काष्ठा in6_pktinfo) ||
			 sockptr_is_null(optval))
			जाओ e_inval;

		अगर (copy_from_sockptr(&pkt, optval, माप(pkt))) अणु
			retv = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (!sk_dev_equal_l3scope(sk, pkt.ipi6_अगरindex))
			जाओ e_inval;

		np->sticky_pktinfo.ipi6_अगरindex = pkt.ipi6_अगरindex;
		np->sticky_pktinfo.ipi6_addr = pkt.ipi6_addr;
		retv = 0;
		अवरोध;
	पूर्ण

	हाल IPV6_2292PKTOPTIONS:
	अणु
		काष्ठा ipv6_txoptions *opt = शून्य;
		काष्ठा msghdr msg;
		काष्ठा flowi6 fl6;
		काष्ठा ipcm6_cookie ipc6;

		स_रखो(&fl6, 0, माप(fl6));
		fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;
		fl6.flowi6_mark = sk->sk_mark;

		अगर (optlen == 0)
			जाओ update;

		/* 1K is probably excessive
		 * 1K is surely not enough, 2K per standard header is 16K.
		 */
		retv = -EINVAL;
		अगर (optlen > 64*1024)
			अवरोध;

		opt = sock_kदो_स्मृति(sk, माप(*opt) + optlen, GFP_KERNEL);
		retv = -ENOBUFS;
		अगर (!opt)
			अवरोध;

		स_रखो(opt, 0, माप(*opt));
		refcount_set(&opt->refcnt, 1);
		opt->tot_len = माप(*opt) + optlen;
		retv = -EFAULT;
		अगर (copy_from_sockptr(opt + 1, optval, optlen))
			जाओ करोne;

		msg.msg_controllen = optlen;
		msg.msg_control = (व्योम *)(opt+1);
		ipc6.opt = opt;

		retv = ip6_datagram_send_ctl(net, sk, &msg, &fl6, &ipc6);
		अगर (retv)
			जाओ करोne;
update:
		retv = 0;
		opt = ipv6_update_options(sk, opt);
करोne:
		अगर (opt) अणु
			atomic_sub(opt->tot_len, &sk->sk_omem_alloc);
			txopt_put(opt);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल IPV6_UNICAST_HOPS:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val > 255 || val < -1)
			जाओ e_inval;
		np->hop_limit = val;
		retv = 0;
		अवरोध;

	हाल IPV6_MULTICAST_HOPS:
		अगर (sk->sk_type == SOCK_STREAM)
			अवरोध;
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val > 255 || val < -1)
			जाओ e_inval;
		np->mcast_hops = (val == -1 ? IPV6_DEFAULT_MCASTHOPS : val);
		retv = 0;
		अवरोध;

	हाल IPV6_MULTICAST_LOOP:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val != valbool)
			जाओ e_inval;
		np->mc_loop = valbool;
		retv = 0;
		अवरोध;

	हाल IPV6_UNICAST_IF:
	अणु
		काष्ठा net_device *dev = शून्य;
		पूर्णांक अगरindex;

		अगर (optlen != माप(पूर्णांक))
			जाओ e_inval;

		अगरindex = (__क्रमce पूर्णांक)ntohl((__क्रमce __be32)val);
		अगर (अगरindex == 0) अणु
			np->ucast_oअगर = 0;
			retv = 0;
			अवरोध;
		पूर्ण

		dev = dev_get_by_index(net, अगरindex);
		retv = -EADDRNOTAVAIL;
		अगर (!dev)
			अवरोध;
		dev_put(dev);

		retv = -EINVAL;
		अगर (sk->sk_bound_dev_अगर)
			अवरोध;

		np->ucast_oअगर = अगरindex;
		retv = 0;
		अवरोध;
	पूर्ण

	हाल IPV6_MULTICAST_IF:
		अगर (sk->sk_type == SOCK_STREAM)
			अवरोध;
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;

		अगर (val) अणु
			काष्ठा net_device *dev;
			पूर्णांक midx;

			rcu_पढ़ो_lock();

			dev = dev_get_by_index_rcu(net, val);
			अगर (!dev) अणु
				rcu_पढ़ो_unlock();
				retv = -ENODEV;
				अवरोध;
			पूर्ण
			midx = l3mdev_master_अगरindex_rcu(dev);

			rcu_पढ़ो_unlock();

			अगर (sk->sk_bound_dev_अगर &&
			    sk->sk_bound_dev_अगर != val &&
			    (!midx || midx != sk->sk_bound_dev_अगर))
				जाओ e_inval;
		पूर्ण
		np->mcast_oअगर = val;
		retv = 0;
		अवरोध;
	हाल IPV6_ADD_MEMBERSHIP:
	हाल IPV6_DROP_MEMBERSHIP:
	अणु
		काष्ठा ipv6_mreq mreq;

		अगर (optlen < माप(काष्ठा ipv6_mreq))
			जाओ e_inval;

		retv = -EPROTO;
		अगर (inet_sk(sk)->is_icsk)
			अवरोध;

		retv = -EFAULT;
		अगर (copy_from_sockptr(&mreq, optval, माप(काष्ठा ipv6_mreq)))
			अवरोध;

		अगर (optname == IPV6_ADD_MEMBERSHIP)
			retv = ipv6_sock_mc_join(sk, mreq.ipv6mr_अगरindex, &mreq.ipv6mr_multiaddr);
		अन्यथा
			retv = ipv6_sock_mc_drop(sk, mreq.ipv6mr_अगरindex, &mreq.ipv6mr_multiaddr);
		अवरोध;
	पूर्ण
	हाल IPV6_JOIN_ANYCAST:
	हाल IPV6_LEAVE_ANYCAST:
	अणु
		काष्ठा ipv6_mreq mreq;

		अगर (optlen < माप(काष्ठा ipv6_mreq))
			जाओ e_inval;

		retv = -EFAULT;
		अगर (copy_from_sockptr(&mreq, optval, माप(काष्ठा ipv6_mreq)))
			अवरोध;

		अगर (optname == IPV6_JOIN_ANYCAST)
			retv = ipv6_sock_ac_join(sk, mreq.ipv6mr_अगरindex, &mreq.ipv6mr_acaddr);
		अन्यथा
			retv = ipv6_sock_ac_drop(sk, mreq.ipv6mr_अगरindex, &mreq.ipv6mr_acaddr);
		अवरोध;
	पूर्ण
	हाल IPV6_MULTICAST_ALL:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->mc_all = valbool;
		retv = 0;
		अवरोध;

	हाल MCAST_JOIN_GROUP:
	हाल MCAST_LEAVE_GROUP:
		अगर (in_compat_syscall())
			retv = compat_ipv6_mcast_join_leave(sk, optname, optval,
							    optlen);
		अन्यथा
			retv = ipv6_mcast_join_leave(sk, optname, optval,
						     optlen);
		अवरोध;
	हाल MCAST_JOIN_SOURCE_GROUP:
	हाल MCAST_LEAVE_SOURCE_GROUP:
	हाल MCAST_BLOCK_SOURCE:
	हाल MCAST_UNBLOCK_SOURCE:
		retv = करो_ipv6_mcast_group_source(sk, optname, optval, optlen);
		अवरोध;
	हाल MCAST_MSFILTER:
		अगर (in_compat_syscall())
			retv = compat_ipv6_set_mcast_msfilter(sk, optval,
							      optlen);
		अन्यथा
			retv = ipv6_set_mcast_msfilter(sk, optval, optlen);
		अवरोध;
	हाल IPV6_ROUTER_ALERT:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		retv = ip6_ra_control(sk, val);
		अवरोध;
	हाल IPV6_ROUTER_ALERT_ISOLATE:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->rtalert_isolate = valbool;
		retv = 0;
		अवरोध;
	हाल IPV6_MTU_DISCOVER:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val < IPV6_PMTUDISC_DONT || val > IPV6_PMTUDISC_OMIT)
			जाओ e_inval;
		np->pmtudisc = val;
		retv = 0;
		अवरोध;
	हाल IPV6_MTU:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val && val < IPV6_MIN_MTU)
			जाओ e_inval;
		np->frag_size = val;
		retv = 0;
		अवरोध;
	हाल IPV6_RECVERR:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->recverr = valbool;
		अगर (!val)
			skb_queue_purge(&sk->sk_error_queue);
		retv = 0;
		अवरोध;
	हाल IPV6_FLOWINFO_SEND:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		np->sndflow = valbool;
		retv = 0;
		अवरोध;
	हाल IPV6_FLOWLABEL_MGR:
		retv = ipv6_flowlabel_opt(sk, optval, optlen);
		अवरोध;
	हाल IPV6_IPSEC_POLICY:
	हाल IPV6_XFRM_POLICY:
		retv = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		retv = xfrm_user_policy(sk, optname, optval, optlen);
		अवरोध;

	हाल IPV6_ADDR_PREFERENCES:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		retv = __ip6_sock_set_addr_preferences(sk, val);
		अवरोध;
	हाल IPV6_MINHOPCOUNT:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val < 0 || val > 255)
			जाओ e_inval;
		np->min_hopcount = val;
		retv = 0;
		अवरोध;
	हाल IPV6_DONTFRAG:
		np->करोntfrag = valbool;
		retv = 0;
		अवरोध;
	हाल IPV6_AUTOFLOWLABEL:
		np->स्वतःflowlabel = valbool;
		np->स्वतःflowlabel_set = 1;
		retv = 0;
		अवरोध;
	हाल IPV6_RECVFRAGSIZE:
		np->rxopt.bits.recvfragsize = valbool;
		retv = 0;
		अवरोध;
	हाल IPV6_RECVERR_RFC4884:
		अगर (optlen < माप(पूर्णांक))
			जाओ e_inval;
		अगर (val < 0 || val > 1)
			जाओ e_inval;
		np->recverr_rfc4884 = valbool;
		retv = 0;
		अवरोध;
	पूर्ण

	release_sock(sk);
	अगर (needs_rtnl)
		rtnl_unlock();

	वापस retv;

e_inval:
	release_sock(sk);
	अगर (needs_rtnl)
		rtnl_unlock();
	वापस -EINVAL;
पूर्ण

पूर्णांक ipv6_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		    अचिन्हित पूर्णांक optlen)
अणु
	पूर्णांक err;

	अगर (level == SOL_IP && sk->sk_type != SOCK_RAW)
		वापस udp_prot.setsockopt(sk, level, optname, optval, optlen);

	अगर (level != SOL_IPV6)
		वापस -ENOPROTOOPT;

	err = करो_ipv6_setsockopt(sk, level, optname, optval, optlen);
#अगर_घोषित CONFIG_NETFILTER
	/* we need to exclude all possible ENOPROTOOPTs except शेष हाल */
	अगर (err == -ENOPROTOOPT && optname != IPV6_IPSEC_POLICY &&
			optname != IPV6_XFRM_POLICY)
		err = nf_setsockopt(sk, PF_INET6, optname, optval, optlen);
#पूर्ण_अगर
	वापस err;
पूर्ण
EXPORT_SYMBOL(ipv6_setsockopt);

अटल पूर्णांक ipv6_माला_लोockopt_sticky(काष्ठा sock *sk, काष्ठा ipv6_txoptions *opt,
				  पूर्णांक optname, अक्षर __user *optval, पूर्णांक len)
अणु
	काष्ठा ipv6_opt_hdr *hdr;

	अगर (!opt)
		वापस 0;

	चयन (optname) अणु
	हाल IPV6_HOPOPTS:
		hdr = opt->hopopt;
		अवरोध;
	हाल IPV6_RTHDRDSTOPTS:
		hdr = opt->dst0opt;
		अवरोध;
	हाल IPV6_RTHDR:
		hdr = (काष्ठा ipv6_opt_hdr *)opt->srcrt;
		अवरोध;
	हाल IPV6_DSTOPTS:
		hdr = opt->dst1opt;
		अवरोध;
	शेष:
		वापस -EINVAL;	/* should not happen */
	पूर्ण

	अगर (!hdr)
		वापस 0;

	len = min_t(अचिन्हित पूर्णांक, len, ipv6_optlen(hdr));
	अगर (copy_to_user(optval, hdr, len))
		वापस -EFAULT;
	वापस len;
पूर्ण

अटल पूर्णांक ipv6_get_msfilter(काष्ठा sock *sk, व्योम __user *optval,
		पूर्णांक __user *optlen, पूर्णांक len)
अणु
	स्थिर पूर्णांक size0 = दुरत्व(काष्ठा group_filter, gf_slist);
	काष्ठा group_filter __user *p = optval;
	काष्ठा group_filter gsf;
	पूर्णांक num;
	पूर्णांक err;

	अगर (len < size0)
		वापस -EINVAL;
	अगर (copy_from_user(&gsf, p, size0))
		वापस -EFAULT;
	अगर (gsf.gf_group.ss_family != AF_INET6)
		वापस -EADDRNOTAVAIL;
	num = gsf.gf_numsrc;
	lock_sock(sk);
	err = ip6_mc_msfget(sk, &gsf, p->gf_slist);
	अगर (!err) अणु
		अगर (num > gsf.gf_numsrc)
			num = gsf.gf_numsrc;
		अगर (put_user(GROUP_FILTER_SIZE(num), optlen) ||
		    copy_to_user(p, &gsf, size0))
			err = -EFAULT;
	पूर्ण
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक compat_ipv6_get_msfilter(काष्ठा sock *sk, व्योम __user *optval,
		पूर्णांक __user *optlen)
अणु
	स्थिर पूर्णांक size0 = दुरत्व(काष्ठा compat_group_filter, gf_slist);
	काष्ठा compat_group_filter __user *p = optval;
	काष्ठा compat_group_filter gf32;
	काष्ठा group_filter gf;
	पूर्णांक len, err;
	पूर्णांक num;

	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (len < size0)
		वापस -EINVAL;

	अगर (copy_from_user(&gf32, p, size0))
		वापस -EFAULT;
	gf.gf_पूर्णांकerface = gf32.gf_पूर्णांकerface;
	gf.gf_भ_शेषe = gf32.gf_भ_शेषe;
	num = gf.gf_numsrc = gf32.gf_numsrc;
	gf.gf_group = gf32.gf_group;

	अगर (gf.gf_group.ss_family != AF_INET6)
		वापस -EADDRNOTAVAIL;

	lock_sock(sk);
	err = ip6_mc_msfget(sk, &gf, p->gf_slist);
	release_sock(sk);
	अगर (err)
		वापस err;
	अगर (num > gf.gf_numsrc)
		num = gf.gf_numsrc;
	len = GROUP_FILTER_SIZE(num) - (माप(gf)-माप(gf32));
	अगर (put_user(len, optlen) ||
	    put_user(gf.gf_भ_शेषe, &p->gf_भ_शेषe) ||
	    put_user(gf.gf_numsrc, &p->gf_numsrc))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_ipv6_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		    अक्षर __user *optval, पूर्णांक __user *optlen, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	पूर्णांक len;
	पूर्णांक val;

	अगर (ip6_mroute_opt(optname))
		वापस ip6_mroute_माला_लोockopt(sk, optname, optval, optlen);

	अगर (get_user(len, optlen))
		वापस -EFAULT;
	चयन (optname) अणु
	हाल IPV6_ADDRFORM:
		अगर (sk->sk_protocol != IPPROTO_UDP &&
		    sk->sk_protocol != IPPROTO_UDPLITE &&
		    sk->sk_protocol != IPPROTO_TCP)
			वापस -ENOPROTOOPT;
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -ENOTCONN;
		val = sk->sk_family;
		अवरोध;
	हाल MCAST_MSFILTER:
		अगर (in_compat_syscall())
			वापस compat_ipv6_get_msfilter(sk, optval, optlen);
		वापस ipv6_get_msfilter(sk, optval, optlen, len);
	हाल IPV6_2292PKTOPTIONS:
	अणु
		काष्ठा msghdr msg;
		काष्ठा sk_buff *skb;

		अगर (sk->sk_type != SOCK_STREAM)
			वापस -ENOPROTOOPT;

		msg.msg_control_user = optval;
		msg.msg_controllen = len;
		msg.msg_flags = flags;
		msg.msg_control_is_user = true;

		lock_sock(sk);
		skb = np->pktoptions;
		अगर (skb)
			ip6_datagram_recv_ctl(sk, &msg, skb);
		release_sock(sk);
		अगर (!skb) अणु
			अगर (np->rxopt.bits.rxinfo) अणु
				काष्ठा in6_pktinfo src_info;
				src_info.ipi6_अगरindex = np->mcast_oअगर ? np->mcast_oअगर :
					np->sticky_pktinfo.ipi6_अगरindex;
				src_info.ipi6_addr = np->mcast_oअगर ? sk->sk_v6_daddr : np->sticky_pktinfo.ipi6_addr;
				put_cmsg(&msg, SOL_IPV6, IPV6_PKTINFO, माप(src_info), &src_info);
			पूर्ण
			अगर (np->rxopt.bits.rxhlim) अणु
				पूर्णांक hlim = np->mcast_hops;
				put_cmsg(&msg, SOL_IPV6, IPV6_HOPLIMIT, माप(hlim), &hlim);
			पूर्ण
			अगर (np->rxopt.bits.rxtclass) अणु
				पूर्णांक tclass = (पूर्णांक)ip6_tclass(np->rcv_flowinfo);

				put_cmsg(&msg, SOL_IPV6, IPV6_TCLASS, माप(tclass), &tclass);
			पूर्ण
			अगर (np->rxopt.bits.rxoinfo) अणु
				काष्ठा in6_pktinfo src_info;
				src_info.ipi6_अगरindex = np->mcast_oअगर ? np->mcast_oअगर :
					np->sticky_pktinfo.ipi6_अगरindex;
				src_info.ipi6_addr = np->mcast_oअगर ? sk->sk_v6_daddr :
								     np->sticky_pktinfo.ipi6_addr;
				put_cmsg(&msg, SOL_IPV6, IPV6_2292PKTINFO, माप(src_info), &src_info);
			पूर्ण
			अगर (np->rxopt.bits.rxohlim) अणु
				पूर्णांक hlim = np->mcast_hops;
				put_cmsg(&msg, SOL_IPV6, IPV6_2292HOPLIMIT, माप(hlim), &hlim);
			पूर्ण
			अगर (np->rxopt.bits.rxflow) अणु
				__be32 flowinfo = np->rcv_flowinfo;

				put_cmsg(&msg, SOL_IPV6, IPV6_FLOWINFO, माप(flowinfo), &flowinfo);
			पूर्ण
		पूर्ण
		len -= msg.msg_controllen;
		वापस put_user(len, optlen);
	पूर्ण
	हाल IPV6_MTU:
	अणु
		काष्ठा dst_entry *dst;

		val = 0;
		rcu_पढ़ो_lock();
		dst = __sk_dst_get(sk);
		अगर (dst)
			val = dst_mtu(dst);
		rcu_पढ़ो_unlock();
		अगर (!val)
			वापस -ENOTCONN;
		अवरोध;
	पूर्ण

	हाल IPV6_V6ONLY:
		val = sk->sk_ipv6only;
		अवरोध;

	हाल IPV6_RECVPKTINFO:
		val = np->rxopt.bits.rxinfo;
		अवरोध;

	हाल IPV6_2292PKTINFO:
		val = np->rxopt.bits.rxoinfo;
		अवरोध;

	हाल IPV6_RECVHOPLIMIT:
		val = np->rxopt.bits.rxhlim;
		अवरोध;

	हाल IPV6_2292HOPLIMIT:
		val = np->rxopt.bits.rxohlim;
		अवरोध;

	हाल IPV6_RECVRTHDR:
		val = np->rxopt.bits.srcrt;
		अवरोध;

	हाल IPV6_2292RTHDR:
		val = np->rxopt.bits.osrcrt;
		अवरोध;

	हाल IPV6_HOPOPTS:
	हाल IPV6_RTHDRDSTOPTS:
	हाल IPV6_RTHDR:
	हाल IPV6_DSTOPTS:
	अणु
		काष्ठा ipv6_txoptions *opt;

		lock_sock(sk);
		opt = rcu_dereference_रक्षित(np->opt,
						lockdep_sock_is_held(sk));
		len = ipv6_माला_लोockopt_sticky(sk, opt, optname, optval, len);
		release_sock(sk);
		/* check अगर ipv6_माला_लोockopt_sticky() वापसs err code */
		अगर (len < 0)
			वापस len;
		वापस put_user(len, optlen);
	पूर्ण

	हाल IPV6_RECVHOPOPTS:
		val = np->rxopt.bits.hopopts;
		अवरोध;

	हाल IPV6_2292HOPOPTS:
		val = np->rxopt.bits.ohopopts;
		अवरोध;

	हाल IPV6_RECVDSTOPTS:
		val = np->rxopt.bits.dstopts;
		अवरोध;

	हाल IPV6_2292DSTOPTS:
		val = np->rxopt.bits.odstopts;
		अवरोध;

	हाल IPV6_TCLASS:
		val = np->tclass;
		अवरोध;

	हाल IPV6_RECVTCLASS:
		val = np->rxopt.bits.rxtclass;
		अवरोध;

	हाल IPV6_FLOWINFO:
		val = np->rxopt.bits.rxflow;
		अवरोध;

	हाल IPV6_RECVPATHMTU:
		val = np->rxopt.bits.rxpmtu;
		अवरोध;

	हाल IPV6_PATHMTU:
	अणु
		काष्ठा dst_entry *dst;
		काष्ठा ip6_mtuinfo mtuinfo;

		अगर (len < माप(mtuinfo))
			वापस -EINVAL;

		len = माप(mtuinfo);
		स_रखो(&mtuinfo, 0, माप(mtuinfo));

		rcu_पढ़ो_lock();
		dst = __sk_dst_get(sk);
		अगर (dst)
			mtuinfo.ip6m_mtu = dst_mtu(dst);
		rcu_पढ़ो_unlock();
		अगर (!mtuinfo.ip6m_mtu)
			वापस -ENOTCONN;

		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &mtuinfo, len))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल IPV6_TRANSPARENT:
		val = inet_sk(sk)->transparent;
		अवरोध;

	हाल IPV6_FREEBIND:
		val = inet_sk(sk)->मुक्तbind;
		अवरोध;

	हाल IPV6_RECVORIGDSTADDR:
		val = np->rxopt.bits.rxorigdstaddr;
		अवरोध;

	हाल IPV6_UNICAST_HOPS:
	हाल IPV6_MULTICAST_HOPS:
	अणु
		काष्ठा dst_entry *dst;

		अगर (optname == IPV6_UNICAST_HOPS)
			val = np->hop_limit;
		अन्यथा
			val = np->mcast_hops;

		अगर (val < 0) अणु
			rcu_पढ़ो_lock();
			dst = __sk_dst_get(sk);
			अगर (dst)
				val = ip6_dst_hoplimit(dst);
			rcu_पढ़ो_unlock();
		पूर्ण

		अगर (val < 0)
			val = sock_net(sk)->ipv6.devconf_all->hop_limit;
		अवरोध;
	पूर्ण

	हाल IPV6_MULTICAST_LOOP:
		val = np->mc_loop;
		अवरोध;

	हाल IPV6_MULTICAST_IF:
		val = np->mcast_oअगर;
		अवरोध;

	हाल IPV6_MULTICAST_ALL:
		val = np->mc_all;
		अवरोध;

	हाल IPV6_UNICAST_IF:
		val = (__क्रमce पूर्णांक)htonl((__u32) np->ucast_oअगर);
		अवरोध;

	हाल IPV6_MTU_DISCOVER:
		val = np->pmtudisc;
		अवरोध;

	हाल IPV6_RECVERR:
		val = np->recverr;
		अवरोध;

	हाल IPV6_FLOWINFO_SEND:
		val = np->sndflow;
		अवरोध;

	हाल IPV6_FLOWLABEL_MGR:
	अणु
		काष्ठा in6_flowlabel_req freq;
		पूर्णांक flags;

		अगर (len < माप(freq))
			वापस -EINVAL;

		अगर (copy_from_user(&freq, optval, माप(freq)))
			वापस -EFAULT;

		अगर (freq.flr_action != IPV6_FL_A_GET)
			वापस -EINVAL;

		len = माप(freq);
		flags = freq.flr_flags;

		स_रखो(&freq, 0, माप(freq));

		val = ipv6_flowlabel_opt_get(sk, &freq, flags);
		अगर (val < 0)
			वापस val;

		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &freq, len))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल IPV6_ADDR_PREFERENCES:
		val = 0;

		अगर (np->srcprefs & IPV6_PREFER_SRC_TMP)
			val |= IPV6_PREFER_SRC_TMP;
		अन्यथा अगर (np->srcprefs & IPV6_PREFER_SRC_PUBLIC)
			val |= IPV6_PREFER_SRC_PUBLIC;
		अन्यथा अणु
			/* XXX: should we वापस प्रणाली शेष? */
			val |= IPV6_PREFER_SRC_PUBTMP_DEFAULT;
		पूर्ण

		अगर (np->srcprefs & IPV6_PREFER_SRC_COA)
			val |= IPV6_PREFER_SRC_COA;
		अन्यथा
			val |= IPV6_PREFER_SRC_HOME;
		अवरोध;

	हाल IPV6_MINHOPCOUNT:
		val = np->min_hopcount;
		अवरोध;

	हाल IPV6_DONTFRAG:
		val = np->करोntfrag;
		अवरोध;

	हाल IPV6_AUTOFLOWLABEL:
		val = ip6_स्वतःflowlabel(sock_net(sk), np);
		अवरोध;

	हाल IPV6_RECVFRAGSIZE:
		val = np->rxopt.bits.recvfragsize;
		अवरोध;

	हाल IPV6_ROUTER_ALERT_ISOLATE:
		val = np->rtalert_isolate;
		अवरोध;

	हाल IPV6_RECVERR_RFC4884:
		val = np->recverr_rfc4884;
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
	len = min_t(अचिन्हित पूर्णांक, माप(पूर्णांक), len);
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक ipv6_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक err;

	अगर (level == SOL_IP && sk->sk_type != SOCK_RAW)
		वापस udp_prot.माला_लोockopt(sk, level, optname, optval, optlen);

	अगर (level != SOL_IPV6)
		वापस -ENOPROTOOPT;

	err = करो_ipv6_माला_लोockopt(sk, level, optname, optval, optlen, 0);
#अगर_घोषित CONFIG_NETFILTER
	/* we need to exclude all possible ENOPROTOOPTs except शेष हाल */
	अगर (err == -ENOPROTOOPT && optname != IPV6_2292PKTOPTIONS) अणु
		पूर्णांक len;

		अगर (get_user(len, optlen))
			वापस -EFAULT;

		err = nf_माला_लोockopt(sk, PF_INET6, optname, optval, &len);
		अगर (err >= 0)
			err = put_user(len, optlen);
	पूर्ण
#पूर्ण_अगर
	वापस err;
पूर्ण
EXPORT_SYMBOL(ipv6_माला_लोockopt);
