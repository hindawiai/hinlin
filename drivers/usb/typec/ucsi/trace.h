<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ucsi

#अगर !defined(__UCSI_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __UCSI_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/usb/typec_alपंचांगode.h>

स्थिर अक्षर *ucsi_cmd_str(u64 raw_cmd);
स्थिर अक्षर *ucsi_cci_str(u32 cci);
स्थिर अक्षर *ucsi_recipient_str(u8 recipient);

DECLARE_EVENT_CLASS(ucsi_log_command,
	TP_PROTO(u64 command, पूर्णांक ret),
	TP_ARGS(command, ret),
	TP_STRUCT__entry(
		__field(u64, ctrl)
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		__entry->ctrl = command;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("%s -> %s (err=%d)", ucsi_cmd_str(__entry->ctrl),
		__entry->ret < 0 ? "FAIL" : "OK",
		__entry->ret < 0 ? __entry->ret : 0)
);

DEFINE_EVENT(ucsi_log_command, ucsi_run_command,
	TP_PROTO(u64 command, पूर्णांक ret),
	TP_ARGS(command, ret)
);

DEFINE_EVENT(ucsi_log_command, ucsi_reset_ppm,
	TP_PROTO(u64 command, पूर्णांक ret),
	TP_ARGS(command, ret)
);

DECLARE_EVENT_CLASS(ucsi_log_connector_status,
	TP_PROTO(पूर्णांक port, काष्ठा ucsi_connector_status *status),
	TP_ARGS(port, status),
	TP_STRUCT__entry(
		__field(पूर्णांक, port)
		__field(u16, change)
		__field(u8, opmode)
		__field(u8, connected)
		__field(u8, pwr_dir)
		__field(u8, partner_flags)
		__field(u8, partner_type)
		__field(u32, request_data_obj)
		__field(u8, bc_status)
	),
	TP_fast_assign(
		__entry->port = port - 1;
		__entry->change = status->change;
		__entry->opmode = UCSI_CONSTAT_PWR_OPMODE(status->flags);
		__entry->connected = !!(status->flags & UCSI_CONSTAT_CONNECTED);
		__entry->pwr_dir = !!(status->flags & UCSI_CONSTAT_PWR_सूची);
		__entry->partner_flags = UCSI_CONSTAT_PARTNER_FLAGS(status->flags);
		__entry->partner_type = UCSI_CONSTAT_PARTNER_TYPE(status->flags);
		__entry->request_data_obj = status->request_data_obj;
		__entry->bc_status = UCSI_CONSTAT_BC_STATUS(status->pwr_status);
	),
	TP_prपूर्णांकk("port%d status: change=%04x, opmode=%x, connected=%d, "
		"sourcing=%d, partner_flags=%x, partner_type=%x, "
		"request_data_obj=%08x, BC status=%x", __entry->port,
		__entry->change, __entry->opmode, __entry->connected,
		__entry->pwr_dir, __entry->partner_flags, __entry->partner_type,
		__entry->request_data_obj, __entry->bc_status)
);

DEFINE_EVENT(ucsi_log_connector_status, ucsi_connector_change,
	TP_PROTO(पूर्णांक port, काष्ठा ucsi_connector_status *status),
	TP_ARGS(port, status)
);

DEFINE_EVENT(ucsi_log_connector_status, ucsi_रेजिस्टर_port,
	TP_PROTO(पूर्णांक port, काष्ठा ucsi_connector_status *status),
	TP_ARGS(port, status)
);

DECLARE_EVENT_CLASS(ucsi_log_रेजिस्टर_alपंचांगode,
	TP_PROTO(u8 recipient, काष्ठा typec_alपंचांगode *alt),
	TP_ARGS(recipient, alt),
	TP_STRUCT__entry(
		__field(u8, recipient)
		__field(u16, svid)
		__field(u8, mode)
		__field(u32, vकरो)
	),
	TP_fast_assign(
		__entry->recipient = recipient;
		__entry->svid = alt->svid;
		__entry->mode = alt->mode;
		__entry->vकरो = alt->vकरो;
	),
	TP_prपूर्णांकk("%s alt mode: svid %04x, mode %d vdo %x",
		  ucsi_recipient_str(__entry->recipient), __entry->svid,
		  __entry->mode, __entry->vकरो)
);

DEFINE_EVENT(ucsi_log_रेजिस्टर_alपंचांगode, ucsi_रेजिस्टर_alपंचांगode,
	TP_PROTO(u8 recipient, काष्ठा typec_alपंचांगode *alt),
	TP_ARGS(recipient, alt)
);

#पूर्ण_अगर /* __UCSI_TRACE_H */

/* This part must be outside protection */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
