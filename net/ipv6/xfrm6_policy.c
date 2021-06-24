<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xfrm6_policy.c: based on xfrm4_policy.c
 *
 * Authors:
 *	Mitsuru KANDA @USAGI
 *	Kazunori MIYAZAWA @USAGI
 *	Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 *		IPv6 support
 *	YOSHIFUJI Hideaki
 *		Split up af-specअगरic portion
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <net/addrconf.h>
#समावेश <net/dst.h>
#समावेश <net/xfrm.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/l3mdev.h>

अटल काष्ठा dst_entry *xfrm6_dst_lookup(काष्ठा net *net, पूर्णांक tos, पूर्णांक oअगर,
					  स्थिर xfrm_address_t *saddr,
					  स्थिर xfrm_address_t *daddr,
					  u32 mark)
अणु
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;
	पूर्णांक err;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_oअगर = l3mdev_master_अगरindex_by_index(net, oअगर);
	fl6.flowi6_flags = FLOWI_FLAG_SKIP_NH_OIF;
	fl6.flowi6_mark = mark;
	स_नकल(&fl6.daddr, daddr, माप(fl6.daddr));
	अगर (saddr)
		स_नकल(&fl6.saddr, saddr, माप(fl6.saddr));

	dst = ip6_route_output(net, शून्य, &fl6);

	err = dst->error;
	अगर (dst->error) अणु
		dst_release(dst);
		dst = ERR_PTR(err);
	पूर्ण

	वापस dst;
पूर्ण

अटल पूर्णांक xfrm6_get_saddr(काष्ठा net *net, पूर्णांक oअगर,
			   xfrm_address_t *saddr, xfrm_address_t *daddr,
			   u32 mark)
अणु
	काष्ठा dst_entry *dst;
	काष्ठा net_device *dev;

	dst = xfrm6_dst_lookup(net, 0, oअगर, शून्य, daddr, mark);
	अगर (IS_ERR(dst))
		वापस -EHOSTUNREACH;

	dev = ip6_dst_idev(dst)->dev;
	ipv6_dev_get_saddr(dev_net(dev), dev, &daddr->in6, 0, &saddr->in6);
	dst_release(dst);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_fill_dst(काष्ठा xfrm_dst *xdst, काष्ठा net_device *dev,
			  स्थिर काष्ठा flowi *fl)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)xdst->route;

	xdst->u.dst.dev = dev;
	dev_hold(dev);

	xdst->u.rt6.rt6i_idev = in6_dev_get(dev);
	अगर (!xdst->u.rt6.rt6i_idev) अणु
		dev_put(dev);
		वापस -ENODEV;
	पूर्ण

	/* Sheit... I remember I did this right. Apparently,
	 * it was magically lost, so this code needs audit */
	xdst->u.rt6.rt6i_flags = rt->rt6i_flags & (RTF_ANYCAST |
						   RTF_LOCAL);
	xdst->route_cookie = rt6_get_cookie(rt);
	xdst->u.rt6.rt6i_gateway = rt->rt6i_gateway;
	xdst->u.rt6.rt6i_dst = rt->rt6i_dst;
	xdst->u.rt6.rt6i_src = rt->rt6i_src;
	INIT_LIST_HEAD(&xdst->u.rt6.rt6i_uncached);
	rt6_uncached_list_add(&xdst->u.rt6);
	atomic_inc(&dev_net(dev)->ipv6.rt6_stats->fib_rt_uncache);

	वापस 0;
पूर्ण

अटल व्योम xfrm6_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			      काष्ठा sk_buff *skb, u32 mtu,
			      bool confirm_neigh)
अणु
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;
	काष्ठा dst_entry *path = xdst->route;

	path->ops->update_pmtu(path, sk, skb, mtu, confirm_neigh);
पूर्ण

अटल व्योम xfrm6_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;
	काष्ठा dst_entry *path = xdst->route;

	path->ops->redirect(path, sk, skb);
पूर्ण

अटल व्योम xfrm6_dst_destroy(काष्ठा dst_entry *dst)
अणु
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;

	अगर (likely(xdst->u.rt6.rt6i_idev))
		in6_dev_put(xdst->u.rt6.rt6i_idev);
	dst_destroy_metrics_generic(dst);
	अगर (xdst->u.rt6.rt6i_uncached_list)
		rt6_uncached_list_del(&xdst->u.rt6);
	xfrm_dst_destroy(xdst);
पूर्ण

अटल व्योम xfrm6_dst_अगरकरोwn(काष्ठा dst_entry *dst, काष्ठा net_device *dev,
			     पूर्णांक unरेजिस्टर)
अणु
	काष्ठा xfrm_dst *xdst;

	अगर (!unरेजिस्टर)
		वापस;

	xdst = (काष्ठा xfrm_dst *)dst;
	अगर (xdst->u.rt6.rt6i_idev->dev == dev) अणु
		काष्ठा inet6_dev *loopback_idev =
			in6_dev_get(dev_net(dev)->loopback_dev);

		करो अणु
			in6_dev_put(xdst->u.rt6.rt6i_idev);
			xdst->u.rt6.rt6i_idev = loopback_idev;
			in6_dev_hold(loopback_idev);
			xdst = (काष्ठा xfrm_dst *)xfrm_dst_child(&xdst->u.dst);
		पूर्ण जबतक (xdst->u.dst.xfrm);

		__in6_dev_put(loopback_idev);
	पूर्ण

	xfrm_dst_अगरकरोwn(dst, dev);
पूर्ण

अटल काष्ठा dst_ops xfrm6_dst_ops_ढाँचा = अणु
	.family =		AF_INET6,
	.update_pmtu =		xfrm6_update_pmtu,
	.redirect =		xfrm6_redirect,
	.cow_metrics =		dst_cow_metrics_generic,
	.destroy =		xfrm6_dst_destroy,
	.अगरकरोwn =		xfrm6_dst_अगरकरोwn,
	.local_out =		__ip6_local_out,
	.gc_thresh =		32768,
पूर्ण;

अटल स्थिर काष्ठा xfrm_policy_afinfo xfrm6_policy_afinfo = अणु
	.dst_ops =		&xfrm6_dst_ops_ढाँचा,
	.dst_lookup =		xfrm6_dst_lookup,
	.get_saddr =		xfrm6_get_saddr,
	.fill_dst =		xfrm6_fill_dst,
	.blackhole_route =	ip6_blackhole_route,
पूर्ण;

अटल पूर्णांक __init xfrm6_policy_init(व्योम)
अणु
	वापस xfrm_policy_रेजिस्टर_afinfo(&xfrm6_policy_afinfo, AF_INET6);
पूर्ण

अटल व्योम xfrm6_policy_fini(व्योम)
अणु
	xfrm_policy_unरेजिस्टर_afinfo(&xfrm6_policy_afinfo);
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table xfrm6_policy_table[] = अणु
	अणु
		.procname       = "xfrm6_gc_thresh",
		.data		= &init_net.xfrm.xfrm6_dst_ops.gc_thresh,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __net_init xfrm6_net_sysctl_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	काष्ठा ctl_table_header *hdr;

	table = xfrm6_policy_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(xfrm6_policy_table), GFP_KERNEL);
		अगर (!table)
			जाओ err_alloc;

		table[0].data = &net->xfrm.xfrm6_dst_ops.gc_thresh;
	पूर्ण

	hdr = रेजिस्टर_net_sysctl(net, "net/ipv6", table);
	अगर (!hdr)
		जाओ err_reg;

	net->ipv6.sysctl.xfrm6_hdr = hdr;
	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास xfrm6_net_sysctl_निकास(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	अगर (!net->ipv6.sysctl.xfrm6_hdr)
		वापस;

	table = net->ipv6.sysctl.xfrm6_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->ipv6.sysctl.xfrm6_hdr);
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
पूर्ण
#अन्यथा /* CONFIG_SYSCTL */
अटल अंतरभूत पूर्णांक xfrm6_net_sysctl_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xfrm6_net_sysctl_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init xfrm6_net_init(काष्ठा net *net)
अणु
	पूर्णांक ret;

	स_नकल(&net->xfrm.xfrm6_dst_ops, &xfrm6_dst_ops_ढाँचा,
	       माप(xfrm6_dst_ops_ढाँचा));
	ret = dst_entries_init(&net->xfrm.xfrm6_dst_ops);
	अगर (ret)
		वापस ret;

	ret = xfrm6_net_sysctl_init(net);
	अगर (ret)
		dst_entries_destroy(&net->xfrm.xfrm6_dst_ops);

	वापस ret;
पूर्ण

अटल व्योम __net_निकास xfrm6_net_निकास(काष्ठा net *net)
अणु
	xfrm6_net_sysctl_निकास(net);
	dst_entries_destroy(&net->xfrm.xfrm6_dst_ops);
पूर्ण

अटल काष्ठा pernet_operations xfrm6_net_ops = अणु
	.init	= xfrm6_net_init,
	.निकास	= xfrm6_net_निकास,
पूर्ण;

पूर्णांक __init xfrm6_init(व्योम)
अणु
	पूर्णांक ret;

	ret = xfrm6_policy_init();
	अगर (ret)
		जाओ out;
	ret = xfrm6_state_init();
	अगर (ret)
		जाओ out_policy;

	ret = xfrm6_protocol_init();
	अगर (ret)
		जाओ out_state;

	रेजिस्टर_pernet_subsys(&xfrm6_net_ops);
out:
	वापस ret;
out_state:
	xfrm6_state_fini();
out_policy:
	xfrm6_policy_fini();
	जाओ out;
पूर्ण

व्योम xfrm6_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&xfrm6_net_ops);
	xfrm6_protocol_fini();
	xfrm6_policy_fini();
	xfrm6_state_fini();
पूर्ण
