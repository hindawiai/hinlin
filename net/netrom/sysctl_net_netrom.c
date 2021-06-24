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
#समावेश <net/netrom.h>

/*
 *	Values taken from NET/ROM करोcumentation.
 */
अटल पूर्णांक min_quality[] = अणु0पूर्ण, max_quality[] = अणु255पूर्ण;
अटल पूर्णांक min_obs[]     = अणु0पूर्ण, max_obs[]     = अणु255पूर्ण;
अटल पूर्णांक min_ttl[]     = अणु0पूर्ण, max_ttl[]     = अणु255पूर्ण;
अटल पूर्णांक min_t1[]      = अणु5 * HZपूर्ण;
अटल पूर्णांक max_t1[]      = अणु600 * HZपूर्ण;
अटल पूर्णांक min_n2[]      = अणु2पूर्ण, max_n2[]      = अणु127पूर्ण;
अटल पूर्णांक min_t2[]      = अणु1 * HZपूर्ण;
अटल पूर्णांक max_t2[]      = अणु60 * HZपूर्ण;
अटल पूर्णांक min_t4[]      = अणु1 * HZपूर्ण;
अटल पूर्णांक max_t4[]      = अणु1000 * HZपूर्ण;
अटल पूर्णांक min_winकरोw[]  = अणु1पूर्ण, max_winकरोw[]  = अणु127पूर्ण;
अटल पूर्णांक min_idle[]    = अणु0 * HZपूर्ण;
अटल पूर्णांक max_idle[]    = अणु65535 * HZपूर्ण;
अटल पूर्णांक min_route[]   = अणु0पूर्ण, max_route[]   = अणु1पूर्ण;
अटल पूर्णांक min_fails[]   = अणु1पूर्ण, max_fails[]   = अणु10पूर्ण;
अटल पूर्णांक min_reset[]   = अणु0पूर्ण, max_reset[]   = अणु1पूर्ण;

अटल काष्ठा ctl_table_header *nr_table_header;

अटल काष्ठा ctl_table nr_table[] = अणु
	अणु
		.procname	= "default_path_quality",
		.data		= &sysctl_netrom_शेष_path_quality,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_quality,
		.extra2		= &max_quality
	पूर्ण,
	अणु
		.procname	= "obsolescence_count_initialiser",
		.data		= &sysctl_netrom_obsolescence_count_initialiser,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_obs,
		.extra2		= &max_obs
	पूर्ण,
	अणु
		.procname	= "network_ttl_initialiser",
		.data		= &sysctl_netrom_network_ttl_initialiser,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_ttl,
		.extra2		= &max_ttl
	पूर्ण,
	अणु
		.procname	= "transport_timeout",
		.data		= &sysctl_netrom_transport_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_t1,
		.extra2		= &max_t1
	पूर्ण,
	अणु
		.procname	= "transport_maximum_tries",
		.data		= &sysctl_netrom_transport_maximum_tries,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_n2,
		.extra2		= &max_n2
	पूर्ण,
	अणु
		.procname	= "transport_acknowledge_delay",
		.data		= &sysctl_netrom_transport_acknowledge_delay,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_t2,
		.extra2		= &max_t2
	पूर्ण,
	अणु
		.procname	= "transport_busy_delay",
		.data		= &sysctl_netrom_transport_busy_delay,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_t4,
		.extra2		= &max_t4
	पूर्ण,
	अणु
		.procname	= "transport_requested_window_size",
		.data		= &sysctl_netrom_transport_requested_winकरोw_size,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_winकरोw,
		.extra2		= &max_winकरोw
	पूर्ण,
	अणु
		.procname	= "transport_no_activity_timeout",
		.data		= &sysctl_netrom_transport_no_activity_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_idle,
		.extra2		= &max_idle
	पूर्ण,
	अणु
		.procname	= "routing_control",
		.data		= &sysctl_netrom_routing_control,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_route,
		.extra2		= &max_route
	पूर्ण,
	अणु
		.procname	= "link_fails_count",
		.data		= &sysctl_netrom_link_fails_count,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_fails,
		.extra2		= &max_fails
	पूर्ण,
	अणु
		.procname	= "reset",
		.data		= &sysctl_netrom_reset_circuit,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_reset,
		.extra2		= &max_reset
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक __init nr_रेजिस्टर_sysctl(व्योम)
अणु
	nr_table_header = रेजिस्टर_net_sysctl(&init_net, "net/netrom", nr_table);
	अगर (!nr_table_header)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम nr_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(nr_table_header);
पूर्ण
