<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C)2003,2004 USAGI/WIDE Project
 *
 * Author:
 *	Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 */

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/in6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_log.h>

#समावेश "nf_internals.h"

अटल स्थिर अचिन्हित पूर्णांक nf_ct_icmpv6_समयout = 30*HZ;

bool icmpv6_pkt_to_tuple(स्थिर काष्ठा sk_buff *skb,
			 अचिन्हित पूर्णांक dataoff,
			 काष्ठा net *net,
			 काष्ठा nf_conntrack_tuple *tuple)
अणु
	स्थिर काष्ठा icmp6hdr *hp;
	काष्ठा icmp6hdr _hdr;

	hp = skb_header_poपूर्णांकer(skb, dataoff, माप(_hdr), &_hdr);
	अगर (hp == शून्य)
		वापस false;
	tuple->dst.u.icmp.type = hp->icmp6_type;
	tuple->src.u.icmp.id = hp->icmp6_identअगरier;
	tuple->dst.u.icmp.code = hp->icmp6_code;

	वापस true;
पूर्ण

/* Add 1; spaces filled with 0. */
अटल स्थिर u_पूर्णांक8_t invmap[] = अणु
	[ICMPV6_ECHO_REQUEST - 128]	= ICMPV6_ECHO_REPLY + 1,
	[ICMPV6_ECHO_REPLY - 128]	= ICMPV6_ECHO_REQUEST + 1,
	[ICMPV6_NI_QUERY - 128]		= ICMPV6_NI_REPLY + 1,
	[ICMPV6_NI_REPLY - 128]		= ICMPV6_NI_QUERY + 1
पूर्ण;

अटल स्थिर u_पूर्णांक8_t noct_valid_new[] = अणु
	[ICMPV6_MGM_QUERY - 130] = 1,
	[ICMPV6_MGM_REPORT - 130] = 1,
	[ICMPV6_MGM_REDUCTION - 130] = 1,
	[NDISC_ROUTER_SOLICITATION - 130] = 1,
	[NDISC_ROUTER_ADVERTISEMENT - 130] = 1,
	[NDISC_NEIGHBOUR_SOLICITATION - 130] = 1,
	[NDISC_NEIGHBOUR_ADVERTISEMENT - 130] = 1,
	[ICMPV6_MLD2_REPORT - 130] = 1
पूर्ण;

bool nf_conntrack_invert_icmpv6_tuple(काष्ठा nf_conntrack_tuple *tuple,
				      स्थिर काष्ठा nf_conntrack_tuple *orig)
अणु
	पूर्णांक type = orig->dst.u.icmp.type - 128;
	अगर (type < 0 || type >= माप(invmap) || !invmap[type])
		वापस false;

	tuple->src.u.icmp.id   = orig->src.u.icmp.id;
	tuple->dst.u.icmp.type = invmap[type] - 1;
	tuple->dst.u.icmp.code = orig->dst.u.icmp.code;
	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक *icmpv6_get_समयouts(काष्ठा net *net)
अणु
	वापस &nf_icmpv6_pernet(net)->समयout;
पूर्ण

/* Returns verdict क्रम packet, or -1 क्रम invalid. */
पूर्णांक nf_conntrack_icmpv6_packet(काष्ठा nf_conn *ct,
			       काष्ठा sk_buff *skb,
			       क्रमागत ip_conntrack_info ctinfo,
			       स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक *समयout = nf_ct_समयout_lookup(ct);
	अटल स्थिर u8 valid_new[] = अणु
		[ICMPV6_ECHO_REQUEST - 128] = 1,
		[ICMPV6_NI_QUERY - 128] = 1
	पूर्ण;

	अगर (state->pf != NFPROTO_IPV6)
		वापस -NF_ACCEPT;

	अगर (!nf_ct_is_confirmed(ct)) अणु
		पूर्णांक type = ct->tuplehash[0].tuple.dst.u.icmp.type - 128;

		अगर (type < 0 || type >= माप(valid_new) || !valid_new[type]) अणु
			/* Can't create a new ICMPv6 `conn' with this. */
			pr_debug("icmpv6: can't create new conn with type %u\n",
				 type + 128);
			nf_ct_dump_tuple_ipv6(&ct->tuplehash[0].tuple);
			वापस -NF_ACCEPT;
		पूर्ण
	पूर्ण

	अगर (!समयout)
		समयout = icmpv6_get_समयouts(nf_ct_net(ct));

	/* Do not immediately delete the connection after the first
	   successful reply to aव्योम excessive conntrackd traffic
	   and also to handle correctly ICMP echo reply duplicates. */
	nf_ct_refresh_acct(ct, ctinfo, skb, *समयout);

	वापस NF_ACCEPT;
पूर्ण


अटल व्योम icmpv6_error_log(स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा nf_hook_state *state,
			     स्थिर अक्षर *msg)
अणु
	nf_l4proto_log_invalid(skb, state->net, state->pf,
			       IPPROTO_ICMPV6, "%s", msg);
पूर्ण

पूर्णांक nf_conntrack_icmpv6_error(काष्ठा nf_conn *पंचांगpl,
			      काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक dataoff,
			      स्थिर काष्ठा nf_hook_state *state)
अणु
	जोड़ nf_inet_addr outer_daddr;
	स्थिर काष्ठा icmp6hdr *icmp6h;
	काष्ठा icmp6hdr _ih;
	पूर्णांक type;

	icmp6h = skb_header_poपूर्णांकer(skb, dataoff, माप(_ih), &_ih);
	अगर (icmp6h == शून्य) अणु
		icmpv6_error_log(skb, state, "short packet");
		वापस -NF_ACCEPT;
	पूर्ण

	अगर (state->hook == NF_INET_PRE_ROUTING &&
	    state->net->ct.sysctl_checksum &&
	    nf_ip6_checksum(skb, state->hook, dataoff, IPPROTO_ICMPV6)) अणु
		icmpv6_error_log(skb, state, "ICMPv6 checksum failed");
		वापस -NF_ACCEPT;
	पूर्ण

	type = icmp6h->icmp6_type - 130;
	अगर (type >= 0 && type < माप(noct_valid_new) &&
	    noct_valid_new[type]) अणु
		nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);
		वापस NF_ACCEPT;
	पूर्ण

	/* is not error message ? */
	अगर (icmp6h->icmp6_type >= 128)
		वापस NF_ACCEPT;

	स_नकल(&outer_daddr.ip6, &ipv6_hdr(skb)->daddr,
	       माप(outer_daddr.ip6));
	dataoff += माप(*icmp6h);
	वापस nf_conntrack_inet_error(पंचांगpl, skb, dataoff, state,
				       IPPROTO_ICMPV6, &outer_daddr);
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>
अटल पूर्णांक icmpv6_tuple_to_nlattr(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nf_conntrack_tuple *t)
अणु
	अगर (nla_put_be16(skb, CTA_PROTO_ICMPV6_ID, t->src.u.icmp.id) ||
	    nla_put_u8(skb, CTA_PROTO_ICMPV6_TYPE, t->dst.u.icmp.type) ||
	    nla_put_u8(skb, CTA_PROTO_ICMPV6_CODE, t->dst.u.icmp.code))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nla_policy icmpv6_nla_policy[CTA_PROTO_MAX+1] = अणु
	[CTA_PROTO_ICMPV6_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTO_ICMPV6_CODE]	= अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTO_ICMPV6_ID]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक icmpv6_nlattr_to_tuple(काष्ठा nlattr *tb[],
				काष्ठा nf_conntrack_tuple *tuple,
				u_पूर्णांक32_t flags)
अणु
	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_ICMPV6_TYPE)) अणु
		अगर (!tb[CTA_PROTO_ICMPV6_TYPE])
			वापस -EINVAL;

		tuple->dst.u.icmp.type = nla_get_u8(tb[CTA_PROTO_ICMPV6_TYPE]);
		अगर (tuple->dst.u.icmp.type < 128 ||
		    tuple->dst.u.icmp.type - 128 >= माप(invmap) ||
		    !invmap[tuple->dst.u.icmp.type - 128])
			वापस -EINVAL;
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_ICMPV6_CODE)) अणु
		अगर (!tb[CTA_PROTO_ICMPV6_CODE])
			वापस -EINVAL;

		tuple->dst.u.icmp.code = nla_get_u8(tb[CTA_PROTO_ICMPV6_CODE]);
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_ICMPV6_ID)) अणु
		अगर (!tb[CTA_PROTO_ICMPV6_ID])
			वापस -EINVAL;

		tuple->src.u.icmp.id = nla_get_be16(tb[CTA_PROTO_ICMPV6_ID]);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक icmpv6_nlattr_tuple_size(व्योम)
अणु
	अटल अचिन्हित पूर्णांक size __पढ़ो_mostly;

	अगर (!size)
		size = nla_policy_len(icmpv6_nla_policy, CTA_PROTO_MAX + 1);

	वापस size;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक icmpv6_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
					काष्ठा net *net, व्योम *data)
अणु
	अचिन्हित पूर्णांक *समयout = data;
	काष्ठा nf_icmp_net *in = nf_icmpv6_pernet(net);

	अगर (!समयout)
		समयout = icmpv6_get_समयouts(net);
	अगर (tb[CTA_TIMEOUT_ICMPV6_TIMEOUT]) अणु
		*समयout =
		    ntohl(nla_get_be32(tb[CTA_TIMEOUT_ICMPV6_TIMEOUT])) * HZ;
	पूर्ण अन्यथा अणु
		/* Set शेष ICMPv6 समयout. */
		*समयout = in->समयout;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
icmpv6_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक *समयout = data;

	अगर (nla_put_be32(skb, CTA_TIMEOUT_ICMPV6_TIMEOUT, htonl(*समयout / HZ)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy
icmpv6_समयout_nla_policy[CTA_TIMEOUT_ICMPV6_MAX+1] = अणु
	[CTA_TIMEOUT_ICMPV6_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_icmpv6_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_icmp_net *in = nf_icmpv6_pernet(net);

	in->समयout = nf_ct_icmpv6_समयout;
पूर्ण

स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_icmpv6 =
अणु
	.l4proto		= IPPROTO_ICMPV6,
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.tuple_to_nlattr	= icmpv6_tuple_to_nlattr,
	.nlattr_tuple_size	= icmpv6_nlattr_tuple_size,
	.nlattr_to_tuple	= icmpv6_nlattr_to_tuple,
	.nla_policy		= icmpv6_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= icmpv6_समयout_nlattr_to_obj,
		.obj_to_nlattr	= icmpv6_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_ICMP_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक),
		.nla_policy	= icmpv6_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
