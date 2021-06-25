<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <linux/kmod.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_reg.h"
#समावेश "mantis_pci.h"

#घोषणा DRIVER_NAME		"Mantis Core"

पूर्णांक mantis_pci_init(काष्ठा mantis_pci *mantis)
अणु
	u8 latency;
	काष्ठा mantis_hwconfig *config	= mantis->hwconfig;
	काष्ठा pci_dev *pdev		= mantis->pdev;
	पूर्णांक err, ret = 0;

	dprपूर्णांकk(MANTIS_ERROR, 0, "found a %s PCI %s device on (%02x:%02x.%x),\n",
		config->model_name,
		config->dev_type,
		mantis->pdev->bus->number,
		PCI_SLOT(mantis->pdev->devfn),
		PCI_FUNC(mantis->pdev->devfn));

	err = pci_enable_device(pdev);
	अगर (err != 0) अणु
		ret = -ENODEV;
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: PCI enable failed <%i>", err);
		जाओ fail0;
	पूर्ण

	err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err != 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Unable to obtain 32 bit DMA <%i>", err);
		ret = -ENOMEM;
		जाओ fail1;
	पूर्ण

	pci_set_master(pdev);

	अगर (!request_mem_region(pci_resource_start(pdev, 0),
				pci_resource_len(pdev, 0),
				DRIVER_NAME)) अणु

		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: BAR0 Request failed !");
		ret = -ENODEV;
		जाओ fail1;
	पूर्ण

	mantis->mmio = ioremap(pci_resource_start(pdev, 0),
			       pci_resource_len(pdev, 0));

	अगर (!mantis->mmio) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: BAR0 remap failed !");
		ret = -ENODEV;
		जाओ fail2;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &latency);
	mantis->latency = latency;
	mantis->revision = pdev->revision;

	dprपूर्णांकk(MANTIS_ERROR, 0, "    Mantis Rev %d [%04x:%04x], ",
		mantis->revision,
		mantis->pdev->subप्रणाली_venकरोr,
		mantis->pdev->subप्रणाली_device);

	dprपूर्णांकk(MANTIS_ERROR, 0,
		"irq: %d, latency: %d\n    memory: 0x%lx, mmio: 0x%p\n",
		mantis->pdev->irq,
		mantis->latency,
		mantis->mantis_addr,
		mantis->mmio);

	err = request_irq(pdev->irq,
			  config->irq_handler,
			  IRQF_SHARED,
			  DRIVER_NAME,
			  mantis);

	अगर (err != 0) अणु

		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: IRQ registration failed ! <%d>", err);
		ret = -ENODEV;
		जाओ fail3;
	पूर्ण

	pci_set_drvdata(pdev, mantis);
	वापस ret;

	/* Error conditions */
fail3:
	dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: <%d> I/O unmap", ret);
	अगर (mantis->mmio)
		iounmap(mantis->mmio);

fail2:
	dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: <%d> releasing regions", ret);
	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));

fail1:
	dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: <%d> disabling device", ret);
	pci_disable_device(pdev);

fail0:
	dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: <%d> exiting", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_pci_init);

व्योम mantis_pci_निकास(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा pci_dev *pdev = mantis->pdev;

	dprपूर्णांकk(MANTIS_NOTICE, 1, " mem: 0x%p", mantis->mmio);
	मुक्त_irq(pdev->irq, mantis);
	अगर (mantis->mmio) अणु
		iounmap(mantis->mmio);
		release_mem_region(pci_resource_start(pdev, 0),
				   pci_resource_len(pdev, 0));
	पूर्ण

	pci_disable_device(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(mantis_pci_निकास);

MODULE_DESCRIPTION("Mantis PCI DTV bridge driver");
MODULE_AUTHOR("Manu Abraham");
MODULE_LICENSE("GPL");
