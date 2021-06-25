<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Debug traces क्रम zfcp.
 *
 * Copyright IBM Corp. 2002, 2020
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/debug.h>
#समावेश "zfcp_dbf.h"
#समावेश "zfcp_ext.h"
#समावेश "zfcp_fc.h"

अटल u32 dbfsize = 4;

module_param(dbfsize, uपूर्णांक, 0400);
MODULE_PARM_DESC(dbfsize,
		 "number of pages for each debug feature area (default 4)");

अटल u32 dbflevel = 3;

module_param(dbflevel, uपूर्णांक, 0400);
MODULE_PARM_DESC(dbflevel,
		 "log level for each debug feature area "
		 "(default 3, range 0..6)");

अटल अंतरभूत अचिन्हित पूर्णांक zfcp_dbf_plen(अचिन्हित पूर्णांक offset)
अणु
	वापस माप(काष्ठा zfcp_dbf_pay) + offset - ZFCP_DBF_PAY_MAX_REC;
पूर्ण

अटल अंतरभूत
व्योम zfcp_dbf_pl_ग_लिखो(काष्ठा zfcp_dbf *dbf, व्योम *data, u16 length, अक्षर *area,
		       u64 req_id)
अणु
	काष्ठा zfcp_dbf_pay *pl = &dbf->pay_buf;
	u16 offset = 0, rec_length;

	spin_lock(&dbf->pay_lock);
	स_रखो(pl, 0, माप(*pl));
	pl->fsf_req_id = req_id;
	स_नकल(pl->area, area, ZFCP_DBF_TAG_LEN);

	जबतक (offset < length) अणु
		rec_length = min((u16) ZFCP_DBF_PAY_MAX_REC,
				 (u16) (length - offset));
		स_नकल(pl->data, data + offset, rec_length);
		debug_event(dbf->pay, 1, pl, zfcp_dbf_plen(rec_length));

		offset += rec_length;
		pl->counter++;
	पूर्ण

	spin_unlock(&dbf->pay_lock);
पूर्ण

/**
 * zfcp_dbf_hba_fsf_res - trace event क्रम fsf responses
 * @tag: tag indicating which kind of FSF response has been received
 * @level: trace level to be used क्रम event
 * @req: request क्रम which a response was received
 */
व्योम zfcp_dbf_hba_fsf_res(अक्षर *tag, पूर्णांक level, काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_dbf *dbf = req->adapter->dbf;
	काष्ठा fsf_qtcb_prefix *q_pref = &req->qtcb->prefix;
	काष्ठा fsf_qtcb_header *q_head = &req->qtcb->header;
	काष्ठा zfcp_dbf_hba *rec = &dbf->hba_buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_HBA_RES;
	rec->fsf_req_id = req->req_id;
	rec->fsf_req_status = req->status;
	rec->fsf_cmd = q_head->fsf_command;
	rec->fsf_seq_no = q_pref->req_seq_no;
	rec->u.res.req_issued = req->issued;
	rec->u.res.prot_status = q_pref->prot_status;
	rec->u.res.fsf_status = q_head->fsf_status;
	rec->u.res.port_handle = q_head->port_handle;
	rec->u.res.lun_handle = q_head->lun_handle;

	स_नकल(rec->u.res.prot_status_qual, &q_pref->prot_status_qual,
	       FSF_PROT_STATUS_QUAL_SIZE);
	स_नकल(rec->u.res.fsf_status_qual, &q_head->fsf_status_qual,
	       FSF_STATUS_QUALIFIER_SIZE);

	rec->pl_len = q_head->log_length;
	zfcp_dbf_pl_ग_लिखो(dbf, (अक्षर *)q_pref + q_head->log_start,
			  rec->pl_len, "fsf_res", req->req_id);

	debug_event(dbf->hba, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
पूर्ण

/**
 * zfcp_dbf_hba_fsf_fces - trace event क्रम fsf responses related to
 *			   FC Endpoपूर्णांक Security (FCES)
 * @tag: tag indicating which kind of FC Endpoपूर्णांक Security event has occurred
 * @req: request क्रम which a response was received
 * @wwpn: remote port or ZFCP_DBF_INVALID_WWPN
 * @fc_security_old: old FC Endpoपूर्णांक Security of FCP device or connection
 * @fc_security_new: new FC Endpoपूर्णांक Security of FCP device or connection
 */
व्योम zfcp_dbf_hba_fsf_fces(अक्षर *tag, स्थिर काष्ठा zfcp_fsf_req *req, u64 wwpn,
			   u32 fc_security_old, u32 fc_security_new)
अणु
	काष्ठा zfcp_dbf *dbf = req->adapter->dbf;
	काष्ठा fsf_qtcb_prefix *q_pref = &req->qtcb->prefix;
	काष्ठा fsf_qtcb_header *q_head = &req->qtcb->header;
	काष्ठा zfcp_dbf_hba *rec = &dbf->hba_buf;
	अटल पूर्णांक स्थिर level = 3;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!debug_level_enabled(dbf->hba, level)))
		वापस;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_HBA_FCES;
	rec->fsf_req_id = req->req_id;
	rec->fsf_req_status = req->status;
	rec->fsf_cmd = q_head->fsf_command;
	rec->fsf_seq_no = q_pref->req_seq_no;
	rec->u.fces.req_issued = req->issued;
	rec->u.fces.fsf_status = q_head->fsf_status;
	rec->u.fces.port_handle = q_head->port_handle;
	rec->u.fces.wwpn = wwpn;
	rec->u.fces.fc_security_old = fc_security_old;
	rec->u.fces.fc_security_new = fc_security_new;

	debug_event(dbf->hba, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
पूर्ण

/**
 * zfcp_dbf_hba_fsf_uss - trace event क्रम an unsolicited status buffer
 * @tag: tag indicating which kind of unsolicited status has been received
 * @req: request providing the unsolicited status
 */
व्योम zfcp_dbf_hba_fsf_uss(अक्षर *tag, काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_dbf *dbf = req->adapter->dbf;
	काष्ठा fsf_status_पढ़ो_buffer *srb = req->data;
	काष्ठा zfcp_dbf_hba *rec = &dbf->hba_buf;
	अटल पूर्णांक स्थिर level = 2;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!debug_level_enabled(dbf->hba, level)))
		वापस;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_HBA_USS;
	rec->fsf_req_id = req->req_id;
	rec->fsf_req_status = req->status;
	rec->fsf_cmd = FSF_QTCB_UNSOLICITED_STATUS;

	अगर (!srb)
		जाओ log;

	rec->u.uss.status_type = srb->status_type;
	rec->u.uss.status_subtype = srb->status_subtype;
	rec->u.uss.d_id = ntoh24(srb->d_id);
	rec->u.uss.lun = srb->fcp_lun;
	स_नकल(&rec->u.uss.queue_designator, &srb->queue_designator,
	       माप(rec->u.uss.queue_designator));

	/* status पढ़ो buffer payload length */
	rec->pl_len = (!srb->length) ? 0 : srb->length -
			दुरत्व(काष्ठा fsf_status_पढ़ो_buffer, payload);

	अगर (rec->pl_len)
		zfcp_dbf_pl_ग_लिखो(dbf, srb->payload.data, rec->pl_len,
				  "fsf_uss", req->req_id);
log:
	debug_event(dbf->hba, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
पूर्ण

/**
 * zfcp_dbf_hba_bit_err - trace event क्रम bit error conditions
 * @tag: tag indicating which kind of bit error unsolicited status was received
 * @req: request which caused the bit_error condition
 */
व्योम zfcp_dbf_hba_bit_err(अक्षर *tag, काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_dbf *dbf = req->adapter->dbf;
	काष्ठा zfcp_dbf_hba *rec = &dbf->hba_buf;
	काष्ठा fsf_status_पढ़ो_buffer *sr_buf = req->data;
	अटल पूर्णांक स्थिर level = 1;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!debug_level_enabled(dbf->hba, level)))
		वापस;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_HBA_BIT;
	rec->fsf_req_id = req->req_id;
	rec->fsf_req_status = req->status;
	rec->fsf_cmd = FSF_QTCB_UNSOLICITED_STATUS;
	स_नकल(&rec->u.be, &sr_buf->payload.bit_error,
	       माप(काष्ठा fsf_bit_error_payload));

	debug_event(dbf->hba, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
पूर्ण

/**
 * zfcp_dbf_hba_def_err - trace event क्रम deferred error messages
 * @adapter: poपूर्णांकer to काष्ठा zfcp_adapter
 * @req_id: request id which caused the deferred error message
 * @scount: number of sbals incl. the संकेतing sbal
 * @pl: array of all involved sbals
 */
व्योम zfcp_dbf_hba_def_err(काष्ठा zfcp_adapter *adapter, u64 req_id, u16 scount,
			  व्योम **pl)
अणु
	काष्ठा zfcp_dbf *dbf = adapter->dbf;
	काष्ठा zfcp_dbf_pay *payload = &dbf->pay_buf;
	अचिन्हित दीर्घ flags;
	अटल पूर्णांक स्थिर level = 1;
	u16 length;

	अगर (unlikely(!debug_level_enabled(dbf->pay, level)))
		वापस;

	अगर (!pl)
		वापस;

	spin_lock_irqsave(&dbf->pay_lock, flags);
	स_रखो(payload, 0, माप(*payload));

	स_नकल(payload->area, "def_err", 7);
	payload->fsf_req_id = req_id;
	payload->counter = 0;
	length = min((u16)माप(काष्ठा qdio_buffer),
		     (u16)ZFCP_DBF_PAY_MAX_REC);

	जबतक (payload->counter < scount && (अक्षर *)pl[payload->counter]) अणु
		स_नकल(payload->data, (अक्षर *)pl[payload->counter], length);
		debug_event(dbf->pay, level, payload, zfcp_dbf_plen(length));
		payload->counter++;
	पूर्ण

	spin_unlock_irqrestore(&dbf->pay_lock, flags);
पूर्ण

अटल व्योम zfcp_dbf_set_common(काष्ठा zfcp_dbf_rec *rec,
				काष्ठा zfcp_adapter *adapter,
				काष्ठा zfcp_port *port,
				काष्ठा scsi_device *sdev)
अणु
	rec->adapter_status = atomic_पढ़ो(&adapter->status);
	अगर (port) अणु
		rec->port_status = atomic_पढ़ो(&port->status);
		rec->wwpn = port->wwpn;
		rec->d_id = port->d_id;
	पूर्ण
	अगर (sdev) अणु
		rec->lun_status = atomic_पढ़ो(&sdev_to_zfcp(sdev)->status);
		rec->lun = zfcp_scsi_dev_lun(sdev);
	पूर्ण अन्यथा
		rec->lun = ZFCP_DBF_INVALID_LUN;
पूर्ण

/**
 * zfcp_dbf_rec_trig - trace event related to triggered recovery
 * @tag: identअगरier क्रम event
 * @adapter: adapter on which the erp_action should run
 * @port: remote port involved in the erp_action
 * @sdev: scsi device involved in the erp_action
 * @want: wanted erp_action
 * @need: required erp_action
 *
 * The adapter->erp_lock has to be held.
 */
व्योम zfcp_dbf_rec_trig(अक्षर *tag, काष्ठा zfcp_adapter *adapter,
		       काष्ठा zfcp_port *port, काष्ठा scsi_device *sdev,
		       u8 want, u8 need)
अणु
	काष्ठा zfcp_dbf *dbf = adapter->dbf;
	काष्ठा zfcp_dbf_rec *rec = &dbf->rec_buf;
	अटल पूर्णांक स्थिर level = 1;
	काष्ठा list_head *entry;
	अचिन्हित दीर्घ flags;

	lockdep_निश्चित_held(&adapter->erp_lock);

	अगर (unlikely(!debug_level_enabled(dbf->rec, level)))
		वापस;

	spin_lock_irqsave(&dbf->rec_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	rec->id = ZFCP_DBF_REC_TRIG;
	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	zfcp_dbf_set_common(rec, adapter, port, sdev);

	list_क्रम_each(entry, &adapter->erp_पढ़ोy_head)
		rec->u.trig.पढ़ोy++;

	list_क्रम_each(entry, &adapter->erp_running_head)
		rec->u.trig.running++;

	rec->u.trig.want = want;
	rec->u.trig.need = need;

	debug_event(dbf->rec, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->rec_lock, flags);
पूर्ण

/**
 * zfcp_dbf_rec_trig_lock - trace event related to triggered recovery with lock
 * @tag: identअगरier क्रम event
 * @adapter: adapter on which the erp_action should run
 * @port: remote port involved in the erp_action
 * @sdev: scsi device involved in the erp_action
 * @want: wanted erp_action
 * @need: required erp_action
 *
 * The adapter->erp_lock must not be held.
 */
व्योम zfcp_dbf_rec_trig_lock(अक्षर *tag, काष्ठा zfcp_adapter *adapter,
			    काष्ठा zfcp_port *port, काष्ठा scsi_device *sdev,
			    u8 want, u8 need)
अणु
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&adapter->erp_lock, flags);
	zfcp_dbf_rec_trig(tag, adapter, port, sdev, want, need);
	पढ़ो_unlock_irqrestore(&adapter->erp_lock, flags);
पूर्ण

/**
 * zfcp_dbf_rec_run_lvl - trace event related to running recovery
 * @level: trace level to be used क्रम event
 * @tag: identअगरier क्रम event
 * @erp: erp_action running
 */
व्योम zfcp_dbf_rec_run_lvl(पूर्णांक level, अक्षर *tag, काष्ठा zfcp_erp_action *erp)
अणु
	काष्ठा zfcp_dbf *dbf = erp->adapter->dbf;
	काष्ठा zfcp_dbf_rec *rec = &dbf->rec_buf;
	अचिन्हित दीर्घ flags;

	अगर (!debug_level_enabled(dbf->rec, level))
		वापस;

	spin_lock_irqsave(&dbf->rec_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	rec->id = ZFCP_DBF_REC_RUN;
	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	zfcp_dbf_set_common(rec, erp->adapter, erp->port, erp->sdev);

	rec->u.run.fsf_req_id = erp->fsf_req_id;
	rec->u.run.rec_status = erp->status;
	rec->u.run.rec_step = erp->step;
	rec->u.run.rec_action = erp->type;

	अगर (erp->sdev)
		rec->u.run.rec_count =
			atomic_पढ़ो(&sdev_to_zfcp(erp->sdev)->erp_counter);
	अन्यथा अगर (erp->port)
		rec->u.run.rec_count = atomic_पढ़ो(&erp->port->erp_counter);
	अन्यथा
		rec->u.run.rec_count = atomic_पढ़ो(&erp->adapter->erp_counter);

	debug_event(dbf->rec, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->rec_lock, flags);
पूर्ण

/**
 * zfcp_dbf_rec_run - trace event related to running recovery
 * @tag: identअगरier क्रम event
 * @erp: erp_action running
 */
व्योम zfcp_dbf_rec_run(अक्षर *tag, काष्ठा zfcp_erp_action *erp)
अणु
	zfcp_dbf_rec_run_lvl(1, tag, erp);
पूर्ण

/**
 * zfcp_dbf_rec_run_wka - trace wka port event with info like running recovery
 * @tag: identअगरier क्रम event
 * @wka_port: well known address port
 * @req_id: request ID to correlate with potential HBA trace record
 */
व्योम zfcp_dbf_rec_run_wka(अक्षर *tag, काष्ठा zfcp_fc_wka_port *wka_port,
			  u64 req_id)
अणु
	काष्ठा zfcp_dbf *dbf = wka_port->adapter->dbf;
	काष्ठा zfcp_dbf_rec *rec = &dbf->rec_buf;
	अटल पूर्णांक स्थिर level = 1;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!debug_level_enabled(dbf->rec, level)))
		वापस;

	spin_lock_irqsave(&dbf->rec_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	rec->id = ZFCP_DBF_REC_RUN;
	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->port_status = wka_port->status;
	rec->d_id = wka_port->d_id;
	rec->lun = ZFCP_DBF_INVALID_LUN;

	rec->u.run.fsf_req_id = req_id;
	rec->u.run.rec_status = ~0;
	rec->u.run.rec_step = ~0;
	rec->u.run.rec_action = ~0;
	rec->u.run.rec_count = ~0;

	debug_event(dbf->rec, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->rec_lock, flags);
पूर्ण

#घोषणा ZFCP_DBF_SAN_LEVEL 1

अटल अंतरभूत
व्योम zfcp_dbf_san(अक्षर *tag, काष्ठा zfcp_dbf *dbf,
		  अक्षर *paytag, काष्ठा scatterlist *sg, u8 id, u16 len,
		  u64 req_id, u32 d_id, u16 cap_len)
अणु
	काष्ठा zfcp_dbf_san *rec = &dbf->san_buf;
	u16 rec_len;
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_dbf_pay *payload = &dbf->pay_buf;
	u16 pay_sum = 0;

	spin_lock_irqsave(&dbf->san_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	rec->id = id;
	rec->fsf_req_id = req_id;
	rec->d_id = d_id;
	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->pl_len = len; /* full length even अगर we cap pay below */
	अगर (!sg)
		जाओ out;
	rec_len = min_t(अचिन्हित पूर्णांक, sg->length, ZFCP_DBF_SAN_MAX_PAYLOAD);
	स_नकल(rec->payload, sg_virt(sg), rec_len); /* part of 1st sg entry */
	अगर (len <= rec_len)
		जाओ out; /* skip pay record अगर full content in rec->payload */

	/* अगर (len > rec_len):
	 * dump data up to cap_len ignoring small duplicate in rec->payload
	 */
	spin_lock(&dbf->pay_lock);
	स_रखो(payload, 0, माप(*payload));
	स_नकल(payload->area, paytag, ZFCP_DBF_TAG_LEN);
	payload->fsf_req_id = req_id;
	payload->counter = 0;
	क्रम (; sg && pay_sum < cap_len; sg = sg_next(sg)) अणु
		u16 pay_len, offset = 0;

		जबतक (offset < sg->length && pay_sum < cap_len) अणु
			pay_len = min((u16)ZFCP_DBF_PAY_MAX_REC,
				      (u16)(sg->length - offset));
			/* cap_len <= pay_sum < cap_len+ZFCP_DBF_PAY_MAX_REC */
			स_नकल(payload->data, sg_virt(sg) + offset, pay_len);
			debug_event(dbf->pay, ZFCP_DBF_SAN_LEVEL, payload,
				    zfcp_dbf_plen(pay_len));
			payload->counter++;
			offset += pay_len;
			pay_sum += pay_len;
		पूर्ण
	पूर्ण
	spin_unlock(&dbf->pay_lock);

out:
	debug_event(dbf->san, ZFCP_DBF_SAN_LEVEL, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->san_lock, flags);
पूर्ण

/**
 * zfcp_dbf_san_req - trace event क्रम issued SAN request
 * @tag: identअगरier क्रम event
 * @fsf: request containing issued CT or ELS data
 * @d_id: N_Port_ID where SAN request is sent to
 * d_id: destination ID
 */
व्योम zfcp_dbf_san_req(अक्षर *tag, काष्ठा zfcp_fsf_req *fsf, u32 d_id)
अणु
	काष्ठा zfcp_dbf *dbf = fsf->adapter->dbf;
	काष्ठा zfcp_fsf_ct_els *ct_els = fsf->data;
	u16 length;

	अगर (unlikely(!debug_level_enabled(dbf->san, ZFCP_DBF_SAN_LEVEL)))
		वापस;

	length = (u16)zfcp_qdio_real_bytes(ct_els->req);
	zfcp_dbf_san(tag, dbf, "san_req", ct_els->req, ZFCP_DBF_SAN_REQ,
		     length, fsf->req_id, d_id, length);
पूर्ण

अटल u16 zfcp_dbf_san_res_cap_len_अगर_gpn_ft(अक्षर *tag,
					      काष्ठा zfcp_fsf_req *fsf,
					      u16 len)
अणु
	काष्ठा zfcp_fsf_ct_els *ct_els = fsf->data;
	काष्ठा fc_ct_hdr *reqh = sg_virt(ct_els->req);
	काष्ठा fc_ns_gid_ft *reqn = (काष्ठा fc_ns_gid_ft *)(reqh + 1);
	काष्ठा scatterlist *resp_entry = ct_els->resp;
	काष्ठा fc_ct_hdr *resph;
	काष्ठा fc_gpn_ft_resp *acc;
	पूर्णांक max_entries, x, last = 0;

	अगर (!(स_भेद(tag, "fsscth2", 7) == 0
	      && ct_els->d_id == FC_FID_सूची_SERV
	      && reqh->ct_rev == FC_CT_REV
	      && reqh->ct_in_id[0] == 0
	      && reqh->ct_in_id[1] == 0
	      && reqh->ct_in_id[2] == 0
	      && reqh->ct_fs_type == FC_FST_सूची
	      && reqh->ct_fs_subtype == FC_NS_SUBTYPE
	      && reqh->ct_options == 0
	      && reqh->_ct_resvd1 == 0
	      && reqh->ct_cmd == cpu_to_be16(FC_NS_GPN_FT)
	      /* reqh->ct_mr_size can vary so करो not match but पढ़ो below */
	      && reqh->_ct_resvd2 == 0
	      && reqh->ct_reason == 0
	      && reqh->ct_explan == 0
	      && reqh->ct_venकरोr == 0
	      && reqn->fn_resvd == 0
	      && reqn->fn_करोमुख्य_id_scope == 0
	      && reqn->fn_area_id_scope == 0
	      && reqn->fn_fc4_type == FC_TYPE_FCP))
		वापस len; /* not GPN_FT response so करो not cap */

	acc = sg_virt(resp_entry);

	/* cap all but accept CT responses to at least the CT header */
	resph = (काष्ठा fc_ct_hdr *)acc;
	अगर ((ct_els->status) ||
	    (resph->ct_cmd != cpu_to_be16(FC_FS_ACC)))
		वापस max(FC_CT_HDR_LEN, ZFCP_DBF_SAN_MAX_PAYLOAD);

	max_entries = (be16_to_cpu(reqh->ct_mr_size) * 4 /
		       माप(काष्ठा fc_gpn_ft_resp))
		+ 1 /* zfcp_fc_scan_ports: bytes correct, entries off-by-one
		     * to account क्रम header as 1st pseuकरो "entry" */;

	/* the basic CT_IU preamble is the same size as one entry in the GPN_FT
	 * response, allowing us to skip special handling क्रम it - just skip it
	 */
	क्रम (x = 1; x < max_entries && !last; x++) अणु
		अगर (x % (ZFCP_FC_GPN_FT_ENT_PAGE + 1))
			acc++;
		अन्यथा
			acc = sg_virt(++resp_entry);

		last = acc->fp_flags & FC_NS_FID_LAST;
	पूर्ण
	len = min(len, (u16)(x * माप(काष्ठा fc_gpn_ft_resp)));
	वापस len; /* cap after last entry */
पूर्ण

/**
 * zfcp_dbf_san_res - trace event क्रम received SAN request
 * @tag: identअगरier क्रम event
 * @fsf: request containing received CT or ELS data
 */
व्योम zfcp_dbf_san_res(अक्षर *tag, काष्ठा zfcp_fsf_req *fsf)
अणु
	काष्ठा zfcp_dbf *dbf = fsf->adapter->dbf;
	काष्ठा zfcp_fsf_ct_els *ct_els = fsf->data;
	u16 length;

	अगर (unlikely(!debug_level_enabled(dbf->san, ZFCP_DBF_SAN_LEVEL)))
		वापस;

	length = (u16)zfcp_qdio_real_bytes(ct_els->resp);
	zfcp_dbf_san(tag, dbf, "san_res", ct_els->resp, ZFCP_DBF_SAN_RES,
		     length, fsf->req_id, ct_els->d_id,
		     zfcp_dbf_san_res_cap_len_अगर_gpn_ft(tag, fsf, length));
पूर्ण

/**
 * zfcp_dbf_san_in_els - trace event क्रम incoming ELS
 * @tag: identअगरier क्रम event
 * @fsf: request containing received ELS data
 */
व्योम zfcp_dbf_san_in_els(अक्षर *tag, काष्ठा zfcp_fsf_req *fsf)
अणु
	काष्ठा zfcp_dbf *dbf = fsf->adapter->dbf;
	काष्ठा fsf_status_पढ़ो_buffer *srb =
		(काष्ठा fsf_status_पढ़ो_buffer *) fsf->data;
	u16 length;
	काष्ठा scatterlist sg;

	अगर (unlikely(!debug_level_enabled(dbf->san, ZFCP_DBF_SAN_LEVEL)))
		वापस;

	length = (u16)(srb->length -
			दुरत्व(काष्ठा fsf_status_पढ़ो_buffer, payload));
	sg_init_one(&sg, srb->payload.data, length);
	zfcp_dbf_san(tag, dbf, "san_els", &sg, ZFCP_DBF_SAN_ELS, length,
		     fsf->req_id, ntoh24(srb->d_id), length);
पूर्ण

/**
 * zfcp_dbf_scsi_common() - Common trace event helper क्रम scsi.
 * @tag: Identअगरier क्रम event.
 * @level: trace level of event.
 * @sdev: Poपूर्णांकer to SCSI device as context क्रम this event.
 * @sc: Poपूर्णांकer to SCSI command, or शून्य with task management function (TMF).
 * @fsf: Poपूर्णांकer to FSF request, or शून्य.
 */
व्योम zfcp_dbf_scsi_common(अक्षर *tag, पूर्णांक level, काष्ठा scsi_device *sdev,
			  काष्ठा scsi_cmnd *sc, काष्ठा zfcp_fsf_req *fsf)
अणु
	काष्ठा zfcp_adapter *adapter =
		(काष्ठा zfcp_adapter *) sdev->host->hostdata[0];
	काष्ठा zfcp_dbf *dbf = adapter->dbf;
	काष्ठा zfcp_dbf_scsi *rec = &dbf->scsi_buf;
	काष्ठा fcp_resp_with_ext *fcp_rsp;
	काष्ठा fcp_resp_rsp_info *fcp_rsp_info;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dbf->scsi_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_SCSI_CMND;
	अगर (sc) अणु
		rec->scsi_result = sc->result;
		rec->scsi_retries = sc->retries;
		rec->scsi_allowed = sc->allowed;
		rec->scsi_id = sc->device->id;
		rec->scsi_lun = (u32)sc->device->lun;
		rec->scsi_lun_64_hi = (u32)(sc->device->lun >> 32);
		rec->host_scribble = (अचिन्हित दीर्घ)sc->host_scribble;

		स_नकल(rec->scsi_opcode, sc->cmnd,
		       min_t(पूर्णांक, sc->cmd_len, ZFCP_DBF_SCSI_OPCODE));
	पूर्ण अन्यथा अणु
		rec->scsi_result = ~0;
		rec->scsi_retries = ~0;
		rec->scsi_allowed = ~0;
		rec->scsi_id = sdev->id;
		rec->scsi_lun = (u32)sdev->lun;
		rec->scsi_lun_64_hi = (u32)(sdev->lun >> 32);
		rec->host_scribble = ~0;

		स_रखो(rec->scsi_opcode, 0xff, ZFCP_DBF_SCSI_OPCODE);
	पूर्ण

	अगर (fsf) अणु
		rec->fsf_req_id = fsf->req_id;
		rec->pl_len = FCP_RESP_WITH_EXT;
		fcp_rsp = &(fsf->qtcb->bottom.io.fcp_rsp.iu);
		/* mandatory parts of FCP_RSP IU in this SCSI record */
		स_नकल(&rec->fcp_rsp, fcp_rsp, FCP_RESP_WITH_EXT);
		अगर (fcp_rsp->resp.fr_flags & FCP_RSP_LEN_VAL) अणु
			fcp_rsp_info = (काष्ठा fcp_resp_rsp_info *) &fcp_rsp[1];
			rec->fcp_rsp_info = fcp_rsp_info->rsp_code;
			rec->pl_len += be32_to_cpu(fcp_rsp->ext.fr_rsp_len);
		पूर्ण
		अगर (fcp_rsp->resp.fr_flags & FCP_SNS_LEN_VAL) अणु
			rec->pl_len += be32_to_cpu(fcp_rsp->ext.fr_sns_len);
		पूर्ण
		/* complete FCP_RSP IU in associated PAYload record
		 * but only अगर there are optional parts
		 */
		अगर (fcp_rsp->resp.fr_flags != 0)
			zfcp_dbf_pl_ग_लिखो(
				dbf, fcp_rsp,
				/* at least one full PAY record
				 * but not beyond hardware response field
				 */
				min_t(u16, max_t(u16, rec->pl_len,
						 ZFCP_DBF_PAY_MAX_REC),
				      FSF_FCP_RSP_SIZE),
				"fcp_riu", fsf->req_id);
	पूर्ण

	debug_event(dbf->scsi, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->scsi_lock, flags);
पूर्ण

/**
 * zfcp_dbf_scsi_eh() - Trace event क्रम special हालs of scsi_eh callbacks.
 * @tag: Identअगरier क्रम event.
 * @adapter: Poपूर्णांकer to zfcp adapter as context क्रम this event.
 * @scsi_id: SCSI ID/target to indicate scope of task management function (TMF).
 * @ret: Return value of calling function.
 *
 * This SCSI trace variant करोes not depend on any of:
 * scsi_cmnd, zfcp_fsf_req, scsi_device.
 */
व्योम zfcp_dbf_scsi_eh(अक्षर *tag, काष्ठा zfcp_adapter *adapter,
		      अचिन्हित पूर्णांक scsi_id, पूर्णांक ret)
अणु
	काष्ठा zfcp_dbf *dbf = adapter->dbf;
	काष्ठा zfcp_dbf_scsi *rec = &dbf->scsi_buf;
	अचिन्हित दीर्घ flags;
	अटल पूर्णांक स्थिर level = 1;

	अगर (unlikely(!debug_level_enabled(adapter->dbf->scsi, level)))
		वापस;

	spin_lock_irqsave(&dbf->scsi_lock, flags);
	स_रखो(rec, 0, माप(*rec));

	स_नकल(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_SCSI_CMND;
	rec->scsi_result = ret; /* re-use field, पूर्णांक is 4 bytes and fits */
	rec->scsi_retries = ~0;
	rec->scsi_allowed = ~0;
	rec->fcp_rsp_info = ~0;
	rec->scsi_id = scsi_id;
	rec->scsi_lun = (u32)ZFCP_DBF_INVALID_LUN;
	rec->scsi_lun_64_hi = (u32)(ZFCP_DBF_INVALID_LUN >> 32);
	rec->host_scribble = ~0;
	स_रखो(rec->scsi_opcode, 0xff, ZFCP_DBF_SCSI_OPCODE);

	debug_event(dbf->scsi, level, rec, माप(*rec));
	spin_unlock_irqrestore(&dbf->scsi_lock, flags);
पूर्ण

अटल debug_info_t *zfcp_dbf_reg(स्थिर अक्षर *name, पूर्णांक size, पूर्णांक rec_size)
अणु
	काष्ठा debug_info *d;

	d = debug_रेजिस्टर(name, size, 1, rec_size);
	अगर (!d)
		वापस शून्य;

	debug_रेजिस्टर_view(d, &debug_hex_ascii_view);
	debug_set_level(d, dbflevel);

	वापस d;
पूर्ण

अटल व्योम zfcp_dbf_unरेजिस्टर(काष्ठा zfcp_dbf *dbf)
अणु
	अगर (!dbf)
		वापस;

	debug_unरेजिस्टर(dbf->scsi);
	debug_unरेजिस्टर(dbf->san);
	debug_unरेजिस्टर(dbf->hba);
	debug_unरेजिस्टर(dbf->pay);
	debug_unरेजिस्टर(dbf->rec);
	kमुक्त(dbf);
पूर्ण

/**
 * zfcp_adapter_debug_रेजिस्टर - रेजिस्टरs debug feature क्रम an adapter
 * @adapter: poपूर्णांकer to adapter क्रम which debug features should be रेजिस्टरed
 * वापस: -ENOMEM on error, 0 otherwise
 */
पूर्णांक zfcp_dbf_adapter_रेजिस्टर(काष्ठा zfcp_adapter *adapter)
अणु
	अक्षर name[DEBUG_MAX_NAME_LEN];
	काष्ठा zfcp_dbf *dbf;

	dbf = kzalloc(माप(काष्ठा zfcp_dbf), GFP_KERNEL);
	अगर (!dbf)
		वापस -ENOMEM;

	spin_lock_init(&dbf->pay_lock);
	spin_lock_init(&dbf->hba_lock);
	spin_lock_init(&dbf->san_lock);
	spin_lock_init(&dbf->scsi_lock);
	spin_lock_init(&dbf->rec_lock);

	/* debug feature area which records recovery activity */
	प्र_लिखो(name, "zfcp_%s_rec", dev_name(&adapter->ccw_device->dev));
	dbf->rec = zfcp_dbf_reg(name, dbfsize, माप(काष्ठा zfcp_dbf_rec));
	अगर (!dbf->rec)
		जाओ err_out;

	/* debug feature area which records HBA (FSF and QDIO) conditions */
	प्र_लिखो(name, "zfcp_%s_hba", dev_name(&adapter->ccw_device->dev));
	dbf->hba = zfcp_dbf_reg(name, dbfsize, माप(काष्ठा zfcp_dbf_hba));
	अगर (!dbf->hba)
		जाओ err_out;

	/* debug feature area which records payload info */
	प्र_लिखो(name, "zfcp_%s_pay", dev_name(&adapter->ccw_device->dev));
	dbf->pay = zfcp_dbf_reg(name, dbfsize * 2, माप(काष्ठा zfcp_dbf_pay));
	अगर (!dbf->pay)
		जाओ err_out;

	/* debug feature area which records SAN command failures and recovery */
	प्र_लिखो(name, "zfcp_%s_san", dev_name(&adapter->ccw_device->dev));
	dbf->san = zfcp_dbf_reg(name, dbfsize, माप(काष्ठा zfcp_dbf_san));
	अगर (!dbf->san)
		जाओ err_out;

	/* debug feature area which records SCSI command failures and recovery */
	प्र_लिखो(name, "zfcp_%s_scsi", dev_name(&adapter->ccw_device->dev));
	dbf->scsi = zfcp_dbf_reg(name, dbfsize, माप(काष्ठा zfcp_dbf_scsi));
	अगर (!dbf->scsi)
		जाओ err_out;

	adapter->dbf = dbf;

	वापस 0;
err_out:
	zfcp_dbf_unरेजिस्टर(dbf);
	वापस -ENOMEM;
पूर्ण

/**
 * zfcp_adapter_debug_unरेजिस्टर - unरेजिस्टरs debug feature क्रम an adapter
 * @adapter: poपूर्णांकer to adapter क्रम which debug features should be unरेजिस्टरed
 */
व्योम zfcp_dbf_adapter_unरेजिस्टर(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा zfcp_dbf *dbf = adapter->dbf;

	adapter->dbf = शून्य;
	zfcp_dbf_unरेजिस्टर(dbf);
पूर्ण

