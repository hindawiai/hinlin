<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* sysctls क्रम configuring RxRPC operating parameters
 *
 * Copyright (C) 2014 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/sysctl.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

अटल काष्ठा ctl_table_header *rxrpc_sysctl_reg_table;
अटल स्थिर अचिन्हित पूर्णांक four = 4;
अटल स्थिर अचिन्हित पूर्णांक thirtytwo = 32;
अटल स्थिर अचिन्हित पूर्णांक n_65535 = 65535;
अटल स्थिर अचिन्हित पूर्णांक n_max_acks = RXRPC_RXTX_BUFF_SIZE - 1;
अटल स्थिर अचिन्हित दीर्घ one_jअगरfy = 1;
अटल स्थिर अचिन्हित दीर्घ max_jअगरfies = MAX_JIFFY_OFFSET;

/*
 * RxRPC operating parameters.
 *
 * See Documentation/networking/rxrpc.rst and the variable definitions क्रम more
 * inक्रमmation on the inभागidual parameters.
 */
अटल काष्ठा ctl_table rxrpc_sysctl_table[] = अणु
	/* Values measured in milliseconds but used in jअगरfies */
	अणु
		.procname	= "req_ack_delay",
		.data		= &rxrpc_requested_ack_delay,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_ms_jअगरfies_minmax,
		.extra1		= (व्योम *)&one_jअगरfy,
		.extra2		= (व्योम *)&max_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "soft_ack_delay",
		.data		= &rxrpc_soft_ack_delay,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_ms_jअगरfies_minmax,
		.extra1		= (व्योम *)&one_jअगरfy,
		.extra2		= (व्योम *)&max_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "idle_ack_delay",
		.data		= &rxrpc_idle_ack_delay,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_ms_jअगरfies_minmax,
		.extra1		= (व्योम *)&one_jअगरfy,
		.extra2		= (व्योम *)&max_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "idle_conn_expiry",
		.data		= &rxrpc_conn_idle_client_expiry,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_ms_jअगरfies_minmax,
		.extra1		= (व्योम *)&one_jअगरfy,
		.extra2		= (व्योम *)&max_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "idle_conn_fast_expiry",
		.data		= &rxrpc_conn_idle_client_fast_expiry,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_ms_jअगरfies_minmax,
		.extra1		= (व्योम *)&one_jअगरfy,
		.extra2		= (व्योम *)&max_jअगरfies,
	पूर्ण,

	/* Non-समय values */
	अणु
		.procname	= "reap_client_conns",
		.data		= &rxrpc_reap_client_connections,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)SYSCTL_ONE,
		.extra2		= (व्योम *)&n_65535,
	पूर्ण,
	अणु
		.procname	= "max_backlog",
		.data		= &rxrpc_max_backlog,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)&four,
		.extra2		= (व्योम *)&thirtytwo,
	पूर्ण,
	अणु
		.procname	= "rx_window_size",
		.data		= &rxrpc_rx_winकरोw_size,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)SYSCTL_ONE,
		.extra2		= (व्योम *)&n_max_acks,
	पूर्ण,
	अणु
		.procname	= "rx_mtu",
		.data		= &rxrpc_rx_mtu,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)SYSCTL_ONE,
		.extra2		= (व्योम *)&n_65535,
	पूर्ण,
	अणु
		.procname	= "rx_jumbo_max",
		.data		= &rxrpc_rx_jumbo_max,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)SYSCTL_ONE,
		.extra2		= (व्योम *)&four,
	पूर्ण,

	अणु पूर्ण
पूर्ण;

पूर्णांक __init rxrpc_sysctl_init(व्योम)
अणु
	rxrpc_sysctl_reg_table = रेजिस्टर_net_sysctl(&init_net, "net/rxrpc",
						     rxrpc_sysctl_table);
	अगर (!rxrpc_sysctl_reg_table)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम rxrpc_sysctl_निकास(व्योम)
अणु
	अगर (rxrpc_sysctl_reg_table)
		unरेजिस्टर_net_sysctl_table(rxrpc_sysctl_reg_table);
पूर्ण
