<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016, Avago Technologies
 */

#अगर_अघोषित _NVME_FC_TRANSPORT_H
#घोषणा _NVME_FC_TRANSPORT_H 1


/*
 * Common definitions between the nvme_fc (host) transport and
 * nvmet_fc (target) transport implementation.
 */

/*
 * ******************  FC-NVME LS HANDLING ******************
 */

जोड़ nvmefc_ls_requests अणु
	काष्ठा fcnvme_ls_rqst_w0		w0;
	काष्ठा fcnvme_ls_cr_assoc_rqst		rq_cr_assoc;
	काष्ठा fcnvme_ls_cr_conn_rqst		rq_cr_conn;
	काष्ठा fcnvme_ls_disconnect_assoc_rqst	rq_dis_assoc;
	काष्ठा fcnvme_ls_disconnect_conn_rqst	rq_dis_conn;
पूर्ण __aligned(128);	/* alignment क्रम other things alloc'd with */

जोड़ nvmefc_ls_responses अणु
	काष्ठा fcnvme_ls_rjt			rsp_rjt;
	काष्ठा fcnvme_ls_cr_assoc_acc		rsp_cr_assoc;
	काष्ठा fcnvme_ls_cr_conn_acc		rsp_cr_conn;
	काष्ठा fcnvme_ls_disconnect_assoc_acc	rsp_dis_assoc;
	काष्ठा fcnvme_ls_disconnect_conn_acc	rsp_dis_conn;
पूर्ण __aligned(128);	/* alignment क्रम other things alloc'd with */

अटल अंतरभूत व्योम
nvme_fc_क्रमmat_rsp_hdr(व्योम *buf, u8 ls_cmd, __be32 desc_len, u8 rqst_ls_cmd)
अणु
	काष्ठा fcnvme_ls_acc_hdr *acc = buf;

	acc->w0.ls_cmd = ls_cmd;
	acc->desc_list_len = desc_len;
	acc->rqst.desc_tag = cpu_to_be32(FCNVME_LSDESC_RQST);
	acc->rqst.desc_len =
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_lsdesc_rqst));
	acc->rqst.w0.ls_cmd = rqst_ls_cmd;
पूर्ण

अटल अंतरभूत पूर्णांक
nvme_fc_क्रमmat_rjt(व्योम *buf, u16 buflen, u8 ls_cmd,
			u8 reason, u8 explanation, u8 venकरोr)
अणु
	काष्ठा fcnvme_ls_rjt *rjt = buf;

	nvme_fc_क्रमmat_rsp_hdr(buf, FCNVME_LSDESC_RQST,
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_ls_rjt)),
			ls_cmd);
	rjt->rjt.desc_tag = cpu_to_be32(FCNVME_LSDESC_RJT);
	rjt->rjt.desc_len = fcnvme_lsdesc_len(माप(काष्ठा fcnvme_lsdesc_rjt));
	rjt->rjt.reason_code = reason;
	rjt->rjt.reason_explanation = explanation;
	rjt->rjt.venकरोr = venकरोr;

	वापस माप(काष्ठा fcnvme_ls_rjt);
पूर्ण

/* Validation Error indexes पूर्णांकo the string table below */
क्रमागत अणु
	VERR_NO_ERROR		= 0,
	VERR_CR_ASSOC_LEN	= 1,
	VERR_CR_ASSOC_RQST_LEN	= 2,
	VERR_CR_ASSOC_CMD	= 3,
	VERR_CR_ASSOC_CMD_LEN	= 4,
	VERR_ERSP_RATIO		= 5,
	VERR_ASSOC_ALLOC_FAIL	= 6,
	VERR_QUEUE_ALLOC_FAIL	= 7,
	VERR_CR_CONN_LEN	= 8,
	VERR_CR_CONN_RQST_LEN	= 9,
	VERR_ASSOC_ID		= 10,
	VERR_ASSOC_ID_LEN	= 11,
	VERR_NO_ASSOC		= 12,
	VERR_CONN_ID		= 13,
	VERR_CONN_ID_LEN	= 14,
	VERR_INVAL_CONN		= 15,
	VERR_CR_CONN_CMD	= 16,
	VERR_CR_CONN_CMD_LEN	= 17,
	VERR_DISCONN_LEN	= 18,
	VERR_DISCONN_RQST_LEN	= 19,
	VERR_DISCONN_CMD	= 20,
	VERR_DISCONN_CMD_LEN	= 21,
	VERR_DISCONN_SCOPE	= 22,
	VERR_RS_LEN		= 23,
	VERR_RS_RQST_LEN	= 24,
	VERR_RS_CMD		= 25,
	VERR_RS_CMD_LEN		= 26,
	VERR_RS_RCTL		= 27,
	VERR_RS_RO		= 28,
	VERR_LSACC		= 29,
	VERR_LSDESC_RQST	= 30,
	VERR_LSDESC_RQST_LEN	= 31,
	VERR_CR_ASSOC		= 32,
	VERR_CR_ASSOC_ACC_LEN	= 33,
	VERR_CR_CONN		= 34,
	VERR_CR_CONN_ACC_LEN	= 35,
	VERR_DISCONN		= 36,
	VERR_DISCONN_ACC_LEN	= 37,
पूर्ण;

अटल अक्षर *validation_errors[] = अणु
	"OK",
	"Bad CR_ASSOC Length",
	"Bad CR_ASSOC Rqst Length",
	"Not CR_ASSOC Cmd",
	"Bad CR_ASSOC Cmd Length",
	"Bad Ersp Ratio",
	"Association Allocation Failed",
	"Queue Allocation Failed",
	"Bad CR_CONN Length",
	"Bad CR_CONN Rqst Length",
	"Not Association ID",
	"Bad Association ID Length",
	"No Association",
	"Not Connection ID",
	"Bad Connection ID Length",
	"Invalid Connection ID",
	"Not CR_CONN Cmd",
	"Bad CR_CONN Cmd Length",
	"Bad DISCONN Length",
	"Bad DISCONN Rqst Length",
	"Not DISCONN Cmd",
	"Bad DISCONN Cmd Length",
	"Bad Disconnect Scope",
	"Bad RS Length",
	"Bad RS Rqst Length",
	"Not RS Cmd",
	"Bad RS Cmd Length",
	"Bad RS R_CTL",
	"Bad RS Relative Offset",
	"Not LS_ACC",
	"Not LSDESC_RQST",
	"Bad LSDESC_RQST Length",
	"Not CR_ASSOC Rqst",
	"Bad CR_ASSOC ACC Length",
	"Not CR_CONN Rqst",
	"Bad CR_CONN ACC Length",
	"Not Disconnect Rqst",
	"Bad Disconnect ACC Length",
पूर्ण;

#घोषणा NVME_FC_LAST_LS_CMD_VALUE	FCNVME_LS_DISCONNECT_CONN

अटल अक्षर *nvmefc_ls_names[] = अणु
	"Reserved (0)",
	"RJT (1)",
	"ACC (2)",
	"Create Association",
	"Create Connection",
	"Disconnect Association",
	"Disconnect Connection",
पूर्ण;

अटल अंतरभूत व्योम
nvmefc_fmt_lsreq_discon_assoc(काष्ठा nvmefc_ls_req *lsreq,
	काष्ठा fcnvme_ls_disconnect_assoc_rqst *discon_rqst,
	काष्ठा fcnvme_ls_disconnect_assoc_acc *discon_acc,
	u64 association_id)
अणु
	lsreq->rqstaddr = discon_rqst;
	lsreq->rqstlen = माप(*discon_rqst);
	lsreq->rspaddr = discon_acc;
	lsreq->rsplen = माप(*discon_acc);
	lsreq->समयout = NVME_FC_LS_TIMEOUT_SEC;

	discon_rqst->w0.ls_cmd = FCNVME_LS_DISCONNECT_ASSOC;
	discon_rqst->desc_list_len = cpu_to_be32(
				माप(काष्ठा fcnvme_lsdesc_assoc_id) +
				माप(काष्ठा fcnvme_lsdesc_disconn_cmd));

	discon_rqst->associd.desc_tag = cpu_to_be32(FCNVME_LSDESC_ASSOC_ID);
	discon_rqst->associd.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_assoc_id));

	discon_rqst->associd.association_id = cpu_to_be64(association_id);

	discon_rqst->discon_cmd.desc_tag = cpu_to_be32(
						FCNVME_LSDESC_DISCONN_CMD);
	discon_rqst->discon_cmd.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_disconn_cmd));
पूर्ण

अटल अंतरभूत पूर्णांक
nvmefc_vldt_lsreq_discon_assoc(u32 rqstlen,
	काष्ठा fcnvme_ls_disconnect_assoc_rqst *rqst)
अणु
	पूर्णांक ret = 0;

	अगर (rqstlen < माप(काष्ठा fcnvme_ls_disconnect_assoc_rqst))
		ret = VERR_DISCONN_LEN;
	अन्यथा अगर (rqst->desc_list_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_ls_disconnect_assoc_rqst)))
		ret = VERR_DISCONN_RQST_LEN;
	अन्यथा अगर (rqst->associd.desc_tag != cpu_to_be32(FCNVME_LSDESC_ASSOC_ID))
		ret = VERR_ASSOC_ID;
	अन्यथा अगर (rqst->associd.desc_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_assoc_id)))
		ret = VERR_ASSOC_ID_LEN;
	अन्यथा अगर (rqst->discon_cmd.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_DISCONN_CMD))
		ret = VERR_DISCONN_CMD;
	अन्यथा अगर (rqst->discon_cmd.desc_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_disconn_cmd)))
		ret = VERR_DISCONN_CMD_LEN;
	/*
	 * As the standard changed on the LS, check अगर old क्रमmat and scope
	 * something other than Association (e.g. 0).
	 */
	अन्यथा अगर (rqst->discon_cmd.rsvd8[0])
		ret = VERR_DISCONN_SCOPE;

	वापस ret;
पूर्ण

#पूर्ण_अगर /* _NVME_FC_TRANSPORT_H */
