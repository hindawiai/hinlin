<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NVM Express device driver tracepoपूर्णांकs
 * Copyright (c) 2018 Johannes Thumshirn, SUSE Linux GmbH
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nvme

#अगर !defined(_TRACE_NVME_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NVME_H

#समावेश <linux/nvme.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "nvme.h"

स्थिर अक्षर *nvme_trace_parse_admin_cmd(काष्ठा trace_seq *p, u8 opcode,
		u8 *cdw10);
स्थिर अक्षर *nvme_trace_parse_nvm_cmd(काष्ठा trace_seq *p, u8 opcode,
		u8 *cdw10);
स्थिर अक्षर *nvme_trace_parse_fabrics_cmd(काष्ठा trace_seq *p, u8 fctype,
		u8 *spc);

#घोषणा parse_nvme_cmd(qid, opcode, fctype, cdw10)			\
	((opcode) == nvme_fabrics_command ?				\
	 nvme_trace_parse_fabrics_cmd(p, fctype, cdw10) :		\
	((qid) ?							\
	 nvme_trace_parse_nvm_cmd(p, opcode, cdw10) :			\
	 nvme_trace_parse_admin_cmd(p, opcode, cdw10)))

स्थिर अक्षर *nvme_trace_disk_name(काष्ठा trace_seq *p, अक्षर *name);
#घोषणा __prपूर्णांक_disk_name(name)				\
	nvme_trace_disk_name(p, name)

#अगर_अघोषित TRACE_HEADER_MULTI_READ
अटल अंतरभूत व्योम __assign_disk_name(अक्षर *name, काष्ठा gendisk *disk)
अणु
	अगर (disk)
		स_नकल(name, disk->disk_name, DISK_NAME_LEN);
	अन्यथा
		स_रखो(name, 0, DISK_NAME_LEN);
पूर्ण
#पूर्ण_अगर

TRACE_EVENT(nvme_setup_cmd,
	    TP_PROTO(काष्ठा request *req, काष्ठा nvme_command *cmd),
	    TP_ARGS(req, cmd),
	    TP_STRUCT__entry(
		__array(अक्षर, disk, DISK_NAME_LEN)
		__field(पूर्णांक, ctrl_id)
		__field(पूर्णांक, qid)
		__field(u8, opcode)
		__field(u8, flags)
		__field(u8, fctype)
		__field(u16, cid)
		__field(u32, nsid)
		__field(u64, metadata)
		__array(u8, cdw10, 24)
	    ),
	    TP_fast_assign(
		__entry->ctrl_id = nvme_req(req)->ctrl->instance;
		__entry->qid = nvme_req_qid(req);
		__entry->opcode = cmd->common.opcode;
		__entry->flags = cmd->common.flags;
		__entry->cid = cmd->common.command_id;
		__entry->nsid = le32_to_cpu(cmd->common.nsid);
		__entry->metadata = le64_to_cpu(cmd->common.metadata);
		__entry->fctype = cmd->fabrics.fctype;
		__assign_disk_name(__entry->disk, req->rq_disk);
		स_नकल(__entry->cdw10, &cmd->common.cdw10,
			माप(__entry->cdw10));
	    ),
	    TP_prपूर्णांकk("nvme%d: %sqid=%d, cmdid=%u, nsid=%u, flags=0x%x, meta=0x%llx, cmd=(%s %s)",
		      __entry->ctrl_id, __prपूर्णांक_disk_name(__entry->disk),
		      __entry->qid, __entry->cid, __entry->nsid,
		      __entry->flags, __entry->metadata,
		      show_opcode_name(__entry->qid, __entry->opcode,
				__entry->fctype),
		      parse_nvme_cmd(__entry->qid, __entry->opcode,
				__entry->fctype, __entry->cdw10))
);

TRACE_EVENT(nvme_complete_rq,
	    TP_PROTO(काष्ठा request *req),
	    TP_ARGS(req),
	    TP_STRUCT__entry(
		__array(अक्षर, disk, DISK_NAME_LEN)
		__field(पूर्णांक, ctrl_id)
		__field(पूर्णांक, qid)
		__field(पूर्णांक, cid)
		__field(u64, result)
		__field(u8, retries)
		__field(u8, flags)
		__field(u16, status)
	    ),
	    TP_fast_assign(
		__entry->ctrl_id = nvme_req(req)->ctrl->instance;
		__entry->qid = nvme_req_qid(req);
		__entry->cid = req->tag;
		__entry->result = le64_to_cpu(nvme_req(req)->result.u64);
		__entry->retries = nvme_req(req)->retries;
		__entry->flags = nvme_req(req)->flags;
		__entry->status = nvme_req(req)->status;
		__assign_disk_name(__entry->disk, req->rq_disk);
	    ),
	    TP_prपूर्णांकk("nvme%d: %sqid=%d, cmdid=%u, res=%#llx, retries=%u, flags=0x%x, status=%#x",
		      __entry->ctrl_id, __prपूर्णांक_disk_name(__entry->disk),
		      __entry->qid, __entry->cid, __entry->result,
		      __entry->retries, __entry->flags, __entry->status)

);

#घोषणा aer_name(aer) अणु aer, #aer पूर्ण

TRACE_EVENT(nvme_async_event,
	TP_PROTO(काष्ठा nvme_ctrl *ctrl, u32 result),
	TP_ARGS(ctrl, result),
	TP_STRUCT__entry(
		__field(पूर्णांक, ctrl_id)
		__field(u32, result)
	),
	TP_fast_assign(
		__entry->ctrl_id = ctrl->instance;
		__entry->result = result;
	),
	TP_prपूर्णांकk("nvme%d: NVME_AEN=%#08x [%s]",
		__entry->ctrl_id, __entry->result,
		__prपूर्णांक_symbolic(__entry->result,
		aer_name(NVME_AER_NOTICE_NS_CHANGED),
		aer_name(NVME_AER_NOTICE_ANA),
		aer_name(NVME_AER_NOTICE_FW_ACT_STARTING),
		aer_name(NVME_AER_NOTICE_DISC_CHANGED),
		aer_name(NVME_AER_ERROR),
		aer_name(NVME_AER_SMART),
		aer_name(NVME_AER_CSS),
		aer_name(NVME_AER_VS))
	)
);

#अघोषित aer_name

TRACE_EVENT(nvme_sq,
	TP_PROTO(काष्ठा request *req, __le16 sq_head, पूर्णांक sq_tail),
	TP_ARGS(req, sq_head, sq_tail),
	TP_STRUCT__entry(
		__field(पूर्णांक, ctrl_id)
		__array(अक्षर, disk, DISK_NAME_LEN)
		__field(पूर्णांक, qid)
		__field(u16, sq_head)
		__field(u16, sq_tail)
	),
	TP_fast_assign(
		__entry->ctrl_id = nvme_req(req)->ctrl->instance;
		__assign_disk_name(__entry->disk, req->rq_disk);
		__entry->qid = nvme_req_qid(req);
		__entry->sq_head = le16_to_cpu(sq_head);
		__entry->sq_tail = sq_tail;
	),
	TP_prपूर्णांकk("nvme%d: %sqid=%d, head=%u, tail=%u",
		__entry->ctrl_id, __prपूर्णांक_disk_name(__entry->disk),
		__entry->qid, __entry->sq_head, __entry->sq_tail
	)
);

#पूर्ण_अगर /* _TRACE_NVME_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
