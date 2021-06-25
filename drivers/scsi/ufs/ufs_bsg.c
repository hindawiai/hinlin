<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bsg endpoपूर्णांक that supports UPIUs
 *
 * Copyright (C) 2018 Western Digital Corporation
 */
#समावेश "ufs_bsg.h"

अटल पूर्णांक ufs_bsg_get_query_desc_size(काष्ठा ufs_hba *hba, पूर्णांक *desc_len,
				       काष्ठा utp_upiu_query *qr)
अणु
	पूर्णांक desc_size = be16_to_cpu(qr->length);
	पूर्णांक desc_id = qr->idn;

	अगर (desc_size <= 0)
		वापस -EINVAL;

	ufshcd_map_desc_id_to_length(hba, desc_id, desc_len);
	अगर (!*desc_len)
		वापस -EINVAL;

	*desc_len = min_t(पूर्णांक, *desc_len, desc_size);

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_bsg_verअगरy_query_size(काष्ठा ufs_hba *hba,
				     अचिन्हित पूर्णांक request_len,
				     अचिन्हित पूर्णांक reply_len)
अणु
	पूर्णांक min_req_len = माप(काष्ठा ufs_bsg_request);
	पूर्णांक min_rsp_len = माप(काष्ठा ufs_bsg_reply);

	अगर (min_req_len > request_len || min_rsp_len > reply_len) अणु
		dev_err(hba->dev, "not enough space assigned\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_bsg_alloc_desc_buffer(काष्ठा ufs_hba *hba, काष्ठा bsg_job *job,
				     uपूर्णांक8_t **desc_buff, पूर्णांक *desc_len,
				     क्रमागत query_opcode desc_op)
अणु
	काष्ठा ufs_bsg_request *bsg_request = job->request;
	काष्ठा utp_upiu_query *qr;
	u8 *descp;

	अगर (desc_op != UPIU_QUERY_OPCODE_WRITE_DESC &&
	    desc_op != UPIU_QUERY_OPCODE_READ_DESC)
		जाओ out;

	qr = &bsg_request->upiu_req.qr;
	अगर (ufs_bsg_get_query_desc_size(hba, desc_len, qr)) अणु
		dev_err(hba->dev, "Illegal desc size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (*desc_len > job->request_payload.payload_len) अणु
		dev_err(hba->dev, "Illegal desc size\n");
		वापस -EINVAL;
	पूर्ण

	descp = kzalloc(*desc_len, GFP_KERNEL);
	अगर (!descp)
		वापस -ENOMEM;

	अगर (desc_op == UPIU_QUERY_OPCODE_WRITE_DESC)
		sg_copy_to_buffer(job->request_payload.sg_list,
				  job->request_payload.sg_cnt, descp,
				  *desc_len);

	*desc_buff = descp;

out:
	वापस 0;
पूर्ण

अटल पूर्णांक ufs_bsg_request(काष्ठा bsg_job *job)
अणु
	काष्ठा ufs_bsg_request *bsg_request = job->request;
	काष्ठा ufs_bsg_reply *bsg_reply = job->reply;
	काष्ठा ufs_hba *hba = shost_priv(dev_to_shost(job->dev->parent));
	अचिन्हित पूर्णांक req_len = job->request_len;
	अचिन्हित पूर्णांक reply_len = job->reply_len;
	काष्ठा uic_command uc = अणुपूर्ण;
	पूर्णांक msgcode;
	uपूर्णांक8_t *desc_buff = शून्य;
	पूर्णांक desc_len = 0;
	क्रमागत query_opcode desc_op = UPIU_QUERY_OPCODE_NOP;
	पूर्णांक ret;

	ret = ufs_bsg_verअगरy_query_size(hba, req_len, reply_len);
	अगर (ret)
		जाओ out;

	bsg_reply->reply_payload_rcv_len = 0;

	pm_runसमय_get_sync(hba->dev);

	msgcode = bsg_request->msgcode;
	चयन (msgcode) अणु
	हाल UPIU_TRANSACTION_QUERY_REQ:
		desc_op = bsg_request->upiu_req.qr.opcode;
		ret = ufs_bsg_alloc_desc_buffer(hba, job, &desc_buff,
						&desc_len, desc_op);
		अगर (ret) अणु
			pm_runसमय_put_sync(hba->dev);
			जाओ out;
		पूर्ण

		fallthrough;
	हाल UPIU_TRANSACTION_NOP_OUT:
	हाल UPIU_TRANSACTION_TASK_REQ:
		ret = ufshcd_exec_raw_upiu_cmd(hba, &bsg_request->upiu_req,
					       &bsg_reply->upiu_rsp, msgcode,
					       desc_buff, &desc_len, desc_op);
		अगर (ret)
			dev_err(hba->dev,
				"exe raw upiu: error code %d\n", ret);

		अवरोध;
	हाल UPIU_TRANSACTION_UIC_CMD:
		स_नकल(&uc, &bsg_request->upiu_req.uc, UIC_CMD_SIZE);
		ret = ufshcd_send_uic_cmd(hba, &uc);
		अगर (ret)
			dev_err(hba->dev,
				"send uic cmd: error code %d\n", ret);

		स_नकल(&bsg_reply->upiu_rsp.uc, &uc, UIC_CMD_SIZE);

		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		dev_err(hba->dev, "unsupported msgcode 0x%x\n", msgcode);

		अवरोध;
	पूर्ण

	pm_runसमय_put_sync(hba->dev);

	अगर (!desc_buff)
		जाओ out;

	अगर (desc_op == UPIU_QUERY_OPCODE_READ_DESC && desc_len)
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(job->request_payload.sg_list,
					    job->request_payload.sg_cnt,
					    desc_buff, desc_len);

	kमुक्त(desc_buff);

out:
	bsg_reply->result = ret;
	job->reply_len = माप(काष्ठा ufs_bsg_reply);
	/* complete the job here only अगर no error */
	अगर (ret == 0)
		bsg_job_करोne(job, ret, bsg_reply->reply_payload_rcv_len);

	वापस ret;
पूर्ण

/**
 * ufs_bsg_हटाओ - detach and हटाओ the added ufs-bsg node
 * @hba: per adapter object
 *
 * Should be called when unloading the driver.
 */
व्योम ufs_bsg_हटाओ(काष्ठा ufs_hba *hba)
अणु
	काष्ठा device *bsg_dev = &hba->bsg_dev;

	अगर (!hba->bsg_queue)
		वापस;

	bsg_हटाओ_queue(hba->bsg_queue);

	device_del(bsg_dev);
	put_device(bsg_dev);
पूर्ण

अटल अंतरभूत व्योम ufs_bsg_node_release(काष्ठा device *dev)
अणु
	put_device(dev->parent);
पूर्ण

/**
 * ufs_bsg_probe - Add ufs bsg device node
 * @hba: per adapter object
 *
 * Called during initial loading of the driver, and beक्रमe scsi_scan_host.
 */
पूर्णांक ufs_bsg_probe(काष्ठा ufs_hba *hba)
अणु
	काष्ठा device *bsg_dev = &hba->bsg_dev;
	काष्ठा Scsi_Host *shost = hba->host;
	काष्ठा device *parent = &shost->shost_gendev;
	काष्ठा request_queue *q;
	पूर्णांक ret;

	device_initialize(bsg_dev);

	bsg_dev->parent = get_device(parent);
	bsg_dev->release = ufs_bsg_node_release;

	dev_set_name(bsg_dev, "ufs-bsg%u", shost->host_no);

	ret = device_add(bsg_dev);
	अगर (ret)
		जाओ out;

	q = bsg_setup_queue(bsg_dev, dev_name(bsg_dev), ufs_bsg_request, शून्य, 0);
	अगर (IS_ERR(q)) अणु
		ret = PTR_ERR(q);
		जाओ out;
	पूर्ण

	hba->bsg_queue = q;

	वापस 0;

out:
	dev_err(bsg_dev, "fail to initialize a bsg dev %d\n", shost->host_no);
	put_device(bsg_dev);
	वापस ret;
पूर्ण
