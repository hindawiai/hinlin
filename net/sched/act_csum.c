<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Checksum updating actions
 *
 * Copyright (c) 2010 Gregoire Baron <baronchon@n7mm.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/netlink.h>
#समावेश <net/netlink.h>
#समावेश <linux/rtnetlink.h>

#समावेश <linux/skbuff.h>

#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/igmp.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/sctp/checksum.h>

#समावेश <net/act_api.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/tc_act/tc_csum.h>
#समावेश <net/tc_act/tc_csum.h>

अटल स्थिर काष्ठा nla_policy csum_policy[TCA_CSUM_MAX + 1] = अणु
	[TCA_CSUM_PARMS] = अणु .len = माप(काष्ठा tc_csum), पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक csum_net_id;
अटल काष्ठा tc_action_ops act_csum_ops;

अटल पूर्णांक tcf_csum_init(काष्ठा net *net, काष्ठा nlattr *nla,
			 काष्ठा nlattr *est, काष्ठा tc_action **a, पूर्णांक ovr,
			 पूर्णांक bind, bool rtnl_held, काष्ठा tcf_proto *tp,
			 u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, csum_net_id);
	काष्ठा tcf_csum_params *params_new;
	काष्ठा nlattr *tb[TCA_CSUM_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_csum *parm;
	काष्ठा tcf_csum *p;
	पूर्णांक ret = 0, err;
	u32 index;

	अगर (nla == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_CSUM_MAX, nla, csum_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_CSUM_PARMS] == शून्य)
		वापस -EINVAL;
	parm = nla_data(tb[TCA_CSUM_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (!err) अणु
		ret = tcf_idr_create_from_flags(tn, index, est, a,
						&act_csum_ops, bind, flags);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (err > 0) अणु
		अगर (bind)/* करोnt override शेषs */
			वापस 0;
		अगर (!ovr) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस err;
	पूर्ण

	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	p = to_tcf_csum(*a);

	params_new = kzalloc(माप(*params_new), GFP_KERNEL);
	अगर (unlikely(!params_new)) अणु
		err = -ENOMEM;
		जाओ put_chain;
	पूर्ण
	params_new->update_flags = parm->update_flags;

	spin_lock_bh(&p->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	params_new = rcu_replace_poपूर्णांकer(p->params, params_new,
					 lockdep_is_held(&p->tcf_lock));
	spin_unlock_bh(&p->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	अगर (params_new)
		kमुक्त_rcu(params_new, rcu);

	वापस ret;
put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

/**
 * tcf_csum_skb_nextlayer - Get next layer poपूर्णांकer
 * @skb: sk_buff to use
 * @ihl: previous summed headers length
 * @ipl: complete packet length
 * @jhl: next header length
 *
 * Check the expected next layer availability in the specअगरied sk_buff.
 * Return the next layer poपूर्णांकer अगर pass, शून्य otherwise.
 */
अटल व्योम *tcf_csum_skb_nextlayer(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक ihl, अचिन्हित पूर्णांक ipl,
				    अचिन्हित पूर्णांक jhl)
अणु
	पूर्णांक ntkoff = skb_network_offset(skb);
	पूर्णांक hl = ihl + jhl;

	अगर (!pskb_may_pull(skb, ipl + ntkoff) || (ipl < hl) ||
	    skb_try_make_writable(skb, hl + ntkoff))
		वापस शून्य;
	अन्यथा
		वापस (व्योम *)(skb_network_header(skb) + ihl);
पूर्ण

अटल पूर्णांक tcf_csum_ipv4_icmp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ihl,
			      अचिन्हित पूर्णांक ipl)
अणु
	काष्ठा icmphdr *icmph;

	icmph = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*icmph));
	अगर (icmph == शून्य)
		वापस 0;

	icmph->checksum = 0;
	skb->csum = csum_partial(icmph, ipl - ihl, 0);
	icmph->checksum = csum_fold(skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv4_igmp(काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक ihl, अचिन्हित पूर्णांक ipl)
अणु
	काष्ठा igmphdr *igmph;

	igmph = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*igmph));
	अगर (igmph == शून्य)
		वापस 0;

	igmph->csum = 0;
	skb->csum = csum_partial(igmph, ipl - ihl, 0);
	igmph->csum = csum_fold(skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv6_icmp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ihl,
			      अचिन्हित पूर्णांक ipl)
अणु
	काष्ठा icmp6hdr *icmp6h;
	स्थिर काष्ठा ipv6hdr *ip6h;

	icmp6h = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*icmp6h));
	अगर (icmp6h == शून्य)
		वापस 0;

	ip6h = ipv6_hdr(skb);
	icmp6h->icmp6_cksum = 0;
	skb->csum = csum_partial(icmp6h, ipl - ihl, 0);
	icmp6h->icmp6_cksum = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
					      ipl - ihl, IPPROTO_ICMPV6,
					      skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv4_tcp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ihl,
			     अचिन्हित पूर्णांक ipl)
अणु
	काष्ठा tcphdr *tcph;
	स्थिर काष्ठा iphdr *iph;

	अगर (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4)
		वापस 1;

	tcph = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*tcph));
	अगर (tcph == शून्य)
		वापस 0;

	iph = ip_hdr(skb);
	tcph->check = 0;
	skb->csum = csum_partial(tcph, ipl - ihl, 0);
	tcph->check = tcp_v4_check(ipl - ihl,
				   iph->saddr, iph->daddr, skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv6_tcp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ihl,
			     अचिन्हित पूर्णांक ipl)
अणु
	काष्ठा tcphdr *tcph;
	स्थिर काष्ठा ipv6hdr *ip6h;

	अगर (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6)
		वापस 1;

	tcph = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*tcph));
	अगर (tcph == शून्य)
		वापस 0;

	ip6h = ipv6_hdr(skb);
	tcph->check = 0;
	skb->csum = csum_partial(tcph, ipl - ihl, 0);
	tcph->check = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
				      ipl - ihl, IPPROTO_TCP,
				      skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv4_udp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ihl,
			     अचिन्हित पूर्णांक ipl, पूर्णांक udplite)
अणु
	काष्ठा udphdr *udph;
	स्थिर काष्ठा iphdr *iph;
	u16 ul;

	अगर (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
		वापस 1;

	/*
	 * Support both UDP and UDPLITE checksum algorithms, Don't use
	 * udph->len to get the real length without any protocol check,
	 * UDPLITE uses udph->len क्रम another thing,
	 * Use iph->tot_len, or just ipl.
	 */

	udph = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*udph));
	अगर (udph == शून्य)
		वापस 0;

	iph = ip_hdr(skb);
	ul = ntohs(udph->len);

	अगर (udplite || udph->check) अणु

		udph->check = 0;

		अगर (udplite) अणु
			अगर (ul == 0)
				skb->csum = csum_partial(udph, ipl - ihl, 0);
			अन्यथा अगर ((ul >= माप(*udph)) && (ul <= ipl - ihl))
				skb->csum = csum_partial(udph, ul, 0);
			अन्यथा
				जाओ ignore_obscure_skb;
		पूर्ण अन्यथा अणु
			अगर (ul != ipl - ihl)
				जाओ ignore_obscure_skb;

			skb->csum = csum_partial(udph, ul, 0);
		पूर्ण

		udph->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						ul, iph->protocol,
						skb->csum);

		अगर (!udph->check)
			udph->check = CSUM_MANGLED_0;
	पूर्ण

	skb->ip_summed = CHECKSUM_NONE;

ignore_obscure_skb:
	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv6_udp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ihl,
			     अचिन्हित पूर्णांक ipl, पूर्णांक udplite)
अणु
	काष्ठा udphdr *udph;
	स्थिर काष्ठा ipv6hdr *ip6h;
	u16 ul;

	अगर (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
		वापस 1;

	/*
	 * Support both UDP and UDPLITE checksum algorithms, Don't use
	 * udph->len to get the real length without any protocol check,
	 * UDPLITE uses udph->len क्रम another thing,
	 * Use ip6h->payload_len + माप(*ip6h) ... , or just ipl.
	 */

	udph = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*udph));
	अगर (udph == शून्य)
		वापस 0;

	ip6h = ipv6_hdr(skb);
	ul = ntohs(udph->len);

	udph->check = 0;

	अगर (udplite) अणु
		अगर (ul == 0)
			skb->csum = csum_partial(udph, ipl - ihl, 0);

		अन्यथा अगर ((ul >= माप(*udph)) && (ul <= ipl - ihl))
			skb->csum = csum_partial(udph, ul, 0);

		अन्यथा
			जाओ ignore_obscure_skb;
	पूर्ण अन्यथा अणु
		अगर (ul != ipl - ihl)
			जाओ ignore_obscure_skb;

		skb->csum = csum_partial(udph, ul, 0);
	पूर्ण

	udph->check = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr, ul,
				      udplite ? IPPROTO_UDPLITE : IPPROTO_UDP,
				      skb->csum);

	अगर (!udph->check)
		udph->check = CSUM_MANGLED_0;

	skb->ip_summed = CHECKSUM_NONE;

ignore_obscure_skb:
	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_sctp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ihl,
			 अचिन्हित पूर्णांक ipl)
अणु
	काष्ठा sctphdr *sctph;

	अगर (skb_is_gso(skb) && skb_is_gso_sctp(skb))
		वापस 1;

	sctph = tcf_csum_skb_nextlayer(skb, ihl, ipl, माप(*sctph));
	अगर (!sctph)
		वापस 0;

	sctph->checksum = sctp_compute_cksum(skb,
					     skb_network_offset(skb) + ihl);
	skb->ip_summed = CHECKSUM_NONE;
	skb->csum_not_inet = 0;

	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv4(काष्ठा sk_buff *skb, u32 update_flags)
अणु
	स्थिर काष्ठा iphdr *iph;
	पूर्णांक ntkoff;

	ntkoff = skb_network_offset(skb);

	अगर (!pskb_may_pull(skb, माप(*iph) + ntkoff))
		जाओ fail;

	iph = ip_hdr(skb);

	चयन (iph->frag_off & htons(IP_OFFSET) ? 0 : iph->protocol) अणु
	हाल IPPROTO_ICMP:
		अगर (update_flags & TCA_CSUM_UPDATE_FLAG_ICMP)
			अगर (!tcf_csum_ipv4_icmp(skb, iph->ihl * 4,
						ntohs(iph->tot_len)))
				जाओ fail;
		अवरोध;
	हाल IPPROTO_IGMP:
		अगर (update_flags & TCA_CSUM_UPDATE_FLAG_IGMP)
			अगर (!tcf_csum_ipv4_igmp(skb, iph->ihl * 4,
						ntohs(iph->tot_len)))
				जाओ fail;
		अवरोध;
	हाल IPPROTO_TCP:
		अगर (update_flags & TCA_CSUM_UPDATE_FLAG_TCP)
			अगर (!tcf_csum_ipv4_tcp(skb, iph->ihl * 4,
					       ntohs(iph->tot_len)))
				जाओ fail;
		अवरोध;
	हाल IPPROTO_UDP:
		अगर (update_flags & TCA_CSUM_UPDATE_FLAG_UDP)
			अगर (!tcf_csum_ipv4_udp(skb, iph->ihl * 4,
					       ntohs(iph->tot_len), 0))
				जाओ fail;
		अवरोध;
	हाल IPPROTO_UDPLITE:
		अगर (update_flags & TCA_CSUM_UPDATE_FLAG_UDPLITE)
			अगर (!tcf_csum_ipv4_udp(skb, iph->ihl * 4,
					       ntohs(iph->tot_len), 1))
				जाओ fail;
		अवरोध;
	हाल IPPROTO_SCTP:
		अगर ((update_flags & TCA_CSUM_UPDATE_FLAG_SCTP) &&
		    !tcf_csum_sctp(skb, iph->ihl * 4, ntohs(iph->tot_len)))
			जाओ fail;
		अवरोध;
	पूर्ण

	अगर (update_flags & TCA_CSUM_UPDATE_FLAG_IPV4HDR) अणु
		अगर (skb_try_make_writable(skb, माप(*iph) + ntkoff))
			जाओ fail;

		ip_send_check(ip_hdr(skb));
	पूर्ण

	वापस 1;

fail:
	वापस 0;
पूर्ण

अटल पूर्णांक tcf_csum_ipv6_hopopts(काष्ठा ipv6_opt_hdr *ip6xh, अचिन्हित पूर्णांक ixhl,
				 अचिन्हित पूर्णांक *pl)
अणु
	पूर्णांक off, len, optlen;
	अचिन्हित अक्षर *xh = (व्योम *)ip6xh;

	off = माप(*ip6xh);
	len = ixhl - off;

	जबतक (len > 1) अणु
		चयन (xh[off]) अणु
		हाल IPV6_TLV_PAD1:
			optlen = 1;
			अवरोध;
		हाल IPV6_TLV_JUMBO:
			optlen = xh[off + 1] + 2;
			अगर (optlen != 6 || len < 6 || (off & 3) != 2)
				/* wrong jumbo option length/alignment */
				वापस 0;
			*pl = ntohl(*(__be32 *)(xh + off + 2));
			जाओ करोne;
		शेष:
			optlen = xh[off + 1] + 2;
			अगर (optlen > len)
				/* ignore obscure options */
				जाओ करोne;
			अवरोध;
		पूर्ण
		off += optlen;
		len -= optlen;
	पूर्ण

करोne:
	वापस 1;
पूर्ण

अटल पूर्णांक tcf_csum_ipv6(काष्ठा sk_buff *skb, u32 update_flags)
अणु
	काष्ठा ipv6hdr *ip6h;
	काष्ठा ipv6_opt_hdr *ip6xh;
	अचिन्हित पूर्णांक hl, ixhl;
	अचिन्हित पूर्णांक pl;
	पूर्णांक ntkoff;
	u8 nexthdr;

	ntkoff = skb_network_offset(skb);

	hl = माप(*ip6h);

	अगर (!pskb_may_pull(skb, hl + ntkoff))
		जाओ fail;

	ip6h = ipv6_hdr(skb);

	pl = ntohs(ip6h->payload_len);
	nexthdr = ip6h->nexthdr;

	करो अणु
		चयन (nexthdr) अणु
		हाल NEXTHDR_FRAGMENT:
			जाओ ignore_skb;
		हाल NEXTHDR_ROUTING:
		हाल NEXTHDR_HOP:
		हाल NEXTHDR_DEST:
			अगर (!pskb_may_pull(skb, hl + माप(*ip6xh) + ntkoff))
				जाओ fail;
			ip6xh = (व्योम *)(skb_network_header(skb) + hl);
			ixhl = ipv6_optlen(ip6xh);
			अगर (!pskb_may_pull(skb, hl + ixhl + ntkoff))
				जाओ fail;
			ip6xh = (व्योम *)(skb_network_header(skb) + hl);
			अगर ((nexthdr == NEXTHDR_HOP) &&
			    !(tcf_csum_ipv6_hopopts(ip6xh, ixhl, &pl)))
				जाओ fail;
			nexthdr = ip6xh->nexthdr;
			hl += ixhl;
			अवरोध;
		हाल IPPROTO_ICMPV6:
			अगर (update_flags & TCA_CSUM_UPDATE_FLAG_ICMP)
				अगर (!tcf_csum_ipv6_icmp(skb,
							hl, pl + माप(*ip6h)))
					जाओ fail;
			जाओ करोne;
		हाल IPPROTO_TCP:
			अगर (update_flags & TCA_CSUM_UPDATE_FLAG_TCP)
				अगर (!tcf_csum_ipv6_tcp(skb,
						       hl, pl + माप(*ip6h)))
					जाओ fail;
			जाओ करोne;
		हाल IPPROTO_UDP:
			अगर (update_flags & TCA_CSUM_UPDATE_FLAG_UDP)
				अगर (!tcf_csum_ipv6_udp(skb, hl,
						       pl + माप(*ip6h), 0))
					जाओ fail;
			जाओ करोne;
		हाल IPPROTO_UDPLITE:
			अगर (update_flags & TCA_CSUM_UPDATE_FLAG_UDPLITE)
				अगर (!tcf_csum_ipv6_udp(skb, hl,
						       pl + माप(*ip6h), 1))
					जाओ fail;
			जाओ करोne;
		हाल IPPROTO_SCTP:
			अगर ((update_flags & TCA_CSUM_UPDATE_FLAG_SCTP) &&
			    !tcf_csum_sctp(skb, hl, pl + माप(*ip6h)))
				जाओ fail;
			जाओ करोne;
		शेष:
			जाओ ignore_skb;
		पूर्ण
	पूर्ण जबतक (pskb_may_pull(skb, hl + 1 + ntkoff));

करोne:
ignore_skb:
	वापस 1;

fail:
	वापस 0;
पूर्ण

अटल पूर्णांक tcf_csum_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_csum *p = to_tcf_csum(a);
	bool orig_vlan_tag_present = false;
	अचिन्हित पूर्णांक vlan_hdr_count = 0;
	काष्ठा tcf_csum_params *params;
	u32 update_flags;
	__be16 protocol;
	पूर्णांक action;

	params = rcu_dereference_bh(p->params);

	tcf_lastuse_update(&p->tcf_पंचांग);
	tcf_action_update_bstats(&p->common, skb);

	action = READ_ONCE(p->tcf_action);
	अगर (unlikely(action == TC_ACT_SHOT))
		जाओ drop;

	update_flags = params->update_flags;
	protocol = skb_protocol(skb, false);
again:
	चयन (protocol) अणु
	हाल cpu_to_be16(ETH_P_IP):
		अगर (!tcf_csum_ipv4(skb, update_flags))
			जाओ drop;
		अवरोध;
	हाल cpu_to_be16(ETH_P_IPV6):
		अगर (!tcf_csum_ipv6(skb, update_flags))
			जाओ drop;
		अवरोध;
	हाल cpu_to_be16(ETH_P_8021AD):
		fallthrough;
	हाल cpu_to_be16(ETH_P_8021Q):
		अगर (skb_vlan_tag_present(skb) && !orig_vlan_tag_present) अणु
			protocol = skb->protocol;
			orig_vlan_tag_present = true;
		पूर्ण अन्यथा अणु
			काष्ठा vlan_hdr *vlan = (काष्ठा vlan_hdr *)skb->data;

			protocol = vlan->h_vlan_encapsulated_proto;
			skb_pull(skb, VLAN_HLEN);
			skb_reset_network_header(skb);
			vlan_hdr_count++;
		पूर्ण
		जाओ again;
	पूर्ण

out:
	/* Restore the skb क्रम the pulled VLAN tags */
	जबतक (vlan_hdr_count--) अणु
		skb_push(skb, VLAN_HLEN);
		skb_reset_network_header(skb);
	पूर्ण

	वापस action;

drop:
	tcf_action_inc_drop_qstats(&p->common);
	action = TC_ACT_SHOT;
	जाओ out;
पूर्ण

अटल पूर्णांक tcf_csum_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक bind,
			 पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_csum *p = to_tcf_csum(a);
	काष्ठा tcf_csum_params *params;
	काष्ठा tc_csum opt = अणु
		.index   = p->tcf_index,
		.refcnt  = refcount_पढ़ो(&p->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&p->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&p->tcf_lock);
	params = rcu_dereference_रक्षित(p->params,
					   lockdep_is_held(&p->tcf_lock));
	opt.action = p->tcf_action;
	opt.update_flags = params->update_flags;

	अगर (nla_put(skb, TCA_CSUM_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &p->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_CSUM_TM, माप(t), &t, TCA_CSUM_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&p->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&p->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल व्योम tcf_csum_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_csum *p = to_tcf_csum(a);
	काष्ठा tcf_csum_params *params;

	params = rcu_dereference_रक्षित(p->params, 1);
	अगर (params)
		kमुक्त_rcu(params, rcu);
पूर्ण

अटल पूर्णांक tcf_csum_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb, पूर्णांक type,
			   स्थिर काष्ठा tc_action_ops *ops,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, csum_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_csum_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, csum_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल माप_प्रकार tcf_csum_get_fill_size(स्थिर काष्ठा tc_action *act)
अणु
	वापस nla_total_size(माप(काष्ठा tc_csum));
पूर्ण

अटल काष्ठा tc_action_ops act_csum_ops = अणु
	.kind		= "csum",
	.id		= TCA_ID_CSUM,
	.owner		= THIS_MODULE,
	.act		= tcf_csum_act,
	.dump		= tcf_csum_dump,
	.init		= tcf_csum_init,
	.cleanup	= tcf_csum_cleanup,
	.walk		= tcf_csum_walker,
	.lookup		= tcf_csum_search,
	.get_fill_size  = tcf_csum_get_fill_size,
	.size		= माप(काष्ठा tcf_csum),
पूर्ण;

अटल __net_init पूर्णांक csum_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, csum_net_id);

	वापस tc_action_net_init(net, tn, &act_csum_ops);
पूर्ण

अटल व्योम __net_निकास csum_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, csum_net_id);
पूर्ण

अटल काष्ठा pernet_operations csum_net_ops = अणु
	.init = csum_init_net,
	.निकास_batch = csum_निकास_net,
	.id   = &csum_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_DESCRIPTION("Checksum updating actions");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init csum_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_csum_ops, &csum_net_ops);
पूर्ण

अटल व्योम __निकास csum_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_csum_ops, &csum_net_ops);
पूर्ण

module_init(csum_init_module);
module_निकास(csum_cleanup_module);
