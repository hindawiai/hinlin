<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCI glue क्रम ISHTP provider device (ISH) driver
 *
 * Copyright (c) 2014-2016, Intel Corporation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/पूर्णांकel_ish.h>
#समावेश "ishtp-dev.h"
#समावेश "hw-ish.h"

अटल स्थिर काष्ठा pci_device_id ish_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, CHV_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, BXT_Ax_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, BXT_Bx_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, APL_Ax_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, SPT_Ax_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, CNL_Ax_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, GLK_Ax_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, CNL_H_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ICL_MOBILE_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, SPT_H_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, CML_LP_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, CMP_H_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, EHL_Ax_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, TGL_LP_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, TGL_H_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ADL_S_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ADL_P_DEVICE_ID)पूर्ण,
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ish_pci_tbl);

/**
 * ish_event_tracer() - Callback function to dump trace messages
 * @dev:	ishtp device
 * @क्रमmat:	म_लिखो style क्रमmat
 *
 * Callback to direct log messages to Linux trace buffers
 */
अटल __म_लिखो(2, 3)
व्योम ish_event_tracer(काष्ठा ishtp_device *dev, स्थिर अक्षर *क्रमmat, ...)
अणु
	अगर (trace_ishtp_dump_enabled()) अणु
		बहु_सूची args;
		अक्षर पंचांगp_buf[100];

		बहु_शुरू(args, क्रमmat);
		vsnम_लिखो(पंचांगp_buf, माप(पंचांगp_buf), क्रमmat, args);
		बहु_पूर्ण(args);

		trace_ishtp_dump(पंचांगp_buf);
	पूर्ण
पूर्ण

/**
 * ish_init() - Init function
 * @dev:	ishtp device
 *
 * This function initialize रुको queues क्रम suspend/resume and call
 * calls hadware initialization function. This will initiate
 * startup sequence
 *
 * Return: 0 क्रम success or error code क्रम failure
 */
अटल पूर्णांक ish_init(काष्ठा ishtp_device *dev)
अणु
	पूर्णांक ret;

	/* Set the state of ISH HW to start */
	ret = ish_hw_start(dev);
	अगर (ret) अणु
		dev_err(dev->devc, "ISH: hw start failed.\n");
		वापस ret;
	पूर्ण

	/* Start the पूर्णांकer process communication to ISH processor */
	ret = ishtp_start(dev);
	अगर (ret) अणु
		dev_err(dev->devc, "ISHTP: Protocol init failed.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id ish_invalid_pci_ids[] = अणु
	/* Mehlow platक्रमm special pci ids */
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xA309)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xA30A)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत bool ish_should_enter_d0i3(काष्ठा pci_dev *pdev)
अणु
	वापस !pm_suspend_via_firmware() || pdev->device == CHV_DEVICE_ID;
पूर्ण

अटल अंतरभूत bool ish_should_leave_d0i3(काष्ठा pci_dev *pdev)
अणु
	वापस !pm_resume_via_firmware() || pdev->device == CHV_DEVICE_ID;
पूर्ण

अटल पूर्णांक enable_gpe(काष्ठा device *dev)
अणु
#अगर_घोषित CONFIG_ACPI
	acpi_status acpi_sts;
	काष्ठा acpi_device *adev;
	काष्ठा acpi_device_wakeup *wakeup;

	adev = ACPI_COMPANION(dev);
	अगर (!adev) अणु
		dev_err(dev, "get acpi handle failed\n");
		वापस -ENODEV;
	पूर्ण
	wakeup = &adev->wakeup;

	acpi_sts = acpi_enable_gpe(wakeup->gpe_device, wakeup->gpe_number);
	अगर (ACPI_FAILURE(acpi_sts)) अणु
		dev_err(dev, "enable ose_gpe failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल व्योम enable_pme_wake(काष्ठा pci_dev *pdev)
अणु
	अगर ((pci_pme_capable(pdev, PCI_D0) ||
	     pci_pme_capable(pdev, PCI_D3hot) ||
	     pci_pme_capable(pdev, PCI_D3cold)) && !enable_gpe(&pdev->dev)) अणु
		pci_pme_active(pdev, true);
		dev_dbg(&pdev->dev, "ish ipc driver pme wake enabled\n");
	पूर्ण
पूर्ण

/**
 * ish_probe() - PCI driver probe callback
 * @pdev:	pci device
 * @ent:	pci device id
 *
 * Initialize PCI function, setup पूर्णांकerrupt and call क्रम ISH initialization
 *
 * Return: 0 क्रम success or error code क्रम failure
 */
अटल पूर्णांक ish_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;
	काष्ठा ish_hw *hw;
	अचिन्हित दीर्घ irq_flag = 0;
	काष्ठा ishtp_device *ishtp;
	काष्ठा device *dev = &pdev->dev;

	/* Check क्रम invalid platक्रमms क्रम ISH support */
	अगर (pci_dev_present(ish_invalid_pci_ids))
		वापस -ENODEV;

	/* enable pci dev */
	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(dev, "ISH: Failed to enable PCI device\n");
		वापस ret;
	पूर्ण

	/* set PCI host mastering */
	pci_set_master(pdev);

	/* pci request regions क्रम ISH driver */
	ret = pcim_iomap_regions(pdev, 1 << 0, KBUILD_MODNAME);
	अगर (ret) अणु
		dev_err(dev, "ISH: Failed to get PCI regions\n");
		वापस ret;
	पूर्ण

	/* allocates and initializes the ISH dev काष्ठाure */
	ishtp = ish_dev_init(pdev);
	अगर (!ishtp) अणु
		ret = -ENOMEM;
		वापस ret;
	पूर्ण
	hw = to_ish_hw(ishtp);
	ishtp->prपूर्णांक_log = ish_event_tracer;

	/* mapping IO device memory */
	hw->mem_addr = pcim_iomap_table(pdev)[0];
	ishtp->pdev = pdev;

	/* request and enable पूर्णांकerrupt */
	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (!pdev->msi_enabled && !pdev->msix_enabled)
		irq_flag = IRQF_SHARED;

	ret = devm_request_irq(dev, pdev->irq, ish_irq_handler,
			       irq_flag, KBUILD_MODNAME, ishtp);
	अगर (ret) अणु
		dev_err(dev, "ISH: request IRQ %d failed\n", pdev->irq);
		वापस ret;
	पूर्ण

	dev_set_drvdata(ishtp->devc, ishtp);

	init_रुकोqueue_head(&ishtp->suspend_रुको);
	init_रुकोqueue_head(&ishtp->resume_रुको);

	/* Enable PME क्रम EHL */
	अगर (pdev->device == EHL_Ax_DEVICE_ID)
		enable_pme_wake(pdev);

	ret = ish_init(ishtp);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * ish_हटाओ() - PCI driver हटाओ callback
 * @pdev:	pci device
 *
 * This function करोes cleanup of ISH on pci हटाओ callback
 */
अटल व्योम ish_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ishtp_device *ishtp_dev = pci_get_drvdata(pdev);

	ishtp_bus_हटाओ_all_clients(ishtp_dev, false);
	ish_device_disable(ishtp_dev);
पूर्ण

अटल काष्ठा device __maybe_unused *ish_resume_device;

/* 50ms to get resume response */
#घोषणा WAIT_FOR_RESUME_ACK_MS		50

/**
 * ish_resume_handler() - Work function to complete resume
 * @work:	work काष्ठा
 *
 * The resume work function to complete resume function asynchronously.
 * There are two resume paths, one where ISH is not घातered off,
 * in that हाल a simple resume message is enough, others we need
 * a reset sequence.
 */
अटल व्योम __maybe_unused ish_resume_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ish_resume_device);
	काष्ठा ishtp_device *dev = pci_get_drvdata(pdev);
	uपूर्णांक32_t fwsts = dev->ops->get_fw_status(dev);
	पूर्णांक ret;

	अगर (ish_should_leave_d0i3(pdev) && !dev->suspend_flag
			&& IPC_IS_ISH_ILUP(fwsts)) अणु
		disable_irq_wake(pdev->irq);

		ish_set_host_पढ़ोy(dev);

		ishtp_send_resume(dev);

		/* Waiting to get resume response */
		अगर (dev->resume_flag)
			ret = रुको_event_पूर्णांकerruptible_समयout(dev->resume_रुको,
				!dev->resume_flag,
				msecs_to_jअगरfies(WAIT_FOR_RESUME_ACK_MS));

		/*
		 * If the flag is not cleared, something is wrong with ISH FW.
		 * So on resume, need to go through init sequence again.
		 */
		अगर (dev->resume_flag)
			ish_init(dev);
	पूर्ण अन्यथा अणु
		/*
		 * Resume from the D3, full reboot of ISH processor will happen,
		 * so need to go through init sequence again.
		 */
		ish_init(dev);
	पूर्ण
पूर्ण

/**
 * ish_suspend() - ISH suspend callback
 * @device:	device poपूर्णांकer
 *
 * ISH suspend callback
 *
 * Return: 0 to the pm core
 */
अटल पूर्णांक __maybe_unused ish_suspend(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा ishtp_device *dev = pci_get_drvdata(pdev);

	अगर (ish_should_enter_d0i3(pdev)) अणु
		/*
		 * If previous suspend hasn't been asnwered then ISH is likely
		 * dead, करोn't attempt nested notअगरication
		 */
		अगर (dev->suspend_flag)
			वापस	0;

		dev->resume_flag = 0;
		dev->suspend_flag = 1;
		ishtp_send_suspend(dev);

		/* 25 ms should be enough क्रम live ISH to flush all IPC buf */
		अगर (dev->suspend_flag)
			रुको_event_पूर्णांकerruptible_समयout(dev->suspend_रुको,
					!dev->suspend_flag,
					msecs_to_jअगरfies(25));

		अगर (dev->suspend_flag) अणु
			/*
			 * It looks like FW halt, clear the DMA bit, and put
			 * ISH पूर्णांकo D3, and FW would reset on resume.
			 */
			ish_disable_dma(dev);
		पूर्ण अन्यथा अणु
			/*
			 * Save state so PCI core will keep the device at D0,
			 * the ISH would enter D0i3
			 */
			pci_save_state(pdev);

			enable_irq_wake(pdev->irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Clear the DMA bit beक्रमe putting ISH पूर्णांकo D3,
		 * or ISH FW would reset स्वतःmatically.
		 */
		ish_disable_dma(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल __maybe_unused DECLARE_WORK(resume_work, ish_resume_handler);
/**
 * ish_resume() - ISH resume callback
 * @device:	device poपूर्णांकer
 *
 * ISH resume callback
 *
 * Return: 0 to the pm core
 */
अटल पूर्णांक __maybe_unused ish_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा ishtp_device *dev = pci_get_drvdata(pdev);

	/* add this to finish घातer flow क्रम EHL */
	अगर (dev->pdev->device == EHL_Ax_DEVICE_ID) अणु
		pci_set_घातer_state(pdev, PCI_D0);
		enable_pme_wake(pdev);
		dev_dbg(dev->devc, "set power state to D0 for ehl\n");
	पूर्ण

	ish_resume_device = device;
	dev->resume_flag = 1;

	schedule_work(&resume_work);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ish_pm_ops, ish_suspend, ish_resume);

अटल काष्ठा pci_driver ish_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = ish_pci_tbl,
	.probe = ish_probe,
	.हटाओ = ish_हटाओ,
	.driver.pm = &ish_pm_ops,
पूर्ण;

module_pci_driver(ish_driver);

/* Original author */
MODULE_AUTHOR("Daniel Drubin <daniel.drubin@intel.com>");
/* Aकरोption to upstream Linux kernel */
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");

MODULE_DESCRIPTION("Intel(R) Integrated Sensor Hub PCI Device Driver");
MODULE_LICENSE("GPL");
