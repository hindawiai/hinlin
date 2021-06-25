<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * scsi_scan.c
 *
 * Copyright (C) 2000 Eric Youngdale,
 * Copyright (C) 2002 Patrick Mansfield
 *
 * The general scanning/probing algorithm is as follows, exceptions are
 * made to it depending on device specअगरic flags, compilation options, and
 * global variable (boot or module load समय) settings.
 *
 * A specअगरic LUN is scanned via an INQUIRY command; अगर the LUN has a
 * device attached, a scsi_device is allocated and setup क्रम it.
 *
 * For every id of every channel on the given host:
 *
 * 	Scan LUN 0; अगर the target responds to LUN 0 (even अगर there is no
 * 	device or storage attached to LUN 0):
 *
 * 		If LUN 0 has a device attached, allocate and setup a
 * 		scsi_device क्रम it.
 *
 * 		If target is SCSI-3 or up, issue a REPORT LUN, and scan
 * 		all of the LUNs वापसed by the REPORT LUN; अन्यथा,
 * 		sequentially scan LUNs up until some maximum is reached,
 * 		or a LUN is seen that cannot have a device attached to it.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/async.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_devinfo.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_dh.h>
#समावेश <scsi/scsi_eh.h>

#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"

#घोषणा ALLOC_FAILURE_MSG	KERN_ERR "%s: Allocation failure during" \
	" SCSI scanning, some SCSI devices might not be configured\n"

/*
 * Default समयout
 */
#घोषणा SCSI_TIMEOUT (2*HZ)
#घोषणा SCSI_REPORT_LUNS_TIMEOUT (30*HZ)

/*
 * Prefix values क्रम the SCSI id's (stored in sysfs name field)
 */
#घोषणा SCSI_UID_SER_NUM 'S'
#घोषणा SCSI_UID_UNKNOWN 'Z'

/*
 * Return values of some of the scanning functions.
 *
 * SCSI_SCAN_NO_RESPONSE: no valid response received from the target, this
 * includes allocation or general failures preventing IO from being sent.
 *
 * SCSI_SCAN_TARGET_PRESENT: target responded, but no device is available
 * on the given LUN.
 *
 * SCSI_SCAN_LUN_PRESENT: target responded, and a device is available on a
 * given LUN.
 */
#घोषणा SCSI_SCAN_NO_RESPONSE		0
#घोषणा SCSI_SCAN_TARGET_PRESENT	1
#घोषणा SCSI_SCAN_LUN_PRESENT		2

अटल स्थिर अक्षर *scsi_null_device_strs = "nullnullnullnull";

#घोषणा MAX_SCSI_LUNS	512

अटल u64 max_scsi_luns = MAX_SCSI_LUNS;

module_param_named(max_luns, max_scsi_luns, ulदीर्घ, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(max_luns,
		 "last scsi LUN (should be between 1 and 2^64-1)");

#अगर_घोषित CONFIG_SCSI_SCAN_ASYNC
#घोषणा SCSI_SCAN_TYPE_DEFAULT "async"
#अन्यथा
#घोषणा SCSI_SCAN_TYPE_DEFAULT "sync"
#पूर्ण_अगर

अक्षर scsi_scan_type[7] = SCSI_SCAN_TYPE_DEFAULT;

module_param_string(scan, scsi_scan_type, माप(scsi_scan_type),
		    S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(scan, "sync, async, manual, or none. "
		 "Setting to 'manual' disables automatic scanning, but allows "
		 "for manual device scan via the 'scan' sysfs attribute.");

अटल अचिन्हित पूर्णांक scsi_inq_समयout = SCSI_TIMEOUT/HZ + 18;

module_param_named(inq_समयout, scsi_inq_समयout, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(inq_समयout, 
		 "Timeout (in seconds) waiting for devices to answer INQUIRY."
		 " Default is 20. Some devices may need more; most need less.");

/* This lock protects only this list */
अटल DEFINE_SPINLOCK(async_scan_lock);
अटल LIST_HEAD(scanning_hosts);

काष्ठा async_scan_data अणु
	काष्ठा list_head list;
	काष्ठा Scsi_Host *shost;
	काष्ठा completion prev_finished;
पूर्ण;

/**
 * scsi_complete_async_scans - Wait क्रम asynchronous scans to complete
 *
 * When this function वापसs, any host which started scanning beक्रमe
 * this function was called will have finished its scan.  Hosts which
 * started scanning after this function was called may or may not have
 * finished.
 */
पूर्णांक scsi_complete_async_scans(व्योम)
अणु
	काष्ठा async_scan_data *data;

	करो अणु
		अगर (list_empty(&scanning_hosts))
			वापस 0;
		/* If we can't get memory immediately, that's OK.  Just
		 * sleep a little.  Even अगर we never get memory, the async
		 * scans will finish eventually.
		 */
		data = kदो_स्मृति(माप(*data), GFP_KERNEL);
		अगर (!data)
			msleep(1);
	पूर्ण जबतक (!data);

	data->shost = शून्य;
	init_completion(&data->prev_finished);

	spin_lock(&async_scan_lock);
	/* Check that there's still somebody अन्यथा on the list */
	अगर (list_empty(&scanning_hosts))
		जाओ करोne;
	list_add_tail(&data->list, &scanning_hosts);
	spin_unlock(&async_scan_lock);

	prपूर्णांकk(KERN_INFO "scsi: waiting for bus probes to complete ...\n");
	रुको_क्रम_completion(&data->prev_finished);

	spin_lock(&async_scan_lock);
	list_del(&data->list);
	अगर (!list_empty(&scanning_hosts)) अणु
		काष्ठा async_scan_data *next = list_entry(scanning_hosts.next,
				काष्ठा async_scan_data, list);
		complete(&next->prev_finished);
	पूर्ण
 करोne:
	spin_unlock(&async_scan_lock);

	kमुक्त(data);
	वापस 0;
पूर्ण

/**
 * scsi_unlock_floptical - unlock device via a special MODE SENSE command
 * @sdev:	scsi device to send command to
 * @result:	area to store the result of the MODE SENSE
 *
 * Description:
 *     Send a venकरोr specअगरic MODE SENSE (not a MODE SELECT) command.
 *     Called क्रम BLIST_KEY devices.
 **/
अटल व्योम scsi_unlock_floptical(काष्ठा scsi_device *sdev,
				  अचिन्हित अक्षर *result)
अणु
	अचिन्हित अक्षर scsi_cmd[MAX_COMMAND_SIZE];

	sdev_prपूर्णांकk(KERN_NOTICE, sdev, "unlocking floptical drive\n");
	scsi_cmd[0] = MODE_SENSE;
	scsi_cmd[1] = 0;
	scsi_cmd[2] = 0x2e;
	scsi_cmd[3] = 0;
	scsi_cmd[4] = 0x2a;     /* size */
	scsi_cmd[5] = 0;
	scsi_execute_req(sdev, scsi_cmd, DMA_FROM_DEVICE, result, 0x2a, शून्य,
			 SCSI_TIMEOUT, 3, शून्य);
पूर्ण

/**
 * scsi_alloc_sdev - allocate and setup a scsi_Device
 * @starget: which target to allocate a &scsi_device क्रम
 * @lun: which lun
 * @hostdata: usually शून्य and set by ->slave_alloc instead
 *
 * Description:
 *     Allocate, initialize क्रम io, and वापस a poपूर्णांकer to a scsi_Device.
 *     Stores the @shost, @channel, @id, and @lun in the scsi_Device, and
 *     adds scsi_Device to the appropriate list.
 *
 * Return value:
 *     scsi_Device poपूर्णांकer, or शून्य on failure.
 **/
अटल काष्ठा scsi_device *scsi_alloc_sdev(काष्ठा scsi_target *starget,
					   u64 lun, व्योम *hostdata)
अणु
	अचिन्हित पूर्णांक depth;
	काष्ठा scsi_device *sdev;
	पूर्णांक display_failure_msg = 1, ret;
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);

	sdev = kzalloc(माप(*sdev) + shost->transportt->device_size,
		       GFP_KERNEL);
	अगर (!sdev)
		जाओ out;

	sdev->venकरोr = scsi_null_device_strs;
	sdev->model = scsi_null_device_strs;
	sdev->rev = scsi_null_device_strs;
	sdev->host = shost;
	sdev->queue_ramp_up_period = SCSI_DEFAULT_RAMP_UP_PERIOD;
	sdev->id = starget->id;
	sdev->lun = lun;
	sdev->channel = starget->channel;
	mutex_init(&sdev->state_mutex);
	sdev->sdev_state = SDEV_CREATED;
	INIT_LIST_HEAD(&sdev->siblings);
	INIT_LIST_HEAD(&sdev->same_target_siblings);
	INIT_LIST_HEAD(&sdev->starved_entry);
	INIT_LIST_HEAD(&sdev->event_list);
	spin_lock_init(&sdev->list_lock);
	mutex_init(&sdev->inquiry_mutex);
	INIT_WORK(&sdev->event_work, scsi_evt_thपढ़ो);
	INIT_WORK(&sdev->requeue_work, scsi_requeue_run_queue);

	sdev->sdev_gendev.parent = get_device(&starget->dev);
	sdev->sdev_target = starget;

	/* usually शून्य and set by ->slave_alloc instead */
	sdev->hostdata = hostdata;

	/* अगर the device needs this changing, it may करो so in the
	 * slave_configure function */
	sdev->max_device_blocked = SCSI_DEFAULT_DEVICE_BLOCKED;

	/*
	 * Some low level driver could use device->type
	 */
	sdev->type = -1;

	/*
	 * Assume that the device will have handshaking problems,
	 * and then fix this field later अगर it turns out it
	 * करोesn't
	 */
	sdev->borken = 1;

	sdev->request_queue = scsi_mq_alloc_queue(sdev);
	अगर (!sdev->request_queue) अणु
		/* release fn is set up in scsi_sysfs_device_initialise, so
		 * have to मुक्त and put manually here */
		put_device(&starget->dev);
		kमुक्त(sdev);
		जाओ out;
	पूर्ण
	WARN_ON_ONCE(!blk_get_queue(sdev->request_queue));
	sdev->request_queue->queuedata = sdev;

	depth = sdev->host->cmd_per_lun ?: 1;

	/*
	 * Use .can_queue as budget map's depth because we have to
	 * support adjusting queue depth from sysfs. Meanसमय use
	 * शेष device queue depth to figure out sbiपंचांगap shअगरt
	 * since we use this queue depth most of बार.
	 */
	अगर (sbiपंचांगap_init_node(&sdev->budget_map,
				scsi_device_max_queue_depth(sdev),
				sbiपंचांगap_calculate_shअगरt(depth),
				GFP_KERNEL, sdev->request_queue->node,
				false, true)) अणु
		put_device(&starget->dev);
		kमुक्त(sdev);
		जाओ out;
	पूर्ण

	scsi_change_queue_depth(sdev, depth);

	scsi_sysfs_device_initialize(sdev);

	अगर (shost->hostt->slave_alloc) अणु
		ret = shost->hostt->slave_alloc(sdev);
		अगर (ret) अणु
			/*
			 * अगर LLDD reports slave not present, करोn't clutter
			 * console with alloc failure messages
			 */
			अगर (ret == -ENXIO)
				display_failure_msg = 0;
			जाओ out_device_destroy;
		पूर्ण
	पूर्ण

	वापस sdev;

out_device_destroy:
	__scsi_हटाओ_device(sdev);
out:
	अगर (display_failure_msg)
		prपूर्णांकk(ALLOC_FAILURE_MSG, __func__);
	वापस शून्य;
पूर्ण

अटल व्योम scsi_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा device *dev = &starget->dev;
	काष्ठा Scsi_Host *shost = dev_to_shost(dev->parent);
	अचिन्हित दीर्घ flags;

	BUG_ON(starget->state == STARGET_DEL);
	starget->state = STARGET_DEL;
	transport_destroy_device(dev);
	spin_lock_irqsave(shost->host_lock, flags);
	अगर (shost->hostt->target_destroy)
		shost->hostt->target_destroy(starget);
	list_del_init(&starget->siblings);
	spin_unlock_irqrestore(shost->host_lock, flags);
	put_device(dev);
पूर्ण

अटल व्योम scsi_target_dev_release(काष्ठा device *dev)
अणु
	काष्ठा device *parent = dev->parent;
	काष्ठा scsi_target *starget = to_scsi_target(dev);

	kमुक्त(starget);
	put_device(parent);
पूर्ण

अटल काष्ठा device_type scsi_target_type = अणु
	.name =		"scsi_target",
	.release =	scsi_target_dev_release,
पूर्ण;

पूर्णांक scsi_is_target_device(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &scsi_target_type;
पूर्ण
EXPORT_SYMBOL(scsi_is_target_device);

अटल काष्ठा scsi_target *__scsi_find_target(काष्ठा device *parent,
					      पूर्णांक channel, uपूर्णांक id)
अणु
	काष्ठा scsi_target *starget, *found_starget = शून्य;
	काष्ठा Scsi_Host *shost = dev_to_shost(parent);
	/*
	 * Search क्रम an existing target क्रम this sdev.
	 */
	list_क्रम_each_entry(starget, &shost->__tarमाला_लो, siblings) अणु
		अगर (starget->id == id &&
		    starget->channel == channel) अणु
			found_starget = starget;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found_starget)
		get_device(&found_starget->dev);

	वापस found_starget;
पूर्ण

/**
 * scsi_target_reap_ref_release - हटाओ target from visibility
 * @kref: the reap_ref in the target being released
 *
 * Called on last put of reap_ref, which is the indication that no device
 * under this target is visible anymore, so render the target invisible in
 * sysfs.  Note: we have to be in user context here because the target reaps
 * should be करोne in places where the scsi device visibility is being हटाओd.
 */
अटल व्योम scsi_target_reap_ref_release(काष्ठा kref *kref)
अणु
	काष्ठा scsi_target *starget
		= container_of(kref, काष्ठा scsi_target, reap_ref);

	/*
	 * अगर we get here and the target is still in a CREATED state that
	 * means it was allocated but never made visible (because a scan
	 * turned up no LUNs), so करोn't call device_del() on it.
	 */
	अगर ((starget->state != STARGET_CREATED) &&
	    (starget->state != STARGET_CREATED_REMOVE)) अणु
		transport_हटाओ_device(&starget->dev);
		device_del(&starget->dev);
	पूर्ण
	scsi_target_destroy(starget);
पूर्ण

अटल व्योम scsi_target_reap_ref_put(काष्ठा scsi_target *starget)
अणु
	kref_put(&starget->reap_ref, scsi_target_reap_ref_release);
पूर्ण

/**
 * scsi_alloc_target - allocate a new or find an existing target
 * @parent:	parent of the target (need not be a scsi host)
 * @channel:	target channel number (zero अगर no channels)
 * @id:		target id number
 *
 * Return an existing target अगर one exists, provided it hasn't alपढ़ोy
 * gone पूर्णांकo STARGET_DEL state, otherwise allocate a new target.
 *
 * The target is वापसed with an incremented reference, so the caller
 * is responsible क्रम both reaping and करोing a last put
 */
अटल काष्ठा scsi_target *scsi_alloc_target(काष्ठा device *parent,
					     पूर्णांक channel, uपूर्णांक id)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(parent);
	काष्ठा device *dev = शून्य;
	अचिन्हित दीर्घ flags;
	स्थिर पूर्णांक size = माप(काष्ठा scsi_target)
		+ shost->transportt->target_size;
	काष्ठा scsi_target *starget;
	काष्ठा scsi_target *found_target;
	पूर्णांक error, ref_got;

	starget = kzalloc(size, GFP_KERNEL);
	अगर (!starget) अणु
		prपूर्णांकk(KERN_ERR "%s: allocation failure\n", __func__);
		वापस शून्य;
	पूर्ण
	dev = &starget->dev;
	device_initialize(dev);
	kref_init(&starget->reap_ref);
	dev->parent = get_device(parent);
	dev_set_name(dev, "target%d:%d:%d", shost->host_no, channel, id);
	dev->bus = &scsi_bus_type;
	dev->type = &scsi_target_type;
	starget->id = id;
	starget->channel = channel;
	starget->can_queue = 0;
	INIT_LIST_HEAD(&starget->siblings);
	INIT_LIST_HEAD(&starget->devices);
	starget->state = STARGET_CREATED;
	starget->scsi_level = SCSI_2;
	starget->max_target_blocked = SCSI_DEFAULT_TARGET_BLOCKED;
 retry:
	spin_lock_irqsave(shost->host_lock, flags);

	found_target = __scsi_find_target(parent, channel, id);
	अगर (found_target)
		जाओ found;

	list_add_tail(&starget->siblings, &shost->__tarमाला_लो);
	spin_unlock_irqrestore(shost->host_lock, flags);
	/* allocate and add */
	transport_setup_device(dev);
	अगर (shost->hostt->target_alloc) अणु
		error = shost->hostt->target_alloc(starget);

		अगर(error) अणु
			dev_prपूर्णांकk(KERN_ERR, dev, "target allocation failed, error %d\n", error);
			/* करोn't want scsi_target_reap to करो the final
			 * put because it will be under the host lock */
			scsi_target_destroy(starget);
			वापस शून्य;
		पूर्ण
	पूर्ण
	get_device(dev);

	वापस starget;

 found:
	/*
	 * release routine alपढ़ोy fired अगर kref is zero, so अगर we can still
	 * take the reference, the target must be alive.  If we can't, it must
	 * be dying and we need to रुको क्रम a new target
	 */
	ref_got = kref_get_unless_zero(&found_target->reap_ref);

	spin_unlock_irqrestore(shost->host_lock, flags);
	अगर (ref_got) अणु
		put_device(dev);
		वापस found_target;
	पूर्ण
	/*
	 * Unक्रमtunately, we found a dying target; need to रुको until it's
	 * dead beक्रमe we can get a new one.  There is an anomaly here.  We
	 * *should* call scsi_target_reap() to balance the kref_get() of the
	 * reap_ref above.  However, since the target being released, it's
	 * alपढ़ोy invisible and the reap_ref is irrelevant.  If we call
	 * scsi_target_reap() we might spuriously करो another device_del() on
	 * an alपढ़ोy invisible target.
	 */
	put_device(&found_target->dev);
	/*
	 * length of समय is irrelevant here, we just want to yield the CPU
	 * क्रम a tick to aव्योम busy रुकोing क्रम the target to die.
	 */
	msleep(1);
	जाओ retry;
पूर्ण

/**
 * scsi_target_reap - check to see अगर target is in use and destroy अगर not
 * @starget: target to be checked
 *
 * This is used after removing a LUN or करोing a last put of the target
 * it checks atomically that nothing is using the target and हटाओs
 * it अगर so.
 */
व्योम scsi_target_reap(काष्ठा scsi_target *starget)
अणु
	/*
	 * serious problem अगर this triggers: STARGET_DEL is only set in the अगर
	 * the reap_ref drops to zero, so we're trying to करो another final put
	 * on an alपढ़ोy released kref
	 */
	BUG_ON(starget->state == STARGET_DEL);
	scsi_target_reap_ref_put(starget);
पूर्ण

/**
 * scsi_sanitize_inquiry_string - हटाओ non-graphical अक्षरs from an
 *                                INQUIRY result string
 * @s: INQUIRY result string to sanitize
 * @len: length of the string
 *
 * Description:
 *	The SCSI spec says that INQUIRY venकरोr, product, and revision
 *	strings must consist entirely of graphic ASCII अक्षरacters,
 *	padded on the right with spaces.  Since not all devices obey
 *	this rule, we will replace non-graphic or non-ASCII अक्षरacters
 *	with spaces.  Exception: a NUL अक्षरacter is पूर्णांकerpreted as a
 *	string terminator, so all the following अक्षरacters are set to
 *	spaces.
 **/
व्योम scsi_sanitize_inquiry_string(अचिन्हित अक्षर *s, पूर्णांक len)
अणु
	पूर्णांक terminated = 0;

	क्रम (; len > 0; (--len, ++s)) अणु
		अगर (*s == 0)
			terminated = 1;
		अगर (terminated || *s < 0x20 || *s > 0x7e)
			*s = ' ';
	पूर्ण
पूर्ण
EXPORT_SYMBOL(scsi_sanitize_inquiry_string);

/**
 * scsi_probe_lun - probe a single LUN using a SCSI INQUIRY
 * @sdev:	scsi_device to probe
 * @inq_result:	area to store the INQUIRY result
 * @result_len: len of inq_result
 * @bflags:	store any bflags found here
 *
 * Description:
 *     Probe the lun associated with @req using a standard SCSI INQUIRY;
 *
 *     If the INQUIRY is successful, zero is वापसed and the
 *     INQUIRY data is in @inq_result; the scsi_level and INQUIRY length
 *     are copied to the scsi_device any flags value is stored in *@bflags.
 **/
अटल पूर्णांक scsi_probe_lun(काष्ठा scsi_device *sdev, अचिन्हित अक्षर *inq_result,
			  पूर्णांक result_len, blist_flags_t *bflags)
अणु
	अचिन्हित अक्षर scsi_cmd[MAX_COMMAND_SIZE];
	पूर्णांक first_inquiry_len, try_inquiry_len, next_inquiry_len;
	पूर्णांक response_len = 0;
	पूर्णांक pass, count, result;
	काष्ठा scsi_sense_hdr sshdr;

	*bflags = 0;

	/* Perक्रमm up to 3 passes.  The first pass uses a conservative
	 * transfer length of 36 unless sdev->inquiry_len specअगरies a
	 * dअगरferent value. */
	first_inquiry_len = sdev->inquiry_len ? sdev->inquiry_len : 36;
	try_inquiry_len = first_inquiry_len;
	pass = 1;

 next_pass:
	SCSI_LOG_SCAN_BUS(3, sdev_prपूर्णांकk(KERN_INFO, sdev,
				"scsi scan: INQUIRY pass %d length %d\n",
				pass, try_inquiry_len));

	/* Each pass माला_लो up to three chances to ignore Unit Attention */
	क्रम (count = 0; count < 3; ++count) अणु
		पूर्णांक resid;

		स_रखो(scsi_cmd, 0, 6);
		scsi_cmd[0] = INQUIRY;
		scsi_cmd[4] = (अचिन्हित अक्षर) try_inquiry_len;

		स_रखो(inq_result, 0, try_inquiry_len);

		result = scsi_execute_req(sdev,  scsi_cmd, DMA_FROM_DEVICE,
					  inq_result, try_inquiry_len, &sshdr,
					  HZ / 2 + HZ * scsi_inq_समयout, 3,
					  &resid);

		SCSI_LOG_SCAN_BUS(3, sdev_prपूर्णांकk(KERN_INFO, sdev,
				"scsi scan: INQUIRY %s with code 0x%x\n",
				result ? "failed" : "successful", result));

		अगर (result) अणु
			/*
			 * not-पढ़ोy to पढ़ोy transition [asc/ascq=0x28/0x0]
			 * or घातer-on, reset [asc/ascq=0x29/0x0], जारी.
			 * INQUIRY should not yield UNIT_ATTENTION
			 * but many buggy devices करो so anyway. 
			 */
			अगर (driver_byte(result) == DRIVER_SENSE &&
			    scsi_sense_valid(&sshdr)) अणु
				अगर ((sshdr.sense_key == UNIT_ATTENTION) &&
				    ((sshdr.asc == 0x28) ||
				     (sshdr.asc == 0x29)) &&
				    (sshdr.ascq == 0))
					जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * अगर nothing was transferred, we try
			 * again. It's a workaround क्रम some USB
			 * devices.
			 */
			अगर (resid == try_inquiry_len)
				जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (result == 0) अणु
		scsi_sanitize_inquiry_string(&inq_result[8], 8);
		scsi_sanitize_inquiry_string(&inq_result[16], 16);
		scsi_sanitize_inquiry_string(&inq_result[32], 4);

		response_len = inq_result[4] + 5;
		अगर (response_len > 255)
			response_len = first_inquiry_len;	/* sanity */

		/*
		 * Get any flags क्रम this device.
		 *
		 * XXX add a bflags to scsi_device, and replace the
		 * corresponding bit fields in scsi_device, so bflags
		 * need not be passed as an argument.
		 */
		*bflags = scsi_get_device_flags(sdev, &inq_result[8],
				&inq_result[16]);

		/* When the first pass succeeds we gain inक्रमmation about
		 * what larger transfer lengths might work. */
		अगर (pass == 1) अणु
			अगर (BLIST_INQUIRY_36 & *bflags)
				next_inquiry_len = 36;
			अन्यथा अगर (sdev->inquiry_len)
				next_inquiry_len = sdev->inquiry_len;
			अन्यथा
				next_inquiry_len = response_len;

			/* If more data is available perक्रमm the second pass */
			अगर (next_inquiry_len > try_inquiry_len) अणु
				try_inquiry_len = next_inquiry_len;
				pass = 2;
				जाओ next_pass;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (pass == 2) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "scsi scan: %d byte inquiry failed.  "
			    "Consider BLIST_INQUIRY_36 for this device\n",
			    try_inquiry_len);

		/* If this pass failed, the third pass goes back and transfers
		 * the same amount as we successfully got in the first pass. */
		try_inquiry_len = first_inquiry_len;
		pass = 3;
		जाओ next_pass;
	पूर्ण

	/* If the last transfer attempt got an error, assume the
	 * peripheral करोesn't exist or is dead. */
	अगर (result)
		वापस -EIO;

	/* Don't report any more data than the device says is valid */
	sdev->inquiry_len = min(try_inquiry_len, response_len);

	/*
	 * XXX Abort अगर the response length is less than 36? If less than
	 * 32, the lookup of the device flags (above) could be invalid,
	 * and it would be possible to take an incorrect action - we करो
	 * not want to hang because of a लघु INQUIRY. On the flip side,
	 * अगर the device is spun करोwn or becoming पढ़ोy (and so it gives a
	 * लघु INQUIRY), an पात here prevents any further use of the
	 * device, including spin up.
	 *
	 * On the whole, the best approach seems to be to assume the first
	 * 36 bytes are valid no matter what the device says.  That's
	 * better than copying < 36 bytes to the inquiry-result buffer
	 * and displaying garbage क्रम the Venकरोr, Product, or Revision
	 * strings.
	 */
	अगर (sdev->inquiry_len < 36) अणु
		अगर (!sdev->host->लघु_inquiry) अणु
			shost_prपूर्णांकk(KERN_INFO, sdev->host,
				    "scsi scan: INQUIRY result too short (%d),"
				    " using 36\n", sdev->inquiry_len);
			sdev->host->लघु_inquiry = 1;
		पूर्ण
		sdev->inquiry_len = 36;
	पूर्ण

	/*
	 * Related to the above issue:
	 *
	 * XXX Devices (disk or all?) should be sent a TEST UNIT READY,
	 * and अगर not पढ़ोy, sent a START_STOP to start (maybe spin up) and
	 * then send the INQUIRY again, since the INQUIRY can change after
	 * a device is initialized.
	 *
	 * Ideally, start a device अगर explicitly asked to करो so.  This
	 * assumes that a device is spun up on घातer on, spun करोwn on
	 * request, and then spun up on request.
	 */

	/*
	 * The scanning code needs to know the scsi_level, even अगर no
	 * device is attached at LUN 0 (SCSI_SCAN_TARGET_PRESENT) so
	 * non-zero LUNs can be scanned.
	 */
	sdev->scsi_level = inq_result[2] & 0x07;
	अगर (sdev->scsi_level >= 2 ||
	    (sdev->scsi_level == 1 && (inq_result[3] & 0x0f) == 1))
		sdev->scsi_level++;
	sdev->sdev_target->scsi_level = sdev->scsi_level;

	/*
	 * If SCSI-2 or lower, and अगर the transport requires it,
	 * store the LUN value in CDB[1].
	 */
	sdev->lun_in_cdb = 0;
	अगर (sdev->scsi_level <= SCSI_2 &&
	    sdev->scsi_level != SCSI_UNKNOWN &&
	    !sdev->host->no_scsi2_lun_in_cdb)
		sdev->lun_in_cdb = 1;

	वापस 0;
पूर्ण

/**
 * scsi_add_lun - allocate and fully initialze a scsi_device
 * @sdev:	holds inक्रमmation to be stored in the new scsi_device
 * @inq_result:	holds the result of a previous INQUIRY to the LUN
 * @bflags:	black/white list flag
 * @async:	1 अगर this device is being scanned asynchronously
 *
 * Description:
 *     Initialize the scsi_device @sdev.  Optionally set fields based
 *     on values in *@bflags.
 *
 * Return:
 *     SCSI_SCAN_NO_RESPONSE: could not allocate or setup a scsi_device
 *     SCSI_SCAN_LUN_PRESENT: a new scsi_device was allocated and initialized
 **/
अटल पूर्णांक scsi_add_lun(काष्ठा scsi_device *sdev, अचिन्हित अक्षर *inq_result,
		blist_flags_t *bflags, पूर्णांक async)
अणु
	पूर्णांक ret;

	/*
	 * XXX करो not save the inquiry, since it can change underneath us,
	 * save just venकरोr/model/rev.
	 *
	 * Rather than save it and have an ioctl that retrieves the saved
	 * value, have an ioctl that executes the same INQUIRY code used
	 * in scsi_probe_lun, let user level programs करोing INQUIRY
	 * scanning run at their own risk, or supply a user level program
	 * that can correctly scan.
	 */

	/*
	 * Copy at least 36 bytes of INQUIRY data, so that we करोn't
	 * dereference unallocated memory when accessing the Venकरोr,
	 * Product, and Revision strings.  Badly behaved devices may set
	 * the INQUIRY Additional Length byte to a small value, indicating
	 * these strings are invalid, but often they contain plausible data
	 * nonetheless.  It करोesn't matter अगर the device sent < 36 bytes
	 * total, since scsi_probe_lun() initializes inq_result with 0s.
	 */
	sdev->inquiry = kmemdup(inq_result,
				max_t(माप_प्रकार, sdev->inquiry_len, 36),
				GFP_KERNEL);
	अगर (sdev->inquiry == शून्य)
		वापस SCSI_SCAN_NO_RESPONSE;

	sdev->venकरोr = (अक्षर *) (sdev->inquiry + 8);
	sdev->model = (अक्षर *) (sdev->inquiry + 16);
	sdev->rev = (अक्षर *) (sdev->inquiry + 32);

	अगर (म_भेदन(sdev->venकरोr, "ATA     ", 8) == 0) अणु
		/*
		 * sata emulation layer device.  This is a hack to work around
		 * the SATL घातer management specअगरications which state that
		 * when the SATL detects the device has gone पूर्णांकo standby
		 * mode, it shall respond with NOT READY.
		 */
		sdev->allow_restart = 1;
	पूर्ण

	अगर (*bflags & BLIST_ISROM) अणु
		sdev->type = TYPE_ROM;
		sdev->removable = 1;
	पूर्ण अन्यथा अणु
		sdev->type = (inq_result[0] & 0x1f);
		sdev->removable = (inq_result[1] & 0x80) >> 7;

		/*
		 * some devices may respond with wrong type क्रम
		 * well-known logical units. Force well-known type
		 * to क्रमागतerate them correctly.
		 */
		अगर (scsi_is_wlun(sdev->lun) && sdev->type != TYPE_WLUN) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				"%s: correcting incorrect peripheral device type 0x%x for W-LUN 0x%16xhN\n",
				__func__, sdev->type, (अचिन्हित पूर्णांक)sdev->lun);
			sdev->type = TYPE_WLUN;
		पूर्ण

	पूर्ण

	अगर (sdev->type == TYPE_RBC || sdev->type == TYPE_ROM) अणु
		/* RBC and MMC devices can वापस SCSI-3 compliance and yet
		 * still not support REPORT LUNS, so make them act as
		 * BLIST_NOREPORTLUN unless BLIST_REPORTLUN2 is
		 * specअगरically set */
		अगर ((*bflags & BLIST_REPORTLUN2) == 0)
			*bflags |= BLIST_NOREPORTLUN;
	पूर्ण

	/*
	 * For a peripheral qualअगरier (PQ) value of 1 (001b), the SCSI
	 * spec says: The device server is capable of supporting the
	 * specअगरied peripheral device type on this logical unit. However,
	 * the physical device is not currently connected to this logical
	 * unit.
	 *
	 * The above is vague, as it implies that we could treat 001 and
	 * 011 the same. Stay compatible with previous code, and create a
	 * scsi_device क्रम a PQ of 1
	 *
	 * Don't set the device offline here; rather let the upper
	 * level drivers eval the PQ to decide whether they should
	 * attach. So हटाओ ((inq_result[0] >> 5) & 7) == 1 check.
	 */ 

	sdev->inq_periph_qual = (inq_result[0] >> 5) & 7;
	sdev->lockable = sdev->removable;
	sdev->soft_reset = (inq_result[7] & 1) && ((inq_result[3] & 7) == 2);

	अगर (sdev->scsi_level >= SCSI_3 ||
			(sdev->inquiry_len > 56 && inq_result[56] & 0x04))
		sdev->ppr = 1;
	अगर (inq_result[7] & 0x60)
		sdev->wdtr = 1;
	अगर (inq_result[7] & 0x10)
		sdev->sdtr = 1;

	sdev_prपूर्णांकk(KERN_NOTICE, sdev, "%s %.8s %.16s %.4s PQ: %d "
			"ANSI: %d%s\n", scsi_device_type(sdev->type),
			sdev->venकरोr, sdev->model, sdev->rev,
			sdev->inq_periph_qual, inq_result[2] & 0x07,
			(inq_result[3] & 0x0f) == 1 ? " CCS" : "");

	अगर ((sdev->scsi_level >= SCSI_2) && (inq_result[7] & 2) &&
	    !(*bflags & BLIST_NOTQ)) अणु
		sdev->tagged_supported = 1;
		sdev->simple_tags = 1;
	पूर्ण

	/*
	 * Some devices (Texel CD ROM drives) have handshaking problems
	 * when used with the Seagate controllers. borken is initialized
	 * to 1, and then set it to 0 here.
	 */
	अगर ((*bflags & BLIST_BORKEN) == 0)
		sdev->borken = 0;

	अगर (*bflags & BLIST_NO_ULD_ATTACH)
		sdev->no_uld_attach = 1;

	/*
	 * Apparently some really broken devices (contrary to the SCSI
	 * standards) need to be selected without निश्चितing ATN
	 */
	अगर (*bflags & BLIST_SELECT_NO_ATN)
		sdev->select_no_atn = 1;

	/*
	 * Maximum 512 sector transfer length
	 * broken RA4x00 Compaq Disk Array
	 */
	अगर (*bflags & BLIST_MAX_512)
		blk_queue_max_hw_sectors(sdev->request_queue, 512);
	/*
	 * Max 1024 sector transfer length क्रम tarमाला_लो that report incorrect
	 * max/optimal lengths and relied on the old block layer safe शेष
	 */
	अन्यथा अगर (*bflags & BLIST_MAX_1024)
		blk_queue_max_hw_sectors(sdev->request_queue, 1024);

	/*
	 * Some devices may not want to have a start command स्वतःmatically
	 * issued when a device is added.
	 */
	अगर (*bflags & BLIST_NOSTARTONADD)
		sdev->no_start_on_add = 1;

	अगर (*bflags & BLIST_SINGLELUN)
		scsi_target(sdev)->single_lun = 1;

	sdev->use_10_क्रम_rw = 1;

	/* some devices करोn't like REPORT SUPPORTED OPERATION CODES
	 * and will simply समयout causing sd_mod init to take a very
	 * very दीर्घ समय */
	अगर (*bflags & BLIST_NO_RSOC)
		sdev->no_report_opcodes = 1;

	/* set the device running here so that slave configure
	 * may करो I/O */
	mutex_lock(&sdev->state_mutex);
	ret = scsi_device_set_state(sdev, SDEV_RUNNING);
	अगर (ret)
		ret = scsi_device_set_state(sdev, SDEV_BLOCK);
	mutex_unlock(&sdev->state_mutex);

	अगर (ret) अणु
		sdev_prपूर्णांकk(KERN_ERR, sdev,
			    "in wrong state %s to complete scan\n",
			    scsi_device_state_name(sdev->sdev_state));
		वापस SCSI_SCAN_NO_RESPONSE;
	पूर्ण

	अगर (*bflags & BLIST_NOT_LOCKABLE)
		sdev->lockable = 0;

	अगर (*bflags & BLIST_RETRY_HWERROR)
		sdev->retry_hwerror = 1;

	अगर (*bflags & BLIST_NO_DIF)
		sdev->no_dअगर = 1;

	अगर (*bflags & BLIST_UNMAP_LIMIT_WS)
		sdev->unmap_limit_क्रम_ws = 1;

	sdev->eh_समयout = SCSI_DEFAULT_EH_TIMEOUT;

	अगर (*bflags & BLIST_TRY_VPD_PAGES)
		sdev->try_vpd_pages = 1;
	अन्यथा अगर (*bflags & BLIST_SKIP_VPD_PAGES)
		sdev->skip_vpd_pages = 1;

	transport_configure_device(&sdev->sdev_gendev);

	अगर (sdev->host->hostt->slave_configure) अणु
		ret = sdev->host->hostt->slave_configure(sdev);
		अगर (ret) अणु
			/*
			 * अगर LLDD reports slave not present, करोn't clutter
			 * console with alloc failure messages
			 */
			अगर (ret != -ENXIO) अणु
				sdev_prपूर्णांकk(KERN_ERR, sdev,
					"failed to configure device\n");
			पूर्ण
			वापस SCSI_SCAN_NO_RESPONSE;
		पूर्ण
	पूर्ण

	अगर (sdev->scsi_level >= SCSI_3)
		scsi_attach_vpd(sdev);

	sdev->max_queue_depth = sdev->queue_depth;
	WARN_ON_ONCE(sdev->max_queue_depth > sdev->budget_map.depth);
	sdev->sdev_bflags = *bflags;

	/*
	 * Ok, the device is now all set up, we can
	 * रेजिस्टर it and tell the rest of the kernel
	 * about it.
	 */
	अगर (!async && scsi_sysfs_add_sdev(sdev) != 0)
		वापस SCSI_SCAN_NO_RESPONSE;

	वापस SCSI_SCAN_LUN_PRESENT;
पूर्ण

#अगर_घोषित CONFIG_SCSI_LOGGING
/** 
 * scsi_inq_str - prपूर्णांक INQUIRY data from min to max index, strip trailing whitespace
 * @buf:   Output buffer with at least end-first+1 bytes of space
 * @inq:   Inquiry buffer (input)
 * @first: Offset of string पूर्णांकo inq
 * @end:   Index after last अक्षरacter in inq
 */
अटल अचिन्हित अक्षर *scsi_inq_str(अचिन्हित अक्षर *buf, अचिन्हित अक्षर *inq,
				   अचिन्हित first, अचिन्हित end)
अणु
	अचिन्हित term = 0, idx;

	क्रम (idx = 0; idx + first < end && idx + first < inq[4] + 5; idx++) अणु
		अगर (inq[idx+first] > ' ') अणु
			buf[idx] = inq[idx+first];
			term = idx+1;
		पूर्ण अन्यथा अणु
			buf[idx] = ' ';
		पूर्ण
	पूर्ण
	buf[term] = 0;
	वापस buf;
पूर्ण
#पूर्ण_अगर

/**
 * scsi_probe_and_add_lun - probe a LUN, अगर a LUN is found add it
 * @starget:	poपूर्णांकer to target device काष्ठाure
 * @lun:	LUN of target device
 * @bflagsp:	store bflags here अगर not शून्य
 * @sdevp:	probe the LUN corresponding to this scsi_device
 * @rescan:     अगर not equal to SCSI_SCAN_INITIAL skip some code only
 *              needed on first scan
 * @hostdata:	passed to scsi_alloc_sdev()
 *
 * Description:
 *     Call scsi_probe_lun, अगर a LUN with an attached device is found,
 *     allocate and set it up by calling scsi_add_lun.
 *
 * Return:
 *
 *   - SCSI_SCAN_NO_RESPONSE: could not allocate or setup a scsi_device
 *   - SCSI_SCAN_TARGET_PRESENT: target responded, but no device is
 *         attached at the LUN
 *   - SCSI_SCAN_LUN_PRESENT: a new scsi_device was allocated and initialized
 **/
अटल पूर्णांक scsi_probe_and_add_lun(काष्ठा scsi_target *starget,
				  u64 lun, blist_flags_t *bflagsp,
				  काष्ठा scsi_device **sdevp,
				  क्रमागत scsi_scan_mode rescan,
				  व्योम *hostdata)
अणु
	काष्ठा scsi_device *sdev;
	अचिन्हित अक्षर *result;
	blist_flags_t bflags;
	पूर्णांक res = SCSI_SCAN_NO_RESPONSE, result_len = 256;
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);

	/*
	 * The rescan flag is used as an optimization, the first scan of a
	 * host adapter calls पूर्णांकo here with rescan == 0.
	 */
	sdev = scsi_device_lookup_by_target(starget, lun);
	अगर (sdev) अणु
		अगर (rescan != SCSI_SCAN_INITIAL || !scsi_device_created(sdev)) अणु
			SCSI_LOG_SCAN_BUS(3, sdev_prपूर्णांकk(KERN_INFO, sdev,
				"scsi scan: device exists on %s\n",
				dev_name(&sdev->sdev_gendev)));
			अगर (sdevp)
				*sdevp = sdev;
			अन्यथा
				scsi_device_put(sdev);

			अगर (bflagsp)
				*bflagsp = scsi_get_device_flags(sdev,
								 sdev->venकरोr,
								 sdev->model);
			वापस SCSI_SCAN_LUN_PRESENT;
		पूर्ण
		scsi_device_put(sdev);
	पूर्ण अन्यथा
		sdev = scsi_alloc_sdev(starget, lun, hostdata);
	अगर (!sdev)
		जाओ out;

	result = kदो_स्मृति(result_len, GFP_KERNEL);
	अगर (!result)
		जाओ out_मुक्त_sdev;

	अगर (scsi_probe_lun(sdev, result, result_len, &bflags))
		जाओ out_मुक्त_result;

	अगर (bflagsp)
		*bflagsp = bflags;
	/*
	 * result contains valid SCSI INQUIRY data.
	 */
	अगर ((result[0] >> 5) == 3) अणु
		/*
		 * For a Peripheral qualअगरier 3 (011b), the SCSI
		 * spec says: The device server is not capable of
		 * supporting a physical device on this logical
		 * unit.
		 *
		 * For disks, this implies that there is no
		 * logical disk configured at sdev->lun, but there
		 * is a target id responding.
		 */
		SCSI_LOG_SCAN_BUS(2, sdev_prपूर्णांकk(KERN_INFO, sdev, "scsi scan:"
				   " peripheral qualifier of 3, device not"
				   " added\n"))
		अगर (lun == 0) अणु
			SCSI_LOG_SCAN_BUS(1, अणु
				अचिन्हित अक्षर vend[9];
				अचिन्हित अक्षर mod[17];

				sdev_prपूर्णांकk(KERN_INFO, sdev,
					"scsi scan: consider passing scsi_mod."
					"dev_flags=%s:%s:0x240 or 0x1000240\n",
					scsi_inq_str(vend, result, 8, 16),
					scsi_inq_str(mod, result, 16, 32));
			पूर्ण);

		पूर्ण

		res = SCSI_SCAN_TARGET_PRESENT;
		जाओ out_मुक्त_result;
	पूर्ण

	/*
	 * Some tarमाला_लो may set slight variations of PQ and PDT to संकेत
	 * that no LUN is present, so करोn't add sdev in these हालs.
	 * Two specअगरic examples are:
	 * 1) NetApp tarमाला_लो: वापस PQ=1, PDT=0x1f
	 * 2) IBM/2145 tarमाला_लो: वापस PQ=1, PDT=0
	 * 3) USB UFI: वापसs PDT=0x1f, with the PQ bits being "reserved"
	 *    in the UFI 1.0 spec (we cannot rely on reserved bits).
	 *
	 * References:
	 * 1) SCSI SPC-3, pp. 145-146
	 * PQ=1: "A peripheral device having the specअगरied peripheral
	 * device type is not connected to this logical unit. However, the
	 * device server is capable of supporting the specअगरied peripheral
	 * device type on this logical unit."
	 * PDT=0x1f: "Unknown or no device type"
	 * 2) USB UFI 1.0, p. 20
	 * PDT=00h Direct-access device (floppy)
	 * PDT=1Fh none (no FDD connected to the requested logical unit)
	 */
	अगर (((result[0] >> 5) == 1 ||
	    (starget->pdt_1f_क्रम_no_lun && (result[0] & 0x1f) == 0x1f)) &&
	    !scsi_is_wlun(lun)) अणु
		SCSI_LOG_SCAN_BUS(3, sdev_prपूर्णांकk(KERN_INFO, sdev,
					"scsi scan: peripheral device type"
					" of 31, no device added\n"));
		res = SCSI_SCAN_TARGET_PRESENT;
		जाओ out_मुक्त_result;
	पूर्ण

	res = scsi_add_lun(sdev, result, &bflags, shost->async_scan);
	अगर (res == SCSI_SCAN_LUN_PRESENT) अणु
		अगर (bflags & BLIST_KEY) अणु
			sdev->lockable = 0;
			scsi_unlock_floptical(sdev, result);
		पूर्ण
	पूर्ण

 out_मुक्त_result:
	kमुक्त(result);
 out_मुक्त_sdev:
	अगर (res == SCSI_SCAN_LUN_PRESENT) अणु
		अगर (sdevp) अणु
			अगर (scsi_device_get(sdev) == 0) अणु
				*sdevp = sdev;
			पूर्ण अन्यथा अणु
				__scsi_हटाओ_device(sdev);
				res = SCSI_SCAN_NO_RESPONSE;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		__scsi_हटाओ_device(sdev);
 out:
	वापस res;
पूर्ण

/**
 * scsi_sequential_lun_scan - sequentially scan a SCSI target
 * @starget:	poपूर्णांकer to target काष्ठाure to scan
 * @bflags:	black/white list flag क्रम LUN 0
 * @scsi_level: Which version of the standard करोes this device adhere to
 * @rescan:     passed to scsi_probe_add_lun()
 *
 * Description:
 *     Generally, scan from LUN 1 (LUN 0 is assumed to alपढ़ोy have been
 *     scanned) to some maximum lun until a LUN is found with no device
 *     attached. Use the bflags to figure out any oddities.
 *
 *     Modअगरies sdevscan->lun.
 **/
अटल व्योम scsi_sequential_lun_scan(काष्ठा scsi_target *starget,
				     blist_flags_t bflags, पूर्णांक scsi_level,
				     क्रमागत scsi_scan_mode rescan)
अणु
	uपूर्णांक max_dev_lun;
	u64 sparse_lun, lun;
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);

	SCSI_LOG_SCAN_BUS(3, starget_prपूर्णांकk(KERN_INFO, starget,
		"scsi scan: Sequential scan\n"));

	max_dev_lun = min(max_scsi_luns, shost->max_lun);
	/*
	 * If this device is known to support sparse multiple units,
	 * override the other settings, and scan all of them. Normally,
	 * SCSI-3 devices should be scanned via the REPORT LUNS.
	 */
	अगर (bflags & BLIST_SPARSELUN) अणु
		max_dev_lun = shost->max_lun;
		sparse_lun = 1;
	पूर्ण अन्यथा
		sparse_lun = 0;

	/*
	 * If less than SCSI_1_CCS, and no special lun scanning, stop
	 * scanning; this matches 2.4 behaviour, but could just be a bug
	 * (to जारी scanning a SCSI_1_CCS device).
	 *
	 * This test is broken.  We might not have any device on lun0 क्रम
	 * a sparselun device, and अगर that's the हाल then how would we
	 * know the real scsi_level, eh?  It might make sense to just not
	 * scan any SCSI_1 device क्रम non-0 luns, but that check would best
	 * go पूर्णांकo scsi_alloc_sdev() and just have it वापस null when asked
	 * to alloc an sdev क्रम lun > 0 on an alपढ़ोy found SCSI_1 device.
	 *
	अगर ((sdevscan->scsi_level < SCSI_1_CCS) &&
	    ((bflags & (BLIST_FORCELUN | BLIST_SPARSELUN | BLIST_MAX5LUN))
	     == 0))
		वापस;
	 */
	/*
	 * If this device is known to support multiple units, override
	 * the other settings, and scan all of them.
	 */
	अगर (bflags & BLIST_FORCELUN)
		max_dev_lun = shost->max_lun;
	/*
	 * REGAL CDC-4X: aव्योम hang after LUN 4
	 */
	अगर (bflags & BLIST_MAX5LUN)
		max_dev_lun = min(5U, max_dev_lun);
	/*
	 * Do not scan SCSI-2 or lower device past LUN 7, unless
	 * BLIST_LARGELUN.
	 */
	अगर (scsi_level < SCSI_3 && !(bflags & BLIST_LARGELUN))
		max_dev_lun = min(8U, max_dev_lun);
	अन्यथा
		max_dev_lun = min(256U, max_dev_lun);

	/*
	 * We have alपढ़ोy scanned LUN 0, so start at LUN 1. Keep scanning
	 * until we reach the max, or no LUN is found and we are not
	 * sparse_lun.
	 */
	क्रम (lun = 1; lun < max_dev_lun; ++lun)
		अगर ((scsi_probe_and_add_lun(starget, lun, शून्य, शून्य, rescan,
					    शून्य) != SCSI_SCAN_LUN_PRESENT) &&
		    !sparse_lun)
			वापस;
पूर्ण

/**
 * scsi_report_lun_scan - Scan using SCSI REPORT LUN results
 * @starget: which target
 * @bflags: Zero or a mix of BLIST_NOLUN, BLIST_REPORTLUN2, or BLIST_NOREPORTLUN
 * @rescan: nonzero अगर we can skip code only needed on first scan
 *
 * Description:
 *   Fast scanning क्रम modern (SCSI-3) devices by sending a REPORT LUN command.
 *   Scan the resulting list of LUNs by calling scsi_probe_and_add_lun.
 *
 *   If BLINK_REPORTLUN2 is set, scan a target that supports more than 8
 *   LUNs even अगर it's older than SCSI-3.
 *   If BLIST_NOREPORTLUN is set, वापस 1 always.
 *   If BLIST_NOLUN is set, वापस 0 always.
 *   If starget->no_report_luns is set, वापस 1 always.
 *
 * Return:
 *     0: scan completed (or no memory, so further scanning is futile)
 *     1: could not scan with REPORT LUN
 **/
अटल पूर्णांक scsi_report_lun_scan(काष्ठा scsi_target *starget, blist_flags_t bflags,
				क्रमागत scsi_scan_mode rescan)
अणु
	अचिन्हित अक्षर scsi_cmd[MAX_COMMAND_SIZE];
	अचिन्हित पूर्णांक length;
	u64 lun;
	अचिन्हित पूर्णांक num_luns;
	अचिन्हित पूर्णांक retries;
	पूर्णांक result;
	काष्ठा scsi_lun *lunp, *lun_data;
	काष्ठा scsi_sense_hdr sshdr;
	काष्ठा scsi_device *sdev;
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	पूर्णांक ret = 0;

	/*
	 * Only support SCSI-3 and up devices अगर BLIST_NOREPORTLUN is not set.
	 * Also allow SCSI-2 अगर BLIST_REPORTLUN2 is set and host adapter करोes
	 * support more than 8 LUNs.
	 * Don't attempt if the target doesn't support REPORT LUNS.
	 */
	अगर (bflags & BLIST_NOREPORTLUN)
		वापस 1;
	अगर (starget->scsi_level < SCSI_2 &&
	    starget->scsi_level != SCSI_UNKNOWN)
		वापस 1;
	अगर (starget->scsi_level < SCSI_3 &&
	    (!(bflags & BLIST_REPORTLUN2) || shost->max_lun <= 8))
		वापस 1;
	अगर (bflags & BLIST_NOLUN)
		वापस 0;
	अगर (starget->no_report_luns)
		वापस 1;

	अगर (!(sdev = scsi_device_lookup_by_target(starget, 0))) अणु
		sdev = scsi_alloc_sdev(starget, 0, शून्य);
		अगर (!sdev)
			वापस 0;
		अगर (scsi_device_get(sdev)) अणु
			__scsi_हटाओ_device(sdev);
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Allocate enough to hold the header (the same size as one scsi_lun)
	 * plus the number of luns we are requesting.  511 was the शेष
	 * value of the now हटाओd max_report_luns parameter.
	 */
	length = (511 + 1) * माप(काष्ठा scsi_lun);
retry:
	lun_data = kदो_स्मृति(length, GFP_KERNEL);
	अगर (!lun_data) अणु
		prपूर्णांकk(ALLOC_FAILURE_MSG, __func__);
		जाओ out;
	पूर्ण

	scsi_cmd[0] = REPORT_LUNS;

	/*
	 * bytes 1 - 5: reserved, set to zero.
	 */
	स_रखो(&scsi_cmd[1], 0, 5);

	/*
	 * bytes 6 - 9: length of the command.
	 */
	put_unaligned_be32(length, &scsi_cmd[6]);

	scsi_cmd[10] = 0;	/* reserved */
	scsi_cmd[11] = 0;	/* control */

	/*
	 * We can get a UNIT ATTENTION, क्रम example a घातer on/reset, so
	 * retry a few बार (like sd.c करोes क्रम TEST UNIT READY).
	 * Experience shows some combinations of adapter/devices get at
	 * least two घातer on/resets.
	 *
	 * Illegal requests (क्रम devices that करो not support REPORT LUNS)
	 * should come through as a check condition, and will not generate
	 * a retry.
	 */
	क्रम (retries = 0; retries < 3; retries++) अणु
		SCSI_LOG_SCAN_BUS(3, sdev_prपूर्णांकk (KERN_INFO, sdev,
				"scsi scan: Sending REPORT LUNS to (try %d)\n",
				retries));

		result = scsi_execute_req(sdev, scsi_cmd, DMA_FROM_DEVICE,
					  lun_data, length, &sshdr,
					  SCSI_REPORT_LUNS_TIMEOUT, 3, शून्य);

		SCSI_LOG_SCAN_BUS(3, sdev_prपूर्णांकk (KERN_INFO, sdev,
				"scsi scan: REPORT LUNS"
				" %s (try %d) result 0x%x\n",
				result ?  "failed" : "successful",
				retries, result));
		अगर (result == 0)
			अवरोध;
		अन्यथा अगर (scsi_sense_valid(&sshdr)) अणु
			अगर (sshdr.sense_key != UNIT_ATTENTION)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (result) अणु
		/*
		 * The device probably करोes not support a REPORT LUN command
		 */
		ret = 1;
		जाओ out_err;
	पूर्ण

	/*
	 * Get the length from the first four bytes of lun_data.
	 */
	अगर (get_unaligned_be32(lun_data->scsi_lun) +
	    माप(काष्ठा scsi_lun) > length) अणु
		length = get_unaligned_be32(lun_data->scsi_lun) +
			 माप(काष्ठा scsi_lun);
		kमुक्त(lun_data);
		जाओ retry;
	पूर्ण
	length = get_unaligned_be32(lun_data->scsi_lun);

	num_luns = (length / माप(काष्ठा scsi_lun));

	SCSI_LOG_SCAN_BUS(3, sdev_prपूर्णांकk (KERN_INFO, sdev,
		"scsi scan: REPORT LUN scan\n"));

	/*
	 * Scan the luns in lun_data. The entry at offset 0 is really
	 * the header, so start at 1 and go up to and including num_luns.
	 */
	क्रम (lunp = &lun_data[1]; lunp <= &lun_data[num_luns]; lunp++) अणु
		lun = scsilun_to_पूर्णांक(lunp);

		अगर (lun > sdev->host->max_lun) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "lun%llu has a LUN larger than"
				    " allowed by the host adapter\n", lun);
		पूर्ण अन्यथा अणु
			पूर्णांक res;

			res = scsi_probe_and_add_lun(starget,
				lun, शून्य, शून्य, rescan, शून्य);
			अगर (res == SCSI_SCAN_NO_RESPONSE) अणु
				/*
				 * Got some results, but now none, पात.
				 */
				sdev_prपूर्णांकk(KERN_ERR, sdev,
					"Unexpected response"
					" from lun %llu while scanning, scan"
					" aborted\n", (अचिन्हित दीर्घ दीर्घ)lun);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

 out_err:
	kमुक्त(lun_data);
 out:
	अगर (scsi_device_created(sdev))
		/*
		 * the sdev we used didn't appear in the report luns scan
		 */
		__scsi_हटाओ_device(sdev);
	scsi_device_put(sdev);
	वापस ret;
पूर्ण

काष्ठा scsi_device *__scsi_add_device(काष्ठा Scsi_Host *shost, uपूर्णांक channel,
				      uपूर्णांक id, u64 lun, व्योम *hostdata)
अणु
	काष्ठा scsi_device *sdev = ERR_PTR(-ENODEV);
	काष्ठा device *parent = &shost->shost_gendev;
	काष्ठा scsi_target *starget;

	अगर (म_भेदन(scsi_scan_type, "none", 4) == 0)
		वापस ERR_PTR(-ENODEV);

	starget = scsi_alloc_target(parent, channel, id);
	अगर (!starget)
		वापस ERR_PTR(-ENOMEM);
	scsi_स्वतःpm_get_target(starget);

	mutex_lock(&shost->scan_mutex);
	अगर (!shost->async_scan)
		scsi_complete_async_scans();

	अगर (scsi_host_scan_allowed(shost) && scsi_स्वतःpm_get_host(shost) == 0) अणु
		scsi_probe_and_add_lun(starget, lun, शून्य, &sdev, 1, hostdata);
		scsi_स्वतःpm_put_host(shost);
	पूर्ण
	mutex_unlock(&shost->scan_mutex);
	scsi_स्वतःpm_put_target(starget);
	/*
	 * paired with scsi_alloc_target().  Target will be destroyed unless
	 * scsi_probe_and_add_lun made an underlying device visible
	 */
	scsi_target_reap(starget);
	put_device(&starget->dev);

	वापस sdev;
पूर्ण
EXPORT_SYMBOL(__scsi_add_device);

पूर्णांक scsi_add_device(काष्ठा Scsi_Host *host, uपूर्णांक channel,
		    uपूर्णांक target, u64 lun)
अणु
	काष्ठा scsi_device *sdev = 
		__scsi_add_device(host, channel, target, lun, शून्य);
	अगर (IS_ERR(sdev))
		वापस PTR_ERR(sdev);

	scsi_device_put(sdev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_add_device);

व्योम scsi_rescan_device(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	device_lock(dev);

	scsi_attach_vpd(sdev);

	अगर (sdev->handler && sdev->handler->rescan)
		sdev->handler->rescan(sdev);

	अगर (dev->driver && try_module_get(dev->driver->owner)) अणु
		काष्ठा scsi_driver *drv = to_scsi_driver(dev->driver);

		अगर (drv->rescan)
			drv->rescan(dev);
		module_put(dev->driver->owner);
	पूर्ण
	device_unlock(dev);
पूर्ण
EXPORT_SYMBOL(scsi_rescan_device);

अटल व्योम __scsi_scan_target(काष्ठा device *parent, अचिन्हित पूर्णांक channel,
		अचिन्हित पूर्णांक id, u64 lun, क्रमागत scsi_scan_mode rescan)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(parent);
	blist_flags_t bflags = 0;
	पूर्णांक res;
	काष्ठा scsi_target *starget;

	अगर (shost->this_id == id)
		/*
		 * Don't scan the host adapter
		 */
		वापस;

	starget = scsi_alloc_target(parent, channel, id);
	अगर (!starget)
		वापस;
	scsi_स्वतःpm_get_target(starget);

	अगर (lun != SCAN_WILD_CARD) अणु
		/*
		 * Scan क्रम a specअगरic host/chan/id/lun.
		 */
		scsi_probe_and_add_lun(starget, lun, शून्य, शून्य, rescan, शून्य);
		जाओ out_reap;
	पूर्ण

	/*
	 * Scan LUN 0, अगर there is some response, scan further. Ideally, we
	 * would not configure LUN 0 until all LUNs are scanned.
	 */
	res = scsi_probe_and_add_lun(starget, 0, &bflags, शून्य, rescan, शून्य);
	अगर (res == SCSI_SCAN_LUN_PRESENT || res == SCSI_SCAN_TARGET_PRESENT) अणु
		अगर (scsi_report_lun_scan(starget, bflags, rescan) != 0)
			/*
			 * The REPORT LUN did not scan the target,
			 * करो a sequential scan.
			 */
			scsi_sequential_lun_scan(starget, bflags,
						 starget->scsi_level, rescan);
	पूर्ण

 out_reap:
	scsi_स्वतःpm_put_target(starget);
	/*
	 * paired with scsi_alloc_target(): determine अगर the target has
	 * any children at all and अगर not, nuke it
	 */
	scsi_target_reap(starget);

	put_device(&starget->dev);
पूर्ण

/**
 * scsi_scan_target - scan a target id, possibly including all LUNs on the target.
 * @parent:	host to scan
 * @channel:	channel to scan
 * @id:		target id to scan
 * @lun:	Specअगरic LUN to scan or SCAN_WILD_CARD
 * @rescan:	passed to LUN scanning routines; SCSI_SCAN_INITIAL क्रम
 *              no rescan, SCSI_SCAN_RESCAN to rescan existing LUNs,
 *              and SCSI_SCAN_MANUAL to क्रमce scanning even अगर
 *              'scan=manual' is set.
 *
 * Description:
 *     Scan the target id on @parent, @channel, and @id. Scan at least LUN 0,
 *     and possibly all LUNs on the target id.
 *
 *     First try a REPORT LUN scan, अगर that करोes not scan the target, करो a
 *     sequential scan of LUNs on the target id.
 **/
व्योम scsi_scan_target(काष्ठा device *parent, अचिन्हित पूर्णांक channel,
		      अचिन्हित पूर्णांक id, u64 lun, क्रमागत scsi_scan_mode rescan)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(parent);

	अगर (म_भेदन(scsi_scan_type, "none", 4) == 0)
		वापस;

	अगर (rescan != SCSI_SCAN_MANUAL &&
	    म_भेदन(scsi_scan_type, "manual", 6) == 0)
		वापस;

	mutex_lock(&shost->scan_mutex);
	अगर (!shost->async_scan)
		scsi_complete_async_scans();

	अगर (scsi_host_scan_allowed(shost) && scsi_स्वतःpm_get_host(shost) == 0) अणु
		__scsi_scan_target(parent, channel, id, lun, rescan);
		scsi_स्वतःpm_put_host(shost);
	पूर्ण
	mutex_unlock(&shost->scan_mutex);
पूर्ण
EXPORT_SYMBOL(scsi_scan_target);

अटल व्योम scsi_scan_channel(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक channel,
			      अचिन्हित पूर्णांक id, u64 lun,
			      क्रमागत scsi_scan_mode rescan)
अणु
	uपूर्णांक order_id;

	अगर (id == SCAN_WILD_CARD)
		क्रम (id = 0; id < shost->max_id; ++id) अणु
			/*
			 * XXX adapter drivers when possible (FCP, iSCSI)
			 * could modअगरy max_id to match the current max,
			 * not the असलolute max.
			 *
			 * XXX add a shost id iterator, so क्रम example,
			 * the FC ID can be the same as a target id
			 * without a huge overhead of sparse id's.
			 */
			अगर (shost->reverse_ordering)
				/*
				 * Scan from high to low id.
				 */
				order_id = shost->max_id - id - 1;
			अन्यथा
				order_id = id;
			__scsi_scan_target(&shost->shost_gendev, channel,
					order_id, lun, rescan);
		पूर्ण
	अन्यथा
		__scsi_scan_target(&shost->shost_gendev, channel,
				id, lun, rescan);
पूर्ण

पूर्णांक scsi_scan_host_selected(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक channel,
			    अचिन्हित पूर्णांक id, u64 lun,
			    क्रमागत scsi_scan_mode rescan)
अणु
	SCSI_LOG_SCAN_BUS(3, shost_prपूर्णांकk (KERN_INFO, shost,
		"%s: <%u:%u:%llu>\n",
		__func__, channel, id, lun));

	अगर (((channel != SCAN_WILD_CARD) && (channel > shost->max_channel)) ||
	    ((id != SCAN_WILD_CARD) && (id >= shost->max_id)) ||
	    ((lun != SCAN_WILD_CARD) && (lun >= shost->max_lun)))
		वापस -EINVAL;

	mutex_lock(&shost->scan_mutex);
	अगर (!shost->async_scan)
		scsi_complete_async_scans();

	अगर (scsi_host_scan_allowed(shost) && scsi_स्वतःpm_get_host(shost) == 0) अणु
		अगर (channel == SCAN_WILD_CARD)
			क्रम (channel = 0; channel <= shost->max_channel;
			     channel++)
				scsi_scan_channel(shost, channel, id, lun,
						  rescan);
		अन्यथा
			scsi_scan_channel(shost, channel, id, lun, rescan);
		scsi_स्वतःpm_put_host(shost);
	पूर्ण
	mutex_unlock(&shost->scan_mutex);

	वापस 0;
पूर्ण

अटल व्योम scsi_sysfs_add_devices(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_device *sdev;
	shost_क्रम_each_device(sdev, shost) अणु
		/* target हटाओd beक्रमe the device could be added */
		अगर (sdev->sdev_state == SDEV_DEL)
			जारी;
		/* If device is alपढ़ोy visible, skip adding it to sysfs */
		अगर (sdev->is_visible)
			जारी;
		अगर (!scsi_host_scan_allowed(shost) ||
		    scsi_sysfs_add_sdev(sdev) != 0)
			__scsi_हटाओ_device(sdev);
	पूर्ण
पूर्ण

/**
 * scsi_prep_async_scan - prepare क्रम an async scan
 * @shost: the host which will be scanned
 * Returns: a cookie to be passed to scsi_finish_async_scan()
 *
 * Tells the midlayer this host is going to करो an asynchronous scan.
 * It reserves the host's position in the scanning list and ensures
 * that other asynchronous scans started after this one won't affect the
 * ordering of the discovered devices.
 */
अटल काष्ठा async_scan_data *scsi_prep_async_scan(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा async_scan_data *data = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (म_भेदन(scsi_scan_type, "sync", 4) == 0)
		वापस शून्य;

	mutex_lock(&shost->scan_mutex);
	अगर (shost->async_scan) अणु
		shost_prपूर्णांकk(KERN_DEBUG, shost, "%s called twice\n", __func__);
		जाओ err;
	पूर्ण

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ err;
	data->shost = scsi_host_get(shost);
	अगर (!data->shost)
		जाओ err;
	init_completion(&data->prev_finished);

	spin_lock_irqsave(shost->host_lock, flags);
	shost->async_scan = 1;
	spin_unlock_irqrestore(shost->host_lock, flags);
	mutex_unlock(&shost->scan_mutex);

	spin_lock(&async_scan_lock);
	अगर (list_empty(&scanning_hosts))
		complete(&data->prev_finished);
	list_add_tail(&data->list, &scanning_hosts);
	spin_unlock(&async_scan_lock);

	वापस data;

 err:
	mutex_unlock(&shost->scan_mutex);
	kमुक्त(data);
	वापस शून्य;
पूर्ण

/**
 * scsi_finish_async_scan - asynchronous scan has finished
 * @data: cookie वापसed from earlier call to scsi_prep_async_scan()
 *
 * All the devices currently attached to this host have been found.
 * This function announces all the devices it has found to the rest
 * of the प्रणाली.
 */
अटल व्योम scsi_finish_async_scan(काष्ठा async_scan_data *data)
अणु
	काष्ठा Scsi_Host *shost;
	अचिन्हित दीर्घ flags;

	अगर (!data)
		वापस;

	shost = data->shost;

	mutex_lock(&shost->scan_mutex);

	अगर (!shost->async_scan) अणु
		shost_prपूर्णांकk(KERN_INFO, shost, "%s called twice\n", __func__);
		dump_stack();
		mutex_unlock(&shost->scan_mutex);
		वापस;
	पूर्ण

	रुको_क्रम_completion(&data->prev_finished);

	scsi_sysfs_add_devices(shost);

	spin_lock_irqsave(shost->host_lock, flags);
	shost->async_scan = 0;
	spin_unlock_irqrestore(shost->host_lock, flags);

	mutex_unlock(&shost->scan_mutex);

	spin_lock(&async_scan_lock);
	list_del(&data->list);
	अगर (!list_empty(&scanning_hosts)) अणु
		काष्ठा async_scan_data *next = list_entry(scanning_hosts.next,
				काष्ठा async_scan_data, list);
		complete(&next->prev_finished);
	पूर्ण
	spin_unlock(&async_scan_lock);

	scsi_स्वतःpm_put_host(shost);
	scsi_host_put(shost);
	kमुक्त(data);
पूर्ण

अटल व्योम करो_scsi_scan_host(काष्ठा Scsi_Host *shost)
अणु
	अगर (shost->hostt->scan_finished) अणु
		अचिन्हित दीर्घ start = jअगरfies;
		अगर (shost->hostt->scan_start)
			shost->hostt->scan_start(shost);

		जबतक (!shost->hostt->scan_finished(shost, jअगरfies - start))
			msleep(10);
	पूर्ण अन्यथा अणु
		scsi_scan_host_selected(shost, SCAN_WILD_CARD, SCAN_WILD_CARD,
				SCAN_WILD_CARD, 0);
	पूर्ण
पूर्ण

अटल व्योम करो_scan_async(व्योम *_data, async_cookie_t c)
अणु
	काष्ठा async_scan_data *data = _data;
	काष्ठा Scsi_Host *shost = data->shost;

	करो_scsi_scan_host(shost);
	scsi_finish_async_scan(data);
पूर्ण

/**
 * scsi_scan_host - scan the given adapter
 * @shost:	adapter to scan
 **/
व्योम scsi_scan_host(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा async_scan_data *data;

	अगर (म_भेदन(scsi_scan_type, "none", 4) == 0 ||
	    म_भेदन(scsi_scan_type, "manual", 6) == 0)
		वापस;
	अगर (scsi_स्वतःpm_get_host(shost) < 0)
		वापस;

	data = scsi_prep_async_scan(shost);
	अगर (!data) अणु
		करो_scsi_scan_host(shost);
		scsi_स्वतःpm_put_host(shost);
		वापस;
	पूर्ण

	/* रेजिस्टर with the async subप्रणाली so रुको_क्रम_device_probe()
	 * will flush this work
	 */
	async_schedule(करो_scan_async, data);

	/* scsi_स्वतःpm_put_host(shost) is called in scsi_finish_async_scan() */
पूर्ण
EXPORT_SYMBOL(scsi_scan_host);

व्योम scsi_क्रमget_host(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ flags;

 restart:
	spin_lock_irqsave(shost->host_lock, flags);
	list_क्रम_each_entry(sdev, &shost->__devices, siblings) अणु
		अगर (sdev->sdev_state == SDEV_DEL)
			जारी;
		spin_unlock_irqrestore(shost->host_lock, flags);
		__scsi_हटाओ_device(sdev);
		जाओ restart;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * scsi_get_host_dev - Create a scsi_device that poपूर्णांकs to the host adapter itself
 * @shost: Host that needs a scsi_device
 *
 * Lock status: None assumed.
 *
 * Returns:     The scsi_device or शून्य
 *
 * Notes:
 *	Attach a single scsi_device to the Scsi_Host - this should
 *	be made to look like a "pseudo-device" that poपूर्णांकs to the
 *	HA itself.
 *
 *	Note - this device is not accessible from any high-level
 *	drivers (including generics), which is probably not
 *	optimal.  We can add hooks later to attach.
 */
काष्ठा scsi_device *scsi_get_host_dev(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_device *sdev = शून्य;
	काष्ठा scsi_target *starget;

	mutex_lock(&shost->scan_mutex);
	अगर (!scsi_host_scan_allowed(shost))
		जाओ out;
	starget = scsi_alloc_target(&shost->shost_gendev, 0, shost->this_id);
	अगर (!starget)
		जाओ out;

	sdev = scsi_alloc_sdev(starget, 0, शून्य);
	अगर (sdev)
		sdev->borken = 0;
	अन्यथा
		scsi_target_reap(starget);
	put_device(&starget->dev);
 out:
	mutex_unlock(&shost->scan_mutex);
	वापस sdev;
पूर्ण
EXPORT_SYMBOL(scsi_get_host_dev);

/**
 * scsi_मुक्त_host_dev - Free a scsi_device that poपूर्णांकs to the host adapter itself
 * @sdev: Host device to be मुक्तd
 *
 * Lock status: None assumed.
 *
 * Returns:     Nothing
 */
व्योम scsi_मुक्त_host_dev(काष्ठा scsi_device *sdev)
अणु
	BUG_ON(sdev->id != sdev->host->this_id);

	__scsi_हटाओ_device(sdev);
पूर्ण
EXPORT_SYMBOL(scsi_मुक्त_host_dev);

