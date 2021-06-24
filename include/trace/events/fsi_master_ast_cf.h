<शैली गुरु>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fsi_master_ast_cf

#अगर !defined(_TRACE_FSI_MASTER_ACF_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FSI_MASTER_ACF_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(fsi_master_acf_copro_command,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master, uपूर्णांक32_t op),
	TP_ARGS(master, op),
	TP_STRUCT__entry(
		__field(पूर्णांक,		master_idx)
		__field(uपूर्णांक32_t,	op)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->op = op;
	),
	TP_prपूर्णांकk("fsi-acf%d command %08x",
		  __entry->master_idx, __entry->op
	)
);

TRACE_EVENT(fsi_master_acf_send_request,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master, स्थिर काष्ठा fsi_msg *cmd, u8 rbits),
	TP_ARGS(master, cmd, rbits),
	TP_STRUCT__entry(
		__field(पूर्णांक,		master_idx)
		__field(uपूर्णांक64_t,	msg)
		__field(u8,		bits)
		__field(u8,		rbits)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->msg = cmd->msg;
		__entry->bits = cmd->bits;
		__entry->rbits = rbits;
	),
	TP_prपूर्णांकk("fsi-acf%d cmd: %016llx/%d/%d",
		__entry->master_idx, (अचिन्हित दीर्घ दीर्घ)__entry->msg,
		__entry->bits, __entry->rbits
	)
);

TRACE_EVENT(fsi_master_acf_copro_response,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master, u8 rtag, u8 rcrc, __be32 rdata, bool crc_ok),
	TP_ARGS(master, rtag, rcrc, rdata, crc_ok),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(u8,	rtag)
		__field(u8,	rcrc)
		__field(u32,    rdata)
		__field(bool,   crc_ok)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->rtag = rtag;
		__entry->rcrc = rcrc;
		__entry->rdata = be32_to_cpu(rdata);
		__entry->crc_ok = crc_ok;
	),
	TP_prपूर्णांकk("fsi-acf%d rsp: tag=%04x crc=%04x data=%08x %c\n",
		__entry->master_idx, __entry->rtag, __entry->rcrc,
		__entry->rdata, __entry->crc_ok ? ' ' : '!'
	)
);

TRACE_EVENT(fsi_master_acf_crc_rsp_error,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master, पूर्णांक retries),
	TP_ARGS(master, retries),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	retries)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->retries = retries;
	),
	TP_prपूर्णांकk("fsi-acf%d CRC error in response retry %d",
		__entry->master_idx, __entry->retries
	)
);

TRACE_EVENT(fsi_master_acf_poll_response_busy,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master, पूर्णांक busy_count),
	TP_ARGS(master, busy_count),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	busy_count)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->busy_count = busy_count;
	),
	TP_prपूर्णांकk("fsi-acf%d: device reported busy %d times",
		__entry->master_idx, __entry->busy_count
	)
);

TRACE_EVENT(fsi_master_acf_cmd_असल_addr,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master, u32 addr),
	TP_ARGS(master, addr),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(u32,	addr)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->addr = addr;
	),
	TP_prपूर्णांकk("fsi-acf%d: Sending ABS_ADR %06x",
		__entry->master_idx, __entry->addr
	)
);

TRACE_EVENT(fsi_master_acf_cmd_rel_addr,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master, u32 rel_addr),
	TP_ARGS(master, rel_addr),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(u32,	rel_addr)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
		__entry->rel_addr = rel_addr;
	),
	TP_prपूर्णांकk("fsi-acf%d: Sending REL_ADR %03x",
		__entry->master_idx, __entry->rel_addr
	)
);

TRACE_EVENT(fsi_master_acf_cmd_same_addr,
	TP_PROTO(स्थिर काष्ठा fsi_master_acf *master),
	TP_ARGS(master),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
	),
	TP_fast_assign(
		__entry->master_idx = master->master.idx;
	),
	TP_prपूर्णांकk("fsi-acf%d: Sending SAME_ADR",
		__entry->master_idx
	)
);

#पूर्ण_अगर /* _TRACE_FSI_MASTER_ACF_H */

#समावेश <trace/define_trace.h>
