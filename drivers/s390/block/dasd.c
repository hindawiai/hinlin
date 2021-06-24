<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Carsten Otte <Cotte@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2009
 */

#घोषणा KMSG_COMPONENT "dasd"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/major.h>
#समावेश <linux/slab.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/async.h>
#समावेश <linux/mutex.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/idals.h>
#समावेश <यंत्र/itcw.h>
#समावेश <यंत्र/diag.h>

/* This is ugly... */
#घोषणा PRINTK_HEADER "dasd:"

#समावेश "dasd_int.h"
/*
 * SECTION: Constant definitions to be used within this file
 */
#घोषणा DASD_CHANQ_MAX_SIZE 4

#घोषणा DASD_DIAG_MOD		"dasd_diag_mod"

अटल अचिन्हित पूर्णांक queue_depth = 32;
अटल अचिन्हित पूर्णांक nr_hw_queues = 4;

module_param(queue_depth, uपूर्णांक, 0444);
MODULE_PARM_DESC(queue_depth, "Default queue depth for new DASD devices");

module_param(nr_hw_queues, uपूर्णांक, 0444);
MODULE_PARM_DESC(nr_hw_queues, "Default number of hardware queues for new DASD devices");

/*
 * SECTION: exported variables of dasd.c
 */
debug_info_t *dasd_debug_area;
EXPORT_SYMBOL(dasd_debug_area);
अटल काष्ठा dentry *dasd_debugfs_root_entry;
काष्ठा dasd_discipline *dasd_diag_discipline_poपूर्णांकer;
EXPORT_SYMBOL(dasd_diag_discipline_poपूर्णांकer);
व्योम dasd_पूर्णांक_handler(काष्ठा ccw_device *, अचिन्हित दीर्घ, काष्ठा irb *);

MODULE_AUTHOR("Holger Smolinski <Holger.Smolinski@de.ibm.com>");
MODULE_DESCRIPTION("Linux on S/390 DASD device driver,"
		   " Copyright IBM Corp. 2000");
MODULE_LICENSE("GPL");

/*
 * SECTION: prototypes क्रम अटल functions of dasd.c
 */
अटल पूर्णांक  dasd_alloc_queue(काष्ठा dasd_block *);
अटल व्योम dasd_मुक्त_queue(काष्ठा dasd_block *);
अटल पूर्णांक dasd_flush_block_queue(काष्ठा dasd_block *);
अटल व्योम dasd_device_tasklet(अचिन्हित दीर्घ);
अटल व्योम dasd_block_tasklet(अचिन्हित दीर्घ);
अटल व्योम करो_kick_device(काष्ठा work_काष्ठा *);
अटल व्योम करो_reload_device(काष्ठा work_काष्ठा *);
अटल व्योम करो_requeue_requests(काष्ठा work_काष्ठा *);
अटल व्योम dasd_वापस_cqr_cb(काष्ठा dasd_ccw_req *, व्योम *);
अटल व्योम dasd_device_समयout(काष्ठा समयr_list *);
अटल व्योम dasd_block_समयout(काष्ठा समयr_list *);
अटल व्योम __dasd_process_erp(काष्ठा dasd_device *, काष्ठा dasd_ccw_req *);
अटल व्योम dasd_profile_init(काष्ठा dasd_profile *, काष्ठा dentry *);
अटल व्योम dasd_profile_निकास(काष्ठा dasd_profile *);
अटल व्योम dasd_hosts_init(काष्ठा dentry *, काष्ठा dasd_device *);
अटल व्योम dasd_hosts_निकास(काष्ठा dasd_device *);

/*
 * SECTION: Operations on the device काष्ठाure.
 */
अटल रुको_queue_head_t dasd_init_रुकोq;
अटल रुको_queue_head_t dasd_flush_wq;
अटल रुको_queue_head_t generic_रुकोq;
अटल रुको_queue_head_t shutकरोwn_रुकोq;

/*
 * Allocate memory क्रम a new device काष्ठाure.
 */
काष्ठा dasd_device *dasd_alloc_device(व्योम)
अणु
	काष्ठा dasd_device *device;

	device = kzalloc(माप(काष्ठा dasd_device), GFP_ATOMIC);
	अगर (!device)
		वापस ERR_PTR(-ENOMEM);

	/* Get two pages क्रम normal block device operations. */
	device->ccw_mem = (व्योम *) __get_मुक्त_pages(GFP_ATOMIC | GFP_DMA, 1);
	अगर (!device->ccw_mem) अणु
		kमुक्त(device);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	/* Get one page क्रम error recovery. */
	device->erp_mem = (व्योम *) get_zeroed_page(GFP_ATOMIC | GFP_DMA);
	अगर (!device->erp_mem) अणु
		मुक्त_pages((अचिन्हित दीर्घ) device->ccw_mem, 1);
		kमुक्त(device);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	/* Get two pages क्रम ese क्रमmat. */
	device->ese_mem = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC | GFP_DMA, 1);
	अगर (!device->ese_mem) अणु
		मुक्त_page((अचिन्हित दीर्घ) device->erp_mem);
		मुक्त_pages((अचिन्हित दीर्घ) device->ccw_mem, 1);
		kमुक्त(device);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dasd_init_chunklist(&device->ccw_chunks, device->ccw_mem, PAGE_SIZE*2);
	dasd_init_chunklist(&device->erp_chunks, device->erp_mem, PAGE_SIZE);
	dasd_init_chunklist(&device->ese_chunks, device->ese_mem, PAGE_SIZE * 2);
	spin_lock_init(&device->mem_lock);
	atomic_set(&device->tasklet_scheduled, 0);
	tasklet_init(&device->tasklet, dasd_device_tasklet,
		     (अचिन्हित दीर्घ) device);
	INIT_LIST_HEAD(&device->ccw_queue);
	समयr_setup(&device->समयr, dasd_device_समयout, 0);
	INIT_WORK(&device->kick_work, करो_kick_device);
	INIT_WORK(&device->reload_device, करो_reload_device);
	INIT_WORK(&device->requeue_requests, करो_requeue_requests);
	device->state = DASD_STATE_NEW;
	device->target = DASD_STATE_NEW;
	mutex_init(&device->state_mutex);
	spin_lock_init(&device->profile.lock);
	वापस device;
पूर्ण

/*
 * Free memory of a device काष्ठाure.
 */
व्योम dasd_मुक्त_device(काष्ठा dasd_device *device)
अणु
	kमुक्त(device->निजी);
	मुक्त_pages((अचिन्हित दीर्घ) device->ese_mem, 1);
	मुक्त_page((अचिन्हित दीर्घ) device->erp_mem);
	मुक्त_pages((अचिन्हित दीर्घ) device->ccw_mem, 1);
	kमुक्त(device);
पूर्ण

/*
 * Allocate memory क्रम a new device काष्ठाure.
 */
काष्ठा dasd_block *dasd_alloc_block(व्योम)
अणु
	काष्ठा dasd_block *block;

	block = kzalloc(माप(*block), GFP_ATOMIC);
	अगर (!block)
		वापस ERR_PTR(-ENOMEM);
	/* खोलो_count = 0 means device online but not in use */
	atomic_set(&block->खोलो_count, -1);

	atomic_set(&block->tasklet_scheduled, 0);
	tasklet_init(&block->tasklet, dasd_block_tasklet,
		     (अचिन्हित दीर्घ) block);
	INIT_LIST_HEAD(&block->ccw_queue);
	spin_lock_init(&block->queue_lock);
	INIT_LIST_HEAD(&block->क्रमmat_list);
	spin_lock_init(&block->क्रमmat_lock);
	समयr_setup(&block->समयr, dasd_block_समयout, 0);
	spin_lock_init(&block->profile.lock);

	वापस block;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_alloc_block);

/*
 * Free memory of a device काष्ठाure.
 */
व्योम dasd_मुक्त_block(काष्ठा dasd_block *block)
अणु
	kमुक्त(block);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_मुक्त_block);

/*
 * Make a new device known to the प्रणाली.
 */
अटल पूर्णांक dasd_state_new_to_known(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	/*
	 * As दीर्घ as the device is not in state DASD_STATE_NEW we want to
	 * keep the reference count > 0.
	 */
	dasd_get_device(device);

	अगर (device->block) अणु
		rc = dasd_alloc_queue(device->block);
		अगर (rc) अणु
			dasd_put_device(device);
			वापस rc;
		पूर्ण
	पूर्ण
	device->state = DASD_STATE_KNOWN;
	वापस 0;
पूर्ण

/*
 * Let the प्रणाली क्रमget about a device.
 */
अटल पूर्णांक dasd_state_known_to_new(काष्ठा dasd_device *device)
अणु
	/* Disable extended error reporting क्रम this device. */
	dasd_eer_disable(device);
	device->state = DASD_STATE_NEW;

	अगर (device->block)
		dasd_मुक्त_queue(device->block);

	/* Give up reference we took in dasd_state_new_to_known. */
	dasd_put_device(device);
	वापस 0;
पूर्ण

अटल काष्ठा dentry *dasd_debugfs_setup(स्थिर अक्षर *name,
					 काष्ठा dentry *base_dentry)
अणु
	काष्ठा dentry *pde;

	अगर (!base_dentry)
		वापस शून्य;
	pde = debugfs_create_dir(name, base_dentry);
	अगर (!pde || IS_ERR(pde))
		वापस शून्य;
	वापस pde;
पूर्ण

/*
 * Request the irq line क्रम the device.
 */
अटल पूर्णांक dasd_state_known_to_basic(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_block *block = device->block;
	पूर्णांक rc = 0;

	/* Allocate and रेजिस्टर gendisk काष्ठाure. */
	अगर (block) अणु
		rc = dasd_gendisk_alloc(block);
		अगर (rc)
			वापस rc;
		block->debugfs_dentry =
			dasd_debugfs_setup(block->gdp->disk_name,
					   dasd_debugfs_root_entry);
		dasd_profile_init(&block->profile, block->debugfs_dentry);
		अगर (dasd_global_profile_level == DASD_PROखाता_ON)
			dasd_profile_on(&device->block->profile);
	पूर्ण
	device->debugfs_dentry =
		dasd_debugfs_setup(dev_name(&device->cdev->dev),
				   dasd_debugfs_root_entry);
	dasd_profile_init(&device->profile, device->debugfs_dentry);
	dasd_hosts_init(device->debugfs_dentry, device);

	/* रेजिस्टर 'device' debug area, used क्रम all DBF_DEV_XXX calls */
	device->debug_area = debug_रेजिस्टर(dev_name(&device->cdev->dev), 4, 1,
					    8 * माप(दीर्घ));
	debug_रेजिस्टर_view(device->debug_area, &debug_प्र_लिखो_view);
	debug_set_level(device->debug_area, DBF_WARNING);
	DBF_DEV_EVENT(DBF_EMERG, device, "%s", "debug area created");

	device->state = DASD_STATE_BASIC;

	वापस rc;
पूर्ण

/*
 * Release the irq line क्रम the device. Terminate any running i/o.
 */
अटल पूर्णांक dasd_state_basic_to_known(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	अगर (device->discipline->basic_to_known) अणु
		rc = device->discipline->basic_to_known(device);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (device->block) अणु
		dasd_profile_निकास(&device->block->profile);
		debugfs_हटाओ(device->block->debugfs_dentry);
		dasd_gendisk_मुक्त(device->block);
		dasd_block_clear_समयr(device->block);
	पूर्ण
	rc = dasd_flush_device_queue(device);
	अगर (rc)
		वापस rc;
	dasd_device_clear_समयr(device);
	dasd_profile_निकास(&device->profile);
	dasd_hosts_निकास(device);
	debugfs_हटाओ(device->debugfs_dentry);
	DBF_DEV_EVENT(DBF_EMERG, device, "%p debug area deleted", device);
	अगर (device->debug_area != शून्य) अणु
		debug_unरेजिस्टर(device->debug_area);
		device->debug_area = शून्य;
	पूर्ण
	device->state = DASD_STATE_KNOWN;
	वापस 0;
पूर्ण

/*
 * Do the initial analysis. The करो_analysis function may वापस
 * -EAGAIN in which हाल the device keeps the state DASD_STATE_BASIC
 * until the discipline decides to जारी the startup sequence
 * by calling the function dasd_change_state. The eckd disciplines
 * uses this to start a ccw that detects the क्रमmat. The completion
 * पूर्णांकerrupt क्रम this detection ccw uses the kernel event daemon to
 * trigger the call to dasd_change_state. All this is करोne in the
 * discipline code, see dasd_eckd.c.
 * After the analysis ccw is करोne (करो_analysis वापसed 0) the block
 * device is setup.
 * In हाल the analysis वापसs an error, the device setup is stopped
 * (a fake disk was alपढ़ोy added to allow क्रमmatting).
 */
अटल पूर्णांक dasd_state_basic_to_पढ़ोy(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;
	काष्ठा dasd_block *block;
	काष्ठा gendisk *disk;

	rc = 0;
	block = device->block;
	/* make disk known with correct capacity */
	अगर (block) अणु
		अगर (block->base->discipline->करो_analysis != शून्य)
			rc = block->base->discipline->करो_analysis(block);
		अगर (rc) अणु
			अगर (rc != -EAGAIN) अणु
				device->state = DASD_STATE_UNFMT;
				disk = device->block->gdp;
				kobject_uevent(&disk_to_dev(disk)->kobj,
					       KOBJ_CHANGE);
				जाओ out;
			पूर्ण
			वापस rc;
		पूर्ण
		अगर (device->discipline->setup_blk_queue)
			device->discipline->setup_blk_queue(block);
		set_capacity(block->gdp,
			     block->blocks << block->s2b_shअगरt);
		device->state = DASD_STATE_READY;
		rc = dasd_scan_partitions(block);
		अगर (rc) अणु
			device->state = DASD_STATE_BASIC;
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		device->state = DASD_STATE_READY;
	पूर्ण
out:
	अगर (device->discipline->basic_to_पढ़ोy)
		rc = device->discipline->basic_to_पढ़ोy(device);
	वापस rc;
पूर्ण

अटल अंतरभूत
पूर्णांक _रुको_क्रम_empty_queues(काष्ठा dasd_device *device)
अणु
	अगर (device->block)
		वापस list_empty(&device->ccw_queue) &&
			list_empty(&device->block->ccw_queue);
	अन्यथा
		वापस list_empty(&device->ccw_queue);
पूर्ण

/*
 * Remove device from block device layer. Destroy dirty buffers.
 * Forget क्रमmat inक्रमmation. Check अगर the target level is basic
 * and अगर it is create fake disk क्रम क्रमmatting.
 */
अटल पूर्णांक dasd_state_पढ़ोy_to_basic(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	device->state = DASD_STATE_BASIC;
	अगर (device->block) अणु
		काष्ठा dasd_block *block = device->block;
		rc = dasd_flush_block_queue(block);
		अगर (rc) अणु
			device->state = DASD_STATE_READY;
			वापस rc;
		पूर्ण
		dasd_destroy_partitions(block);
		block->blocks = 0;
		block->bp_block = 0;
		block->s2b_shअगरt = 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Back to basic.
 */
अटल पूर्णांक dasd_state_unfmt_to_basic(काष्ठा dasd_device *device)
अणु
	device->state = DASD_STATE_BASIC;
	वापस 0;
पूर्ण

/*
 * Make the device online and schedule the bottom half to start
 * the requeueing of requests from the linux request queue to the
 * ccw queue.
 */
अटल पूर्णांक
dasd_state_पढ़ोy_to_online(काष्ठा dasd_device * device)
अणु
	device->state = DASD_STATE_ONLINE;
	अगर (device->block) अणु
		dasd_schedule_block_bh(device->block);
		अगर ((device->features & DASD_FEATURE_USERAW)) अणु
			kobject_uevent(&disk_to_dev(device->block->gdp)->kobj,
					KOBJ_CHANGE);
			वापस 0;
		पूर्ण
		disk_uevent(device->block->bdev->bd_disk, KOBJ_CHANGE);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Stop the requeueing of requests again.
 */
अटल पूर्णांक dasd_state_online_to_पढ़ोy(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	अगर (device->discipline->online_to_पढ़ोy) अणु
		rc = device->discipline->online_to_पढ़ोy(device);
		अगर (rc)
			वापस rc;
	पूर्ण

	device->state = DASD_STATE_READY;
	अगर (device->block && !(device->features & DASD_FEATURE_USERAW))
		disk_uevent(device->block->bdev->bd_disk, KOBJ_CHANGE);
	वापस 0;
पूर्ण

/*
 * Device startup state changes.
 */
अटल पूर्णांक dasd_increase_state(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	rc = 0;
	अगर (device->state == DASD_STATE_NEW &&
	    device->target >= DASD_STATE_KNOWN)
		rc = dasd_state_new_to_known(device);

	अगर (!rc &&
	    device->state == DASD_STATE_KNOWN &&
	    device->target >= DASD_STATE_BASIC)
		rc = dasd_state_known_to_basic(device);

	अगर (!rc &&
	    device->state == DASD_STATE_BASIC &&
	    device->target >= DASD_STATE_READY)
		rc = dasd_state_basic_to_पढ़ोy(device);

	अगर (!rc &&
	    device->state == DASD_STATE_UNFMT &&
	    device->target > DASD_STATE_UNFMT)
		rc = -EPERM;

	अगर (!rc &&
	    device->state == DASD_STATE_READY &&
	    device->target >= DASD_STATE_ONLINE)
		rc = dasd_state_पढ़ोy_to_online(device);

	वापस rc;
पूर्ण

/*
 * Device shutकरोwn state changes.
 */
अटल पूर्णांक dasd_decrease_state(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	rc = 0;
	अगर (device->state == DASD_STATE_ONLINE &&
	    device->target <= DASD_STATE_READY)
		rc = dasd_state_online_to_पढ़ोy(device);

	अगर (!rc &&
	    device->state == DASD_STATE_READY &&
	    device->target <= DASD_STATE_BASIC)
		rc = dasd_state_पढ़ोy_to_basic(device);

	अगर (!rc &&
	    device->state == DASD_STATE_UNFMT &&
	    device->target <= DASD_STATE_BASIC)
		rc = dasd_state_unfmt_to_basic(device);

	अगर (!rc &&
	    device->state == DASD_STATE_BASIC &&
	    device->target <= DASD_STATE_KNOWN)
		rc = dasd_state_basic_to_known(device);

	अगर (!rc &&
	    device->state == DASD_STATE_KNOWN &&
	    device->target <= DASD_STATE_NEW)
		rc = dasd_state_known_to_new(device);

	वापस rc;
पूर्ण

/*
 * This is the मुख्य startup/shutकरोwn routine.
 */
अटल व्योम dasd_change_state(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	अगर (device->state == device->target)
		/* Alपढ़ोy where we want to go today... */
		वापस;
	अगर (device->state < device->target)
		rc = dasd_increase_state(device);
	अन्यथा
		rc = dasd_decrease_state(device);
	अगर (rc == -EAGAIN)
		वापस;
	अगर (rc)
		device->target = device->state;

	/* let user-space know that the device status changed */
	kobject_uevent(&device->cdev->dev.kobj, KOBJ_CHANGE);

	अगर (device->state == device->target)
		wake_up(&dasd_init_रुकोq);
पूर्ण

/*
 * Kick starter क्रम devices that did not complete the startup/shutकरोwn
 * procedure or were sleeping because of a pending state.
 * dasd_kick_device will schedule a call करो करो_kick_device to the kernel
 * event daemon.
 */
अटल व्योम करो_kick_device(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dasd_device *device = container_of(work, काष्ठा dasd_device, kick_work);
	mutex_lock(&device->state_mutex);
	dasd_change_state(device);
	mutex_unlock(&device->state_mutex);
	dasd_schedule_device_bh(device);
	dasd_put_device(device);
पूर्ण

व्योम dasd_kick_device(काष्ठा dasd_device *device)
अणु
	dasd_get_device(device);
	/* queue call to dasd_kick_device to the kernel event daemon. */
	अगर (!schedule_work(&device->kick_work))
		dasd_put_device(device);
पूर्ण
EXPORT_SYMBOL(dasd_kick_device);

/*
 * dasd_reload_device will schedule a call करो करो_reload_device to the kernel
 * event daemon.
 */
अटल व्योम करो_reload_device(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dasd_device *device = container_of(work, काष्ठा dasd_device,
						  reload_device);
	device->discipline->reload(device);
	dasd_put_device(device);
पूर्ण

व्योम dasd_reload_device(काष्ठा dasd_device *device)
अणु
	dasd_get_device(device);
	/* queue call to dasd_reload_device to the kernel event daemon. */
	अगर (!schedule_work(&device->reload_device))
		dasd_put_device(device);
पूर्ण
EXPORT_SYMBOL(dasd_reload_device);

/*
 * Set the target state क्रम a device and starts the state change.
 */
व्योम dasd_set_target_state(काष्ठा dasd_device *device, पूर्णांक target)
अणु
	dasd_get_device(device);
	mutex_lock(&device->state_mutex);
	/* If we are in probeonly mode stop at DASD_STATE_READY. */
	अगर (dasd_probeonly && target > DASD_STATE_READY)
		target = DASD_STATE_READY;
	अगर (device->target != target) अणु
		अगर (device->state == target)
			wake_up(&dasd_init_रुकोq);
		device->target = target;
	पूर्ण
	अगर (device->state != device->target)
		dasd_change_state(device);
	mutex_unlock(&device->state_mutex);
	dasd_put_device(device);
पूर्ण
EXPORT_SYMBOL(dasd_set_target_state);

/*
 * Enable devices with device numbers in [from..to].
 */
अटल अंतरभूत पूर्णांक _रुको_क्रम_device(काष्ठा dasd_device *device)
अणु
	वापस (device->state == device->target);
पूर्ण

व्योम dasd_enable_device(काष्ठा dasd_device *device)
अणु
	dasd_set_target_state(device, DASD_STATE_ONLINE);
	अगर (device->state <= DASD_STATE_KNOWN)
		/* No discipline क्रम device found. */
		dasd_set_target_state(device, DASD_STATE_NEW);
	/* Now रुको क्रम the devices to come up. */
	रुको_event(dasd_init_रुकोq, _रुको_क्रम_device(device));

	dasd_reload_device(device);
	अगर (device->discipline->kick_validate)
		device->discipline->kick_validate(device);
पूर्ण
EXPORT_SYMBOL(dasd_enable_device);

/*
 * SECTION: device operation (पूर्णांकerrupt handler, start i/o, term i/o ...)
 */

अचिन्हित पूर्णांक dasd_global_profile_level = DASD_PROखाता_OFF;

#अगर_घोषित CONFIG_DASD_PROखाता
काष्ठा dasd_profile dasd_global_profile = अणु
	.lock = __SPIN_LOCK_UNLOCKED(dasd_global_profile.lock),
पूर्ण;
अटल काष्ठा dentry *dasd_debugfs_global_entry;

/*
 * Add profiling inक्रमmation क्रम cqr beक्रमe execution.
 */
अटल व्योम dasd_profile_start(काष्ठा dasd_block *block,
			       काष्ठा dasd_ccw_req *cqr,
			       काष्ठा request *req)
अणु
	काष्ठा list_head *l;
	अचिन्हित पूर्णांक counter;
	काष्ठा dasd_device *device;

	/* count the length of the chanq क्रम statistics */
	counter = 0;
	अगर (dasd_global_profile_level || block->profile.data)
		list_क्रम_each(l, &block->ccw_queue)
			अगर (++counter >= 31)
				अवरोध;

	spin_lock(&dasd_global_profile.lock);
	अगर (dasd_global_profile.data) अणु
		dasd_global_profile.data->dasd_io_nr_req[counter]++;
		अगर (rq_data_dir(req) == READ)
			dasd_global_profile.data->dasd_पढ़ो_nr_req[counter]++;
	पूर्ण
	spin_unlock(&dasd_global_profile.lock);

	spin_lock(&block->profile.lock);
	अगर (block->profile.data) अणु
		block->profile.data->dasd_io_nr_req[counter]++;
		अगर (rq_data_dir(req) == READ)
			block->profile.data->dasd_पढ़ो_nr_req[counter]++;
	पूर्ण
	spin_unlock(&block->profile.lock);

	/*
	 * We count the request क्रम the start device, even though it may run on
	 * some other device due to error recovery. This way we make sure that
	 * we count each request only once.
	 */
	device = cqr->startdev;
	अगर (device->profile.data) अणु
		counter = 1; /* request is not yet queued on the start device */
		list_क्रम_each(l, &device->ccw_queue)
			अगर (++counter >= 31)
				अवरोध;
	पूर्ण
	spin_lock(&device->profile.lock);
	अगर (device->profile.data) अणु
		device->profile.data->dasd_io_nr_req[counter]++;
		अगर (rq_data_dir(req) == READ)
			device->profile.data->dasd_पढ़ो_nr_req[counter]++;
	पूर्ण
	spin_unlock(&device->profile.lock);
पूर्ण

/*
 * Add profiling inक्रमmation क्रम cqr after execution.
 */

#घोषणा dasd_profile_counter(value, index)			   \
अणु								   \
	क्रम (index = 0; index < 31 && value >> (2+index); index++) \
		;						   \
पूर्ण

अटल व्योम dasd_profile_end_add_data(काष्ठा dasd_profile_info *data,
				      पूर्णांक is_alias,
				      पूर्णांक is_tpm,
				      पूर्णांक is_पढ़ो,
				      दीर्घ sectors,
				      पूर्णांक sectors_ind,
				      पूर्णांक totसमय_ind,
				      पूर्णांक totसमयps_ind,
				      पूर्णांक strसमय_ind,
				      पूर्णांक irqसमय_ind,
				      पूर्णांक irqसमयps_ind,
				      पूर्णांक endसमय_ind)
अणु
	/* in हाल of an overflow, reset the whole profile */
	अगर (data->dasd_io_reqs == अच_पूर्णांक_उच्च) अणु
			स_रखो(data, 0, माप(*data));
			kसमय_get_real_ts64(&data->starttod);
	पूर्ण
	data->dasd_io_reqs++;
	data->dasd_io_sects += sectors;
	अगर (is_alias)
		data->dasd_io_alias++;
	अगर (is_tpm)
		data->dasd_io_tpm++;

	data->dasd_io_secs[sectors_ind]++;
	data->dasd_io_बार[totसमय_ind]++;
	data->dasd_io_timps[totसमयps_ind]++;
	data->dasd_io_समय1[strसमय_ind]++;
	data->dasd_io_समय2[irqसमय_ind]++;
	data->dasd_io_समय2ps[irqसमयps_ind]++;
	data->dasd_io_समय3[endसमय_ind]++;

	अगर (is_पढ़ो) अणु
		data->dasd_पढ़ो_reqs++;
		data->dasd_पढ़ो_sects += sectors;
		अगर (is_alias)
			data->dasd_पढ़ो_alias++;
		अगर (is_tpm)
			data->dasd_पढ़ो_tpm++;
		data->dasd_पढ़ो_secs[sectors_ind]++;
		data->dasd_पढ़ो_बार[totसमय_ind]++;
		data->dasd_पढ़ो_समय1[strसमय_ind]++;
		data->dasd_पढ़ो_समय2[irqसमय_ind]++;
		data->dasd_पढ़ो_समय3[endसमय_ind]++;
	पूर्ण
पूर्ण

अटल व्योम dasd_profile_end(काष्ठा dasd_block *block,
			     काष्ठा dasd_ccw_req *cqr,
			     काष्ठा request *req)
अणु
	अचिन्हित दीर्घ strसमय, irqसमय, endसमय, totसमय;
	अचिन्हित दीर्घ totसमयps, sectors;
	काष्ठा dasd_device *device;
	पूर्णांक sectors_ind, totसमय_ind, totसमयps_ind, strसमय_ind;
	पूर्णांक irqसमय_ind, irqसमयps_ind, endसमय_ind;
	काष्ठा dasd_profile_info *data;

	device = cqr->startdev;
	अगर (!(dasd_global_profile_level ||
	      block->profile.data ||
	      device->profile.data))
		वापस;

	sectors = blk_rq_sectors(req);
	अगर (!cqr->buildclk || !cqr->startclk ||
	    !cqr->stopclk || !cqr->endclk ||
	    !sectors)
		वापस;

	strसमय = ((cqr->startclk - cqr->buildclk) >> 12);
	irqसमय = ((cqr->stopclk - cqr->startclk) >> 12);
	endसमय = ((cqr->endclk - cqr->stopclk) >> 12);
	totसमय = ((cqr->endclk - cqr->buildclk) >> 12);
	totसमयps = totसमय / sectors;

	dasd_profile_counter(sectors, sectors_ind);
	dasd_profile_counter(totसमय, totसमय_ind);
	dasd_profile_counter(totसमयps, totसमयps_ind);
	dasd_profile_counter(strसमय, strसमय_ind);
	dasd_profile_counter(irqसमय, irqसमय_ind);
	dasd_profile_counter(irqसमय / sectors, irqसमयps_ind);
	dasd_profile_counter(endसमय, endसमय_ind);

	spin_lock(&dasd_global_profile.lock);
	अगर (dasd_global_profile.data) अणु
		data = dasd_global_profile.data;
		data->dasd_sum_बार += totसमय;
		data->dasd_sum_समय_str += strसमय;
		data->dasd_sum_समय_irq += irqसमय;
		data->dasd_sum_समय_end += endसमय;
		dasd_profile_end_add_data(dasd_global_profile.data,
					  cqr->startdev != block->base,
					  cqr->cpmode == 1,
					  rq_data_dir(req) == READ,
					  sectors, sectors_ind, totसमय_ind,
					  totसमयps_ind, strसमय_ind,
					  irqसमय_ind, irqसमयps_ind,
					  endसमय_ind);
	पूर्ण
	spin_unlock(&dasd_global_profile.lock);

	spin_lock(&block->profile.lock);
	अगर (block->profile.data) अणु
		data = block->profile.data;
		data->dasd_sum_बार += totसमय;
		data->dasd_sum_समय_str += strसमय;
		data->dasd_sum_समय_irq += irqसमय;
		data->dasd_sum_समय_end += endसमय;
		dasd_profile_end_add_data(block->profile.data,
					  cqr->startdev != block->base,
					  cqr->cpmode == 1,
					  rq_data_dir(req) == READ,
					  sectors, sectors_ind, totसमय_ind,
					  totसमयps_ind, strसमय_ind,
					  irqसमय_ind, irqसमयps_ind,
					  endसमय_ind);
	पूर्ण
	spin_unlock(&block->profile.lock);

	spin_lock(&device->profile.lock);
	अगर (device->profile.data) अणु
		data = device->profile.data;
		data->dasd_sum_बार += totसमय;
		data->dasd_sum_समय_str += strसमय;
		data->dasd_sum_समय_irq += irqसमय;
		data->dasd_sum_समय_end += endसमय;
		dasd_profile_end_add_data(device->profile.data,
					  cqr->startdev != block->base,
					  cqr->cpmode == 1,
					  rq_data_dir(req) == READ,
					  sectors, sectors_ind, totसमय_ind,
					  totसमयps_ind, strसमय_ind,
					  irqसमय_ind, irqसमयps_ind,
					  endसमय_ind);
	पूर्ण
	spin_unlock(&device->profile.lock);
पूर्ण

व्योम dasd_profile_reset(काष्ठा dasd_profile *profile)
अणु
	काष्ठा dasd_profile_info *data;

	spin_lock_bh(&profile->lock);
	data = profile->data;
	अगर (!data) अणु
		spin_unlock_bh(&profile->lock);
		वापस;
	पूर्ण
	स_रखो(data, 0, माप(*data));
	kसमय_get_real_ts64(&data->starttod);
	spin_unlock_bh(&profile->lock);
पूर्ण

पूर्णांक dasd_profile_on(काष्ठा dasd_profile *profile)
अणु
	काष्ठा dasd_profile_info *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	spin_lock_bh(&profile->lock);
	अगर (profile->data) अणु
		spin_unlock_bh(&profile->lock);
		kमुक्त(data);
		वापस 0;
	पूर्ण
	kसमय_get_real_ts64(&data->starttod);
	profile->data = data;
	spin_unlock_bh(&profile->lock);
	वापस 0;
पूर्ण

व्योम dasd_profile_off(काष्ठा dasd_profile *profile)
अणु
	spin_lock_bh(&profile->lock);
	kमुक्त(profile->data);
	profile->data = शून्य;
	spin_unlock_bh(&profile->lock);
पूर्ण

अक्षर *dasd_get_user_string(स्थिर अक्षर __user *user_buf, माप_प्रकार user_len)
अणु
	अक्षर *buffer;

	buffer = vदो_स्मृति(user_len + 1);
	अगर (buffer == शून्य)
		वापस ERR_PTR(-ENOMEM);
	अगर (copy_from_user(buffer, user_buf, user_len) != 0) अणु
		vमुक्त(buffer);
		वापस ERR_PTR(-EFAULT);
	पूर्ण
	/* got the string, now strip linefeed. */
	अगर (buffer[user_len - 1] == '\n')
		buffer[user_len - 1] = 0;
	अन्यथा
		buffer[user_len] = 0;
	वापस buffer;
पूर्ण

अटल sमाप_प्रकार dasd_stats_ग_लिखो(काष्ठा file *file,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार user_len, loff_t *pos)
अणु
	अक्षर *buffer, *str;
	पूर्णांक rc;
	काष्ठा seq_file *m = (काष्ठा seq_file *)file->निजी_data;
	काष्ठा dasd_profile *prof = m->निजी;

	अगर (user_len > 65536)
		user_len = 65536;
	buffer = dasd_get_user_string(user_buf, user_len);
	अगर (IS_ERR(buffer))
		वापस PTR_ERR(buffer);

	str = skip_spaces(buffer);
	rc = user_len;
	अगर (म_भेदन(str, "reset", 5) == 0) अणु
		dasd_profile_reset(prof);
	पूर्ण अन्यथा अगर (म_भेदन(str, "on", 2) == 0) अणु
		rc = dasd_profile_on(prof);
		अगर (rc)
			जाओ out;
		rc = user_len;
		अगर (prof == &dasd_global_profile) अणु
			dasd_profile_reset(prof);
			dasd_global_profile_level = DASD_PROखाता_GLOBAL_ONLY;
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेदन(str, "off", 3) == 0) अणु
		अगर (prof == &dasd_global_profile)
			dasd_global_profile_level = DASD_PROखाता_OFF;
		dasd_profile_off(prof);
	पूर्ण अन्यथा
		rc = -EINVAL;
out:
	vमुक्त(buffer);
	वापस rc;
पूर्ण

अटल व्योम dasd_stats_array(काष्ठा seq_file *m, अचिन्हित पूर्णांक *array)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++)
		seq_म_लिखो(m, "%u ", array[i]);
	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम dasd_stats_seq_prपूर्णांक(काष्ठा seq_file *m,
				 काष्ठा dasd_profile_info *data)
अणु
	seq_म_लिखो(m, "start_time %lld.%09ld\n",
		   (s64)data->starttod.tv_sec, data->starttod.tv_nsec);
	seq_म_लिखो(m, "total_requests %u\n", data->dasd_io_reqs);
	seq_म_लिखो(m, "total_sectors %u\n", data->dasd_io_sects);
	seq_म_लिखो(m, "total_pav %u\n", data->dasd_io_alias);
	seq_म_लिखो(m, "total_hpf %u\n", data->dasd_io_tpm);
	seq_म_लिखो(m, "avg_total %lu\n", data->dasd_io_reqs ?
		   data->dasd_sum_बार / data->dasd_io_reqs : 0UL);
	seq_म_लिखो(m, "avg_build_to_ssch %lu\n", data->dasd_io_reqs ?
		   data->dasd_sum_समय_str / data->dasd_io_reqs : 0UL);
	seq_म_लिखो(m, "avg_ssch_to_irq %lu\n", data->dasd_io_reqs ?
		   data->dasd_sum_समय_irq / data->dasd_io_reqs : 0UL);
	seq_म_लिखो(m, "avg_irq_to_end %lu\n", data->dasd_io_reqs ?
		   data->dasd_sum_समय_end / data->dasd_io_reqs : 0UL);
	seq_माला_दो(m, "histogram_sectors ");
	dasd_stats_array(m, data->dasd_io_secs);
	seq_माला_दो(m, "histogram_io_times ");
	dasd_stats_array(m, data->dasd_io_बार);
	seq_माला_दो(m, "histogram_io_times_weighted ");
	dasd_stats_array(m, data->dasd_io_timps);
	seq_माला_दो(m, "histogram_time_build_to_ssch ");
	dasd_stats_array(m, data->dasd_io_समय1);
	seq_माला_दो(m, "histogram_time_ssch_to_irq ");
	dasd_stats_array(m, data->dasd_io_समय2);
	seq_माला_दो(m, "histogram_time_ssch_to_irq_weighted ");
	dasd_stats_array(m, data->dasd_io_समय2ps);
	seq_माला_दो(m, "histogram_time_irq_to_end ");
	dasd_stats_array(m, data->dasd_io_समय3);
	seq_माला_दो(m, "histogram_ccw_queue_length ");
	dasd_stats_array(m, data->dasd_io_nr_req);
	seq_म_लिखो(m, "total_read_requests %u\n", data->dasd_पढ़ो_reqs);
	seq_म_लिखो(m, "total_read_sectors %u\n", data->dasd_पढ़ो_sects);
	seq_म_लिखो(m, "total_read_pav %u\n", data->dasd_पढ़ो_alias);
	seq_म_लिखो(m, "total_read_hpf %u\n", data->dasd_पढ़ो_tpm);
	seq_माला_दो(m, "histogram_read_sectors ");
	dasd_stats_array(m, data->dasd_पढ़ो_secs);
	seq_माला_दो(m, "histogram_read_times ");
	dasd_stats_array(m, data->dasd_पढ़ो_बार);
	seq_माला_दो(m, "histogram_read_time_build_to_ssch ");
	dasd_stats_array(m, data->dasd_पढ़ो_समय1);
	seq_माला_दो(m, "histogram_read_time_ssch_to_irq ");
	dasd_stats_array(m, data->dasd_पढ़ो_समय2);
	seq_माला_दो(m, "histogram_read_time_irq_to_end ");
	dasd_stats_array(m, data->dasd_पढ़ो_समय3);
	seq_माला_दो(m, "histogram_read_ccw_queue_length ");
	dasd_stats_array(m, data->dasd_पढ़ो_nr_req);
पूर्ण

अटल पूर्णांक dasd_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dasd_profile *profile;
	काष्ठा dasd_profile_info *data;

	profile = m->निजी;
	spin_lock_bh(&profile->lock);
	data = profile->data;
	अगर (!data) अणु
		spin_unlock_bh(&profile->lock);
		seq_माला_दो(m, "disabled\n");
		वापस 0;
	पूर्ण
	dasd_stats_seq_prपूर्णांक(m, data);
	spin_unlock_bh(&profile->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक dasd_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dasd_profile *profile = inode->i_निजी;
	वापस single_खोलो(file, dasd_stats_show, profile);
पूर्ण

अटल स्थिर काष्ठा file_operations dasd_stats_raw_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= dasd_stats_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
	.ग_लिखो		= dasd_stats_ग_लिखो,
पूर्ण;

अटल व्योम dasd_profile_init(काष्ठा dasd_profile *profile,
			      काष्ठा dentry *base_dentry)
अणु
	umode_t mode;
	काष्ठा dentry *pde;

	अगर (!base_dentry)
		वापस;
	profile->dentry = शून्य;
	profile->data = शून्य;
	mode = (S_IRUSR | S_IWUSR | S_IFREG);
	pde = debugfs_create_file("statistics", mode, base_dentry,
				  profile, &dasd_stats_raw_fops);
	अगर (pde && !IS_ERR(pde))
		profile->dentry = pde;
	वापस;
पूर्ण

अटल व्योम dasd_profile_निकास(काष्ठा dasd_profile *profile)
अणु
	dasd_profile_off(profile);
	debugfs_हटाओ(profile->dentry);
	profile->dentry = शून्य;
पूर्ण

अटल व्योम dasd_statistics_हटाओroot(व्योम)
अणु
	dasd_global_profile_level = DASD_PROखाता_OFF;
	dasd_profile_निकास(&dasd_global_profile);
	debugfs_हटाओ(dasd_debugfs_global_entry);
	debugfs_हटाओ(dasd_debugfs_root_entry);
पूर्ण

अटल व्योम dasd_statistics_createroot(व्योम)
अणु
	काष्ठा dentry *pde;

	dasd_debugfs_root_entry = शून्य;
	pde = debugfs_create_dir("dasd", शून्य);
	अगर (!pde || IS_ERR(pde))
		जाओ error;
	dasd_debugfs_root_entry = pde;
	pde = debugfs_create_dir("global", dasd_debugfs_root_entry);
	अगर (!pde || IS_ERR(pde))
		जाओ error;
	dasd_debugfs_global_entry = pde;
	dasd_profile_init(&dasd_global_profile, dasd_debugfs_global_entry);
	वापस;

error:
	DBF_EVENT(DBF_ERR, "%s",
		  "Creation of the dasd debugfs interface failed");
	dasd_statistics_हटाओroot();
	वापस;
पूर्ण

#अन्यथा
#घोषणा dasd_profile_start(block, cqr, req) करो अणुपूर्ण जबतक (0)
#घोषणा dasd_profile_end(block, cqr, req) करो अणुपूर्ण जबतक (0)

अटल व्योम dasd_statistics_createroot(व्योम)
अणु
	वापस;
पूर्ण

अटल व्योम dasd_statistics_हटाओroot(व्योम)
अणु
	वापस;
पूर्ण

पूर्णांक dasd_stats_generic_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_माला_दो(m, "Statistics are not activated in this kernel\n");
	वापस 0;
पूर्ण

अटल व्योम dasd_profile_init(काष्ठा dasd_profile *profile,
			      काष्ठा dentry *base_dentry)
अणु
	वापस;
पूर्ण

अटल व्योम dasd_profile_निकास(काष्ठा dasd_profile *profile)
अणु
	वापस;
पूर्ण

पूर्णांक dasd_profile_on(काष्ठा dasd_profile *profile)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर				/* CONFIG_DASD_PROखाता */

अटल पूर्णांक dasd_hosts_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक rc = -EOPNOTSUPP;

	device = m->निजी;
	dasd_get_device(device);

	अगर (device->discipline->hosts_prपूर्णांक)
		rc = device->discipline->hosts_prपूर्णांक(device, m);

	dasd_put_device(device);
	वापस rc;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dasd_hosts);

अटल व्योम dasd_hosts_निकास(काष्ठा dasd_device *device)
अणु
	debugfs_हटाओ(device->hosts_dentry);
	device->hosts_dentry = शून्य;
पूर्ण

अटल व्योम dasd_hosts_init(काष्ठा dentry *base_dentry,
			    काष्ठा dasd_device *device)
अणु
	काष्ठा dentry *pde;
	umode_t mode;

	अगर (!base_dentry)
		वापस;

	mode = S_IRUSR | S_IFREG;
	pde = debugfs_create_file("host_access_list", mode, base_dentry,
				  device, &dasd_hosts_fops);
	अगर (pde && !IS_ERR(pde))
		device->hosts_dentry = pde;
पूर्ण

काष्ठा dasd_ccw_req *dasd_sदो_स्मृति_request(पूर्णांक magic, पूर्णांक cplength, पूर्णांक datasize,
					  काष्ठा dasd_device *device,
					  काष्ठा dasd_ccw_req *cqr)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर *data, *chunk;
	पूर्णांक size = 0;

	अगर (cplength > 0)
		size += cplength * माप(काष्ठा ccw1);
	अगर (datasize > 0)
		size += datasize;
	अगर (!cqr)
		size += (माप(*cqr) + 7L) & -8L;

	spin_lock_irqsave(&device->mem_lock, flags);
	data = chunk = dasd_alloc_chunk(&device->ccw_chunks, size);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	अगर (!chunk)
		वापस ERR_PTR(-ENOMEM);
	अगर (!cqr) अणु
		cqr = (व्योम *) data;
		data += (माप(*cqr) + 7L) & -8L;
	पूर्ण
	स_रखो(cqr, 0, माप(*cqr));
	cqr->mem_chunk = chunk;
	अगर (cplength > 0) अणु
		cqr->cpaddr = data;
		data += cplength * माप(काष्ठा ccw1);
		स_रखो(cqr->cpaddr, 0, cplength * माप(काष्ठा ccw1));
	पूर्ण
	अगर (datasize > 0) अणु
		cqr->data = data;
 		स_रखो(cqr->data, 0, datasize);
	पूर्ण
	cqr->magic = magic;
	set_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	dasd_get_device(device);
	वापस cqr;
पूर्ण
EXPORT_SYMBOL(dasd_sदो_स्मृति_request);

काष्ठा dasd_ccw_req *dasd_fदो_स्मृति_request(पूर्णांक magic, पूर्णांक cplength,
					  पूर्णांक datasize,
					  काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	अचिन्हित दीर्घ flags;
	पूर्णांक size, cqr_size;
	अक्षर *data;

	cqr_size = (माप(*cqr) + 7L) & -8L;
	size = cqr_size;
	अगर (cplength > 0)
		size += cplength * माप(काष्ठा ccw1);
	अगर (datasize > 0)
		size += datasize;

	spin_lock_irqsave(&device->mem_lock, flags);
	cqr = dasd_alloc_chunk(&device->ese_chunks, size);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	अगर (!cqr)
		वापस ERR_PTR(-ENOMEM);
	स_रखो(cqr, 0, माप(*cqr));
	data = (अक्षर *)cqr + cqr_size;
	cqr->cpaddr = शून्य;
	अगर (cplength > 0) अणु
		cqr->cpaddr = data;
		data += cplength * माप(काष्ठा ccw1);
		स_रखो(cqr->cpaddr, 0, cplength * माप(काष्ठा ccw1));
	पूर्ण
	cqr->data = शून्य;
	अगर (datasize > 0) अणु
		cqr->data = data;
		स_रखो(cqr->data, 0, datasize);
	पूर्ण

	cqr->magic = magic;
	set_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	dasd_get_device(device);

	वापस cqr;
पूर्ण
EXPORT_SYMBOL(dasd_fदो_स्मृति_request);

व्योम dasd_sमुक्त_request(काष्ठा dasd_ccw_req *cqr, काष्ठा dasd_device *device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device->mem_lock, flags);
	dasd_मुक्त_chunk(&device->ccw_chunks, cqr->mem_chunk);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	dasd_put_device(device);
पूर्ण
EXPORT_SYMBOL(dasd_sमुक्त_request);

व्योम dasd_fमुक्त_request(काष्ठा dasd_ccw_req *cqr, काष्ठा dasd_device *device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device->mem_lock, flags);
	dasd_मुक्त_chunk(&device->ese_chunks, cqr);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	dasd_put_device(device);
पूर्ण
EXPORT_SYMBOL(dasd_fमुक्त_request);

/*
 * Check discipline magic in cqr.
 */
अटल अंतरभूत पूर्णांक dasd_check_cqr(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;

	अगर (cqr == शून्य)
		वापस -EINVAL;
	device = cqr->startdev;
	अगर (म_भेदन((अक्षर *) &cqr->magic, device->discipline->ebcname, 4)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device,
			    " dasd_ccw_req 0x%08x magic doesn't match"
			    " discipline 0x%08x",
			    cqr->magic,
			    *(अचिन्हित पूर्णांक *) device->discipline->name);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Terminate the current i/o and set the request to clear_pending.
 * Timer keeps device runnig.
 * ccw_device_clear can fail अगर the i/o subप्रणाली
 * is in a bad mood.
 */
पूर्णांक dasd_term_IO(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक retries, rc;
	अक्षर errorstring[ERRORLENGTH];

	/* Check the cqr */
	rc = dasd_check_cqr(cqr);
	अगर (rc)
		वापस rc;
	retries = 0;
	device = (काष्ठा dasd_device *) cqr->startdev;
	जबतक ((retries < 5) && (cqr->status == DASD_CQR_IN_IO)) अणु
		rc = ccw_device_clear(device->cdev, (दीर्घ) cqr);
		चयन (rc) अणु
		हाल 0:	/* termination successful */
			cqr->status = DASD_CQR_CLEAR_PENDING;
			cqr->stopclk = get_tod_घड़ी();
			cqr->startसमय = 0;
			DBF_DEV_EVENT(DBF_DEBUG, device,
				      "terminate cqr %p successful",
				      cqr);
			अवरोध;
		हाल -ENODEV:
			DBF_DEV_EVENT(DBF_ERR, device, "%s",
				      "device gone, retry");
			अवरोध;
		हाल -EINVAL:
			/*
			 * device not valid so no I/O could be running
			 * handle CQR as termination successful
			 */
			cqr->status = DASD_CQR_CLEARED;
			cqr->stopclk = get_tod_घड़ी();
			cqr->startसमय = 0;
			/* no retries क्रम invalid devices */
			cqr->retries = -1;
			DBF_DEV_EVENT(DBF_ERR, device, "%s",
				      "EINVAL, handle as terminated");
			/* fake rc to success */
			rc = 0;
			अवरोध;
		शेष:
			/* पूर्णांकernal error 10 - unknown rc*/
			snम_लिखो(errorstring, ERRORLENGTH, "10 %d", rc);
			dev_err(&device->cdev->dev, "An error occurred in the "
				"DASD device driver, reason=%s\n", errorstring);
			BUG();
			अवरोध;
		पूर्ण
		retries++;
	पूर्ण
	dasd_schedule_device_bh(device);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(dasd_term_IO);

/*
 * Start the i/o. This start_IO can fail अगर the channel is really busy.
 * In that हाल set up a समयr to start the request later.
 */
पूर्णांक dasd_start_IO(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक rc;
	अक्षर errorstring[ERRORLENGTH];

	/* Check the cqr */
	rc = dasd_check_cqr(cqr);
	अगर (rc) अणु
		cqr->पूर्णांकrc = rc;
		वापस rc;
	पूर्ण
	device = (काष्ठा dasd_device *) cqr->startdev;
	अगर (((cqr->block &&
	      test_bit(DASD_FLAG_LOCK_STOLEN, &cqr->block->base->flags)) ||
	     test_bit(DASD_FLAG_LOCK_STOLEN, &device->flags)) &&
	    !test_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags)) अणु
		DBF_DEV_EVENT(DBF_DEBUG, device, "start_IO: return request %p "
			      "because of stolen lock", cqr);
		cqr->status = DASD_CQR_ERROR;
		cqr->पूर्णांकrc = -EPERM;
		वापस -EPERM;
	पूर्ण
	अगर (cqr->retries < 0) अणु
		/* पूर्णांकernal error 14 - start_IO run out of retries */
		प्र_लिखो(errorstring, "14 %p", cqr);
		dev_err(&device->cdev->dev, "An error occurred in the DASD "
			"device driver, reason=%s\n", errorstring);
		cqr->status = DASD_CQR_ERROR;
		वापस -EIO;
	पूर्ण
	cqr->startclk = get_tod_घड़ी();
	cqr->startसमय = jअगरfies;
	cqr->retries--;
	अगर (!test_bit(DASD_CQR_VERIFY_PATH, &cqr->flags)) अणु
		cqr->lpm &= dasd_path_get_opm(device);
		अगर (!cqr->lpm)
			cqr->lpm = dasd_path_get_opm(device);
	पूर्ण
	अगर (cqr->cpmode == 1) अणु
		rc = ccw_device_पंचांग_start(device->cdev, cqr->cpaddr,
					 (दीर्घ) cqr, cqr->lpm);
	पूर्ण अन्यथा अणु
		rc = ccw_device_start(device->cdev, cqr->cpaddr,
				      (दीर्घ) cqr, cqr->lpm, 0);
	पूर्ण
	चयन (rc) अणु
	हाल 0:
		cqr->status = DASD_CQR_IN_IO;
		अवरोध;
	हाल -EBUSY:
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "start_IO: device busy, retry later");
		अवरोध;
	हाल -EACCES:
		/* -EACCES indicates that the request used only a subset of the
		 * available paths and all these paths are gone. If the lpm of
		 * this request was only a subset of the opm (e.g. the ppm) then
		 * we just करो a retry with all available paths.
		 * If we alपढ़ोy use the full opm, something is amiss, and we
		 * need a full path verअगरication.
		 */
		अगर (test_bit(DASD_CQR_VERIFY_PATH, &cqr->flags)) अणु
			DBF_DEV_EVENT(DBF_WARNING, device,
				      "start_IO: selected paths gone (%x)",
				      cqr->lpm);
		पूर्ण अन्यथा अगर (cqr->lpm != dasd_path_get_opm(device)) अणु
			cqr->lpm = dasd_path_get_opm(device);
			DBF_DEV_EVENT(DBF_DEBUG, device, "%s",
				      "start_IO: selected paths gone,"
				      " retry on all paths");
		पूर्ण अन्यथा अणु
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				      "start_IO: all paths in opm gone,"
				      " do path verification");
			dasd_generic_last_path_gone(device);
			dasd_path_no_path(device);
			dasd_path_set_tbvpm(device,
					  ccw_device_get_path_mask(
						  device->cdev));
		पूर्ण
		अवरोध;
	हाल -ENODEV:
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "start_IO: -ENODEV device gone, retry");
		अवरोध;
	हाल -EIO:
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "start_IO: -EIO device gone, retry");
		अवरोध;
	हाल -EINVAL:
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "start_IO: -EINVAL device currently "
			      "not accessible");
		अवरोध;
	शेष:
		/* पूर्णांकernal error 11 - unknown rc */
		snम_लिखो(errorstring, ERRORLENGTH, "11 %d", rc);
		dev_err(&device->cdev->dev,
			"An error occurred in the DASD device driver, "
			"reason=%s\n", errorstring);
		BUG();
		अवरोध;
	पूर्ण
	cqr->पूर्णांकrc = rc;
	वापस rc;
पूर्ण
EXPORT_SYMBOL(dasd_start_IO);

/*
 * Timeout function क्रम dasd devices. This is used क्रम dअगरferent purposes
 *  1) missing पूर्णांकerrupt handler क्रम normal operation
 *  2) delayed start of request where start_IO failed with -EBUSY
 *  3) समयout क्रम missing state change पूर्णांकerrupts
 * The head of the ccw queue will have status DASD_CQR_IN_IO क्रम 1),
 * DASD_CQR_QUEUED क्रम 2) and 3).
 */
अटल व्योम dasd_device_समयout(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_device *device;

	device = from_समयr(device, t, समयr);
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	/* re-activate request queue */
	dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_PENDING);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	dasd_schedule_device_bh(device);
पूर्ण

/*
 * Setup समयout क्रम a device in jअगरfies.
 */
व्योम dasd_device_set_समयr(काष्ठा dasd_device *device, पूर्णांक expires)
अणु
	अगर (expires == 0)
		del_समयr(&device->समयr);
	अन्यथा
		mod_समयr(&device->समयr, jअगरfies + expires);
पूर्ण
EXPORT_SYMBOL(dasd_device_set_समयr);

/*
 * Clear समयout क्रम a device.
 */
व्योम dasd_device_clear_समयr(काष्ठा dasd_device *device)
अणु
	del_समयr(&device->समयr);
पूर्ण
EXPORT_SYMBOL(dasd_device_clear_समयr);

अटल व्योम dasd_handle_समाप्तed_request(काष्ठा ccw_device *cdev,
				       अचिन्हित दीर्घ पूर्णांकparm)
अणु
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा dasd_device *device;

	अगर (!पूर्णांकparm)
		वापस;
	cqr = (काष्ठा dasd_ccw_req *) पूर्णांकparm;
	अगर (cqr->status != DASD_CQR_IN_IO) अणु
		DBF_EVENT_DEVID(DBF_DEBUG, cdev,
				"invalid status in handle_killed_request: "
				"%02x", cqr->status);
		वापस;
	पूर्ण

	device = dasd_device_from_cdev_locked(cdev);
	अगर (IS_ERR(device)) अणु
		DBF_EVENT_DEVID(DBF_DEBUG, cdev, "%s",
				"unable to get device from cdev");
		वापस;
	पूर्ण

	अगर (!cqr->startdev ||
	    device != cqr->startdev ||
	    म_भेदन(cqr->startdev->discipline->ebcname,
		    (अक्षर *) &cqr->magic, 4)) अणु
		DBF_EVENT_DEVID(DBF_DEBUG, cdev, "%s",
				"invalid device in request");
		dasd_put_device(device);
		वापस;
	पूर्ण

	/* Schedule request to be retried. */
	cqr->status = DASD_CQR_QUEUED;

	dasd_device_clear_समयr(device);
	dasd_schedule_device_bh(device);
	dasd_put_device(device);
पूर्ण

व्योम dasd_generic_handle_state_change(काष्ठा dasd_device *device)
अणु
	/* First of all start sense subप्रणाली status request. */
	dasd_eer_snss(device);

	dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_PENDING);
	dasd_schedule_device_bh(device);
	अगर (device->block) अणु
		dasd_schedule_block_bh(device->block);
		अगर (device->block->request_queue)
			blk_mq_run_hw_queues(device->block->request_queue,
					     true);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_handle_state_change);

अटल पूर्णांक dasd_check_hpf_error(काष्ठा irb *irb)
अणु
	वापस (scsw_पंचांग_is_valid_schxs(&irb->scsw) &&
	    (irb->scsw.पंचांग.sesq == SCSW_SESQ_DEV_NOFCX ||
	     irb->scsw.पंचांग.sesq == SCSW_SESQ_PATH_NOFCX));
पूर्ण

अटल पूर्णांक dasd_ese_needs_क्रमmat(काष्ठा dasd_block *block, काष्ठा irb *irb)
अणु
	काष्ठा dasd_device *device = शून्य;
	u8 *sense = शून्य;

	अगर (!block)
		वापस 0;
	device = block->base;
	अगर (!device || !device->discipline->is_ese)
		वापस 0;
	अगर (!device->discipline->is_ese(device))
		वापस 0;

	sense = dasd_get_sense(irb);
	अगर (!sense)
		वापस 0;

	वापस !!(sense[1] & SNS1_NO_REC_FOUND) ||
		!!(sense[1] & SNS1_खाता_PROTECTED) ||
		scsw_cstat(&irb->scsw) == SCHN_STAT_INCORR_LEN;
पूर्ण

अटल पूर्णांक dasd_ese_oos_cond(u8 *sense)
अणु
	वापस sense[0] & SNS0_EQUIPMENT_CHECK &&
		sense[1] & SNS1_PERM_ERR &&
		sense[1] & SNS1_WRITE_INHIBITED &&
		sense[25] == 0x01;
पूर्ण

/*
 * Interrupt handler क्रम "normal" ssch-io based dasd devices.
 */
व्योम dasd_पूर्णांक_handler(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm,
		      काष्ठा irb *irb)
अणु
	काष्ठा dasd_ccw_req *cqr, *next, *fcqr;
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ now;
	पूर्णांक nrf_suppressed = 0;
	पूर्णांक fp_suppressed = 0;
	u8 *sense = शून्य;
	पूर्णांक expires;

	cqr = (काष्ठा dasd_ccw_req *) पूर्णांकparm;
	अगर (IS_ERR(irb)) अणु
		चयन (PTR_ERR(irb)) अणु
		हाल -EIO:
			अगर (cqr && cqr->status == DASD_CQR_CLEAR_PENDING) अणु
				device = cqr->startdev;
				cqr->status = DASD_CQR_CLEARED;
				dasd_device_clear_समयr(device);
				wake_up(&dasd_flush_wq);
				dasd_schedule_device_bh(device);
				वापस;
			पूर्ण
			अवरोध;
		हाल -ETIMEDOUT:
			DBF_EVENT_DEVID(DBF_WARNING, cdev, "%s: "
					"request timed out\n", __func__);
			अवरोध;
		शेष:
			DBF_EVENT_DEVID(DBF_WARNING, cdev, "%s: "
					"unknown error %ld\n", __func__,
					PTR_ERR(irb));
		पूर्ण
		dasd_handle_समाप्तed_request(cdev, पूर्णांकparm);
		वापस;
	पूर्ण

	now = get_tod_घड़ी();
	/* check क्रम conditions that should be handled immediately */
	अगर (!cqr ||
	    !(scsw_dstat(&irb->scsw) == (DEV_STAT_CHN_END | DEV_STAT_DEV_END) &&
	      scsw_cstat(&irb->scsw) == 0)) अणु
		अगर (cqr)
			स_नकल(&cqr->irb, irb, माप(*irb));
		device = dasd_device_from_cdev_locked(cdev);
		अगर (IS_ERR(device))
			वापस;
		/* ignore unsolicited पूर्णांकerrupts क्रम DIAG discipline */
		अगर (device->discipline == dasd_diag_discipline_poपूर्णांकer) अणु
			dasd_put_device(device);
			वापस;
		पूर्ण

		/*
		 * In some हालs 'File Protected' or 'No Record Found' errors
		 * might be expected and debug log messages क्रम the
		 * corresponding पूर्णांकerrupts shouldn't be written then.
		 * Check अगर either of the according suppress bits is set.
		 */
		sense = dasd_get_sense(irb);
		अगर (sense) अणु
			fp_suppressed = (sense[1] & SNS1_खाता_PROTECTED) &&
				test_bit(DASD_CQR_SUPPRESS_FP, &cqr->flags);
			nrf_suppressed = (sense[1] & SNS1_NO_REC_FOUND) &&
				test_bit(DASD_CQR_SUPPRESS_NRF, &cqr->flags);

			/*
			 * Extent pool probably out-of-space.
			 * Stop device and check exhaust level.
			 */
			अगर (dasd_ese_oos_cond(sense)) अणु
				dasd_generic_space_exhaust(device, cqr);
				device->discipline->ext_pool_exhaust(device, cqr);
				dasd_put_device(device);
				वापस;
			पूर्ण
		पूर्ण
		अगर (!(fp_suppressed || nrf_suppressed))
			device->discipline->dump_sense_dbf(device, irb, "int");

		अगर (device->features & DASD_FEATURE_ERPLOG)
			device->discipline->dump_sense(device, cqr, irb);
		device->discipline->check_क्रम_device_change(device, cqr, irb);
		dasd_put_device(device);
	पूर्ण

	/* check क्रम क्रम attention message */
	अगर (scsw_dstat(&irb->scsw) & DEV_STAT_ATTENTION) अणु
		device = dasd_device_from_cdev_locked(cdev);
		अगर (!IS_ERR(device)) अणु
			device->discipline->check_attention(device,
							    irb->esw.esw1.lpum);
			dasd_put_device(device);
		पूर्ण
	पूर्ण

	अगर (!cqr)
		वापस;

	device = (काष्ठा dasd_device *) cqr->startdev;
	अगर (!device ||
	    म_भेदन(device->discipline->ebcname, (अक्षर *) &cqr->magic, 4)) अणु
		DBF_EVENT_DEVID(DBF_DEBUG, cdev, "%s",
				"invalid device in request");
		वापस;
	पूर्ण

	अगर (dasd_ese_needs_क्रमmat(cqr->block, irb)) अणु
		अगर (rq_data_dir((काष्ठा request *)cqr->callback_data) == READ) अणु
			device->discipline->ese_पढ़ो(cqr, irb);
			cqr->status = DASD_CQR_SUCCESS;
			cqr->stopclk = now;
			dasd_device_clear_समयr(device);
			dasd_schedule_device_bh(device);
			वापस;
		पूर्ण
		fcqr = device->discipline->ese_क्रमmat(device, cqr, irb);
		अगर (IS_ERR(fcqr)) अणु
			अगर (PTR_ERR(fcqr) == -EINVAL) अणु
				cqr->status = DASD_CQR_ERROR;
				वापस;
			पूर्ण
			/*
			 * If we can't क्रमmat now, let the request go
			 * one extra round. Maybe we can क्रमmat later.
			 */
			cqr->status = DASD_CQR_QUEUED;
			dasd_schedule_device_bh(device);
			वापस;
		पूर्ण अन्यथा अणु
			fcqr->status = DASD_CQR_QUEUED;
			cqr->status = DASD_CQR_QUEUED;
			list_add(&fcqr->devlist, &device->ccw_queue);
			dasd_schedule_device_bh(device);
			वापस;
		पूर्ण
	पूर्ण

	/* Check क्रम clear pending */
	अगर (cqr->status == DASD_CQR_CLEAR_PENDING &&
	    scsw_fctl(&irb->scsw) & SCSW_FCTL_CLEAR_FUNC) अणु
		cqr->status = DASD_CQR_CLEARED;
		dasd_device_clear_समयr(device);
		wake_up(&dasd_flush_wq);
		dasd_schedule_device_bh(device);
		वापस;
	पूर्ण

	/* check status - the request might have been समाप्तed by dyn detach */
	अगर (cqr->status != DASD_CQR_IN_IO) अणु
		DBF_DEV_EVENT(DBF_DEBUG, device, "invalid status: bus_id %s, "
			      "status %02x", dev_name(&cdev->dev), cqr->status);
		वापस;
	पूर्ण

	next = शून्य;
	expires = 0;
	अगर (scsw_dstat(&irb->scsw) == (DEV_STAT_CHN_END | DEV_STAT_DEV_END) &&
	    scsw_cstat(&irb->scsw) == 0) अणु
		/* request was completed successfully */
		cqr->status = DASD_CQR_SUCCESS;
		cqr->stopclk = now;
		/* Start first request on queue अगर possible -> fast_io. */
		अगर (cqr->devlist.next != &device->ccw_queue) अणु
			next = list_entry(cqr->devlist.next,
					  काष्ठा dasd_ccw_req, devlist);
		पूर्ण
	पूर्ण अन्यथा अणु  /* error */
		/* check क्रम HPF error
		 * call discipline function to requeue all requests
		 * and disable HPF accordingly
		 */
		अगर (cqr->cpmode && dasd_check_hpf_error(irb) &&
		    device->discipline->handle_hpf_error)
			device->discipline->handle_hpf_error(device, irb);
		/*
		 * If we करोn't want complex ERP क्रम this request, then just
		 * reset this and retry it in the fastpath
		 */
		अगर (!test_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags) &&
		    cqr->retries > 0) अणु
			अगर (cqr->lpm == dasd_path_get_opm(device))
				DBF_DEV_EVENT(DBF_DEBUG, device,
					      "default ERP in fastpath "
					      "(%i retries left)",
					      cqr->retries);
			अगर (!test_bit(DASD_CQR_VERIFY_PATH, &cqr->flags))
				cqr->lpm = dasd_path_get_opm(device);
			cqr->status = DASD_CQR_QUEUED;
			next = cqr;
		पूर्ण अन्यथा
			cqr->status = DASD_CQR_ERROR;
	पूर्ण
	अगर (next && (next->status == DASD_CQR_QUEUED) &&
	    (!device->stopped)) अणु
		अगर (device->discipline->start_IO(next) == 0)
			expires = next->expires;
	पूर्ण
	अगर (expires != 0)
		dasd_device_set_समयr(device, expires);
	अन्यथा
		dasd_device_clear_समयr(device);
	dasd_schedule_device_bh(device);
पूर्ण
EXPORT_SYMBOL(dasd_पूर्णांक_handler);

क्रमागत uc_toकरो dasd_generic_uc_handler(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	काष्ठा dasd_device *device;

	device = dasd_device_from_cdev_locked(cdev);

	अगर (IS_ERR(device))
		जाओ out;
	अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags) ||
	   device->state != device->target ||
	   !device->discipline->check_क्रम_device_change)अणु
		dasd_put_device(device);
		जाओ out;
	पूर्ण
	अगर (device->discipline->dump_sense_dbf)
		device->discipline->dump_sense_dbf(device, irb, "uc");
	device->discipline->check_क्रम_device_change(device, शून्य, irb);
	dasd_put_device(device);
out:
	वापस UC_TODO_RETRY;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_uc_handler);

/*
 * If we have an error on a dasd_block layer request then we cancel
 * and वापस all further requests from the same dasd_block as well.
 */
अटल व्योम __dasd_device_recovery(काष्ठा dasd_device *device,
				   काष्ठा dasd_ccw_req *ref_cqr)
अणु
	काष्ठा list_head *l, *n;
	काष्ठा dasd_ccw_req *cqr;

	/*
	 * only requeue request that came from the dasd_block layer
	 */
	अगर (!ref_cqr->block)
		वापस;

	list_क्रम_each_safe(l, n, &device->ccw_queue) अणु
		cqr = list_entry(l, काष्ठा dasd_ccw_req, devlist);
		अगर (cqr->status == DASD_CQR_QUEUED &&
		    ref_cqr->block == cqr->block) अणु
			cqr->status = DASD_CQR_CLEARED;
		पूर्ण
	पूर्ण
पूर्ण;

/*
 * Remove those ccw requests from the queue that need to be वापसed
 * to the upper layer.
 */
अटल व्योम __dasd_device_process_ccw_queue(काष्ठा dasd_device *device,
					    काष्ठा list_head *final_queue)
अणु
	काष्ठा list_head *l, *n;
	काष्ठा dasd_ccw_req *cqr;

	/* Process request with final status. */
	list_क्रम_each_safe(l, n, &device->ccw_queue) अणु
		cqr = list_entry(l, काष्ठा dasd_ccw_req, devlist);

		/* Skip any non-final request. */
		अगर (cqr->status == DASD_CQR_QUEUED ||
		    cqr->status == DASD_CQR_IN_IO ||
		    cqr->status == DASD_CQR_CLEAR_PENDING)
			जारी;
		अगर (cqr->status == DASD_CQR_ERROR) अणु
			__dasd_device_recovery(device, cqr);
		पूर्ण
		/* Rechain finished requests to final queue */
		list_move_tail(&cqr->devlist, final_queue);
	पूर्ण
पूर्ण

अटल व्योम __dasd_process_cqr(काष्ठा dasd_device *device,
			       काष्ठा dasd_ccw_req *cqr)
अणु
	अक्षर errorstring[ERRORLENGTH];

	चयन (cqr->status) अणु
	हाल DASD_CQR_SUCCESS:
		cqr->status = DASD_CQR_DONE;
		अवरोध;
	हाल DASD_CQR_ERROR:
		cqr->status = DASD_CQR_NEED_ERP;
		अवरोध;
	हाल DASD_CQR_CLEARED:
		cqr->status = DASD_CQR_TERMINATED;
		अवरोध;
	शेष:
		/* पूर्णांकernal error 12 - wrong cqr status*/
		snम_लिखो(errorstring, ERRORLENGTH, "12 %p %x02", cqr, cqr->status);
		dev_err(&device->cdev->dev,
			"An error occurred in the DASD device driver, "
			"reason=%s\n", errorstring);
		BUG();
	पूर्ण
	अगर (cqr->callback)
		cqr->callback(cqr, cqr->callback_data);
पूर्ण

/*
 * the cqrs from the final queue are वापसed to the upper layer
 * by setting a dasd_block state and calling the callback function
 */
अटल व्योम __dasd_device_process_final_queue(काष्ठा dasd_device *device,
					      काष्ठा list_head *final_queue)
अणु
	काष्ठा list_head *l, *n;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा dasd_block *block;

	list_क्रम_each_safe(l, n, final_queue) अणु
		cqr = list_entry(l, काष्ठा dasd_ccw_req, devlist);
		list_del_init(&cqr->devlist);
		block = cqr->block;
		अगर (!block) अणु
			__dasd_process_cqr(device, cqr);
		पूर्ण अन्यथा अणु
			spin_lock_bh(&block->queue_lock);
			__dasd_process_cqr(device, cqr);
			spin_unlock_bh(&block->queue_lock);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Take a look at the first request on the ccw queue and check
 * अगर it reached its expire समय. If so, terminate the IO.
 */
अटल व्योम __dasd_device_check_expire(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;

	अगर (list_empty(&device->ccw_queue))
		वापस;
	cqr = list_entry(device->ccw_queue.next, काष्ठा dasd_ccw_req, devlist);
	अगर ((cqr->status == DASD_CQR_IN_IO && cqr->expires != 0) &&
	    (समय_after_eq(jअगरfies, cqr->expires + cqr->startसमय))) अणु
		अगर (test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) अणु
			/*
			 * IO in safe offline processing should not
			 * run out of retries
			 */
			cqr->retries++;
		पूर्ण
		अगर (device->discipline->term_IO(cqr) != 0) अणु
			/* Hmpf, try again in 5 sec */
			dev_err(&device->cdev->dev,
				"cqr %p timed out (%lus) but cannot be "
				"ended, retrying in 5 s\n",
				cqr, (cqr->expires/HZ));
			cqr->expires += 5*HZ;
			dasd_device_set_समयr(device, 5*HZ);
		पूर्ण अन्यथा अणु
			dev_err(&device->cdev->dev,
				"cqr %p timed out (%lus), %i retries "
				"remaining\n", cqr, (cqr->expires/HZ),
				cqr->retries);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * वापस 1 when device is not eligible क्रम IO
 */
अटल पूर्णांक __dasd_device_is_unusable(काष्ठा dasd_device *device,
				     काष्ठा dasd_ccw_req *cqr)
अणु
	पूर्णांक mask = ~(DASD_STOPPED_DC_WAIT | DASD_STOPPED_NOSPC);

	अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags) &&
	    !test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) अणु
		/*
		 * dasd is being set offline
		 * but it is no safe offline where we have to allow I/O
		 */
		वापस 1;
	पूर्ण
	अगर (device->stopped) अणु
		अगर (device->stopped & mask) अणु
			/* stopped and CQR will not change that. */
			वापस 1;
		पूर्ण
		अगर (!test_bit(DASD_CQR_VERIFY_PATH, &cqr->flags)) अणु
			/* CQR is not able to change device to
			 * operational. */
			वापस 1;
		पूर्ण
		/* CQR required to get device operational. */
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Take a look at the first request on the ccw queue and check
 * अगर it needs to be started.
 */
अटल व्योम __dasd_device_start_head(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;

	अगर (list_empty(&device->ccw_queue))
		वापस;
	cqr = list_entry(device->ccw_queue.next, काष्ठा dasd_ccw_req, devlist);
	अगर (cqr->status != DASD_CQR_QUEUED)
		वापस;
	/* अगर device is not usable वापस request to upper layer */
	अगर (__dasd_device_is_unusable(device, cqr)) अणु
		cqr->पूर्णांकrc = -EAGAIN;
		cqr->status = DASD_CQR_CLEARED;
		dasd_schedule_device_bh(device);
		वापस;
	पूर्ण

	rc = device->discipline->start_IO(cqr);
	अगर (rc == 0)
		dasd_device_set_समयr(device, cqr->expires);
	अन्यथा अगर (rc == -EACCES) अणु
		dasd_schedule_device_bh(device);
	पूर्ण अन्यथा
		/* Hmpf, try again in 1/2 sec */
		dasd_device_set_समयr(device, 50);
पूर्ण

अटल व्योम __dasd_device_check_path_events(काष्ठा dasd_device *device)
अणु
	__u8 tbvpm, fcsecpm;
	पूर्णांक rc;

	tbvpm = dasd_path_get_tbvpm(device);
	fcsecpm = dasd_path_get_fcsecpm(device);

	अगर (!tbvpm && !fcsecpm)
		वापस;

	अगर (device->stopped & ~(DASD_STOPPED_DC_WAIT))
		वापस;
	rc = device->discipline->pe_handler(device, tbvpm, fcsecpm);
	अगर (rc) अणु
		dasd_device_set_समयr(device, 50);
	पूर्ण अन्यथा अणु
		dasd_path_clear_all_verअगरy(device);
		dasd_path_clear_all_fcsec(device);
	पूर्ण
पूर्ण;

/*
 * Go through all request on the dasd_device request queue,
 * terminate them on the cdev अगर necessary, and वापस them to the
 * submitting layer via callback.
 * Note:
 * Make sure that all 'submitting layers' still exist when
 * this function is called!. In other words, when 'device' is a base
 * device then all block layer requests must have been हटाओd beक्रमe
 * via dasd_flush_block_queue.
 */
पूर्णांक dasd_flush_device_queue(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr, *n;
	पूर्णांक rc;
	काष्ठा list_head flush_queue;

	INIT_LIST_HEAD(&flush_queue);
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = 0;
	list_क्रम_each_entry_safe(cqr, n, &device->ccw_queue, devlist) अणु
		/* Check status and move request to flush_queue */
		चयन (cqr->status) अणु
		हाल DASD_CQR_IN_IO:
			rc = device->discipline->term_IO(cqr);
			अगर (rc) अणु
				/* unable to terminate requeust */
				dev_err(&device->cdev->dev,
					"Flushing the DASD request queue "
					"failed for request %p\n", cqr);
				/* stop flush processing */
				जाओ finished;
			पूर्ण
			अवरोध;
		हाल DASD_CQR_QUEUED:
			cqr->stopclk = get_tod_घड़ी();
			cqr->status = DASD_CQR_CLEARED;
			अवरोध;
		शेष: /* no need to modअगरy the others */
			अवरोध;
		पूर्ण
		list_move_tail(&cqr->devlist, &flush_queue);
	पूर्ण
finished:
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	/*
	 * After this poपूर्णांक all requests must be in state CLEAR_PENDING,
	 * CLEARED, SUCCESS or ERROR. Now रुको क्रम CLEAR_PENDING to become
	 * one of the others.
	 */
	list_क्रम_each_entry_safe(cqr, n, &flush_queue, devlist)
		रुको_event(dasd_flush_wq,
			   (cqr->status != DASD_CQR_CLEAR_PENDING));
	/*
	 * Now set each request back to TERMINATED, DONE or NEED_ERP
	 * and call the callback function of flushed requests
	 */
	__dasd_device_process_final_queue(device, &flush_queue);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_flush_device_queue);

/*
 * Acquire the device lock and process queues क्रम the device.
 */
अटल व्योम dasd_device_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा dasd_device *device = (काष्ठा dasd_device *) data;
	काष्ठा list_head final_queue;

	atomic_set (&device->tasklet_scheduled, 0);
	INIT_LIST_HEAD(&final_queue);
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Check expire समय of first request on the ccw queue. */
	__dasd_device_check_expire(device);
	/* find final requests on ccw queue */
	__dasd_device_process_ccw_queue(device, &final_queue);
	__dasd_device_check_path_events(device);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	/* Now call the callback function of requests with final status */
	__dasd_device_process_final_queue(device, &final_queue);
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Now check अगर the head of the ccw queue needs to be started. */
	__dasd_device_start_head(device);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	अगर (रुकोqueue_active(&shutकरोwn_रुकोq))
		wake_up(&shutकरोwn_रुकोq);
	dasd_put_device(device);
पूर्ण

/*
 * Schedules a call to dasd_tasklet over the device tasklet.
 */
व्योम dasd_schedule_device_bh(काष्ठा dasd_device *device)
अणु
	/* Protect against rescheduling. */
	अगर (atomic_cmpxchg (&device->tasklet_scheduled, 0, 1) != 0)
		वापस;
	dasd_get_device(device);
	tasklet_hi_schedule(&device->tasklet);
पूर्ण
EXPORT_SYMBOL(dasd_schedule_device_bh);

व्योम dasd_device_set_stop_bits(काष्ठा dasd_device *device, पूर्णांक bits)
अणु
	device->stopped |= bits;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_device_set_stop_bits);

व्योम dasd_device_हटाओ_stop_bits(काष्ठा dasd_device *device, पूर्णांक bits)
अणु
	device->stopped &= ~bits;
	अगर (!device->stopped)
		wake_up(&generic_रुकोq);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_device_हटाओ_stop_bits);

/*
 * Queue a request to the head of the device ccw_queue.
 * Start the I/O अगर possible.
 */
व्योम dasd_add_request_head(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;

	device = cqr->startdev;
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	cqr->status = DASD_CQR_QUEUED;
	list_add(&cqr->devlist, &device->ccw_queue);
	/* let the bh start the request to keep them in order */
	dasd_schedule_device_bh(device);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
पूर्ण
EXPORT_SYMBOL(dasd_add_request_head);

/*
 * Queue a request to the tail of the device ccw_queue.
 * Start the I/O अगर possible.
 */
व्योम dasd_add_request_tail(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;

	device = cqr->startdev;
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	cqr->status = DASD_CQR_QUEUED;
	list_add_tail(&cqr->devlist, &device->ccw_queue);
	/* let the bh start the request to keep them in order */
	dasd_schedule_device_bh(device);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
पूर्ण
EXPORT_SYMBOL(dasd_add_request_tail);

/*
 * Wakeup helper क्रम the 'sleep_on' functions.
 */
व्योम dasd_wakeup_cb(काष्ठा dasd_ccw_req *cqr, व्योम *data)
अणु
	spin_lock_irq(get_ccwdev_lock(cqr->startdev->cdev));
	cqr->callback_data = DASD_SLEEPON_END_TAG;
	spin_unlock_irq(get_ccwdev_lock(cqr->startdev->cdev));
	wake_up(&generic_रुकोq);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_wakeup_cb);

अटल अंतरभूत पूर्णांक _रुको_क्रम_wakeup(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक rc;

	device = cqr->startdev;
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = (cqr->callback_data == DASD_SLEEPON_END_TAG);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	वापस rc;
पूर्ण

/*
 * checks अगर error recovery is necessary, वापसs 1 अगर yes, 0 otherwise.
 */
अटल पूर्णांक __dasd_sleep_on_erp(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;
	dasd_erp_fn_t erp_fn;

	अगर (cqr->status == DASD_CQR_FILLED)
		वापस 0;
	device = cqr->startdev;
	अगर (test_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags)) अणु
		अगर (cqr->status == DASD_CQR_TERMINATED) अणु
			device->discipline->handle_terminated_request(cqr);
			वापस 1;
		पूर्ण
		अगर (cqr->status == DASD_CQR_NEED_ERP) अणु
			erp_fn = device->discipline->erp_action(cqr);
			erp_fn(cqr);
			वापस 1;
		पूर्ण
		अगर (cqr->status == DASD_CQR_FAILED)
			dasd_log_sense(cqr, &cqr->irb);
		अगर (cqr->refers) अणु
			__dasd_process_erp(device, cqr);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __dasd_sleep_on_loop_condition(काष्ठा dasd_ccw_req *cqr)
अणु
	अगर (test_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags)) अणु
		अगर (cqr->refers) /* erp is not करोne yet */
			वापस 1;
		वापस ((cqr->status != DASD_CQR_DONE) &&
			(cqr->status != DASD_CQR_FAILED));
	पूर्ण अन्यथा
		वापस (cqr->status == DASD_CQR_FILLED);
पूर्ण

अटल पूर्णांक _dasd_sleep_on(काष्ठा dasd_ccw_req *मुख्यcqr, पूर्णांक पूर्णांकerruptible)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक rc;
	काष्ठा list_head ccw_queue;
	काष्ठा dasd_ccw_req *cqr;

	INIT_LIST_HEAD(&ccw_queue);
	मुख्यcqr->status = DASD_CQR_FILLED;
	device = मुख्यcqr->startdev;
	list_add(&मुख्यcqr->blocklist, &ccw_queue);
	क्रम (cqr = मुख्यcqr;  __dasd_sleep_on_loop_condition(cqr);
	     cqr = list_first_entry(&ccw_queue,
				    काष्ठा dasd_ccw_req, blocklist)) अणु

		अगर (__dasd_sleep_on_erp(cqr))
			जारी;
		अगर (cqr->status != DASD_CQR_FILLED) /* could be failed */
			जारी;
		अगर (test_bit(DASD_FLAG_LOCK_STOLEN, &device->flags) &&
		    !test_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags)) अणु
			cqr->status = DASD_CQR_FAILED;
			cqr->पूर्णांकrc = -EPERM;
			जारी;
		पूर्ण
		/* Non-temporary stop condition will trigger fail fast */
		अगर (device->stopped & ~DASD_STOPPED_PENDING &&
		    test_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags) &&
		    (!dasd_eer_enabled(device))) अणु
			cqr->status = DASD_CQR_FAILED;
			cqr->पूर्णांकrc = -ENOLINK;
			जारी;
		पूर्ण
		/*
		 * Don't try to start requests अगर device is in
		 * offline processing, it might रुको क्रमever
		 */
		अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags)) अणु
			cqr->status = DASD_CQR_FAILED;
			cqr->पूर्णांकrc = -ENODEV;
			जारी;
		पूर्ण
		/*
		 * Don't try to start requests अगर device is stopped
		 * except path verअगरication requests
		 */
		अगर (!test_bit(DASD_CQR_VERIFY_PATH, &cqr->flags)) अणु
			अगर (पूर्णांकerruptible) अणु
				rc = रुको_event_पूर्णांकerruptible(
					generic_रुकोq, !(device->stopped));
				अगर (rc == -ERESTARTSYS) अणु
					cqr->status = DASD_CQR_FAILED;
					मुख्यcqr->पूर्णांकrc = rc;
					जारी;
				पूर्ण
			पूर्ण अन्यथा
				रुको_event(generic_रुकोq, !(device->stopped));
		पूर्ण
		अगर (!cqr->callback)
			cqr->callback = dasd_wakeup_cb;

		cqr->callback_data = DASD_SLEEPON_START_TAG;
		dasd_add_request_tail(cqr);
		अगर (पूर्णांकerruptible) अणु
			rc = रुको_event_पूर्णांकerruptible(
				generic_रुकोq, _रुको_क्रम_wakeup(cqr));
			अगर (rc == -ERESTARTSYS) अणु
				dasd_cancel_req(cqr);
				/* रुको (non-पूर्णांकerruptible) क्रम final status */
				रुको_event(generic_रुकोq,
					   _रुको_क्रम_wakeup(cqr));
				cqr->status = DASD_CQR_FAILED;
				मुख्यcqr->पूर्णांकrc = rc;
				जारी;
			पूर्ण
		पूर्ण अन्यथा
			रुको_event(generic_रुकोq, _रुको_क्रम_wakeup(cqr));
	पूर्ण

	मुख्यcqr->endclk = get_tod_घड़ी();
	अगर ((मुख्यcqr->status != DASD_CQR_DONE) &&
	    (मुख्यcqr->पूर्णांकrc != -ERESTARTSYS))
		dasd_log_sense(मुख्यcqr, &मुख्यcqr->irb);
	अगर (मुख्यcqr->status == DASD_CQR_DONE)
		rc = 0;
	अन्यथा अगर (मुख्यcqr->पूर्णांकrc)
		rc = मुख्यcqr->पूर्णांकrc;
	अन्यथा
		rc = -EIO;
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक _रुको_क्रम_wakeup_queue(काष्ठा list_head *ccw_queue)
अणु
	काष्ठा dasd_ccw_req *cqr;

	list_क्रम_each_entry(cqr, ccw_queue, blocklist) अणु
		अगर (cqr->callback_data != DASD_SLEEPON_END_TAG)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक _dasd_sleep_on_queue(काष्ठा list_head *ccw_queue, पूर्णांक पूर्णांकerruptible)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_ccw_req *cqr, *n;
	u8 *sense = शून्य;
	पूर्णांक rc;

retry:
	list_क्रम_each_entry_safe(cqr, n, ccw_queue, blocklist) अणु
		device = cqr->startdev;
		अगर (cqr->status != DASD_CQR_FILLED) /*could be failed*/
			जारी;

		अगर (test_bit(DASD_FLAG_LOCK_STOLEN, &device->flags) &&
		    !test_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags)) अणु
			cqr->status = DASD_CQR_FAILED;
			cqr->पूर्णांकrc = -EPERM;
			जारी;
		पूर्ण
		/*Non-temporary stop condition will trigger fail fast*/
		अगर (device->stopped & ~DASD_STOPPED_PENDING &&
		    test_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags) &&
		    !dasd_eer_enabled(device)) अणु
			cqr->status = DASD_CQR_FAILED;
			cqr->पूर्णांकrc = -EAGAIN;
			जारी;
		पूर्ण

		/*Don't try to start requests अगर device is stopped*/
		अगर (पूर्णांकerruptible) अणु
			rc = रुको_event_पूर्णांकerruptible(
				generic_रुकोq, !device->stopped);
			अगर (rc == -ERESTARTSYS) अणु
				cqr->status = DASD_CQR_FAILED;
				cqr->पूर्णांकrc = rc;
				जारी;
			पूर्ण
		पूर्ण अन्यथा
			रुको_event(generic_रुकोq, !(device->stopped));

		अगर (!cqr->callback)
			cqr->callback = dasd_wakeup_cb;
		cqr->callback_data = DASD_SLEEPON_START_TAG;
		dasd_add_request_tail(cqr);
	पूर्ण

	रुको_event(generic_रुकोq, _रुको_क्रम_wakeup_queue(ccw_queue));

	rc = 0;
	list_क्रम_each_entry_safe(cqr, n, ccw_queue, blocklist) अणु
		/*
		 * In some हालs the 'File Protected' or 'Incorrect Length'
		 * error might be expected and error recovery would be
		 * unnecessary in these हालs.	Check अगर the according suppress
		 * bit is set.
		 */
		sense = dasd_get_sense(&cqr->irb);
		अगर (sense && sense[1] & SNS1_खाता_PROTECTED &&
		    test_bit(DASD_CQR_SUPPRESS_FP, &cqr->flags))
			जारी;
		अगर (scsw_cstat(&cqr->irb.scsw) == 0x40 &&
		    test_bit(DASD_CQR_SUPPRESS_IL, &cqr->flags))
			जारी;

		/*
		 * क्रम alias devices simplअगरy error recovery and
		 * वापस to upper layer
		 * करो not skip ERP requests
		 */
		अगर (cqr->startdev != cqr->basedev && !cqr->refers &&
		    (cqr->status == DASD_CQR_TERMINATED ||
		     cqr->status == DASD_CQR_NEED_ERP))
			वापस -EAGAIN;

		/* normal recovery क्रम basedev IO */
		अगर (__dasd_sleep_on_erp(cqr))
			/* handle erp first */
			जाओ retry;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Queue a request to the tail of the device ccw_queue and रुको क्रम
 * it's completion.
 */
पूर्णांक dasd_sleep_on(काष्ठा dasd_ccw_req *cqr)
अणु
	वापस _dasd_sleep_on(cqr, 0);
पूर्ण
EXPORT_SYMBOL(dasd_sleep_on);

/*
 * Start requests from a ccw_queue and रुको क्रम their completion.
 */
पूर्णांक dasd_sleep_on_queue(काष्ठा list_head *ccw_queue)
अणु
	वापस _dasd_sleep_on_queue(ccw_queue, 0);
पूर्ण
EXPORT_SYMBOL(dasd_sleep_on_queue);

/*
 * Start requests from a ccw_queue and रुको पूर्णांकerruptible क्रम their completion.
 */
पूर्णांक dasd_sleep_on_queue_पूर्णांकerruptible(काष्ठा list_head *ccw_queue)
अणु
	वापस _dasd_sleep_on_queue(ccw_queue, 1);
पूर्ण
EXPORT_SYMBOL(dasd_sleep_on_queue_पूर्णांकerruptible);

/*
 * Queue a request to the tail of the device ccw_queue and रुको
 * पूर्णांकerruptible क्रम it's completion.
 */
पूर्णांक dasd_sleep_on_पूर्णांकerruptible(काष्ठा dasd_ccw_req *cqr)
अणु
	वापस _dasd_sleep_on(cqr, 1);
पूर्ण
EXPORT_SYMBOL(dasd_sleep_on_पूर्णांकerruptible);

/*
 * Whoa nelly now it माला_लो really hairy. For some functions (e.g. steal lock
 * क्रम eckd devices) the currently running request has to be terminated
 * and be put back to status queued, beक्रमe the special request is added
 * to the head of the queue. Then the special request is रुकोed on normally.
 */
अटल अंतरभूत पूर्णांक _dasd_term_running_cqr(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;

	अगर (list_empty(&device->ccw_queue))
		वापस 0;
	cqr = list_entry(device->ccw_queue.next, काष्ठा dasd_ccw_req, devlist);
	rc = device->discipline->term_IO(cqr);
	अगर (!rc)
		/*
		 * CQR terminated because a more important request is pending.
		 * Unकरो decreasing of retry counter because this is
		 * not an error हाल.
		 */
		cqr->retries++;
	वापस rc;
पूर्ण

पूर्णांक dasd_sleep_on_immediatly(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक rc;

	device = cqr->startdev;
	अगर (test_bit(DASD_FLAG_LOCK_STOLEN, &device->flags) &&
	    !test_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags)) अणु
		cqr->status = DASD_CQR_FAILED;
		cqr->पूर्णांकrc = -EPERM;
		वापस -EIO;
	पूर्ण
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = _dasd_term_running_cqr(device);
	अगर (rc) अणु
		spin_unlock_irq(get_ccwdev_lock(device->cdev));
		वापस rc;
	पूर्ण
	cqr->callback = dasd_wakeup_cb;
	cqr->callback_data = DASD_SLEEPON_START_TAG;
	cqr->status = DASD_CQR_QUEUED;
	/*
	 * add new request as second
	 * first the terminated cqr needs to be finished
	 */
	list_add(&cqr->devlist, device->ccw_queue.next);

	/* let the bh start the request to keep them in order */
	dasd_schedule_device_bh(device);

	spin_unlock_irq(get_ccwdev_lock(device->cdev));

	रुको_event(generic_रुकोq, _रुको_क्रम_wakeup(cqr));

	अगर (cqr->status == DASD_CQR_DONE)
		rc = 0;
	अन्यथा अगर (cqr->पूर्णांकrc)
		rc = cqr->पूर्णांकrc;
	अन्यथा
		rc = -EIO;

	/* kick tasklets */
	dasd_schedule_device_bh(device);
	अगर (device->block)
		dasd_schedule_block_bh(device->block);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(dasd_sleep_on_immediatly);

/*
 * Cancels a request that was started with dasd_sleep_on_req.
 * This is useful to समयout requests. The request will be
 * terminated अगर it is currently in i/o.
 * Returns 0 अगर request termination was successful
 *	   negative error code अगर termination failed
 * Cancellation of a request is an asynchronous operation! The calling
 * function has to रुको until the request is properly वापसed via callback.
 */
अटल पूर्णांक __dasd_cancel_req(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device = cqr->startdev;
	पूर्णांक rc = 0;

	चयन (cqr->status) अणु
	हाल DASD_CQR_QUEUED:
		/* request was not started - just set to cleared */
		cqr->status = DASD_CQR_CLEARED;
		अवरोध;
	हाल DASD_CQR_IN_IO:
		/* request in IO - terminate IO and release again */
		rc = device->discipline->term_IO(cqr);
		अगर (rc) अणु
			dev_err(&device->cdev->dev,
				"Cancelling request %p failed with rc=%d\n",
				cqr, rc);
		पूर्ण अन्यथा अणु
			cqr->stopclk = get_tod_घड़ी();
		पूर्ण
		अवरोध;
	शेष: /* alपढ़ोy finished or clear pending - करो nothing */
		अवरोध;
	पूर्ण
	dasd_schedule_device_bh(device);
	वापस rc;
पूर्ण

पूर्णांक dasd_cancel_req(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_device *device = cqr->startdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	rc = __dasd_cancel_req(cqr);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	वापस rc;
पूर्ण

/*
 * SECTION: Operations of the dasd_block layer.
 */

/*
 * Timeout function क्रम dasd_block. This is used when the block layer
 * is रुकोing क्रम something that may not come reliably, (e.g. a state
 * change पूर्णांकerrupt)
 */
अटल व्योम dasd_block_समयout(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_block *block;

	block = from_समयr(block, t, समयr);
	spin_lock_irqsave(get_ccwdev_lock(block->base->cdev), flags);
	/* re-activate request queue */
	dasd_device_हटाओ_stop_bits(block->base, DASD_STOPPED_PENDING);
	spin_unlock_irqrestore(get_ccwdev_lock(block->base->cdev), flags);
	dasd_schedule_block_bh(block);
	blk_mq_run_hw_queues(block->request_queue, true);
पूर्ण

/*
 * Setup समयout क्रम a dasd_block in jअगरfies.
 */
व्योम dasd_block_set_समयr(काष्ठा dasd_block *block, पूर्णांक expires)
अणु
	अगर (expires == 0)
		del_समयr(&block->समयr);
	अन्यथा
		mod_समयr(&block->समयr, jअगरfies + expires);
पूर्ण
EXPORT_SYMBOL(dasd_block_set_समयr);

/*
 * Clear समयout क्रम a dasd_block.
 */
व्योम dasd_block_clear_समयr(काष्ठा dasd_block *block)
अणु
	del_समयr(&block->समयr);
पूर्ण
EXPORT_SYMBOL(dasd_block_clear_समयr);

/*
 * Process finished error recovery ccw.
 */
अटल व्योम __dasd_process_erp(काष्ठा dasd_device *device,
			       काष्ठा dasd_ccw_req *cqr)
अणु
	dasd_erp_fn_t erp_fn;

	अगर (cqr->status == DASD_CQR_DONE)
		DBF_DEV_EVENT(DBF_NOTICE, device, "%s", "ERP successful");
	अन्यथा
		dev_err(&device->cdev->dev, "ERP failed for the DASD\n");
	erp_fn = device->discipline->erp_postaction(cqr);
	erp_fn(cqr);
पूर्ण

अटल व्योम __dasd_cleanup_cqr(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा request *req;
	blk_status_t error = BLK_STS_OK;
	अचिन्हित पूर्णांक proc_bytes;
	पूर्णांक status;

	req = (काष्ठा request *) cqr->callback_data;
	dasd_profile_end(cqr->block, cqr, req);

	proc_bytes = cqr->proc_bytes;
	status = cqr->block->base->discipline->मुक्त_cp(cqr, req);
	अगर (status < 0)
		error = त्रुटि_सं_to_blk_status(status);
	अन्यथा अगर (status == 0) अणु
		चयन (cqr->पूर्णांकrc) अणु
		हाल -EPERM:
			error = BLK_STS_NEXUS;
			अवरोध;
		हाल -ENOLINK:
			error = BLK_STS_TRANSPORT;
			अवरोध;
		हाल -ETIMEDOUT:
			error = BLK_STS_TIMEOUT;
			अवरोध;
		शेष:
			error = BLK_STS_IOERR;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * We need to take care क्रम ETIMEDOUT errors here since the
	 * complete callback करोes not get called in this हाल.
	 * Take care of all errors here and aव्योम additional code to
	 * transfer the error value to the complete callback.
	 */
	अगर (error) अणु
		blk_mq_end_request(req, error);
		blk_mq_run_hw_queues(req->q, true);
	पूर्ण अन्यथा अणु
		/*
		 * Partial completed requests can happen with ESE devices.
		 * During पढ़ो we might have gotten a NRF error and have to
		 * complete a request partially.
		 */
		अगर (proc_bytes) अणु
			blk_update_request(req, BLK_STS_OK,
					   blk_rq_bytes(req) - proc_bytes);
			blk_mq_requeue_request(req, true);
		पूर्ण अन्यथा अगर (likely(!blk_should_fake_समयout(req->q))) अणु
			blk_mq_complete_request(req);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Process ccw request queue.
 */
अटल व्योम __dasd_process_block_ccw_queue(काष्ठा dasd_block *block,
					   काष्ठा list_head *final_queue)
अणु
	काष्ठा list_head *l, *n;
	काष्ठा dasd_ccw_req *cqr;
	dasd_erp_fn_t erp_fn;
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_device *base = block->base;

restart:
	/* Process request with final status. */
	list_क्रम_each_safe(l, n, &block->ccw_queue) अणु
		cqr = list_entry(l, काष्ठा dasd_ccw_req, blocklist);
		अगर (cqr->status != DASD_CQR_DONE &&
		    cqr->status != DASD_CQR_FAILED &&
		    cqr->status != DASD_CQR_NEED_ERP &&
		    cqr->status != DASD_CQR_TERMINATED)
			जारी;

		अगर (cqr->status == DASD_CQR_TERMINATED) अणु
			base->discipline->handle_terminated_request(cqr);
			जाओ restart;
		पूर्ण

		/*  Process requests that may be recovered */
		अगर (cqr->status == DASD_CQR_NEED_ERP) अणु
			erp_fn = base->discipline->erp_action(cqr);
			अगर (IS_ERR(erp_fn(cqr)))
				जारी;
			जाओ restart;
		पूर्ण

		/* log sense क्रम fatal error */
		अगर (cqr->status == DASD_CQR_FAILED) अणु
			dasd_log_sense(cqr, &cqr->irb);
		पूर्ण

		/* First of all call extended error reporting. */
		अगर (dasd_eer_enabled(base) &&
		    cqr->status == DASD_CQR_FAILED) अणु
			dasd_eer_ग_लिखो(base, cqr, DASD_EER_FATALERROR);

			/* restart request  */
			cqr->status = DASD_CQR_FILLED;
			cqr->retries = 255;
			spin_lock_irqsave(get_ccwdev_lock(base->cdev), flags);
			dasd_device_set_stop_bits(base, DASD_STOPPED_QUIESCE);
			spin_unlock_irqrestore(get_ccwdev_lock(base->cdev),
					       flags);
			जाओ restart;
		पूर्ण

		/* Process finished ERP request. */
		अगर (cqr->refers) अणु
			__dasd_process_erp(base, cqr);
			जाओ restart;
		पूर्ण

		/* Rechain finished requests to final queue */
		cqr->endclk = get_tod_घड़ी();
		list_move_tail(&cqr->blocklist, final_queue);
	पूर्ण
पूर्ण

अटल व्योम dasd_वापस_cqr_cb(काष्ठा dasd_ccw_req *cqr, व्योम *data)
अणु
	dasd_schedule_block_bh(cqr->block);
पूर्ण

अटल व्योम __dasd_block_start_head(काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_ccw_req *cqr;

	अगर (list_empty(&block->ccw_queue))
		वापस;
	/* We allways begin with the first requests on the queue, as some
	 * of previously started requests have to be enqueued on a
	 * dasd_device again क्रम error recovery.
	 */
	list_क्रम_each_entry(cqr, &block->ccw_queue, blocklist) अणु
		अगर (cqr->status != DASD_CQR_FILLED)
			जारी;
		अगर (test_bit(DASD_FLAG_LOCK_STOLEN, &block->base->flags) &&
		    !test_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags)) अणु
			cqr->status = DASD_CQR_FAILED;
			cqr->पूर्णांकrc = -EPERM;
			dasd_schedule_block_bh(block);
			जारी;
		पूर्ण
		/* Non-temporary stop condition will trigger fail fast */
		अगर (block->base->stopped & ~DASD_STOPPED_PENDING &&
		    test_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags) &&
		    (!dasd_eer_enabled(block->base))) अणु
			cqr->status = DASD_CQR_FAILED;
			cqr->पूर्णांकrc = -ENOLINK;
			dasd_schedule_block_bh(block);
			जारी;
		पूर्ण
		/* Don't try to start requests अगर device is stopped */
		अगर (block->base->stopped)
			वापस;

		/* just a fail safe check, should not happen */
		अगर (!cqr->startdev)
			cqr->startdev = block->base;

		/* make sure that the requests we submit find their way back */
		cqr->callback = dasd_वापस_cqr_cb;

		dasd_add_request_tail(cqr);
	पूर्ण
पूर्ण

/*
 * Central dasd_block layer routine. Takes requests from the generic
 * block layer request queue, creates ccw requests, enqueues them on
 * a dasd_device and processes ccw requests that have been वापसed.
 */
अटल व्योम dasd_block_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा dasd_block *block = (काष्ठा dasd_block *) data;
	काष्ठा list_head final_queue;
	काष्ठा list_head *l, *n;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा dasd_queue *dq;

	atomic_set(&block->tasklet_scheduled, 0);
	INIT_LIST_HEAD(&final_queue);
	spin_lock_irq(&block->queue_lock);
	/* Finish off requests on ccw queue */
	__dasd_process_block_ccw_queue(block, &final_queue);
	spin_unlock_irq(&block->queue_lock);

	/* Now call the callback function of requests with final status */
	list_क्रम_each_safe(l, n, &final_queue) अणु
		cqr = list_entry(l, काष्ठा dasd_ccw_req, blocklist);
		dq = cqr->dq;
		spin_lock_irq(&dq->lock);
		list_del_init(&cqr->blocklist);
		__dasd_cleanup_cqr(cqr);
		spin_unlock_irq(&dq->lock);
	पूर्ण

	spin_lock_irq(&block->queue_lock);
	/* Now check अगर the head of the ccw queue needs to be started. */
	__dasd_block_start_head(block);
	spin_unlock_irq(&block->queue_lock);

	अगर (रुकोqueue_active(&shutकरोwn_रुकोq))
		wake_up(&shutकरोwn_रुकोq);
	dasd_put_device(block->base);
पूर्ण

अटल व्योम _dasd_wake_block_flush_cb(काष्ठा dasd_ccw_req *cqr, व्योम *data)
अणु
	wake_up(&dasd_flush_wq);
पूर्ण

/*
 * Requeue a request back to the block request queue
 * only works क्रम block requests
 */
अटल पूर्णांक _dasd_requeue_request(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा dasd_block *block = cqr->block;
	काष्ठा request *req;

	अगर (!block)
		वापस -EINVAL;
	/*
	 * If the request is an ERP request there is nothing to requeue.
	 * This will be करोne with the reमुख्यing original request.
	 */
	अगर (cqr->refers)
		वापस 0;
	spin_lock_irq(&cqr->dq->lock);
	req = (काष्ठा request *) cqr->callback_data;
	blk_mq_requeue_request(req, false);
	spin_unlock_irq(&cqr->dq->lock);

	वापस 0;
पूर्ण

/*
 * Go through all request on the dasd_block request queue, cancel them
 * on the respective dasd_device, and वापस them to the generic
 * block layer.
 */
अटल पूर्णांक dasd_flush_block_queue(काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_ccw_req *cqr, *n;
	पूर्णांक rc, i;
	काष्ठा list_head flush_queue;
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&flush_queue);
	spin_lock_bh(&block->queue_lock);
	rc = 0;
restart:
	list_क्रम_each_entry_safe(cqr, n, &block->ccw_queue, blocklist) अणु
		/* अगर this request currently owned by a dasd_device cancel it */
		अगर (cqr->status >= DASD_CQR_QUEUED)
			rc = dasd_cancel_req(cqr);
		अगर (rc < 0)
			अवरोध;
		/* Rechain request (including erp chain) so it won't be
		 * touched by the dasd_block_tasklet anymore.
		 * Replace the callback so we notice when the request
		 * is वापसed from the dasd_device layer.
		 */
		cqr->callback = _dasd_wake_block_flush_cb;
		क्रम (i = 0; cqr != शून्य; cqr = cqr->refers, i++)
			list_move_tail(&cqr->blocklist, &flush_queue);
		अगर (i > 1)
			/* moved more than one request - need to restart */
			जाओ restart;
	पूर्ण
	spin_unlock_bh(&block->queue_lock);
	/* Now call the callback function of flushed requests */
restart_cb:
	list_क्रम_each_entry_safe(cqr, n, &flush_queue, blocklist) अणु
		रुको_event(dasd_flush_wq, (cqr->status < DASD_CQR_QUEUED));
		/* Process finished ERP request. */
		अगर (cqr->refers) अणु
			spin_lock_bh(&block->queue_lock);
			__dasd_process_erp(block->base, cqr);
			spin_unlock_bh(&block->queue_lock);
			/* restart list_क्रम_xx loop since dasd_process_erp
			 * might हटाओ multiple elements */
			जाओ restart_cb;
		पूर्ण
		/* call the callback function */
		spin_lock_irqsave(&cqr->dq->lock, flags);
		cqr->endclk = get_tod_घड़ी();
		list_del_init(&cqr->blocklist);
		__dasd_cleanup_cqr(cqr);
		spin_unlock_irqrestore(&cqr->dq->lock, flags);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Schedules a call to dasd_tasklet over the device tasklet.
 */
व्योम dasd_schedule_block_bh(काष्ठा dasd_block *block)
अणु
	/* Protect against rescheduling. */
	अगर (atomic_cmpxchg(&block->tasklet_scheduled, 0, 1) != 0)
		वापस;
	/* lअगरe cycle of block is bound to it's base device */
	dasd_get_device(block->base);
	tasklet_hi_schedule(&block->tasklet);
पूर्ण
EXPORT_SYMBOL(dasd_schedule_block_bh);


/*
 * SECTION: बाह्यal block device operations
 * (request queue handling, खोलो, release, etc.)
 */

/*
 * Dasd request queue function. Called from ll_rw_blk.c
 */
अटल blk_status_t करो_dasd_request(काष्ठा blk_mq_hw_ctx *hctx,
				    स्थिर काष्ठा blk_mq_queue_data *qd)
अणु
	काष्ठा dasd_block *block = hctx->queue->queuedata;
	काष्ठा dasd_queue *dq = hctx->driver_data;
	काष्ठा request *req = qd->rq;
	काष्ठा dasd_device *basedev;
	काष्ठा dasd_ccw_req *cqr;
	blk_status_t rc = BLK_STS_OK;

	basedev = block->base;
	spin_lock_irq(&dq->lock);
	अगर (basedev->state < DASD_STATE_READY ||
	    test_bit(DASD_FLAG_OFFLINE, &basedev->flags)) अणु
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "device not ready for request %p", req);
		rc = BLK_STS_IOERR;
		जाओ out;
	पूर्ण

	/*
	 * अगर device is stopped करो not fetch new requests
	 * except failfast is active which will let requests fail
	 * immediately in __dasd_block_start_head()
	 */
	अगर (basedev->stopped && !(basedev->features & DASD_FEATURE_FAILFAST)) अणु
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "device stopped request %p", req);
		rc = BLK_STS_RESOURCE;
		जाओ out;
	पूर्ण

	अगर (basedev->features & DASD_FEATURE_READONLY &&
	    rq_data_dir(req) == WRITE) अणु
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "Rejecting write request %p", req);
		rc = BLK_STS_IOERR;
		जाओ out;
	पूर्ण

	अगर (test_bit(DASD_FLAG_ABORTALL, &basedev->flags) &&
	    (basedev->features & DASD_FEATURE_FAILFAST ||
	     blk_noretry_request(req))) अणु
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "Rejecting failfast request %p", req);
		rc = BLK_STS_IOERR;
		जाओ out;
	पूर्ण

	cqr = basedev->discipline->build_cp(basedev, block, req);
	अगर (IS_ERR(cqr)) अणु
		अगर (PTR_ERR(cqr) == -EBUSY ||
		    PTR_ERR(cqr) == -ENOMEM ||
		    PTR_ERR(cqr) == -EAGAIN) अणु
			rc = BLK_STS_RESOURCE;
			जाओ out;
		पूर्ण
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "CCW creation failed (rc=%ld) on request %p",
			      PTR_ERR(cqr), req);
		rc = BLK_STS_IOERR;
		जाओ out;
	पूर्ण
	/*
	 *  Note: callback is set to dasd_वापस_cqr_cb in
	 * __dasd_block_start_head to cover erp requests as well
	 */
	cqr->callback_data = req;
	cqr->status = DASD_CQR_FILLED;
	cqr->dq = dq;

	blk_mq_start_request(req);
	spin_lock(&block->queue_lock);
	list_add_tail(&cqr->blocklist, &block->ccw_queue);
	INIT_LIST_HEAD(&cqr->devlist);
	dasd_profile_start(block, cqr, req);
	dasd_schedule_block_bh(block);
	spin_unlock(&block->queue_lock);

out:
	spin_unlock_irq(&dq->lock);
	वापस rc;
पूर्ण

/*
 * Block समयout callback, called from the block layer
 *
 * Return values:
 * BLK_EH_RESET_TIMER अगर the request should be left running
 * BLK_EH_DONE अगर the request is handled or terminated
 *		      by the driver.
 */
क्रमागत blk_eh_समयr_वापस dasd_बार_out(काष्ठा request *req, bool reserved)
अणु
	काष्ठा dasd_block *block = req->q->queuedata;
	काष्ठा dasd_device *device;
	काष्ठा dasd_ccw_req *cqr;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	cqr = blk_mq_rq_to_pdu(req);
	अगर (!cqr)
		वापस BLK_EH_DONE;

	spin_lock_irqsave(&cqr->dq->lock, flags);
	device = cqr->startdev ? cqr->startdev : block->base;
	अगर (!device->blk_समयout) अणु
		spin_unlock_irqrestore(&cqr->dq->lock, flags);
		वापस BLK_EH_RESET_TIMER;
	पूर्ण
	DBF_DEV_EVENT(DBF_WARNING, device,
		      " dasd_times_out cqr %p status %x",
		      cqr, cqr->status);

	spin_lock(&block->queue_lock);
	spin_lock(get_ccwdev_lock(device->cdev));
	cqr->retries = -1;
	cqr->पूर्णांकrc = -ETIMEDOUT;
	अगर (cqr->status >= DASD_CQR_QUEUED) अणु
		rc = __dasd_cancel_req(cqr);
	पूर्ण अन्यथा अगर (cqr->status == DASD_CQR_FILLED ||
		   cqr->status == DASD_CQR_NEED_ERP) अणु
		cqr->status = DASD_CQR_TERMINATED;
	पूर्ण अन्यथा अगर (cqr->status == DASD_CQR_IN_ERP) अणु
		काष्ठा dasd_ccw_req *searchcqr, *nextcqr, *पंचांगpcqr;

		list_क्रम_each_entry_safe(searchcqr, nextcqr,
					 &block->ccw_queue, blocklist) अणु
			पंचांगpcqr = searchcqr;
			जबतक (पंचांगpcqr->refers)
				पंचांगpcqr = पंचांगpcqr->refers;
			अगर (पंचांगpcqr != cqr)
				जारी;
			/* searchcqr is an ERP request क्रम cqr */
			searchcqr->retries = -1;
			searchcqr->पूर्णांकrc = -ETIMEDOUT;
			अगर (searchcqr->status >= DASD_CQR_QUEUED) अणु
				rc = __dasd_cancel_req(searchcqr);
			पूर्ण अन्यथा अगर ((searchcqr->status == DASD_CQR_FILLED) ||
				   (searchcqr->status == DASD_CQR_NEED_ERP)) अणु
				searchcqr->status = DASD_CQR_TERMINATED;
				rc = 0;
			पूर्ण अन्यथा अगर (searchcqr->status == DASD_CQR_IN_ERP) अणु
				/*
				 * Shouldn't happen; most recent ERP
				 * request is at the front of queue
				 */
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(get_ccwdev_lock(device->cdev));
	dasd_schedule_block_bh(block);
	spin_unlock(&block->queue_lock);
	spin_unlock_irqrestore(&cqr->dq->lock, flags);

	वापस rc ? BLK_EH_RESET_TIMER : BLK_EH_DONE;
पूर्ण

अटल पूर्णांक dasd_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
			  अचिन्हित पूर्णांक idx)
अणु
	काष्ठा dasd_queue *dq = kzalloc(माप(*dq), GFP_KERNEL);

	अगर (!dq)
		वापस -ENOMEM;

	spin_lock_init(&dq->lock);
	hctx->driver_data = dq;

	वापस 0;
पूर्ण

अटल व्योम dasd_निकास_hctx(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित पूर्णांक idx)
अणु
	kमुक्त(hctx->driver_data);
	hctx->driver_data = शून्य;
पूर्ण

अटल व्योम dasd_request_करोne(काष्ठा request *req)
अणु
	blk_mq_end_request(req, 0);
	blk_mq_run_hw_queues(req->q, true);
पूर्ण

अटल काष्ठा blk_mq_ops dasd_mq_ops = अणु
	.queue_rq = करो_dasd_request,
	.complete = dasd_request_करोne,
	.समयout = dasd_बार_out,
	.init_hctx = dasd_init_hctx,
	.निकास_hctx = dasd_निकास_hctx,
पूर्ण;

/*
 * Allocate and initialize request queue and शेष I/O scheduler.
 */
अटल पूर्णांक dasd_alloc_queue(काष्ठा dasd_block *block)
अणु
	पूर्णांक rc;

	block->tag_set.ops = &dasd_mq_ops;
	block->tag_set.cmd_size = माप(काष्ठा dasd_ccw_req);
	block->tag_set.nr_hw_queues = nr_hw_queues;
	block->tag_set.queue_depth = queue_depth;
	block->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	block->tag_set.numa_node = NUMA_NO_NODE;

	rc = blk_mq_alloc_tag_set(&block->tag_set);
	अगर (rc)
		वापस rc;

	block->request_queue = blk_mq_init_queue(&block->tag_set);
	अगर (IS_ERR(block->request_queue))
		वापस PTR_ERR(block->request_queue);

	block->request_queue->queuedata = block;

	वापस 0;
पूर्ण

/*
 * Deactivate and मुक्त request queue.
 */
अटल व्योम dasd_मुक्त_queue(काष्ठा dasd_block *block)
अणु
	अगर (block->request_queue) अणु
		blk_cleanup_queue(block->request_queue);
		blk_mq_मुक्त_tag_set(&block->tag_set);
		block->request_queue = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक dasd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा dasd_device *base;
	पूर्णांक rc;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;

	atomic_inc(&base->block->खोलो_count);
	अगर (test_bit(DASD_FLAG_OFFLINE, &base->flags)) अणु
		rc = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (!try_module_get(base->discipline->owner)) अणु
		rc = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (dasd_probeonly) अणु
		dev_info(&base->cdev->dev,
			 "Accessing the DASD failed because it is in "
			 "probeonly mode\n");
		rc = -EPERM;
		जाओ out;
	पूर्ण

	अगर (base->state <= DASD_STATE_BASIC) अणु
		DBF_DEV_EVENT(DBF_ERR, base, " %s",
			      " Cannot open unrecognized device");
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	अगर ((mode & FMODE_WRITE) &&
	    (test_bit(DASD_FLAG_DEVICE_RO, &base->flags) ||
	     (base->features & DASD_FEATURE_READONLY))) अणु
		rc = -EROFS;
		जाओ out;
	पूर्ण

	dasd_put_device(base);
	वापस 0;

out:
	module_put(base->discipline->owner);
unlock:
	atomic_dec(&base->block->खोलो_count);
	dasd_put_device(base);
	वापस rc;
पूर्ण

अटल व्योम dasd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा dasd_device *base = dasd_device_from_gendisk(disk);
	अगर (base) अणु
		atomic_dec(&base->block->खोलो_count);
		module_put(base->discipline->owner);
		dasd_put_device(base);
	पूर्ण
पूर्ण

/*
 * Return disk geometry.
 */
अटल पूर्णांक dasd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा dasd_device *base;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	अगर (!base)
		वापस -ENODEV;

	अगर (!base->discipline ||
	    !base->discipline->fill_geometry) अणु
		dasd_put_device(base);
		वापस -EINVAL;
	पूर्ण
	base->discipline->fill_geometry(base->block, geo);
	geo->start = get_start_sect(bdev) >> base->block->s2b_shअगरt;
	dasd_put_device(base);
	वापस 0;
पूर्ण

स्थिर काष्ठा block_device_operations
dasd_device_operations = अणु
	.owner		= THIS_MODULE,
	.खोलो		= dasd_खोलो,
	.release	= dasd_release,
	.ioctl		= dasd_ioctl,
	.compat_ioctl	= dasd_ioctl,
	.getgeo		= dasd_getgeo,
	.set_पढ़ो_only	= dasd_set_पढ़ो_only,
पूर्ण;

/*******************************************************************************
 * end of block device operations
 */

अटल व्योम
dasd_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	dasd_proc_निकास();
#पूर्ण_अगर
	dasd_eer_निकास();
	kmem_cache_destroy(dasd_page_cache);
	dasd_page_cache = शून्य;
	dasd_gendisk_निकास();
	dasd_devmap_निकास();
	अगर (dasd_debug_area != शून्य) अणु
		debug_unरेजिस्टर(dasd_debug_area);
		dasd_debug_area = शून्य;
	पूर्ण
	dasd_statistics_हटाओroot();
पूर्ण

/*
 * SECTION: common functions क्रम ccw_driver use
 */

/*
 * Is the device पढ़ो-only?
 * Note that this function करोes not report the setting of the
 * पढ़ोonly device attribute, but how it is configured in z/VM.
 */
पूर्णांक dasd_device_is_ro(काष्ठा dasd_device *device)
अणु
	काष्ठा ccw_dev_id dev_id;
	काष्ठा diag210 diag_data;
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM)
		वापस 0;
	ccw_device_get_id(device->cdev, &dev_id);
	स_रखो(&diag_data, 0, माप(diag_data));
	diag_data.vrdcdvno = dev_id.devno;
	diag_data.vrdclen = माप(diag_data);
	rc = diag210(&diag_data);
	अगर (rc == 0 || rc == 2) अणु
		वापस diag_data.vrdcvfla & 0x80;
	पूर्ण अन्यथा अणु
		DBF_EVENT(DBF_WARNING, "diag210 failed for dev=%04x with rc=%d",
			  dev_id.devno, rc);
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dasd_device_is_ro);

अटल व्योम dasd_generic_स्वतः_online(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा ccw_device *cdev = data;
	पूर्णांक ret;

	ret = ccw_device_set_online(cdev);
	अगर (ret)
		pr_warn("%s: Setting the DASD online failed with rc=%d\n",
			dev_name(&cdev->dev), ret);
पूर्ण

/*
 * Initial attempt at a probe function. this can be simplअगरied once
 * the other detection code is gone.
 */
पूर्णांक dasd_generic_probe(काष्ठा ccw_device *cdev)
अणु
	cdev->handler = &dasd_पूर्णांक_handler;

	/*
	 * Automatically online either all dasd devices (dasd_स्वतःdetect)
	 * or all devices specअगरied with dasd= parameters during
	 * initial probe.
	 */
	अगर ((dasd_get_feature(cdev, DASD_FEATURE_INITIAL_ONLINE) > 0 ) ||
	    (dasd_स्वतःdetect && dasd_busid_known(dev_name(&cdev->dev)) != 0))
		async_schedule(dasd_generic_स्वतः_online, cdev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_probe);

व्योम dasd_generic_मुक्त_discipline(काष्ठा dasd_device *device)
अणु
	/* Forget the discipline inक्रमmation. */
	अगर (device->discipline) अणु
		अगर (device->discipline->uncheck_device)
			device->discipline->uncheck_device(device);
		module_put(device->discipline->owner);
		device->discipline = शून्य;
	पूर्ण
	अगर (device->base_discipline) अणु
		module_put(device->base_discipline->owner);
		device->base_discipline = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_मुक्त_discipline);

/*
 * This will one day be called from a global not_oper handler.
 * It is also used by driver_unरेजिस्टर during module unload.
 */
व्योम dasd_generic_हटाओ(काष्ठा ccw_device *cdev)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_block *block;

	device = dasd_device_from_cdev(cdev);
	अगर (IS_ERR(device))
		वापस;

	अगर (test_and_set_bit(DASD_FLAG_OFFLINE, &device->flags) &&
	    !test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) अणु
		/* Alपढ़ोy करोing offline processing */
		dasd_put_device(device);
		वापस;
	पूर्ण
	/*
	 * This device is हटाओd unconditionally. Set offline
	 * flag to prevent dasd_खोलो from खोलोing it जबतक it is
	 * no quite करोwn yet.
	 */
	dasd_set_target_state(device, DASD_STATE_NEW);
	cdev->handler = शून्य;
	/* dasd_delete_device destroys the device reference. */
	block = device->block;
	dasd_delete_device(device);
	/*
	 * lअगरe cycle of block is bound to device, so delete it after
	 * device was safely हटाओd
	 */
	अगर (block)
		dasd_मुक्त_block(block);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_हटाओ);

/*
 * Activate a device. This is called from dasd_अणुeckd,fbaपूर्ण_probe() when either
 * the device is detected क्रम the first समय and is supposed to be used
 * or the user has started activation through sysfs.
 */
पूर्णांक dasd_generic_set_online(काष्ठा ccw_device *cdev,
			    काष्ठा dasd_discipline *base_discipline)
अणु
	काष्ठा dasd_discipline *discipline;
	काष्ठा dasd_device *device;
	पूर्णांक rc;

	/* first online clears initial online feature flag */
	dasd_set_feature(cdev, DASD_FEATURE_INITIAL_ONLINE, 0);
	device = dasd_create_device(cdev);
	अगर (IS_ERR(device))
		वापस PTR_ERR(device);

	discipline = base_discipline;
	अगर (device->features & DASD_FEATURE_USEDIAG) अणु
	  	अगर (!dasd_diag_discipline_poपूर्णांकer) अणु
			/* Try to load the required module. */
			rc = request_module(DASD_DIAG_MOD);
			अगर (rc) अणु
				pr_warn("%s Setting the DASD online failed "
					"because the required module %s "
					"could not be loaded (rc=%d)\n",
					dev_name(&cdev->dev), DASD_DIAG_MOD,
					rc);
				dasd_delete_device(device);
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		/* Module init could have failed, so check again here after
		 * request_module(). */
		अगर (!dasd_diag_discipline_poपूर्णांकer) अणु
			pr_warn("%s Setting the DASD online failed because of missing DIAG discipline\n",
				dev_name(&cdev->dev));
			dasd_delete_device(device);
			वापस -ENODEV;
		पूर्ण
		discipline = dasd_diag_discipline_poपूर्णांकer;
	पूर्ण
	अगर (!try_module_get(base_discipline->owner)) अणु
		dasd_delete_device(device);
		वापस -EINVAL;
	पूर्ण
	अगर (!try_module_get(discipline->owner)) अणु
		module_put(base_discipline->owner);
		dasd_delete_device(device);
		वापस -EINVAL;
	पूर्ण
	device->base_discipline = base_discipline;
	device->discipline = discipline;

	/* check_device will allocate block device अगर necessary */
	rc = discipline->check_device(device);
	अगर (rc) अणु
		pr_warn("%s Setting the DASD online with discipline %s failed with rc=%i\n",
			dev_name(&cdev->dev), discipline->name, rc);
		module_put(discipline->owner);
		module_put(base_discipline->owner);
		dasd_delete_device(device);
		वापस rc;
	पूर्ण

	dasd_set_target_state(device, DASD_STATE_ONLINE);
	अगर (device->state <= DASD_STATE_KNOWN) अणु
		pr_warn("%s Setting the DASD online failed because of a missing discipline\n",
			dev_name(&cdev->dev));
		rc = -ENODEV;
		dasd_set_target_state(device, DASD_STATE_NEW);
		अगर (device->block)
			dasd_मुक्त_block(device->block);
		dasd_delete_device(device);
	पूर्ण अन्यथा
		pr_debug("dasd_generic device %s found\n",
				dev_name(&cdev->dev));

	रुको_event(dasd_init_रुकोq, _रुको_क्रम_device(device));

	dasd_put_device(device);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_set_online);

पूर्णांक dasd_generic_set_offline(काष्ठा ccw_device *cdev)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_block *block;
	पूर्णांक max_count, खोलो_count, rc;
	अचिन्हित दीर्घ flags;

	rc = 0;
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	device = dasd_device_from_cdev_locked(cdev);
	अगर (IS_ERR(device)) अणु
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		वापस PTR_ERR(device);
	पूर्ण

	/*
	 * We must make sure that this device is currently not in use.
	 * The खोलो_count is increased क्रम every खोलोer, that includes
	 * the blkdev_get in dasd_scan_partitions. We are only पूर्णांकerested
	 * in the other खोलोers.
	 */
	अगर (device->block) अणु
		max_count = device->block->bdev ? 0 : -1;
		खोलो_count = atomic_पढ़ो(&device->block->खोलो_count);
		अगर (खोलो_count > max_count) अणु
			अगर (खोलो_count > 0)
				pr_warn("%s: The DASD cannot be set offline with open count %i\n",
					dev_name(&cdev->dev), खोलो_count);
			अन्यथा
				pr_warn("%s: The DASD cannot be set offline while it is in use\n",
					dev_name(&cdev->dev));
			rc = -EBUSY;
			जाओ out_err;
		पूर्ण
	पूर्ण

	/*
	 * Test अगर the offline processing is alपढ़ोy running and निकास अगर so.
	 * If a safe offline is being processed this could only be a normal
	 * offline that should be able to overtake the safe offline and
	 * cancel any I/O we करो not want to रुको क्रम any दीर्घer
	 */
	अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags)) अणु
		अगर (test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) अणु
			clear_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING,
				  &device->flags);
		पूर्ण अन्यथा अणु
			rc = -EBUSY;
			जाओ out_err;
		पूर्ण
	पूर्ण
	set_bit(DASD_FLAG_OFFLINE, &device->flags);

	/*
	 * अगर safe_offline is called set safe_offline_running flag and
	 * clear safe_offline so that a call to normal offline
	 * can overrun safe_offline processing
	 */
	अगर (test_and_clear_bit(DASD_FLAG_SAFE_OFFLINE, &device->flags) &&
	    !test_and_set_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) अणु
		/* need to unlock here to रुको क्रम outstanding I/O */
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		/*
		 * If we want to set the device safe offline all IO operations
		 * should be finished beक्रमe continuing the offline process
		 * so sync bdev first and then रुको क्रम our queues to become
		 * empty
		 */
		अगर (device->block) अणु
			rc = fsync_bdev(device->block->bdev);
			अगर (rc != 0)
				जाओ पूर्णांकerrupted;
		पूर्ण
		dasd_schedule_device_bh(device);
		rc = रुको_event_पूर्णांकerruptible(shutकरोwn_रुकोq,
					      _रुको_क्रम_empty_queues(device));
		अगर (rc != 0)
			जाओ पूर्णांकerrupted;

		/*
		 * check अगर a normal offline process overtook the offline
		 * processing in this हाल simply करो nothing beside वापसing
		 * that we got पूर्णांकerrupted
		 * otherwise mark safe offline as not running any दीर्घer and
		 * जारी with normal offline
		 */
		spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
		अगर (!test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) अणु
			rc = -ERESTARTSYS;
			जाओ out_err;
		पूर्ण
		clear_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags);
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	dasd_set_target_state(device, DASD_STATE_NEW);
	/* dasd_delete_device destroys the device reference. */
	block = device->block;
	dasd_delete_device(device);
	/*
	 * lअगरe cycle of block is bound to device, so delete it after
	 * device was safely हटाओd
	 */
	अगर (block)
		dasd_मुक्त_block(block);

	वापस 0;

पूर्णांकerrupted:
	/* पूर्णांकerrupted by संकेत */
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	clear_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags);
	clear_bit(DASD_FLAG_OFFLINE, &device->flags);
out_err:
	dasd_put_device(device);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_set_offline);

पूर्णांक dasd_generic_last_path_gone(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;

	dev_warn(&device->cdev->dev, "No operational channel path is left "
		 "for the device\n");
	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "last path gone");
	/* First of all call extended error reporting. */
	dasd_eer_ग_लिखो(device, शून्य, DASD_EER_NOPATH);

	अगर (device->state < DASD_STATE_BASIC)
		वापस 0;
	/* Device is active. We want to keep it. */
	list_क्रम_each_entry(cqr, &device->ccw_queue, devlist)
		अगर ((cqr->status == DASD_CQR_IN_IO) ||
		    (cqr->status == DASD_CQR_CLEAR_PENDING)) अणु
			cqr->status = DASD_CQR_QUEUED;
			cqr->retries++;
		पूर्ण
	dasd_device_set_stop_bits(device, DASD_STOPPED_DC_WAIT);
	dasd_device_clear_समयr(device);
	dasd_schedule_device_bh(device);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_last_path_gone);

पूर्णांक dasd_generic_path_operational(काष्ठा dasd_device *device)
अणु
	dev_info(&device->cdev->dev, "A channel path to the device has become "
		 "operational\n");
	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "path operational");
	dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_DC_WAIT);
	dasd_schedule_device_bh(device);
	अगर (device->block) अणु
		dasd_schedule_block_bh(device->block);
		अगर (device->block->request_queue)
			blk_mq_run_hw_queues(device->block->request_queue,
					     true);
		पूर्ण

	अगर (!device->stopped)
		wake_up(&generic_रुकोq);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_path_operational);

पूर्णांक dasd_generic_notअगरy(काष्ठा ccw_device *cdev, पूर्णांक event)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक ret;

	device = dasd_device_from_cdev_locked(cdev);
	अगर (IS_ERR(device))
		वापस 0;
	ret = 0;
	चयन (event) अणु
	हाल CIO_GONE:
	हाल CIO_BOXED:
	हाल CIO_NO_PATH:
		dasd_path_no_path(device);
		ret = dasd_generic_last_path_gone(device);
		अवरोध;
	हाल CIO_OPER:
		ret = 1;
		अगर (dasd_path_get_opm(device))
			ret = dasd_generic_path_operational(device);
		अवरोध;
	पूर्ण
	dasd_put_device(device);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_notअगरy);

व्योम dasd_generic_path_event(काष्ठा ccw_device *cdev, पूर्णांक *path_event)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक chp, olकरोpm, hpfpm, अगरccpm;

	device = dasd_device_from_cdev_locked(cdev);
	अगर (IS_ERR(device))
		वापस;

	olकरोpm = dasd_path_get_opm(device);
	क्रम (chp = 0; chp < 8; chp++) अणु
		अगर (path_event[chp] & PE_PATH_GONE) अणु
			dasd_path_notoper(device, chp);
		पूर्ण
		अगर (path_event[chp] & PE_PATH_AVAILABLE) अणु
			dasd_path_available(device, chp);
			dasd_schedule_device_bh(device);
		पूर्ण
		अगर (path_event[chp] & PE_PATHGROUP_ESTABLISHED) अणु
			अगर (!dasd_path_is_operational(device, chp) &&
			    !dasd_path_need_verअगरy(device, chp)) अणु
				/*
				 * we can not establish a pathgroup on an
				 * unavailable path, so trigger a path
				 * verअगरication first
				 */
			dasd_path_available(device, chp);
			dasd_schedule_device_bh(device);
			पूर्ण
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				      "Pathgroup re-established\n");
			अगर (device->discipline->kick_validate)
				device->discipline->kick_validate(device);
		पूर्ण
		अगर (path_event[chp] & PE_PATH_FCES_EVENT) अणु
			dasd_path_fcsec_update(device, chp);
			dasd_schedule_device_bh(device);
		पूर्ण
	पूर्ण
	hpfpm = dasd_path_get_hpfpm(device);
	अगरccpm = dasd_path_get_अगरccpm(device);
	अगर (!dasd_path_get_opm(device) && hpfpm) अणु
		/*
		 * device has no operational paths but at least one path is
		 * disabled due to HPF errors
		 * disable HPF at all and use the path(s) again
		 */
		अगर (device->discipline->disable_hpf)
			device->discipline->disable_hpf(device);
		dasd_device_set_stop_bits(device, DASD_STOPPED_NOT_ACC);
		dasd_path_set_tbvpm(device, hpfpm);
		dasd_schedule_device_bh(device);
		dasd_schedule_requeue(device);
	पूर्ण अन्यथा अगर (!dasd_path_get_opm(device) && अगरccpm) अणु
		/*
		 * device has no operational paths but at least one path is
		 * disabled due to IFCC errors
		 * trigger path verअगरication on paths with IFCC errors
		 */
		dasd_path_set_tbvpm(device, अगरccpm);
		dasd_schedule_device_bh(device);
	पूर्ण
	अगर (olकरोpm && !dasd_path_get_opm(device) && !hpfpm && !अगरccpm) अणु
		dev_warn(&device->cdev->dev,
			 "No verified channel paths remain for the device\n");
		DBF_DEV_EVENT(DBF_WARNING, device,
			      "%s", "last verified path gone");
		dasd_eer_ग_लिखो(device, शून्य, DASD_EER_NOPATH);
		dasd_device_set_stop_bits(device,
					  DASD_STOPPED_DC_WAIT);
	पूर्ण
	dasd_put_device(device);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_path_event);

पूर्णांक dasd_generic_verअगरy_path(काष्ठा dasd_device *device, __u8 lpm)
अणु
	अगर (!dasd_path_get_opm(device) && lpm) अणु
		dasd_path_set_opm(device, lpm);
		dasd_generic_path_operational(device);
	पूर्ण अन्यथा
		dasd_path_add_opm(device, lpm);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_verअगरy_path);

व्योम dasd_generic_space_exhaust(काष्ठा dasd_device *device,
				काष्ठा dasd_ccw_req *cqr)
अणु
	dasd_eer_ग_लिखो(device, शून्य, DASD_EER_NOSPC);

	अगर (device->state < DASD_STATE_BASIC)
		वापस;

	अगर (cqr->status == DASD_CQR_IN_IO ||
	    cqr->status == DASD_CQR_CLEAR_PENDING) अणु
		cqr->status = DASD_CQR_QUEUED;
		cqr->retries++;
	पूर्ण
	dasd_device_set_stop_bits(device, DASD_STOPPED_NOSPC);
	dasd_device_clear_समयr(device);
	dasd_schedule_device_bh(device);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_space_exhaust);

व्योम dasd_generic_space_avail(काष्ठा dasd_device *device)
अणु
	dev_info(&device->cdev->dev, "Extent pool space is available\n");
	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "space available");

	dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_NOSPC);
	dasd_schedule_device_bh(device);

	अगर (device->block) अणु
		dasd_schedule_block_bh(device->block);
		अगर (device->block->request_queue)
			blk_mq_run_hw_queues(device->block->request_queue, true);
	पूर्ण
	अगर (!device->stopped)
		wake_up(&generic_रुकोq);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_space_avail);

/*
 * clear active requests and requeue them to block layer अगर possible
 */
अटल पूर्णांक dasd_generic_requeue_all_requests(काष्ठा dasd_device *device)
अणु
	काष्ठा list_head requeue_queue;
	काष्ठा dasd_ccw_req *cqr, *n;
	काष्ठा dasd_ccw_req *refers;
	पूर्णांक rc;

	INIT_LIST_HEAD(&requeue_queue);
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = 0;
	list_क्रम_each_entry_safe(cqr, n, &device->ccw_queue, devlist) अणु
		/* Check status and move request to flush_queue */
		अगर (cqr->status == DASD_CQR_IN_IO) अणु
			rc = device->discipline->term_IO(cqr);
			अगर (rc) अणु
				/* unable to terminate requeust */
				dev_err(&device->cdev->dev,
					"Unable to terminate request %p "
					"on suspend\n", cqr);
				spin_unlock_irq(get_ccwdev_lock(device->cdev));
				dasd_put_device(device);
				वापस rc;
			पूर्ण
		पूर्ण
		list_move_tail(&cqr->devlist, &requeue_queue);
	पूर्ण
	spin_unlock_irq(get_ccwdev_lock(device->cdev));

	list_क्रम_each_entry_safe(cqr, n, &requeue_queue, devlist) अणु
		रुको_event(dasd_flush_wq,
			   (cqr->status != DASD_CQR_CLEAR_PENDING));

		/*
		 * requeue requests to blocklayer will only work
		 * क्रम block device requests
		 */
		अगर (_dasd_requeue_request(cqr))
			जारी;

		/* हटाओ requests from device and block queue */
		list_del_init(&cqr->devlist);
		जबतक (cqr->refers != शून्य) अणु
			refers = cqr->refers;
			/* हटाओ the request from the block queue */
			list_del(&cqr->blocklist);
			/* मुक्त the finished erp request */
			dasd_मुक्त_erp_request(cqr, cqr->memdev);
			cqr = refers;
		पूर्ण

		/*
		 * _dasd_requeue_request alपढ़ोy checked क्रम a valid
		 * blockdevice, no need to check again
		 * all erp requests (cqr->refers) have a cqr->block
		 * poपूर्णांकer copy from the original cqr
		 */
		list_del_init(&cqr->blocklist);
		cqr->block->base->discipline->मुक्त_cp(
			cqr, (काष्ठा request *) cqr->callback_data);
	पूर्ण

	/*
	 * अगर requests reमुख्य then they are पूर्णांकernal request
	 * and go back to the device queue
	 */
	अगर (!list_empty(&requeue_queue)) अणु
		/* move मुक्तze_queue to start of the ccw_queue */
		spin_lock_irq(get_ccwdev_lock(device->cdev));
		list_splice_tail(&requeue_queue, &device->ccw_queue);
		spin_unlock_irq(get_ccwdev_lock(device->cdev));
	पूर्ण
	dasd_schedule_device_bh(device);
	वापस rc;
पूर्ण

अटल व्योम करो_requeue_requests(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dasd_device *device = container_of(work, काष्ठा dasd_device,
						  requeue_requests);
	dasd_generic_requeue_all_requests(device);
	dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_NOT_ACC);
	अगर (device->block)
		dasd_schedule_block_bh(device->block);
	dasd_put_device(device);
पूर्ण

व्योम dasd_schedule_requeue(काष्ठा dasd_device *device)
अणु
	dasd_get_device(device);
	/* queue call to dasd_reload_device to the kernel event daemon. */
	अगर (!schedule_work(&device->requeue_requests))
		dasd_put_device(device);
पूर्ण
EXPORT_SYMBOL(dasd_schedule_requeue);

अटल काष्ठा dasd_ccw_req *dasd_generic_build_rdc(काष्ठा dasd_device *device,
						   पूर्णांक rdc_buffer_size,
						   पूर्णांक magic)
अणु
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;

	cqr = dasd_sदो_स्मृति_request(magic, 1 /* RDC */, rdc_buffer_size, device,
				   शून्य);

	अगर (IS_ERR(cqr)) अणु
		/* पूर्णांकernal error 13 - Allocating the RDC request failed*/
		dev_err(&device->cdev->dev,
			 "An error occurred in the DASD device driver, "
			 "reason=%s\n", "13");
		वापस cqr;
	पूर्ण

	ccw = cqr->cpaddr;
	ccw->cmd_code = CCW_CMD_RDC;
	ccw->cda = (__u32)(addr_t) cqr->data;
	ccw->flags = 0;
	ccw->count = rdc_buffer_size;
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->expires = 10*HZ;
	cqr->retries = 256;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	वापस cqr;
पूर्ण


पूर्णांक dasd_generic_पढ़ो_dev_अक्षरs(काष्ठा dasd_device *device, पूर्णांक magic,
				व्योम *rdc_buffer, पूर्णांक rdc_buffer_size)
अणु
	पूर्णांक ret;
	काष्ठा dasd_ccw_req *cqr;

	cqr = dasd_generic_build_rdc(device, rdc_buffer_size, magic);
	अगर (IS_ERR(cqr))
		वापस PTR_ERR(cqr);

	ret = dasd_sleep_on(cqr);
	अगर (ret == 0)
		स_नकल(rdc_buffer, cqr->data, rdc_buffer_size);
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_पढ़ो_dev_अक्षरs);

/*
 *   In command mode and transport mode we need to look क्रम sense
 *   data in dअगरferent places. The sense data itself is allways
 *   an array of 32 bytes, so we can unअगरy the sense data access
 *   क्रम both modes.
 */
अक्षर *dasd_get_sense(काष्ठा irb *irb)
अणु
	काष्ठा tsb *tsb = शून्य;
	अक्षर *sense = शून्य;

	अगर (scsw_is_पंचांग(&irb->scsw) && (irb->scsw.पंचांग.fcxs == 0x01)) अणु
		अगर (irb->scsw.पंचांग.tcw)
			tsb = tcw_get_tsb((काष्ठा tcw *)(अचिन्हित दीर्घ)
					  irb->scsw.पंचांग.tcw);
		अगर (tsb && tsb->length == 64 && tsb->flags)
			चयन (tsb->flags & 0x07) अणु
			हाल 1:	/* tsa_iostat */
				sense = tsb->tsa.iostat.sense;
				अवरोध;
			हाल 2: /* tsa_ddpc */
				sense = tsb->tsa.ddpc.sense;
				अवरोध;
			शेष:
				/* currently we करोn't use पूर्णांकerrogate data */
				अवरोध;
			पूर्ण
	पूर्ण अन्यथा अगर (irb->esw.esw0.erw.cons) अणु
		sense = irb->ecw;
	पूर्ण
	वापस sense;
पूर्ण
EXPORT_SYMBOL_GPL(dasd_get_sense);

व्योम dasd_generic_shutकरोwn(काष्ठा ccw_device *cdev)
अणु
	काष्ठा dasd_device *device;

	device = dasd_device_from_cdev(cdev);
	अगर (IS_ERR(device))
		वापस;

	अगर (device->block)
		dasd_schedule_block_bh(device->block);

	dasd_schedule_device_bh(device);

	रुको_event(shutकरोwn_रुकोq, _रुको_क्रम_empty_queues(device));
पूर्ण
EXPORT_SYMBOL_GPL(dasd_generic_shutकरोwn);

अटल पूर्णांक __init dasd_init(व्योम)
अणु
	पूर्णांक rc;

	init_रुकोqueue_head(&dasd_init_रुकोq);
	init_रुकोqueue_head(&dasd_flush_wq);
	init_रुकोqueue_head(&generic_रुकोq);
	init_रुकोqueue_head(&shutकरोwn_रुकोq);

	/* रेजिस्टर 'common' DASD debug area, used क्रम all DBF_XXX calls */
	dasd_debug_area = debug_रेजिस्टर("dasd", 1, 1, 8 * माप(दीर्घ));
	अगर (dasd_debug_area == शून्य) अणु
		rc = -ENOMEM;
		जाओ failed;
	पूर्ण
	debug_रेजिस्टर_view(dasd_debug_area, &debug_प्र_लिखो_view);
	debug_set_level(dasd_debug_area, DBF_WARNING);

	DBF_EVENT(DBF_EMERG, "%s", "debug area created");

	dasd_diag_discipline_poपूर्णांकer = शून्य;

	dasd_statistics_createroot();

	rc = dasd_devmap_init();
	अगर (rc)
		जाओ failed;
	rc = dasd_gendisk_init();
	अगर (rc)
		जाओ failed;
	rc = dasd_parse();
	अगर (rc)
		जाओ failed;
	rc = dasd_eer_init();
	अगर (rc)
		जाओ failed;
#अगर_घोषित CONFIG_PROC_FS
	rc = dasd_proc_init();
	अगर (rc)
		जाओ failed;
#पूर्ण_अगर

	वापस 0;
failed:
	pr_info("The DASD device driver could not be initialized\n");
	dasd_निकास();
	वापस rc;
पूर्ण

module_init(dasd_init);
module_निकास(dasd_निकास);
