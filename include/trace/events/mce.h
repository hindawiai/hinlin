<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mce

#अगर !defined(_TRACE_MCE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_MCE_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/mce.h>

TRACE_EVENT(mce_record,

	TP_PROTO(काष्ठा mce *m),

	TP_ARGS(m),

	TP_STRUCT__entry(
		__field(	u64,		mcgcap		)
		__field(	u64,		mcgstatus	)
		__field(	u64,		status		)
		__field(	u64,		addr		)
		__field(	u64,		misc		)
		__field(	u64,		synd		)
		__field(	u64,		ipid		)
		__field(	u64,		ip		)
		__field(	u64,		tsc		)
		__field(	u64,		wallसमय	)
		__field(	u32,		cpu		)
		__field(	u32,		cpuid		)
		__field(	u32,		apicid		)
		__field(	u32,		socketid	)
		__field(	u8,		cs		)
		__field(	u8,		bank		)
		__field(	u8,		cpuvenकरोr	)
	),

	TP_fast_assign(
		__entry->mcgcap		= m->mcgcap;
		__entry->mcgstatus	= m->mcgstatus;
		__entry->status		= m->status;
		__entry->addr		= m->addr;
		__entry->misc		= m->misc;
		__entry->synd		= m->synd;
		__entry->ipid		= m->ipid;
		__entry->ip		= m->ip;
		__entry->tsc		= m->tsc;
		__entry->wallसमय	= m->समय;
		__entry->cpu		= m->extcpu;
		__entry->cpuid		= m->cpuid;
		__entry->apicid		= m->apicid;
		__entry->socketid	= m->socketid;
		__entry->cs		= m->cs;
		__entry->bank		= m->bank;
		__entry->cpuvenकरोr	= m->cpuvenकरोr;
	),

	TP_prपूर्णांकk("CPU: %d, MCGc/s: %llx/%llx, MC%d: %016Lx, IPID: %016Lx, ADDR/MISC/SYND: %016Lx/%016Lx/%016Lx, RIP: %02x:<%016Lx>, TSC: %llx, PROCESSOR: %u:%x, TIME: %llu, SOCKET: %u, APIC: %x",
		__entry->cpu,
		__entry->mcgcap, __entry->mcgstatus,
		__entry->bank, __entry->status,
		__entry->ipid,
		__entry->addr, __entry->misc, __entry->synd,
		__entry->cs, __entry->ip,
		__entry->tsc,
		__entry->cpuvenकरोr, __entry->cpuid,
		__entry->wallसमय,
		__entry->socketid,
		__entry->apicid)
);

#पूर्ण_अगर /* _TRACE_MCE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
