<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * (C) Copyright David Brownell 2000-2002
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#समावेश "usb.h"


/* PCI-based HCs are common, but plenty of non-PCI HCs are used too */

/*
 * Coordinate hanकरोffs between EHCI and companion controllers
 * during EHCI probing and प्रणाली resume.
 */

अटल DECLARE_RWSEM(companions_rwsem);

#घोषणा CL_UHCI		PCI_CLASS_SERIAL_USB_UHCI
#घोषणा CL_OHCI		PCI_CLASS_SERIAL_USB_OHCI
#घोषणा CL_EHCI		PCI_CLASS_SERIAL_USB_EHCI

अटल अंतरभूत पूर्णांक is_ohci_or_uhci(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->class == CL_OHCI || pdev->class == CL_UHCI;
पूर्ण

प्रकार व्योम (*companion_fn)(काष्ठा pci_dev *pdev, काष्ठा usb_hcd *hcd,
		काष्ठा pci_dev *companion, काष्ठा usb_hcd *companion_hcd);

/* Iterate over PCI devices in the same slot as pdev and call fn क्रम each */
अटल व्योम क्रम_each_companion(काष्ठा pci_dev *pdev, काष्ठा usb_hcd *hcd,
		companion_fn fn)
अणु
	काष्ठा pci_dev		*companion;
	काष्ठा usb_hcd		*companion_hcd;
	अचिन्हित पूर्णांक		slot = PCI_SLOT(pdev->devfn);

	/*
	 * Iterate through other PCI functions in the same slot.
	 * If the function's drvdata isn't set then it isn't bound to
	 * a USB host controller driver, so skip it.
	 */
	companion = शून्य;
	क्रम_each_pci_dev(companion) अणु
		अगर (companion->bus != pdev->bus ||
				PCI_SLOT(companion->devfn) != slot)
			जारी;

		/*
		 * Companion device should be either UHCI,OHCI or EHCI host
		 * controller, otherwise skip.
		 */
		अगर (companion->class != CL_UHCI && companion->class != CL_OHCI &&
				companion->class != CL_EHCI)
			जारी;

		companion_hcd = pci_get_drvdata(companion);
		अगर (!companion_hcd || !companion_hcd->self.root_hub)
			जारी;
		fn(pdev, hcd, companion, companion_hcd);
	पूर्ण
पूर्ण

/*
 * We're about to add an EHCI controller, which will unceremoniously grab
 * all the port connections away from its companions.  To prevent annoying
 * error messages, lock the companion's root hub and gracefully unconfigure
 * it beक्रमehand.  Leave it locked until the EHCI controller is all set.
 */
अटल व्योम ehci_pre_add(काष्ठा pci_dev *pdev, काष्ठा usb_hcd *hcd,
		काष्ठा pci_dev *companion, काष्ठा usb_hcd *companion_hcd)
अणु
	काष्ठा usb_device *udev;

	अगर (is_ohci_or_uhci(companion)) अणु
		udev = companion_hcd->self.root_hub;
		usb_lock_device(udev);
		usb_set_configuration(udev, 0);
	पूर्ण
पूर्ण

/*
 * Adding the EHCI controller has either succeeded or failed.  Set the
 * companion poपूर्णांकer accordingly, and in either हाल, reconfigure and
 * unlock the root hub.
 */
अटल व्योम ehci_post_add(काष्ठा pci_dev *pdev, काष्ठा usb_hcd *hcd,
		काष्ठा pci_dev *companion, काष्ठा usb_hcd *companion_hcd)
अणु
	काष्ठा usb_device *udev;

	अगर (is_ohci_or_uhci(companion)) अणु
		अगर (dev_get_drvdata(&pdev->dev)) अणु	/* Succeeded */
			dev_dbg(&pdev->dev, "HS companion for %s\n",
					dev_name(&companion->dev));
			companion_hcd->self.hs_companion = &hcd->self;
		पूर्ण
		udev = companion_hcd->self.root_hub;
		usb_set_configuration(udev, 1);
		usb_unlock_device(udev);
	पूर्ण
पूर्ण

/*
 * We just added a non-EHCI controller.  Find the EHCI controller to
 * which it is a companion, and store a poपूर्णांकer to the bus काष्ठाure.
 */
अटल व्योम non_ehci_add(काष्ठा pci_dev *pdev, काष्ठा usb_hcd *hcd,
		काष्ठा pci_dev *companion, काष्ठा usb_hcd *companion_hcd)
अणु
	अगर (is_ohci_or_uhci(pdev) && companion->class == CL_EHCI) अणु
		dev_dbg(&pdev->dev, "FS/LS companion for %s\n",
				dev_name(&companion->dev));
		hcd->self.hs_companion = &companion_hcd->self;
	पूर्ण
पूर्ण

/* We are removing an EHCI controller.  Clear the companions' poपूर्णांकers. */
अटल व्योम ehci_हटाओ(काष्ठा pci_dev *pdev, काष्ठा usb_hcd *hcd,
		काष्ठा pci_dev *companion, काष्ठा usb_hcd *companion_hcd)
अणु
	अगर (is_ohci_or_uhci(companion))
		companion_hcd->self.hs_companion = शून्य;
पूर्ण

#अगर_घोषित	CONFIG_PM

/* An EHCI controller must रुको क्रम its companions beक्रमe resuming. */
अटल व्योम ehci_रुको_क्रम_companions(काष्ठा pci_dev *pdev, काष्ठा usb_hcd *hcd,
		काष्ठा pci_dev *companion, काष्ठा usb_hcd *companion_hcd)
अणु
	अगर (is_ohci_or_uhci(companion))
		device_pm_रुको_क्रम_dev(&pdev->dev, &companion->dev);
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */

/**
 * usb_hcd_pci_probe - initialize PCI-based HCDs
 * @dev: USB Host Controller being probed
 * @id: pci hotplug id connecting controller to HCD framework
 * @driver: USB HC driver handle
 *
 * Context: task context, might sleep
 *
 * Allocates basic PCI resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 *
 * Store this function in the HCD's काष्ठा pci_driver as probe().
 *
 * Return: 0 अगर successful.
 */
पूर्णांक usb_hcd_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id,
		      स्थिर काष्ठा hc_driver *driver)
अणु
	काष्ठा usb_hcd		*hcd;
	पूर्णांक			retval;
	पूर्णांक			hcd_irq = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (!id)
		वापस -EINVAL;

	अगर (!driver)
		वापस -EINVAL;

	अगर (pci_enable_device(dev) < 0)
		वापस -ENODEV;

	/*
	 * The xHCI driver has its own irq management
	 * make sure irq setup is not touched क्रम xhci in generic hcd code
	 */
	अगर ((driver->flags & HCD_MASK) < HCD_USB3) अणु
		retval = pci_alloc_irq_vectors(dev, 1, 1, PCI_IRQ_LEGACY | PCI_IRQ_MSI);
		अगर (retval < 0) अणु
			dev_err(&dev->dev,
			"Found HC with no IRQ. Check BIOS/PCI %s setup!\n",
				pci_name(dev));
			retval = -ENODEV;
			जाओ disable_pci;
		पूर्ण
		hcd_irq = pci_irq_vector(dev, 0);
	पूर्ण

	hcd = usb_create_hcd(driver, &dev->dev, pci_name(dev));
	अगर (!hcd) अणु
		retval = -ENOMEM;
		जाओ मुक्त_irq_vectors;
	पूर्ण

	hcd->amd_resume_bug = (usb_hcd_amd_remote_wakeup_quirk(dev) &&
			driver->flags & (HCD_USB11 | HCD_USB3)) ? 1 : 0;

	अगर (driver->flags & HCD_MEMORY) अणु
		/* EHCI, OHCI */
		hcd->rsrc_start = pci_resource_start(dev, 0);
		hcd->rsrc_len = pci_resource_len(dev, 0);
		अगर (!devm_request_mem_region(&dev->dev, hcd->rsrc_start,
				hcd->rsrc_len, driver->description)) अणु
			dev_dbg(&dev->dev, "controller already in use\n");
			retval = -EBUSY;
			जाओ put_hcd;
		पूर्ण
		hcd->regs = devm_ioremap(&dev->dev, hcd->rsrc_start,
				hcd->rsrc_len);
		अगर (hcd->regs == शून्य) अणु
			dev_dbg(&dev->dev, "error mapping memory\n");
			retval = -EFAULT;
			जाओ put_hcd;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* UHCI */
		पूर्णांक	region;

		क्रम (region = 0; region < PCI_STD_NUM_BARS; region++) अणु
			अगर (!(pci_resource_flags(dev, region) &
					IORESOURCE_IO))
				जारी;

			hcd->rsrc_start = pci_resource_start(dev, region);
			hcd->rsrc_len = pci_resource_len(dev, region);
			अगर (devm_request_region(&dev->dev, hcd->rsrc_start,
					hcd->rsrc_len, driver->description))
				अवरोध;
		पूर्ण
		अगर (region == PCI_ROM_RESOURCE) अणु
			dev_dbg(&dev->dev, "no i/o regions available\n");
			retval = -EBUSY;
			जाओ put_hcd;
		पूर्ण
	पूर्ण

	pci_set_master(dev);

	/* Note: dev_set_drvdata must be called जबतक holding the rwsem */
	अगर (dev->class == CL_EHCI) अणु
		करोwn_ग_लिखो(&companions_rwsem);
		dev_set_drvdata(&dev->dev, hcd);
		क्रम_each_companion(dev, hcd, ehci_pre_add);
		retval = usb_add_hcd(hcd, hcd_irq, IRQF_SHARED);
		अगर (retval != 0)
			dev_set_drvdata(&dev->dev, शून्य);
		क्रम_each_companion(dev, hcd, ehci_post_add);
		up_ग_लिखो(&companions_rwsem);
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&companions_rwsem);
		dev_set_drvdata(&dev->dev, hcd);
		retval = usb_add_hcd(hcd, hcd_irq, IRQF_SHARED);
		अगर (retval != 0)
			dev_set_drvdata(&dev->dev, शून्य);
		अन्यथा
			क्रम_each_companion(dev, hcd, non_ehci_add);
		up_पढ़ो(&companions_rwsem);
	पूर्ण

	अगर (retval != 0)
		जाओ put_hcd;
	device_wakeup_enable(hcd->self.controller);

	अगर (pci_dev_run_wake(dev))
		pm_runसमय_put_noidle(&dev->dev);
	वापस retval;

put_hcd:
	usb_put_hcd(hcd);
मुक्त_irq_vectors:
	अगर ((driver->flags & HCD_MASK) < HCD_USB3)
		pci_मुक्त_irq_vectors(dev);
disable_pci:
	pci_disable_device(dev);
	dev_err(&dev->dev, "init %s fail, %d\n", pci_name(dev), retval);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_pci_probe);


/* may be called without controller electrically present */
/* may be called with controller, bus, and devices active */

/**
 * usb_hcd_pci_हटाओ - shutकरोwn processing क्रम PCI-based HCDs
 * @dev: USB Host Controller being हटाओd
 *
 * Context: task context, might sleep
 *
 * Reverses the effect of usb_hcd_pci_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thपढ़ो
 * context, normally "rmmod", "apmd", or something similar.
 *
 * Store this function in the HCD's काष्ठा pci_driver as हटाओ().
 */
व्योम usb_hcd_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा usb_hcd		*hcd;
	पूर्णांक			hcd_driver_flags;

	hcd = pci_get_drvdata(dev);
	अगर (!hcd)
		वापस;

	hcd_driver_flags = hcd->driver->flags;

	अगर (pci_dev_run_wake(dev))
		pm_runसमय_get_noresume(&dev->dev);

	/* Fake an पूर्णांकerrupt request in order to give the driver a chance
	 * to test whether the controller hardware has been हटाओd (e.g.,
	 * cardbus physical eject).
	 */
	local_irq_disable();
	usb_hcd_irq(0, hcd);
	local_irq_enable();

	/* Note: dev_set_drvdata must be called जबतक holding the rwsem */
	अगर (dev->class == CL_EHCI) अणु
		करोwn_ग_लिखो(&companions_rwsem);
		क्रम_each_companion(dev, hcd, ehci_हटाओ);
		usb_हटाओ_hcd(hcd);
		dev_set_drvdata(&dev->dev, शून्य);
		up_ग_लिखो(&companions_rwsem);
	पूर्ण अन्यथा अणु
		/* Not EHCI; just clear the companion poपूर्णांकer */
		करोwn_पढ़ो(&companions_rwsem);
		hcd->self.hs_companion = शून्य;
		usb_हटाओ_hcd(hcd);
		dev_set_drvdata(&dev->dev, शून्य);
		up_पढ़ो(&companions_rwsem);
	पूर्ण
	usb_put_hcd(hcd);
	अगर ((hcd_driver_flags & HCD_MASK) < HCD_USB3)
		pci_मुक्त_irq_vectors(dev);
	pci_disable_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_pci_हटाओ);

/**
 * usb_hcd_pci_shutकरोwn - shutकरोwn host controller
 * @dev: USB Host Controller being shutकरोwn
 */
व्योम usb_hcd_pci_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	काष्ठा usb_hcd		*hcd;

	hcd = pci_get_drvdata(dev);
	अगर (!hcd)
		वापस;

	अगर (test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags) &&
			hcd->driver->shutकरोwn) अणु
		hcd->driver->shutकरोwn(hcd);
		अगर (usb_hcd_is_primary_hcd(hcd) && hcd->irq > 0)
			मुक्त_irq(hcd->irq, hcd);
		pci_disable_device(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_pci_shutकरोwn);

#अगर_घोषित	CONFIG_PM

#अगर_घोषित	CONFIG_PPC_PMAC
अटल व्योम घातermac_set_asic(काष्ठा pci_dev *pci_dev, पूर्णांक enable)
अणु
	/* Enanble or disable ASIC घड़ीs क्रम USB */
	अगर (machine_is(घातermac)) अणु
		काष्ठा device_node	*of_node;

		of_node = pci_device_to_OF_node(pci_dev);
		अगर (of_node)
			pmac_call_feature(PMAC_FTR_USB_ENABLE,
					of_node, 0, enable);
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम घातermac_set_asic(काष्ठा pci_dev *pci_dev, पूर्णांक enable)
अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_PPC_PMAC */

अटल पूर्णांक check_root_hub_suspended(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd		*hcd = dev_get_drvdata(dev);

	अगर (HCD_RH_RUNNING(hcd)) अणु
		dev_warn(dev, "Root hub is not suspended\n");
		वापस -EBUSY;
	पूर्ण
	अगर (hcd->shared_hcd) अणु
		hcd = hcd->shared_hcd;
		अगर (HCD_RH_RUNNING(hcd)) अणु
			dev_warn(dev, "Secondary root hub is not suspended\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक suspend_common(काष्ठा device *dev, bool करो_wakeup)
अणु
	काष्ठा pci_dev		*pci_dev = to_pci_dev(dev);
	काष्ठा usb_hcd		*hcd = pci_get_drvdata(pci_dev);
	पूर्णांक			retval;

	/* Root hub suspend should have stopped all करोwnstream traffic,
	 * and all bus master traffic.  And करोne so क्रम both the पूर्णांकerface
	 * and the stub usb_device (which we check here).  But maybe it
	 * didn't; writing sysfs घातer/state files ignores such rules...
	 */
	retval = check_root_hub_suspended(dev);
	अगर (retval)
		वापस retval;

	अगर (hcd->driver->pci_suspend && !HCD_DEAD(hcd)) अणु
		/* Optimization: Don't suspend अगर a root-hub wakeup is
		 * pending and it would cause the HCD to wake up anyway.
		 */
		अगर (करो_wakeup && HCD_WAKEUP_PENDING(hcd))
			वापस -EBUSY;
		अगर (करो_wakeup && hcd->shared_hcd &&
				HCD_WAKEUP_PENDING(hcd->shared_hcd))
			वापस -EBUSY;
		retval = hcd->driver->pci_suspend(hcd, करो_wakeup);
		suspend_report_result(hcd->driver->pci_suspend, retval);

		/* Check again in हाल wakeup raced with pci_suspend */
		अगर ((retval == 0 && करो_wakeup && HCD_WAKEUP_PENDING(hcd)) ||
				(retval == 0 && करो_wakeup && hcd->shared_hcd &&
				 HCD_WAKEUP_PENDING(hcd->shared_hcd))) अणु
			अगर (hcd->driver->pci_resume)
				hcd->driver->pci_resume(hcd, false);
			retval = -EBUSY;
		पूर्ण
		अगर (retval)
			वापस retval;
	पूर्ण

	/* If MSI-X is enabled, the driver will have synchronized all vectors
	 * in pci_suspend(). If MSI or legacy PCI is enabled, that will be
	 * synchronized here.
	 */
	अगर (!hcd->msix_enabled)
		synchronize_irq(pci_irq_vector(pci_dev, 0));

	/* Downstream ports from this root hub should alपढ़ोy be quiesced, so
	 * there will be no DMA activity.  Now we can shut करोwn the upstream
	 * link (except maybe क्रम PME# resume संकेतing).  We'll enter a
	 * low घातer state during suspend_noirq, अगर the hardware allows.
	 */
	pci_disable_device(pci_dev);
	वापस retval;
पूर्ण

अटल पूर्णांक resume_common(काष्ठा device *dev, पूर्णांक event)
अणु
	काष्ठा pci_dev		*pci_dev = to_pci_dev(dev);
	काष्ठा usb_hcd		*hcd = pci_get_drvdata(pci_dev);
	पूर्णांक			retval;

	अगर (HCD_RH_RUNNING(hcd) ||
			(hcd->shared_hcd &&
			 HCD_RH_RUNNING(hcd->shared_hcd))) अणु
		dev_dbg(dev, "can't resume, not suspended!\n");
		वापस 0;
	पूर्ण

	retval = pci_enable_device(pci_dev);
	अगर (retval < 0) अणु
		dev_err(dev, "can't re-enable after resume, %d!\n", retval);
		वापस retval;
	पूर्ण

	pci_set_master(pci_dev);

	अगर (hcd->driver->pci_resume && !HCD_DEAD(hcd)) अणु

		/*
		 * Only EHCI controllers have to रुको क्रम their companions.
		 * No locking is needed because PCI controller drivers करो not
		 * get unbound during प्रणाली resume.
		 */
		अगर (pci_dev->class == CL_EHCI && event != PM_EVENT_AUTO_RESUME)
			क्रम_each_companion(pci_dev, hcd,
					ehci_रुको_क्रम_companions);

		retval = hcd->driver->pci_resume(hcd,
				event == PM_EVENT_RESTORE);
		अगर (retval) अणु
			dev_err(dev, "PCI post-resume error %d!\n", retval);
			usb_hc_died(hcd);
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

#अगर_घोषित	CONFIG_PM_SLEEP

अटल पूर्णांक hcd_pci_suspend(काष्ठा device *dev)
अणु
	वापस suspend_common(dev, device_may_wakeup(dev));
पूर्ण

अटल पूर्णांक hcd_pci_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev		*pci_dev = to_pci_dev(dev);
	काष्ठा usb_hcd		*hcd = pci_get_drvdata(pci_dev);
	पूर्णांक			retval;

	retval = check_root_hub_suspended(dev);
	अगर (retval)
		वापस retval;

	pci_save_state(pci_dev);

	/* If the root hub is dead rather than suspended, disallow remote
	 * wakeup.  usb_hc_died() should ensure that both hosts are marked as
	 * dying, so we only need to check the primary roothub.
	 */
	अगर (HCD_DEAD(hcd))
		device_set_wakeup_enable(dev, 0);
	dev_dbg(dev, "wakeup: %d\n", device_may_wakeup(dev));

	/* Possibly enable remote wakeup,
	 * choose the appropriate low-घातer state, and go to that state.
	 */
	retval = pci_prepare_to_sleep(pci_dev);
	अगर (retval == -EIO) अणु		/* Low-घातer not supported */
		dev_dbg(dev, "--> PCI D0 legacy\n");
		retval = 0;
	पूर्ण अन्यथा अगर (retval == 0) अणु
		dev_dbg(dev, "--> PCI %s\n",
				pci_घातer_name(pci_dev->current_state));
	पूर्ण अन्यथा अणु
		suspend_report_result(pci_prepare_to_sleep, retval);
		वापस retval;
	पूर्ण

	घातermac_set_asic(pci_dev, 0);
	वापस retval;
पूर्ण

अटल पूर्णांक hcd_pci_resume_noirq(काष्ठा device *dev)
अणु
	घातermac_set_asic(to_pci_dev(dev), 1);
	वापस 0;
पूर्ण

अटल पूर्णांक hcd_pci_resume(काष्ठा device *dev)
अणु
	वापस resume_common(dev, PM_EVENT_RESUME);
पूर्ण

अटल पूर्णांक hcd_pci_restore(काष्ठा device *dev)
अणु
	वापस resume_common(dev, PM_EVENT_RESTORE);
पूर्ण

#अन्यथा

#घोषणा hcd_pci_suspend		शून्य
#घोषणा hcd_pci_suspend_noirq	शून्य
#घोषणा hcd_pci_resume_noirq	शून्य
#घोषणा hcd_pci_resume		शून्य
#घोषणा hcd_pci_restore		शून्य

#पूर्ण_अगर	/* CONFIG_PM_SLEEP */

अटल पूर्णांक hcd_pci_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक	retval;

	retval = suspend_common(dev, true);
	अगर (retval == 0)
		घातermac_set_asic(to_pci_dev(dev), 0);
	dev_dbg(dev, "hcd_pci_runtime_suspend: %d\n", retval);
	वापस retval;
पूर्ण

अटल पूर्णांक hcd_pci_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक	retval;

	घातermac_set_asic(to_pci_dev(dev), 1);
	retval = resume_common(dev, PM_EVENT_AUTO_RESUME);
	dev_dbg(dev, "hcd_pci_runtime_resume: %d\n", retval);
	वापस retval;
पूर्ण

स्थिर काष्ठा dev_pm_ops usb_hcd_pci_pm_ops = अणु
	.suspend	= hcd_pci_suspend,
	.suspend_noirq	= hcd_pci_suspend_noirq,
	.resume_noirq	= hcd_pci_resume_noirq,
	.resume		= hcd_pci_resume,
	.मुक्तze		= check_root_hub_suspended,
	.मुक्तze_noirq	= check_root_hub_suspended,
	.thaw_noirq	= शून्य,
	.thaw		= शून्य,
	.घातeroff	= hcd_pci_suspend,
	.घातeroff_noirq	= hcd_pci_suspend_noirq,
	.restore_noirq	= hcd_pci_resume_noirq,
	.restore	= hcd_pci_restore,
	.runसमय_suspend = hcd_pci_runसमय_suspend,
	.runसमय_resume	= hcd_pci_runसमय_resume,
पूर्ण;
EXPORT_SYMBOL_GPL(usb_hcd_pci_pm_ops);

#पूर्ण_अगर	/* CONFIG_PM */
