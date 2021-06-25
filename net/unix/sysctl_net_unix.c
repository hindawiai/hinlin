<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NET4:	Sysctl पूर्णांकerface to net af_unix subप्रणाली.
 *
 * Authors:	Mike Shaver.
 */

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>

#समावेश <net/af_unix.h>

अटल काष्ठा ctl_table unix_table[] = अणु
	अणु
		.procname	= "max_dgram_qlen",
		.data		= &init_net.unx.sysctl_max_dgram_qlen,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक __net_init unix_sysctl_रेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = kmemdup(unix_table, माप(unix_table), GFP_KERNEL);
	अगर (table == शून्य)
		जाओ err_alloc;

	/* Don't export sysctls to unprivileged users */
	अगर (net->user_ns != &init_user_ns)
		table[0].procname = शून्य;

	table[0].data = &net->unx.sysctl_max_dgram_qlen;
	net->unx.ctl = रेजिस्टर_net_sysctl(net, "net/unix", table);
	अगर (net->unx.ctl == शून्य)
		जाओ err_reg;

	वापस 0;

err_reg:
	kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

व्योम unix_sysctl_unरेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = net->unx.ctl->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->unx.ctl);
	kमुक्त(table);
पूर्ण
