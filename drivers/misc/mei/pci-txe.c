<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mei.h>


#समावेश "mei_dev.h"
#समावेश "hw-txe.h"

अटल स्थिर काष्ठा pci_device_id mei_txe_pci_tbl[] = अणु
	अणुPCI_VDEVICE(INTEL, 0x0F18)पूर्ण, /* Baytrail */
	अणुPCI_VDEVICE(INTEL, 0x2298)पूर्ण, /* Cherrytrail */

	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, mei_txe_pci_tbl);

#अगर_घोषित CONFIG_PM
अटल अंतरभूत व्योम mei_txe_set_pm_करोमुख्य(काष्ठा mei_device *dev);
अटल अंतरभूत व्योम mei_txe_unset_pm_करोमुख्य(काष्ठा mei_device *dev);
#अन्यथा
अटल अंतरभूत व्योम mei_txe_set_pm_करोमुख्य(काष्ठा mei_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम mei_txe_unset_pm_करोमुख्य(काष्ठा mei_device *dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM */

/**
 * mei_txe_probe - Device Initialization Routine
 *
 * @pdev: PCI device काष्ठाure
 * @ent: entry in mei_txe_pci_tbl
 *
 * Return: 0 on success, <0 on failure.
 */
अटल पूर्णांक mei_txe_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_txe_hw *hw;
	स्थिर पूर्णांक mask = BIT(SEC_BAR) | BIT(BRIDGE_BAR);
	पूर्णांक err;

	/* enable pci dev */
	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable pci device.\n");
		जाओ end;
	पूर्ण
	/* set PCI host mastering  */
	pci_set_master(pdev);
	/* pci request regions and mapping IO device memory क्रम mei driver */
	err = pcim_iomap_regions(pdev, mask, KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to get pci regions.\n");
		जाओ end;
	पूर्ण

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(36));
	अगर (err) अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "No suitable DMA available.\n");
			जाओ end;
		पूर्ण
	पूर्ण

	/* allocates and initializes the mei dev काष्ठाure */
	dev = mei_txe_dev_init(pdev);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ end;
	पूर्ण
	hw = to_txe_hw(dev);
	hw->mem_addr = pcim_iomap_table(pdev);

	pci_enable_msi(pdev);

	/* clear spurious पूर्णांकerrupts */
	mei_clear_पूर्णांकerrupts(dev);

	/* request and enable पूर्णांकerrupt  */
	अगर (pci_dev_msi_enabled(pdev))
		err = request_thपढ़ोed_irq(pdev->irq,
			शून्य,
			mei_txe_irq_thपढ़ो_handler,
			IRQF_ONESHOT, KBUILD_MODNAME, dev);
	अन्यथा
		err = request_thपढ़ोed_irq(pdev->irq,
			mei_txe_irq_quick_handler,
			mei_txe_irq_thपढ़ो_handler,
			IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "mei: request_threaded_irq failure. irq = %d\n",
			pdev->irq);
		जाओ end;
	पूर्ण

	अगर (mei_start(dev)) अणु
		dev_err(&pdev->dev, "init hw failure.\n");
		err = -ENODEV;
		जाओ release_irq;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, MEI_TXI_RPM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);

	err = mei_रेजिस्टर(dev, &pdev->dev);
	अगर (err)
		जाओ stop;

	pci_set_drvdata(pdev, dev);

	/*
	 * MEI requires to resume from runसमय suspend mode
	 * in order to perक्रमm link reset flow upon प्रणाली suspend.
	 */
	dev_pm_set_driver_flags(&pdev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE);

	/*
	 * TXE maps runसमय suspend/resume to own घातer gating states,
	 * hence we need to go around native PCI runसमय service which
	 * eventually brings the device पूर्णांकo D3cold/hot state.
	 * But the TXE device cannot wake up from D3 unlike from own
	 * घातer gating. To get around PCI device native runसमय pm,
	 * TXE uses runसमय pm करोमुख्य handlers which take precedence.
	 */
	mei_txe_set_pm_करोमुख्य(dev);

	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;

stop:
	mei_stop(dev);
release_irq:
	mei_cancel_work(dev);
	mei_disable_पूर्णांकerrupts(dev);
	मुक्त_irq(pdev->irq, dev);
end:
	dev_err(&pdev->dev, "initialization failed.\n");
	वापस err;
पूर्ण

/**
 * mei_txe_हटाओ - Device Shutकरोwn Routine
 *
 * @pdev: PCI device काष्ठाure
 *
 *  mei_txe_shutकरोwn is called from the reboot notअगरier
 *  it's a simplअगरied version of हटाओ so we go करोwn
 *  faster.
 */
अटल व्योम mei_txe_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mei_device *dev;

	dev = pci_get_drvdata(pdev);
	अगर (!dev)
		वापस;

	dev_dbg(&pdev->dev, "shutdown\n");
	mei_stop(dev);

	mei_txe_unset_pm_करोमुख्य(dev);

	mei_disable_पूर्णांकerrupts(dev);
	मुक्त_irq(pdev->irq, dev);
पूर्ण

/**
 * mei_txe_हटाओ - Device Removal Routine
 *
 * @pdev: PCI device काष्ठाure
 *
 * mei_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.
 */
अटल व्योम mei_txe_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mei_device *dev;

	dev = pci_get_drvdata(pdev);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "mei: dev == NULL\n");
		वापस;
	पूर्ण

	pm_runसमय_get_noresume(&pdev->dev);

	mei_stop(dev);

	mei_txe_unset_pm_करोमुख्य(dev);

	mei_disable_पूर्णांकerrupts(dev);
	मुक्त_irq(pdev->irq, dev);

	mei_deरेजिस्टर(dev);
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mei_txe_pci_suspend(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा mei_device *dev = pci_get_drvdata(pdev);

	अगर (!dev)
		वापस -ENODEV;

	dev_dbg(&pdev->dev, "suspend\n");

	mei_stop(dev);

	mei_disable_पूर्णांकerrupts(dev);

	मुक्त_irq(pdev->irq, dev);
	pci_disable_msi(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक mei_txe_pci_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा mei_device *dev;
	पूर्णांक err;

	dev = pci_get_drvdata(pdev);
	अगर (!dev)
		वापस -ENODEV;

	pci_enable_msi(pdev);

	mei_clear_पूर्णांकerrupts(dev);

	/* request and enable पूर्णांकerrupt */
	अगर (pci_dev_msi_enabled(pdev))
		err = request_thपढ़ोed_irq(pdev->irq,
			शून्य,
			mei_txe_irq_thपढ़ो_handler,
			IRQF_ONESHOT, KBUILD_MODNAME, dev);
	अन्यथा
		err = request_thपढ़ोed_irq(pdev->irq,
			mei_txe_irq_quick_handler,
			mei_txe_irq_thपढ़ो_handler,
			IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "request_threaded_irq failed: irq = %d.\n",
				pdev->irq);
		वापस err;
	पूर्ण

	err = mei_restart(dev);

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mei_txe_pm_runसमय_idle(काष्ठा device *device)
अणु
	काष्ठा mei_device *dev;

	dev_dbg(device, "rpm: txe: runtime_idle\n");

	dev = dev_get_drvdata(device);
	अगर (!dev)
		वापस -ENODEV;
	अगर (mei_ग_लिखो_is_idle(dev))
		pm_runसमय_स्वतःsuspend(device);

	वापस -EBUSY;
पूर्ण
अटल पूर्णांक mei_txe_pm_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक ret;

	dev_dbg(device, "rpm: txe: runtime suspend\n");

	dev = dev_get_drvdata(device);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->device_lock);

	अगर (mei_ग_लिखो_is_idle(dev))
		ret = mei_txe_aliveness_set_sync(dev, 0);
	अन्यथा
		ret = -EAGAIN;

	/* keep irq on we are staying in D0 */

	dev_dbg(device, "rpm: txe: runtime suspend ret=%d\n", ret);

	mutex_unlock(&dev->device_lock);

	अगर (ret && ret != -EAGAIN)
		schedule_work(&dev->reset_work);

	वापस ret;
पूर्ण

अटल पूर्णांक mei_txe_pm_runसमय_resume(काष्ठा device *device)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक ret;

	dev_dbg(device, "rpm: txe: runtime resume\n");

	dev = dev_get_drvdata(device);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->device_lock);

	mei_enable_पूर्णांकerrupts(dev);

	ret = mei_txe_aliveness_set_sync(dev, 1);

	mutex_unlock(&dev->device_lock);

	dev_dbg(device, "rpm: txe: runtime resume ret = %d\n", ret);

	अगर (ret)
		schedule_work(&dev->reset_work);

	वापस ret;
पूर्ण

/**
 * mei_txe_set_pm_करोमुख्य - fill and set pm करोमुख्य काष्ठाure क्रम device
 *
 * @dev: mei_device
 */
अटल अंतरभूत व्योम mei_txe_set_pm_करोमुख्य(काष्ठा mei_device *dev)
अणु
	काष्ठा pci_dev *pdev  = to_pci_dev(dev->dev);

	अगर (pdev->dev.bus && pdev->dev.bus->pm) अणु
		dev->pg_करोमुख्य.ops = *pdev->dev.bus->pm;

		dev->pg_करोमुख्य.ops.runसमय_suspend = mei_txe_pm_runसमय_suspend;
		dev->pg_करोमुख्य.ops.runसमय_resume = mei_txe_pm_runसमय_resume;
		dev->pg_करोमुख्य.ops.runसमय_idle = mei_txe_pm_runसमय_idle;

		dev_pm_करोमुख्य_set(&pdev->dev, &dev->pg_करोमुख्य);
	पूर्ण
पूर्ण

/**
 * mei_txe_unset_pm_करोमुख्य - clean pm करोमुख्य काष्ठाure क्रम device
 *
 * @dev: mei_device
 */
अटल अंतरभूत व्योम mei_txe_unset_pm_करोमुख्य(काष्ठा mei_device *dev)
अणु
	/* stop using pm callbacks अगर any */
	dev_pm_करोमुख्य_set(dev->dev, शून्य);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mei_txe_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mei_txe_pci_suspend,
				mei_txe_pci_resume)
	SET_RUNTIME_PM_OPS(
		mei_txe_pm_runसमय_suspend,
		mei_txe_pm_runसमय_resume,
		mei_txe_pm_runसमय_idle)
पूर्ण;

#घोषणा MEI_TXE_PM_OPS	(&mei_txe_pm_ops)
#अन्यथा
#घोषणा MEI_TXE_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM */

/*
 *  PCI driver काष्ठाure
 */
अटल काष्ठा pci_driver mei_txe_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = mei_txe_pci_tbl,
	.probe = mei_txe_probe,
	.हटाओ = mei_txe_हटाओ,
	.shutकरोwn = mei_txe_shutकरोwn,
	.driver.pm = MEI_TXE_PM_OPS,
पूर्ण;

module_pci_driver(mei_txe_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Intel(R) Trusted Execution Environment Interface");
MODULE_LICENSE("GPL v2");
