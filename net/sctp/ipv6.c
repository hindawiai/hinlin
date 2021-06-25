<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2002, 2004
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 * Copyright (c) 2002-2003 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * SCTP over IPv6.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Le Yanqun		    <yanqun.le@nokia.com>
 *    Hui Huang		    <hui.huang@nokia.com>
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Sridhar Samudrala	    <sri@us.ibm.com>
 *    Jon Grimm		    <jgrimm@us.ibm.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *
 * Based on:
 *	linux/net/ipv6/tcp_ipv6.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/ipsec.h>
#समावेश <linux/slab.h>

#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/seq_file.h>

#समावेश <net/protocol.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/transp_v6.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/udp_tunnel.h>

#समावेश <linux/uaccess.h>

अटल अंतरभूत पूर्णांक sctp_v6_addr_match_len(जोड़ sctp_addr *s1,
					 जोड़ sctp_addr *s2);
अटल व्योम sctp_v6_to_addr(जोड़ sctp_addr *addr, काष्ठा in6_addr *saddr,
			      __be16 port);
अटल पूर्णांक sctp_v6_cmp_addr(स्थिर जोड़ sctp_addr *addr1,
			    स्थिर जोड़ sctp_addr *addr2);

/* Event handler क्रम inet6 address addition/deletion events.
 * The sctp_local_addr_list needs to be protocted by a spin lock since
 * multiple notअगरiers (say IPv4 and IPv6) may be running at the same
 * समय and thus corrupt the list.
 * The पढ़ोer side is रक्षित with RCU.
 */
अटल पूर्णांक sctp_inet6addr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ ev,
				व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगरa = (काष्ठा inet6_अगरaddr *)ptr;
	काष्ठा sctp_sockaddr_entry *addr = शून्य;
	काष्ठा sctp_sockaddr_entry *temp;
	काष्ठा net *net = dev_net(अगरa->idev->dev);
	पूर्णांक found = 0;

	चयन (ev) अणु
	हाल NETDEV_UP:
		addr = kzalloc(माप(*addr), GFP_ATOMIC);
		अगर (addr) अणु
			addr->a.v6.sin6_family = AF_INET6;
			addr->a.v6.sin6_addr = अगरa->addr;
			addr->a.v6.sin6_scope_id = अगरa->idev->dev->अगरindex;
			addr->valid = 1;
			spin_lock_bh(&net->sctp.local_addr_lock);
			list_add_tail_rcu(&addr->list, &net->sctp.local_addr_list);
			sctp_addr_wq_mgmt(net, addr, SCTP_ADDR_NEW);
			spin_unlock_bh(&net->sctp.local_addr_lock);
		पूर्ण
		अवरोध;
	हाल NETDEV_DOWN:
		spin_lock_bh(&net->sctp.local_addr_lock);
		list_क्रम_each_entry_safe(addr, temp,
					&net->sctp.local_addr_list, list) अणु
			अगर (addr->a.sa.sa_family == AF_INET6 &&
					ipv6_addr_equal(&addr->a.v6.sin6_addr,
						&अगरa->addr)) अणु
				sctp_addr_wq_mgmt(net, addr, SCTP_ADDR_DEL);
				found = 1;
				addr->valid = 0;
				list_del_rcu(&addr->list);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&net->sctp.local_addr_lock);
		अगर (found)
			kमुक्त_rcu(addr, rcu);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sctp_inet6addr_notअगरier = अणु
	.notअगरier_call = sctp_inet6addr_event,
पूर्ण;

/* ICMP error handler. */
अटल पूर्णांक sctp_v6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा inet6_dev *idev;
	काष्ठा sock *sk;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_transport *transport;
	काष्ठा ipv6_pinfo *np;
	__u16 saveip, savesctp;
	पूर्णांक err, ret = 0;
	काष्ठा net *net = dev_net(skb->dev);

	idev = in6_dev_get(skb->dev);

	/* Fix up skb to look at the embedded net header. */
	saveip	 = skb->network_header;
	savesctp = skb->transport_header;
	skb_reset_network_header(skb);
	skb_set_transport_header(skb, offset);
	sk = sctp_err_lookup(net, AF_INET6, skb, sctp_hdr(skb), &asoc, &transport);
	/* Put back, the original poपूर्णांकers. */
	skb->network_header   = saveip;
	skb->transport_header = savesctp;
	अगर (!sk) अणु
		__ICMP6_INC_STATS(net, idev, ICMP6_MIB_INERRORS);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	/* Warning:  The sock lock is held.  Remember to call
	 * sctp_err_finish!
	 */

	चयन (type) अणु
	हाल ICMPV6_PKT_TOOBIG:
		अगर (ip6_sk_accept_pmtu(sk))
			sctp_icmp_frag_needed(sk, asoc, transport, ntohl(info));
		जाओ out_unlock;
	हाल ICMPV6_PARAMPROB:
		अगर (ICMPV6_UNK_NEXTHDR == code) अणु
			sctp_icmp_proto_unreachable(sk, asoc, transport);
			जाओ out_unlock;
		पूर्ण
		अवरोध;
	हाल NDISC_REसूचीECT:
		sctp_icmp_redirect(sk, transport, skb);
		जाओ out_unlock;
	शेष:
		अवरोध;
	पूर्ण

	np = inet6_sk(sk);
	icmpv6_err_convert(type, code, &err);
	अगर (!sock_owned_by_user(sk) && np->recverr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण अन्यथा अणु  /* Only an error on समयout */
		sk->sk_err_soft = err;
	पूर्ण

out_unlock:
	sctp_err_finish(sk, transport);
out:
	अगर (likely(idev != शून्य))
		in6_dev_put(idev);

	वापस ret;
पूर्ण

अटल पूर्णांक sctp_v6_xmit(काष्ठा sk_buff *skb, काष्ठा sctp_transport *t)
अणु
	काष्ठा dst_entry *dst = dst_clone(t->dst);
	काष्ठा flowi6 *fl6 = &t->fl.u.ip6;
	काष्ठा sock *sk = skb->sk;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	__u8 tclass = np->tclass;
	__be32 label;

	pr_debug("%s: skb:%p, len:%d, src:%pI6 dst:%pI6\n", __func__, skb,
		 skb->len, &fl6->saddr, &fl6->daddr);

	अगर (t->dscp & SCTP_DSCP_SET_MASK)
		tclass = t->dscp & SCTP_DSCP_VAL_MASK;

	अगर (INET_ECN_is_capable(tclass))
		IP6_ECN_flow_xmit(sk, fl6->flowlabel);

	अगर (!(t->param_flags & SPP_PMTUD_ENABLE))
		skb->ignore_df = 1;

	SCTP_INC_STATS(sock_net(sk), SCTP_MIB_OUTSCTPPACKS);

	अगर (!t->encap_port || !sctp_sk(sk)->udp_port) अणु
		पूर्णांक res;

		skb_dst_set(skb, dst);
		rcu_पढ़ो_lock();
		res = ip6_xmit(sk, skb, fl6, sk->sk_mark,
			       rcu_dereference(np->opt),
			       tclass, sk->sk_priority);
		rcu_पढ़ो_unlock();
		वापस res;
	पूर्ण

	अगर (skb_is_gso(skb))
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;

	skb->encapsulation = 1;
	skb_reset_inner_mac_header(skb);
	skb_reset_inner_transport_header(skb);
	skb_set_inner_ipproto(skb, IPPROTO_SCTP);
	label = ip6_make_flowlabel(sock_net(sk), skb, fl6->flowlabel, true, fl6);

	वापस udp_tunnel6_xmit_skb(dst, sk, skb, शून्य, &fl6->saddr,
				    &fl6->daddr, tclass, ip6_dst_hoplimit(dst),
				    label, sctp_sk(sk)->udp_port, t->encap_port, false);
पूर्ण

/* Returns the dst cache entry क्रम the given source and destination ip
 * addresses.
 */
अटल व्योम sctp_v6_get_dst(काष्ठा sctp_transport *t, जोड़ sctp_addr *saddr,
			    काष्ठा flowi *fl, काष्ठा sock *sk)
अणु
	काष्ठा sctp_association *asoc = t->asoc;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा flowi _fl;
	काष्ठा flowi6 *fl6 = &_fl.u.ip6;
	काष्ठा sctp_bind_addr *bp;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sctp_sockaddr_entry *laddr;
	जोड़ sctp_addr *daddr = &t->ipaddr;
	जोड़ sctp_addr dst_saddr;
	काष्ठा in6_addr *final_p, final;
	क्रमागत sctp_scope scope;
	__u8 matchlen = 0;

	स_रखो(&_fl, 0, माप(_fl));
	fl6->daddr = daddr->v6.sin6_addr;
	fl6->fl6_dport = daddr->v6.sin6_port;
	fl6->flowi6_proto = IPPROTO_SCTP;
	अगर (ipv6_addr_type(&daddr->v6.sin6_addr) & IPV6_ADDR_LINKLOCAL)
		fl6->flowi6_oअगर = daddr->v6.sin6_scope_id;
	अन्यथा अगर (asoc)
		fl6->flowi6_oअगर = asoc->base.sk->sk_bound_dev_अगर;
	अगर (t->flowlabel & SCTP_FLOWLABEL_SET_MASK)
		fl6->flowlabel = htonl(t->flowlabel & SCTP_FLOWLABEL_VAL_MASK);

	अगर (np->sndflow && (fl6->flowlabel & IPV6_FLOWLABEL_MASK)) अणु
		काष्ठा ip6_flowlabel *flowlabel;

		flowlabel = fl6_sock_lookup(sk, fl6->flowlabel);
		अगर (IS_ERR(flowlabel))
			जाओ out;
		fl6_sock_release(flowlabel);
	पूर्ण

	pr_debug("%s: dst=%pI6 ", __func__, &fl6->daddr);

	अगर (asoc)
		fl6->fl6_sport = htons(asoc->base.bind_addr.port);

	अगर (saddr) अणु
		fl6->saddr = saddr->v6.sin6_addr;
		अगर (!fl6->fl6_sport)
			fl6->fl6_sport = saddr->v6.sin6_port;

		pr_debug("src=%pI6 - ", &fl6->saddr);
	पूर्ण

	rcu_पढ़ो_lock();
	final_p = fl6_update_dst(fl6, rcu_dereference(np->opt), &final);
	rcu_पढ़ो_unlock();

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, fl6, final_p);
	अगर (!asoc || saddr) अणु
		t->dst = dst;
		स_नकल(fl, &_fl, माप(_fl));
		जाओ out;
	पूर्ण

	bp = &asoc->base.bind_addr;
	scope = sctp_scope(daddr);
	/* ip6_dst_lookup has filled in the fl6->saddr क्रम us.  Check
	 * to see अगर we can use it.
	 */
	अगर (!IS_ERR(dst)) अणु
		/* Walk through the bind address list and look क्रम a bind
		 * address that matches the source address of the वापसed dst.
		 */
		sctp_v6_to_addr(&dst_saddr, &fl6->saddr, htons(bp->port));
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
			अगर (!laddr->valid || laddr->state == SCTP_ADDR_DEL ||
			    (laddr->state != SCTP_ADDR_SRC &&
			     !asoc->src_out_of_asoc_ok))
				जारी;

			/* Do not compare against v4 addrs */
			अगर ((laddr->a.sa.sa_family == AF_INET6) &&
			    (sctp_v6_cmp_addr(&dst_saddr, &laddr->a))) अणु
				rcu_पढ़ो_unlock();
				t->dst = dst;
				स_नकल(fl, &_fl, माप(_fl));
				जाओ out;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		/* None of the bound addresses match the source address of the
		 * dst. So release it.
		 */
		dst_release(dst);
		dst = शून्य;
	पूर्ण

	/* Walk through the bind address list and try to get the
	 * best source address क्रम a given destination.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
		काष्ठा dst_entry *bdst;
		__u8 bmatchlen;

		अगर (!laddr->valid ||
		    laddr->state != SCTP_ADDR_SRC ||
		    laddr->a.sa.sa_family != AF_INET6 ||
		    scope > sctp_scope(&laddr->a))
			जारी;

		fl6->saddr = laddr->a.v6.sin6_addr;
		fl6->fl6_sport = laddr->a.v6.sin6_port;
		final_p = fl6_update_dst(fl6, rcu_dereference(np->opt), &final);
		bdst = ip6_dst_lookup_flow(sock_net(sk), sk, fl6, final_p);

		अगर (IS_ERR(bdst))
			जारी;

		अगर (ipv6_chk_addr(dev_net(bdst->dev),
				  &laddr->a.v6.sin6_addr, bdst->dev, 1)) अणु
			अगर (!IS_ERR_OR_शून्य(dst))
				dst_release(dst);
			dst = bdst;
			t->dst = dst;
			स_नकल(fl, &_fl, माप(_fl));
			अवरोध;
		पूर्ण

		bmatchlen = sctp_v6_addr_match_len(daddr, &laddr->a);
		अगर (matchlen > bmatchlen) अणु
			dst_release(bdst);
			जारी;
		पूर्ण

		अगर (!IS_ERR_OR_शून्य(dst))
			dst_release(dst);
		dst = bdst;
		matchlen = bmatchlen;
		t->dst = dst;
		स_नकल(fl, &_fl, माप(_fl));
	पूर्ण
	rcu_पढ़ो_unlock();

out:
	अगर (!IS_ERR_OR_शून्य(dst)) अणु
		काष्ठा rt6_info *rt;

		rt = (काष्ठा rt6_info *)dst;
		t->dst_cookie = rt6_get_cookie(rt);
		pr_debug("rt6_dst:%pI6/%d rt6_src:%pI6\n",
			 &rt->rt6i_dst.addr, rt->rt6i_dst.plen,
			 &fl->u.ip6.saddr);
	पूर्ण अन्यथा अणु
		t->dst = शून्य;
		pr_debug("no route\n");
	पूर्ण
पूर्ण

/* Returns the number of consecutive initial bits that match in the 2 ipv6
 * addresses.
 */
अटल अंतरभूत पूर्णांक sctp_v6_addr_match_len(जोड़ sctp_addr *s1,
					 जोड़ sctp_addr *s2)
अणु
	वापस ipv6_addr_dअगरf(&s1->v6.sin6_addr, &s2->v6.sin6_addr);
पूर्ण

/* Fills in the source address(saddr) based on the destination address(daddr)
 * and asoc's bind address list.
 */
अटल व्योम sctp_v6_get_saddr(काष्ठा sctp_sock *sk,
			      काष्ठा sctp_transport *t,
			      काष्ठा flowi *fl)
अणु
	काष्ठा flowi6 *fl6 = &fl->u.ip6;
	जोड़ sctp_addr *saddr = &t->saddr;

	pr_debug("%s: asoc:%p dst:%p\n", __func__, t->asoc, t->dst);

	अगर (t->dst) अणु
		saddr->v6.sin6_family = AF_INET6;
		saddr->v6.sin6_addr = fl6->saddr;
	पूर्ण
पूर्ण

/* Make a copy of all potential local addresses. */
अटल व्योम sctp_v6_copy_addrlist(काष्ठा list_head *addrlist,
				  काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *in6_dev;
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा sctp_sockaddr_entry *addr;

	rcu_पढ़ो_lock();
	अगर ((in6_dev = __in6_dev_get(dev)) == शून्य) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	पढ़ो_lock_bh(&in6_dev->lock);
	list_क्रम_each_entry(अगरp, &in6_dev->addr_list, अगर_list) अणु
		/* Add the address to the local list.  */
		addr = kzalloc(माप(*addr), GFP_ATOMIC);
		अगर (addr) अणु
			addr->a.v6.sin6_family = AF_INET6;
			addr->a.v6.sin6_addr = अगरp->addr;
			addr->a.v6.sin6_scope_id = dev->अगरindex;
			addr->valid = 1;
			INIT_LIST_HEAD(&addr->list);
			list_add_tail(&addr->list, addrlist);
		पूर्ण
	पूर्ण

	पढ़ो_unlock_bh(&in6_dev->lock);
	rcu_पढ़ो_unlock();
पूर्ण

/* Copy over any ip options */
अटल व्योम sctp_v6_copy_ip_options(काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
	काष्ठा ipv6_pinfo *newnp, *np = inet6_sk(sk);
	काष्ठा ipv6_txoptions *opt;

	newnp = inet6_sk(newsk);

	rcu_पढ़ो_lock();
	opt = rcu_dereference(np->opt);
	अगर (opt) अणु
		opt = ipv6_dup_options(newsk, opt);
		अगर (!opt)
			pr_err("%s: Failed to copy ip options\n", __func__);
	पूर्ण
	RCU_INIT_POINTER(newnp->opt, opt);
	rcu_पढ़ो_unlock();
पूर्ण

/* Account क्रम the IP options */
अटल पूर्णांक sctp_v6_ip_options_len(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_txoptions *opt;
	पूर्णांक len = 0;

	rcu_पढ़ो_lock();
	opt = rcu_dereference(np->opt);
	अगर (opt)
		len = opt->opt_flen + opt->opt_nflen;

	rcu_पढ़ो_unlock();
	वापस len;
पूर्ण

/* Initialize a sockaddr_storage from in incoming skb. */
अटल व्योम sctp_v6_from_skb(जोड़ sctp_addr *addr, काष्ठा sk_buff *skb,
			     पूर्णांक is_saddr)
अणु
	/* Always called on head skb, so this is safe */
	काष्ठा sctphdr *sh = sctp_hdr(skb);
	काष्ठा sockaddr_in6 *sa = &addr->v6;

	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_flowinfo = 0; /* FIXME */
	addr->v6.sin6_scope_id = ((काष्ठा inet6_skb_parm *)skb->cb)->iअगर;

	अगर (is_saddr) अणु
		sa->sin6_port = sh->source;
		sa->sin6_addr = ipv6_hdr(skb)->saddr;
	पूर्ण अन्यथा अणु
		sa->sin6_port = sh->dest;
		sa->sin6_addr = ipv6_hdr(skb)->daddr;
	पूर्ण
पूर्ण

/* Initialize an sctp_addr from a socket. */
अटल व्योम sctp_v6_from_sk(जोड़ sctp_addr *addr, काष्ठा sock *sk)
अणु
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_port = 0;
	addr->v6.sin6_addr = sk->sk_v6_rcv_saddr;
पूर्ण

/* Initialize sk->sk_rcv_saddr from sctp_addr. */
अटल व्योम sctp_v6_to_sk_saddr(जोड़ sctp_addr *addr, काष्ठा sock *sk)
अणु
	अगर (addr->sa.sa_family == AF_INET) अणु
		sk->sk_v6_rcv_saddr.s6_addr32[0] = 0;
		sk->sk_v6_rcv_saddr.s6_addr32[1] = 0;
		sk->sk_v6_rcv_saddr.s6_addr32[2] = htonl(0x0000ffff);
		sk->sk_v6_rcv_saddr.s6_addr32[3] =
			addr->v4.sin_addr.s_addr;
	पूर्ण अन्यथा अणु
		sk->sk_v6_rcv_saddr = addr->v6.sin6_addr;
	पूर्ण
पूर्ण

/* Initialize sk->sk_daddr from sctp_addr. */
अटल व्योम sctp_v6_to_sk_daddr(जोड़ sctp_addr *addr, काष्ठा sock *sk)
अणु
	अगर (addr->sa.sa_family == AF_INET) अणु
		sk->sk_v6_daddr.s6_addr32[0] = 0;
		sk->sk_v6_daddr.s6_addr32[1] = 0;
		sk->sk_v6_daddr.s6_addr32[2] = htonl(0x0000ffff);
		sk->sk_v6_daddr.s6_addr32[3] = addr->v4.sin_addr.s_addr;
	पूर्ण अन्यथा अणु
		sk->sk_v6_daddr = addr->v6.sin6_addr;
	पूर्ण
पूर्ण

/* Initialize a sctp_addr from an address parameter. */
अटल व्योम sctp_v6_from_addr_param(जोड़ sctp_addr *addr,
				    जोड़ sctp_addr_param *param,
				    __be16 port, पूर्णांक iअगर)
अणु
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_port = port;
	addr->v6.sin6_flowinfo = 0; /* BUG */
	addr->v6.sin6_addr = param->v6.addr;
	addr->v6.sin6_scope_id = iअगर;
पूर्ण

/* Initialize an address parameter from a sctp_addr and वापस the length
 * of the address parameter.
 */
अटल पूर्णांक sctp_v6_to_addr_param(स्थिर जोड़ sctp_addr *addr,
				 जोड़ sctp_addr_param *param)
अणु
	पूर्णांक length = माप(काष्ठा sctp_ipv6addr_param);

	param->v6.param_hdr.type = SCTP_PARAM_IPV6_ADDRESS;
	param->v6.param_hdr.length = htons(length);
	param->v6.addr = addr->v6.sin6_addr;

	वापस length;
पूर्ण

/* Initialize a sctp_addr from काष्ठा in6_addr. */
अटल व्योम sctp_v6_to_addr(जोड़ sctp_addr *addr, काष्ठा in6_addr *saddr,
			      __be16 port)
अणु
	addr->sa.sa_family = AF_INET6;
	addr->v6.sin6_port = port;
	addr->v6.sin6_flowinfo = 0;
	addr->v6.sin6_addr = *saddr;
	addr->v6.sin6_scope_id = 0;
पूर्ण

अटल पूर्णांक __sctp_v6_cmp_addr(स्थिर जोड़ sctp_addr *addr1,
			      स्थिर जोड़ sctp_addr *addr2)
अणु
	अगर (addr1->sa.sa_family != addr2->sa.sa_family) अणु
		अगर (addr1->sa.sa_family == AF_INET &&
		    addr2->sa.sa_family == AF_INET6 &&
		    ipv6_addr_v4mapped(&addr2->v6.sin6_addr) &&
		    addr2->v6.sin6_addr.s6_addr32[3] ==
		    addr1->v4.sin_addr.s_addr)
			वापस 1;

		अगर (addr2->sa.sa_family == AF_INET &&
		    addr1->sa.sa_family == AF_INET6 &&
		    ipv6_addr_v4mapped(&addr1->v6.sin6_addr) &&
		    addr1->v6.sin6_addr.s6_addr32[3] ==
		    addr2->v4.sin_addr.s_addr)
			वापस 1;

		वापस 0;
	पूर्ण

	अगर (!ipv6_addr_equal(&addr1->v6.sin6_addr, &addr2->v6.sin6_addr))
		वापस 0;

	/* If this is a linklocal address, compare the scope_id. */
	अगर ((ipv6_addr_type(&addr1->v6.sin6_addr) & IPV6_ADDR_LINKLOCAL) &&
	    addr1->v6.sin6_scope_id && addr2->v6.sin6_scope_id &&
	    addr1->v6.sin6_scope_id != addr2->v6.sin6_scope_id)
		वापस 0;

	वापस 1;
पूर्ण

/* Compare addresses exactly.
 * v4-mapped-v6 is also in consideration.
 */
अटल पूर्णांक sctp_v6_cmp_addr(स्थिर जोड़ sctp_addr *addr1,
			    स्थिर जोड़ sctp_addr *addr2)
अणु
	वापस __sctp_v6_cmp_addr(addr1, addr2) &&
	       addr1->v6.sin6_port == addr2->v6.sin6_port;
पूर्ण

/* Initialize addr काष्ठा to INADDR_ANY. */
अटल व्योम sctp_v6_inaddr_any(जोड़ sctp_addr *addr, __be16 port)
अणु
	स_रखो(addr, 0x00, माप(जोड़ sctp_addr));
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_port = port;
पूर्ण

/* Is this a wildcard address? */
अटल पूर्णांक sctp_v6_is_any(स्थिर जोड़ sctp_addr *addr)
अणु
	वापस ipv6_addr_any(&addr->v6.sin6_addr);
पूर्ण

/* Should this be available क्रम binding?   */
अटल पूर्णांक sctp_v6_available(जोड़ sctp_addr *addr, काष्ठा sctp_sock *sp)
अणु
	पूर्णांक type;
	काष्ठा net *net = sock_net(&sp->inet.sk);
	स्थिर काष्ठा in6_addr *in6 = (स्थिर काष्ठा in6_addr *)&addr->v6.sin6_addr;

	type = ipv6_addr_type(in6);
	अगर (IPV6_ADDR_ANY == type)
		वापस 1;
	अगर (type == IPV6_ADDR_MAPPED) अणु
		अगर (sp && ipv6_only_sock(sctp_opt2sk(sp)))
			वापस 0;
		sctp_v6_map_v4(addr);
		वापस sctp_get_af_specअगरic(AF_INET)->available(addr, sp);
	पूर्ण
	अगर (!(type & IPV6_ADDR_UNICAST))
		वापस 0;

	वापस ipv6_can_nonlocal_bind(net, &sp->inet) ||
	       ipv6_chk_addr(net, in6, शून्य, 0);
पूर्ण

/* This function checks अगर the address is a valid address to be used क्रम
 * SCTP.
 *
 * Output:
 * Return 0 - If the address is a non-unicast or an illegal address.
 * Return 1 - If the address is a unicast.
 */
अटल पूर्णांक sctp_v6_addr_valid(जोड़ sctp_addr *addr,
			      काष्ठा sctp_sock *sp,
			      स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = ipv6_addr_type(&addr->v6.sin6_addr);

	/* Support v4-mapped-v6 address. */
	अगर (ret == IPV6_ADDR_MAPPED) अणु
		/* Note: This routine is used in input, so v4-mapped-v6
		 * are disallowed here when there is no sctp_sock.
		 */
		अगर (sp && ipv6_only_sock(sctp_opt2sk(sp)))
			वापस 0;
		sctp_v6_map_v4(addr);
		वापस sctp_get_af_specअगरic(AF_INET)->addr_valid(addr, sp, skb);
	पूर्ण

	/* Is this a non-unicast address */
	अगर (!(ret & IPV6_ADDR_UNICAST))
		वापस 0;

	वापस 1;
पूर्ण

/* What is the scope of 'addr'?  */
अटल क्रमागत sctp_scope sctp_v6_scope(जोड़ sctp_addr *addr)
अणु
	क्रमागत sctp_scope retval;
	पूर्णांक v6scope;

	/* The IPv6 scope is really a set of bit fields.
	 * See IFA_* in <net/अगर_inet6.h>.  Map to a generic SCTP scope.
	 */

	v6scope = ipv6_addr_scope(&addr->v6.sin6_addr);
	चयन (v6scope) अणु
	हाल IFA_HOST:
		retval = SCTP_SCOPE_LOOPBACK;
		अवरोध;
	हाल IFA_LINK:
		retval = SCTP_SCOPE_LINK;
		अवरोध;
	हाल IFA_SITE:
		retval = SCTP_SCOPE_PRIVATE;
		अवरोध;
	शेष:
		retval = SCTP_SCOPE_GLOBAL;
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/* Create and initialize a new sk क्रम the socket to be वापसed by accept(). */
अटल काष्ठा sock *sctp_v6_create_accept_sk(काष्ठा sock *sk,
					     काष्ठा sctp_association *asoc,
					     bool kern)
अणु
	काष्ठा sock *newsk;
	काष्ठा ipv6_pinfo *newnp, *np = inet6_sk(sk);
	काष्ठा sctp6_sock *newsctp6sk;

	newsk = sk_alloc(sock_net(sk), PF_INET6, GFP_KERNEL, sk->sk_prot, kern);
	अगर (!newsk)
		जाओ out;

	sock_init_data(शून्य, newsk);

	sctp_copy_sock(newsk, sk, asoc);
	sock_reset_flag(sk, SOCK_ZAPPED);

	newsctp6sk = (काष्ठा sctp6_sock *)newsk;
	inet_sk(newsk)->pinet6 = &newsctp6sk->inet6;

	sctp_sk(newsk)->v4mapped = sctp_sk(sk)->v4mapped;

	newnp = inet6_sk(newsk);

	स_नकल(newnp, np, माप(काष्ठा ipv6_pinfo));
	newnp->ipv6_mc_list = शून्य;
	newnp->ipv6_ac_list = शून्य;
	newnp->ipv6_fl_list = शून्य;

	sctp_v6_copy_ip_options(sk, newsk);

	/* Initialize sk's sport, dport, rcv_saddr and daddr क्रम माला_लोockname()
	 * and getpeername().
	 */
	sctp_v6_to_sk_daddr(&asoc->peer.primary_addr, newsk);

	newsk->sk_v6_rcv_saddr = sk->sk_v6_rcv_saddr;

	sk_refcnt_debug_inc(newsk);

	अगर (newsk->sk_prot->init(newsk)) अणु
		sk_common_release(newsk);
		newsk = शून्य;
	पूर्ण

out:
	वापस newsk;
पूर्ण

/* Format a sockaddr क्रम वापस to user space. This makes sure the वापस is
 * AF_INET or AF_INET6 depending on the SCTP_I_WANT_MAPPED_V4_ADDR option.
 */
अटल पूर्णांक sctp_v6_addr_to_user(काष्ठा sctp_sock *sp, जोड़ sctp_addr *addr)
अणु
	अगर (sp->v4mapped) अणु
		अगर (addr->sa.sa_family == AF_INET)
			sctp_v4_map_v6(addr);
	पूर्ण अन्यथा अणु
		अगर (addr->sa.sa_family == AF_INET6 &&
		    ipv6_addr_v4mapped(&addr->v6.sin6_addr))
			sctp_v6_map_v4(addr);
	पूर्ण

	अगर (addr->sa.sa_family == AF_INET) अणु
		स_रखो(addr->v4.sin_zero, 0, माप(addr->v4.sin_zero));
		वापस माप(काष्ठा sockaddr_in);
	पूर्ण
	वापस माप(काष्ठा sockaddr_in6);
पूर्ण

/* Where did this skb come from?  */
अटल पूर्णांक sctp_v6_skb_iअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस IP6CB(skb)->iअगर;
पूर्ण

/* Was this packet marked by Explicit Congestion Notअगरication? */
अटल पूर्णांक sctp_v6_is_ce(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस *((__u32 *)(ipv6_hdr(skb))) & (__क्रमce __u32)htonl(1 << 20);
पूर्ण

/* Dump the v6 addr to the seq file. */
अटल व्योम sctp_v6_seq_dump_addr(काष्ठा seq_file *seq, जोड़ sctp_addr *addr)
अणु
	seq_म_लिखो(seq, "%pI6 ", &addr->v6.sin6_addr);
पूर्ण

अटल व्योम sctp_v6_ecn_capable(काष्ठा sock *sk)
अणु
	inet6_sk(sk)->tclass |= INET_ECN_ECT_0;
पूर्ण

/* Initialize a PF_INET msgname from a ulpevent. */
अटल व्योम sctp_inet6_event_msgname(काष्ठा sctp_ulpevent *event,
				     अक्षर *msgname, पूर्णांक *addrlen)
अणु
	जोड़ sctp_addr *addr;
	काष्ठा sctp_association *asoc;
	जोड़ sctp_addr *paddr;

	अगर (!msgname)
		वापस;

	addr = (जोड़ sctp_addr *)msgname;
	asoc = event->asoc;
	paddr = &asoc->peer.primary_addr;

	अगर (paddr->sa.sa_family == AF_INET) अणु
		addr->v4.sin_family = AF_INET;
		addr->v4.sin_port = htons(asoc->peer.port);
		addr->v4.sin_addr = paddr->v4.sin_addr;
	पूर्ण अन्यथा अणु
		addr->v6.sin6_family = AF_INET6;
		addr->v6.sin6_flowinfo = 0;
		अगर (ipv6_addr_type(&paddr->v6.sin6_addr) & IPV6_ADDR_LINKLOCAL)
			addr->v6.sin6_scope_id = paddr->v6.sin6_scope_id;
		अन्यथा
			addr->v6.sin6_scope_id = 0;
		addr->v6.sin6_port = htons(asoc->peer.port);
		addr->v6.sin6_addr = paddr->v6.sin6_addr;
	पूर्ण

	*addrlen = sctp_v6_addr_to_user(sctp_sk(asoc->base.sk), addr);
पूर्ण

/* Initialize a msg_name from an inbound skb. */
अटल व्योम sctp_inet6_skb_msgname(काष्ठा sk_buff *skb, अक्षर *msgname,
				   पूर्णांक *addr_len)
अणु
	जोड़ sctp_addr *addr;
	काष्ठा sctphdr *sh;

	अगर (!msgname)
		वापस;

	addr = (जोड़ sctp_addr *)msgname;
	sh = sctp_hdr(skb);

	अगर (ip_hdr(skb)->version == 4) अणु
		addr->v4.sin_family = AF_INET;
		addr->v4.sin_port = sh->source;
		addr->v4.sin_addr.s_addr = ip_hdr(skb)->saddr;
	पूर्ण अन्यथा अणु
		addr->v6.sin6_family = AF_INET6;
		addr->v6.sin6_flowinfo = 0;
		addr->v6.sin6_port = sh->source;
		addr->v6.sin6_addr = ipv6_hdr(skb)->saddr;
		अगर (ipv6_addr_type(&addr->v6.sin6_addr) & IPV6_ADDR_LINKLOCAL)
			addr->v6.sin6_scope_id = sctp_v6_skb_iअगर(skb);
		अन्यथा
			addr->v6.sin6_scope_id = 0;
	पूर्ण

	*addr_len = sctp_v6_addr_to_user(sctp_sk(skb->sk), addr);
पूर्ण

/* Do we support this AF? */
अटल पूर्णांक sctp_inet6_af_supported(sa_family_t family, काष्ठा sctp_sock *sp)
अणु
	चयन (family) अणु
	हाल AF_INET6:
		वापस 1;
	/* v4-mapped-v6 addresses */
	हाल AF_INET:
		अगर (!__ipv6_only_sock(sctp_opt2sk(sp)))
			वापस 1;
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Address matching with wildcards allowed.  This extra level
 * of indirection lets us choose whether a PF_INET6 should
 * disallow any v4 addresses अगर we so choose.
 */
अटल पूर्णांक sctp_inet6_cmp_addr(स्थिर जोड़ sctp_addr *addr1,
			       स्थिर जोड़ sctp_addr *addr2,
			       काष्ठा sctp_sock *opt)
अणु
	काष्ठा sock *sk = sctp_opt2sk(opt);
	काष्ठा sctp_af *af1, *af2;

	af1 = sctp_get_af_specअगरic(addr1->sa.sa_family);
	af2 = sctp_get_af_specअगरic(addr2->sa.sa_family);

	अगर (!af1 || !af2)
		वापस 0;

	/* If the socket is IPv6 only, v4 addrs will not match */
	अगर (__ipv6_only_sock(sk) && af1 != af2)
		वापस 0;

	/* Today, wildcard AF_INET/AF_INET6. */
	अगर (sctp_is_any(sk, addr1) || sctp_is_any(sk, addr2))
		वापस 1;

	अगर (addr1->sa.sa_family == AF_INET && addr2->sa.sa_family == AF_INET)
		वापस addr1->v4.sin_addr.s_addr == addr2->v4.sin_addr.s_addr;

	वापस __sctp_v6_cmp_addr(addr1, addr2);
पूर्ण

/* Verअगरy that the provided sockaddr looks bindable.   Common verअगरication,
 * has alपढ़ोy been taken care of.
 */
अटल पूर्णांक sctp_inet6_bind_verअगरy(काष्ठा sctp_sock *opt, जोड़ sctp_addr *addr)
अणु
	काष्ठा sctp_af *af;

	/* ASSERT: address family has alपढ़ोy been verअगरied. */
	अगर (addr->sa.sa_family != AF_INET6)
		af = sctp_get_af_specअगरic(addr->sa.sa_family);
	अन्यथा अणु
		पूर्णांक type = ipv6_addr_type(&addr->v6.sin6_addr);
		काष्ठा net_device *dev;

		अगर (type & IPV6_ADDR_LINKLOCAL) अणु
			काष्ठा net *net;
			अगर (!addr->v6.sin6_scope_id)
				वापस 0;
			net = sock_net(&opt->inet.sk);
			rcu_पढ़ो_lock();
			dev = dev_get_by_index_rcu(net, addr->v6.sin6_scope_id);
			अगर (!dev || !(ipv6_can_nonlocal_bind(net, &opt->inet) ||
				      ipv6_chk_addr(net, &addr->v6.sin6_addr,
						    dev, 0))) अणु
				rcu_पढ़ो_unlock();
				वापस 0;
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण

		af = opt->pf->af;
	पूर्ण
	वापस af->available(addr, opt);
पूर्ण

/* Verअगरy that the provided sockaddr looks sendable.   Common verअगरication,
 * has alपढ़ोy been taken care of.
 */
अटल पूर्णांक sctp_inet6_send_verअगरy(काष्ठा sctp_sock *opt, जोड़ sctp_addr *addr)
अणु
	काष्ठा sctp_af *af = शून्य;

	/* ASSERT: address family has alपढ़ोy been verअगरied. */
	अगर (addr->sa.sa_family != AF_INET6)
		af = sctp_get_af_specअगरic(addr->sa.sa_family);
	अन्यथा अणु
		पूर्णांक type = ipv6_addr_type(&addr->v6.sin6_addr);
		काष्ठा net_device *dev;

		अगर (type & IPV6_ADDR_LINKLOCAL) अणु
			अगर (!addr->v6.sin6_scope_id)
				वापस 0;
			rcu_पढ़ो_lock();
			dev = dev_get_by_index_rcu(sock_net(&opt->inet.sk),
						   addr->v6.sin6_scope_id);
			rcu_पढ़ो_unlock();
			अगर (!dev)
				वापस 0;
		पूर्ण
		af = opt->pf->af;
	पूर्ण

	वापस af != शून्य;
पूर्ण

/* Fill in Supported Address Type inक्रमmation क्रम INIT and INIT-ACK
 * chunks.   Note: In the future, we may want to look at sock options
 * to determine whether a PF_INET6 socket really wants to have IPV4
 * addresses.
 * Returns number of addresses supported.
 */
अटल पूर्णांक sctp_inet6_supported_addrs(स्थिर काष्ठा sctp_sock *opt,
				      __be16 *types)
अणु
	types[0] = SCTP_PARAM_IPV6_ADDRESS;
	अगर (!opt || !ipv6_only_sock(sctp_opt2sk(opt))) अणु
		types[1] = SCTP_PARAM_IPV4_ADDRESS;
		वापस 2;
	पूर्ण
	वापस 1;
पूर्ण

/* Handle SCTP_I_WANT_MAPPED_V4_ADDR क्रम getpeername() and माला_लोockname() */
अटल पूर्णांक sctp_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			पूर्णांक peer)
अणु
	पूर्णांक rc;

	rc = inet6_getname(sock, uaddr, peer);

	अगर (rc < 0)
		वापस rc;

	rc = sctp_v6_addr_to_user(sctp_sk(sock->sk),
					  (जोड़ sctp_addr *)uaddr);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा proto_ops inet6_seqpacket_ops = अणु
	.family		   = PF_INET6,
	.owner		   = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = inet6_bind,
	.connect	   = sctp_inet_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = inet_accept,
	.getname	   = sctp_getname,
	.poll		   = sctp_poll,
	.ioctl		   = inet6_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sctp_inet_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = inet_recvmsg,
	.mmap		   = sock_no_mmap,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet6_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा inet_protosw sctpv6_seqpacket_protosw = अणु
	.type          = SOCK_SEQPACKET,
	.protocol      = IPPROTO_SCTP,
	.prot 	       = &sctpv6_prot,
	.ops           = &inet6_seqpacket_ops,
	.flags         = SCTP_PROTOSW_FLAG
पूर्ण;
अटल काष्ठा inet_protosw sctpv6_stream_protosw = अणु
	.type          = SOCK_STREAM,
	.protocol      = IPPROTO_SCTP,
	.prot 	       = &sctpv6_prot,
	.ops           = &inet6_seqpacket_ops,
	.flags         = SCTP_PROTOSW_FLAG,
पूर्ण;

अटल पूर्णांक sctp6_rcv(काष्ठा sk_buff *skb)
अणु
	SCTP_INPUT_CB(skb)->encap_port = 0;
	वापस sctp_rcv(skb) ? -1 : 0;
पूर्ण

अटल स्थिर काष्ठा inet6_protocol sctpv6_protocol = अणु
	.handler      = sctp6_rcv,
	.err_handler  = sctp_v6_err,
	.flags        = INET6_PROTO_NOPOLICY | INET6_PROTO_FINAL,
पूर्ण;

अटल काष्ठा sctp_af sctp_af_inet6 = अणु
	.sa_family	   = AF_INET6,
	.sctp_xmit	   = sctp_v6_xmit,
	.setsockopt	   = ipv6_setsockopt,
	.माला_लोockopt	   = ipv6_माला_लोockopt,
	.get_dst	   = sctp_v6_get_dst,
	.get_saddr	   = sctp_v6_get_saddr,
	.copy_addrlist	   = sctp_v6_copy_addrlist,
	.from_skb	   = sctp_v6_from_skb,
	.from_sk	   = sctp_v6_from_sk,
	.from_addr_param   = sctp_v6_from_addr_param,
	.to_addr_param	   = sctp_v6_to_addr_param,
	.cmp_addr	   = sctp_v6_cmp_addr,
	.scope		   = sctp_v6_scope,
	.addr_valid	   = sctp_v6_addr_valid,
	.inaddr_any	   = sctp_v6_inaddr_any,
	.is_any		   = sctp_v6_is_any,
	.available	   = sctp_v6_available,
	.skb_iअगर	   = sctp_v6_skb_iअगर,
	.is_ce		   = sctp_v6_is_ce,
	.seq_dump_addr	   = sctp_v6_seq_dump_addr,
	.ecn_capable	   = sctp_v6_ecn_capable,
	.net_header_len	   = माप(काष्ठा ipv6hdr),
	.sockaddr_len	   = माप(काष्ठा sockaddr_in6),
	.ip_options_len	   = sctp_v6_ip_options_len,
पूर्ण;

अटल काष्ठा sctp_pf sctp_pf_inet6 = अणु
	.event_msgname = sctp_inet6_event_msgname,
	.skb_msgname   = sctp_inet6_skb_msgname,
	.af_supported  = sctp_inet6_af_supported,
	.cmp_addr      = sctp_inet6_cmp_addr,
	.bind_verअगरy   = sctp_inet6_bind_verअगरy,
	.send_verअगरy   = sctp_inet6_send_verअगरy,
	.supported_addrs = sctp_inet6_supported_addrs,
	.create_accept_sk = sctp_v6_create_accept_sk,
	.addr_to_user  = sctp_v6_addr_to_user,
	.to_sk_saddr   = sctp_v6_to_sk_saddr,
	.to_sk_daddr   = sctp_v6_to_sk_daddr,
	.copy_ip_options = sctp_v6_copy_ip_options,
	.af            = &sctp_af_inet6,
पूर्ण;

/* Initialize IPv6 support and रेजिस्टर with socket layer.  */
व्योम sctp_v6_pf_init(व्योम)
अणु
	/* Register the SCTP specअगरic PF_INET6 functions. */
	sctp_रेजिस्टर_pf(&sctp_pf_inet6, PF_INET6);

	/* Register the SCTP specअगरic AF_INET6 functions. */
	sctp_रेजिस्टर_af(&sctp_af_inet6);
पूर्ण

व्योम sctp_v6_pf_निकास(व्योम)
अणु
	list_del(&sctp_af_inet6.list);
पूर्ण

/* Initialize IPv6 support and रेजिस्टर with socket layer.  */
पूर्णांक sctp_v6_protosw_init(व्योम)
अणु
	पूर्णांक rc;

	rc = proto_रेजिस्टर(&sctpv6_prot, 1);
	अगर (rc)
		वापस rc;

	/* Add SCTPv6(UDP and TCP style) to inetsw6 linked list. */
	inet6_रेजिस्टर_protosw(&sctpv6_seqpacket_protosw);
	inet6_रेजिस्टर_protosw(&sctpv6_stream_protosw);

	वापस 0;
पूर्ण

व्योम sctp_v6_protosw_निकास(व्योम)
अणु
	inet6_unरेजिस्टर_protosw(&sctpv6_seqpacket_protosw);
	inet6_unरेजिस्टर_protosw(&sctpv6_stream_protosw);
	proto_unरेजिस्टर(&sctpv6_prot);
पूर्ण


/* Register with inet6 layer. */
पूर्णांक sctp_v6_add_protocol(व्योम)
अणु
	/* Register notअगरier क्रम inet6 address additions/deletions. */
	रेजिस्टर_inet6addr_notअगरier(&sctp_inet6addr_notअगरier);

	अगर (inet6_add_protocol(&sctpv6_protocol, IPPROTO_SCTP) < 0)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

/* Unरेजिस्टर with inet6 layer. */
व्योम sctp_v6_del_protocol(व्योम)
अणु
	inet6_del_protocol(&sctpv6_protocol, IPPROTO_SCTP);
	unरेजिस्टर_inet6addr_notअगरier(&sctp_inet6addr_notअगरier);
पूर्ण
