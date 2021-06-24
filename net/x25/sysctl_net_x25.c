<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* -*- linux-c -*-
 * sysctl_net_x25.c: sysctl पूर्णांकerface to net X.25 subप्रणाली.
 *
 * Begun April 1, 1996, Mike Shaver.
 * Added /proc/sys/net/x25 directory entry (empty =) ). [MS]
 */

#समावेश <linux/sysctl.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <net/x25.h>

अटल पूर्णांक min_समयr[] = अणु   1 * HZ पूर्ण;
अटल पूर्णांक max_समयr[] = अणु 300 * HZ पूर्ण;

अटल काष्ठा ctl_table_header *x25_table_header;

अटल काष्ठा ctl_table x25_table[] = अणु
	अणु
		.procname =	"restart_request_timeout",
		.data =		&sysctl_x25_restart_request_समयout,
		.maxlen =	माप(पूर्णांक),
		.mode =		0644,
		.proc_handler =	proc_करोपूर्णांकvec_minmax,
		.extra1 =	&min_समयr,
		.extra2 =	&max_समयr,
	पूर्ण,
	अणु
		.procname =	"call_request_timeout",
		.data =		&sysctl_x25_call_request_समयout,
		.maxlen =	माप(पूर्णांक),
		.mode =		0644,
		.proc_handler =	proc_करोपूर्णांकvec_minmax,
		.extra1 =	&min_समयr,
		.extra2 =	&max_समयr,
	पूर्ण,
	अणु
		.procname =	"reset_request_timeout",
		.data =		&sysctl_x25_reset_request_समयout,
		.maxlen =	माप(पूर्णांक),
		.mode =		0644,
		.proc_handler =	proc_करोपूर्णांकvec_minmax,
		.extra1 =	&min_समयr,
		.extra2 =	&max_समयr,
	पूर्ण,
	अणु
		.procname =	"clear_request_timeout",
		.data =		&sysctl_x25_clear_request_समयout,
		.maxlen =	माप(पूर्णांक),
		.mode =		0644,
		.proc_handler =	proc_करोपूर्णांकvec_minmax,
		.extra1 =	&min_समयr,
		.extra2 =	&max_समयr,
	पूर्ण,
	अणु
		.procname =	"acknowledgement_hold_back_timeout",
		.data =		&sysctl_x25_ack_holdback_समयout,
		.maxlen =	माप(पूर्णांक),
		.mode =		0644,
		.proc_handler =	proc_करोपूर्णांकvec_minmax,
		.extra1 =	&min_समयr,
		.extra2 =	&max_समयr,
	पूर्ण,
	अणु
		.procname =	"x25_forward",
		.data = 	&sysctl_x25_क्रमward,
		.maxlen = 	माप(पूर्णांक),
		.mode = 	0644,
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

पूर्णांक __init x25_रेजिस्टर_sysctl(व्योम)
अणु
	x25_table_header = रेजिस्टर_net_sysctl(&init_net, "net/x25", x25_table);
	अगर (!x25_table_header)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम x25_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(x25_table_header);
पूर्ण
