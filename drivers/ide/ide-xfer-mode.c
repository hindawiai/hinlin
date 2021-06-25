<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ide.h>
#समावेश <linux/bitops.h>

अटल स्थिर अक्षर *udma_str[] =
	 अणु "UDMA/16", "UDMA/25",  "UDMA/33",  "UDMA/44",
	   "UDMA/66", "UDMA/100", "UDMA/133", "UDMA7" पूर्ण;
अटल स्थिर अक्षर *mwdma_str[] =
	अणु "MWDMA0", "MWDMA1", "MWDMA2", "MWDMA3", "MWDMA4" पूर्ण;
अटल स्थिर अक्षर *swdma_str[] =
	अणु "SWDMA0", "SWDMA1", "SWDMA2" पूर्ण;
अटल स्थिर अक्षर *pio_str[] =
	अणु "PIO0", "PIO1", "PIO2", "PIO3", "PIO4", "PIO5", "PIO6" पूर्ण;

/**
 *	ide_xfer_verbose	-	वापस IDE mode names
 *	@mode: transfer mode
 *
 *	Returns a स्थिरant string giving the name of the mode
 *	requested.
 */

स्थिर अक्षर *ide_xfer_verbose(u8 mode)
अणु
	स्थिर अक्षर *s;
	u8 i = mode & 0xf;

	अगर (mode >= XFER_UDMA_0 && mode <= XFER_UDMA_7)
		s = udma_str[i];
	अन्यथा अगर (mode >= XFER_MW_DMA_0 && mode <= XFER_MW_DMA_4)
		s = mwdma_str[i];
	अन्यथा अगर (mode >= XFER_SW_DMA_0 && mode <= XFER_SW_DMA_2)
		s = swdma_str[i];
	अन्यथा अगर (mode >= XFER_PIO_0 && mode <= XFER_PIO_6)
		s = pio_str[i & 0x7];
	अन्यथा अगर (mode == XFER_PIO_SLOW)
		s = "PIO SLOW";
	अन्यथा
		s = "XFER ERROR";

	वापस s;
पूर्ण
EXPORT_SYMBOL(ide_xfer_verbose);

/**
 *	ide_get_best_pio_mode	-	get PIO mode from drive
 *	@drive: drive to consider
 *	@mode_wanted: preferred mode
 *	@max_mode: highest allowed mode
 *
 *	This routine वापसs the recommended PIO settings क्रम a given drive,
 *	based on the drive->id inक्रमmation and the ide_pio_blacklist[].
 *
 *	Drive PIO mode is स्वतः-selected अगर 255 is passed as mode_wanted.
 *	This is used by most chipset support modules when "auto-tuning".
 */

अटल u8 ide_get_best_pio_mode(ide_drive_t *drive, u8 mode_wanted, u8 max_mode)
अणु
	u16 *id = drive->id;
	पूर्णांक pio_mode = -1, overridden = 0;

	अगर (mode_wanted != 255)
		वापस min_t(u8, mode_wanted, max_mode);

	अगर ((drive->hwअगर->host_flags & IDE_HFLAG_PIO_NO_BLACKLIST) == 0)
		pio_mode = ide_scan_pio_blacklist((अक्षर *)&id[ATA_ID_PROD]);

	अगर (pio_mode != -1) अणु
		prपूर्णांकk(KERN_INFO "%s: is on PIO blacklist\n", drive->name);
	पूर्ण अन्यथा अणु
		pio_mode = id[ATA_ID_OLD_PIO_MODES] >> 8;
		अगर (pio_mode > 2) अणु	/* 2 is maximum allowed tPIO value */
			pio_mode = 2;
			overridden = 1;
		पूर्ण

		अगर (id[ATA_ID_FIELD_VALID] & 2) अणु	      /* ATA2? */
			अगर (ata_id_is_cfa(id) && (id[ATA_ID_CFA_MODES] & 7))
				pio_mode = 4 + min_t(पूर्णांक, 2,
						     id[ATA_ID_CFA_MODES] & 7);
			अन्यथा अगर (ata_id_has_iordy(id)) अणु
				अगर (id[ATA_ID_PIO_MODES] & 7) अणु
					overridden = 0;
					अगर (id[ATA_ID_PIO_MODES] & 4)
						pio_mode = 5;
					अन्यथा अगर (id[ATA_ID_PIO_MODES] & 2)
						pio_mode = 4;
					अन्यथा
						pio_mode = 3;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (overridden)
			prपूर्णांकk(KERN_INFO "%s: tPIO > 2, assuming tPIO = 2\n",
					 drive->name);
	पूर्ण

	अगर (pio_mode > max_mode)
		pio_mode = max_mode;

	वापस pio_mode;
पूर्ण

पूर्णांक ide_pio_need_iordy(ide_drive_t *drive, स्थिर u8 pio)
अणु
	/*
	 * IORDY may lead to controller lock up on certain controllers
	 * अगर the port is not occupied.
	 */
	अगर (pio == 0 && (drive->hwअगर->port_flags & IDE_PFLAG_PROBING))
		वापस 0;
	वापस ata_id_pio_need_iordy(drive->id, pio);
पूर्ण
EXPORT_SYMBOL_GPL(ide_pio_need_iordy);

पूर्णांक ide_set_pio_mode(ide_drive_t *drive, स्थिर u8 mode)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;

	अगर (hwअगर->host_flags & IDE_HFLAG_NO_SET_MODE)
		वापस 0;

	अगर (port_ops == शून्य || port_ops->set_pio_mode == शून्य)
		वापस -1;

	/*
	 * TODO: temporary hack क्रम some legacy host drivers that didn't
	 * set transfer mode on the device in ->set_pio_mode method...
	 */
	अगर (port_ops->set_dma_mode == शून्य) अणु
		drive->pio_mode = mode;
		port_ops->set_pio_mode(hwअगर, drive);
		वापस 0;
	पूर्ण

	अगर (hwअगर->host_flags & IDE_HFLAG_POST_SET_MODE) अणु
		अगर (ide_config_drive_speed(drive, mode))
			वापस -1;
		drive->pio_mode = mode;
		port_ops->set_pio_mode(hwअगर, drive);
		वापस 0;
	पूर्ण अन्यथा अणु
		drive->pio_mode = mode;
		port_ops->set_pio_mode(hwअगर, drive);
		वापस ide_config_drive_speed(drive, mode);
	पूर्ण
पूर्ण

पूर्णांक ide_set_dma_mode(ide_drive_t *drive, स्थिर u8 mode)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;

	अगर (hwअगर->host_flags & IDE_HFLAG_NO_SET_MODE)
		वापस 0;

	अगर (port_ops == शून्य || port_ops->set_dma_mode == शून्य)
		वापस -1;

	अगर (hwअगर->host_flags & IDE_HFLAG_POST_SET_MODE) अणु
		अगर (ide_config_drive_speed(drive, mode))
			वापस -1;
		drive->dma_mode = mode;
		port_ops->set_dma_mode(hwअगर, drive);
		वापस 0;
	पूर्ण अन्यथा अणु
		drive->dma_mode = mode;
		port_ops->set_dma_mode(hwअगर, drive);
		वापस ide_config_drive_speed(drive, mode);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_set_dma_mode);

/* req_pio == "255" क्रम स्वतः-tune */
व्योम ide_set_pio(ide_drive_t *drive, u8 req_pio)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;
	u8 host_pio, pio;

	अगर (port_ops == शून्य || port_ops->set_pio_mode == शून्य ||
	    (hwअगर->host_flags & IDE_HFLAG_NO_SET_MODE))
		वापस;

	BUG_ON(hwअगर->pio_mask == 0x00);

	host_pio = fls(hwअगर->pio_mask) - 1;

	pio = ide_get_best_pio_mode(drive, req_pio, host_pio);

	/*
	 * TODO:
	 * - report device max PIO mode
	 * - check req_pio != 255 against device max PIO mode
	 */
	prपूर्णांकk(KERN_DEBUG "%s: host max PIO%d wanted PIO%d%s selected PIO%d\n",
			  drive->name, host_pio, req_pio,
			  req_pio == 255 ? "(auto-tune)" : "", pio);

	(व्योम)ide_set_pio_mode(drive, XFER_PIO_0 + pio);
पूर्ण
EXPORT_SYMBOL_GPL(ide_set_pio);

/**
 *	ide_rate_filter		-	filter transfer mode
 *	@drive: IDE device
 *	@speed: desired speed
 *
 *	Given the available transfer modes this function वापसs
 *	the best available speed at or below the speed requested.
 *
 *	TODO: check device PIO capabilities
 */

अटल u8 ide_rate_filter(ide_drive_t *drive, u8 speed)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 mode = ide_find_dma_mode(drive, speed);

	अगर (mode == 0) अणु
		अगर (hwअगर->pio_mask)
			mode = fls(hwअगर->pio_mask) - 1 + XFER_PIO_0;
		अन्यथा
			mode = XFER_PIO_4;
	पूर्ण

/*	prपूर्णांकk("%s: mode 0x%02x, speed 0x%02x\n", __func__, mode, speed); */

	वापस min(speed, mode);
पूर्ण

/**
 *	ide_set_xfer_rate	-	set transfer rate
 *	@drive: drive to set
 *	@rate: speed to attempt to set
 *
 *	General helper क्रम setting the speed of an IDE device. This
 *	function knows about user enक्रमced limits from the configuration
 *	which ->set_pio_mode/->set_dma_mode करोes not.
 */

पूर्णांक ide_set_xfer_rate(ide_drive_t *drive, u8 rate)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;

	अगर (port_ops == शून्य || port_ops->set_dma_mode == शून्य ||
	    (hwअगर->host_flags & IDE_HFLAG_NO_SET_MODE))
		वापस -1;

	rate = ide_rate_filter(drive, rate);

	BUG_ON(rate < XFER_PIO_0);

	अगर (rate >= XFER_PIO_0 && rate <= XFER_PIO_6)
		वापस ide_set_pio_mode(drive, rate);

	वापस ide_set_dma_mode(drive, rate);
पूर्ण
