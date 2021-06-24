<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * virtio_pmem.c: Virtio pmem Driver
 *
 * Discovers persistent memory range inक्रमmation
 * from host and provides a virtio based flushing
 * पूर्णांकerface.
 */
#समावेश "virtio_pmem.h"
#समावेश "nd.h"

 /* The पूर्णांकerrupt handler */
व्योम virtio_pmem_host_ack(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_pmem *vpmem = vq->vdev->priv;
	काष्ठा virtio_pmem_request *req_data, *req_buf;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;

	spin_lock_irqsave(&vpmem->pmem_lock, flags);
	जबतक ((req_data = virtqueue_get_buf(vq, &len)) != शून्य) अणु
		req_data->करोne = true;
		wake_up(&req_data->host_acked);

		अगर (!list_empty(&vpmem->req_list)) अणु
			req_buf = list_first_entry(&vpmem->req_list,
					काष्ठा virtio_pmem_request, list);
			req_buf->wq_buf_avail = true;
			wake_up(&req_buf->wq_buf);
			list_del(&req_buf->list);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vpmem->pmem_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_pmem_host_ack);

 /* The request submission function */
अटल पूर्णांक virtio_pmem_flush(काष्ठा nd_region *nd_region)
अणु
	काष्ठा virtio_device *vdev = nd_region->provider_data;
	काष्ठा virtio_pmem *vpmem  = vdev->priv;
	काष्ठा virtio_pmem_request *req_data;
	काष्ठा scatterlist *sgs[2], sg, ret;
	अचिन्हित दीर्घ flags;
	पूर्णांक err, err1;

	might_sleep();
	req_data = kदो_स्मृति(माप(*req_data), GFP_KERNEL);
	अगर (!req_data)
		वापस -ENOMEM;

	req_data->करोne = false;
	init_रुकोqueue_head(&req_data->host_acked);
	init_रुकोqueue_head(&req_data->wq_buf);
	INIT_LIST_HEAD(&req_data->list);
	req_data->req.type = cpu_to_le32(VIRTIO_PMEM_REQ_TYPE_FLUSH);
	sg_init_one(&sg, &req_data->req, माप(req_data->req));
	sgs[0] = &sg;
	sg_init_one(&ret, &req_data->resp.ret, माप(req_data->resp));
	sgs[1] = &ret;

	spin_lock_irqsave(&vpmem->pmem_lock, flags);
	 /*
	  * If virtqueue_add_sgs वापसs -ENOSPC then req_vq भव
	  * queue करोes not have मुक्त descriptor. We add the request
	  * to req_list and रुको क्रम host_ack to wake us up when मुक्त
	  * slots are available.
	  */
	जबतक ((err = virtqueue_add_sgs(vpmem->req_vq, sgs, 1, 1, req_data,
					GFP_ATOMIC)) == -ENOSPC) अणु

		dev_info(&vdev->dev, "failed to send command to virtio pmem device, no free slots in the virtqueue\n");
		req_data->wq_buf_avail = false;
		list_add_tail(&req_data->list, &vpmem->req_list);
		spin_unlock_irqrestore(&vpmem->pmem_lock, flags);

		/* A host response results in "host_ack" getting called */
		रुको_event(req_data->wq_buf, req_data->wq_buf_avail);
		spin_lock_irqsave(&vpmem->pmem_lock, flags);
	पूर्ण
	err1 = virtqueue_kick(vpmem->req_vq);
	spin_unlock_irqrestore(&vpmem->pmem_lock, flags);
	/*
	 * virtqueue_add_sgs failed with error dअगरferent than -ENOSPC, we can't
	 * करो anything about that.
	 */
	अगर (err || !err1) अणु
		dev_info(&vdev->dev, "failed to send command to virtio pmem device\n");
		err = -EIO;
	पूर्ण अन्यथा अणु
		/* A host repsonse results in "host_ack" getting called */
		रुको_event(req_data->host_acked, req_data->करोne);
		err = le32_to_cpu(req_data->resp.ret);
	पूर्ण

	kमुक्त(req_data);
	वापस err;
पूर्ण;

/* The asynchronous flush callback function */
पूर्णांक async_pmem_flush(काष्ठा nd_region *nd_region, काष्ठा bio *bio)
अणु
	/*
	 * Create child bio क्रम asynchronous flush and chain with
	 * parent bio. Otherwise directly call nd_region flush.
	 */
	अगर (bio && bio->bi_iter.bi_sector != -1) अणु
		काष्ठा bio *child = bio_alloc(GFP_ATOMIC, 0);

		अगर (!child)
			वापस -ENOMEM;
		bio_copy_dev(child, bio);
		child->bi_opf = REQ_PREFLUSH;
		child->bi_iter.bi_sector = -1;
		bio_chain(child, bio);
		submit_bio(child);
		वापस 0;
	पूर्ण
	अगर (virtio_pmem_flush(nd_region))
		वापस -EIO;

	वापस 0;
पूर्ण;
EXPORT_SYMBOL_GPL(async_pmem_flush);
MODULE_LICENSE("GPL");
