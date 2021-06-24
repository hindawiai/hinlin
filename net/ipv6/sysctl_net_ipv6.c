<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sysctl_net_ipv6.c: sysctl पूर्णांकerface to net IPV6 subप्रणाली.
 *
 * Changes:
 * YOSHIFUJI Hideaki @USAGI:	added icmp sysctl table.
 */

#समावेश <linux/mm.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/in6.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/ndisc.h>
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <net/inet_frag.h>
#समावेश <net/netevent.h>
#अगर_घोषित CONFIG_NETLABEL
#समावेश <net/calipso.h>
#पूर्ण_अगर

अटल पूर्णांक two = 2;
अटल पूर्णांक flowlabel_reflect_max = 0x7;
अटल पूर्णांक स्वतः_flowlabels_max = IP6_AUTO_FLOW_LABEL_MAX;

अटल पूर्णांक proc_rt6_multipath_hash_policy(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
					  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net;
	पूर्णांक ret;

	net = container_of(table->data, काष्ठा net,
			   ipv6.sysctl.multipath_hash_policy);
	ret = proc_करोu8vec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0)
		call_netevent_notअगरiers(NETEVENT_IPV6_MPATH_HASH_UPDATE, net);

	वापस ret;
पूर्ण

अटल काष्ठा ctl_table ipv6_table_ढाँचा[] = अणु
	अणु
		.procname	= "bindv6only",
		.data		= &init_net.ipv6.sysctl.bindv6only,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "anycast_src_echo_reply",
		.data		= &init_net.ipv6.sysctl.anycast_src_echo_reply,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "flowlabel_consistency",
		.data		= &init_net.ipv6.sysctl.flowlabel_consistency,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "auto_flowlabels",
		.data		= &init_net.ipv6.sysctl.स्वतः_flowlabels,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra2		= &स्वतः_flowlabels_max
	पूर्ण,
	अणु
		.procname	= "fwmark_reflect",
		.data		= &init_net.ipv6.sysctl.fwmark_reflect,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "idgen_retries",
		.data		= &init_net.ipv6.sysctl.idgen_retries,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "idgen_delay",
		.data		= &init_net.ipv6.sysctl.idgen_delay,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "flowlabel_state_ranges",
		.data		= &init_net.ipv6.sysctl.flowlabel_state_ranges,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip_nonlocal_bind",
		.data		= &init_net.ipv6.sysctl.ip_nonlocal_bind,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "flowlabel_reflect",
		.data		= &init_net.ipv6.sysctl.flowlabel_reflect,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &flowlabel_reflect_max,
	पूर्ण,
	अणु
		.procname	= "max_dst_opts_number",
		.data		= &init_net.ipv6.sysctl.max_dst_opts_cnt,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "max_hbh_opts_number",
		.data		= &init_net.ipv6.sysctl.max_hbh_opts_cnt,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "max_dst_opts_length",
		.data		= &init_net.ipv6.sysctl.max_dst_opts_len,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "max_hbh_length",
		.data		= &init_net.ipv6.sysctl.max_hbh_opts_len,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "fib_multipath_hash_policy",
		.data		= &init_net.ipv6.sysctl.multipath_hash_policy,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler   = proc_rt6_multipath_hash_policy,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "seg6_flowlabel",
		.data		= &init_net.ipv6.sysctl.seg6_flowlabel,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "fib_notify_on_flag_change",
		.data		= &init_net.ipv6.sysctl.fib_notअगरy_on_flag_change,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = &two,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table ipv6_rotable[] = अणु
	अणु
		.procname	= "mld_max_msf",
		.data		= &sysctl_mld_max_msf,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "mld_qrv",
		.data		= &sysctl_mld_qrv,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE
	पूर्ण,
#अगर_घोषित CONFIG_NETLABEL
	अणु
		.procname	= "calipso_cache_enable",
		.data		= &calipso_cache_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "calipso_cache_bucket_size",
		.data		= &calipso_cache_bucketsize,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NETLABEL */
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __net_init ipv6_sysctl_net_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *ipv6_table;
	काष्ठा ctl_table *ipv6_route_table;
	काष्ठा ctl_table *ipv6_icmp_table;
	पूर्णांक err, i;

	err = -ENOMEM;
	ipv6_table = kmemdup(ipv6_table_ढाँचा, माप(ipv6_table_ढाँचा),
			     GFP_KERNEL);
	अगर (!ipv6_table)
		जाओ out;
	/* Update the variables to poपूर्णांक पूर्णांकo the current काष्ठा net */
	क्रम (i = 0; i < ARRAY_SIZE(ipv6_table_ढाँचा) - 1; i++)
		ipv6_table[i].data += (व्योम *)net - (व्योम *)&init_net;

	ipv6_route_table = ipv6_route_sysctl_init(net);
	अगर (!ipv6_route_table)
		जाओ out_ipv6_table;

	ipv6_icmp_table = ipv6_icmp_sysctl_init(net);
	अगर (!ipv6_icmp_table)
		जाओ out_ipv6_route_table;

	net->ipv6.sysctl.hdr = रेजिस्टर_net_sysctl(net, "net/ipv6", ipv6_table);
	अगर (!net->ipv6.sysctl.hdr)
		जाओ out_ipv6_icmp_table;

	net->ipv6.sysctl.route_hdr =
		रेजिस्टर_net_sysctl(net, "net/ipv6/route", ipv6_route_table);
	अगर (!net->ipv6.sysctl.route_hdr)
		जाओ out_unरेजिस्टर_ipv6_table;

	net->ipv6.sysctl.icmp_hdr =
		रेजिस्टर_net_sysctl(net, "net/ipv6/icmp", ipv6_icmp_table);
	अगर (!net->ipv6.sysctl.icmp_hdr)
		जाओ out_unरेजिस्टर_route_table;

	err = 0;
out:
	वापस err;
out_unरेजिस्टर_route_table:
	unरेजिस्टर_net_sysctl_table(net->ipv6.sysctl.route_hdr);
out_unरेजिस्टर_ipv6_table:
	unरेजिस्टर_net_sysctl_table(net->ipv6.sysctl.hdr);
out_ipv6_icmp_table:
	kमुक्त(ipv6_icmp_table);
out_ipv6_route_table:
	kमुक्त(ipv6_route_table);
out_ipv6_table:
	kमुक्त(ipv6_table);
	जाओ out;
पूर्ण

अटल व्योम __net_निकास ipv6_sysctl_net_निकास(काष्ठा net *net)
अणु
	काष्ठा ctl_table *ipv6_table;
	काष्ठा ctl_table *ipv6_route_table;
	काष्ठा ctl_table *ipv6_icmp_table;

	ipv6_table = net->ipv6.sysctl.hdr->ctl_table_arg;
	ipv6_route_table = net->ipv6.sysctl.route_hdr->ctl_table_arg;
	ipv6_icmp_table = net->ipv6.sysctl.icmp_hdr->ctl_table_arg;

	unरेजिस्टर_net_sysctl_table(net->ipv6.sysctl.icmp_hdr);
	unरेजिस्टर_net_sysctl_table(net->ipv6.sysctl.route_hdr);
	unरेजिस्टर_net_sysctl_table(net->ipv6.sysctl.hdr);

	kमुक्त(ipv6_table);
	kमुक्त(ipv6_route_table);
	kमुक्त(ipv6_icmp_table);
पूर्ण

अटल काष्ठा pernet_operations ipv6_sysctl_net_ops = अणु
	.init = ipv6_sysctl_net_init,
	.निकास = ipv6_sysctl_net_निकास,
पूर्ण;

अटल काष्ठा ctl_table_header *ip6_header;

पूर्णांक ipv6_sysctl_रेजिस्टर(व्योम)
अणु
	पूर्णांक err = -ENOMEM;

	ip6_header = रेजिस्टर_net_sysctl(&init_net, "net/ipv6", ipv6_rotable);
	अगर (!ip6_header)
		जाओ out;

	err = रेजिस्टर_pernet_subsys(&ipv6_sysctl_net_ops);
	अगर (err)
		जाओ err_pernet;
out:
	वापस err;

err_pernet:
	unरेजिस्टर_net_sysctl_table(ip6_header);
	जाओ out;
पूर्ण

व्योम ipv6_sysctl_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(ip6_header);
	unरेजिस्टर_pernet_subsys(&ipv6_sysctl_net_ops);
पूर्ण
