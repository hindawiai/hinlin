<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Creates audit record क्रम dropped/accepted packets
 *
 * (C) 2010-2011 Thomas Graf <tgraf@redhat.com>
 * (C) 2010-2011 Red Hat, Inc.
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/audit.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_AUDIT.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Graf <tgraf@redhat.com>");
MODULE_DESCRIPTION("Xtables: creates audit records for dropped/accepted packets");
MODULE_ALIAS("ipt_AUDIT");
MODULE_ALIAS("ip6t_AUDIT");
MODULE_ALIAS("ebt_AUDIT");
MODULE_ALIAS("arpt_AUDIT");

अटल bool audit_ip4(काष्ठा audit_buffer *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr _iph;
	स्थिर काष्ठा iphdr *ih;

	ih = skb_header_poपूर्णांकer(skb, skb_network_offset(skb), माप(_iph), &_iph);
	अगर (!ih)
		वापस false;

	audit_log_क्रमmat(ab, " saddr=%pI4 daddr=%pI4 proto=%hhu",
			 &ih->saddr, &ih->daddr, ih->protocol);

	वापस true;
पूर्ण

अटल bool audit_ip6(काष्ठा audit_buffer *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr _ip6h;
	स्थिर काष्ठा ipv6hdr *ih;
	u8 nexthdr;
	__be16 frag_off;

	ih = skb_header_poपूर्णांकer(skb, skb_network_offset(skb), माप(_ip6h), &_ip6h);
	अगर (!ih)
		वापस false;

	nexthdr = ih->nexthdr;
	ipv6_skip_exthdr(skb, skb_network_offset(skb) + माप(_ip6h), &nexthdr, &frag_off);

	audit_log_क्रमmat(ab, " saddr=%pI6c daddr=%pI6c proto=%hhu",
			 &ih->saddr, &ih->daddr, nexthdr);

	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक
audit_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा audit_buffer *ab;
	पूर्णांक fam = -1;

	अगर (audit_enabled == AUDIT_OFF)
		जाओ errout;
	ab = audit_log_start(शून्य, GFP_ATOMIC, AUDIT_NETFILTER_PKT);
	अगर (ab == शून्य)
		जाओ errout;

	audit_log_क्रमmat(ab, "mark=%#x", skb->mark);

	चयन (xt_family(par)) अणु
	हाल NFPROTO_BRIDGE:
		चयन (eth_hdr(skb)->h_proto) अणु
		हाल htons(ETH_P_IP):
			fam = audit_ip4(ab, skb) ? NFPROTO_IPV4 : -1;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			fam = audit_ip6(ab, skb) ? NFPROTO_IPV6 : -1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NFPROTO_IPV4:
		fam = audit_ip4(ab, skb) ? NFPROTO_IPV4 : -1;
		अवरोध;
	हाल NFPROTO_IPV6:
		fam = audit_ip6(ab, skb) ? NFPROTO_IPV6 : -1;
		अवरोध;
	पूर्ण

	अगर (fam == -1)
		audit_log_क्रमmat(ab, " saddr=? daddr=? proto=-1");

	audit_log_end(ab);

errout:
	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक
audit_tg_ebt(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	audit_tg(skb, par);
	वापस EBT_CONTINUE;
पूर्ण

अटल पूर्णांक audit_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_audit_info *info = par->targinfo;

	अगर (info->type > XT_AUDIT_TYPE_MAX) अणु
		pr_info_ratelimited("Audit type out of range (valid range: 0..%hhu)\n",
				    XT_AUDIT_TYPE_MAX);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_target audit_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "AUDIT",
		.family		= NFPROTO_UNSPEC,
		.target		= audit_tg,
		.tarमाला_लोize	= माप(काष्ठा xt_audit_info),
		.checkentry	= audit_tg_check,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "AUDIT",
		.family		= NFPROTO_BRIDGE,
		.target		= audit_tg_ebt,
		.tarमाला_लोize	= माप(काष्ठा xt_audit_info),
		.checkentry	= audit_tg_check,
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init audit_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(audit_tg_reg, ARRAY_SIZE(audit_tg_reg));
पूर्ण

अटल व्योम __निकास audit_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(audit_tg_reg, ARRAY_SIZE(audit_tg_reg));
पूर्ण

module_init(audit_tg_init);
module_निकास(audit_tg_निकास);
