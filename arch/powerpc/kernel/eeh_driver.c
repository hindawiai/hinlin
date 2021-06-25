<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCI Error Recovery Driver क्रम RPA-compliant PPC64 platक्रमm.
 * Copyright IBM Corp. 2004 2005
 * Copyright Linas Vepstas <linas@linas.org> 2004, 2005
 *
 * Send comments and feedback to Linas Vepstas <linas@austin.ibm.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/eeh_event.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>

काष्ठा eeh_rmv_data अणु
	काष्ठा list_head हटाओd_vf_list;
	पूर्णांक हटाओd_dev_count;
पूर्ण;

अटल पूर्णांक eeh_result_priority(क्रमागत pci_ers_result result)
अणु
	चयन (result) अणु
	हाल PCI_ERS_RESULT_NONE:
		वापस 1;
	हाल PCI_ERS_RESULT_NO_AER_DRIVER:
		वापस 2;
	हाल PCI_ERS_RESULT_RECOVERED:
		वापस 3;
	हाल PCI_ERS_RESULT_CAN_RECOVER:
		वापस 4;
	हाल PCI_ERS_RESULT_DISCONNECT:
		वापस 5;
	हाल PCI_ERS_RESULT_NEED_RESET:
		वापस 6;
	शेष:
		WARN_ONCE(1, "Unknown pci_ers_result value: %d\n", (पूर्णांक)result);
		वापस 0;
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर *pci_ers_result_name(क्रमागत pci_ers_result result)
अणु
	चयन (result) अणु
	हाल PCI_ERS_RESULT_NONE:
		वापस "none";
	हाल PCI_ERS_RESULT_CAN_RECOVER:
		वापस "can recover";
	हाल PCI_ERS_RESULT_NEED_RESET:
		वापस "need reset";
	हाल PCI_ERS_RESULT_DISCONNECT:
		वापस "disconnect";
	हाल PCI_ERS_RESULT_RECOVERED:
		वापस "recovered";
	हाल PCI_ERS_RESULT_NO_AER_DRIVER:
		वापस "no AER driver";
	शेष:
		WARN_ONCE(1, "Unknown result type: %d\n", (पूर्णांक)result);
		वापस "unknown";
	पूर्ण
पूर्ण;

अटल क्रमागत pci_ers_result pci_ers_merge_result(क्रमागत pci_ers_result old,
						क्रमागत pci_ers_result new)
अणु
	अगर (eeh_result_priority(new) > eeh_result_priority(old))
		वापस new;
	वापस old;
पूर्ण

अटल bool eeh_dev_हटाओd(काष्ठा eeh_dev *edev)
अणु
	वापस !edev || (edev->mode & EEH_DEV_REMOVED);
पूर्ण

अटल bool eeh_edev_actionable(काष्ठा eeh_dev *edev)
अणु
	अगर (!edev->pdev)
		वापस false;
	अगर (edev->pdev->error_state == pci_channel_io_perm_failure)
		वापस false;
	अगर (eeh_dev_हटाओd(edev))
		वापस false;
	अगर (eeh_pe_passed(edev->pe))
		वापस false;

	वापस true;
पूर्ण

/**
 * eeh_pcid_get - Get the PCI device driver
 * @pdev: PCI device
 *
 * The function is used to retrieve the PCI device driver क्रम
 * the indicated PCI device. Besides, we will increase the reference
 * of the PCI device driver to prevent that being unloaded on
 * the fly. Otherwise, kernel crash would be seen.
 */
अटल अंतरभूत काष्ठा pci_driver *eeh_pcid_get(काष्ठा pci_dev *pdev)
अणु
	अगर (!pdev || !pdev->driver)
		वापस शून्य;

	अगर (!try_module_get(pdev->driver->driver.owner))
		वापस शून्य;

	वापस pdev->driver;
पूर्ण

/**
 * eeh_pcid_put - Dereference on the PCI device driver
 * @pdev: PCI device
 *
 * The function is called to करो dereference on the PCI device
 * driver of the indicated PCI device.
 */
अटल अंतरभूत व्योम eeh_pcid_put(काष्ठा pci_dev *pdev)
अणु
	अगर (!pdev || !pdev->driver)
		वापस;

	module_put(pdev->driver->driver.owner);
पूर्ण

/**
 * eeh_disable_irq - Disable पूर्णांकerrupt क्रम the recovering device
 * @dev: PCI device
 *
 * This routine must be called when reporting temporary or permanent
 * error to the particular PCI device to disable पूर्णांकerrupt of that
 * device. If the device has enabled MSI or MSI-X पूर्णांकerrupt, we needn't
 * करो real work because EEH should मुक्तze DMA transfers क्रम those PCI
 * devices encountering EEH errors, which includes MSI or MSI-X.
 */
अटल व्योम eeh_disable_irq(काष्ठा eeh_dev *edev)
अणु
	/* Don't disable MSI and MSI-X पूर्णांकerrupts. They are
	 * effectively disabled by the DMA Stopped state
	 * when an EEH error occurs.
	 */
	अगर (edev->pdev->msi_enabled || edev->pdev->msix_enabled)
		वापस;

	अगर (!irq_has_action(edev->pdev->irq))
		वापस;

	edev->mode |= EEH_DEV_IRQ_DISABLED;
	disable_irq_nosync(edev->pdev->irq);
पूर्ण

/**
 * eeh_enable_irq - Enable पूर्णांकerrupt क्रम the recovering device
 * @dev: PCI device
 *
 * This routine must be called to enable पूर्णांकerrupt जबतक failed
 * device could be resumed.
 */
अटल व्योम eeh_enable_irq(काष्ठा eeh_dev *edev)
अणु
	अगर ((edev->mode) & EEH_DEV_IRQ_DISABLED) अणु
		edev->mode &= ~EEH_DEV_IRQ_DISABLED;
		/*
		 * FIXME !!!!!
		 *
		 * This is just ass backwards. This maze has
		 * unbalanced irq_enable/disable calls. So instead of
		 * finding the root cause it works around the warning
		 * in the irq_enable code by conditionally calling
		 * पूर्णांकo it.
		 *
		 * That's just wrong.The warning in the core code is
		 * there to tell people to fix their asymmetries in
		 * their own code, not by abusing the core inक्रमmation
		 * to aव्योम it.
		 *
		 * I so wish that the assymetry would be the other way
		 * round and a few more irq_disable calls render that
		 * shit unusable क्रमever.
		 *
		 *	tglx
		 */
		अगर (irqd_irq_disabled(irq_get_irq_data(edev->pdev->irq)))
			enable_irq(edev->pdev->irq);
	पूर्ण
पूर्ण

अटल व्योम eeh_dev_save_state(काष्ठा eeh_dev *edev, व्योम *userdata)
अणु
	काष्ठा pci_dev *pdev;

	अगर (!edev)
		वापस;

	/*
	 * We cannot access the config space on some adapters.
	 * Otherwise, it will cause fenced PHB. We करोn't save
	 * the content in their config space and will restore
	 * from the initial config space saved when the EEH
	 * device is created.
	 */
	अगर (edev->pe && (edev->pe->state & EEH_PE_CFG_RESTRICTED))
		वापस;

	pdev = eeh_dev_to_pci_dev(edev);
	अगर (!pdev)
		वापस;

	pci_save_state(pdev);
पूर्ण

अटल व्योम eeh_set_channel_state(काष्ठा eeh_pe *root, pci_channel_state_t s)
अणु
	काष्ठा eeh_pe *pe;
	काष्ठा eeh_dev *edev, *पंचांगp;

	eeh_क्रम_each_pe(root, pe)
		eeh_pe_क्रम_each_dev(pe, edev, पंचांगp)
			अगर (eeh_edev_actionable(edev))
				edev->pdev->error_state = s;
पूर्ण

अटल व्योम eeh_set_irq_state(काष्ठा eeh_pe *root, bool enable)
अणु
	काष्ठा eeh_pe *pe;
	काष्ठा eeh_dev *edev, *पंचांगp;

	eeh_क्रम_each_pe(root, pe) अणु
		eeh_pe_क्रम_each_dev(pe, edev, पंचांगp) अणु
			अगर (!eeh_edev_actionable(edev))
				जारी;

			अगर (!eeh_pcid_get(edev->pdev))
				जारी;

			अगर (enable)
				eeh_enable_irq(edev);
			अन्यथा
				eeh_disable_irq(edev);

			eeh_pcid_put(edev->pdev);
		पूर्ण
	पूर्ण
पूर्ण

प्रकार क्रमागत pci_ers_result (*eeh_report_fn)(काष्ठा eeh_dev *,
					     काष्ठा pci_dev *,
					     काष्ठा pci_driver *);
अटल व्योम eeh_pe_report_edev(काष्ठा eeh_dev *edev, eeh_report_fn fn,
			       क्रमागत pci_ers_result *result)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pci_driver *driver;
	क्रमागत pci_ers_result new_result;

	pci_lock_rescan_हटाओ();
	pdev = edev->pdev;
	अगर (pdev)
		get_device(&pdev->dev);
	pci_unlock_rescan_हटाओ();
	अगर (!pdev) अणु
		eeh_edev_info(edev, "no device");
		वापस;
	पूर्ण
	device_lock(&pdev->dev);
	अगर (eeh_edev_actionable(edev)) अणु
		driver = eeh_pcid_get(pdev);

		अगर (!driver)
			eeh_edev_info(edev, "no driver");
		अन्यथा अगर (!driver->err_handler)
			eeh_edev_info(edev, "driver not EEH aware");
		अन्यथा अगर (edev->mode & EEH_DEV_NO_HANDLER)
			eeh_edev_info(edev, "driver bound too late");
		अन्यथा अणु
			new_result = fn(edev, pdev, driver);
			eeh_edev_info(edev, "%s driver reports: '%s'",
				      driver->name,
				      pci_ers_result_name(new_result));
			अगर (result)
				*result = pci_ers_merge_result(*result,
							       new_result);
		पूर्ण
		अगर (driver)
			eeh_pcid_put(pdev);
	पूर्ण अन्यथा अणु
		eeh_edev_info(edev, "not actionable (%d,%d,%d)", !!pdev,
			      !eeh_dev_हटाओd(edev), !eeh_pe_passed(edev->pe));
	पूर्ण
	device_unlock(&pdev->dev);
	अगर (edev->pdev != pdev)
		eeh_edev_warn(edev, "Device changed during processing!\n");
	put_device(&pdev->dev);
पूर्ण

अटल व्योम eeh_pe_report(स्थिर अक्षर *name, काष्ठा eeh_pe *root,
			  eeh_report_fn fn, क्रमागत pci_ers_result *result)
अणु
	काष्ठा eeh_pe *pe;
	काष्ठा eeh_dev *edev, *पंचांगp;

	pr_info("EEH: Beginning: '%s'\n", name);
	eeh_क्रम_each_pe(root, pe) eeh_pe_क्रम_each_dev(pe, edev, पंचांगp)
		eeh_pe_report_edev(edev, fn, result);
	अगर (result)
		pr_info("EEH: Finished:'%s' with aggregate recovery state:'%s'\n",
			name, pci_ers_result_name(*result));
	अन्यथा
		pr_info("EEH: Finished:'%s'", name);
पूर्ण

/**
 * eeh_report_error - Report pci error to each device driver
 * @edev: eeh device
 * @driver: device's PCI driver
 *
 * Report an EEH error to each device driver.
 */
अटल क्रमागत pci_ers_result eeh_report_error(काष्ठा eeh_dev *edev,
					    काष्ठा pci_dev *pdev,
					    काष्ठा pci_driver *driver)
अणु
	क्रमागत pci_ers_result rc;

	अगर (!driver->err_handler->error_detected)
		वापस PCI_ERS_RESULT_NONE;

	eeh_edev_info(edev, "Invoking %s->error_detected(IO frozen)",
		      driver->name);
	rc = driver->err_handler->error_detected(pdev, pci_channel_io_frozen);

	edev->in_error = true;
	pci_uevent_ers(pdev, PCI_ERS_RESULT_NONE);
	वापस rc;
पूर्ण

/**
 * eeh_report_mmio_enabled - Tell drivers that MMIO has been enabled
 * @edev: eeh device
 * @driver: device's PCI driver
 *
 * Tells each device driver that IO ports, MMIO and config space I/O
 * are now enabled.
 */
अटल क्रमागत pci_ers_result eeh_report_mmio_enabled(काष्ठा eeh_dev *edev,
						   काष्ठा pci_dev *pdev,
						   काष्ठा pci_driver *driver)
अणु
	अगर (!driver->err_handler->mmio_enabled)
		वापस PCI_ERS_RESULT_NONE;
	eeh_edev_info(edev, "Invoking %s->mmio_enabled()", driver->name);
	वापस driver->err_handler->mmio_enabled(pdev);
पूर्ण

/**
 * eeh_report_reset - Tell device that slot has been reset
 * @edev: eeh device
 * @driver: device's PCI driver
 *
 * This routine must be called जबतक EEH tries to reset particular
 * PCI device so that the associated PCI device driver could take
 * some actions, usually to save data the driver needs so that the
 * driver can work again जबतक the device is recovered.
 */
अटल क्रमागत pci_ers_result eeh_report_reset(काष्ठा eeh_dev *edev,
					    काष्ठा pci_dev *pdev,
					    काष्ठा pci_driver *driver)
अणु
	अगर (!driver->err_handler->slot_reset || !edev->in_error)
		वापस PCI_ERS_RESULT_NONE;
	eeh_edev_info(edev, "Invoking %s->slot_reset()", driver->name);
	वापस driver->err_handler->slot_reset(pdev);
पूर्ण

अटल व्योम eeh_dev_restore_state(काष्ठा eeh_dev *edev, व्योम *userdata)
अणु
	काष्ठा pci_dev *pdev;

	अगर (!edev)
		वापस;

	/*
	 * The content in the config space isn't saved because
	 * the blocked config space on some adapters. We have
	 * to restore the initial saved config space when the
	 * EEH device is created.
	 */
	अगर (edev->pe && (edev->pe->state & EEH_PE_CFG_RESTRICTED)) अणु
		अगर (list_is_last(&edev->entry, &edev->pe->edevs))
			eeh_pe_restore_bars(edev->pe);

		वापस;
	पूर्ण

	pdev = eeh_dev_to_pci_dev(edev);
	अगर (!pdev)
		वापस;

	pci_restore_state(pdev);
पूर्ण

/**
 * eeh_report_resume - Tell device to resume normal operations
 * @edev: eeh device
 * @driver: device's PCI driver
 *
 * This routine must be called to notअगरy the device driver that it
 * could resume so that the device driver can करो some initialization
 * to make the recovered device work again.
 */
अटल क्रमागत pci_ers_result eeh_report_resume(काष्ठा eeh_dev *edev,
					     काष्ठा pci_dev *pdev,
					     काष्ठा pci_driver *driver)
अणु
	अगर (!driver->err_handler->resume || !edev->in_error)
		वापस PCI_ERS_RESULT_NONE;

	eeh_edev_info(edev, "Invoking %s->resume()", driver->name);
	driver->err_handler->resume(pdev);

	pci_uevent_ers(edev->pdev, PCI_ERS_RESULT_RECOVERED);
#अगर_घोषित CONFIG_PCI_IOV
	अगर (eeh_ops->notअगरy_resume)
		eeh_ops->notअगरy_resume(edev);
#पूर्ण_अगर
	वापस PCI_ERS_RESULT_NONE;
पूर्ण

/**
 * eeh_report_failure - Tell device driver that device is dead.
 * @edev: eeh device
 * @driver: device's PCI driver
 *
 * This inक्रमms the device driver that the device is permanently
 * dead, and that no further recovery attempts will be made on it.
 */
अटल क्रमागत pci_ers_result eeh_report_failure(काष्ठा eeh_dev *edev,
					      काष्ठा pci_dev *pdev,
					      काष्ठा pci_driver *driver)
अणु
	क्रमागत pci_ers_result rc;

	अगर (!driver->err_handler->error_detected)
		वापस PCI_ERS_RESULT_NONE;

	eeh_edev_info(edev, "Invoking %s->error_detected(permanent failure)",
		      driver->name);
	rc = driver->err_handler->error_detected(pdev,
						 pci_channel_io_perm_failure);

	pci_uevent_ers(pdev, PCI_ERS_RESULT_DISCONNECT);
	वापस rc;
पूर्ण

अटल व्योम *eeh_add_virt_device(काष्ठा eeh_dev *edev)
अणु
	काष्ठा pci_driver *driver;
	काष्ठा pci_dev *dev = eeh_dev_to_pci_dev(edev);

	अगर (!(edev->physfn)) अणु
		eeh_edev_warn(edev, "Not for VF\n");
		वापस शून्य;
	पूर्ण

	driver = eeh_pcid_get(dev);
	अगर (driver) अणु
		अगर (driver->err_handler) अणु
			eeh_pcid_put(dev);
			वापस शून्य;
		पूर्ण
		eeh_pcid_put(dev);
	पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
	pci_iov_add_virtfn(edev->physfn, edev->vf_index);
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

अटल व्योम eeh_rmv_device(काष्ठा eeh_dev *edev, व्योम *userdata)
अणु
	काष्ठा pci_driver *driver;
	काष्ठा pci_dev *dev = eeh_dev_to_pci_dev(edev);
	काष्ठा eeh_rmv_data *rmv_data = (काष्ठा eeh_rmv_data *)userdata;

	/*
	 * Actually, we should हटाओ the PCI bridges as well.
	 * However, that's lots of complनिकासy to करो that,
	 * particularly some of devices under the bridge might
	 * support EEH. So we just care about PCI devices क्रम
	 * simplicity here.
	 */
	अगर (!eeh_edev_actionable(edev) ||
	    (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE))
		वापस;

	अगर (rmv_data) अणु
		driver = eeh_pcid_get(dev);
		अगर (driver) अणु
			अगर (driver->err_handler &&
			    driver->err_handler->error_detected &&
			    driver->err_handler->slot_reset) अणु
				eeh_pcid_put(dev);
				वापस;
			पूर्ण
			eeh_pcid_put(dev);
		पूर्ण
	पूर्ण

	/* Remove it from PCI subप्रणाली */
	pr_info("EEH: Removing %s without EEH sensitive driver\n",
		pci_name(dev));
	edev->mode |= EEH_DEV_DISCONNECTED;
	अगर (rmv_data)
		rmv_data->हटाओd_dev_count++;

	अगर (edev->physfn) अणु
#अगर_घोषित CONFIG_PCI_IOV
		pci_iov_हटाओ_virtfn(edev->physfn, edev->vf_index);
		edev->pdev = शून्य;
#पूर्ण_अगर
		अगर (rmv_data)
			list_add(&edev->rmv_entry, &rmv_data->हटाओd_vf_list);
	पूर्ण अन्यथा अणु
		pci_lock_rescan_हटाओ();
		pci_stop_and_हटाओ_bus_device(dev);
		pci_unlock_rescan_हटाओ();
	पूर्ण
पूर्ण

अटल व्योम *eeh_pe_detach_dev(काष्ठा eeh_pe *pe, व्योम *userdata)
अणु
	काष्ठा eeh_dev *edev, *पंचांगp;

	eeh_pe_क्रम_each_dev(pe, edev, पंचांगp) अणु
		अगर (!(edev->mode & EEH_DEV_DISCONNECTED))
			जारी;

		edev->mode &= ~(EEH_DEV_DISCONNECTED | EEH_DEV_IRQ_DISABLED);
		eeh_pe_tree_हटाओ(edev);
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Explicitly clear PE's frozen state क्रम PowerNV where
 * we have frozen PE until BAR restore is completed. It's
 * harmless to clear it क्रम pSeries. To be consistent with
 * PE reset (क्रम 3 बार), we try to clear the frozen state
 * क्रम 3 बार as well.
 */
अटल पूर्णांक eeh_clear_pe_frozen_state(काष्ठा eeh_pe *root, bool include_passed)
अणु
	काष्ठा eeh_pe *pe;
	पूर्णांक i;

	eeh_क्रम_each_pe(root, pe) अणु
		अगर (include_passed || !eeh_pe_passed(pe)) अणु
			क्रम (i = 0; i < 3; i++)
				अगर (!eeh_unमुक्तze_pe(pe))
					अवरोध;
			अगर (i >= 3)
				वापस -EIO;
		पूर्ण
	पूर्ण
	eeh_pe_state_clear(root, EEH_PE_ISOLATED, include_passed);
	वापस 0;
पूर्ण

पूर्णांक eeh_pe_reset_and_recover(काष्ठा eeh_pe *pe)
अणु
	पूर्णांक ret;

	/* Bail अगर the PE is being recovered */
	अगर (pe->state & EEH_PE_RECOVERING)
		वापस 0;

	/* Put the PE पूर्णांकo recovery mode */
	eeh_pe_state_mark(pe, EEH_PE_RECOVERING);

	/* Save states */
	eeh_pe_dev_traverse(pe, eeh_dev_save_state, शून्य);

	/* Issue reset */
	ret = eeh_pe_reset_full(pe, true);
	अगर (ret) अणु
		eeh_pe_state_clear(pe, EEH_PE_RECOVERING, true);
		वापस ret;
	पूर्ण

	/* Unमुक्तze the PE */
	ret = eeh_clear_pe_frozen_state(pe, true);
	अगर (ret) अणु
		eeh_pe_state_clear(pe, EEH_PE_RECOVERING, true);
		वापस ret;
	पूर्ण

	/* Restore device state */
	eeh_pe_dev_traverse(pe, eeh_dev_restore_state, शून्य);

	/* Clear recovery mode */
	eeh_pe_state_clear(pe, EEH_PE_RECOVERING, true);

	वापस 0;
पूर्ण

/**
 * eeh_reset_device - Perक्रमm actual reset of a pci slot
 * @driver_eeh_aware: Does the device's driver provide EEH support?
 * @pe: EEH PE
 * @bus: PCI bus corresponding to the isolcated slot
 * @rmv_data: Optional, list to record हटाओd devices
 *
 * This routine must be called to करो reset on the indicated PE.
 * During the reset, udev might be invoked because those affected
 * PCI devices will be हटाओd and then added.
 */
अटल पूर्णांक eeh_reset_device(काष्ठा eeh_pe *pe, काष्ठा pci_bus *bus,
			    काष्ठा eeh_rmv_data *rmv_data,
			    bool driver_eeh_aware)
अणु
	समय64_t tstamp;
	पूर्णांक cnt, rc;
	काष्ठा eeh_dev *edev;
	काष्ठा eeh_pe *पंचांगp_pe;
	bool any_passed = false;

	eeh_क्रम_each_pe(pe, पंचांगp_pe)
		any_passed |= eeh_pe_passed(पंचांगp_pe);

	/* pcibios will clear the counter; save the value */
	cnt = pe->मुक्तze_count;
	tstamp = pe->tstamp;

	/*
	 * We करोn't हटाओ the corresponding PE instances because
	 * we need the inक्रमmation afterwords. The attached EEH
	 * devices are expected to be attached soon when calling
	 * पूर्णांकo pci_hp_add_devices().
	 */
	eeh_pe_state_mark(pe, EEH_PE_KEEP);
	अगर (any_passed || driver_eeh_aware || (pe->type & EEH_PE_VF)) अणु
		eeh_pe_dev_traverse(pe, eeh_rmv_device, rmv_data);
	पूर्ण अन्यथा अणु
		pci_lock_rescan_हटाओ();
		pci_hp_हटाओ_devices(bus);
		pci_unlock_rescan_हटाओ();
	पूर्ण

	/*
	 * Reset the pci controller. (Asserts RST#; resets config space).
	 * Reconfigure bridges and devices. Don't try to bring the प्रणाली
	 * up अगर the reset failed क्रम some reason.
	 *
	 * During the reset, it's very dangerous to have uncontrolled PCI
	 * config accesses. So we prefer to block them. However, controlled
	 * PCI config accesses initiated from EEH itself are allowed.
	 */
	rc = eeh_pe_reset_full(pe, false);
	अगर (rc)
		वापस rc;

	pci_lock_rescan_हटाओ();

	/* Restore PE */
	eeh_ops->configure_bridge(pe);
	eeh_pe_restore_bars(pe);

	/* Clear frozen state */
	rc = eeh_clear_pe_frozen_state(pe, false);
	अगर (rc) अणु
		pci_unlock_rescan_हटाओ();
		वापस rc;
	पूर्ण

	/* Give the प्रणाली 5 seconds to finish running the user-space
	 * hotplug shutकरोwn scripts, e.g. अगरकरोwn क्रम ethernet.  Yes,
	 * this is a hack, but अगर we करोn't करो this, and try to bring
	 * the device up beक्रमe the scripts have taken it करोwn,
	 * potentially weird things happen.
	 */
	अगर (!driver_eeh_aware || rmv_data->हटाओd_dev_count) अणु
		pr_info("EEH: Sleep 5s ahead of %s hotplug\n",
			(driver_eeh_aware ? "partial" : "complete"));
		ssleep(5);

		/*
		 * The EEH device is still connected with its parent
		 * PE. We should disconnect it so the binding can be
		 * rebuilt when adding PCI devices.
		 */
		edev = list_first_entry(&pe->edevs, काष्ठा eeh_dev, entry);
		eeh_pe_traverse(pe, eeh_pe_detach_dev, शून्य);
		अगर (pe->type & EEH_PE_VF) अणु
			eeh_add_virt_device(edev);
		पूर्ण अन्यथा अणु
			अगर (!driver_eeh_aware)
				eeh_pe_state_clear(pe, EEH_PE_PRI_BUS, true);
			pci_hp_add_devices(bus);
		पूर्ण
	पूर्ण
	eeh_pe_state_clear(pe, EEH_PE_KEEP, true);

	pe->tstamp = tstamp;
	pe->मुक्तze_count = cnt;

	pci_unlock_rescan_हटाओ();
	वापस 0;
पूर्ण

/* The दीर्घest amount of समय to रुको क्रम a pci device
 * to come back on line, in seconds.
 */
#घोषणा MAX_WAIT_FOR_RECOVERY 300


/* Walks the PE tree after processing an event to हटाओ any stale PEs.
 *
 * NB: This needs to be recursive to ensure the leaf PEs get हटाओd
 * beक्रमe their parents करो. Although this is possible to करो recursively
 * we करोn't since this is easier to पढ़ो and we need to garantee
 * the leaf nodes will be handled first.
 */
अटल व्योम eeh_pe_cleanup(काष्ठा eeh_pe *pe)
अणु
	काष्ठा eeh_pe *child_pe, *पंचांगp;

	list_क्रम_each_entry_safe(child_pe, पंचांगp, &pe->child_list, child)
		eeh_pe_cleanup(child_pe);

	अगर (pe->state & EEH_PE_KEEP)
		वापस;

	अगर (!(pe->state & EEH_PE_INVALID))
		वापस;

	अगर (list_empty(&pe->edevs) && list_empty(&pe->child_list)) अणु
		list_del(&pe->child);
		kमुक्त(pe);
	पूर्ण
पूर्ण

/**
 * eeh_check_slot_presence - Check अगर a device is still present in a slot
 * @pdev: pci_dev to check
 *
 * This function may वापस a false positive अगर we can't determine the slot's
 * presence state. This might happen क्रम क्रम PCIe slots अगर the PE containing
 * the upstream bridge is also frozen, or the bridge is part of the same PE
 * as the device.
 *
 * This shouldn't happen often, but you might see it अगर you hotplug a PCIe
 * चयन.
 */
अटल bool eeh_slot_presence_check(काष्ठा pci_dev *pdev)
अणु
	स्थिर काष्ठा hotplug_slot_ops *ops;
	काष्ठा pci_slot *slot;
	u8 state;
	पूर्णांक rc;

	अगर (!pdev)
		वापस false;

	अगर (pdev->error_state == pci_channel_io_perm_failure)
		वापस false;

	slot = pdev->slot;
	अगर (!slot || !slot->hotplug)
		वापस true;

	ops = slot->hotplug->ops;
	अगर (!ops || !ops->get_adapter_status)
		वापस true;

	/* set the attention indicator जबतक we've got the slot ops */
	अगर (ops->set_attention_status)
		ops->set_attention_status(slot->hotplug, 1);

	rc = ops->get_adapter_status(slot->hotplug, &state);
	अगर (rc)
		वापस true;

	वापस !!state;
पूर्ण

अटल व्योम eeh_clear_slot_attention(काष्ठा pci_dev *pdev)
अणु
	स्थिर काष्ठा hotplug_slot_ops *ops;
	काष्ठा pci_slot *slot;

	अगर (!pdev)
		वापस;

	अगर (pdev->error_state == pci_channel_io_perm_failure)
		वापस;

	slot = pdev->slot;
	अगर (!slot || !slot->hotplug)
		वापस;

	ops = slot->hotplug->ops;
	अगर (!ops || !ops->set_attention_status)
		वापस;

	ops->set_attention_status(slot->hotplug, 0);
पूर्ण

/**
 * eeh_handle_normal_event - Handle EEH events on a specअगरic PE
 * @pe: EEH PE - which should not be used after we वापस, as it may
 * have been invalidated.
 *
 * Attempts to recover the given PE.  If recovery fails or the PE has failed
 * too many बार, हटाओ the PE.
 *
 * While PHB detects address or data parity errors on particular PCI
 * slot, the associated PE will be frozen. Besides, DMA's occurring
 * to wild addresses (which usually happen due to bugs in device
 * drivers or in PCI adapter firmware) can cause EEH error. #SERR,
 * #PERR or other misc PCI-related errors also can trigger EEH errors.
 *
 * Recovery process consists of unplugging the device driver (which
 * generated hotplug events to userspace), then issuing a PCI #RST to
 * the device, then reconfiguring the PCI config space क्रम all bridges
 * & devices under this slot, and then finally restarting the device
 * drivers (which cause a second set of hotplug events to go out to
 * userspace).
 */
व्योम eeh_handle_normal_event(काष्ठा eeh_pe *pe)
अणु
	काष्ठा pci_bus *bus;
	काष्ठा eeh_dev *edev, *पंचांगp;
	काष्ठा eeh_pe *पंचांगp_pe;
	पूर्णांक rc = 0;
	क्रमागत pci_ers_result result = PCI_ERS_RESULT_NONE;
	काष्ठा eeh_rmv_data rmv_data =
		अणुLIST_HEAD_INIT(rmv_data.हटाओd_vf_list), 0पूर्ण;
	पूर्णांक devices = 0;

	bus = eeh_pe_bus_get(pe);
	अगर (!bus) अणु
		pr_err("%s: Cannot find PCI bus for PHB#%x-PE#%x\n",
			__func__, pe->phb->global_number, pe->addr);
		वापस;
	पूर्ण

	/*
	 * When devices are hot-हटाओd we might get an EEH due to
	 * a driver attempting to touch the MMIO space of a हटाओd
	 * device. In this हाल we करोn't have a device to recover
	 * so suppress the event अगर we can't find any present devices.
	 *
	 * The hotplug driver should take care of tearing करोwn the
	 * device itself.
	 */
	eeh_क्रम_each_pe(pe, पंचांगp_pe)
		eeh_pe_क्रम_each_dev(पंचांगp_pe, edev, पंचांगp)
			अगर (eeh_slot_presence_check(edev->pdev))
				devices++;

	अगर (!devices) अणु
		pr_debug("EEH: Frozen PHB#%x-PE#%x is empty!\n",
			pe->phb->global_number, pe->addr);
		जाओ out; /* nothing to recover */
	पूर्ण

	/* Log the event */
	अगर (pe->type & EEH_PE_PHB) अणु
		pr_err("EEH: Recovering PHB#%x, location: %s\n",
			pe->phb->global_number, eeh_pe_loc_get(pe));
	पूर्ण अन्यथा अणु
		काष्ठा eeh_pe *phb_pe = eeh_phb_pe_get(pe->phb);

		pr_err("EEH: Recovering PHB#%x-PE#%x\n",
		       pe->phb->global_number, pe->addr);
		pr_err("EEH: PE location: %s, PHB location: %s\n",
		       eeh_pe_loc_get(pe), eeh_pe_loc_get(phb_pe));
	पूर्ण

#अगर_घोषित CONFIG_STACKTRACE
	/*
	 * Prपूर्णांक the saved stack trace now that we've verified there's
	 * something to recover.
	 */
	अगर (pe->trace_entries) अणु
		व्योम **ptrs = (व्योम **) pe->stack_trace;
		पूर्णांक i;

		pr_err("EEH: Frozen PHB#%x-PE#%x detected\n",
		       pe->phb->global_number, pe->addr);

		/* FIXME: Use the same क्रमmat as dump_stack() */
		pr_err("EEH: Call Trace:\n");
		क्रम (i = 0; i < pe->trace_entries; i++)
			pr_err("EEH: [%pK] %pS\n", ptrs[i], ptrs[i]);

		pe->trace_entries = 0;
	पूर्ण
#पूर्ण_अगर /* CONFIG_STACKTRACE */

	eeh_pe_update_समय_stamp(pe);
	pe->मुक्तze_count++;
	अगर (pe->मुक्तze_count > eeh_max_मुक्तzes) अणु
		pr_err("EEH: PHB#%x-PE#%x has failed %d times in the last hour and has been permanently disabled.\n",
		       pe->phb->global_number, pe->addr,
		       pe->मुक्तze_count);
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	eeh_क्रम_each_pe(pe, पंचांगp_pe)
		eeh_pe_क्रम_each_dev(पंचांगp_pe, edev, पंचांगp)
			edev->mode &= ~EEH_DEV_NO_HANDLER;

	/* Walk the various device drivers attached to this slot through
	 * a reset sequence, giving each an opportunity to करो what it needs
	 * to accomplish the reset.  Each child माला_लो a report of the
	 * status ... अगर any child can't handle the reset, then the entire
	 * slot is dlpar हटाओd and added.
	 *
	 * When the PHB is fenced, we have to issue a reset to recover from
	 * the error. Override the result अगर necessary to have partially
	 * hotplug क्रम this हाल.
	 */
	अगर (result != PCI_ERS_RESULT_DISCONNECT) अणु
		pr_warn("EEH: This PCI device has failed %d times in the last hour and will be permanently disabled after %d failures.\n",
			pe->मुक्तze_count, eeh_max_मुक्तzes);
		pr_info("EEH: Notify device drivers to shutdown\n");
		eeh_set_channel_state(pe, pci_channel_io_frozen);
		eeh_set_irq_state(pe, false);
		eeh_pe_report("error_detected(IO frozen)", pe,
			      eeh_report_error, &result);
		अगर ((pe->type & EEH_PE_PHB) &&
		    result != PCI_ERS_RESULT_NONE &&
		    result != PCI_ERS_RESULT_NEED_RESET)
			result = PCI_ERS_RESULT_NEED_RESET;
	पूर्ण

	/* Get the current PCI slot state. This can take a दीर्घ समय,
	 * someबार over 300 seconds क्रम certain प्रणालीs.
	 */
	अगर (result != PCI_ERS_RESULT_DISCONNECT) अणु
		rc = eeh_रुको_state(pe, MAX_WAIT_FOR_RECOVERY*1000);
		अगर (rc < 0 || rc == EEH_STATE_NOT_SUPPORT) अणु
			pr_warn("EEH: Permanent failure\n");
			result = PCI_ERS_RESULT_DISCONNECT;
		पूर्ण
	पूर्ण

	/* Since rtas may enable MMIO when posting the error log,
	 * करोn't post the error log until after all dev drivers
	 * have been inक्रमmed.
	 */
	अगर (result != PCI_ERS_RESULT_DISCONNECT) अणु
		pr_info("EEH: Collect temporary log\n");
		eeh_slot_error_detail(pe, EEH_LOG_TEMP);
	पूर्ण

	/* If all device drivers were EEH-unaware, then shut
	 * करोwn all of the device drivers, and hope they
	 * go करोwn willingly, without panicing the प्रणाली.
	 */
	अगर (result == PCI_ERS_RESULT_NONE) अणु
		pr_info("EEH: Reset with hotplug activity\n");
		rc = eeh_reset_device(pe, bus, शून्य, false);
		अगर (rc) अणु
			pr_warn("%s: Unable to reset, err=%d\n",
				__func__, rc);
			result = PCI_ERS_RESULT_DISCONNECT;
		पूर्ण
	पूर्ण

	/* If all devices reported they can proceed, then re-enable MMIO */
	अगर (result == PCI_ERS_RESULT_CAN_RECOVER) अणु
		pr_info("EEH: Enable I/O for affected devices\n");
		rc = eeh_pci_enable(pe, EEH_OPT_THAW_MMIO);

		अगर (rc < 0) अणु
			result = PCI_ERS_RESULT_DISCONNECT;
		पूर्ण अन्यथा अगर (rc) अणु
			result = PCI_ERS_RESULT_NEED_RESET;
		पूर्ण अन्यथा अणु
			pr_info("EEH: Notify device drivers to resume I/O\n");
			eeh_pe_report("mmio_enabled", pe,
				      eeh_report_mmio_enabled, &result);
		पूर्ण
	पूर्ण

	/* If all devices reported they can proceed, then re-enable DMA */
	अगर (result == PCI_ERS_RESULT_CAN_RECOVER) अणु
		pr_info("EEH: Enabled DMA for affected devices\n");
		rc = eeh_pci_enable(pe, EEH_OPT_THAW_DMA);

		अगर (rc < 0) अणु
			result = PCI_ERS_RESULT_DISCONNECT;
		पूर्ण अन्यथा अगर (rc) अणु
			result = PCI_ERS_RESULT_NEED_RESET;
		पूर्ण अन्यथा अणु
			/*
			 * We didn't करो PE reset क्रम the हाल. The PE
			 * is still in frozen state. Clear it beक्रमe
			 * resuming the PE.
			 */
			eeh_pe_state_clear(pe, EEH_PE_ISOLATED, true);
			result = PCI_ERS_RESULT_RECOVERED;
		पूर्ण
	पूर्ण

	/* If any device called out क्रम a reset, then reset the slot */
	अगर (result == PCI_ERS_RESULT_NEED_RESET) अणु
		pr_info("EEH: Reset without hotplug activity\n");
		rc = eeh_reset_device(pe, bus, &rmv_data, true);
		अगर (rc) अणु
			pr_warn("%s: Cannot reset, err=%d\n",
				__func__, rc);
			result = PCI_ERS_RESULT_DISCONNECT;
		पूर्ण अन्यथा अणु
			result = PCI_ERS_RESULT_NONE;
			eeh_set_channel_state(pe, pci_channel_io_normal);
			eeh_set_irq_state(pe, true);
			eeh_pe_report("slot_reset", pe, eeh_report_reset,
				      &result);
		पूर्ण
	पूर्ण

	अगर ((result == PCI_ERS_RESULT_RECOVERED) ||
	    (result == PCI_ERS_RESULT_NONE)) अणु
		/*
		 * For those hot हटाओd VFs, we should add back them after PF
		 * get recovered properly.
		 */
		list_क्रम_each_entry_safe(edev, पंचांगp, &rmv_data.हटाओd_vf_list,
					 rmv_entry) अणु
			eeh_add_virt_device(edev);
			list_del(&edev->rmv_entry);
		पूर्ण

		/* Tell all device drivers that they can resume operations */
		pr_info("EEH: Notify device driver to resume\n");
		eeh_set_channel_state(pe, pci_channel_io_normal);
		eeh_set_irq_state(pe, true);
		eeh_pe_report("resume", pe, eeh_report_resume, शून्य);
		eeh_क्रम_each_pe(pe, पंचांगp_pe) अणु
			eeh_pe_क्रम_each_dev(पंचांगp_pe, edev, पंचांगp) अणु
				edev->mode &= ~EEH_DEV_NO_HANDLER;
				edev->in_error = false;
			पूर्ण
		पूर्ण

		pr_info("EEH: Recovery successful.\n");
	पूर्ण अन्यथा  अणु
		/*
		 * About 90% of all real-lअगरe EEH failures in the field
		 * are due to poorly seated PCI cards. Only 10% or so are
		 * due to actual, failed cards.
		 */
		pr_err("EEH: Unable to recover from failure from PHB#%x-PE#%x.\n"
		       "Please try reseating or replacing it\n",
			pe->phb->global_number, pe->addr);

		eeh_slot_error_detail(pe, EEH_LOG_PERM);

		/* Notअगरy all devices that they're about to go करोwn. */
		eeh_set_channel_state(pe, pci_channel_io_perm_failure);
		eeh_set_irq_state(pe, false);
		eeh_pe_report("error_detected(permanent failure)", pe,
			      eeh_report_failure, शून्य);

		/* Mark the PE to be हटाओd permanently */
		eeh_pe_state_mark(pe, EEH_PE_REMOVED);

		/*
		 * Shut करोwn the device drivers क्रम good. We mark
		 * all हटाओd devices correctly to aव्योम access
		 * the their PCI config any more.
		 */
		अगर (pe->type & EEH_PE_VF) अणु
			eeh_pe_dev_traverse(pe, eeh_rmv_device, शून्य);
			eeh_pe_dev_mode_mark(pe, EEH_DEV_REMOVED);
		पूर्ण अन्यथा अणु
			eeh_pe_state_clear(pe, EEH_PE_PRI_BUS, true);
			eeh_pe_dev_mode_mark(pe, EEH_DEV_REMOVED);

			pci_lock_rescan_हटाओ();
			pci_hp_हटाओ_devices(bus);
			pci_unlock_rescan_हटाओ();
			/* The passed PE should no दीर्घer be used */
			वापस;
		पूर्ण
	पूर्ण

out:
	/*
	 * Clean up any PEs without devices. While marked as EEH_PE_RECOVERYING
	 * we करोn't want to modअगरy the PE tree काष्ठाure so we करो it here.
	 */
	eeh_pe_cleanup(pe);

	/* clear the slot attention LED क्रम all recovered devices */
	eeh_क्रम_each_pe(pe, पंचांगp_pe)
		eeh_pe_क्रम_each_dev(पंचांगp_pe, edev, पंचांगp)
			eeh_clear_slot_attention(edev->pdev);

	eeh_pe_state_clear(pe, EEH_PE_RECOVERING, true);
पूर्ण

/**
 * eeh_handle_special_event - Handle EEH events without a specअगरic failing PE
 *
 * Called when an EEH event is detected but can't be narrowed करोwn to a
 * specअगरic PE.  Iterates through possible failures and handles them as
 * necessary.
 */
व्योम eeh_handle_special_event(व्योम)
अणु
	काष्ठा eeh_pe *pe, *phb_pe, *पंचांगp_pe;
	काष्ठा eeh_dev *edev, *पंचांगp_edev;
	काष्ठा pci_bus *bus;
	काष्ठा pci_controller *hose;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;


	करो अणु
		rc = eeh_ops->next_error(&pe);

		चयन (rc) अणु
		हाल EEH_NEXT_ERR_DEAD_IOC:
			/* Mark all PHBs in dead state */
			eeh_serialize_lock(&flags);

			/* Purge all events */
			eeh_हटाओ_event(शून्य, true);

			list_क्रम_each_entry(hose, &hose_list, list_node) अणु
				phb_pe = eeh_phb_pe_get(hose);
				अगर (!phb_pe) जारी;

				eeh_pe_mark_isolated(phb_pe);
			पूर्ण

			eeh_serialize_unlock(flags);

			अवरोध;
		हाल EEH_NEXT_ERR_FROZEN_PE:
		हाल EEH_NEXT_ERR_FENCED_PHB:
		हाल EEH_NEXT_ERR_DEAD_PHB:
			/* Mark the PE in fenced state */
			eeh_serialize_lock(&flags);

			/* Purge all events of the PHB */
			eeh_हटाओ_event(pe, true);

			अगर (rc != EEH_NEXT_ERR_DEAD_PHB)
				eeh_pe_state_mark(pe, EEH_PE_RECOVERING);
			eeh_pe_mark_isolated(pe);

			eeh_serialize_unlock(flags);

			अवरोध;
		हाल EEH_NEXT_ERR_NONE:
			वापस;
		शेष:
			pr_warn("%s: Invalid value %d from next_error()\n",
				__func__, rc);
			वापस;
		पूर्ण

		/*
		 * For fenced PHB and frozen PE, it's handled as normal
		 * event. We have to हटाओ the affected PHBs क्रम dead
		 * PHB and IOC
		 */
		अगर (rc == EEH_NEXT_ERR_FROZEN_PE ||
		    rc == EEH_NEXT_ERR_FENCED_PHB) अणु
			eeh_pe_state_mark(pe, EEH_PE_RECOVERING);
			eeh_handle_normal_event(pe);
		पूर्ण अन्यथा अणु
			eeh_क्रम_each_pe(pe, पंचांगp_pe)
				eeh_pe_क्रम_each_dev(पंचांगp_pe, edev, पंचांगp_edev)
					edev->mode &= ~EEH_DEV_NO_HANDLER;

			/* Notअगरy all devices to be करोwn */
			eeh_pe_state_clear(pe, EEH_PE_PRI_BUS, true);
			eeh_set_channel_state(pe, pci_channel_io_perm_failure);
			eeh_pe_report(
				"error_detected(permanent failure)", pe,
				eeh_report_failure, शून्य);

			pci_lock_rescan_हटाओ();
			list_क्रम_each_entry(hose, &hose_list, list_node) अणु
				phb_pe = eeh_phb_pe_get(hose);
				अगर (!phb_pe ||
				    !(phb_pe->state & EEH_PE_ISOLATED) ||
				    (phb_pe->state & EEH_PE_RECOVERING))
					जारी;

				bus = eeh_pe_bus_get(phb_pe);
				अगर (!bus) अणु
					pr_err("%s: Cannot find PCI bus for "
					       "PHB#%x-PE#%x\n",
					       __func__,
					       pe->phb->global_number,
					       pe->addr);
					अवरोध;
				पूर्ण
				pci_hp_हटाओ_devices(bus);
			पूर्ण
			pci_unlock_rescan_हटाओ();
		पूर्ण

		/*
		 * If we have detected dead IOC, we needn't proceed
		 * any more since all PHBs would have been हटाओd
		 */
		अगर (rc == EEH_NEXT_ERR_DEAD_IOC)
			अवरोध;
	पूर्ण जबतक (rc != EEH_NEXT_ERR_NONE);
पूर्ण
