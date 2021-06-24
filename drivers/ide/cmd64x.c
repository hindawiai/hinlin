<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cmd64x.c: Enable पूर्णांकerrupts at initialization समय on Ultra/PCI machines.
 *           Due to massive hardware bugs, UltraDMA is only supported
 *           on the 646U2 and not on the 646U.
 *
 * Copyright (C) 1998		Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 1998		David S. Miller (davem@redhat.com)
 *
 * Copyright (C) 1999-2002	Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2007-2010	Bartlomiej Zolnierkiewicz
 * Copyright (C) 2007,2009	MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "cmd64x"

/*
 * CMD64x specअगरic रेजिस्टरs definition.
 */
#घोषणा CFR		0x50
#घोषणा   CFR_INTR_CH0		0x04

#घोषणा	CMDTIM		0x52
#घोषणा	ARTTIM0		0x53
#घोषणा	DRWTIM0		0x54
#घोषणा ARTTIM1 	0x55
#घोषणा DRWTIM1		0x56
#घोषणा ARTTIM23	0x57
#घोषणा   ARTTIM23_DIS_RA2	0x04
#घोषणा   ARTTIM23_DIS_RA3	0x08
#घोषणा   ARTTIM23_INTR_CH1	0x10
#घोषणा DRWTIM2		0x58
#घोषणा BRST		0x59
#घोषणा DRWTIM3		0x5b

#घोषणा BMIDECR0	0x70
#घोषणा MRDMODE		0x71
#घोषणा   MRDMODE_INTR_CH0	0x04
#घोषणा   MRDMODE_INTR_CH1	0x08
#घोषणा UDIDETCR0	0x73
#घोषणा DTPR0		0x74
#घोषणा BMIDECR1	0x78
#घोषणा BMIDECSR	0x79
#घोषणा UDIDETCR1	0x7B
#घोषणा DTPR1		0x7C

अटल व्योम cmd64x_program_timings(ide_drive_t *drive, u8 mode)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	पूर्णांक bus_speed = ide_pci_clk ? ide_pci_clk : 33;
	स्थिर अचिन्हित दीर्घ T = 1000000 / bus_speed;
	अटल स्थिर u8 recovery_values[] =
		अणु15, 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0पूर्ण;
	अटल स्थिर u8 setup_values[] = अणु0x40, 0x40, 0x40, 0x80, 0, 0xc0पूर्ण;
	अटल स्थिर u8 arttim_regs[4] = अणुARTTIM0, ARTTIM1, ARTTIM23, ARTTIM23पूर्ण;
	अटल स्थिर u8 drwtim_regs[4] = अणुDRWTIM0, DRWTIM1, DRWTIM2, DRWTIM3पूर्ण;
	काष्ठा ide_timing t;
	u8 arttim = 0;

	अगर (drive->dn >= ARRAY_SIZE(drwtim_regs))
		वापस;

	ide_timing_compute(drive, mode, &t, T, 0);

	/*
	 * In हाल we've got too दीर्घ recovery phase, try to lengthen
	 * the active phase
	 */
	अगर (t.recover > 16) अणु
		t.active += t.recover - 16;
		t.recover = 16;
	पूर्ण
	अगर (t.active > 16)		/* shouldn't actually happen... */
		t.active = 16;

	/*
	 * Convert values to पूर्णांकernal chipset representation
	 */
	t.recover = recovery_values[t.recover];
	t.active &= 0x0f;

	/* Program the active/recovery counts पूर्णांकo the DRWTIM रेजिस्टर */
	pci_ग_लिखो_config_byte(dev, drwtim_regs[drive->dn],
			      (t.active << 4) | t.recover);

	/*
	 * The primary channel has inभागidual address setup timing रेजिस्टरs
	 * क्रम each drive and the hardware selects the slowest timing itself.
	 * The secondary channel has one common रेजिस्टर and we have to select
	 * the slowest address setup timing ourselves.
	 */
	अगर (hwअगर->channel) अणु
		ide_drive_t *pair = ide_get_pair_dev(drive);

		अगर (pair) अणु
			काष्ठा ide_timing tp;

			ide_timing_compute(pair, pair->pio_mode, &tp, T, 0);
			ide_timing_merge(&t, &tp, &t, IDE_TIMING_SETUP);
			अगर (pair->dma_mode) अणु
				ide_timing_compute(pair, pair->dma_mode,
						&tp, T, 0);
				ide_timing_merge(&tp, &t, &t, IDE_TIMING_SETUP);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (t.setup > 5)		/* shouldn't actually happen... */
		t.setup = 5;

	/*
	 * Program the address setup घड़ीs पूर्णांकo the ARTTIM रेजिस्टरs.
	 * Aव्योम clearing the secondary channel's पूर्णांकerrupt bit.
	 */
	(व्योम) pci_पढ़ो_config_byte (dev, arttim_regs[drive->dn], &arttim);
	अगर (hwअगर->channel)
		arttim &= ~ARTTIM23_INTR_CH1;
	arttim &= ~0xc0;
	arttim |= setup_values[t.setup];
	(व्योम) pci_ग_लिखो_config_byte(dev, arttim_regs[drive->dn], arttim);
पूर्ण

/*
 * Attempts to set drive's PIO mode.
 * Special हालs are 8: prefetch off, 9: prefetch on (both never worked)
 */

अटल व्योम cmd64x_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	/*
	 * Filter out the prefetch control values
	 * to prevent PIO5 from being programmed
	 */
	अगर (pio == 8 || pio == 9)
		वापस;

	cmd64x_program_timings(drive, XFER_PIO_0 + pio);
पूर्ण

अटल व्योम cmd64x_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 unit			= drive->dn & 0x01;
	u8 regU = 0, pciU	= hwअगर->channel ? UDIDETCR1 : UDIDETCR0;
	स्थिर u8 speed		= drive->dma_mode;

	pci_पढ़ो_config_byte(dev, pciU, &regU);
	regU &= ~(unit ? 0xCA : 0x35);

	चयन(speed) अणु
	हाल XFER_UDMA_5:
		regU |= unit ? 0x0A : 0x05;
		अवरोध;
	हाल XFER_UDMA_4:
		regU |= unit ? 0x4A : 0x15;
		अवरोध;
	हाल XFER_UDMA_3:
		regU |= unit ? 0x8A : 0x25;
		अवरोध;
	हाल XFER_UDMA_2:
		regU |= unit ? 0x42 : 0x11;
		अवरोध;
	हाल XFER_UDMA_1:
		regU |= unit ? 0x82 : 0x21;
		अवरोध;
	हाल XFER_UDMA_0:
		regU |= unit ? 0xC2 : 0x31;
		अवरोध;
	हाल XFER_MW_DMA_2:
	हाल XFER_MW_DMA_1:
	हाल XFER_MW_DMA_0:
		cmd64x_program_timings(drive, speed);
		अवरोध;
	पूर्ण

	pci_ग_लिखो_config_byte(dev, pciU, regU);
पूर्ण

अटल व्योम cmd648_clear_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ base	= pci_resource_start(dev, 4);
	u8  irq_mask		= hwअगर->channel ? MRDMODE_INTR_CH1 :
						  MRDMODE_INTR_CH0;
	u8  mrdmode		= inb(base + 1);

	/* clear the पूर्णांकerrupt bit */
	outb((mrdmode & ~(MRDMODE_INTR_CH0 | MRDMODE_INTR_CH1)) | irq_mask,
	     base + 1);
पूर्ण

अटल व्योम cmd64x_clear_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	पूर्णांक irq_reg		= hwअगर->channel ? ARTTIM23 : CFR;
	u8  irq_mask		= hwअगर->channel ? ARTTIM23_INTR_CH1 :
						  CFR_INTR_CH0;
	u8  irq_stat		= 0;

	(व्योम) pci_पढ़ो_config_byte(dev, irq_reg, &irq_stat);
	/* clear the पूर्णांकerrupt bit */
	(व्योम) pci_ग_लिखो_config_byte(dev, irq_reg, irq_stat | irq_mask);
पूर्ण

अटल पूर्णांक cmd648_test_irq(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ base	= pci_resource_start(dev, 4);
	u8 irq_mask		= hwअगर->channel ? MRDMODE_INTR_CH1 :
						  MRDMODE_INTR_CH0;
	u8 mrdmode		= inb(base + 1);

	pr_debug("%s: mrdmode: 0x%02x irq_mask: 0x%02x\n",
		 hwअगर->name, mrdmode, irq_mask);

	वापस (mrdmode & irq_mask) ? 1 : 0;
पूर्ण

अटल पूर्णांक cmd64x_test_irq(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	पूर्णांक irq_reg		= hwअगर->channel ? ARTTIM23 : CFR;
	u8  irq_mask		= hwअगर->channel ? ARTTIM23_INTR_CH1 :
						  CFR_INTR_CH0;
	u8  irq_stat		= 0;

	(व्योम) pci_पढ़ो_config_byte(dev, irq_reg, &irq_stat);

	pr_debug("%s: irq_stat: 0x%02x irq_mask: 0x%02x\n",
		 hwअगर->name, irq_stat, irq_mask);

	वापस (irq_stat & irq_mask) ? 1 : 0;
पूर्ण

/*
 * ASUS P55T2P4D with CMD646 chipset revision 0x01 requires the old
 * event order क्रम DMA transfers.
 */

अटल पूर्णांक cmd646_1_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_stat = 0, dma_cmd = 0;

	/* get DMA status */
	dma_stat = inb(hwअगर->dma_base + ATA_DMA_STATUS);
	/* पढ़ो DMA command state */
	dma_cmd = inb(hwअगर->dma_base + ATA_DMA_CMD);
	/* stop DMA */
	outb(dma_cmd & ~1, hwअगर->dma_base + ATA_DMA_CMD);
	/* clear the INTR & ERROR bits */
	outb(dma_stat | 6, hwअगर->dma_base + ATA_DMA_STATUS);
	/* verअगरy good DMA status */
	वापस (dma_stat & 7) != 4;
पूर्ण

अटल पूर्णांक init_chipset_cmd64x(काष्ठा pci_dev *dev)
अणु
	u8 mrdmode = 0;

	/* Set a good latency समयr and cache line size value. */
	(व्योम) pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 64);
	/* FIXME: pci_set_master() to ensure a good latency समयr value */

	/*
	 * Enable पूर्णांकerrupts, select MEMORY READ LINE क्रम पढ़ोs.
	 *
	 * NOTE: although not mentioned in the PCI0646U specs,
	 * bits 0-1 are ग_लिखो only and won't be पढ़ो back as
	 * set or not -- PCI0646U2 specs clarअगरy this poपूर्णांक.
	 */
	(व्योम) pci_पढ़ो_config_byte (dev, MRDMODE, &mrdmode);
	mrdmode &= ~0x30;
	(व्योम) pci_ग_लिखो_config_byte(dev, MRDMODE, (mrdmode | 0x02));

	वापस 0;
पूर्ण

अटल u8 cmd64x_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev  *dev	= to_pci_dev(hwअगर->dev);
	u8 bmidecsr = 0, mask	= hwअगर->channel ? 0x02 : 0x01;

	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_CMD_648:
	हाल PCI_DEVICE_ID_CMD_649:
 		pci_पढ़ो_config_byte(dev, BMIDECSR, &bmidecsr);
		वापस (bmidecsr & mask) ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
	शेष:
		वापस ATA_CBL_PATA40;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ide_port_ops cmd64x_port_ops = अणु
	.set_pio_mode		= cmd64x_set_pio_mode,
	.set_dma_mode		= cmd64x_set_dma_mode,
	.clear_irq		= cmd64x_clear_irq,
	.test_irq		= cmd64x_test_irq,
	.cable_detect		= cmd64x_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops cmd648_port_ops = अणु
	.set_pio_mode		= cmd64x_set_pio_mode,
	.set_dma_mode		= cmd64x_set_dma_mode,
	.clear_irq		= cmd648_clear_irq,
	.test_irq		= cmd648_test_irq,
	.cable_detect		= cmd64x_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops cmd646_rev1_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= cmd646_1_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info cmd64x_chipsets[] = अणु
	अणु	/* 0: CMD643 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_cmd64x,
		.enablebits	= अणुअणु0x00,0x00,0x00पूर्ण, अणु0x51,0x08,0x08पूर्णपूर्ण,
		.port_ops	= &cmd64x_port_ops,
		.host_flags	= IDE_HFLAG_CLEAR_SIMPLEX |
				  IDE_HFLAG_ABUSE_PREFETCH |
				  IDE_HFLAG_SERIALIZE,
		.pio_mask	= ATA_PIO5,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= 0x00, /* no udma */
	पूर्ण,
	अणु	/* 1: CMD646 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_cmd64x,
		.enablebits	= अणुअणु0x51,0x04,0x04पूर्ण, अणु0x51,0x08,0x08पूर्णपूर्ण,
		.port_ops	= &cmd648_port_ops,
		.host_flags	= IDE_HFLAG_ABUSE_PREFETCH |
				  IDE_HFLAG_SERIALIZE,
		.pio_mask	= ATA_PIO5,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA2,
	पूर्ण,
	अणु	/* 2: CMD648 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_cmd64x,
		.enablebits	= अणुअणु0x51,0x04,0x04पूर्ण, अणु0x51,0x08,0x08पूर्णपूर्ण,
		.port_ops	= &cmd648_port_ops,
		.host_flags	= IDE_HFLAG_ABUSE_PREFETCH,
		.pio_mask	= ATA_PIO5,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA4,
	पूर्ण,
	अणु	/* 3: CMD649 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_cmd64x,
		.enablebits	= अणुअणु0x51,0x04,0x04पूर्ण, अणु0x51,0x08,0x08पूर्णपूर्ण,
		.port_ops	= &cmd648_port_ops,
		.host_flags	= IDE_HFLAG_ABUSE_PREFETCH,
		.pio_mask	= ATA_PIO5,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण
पूर्ण;

अटल पूर्णांक cmd64x_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d;
	u8 idx = id->driver_data;

	d = cmd64x_chipsets[idx];

	अगर (idx == 1) अणु
		/*
		 * UltraDMA only supported on PCI646U and PCI646U2, which
		 * correspond to revisions 0x03, 0x05 and 0x07 respectively.
		 * Actually, although the CMD tech support people won't
		 * tell me the details, the 0x03 revision cannot support
		 * UDMA correctly without hardware modअगरications, and even
		 * then it only works with Quantum disks due to some
		 * hold समय assumptions in the 646U part which are fixed
		 * in the 646U2.
		 *
		 * So we only करो UltraDMA on revision 0x05 and 0x07 chipsets.
		 */
		अगर (dev->revision < 5) अणु
			d.udma_mask = 0x00;
			/*
			 * The original PCI0646 didn't have the primary
			 * channel enable bit, it appeared starting with
			 * PCI0646U (i.e. revision ID 3).
			 */
			अगर (dev->revision < 3) अणु
				d.enablebits[0].reg = 0;
				d.port_ops = &cmd64x_port_ops;
				अगर (dev->revision == 1)
					d.dma_ops = &cmd646_rev1_dma_ops;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cmd64x_pci_tbl[] = अणु
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_643), 0 पूर्ण,
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_646), 1 पूर्ण,
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_648), 2 पूर्ण,
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_649), 3 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, cmd64x_pci_tbl);

अटल काष्ठा pci_driver cmd64x_pci_driver = अणु
	.name		= "CMD64x_IDE",
	.id_table	= cmd64x_pci_tbl,
	.probe		= cmd64x_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init cmd64x_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&cmd64x_pci_driver);
पूर्ण

अटल व्योम __निकास cmd64x_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cmd64x_pci_driver);
पूर्ण

module_init(cmd64x_ide_init);
module_निकास(cmd64x_ide_निकास);

MODULE_AUTHOR("Eddie Dost, David Miller, Andre Hedrick, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("PCI driver module for CMD64x IDE");
MODULE_LICENSE("GPL");
