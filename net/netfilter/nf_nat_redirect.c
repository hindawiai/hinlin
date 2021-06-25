<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * Copyright (c) 2011 Patrick McHardy <kaber@trash.net>
 *
 * Based on Rusty Russell's IPv4 REसूचीECT target. Development of IPv6
 * NAT funded by Astaro.
 */

#समावेश <linux/अगर.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/addrconf.h>
#समावेश <net/checksum.h>
#समावेश <net/protocol.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_redirect.h>

अचिन्हित पूर्णांक
nf_nat_redirect_ipv4(काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr,
		     अचिन्हित पूर्णांक hooknum)
अणु
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	__be32 newdst;
	काष्ठा nf_nat_range2 newrange;

	WARN_ON(hooknum != NF_INET_PRE_ROUTING &&
		hooknum != NF_INET_LOCAL_OUT);

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED)));

	/* Local packets: make them go to loopback */
	अगर (hooknum == NF_INET_LOCAL_OUT) अणु
		newdst = htonl(0x7F000001);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा in_device *indev;

		newdst = 0;

		indev = __in_dev_get_rcu(skb->dev);
		अगर (indev) अणु
			स्थिर काष्ठा in_अगरaddr *अगरa;

			अगरa = rcu_dereference(indev->अगरa_list);
			अगर (अगरa)
				newdst = अगरa->अगरa_local;
		पूर्ण

		अगर (!newdst)
			वापस NF_DROP;
	पूर्ण

	/* Transfer from original range. */
	स_रखो(&newrange.min_addr, 0, माप(newrange.min_addr));
	स_रखो(&newrange.max_addr, 0, माप(newrange.max_addr));
	newrange.flags	     = mr->range[0].flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr.ip = newdst;
	newrange.max_addr.ip = newdst;
	newrange.min_proto   = mr->range[0].min;
	newrange.max_proto   = mr->range[0].max;

	/* Hand modअगरied range to generic setup. */
	वापस nf_nat_setup_info(ct, &newrange, NF_NAT_MANIP_DST);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_redirect_ipv4);

अटल स्थिर काष्ठा in6_addr loopback_addr = IN6ADDR_LOOPBACK_INIT;

अचिन्हित पूर्णांक
nf_nat_redirect_ipv6(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_nat_range2 *range,
		     अचिन्हित पूर्णांक hooknum)
अणु
	काष्ठा nf_nat_range2 newrange;
	काष्ठा in6_addr newdst;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (hooknum == NF_INET_LOCAL_OUT) अणु
		newdst = loopback_addr;
	पूर्ण अन्यथा अणु
		काष्ठा inet6_dev *idev;
		काष्ठा inet6_अगरaddr *अगरa;
		bool addr = false;

		idev = __in6_dev_get(skb->dev);
		अगर (idev != शून्य) अणु
			पढ़ो_lock_bh(&idev->lock);
			list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
				newdst = अगरa->addr;
				addr = true;
				अवरोध;
			पूर्ण
			पढ़ो_unlock_bh(&idev->lock);
		पूर्ण

		अगर (!addr)
			वापस NF_DROP;
	पूर्ण

	newrange.flags		= range->flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr.in6	= newdst;
	newrange.max_addr.in6	= newdst;
	newrange.min_proto	= range->min_proto;
	newrange.max_proto	= range->max_proto;

	वापस nf_nat_setup_info(ct, &newrange, NF_NAT_MANIP_DST);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_redirect_ipv6);
