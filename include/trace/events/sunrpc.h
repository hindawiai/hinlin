<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM sunrpc

#अगर !defined(_TRACE_SUNRPC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SUNRPC_H

#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/xprtsock.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/net.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_DEFINE_ENUM(SOCK_STREAM);
TRACE_DEFINE_ENUM(SOCK_DGRAM);
TRACE_DEFINE_ENUM(SOCK_RAW);
TRACE_DEFINE_ENUM(SOCK_RDM);
TRACE_DEFINE_ENUM(SOCK_SEQPACKET);
TRACE_DEFINE_ENUM(SOCK_DCCP);
TRACE_DEFINE_ENUM(SOCK_PACKET);

#घोषणा show_socket_type(type)					\
	__prपूर्णांक_symbolic(type,					\
		अणु SOCK_STREAM,		"STREAM" पूर्ण,		\
		अणु SOCK_DGRAM,		"DGRAM" पूर्ण,		\
		अणु SOCK_RAW,		"RAW" पूर्ण,		\
		अणु SOCK_RDM,		"RDM" पूर्ण,		\
		अणु SOCK_SEQPACKET,	"SEQPACKET" पूर्ण,		\
		अणु SOCK_DCCP,		"DCCP" पूर्ण,		\
		अणु SOCK_PACKET,		"PACKET" पूर्ण)

/* This list is known to be incomplete, add new क्रमागतs as needed. */
TRACE_DEFINE_ENUM(AF_UNSPEC);
TRACE_DEFINE_ENUM(AF_UNIX);
TRACE_DEFINE_ENUM(AF_LOCAL);
TRACE_DEFINE_ENUM(AF_INET);
TRACE_DEFINE_ENUM(AF_INET6);

#घोषणा rpc_show_address_family(family)				\
	__prपूर्णांक_symbolic(family,				\
		अणु AF_UNSPEC,		"AF_UNSPEC" पूर्ण,		\
		अणु AF_UNIX,		"AF_UNIX" पूर्ण,		\
		अणु AF_LOCAL,		"AF_LOCAL" पूर्ण,		\
		अणु AF_INET,		"AF_INET" पूर्ण,		\
		अणु AF_INET6,		"AF_INET6" पूर्ण)

DECLARE_EVENT_CLASS(rpc_xdr_buf_class,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		स्थिर काष्ठा xdr_buf *xdr
	),

	TP_ARGS(task, xdr),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(स्थिर व्योम *, head_base)
		__field(माप_प्रकार, head_len)
		__field(स्थिर व्योम *, tail_base)
		__field(माप_प्रकार, tail_len)
		__field(अचिन्हित पूर्णांक, page_len)
		__field(अचिन्हित पूर्णांक, msg_len)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client ?
				     task->tk_client->cl_clid : -1;
		__entry->head_base = xdr->head[0].iov_base;
		__entry->head_len = xdr->head[0].iov_len;
		__entry->tail_base = xdr->tail[0].iov_base;
		__entry->tail_len = xdr->tail[0].iov_len;
		__entry->page_len = xdr->page_len;
		__entry->msg_len = xdr->len;
	),

	TP_prपूर्णांकk("task:%u@%u head=[%p,%zu] page=%u tail=[%p,%zu] len=%u",
		__entry->task_id, __entry->client_id,
		__entry->head_base, __entry->head_len, __entry->page_len,
		__entry->tail_base, __entry->tail_len, __entry->msg_len
	)
);

#घोषणा DEFINE_RPCXDRBUF_EVENT(name)					\
		DEFINE_EVENT(rpc_xdr_buf_class,				\
				rpc_xdr_##name,				\
				TP_PROTO(				\
					स्थिर काष्ठा rpc_task *task,	\
					स्थिर काष्ठा xdr_buf *xdr	\
				),					\
				TP_ARGS(task, xdr))

DEFINE_RPCXDRBUF_EVENT(sendto);
DEFINE_RPCXDRBUF_EVENT(recvfrom);
DEFINE_RPCXDRBUF_EVENT(reply_pages);


DECLARE_EVENT_CLASS(rpc_clnt_class,
	TP_PROTO(
		स्थिर काष्ठा rpc_clnt *clnt
	),

	TP_ARGS(clnt),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, client_id)
	),

	TP_fast_assign(
		__entry->client_id = clnt->cl_clid;
	),

	TP_prपूर्णांकk("clid=%u", __entry->client_id)
);

#घोषणा DEFINE_RPC_CLNT_EVENT(name)					\
		DEFINE_EVENT(rpc_clnt_class,				\
				rpc_clnt_##name,			\
				TP_PROTO(				\
					स्थिर काष्ठा rpc_clnt *clnt	\
				),					\
				TP_ARGS(clnt))

DEFINE_RPC_CLNT_EVENT(मुक्त);
DEFINE_RPC_CLNT_EVENT(समाप्तall);
DEFINE_RPC_CLNT_EVENT(shutकरोwn);
DEFINE_RPC_CLNT_EVENT(release);
DEFINE_RPC_CLNT_EVENT(replace_xprt);
DEFINE_RPC_CLNT_EVENT(replace_xprt_err);

TRACE_EVENT(rpc_clnt_new,
	TP_PROTO(
		स्थिर काष्ठा rpc_clnt *clnt,
		स्थिर काष्ठा rpc_xprt *xprt,
		स्थिर अक्षर *program,
		स्थिर अक्षर *server
	),

	TP_ARGS(clnt, xprt, program, server),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, client_id)
		__string(addr, xprt->address_strings[RPC_DISPLAY_ADDR])
		__string(port, xprt->address_strings[RPC_DISPLAY_PORT])
		__string(program, program)
		__string(server, server)
	),

	TP_fast_assign(
		__entry->client_id = clnt->cl_clid;
		__assign_str(addr, xprt->address_strings[RPC_DISPLAY_ADDR]);
		__assign_str(port, xprt->address_strings[RPC_DISPLAY_PORT]);
		__assign_str(program, program)
		__assign_str(server, server)
	),

	TP_prपूर्णांकk("client=%u peer=[%s]:%s program=%s server=%s",
		__entry->client_id, __get_str(addr), __get_str(port),
		__get_str(program), __get_str(server))
);

TRACE_EVENT(rpc_clnt_new_err,
	TP_PROTO(
		स्थिर अक्षर *program,
		स्थिर अक्षर *server,
		पूर्णांक error
	),

	TP_ARGS(program, server, error),

	TP_STRUCT__entry(
		__field(पूर्णांक, error)
		__string(program, program)
		__string(server, server)
	),

	TP_fast_assign(
		__entry->error = error;
		__assign_str(program, program)
		__assign_str(server, server)
	),

	TP_prपूर्णांकk("program=%s server=%s error=%d",
		__get_str(program), __get_str(server), __entry->error)
);

TRACE_EVENT(rpc_clnt_clone_err,
	TP_PROTO(
		स्थिर काष्ठा rpc_clnt *clnt,
		पूर्णांक error
	),

	TP_ARGS(clnt, error),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, error)
	),

	TP_fast_assign(
		__entry->client_id = clnt->cl_clid;
		__entry->error = error;
	),

	TP_prपूर्णांकk("client=%u error=%d", __entry->client_id, __entry->error)
);


TRACE_DEFINE_ENUM(RPC_AUTH_OK);
TRACE_DEFINE_ENUM(RPC_AUTH_BADCRED);
TRACE_DEFINE_ENUM(RPC_AUTH_REJECTEDCRED);
TRACE_DEFINE_ENUM(RPC_AUTH_BADVERF);
TRACE_DEFINE_ENUM(RPC_AUTH_REJECTEDVERF);
TRACE_DEFINE_ENUM(RPC_AUTH_TOOWEAK);
TRACE_DEFINE_ENUM(RPCSEC_GSS_CREDPROBLEM);
TRACE_DEFINE_ENUM(RPCSEC_GSS_CTXPROBLEM);

#घोषणा rpc_show_auth_stat(status)					\
	__prपूर्णांक_symbolic(status,					\
		अणु RPC_AUTH_OK,			"AUTH_OK" पूर्ण,		\
		अणु RPC_AUTH_BADCRED,		"BADCRED" पूर्ण,		\
		अणु RPC_AUTH_REJECTEDCRED,	"REJECTEDCRED" पूर्ण,	\
		अणु RPC_AUTH_BADVERF,		"BADVERF" पूर्ण,		\
		अणु RPC_AUTH_REJECTEDVERF,	"REJECTEDVERF" पूर्ण,	\
		अणु RPC_AUTH_TOOWEAK,		"TOOWEAK" पूर्ण,		\
		अणु RPCSEC_GSS_CREDPROBLEM,	"GSS_CREDPROBLEM" पूर्ण,	\
		अणु RPCSEC_GSS_CTXPROBLEM,	"GSS_CTXPROBLEM" पूर्ण)	\

DECLARE_EVENT_CLASS(rpc_task_status,

	TP_PROTO(स्थिर काष्ठा rpc_task *task),

	TP_ARGS(task),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->status = task->tk_status;
	),

	TP_prपूर्णांकk("task:%u@%u status=%d",
		__entry->task_id, __entry->client_id,
		__entry->status)
);
#घोषणा DEFINE_RPC_STATUS_EVENT(name) \
	DEFINE_EVENT(rpc_task_status, rpc_##name##_status, \
			TP_PROTO( \
				स्थिर काष्ठा rpc_task *task \
			), \
			TP_ARGS(task))

DEFINE_RPC_STATUS_EVENT(call);
DEFINE_RPC_STATUS_EVENT(connect);
DEFINE_RPC_STATUS_EVENT(समयout);
DEFINE_RPC_STATUS_EVENT(retry_refresh);
DEFINE_RPC_STATUS_EVENT(refresh);

TRACE_EVENT(rpc_request,
	TP_PROTO(स्थिर काष्ठा rpc_task *task),

	TP_ARGS(task),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, version)
		__field(bool, async)
		__string(progname, task->tk_client->cl_program->name)
		__string(procname, rpc_proc_name(task))
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->version = task->tk_client->cl_vers;
		__entry->async = RPC_IS_ASYNC(task);
		__assign_str(progname, task->tk_client->cl_program->name)
		__assign_str(procname, rpc_proc_name(task))
	),

	TP_prपूर्णांकk("task:%u@%u %sv%d %s (%ssync)",
		__entry->task_id, __entry->client_id,
		__get_str(progname), __entry->version,
		__get_str(procname), __entry->async ? "a": ""
		)
);

TRACE_DEFINE_ENUM(RPC_TASK_ASYNC);
TRACE_DEFINE_ENUM(RPC_TASK_SWAPPER);
TRACE_DEFINE_ENUM(RPC_TASK_शून्यCREDS);
TRACE_DEFINE_ENUM(RPC_CALL_MAJORSEEN);
TRACE_DEFINE_ENUM(RPC_TASK_ROOTCREDS);
TRACE_DEFINE_ENUM(RPC_TASK_DYNAMIC);
TRACE_DEFINE_ENUM(RPC_TASK_NO_ROUND_ROBIN);
TRACE_DEFINE_ENUM(RPC_TASK_SOFT);
TRACE_DEFINE_ENUM(RPC_TASK_SOFTCONN);
TRACE_DEFINE_ENUM(RPC_TASK_SENT);
TRACE_DEFINE_ENUM(RPC_TASK_TIMEOUT);
TRACE_DEFINE_ENUM(RPC_TASK_NOCONNECT);
TRACE_DEFINE_ENUM(RPC_TASK_NO_RETRANS_TIMEOUT);
TRACE_DEFINE_ENUM(RPC_TASK_CRED_NOREF);

#घोषणा rpc_show_task_flags(flags)					\
	__prपूर्णांक_flags(flags, "|",					\
		अणु RPC_TASK_ASYNC, "ASYNC" पूर्ण,				\
		अणु RPC_TASK_SWAPPER, "SWAPPER" पूर्ण,			\
		अणु RPC_TASK_शून्यCREDS, "NULLCREDS" पूर्ण,			\
		अणु RPC_CALL_MAJORSEEN, "MAJORSEEN" पूर्ण,			\
		अणु RPC_TASK_ROOTCREDS, "ROOTCREDS" पूर्ण,			\
		अणु RPC_TASK_DYNAMIC, "DYNAMIC" पूर्ण,			\
		अणु RPC_TASK_NO_ROUND_ROBIN, "NO_ROUND_ROBIN" पूर्ण,		\
		अणु RPC_TASK_SOFT, "SOFT" पूर्ण,				\
		अणु RPC_TASK_SOFTCONN, "SOFTCONN" पूर्ण,			\
		अणु RPC_TASK_SENT, "SENT" पूर्ण,				\
		अणु RPC_TASK_TIMEOUT, "TIMEOUT" पूर्ण,			\
		अणु RPC_TASK_NOCONNECT, "NOCONNECT" पूर्ण,			\
		अणु RPC_TASK_NO_RETRANS_TIMEOUT, "NORTO" पूर्ण,		\
		अणु RPC_TASK_CRED_NOREF, "CRED_NOREF" पूर्ण)

TRACE_DEFINE_ENUM(RPC_TASK_RUNNING);
TRACE_DEFINE_ENUM(RPC_TASK_QUEUED);
TRACE_DEFINE_ENUM(RPC_TASK_ACTIVE);
TRACE_DEFINE_ENUM(RPC_TASK_NEED_XMIT);
TRACE_DEFINE_ENUM(RPC_TASK_NEED_RECV);
TRACE_DEFINE_ENUM(RPC_TASK_MSG_PIN_WAIT);
TRACE_DEFINE_ENUM(RPC_TASK_SIGNALLED);

#घोषणा rpc_show_runstate(flags)					\
	__prपूर्णांक_flags(flags, "|",					\
		अणु (1UL << RPC_TASK_RUNNING), "RUNNING" पूर्ण,		\
		अणु (1UL << RPC_TASK_QUEUED), "QUEUED" पूर्ण,			\
		अणु (1UL << RPC_TASK_ACTIVE), "ACTIVE" पूर्ण,			\
		अणु (1UL << RPC_TASK_NEED_XMIT), "NEED_XMIT" पूर्ण,		\
		अणु (1UL << RPC_TASK_NEED_RECV), "NEED_RECV" पूर्ण,		\
		अणु (1UL << RPC_TASK_MSG_PIN_WAIT), "MSG_PIN_WAIT" पूर्ण,	\
		अणु (1UL << RPC_TASK_SIGNALLED), "SIGNALLED" पूर्ण)

DECLARE_EVENT_CLASS(rpc_task_running,

	TP_PROTO(स्थिर काष्ठा rpc_task *task, स्थिर व्योम *action),

	TP_ARGS(task, action),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(स्थिर व्योम *, action)
		__field(अचिन्हित दीर्घ, runstate)
		__field(पूर्णांक, status)
		__field(अचिन्हित लघु, flags)
		),

	TP_fast_assign(
		__entry->client_id = task->tk_client ?
				     task->tk_client->cl_clid : -1;
		__entry->task_id = task->tk_pid;
		__entry->action = action;
		__entry->runstate = task->tk_runstate;
		__entry->status = task->tk_status;
		__entry->flags = task->tk_flags;
		),

	TP_prपूर्णांकk("task:%u@%d flags=%s runstate=%s status=%d action=%ps",
		__entry->task_id, __entry->client_id,
		rpc_show_task_flags(__entry->flags),
		rpc_show_runstate(__entry->runstate),
		__entry->status,
		__entry->action
		)
);
#घोषणा DEFINE_RPC_RUNNING_EVENT(name) \
	DEFINE_EVENT(rpc_task_running, rpc_task_##name, \
			TP_PROTO( \
				स्थिर काष्ठा rpc_task *task, \
				स्थिर व्योम *action \
			), \
			TP_ARGS(task, action))

DEFINE_RPC_RUNNING_EVENT(begin);
DEFINE_RPC_RUNNING_EVENT(run_action);
DEFINE_RPC_RUNNING_EVENT(sync_sleep);
DEFINE_RPC_RUNNING_EVENT(sync_wake);
DEFINE_RPC_RUNNING_EVENT(complete);
DEFINE_RPC_RUNNING_EVENT(समयout);
DEFINE_RPC_RUNNING_EVENT(संकेतled);
DEFINE_RPC_RUNNING_EVENT(end);

DECLARE_EVENT_CLASS(rpc_task_queued,

	TP_PROTO(स्थिर काष्ठा rpc_task *task, स्थिर काष्ठा rpc_रुको_queue *q),

	TP_ARGS(task, q),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(अचिन्हित दीर्घ, समयout)
		__field(अचिन्हित दीर्घ, runstate)
		__field(पूर्णांक, status)
		__field(अचिन्हित लघु, flags)
		__string(q_name, rpc_qname(q))
		),

	TP_fast_assign(
		__entry->client_id = task->tk_client ?
				     task->tk_client->cl_clid : -1;
		__entry->task_id = task->tk_pid;
		__entry->समयout = rpc_task_समयout(task);
		__entry->runstate = task->tk_runstate;
		__entry->status = task->tk_status;
		__entry->flags = task->tk_flags;
		__assign_str(q_name, rpc_qname(q));
		),

	TP_prपूर्णांकk("task:%u@%d flags=%s runstate=%s status=%d timeout=%lu queue=%s",
		__entry->task_id, __entry->client_id,
		rpc_show_task_flags(__entry->flags),
		rpc_show_runstate(__entry->runstate),
		__entry->status,
		__entry->समयout,
		__get_str(q_name)
		)
);
#घोषणा DEFINE_RPC_QUEUED_EVENT(name) \
	DEFINE_EVENT(rpc_task_queued, rpc_task_##name, \
			TP_PROTO( \
				स्थिर काष्ठा rpc_task *task, \
				स्थिर काष्ठा rpc_रुको_queue *q \
			), \
			TP_ARGS(task, q))

DEFINE_RPC_QUEUED_EVENT(sleep);
DEFINE_RPC_QUEUED_EVENT(wakeup);

DECLARE_EVENT_CLASS(rpc_failure,

	TP_PROTO(स्थिर काष्ठा rpc_task *task),

	TP_ARGS(task),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
	),

	TP_prपूर्णांकk("task:%u@%u",
		__entry->task_id, __entry->client_id)
);

#घोषणा DEFINE_RPC_FAILURE(name)					\
	DEFINE_EVENT(rpc_failure, rpc_bad_##name,			\
			TP_PROTO(					\
				स्थिर काष्ठा rpc_task *task		\
			),						\
			TP_ARGS(task))

DEFINE_RPC_FAILURE(callhdr);
DEFINE_RPC_FAILURE(verअगरier);

DECLARE_EVENT_CLASS(rpc_reply_event,

	TP_PROTO(
		स्थिर काष्ठा rpc_task *task
	),

	TP_ARGS(task),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__string(progname, task->tk_client->cl_program->name)
		__field(u32, version)
		__string(procname, rpc_proc_name(task))
		__string(servername, task->tk_xprt->servername)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(task->tk_rqstp->rq_xid);
		__assign_str(progname, task->tk_client->cl_program->name)
		__entry->version = task->tk_client->cl_vers;
		__assign_str(procname, rpc_proc_name(task))
		__assign_str(servername, task->tk_xprt->servername)
	),

	TP_prपूर्णांकk("task:%u@%d server=%s xid=0x%08x %sv%d %s",
		__entry->task_id, __entry->client_id, __get_str(servername),
		__entry->xid, __get_str(progname), __entry->version,
		__get_str(procname))
)

#घोषणा DEFINE_RPC_REPLY_EVENT(name)					\
	DEFINE_EVENT(rpc_reply_event, rpc__##name,			\
			TP_PROTO(					\
				स्थिर काष्ठा rpc_task *task		\
			),						\
			TP_ARGS(task))

DEFINE_RPC_REPLY_EVENT(prog_unavail);
DEFINE_RPC_REPLY_EVENT(prog_mismatch);
DEFINE_RPC_REPLY_EVENT(proc_unavail);
DEFINE_RPC_REPLY_EVENT(garbage_args);
DEFINE_RPC_REPLY_EVENT(unparsable);
DEFINE_RPC_REPLY_EVENT(mismatch);
DEFINE_RPC_REPLY_EVENT(stale_creds);
DEFINE_RPC_REPLY_EVENT(bad_creds);
DEFINE_RPC_REPLY_EVENT(auth_tooweak);

#घोषणा DEFINE_RPCB_ERROR_EVENT(name)					\
	DEFINE_EVENT(rpc_reply_event, rpcb_##name##_err,		\
			TP_PROTO(					\
				स्थिर काष्ठा rpc_task *task		\
			),						\
			TP_ARGS(task))

DEFINE_RPCB_ERROR_EVENT(prog_unavail);
DEFINE_RPCB_ERROR_EVENT(समयout);
DEFINE_RPCB_ERROR_EVENT(bind_version);
DEFINE_RPCB_ERROR_EVENT(unreachable);
DEFINE_RPCB_ERROR_EVENT(unrecognized);

TRACE_EVENT(rpc_buf_alloc,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		पूर्णांक status
	),

	TP_ARGS(task, status),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(माप_प्रकार, callsize)
		__field(माप_प्रकार, recvsize)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->callsize = task->tk_rqstp->rq_callsize;
		__entry->recvsize = task->tk_rqstp->rq_rcvsize;
		__entry->status = status;
	),

	TP_prपूर्णांकk("task:%u@%u callsize=%zu recvsize=%zu status=%d",
		__entry->task_id, __entry->client_id,
		__entry->callsize, __entry->recvsize, __entry->status
	)
);

TRACE_EVENT(rpc_call_rpcerror,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		पूर्णांक tk_status,
		पूर्णांक rpc_status
	),

	TP_ARGS(task, tk_status, rpc_status),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, tk_status)
		__field(पूर्णांक, rpc_status)
	),

	TP_fast_assign(
		__entry->client_id = task->tk_client->cl_clid;
		__entry->task_id = task->tk_pid;
		__entry->tk_status = tk_status;
		__entry->rpc_status = rpc_status;
	),

	TP_prपूर्णांकk("task:%u@%u tk_status=%d rpc_status=%d",
		__entry->task_id, __entry->client_id,
		__entry->tk_status, __entry->rpc_status)
);

TRACE_EVENT(rpc_stats_latency,

	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		kसमय_प्रकार backlog,
		kसमय_प्रकार rtt,
		kसमय_प्रकार execute
	),

	TP_ARGS(task, backlog, rtt, execute),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(पूर्णांक, version)
		__string(progname, task->tk_client->cl_program->name)
		__string(procname, rpc_proc_name(task))
		__field(अचिन्हित दीर्घ, backlog)
		__field(अचिन्हित दीर्घ, rtt)
		__field(अचिन्हित दीर्घ, execute)
	),

	TP_fast_assign(
		__entry->client_id = task->tk_client->cl_clid;
		__entry->task_id = task->tk_pid;
		__entry->xid = be32_to_cpu(task->tk_rqstp->rq_xid);
		__entry->version = task->tk_client->cl_vers;
		__assign_str(progname, task->tk_client->cl_program->name)
		__assign_str(procname, rpc_proc_name(task))
		__entry->backlog = kसमय_प्रकारo_us(backlog);
		__entry->rtt = kसमय_प्रकारo_us(rtt);
		__entry->execute = kसमय_प्रकारo_us(execute);
	),

	TP_prपूर्णांकk("task:%u@%d xid=0x%08x %sv%d %s backlog=%lu rtt=%lu execute=%lu",
		__entry->task_id, __entry->client_id, __entry->xid,
		__get_str(progname), __entry->version, __get_str(procname),
		__entry->backlog, __entry->rtt, __entry->execute)
);

TRACE_EVENT(rpc_xdr_overflow,
	TP_PROTO(
		स्थिर काष्ठा xdr_stream *xdr,
		माप_प्रकार requested
	),

	TP_ARGS(xdr, requested),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, version)
		__field(माप_प्रकार, requested)
		__field(स्थिर व्योम *, end)
		__field(स्थिर व्योम *, p)
		__field(स्थिर व्योम *, head_base)
		__field(माप_प्रकार, head_len)
		__field(स्थिर व्योम *, tail_base)
		__field(माप_प्रकार, tail_len)
		__field(अचिन्हित पूर्णांक, page_len)
		__field(अचिन्हित पूर्णांक, len)
		__string(progname, xdr->rqst ?
			 xdr->rqst->rq_task->tk_client->cl_program->name : "unknown")
		__string(procedure, xdr->rqst ?
			 xdr->rqst->rq_task->tk_msg.rpc_proc->p_name : "unknown")
	),

	TP_fast_assign(
		अगर (xdr->rqst) अणु
			स्थिर काष्ठा rpc_task *task = xdr->rqst->rq_task;

			__entry->task_id = task->tk_pid;
			__entry->client_id = task->tk_client->cl_clid;
			__assign_str(progname,
				     task->tk_client->cl_program->name)
			__entry->version = task->tk_client->cl_vers;
			__assign_str(procedure, task->tk_msg.rpc_proc->p_name)
		पूर्ण अन्यथा अणु
			__entry->task_id = 0;
			__entry->client_id = 0;
			__assign_str(progname, "unknown")
			__entry->version = 0;
			__assign_str(procedure, "unknown")
		पूर्ण
		__entry->requested = requested;
		__entry->end = xdr->end;
		__entry->p = xdr->p;
		__entry->head_base = xdr->buf->head[0].iov_base,
		__entry->head_len = xdr->buf->head[0].iov_len,
		__entry->page_len = xdr->buf->page_len,
		__entry->tail_base = xdr->buf->tail[0].iov_base,
		__entry->tail_len = xdr->buf->tail[0].iov_len,
		__entry->len = xdr->buf->len;
	),

	TP_prपूर्णांकk(
		"task:%u@%u %sv%d %s requested=%zu p=%p end=%p xdr=[%p,%zu]/%u/[%p,%zu]/%u\n",
		__entry->task_id, __entry->client_id,
		__get_str(progname), __entry->version, __get_str(procedure),
		__entry->requested, __entry->p, __entry->end,
		__entry->head_base, __entry->head_len,
		__entry->page_len,
		__entry->tail_base, __entry->tail_len,
		__entry->len
	)
);

TRACE_EVENT(rpc_xdr_alignment,
	TP_PROTO(
		स्थिर काष्ठा xdr_stream *xdr,
		माप_प्रकार offset,
		अचिन्हित पूर्णांक copied
	),

	TP_ARGS(xdr, offset, copied),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, version)
		__field(माप_प्रकार, offset)
		__field(अचिन्हित पूर्णांक, copied)
		__field(स्थिर व्योम *, head_base)
		__field(माप_प्रकार, head_len)
		__field(स्थिर व्योम *, tail_base)
		__field(माप_प्रकार, tail_len)
		__field(अचिन्हित पूर्णांक, page_len)
		__field(अचिन्हित पूर्णांक, len)
		__string(progname,
			 xdr->rqst->rq_task->tk_client->cl_program->name)
		__string(procedure,
			 xdr->rqst->rq_task->tk_msg.rpc_proc->p_name)
	),

	TP_fast_assign(
		स्थिर काष्ठा rpc_task *task = xdr->rqst->rq_task;

		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__assign_str(progname,
			     task->tk_client->cl_program->name)
		__entry->version = task->tk_client->cl_vers;
		__assign_str(procedure, task->tk_msg.rpc_proc->p_name)

		__entry->offset = offset;
		__entry->copied = copied;
		__entry->head_base = xdr->buf->head[0].iov_base,
		__entry->head_len = xdr->buf->head[0].iov_len,
		__entry->page_len = xdr->buf->page_len,
		__entry->tail_base = xdr->buf->tail[0].iov_base,
		__entry->tail_len = xdr->buf->tail[0].iov_len,
		__entry->len = xdr->buf->len;
	),

	TP_prपूर्णांकk(
		"task:%u@%u %sv%d %s offset=%zu copied=%u xdr=[%p,%zu]/%u/[%p,%zu]/%u\n",
		__entry->task_id, __entry->client_id,
		__get_str(progname), __entry->version, __get_str(procedure),
		__entry->offset, __entry->copied,
		__entry->head_base, __entry->head_len,
		__entry->page_len,
		__entry->tail_base, __entry->tail_len,
		__entry->len
	)
);

/*
 * First define the क्रमागतs in the below macros to be exported to userspace
 * via TRACE_DEFINE_ENUM().
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

#घोषणा RPC_SHOW_SOCKET				\
	EM( SS_FREE, "FREE" )			\
	EM( SS_UNCONNECTED, "UNCONNECTED" )	\
	EM( SS_CONNECTING, "CONNECTING" )	\
	EM( SS_CONNECTED, "CONNECTED" )		\
	EMe( SS_DISCONNECTING, "DISCONNECTING" )

#घोषणा rpc_show_socket_state(state) \
	__prपूर्णांक_symbolic(state, RPC_SHOW_SOCKET)

RPC_SHOW_SOCKET

#घोषणा RPC_SHOW_SOCK				\
	EM( TCP_ESTABLISHED, "ESTABLISHED" )	\
	EM( TCP_SYN_SENT, "SYN_SENT" )		\
	EM( TCP_SYN_RECV, "SYN_RECV" )		\
	EM( TCP_FIN_WAIT1, "FIN_WAIT1" )	\
	EM( TCP_FIN_WAIT2, "FIN_WAIT2" )	\
	EM( TCP_TIME_WAIT, "TIME_WAIT" )	\
	EM( TCP_CLOSE, "CLOSE" )		\
	EM( TCP_CLOSE_WAIT, "CLOSE_WAIT" )	\
	EM( TCP_LAST_ACK, "LAST_ACK" )		\
	EM( TCP_LISTEN, "LISTEN" )		\
	EMe( TCP_CLOSING, "CLOSING" )

#घोषणा rpc_show_sock_state(state) \
	__prपूर्णांक_symbolic(state, RPC_SHOW_SOCK)

RPC_SHOW_SOCK

/*
 * Now redefine the EM() and EMe() macros to map the क्रमागतs to the strings
 * that will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	अणुa, bपूर्ण,
#घोषणा EMe(a, b)	अणुa, bपूर्ण

DECLARE_EVENT_CLASS(xs_socket_event,

		TP_PROTO(
			काष्ठा rpc_xprt *xprt,
			काष्ठा socket *socket
		),

		TP_ARGS(xprt, socket),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, socket_state)
			__field(अचिन्हित पूर्णांक, sock_state)
			__field(अचिन्हित दीर्घ दीर्घ, ino)
			__string(dstaddr,
				xprt->address_strings[RPC_DISPLAY_ADDR])
			__string(dstport,
				xprt->address_strings[RPC_DISPLAY_PORT])
		),

		TP_fast_assign(
			काष्ठा inode *inode = SOCK_INODE(socket);
			__entry->socket_state = socket->state;
			__entry->sock_state = socket->sk->sk_state;
			__entry->ino = (अचिन्हित दीर्घ दीर्घ)inode->i_ino;
			__assign_str(dstaddr,
				xprt->address_strings[RPC_DISPLAY_ADDR]);
			__assign_str(dstport,
				xprt->address_strings[RPC_DISPLAY_PORT]);
		),

		TP_prपूर्णांकk(
			"socket:[%llu] dstaddr=%s/%s "
			"state=%u (%s) sk_state=%u (%s)",
			__entry->ino, __get_str(dstaddr), __get_str(dstport),
			__entry->socket_state,
			rpc_show_socket_state(__entry->socket_state),
			__entry->sock_state,
			rpc_show_sock_state(__entry->sock_state)
		)
);
#घोषणा DEFINE_RPC_SOCKET_EVENT(name) \
	DEFINE_EVENT(xs_socket_event, name, \
			TP_PROTO( \
				काष्ठा rpc_xprt *xprt, \
				काष्ठा socket *socket \
			), \
			TP_ARGS(xprt, socket))

DECLARE_EVENT_CLASS(xs_socket_event_करोne,

		TP_PROTO(
			काष्ठा rpc_xprt *xprt,
			काष्ठा socket *socket,
			पूर्णांक error
		),

		TP_ARGS(xprt, socket, error),

		TP_STRUCT__entry(
			__field(पूर्णांक, error)
			__field(अचिन्हित पूर्णांक, socket_state)
			__field(अचिन्हित पूर्णांक, sock_state)
			__field(अचिन्हित दीर्घ दीर्घ, ino)
			__string(dstaddr,
				xprt->address_strings[RPC_DISPLAY_ADDR])
			__string(dstport,
				xprt->address_strings[RPC_DISPLAY_PORT])
		),

		TP_fast_assign(
			काष्ठा inode *inode = SOCK_INODE(socket);
			__entry->socket_state = socket->state;
			__entry->sock_state = socket->sk->sk_state;
			__entry->ino = (अचिन्हित दीर्घ दीर्घ)inode->i_ino;
			__entry->error = error;
			__assign_str(dstaddr,
				xprt->address_strings[RPC_DISPLAY_ADDR]);
			__assign_str(dstport,
				xprt->address_strings[RPC_DISPLAY_PORT]);
		),

		TP_prपूर्णांकk(
			"error=%d socket:[%llu] dstaddr=%s/%s "
			"state=%u (%s) sk_state=%u (%s)",
			__entry->error,
			__entry->ino, __get_str(dstaddr), __get_str(dstport),
			__entry->socket_state,
			rpc_show_socket_state(__entry->socket_state),
			__entry->sock_state,
			rpc_show_sock_state(__entry->sock_state)
		)
);
#घोषणा DEFINE_RPC_SOCKET_EVENT_DONE(name) \
	DEFINE_EVENT(xs_socket_event_करोne, name, \
			TP_PROTO( \
				काष्ठा rpc_xprt *xprt, \
				काष्ठा socket *socket, \
				पूर्णांक error \
			), \
			TP_ARGS(xprt, socket, error))

DEFINE_RPC_SOCKET_EVENT(rpc_socket_state_change);
DEFINE_RPC_SOCKET_EVENT_DONE(rpc_socket_connect);
DEFINE_RPC_SOCKET_EVENT_DONE(rpc_socket_error);
DEFINE_RPC_SOCKET_EVENT_DONE(rpc_socket_reset_connection);
DEFINE_RPC_SOCKET_EVENT(rpc_socket_बंद);
DEFINE_RPC_SOCKET_EVENT(rpc_socket_shutकरोwn);

TRACE_EVENT(rpc_socket_nospace,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst,
		स्थिर काष्ठा sock_xprt *transport
	),

	TP_ARGS(rqst, transport),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(अचिन्हित पूर्णांक, total)
		__field(अचिन्हित पूर्णांक, reमुख्यing)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->total = rqst->rq_slen;
		__entry->reमुख्यing = rqst->rq_slen - transport->xmit.offset;
	),

	TP_prपूर्णांकk("task:%u@%u total=%u remaining=%u",
		__entry->task_id, __entry->client_id,
		__entry->total, __entry->reमुख्यing
	)
);

TRACE_DEFINE_ENUM(XPRT_LOCKED);
TRACE_DEFINE_ENUM(XPRT_CONNECTED);
TRACE_DEFINE_ENUM(XPRT_CONNECTING);
TRACE_DEFINE_ENUM(XPRT_CLOSE_WAIT);
TRACE_DEFINE_ENUM(XPRT_BOUND);
TRACE_DEFINE_ENUM(XPRT_BINDING);
TRACE_DEFINE_ENUM(XPRT_CLOSING);
TRACE_DEFINE_ENUM(XPRT_CONGESTED);
TRACE_DEFINE_ENUM(XPRT_CWND_WAIT);
TRACE_DEFINE_ENUM(XPRT_WRITE_SPACE);

#घोषणा rpc_show_xprt_state(x)						\
	__prपूर्णांक_flags(x, "|",						\
		अणु (1UL << XPRT_LOCKED),		"LOCKED"पूर्ण,		\
		अणु (1UL << XPRT_CONNECTED),	"CONNECTED"पूर्ण,		\
		अणु (1UL << XPRT_CONNECTING),	"CONNECTING"पूर्ण,		\
		अणु (1UL << XPRT_CLOSE_WAIT),	"CLOSE_WAIT"पूर्ण,		\
		अणु (1UL << XPRT_BOUND),		"BOUND"पूर्ण,		\
		अणु (1UL << XPRT_BINDING),	"BINDING"पूर्ण,		\
		अणु (1UL << XPRT_CLOSING),	"CLOSING"पूर्ण,		\
		अणु (1UL << XPRT_CONGESTED),	"CONGESTED"पूर्ण,		\
		अणु (1UL << XPRT_CWND_WAIT),	"CWND_WAIT"पूर्ण,		\
		अणु (1UL << XPRT_WRITE_SPACE),	"WRITE_SPACE"पूर्ण)

DECLARE_EVENT_CLASS(rpc_xprt_lअगरeसमय_class,
	TP_PROTO(
		स्थिर काष्ठा rpc_xprt *xprt
	),

	TP_ARGS(xprt),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, state)
		__string(addr, xprt->address_strings[RPC_DISPLAY_ADDR])
		__string(port, xprt->address_strings[RPC_DISPLAY_PORT])
	),

	TP_fast_assign(
		__entry->state = xprt->state;
		__assign_str(addr, xprt->address_strings[RPC_DISPLAY_ADDR]);
		__assign_str(port, xprt->address_strings[RPC_DISPLAY_PORT]);
	),

	TP_prपूर्णांकk("peer=[%s]:%s state=%s",
		__get_str(addr), __get_str(port),
		rpc_show_xprt_state(__entry->state))
);

#घोषणा DEFINE_RPC_XPRT_LIFETIME_EVENT(name) \
	DEFINE_EVENT(rpc_xprt_lअगरeसमय_class, \
			xprt_##name, \
			TP_PROTO( \
				स्थिर काष्ठा rpc_xprt *xprt \
			), \
			TP_ARGS(xprt))

DEFINE_RPC_XPRT_LIFETIME_EVENT(create);
DEFINE_RPC_XPRT_LIFETIME_EVENT(connect);
DEFINE_RPC_XPRT_LIFETIME_EVENT(disconnect_स्वतः);
DEFINE_RPC_XPRT_LIFETIME_EVENT(disconnect_करोne);
DEFINE_RPC_XPRT_LIFETIME_EVENT(disconnect_क्रमce);
DEFINE_RPC_XPRT_LIFETIME_EVENT(disconnect_cleanup);
DEFINE_RPC_XPRT_LIFETIME_EVENT(destroy);

DECLARE_EVENT_CLASS(rpc_xprt_event,
	TP_PROTO(
		स्थिर काष्ठा rpc_xprt *xprt,
		__be32 xid,
		पूर्णांक status
	),

	TP_ARGS(xprt, xid, status),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(पूर्णांक, status)
		__string(addr, xprt->address_strings[RPC_DISPLAY_ADDR])
		__string(port, xprt->address_strings[RPC_DISPLAY_PORT])
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(xid);
		__entry->status = status;
		__assign_str(addr, xprt->address_strings[RPC_DISPLAY_ADDR]);
		__assign_str(port, xprt->address_strings[RPC_DISPLAY_PORT]);
	),

	TP_prपूर्णांकk("peer=[%s]:%s xid=0x%08x status=%d", __get_str(addr),
			__get_str(port), __entry->xid,
			__entry->status)
);
#घोषणा DEFINE_RPC_XPRT_EVENT(name) \
	DEFINE_EVENT(rpc_xprt_event, xprt_##name, \
			TP_PROTO( \
				स्थिर काष्ठा rpc_xprt *xprt, \
				__be32 xid, \
				पूर्णांक status \
			), \
			TP_ARGS(xprt, xid, status))

DEFINE_RPC_XPRT_EVENT(समयr);
DEFINE_RPC_XPRT_EVENT(lookup_rqst);

TRACE_EVENT(xprt_transmit,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst,
		पूर्णांक status
	),

	TP_ARGS(rqst, status),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(u32, seqno)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client ?
			rqst->rq_task->tk_client->cl_clid : -1;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->seqno = rqst->rq_seqno;
		__entry->status = status;
	),

	TP_prपूर्णांकk(
		"task:%u@%u xid=0x%08x seqno=%u status=%d",
		__entry->task_id, __entry->client_id, __entry->xid,
		__entry->seqno, __entry->status)
);

TRACE_EVENT(xprt_retransmit,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst
	),

	TP_ARGS(rqst),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(पूर्णांक, ntrans)
		__field(पूर्णांक, version)
		__string(progname,
			 rqst->rq_task->tk_client->cl_program->name)
		__string(procedure,
			 rqst->rq_task->tk_msg.rpc_proc->p_name)
	),

	TP_fast_assign(
		काष्ठा rpc_task *task = rqst->rq_task;

		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client ?
			task->tk_client->cl_clid : -1;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->ntrans = rqst->rq_ntrans;
		__assign_str(progname,
			     task->tk_client->cl_program->name)
		__entry->version = task->tk_client->cl_vers;
		__assign_str(procedure, task->tk_msg.rpc_proc->p_name)
	),

	TP_prपूर्णांकk(
		"task:%u@%u xid=0x%08x %sv%d %s ntrans=%d",
		__entry->task_id, __entry->client_id, __entry->xid,
		__get_str(progname), __entry->version, __get_str(procedure),
		__entry->ntrans)
);

TRACE_EVENT(xprt_ping,
	TP_PROTO(स्थिर काष्ठा rpc_xprt *xprt, पूर्णांक status),

	TP_ARGS(xprt, status),

	TP_STRUCT__entry(
		__field(पूर्णांक, status)
		__string(addr, xprt->address_strings[RPC_DISPLAY_ADDR])
		__string(port, xprt->address_strings[RPC_DISPLAY_PORT])
	),

	TP_fast_assign(
		__entry->status = status;
		__assign_str(addr, xprt->address_strings[RPC_DISPLAY_ADDR]);
		__assign_str(port, xprt->address_strings[RPC_DISPLAY_PORT]);
	),

	TP_prपूर्णांकk("peer=[%s]:%s status=%d",
			__get_str(addr), __get_str(port), __entry->status)
);

DECLARE_EVENT_CLASS(xprt_ग_लिखोlock_event,
	TP_PROTO(
		स्थिर काष्ठा rpc_xprt *xprt, स्थिर काष्ठा rpc_task *task
	),

	TP_ARGS(xprt, task),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(अचिन्हित पूर्णांक, snd_task_id)
	),

	TP_fast_assign(
		अगर (task) अणु
			__entry->task_id = task->tk_pid;
			__entry->client_id = task->tk_client ?
					     task->tk_client->cl_clid : -1;
		पूर्ण अन्यथा अणु
			__entry->task_id = -1;
			__entry->client_id = -1;
		पूर्ण
		__entry->snd_task_id = xprt->snd_task ?
					xprt->snd_task->tk_pid : -1;
	),

	TP_prपूर्णांकk("task:%u@%u snd_task:%u",
			__entry->task_id, __entry->client_id,
			__entry->snd_task_id)
);

#घोषणा DEFINE_WRITELOCK_EVENT(name) \
	DEFINE_EVENT(xprt_ग_लिखोlock_event, xprt_##name, \
			TP_PROTO( \
				स्थिर काष्ठा rpc_xprt *xprt, \
				स्थिर काष्ठा rpc_task *task \
			), \
			TP_ARGS(xprt, task))

DEFINE_WRITELOCK_EVENT(reserve_xprt);
DEFINE_WRITELOCK_EVENT(release_xprt);

DECLARE_EVENT_CLASS(xprt_cong_event,
	TP_PROTO(
		स्थिर काष्ठा rpc_xprt *xprt, स्थिर काष्ठा rpc_task *task
	),

	TP_ARGS(xprt, task),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(अचिन्हित पूर्णांक, snd_task_id)
		__field(अचिन्हित दीर्घ, cong)
		__field(अचिन्हित दीर्घ, cwnd)
		__field(bool, रुको)
	),

	TP_fast_assign(
		अगर (task) अणु
			__entry->task_id = task->tk_pid;
			__entry->client_id = task->tk_client ?
					     task->tk_client->cl_clid : -1;
		पूर्ण अन्यथा अणु
			__entry->task_id = -1;
			__entry->client_id = -1;
		पूर्ण
		__entry->snd_task_id = xprt->snd_task ?
					xprt->snd_task->tk_pid : -1;
		__entry->cong = xprt->cong;
		__entry->cwnd = xprt->cwnd;
		__entry->रुको = test_bit(XPRT_CWND_WAIT, &xprt->state);
	),

	TP_prपूर्णांकk("task:%u@%u snd_task:%u cong=%lu cwnd=%lu%s",
			__entry->task_id, __entry->client_id,
			__entry->snd_task_id, __entry->cong, __entry->cwnd,
			__entry->रुको ? " (wait)" : "")
);

#घोषणा DEFINE_CONG_EVENT(name) \
	DEFINE_EVENT(xprt_cong_event, xprt_##name, \
			TP_PROTO( \
				स्थिर काष्ठा rpc_xprt *xprt, \
				स्थिर काष्ठा rpc_task *task \
			), \
			TP_ARGS(xprt, task))

DEFINE_CONG_EVENT(reserve_cong);
DEFINE_CONG_EVENT(release_cong);
DEFINE_CONG_EVENT(get_cong);
DEFINE_CONG_EVENT(put_cong);

TRACE_EVENT(xprt_reserve,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst
	),

	TP_ARGS(rqst),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x",
		__entry->task_id, __entry->client_id, __entry->xid
	)
);

TRACE_EVENT(xs_stream_पढ़ो_data,
	TP_PROTO(काष्ठा rpc_xprt *xprt, sमाप_प्रकार err, माप_प्रकार total),

	TP_ARGS(xprt, err, total),

	TP_STRUCT__entry(
		__field(sमाप_प्रकार, err)
		__field(माप_प्रकार, total)
		__string(addr, xprt ? xprt->address_strings[RPC_DISPLAY_ADDR] :
				"(null)")
		__string(port, xprt ? xprt->address_strings[RPC_DISPLAY_PORT] :
				"(null)")
	),

	TP_fast_assign(
		__entry->err = err;
		__entry->total = total;
		__assign_str(addr, xprt ?
			xprt->address_strings[RPC_DISPLAY_ADDR] : "(null)");
		__assign_str(port, xprt ?
			xprt->address_strings[RPC_DISPLAY_PORT] : "(null)");
	),

	TP_prपूर्णांकk("peer=[%s]:%s err=%zd total=%zu", __get_str(addr),
			__get_str(port), __entry->err, __entry->total)
);

TRACE_EVENT(xs_stream_पढ़ो_request,
	TP_PROTO(काष्ठा sock_xprt *xs),

	TP_ARGS(xs),

	TP_STRUCT__entry(
		__string(addr, xs->xprt.address_strings[RPC_DISPLAY_ADDR])
		__string(port, xs->xprt.address_strings[RPC_DISPLAY_PORT])
		__field(u32, xid)
		__field(अचिन्हित दीर्घ, copied)
		__field(अचिन्हित पूर्णांक, reclen)
		__field(अचिन्हित पूर्णांक, offset)
	),

	TP_fast_assign(
		__assign_str(addr, xs->xprt.address_strings[RPC_DISPLAY_ADDR]);
		__assign_str(port, xs->xprt.address_strings[RPC_DISPLAY_PORT]);
		__entry->xid = be32_to_cpu(xs->recv.xid);
		__entry->copied = xs->recv.copied;
		__entry->reclen = xs->recv.len;
		__entry->offset = xs->recv.offset;
	),

	TP_prपूर्णांकk("peer=[%s]:%s xid=0x%08x copied=%lu reclen=%u offset=%u",
			__get_str(addr), __get_str(port), __entry->xid,
			__entry->copied, __entry->reclen, __entry->offset)
);

TRACE_EVENT(rpcb_getport,
	TP_PROTO(
		स्थिर काष्ठा rpc_clnt *clnt,
		स्थिर काष्ठा rpc_task *task,
		अचिन्हित पूर्णांक bind_version
	),

	TP_ARGS(clnt, task, bind_version),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(अचिन्हित पूर्णांक, program)
		__field(अचिन्हित पूर्णांक, version)
		__field(पूर्णांक, protocol)
		__field(अचिन्हित पूर्णांक, bind_version)
		__string(servername, task->tk_xprt->servername)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = clnt->cl_clid;
		__entry->program = clnt->cl_prog;
		__entry->version = clnt->cl_vers;
		__entry->protocol = task->tk_xprt->prot;
		__entry->bind_version = bind_version;
		__assign_str(servername, task->tk_xprt->servername);
	),

	TP_prपूर्णांकk("task:%u@%u server=%s program=%u version=%u protocol=%d bind_version=%u",
		__entry->task_id, __entry->client_id, __get_str(servername),
		__entry->program, __entry->version, __entry->protocol,
		__entry->bind_version
	)
);

TRACE_EVENT(rpcb_setport,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		पूर्णांक status,
		अचिन्हित लघु port
	),

	TP_ARGS(task, status, port),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, status)
		__field(अचिन्हित लघु, port)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->status = status;
		__entry->port = port;
	),

	TP_prपूर्णांकk("task:%u@%u status=%d port=%u",
		__entry->task_id, __entry->client_id,
		__entry->status, __entry->port
	)
);

TRACE_EVENT(pmap_रेजिस्टर,
	TP_PROTO(
		u32 program,
		u32 version,
		पूर्णांक protocol,
		अचिन्हित लघु port
	),

	TP_ARGS(program, version, protocol, port),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, program)
		__field(अचिन्हित पूर्णांक, version)
		__field(पूर्णांक, protocol)
		__field(अचिन्हित पूर्णांक, port)
	),

	TP_fast_assign(
		__entry->program = program;
		__entry->version = version;
		__entry->protocol = protocol;
		__entry->port = port;
	),

	TP_prपूर्णांकk("program=%u version=%u protocol=%d port=%u",
		__entry->program, __entry->version,
		__entry->protocol, __entry->port
	)
);

TRACE_EVENT(rpcb_रेजिस्टर,
	TP_PROTO(
		u32 program,
		u32 version,
		स्थिर अक्षर *addr,
		स्थिर अक्षर *netid
	),

	TP_ARGS(program, version, addr, netid),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, program)
		__field(अचिन्हित पूर्णांक, version)
		__string(addr, addr)
		__string(netid, netid)
	),

	TP_fast_assign(
		__entry->program = program;
		__entry->version = version;
		__assign_str(addr, addr);
		__assign_str(netid, netid);
	),

	TP_prपूर्णांकk("program=%u version=%u addr=%s netid=%s",
		__entry->program, __entry->version,
		__get_str(addr), __get_str(netid)
	)
);

TRACE_EVENT(rpcb_unरेजिस्टर,
	TP_PROTO(
		u32 program,
		u32 version,
		स्थिर अक्षर *netid
	),

	TP_ARGS(program, version, netid),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, program)
		__field(अचिन्हित पूर्णांक, version)
		__string(netid, netid)
	),

	TP_fast_assign(
		__entry->program = program;
		__entry->version = version;
		__assign_str(netid, netid);
	),

	TP_prपूर्णांकk("program=%u version=%u netid=%s",
		__entry->program, __entry->version, __get_str(netid)
	)
);

/* Record an xdr_buf containing a fully-क्रमmed RPC message */
DECLARE_EVENT_CLASS(svc_xdr_msg_class,
	TP_PROTO(
		स्थिर काष्ठा xdr_buf *xdr
	),

	TP_ARGS(xdr),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(स्थिर व्योम *, head_base)
		__field(माप_प्रकार, head_len)
		__field(स्थिर व्योम *, tail_base)
		__field(माप_प्रकार, tail_len)
		__field(अचिन्हित पूर्णांक, page_len)
		__field(अचिन्हित पूर्णांक, msg_len)
	),

	TP_fast_assign(
		__be32 *p = (__be32 *)xdr->head[0].iov_base;

		__entry->xid = be32_to_cpu(*p);
		__entry->head_base = p;
		__entry->head_len = xdr->head[0].iov_len;
		__entry->tail_base = xdr->tail[0].iov_base;
		__entry->tail_len = xdr->tail[0].iov_len;
		__entry->page_len = xdr->page_len;
		__entry->msg_len = xdr->len;
	),

	TP_prपूर्णांकk("xid=0x%08x head=[%p,%zu] page=%u tail=[%p,%zu] len=%u",
		__entry->xid,
		__entry->head_base, __entry->head_len, __entry->page_len,
		__entry->tail_base, __entry->tail_len, __entry->msg_len
	)
);

#घोषणा DEFINE_SVCXDRMSG_EVENT(name)					\
		DEFINE_EVENT(svc_xdr_msg_class,				\
				svc_xdr_##name,				\
				TP_PROTO(				\
					स्थिर काष्ठा xdr_buf *xdr	\
				),					\
				TP_ARGS(xdr))

DEFINE_SVCXDRMSG_EVENT(recvfrom);

/* Record an xdr_buf containing arbitrary data, tagged with an XID */
DECLARE_EVENT_CLASS(svc_xdr_buf_class,
	TP_PROTO(
		__be32 xid,
		स्थिर काष्ठा xdr_buf *xdr
	),

	TP_ARGS(xid, xdr),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(स्थिर व्योम *, head_base)
		__field(माप_प्रकार, head_len)
		__field(स्थिर व्योम *, tail_base)
		__field(माप_प्रकार, tail_len)
		__field(अचिन्हित पूर्णांक, page_len)
		__field(अचिन्हित पूर्णांक, msg_len)
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(xid);
		__entry->head_base = xdr->head[0].iov_base;
		__entry->head_len = xdr->head[0].iov_len;
		__entry->tail_base = xdr->tail[0].iov_base;
		__entry->tail_len = xdr->tail[0].iov_len;
		__entry->page_len = xdr->page_len;
		__entry->msg_len = xdr->len;
	),

	TP_prपूर्णांकk("xid=0x%08x head=[%p,%zu] page=%u tail=[%p,%zu] len=%u",
		__entry->xid,
		__entry->head_base, __entry->head_len, __entry->page_len,
		__entry->tail_base, __entry->tail_len, __entry->msg_len
	)
);

#घोषणा DEFINE_SVCXDRBUF_EVENT(name)					\
		DEFINE_EVENT(svc_xdr_buf_class,				\
				svc_xdr_##name,				\
				TP_PROTO(				\
					__be32 xid,			\
					स्थिर काष्ठा xdr_buf *xdr	\
				),					\
				TP_ARGS(xid, xdr))

DEFINE_SVCXDRBUF_EVENT(sendto);

/*
 * from include/linux/sunrpc/svc.h
 */
#घोषणा SVC_RQST_FLAG_LIST						\
	svc_rqst_flag(SECURE)						\
	svc_rqst_flag(LOCAL)						\
	svc_rqst_flag(USEDEFERRAL)					\
	svc_rqst_flag(DROPME)						\
	svc_rqst_flag(SPLICE_OK)					\
	svc_rqst_flag(VICTIM)						\
	svc_rqst_flag(BUSY)						\
	svc_rqst_flag(DATA)						\
	svc_rqst_flag_end(AUTHERR)

#अघोषित svc_rqst_flag
#अघोषित svc_rqst_flag_end
#घोषणा svc_rqst_flag(x)	TRACE_DEFINE_ENUM(RQ_##x);
#घोषणा svc_rqst_flag_end(x)	TRACE_DEFINE_ENUM(RQ_##x);

SVC_RQST_FLAG_LIST

#अघोषित svc_rqst_flag
#अघोषित svc_rqst_flag_end
#घोषणा svc_rqst_flag(x)	अणु BIT(RQ_##x), #x पूर्ण,
#घोषणा svc_rqst_flag_end(x)	अणु BIT(RQ_##x), #x पूर्ण

#घोषणा show_rqstp_flags(flags)						\
		__prपूर्णांक_flags(flags, "|", SVC_RQST_FLAG_LIST)

TRACE_DEFINE_ENUM(SVC_GARBAGE);
TRACE_DEFINE_ENUM(SVC_SYSERR);
TRACE_DEFINE_ENUM(SVC_VALID);
TRACE_DEFINE_ENUM(SVC_NEGATIVE);
TRACE_DEFINE_ENUM(SVC_OK);
TRACE_DEFINE_ENUM(SVC_DROP);
TRACE_DEFINE_ENUM(SVC_CLOSE);
TRACE_DEFINE_ENUM(SVC_DENIED);
TRACE_DEFINE_ENUM(SVC_PENDING);
TRACE_DEFINE_ENUM(SVC_COMPLETE);

#घोषणा svc_show_status(status)				\
	__prपूर्णांक_symbolic(status,			\
		अणु SVC_GARBAGE,	"SVC_GARBAGE" पूर्ण,	\
		अणु SVC_SYSERR,	"SVC_SYSERR" पूर्ण,		\
		अणु SVC_VALID,	"SVC_VALID" पूर्ण,		\
		अणु SVC_NEGATIVE,	"SVC_NEGATIVE" पूर्ण,	\
		अणु SVC_OK,	"SVC_OK" पूर्ण,		\
		अणु SVC_DROP,	"SVC_DROP" पूर्ण,		\
		अणु SVC_CLOSE,	"SVC_CLOSE" पूर्ण,		\
		अणु SVC_DENIED,	"SVC_DENIED" पूर्ण,		\
		अणु SVC_PENDING,	"SVC_PENDING" पूर्ण,	\
		अणु SVC_COMPLETE,	"SVC_COMPLETE" पूर्ण)

TRACE_EVENT(svc_authenticate,
	TP_PROTO(स्थिर काष्ठा svc_rqst *rqst, पूर्णांक auth_res, __be32 auth_stat),

	TP_ARGS(rqst, auth_res, auth_stat),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(अचिन्हित दीर्घ, svc_status)
		__field(अचिन्हित दीर्घ, auth_stat)
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->svc_status = auth_res;
		__entry->auth_stat = be32_to_cpu(auth_stat);
	),

	TP_prपूर्णांकk("xid=0x%08x auth_res=%s auth_stat=%s",
			__entry->xid, svc_show_status(__entry->svc_status),
			rpc_show_auth_stat(__entry->auth_stat))
);

TRACE_EVENT(svc_process,
	TP_PROTO(स्थिर काष्ठा svc_rqst *rqst, स्थिर अक्षर *name),

	TP_ARGS(rqst, name),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(u32, vers)
		__field(u32, proc)
		__string(service, name)
		__string(procedure, rqst->rq_procinfo->pc_name)
		__string(addr, rqst->rq_xprt ?
			 rqst->rq_xprt->xpt_remotebuf : "(null)")
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->vers = rqst->rq_vers;
		__entry->proc = rqst->rq_proc;
		__assign_str(service, name);
		__assign_str(procedure, rqst->rq_procinfo->pc_name);
		__assign_str(addr, rqst->rq_xprt ?
			     rqst->rq_xprt->xpt_remotebuf : "(null)");
	),

	TP_prपूर्णांकk("addr=%s xid=0x%08x service=%s vers=%u proc=%s",
			__get_str(addr), __entry->xid,
			__get_str(service), __entry->vers,
			__get_str(procedure)
	)
);

DECLARE_EVENT_CLASS(svc_rqst_event,

	TP_PROTO(
		स्थिर काष्ठा svc_rqst *rqst
	),

	TP_ARGS(rqst),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, rqst->rq_xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->flags = rqst->rq_flags;
		__assign_str(addr, rqst->rq_xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s xid=0x%08x flags=%s",
			__get_str(addr), __entry->xid,
			show_rqstp_flags(__entry->flags))
);
#घोषणा DEFINE_SVC_RQST_EVENT(name) \
	DEFINE_EVENT(svc_rqst_event, svc_##name, \
			TP_PROTO( \
				स्थिर काष्ठा svc_rqst *rqst \
			), \
			TP_ARGS(rqst))

DEFINE_SVC_RQST_EVENT(defer);
DEFINE_SVC_RQST_EVENT(drop);

DECLARE_EVENT_CLASS(svc_rqst_status,

	TP_PROTO(काष्ठा svc_rqst *rqst, पूर्णांक status),

	TP_ARGS(rqst, status),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(पूर्णांक, status)
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, rqst->rq_xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->status = status;
		__entry->flags = rqst->rq_flags;
		__assign_str(addr, rqst->rq_xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s xid=0x%08x status=%d flags=%s",
		  __get_str(addr), __entry->xid,
		  __entry->status, show_rqstp_flags(__entry->flags))
);

DEFINE_EVENT(svc_rqst_status, svc_send,
	TP_PROTO(काष्ठा svc_rqst *rqst, पूर्णांक status),
	TP_ARGS(rqst, status));

#घोषणा show_svc_xprt_flags(flags)					\
	__prपूर्णांक_flags(flags, "|",					\
		अणु (1UL << XPT_BUSY),		"XPT_BUSY"पूर्ण,		\
		अणु (1UL << XPT_CONN),		"XPT_CONN"पूर्ण,		\
		अणु (1UL << XPT_CLOSE),		"XPT_CLOSE"पूर्ण,		\
		अणु (1UL << XPT_DATA),		"XPT_DATA"पूर्ण,		\
		अणु (1UL << XPT_TEMP),		"XPT_TEMP"पूर्ण,		\
		अणु (1UL << XPT_DEAD),		"XPT_DEAD"पूर्ण,		\
		अणु (1UL << XPT_CHNGBUF),		"XPT_CHNGBUF"पूर्ण,		\
		अणु (1UL << XPT_DEFERRED),	"XPT_DEFERRED"पूर्ण,	\
		अणु (1UL << XPT_OLD),		"XPT_OLD"पूर्ण,		\
		अणु (1UL << XPT_LISTENER),	"XPT_LISTENER"पूर्ण,	\
		अणु (1UL << XPT_CACHE_AUTH),	"XPT_CACHE_AUTH"पूर्ण,	\
		अणु (1UL << XPT_LOCAL),		"XPT_LOCAL"पूर्ण,		\
		अणु (1UL << XPT_KILL_TEMP),	"XPT_KILL_TEMP"पूर्ण,	\
		अणु (1UL << XPT_CONG_CTRL),	"XPT_CONG_CTRL"पूर्ण)

TRACE_EVENT(svc_xprt_create_err,
	TP_PROTO(
		स्थिर अक्षर *program,
		स्थिर अक्षर *protocol,
		काष्ठा sockaddr *sap,
		स्थिर काष्ठा svc_xprt *xprt
	),

	TP_ARGS(program, protocol, sap, xprt),

	TP_STRUCT__entry(
		__field(दीर्घ, error)
		__string(program, program)
		__string(protocol, protocol)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->error = PTR_ERR(xprt);
		__assign_str(program, program);
		__assign_str(protocol, protocol);
		स_नकल(__entry->addr, sap, माप(__entry->addr));
	),

	TP_prपूर्णांकk("addr=%pISpc program=%s protocol=%s error=%ld",
		__entry->addr, __get_str(program), __get_str(protocol),
		__entry->error)
);

TRACE_EVENT(svc_xprt_करो_enqueue,
	TP_PROTO(काष्ठा svc_xprt *xprt, काष्ठा svc_rqst *rqst),

	TP_ARGS(xprt, rqst),

	TP_STRUCT__entry(
		__field(पूर्णांक, pid)
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->pid = rqst? rqst->rq_task->pid : 0;
		__entry->flags = xprt->xpt_flags;
		__assign_str(addr, xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s pid=%d flags=%s", __get_str(addr),
		__entry->pid, show_svc_xprt_flags(__entry->flags))
);

DECLARE_EVENT_CLASS(svc_xprt_event,
	TP_PROTO(काष्ठा svc_xprt *xprt),

	TP_ARGS(xprt),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->flags = xprt->xpt_flags;
		__assign_str(addr, xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s flags=%s", __get_str(addr),
		show_svc_xprt_flags(__entry->flags))
);

#घोषणा DEFINE_SVC_XPRT_EVENT(name) \
	DEFINE_EVENT(svc_xprt_event, svc_xprt_##name, \
			TP_PROTO( \
				काष्ठा svc_xprt *xprt \
			), \
			TP_ARGS(xprt))

DEFINE_SVC_XPRT_EVENT(received);
DEFINE_SVC_XPRT_EVENT(no_ग_लिखो_space);
DEFINE_SVC_XPRT_EVENT(बंद);
DEFINE_SVC_XPRT_EVENT(detach);
DEFINE_SVC_XPRT_EVENT(मुक्त);

TRACE_EVENT(svc_xprt_accept,
	TP_PROTO(
		स्थिर काष्ठा svc_xprt *xprt,
		स्थिर अक्षर *service
	),

	TP_ARGS(xprt, service),

	TP_STRUCT__entry(
		__string(addr, xprt->xpt_remotebuf)
		__string(protocol, xprt->xpt_class->xcl_name)
		__string(service, service)
	),

	TP_fast_assign(
		__assign_str(addr, xprt->xpt_remotebuf);
		__assign_str(protocol, xprt->xpt_class->xcl_name)
		__assign_str(service, service);
	),

	TP_prपूर्णांकk("addr=%s protocol=%s service=%s",
		__get_str(addr), __get_str(protocol), __get_str(service)
	)
);

TRACE_EVENT(svc_xprt_dequeue,
	TP_PROTO(काष्ठा svc_rqst *rqst),

	TP_ARGS(rqst),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, flags)
		__field(अचिन्हित दीर्घ, wakeup)
		__string(addr, rqst->rq_xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->flags = rqst->rq_xprt->xpt_flags;
		__entry->wakeup = kसमय_प्रकारo_us(kसमय_sub(kसमय_get(),
							rqst->rq_qसमय));
		__assign_str(addr, rqst->rq_xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s flags=%s wakeup-us=%lu", __get_str(addr),
		show_svc_xprt_flags(__entry->flags), __entry->wakeup)
);

TRACE_EVENT(svc_wake_up,
	TP_PROTO(पूर्णांक pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("pid=%d", __entry->pid)
);

TRACE_EVENT(svc_handle_xprt,
	TP_PROTO(काष्ठा svc_xprt *xprt, पूर्णांक len),

	TP_ARGS(xprt, len),

	TP_STRUCT__entry(
		__field(पूर्णांक, len)
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->len = len;
		__entry->flags = xprt->xpt_flags;
		__assign_str(addr, xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s len=%d flags=%s", __get_str(addr),
		__entry->len, show_svc_xprt_flags(__entry->flags))
);

TRACE_EVENT(svc_stats_latency,
	TP_PROTO(स्थिर काष्ठा svc_rqst *rqst),

	TP_ARGS(rqst),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(अचिन्हित दीर्घ, execute)
		__string(procedure, rqst->rq_procinfo->pc_name)
		__string(addr, rqst->rq_xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->execute = kसमय_प्रकारo_us(kसमय_sub(kसमय_get(),
							 rqst->rq_sसमय));
		__assign_str(procedure, rqst->rq_procinfo->pc_name);
		__assign_str(addr, rqst->rq_xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s xid=0x%08x proc=%s execute-us=%lu",
		__get_str(addr), __entry->xid, __get_str(procedure),
		__entry->execute)
);

DECLARE_EVENT_CLASS(svc_deferred_event,
	TP_PROTO(
		स्थिर काष्ठा svc_deferred_req *dr
	),

	TP_ARGS(dr),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, dr)
		__field(u32, xid)
		__string(addr, dr->xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->dr = dr;
		__entry->xid = be32_to_cpu(*(__be32 *)(dr->args +
						       (dr->xprt_hlen>>2)));
		__assign_str(addr, dr->xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s dr=%p xid=0x%08x", __get_str(addr), __entry->dr,
		__entry->xid)
);

#घोषणा DEFINE_SVC_DEFERRED_EVENT(name) \
	DEFINE_EVENT(svc_deferred_event, svc_defer_##name, \
			TP_PROTO( \
				स्थिर काष्ठा svc_deferred_req *dr \
			), \
			TP_ARGS(dr))

DEFINE_SVC_DEFERRED_EVENT(drop);
DEFINE_SVC_DEFERRED_EVENT(queue);
DEFINE_SVC_DEFERRED_EVENT(recv);

TRACE_EVENT(svcsock_new_socket,
	TP_PROTO(
		स्थिर काष्ठा socket *socket
	),

	TP_ARGS(socket),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, type)
		__field(अचिन्हित दीर्घ, family)
		__field(bool, listener)
	),

	TP_fast_assign(
		__entry->type = socket->type;
		__entry->family = socket->sk->sk_family;
		__entry->listener = (socket->sk->sk_state == TCP_LISTEN);
	),

	TP_prपूर्णांकk("type=%s family=%s%s",
		show_socket_type(__entry->type),
		rpc_show_address_family(__entry->family),
		__entry->listener ? " (listener)" : ""
	)
);

TRACE_EVENT(svcsock_marker,
	TP_PROTO(
		स्थिर काष्ठा svc_xprt *xprt,
		__be32 marker
	),

	TP_ARGS(xprt, marker),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, length)
		__field(bool, last)
		__string(addr, xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->length = be32_to_cpu(marker) & RPC_FRAGMENT_SIZE_MASK;
		__entry->last = be32_to_cpu(marker) & RPC_LAST_STREAM_FRAGMENT;
		__assign_str(addr, xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s length=%u%s", __get_str(addr),
		__entry->length, __entry->last ? " (last)" : "")
);

DECLARE_EVENT_CLASS(svcsock_class,
	TP_PROTO(
		स्थिर काष्ठा svc_xprt *xprt,
		sमाप_प्रकार result
	),

	TP_ARGS(xprt, result),

	TP_STRUCT__entry(
		__field(sमाप_प्रकार, result)
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->result = result;
		__entry->flags = xprt->xpt_flags;
		__assign_str(addr, xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s result=%zd flags=%s", __get_str(addr),
		__entry->result, show_svc_xprt_flags(__entry->flags)
	)
);

#घोषणा DEFINE_SVCSOCK_EVENT(name) \
	DEFINE_EVENT(svcsock_class, svcsock_##name, \
			TP_PROTO( \
				स्थिर काष्ठा svc_xprt *xprt, \
				sमाप_प्रकार result \
			), \
			TP_ARGS(xprt, result))

DEFINE_SVCSOCK_EVENT(udp_send);
DEFINE_SVCSOCK_EVENT(udp_recv);
DEFINE_SVCSOCK_EVENT(udp_recv_err);
DEFINE_SVCSOCK_EVENT(tcp_send);
DEFINE_SVCSOCK_EVENT(tcp_recv);
DEFINE_SVCSOCK_EVENT(tcp_recv_eagain);
DEFINE_SVCSOCK_EVENT(tcp_recv_err);
DEFINE_SVCSOCK_EVENT(data_पढ़ोy);
DEFINE_SVCSOCK_EVENT(ग_लिखो_space);

TRACE_EVENT(svcsock_tcp_recv_लघु,
	TP_PROTO(
		स्थिर काष्ठा svc_xprt *xprt,
		u32 expected,
		u32 received
	),

	TP_ARGS(xprt, expected, received),

	TP_STRUCT__entry(
		__field(u32, expected)
		__field(u32, received)
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->expected = expected;
		__entry->received = received;
		__entry->flags = xprt->xpt_flags;
		__assign_str(addr, xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s flags=%s expected=%u received=%u",
		__get_str(addr), show_svc_xprt_flags(__entry->flags),
		__entry->expected, __entry->received
	)
);

TRACE_EVENT(svcsock_tcp_state,
	TP_PROTO(
		स्थिर काष्ठा svc_xprt *xprt,
		स्थिर काष्ठा socket *socket
	),

	TP_ARGS(xprt, socket),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, socket_state)
		__field(अचिन्हित दीर्घ, sock_state)
		__field(अचिन्हित दीर्घ, flags)
		__string(addr, xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->socket_state = socket->state;
		__entry->sock_state = socket->sk->sk_state;
		__entry->flags = xprt->xpt_flags;
		__assign_str(addr, xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s state=%s sk_state=%s flags=%s", __get_str(addr),
		rpc_show_socket_state(__entry->socket_state),
		rpc_show_sock_state(__entry->sock_state),
		show_svc_xprt_flags(__entry->flags)
	)
);

DECLARE_EVENT_CLASS(svcsock_accept_class,
	TP_PROTO(
		स्थिर काष्ठा svc_xprt *xprt,
		स्थिर अक्षर *service,
		दीर्घ status
	),

	TP_ARGS(xprt, service, status),

	TP_STRUCT__entry(
		__field(दीर्घ, status)
		__string(service, service)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->status = status;
		__assign_str(service, service);
		स_नकल(__entry->addr, &xprt->xpt_local, माप(__entry->addr));
	),

	TP_prपूर्णांकk("listener=%pISpc service=%s status=%ld",
		__entry->addr, __get_str(service), __entry->status
	)
);

#घोषणा DEFINE_ACCEPT_EVENT(name) \
	DEFINE_EVENT(svcsock_accept_class, svcsock_##name##_err, \
			TP_PROTO( \
				स्थिर काष्ठा svc_xprt *xprt, \
				स्थिर अक्षर *service, \
				दीर्घ status \
			), \
			TP_ARGS(xprt, service, status))

DEFINE_ACCEPT_EVENT(accept);
DEFINE_ACCEPT_EVENT(getpeername);

DECLARE_EVENT_CLASS(cache_event,
	TP_PROTO(
		स्थिर काष्ठा cache_detail *cd,
		स्थिर काष्ठा cache_head *h
	),

	TP_ARGS(cd, h),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा cache_head *, h)
		__string(name, cd->name)
	),

	TP_fast_assign(
		__entry->h = h;
		__assign_str(name, cd->name);
	),

	TP_prपूर्णांकk("cache=%s entry=%p", __get_str(name), __entry->h)
);
#घोषणा DEFINE_CACHE_EVENT(name) \
	DEFINE_EVENT(cache_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा cache_detail *cd, \
				स्थिर काष्ठा cache_head *h \
			), \
			TP_ARGS(cd, h))
DEFINE_CACHE_EVENT(cache_entry_expired);
DEFINE_CACHE_EVENT(cache_entry_upcall);
DEFINE_CACHE_EVENT(cache_entry_update);
DEFINE_CACHE_EVENT(cache_entry_make_negative);
DEFINE_CACHE_EVENT(cache_entry_no_listener);

DECLARE_EVENT_CLASS(रेजिस्टर_class,
	TP_PROTO(
		स्थिर अक्षर *program,
		स्थिर u32 version,
		स्थिर पूर्णांक family,
		स्थिर अचिन्हित लघु protocol,
		स्थिर अचिन्हित लघु port,
		पूर्णांक error
	),

	TP_ARGS(program, version, family, protocol, port, error),

	TP_STRUCT__entry(
		__field(u32, version)
		__field(अचिन्हित दीर्घ, family)
		__field(अचिन्हित लघु, protocol)
		__field(अचिन्हित लघु, port)
		__field(पूर्णांक, error)
		__string(program, program)
	),

	TP_fast_assign(
		__entry->version = version;
		__entry->family = family;
		__entry->protocol = protocol;
		__entry->port = port;
		__entry->error = error;
		__assign_str(program, program);
	),

	TP_prपूर्णांकk("program=%sv%u proto=%s port=%u family=%s error=%d",
		__get_str(program), __entry->version,
		__entry->protocol == IPPROTO_UDP ? "udp" : "tcp",
		__entry->port, rpc_show_address_family(__entry->family),
		__entry->error
	)
);

#घोषणा DEFINE_REGISTER_EVENT(name) \
	DEFINE_EVENT(रेजिस्टर_class, svc_##name, \
			TP_PROTO( \
				स्थिर अक्षर *program, \
				स्थिर u32 version, \
				स्थिर पूर्णांक family, \
				स्थिर अचिन्हित लघु protocol, \
				स्थिर अचिन्हित लघु port, \
				पूर्णांक error \
			), \
			TP_ARGS(program, version, family, protocol, \
				port, error))

DEFINE_REGISTER_EVENT(रेजिस्टर);
DEFINE_REGISTER_EVENT(noरेजिस्टर);

TRACE_EVENT(svc_unरेजिस्टर,
	TP_PROTO(
		स्थिर अक्षर *program,
		स्थिर u32 version,
		पूर्णांक error
	),

	TP_ARGS(program, version, error),

	TP_STRUCT__entry(
		__field(u32, version)
		__field(पूर्णांक, error)
		__string(program, program)
	),

	TP_fast_assign(
		__entry->version = version;
		__entry->error = error;
		__assign_str(program, program);
	),

	TP_prपूर्णांकk("program=%sv%u error=%d",
		__get_str(program), __entry->version, __entry->error
	)
);

#पूर्ण_अगर /* _TRACE_SUNRPC_H */

#समावेश <trace/define_trace.h>
