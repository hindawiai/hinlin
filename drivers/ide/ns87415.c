<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1997-1998	Mark Lord <mlord@pobox.com>
 * Copyright (C) 1998		Eddie C. Dost <ecd@skynet.be>
 * Copyright (C) 1999-2000	Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2004		Grant Grundler <grundler at parisc-linux.org>
 *
 * Inspired by an earlier efक्रमt from David S. Miller <davem@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "ns87415"

#अगर_घोषित CONFIG_SUPERIO
/* SUPERIO 87560 is a PoS chip that NatSem denies exists.
 * Unक्रमtunately, it's built-in on all Astro-based PA-RISC workstations
 * which use the पूर्णांकegrated NS87514 cell क्रम CD-ROM support.
 * i.e we have to support क्रम CD-ROM installs.
 * See drivers/parisc/superio.c क्रम more gory details.
 */
#समावेश <यंत्र/superपन.स>

#घोषणा SUPERIO_IDE_MAX_RETRIES 25

/* Because of a defect in Super I/O, all पढ़ोs of the PCI DMA status 
 * रेजिस्टरs, IDE status रेजिस्टर and the IDE select रेजिस्टर need to be 
 * retried
 */
अटल u8 superio_ide_inb (अचिन्हित दीर्घ port)
अणु
	u8 पंचांगp;
	पूर्णांक retries = SUPERIO_IDE_MAX_RETRIES;

	/* prपूर्णांकk(" [ reading port 0x%x with retry ] ", port); */

	करो अणु
		पंचांगp = inb(port);
		अगर (पंचांगp == 0)
			udelay(50);
	पूर्ण जबतक (पंचांगp == 0 && retries-- > 0);

	वापस पंचांगp;
पूर्ण

अटल u8 superio_पढ़ो_status(ide_hwअगर_t *hwअगर)
अणु
	वापस superio_ide_inb(hwअगर->io_ports.status_addr);
पूर्ण

अटल u8 superio_dma_sff_पढ़ो_status(ide_hwअगर_t *hwअगर)
अणु
	वापस superio_ide_inb(hwअगर->dma_base + ATA_DMA_STATUS);
पूर्ण

अटल व्योम superio_tf_पढ़ो(ide_drive_t *drive, काष्ठा ide_taskfile *tf,
			    u8 valid)
अणु
	काष्ठा ide_io_ports *io_ports = &drive->hwअगर->io_ports;

	अगर (valid & IDE_VALID_ERROR)
		tf->error  = inb(io_ports->feature_addr);
	अगर (valid & IDE_VALID_NSECT)
		tf->nsect  = inb(io_ports->nsect_addr);
	अगर (valid & IDE_VALID_LBAL)
		tf->lbal   = inb(io_ports->lbal_addr);
	अगर (valid & IDE_VALID_LBAM)
		tf->lbam   = inb(io_ports->lbam_addr);
	अगर (valid & IDE_VALID_LBAH)
		tf->lbah   = inb(io_ports->lbah_addr);
	अगर (valid & IDE_VALID_DEVICE)
		tf->device = superio_ide_inb(io_ports->device_addr);
पूर्ण

अटल व्योम ns87415_dev_select(ide_drive_t *drive);

अटल स्थिर काष्ठा ide_tp_ops superio_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= superio_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ns87415_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= superio_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

अटल व्योम superio_init_iops(काष्ठा hwअगर_s *hwअगर)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	u32 dma_stat;
	u8 port = hwअगर->channel, पंचांगp;

	dma_stat = (pci_resource_start(pdev, 4) & ~3) + (!port ? 2 : 0xa);

	/* Clear error/पूर्णांकerrupt, enable dma */
	पंचांगp = superio_ide_inb(dma_stat);
	outb(पंचांगp | 0x66, dma_stat);
पूर्ण
#अन्यथा
#घोषणा superio_dma_sff_पढ़ो_status ide_dma_sff_पढ़ो_status
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक ns87415_count = 0, ns87415_control[MAX_HWIFS] = अणु 0 पूर्ण;

/*
 * This routine either enables/disables (according to IDE_DFLAG_PRESENT)
 * the IRQ associated with the port,
 * and selects either PIO or DMA handshaking क्रम the next I/O operation.
 */
अटल व्योम ns87415_prepare_drive (ide_drive_t *drive, अचिन्हित पूर्णांक use_dma)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित पूर्णांक bit, other, new, *old = (अचिन्हित पूर्णांक *) hwअगर->select_data;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	new = *old;

	/* Adjust IRQ enable bit */
	bit = 1 << (8 + hwअगर->channel);

	अगर (drive->dev_flags & IDE_DFLAG_PRESENT)
		new &= ~bit;
	अन्यथा
		new |= bit;

	/* Select PIO or DMA, DMA may only be selected क्रम one drive/channel. */
	bit   = 1 << (20 + (drive->dn & 1) + (hwअगर->channel << 1));
	other = 1 << (20 + (1 - (drive->dn & 1)) + (hwअगर->channel << 1));
	new = use_dma ? ((new & ~other) | bit) : (new & ~bit);

	अगर (new != *old) अणु
		अचिन्हित अक्षर stat;

		/*
		 * Don't change DMA engine settings जबतक Write Buffers
		 * are busy.
		 */
		(व्योम) pci_पढ़ो_config_byte(dev, 0x43, &stat);
		जबतक (stat & 0x03) अणु
			udelay(1);
			(व्योम) pci_पढ़ो_config_byte(dev, 0x43, &stat);
		पूर्ण

		*old = new;
		(व्योम) pci_ग_लिखो_config_dword(dev, 0x40, new);

		/*
		 * And let things settle...
		 */
		udelay(10);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम ns87415_dev_select(ide_drive_t *drive)
अणु
	ns87415_prepare_drive(drive,
			      !!(drive->dev_flags & IDE_DFLAG_USING_DMA));

	outb(drive->select | ATA_DEVICE_OBS, drive->hwअगर->io_ports.device_addr);
पूर्ण

अटल व्योम ns87415_dma_start(ide_drive_t *drive)
अणु
	ns87415_prepare_drive(drive, 1);
	ide_dma_start(drive);
पूर्ण

अटल पूर्णांक ns87415_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_stat = 0, dma_cmd = 0;

	dma_stat = hwअगर->dma_ops->dma_sff_पढ़ो_status(hwअगर);
	/* get DMA command mode */
	dma_cmd = inb(hwअगर->dma_base + ATA_DMA_CMD);
	/* stop DMA */
	outb(dma_cmd & ~1, hwअगर->dma_base + ATA_DMA_CMD);
	/* from ERRATA: clear the INTR & ERROR bits */
	dma_cmd = inb(hwअगर->dma_base + ATA_DMA_CMD);
	outb(dma_cmd | 6, hwअगर->dma_base + ATA_DMA_CMD);

	ns87415_prepare_drive(drive, 0);

	/* verअगरy good DMA status */
	वापस (dma_stat & 7) != 4;
पूर्ण

अटल व्योम init_hwअगर_ns87415 (ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित पूर्णांक ctrl, using_पूर्णांकa;
	u8 progअगर;
#अगर_घोषित __sparc_v9__
	पूर्णांक समयout;
	u8 stat;
#पूर्ण_अगर

	/*
	 * We cannot probe क्रम IRQ: both ports share common IRQ on INTA.
	 * Also, leave IRQ masked during drive probing, to prevent infinite
	 * पूर्णांकerrupts from a potentially भग्नing INTA..
	 *
	 * IRQs get unmasked in dev_select() when drive is first used.
	 */
	(व्योम) pci_पढ़ो_config_dword(dev, 0x40, &ctrl);
	(व्योम) pci_पढ़ो_config_byte(dev, 0x09, &progअगर);
	/* is irq in "native" mode? */
	using_पूर्णांकa = progअगर & (1 << (hwअगर->channel << 1));
	अगर (!using_पूर्णांकa)
		using_पूर्णांकa = ctrl & (1 << (4 + hwअगर->channel));
	अगर (hwअगर->mate) अणु
		hwअगर->select_data = hwअगर->mate->select_data;
	पूर्ण अन्यथा अणु
		hwअगर->select_data = (अचिन्हित दीर्घ)
					&ns87415_control[ns87415_count++];
		ctrl |= (1 << 8) | (1 << 9);	/* mask both IRQs */
		अगर (using_पूर्णांकa)
			ctrl &= ~(1 << 6);	/* unmask INTA */
		*((अचिन्हित पूर्णांक *)hwअगर->select_data) = ctrl;
		(व्योम) pci_ग_लिखो_config_dword(dev, 0x40, ctrl);

		/*
		 * Set prefetch size to 512 bytes क्रम both ports,
		 * but करोn't turn on/off prefetching here.
		 */
		pci_ग_लिखो_config_byte(dev, 0x55, 0xee);

#अगर_घोषित __sparc_v9__
		/*
		 * XXX: Reset the device, अगर we करोn't it will not respond to
		 *      dev_select() properly during first ide_probe_port().
		 */
		समयout = 10000;
		outb(12, hwअगर->io_ports.ctl_addr);
		udelay(10);
		outb(8, hwअगर->io_ports.ctl_addr);
		करो अणु
			udelay(50);
			stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);
			अगर (stat == 0xff)
				अवरोध;
		पूर्ण जबतक ((stat & ATA_BUSY) && --समयout);
#पूर्ण_अगर
	पूर्ण

	अगर (!using_पूर्णांकa)
		hwअगर->irq = pci_get_legacy_ide_irq(dev, hwअगर->channel);

	अगर (!hwअगर->dma_base)
		वापस;

	outb(0x60, hwअगर->dma_base + ATA_DMA_STATUS);
पूर्ण

अटल स्थिर काष्ठा ide_tp_ops ns87415_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ns87415_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops ns87415_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ns87415_dma_start,
	.dma_end		= ns87415_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= superio_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info ns87415_chipset = अणु
	.name		= DRV_NAME,
	.init_hwअगर	= init_hwअगर_ns87415,
	.tp_ops 	= &ns87415_tp_ops,
	.dma_ops	= &ns87415_dma_ops,
	.host_flags	= IDE_HFLAG_TRUST_BIOS_FOR_DMA |
			  IDE_HFLAG_NO_ATAPI_DMA,
पूर्ण;

अटल पूर्णांक ns87415_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d = ns87415_chipset;

#अगर_घोषित CONFIG_SUPERIO
	अगर (PCI_SLOT(dev->devfn) == 0xE) अणु
		/* Built-in - assume it's under superio. */
		d.init_iops = superio_init_iops;
		d.tp_ops = &superio_tp_ops;
	पूर्ण
#पूर्ण_अगर
	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ns87415_pci_tbl[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_87415), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, ns87415_pci_tbl);

अटल काष्ठा pci_driver ns87415_pci_driver = अणु
	.name		= "NS87415_IDE",
	.id_table	= ns87415_pci_tbl,
	.probe		= ns87415_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init ns87415_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&ns87415_pci_driver);
पूर्ण

अटल व्योम __निकास ns87415_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ns87415_pci_driver);
पूर्ण

module_init(ns87415_ide_init);
module_निकास(ns87415_ide_निकास);

MODULE_AUTHOR("Mark Lord, Eddie Dost, Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for NS87415 IDE");
MODULE_LICENSE("GPL");
