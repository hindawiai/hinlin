<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ITE 8213 IDE driver
 *
 * Copyright (C) 2006 Jack Lee
 * Copyright (C) 2006 Alan Cox
 * Copyright (C) 2007 Bartlomiej Zolnierkiewicz
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "it8213"

/**
 *	it8213_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Set the पूर्णांकerface PIO mode.
 */

अटल व्योम it8213_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	पूर्णांक is_slave		= drive->dn & 1;
	पूर्णांक master_port		= 0x40;
	पूर्णांक slave_port		= 0x44;
	अचिन्हित दीर्घ flags;
	u16 master_data;
	u8 slave_data;
	अटल DEFINE_SPINLOCK(tune_lock);
	पूर्णांक control = 0;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	अटल स्थिर u8 timings[][2] = अणु
					अणु 0, 0 पूर्ण,
					अणु 0, 0 पूर्ण,
					अणु 1, 0 पूर्ण,
					अणु 2, 1 पूर्ण,
					अणु 2, 3 पूर्ण, पूर्ण;

	spin_lock_irqsave(&tune_lock, flags);
	pci_पढ़ो_config_word(dev, master_port, &master_data);

	अगर (pio > 1)
		control |= 1;	/* Programmable timing on */
	अगर (drive->media != ide_disk)
		control |= 4;	/* ATAPI */
	अगर (ide_pio_need_iordy(drive, pio))
		control |= 2;	/* IORDY */
	अगर (is_slave) अणु
		master_data |=  0x4000;
		master_data &= ~0x0070;
		अगर (pio > 1)
			master_data = master_data | (control << 4);
		pci_पढ़ो_config_byte(dev, slave_port, &slave_data);
		slave_data = slave_data & 0xf0;
		slave_data = slave_data | (timings[pio][0] << 2) | timings[pio][1];
	पूर्ण अन्यथा अणु
		master_data &= ~0x3307;
		अगर (pio > 1)
			master_data = master_data | control;
		master_data = master_data | (timings[pio][0] << 12) | (timings[pio][1] << 8);
	पूर्ण
	pci_ग_लिखो_config_word(dev, master_port, master_data);
	अगर (is_slave)
		pci_ग_लिखो_config_byte(dev, slave_port, slave_data);
	spin_unlock_irqrestore(&tune_lock, flags);
पूर्ण

/**
 *	it8213_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Tune the ITE chipset क्रम the DMA mode.
 */

अटल व्योम it8213_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 maslave		= 0x40;
	पूर्णांक a_speed		= 3 << (drive->dn * 4);
	पूर्णांक u_flag		= 1 << drive->dn;
	पूर्णांक v_flag		= 0x01 << drive->dn;
	पूर्णांक w_flag		= 0x10 << drive->dn;
	पूर्णांक u_speed		= 0;
	u16			reg4042, reg4a;
	u8			reg48, reg54, reg55;
	स्थिर u8 speed		= drive->dma_mode;

	pci_पढ़ो_config_word(dev, maslave, &reg4042);
	pci_पढ़ो_config_byte(dev, 0x48, &reg48);
	pci_पढ़ो_config_word(dev, 0x4a, &reg4a);
	pci_पढ़ो_config_byte(dev, 0x54, &reg54);
	pci_पढ़ो_config_byte(dev, 0x55, &reg55);

	अगर (speed >= XFER_UDMA_0) अणु
		u8 udma = speed - XFER_UDMA_0;

		u_speed = min_t(u8, 2 - (udma & 1), udma) << (drive->dn * 4);

		अगर (!(reg48 & u_flag))
			pci_ग_लिखो_config_byte(dev, 0x48, reg48 | u_flag);
		अगर (speed >= XFER_UDMA_5)
			pci_ग_लिखो_config_byte(dev, 0x55, (u8) reg55|w_flag);
		अन्यथा
			pci_ग_लिखो_config_byte(dev, 0x55, (u8) reg55 & ~w_flag);

		अगर ((reg4a & a_speed) != u_speed)
			pci_ग_लिखो_config_word(dev, 0x4a, (reg4a & ~a_speed) | u_speed);
		अगर (speed > XFER_UDMA_2) अणु
			अगर (!(reg54 & v_flag))
				pci_ग_लिखो_config_byte(dev, 0x54, reg54 | v_flag);
		पूर्ण अन्यथा
			pci_ग_लिखो_config_byte(dev, 0x54, reg54 & ~v_flag);
	पूर्ण अन्यथा अणु
		स्थिर u8 mwdma_to_pio[] = अणु 0, 3, 4 पूर्ण;

		अगर (reg48 & u_flag)
			pci_ग_लिखो_config_byte(dev, 0x48, reg48 & ~u_flag);
		अगर (reg4a & a_speed)
			pci_ग_लिखो_config_word(dev, 0x4a, reg4a & ~a_speed);
		अगर (reg54 & v_flag)
			pci_ग_लिखो_config_byte(dev, 0x54, reg54 & ~v_flag);
		अगर (reg55 & w_flag)
			pci_ग_लिखो_config_byte(dev, 0x55, (u8) reg55 & ~w_flag);

		अगर (speed >= XFER_MW_DMA_0)
			drive->pio_mode =
				mwdma_to_pio[speed - XFER_MW_DMA_0] + XFER_PIO_0;
		अन्यथा
			drive->pio_mode = XFER_PIO_2; /* क्रम SWDMA2 */

		it8213_set_pio_mode(hwअगर, drive);
	पूर्ण
पूर्ण

अटल u8 it8213_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u8 reg42h = 0;

	pci_पढ़ो_config_byte(dev, 0x42, &reg42h);

	वापस (reg42h & 0x02) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops it8213_port_ops = अणु
	.set_pio_mode		= it8213_set_pio_mode,
	.set_dma_mode		= it8213_set_dma_mode,
	.cable_detect		= it8213_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info it8213_chipset = अणु
	.name		= DRV_NAME,
	.enablebits	= अणु अणु0x41, 0x80, 0x80पूर्ण पूर्ण,
	.port_ops	= &it8213_port_ops,
	.host_flags	= IDE_HFLAG_SINGLE,
	.pio_mask	= ATA_PIO4,
	.swdma_mask	= ATA_SWDMA2_ONLY,
	.mwdma_mask	= ATA_MWDMA12_ONLY,
	.udma_mask	= ATA_UDMA6,
पूर्ण;

/**
 *	it8213_init_one	-	pci layer discovery entry
 *	@dev: PCI device
 *	@id: ident table entry
 *
 *	Called by the PCI code when it finds an ITE8213 controller. As
 *	this device follows the standard पूर्णांकerfaces we can use the
 *	standard helper functions to करो almost all the work क्रम us.
 */

अटल पूर्णांक it8213_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &it8213_chipset, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id it8213_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8213), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, it8213_pci_tbl);

अटल काष्ठा pci_driver it8213_pci_driver = अणु
	.name		= "ITE8213_IDE",
	.id_table	= it8213_pci_tbl,
	.probe		= it8213_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init it8213_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&it8213_pci_driver);
पूर्ण

अटल व्योम __निकास it8213_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&it8213_pci_driver);
पूर्ण

module_init(it8213_ide_init);
module_निकास(it8213_ide_निकास);

MODULE_AUTHOR("Jack Lee, Alan Cox");
MODULE_DESCRIPTION("PCI driver module for the ITE 8213");
MODULE_LICENSE("GPL");
