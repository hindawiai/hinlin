<शैली गुरु>
/*
 * Copyright (C) 1999-2000	Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2002		Lionel Bouton <Lionel.Bouton@inet6.fr>, Maपूर्णांकainer
 * Copyright (C) 2003		Vojtech Pavlik <vojtech@suse.cz>
 * Copyright (C) 2007-2009	Bartlomiej Zolnierkiewicz
 *
 * May be copied or modअगरied under the terms of the GNU General Public License
 *
 *
 * Thanks :
 *
 * SiS Taiwan		: क्रम direct support and hardware.
 * Daniela Engert	: क्रम initial ATA100 advices and numerous others.
 * John Fremlin, Manfred Spraul, Dave Morgan, Peter Kjellerstedt	:
 *			  क्रम checking code correctness, providing patches.
 *
 *
 * Original tests and design on the SiS620 chipset.
 * ATA100 tests and design on the SiS735 chipset.
 * ATA16/33 support from specs
 * ATA133 support क्रम SiS961/962 by L.C. Chang <lcchang@sis.com.tw>
 * ATA133 961/962/963 fixes by Vojtech Pavlik <vojtech@suse.cz>
 *
 * Documentation:
 *	SiS chipset करोcumentation available under NDA to companies only
 *      (not to inभागiduals).
 */

/*
 * The original SiS5513 comes from a SiS5511/55112/5513 chipset. The original
 * SiS5513 was also used in the SiS5596/5513 chipset. Thus अगर we see a SiS5511
 * or SiS5596, we can assume we see the first MWDMA-16 capable SiS5513 chip.
 *
 * Later SiS chipsets पूर्णांकegrated the 5513 functionality पूर्णांकo the NorthBridge,
 * starting with SiS5571 and up to SiS745. The PCI ID didn't change, though. We
 * can figure out that we have a more modern and more capable 5513 by looking
 * क्रम the respective NorthBridge IDs.
 *
 * Even later (96x family) SiS chipsets use the MuTIOL link and place the 5513
 * पूर्णांकo the SouthBrige. Here we cannot rely on looking up the NorthBridge PCI
 * ID, जबतक the now ATA-133 capable 5513 still has the same PCI ID.
 * Fortunately the 5513 can be 'unmasked' by fiddling with some config space
 * bits, changing its device id to the true one - 5517 क्रम 961 and 5518 क्रम
 * 962/963.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>

#घोषणा DRV_NAME "sis5513"

/* रेजिस्टरs layout and init values are chipset family dependent */
#अघोषित ATA_16
#घोषणा ATA_16		0x01
#घोषणा ATA_33		0x02
#घोषणा ATA_66		0x03
#घोषणा ATA_100a	0x04 /* SiS730/SiS550 is ATA100 with ATA66 layout */
#घोषणा ATA_100		0x05
#घोषणा ATA_133a	0x06 /* SiS961b with 133 support */
#घोषणा ATA_133		0x07 /* SiS962/963 */

अटल u8 chipset_family;

/*
 * Devices supported
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u16 host_id;
	u8 chipset_family;
	u8 flags;
पूर्ण SiSHostChipInfo[] = अणु
	अणु "SiS968",	PCI_DEVICE_ID_SI_968,	ATA_133  पूर्ण,
	अणु "SiS966",	PCI_DEVICE_ID_SI_966,	ATA_133  पूर्ण,
	अणु "SiS965",	PCI_DEVICE_ID_SI_965,	ATA_133  पूर्ण,
	अणु "SiS745",	PCI_DEVICE_ID_SI_745,	ATA_100  पूर्ण,
	अणु "SiS735",	PCI_DEVICE_ID_SI_735,	ATA_100  पूर्ण,
	अणु "SiS733",	PCI_DEVICE_ID_SI_733,	ATA_100  पूर्ण,
	अणु "SiS635",	PCI_DEVICE_ID_SI_635,	ATA_100  पूर्ण,
	अणु "SiS633",	PCI_DEVICE_ID_SI_633,	ATA_100  पूर्ण,

	अणु "SiS730",	PCI_DEVICE_ID_SI_730,	ATA_100a पूर्ण,
	अणु "SiS550",	PCI_DEVICE_ID_SI_550,	ATA_100a पूर्ण,

	अणु "SiS640",	PCI_DEVICE_ID_SI_640,	ATA_66   पूर्ण,
	अणु "SiS630",	PCI_DEVICE_ID_SI_630,	ATA_66   पूर्ण,
	अणु "SiS620",	PCI_DEVICE_ID_SI_620,	ATA_66   पूर्ण,
	अणु "SiS540",	PCI_DEVICE_ID_SI_540,	ATA_66   पूर्ण,
	अणु "SiS530",	PCI_DEVICE_ID_SI_530,	ATA_66   पूर्ण,

	अणु "SiS5600",	PCI_DEVICE_ID_SI_5600,	ATA_33   पूर्ण,
	अणु "SiS5598",	PCI_DEVICE_ID_SI_5598,	ATA_33   पूर्ण,
	अणु "SiS5597",	PCI_DEVICE_ID_SI_5597,	ATA_33   पूर्ण,
	अणु "SiS5591/2",	PCI_DEVICE_ID_SI_5591,	ATA_33   पूर्ण,
	अणु "SiS5582",	PCI_DEVICE_ID_SI_5582,	ATA_33   पूर्ण,
	अणु "SiS5581",	PCI_DEVICE_ID_SI_5581,	ATA_33   पूर्ण,

	अणु "SiS5596",	PCI_DEVICE_ID_SI_5596,	ATA_16   पूर्ण,
	अणु "SiS5571",	PCI_DEVICE_ID_SI_5571,	ATA_16   पूर्ण,
	अणु "SiS5517",	PCI_DEVICE_ID_SI_5517,	ATA_16   पूर्ण,
	अणु "SiS551x",	PCI_DEVICE_ID_SI_5511,	ATA_16   पूर्ण,
पूर्ण;

/* Cycle समय bits and values vary across chip dma capabilities
   These three arrays hold the रेजिस्टर layout and the values to set.
   Indexed by chipset_family and (dma_mode - XFER_UDMA_0) */

/* अणु0, ATA_16, ATA_33, ATA_66, ATA_100a, ATA_100, ATA_133पूर्ण */
अटल u8 cycle_समय_offset[] = अणु 0, 0, 5, 4, 4, 0, 0 पूर्ण;
अटल u8 cycle_समय_range[]  = अणु 0, 0, 2, 3, 3, 4, 4 पूर्ण;
अटल u8 cycle_समय_value[][XFER_UDMA_6 - XFER_UDMA_0 + 1] = अणु
	अणु  0,  0, 0, 0, 0, 0, 0 पूर्ण, /* no UDMA */
	अणु  0,  0, 0, 0, 0, 0, 0 पूर्ण, /* no UDMA */
	अणु  3,  2, 1, 0, 0, 0, 0 पूर्ण, /* ATA_33 */
	अणु  7,  5, 3, 2, 1, 0, 0 पूर्ण, /* ATA_66 */
	अणु  7,  5, 3, 2, 1, 0, 0 पूर्ण, /* ATA_100a (730 specअगरic),
				      dअगरferent cycle_समय range and offset */
	अणु 11,  7, 5, 4, 2, 1, 0 पूर्ण, /* ATA_100 */
	अणु 15, 10, 7, 5, 3, 2, 1 पूर्ण, /* ATA_133a (earliest 691 southbridges) */
	अणु 15, 10, 7, 5, 3, 2, 1 पूर्ण, /* ATA_133 */
पूर्ण;
/* CRC Valid Setup Time vary across IDE घड़ी setting 33/66/100/133
   See SiS962 data sheet क्रम more detail */
अटल u8 cvs_समय_value[][XFER_UDMA_6 - XFER_UDMA_0 + 1] = अणु
	अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण, /* no UDMA */
	अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण, /* no UDMA */
	अणु 2, 1, 1, 0, 0, 0, 0 पूर्ण,
	अणु 4, 3, 2, 1, 0, 0, 0 पूर्ण,
	अणु 4, 3, 2, 1, 0, 0, 0 पूर्ण,
	अणु 6, 4, 3, 1, 1, 1, 0 पूर्ण,
	अणु 9, 6, 4, 2, 2, 2, 2 पूर्ण,
	अणु 9, 6, 4, 2, 2, 2, 2 पूर्ण,
पूर्ण;
/* Initialize समय, Active समय, Recovery समय vary across
   IDE घड़ी settings. These 3 arrays hold the रेजिस्टर value
   क्रम PIO0/1/2/3/4 and DMA0/1/2 mode in order */
अटल u8 ini_समय_value[][8] = अणु
	अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 2, 1, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु 4, 3, 1, 1, 1, 3, 1, 1 पूर्ण,
	अणु 4, 3, 1, 1, 1, 3, 1, 1 पूर्ण,
	अणु 6, 4, 2, 2, 2, 4, 2, 2 पूर्ण,
	अणु 9, 6, 3, 3, 3, 6, 3, 3 पूर्ण,
	अणु 9, 6, 3, 3, 3, 6, 3, 3 पूर्ण,
पूर्ण;
अटल u8 act_समय_value[][8] = अणु
	अणु  0,  0,  0,  0, 0,  0,  0, 0 पूर्ण,
	अणु  0,  0,  0,  0, 0,  0,  0, 0 पूर्ण,
	अणु  9,  9,  9,  2, 2,  7,  2, 2 पूर्ण,
	अणु 19, 19, 19,  5, 4, 14,  5, 4 पूर्ण,
	अणु 19, 19, 19,  5, 4, 14,  5, 4 पूर्ण,
	अणु 28, 28, 28,  7, 6, 21,  7, 6 पूर्ण,
	अणु 38, 38, 38, 10, 9, 28, 10, 9 पूर्ण,
	अणु 38, 38, 38, 10, 9, 28, 10, 9 पूर्ण,
पूर्ण;
अटल u8 rco_समय_value[][8] = अणु
	अणु  0,  0, 0,  0, 0,  0,  0, 0 पूर्ण,
	अणु  0,  0, 0,  0, 0,  0,  0, 0 पूर्ण,
	अणु  9,  2, 0,  2, 0,  7,  1, 1 पूर्ण,
	अणु 19,  5, 1,  5, 2, 16,  3, 2 पूर्ण,
	अणु 19,  5, 1,  5, 2, 16,  3, 2 पूर्ण,
	अणु 30,  9, 3,  9, 4, 25,  6, 4 पूर्ण,
	अणु 40, 12, 4, 12, 5, 34, 12, 5 पूर्ण,
	अणु 40, 12, 4, 12, 5, 34, 12, 5 पूर्ण,
पूर्ण;

/*
 * Prपूर्णांकing configuration
 */
/* Used क्रम chipset type prपूर्णांकing at boot समय */
अटल अक्षर *chipset_capability[] = अणु
	"ATA", "ATA 16",
	"ATA 33", "ATA 66",
	"ATA 100 (1st gen)", "ATA 100 (2nd gen)",
	"ATA 133 (1st gen)", "ATA 133 (2nd gen)"
पूर्ण;

/*
 * Configuration functions
 */

अटल u8 sis_ata133_get_base(ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u32 reg54 = 0;

	pci_पढ़ो_config_dword(dev, 0x54, &reg54);

	वापस ((reg54 & 0x40000000) ? 0x70 : 0x40) + drive->dn * 4;
पूर्ण

अटल व्योम sis_ata16_program_timings(ide_drive_t *drive, स्थिर u8 mode)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u16 t1 = 0;
	u8 drive_pci = 0x40 + drive->dn * 2;

	स्थिर u16 pio_timings[]   = अणु 0x000, 0x607, 0x404, 0x303, 0x301 पूर्ण;
	स्थिर u16 mwdma_timings[] = अणु 0x008, 0x302, 0x301 पूर्ण;

	pci_पढ़ो_config_word(dev, drive_pci, &t1);

	/* clear active/recovery timings */
	t1 &= ~0x070f;
	अगर (mode >= XFER_MW_DMA_0) अणु
		अगर (chipset_family > ATA_16)
			t1 &= ~0x8000;	/* disable UDMA */
		t1 |= mwdma_timings[mode - XFER_MW_DMA_0];
	पूर्ण अन्यथा
		t1 |= pio_timings[mode - XFER_PIO_0];

	pci_ग_लिखो_config_word(dev, drive_pci, t1);
पूर्ण

अटल व्योम sis_ata100_program_timings(ide_drive_t *drive, स्थिर u8 mode)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u8 t1, drive_pci = 0x40 + drive->dn * 2;

	/* timing bits: 7:4 active 3:0 recovery */
	स्थिर u8 pio_timings[]   = अणु 0x00, 0x67, 0x44, 0x33, 0x31 पूर्ण;
	स्थिर u8 mwdma_timings[] = अणु 0x08, 0x32, 0x31 पूर्ण;

	अगर (mode >= XFER_MW_DMA_0) अणु
		u8 t2 = 0;

		pci_पढ़ो_config_byte(dev, drive_pci, &t2);
		t2 &= ~0x80;	/* disable UDMA */
		pci_ग_लिखो_config_byte(dev, drive_pci, t2);

		t1 = mwdma_timings[mode - XFER_MW_DMA_0];
	पूर्ण अन्यथा
		t1 = pio_timings[mode - XFER_PIO_0];

	pci_ग_लिखो_config_byte(dev, drive_pci + 1, t1);
पूर्ण

अटल व्योम sis_ata133_program_timings(ide_drive_t *drive, स्थिर u8 mode)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u32 t1 = 0;
	u8 drive_pci = sis_ata133_get_base(drive), clk, idx;

	pci_पढ़ो_config_dword(dev, drive_pci, &t1);

	t1 &= 0xc0c00fff;
	clk = (t1 & 0x08) ? ATA_133 : ATA_100;
	अगर (mode >= XFER_MW_DMA_0) अणु
		t1 &= ~0x04;	/* disable UDMA */
		idx = mode - XFER_MW_DMA_0 + 5;
	पूर्ण अन्यथा
		idx = mode - XFER_PIO_0;
	t1 |= ini_समय_value[clk][idx] << 12;
	t1 |= act_समय_value[clk][idx] << 16;
	t1 |= rco_समय_value[clk][idx] << 24;

	pci_ग_लिखो_config_dword(dev, drive_pci, t1);
पूर्ण

अटल व्योम sis_program_timings(ide_drive_t *drive, स्थिर u8 mode)
अणु
	अगर (chipset_family < ATA_100)		/* ATA_16/33/66/100a */
		sis_ata16_program_timings(drive, mode);
	अन्यथा अगर (chipset_family < ATA_133)	/* ATA_100/133a */
		sis_ata100_program_timings(drive, mode);
	अन्यथा					/* ATA_133 */
		sis_ata133_program_timings(drive, mode);
पूर्ण

अटल व्योम config_drive_art_rwp(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 reg4bh		= 0;
	u8 rw_prefetch		= 0;

	pci_पढ़ो_config_byte(dev, 0x4b, &reg4bh);

	rw_prefetch = reg4bh & ~(0x11 << drive->dn);

	अगर (drive->media == ide_disk)
		rw_prefetch |= 0x11 << drive->dn;

	अगर (reg4bh != rw_prefetch)
		pci_ग_लिखो_config_byte(dev, 0x4b, rw_prefetch);
पूर्ण

अटल व्योम sis_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	config_drive_art_rwp(drive);
	sis_program_timings(drive, drive->pio_mode);
पूर्ण

अटल व्योम sis_ata133_program_udma_timings(ide_drive_t *drive, स्थिर u8 mode)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u32 regdw = 0;
	u8 drive_pci = sis_ata133_get_base(drive), clk, idx;

	pci_पढ़ो_config_dword(dev, drive_pci, &regdw);

	regdw |= 0x04;
	regdw &= 0xfffff00f;
	/* check अगर ATA133 enable */
	clk = (regdw & 0x08) ? ATA_133 : ATA_100;
	idx = mode - XFER_UDMA_0;
	regdw |= cycle_समय_value[clk][idx] << 4;
	regdw |= cvs_समय_value[clk][idx] << 8;

	pci_ग_लिखो_config_dword(dev, drive_pci, regdw);
पूर्ण

अटल व्योम sis_ata33_program_udma_timings(ide_drive_t *drive, स्थिर u8 mode)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u8 drive_pci = 0x40 + drive->dn * 2, reg = 0, i = chipset_family;

	pci_पढ़ो_config_byte(dev, drive_pci + 1, &reg);

	/* क्रमce the UDMA bit on अगर we want to use UDMA */
	reg |= 0x80;
	/* clean reg cycle समय bits */
	reg &= ~((0xff >> (8 - cycle_समय_range[i])) << cycle_समय_offset[i]);
	/* set reg cycle समय bits */
	reg |= cycle_समय_value[i][mode - XFER_UDMA_0] << cycle_समय_offset[i];

	pci_ग_लिखो_config_byte(dev, drive_pci + 1, reg);
पूर्ण

अटल व्योम sis_program_udma_timings(ide_drive_t *drive, स्थिर u8 mode)
अणु
	अगर (chipset_family >= ATA_133)	/* ATA_133 */
		sis_ata133_program_udma_timings(drive, mode);
	अन्यथा				/* ATA_33/66/100a/100/133a */
		sis_ata33_program_udma_timings(drive, mode);
पूर्ण

अटल व्योम sis_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	स्थिर u8 speed = drive->dma_mode;

	अगर (speed >= XFER_UDMA_0)
		sis_program_udma_timings(drive, speed);
	अन्यथा
		sis_program_timings(drive, speed);
पूर्ण

अटल u8 sis_ata133_udma_filter(ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u32 regdw = 0;
	u8 drive_pci = sis_ata133_get_base(drive);

	pci_पढ़ो_config_dword(dev, drive_pci, &regdw);

	/* अगर ATA133 disable, we should not set speed above UDMA5 */
	वापस (regdw & 0x08) ? ATA_UDMA6 : ATA_UDMA5;
पूर्ण

अटल पूर्णांक sis_find_family(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *host;
	पूर्णांक i = 0;

	chipset_family = 0;

	क्रम (i = 0; i < ARRAY_SIZE(SiSHostChipInfo) && !chipset_family; i++) अणु

		host = pci_get_device(PCI_VENDOR_ID_SI, SiSHostChipInfo[i].host_id, शून्य);

		अगर (!host)
			जारी;

		chipset_family = SiSHostChipInfo[i].chipset_family;

		/* Special हाल क्रम SiS630 : 630S/ET is ATA_100a */
		अगर (SiSHostChipInfo[i].host_id == PCI_DEVICE_ID_SI_630) अणु
			अगर (host->revision >= 0x30)
				chipset_family = ATA_100a;
		पूर्ण
		pci_dev_put(host);

		prपूर्णांकk(KERN_INFO DRV_NAME " %s: %s %s controller\n",
			pci_name(dev), SiSHostChipInfo[i].name,
			chipset_capability[chipset_family]);
	पूर्ण

	अगर (!chipset_family) अणु /* Beदीर्घs to pci-quirks */

			u32 idemisc;
			u16 trueid;

			/* Disable ID masking and रेजिस्टर remapping */
			pci_पढ़ो_config_dword(dev, 0x54, &idemisc);
			pci_ग_लिखो_config_dword(dev, 0x54, (idemisc & 0x7fffffff));
			pci_पढ़ो_config_word(dev, PCI_DEVICE_ID, &trueid);
			pci_ग_लिखो_config_dword(dev, 0x54, idemisc);

			अगर (trueid == 0x5518) अणु
				prपूर्णांकk(KERN_INFO DRV_NAME " %s: SiS 962/963 MuTIOL IDE UDMA133 controller\n",
					pci_name(dev));
				chipset_family = ATA_133;

				/* Check क्रम 5513 compatibility mapping
				 * We must use this, अन्यथा the port enabled code will fail,
				 * as it expects the enablebits at 0x4a.
				 */
				अगर ((idemisc & 0x40000000) == 0) अणु
					pci_ग_लिखो_config_dword(dev, 0x54, idemisc | 0x40000000);
					prपूर्णांकk(KERN_INFO DRV_NAME " %s: Switching to 5513 register mapping\n",
						pci_name(dev));
				पूर्ण
			पूर्ण
	पूर्ण

	अगर (!chipset_family) अणु /* Beदीर्घs to pci-quirks */

			काष्ठा pci_dev *lpc_bridge;
			u16 trueid;
			u8 prefctl;
			u8 idecfg;

			pci_पढ़ो_config_byte(dev, 0x4a, &idecfg);
			pci_ग_लिखो_config_byte(dev, 0x4a, idecfg | 0x10);
			pci_पढ़ो_config_word(dev, PCI_DEVICE_ID, &trueid);
			pci_ग_लिखो_config_byte(dev, 0x4a, idecfg);

			अगर (trueid == 0x5517) अणु /* SiS 961/961B */

				lpc_bridge = pci_get_slot(dev->bus, 0x10); /* Bus 0, Dev 2, Fn 0 */
				pci_पढ़ो_config_byte(dev, 0x49, &prefctl);
				pci_dev_put(lpc_bridge);

				अगर (lpc_bridge->revision == 0x10 && (prefctl & 0x80)) अणु
					prपूर्णांकk(KERN_INFO DRV_NAME " %s: SiS 961B MuTIOL IDE UDMA133 controller\n",
						pci_name(dev));
					chipset_family = ATA_133a;
				पूर्ण अन्यथा अणु
					prपूर्णांकk(KERN_INFO DRV_NAME " %s: SiS 961 MuTIOL IDE UDMA100 controller\n",
						pci_name(dev));
					chipset_family = ATA_100;
				पूर्ण
			पूर्ण
	पूर्ण

	वापस chipset_family;
पूर्ण

अटल पूर्णांक init_chipset_sis5513(काष्ठा pci_dev *dev)
अणु
	/* Make general config ops here
	   1/ tell IDE channels to operate in Compatibility mode only
	   2/ tell old chips to allow per drive IDE timings */

	u8 reg;
	u16 regw;

	चयन (chipset_family) अणु
	हाल ATA_133:
		/* SiS962 operation mode */
		pci_पढ़ो_config_word(dev, 0x50, &regw);
		अगर (regw & 0x08)
			pci_ग_लिखो_config_word(dev, 0x50, regw&0xfff7);
		pci_पढ़ो_config_word(dev, 0x52, &regw);
		अगर (regw & 0x08)
			pci_ग_लिखो_config_word(dev, 0x52, regw&0xfff7);
		अवरोध;
	हाल ATA_133a:
	हाल ATA_100:
		/* Fixup latency */
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x80);
		/* Set compatibility bit */
		pci_पढ़ो_config_byte(dev, 0x49, &reg);
		अगर (!(reg & 0x01))
			pci_ग_लिखो_config_byte(dev, 0x49, reg|0x01);
		अवरोध;
	हाल ATA_100a:
	हाल ATA_66:
		/* Fixup latency */
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x10);

		/* On ATA_66 chips the bit was अन्यथाwhere */
		pci_पढ़ो_config_byte(dev, 0x52, &reg);
		अगर (!(reg & 0x04))
			pci_ग_लिखो_config_byte(dev, 0x52, reg|0x04);
		अवरोध;
	हाल ATA_33:
		/* On ATA_33 we didn't have a single bit to set */
		pci_पढ़ो_config_byte(dev, 0x09, &reg);
		अगर ((reg & 0x0f) != 0x00)
			pci_ग_लिखो_config_byte(dev, 0x09, reg&0xf0);
		fallthrough;
	हाल ATA_16:
		/* क्रमce per drive recovery and active timings
		   needed on ATA_33 and below chips */
		pci_पढ़ो_config_byte(dev, 0x52, &reg);
		अगर (!(reg & 0x08))
			pci_ग_लिखो_config_byte(dev, 0x52, reg|0x08);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा sis_laptop अणु
	u16 device;
	u16 subvenकरोr;
	u16 subdevice;
पूर्ण;

अटल स्थिर काष्ठा sis_laptop sis_laptop[] = अणु
	/* devid, subvenकरोr, subdev */
	अणु 0x5513, 0x1043, 0x1107 पूर्ण,	/* ASUS A6K */
	अणु 0x5513, 0x1734, 0x105f पूर्ण,	/* FSC Amilo A1630 */
	अणु 0x5513, 0x1071, 0x8640 पूर्ण,     /* EasyNote K5305 */
	/* end marker */
	अणु 0, पूर्ण
पूर्ण;

अटल u8 sis_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	स्थिर काष्ठा sis_laptop *lap = &sis_laptop[0];
	u8 ata66 = 0;

	जबतक (lap->device) अणु
		अगर (lap->device == pdev->device &&
		    lap->subvenकरोr == pdev->subप्रणाली_venकरोr &&
		    lap->subdevice == pdev->subप्रणाली_device)
			वापस ATA_CBL_PATA40_SHORT;
		lap++;
	पूर्ण

	अगर (chipset_family >= ATA_133) अणु
		u16 regw = 0;
		u16 reg_addr = hwअगर->channel ? 0x52: 0x50;
		pci_पढ़ो_config_word(pdev, reg_addr, &regw);
		ata66 = (regw & 0x8000) ? 0 : 1;
	पूर्ण अन्यथा अगर (chipset_family >= ATA_66) अणु
		u8 reg48h = 0;
		u8 mask = hwअगर->channel ? 0x20 : 0x10;
		pci_पढ़ो_config_byte(pdev, 0x48, &reg48h);
		ata66 = (reg48h & mask) ? 0 : 1;
	पूर्ण

	वापस ata66 ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops sis_port_ops = अणु
	.set_pio_mode		= sis_set_pio_mode,
	.set_dma_mode		= sis_set_dma_mode,
	.cable_detect		= sis_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops sis_ata133_port_ops = अणु
	.set_pio_mode		= sis_set_pio_mode,
	.set_dma_mode		= sis_set_dma_mode,
	.udma_filter		= sis_ata133_udma_filter,
	.cable_detect		= sis_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info sis5513_chipset = अणु
	.name		= DRV_NAME,
	.init_chipset	= init_chipset_sis5513,
	.enablebits	= अणु अणु0x4a, 0x02, 0x02पूर्ण, अणु0x4a, 0x04, 0x04पूर्ण पूर्ण,
	.host_flags	= IDE_HFLAG_NO_AUTODMA,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
पूर्ण;

अटल पूर्णांक sis5513_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d = sis5513_chipset;
	u8 udma_rates[] = अणु 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f पूर्ण;
	पूर्णांक rc;

	rc = pci_enable_device(dev);
	अगर (rc)
		वापस rc;

	अगर (sis_find_family(dev) == 0)
		वापस -ENOTSUPP;

	अगर (chipset_family >= ATA_133)
		d.port_ops = &sis_ata133_port_ops;
	अन्यथा
		d.port_ops = &sis_port_ops;

	d.udma_mask = udma_rates[chipset_family];

	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण

अटल व्योम sis5513_हटाओ(काष्ठा pci_dev *dev)
अणु
	ide_pci_हटाओ(dev);
	pci_disable_device(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id sis5513_pci_tbl[] = अणु
	अणु PCI_VDEVICE(SI, PCI_DEVICE_ID_SI_5513), 0 पूर्ण,
	अणु PCI_VDEVICE(SI, PCI_DEVICE_ID_SI_5518), 0 पूर्ण,
	अणु PCI_VDEVICE(SI, PCI_DEVICE_ID_SI_1180), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, sis5513_pci_tbl);

अटल काष्ठा pci_driver sis5513_pci_driver = अणु
	.name		= "SIS_IDE",
	.id_table	= sis5513_pci_tbl,
	.probe		= sis5513_init_one,
	.हटाओ		= sis5513_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init sis5513_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&sis5513_pci_driver);
पूर्ण

अटल व्योम __निकास sis5513_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sis5513_pci_driver);
पूर्ण

module_init(sis5513_ide_init);
module_निकास(sis5513_ide_निकास);

MODULE_AUTHOR("Lionel Bouton, L C Chang, Andre Hedrick, Vojtech Pavlik");
MODULE_DESCRIPTION("PCI driver module for SIS IDE");
MODULE_LICENSE("GPL");
