<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
// Copyright 2017 IBM Corp.
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ocxl

#अगर !defined(_TRACE_OCXL_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_OCXL_H

#समावेश <linux/tracepoपूर्णांक.h>


TRACE_EVENT(ocxl_mmu_notअगरier_range,
	TP_PROTO(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, अचिन्हित दीर्घ pidr),
	TP_ARGS(start, end, pidr),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, start)
		__field(अचिन्हित दीर्घ, end)
		__field(अचिन्हित दीर्घ, pidr)
	),

	TP_fast_assign(
		__entry->start = start;
		__entry->end = end;
		__entry->pidr = pidr;
	),

	TP_prपूर्णांकk("start=0x%lx end=0x%lx pidr=0x%lx",
		__entry->start,
		__entry->end,
		__entry->pidr
	)
);

TRACE_EVENT(ocxl_init_mmu_notअगरier,
	TP_PROTO(पूर्णांक pasid, अचिन्हित दीर्घ pidr),
	TP_ARGS(pasid, pidr),

	TP_STRUCT__entry(
		__field(पूर्णांक, pasid)
		__field(अचिन्हित दीर्घ, pidr)
	),

	TP_fast_assign(
		__entry->pasid = pasid;
		__entry->pidr = pidr;
	),

	TP_prपूर्णांकk("pasid=%d, pidr=0x%lx",
		__entry->pasid,
		__entry->pidr
	)
);

TRACE_EVENT(ocxl_release_mmu_notअगरier,
	TP_PROTO(पूर्णांक pasid, अचिन्हित दीर्घ pidr),
	TP_ARGS(pasid, pidr),

	TP_STRUCT__entry(
		__field(पूर्णांक, pasid)
		__field(अचिन्हित दीर्घ, pidr)
	),

	TP_fast_assign(
		__entry->pasid = pasid;
		__entry->pidr = pidr;
	),

	TP_prपूर्णांकk("pasid=%d, pidr=0x%lx",
		__entry->pasid,
		__entry->pidr
	)
);

DECLARE_EVENT_CLASS(ocxl_context,
	TP_PROTO(pid_t pid, व्योम *spa, पूर्णांक pasid, u32 pidr, u32 tidr),
	TP_ARGS(pid, spa, pasid, pidr, tidr),

	TP_STRUCT__entry(
		__field(pid_t, pid)
		__field(व्योम*, spa)
		__field(पूर्णांक, pasid)
		__field(u32, pidr)
		__field(u32, tidr)
	),

	TP_fast_assign(
		__entry->pid = pid;
		__entry->spa = spa;
		__entry->pasid = pasid;
		__entry->pidr = pidr;
		__entry->tidr = tidr;
	),

	TP_prपूर्णांकk("linux pid=%d spa=0x%p pasid=0x%x pidr=0x%x tidr=0x%x",
		__entry->pid,
		__entry->spa,
		__entry->pasid,
		__entry->pidr,
		__entry->tidr
	)
);

DEFINE_EVENT(ocxl_context, ocxl_context_add,
	TP_PROTO(pid_t pid, व्योम *spa, पूर्णांक pasid, u32 pidr, u32 tidr),
	TP_ARGS(pid, spa, pasid, pidr, tidr)
);

DEFINE_EVENT(ocxl_context, ocxl_context_हटाओ,
	TP_PROTO(pid_t pid, व्योम *spa, पूर्णांक pasid, u32 pidr, u32 tidr),
	TP_ARGS(pid, spa, pasid, pidr, tidr)
);

TRACE_EVENT(ocxl_terminate_pasid,
	TP_PROTO(पूर्णांक pasid, पूर्णांक rc),
	TP_ARGS(pasid, rc),

	TP_STRUCT__entry(
		__field(पूर्णांक, pasid)
		__field(पूर्णांक, rc)
	),

	TP_fast_assign(
		__entry->pasid = pasid;
		__entry->rc = rc;
	),

	TP_prपूर्णांकk("pasid=0x%x rc=%d",
		__entry->pasid,
		__entry->rc
	)
);

DECLARE_EVENT_CLASS(ocxl_fault_handler,
	TP_PROTO(व्योम *spa, u64 pe, u64 dsisr, u64 dar, u64 tfc),
	TP_ARGS(spa, pe, dsisr, dar, tfc),

	TP_STRUCT__entry(
		__field(व्योम *, spa)
		__field(u64, pe)
		__field(u64, dsisr)
		__field(u64, dar)
		__field(u64, tfc)
	),

	TP_fast_assign(
		__entry->spa = spa;
		__entry->pe = pe;
		__entry->dsisr = dsisr;
		__entry->dar = dar;
		__entry->tfc = tfc;
	),

	TP_prपूर्णांकk("spa=%p pe=0x%llx dsisr=0x%llx dar=0x%llx tfc=0x%llx",
		__entry->spa,
		__entry->pe,
		__entry->dsisr,
		__entry->dar,
		__entry->tfc
	)
);

DEFINE_EVENT(ocxl_fault_handler, ocxl_fault,
	TP_PROTO(व्योम *spa, u64 pe, u64 dsisr, u64 dar, u64 tfc),
	TP_ARGS(spa, pe, dsisr, dar, tfc)
);

DEFINE_EVENT(ocxl_fault_handler, ocxl_fault_ack,
	TP_PROTO(व्योम *spa, u64 pe, u64 dsisr, u64 dar, u64 tfc),
	TP_ARGS(spa, pe, dsisr, dar, tfc)
);

TRACE_EVENT(ocxl_afu_irq_alloc,
	TP_PROTO(पूर्णांक pasid, पूर्णांक irq_id, अचिन्हित पूर्णांक virq, पूर्णांक hw_irq),
	TP_ARGS(pasid, irq_id, virq, hw_irq),

	TP_STRUCT__entry(
		__field(पूर्णांक, pasid)
		__field(पूर्णांक, irq_id)
		__field(अचिन्हित पूर्णांक, virq)
		__field(पूर्णांक, hw_irq)
	),

	TP_fast_assign(
		__entry->pasid = pasid;
		__entry->irq_id = irq_id;
		__entry->virq = virq;
		__entry->hw_irq = hw_irq;
	),

	TP_prपूर्णांकk("pasid=0x%x irq_id=%d virq=%u hw_irq=%d",
		__entry->pasid,
		__entry->irq_id,
		__entry->virq,
		__entry->hw_irq
	)
);

TRACE_EVENT(ocxl_afu_irq_मुक्त,
	TP_PROTO(पूर्णांक pasid, पूर्णांक irq_id),
	TP_ARGS(pasid, irq_id),

	TP_STRUCT__entry(
		__field(पूर्णांक, pasid)
		__field(पूर्णांक, irq_id)
	),

	TP_fast_assign(
		__entry->pasid = pasid;
		__entry->irq_id = irq_id;
	),

	TP_prपूर्णांकk("pasid=0x%x irq_id=%d",
		__entry->pasid,
		__entry->irq_id
	)
);

TRACE_EVENT(ocxl_afu_irq_receive,
	TP_PROTO(पूर्णांक virq),
	TP_ARGS(virq),

	TP_STRUCT__entry(
		__field(पूर्णांक, virq)
	),

	TP_fast_assign(
		__entry->virq = virq;
	),

	TP_prपूर्णांकk("virq=%d",
		__entry->virq
	)
);

#पूर्ण_अगर /* _TRACE_OCXL_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
