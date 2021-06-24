<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c) 2011-2013 QLogic Corporation
 */

#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_bsg.h"

अटल पूर्णांक
qla4xxx_पढ़ो_flash(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t length = 0;
	dma_addr_t flash_dma;
	uपूर्णांक8_t *flash = शून्य;
	पूर्णांक rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ leave;

	अगर (ql4xxx_reset_active(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	अगर (ha->flash_state != QLFLASH_WAITING) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: another flash operation "
			   "active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	ha->flash_state = QLFLASH_READING;
	offset = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	length = bsg_job->reply_payload.payload_len;

	flash = dma_alloc_coherent(&ha->pdev->dev, length, &flash_dma,
				   GFP_KERNEL);
	अगर (!flash) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: dma alloc failed for flash "
			   "data\n", __func__);
		rval = -ENOMEM;
		जाओ leave;
	पूर्ण

	rval = qla4xxx_get_flash(ha, flash_dma, offset, length);
	अगर (rval) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: get flash failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	पूर्ण अन्यथा अणु
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
					    bsg_job->reply_payload.sg_cnt,
					    flash, length);
		bsg_reply->result = DID_OK << 16;
	पूर्ण

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
	dma_मुक्त_coherent(&ha->pdev->dev, length, flash, flash_dma);
leave:
	ha->flash_state = QLFLASH_WAITING;
	वापस rval;
पूर्ण

अटल पूर्णांक
qla4xxx_update_flash(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	uपूर्णांक32_t length = 0;
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t options = 0;
	dma_addr_t flash_dma;
	uपूर्णांक8_t *flash = शून्य;
	पूर्णांक rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ leave;

	अगर (ql4xxx_reset_active(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	अगर (ha->flash_state != QLFLASH_WAITING) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: another flash operation "
			   "active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	ha->flash_state = QLFLASH_WRITING;
	length = bsg_job->request_payload.payload_len;
	offset = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	options = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[2];

	flash = dma_alloc_coherent(&ha->pdev->dev, length, &flash_dma,
				   GFP_KERNEL);
	अगर (!flash) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: dma alloc failed for flash "
			   "data\n", __func__);
		rval = -ENOMEM;
		जाओ leave;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
			  bsg_job->request_payload.sg_cnt, flash, length);

	rval = qla4xxx_set_flash(ha, flash_dma, offset, length, options);
	अगर (rval) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: set flash failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	पूर्ण अन्यथा
		bsg_reply->result = DID_OK << 16;

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
	dma_मुक्त_coherent(&ha->pdev->dev, length, flash, flash_dma);
leave:
	ha->flash_state = QLFLASH_WAITING;
	वापस rval;
पूर्ण

अटल पूर्णांक
qla4xxx_get_acb_state(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uपूर्णांक32_t status[MBOX_REG_COUNT];
	uपूर्णांक32_t acb_idx;
	uपूर्णांक32_t ip_idx;
	पूर्णांक rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ leave;

	/* Only 4022 and above adapters are supported */
	अगर (is_qla4010(ha))
		जाओ leave;

	अगर (ql4xxx_reset_active(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	अगर (bsg_job->reply_payload.payload_len < माप(status)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: invalid payload len %d\n",
			   __func__, bsg_job->reply_payload.payload_len);
		rval = -EINVAL;
		जाओ leave;
	पूर्ण

	acb_idx = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	ip_idx = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[2];

	rval = qla4xxx_get_ip_state(ha, acb_idx, ip_idx, status);
	अगर (rval) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: get ip state failed\n",
			   __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	पूर्ण अन्यथा अणु
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
					    bsg_job->reply_payload.sg_cnt,
					    status, माप(status));
		bsg_reply->result = DID_OK << 16;
	पूर्ण

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
leave:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla4xxx_पढ़ो_nvram(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t len = 0;
	uपूर्णांक32_t total_len = 0;
	dma_addr_t nvram_dma;
	uपूर्णांक8_t *nvram = शून्य;
	पूर्णांक rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ leave;

	/* Only 40xx adapters are supported */
	अगर (!(is_qla4010(ha) || is_qla4022(ha) || is_qla4032(ha)))
		जाओ leave;

	अगर (ql4xxx_reset_active(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	offset = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	len = bsg_job->reply_payload.payload_len;
	total_len = offset + len;

	/* total len should not be greater than max NVRAM size */
	अगर ((is_qla4010(ha) && total_len > QL4010_NVRAM_SIZE) ||
	    ((is_qla4022(ha) || is_qla4032(ha)) &&
	     total_len > QL40X2_NVRAM_SIZE)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: offset+len greater than max"
			   " nvram size, offset=%d len=%d\n",
			   __func__, offset, len);
		जाओ leave;
	पूर्ण

	nvram = dma_alloc_coherent(&ha->pdev->dev, len, &nvram_dma,
				   GFP_KERNEL);
	अगर (!nvram) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: dma alloc failed for nvram "
			   "data\n", __func__);
		rval = -ENOMEM;
		जाओ leave;
	पूर्ण

	rval = qla4xxx_get_nvram(ha, nvram_dma, offset, len);
	अगर (rval) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: get nvram failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	पूर्ण अन्यथा अणु
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
					    bsg_job->reply_payload.sg_cnt,
					    nvram, len);
		bsg_reply->result = DID_OK << 16;
	पूर्ण

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
	dma_मुक्त_coherent(&ha->pdev->dev, len, nvram, nvram_dma);
leave:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla4xxx_update_nvram(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t len = 0;
	uपूर्णांक32_t total_len = 0;
	dma_addr_t nvram_dma;
	uपूर्णांक8_t *nvram = शून्य;
	पूर्णांक rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ leave;

	अगर (!(is_qla4010(ha) || is_qla4022(ha) || is_qla4032(ha)))
		जाओ leave;

	अगर (ql4xxx_reset_active(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	offset = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	len = bsg_job->request_payload.payload_len;
	total_len = offset + len;

	/* total len should not be greater than max NVRAM size */
	अगर ((is_qla4010(ha) && total_len > QL4010_NVRAM_SIZE) ||
	    ((is_qla4022(ha) || is_qla4032(ha)) &&
	     total_len > QL40X2_NVRAM_SIZE)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: offset+len greater than max"
			   " nvram size, offset=%d len=%d\n",
			   __func__, offset, len);
		जाओ leave;
	पूर्ण

	nvram = dma_alloc_coherent(&ha->pdev->dev, len, &nvram_dma,
				   GFP_KERNEL);
	अगर (!nvram) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: dma alloc failed for flash "
			   "data\n", __func__);
		rval = -ENOMEM;
		जाओ leave;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
			  bsg_job->request_payload.sg_cnt, nvram, len);

	rval = qla4xxx_set_nvram(ha, nvram_dma, offset, len);
	अगर (rval) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: set nvram failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	पूर्ण अन्यथा
		bsg_reply->result = DID_OK << 16;

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
	dma_मुक्त_coherent(&ha->pdev->dev, len, nvram, nvram_dma);
leave:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla4xxx_restore_शेषs(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uपूर्णांक32_t region = 0;
	uपूर्णांक32_t field0 = 0;
	uपूर्णांक32_t field1 = 0;
	पूर्णांक rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ leave;

	अगर (is_qla4010(ha))
		जाओ leave;

	अगर (ql4xxx_reset_active(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	region = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	field0 = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[2];
	field1 = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[3];

	rval = qla4xxx_restore_factory_शेषs(ha, region, field0, field1);
	अगर (rval) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: set nvram failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	पूर्ण अन्यथा
		bsg_reply->result = DID_OK << 16;

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
leave:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla4xxx_bsg_get_acb(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uपूर्णांक32_t acb_type = 0;
	uपूर्णांक32_t len = 0;
	dma_addr_t acb_dma;
	uपूर्णांक8_t *acb = शून्य;
	पूर्णांक rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ leave;

	/* Only 4022 and above adapters are supported */
	अगर (is_qla4010(ha))
		जाओ leave;

	अगर (ql4xxx_reset_active(ha)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		जाओ leave;
	पूर्ण

	acb_type = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	len = bsg_job->reply_payload.payload_len;
	अगर (len < माप(काष्ठा addr_ctrl_blk)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: invalid acb len %d\n",
			   __func__, len);
		rval = -EINVAL;
		जाओ leave;
	पूर्ण

	acb = dma_alloc_coherent(&ha->pdev->dev, len, &acb_dma, GFP_KERNEL);
	अगर (!acb) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: dma alloc failed for acb "
			   "data\n", __func__);
		rval = -ENOMEM;
		जाओ leave;
	पूर्ण

	rval = qla4xxx_get_acb(ha, acb_dma, acb_type, len);
	अगर (rval) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: get acb failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	पूर्ण अन्यथा अणु
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
					    bsg_job->reply_payload.sg_cnt,
					    acb, len);
		bsg_reply->result = DID_OK << 16;
	पूर्ण

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
	dma_मुक्त_coherent(&ha->pdev->dev, len, acb, acb_dma);
leave:
	वापस rval;
पूर्ण

अटल व्योम ql4xxx_execute_diag_cmd(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uपूर्णांक8_t *rsp_ptr = शून्य;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_ERROR;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: in\n", __func__));

	अगर (test_bit(DPC_RESET_HA, &ha->dpc_flags)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Adapter reset in progress. Invalid Request\n",
			   __func__);
		bsg_reply->result = DID_ERROR << 16;
		जाओ निकास_diag_mem_test;
	पूर्ण

	bsg_reply->reply_payload_rcv_len = 0;
	स_नकल(mbox_cmd, &bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1],
	       माप(uपूर्णांक32_t) * MBOX_REG_COUNT);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: mbox_cmd: %08X %08X %08X %08X %08X %08X %08X %08X\n",
			  __func__, mbox_cmd[0], mbox_cmd[1], mbox_cmd[2],
			  mbox_cmd[3], mbox_cmd[4], mbox_cmd[5], mbox_cmd[6],
			  mbox_cmd[7]));

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 8, &mbox_cmd[0],
					 &mbox_sts[0]);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: mbox_sts: %08X %08X %08X %08X %08X %08X %08X %08X\n",
			  __func__, mbox_sts[0], mbox_sts[1], mbox_sts[2],
			  mbox_sts[3], mbox_sts[4], mbox_sts[5], mbox_sts[6],
			  mbox_sts[7]));

	अगर (status == QLA_SUCCESS)
		bsg_reply->result = DID_OK << 16;
	अन्यथा
		bsg_reply->result = DID_ERROR << 16;

	/* Send mbox_sts to application */
	bsg_job->reply_len = माप(काष्ठा iscsi_bsg_reply) + माप(mbox_sts);
	rsp_ptr = ((uपूर्णांक8_t *)bsg_reply) + माप(काष्ठा iscsi_bsg_reply);
	स_नकल(rsp_ptr, mbox_sts, माप(mbox_sts));

निकास_diag_mem_test:
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: bsg_reply->result = x%x, status = %s\n",
			  __func__, bsg_reply->result, STATUS(status)));

	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
पूर्ण

अटल पूर्णांक qla4_83xx_रुको_क्रम_loopback_config_comp(काष्ठा scsi_qla_host *ha,
						   पूर्णांक रुको_क्रम_link)
अणु
	पूर्णांक status = QLA_SUCCESS;

	अगर (!रुको_क्रम_completion_समयout(&ha->idc_comp, (IDC_COMP_TOV * HZ))) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IDC Complete notification not received, Waiting for another %d timeout",
			   __func__, ha->idc_extend_पंचांगo);
		अगर (ha->idc_extend_पंचांगo) अणु
			अगर (!रुको_क्रम_completion_समयout(&ha->idc_comp,
						(ha->idc_extend_पंचांगo * HZ))) अणु
				ha->notअगरy_idc_comp = 0;
				ha->notअगरy_link_up_comp = 0;
				ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: Aborting: IDC Complete notification not received",
					   __func__);
				status = QLA_ERROR;
				जाओ निकास_रुको;
			पूर्ण अन्यथा अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "%s: IDC Complete notification received\n",
						  __func__));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: IDC Complete notification received\n",
				  __func__));
	पूर्ण
	ha->notअगरy_idc_comp = 0;

	अगर (रुको_क्रम_link) अणु
		अगर (!रुको_क्रम_completion_समयout(&ha->link_up_comp,
						 (IDC_COMP_TOV * HZ))) अणु
			ha->notअगरy_link_up_comp = 0;
			ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: Aborting: LINK UP notification not received",
				   __func__);
			status = QLA_ERROR;
			जाओ निकास_रुको;
		पूर्ण अन्यथा अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "%s: LINK UP notification received\n",
					  __func__));
		पूर्ण
		ha->notअगरy_link_up_comp = 0;
	पूर्ण

निकास_रुको:
	वापस status;
पूर्ण

अटल पूर्णांक qla4_83xx_pre_loopback_config(काष्ठा scsi_qla_host *ha,
					 uपूर्णांक32_t *mbox_cmd)
अणु
	uपूर्णांक32_t config = 0;
	पूर्णांक status = QLA_SUCCESS;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: in\n", __func__));

	status = qla4_83xx_get_port_config(ha, &config);
	अगर (status != QLA_SUCCESS)
		जाओ निकास_pre_loopback_config;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Default port config=%08X\n",
			  __func__, config));

	अगर ((config & ENABLE_INTERNAL_LOOPBACK) ||
	    (config & ENABLE_EXTERNAL_LOOPBACK)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Loopback diagnostics already in progress. Invalid request\n",
			   __func__);
		जाओ निकास_pre_loopback_config;
	पूर्ण

	अगर (mbox_cmd[1] == QL_DIAG_CMD_TEST_INT_LOOPBACK)
		config |= ENABLE_INTERNAL_LOOPBACK;

	अगर (mbox_cmd[1] == QL_DIAG_CMD_TEST_EXT_LOOPBACK)
		config |= ENABLE_EXTERNAL_LOOPBACK;

	config &= ~ENABLE_DCBX;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: New port config=%08X\n",
			  __func__, config));

	ha->notअगरy_idc_comp = 1;
	ha->notअगरy_link_up_comp = 1;

	/* get the link state */
	qla4xxx_get_firmware_state(ha);

	status = qla4_83xx_set_port_config(ha, &config);
	अगर (status != QLA_SUCCESS) अणु
		ha->notअगरy_idc_comp = 0;
		ha->notअगरy_link_up_comp = 0;
		जाओ निकास_pre_loopback_config;
	पूर्ण
निकास_pre_loopback_config:
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: status = %s\n", __func__,
			  STATUS(status)));
	वापस status;
पूर्ण

अटल पूर्णांक qla4_83xx_post_loopback_config(काष्ठा scsi_qla_host *ha,
					  uपूर्णांक32_t *mbox_cmd)
अणु
	पूर्णांक status = QLA_SUCCESS;
	uपूर्णांक32_t config = 0;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: in\n", __func__));

	status = qla4_83xx_get_port_config(ha, &config);
	अगर (status != QLA_SUCCESS)
		जाओ निकास_post_loopback_config;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: port config=%08X\n", __func__,
			  config));

	अगर (mbox_cmd[1] == QL_DIAG_CMD_TEST_INT_LOOPBACK)
		config &= ~ENABLE_INTERNAL_LOOPBACK;
	अन्यथा अगर (mbox_cmd[1] == QL_DIAG_CMD_TEST_EXT_LOOPBACK)
		config &= ~ENABLE_EXTERNAL_LOOPBACK;

	config |= ENABLE_DCBX;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: Restore default port config=%08X\n", __func__,
			  config));

	ha->notअगरy_idc_comp = 1;
	अगर (ha->addl_fw_state & FW_ADDSTATE_LINK_UP)
		ha->notअगरy_link_up_comp = 1;

	status = qla4_83xx_set_port_config(ha, &config);
	अगर (status != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Scheduling adapter reset\n",
			   __func__);
		set_bit(DPC_RESET_HA, &ha->dpc_flags);
		clear_bit(AF_LOOPBACK, &ha->flags);
		जाओ निकास_post_loopback_config;
	पूर्ण

निकास_post_loopback_config:
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: status = %s\n", __func__,
			  STATUS(status)));
	वापस status;
पूर्ण

अटल व्योम qla4xxx_execute_diag_loopback_cmd(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uपूर्णांक8_t *rsp_ptr = शून्य;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक रुको_क्रम_link = 1;
	पूर्णांक status = QLA_ERROR;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: in\n", __func__));

	bsg_reply->reply_payload_rcv_len = 0;

	अगर (test_bit(AF_LOOPBACK, &ha->flags)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Loopback Diagnostics already in progress. Invalid Request\n",
			   __func__);
		bsg_reply->result = DID_ERROR << 16;
		जाओ निकास_loopback_cmd;
	पूर्ण

	अगर (test_bit(DPC_RESET_HA, &ha->dpc_flags)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Adapter reset in progress. Invalid Request\n",
			   __func__);
		bsg_reply->result = DID_ERROR << 16;
		जाओ निकास_loopback_cmd;
	पूर्ण

	स_नकल(mbox_cmd, &bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1],
	       माप(uपूर्णांक32_t) * MBOX_REG_COUNT);

	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		status = qla4_83xx_pre_loopback_config(ha, mbox_cmd);
		अगर (status != QLA_SUCCESS) अणु
			bsg_reply->result = DID_ERROR << 16;
			जाओ निकास_loopback_cmd;
		पूर्ण

		status = qla4_83xx_रुको_क्रम_loopback_config_comp(ha,
								 रुको_क्रम_link);
		अगर (status != QLA_SUCCESS) अणु
			bsg_reply->result = DID_TIME_OUT << 16;
			जाओ restore;
		पूर्ण
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: mbox_cmd: %08X %08X %08X %08X %08X %08X %08X %08X\n",
			  __func__, mbox_cmd[0], mbox_cmd[1], mbox_cmd[2],
			  mbox_cmd[3], mbox_cmd[4], mbox_cmd[5], mbox_cmd[6],
			  mbox_cmd[7]));

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 8, &mbox_cmd[0],
				&mbox_sts[0]);

	अगर (status == QLA_SUCCESS)
		bsg_reply->result = DID_OK << 16;
	अन्यथा
		bsg_reply->result = DID_ERROR << 16;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: mbox_sts: %08X %08X %08X %08X %08X %08X %08X %08X\n",
			  __func__, mbox_sts[0], mbox_sts[1], mbox_sts[2],
			  mbox_sts[3], mbox_sts[4], mbox_sts[5], mbox_sts[6],
			  mbox_sts[7]));

	/* Send mbox_sts to application */
	bsg_job->reply_len = माप(काष्ठा iscsi_bsg_reply) + माप(mbox_sts);
	rsp_ptr = ((uपूर्णांक8_t *)bsg_reply) + माप(काष्ठा iscsi_bsg_reply);
	स_नकल(rsp_ptr, mbox_sts, माप(mbox_sts));
restore:
	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		status = qla4_83xx_post_loopback_config(ha, mbox_cmd);
		अगर (status != QLA_SUCCESS) अणु
			bsg_reply->result = DID_ERROR << 16;
			जाओ निकास_loopback_cmd;
		पूर्ण

		/* क्रम pre_loopback_config() रुको क्रम LINK UP only
		 * अगर PHY LINK is UP */
		अगर (!(ha->addl_fw_state & FW_ADDSTATE_LINK_UP))
			रुको_क्रम_link = 0;

		status = qla4_83xx_रुको_क्रम_loopback_config_comp(ha,
								 रुको_क्रम_link);
		अगर (status != QLA_SUCCESS) अणु
			bsg_reply->result = DID_TIME_OUT << 16;
			जाओ निकास_loopback_cmd;
		पूर्ण
	पूर्ण
निकास_loopback_cmd:
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: bsg_reply->result = x%x, status = %s\n",
			  __func__, bsg_reply->result, STATUS(status)));
	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
पूर्ण

अटल पूर्णांक qla4xxx_execute_diag_test(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	uपूर्णांक32_t diag_cmd;
	पूर्णांक rval = -EINVAL;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: in\n", __func__));

	diag_cmd = bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[1];
	अगर (diag_cmd == MBOX_CMD_DIAG_TEST) अणु
		चयन (bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[2]) अणु
		हाल QL_DIAG_CMD_TEST_DDR_SIZE:
		हाल QL_DIAG_CMD_TEST_DDR_RW:
		हाल QL_DIAG_CMD_TEST_ONCHIP_MEM_RW:
		हाल QL_DIAG_CMD_TEST_NVRAM:
		हाल QL_DIAG_CMD_TEST_FLASH_ROM:
		हाल QL_DIAG_CMD_TEST_DMA_XFER:
		हाल QL_DIAG_CMD_SELF_DDR_RW:
		हाल QL_DIAG_CMD_SELF_ONCHIP_MEM_RW:
			/* Execute diag test क्रम adapter RAM/FLASH */
			ql4xxx_execute_diag_cmd(bsg_job);
			/* Always वापस success as we want to sent bsg_reply
			 * to Application */
			rval = QLA_SUCCESS;
			अवरोध;

		हाल QL_DIAG_CMD_TEST_INT_LOOPBACK:
		हाल QL_DIAG_CMD_TEST_EXT_LOOPBACK:
			/* Execute diag test क्रम Network */
			qla4xxx_execute_diag_loopback_cmd(bsg_job);
			/* Always वापस success as we want to sent bsg_reply
			 * to Application */
			rval = QLA_SUCCESS;
			अवरोध;
		शेष:
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Invalid diag test: 0x%x\n",
				   __func__,
				   bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[2]);
		पूर्ण
	पूर्ण अन्यथा अगर ((diag_cmd == MBOX_CMD_SET_LED_CONFIG) ||
		   (diag_cmd == MBOX_CMD_GET_LED_CONFIG)) अणु
		ql4xxx_execute_diag_cmd(bsg_job);
		rval = QLA_SUCCESS;
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Invalid diag cmd: 0x%x\n",
			   __func__, diag_cmd);
	पूर्ण

	वापस rval;
पूर्ण

/**
 * qla4xxx_process_venकरोr_specअगरic - handle venकरोr specअगरic bsg request
 * @bsg_job: iscsi_bsg_job to handle
 **/
पूर्णांक qla4xxx_process_venकरोr_specअगरic(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);

	चयन (bsg_req->rqst_data.h_venकरोr.venकरोr_cmd[0]) अणु
	हाल QLISCSI_VND_READ_FLASH:
		वापस qla4xxx_पढ़ो_flash(bsg_job);

	हाल QLISCSI_VND_UPDATE_FLASH:
		वापस qla4xxx_update_flash(bsg_job);

	हाल QLISCSI_VND_GET_ACB_STATE:
		वापस qla4xxx_get_acb_state(bsg_job);

	हाल QLISCSI_VND_READ_NVRAM:
		वापस qla4xxx_पढ़ो_nvram(bsg_job);

	हाल QLISCSI_VND_UPDATE_NVRAM:
		वापस qla4xxx_update_nvram(bsg_job);

	हाल QLISCSI_VND_RESTORE_DEFAULTS:
		वापस qla4xxx_restore_शेषs(bsg_job);

	हाल QLISCSI_VND_GET_ACB:
		वापस qla4xxx_bsg_get_acb(bsg_job);

	हाल QLISCSI_VND_DIAG_TEST:
		वापस qla4xxx_execute_diag_test(bsg_job);

	शेष:
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: invalid BSG vendor command: "
			   "0x%x\n", __func__, bsg_req->msgcode);
		bsg_reply->result = (DID_ERROR << 16);
		bsg_reply->reply_payload_rcv_len = 0;
		bsg_job_करोne(bsg_job, bsg_reply->result,
			     bsg_reply->reply_payload_rcv_len);
		वापस -ENOSYS;
	पूर्ण
पूर्ण

/**
 * qla4xxx_bsg_request - handle bsg request from ISCSI transport
 * @bsg_job: iscsi_bsg_job to handle
 */
पूर्णांक qla4xxx_bsg_request(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा iscsi_bsg_request *bsg_req = bsg_job->request;
	काष्ठा Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	काष्ठा scsi_qla_host *ha = to_qla_host(host);

	चयन (bsg_req->msgcode) अणु
	हाल ISCSI_BSG_HST_VENDOR:
		वापस qla4xxx_process_venकरोr_specअगरic(bsg_job);

	शेष:
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: invalid BSG command: 0x%x\n",
			   __func__, bsg_req->msgcode);
	पूर्ण

	वापस -ENOSYS;
पूर्ण
