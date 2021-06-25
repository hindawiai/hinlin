<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    basic function of the tape device driver
 *
 *  S390 and zSeries version
 *    Copyright IBM Corp. 2001, 2009
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *		 Michael Holzheu <holzheu@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 *		 Stefan Bader <shbader@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "tape"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>	     // क्रम kernel parameters
#समावेश <linux/kmod.h>	     // क्रम requesting modules
#समावेश <linux/spinlock.h>  // क्रम locks
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/types.h>	     // क्रम variable types

#घोषणा TAPE_DBF_AREA	tape_core_dbf

#समावेश "tape.h"
#समावेश "tape_std.h"

#घोषणा LONG_BUSY_TIMEOUT 180 /* seconds */

अटल व्योम __tape_करो_irq (काष्ठा ccw_device *, अचिन्हित दीर्घ, काष्ठा irb *);
अटल व्योम tape_delayed_next_request(काष्ठा work_काष्ठा *);
अटल व्योम tape_दीर्घ_busy_समयout(काष्ठा समयr_list *t);

/*
 * One list to contain all tape devices of all disciplines, so
 * we can assign the devices to minor numbers of the same major
 * The list is रक्षित by the rwlock
 */
अटल LIST_HEAD(tape_device_list);
अटल DEFINE_RWLOCK(tape_device_lock);

/*
 * Poपूर्णांकer to debug area.
 */
debug_info_t *TAPE_DBF_AREA = शून्य;
EXPORT_SYMBOL(TAPE_DBF_AREA);

/*
 * Prपूर्णांकable strings क्रम tape क्रमागतerations.
 */
स्थिर अक्षर *tape_state_verbose[TS_SIZE] =
अणु
	[TS_UNUSED]   = "UNUSED",
	[TS_IN_USE]   = "IN_USE",
	[TS_BLKUSE]   = "BLKUSE",
	[TS_INIT]     = "INIT  ",
	[TS_NOT_OPER] = "NOT_OP"
पूर्ण;

स्थिर अक्षर *tape_op_verbose[TO_SIZE] =
अणु
	[TO_BLOCK] = "BLK",	[TO_BSB] = "BSB",
	[TO_BSF] = "BSF",	[TO_DSE] = "DSE",
	[TO_FSB] = "FSB",	[TO_FSF] = "FSF",
	[TO_LBL] = "LBL",	[TO_NOP] = "NOP",
	[TO_RBA] = "RBA",	[TO_RBI] = "RBI",
	[TO_RFO] = "RFO",	[TO_REW] = "REW",
	[TO_RUN] = "RUN",	[TO_WRI] = "WRI",
	[TO_WTM] = "WTM",	[TO_MSEN] = "MSN",
	[TO_LOAD] = "LOA",	[TO_READ_CONFIG] = "RCF",
	[TO_READ_ATTMSG] = "RAT",
	[TO_DIS] = "DIS",	[TO_ASSIGN] = "ASS",
	[TO_UNASSIGN] = "UAS",  [TO_CRYPT_ON] = "CON",
	[TO_CRYPT_OFF] = "COF",	[TO_KEKL_SET] = "KLS",
	[TO_KEKL_QUERY] = "KLQ",[TO_RDC] = "RDC",
पूर्ण;

अटल पूर्णांक devid_to_पूर्णांक(काष्ठा ccw_dev_id *dev_id)
अणु
	वापस dev_id->devno + (dev_id->ssid << 16);
पूर्ण

/*
 * Some channel attached tape specअगरic attributes.
 *
 * FIXME: In the future the first_minor and blocksize attribute should be
 *        replaced by a link to the cdev tree.
 */
अटल sमाप_प्रकार
tape_medium_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tape_device *tdev;

	tdev = dev_get_drvdata(dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", tdev->medium_state);
पूर्ण

अटल
DEVICE_ATTR(medium_state, 0444, tape_medium_state_show, शून्य);

अटल sमाप_प्रकार
tape_first_minor_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tape_device *tdev;

	tdev = dev_get_drvdata(dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", tdev->first_minor);
पूर्ण

अटल
DEVICE_ATTR(first_minor, 0444, tape_first_minor_show, शून्य);

अटल sमाप_प्रकार
tape_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tape_device *tdev;

	tdev = dev_get_drvdata(dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", (tdev->first_minor < 0) ?
		"OFFLINE" : tape_state_verbose[tdev->tape_state]);
पूर्ण

अटल
DEVICE_ATTR(state, 0444, tape_state_show, शून्य);

अटल sमाप_प्रकार
tape_operation_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tape_device *tdev;
	sमाप_प्रकार rc;

	tdev = dev_get_drvdata(dev);
	अगर (tdev->first_minor < 0)
		वापस scnम_लिखो(buf, PAGE_SIZE, "N/A\n");

	spin_lock_irq(get_ccwdev_lock(tdev->cdev));
	अगर (list_empty(&tdev->req_queue))
		rc = scnम_लिखो(buf, PAGE_SIZE, "---\n");
	अन्यथा अणु
		काष्ठा tape_request *req;

		req = list_entry(tdev->req_queue.next, काष्ठा tape_request,
			list);
		rc = scnम_लिखो(buf,PAGE_SIZE, "%s\n", tape_op_verbose[req->op]);
	पूर्ण
	spin_unlock_irq(get_ccwdev_lock(tdev->cdev));
	वापस rc;
पूर्ण

अटल
DEVICE_ATTR(operation, 0444, tape_operation_show, शून्य);

अटल sमाप_प्रकार
tape_blocksize_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tape_device *tdev;

	tdev = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", tdev->अक्षर_data.block_size);
पूर्ण

अटल
DEVICE_ATTR(blocksize, 0444, tape_blocksize_show, शून्य);

अटल काष्ठा attribute *tape_attrs[] = अणु
	&dev_attr_medium_state.attr,
	&dev_attr_first_minor.attr,
	&dev_attr_state.attr,
	&dev_attr_operation.attr,
	&dev_attr_blocksize.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tape_attr_group = अणु
	.attrs = tape_attrs,
पूर्ण;

/*
 * Tape state functions
 */
व्योम
tape_state_set(काष्ठा tape_device *device, क्रमागत tape_state newstate)
अणु
	स्थिर अक्षर *str;

	अगर (device->tape_state == TS_NOT_OPER) अणु
		DBF_EVENT(3, "ts_set err: not oper\n");
		वापस;
	पूर्ण
	DBF_EVENT(4, "ts. dev:	%x\n", device->first_minor);
	DBF_EVENT(4, "old ts:\t\n");
	अगर (device->tape_state < TS_SIZE && device->tape_state >=0 )
		str = tape_state_verbose[device->tape_state];
	अन्यथा
		str = "UNKNOWN TS";
	DBF_EVENT(4, "%s\n", str);
	DBF_EVENT(4, "new ts:\t\n");
	अगर (newstate < TS_SIZE && newstate >= 0)
		str = tape_state_verbose[newstate];
	अन्यथा
		str = "UNKNOWN TS";
	DBF_EVENT(4, "%s\n", str);
	device->tape_state = newstate;
	wake_up(&device->state_change_wq);
पूर्ण

काष्ठा tape_med_state_work_data अणु
	काष्ठा tape_device *device;
	क्रमागत tape_medium_state state;
	काष्ठा work_काष्ठा  work;
पूर्ण;

अटल व्योम
tape_med_state_work_handler(काष्ठा work_काष्ठा *work)
अणु
	अटल अक्षर env_state_loaded[] = "MEDIUM_STATE=LOADED";
	अटल अक्षर env_state_unloaded[] = "MEDIUM_STATE=UNLOADED";
	काष्ठा tape_med_state_work_data *p =
		container_of(work, काष्ठा tape_med_state_work_data, work);
	काष्ठा tape_device *device = p->device;
	अक्षर *envp[] = अणु शून्य, शून्य पूर्ण;

	चयन (p->state) अणु
	हाल MS_UNLOADED:
		pr_info("%s: The tape cartridge has been successfully "
			"unloaded\n", dev_name(&device->cdev->dev));
		envp[0] = env_state_unloaded;
		kobject_uevent_env(&device->cdev->dev.kobj, KOBJ_CHANGE, envp);
		अवरोध;
	हाल MS_LOADED:
		pr_info("%s: A tape cartridge has been mounted\n",
			dev_name(&device->cdev->dev));
		envp[0] = env_state_loaded;
		kobject_uevent_env(&device->cdev->dev.kobj, KOBJ_CHANGE, envp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	tape_put_device(device);
	kमुक्त(p);
पूर्ण

अटल व्योम
tape_med_state_work(काष्ठा tape_device *device, क्रमागत tape_medium_state state)
अणु
	काष्ठा tape_med_state_work_data *p;

	p = kzalloc(माप(*p), GFP_ATOMIC);
	अगर (p) अणु
		INIT_WORK(&p->work, tape_med_state_work_handler);
		p->device = tape_get_device(device);
		p->state = state;
		schedule_work(&p->work);
	पूर्ण
पूर्ण

व्योम
tape_med_state_set(काष्ठा tape_device *device, क्रमागत tape_medium_state newstate)
अणु
	क्रमागत tape_medium_state oldstate;

	oldstate = device->medium_state;
	अगर (oldstate == newstate)
		वापस;
	device->medium_state = newstate;
	चयन(newstate)अणु
	हाल MS_UNLOADED:
		device->tape_generic_status |= GMT_DR_OPEN(~0);
		अगर (oldstate == MS_LOADED)
			tape_med_state_work(device, MS_UNLOADED);
		अवरोध;
	हाल MS_LOADED:
		device->tape_generic_status &= ~GMT_DR_OPEN(~0);
		अगर (oldstate == MS_UNLOADED)
			tape_med_state_work(device, MS_LOADED);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	wake_up(&device->state_change_wq);
पूर्ण

/*
 * Stop running ccw. Has to be called with the device lock held.
 */
अटल पूर्णांक
__tape_cancel_io(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	पूर्णांक retries;
	पूर्णांक rc;

	/* Check अगर पूर्णांकerrupt has alपढ़ोy been processed */
	अगर (request->callback == शून्य)
		वापस 0;

	rc = 0;
	क्रम (retries = 0; retries < 5; retries++) अणु
		rc = ccw_device_clear(device->cdev, (दीर्घ) request);

		चयन (rc) अणु
			हाल 0:
				request->status	= TAPE_REQUEST_DONE;
				वापस 0;
			हाल -EBUSY:
				request->status	= TAPE_REQUEST_CANCEL;
				schedule_delayed_work(&device->tape_dnr, 0);
				वापस 0;
			हाल -ENODEV:
				DBF_EXCEPTION(2, "device gone, retry\n");
				अवरोध;
			हाल -EIO:
				DBF_EXCEPTION(2, "I/O error, retry\n");
				अवरोध;
			शेष:
				BUG();
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Add device पूर्णांकo the sorted list, giving it the first
 * available minor number.
 */
अटल पूर्णांक
tape_assign_minor(काष्ठा tape_device *device)
अणु
	काष्ठा tape_device *पंचांगp;
	पूर्णांक minor;

	minor = 0;
	ग_लिखो_lock(&tape_device_lock);
	list_क्रम_each_entry(पंचांगp, &tape_device_list, node) अणु
		अगर (minor < पंचांगp->first_minor)
			अवरोध;
		minor += TAPE_MINORS_PER_DEV;
	पूर्ण
	अगर (minor >= 256) अणु
		ग_लिखो_unlock(&tape_device_lock);
		वापस -ENODEV;
	पूर्ण
	device->first_minor = minor;
	list_add_tail(&device->node, &पंचांगp->node);
	ग_लिखो_unlock(&tape_device_lock);
	वापस 0;
पूर्ण

/* हटाओ device from the list */
अटल व्योम
tape_हटाओ_minor(काष्ठा tape_device *device)
अणु
	ग_लिखो_lock(&tape_device_lock);
	list_del_init(&device->node);
	device->first_minor = -1;
	ग_लिखो_unlock(&tape_device_lock);
पूर्ण

/*
 * Set a device online.
 *
 * This function is called by the common I/O layer to move a device from the
 * detected but offline पूर्णांकo the online state.
 * If we वापस an error (RC < 0) the device reमुख्यs in the offline state. This
 * can happen अगर the device is asचिन्हित somewhere अन्यथा, क्रम example.
 */
पूर्णांक
tape_generic_online(काष्ठा tape_device *device,
		   काष्ठा tape_discipline *discipline)
अणु
	पूर्णांक rc;

	DBF_LH(6, "tape_enable_device(%p, %p)\n", device, discipline);

	अगर (device->tape_state != TS_INIT) अणु
		DBF_LH(3, "Tapestate not INIT (%d)\n", device->tape_state);
		वापस -EINVAL;
	पूर्ण

	समयr_setup(&device->lb_समयout, tape_दीर्घ_busy_समयout, 0);

	/* Let the discipline have a go at the device. */
	device->discipline = discipline;
	अगर (!try_module_get(discipline->owner)) अणु
		वापस -EINVAL;
	पूर्ण

	rc = discipline->setup_device(device);
	अगर (rc)
		जाओ out;
	rc = tape_assign_minor(device);
	अगर (rc)
		जाओ out_discipline;

	rc = tapeअक्षर_setup_device(device);
	अगर (rc)
		जाओ out_minor;

	tape_state_set(device, TS_UNUSED);

	DBF_LH(3, "(%08x): Drive set online\n", device->cdev_id);

	वापस 0;

out_minor:
	tape_हटाओ_minor(device);
out_discipline:
	device->discipline->cleanup_device(device);
	device->discipline = शून्य;
out:
	module_put(discipline->owner);
	वापस rc;
पूर्ण

अटल व्योम
tape_cleanup_device(काष्ठा tape_device *device)
अणु
	tapeअक्षर_cleanup_device(device);
	device->discipline->cleanup_device(device);
	module_put(device->discipline->owner);
	tape_हटाओ_minor(device);
	tape_med_state_set(device, MS_UNKNOWN);
पूर्ण

/*
 * Set device offline.
 *
 * Called by the common I/O layer अगर the drive should set offline on user
 * request. We may prevent this by वापसing an error.
 * Manual offline is only allowed जबतक the drive is not in use.
 */
पूर्णांक
tape_generic_offline(काष्ठा ccw_device *cdev)
अणु
	काष्ठा tape_device *device;

	device = dev_get_drvdata(&cdev->dev);
	अगर (!device) अणु
		वापस -ENODEV;
	पूर्ण

	DBF_LH(3, "(%08x): tape_generic_offline(%p)\n",
		device->cdev_id, device);

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	चयन (device->tape_state) अणु
		हाल TS_INIT:
		हाल TS_NOT_OPER:
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			अवरोध;
		हाल TS_UNUSED:
			tape_state_set(device, TS_INIT);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			tape_cleanup_device(device);
			अवरोध;
		शेष:
			DBF_EVENT(3, "(%08x): Set offline failed "
				"- drive in use.\n",
				device->cdev_id);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			वापस -EBUSY;
	पूर्ण

	DBF_LH(3, "(%08x): Drive set offline.\n", device->cdev_id);
	वापस 0;
पूर्ण

/*
 * Allocate memory क्रम a new device काष्ठाure.
 */
अटल काष्ठा tape_device *
tape_alloc_device(व्योम)
अणु
	काष्ठा tape_device *device;

	device = kzalloc(माप(काष्ठा tape_device), GFP_KERNEL);
	अगर (device == शून्य) अणु
		DBF_EXCEPTION(2, "ti:no mem\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	device->modeset_byte = kदो_स्मृति(1, GFP_KERNEL | GFP_DMA);
	अगर (device->modeset_byte == शून्य) अणु
		DBF_EXCEPTION(2, "ti:no mem\n");
		kमुक्त(device);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	mutex_init(&device->mutex);
	INIT_LIST_HEAD(&device->req_queue);
	INIT_LIST_HEAD(&device->node);
	init_रुकोqueue_head(&device->state_change_wq);
	init_रुकोqueue_head(&device->रुको_queue);
	device->tape_state = TS_INIT;
	device->medium_state = MS_UNKNOWN;
	*device->modeset_byte = 0;
	device->first_minor = -1;
	atomic_set(&device->ref_count, 1);
	INIT_DELAYED_WORK(&device->tape_dnr, tape_delayed_next_request);

	वापस device;
पूर्ण

/*
 * Get a reference to an existing device काष्ठाure. This will स्वतःmatically
 * increment the reference count.
 */
काष्ठा tape_device *
tape_get_device(काष्ठा tape_device *device)
अणु
	पूर्णांक count;

	count = atomic_inc_वापस(&device->ref_count);
	DBF_EVENT(4, "tape_get_device(%p) = %i\n", device, count);
	वापस device;
पूर्ण

/*
 * Decrease the reference counter of a devices काष्ठाure. If the
 * reference counter reaches zero मुक्त the device काष्ठाure.
 * The function वापसs a शून्य poपूर्णांकer to be used by the caller
 * क्रम clearing reference poपूर्णांकers.
 */
व्योम
tape_put_device(काष्ठा tape_device *device)
अणु
	पूर्णांक count;

	count = atomic_dec_वापस(&device->ref_count);
	DBF_EVENT(4, "tape_put_device(%p) -> %i\n", device, count);
	BUG_ON(count < 0);
	अगर (count == 0) अणु
		kमुक्त(device->modeset_byte);
		kमुक्त(device);
	पूर्ण
पूर्ण

/*
 * Find tape device by a device index.
 */
काष्ठा tape_device *
tape_find_device(पूर्णांक devindex)
अणु
	काष्ठा tape_device *device, *पंचांगp;

	device = ERR_PTR(-ENODEV);
	पढ़ो_lock(&tape_device_lock);
	list_क्रम_each_entry(पंचांगp, &tape_device_list, node) अणु
		अगर (पंचांगp->first_minor / TAPE_MINORS_PER_DEV == devindex) अणु
			device = tape_get_device(पंचांगp);
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&tape_device_lock);
	वापस device;
पूर्ण

/*
 * Driverfs tape probe function.
 */
पूर्णांक
tape_generic_probe(काष्ठा ccw_device *cdev)
अणु
	काष्ठा tape_device *device;
	पूर्णांक ret;
	काष्ठा ccw_dev_id dev_id;

	device = tape_alloc_device();
	अगर (IS_ERR(device))
		वापस -ENODEV;
	ccw_device_set_options(cdev, CCWDEV_DO_PATHGROUP |
				     CCWDEV_DO_MULTIPATH);
	ret = sysfs_create_group(&cdev->dev.kobj, &tape_attr_group);
	अगर (ret) अणु
		tape_put_device(device);
		वापस ret;
	पूर्ण
	dev_set_drvdata(&cdev->dev, device);
	cdev->handler = __tape_करो_irq;
	device->cdev = cdev;
	ccw_device_get_id(cdev, &dev_id);
	device->cdev_id = devid_to_पूर्णांक(&dev_id);
	वापस ret;
पूर्ण

अटल व्योम
__tape_discard_requests(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *	request;
	काष्ठा list_head *	l, *n;

	list_क्रम_each_safe(l, n, &device->req_queue) अणु
		request = list_entry(l, काष्ठा tape_request, list);
		अगर (request->status == TAPE_REQUEST_IN_IO)
			request->status = TAPE_REQUEST_DONE;
		list_del(&request->list);

		/* Decrease ref_count क्रम हटाओd request. */
		request->device = शून्य;
		tape_put_device(device);
		request->rc = -EIO;
		अगर (request->callback != शून्य)
			request->callback(request, request->callback_data);
	पूर्ण
पूर्ण

/*
 * Driverfs tape हटाओ function.
 *
 * This function is called whenever the common I/O layer detects the device
 * gone. This can happen at any समय and we cannot refuse.
 */
व्योम
tape_generic_हटाओ(काष्ठा ccw_device *cdev)
अणु
	काष्ठा tape_device *	device;

	device = dev_get_drvdata(&cdev->dev);
	अगर (!device) अणु
		वापस;
	पूर्ण
	DBF_LH(3, "(%08x): tape_generic_remove(%p)\n", device->cdev_id, cdev);

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	चयन (device->tape_state) अणु
		हाल TS_INIT:
			tape_state_set(device, TS_NOT_OPER);
			fallthrough;
		हाल TS_NOT_OPER:
			/*
			 * Nothing to करो.
			 */
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			अवरोध;
		हाल TS_UNUSED:
			/*
			 * Need only to release the device.
			 */
			tape_state_set(device, TS_NOT_OPER);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			tape_cleanup_device(device);
			अवरोध;
		शेष:
			/*
			 * There may be requests on the queue. We will not get
			 * an पूर्णांकerrupt क्रम a request that was running. So we
			 * just post them all as I/O errors.
			 */
			DBF_EVENT(3, "(%08x): Drive in use vanished!\n",
				device->cdev_id);
			pr_warn("%s: A tape unit was detached while in use\n",
				dev_name(&device->cdev->dev));
			tape_state_set(device, TS_NOT_OPER);
			__tape_discard_requests(device);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			tape_cleanup_device(device);
	पूर्ण

	device = dev_get_drvdata(&cdev->dev);
	अगर (device) अणु
		sysfs_हटाओ_group(&cdev->dev.kobj, &tape_attr_group);
		dev_set_drvdata(&cdev->dev, शून्य);
		tape_put_device(device);
	पूर्ण
पूर्ण

/*
 * Allocate a new tape ccw request
 */
काष्ठा tape_request *
tape_alloc_request(पूर्णांक cplength, पूर्णांक datasize)
अणु
	काष्ठा tape_request *request;

	BUG_ON(datasize > PAGE_SIZE || (cplength*माप(काष्ठा ccw1)) > PAGE_SIZE);

	DBF_LH(6, "tape_alloc_request(%d, %d)\n", cplength, datasize);

	request = kzalloc(माप(काष्ठा tape_request), GFP_KERNEL);
	अगर (request == शून्य) अणु
		DBF_EXCEPTION(1, "cqra nomem\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	/* allocate channel program */
	अगर (cplength > 0) अणु
		request->cpaddr = kसुस्मृति(cplength, माप(काष्ठा ccw1),
					  GFP_ATOMIC | GFP_DMA);
		अगर (request->cpaddr == शून्य) अणु
			DBF_EXCEPTION(1, "cqra nomem\n");
			kमुक्त(request);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण
	/* alloc small kernel buffer */
	अगर (datasize > 0) अणु
		request->cpdata = kzalloc(datasize, GFP_KERNEL | GFP_DMA);
		अगर (request->cpdata == शून्य) अणु
			DBF_EXCEPTION(1, "cqra nomem\n");
			kमुक्त(request->cpaddr);
			kमुक्त(request);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण
	DBF_LH(6, "New request %p(%p/%p)\n", request, request->cpaddr,
		request->cpdata);

	वापस request;
पूर्ण

/*
 * Free tape ccw request
 */
व्योम
tape_मुक्त_request (काष्ठा tape_request * request)
अणु
	DBF_LH(6, "Free request %p\n", request);

	अगर (request->device)
		tape_put_device(request->device);
	kमुक्त(request->cpdata);
	kमुक्त(request->cpaddr);
	kमुक्त(request);
पूर्ण

अटल पूर्णांक
__tape_start_io(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	पूर्णांक rc;

	rc = ccw_device_start(
		device->cdev,
		request->cpaddr,
		(अचिन्हित दीर्घ) request,
		0x00,
		request->options
	);
	अगर (rc == 0) अणु
		request->status = TAPE_REQUEST_IN_IO;
	पूर्ण अन्यथा अगर (rc == -EBUSY) अणु
		/* The common I/O subप्रणाली is currently busy. Retry later. */
		request->status = TAPE_REQUEST_QUEUED;
		schedule_delayed_work(&device->tape_dnr, 0);
		rc = 0;
	पूर्ण अन्यथा अणु
		/* Start failed. Remove request and indicate failure. */
		DBF_EVENT(1, "tape: start request failed with RC = %i\n", rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम
__tape_start_next_request(काष्ठा tape_device *device)
अणु
	काष्ठा list_head *l, *n;
	काष्ठा tape_request *request;
	पूर्णांक rc;

	DBF_LH(6, "__tape_start_next_request(%p)\n", device);
	/*
	 * Try to start each request on request queue until one is
	 * started successful.
	 */
	list_क्रम_each_safe(l, n, &device->req_queue) अणु
		request = list_entry(l, काष्ठा tape_request, list);

		/*
		 * Aव्योम race condition अगर bottom-half was triggered more than
		 * once.
		 */
		अगर (request->status == TAPE_REQUEST_IN_IO)
			वापस;
		/*
		 * Request has alपढ़ोy been stopped. We have to रुको until
		 * the request is हटाओd from the queue in the पूर्णांकerrupt
		 * handling.
		 */
		अगर (request->status == TAPE_REQUEST_DONE)
			वापस;

		/*
		 * We wanted to cancel the request but the common I/O layer
		 * was busy at that समय. This can only happen अगर this
		 * function is called by delayed_next_request.
		 * Otherwise we start the next request on the queue.
		 */
		अगर (request->status == TAPE_REQUEST_CANCEL) अणु
			rc = __tape_cancel_io(device, request);
		पूर्ण अन्यथा अणु
			rc = __tape_start_io(device, request);
		पूर्ण
		अगर (rc == 0)
			वापस;

		/* Set ending status. */
		request->rc = rc;
		request->status = TAPE_REQUEST_DONE;

		/* Remove from request queue. */
		list_del(&request->list);

		/* Do callback. */
		अगर (request->callback != शून्य)
			request->callback(request, request->callback_data);
	पूर्ण
पूर्ण

अटल व्योम
tape_delayed_next_request(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tape_device *device =
		container_of(work, काष्ठा tape_device, tape_dnr.work);

	DBF_LH(6, "tape_delayed_next_request(%p)\n", device);
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	__tape_start_next_request(device);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
पूर्ण

अटल व्योम tape_दीर्घ_busy_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा tape_device *device = from_समयr(device, t, lb_समयout);
	काष्ठा tape_request *request;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	request = list_entry(device->req_queue.next, काष्ठा tape_request, list);
	BUG_ON(request->status != TAPE_REQUEST_LONG_BUSY);
	DBF_LH(6, "%08x: Long busy timeout.\n", device->cdev_id);
	__tape_start_next_request(device);
	tape_put_device(device);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
पूर्ण

अटल व्योम
__tape_end_request(
	काष्ठा tape_device *	device,
	काष्ठा tape_request *	request,
	पूर्णांक			rc)
अणु
	DBF_LH(6, "__tape_end_request(%p, %p, %i)\n", device, request, rc);
	अगर (request) अणु
		request->rc = rc;
		request->status = TAPE_REQUEST_DONE;

		/* Remove from request queue. */
		list_del(&request->list);

		/* Do callback. */
		अगर (request->callback != शून्य)
			request->callback(request, request->callback_data);
	पूर्ण

	/* Start next request. */
	अगर (!list_empty(&device->req_queue))
		__tape_start_next_request(device);
पूर्ण

/*
 * Write sense data to dbf
 */
व्योम
tape_dump_sense_dbf(काष्ठा tape_device *device, काष्ठा tape_request *request,
		    काष्ठा irb *irb)
अणु
	अचिन्हित पूर्णांक *sptr;
	स्थिर अक्षर* op;

	अगर (request != शून्य)
		op = tape_op_verbose[request->op];
	अन्यथा
		op = "---";
	DBF_EVENT(3, "DSTAT : %02x   CSTAT: %02x\n",
		  irb->scsw.cmd.dstat, irb->scsw.cmd.cstat);
	DBF_EVENT(3, "DEVICE: %08x OP\t: %s\n", device->cdev_id, op);
	sptr = (अचिन्हित पूर्णांक *) irb->ecw;
	DBF_EVENT(3, "%08x %08x\n", sptr[0], sptr[1]);
	DBF_EVENT(3, "%08x %08x\n", sptr[2], sptr[3]);
	DBF_EVENT(3, "%08x %08x\n", sptr[4], sptr[5]);
	DBF_EVENT(3, "%08x %08x\n", sptr[6], sptr[7]);
पूर्ण

/*
 * I/O helper function. Adds the request to the request queue
 * and starts it अगर the tape is idle. Has to be called with
 * the device lock held.
 */
अटल पूर्णांक
__tape_start_request(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	पूर्णांक rc;

	चयन (request->op) अणु
		हाल TO_MSEN:
		हाल TO_ASSIGN:
		हाल TO_UNASSIGN:
		हाल TO_READ_ATTMSG:
		हाल TO_RDC:
			अगर (device->tape_state == TS_INIT)
				अवरोध;
			अगर (device->tape_state == TS_UNUSED)
				अवरोध;
			fallthrough;
		शेष:
			अगर (device->tape_state == TS_BLKUSE)
				अवरोध;
			अगर (device->tape_state != TS_IN_USE)
				वापस -ENODEV;
	पूर्ण

	/* Increase use count of device क्रम the added request. */
	request->device = tape_get_device(device);

	अगर (list_empty(&device->req_queue)) अणु
		/* No other requests are on the queue. Start this one. */
		rc = __tape_start_io(device, request);
		अगर (rc)
			वापस rc;

		DBF_LH(5, "Request %p added for execution.\n", request);
		list_add(&request->list, &device->req_queue);
	पूर्ण अन्यथा अणु
		DBF_LH(5, "Request %p add to queue.\n", request);
		request->status = TAPE_REQUEST_QUEUED;
		list_add_tail(&request->list, &device->req_queue);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Add the request to the request queue, try to start it अगर the
 * tape is idle. Return without रुकोing क्रम end of i/o.
 */
पूर्णांक
tape_करो_io_async(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	पूर्णांक rc;

	DBF_LH(6, "tape_do_io_async(%p, %p)\n", device, request);

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Add request to request queue and try to start it. */
	rc = __tape_start_request(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	वापस rc;
पूर्ण

/*
 * tape_करो_io/__tape_wake_up
 * Add the request to the request queue, try to start it अगर the
 * tape is idle and रुको unपूर्णांकerruptible क्रम its completion.
 */
अटल व्योम
__tape_wake_up(काष्ठा tape_request *request, व्योम *data)
अणु
	request->callback = शून्य;
	wake_up((रुको_queue_head_t *) data);
पूर्ण

पूर्णांक
tape_करो_io(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	पूर्णांक rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Setup callback */
	request->callback = __tape_wake_up;
	request->callback_data = &device->रुको_queue;
	/* Add request to request queue and try to start it. */
	rc = __tape_start_request(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	अगर (rc)
		वापस rc;
	/* Request added to the queue. Wait क्रम its completion. */
	रुको_event(device->रुको_queue, (request->callback == शून्य));
	/* Get rc from request */
	वापस request->rc;
पूर्ण

/*
 * tape_करो_io_पूर्णांकerruptible/__tape_wake_up_पूर्णांकerruptible
 * Add the request to the request queue, try to start it अगर the
 * tape is idle and रुको unपूर्णांकerruptible क्रम its completion.
 */
अटल व्योम
__tape_wake_up_पूर्णांकerruptible(काष्ठा tape_request *request, व्योम *data)
अणु
	request->callback = शून्य;
	wake_up_पूर्णांकerruptible((रुको_queue_head_t *) data);
पूर्ण

पूर्णांक
tape_करो_io_पूर्णांकerruptible(काष्ठा tape_device *device,
			 काष्ठा tape_request *request)
अणु
	पूर्णांक rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Setup callback */
	request->callback = __tape_wake_up_पूर्णांकerruptible;
	request->callback_data = &device->रुको_queue;
	rc = __tape_start_request(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	अगर (rc)
		वापस rc;
	/* Request added to the queue. Wait क्रम its completion. */
	rc = रुको_event_पूर्णांकerruptible(device->रुको_queue,
				      (request->callback == शून्य));
	अगर (rc != -ERESTARTSYS)
		/* Request finished normally. */
		वापस request->rc;

	/* Interrupted by a संकेत. We have to stop the current request. */
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = __tape_cancel_io(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	अगर (rc == 0) अणु
		/* Wait क्रम the पूर्णांकerrupt that acknowledges the halt. */
		करो अणु
			rc = रुको_event_पूर्णांकerruptible(
				device->रुको_queue,
				(request->callback == शून्य)
			);
		पूर्ण जबतक (rc == -ERESTARTSYS);

		DBF_EVENT(3, "IO stopped on %08x\n", device->cdev_id);
		rc = -ERESTARTSYS;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Stop running ccw.
 */
पूर्णांक
tape_cancel_io(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	पूर्णांक rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = __tape_cancel_io(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	वापस rc;
पूर्ण

/*
 * Tape पूर्णांकerrupt routine, called from the ccw_device layer
 */
अटल व्योम
__tape_करो_irq (काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm, काष्ठा irb *irb)
अणु
	काष्ठा tape_device *device;
	काष्ठा tape_request *request;
	पूर्णांक rc;

	device = dev_get_drvdata(&cdev->dev);
	अगर (device == शून्य) अणु
		वापस;
	पूर्ण
	request = (काष्ठा tape_request *) पूर्णांकparm;

	DBF_LH(6, "__tape_do_irq(device=%p, request=%p)\n", device, request);

	/* On special conditions irb is an error poपूर्णांकer */
	अगर (IS_ERR(irb)) अणु
		/* FIXME: What to करो with the request? */
		चयन (PTR_ERR(irb)) अणु
			हाल -ETIMEDOUT:
				DBF_LH(1, "(%08x): Request timed out\n",
				       device->cdev_id);
				fallthrough;
			हाल -EIO:
				__tape_end_request(device, request, -EIO);
				अवरोध;
			शेष:
				DBF_LH(1, "(%08x): Unexpected i/o error %li\n",
				       device->cdev_id,	PTR_ERR(irb));
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * If the condition code is not zero and the start function bit is
	 * still set, this is an deferred error and the last start I/O did
	 * not succeed. At this poपूर्णांक the condition that caused the deferred
	 * error might still apply. So we just schedule the request to be
	 * started later.
	 */
	अगर (irb->scsw.cmd.cc != 0 &&
	    (irb->scsw.cmd.fctl & SCSW_FCTL_START_FUNC) &&
	    (request->status == TAPE_REQUEST_IN_IO)) अणु
		DBF_EVENT(3,"(%08x): deferred cc=%i, fctl=%i. restarting\n",
			device->cdev_id, irb->scsw.cmd.cc, irb->scsw.cmd.fctl);
		request->status = TAPE_REQUEST_QUEUED;
		schedule_delayed_work(&device->tape_dnr, HZ);
		वापस;
	पूर्ण

	/* May be an unsolicited irq */
	अगर(request != शून्य)
		request->rescnt = irb->scsw.cmd.count;
	अन्यथा अगर ((irb->scsw.cmd.dstat == 0x85 || irb->scsw.cmd.dstat == 0x80) &&
		 !list_empty(&device->req_queue)) अणु
		/* Not Ready to Ready after दीर्घ busy ? */
		काष्ठा tape_request *req;
		req = list_entry(device->req_queue.next,
				 काष्ठा tape_request, list);
		अगर (req->status == TAPE_REQUEST_LONG_BUSY) अणु
			DBF_EVENT(3, "(%08x): del timer\n", device->cdev_id);
			अगर (del_समयr(&device->lb_समयout)) अणु
				tape_put_device(device);
				__tape_start_next_request(device);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण
	अगर (irb->scsw.cmd.dstat != 0x0c) अणु
		/* Set the 'ONLINE' flag depending on sense byte 1 */
		अगर(*(((__u8 *) irb->ecw) + 1) & SENSE_DRIVE_ONLINE)
			device->tape_generic_status |= GMT_ONLINE(~0);
		अन्यथा
			device->tape_generic_status &= ~GMT_ONLINE(~0);

		/*
		 * Any request that करोes not come back with channel end
		 * and device end is unusual. Log the sense data.
		 */
		DBF_EVENT(3,"-- Tape Interrupthandler --\n");
		tape_dump_sense_dbf(device, request, irb);
	पूर्ण अन्यथा अणु
		/* Upon normal completion the device _is_ online */
		device->tape_generic_status |= GMT_ONLINE(~0);
	पूर्ण
	अगर (device->tape_state == TS_NOT_OPER) अणु
		DBF_EVENT(6, "tape:device is not operational\n");
		वापस;
	पूर्ण

	/*
	 * Request that were canceled still come back with an पूर्णांकerrupt.
	 * To detect these request the state will be set to TAPE_REQUEST_DONE.
	 */
	अगर(request != शून्य && request->status == TAPE_REQUEST_DONE) अणु
		__tape_end_request(device, request, -EIO);
		वापस;
	पूर्ण

	rc = device->discipline->irq(device, request, irb);
	/*
	 * rc < 0 : request finished unsuccessfully.
	 * rc == TAPE_IO_SUCCESS: request finished successfully.
	 * rc == TAPE_IO_PENDING: request is still running. Ignore rc.
	 * rc == TAPE_IO_RETRY: request finished but needs another go.
	 * rc == TAPE_IO_STOP: request needs to get terminated.
	 */
	चयन (rc) अणु
		हाल TAPE_IO_SUCCESS:
			/* Upon normal completion the device _is_ online */
			device->tape_generic_status |= GMT_ONLINE(~0);
			__tape_end_request(device, request, rc);
			अवरोध;
		हाल TAPE_IO_PENDING:
			अवरोध;
		हाल TAPE_IO_LONG_BUSY:
			device->lb_समयout.expires = jअगरfies +
				LONG_BUSY_TIMEOUT * HZ;
			DBF_EVENT(3, "(%08x): add timer\n", device->cdev_id);
			add_समयr(&device->lb_समयout);
			request->status = TAPE_REQUEST_LONG_BUSY;
			अवरोध;
		हाल TAPE_IO_RETRY:
			rc = __tape_start_io(device, request);
			अगर (rc)
				__tape_end_request(device, request, rc);
			अवरोध;
		हाल TAPE_IO_STOP:
			rc = __tape_cancel_io(device, request);
			अगर (rc)
				__tape_end_request(device, request, rc);
			अवरोध;
		शेष:
			अगर (rc > 0) अणु
				DBF_EVENT(6, "xunknownrc\n");
				__tape_end_request(device, request, -EIO);
			पूर्ण अन्यथा अणु
				__tape_end_request(device, request, rc);
			पूर्ण
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Tape device खोलो function used by tape_अक्षर frontend.
 */
पूर्णांक
tape_खोलो(काष्ठा tape_device *device)
अणु
	पूर्णांक rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	अगर (device->tape_state == TS_NOT_OPER) अणु
		DBF_EVENT(6, "TAPE:nodev\n");
		rc = -ENODEV;
	पूर्ण अन्यथा अगर (device->tape_state == TS_IN_USE) अणु
		DBF_EVENT(6, "TAPE:dbusy\n");
		rc = -EBUSY;
	पूर्ण अन्यथा अगर (device->tape_state == TS_BLKUSE) अणु
		DBF_EVENT(6, "TAPE:dbusy\n");
		rc = -EBUSY;
	पूर्ण अन्यथा अगर (device->discipline != शून्य &&
		   !try_module_get(device->discipline->owner)) अणु
		DBF_EVENT(6, "TAPE:nodisc\n");
		rc = -ENODEV;
	पूर्ण अन्यथा अणु
		tape_state_set(device, TS_IN_USE);
		rc = 0;
	पूर्ण
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	वापस rc;
पूर्ण

/*
 * Tape device release function used by tape_अक्षर frontend.
 */
पूर्णांक
tape_release(काष्ठा tape_device *device)
अणु
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	अगर (device->tape_state == TS_IN_USE)
		tape_state_set(device, TS_UNUSED);
	module_put(device->discipline->owner);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	वापस 0;
पूर्ण

/*
 * Execute a magnetic tape command a number of बार.
 */
पूर्णांक
tape_mtop(काष्ठा tape_device *device, पूर्णांक mt_op, पूर्णांक mt_count)
अणु
	tape_mtop_fn fn;
	पूर्णांक rc;

	DBF_EVENT(6, "TAPE:mtio\n");
	DBF_EVENT(6, "TAPE:ioop: %x\n", mt_op);
	DBF_EVENT(6, "TAPE:arg:	 %x\n", mt_count);

	अगर (mt_op < 0 || mt_op >= TAPE_NR_MTOPS)
		वापस -EINVAL;
	fn = device->discipline->mtop_array[mt_op];
	अगर (fn == शून्य)
		वापस -EINVAL;

	/* We assume that the backends can handle count up to 500. */
	अगर (mt_op == MTBSR  || mt_op == MTFSR  || mt_op == MTFSF  ||
	    mt_op == MTBSF  || mt_op == MTFSFM || mt_op == MTBSFM) अणु
		rc = 0;
		क्रम (; mt_count > 500; mt_count -= 500)
			अगर ((rc = fn(device, 500)) != 0)
				अवरोध;
		अगर (rc == 0)
			rc = fn(device, mt_count);
	पूर्ण अन्यथा
		rc = fn(device, mt_count);
	वापस rc;

पूर्ण

/*
 * Tape init function.
 */
अटल पूर्णांक
tape_init (व्योम)
अणु
	TAPE_DBF_AREA = debug_रेजिस्टर ( "tape", 2, 2, 4*माप(दीर्घ));
	debug_रेजिस्टर_view(TAPE_DBF_AREA, &debug_प्र_लिखो_view);
#अगर_घोषित DBF_LIKE_HELL
	debug_set_level(TAPE_DBF_AREA, 6);
#पूर्ण_अगर
	DBF_EVENT(3, "tape init\n");
	tape_proc_init();
	tapeअक्षर_init ();
	वापस 0;
पूर्ण

/*
 * Tape निकास function.
 */
अटल व्योम
tape_निकास(व्योम)
अणु
	DBF_EVENT(6, "tape exit\n");

	/* Get rid of the frontends */
	tapeअक्षर_निकास();
	tape_proc_cleanup();
	debug_unरेजिस्टर (TAPE_DBF_AREA);
पूर्ण

MODULE_AUTHOR("(C) 2001 IBM Deutschland Entwicklung GmbH by Carsten Otte and "
	      "Michael Holzheu (cotte@de.ibm.com,holzheu@de.ibm.com)");
MODULE_DESCRIPTION("Linux on zSeries channel attached tape device driver");
MODULE_LICENSE("GPL");

module_init(tape_init);
module_निकास(tape_निकास);

EXPORT_SYMBOL(tape_generic_हटाओ);
EXPORT_SYMBOL(tape_generic_probe);
EXPORT_SYMBOL(tape_generic_online);
EXPORT_SYMBOL(tape_generic_offline);
EXPORT_SYMBOL(tape_put_device);
EXPORT_SYMBOL(tape_get_device);
EXPORT_SYMBOL(tape_state_verbose);
EXPORT_SYMBOL(tape_op_verbose);
EXPORT_SYMBOL(tape_state_set);
EXPORT_SYMBOL(tape_med_state_set);
EXPORT_SYMBOL(tape_alloc_request);
EXPORT_SYMBOL(tape_मुक्त_request);
EXPORT_SYMBOL(tape_dump_sense_dbf);
EXPORT_SYMBOL(tape_करो_io);
EXPORT_SYMBOL(tape_करो_io_async);
EXPORT_SYMBOL(tape_करो_io_पूर्णांकerruptible);
EXPORT_SYMBOL(tape_cancel_io);
EXPORT_SYMBOL(tape_mtop);
