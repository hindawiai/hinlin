<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* uio_pci_generic - generic UIO driver क्रम PCI 2.3 devices
 *
 * Copyright (C) 2009 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * Since the driver करोes not declare any device ids, you must allocate
 * id and bind the device to the driver yourself.  For example:
 *
 * # echo "8086 10f5" > /sys/bus/pci/drivers/uio_pci_generic/new_id
 * # echo -n 0000:00:19.0 > /sys/bus/pci/drivers/e1000e/unbind
 * # echo -n 0000:00:19.0 > /sys/bus/pci/drivers/uio_pci_generic/bind
 * # ls -l /sys/bus/pci/devices/0000:00:19.0/driver
 * .../0000:00:19.0/driver -> ../../../bus/pci/drivers/uio_pci_generic
 *
 * Driver won't bind to devices which करो not support the Interrupt Disable Bit
 * in the command रेजिस्टर. All devices compliant to PCI 2.3 (circa 2002) and
 * all compliant PCI Express devices should support this bit.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uio_driver.h>

#घोषणा DRIVER_VERSION	"0.01.0"
#घोषणा DRIVER_AUTHOR	"Michael S. Tsirkin <mst@redhat.com>"
#घोषणा DRIVER_DESC	"Generic UIO driver for PCI 2.3 devices"

काष्ठा uio_pci_generic_dev अणु
	काष्ठा uio_info info;
	काष्ठा pci_dev *pdev;
पूर्ण;

अटल अंतरभूत काष्ठा uio_pci_generic_dev *
to_uio_pci_generic_dev(काष्ठा uio_info *info)
अणु
	वापस container_of(info, काष्ठा uio_pci_generic_dev, info);
पूर्ण

अटल पूर्णांक release(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा uio_pci_generic_dev *gdev = to_uio_pci_generic_dev(info);

	/*
	 * This driver is insecure when used with devices करोing DMA, but some
	त * people (mis)use it with such devices.
	त * Let's at least make sure DMA isn't left enabled after the userspace
	त * driver बंदs the fd.
	त * Note that there's a non-zero chance करोing this will wedge the device
	त * at least until reset.
	 */
	pci_clear_master(gdev->pdev);
	वापस 0;
पूर्ण

/* Interrupt handler. Read/modअगरy/ग_लिखो the command रेजिस्टर to disable
 * the पूर्णांकerrupt. */
अटल irqवापस_t irqhandler(पूर्णांक irq, काष्ठा uio_info *info)
अणु
	काष्ठा uio_pci_generic_dev *gdev = to_uio_pci_generic_dev(info);

	अगर (!pci_check_and_mask_पूर्णांकx(gdev->pdev))
		वापस IRQ_NONE;

	/* UIO core will संकेत the user process. */
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uio_pci_generic_dev *gdev;
	पूर्णांक err;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "%s: pci_enable_device failed: %d\n",
			__func__, err);
		वापस err;
	पूर्ण

	अगर (pdev->irq && !pci_पूर्णांकx_mask_supported(pdev))
		वापस -ENODEV;

	gdev = devm_kzalloc(&pdev->dev, माप(काष्ठा uio_pci_generic_dev), GFP_KERNEL);
	अगर (!gdev)
		वापस -ENOMEM;

	gdev->info.name = "uio_pci_generic";
	gdev->info.version = DRIVER_VERSION;
	gdev->info.release = release;
	gdev->pdev = pdev;
	अगर (pdev->irq && (pdev->irq != IRQ_NOTCONNECTED)) अणु
		gdev->info.irq = pdev->irq;
		gdev->info.irq_flags = IRQF_SHARED;
		gdev->info.handler = irqhandler;
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev, "No IRQ assigned to device: "
			 "no support for interrupts?\n");
	पूर्ण

	वापस devm_uio_रेजिस्टर_device(&pdev->dev, &gdev->info);
पूर्ण

अटल काष्ठा pci_driver uio_pci_driver = अणु
	.name = "uio_pci_generic",
	.id_table = शून्य, /* only dynamic id's */
	.probe = probe,
पूर्ण;

module_pci_driver(uio_pci_driver);
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
