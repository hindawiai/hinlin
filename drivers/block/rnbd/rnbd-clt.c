<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/idr.h>

#समावेश "rnbd-clt.h"

MODULE_DESCRIPTION("RDMA Network Block Device Client");
MODULE_LICENSE("GPL");

अटल पूर्णांक rnbd_client_major;
अटल DEFINE_IDA(index_ida);
अटल DEFINE_MUTEX(ida_lock);
अटल DEFINE_MUTEX(sess_lock);
अटल LIST_HEAD(sess_list);

/*
 * Maximum number of partitions an instance can have.
 * 6 bits = 64 minors = 63 partitions (one minor is used क्रम the device itself)
 */
#घोषणा RNBD_PART_BITS		6

अटल अंतरभूत bool rnbd_clt_get_sess(काष्ठा rnbd_clt_session *sess)
अणु
	वापस refcount_inc_not_zero(&sess->refcount);
पूर्ण

अटल व्योम मुक्त_sess(काष्ठा rnbd_clt_session *sess);

अटल व्योम rnbd_clt_put_sess(काष्ठा rnbd_clt_session *sess)
अणु
	might_sleep();

	अगर (refcount_dec_and_test(&sess->refcount))
		मुक्त_sess(sess);
पूर्ण

अटल व्योम rnbd_clt_put_dev(काष्ठा rnbd_clt_dev *dev)
अणु
	might_sleep();

	अगर (!refcount_dec_and_test(&dev->refcount))
		वापस;

	mutex_lock(&ida_lock);
	ida_simple_हटाओ(&index_ida, dev->clt_device_id);
	mutex_unlock(&ida_lock);
	kमुक्त(dev->hw_queues);
	kमुक्त(dev->pathname);
	rnbd_clt_put_sess(dev->sess);
	mutex_destroy(&dev->lock);
	kमुक्त(dev);
पूर्ण

अटल अंतरभूत bool rnbd_clt_get_dev(काष्ठा rnbd_clt_dev *dev)
अणु
	वापस refcount_inc_not_zero(&dev->refcount);
पूर्ण

अटल पूर्णांक rnbd_clt_set_dev_attr(काष्ठा rnbd_clt_dev *dev,
				 स्थिर काष्ठा rnbd_msg_खोलो_rsp *rsp)
अणु
	काष्ठा rnbd_clt_session *sess = dev->sess;

	अगर (!rsp->logical_block_size)
		वापस -EINVAL;

	dev->device_id		    = le32_to_cpu(rsp->device_id);
	dev->nsectors		    = le64_to_cpu(rsp->nsectors);
	dev->logical_block_size	    = le16_to_cpu(rsp->logical_block_size);
	dev->physical_block_size    = le16_to_cpu(rsp->physical_block_size);
	dev->max_ग_लिखो_same_sectors = le32_to_cpu(rsp->max_ग_लिखो_same_sectors);
	dev->max_discard_sectors    = le32_to_cpu(rsp->max_discard_sectors);
	dev->discard_granularity    = le32_to_cpu(rsp->discard_granularity);
	dev->discard_alignment	    = le32_to_cpu(rsp->discard_alignment);
	dev->secure_discard	    = le16_to_cpu(rsp->secure_discard);
	dev->rotational		    = rsp->rotational;
	dev->wc			    = !!(rsp->cache_policy & RNBD_WRITEBACK);
	dev->fua		    = !!(rsp->cache_policy & RNBD_FUA);

	dev->max_hw_sectors = sess->max_io_size / SECTOR_SIZE;
	dev->max_segments = BMAX_SEGMENTS;

	वापस 0;
पूर्ण

अटल पूर्णांक rnbd_clt_change_capacity(काष्ठा rnbd_clt_dev *dev,
				    माप_प्रकार new_nsectors)
अणु
	rnbd_clt_info(dev, "Device size changed from %zu to %zu sectors\n",
		       dev->nsectors, new_nsectors);
	dev->nsectors = new_nsectors;
	set_capacity_and_notअगरy(dev->gd, dev->nsectors);
	वापस 0;
पूर्ण

अटल पूर्णांक process_msg_खोलो_rsp(काष्ठा rnbd_clt_dev *dev,
				काष्ठा rnbd_msg_खोलो_rsp *rsp)
अणु
	काष्ठा kobject *gd_kobj;
	पूर्णांक err = 0;

	mutex_lock(&dev->lock);
	अगर (dev->dev_state == DEV_STATE_UNMAPPED) अणु
		rnbd_clt_info(dev,
			       "Ignoring Open-Response message from server for  unmapped device\n");
		err = -ENOENT;
		जाओ out;
	पूर्ण
	अगर (dev->dev_state == DEV_STATE_MAPPED_DISCONNECTED) अणु
		u64 nsectors = le64_to_cpu(rsp->nsectors);

		/*
		 * If the device was remapped and the size changed in the
		 * meanसमय we need to revalidate it
		 */
		अगर (dev->nsectors != nsectors)
			rnbd_clt_change_capacity(dev, nsectors);
		gd_kobj = &disk_to_dev(dev->gd)->kobj;
		kobject_uevent(gd_kobj, KOBJ_ONLINE);
		rnbd_clt_info(dev, "Device online, device remapped successfully\n");
	पूर्ण
	err = rnbd_clt_set_dev_attr(dev, rsp);
	अगर (err)
		जाओ out;
	dev->dev_state = DEV_STATE_MAPPED;

out:
	mutex_unlock(&dev->lock);

	वापस err;
पूर्ण

पूर्णांक rnbd_clt_resize_disk(काष्ठा rnbd_clt_dev *dev, माप_प्रकार newsize)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev->lock);
	अगर (dev->dev_state != DEV_STATE_MAPPED) अणु
		pr_err("Failed to set new size of the device, device is not opened\n");
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	ret = rnbd_clt_change_capacity(dev, newsize);

out:
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rnbd_clt_dev_requeue(काष्ठा rnbd_queue *q)
अणु
	अगर (WARN_ON(!q->hctx))
		वापस;

	/* We can come here from पूर्णांकerrupt, thus async=true */
	blk_mq_run_hw_queue(q->hctx, true);
पूर्ण

क्रमागत अणु
	RNBD_DELAY_IFBUSY = -1,
पूर्ण;

/**
 * rnbd_get_cpu_qlist() - finds a list with HW queues to be rerun
 * @sess:	Session to find a queue क्रम
 * @cpu:	Cpu to start the search from
 *
 * Description:
 *     Each CPU has a list of HW queues, which needs to be rerun.  If a list
 *     is not empty - it is marked with a bit.  This function finds first
 *     set bit in a biपंचांगap and वापसs corresponding CPU list.
 */
अटल काष्ठा rnbd_cpu_qlist *
rnbd_get_cpu_qlist(काष्ठा rnbd_clt_session *sess, पूर्णांक cpu)
अणु
	पूर्णांक bit;

	/* Search from cpu to nr_cpu_ids */
	bit = find_next_bit(sess->cpu_queues_bm, nr_cpu_ids, cpu);
	अगर (bit < nr_cpu_ids) अणु
		वापस per_cpu_ptr(sess->cpu_queues, bit);
	पूर्ण अन्यथा अगर (cpu != 0) अणु
		/* Search from 0 to cpu */
		bit = find_next_bit(sess->cpu_queues_bm, cpu, 0);
		अगर (bit < cpu)
			वापस per_cpu_ptr(sess->cpu_queues, bit);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक nxt_cpu(पूर्णांक cpu)
अणु
	वापस (cpu + 1) % nr_cpu_ids;
पूर्ण

/**
 * rnbd_rerun_अगर_needed() - rerun next queue marked as stopped
 * @sess:	Session to rerun a queue on
 *
 * Description:
 *     Each CPU has it's own list of HW queues, which should be rerun.
 *     Function finds such list with HW queues, takes a list lock, picks up
 *     the first HW queue out of the list and requeues it.
 *
 * Return:
 *     True अगर the queue was requeued, false otherwise.
 *
 * Context:
 *     Does not matter.
 */
अटल bool rnbd_rerun_अगर_needed(काष्ठा rnbd_clt_session *sess)
अणु
	काष्ठा rnbd_queue *q = शून्य;
	काष्ठा rnbd_cpu_qlist *cpu_q;
	अचिन्हित दीर्घ flags;
	पूर्णांक *cpup;

	/*
	 * To keep fairness and not to let other queues starve we always
	 * try to wake up someone अन्यथा in round-robin manner.  That of course
	 * increases latency but queues always have a chance to be executed.
	 */
	cpup = get_cpu_ptr(sess->cpu_rr);
	क्रम (cpu_q = rnbd_get_cpu_qlist(sess, nxt_cpu(*cpup)); cpu_q;
	     cpu_q = rnbd_get_cpu_qlist(sess, nxt_cpu(cpu_q->cpu))) अणु
		अगर (!spin_trylock_irqsave(&cpu_q->requeue_lock, flags))
			जारी;
		अगर (!test_bit(cpu_q->cpu, sess->cpu_queues_bm))
			जाओ unlock;
		q = list_first_entry_or_null(&cpu_q->requeue_list,
					     typeof(*q), requeue_list);
		अगर (WARN_ON(!q))
			जाओ clear_bit;
		list_del_init(&q->requeue_list);
		clear_bit_unlock(0, &q->in_list);

		अगर (list_empty(&cpu_q->requeue_list)) अणु
			/* Clear bit अगर nothing is left */
clear_bit:
			clear_bit(cpu_q->cpu, sess->cpu_queues_bm);
		पूर्ण
unlock:
		spin_unlock_irqrestore(&cpu_q->requeue_lock, flags);

		अगर (q)
			अवरोध;
	पूर्ण

	/**
	 * Saves the CPU that is going to be requeued on the per-cpu var. Just
	 * incrementing it करोesn't work because rnbd_get_cpu_qlist() will
	 * always वापस the first CPU with something on the queue list when the
	 * value stored on the var is greater than the last CPU with something
	 * on the list.
	 */
	अगर (cpu_q)
		*cpup = cpu_q->cpu;
	put_cpu_var(sess->cpu_rr);

	अगर (q)
		rnbd_clt_dev_requeue(q);

	वापस q;
पूर्ण

/**
 * rnbd_rerun_all_अगर_idle() - rerun all queues left in the list अगर
 *				 session is idling (there are no requests
 *				 in-flight).
 * @sess:	Session to rerun the queues on
 *
 * Description:
 *     This function tries to rerun all stopped queues अगर there are no
 *     requests in-flight anymore.  This function tries to solve an obvious
 *     problem, when number of tags < than number of queues (hctx), which
 *     are stopped and put to sleep.  If last permit, which has been just put,
 *     करोes not wake up all left queues (hctxs), IO requests hang क्रमever.
 *
 *     That can happen when all number of permits, say N, have been exhausted
 *     from one CPU, and we have many block devices per session, say M.
 *     Each block device has it's own queue (hctx) क्रम each CPU, so eventually
 *     we can put that number of queues (hctxs) to sleep: M x nr_cpu_ids.
 *     If number of permits N < M x nr_cpu_ids finally we will get an IO hang.
 *
 *     To aव्योम this hang last caller of rnbd_put_permit() (last caller is the
 *     one who observes sess->busy == 0) must wake up all reमुख्यing queues.
 *
 * Context:
 *     Does not matter.
 */
अटल व्योम rnbd_rerun_all_अगर_idle(काष्ठा rnbd_clt_session *sess)
अणु
	bool requeued;

	करो अणु
		requeued = rnbd_rerun_अगर_needed(sess);
	पूर्ण जबतक (atomic_पढ़ो(&sess->busy) == 0 && requeued);
पूर्ण

अटल काष्ठा rtrs_permit *rnbd_get_permit(काष्ठा rnbd_clt_session *sess,
					     क्रमागत rtrs_clt_con_type con_type,
					     क्रमागत रुको_type रुको)
अणु
	काष्ठा rtrs_permit *permit;

	permit = rtrs_clt_get_permit(sess->rtrs, con_type, रुको);
	अगर (permit)
		/* We have a subtle rare हाल here, when all permits can be
		 * consumed beक्रमe busy counter increased.  This is safe,
		 * because loser will get शून्य as a permit, observe 0 busy
		 * counter and immediately restart the queue himself.
		 */
		atomic_inc(&sess->busy);

	वापस permit;
पूर्ण

अटल व्योम rnbd_put_permit(काष्ठा rnbd_clt_session *sess,
			     काष्ठा rtrs_permit *permit)
अणु
	rtrs_clt_put_permit(sess->rtrs, permit);
	atomic_dec(&sess->busy);
	/* Paired with rnbd_clt_dev_add_to_requeue().  Decrement first
	 * and then check queue bits.
	 */
	smp_mb__after_atomic();
	rnbd_rerun_all_अगर_idle(sess);
पूर्ण

अटल काष्ठा rnbd_iu *rnbd_get_iu(काष्ठा rnbd_clt_session *sess,
				     क्रमागत rtrs_clt_con_type con_type,
				     क्रमागत रुको_type रुको)
अणु
	काष्ठा rnbd_iu *iu;
	काष्ठा rtrs_permit *permit;

	iu = kzalloc(माप(*iu), GFP_KERNEL);
	अगर (!iu)
		वापस शून्य;

	permit = rnbd_get_permit(sess, con_type, रुको);
	अगर (!permit) अणु
		kमुक्त(iu);
		वापस शून्य;
	पूर्ण

	iu->permit = permit;
	/*
	 * 1st reference is dropped after finishing sending a "user" message,
	 * 2nd reference is dropped after confirmation with the response is
	 * वापसed.
	 * 1st and 2nd can happen in any order, so the rnbd_iu should be
	 * released (rtrs_permit वापसed to rtrs) only after both
	 * are finished.
	 */
	atomic_set(&iu->refcount, 2);
	init_रुकोqueue_head(&iu->comp.रुको);
	iu->comp.त्रुटि_सं = पूर्णांक_उच्च;

	अगर (sg_alloc_table(&iu->sgt, 1, GFP_KERNEL)) अणु
		rnbd_put_permit(sess, permit);
		kमुक्त(iu);
		वापस शून्य;
	पूर्ण

	वापस iu;
पूर्ण

अटल व्योम rnbd_put_iu(काष्ठा rnbd_clt_session *sess, काष्ठा rnbd_iu *iu)
अणु
	अगर (atomic_dec_and_test(&iu->refcount)) अणु
		sg_मुक्त_table(&iu->sgt);
		rnbd_put_permit(sess, iu->permit);
		kमुक्त(iu);
	पूर्ण
पूर्ण

अटल व्योम rnbd_softirq_करोne_fn(काष्ठा request *rq)
अणु
	काष्ठा rnbd_clt_dev *dev	= rq->rq_disk->निजी_data;
	काष्ठा rnbd_clt_session *sess	= dev->sess;
	काष्ठा rnbd_iu *iu;

	iu = blk_mq_rq_to_pdu(rq);
	sg_मुक्त_table_chained(&iu->sgt, RNBD_INLINE_SG_CNT);
	rnbd_put_permit(sess, iu->permit);
	blk_mq_end_request(rq, त्रुटि_सं_to_blk_status(iu->त्रुटि_सं));
पूर्ण

अटल व्योम msg_io_conf(व्योम *priv, पूर्णांक त्रुटि_सं)
अणु
	काष्ठा rnbd_iu *iu = priv;
	काष्ठा rnbd_clt_dev *dev = iu->dev;
	काष्ठा request *rq = iu->rq;
	पूर्णांक rw = rq_data_dir(rq);

	iu->त्रुटि_सं = त्रुटि_सं;

	blk_mq_complete_request(rq);

	अगर (त्रुटि_सं)
		rnbd_clt_info_rl(dev, "%s I/O failed with err: %d\n",
				 rw == READ ? "read" : "write", त्रुटि_सं);
पूर्ण

अटल व्योम wake_up_iu_comp(काष्ठा rnbd_iu *iu, पूर्णांक त्रुटि_सं)
अणु
	iu->comp.त्रुटि_सं = त्रुटि_सं;
	wake_up(&iu->comp.रुको);
पूर्ण

अटल व्योम msg_conf(व्योम *priv, पूर्णांक त्रुटि_सं)
अणु
	काष्ठा rnbd_iu *iu = priv;

	iu->त्रुटि_सं = त्रुटि_सं;
	schedule_work(&iu->work);
पूर्ण

अटल पूर्णांक send_usr_msg(काष्ठा rtrs_clt *rtrs, पूर्णांक dir,
			काष्ठा rnbd_iu *iu, काष्ठा kvec *vec,
			माप_प्रकार len, काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sg_len,
			व्योम (*conf)(काष्ठा work_काष्ठा *work),
			पूर्णांक *त्रुटि_सं, पूर्णांक रुको)
अणु
	पूर्णांक err;
	काष्ठा rtrs_clt_req_ops req_ops;

	INIT_WORK(&iu->work, conf);
	req_ops = (काष्ठा rtrs_clt_req_ops) अणु
		.priv = iu,
		.conf_fn = msg_conf,
	पूर्ण;
	err = rtrs_clt_request(dir, &req_ops, rtrs, iu->permit,
				vec, 1, len, sg, sg_len);
	अगर (!err && रुको) अणु
		रुको_event(iu->comp.रुको, iu->comp.त्रुटि_सं != पूर्णांक_उच्च);
		*त्रुटि_सं = iu->comp.त्रुटि_सं;
	पूर्ण अन्यथा अणु
		*त्रुटि_सं = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम msg_बंद_conf(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rnbd_iu *iu = container_of(work, काष्ठा rnbd_iu, work);
	काष्ठा rnbd_clt_dev *dev = iu->dev;

	wake_up_iu_comp(iu, iu->त्रुटि_सं);
	rnbd_put_iu(dev->sess, iu);
	rnbd_clt_put_dev(dev);
पूर्ण

अटल पूर्णांक send_msg_बंद(काष्ठा rnbd_clt_dev *dev, u32 device_id,
			  क्रमागत रुको_type रुको)
अणु
	काष्ठा rnbd_clt_session *sess = dev->sess;
	काष्ठा rnbd_msg_बंद msg;
	काष्ठा rnbd_iu *iu;
	काष्ठा kvec vec = अणु
		.iov_base = &msg,
		.iov_len  = माप(msg)
	पूर्ण;
	पूर्णांक err, त्रुटि_सं;

	iu = rnbd_get_iu(sess, RTRS_ADMIN_CON, RTRS_PERMIT_WAIT);
	अगर (!iu)
		वापस -ENOMEM;

	iu->buf = शून्य;
	iu->dev = dev;

	msg.hdr.type	= cpu_to_le16(RNBD_MSG_CLOSE);
	msg.device_id	= cpu_to_le32(device_id);

	WARN_ON(!rnbd_clt_get_dev(dev));
	err = send_usr_msg(sess->rtrs, WRITE, iu, &vec, 0, शून्य, 0,
			   msg_बंद_conf, &त्रुटि_सं, रुको);
	अगर (err) अणु
		rnbd_clt_put_dev(dev);
		rnbd_put_iu(sess, iu);
	पूर्ण अन्यथा अणु
		err = त्रुटि_सं;
	पूर्ण

	rnbd_put_iu(sess, iu);
	वापस err;
पूर्ण

अटल व्योम msg_खोलो_conf(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rnbd_iu *iu = container_of(work, काष्ठा rnbd_iu, work);
	काष्ठा rnbd_msg_खोलो_rsp *rsp = iu->buf;
	काष्ठा rnbd_clt_dev *dev = iu->dev;
	पूर्णांक त्रुटि_सं = iu->त्रुटि_सं;

	अगर (त्रुटि_सं) अणु
		rnbd_clt_err(dev,
			      "Opening failed, server responded: %d\n",
			      त्रुटि_सं);
	पूर्ण अन्यथा अणु
		त्रुटि_सं = process_msg_खोलो_rsp(dev, rsp);
		अगर (त्रुटि_सं) अणु
			u32 device_id = le32_to_cpu(rsp->device_id);
			/*
			 * If server thinks its fine, but we fail to process
			 * then be nice and send a बंद to server.
			 */
			send_msg_बंद(dev, device_id, RTRS_PERMIT_NOWAIT);
		पूर्ण
	पूर्ण
	kमुक्त(rsp);
	wake_up_iu_comp(iu, त्रुटि_सं);
	rnbd_put_iu(dev->sess, iu);
	rnbd_clt_put_dev(dev);
पूर्ण

अटल व्योम msg_sess_info_conf(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rnbd_iu *iu = container_of(work, काष्ठा rnbd_iu, work);
	काष्ठा rnbd_msg_sess_info_rsp *rsp = iu->buf;
	काष्ठा rnbd_clt_session *sess = iu->sess;

	अगर (!iu->त्रुटि_सं)
		sess->ver = min_t(u8, rsp->ver, RNBD_PROTO_VER_MAJOR);

	kमुक्त(rsp);
	wake_up_iu_comp(iu, iu->त्रुटि_सं);
	rnbd_put_iu(sess, iu);
	rnbd_clt_put_sess(sess);
पूर्ण

अटल पूर्णांक send_msg_खोलो(काष्ठा rnbd_clt_dev *dev, क्रमागत रुको_type रुको)
अणु
	काष्ठा rnbd_clt_session *sess = dev->sess;
	काष्ठा rnbd_msg_खोलो_rsp *rsp;
	काष्ठा rnbd_msg_खोलो msg;
	काष्ठा rnbd_iu *iu;
	काष्ठा kvec vec = अणु
		.iov_base = &msg,
		.iov_len  = माप(msg)
	पूर्ण;
	पूर्णांक err, त्रुटि_सं;

	rsp = kzalloc(माप(*rsp), GFP_KERNEL);
	अगर (!rsp)
		वापस -ENOMEM;

	iu = rnbd_get_iu(sess, RTRS_ADMIN_CON, RTRS_PERMIT_WAIT);
	अगर (!iu) अणु
		kमुक्त(rsp);
		वापस -ENOMEM;
	पूर्ण

	iu->buf = rsp;
	iu->dev = dev;

	sg_init_one(iu->sgt.sgl, rsp, माप(*rsp));

	msg.hdr.type	= cpu_to_le16(RNBD_MSG_OPEN);
	msg.access_mode	= dev->access_mode;
	strscpy(msg.dev_name, dev->pathname, माप(msg.dev_name));

	WARN_ON(!rnbd_clt_get_dev(dev));
	err = send_usr_msg(sess->rtrs, READ, iu,
			   &vec, माप(*rsp), iu->sgt.sgl, 1,
			   msg_खोलो_conf, &त्रुटि_सं, रुको);
	अगर (err) अणु
		rnbd_clt_put_dev(dev);
		rnbd_put_iu(sess, iu);
		kमुक्त(rsp);
	पूर्ण अन्यथा अणु
		err = त्रुटि_सं;
	पूर्ण

	rnbd_put_iu(sess, iu);
	वापस err;
पूर्ण

अटल पूर्णांक send_msg_sess_info(काष्ठा rnbd_clt_session *sess, क्रमागत रुको_type रुको)
अणु
	काष्ठा rnbd_msg_sess_info_rsp *rsp;
	काष्ठा rnbd_msg_sess_info msg;
	काष्ठा rnbd_iu *iu;
	काष्ठा kvec vec = अणु
		.iov_base = &msg,
		.iov_len  = माप(msg)
	पूर्ण;
	पूर्णांक err, त्रुटि_सं;

	rsp = kzalloc(माप(*rsp), GFP_KERNEL);
	अगर (!rsp)
		वापस -ENOMEM;

	iu = rnbd_get_iu(sess, RTRS_ADMIN_CON, RTRS_PERMIT_WAIT);
	अगर (!iu) अणु
		kमुक्त(rsp);
		वापस -ENOMEM;
	पूर्ण

	iu->buf = rsp;
	iu->sess = sess;
	sg_init_one(iu->sgt.sgl, rsp, माप(*rsp));

	msg.hdr.type = cpu_to_le16(RNBD_MSG_SESS_INFO);
	msg.ver      = RNBD_PROTO_VER_MAJOR;

	अगर (!rnbd_clt_get_sess(sess)) अणु
		/*
		 * That can happen only in one हाल, when RTRS has restablished
		 * the connection and link_ev() is called, but session is almost
		 * dead, last reference on session is put and caller is रुकोing
		 * क्रम RTRS to बंद everything.
		 */
		err = -ENODEV;
		जाओ put_iu;
	पूर्ण
	err = send_usr_msg(sess->rtrs, READ, iu,
			   &vec, माप(*rsp), iu->sgt.sgl, 1,
			   msg_sess_info_conf, &त्रुटि_सं, रुको);
	अगर (err) अणु
		rnbd_clt_put_sess(sess);
put_iu:
		rnbd_put_iu(sess, iu);
		kमुक्त(rsp);
	पूर्ण अन्यथा अणु
		err = त्रुटि_सं;
	पूर्ण
	rnbd_put_iu(sess, iu);
	वापस err;
पूर्ण

अटल व्योम set_dev_states_to_disconnected(काष्ठा rnbd_clt_session *sess)
अणु
	काष्ठा rnbd_clt_dev *dev;
	काष्ठा kobject *gd_kobj;

	mutex_lock(&sess->lock);
	list_क्रम_each_entry(dev, &sess->devs_list, list) अणु
		rnbd_clt_err(dev, "Device disconnected.\n");

		mutex_lock(&dev->lock);
		अगर (dev->dev_state == DEV_STATE_MAPPED) अणु
			dev->dev_state = DEV_STATE_MAPPED_DISCONNECTED;
			gd_kobj = &disk_to_dev(dev->gd)->kobj;
			kobject_uevent(gd_kobj, KOBJ_OFFLINE);
		पूर्ण
		mutex_unlock(&dev->lock);
	पूर्ण
	mutex_unlock(&sess->lock);
पूर्ण

अटल व्योम remap_devs(काष्ठा rnbd_clt_session *sess)
अणु
	काष्ठा rnbd_clt_dev *dev;
	काष्ठा rtrs_attrs attrs;
	पूर्णांक err;

	/*
	 * Careful here: we are called from RTRS link event directly,
	 * thus we can't send any RTRS request and रुको क्रम response
	 * or RTRS will not be able to complete request with failure
	 * अगर something goes wrong (failing of outstanding requests
	 * happens exactly from the context where we are blocking now).
	 *
	 * So to aव्योम deadlocks each usr message sent from here must
	 * be asynchronous.
	 */

	err = send_msg_sess_info(sess, RTRS_PERMIT_NOWAIT);
	अगर (err) अणु
		pr_err("send_msg_sess_info(\"%s\"): %d\n", sess->sessname, err);
		वापस;
	पूर्ण

	err = rtrs_clt_query(sess->rtrs, &attrs);
	अगर (err) अणु
		pr_err("rtrs_clt_query(\"%s\"): %d\n", sess->sessname, err);
		वापस;
	पूर्ण
	mutex_lock(&sess->lock);
	sess->max_io_size = attrs.max_io_size;

	list_क्रम_each_entry(dev, &sess->devs_list, list) अणु
		bool skip;

		mutex_lock(&dev->lock);
		skip = (dev->dev_state == DEV_STATE_INIT);
		mutex_unlock(&dev->lock);
		अगर (skip)
			/*
			 * When device is establishing connection क्रम the first
			 * समय - करो not remap, it will be बंदd soon.
			 */
			जारी;

		rnbd_clt_info(dev, "session reconnected, remapping device\n");
		err = send_msg_खोलो(dev, RTRS_PERMIT_NOWAIT);
		अगर (err) अणु
			rnbd_clt_err(dev, "send_msg_open(): %d\n", err);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&sess->lock);
पूर्ण

अटल व्योम rnbd_clt_link_ev(व्योम *priv, क्रमागत rtrs_clt_link_ev ev)
अणु
	काष्ठा rnbd_clt_session *sess = priv;

	चयन (ev) अणु
	हाल RTRS_CLT_LINK_EV_DISCONNECTED:
		set_dev_states_to_disconnected(sess);
		अवरोध;
	हाल RTRS_CLT_LINK_EV_RECONNECTED:
		remap_devs(sess);
		अवरोध;
	शेष:
		pr_err("Unknown session event received (%d), session: %s\n",
		       ev, sess->sessname);
	पूर्ण
पूर्ण

अटल व्योम rnbd_init_cpu_qlists(काष्ठा rnbd_cpu_qlist __percpu *cpu_queues)
अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा rnbd_cpu_qlist *cpu_q;

	क्रम_each_possible_cpu(cpu) अणु
		cpu_q = per_cpu_ptr(cpu_queues, cpu);

		cpu_q->cpu = cpu;
		INIT_LIST_HEAD(&cpu_q->requeue_list);
		spin_lock_init(&cpu_q->requeue_lock);
	पूर्ण
पूर्ण

अटल व्योम destroy_mq_tags(काष्ठा rnbd_clt_session *sess)
अणु
	अगर (sess->tag_set.tags)
		blk_mq_मुक्त_tag_set(&sess->tag_set);
पूर्ण

अटल अंतरभूत व्योम wake_up_rtrs_रुकोers(काष्ठा rnbd_clt_session *sess)
अणु
	sess->rtrs_पढ़ोy = true;
	wake_up_all(&sess->rtrs_रुकोq);
पूर्ण

अटल व्योम बंद_rtrs(काष्ठा rnbd_clt_session *sess)
अणु
	might_sleep();

	अगर (!IS_ERR_OR_शून्य(sess->rtrs)) अणु
		rtrs_clt_बंद(sess->rtrs);
		sess->rtrs = शून्य;
		wake_up_rtrs_रुकोers(sess);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_sess(काष्ठा rnbd_clt_session *sess)
अणु
	WARN_ON(!list_empty(&sess->devs_list));

	might_sleep();

	बंद_rtrs(sess);
	destroy_mq_tags(sess);
	अगर (!list_empty(&sess->list)) अणु
		mutex_lock(&sess_lock);
		list_del(&sess->list);
		mutex_unlock(&sess_lock);
	पूर्ण
	मुक्त_percpu(sess->cpu_queues);
	मुक्त_percpu(sess->cpu_rr);
	mutex_destroy(&sess->lock);
	kमुक्त(sess);
पूर्ण

अटल काष्ठा rnbd_clt_session *alloc_sess(स्थिर अक्षर *sessname)
अणु
	काष्ठा rnbd_clt_session *sess;
	पूर्णांक err, cpu;

	sess = kzalloc_node(माप(*sess), GFP_KERNEL, NUMA_NO_NODE);
	अगर (!sess)
		वापस ERR_PTR(-ENOMEM);
	strscpy(sess->sessname, sessname, माप(sess->sessname));
	atomic_set(&sess->busy, 0);
	mutex_init(&sess->lock);
	INIT_LIST_HEAD(&sess->devs_list);
	INIT_LIST_HEAD(&sess->list);
	biपंचांगap_zero(sess->cpu_queues_bm, num_possible_cpus());
	init_रुकोqueue_head(&sess->rtrs_रुकोq);
	refcount_set(&sess->refcount, 1);

	sess->cpu_queues = alloc_percpu(काष्ठा rnbd_cpu_qlist);
	अगर (!sess->cpu_queues) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण
	rnbd_init_cpu_qlists(sess->cpu_queues);

	/*
	 * That is simple percpu variable which stores cpu indices, which are
	 * incremented on each access.  We need that क्रम the sake of fairness
	 * to wake up queues in a round-robin manner.
	 */
	sess->cpu_rr = alloc_percpu(पूर्णांक);
	अगर (!sess->cpu_rr) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण
	क्रम_each_possible_cpu(cpu)
		* per_cpu_ptr(sess->cpu_rr, cpu) = cpu;

	वापस sess;

err:
	मुक्त_sess(sess);

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक रुको_क्रम_rtrs_connection(काष्ठा rnbd_clt_session *sess)
अणु
	रुको_event(sess->rtrs_रुकोq, sess->rtrs_पढ़ोy);
	अगर (IS_ERR_OR_शून्य(sess->rtrs))
		वापस -ECONNRESET;

	वापस 0;
पूर्ण

अटल व्योम रुको_क्रम_rtrs_disconnection(काष्ठा rnbd_clt_session *sess)
	__releases(&sess_lock)
	__acquires(&sess_lock)
अणु
	DEFINE_WAIT(रुको);

	prepare_to_रुको(&sess->rtrs_रुकोq, &रुको, TASK_UNINTERRUPTIBLE);
	अगर (IS_ERR_OR_शून्य(sess->rtrs)) अणु
		finish_रुको(&sess->rtrs_रुकोq, &रुको);
		वापस;
	पूर्ण
	mutex_unlock(&sess_lock);
	/* loop in caller, see __find_and_get_sess().
	 * You can't leave mutex locked and call schedule(), you will catch a
	 * deadlock with a caller of मुक्त_sess(), which has just put the last
	 * reference and is about to take the sess_lock in order to delete
	 * the session from the list.
	 */
	schedule();
	mutex_lock(&sess_lock);
पूर्ण

अटल काष्ठा rnbd_clt_session *__find_and_get_sess(स्थिर अक्षर *sessname)
	__releases(&sess_lock)
	__acquires(&sess_lock)
अणु
	काष्ठा rnbd_clt_session *sess, *sn;
	पूर्णांक err;

again:
	list_क्रम_each_entry_safe(sess, sn, &sess_list, list) अणु
		अगर (म_भेद(sessname, sess->sessname))
			जारी;

		अगर (sess->rtrs_पढ़ोy && IS_ERR_OR_शून्य(sess->rtrs))
			/*
			 * No RTRS connection, session is dying.
			 */
			जारी;

		अगर (rnbd_clt_get_sess(sess)) अणु
			/*
			 * Alive session is found, रुको क्रम RTRS connection.
			 */
			mutex_unlock(&sess_lock);
			err = रुको_क्रम_rtrs_connection(sess);
			अगर (err)
				rnbd_clt_put_sess(sess);
			mutex_lock(&sess_lock);

			अगर (err)
				/* Session is dying, repeat the loop */
				जाओ again;

			वापस sess;
		पूर्ण
		/*
		 * Ref is 0, session is dying, रुको क्रम RTRS disconnect
		 * in order to aव्योम session names clashes.
		 */
		रुको_क्रम_rtrs_disconnection(sess);
		/*
		 * RTRS is disconnected and soon session will be मुक्तd,
		 * so repeat a loop.
		 */
		जाओ again;
	पूर्ण

	वापस शून्य;
पूर्ण

/* caller is responsible क्रम initializing 'first' to false */
अटल काष्ठा
rnbd_clt_session *find_or_create_sess(स्थिर अक्षर *sessname, bool *first)
अणु
	काष्ठा rnbd_clt_session *sess = शून्य;

	mutex_lock(&sess_lock);
	sess = __find_and_get_sess(sessname);
	अगर (!sess) अणु
		sess = alloc_sess(sessname);
		अगर (IS_ERR(sess)) अणु
			mutex_unlock(&sess_lock);
			वापस sess;
		पूर्ण
		list_add(&sess->list, &sess_list);
		*first = true;
	पूर्ण
	mutex_unlock(&sess_lock);

	वापस sess;
पूर्ण

अटल पूर्णांक rnbd_client_खोलो(काष्ठा block_device *block_device, भ_शेषe_t mode)
अणु
	काष्ठा rnbd_clt_dev *dev = block_device->bd_disk->निजी_data;

	अगर (dev->पढ़ो_only && (mode & FMODE_WRITE))
		वापस -EPERM;

	अगर (dev->dev_state == DEV_STATE_UNMAPPED ||
	    !rnbd_clt_get_dev(dev))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम rnbd_client_release(काष्ठा gendisk *gen, भ_शेषe_t mode)
अणु
	काष्ठा rnbd_clt_dev *dev = gen->निजी_data;

	rnbd_clt_put_dev(dev);
पूर्ण

अटल पूर्णांक rnbd_client_getgeo(काष्ठा block_device *block_device,
			      काष्ठा hd_geometry *geo)
अणु
	u64 size;
	काष्ठा rnbd_clt_dev *dev;

	dev = block_device->bd_disk->निजी_data;
	size = dev->size * (dev->logical_block_size / SECTOR_SIZE);
	geo->cylinders	= size >> 6;	/* size/64 */
	geo->heads	= 4;
	geo->sectors	= 16;
	geo->start	= 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations rnbd_client_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= rnbd_client_खोलो,
	.release	= rnbd_client_release,
	.getgeo		= rnbd_client_getgeo
पूर्ण;

/* The amount of data that beदीर्घs to an I/O and the amount of data that
 * should be पढ़ो or written to the disk (bi_size) can dअगरfer.
 *
 * E.g. When WRITE_SAME is used, only a small amount of data is
 * transferred that is then written repeatedly over a lot of sectors.
 *
 * Get the size of data to be transferred via RTRS by summing up the size
 * of the scather-gather list entries.
 */
अटल माप_प्रकार rnbd_clt_get_sg_size(काष्ठा scatterlist *sglist, u32 len)
अणु
	काष्ठा scatterlist *sg;
	माप_प्रकार tsize = 0;
	पूर्णांक i;

	क्रम_each_sg(sglist, sg, len, i)
		tsize += sg->length;
	वापस tsize;
पूर्ण

अटल पूर्णांक rnbd_client_xfer_request(काष्ठा rnbd_clt_dev *dev,
				     काष्ठा request *rq,
				     काष्ठा rnbd_iu *iu)
अणु
	काष्ठा rtrs_clt *rtrs = dev->sess->rtrs;
	काष्ठा rtrs_permit *permit = iu->permit;
	काष्ठा rnbd_msg_io msg;
	काष्ठा rtrs_clt_req_ops req_ops;
	अचिन्हित पूर्णांक sg_cnt = 0;
	काष्ठा kvec vec;
	माप_प्रकार size;
	पूर्णांक err;

	iu->rq		= rq;
	iu->dev		= dev;
	msg.sector	= cpu_to_le64(blk_rq_pos(rq));
	msg.bi_size	= cpu_to_le32(blk_rq_bytes(rq));
	msg.rw		= cpu_to_le32(rq_to_rnbd_flags(rq));
	msg.prio	= cpu_to_le16(req_get_ioprio(rq));

	/*
	 * We only support discards with single segment क्रम now.
	 * See queue limits.
	 */
	अगर (req_op(rq) != REQ_OP_DISCARD)
		sg_cnt = blk_rq_map_sg(dev->queue, rq, iu->sgt.sgl);

	अगर (sg_cnt == 0)
		sg_mark_end(&iu->sgt.sgl[0]);

	msg.hdr.type	= cpu_to_le16(RNBD_MSG_IO);
	msg.device_id	= cpu_to_le32(dev->device_id);

	vec = (काष्ठा kvec) अणु
		.iov_base = &msg,
		.iov_len  = माप(msg)
	पूर्ण;
	size = rnbd_clt_get_sg_size(iu->sgt.sgl, sg_cnt);
	req_ops = (काष्ठा rtrs_clt_req_ops) अणु
		.priv = iu,
		.conf_fn = msg_io_conf,
	पूर्ण;
	err = rtrs_clt_request(rq_data_dir(rq), &req_ops, rtrs, permit,
			       &vec, 1, size, iu->sgt.sgl, sg_cnt);
	अगर (err) अणु
		rnbd_clt_err_rl(dev, "RTRS failed to transfer IO, err: %d\n",
				 err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rnbd_clt_dev_add_to_requeue() - add device to requeue अगर session is busy
 * @dev:	Device to be checked
 * @q:		Queue to be added to the requeue list अगर required
 *
 * Description:
 *     If session is busy, that means someone will requeue us when resources
 *     are मुक्तd.  If session is not करोing anything - device is not added to
 *     the list and @false is वापसed.
 */
अटल bool rnbd_clt_dev_add_to_requeue(काष्ठा rnbd_clt_dev *dev,
						काष्ठा rnbd_queue *q)
अणु
	काष्ठा rnbd_clt_session *sess = dev->sess;
	काष्ठा rnbd_cpu_qlist *cpu_q;
	अचिन्हित दीर्घ flags;
	bool added = true;
	bool need_set;

	cpu_q = get_cpu_ptr(sess->cpu_queues);
	spin_lock_irqsave(&cpu_q->requeue_lock, flags);

	अगर (!test_and_set_bit_lock(0, &q->in_list)) अणु
		अगर (WARN_ON(!list_empty(&q->requeue_list)))
			जाओ unlock;

		need_set = !test_bit(cpu_q->cpu, sess->cpu_queues_bm);
		अगर (need_set) अणु
			set_bit(cpu_q->cpu, sess->cpu_queues_bm);
			/* Paired with rnbd_put_permit(). Set a bit first
			 * and then observe the busy counter.
			 */
			smp_mb__beक्रमe_atomic();
		पूर्ण
		अगर (atomic_पढ़ो(&sess->busy)) अणु
			list_add_tail(&q->requeue_list, &cpu_q->requeue_list);
		पूर्ण अन्यथा अणु
			/* Very unlikely, but possible: busy counter was
			 * observed as zero.  Drop all bits and वापस
			 * false to restart the queue by ourselves.
			 */
			अगर (need_set)
				clear_bit(cpu_q->cpu, sess->cpu_queues_bm);
			clear_bit_unlock(0, &q->in_list);
			added = false;
		पूर्ण
	पूर्ण
unlock:
	spin_unlock_irqrestore(&cpu_q->requeue_lock, flags);
	put_cpu_ptr(sess->cpu_queues);

	वापस added;
पूर्ण

अटल व्योम rnbd_clt_dev_kick_mq_queue(काष्ठा rnbd_clt_dev *dev,
					काष्ठा blk_mq_hw_ctx *hctx,
					पूर्णांक delay)
अणु
	काष्ठा rnbd_queue *q = hctx->driver_data;

	अगर (delay != RNBD_DELAY_IFBUSY)
		blk_mq_delay_run_hw_queue(hctx, delay);
	अन्यथा अगर (!rnbd_clt_dev_add_to_requeue(dev, q))
		/*
		 * If session is not busy we have to restart
		 * the queue ourselves.
		 */
		blk_mq_delay_run_hw_queue(hctx, 10/*ms*/);
पूर्ण

अटल blk_status_t rnbd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				   स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *rq = bd->rq;
	काष्ठा rnbd_clt_dev *dev = rq->rq_disk->निजी_data;
	काष्ठा rnbd_iu *iu = blk_mq_rq_to_pdu(rq);
	पूर्णांक err;
	blk_status_t ret = BLK_STS_IOERR;

	अगर (dev->dev_state != DEV_STATE_MAPPED)
		वापस BLK_STS_IOERR;

	iu->permit = rnbd_get_permit(dev->sess, RTRS_IO_CON,
				      RTRS_PERMIT_NOWAIT);
	अगर (!iu->permit) अणु
		rnbd_clt_dev_kick_mq_queue(dev, hctx, RNBD_DELAY_IFBUSY);
		वापस BLK_STS_RESOURCE;
	पूर्ण

	iu->sgt.sgl = iu->first_sgl;
	err = sg_alloc_table_chained(&iu->sgt,
				     /* Even-अगर the request has no segment,
				      * sglist must have one entry at least.
				      */
				     blk_rq_nr_phys_segments(rq) ? : 1,
				     iu->sgt.sgl,
				     RNBD_INLINE_SG_CNT);
	अगर (err) अणु
		rnbd_clt_err_rl(dev, "sg_alloc_table_chained ret=%d\n", err);
		rnbd_clt_dev_kick_mq_queue(dev, hctx, 10/*ms*/);
		rnbd_put_permit(dev->sess, iu->permit);
		वापस BLK_STS_RESOURCE;
	पूर्ण

	blk_mq_start_request(rq);
	err = rnbd_client_xfer_request(dev, rq, iu);
	अगर (err == 0)
		वापस BLK_STS_OK;
	अगर (err == -EAGAIN || err == -ENOMEM) अणु
		rnbd_clt_dev_kick_mq_queue(dev, hctx, 10/*ms*/);
		ret = BLK_STS_RESOURCE;
	पूर्ण
	sg_मुक्त_table_chained(&iu->sgt, RNBD_INLINE_SG_CNT);
	rnbd_put_permit(dev->sess, iu->permit);
	वापस ret;
पूर्ण

अटल पूर्णांक rnbd_rdma_poll(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा rnbd_queue *q = hctx->driver_data;
	काष्ठा rnbd_clt_dev *dev = q->dev;
	पूर्णांक cnt;

	cnt = rtrs_clt_rdma_cq_direct(dev->sess->rtrs, hctx->queue_num);
	वापस cnt;
पूर्ण

अटल पूर्णांक rnbd_rdma_map_queues(काष्ठा blk_mq_tag_set *set)
अणु
	काष्ठा rnbd_clt_session *sess = set->driver_data;

	/* shared पढ़ो/ग_लिखो queues */
	set->map[HCTX_TYPE_DEFAULT].nr_queues = num_online_cpus();
	set->map[HCTX_TYPE_DEFAULT].queue_offset = 0;
	set->map[HCTX_TYPE_READ].nr_queues = num_online_cpus();
	set->map[HCTX_TYPE_READ].queue_offset = 0;
	blk_mq_map_queues(&set->map[HCTX_TYPE_DEFAULT]);
	blk_mq_map_queues(&set->map[HCTX_TYPE_READ]);

	अगर (sess->nr_poll_queues) अणु
		/* dedicated queue क्रम poll */
		set->map[HCTX_TYPE_POLL].nr_queues = sess->nr_poll_queues;
		set->map[HCTX_TYPE_POLL].queue_offset = set->map[HCTX_TYPE_READ].queue_offset +
			set->map[HCTX_TYPE_READ].nr_queues;
		blk_mq_map_queues(&set->map[HCTX_TYPE_POLL]);
		pr_info("[session=%s] mapped %d/%d/%d default/read/poll queues.\n",
			sess->sessname,
			set->map[HCTX_TYPE_DEFAULT].nr_queues,
			set->map[HCTX_TYPE_READ].nr_queues,
			set->map[HCTX_TYPE_POLL].nr_queues);
	पूर्ण अन्यथा अणु
		pr_info("[session=%s] mapped %d/%d default/read queues.\n",
			sess->sessname,
			set->map[HCTX_TYPE_DEFAULT].nr_queues,
			set->map[HCTX_TYPE_READ].nr_queues);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा blk_mq_ops rnbd_mq_ops = अणु
	.queue_rq	= rnbd_queue_rq,
	.complete	= rnbd_softirq_करोne_fn,
	.map_queues     = rnbd_rdma_map_queues,
	.poll           = rnbd_rdma_poll,
पूर्ण;

अटल पूर्णांक setup_mq_tags(काष्ठा rnbd_clt_session *sess)
अणु
	काष्ठा blk_mq_tag_set *tag_set = &sess->tag_set;

	स_रखो(tag_set, 0, माप(*tag_set));
	tag_set->ops		= &rnbd_mq_ops;
	tag_set->queue_depth	= sess->queue_depth;
	tag_set->numa_node		= NUMA_NO_NODE;
	tag_set->flags		= BLK_MQ_F_SHOULD_MERGE |
				  BLK_MQ_F_TAG_QUEUE_SHARED;
	tag_set->cmd_size	= माप(काष्ठा rnbd_iu) + RNBD_RDMA_SGL_SIZE;

	/* क्रम HCTX_TYPE_DEFAULT, HCTX_TYPE_READ, HCTX_TYPE_POLL */
	tag_set->nr_maps        = sess->nr_poll_queues ? HCTX_MAX_TYPES : 2;
	/*
	 * HCTX_TYPE_DEFAULT and HCTX_TYPE_READ share one set of queues
	 * others are क्रम HCTX_TYPE_POLL
	 */
	tag_set->nr_hw_queues	= num_online_cpus() + sess->nr_poll_queues;
	tag_set->driver_data    = sess;

	वापस blk_mq_alloc_tag_set(tag_set);
पूर्ण

अटल काष्ठा rnbd_clt_session *
find_and_get_or_create_sess(स्थिर अक्षर *sessname,
			    स्थिर काष्ठा rtrs_addr *paths,
			    माप_प्रकार path_cnt, u16 port_nr, u32 nr_poll_queues)
अणु
	काष्ठा rnbd_clt_session *sess;
	काष्ठा rtrs_attrs attrs;
	पूर्णांक err;
	bool first = false;
	काष्ठा rtrs_clt_ops rtrs_ops;

	sess = find_or_create_sess(sessname, &first);
	अगर (sess == ERR_PTR(-ENOMEM))
		वापस ERR_PTR(-ENOMEM);
	अन्यथा अगर ((nr_poll_queues && !first) ||  (!nr_poll_queues && sess->nr_poll_queues)) अणु
		/*
		 * A device MUST have its own session to use the polling-mode.
		 * It must fail to map new device with the same session.
		 */
		err = -EINVAL;
		जाओ put_sess;
	पूर्ण

	अगर (!first)
		वापस sess;

	अगर (!path_cnt) अणु
		pr_err("Session %s not found, and path parameter not given", sessname);
		err = -ENXIO;
		जाओ put_sess;
	पूर्ण

	rtrs_ops = (काष्ठा rtrs_clt_ops) अणु
		.priv = sess,
		.link_ev = rnbd_clt_link_ev,
	पूर्ण;
	/*
	 * Nothing was found, establish rtrs connection and proceed further.
	 */
	sess->rtrs = rtrs_clt_खोलो(&rtrs_ops, sessname,
				   paths, path_cnt, port_nr,
				   0, /* Do not use pdu of rtrs */
				   RECONNECT_DELAY, BMAX_SEGMENTS,
				   MAX_RECONNECTS, nr_poll_queues);
	अगर (IS_ERR(sess->rtrs)) अणु
		err = PTR_ERR(sess->rtrs);
		जाओ wake_up_and_put;
	पूर्ण

	err = rtrs_clt_query(sess->rtrs, &attrs);
	अगर (err)
		जाओ बंद_rtrs;

	sess->max_io_size = attrs.max_io_size;
	sess->queue_depth = attrs.queue_depth;
	sess->nr_poll_queues = nr_poll_queues;

	err = setup_mq_tags(sess);
	अगर (err)
		जाओ बंद_rtrs;

	err = send_msg_sess_info(sess, RTRS_PERMIT_WAIT);
	अगर (err)
		जाओ बंद_rtrs;

	wake_up_rtrs_रुकोers(sess);

	वापस sess;

बंद_rtrs:
	बंद_rtrs(sess);
put_sess:
	rnbd_clt_put_sess(sess);

	वापस ERR_PTR(err);

wake_up_and_put:
	wake_up_rtrs_रुकोers(sess);
	जाओ put_sess;
पूर्ण

अटल अंतरभूत व्योम rnbd_init_hw_queue(काष्ठा rnbd_clt_dev *dev,
				       काष्ठा rnbd_queue *q,
				       काष्ठा blk_mq_hw_ctx *hctx)
अणु
	INIT_LIST_HEAD(&q->requeue_list);
	q->dev  = dev;
	q->hctx = hctx;
पूर्ण

अटल व्योम rnbd_init_mq_hw_queues(काष्ठा rnbd_clt_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा rnbd_queue *q;

	queue_क्रम_each_hw_ctx(dev->queue, hctx, i) अणु
		q = &dev->hw_queues[i];
		rnbd_init_hw_queue(dev, q, hctx);
		hctx->driver_data = q;
	पूर्ण
पूर्ण

अटल पूर्णांक setup_mq_dev(काष्ठा rnbd_clt_dev *dev)
अणु
	dev->queue = blk_mq_init_queue(&dev->sess->tag_set);
	अगर (IS_ERR(dev->queue)) अणु
		rnbd_clt_err(dev, "Initializing multiqueue queue failed, err: %ld\n",
			      PTR_ERR(dev->queue));
		वापस PTR_ERR(dev->queue);
	पूर्ण
	rnbd_init_mq_hw_queues(dev);
	वापस 0;
पूर्ण

अटल व्योम setup_request_queue(काष्ठा rnbd_clt_dev *dev)
अणु
	blk_queue_logical_block_size(dev->queue, dev->logical_block_size);
	blk_queue_physical_block_size(dev->queue, dev->physical_block_size);
	blk_queue_max_hw_sectors(dev->queue, dev->max_hw_sectors);
	blk_queue_max_ग_लिखो_same_sectors(dev->queue,
					 dev->max_ग_लिखो_same_sectors);

	/*
	 * we करोn't support discards to "discontiguous" segments
	 * in on request
	 */
	blk_queue_max_discard_segments(dev->queue, 1);

	blk_queue_max_discard_sectors(dev->queue, dev->max_discard_sectors);
	dev->queue->limits.discard_granularity	= dev->discard_granularity;
	dev->queue->limits.discard_alignment	= dev->discard_alignment;
	अगर (dev->max_discard_sectors)
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, dev->queue);
	अगर (dev->secure_discard)
		blk_queue_flag_set(QUEUE_FLAG_SECERASE, dev->queue);

	blk_queue_flag_set(QUEUE_FLAG_SAME_COMP, dev->queue);
	blk_queue_flag_set(QUEUE_FLAG_SAME_FORCE, dev->queue);
	blk_queue_max_segments(dev->queue, dev->max_segments);
	blk_queue_io_opt(dev->queue, dev->sess->max_io_size);
	blk_queue_virt_boundary(dev->queue, SZ_4K - 1);
	blk_queue_ग_लिखो_cache(dev->queue, dev->wc, dev->fua);
	dev->queue->queuedata = dev;
पूर्ण

अटल व्योम rnbd_clt_setup_gen_disk(काष्ठा rnbd_clt_dev *dev, पूर्णांक idx)
अणु
	dev->gd->major		= rnbd_client_major;
	dev->gd->first_minor	= idx << RNBD_PART_BITS;
	dev->gd->fops		= &rnbd_client_ops;
	dev->gd->queue		= dev->queue;
	dev->gd->निजी_data	= dev;
	snम_लिखो(dev->gd->disk_name, माप(dev->gd->disk_name), "rnbd%d",
		 idx);
	pr_debug("disk_name=%s, capacity=%zu\n",
		 dev->gd->disk_name,
		 dev->nsectors * (dev->logical_block_size / SECTOR_SIZE)
		 );

	set_capacity(dev->gd, dev->nsectors);

	अगर (dev->access_mode == RNBD_ACCESS_RO) अणु
		dev->पढ़ो_only = true;
		set_disk_ro(dev->gd, true);
	पूर्ण अन्यथा अणु
		dev->पढ़ो_only = false;
	पूर्ण

	अगर (!dev->rotational)
		blk_queue_flag_set(QUEUE_FLAG_NONROT, dev->queue);
	add_disk(dev->gd);
पूर्ण

अटल पूर्णांक rnbd_client_setup_device(काष्ठा rnbd_clt_dev *dev)
अणु
	पूर्णांक err, idx = dev->clt_device_id;

	dev->size = dev->nsectors * dev->logical_block_size;

	err = setup_mq_dev(dev);
	अगर (err)
		वापस err;

	setup_request_queue(dev);

	dev->gd = alloc_disk_node(1 << RNBD_PART_BITS,	NUMA_NO_NODE);
	अगर (!dev->gd) अणु
		blk_cleanup_queue(dev->queue);
		वापस -ENOMEM;
	पूर्ण

	rnbd_clt_setup_gen_disk(dev, idx);

	वापस 0;
पूर्ण

अटल काष्ठा rnbd_clt_dev *init_dev(काष्ठा rnbd_clt_session *sess,
				      क्रमागत rnbd_access_mode access_mode,
				      स्थिर अक्षर *pathname,
				      u32 nr_poll_queues)
अणु
	काष्ठा rnbd_clt_dev *dev;
	पूर्णांक ret;

	dev = kzalloc_node(माप(*dev), GFP_KERNEL, NUMA_NO_NODE);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * nr_cpu_ids: the number of softirq queues
	 * nr_poll_queues: the number of polling queues
	 */
	dev->hw_queues = kसुस्मृति(nr_cpu_ids + nr_poll_queues,
				 माप(*dev->hw_queues),
				 GFP_KERNEL);
	अगर (!dev->hw_queues) अणु
		ret = -ENOMEM;
		जाओ out_alloc;
	पूर्ण

	mutex_lock(&ida_lock);
	ret = ida_simple_get(&index_ida, 0, 1 << (MINORBITS - RNBD_PART_BITS),
			     GFP_KERNEL);
	mutex_unlock(&ida_lock);
	अगर (ret < 0) अणु
		pr_err("Failed to initialize device '%s' from session %s, allocating idr failed, err: %d\n",
		       pathname, sess->sessname, ret);
		जाओ out_queues;
	पूर्ण

	dev->pathname = kstrdup(pathname, GFP_KERNEL);
	अगर (!dev->pathname) अणु
		ret = -ENOMEM;
		जाओ out_queues;
	पूर्ण

	dev->clt_device_id	= ret;
	dev->sess		= sess;
	dev->access_mode	= access_mode;
	dev->nr_poll_queues	= nr_poll_queues;
	mutex_init(&dev->lock);
	refcount_set(&dev->refcount, 1);
	dev->dev_state = DEV_STATE_INIT;

	/*
	 * Here we called from sysfs entry, thus clt-sysfs is
	 * responsible that session will not disappear.
	 */
	WARN_ON(!rnbd_clt_get_sess(sess));

	वापस dev;

out_queues:
	kमुक्त(dev->hw_queues);
out_alloc:
	kमुक्त(dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल bool __exists_dev(स्थिर अक्षर *pathname, स्थिर अक्षर *sessname)
अणु
	काष्ठा rnbd_clt_session *sess;
	काष्ठा rnbd_clt_dev *dev;
	bool found = false;

	list_क्रम_each_entry(sess, &sess_list, list) अणु
		अगर (sessname && म_भेदन(sess->sessname, sessname,
					माप(sess->sessname)))
			जारी;
		mutex_lock(&sess->lock);
		list_क्रम_each_entry(dev, &sess->devs_list, list) अणु
			अगर (म_माप(dev->pathname) == म_माप(pathname) &&
			    !म_भेद(dev->pathname, pathname)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&sess->lock);
		अगर (found)
			अवरोध;
	पूर्ण

	वापस found;
पूर्ण

अटल bool exists_devpath(स्थिर अक्षर *pathname, स्थिर अक्षर *sessname)
अणु
	bool found;

	mutex_lock(&sess_lock);
	found = __exists_dev(pathname, sessname);
	mutex_unlock(&sess_lock);

	वापस found;
पूर्ण

अटल bool insert_dev_अगर_not_exists_devpath(काष्ठा rnbd_clt_dev *dev)
अणु
	bool found;
	काष्ठा rnbd_clt_session *sess = dev->sess;

	mutex_lock(&sess_lock);
	found = __exists_dev(dev->pathname, sess->sessname);
	अगर (!found) अणु
		mutex_lock(&sess->lock);
		list_add_tail(&dev->list, &sess->devs_list);
		mutex_unlock(&sess->lock);
	पूर्ण
	mutex_unlock(&sess_lock);

	वापस found;
पूर्ण

अटल व्योम delete_dev(काष्ठा rnbd_clt_dev *dev)
अणु
	काष्ठा rnbd_clt_session *sess = dev->sess;

	mutex_lock(&sess->lock);
	list_del(&dev->list);
	mutex_unlock(&sess->lock);
पूर्ण

काष्ठा rnbd_clt_dev *rnbd_clt_map_device(स्थिर अक्षर *sessname,
					   काष्ठा rtrs_addr *paths,
					   माप_प्रकार path_cnt, u16 port_nr,
					   स्थिर अक्षर *pathname,
					   क्रमागत rnbd_access_mode access_mode,
					   u32 nr_poll_queues)
अणु
	काष्ठा rnbd_clt_session *sess;
	काष्ठा rnbd_clt_dev *dev;
	पूर्णांक ret;

	अगर (exists_devpath(pathname, sessname))
		वापस ERR_PTR(-EEXIST);

	sess = find_and_get_or_create_sess(sessname, paths, path_cnt, port_nr, nr_poll_queues);
	अगर (IS_ERR(sess))
		वापस ERR_CAST(sess);

	dev = init_dev(sess, access_mode, pathname, nr_poll_queues);
	अगर (IS_ERR(dev)) अणु
		pr_err("map_device: failed to map device '%s' from session %s, can't initialize device, err: %ld\n",
		       pathname, sess->sessname, PTR_ERR(dev));
		ret = PTR_ERR(dev);
		जाओ put_sess;
	पूर्ण
	अगर (insert_dev_अगर_not_exists_devpath(dev)) अणु
		ret = -EEXIST;
		जाओ put_dev;
	पूर्ण
	ret = send_msg_खोलो(dev, RTRS_PERMIT_WAIT);
	अगर (ret) अणु
		rnbd_clt_err(dev,
			      "map_device: failed, can't open remote device, err: %d\n",
			      ret);
		जाओ del_dev;
	पूर्ण
	mutex_lock(&dev->lock);
	pr_debug("Opened remote device: session=%s, path='%s'\n",
		 sess->sessname, pathname);
	ret = rnbd_client_setup_device(dev);
	अगर (ret) अणु
		rnbd_clt_err(dev,
			      "map_device: Failed to configure device, err: %d\n",
			      ret);
		mutex_unlock(&dev->lock);
		जाओ send_बंद;
	पूर्ण

	rnbd_clt_info(dev,
		       "map_device: Device mapped as %s (nsectors: %zu, logical_block_size: %d, physical_block_size: %d, max_write_same_sectors: %d, max_discard_sectors: %d, discard_granularity: %d, discard_alignment: %d, secure_discard: %d, max_segments: %d, max_hw_sectors: %d, rotational: %d, wc: %d, fua: %d)\n",
		       dev->gd->disk_name, dev->nsectors,
		       dev->logical_block_size, dev->physical_block_size,
		       dev->max_ग_लिखो_same_sectors, dev->max_discard_sectors,
		       dev->discard_granularity, dev->discard_alignment,
		       dev->secure_discard, dev->max_segments,
		       dev->max_hw_sectors, dev->rotational, dev->wc, dev->fua);

	mutex_unlock(&dev->lock);
	rnbd_clt_put_sess(sess);

	वापस dev;

send_बंद:
	send_msg_बंद(dev, dev->device_id, RTRS_PERMIT_WAIT);
del_dev:
	delete_dev(dev);
put_dev:
	rnbd_clt_put_dev(dev);
put_sess:
	rnbd_clt_put_sess(sess);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम destroy_gen_disk(काष्ठा rnbd_clt_dev *dev)
अणु
	del_gendisk(dev->gd);
	blk_cleanup_queue(dev->queue);
	put_disk(dev->gd);
पूर्ण

अटल व्योम destroy_sysfs(काष्ठा rnbd_clt_dev *dev,
			  स्थिर काष्ठा attribute *sysfs_self)
अणु
	rnbd_clt_हटाओ_dev_symlink(dev);
	अगर (dev->kobj.state_initialized) अणु
		अगर (sysfs_self)
			/* To aव्योम deadlock firstly हटाओ itself */
			sysfs_हटाओ_file_self(&dev->kobj, sysfs_self);
		kobject_del(&dev->kobj);
		kobject_put(&dev->kobj);
	पूर्ण
पूर्ण

पूर्णांक rnbd_clt_unmap_device(काष्ठा rnbd_clt_dev *dev, bool क्रमce,
			   स्थिर काष्ठा attribute *sysfs_self)
अणु
	काष्ठा rnbd_clt_session *sess = dev->sess;
	पूर्णांक refcount, ret = 0;
	bool was_mapped;

	mutex_lock(&dev->lock);
	अगर (dev->dev_state == DEV_STATE_UNMAPPED) अणु
		rnbd_clt_info(dev, "Device is already being unmapped\n");
		ret = -EALREADY;
		जाओ err;
	पूर्ण
	refcount = refcount_पढ़ो(&dev->refcount);
	अगर (!क्रमce && refcount > 1) अणु
		rnbd_clt_err(dev,
			      "Closing device failed, device is in use, (%d device users)\n",
			      refcount - 1);
		ret = -EBUSY;
		जाओ err;
	पूर्ण
	was_mapped = (dev->dev_state == DEV_STATE_MAPPED);
	dev->dev_state = DEV_STATE_UNMAPPED;
	mutex_unlock(&dev->lock);

	delete_dev(dev);
	destroy_sysfs(dev, sysfs_self);
	destroy_gen_disk(dev);
	अगर (was_mapped && sess->rtrs)
		send_msg_बंद(dev, dev->device_id, RTRS_PERMIT_WAIT);

	rnbd_clt_info(dev, "Device is unmapped\n");

	/* Likely last reference put */
	rnbd_clt_put_dev(dev);

	/*
	 * Here device and session can be vanished!
	 */

	वापस 0;
err:
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

पूर्णांक rnbd_clt_remap_device(काष्ठा rnbd_clt_dev *dev)
अणु
	पूर्णांक err;

	mutex_lock(&dev->lock);
	अगर (dev->dev_state == DEV_STATE_MAPPED_DISCONNECTED)
		err = 0;
	अन्यथा अगर (dev->dev_state == DEV_STATE_UNMAPPED)
		err = -ENODEV;
	अन्यथा अगर (dev->dev_state == DEV_STATE_MAPPED)
		err = -EALREADY;
	अन्यथा
		err = -EBUSY;
	mutex_unlock(&dev->lock);
	अगर (!err) अणु
		rnbd_clt_info(dev, "Remapping device.\n");
		err = send_msg_खोलो(dev, RTRS_PERMIT_WAIT);
		अगर (err)
			rnbd_clt_err(dev, "remap_device: %d\n", err);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम unmap_device_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rnbd_clt_dev *dev;

	dev = container_of(work, typeof(*dev), unmap_on_rmmod_work);
	rnbd_clt_unmap_device(dev, true, शून्य);
पूर्ण

अटल व्योम rnbd_destroy_sessions(व्योम)
अणु
	काष्ठा rnbd_clt_session *sess, *sn;
	काष्ठा rnbd_clt_dev *dev, *tn;

	/* Firstly क्रमbid access through sysfs पूर्णांकerface */
	rnbd_clt_destroy_sysfs_files();

	/*
	 * Here at this poपूर्णांक there is no any concurrent access to sessions
	 * list and devices list:
	 *   1. New session or device can't be created - session sysfs files
	 *      are हटाओd.
	 *   2. Device or session can't be हटाओd - module reference is taken
	 *      पूर्णांकo account in unmap device sysfs callback.
	 *   3. No IO requests inflight - each file खोलो of block_dev increases
	 *      module reference in get_disk().
	 *
	 * But still there can be user requests inflights, which are sent by
	 * asynchronous send_msg_*() functions, thus beक्रमe unmapping devices
	 * RTRS session must be explicitly बंदd.
	 */

	list_क्रम_each_entry_safe(sess, sn, &sess_list, list) अणु
		अगर (!rnbd_clt_get_sess(sess))
			जारी;
		बंद_rtrs(sess);
		list_क्रम_each_entry_safe(dev, tn, &sess->devs_list, list) अणु
			/*
			 * Here unmap happens in parallel क्रम only one reason:
			 * blk_cleanup_queue() takes around half a second, so
			 * on huge amount of devices the whole module unload
			 * procedure takes minutes.
			 */
			INIT_WORK(&dev->unmap_on_rmmod_work, unmap_device_work);
			queue_work(प्रणाली_दीर्घ_wq, &dev->unmap_on_rmmod_work);
		पूर्ण
		rnbd_clt_put_sess(sess);
	पूर्ण
	/* Wait क्रम all scheduled unmap works */
	flush_workqueue(प्रणाली_दीर्घ_wq);
	WARN_ON(!list_empty(&sess_list));
पूर्ण

अटल पूर्णांक __init rnbd_client_init(व्योम)
अणु
	पूर्णांक err = 0;

	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_hdr) != 4);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_sess_info) != 36);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_sess_info_rsp) != 36);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_खोलो) != 264);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_बंद) != 8);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_खोलो_rsp) != 56);
	rnbd_client_major = रेजिस्टर_blkdev(rnbd_client_major, "rnbd");
	अगर (rnbd_client_major <= 0) अणु
		pr_err("Failed to load module, block device registration failed\n");
		वापस -EBUSY;
	पूर्ण

	err = rnbd_clt_create_sysfs_files();
	अगर (err) अणु
		pr_err("Failed to load module, creating sysfs device files failed, err: %d\n",
		       err);
		unरेजिस्टर_blkdev(rnbd_client_major, "rnbd");
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास rnbd_client_निकास(व्योम)
अणु
	rnbd_destroy_sessions();
	unरेजिस्टर_blkdev(rnbd_client_major, "rnbd");
	ida_destroy(&index_ida);
पूर्ण

module_init(rnbd_client_init);
module_निकास(rnbd_client_निकास);
