<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	i6300esb:	Watchकरोg समयr driver क्रम Intel 6300ESB chipset
 *
 *	(c) Copyright 2004 Google Inc.
 *	(c) Copyright 2005 David Hथअrdeman <david@2gen.com>
 *
 *	based on i810-tco.c which is in turn based on softकरोg.c
 *
 *	The समयr is implemented in the following I/O controller hubs:
 *	(See the पूर्णांकel करोcumentation on http://developer.पूर्णांकel.com.)
 *	6300ESB chip : करोcument number 300641-004
 *
 *  2004YYZZ Ross Biro
 *	Initial version 0.01
 *  2004YYZZ Ross Biro
 *	Version 0.02
 *  20050210 David Hथअrdeman <david@2gen.com>
 *	Ported driver to kernel 2.6
 *  20171016 Radu Rendec <rrendec@arista.com>
 *	Change driver to use the watchकरोg subप्रणाली
 *	Add support क्रम multiple 6300ESB devices
 */

/*
 *      Includes, defines, variables, module parameters, ...
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

/* Module and version inक्रमmation */
#घोषणा ESB_MODULE_NAME "i6300ESB timer"

/* PCI configuration रेजिस्टरs */
#घोषणा ESB_CONFIG_REG  0x60            /* Config रेजिस्टर                   */
#घोषणा ESB_LOCK_REG    0x68            /* WDT lock रेजिस्टर                 */

/* Memory mapped रेजिस्टरs */
#घोषणा ESB_TIMER1_REG(w) ((w)->base + 0x00)/* Timer1 value after each reset */
#घोषणा ESB_TIMER2_REG(w) ((w)->base + 0x04)/* Timer2 value after each reset */
#घोषणा ESB_GINTSR_REG(w) ((w)->base + 0x08)/* General Interrupt Status Reg  */
#घोषणा ESB_RELOAD_REG(w) ((w)->base + 0x0c)/* Reload रेजिस्टर               */

/* Lock रेजिस्टर bits */
#घोषणा ESB_WDT_FUNC    (0x01 << 2)   /* Watchकरोg functionality            */
#घोषणा ESB_WDT_ENABLE  (0x01 << 1)   /* Enable WDT                        */
#घोषणा ESB_WDT_LOCK    (0x01 << 0)   /* Lock (nowayout)                   */

/* Config रेजिस्टर bits */
#घोषणा ESB_WDT_REBOOT  (0x01 << 5)   /* Enable reboot on समयout          */
#घोषणा ESB_WDT_FREQ    (0x01 << 2)   /* Decrement frequency               */
#घोषणा ESB_WDT_INTTYPE (0x03 << 0)   /* Interrupt type on समयr1 समयout  */

/* Reload रेजिस्टर bits */
#घोषणा ESB_WDT_TIMEOUT (0x01 << 9)    /* Watchकरोg समयd out                */
#घोषणा ESB_WDT_RELOAD  (0x01 << 8)    /* prevent समयout                   */

/* Magic स्थिरants */
#घोषणा ESB_UNLOCK1     0x80            /* Step 1 to unlock reset रेजिस्टरs  */
#घोषणा ESB_UNLOCK2     0x86            /* Step 2 to unlock reset रेजिस्टरs  */

/* module parameters */
/* 30 sec शेष heartbeat (1 < heartbeat < 2*1023) */
#घोषणा ESB_HEARTBEAT_MIN	1
#घोषणा ESB_HEARTBEAT_MAX	2046
#घोषणा ESB_HEARTBEAT_DEFAULT	30
#घोषणा ESB_HEARTBEAT_RANGE __MODULE_STRING(ESB_HEARTBEAT_MIN) \
	"<heartbeat<" __MODULE_STRING(ESB_HEARTBEAT_MAX)
अटल पूर्णांक heartbeat; /* in seconds */
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
	"Watchdog heartbeat in seconds. (" ESB_HEARTBEAT_RANGE
	", default=" __MODULE_STRING(ESB_HEARTBEAT_DEFAULT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/* पूर्णांकernal variables */
काष्ठा esb_dev अणु
	काष्ठा watchकरोg_device wdd;
	व्योम __iomem *base;
	काष्ठा pci_dev *pdev;
पूर्ण;

#घोषणा to_esb_dev(wptr) container_of(wptr, काष्ठा esb_dev, wdd)

/*
 * Some i6300ESB specअगरic functions
 */

/*
 * Prepare क्रम reloading the समयr by unlocking the proper रेजिस्टरs.
 * This is perक्रमmed by first writing 0x80 followed by 0x86 to the
 * reload रेजिस्टर. After this the appropriate रेजिस्टरs can be written
 * to once beक्रमe they need to be unlocked again.
 */
अटल अंतरभूत व्योम esb_unlock_रेजिस्टरs(काष्ठा esb_dev *edev)
अणु
	ग_लिखोw(ESB_UNLOCK1, ESB_RELOAD_REG(edev));
	ग_लिखोw(ESB_UNLOCK2, ESB_RELOAD_REG(edev));
पूर्ण

अटल पूर्णांक esb_समयr_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा esb_dev *edev = to_esb_dev(wdd);
	पूर्णांक _wdd_nowayout = test_bit(WDOG_NO_WAY_OUT, &wdd->status);
	u8 val;

	esb_unlock_रेजिस्टरs(edev);
	ग_लिखोw(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));
	/* Enable or Enable + Lock? */
	val = ESB_WDT_ENABLE | (_wdd_nowayout ? ESB_WDT_LOCK : 0x00);
	pci_ग_लिखो_config_byte(edev->pdev, ESB_LOCK_REG, val);
	वापस 0;
पूर्ण

अटल पूर्णांक esb_समयr_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा esb_dev *edev = to_esb_dev(wdd);
	u8 val;

	/* First, reset समयrs as suggested by the करोcs */
	esb_unlock_रेजिस्टरs(edev);
	ग_लिखोw(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));
	/* Then disable the WDT */
	pci_ग_लिखो_config_byte(edev->pdev, ESB_LOCK_REG, 0x0);
	pci_पढ़ो_config_byte(edev->pdev, ESB_LOCK_REG, &val);

	/* Returns 0 अगर the समयr was disabled, non-zero otherwise */
	वापस val & ESB_WDT_ENABLE;
पूर्ण

अटल पूर्णांक esb_समयr_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा esb_dev *edev = to_esb_dev(wdd);

	esb_unlock_रेजिस्टरs(edev);
	ग_लिखोw(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));
	/* FIXME: Do we need to flush anything here? */
	वापस 0;
पूर्ण

अटल पूर्णांक esb_समयr_set_heartbeat(काष्ठा watchकरोg_device *wdd,
		अचिन्हित पूर्णांक समय)
अणु
	काष्ठा esb_dev *edev = to_esb_dev(wdd);
	u32 val;

	/* We shअगरt by 9, so अगर we are passed a value of 1 sec,
	 * val will be 1 << 9 = 512, then ग_लिखो that to two
	 * समयrs => 2 * 512 = 1024 (which is decremented at 1KHz)
	 */
	val = समय << 9;

	/* Write समयr 1 */
	esb_unlock_रेजिस्टरs(edev);
	ग_लिखोl(val, ESB_TIMER1_REG(edev));

	/* Write समयr 2 */
	esb_unlock_रेजिस्टरs(edev);
	ग_लिखोl(val, ESB_TIMER2_REG(edev));

	/* Reload */
	esb_unlock_रेजिस्टरs(edev);
	ग_लिखोw(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));

	/* FIXME: Do we need to flush everything out? */

	/* Done */
	wdd->समयout = समय;
	वापस 0;
पूर्ण

/*
 * Watchकरोg Subप्रणाली Interfaces
 */

अटल काष्ठा watchकरोg_info esb_info = अणु
	.identity = ESB_MODULE_NAME,
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops esb_ops = अणु
	.owner = THIS_MODULE,
	.start = esb_समयr_start,
	.stop = esb_समयr_stop,
	.set_समयout = esb_समयr_set_heartbeat,
	.ping = esb_समयr_keepalive,
पूर्ण;

/*
 * Data क्रम PCI driver पूर्णांकerface
 */
अटल स्थिर काष्ठा pci_device_id esb_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ESB_9), पूर्ण,
	अणु 0, पूर्ण,                 /* End of list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, esb_pci_tbl);

/*
 *      Init & निकास routines
 */

अटल अचिन्हित अक्षर esb_getdevice(काष्ठा esb_dev *edev)
अणु
	अगर (pci_enable_device(edev->pdev)) अणु
		dev_err(&edev->pdev->dev, "failed to enable device\n");
		जाओ err_devput;
	पूर्ण

	अगर (pci_request_region(edev->pdev, 0, ESB_MODULE_NAME)) अणु
		dev_err(&edev->pdev->dev, "failed to request region\n");
		जाओ err_disable;
	पूर्ण

	edev->base = pci_ioremap_bar(edev->pdev, 0);
	अगर (edev->base == शून्य) अणु
		/* Something's wrong here, BASEADDR has to be set */
		dev_err(&edev->pdev->dev, "failed to get BASEADDR\n");
		जाओ err_release;
	पूर्ण

	/* Done */
	dev_set_drvdata(&edev->pdev->dev, edev);
	वापस 1;

err_release:
	pci_release_region(edev->pdev, 0);
err_disable:
	pci_disable_device(edev->pdev);
err_devput:
	वापस 0;
पूर्ण

अटल व्योम esb_initdevice(काष्ठा esb_dev *edev)
अणु
	u8 val1;
	u16 val2;

	/*
	 * Config रेजिस्टर:
	 * Bit    5 : 0 = Enable WDT_OUTPUT
	 * Bit    2 : 0 = set the समयr frequency to the PCI घड़ी
	 * भागided by 2^15 (approx 1KHz).
	 * Bits 1:0 : 11 = WDT_INT_TYPE Disabled.
	 * The watchकरोg has two समयrs, it can be setup so that the
	 * expiry of समयr1 results in an पूर्णांकerrupt and the expiry of
	 * समयr2 results in a reboot. We set it to not generate
	 * any पूर्णांकerrupts as there is not much we can करो with it
	 * right now.
	 */
	pci_ग_लिखो_config_word(edev->pdev, ESB_CONFIG_REG, 0x0003);

	/* Check that the WDT isn't alपढ़ोy locked */
	pci_पढ़ो_config_byte(edev->pdev, ESB_LOCK_REG, &val1);
	अगर (val1 & ESB_WDT_LOCK)
		dev_warn(&edev->pdev->dev, "nowayout already set\n");

	/* Set the समयr to watchकरोg mode and disable it क्रम now */
	pci_ग_लिखो_config_byte(edev->pdev, ESB_LOCK_REG, 0x00);

	/* Check अगर the watchकरोg was previously triggered */
	esb_unlock_रेजिस्टरs(edev);
	val2 = पढ़ोw(ESB_RELOAD_REG(edev));
	अगर (val2 & ESB_WDT_TIMEOUT)
		edev->wdd.bootstatus = WDIOF_CARDRESET;

	/* Reset WDT_TIMEOUT flag and समयrs */
	esb_unlock_रेजिस्टरs(edev);
	ग_लिखोw((ESB_WDT_TIMEOUT | ESB_WDT_RELOAD), ESB_RELOAD_REG(edev));

	/* And set the correct समयout value */
	esb_समयr_set_heartbeat(&edev->wdd, edev->wdd.समयout);
पूर्ण

अटल पूर्णांक esb_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा esb_dev *edev;
	पूर्णांक ret;

	edev = devm_kzalloc(&pdev->dev, माप(*edev), GFP_KERNEL);
	अगर (!edev)
		वापस -ENOMEM;

	/* Check whether or not the hardware watchकरोg is there */
	edev->pdev = pdev;
	अगर (!esb_getdevice(edev))
		वापस -ENODEV;

	/* Initialize the watchकरोg and make sure it करोes not run */
	edev->wdd.info = &esb_info;
	edev->wdd.ops = &esb_ops;
	edev->wdd.min_समयout = ESB_HEARTBEAT_MIN;
	edev->wdd.max_समयout = ESB_HEARTBEAT_MAX;
	edev->wdd.समयout = ESB_HEARTBEAT_DEFAULT;
	watchकरोg_init_समयout(&edev->wdd, heartbeat, शून्य);
	watchकरोg_set_nowayout(&edev->wdd, nowayout);
	watchकरोg_stop_on_reboot(&edev->wdd);
	watchकरोg_stop_on_unरेजिस्टर(&edev->wdd);
	esb_initdevice(edev);

	/* Register the watchकरोg so that userspace has access to it */
	ret = watchकरोg_रेजिस्टर_device(&edev->wdd);
	अगर (ret != 0)
		जाओ err_unmap;
	dev_info(&pdev->dev,
		"initialized. heartbeat=%d sec (nowayout=%d)\n",
		edev->wdd.समयout, nowayout);
	वापस 0;

err_unmap:
	iounmap(edev->base);
	pci_release_region(edev->pdev, 0);
	pci_disable_device(edev->pdev);
	वापस ret;
पूर्ण

अटल व्योम esb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा esb_dev *edev = dev_get_drvdata(&pdev->dev);

	watchकरोg_unरेजिस्टर_device(&edev->wdd);
	iounmap(edev->base);
	pci_release_region(edev->pdev, 0);
	pci_disable_device(edev->pdev);
पूर्ण

अटल काष्ठा pci_driver esb_driver = अणु
	.name		= ESB_MODULE_NAME,
	.id_table	= esb_pci_tbl,
	.probe          = esb_probe,
	.हटाओ         = esb_हटाओ,
पूर्ण;

module_pci_driver(esb_driver);

MODULE_AUTHOR("Ross Biro and David Hथअrdeman");
MODULE_DESCRIPTION("Watchdog driver for Intel 6300ESB chipsets");
MODULE_LICENSE("GPL");
