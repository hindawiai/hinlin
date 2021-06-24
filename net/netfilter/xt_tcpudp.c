<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_tcpudp.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_DESCRIPTION("Xtables: TCP, UDP and UDP-Lite match");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xt_tcp");
MODULE_ALIAS("xt_udp");
MODULE_ALIAS("ipt_udp");
MODULE_ALIAS("ipt_tcp");
MODULE_ALIAS("ip6t_udp");
MODULE_ALIAS("ip6t_tcp");

/* Returns 1 अगर the port is matched by the range, 0 otherwise */
अटल अंतरभूत bool
port_match(u_पूर्णांक16_t min, u_पूर्णांक16_t max, u_पूर्णांक16_t port, bool invert)
अणु
	वापस (port >= min && port <= max) ^ invert;
पूर्ण

अटल bool
tcp_find_option(u_पूर्णांक8_t option,
		स्थिर काष्ठा sk_buff *skb,
		अचिन्हित पूर्णांक protoff,
		अचिन्हित पूर्णांक optlen,
		bool invert,
		bool *hotdrop)
अणु
	/* tcp.करोff is only 4 bits, ie. max 15 * 4 bytes */
	स्थिर u_पूर्णांक8_t *op;
	u_पूर्णांक8_t _opt[60 - माप(काष्ठा tcphdr)];
	अचिन्हित पूर्णांक i;

	pr_debug("finding option\n");

	अगर (!optlen)
		वापस invert;

	/* If we करोn't have the whole header, drop packet. */
	op = skb_header_poपूर्णांकer(skb, protoff + माप(काष्ठा tcphdr),
				optlen, _opt);
	अगर (op == शून्य) अणु
		*hotdrop = true;
		वापस false;
	पूर्ण

	क्रम (i = 0; i < optlen; ) अणु
		अगर (op[i] == option) वापस !invert;
		अगर (op[i] < 2) i++;
		अन्यथा i += op[i+1]?:1;
	पूर्ण

	वापस invert;
पूर्ण

अटल bool tcp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;
	स्थिर काष्ठा xt_tcp *tcpinfo = par->matchinfo;

	अगर (par->fragoff != 0) अणु
		/* To quote Alan:

		   Don't allow a fragment of TCP 8 bytes in. Nobody normal
		   causes this. Its a cracker trying to अवरोध in by करोing a
		   flag overग_लिखो to pass the direction checks.
		*/
		अगर (par->fragoff == 1) अणु
			pr_debug("Dropping evil TCP offset=1 frag.\n");
			par->hotdrop = true;
		पूर्ण
		/* Must not be a fragment. */
		वापस false;
	पूर्ण

	th = skb_header_poपूर्णांकer(skb, par->thoff, माप(_tcph), &_tcph);
	अगर (th == शून्य) अणु
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to drop. */
		pr_debug("Dropping evil TCP offset=0 tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण

	अगर (!port_match(tcpinfo->spts[0], tcpinfo->spts[1],
			ntohs(th->source),
			!!(tcpinfo->invflags & XT_TCP_INV_SRCPT)))
		वापस false;
	अगर (!port_match(tcpinfo->dpts[0], tcpinfo->dpts[1],
			ntohs(th->dest),
			!!(tcpinfo->invflags & XT_TCP_INV_DSTPT)))
		वापस false;
	अगर (!NF_INVF(tcpinfo, XT_TCP_INV_FLAGS,
		     (((अचिन्हित अक्षर *)th)[13] & tcpinfo->flg_mask) == tcpinfo->flg_cmp))
		वापस false;
	अगर (tcpinfo->option) अणु
		अगर (th->करोff * 4 < माप(_tcph)) अणु
			par->hotdrop = true;
			वापस false;
		पूर्ण
		अगर (!tcp_find_option(tcpinfo->option, skb, par->thoff,
				     th->करोff*4 - माप(_tcph),
				     tcpinfo->invflags & XT_TCP_INV_OPTION,
				     &par->hotdrop))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक tcp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_tcp *tcpinfo = par->matchinfo;

	/* Must specअगरy no unknown invflags */
	वापस (tcpinfo->invflags & ~XT_TCP_INV_MASK) ? -EINVAL : 0;
पूर्ण

अटल bool udp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा udphdr *uh;
	काष्ठा udphdr _udph;
	स्थिर काष्ठा xt_udp *udpinfo = par->matchinfo;

	/* Must not be a fragment. */
	अगर (par->fragoff != 0)
		वापस false;

	uh = skb_header_poपूर्णांकer(skb, par->thoff, माप(_udph), &_udph);
	अगर (uh == शून्य) अणु
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to drop. */
		pr_debug("Dropping evil UDP tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस port_match(udpinfo->spts[0], udpinfo->spts[1],
			  ntohs(uh->source),
			  !!(udpinfo->invflags & XT_UDP_INV_SRCPT))
		&& port_match(udpinfo->dpts[0], udpinfo->dpts[1],
			      ntohs(uh->dest),
			      !!(udpinfo->invflags & XT_UDP_INV_DSTPT));
पूर्ण

अटल पूर्णांक udp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_udp *udpinfo = par->matchinfo;

	/* Must specअगरy no unknown invflags */
	वापस (udpinfo->invflags & ~XT_UDP_INV_MASK) ? -EINVAL : 0;
पूर्ण

अटल काष्ठा xt_match tcpudp_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "tcp",
		.family		= NFPROTO_IPV4,
		.checkentry	= tcp_mt_check,
		.match		= tcp_mt,
		.matchsize	= माप(काष्ठा xt_tcp),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "tcp",
		.family		= NFPROTO_IPV6,
		.checkentry	= tcp_mt_check,
		.match		= tcp_mt,
		.matchsize	= माप(काष्ठा xt_tcp),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "udp",
		.family		= NFPROTO_IPV4,
		.checkentry	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= माप(काष्ठा xt_udp),
		.proto		= IPPROTO_UDP,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "udp",
		.family		= NFPROTO_IPV6,
		.checkentry	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= माप(काष्ठा xt_udp),
		.proto		= IPPROTO_UDP,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "udplite",
		.family		= NFPROTO_IPV4,
		.checkentry	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= माप(काष्ठा xt_udp),
		.proto		= IPPROTO_UDPLITE,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "udplite",
		.family		= NFPROTO_IPV6,
		.checkentry	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= माप(काष्ठा xt_udp),
		.proto		= IPPROTO_UDPLITE,
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tcpudp_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(tcpudp_mt_reg, ARRAY_SIZE(tcpudp_mt_reg));
पूर्ण

अटल व्योम __निकास tcpudp_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(tcpudp_mt_reg, ARRAY_SIZE(tcpudp_mt_reg));
पूर्ण

module_init(tcpudp_mt_init);
module_निकास(tcpudp_mt_निकास);
