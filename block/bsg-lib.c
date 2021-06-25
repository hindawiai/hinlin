<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  BSG helper library
 *
 *  Copyright (C) 2008   James Smart, Emulex Corporation
 *  Copyright (C) 2011   Red Hat, Inc.  All rights reserved.
 *  Copyright (C) 2011   Mike Christie
 */
#समावेश <linux/slab.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/bsg-lib.h>
#समावेश <linux/export.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/sg.h>

#घोषणा uptr64(val) ((व्योम __user *)(uपूर्णांकptr_t)(val))

काष्ठा bsg_set अणु
	काष्ठा blk_mq_tag_set	tag_set;
	bsg_job_fn		*job_fn;
	bsg_समयout_fn		*समयout_fn;
पूर्ण;

अटल पूर्णांक bsg_transport_check_proto(काष्ठा sg_io_v4 *hdr)
अणु
	अगर (hdr->protocol != BSG_PROTOCOL_SCSI  ||
	    hdr->subprotocol != BSG_SUB_PROTOCOL_SCSI_TRANSPORT)
		वापस -EINVAL;
	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;
	वापस 0;
पूर्ण

अटल पूर्णांक bsg_transport_fill_hdr(काष्ठा request *rq, काष्ठा sg_io_v4 *hdr,
		भ_शेषe_t mode)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(rq);
	पूर्णांक ret;

	job->request_len = hdr->request_len;
	job->request = memdup_user(uptr64(hdr->request), hdr->request_len);
	अगर (IS_ERR(job->request))
		वापस PTR_ERR(job->request);

	अगर (hdr->करोut_xfer_len && hdr->din_xfer_len) अणु
		job->bidi_rq = blk_get_request(rq->q, REQ_OP_SCSI_IN, 0);
		अगर (IS_ERR(job->bidi_rq)) अणु
			ret = PTR_ERR(job->bidi_rq);
			जाओ out;
		पूर्ण

		ret = blk_rq_map_user(rq->q, job->bidi_rq, शून्य,
				uptr64(hdr->din_xferp), hdr->din_xfer_len,
				GFP_KERNEL);
		अगर (ret)
			जाओ out_मुक्त_bidi_rq;

		job->bidi_bio = job->bidi_rq->bio;
	पूर्ण अन्यथा अणु
		job->bidi_rq = शून्य;
		job->bidi_bio = शून्य;
	पूर्ण

	वापस 0;

out_मुक्त_bidi_rq:
	अगर (job->bidi_rq)
		blk_put_request(job->bidi_rq);
out:
	kमुक्त(job->request);
	वापस ret;
पूर्ण

अटल पूर्णांक bsg_transport_complete_rq(काष्ठा request *rq, काष्ठा sg_io_v4 *hdr)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(rq);
	पूर्णांक ret = 0;

	/*
	 * The assignments below करोn't make much sense, but are kept क्रम
	 * bug by bug backwards compatibility:
	 */
	hdr->device_status = job->result & 0xff;
	hdr->transport_status = host_byte(job->result);
	hdr->driver_status = driver_byte(job->result);
	hdr->info = 0;
	अगर (hdr->device_status || hdr->transport_status || hdr->driver_status)
		hdr->info |= SG_INFO_CHECK;
	hdr->response_len = 0;

	अगर (job->result < 0) अणु
		/* we're only वापसing the result field in the reply */
		job->reply_len = माप(u32);
		ret = job->result;
	पूर्ण

	अगर (job->reply_len && hdr->response) अणु
		पूर्णांक len = min(hdr->max_response_len, job->reply_len);

		अगर (copy_to_user(uptr64(hdr->response), job->reply, len))
			ret = -EFAULT;
		अन्यथा
			hdr->response_len = len;
	पूर्ण

	/* we assume all request payload was transferred, residual == 0 */
	hdr->करोut_resid = 0;

	अगर (job->bidi_rq) अणु
		अचिन्हित पूर्णांक rsp_len = job->reply_payload.payload_len;

		अगर (WARN_ON(job->reply_payload_rcv_len > rsp_len))
			hdr->din_resid = 0;
		अन्यथा
			hdr->din_resid = rsp_len - job->reply_payload_rcv_len;
	पूर्ण अन्यथा अणु
		hdr->din_resid = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bsg_transport_मुक्त_rq(काष्ठा request *rq)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(rq);

	अगर (job->bidi_rq) अणु
		blk_rq_unmap_user(job->bidi_bio);
		blk_put_request(job->bidi_rq);
	पूर्ण

	kमुक्त(job->request);
पूर्ण

अटल स्थिर काष्ठा bsg_ops bsg_transport_ops = अणु
	.check_proto		= bsg_transport_check_proto,
	.fill_hdr		= bsg_transport_fill_hdr,
	.complete_rq		= bsg_transport_complete_rq,
	.मुक्त_rq		= bsg_transport_मुक्त_rq,
पूर्ण;

/**
 * bsg_tearकरोwn_job - routine to tearकरोwn a bsg job
 * @kref: kref inside bsg_job that is to be torn करोwn
 */
अटल व्योम bsg_tearकरोwn_job(काष्ठा kref *kref)
अणु
	काष्ठा bsg_job *job = container_of(kref, काष्ठा bsg_job, kref);
	काष्ठा request *rq = blk_mq_rq_from_pdu(job);

	put_device(job->dev);	/* release reference क्रम the request */

	kमुक्त(job->request_payload.sg_list);
	kमुक्त(job->reply_payload.sg_list);

	blk_mq_end_request(rq, BLK_STS_OK);
पूर्ण

व्योम bsg_job_put(काष्ठा bsg_job *job)
अणु
	kref_put(&job->kref, bsg_tearकरोwn_job);
पूर्ण
EXPORT_SYMBOL_GPL(bsg_job_put);

पूर्णांक bsg_job_get(काष्ठा bsg_job *job)
अणु
	वापस kref_get_unless_zero(&job->kref);
पूर्ण
EXPORT_SYMBOL_GPL(bsg_job_get);

/**
 * bsg_job_करोne - completion routine क्रम bsg requests
 * @job: bsg_job that is complete
 * @result: job reply result
 * @reply_payload_rcv_len: length of payload recvd
 *
 * The LLD should call this when the bsg job has completed.
 */
व्योम bsg_job_करोne(काष्ठा bsg_job *job, पूर्णांक result,
		  अचिन्हित पूर्णांक reply_payload_rcv_len)
अणु
	काष्ठा request *rq = blk_mq_rq_from_pdu(job);

	job->result = result;
	job->reply_payload_rcv_len = reply_payload_rcv_len;
	अगर (likely(!blk_should_fake_समयout(rq->q)))
		blk_mq_complete_request(rq);
पूर्ण
EXPORT_SYMBOL_GPL(bsg_job_करोne);

/**
 * bsg_complete - softirq करोne routine क्रम destroying the bsg requests
 * @rq: BSG request that holds the job to be destroyed
 */
अटल व्योम bsg_complete(काष्ठा request *rq)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(rq);

	bsg_job_put(job);
पूर्ण

अटल पूर्णांक bsg_map_buffer(काष्ठा bsg_buffer *buf, काष्ठा request *req)
अणु
	माप_प्रकार sz = (माप(काष्ठा scatterlist) * req->nr_phys_segments);

	BUG_ON(!req->nr_phys_segments);

	buf->sg_list = kदो_स्मृति(sz, GFP_KERNEL);
	अगर (!buf->sg_list)
		वापस -ENOMEM;
	sg_init_table(buf->sg_list, req->nr_phys_segments);
	buf->sg_cnt = blk_rq_map_sg(req->q, req, buf->sg_list);
	buf->payload_len = blk_rq_bytes(req);
	वापस 0;
पूर्ण

/**
 * bsg_prepare_job - create the bsg_job काष्ठाure क्रम the bsg request
 * @dev: device that is being sent the bsg request
 * @req: BSG request that needs a job काष्ठाure
 */
अटल bool bsg_prepare_job(काष्ठा device *dev, काष्ठा request *req)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(req);
	पूर्णांक ret;

	job->समयout = req->समयout;

	अगर (req->bio) अणु
		ret = bsg_map_buffer(&job->request_payload, req);
		अगर (ret)
			जाओ failjob_rls_job;
	पूर्ण
	अगर (job->bidi_rq) अणु
		ret = bsg_map_buffer(&job->reply_payload, job->bidi_rq);
		अगर (ret)
			जाओ failjob_rls_rqst_payload;
	पूर्ण
	job->dev = dev;
	/* take a reference क्रम the request */
	get_device(job->dev);
	kref_init(&job->kref);
	वापस true;

failjob_rls_rqst_payload:
	kमुक्त(job->request_payload.sg_list);
failjob_rls_job:
	job->result = -ENOMEM;
	वापस false;
पूर्ण

/**
 * bsg_queue_rq - generic handler क्रम bsg requests
 * @hctx: hardware queue
 * @bd: queue data
 *
 * On error the create_bsg_job function should वापस a -Exyz error value
 * that will be set to ->result.
 *
 * Drivers/subsys should pass this to the queue init function.
 */
अटल blk_status_t bsg_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा device *dev = q->queuedata;
	काष्ठा request *req = bd->rq;
	काष्ठा bsg_set *bset =
		container_of(q->tag_set, काष्ठा bsg_set, tag_set);
	blk_status_t sts = BLK_STS_IOERR;
	पूर्णांक ret;

	blk_mq_start_request(req);

	अगर (!get_device(dev))
		वापस BLK_STS_IOERR;

	अगर (!bsg_prepare_job(dev, req))
		जाओ out;

	ret = bset->job_fn(blk_mq_rq_to_pdu(req));
	अगर (!ret)
		sts = BLK_STS_OK;

out:
	put_device(dev);
	वापस sts;
पूर्ण

/* called right after the request is allocated क्रम the request_queue */
अटल पूर्णांक bsg_init_rq(काष्ठा blk_mq_tag_set *set, काष्ठा request *req,
		       अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(req);

	job->reply = kzalloc(SCSI_SENSE_BUFFERSIZE, GFP_KERNEL);
	अगर (!job->reply)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/* called right beक्रमe the request is given to the request_queue user */
अटल व्योम bsg_initialize_rq(काष्ठा request *req)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(req);
	व्योम *reply = job->reply;

	स_रखो(job, 0, माप(*job));
	job->reply = reply;
	job->reply_len = SCSI_SENSE_BUFFERSIZE;
	job->dd_data = job + 1;
पूर्ण

अटल व्योम bsg_निकास_rq(काष्ठा blk_mq_tag_set *set, काष्ठा request *req,
		       अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(req);

	kमुक्त(job->reply);
पूर्ण

व्योम bsg_हटाओ_queue(काष्ठा request_queue *q)
अणु
	अगर (q) अणु
		काष्ठा bsg_set *bset =
			container_of(q->tag_set, काष्ठा bsg_set, tag_set);

		bsg_unरेजिस्टर_queue(q);
		blk_cleanup_queue(q);
		blk_mq_मुक्त_tag_set(&bset->tag_set);
		kमुक्त(bset);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bsg_हटाओ_queue);

अटल क्रमागत blk_eh_समयr_वापस bsg_समयout(काष्ठा request *rq, bool reserved)
अणु
	काष्ठा bsg_set *bset =
		container_of(rq->q->tag_set, काष्ठा bsg_set, tag_set);

	अगर (!bset->समयout_fn)
		वापस BLK_EH_DONE;
	वापस bset->समयout_fn(rq);
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops bsg_mq_ops = अणु
	.queue_rq		= bsg_queue_rq,
	.init_request		= bsg_init_rq,
	.निकास_request		= bsg_निकास_rq,
	.initialize_rq_fn	= bsg_initialize_rq,
	.complete		= bsg_complete,
	.समयout		= bsg_समयout,
पूर्ण;

/**
 * bsg_setup_queue - Create and add the bsg hooks so we can receive requests
 * @dev: device to attach bsg device to
 * @name: device to give bsg device
 * @job_fn: bsg job handler
 * @समयout: समयout handler function poपूर्णांकer
 * @dd_job_size: size of LLD data needed क्रम each job
 */
काष्ठा request_queue *bsg_setup_queue(काष्ठा device *dev, स्थिर अक्षर *name,
		bsg_job_fn *job_fn, bsg_समयout_fn *समयout, पूर्णांक dd_job_size)
अणु
	काष्ठा bsg_set *bset;
	काष्ठा blk_mq_tag_set *set;
	काष्ठा request_queue *q;
	पूर्णांक ret = -ENOMEM;

	bset = kzalloc(माप(*bset), GFP_KERNEL);
	अगर (!bset)
		वापस ERR_PTR(-ENOMEM);

	bset->job_fn = job_fn;
	bset->समयout_fn = समयout;

	set = &bset->tag_set;
	set->ops = &bsg_mq_ops;
	set->nr_hw_queues = 1;
	set->queue_depth = 128;
	set->numa_node = NUMA_NO_NODE;
	set->cmd_size = माप(काष्ठा bsg_job) + dd_job_size;
	set->flags = BLK_MQ_F_NO_SCHED | BLK_MQ_F_BLOCKING;
	अगर (blk_mq_alloc_tag_set(set))
		जाओ out_tag_set;

	q = blk_mq_init_queue(set);
	अगर (IS_ERR(q)) अणु
		ret = PTR_ERR(q);
		जाओ out_queue;
	पूर्ण

	q->queuedata = dev;
	blk_queue_rq_समयout(q, BLK_DEFAULT_SG_TIMEOUT);

	ret = bsg_रेजिस्टर_queue(q, dev, name, &bsg_transport_ops);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: bsg interface failed to "
		       "initialize - register queue\n", dev->kobj.name);
		जाओ out_cleanup_queue;
	पूर्ण

	वापस q;
out_cleanup_queue:
	blk_cleanup_queue(q);
out_queue:
	blk_mq_मुक्त_tag_set(set);
out_tag_set:
	kमुक्त(bset);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(bsg_setup_queue);
