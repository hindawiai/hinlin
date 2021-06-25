<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    dmx3191d.c - driver क्रम the Domex DMX3191D SCSI card.
    Copyright (C) 2000 by Massimo Piccioni <dafastidio@libero.it>
    Portions Copyright (C) 2004 by Christoph Hellwig <hch@lst.de>

    Based on the generic NCR5380 driver by Drew Eckhardt et al.

*/

#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi_host.h>

/*
 * Definitions क्रम the generic 5380 driver.
 */

#घोषणा NCR5380_पढ़ो(reg)		inb(hostdata->base + (reg))
#घोषणा NCR5380_ग_लिखो(reg, value)	outb(value, hostdata->base + (reg))

#घोषणा NCR5380_dma_xfer_len		NCR5380_dma_xfer_none
#घोषणा NCR5380_dma_recv_setup		NCR5380_dma_setup_none
#घोषणा NCR5380_dma_send_setup		NCR5380_dma_setup_none
#घोषणा NCR5380_dma_residual		NCR5380_dma_residual_none

#घोषणा NCR5380_implementation_fields	/* none */

#समावेश "NCR5380.h"
#समावेश "NCR5380.c"

#घोषणा DMX3191D_DRIVER_NAME	"dmx3191d"
#घोषणा DMX3191D_REGION_LEN	8


अटल काष्ठा scsi_host_ढाँचा dmx3191d_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= DMX3191D_DRIVER_NAME,
	.name			= "Domex DMX3191D",
	.info			= NCR5380_info,
	.queuecommand		= NCR5380_queue_command,
	.eh_पात_handler	= NCR5380_पात,
	.eh_host_reset_handler	= NCR5380_host_reset,
	.can_queue		= 32,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= 2,
	.dma_boundary		= PAGE_SIZE - 1,
	.cmd_size		= NCR5380_CMD_SIZE,
पूर्ण;

अटल पूर्णांक dmx3191d_probe_one(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा NCR5380_hostdata *hostdata;
	अचिन्हित दीर्घ io;
	पूर्णांक error = -ENODEV;

	अगर (pci_enable_device(pdev))
		जाओ out;

	io = pci_resource_start(pdev, 0);
	अगर (!request_region(io, DMX3191D_REGION_LEN, DMX3191D_DRIVER_NAME)) अणु
		prपूर्णांकk(KERN_ERR "dmx3191: region 0x%lx-0x%lx already reserved\n",
				io, io + DMX3191D_REGION_LEN);
		जाओ out_disable_device;
	पूर्ण

	shost = scsi_host_alloc(&dmx3191d_driver_ढाँचा,
			माप(काष्ठा NCR5380_hostdata));
	अगर (!shost)
		जाओ out_release_region;       

	hostdata = shost_priv(shost);
	hostdata->base = io;

	/* This card करोes not seem to उठाओ an पूर्णांकerrupt on pdev->irq.
	 * Steam-घातered SCSI controllers run without an IRQ anyway.
	 */
	shost->irq = NO_IRQ;

	error = NCR5380_init(shost, 0);
	अगर (error)
		जाओ out_host_put;

	NCR5380_maybe_reset_bus(shost);

	pci_set_drvdata(pdev, shost);

	error = scsi_add_host(shost, &pdev->dev);
	अगर (error)
		जाओ out_निकास;

	scsi_scan_host(shost);
	वापस 0;

out_निकास:
	NCR5380_निकास(shost);
out_host_put:
	scsi_host_put(shost);
 out_release_region:
	release_region(io, DMX3191D_REGION_LEN);
 out_disable_device:
	pci_disable_device(pdev);
 out:
	वापस error;
पूर्ण

अटल व्योम dmx3191d_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(shost);
	अचिन्हित दीर्घ io = hostdata->base;

	scsi_हटाओ_host(shost);

	NCR5380_निकास(shost);
	scsi_host_put(shost);
	release_region(io, DMX3191D_REGION_LEN);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_device_id dmx3191d_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_DOMEX, PCI_DEVICE_ID_DOMEX_DMX3191D,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dmx3191d_pci_tbl);

अटल काष्ठा pci_driver dmx3191d_pci_driver = अणु
	.name		= DMX3191D_DRIVER_NAME,
	.id_table	= dmx3191d_pci_tbl,
	.probe		= dmx3191d_probe_one,
	.हटाओ		= dmx3191d_हटाओ_one,
पूर्ण;

module_pci_driver(dmx3191d_pci_driver);

MODULE_AUTHOR("Massimo Piccioni <dafastidio@libero.it>");
MODULE_DESCRIPTION("Domex DMX3191D SCSI driver");
MODULE_LICENSE("GPL");
