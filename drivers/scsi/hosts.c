<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  hosts.c Copyright (C) 1992 Drew Eckhardt
 *          Copyright (C) 1993, 1994, 1995 Eric Youngdale
 *          Copyright (C) 2002-2003 Christoph Hellwig
 *
 *  mid to lowlevel SCSI driver पूर्णांकerface
 *      Initial versions: Drew Eckhardt
 *      Subsequent revisions: Eric Youngdale
 *
 *  <drew@coloraकरो.edu>
 *
 *  Jअगरfies wrap fixes (host->resetting), 3 Dec 1998 Andrea Arcangeli
 *  Added QLOGIC QLA1280 SCSI controller kernel host support. 
 *     August 4, 1999 Fred Lewis, Intel DuPont
 *
 *  Updated to reflect the new initialization scheme क्रम the higher 
 *  level of scsi drivers (sd/sr/st)
 *  September 17, 2000 Torben Mathiasen <पंचांगm@image.dk>
 *
 *  Reकाष्ठाured scsi_host lists and associated functions.
 *  September 04, 2002 Mike Anderson (andmike@us.ibm.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/transport_class.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/idr.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"


अटल पूर्णांक shost_eh_deadline = -1;

module_param_named(eh_deadline, shost_eh_deadline, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(eh_deadline,
		 "SCSI EH समयout in seconds (should be between 0 and 2^31-1)");

अटल DEFINE_IDA(host_index_ida);


अटल व्योम scsi_host_cls_release(काष्ठा device *dev)
अणु
	put_device(&class_to_shost(dev)->shost_gendev);
पूर्ण

अटल काष्ठा class shost_class = अणु
	.name		= "scsi_host",
	.dev_release	= scsi_host_cls_release,
पूर्ण;

/**
 *	scsi_host_set_state - Take the given host through the host state model.
 *	@shost:	scsi host to change the state of.
 *	@state:	state to change to.
 *
 *	Returns zero अगर unsuccessful or an error अगर the requested
 *	transition is illegal.
 **/
पूर्णांक scsi_host_set_state(काष्ठा Scsi_Host *shost, क्रमागत scsi_host_state state)
अणु
	क्रमागत scsi_host_state oldstate = shost->shost_state;

	अगर (state == oldstate)
		वापस 0;

	चयन (state) अणु
	हाल SHOST_CREATED:
		/* There are no legal states that come back to
		 * created.  This is the manually initialised start
		 * state */
		जाओ illegal;

	हाल SHOST_RUNNING:
		चयन (oldstate) अणु
		हाल SHOST_CREATED:
		हाल SHOST_RECOVERY:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SHOST_RECOVERY:
		चयन (oldstate) अणु
		हाल SHOST_RUNNING:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SHOST_CANCEL:
		चयन (oldstate) अणु
		हाल SHOST_CREATED:
		हाल SHOST_RUNNING:
		हाल SHOST_CANCEL_RECOVERY:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SHOST_DEL:
		चयन (oldstate) अणु
		हाल SHOST_CANCEL:
		हाल SHOST_DEL_RECOVERY:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SHOST_CANCEL_RECOVERY:
		चयन (oldstate) अणु
		हाल SHOST_CANCEL:
		हाल SHOST_RECOVERY:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल SHOST_DEL_RECOVERY:
		चयन (oldstate) अणु
		हाल SHOST_CANCEL_RECOVERY:
			अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;
	पूर्ण
	shost->shost_state = state;
	वापस 0;

 illegal:
	SCSI_LOG_ERROR_RECOVERY(1,
				shost_prपूर्णांकk(KERN_ERR, shost,
					     "Illegal host state transition"
					     "%s->%s\n",
					     scsi_host_state_name(oldstate),
					     scsi_host_state_name(state)));
	वापस -EINVAL;
पूर्ण

/**
 * scsi_हटाओ_host - हटाओ a scsi host
 * @shost:	a poपूर्णांकer to a scsi host to हटाओ
 **/
व्योम scsi_हटाओ_host(काष्ठा Scsi_Host *shost)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&shost->scan_mutex);
	spin_lock_irqsave(shost->host_lock, flags);
	अगर (scsi_host_set_state(shost, SHOST_CANCEL))
		अगर (scsi_host_set_state(shost, SHOST_CANCEL_RECOVERY)) अणु
			spin_unlock_irqrestore(shost->host_lock, flags);
			mutex_unlock(&shost->scan_mutex);
			वापस;
		पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	scsi_स्वतःpm_get_host(shost);
	flush_workqueue(shost->पंचांगf_work_q);
	scsi_क्रमget_host(shost);
	mutex_unlock(&shost->scan_mutex);
	scsi_proc_host_rm(shost);

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (scsi_host_set_state(shost, SHOST_DEL))
		BUG_ON(scsi_host_set_state(shost, SHOST_DEL_RECOVERY));
	spin_unlock_irqrestore(shost->host_lock, flags);

	transport_unरेजिस्टर_device(&shost->shost_gendev);
	device_unरेजिस्टर(&shost->shost_dev);
	device_del(&shost->shost_gendev);
पूर्ण
EXPORT_SYMBOL(scsi_हटाओ_host);

/**
 * scsi_add_host_with_dma - add a scsi host with dma device
 * @shost:	scsi host poपूर्णांकer to add
 * @dev:	a काष्ठा device of type scsi class
 * @dma_dev:	dma device क्रम the host
 *
 * Note: You rarely need to worry about this unless you're in a
 * भवised host environments, so use the simpler scsi_add_host()
 * function instead.
 *
 * Return value: 
 * 	0 on success / != 0 क्रम error
 **/
पूर्णांक scsi_add_host_with_dma(काष्ठा Scsi_Host *shost, काष्ठा device *dev,
			   काष्ठा device *dma_dev)
अणु
	काष्ठा scsi_host_ढाँचा *sht = shost->hostt;
	पूर्णांक error = -EINVAL;

	shost_prपूर्णांकk(KERN_INFO, shost, "%s\n",
			sht->info ? sht->info(shost) : sht->name);

	अगर (!shost->can_queue) अणु
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "can_queue = 0 no longer supported\n");
		जाओ fail;
	पूर्ण

	error = scsi_init_sense_cache(shost);
	अगर (error)
		जाओ fail;

	error = scsi_mq_setup_tags(shost);
	अगर (error)
		जाओ fail;

	अगर (!shost->shost_gendev.parent)
		shost->shost_gendev.parent = dev ? dev : &platक्रमm_bus;
	अगर (!dma_dev)
		dma_dev = shost->shost_gendev.parent;

	shost->dma_dev = dma_dev;

	/*
	 * Increase usage count temporarily here so that calling
	 * scsi_स्वतःpm_put_host() will trigger runसमय idle अगर there is
	 * nothing अन्यथा preventing suspending the device.
	 */
	pm_runसमय_get_noresume(&shost->shost_gendev);
	pm_runसमय_set_active(&shost->shost_gendev);
	pm_runसमय_enable(&shost->shost_gendev);
	device_enable_async_suspend(&shost->shost_gendev);

	error = device_add(&shost->shost_gendev);
	अगर (error)
		जाओ out_disable_runसमय_pm;

	scsi_host_set_state(shost, SHOST_RUNNING);
	get_device(shost->shost_gendev.parent);

	device_enable_async_suspend(&shost->shost_dev);

	get_device(&shost->shost_gendev);
	error = device_add(&shost->shost_dev);
	अगर (error)
		जाओ out_del_gendev;

	अगर (shost->transportt->host_size) अणु
		shost->shost_data = kzalloc(shost->transportt->host_size,
					 GFP_KERNEL);
		अगर (shost->shost_data == शून्य) अणु
			error = -ENOMEM;
			जाओ out_del_dev;
		पूर्ण
	पूर्ण

	अगर (shost->transportt->create_work_queue) अणु
		snम_लिखो(shost->work_q_name, माप(shost->work_q_name),
			 "scsi_wq_%d", shost->host_no);
		shost->work_q = alloc_workqueue("%s",
			WQ_SYSFS | __WQ_LEGACY | WQ_MEM_RECLAIM | WQ_UNBOUND,
			1, shost->work_q_name);

		अगर (!shost->work_q) अणु
			error = -EINVAL;
			जाओ out_del_dev;
		पूर्ण
	पूर्ण

	error = scsi_sysfs_add_host(shost);
	अगर (error)
		जाओ out_del_dev;

	scsi_proc_host_add(shost);
	scsi_स्वतःpm_put_host(shost);
	वापस error;

	/*
	 * Any host allocation in this function will be मुक्तd in
	 * scsi_host_dev_release().
	 */
 out_del_dev:
	device_del(&shost->shost_dev);
 out_del_gendev:
	/*
	 * Host state is SHOST_RUNNING so we have to explicitly release
	 * ->shost_dev.
	 */
	put_device(&shost->shost_dev);
	device_del(&shost->shost_gendev);
 out_disable_runसमय_pm:
	device_disable_async_suspend(&shost->shost_gendev);
	pm_runसमय_disable(&shost->shost_gendev);
	pm_runसमय_set_suspended(&shost->shost_gendev);
	pm_runसमय_put_noidle(&shost->shost_gendev);
 fail:
	वापस error;
पूर्ण
EXPORT_SYMBOL(scsi_add_host_with_dma);

अटल व्योम scsi_host_dev_release(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा device *parent = dev->parent;

	scsi_proc_hostdir_rm(shost->hostt);

	/* Wait क्रम functions invoked through call_rcu(&shost->rcu, ...) */
	rcu_barrier();

	अगर (shost->पंचांगf_work_q)
		destroy_workqueue(shost->पंचांगf_work_q);
	अगर (shost->ehandler)
		kthपढ़ो_stop(shost->ehandler);
	अगर (shost->work_q)
		destroy_workqueue(shost->work_q);

	अगर (shost->shost_state == SHOST_CREATED) अणु
		/*
		 * Free the shost_dev device name here अगर scsi_host_alloc()
		 * and scsi_host_put() have been called but neither
		 * scsi_host_add() nor scsi_host_हटाओ() has been called.
		 * This aव्योमs that the memory allocated क्रम the shost_dev
		 * name is leaked.
		 */
		kमुक्त(dev_name(&shost->shost_dev));
	पूर्ण

	अगर (shost->tag_set.tags)
		scsi_mq_destroy_tags(shost);

	kमुक्त(shost->shost_data);

	ida_simple_हटाओ(&host_index_ida, shost->host_no);

	अगर (shost->shost_state != SHOST_CREATED)
		put_device(parent);
	kमुक्त(shost);
पूर्ण

अटल काष्ठा device_type scsi_host_type = अणु
	.name =		"scsi_host",
	.release =	scsi_host_dev_release,
पूर्ण;

/**
 * scsi_host_alloc - रेजिस्टर a scsi host adapter instance.
 * @sht:	poपूर्णांकer to scsi host ढाँचा
 * @privsize:	extra bytes to allocate क्रम driver
 *
 * Note:
 * 	Allocate a new Scsi_Host and perक्रमm basic initialization.
 * 	The host is not published to the scsi midlayer until scsi_add_host
 * 	is called.
 *
 * Return value:
 * 	Poपूर्णांकer to a new Scsi_Host
 **/
काष्ठा Scsi_Host *scsi_host_alloc(काष्ठा scsi_host_ढाँचा *sht, पूर्णांक privsize)
अणु
	काष्ठा Scsi_Host *shost;
	पूर्णांक index;

	shost = kzalloc(माप(काष्ठा Scsi_Host) + privsize, GFP_KERNEL);
	अगर (!shost)
		वापस शून्य;

	shost->host_lock = &shost->शेष_lock;
	spin_lock_init(shost->host_lock);
	shost->shost_state = SHOST_CREATED;
	INIT_LIST_HEAD(&shost->__devices);
	INIT_LIST_HEAD(&shost->__tarमाला_लो);
	INIT_LIST_HEAD(&shost->eh_cmd_q);
	INIT_LIST_HEAD(&shost->starved_list);
	init_रुकोqueue_head(&shost->host_रुको);
	mutex_init(&shost->scan_mutex);

	index = ida_simple_get(&host_index_ida, 0, 0, GFP_KERNEL);
	अगर (index < 0) अणु
		kमुक्त(shost);
		वापस शून्य;
	पूर्ण
	shost->host_no = index;

	shost->dma_channel = 0xff;

	/* These three are शेष values which can be overridden */
	shost->max_channel = 0;
	shost->max_id = 8;
	shost->max_lun = 8;

	/* Give each shost a शेष transportt */
	shost->transportt = &blank_transport_ढाँचा;

	/*
	 * All drivers right now should be able to handle 12 byte
	 * commands.  Every so often there are requests क्रम 16 byte
	 * commands, but inभागidual low-level drivers need to certअगरy that
	 * they actually करो something sensible with such commands.
	 */
	shost->max_cmd_len = 12;
	shost->hostt = sht;
	shost->this_id = sht->this_id;
	shost->can_queue = sht->can_queue;
	shost->sg_tablesize = sht->sg_tablesize;
	shost->sg_prot_tablesize = sht->sg_prot_tablesize;
	shost->cmd_per_lun = sht->cmd_per_lun;
	shost->no_ग_लिखो_same = sht->no_ग_लिखो_same;
	shost->host_tagset = sht->host_tagset;

	अगर (shost_eh_deadline == -1 || !sht->eh_host_reset_handler)
		shost->eh_deadline = -1;
	अन्यथा अगर ((uदीर्घ) shost_eh_deadline * HZ > पूर्णांक_उच्च) अणु
		shost_prपूर्णांकk(KERN_WARNING, shost,
			     "eh_deadline %u too large, setting to %u\n",
			     shost_eh_deadline, पूर्णांक_उच्च / HZ);
		shost->eh_deadline = पूर्णांक_उच्च;
	पूर्ण अन्यथा
		shost->eh_deadline = shost_eh_deadline * HZ;

	अगर (sht->supported_mode == MODE_UNKNOWN)
		/* means we didn't set it ... शेष to INITIATOR */
		shost->active_mode = MODE_INITIATOR;
	अन्यथा
		shost->active_mode = sht->supported_mode;

	अगर (sht->max_host_blocked)
		shost->max_host_blocked = sht->max_host_blocked;
	अन्यथा
		shost->max_host_blocked = SCSI_DEFAULT_HOST_BLOCKED;

	/*
	 * If the driver imposes no hard sector transfer limit, start at
	 * machine infinity initially.
	 */
	अगर (sht->max_sectors)
		shost->max_sectors = sht->max_sectors;
	अन्यथा
		shost->max_sectors = SCSI_DEFAULT_MAX_SECTORS;

	अगर (sht->max_segment_size)
		shost->max_segment_size = sht->max_segment_size;
	अन्यथा
		shost->max_segment_size = BLK_MAX_SEGMENT_SIZE;

	/*
	 * assume a 4GB boundary, अगर not set
	 */
	अगर (sht->dma_boundary)
		shost->dma_boundary = sht->dma_boundary;
	अन्यथा
		shost->dma_boundary = 0xffffffff;

	अगर (sht->virt_boundary_mask)
		shost->virt_boundary_mask = sht->virt_boundary_mask;

	device_initialize(&shost->shost_gendev);
	dev_set_name(&shost->shost_gendev, "host%d", shost->host_no);
	shost->shost_gendev.bus = &scsi_bus_type;
	shost->shost_gendev.type = &scsi_host_type;

	device_initialize(&shost->shost_dev);
	shost->shost_dev.parent = &shost->shost_gendev;
	shost->shost_dev.class = &shost_class;
	dev_set_name(&shost->shost_dev, "host%d", shost->host_no);
	shost->shost_dev.groups = scsi_sysfs_shost_attr_groups;

	shost->ehandler = kthपढ़ो_run(scsi_error_handler, shost,
			"scsi_eh_%d", shost->host_no);
	अगर (IS_ERR(shost->ehandler)) अणु
		shost_prपूर्णांकk(KERN_WARNING, shost,
			"error handler thread failed to spawn, error = %ld\n",
			PTR_ERR(shost->ehandler));
		जाओ fail;
	पूर्ण

	shost->पंचांगf_work_q = alloc_workqueue("scsi_tmf_%d",
					WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_SYSFS,
					   1, shost->host_no);
	अगर (!shost->पंचांगf_work_q) अणु
		shost_prपूर्णांकk(KERN_WARNING, shost,
			     "failed to create tmf workq\n");
		जाओ fail;
	पूर्ण
	scsi_proc_hostdir_add(shost->hostt);
	वापस shost;
 fail:
	/*
	 * Host state is still SHOST_CREATED and that is enough to release
	 * ->shost_gendev. scsi_host_dev_release() will मुक्त
	 * dev_name(&shost->shost_dev).
	 */
	put_device(&shost->shost_gendev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(scsi_host_alloc);

अटल पूर्णांक __scsi_host_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा Scsi_Host *p;
	स्थिर अचिन्हित लघु *hostnum = data;

	p = class_to_shost(dev);
	वापस p->host_no == *hostnum;
पूर्ण

/**
 * scsi_host_lookup - get a reference to a Scsi_Host by host no
 * @hostnum:	host number to locate
 *
 * Return value:
 *	A poपूर्णांकer to located Scsi_Host or शून्य.
 *
 *	The caller must करो a scsi_host_put() to drop the reference
 *	that scsi_host_get() took. The put_device() below dropped
 *	the reference from class_find_device().
 **/
काष्ठा Scsi_Host *scsi_host_lookup(अचिन्हित लघु hostnum)
अणु
	काष्ठा device *cdev;
	काष्ठा Scsi_Host *shost = शून्य;

	cdev = class_find_device(&shost_class, शून्य, &hostnum,
				 __scsi_host_match);
	अगर (cdev) अणु
		shost = scsi_host_get(class_to_shost(cdev));
		put_device(cdev);
	पूर्ण
	वापस shost;
पूर्ण
EXPORT_SYMBOL(scsi_host_lookup);

/**
 * scsi_host_get - inc a Scsi_Host ref count
 * @shost:	Poपूर्णांकer to Scsi_Host to inc.
 **/
काष्ठा Scsi_Host *scsi_host_get(काष्ठा Scsi_Host *shost)
अणु
	अगर ((shost->shost_state == SHOST_DEL) ||
		!get_device(&shost->shost_gendev))
		वापस शून्य;
	वापस shost;
पूर्ण
EXPORT_SYMBOL(scsi_host_get);

अटल bool scsi_host_check_in_flight(काष्ठा request *rq, व्योम *data,
				      bool reserved)
अणु
	पूर्णांक *count = data;
	काष्ठा scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);

	अगर (test_bit(SCMD_STATE_INFLIGHT, &cmd->state))
		(*count)++;

	वापस true;
पूर्ण

/**
 * scsi_host_busy - Return the host busy counter
 * @shost:	Poपूर्णांकer to Scsi_Host to inc.
 **/
पूर्णांक scsi_host_busy(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक cnt = 0;

	blk_mq_tagset_busy_iter(&shost->tag_set,
				scsi_host_check_in_flight, &cnt);
	वापस cnt;
पूर्ण
EXPORT_SYMBOL(scsi_host_busy);

/**
 * scsi_host_put - dec a Scsi_Host ref count
 * @shost:	Poपूर्णांकer to Scsi_Host to dec.
 **/
व्योम scsi_host_put(काष्ठा Scsi_Host *shost)
अणु
	put_device(&shost->shost_gendev);
पूर्ण
EXPORT_SYMBOL(scsi_host_put);

पूर्णांक scsi_init_hosts(व्योम)
अणु
	वापस class_रेजिस्टर(&shost_class);
पूर्ण

व्योम scsi_निकास_hosts(व्योम)
अणु
	class_unरेजिस्टर(&shost_class);
	ida_destroy(&host_index_ida);
पूर्ण

पूर्णांक scsi_is_host_device(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &scsi_host_type;
पूर्ण
EXPORT_SYMBOL(scsi_is_host_device);

/**
 * scsi_queue_work - Queue work to the Scsi_Host workqueue.
 * @shost:	Poपूर्णांकer to Scsi_Host.
 * @work:	Work to queue क्रम execution.
 *
 * Return value:
 * 	1 - work queued क्रम execution
 *	0 - work is alपढ़ोy queued
 *	-EINVAL - work queue करोesn't exist
 **/
पूर्णांक scsi_queue_work(काष्ठा Scsi_Host *shost, काष्ठा work_काष्ठा *work)
अणु
	अगर (unlikely(!shost->work_q)) अणु
		shost_prपूर्णांकk(KERN_ERR, shost,
			"ERROR: Scsi host '%s' attempted to queue scsi-work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();

		वापस -EINVAL;
	पूर्ण

	वापस queue_work(shost->work_q, work);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_queue_work);

/**
 * scsi_flush_work - Flush a Scsi_Host's workqueue.
 * @shost:	Poपूर्णांकer to Scsi_Host.
 **/
व्योम scsi_flush_work(काष्ठा Scsi_Host *shost)
अणु
	अगर (!shost->work_q) अणु
		shost_prपूर्णांकk(KERN_ERR, shost,
			"ERROR: Scsi host '%s' attempted to flush scsi-work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();
		वापस;
	पूर्ण

	flush_workqueue(shost->work_q);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_flush_work);

अटल bool complete_all_cmds_iter(काष्ठा request *rq, व्योम *data, bool rsvd)
अणु
	काष्ठा scsi_cmnd *scmd = blk_mq_rq_to_pdu(rq);
	पूर्णांक status = *(पूर्णांक *)data;

	scsi_dma_unmap(scmd);
	scmd->result = status << 16;
	scmd->scsi_करोne(scmd);
	वापस true;
पूर्ण

/**
 * scsi_host_complete_all_commands - Terminate all running commands
 * @shost:	Scsi Host on which commands should be terminated
 * @status:	Status to be set क्रम the terminated commands
 *
 * There is no protection against modअगरication of the number
 * of outstanding commands. It is the responsibility of the
 * caller to ensure that concurrent I/O submission and/or
 * completion is stopped when calling this function.
 */
व्योम scsi_host_complete_all_commands(काष्ठा Scsi_Host *shost, पूर्णांक status)
अणु
	blk_mq_tagset_busy_iter(&shost->tag_set, complete_all_cmds_iter,
				&status);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_host_complete_all_commands);

काष्ठा scsi_host_busy_iter_data अणु
	bool (*fn)(काष्ठा scsi_cmnd *, व्योम *, bool);
	व्योम *priv;
पूर्ण;

अटल bool __scsi_host_busy_iter_fn(काष्ठा request *req, व्योम *priv,
				   bool reserved)
अणु
	काष्ठा scsi_host_busy_iter_data *iter_data = priv;
	काष्ठा scsi_cmnd *sc = blk_mq_rq_to_pdu(req);

	वापस iter_data->fn(sc, iter_data->priv, reserved);
पूर्ण

/**
 * scsi_host_busy_iter - Iterate over all busy commands
 * @shost:	Poपूर्णांकer to Scsi_Host.
 * @fn:		Function to call on each busy command
 * @priv:	Data poपूर्णांकer passed to @fn
 *
 * If locking against concurrent command completions is required
 * ithas to be provided by the caller
 **/
व्योम scsi_host_busy_iter(काष्ठा Scsi_Host *shost,
			 bool (*fn)(काष्ठा scsi_cmnd *, व्योम *, bool),
			 व्योम *priv)
अणु
	काष्ठा scsi_host_busy_iter_data iter_data = अणु
		.fn = fn,
		.priv = priv,
	पूर्ण;

	blk_mq_tagset_busy_iter(&shost->tag_set, __scsi_host_busy_iter_fn,
				&iter_data);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_host_busy_iter);
