<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NVM Express target device driver tracepoपूर्णांकs
 * Copyright (c) 2018 Johannes Thumshirn, SUSE Linux GmbH
 *
 * This is entirely based on drivers/nvme/host/trace.h
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nvmet

#अगर !defined(_TRACE_NVMET_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NVMET_H

#समावेश <linux/nvme.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "nvmet.h"

स्थिर अक्षर *nvmet_trace_parse_admin_cmd(काष्ठा trace_seq *p, u8 opcode,
		u8 *cdw10);
स्थिर अक्षर *nvmet_trace_parse_nvm_cmd(काष्ठा trace_seq *p, u8 opcode,
		u8 *cdw10);
स्थिर अक्षर *nvmet_trace_parse_fabrics_cmd(काष्ठा trace_seq *p, u8 fctype,
		u8 *spc);

#घोषणा parse_nvme_cmd(qid, opcode, fctype, cdw10)			\
	((opcode) == nvme_fabrics_command ?				\
	 nvmet_trace_parse_fabrics_cmd(p, fctype, cdw10) :		\
	(qid ?								\
	 nvmet_trace_parse_nvm_cmd(p, opcode, cdw10) :			\
	 nvmet_trace_parse_admin_cmd(p, opcode, cdw10)))

स्थिर अक्षर *nvmet_trace_ctrl_name(काष्ठा trace_seq *p, काष्ठा nvmet_ctrl *ctrl);
#घोषणा __prपूर्णांक_ctrl_name(ctrl)				\
	nvmet_trace_ctrl_name(p, ctrl)

स्थिर अक्षर *nvmet_trace_disk_name(काष्ठा trace_seq *p, अक्षर *name);
#घोषणा __prपूर्णांक_disk_name(name)				\
	nvmet_trace_disk_name(p, name)

#अगर_अघोषित TRACE_HEADER_MULTI_READ
अटल अंतरभूत काष्ठा nvmet_ctrl *nvmet_req_to_ctrl(काष्ठा nvmet_req *req)
अणु
	वापस req->sq->ctrl;
पूर्ण

अटल अंतरभूत व्योम __assign_req_name(अक्षर *name, काष्ठा nvmet_req *req)
अणु
	अगर (!req->ns) अणु
		स_रखो(name, 0, DISK_NAME_LEN);
		वापस;
	पूर्ण

	म_नकलन(name, req->ns->device_path,
		min_t(माप_प्रकार, DISK_NAME_LEN, म_माप(req->ns->device_path)));
पूर्ण
#पूर्ण_अगर

TRACE_EVENT(nvmet_req_init,
	TP_PROTO(काष्ठा nvmet_req *req, काष्ठा nvme_command *cmd),
	TP_ARGS(req, cmd),
	TP_STRUCT__entry(
		__field(काष्ठा nvme_command *, cmd)
		__field(काष्ठा nvmet_ctrl *, ctrl)
		__array(अक्षर, disk, DISK_NAME_LEN)
		__field(पूर्णांक, qid)
		__field(u16, cid)
		__field(u8, opcode)
		__field(u8, fctype)
		__field(u8, flags)
		__field(u32, nsid)
		__field(u64, metadata)
		__array(u8, cdw10, 24)
	),
	TP_fast_assign(
		__entry->cmd = cmd;
		__entry->ctrl = nvmet_req_to_ctrl(req);
		__assign_req_name(__entry->disk, req);
		__entry->qid = req->sq->qid;
		__entry->cid = cmd->common.command_id;
		__entry->opcode = cmd->common.opcode;
		__entry->fctype = cmd->fabrics.fctype;
		__entry->flags = cmd->common.flags;
		__entry->nsid = le32_to_cpu(cmd->common.nsid);
		__entry->metadata = le64_to_cpu(cmd->common.metadata);
		स_नकल(__entry->cdw10, &cmd->common.cdw10,
			माप(__entry->cdw10));
	),
	TP_prपूर्णांकk("nvmet%s: %sqid=%d, cmdid=%u, nsid=%u, flags=%#x, "
		  "meta=%#llx, cmd=(%s, %s)",
		__prपूर्णांक_ctrl_name(__entry->ctrl),
		__prपूर्णांक_disk_name(__entry->disk),
		__entry->qid, __entry->cid, __entry->nsid,
		__entry->flags, __entry->metadata,
		show_opcode_name(__entry->qid, __entry->opcode,
				__entry->fctype),
		parse_nvme_cmd(__entry->qid, __entry->opcode,
				__entry->fctype, __entry->cdw10))
);

TRACE_EVENT(nvmet_req_complete,
	TP_PROTO(काष्ठा nvmet_req *req),
	TP_ARGS(req),
	TP_STRUCT__entry(
		__field(काष्ठा nvmet_ctrl *, ctrl)
		__array(अक्षर, disk, DISK_NAME_LEN)
		__field(पूर्णांक, qid)
		__field(पूर्णांक, cid)
		__field(u64, result)
		__field(u16, status)
	),
	TP_fast_assign(
		__entry->ctrl = nvmet_req_to_ctrl(req);
		__entry->qid = req->cq->qid;
		__entry->cid = req->cqe->command_id;
		__entry->result = le64_to_cpu(req->cqe->result.u64);
		__entry->status = le16_to_cpu(req->cqe->status) >> 1;
		__assign_req_name(__entry->disk, req);
	),
	TP_prपूर्णांकk("nvmet%s: %sqid=%d, cmdid=%u, res=%#llx, status=%#x",
		__prपूर्णांक_ctrl_name(__entry->ctrl),
		__prपूर्णांक_disk_name(__entry->disk),
		__entry->qid, __entry->cid, __entry->result, __entry->status)

);

#घोषणा aer_name(aer) अणु aer, #aer पूर्ण

TRACE_EVENT(nvmet_async_event,
	TP_PROTO(काष्ठा nvmet_ctrl *ctrl, __le32 result),
	TP_ARGS(ctrl, result),
	TP_STRUCT__entry(
		__field(पूर्णांक, ctrl_id)
		__field(u32, result)
	),
	TP_fast_assign(
		__entry->ctrl_id = ctrl->cntlid;
		__entry->result = (le32_to_cpu(result) & 0xff00) >> 8;
	),
	TP_prपूर्णांकk("nvmet%d: NVME_AEN=%#08x [%s]",
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

#पूर्ण_अगर /* _TRACE_NVMET_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
