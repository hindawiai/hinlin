<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 1996 Mike Shaver (shaver@zeroknowledge.com)
 */
#समावेश <linux/mm.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/init.h>
#समावेश <net/ax25.h>
#समावेश <net/rose.h>

अटल पूर्णांक min_समयr[]  = अणु1 * HZपूर्ण;
अटल पूर्णांक max_समयr[]  = अणु300 * HZपूर्ण;
अटल पूर्णांक min_idle[]   = अणु0 * HZपूर्ण;
अटल पूर्णांक max_idle[]   = अणु65535 * HZपूर्ण;
अटल पूर्णांक min_route[1],       max_route[] = अणु1पूर्ण;
अटल पूर्णांक min_fसमयr[] = अणु60 * HZपूर्ण;
अटल पूर्णांक max_fसमयr[] = अणु600 * HZपूर्ण;
अटल पूर्णांक min_maxvcs[] = अणु1पूर्ण, max_maxvcs[] = अणु254पूर्ण;
अटल पूर्णांक min_winकरोw[] = अणु1पूर्ण, max_winकरोw[] = अणु7पूर्ण;

अटल काष्ठा ctl_table_header *rose_table_header;

अटल काष्ठा ctl_table rose_table[] = अणु
	अणु
		.procname	= "restart_request_timeout",
		.data		= &sysctl_rose_restart_request_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_समयr,
		.extra2		= &max_समयr
	पूर्ण,
	अणु
		.procname	= "call_request_timeout",
		.data		= &sysctl_rose_call_request_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_समयr,
		.extra2		= &max_समयr
	पूर्ण,
	अणु
		.procname	= "reset_request_timeout",
		.data		= &sysctl_rose_reset_request_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_समयr,
		.extra2		= &max_समयr
	पूर्ण,
	अणु
		.procname	= "clear_request_timeout",
		.data		= &sysctl_rose_clear_request_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_समयr,
		.extra2		= &max_समयr
	पूर्ण,
	अणु
		.procname	= "no_activity_timeout",
		.data		= &sysctl_rose_no_activity_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_idle,
		.extra2		= &max_idle
	पूर्ण,
	अणु
		.procname	= "acknowledge_hold_back_timeout",
		.data		= &sysctl_rose_ack_hold_back_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_समयr,
		.extra2		= &max_समयr
	पूर्ण,
	अणु
		.procname	= "routing_control",
		.data		= &sysctl_rose_routing_control,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_route,
		.extra2		= &max_route
	पूर्ण,
	अणु
		.procname	= "link_fail_timeout",
		.data		= &sysctl_rose_link_fail_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_fसमयr,
		.extra2		= &max_fसमयr
	पूर्ण,
	अणु
		.procname	= "maximum_virtual_circuits",
		.data		= &sysctl_rose_maximum_vcs,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_maxvcs,
		.extra2		= &max_maxvcs
	पूर्ण,
	अणु
		.procname	= "window_size",
		.data		= &sysctl_rose_winकरोw_size,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_winकरोw,
		.extra2		= &max_winकरोw
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम __init rose_रेजिस्टर_sysctl(व्योम)
अणु
	rose_table_header = रेजिस्टर_net_sysctl(&init_net, "net/rose", rose_table);
पूर्ण

व्योम rose_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(rose_table_header);
पूर्ण
