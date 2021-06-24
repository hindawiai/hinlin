<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2019, Tessares SA.
 */

#समावेश <linux/sysctl.h>

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश "protocol.h"

#घोषणा MPTCP_SYSCTL_PATH "net/mptcp"

अटल पूर्णांक mptcp_pernet_id;
काष्ठा mptcp_pernet अणु
	काष्ठा ctl_table_header *ctl_table_hdr;

	पूर्णांक mptcp_enabled;
	अचिन्हित पूर्णांक add_addr_समयout;
पूर्ण;

अटल काष्ठा mptcp_pernet *mptcp_get_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, mptcp_pernet_id);
पूर्ण

पूर्णांक mptcp_is_enabled(काष्ठा net *net)
अणु
	वापस mptcp_get_pernet(net)->mptcp_enabled;
पूर्ण

अचिन्हित पूर्णांक mptcp_get_add_addr_समयout(काष्ठा net *net)
अणु
	वापस mptcp_get_pernet(net)->add_addr_समयout;
पूर्ण

अटल काष्ठा ctl_table mptcp_sysctl_table[] = अणु
	अणु
		.procname = "enabled",
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		/* users with CAP_NET_ADMIN or root (not and) can change this
		 * value, same as other sysctl or the 'net' tree.
		 */
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname = "add_addr_timeout",
		.maxlen = माप(अचिन्हित पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम mptcp_pernet_set_शेषs(काष्ठा mptcp_pernet *pernet)
अणु
	pernet->mptcp_enabled = 1;
	pernet->add_addr_समयout = TCP_RTO_MAX;
पूर्ण

अटल पूर्णांक mptcp_pernet_new_table(काष्ठा net *net, काष्ठा mptcp_pernet *pernet)
अणु
	काष्ठा ctl_table_header *hdr;
	काष्ठा ctl_table *table;

	table = mptcp_sysctl_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(mptcp_sysctl_table), GFP_KERNEL);
		अगर (!table)
			जाओ err_alloc;
	पूर्ण

	table[0].data = &pernet->mptcp_enabled;
	table[1].data = &pernet->add_addr_समयout;

	hdr = रेजिस्टर_net_sysctl(net, MPTCP_SYSCTL_PATH, table);
	अगर (!hdr)
		जाओ err_reg;

	pernet->ctl_table_hdr = hdr;

	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल व्योम mptcp_pernet_del_table(काष्ठा mptcp_pernet *pernet)
अणु
	काष्ठा ctl_table *table = pernet->ctl_table_hdr->ctl_table_arg;

	unरेजिस्टर_net_sysctl_table(pernet->ctl_table_hdr);

	kमुक्त(table);
पूर्ण

अटल पूर्णांक __net_init mptcp_net_init(काष्ठा net *net)
अणु
	काष्ठा mptcp_pernet *pernet = mptcp_get_pernet(net);

	mptcp_pernet_set_शेषs(pernet);

	वापस mptcp_pernet_new_table(net, pernet);
पूर्ण

/* Note: the callback will only be called per extra netns */
अटल व्योम __net_निकास mptcp_net_निकास(काष्ठा net *net)
अणु
	काष्ठा mptcp_pernet *pernet = mptcp_get_pernet(net);

	mptcp_pernet_del_table(pernet);
पूर्ण

अटल काष्ठा pernet_operations mptcp_pernet_ops = अणु
	.init = mptcp_net_init,
	.निकास = mptcp_net_निकास,
	.id = &mptcp_pernet_id,
	.size = माप(काष्ठा mptcp_pernet),
पूर्ण;

व्योम __init mptcp_init(व्योम)
अणु
	mptcp_join_cookie_init();
	mptcp_proto_init();

	अगर (रेजिस्टर_pernet_subsys(&mptcp_pernet_ops) < 0)
		panic("Failed to register MPTCP pernet subsystem.\n");
पूर्ण

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
पूर्णांक __init mptcpv6_init(व्योम)
अणु
	पूर्णांक err;

	err = mptcp_proto_v6_init();

	वापस err;
पूर्ण
#पूर्ण_अगर
