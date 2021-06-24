<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Google, Inc.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM binder

#अगर !defined(_BINDER_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _BINDER_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा binder_buffer;
काष्ठा binder_node;
काष्ठा binder_proc;
काष्ठा binder_alloc;
काष्ठा binder_ref_data;
काष्ठा binder_thपढ़ो;
काष्ठा binder_transaction;

TRACE_EVENT(binder_ioctl,
	TP_PROTO(अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg),
	TP_ARGS(cmd, arg),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, cmd)
		__field(अचिन्हित दीर्घ, arg)
	),
	TP_fast_assign(
		__entry->cmd = cmd;
		__entry->arg = arg;
	),
	TP_prपूर्णांकk("cmd=0x%x arg=0x%lx", __entry->cmd, __entry->arg)
);

DECLARE_EVENT_CLASS(binder_lock_class,
	TP_PROTO(स्थिर अक्षर *tag),
	TP_ARGS(tag),
	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, tag)
	),
	TP_fast_assign(
		__entry->tag = tag;
	),
	TP_prपूर्णांकk("tag=%s", __entry->tag)
);

#घोषणा DEFINE_BINDER_LOCK_EVENT(name)	\
DEFINE_EVENT(binder_lock_class, name,	\
	TP_PROTO(स्थिर अक्षर *func), \
	TP_ARGS(func))

DEFINE_BINDER_LOCK_EVENT(binder_lock);
DEFINE_BINDER_LOCK_EVENT(binder_locked);
DEFINE_BINDER_LOCK_EVENT(binder_unlock);

DECLARE_EVENT_CLASS(binder_function_वापस_class,
	TP_PROTO(पूर्णांक ret),
	TP_ARGS(ret),
	TP_STRUCT__entry(
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("ret=%d", __entry->ret)
);

#घोषणा DEFINE_BINDER_FUNCTION_RETURN_EVENT(name)	\
DEFINE_EVENT(binder_function_वापस_class, name,	\
	TP_PROTO(पूर्णांक ret), \
	TP_ARGS(ret))

DEFINE_BINDER_FUNCTION_RETURN_EVENT(binder_ioctl_करोne);
DEFINE_BINDER_FUNCTION_RETURN_EVENT(binder_ग_लिखो_करोne);
DEFINE_BINDER_FUNCTION_RETURN_EVENT(binder_पढ़ो_करोne);

TRACE_EVENT(binder_रुको_क्रम_work,
	TP_PROTO(bool proc_work, bool transaction_stack, bool thपढ़ो_toकरो),
	TP_ARGS(proc_work, transaction_stack, thपढ़ो_toकरो),

	TP_STRUCT__entry(
		__field(bool, proc_work)
		__field(bool, transaction_stack)
		__field(bool, thपढ़ो_toकरो)
	),
	TP_fast_assign(
		__entry->proc_work = proc_work;
		__entry->transaction_stack = transaction_stack;
		__entry->thपढ़ो_toकरो = thपढ़ो_toकरो;
	),
	TP_prपूर्णांकk("proc_work=%d transaction_stack=%d thread_todo=%d",
		  __entry->proc_work, __entry->transaction_stack,
		  __entry->thपढ़ो_toकरो)
);

TRACE_EVENT(binder_txn_latency_मुक्त,
	TP_PROTO(काष्ठा binder_transaction *t,
		 पूर्णांक from_proc, पूर्णांक from_thपढ़ो,
		 पूर्णांक to_proc, पूर्णांक to_thपढ़ो),
	TP_ARGS(t, from_proc, from_thपढ़ो, to_proc, to_thपढ़ो),
	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(पूर्णांक, from_proc)
		__field(पूर्णांक, from_thपढ़ो)
		__field(पूर्णांक, to_proc)
		__field(पूर्णांक, to_thपढ़ो)
		__field(अचिन्हित पूर्णांक, code)
		__field(अचिन्हित पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
		__entry->from_proc = from_proc;
		__entry->from_thपढ़ो = from_thपढ़ो;
		__entry->to_proc = to_proc;
		__entry->to_thपढ़ो = to_thपढ़ो;
		__entry->code = t->code;
		__entry->flags = t->flags;
	),
	TP_prपूर्णांकk("transaction=%d from %d:%d to %d:%d flags=0x%x code=0x%x",
		  __entry->debug_id, __entry->from_proc, __entry->from_thपढ़ो,
		  __entry->to_proc, __entry->to_thपढ़ो, __entry->code,
		  __entry->flags)
);

TRACE_EVENT(binder_transaction,
	TP_PROTO(bool reply, काष्ठा binder_transaction *t,
		 काष्ठा binder_node *target_node),
	TP_ARGS(reply, t, target_node),
	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(पूर्णांक, target_node)
		__field(पूर्णांक, to_proc)
		__field(पूर्णांक, to_thपढ़ो)
		__field(पूर्णांक, reply)
		__field(अचिन्हित पूर्णांक, code)
		__field(अचिन्हित पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
		__entry->target_node = target_node ? target_node->debug_id : 0;
		__entry->to_proc = t->to_proc->pid;
		__entry->to_thपढ़ो = t->to_thपढ़ो ? t->to_thपढ़ो->pid : 0;
		__entry->reply = reply;
		__entry->code = t->code;
		__entry->flags = t->flags;
	),
	TP_prपूर्णांकk("transaction=%d dest_node=%d dest_proc=%d dest_thread=%d reply=%d flags=0x%x code=0x%x",
		  __entry->debug_id, __entry->target_node,
		  __entry->to_proc, __entry->to_thपढ़ो,
		  __entry->reply, __entry->flags, __entry->code)
);

TRACE_EVENT(binder_transaction_received,
	TP_PROTO(काष्ठा binder_transaction *t),
	TP_ARGS(t),

	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
	),
	TP_prपूर्णांकk("transaction=%d", __entry->debug_id)
);

TRACE_EVENT(binder_transaction_node_to_ref,
	TP_PROTO(काष्ठा binder_transaction *t, काष्ठा binder_node *node,
		 काष्ठा binder_ref_data *rdata),
	TP_ARGS(t, node, rdata),

	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(पूर्णांक, node_debug_id)
		__field(binder_uपूर्णांकptr_t, node_ptr)
		__field(पूर्णांक, ref_debug_id)
		__field(uपूर्णांक32_t, ref_desc)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
		__entry->node_debug_id = node->debug_id;
		__entry->node_ptr = node->ptr;
		__entry->ref_debug_id = rdata->debug_id;
		__entry->ref_desc = rdata->desc;
	),
	TP_prपूर्णांकk("transaction=%d node=%d src_ptr=0x%016llx ==> dest_ref=%d dest_desc=%d",
		  __entry->debug_id, __entry->node_debug_id,
		  (u64)__entry->node_ptr,
		  __entry->ref_debug_id, __entry->ref_desc)
);

TRACE_EVENT(binder_transaction_ref_to_node,
	TP_PROTO(काष्ठा binder_transaction *t, काष्ठा binder_node *node,
		 काष्ठा binder_ref_data *rdata),
	TP_ARGS(t, node, rdata),

	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(पूर्णांक, ref_debug_id)
		__field(uपूर्णांक32_t, ref_desc)
		__field(पूर्णांक, node_debug_id)
		__field(binder_uपूर्णांकptr_t, node_ptr)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
		__entry->ref_debug_id = rdata->debug_id;
		__entry->ref_desc = rdata->desc;
		__entry->node_debug_id = node->debug_id;
		__entry->node_ptr = node->ptr;
	),
	TP_prपूर्णांकk("transaction=%d node=%d src_ref=%d src_desc=%d ==> dest_ptr=0x%016llx",
		  __entry->debug_id, __entry->node_debug_id,
		  __entry->ref_debug_id, __entry->ref_desc,
		  (u64)__entry->node_ptr)
);

TRACE_EVENT(binder_transaction_ref_to_ref,
	TP_PROTO(काष्ठा binder_transaction *t, काष्ठा binder_node *node,
		 काष्ठा binder_ref_data *src_ref,
		 काष्ठा binder_ref_data *dest_ref),
	TP_ARGS(t, node, src_ref, dest_ref),

	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(पूर्णांक, node_debug_id)
		__field(पूर्णांक, src_ref_debug_id)
		__field(uपूर्णांक32_t, src_ref_desc)
		__field(पूर्णांक, dest_ref_debug_id)
		__field(uपूर्णांक32_t, dest_ref_desc)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
		__entry->node_debug_id = node->debug_id;
		__entry->src_ref_debug_id = src_ref->debug_id;
		__entry->src_ref_desc = src_ref->desc;
		__entry->dest_ref_debug_id = dest_ref->debug_id;
		__entry->dest_ref_desc = dest_ref->desc;
	),
	TP_prपूर्णांकk("transaction=%d node=%d src_ref=%d src_desc=%d ==> dest_ref=%d dest_desc=%d",
		  __entry->debug_id, __entry->node_debug_id,
		  __entry->src_ref_debug_id, __entry->src_ref_desc,
		  __entry->dest_ref_debug_id, __entry->dest_ref_desc)
);

TRACE_EVENT(binder_transaction_fd_send,
	TP_PROTO(काष्ठा binder_transaction *t, पूर्णांक fd, माप_प्रकार offset),
	TP_ARGS(t, fd, offset),

	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(पूर्णांक, fd)
		__field(माप_प्रकार, offset)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
		__entry->fd = fd;
		__entry->offset = offset;
	),
	TP_prपूर्णांकk("transaction=%d src_fd=%d offset=%zu",
		  __entry->debug_id, __entry->fd, __entry->offset)
);

TRACE_EVENT(binder_transaction_fd_recv,
	TP_PROTO(काष्ठा binder_transaction *t, पूर्णांक fd, माप_प्रकार offset),
	TP_ARGS(t, fd, offset),

	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(पूर्णांक, fd)
		__field(माप_प्रकार, offset)
	),
	TP_fast_assign(
		__entry->debug_id = t->debug_id;
		__entry->fd = fd;
		__entry->offset = offset;
	),
	TP_prपूर्णांकk("transaction=%d dest_fd=%d offset=%zu",
		  __entry->debug_id, __entry->fd, __entry->offset)
);

DECLARE_EVENT_CLASS(binder_buffer_class,
	TP_PROTO(काष्ठा binder_buffer *buf),
	TP_ARGS(buf),
	TP_STRUCT__entry(
		__field(पूर्णांक, debug_id)
		__field(माप_प्रकार, data_size)
		__field(माप_प्रकार, offsets_size)
		__field(माप_प्रकार, extra_buffers_size)
	),
	TP_fast_assign(
		__entry->debug_id = buf->debug_id;
		__entry->data_size = buf->data_size;
		__entry->offsets_size = buf->offsets_size;
		__entry->extra_buffers_size = buf->extra_buffers_size;
	),
	TP_prपूर्णांकk("transaction=%d data_size=%zd offsets_size=%zd extra_buffers_size=%zd",
		  __entry->debug_id, __entry->data_size, __entry->offsets_size,
		  __entry->extra_buffers_size)
);

DEFINE_EVENT(binder_buffer_class, binder_transaction_alloc_buf,
	TP_PROTO(काष्ठा binder_buffer *buffer),
	TP_ARGS(buffer));

DEFINE_EVENT(binder_buffer_class, binder_transaction_buffer_release,
	TP_PROTO(काष्ठा binder_buffer *buffer),
	TP_ARGS(buffer));

DEFINE_EVENT(binder_buffer_class, binder_transaction_failed_buffer_release,
	TP_PROTO(काष्ठा binder_buffer *buffer),
	TP_ARGS(buffer));

TRACE_EVENT(binder_update_page_range,
	TP_PROTO(काष्ठा binder_alloc *alloc, bool allocate,
		 व्योम __user *start, व्योम __user *end),
	TP_ARGS(alloc, allocate, start, end),
	TP_STRUCT__entry(
		__field(पूर्णांक, proc)
		__field(bool, allocate)
		__field(माप_प्रकार, offset)
		__field(माप_प्रकार, size)
	),
	TP_fast_assign(
		__entry->proc = alloc->pid;
		__entry->allocate = allocate;
		__entry->offset = start - alloc->buffer;
		__entry->size = end - start;
	),
	TP_prपूर्णांकk("proc=%d allocate=%d offset=%zu size=%zu",
		  __entry->proc, __entry->allocate,
		  __entry->offset, __entry->size)
);

DECLARE_EVENT_CLASS(binder_lru_page_class,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index),
	TP_STRUCT__entry(
		__field(पूर्णांक, proc)
		__field(माप_प्रकार, page_index)
	),
	TP_fast_assign(
		__entry->proc = alloc->pid;
		__entry->page_index = page_index;
	),
	TP_prपूर्णांकk("proc=%d page_index=%zu",
		  __entry->proc, __entry->page_index)
);

DEFINE_EVENT(binder_lru_page_class, binder_alloc_lru_start,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_alloc_lru_end,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_मुक्त_lru_start,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_मुक्त_lru_end,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_alloc_page_start,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_alloc_page_end,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_unmap_user_start,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_unmap_user_end,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_unmap_kernel_start,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

DEFINE_EVENT(binder_lru_page_class, binder_unmap_kernel_end,
	TP_PROTO(स्थिर काष्ठा binder_alloc *alloc, माप_प्रकार page_index),
	TP_ARGS(alloc, page_index));

TRACE_EVENT(binder_command,
	TP_PROTO(uपूर्णांक32_t cmd),
	TP_ARGS(cmd),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t, cmd)
	),
	TP_fast_assign(
		__entry->cmd = cmd;
	),
	TP_prपूर्णांकk("cmd=0x%x %s",
		  __entry->cmd,
		  _IOC_NR(__entry->cmd) < ARRAY_SIZE(binder_command_strings) ?
			  binder_command_strings[_IOC_NR(__entry->cmd)] :
			  "unknown")
);

TRACE_EVENT(binder_वापस,
	TP_PROTO(uपूर्णांक32_t cmd),
	TP_ARGS(cmd),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t, cmd)
	),
	TP_fast_assign(
		__entry->cmd = cmd;
	),
	TP_prपूर्णांकk("cmd=0x%x %s",
		  __entry->cmd,
		  _IOC_NR(__entry->cmd) < ARRAY_SIZE(binder_वापस_strings) ?
			  binder_वापस_strings[_IOC_NR(__entry->cmd)] :
			  "unknown")
);

#पूर्ण_अगर /* _BINDER_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता binder_trace
#समावेश <trace/define_trace.h>
