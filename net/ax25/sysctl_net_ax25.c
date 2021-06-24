<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 1996 Mike Shaver (shaver@zeroknowledge.com)
 */
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/spinlock.h>
#समावेश <net/ax25.h>

अटल पूर्णांक min_ipdeभ_शेषe[1],    	max_ipdeभ_शेषe[] = अणु1पूर्ण;
अटल पूर्णांक min_axdeभ_शेषe[1],            max_axdeभ_शेषe[] = अणु1पूर्ण;
अटल पूर्णांक min_backoff[1],		max_backoff[] = अणु2पूर्ण;
अटल पूर्णांक min_conmode[1],		max_conmode[] = अणु2पूर्ण;
अटल पूर्णांक min_winकरोw[] = अणु1पूर्ण,		max_winकरोw[] = अणु7पूर्ण;
अटल पूर्णांक min_ewinकरोw[] = अणु1पूर्ण,		max_ewinकरोw[] = अणु63पूर्ण;
अटल पूर्णांक min_t1[] = अणु1पूर्ण,		max_t1[] = अणु30000पूर्ण;
अटल पूर्णांक min_t2[] = अणु1पूर्ण,		max_t2[] = अणु20000पूर्ण;
अटल पूर्णांक min_t3[1],			max_t3[] = अणु3600000पूर्ण;
अटल पूर्णांक min_idle[1],			max_idle[] = अणु65535000पूर्ण;
अटल पूर्णांक min_n2[] = अणु1पूर्ण,		max_n2[] = अणु31पूर्ण;
अटल पूर्णांक min_paclen[] = अणु1पूर्ण,		max_paclen[] = अणु512पूर्ण;
अटल पूर्णांक min_proto[1],		max_proto[] = अणु AX25_PROTO_MAX पूर्ण;
#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
अटल पूर्णांक min_ds_समयout[1],		max_ds_समयout[] = अणु65535000पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा ctl_table ax25_param_table[] = अणु
	अणु
		.procname	= "ip_default_mode",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_ipdeभ_शेषe,
		.extra2		= &max_ipdeभ_शेषe
	पूर्ण,
	अणु
		.procname	= "ax25_default_mode",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_axdeभ_शेषe,
		.extra2		= &max_axdeभ_शेषe
	पूर्ण,
	अणु
		.procname	= "backoff_type",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_backoff,
		.extra2		= &max_backoff
	पूर्ण,
	अणु
		.procname	= "connect_mode",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_conmode,
		.extra2		= &max_conmode
	पूर्ण,
	अणु
		.procname	= "standard_window_size",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_winकरोw,
		.extra2		= &max_winकरोw
	पूर्ण,
	अणु
		.procname	= "extended_window_size",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_ewinकरोw,
		.extra2		= &max_ewinकरोw
	पूर्ण,
	अणु
		.procname	= "t1_timeout",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_t1,
		.extra2		= &max_t1
	पूर्ण,
	अणु
		.procname	= "t2_timeout",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_t2,
		.extra2		= &max_t2
	पूर्ण,
	अणु
		.procname	= "t3_timeout",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_t3,
		.extra2		= &max_t3
	पूर्ण,
	अणु
		.procname	= "idle_timeout",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_idle,
		.extra2		= &max_idle
	पूर्ण,
	अणु
		.procname	= "maximum_retry_count",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_n2,
		.extra2		= &max_n2
	पूर्ण,
	अणु
		.procname	= "maximum_packet_length",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_paclen,
		.extra2		= &max_paclen
	पूर्ण,
	अणु
		.procname	= "protocol",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_proto,
		.extra2		= &max_proto
	पूर्ण,
#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	अणु
		.procname	= "dama_slave_timeout",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_ds_समयout,
		.extra2		= &max_ds_समयout
	पूर्ण,
#पूर्ण_अगर

	अणु पूर्ण	/* that's all, folks! */
पूर्ण;

पूर्णांक ax25_रेजिस्टर_dev_sysctl(ax25_dev *ax25_dev)
अणु
	अक्षर path[माप("net/ax25/") + IFNAMSIZ];
	पूर्णांक k;
	काष्ठा ctl_table *table;

	table = kmemdup(ax25_param_table, माप(ax25_param_table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	क्रम (k = 0; k < AX25_MAX_VALUES; k++)
		table[k].data = &ax25_dev->values[k];

	snम_लिखो(path, माप(path), "net/ax25/%s", ax25_dev->dev->name);
	ax25_dev->sysheader = रेजिस्टर_net_sysctl(&init_net, path, table);
	अगर (!ax25_dev->sysheader) अणु
		kमुक्त(table);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम ax25_unरेजिस्टर_dev_sysctl(ax25_dev *ax25_dev)
अणु
	काष्ठा ctl_table_header *header = ax25_dev->sysheader;
	काष्ठा ctl_table *table;

	अगर (header) अणु
		ax25_dev->sysheader = शून्य;
		table = header->ctl_table_arg;
		unरेजिस्टर_net_sysctl_table(header);
		kमुक्त(table);
	पूर्ण
पूर्ण
