<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SL82C105/Winbond 553 IDE driver
 *
 * Maपूर्णांकainer unknown.
 *
 * Drive tuning added from Rebel.com's kernel sources
 *  -- Russell King (15/11/98) linux@arm.linux.org.uk
 * 
 * Merge in Russell's HW workarounds, fix various problems
 * with the timing रेजिस्टरs setup.
 *  -- Benjamin Herrenschmidt (01/11/03) benh@kernel.crashing.org
 *
 * Copyright (C) 2006-2007,2009 MontaVista Software, Inc. <source@mvista.com>
 * Copyright (C)      2007 Bartlomiej Zolnierkiewicz
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "sl82c105"

/*
 * SL82C105 PCI config रेजिस्टर 0x40 bits.
 */
#घोषणा CTRL_IDE_IRQB   (1 << 30)
#घोषणा CTRL_IDE_IRQA   (1 << 28)
#घोषणा CTRL_LEGIRQ     (1 << 11)
#घोषणा CTRL_P1F16      (1 << 5)
#घोषणा CTRL_P1EN       (1 << 4)
#घोषणा CTRL_P0F16      (1 << 1)
#घोषणा CTRL_P0EN       (1 << 0)

/*
 * Convert a PIO mode and cycle समय to the required on/off बार
 * क्रम the पूर्णांकerface.  This has protection against runaway timings.
 */
अटल अचिन्हित पूर्णांक get_pio_timings(ide_drive_t *drive, u8 pio)
अणु
	काष्ठा ide_timing *t = ide_timing_find_mode(XFER_PIO_0 + pio);
	अचिन्हित पूर्णांक cmd_on, cmd_off;
	u8 iordy = 0;

	cmd_on  = (t->active + 29) / 30;
	cmd_off = (ide_pio_cycle_समय(drive, pio) - 30 * cmd_on + 29) / 30;

	अगर (cmd_on == 0)
		cmd_on = 1;

	अगर (cmd_off == 0)
		cmd_off = 1;

	अगर (ide_pio_need_iordy(drive, pio))
		iordy = 0x40;

	वापस (cmd_on - 1) << 8 | (cmd_off - 1) | iordy;
पूर्ण

/*
 * Configure the chipset क्रम PIO mode.
 */
अटल व्योम sl82c105_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ timings	= (अचिन्हित दीर्घ)ide_get_drivedata(drive);
	पूर्णांक reg			= 0x44 + drive->dn * 4;
	u16 drv_ctrl;
	स्थिर u8 pio		= drive->pio_mode - XFER_PIO_0;

	drv_ctrl = get_pio_timings(drive, pio);

	/*
	 * Store the PIO timings so that we can restore them
	 * in हाल DMA will be turned off...
	 */
	timings &= 0xffff0000;
	timings |= drv_ctrl;
	ide_set_drivedata(drive, (व्योम *)timings);

	pci_ग_लिखो_config_word(dev, reg,  drv_ctrl);
	pci_पढ़ो_config_word (dev, reg, &drv_ctrl);

	prपूर्णांकk(KERN_DEBUG "%s: selected %s (%dns) (%04X)\n", drive->name,
			  ide_xfer_verbose(pio + XFER_PIO_0),
			  ide_pio_cycle_समय(drive, pio), drv_ctrl);
पूर्ण

/*
 * Configure the chipset क्रम DMA mode.
 */
अटल व्योम sl82c105_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अटल u16 mwdma_timings[] = अणु0x0707, 0x0201, 0x0200पूर्ण;
	अचिन्हित दीर्घ timings = (अचिन्हित दीर्घ)ide_get_drivedata(drive);
	u16 drv_ctrl;
	स्थिर u8 speed = drive->dma_mode;

	drv_ctrl = mwdma_timings[speed - XFER_MW_DMA_0];

	/*
	 * Store the DMA timings so that we can actually program
	 * them when DMA will be turned on...
	 */
	timings &= 0x0000ffff;
	timings |= (अचिन्हित दीर्घ)drv_ctrl << 16;
	ide_set_drivedata(drive, (व्योम *)timings);
पूर्ण

अटल पूर्णांक sl82c105_test_irq(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u32 val, mask		= hwअगर->channel ? CTRL_IDE_IRQB : CTRL_IDE_IRQA;

	pci_पढ़ो_config_dword(dev, 0x40, &val);

	वापस (val & mask) ? 1 : 0;
पूर्ण

/*
 * The SL82C105 holds off all IDE पूर्णांकerrupts जबतक in DMA mode until
 * all DMA activity is completed.  Someबार this causes problems (eg,
 * when the drive wants to report an error condition).
 *
 * 0x7e is a "chip testing" रेजिस्टर.  Bit 2 resets the DMA controller
 * state machine.  We need to kick this to work around various bugs.
 */
अटल अंतरभूत व्योम sl82c105_reset_host(काष्ठा pci_dev *dev)
अणु
	u16 val;

	pci_पढ़ो_config_word(dev, 0x7e, &val);
	pci_ग_लिखो_config_word(dev, 0x7e, val | (1 << 2));
	pci_ग_लिखो_config_word(dev, 0x7e, val & ~(1 << 2));
पूर्ण

/*
 * If we get an IRQ समयout, it might be that the DMA state machine
 * got confused.  Fix from Todd Inglett.  Details from Winbond.
 *
 * This function is called when the IDE समयr expires, the drive
 * indicates that it is READY, and we were रुकोing क्रम DMA to complete.
 */
अटल व्योम sl82c105_dma_lost_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u32 val, mask		= hwअगर->channel ? CTRL_IDE_IRQB : CTRL_IDE_IRQA;
	u8 dma_cmd;

	prपूर्णांकk(KERN_WARNING "sl82c105: lost IRQ, resetting host\n");

	/*
	 * Check the raw पूर्णांकerrupt from the drive.
	 */
	pci_पढ़ो_config_dword(dev, 0x40, &val);
	अगर (val & mask)
		prपूर्णांकk(KERN_INFO "sl82c105: drive was requesting IRQ, "
		       "but host lost it\n");

	/*
	 * Was DMA enabled?  If so, disable it - we're resetting the
	 * host.  The IDE layer will be handling the drive क्रम us.
	 */
	dma_cmd = inb(hwअगर->dma_base + ATA_DMA_CMD);
	अगर (dma_cmd & 1) अणु
		outb(dma_cmd & ~1, hwअगर->dma_base + ATA_DMA_CMD);
		prपूर्णांकk(KERN_INFO "sl82c105: DMA was enabled\n");
	पूर्ण

	sl82c105_reset_host(dev);
पूर्ण

/*
 * ATAPI devices can cause the SL82C105 DMA state machine to go gaga.
 * Winbond recommend that the DMA state machine is reset prior to
 * setting the bus master DMA enable bit.
 *
 * The generic IDE core will have disabled the BMEN bit beक्रमe this
 * function is called.
 */
अटल व्योम sl82c105_dma_start(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	पूर्णांक reg 		= 0x44 + drive->dn * 4;

	pci_ग_लिखो_config_word(dev, reg,
			      (अचिन्हित दीर्घ)ide_get_drivedata(drive) >> 16);

	sl82c105_reset_host(dev);
	ide_dma_start(drive);
पूर्ण

अटल व्योम sl82c105_dma_clear(ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);

	sl82c105_reset_host(dev);
पूर्ण

अटल पूर्णांक sl82c105_dma_end(ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(drive->hwअगर->dev);
	पूर्णांक reg 		= 0x44 + drive->dn * 4;
	पूर्णांक ret			= ide_dma_end(drive);

	pci_ग_लिखो_config_word(dev, reg,
			      (अचिन्हित दीर्घ)ide_get_drivedata(drive));

	वापस ret;
पूर्ण

/*
 * ATA reset will clear the 16 bits mode in the control
 * रेजिस्टर, we need to reprogram it
 */
अटल व्योम sl82c105_resetproc(ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u32 val;

	pci_पढ़ो_config_dword(dev, 0x40, &val);
	val |= (CTRL_P1F16 | CTRL_P0F16);
	pci_ग_लिखो_config_dword(dev, 0x40, val);
पूर्ण

/*
 * Return the revision of the Winbond bridge
 * which this function is part of.
 */
अटल u8 sl82c105_bridge_revision(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *bridge;

	/*
	 * The bridge should be part of the same device, but function 0.
	 */
	bridge = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(dev->bus),
					dev->bus->number,
					PCI_DEVFN(PCI_SLOT(dev->devfn), 0));
	अगर (!bridge)
		वापस -1;

	/*
	 * Make sure it is a Winbond 553 and is an ISA bridge.
	 */
	अगर (bridge->venकरोr != PCI_VENDOR_ID_WINBOND ||
	    bridge->device != PCI_DEVICE_ID_WINBOND_83C553 ||
	    bridge->class >> 8 != PCI_CLASS_BRIDGE_ISA) अणु
	    	pci_dev_put(bridge);
		वापस -1;
	पूर्ण
	/*
	 * We need to find function 0's revision, not function 1
	 */
	pci_dev_put(bridge);

	वापस bridge->revision;
पूर्ण

/*
 * Enable the PCI device
 * 
 * --BenH: It's arch fixup code that should enable channels that
 * have not been enabled by firmware. I decided we can still enable
 * channel 0 here at least, but channel 1 has to be enabled by
 * firmware or arch code. We still set both to 16 bits mode.
 */
अटल पूर्णांक init_chipset_sl82c105(काष्ठा pci_dev *dev)
अणु
	u32 val;

	pci_पढ़ो_config_dword(dev, 0x40, &val);
	val |= CTRL_P0EN | CTRL_P0F16 | CTRL_P1F16;
	pci_ग_लिखो_config_dword(dev, 0x40, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops sl82c105_port_ops = अणु
	.set_pio_mode		= sl82c105_set_pio_mode,
	.set_dma_mode		= sl82c105_set_dma_mode,
	.resetproc		= sl82c105_resetproc,
	.test_irq		= sl82c105_test_irq,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops sl82c105_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= sl82c105_dma_start,
	.dma_end		= sl82c105_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= sl82c105_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_clear		= sl82c105_dma_clear,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info sl82c105_chipset = अणु
	.name		= DRV_NAME,
	.init_chipset	= init_chipset_sl82c105,
	.enablebits	= अणुअणु0x40,0x01,0x01पूर्ण, अणु0x40,0x10,0x10पूर्णपूर्ण,
	.port_ops	= &sl82c105_port_ops,
	.dma_ops	= &sl82c105_dma_ops,
	.host_flags	= IDE_HFLAG_IO_32BIT |
			  IDE_HFLAG_UNMASK_IRQS |
			  IDE_HFLAG_SERIALIZE_DMA |
			  IDE_HFLAG_NO_AUTODMA,
	.pio_mask	= ATA_PIO5,
	.mwdma_mask	= ATA_MWDMA2,
पूर्ण;

अटल पूर्णांक sl82c105_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d = sl82c105_chipset;
	u8 rev = sl82c105_bridge_revision(dev);

	अगर (rev <= 5) अणु
		/*
		 * Never ever EVER under any circumstances enable
		 * DMA when the bridge is this old.
		 */
		prपूर्णांकk(KERN_INFO DRV_NAME ": Winbond W83C553 bridge "
				 "revision %d, BM-DMA disabled\n", rev);
		d.dma_ops = शून्य;
		d.mwdma_mask = 0;
		d.host_flags &= ~IDE_HFLAG_SERIALIZE_DMA;
	पूर्ण

	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id sl82c105_pci_tbl[] = अणु
	अणु PCI_VDEVICE(WINBOND, PCI_DEVICE_ID_WINBOND_82C105), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, sl82c105_pci_tbl);

अटल काष्ठा pci_driver sl82c105_pci_driver = अणु
	.name		= "W82C105_IDE",
	.id_table	= sl82c105_pci_tbl,
	.probe		= sl82c105_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init sl82c105_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&sl82c105_pci_driver);
पूर्ण

अटल व्योम __निकास sl82c105_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sl82c105_pci_driver);
पूर्ण

module_init(sl82c105_ide_init);
module_निकास(sl82c105_ide_निकास);

MODULE_DESCRIPTION("PCI driver module for W82C105 IDE");
MODULE_LICENSE("GPL");
