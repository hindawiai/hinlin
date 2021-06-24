<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#घोषणा pr_fmt(fmt)			"habanalabs: " fmt

#समावेश "habanalabs.h"

#समावेश <linux/pci.h>
#समावेश <linux/hwmon.h>
#समावेश <uapi/misc/habanaद_असल.h>

क्रमागत hl_device_status hl_device_status(काष्ठा hl_device *hdev)
अणु
	क्रमागत hl_device_status status;

	अगर (atomic_पढ़ो(&hdev->in_reset))
		status = HL_DEVICE_STATUS_IN_RESET;
	अन्यथा अगर (hdev->needs_reset)
		status = HL_DEVICE_STATUS_NEEDS_RESET;
	अन्यथा अगर (hdev->disabled)
		status = HL_DEVICE_STATUS_MALFUNCTION;
	अन्यथा
		status = HL_DEVICE_STATUS_OPERATIONAL;

	वापस status;
पूर्ण

bool hl_device_operational(काष्ठा hl_device *hdev,
		क्रमागत hl_device_status *status)
अणु
	क्रमागत hl_device_status current_status;

	current_status = hl_device_status(hdev);
	अगर (status)
		*status = current_status;

	चयन (current_status) अणु
	हाल HL_DEVICE_STATUS_IN_RESET:
	हाल HL_DEVICE_STATUS_MALFUNCTION:
	हाल HL_DEVICE_STATUS_NEEDS_RESET:
		वापस false;
	हाल HL_DEVICE_STATUS_OPERATIONAL:
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम hpriv_release(काष्ठा kref *ref)
अणु
	काष्ठा hl_fpriv *hpriv;
	काष्ठा hl_device *hdev;

	hpriv = container_of(ref, काष्ठा hl_fpriv, refcount);

	hdev = hpriv->hdev;

	put_pid(hpriv->taskpid);

	hl_debugfs_हटाओ_file(hpriv);

	mutex_destroy(&hpriv->restore_phase_mutex);

	mutex_lock(&hdev->fpriv_list_lock);
	list_del(&hpriv->dev_node);
	hdev->compute_ctx = शून्य;
	mutex_unlock(&hdev->fpriv_list_lock);

	kमुक्त(hpriv);

	अगर (hdev->reset_upon_device_release)
		hl_device_reset(hdev, 0);
पूर्ण

व्योम hl_hpriv_get(काष्ठा hl_fpriv *hpriv)
अणु
	kref_get(&hpriv->refcount);
पूर्ण

पूर्णांक hl_hpriv_put(काष्ठा hl_fpriv *hpriv)
अणु
	वापस kref_put(&hpriv->refcount, hpriv_release);
पूर्ण

/*
 * hl_device_release - release function क्रम habanaद_असल device
 *
 * @inode: poपूर्णांकer to inode काष्ठाure
 * @filp: poपूर्णांकer to file काष्ठाure
 *
 * Called when process बंदs an habanaद_असल device
 */
अटल पूर्णांक hl_device_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा hl_fpriv *hpriv = filp->निजी_data;
	काष्ठा hl_device *hdev = hpriv->hdev;

	filp->निजी_data = शून्य;

	अगर (!hdev) अणु
		pr_crit("Closing FD after device was removed. Memory leak will occur and it is advised to reboot.\n");
		put_pid(hpriv->taskpid);
		वापस 0;
	पूर्ण

	/* Each pending user पूर्णांकerrupt holds the user's context, hence we
	 * must release them all beक्रमe calling hl_ctx_mgr_fini().
	 */
	hl_release_pending_user_पूर्णांकerrupts(hpriv->hdev);

	hl_cb_mgr_fini(hdev, &hpriv->cb_mgr);
	hl_ctx_mgr_fini(hdev, &hpriv->ctx_mgr);

	अगर (!hl_hpriv_put(hpriv))
		dev_warn(hdev->dev,
			"Device is still in use because there are live CS and/or memory mappings\n");

	वापस 0;
पूर्ण

अटल पूर्णांक hl_device_release_ctrl(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा hl_fpriv *hpriv = filp->निजी_data;
	काष्ठा hl_device *hdev = hpriv->hdev;

	filp->निजी_data = शून्य;

	अगर (!hdev) अणु
		pr_err("Closing FD after device was removed\n");
		जाओ out;
	पूर्ण

	mutex_lock(&hdev->fpriv_list_lock);
	list_del(&hpriv->dev_node);
	mutex_unlock(&hdev->fpriv_list_lock);
out:
	put_pid(hpriv->taskpid);

	kमुक्त(hpriv);

	वापस 0;
पूर्ण

/*
 * hl_mmap - mmap function क्रम habanaद_असल device
 *
 * @*filp: poपूर्णांकer to file काष्ठाure
 * @*vma: poपूर्णांकer to vm_area_काष्ठा of the process
 *
 * Called when process करोes an mmap on habanaद_असल device. Call the device's mmap
 * function at the end of the common code.
 */
अटल पूर्णांक hl_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hl_fpriv *hpriv = filp->निजी_data;
	काष्ठा hl_device *hdev = hpriv->hdev;
	अचिन्हित दीर्घ vm_pgoff;

	अगर (!hdev) अणु
		pr_err_ratelimited("Trying to mmap after device was removed! Please close FD\n");
		वापस -ENODEV;
	पूर्ण

	vm_pgoff = vma->vm_pgoff;
	vma->vm_pgoff = HL_MMAP_OFFSET_VALUE_GET(vm_pgoff);

	चयन (vm_pgoff & HL_MMAP_TYPE_MASK) अणु
	हाल HL_MMAP_TYPE_CB:
		वापस hl_cb_mmap(hpriv, vma);

	हाल HL_MMAP_TYPE_BLOCK:
		वापस hl_hw_block_mmap(hpriv, vma);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा file_operations hl_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = hl_device_खोलो,
	.release = hl_device_release,
	.mmap = hl_mmap,
	.unlocked_ioctl = hl_ioctl,
	.compat_ioctl = hl_ioctl
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_ctrl_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = hl_device_खोलो_ctrl,
	.release = hl_device_release_ctrl,
	.unlocked_ioctl = hl_ioctl_control,
	.compat_ioctl = hl_ioctl_control
पूर्ण;

अटल व्योम device_release_func(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

/*
 * device_init_cdev - Initialize cdev and device क्रम habanaद_असल device
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 * @hclass: poपूर्णांकer to the class object of the device
 * @minor: minor number of the specअगरic device
 * @fpos: file operations to install क्रम this device
 * @name: name of the device as it will appear in the fileप्रणाली
 * @cdev: poपूर्णांकer to the अक्षर device object that will be initialized
 * @dev: poपूर्णांकer to the device object that will be initialized
 *
 * Initialize a cdev and a Linux device क्रम habanaद_असल's device.
 */
अटल पूर्णांक device_init_cdev(काष्ठा hl_device *hdev, काष्ठा class *hclass,
				पूर्णांक minor, स्थिर काष्ठा file_operations *fops,
				अक्षर *name, काष्ठा cdev *cdev,
				काष्ठा device **dev)
अणु
	cdev_init(cdev, fops);
	cdev->owner = THIS_MODULE;

	*dev = kzalloc(माप(**dev), GFP_KERNEL);
	अगर (!*dev)
		वापस -ENOMEM;

	device_initialize(*dev);
	(*dev)->devt = MKDEV(hdev->major, minor);
	(*dev)->class = hclass;
	(*dev)->release = device_release_func;
	dev_set_drvdata(*dev, hdev);
	dev_set_name(*dev, "%s", name);

	वापस 0;
पूर्ण

अटल पूर्णांक device_cdev_sysfs_add(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	rc = cdev_device_add(&hdev->cdev, hdev->dev);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"failed to add a char device to the system\n");
		वापस rc;
	पूर्ण

	rc = cdev_device_add(&hdev->cdev_ctrl, hdev->dev_ctrl);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"failed to add a control char device to the system\n");
		जाओ delete_cdev_device;
	पूर्ण

	/* hl_sysfs_init() must be करोne after adding the device to the प्रणाली */
	rc = hl_sysfs_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize sysfs\n");
		जाओ delete_ctrl_cdev_device;
	पूर्ण

	hdev->cdev_sysfs_created = true;

	वापस 0;

delete_ctrl_cdev_device:
	cdev_device_del(&hdev->cdev_ctrl, hdev->dev_ctrl);
delete_cdev_device:
	cdev_device_del(&hdev->cdev, hdev->dev);
	वापस rc;
पूर्ण

अटल व्योम device_cdev_sysfs_del(काष्ठा hl_device *hdev)
अणु
	अगर (!hdev->cdev_sysfs_created)
		जाओ put_devices;

	hl_sysfs_fini(hdev);
	cdev_device_del(&hdev->cdev_ctrl, hdev->dev_ctrl);
	cdev_device_del(&hdev->cdev, hdev->dev);

put_devices:
	put_device(hdev->dev);
	put_device(hdev->dev_ctrl);
पूर्ण

अटल व्योम device_hard_reset_pending(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hl_device_reset_work *device_reset_work =
		container_of(work, काष्ठा hl_device_reset_work,
				reset_work.work);
	काष्ठा hl_device *hdev = device_reset_work->hdev;
	पूर्णांक rc;

	rc = hl_device_reset(hdev, HL_RESET_HARD | HL_RESET_FROM_RESET_THREAD);
	अगर ((rc == -EBUSY) && !hdev->device_fini_pending) अणु
		dev_info(hdev->dev,
			"Could not reset device. will try again in %u seconds",
			HL_PENDING_RESET_PER_SEC);

		queue_delayed_work(device_reset_work->wq,
			&device_reset_work->reset_work,
			msecs_to_jअगरfies(HL_PENDING_RESET_PER_SEC * 1000));
	पूर्ण
पूर्ण

/*
 * device_early_init - करो some early initialization क्रम the habanaद_असल device
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 * Install the relevant function poपूर्णांकers and call the early_init function,
 * अगर such a function exists
 */
अटल पूर्णांक device_early_init(काष्ठा hl_device *hdev)
अणु
	पूर्णांक i, rc;
	अक्षर workq_name[32];

	चयन (hdev->asic_type) अणु
	हाल ASIC_GOYA:
		goya_set_asic_funcs(hdev);
		strscpy(hdev->asic_name, "GOYA", माप(hdev->asic_name));
		अवरोध;
	हाल ASIC_GAUDI:
		gaudi_set_asic_funcs(hdev);
		strscpy(hdev->asic_name, "GAUDI", माप(hdev->asic_name));
		अवरोध;
	हाल ASIC_GAUDI_SEC:
		gaudi_set_asic_funcs(hdev);
		strscpy(hdev->asic_name, "GAUDI SEC", माप(hdev->asic_name));
		अवरोध;
	शेष:
		dev_err(hdev->dev, "Unrecognized ASIC type %d\n",
			hdev->asic_type);
		वापस -EINVAL;
	पूर्ण

	rc = hdev->asic_funcs->early_init(hdev);
	अगर (rc)
		वापस rc;

	rc = hl_asid_init(hdev);
	अगर (rc)
		जाओ early_fini;

	अगर (hdev->asic_prop.completion_queues_count) अणु
		hdev->cq_wq = kसुस्मृति(hdev->asic_prop.completion_queues_count,
				माप(*hdev->cq_wq),
				GFP_KERNEL);
		अगर (!hdev->cq_wq) अणु
			rc = -ENOMEM;
			जाओ asid_fini;
		पूर्ण
	पूर्ण

	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++) अणु
		snम_लिखो(workq_name, 32, "hl-free-jobs-%u", (u32) i);
		hdev->cq_wq[i] = create_singlethपढ़ो_workqueue(workq_name);
		अगर (hdev->cq_wq[i] == शून्य) अणु
			dev_err(hdev->dev, "Failed to allocate CQ workqueue\n");
			rc = -ENOMEM;
			जाओ मुक्त_cq_wq;
		पूर्ण
	पूर्ण

	hdev->eq_wq = alloc_workqueue("hl-events", WQ_UNBOUND, 0);
	अगर (hdev->eq_wq == शून्य) अणु
		dev_err(hdev->dev, "Failed to allocate EQ workqueue\n");
		rc = -ENOMEM;
		जाओ मुक्त_cq_wq;
	पूर्ण

	hdev->sob_reset_wq = alloc_workqueue("hl-sob-reset", WQ_UNBOUND, 0);
	अगर (!hdev->sob_reset_wq) अणु
		dev_err(hdev->dev,
			"Failed to allocate SOB reset workqueue\n");
		rc = -ENOMEM;
		जाओ मुक्त_eq_wq;
	पूर्ण

	hdev->hl_chip_info = kzalloc(माप(काष्ठा hwmon_chip_info),
					GFP_KERNEL);
	अगर (!hdev->hl_chip_info) अणु
		rc = -ENOMEM;
		जाओ मुक्त_sob_reset_wq;
	पूर्ण

	rc = hl_mmu_अगर_set_funcs(hdev);
	अगर (rc)
		जाओ मुक्त_chip_info;

	hl_cb_mgr_init(&hdev->kernel_cb_mgr);

	hdev->device_reset_work.wq =
			create_singlethपढ़ो_workqueue("hl_device_reset");
	अगर (!hdev->device_reset_work.wq) अणु
		rc = -ENOMEM;
		dev_err(hdev->dev, "Failed to create device reset WQ\n");
		जाओ मुक्त_cb_mgr;
	पूर्ण

	INIT_DELAYED_WORK(&hdev->device_reset_work.reset_work,
			device_hard_reset_pending);
	hdev->device_reset_work.hdev = hdev;
	hdev->device_fini_pending = 0;

	mutex_init(&hdev->send_cpu_message_lock);
	mutex_init(&hdev->debug_lock);
	INIT_LIST_HEAD(&hdev->cs_mirror_list);
	spin_lock_init(&hdev->cs_mirror_lock);
	INIT_LIST_HEAD(&hdev->fpriv_list);
	mutex_init(&hdev->fpriv_list_lock);
	atomic_set(&hdev->in_reset, 0);

	वापस 0;

मुक्त_cb_mgr:
	hl_cb_mgr_fini(hdev, &hdev->kernel_cb_mgr);
मुक्त_chip_info:
	kमुक्त(hdev->hl_chip_info);
मुक्त_sob_reset_wq:
	destroy_workqueue(hdev->sob_reset_wq);
मुक्त_eq_wq:
	destroy_workqueue(hdev->eq_wq);
मुक्त_cq_wq:
	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		अगर (hdev->cq_wq[i])
			destroy_workqueue(hdev->cq_wq[i]);
	kमुक्त(hdev->cq_wq);
asid_fini:
	hl_asid_fini(hdev);
early_fini:
	अगर (hdev->asic_funcs->early_fini)
		hdev->asic_funcs->early_fini(hdev);

	वापस rc;
पूर्ण

/*
 * device_early_fini - finalize all that was करोne in device_early_init
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 */
अटल व्योम device_early_fini(काष्ठा hl_device *hdev)
अणु
	पूर्णांक i;

	mutex_destroy(&hdev->debug_lock);
	mutex_destroy(&hdev->send_cpu_message_lock);

	mutex_destroy(&hdev->fpriv_list_lock);

	hl_cb_mgr_fini(hdev, &hdev->kernel_cb_mgr);

	kमुक्त(hdev->hl_chip_info);

	destroy_workqueue(hdev->sob_reset_wq);
	destroy_workqueue(hdev->eq_wq);
	destroy_workqueue(hdev->device_reset_work.wq);

	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		destroy_workqueue(hdev->cq_wq[i]);
	kमुक्त(hdev->cq_wq);

	hl_asid_fini(hdev);

	अगर (hdev->asic_funcs->early_fini)
		hdev->asic_funcs->early_fini(hdev);
पूर्ण

अटल व्योम set_freq_to_low_job(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hl_device *hdev = container_of(work, काष्ठा hl_device,
						work_freq.work);

	mutex_lock(&hdev->fpriv_list_lock);

	अगर (!hdev->compute_ctx)
		hl_device_set_frequency(hdev, PLL_LOW);

	mutex_unlock(&hdev->fpriv_list_lock);

	schedule_delayed_work(&hdev->work_freq,
			usecs_to_jअगरfies(HL_PLL_LOW_JOB_FREQ_USEC));
पूर्ण

अटल व्योम hl_device_heartbeat(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hl_device *hdev = container_of(work, काष्ठा hl_device,
						work_heartbeat.work);

	अगर (!hl_device_operational(hdev, शून्य))
		जाओ reschedule;

	अगर (!hdev->asic_funcs->send_heartbeat(hdev))
		जाओ reschedule;

	dev_err(hdev->dev, "Device heartbeat failed!\n");
	hl_device_reset(hdev, HL_RESET_HARD | HL_RESET_HEARTBEAT);

	वापस;

reschedule:
	schedule_delayed_work(&hdev->work_heartbeat,
			usecs_to_jअगरfies(HL_HEARTBEAT_PER_USEC));
पूर्ण

/*
 * device_late_init - करो late stuff initialization क्रम the habanaद_असल device
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 * Do stuff that either needs the device H/W queues to be active or needs
 * to happen after all the rest of the initialization is finished
 */
अटल पूर्णांक device_late_init(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	अगर (hdev->asic_funcs->late_init) अणु
		rc = hdev->asic_funcs->late_init(hdev);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"failed late initialization for the H/W\n");
			वापस rc;
		पूर्ण
	पूर्ण

	hdev->high_pll = hdev->asic_prop.high_pll;

	/* क्रमce setting to low frequency */
	hdev->curr_pll_profile = PLL_LOW;

	अगर (hdev->pm_mng_profile == PM_AUTO)
		hdev->asic_funcs->set_pll_profile(hdev, PLL_LOW);
	अन्यथा
		hdev->asic_funcs->set_pll_profile(hdev, PLL_LAST);

	INIT_DELAYED_WORK(&hdev->work_freq, set_freq_to_low_job);
	schedule_delayed_work(&hdev->work_freq,
	usecs_to_jअगरfies(HL_PLL_LOW_JOB_FREQ_USEC));

	अगर (hdev->heartbeat) अणु
		INIT_DELAYED_WORK(&hdev->work_heartbeat, hl_device_heartbeat);
		schedule_delayed_work(&hdev->work_heartbeat,
				usecs_to_jअगरfies(HL_HEARTBEAT_PER_USEC));
	पूर्ण

	hdev->late_init_करोne = true;

	वापस 0;
पूर्ण

/*
 * device_late_fini - finalize all that was करोne in device_late_init
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 */
अटल व्योम device_late_fini(काष्ठा hl_device *hdev)
अणु
	अगर (!hdev->late_init_करोne)
		वापस;

	cancel_delayed_work_sync(&hdev->work_freq);
	अगर (hdev->heartbeat)
		cancel_delayed_work_sync(&hdev->work_heartbeat);

	अगर (hdev->asic_funcs->late_fini)
		hdev->asic_funcs->late_fini(hdev);

	hdev->late_init_करोne = false;
पूर्ण

पूर्णांक hl_device_utilization(काष्ठा hl_device *hdev, u32 *utilization)
अणु
	u64 max_घातer, curr_घातer, dc_घातer, भागidend;
	पूर्णांक rc;

	max_घातer = hdev->asic_prop.max_घातer_शेष;
	dc_घातer = hdev->asic_prop.dc_घातer_शेष;
	rc = hl_fw_cpucp_घातer_get(hdev, &curr_घातer);

	अगर (rc)
		वापस rc;

	curr_घातer = clamp(curr_घातer, dc_घातer, max_घातer);

	भागidend = (curr_घातer - dc_घातer) * 100;
	*utilization = (u32) भाग_u64(भागidend, (max_घातer - dc_घातer));

	वापस 0;
पूर्ण

/*
 * hl_device_set_frequency - set the frequency of the device
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 * @freq: the new frequency value
 *
 * Change the frequency अगर needed. This function has no protection against
 * concurrency, thereक्रमe it is assumed that the calling function has रक्षित
 * itself against the हाल of calling this function from multiple thपढ़ोs with
 * dअगरferent values
 *
 * Returns 0 अगर no change was करोne, otherwise वापसs 1
 */
पूर्णांक hl_device_set_frequency(काष्ठा hl_device *hdev, क्रमागत hl_pll_frequency freq)
अणु
	अगर ((hdev->pm_mng_profile == PM_MANUAL) ||
			(hdev->curr_pll_profile == freq))
		वापस 0;

	dev_dbg(hdev->dev, "Changing device frequency to %s\n",
		freq == PLL_HIGH ? "high" : "low");

	hdev->asic_funcs->set_pll_profile(hdev, freq);

	hdev->curr_pll_profile = freq;

	वापस 1;
पूर्ण

पूर्णांक hl_device_set_debug_mode(काष्ठा hl_device *hdev, bool enable)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&hdev->debug_lock);

	अगर (!enable) अणु
		अगर (!hdev->in_debug) अणु
			dev_err(hdev->dev,
				"Failed to disable debug mode because device was not in debug mode\n");
			rc = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (!hdev->hard_reset_pending)
			hdev->asic_funcs->halt_coresight(hdev);

		hdev->in_debug = 0;

		अगर (!hdev->hard_reset_pending)
			hdev->asic_funcs->set_घड़ी_gating(hdev);

		जाओ out;
	पूर्ण

	अगर (hdev->in_debug) अणु
		dev_err(hdev->dev,
			"Failed to enable debug mode because device is already in debug mode\n");
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	hdev->asic_funcs->disable_घड़ी_gating(hdev);
	hdev->in_debug = 1;

out:
	mutex_unlock(&hdev->debug_lock);

	वापस rc;
पूर्ण

/*
 * hl_device_suspend - initiate device suspend
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 * Puts the hw in the suspend state (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver suspend.
 */
पूर्णांक hl_device_suspend(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	pci_save_state(hdev->pdev);

	/* Block future CS/VM/JOB completion operations */
	rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
	अगर (rc) अणु
		dev_err(hdev->dev, "Can't suspend while in reset\n");
		वापस -EIO;
	पूर्ण

	/* This blocks all other stuff that is not blocked by in_reset */
	hdev->disabled = true;

	/*
	 * Flush anyone that is inside the critical section of enqueue
	 * jobs to the H/W
	 */
	hdev->asic_funcs->hw_queues_lock(hdev);
	hdev->asic_funcs->hw_queues_unlock(hdev);

	/* Flush processes that are sending message to CPU */
	mutex_lock(&hdev->send_cpu_message_lock);
	mutex_unlock(&hdev->send_cpu_message_lock);

	rc = hdev->asic_funcs->suspend(hdev);
	अगर (rc)
		dev_err(hdev->dev,
			"Failed to disable PCI access of device CPU\n");

	/* Shut करोwn the device */
	pci_disable_device(hdev->pdev);
	pci_set_घातer_state(hdev->pdev, PCI_D3hot);

	वापस 0;
पूर्ण

/*
 * hl_device_resume - initiate device resume
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 * Bring the hw back to operating state (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver resume.
 */
पूर्णांक hl_device_resume(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc;

	pci_set_घातer_state(hdev->pdev, PCI_D0);
	pci_restore_state(hdev->pdev);
	rc = pci_enable_device_mem(hdev->pdev);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to enable PCI device in resume\n");
		वापस rc;
	पूर्ण

	pci_set_master(hdev->pdev);

	rc = hdev->asic_funcs->resume(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to resume device after suspend\n");
		जाओ disable_device;
	पूर्ण


	hdev->disabled = false;
	atomic_set(&hdev->in_reset, 0);

	rc = hl_device_reset(hdev, HL_RESET_HARD);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to reset device during resume\n");
		जाओ disable_device;
	पूर्ण

	वापस 0;

disable_device:
	pci_clear_master(hdev->pdev);
	pci_disable_device(hdev->pdev);

	वापस rc;
पूर्ण

अटल पूर्णांक device_समाप्त_खोलो_processes(काष्ठा hl_device *hdev, u32 समयout)
अणु
	काष्ठा hl_fpriv	*hpriv;
	काष्ठा task_काष्ठा *task = शून्य;
	u32 pending_cnt;


	/* Giving समय क्रम user to बंद FD, and क्रम processes that are inside
	 * hl_device_खोलो to finish
	 */
	अगर (!list_empty(&hdev->fpriv_list))
		ssleep(1);

	अगर (समयout) अणु
		pending_cnt = समयout;
	पूर्ण अन्यथा अणु
		अगर (hdev->process_समाप्त_trial_cnt) अणु
			/* Processes have been alपढ़ोy समाप्तed */
			pending_cnt = 1;
			जाओ रुको_क्रम_processes;
		पूर्ण अन्यथा अणु
			/* Wait a small period after process समाप्त */
			pending_cnt = HL_PENDING_RESET_PER_SEC;
		पूर्ण
	पूर्ण

	mutex_lock(&hdev->fpriv_list_lock);

	/* This section must be रक्षित because we are dereferencing
	 * poपूर्णांकers that are मुक्तd अगर the process निकासs
	 */
	list_क्रम_each_entry(hpriv, &hdev->fpriv_list, dev_node) अणु
		task = get_pid_task(hpriv->taskpid, PIDTYPE_PID);
		अगर (task) अणु
			dev_info(hdev->dev, "Killing user process pid=%d\n",
				task_pid_nr(task));
			send_sig(SIGKILL, task, 1);
			usleep_range(1000, 10000);

			put_task_काष्ठा(task);
		पूर्ण
	पूर्ण

	mutex_unlock(&hdev->fpriv_list_lock);

	/*
	 * We समाप्तed the खोलो users, but that करोesn't mean they are बंदd.
	 * It could be that they are running a दीर्घ cleanup phase in the driver
	 * e.g. MMU unmappings, or running other दीर्घ tearकरोwn flow even beक्रमe
	 * our cleanup.
	 * Thereक्रमe we need to रुको again to make sure they are बंदd beक्रमe
	 * continuing with the reset.
	 */

रुको_क्रम_processes:
	जबतक ((!list_empty(&hdev->fpriv_list)) && (pending_cnt)) अणु
		dev_dbg(hdev->dev,
			"Waiting for all unmap operations to finish before hard reset\n");

		pending_cnt--;

		ssleep(1);
	पूर्ण

	/* All processes निकासed successfully */
	अगर (list_empty(&hdev->fpriv_list))
		वापस 0;

	/* Give up रुकोing क्रम processes to निकास */
	अगर (hdev->process_समाप्त_trial_cnt == HL_PENDING_RESET_MAX_TRIALS)
		वापस -ETIME;

	hdev->process_समाप्त_trial_cnt++;

	वापस -EBUSY;
पूर्ण

अटल व्योम device_disable_खोलो_processes(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_fpriv *hpriv;

	mutex_lock(&hdev->fpriv_list_lock);
	list_क्रम_each_entry(hpriv, &hdev->fpriv_list, dev_node)
		hpriv->hdev = शून्य;
	mutex_unlock(&hdev->fpriv_list_lock);
पूर्ण

/*
 * hl_device_reset - reset the device
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 * @flags: reset flags.
 *
 * Block future CS and रुको क्रम pending CS to be enqueued
 * Call ASIC H/W fini
 * Flush all completions
 * Re-initialize all पूर्णांकernal data काष्ठाures
 * Call ASIC H/W init, late_init
 * Test queues
 * Enable device
 *
 * Returns 0 क्रम success or an error on failure.
 */
पूर्णांक hl_device_reset(काष्ठा hl_device *hdev, u32 flags)
अणु
	u64 idle_mask[HL_BUSY_ENGINES_MASK_EXT_SIZE] = अणु0पूर्ण;
	bool hard_reset, from_hard_reset_thपढ़ो;
	पूर्णांक i, rc;

	अगर (!hdev->init_करोne) अणु
		dev_err(hdev->dev,
			"Can't reset before initialization is done\n");
		वापस 0;
	पूर्ण

	hard_reset = (flags & HL_RESET_HARD) != 0;
	from_hard_reset_thपढ़ो = (flags & HL_RESET_FROM_RESET_THREAD) != 0;

	अगर ((!hard_reset) && (!hdev->supports_soft_reset)) अणु
		dev_dbg(hdev->dev, "Doing hard-reset instead of soft-reset\n");
		hard_reset = true;
	पूर्ण

	/* Re-entry of reset thपढ़ो */
	अगर (from_hard_reset_thपढ़ो && hdev->process_समाप्त_trial_cnt)
		जाओ समाप्त_processes;

	/*
	 * Prevent concurrency in this function - only one reset should be
	 * करोne at any given समय. Only need to perक्रमm this अगर we didn't
	 * get from the dedicated hard reset thपढ़ो
	 */
	अगर (!from_hard_reset_thपढ़ो) अणु
		/* Block future CS/VM/JOB completion operations */
		rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
		अगर (rc)
			वापस 0;

		/*
		 * अगर reset is due to heartbeat, device CPU is no responsive in
		 * which हाल no poपूर्णांक sending PCI disable message to it
		 */
		अगर (hard_reset && !(flags & HL_RESET_HEARTBEAT)) अणु
			/* Disable PCI access from device F/W so he won't send
			 * us additional पूर्णांकerrupts. We disable MSI/MSI-X at
			 * the halt_engines function and we can't have the F/W
			 * sending us पूर्णांकerrupts after that. We need to disable
			 * the access here because अगर the device is marked
			 * disable, the message won't be send. Also, in हाल
			 * of heartbeat, the device CPU is marked as disable
			 * so this message won't be sent
			 */
			अगर (hl_fw_send_pci_access_msg(hdev,
					CPUCP_PACKET_DISABLE_PCI_ACCESS))
				dev_warn(hdev->dev,
					"Failed to disable PCI access by F/W\n");
		पूर्ण

		/* This also blocks future CS/VM/JOB completion operations */
		hdev->disabled = true;

		/* Flush anyone that is inside the critical section of enqueue
		 * jobs to the H/W
		 */
		hdev->asic_funcs->hw_queues_lock(hdev);
		hdev->asic_funcs->hw_queues_unlock(hdev);

		/* Flush anyone that is inside device खोलो */
		mutex_lock(&hdev->fpriv_list_lock);
		mutex_unlock(&hdev->fpriv_list_lock);

		dev_err(hdev->dev, "Going to RESET device!\n");
	पूर्ण

again:
	अगर ((hard_reset) && (!from_hard_reset_thपढ़ो)) अणु
		hdev->hard_reset_pending = true;

		hdev->process_समाप्त_trial_cnt = 0;

		/*
		 * Because the reset function can't run from पूर्णांकerrupt or
		 * from heartbeat work, we need to call the reset function
		 * from a dedicated work
		 */
		queue_delayed_work(hdev->device_reset_work.wq,
			&hdev->device_reset_work.reset_work, 0);

		वापस 0;
	पूर्ण

	अगर (hard_reset) अणु
		device_late_fini(hdev);

		/*
		 * Now that the heartbeat thपढ़ो is बंदd, flush processes
		 * which are sending messages to CPU
		 */
		mutex_lock(&hdev->send_cpu_message_lock);
		mutex_unlock(&hdev->send_cpu_message_lock);
	पूर्ण

	/*
	 * Halt the engines and disable पूर्णांकerrupts so we won't get any more
	 * completions from H/W and we won't have any accesses from the
	 * H/W to the host machine
	 */
	hdev->asic_funcs->halt_engines(hdev, hard_reset);

	/* Go over all the queues, release all CS and their jobs */
	hl_cs_rollback_all(hdev);

	/* Release all pending user पूर्णांकerrupts, each pending user पूर्णांकerrupt
	 * holds a reference to user context
	 */
	hl_release_pending_user_पूर्णांकerrupts(hdev);

समाप्त_processes:
	अगर (hard_reset) अणु
		/* Kill processes here after CS rollback. This is because the
		 * process can't really निकास until all its CSs are करोne, which
		 * is what we करो in cs rollback
		 */
		rc = device_समाप्त_खोलो_processes(hdev, 0);

		अगर (rc == -EBUSY) अणु
			अगर (hdev->device_fini_pending) अणु
				dev_crit(hdev->dev,
					"Failed to kill all open processes, stopping hard reset\n");
				जाओ out_err;
			पूर्ण

			/* संकेत reset thपढ़ो to reschedule */
			वापस rc;
		पूर्ण

		अगर (rc) अणु
			dev_crit(hdev->dev,
				"Failed to kill all open processes, stopping hard reset\n");
			जाओ out_err;
		पूर्ण

		/* Flush the Event queue workers to make sure no other thपढ़ो is
		 * पढ़ोing or writing to रेजिस्टरs during the reset
		 */
		flush_workqueue(hdev->eq_wq);
	पूर्ण

	/* Reset the H/W. It will be in idle state after this वापसs */
	hdev->asic_funcs->hw_fini(hdev, hard_reset);

	अगर (hard_reset) अणु
		/* Release kernel context */
		अगर (hdev->kernel_ctx && hl_ctx_put(hdev->kernel_ctx) == 1)
			hdev->kernel_ctx = शून्य;
		hl_vm_fini(hdev);
		hl_mmu_fini(hdev);
		hl_eq_reset(hdev, &hdev->event_queue);
	पूर्ण

	/* Re-initialize PI,CI to 0 in all queues (hw queue, cq) */
	hl_hw_queue_reset(hdev, hard_reset);
	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		hl_cq_reset(hdev, &hdev->completion_queue[i]);

	mutex_lock(&hdev->fpriv_list_lock);

	/* Make sure the context चयन phase will run again */
	अगर (hdev->compute_ctx) अणु
		atomic_set(&hdev->compute_ctx->thपढ़ो_ctx_चयन_token, 1);
		hdev->compute_ctx->thपढ़ो_ctx_चयन_रुको_token = 0;
	पूर्ण

	mutex_unlock(&hdev->fpriv_list_lock);

	/* Finished tear-करोwn, starting to re-initialize */

	अगर (hard_reset) अणु
		hdev->device_cpu_disabled = false;
		hdev->hard_reset_pending = false;

		अगर (hdev->kernel_ctx) अणु
			dev_crit(hdev->dev,
				"kernel ctx was alive during hard reset, something is terribly wrong\n");
			rc = -EBUSY;
			जाओ out_err;
		पूर्ण

		rc = hl_mmu_init(hdev);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to initialize MMU S/W after hard reset\n");
			जाओ out_err;
		पूर्ण

		/* Allocate the kernel context */
		hdev->kernel_ctx = kzalloc(माप(*hdev->kernel_ctx),
						GFP_KERNEL);
		अगर (!hdev->kernel_ctx) अणु
			rc = -ENOMEM;
			hl_mmu_fini(hdev);
			जाओ out_err;
		पूर्ण

		hdev->compute_ctx = शून्य;

		rc = hl_ctx_init(hdev, hdev->kernel_ctx, true);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"failed to init kernel ctx in hard reset\n");
			kमुक्त(hdev->kernel_ctx);
			hdev->kernel_ctx = शून्य;
			hl_mmu_fini(hdev);
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* Device is now enabled as part of the initialization requires
	 * communication with the device firmware to get inक्रमmation that
	 * is required क्रम the initialization itself
	 */
	hdev->disabled = false;

	rc = hdev->asic_funcs->hw_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"failed to initialize the H/W after reset\n");
		जाओ out_err;
	पूर्ण

	/* If device is not idle fail the reset process */
	अगर (!hdev->asic_funcs->is_device_idle(hdev, idle_mask,
			HL_BUSY_ENGINES_MASK_EXT_SIZE, शून्य)) अणु
		dev_err(hdev->dev,
			"device is not idle (mask %#llx %#llx) after reset\n",
			idle_mask[0], idle_mask[1]);
		rc = -EIO;
		जाओ out_err;
	पूर्ण

	/* Check that the communication with the device is working */
	rc = hdev->asic_funcs->test_queues(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to detect if device is alive after reset\n");
		जाओ out_err;
	पूर्ण

	अगर (hard_reset) अणु
		rc = device_late_init(hdev);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed late init after hard reset\n");
			जाओ out_err;
		पूर्ण

		rc = hl_vm_init(hdev);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to init memory module after hard reset\n");
			जाओ out_err;
		पूर्ण

		hl_set_max_घातer(hdev);
	पूर्ण अन्यथा अणु
		rc = hdev->asic_funcs->soft_reset_late_init(hdev);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed late init after soft reset\n");
			जाओ out_err;
		पूर्ण
	पूर्ण

	atomic_set(&hdev->in_reset, 0);
	hdev->needs_reset = false;

	dev_notice(hdev->dev, "Successfully finished resetting the device\n");

	अगर (hard_reset) अणु
		hdev->hard_reset_cnt++;

		/* After reset is करोne, we are पढ़ोy to receive events from
		 * the F/W. We can't करो it beक्रमe because we will ignore events
		 * and अगर those events are fatal, we won't know about it and
		 * the device will be operational although it shouldn't be
		 */
		hdev->asic_funcs->enable_events_from_fw(hdev);
	पूर्ण अन्यथा अणु
		hdev->soft_reset_cnt++;
	पूर्ण

	वापस 0;

out_err:
	hdev->disabled = true;

	अगर (hard_reset) अणु
		dev_err(hdev->dev,
			"Failed to reset! Device is NOT usable\n");
		hdev->hard_reset_cnt++;
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev,
			"Failed to do soft-reset, trying hard reset\n");
		hdev->soft_reset_cnt++;
		hard_reset = true;
		जाओ again;
	पूर्ण

	atomic_set(&hdev->in_reset, 0);

	वापस rc;
पूर्ण

/*
 * hl_device_init - मुख्य initialization function क्रम habanaद_असल device
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 * Allocate an id क्रम the device, करो early initialization and then call the
 * ASIC specअगरic initialization functions. Finally, create the cdev and the
 * Linux device to expose it to the user
 */
पूर्णांक hl_device_init(काष्ठा hl_device *hdev, काष्ठा class *hclass)
अणु
	पूर्णांक i, rc, cq_cnt, user_पूर्णांकerrupt_cnt, cq_पढ़ोy_cnt;
	अक्षर *name;
	bool add_cdev_sysfs_on_err = false;

	name = kaप्र_लिखो(GFP_KERNEL, "hl%d", hdev->id / 2);
	अगर (!name) अणु
		rc = -ENOMEM;
		जाओ out_disabled;
	पूर्ण

	/* Initialize cdev and device काष्ठाures */
	rc = device_init_cdev(hdev, hclass, hdev->id, &hl_ops, name,
				&hdev->cdev, &hdev->dev);

	kमुक्त(name);

	अगर (rc)
		जाओ out_disabled;

	name = kaप्र_लिखो(GFP_KERNEL, "hl_controlD%d", hdev->id / 2);
	अगर (!name) अणु
		rc = -ENOMEM;
		जाओ मुक्त_dev;
	पूर्ण

	/* Initialize cdev and device काष्ठाures क्रम control device */
	rc = device_init_cdev(hdev, hclass, hdev->id_control, &hl_ctrl_ops,
				name, &hdev->cdev_ctrl, &hdev->dev_ctrl);

	kमुक्त(name);

	अगर (rc)
		जाओ मुक्त_dev;

	/* Initialize ASIC function poपूर्णांकers and perक्रमm early init */
	rc = device_early_init(hdev);
	अगर (rc)
		जाओ मुक्त_dev_ctrl;

	user_पूर्णांकerrupt_cnt = hdev->asic_prop.user_पूर्णांकerrupt_count;

	अगर (user_पूर्णांकerrupt_cnt) अणु
		hdev->user_पूर्णांकerrupt = kसुस्मृति(user_पूर्णांकerrupt_cnt,
				माप(*hdev->user_पूर्णांकerrupt),
				GFP_KERNEL);

		अगर (!hdev->user_पूर्णांकerrupt) अणु
			rc = -ENOMEM;
			जाओ early_fini;
		पूर्ण
	पूर्ण

	/*
	 * Start calling ASIC initialization. First S/W then H/W and finally
	 * late init
	 */
	rc = hdev->asic_funcs->sw_init(hdev);
	अगर (rc)
		जाओ user_पूर्णांकerrupts_fini;

	/*
	 * Initialize the H/W queues. Must be करोne beक्रमe hw_init, because
	 * there the addresses of the kernel queue are being written to the
	 * रेजिस्टरs of the device
	 */
	rc = hl_hw_queues_create(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize kernel queues\n");
		जाओ sw_fini;
	पूर्ण

	cq_cnt = hdev->asic_prop.completion_queues_count;

	/*
	 * Initialize the completion queues. Must be करोne beक्रमe hw_init,
	 * because there the addresses of the completion queues are being
	 * passed as arguments to request_irq
	 */
	अगर (cq_cnt) अणु
		hdev->completion_queue = kसुस्मृति(cq_cnt,
				माप(*hdev->completion_queue),
				GFP_KERNEL);

		अगर (!hdev->completion_queue) अणु
			dev_err(hdev->dev,
				"failed to allocate completion queues\n");
			rc = -ENOMEM;
			जाओ hw_queues_destroy;
		पूर्ण
	पूर्ण

	क्रम (i = 0, cq_पढ़ोy_cnt = 0 ; i < cq_cnt ; i++, cq_पढ़ोy_cnt++) अणु
		rc = hl_cq_init(hdev, &hdev->completion_queue[i],
				hdev->asic_funcs->get_queue_id_क्रम_cq(hdev, i));
		अगर (rc) अणु
			dev_err(hdev->dev,
				"failed to initialize completion queue\n");
			जाओ cq_fini;
		पूर्ण
		hdev->completion_queue[i].cq_idx = i;
	पूर्ण

	/*
	 * Initialize the event queue. Must be करोne beक्रमe hw_init,
	 * because there the address of the event queue is being
	 * passed as argument to request_irq
	 */
	rc = hl_eq_init(hdev, &hdev->event_queue);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize event queue\n");
		जाओ cq_fini;
	पूर्ण

	/* MMU S/W must be initialized beक्रमe kernel context is created */
	rc = hl_mmu_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to initialize MMU S/W structures\n");
		जाओ eq_fini;
	पूर्ण

	/* Allocate the kernel context */
	hdev->kernel_ctx = kzalloc(माप(*hdev->kernel_ctx), GFP_KERNEL);
	अगर (!hdev->kernel_ctx) अणु
		rc = -ENOMEM;
		जाओ mmu_fini;
	पूर्ण

	hdev->compute_ctx = शून्य;

	hl_debugfs_add_device(hdev);

	/* debugfs nodes are created in hl_ctx_init so it must be called after
	 * hl_debugfs_add_device.
	 */
	rc = hl_ctx_init(hdev, hdev->kernel_ctx, true);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize kernel context\n");
		kमुक्त(hdev->kernel_ctx);
		जाओ हटाओ_device_from_debugfs;
	पूर्ण

	rc = hl_cb_pool_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize CB pool\n");
		जाओ release_ctx;
	पूर्ण

	/*
	 * From this poपूर्णांक, in हाल of an error, add अक्षर devices and create
	 * sysfs nodes as part of the error flow, to allow debugging.
	 */
	add_cdev_sysfs_on_err = true;

	/* Device is now enabled as part of the initialization requires
	 * communication with the device firmware to get inक्रमmation that
	 * is required क्रम the initialization itself
	 */
	hdev->disabled = false;

	rc = hdev->asic_funcs->hw_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to initialize the H/W\n");
		rc = 0;
		जाओ out_disabled;
	पूर्ण

	/* Check that the communication with the device is working */
	rc = hdev->asic_funcs->test_queues(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to detect if device is alive\n");
		rc = 0;
		जाओ out_disabled;
	पूर्ण

	rc = device_late_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed late initialization\n");
		rc = 0;
		जाओ out_disabled;
	पूर्ण

	dev_info(hdev->dev, "Found %s device with %lluGB DRAM\n",
		hdev->asic_name,
		hdev->asic_prop.dram_size / 1024 / 1024 / 1024);

	rc = hl_vm_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to initialize memory module\n");
		rc = 0;
		जाओ out_disabled;
	पूर्ण

	/*
	 * Expose devices and sysfs nodes to user.
	 * From here there is no need to add अक्षर devices and create sysfs nodes
	 * in हाल of an error.
	 */
	add_cdev_sysfs_on_err = false;
	rc = device_cdev_sysfs_add(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to add char devices and sysfs nodes\n");
		rc = 0;
		जाओ out_disabled;
	पूर्ण

	/* Need to call this again because the max घातer might change,
	 * depending on card type क्रम certain ASICs
	 */
	hl_set_max_घातer(hdev);

	/*
	 * hl_hwmon_init() must be called after device_late_init(), because only
	 * there we get the inक्रमmation from the device about which
	 * hwmon-related sensors the device supports.
	 * Furthermore, it must be करोne after adding the device to the प्रणाली.
	 */
	rc = hl_hwmon_init(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to initialize hwmon\n");
		rc = 0;
		जाओ out_disabled;
	पूर्ण

	dev_notice(hdev->dev,
		"Successfully added device to habanalabs driver\n");

	hdev->init_करोne = true;

	/* After initialization is करोne, we are पढ़ोy to receive events from
	 * the F/W. We can't करो it beक्रमe because we will ignore events and अगर
	 * those events are fatal, we won't know about it and the device will
	 * be operational although it shouldn't be
	 */
	hdev->asic_funcs->enable_events_from_fw(hdev);

	वापस 0;

release_ctx:
	अगर (hl_ctx_put(hdev->kernel_ctx) != 1)
		dev_err(hdev->dev,
			"kernel ctx is still alive on initialization failure\n");
हटाओ_device_from_debugfs:
	hl_debugfs_हटाओ_device(hdev);
mmu_fini:
	hl_mmu_fini(hdev);
eq_fini:
	hl_eq_fini(hdev, &hdev->event_queue);
cq_fini:
	क्रम (i = 0 ; i < cq_पढ़ोy_cnt ; i++)
		hl_cq_fini(hdev, &hdev->completion_queue[i]);
	kमुक्त(hdev->completion_queue);
hw_queues_destroy:
	hl_hw_queues_destroy(hdev);
sw_fini:
	hdev->asic_funcs->sw_fini(hdev);
user_पूर्णांकerrupts_fini:
	kमुक्त(hdev->user_पूर्णांकerrupt);
early_fini:
	device_early_fini(hdev);
मुक्त_dev_ctrl:
	put_device(hdev->dev_ctrl);
मुक्त_dev:
	put_device(hdev->dev);
out_disabled:
	hdev->disabled = true;
	अगर (add_cdev_sysfs_on_err)
		device_cdev_sysfs_add(hdev);
	अगर (hdev->pdev)
		dev_err(&hdev->pdev->dev,
			"Failed to initialize hl%d. Device is NOT usable !\n",
			hdev->id / 2);
	अन्यथा
		pr_err("Failed to initialize hl%d. Device is NOT usable !\n",
			hdev->id / 2);

	वापस rc;
पूर्ण

/*
 * hl_device_fini - मुख्य tear-करोwn function क्रम habanaद_असल device
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 *
 * Destroy the device, call ASIC fini functions and release the id
 */
व्योम hl_device_fini(काष्ठा hl_device *hdev)
अणु
	kसमय_प्रकार समयout;
	पूर्णांक i, rc;

	dev_info(hdev->dev, "Removing device\n");

	hdev->device_fini_pending = 1;
	flush_delayed_work(&hdev->device_reset_work.reset_work);

	/*
	 * This function is competing with the reset function, so try to
	 * take the reset atomic and अगर we are alपढ़ोy in middle of reset,
	 * रुको until reset function is finished. Reset function is deचिन्हित
	 * to always finish. However, in Gaudi, because of all the network
	 * ports, the hard reset could take between 10-30 seconds
	 */

	समयout = kसमय_add_us(kसमय_get(),
				HL_HARD_RESET_MAX_TIMEOUT * 1000 * 1000);
	rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
	जबतक (rc) अणु
		usleep_range(50, 200);
		rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
		अगर (kसमय_compare(kसमय_get(), समयout) > 0) अणु
			dev_crit(hdev->dev,
				"Failed to remove device because reset function did not finish\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Disable PCI access from device F/W so it won't send us additional
	 * पूर्णांकerrupts. We disable MSI/MSI-X at the halt_engines function and we
	 * can't have the F/W sending us पूर्णांकerrupts after that. We need to
	 * disable the access here because अगर the device is marked disable, the
	 * message won't be send. Also, in हाल of heartbeat, the device CPU is
	 * marked as disable so this message won't be sent
	 */
	hl_fw_send_pci_access_msg(hdev,	CPUCP_PACKET_DISABLE_PCI_ACCESS);

	/* Mark device as disabled */
	hdev->disabled = true;

	/* Flush anyone that is inside the critical section of enqueue
	 * jobs to the H/W
	 */
	hdev->asic_funcs->hw_queues_lock(hdev);
	hdev->asic_funcs->hw_queues_unlock(hdev);

	/* Flush anyone that is inside device खोलो */
	mutex_lock(&hdev->fpriv_list_lock);
	mutex_unlock(&hdev->fpriv_list_lock);

	hdev->hard_reset_pending = true;

	hl_hwmon_fini(hdev);

	device_late_fini(hdev);

	/*
	 * Halt the engines and disable पूर्णांकerrupts so we won't get any more
	 * completions from H/W and we won't have any accesses from the
	 * H/W to the host machine
	 */
	hdev->asic_funcs->halt_engines(hdev, true);

	/* Go over all the queues, release all CS and their jobs */
	hl_cs_rollback_all(hdev);

	/* Kill processes here after CS rollback. This is because the process
	 * can't really निकास until all its CSs are करोne, which is what we
	 * करो in cs rollback
	 */
	dev_info(hdev->dev,
		"Waiting for all processes to exit (timeout of %u seconds)",
		HL_PENDING_RESET_LONG_SEC);

	rc = device_समाप्त_खोलो_processes(hdev, HL_PENDING_RESET_LONG_SEC);
	अगर (rc) अणु
		dev_crit(hdev->dev, "Failed to kill all open processes\n");
		device_disable_खोलो_processes(hdev);
	पूर्ण

	hl_cb_pool_fini(hdev);

	/* Reset the H/W. It will be in idle state after this वापसs */
	hdev->asic_funcs->hw_fini(hdev, true);

	/* Release kernel context */
	अगर ((hdev->kernel_ctx) && (hl_ctx_put(hdev->kernel_ctx) != 1))
		dev_err(hdev->dev, "kernel ctx is still alive\n");

	hl_debugfs_हटाओ_device(hdev);

	hl_vm_fini(hdev);

	hl_mmu_fini(hdev);

	hl_eq_fini(hdev, &hdev->event_queue);

	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		hl_cq_fini(hdev, &hdev->completion_queue[i]);
	kमुक्त(hdev->completion_queue);
	kमुक्त(hdev->user_पूर्णांकerrupt);

	hl_hw_queues_destroy(hdev);

	/* Call ASIC S/W finalize function */
	hdev->asic_funcs->sw_fini(hdev);

	device_early_fini(hdev);

	/* Hide devices and sysfs nodes from user */
	device_cdev_sysfs_del(hdev);

	pr_info("removed device successfully\n");
पूर्ण

/*
 * MMIO रेजिस्टर access helper functions.
 */

/*
 * hl_rreg - Read an MMIO रेजिस्टर
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 * @reg: MMIO रेजिस्टर offset (in bytes)
 *
 * Returns the value of the MMIO रेजिस्टर we are asked to पढ़ो
 *
 */
अंतरभूत u32 hl_rreg(काष्ठा hl_device *hdev, u32 reg)
अणु
	वापस पढ़ोl(hdev->rmmio + reg);
पूर्ण

/*
 * hl_wreg - Write to an MMIO रेजिस्टर
 *
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 * @reg: MMIO रेजिस्टर offset (in bytes)
 * @val: 32-bit value
 *
 * Writes the 32-bit value पूर्णांकo the MMIO रेजिस्टर
 *
 */
अंतरभूत व्योम hl_wreg(काष्ठा hl_device *hdev, u32 reg, u32 val)
अणु
	ग_लिखोl(val, hdev->rmmio + reg);
पूर्ण
