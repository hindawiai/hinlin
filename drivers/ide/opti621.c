<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1996-1998  Linus Torvalds & authors (see below)
 */

/*
 * Authors:
 * Jaromir Koutek <miri@punknet.cz>,
 * Jan Harkes <jaharkes@cwi.nl>,
 * Mark Lord <mlord@pobox.com>
 * Some parts of code are from ali14xx.c and from rz1000.c.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "opti621"

#घोषणा READ_REG 0	/* index of Read cycle timing रेजिस्टर */
#घोषणा WRITE_REG 1	/* index of Write cycle timing रेजिस्टर */
#घोषणा CNTRL_REG 3	/* index of Control रेजिस्टर */
#घोषणा STRAP_REG 5	/* index of Strap रेजिस्टर */
#घोषणा MISC_REG 6	/* index of Miscellaneous रेजिस्टर */

अटल पूर्णांक reg_base;

अटल DEFINE_SPINLOCK(opti621_lock);

/* Write value to रेजिस्टर reg, base of रेजिस्टर
 * is at reg_base (0x1f0 primary, 0x170 secondary,
 * अगर not changed by PCI configuration).
 * This is from setupvic.exe program.
 */
अटल व्योम ग_लिखो_reg(u8 value, पूर्णांक reg)
अणु
	inw(reg_base + 1);
	inw(reg_base + 1);
	outb(3, reg_base + 2);
	outb(value, reg_base + reg);
	outb(0x83, reg_base + 2);
पूर्ण

/* Read value from रेजिस्टर reg, base of रेजिस्टर
 * is at reg_base (0x1f0 primary, 0x170 secondary,
 * अगर not changed by PCI configuration).
 * This is from setupvic.exe program.
 */
अटल u8 पढ़ो_reg(पूर्णांक reg)
अणु
	u8 ret = 0;

	inw(reg_base + 1);
	inw(reg_base + 1);
	outb(3, reg_base + 2);
	ret = inb(reg_base + reg);
	outb(0x83, reg_base + 2);

	वापस ret;
पूर्ण

अटल व्योम opti621_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	ide_drive_t *pair = ide_get_pair_dev(drive);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mode = drive->pio_mode, pair_mode;
	स्थिर u8 pio = mode - XFER_PIO_0;
	u8 tim, misc, addr_pio = pio, clk;

	/* DRDY is शेष 2 (by OPTi Databook) */
	अटल स्थिर u8 addr_timings[2][5] = अणु
		अणु 0x20, 0x10, 0x00, 0x00, 0x00 पूर्ण,	/* 33 MHz */
		अणु 0x10, 0x10, 0x00, 0x00, 0x00 पूर्ण,	/* 25 MHz */
	पूर्ण;
	अटल स्थिर u8 data_rec_timings[2][5] = अणु
		अणु 0x5b, 0x45, 0x32, 0x21, 0x20 पूर्ण,	/* 33 MHz */
		अणु 0x48, 0x34, 0x21, 0x10, 0x10 पूर्ण	/* 25 MHz */
	पूर्ण;

	ide_set_drivedata(drive, (व्योम *)mode);

	अगर (pair) अणु
		pair_mode = (अचिन्हित दीर्घ)ide_get_drivedata(pair);
		अगर (pair_mode && pair_mode < mode)
			addr_pio = pair_mode - XFER_PIO_0;
	पूर्ण

	spin_lock_irqsave(&opti621_lock, flags);

	reg_base = hwअगर->io_ports.data_addr;

	/* allow Register-B */
	outb(0xc0, reg_base + CNTRL_REG);
	/* hmm, setupvic.exe करोes this ;-) */
	outb(0xff, reg_base + 5);
	/* अगर पढ़ोs 0xff, adapter not exist? */
	(व्योम)inb(reg_base + CNTRL_REG);
	/* अगर पढ़ोs 0xc0, no पूर्णांकerface exist? */
	पढ़ो_reg(CNTRL_REG);

	/* check CLK speed */
	clk = पढ़ो_reg(STRAP_REG) & 1;

	prपूर्णांकk(KERN_INFO "%s: CLK = %d MHz\n", hwअगर->name, clk ? 25 : 33);

	tim  = data_rec_timings[clk][pio];
	misc = addr_timings[clk][addr_pio];

	/* select Index-0/1 क्रम Register-A/B */
	ग_लिखो_reg(drive->dn & 1, MISC_REG);
	/* set पढ़ो cycle timings */
	ग_लिखो_reg(tim, READ_REG);
	/* set ग_लिखो cycle timings */
	ग_लिखो_reg(tim, WRITE_REG);

	/* use Register-A क्रम drive 0 */
	/* use Register-B क्रम drive 1 */
	ग_लिखो_reg(0x85, CNTRL_REG);

	/* set address setup, DRDY timings,   */
	/*  and पढ़ो prefetch क्रम both drives */
	ग_लिखो_reg(misc, MISC_REG);

	spin_unlock_irqrestore(&opti621_lock, flags);
पूर्ण

अटल स्थिर काष्ठा ide_port_ops opti621_port_ops = अणु
	.set_pio_mode		= opti621_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info opti621_chipset = अणु
	.name		= DRV_NAME,
	.enablebits	= अणु अणु0x45, 0x80, 0x00पूर्ण, अणु0x40, 0x08, 0x00पूर्ण पूर्ण,
	.port_ops	= &opti621_port_ops,
	.host_flags	= IDE_HFLAG_NO_DMA,
	.pio_mask	= ATA_PIO4,
पूर्ण;

अटल पूर्णांक opti621_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &opti621_chipset, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id opti621_pci_tbl[] = अणु
	अणु PCI_VDEVICE(OPTI, PCI_DEVICE_ID_OPTI_82C621), 0 पूर्ण,
	अणु PCI_VDEVICE(OPTI, PCI_DEVICE_ID_OPTI_82C825), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, opti621_pci_tbl);

अटल काष्ठा pci_driver opti621_pci_driver = अणु
	.name		= "Opti621_IDE",
	.id_table	= opti621_pci_tbl,
	.probe		= opti621_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init opti621_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&opti621_pci_driver);
पूर्ण

अटल व्योम __निकास opti621_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&opti621_pci_driver);
पूर्ण

module_init(opti621_ide_init);
module_निकास(opti621_ide_निकास);

MODULE_AUTHOR("Jaromir Koutek, Jan Harkes, Mark Lord");
MODULE_DESCRIPTION("PCI driver module for Opti621 IDE");
MODULE_LICENSE("GPL");
