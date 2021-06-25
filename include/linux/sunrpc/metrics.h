<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/sunrpc/metrics.h
 *
 *  Declarations क्रम RPC client per-operation metrics
 *
 *  Copyright (C) 2005	Chuck Lever <cel@netapp.com>
 *
 *  RPC client per-operation statistics provide latency and retry
 *  inक्रमmation about each type of RPC procedure in a given RPC program.
 *  These statistics are not क्रम detailed problem diagnosis, but simply
 *  to indicate whether the problem is local or remote.
 *
 *  These counters are not meant to be human-पढ़ोable, but are meant to be
 *  पूर्णांकegrated पूर्णांकo प्रणाली monitoring tools such as "sar" and "iostat".  As
 *  such, the counters are sampled by the tools over समय, and are never
 *  zeroed after a file प्रणाली is mounted.  Moving averages can be computed
 *  by the tools by taking the dअगरference between two instantaneous samples
 *  and भागiding that by the समय between the samples.
 *
 *  The counters are मुख्यtained in a single array per RPC client, indexed
 *  by procedure number.  There is no need to मुख्यtain separate counter
 *  arrays per-CPU because these counters are always modअगरied behind locks.
 */

#अगर_अघोषित _LINUX_SUNRPC_METRICS_H
#घोषणा _LINUX_SUNRPC_METRICS_H

#समावेश <linux/seq_file.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/spinlock.h>

#घोषणा RPC_IOSTATS_VERS	"1.1"

काष्ठा rpc_iostats अणु
	spinlock_t		om_lock;

	/*
	 * These counters give an idea about how many request
	 * transmissions are required, on average, to complete that
	 * particular procedure.  Some procedures may require more
	 * than one transmission because the server is unresponsive,
	 * the client is retransmitting too aggressively, or the
	 * requests are large and the network is congested.
	 */
	अचिन्हित दीर्घ		om_ops,		/* count of operations */
				om_ntrans,	/* count of RPC transmissions */
				om_समयouts;	/* count of major समयouts */

	/*
	 * These count how many bytes are sent and received क्रम a
	 * given RPC procedure type.  This indicates how much load a
	 * particular procedure is putting on the network.  These
	 * counts include the RPC and ULP headers, and the request
	 * payload.
	 */
	अचिन्हित दीर्घ दीर्घ      om_bytes_sent,	/* count of bytes out */
				om_bytes_recv;	/* count of bytes in */

	/*
	 * The length of समय an RPC request रुकोs in queue beक्रमe
	 * transmission, the network + server latency of the request,
	 * and the total समय the request spent from init to release
	 * are measured.
	 */
	kसमय_प्रकार			om_queue,	/* queued क्रम xmit */
				om_rtt,		/* RPC RTT */
				om_execute;	/* RPC execution */
	/*
	 * The count of operations that complete with tk_status < 0.
	 * These statuses usually indicate error conditions.
	 */
	अचिन्हित दीर्घ           om_error_status;
पूर्ण ____cacheline_aligned;

काष्ठा rpc_task;
काष्ठा rpc_clnt;

/*
 * EXPORTed functions क्रम managing rpc_iostats काष्ठाures
 */

#अगर_घोषित CONFIG_PROC_FS

काष्ठा rpc_iostats *	rpc_alloc_iostats(काष्ठा rpc_clnt *);
व्योम			rpc_count_iostats(स्थिर काष्ठा rpc_task *,
					  काष्ठा rpc_iostats *);
व्योम			rpc_count_iostats_metrics(स्थिर काष्ठा rpc_task *,
					  काष्ठा rpc_iostats *);
व्योम			rpc_clnt_show_stats(काष्ठा seq_file *, काष्ठा rpc_clnt *);
व्योम			rpc_मुक्त_iostats(काष्ठा rpc_iostats *);

#अन्यथा  /*  CONFIG_PROC_FS  */

अटल अंतरभूत काष्ठा rpc_iostats *rpc_alloc_iostats(काष्ठा rpc_clnt *clnt) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम rpc_count_iostats(स्थिर काष्ठा rpc_task *task,
				     काष्ठा rpc_iostats *stats) अणुपूर्ण
अटल अंतरभूत व्योम rpc_count_iostats_metrics(स्थिर काष्ठा rpc_task *task,
					     काष्ठा rpc_iostats *stats)
अणु
पूर्ण

अटल अंतरभूत व्योम rpc_clnt_show_stats(काष्ठा seq_file *seq, काष्ठा rpc_clnt *clnt) अणुपूर्ण
अटल अंतरभूत व्योम rpc_मुक्त_iostats(काष्ठा rpc_iostats *stats) अणुपूर्ण

#पूर्ण_अगर  /*  CONFIG_PROC_FS  */

#पूर्ण_अगर /* _LINUX_SUNRPC_METRICS_H */
