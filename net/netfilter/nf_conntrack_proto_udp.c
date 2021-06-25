<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/udp.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/checksum.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <net/netfilter/ipv4/nf_conntrack_ipv4.h>
#समावेश <net/netfilter/ipv6/nf_conntrack_ipv6.h>

अटल स्थिर अचिन्हित पूर्णांक udp_समयouts[UDP_CT_MAX] = अणु
	[UDP_CT_UNREPLIED]	= 30*HZ,
	[UDP_CT_REPLIED]	= 120*HZ,
पूर्ण;

अटल अचिन्हित पूर्णांक *udp_get_समयouts(काष्ठा net *net)
अणु
	वापस nf_udp_pernet(net)->समयouts;
पूर्ण

अटल व्योम udp_error_log(स्थिर काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nf_hook_state *state,
			  स्थिर अक्षर *msg)
अणु
	nf_l4proto_log_invalid(skb, state->net, state->pf,
			       IPPROTO_UDP, "%s", msg);
पूर्ण

अटल bool udp_error(काष्ठा sk_buff *skb,
		      अचिन्हित पूर्णांक dataoff,
		      स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक udplen = skb->len - dataoff;
	स्थिर काष्ठा udphdr *hdr;
	काष्ठा udphdr _hdr;

	/* Header is too small? */
	hdr = skb_header_poपूर्णांकer(skb, dataoff, माप(_hdr), &_hdr);
	अगर (!hdr) अणु
		udp_error_log(skb, state, "short packet");
		वापस true;
	पूर्ण

	/* Truncated/malक्रमmed packets */
	अगर (ntohs(hdr->len) > udplen || ntohs(hdr->len) < माप(*hdr)) अणु
		udp_error_log(skb, state, "truncated/malformed packet");
		वापस true;
	पूर्ण

	/* Packet with no checksum */
	अगर (!hdr->check)
		वापस false;

	/* Checksum invalid? Ignore.
	 * We skip checking packets on the outgoing path
	 * because the checksum is assumed to be correct.
	 * FIXME: Source route IP option packets --RR */
	अगर (state->hook == NF_INET_PRE_ROUTING &&
	    state->net->ct.sysctl_checksum &&
	    nf_checksum(skb, state->hook, dataoff, IPPROTO_UDP, state->pf)) अणु
		udp_error_log(skb, state, "bad checksum");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Returns verdict क्रम packet, and may modअगरy conntracktype */
पूर्णांक nf_conntrack_udp_packet(काष्ठा nf_conn *ct,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    क्रमागत ip_conntrack_info ctinfo,
			    स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक *समयouts;

	अगर (udp_error(skb, dataoff, state))
		वापस -NF_ACCEPT;

	समयouts = nf_ct_समयout_lookup(ct);
	अगर (!समयouts)
		समयouts = udp_get_समयouts(nf_ct_net(ct));

	अगर (!nf_ct_is_confirmed(ct))
		ct->proto.udp.stream_ts = 2 * HZ + jअगरfies;

	/* If we've seen traffic both ways, this is some kind of UDP
	 * stream. Set Assured.
	 */
	अगर (test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) अणु
		अचिन्हित दीर्घ extra = समयouts[UDP_CT_UNREPLIED];

		/* Still active after two seconds? Extend समयout. */
		अगर (समय_after(jअगरfies, ct->proto.udp.stream_ts))
			extra = समयouts[UDP_CT_REPLIED];

		nf_ct_refresh_acct(ct, ctinfo, skb, extra);

		/* never set ASSURED क्रम IPS_NAT_CLASH, they समय out soon */
		अगर (unlikely((ct->status & IPS_NAT_CLASH)))
			वापस NF_ACCEPT;

		/* Also, more likely to be important, and not a probe */
		अगर (!test_and_set_bit(IPS_ASSURED_BIT, &ct->status))
			nf_conntrack_event_cache(IPCT_ASSURED, ct);
	पूर्ण अन्यथा अणु
		nf_ct_refresh_acct(ct, ctinfo, skb, समयouts[UDP_CT_UNREPLIED]);
	पूर्ण
	वापस NF_ACCEPT;
पूर्ण

#अगर_घोषित CONFIG_NF_CT_PROTO_UDPLITE
अटल व्योम udplite_error_log(स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा nf_hook_state *state,
			      स्थिर अक्षर *msg)
अणु
	nf_l4proto_log_invalid(skb, state->net, state->pf,
			       IPPROTO_UDPLITE, "%s", msg);
पूर्ण

अटल bool udplite_error(काष्ठा sk_buff *skb,
			  अचिन्हित पूर्णांक dataoff,
			  स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक udplen = skb->len - dataoff;
	स्थिर काष्ठा udphdr *hdr;
	काष्ठा udphdr _hdr;
	अचिन्हित पूर्णांक cscov;

	/* Header is too small? */
	hdr = skb_header_poपूर्णांकer(skb, dataoff, माप(_hdr), &_hdr);
	अगर (!hdr) अणु
		udplite_error_log(skb, state, "short packet");
		वापस true;
	पूर्ण

	cscov = ntohs(hdr->len);
	अगर (cscov == 0) अणु
		cscov = udplen;
	पूर्ण अन्यथा अगर (cscov < माप(*hdr) || cscov > udplen) अणु
		udplite_error_log(skb, state, "invalid checksum coverage");
		वापस true;
	पूर्ण

	/* UDPLITE mandates checksums */
	अगर (!hdr->check) अणु
		udplite_error_log(skb, state, "checksum missing");
		वापस true;
	पूर्ण

	/* Checksum invalid? Ignore. */
	अगर (state->hook == NF_INET_PRE_ROUTING &&
	    state->net->ct.sysctl_checksum &&
	    nf_checksum_partial(skb, state->hook, dataoff, cscov, IPPROTO_UDP,
				state->pf)) अणु
		udplite_error_log(skb, state, "bad checksum");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Returns verdict क्रम packet, and may modअगरy conntracktype */
पूर्णांक nf_conntrack_udplite_packet(काष्ठा nf_conn *ct,
				काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक dataoff,
				क्रमागत ip_conntrack_info ctinfo,
				स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक *समयouts;

	अगर (udplite_error(skb, dataoff, state))
		वापस -NF_ACCEPT;

	समयouts = nf_ct_समयout_lookup(ct);
	अगर (!समयouts)
		समयouts = udp_get_समयouts(nf_ct_net(ct));

	/* If we've seen traffic both ways, this is some kind of UDP
	   stream.  Extend समयout. */
	अगर (test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) अणु
		nf_ct_refresh_acct(ct, ctinfo, skb,
				   समयouts[UDP_CT_REPLIED]);

		अगर (unlikely((ct->status & IPS_NAT_CLASH)))
			वापस NF_ACCEPT;

		/* Also, more likely to be important, and not a probe */
		अगर (!test_and_set_bit(IPS_ASSURED_BIT, &ct->status))
			nf_conntrack_event_cache(IPCT_ASSURED, ct);
	पूर्ण अन्यथा अणु
		nf_ct_refresh_acct(ct, ctinfo, skb, समयouts[UDP_CT_UNREPLIED]);
	पूर्ण
	वापस NF_ACCEPT;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक udp_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
				     काष्ठा net *net, व्योम *data)
अणु
	अचिन्हित पूर्णांक *समयouts = data;
	काष्ठा nf_udp_net *un = nf_udp_pernet(net);

	अगर (!समयouts)
		समयouts = un->समयouts;

	/* set शेष समयouts क्रम UDP. */
	समयouts[UDP_CT_UNREPLIED] = un->समयouts[UDP_CT_UNREPLIED];
	समयouts[UDP_CT_REPLIED] = un->समयouts[UDP_CT_REPLIED];

	अगर (tb[CTA_TIMEOUT_UDP_UNREPLIED]) अणु
		समयouts[UDP_CT_UNREPLIED] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_UDP_UNREPLIED])) * HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_UDP_REPLIED]) अणु
		समयouts[UDP_CT_REPLIED] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_UDP_REPLIED])) * HZ;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
udp_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक *समयouts = data;

	अगर (nla_put_be32(skb, CTA_TIMEOUT_UDP_UNREPLIED,
			 htonl(समयouts[UDP_CT_UNREPLIED] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_UDP_REPLIED,
			 htonl(समयouts[UDP_CT_REPLIED] / HZ)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy
udp_समयout_nla_policy[CTA_TIMEOUT_UDP_MAX+1] = अणु
       [CTA_TIMEOUT_UDP_UNREPLIED]	= अणु .type = NLA_U32 पूर्ण,
       [CTA_TIMEOUT_UDP_REPLIED]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_udp_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_udp_net *un = nf_udp_pernet(net);
	पूर्णांक i;

	क्रम (i = 0; i < UDP_CT_MAX; i++)
		un->समयouts[i] = udp_समयouts[i];
पूर्ण

स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_udp =
अणु
	.l4proto		= IPPROTO_UDP,
	.allow_clash		= true,
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.tuple_to_nlattr	= nf_ct_port_tuple_to_nlattr,
	.nlattr_to_tuple	= nf_ct_port_nlattr_to_tuple,
	.nlattr_tuple_size	= nf_ct_port_nlattr_tuple_size,
	.nla_policy		= nf_ct_port_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= udp_समयout_nlattr_to_obj,
		.obj_to_nlattr	= udp_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_UDP_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक) * CTA_TIMEOUT_UDP_MAX,
		.nla_policy	= udp_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;

#अगर_घोषित CONFIG_NF_CT_PROTO_UDPLITE
स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_udplite =
अणु
	.l4proto		= IPPROTO_UDPLITE,
	.allow_clash		= true,
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.tuple_to_nlattr	= nf_ct_port_tuple_to_nlattr,
	.nlattr_to_tuple	= nf_ct_port_nlattr_to_tuple,
	.nlattr_tuple_size	= nf_ct_port_nlattr_tuple_size,
	.nla_policy		= nf_ct_port_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= udp_समयout_nlattr_to_obj,
		.obj_to_nlattr	= udp_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_UDP_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक) * CTA_TIMEOUT_UDP_MAX,
		.nla_policy	= udp_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
#पूर्ण_अगर
