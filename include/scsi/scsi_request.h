<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_REQUEST_H
#घोषणा _SCSI_SCSI_REQUEST_H

#समावेश <linux/blk-mq.h>

#घोषणा BLK_MAX_CDB	16

काष्ठा scsi_request अणु
	अचिन्हित अक्षर	__cmd[BLK_MAX_CDB];
	अचिन्हित अक्षर	*cmd;
	अचिन्हित लघु	cmd_len;
	पूर्णांक		result;
	अचिन्हित पूर्णांक	sense_len;
	अचिन्हित पूर्णांक	resid_len;	/* residual count */
	पूर्णांक		retries;
	व्योम		*sense;
पूर्ण;

अटल अंतरभूत काष्ठा scsi_request *scsi_req(काष्ठा request *rq)
अणु
	वापस blk_mq_rq_to_pdu(rq);
पूर्ण

अटल अंतरभूत व्योम scsi_req_मुक्त_cmd(काष्ठा scsi_request *req)
अणु
	अगर (req->cmd != req->__cmd)
		kमुक्त(req->cmd);
पूर्ण

व्योम scsi_req_init(काष्ठा scsi_request *req);

#पूर्ण_अगर /* _SCSI_SCSI_REQUEST_H */
