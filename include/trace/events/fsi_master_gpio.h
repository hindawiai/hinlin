<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fsi_master_gpio

#अगर !defined(_TRACE_FSI_MASTER_GPIO_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FSI_MASTER_GPIO_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(fsi_master_gpio_in,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master, पूर्णांक bits, uपूर्णांक64_t msg),
	TP_ARGS(master, bits, msg),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	bits)
		__field(uपूर्णांक64_t, msg)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->bits = bits;
		__entry->msg  = msg & ((1ull<<bits) - 1);
	),
	TP_prपूर्णांकk("fsi-gpio%d => %0*llx[%d]",
		__entry->master_idx,
		(__entry->bits + 3) / 4,
		__entry->msg,
		__entry->bits
	)
);

TRACE_EVENT(fsi_master_gpio_out,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master, पूर्णांक bits, uपूर्णांक64_t msg),
	TP_ARGS(master, bits, msg),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	bits)
		__field(uपूर्णांक64_t, msg)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->bits = bits;
		__entry->msg  = msg & ((1ull<<bits) - 1);
	),
	TP_prपूर्णांकk("fsi-gpio%d <= %0*llx[%d]",
		__entry->master_idx,
		(__entry->bits + 3) / 4,
		__entry->msg,
		__entry->bits
	)
);

TRACE_EVENT(fsi_master_gpio_घड़ी_zeros,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master, पूर्णांक घड़ीs),
	TP_ARGS(master, घड़ीs),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	घड़ीs)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->घड़ीs = घड़ीs;
	),
	TP_prपूर्णांकk("fsi-gpio%d clock %d zeros",
		  __entry->master_idx, __entry->घड़ीs
	)
);

TRACE_EVENT(fsi_master_gpio_अवरोध,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master),
	TP_ARGS(master),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
	),
	TP_prपूर्णांकk("fsi-gpio%d ----break---",
		__entry->master_idx
	)
);

TRACE_EVENT(fsi_master_gpio_crc_cmd_error,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master),
	TP_ARGS(master),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
	),
	TP_prपूर्णांकk("fsi-gpio%d ----CRC command retry---",
		__entry->master_idx
	)
);

TRACE_EVENT(fsi_master_gpio_crc_rsp_error,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master),
	TP_ARGS(master),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
	),
	TP_prपूर्णांकk("fsi-gpio%d ----CRC response---",
		__entry->master_idx
	)
);

TRACE_EVENT(fsi_master_gpio_poll_response_busy,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master, पूर्णांक busy),
	TP_ARGS(master, busy),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	busy)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->busy = busy;
	),
	TP_prपूर्णांकk("fsi-gpio%d: device reported busy %d times",
		__entry->master_idx, __entry->busy)
);

TRACE_EVENT(fsi_master_gpio_cmd_असल_addr,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master, u32 addr),
	TP_ARGS(master, addr),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(u32,	addr)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->addr = addr;
	),
	TP_prपूर्णांकk("fsi-gpio%d: Sending ABS_ADR %06x",
		__entry->master_idx, __entry->addr)
);

TRACE_EVENT(fsi_master_gpio_cmd_rel_addr,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master, u32 rel_addr),
	TP_ARGS(master, rel_addr),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(u32,	rel_addr)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->rel_addr = rel_addr;
	),
	TP_prपूर्णांकk("fsi-gpio%d: Sending REL_ADR %03x",
		__entry->master_idx, __entry->rel_addr)
);

TRACE_EVENT(fsi_master_gpio_cmd_same_addr,
	TP_PROTO(स्थिर काष्ठा fsi_master_gpio *master),
	TP_ARGS(master),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
	),
	TP_prपूर्णांकk("fsi-gpio%d: Sending SAME_ADR",
		__entry->master_idx)
);

#पूर्ण_अगर /* _TRACE_FSI_MASTER_GPIO_H */

#समावेश <trace/define_trace.h>
