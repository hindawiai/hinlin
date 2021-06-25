<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * nf_nat_snmp_basic.c
 *
 * Basic SNMP Application Layer Gateway
 *
 * This IP NAT module is पूर्णांकended क्रम use with SNMP network
 * discovery and monitoring applications where target networks use
 * conflicting निजी address realms.
 *
 * Static NAT is used to remap the networks from the view of the network
 * management प्रणाली at the IP layer, and this module remaps some application
 * layer addresses to match.
 *
 * The simplest क्रमm of ALG is perक्रमmed, where only tagged IP addresses
 * are modअगरied.  The module करोes not need to be MIB aware and only scans
 * messages at the ASN.1/BER level.
 *
 * Currently, only SNMPv1 and SNMPv2 are supported.
 *
 * More inक्रमmation on ALG and associated issues can be found in
 * RFC 2962
 *
 * The ASB.1/BER parsing code is derived from the gxsnmp package by Gregory
 * McLean & Jochen Friedrich, stripped करोwn क्रम use in the kernel.
 *
 * Copyright (c) 2000 RP Internet (www.rpi.net.au).
 *
 * Author: James Morris <jmorris@पूर्णांकercode.com.au>
 *
 * Copyright (c) 2006-2010 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <net/checksum.h>
#समावेश <net/udp.h>

#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <linux/netfilter/nf_conntrack_snmp.h>
#समावेश "nf_nat_snmp_basic.asn1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");
MODULE_DESCRIPTION("Basic SNMP Application Layer Gateway");
MODULE_ALIAS("ip_nat_snmp_basic");
MODULE_ALIAS_NFCT_HELPER("snmp_trap");

#घोषणा SNMP_PORT 161
#घोषणा SNMP_TRAP_PORT 162

अटल DEFINE_SPINLOCK(snmp_lock);

काष्ठा snmp_ctx अणु
	अचिन्हित अक्षर *begin;
	__sum16 *check;
	__be32 from;
	__be32 to;
पूर्ण;

अटल व्योम fast_csum(काष्ठा snmp_ctx *ctx, अचिन्हित अक्षर offset)
अणु
	अचिन्हित अक्षर s[12] = अणु0,पूर्ण;
	पूर्णांक size;

	अगर (offset & 1) अणु
		स_नकल(&s[1], &ctx->from, 4);
		स_नकल(&s[7], &ctx->to, 4);
		s[0] = ~0;
		s[1] = ~s[1];
		s[2] = ~s[2];
		s[3] = ~s[3];
		s[4] = ~s[4];
		s[5] = ~0;
		size = 12;
	पूर्ण अन्यथा अणु
		स_नकल(&s[0], &ctx->from, 4);
		स_नकल(&s[4], &ctx->to, 4);
		s[0] = ~s[0];
		s[1] = ~s[1];
		s[2] = ~s[2];
		s[3] = ~s[3];
		size = 8;
	पूर्ण
	*ctx->check = csum_fold(csum_partial(s, size,
					     ~csum_unfold(*ctx->check)));
पूर्ण

पूर्णांक snmp_version(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
		 स्थिर व्योम *data, माप_प्रकार datalen)
अणु
	अगर (datalen != 1)
		वापस -EINVAL;
	अगर (*(अचिन्हित अक्षर *)data > 1)
		वापस -ENOTSUPP;
	वापस 1;
पूर्ण

पूर्णांक snmp_helper(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
		स्थिर व्योम *data, माप_प्रकार datalen)
अणु
	काष्ठा snmp_ctx *ctx = (काष्ठा snmp_ctx *)context;
	__be32 *pdata;

	अगर (datalen != 4)
		वापस -EINVAL;
	pdata = (__be32 *)data;
	अगर (*pdata == ctx->from) अणु
		pr_debug("%s: %pI4 to %pI4\n", __func__,
			 (व्योम *)&ctx->from, (व्योम *)&ctx->to);

		अगर (*ctx->check)
			fast_csum(ctx, (अचिन्हित अक्षर *)data - ctx->begin);
		*pdata = ctx->to;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक snmp_translate(काष्ठा nf_conn *ct, पूर्णांक dir, काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा udphdr *udph = (काष्ठा udphdr *)((__be32 *)iph + iph->ihl);
	u16 datalen = ntohs(udph->len) - माप(काष्ठा udphdr);
	अक्षर *data = (अचिन्हित अक्षर *)udph + माप(काष्ठा udphdr);
	काष्ठा snmp_ctx ctx;
	पूर्णांक ret;

	अगर (dir == IP_CT_सूची_ORIGINAL) अणु
		ctx.from = ct->tuplehash[dir].tuple.src.u3.ip;
		ctx.to = ct->tuplehash[!dir].tuple.dst.u3.ip;
	पूर्ण अन्यथा अणु
		ctx.from = ct->tuplehash[!dir].tuple.src.u3.ip;
		ctx.to = ct->tuplehash[dir].tuple.dst.u3.ip;
	पूर्ण

	अगर (ctx.from == ctx.to)
		वापस NF_ACCEPT;

	ctx.begin = (अचिन्हित अक्षर *)udph + माप(काष्ठा udphdr);
	ctx.check = &udph->check;
	ret = asn1_ber_decoder(&nf_nat_snmp_basic_decoder, &ctx, data, datalen);
	अगर (ret < 0) अणु
		nf_ct_helper_log(skb, ct, "parser failed\n");
		वापस NF_DROP;
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण

/* We करोn't actually set up expectations, just adjust पूर्णांकernal IP
 * addresses अगर this is being NATted
 */
अटल पूर्णांक help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		काष्ठा nf_conn *ct,
		क्रमागत ip_conntrack_info ctinfo)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	अचिन्हित पूर्णांक ret;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	स्थिर काष्ठा udphdr *udph = (काष्ठा udphdr *)((__be32 *)iph + iph->ihl);

	/* SNMP replies and originating SNMP traps get mangled */
	अगर (udph->source == htons(SNMP_PORT) && dir != IP_CT_सूची_REPLY)
		वापस NF_ACCEPT;
	अगर (udph->dest == htons(SNMP_TRAP_PORT) && dir != IP_CT_सूची_ORIGINAL)
		वापस NF_ACCEPT;

	/* No NAT? */
	अगर (!(ct->status & IPS_NAT_MASK))
		वापस NF_ACCEPT;

	/* Make sure the packet length is ok.  So far, we were only guaranteed
	 * to have a valid length IP header plus 8 bytes, which means we have
	 * enough room क्रम a UDP header.  Just verअगरy the UDP length field so we
	 * can mess around with the payload.
	 */
	अगर (ntohs(udph->len) != skb->len - (iph->ihl << 2)) अणु
		nf_ct_helper_log(skb, ct, "dropping malformed packet\n");
		वापस NF_DROP;
	पूर्ण

	अगर (skb_ensure_writable(skb, skb->len)) अणु
		nf_ct_helper_log(skb, ct, "cannot mangle packet");
		वापस NF_DROP;
	पूर्ण

	spin_lock_bh(&snmp_lock);
	ret = snmp_translate(ct, dir, skb);
	spin_unlock_bh(&snmp_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nf_conntrack_expect_policy snmp_exp_policy = अणु
	.max_expected	= 0,
	.समयout	= 180,
पूर्ण;

अटल काष्ठा nf_conntrack_helper snmp_trap_helper __पढ़ो_mostly = अणु
	.me			= THIS_MODULE,
	.help			= help,
	.expect_policy		= &snmp_exp_policy,
	.name			= "snmp_trap",
	.tuple.src.l3num	= AF_INET,
	.tuple.src.u.udp.port	= cpu_to_be16(SNMP_TRAP_PORT),
	.tuple.dst.protonum	= IPPROTO_UDP,
पूर्ण;

अटल पूर्णांक __init nf_nat_snmp_basic_init(व्योम)
अणु
	BUG_ON(nf_nat_snmp_hook != शून्य);
	RCU_INIT_POINTER(nf_nat_snmp_hook, help);

	वापस nf_conntrack_helper_रेजिस्टर(&snmp_trap_helper);
पूर्ण

अटल व्योम __निकास nf_nat_snmp_basic_fini(व्योम)
अणु
	RCU_INIT_POINTER(nf_nat_snmp_hook, शून्य);
	synchronize_rcu();
	nf_conntrack_helper_unरेजिस्टर(&snmp_trap_helper);
पूर्ण

module_init(nf_nat_snmp_basic_init);
module_निकास(nf_nat_snmp_basic_fini);
