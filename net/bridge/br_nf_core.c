<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Handle firewalling core
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 *	Bart De Schuymer		<bdschuym@panकरोra.be>
 *
 *	Lennert dedicates this file to Kerstin Wurdinger.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/in_route.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/route.h>

#समावेश "br_private.h"
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

अटल व्योम fake_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			     काष्ठा sk_buff *skb, u32 mtu,
			     bool confirm_neigh)
अणु
पूर्ण

अटल व्योम fake_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			  काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल u32 *fake_cow_metrics(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old)
अणु
	वापस शून्य;
पूर्ण

अटल काष्ठा neighbour *fake_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					   काष्ठा sk_buff *skb,
					   स्थिर व्योम *daddr)
अणु
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक fake_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dst->dev->mtu;
पूर्ण

अटल काष्ठा dst_ops fake_dst_ops = अणु
	.family		= AF_INET,
	.update_pmtu	= fake_update_pmtu,
	.redirect	= fake_redirect,
	.cow_metrics	= fake_cow_metrics,
	.neigh_lookup	= fake_neigh_lookup,
	.mtu		= fake_mtu,
पूर्ण;

/*
 * Initialize bogus route table used to keep netfilter happy.
 * Currently, we fill in the PMTU entry because netfilter
 * refragmentation needs it, and the rt_flags entry because
 * ipt_REJECT needs it.  Future netfilter modules might
 * require us to fill additional fields.
 */
अटल स्थिर u32 br_dst_शेष_metrics[RTAX_MAX] = अणु
	[RTAX_MTU - 1] = 1500,
पूर्ण;

व्योम br_netfilter_rtable_init(काष्ठा net_bridge *br)
अणु
	काष्ठा rtable *rt = &br->fake_rtable;

	atomic_set(&rt->dst.__refcnt, 1);
	rt->dst.dev = br->dev;
	dst_init_metrics(&rt->dst, br_dst_शेष_metrics, true);
	rt->dst.flags	= DST_NOXFRM | DST_FAKE_RTABLE;
	rt->dst.ops = &fake_dst_ops;
पूर्ण

पूर्णांक __init br_nf_core_init(व्योम)
अणु
	वापस dst_entries_init(&fake_dst_ops);
पूर्ण

व्योम br_nf_core_fini(व्योम)
अणु
	dst_entries_destroy(&fake_dst_ops);
पूर्ण
