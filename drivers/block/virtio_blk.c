<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//#घोषणा DEBUG
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_blk.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/idr.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-mq-virtपन.स>
#समावेश <linux/numa.h>
#समावेश <uapi/linux/virtio_ring.h>

#घोषणा PART_BITS 4
#घोषणा VQ_NAME_LEN 16
#घोषणा MAX_DISCARD_SEGMENTS 256u

अटल पूर्णांक major;
अटल DEFINE_IDA(vd_index_ida);

अटल काष्ठा workqueue_काष्ठा *virtblk_wq;

काष्ठा virtio_blk_vq अणु
	काष्ठा virtqueue *vq;
	spinlock_t lock;
	अक्षर name[VQ_NAME_LEN];
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा virtio_blk अणु
	/*
	 * This mutex must be held by anything that may run after
	 * virtblk_हटाओ() sets vblk->vdev to शून्य.
	 *
	 * blk-mq, virtqueue processing, and sysfs attribute code paths are
	 * shut करोwn beक्रमe vblk->vdev is set to शून्य and thereक्रमe करो not need
	 * to hold this mutex.
	 */
	काष्ठा mutex vdev_mutex;
	काष्ठा virtio_device *vdev;

	/* The disk काष्ठाure क्रम the kernel. */
	काष्ठा gendisk *disk;

	/* Block layer tags. */
	काष्ठा blk_mq_tag_set tag_set;

	/* Process context क्रम config space updates */
	काष्ठा work_काष्ठा config_work;

	/*
	 * Tracks references from block_device_operations खोलो/release and
	 * virtio_driver probe/हटाओ so this object can be मुक्तd once no
	 * दीर्घer in use.
	 */
	refcount_t refs;

	/* What host tells us, plus 2 क्रम header & tailer. */
	अचिन्हित पूर्णांक sg_elems;

	/* Ida index - used to track minor number allocations. */
	पूर्णांक index;

	/* num of vqs */
	पूर्णांक num_vqs;
	काष्ठा virtio_blk_vq *vqs;
पूर्ण;

काष्ठा virtblk_req अणु
	काष्ठा virtio_blk_outhdr out_hdr;
	u8 status;
	काष्ठा scatterlist sg[];
पूर्ण;

अटल अंतरभूत blk_status_t virtblk_result(काष्ठा virtblk_req *vbr)
अणु
	चयन (vbr->status) अणु
	हाल VIRTIO_BLK_S_OK:
		वापस BLK_STS_OK;
	हाल VIRTIO_BLK_S_UNSUPP:
		वापस BLK_STS_NOTSUPP;
	शेष:
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

अटल पूर्णांक virtblk_add_req(काष्ठा virtqueue *vq, काष्ठा virtblk_req *vbr,
		काष्ठा scatterlist *data_sg, bool have_data)
अणु
	काष्ठा scatterlist hdr, status, *sgs[3];
	अचिन्हित पूर्णांक num_out = 0, num_in = 0;

	sg_init_one(&hdr, &vbr->out_hdr, माप(vbr->out_hdr));
	sgs[num_out++] = &hdr;

	अगर (have_data) अणु
		अगर (vbr->out_hdr.type & cpu_to_virtio32(vq->vdev, VIRTIO_BLK_T_OUT))
			sgs[num_out++] = data_sg;
		अन्यथा
			sgs[num_out + num_in++] = data_sg;
	पूर्ण

	sg_init_one(&status, &vbr->status, माप(vbr->status));
	sgs[num_out + num_in++] = &status;

	वापस virtqueue_add_sgs(vq, sgs, num_out, num_in, vbr, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक virtblk_setup_discard_ग_लिखो_zeroes(काष्ठा request *req, bool unmap)
अणु
	अचिन्हित लघु segments = blk_rq_nr_discard_segments(req);
	अचिन्हित लघु n = 0;
	काष्ठा virtio_blk_discard_ग_लिखो_zeroes *range;
	काष्ठा bio *bio;
	u32 flags = 0;

	अगर (unmap)
		flags |= VIRTIO_BLK_WRITE_ZEROES_FLAG_UNMAP;

	range = kदो_स्मृति_array(segments, माप(*range), GFP_ATOMIC);
	अगर (!range)
		वापस -ENOMEM;

	/*
	 * Single max discard segment means multi-range discard isn't
	 * supported, and block layer only runs contiguity merge like
	 * normal RW request. So we can't reply on bio क्रम retrieving
	 * each range info.
	 */
	अगर (queue_max_discard_segments(req->q) == 1) अणु
		range[0].flags = cpu_to_le32(flags);
		range[0].num_sectors = cpu_to_le32(blk_rq_sectors(req));
		range[0].sector = cpu_to_le64(blk_rq_pos(req));
		n = 1;
	पूर्ण अन्यथा अणु
		__rq_क्रम_each_bio(bio, req) अणु
			u64 sector = bio->bi_iter.bi_sector;
			u32 num_sectors = bio->bi_iter.bi_size >> SECTOR_SHIFT;

			range[n].flags = cpu_to_le32(flags);
			range[n].num_sectors = cpu_to_le32(num_sectors);
			range[n].sector = cpu_to_le64(sector);
			n++;
		पूर्ण
	पूर्ण

	WARN_ON_ONCE(n != segments);

	req->special_vec.bv_page = virt_to_page(range);
	req->special_vec.bv_offset = offset_in_page(range);
	req->special_vec.bv_len = माप(*range) * segments;
	req->rq_flags |= RQF_SPECIAL_PAYLOAD;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम virtblk_request_करोne(काष्ठा request *req)
अणु
	काष्ठा virtblk_req *vbr = blk_mq_rq_to_pdu(req);

	अगर (req->rq_flags & RQF_SPECIAL_PAYLOAD) अणु
		kमुक्त(page_address(req->special_vec.bv_page) +
		      req->special_vec.bv_offset);
	पूर्ण

	blk_mq_end_request(req, virtblk_result(vbr));
पूर्ण

अटल व्योम virtblk_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_blk *vblk = vq->vdev->priv;
	bool req_करोne = false;
	पूर्णांक qid = vq->index;
	काष्ठा virtblk_req *vbr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;

	spin_lock_irqsave(&vblk->vqs[qid].lock, flags);
	करो अणु
		virtqueue_disable_cb(vq);
		जबतक ((vbr = virtqueue_get_buf(vblk->vqs[qid].vq, &len)) != शून्य) अणु
			काष्ठा request *req = blk_mq_rq_from_pdu(vbr);

			अगर (likely(!blk_should_fake_समयout(req->q)))
				blk_mq_complete_request(req);
			req_करोne = true;
		पूर्ण
		अगर (unlikely(virtqueue_is_broken(vq)))
			अवरोध;
	पूर्ण जबतक (!virtqueue_enable_cb(vq));

	/* In हाल queue is stopped रुकोing क्रम more buffers. */
	अगर (req_करोne)
		blk_mq_start_stopped_hw_queues(vblk->disk->queue, true);
	spin_unlock_irqrestore(&vblk->vqs[qid].lock, flags);
पूर्ण

अटल व्योम virtio_commit_rqs(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा virtio_blk *vblk = hctx->queue->queuedata;
	काष्ठा virtio_blk_vq *vq = &vblk->vqs[hctx->queue_num];
	bool kick;

	spin_lock_irq(&vq->lock);
	kick = virtqueue_kick_prepare(vq->vq);
	spin_unlock_irq(&vq->lock);

	अगर (kick)
		virtqueue_notअगरy(vq->vq);
पूर्ण

अटल blk_status_t virtio_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			   स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा virtio_blk *vblk = hctx->queue->queuedata;
	काष्ठा request *req = bd->rq;
	काष्ठा virtblk_req *vbr = blk_mq_rq_to_pdu(req);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक num;
	पूर्णांक qid = hctx->queue_num;
	पूर्णांक err;
	bool notअगरy = false;
	bool unmap = false;
	u32 type;

	BUG_ON(req->nr_phys_segments + 2 > vblk->sg_elems);

	चयन (req_op(req)) अणु
	हाल REQ_OP_READ:
	हाल REQ_OP_WRITE:
		type = 0;
		अवरोध;
	हाल REQ_OP_FLUSH:
		type = VIRTIO_BLK_T_FLUSH;
		अवरोध;
	हाल REQ_OP_DISCARD:
		type = VIRTIO_BLK_T_DISCARD;
		अवरोध;
	हाल REQ_OP_WRITE_ZEROES:
		type = VIRTIO_BLK_T_WRITE_ZEROES;
		unmap = !(req->cmd_flags & REQ_NOUNMAP);
		अवरोध;
	हाल REQ_OP_DRV_IN:
		type = VIRTIO_BLK_T_GET_ID;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस BLK_STS_IOERR;
	पूर्ण

	vbr->out_hdr.type = cpu_to_virtio32(vblk->vdev, type);
	vbr->out_hdr.sector = type ?
		0 : cpu_to_virtio64(vblk->vdev, blk_rq_pos(req));
	vbr->out_hdr.ioprio = cpu_to_virtio32(vblk->vdev, req_get_ioprio(req));

	blk_mq_start_request(req);

	अगर (type == VIRTIO_BLK_T_DISCARD || type == VIRTIO_BLK_T_WRITE_ZEROES) अणु
		err = virtblk_setup_discard_ग_लिखो_zeroes(req, unmap);
		अगर (err)
			वापस BLK_STS_RESOURCE;
	पूर्ण

	num = blk_rq_map_sg(hctx->queue, req, vbr->sg);
	अगर (num) अणु
		अगर (rq_data_dir(req) == WRITE)
			vbr->out_hdr.type |= cpu_to_virtio32(vblk->vdev, VIRTIO_BLK_T_OUT);
		अन्यथा
			vbr->out_hdr.type |= cpu_to_virtio32(vblk->vdev, VIRTIO_BLK_T_IN);
	पूर्ण

	spin_lock_irqsave(&vblk->vqs[qid].lock, flags);
	err = virtblk_add_req(vblk->vqs[qid].vq, vbr, vbr->sg, num);
	अगर (err) अणु
		virtqueue_kick(vblk->vqs[qid].vq);
		/* Don't stop the queue अगर -ENOMEM: we may have failed to
		 * bounce the buffer due to global resource outage.
		 */
		अगर (err == -ENOSPC)
			blk_mq_stop_hw_queue(hctx);
		spin_unlock_irqrestore(&vblk->vqs[qid].lock, flags);
		चयन (err) अणु
		हाल -ENOSPC:
			वापस BLK_STS_DEV_RESOURCE;
		हाल -ENOMEM:
			वापस BLK_STS_RESOURCE;
		शेष:
			वापस BLK_STS_IOERR;
		पूर्ण
	पूर्ण

	अगर (bd->last && virtqueue_kick_prepare(vblk->vqs[qid].vq))
		notअगरy = true;
	spin_unlock_irqrestore(&vblk->vqs[qid].lock, flags);

	अगर (notअगरy)
		virtqueue_notअगरy(vblk->vqs[qid].vq);
	वापस BLK_STS_OK;
पूर्ण

/* वापस id (s/n) string क्रम *disk to *id_str
 */
अटल पूर्णांक virtblk_get_id(काष्ठा gendisk *disk, अक्षर *id_str)
अणु
	काष्ठा virtio_blk *vblk = disk->निजी_data;
	काष्ठा request_queue *q = vblk->disk->queue;
	काष्ठा request *req;
	पूर्णांक err;

	req = blk_get_request(q, REQ_OP_DRV_IN, 0);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	err = blk_rq_map_kern(q, req, id_str, VIRTIO_BLK_ID_BYTES, GFP_KERNEL);
	अगर (err)
		जाओ out;

	blk_execute_rq(vblk->disk, req, false);
	err = blk_status_to_त्रुटि_सं(virtblk_result(blk_mq_rq_to_pdu(req)));
out:
	blk_put_request(req);
	वापस err;
पूर्ण

अटल व्योम virtblk_get(काष्ठा virtio_blk *vblk)
अणु
	refcount_inc(&vblk->refs);
पूर्ण

अटल व्योम virtblk_put(काष्ठा virtio_blk *vblk)
अणु
	अगर (refcount_dec_and_test(&vblk->refs)) अणु
		ida_simple_हटाओ(&vd_index_ida, vblk->index);
		mutex_destroy(&vblk->vdev_mutex);
		kमुक्त(vblk);
	पूर्ण
पूर्ण

अटल पूर्णांक virtblk_खोलो(काष्ठा block_device *bd, भ_शेषe_t mode)
अणु
	काष्ठा virtio_blk *vblk = bd->bd_disk->निजी_data;
	पूर्णांक ret = 0;

	mutex_lock(&vblk->vdev_mutex);

	अगर (vblk->vdev)
		virtblk_get(vblk);
	अन्यथा
		ret = -ENXIO;

	mutex_unlock(&vblk->vdev_mutex);
	वापस ret;
पूर्ण

अटल व्योम virtblk_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा virtio_blk *vblk = disk->निजी_data;

	virtblk_put(vblk);
पूर्ण

/* We provide getgeo only to please some old bootloader/partitioning tools */
अटल पूर्णांक virtblk_getgeo(काष्ठा block_device *bd, काष्ठा hd_geometry *geo)
अणु
	काष्ठा virtio_blk *vblk = bd->bd_disk->निजी_data;
	पूर्णांक ret = 0;

	mutex_lock(&vblk->vdev_mutex);

	अगर (!vblk->vdev) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	/* see अगर the host passed in geometry config */
	अगर (virtio_has_feature(vblk->vdev, VIRTIO_BLK_F_GEOMETRY)) अणु
		virtio_cपढ़ो(vblk->vdev, काष्ठा virtio_blk_config,
			     geometry.cylinders, &geo->cylinders);
		virtio_cपढ़ो(vblk->vdev, काष्ठा virtio_blk_config,
			     geometry.heads, &geo->heads);
		virtio_cपढ़ो(vblk->vdev, काष्ठा virtio_blk_config,
			     geometry.sectors, &geo->sectors);
	पूर्ण अन्यथा अणु
		/* some standard values, similar to sd */
		geo->heads = 1 << 6;
		geo->sectors = 1 << 5;
		geo->cylinders = get_capacity(bd->bd_disk) >> 11;
	पूर्ण
out:
	mutex_unlock(&vblk->vdev_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा block_device_operations virtblk_fops = अणु
	.owner  = THIS_MODULE,
	.खोलो = virtblk_खोलो,
	.release = virtblk_release,
	.getgeo = virtblk_getgeo,
पूर्ण;

अटल पूर्णांक index_to_minor(पूर्णांक index)
अणु
	वापस index << PART_BITS;
पूर्ण

अटल पूर्णांक minor_to_index(पूर्णांक minor)
अणु
	वापस minor >> PART_BITS;
पूर्ण

अटल sमाप_प्रकार serial_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	पूर्णांक err;

	/* sysfs gives us a PAGE_SIZE buffer */
	BUILD_BUG_ON(PAGE_SIZE < VIRTIO_BLK_ID_BYTES);

	buf[VIRTIO_BLK_ID_BYTES] = '\0';
	err = virtblk_get_id(disk, buf);
	अगर (!err)
		वापस म_माप(buf);

	अगर (err == -EIO) /* Unsupported? Make it empty. */
		वापस 0;

	वापस err;
पूर्ण

अटल DEVICE_ATTR_RO(serial);

/* The queue's logical block size must be set beक्रमe calling this */
अटल व्योम virtblk_update_capacity(काष्ठा virtio_blk *vblk, bool resize)
अणु
	काष्ठा virtio_device *vdev = vblk->vdev;
	काष्ठा request_queue *q = vblk->disk->queue;
	अक्षर cap_str_2[10], cap_str_10[10];
	अचिन्हित दीर्घ दीर्घ nblocks;
	u64 capacity;

	/* Host must always specअगरy the capacity. */
	virtio_cपढ़ो(vdev, काष्ठा virtio_blk_config, capacity, &capacity);

	/* If capacity is too big, truncate with warning. */
	अगर ((sector_t)capacity != capacity) अणु
		dev_warn(&vdev->dev, "Capacity %llu too large: truncating\n",
			 (अचिन्हित दीर्घ दीर्घ)capacity);
		capacity = (sector_t)-1;
	पूर्ण

	nblocks = DIV_ROUND_UP_ULL(capacity, queue_logical_block_size(q) >> 9);

	string_get_size(nblocks, queue_logical_block_size(q),
			STRING_UNITS_2, cap_str_2, माप(cap_str_2));
	string_get_size(nblocks, queue_logical_block_size(q),
			STRING_UNITS_10, cap_str_10, माप(cap_str_10));

	dev_notice(&vdev->dev,
		   "[%s] %s%llu %d-byte logical blocks (%s/%s)\n",
		   vblk->disk->disk_name,
		   resize ? "new size: " : "",
		   nblocks,
		   queue_logical_block_size(q),
		   cap_str_10,
		   cap_str_2);

	set_capacity_and_notअगरy(vblk->disk, capacity);
पूर्ण

अटल व्योम virtblk_config_changed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_blk *vblk =
		container_of(work, काष्ठा virtio_blk, config_work);

	virtblk_update_capacity(vblk, true);
पूर्ण

अटल व्योम virtblk_config_changed(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_blk *vblk = vdev->priv;

	queue_work(virtblk_wq, &vblk->config_work);
पूर्ण

अटल पूर्णांक init_vq(काष्ठा virtio_blk *vblk)
अणु
	पूर्णांक err;
	पूर्णांक i;
	vq_callback_t **callbacks;
	स्थिर अक्षर **names;
	काष्ठा virtqueue **vqs;
	अचिन्हित लघु num_vqs;
	काष्ठा virtio_device *vdev = vblk->vdev;
	काष्ठा irq_affinity desc = अणु 0, पूर्ण;

	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_MQ,
				   काष्ठा virtio_blk_config, num_queues,
				   &num_vqs);
	अगर (err)
		num_vqs = 1;

	num_vqs = min_t(अचिन्हित पूर्णांक, nr_cpu_ids, num_vqs);

	vblk->vqs = kदो_स्मृति_array(num_vqs, माप(*vblk->vqs), GFP_KERNEL);
	अगर (!vblk->vqs)
		वापस -ENOMEM;

	names = kदो_स्मृति_array(num_vqs, माप(*names), GFP_KERNEL);
	callbacks = kदो_स्मृति_array(num_vqs, माप(*callbacks), GFP_KERNEL);
	vqs = kदो_स्मृति_array(num_vqs, माप(*vqs), GFP_KERNEL);
	अगर (!names || !callbacks || !vqs) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_vqs; i++) अणु
		callbacks[i] = virtblk_करोne;
		snम_लिखो(vblk->vqs[i].name, VQ_NAME_LEN, "req.%d", i);
		names[i] = vblk->vqs[i].name;
	पूर्ण

	/* Discover virtqueues and ग_लिखो inक्रमmation to configuration.  */
	err = virtio_find_vqs(vdev, num_vqs, vqs, callbacks, names, &desc);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < num_vqs; i++) अणु
		spin_lock_init(&vblk->vqs[i].lock);
		vblk->vqs[i].vq = vqs[i];
	पूर्ण
	vblk->num_vqs = num_vqs;

out:
	kमुक्त(vqs);
	kमुक्त(callbacks);
	kमुक्त(names);
	अगर (err)
		kमुक्त(vblk->vqs);
	वापस err;
पूर्ण

/*
 * Legacy naming scheme used क्रम virtio devices.  We are stuck with it क्रम
 * virtio blk but करोn't ever use it क्रम any new driver.
 */
अटल पूर्णांक virtblk_name_क्रमmat(अक्षर *prefix, पूर्णांक index, अक्षर *buf, पूर्णांक buflen)
अणु
	स्थिर पूर्णांक base = 'z' - 'a' + 1;
	अक्षर *begin = buf + म_माप(prefix);
	अक्षर *end = buf + buflen;
	अक्षर *p;
	पूर्णांक unit;

	p = end - 1;
	*p = '\0';
	unit = base;
	करो अणु
		अगर (p == begin)
			वापस -EINVAL;
		*--p = 'a' + (index % unit);
		index = (index / unit) - 1;
	पूर्ण जबतक (index >= 0);

	स_हटाओ(begin, p, end - p);
	स_नकल(buf, prefix, म_माप(prefix));

	वापस 0;
पूर्ण

अटल पूर्णांक virtblk_get_cache_mode(काष्ठा virtio_device *vdev)
अणु
	u8 ग_लिखोback;
	पूर्णांक err;

	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_CONFIG_WCE,
				   काष्ठा virtio_blk_config, wce,
				   &ग_लिखोback);

	/*
	 * If WCE is not configurable and flush is not available,
	 * assume no ग_लिखोback cache is in use.
	 */
	अगर (err)
		ग_लिखोback = virtio_has_feature(vdev, VIRTIO_BLK_F_FLUSH);

	वापस ग_लिखोback;
पूर्ण

अटल व्योम virtblk_update_cache_mode(काष्ठा virtio_device *vdev)
अणु
	u8 ग_लिखोback = virtblk_get_cache_mode(vdev);
	काष्ठा virtio_blk *vblk = vdev->priv;

	blk_queue_ग_लिखो_cache(vblk->disk->queue, ग_लिखोback, false);
पूर्ण

अटल स्थिर अक्षर *स्थिर virtblk_cache_types[] = अणु
	"write through", "write back"
पूर्ण;

अटल sमाप_प्रकार
cache_type_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा virtio_blk *vblk = disk->निजी_data;
	काष्ठा virtio_device *vdev = vblk->vdev;
	पूर्णांक i;

	BUG_ON(!virtio_has_feature(vblk->vdev, VIRTIO_BLK_F_CONFIG_WCE));
	i = sysfs_match_string(virtblk_cache_types, buf);
	अगर (i < 0)
		वापस i;

	virtio_cग_लिखो8(vdev, दुरत्व(काष्ठा virtio_blk_config, wce), i);
	virtblk_update_cache_mode(vdev);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
cache_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा virtio_blk *vblk = disk->निजी_data;
	u8 ग_लिखोback = virtblk_get_cache_mode(vblk->vdev);

	BUG_ON(ग_लिखोback >= ARRAY_SIZE(virtblk_cache_types));
	वापस snम_लिखो(buf, 40, "%s\n", virtblk_cache_types[ग_लिखोback]);
पूर्ण

अटल DEVICE_ATTR_RW(cache_type);

अटल काष्ठा attribute *virtblk_attrs[] = अणु
	&dev_attr_serial.attr,
	&dev_attr_cache_type.attr,
	शून्य,
पूर्ण;

अटल umode_t virtblk_attrs_are_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा virtio_blk *vblk = disk->निजी_data;
	काष्ठा virtio_device *vdev = vblk->vdev;

	अगर (a == &dev_attr_cache_type.attr &&
	    !virtio_has_feature(vdev, VIRTIO_BLK_F_CONFIG_WCE))
		वापस S_IRUGO;

	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group virtblk_attr_group = अणु
	.attrs = virtblk_attrs,
	.is_visible = virtblk_attrs_are_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *virtblk_attr_groups[] = अणु
	&virtblk_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक virtblk_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
		अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा virtio_blk *vblk = set->driver_data;
	काष्ठा virtblk_req *vbr = blk_mq_rq_to_pdu(rq);

	sg_init_table(vbr->sg, vblk->sg_elems);
	वापस 0;
पूर्ण

अटल पूर्णांक virtblk_map_queues(काष्ठा blk_mq_tag_set *set)
अणु
	काष्ठा virtio_blk *vblk = set->driver_data;

	वापस blk_mq_virtio_map_queues(&set->map[HCTX_TYPE_DEFAULT],
					vblk->vdev, 0);
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops virtio_mq_ops = अणु
	.queue_rq	= virtio_queue_rq,
	.commit_rqs	= virtio_commit_rqs,
	.complete	= virtblk_request_करोne,
	.init_request	= virtblk_init_request,
	.map_queues	= virtblk_map_queues,
पूर्ण;

अटल अचिन्हित पूर्णांक virtblk_queue_depth;
module_param_named(queue_depth, virtblk_queue_depth, uपूर्णांक, 0444);

अटल पूर्णांक virtblk_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_blk *vblk;
	काष्ठा request_queue *q;
	पूर्णांक err, index;

	u32 v, blk_size, max_size, sg_elems, opt_io_size;
	u16 min_io_size;
	u8 physical_block_exp, alignment_offset;
	अचिन्हित पूर्णांक queue_depth;

	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	err = ida_simple_get(&vd_index_ida, 0, minor_to_index(1 << MINORBITS),
			     GFP_KERNEL);
	अगर (err < 0)
		जाओ out;
	index = err;

	/* We need to know how many segments beक्रमe we allocate. */
	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_SEG_MAX,
				   काष्ठा virtio_blk_config, seg_max,
				   &sg_elems);

	/* We need at least one SG element, whatever they say. */
	अगर (err || !sg_elems)
		sg_elems = 1;

	/* We need an extra sg elements at head and tail. */
	sg_elems += 2;
	vdev->priv = vblk = kदो_स्मृति(माप(*vblk), GFP_KERNEL);
	अगर (!vblk) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_index;
	पूर्ण

	/* This reference is dropped in virtblk_हटाओ(). */
	refcount_set(&vblk->refs, 1);
	mutex_init(&vblk->vdev_mutex);

	vblk->vdev = vdev;
	vblk->sg_elems = sg_elems;

	INIT_WORK(&vblk->config_work, virtblk_config_changed_work);

	err = init_vq(vblk);
	अगर (err)
		जाओ out_मुक्त_vblk;

	/* FIXME: How many partitions?  How दीर्घ is a piece of string? */
	vblk->disk = alloc_disk(1 << PART_BITS);
	अगर (!vblk->disk) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_vq;
	पूर्ण

	/* Default queue sizing is to fill the ring. */
	अगर (likely(!virtblk_queue_depth)) अणु
		queue_depth = vblk->vqs[0].vq->num_मुक्त;
		/* ... but without indirect descs, we use 2 descs per req */
		अगर (!virtio_has_feature(vdev, VIRTIO_RING_F_INसूचीECT_DESC))
			queue_depth /= 2;
	पूर्ण अन्यथा अणु
		queue_depth = virtblk_queue_depth;
	पूर्ण

	स_रखो(&vblk->tag_set, 0, माप(vblk->tag_set));
	vblk->tag_set.ops = &virtio_mq_ops;
	vblk->tag_set.queue_depth = queue_depth;
	vblk->tag_set.numa_node = NUMA_NO_NODE;
	vblk->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	vblk->tag_set.cmd_size =
		माप(काष्ठा virtblk_req) +
		माप(काष्ठा scatterlist) * sg_elems;
	vblk->tag_set.driver_data = vblk;
	vblk->tag_set.nr_hw_queues = vblk->num_vqs;

	err = blk_mq_alloc_tag_set(&vblk->tag_set);
	अगर (err)
		जाओ out_put_disk;

	q = blk_mq_init_queue(&vblk->tag_set);
	अगर (IS_ERR(q)) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_tags;
	पूर्ण
	vblk->disk->queue = q;

	q->queuedata = vblk;

	virtblk_name_क्रमmat("vd", index, vblk->disk->disk_name, DISK_NAME_LEN);

	vblk->disk->major = major;
	vblk->disk->first_minor = index_to_minor(index);
	vblk->disk->निजी_data = vblk;
	vblk->disk->fops = &virtblk_fops;
	vblk->disk->flags |= GENHD_FL_EXT_DEVT;
	vblk->index = index;

	/* configure queue flush support */
	virtblk_update_cache_mode(vdev);

	/* If disk is पढ़ो-only in the host, the guest should obey */
	अगर (virtio_has_feature(vdev, VIRTIO_BLK_F_RO))
		set_disk_ro(vblk->disk, 1);

	/* We can handle whatever the host told us to handle. */
	blk_queue_max_segments(q, vblk->sg_elems-2);

	/* No real sector limit. */
	blk_queue_max_hw_sectors(q, -1U);

	max_size = virtio_max_dma_size(vdev);

	/* Host can optionally specअगरy maximum segment size and number of
	 * segments. */
	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_SIZE_MAX,
				   काष्ठा virtio_blk_config, size_max, &v);
	अगर (!err)
		max_size = min(max_size, v);

	blk_queue_max_segment_size(q, max_size);

	/* Host can optionally specअगरy the block size of the device */
	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_BLK_SIZE,
				   काष्ठा virtio_blk_config, blk_size,
				   &blk_size);
	अगर (!err)
		blk_queue_logical_block_size(q, blk_size);
	अन्यथा
		blk_size = queue_logical_block_size(q);

	/* Use topology inक्रमmation अगर available */
	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_TOPOLOGY,
				   काष्ठा virtio_blk_config, physical_block_exp,
				   &physical_block_exp);
	अगर (!err && physical_block_exp)
		blk_queue_physical_block_size(q,
				blk_size * (1 << physical_block_exp));

	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_TOPOLOGY,
				   काष्ठा virtio_blk_config, alignment_offset,
				   &alignment_offset);
	अगर (!err && alignment_offset)
		blk_queue_alignment_offset(q, blk_size * alignment_offset);

	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_TOPOLOGY,
				   काष्ठा virtio_blk_config, min_io_size,
				   &min_io_size);
	अगर (!err && min_io_size)
		blk_queue_io_min(q, blk_size * min_io_size);

	err = virtio_cपढ़ो_feature(vdev, VIRTIO_BLK_F_TOPOLOGY,
				   काष्ठा virtio_blk_config, opt_io_size,
				   &opt_io_size);
	अगर (!err && opt_io_size)
		blk_queue_io_opt(q, blk_size * opt_io_size);

	अगर (virtio_has_feature(vdev, VIRTIO_BLK_F_DISCARD)) अणु
		q->limits.discard_granularity = blk_size;

		virtio_cपढ़ो(vdev, काष्ठा virtio_blk_config,
			     discard_sector_alignment, &v);
		q->limits.discard_alignment = v ? v << SECTOR_SHIFT : 0;

		virtio_cपढ़ो(vdev, काष्ठा virtio_blk_config,
			     max_discard_sectors, &v);
		blk_queue_max_discard_sectors(q, v ? v : अच_पूर्णांक_उच्च);

		virtio_cपढ़ो(vdev, काष्ठा virtio_blk_config, max_discard_seg,
			     &v);
		blk_queue_max_discard_segments(q,
					       min_not_zero(v,
							    MAX_DISCARD_SEGMENTS));

		blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
	पूर्ण

	अगर (virtio_has_feature(vdev, VIRTIO_BLK_F_WRITE_ZEROES)) अणु
		virtio_cपढ़ो(vdev, काष्ठा virtio_blk_config,
			     max_ग_लिखो_zeroes_sectors, &v);
		blk_queue_max_ग_लिखो_zeroes_sectors(q, v ? v : अच_पूर्णांक_उच्च);
	पूर्ण

	virtblk_update_capacity(vblk, false);
	virtio_device_पढ़ोy(vdev);

	device_add_disk(&vdev->dev, vblk->disk, virtblk_attr_groups);
	वापस 0;

out_मुक्त_tags:
	blk_mq_मुक्त_tag_set(&vblk->tag_set);
out_put_disk:
	put_disk(vblk->disk);
out_मुक्त_vq:
	vdev->config->del_vqs(vdev);
	kमुक्त(vblk->vqs);
out_मुक्त_vblk:
	kमुक्त(vblk);
out_मुक्त_index:
	ida_simple_हटाओ(&vd_index_ida, index);
out:
	वापस err;
पूर्ण

अटल व्योम virtblk_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_blk *vblk = vdev->priv;

	/* Make sure no work handler is accessing the device. */
	flush_work(&vblk->config_work);

	del_gendisk(vblk->disk);
	blk_cleanup_queue(vblk->disk->queue);

	blk_mq_मुक्त_tag_set(&vblk->tag_set);

	mutex_lock(&vblk->vdev_mutex);

	/* Stop all the virtqueues. */
	vdev->config->reset(vdev);

	/* Virtqueues are stopped, nothing can use vblk->vdev anymore. */
	vblk->vdev = शून्य;

	put_disk(vblk->disk);
	vdev->config->del_vqs(vdev);
	kमुक्त(vblk->vqs);

	mutex_unlock(&vblk->vdev_mutex);

	virtblk_put(vblk);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtblk_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_blk *vblk = vdev->priv;

	/* Ensure we करोn't receive any more पूर्णांकerrupts */
	vdev->config->reset(vdev);

	/* Make sure no work handler is accessing the device. */
	flush_work(&vblk->config_work);

	blk_mq_quiesce_queue(vblk->disk->queue);

	vdev->config->del_vqs(vdev);
	वापस 0;
पूर्ण

अटल पूर्णांक virtblk_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_blk *vblk = vdev->priv;
	पूर्णांक ret;

	ret = init_vq(vdev->priv);
	अगर (ret)
		वापस ret;

	virtio_device_पढ़ोy(vdev);

	blk_mq_unquiesce_queue(vblk->disk->queue);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_BLOCK, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक features_legacy[] = अणु
	VIRTIO_BLK_F_SEG_MAX, VIRTIO_BLK_F_SIZE_MAX, VIRTIO_BLK_F_GEOMETRY,
	VIRTIO_BLK_F_RO, VIRTIO_BLK_F_BLK_SIZE,
	VIRTIO_BLK_F_FLUSH, VIRTIO_BLK_F_TOPOLOGY, VIRTIO_BLK_F_CONFIG_WCE,
	VIRTIO_BLK_F_MQ, VIRTIO_BLK_F_DISCARD, VIRTIO_BLK_F_WRITE_ZEROES,
पूर्ण
;
अटल अचिन्हित पूर्णांक features[] = अणु
	VIRTIO_BLK_F_SEG_MAX, VIRTIO_BLK_F_SIZE_MAX, VIRTIO_BLK_F_GEOMETRY,
	VIRTIO_BLK_F_RO, VIRTIO_BLK_F_BLK_SIZE,
	VIRTIO_BLK_F_FLUSH, VIRTIO_BLK_F_TOPOLOGY, VIRTIO_BLK_F_CONFIG_WCE,
	VIRTIO_BLK_F_MQ, VIRTIO_BLK_F_DISCARD, VIRTIO_BLK_F_WRITE_ZEROES,
पूर्ण;

अटल काष्ठा virtio_driver virtio_blk = अणु
	.feature_table			= features,
	.feature_table_size		= ARRAY_SIZE(features),
	.feature_table_legacy		= features_legacy,
	.feature_table_size_legacy	= ARRAY_SIZE(features_legacy),
	.driver.name			= KBUILD_MODNAME,
	.driver.owner			= THIS_MODULE,
	.id_table			= id_table,
	.probe				= virtblk_probe,
	.हटाओ				= virtblk_हटाओ,
	.config_changed			= virtblk_config_changed,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze				= virtblk_मुक्तze,
	.restore			= virtblk_restore,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक error;

	virtblk_wq = alloc_workqueue("virtio-blk", 0, 0);
	अगर (!virtblk_wq)
		वापस -ENOMEM;

	major = रेजिस्टर_blkdev(0, "virtblk");
	अगर (major < 0) अणु
		error = major;
		जाओ out_destroy_workqueue;
	पूर्ण

	error = रेजिस्टर_virtio_driver(&virtio_blk);
	अगर (error)
		जाओ out_unरेजिस्टर_blkdev;
	वापस 0;

out_unरेजिस्टर_blkdev:
	unरेजिस्टर_blkdev(major, "virtblk");
out_destroy_workqueue:
	destroy_workqueue(virtblk_wq);
	वापस error;
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	unरेजिस्टर_virtio_driver(&virtio_blk);
	unरेजिस्टर_blkdev(major, "virtblk");
	destroy_workqueue(virtblk_wq);
पूर्ण
module_init(init);
module_निकास(fini);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio block driver");
MODULE_LICENSE("GPL");
