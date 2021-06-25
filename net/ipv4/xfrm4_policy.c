<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xfrm4_policy.c
 *
 * Changes:
 *	Kazunori MIYAZAWA @USAGI
 * 	YOSHIFUJI Hideaki @USAGI
 *		Split up af-specअगरic portion
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/dst.h>
#समावेश <net/xfrm.h>
#समावेश <net/ip.h>
#समावेश <net/l3mdev.h>

अटल काष्ठा dst_entry *__xfrm4_dst_lookup(काष्ठा net *net, काष्ठा flowi4 *fl4,
					    पूर्णांक tos, पूर्णांक oअगर,
					    स्थिर xfrm_address_t *saddr,
					    स्थिर xfrm_address_t *daddr,
					    u32 mark)
अणु
	काष्ठा rtable *rt;

	स_रखो(fl4, 0, माप(*fl4));
	fl4->daddr = daddr->a4;
	fl4->flowi4_tos = tos;
	fl4->flowi4_oअगर = l3mdev_master_अगरindex_by_index(net, oअगर);
	fl4->flowi4_mark = mark;
	अगर (saddr)
		fl4->saddr = saddr->a4;

	fl4->flowi4_flags = FLOWI_FLAG_SKIP_NH_OIF;

	rt = __ip_route_output_key(net, fl4);
	अगर (!IS_ERR(rt))
		वापस &rt->dst;

	वापस ERR_CAST(rt);
पूर्ण

अटल काष्ठा dst_entry *xfrm4_dst_lookup(काष्ठा net *net, पूर्णांक tos, पूर्णांक oअगर,
					  स्थिर xfrm_address_t *saddr,
					  स्थिर xfrm_address_t *daddr,
					  u32 mark)
अणु
	काष्ठा flowi4 fl4;

	वापस __xfrm4_dst_lookup(net, &fl4, tos, oअगर, saddr, daddr, mark);
पूर्ण

अटल पूर्णांक xfrm4_get_saddr(काष्ठा net *net, पूर्णांक oअगर,
			   xfrm_address_t *saddr, xfrm_address_t *daddr,
			   u32 mark)
अणु
	काष्ठा dst_entry *dst;
	काष्ठा flowi4 fl4;

	dst = __xfrm4_dst_lookup(net, &fl4, 0, oअगर, शून्य, daddr, mark);
	अगर (IS_ERR(dst))
		वापस -EHOSTUNREACH;

	saddr->a4 = fl4.saddr;
	dst_release(dst);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm4_fill_dst(काष्ठा xfrm_dst *xdst, काष्ठा net_device *dev,
			  स्थिर काष्ठा flowi *fl)
अणु
	काष्ठा rtable *rt = (काष्ठा rtable *)xdst->route;
	स्थिर काष्ठा flowi4 *fl4 = &fl->u.ip4;

	xdst->u.rt.rt_iअगर = fl4->flowi4_iअगर;

	xdst->u.dst.dev = dev;
	dev_hold(dev);

	/* Sheit... I remember I did this right. Apparently,
	 * it was magically lost, so this code needs audit */
	xdst->u.rt.rt_is_input = rt->rt_is_input;
	xdst->u.rt.rt_flags = rt->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST |
					      RTCF_LOCAL);
	xdst->u.rt.rt_type = rt->rt_type;
	xdst->u.rt.rt_uses_gateway = rt->rt_uses_gateway;
	xdst->u.rt.rt_gw_family = rt->rt_gw_family;
	अगर (rt->rt_gw_family == AF_INET)
		xdst->u.rt.rt_gw4 = rt->rt_gw4;
	अन्यथा अगर (rt->rt_gw_family == AF_INET6)
		xdst->u.rt.rt_gw6 = rt->rt_gw6;
	xdst->u.rt.rt_pmtu = rt->rt_pmtu;
	xdst->u.rt.rt_mtu_locked = rt->rt_mtu_locked;
	INIT_LIST_HEAD(&xdst->u.rt.rt_uncached);
	rt_add_uncached_list(&xdst->u.rt);

	वापस 0;
पूर्ण

अटल व्योम xfrm4_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			      काष्ठा sk_buff *skb, u32 mtu,
			      bool confirm_neigh)
अणु
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;
	काष्ठा dst_entry *path = xdst->route;

	path->ops->update_pmtu(path, sk, skb, mtu, confirm_neigh);
पूर्ण

अटल व्योम xfrm4_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;
	काष्ठा dst_entry *path = xdst->route;

	path->ops->redirect(path, sk, skb);
पूर्ण

अटल व्योम xfrm4_dst_destroy(काष्ठा dst_entry *dst)
अणु
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;

	dst_destroy_metrics_generic(dst);
	अगर (xdst->u.rt.rt_uncached_list)
		rt_del_uncached_list(&xdst->u.rt);
	xfrm_dst_destroy(xdst);
पूर्ण

अटल व्योम xfrm4_dst_अगरकरोwn(काष्ठा dst_entry *dst, काष्ठा net_device *dev,
			     पूर्णांक unरेजिस्टर)
अणु
	अगर (!unरेजिस्टर)
		वापस;

	xfrm_dst_अगरकरोwn(dst, dev);
पूर्ण

अटल काष्ठा dst_ops xfrm4_dst_ops_ढाँचा = अणु
	.family =		AF_INET,
	.update_pmtu =		xfrm4_update_pmtu,
	.redirect =		xfrm4_redirect,
	.cow_metrics =		dst_cow_metrics_generic,
	.destroy =		xfrm4_dst_destroy,
	.अगरकरोwn =		xfrm4_dst_अगरकरोwn,
	.local_out =		__ip_local_out,
	.gc_thresh =		32768,
पूर्ण;

अटल स्थिर काष्ठा xfrm_policy_afinfo xfrm4_policy_afinfo = अणु
	.dst_ops =		&xfrm4_dst_ops_ढाँचा,
	.dst_lookup =		xfrm4_dst_lookup,
	.get_saddr =		xfrm4_get_saddr,
	.fill_dst =		xfrm4_fill_dst,
	.blackhole_route =	ipv4_blackhole_route,
पूर्ण;

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table xfrm4_policy_table[] = अणु
	अणु
		.procname       = "xfrm4_gc_thresh",
		.data           = &init_net.xfrm.xfrm4_dst_ops.gc_thresh,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल __net_init पूर्णांक xfrm4_net_sysctl_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	काष्ठा ctl_table_header *hdr;

	table = xfrm4_policy_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(xfrm4_policy_table), GFP_KERNEL);
		अगर (!table)
			जाओ err_alloc;

		table[0].data = &net->xfrm.xfrm4_dst_ops.gc_thresh;
	पूर्ण

	hdr = रेजिस्टर_net_sysctl(net, "net/ipv4", table);
	अगर (!hdr)
		जाओ err_reg;

	net->ipv4.xfrm4_hdr = hdr;
	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल __net_निकास व्योम xfrm4_net_sysctl_निकास(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	अगर (!net->ipv4.xfrm4_hdr)
		वापस;

	table = net->ipv4.xfrm4_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->ipv4.xfrm4_hdr);
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
पूर्ण
#अन्यथा /* CONFIG_SYSCTL */
अटल अंतरभूत पूर्णांक xfrm4_net_sysctl_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xfrm4_net_sysctl_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init xfrm4_net_init(काष्ठा net *net)
अणु
	पूर्णांक ret;

	स_नकल(&net->xfrm.xfrm4_dst_ops, &xfrm4_dst_ops_ढाँचा,
	       माप(xfrm4_dst_ops_ढाँचा));
	ret = dst_entries_init(&net->xfrm.xfrm4_dst_ops);
	अगर (ret)
		वापस ret;

	ret = xfrm4_net_sysctl_init(net);
	अगर (ret)
		dst_entries_destroy(&net->xfrm.xfrm4_dst_ops);

	वापस ret;
पूर्ण

अटल व्योम __net_निकास xfrm4_net_निकास(काष्ठा net *net)
अणु
	xfrm4_net_sysctl_निकास(net);
	dst_entries_destroy(&net->xfrm.xfrm4_dst_ops);
पूर्ण

अटल काष्ठा pernet_operations __net_initdata xfrm4_net_ops = अणु
	.init	= xfrm4_net_init,
	.निकास	= xfrm4_net_निकास,
पूर्ण;

अटल व्योम __init xfrm4_policy_init(व्योम)
अणु
	xfrm_policy_रेजिस्टर_afinfo(&xfrm4_policy_afinfo, AF_INET);
पूर्ण

व्योम __init xfrm4_init(व्योम)
अणु
	xfrm4_state_init();
	xfrm4_policy_init();
	xfrm4_protocol_init();
	रेजिस्टर_pernet_subsys(&xfrm4_net_ops);
पूर्ण
