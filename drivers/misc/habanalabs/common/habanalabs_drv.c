<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#घोषणा pr_fmt(fmt)		"habanalabs: " fmt

#समावेश "habanalabs.h"

#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/module.h>

#घोषणा HL_DRIVER_AUTHOR	"HabanaLabs Kernel Driver Team"

#घोषणा HL_DRIVER_DESC		"Driver for HabanaLabs's AI Accelerators"

MODULE_AUTHOR(HL_DRIVER_AUTHOR);
MODULE_DESCRIPTION(HL_DRIVER_DESC);
MODULE_LICENSE("GPL v2");

अटल पूर्णांक hl_major;
अटल काष्ठा class *hl_class;
अटल DEFINE_IDR(hl_devs_idr);
अटल DEFINE_MUTEX(hl_devs_idr_lock);

अटल पूर्णांक समयout_locked = 30;
अटल पूर्णांक reset_on_lockup = 1;
अटल पूर्णांक memory_scrub = 1;
अटल uदीर्घ boot_error_status_mask = अच_दीर्घ_उच्च;

module_param(समयout_locked, पूर्णांक, 0444);
MODULE_PARM_DESC(समयout_locked,
	"Device lockup timeout in seconds (0 = disabled, default 30s)");

module_param(reset_on_lockup, पूर्णांक, 0444);
MODULE_PARM_DESC(reset_on_lockup,
	"Do device reset on lockup (0 = no, 1 = yes, default yes)");

module_param(memory_scrub, पूर्णांक, 0444);
MODULE_PARM_DESC(memory_scrub,
	"Scrub device memory in various states (0 = no, 1 = yes, default yes)");

module_param(boot_error_status_mask, uदीर्घ, 0444);
MODULE_PARM_DESC(boot_error_status_mask,
	"Mask of the error status during device CPU boot (If bitX is cleared then error X is masked. Default all 1's)");

#घोषणा PCI_VENDOR_ID_HABANALABS	0x1da3

#घोषणा PCI_IDS_GOYA			0x0001
#घोषणा PCI_IDS_GAUDI			0x1000
#घोषणा PCI_IDS_GAUDI_SEC		0x1010

अटल स्थिर काष्ठा pci_device_id ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HABANALABS, PCI_IDS_GOYA), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HABANALABS, PCI_IDS_GAUDI), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HABANALABS, PCI_IDS_GAUDI_SEC), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ids);

/*
 * get_asic_type - translate device id to asic type
 *
 * @device: id of the PCI device
 *
 * Translate device id to asic type.
 * In हाल of unidentअगरied device, वापस -1
 */
अटल क्रमागत hl_asic_type get_asic_type(u16 device)
अणु
	क्रमागत hl_asic_type asic_type;

	चयन (device) अणु
	हाल PCI_IDS_GOYA:
		asic_type = ASIC_GOYA;
		अवरोध;
	हाल PCI_IDS_GAUDI:
		asic_type = ASIC_GAUDI;
		अवरोध;
	हाल PCI_IDS_GAUDI_SEC:
		asic_type = ASIC_GAUDI_SEC;
		अवरोध;
	शेष:
		asic_type = ASIC_INVALID;
		अवरोध;
	पूर्ण

	वापस asic_type;
पूर्ण

अटल bool is_asic_secured(क्रमागत hl_asic_type asic_type)
अणु
	चयन (asic_type) अणु
	हाल ASIC_GAUDI_SEC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * hl_device_खोलो - खोलो function क्रम habanaद_असल device
 *
 * @inode: poपूर्णांकer to inode काष्ठाure
 * @filp: poपूर्णांकer to file काष्ठाure
 *
 * Called when process खोलोs an habanaद_असल device.
 */
पूर्णांक hl_device_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	क्रमागत hl_device_status status;
	काष्ठा hl_device *hdev;
	काष्ठा hl_fpriv *hpriv;
	पूर्णांक rc;

	mutex_lock(&hl_devs_idr_lock);
	hdev = idr_find(&hl_devs_idr, iminor(inode));
	mutex_unlock(&hl_devs_idr_lock);

	अगर (!hdev) अणु
		pr_err("Couldn't find device %d:%d\n",
			imajor(inode), iminor(inode));
		वापस -ENXIO;
	पूर्ण

	hpriv = kzalloc(माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;

	hpriv->hdev = hdev;
	filp->निजी_data = hpriv;
	hpriv->filp = filp;
	mutex_init(&hpriv->restore_phase_mutex);
	kref_init(&hpriv->refcount);
	nonseekable_खोलो(inode, filp);

	hl_cb_mgr_init(&hpriv->cb_mgr);
	hl_ctx_mgr_init(&hpriv->ctx_mgr);

	hpriv->taskpid = find_get_pid(current->pid);

	mutex_lock(&hdev->fpriv_list_lock);

	अगर (!hl_device_operational(hdev, &status)) अणु
		dev_err_ratelimited(hdev->dev,
			"Can't open %s because it is %s\n",
			dev_name(hdev->dev), hdev->status[status]);
		rc = -EPERM;
		जाओ out_err;
	पूर्ण

	अगर (hdev->in_debug) अणु
		dev_err_ratelimited(hdev->dev,
			"Can't open %s because it is being debugged by another user\n",
			dev_name(hdev->dev));
		rc = -EPERM;
		जाओ out_err;
	पूर्ण

	अगर (hdev->compute_ctx) अणु
		dev_dbg_ratelimited(hdev->dev,
			"Can't open %s because another user is working on it\n",
			dev_name(hdev->dev));
		rc = -EBUSY;
		जाओ out_err;
	पूर्ण

	rc = hl_ctx_create(hdev, hpriv);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to create context %d\n", rc);
		जाओ out_err;
	पूर्ण

	/* Device is IDLE at this poपूर्णांक so it is legal to change PLLs.
	 * There is no need to check anything because अगर the PLL is
	 * alपढ़ोy HIGH, the set function will वापस without करोing
	 * anything
	 */
	hl_device_set_frequency(hdev, PLL_HIGH);

	list_add(&hpriv->dev_node, &hdev->fpriv_list);
	mutex_unlock(&hdev->fpriv_list_lock);

	hl_debugfs_add_file(hpriv);

	वापस 0;

out_err:
	mutex_unlock(&hdev->fpriv_list_lock);

	hl_cb_mgr_fini(hpriv->hdev, &hpriv->cb_mgr);
	hl_ctx_mgr_fini(hpriv->hdev, &hpriv->ctx_mgr);
	filp->निजी_data = शून्य;
	mutex_destroy(&hpriv->restore_phase_mutex);
	put_pid(hpriv->taskpid);

	kमुक्त(hpriv);

	वापस rc;
पूर्ण

पूर्णांक hl_device_खोलो_ctrl(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा hl_device *hdev;
	काष्ठा hl_fpriv *hpriv;
	पूर्णांक rc;

	mutex_lock(&hl_devs_idr_lock);
	hdev = idr_find(&hl_devs_idr, iminor(inode));
	mutex_unlock(&hl_devs_idr_lock);

	अगर (!hdev) अणु
		pr_err("Couldn't find device %d:%d\n",
			imajor(inode), iminor(inode));
		वापस -ENXIO;
	पूर्ण

	hpriv = kzalloc(माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;

	mutex_lock(&hdev->fpriv_list_lock);

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		dev_err_ratelimited(hdev->dev_ctrl,
			"Can't open %s because it is disabled or in reset\n",
			dev_name(hdev->dev_ctrl));
		rc = -EPERM;
		जाओ out_err;
	पूर्ण

	list_add(&hpriv->dev_node, &hdev->fpriv_list);
	mutex_unlock(&hdev->fpriv_list_lock);

	hpriv->hdev = hdev;
	filp->निजी_data = hpriv;
	hpriv->filp = filp;
	hpriv->is_control = true;
	nonseekable_खोलो(inode, filp);

	hpriv->taskpid = find_get_pid(current->pid);

	वापस 0;

out_err:
	mutex_unlock(&hdev->fpriv_list_lock);
	kमुक्त(hpriv);
	वापस rc;
पूर्ण

अटल व्योम set_driver_behavior_per_device(काष्ठा hl_device *hdev)
अणु
	hdev->fw_components = FW_TYPE_ALL_TYPES;
	hdev->cpu_queues_enable = 1;
	hdev->heartbeat = 1;
	hdev->mmu_enable = 1;
	hdev->घड़ी_gating_mask = अच_दीर्घ_उच्च;
	hdev->sram_scrambler_enable = 1;
	hdev->dram_scrambler_enable = 1;
	hdev->bmc_enable = 1;
	hdev->hard_reset_on_fw_events = 1;
	hdev->reset_on_preboot_fail = 1;

	hdev->reset_pcilink = 0;
	hdev->axi_drain = 0;
पूर्ण

/*
 * create_hdev - create habanaद_असल device instance
 *
 * @dev: will hold the poपूर्णांकer to the new habanaद_असल device काष्ठाure
 * @pdev: poपूर्णांकer to the pci device
 * @asic_type: in हाल of simulator device, which device is it
 * @minor: in हाल of simulator device, the minor of the device
 *
 * Allocate memory क्रम habanaद_असल device and initialize basic fields
 * Identअगरy the ASIC type
 * Allocate ID (minor) क्रम the device (only क्रम real devices)
 */
पूर्णांक create_hdev(काष्ठा hl_device **dev, काष्ठा pci_dev *pdev,
		क्रमागत hl_asic_type asic_type, पूर्णांक minor)
अणु
	काष्ठा hl_device *hdev;
	पूर्णांक rc, मुख्य_id, ctrl_id = 0;

	*dev = शून्य;

	hdev = kzalloc(माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;

	/* First, we must find out which ASIC are we handling. This is needed
	 * to configure the behavior of the driver (kernel parameters)
	 */
	अगर (pdev) अणु
		hdev->asic_type = get_asic_type(pdev->device);
		अगर (hdev->asic_type == ASIC_INVALID) अणु
			dev_err(&pdev->dev, "Unsupported ASIC\n");
			rc = -ENODEV;
			जाओ मुक्त_hdev;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdev->asic_type = asic_type;
	पूर्ण

	अगर (pdev)
		hdev->asic_prop.fw_security_disabled =
				!is_asic_secured(pdev->device);
	अन्यथा
		hdev->asic_prop.fw_security_disabled = true;

	/* Assign status description string */
	म_नकलन(hdev->status[HL_DEVICE_STATUS_MALFUNCTION],
					"disabled", HL_STR_MAX);
	म_नकलन(hdev->status[HL_DEVICE_STATUS_IN_RESET],
					"in reset", HL_STR_MAX);
	म_नकलन(hdev->status[HL_DEVICE_STATUS_NEEDS_RESET],
					"needs reset", HL_STR_MAX);

	hdev->major = hl_major;
	hdev->reset_on_lockup = reset_on_lockup;
	hdev->memory_scrub = memory_scrub;
	hdev->boot_error_status_mask = boot_error_status_mask;

	hdev->pldm = 0;

	set_driver_behavior_per_device(hdev);

	अगर (समयout_locked)
		hdev->समयout_jअगरfies = msecs_to_jअगरfies(समयout_locked * 1000);
	अन्यथा
		hdev->समयout_jअगरfies = MAX_SCHEDULE_TIMEOUT;

	hdev->disabled = true;
	hdev->pdev = pdev; /* can be शून्य in हाल of simulator device */

	/* Set शेष DMA mask to 32 bits */
	hdev->dma_mask = 32;

	mutex_lock(&hl_devs_idr_lock);

	/* Always save 2 numbers, 1 क्रम मुख्य device and 1 क्रम control.
	 * They must be consecutive
	 */
	मुख्य_id = idr_alloc(&hl_devs_idr, hdev, 0, HL_MAX_MINORS,
				GFP_KERNEL);

	अगर (मुख्य_id >= 0)
		ctrl_id = idr_alloc(&hl_devs_idr, hdev, मुख्य_id + 1,
					मुख्य_id + 2, GFP_KERNEL);

	mutex_unlock(&hl_devs_idr_lock);

	अगर ((मुख्य_id < 0) || (ctrl_id < 0)) अणु
		अगर ((मुख्य_id == -ENOSPC) || (ctrl_id == -ENOSPC))
			pr_err("too many devices in the system\n");

		अगर (मुख्य_id >= 0) अणु
			mutex_lock(&hl_devs_idr_lock);
			idr_हटाओ(&hl_devs_idr, मुख्य_id);
			mutex_unlock(&hl_devs_idr_lock);
		पूर्ण

		rc = -EBUSY;
		जाओ मुक्त_hdev;
	पूर्ण

	hdev->id = मुख्य_id;
	hdev->id_control = ctrl_id;

	*dev = hdev;

	वापस 0;

मुक्त_hdev:
	kमुक्त(hdev);
	वापस rc;
पूर्ण

/*
 * destroy_hdev - destroy habanaद_असल device instance
 *
 * @dev: poपूर्णांकer to the habanaद_असल device काष्ठाure
 *
 */
व्योम destroy_hdev(काष्ठा hl_device *hdev)
अणु
	/* Remove device from the device list */
	mutex_lock(&hl_devs_idr_lock);
	idr_हटाओ(&hl_devs_idr, hdev->id);
	idr_हटाओ(&hl_devs_idr, hdev->id_control);
	mutex_unlock(&hl_devs_idr_lock);

	kमुक्त(hdev);
पूर्ण

अटल पूर्णांक hl_pmops_suspend(काष्ठा device *dev)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	pr_debug("Going to suspend PCI device\n");

	अगर (!hdev) अणु
		pr_err("device pointer is NULL in suspend\n");
		वापस 0;
	पूर्ण

	वापस hl_device_suspend(hdev);
पूर्ण

अटल पूर्णांक hl_pmops_resume(काष्ठा device *dev)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	pr_debug("Going to resume PCI device\n");

	अगर (!hdev) अणु
		pr_err("device pointer is NULL in resume\n");
		वापस 0;
	पूर्ण

	वापस hl_device_resume(hdev);
पूर्ण

/*
 * hl_pci_probe - probe PCI habanaद_असल devices
 *
 * @pdev: poपूर्णांकer to pci device
 * @id: poपूर्णांकer to pci device id काष्ठाure
 *
 * Standard PCI probe function क्रम habanaद_असल device.
 * Create a new habanaद_असल device and initialize it according to the
 * device's type
 */
अटल पूर्णांक hl_pci_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा hl_device *hdev;
	पूर्णांक rc;

	dev_info(&pdev->dev, HL_NAME
		 " device found [%04x:%04x] (rev %x)\n",
		 (पूर्णांक)pdev->venकरोr, (पूर्णांक)pdev->device, (पूर्णांक)pdev->revision);

	rc = create_hdev(&hdev, pdev, ASIC_INVALID, -1);
	अगर (rc)
		वापस rc;

	pci_set_drvdata(pdev, hdev);

	pci_enable_pcie_error_reporting(pdev);

	rc = hl_device_init(hdev, hl_class);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Fatal error during habanalabs device init\n");
		rc = -ENODEV;
		जाओ disable_device;
	पूर्ण

	वापस 0;

disable_device:
	pci_set_drvdata(pdev, शून्य);
	destroy_hdev(hdev);

	वापस rc;
पूर्ण

/*
 * hl_pci_हटाओ - हटाओ PCI habanaद_असल devices
 *
 * @pdev: poपूर्णांकer to pci device
 *
 * Standard PCI हटाओ function क्रम habanaद_असल device
 */
अटल व्योम hl_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hl_device *hdev;

	hdev = pci_get_drvdata(pdev);
	अगर (!hdev)
		वापस;

	hl_device_fini(hdev);
	pci_disable_pcie_error_reporting(pdev);
	pci_set_drvdata(pdev, शून्य);
	destroy_hdev(hdev);
पूर्ण

/**
 * hl_pci_err_detected - a PCI bus error detected on this device
 *
 * @pdev: poपूर्णांकer to pci device
 * @state: PCI error type
 *
 * Called by the PCI subप्रणाली whenever a non-correctable
 * PCI bus error is detected
 */
अटल pci_ers_result_t
hl_pci_err_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा hl_device *hdev = pci_get_drvdata(pdev);
	क्रमागत pci_ers_result result;

	चयन (state) अणु
	हाल pci_channel_io_normal:
		वापस PCI_ERS_RESULT_CAN_RECOVER;

	हाल pci_channel_io_frozen:
		dev_warn(hdev->dev, "frozen state error detected\n");
		result = PCI_ERS_RESULT_NEED_RESET;
		अवरोध;

	हाल pci_channel_io_perm_failure:
		dev_warn(hdev->dev, "failure state error detected\n");
		result = PCI_ERS_RESULT_DISCONNECT;
		अवरोध;

	शेष:
		result = PCI_ERS_RESULT_NONE;
	पूर्ण

	hdev->asic_funcs->halt_engines(hdev, true);

	वापस result;
पूर्ण

/**
 * hl_pci_err_resume - resume after a PCI slot reset
 *
 * @pdev: poपूर्णांकer to pci device
 *
 */
अटल व्योम hl_pci_err_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hl_device *hdev = pci_get_drvdata(pdev);

	dev_warn(hdev->dev, "Resuming device after PCI slot reset\n");
	hl_device_resume(hdev);
पूर्ण

/**
 * hl_pci_err_slot_reset - a PCI slot reset has just happened
 *
 * @pdev: poपूर्णांकer to pci device
 *
 * Determine अगर the driver can recover from the PCI slot reset
 */
अटल pci_ers_result_t hl_pci_err_slot_reset(काष्ठा pci_dev *pdev)
अणु
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hl_pm_ops = अणु
	.suspend = hl_pmops_suspend,
	.resume = hl_pmops_resume,
पूर्ण;

अटल स्थिर काष्ठा pci_error_handlers hl_pci_err_handler = अणु
	.error_detected = hl_pci_err_detected,
	.slot_reset = hl_pci_err_slot_reset,
	.resume = hl_pci_err_resume,
पूर्ण;

अटल काष्ठा pci_driver hl_pci_driver = अणु
	.name = HL_NAME,
	.id_table = ids,
	.probe = hl_pci_probe,
	.हटाओ = hl_pci_हटाओ,
	.shutकरोwn = hl_pci_हटाओ,
	.driver.pm = &hl_pm_ops,
	.err_handler = &hl_pci_err_handler,
पूर्ण;

/*
 * hl_init - Initialize the habanaद_असल kernel driver
 */
अटल पूर्णांक __init hl_init(व्योम)
अणु
	पूर्णांक rc;
	dev_t dev;

	pr_info("loading driver\n");

	rc = alloc_chrdev_region(&dev, 0, HL_MAX_MINORS, HL_NAME);
	अगर (rc < 0) अणु
		pr_err("unable to get major\n");
		वापस rc;
	पूर्ण

	hl_major = MAJOR(dev);

	hl_class = class_create(THIS_MODULE, HL_NAME);
	अगर (IS_ERR(hl_class)) अणु
		pr_err("failed to allocate class\n");
		rc = PTR_ERR(hl_class);
		जाओ हटाओ_major;
	पूर्ण

	hl_debugfs_init();

	rc = pci_रेजिस्टर_driver(&hl_pci_driver);
	अगर (rc) अणु
		pr_err("failed to register pci device\n");
		जाओ हटाओ_debugfs;
	पूर्ण

	pr_debug("driver loaded\n");

	वापस 0;

हटाओ_debugfs:
	hl_debugfs_fini();
	class_destroy(hl_class);
हटाओ_major:
	unरेजिस्टर_chrdev_region(MKDEV(hl_major, 0), HL_MAX_MINORS);
	वापस rc;
पूर्ण

/*
 * hl_निकास - Release all resources of the habanaद_असल kernel driver
 */
अटल व्योम __निकास hl_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hl_pci_driver);

	/*
	 * Removing debugfs must be after all devices or simulator devices
	 * have been हटाओd because otherwise we get a bug in the
	 * debugfs module क्रम referencing शून्य objects
	 */
	hl_debugfs_fini();

	class_destroy(hl_class);
	unरेजिस्टर_chrdev_region(MKDEV(hl_major, 0), HL_MAX_MINORS);

	idr_destroy(&hl_devs_idr);

	pr_debug("driver removed\n");
पूर्ण

module_init(hl_init);
module_निकास(hl_निकास);
