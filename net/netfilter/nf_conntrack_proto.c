<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/err.h>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_bridge.h>
#समावेश <net/netfilter/nf_log.h>

#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <linux/sysctl.h>
#समावेश <net/route.h>
#समावेश <net/ip.h>

#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/ipv4/nf_conntrack_ipv4.h>
#समावेश <net/netfilter/ipv6/nf_conntrack_ipv6.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <net/netfilter/ipv4/nf_defrag_ipv4.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>

#समावेश <linux/ipv6.h>
#समावेश <linux/in6.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet_frag.h>

बाह्य अचिन्हित पूर्णांक nf_conntrack_net_id;

अटल DEFINE_MUTEX(nf_ct_proto_mutex);

#अगर_घोषित CONFIG_SYSCTL
__म_लिखो(5, 6)
व्योम nf_l4proto_log_invalid(स्थिर काष्ठा sk_buff *skb,
			    काष्ठा net *net,
			    u16 pf, u8 protonum,
			    स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (net->ct.sysctl_log_invalid != protonum &&
	    net->ct.sysctl_log_invalid != IPPROTO_RAW)
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	nf_log_packet(net, pf, 0, skb, शून्य, शून्य, शून्य,
		      "nf_ct_proto_%d: %pV ", protonum, &vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(nf_l4proto_log_invalid);

__म_लिखो(3, 4)
व्योम nf_ct_l4proto_log_invalid(स्थिर काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_conn *ct,
			       स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	काष्ठा net *net;
	बहु_सूची args;

	net = nf_ct_net(ct);
	अगर (likely(net->ct.sysctl_log_invalid == 0))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	nf_l4proto_log_invalid(skb, net, nf_ct_l3num(ct),
			       nf_ct_protonum(ct), "%pV", &vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_l4proto_log_invalid);
#पूर्ण_अगर

स्थिर काष्ठा nf_conntrack_l4proto *nf_ct_l4proto_find(u8 l4proto)
अणु
	चयन (l4proto) अणु
	हाल IPPROTO_UDP: वापस &nf_conntrack_l4proto_udp;
	हाल IPPROTO_TCP: वापस &nf_conntrack_l4proto_tcp;
	हाल IPPROTO_ICMP: वापस &nf_conntrack_l4proto_icmp;
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	हाल IPPROTO_DCCP: वापस &nf_conntrack_l4proto_dccp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	हाल IPPROTO_SCTP: वापस &nf_conntrack_l4proto_sctp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_UDPLITE
	हाल IPPROTO_UDPLITE: वापस &nf_conntrack_l4proto_udplite;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	हाल IPPROTO_GRE: वापस &nf_conntrack_l4proto_gre;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPPROTO_ICMPV6: वापस &nf_conntrack_l4proto_icmpv6;
#पूर्ण_अगर /* CONFIG_IPV6 */
	पूर्ण

	वापस &nf_conntrack_l4proto_generic;
पूर्ण;
EXPORT_SYMBOL_GPL(nf_ct_l4proto_find);

अचिन्हित पूर्णांक nf_confirm(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	स्थिर काष्ठा nf_conn_help *help;

	help = nfct_help(ct);
	अगर (help) अणु
		स्थिर काष्ठा nf_conntrack_helper *helper;
		पूर्णांक ret;

		/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
		helper = rcu_dereference(help->helper);
		अगर (helper) अणु
			ret = helper->help(skb,
					   protoff,
					   ct, ctinfo);
			अगर (ret != NF_ACCEPT)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (test_bit(IPS_SEQ_ADJUST_BIT, &ct->status) &&
	    !nf_is_loopback_packet(skb)) अणु
		अगर (!nf_ct_seq_adjust(skb, ct, ctinfo, protoff)) अणु
			NF_CT_STAT_INC_ATOMIC(nf_ct_net(ct), drop);
			वापस NF_DROP;
		पूर्ण
	पूर्ण

	/* We've seen it coming out the other side: confirm it */
	वापस nf_conntrack_confirm(skb);
पूर्ण
EXPORT_SYMBOL_GPL(nf_confirm);

अटल अचिन्हित पूर्णांक ipv4_confirm(व्योम *priv,
				 काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nf_hook_state *state)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct || ctinfo == IP_CT_RELATED_REPLY)
		वापस nf_conntrack_confirm(skb);

	वापस nf_confirm(skb,
			  skb_network_offset(skb) + ip_hdrlen(skb),
			  ct, ctinfo);
पूर्ण

अटल अचिन्हित पूर्णांक ipv4_conntrack_in(व्योम *priv,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस nf_conntrack_in(skb, state);
पूर्ण

अटल अचिन्हित पूर्णांक ipv4_conntrack_local(व्योम *priv,
					 काष्ठा sk_buff *skb,
					 स्थिर काष्ठा nf_hook_state *state)
अणु
	अगर (ip_is_fragment(ip_hdr(skb))) अणु /* IP_NODEFRAG setsockopt set */
		क्रमागत ip_conntrack_info ctinfo;
		काष्ठा nf_conn *पंचांगpl;

		पंचांगpl = nf_ct_get(skb, &ctinfo);
		अगर (पंचांगpl && nf_ct_is_ढाँचा(पंचांगpl)) अणु
			/* when skipping ct, clear ढाँचाs to aव्योम fooling
			 * later tarमाला_लो/matches
			 */
			skb->_nfct = 0;
			nf_ct_put(पंचांगpl);
		पूर्ण
		वापस NF_ACCEPT;
	पूर्ण

	वापस nf_conntrack_in(skb, state);
पूर्ण

/* Connection tracking may drop packets, but never alters them, so
 * make it the first hook.
 */
अटल स्थिर काष्ठा nf_hook_ops ipv4_conntrack_ops[] = अणु
	अणु
		.hook		= ipv4_conntrack_in,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP_PRI_CONNTRACK,
	पूर्ण,
	अणु
		.hook		= ipv4_conntrack_local,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP_PRI_CONNTRACK,
	पूर्ण,
	अणु
		.hook		= ipv4_confirm,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP_PRI_CONNTRACK_CONFIRM,
	पूर्ण,
	अणु
		.hook		= ipv4_confirm,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_CONNTRACK_CONFIRM,
	पूर्ण,
पूर्ण;

/* Fast function क्रम those who करोn't want to parse /proc (and I don't
 * blame them).
 * Reversing the socket's dst/src poपूर्णांक of view gives us the reply
 * mapping.
 */
अटल पूर्णांक
getorigdst(काष्ठा sock *sk, पूर्णांक optval, व्योम __user *user, पूर्णांक *len)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conntrack_tuple tuple;

	स_रखो(&tuple, 0, माप(tuple));

	lock_sock(sk);
	tuple.src.u3.ip = inet->inet_rcv_saddr;
	tuple.src.u.tcp.port = inet->inet_sport;
	tuple.dst.u3.ip = inet->inet_daddr;
	tuple.dst.u.tcp.port = inet->inet_dport;
	tuple.src.l3num = PF_INET;
	tuple.dst.protonum = sk->sk_protocol;
	release_sock(sk);

	/* We only करो TCP and SCTP at the moment: is there a better way? */
	अगर (tuple.dst.protonum != IPPROTO_TCP &&
	    tuple.dst.protonum != IPPROTO_SCTP) अणु
		pr_debug("SO_ORIGINAL_DST: Not a TCP/SCTP socket\n");
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर ((अचिन्हित पूर्णांक)*len < माप(काष्ठा sockaddr_in)) अणु
		pr_debug("SO_ORIGINAL_DST: len %d not %zu\n",
			 *len, माप(काष्ठा sockaddr_in));
		वापस -EINVAL;
	पूर्ण

	h = nf_conntrack_find_get(sock_net(sk), &nf_ct_zone_dflt, &tuple);
	अगर (h) अणु
		काष्ठा sockaddr_in sin;
		काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

		sin.sin_family = AF_INET;
		sin.sin_port = ct->tuplehash[IP_CT_सूची_ORIGINAL]
			.tuple.dst.u.tcp.port;
		sin.sin_addr.s_addr = ct->tuplehash[IP_CT_सूची_ORIGINAL]
			.tuple.dst.u3.ip;
		स_रखो(sin.sin_zero, 0, माप(sin.sin_zero));

		pr_debug("SO_ORIGINAL_DST: %pI4 %u\n",
			 &sin.sin_addr.s_addr, ntohs(sin.sin_port));
		nf_ct_put(ct);
		अगर (copy_to_user(user, &sin, माप(sin)) != 0)
			वापस -EFAULT;
		अन्यथा
			वापस 0;
	पूर्ण
	pr_debug("SO_ORIGINAL_DST: Can't find %pI4/%u-%pI4/%u.\n",
		 &tuple.src.u3.ip, ntohs(tuple.src.u.tcp.port),
		 &tuple.dst.u3.ip, ntohs(tuple.dst.u.tcp.port));
	वापस -ENOENT;
पूर्ण

अटल काष्ठा nf_sockopt_ops so_getorigdst = अणु
	.pf		= PF_INET,
	.get_opपंचांगin	= SO_ORIGINAL_DST,
	.get_opपंचांगax	= SO_ORIGINAL_DST + 1,
	.get		= getorigdst,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक
ipv6_getorigdst(काष्ठा sock *sk, पूर्णांक optval, व्योम __user *user, पूर्णांक *len)
अणु
	काष्ठा nf_conntrack_tuple tuple = अणु .src.l3num = NFPROTO_IPV6 पूर्ण;
	स्थिर काष्ठा ipv6_pinfo *inet6 = inet6_sk(sk);
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा sockaddr_in6 sin6;
	काष्ठा nf_conn *ct;
	__be32 flow_label;
	पूर्णांक bound_dev_अगर;

	lock_sock(sk);
	tuple.src.u3.in6 = sk->sk_v6_rcv_saddr;
	tuple.src.u.tcp.port = inet->inet_sport;
	tuple.dst.u3.in6 = sk->sk_v6_daddr;
	tuple.dst.u.tcp.port = inet->inet_dport;
	tuple.dst.protonum = sk->sk_protocol;
	bound_dev_अगर = sk->sk_bound_dev_अगर;
	flow_label = inet6->flow_label;
	release_sock(sk);

	अगर (tuple.dst.protonum != IPPROTO_TCP &&
	    tuple.dst.protonum != IPPROTO_SCTP)
		वापस -ENOPROTOOPT;

	अगर (*len < 0 || (अचिन्हित पूर्णांक)*len < माप(sin6))
		वापस -EINVAL;

	h = nf_conntrack_find_get(sock_net(sk), &nf_ct_zone_dflt, &tuple);
	अगर (!h) अणु
		pr_debug("IP6T_SO_ORIGINAL_DST: Can't find %pI6c/%u-%pI6c/%u.\n",
			 &tuple.src.u3.ip6, ntohs(tuple.src.u.tcp.port),
			 &tuple.dst.u3.ip6, ntohs(tuple.dst.u.tcp.port));
		वापस -ENOENT;
	पूर्ण

	ct = nf_ct_tuplehash_to_ctrack(h);

	sin6.sin6_family = AF_INET6;
	sin6.sin6_port = ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.u.tcp.port;
	sin6.sin6_flowinfo = flow_label & IPV6_FLOWINFO_MASK;
	स_नकल(&sin6.sin6_addr,
	       &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.u3.in6,
	       माप(sin6.sin6_addr));

	nf_ct_put(ct);
	sin6.sin6_scope_id = ipv6_अगरace_scope_id(&sin6.sin6_addr, bound_dev_अगर);
	वापस copy_to_user(user, &sin6, माप(sin6)) ? -EFAULT : 0;
पूर्ण

अटल काष्ठा nf_sockopt_ops so_getorigdst6 = अणु
	.pf		= NFPROTO_IPV6,
	.get_opपंचांगin	= IP6T_SO_ORIGINAL_DST,
	.get_opपंचांगax	= IP6T_SO_ORIGINAL_DST + 1,
	.get		= ipv6_getorigdst,
	.owner		= THIS_MODULE,
पूर्ण;

अटल अचिन्हित पूर्णांक ipv6_confirm(व्योम *priv,
				 काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	अचिन्हित अक्षर pnum = ipv6_hdr(skb)->nexthdr;
	__be16 frag_off;
	पूर्णांक protoff;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct || ctinfo == IP_CT_RELATED_REPLY)
		वापस nf_conntrack_confirm(skb);

	protoff = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &pnum,
				   &frag_off);
	अगर (protoff < 0 || (frag_off & htons(~0x7)) != 0) अणु
		pr_debug("proto header not found\n");
		वापस nf_conntrack_confirm(skb);
	पूर्ण

	वापस nf_confirm(skb, protoff, ct, ctinfo);
पूर्ण

अटल अचिन्हित पूर्णांक ipv6_conntrack_in(व्योम *priv,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस nf_conntrack_in(skb, state);
पूर्ण

अटल अचिन्हित पूर्णांक ipv6_conntrack_local(व्योम *priv,
					 काष्ठा sk_buff *skb,
					 स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस nf_conntrack_in(skb, state);
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ipv6_conntrack_ops[] = अणु
	अणु
		.hook		= ipv6_conntrack_in,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP6_PRI_CONNTRACK,
	पूर्ण,
	अणु
		.hook		= ipv6_conntrack_local,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP6_PRI_CONNTRACK,
	पूर्ण,
	अणु
		.hook		= ipv6_confirm,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP6_PRI_LAST,
	पूर्ण,
	अणु
		.hook		= ipv6_confirm,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP6_PRI_LAST - 1,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक nf_ct_tcp_fixup(काष्ठा nf_conn *ct, व्योम *_nfproto)
अणु
	u8 nfproto = (अचिन्हित दीर्घ)_nfproto;

	अगर (nf_ct_l3num(ct) != nfproto)
		वापस 0;

	अगर (nf_ct_protonum(ct) == IPPROTO_TCP &&
	    ct->proto.tcp.state == TCP_CONNTRACK_ESTABLISHED) अणु
		ct->proto.tcp.seen[0].td_maxwin = 0;
		ct->proto.tcp.seen[1].td_maxwin = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nf_ct_bridge_info *nf_ct_bridge_info;

अटल पूर्णांक nf_ct_netns_करो_get(काष्ठा net *net, u8 nfproto)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	bool fixup_needed = false, retry = true;
	पूर्णांक err = 0;
retry:
	mutex_lock(&nf_ct_proto_mutex);

	चयन (nfproto) अणु
	हाल NFPROTO_IPV4:
		cnet->users4++;
		अगर (cnet->users4 > 1)
			जाओ out_unlock;
		err = nf_defrag_ipv4_enable(net);
		अगर (err) अणु
			cnet->users4 = 0;
			जाओ out_unlock;
		पूर्ण

		err = nf_रेजिस्टर_net_hooks(net, ipv4_conntrack_ops,
					    ARRAY_SIZE(ipv4_conntrack_ops));
		अगर (err)
			cnet->users4 = 0;
		अन्यथा
			fixup_needed = true;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल NFPROTO_IPV6:
		cnet->users6++;
		अगर (cnet->users6 > 1)
			जाओ out_unlock;
		err = nf_defrag_ipv6_enable(net);
		अगर (err < 0) अणु
			cnet->users6 = 0;
			जाओ out_unlock;
		पूर्ण

		err = nf_रेजिस्टर_net_hooks(net, ipv6_conntrack_ops,
					    ARRAY_SIZE(ipv6_conntrack_ops));
		अगर (err)
			cnet->users6 = 0;
		अन्यथा
			fixup_needed = true;
		अवरोध;
#पूर्ण_अगर
	हाल NFPROTO_BRIDGE:
		अगर (!nf_ct_bridge_info) अणु
			अगर (!retry) अणु
				err = -EPROTO;
				जाओ out_unlock;
			पूर्ण
			mutex_unlock(&nf_ct_proto_mutex);
			request_module("nf_conntrack_bridge");
			retry = false;
			जाओ retry;
		पूर्ण
		अगर (!try_module_get(nf_ct_bridge_info->me)) अणु
			err = -EPROTO;
			जाओ out_unlock;
		पूर्ण
		cnet->users_bridge++;
		अगर (cnet->users_bridge > 1)
			जाओ out_unlock;

		err = nf_रेजिस्टर_net_hooks(net, nf_ct_bridge_info->ops,
					    nf_ct_bridge_info->ops_size);
		अगर (err)
			cnet->users_bridge = 0;
		अन्यथा
			fixup_needed = true;
		अवरोध;
	शेष:
		err = -EPROTO;
		अवरोध;
	पूर्ण
 out_unlock:
	mutex_unlock(&nf_ct_proto_mutex);

	अगर (fixup_needed)
		nf_ct_iterate_cleanup_net(net, nf_ct_tcp_fixup,
					  (व्योम *)(अचिन्हित दीर्घ)nfproto, 0, 0);

	वापस err;
पूर्ण

अटल व्योम nf_ct_netns_करो_put(काष्ठा net *net, u8 nfproto)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

	mutex_lock(&nf_ct_proto_mutex);
	चयन (nfproto) अणु
	हाल NFPROTO_IPV4:
		अगर (cnet->users4 && (--cnet->users4 == 0)) अणु
			nf_unरेजिस्टर_net_hooks(net, ipv4_conntrack_ops,
						ARRAY_SIZE(ipv4_conntrack_ops));
			nf_defrag_ipv4_disable(net);
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल NFPROTO_IPV6:
		अगर (cnet->users6 && (--cnet->users6 == 0)) अणु
			nf_unरेजिस्टर_net_hooks(net, ipv6_conntrack_ops,
						ARRAY_SIZE(ipv6_conntrack_ops));
			nf_defrag_ipv6_disable(net);
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	हाल NFPROTO_BRIDGE:
		अगर (!nf_ct_bridge_info)
			अवरोध;
		अगर (cnet->users_bridge && (--cnet->users_bridge == 0))
			nf_unरेजिस्टर_net_hooks(net, nf_ct_bridge_info->ops,
						nf_ct_bridge_info->ops_size);

		module_put(nf_ct_bridge_info->me);
		अवरोध;
	पूर्ण
	mutex_unlock(&nf_ct_proto_mutex);
पूर्ण

अटल पूर्णांक nf_ct_netns_inet_get(काष्ठा net *net)
अणु
	पूर्णांक err;

	err = nf_ct_netns_करो_get(net, NFPROTO_IPV4);
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (err < 0)
		जाओ err1;
	err = nf_ct_netns_करो_get(net, NFPROTO_IPV6);
	अगर (err < 0)
		जाओ err2;

	वापस err;
err2:
	nf_ct_netns_put(net, NFPROTO_IPV4);
err1:
#पूर्ण_अगर
	वापस err;
पूर्ण

पूर्णांक nf_ct_netns_get(काष्ठा net *net, u8 nfproto)
अणु
	पूर्णांक err;

	चयन (nfproto) अणु
	हाल NFPROTO_INET:
		err = nf_ct_netns_inet_get(net);
		अवरोध;
	हाल NFPROTO_BRIDGE:
		err = nf_ct_netns_करो_get(net, NFPROTO_BRIDGE);
		अगर (err < 0)
			वापस err;

		err = nf_ct_netns_inet_get(net);
		अगर (err < 0) अणु
			nf_ct_netns_put(net, NFPROTO_BRIDGE);
			वापस err;
		पूर्ण
		अवरोध;
	शेष:
		err = nf_ct_netns_करो_get(net, nfproto);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_netns_get);

व्योम nf_ct_netns_put(काष्ठा net *net, uपूर्णांक8_t nfproto)
अणु
	चयन (nfproto) अणु
	हाल NFPROTO_BRIDGE:
		nf_ct_netns_करो_put(net, NFPROTO_BRIDGE);
		fallthrough;
	हाल NFPROTO_INET:
		nf_ct_netns_करो_put(net, NFPROTO_IPV4);
		nf_ct_netns_करो_put(net, NFPROTO_IPV6);
		अवरोध;
	शेष:
		nf_ct_netns_करो_put(net, nfproto);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_netns_put);

व्योम nf_ct_bridge_रेजिस्टर(काष्ठा nf_ct_bridge_info *info)
अणु
	WARN_ON(nf_ct_bridge_info);
	mutex_lock(&nf_ct_proto_mutex);
	nf_ct_bridge_info = info;
	mutex_unlock(&nf_ct_proto_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_bridge_रेजिस्टर);

व्योम nf_ct_bridge_unरेजिस्टर(काष्ठा nf_ct_bridge_info *info)
अणु
	WARN_ON(!nf_ct_bridge_info);
	mutex_lock(&nf_ct_proto_mutex);
	nf_ct_bridge_info = शून्य;
	mutex_unlock(&nf_ct_proto_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_bridge_unरेजिस्टर);

पूर्णांक nf_conntrack_proto_init(व्योम)
अणु
	पूर्णांक ret;

	ret = nf_रेजिस्टर_sockopt(&so_getorigdst);
	अगर (ret < 0)
		वापस ret;

#अगर IS_ENABLED(CONFIG_IPV6)
	ret = nf_रेजिस्टर_sockopt(&so_getorigdst6);
	अगर (ret < 0)
		जाओ cleanup_sockopt;
#पूर्ण_अगर

	वापस ret;

#अगर IS_ENABLED(CONFIG_IPV6)
cleanup_sockopt:
	nf_unरेजिस्टर_sockopt(&so_getorigdst);
#पूर्ण_अगर
	वापस ret;
पूर्ण

व्योम nf_conntrack_proto_fini(व्योम)
अणु
	nf_unरेजिस्टर_sockopt(&so_getorigdst);
#अगर IS_ENABLED(CONFIG_IPV6)
	nf_unरेजिस्टर_sockopt(&so_getorigdst6);
#पूर्ण_अगर
पूर्ण

व्योम nf_conntrack_proto_pernet_init(काष्ठा net *net)
अणु
	nf_conntrack_generic_init_net(net);
	nf_conntrack_udp_init_net(net);
	nf_conntrack_tcp_init_net(net);
	nf_conntrack_icmp_init_net(net);
#अगर IS_ENABLED(CONFIG_IPV6)
	nf_conntrack_icmpv6_init_net(net);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	nf_conntrack_dccp_init_net(net);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	nf_conntrack_sctp_init_net(net);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	nf_conntrack_gre_init_net(net);
#पूर्ण_अगर
पूर्ण

व्योम nf_conntrack_proto_pernet_fini(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	nf_ct_gre_keymap_flush(net);
#पूर्ण_अगर
पूर्ण

module_param_call(hashsize, nf_conntrack_set_hashsize, param_get_uपूर्णांक,
		  &nf_conntrack_htable_size, 0600);

MODULE_ALIAS("ip_conntrack");
MODULE_ALIAS("nf_conntrack-" __stringअगरy(AF_INET));
MODULE_ALIAS("nf_conntrack-" __stringअगरy(AF_INET6));
MODULE_LICENSE("GPL");
