<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2000-2002 Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2006-2007 MontaVista Software, Inc. <source@mvista.com>
 *
 * This is a look-alike variation of the ICH0 PIIX4 Ultra-66,
 * but this keeps the ISA-Bridge and slots alive.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "slc90e66"

अटल DEFINE_SPINLOCK(slc90e66_lock);

अटल व्योम slc90e66_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	पूर्णांक is_slave		= drive->dn & 1;
	पूर्णांक master_port		= hwअगर->channel ? 0x42 : 0x40;
	पूर्णांक slave_port		= 0x44;
	अचिन्हित दीर्घ flags;
	u16 master_data;
	u8 slave_data;
	पूर्णांक control = 0;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

				     /* ISP  RTC */
	अटल स्थिर u8 timings[][2] = अणु
					अणु 0, 0 पूर्ण,
					अणु 0, 0 पूर्ण,
					अणु 1, 0 पूर्ण,
					अणु 2, 1 पूर्ण,
					अणु 2, 3 पूर्ण, पूर्ण;

	spin_lock_irqsave(&slc90e66_lock, flags);
	pci_पढ़ो_config_word(dev, master_port, &master_data);

	अगर (pio > 1)
		control |= 1;	/* Programmable timing on */
	अगर (drive->media == ide_disk)
		control |= 4;	/* Prefetch, post ग_लिखो */
	अगर (ide_pio_need_iordy(drive, pio))
		control |= 2;	/* IORDY */
	अगर (is_slave) अणु
		master_data |=  0x4000;
		master_data &= ~0x0070;
		अगर (pio > 1) अणु
			/* Set PPE, IE and TIME */
			master_data |= control << 4;
		पूर्ण
		pci_पढ़ो_config_byte(dev, slave_port, &slave_data);
		slave_data &= hwअगर->channel ? 0x0f : 0xf0;
		slave_data |= ((timings[pio][0] << 2) | timings[pio][1]) <<
			       (hwअगर->channel ? 4 : 0);
	पूर्ण अन्यथा अणु
		master_data &= ~0x3307;
		अगर (pio > 1) अणु
			/* enable PPE, IE and TIME */
			master_data |= control;
		पूर्ण
		master_data |= (timings[pio][0] << 12) | (timings[pio][1] << 8);
	पूर्ण
	pci_ग_लिखो_config_word(dev, master_port, master_data);
	अगर (is_slave)
		pci_ग_लिखो_config_byte(dev, slave_port, slave_data);
	spin_unlock_irqrestore(&slc90e66_lock, flags);
पूर्ण

अटल व्योम slc90e66_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 maslave		= hwअगर->channel ? 0x42 : 0x40;
	पूर्णांक sitre = 0, a_speed	= 7 << (drive->dn * 4);
	पूर्णांक u_speed = 0, u_flag = 1 << drive->dn;
	u16			reg4042, reg44, reg48, reg4a;
	स्थिर u8 speed		= drive->dma_mode;

	pci_पढ़ो_config_word(dev, maslave, &reg4042);
	sitre = (reg4042 & 0x4000) ? 1 : 0;
	pci_पढ़ो_config_word(dev, 0x44, &reg44);
	pci_पढ़ो_config_word(dev, 0x48, &reg48);
	pci_पढ़ो_config_word(dev, 0x4a, &reg4a);

	अगर (speed >= XFER_UDMA_0) अणु
		u_speed = (speed - XFER_UDMA_0) << (drive->dn * 4);

		अगर (!(reg48 & u_flag))
			pci_ग_लिखो_config_word(dev, 0x48, reg48|u_flag);
		अगर ((reg4a & a_speed) != u_speed) अणु
			pci_ग_लिखो_config_word(dev, 0x4a, reg4a & ~a_speed);
			pci_पढ़ो_config_word(dev, 0x4a, &reg4a);
			pci_ग_लिखो_config_word(dev, 0x4a, reg4a|u_speed);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर u8 mwdma_to_pio[] = अणु 0, 3, 4 पूर्ण;

		अगर (reg48 & u_flag)
			pci_ग_लिखो_config_word(dev, 0x48, reg48 & ~u_flag);
		अगर (reg4a & a_speed)
			pci_ग_लिखो_config_word(dev, 0x4a, reg4a & ~a_speed);

		अगर (speed >= XFER_MW_DMA_0)
			drive->pio_mode =
				mwdma_to_pio[speed - XFER_MW_DMA_0] + XFER_PIO_0;
		अन्यथा
			drive->pio_mode = XFER_PIO_2; /* क्रम SWDMA2 */

		slc90e66_set_pio_mode(hwअगर, drive);
	पूर्ण
पूर्ण

अटल u8 slc90e66_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u8 reg47 = 0, mask = hwअगर->channel ? 0x01 : 0x02;

	pci_पढ़ो_config_byte(dev, 0x47, &reg47);

	/* bit[0(1)]: 0:80, 1:40 */
	वापस (reg47 & mask) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops slc90e66_port_ops = अणु
	.set_pio_mode		= slc90e66_set_pio_mode,
	.set_dma_mode		= slc90e66_set_dma_mode,
	.cable_detect		= slc90e66_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info slc90e66_chipset = अणु
	.name		= DRV_NAME,
	.enablebits	= अणु अणु0x41, 0x80, 0x80पूर्ण, अणु0x43, 0x80, 0x80पूर्ण पूर्ण,
	.port_ops	= &slc90e66_port_ops,
	.pio_mask	= ATA_PIO4,
	.swdma_mask	= ATA_SWDMA2_ONLY,
	.mwdma_mask	= ATA_MWDMA12_ONLY,
	.udma_mask	= ATA_UDMA4,
पूर्ण;

अटल पूर्णांक slc90e66_init_one(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &slc90e66_chipset, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id slc90e66_pci_tbl[] = अणु
	अणु PCI_VDEVICE(EFAR, PCI_DEVICE_ID_EFAR_SLC90E66_1), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, slc90e66_pci_tbl);

अटल काष्ठा pci_driver slc90e66_pci_driver = अणु
	.name		= "SLC90e66_IDE",
	.id_table	= slc90e66_pci_tbl,
	.probe		= slc90e66_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init slc90e66_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&slc90e66_pci_driver);
पूर्ण

अटल व्योम __निकास slc90e66_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&slc90e66_pci_driver);
पूर्ण

module_init(slc90e66_ide_init);
module_निकास(slc90e66_ide_निकास);

MODULE_AUTHOR("Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for SLC90E66 IDE");
MODULE_LICENSE("GPL");
