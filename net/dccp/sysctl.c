<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  net/dccp/sysctl.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@mandriva.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/sysctl.h>
#समावेश "dccp.h"
#समावेश "feat.h"

#अगर_अघोषित CONFIG_SYSCTL
#त्रुटि This file should not be compiled without CONFIG_SYSCTL defined
#पूर्ण_अगर

/* Boundary values */
अटल पूर्णांक		u8_max   = 0xFF;
अटल अचिन्हित दीर्घ	seqw_min = DCCPF_SEQ_WMIN,
			seqw_max = 0xFFFFFFFF;		/* maximum on 32 bit */

अटल काष्ठा ctl_table dccp_शेष_table[] = अणु
	अणु
		.procname	= "seq_window",
		.data		= &sysctl_dccp_sequence_winकरोw,
		.maxlen		= माप(sysctl_dccp_sequence_winकरोw),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
		.extra1		= &seqw_min,		/* RFC 4340, 7.5.2 */
		.extra2		= &seqw_max,
	पूर्ण,
	अणु
		.procname	= "rx_ccid",
		.data		= &sysctl_dccp_rx_ccid,
		.maxlen		= माप(sysctl_dccp_rx_ccid),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &u8_max,		/* RFC 4340, 10. */
	पूर्ण,
	अणु
		.procname	= "tx_ccid",
		.data		= &sysctl_dccp_tx_ccid,
		.maxlen		= माप(sysctl_dccp_tx_ccid),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &u8_max,		/* RFC 4340, 10. */
	पूर्ण,
	अणु
		.procname	= "request_retries",
		.data		= &sysctl_dccp_request_retries,
		.maxlen		= माप(sysctl_dccp_request_retries),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= &u8_max,
	पूर्ण,
	अणु
		.procname	= "retries1",
		.data		= &sysctl_dccp_retries1,
		.maxlen		= माप(sysctl_dccp_retries1),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &u8_max,
	पूर्ण,
	अणु
		.procname	= "retries2",
		.data		= &sysctl_dccp_retries2,
		.maxlen		= माप(sysctl_dccp_retries2),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &u8_max,
	पूर्ण,
	अणु
		.procname	= "tx_qlen",
		.data		= &sysctl_dccp_tx_qlen,
		.maxlen		= माप(sysctl_dccp_tx_qlen),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "sync_ratelimit",
		.data		= &sysctl_dccp_sync_ratelimit,
		.maxlen		= माप(sysctl_dccp_sync_ratelimit),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,

	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *dccp_table_header;

पूर्णांक __init dccp_sysctl_init(व्योम)
अणु
	dccp_table_header = रेजिस्टर_net_sysctl(&init_net, "net/dccp/default",
			dccp_शेष_table);

	वापस dccp_table_header != शून्य ? 0 : -ENOMEM;
पूर्ण

व्योम dccp_sysctl_निकास(व्योम)
अणु
	अगर (dccp_table_header != शून्य) अणु
		unरेजिस्टर_net_sysctl_table(dccp_table_header);
		dccp_table_header = शून्य;
	पूर्ण
पूर्ण
