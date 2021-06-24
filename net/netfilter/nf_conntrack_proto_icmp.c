<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2006-2010 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/in.h>
#समावेश <linux/icmp.h>
#समावेश <linux/seq_file.h>
#समावेश <net/ip.h>
#समावेश <net/checksum.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_log.h>

#समावेश "nf_internals.h"

अटल स्थिर अचिन्हित पूर्णांक nf_ct_icmp_समयout = 30*HZ;

bool icmp_pkt_to_tuple(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक dataoff,
		       काष्ठा net *net, काष्ठा nf_conntrack_tuple *tuple)
अणु
	स्थिर काष्ठा icmphdr *hp;
	काष्ठा icmphdr _hdr;

	hp = skb_header_poपूर्णांकer(skb, dataoff, माप(_hdr), &_hdr);
	अगर (hp == शून्य)
		वापस false;

	tuple->dst.u.icmp.type = hp->type;
	tuple->src.u.icmp.id = hp->un.echo.id;
	tuple->dst.u.icmp.code = hp->code;

	वापस true;
पूर्ण

/* Add 1; spaces filled with 0. */
अटल स्थिर u_पूर्णांक8_t invmap[] = अणु
	[ICMP_ECHO] = ICMP_ECHOREPLY + 1,
	[ICMP_ECHOREPLY] = ICMP_ECHO + 1,
	[ICMP_TIMESTAMP] = ICMP_TIMESTAMPREPLY + 1,
	[ICMP_TIMESTAMPREPLY] = ICMP_TIMESTAMP + 1,
	[ICMP_INFO_REQUEST] = ICMP_INFO_REPLY + 1,
	[ICMP_INFO_REPLY] = ICMP_INFO_REQUEST + 1,
	[ICMP_ADDRESS] = ICMP_ADDRESSREPLY + 1,
	[ICMP_ADDRESSREPLY] = ICMP_ADDRESS + 1
पूर्ण;

bool nf_conntrack_invert_icmp_tuple(काष्ठा nf_conntrack_tuple *tuple,
				    स्थिर काष्ठा nf_conntrack_tuple *orig)
अणु
	अगर (orig->dst.u.icmp.type >= माप(invmap) ||
	    !invmap[orig->dst.u.icmp.type])
		वापस false;

	tuple->src.u.icmp.id = orig->src.u.icmp.id;
	tuple->dst.u.icmp.type = invmap[orig->dst.u.icmp.type] - 1;
	tuple->dst.u.icmp.code = orig->dst.u.icmp.code;
	वापस true;
पूर्ण

/* Returns verdict क्रम packet, or -1 क्रम invalid. */
पूर्णांक nf_conntrack_icmp_packet(काष्ठा nf_conn *ct,
			     काष्ठा sk_buff *skb,
			     क्रमागत ip_conntrack_info ctinfo,
			     स्थिर काष्ठा nf_hook_state *state)
अणु
	/* Do not immediately delete the connection after the first
	   successful reply to aव्योम excessive conntrackd traffic
	   and also to handle correctly ICMP echo reply duplicates. */
	अचिन्हित पूर्णांक *समयout = nf_ct_समयout_lookup(ct);
	अटल स्थिर u_पूर्णांक8_t valid_new[] = अणु
		[ICMP_ECHO] = 1,
		[ICMP_TIMESTAMP] = 1,
		[ICMP_INFO_REQUEST] = 1,
		[ICMP_ADDRESS] = 1
	पूर्ण;

	अगर (state->pf != NFPROTO_IPV4)
		वापस -NF_ACCEPT;

	अगर (ct->tuplehash[0].tuple.dst.u.icmp.type >= माप(valid_new) ||
	    !valid_new[ct->tuplehash[0].tuple.dst.u.icmp.type]) अणु
		/* Can't create a new ICMP `conn' with this. */
		pr_debug("icmp: can't create new conn with type %u\n",
			 ct->tuplehash[0].tuple.dst.u.icmp.type);
		nf_ct_dump_tuple_ip(&ct->tuplehash[0].tuple);
		वापस -NF_ACCEPT;
	पूर्ण

	अगर (!समयout)
		समयout = &nf_icmp_pernet(nf_ct_net(ct))->समयout;

	nf_ct_refresh_acct(ct, ctinfo, skb, *समयout);
	वापस NF_ACCEPT;
पूर्ण

/* Check inner header is related to any of the existing connections */
पूर्णांक nf_conntrack_inet_error(काष्ठा nf_conn *पंचांगpl, काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    स्थिर काष्ठा nf_hook_state *state,
			    u8 l4proto, जोड़ nf_inet_addr *outer_daddr)
अणु
	काष्ठा nf_conntrack_tuple innertuple, origtuple;
	स्थिर काष्ठा nf_conntrack_tuple_hash *h;
	स्थिर काष्ठा nf_conntrack_zone *zone;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conntrack_zone पंचांगp;
	जोड़ nf_inet_addr *ct_daddr;
	क्रमागत ip_conntrack_dir dir;
	काष्ठा nf_conn *ct;

	WARN_ON(skb_nfct(skb));
	zone = nf_ct_zone_पंचांगpl(पंचांगpl, skb, &पंचांगp);

	/* Are they talking about one of our connections? */
	अगर (!nf_ct_get_tuplepr(skb, dataoff,
			       state->pf, state->net, &origtuple))
		वापस -NF_ACCEPT;

	/* Ordinarily, we'd expect the inverted tupleproto, but it's
	   been preserved inside the ICMP. */
	अगर (!nf_ct_invert_tuple(&innertuple, &origtuple))
		वापस -NF_ACCEPT;

	h = nf_conntrack_find_get(state->net, zone, &innertuple);
	अगर (!h)
		वापस -NF_ACCEPT;

	/* Consider: A -> T (=This machine) -> B
	 *   Conntrack entry will look like this:
	 *      Original:  A->B
	 *      Reply:     B->T (SNAT हाल) OR A
	 *
	 * When this function runs, we got packet that looks like this:
	 * iphdr|icmphdr|inner_iphdr|l4header (tcp, udp, ..).
	 *
	 * Above nf_conntrack_find_get() makes lookup based on inner_hdr,
	 * so we should expect that destination of the found connection
	 * matches outer header destination address.
	 *
	 * In above example, we can consider these two हालs:
	 *  1. Error coming in reply direction from B or M (middle box) to
	 *     T (SNAT हाल) or A.
	 *     Inner saddr will be B, dst will be T or A.
	 *     The found conntrack will be reply tuple (B->T/A).
	 *  2. Error coming in original direction from A or M to B.
	 *     Inner saddr will be A, inner daddr will be B.
	 *     The found conntrack will be original tuple (A->B).
	 *
	 * In both हालs, conntrack[dir].dst == inner.dst.
	 *
	 * A bogus packet could look like this:
	 *   Inner: B->T
	 *   Outer: B->X (other machine reachable by T).
	 *
	 * In this हाल, lookup yields connection A->B and will
	 * set packet from B->X as *RELATED*, even though no connection
	 * from X was ever seen.
	 */
	ct = nf_ct_tuplehash_to_ctrack(h);
	dir = NF_CT_सूचीECTION(h);
	ct_daddr = &ct->tuplehash[dir].tuple.dst.u3;
	अगर (!nf_inet_addr_cmp(outer_daddr, ct_daddr)) अणु
		अगर (state->pf == AF_INET) अणु
			nf_l4proto_log_invalid(skb, state->net, state->pf,
					       l4proto,
					       "outer daddr %pI4 != inner %pI4",
					       &outer_daddr->ip, &ct_daddr->ip);
		पूर्ण अन्यथा अगर (state->pf == AF_INET6) अणु
			nf_l4proto_log_invalid(skb, state->net, state->pf,
					       l4proto,
					       "outer daddr %pI6 != inner %pI6",
					       &outer_daddr->ip6, &ct_daddr->ip6);
		पूर्ण
		nf_ct_put(ct);
		वापस -NF_ACCEPT;
	पूर्ण

	ctinfo = IP_CT_RELATED;
	अगर (dir == IP_CT_सूची_REPLY)
		ctinfo += IP_CT_IS_REPLY;

	/* Update skb to refer to this connection */
	nf_ct_set(skb, ct, ctinfo);
	वापस NF_ACCEPT;
पूर्ण

अटल व्योम icmp_error_log(स्थिर काष्ठा sk_buff *skb,
			   स्थिर काष्ठा nf_hook_state *state,
			   स्थिर अक्षर *msg)
अणु
	nf_l4proto_log_invalid(skb, state->net, state->pf,
			       IPPROTO_ICMP, "%s", msg);
पूर्ण

/* Small and modअगरied version of icmp_rcv */
पूर्णांक nf_conntrack_icmpv4_error(काष्ठा nf_conn *पंचांगpl,
			      काष्ठा sk_buff *skb, अचिन्हित पूर्णांक dataoff,
			      स्थिर काष्ठा nf_hook_state *state)
अणु
	जोड़ nf_inet_addr outer_daddr;
	स्थिर काष्ठा icmphdr *icmph;
	काष्ठा icmphdr _ih;

	/* Not enough header? */
	icmph = skb_header_poपूर्णांकer(skb, dataoff, माप(_ih), &_ih);
	अगर (icmph == शून्य) अणु
		icmp_error_log(skb, state, "short packet");
		वापस -NF_ACCEPT;
	पूर्ण

	/* See nf_conntrack_proto_tcp.c */
	अगर (state->net->ct.sysctl_checksum &&
	    state->hook == NF_INET_PRE_ROUTING &&
	    nf_ip_checksum(skb, state->hook, dataoff, IPPROTO_ICMP)) अणु
		icmp_error_log(skb, state, "bad hw icmp checksum");
		वापस -NF_ACCEPT;
	पूर्ण

	/*
	 *	18 is the highest 'known' ICMP type. Anything अन्यथा is a mystery
	 *
	 *	RFC 1122: 3.2.2  Unknown ICMP messages types MUST be silently
	 *		  discarded.
	 */
	अगर (icmph->type > NR_ICMP_TYPES) अणु
		icmp_error_log(skb, state, "invalid icmp type");
		वापस -NF_ACCEPT;
	पूर्ण

	/* Need to track icmp error message? */
	अगर (!icmp_is_err(icmph->type))
		वापस NF_ACCEPT;

	स_रखो(&outer_daddr, 0, माप(outer_daddr));
	outer_daddr.ip = ip_hdr(skb)->daddr;

	dataoff += माप(*icmph);
	वापस nf_conntrack_inet_error(पंचांगpl, skb, dataoff, state,
				       IPPROTO_ICMP, &outer_daddr);
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>

अटल पूर्णांक icmp_tuple_to_nlattr(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nf_conntrack_tuple *t)
अणु
	अगर (nla_put_be16(skb, CTA_PROTO_ICMP_ID, t->src.u.icmp.id) ||
	    nla_put_u8(skb, CTA_PROTO_ICMP_TYPE, t->dst.u.icmp.type) ||
	    nla_put_u8(skb, CTA_PROTO_ICMP_CODE, t->dst.u.icmp.code))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nla_policy icmp_nla_policy[CTA_PROTO_MAX+1] = अणु
	[CTA_PROTO_ICMP_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTO_ICMP_CODE]	= अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTO_ICMP_ID]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक icmp_nlattr_to_tuple(काष्ठा nlattr *tb[],
				काष्ठा nf_conntrack_tuple *tuple,
				u_पूर्णांक32_t flags)
अणु
	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_ICMP_TYPE)) अणु
		अगर (!tb[CTA_PROTO_ICMP_TYPE])
			वापस -EINVAL;

		tuple->dst.u.icmp.type = nla_get_u8(tb[CTA_PROTO_ICMP_TYPE]);
		अगर (tuple->dst.u.icmp.type >= माप(invmap) ||
		    !invmap[tuple->dst.u.icmp.type])
			वापस -EINVAL;
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_ICMP_CODE)) अणु
		अगर (!tb[CTA_PROTO_ICMP_CODE])
			वापस -EINVAL;

		tuple->dst.u.icmp.code = nla_get_u8(tb[CTA_PROTO_ICMP_CODE]);
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_ICMP_ID)) अणु
		अगर (!tb[CTA_PROTO_ICMP_ID])
			वापस -EINVAL;

		tuple->src.u.icmp.id = nla_get_be16(tb[CTA_PROTO_ICMP_ID]);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक icmp_nlattr_tuple_size(व्योम)
अणु
	अटल अचिन्हित पूर्णांक size __पढ़ो_mostly;

	अगर (!size)
		size = nla_policy_len(icmp_nla_policy, CTA_PROTO_MAX + 1);

	वापस size;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक icmp_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
				      काष्ठा net *net, व्योम *data)
अणु
	अचिन्हित पूर्णांक *समयout = data;
	काष्ठा nf_icmp_net *in = nf_icmp_pernet(net);

	अगर (tb[CTA_TIMEOUT_ICMP_TIMEOUT]) अणु
		अगर (!समयout)
			समयout = &in->समयout;
		*समयout =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_ICMP_TIMEOUT])) * HZ;
	पूर्ण अन्यथा अगर (समयout) अणु
		/* Set शेष ICMP समयout. */
		*समयout = in->समयout;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
icmp_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक *समयout = data;

	अगर (nla_put_be32(skb, CTA_TIMEOUT_ICMP_TIMEOUT, htonl(*समयout / HZ)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy
icmp_समयout_nla_policy[CTA_TIMEOUT_ICMP_MAX+1] = अणु
	[CTA_TIMEOUT_ICMP_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_icmp_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_icmp_net *in = nf_icmp_pernet(net);

	in->समयout = nf_ct_icmp_समयout;
पूर्ण

स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_icmp =
अणु
	.l4proto		= IPPROTO_ICMP,
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.tuple_to_nlattr	= icmp_tuple_to_nlattr,
	.nlattr_tuple_size	= icmp_nlattr_tuple_size,
	.nlattr_to_tuple	= icmp_nlattr_to_tuple,
	.nla_policy		= icmp_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= icmp_समयout_nlattr_to_obj,
		.obj_to_nlattr	= icmp_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_ICMP_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक),
		.nla_policy	= icmp_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
