<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rseq

#अगर !defined(_TRACE_RSEQ_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RSEQ_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/types.h>

TRACE_EVENT(rseq_update,

	TP_PROTO(काष्ठा task_काष्ठा *t),

	TP_ARGS(t),

	TP_STRUCT__entry(
		__field(s32, cpu_id)
	),

	TP_fast_assign(
		__entry->cpu_id = raw_smp_processor_id();
	),

	TP_prपूर्णांकk("cpu_id=%d", __entry->cpu_id)
);

TRACE_EVENT(rseq_ip_fixup,

	TP_PROTO(अचिन्हित दीर्घ regs_ip, अचिन्हित दीर्घ start_ip,
		अचिन्हित दीर्घ post_commit_offset, अचिन्हित दीर्घ पात_ip),

	TP_ARGS(regs_ip, start_ip, post_commit_offset, पात_ip),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, regs_ip)
		__field(अचिन्हित दीर्घ, start_ip)
		__field(अचिन्हित दीर्घ, post_commit_offset)
		__field(अचिन्हित दीर्घ, पात_ip)
	),

	TP_fast_assign(
		__entry->regs_ip = regs_ip;
		__entry->start_ip = start_ip;
		__entry->post_commit_offset = post_commit_offset;
		__entry->पात_ip = पात_ip;
	),

	TP_prपूर्णांकk("regs_ip=0x%lx start_ip=0x%lx post_commit_offset=%lu abort_ip=0x%lx",
		__entry->regs_ip, __entry->start_ip,
		__entry->post_commit_offset, __entry->पात_ip)
);

#पूर्ण_अगर /* _TRACE_SOCK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
