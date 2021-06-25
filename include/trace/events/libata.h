<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM libata

#अगर !defined(_TRACE_LIBATA_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_LIBATA_H

#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#घोषणा ata_opcode_name(opcode)	अणु opcode, #opcode पूर्ण
#घोषणा show_opcode_name(val)					\
	__prपूर्णांक_symbolic(val,					\
		 ata_opcode_name(ATA_CMD_DEV_RESET),		\
		 ata_opcode_name(ATA_CMD_CHK_POWER),		\
		 ata_opcode_name(ATA_CMD_STANDBY),		\
		 ata_opcode_name(ATA_CMD_IDLE),			\
		 ata_opcode_name(ATA_CMD_EDD),			\
		 ata_opcode_name(ATA_CMD_DOWNLOAD_MICRO),	\
		 ata_opcode_name(ATA_CMD_DOWNLOAD_MICRO_DMA),	\
		 ata_opcode_name(ATA_CMD_NOP),			\
		 ata_opcode_name(ATA_CMD_FLUSH),		\
		 ata_opcode_name(ATA_CMD_FLUSH_EXT),		\
		 ata_opcode_name(ATA_CMD_ID_ATA),		\
		 ata_opcode_name(ATA_CMD_ID_ATAPI),		\
		 ata_opcode_name(ATA_CMD_SERVICE),		\
		 ata_opcode_name(ATA_CMD_READ),			\
		 ata_opcode_name(ATA_CMD_READ_EXT),		\
		 ata_opcode_name(ATA_CMD_READ_QUEUED),		\
		 ata_opcode_name(ATA_CMD_READ_STREAM_EXT),	\
		 ata_opcode_name(ATA_CMD_READ_STREAM_DMA_EXT),	\
		 ata_opcode_name(ATA_CMD_WRITE),		\
		 ata_opcode_name(ATA_CMD_WRITE_EXT),		\
		 ata_opcode_name(ATA_CMD_WRITE_QUEUED),		\
		 ata_opcode_name(ATA_CMD_WRITE_STREAM_EXT),	\
		 ata_opcode_name(ATA_CMD_WRITE_STREAM_DMA_EXT), \
		 ata_opcode_name(ATA_CMD_WRITE_FUA_EXT),	\
		 ata_opcode_name(ATA_CMD_WRITE_QUEUED_FUA_EXT), \
		 ata_opcode_name(ATA_CMD_FPDMA_READ),		\
		 ata_opcode_name(ATA_CMD_FPDMA_WRITE),		\
		 ata_opcode_name(ATA_CMD_NCQ_NON_DATA),		\
		 ata_opcode_name(ATA_CMD_FPDMA_SEND),		\
		 ata_opcode_name(ATA_CMD_FPDMA_RECV),		\
		 ata_opcode_name(ATA_CMD_PIO_READ),		\
		 ata_opcode_name(ATA_CMD_PIO_READ_EXT),		\
		 ata_opcode_name(ATA_CMD_PIO_WRITE),		\
		 ata_opcode_name(ATA_CMD_PIO_WRITE_EXT),	\
		 ata_opcode_name(ATA_CMD_READ_MULTI),		\
		 ata_opcode_name(ATA_CMD_READ_MULTI_EXT),	\
		 ata_opcode_name(ATA_CMD_WRITE_MULTI),		\
		 ata_opcode_name(ATA_CMD_WRITE_MULTI_EXT),	\
		 ata_opcode_name(ATA_CMD_WRITE_MULTI_FUA_EXT),	\
		 ata_opcode_name(ATA_CMD_SET_FEATURES),		\
		 ata_opcode_name(ATA_CMD_SET_MULTI),		\
		 ata_opcode_name(ATA_CMD_PACKET),		\
		 ata_opcode_name(ATA_CMD_VERIFY),		\
		 ata_opcode_name(ATA_CMD_VERIFY_EXT),		\
		 ata_opcode_name(ATA_CMD_WRITE_UNCORR_EXT),	\
		 ata_opcode_name(ATA_CMD_STANDBYNOW1),		\
		 ata_opcode_name(ATA_CMD_IDLEIMMEDIATE),	\
		 ata_opcode_name(ATA_CMD_SLEEP),		\
		 ata_opcode_name(ATA_CMD_INIT_DEV_PARAMS),	\
		 ata_opcode_name(ATA_CMD_READ_NATIVE_MAX),	\
		 ata_opcode_name(ATA_CMD_READ_NATIVE_MAX_EXT),	\
		 ata_opcode_name(ATA_CMD_SET_MAX),		\
		 ata_opcode_name(ATA_CMD_SET_MAX_EXT),		\
		 ata_opcode_name(ATA_CMD_READ_LOG_EXT),		\
		 ata_opcode_name(ATA_CMD_WRITE_LOG_EXT),	\
		 ata_opcode_name(ATA_CMD_READ_LOG_DMA_EXT),	\
		 ata_opcode_name(ATA_CMD_WRITE_LOG_DMA_EXT),	\
		 ata_opcode_name(ATA_CMD_TRUSTED_NONDATA),	\
		 ata_opcode_name(ATA_CMD_TRUSTED_RCV),		\
		 ata_opcode_name(ATA_CMD_TRUSTED_RCV_DMA),	\
		 ata_opcode_name(ATA_CMD_TRUSTED_SND),		\
		 ata_opcode_name(ATA_CMD_TRUSTED_SND_DMA),	\
		 ata_opcode_name(ATA_CMD_PMP_READ),		\
		 ata_opcode_name(ATA_CMD_PMP_READ_DMA),		\
		 ata_opcode_name(ATA_CMD_PMP_WRITE),		\
		 ata_opcode_name(ATA_CMD_PMP_WRITE_DMA),	\
		 ata_opcode_name(ATA_CMD_CONF_OVERLAY),		\
		 ata_opcode_name(ATA_CMD_SEC_SET_PASS),		\
		 ata_opcode_name(ATA_CMD_SEC_UNLOCK),		\
		 ata_opcode_name(ATA_CMD_SEC_ERASE_PREP),	\
		 ata_opcode_name(ATA_CMD_SEC_ERASE_UNIT),	\
		 ata_opcode_name(ATA_CMD_SEC_FREEZE_LOCK),	\
		 ata_opcode_name(ATA_CMD_SEC_DISABLE_PASS),	\
		 ata_opcode_name(ATA_CMD_CONFIG_STREAM),	\
		 ata_opcode_name(ATA_CMD_SMART),		\
		 ata_opcode_name(ATA_CMD_MEDIA_LOCK),		\
		 ata_opcode_name(ATA_CMD_MEDIA_UNLOCK),		\
		 ata_opcode_name(ATA_CMD_DSM),			\
		 ata_opcode_name(ATA_CMD_CHK_MED_CRD_TYP),	\
		 ata_opcode_name(ATA_CMD_CFA_REQ_EXT_ERR),	\
		 ata_opcode_name(ATA_CMD_CFA_WRITE_NE),		\
		 ata_opcode_name(ATA_CMD_CFA_TRANS_SECT),	\
		 ata_opcode_name(ATA_CMD_CFA_ERASE),		\
		 ata_opcode_name(ATA_CMD_CFA_WRITE_MULT_NE),	\
		 ata_opcode_name(ATA_CMD_REQ_SENSE_DATA),	\
		 ata_opcode_name(ATA_CMD_SANITIZE_DEVICE),	\
		 ata_opcode_name(ATA_CMD_ZAC_MGMT_IN),		\
		 ata_opcode_name(ATA_CMD_ZAC_MGMT_OUT),		\
		 ata_opcode_name(ATA_CMD_RESTORE),		\
		 ata_opcode_name(ATA_CMD_READ_LONG),		\
		 ata_opcode_name(ATA_CMD_READ_LONG_ONCE),	\
		 ata_opcode_name(ATA_CMD_WRITE_LONG),		\
		 ata_opcode_name(ATA_CMD_WRITE_LONG_ONCE))

#घोषणा ata_error_name(result)	अणु result, #result पूर्ण
#घोषणा show_error_name(val)				\
	__prपूर्णांक_symbolic(val,				\
		ata_error_name(ATA_ICRC),		\
		ata_error_name(ATA_UNC),		\
		ata_error_name(ATA_MC),			\
		ata_error_name(ATA_IDNF),		\
		ata_error_name(ATA_MCR),		\
		ata_error_name(ATA_ABORTED),		\
		ata_error_name(ATA_TRK0NF),		\
		ata_error_name(ATA_AMNF))

#घोषणा ata_protocol_name(proto)	अणु proto, #proto पूर्ण
#घोषणा show_protocol_name(val)				\
	__prपूर्णांक_symbolic(val,				\
		ata_protocol_name(ATA_PROT_UNKNOWN),	\
		ata_protocol_name(ATA_PROT_NODATA),	\
		ata_protocol_name(ATA_PROT_PIO),	\
		ata_protocol_name(ATA_PROT_DMA),	\
		ata_protocol_name(ATA_PROT_NCQ),	\
		ata_protocol_name(ATA_PROT_NCQ_NODATA),	\
		ata_protocol_name(ATAPI_PROT_NODATA),	\
		ata_protocol_name(ATAPI_PROT_PIO),	\
		ata_protocol_name(ATAPI_PROT_DMA))

स्थिर अक्षर *libata_trace_parse_status(काष्ठा trace_seq*, अचिन्हित अक्षर);
#घोषणा __parse_status(s) libata_trace_parse_status(p, s)

स्थिर अक्षर *libata_trace_parse_eh_action(काष्ठा trace_seq *, अचिन्हित पूर्णांक);
#घोषणा __parse_eh_action(a) libata_trace_parse_eh_action(p, a)

स्थिर अक्षर *libata_trace_parse_eh_err_mask(काष्ठा trace_seq *, अचिन्हित पूर्णांक);
#घोषणा __parse_eh_err_mask(m) libata_trace_parse_eh_err_mask(p, m)

स्थिर अक्षर *libata_trace_parse_qc_flags(काष्ठा trace_seq *, अचिन्हित पूर्णांक);
#घोषणा __parse_qc_flags(f) libata_trace_parse_qc_flags(p, f)

स्थिर अक्षर *libata_trace_parse_subcmd(काष्ठा trace_seq *, अचिन्हित अक्षर,
				      अचिन्हित अक्षर, अचिन्हित अक्षर);
#घोषणा __parse_subcmd(c,f,h) libata_trace_parse_subcmd(p, c, f, h)

TRACE_EVENT(ata_qc_issue,

	TP_PROTO(काष्ठा ata_queued_cmd *qc),

	TP_ARGS(qc),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	ata_port )
		__field( अचिन्हित पूर्णांक,	ata_dev	)
		__field( अचिन्हित पूर्णांक,	tag	)
		__field( अचिन्हित अक्षर,	cmd	)
		__field( अचिन्हित अक्षर,	dev	)
		__field( अचिन्हित अक्षर,	lbal	)
		__field( अचिन्हित अक्षर,	lbam	)
		__field( अचिन्हित अक्षर,	lbah	)
		__field( अचिन्हित अक्षर,	nsect	)
		__field( अचिन्हित अक्षर,	feature	)
		__field( अचिन्हित अक्षर,	hob_lbal )
		__field( अचिन्हित अक्षर,	hob_lbam )
		__field( अचिन्हित अक्षर,	hob_lbah )
		__field( अचिन्हित अक्षर,	hob_nsect )
		__field( अचिन्हित अक्षर,	hob_feature )
		__field( अचिन्हित अक्षर,	ctl )
		__field( अचिन्हित अक्षर,	proto )
		__field( अचिन्हित दीर्घ,	flags )
	),

	TP_fast_assign(
		__entry->ata_port	= qc->ap->prपूर्णांक_id;
		__entry->ata_dev	= qc->dev->link->pmp + qc->dev->devno;
		__entry->tag		= qc->tag;
		__entry->proto		= qc->tf.protocol;
		__entry->cmd		= qc->tf.command;
		__entry->dev		= qc->tf.device;
		__entry->lbal		= qc->tf.lbal;
		__entry->lbam		= qc->tf.lbam;
		__entry->lbah		= qc->tf.lbah;
		__entry->hob_lbal	= qc->tf.hob_lbal;
		__entry->hob_lbam	= qc->tf.hob_lbam;
		__entry->hob_lbah	= qc->tf.hob_lbah;
		__entry->feature	= qc->tf.feature;
		__entry->hob_feature	= qc->tf.hob_feature;
		__entry->nsect		= qc->tf.nsect;
		__entry->hob_nsect	= qc->tf.hob_nsect;
	),

	TP_prपूर्णांकk("ata_port=%u ata_dev=%u tag=%d proto=%s cmd=%s%s " \
		  " tf=(%02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x)",
		  __entry->ata_port, __entry->ata_dev, __entry->tag,
		  show_protocol_name(__entry->proto),
		  show_opcode_name(__entry->cmd),
		  __parse_subcmd(__entry->cmd, __entry->feature, __entry->hob_nsect),
		  __entry->cmd, __entry->feature, __entry->nsect,
		  __entry->lbal, __entry->lbam, __entry->lbah,
		  __entry->hob_feature, __entry->hob_nsect,
		  __entry->hob_lbal, __entry->hob_lbam, __entry->hob_lbah,
		  __entry->dev)
);

DECLARE_EVENT_CLASS(ata_qc_complete_ढाँचा,

	TP_PROTO(काष्ठा ata_queued_cmd *qc),

	TP_ARGS(qc),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	ata_port )
		__field( अचिन्हित पूर्णांक,	ata_dev	)
		__field( अचिन्हित पूर्णांक,	tag	)
		__field( अचिन्हित अक्षर,	status	)
		__field( अचिन्हित अक्षर,	dev	)
		__field( अचिन्हित अक्षर,	lbal	)
		__field( अचिन्हित अक्षर,	lbam	)
		__field( अचिन्हित अक्षर,	lbah	)
		__field( अचिन्हित अक्षर,	nsect	)
		__field( अचिन्हित अक्षर,	error	)
		__field( अचिन्हित अक्षर,	hob_lbal )
		__field( अचिन्हित अक्षर,	hob_lbam )
		__field( अचिन्हित अक्षर,	hob_lbah )
		__field( अचिन्हित अक्षर,	hob_nsect )
		__field( अचिन्हित अक्षर,	hob_feature )
		__field( अचिन्हित अक्षर,	ctl )
		__field( अचिन्हित दीर्घ,	flags )
	),

	TP_fast_assign(
		__entry->ata_port	= qc->ap->prपूर्णांक_id;
		__entry->ata_dev	= qc->dev->link->pmp + qc->dev->devno;
		__entry->tag		= qc->tag;
		__entry->status		= qc->result_tf.command;
		__entry->dev		= qc->result_tf.device;
		__entry->lbal		= qc->result_tf.lbal;
		__entry->lbam		= qc->result_tf.lbam;
		__entry->lbah		= qc->result_tf.lbah;
		__entry->hob_lbal	= qc->result_tf.hob_lbal;
		__entry->hob_lbam	= qc->result_tf.hob_lbam;
		__entry->hob_lbah	= qc->result_tf.hob_lbah;
		__entry->error		= qc->result_tf.feature;
		__entry->hob_feature	= qc->result_tf.hob_feature;
		__entry->nsect		= qc->result_tf.nsect;
		__entry->hob_nsect	= qc->result_tf.hob_nsect;
	),

	TP_prपूर्णांकk("ata_port=%u ata_dev=%u tag=%d flags=%s status=%s " \
		  " res=(%02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x)",
		  __entry->ata_port, __entry->ata_dev, __entry->tag,
		  __parse_qc_flags(__entry->flags),
		  __parse_status(__entry->status),
		  __entry->status, __entry->error, __entry->nsect,
		  __entry->lbal, __entry->lbam, __entry->lbah,
		  __entry->hob_feature, __entry->hob_nsect,
		  __entry->hob_lbal, __entry->hob_lbam, __entry->hob_lbah,
		  __entry->dev)
);

DEFINE_EVENT(ata_qc_complete_ढाँचा, ata_qc_complete_पूर्णांकernal,
	     TP_PROTO(काष्ठा ata_queued_cmd *qc),
	     TP_ARGS(qc));

DEFINE_EVENT(ata_qc_complete_ढाँचा, ata_qc_complete_failed,
	     TP_PROTO(काष्ठा ata_queued_cmd *qc),
	     TP_ARGS(qc));

DEFINE_EVENT(ata_qc_complete_ढाँचा, ata_qc_complete_करोne,
	     TP_PROTO(काष्ठा ata_queued_cmd *qc),
	     TP_ARGS(qc));

TRACE_EVENT(ata_eh_link_स्वतःpsy,

	TP_PROTO(काष्ठा ata_device *dev, अचिन्हित पूर्णांक eh_action, अचिन्हित पूर्णांक eh_err_mask),

	TP_ARGS(dev, eh_action, eh_err_mask),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	ata_port )
		__field( अचिन्हित पूर्णांक,	ata_dev	)
		__field( अचिन्हित पूर्णांक,	eh_action )
		__field( अचिन्हित पूर्णांक,	eh_err_mask)
	),

	TP_fast_assign(
		__entry->ata_port	= dev->link->ap->prपूर्णांक_id;
		__entry->ata_dev	= dev->link->pmp + dev->devno;
		__entry->eh_action	= eh_action;
		__entry->eh_err_mask	= eh_err_mask;
	),

	TP_prपूर्णांकk("ata_port=%u ata_dev=%u eh_action=%s err_mask=%s",
		  __entry->ata_port, __entry->ata_dev,
		  __parse_eh_action(__entry->eh_action),
		  __parse_eh_err_mask(__entry->eh_err_mask))
);

TRACE_EVENT(ata_eh_link_स्वतःpsy_qc,

	TP_PROTO(काष्ठा ata_queued_cmd *qc),

	TP_ARGS(qc),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	ata_port )
		__field( अचिन्हित पूर्णांक,	ata_dev	)
		__field( अचिन्हित पूर्णांक,	tag	)
		__field( अचिन्हित पूर्णांक,	qc_flags )
		__field( अचिन्हित पूर्णांक,	eh_err_mask)
	),

	TP_fast_assign(
		__entry->ata_port	= qc->ap->prपूर्णांक_id;
		__entry->ata_dev	= qc->dev->link->pmp + qc->dev->devno;
		__entry->tag		= qc->tag;
		__entry->qc_flags	= qc->flags;
		__entry->eh_err_mask	= qc->err_mask;
	),

	TP_prपूर्णांकk("ata_port=%u ata_dev=%u tag=%d flags=%s err_mask=%s",
		  __entry->ata_port, __entry->ata_dev, __entry->tag,
		  __parse_qc_flags(__entry->qc_flags),
		  __parse_eh_err_mask(__entry->eh_err_mask))
);

#पूर्ण_अगर /*  _TRACE_LIBATA_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
