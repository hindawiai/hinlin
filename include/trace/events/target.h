<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM target

#अगर !defined(_TRACE_TARGET_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_TARGET_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <target/target_core_base.h>

/* cribbed verbatim from <trace/event/scsi.h> */
#घोषणा scsi_opcode_name(opcode)	अणु opcode, #opcode पूर्ण
#घोषणा show_opcode_name(val)					\
	__prपूर्णांक_symbolic(val,					\
		scsi_opcode_name(TEST_UNIT_READY),		\
		scsi_opcode_name(REZERO_UNIT),			\
		scsi_opcode_name(REQUEST_SENSE),		\
		scsi_opcode_name(FORMAT_UNIT),			\
		scsi_opcode_name(READ_BLOCK_LIMITS),		\
		scsi_opcode_name(REASSIGN_BLOCKS),		\
		scsi_opcode_name(INITIALIZE_ELEMENT_STATUS),	\
		scsi_opcode_name(READ_6),			\
		scsi_opcode_name(WRITE_6),			\
		scsi_opcode_name(SEEK_6),			\
		scsi_opcode_name(READ_REVERSE),			\
		scsi_opcode_name(WRITE_खाताMARKS),		\
		scsi_opcode_name(SPACE),			\
		scsi_opcode_name(INQUIRY),			\
		scsi_opcode_name(RECOVER_BUFFERED_DATA),	\
		scsi_opcode_name(MODE_SELECT),			\
		scsi_opcode_name(RESERVE),			\
		scsi_opcode_name(RELEASE),			\
		scsi_opcode_name(COPY),				\
		scsi_opcode_name(ERASE),			\
		scsi_opcode_name(MODE_SENSE),			\
		scsi_opcode_name(START_STOP),			\
		scsi_opcode_name(RECEIVE_DIAGNOSTIC),		\
		scsi_opcode_name(SEND_DIAGNOSTIC),		\
		scsi_opcode_name(ALLOW_MEDIUM_REMOVAL),		\
		scsi_opcode_name(SET_WINDOW),			\
		scsi_opcode_name(READ_CAPACITY),		\
		scsi_opcode_name(READ_10),			\
		scsi_opcode_name(WRITE_10),			\
		scsi_opcode_name(SEEK_10),			\
		scsi_opcode_name(POSITION_TO_ELEMENT),		\
		scsi_opcode_name(WRITE_VERIFY),			\
		scsi_opcode_name(VERIFY),			\
		scsi_opcode_name(SEARCH_HIGH),			\
		scsi_opcode_name(SEARCH_EQUAL),			\
		scsi_opcode_name(SEARCH_LOW),			\
		scsi_opcode_name(SET_LIMITS),			\
		scsi_opcode_name(PRE_FETCH),			\
		scsi_opcode_name(READ_POSITION),		\
		scsi_opcode_name(SYNCHRONIZE_CACHE),		\
		scsi_opcode_name(LOCK_UNLOCK_CACHE),		\
		scsi_opcode_name(READ_DEFECT_DATA),		\
		scsi_opcode_name(MEDIUM_SCAN),			\
		scsi_opcode_name(COMPARE),			\
		scsi_opcode_name(COPY_VERIFY),			\
		scsi_opcode_name(WRITE_BUFFER),			\
		scsi_opcode_name(READ_BUFFER),			\
		scsi_opcode_name(UPDATE_BLOCK),			\
		scsi_opcode_name(READ_LONG),			\
		scsi_opcode_name(WRITE_LONG),			\
		scsi_opcode_name(CHANGE_DEFINITION),		\
		scsi_opcode_name(WRITE_SAME),			\
		scsi_opcode_name(UNMAP),			\
		scsi_opcode_name(READ_TOC),			\
		scsi_opcode_name(LOG_SELECT),			\
		scsi_opcode_name(LOG_SENSE),			\
		scsi_opcode_name(XDWRITEREAD_10),		\
		scsi_opcode_name(MODE_SELECT_10),		\
		scsi_opcode_name(RESERVE_10),			\
		scsi_opcode_name(RELEASE_10),			\
		scsi_opcode_name(MODE_SENSE_10),		\
		scsi_opcode_name(PERSISTENT_RESERVE_IN),	\
		scsi_opcode_name(PERSISTENT_RESERVE_OUT),	\
		scsi_opcode_name(VARIABLE_LENGTH_CMD),		\
		scsi_opcode_name(REPORT_LUNS),			\
		scsi_opcode_name(MAINTEन_अंकCE_IN),		\
		scsi_opcode_name(MAINTEन_अंकCE_OUT),		\
		scsi_opcode_name(MOVE_MEDIUM),			\
		scsi_opcode_name(EXCHANGE_MEDIUM),		\
		scsi_opcode_name(READ_12),			\
		scsi_opcode_name(WRITE_12),			\
		scsi_opcode_name(WRITE_VERIFY_12),		\
		scsi_opcode_name(SEARCH_HIGH_12),		\
		scsi_opcode_name(SEARCH_EQUAL_12),		\
		scsi_opcode_name(SEARCH_LOW_12),		\
		scsi_opcode_name(READ_ELEMENT_STATUS),		\
		scsi_opcode_name(SEND_VOLUME_TAG),		\
		scsi_opcode_name(WRITE_LONG_2),			\
		scsi_opcode_name(READ_16),			\
		scsi_opcode_name(WRITE_16),			\
		scsi_opcode_name(VERIFY_16),			\
		scsi_opcode_name(WRITE_SAME_16),		\
		scsi_opcode_name(SERVICE_ACTION_IN_16),		\
		scsi_opcode_name(SAI_READ_CAPACITY_16),		\
		scsi_opcode_name(SAI_GET_LBA_STATUS),		\
		scsi_opcode_name(MI_REPORT_TARGET_PGS),		\
		scsi_opcode_name(MO_SET_TARGET_PGS),		\
		scsi_opcode_name(READ_32),			\
		scsi_opcode_name(WRITE_32),			\
		scsi_opcode_name(WRITE_SAME_32),		\
		scsi_opcode_name(ATA_16),			\
		scsi_opcode_name(ATA_12))

#घोषणा show_task_attribute_name(val)				\
	__prपूर्णांक_symbolic(val,					\
		अणु TCM_SIMPLE_TAG,	"SIMPLE"	पूर्ण,	\
		अणु TCM_HEAD_TAG,		"HEAD"		पूर्ण,	\
		अणु TCM_ORDERED_TAG,	"ORDERED"	पूर्ण,	\
		अणु TCM_ACA_TAG,		"ACA"		पूर्ण )

#घोषणा show_scsi_status_name(val)				\
	__prपूर्णांक_symbolic(val,					\
		अणु SAM_STAT_GOOD,	"GOOD" पूर्ण,		\
		अणु SAM_STAT_CHECK_CONDITION, "CHECK CONDITION" पूर्ण, \
		अणु SAM_STAT_CONDITION_MET, "CONDITION MET" पूर्ण,	\
		अणु SAM_STAT_BUSY,	"BUSY" पूर्ण,		\
		अणु SAM_STAT_INTERMEDIATE, "INTERMEDIATE" पूर्ण,	\
		अणु SAM_STAT_INTERMEDIATE_CONDITION_MET, "INTERMEDIATE CONDITION MET" पूर्ण, \
		अणु SAM_STAT_RESERVATION_CONFLICT, "RESERVATION CONFLICT" पूर्ण, \
		अणु SAM_STAT_COMMAND_TERMINATED, "COMMAND TERMINATED" पूर्ण, \
		अणु SAM_STAT_TASK_SET_FULL, "TASK SET FULL" पूर्ण,	\
		अणु SAM_STAT_ACA_ACTIVE, "ACA ACTIVE" पूर्ण,		\
		अणु SAM_STAT_TASK_ABORTED, "TASK ABORTED" पूर्ण )

TRACE_EVENT(target_sequencer_start,

	TP_PROTO(काष्ठा se_cmd *cmd),

	TP_ARGS(cmd),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	unpacked_lun	)
		__field( अचिन्हित दीर्घ दीर्घ,	tag	)
		__field( अचिन्हित पूर्णांक,	opcode		)
		__field( अचिन्हित पूर्णांक,	data_length	)
		__field( अचिन्हित पूर्णांक,	task_attribute  )
		__field( अचिन्हित अक्षर,	control		)
		__array( अचिन्हित अक्षर,	cdb, TCM_MAX_COMMAND_SIZE	)
		__string( initiator,	cmd->se_sess->se_node_acl->initiatorname	)
	),

	TP_fast_assign(
		__entry->unpacked_lun	= cmd->orig_fe_lun;
		__entry->tag		= cmd->tag;
		__entry->opcode		= cmd->t_task_cdb[0];
		__entry->data_length	= cmd->data_length;
		__entry->task_attribute	= cmd->sam_task_attr;
		__entry->control	= scsi_command_control(cmd->t_task_cdb);
		स_नकल(__entry->cdb, cmd->t_task_cdb, TCM_MAX_COMMAND_SIZE);
		__assign_str(initiator, cmd->se_sess->se_node_acl->initiatorname);
	),

	TP_prपूर्णांकk("%s -> LUN %03u tag %#llx %s data_length %6u  CDB %s  (TA:%s C:%02x)",
		  __get_str(initiator), __entry->unpacked_lun,
		  __entry->tag, show_opcode_name(__entry->opcode),
		  __entry->data_length, __prपूर्णांक_hex(__entry->cdb, 16),
		  show_task_attribute_name(__entry->task_attribute),
		  __entry->control
	)
);

TRACE_EVENT(target_cmd_complete,

	TP_PROTO(काष्ठा se_cmd *cmd),

	TP_ARGS(cmd),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	unpacked_lun	)
		__field( अचिन्हित दीर्घ दीर्घ,	tag	)
		__field( अचिन्हित पूर्णांक,	opcode		)
		__field( अचिन्हित पूर्णांक,	data_length	)
		__field( अचिन्हित पूर्णांक,	task_attribute  )
		__field( अचिन्हित अक्षर,	control		)
		__field( अचिन्हित अक्षर,	scsi_status	)
		__field( अचिन्हित अक्षर,	sense_length	)
		__array( अचिन्हित अक्षर,	cdb, TCM_MAX_COMMAND_SIZE	)
		__array( अचिन्हित अक्षर,	sense_data, 18	)
		__string(initiator,	cmd->se_sess->se_node_acl->initiatorname)
	),

	TP_fast_assign(
		__entry->unpacked_lun	= cmd->orig_fe_lun;
		__entry->tag		= cmd->tag;
		__entry->opcode		= cmd->t_task_cdb[0];
		__entry->data_length	= cmd->data_length;
		__entry->task_attribute	= cmd->sam_task_attr;
		__entry->control	= scsi_command_control(cmd->t_task_cdb);
		__entry->scsi_status	= cmd->scsi_status;
		__entry->sense_length	= cmd->scsi_status == SAM_STAT_CHECK_CONDITION ?
			min(18, ((u8 *) cmd->sense_buffer)[SPC_ADD_SENSE_LEN_OFFSET] + 8) : 0;
		स_नकल(__entry->cdb, cmd->t_task_cdb, TCM_MAX_COMMAND_SIZE);
		स_नकल(__entry->sense_data, cmd->sense_buffer, __entry->sense_length);
		__assign_str(initiator, cmd->se_sess->se_node_acl->initiatorname);
	),

	TP_prपूर्णांकk("%s <- LUN %03u tag %#llx status %s (sense len %d%s%s)  %s data_length %6u  CDB %s  (TA:%s C:%02x)",
		  __get_str(initiator), __entry->unpacked_lun,
		  __entry->tag,
		  show_scsi_status_name(__entry->scsi_status),
		  __entry->sense_length, __entry->sense_length ? " / " : "",
		  __prपूर्णांक_hex(__entry->sense_data, __entry->sense_length),
		  show_opcode_name(__entry->opcode),
		  __entry->data_length, __prपूर्णांक_hex(__entry->cdb, 16),
		  show_task_attribute_name(__entry->task_attribute),
		  __entry->control
	)
);

#पूर्ण_अगर /*  _TRACE_TARGET_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
