<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM घातerpc

#अगर !defined(_TRACE_POWERPC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_POWERPC_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा pt_regs;

DECLARE_EVENT_CLASS(ppc64_पूर्णांकerrupt_class,

	TP_PROTO(काष्ठा pt_regs *regs),

	TP_ARGS(regs),

	TP_STRUCT__entry(
		__field(काष्ठा pt_regs *, regs)
	),

	TP_fast_assign(
		__entry->regs = regs;
	),

	TP_prपूर्णांकk("pt_regs=%p", __entry->regs)
);

DEFINE_EVENT(ppc64_पूर्णांकerrupt_class, irq_entry,

	TP_PROTO(काष्ठा pt_regs *regs),

	TP_ARGS(regs)
);

DEFINE_EVENT(ppc64_पूर्णांकerrupt_class, irq_निकास,

	TP_PROTO(काष्ठा pt_regs *regs),

	TP_ARGS(regs)
);

DEFINE_EVENT(ppc64_पूर्णांकerrupt_class, समयr_पूर्णांकerrupt_entry,

	TP_PROTO(काष्ठा pt_regs *regs),

	TP_ARGS(regs)
);

DEFINE_EVENT(ppc64_पूर्णांकerrupt_class, समयr_पूर्णांकerrupt_निकास,

	TP_PROTO(काष्ठा pt_regs *regs),

	TP_ARGS(regs)
);

#अगर_घोषित CONFIG_PPC_DOORBELL
DEFINE_EVENT(ppc64_पूर्णांकerrupt_class, करोorbell_entry,

	TP_PROTO(काष्ठा pt_regs *regs),

	TP_ARGS(regs)
);

DEFINE_EVENT(ppc64_पूर्णांकerrupt_class, करोorbell_निकास,

	TP_PROTO(काष्ठा pt_regs *regs),

	TP_ARGS(regs)
);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PSERIES
बाह्य पूर्णांक hcall_tracepoपूर्णांक_regfunc(व्योम);
बाह्य व्योम hcall_tracepoपूर्णांक_unregfunc(व्योम);

TRACE_EVENT_FN_COND(hcall_entry,

	TP_PROTO(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *args),

	TP_ARGS(opcode, args),

	TP_CONDITION(cpu_online(raw_smp_processor_id())),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, opcode)
	),

	TP_fast_assign(
		__entry->opcode = opcode;
	),

	TP_prपूर्णांकk("opcode=%lu", __entry->opcode),

	hcall_tracepoपूर्णांक_regfunc, hcall_tracepoपूर्णांक_unregfunc
);

TRACE_EVENT_FN_COND(hcall_निकास,

	TP_PROTO(अचिन्हित दीर्घ opcode, दीर्घ retval, अचिन्हित दीर्घ *retbuf),

	TP_ARGS(opcode, retval, retbuf),

	TP_CONDITION(cpu_online(raw_smp_processor_id())),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, opcode)
		__field(दीर्घ, retval)
	),

	TP_fast_assign(
		__entry->opcode = opcode;
		__entry->retval = retval;
	),

	TP_prपूर्णांकk("opcode=%lu retval=%ld", __entry->opcode, __entry->retval),

	hcall_tracepoपूर्णांक_regfunc, hcall_tracepoपूर्णांक_unregfunc
);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_POWERNV
बाह्य पूर्णांक opal_tracepoपूर्णांक_regfunc(व्योम);
बाह्य व्योम opal_tracepoपूर्णांक_unregfunc(व्योम);

TRACE_EVENT_FN(opal_entry,

	TP_PROTO(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *args),

	TP_ARGS(opcode, args),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, opcode)
	),

	TP_fast_assign(
		__entry->opcode = opcode;
	),

	TP_prपूर्णांकk("opcode=%lu", __entry->opcode),

	opal_tracepoपूर्णांक_regfunc, opal_tracepoपूर्णांक_unregfunc
);

TRACE_EVENT_FN(opal_निकास,

	TP_PROTO(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ retval),

	TP_ARGS(opcode, retval),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, opcode)
		__field(अचिन्हित दीर्घ, retval)
	),

	TP_fast_assign(
		__entry->opcode = opcode;
		__entry->retval = retval;
	),

	TP_prपूर्णांकk("opcode=%lu retval=%lu", __entry->opcode, __entry->retval),

	opal_tracepoपूर्णांक_regfunc, opal_tracepoपूर्णांक_unregfunc
);
#पूर्ण_अगर

TRACE_EVENT(hash_fault,

	    TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ access, अचिन्हित दीर्घ trap),
	    TP_ARGS(addr, access, trap),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, addr)
		    __field(अचिन्हित दीर्घ, access)
		    __field(अचिन्हित दीर्घ, trap)
		    ),

	    TP_fast_assign(
		    __entry->addr = addr;
		    __entry->access = access;
		    __entry->trap = trap;
		    ),

	    TP_prपूर्णांकk("hash fault with addr 0x%lx and access = 0x%lx trap = 0x%lx",
		      __entry->addr, __entry->access, __entry->trap)
);


TRACE_EVENT(tlbie,

	TP_PROTO(अचिन्हित दीर्घ lpid, अचिन्हित दीर्घ local, अचिन्हित दीर्घ rb,
		अचिन्हित दीर्घ rs, अचिन्हित दीर्घ ric, अचिन्हित दीर्घ prs,
		अचिन्हित दीर्घ r),
	TP_ARGS(lpid, local, rb, rs, ric, prs, r),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, lpid)
		__field(अचिन्हित दीर्घ, local)
		__field(अचिन्हित दीर्घ, rb)
		__field(अचिन्हित दीर्घ, rs)
		__field(अचिन्हित दीर्घ, ric)
		__field(अचिन्हित दीर्घ, prs)
		__field(अचिन्हित दीर्घ, r)
		),

	TP_fast_assign(
		__entry->lpid = lpid;
		__entry->local = local;
		__entry->rb = rb;
		__entry->rs = rs;
		__entry->ric = ric;
		__entry->prs = prs;
		__entry->r = r;
		),

	TP_prपूर्णांकk("lpid=%ld, local=%ld, rb=0x%lx, rs=0x%lx, ric=0x%lx, "
		"prs=0x%lx, r=0x%lx", __entry->lpid, __entry->local,
		__entry->rb, __entry->rs, __entry->ric, __entry->prs,
		__entry->r)
);

TRACE_EVENT(tlbia,

	TP_PROTO(अचिन्हित दीर्घ id),
	TP_ARGS(id),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, id)
		),

	TP_fast_assign(
		__entry->id = id;
		),

	TP_prपूर्णांकk("ctx.id=0x%lx", __entry->id)
);

#पूर्ण_अगर /* _TRACE_POWERPC_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता

#घोषणा TRACE_INCLUDE_PATH यंत्र
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
