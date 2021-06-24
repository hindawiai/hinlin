<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Block driver क्रम s390 storage class memory.
 *
 * Copyright IBM Corp. 2012
 * Author(s): Sebastian Ott <sebott@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "scm_block"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/genhd.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/eadm.h>
#समावेश "scm_blk.h"

debug_info_t *scm_debug;
अटल पूर्णांक scm_major;
अटल mempool_t *aidaw_pool;
अटल DEFINE_SPINLOCK(list_lock);
अटल LIST_HEAD(inactive_requests);
अटल अचिन्हित पूर्णांक nr_requests = 64;
अटल अचिन्हित पूर्णांक nr_requests_per_io = 8;
अटल atomic_t nr_devices = ATOMIC_INIT(0);
module_param(nr_requests, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(nr_requests, "Number of parallel requests.");

module_param(nr_requests_per_io, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(nr_requests_per_io, "Number of requests per IO.");

MODULE_DESCRIPTION("Block driver for s390 storage class memory.");
MODULE_LICENSE("GPL");
MODULE_ALIAS("scm:scmdev*");

अटल व्योम __scm_मुक्त_rq(काष्ठा scm_request *scmrq)
अणु
	काष्ठा aob_rq_header *aobrq = to_aobrq(scmrq);

	मुक्त_page((अचिन्हित दीर्घ) scmrq->aob);
	kमुक्त(scmrq->request);
	kमुक्त(aobrq);
पूर्ण

अटल व्योम scm_मुक्त_rqs(व्योम)
अणु
	काष्ठा list_head *iter, *safe;
	काष्ठा scm_request *scmrq;

	spin_lock_irq(&list_lock);
	list_क्रम_each_safe(iter, safe, &inactive_requests) अणु
		scmrq = list_entry(iter, काष्ठा scm_request, list);
		list_del(&scmrq->list);
		__scm_मुक्त_rq(scmrq);
	पूर्ण
	spin_unlock_irq(&list_lock);

	mempool_destroy(aidaw_pool);
पूर्ण

अटल पूर्णांक __scm_alloc_rq(व्योम)
अणु
	काष्ठा aob_rq_header *aobrq;
	काष्ठा scm_request *scmrq;

	aobrq = kzalloc(माप(*aobrq) + माप(*scmrq), GFP_KERNEL);
	अगर (!aobrq)
		वापस -ENOMEM;

	scmrq = (व्योम *) aobrq->data;
	scmrq->aob = (व्योम *) get_zeroed_page(GFP_DMA);
	अगर (!scmrq->aob)
		जाओ मुक्त;

	scmrq->request = kसुस्मृति(nr_requests_per_io, माप(scmrq->request[0]),
				 GFP_KERNEL);
	अगर (!scmrq->request)
		जाओ मुक्त;

	INIT_LIST_HEAD(&scmrq->list);
	spin_lock_irq(&list_lock);
	list_add(&scmrq->list, &inactive_requests);
	spin_unlock_irq(&list_lock);

	वापस 0;
मुक्त:
	__scm_मुक्त_rq(scmrq);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक scm_alloc_rqs(अचिन्हित पूर्णांक nrqs)
अणु
	पूर्णांक ret = 0;

	aidaw_pool = mempool_create_page_pool(max(nrqs/8, 1U), 0);
	अगर (!aidaw_pool)
		वापस -ENOMEM;

	जबतक (nrqs-- && !ret)
		ret = __scm_alloc_rq();

	वापस ret;
पूर्ण

अटल काष्ठा scm_request *scm_request_fetch(व्योम)
अणु
	काष्ठा scm_request *scmrq = शून्य;

	spin_lock_irq(&list_lock);
	अगर (list_empty(&inactive_requests))
		जाओ out;
	scmrq = list_first_entry(&inactive_requests, काष्ठा scm_request, list);
	list_del(&scmrq->list);
out:
	spin_unlock_irq(&list_lock);
	वापस scmrq;
पूर्ण

अटल व्योम scm_request_करोne(काष्ठा scm_request *scmrq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा msb *msb;
	u64 aidaw;
	पूर्णांक i;

	क्रम (i = 0; i < nr_requests_per_io && scmrq->request[i]; i++) अणु
		msb = &scmrq->aob->msb[i];
		aidaw = msb->data_addr;

		अगर ((msb->flags & MSB_FLAG_IDA) && aidaw &&
		    IS_ALIGNED(aidaw, PAGE_SIZE))
			mempool_मुक्त(virt_to_page(aidaw), aidaw_pool);
	पूर्ण

	spin_lock_irqsave(&list_lock, flags);
	list_add(&scmrq->list, &inactive_requests);
	spin_unlock_irqrestore(&list_lock, flags);
पूर्ण

अटल bool scm_permit_request(काष्ठा scm_blk_dev *bdev, काष्ठा request *req)
अणु
	वापस rq_data_dir(req) != WRITE || bdev->state != SCM_WR_PROHIBIT;
पूर्ण

अटल अंतरभूत काष्ठा aidaw *scm_aidaw_alloc(व्योम)
अणु
	काष्ठा page *page = mempool_alloc(aidaw_pool, GFP_ATOMIC);

	वापस page ? page_address(page) : शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ scm_aidaw_bytes(काष्ठा aidaw *aidaw)
अणु
	अचिन्हित दीर्घ _aidaw = (अचिन्हित दीर्घ) aidaw;
	अचिन्हित दीर्घ bytes = ALIGN(_aidaw, PAGE_SIZE) - _aidaw;

	वापस (bytes / माप(*aidaw)) * PAGE_SIZE;
पूर्ण

काष्ठा aidaw *scm_aidaw_fetch(काष्ठा scm_request *scmrq, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा aidaw *aidaw;

	अगर (scm_aidaw_bytes(scmrq->next_aidaw) >= bytes)
		वापस scmrq->next_aidaw;

	aidaw = scm_aidaw_alloc();
	अगर (aidaw)
		स_रखो(aidaw, 0, PAGE_SIZE);
	वापस aidaw;
पूर्ण

अटल पूर्णांक scm_request_prepare(काष्ठा scm_request *scmrq)
अणु
	काष्ठा scm_blk_dev *bdev = scmrq->bdev;
	काष्ठा scm_device *scmdev = bdev->gendisk->निजी_data;
	पूर्णांक pos = scmrq->aob->request.msb_count;
	काष्ठा msb *msb = &scmrq->aob->msb[pos];
	काष्ठा request *req = scmrq->request[pos];
	काष्ठा req_iterator iter;
	काष्ठा aidaw *aidaw;
	काष्ठा bio_vec bv;

	aidaw = scm_aidaw_fetch(scmrq, blk_rq_bytes(req));
	अगर (!aidaw)
		वापस -ENOMEM;

	msb->bs = MSB_BS_4K;
	scmrq->aob->request.msb_count++;
	msb->scm_addr = scmdev->address + ((u64) blk_rq_pos(req) << 9);
	msb->oc = (rq_data_dir(req) == READ) ? MSB_OC_READ : MSB_OC_WRITE;
	msb->flags |= MSB_FLAG_IDA;
	msb->data_addr = (u64) aidaw;

	rq_क्रम_each_segment(bv, req, iter) अणु
		WARN_ON(bv.bv_offset);
		msb->blk_count += bv.bv_len >> 12;
		aidaw->data_addr = (u64) page_address(bv.bv_page);
		aidaw++;
	पूर्ण

	scmrq->next_aidaw = aidaw;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम scm_request_set(काष्ठा scm_request *scmrq,
				   काष्ठा request *req)
अणु
	scmrq->request[scmrq->aob->request.msb_count] = req;
पूर्ण

अटल अंतरभूत व्योम scm_request_init(काष्ठा scm_blk_dev *bdev,
				    काष्ठा scm_request *scmrq)
अणु
	काष्ठा aob_rq_header *aobrq = to_aobrq(scmrq);
	काष्ठा aob *aob = scmrq->aob;

	स_रखो(scmrq->request, 0,
	       nr_requests_per_io * माप(scmrq->request[0]));
	स_रखो(aob, 0, माप(*aob));
	aobrq->scmdev = bdev->scmdev;
	aob->request.cmd_code = ARQB_CMD_MOVE;
	aob->request.data = (u64) aobrq;
	scmrq->bdev = bdev;
	scmrq->retries = 4;
	scmrq->error = BLK_STS_OK;
	/* We करोn't use all msbs - place aidaws at the end of the aob page. */
	scmrq->next_aidaw = (व्योम *) &aob->msb[nr_requests_per_io];
पूर्ण

अटल व्योम scm_request_requeue(काष्ठा scm_request *scmrq)
अणु
	काष्ठा scm_blk_dev *bdev = scmrq->bdev;
	पूर्णांक i;

	क्रम (i = 0; i < nr_requests_per_io && scmrq->request[i]; i++)
		blk_mq_requeue_request(scmrq->request[i], false);

	atomic_dec(&bdev->queued_reqs);
	scm_request_करोne(scmrq);
	blk_mq_kick_requeue_list(bdev->rq);
पूर्ण

अटल व्योम scm_request_finish(काष्ठा scm_request *scmrq)
अणु
	काष्ठा scm_blk_dev *bdev = scmrq->bdev;
	blk_status_t *error;
	पूर्णांक i;

	क्रम (i = 0; i < nr_requests_per_io && scmrq->request[i]; i++) अणु
		error = blk_mq_rq_to_pdu(scmrq->request[i]);
		*error = scmrq->error;
		अगर (likely(!blk_should_fake_समयout(scmrq->request[i]->q)))
			blk_mq_complete_request(scmrq->request[i]);
	पूर्ण

	atomic_dec(&bdev->queued_reqs);
	scm_request_करोne(scmrq);
पूर्ण

अटल व्योम scm_request_start(काष्ठा scm_request *scmrq)
अणु
	काष्ठा scm_blk_dev *bdev = scmrq->bdev;

	atomic_inc(&bdev->queued_reqs);
	अगर (eadm_start_aob(scmrq->aob)) अणु
		SCM_LOG(5, "no subchannel");
		scm_request_requeue(scmrq);
	पूर्ण
पूर्ण

काष्ठा scm_queue अणु
	काष्ठा scm_request *scmrq;
	spinlock_t lock;
पूर्ण;

अटल blk_status_t scm_blk_request(काष्ठा blk_mq_hw_ctx *hctx,
			   स्थिर काष्ठा blk_mq_queue_data *qd)
अणु
	काष्ठा scm_device *scmdev = hctx->queue->queuedata;
	काष्ठा scm_blk_dev *bdev = dev_get_drvdata(&scmdev->dev);
	काष्ठा scm_queue *sq = hctx->driver_data;
	काष्ठा request *req = qd->rq;
	काष्ठा scm_request *scmrq;

	spin_lock(&sq->lock);
	अगर (!scm_permit_request(bdev, req)) अणु
		spin_unlock(&sq->lock);
		वापस BLK_STS_RESOURCE;
	पूर्ण

	scmrq = sq->scmrq;
	अगर (!scmrq) अणु
		scmrq = scm_request_fetch();
		अगर (!scmrq) अणु
			SCM_LOG(5, "no request");
			spin_unlock(&sq->lock);
			वापस BLK_STS_RESOURCE;
		पूर्ण
		scm_request_init(bdev, scmrq);
		sq->scmrq = scmrq;
	पूर्ण
	scm_request_set(scmrq, req);

	अगर (scm_request_prepare(scmrq)) अणु
		SCM_LOG(5, "aidaw alloc failed");
		scm_request_set(scmrq, शून्य);

		अगर (scmrq->aob->request.msb_count)
			scm_request_start(scmrq);

		sq->scmrq = शून्य;
		spin_unlock(&sq->lock);
		वापस BLK_STS_RESOURCE;
	पूर्ण
	blk_mq_start_request(req);

	अगर (qd->last || scmrq->aob->request.msb_count == nr_requests_per_io) अणु
		scm_request_start(scmrq);
		sq->scmrq = शून्य;
	पूर्ण
	spin_unlock(&sq->lock);
	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक scm_blk_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
			     अचिन्हित पूर्णांक idx)
अणु
	काष्ठा scm_queue *qd = kzalloc(माप(*qd), GFP_KERNEL);

	अगर (!qd)
		वापस -ENOMEM;

	spin_lock_init(&qd->lock);
	hctx->driver_data = qd;

	वापस 0;
पूर्ण

अटल व्योम scm_blk_निकास_hctx(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा scm_queue *qd = hctx->driver_data;

	WARN_ON(qd->scmrq);
	kमुक्त(hctx->driver_data);
	hctx->driver_data = शून्य;
पूर्ण

अटल व्योम __scmrq_log_error(काष्ठा scm_request *scmrq)
अणु
	काष्ठा aob *aob = scmrq->aob;

	अगर (scmrq->error == BLK_STS_TIMEOUT)
		SCM_LOG(1, "Request timeout");
	अन्यथा अणु
		SCM_LOG(1, "Request error");
		SCM_LOG_HEX(1, &aob->response, माप(aob->response));
	पूर्ण
	अगर (scmrq->retries)
		SCM_LOG(1, "Retry request");
	अन्यथा
		pr_err("An I/O operation to SCM failed with rc=%d\n",
		       scmrq->error);
पूर्ण

अटल व्योम scm_blk_handle_error(काष्ठा scm_request *scmrq)
अणु
	काष्ठा scm_blk_dev *bdev = scmrq->bdev;
	अचिन्हित दीर्घ flags;

	अगर (scmrq->error != BLK_STS_IOERR)
		जाओ restart;

	/* For -EIO the response block is valid. */
	चयन (scmrq->aob->response.eqc) अणु
	हाल EQC_WR_PROHIBIT:
		spin_lock_irqsave(&bdev->lock, flags);
		अगर (bdev->state != SCM_WR_PROHIBIT)
			pr_info("%lx: Write access to the SCM increment is suspended\n",
				(अचिन्हित दीर्घ) bdev->scmdev->address);
		bdev->state = SCM_WR_PROHIBIT;
		spin_unlock_irqrestore(&bdev->lock, flags);
		जाओ requeue;
	शेष:
		अवरोध;
	पूर्ण

restart:
	अगर (!eadm_start_aob(scmrq->aob))
		वापस;

requeue:
	scm_request_requeue(scmrq);
पूर्ण

व्योम scm_blk_irq(काष्ठा scm_device *scmdev, व्योम *data, blk_status_t error)
अणु
	काष्ठा scm_request *scmrq = data;

	scmrq->error = error;
	अगर (error) अणु
		__scmrq_log_error(scmrq);
		अगर (scmrq->retries-- > 0) अणु
			scm_blk_handle_error(scmrq);
			वापस;
		पूर्ण
	पूर्ण

	scm_request_finish(scmrq);
पूर्ण

अटल व्योम scm_blk_request_करोne(काष्ठा request *req)
अणु
	blk_status_t *error = blk_mq_rq_to_pdu(req);

	blk_mq_end_request(req, *error);
पूर्ण

अटल स्थिर काष्ठा block_device_operations scm_blk_devops = अणु
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops scm_mq_ops = अणु
	.queue_rq = scm_blk_request,
	.complete = scm_blk_request_करोne,
	.init_hctx = scm_blk_init_hctx,
	.निकास_hctx = scm_blk_निकास_hctx,
पूर्ण;

पूर्णांक scm_blk_dev_setup(काष्ठा scm_blk_dev *bdev, काष्ठा scm_device *scmdev)
अणु
	अचिन्हित पूर्णांक devindex, nr_max_blk;
	काष्ठा request_queue *rq;
	पूर्णांक len, ret;

	devindex = atomic_inc_वापस(&nr_devices) - 1;
	/* scma..scmz + scmaa..scmzz */
	अगर (devindex > 701) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	bdev->scmdev = scmdev;
	bdev->state = SCM_OPER;
	spin_lock_init(&bdev->lock);
	atomic_set(&bdev->queued_reqs, 0);

	bdev->tag_set.ops = &scm_mq_ops;
	bdev->tag_set.cmd_size = माप(blk_status_t);
	bdev->tag_set.nr_hw_queues = nr_requests;
	bdev->tag_set.queue_depth = nr_requests_per_io * nr_requests;
	bdev->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	bdev->tag_set.numa_node = NUMA_NO_NODE;

	ret = blk_mq_alloc_tag_set(&bdev->tag_set);
	अगर (ret)
		जाओ out;

	rq = blk_mq_init_queue(&bdev->tag_set);
	अगर (IS_ERR(rq)) अणु
		ret = PTR_ERR(rq);
		जाओ out_tag;
	पूर्ण
	bdev->rq = rq;
	nr_max_blk = min(scmdev->nr_max_block,
			 (अचिन्हित पूर्णांक) (PAGE_SIZE / माप(काष्ठा aidaw)));

	blk_queue_logical_block_size(rq, 1 << 12);
	blk_queue_max_hw_sectors(rq, nr_max_blk << 3); /* 8 * 512 = blk_size */
	blk_queue_max_segments(rq, nr_max_blk);
	blk_queue_flag_set(QUEUE_FLAG_NONROT, rq);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, rq);

	bdev->gendisk = alloc_disk(SCM_NR_PARTS);
	अगर (!bdev->gendisk) अणु
		ret = -ENOMEM;
		जाओ out_queue;
	पूर्ण
	rq->queuedata = scmdev;
	bdev->gendisk->निजी_data = scmdev;
	bdev->gendisk->fops = &scm_blk_devops;
	bdev->gendisk->queue = rq;
	bdev->gendisk->major = scm_major;
	bdev->gendisk->first_minor = devindex * SCM_NR_PARTS;

	len = snम_लिखो(bdev->gendisk->disk_name, DISK_NAME_LEN, "scm");
	अगर (devindex > 25) अणु
		len += snम_लिखो(bdev->gendisk->disk_name + len,
				DISK_NAME_LEN - len, "%c",
				'a' + (devindex / 26) - 1);
		devindex = devindex % 26;
	पूर्ण
	snम_लिखो(bdev->gendisk->disk_name + len, DISK_NAME_LEN - len, "%c",
		 'a' + devindex);

	/* 512 byte sectors */
	set_capacity(bdev->gendisk, scmdev->size >> 9);
	device_add_disk(&scmdev->dev, bdev->gendisk, शून्य);
	वापस 0;

out_queue:
	blk_cleanup_queue(rq);
out_tag:
	blk_mq_मुक्त_tag_set(&bdev->tag_set);
out:
	atomic_dec(&nr_devices);
	वापस ret;
पूर्ण

व्योम scm_blk_dev_cleanup(काष्ठा scm_blk_dev *bdev)
अणु
	del_gendisk(bdev->gendisk);
	blk_cleanup_queue(bdev->gendisk->queue);
	blk_mq_मुक्त_tag_set(&bdev->tag_set);
	put_disk(bdev->gendisk);
पूर्ण

व्योम scm_blk_set_available(काष्ठा scm_blk_dev *bdev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bdev->lock, flags);
	अगर (bdev->state == SCM_WR_PROHIBIT)
		pr_info("%lx: Write access to the SCM increment is restored\n",
			(अचिन्हित दीर्घ) bdev->scmdev->address);
	bdev->state = SCM_OPER;
	spin_unlock_irqrestore(&bdev->lock, flags);
पूर्ण

अटल bool __init scm_blk_params_valid(व्योम)
अणु
	अगर (!nr_requests_per_io || nr_requests_per_io > 64)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __init scm_blk_init(व्योम)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!scm_blk_params_valid())
		जाओ out;

	ret = रेजिस्टर_blkdev(0, "scm");
	अगर (ret < 0)
		जाओ out;

	scm_major = ret;
	ret = scm_alloc_rqs(nr_requests);
	अगर (ret)
		जाओ out_मुक्त;

	scm_debug = debug_रेजिस्टर("scm_log", 16, 1, 16);
	अगर (!scm_debug) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	debug_रेजिस्टर_view(scm_debug, &debug_hex_ascii_view);
	debug_set_level(scm_debug, 2);

	ret = scm_drv_init();
	अगर (ret)
		जाओ out_dbf;

	वापस ret;

out_dbf:
	debug_unरेजिस्टर(scm_debug);
out_मुक्त:
	scm_मुक्त_rqs();
	unरेजिस्टर_blkdev(scm_major, "scm");
out:
	वापस ret;
पूर्ण
module_init(scm_blk_init);

अटल व्योम __निकास scm_blk_cleanup(व्योम)
अणु
	scm_drv_cleanup();
	debug_unरेजिस्टर(scm_debug);
	scm_मुक्त_rqs();
	unरेजिस्टर_blkdev(scm_major, "scm");
पूर्ण
module_निकास(scm_blk_cleanup);
