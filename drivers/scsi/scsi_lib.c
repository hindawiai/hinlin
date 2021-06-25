<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999 Eric Youngdale
 * Copyright (C) 2014 Christoph Hellwig
 *
 *  SCSI queueing library.
 *      Initial versions: Eric Youngdale (eric@andante.org).
 *                        Based upon conversations with large numbers
 *                        of people at Linux Expo.
 */

#समावेश <linux/bपन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/ratelimit.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h> /* __scsi_init_queue() */
#समावेश <scsi/scsi_dh.h>

#समावेश <trace/events/scsi.h>

#समावेश "scsi_debugfs.h"
#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"

/*
 * Size of पूर्णांकegrity metadata is usually small, 1 अंतरभूत sg should
 * cover normal हालs.
 */
#अगर_घोषित CONFIG_ARCH_NO_SG_CHAIN
#घोषणा  SCSI_INLINE_PROT_SG_CNT  0
#घोषणा  SCSI_INLINE_SG_CNT  0
#अन्यथा
#घोषणा  SCSI_INLINE_PROT_SG_CNT  1
#घोषणा  SCSI_INLINE_SG_CNT  2
#पूर्ण_अगर

अटल काष्ठा kmem_cache *scsi_sense_cache;
अटल DEFINE_MUTEX(scsi_sense_cache_mutex);

अटल व्योम scsi_mq_uninit_cmd(काष्ठा scsi_cmnd *cmd);

पूर्णांक scsi_init_sense_cache(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&scsi_sense_cache_mutex);
	अगर (!scsi_sense_cache) अणु
		scsi_sense_cache =
			kmem_cache_create_usercopy("scsi_sense_cache",
				SCSI_SENSE_BUFFERSIZE, 0, SLAB_HWCACHE_ALIGN,
				0, SCSI_SENSE_BUFFERSIZE, शून्य);
		अगर (!scsi_sense_cache)
			ret = -ENOMEM;
	पूर्ण
	mutex_unlock(&scsi_sense_cache_mutex);
	वापस ret;
पूर्ण

/*
 * When to reinvoke queueing after a resource लघुage. It's 3 msecs to
 * not change behaviour from the previous unplug mechanism, experimentation
 * may prove this needs changing.
 */
#घोषणा SCSI_QUEUE_DELAY	3

अटल व्योम
scsi_set_blocked(काष्ठा scsi_cmnd *cmd, पूर्णांक reason)
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा scsi_device *device = cmd->device;
	काष्ठा scsi_target *starget = scsi_target(device);

	/*
	 * Set the appropriate busy bit क्रम the device/host.
	 *
	 * If the host/device isn't busy, assume that something actually
	 * completed, and that we should be able to queue a command now.
	 *
	 * Note that the prior mid-layer assumption that any host could
	 * always queue at least one command is now broken.  The mid-layer
	 * will implement a user specअगरiable stall (see
	 * scsi_host.max_host_blocked and scsi_device.max_device_blocked)
	 * अगर a command is requeued with no other commands outstanding
	 * either क्रम the device or क्रम the host.
	 */
	चयन (reason) अणु
	हाल SCSI_MLQUEUE_HOST_BUSY:
		atomic_set(&host->host_blocked, host->max_host_blocked);
		अवरोध;
	हाल SCSI_MLQUEUE_DEVICE_BUSY:
	हाल SCSI_MLQUEUE_EH_RETRY:
		atomic_set(&device->device_blocked,
			   device->max_device_blocked);
		अवरोध;
	हाल SCSI_MLQUEUE_TARGET_BUSY:
		atomic_set(&starget->target_blocked,
			   starget->max_target_blocked);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम scsi_mq_requeue_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	अगर (cmd->request->rq_flags & RQF_DONTPREP) अणु
		cmd->request->rq_flags &= ~RQF_DONTPREP;
		scsi_mq_uninit_cmd(cmd);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(true);
	पूर्ण
	blk_mq_requeue_request(cmd->request, true);
पूर्ण

/**
 * __scsi_queue_insert - निजी queue insertion
 * @cmd: The SCSI command being requeued
 * @reason:  The reason क्रम the requeue
 * @unbusy: Whether the queue should be unbusied
 *
 * This is a निजी queue insertion.  The खुला पूर्णांकerface
 * scsi_queue_insert() always assumes the queue should be unbusied
 * because it's always called beक्रमe the completion.  This function is
 * क्रम a requeue after completion, which should only occur in this
 * file.
 */
अटल व्योम __scsi_queue_insert(काष्ठा scsi_cmnd *cmd, पूर्णांक reason, bool unbusy)
अणु
	काष्ठा scsi_device *device = cmd->device;

	SCSI_LOG_MLQUEUE(1, scmd_prपूर्णांकk(KERN_INFO, cmd,
		"Inserting command %p into mlqueue\n", cmd));

	scsi_set_blocked(cmd, reason);

	/*
	 * Decrement the counters, since these commands are no दीर्घer
	 * active on the host/device.
	 */
	अगर (unbusy)
		scsi_device_unbusy(device, cmd);

	/*
	 * Requeue this command.  It will go beक्रमe all other commands
	 * that are alपढ़ोy in the queue. Schedule requeue work under
	 * lock such that the kblockd_schedule_work() call happens
	 * beक्रमe blk_cleanup_queue() finishes.
	 */
	cmd->result = 0;

	blk_mq_requeue_request(cmd->request, true);
पूर्ण

/**
 * scsi_queue_insert - Reinsert a command in the queue.
 * @cmd:    command that we are adding to queue.
 * @reason: why we are inserting command to queue.
 *
 * We करो this क्रम one of two हालs. Either the host is busy and it cannot accept
 * any more commands क्रम the समय being, or the device वापसed QUEUE_FULL and
 * can accept no more commands.
 *
 * Context: This could be called either from an पूर्णांकerrupt context or a normal
 * process context.
 */
व्योम scsi_queue_insert(काष्ठा scsi_cmnd *cmd, पूर्णांक reason)
अणु
	__scsi_queue_insert(cmd, reason, true);
पूर्ण


/**
 * __scsi_execute - insert request and रुको क्रम the result
 * @sdev:	scsi device
 * @cmd:	scsi command
 * @data_direction: data direction
 * @buffer:	data buffer
 * @bufflen:	len of buffer
 * @sense:	optional sense buffer
 * @sshdr:	optional decoded sense header
 * @समयout:	request समयout in seconds
 * @retries:	number of बार to retry request
 * @flags:	flags क्रम ->cmd_flags
 * @rq_flags:	flags क्रम ->rq_flags
 * @resid:	optional residual length
 *
 * Returns the scsi_cmnd result field अगर a command was executed, or a negative
 * Linux error code अगर we didn't get that far.
 */
पूर्णांक __scsi_execute(काष्ठा scsi_device *sdev, स्थिर अचिन्हित अक्षर *cmd,
		 पूर्णांक data_direction, व्योम *buffer, अचिन्हित bufflen,
		 अचिन्हित अक्षर *sense, काष्ठा scsi_sense_hdr *sshdr,
		 पूर्णांक समयout, पूर्णांक retries, u64 flags, req_flags_t rq_flags,
		 पूर्णांक *resid)
अणु
	काष्ठा request *req;
	काष्ठा scsi_request *rq;
	पूर्णांक ret = DRIVER_ERROR << 24;

	req = blk_get_request(sdev->request_queue,
			data_direction == DMA_TO_DEVICE ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN,
			rq_flags & RQF_PM ? BLK_MQ_REQ_PM : 0);
	अगर (IS_ERR(req))
		वापस ret;
	rq = scsi_req(req);

	अगर (bufflen &&	blk_rq_map_kern(sdev->request_queue, req,
					buffer, bufflen, GFP_NOIO))
		जाओ out;

	rq->cmd_len = COMMAND_SIZE(cmd[0]);
	स_नकल(rq->cmd, cmd, rq->cmd_len);
	rq->retries = retries;
	req->समयout = समयout;
	req->cmd_flags |= flags;
	req->rq_flags |= rq_flags | RQF_QUIET;

	/*
	 * head injection *required* here otherwise quiesce won't work
	 */
	blk_execute_rq(शून्य, req, 1);

	/*
	 * Some devices (USB mass-storage in particular) may transfer
	 * garbage data together with a residue indicating that the data
	 * is invalid.  Prevent the garbage from being misपूर्णांकerpreted
	 * and prevent security leaks by zeroing out the excess data.
	 */
	अगर (unlikely(rq->resid_len > 0 && rq->resid_len <= bufflen))
		स_रखो(buffer + (bufflen - rq->resid_len), 0, rq->resid_len);

	अगर (resid)
		*resid = rq->resid_len;
	अगर (sense && rq->sense_len)
		स_नकल(sense, rq->sense, SCSI_SENSE_BUFFERSIZE);
	अगर (sshdr)
		scsi_normalize_sense(rq->sense, rq->sense_len, sshdr);
	ret = rq->result;
 out:
	blk_put_request(req);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__scsi_execute);

/*
 * Wake up the error handler अगर necessary. Aव्योम as follows that the error
 * handler is not woken up अगर host in-flight requests number ==
 * shost->host_failed: use call_rcu() in scsi_eh_scmd_add() in combination
 * with an RCU पढ़ो lock in this function to ensure that this function in
 * its entirety either finishes beक्रमe scsi_eh_scmd_add() increases the
 * host_failed counter or that it notices the shost state change made by
 * scsi_eh_scmd_add().
 */
अटल व्योम scsi_dec_host_busy(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmd)
अणु
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();
	__clear_bit(SCMD_STATE_INFLIGHT, &cmd->state);
	अगर (unlikely(scsi_host_in_recovery(shost))) अणु
		spin_lock_irqsave(shost->host_lock, flags);
		अगर (shost->host_failed || shost->host_eh_scheduled)
			scsi_eh_wakeup(shost);
		spin_unlock_irqrestore(shost->host_lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम scsi_device_unbusy(काष्ठा scsi_device *sdev, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा scsi_target *starget = scsi_target(sdev);

	scsi_dec_host_busy(shost, cmd);

	अगर (starget->can_queue > 0)
		atomic_dec(&starget->target_busy);

	sbiपंचांगap_put(&sdev->budget_map, cmd->budget_token);
	cmd->budget_token = -1;
पूर्ण

अटल व्योम scsi_kick_queue(काष्ठा request_queue *q)
अणु
	blk_mq_run_hw_queues(q, false);
पूर्ण

/*
 * Called क्रम single_lun devices on IO completion. Clear starget_sdev_user,
 * and call blk_run_queue क्रम all the scsi_devices on the target -
 * including current_sdev first.
 *
 * Called with *no* scsi locks held.
 */
अटल व्योम scsi_single_lun_run(काष्ठा scsi_device *current_sdev)
अणु
	काष्ठा Scsi_Host *shost = current_sdev->host;
	काष्ठा scsi_device *sdev, *पंचांगp;
	काष्ठा scsi_target *starget = scsi_target(current_sdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	starget->starget_sdev_user = शून्य;
	spin_unlock_irqrestore(shost->host_lock, flags);

	/*
	 * Call blk_run_queue क्रम all LUNs on the target, starting with
	 * current_sdev. We race with others (to set starget_sdev_user),
	 * but in most हालs, we will be first. Ideally, each LU on the
	 * target would get some limited समय or requests on the target.
	 */
	scsi_kick_queue(current_sdev->request_queue);

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (starget->starget_sdev_user)
		जाओ out;
	list_क्रम_each_entry_safe(sdev, पंचांगp, &starget->devices,
			same_target_siblings) अणु
		अगर (sdev == current_sdev)
			जारी;
		अगर (scsi_device_get(sdev))
			जारी;

		spin_unlock_irqrestore(shost->host_lock, flags);
		scsi_kick_queue(sdev->request_queue);
		spin_lock_irqsave(shost->host_lock, flags);

		scsi_device_put(sdev);
	पूर्ण
 out:
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

अटल अंतरभूत bool scsi_device_is_busy(काष्ठा scsi_device *sdev)
अणु
	अगर (scsi_device_busy(sdev) >= sdev->queue_depth)
		वापस true;
	अगर (atomic_पढ़ो(&sdev->device_blocked) > 0)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool scsi_target_is_busy(काष्ठा scsi_target *starget)
अणु
	अगर (starget->can_queue > 0) अणु
		अगर (atomic_पढ़ो(&starget->target_busy) >= starget->can_queue)
			वापस true;
		अगर (atomic_पढ़ो(&starget->target_blocked) > 0)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool scsi_host_is_busy(काष्ठा Scsi_Host *shost)
अणु
	अगर (atomic_पढ़ो(&shost->host_blocked) > 0)
		वापस true;
	अगर (shost->host_self_blocked)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम scsi_starved_list_run(काष्ठा Scsi_Host *shost)
अणु
	LIST_HEAD(starved_list);
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	list_splice_init(&shost->starved_list, &starved_list);

	जबतक (!list_empty(&starved_list)) अणु
		काष्ठा request_queue *slq;

		/*
		 * As दीर्घ as shost is accepting commands and we have
		 * starved queues, call blk_run_queue. scsi_request_fn
		 * drops the queue_lock and can add us back to the
		 * starved_list.
		 *
		 * host_lock protects the starved_list and starved_entry.
		 * scsi_request_fn must get the host_lock beक्रमe checking
		 * or modअगरying starved_list or starved_entry.
		 */
		अगर (scsi_host_is_busy(shost))
			अवरोध;

		sdev = list_entry(starved_list.next,
				  काष्ठा scsi_device, starved_entry);
		list_del_init(&sdev->starved_entry);
		अगर (scsi_target_is_busy(scsi_target(sdev))) अणु
			list_move_tail(&sdev->starved_entry,
				       &shost->starved_list);
			जारी;
		पूर्ण

		/*
		 * Once we drop the host lock, a racing scsi_हटाओ_device()
		 * call may हटाओ the sdev from the starved list and destroy
		 * it and the queue.  Mitigate by taking a reference to the
		 * queue and never touching the sdev again after we drop the
		 * host lock.  Note: अगर __scsi_हटाओ_device() invokes
		 * blk_cleanup_queue() beक्रमe the queue is run from this
		 * function then blk_run_queue() will वापस immediately since
		 * blk_cleanup_queue() marks the queue with QUEUE_FLAG_DYING.
		 */
		slq = sdev->request_queue;
		अगर (!blk_get_queue(slq))
			जारी;
		spin_unlock_irqrestore(shost->host_lock, flags);

		scsi_kick_queue(slq);
		blk_put_queue(slq);

		spin_lock_irqsave(shost->host_lock, flags);
	पूर्ण
	/* put any unprocessed entries back */
	list_splice(&starved_list, &shost->starved_list);
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * scsi_run_queue - Select a proper request queue to serve next.
 * @q:  last request's queue
 *
 * The previous command was completely finished, start a new one अगर possible.
 */
अटल व्योम scsi_run_queue(काष्ठा request_queue *q)
अणु
	काष्ठा scsi_device *sdev = q->queuedata;

	अगर (scsi_target(sdev)->single_lun)
		scsi_single_lun_run(sdev);
	अगर (!list_empty(&sdev->host->starved_list))
		scsi_starved_list_run(sdev->host);

	blk_mq_run_hw_queues(q, false);
पूर्ण

व्योम scsi_requeue_run_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा request_queue *q;

	sdev = container_of(work, काष्ठा scsi_device, requeue_work);
	q = sdev->request_queue;
	scsi_run_queue(q);
पूर्ण

व्योम scsi_run_host_queues(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_device *sdev;

	shost_क्रम_each_device(sdev, shost)
		scsi_run_queue(sdev->request_queue);
पूर्ण

अटल व्योम scsi_uninit_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	अगर (!blk_rq_is_passthrough(cmd->request)) अणु
		काष्ठा scsi_driver *drv = scsi_cmd_to_driver(cmd);

		अगर (drv->uninit_command)
			drv->uninit_command(cmd);
	पूर्ण
पूर्ण

व्योम scsi_मुक्त_sgtables(काष्ठा scsi_cmnd *cmd)
अणु
	अगर (cmd->sdb.table.nents)
		sg_मुक्त_table_chained(&cmd->sdb.table,
				SCSI_INLINE_SG_CNT);
	अगर (scsi_prot_sg_count(cmd))
		sg_मुक्त_table_chained(&cmd->prot_sdb->table,
				SCSI_INLINE_PROT_SG_CNT);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_मुक्त_sgtables);

अटल व्योम scsi_mq_uninit_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	scsi_मुक्त_sgtables(cmd);
	scsi_uninit_cmd(cmd);
पूर्ण

अटल व्योम scsi_run_queue_async(काष्ठा scsi_device *sdev)
अणु
	अगर (scsi_target(sdev)->single_lun ||
	    !list_empty(&sdev->host->starved_list)) अणु
		kblockd_schedule_work(&sdev->requeue_work);
	पूर्ण अन्यथा अणु
		/*
		 * smp_mb() present in sbiपंचांगap_queue_clear() or implied in
		 * .end_io is क्रम ordering writing .device_busy in
		 * scsi_device_unbusy() and पढ़ोing sdev->restarts.
		 */
		पूर्णांक old = atomic_पढ़ो(&sdev->restarts);

		/*
		 * ->restarts has to be kept as non-zero अगर new budget
		 *  contention occurs.
		 *
		 *  No need to run queue when either another re-run
		 *  queue wins in updating ->restarts or a new budget
		 *  contention occurs.
		 */
		अगर (old && atomic_cmpxchg(&sdev->restarts, old, 0) == old)
			blk_mq_run_hw_queues(sdev->request_queue, true);
	पूर्ण
पूर्ण

/* Returns false when no more bytes to process, true अगर there are more */
अटल bool scsi_end_request(काष्ठा request *req, blk_status_t error,
		अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा request_queue *q = sdev->request_queue;

	अगर (blk_update_request(req, error, bytes))
		वापस true;

	अगर (blk_queue_add_अक्रमom(q))
		add_disk_अक्रमomness(req->rq_disk);

	अगर (!blk_rq_is_scsi(req)) अणु
		WARN_ON_ONCE(!(cmd->flags & SCMD_INITIALIZED));
		cmd->flags &= ~SCMD_INITIALIZED;
	पूर्ण

	/*
	 * Calling rcu_barrier() is not necessary here because the
	 * SCSI error handler guarantees that the function called by
	 * call_rcu() has been called beक्रमe scsi_end_request() is
	 * called.
	 */
	destroy_rcu_head(&cmd->rcu);

	/*
	 * In the MQ हाल the command माला_लो मुक्तd by __blk_mq_end_request,
	 * so we have to करो all cleanup that depends on it earlier.
	 *
	 * We also can't kick the queues from irq context, so we
	 * will have to defer it to a workqueue.
	 */
	scsi_mq_uninit_cmd(cmd);

	/*
	 * queue is still alive, so grab the ref क्रम preventing it
	 * from being cleaned up during running queue.
	 */
	percpu_ref_get(&q->q_usage_counter);

	__blk_mq_end_request(req, error);

	scsi_run_queue_async(sdev);

	percpu_ref_put(&q->q_usage_counter);
	वापस false;
पूर्ण

/**
 * scsi_result_to_blk_status - translate a SCSI result code पूर्णांकo blk_status_t
 * @cmd:	SCSI command
 * @result:	scsi error code
 *
 * Translate a SCSI result code पूर्णांकo a blk_status_t value. May reset the host
 * byte of @cmd->result.
 */
अटल blk_status_t scsi_result_to_blk_status(काष्ठा scsi_cmnd *cmd, पूर्णांक result)
अणु
	चयन (host_byte(result)) अणु
	हाल DID_OK:
		/*
		 * Also check the other bytes than the status byte in result
		 * to handle the हाल when a SCSI LLD sets result to
		 * DRIVER_SENSE << 24 without setting SAM_STAT_CHECK_CONDITION.
		 */
		अगर (scsi_status_is_good(result) && (result & ~0xff) == 0)
			वापस BLK_STS_OK;
		वापस BLK_STS_IOERR;
	हाल DID_TRANSPORT_FAILFAST:
	हाल DID_TRANSPORT_MARGINAL:
		वापस BLK_STS_TRANSPORT;
	हाल DID_TARGET_FAILURE:
		set_host_byte(cmd, DID_OK);
		वापस BLK_STS_TARGET;
	हाल DID_NEXUS_FAILURE:
		set_host_byte(cmd, DID_OK);
		वापस BLK_STS_NEXUS;
	हाल DID_ALLOC_FAILURE:
		set_host_byte(cmd, DID_OK);
		वापस BLK_STS_NOSPC;
	हाल DID_MEDIUM_ERROR:
		set_host_byte(cmd, DID_OK);
		वापस BLK_STS_MEDIUM;
	शेष:
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

/* Helper क्रम scsi_io_completion() when "reprep" action required. */
अटल व्योम scsi_io_completion_reprep(काष्ठा scsi_cmnd *cmd,
				      काष्ठा request_queue *q)
अणु
	/* A new command will be prepared and issued. */
	scsi_mq_requeue_cmd(cmd);
पूर्ण

अटल bool scsi_cmd_runसमय_exceeced(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा request *req = cmd->request;
	अचिन्हित दीर्घ रुको_क्रम;

	अगर (cmd->allowed == SCSI_CMD_RETRIES_NO_LIMIT)
		वापस false;

	रुको_क्रम = (cmd->allowed + 1) * req->समयout;
	अगर (समय_beक्रमe(cmd->jअगरfies_at_alloc + रुको_क्रम, jअगरfies)) अणु
		scmd_prपूर्णांकk(KERN_ERR, cmd, "timing out command, waited %lus\n",
			    रुको_क्रम/HZ);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Helper क्रम scsi_io_completion() when special action required. */
अटल व्योम scsi_io_completion_action(काष्ठा scsi_cmnd *cmd, पूर्णांक result)
अणु
	काष्ठा request_queue *q = cmd->device->request_queue;
	काष्ठा request *req = cmd->request;
	पूर्णांक level = 0;
	क्रमागत अणुACTION_FAIL, ACTION_REPREP, ACTION_RETRY,
	      ACTION_DELAYED_RETRYपूर्ण action;
	काष्ठा scsi_sense_hdr sshdr;
	bool sense_valid;
	bool sense_current = true;      /* false implies "deferred sense" */
	blk_status_t blk_stat;

	sense_valid = scsi_command_normalize_sense(cmd, &sshdr);
	अगर (sense_valid)
		sense_current = !scsi_sense_is_deferred(&sshdr);

	blk_stat = scsi_result_to_blk_status(cmd, result);

	अगर (host_byte(result) == DID_RESET) अणु
		/* Third party bus reset or reset क्रम error recovery
		 * reasons.  Just retry the command and see what
		 * happens.
		 */
		action = ACTION_RETRY;
	पूर्ण अन्यथा अगर (sense_valid && sense_current) अणु
		चयन (sshdr.sense_key) अणु
		हाल UNIT_ATTENTION:
			अगर (cmd->device->removable) अणु
				/* Detected disc change.  Set a bit
				 * and quietly refuse further access.
				 */
				cmd->device->changed = 1;
				action = ACTION_FAIL;
			पूर्ण अन्यथा अणु
				/* Must have been a घातer glitch, or a
				 * bus reset.  Could not have been a
				 * media change, so we just retry the
				 * command and see what happens.
				 */
				action = ACTION_RETRY;
			पूर्ण
			अवरोध;
		हाल ILLEGAL_REQUEST:
			/* If we had an ILLEGAL REQUEST वापसed, then
			 * we may have perक्रमmed an unsupported
			 * command.  The only thing this should be
			 * would be a ten byte पढ़ो where only a six
			 * byte पढ़ो was supported.  Also, on a प्रणाली
			 * where READ CAPACITY failed, we may have
			 * पढ़ो past the end of the disk.
			 */
			अगर ((cmd->device->use_10_क्रम_rw &&
			    sshdr.asc == 0x20 && sshdr.ascq == 0x00) &&
			    (cmd->cmnd[0] == READ_10 ||
			     cmd->cmnd[0] == WRITE_10)) अणु
				/* This will issue a new 6-byte command. */
				cmd->device->use_10_क्रम_rw = 0;
				action = ACTION_REPREP;
			पूर्ण अन्यथा अगर (sshdr.asc == 0x10) /* DIX */ अणु
				action = ACTION_FAIL;
				blk_stat = BLK_STS_PROTECTION;
			/* INVALID COMMAND OPCODE or INVALID FIELD IN CDB */
			पूर्ण अन्यथा अगर (sshdr.asc == 0x20 || sshdr.asc == 0x24) अणु
				action = ACTION_FAIL;
				blk_stat = BLK_STS_TARGET;
			पूर्ण अन्यथा
				action = ACTION_FAIL;
			अवरोध;
		हाल ABORTED_COMMAND:
			action = ACTION_FAIL;
			अगर (sshdr.asc == 0x10) /* DIF */
				blk_stat = BLK_STS_PROTECTION;
			अवरोध;
		हाल NOT_READY:
			/* If the device is in the process of becoming
			 * पढ़ोy, or has a temporary blockage, retry.
			 */
			अगर (sshdr.asc == 0x04) अणु
				चयन (sshdr.ascq) अणु
				हाल 0x01: /* becoming पढ़ोy */
				हाल 0x04: /* क्रमmat in progress */
				हाल 0x05: /* rebuild in progress */
				हाल 0x06: /* recalculation in progress */
				हाल 0x07: /* operation in progress */
				हाल 0x08: /* Long ग_लिखो in progress */
				हाल 0x09: /* self test in progress */
				हाल 0x14: /* space allocation in progress */
				हाल 0x1a: /* start stop unit in progress */
				हाल 0x1b: /* sanitize in progress */
				हाल 0x1d: /* configuration in progress */
				हाल 0x24: /* depopulation in progress */
					action = ACTION_DELAYED_RETRY;
					अवरोध;
				हाल 0x0a: /* ALUA state transition */
					blk_stat = BLK_STS_AGAIN;
					fallthrough;
				शेष:
					action = ACTION_FAIL;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा
				action = ACTION_FAIL;
			अवरोध;
		हाल VOLUME_OVERFLOW:
			/* See SSC3rXX or current. */
			action = ACTION_FAIL;
			अवरोध;
		हाल DATA_PROTECT:
			action = ACTION_FAIL;
			अगर ((sshdr.asc == 0x0C && sshdr.ascq == 0x12) ||
			    (sshdr.asc == 0x55 &&
			     (sshdr.ascq == 0x0E || sshdr.ascq == 0x0F))) अणु
				/* Insufficient zone resources */
				blk_stat = BLK_STS_ZONE_OPEN_RESOURCE;
			पूर्ण
			अवरोध;
		शेष:
			action = ACTION_FAIL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		action = ACTION_FAIL;

	अगर (action != ACTION_FAIL && scsi_cmd_runसमय_exceeced(cmd))
		action = ACTION_FAIL;

	चयन (action) अणु
	हाल ACTION_FAIL:
		/* Give up and fail the reमुख्यder of the request */
		अगर (!(req->rq_flags & RQF_QUIET)) अणु
			अटल DEFINE_RATELIMIT_STATE(_rs,
					DEFAULT_RATELIMIT_INTERVAL,
					DEFAULT_RATELIMIT_BURST);

			अगर (unlikely(scsi_logging_level))
				level =
				     SCSI_LOG_LEVEL(SCSI_LOG_MLCOMPLETE_SHIFT,
						    SCSI_LOG_MLCOMPLETE_BITS);

			/*
			 * अगर logging is enabled the failure will be prपूर्णांकed
			 * in scsi_log_completion(), so aव्योम duplicate messages
			 */
			अगर (!level && __ratelimit(&_rs)) अणु
				scsi_prपूर्णांक_result(cmd, शून्य, FAILED);
				अगर (driver_byte(result) == DRIVER_SENSE)
					scsi_prपूर्णांक_sense(cmd);
				scsi_prपूर्णांक_command(cmd);
			पूर्ण
		पूर्ण
		अगर (!scsi_end_request(req, blk_stat, blk_rq_err_bytes(req)))
			वापस;
		fallthrough;
	हाल ACTION_REPREP:
		scsi_io_completion_reprep(cmd, q);
		अवरोध;
	हाल ACTION_RETRY:
		/* Retry the same command immediately */
		__scsi_queue_insert(cmd, SCSI_MLQUEUE_EH_RETRY, false);
		अवरोध;
	हाल ACTION_DELAYED_RETRY:
		/* Retry the same command after a delay */
		__scsi_queue_insert(cmd, SCSI_MLQUEUE_DEVICE_BUSY, false);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Helper क्रम scsi_io_completion() when cmd->result is non-zero. Returns a
 * new result that may suppress further error checking. Also modअगरies
 * *blk_statp in some हालs.
 */
अटल पूर्णांक scsi_io_completion_nz_result(काष्ठा scsi_cmnd *cmd, पूर्णांक result,
					blk_status_t *blk_statp)
अणु
	bool sense_valid;
	bool sense_current = true;	/* false implies "deferred sense" */
	काष्ठा request *req = cmd->request;
	काष्ठा scsi_sense_hdr sshdr;

	sense_valid = scsi_command_normalize_sense(cmd, &sshdr);
	अगर (sense_valid)
		sense_current = !scsi_sense_is_deferred(&sshdr);

	अगर (blk_rq_is_passthrough(req)) अणु
		अगर (sense_valid) अणु
			/*
			 * SG_IO wants current and deferred errors
			 */
			scsi_req(req)->sense_len =
				min(8 + cmd->sense_buffer[7],
				    SCSI_SENSE_BUFFERSIZE);
		पूर्ण
		अगर (sense_current)
			*blk_statp = scsi_result_to_blk_status(cmd, result);
	पूर्ण अन्यथा अगर (blk_rq_bytes(req) == 0 && sense_current) अणु
		/*
		 * Flush commands करो not transfers any data, and thus cannot use
		 * good_bytes != blk_rq_bytes(req) as the संकेत क्रम an error.
		 * This sets *blk_statp explicitly क्रम the problem हाल.
		 */
		*blk_statp = scsi_result_to_blk_status(cmd, result);
	पूर्ण
	/*
	 * Recovered errors need reporting, but they're always treated as
	 * success, so fiddle the result code here.  For passthrough requests
	 * we alपढ़ोy took a copy of the original पूर्णांकo sreq->result which
	 * is what माला_लो वापसed to the user
	 */
	अगर (sense_valid && (sshdr.sense_key == RECOVERED_ERROR)) अणु
		bool करो_prपूर्णांक = true;
		/*
		 * अगर ATA PASS-THROUGH INFORMATION AVAILABLE [0x0, 0x1d]
		 * skip prपूर्णांक since caller wants ATA रेजिस्टरs. Only occurs
		 * on SCSI ATA PASS_THROUGH commands when CK_COND=1
		 */
		अगर ((sshdr.asc == 0x0) && (sshdr.ascq == 0x1d))
			करो_prपूर्णांक = false;
		अन्यथा अगर (req->rq_flags & RQF_QUIET)
			करो_prपूर्णांक = false;
		अगर (करो_prपूर्णांक)
			scsi_prपूर्णांक_sense(cmd);
		result = 0;
		/* क्रम passthrough, *blk_statp may be set */
		*blk_statp = BLK_STS_OK;
	पूर्ण
	/*
	 * Another corner हाल: the SCSI status byte is non-zero but 'good'.
	 * Example: PRE-FETCH command वापसs SAM_STAT_CONDITION_MET when
	 * it is able to fit nominated LBs in its cache (and SAM_STAT_GOOD
	 * अगर it can't fit). Treat SAM_STAT_CONDITION_MET and the related
	 * पूर्णांकermediate statuses (both obsolete in SAM-4) as good.
	 */
	अगर (status_byte(result) && scsi_status_is_good(result)) अणु
		result = 0;
		*blk_statp = BLK_STS_OK;
	पूर्ण
	वापस result;
पूर्ण

/**
 * scsi_io_completion - Completion processing क्रम SCSI commands.
 * @cmd:	command that is finished.
 * @good_bytes:	number of processed bytes.
 *
 * We will finish off the specअगरied number of sectors. If we are करोne, the
 * command block will be released and the queue function will be goosed. If we
 * are not करोne then we have to figure out what to करो next:
 *
 *   a) We can call scsi_io_completion_reprep().  The request will be
 *	unprepared and put back on the queue.  Then a new command will
 *	be created क्रम it.  This should be used अगर we made क्रमward
 *	progress, or अगर we want to चयन from READ(10) to READ(6) क्रम
 *	example.
 *
 *   b) We can call scsi_io_completion_action().  The request will be
 *	put back on the queue and retried using the same command as
 *	beक्रमe, possibly after a delay.
 *
 *   c) We can call scsi_end_request() with blk_stat other than
 *	BLK_STS_OK, to fail the reमुख्यder of the request.
 */
व्योम scsi_io_completion(काष्ठा scsi_cmnd *cmd, अचिन्हित पूर्णांक good_bytes)
अणु
	पूर्णांक result = cmd->result;
	काष्ठा request_queue *q = cmd->device->request_queue;
	काष्ठा request *req = cmd->request;
	blk_status_t blk_stat = BLK_STS_OK;

	अगर (unlikely(result))	/* a nz result may or may not be an error */
		result = scsi_io_completion_nz_result(cmd, result, &blk_stat);

	अगर (unlikely(blk_rq_is_passthrough(req))) अणु
		/*
		 * scsi_result_to_blk_status may have reset the host_byte
		 */
		scsi_req(req)->result = cmd->result;
	पूर्ण

	/*
	 * Next deal with any sectors which we were able to correctly
	 * handle.
	 */
	SCSI_LOG_HLCOMPLETE(1, scmd_prपूर्णांकk(KERN_INFO, cmd,
		"%u sectors total, %d bytes done.\n",
		blk_rq_sectors(req), good_bytes));

	/*
	 * Failed, zero length commands always need to drop करोwn
	 * to retry code. Fast path should वापस in this block.
	 */
	अगर (likely(blk_rq_bytes(req) > 0 || blk_stat == BLK_STS_OK)) अणु
		अगर (likely(!scsi_end_request(req, blk_stat, good_bytes)))
			वापस; /* no bytes reमुख्यing */
	पूर्ण

	/* Kill reमुख्यder अगर no retries. */
	अगर (unlikely(blk_stat && scsi_noretry_cmd(cmd))) अणु
		अगर (scsi_end_request(req, blk_stat, blk_rq_bytes(req)))
			WARN_ONCE(true,
			    "Bytes remaining after failed, no-retry command");
		वापस;
	पूर्ण

	/*
	 * If there had been no error, but we have leftover bytes in the
	 * requeues just queue the command up again.
	 */
	अगर (likely(result == 0))
		scsi_io_completion_reprep(cmd, q);
	अन्यथा
		scsi_io_completion_action(cmd, result);
पूर्ण

अटल अंतरभूत bool scsi_cmd_needs_dma_drain(काष्ठा scsi_device *sdev,
		काष्ठा request *rq)
अणु
	वापस sdev->dma_drain_len && blk_rq_is_passthrough(rq) &&
	       !op_is_ग_लिखो(req_op(rq)) &&
	       sdev->host->hostt->dma_need_drain(rq);
पूर्ण

/**
 * scsi_alloc_sgtables - Allocate and initialize data and पूर्णांकegrity scatterlists
 * @cmd: SCSI command data काष्ठाure to initialize.
 *
 * Initializes @cmd->sdb and also @cmd->prot_sdb अगर data पूर्णांकegrity is enabled
 * क्रम @cmd.
 *
 * Returns:
 * * BLK_STS_OK       - on success
 * * BLK_STS_RESOURCE - अगर the failure is retryable
 * * BLK_STS_IOERR    - अगर the failure is fatal
 */
blk_status_t scsi_alloc_sgtables(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा request *rq = cmd->request;
	अचिन्हित लघु nr_segs = blk_rq_nr_phys_segments(rq);
	काष्ठा scatterlist *last_sg = शून्य;
	blk_status_t ret;
	bool need_drain = scsi_cmd_needs_dma_drain(sdev, rq);
	पूर्णांक count;

	अगर (WARN_ON_ONCE(!nr_segs))
		वापस BLK_STS_IOERR;

	/*
	 * Make sure there is space क्रम the drain.  The driver must adjust
	 * max_hw_segments to be prepared क्रम this.
	 */
	अगर (need_drain)
		nr_segs++;

	/*
	 * If sg table allocation fails, requeue request later.
	 */
	अगर (unlikely(sg_alloc_table_chained(&cmd->sdb.table, nr_segs,
			cmd->sdb.table.sgl, SCSI_INLINE_SG_CNT)))
		वापस BLK_STS_RESOURCE;

	/*
	 * Next, walk the list, and fill in the addresses and sizes of
	 * each segment.
	 */
	count = __blk_rq_map_sg(rq->q, rq, cmd->sdb.table.sgl, &last_sg);

	अगर (blk_rq_bytes(rq) & rq->q->dma_pad_mask) अणु
		अचिन्हित पूर्णांक pad_len =
			(rq->q->dma_pad_mask & ~blk_rq_bytes(rq)) + 1;

		last_sg->length += pad_len;
		cmd->extra_len += pad_len;
	पूर्ण

	अगर (need_drain) अणु
		sg_unmark_end(last_sg);
		last_sg = sg_next(last_sg);
		sg_set_buf(last_sg, sdev->dma_drain_buf, sdev->dma_drain_len);
		sg_mark_end(last_sg);

		cmd->extra_len += sdev->dma_drain_len;
		count++;
	पूर्ण

	BUG_ON(count > cmd->sdb.table.nents);
	cmd->sdb.table.nents = count;
	cmd->sdb.length = blk_rq_payload_bytes(rq);

	अगर (blk_पूर्णांकegrity_rq(rq)) अणु
		काष्ठा scsi_data_buffer *prot_sdb = cmd->prot_sdb;
		पूर्णांक ivecs;

		अगर (WARN_ON_ONCE(!prot_sdb)) अणु
			/*
			 * This can happen अगर someone (e.g. multipath)
			 * queues a command to a device on an adapter
			 * that करोes not support DIX.
			 */
			ret = BLK_STS_IOERR;
			जाओ out_मुक्त_sgtables;
		पूर्ण

		ivecs = blk_rq_count_पूर्णांकegrity_sg(rq->q, rq->bio);

		अगर (sg_alloc_table_chained(&prot_sdb->table, ivecs,
				prot_sdb->table.sgl,
				SCSI_INLINE_PROT_SG_CNT)) अणु
			ret = BLK_STS_RESOURCE;
			जाओ out_मुक्त_sgtables;
		पूर्ण

		count = blk_rq_map_पूर्णांकegrity_sg(rq->q, rq->bio,
						prot_sdb->table.sgl);
		BUG_ON(count > ivecs);
		BUG_ON(count > queue_max_पूर्णांकegrity_segments(rq->q));

		cmd->prot_sdb = prot_sdb;
		cmd->prot_sdb->table.nents = count;
	पूर्ण

	वापस BLK_STS_OK;
out_मुक्त_sgtables:
	scsi_मुक्त_sgtables(cmd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(scsi_alloc_sgtables);

/**
 * scsi_initialize_rq - initialize काष्ठा scsi_cmnd partially
 * @rq: Request associated with the SCSI command to be initialized.
 *
 * This function initializes the members of काष्ठा scsi_cmnd that must be
 * initialized beक्रमe request processing starts and that won't be
 * reinitialized अगर a SCSI command is requeued.
 *
 * Called from inside blk_get_request() क्रम pass-through requests and from
 * inside scsi_init_command() क्रम fileप्रणाली requests.
 */
अटल व्योम scsi_initialize_rq(काष्ठा request *rq)
अणु
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);

	scsi_req_init(&cmd->req);
	init_rcu_head(&cmd->rcu);
	cmd->jअगरfies_at_alloc = jअगरfies;
	cmd->retries = 0;
पूर्ण

/*
 * Only called when the request isn't completed by SCSI, and not मुक्तd by
 * SCSI
 */
अटल व्योम scsi_cleanup_rq(काष्ठा request *rq)
अणु
	अगर (rq->rq_flags & RQF_DONTPREP) अणु
		scsi_mq_uninit_cmd(blk_mq_rq_to_pdu(rq));
		rq->rq_flags &= ~RQF_DONTPREP;
	पूर्ण
पूर्ण

/* Called beक्रमe a request is prepared. See also scsi_mq_prep_fn(). */
व्योम scsi_init_command(काष्ठा scsi_device *dev, काष्ठा scsi_cmnd *cmd)
अणु
	व्योम *buf = cmd->sense_buffer;
	व्योम *prot = cmd->prot_sdb;
	काष्ठा request *rq = blk_mq_rq_from_pdu(cmd);
	अचिन्हित पूर्णांक flags = cmd->flags & SCMD_PRESERVED_FLAGS;
	अचिन्हित दीर्घ jअगरfies_at_alloc;
	पूर्णांक retries, to_clear;
	bool in_flight;
	पूर्णांक budget_token = cmd->budget_token;

	अगर (!blk_rq_is_scsi(rq) && !(flags & SCMD_INITIALIZED)) अणु
		flags |= SCMD_INITIALIZED;
		scsi_initialize_rq(rq);
	पूर्ण

	jअगरfies_at_alloc = cmd->jअगरfies_at_alloc;
	retries = cmd->retries;
	in_flight = test_bit(SCMD_STATE_INFLIGHT, &cmd->state);
	/*
	 * Zero out the cmd, except क्रम the embedded scsi_request. Only clear
	 * the driver-निजी command data अगर the LLD करोes not supply a
	 * function to initialize that data.
	 */
	to_clear = माप(*cmd) - माप(cmd->req);
	अगर (!dev->host->hostt->init_cmd_priv)
		to_clear += dev->host->hostt->cmd_size;
	स_रखो((अक्षर *)cmd + माप(cmd->req), 0, to_clear);

	cmd->device = dev;
	cmd->sense_buffer = buf;
	cmd->prot_sdb = prot;
	cmd->flags = flags;
	INIT_DELAYED_WORK(&cmd->पात_work, scmd_eh_पात_handler);
	cmd->jअगरfies_at_alloc = jअगरfies_at_alloc;
	cmd->retries = retries;
	अगर (in_flight)
		__set_bit(SCMD_STATE_INFLIGHT, &cmd->state);
	cmd->budget_token = budget_token;

पूर्ण

अटल blk_status_t scsi_setup_scsi_cmnd(काष्ठा scsi_device *sdev,
		काष्ठा request *req)
अणु
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);

	/*
	 * Passthrough requests may transfer data, in which हाल they must
	 * a bio attached to them.  Or they might contain a SCSI command
	 * that करोes not transfer data, in which हाल they may optionally
	 * submit a request without an attached bio.
	 */
	अगर (req->bio) अणु
		blk_status_t ret = scsi_alloc_sgtables(cmd);
		अगर (unlikely(ret != BLK_STS_OK))
			वापस ret;
	पूर्ण अन्यथा अणु
		BUG_ON(blk_rq_bytes(req));

		स_रखो(&cmd->sdb, 0, माप(cmd->sdb));
	पूर्ण

	cmd->cmd_len = scsi_req(req)->cmd_len;
	अगर (cmd->cmd_len == 0)
		cmd->cmd_len = scsi_command_size(cmd->cmnd);
	cmd->cmnd = scsi_req(req)->cmd;
	cmd->transfersize = blk_rq_bytes(req);
	cmd->allowed = scsi_req(req)->retries;
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t
scsi_device_state_check(काष्ठा scsi_device *sdev, काष्ठा request *req)
अणु
	चयन (sdev->sdev_state) अणु
	हाल SDEV_CREATED:
		वापस BLK_STS_OK;
	हाल SDEV_OFFLINE:
	हाल SDEV_TRANSPORT_OFFLINE:
		/*
		 * If the device is offline we refuse to process any
		 * commands.  The device must be brought online
		 * beक्रमe trying any recovery commands.
		 */
		अगर (!sdev->offline_alपढ़ोy) अणु
			sdev->offline_alपढ़ोy = true;
			sdev_prपूर्णांकk(KERN_ERR, sdev,
				    "rejecting I/O to offline device\n");
		पूर्ण
		वापस BLK_STS_IOERR;
	हाल SDEV_DEL:
		/*
		 * If the device is fully deleted, we refuse to
		 * process any commands as well.
		 */
		sdev_prपूर्णांकk(KERN_ERR, sdev,
			    "rejecting I/O to dead device\n");
		वापस BLK_STS_IOERR;
	हाल SDEV_BLOCK:
	हाल SDEV_CREATED_BLOCK:
		वापस BLK_STS_RESOURCE;
	हाल SDEV_QUIESCE:
		/*
		 * If the device is blocked we only accept घातer management
		 * commands.
		 */
		अगर (req && WARN_ON_ONCE(!(req->rq_flags & RQF_PM)))
			वापस BLK_STS_RESOURCE;
		वापस BLK_STS_OK;
	शेष:
		/*
		 * For any other not fully online state we only allow
		 * घातer management commands.
		 */
		अगर (req && !(req->rq_flags & RQF_PM))
			वापस BLK_STS_IOERR;
		वापस BLK_STS_OK;
	पूर्ण
पूर्ण

/*
 * scsi_dev_queue_पढ़ोy: अगर we can send requests to sdev, assign one token
 * and वापस the token अन्यथा वापस -1.
 */
अटल अंतरभूत पूर्णांक scsi_dev_queue_पढ़ोy(काष्ठा request_queue *q,
				  काष्ठा scsi_device *sdev)
अणु
	पूर्णांक token;

	token = sbiपंचांगap_get(&sdev->budget_map);
	अगर (atomic_पढ़ो(&sdev->device_blocked)) अणु
		अगर (token < 0)
			जाओ out;

		अगर (scsi_device_busy(sdev) > 1)
			जाओ out_dec;

		/*
		 * unblock after device_blocked iterates to zero
		 */
		अगर (atomic_dec_वापस(&sdev->device_blocked) > 0)
			जाओ out_dec;
		SCSI_LOG_MLQUEUE(3, sdev_prपूर्णांकk(KERN_INFO, sdev,
				   "unblocking device at zero depth\n"));
	पूर्ण

	वापस token;
out_dec:
	अगर (token >= 0)
		sbiपंचांगap_put(&sdev->budget_map, token);
out:
	वापस -1;
पूर्ण

/*
 * scsi_target_queue_पढ़ोy: checks अगर there we can send commands to target
 * @sdev: scsi device on starget to check.
 */
अटल अंतरभूत पूर्णांक scsi_target_queue_पढ़ोy(काष्ठा Scsi_Host *shost,
					   काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_target *starget = scsi_target(sdev);
	अचिन्हित पूर्णांक busy;

	अगर (starget->single_lun) अणु
		spin_lock_irq(shost->host_lock);
		अगर (starget->starget_sdev_user &&
		    starget->starget_sdev_user != sdev) अणु
			spin_unlock_irq(shost->host_lock);
			वापस 0;
		पूर्ण
		starget->starget_sdev_user = sdev;
		spin_unlock_irq(shost->host_lock);
	पूर्ण

	अगर (starget->can_queue <= 0)
		वापस 1;

	busy = atomic_inc_वापस(&starget->target_busy) - 1;
	अगर (atomic_पढ़ो(&starget->target_blocked) > 0) अणु
		अगर (busy)
			जाओ starved;

		/*
		 * unblock after target_blocked iterates to zero
		 */
		अगर (atomic_dec_वापस(&starget->target_blocked) > 0)
			जाओ out_dec;

		SCSI_LOG_MLQUEUE(3, starget_prपूर्णांकk(KERN_INFO, starget,
				 "unblocking target at zero depth\n"));
	पूर्ण

	अगर (busy >= starget->can_queue)
		जाओ starved;

	वापस 1;

starved:
	spin_lock_irq(shost->host_lock);
	list_move_tail(&sdev->starved_entry, &shost->starved_list);
	spin_unlock_irq(shost->host_lock);
out_dec:
	अगर (starget->can_queue > 0)
		atomic_dec(&starget->target_busy);
	वापस 0;
पूर्ण

/*
 * scsi_host_queue_पढ़ोy: अगर we can send requests to shost, वापस 1 अन्यथा
 * वापस 0. We must end up running the queue again whenever 0 is
 * वापसed, अन्यथा IO can hang.
 */
अटल अंतरभूत पूर्णांक scsi_host_queue_पढ़ोy(काष्ठा request_queue *q,
				   काष्ठा Scsi_Host *shost,
				   काष्ठा scsi_device *sdev,
				   काष्ठा scsi_cmnd *cmd)
अणु
	अगर (scsi_host_in_recovery(shost))
		वापस 0;

	अगर (atomic_पढ़ो(&shost->host_blocked) > 0) अणु
		अगर (scsi_host_busy(shost) > 0)
			जाओ starved;

		/*
		 * unblock after host_blocked iterates to zero
		 */
		अगर (atomic_dec_वापस(&shost->host_blocked) > 0)
			जाओ out_dec;

		SCSI_LOG_MLQUEUE(3,
			shost_prपूर्णांकk(KERN_INFO, shost,
				     "unblocking host at zero depth\n"));
	पूर्ण

	अगर (shost->host_self_blocked)
		जाओ starved;

	/* We're OK to process the command, so we can't be starved */
	अगर (!list_empty(&sdev->starved_entry)) अणु
		spin_lock_irq(shost->host_lock);
		अगर (!list_empty(&sdev->starved_entry))
			list_del_init(&sdev->starved_entry);
		spin_unlock_irq(shost->host_lock);
	पूर्ण

	__set_bit(SCMD_STATE_INFLIGHT, &cmd->state);

	वापस 1;

starved:
	spin_lock_irq(shost->host_lock);
	अगर (list_empty(&sdev->starved_entry))
		list_add_tail(&sdev->starved_entry, &shost->starved_list);
	spin_unlock_irq(shost->host_lock);
out_dec:
	scsi_dec_host_busy(shost, cmd);
	वापस 0;
पूर्ण

/*
 * Busy state exporting function क्रम request stacking drivers.
 *
 * For efficiency, no lock is taken to check the busy state of
 * shost/starget/sdev, since the वापसed value is not guaranteed and
 * may be changed after request stacking drivers call the function,
 * regardless of taking lock or not.
 *
 * When scsi can't dispatch I/Os anymore and needs to समाप्त I/Os scsi
 * needs to वापस 'not busy'. Otherwise, request stacking drivers
 * may hold requests क्रमever.
 */
अटल bool scsi_mq_lld_busy(काष्ठा request_queue *q)
अणु
	काष्ठा scsi_device *sdev = q->queuedata;
	काष्ठा Scsi_Host *shost;

	अगर (blk_queue_dying(q))
		वापस false;

	shost = sdev->host;

	/*
	 * Ignore host/starget busy state.
	 * Since block layer करोes not have a concept of fairness across
	 * multiple queues, congestion of host/starget needs to be handled
	 * in SCSI layer.
	 */
	अगर (scsi_host_in_recovery(shost) || scsi_device_is_busy(sdev))
		वापस true;

	वापस false;
पूर्ण

/*
 * Block layer request completion callback. May be called from पूर्णांकerrupt
 * context.
 */
अटल व्योम scsi_complete(काष्ठा request *rq)
अणु
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);
	क्रमागत scsi_disposition disposition;

	INIT_LIST_HEAD(&cmd->eh_entry);

	atomic_inc(&cmd->device->ioकरोne_cnt);
	अगर (cmd->result)
		atomic_inc(&cmd->device->ioerr_cnt);

	disposition = scsi_decide_disposition(cmd);
	अगर (disposition != SUCCESS && scsi_cmd_runसमय_exceeced(cmd))
		disposition = SUCCESS;

	scsi_log_completion(cmd, disposition);

	चयन (disposition) अणु
	हाल SUCCESS:
		scsi_finish_command(cmd);
		अवरोध;
	हाल NEEDS_RETRY:
		scsi_queue_insert(cmd, SCSI_MLQUEUE_EH_RETRY);
		अवरोध;
	हाल ADD_TO_MLQUEUE:
		scsi_queue_insert(cmd, SCSI_MLQUEUE_DEVICE_BUSY);
		अवरोध;
	शेष:
		scsi_eh_scmd_add(cmd);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * scsi_dispatch_cmd - Dispatch a command to the low-level driver.
 * @cmd: command block we are dispatching.
 *
 * Return: nonzero वापस request was rejected and device's queue needs to be
 * plugged.
 */
अटल पूर्णांक scsi_dispatch_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	पूर्णांक rtn = 0;

	atomic_inc(&cmd->device->iorequest_cnt);

	/* check अगर the device is still usable */
	अगर (unlikely(cmd->device->sdev_state == SDEV_DEL)) अणु
		/* in SDEV_DEL we error all commands. DID_NO_CONNECT
		 * वापसs an immediate error upwards, and संकेतs
		 * that the device is no दीर्घer present */
		cmd->result = DID_NO_CONNECT << 16;
		जाओ करोne;
	पूर्ण

	/* Check to see अगर the scsi lld made this device blocked. */
	अगर (unlikely(scsi_device_blocked(cmd->device))) अणु
		/*
		 * in blocked state, the command is just put back on
		 * the device queue.  The suspend state has alपढ़ोy
		 * blocked the queue so future requests should not
		 * occur until the device transitions out of the
		 * suspend state.
		 */
		SCSI_LOG_MLQUEUE(3, scmd_prपूर्णांकk(KERN_INFO, cmd,
			"queuecommand : device blocked\n"));
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण

	/* Store the LUN value in cmnd, अगर needed. */
	अगर (cmd->device->lun_in_cdb)
		cmd->cmnd[1] = (cmd->cmnd[1] & 0x1f) |
			       (cmd->device->lun << 5 & 0xe0);

	scsi_log_send(cmd);

	/*
	 * Beक्रमe we queue this command, check अगर the command
	 * length exceeds what the host adapter can handle.
	 */
	अगर (cmd->cmd_len > cmd->device->host->max_cmd_len) अणु
		SCSI_LOG_MLQUEUE(3, scmd_prपूर्णांकk(KERN_INFO, cmd,
			       "queuecommand : command too long. "
			       "cdb_size=%d host->max_cmd_len=%d\n",
			       cmd->cmd_len, cmd->device->host->max_cmd_len));
		cmd->result = (DID_ABORT << 16);
		जाओ करोne;
	पूर्ण

	अगर (unlikely(host->shost_state == SHOST_DEL)) अणु
		cmd->result = (DID_NO_CONNECT << 16);
		जाओ करोne;

	पूर्ण

	trace_scsi_dispatch_cmd_start(cmd);
	rtn = host->hostt->queuecommand(host, cmd);
	अगर (rtn) अणु
		trace_scsi_dispatch_cmd_error(cmd, rtn);
		अगर (rtn != SCSI_MLQUEUE_DEVICE_BUSY &&
		    rtn != SCSI_MLQUEUE_TARGET_BUSY)
			rtn = SCSI_MLQUEUE_HOST_BUSY;

		SCSI_LOG_MLQUEUE(3, scmd_prपूर्णांकk(KERN_INFO, cmd,
			"queuecommand : request rejected\n"));
	पूर्ण

	वापस rtn;
 करोne:
	cmd->scsi_करोne(cmd);
	वापस 0;
पूर्ण

/* Size in bytes of the sg-list stored in the scsi-mq command-निजी data. */
अटल अचिन्हित पूर्णांक scsi_mq_अंतरभूत_sgl_size(काष्ठा Scsi_Host *shost)
अणु
	वापस min_t(अचिन्हित पूर्णांक, shost->sg_tablesize, SCSI_INLINE_SG_CNT) *
		माप(काष्ठा scatterlist);
पूर्ण

अटल blk_status_t scsi_prepare_cmd(काष्ठा request *req)
अणु
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);
	काष्ठा scsi_device *sdev = req->q->queuedata;
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा scatterlist *sg;

	scsi_init_command(sdev, cmd);

	cmd->request = req;
	cmd->tag = req->tag;
	cmd->prot_op = SCSI_PROT_NORMAL;
	अगर (blk_rq_bytes(req))
		cmd->sc_data_direction = rq_dma_dir(req);
	अन्यथा
		cmd->sc_data_direction = DMA_NONE;

	sg = (व्योम *)cmd + माप(काष्ठा scsi_cmnd) + shost->hostt->cmd_size;
	cmd->sdb.table.sgl = sg;

	अगर (scsi_host_get_prot(shost)) अणु
		स_रखो(cmd->prot_sdb, 0, माप(काष्ठा scsi_data_buffer));

		cmd->prot_sdb->table.sgl =
			(काष्ठा scatterlist *)(cmd->prot_sdb + 1);
	पूर्ण

	/*
	 * Special handling क्रम passthrough commands, which करोn't go to the ULP
	 * at all:
	 */
	अगर (blk_rq_is_scsi(req))
		वापस scsi_setup_scsi_cmnd(sdev, req);

	अगर (sdev->handler && sdev->handler->prep_fn) अणु
		blk_status_t ret = sdev->handler->prep_fn(sdev, req);

		अगर (ret != BLK_STS_OK)
			वापस ret;
	पूर्ण

	cmd->cmnd = scsi_req(req)->cmd = scsi_req(req)->__cmd;
	स_रखो(cmd->cmnd, 0, BLK_MAX_CDB);
	वापस scsi_cmd_to_driver(cmd)->init_command(cmd);
पूर्ण

अटल व्योम scsi_mq_करोne(काष्ठा scsi_cmnd *cmd)
अणु
	अगर (unlikely(blk_should_fake_समयout(cmd->request->q)))
		वापस;
	अगर (unlikely(test_and_set_bit(SCMD_STATE_COMPLETE, &cmd->state)))
		वापस;
	trace_scsi_dispatch_cmd_करोne(cmd);
	blk_mq_complete_request(cmd->request);
पूर्ण

अटल व्योम scsi_mq_put_budget(काष्ठा request_queue *q, पूर्णांक budget_token)
अणु
	काष्ठा scsi_device *sdev = q->queuedata;

	sbiपंचांगap_put(&sdev->budget_map, budget_token);
पूर्ण

अटल पूर्णांक scsi_mq_get_budget(काष्ठा request_queue *q)
अणु
	काष्ठा scsi_device *sdev = q->queuedata;
	पूर्णांक token = scsi_dev_queue_पढ़ोy(q, sdev);

	अगर (token >= 0)
		वापस token;

	atomic_inc(&sdev->restarts);

	/*
	 * Orders atomic_inc(&sdev->restarts) and atomic_पढ़ो(&sdev->device_busy).
	 * .restarts must be incremented beक्रमe .device_busy is पढ़ो because the
	 * code in scsi_run_queue_async() depends on the order of these operations.
	 */
	smp_mb__after_atomic();

	/*
	 * If all in-flight requests originated from this LUN are completed
	 * beक्रमe पढ़ोing .device_busy, sdev->device_busy will be observed as
	 * zero, then blk_mq_delay_run_hw_queues() will dispatch this request
	 * soon. Otherwise, completion of one of these requests will observe
	 * the .restarts flag, and the request queue will be run क्रम handling
	 * this request, see scsi_end_request().
	 */
	अगर (unlikely(scsi_device_busy(sdev) == 0 &&
				!scsi_device_blocked(sdev)))
		blk_mq_delay_run_hw_queues(sdev->request_queue, SCSI_QUEUE_DELAY);
	वापस -1;
पूर्ण

अटल व्योम scsi_mq_set_rq_budget_token(काष्ठा request *req, पूर्णांक token)
अणु
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);

	cmd->budget_token = token;
पूर्ण

अटल पूर्णांक scsi_mq_get_rq_budget_token(काष्ठा request *req)
अणु
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);

	वापस cmd->budget_token;
पूर्ण

अटल blk_status_t scsi_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *req = bd->rq;
	काष्ठा request_queue *q = req->q;
	काष्ठा scsi_device *sdev = q->queuedata;
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);
	blk_status_t ret;
	पूर्णांक reason;

	WARN_ON_ONCE(cmd->budget_token < 0);

	/*
	 * If the device is not in running state we will reject some or all
	 * commands.
	 */
	अगर (unlikely(sdev->sdev_state != SDEV_RUNNING)) अणु
		ret = scsi_device_state_check(sdev, req);
		अगर (ret != BLK_STS_OK)
			जाओ out_put_budget;
	पूर्ण

	ret = BLK_STS_RESOURCE;
	अगर (!scsi_target_queue_पढ़ोy(shost, sdev))
		जाओ out_put_budget;
	अगर (!scsi_host_queue_पढ़ोy(q, shost, sdev, cmd))
		जाओ out_dec_target_busy;

	अगर (!(req->rq_flags & RQF_DONTPREP)) अणु
		ret = scsi_prepare_cmd(req);
		अगर (ret != BLK_STS_OK)
			जाओ out_dec_host_busy;
		req->rq_flags |= RQF_DONTPREP;
	पूर्ण अन्यथा अणु
		clear_bit(SCMD_STATE_COMPLETE, &cmd->state);
	पूर्ण

	cmd->flags &= SCMD_PRESERVED_FLAGS;
	अगर (sdev->simple_tags)
		cmd->flags |= SCMD_TAGGED;
	अगर (bd->last)
		cmd->flags |= SCMD_LAST;

	scsi_set_resid(cmd, 0);
	स_रखो(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
	cmd->scsi_करोne = scsi_mq_करोne;

	blk_mq_start_request(req);
	reason = scsi_dispatch_cmd(cmd);
	अगर (reason) अणु
		scsi_set_blocked(cmd, reason);
		ret = BLK_STS_RESOURCE;
		जाओ out_dec_host_busy;
	पूर्ण

	वापस BLK_STS_OK;

out_dec_host_busy:
	scsi_dec_host_busy(shost, cmd);
out_dec_target_busy:
	अगर (scsi_target(sdev)->can_queue > 0)
		atomic_dec(&scsi_target(sdev)->target_busy);
out_put_budget:
	scsi_mq_put_budget(q, cmd->budget_token);
	cmd->budget_token = -1;
	चयन (ret) अणु
	हाल BLK_STS_OK:
		अवरोध;
	हाल BLK_STS_RESOURCE:
	हाल BLK_STS_ZONE_RESOURCE:
		अगर (scsi_device_blocked(sdev))
			ret = BLK_STS_DEV_RESOURCE;
		अवरोध;
	हाल BLK_STS_AGAIN:
		scsi_req(req)->result = DID_BUS_BUSY << 16;
		अगर (req->rq_flags & RQF_DONTPREP)
			scsi_mq_uninit_cmd(cmd);
		अवरोध;
	शेष:
		अगर (unlikely(!scsi_device_online(sdev)))
			scsi_req(req)->result = DID_NO_CONNECT << 16;
		अन्यथा
			scsi_req(req)->result = DID_ERROR << 16;
		/*
		 * Make sure to release all allocated resources when
		 * we hit an error, as we will never see this command
		 * again.
		 */
		अगर (req->rq_flags & RQF_DONTPREP)
			scsi_mq_uninit_cmd(cmd);
		scsi_run_queue_async(sdev);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस scsi_समयout(काष्ठा request *req,
		bool reserved)
अणु
	अगर (reserved)
		वापस BLK_EH_RESET_TIMER;
	वापस scsi_बार_out(req);
पूर्ण

अटल पूर्णांक scsi_mq_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
				अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा Scsi_Host *shost = set->driver_data;
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);
	काष्ठा scatterlist *sg;
	पूर्णांक ret = 0;

	cmd->sense_buffer =
		kmem_cache_alloc_node(scsi_sense_cache, GFP_KERNEL, numa_node);
	अगर (!cmd->sense_buffer)
		वापस -ENOMEM;
	cmd->req.sense = cmd->sense_buffer;

	अगर (scsi_host_get_prot(shost)) अणु
		sg = (व्योम *)cmd + माप(काष्ठा scsi_cmnd) +
			shost->hostt->cmd_size;
		cmd->prot_sdb = (व्योम *)sg + scsi_mq_अंतरभूत_sgl_size(shost);
	पूर्ण

	अगर (shost->hostt->init_cmd_priv) अणु
		ret = shost->hostt->init_cmd_priv(shost, cmd);
		अगर (ret < 0)
			kmem_cache_मुक्त(scsi_sense_cache, cmd->sense_buffer);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम scsi_mq_निकास_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
				 अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा Scsi_Host *shost = set->driver_data;
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);

	अगर (shost->hostt->निकास_cmd_priv)
		shost->hostt->निकास_cmd_priv(shost, cmd);
	kmem_cache_मुक्त(scsi_sense_cache, cmd->sense_buffer);
पूर्ण


अटल पूर्णांक scsi_mq_poll(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा Scsi_Host *shost = hctx->driver_data;

	अगर (shost->hostt->mq_poll)
		वापस shost->hostt->mq_poll(shost, hctx->queue_num);

	वापस 0;
पूर्ण

अटल पूर्णांक scsi_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
			  अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा Scsi_Host *shost = data;

	hctx->driver_data = shost;
	वापस 0;
पूर्ण

अटल पूर्णांक scsi_map_queues(काष्ठा blk_mq_tag_set *set)
अणु
	काष्ठा Scsi_Host *shost = container_of(set, काष्ठा Scsi_Host, tag_set);

	अगर (shost->hostt->map_queues)
		वापस shost->hostt->map_queues(shost);
	वापस blk_mq_map_queues(&set->map[HCTX_TYPE_DEFAULT]);
पूर्ण

व्योम __scsi_init_queue(काष्ठा Scsi_Host *shost, काष्ठा request_queue *q)
अणु
	काष्ठा device *dev = shost->dma_dev;

	/*
	 * this limit is imposed by hardware restrictions
	 */
	blk_queue_max_segments(q, min_t(अचिन्हित लघु, shost->sg_tablesize,
					SG_MAX_SEGMENTS));

	अगर (scsi_host_prot_dma(shost)) अणु
		shost->sg_prot_tablesize =
			min_not_zero(shost->sg_prot_tablesize,
				     (अचिन्हित लघु)SCSI_MAX_PROT_SG_SEGMENTS);
		BUG_ON(shost->sg_prot_tablesize < shost->sg_tablesize);
		blk_queue_max_पूर्णांकegrity_segments(q, shost->sg_prot_tablesize);
	पूर्ण

	अगर (dev->dma_mask) अणु
		shost->max_sectors = min_t(अचिन्हित पूर्णांक, shost->max_sectors,
				dma_max_mapping_size(dev) >> SECTOR_SHIFT);
	पूर्ण
	blk_queue_max_hw_sectors(q, shost->max_sectors);
	blk_queue_segment_boundary(q, shost->dma_boundary);
	dma_set_seg_boundary(dev, shost->dma_boundary);

	blk_queue_max_segment_size(q, shost->max_segment_size);
	blk_queue_virt_boundary(q, shost->virt_boundary_mask);
	dma_set_max_seg_size(dev, queue_max_segment_size(q));

	/*
	 * Set a reasonable शेष alignment:  The larger of 32-byte (dword),
	 * which is a common minimum क्रम HBAs, and the minimum DMA alignment,
	 * which is set by the platक्रमm.
	 *
	 * Devices that require a bigger alignment can increase it later.
	 */
	blk_queue_dma_alignment(q, max(4, dma_get_cache_alignment()) - 1);
पूर्ण
EXPORT_SYMBOL_GPL(__scsi_init_queue);

अटल स्थिर काष्ठा blk_mq_ops scsi_mq_ops_no_commit = अणु
	.get_budget	= scsi_mq_get_budget,
	.put_budget	= scsi_mq_put_budget,
	.queue_rq	= scsi_queue_rq,
	.complete	= scsi_complete,
	.समयout	= scsi_समयout,
#अगर_घोषित CONFIG_BLK_DEBUG_FS
	.show_rq	= scsi_show_rq,
#पूर्ण_अगर
	.init_request	= scsi_mq_init_request,
	.निकास_request	= scsi_mq_निकास_request,
	.initialize_rq_fn = scsi_initialize_rq,
	.cleanup_rq	= scsi_cleanup_rq,
	.busy		= scsi_mq_lld_busy,
	.map_queues	= scsi_map_queues,
	.init_hctx	= scsi_init_hctx,
	.poll		= scsi_mq_poll,
	.set_rq_budget_token = scsi_mq_set_rq_budget_token,
	.get_rq_budget_token = scsi_mq_get_rq_budget_token,
पूर्ण;


अटल व्योम scsi_commit_rqs(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा Scsi_Host *shost = hctx->driver_data;

	shost->hostt->commit_rqs(shost, hctx->queue_num);
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops scsi_mq_ops = अणु
	.get_budget	= scsi_mq_get_budget,
	.put_budget	= scsi_mq_put_budget,
	.queue_rq	= scsi_queue_rq,
	.commit_rqs	= scsi_commit_rqs,
	.complete	= scsi_complete,
	.समयout	= scsi_समयout,
#अगर_घोषित CONFIG_BLK_DEBUG_FS
	.show_rq	= scsi_show_rq,
#पूर्ण_अगर
	.init_request	= scsi_mq_init_request,
	.निकास_request	= scsi_mq_निकास_request,
	.initialize_rq_fn = scsi_initialize_rq,
	.cleanup_rq	= scsi_cleanup_rq,
	.busy		= scsi_mq_lld_busy,
	.map_queues	= scsi_map_queues,
	.init_hctx	= scsi_init_hctx,
	.poll		= scsi_mq_poll,
	.set_rq_budget_token = scsi_mq_set_rq_budget_token,
	.get_rq_budget_token = scsi_mq_get_rq_budget_token,
पूर्ण;

काष्ठा request_queue *scsi_mq_alloc_queue(काष्ठा scsi_device *sdev)
अणु
	sdev->request_queue = blk_mq_init_queue(&sdev->host->tag_set);
	अगर (IS_ERR(sdev->request_queue))
		वापस शून्य;

	sdev->request_queue->queuedata = sdev;
	__scsi_init_queue(sdev->host, sdev->request_queue);
	blk_queue_flag_set(QUEUE_FLAG_SCSI_PASSTHROUGH, sdev->request_queue);
	वापस sdev->request_queue;
पूर्ण

पूर्णांक scsi_mq_setup_tags(काष्ठा Scsi_Host *shost)
अणु
	अचिन्हित पूर्णांक cmd_size, sgl_size;
	काष्ठा blk_mq_tag_set *tag_set = &shost->tag_set;

	sgl_size = max_t(अचिन्हित पूर्णांक, माप(काष्ठा scatterlist),
				scsi_mq_अंतरभूत_sgl_size(shost));
	cmd_size = माप(काष्ठा scsi_cmnd) + shost->hostt->cmd_size + sgl_size;
	अगर (scsi_host_get_prot(shost))
		cmd_size += माप(काष्ठा scsi_data_buffer) +
			माप(काष्ठा scatterlist) * SCSI_INLINE_PROT_SG_CNT;

	स_रखो(tag_set, 0, माप(*tag_set));
	अगर (shost->hostt->commit_rqs)
		tag_set->ops = &scsi_mq_ops;
	अन्यथा
		tag_set->ops = &scsi_mq_ops_no_commit;
	tag_set->nr_hw_queues = shost->nr_hw_queues ? : 1;
	tag_set->nr_maps = shost->nr_maps ? : 1;
	tag_set->queue_depth = shost->can_queue;
	tag_set->cmd_size = cmd_size;
	tag_set->numa_node = NUMA_NO_NODE;
	tag_set->flags = BLK_MQ_F_SHOULD_MERGE;
	tag_set->flags |=
		BLK_ALLOC_POLICY_TO_MQ_FLAG(shost->hostt->tag_alloc_policy);
	tag_set->driver_data = shost;
	अगर (shost->host_tagset)
		tag_set->flags |= BLK_MQ_F_TAG_HCTX_SHARED;

	वापस blk_mq_alloc_tag_set(tag_set);
पूर्ण

व्योम scsi_mq_destroy_tags(काष्ठा Scsi_Host *shost)
अणु
	blk_mq_मुक्त_tag_set(&shost->tag_set);
पूर्ण

/**
 * scsi_device_from_queue - वापस sdev associated with a request_queue
 * @q: The request queue to वापस the sdev from
 *
 * Return the sdev associated with a request queue or शून्य अगर the
 * request_queue करोes not reference a SCSI device.
 */
काष्ठा scsi_device *scsi_device_from_queue(काष्ठा request_queue *q)
अणु
	काष्ठा scsi_device *sdev = शून्य;

	अगर (q->mq_ops == &scsi_mq_ops_no_commit ||
	    q->mq_ops == &scsi_mq_ops)
		sdev = q->queuedata;
	अगर (!sdev || !get_device(&sdev->sdev_gendev))
		sdev = शून्य;

	वापस sdev;
पूर्ण

/**
 * scsi_block_requests - Utility function used by low-level drivers to prevent
 * further commands from being queued to the device.
 * @shost:  host in question
 *
 * There is no समयr nor any other means by which the requests get unblocked
 * other than the low-level driver calling scsi_unblock_requests().
 */
व्योम scsi_block_requests(काष्ठा Scsi_Host *shost)
अणु
	shost->host_self_blocked = 1;
पूर्ण
EXPORT_SYMBOL(scsi_block_requests);

/**
 * scsi_unblock_requests - Utility function used by low-level drivers to allow
 * further commands to be queued to the device.
 * @shost:  host in question
 *
 * There is no समयr nor any other means by which the requests get unblocked
 * other than the low-level driver calling scsi_unblock_requests(). This is करोne
 * as an API function so that changes to the पूर्णांकernals of the scsi mid-layer
 * won't require wholesale changes to drivers that use this feature.
 */
व्योम scsi_unblock_requests(काष्ठा Scsi_Host *shost)
अणु
	shost->host_self_blocked = 0;
	scsi_run_host_queues(shost);
पूर्ण
EXPORT_SYMBOL(scsi_unblock_requests);

व्योम scsi_निकास_queue(व्योम)
अणु
	kmem_cache_destroy(scsi_sense_cache);
पूर्ण

/**
 *	scsi_mode_select - issue a mode select
 *	@sdev:	SCSI device to be queried
 *	@pf:	Page क्रमmat bit (1 == standard, 0 == venकरोr specअगरic)
 *	@sp:	Save page bit (0 == करोn't save, 1 == save)
 *	@modepage: mode page being requested
 *	@buffer: request buffer (may not be smaller than eight bytes)
 *	@len:	length of request buffer.
 *	@समयout: command समयout
 *	@retries: number of retries beक्रमe failing
 *	@data: वापसs a काष्ठाure असलtracting the mode header data
 *	@sshdr: place to put sense data (or शून्य अगर no sense to be collected).
 *		must be SCSI_SENSE_BUFFERSIZE big.
 *
 *	Returns zero अगर successful; negative error number or scsi
 *	status on error
 *
 */
पूर्णांक
scsi_mode_select(काष्ठा scsi_device *sdev, पूर्णांक pf, पूर्णांक sp, पूर्णांक modepage,
		 अचिन्हित अक्षर *buffer, पूर्णांक len, पूर्णांक समयout, पूर्णांक retries,
		 काष्ठा scsi_mode_data *data, काष्ठा scsi_sense_hdr *sshdr)
अणु
	अचिन्हित अक्षर cmd[10];
	अचिन्हित अक्षर *real_buffer;
	पूर्णांक ret;

	स_रखो(cmd, 0, माप(cmd));
	cmd[1] = (pf ? 0x10 : 0) | (sp ? 0x01 : 0);

	अगर (sdev->use_10_क्रम_ms) अणु
		अगर (len > 65535)
			वापस -EINVAL;
		real_buffer = kदो_स्मृति(8 + len, GFP_KERNEL);
		अगर (!real_buffer)
			वापस -ENOMEM;
		स_नकल(real_buffer + 8, buffer, len);
		len += 8;
		real_buffer[0] = 0;
		real_buffer[1] = 0;
		real_buffer[2] = data->medium_type;
		real_buffer[3] = data->device_specअगरic;
		real_buffer[4] = data->दीर्घlba ? 0x01 : 0;
		real_buffer[5] = 0;
		real_buffer[6] = data->block_descriptor_length >> 8;
		real_buffer[7] = data->block_descriptor_length;

		cmd[0] = MODE_SELECT_10;
		cmd[7] = len >> 8;
		cmd[8] = len;
	पूर्ण अन्यथा अणु
		अगर (len > 255 || data->block_descriptor_length > 255 ||
		    data->दीर्घlba)
			वापस -EINVAL;

		real_buffer = kदो_स्मृति(4 + len, GFP_KERNEL);
		अगर (!real_buffer)
			वापस -ENOMEM;
		स_नकल(real_buffer + 4, buffer, len);
		len += 4;
		real_buffer[0] = 0;
		real_buffer[1] = data->medium_type;
		real_buffer[2] = data->device_specअगरic;
		real_buffer[3] = data->block_descriptor_length;

		cmd[0] = MODE_SELECT;
		cmd[4] = len;
	पूर्ण

	ret = scsi_execute_req(sdev, cmd, DMA_TO_DEVICE, real_buffer, len,
			       sshdr, समयout, retries, शून्य);
	kमुक्त(real_buffer);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_mode_select);

/**
 *	scsi_mode_sense - issue a mode sense, falling back from 10 to six bytes अगर necessary.
 *	@sdev:	SCSI device to be queried
 *	@dbd:	set अगर mode sense will allow block descriptors to be वापसed
 *	@modepage: mode page being requested
 *	@buffer: request buffer (may not be smaller than eight bytes)
 *	@len:	length of request buffer.
 *	@समयout: command समयout
 *	@retries: number of retries beक्रमe failing
 *	@data: वापसs a काष्ठाure असलtracting the mode header data
 *	@sshdr: place to put sense data (or शून्य अगर no sense to be collected).
 *		must be SCSI_SENSE_BUFFERSIZE big.
 *
 *	Returns zero अगर unsuccessful, or the header offset (either 4
 *	or 8 depending on whether a six or ten byte command was
 *	issued) अगर successful.
 */
पूर्णांक
scsi_mode_sense(काष्ठा scsi_device *sdev, पूर्णांक dbd, पूर्णांक modepage,
		  अचिन्हित अक्षर *buffer, पूर्णांक len, पूर्णांक समयout, पूर्णांक retries,
		  काष्ठा scsi_mode_data *data, काष्ठा scsi_sense_hdr *sshdr)
अणु
	अचिन्हित अक्षर cmd[12];
	पूर्णांक use_10_क्रम_ms;
	पूर्णांक header_length;
	पूर्णांक result, retry_count = retries;
	काष्ठा scsi_sense_hdr my_sshdr;

	स_रखो(data, 0, माप(*data));
	स_रखो(&cmd[0], 0, 12);

	dbd = sdev->set_dbd_क्रम_ms ? 8 : dbd;
	cmd[1] = dbd & 0x18;	/* allows DBD and LLBA bits */
	cmd[2] = modepage;

	/* caller might not be पूर्णांकerested in sense, but we need it */
	अगर (!sshdr)
		sshdr = &my_sshdr;

 retry:
	use_10_क्रम_ms = sdev->use_10_क्रम_ms;

	अगर (use_10_क्रम_ms) अणु
		अगर (len < 8)
			len = 8;

		cmd[0] = MODE_SENSE_10;
		cmd[8] = len;
		header_length = 8;
	पूर्ण अन्यथा अणु
		अगर (len < 4)
			len = 4;

		cmd[0] = MODE_SENSE;
		cmd[4] = len;
		header_length = 4;
	पूर्ण

	स_रखो(buffer, 0, len);

	result = scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buffer, len,
				  sshdr, समयout, retries, शून्य);

	/* This code looks awful: what it's करोing is making sure an
	 * ILLEGAL REQUEST sense वापस identअगरies the actual command
	 * byte as the problem.  MODE_SENSE commands can वापस
	 * ILLEGAL REQUEST अगर the code page isn't supported */

	अगर (use_10_क्रम_ms && !scsi_status_is_good(result) &&
	    driver_byte(result) == DRIVER_SENSE) अणु
		अगर (scsi_sense_valid(sshdr)) अणु
			अगर ((sshdr->sense_key == ILLEGAL_REQUEST) &&
			    (sshdr->asc == 0x20) && (sshdr->ascq == 0)) अणु
				/*
				 * Invalid command operation code
				 */
				sdev->use_10_क्रम_ms = 0;
				जाओ retry;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (scsi_status_is_good(result)) अणु
		अगर (unlikely(buffer[0] == 0x86 && buffer[1] == 0x0b &&
			     (modepage == 6 || modepage == 8))) अणु
			/* Initio अवरोधage? */
			header_length = 0;
			data->length = 13;
			data->medium_type = 0;
			data->device_specअगरic = 0;
			data->दीर्घlba = 0;
			data->block_descriptor_length = 0;
		पूर्ण अन्यथा अगर (use_10_क्रम_ms) अणु
			data->length = buffer[0]*256 + buffer[1] + 2;
			data->medium_type = buffer[2];
			data->device_specअगरic = buffer[3];
			data->दीर्घlba = buffer[4] & 0x01;
			data->block_descriptor_length = buffer[6]*256
				+ buffer[7];
		पूर्ण अन्यथा अणु
			data->length = buffer[0] + 1;
			data->medium_type = buffer[1];
			data->device_specअगरic = buffer[2];
			data->block_descriptor_length = buffer[3];
		पूर्ण
		data->header_length = header_length;
	पूर्ण अन्यथा अगर ((status_byte(result) == CHECK_CONDITION) &&
		   scsi_sense_valid(sshdr) &&
		   sshdr->sense_key == UNIT_ATTENTION && retry_count) अणु
		retry_count--;
		जाओ retry;
	पूर्ण

	वापस result;
पूर्ण
EXPORT_SYMBOL(scsi_mode_sense);

/**
 *	scsi_test_unit_पढ़ोy - test अगर unit is पढ़ोy
 *	@sdev:	scsi device to change the state of.
 *	@समयout: command समयout
 *	@retries: number of retries beक्रमe failing
 *	@sshdr: outpout poपूर्णांकer क्रम decoded sense inक्रमmation.
 *
 *	Returns zero अगर unsuccessful or an error अगर TUR failed.  For
 *	removable media, UNIT_ATTENTION sets ->changed flag.
 **/
पूर्णांक
scsi_test_unit_पढ़ोy(काष्ठा scsi_device *sdev, पूर्णांक समयout, पूर्णांक retries,
		     काष्ठा scsi_sense_hdr *sshdr)
अणु
	अक्षर cmd[] = अणु
		TEST_UNIT_READY, 0, 0, 0, 0, 0,
	पूर्ण;
	पूर्णांक result;

	/* try to eat the UNIT_ATTENTION अगर there are enough retries */
	करो अणु
		result = scsi_execute_req(sdev, cmd, DMA_NONE, शून्य, 0, sshdr,
					  समयout, 1, शून्य);
		अगर (sdev->removable && scsi_sense_valid(sshdr) &&
		    sshdr->sense_key == UNIT_ATTENTION)
			sdev->changed = 1;
	पूर्ण जबतक (scsi_sense_valid(sshdr) &&
		 sshdr->sense_key == UNIT_ATTENTION && --retries);

	वापस result;
पूर्ण
EXPORT_SYMBOL(scsi_test_unit_पढ़ोy);

/**
 *	scsi_device_set_state - Take the given device through the device state model.
 *	@sdev:	scsi device to change the state of.
 *	@state:	state to change to.
 *
 *	Returns zero अगर successful or an error अगर the requested
 *	transition is illegal.
 */
पूर्णांक
scsi_device_set_state(काष्ठा scsi_device *sdev, क्रमागत scsi_device_state state)
अणु
	क्रमागत scsi_device_state oldstate = sdev->sdev_state;

	अगर (state == oldstate)
		वापस 0;

	चयन (state) अणु
	हाल SDEV_CREATED:
		चयन (oldstate) अणु
		हाल SDEV_CREATED_BLOCK:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SDEV_RUNNING:
		चयन (oldstate) अणु
		हाल SDEV_CREATED:
		हाल SDEV_OFFLINE:
		हाल SDEV_TRANSPORT_OFFLINE:
		हाल SDEV_QUIESCE:
		हाल SDEV_BLOCK:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SDEV_QUIESCE:
		चयन (oldstate) अणु
		हाल SDEV_RUNNING:
		हाल SDEV_OFFLINE:
		हाल SDEV_TRANSPORT_OFFLINE:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SDEV_OFFLINE:
	हाल SDEV_TRANSPORT_OFFLINE:
		चयन (oldstate) अणु
		हाल SDEV_CREATED:
		हाल SDEV_RUNNING:
		हाल SDEV_QUIESCE:
		हाल SDEV_BLOCK:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SDEV_BLOCK:
		चयन (oldstate) अणु
		हाल SDEV_RUNNING:
		हाल SDEV_CREATED_BLOCK:
		हाल SDEV_QUIESCE:
		हाल SDEV_OFFLINE:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SDEV_CREATED_BLOCK:
		चयन (oldstate) अणु
		हाल SDEV_CREATED:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SDEV_CANCEL:
		चयन (oldstate) अणु
		हाल SDEV_CREATED:
		हाल SDEV_RUNNING:
		हाल SDEV_QUIESCE:
		हाल SDEV_OFFLINE:
		हाल SDEV_TRANSPORT_OFFLINE:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SDEV_DEL:
		चयन (oldstate) अणु
		हाल SDEV_CREATED:
		हाल SDEV_RUNNING:
		हाल SDEV_OFFLINE:
		हाल SDEV_TRANSPORT_OFFLINE:
		हाल SDEV_CANCEL:
		हाल SDEV_BLOCK:
		हाल SDEV_CREATED_BLOCK:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	पूर्ण
	sdev->offline_alपढ़ोy = false;
	sdev->sdev_state = state;
	वापस 0;

 illegal:
	SCSI_LOG_ERROR_RECOVERY(1,
				sdev_prपूर्णांकk(KERN_ERR, sdev,
					    "Illegal state transition %s->%s",
					    scsi_device_state_name(oldstate),
					    scsi_device_state_name(state))
				);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(scsi_device_set_state);

/**
 *	scsi_evt_emit - emit a single SCSI device uevent
 *	@sdev: associated SCSI device
 *	@evt: event to emit
 *
 *	Send a single uevent (scsi_event) to the associated scsi_device.
 */
अटल व्योम scsi_evt_emit(काष्ठा scsi_device *sdev, काष्ठा scsi_event *evt)
अणु
	पूर्णांक idx = 0;
	अक्षर *envp[3];

	चयन (evt->evt_type) अणु
	हाल SDEV_EVT_MEDIA_CHANGE:
		envp[idx++] = "SDEV_MEDIA_CHANGE=1";
		अवरोध;
	हाल SDEV_EVT_INQUIRY_CHANGE_REPORTED:
		scsi_rescan_device(&sdev->sdev_gendev);
		envp[idx++] = "SDEV_UA=INQUIRY_DATA_HAS_CHANGED";
		अवरोध;
	हाल SDEV_EVT_CAPACITY_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=CAPACITY_DATA_HAS_CHANGED";
		अवरोध;
	हाल SDEV_EVT_SOFT_THRESHOLD_REACHED_REPORTED:
	       envp[idx++] = "SDEV_UA=THIN_PROVISIONING_SOFT_THRESHOLD_REACHED";
		अवरोध;
	हाल SDEV_EVT_MODE_PARAMETER_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=MODE_PARAMETERS_CHANGED";
		अवरोध;
	हाल SDEV_EVT_LUN_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=REPORTED_LUNS_DATA_HAS_CHANGED";
		अवरोध;
	हाल SDEV_EVT_ALUA_STATE_CHANGE_REPORTED:
		envp[idx++] = "SDEV_UA=ASYMMETRIC_ACCESS_STATE_CHANGED";
		अवरोध;
	हाल SDEV_EVT_POWER_ON_RESET_OCCURRED:
		envp[idx++] = "SDEV_UA=POWER_ON_RESET_OCCURRED";
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	envp[idx++] = शून्य;

	kobject_uevent_env(&sdev->sdev_gendev.kobj, KOBJ_CHANGE, envp);
पूर्ण

/**
 *	scsi_evt_thपढ़ो - send a uevent क्रम each scsi event
 *	@work: work काष्ठा क्रम scsi_device
 *
 *	Dispatch queued events to their associated scsi_device kobjects
 *	as uevents.
 */
व्योम scsi_evt_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_device *sdev;
	क्रमागत scsi_device_event evt_type;
	LIST_HEAD(event_list);

	sdev = container_of(work, काष्ठा scsi_device, event_work);

	क्रम (evt_type = SDEV_EVT_FIRST; evt_type <= SDEV_EVT_LAST; evt_type++)
		अगर (test_and_clear_bit(evt_type, sdev->pending_events))
			sdev_evt_send_simple(sdev, evt_type, GFP_KERNEL);

	जबतक (1) अणु
		काष्ठा scsi_event *evt;
		काष्ठा list_head *this, *पंचांगp;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&sdev->list_lock, flags);
		list_splice_init(&sdev->event_list, &event_list);
		spin_unlock_irqrestore(&sdev->list_lock, flags);

		अगर (list_empty(&event_list))
			अवरोध;

		list_क्रम_each_safe(this, पंचांगp, &event_list) अणु
			evt = list_entry(this, काष्ठा scsi_event, node);
			list_del(&evt->node);
			scsi_evt_emit(sdev, evt);
			kमुक्त(evt);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * 	sdev_evt_send - send निश्चितed event to uevent thपढ़ो
 *	@sdev: scsi_device event occurred on
 *	@evt: event to send
 *
 *	Assert scsi device event asynchronously.
 */
व्योम sdev_evt_send(काष्ठा scsi_device *sdev, काष्ठा scsi_event *evt)
अणु
	अचिन्हित दीर्घ flags;

#अगर 0
	/* FIXME: currently this check eliminates all media change events
	 * क्रम polled devices.  Need to update to discriminate between AN
	 * and polled events */
	अगर (!test_bit(evt->evt_type, sdev->supported_events)) अणु
		kमुक्त(evt);
		वापस;
	पूर्ण
#पूर्ण_अगर

	spin_lock_irqsave(&sdev->list_lock, flags);
	list_add_tail(&evt->node, &sdev->event_list);
	schedule_work(&sdev->event_work);
	spin_unlock_irqrestore(&sdev->list_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sdev_evt_send);

/**
 * 	sdev_evt_alloc - allocate a new scsi event
 *	@evt_type: type of event to allocate
 *	@gfpflags: GFP flags क्रम allocation
 *
 *	Allocates and वापसs a new scsi_event.
 */
काष्ठा scsi_event *sdev_evt_alloc(क्रमागत scsi_device_event evt_type,
				  gfp_t gfpflags)
अणु
	काष्ठा scsi_event *evt = kzalloc(माप(काष्ठा scsi_event), gfpflags);
	अगर (!evt)
		वापस शून्य;

	evt->evt_type = evt_type;
	INIT_LIST_HEAD(&evt->node);

	/* evt_type-specअगरic initialization, अगर any */
	चयन (evt_type) अणु
	हाल SDEV_EVT_MEDIA_CHANGE:
	हाल SDEV_EVT_INQUIRY_CHANGE_REPORTED:
	हाल SDEV_EVT_CAPACITY_CHANGE_REPORTED:
	हाल SDEV_EVT_SOFT_THRESHOLD_REACHED_REPORTED:
	हाल SDEV_EVT_MODE_PARAMETER_CHANGE_REPORTED:
	हाल SDEV_EVT_LUN_CHANGE_REPORTED:
	हाल SDEV_EVT_ALUA_STATE_CHANGE_REPORTED:
	हाल SDEV_EVT_POWER_ON_RESET_OCCURRED:
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	वापस evt;
पूर्ण
EXPORT_SYMBOL_GPL(sdev_evt_alloc);

/**
 * 	sdev_evt_send_simple - send निश्चितed event to uevent thपढ़ो
 *	@sdev: scsi_device event occurred on
 *	@evt_type: type of event to send
 *	@gfpflags: GFP flags क्रम allocation
 *
 *	Assert scsi device event asynchronously, given an event type.
 */
व्योम sdev_evt_send_simple(काष्ठा scsi_device *sdev,
			  क्रमागत scsi_device_event evt_type, gfp_t gfpflags)
अणु
	काष्ठा scsi_event *evt = sdev_evt_alloc(evt_type, gfpflags);
	अगर (!evt) अणु
		sdev_prपूर्णांकk(KERN_ERR, sdev, "event %d eaten due to OOM\n",
			    evt_type);
		वापस;
	पूर्ण

	sdev_evt_send(sdev, evt);
पूर्ण
EXPORT_SYMBOL_GPL(sdev_evt_send_simple);

/**
 *	scsi_device_quiesce - Block all commands except घातer management.
 *	@sdev:	scsi device to quiesce.
 *
 *	This works by trying to transition to the SDEV_QUIESCE state
 *	(which must be a legal transition).  When the device is in this
 *	state, only घातer management requests will be accepted, all others will
 *	be deferred.
 *
 *	Must be called with user context, may sleep.
 *
 *	Returns zero अगर unsuccessful or an error अगर not.
 */
पूर्णांक
scsi_device_quiesce(काष्ठा scsi_device *sdev)
अणु
	काष्ठा request_queue *q = sdev->request_queue;
	पूर्णांक err;

	/*
	 * It is allowed to call scsi_device_quiesce() multiple बार from
	 * the same context but concurrent scsi_device_quiesce() calls are
	 * not allowed.
	 */
	WARN_ON_ONCE(sdev->quiesced_by && sdev->quiesced_by != current);

	अगर (sdev->quiesced_by == current)
		वापस 0;

	blk_set_pm_only(q);

	blk_mq_मुक्तze_queue(q);
	/*
	 * Ensure that the effect of blk_set_pm_only() will be visible
	 * क्रम percpu_ref_tryget() callers that occur after the queue
	 * unमुक्तze even अगर the queue was alपढ़ोy frozen beक्रमe this function
	 * was called. See also https://lwn.net/Articles/573497/.
	 */
	synchronize_rcu();
	blk_mq_unमुक्तze_queue(q);

	mutex_lock(&sdev->state_mutex);
	err = scsi_device_set_state(sdev, SDEV_QUIESCE);
	अगर (err == 0)
		sdev->quiesced_by = current;
	अन्यथा
		blk_clear_pm_only(q);
	mutex_unlock(&sdev->state_mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(scsi_device_quiesce);

/**
 *	scsi_device_resume - Restart user issued commands to a quiesced device.
 *	@sdev:	scsi device to resume.
 *
 *	Moves the device from quiesced back to running and restarts the
 *	queues.
 *
 *	Must be called with user context, may sleep.
 */
व्योम scsi_device_resume(काष्ठा scsi_device *sdev)
अणु
	/* check अगर the device state was mutated prior to resume, and अगर
	 * so assume the state is being managed अन्यथाwhere (क्रम example
	 * device deleted during suspend)
	 */
	mutex_lock(&sdev->state_mutex);
	अगर (sdev->sdev_state == SDEV_QUIESCE)
		scsi_device_set_state(sdev, SDEV_RUNNING);
	अगर (sdev->quiesced_by) अणु
		sdev->quiesced_by = शून्य;
		blk_clear_pm_only(sdev->request_queue);
	पूर्ण
	mutex_unlock(&sdev->state_mutex);
पूर्ण
EXPORT_SYMBOL(scsi_device_resume);

अटल व्योम
device_quiesce_fn(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	scsi_device_quiesce(sdev);
पूर्ण

व्योम
scsi_target_quiesce(काष्ठा scsi_target *starget)
अणु
	starget_क्रम_each_device(starget, शून्य, device_quiesce_fn);
पूर्ण
EXPORT_SYMBOL(scsi_target_quiesce);

अटल व्योम
device_resume_fn(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	scsi_device_resume(sdev);
पूर्ण

व्योम
scsi_target_resume(काष्ठा scsi_target *starget)
अणु
	starget_क्रम_each_device(starget, शून्य, device_resume_fn);
पूर्ण
EXPORT_SYMBOL(scsi_target_resume);

/**
 * scsi_पूर्णांकernal_device_block_noरुको - try to transition to the SDEV_BLOCK state
 * @sdev: device to block
 *
 * Pause SCSI command processing on the specअगरied device. Does not sleep.
 *
 * Returns zero अगर successful or a negative error code upon failure.
 *
 * Notes:
 * This routine transitions the device to the SDEV_BLOCK state (which must be
 * a legal transition). When the device is in this state, command processing
 * is छोड़ोd until the device leaves the SDEV_BLOCK state. See also
 * scsi_पूर्णांकernal_device_unblock_noरुको().
 */
पूर्णांक scsi_पूर्णांकernal_device_block_noरुको(काष्ठा scsi_device *sdev)
अणु
	काष्ठा request_queue *q = sdev->request_queue;
	पूर्णांक err = 0;

	err = scsi_device_set_state(sdev, SDEV_BLOCK);
	अगर (err) अणु
		err = scsi_device_set_state(sdev, SDEV_CREATED_BLOCK);

		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * The device has transitioned to SDEV_BLOCK.  Stop the
	 * block layer from calling the midlayer with this device's
	 * request queue.
	 */
	blk_mq_quiesce_queue_noरुको(q);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_पूर्णांकernal_device_block_noरुको);

/**
 * scsi_पूर्णांकernal_device_block - try to transition to the SDEV_BLOCK state
 * @sdev: device to block
 *
 * Pause SCSI command processing on the specअगरied device and रुको until all
 * ongoing scsi_request_fn() / scsi_queue_rq() calls have finished. May sleep.
 *
 * Returns zero अगर successful or a negative error code upon failure.
 *
 * Note:
 * This routine transitions the device to the SDEV_BLOCK state (which must be
 * a legal transition). When the device is in this state, command processing
 * is छोड़ोd until the device leaves the SDEV_BLOCK state. See also
 * scsi_पूर्णांकernal_device_unblock().
 */
अटल पूर्णांक scsi_पूर्णांकernal_device_block(काष्ठा scsi_device *sdev)
अणु
	काष्ठा request_queue *q = sdev->request_queue;
	पूर्णांक err;

	mutex_lock(&sdev->state_mutex);
	err = scsi_पूर्णांकernal_device_block_noरुको(sdev);
	अगर (err == 0)
		blk_mq_quiesce_queue(q);
	mutex_unlock(&sdev->state_mutex);

	वापस err;
पूर्ण

व्योम scsi_start_queue(काष्ठा scsi_device *sdev)
अणु
	काष्ठा request_queue *q = sdev->request_queue;

	blk_mq_unquiesce_queue(q);
पूर्ण

/**
 * scsi_पूर्णांकernal_device_unblock_noरुको - resume a device after a block request
 * @sdev:	device to resume
 * @new_state:	state to set the device to after unblocking
 *
 * Restart the device queue क्रम a previously suspended SCSI device. Does not
 * sleep.
 *
 * Returns zero अगर successful or a negative error code upon failure.
 *
 * Notes:
 * This routine transitions the device to the SDEV_RUNNING state or to one of
 * the offline states (which must be a legal transition) allowing the midlayer
 * to goose the queue क्रम this device.
 */
पूर्णांक scsi_पूर्णांकernal_device_unblock_noरुको(काष्ठा scsi_device *sdev,
					क्रमागत scsi_device_state new_state)
अणु
	चयन (new_state) अणु
	हाल SDEV_RUNNING:
	हाल SDEV_TRANSPORT_OFFLINE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Try to transition the scsi device to SDEV_RUNNING or one of the
	 * offlined states and goose the device queue अगर successful.
	 */
	चयन (sdev->sdev_state) अणु
	हाल SDEV_BLOCK:
	हाल SDEV_TRANSPORT_OFFLINE:
		sdev->sdev_state = new_state;
		अवरोध;
	हाल SDEV_CREATED_BLOCK:
		अगर (new_state == SDEV_TRANSPORT_OFFLINE ||
		    new_state == SDEV_OFFLINE)
			sdev->sdev_state = new_state;
		अन्यथा
			sdev->sdev_state = SDEV_CREATED;
		अवरोध;
	हाल SDEV_CANCEL:
	हाल SDEV_OFFLINE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	scsi_start_queue(sdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_पूर्णांकernal_device_unblock_noरुको);

/**
 * scsi_पूर्णांकernal_device_unblock - resume a device after a block request
 * @sdev:	device to resume
 * @new_state:	state to set the device to after unblocking
 *
 * Restart the device queue क्रम a previously suspended SCSI device. May sleep.
 *
 * Returns zero अगर successful or a negative error code upon failure.
 *
 * Notes:
 * This routine transitions the device to the SDEV_RUNNING state or to one of
 * the offline states (which must be a legal transition) allowing the midlayer
 * to goose the queue क्रम this device.
 */
अटल पूर्णांक scsi_पूर्णांकernal_device_unblock(काष्ठा scsi_device *sdev,
					क्रमागत scsi_device_state new_state)
अणु
	पूर्णांक ret;

	mutex_lock(&sdev->state_mutex);
	ret = scsi_पूर्णांकernal_device_unblock_noरुको(sdev, new_state);
	mutex_unlock(&sdev->state_mutex);

	वापस ret;
पूर्ण

अटल व्योम
device_block(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	पूर्णांक ret;

	ret = scsi_पूर्णांकernal_device_block(sdev);

	WARN_ONCE(ret, "scsi_internal_device_block(%s) failed: ret = %d\n",
		  dev_name(&sdev->sdev_gendev), ret);
पूर्ण

अटल पूर्णांक
target_block(काष्ठा device *dev, व्योम *data)
अणु
	अगर (scsi_is_target_device(dev))
		starget_क्रम_each_device(to_scsi_target(dev), शून्य,
					device_block);
	वापस 0;
पूर्ण

व्योम
scsi_target_block(काष्ठा device *dev)
अणु
	अगर (scsi_is_target_device(dev))
		starget_क्रम_each_device(to_scsi_target(dev), शून्य,
					device_block);
	अन्यथा
		device_क्रम_each_child(dev, शून्य, target_block);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_target_block);

अटल व्योम
device_unblock(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	scsi_पूर्णांकernal_device_unblock(sdev, *(क्रमागत scsi_device_state *)data);
पूर्ण

अटल पूर्णांक
target_unblock(काष्ठा device *dev, व्योम *data)
अणु
	अगर (scsi_is_target_device(dev))
		starget_क्रम_each_device(to_scsi_target(dev), data,
					device_unblock);
	वापस 0;
पूर्ण

व्योम
scsi_target_unblock(काष्ठा device *dev, क्रमागत scsi_device_state new_state)
अणु
	अगर (scsi_is_target_device(dev))
		starget_क्रम_each_device(to_scsi_target(dev), &new_state,
					device_unblock);
	अन्यथा
		device_क्रम_each_child(dev, &new_state, target_unblock);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_target_unblock);

पूर्णांक
scsi_host_block(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक ret = 0;

	/*
	 * Call scsi_पूर्णांकernal_device_block_noरुको so we can aव्योम
	 * calling synchronize_rcu() क्रम each LUN.
	 */
	shost_क्रम_each_device(sdev, shost) अणु
		mutex_lock(&sdev->state_mutex);
		ret = scsi_पूर्णांकernal_device_block_noरुको(sdev);
		mutex_unlock(&sdev->state_mutex);
		अगर (ret) अणु
			scsi_device_put(sdev);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * SCSI never enables blk-mq's BLK_MQ_F_BLOCKING flag so
	 * calling synchronize_rcu() once is enough.
	 */
	WARN_ON_ONCE(shost->tag_set.flags & BLK_MQ_F_BLOCKING);

	अगर (!ret)
		synchronize_rcu();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_host_block);

पूर्णांक
scsi_host_unblock(काष्ठा Scsi_Host *shost, पूर्णांक new_state)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक ret = 0;

	shost_क्रम_each_device(sdev, shost) अणु
		ret = scsi_पूर्णांकernal_device_unblock(sdev, new_state);
		अगर (ret) अणु
			scsi_device_put(sdev);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_host_unblock);

/**
 * scsi_kmap_atomic_sg - find and atomically map an sg-elemnt
 * @sgl:	scatter-gather list
 * @sg_count:	number of segments in sg
 * @offset:	offset in bytes पूर्णांकo sg, on वापस offset पूर्णांकo the mapped area
 * @len:	bytes to map, on वापस number of bytes mapped
 *
 * Returns भव address of the start of the mapped page
 */
व्योम *scsi_kmap_atomic_sg(काष्ठा scatterlist *sgl, पूर्णांक sg_count,
			  माप_प्रकार *offset, माप_प्रकार *len)
अणु
	पूर्णांक i;
	माप_प्रकार sg_len = 0, len_complete = 0;
	काष्ठा scatterlist *sg;
	काष्ठा page *page;

	WARN_ON(!irqs_disabled());

	क्रम_each_sg(sgl, sg, sg_count, i) अणु
		len_complete = sg_len; /* Complete sg-entries */
		sg_len += sg->length;
		अगर (sg_len > *offset)
			अवरोध;
	पूर्ण

	अगर (unlikely(i == sg_count)) अणु
		prपूर्णांकk(KERN_ERR "%s: Bytes in sg: %zu, requested offset %zu, "
			"elements %d\n",
		       __func__, sg_len, *offset, sg_count);
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	/* Offset starting from the beginning of first page in this sg-entry */
	*offset = *offset - len_complete + sg->offset;

	/* Assumption: contiguous pages can be accessed as "page + i" */
	page = nth_page(sg_page(sg), (*offset >> PAGE_SHIFT));
	*offset &= ~PAGE_MASK;

	/* Bytes in this sg-entry from *offset to the end of the page */
	sg_len = PAGE_SIZE - *offset;
	अगर (*len > sg_len)
		*len = sg_len;

	वापस kmap_atomic(page);
पूर्ण
EXPORT_SYMBOL(scsi_kmap_atomic_sg);

/**
 * scsi_kunmap_atomic_sg - atomically unmap a भव address, previously mapped with scsi_kmap_atomic_sg
 * @virt:	भव address to be unmapped
 */
व्योम scsi_kunmap_atomic_sg(व्योम *virt)
अणु
	kunmap_atomic(virt);
पूर्ण
EXPORT_SYMBOL(scsi_kunmap_atomic_sg);

व्योम sdev_disable_disk_events(काष्ठा scsi_device *sdev)
अणु
	atomic_inc(&sdev->disk_events_disable_depth);
पूर्ण
EXPORT_SYMBOL(sdev_disable_disk_events);

व्योम sdev_enable_disk_events(काष्ठा scsi_device *sdev)
अणु
	अगर (WARN_ON_ONCE(atomic_पढ़ो(&sdev->disk_events_disable_depth) <= 0))
		वापस;
	atomic_dec(&sdev->disk_events_disable_depth);
पूर्ण
EXPORT_SYMBOL(sdev_enable_disk_events);

अटल अचिन्हित अक्षर designator_prio(स्थिर अचिन्हित अक्षर *d)
अणु
	अगर (d[1] & 0x30)
		/* not associated with LUN */
		वापस 0;

	अगर (d[3] == 0)
		/* invalid length */
		वापस 0;

	/*
	 * Order of preference क्रम lun descriptor:
	 * - SCSI name string
	 * - NAA IEEE Registered Extended
	 * - EUI-64 based 16-byte
	 * - EUI-64 based 12-byte
	 * - NAA IEEE Registered
	 * - NAA IEEE Extended
	 * - EUI-64 based 8-byte
	 * - SCSI name string (truncated)
	 * - T10 Venकरोr ID
	 * as दीर्घer descriptors reduce the likelyhood
	 * of identअगरication clashes.
	 */

	चयन (d[1] & 0xf) अणु
	हाल 8:
		/* SCSI name string, variable-length UTF-8 */
		वापस 9;
	हाल 3:
		चयन (d[4] >> 4) अणु
		हाल 6:
			/* NAA रेजिस्टरed extended */
			वापस 8;
		हाल 5:
			/* NAA रेजिस्टरed */
			वापस 5;
		हाल 4:
			/* NAA extended */
			वापस 4;
		हाल 3:
			/* NAA locally asचिन्हित */
			वापस 1;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन (d[3]) अणु
		हाल 16:
			/* EUI64-based, 16 byte */
			वापस 7;
		हाल 12:
			/* EUI64-based, 12 byte */
			वापस 6;
		हाल 8:
			/* EUI64-based, 8 byte */
			वापस 3;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
		/* T10 venकरोr ID */
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * scsi_vpd_lun_id - वापस a unique device identअगरication
 * @sdev: SCSI device
 * @id:   buffer क्रम the identअगरication
 * @id_len:  length of the buffer
 *
 * Copies a unique device identअगरication पूर्णांकo @id based
 * on the inक्रमmation in the VPD page 0x83 of the device.
 * The string will be क्रमmatted as a SCSI name string.
 *
 * Returns the length of the identअगरication or error on failure.
 * If the identअगरier is दीर्घer than the supplied buffer the actual
 * identअगरier length is वापसed and the buffer is not zero-padded.
 */
पूर्णांक scsi_vpd_lun_id(काष्ठा scsi_device *sdev, अक्षर *id, माप_प्रकार id_len)
अणु
	u8 cur_id_prio = 0;
	u8 cur_id_size = 0;
	स्थिर अचिन्हित अक्षर *d, *cur_id_str;
	स्थिर काष्ठा scsi_vpd *vpd_pg83;
	पूर्णांक id_size = -EINVAL;

	rcu_पढ़ो_lock();
	vpd_pg83 = rcu_dereference(sdev->vpd_pg83);
	अगर (!vpd_pg83) अणु
		rcu_पढ़ो_unlock();
		वापस -ENXIO;
	पूर्ण

	/* The id string must be at least 20 bytes + terminating शून्य byte */
	अगर (id_len < 21) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	स_रखो(id, 0, id_len);
	क्रम (d = vpd_pg83->data + 4;
	     d < vpd_pg83->data + vpd_pg83->len;
	     d += d[3] + 4) अणु
		u8 prio = designator_prio(d);

		अगर (prio == 0 || cur_id_prio > prio)
			जारी;

		चयन (d[1] & 0xf) अणु
		हाल 0x1:
			/* T10 Venकरोr ID */
			अगर (cur_id_size > d[3])
				अवरोध;
			cur_id_prio = prio;
			cur_id_size = d[3];
			अगर (cur_id_size + 4 > id_len)
				cur_id_size = id_len - 4;
			cur_id_str = d + 4;
			id_size = snम_लिखो(id, id_len, "t10.%*pE",
					   cur_id_size, cur_id_str);
			अवरोध;
		हाल 0x2:
			/* EUI-64 */
			cur_id_prio = prio;
			cur_id_size = d[3];
			cur_id_str = d + 4;
			चयन (cur_id_size) अणु
			हाल 8:
				id_size = snम_लिखो(id, id_len,
						   "eui.%8phN",
						   cur_id_str);
				अवरोध;
			हाल 12:
				id_size = snम_लिखो(id, id_len,
						   "eui.%12phN",
						   cur_id_str);
				अवरोध;
			हाल 16:
				id_size = snम_लिखो(id, id_len,
						   "eui.%16phN",
						   cur_id_str);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x3:
			/* NAA */
			cur_id_prio = prio;
			cur_id_size = d[3];
			cur_id_str = d + 4;
			चयन (cur_id_size) अणु
			हाल 8:
				id_size = snम_लिखो(id, id_len,
						   "naa.%8phN",
						   cur_id_str);
				अवरोध;
			हाल 16:
				id_size = snम_लिखो(id, id_len,
						   "naa.%16phN",
						   cur_id_str);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x8:
			/* SCSI name string */
			अगर (cur_id_size > d[3])
				अवरोध;
			/* Prefer others क्रम truncated descriptor */
			अगर (d[3] > id_len) अणु
				prio = 2;
				अगर (cur_id_prio > prio)
					अवरोध;
			पूर्ण
			cur_id_prio = prio;
			cur_id_size = id_size = d[3];
			cur_id_str = d + 4;
			अगर (cur_id_size >= id_len)
				cur_id_size = id_len - 1;
			स_नकल(id, cur_id_str, cur_id_size);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस id_size;
पूर्ण
EXPORT_SYMBOL(scsi_vpd_lun_id);

/*
 * scsi_vpd_tpg_id - वापस a target port group identअगरier
 * @sdev: SCSI device
 *
 * Returns the Target Port Group identअगरier from the inक्रमmation
 * froom VPD page 0x83 of the device.
 *
 * Returns the identअगरier or error on failure.
 */
पूर्णांक scsi_vpd_tpg_id(काष्ठा scsi_device *sdev, पूर्णांक *rel_id)
अणु
	स्थिर अचिन्हित अक्षर *d;
	स्थिर काष्ठा scsi_vpd *vpd_pg83;
	पूर्णांक group_id = -EAGAIN, rel_port = -1;

	rcu_पढ़ो_lock();
	vpd_pg83 = rcu_dereference(sdev->vpd_pg83);
	अगर (!vpd_pg83) अणु
		rcu_पढ़ो_unlock();
		वापस -ENXIO;
	पूर्ण

	d = vpd_pg83->data + 4;
	जबतक (d < vpd_pg83->data + vpd_pg83->len) अणु
		चयन (d[1] & 0xf) अणु
		हाल 0x4:
			/* Relative target port */
			rel_port = get_unaligned_be16(&d[6]);
			अवरोध;
		हाल 0x5:
			/* Target port group */
			group_id = get_unaligned_be16(&d[6]);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		d += d[3] + 4;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (group_id >= 0 && rel_id && rel_port != -1)
		*rel_id = rel_port;

	वापस group_id;
पूर्ण
EXPORT_SYMBOL(scsi_vpd_tpg_id);
