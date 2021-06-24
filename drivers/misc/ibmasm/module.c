<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 *
 * This driver is based on code originally written by Pete Reynolds
 * and others.
 */

/*
 * The ASM device driver करोes the following things:
 *
 * 1) When loaded it sends a message to the service processor,
 * indicating that an OS is * running. This causes the service processor
 * to send periodic heartbeats to the OS.
 *
 * 2) Answers the periodic heartbeats sent by the service processor.
 * Failure to करो so would result in प्रणाली reboot.
 *
 * 3) Acts as a pass through क्रम करोt commands sent from user applications.
 * The पूर्णांकerface क्रम this is the ibmयंत्रfs file प्रणाली.
 *
 * 4) Allows user applications to रेजिस्टर क्रम event notअगरication. Events
 * are sent to the driver through पूर्णांकerrupts. They can be पढ़ो from user
 * space through the ibmयंत्रfs file प्रणाली.
 *
 * 5) Allows user space applications to send heartbeats to the service
 * processor (aka reverse heartbeats). Again this happens through ibmयंत्रfs.
 *
 * 6) Handles remote mouse and keyboard event पूर्णांकerrupts and makes them
 * available to user applications through ibmयंत्रfs.
 *
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश "ibmasm.h"
#समावेश "lowlevel.h"
#समावेश "remote.h"

पूर्णांक ibmयंत्र_debug = 0;
module_param(ibmयंत्र_debug, पूर्णांक , S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ibmयंत्र_debug, " Set debug mode on or off");


अटल पूर्णांक ibmयंत्र_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक result;
	काष्ठा service_processor *sp;

	अगर ((result = pci_enable_device(pdev))) अणु
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		वापस result;
	पूर्ण
	अगर ((result = pci_request_regions(pdev, DRIVER_NAME))) अणु
		dev_err(&pdev->dev, "Failed to allocate PCI resources\n");
		जाओ error_resources;
	पूर्ण
	/* vnc client won't work without bus-mastering */
	pci_set_master(pdev);

	sp = kzalloc(माप(काष्ठा service_processor), GFP_KERNEL);
	अगर (sp == शून्य) अणु
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		result = -ENOMEM;
		जाओ error_kदो_स्मृति;
	पूर्ण

	spin_lock_init(&sp->lock);
	INIT_LIST_HEAD(&sp->command_queue);

	pci_set_drvdata(pdev, (व्योम *)sp);
	sp->dev = &pdev->dev;
	sp->number = pdev->bus->number;
	snम_लिखो(sp->स_नाम, IBMASM_NAME_SIZE, "%d", sp->number);
	snम_लिखो(sp->devname, IBMASM_NAME_SIZE, "%s%d", DRIVER_NAME, sp->number);

	result = ibmयंत्र_event_buffer_init(sp);
	अगर (result) अणु
		dev_err(sp->dev, "Failed to allocate event buffer\n");
		जाओ error_eventbuffer;
	पूर्ण

	result = ibmयंत्र_heartbeat_init(sp);
	अगर (result) अणु
		dev_err(sp->dev, "Failed to allocate heartbeat command\n");
		जाओ error_heartbeat;
	पूर्ण

	sp->irq = pdev->irq;
	sp->base_address = pci_ioremap_bar(pdev, 0);
	अगर (!sp->base_address) अणु
		dev_err(sp->dev, "Failed to ioremap pci memory\n");
		result =  -ENODEV;
		जाओ error_ioremap;
	पूर्ण

	result = request_irq(sp->irq, ibmयंत्र_पूर्णांकerrupt_handler, IRQF_SHARED, sp->devname, (व्योम*)sp);
	अगर (result) अणु
		dev_err(sp->dev, "Failed to register interrupt handler\n");
		जाओ error_request_irq;
	पूर्ण

	enable_sp_पूर्णांकerrupts(sp->base_address);

	result = ibmयंत्र_init_remote_input_dev(sp);
	अगर (result) अणु
		dev_err(sp->dev, "Failed to initialize remote queue\n");
		जाओ error_send_message;
	पूर्ण

	result = ibmयंत्र_send_driver_vpd(sp);
	अगर (result) अणु
		dev_err(sp->dev, "Failed to send driver VPD to service processor\n");
		जाओ error_send_message;
	पूर्ण
	result = ibmयंत्र_send_os_state(sp, SYSTEM_STATE_OS_UP);
	अगर (result) अणु
		dev_err(sp->dev, "Failed to send OS state to service processor\n");
		जाओ error_send_message;
	पूर्ण
	ibmयंत्रfs_add_sp(sp);

	ibmयंत्र_रेजिस्टर_uart(sp);

	वापस 0;

error_send_message:
	disable_sp_पूर्णांकerrupts(sp->base_address);
	ibmयंत्र_मुक्त_remote_input_dev(sp);
	मुक्त_irq(sp->irq, (व्योम *)sp);
error_request_irq:
	iounmap(sp->base_address);
error_ioremap:
	ibmयंत्र_heartbeat_निकास(sp);
error_heartbeat:
	ibmयंत्र_event_buffer_निकास(sp);
error_eventbuffer:
	kमुक्त(sp);
error_kदो_स्मृति:
        pci_release_regions(pdev);
error_resources:
        pci_disable_device(pdev);

	वापस result;
पूर्ण

अटल व्योम ibmयंत्र_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा service_processor *sp = pci_get_drvdata(pdev);

	dbg("Unregistering UART\n");
	ibmयंत्र_unरेजिस्टर_uart(sp);
	dbg("Sending OS down message\n");
	अगर (ibmयंत्र_send_os_state(sp, SYSTEM_STATE_OS_DOWN))
		err("failed to get response to 'Send OS State' command\n");
	dbg("Disabling heartbeats\n");
	ibmयंत्र_heartbeat_निकास(sp);
	dbg("Disabling interrupts\n");
	disable_sp_पूर्णांकerrupts(sp->base_address);
	dbg("Freeing SP irq\n");
	मुक्त_irq(sp->irq, (व्योम *)sp);
	dbg("Cleaning up\n");
	ibmयंत्र_मुक्त_remote_input_dev(sp);
	iounmap(sp->base_address);
	ibmयंत्र_event_buffer_निकास(sp);
	kमुक्त(sp);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_device_id ibmयंत्र_pci_table[] =
अणु
	अणु PCI_DEVICE(VENDORID_IBM, DEVICEID_RSA) पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ibmयंत्र_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= ibmयंत्र_pci_table,
	.probe		= ibmयंत्र_init_one,
	.हटाओ		= ibmयंत्र_हटाओ_one,
पूर्ण;

अटल व्योम __निकास ibmयंत्र_निकास (व्योम)
अणु
	ibmयंत्र_unरेजिस्टर_panic_notअगरier();
	ibmयंत्रfs_unरेजिस्टर();
	pci_unरेजिस्टर_driver(&ibmयंत्र_driver);
	info(DRIVER_DESC " version " DRIVER_VERSION " unloaded");
पूर्ण

अटल पूर्णांक __init ibmयंत्र_init(व्योम)
अणु
	पूर्णांक result = pci_रेजिस्टर_driver(&ibmयंत्र_driver);
	अगर (result)
		वापस result;

	result = ibmयंत्रfs_रेजिस्टर();
	अगर (result) अणु
		pci_unरेजिस्टर_driver(&ibmयंत्र_driver);
		err("Failed to register ibmasmfs file system");
		वापस result;
	पूर्ण

	ibmयंत्र_रेजिस्टर_panic_notअगरier();
	info(DRIVER_DESC " version " DRIVER_VERSION " loaded");
	वापस 0;
पूर्ण

module_init(ibmयंत्र_init);
module_निकास(ibmयंत्र_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ibmयंत्र_pci_table);

