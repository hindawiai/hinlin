<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/stats.c
 *
 * procfs-based user access to generic RPC statistics. The stats files
 * reside in /proc/net/rpc.
 *
 * The पढ़ो routines assume that the buffer passed in is just big enough.
 * If you implement an RPC service that has its own stats routine which
 * appends the generic RPC stats, make sure you करोn't exceed the PAGE_SIZE
 * limit.
 *
 * Copyright (C) 1995, 1996, 1997 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/metrics.h>
#समावेश <linux/rcupdate.h>

#समावेश <trace/events/sunrpc.h>

#समावेश "netns.h"

#घोषणा RPCDBG_FACILITY	RPCDBG_MISC

/*
 * Get RPC client stats
 */
अटल पूर्णांक rpc_proc_show(काष्ठा seq_file *seq, व्योम *v) अणु
	स्थिर काष्ठा rpc_stat	*statp = seq->निजी;
	स्थिर काष्ठा rpc_program *prog = statp->program;
	अचिन्हित पूर्णांक i, j;

	seq_म_लिखो(seq,
		"net %u %u %u %u\n",
			statp->netcnt,
			statp->netudpcnt,
			statp->nettcpcnt,
			statp->nettcpconn);
	seq_म_लिखो(seq,
		"rpc %u %u %u\n",
			statp->rpccnt,
			statp->rpcretrans,
			statp->rpcauthrefresh);

	क्रम (i = 0; i < prog->nrvers; i++) अणु
		स्थिर काष्ठा rpc_version *vers = prog->version[i];
		अगर (!vers)
			जारी;
		seq_म_लिखो(seq, "proc%u %u",
					vers->number, vers->nrprocs);
		क्रम (j = 0; j < vers->nrprocs; j++)
			seq_म_लिखो(seq, " %u", vers->counts[j]);
		seq_अ_दो(seq, '\n');
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rpc_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, rpc_proc_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops rpc_proc_ops = अणु
	.proc_खोलो	= rpc_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

/*
 * Get RPC server stats
 */
व्योम svc_seq_show(काष्ठा seq_file *seq, स्थिर काष्ठा svc_stat *statp)
अणु
	स्थिर काष्ठा svc_program *prog = statp->program;
	स्थिर काष्ठा svc_version *vers;
	अचिन्हित पूर्णांक i, j;

	seq_म_लिखो(seq,
		"net %u %u %u %u\n",
			statp->netcnt,
			statp->netudpcnt,
			statp->nettcpcnt,
			statp->nettcpconn);
	seq_म_लिखो(seq,
		"rpc %u %u %u %u %u\n",
			statp->rpccnt,
			statp->rpcbadfmt+statp->rpcbadauth+statp->rpcbadclnt,
			statp->rpcbadfmt,
			statp->rpcbadauth,
			statp->rpcbadclnt);

	क्रम (i = 0; i < prog->pg_nvers; i++) अणु
		vers = prog->pg_vers[i];
		अगर (!vers)
			जारी;
		seq_म_लिखो(seq, "proc%d %u", i, vers->vs_nproc);
		क्रम (j = 0; j < vers->vs_nproc; j++)
			seq_म_लिखो(seq, " %u", vers->vs_count[j]);
		seq_अ_दो(seq, '\n');
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(svc_seq_show);

/**
 * rpc_alloc_iostats - allocate an rpc_iostats काष्ठाure
 * @clnt: RPC program, version, and xprt
 *
 */
काष्ठा rpc_iostats *rpc_alloc_iostats(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_iostats *stats;
	पूर्णांक i;

	stats = kसुस्मृति(clnt->cl_maxproc, माप(*stats), GFP_KERNEL);
	अगर (stats) अणु
		क्रम (i = 0; i < clnt->cl_maxproc; i++)
			spin_lock_init(&stats[i].om_lock);
	पूर्ण
	वापस stats;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_alloc_iostats);

/**
 * rpc_मुक्त_iostats - release an rpc_iostats काष्ठाure
 * @stats: करोomed rpc_iostats काष्ठाure
 *
 */
व्योम rpc_मुक्त_iostats(काष्ठा rpc_iostats *stats)
अणु
	kमुक्त(stats);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_मुक्त_iostats);

/**
 * rpc_count_iostats_metrics - tally up per-task stats
 * @task: completed rpc_task
 * @op_metrics: stat काष्ठाure क्रम OP that will accumulate stats from @task
 */
व्योम rpc_count_iostats_metrics(स्थिर काष्ठा rpc_task *task,
			       काष्ठा rpc_iostats *op_metrics)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	kसमय_प्रकार backlog, execute, now;

	अगर (!op_metrics || !req)
		वापस;

	now = kसमय_get();
	spin_lock(&op_metrics->om_lock);

	op_metrics->om_ops++;
	/* kernel API: om_ops must never become larger than om_ntrans */
	op_metrics->om_ntrans += max(req->rq_ntrans, 1);
	op_metrics->om_समयouts += task->tk_समयouts;

	op_metrics->om_bytes_sent += req->rq_xmit_bytes_sent;
	op_metrics->om_bytes_recv += req->rq_reply_bytes_recvd;

	backlog = 0;
	अगर (kसमय_प्रकारo_ns(req->rq_xसमय)) अणु
		backlog = kसमय_sub(req->rq_xसमय, task->tk_start);
		op_metrics->om_queue = kसमय_add(op_metrics->om_queue, backlog);
	पूर्ण

	op_metrics->om_rtt = kसमय_add(op_metrics->om_rtt, req->rq_rtt);

	execute = kसमय_sub(now, task->tk_start);
	op_metrics->om_execute = kसमय_add(op_metrics->om_execute, execute);
	अगर (task->tk_status < 0)
		op_metrics->om_error_status++;

	spin_unlock(&op_metrics->om_lock);

	trace_rpc_stats_latency(req->rq_task, backlog, req->rq_rtt, execute);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_count_iostats_metrics);

/**
 * rpc_count_iostats - tally up per-task stats
 * @task: completed rpc_task
 * @stats: array of stat काष्ठाures
 *
 * Uses the statidx from @task
 */
व्योम rpc_count_iostats(स्थिर काष्ठा rpc_task *task, काष्ठा rpc_iostats *stats)
अणु
	rpc_count_iostats_metrics(task,
				  &stats[task->tk_msg.rpc_proc->p_statidx]);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_count_iostats);

अटल व्योम _prपूर्णांक_name(काष्ठा seq_file *seq, अचिन्हित पूर्णांक op,
			स्थिर काष्ठा rpc_procinfo *procs)
अणु
	अगर (procs[op].p_name)
		seq_म_लिखो(seq, "\t%12s: ", procs[op].p_name);
	अन्यथा अगर (op == 0)
		seq_म_लिखो(seq, "\t        NULL: ");
	अन्यथा
		seq_म_लिखो(seq, "\t%12u: ", op);
पूर्ण

अटल व्योम _add_rpc_iostats(काष्ठा rpc_iostats *a, काष्ठा rpc_iostats *b)
अणु
	a->om_ops += b->om_ops;
	a->om_ntrans += b->om_ntrans;
	a->om_समयouts += b->om_समयouts;
	a->om_bytes_sent += b->om_bytes_sent;
	a->om_bytes_recv += b->om_bytes_recv;
	a->om_queue = kसमय_add(a->om_queue, b->om_queue);
	a->om_rtt = kसमय_add(a->om_rtt, b->om_rtt);
	a->om_execute = kसमय_add(a->om_execute, b->om_execute);
	a->om_error_status += b->om_error_status;
पूर्ण

अटल व्योम _prपूर्णांक_rpc_iostats(काष्ठा seq_file *seq, काष्ठा rpc_iostats *stats,
			       पूर्णांक op, स्थिर काष्ठा rpc_procinfo *procs)
अणु
	_prपूर्णांक_name(seq, op, procs);
	seq_म_लिखो(seq, "%lu %lu %lu %llu %llu %llu %llu %llu %lu\n",
		   stats->om_ops,
		   stats->om_ntrans,
		   stats->om_समयouts,
		   stats->om_bytes_sent,
		   stats->om_bytes_recv,
		   kसमय_प्रकारo_ms(stats->om_queue),
		   kसमय_प्रकारo_ms(stats->om_rtt),
		   kसमय_प्रकारo_ms(stats->om_execute),
		   stats->om_error_status);
पूर्ण

अटल पूर्णांक करो_prपूर्णांक_stats(काष्ठा rpc_clnt *clnt, काष्ठा rpc_xprt *xprt, व्योम *seqv)
अणु
	काष्ठा seq_file *seq = seqv;

	xprt->ops->prपूर्णांक_stats(xprt, seq);
	वापस 0;
पूर्ण

व्योम rpc_clnt_show_stats(काष्ठा seq_file *seq, काष्ठा rpc_clnt *clnt)
अणु
	अचिन्हित पूर्णांक op, maxproc = clnt->cl_maxproc;

	अगर (!clnt->cl_metrics)
		वापस;

	seq_म_लिखो(seq, "\tRPC iostats version: %s  ", RPC_IOSTATS_VERS);
	seq_म_लिखो(seq, "p/v: %u/%u (%s)\n",
			clnt->cl_prog, clnt->cl_vers, clnt->cl_program->name);

	rpc_clnt_iterate_क्रम_each_xprt(clnt, करो_prपूर्णांक_stats, seq);

	seq_म_लिखो(seq, "\tper-op statistics\n");
	क्रम (op = 0; op < maxproc; op++) अणु
		काष्ठा rpc_iostats stats = अणुपूर्ण;
		काष्ठा rpc_clnt *next = clnt;
		करो अणु
			_add_rpc_iostats(&stats, &next->cl_metrics[op]);
			अगर (next == next->cl_parent)
				अवरोध;
			next = next->cl_parent;
		पूर्ण जबतक (next);
		_prपूर्णांक_rpc_iostats(seq, &stats, op, clnt->cl_procinfo);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_show_stats);

/*
 * Register/unरेजिस्टर RPC proc files
 */
अटल अंतरभूत काष्ठा proc_dir_entry *
करो_रेजिस्टर(काष्ठा net *net, स्थिर अक्षर *name, व्योम *data,
	    स्थिर काष्ठा proc_ops *proc_ops)
अणु
	काष्ठा sunrpc_net *sn;

	dprपूर्णांकk("RPC:       registering /proc/net/rpc/%s\n", name);
	sn = net_generic(net, sunrpc_net_id);
	वापस proc_create_data(name, 0, sn->proc_net_rpc, proc_ops, data);
पूर्ण

काष्ठा proc_dir_entry *
rpc_proc_रेजिस्टर(काष्ठा net *net, काष्ठा rpc_stat *statp)
अणु
	वापस करो_रेजिस्टर(net, statp->program->name, statp, &rpc_proc_ops);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_proc_रेजिस्टर);

व्योम
rpc_proc_unरेजिस्टर(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा sunrpc_net *sn;

	sn = net_generic(net, sunrpc_net_id);
	हटाओ_proc_entry(name, sn->proc_net_rpc);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_proc_unरेजिस्टर);

काष्ठा proc_dir_entry *
svc_proc_रेजिस्टर(काष्ठा net *net, काष्ठा svc_stat *statp, स्थिर काष्ठा proc_ops *proc_ops)
अणु
	वापस करो_रेजिस्टर(net, statp->program->pg_name, statp, proc_ops);
पूर्ण
EXPORT_SYMBOL_GPL(svc_proc_रेजिस्टर);

व्योम
svc_proc_unरेजिस्टर(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा sunrpc_net *sn;

	sn = net_generic(net, sunrpc_net_id);
	हटाओ_proc_entry(name, sn->proc_net_rpc);
पूर्ण
EXPORT_SYMBOL_GPL(svc_proc_unरेजिस्टर);

पूर्णांक rpc_proc_init(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn;

	dprपूर्णांकk("RPC:       registering /proc/net/rpc\n");
	sn = net_generic(net, sunrpc_net_id);
	sn->proc_net_rpc = proc_सूची_गढ़ो("rpc", net->proc_net);
	अगर (sn->proc_net_rpc == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम rpc_proc_निकास(काष्ठा net *net)
अणु
	dprपूर्णांकk("RPC:       unregistering /proc/net/rpc\n");
	हटाओ_proc_entry("rpc", net->proc_net);
पूर्ण
