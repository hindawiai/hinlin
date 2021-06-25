<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *  Copyright (C) 2003 Herbert Valerio Riedel <hvr@gnu.org>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h> /* For __init, __निकास */
#समावेश <linux/dma-mapping.h>

#समावेश "prismcompat.h"
#समावेश "islpci_dev.h"
#समावेश "islpci_mgt.h"		/* क्रम pc_debug */
#समावेश "isl_oid.h"

MODULE_AUTHOR("[Intersil] R.Bastings and W.Termorshuizen, The prism54.org Development Team <prism54-devel@prism54.org>");
MODULE_DESCRIPTION("The Prism54 802.11 Wireless LAN adapter");
MODULE_LICENSE("GPL");

अटल पूर्णांक	init_pciपंचांग = 0;
module_param(init_pciपंचांग, पूर्णांक, 0);

/* In this order: venकरोr, device, subvenकरोr, subdevice, class, class_mask,
 * driver_data
 * If you have an update क्रम this please contact prism54-devel@prism54.org
 * The latest list can be found at http://wireless.wiki.kernel.org/en/users/Drivers/p54
 */
अटल स्थिर काष्ठा pci_device_id prism54_id_tbl[] = अणु
	/* Intersil PRISM Duette/Prism GT Wireless LAN adapter */
	अणु
	 0x1260, 0x3890,
	 PCI_ANY_ID, PCI_ANY_ID,
	 0, 0, 0
	पूर्ण,

	/* 3COM 3CRWE154G72 Wireless LAN adapter */
	अणु
	 PCI_VDEVICE(3COM, 0x6001), 0
	पूर्ण,

	/* Intersil PRISM Indigo Wireless LAN adapter */
	अणु
	 0x1260, 0x3877,
	 PCI_ANY_ID, PCI_ANY_ID,
	 0, 0, 0
	पूर्ण,

	/* Intersil PRISM Javelin/Xbow Wireless LAN adapter */
	अणु
	 0x1260, 0x3886,
	 PCI_ANY_ID, PCI_ANY_ID,
	 0, 0, 0
	पूर्ण,

	/* End of list */
	अणु0,0,0,0,0,0,0पूर्ण
पूर्ण;

/* रेजिस्टर the device with the Hotplug facilities of the kernel */
MODULE_DEVICE_TABLE(pci, prism54_id_tbl);

अटल पूर्णांक prism54_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम prism54_हटाओ(काष्ठा pci_dev *);
अटल पूर्णांक __maybe_unused prism54_suspend(काष्ठा device *);
अटल पूर्णांक __maybe_unused prism54_resume(काष्ठा device *);

अटल SIMPLE_DEV_PM_OPS(prism54_pm_ops, prism54_suspend, prism54_resume);

अटल काष्ठा pci_driver prism54_driver = अणु
	.name = DRV_NAME,
	.id_table = prism54_id_tbl,
	.probe = prism54_probe,
	.हटाओ = prism54_हटाओ,
	.driver.pm = &prism54_pm_ops,
पूर्ण;

/******************************************************************************
    Module initialization functions
******************************************************************************/

अटल पूर्णांक
prism54_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *ndev;
	u8 latency_पंचांगr;
	u32 mem_addr;
	islpci_निजी *priv;
	पूर्णांक rvalue;

	/* Enable the pci device */
	अगर (pci_enable_device(pdev)) अणु
		prपूर्णांकk(KERN_ERR "%s: pci_enable_device() failed.\n", DRV_NAME);
		वापस -ENODEV;
	पूर्ण

	/* check whether the latency समयr is set correctly */
	pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &latency_पंचांगr);
#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_TRACING, "latency timer: %x\n", latency_पंचांगr);
#पूर्ण_अगर
	अगर (latency_पंचांगr < PCIDEVICE_LATENCY_TIMER_MIN) अणु
		/* set the latency समयr */
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER,
				      PCIDEVICE_LATENCY_TIMER_VAL);
	पूर्ण

	/* enable PCI DMA */
	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_ERR "%s: 32-bit PCI DMA not supported", DRV_NAME);
		जाओ करो_pci_disable_device;
        पूर्ण

	/* 0x40 is the programmable समयr to configure the response समयout (TRDY_TIMEOUT)
	 * 0x41 is the programmable समयr to configure the retry समयout (RETRY_TIMEOUT)
	 *	The RETRY_TIMEOUT is used to set the number of retries that the core, as a
	 *	Master, will perक्रमm beक्रमe abanकरोning a cycle. The शेष value क्रम
	 *	RETRY_TIMEOUT is 0x80, which far exceeds the PCI 2.1 requirement क्रम new
	 *	devices. A ग_लिखो of zero to the RETRY_TIMEOUT रेजिस्टर disables this
	 *	function to allow use with any non-compliant legacy devices that may
	 *	execute more retries.
	 *
	 *	Writing zero to both these two रेजिस्टरs will disable both समयouts and
	 *	*can* solve problems caused by devices that are slow to respond.
	 *	Make this configurable - MSW
	 */
	अगर ( init_pciपंचांग >= 0 ) अणु
		pci_ग_लिखो_config_byte(pdev, 0x40, (u8)init_pciपंचांग);
		pci_ग_लिखो_config_byte(pdev, 0x41, (u8)init_pciपंचांग);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "PCI TRDY/RETRY unchanged\n");
	पूर्ण

	/* request the pci device I/O regions */
	rvalue = pci_request_regions(pdev, DRV_NAME);
	अगर (rvalue) अणु
		prपूर्णांकk(KERN_ERR "%s: pci_request_regions failure (rc=%d)\n",
		       DRV_NAME, rvalue);
		जाओ करो_pci_disable_device;
	पूर्ण

	/* check अगर the memory winकरोw is indeed set */
	rvalue = pci_पढ़ो_config_dword(pdev, PCI_BASE_ADDRESS_0, &mem_addr);
	अगर (rvalue || !mem_addr) अणु
		prपूर्णांकk(KERN_ERR "%s: PCI device memory region not configured; fix your BIOS or CardBus bridge/drivers\n",
		       DRV_NAME);
		जाओ करो_pci_release_regions;
	पूर्ण

	/* enable PCI bus-mastering */
	DEBUG(SHOW_TRACING, "%s: pci_set_master(pdev)\n", DRV_NAME);
	pci_set_master(pdev);

	/* enable MWI */
	pci_try_set_mwi(pdev);

	/* setup the network device पूर्णांकerface and its काष्ठाure */
	अगर (!(ndev = islpci_setup(pdev))) अणु
		/* error configuring the driver as a network device */
		prपूर्णांकk(KERN_ERR "%s: could not configure network device\n",
		       DRV_NAME);
		जाओ करो_pci_clear_mwi;
	पूर्ण

	priv = netdev_priv(ndev);
	islpci_set_state(priv, PRV_STATE_PREBOOT); /* we are attempting to boot */

	/* card is in unknown state yet, might have some पूर्णांकerrupts pending */
	isl38xx_disable_पूर्णांकerrupts(priv->device_base);

	/* request क्रम the पूर्णांकerrupt beक्रमe uploading the firmware */
	rvalue = request_irq(pdev->irq, islpci_पूर्णांकerrupt,
			     IRQF_SHARED, ndev->name, priv);

	अगर (rvalue) अणु
		/* error, could not hook the handler to the irq */
		prपूर्णांकk(KERN_ERR "%s: could not install IRQ handler\n",
		       ndev->name);
		जाओ करो_unरेजिस्टर_netdev;
	पूर्ण

	/* firmware upload is triggered in islpci_खोलो */

	वापस 0;

      करो_unरेजिस्टर_netdev:
	unरेजिस्टर_netdev(ndev);
	islpci_मुक्त_memory(priv);
	मुक्त_netdev(ndev);
	priv = शून्य;
      करो_pci_clear_mwi:
	pci_clear_mwi(pdev);
      करो_pci_release_regions:
	pci_release_regions(pdev);
      करो_pci_disable_device:
	pci_disable_device(pdev);
	वापस -EIO;
पूर्ण

/* set by cleanup_module */
अटल अस्थिर पूर्णांक __in_cleanup_module = 0;

/* this one हटाओs one(!!) instance only */
अटल व्योम
prism54_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *ndev = pci_get_drvdata(pdev);
	islpci_निजी *priv = ndev ? netdev_priv(ndev) : शून्य;
	BUG_ON(!priv);

	अगर (!__in_cleanup_module) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hot unplug detected\n", ndev->name);
		islpci_set_state(priv, PRV_STATE_OFF);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: removing device\n", ndev->name);

	unरेजिस्टर_netdev(ndev);

	/* मुक्त the पूर्णांकerrupt request */

	अगर (islpci_get_state(priv) != PRV_STATE_OFF) अणु
		isl38xx_disable_पूर्णांकerrupts(priv->device_base);
		islpci_set_state(priv, PRV_STATE_OFF);
		/* This bellow causes a lockup at rmmod समय. It might be
		 * because some पूर्णांकerrupts still linger after rmmod समय,
		 * see bug #17 */
		/* pci_set_घातer_state(pdev, 3);*/	/* try to घातer-off */
	पूर्ण

	मुक्त_irq(pdev->irq, priv);

	/* मुक्त the PCI memory and unmap the remapped page */
	islpci_मुक्त_memory(priv);

	मुक्त_netdev(ndev);
	priv = शून्य;

	pci_clear_mwi(pdev);

	pci_release_regions(pdev);

	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused
prism54_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	islpci_निजी *priv = ndev ? netdev_priv(ndev) : शून्य;
	BUG_ON(!priv);

	/* tell the device not to trigger पूर्णांकerrupts क्रम now... */
	isl38xx_disable_पूर्णांकerrupts(priv->device_base);

	/* from now on assume the hardware was alपढ़ोy घातered करोwn
	   and करोn't touch it anymore */
	islpci_set_state(priv, PRV_STATE_OFF);

	netअगर_stop_queue(ndev);
	netअगर_device_detach(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused
prism54_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	islpci_निजी *priv = ndev ? netdev_priv(ndev) : शून्य;

	BUG_ON(!priv);

	prपूर्णांकk(KERN_NOTICE "%s: got resume request\n", ndev->name);

	/* alright let's go पूर्णांकo the PREBOOT state */
	islpci_reset(priv, 1);

	netअगर_device_attach(ndev);
	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
prism54_module_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Loaded %s driver, version %s\n",
	       DRV_NAME, DRV_VERSION);

	__bug_on_wrong_काष्ठा_sizes ();

	वापस pci_रेजिस्टर_driver(&prism54_driver);
पूर्ण

/* by the समय prism54_module_निकास() terminates, as a postcondition
 * all instances will have been destroyed by calls to
 * prism54_हटाओ() */
अटल व्योम __निकास
prism54_module_निकास(व्योम)
अणु
	__in_cleanup_module = 1;

	pci_unरेजिस्टर_driver(&prism54_driver);

	prपूर्णांकk(KERN_INFO "Unloaded %s driver\n", DRV_NAME);

	__in_cleanup_module = 0;
पूर्ण

/* रेजिस्टर entry poपूर्णांकs */
module_init(prism54_module_init);
module_निकास(prism54_module_निकास);
/* खातापूर्ण */
