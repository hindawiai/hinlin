<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004-2005 Advanced Micro Devices, Inc.
 * Copyright (C)      2007 Bartlomiej Zolnierkiewicz
 *
 * History:
 * 09/20/2005 - Jaya Kumar <jayakumar.ide@gmail.com>
 * - Reworked tuneproc, set_drive, misc mods to prep क्रम मुख्यline
 * - Work was sponsored by CIS (M) Sdn Bhd.
 * Ported to Kernel 2.6.11 on June 26, 2005 by
 *   Wolfgang Zuleger <wolfgang.zuleger@gmx.de>
 *   Alexander Kiausch <alex.kiausch@t-online.de>
 * Originally developed by AMD क्रम 2.4/2.6
 *
 * Development of this chipset driver was funded
 * by the nice folks at National Semiconductor/AMD.
 *
 * Documentation:
 *  CS5535 करोcumentation available from AMD
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>

#घोषणा DRV_NAME "cs5535"

#घोषणा MSR_ATAC_BASE		0x51300000
#घोषणा ATAC_GLD_MSR_CAP	(MSR_ATAC_BASE+0)
#घोषणा ATAC_GLD_MSR_CONFIG	(MSR_ATAC_BASE+0x01)
#घोषणा ATAC_GLD_MSR_SMI	(MSR_ATAC_BASE+0x02)
#घोषणा ATAC_GLD_MSR_ERROR	(MSR_ATAC_BASE+0x03)
#घोषणा ATAC_GLD_MSR_PM		(MSR_ATAC_BASE+0x04)
#घोषणा ATAC_GLD_MSR_DIAG	(MSR_ATAC_BASE+0x05)
#घोषणा ATAC_IO_BAR		(MSR_ATAC_BASE+0x08)
#घोषणा ATAC_RESET		(MSR_ATAC_BASE+0x10)
#घोषणा ATAC_CH0D0_PIO		(MSR_ATAC_BASE+0x20)
#घोषणा ATAC_CH0D0_DMA		(MSR_ATAC_BASE+0x21)
#घोषणा ATAC_CH0D1_PIO		(MSR_ATAC_BASE+0x22)
#घोषणा ATAC_CH0D1_DMA		(MSR_ATAC_BASE+0x23)
#घोषणा ATAC_PCI_ABRTERR	(MSR_ATAC_BASE+0x24)
#घोषणा ATAC_BM0_CMD_PRIM	0x00
#घोषणा ATAC_BM0_STS_PRIM	0x02
#घोषणा ATAC_BM0_PRD		0x04
#घोषणा CS5535_CABLE_DETECT	0x48

/* Format I PIO settings. We separate out cmd and data क्रम safer timings */

अटल अचिन्हित पूर्णांक cs5535_pio_cmd_timings[5] =
अणु 0xF7F4, 0x53F3, 0x13F1, 0x5131, 0x1131 पूर्ण;
अटल अचिन्हित पूर्णांक cs5535_pio_dta_timings[5] =
अणु 0xF7F4, 0xF173, 0x8141, 0x5131, 0x1131 पूर्ण;

अटल अचिन्हित पूर्णांक cs5535_mwdma_timings[3] =
अणु 0x7F0FFFF3, 0x7F035352, 0x7f024241 पूर्ण;

अटल अचिन्हित पूर्णांक cs5535_udma_timings[5] =
अणु 0x7F7436A1, 0x7F733481, 0x7F723261, 0x7F713161, 0x7F703061 पूर्ण;

/* Macros to check अगर the रेजिस्टर is the reset value -  reset value is an
   invalid timing and indicates the रेजिस्टर has not been set previously */

#घोषणा CS5535_BAD_PIO(timings) ( (timings&~0x80000000UL) == 0x00009172 )
#घोषणा CS5535_BAD_DMA(timings) ( (timings & 0x000FFFFF) == 0x00077771 )

/****
 *	cs5535_set_speed         -     Configure the chipset to the new speed
 *	@drive: Drive to set up
 *	@speed: desired speed
 *
 *	cs5535_set_speed() configures the chipset to a new speed.
 */
अटल व्योम cs5535_set_speed(ide_drive_t *drive, स्थिर u8 speed)
अणु
	u32 reg = 0, dummy;
	u8 unit = drive->dn & 1;

	/* Set the PIO timings */
	अगर (speed < XFER_SW_DMA_0) अणु
		ide_drive_t *pair = ide_get_pair_dev(drive);
		u8 cmd, pioa;

		cmd = pioa = speed - XFER_PIO_0;

		अगर (pair) अणु
			u8 piob = pair->pio_mode - XFER_PIO_0;

			अगर (piob < cmd)
				cmd = piob;
		पूर्ण

		/* Write the speed of the current drive */
		reg = (cs5535_pio_cmd_timings[cmd] << 16) |
			cs5535_pio_dta_timings[pioa];
		wrmsr(unit ? ATAC_CH0D1_PIO : ATAC_CH0D0_PIO, reg, 0);

		/* And अगर nessesary - change the speed of the other drive */
		rdmsr(unit ?  ATAC_CH0D0_PIO : ATAC_CH0D1_PIO, reg, dummy);

		अगर (((reg >> 16) & cs5535_pio_cmd_timings[cmd]) !=
			cs5535_pio_cmd_timings[cmd]) अणु
			reg &= 0x0000FFFF;
			reg |= cs5535_pio_cmd_timings[cmd] << 16;
			wrmsr(unit ? ATAC_CH0D0_PIO : ATAC_CH0D1_PIO, reg, 0);
		पूर्ण

		/* Set bit 31 of the DMA रेजिस्टर क्रम PIO क्रमmat 1 timings */
		rdmsr(unit ?  ATAC_CH0D1_DMA : ATAC_CH0D0_DMA, reg, dummy);
		wrmsr(unit ? ATAC_CH0D1_DMA : ATAC_CH0D0_DMA,
					reg | 0x80000000UL, 0);
	पूर्ण अन्यथा अणु
		rdmsr(unit ? ATAC_CH0D1_DMA : ATAC_CH0D0_DMA, reg, dummy);

		reg &= 0x80000000UL;  /* Preserve the PIO क्रमmat bit */

		अगर (speed >= XFER_UDMA_0 && speed <= XFER_UDMA_4)
			reg |= cs5535_udma_timings[speed - XFER_UDMA_0];
		अन्यथा अगर (speed >= XFER_MW_DMA_0 && speed <= XFER_MW_DMA_2)
			reg |= cs5535_mwdma_timings[speed - XFER_MW_DMA_0];
		अन्यथा
			वापस;

		wrmsr(unit ? ATAC_CH0D1_DMA : ATAC_CH0D0_DMA, reg, 0);
	पूर्ण
पूर्ण

/**
 *	cs5535_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Programs the chipset क्रम DMA mode.
 */

अटल व्योम cs5535_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	cs5535_set_speed(drive, drive->dma_mode);
पूर्ण

/**
 *	cs5535_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	A callback from the upper layers क्रम PIO-only tuning.
 */

अटल व्योम cs5535_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	cs5535_set_speed(drive, drive->pio_mode);
पूर्ण

अटल u8 cs5535_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u8 bit;

	/* अगर a 80 wire cable was detected */
	pci_पढ़ो_config_byte(dev, CS5535_CABLE_DETECT, &bit);

	वापस (bit & 1) ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops cs5535_port_ops = अणु
	.set_pio_mode		= cs5535_set_pio_mode,
	.set_dma_mode		= cs5535_set_dma_mode,
	.cable_detect		= cs5535_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info cs5535_chipset = अणु
	.name		= DRV_NAME,
	.port_ops	= &cs5535_port_ops,
	.host_flags	= IDE_HFLAG_SINGLE | IDE_HFLAG_POST_SET_MODE,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA4,
पूर्ण;

अटल पूर्णांक cs5535_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &cs5535_chipset, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cs5535_pci_tbl[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_CS5535_IDE), 0 पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_CS5535_IDE), पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, cs5535_pci_tbl);

अटल काष्ठा pci_driver cs5535_pci_driver = अणु
	.name		= "CS5535_IDE",
	.id_table	= cs5535_pci_tbl,
	.probe		= cs5535_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init cs5535_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&cs5535_pci_driver);
पूर्ण

अटल व्योम __निकास cs5535_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cs5535_pci_driver);
पूर्ण

module_init(cs5535_ide_init);
module_निकास(cs5535_ide_निकास);

MODULE_AUTHOR("AMD");
MODULE_DESCRIPTION("PCI driver module for AMD/NS CS5535 IDE");
MODULE_LICENSE("GPL");
