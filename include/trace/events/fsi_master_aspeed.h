<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fsi_master_aspeed

#अगर !defined(_TRACE_FSI_MASTER_ASPEED_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FSI_MASTER_ASPEED_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(fsi_master_aspeed_opb_पढ़ो,
	TP_PROTO(uपूर्णांक32_t addr, माप_प्रकार size, uपूर्णांक32_t result, uपूर्णांक32_t status, uपूर्णांक32_t irq_status),
	TP_ARGS(addr, size, result, status, irq_status),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t,  addr)
		__field(माप_प्रकार,    size)
		__field(uपूर्णांक32_t,  result)
		__field(uपूर्णांक32_t,  status)
		__field(uपूर्णांक32_t,  irq_status)
		),
	TP_fast_assign(
		__entry->addr = addr;
		__entry->size = size;
		__entry->result = result;
		__entry->status = status;
		__entry->irq_status = irq_status;
		),
	TP_prपूर्णांकk("addr %08x size %zu: result %08x sts: %08x irq_sts: %08x",
		__entry->addr, __entry->size, __entry->result,
		__entry->status, __entry->irq_status
	   )
);

TRACE_EVENT(fsi_master_aspeed_opb_ग_लिखो,
	TP_PROTO(uपूर्णांक32_t addr, uपूर्णांक32_t val, माप_प्रकार size, uपूर्णांक32_t status, uपूर्णांक32_t irq_status),
	TP_ARGS(addr, val, size, status, irq_status),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t,    addr)
		__field(uपूर्णांक32_t,    val)
		__field(माप_प्रकार,    size)
		__field(uपूर्णांक32_t,  status)
		__field(uपूर्णांक32_t,  irq_status)
		),
	TP_fast_assign(
		__entry->addr = addr;
		__entry->val = val;
		__entry->size = size;
		__entry->status = status;
		__entry->irq_status = irq_status;
		),
	TP_prपूर्णांकk("addr %08x val %08x size %zu status: %08x irq_sts: %08x",
		__entry->addr, __entry->val, __entry->size,
		__entry->status, __entry->irq_status
		)
	);

TRACE_EVENT(fsi_master_aspeed_opb_error,
	TP_PROTO(uपूर्णांक32_t mresp0, uपूर्णांक32_t mstap0, uपूर्णांक32_t mesrb0),
	TP_ARGS(mresp0, mstap0, mesrb0),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t,  mresp0)
		__field(uपूर्णांक32_t,  mstap0)
		__field(uपूर्णांक32_t,  mesrb0)
		),
	TP_fast_assign(
		__entry->mresp0 = mresp0;
		__entry->mstap0 = mstap0;
		__entry->mesrb0 = mesrb0;
		),
	TP_prपूर्णांकk("mresp0 %08x mstap0 %08x mesrb0 %08x",
		__entry->mresp0, __entry->mstap0, __entry->mesrb0
		)
	);

#पूर्ण_अगर

#समावेश <trace/define_trace.h>
