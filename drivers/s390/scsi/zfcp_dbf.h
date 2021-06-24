<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zfcp device driver
 * debug feature declarations
 *
 * Copyright IBM Corp. 2008, 2020
 */

#अगर_अघोषित ZFCP_DBF_H
#घोषणा ZFCP_DBF_H

#समावेश <scsi/fc/fc_fcp.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_fsf.h"
#समावेश "zfcp_def.h"

#घोषणा ZFCP_DBF_TAG_LEN       7

#घोषणा ZFCP_DBF_INVALID_WWPN	0x0000000000000000ull
#घोषणा ZFCP_DBF_INVALID_LUN	0xFFFFFFFFFFFFFFFFull

क्रमागत zfcp_dbf_pseuकरो_erp_act_type अणु
	ZFCP_PSEUDO_ERP_ACTION_RPORT_ADD = 0xff,
	ZFCP_PSEUDO_ERP_ACTION_RPORT_DEL = 0xfe,
पूर्ण;

/**
 * काष्ठा zfcp_dbf_rec_trigger - trace record क्रम triggered recovery action
 * @पढ़ोy: number of पढ़ोy recovery actions
 * @running: number of running recovery actions
 * @want: wanted recovery action
 * @need: needed recovery action
 */
काष्ठा zfcp_dbf_rec_trigger अणु
	u32 पढ़ोy;
	u32 running;
	u8 want;
	u8 need;
पूर्ण __packed;

/**
 * काष्ठा zfcp_dbf_rec_running - trace record क्रम running recovery
 * @fsf_req_id: request id क्रम fsf requests
 * @rec_status: status of the fsf request
 * @rec_step: current step of the recovery action
 * @rec_action: ERP action type
 * @rec_count: recoveries including retries क्रम particular @rec_action
 */
काष्ठा zfcp_dbf_rec_running अणु
	u64 fsf_req_id;
	u32 rec_status;
	u16 rec_step;
	u8 rec_action;
	u8 rec_count;
पूर्ण __packed;

/**
 * क्रमागत zfcp_dbf_rec_id - recovery trace record id
 * @ZFCP_DBF_REC_TRIG: triggered recovery identअगरier
 * @ZFCP_DBF_REC_RUN: running recovery identअगरier
 */
क्रमागत zfcp_dbf_rec_id अणु
	ZFCP_DBF_REC_TRIG	= 1,
	ZFCP_DBF_REC_RUN	= 2,
पूर्ण;

/**
 * काष्ठा zfcp_dbf_rec - trace record क्रम error recovery actions
 * @id: unique number of recovery record type
 * @tag: identअगरier string specअगरying the location of initiation
 * @lun: logical unit number
 * @wwpn: word wide port number
 * @d_id: destination ID
 * @adapter_status: current status of the adapter
 * @port_status: current status of the port
 * @lun_status: current status of the lun
 * @u: record type specअगरic data
 * @u.trig: काष्ठाure zfcp_dbf_rec_trigger
 * @u.run: काष्ठाure zfcp_dbf_rec_running
 */
काष्ठा zfcp_dbf_rec अणु
	u8 id;
	अक्षर tag[ZFCP_DBF_TAG_LEN];
	u64 lun;
	u64 wwpn;
	u32 d_id;
	u32 adapter_status;
	u32 port_status;
	u32 lun_status;
	जोड़ अणु
		काष्ठा zfcp_dbf_rec_trigger trig;
		काष्ठा zfcp_dbf_rec_running run;
	पूर्ण u;
पूर्ण __packed;

/**
 * क्रमागत zfcp_dbf_san_id - SAN trace record identअगरier
 * @ZFCP_DBF_SAN_REQ: request trace record id
 * @ZFCP_DBF_SAN_RES: response trace record id
 * @ZFCP_DBF_SAN_ELS: extended link service record id
 */
क्रमागत zfcp_dbf_san_id अणु
	ZFCP_DBF_SAN_REQ	= 1,
	ZFCP_DBF_SAN_RES	= 2,
	ZFCP_DBF_SAN_ELS	= 3,
पूर्ण;

/** काष्ठा zfcp_dbf_san - trace record क्रम SAN requests and responses
 * @id: unique number of recovery record type
 * @tag: identअगरier string specअगरying the location of initiation
 * @fsf_req_id: request id क्रम fsf requests
 * @payload: unक्रमmatted inक्रमmation related to request/response
 * @d_id: destination id
 */
काष्ठा zfcp_dbf_san अणु
	u8 id;
	अक्षर tag[ZFCP_DBF_TAG_LEN];
	u64 fsf_req_id;
	u32 d_id;
#घोषणा ZFCP_DBF_SAN_MAX_PAYLOAD (FC_CT_HDR_LEN + 32)
	अक्षर payload[ZFCP_DBF_SAN_MAX_PAYLOAD];
	u16 pl_len;
पूर्ण __packed;

/**
 * काष्ठा zfcp_dbf_hba_res - trace record क्रम hba responses
 * @req_issued: बारtamp when request was issued
 * @prot_status: protocol status
 * @prot_status_qual: protocol status qualअगरier
 * @fsf_status: fsf status
 * @fsf_status_qual: fsf status qualअगरier
 * @port_handle: handle क्रम port
 * @lun_handle: handle क्रम LUN
 */
काष्ठा zfcp_dbf_hba_res अणु
	u64 req_issued;
	u32 prot_status;
	u8  prot_status_qual[FSF_PROT_STATUS_QUAL_SIZE];
	u32 fsf_status;
	u8  fsf_status_qual[FSF_STATUS_QUALIFIER_SIZE];
	u32 port_handle;
	u32 lun_handle;
पूर्ण __packed;

/**
 * काष्ठा zfcp_dbf_hba_uss - trace record क्रम unsolicited status
 * @status_type: type of unsolicited status
 * @status_subtype: subtype of unsolicited status
 * @d_id: destination ID
 * @lun: logical unit number
 * @queue_designator: queue designator
 */
काष्ठा zfcp_dbf_hba_uss अणु
	u32 status_type;
	u32 status_subtype;
	u32 d_id;
	u64 lun;
	u64 queue_designator;
पूर्ण __packed;

/**
 * काष्ठा zfcp_dbf_hba_fces - trace record क्रम FC Endpoपूर्णांक Security
 * @req_issued: बारtamp when request was issued
 * @fsf_status: fsf status
 * @port_handle: handle क्रम port
 * @wwpn: remote FC port WWPN
 * @fc_security_old: old FC Endpoपूर्णांक Security
 * @fc_security_new: new FC Endpoपूर्णांक Security
 *
 */
काष्ठा zfcp_dbf_hba_fces अणु
	u64 req_issued;
	u32 fsf_status;
	u32 port_handle;
	u64 wwpn;
	u32 fc_security_old;
	u32 fc_security_new;
पूर्ण __packed;

/**
 * क्रमागत zfcp_dbf_hba_id - HBA trace record identअगरier
 * @ZFCP_DBF_HBA_RES: response trace record
 * @ZFCP_DBF_HBA_USS: unsolicited status trace record
 * @ZFCP_DBF_HBA_BIT: bit error trace record
 * @ZFCP_DBF_HBA_BASIC: basic adapter event, only trace tag, no other data
 * @ZFCP_DBF_HBA_FCES: FC Endpoपूर्णांक Security trace record
 */
क्रमागत zfcp_dbf_hba_id अणु
	ZFCP_DBF_HBA_RES	= 1,
	ZFCP_DBF_HBA_USS	= 2,
	ZFCP_DBF_HBA_BIT	= 3,
	ZFCP_DBF_HBA_BASIC	= 4,
	ZFCP_DBF_HBA_FCES	= 5,
पूर्ण;

/**
 * काष्ठा zfcp_dbf_hba - common trace record क्रम HBA records
 * @id: unique number of recovery record type
 * @tag: identअगरier string specअगरying the location of initiation
 * @fsf_req_id: request id क्रम fsf requests
 * @fsf_req_status: status of fsf request
 * @fsf_cmd: fsf command
 * @fsf_seq_no: fsf sequence number
 * @pl_len: length of payload stored as zfcp_dbf_pay
 * @u: record type specअगरic data
 * @u.res:  data क्रम fsf responses
 * @u.uss:  data क्रम unsolicited status buffer
 * @u.be:   data क्रम bit error unsolicited status buffer
 * @u.fces: data क्रम FC Endpoपूर्णांक Security
 */
काष्ठा zfcp_dbf_hba अणु
	u8 id;
	अक्षर tag[ZFCP_DBF_TAG_LEN];
	u64 fsf_req_id;
	u32 fsf_req_status;
	u32 fsf_cmd;
	u32 fsf_seq_no;
	u16 pl_len;
	जोड़ अणु
		काष्ठा zfcp_dbf_hba_res res;
		काष्ठा zfcp_dbf_hba_uss uss;
		काष्ठा fsf_bit_error_payload be;
		काष्ठा zfcp_dbf_hba_fces fces;
	पूर्ण u;
पूर्ण __packed;

/**
 * क्रमागत zfcp_dbf_scsi_id - scsi trace record identअगरier
 * @ZFCP_DBF_SCSI_CMND: scsi command trace record
 */
क्रमागत zfcp_dbf_scsi_id अणु
	ZFCP_DBF_SCSI_CMND	= 1,
पूर्ण;

/**
 * काष्ठा zfcp_dbf_scsi - common trace record क्रम SCSI records
 * @id: unique number of recovery record type
 * @tag: identअगरier string specअगरying the location of initiation
 * @scsi_id: scsi device id
 * @scsi_lun: scsi device logical unit number, low part of 64 bit, old 32 bit
 * @scsi_result: scsi result
 * @scsi_retries: current retry number of scsi request
 * @scsi_allowed: allowed retries
 * @fcp_rsp_info: FCP response info code
 * @scsi_opcode: scsi opcode
 * @fsf_req_id: request id of fsf request
 * @host_scribble: LLD specअगरic data attached to SCSI request
 * @pl_len: length of payload stored as zfcp_dbf_pay
 * @fcp_rsp: response क्रम FCP request
 * @scsi_lun_64_hi: scsi device logical unit number, high part of 64 bit
 */
काष्ठा zfcp_dbf_scsi अणु
	u8 id;
	अक्षर tag[ZFCP_DBF_TAG_LEN];
	u32 scsi_id;
	u32 scsi_lun;
	u32 scsi_result;
	u8 scsi_retries;
	u8 scsi_allowed;
	u8 fcp_rsp_info;
#घोषणा ZFCP_DBF_SCSI_OPCODE	16
	u8 scsi_opcode[ZFCP_DBF_SCSI_OPCODE];
	u64 fsf_req_id;
	u64 host_scribble;
	u16 pl_len;
	काष्ठा fcp_resp_with_ext fcp_rsp;
	u32 scsi_lun_64_hi;
पूर्ण __packed;

/**
 * काष्ठा zfcp_dbf_pay - trace record क्रम unक्रमmatted payload inक्रमmation
 * @area: area this record is originated from
 * @counter: ascending record number
 * @fsf_req_id: request id of fsf request
 * @data: unक्रमmatted data
 */
काष्ठा zfcp_dbf_pay अणु
	u8 counter;
	अक्षर area[ZFCP_DBF_TAG_LEN];
	u64 fsf_req_id;
#घोषणा ZFCP_DBF_PAY_MAX_REC 0x100
	अक्षर data[ZFCP_DBF_PAY_MAX_REC];
पूर्ण __packed;

/**
 * काष्ठा zfcp_dbf - मुख्य dbf trace काष्ठाure
 * @pay: reference to payload trace area
 * @rec: reference to recovery trace area
 * @hba: reference to hba trace area
 * @san: reference to san trace area
 * @scsi: reference to scsi trace area
 * @pay_lock: lock protecting payload trace buffer
 * @rec_lock: lock protecting recovery trace buffer
 * @hba_lock: lock protecting hba trace buffer
 * @san_lock: lock protecting san trace buffer
 * @scsi_lock: lock protecting scsi trace buffer
 * @pay_buf: pre-allocated buffer क्रम payload
 * @rec_buf: pre-allocated buffer क्रम recovery
 * @hba_buf: pre-allocated buffer क्रम hba
 * @san_buf: pre-allocated buffer क्रम san
 * @scsi_buf: pre-allocated buffer क्रम scsi
 */
काष्ठा zfcp_dbf अणु
	debug_info_t			*pay;
	debug_info_t			*rec;
	debug_info_t			*hba;
	debug_info_t			*san;
	debug_info_t			*scsi;
	spinlock_t			pay_lock;
	spinlock_t			rec_lock;
	spinlock_t			hba_lock;
	spinlock_t			san_lock;
	spinlock_t			scsi_lock;
	काष्ठा zfcp_dbf_pay		pay_buf;
	काष्ठा zfcp_dbf_rec		rec_buf;
	काष्ठा zfcp_dbf_hba		hba_buf;
	काष्ठा zfcp_dbf_san		san_buf;
	काष्ठा zfcp_dbf_scsi		scsi_buf;
पूर्ण;

/**
 * zfcp_dbf_hba_fsf_resp_suppress - true अगर we should not trace by शेष
 * @req: request that has been completed
 *
 * Returns true अगर FCP response with only benign residual under count.
 */
अटल अंतरभूत
bool zfcp_dbf_hba_fsf_resp_suppress(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा fsf_qtcb *qtcb = req->qtcb;
	u32 fsf_stat = qtcb->header.fsf_status;
	काष्ठा fcp_resp *fcp_rsp;
	u8 rsp_flags, fr_status;

	अगर (qtcb->prefix.qtcb_type != FSF_IO_COMMAND)
		वापस false; /* not an FCP response */
	fcp_rsp = &qtcb->bottom.io.fcp_rsp.iu.resp;
	rsp_flags = fcp_rsp->fr_flags;
	fr_status = fcp_rsp->fr_status;
	वापस (fsf_stat == FSF_FCP_RSP_AVAILABLE) &&
		(rsp_flags == FCP_RESID_UNDER) &&
		(fr_status == SAM_STAT_GOOD);
पूर्ण

अटल अंतरभूत
व्योम zfcp_dbf_hba_fsf_resp(अक्षर *tag, पूर्णांक level, काष्ठा zfcp_fsf_req *req)
अणु
	अगर (debug_level_enabled(req->adapter->dbf->hba, level))
		zfcp_dbf_hba_fsf_res(tag, level, req);
पूर्ण

/**
 * zfcp_dbf_hba_fsf_response - trace event क्रम request completion
 * @req: request that has been completed
 */
अटल अंतरभूत
व्योम zfcp_dbf_hba_fsf_response(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा fsf_qtcb *qtcb = req->qtcb;

	अगर (unlikely(req->status & (ZFCP_STATUS_FSFREQ_DISMISSED |
				    ZFCP_STATUS_FSFREQ_ERROR))) अणु
		zfcp_dbf_hba_fsf_resp("fs_rerr", 3, req);

	पूर्ण अन्यथा अगर ((qtcb->prefix.prot_status != FSF_PROT_GOOD) &&
	    (qtcb->prefix.prot_status != FSF_PROT_FSF_STATUS_PRESENTED)) अणु
		zfcp_dbf_hba_fsf_resp("fs_perr", 1, req);

	पूर्ण अन्यथा अगर (qtcb->header.fsf_status != FSF_GOOD) अणु
		zfcp_dbf_hba_fsf_resp("fs_ferr",
				      zfcp_dbf_hba_fsf_resp_suppress(req)
				      ? 5 : 1, req);

	पूर्ण अन्यथा अगर ((qtcb->header.fsf_command == FSF_QTCB_OPEN_PORT_WITH_DID) ||
		   (qtcb->header.fsf_command == FSF_QTCB_OPEN_LUN)) अणु
		zfcp_dbf_hba_fsf_resp("fs_open", 4, req);

	पूर्ण अन्यथा अगर (qtcb->header.log_length) अणु
		zfcp_dbf_hba_fsf_resp("fs_qtcb", 5, req);

	पूर्ण अन्यथा अणु
		zfcp_dbf_hba_fsf_resp("fs_norm", 6, req);
	पूर्ण
पूर्ण

अटल अंतरभूत
व्योम _zfcp_dbf_scsi(अक्षर *tag, पूर्णांक level, काष्ठा scsi_cmnd *scmd,
		   काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = (काष्ठा zfcp_adapter *)
					scmd->device->host->hostdata[0];

	अगर (debug_level_enabled(adapter->dbf->scsi, level))
		zfcp_dbf_scsi_common(tag, level, scmd->device, scmd, req);
पूर्ण

/**
 * zfcp_dbf_scsi_result - trace event क्रम SCSI command completion
 * @scmd: SCSI command poपूर्णांकer
 * @req: FSF request used to issue SCSI command
 */
अटल अंतरभूत
व्योम zfcp_dbf_scsi_result(काष्ठा scsi_cmnd *scmd, काष्ठा zfcp_fsf_req *req)
अणु
	अगर (scmd->result != 0)
		_zfcp_dbf_scsi("rsl_err", 3, scmd, req);
	अन्यथा अगर (scmd->retries > 0)
		_zfcp_dbf_scsi("rsl_ret", 4, scmd, req);
	अन्यथा
		_zfcp_dbf_scsi("rsl_nor", 6, scmd, req);
पूर्ण

/**
 * zfcp_dbf_scsi_fail_send - trace event क्रम failure to send SCSI command
 * @scmd: SCSI command poपूर्णांकer
 */
अटल अंतरभूत
व्योम zfcp_dbf_scsi_fail_send(काष्ठा scsi_cmnd *scmd)
अणु
	_zfcp_dbf_scsi("rsl_fai", 4, scmd, शून्य);
पूर्ण

/**
 * zfcp_dbf_scsi_पात - trace event क्रम SCSI command पात
 * @tag: tag indicating success or failure of पात operation
 * @scmd: SCSI command to be पातed
 * @fsf_req: request containing पात (might be शून्य)
 */
अटल अंतरभूत
व्योम zfcp_dbf_scsi_पात(अक्षर *tag, काष्ठा scsi_cmnd *scmd,
			 काष्ठा zfcp_fsf_req *fsf_req)
अणु
	_zfcp_dbf_scsi(tag, 1, scmd, fsf_req);
पूर्ण

/**
 * zfcp_dbf_scsi_devreset() - Trace event क्रम Logical Unit or Target Reset.
 * @tag: Tag indicating success or failure of reset operation.
 * @sdev: Poपूर्णांकer to SCSI device as context क्रम this event.
 * @flag: Indicates type of reset (Target Reset, Logical Unit Reset).
 * @fsf_req: Poपूर्णांकer to FSF request representing the TMF, or शून्य.
 */
अटल अंतरभूत
व्योम zfcp_dbf_scsi_devreset(अक्षर *tag, काष्ठा scsi_device *sdev, u8 flag,
			    काष्ठा zfcp_fsf_req *fsf_req)
अणु
	काष्ठा zfcp_adapter *adapter = (काष्ठा zfcp_adapter *)
					sdev->host->hostdata[0];
	अक्षर पंचांगp_tag[ZFCP_DBF_TAG_LEN];
	अटल पूर्णांक स्थिर level = 1;

	अगर (unlikely(!debug_level_enabled(adapter->dbf->scsi, level)))
		वापस;

	अगर (flag == FCP_TMF_TGT_RESET)
		स_नकल(पंचांगp_tag, "tr_", 3);
	अन्यथा
		स_नकल(पंचांगp_tag, "lr_", 3);

	स_नकल(&पंचांगp_tag[3], tag, 4);
	zfcp_dbf_scsi_common(पंचांगp_tag, level, sdev, शून्य, fsf_req);
पूर्ण

/**
 * zfcp_dbf_scsi_nullcmnd() - trace शून्यअगरy of SCSI command in dev/tgt-reset.
 * @scmnd: SCSI command that was शून्यअगरied.
 * @fsf_req: request that owned @scmnd.
 */
अटल अंतरभूत व्योम zfcp_dbf_scsi_nullcmnd(काष्ठा scsi_cmnd *scmnd,
					  काष्ठा zfcp_fsf_req *fsf_req)
अणु
	_zfcp_dbf_scsi("scfc__1", 3, scmnd, fsf_req);
पूर्ण

#पूर्ण_अगर /* ZFCP_DBF_H */
