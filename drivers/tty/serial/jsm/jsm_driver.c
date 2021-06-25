<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/************************************************************************
 * Copyright 2003 Digi International (www.digi.com)
 *
 * Copyright (C) 2004 IBM Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 * Scott H Kilau <Scott_Kilau@digi.com>
 * Wendy Xiong   <wendyx@us.ibm.com>
 *
 *
 ***********************************************************************/
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "jsm.h"

MODULE_AUTHOR("Digi International, https://www.digi.com");
MODULE_DESCRIPTION("Driver for the Digi International Neo and Classic PCI based product line");
MODULE_LICENSE("GPL");

#घोषणा JSM_DRIVER_NAME "jsm"
#घोषणा NR_PORTS	32
#घोषणा JSM_MINOR_START	0

काष्ठा uart_driver jsm_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= JSM_DRIVER_NAME,
	.dev_name	= "ttyn",
	.major		= 0,
	.minor		= JSM_MINOR_START,
	.nr		= NR_PORTS,
पूर्ण;

अटल pci_ers_result_t jsm_io_error_detected(काष्ठा pci_dev *pdev,
					pci_channel_state_t state);
अटल pci_ers_result_t jsm_io_slot_reset(काष्ठा pci_dev *pdev);
अटल व्योम jsm_io_resume(काष्ठा pci_dev *pdev);

अटल स्थिर काष्ठा pci_error_handlers jsm_err_handler = अणु
	.error_detected = jsm_io_error_detected,
	.slot_reset = jsm_io_slot_reset,
	.resume = jsm_io_resume,
पूर्ण;

पूर्णांक jsm_debug;
module_param(jsm_debug, पूर्णांक, 0);
MODULE_PARM_DESC(jsm_debug, "Driver debugging level");

अटल पूर्णांक jsm_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc = 0;
	काष्ठा jsm_board *brd;
	अटल पूर्णांक adapter_count;

	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Device enable FAILED\n");
		जाओ out;
	पूर्ण

	rc = pci_request_regions(pdev, JSM_DRIVER_NAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "pci_request_region FAILED\n");
		जाओ out_disable_device;
	पूर्ण

	brd = kzalloc(माप(*brd), GFP_KERNEL);
	अगर (!brd) अणु
		rc = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण

	/* store the info क्रम the board we've found */
	brd->boardnum = adapter_count++;
	brd->pci_dev = pdev;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_NEO_2DB9:
	हाल PCI_DEVICE_ID_NEO_2DB9PRI:
	हाल PCI_DEVICE_ID_NEO_2RJ45:
	हाल PCI_DEVICE_ID_NEO_2RJ45PRI:
	हाल PCI_DEVICE_ID_NEO_2_422_485:
		brd->maxports = 2;
		अवरोध;

	हाल PCI_DEVICE_ID_CLASSIC_4:
	हाल PCI_DEVICE_ID_CLASSIC_4_422:
	हाल PCI_DEVICE_ID_NEO_4:
	हाल PCIE_DEVICE_ID_NEO_4:
	हाल PCIE_DEVICE_ID_NEO_4RJ45:
	हाल PCIE_DEVICE_ID_NEO_4_IBM:
		brd->maxports = 4;
		अवरोध;

	हाल PCI_DEVICE_ID_CLASSIC_8:
	हाल PCI_DEVICE_ID_CLASSIC_8_422:
	हाल PCI_DEVICE_ID_DIGI_NEO_8:
	हाल PCIE_DEVICE_ID_NEO_8:
	हाल PCIE_DEVICE_ID_NEO_8RJ45:
		brd->maxports = 8;
		अवरोध;

	शेष:
		brd->maxports = 1;
		अवरोध;
	पूर्ण

	spin_lock_init(&brd->bd_पूर्णांकr_lock);

	/* store which revision we have */
	brd->rev = pdev->revision;

	brd->irq = pdev->irq;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_CLASSIC_4:
	हाल PCI_DEVICE_ID_CLASSIC_4_422:
	हाल PCI_DEVICE_ID_CLASSIC_8:
	हाल PCI_DEVICE_ID_CLASSIC_8_422:

		jsm_dbg(INIT, &brd->pci_dev,
			"jsm_found_board - Classic adapter\n");

		/*
		 * For PCI ClassicBoards
		 * PCI Local Address (.i.e. "resource" number) space
		 * 0	PLX Memory Mapped Config
		 * 1	PLX I/O Mapped Config
		 * 2	I/O Mapped UARTs and Status
		 * 3	Memory Mapped VPD
		 * 4	Memory Mapped UARTs and Status
		 */

		/* Get the PCI Base Address Registers */
		brd->membase = pci_resource_start(pdev, 4);
		brd->membase_end = pci_resource_end(pdev, 4);

		अगर (brd->membase & 0x1)
			brd->membase &= ~0x3;
		अन्यथा
			brd->membase &= ~0xF;

		brd->iobase = pci_resource_start(pdev, 1);
		brd->iobase_end = pci_resource_end(pdev, 1);
		brd->iobase = ((अचिन्हित पूर्णांक)(brd->iobase)) & 0xFFFE;

		/* Assign the board_ops काष्ठा */
		brd->bd_ops = &jsm_cls_ops;

		brd->bd_uart_offset = 0x8;
		brd->bd_भागidend = 921600;

		brd->re_map_membase = ioremap(brd->membase,
						pci_resource_len(pdev, 4));
		अगर (!brd->re_map_membase) अणु
			dev_err(&pdev->dev,
				"Card has no PCI Memory resources, failing board.\n");
			rc = -ENOMEM;
			जाओ out_kमुक्त_brd;
		पूर्ण

		/*
		 * Enable Local Interrupt 1			(0x1),
		 * Local Interrupt 1 Polarity Active high	(0x2),
		 * Enable PCI पूर्णांकerrupt				(0x43)
		 */
		outb(0x43, brd->iobase + 0x4c);

		अवरोध;

	हाल PCI_DEVICE_ID_NEO_2DB9:
	हाल PCI_DEVICE_ID_NEO_2DB9PRI:
	हाल PCI_DEVICE_ID_NEO_2RJ45:
	हाल PCI_DEVICE_ID_NEO_2RJ45PRI:
	हाल PCI_DEVICE_ID_NEO_2_422_485:
	हाल PCI_DEVICE_ID_NEO_4:
	हाल PCIE_DEVICE_ID_NEO_4:
	हाल PCIE_DEVICE_ID_NEO_4RJ45:
	हाल PCIE_DEVICE_ID_NEO_4_IBM:
	हाल PCI_DEVICE_ID_DIGI_NEO_8:
	हाल PCIE_DEVICE_ID_NEO_8:
	हाल PCIE_DEVICE_ID_NEO_8RJ45:

		jsm_dbg(INIT, &brd->pci_dev, "jsm_found_board - NEO adapter\n");

		/* get the PCI Base Address Registers */
		brd->membase	= pci_resource_start(pdev, 0);
		brd->membase_end = pci_resource_end(pdev, 0);

		अगर (brd->membase & 1)
			brd->membase &= ~0x3;
		अन्यथा
			brd->membase &= ~0xF;

		/* Assign the board_ops काष्ठा */
		brd->bd_ops = &jsm_neo_ops;

		brd->bd_uart_offset = 0x200;
		brd->bd_भागidend = 921600;

		brd->re_map_membase = ioremap(brd->membase,
						pci_resource_len(pdev, 0));
		अगर (!brd->re_map_membase) अणु
			dev_err(&pdev->dev,
				"Card has no PCI Memory resources, failing board.\n");
			rc = -ENOMEM;
			जाओ out_kमुक्त_brd;
		पूर्ण

		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	rc = request_irq(brd->irq, brd->bd_ops->पूर्णांकr, IRQF_SHARED, "JSM", brd);
	अगर (rc) अणु
		dev_warn(&pdev->dev, "Failed to hook IRQ %d\n", brd->irq);
		जाओ out_iounmap;
	पूर्ण

	rc = jsm_tty_init(brd);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Can't init tty devices (%d)\n", rc);
		rc = -ENXIO;
		जाओ out_मुक्त_irq;
	पूर्ण

	rc = jsm_uart_port_init(brd);
	अगर (rc < 0) अणु
		/* XXX: leaking all resources from jsm_tty_init here! */
		dev_err(&pdev->dev, "Can't init uart port (%d)\n", rc);
		rc = -ENXIO;
		जाओ out_मुक्त_irq;
	पूर्ण

	/* Log the inक्रमmation about the board */
	dev_info(&pdev->dev, "board %d: Digi Classic/Neo (rev %d), irq %d\n",
			adapter_count, brd->rev, brd->irq);

	pci_set_drvdata(pdev, brd);
	pci_save_state(pdev);

	वापस 0;
 out_मुक्त_irq:
	jsm_हटाओ_uart_port(brd);
	मुक्त_irq(brd->irq, brd);
 out_iounmap:
	iounmap(brd->re_map_membase);
 out_kमुक्त_brd:
	kमुक्त(brd);
 out_release_regions:
	pci_release_regions(pdev);
 out_disable_device:
	pci_disable_device(pdev);
 out:
	वापस rc;
पूर्ण

अटल व्योम jsm_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा jsm_board *brd = pci_get_drvdata(pdev);
	पूर्णांक i = 0;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_CLASSIC_4:
	हाल PCI_DEVICE_ID_CLASSIC_4_422:
	हाल PCI_DEVICE_ID_CLASSIC_8:
	हाल PCI_DEVICE_ID_CLASSIC_8_422:
		/* Tell card not to पूर्णांकerrupt anymore. */
		outb(0x0, brd->iobase + 0x4c);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	jsm_हटाओ_uart_port(brd);

	मुक्त_irq(brd->irq, brd);
	iounmap(brd->re_map_membase);

	/* Free all allocated channels काष्ठाs */
	क्रम (i = 0; i < brd->maxports; i++) अणु
		अगर (brd->channels[i]) अणु
			kमुक्त(brd->channels[i]->ch_rqueue);
			kमुक्त(brd->channels[i]->ch_equeue);
			kमुक्त(brd->channels[i]);
		पूर्ण
	पूर्ण

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(brd);
पूर्ण

अटल स्थिर काष्ठा pci_device_id jsm_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_2DB9), 0, 0, 0 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_2DB9PRI), 0, 0, 1 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_2RJ45), 0, 0, 2 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_2RJ45PRI), 0, 0, 3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCIE_DEVICE_ID_NEO_4_IBM), 0, 0, 4 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_DIGI_NEO_8), 0, 0, 5 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_4), 0, 0, 6 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_1_422), 0, 0, 7 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_1_422_485), 0, 0, 8 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_NEO_2_422_485), 0, 0, 9 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCIE_DEVICE_ID_NEO_8), 0, 0, 10 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCIE_DEVICE_ID_NEO_4), 0, 0, 11 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCIE_DEVICE_ID_NEO_4RJ45), 0, 0, 12 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCIE_DEVICE_ID_NEO_8RJ45), 0, 0, 13 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_CLASSIC_4), 0, 0, 14 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_CLASSIC_4_422), 0, 0, 15 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_CLASSIC_8), 0, 0, 16 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DIGI, PCI_DEVICE_ID_CLASSIC_8_422), 0, 0, 17 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, jsm_pci_tbl);

अटल काष्ठा pci_driver jsm_driver = अणु
	.name		= JSM_DRIVER_NAME,
	.id_table	= jsm_pci_tbl,
	.probe		= jsm_probe_one,
	.हटाओ		= jsm_हटाओ_one,
	.err_handler    = &jsm_err_handler,
पूर्ण;

अटल pci_ers_result_t jsm_io_error_detected(काष्ठा pci_dev *pdev,
					pci_channel_state_t state)
अणु
	काष्ठा jsm_board *brd = pci_get_drvdata(pdev);

	jsm_हटाओ_uart_port(brd);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t jsm_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc;

	rc = pci_enable_device(pdev);

	अगर (rc)
		वापस PCI_ERS_RESULT_DISCONNECT;

	pci_set_master(pdev);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम jsm_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा jsm_board *brd = pci_get_drvdata(pdev);

	pci_restore_state(pdev);
	pci_save_state(pdev);

	jsm_uart_port_init(brd);
पूर्ण

अटल पूर्णांक __init jsm_init_module(व्योम)
अणु
	पूर्णांक rc;

	rc = uart_रेजिस्टर_driver(&jsm_uart_driver);
	अगर (!rc) अणु
		rc = pci_रेजिस्टर_driver(&jsm_driver);
		अगर (rc)
			uart_unरेजिस्टर_driver(&jsm_uart_driver);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम __निकास jsm_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&jsm_driver);
	uart_unरेजिस्टर_driver(&jsm_uart_driver);
पूर्ण

module_init(jsm_init_module);
module_निकास(jsm_निकास_module);
