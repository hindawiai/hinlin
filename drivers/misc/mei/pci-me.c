<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "client.h"
#समावेश "hw-me-regs.h"
#समावेश "hw-me.h"

/* mei_pci_tbl - PCI Device ID Table */
अटल स्थिर काष्ठा pci_device_id mei_me_pci_tbl[] = अणु
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_82946GZ, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_82G35, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_82Q965, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_82G965, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_82GM965, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_82GME965, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82Q35, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82G33, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82Q33, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_82X38, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_3200, MEI_ME_ICH_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_6, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_7, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_8, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_9, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9_10, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_1, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_2, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_3, MEI_ME_ICH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH9M_4, MEI_ME_ICH_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH10_1, MEI_ME_ICH10_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH10_2, MEI_ME_ICH10_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH10_3, MEI_ME_ICH10_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICH10_4, MEI_ME_ICH10_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_IBXPK_1, MEI_ME_PCH6_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_IBXPK_2, MEI_ME_PCH6_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CPT_1, MEI_ME_PCH_CPT_PBG_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_PBG_1, MEI_ME_PCH_CPT_PBG_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_PPT_1, MEI_ME_PCH7_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_PPT_2, MEI_ME_PCH7_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_PPT_3, MEI_ME_PCH7_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_LPT_H, MEI_ME_PCH8_SPS_4_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_LPT_W, MEI_ME_PCH8_SPS_4_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_LPT_LP, MEI_ME_PCH8_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_LPT_HR, MEI_ME_PCH8_SPS_4_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_WPT_LP, MEI_ME_PCH8_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_WPT_LP_2, MEI_ME_PCH8_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_SPT, MEI_ME_PCH8_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_SPT_2, MEI_ME_PCH8_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_SPT_3, MEI_ME_PCH8_ITOUCH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_SPT_H, MEI_ME_PCH8_SPS_4_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_SPT_H_2, MEI_ME_PCH8_SPS_4_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_LBG, MEI_ME_PCH12_SPS_4_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_BXT_M, MEI_ME_PCH8_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_APL_I, MEI_ME_PCH8_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_DNV_IE, MEI_ME_PCH8_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_GLK, MEI_ME_PCH8_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_KBP, MEI_ME_PCH8_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_KBP_2, MEI_ME_PCH8_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_KBP_3, MEI_ME_PCH8_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CNP_LP, MEI_ME_PCH12_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CNP_LP_3, MEI_ME_PCH8_ITOUCH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CNP_H, MEI_ME_PCH12_SPS_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CNP_H_3, MEI_ME_PCH12_SPS_ITOUCH_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CMP_LP, MEI_ME_PCH12_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CMP_LP_3, MEI_ME_PCH8_ITOUCH_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CMP_V, MEI_ME_PCH12_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CMP_H, MEI_ME_PCH12_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CMP_H_3, MEI_ME_PCH8_ITOUCH_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ICP_LP, MEI_ME_PCH12_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_TGP_LP, MEI_ME_PCH15_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_TGP_H, MEI_ME_PCH15_SPS_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_JSP_N, MEI_ME_PCH15_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_MCC, MEI_ME_PCH15_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_MCC_4, MEI_ME_PCH8_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_CDF, MEI_ME_PCH8_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_EBG, MEI_ME_PCH15_SPS_CFG)पूर्ण,

	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ADP_S, MEI_ME_PCH15_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ADP_LP, MEI_ME_PCH15_CFG)पूर्ण,
	अणुMEI_PCI_DEVICE(MEI_DEV_ID_ADP_P, MEI_ME_PCH15_CFG)पूर्ण,

	/* required last entry */
	अणु0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mei_me_pci_tbl);

#अगर_घोषित CONFIG_PM
अटल अंतरभूत व्योम mei_me_set_pm_करोमुख्य(काष्ठा mei_device *dev);
अटल अंतरभूत व्योम mei_me_unset_pm_करोमुख्य(काष्ठा mei_device *dev);
#अन्यथा
अटल अंतरभूत व्योम mei_me_set_pm_करोमुख्य(काष्ठा mei_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम mei_me_unset_pm_करोमुख्य(काष्ठा mei_device *dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक mei_me_पढ़ो_fws(स्थिर काष्ठा mei_device *dev, पूर्णांक where, u32 *val)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	वापस pci_पढ़ो_config_dword(pdev, where, val);
पूर्ण

/**
 * mei_me_quirk_probe - probe क्रम devices that करोesn't valid ME पूर्णांकerface
 *
 * @pdev: PCI device काष्ठाure
 * @cfg: per generation config
 *
 * Return: true अगर ME Interface is valid, false otherwise
 */
अटल bool mei_me_quirk_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा mei_cfg *cfg)
अणु
	अगर (cfg->quirk_probe && cfg->quirk_probe(pdev)) अणु
		dev_info(&pdev->dev, "Device doesn't have valid ME Interface\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * mei_me_probe - Device Initialization Routine
 *
 * @pdev: PCI device काष्ठाure
 * @ent: entry in kcs_pci_tbl
 *
 * Return: 0 on success, <0 on failure.
 */
अटल पूर्णांक mei_me_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा mei_cfg *cfg;
	काष्ठा mei_device *dev;
	काष्ठा mei_me_hw *hw;
	अचिन्हित पूर्णांक irqflags;
	पूर्णांक err;

	cfg = mei_me_get_cfg(ent->driver_data);
	अगर (!cfg)
		वापस -ENODEV;

	अगर (!mei_me_quirk_probe(pdev, cfg))
		वापस -ENODEV;

	/* enable pci dev */
	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable pci device.\n");
		जाओ end;
	पूर्ण
	/* set PCI host mastering  */
	pci_set_master(pdev);
	/* pci request regions and mapping IO device memory क्रम mei driver */
	err = pcim_iomap_regions(pdev, BIT(0), KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to get pci regions.\n");
		जाओ end;
	पूर्ण

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)) ||
	    dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु

		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err)
			err = dma_set_coherent_mask(&pdev->dev,
						    DMA_BIT_MASK(32));
	पूर्ण
	अगर (err) अणु
		dev_err(&pdev->dev, "No usable DMA configuration, aborting\n");
		जाओ end;
	पूर्ण

	/* allocates and initializes the mei dev काष्ठाure */
	dev = mei_me_dev_init(&pdev->dev, cfg);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ end;
	पूर्ण
	hw = to_me_hw(dev);
	hw->mem_addr = pcim_iomap_table(pdev)[0];
	hw->पढ़ो_fws = mei_me_पढ़ो_fws;

	pci_enable_msi(pdev);

	hw->irq = pdev->irq;

	 /* request and enable पूर्णांकerrupt */
	irqflags = pci_dev_msi_enabled(pdev) ? IRQF_ONESHOT : IRQF_SHARED;

	err = request_thपढ़ोed_irq(pdev->irq,
			mei_me_irq_quick_handler,
			mei_me_irq_thपढ़ो_handler,
			irqflags, KBUILD_MODNAME, dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "request_threaded_irq failure. irq = %d\n",
		       pdev->irq);
		जाओ end;
	पूर्ण

	अगर (mei_start(dev)) अणु
		dev_err(&pdev->dev, "init hw failure.\n");
		err = -ENODEV;
		जाओ release_irq;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, MEI_ME_RPM_TIMEOUT);
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
	 * ME maps runसमय suspend/resume to D0i states,
	 * hence we need to go around native PCI runसमय service which
	 * eventually brings the device पूर्णांकo D3cold/hot state,
	 * but the mei device cannot wake up from D3 unlike from D0i3.
	 * To get around the PCI device native runसमय pm,
	 * ME uses runसमय pm करोमुख्य handlers which take precedence
	 * over the driver's pm handlers.
	 */
	mei_me_set_pm_करोमुख्य(dev);

	अगर (mei_pg_is_enabled(dev)) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		अगर (hw->d0i3_supported)
			pm_runसमय_allow(&pdev->dev);
	पूर्ण

	dev_dbg(&pdev->dev, "initialization successful.\n");

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
 * mei_me_shutकरोwn - Device Removal Routine
 *
 * @pdev: PCI device काष्ठाure
 *
 * mei_me_shutकरोwn is called from the reboot notअगरier
 * it's a simplअगरied version of हटाओ so we go करोwn
 * faster.
 */
अटल व्योम mei_me_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mei_device *dev;

	dev = pci_get_drvdata(pdev);
	अगर (!dev)
		वापस;

	dev_dbg(&pdev->dev, "shutdown\n");
	mei_stop(dev);

	mei_me_unset_pm_करोमुख्य(dev);

	mei_disable_पूर्णांकerrupts(dev);
	मुक्त_irq(pdev->irq, dev);
पूर्ण

/**
 * mei_me_हटाओ - Device Removal Routine
 *
 * @pdev: PCI device काष्ठाure
 *
 * mei_me_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.
 */
अटल व्योम mei_me_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mei_device *dev;

	dev = pci_get_drvdata(pdev);
	अगर (!dev)
		वापस;

	अगर (mei_pg_is_enabled(dev))
		pm_runसमय_get_noresume(&pdev->dev);

	dev_dbg(&pdev->dev, "stop\n");
	mei_stop(dev);

	mei_me_unset_pm_करोमुख्य(dev);

	mei_disable_पूर्णांकerrupts(dev);

	मुक्त_irq(pdev->irq, dev);

	mei_deरेजिस्टर(dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mei_me_pci_suspend(काष्ठा device *device)
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

अटल पूर्णांक mei_me_pci_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा mei_device *dev;
	अचिन्हित पूर्णांक irqflags;
	पूर्णांक err;

	dev = pci_get_drvdata(pdev);
	अगर (!dev)
		वापस -ENODEV;

	pci_enable_msi(pdev);

	irqflags = pci_dev_msi_enabled(pdev) ? IRQF_ONESHOT : IRQF_SHARED;

	/* request and enable पूर्णांकerrupt */
	err = request_thपढ़ोed_irq(pdev->irq,
			mei_me_irq_quick_handler,
			mei_me_irq_thपढ़ो_handler,
			irqflags, KBUILD_MODNAME, dev);

	अगर (err) अणु
		dev_err(&pdev->dev, "request_threaded_irq failed: irq = %d.\n",
				pdev->irq);
		वापस err;
	पूर्ण

	err = mei_restart(dev);
	अगर (err)
		वापस err;

	/* Start समयr अगर stopped in suspend */
	schedule_delayed_work(&dev->समयr_work, HZ);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mei_me_pm_runसमय_idle(काष्ठा device *device)
अणु
	काष्ठा mei_device *dev;

	dev_dbg(device, "rpm: me: runtime_idle\n");

	dev = dev_get_drvdata(device);
	अगर (!dev)
		वापस -ENODEV;
	अगर (mei_ग_लिखो_is_idle(dev))
		pm_runसमय_स्वतःsuspend(device);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक mei_me_pm_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक ret;

	dev_dbg(device, "rpm: me: runtime suspend\n");

	dev = dev_get_drvdata(device);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->device_lock);

	अगर (mei_ग_लिखो_is_idle(dev))
		ret = mei_me_pg_enter_sync(dev);
	अन्यथा
		ret = -EAGAIN;

	mutex_unlock(&dev->device_lock);

	dev_dbg(device, "rpm: me: runtime suspend ret=%d\n", ret);

	अगर (ret && ret != -EAGAIN)
		schedule_work(&dev->reset_work);

	वापस ret;
पूर्ण

अटल पूर्णांक mei_me_pm_runसमय_resume(काष्ठा device *device)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक ret;

	dev_dbg(device, "rpm: me: runtime resume\n");

	dev = dev_get_drvdata(device);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->device_lock);

	ret = mei_me_pg_निकास_sync(dev);

	mutex_unlock(&dev->device_lock);

	dev_dbg(device, "rpm: me: runtime resume ret = %d\n", ret);

	अगर (ret)
		schedule_work(&dev->reset_work);

	वापस ret;
पूर्ण

/**
 * mei_me_set_pm_करोमुख्य - fill and set pm करोमुख्य काष्ठाure क्रम device
 *
 * @dev: mei_device
 */
अटल अंतरभूत व्योम mei_me_set_pm_करोमुख्य(काष्ठा mei_device *dev)
अणु
	काष्ठा pci_dev *pdev  = to_pci_dev(dev->dev);

	अगर (pdev->dev.bus && pdev->dev.bus->pm) अणु
		dev->pg_करोमुख्य.ops = *pdev->dev.bus->pm;

		dev->pg_करोमुख्य.ops.runसमय_suspend = mei_me_pm_runसमय_suspend;
		dev->pg_करोमुख्य.ops.runसमय_resume = mei_me_pm_runसमय_resume;
		dev->pg_करोमुख्य.ops.runसमय_idle = mei_me_pm_runसमय_idle;

		dev_pm_करोमुख्य_set(&pdev->dev, &dev->pg_करोमुख्य);
	पूर्ण
पूर्ण

/**
 * mei_me_unset_pm_करोमुख्य - clean pm करोमुख्य काष्ठाure क्रम device
 *
 * @dev: mei_device
 */
अटल अंतरभूत व्योम mei_me_unset_pm_करोमुख्य(काष्ठा mei_device *dev)
अणु
	/* stop using pm callbacks अगर any */
	dev_pm_करोमुख्य_set(dev->dev, शून्य);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mei_me_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mei_me_pci_suspend,
				mei_me_pci_resume)
	SET_RUNTIME_PM_OPS(
		mei_me_pm_runसमय_suspend,
		mei_me_pm_runसमय_resume,
		mei_me_pm_runसमय_idle)
पूर्ण;

#घोषणा MEI_ME_PM_OPS	(&mei_me_pm_ops)
#अन्यथा
#घोषणा MEI_ME_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM */
/*
 *  PCI driver काष्ठाure
 */
अटल काष्ठा pci_driver mei_me_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = mei_me_pci_tbl,
	.probe = mei_me_probe,
	.हटाओ = mei_me_हटाओ,
	.shutकरोwn = mei_me_shutकरोwn,
	.driver.pm = MEI_ME_PM_OPS,
	.driver.probe_type = PROBE_PREFER_ASYNCHRONOUS,
पूर्ण;

module_pci_driver(mei_me_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Intel(R) Management Engine Interface");
MODULE_LICENSE("GPL v2");
