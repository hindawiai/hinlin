<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sysctl_net_atalk.c: sysctl पूर्णांकerface to net AppleTalk subप्रणाली.
 *
 * Begun April 1, 1996, Mike Shaver.
 * Added /proc/sys/net/atalk directory entry (empty =) ). [MS]
 * Dynamic registration, added aarp entries. (5/30/97 Chris Horn)
 */

#समावेश <linux/sysctl.h>
#समावेश <net/sock.h>
#समावेश <linux/atalk.h>

अटल काष्ठा ctl_table atalk_table[] = अणु
	अणु
		.procname	= "aarp-expiry-time",
		.data		= &sysctl_aarp_expiry_समय,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "aarp-tick-time",
		.data		= &sysctl_aarp_tick_समय,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "aarp-retransmit-limit",
		.data		= &sysctl_aarp_retransmit_limit,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "aarp-resolve-time",
		.data		= &sysctl_aarp_resolve_समय,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table_header *atalk_table_header;

पूर्णांक __init atalk_रेजिस्टर_sysctl(व्योम)
अणु
	atalk_table_header = रेजिस्टर_net_sysctl(&init_net, "net/appletalk", atalk_table);
	अगर (!atalk_table_header)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम atalk_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(atalk_table_header);
पूर्ण
