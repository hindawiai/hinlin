<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* module that allows mangling of the arp payload */
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_arp/arpt_mangle.h>
#समावेश <net/sock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bart De Schuymer <bdschuym@pandora.be>");
MODULE_DESCRIPTION("arptables arp payload mangle target");

अटल अचिन्हित पूर्णांक
target(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा arpt_mangle *mangle = par->targinfo;
	स्थिर काष्ठा arphdr *arp;
	अचिन्हित अक्षर *arpptr;
	पूर्णांक pln, hln;

	अगर (skb_ensure_writable(skb, skb->len))
		वापस NF_DROP;

	arp = arp_hdr(skb);
	arpptr = skb_network_header(skb) + माप(*arp);
	pln = arp->ar_pln;
	hln = arp->ar_hln;
	/* We assume that pln and hln were checked in the match */
	अगर (mangle->flags & ARPT_MANGLE_SDEV) अणु
		अगर (ARPT_DEV_ADDR_LEN_MAX < hln ||
		   (arpptr + hln > skb_tail_poपूर्णांकer(skb)))
			वापस NF_DROP;
		स_नकल(arpptr, mangle->src_devaddr, hln);
	पूर्ण
	arpptr += hln;
	अगर (mangle->flags & ARPT_MANGLE_SIP) अणु
		अगर (ARPT_MANGLE_ADDR_LEN_MAX < pln ||
		   (arpptr + pln > skb_tail_poपूर्णांकer(skb)))
			वापस NF_DROP;
		स_नकल(arpptr, &mangle->u_s.src_ip, pln);
	पूर्ण
	arpptr += pln;
	अगर (mangle->flags & ARPT_MANGLE_TDEV) अणु
		अगर (ARPT_DEV_ADDR_LEN_MAX < hln ||
		   (arpptr + hln > skb_tail_poपूर्णांकer(skb)))
			वापस NF_DROP;
		स_नकल(arpptr, mangle->tgt_devaddr, hln);
	पूर्ण
	arpptr += hln;
	अगर (mangle->flags & ARPT_MANGLE_TIP) अणु
		अगर (ARPT_MANGLE_ADDR_LEN_MAX < pln ||
		   (arpptr + pln > skb_tail_poपूर्णांकer(skb)))
			वापस NF_DROP;
		स_नकल(arpptr, &mangle->u_t.tgt_ip, pln);
	पूर्ण
	वापस mangle->target;
पूर्ण

अटल पूर्णांक checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा arpt_mangle *mangle = par->targinfo;

	अगर (mangle->flags & ~ARPT_MANGLE_MASK ||
	    !(mangle->flags & ARPT_MANGLE_MASK))
		वापस -EINVAL;

	अगर (mangle->target != NF_DROP && mangle->target != NF_ACCEPT &&
	   mangle->target != XT_CONTINUE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा xt_target arpt_mangle_reg __पढ़ो_mostly = अणु
	.name		= "mangle",
	.family		= NFPROTO_ARP,
	.target		= target,
	.tarमाला_लोize	= माप(काष्ठा arpt_mangle),
	.checkentry	= checkentry,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init arpt_mangle_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&arpt_mangle_reg);
पूर्ण

अटल व्योम __निकास arpt_mangle_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&arpt_mangle_reg);
पूर्ण

module_init(arpt_mangle_init);
module_निकास(arpt_mangle_fini);
