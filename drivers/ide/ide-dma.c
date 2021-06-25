<शैली गुरु>
/*
 *  IDE DMA support (including IDE PCI BM-DMA).
 *
 *  Copyright (C) 1995-1998   Mark Lord
 *  Copyright (C) 1999-2000   Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2004, 2007  Bartlomiej Zolnierkiewicz
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 *  DMA is supported क्रम all IDE devices (disk drives, cdroms, tapes, floppies).
 */

/*
 *  Special Thanks to Mark क्रम his Six years of work.
 */

/*
 * Thanks to "Christopher J. Reimer" <reimer@करोe.carleton.ca> क्रम
 * fixing the problem with the BIOS on some Acer motherboards.
 *
 * Thanks to "Benoit Poulot-Cazajous" <poulot@chorus.fr> क्रम testing
 * "TX" chipset compatibility and क्रम providing patches क्रम the "TX" chipset.
 *
 * Thanks to Christian Brunner <chb@muc.de> क्रम taking a good first crack
 * at generic DMA -- his patches were referred to when preparing this code.
 *
 * Most importantly, thanks to Robert Bringman <rob@mars.trion.com>
 * क्रम supplying a Promise UDMA board & WD UDMA drive क्रम this work!
 */

#समावेश <linux/types.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ide.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>

अटल स्थिर काष्ठा drive_list_entry drive_whitelist[] = अणु
	अणु "Micropolis 2112A"	,       शून्य		पूर्ण,
	अणु "CONNER CTMA 4000"	,       शून्य		पूर्ण,
	अणु "CONNER CTT8000-A"	,       शून्य		पूर्ण,
	अणु "ST34342A"		,	शून्य		पूर्ण,
	अणु शून्य			,	शून्य		पूर्ण
पूर्ण;

अटल स्थिर काष्ठा drive_list_entry drive_blacklist[] = अणु
	अणु "WDC AC11000H"	,	शून्य 		पूर्ण,
	अणु "WDC AC22100H"	,	शून्य 		पूर्ण,
	अणु "WDC AC32500H"	,	शून्य 		पूर्ण,
	अणु "WDC AC33100H"	,	शून्य 		पूर्ण,
	अणु "WDC AC31600H"	,	शून्य 		पूर्ण,
	अणु "WDC AC32100H"	,	"24.09P07"	पूर्ण,
	अणु "WDC AC23200L"	,	"21.10N21"	पूर्ण,
	अणु "Compaq CRD-8241B"	,	शून्य 		पूर्ण,
	अणु "CRD-8400B"		,	शून्य 		पूर्ण,
	अणु "CRD-8480B",			शून्य 		पूर्ण,
	अणु "CRD-8482B",			शून्य 		पूर्ण,
	अणु "CRD-84"		,	शून्य 		पूर्ण,
	अणु "SanDisk SDP3B"	,	शून्य 		पूर्ण,
	अणु "SanDisk SDP3B-64"	,	शून्य 		पूर्ण,
	अणु "SANYO CD-ROM CRD"	,	शून्य 		पूर्ण,
	अणु "HITACHI CDR-8"	,	शून्य 		पूर्ण,
	अणु "HITACHI CDR-8335"	,	शून्य 		पूर्ण,
	अणु "HITACHI CDR-8435"	,	शून्य 		पूर्ण,
	अणु "Toshiba CD-ROM XM-6202B"	,	शून्य 		पूर्ण,
	अणु "TOSHIBA CD-ROM XM-1702BC",	शून्य 		पूर्ण,
	अणु "CD-532E-A"		,	शून्य 		पूर्ण,
	अणु "E-IDE CD-ROM CR-840",	शून्य 		पूर्ण,
	अणु "CD-ROM Drive/F5A",	शून्य 		पूर्ण,
	अणु "WPI CDD-820",		शून्य 		पूर्ण,
	अणु "SAMSUNG CD-ROM SC-148C",	शून्य 		पूर्ण,
	अणु "SAMSUNG CD-ROM SC",	शून्य 		पूर्ण,
	अणु "ATAPI CD-ROM DRIVE 40X MAXIMUM",	शून्य 		पूर्ण,
	अणु "_NEC DV5800A",               शून्य            पूर्ण,
	अणु "SAMSUNG CD-ROM SN-124",	"N001" पूर्ण,
	अणु "Seagate STT20000A",		शून्य  पूर्ण,
	अणु "CD-ROM CDR_U200",		"1.09" पूर्ण,
	अणु शून्य			,	शून्य		पूर्ण

पूर्ण;

/**
 *	ide_dma_पूर्णांकr	-	IDE DMA पूर्णांकerrupt handler
 *	@drive: the drive the पूर्णांकerrupt is क्रम
 *
 *	Handle an पूर्णांकerrupt completing a पढ़ो/ग_लिखो DMA transfer on an
 *	IDE device
 */

ide_startstop_t ide_dma_पूर्णांकr(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_cmd *cmd = &hwअगर->cmd;
	u8 stat = 0, dma_stat = 0;

	drive->रुकोing_क्रम_dma = 0;
	dma_stat = hwअगर->dma_ops->dma_end(drive);
	ide_dma_unmap_sg(drive, cmd);
	stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);

	अगर (OK_STAT(stat, DRIVE_READY, drive->bad_wstat | ATA_DRQ)) अणु
		अगर (!dma_stat) अणु
			अगर ((cmd->tf_flags & IDE_TFLAG_FS) == 0)
				ide_finish_cmd(drive, cmd, stat);
			अन्यथा
				ide_complete_rq(drive, BLK_STS_OK,
						blk_rq_sectors(cmd->rq) << 9);
			वापस ide_stopped;
		पूर्ण
		prपूर्णांकk(KERN_ERR "%s: %s: bad DMA status (0x%02x)\n",
			drive->name, __func__, dma_stat);
	पूर्ण
	वापस ide_error(drive, "dma_intr", stat);
पूर्ण

पूर्णांक ide_dma_good_drive(ide_drive_t *drive)
अणु
	वापस ide_in_drive_list(drive->id, drive_whitelist);
पूर्ण

/**
 *	ide_dma_map_sg	-	map IDE scatter gather क्रम DMA I/O
 *	@drive: the drive to map the DMA table क्रम
 *	@cmd: command
 *
 *	Perक्रमm the DMA mapping magic necessary to access the source or
 *	target buffers of a request via DMA.  The lower layers of the
 *	kernel provide the necessary cache management so that we can
 *	operate in a portable fashion.
 */

अटल पूर्णांक ide_dma_map_sg(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा scatterlist *sg = hwअगर->sg_table;
	पूर्णांक i;

	अगर (cmd->tf_flags & IDE_TFLAG_WRITE)
		cmd->sg_dma_direction = DMA_TO_DEVICE;
	अन्यथा
		cmd->sg_dma_direction = DMA_FROM_DEVICE;

	i = dma_map_sg(hwअगर->dev, sg, cmd->sg_nents, cmd->sg_dma_direction);
	अगर (i) अणु
		cmd->orig_sg_nents = cmd->sg_nents;
		cmd->sg_nents = i;
	पूर्ण

	वापस i;
पूर्ण

/**
 *	ide_dma_unmap_sg	-	clean up DMA mapping
 *	@drive: The drive to unmap
 *
 *	Tearकरोwn mappings after DMA has completed. This must be called
 *	after the completion of each use of ide_build_dmatable and beक्रमe
 *	the next use of ide_build_dmatable. Failure to करो so will cause
 *	an oops as only one mapping can be live क्रम each target at a given
 *	समय.
 */

व्योम ide_dma_unmap_sg(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	dma_unmap_sg(hwअगर->dev, hwअगर->sg_table, cmd->orig_sg_nents,
		     cmd->sg_dma_direction);
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_unmap_sg);

/**
 *	ide_dma_off_quietly	-	Generic DMA समाप्त
 *	@drive: drive to control
 *
 *	Turn off the current DMA on this IDE controller.
 */

व्योम ide_dma_off_quietly(ide_drive_t *drive)
अणु
	drive->dev_flags &= ~IDE_DFLAG_USING_DMA;

	drive->hwअगर->dma_ops->dma_host_set(drive, 0);
पूर्ण
EXPORT_SYMBOL(ide_dma_off_quietly);

/**
 *	ide_dma_off	-	disable DMA on a device
 *	@drive: drive to disable DMA on
 *
 *	Disable IDE DMA क्रम a device on this IDE controller.
 *	Inक्रमm the user that DMA has been disabled.
 */

व्योम ide_dma_off(ide_drive_t *drive)
अणु
	prपूर्णांकk(KERN_INFO "%s: DMA disabled\n", drive->name);
	ide_dma_off_quietly(drive);
पूर्ण
EXPORT_SYMBOL(ide_dma_off);

/**
 *	ide_dma_on		-	Enable DMA on a device
 *	@drive: drive to enable DMA on
 *
 *	Enable IDE DMA क्रम a device on this IDE controller.
 */

व्योम ide_dma_on(ide_drive_t *drive)
अणु
	drive->dev_flags |= IDE_DFLAG_USING_DMA;

	drive->hwअगर->dma_ops->dma_host_set(drive, 1);
पूर्ण

पूर्णांक __ide_dma_bad_drive(ide_drive_t *drive)
अणु
	u16 *id = drive->id;

	पूर्णांक blacklist = ide_in_drive_list(id, drive_blacklist);
	अगर (blacklist) अणु
		prपूर्णांकk(KERN_WARNING "%s: Disabling (U)DMA for %s (blacklisted)\n",
				    drive->name, (अक्षर *)&id[ATA_ID_PROD]);
		वापस blacklist;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__ide_dma_bad_drive);

अटल स्थिर u8 xfer_mode_bases[] = अणु
	XFER_UDMA_0,
	XFER_MW_DMA_0,
	XFER_SW_DMA_0,
पूर्ण;

अटल अचिन्हित पूर्णांक ide_get_mode_mask(ide_drive_t *drive, u8 base, u8 req_mode)
अणु
	u16 *id = drive->id;
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;
	अचिन्हित पूर्णांक mask = 0;

	चयन (base) अणु
	हाल XFER_UDMA_0:
		अगर ((id[ATA_ID_FIELD_VALID] & 4) == 0)
			अवरोध;
		mask = id[ATA_ID_UDMA_MODES];
		अगर (port_ops && port_ops->udma_filter)
			mask &= port_ops->udma_filter(drive);
		अन्यथा
			mask &= hwअगर->ultra_mask;

		/*
		 * aव्योम false cable warning from eighty_nपूर्णांकy_three()
		 */
		अगर (req_mode > XFER_UDMA_2) अणु
			अगर ((mask & 0x78) && (eighty_nपूर्णांकy_three(drive) == 0))
				mask &= 0x07;
		पूर्ण
		अवरोध;
	हाल XFER_MW_DMA_0:
		mask = id[ATA_ID_MWDMA_MODES];

		/* Also look क्रम the CF specअगरic MWDMA modes... */
		अगर (ata_id_is_cfa(id) && (id[ATA_ID_CFA_MODES] & 0x38)) अणु
			u8 mode = ((id[ATA_ID_CFA_MODES] & 0x38) >> 3) - 1;

			mask |= ((2 << mode) - 1) << 3;
		पूर्ण

		अगर (port_ops && port_ops->mdma_filter)
			mask &= port_ops->mdma_filter(drive);
		अन्यथा
			mask &= hwअगर->mwdma_mask;
		अवरोध;
	हाल XFER_SW_DMA_0:
		mask = id[ATA_ID_SWDMA_MODES];
		अगर (!(mask & ATA_SWDMA2) && (id[ATA_ID_OLD_DMA_MODES] >> 8)) अणु
			u8 mode = id[ATA_ID_OLD_DMA_MODES] >> 8;

			/*
			 * अगर the mode is valid convert it to the mask
			 * (the maximum allowed mode is XFER_SW_DMA_2)
			 */
			अगर (mode <= 2)
				mask = (2 << mode) - 1;
		पूर्ण
		mask &= hwअगर->swdma_mask;
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	वापस mask;
पूर्ण

/**
 *	ide_find_dma_mode	-	compute DMA speed
 *	@drive: IDE device
 *	@req_mode: requested mode
 *
 *	Checks the drive/host capabilities and finds the speed to use क्रम
 *	the DMA transfer.  The speed is then limited by the requested mode.
 *
 *	Returns 0 अगर the drive/host combination is incapable of DMA transfers
 *	or अगर the requested mode is not a DMA mode.
 */

u8 ide_find_dma_mode(ide_drive_t *drive, u8 req_mode)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित पूर्णांक mask;
	पूर्णांक x, i;
	u8 mode = 0;

	अगर (drive->media != ide_disk) अणु
		अगर (hwअगर->host_flags & IDE_HFLAG_NO_ATAPI_DMA)
			वापस 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(xfer_mode_bases); i++) अणु
		अगर (req_mode < xfer_mode_bases[i])
			जारी;
		mask = ide_get_mode_mask(drive, xfer_mode_bases[i], req_mode);
		x = fls(mask) - 1;
		अगर (x >= 0) अणु
			mode = xfer_mode_bases[i] + x;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (hwअगर->chipset == ide_acorn && mode == 0) अणु
		/*
		 * is this correct?
		 */
		अगर (ide_dma_good_drive(drive) &&
		    drive->id[ATA_ID_EIDE_DMA_TIME] < 150)
			mode = XFER_MW_DMA_1;
	पूर्ण

	mode = min(mode, req_mode);

	prपूर्णांकk(KERN_INFO "%s: %s mode selected\n", drive->name,
			  mode ? ide_xfer_verbose(mode) : "no DMA");

	वापस mode;
पूर्ण

अटल पूर्णांक ide_tune_dma(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 speed;

	अगर (ata_id_has_dma(drive->id) == 0 ||
	    (drive->dev_flags & IDE_DFLAG_NODMA))
		वापस 0;

	/* consult the list of known "bad" drives */
	अगर (__ide_dma_bad_drive(drive))
		वापस 0;

	अगर (hwअगर->host_flags & IDE_HFLAG_TRUST_BIOS_FOR_DMA)
		वापस config_drive_क्रम_dma(drive);

	speed = ide_max_dma_mode(drive);

	अगर (!speed)
		वापस 0;

	अगर (ide_set_dma_mode(drive, speed))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक ide_dma_check(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	अगर (ide_tune_dma(drive))
		वापस 0;

	/* TODO: always करो PIO fallback */
	अगर (hwअगर->host_flags & IDE_HFLAG_TRUST_BIOS_FOR_DMA)
		वापस -1;

	ide_set_max_pio(drive);

	वापस -1;
पूर्ण

पूर्णांक ide_set_dma(ide_drive_t *drive)
अणु
	पूर्णांक rc;

	/*
	 * Force DMAing क्रम the beginning of the check.
	 * Some chipsets appear to करो पूर्णांकeresting
	 * things, अगर not checked and cleared.
	 *   PARANOIA!!!
	 */
	ide_dma_off_quietly(drive);

	rc = ide_dma_check(drive);
	अगर (rc)
		वापस rc;

	ide_dma_on(drive);

	वापस 0;
पूर्ण

व्योम ide_check_dma_crc(ide_drive_t *drive)
अणु
	u8 mode;

	ide_dma_off_quietly(drive);
	drive->crc_count = 0;
	mode = drive->current_speed;
	/*
	 * Don't try non Ultra-DMA modes without iCRC's.  Force the
	 * device to PIO and make the user enable SWDMA/MWDMA modes.
	 */
	अगर (mode > XFER_UDMA_0 && mode <= XFER_UDMA_7)
		mode--;
	अन्यथा
		mode = XFER_PIO_4;
	ide_set_xfer_rate(drive, mode);
	अगर (drive->current_speed >= XFER_SW_DMA_0)
		ide_dma_on(drive);
पूर्ण

व्योम ide_dma_lost_irq(ide_drive_t *drive)
अणु
	prपूर्णांकk(KERN_ERR "%s: DMA interrupt recovery\n", drive->name);
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_lost_irq);

/*
 * un-busy the port etc, and clear any pending DMA status. we want to
 * retry the current request in pio mode instead of risking tossing it
 * all away
 */
ide_startstop_t ide_dma_समयout_retry(ide_drive_t *drive, पूर्णांक error)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_dma_ops *dma_ops = hwअगर->dma_ops;
	काष्ठा ide_cmd *cmd = &hwअगर->cmd;
	ide_startstop_t ret = ide_stopped;

	/*
	 * end current dma transaction
	 */

	अगर (error < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: DMA timeout error\n", drive->name);
		drive->रुकोing_क्रम_dma = 0;
		(व्योम)dma_ops->dma_end(drive);
		ide_dma_unmap_sg(drive, cmd);
		ret = ide_error(drive, "dma timeout error",
				hwअगर->tp_ops->पढ़ो_status(hwअगर));
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "%s: DMA timeout retry\n", drive->name);
		अगर (dma_ops->dma_clear)
			dma_ops->dma_clear(drive);
		prपूर्णांकk(KERN_ERR "%s: timeout waiting for DMA\n", drive->name);
		अगर (dma_ops->dma_test_irq(drive) == 0) अणु
			ide_dump_status(drive, "DMA timeout",
					hwअगर->tp_ops->पढ़ो_status(hwअगर));
			drive->रुकोing_क्रम_dma = 0;
			(व्योम)dma_ops->dma_end(drive);
			ide_dma_unmap_sg(drive, cmd);
		पूर्ण
	पूर्ण

	/*
	 * disable dma क्रम now, but remember that we did so because of
	 * a समयout -- we'll reenable after we finish this next request
	 * (or rather the first chunk of it) in pio.
	 */
	drive->dev_flags |= IDE_DFLAG_DMA_PIO_RETRY;
	drive->retry_pio++;
	ide_dma_off_quietly(drive);

	/*
	 * make sure request is sane
	 */
	अगर (hwअगर->rq)
		scsi_req(hwअगर->rq)->result = 0;
	वापस ret;
पूर्ण

व्योम ide_release_dma_engine(ide_hwअगर_t *hwअगर)
अणु
	अगर (hwअगर->dmatable_cpu) अणु
		पूर्णांक prd_size = hwअगर->prd_max_nents * hwअगर->prd_ent_size;

		dma_मुक्त_coherent(hwअगर->dev, prd_size,
				  hwअगर->dmatable_cpu, hwअगर->dmatable_dma);
		hwअगर->dmatable_cpu = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_release_dma_engine);

पूर्णांक ide_allocate_dma_engine(ide_hwअगर_t *hwअगर)
अणु
	पूर्णांक prd_size;

	अगर (hwअगर->prd_max_nents == 0)
		hwअगर->prd_max_nents = PRD_ENTRIES;
	अगर (hwअगर->prd_ent_size == 0)
		hwअगर->prd_ent_size = PRD_BYTES;

	prd_size = hwअगर->prd_max_nents * hwअगर->prd_ent_size;

	hwअगर->dmatable_cpu = dma_alloc_coherent(hwअगर->dev, prd_size,
						&hwअगर->dmatable_dma,
						GFP_ATOMIC);
	अगर (hwअगर->dmatable_cpu == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to allocate PRD table\n",
			hwअगर->name);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_allocate_dma_engine);

पूर्णांक ide_dma_prepare(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	स्थिर काष्ठा ide_dma_ops *dma_ops = drive->hwअगर->dma_ops;

	अगर ((drive->dev_flags & IDE_DFLAG_USING_DMA) == 0 ||
	    (dma_ops->dma_check && dma_ops->dma_check(drive, cmd)))
		जाओ out;
	ide_map_sg(drive, cmd);
	अगर (ide_dma_map_sg(drive, cmd) == 0)
		जाओ out_map;
	अगर (dma_ops->dma_setup(drive, cmd))
		जाओ out_dma_unmap;
	drive->रुकोing_क्रम_dma = 1;
	वापस 0;
out_dma_unmap:
	ide_dma_unmap_sg(drive, cmd);
out_map:
	ide_map_sg(drive, cmd);
out:
	वापस 1;
पूर्ण
