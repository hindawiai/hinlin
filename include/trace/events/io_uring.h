<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM io_uring

#अगर !defined(_TRACE_IO_URING_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_IO_URING_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा io_wq_work;

/**
 * io_uring_create - called after a new io_uring context was prepared
 *
 * @fd:			corresponding file descriptor
 * @ctx:		poपूर्णांकer to a ring context काष्ठाure
 * @sq_entries:	actual SQ size
 * @cq_entries:	actual CQ size
 * @flags:		SQ ring flags, provided to io_uring_setup(2)
 *
 * Allows to trace io_uring creation and provide poपूर्णांकer to a context, that can
 * be used later to find correlated events.
 */
TRACE_EVENT(io_uring_create,

	TP_PROTO(पूर्णांक fd, व्योम *ctx, u32 sq_entries, u32 cq_entries, u32 flags),

	TP_ARGS(fd, ctx, sq_entries, cq_entries, flags),

	TP_STRUCT__entry (
		__field(  पूर्णांक,		fd			)
		__field(  व्योम *,	ctx			)
		__field(  u32,		sq_entries	)
		__field(  u32,		cq_entries	)
		__field(  u32,		flags		)
	),

	TP_fast_assign(
		__entry->fd			= fd;
		__entry->ctx		= ctx;
		__entry->sq_entries	= sq_entries;
		__entry->cq_entries	= cq_entries;
		__entry->flags		= flags;
	),

	TP_prपूर्णांकk("ring %p, fd %d sq size %d, cq size %d, flags %d",
			  __entry->ctx, __entry->fd, __entry->sq_entries,
			  __entry->cq_entries, __entry->flags)
);

/**
 * io_uring_रेजिस्टर - called after a buffer/file/eventfd was successfully
 * 					   रेजिस्टरed क्रम a ring
 *
 * @ctx:			poपूर्णांकer to a ring context काष्ठाure
 * @opcode:			describes which operation to perक्रमm
 * @nr_user_files:	number of रेजिस्टरed files
 * @nr_user_bufs:	number of रेजिस्टरed buffers
 * @cq_ev_fd:		whether eventfs रेजिस्टरed or not
 * @ret:			वापस code
 *
 * Allows to trace fixed files/buffers/eventfds, that could be रेजिस्टरed to
 * aव्योम an overhead of getting references to them क्रम every operation. This
 * event, together with io_uring_file_get, can provide a full picture of how
 * much overhead one can reduce via fixing.
 */
TRACE_EVENT(io_uring_रेजिस्टर,

	TP_PROTO(व्योम *ctx, अचिन्हित opcode, अचिन्हित nr_files,
			 अचिन्हित nr_bufs, bool eventfd, दीर्घ ret),

	TP_ARGS(ctx, opcode, nr_files, nr_bufs, eventfd, ret),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx			)
		__field(  अचिन्हित,	opcode		)
		__field(  अचिन्हित,	nr_files	)
		__field(  अचिन्हित,	nr_bufs		)
		__field(  bool,		eventfd		)
		__field(  दीर्घ,		ret			)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->opcode		= opcode;
		__entry->nr_files	= nr_files;
		__entry->nr_bufs	= nr_bufs;
		__entry->eventfd	= eventfd;
		__entry->ret		= ret;
	),

	TP_prपूर्णांकk("ring %p, opcode %d, nr_user_files %d, nr_user_bufs %d, "
			  "eventfd %d, ret %ld",
			  __entry->ctx, __entry->opcode, __entry->nr_files,
			  __entry->nr_bufs, __entry->eventfd, __entry->ret)
);

/**
 * io_uring_file_get - called beक्रमe getting references to an SQE file
 *
 * @ctx:	poपूर्णांकer to a ring context काष्ठाure
 * @fd:		SQE file descriptor
 *
 * Allows to trace out how often an SQE file reference is obtained, which can
 * help figuring out अगर it makes sense to use fixed files, or check that fixed
 * files are used correctly.
 */
TRACE_EVENT(io_uring_file_get,

	TP_PROTO(व्योम *ctx, पूर्णांक fd),

	TP_ARGS(ctx, fd),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx	)
		__field(  पूर्णांक,		fd	)
	),

	TP_fast_assign(
		__entry->ctx	= ctx;
		__entry->fd		= fd;
	),

	TP_prपूर्णांकk("ring %p, fd %d", __entry->ctx, __entry->fd)
);

/**
 * io_uring_queue_async_work - called beक्रमe submitting a new async work
 *
 * @ctx:	poपूर्णांकer to a ring context काष्ठाure
 * @hashed:	type of workqueue, hashed or normal
 * @req:	poपूर्णांकer to a submitted request
 * @work:	poपूर्णांकer to a submitted io_wq_work
 *
 * Allows to trace asynchronous work submission.
 */
TRACE_EVENT(io_uring_queue_async_work,

	TP_PROTO(व्योम *ctx, पूर्णांक rw, व्योम * req, काष्ठा io_wq_work *work,
			 अचिन्हित पूर्णांक flags),

	TP_ARGS(ctx, rw, req, work, flags),

	TP_STRUCT__entry (
		__field(  व्योम *,				ctx		)
		__field(  पूर्णांक,					rw		)
		__field(  व्योम *,				req		)
		__field(  काष्ठा io_wq_work *,		work	)
		__field(  अचिन्हित पूर्णांक,			flags	)
	),

	TP_fast_assign(
		__entry->ctx	= ctx;
		__entry->rw		= rw;
		__entry->req	= req;
		__entry->work	= work;
		__entry->flags	= flags;
	),

	TP_prपूर्णांकk("ring %p, request %p, flags %d, %s queue, work %p",
			  __entry->ctx, __entry->req, __entry->flags,
			  __entry->rw ? "hashed" : "normal", __entry->work)
);

/**
 * io_uring_defer - called when an io_uring request is deferred
 *
 * @ctx:	poपूर्णांकer to a ring context काष्ठाure
 * @req:	poपूर्णांकer to a deferred request
 * @user_data:	user data associated with the request
 *
 * Allows to track deferred requests, to get an insight about what requests are
 * not started immediately.
 */
TRACE_EVENT(io_uring_defer,

	TP_PROTO(व्योम *ctx, व्योम *req, अचिन्हित दीर्घ दीर्घ user_data),

	TP_ARGS(ctx, req, user_data),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx		)
		__field(  व्योम *,	req		)
		__field(  अचिन्हित दीर्घ दीर्घ, data	)
	),

	TP_fast_assign(
		__entry->ctx	= ctx;
		__entry->req	= req;
		__entry->data	= user_data;
	),

	TP_prपूर्णांकk("ring %p, request %p user_data %llu", __entry->ctx,
			__entry->req, __entry->data)
);

/**
 * io_uring_link - called beक्रमe the io_uring request added पूर्णांकo link_list of
 * 				   another request
 *
 * @ctx:			poपूर्णांकer to a ring context काष्ठाure
 * @req:			poपूर्णांकer to a linked request
 * @target_req:		poपूर्णांकer to a previous request, that would contain @req
 *
 * Allows to track linked requests, to understand dependencies between requests
 * and how करोes it influence their execution flow.
 */
TRACE_EVENT(io_uring_link,

	TP_PROTO(व्योम *ctx, व्योम *req, व्योम *target_req),

	TP_ARGS(ctx, req, target_req),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx			)
		__field(  व्योम *,	req			)
		__field(  व्योम *,	target_req	)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->req		= req;
		__entry->target_req	= target_req;
	),

	TP_prपूर्णांकk("ring %p, request %p linked after %p",
			  __entry->ctx, __entry->req, __entry->target_req)
);

/**
 * io_uring_cqring_रुको - called beक्रमe start रुकोing क्रम an available CQE
 *
 * @ctx:		poपूर्णांकer to a ring context काष्ठाure
 * @min_events:	minimal number of events to रुको क्रम
 *
 * Allows to track रुकोing क्रम CQE, so that we can e.g. troubleshoot
 * situations, when an application wants to रुको क्रम an event, that never
 * comes.
 */
TRACE_EVENT(io_uring_cqring_रुको,

	TP_PROTO(व्योम *ctx, पूर्णांक min_events),

	TP_ARGS(ctx, min_events),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx			)
		__field(  पूर्णांक,		min_events	)
	),

	TP_fast_assign(
		__entry->ctx	= ctx;
		__entry->min_events	= min_events;
	),

	TP_prपूर्णांकk("ring %p, min_events %d", __entry->ctx, __entry->min_events)
);

/**
 * io_uring_fail_link - called beक्रमe failing a linked request
 *
 * @req:	request, which links were cancelled
 * @link:	cancelled link
 *
 * Allows to track linked requests cancellation, to see not only that some work
 * was cancelled, but also which request was the reason.
 */
TRACE_EVENT(io_uring_fail_link,

	TP_PROTO(व्योम *req, व्योम *link),

	TP_ARGS(req, link),

	TP_STRUCT__entry (
		__field(  व्योम *,	req		)
		__field(  व्योम *,	link	)
	),

	TP_fast_assign(
		__entry->req	= req;
		__entry->link	= link;
	),

	TP_prपूर्णांकk("request %p, link %p", __entry->req, __entry->link)
);

/**
 * io_uring_complete - called when completing an SQE
 *
 * @ctx:		poपूर्णांकer to a ring context काष्ठाure
 * @user_data:		user data associated with the request
 * @res:		result of the request
 * @cflags:		completion flags
 *
 */
TRACE_EVENT(io_uring_complete,

	TP_PROTO(व्योम *ctx, u64 user_data, दीर्घ res, अचिन्हित cflags),

	TP_ARGS(ctx, user_data, res, cflags),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx		)
		__field(  u64,		user_data	)
		__field(  दीर्घ,		res		)
		__field(  अचिन्हित,	cflags		)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->user_data	= user_data;
		__entry->res		= res;
		__entry->cflags		= cflags;
	),

	TP_prपूर्णांकk("ring %p, user_data 0x%llx, result %ld, cflags %x",
			  __entry->ctx, (अचिन्हित दीर्घ दीर्घ)__entry->user_data,
			  __entry->res, __entry->cflags)
);


/**
 * io_uring_submit_sqe - called beक्रमe submitting one SQE
 *
 * @ctx:		poपूर्णांकer to a ring context काष्ठाure
 * @opcode:		opcode of request
 * @user_data:		user data associated with the request
 * @क्रमce_nonblock:	whether a context blocking or not
 * @sq_thपढ़ो:		true अगर sq_thपढ़ो has submitted this SQE
 *
 * Allows to track SQE submitting, to understand what was the source of it, SQ
 * thपढ़ो or io_uring_enter call.
 */
TRACE_EVENT(io_uring_submit_sqe,

	TP_PROTO(व्योम *ctx, u8 opcode, u64 user_data, bool क्रमce_nonblock,
		 bool sq_thपढ़ो),

	TP_ARGS(ctx, opcode, user_data, क्रमce_nonblock, sq_thपढ़ो),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx		)
		__field(  u8,		opcode		)
		__field(  u64,		user_data	)
		__field(  bool,		क्रमce_nonblock	)
		__field(  bool,		sq_thपढ़ो	)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->opcode		= opcode;
		__entry->user_data	= user_data;
		__entry->क्रमce_nonblock	= क्रमce_nonblock;
		__entry->sq_thपढ़ो	= sq_thपढ़ो;
	),

	TP_prपूर्णांकk("ring %p, op %d, data 0x%llx, non block %d, sq_thread %d",
			  __entry->ctx, __entry->opcode,
			  (अचिन्हित दीर्घ दीर्घ) __entry->user_data,
			  __entry->क्रमce_nonblock, __entry->sq_thपढ़ो)
);

TRACE_EVENT(io_uring_poll_arm,

	TP_PROTO(व्योम *ctx, u8 opcode, u64 user_data, पूर्णांक mask, पूर्णांक events),

	TP_ARGS(ctx, opcode, user_data, mask, events),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx		)
		__field(  u8,		opcode		)
		__field(  u64,		user_data	)
		__field(  पूर्णांक,		mask		)
		__field(  पूर्णांक,		events		)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->opcode		= opcode;
		__entry->user_data	= user_data;
		__entry->mask		= mask;
		__entry->events		= events;
	),

	TP_prपूर्णांकk("ring %p, op %d, data 0x%llx, mask 0x%x, events 0x%x",
			  __entry->ctx, __entry->opcode,
			  (अचिन्हित दीर्घ दीर्घ) __entry->user_data,
			  __entry->mask, __entry->events)
);

TRACE_EVENT(io_uring_poll_wake,

	TP_PROTO(व्योम *ctx, u8 opcode, u64 user_data, पूर्णांक mask),

	TP_ARGS(ctx, opcode, user_data, mask),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx		)
		__field(  u8,		opcode		)
		__field(  u64,		user_data	)
		__field(  पूर्णांक,		mask		)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->opcode		= opcode;
		__entry->user_data	= user_data;
		__entry->mask		= mask;
	),

	TP_prपूर्णांकk("ring %p, op %d, data 0x%llx, mask 0x%x",
			  __entry->ctx, __entry->opcode,
			  (अचिन्हित दीर्घ दीर्घ) __entry->user_data,
			  __entry->mask)
);

TRACE_EVENT(io_uring_task_add,

	TP_PROTO(व्योम *ctx, u8 opcode, u64 user_data, पूर्णांक mask),

	TP_ARGS(ctx, opcode, user_data, mask),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx		)
		__field(  u8,		opcode		)
		__field(  u64,		user_data	)
		__field(  पूर्णांक,		mask		)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->opcode		= opcode;
		__entry->user_data	= user_data;
		__entry->mask		= mask;
	),

	TP_prपूर्णांकk("ring %p, op %d, data 0x%llx, mask %x",
			  __entry->ctx, __entry->opcode,
			  (अचिन्हित दीर्घ दीर्घ) __entry->user_data,
			  __entry->mask)
);

TRACE_EVENT(io_uring_task_run,

	TP_PROTO(व्योम *ctx, u8 opcode, u64 user_data),

	TP_ARGS(ctx, opcode, user_data),

	TP_STRUCT__entry (
		__field(  व्योम *,	ctx		)
		__field(  u8,		opcode		)
		__field(  u64,		user_data	)
	),

	TP_fast_assign(
		__entry->ctx		= ctx;
		__entry->opcode		= opcode;
		__entry->user_data	= user_data;
	),

	TP_prपूर्णांकk("ring %p, op %d, data 0x%llx",
			  __entry->ctx, __entry->opcode,
			  (अचिन्हित दीर्घ दीर्घ) __entry->user_data)
);

#पूर्ण_अगर /* _TRACE_IO_URING_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
