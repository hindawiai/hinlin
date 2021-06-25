<शैली गुरु>
/*
 *  Copyright (c) 1997-1998  Mark Lord
 *  Copyright (c) 2007       MontaVista Software, Inc. <source@mvista.com>
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 *  June 22, 2004 - get rid of check_region
 *                   - Jesper Juhl
 *
 */

/*
 * This module provides support क्रम the bus-master IDE DMA function
 * of the Tekram TRM290 chip, used on a variety of PCI IDE add-on boards,
 * including a "Precision Instruments" board.  The TRM290 pre-dates
 * the sff-8038 standard (ide-dma.c) by a few months, and dअगरfers
 * signअगरicantly enough to warrant separate routines क्रम some functions,
 * जबतक re-using others from ide-dma.c.
 *
 * EXPERIMENTAL!  It works क्रम me (a sample of one).
 *
 * Works reliably क्रम me in DMA mode (READs only),
 * DMA WRITEs are disabled by शेष (see #घोषणा below);
 *
 * DMA is not enabled स्वतःmatically क्रम this chipset,
 * but can be turned on manually (with "hdparm -d1") at run समय.
 *
 * I need volunteers with "spare" drives क्रम further testing
 * and development, and maybe to help figure out the peculiarities.
 * Even knowing the रेजिस्टरs (below), some things behave strangely.
 */

#घोषणा TRM290_NO_DMA_WRITES	/* DMA ग_लिखोs seem unreliable someबार */

/*
 * TRM-290 PCI-IDE2 Bus Master Chip
 * ================================
 * The configuration रेजिस्टरs are addressed in normal I/O port space
 * and are used as follows:
 *
 * trm290_base depends on jumper settings, and is probed क्रम by ide-dma.c
 *
 * trm290_base+2 when WRITTEN: chiptest रेजिस्टर (byte, ग_लिखो-only)
 *	bit7 must always be written as "1"
 *	bits6-2 undefined
 *	bit1 1=legacy_compatible_mode, 0=native_pci_mode
 *	bit0 1=test_mode, 0=normal(शेष)
 *
 * trm290_base+2 when READ: status रेजिस्टर (byte, पढ़ो-only)
 *	bits7-2 undefined
 *	bit1 channel0 busmaster पूर्णांकerrupt status 0=none, 1=निश्चितed
 *	bit0 channel0 पूर्णांकerrupt status 0=none, 1=निश्चितed
 *
 * trm290_base+3 Interrupt mask रेजिस्टर
 *	bits7-5 undefined
 *	bit4 legacy_header: 1=present, 0=असलent
 *	bit3 channel1 busmaster पूर्णांकerrupt status 0=none, 1=निश्चितed (पढ़ो only)
 *	bit2 channel1 पूर्णांकerrupt status 0=none, 1=निश्चितed (पढ़ो only)
 *	bit1 channel1 पूर्णांकerrupt mask: 1=masked, 0=unmasked(शेष)
 *	bit0 channel0 पूर्णांकerrupt mask: 1=masked, 0=unmasked(शेष)
 *
 * trm290_base+1 "CPR" Config Poपूर्णांकer Register (byte)
 *	bit7 1=स्वतःincrement CPR bits 2-0 after each access of CDR
 *	bit6 1=min. 1 रुको-state posted ग_लिखो cycle (शेष), 0=0 रुको-state
 *	bit5 0=enabled master burst access (शेष), 1=disable  (ग_लिखो only)
 *	bit4 PCI DEVSEL# timing select: 1=medium(शेष), 0=fast
 *	bit3 0=primary IDE channel, 1=secondary IDE channel
 *	bits2-0 रेजिस्टर index क्रम accesses through CDR port
 *
 * trm290_base+0 "CDR" Config Data Register (word)
 *	two sets of seven config रेजिस्टरs,
 *	selected by CPR bit 3 (channel) and CPR bits 2-0 (index 0 to 6),
 *	each index defined below:
 *
 * Index-0 Base address रेजिस्टर क्रम command block (word)
 *	शेषs: 0x1f0 क्रम primary, 0x170 क्रम secondary
 *
 * Index-1 general config रेजिस्टर (byte)
 *	bit7 1=DMA enable, 0=DMA disable
 *	bit6 1=activate IDE_RESET, 0=no action (शेष)
 *	bit5 1=enable IORDY, 0=disable IORDY (शेष)
 *	bit4 0=16-bit data port(शेष), 1=8-bit (XT) data port
 *	bit3 पूर्णांकerrupt polarity: 1=active_low, 0=active_high(शेष)
 *	bit2 घातer-saving-mode(?): 1=enable, 0=disable(शेष) (ग_लिखो only)
 *	bit1 bus_master_mode(?): 1=enable, 0=disable(शेष)
 *	bit0 enable_io_ports: 1=enable(शेष), 0=disable
 *
 * Index-2 पढ़ो-ahead counter preload bits 0-7 (byte, ग_लिखो only)
 *	bits7-0 bits7-0 of पढ़ोahead count
 *
 * Index-3 पढ़ो-ahead config रेजिस्टर (byte, ग_लिखो only)
 *	bit7 1=enable_पढ़ोahead, 0=disable_पढ़ोahead(शेष)
 *	bit6 1=clear_FIFO, 0=no_action
 *	bit5 undefined
 *	bit4 mode4 timing control: 1=enable, 0=disable(शेष)
 *	bit3 undefined
 *	bit2 undefined
 *	bits1-0 bits9-8 of पढ़ो-ahead count
 *
 * Index-4 base address रेजिस्टर क्रम control block (word)
 *	शेषs: 0x3f6 क्रम primary, 0x376 क्रम secondary
 *
 * Index-5 data port timings (shared by both drives) (byte)
 *	standard PCI "clk" (घड़ी) counts, शेष value = 0xf5
 *
 *	bits7-6 setup समय:  00=1clk, 01=2clk, 10=3clk, 11=4clk
 *	bits5-3 hold समय:	000=1clk, 001=2clk, 010=3clk,
 *				011=4clk, 100=5clk, 101=6clk,
 *				110=8clk, 111=12clk
 *	bits2-0 active समय:	000=2clk, 001=3clk, 010=4clk,
 *				011=5clk, 100=6clk, 101=8clk,
 *				110=12clk, 111=16clk
 *
 * Index-6 command/control port timings (shared by both drives) (byte)
 *	same layout as Index-5, शेष value = 0xde
 *
 * Suggested CDR programming क्रम PIO mode0 (600ns):
 *	0x01f0,0x21,0xff,0x80,0x03f6,0xf5,0xde	; primary
 *	0x0170,0x21,0xff,0x80,0x0376,0xf5,0xde	; secondary
 *
 * Suggested CDR programming क्रम PIO mode3 (180ns):
 *	0x01f0,0x21,0xff,0x80,0x03f6,0x09,0xde	; primary
 *	0x0170,0x21,0xff,0x80,0x0376,0x09,0xde	; secondary
 *
 * Suggested CDR programming क्रम PIO mode4 (120ns):
 *	0x01f0,0x21,0xff,0x80,0x03f6,0x00,0xde	; primary
 *	0x0170,0x21,0xff,0x80,0x0376,0x00,0xde	; secondary
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "trm290"

अटल व्योम trm290_prepare_drive (ide_drive_t *drive, अचिन्हित पूर्णांक use_dma)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u16 reg = 0;
	अचिन्हित दीर्घ flags;

	/* select PIO or DMA */
	reg = use_dma ? (0x21 | 0x82) : (0x21 & ~0x82);

	local_irq_save(flags);

	अगर (reg != hwअगर->select_data) अणु
		hwअगर->select_data = reg;
		/* set PIO/DMA */
		outb(0x51 | (hwअगर->channel << 3), hwअगर->config_data + 1);
		outw(reg & 0xff, hwअगर->config_data);
	पूर्ण

	/* enable IRQ अगर not probing */
	अगर (drive->dev_flags & IDE_DFLAG_PRESENT) अणु
		reg = inw(hwअगर->config_data + 3);
		reg &= 0x13;
		reg &= ~(1 << hwअगर->channel);
		outw(reg, hwअगर->config_data + 3);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम trm290_dev_select(ide_drive_t *drive)
अणु
	trm290_prepare_drive(drive, !!(drive->dev_flags & IDE_DFLAG_USING_DMA));

	outb(drive->select | ATA_DEVICE_OBS, drive->hwअगर->io_ports.device_addr);
पूर्ण

अटल पूर्णांक trm290_dma_check(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	अगर (cmd->tf_flags & IDE_TFLAG_WRITE) अणु
#अगर_घोषित TRM290_NO_DMA_WRITES
		/* always use PIO क्रम ग_लिखोs */
		वापस 1;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक trm290_dma_setup(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित पूर्णांक count, rw = (cmd->tf_flags & IDE_TFLAG_WRITE) ? 1 : 2;

	count = ide_build_dmatable(drive, cmd);
	अगर (count == 0)
		/* try PIO instead of DMA */
		वापस 1;

	outl(hwअगर->dmatable_dma | rw, hwअगर->dma_base);
	/* start DMA */
	outw(count * 2 - 1, hwअगर->dma_base + 2);

	वापस 0;
पूर्ण

अटल व्योम trm290_dma_start(ide_drive_t *drive)
अणु
	trm290_prepare_drive(drive, 1);
पूर्ण

अटल पूर्णांक trm290_dma_end(ide_drive_t *drive)
अणु
	u16 status = inw(drive->hwअगर->dma_base + 2);

	trm290_prepare_drive(drive, 0);

	वापस status != 0x00ff;
पूर्ण

अटल पूर्णांक trm290_dma_test_irq(ide_drive_t *drive)
अणु
	u16 status = inw(drive->hwअगर->dma_base + 2);

	वापस status == 0x00ff;
पूर्ण

अटल व्योम trm290_dma_host_set(ide_drive_t *drive, पूर्णांक on)
अणु
पूर्ण

अटल व्योम init_hwअगर_trm290(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित पूर्णांक  cfg_base	= pci_resource_start(dev, 4);
	अचिन्हित दीर्घ flags;
	u8 reg = 0;

	अगर ((dev->class & 5) && cfg_base)
		prपूर्णांकk(KERN_INFO DRV_NAME " %s: chip", pci_name(dev));
	अन्यथा अणु
		cfg_base = 0x3df0;
		prपूर्णांकk(KERN_INFO DRV_NAME " %s: using default", pci_name(dev));
	पूर्ण
	prपूर्णांकk(KERN_CONT " config base at 0x%04x\n", cfg_base);
	hwअगर->config_data = cfg_base;
	hwअगर->dma_base = (cfg_base + 4) ^ (hwअगर->channel ? 0x80 : 0);

	prपूर्णांकk(KERN_INFO "    %s: BM-DMA at 0x%04lx-0x%04lx\n",
	       hwअगर->name, hwअगर->dma_base, hwअगर->dma_base + 3);

	अगर (ide_allocate_dma_engine(hwअगर))
		वापस;

	local_irq_save(flags);
	/* put config reg पूर्णांकo first byte of hwअगर->select_data */
	outb(0x51 | (hwअगर->channel << 3), hwअगर->config_data + 1);
	/* select PIO as शेष */
	hwअगर->select_data = 0x21;
	outb(hwअगर->select_data, hwअगर->config_data);
	/* get IRQ info */
	reg = inb(hwअगर->config_data + 3);
	/* mask IRQs क्रम both ports */
	reg = (reg & 0x10) | 0x03;
	outb(reg, hwअगर->config_data + 3);
	local_irq_restore(flags);

	अगर (reg & 0x10)
		/* legacy mode */
		hwअगर->irq = hwअगर->channel ? 15 : 14;

#अगर 1
	अणु
	/*
	 * My trm290-based card करोesn't seem to work with all possible values
	 * क्रम the control basereg, so this kludge ensures that we use only
	 * values that are known to work.  Ugh.		-ml
	 */
		u16 new, old, compat = hwअगर->channel ? 0x374 : 0x3f4;
		अटल u16 next_offset = 0;
		u8 old_mask;

		outb(0x54 | (hwअगर->channel << 3), hwअगर->config_data + 1);
		old = inw(hwअगर->config_data);
		old &= ~1;
		old_mask = inb(old + 2);
		अगर (old != compat && old_mask == 0xff) अणु
			/* leave lower 10 bits untouched */
			compat += (next_offset += 0x400);
			hwअगर->io_ports.ctl_addr = compat + 2;
			outw(compat | 1, hwअगर->config_data);
			new = inw(hwअगर->config_data);
			prपूर्णांकk(KERN_INFO "%s: control basereg workaround: "
				"old=0x%04x, new=0x%04x\n",
				hwअगर->name, old, new & ~1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा ide_tp_ops trm290_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= trm290_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops trm290_dma_ops = अणु
	.dma_host_set		= trm290_dma_host_set,
	.dma_setup 		= trm290_dma_setup,
	.dma_start 		= trm290_dma_start,
	.dma_end		= trm290_dma_end,
	.dma_test_irq		= trm290_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_check		= trm290_dma_check,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info trm290_chipset = अणु
	.name		= DRV_NAME,
	.init_hwअगर	= init_hwअगर_trm290,
	.tp_ops 	= &trm290_tp_ops,
	.dma_ops	= &trm290_dma_ops,
	.host_flags	= IDE_HFLAG_TRM290 |
			  IDE_HFLAG_NO_ATAPI_DMA |
#अगर 0 /* play it safe क्रम now */
			  IDE_HFLAG_TRUST_BIOS_FOR_DMA |
#पूर्ण_अगर
			  IDE_HFLAG_NO_AUTODMA |
			  IDE_HFLAG_NO_LBA48,
पूर्ण;

अटल पूर्णांक trm290_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &trm290_chipset, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id trm290_pci_tbl[] = अणु
	अणु PCI_VDEVICE(TEKRAM, PCI_DEVICE_ID_TEKRAM_DC290), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, trm290_pci_tbl);

अटल काष्ठा pci_driver trm290_pci_driver = अणु
	.name		= "TRM290_IDE",
	.id_table	= trm290_pci_tbl,
	.probe		= trm290_init_one,
	.हटाओ		= ide_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init trm290_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&trm290_pci_driver);
पूर्ण

अटल व्योम __निकास trm290_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&trm290_pci_driver);
पूर्ण

module_init(trm290_ide_init);
module_निकास(trm290_ide_निकास);

MODULE_AUTHOR("Mark Lord");
MODULE_DESCRIPTION("PCI driver module for Tekram TRM290 IDE");
MODULE_LICENSE("GPL");
