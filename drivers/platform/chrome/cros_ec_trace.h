<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Trace events क्रम the ChromeOS Embedded Controller
 *
 * Copyright 2019 Google LLC.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cros_ec

#अगर !defined(_CROS_EC_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _CROS_EC_TRACE_H_

#समावेश <linux/bits.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(cros_ec_request_start,
	TP_PROTO(काष्ठा cros_ec_command *cmd),
	TP_ARGS(cmd),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t, version)
		__field(uपूर्णांक32_t, offset)
		__field(uपूर्णांक32_t, command)
		__field(uपूर्णांक32_t, outsize)
		__field(uपूर्णांक32_t, insize)
	),
	TP_fast_assign(
		__entry->version = cmd->version;
		__entry->offset = cmd->command / EC_CMD_PASSTHRU_OFFSET(1);
		__entry->command = cmd->command % EC_CMD_PASSTHRU_OFFSET(1);
		__entry->outsize = cmd->outsize;
		__entry->insize = cmd->insize;
	),
	TP_prपूर्णांकk("version: %u, offset: %d, command: %s, outsize: %u, insize: %u",
		  __entry->version, __entry->offset,
		  __prपूर्णांक_symbolic(__entry->command, EC_CMDS),
		  __entry->outsize, __entry->insize)
);

TRACE_EVENT(cros_ec_request_करोne,
	TP_PROTO(काष्ठा cros_ec_command *cmd, पूर्णांक retval),
	TP_ARGS(cmd, retval),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t, version)
		__field(uपूर्णांक32_t, offset)
		__field(uपूर्णांक32_t, command)
		__field(uपूर्णांक32_t, outsize)
		__field(uपूर्णांक32_t, insize)
		__field(uपूर्णांक32_t, result)
		__field(पूर्णांक, retval)
	),
	TP_fast_assign(
		__entry->version = cmd->version;
		__entry->offset = cmd->command / EC_CMD_PASSTHRU_OFFSET(1);
		__entry->command = cmd->command % EC_CMD_PASSTHRU_OFFSET(1);
		__entry->outsize = cmd->outsize;
		__entry->insize = cmd->insize;
		__entry->result = cmd->result;
		__entry->retval = retval;
	),
	TP_prपूर्णांकk("version: %u, offset: %d, command: %s, outsize: %u, insize: %u, ec result: %s, retval: %u",
		  __entry->version, __entry->offset,
		  __prपूर्णांक_symbolic(__entry->command, EC_CMDS),
		  __entry->outsize, __entry->insize,
		  __prपूर्णांक_symbolic(__entry->result, EC_RESULT),
		  __entry->retval)
);


#पूर्ण_अगर /* _CROS_EC_TRACE_H_ */

/* this part must be outside header guard */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता cros_ec_trace

#समावेश <trace/define_trace.h>
