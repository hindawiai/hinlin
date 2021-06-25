<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      broadcast connection tracking helper
 *
 *      (c) 2005 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <net/route.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>

पूर्णांक nf_conntrack_broadcast_help(काष्ठा sk_buff *skb,
				काष्ठा nf_conn *ct,
				क्रमागत ip_conntrack_info ctinfo,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा in_device *in_dev;
	काष्ठा nf_conn_help *help = nfct_help(ct);
	__be32 mask = 0;

	/* we're only पूर्णांकerested in locally generated packets */
	अगर (skb->sk == शून्य || !net_eq(nf_ct_net(ct), sock_net(skb->sk)))
		जाओ out;
	अगर (rt == शून्य || !(rt->rt_flags & RTCF_BROADCAST))
		जाओ out;
	अगर (CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL)
		जाओ out;

	in_dev = __in_dev_get_rcu(rt->dst.dev);
	अगर (in_dev != शून्य) अणु
		स्थिर काष्ठा in_अगरaddr *अगरa;

		in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
			अगर (अगरa->अगरa_flags & IFA_F_SECONDARY)
				जारी;

			अगर (अगरa->अगरa_broadcast == iph->daddr) अणु
				mask = अगरa->अगरa_mask;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mask == 0)
		जाओ out;

	exp = nf_ct_expect_alloc(ct);
	अगर (exp == शून्य)
		जाओ out;

	exp->tuple                = ct->tuplehash[IP_CT_सूची_REPLY].tuple;
	exp->tuple.src.u.udp.port = help->helper->tuple.src.u.udp.port;

	exp->mask.src.u3.ip       = mask;
	exp->mask.src.u.udp.port  = htons(0xFFFF);

	exp->expectfn             = शून्य;
	exp->flags                = NF_CT_EXPECT_PERMANENT;
	exp->class		  = NF_CT_EXPECT_CLASS_DEFAULT;
	exp->helper               = शून्य;

	nf_ct_expect_related(exp, 0);
	nf_ct_expect_put(exp);

	nf_ct_refresh(ct, skb, समयout * HZ);
out:
	वापस NF_ACCEPT;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_broadcast_help);

MODULE_LICENSE("GPL");
