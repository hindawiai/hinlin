<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_SYNPROXY.h>

#समावेश <net/netfilter/nf_synproxy.h>

अटल अचिन्हित पूर्णांक
synproxy_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_synproxy_info *info = par->targinfo;
	काष्ठा net *net = xt_net(par);
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	काष्ठा synproxy_options opts = अणुपूर्ण;
	काष्ठा tcphdr *th, _th;

	अगर (nf_ip6_checksum(skb, xt_hooknum(par), par->thoff, IPPROTO_TCP))
		वापस NF_DROP;

	th = skb_header_poपूर्णांकer(skb, par->thoff, माप(_th), &_th);
	अगर (th == शून्य)
		वापस NF_DROP;

	अगर (!synproxy_parse_options(skb, par->thoff, th, &opts))
		वापस NF_DROP;

	अगर (th->syn && !(th->ack || th->fin || th->rst)) अणु
		/* Initial SYN from client */
		this_cpu_inc(snet->stats->syn_received);

		अगर (th->ece && th->cwr)
			opts.options |= XT_SYNPROXY_OPT_ECN;

		opts.options &= info->options;
		opts.mss_encode = opts.mss_option;
		opts.mss_option = info->mss;
		अगर (opts.options & XT_SYNPROXY_OPT_TIMESTAMP)
			synproxy_init_बारtamp_cookie(info, &opts);
		अन्यथा
			opts.options &= ~(XT_SYNPROXY_OPT_WSCALE |
					  XT_SYNPROXY_OPT_SACK_PERM |
					  XT_SYNPROXY_OPT_ECN);

		synproxy_send_client_synack_ipv6(net, skb, th, &opts);
		consume_skb(skb);
		वापस NF_STOLEN;

	पूर्ण अन्यथा अगर (th->ack && !(th->fin || th->rst || th->syn)) अणु
		/* ACK from client */
		अगर (synproxy_recv_client_ack_ipv6(net, skb, th, &opts,
						  ntohl(th->seq))) अणु
			consume_skb(skb);
			वापस NF_STOLEN;
		पूर्ण अन्यथा अणु
			वापस NF_DROP;
		पूर्ण
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक synproxy_tg6_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(par->net);
	स्थिर काष्ठा ip6t_entry *e = par->entryinfo;
	पूर्णांक err;

	अगर (!(e->ipv6.flags & IP6T_F_PROTO) ||
	    e->ipv6.proto != IPPROTO_TCP ||
	    e->ipv6.invflags & XT_INV_PROTO)
		वापस -EINVAL;

	err = nf_ct_netns_get(par->net, par->family);
	अगर (err)
		वापस err;

	err = nf_synproxy_ipv6_init(snet, par->net);
	अगर (err) अणु
		nf_ct_netns_put(par->net, par->family);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम synproxy_tg6_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(par->net);

	nf_synproxy_ipv6_fini(snet, par->net);
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_target synproxy_tg6_reg __पढ़ो_mostly = अणु
	.name		= "SYNPROXY",
	.family		= NFPROTO_IPV6,
	.hooks		= (1 << NF_INET_LOCAL_IN) | (1 << NF_INET_FORWARD),
	.target		= synproxy_tg6,
	.tarमाला_लोize	= माप(काष्ठा xt_synproxy_info),
	.checkentry	= synproxy_tg6_check,
	.destroy	= synproxy_tg6_destroy,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init synproxy_tg6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&synproxy_tg6_reg);
पूर्ण

अटल व्योम __निकास synproxy_tg6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&synproxy_tg6_reg);
पूर्ण

module_init(synproxy_tg6_init);
module_निकास(synproxy_tg6_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Intercept IPv6 TCP connections and establish them using syncookies");
