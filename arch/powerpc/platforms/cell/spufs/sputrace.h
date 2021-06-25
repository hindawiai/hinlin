<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_SPUFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SPUFS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/stringअगरy.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM spufs

TRACE_EVENT(spufs_context,
	TP_PROTO(काष्ठा spu_context *ctx, काष्ठा spu *spu, स्थिर अक्षर *name),
	TP_ARGS(ctx, spu, name),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, name)
		__field(पूर्णांक, owner_tid)
		__field(पूर्णांक, number)
	),

	TP_fast_assign(
		__entry->name = name;
		__entry->owner_tid = ctx->tid;
		__entry->number = spu ? spu->number : -1;
	),

	TP_prपूर्णांकk("%s (ctxthread = %d, spu = %d)",
		__entry->name, __entry->owner_tid, __entry->number)
);

#घोषणा spu_context_trace(name, ctx, spu) \
	trace_spufs_context(ctx, spu, __stringअगरy(name))
#घोषणा spu_context_nospu_trace(name, ctx) \
	trace_spufs_context(ctx, शून्य, __stringअगरy(name))

#पूर्ण_अगर /* _TRACE_SPUFS_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता sputrace
#समावेश <trace/define_trace.h>
