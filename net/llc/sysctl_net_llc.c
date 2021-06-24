<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sysctl_net_llc.c: sysctl पूर्णांकerface to LLC net subप्रणाली.
 *
 * Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <net/net_namespace.h>
#समावेश <net/llc.h>

#अगर_अघोषित CONFIG_SYSCTL
#त्रुटि This file should not be compiled without CONFIG_SYSCTL defined
#पूर्ण_अगर

अटल काष्ठा ctl_table llc2_समयout_table[] = अणु
	अणु
		.procname	= "ack",
		.data		= &sysctl_llc2_ack_समयout,
		.maxlen		= माप(sysctl_llc2_ack_समयout),
		.mode		= 0644,
		.proc_handler   = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "busy",
		.data		= &sysctl_llc2_busy_समयout,
		.maxlen		= माप(sysctl_llc2_busy_समयout),
		.mode		= 0644,
		.proc_handler   = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "p",
		.data		= &sysctl_llc2_p_समयout,
		.maxlen		= माप(sysctl_llc2_p_समयout),
		.mode		= 0644,
		.proc_handler   = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "rej",
		.data		= &sysctl_llc2_rej_समयout,
		.maxlen		= माप(sysctl_llc2_rej_समयout),
		.mode		= 0644,
		.proc_handler   = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table llc_station_table[] = अणु
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table_header *llc2_समयout_header;
अटल काष्ठा ctl_table_header *llc_station_header;

पूर्णांक __init llc_sysctl_init(व्योम)
अणु
	llc2_समयout_header = रेजिस्टर_net_sysctl(&init_net, "net/llc/llc2/timeout", llc2_समयout_table);
	llc_station_header = रेजिस्टर_net_sysctl(&init_net, "net/llc/station", llc_station_table);

	अगर (!llc2_समयout_header || !llc_station_header) अणु
		llc_sysctl_निकास();
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम llc_sysctl_निकास(व्योम)
अणु
	अगर (llc2_समयout_header) अणु
		unरेजिस्टर_net_sysctl_table(llc2_समयout_header);
		llc2_समयout_header = शून्य;
	पूर्ण
	अगर (llc_station_header) अणु
		unरेजिस्टर_net_sysctl_table(llc_station_header);
		llc_station_header = शून्य;
	पूर्ण
पूर्ण
