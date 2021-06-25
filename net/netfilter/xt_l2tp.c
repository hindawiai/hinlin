<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match L2TP header parameters. */

/* (C) 2013      James Chapman <jchapman@katalix.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>
#समावेश <linux/l2tp.h>

#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_tcpudp.h>
#समावेश <linux/netfilter/xt_l2tp.h>

/* L2TP header masks */
#घोषणा L2TP_HDR_T_BIT	0x8000
#घोषणा L2TP_HDR_L_BIT	0x4000
#घोषणा L2TP_HDR_VER	0x000f

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("Xtables: L2TP header match");
MODULE_ALIAS("ipt_l2tp");
MODULE_ALIAS("ip6t_l2tp");

/* The L2TP fields that can be matched */
काष्ठा l2tp_data अणु
	u32 tid;
	u32 sid;
	u8 type;
	u8 version;
पूर्ण;

जोड़ l2tp_val अणु
	__be16 val16[2];
	__be32 val32;
पूर्ण;

अटल bool l2tp_match(स्थिर काष्ठा xt_l2tp_info *info, काष्ठा l2tp_data *data)
अणु
	अगर ((info->flags & XT_L2TP_TYPE) && (info->type != data->type))
		वापस false;

	अगर ((info->flags & XT_L2TP_VERSION) && (info->version != data->version))
		वापस false;

	/* Check tid only क्रम L2TPv3 control or any L2TPv2 packets */
	अगर ((info->flags & XT_L2TP_TID) &&
	    ((data->type == XT_L2TP_TYPE_CONTROL) || (data->version == 2)) &&
	    (info->tid != data->tid))
		वापस false;

	/* Check sid only क्रम L2TP data packets */
	अगर ((info->flags & XT_L2TP_SID) && (data->type == XT_L2TP_TYPE_DATA) &&
	    (info->sid != data->sid))
		वापस false;

	वापस true;
पूर्ण

/* Parse L2TP header fields when UDP encapsulation is used. Handles
 * L2TPv2 and L2TPv3. Note the L2TPv3 control and data packets have a
 * dअगरferent क्रमmat. See
 * RFC2661, Section 3.1, L2TPv2 Header Format
 * RFC3931, Section 3.2.1, L2TPv3 Control Message Header
 * RFC3931, Section 3.2.2, L2TPv3 Data Message Header
 * RFC3931, Section 4.1.2.1, L2TPv3 Session Header over UDP
 */
अटल bool l2tp_udp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par, u16 thoff)
अणु
	स्थिर काष्ठा xt_l2tp_info *info = par->matchinfo;
	पूर्णांक uhlen = माप(काष्ठा udphdr);
	पूर्णांक offs = thoff + uhlen;
	जोड़ l2tp_val *lh;
	जोड़ l2tp_val lhbuf;
	u16 flags;
	काष्ठा l2tp_data data = अणु 0, पूर्ण;

	अगर (par->fragoff != 0)
		वापस false;

	/* Extract L2TP header fields. The flags in the first 16 bits
	 * tell us where the other fields are.
	 */
	lh = skb_header_poपूर्णांकer(skb, offs, 2, &lhbuf);
	अगर (lh == शून्य)
		वापस false;

	flags = ntohs(lh->val16[0]);
	अगर (flags & L2TP_HDR_T_BIT)
		data.type = XT_L2TP_TYPE_CONTROL;
	अन्यथा
		data.type = XT_L2TP_TYPE_DATA;
	data.version = (u8) flags & L2TP_HDR_VER;

	/* Now extract the L2TP tid/sid. These are in dअगरferent places
	 * क्रम L2TPv2 (rfc2661) and L2TPv3 (rfc3931). For L2TPv2, we
	 * must also check to see अगर the length field is present,
	 * since this affects the offsets पूर्णांकo the packet of the
	 * tid/sid fields.
	 */
	अगर (data.version == 3) अणु
		lh = skb_header_poपूर्णांकer(skb, offs + 4, 4, &lhbuf);
		अगर (lh == शून्य)
			वापस false;
		अगर (data.type == XT_L2TP_TYPE_CONTROL)
			data.tid = ntohl(lh->val32);
		अन्यथा
			data.sid = ntohl(lh->val32);
	पूर्ण अन्यथा अगर (data.version == 2) अणु
		अगर (flags & L2TP_HDR_L_BIT)
			offs += 2;
		lh = skb_header_poपूर्णांकer(skb, offs + 2, 4, &lhbuf);
		अगर (lh == शून्य)
			वापस false;
		data.tid = (u32) ntohs(lh->val16[0]);
		data.sid = (u32) ntohs(lh->val16[1]);
	पूर्ण अन्यथा
		वापस false;

	वापस l2tp_match(info, &data);
पूर्ण

/* Parse L2TP header fields क्रम IP encapsulation (no UDP header).
 * L2TPv3 data packets have a dअगरferent क्रमm with IP encap. See
 * RC3931, Section 4.1.1.1, L2TPv3 Session Header over IP.
 * RC3931, Section 4.1.1.2, L2TPv3 Control and Data Traffic over IP.
 */
अटल bool l2tp_ip_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par, u16 thoff)
अणु
	स्थिर काष्ठा xt_l2tp_info *info = par->matchinfo;
	जोड़ l2tp_val *lh;
	जोड़ l2tp_val lhbuf;
	काष्ठा l2tp_data data = अणु 0, पूर्ण;

	/* For IP encap, the L2TP sid is the first 32-bits. */
	lh = skb_header_poपूर्णांकer(skb, thoff, माप(lhbuf), &lhbuf);
	अगर (lh == शून्य)
		वापस false;
	अगर (lh->val32 == 0) अणु
		/* Must be a control packet. The L2TP tid is further
		 * पूर्णांकo the packet.
		 */
		data.type = XT_L2TP_TYPE_CONTROL;
		lh = skb_header_poपूर्णांकer(skb, thoff + 8, माप(lhbuf),
					&lhbuf);
		अगर (lh == शून्य)
			वापस false;
		data.tid = ntohl(lh->val32);
	पूर्ण अन्यथा अणु
		data.sid = ntohl(lh->val32);
		data.type = XT_L2TP_TYPE_DATA;
	पूर्ण

	data.version = 3;

	वापस l2tp_match(info, &data);
पूर्ण

अटल bool l2tp_mt4(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);
	u8 ipproto = iph->protocol;

	/* l2tp_mt_check4 alपढ़ोy restricts the transport protocol */
	चयन (ipproto) अणु
	हाल IPPROTO_UDP:
		वापस l2tp_udp_mt(skb, par, par->thoff);
	हाल IPPROTO_L2TP:
		वापस l2tp_ip_mt(skb, par, par->thoff);
	पूर्ण

	वापस false;
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल bool l2tp_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	अचिन्हित पूर्णांक thoff = 0;
	अचिन्हित लघु fragoff = 0;
	पूर्णांक ipproto;

	ipproto = ipv6_find_hdr(skb, &thoff, -1, &fragoff, शून्य);
	अगर (fragoff != 0)
		वापस false;

	/* l2tp_mt_check6 alपढ़ोy restricts the transport protocol */
	चयन (ipproto) अणु
	हाल IPPROTO_UDP:
		वापस l2tp_udp_mt(skb, par, thoff);
	हाल IPPROTO_L2TP:
		वापस l2tp_ip_mt(skb, par, thoff);
	पूर्ण

	वापस false;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक l2tp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_l2tp_info *info = par->matchinfo;

	/* Check क्रम invalid flags */
	अगर (info->flags & ~(XT_L2TP_TID | XT_L2TP_SID | XT_L2TP_VERSION |
			    XT_L2TP_TYPE)) अणु
		pr_info_ratelimited("unknown flags: %x\n", info->flags);
		वापस -EINVAL;
	पूर्ण

	/* At least one of tid, sid or type=control must be specअगरied */
	अगर ((!(info->flags & XT_L2TP_TID)) &&
	    (!(info->flags & XT_L2TP_SID)) &&
	    ((!(info->flags & XT_L2TP_TYPE)) ||
	     (info->type != XT_L2TP_TYPE_CONTROL))) अणु
		pr_info_ratelimited("invalid flags combination: %x\n",
				    info->flags);
		वापस -EINVAL;
	पूर्ण

	/* If version 2 is specअगरied, check that incompatible params
	 * are not supplied
	 */
	अगर (info->flags & XT_L2TP_VERSION) अणु
		अगर ((info->version < 2) || (info->version > 3)) अणु
			pr_info_ratelimited("wrong L2TP version: %u\n",
					    info->version);
			वापस -EINVAL;
		पूर्ण

		अगर (info->version == 2) अणु
			अगर ((info->flags & XT_L2TP_TID) &&
			    (info->tid > 0xffff)) अणु
				pr_info_ratelimited("v2 tid > 0xffff: %u\n",
						    info->tid);
				वापस -EINVAL;
			पूर्ण
			अगर ((info->flags & XT_L2TP_SID) &&
			    (info->sid > 0xffff)) अणु
				pr_info_ratelimited("v2 sid > 0xffff: %u\n",
						    info->sid);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक l2tp_mt_check4(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_l2tp_info *info = par->matchinfo;
	स्थिर काष्ठा ipt_entry *e = par->entryinfo;
	स्थिर काष्ठा ipt_ip *ip = &e->ip;
	पूर्णांक ret;

	ret = l2tp_mt_check(par);
	अगर (ret != 0)
		वापस ret;

	अगर ((ip->proto != IPPROTO_UDP) &&
	    (ip->proto != IPPROTO_L2TP)) अणु
		pr_info_ratelimited("missing protocol rule (udp|l2tpip)\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((ip->proto == IPPROTO_L2TP) &&
	    (info->version == 2)) अणु
		pr_info_ratelimited("v2 doesn't support IP mode\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल पूर्णांक l2tp_mt_check6(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_l2tp_info *info = par->matchinfo;
	स्थिर काष्ठा ip6t_entry *e = par->entryinfo;
	स्थिर काष्ठा ip6t_ip6 *ip = &e->ipv6;
	पूर्णांक ret;

	ret = l2tp_mt_check(par);
	अगर (ret != 0)
		वापस ret;

	अगर ((ip->proto != IPPROTO_UDP) &&
	    (ip->proto != IPPROTO_L2TP)) अणु
		pr_info_ratelimited("missing protocol rule (udp|l2tpip)\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((ip->proto == IPPROTO_L2TP) &&
	    (info->version == 2)) अणु
		pr_info_ratelimited("v2 doesn't support IP mode\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा xt_match l2tp_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name      = "l2tp",
		.revision  = 0,
		.family    = NFPROTO_IPV4,
		.match     = l2tp_mt4,
		.matchsize = XT_ALIGN(माप(काष्ठा xt_l2tp_info)),
		.checkentry = l2tp_mt_check4,
		.hooks     = ((1 << NF_INET_PRE_ROUTING) |
			      (1 << NF_INET_LOCAL_IN) |
			      (1 << NF_INET_LOCAL_OUT) |
			      (1 << NF_INET_FORWARD)),
		.me        = THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name      = "l2tp",
		.revision  = 0,
		.family    = NFPROTO_IPV6,
		.match     = l2tp_mt6,
		.matchsize = XT_ALIGN(माप(काष्ठा xt_l2tp_info)),
		.checkentry = l2tp_mt_check6,
		.hooks     = ((1 << NF_INET_PRE_ROUTING) |
			      (1 << NF_INET_LOCAL_IN) |
			      (1 << NF_INET_LOCAL_OUT) |
			      (1 << NF_INET_FORWARD)),
		.me        = THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init l2tp_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(&l2tp_mt_reg[0], ARRAY_SIZE(l2tp_mt_reg));
पूर्ण

अटल व्योम __निकास l2tp_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(&l2tp_mt_reg[0], ARRAY_SIZE(l2tp_mt_reg));
पूर्ण

module_init(l2tp_mt_init);
module_निकास(l2tp_mt_निकास);
