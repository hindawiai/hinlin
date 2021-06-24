<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/sysctl.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <net/xfrm.h>

अटल व्योम __net_init __xfrm_sysctl_init(काष्ठा net *net)
अणु
	net->xfrm.sysctl_aevent_eसमय = XFRM_AE_ETIME;
	net->xfrm.sysctl_aevent_rseqth = XFRM_AE_SEQT_SIZE;
	net->xfrm.sysctl_larval_drop = 1;
	net->xfrm.sysctl_acq_expires = 30;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table xfrm_table[] = अणु
	अणु
		.procname	= "xfrm_aevent_etime",
		.maxlen		= माप(u32),
		.mode		= 0644,
		.proc_handler	= proc_करोuपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "xfrm_aevent_rseqth",
		.maxlen		= माप(u32),
		.mode		= 0644,
		.proc_handler	= proc_करोuपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "xfrm_larval_drop",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "xfrm_acq_expires",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक __net_init xfrm_sysctl_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	__xfrm_sysctl_init(net);

	table = kmemdup(xfrm_table, माप(xfrm_table), GFP_KERNEL);
	अगर (!table)
		जाओ out_kmemdup;
	table[0].data = &net->xfrm.sysctl_aevent_eसमय;
	table[1].data = &net->xfrm.sysctl_aevent_rseqth;
	table[2].data = &net->xfrm.sysctl_larval_drop;
	table[3].data = &net->xfrm.sysctl_acq_expires;

	/* Don't export sysctls to unprivileged users */
	अगर (net->user_ns != &init_user_ns)
		table[0].procname = शून्य;

	net->xfrm.sysctl_hdr = रेजिस्टर_net_sysctl(net, "net/core", table);
	अगर (!net->xfrm.sysctl_hdr)
		जाओ out_रेजिस्टर;
	वापस 0;

out_रेजिस्टर:
	kमुक्त(table);
out_kmemdup:
	वापस -ENOMEM;
पूर्ण

व्योम __net_निकास xfrm_sysctl_fini(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = net->xfrm.sysctl_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->xfrm.sysctl_hdr);
	kमुक्त(table);
पूर्ण
#अन्यथा
पूर्णांक __net_init xfrm_sysctl_init(काष्ठा net *net)
अणु
	__xfrm_sysctl_init(net);
	वापस 0;
पूर्ण
#पूर्ण_अगर
