<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ide.h>
#समावेश <linux/delay.h>

अटल ide_startstop_t ide_ata_error(ide_drive_t *drive, काष्ठा request *rq,
				     u8 stat, u8 err)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	अगर ((stat & ATA_BUSY) ||
	    ((stat & ATA_DF) && (drive->dev_flags & IDE_DFLAG_NOWERR) == 0)) अणु
		/* other bits are useless when BUSY */
		scsi_req(rq)->result |= ERROR_RESET;
	पूर्ण अन्यथा अगर (stat & ATA_ERR) अणु
		/* err has dअगरferent meaning on cdrom and tape */
		अगर (err == ATA_ABORTED) अणु
			अगर ((drive->dev_flags & IDE_DFLAG_LBA) &&
			    /* some newer drives करोn't support ATA_CMD_INIT_DEV_PARAMS */
			    hwअगर->tp_ops->पढ़ो_status(hwअगर) == ATA_CMD_INIT_DEV_PARAMS)
				वापस ide_stopped;
		पूर्ण अन्यथा अगर ((err & BAD_CRC) == BAD_CRC) अणु
			/* UDMA crc error, just retry the operation */
			drive->crc_count++;
		पूर्ण अन्यथा अगर (err & (ATA_BBK | ATA_UNC)) अणु
			/* retries won't help these */
			scsi_req(rq)->result = ERROR_MAX;
		पूर्ण अन्यथा अगर (err & ATA_TRK0NF) अणु
			/* help it find track zero */
			scsi_req(rq)->result |= ERROR_RECAL;
		पूर्ण
	पूर्ण

	अगर ((stat & ATA_DRQ) && rq_data_dir(rq) == READ &&
	    (hwअगर->host_flags & IDE_HFLAG_ERROR_STOPS_FIFO) == 0) अणु
		पूर्णांक nsect = drive->mult_count ? drive->mult_count : 1;

		ide_pad_transfer(drive, READ, nsect * SECTOR_SIZE);
	पूर्ण

	अगर (scsi_req(rq)->result >= ERROR_MAX || blk_noretry_request(rq)) अणु
		ide_समाप्त_rq(drive, rq);
		वापस ide_stopped;
	पूर्ण

	अगर (hwअगर->tp_ops->पढ़ो_status(hwअगर) & (ATA_BUSY | ATA_DRQ))
		scsi_req(rq)->result |= ERROR_RESET;

	अगर ((scsi_req(rq)->result & ERROR_RESET) == ERROR_RESET) अणु
		++scsi_req(rq)->result;
		वापस ide_करो_reset(drive);
	पूर्ण

	अगर ((scsi_req(rq)->result & ERROR_RECAL) == ERROR_RECAL)
		drive->special_flags |= IDE_SFLAG_RECALIBRATE;

	++scsi_req(rq)->result;

	वापस ide_stopped;
पूर्ण

अटल ide_startstop_t ide_atapi_error(ide_drive_t *drive, काष्ठा request *rq,
				       u8 stat, u8 err)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	अगर ((stat & ATA_BUSY) ||
	    ((stat & ATA_DF) && (drive->dev_flags & IDE_DFLAG_NOWERR) == 0)) अणु
		/* other bits are useless when BUSY */
		scsi_req(rq)->result |= ERROR_RESET;
	पूर्ण अन्यथा अणु
		/* add decoding error stuff */
	पूर्ण

	अगर (hwअगर->tp_ops->पढ़ो_status(hwअगर) & (ATA_BUSY | ATA_DRQ))
		/* क्रमce an पात */
		hwअगर->tp_ops->exec_command(hwअगर, ATA_CMD_IDLEIMMEDIATE);

	अगर (scsi_req(rq)->result >= ERROR_MAX) अणु
		ide_समाप्त_rq(drive, rq);
	पूर्ण अन्यथा अणु
		अगर ((scsi_req(rq)->result & ERROR_RESET) == ERROR_RESET) अणु
			++scsi_req(rq)->result;
			वापस ide_करो_reset(drive);
		पूर्ण
		++scsi_req(rq)->result;
	पूर्ण

	वापस ide_stopped;
पूर्ण

अटल ide_startstop_t __ide_error(ide_drive_t *drive, काष्ठा request *rq,
				   u8 stat, u8 err)
अणु
	अगर (drive->media == ide_disk)
		वापस ide_ata_error(drive, rq, stat, err);
	वापस ide_atapi_error(drive, rq, stat, err);
पूर्ण

/**
 *	ide_error	-	handle an error on the IDE
 *	@drive: drive the error occurred on
 *	@msg: message to report
 *	@stat: status bits
 *
 *	ide_error() takes action based on the error वापसed by the drive.
 *	For normal I/O that may well include retries. We deal with
 *	both new-style (taskfile) and old style command handling here.
 *	In the हाल of taskfile command handling there is work left to
 *	करो
 */

ide_startstop_t ide_error(ide_drive_t *drive, स्थिर अक्षर *msg, u8 stat)
अणु
	काष्ठा request *rq;
	u8 err;

	err = ide_dump_status(drive, msg, stat);

	rq = drive->hwअगर->rq;
	अगर (rq == शून्य)
		वापस ide_stopped;

	/* retry only "normal" I/O: */
	अगर (blk_rq_is_passthrough(rq)) अणु
		अगर (ata_taskfile_request(rq)) अणु
			काष्ठा ide_cmd *cmd = ide_req(rq)->special;

			अगर (cmd)
				ide_complete_cmd(drive, cmd, stat, err);
		पूर्ण अन्यथा अगर (ata_pm_request(rq)) अणु
			scsi_req(rq)->result = 1;
			ide_complete_pm_rq(drive, rq);
			वापस ide_stopped;
		पूर्ण
		scsi_req(rq)->result = err;
		ide_complete_rq(drive, err ? BLK_STS_IOERR : BLK_STS_OK, blk_rq_bytes(rq));
		वापस ide_stopped;
	पूर्ण

	वापस __ide_error(drive, rq, stat, err);
पूर्ण
EXPORT_SYMBOL_GPL(ide_error);

अटल अंतरभूत व्योम ide_complete_drive_reset(ide_drive_t *drive, blk_status_t err)
अणु
	काष्ठा request *rq = drive->hwअगर->rq;

	अगर (rq && ata_misc_request(rq) &&
	    scsi_req(rq)->cmd[0] == REQ_DRIVE_RESET) अणु
		अगर (err <= 0 && scsi_req(rq)->result == 0)
			scsi_req(rq)->result = -EIO;
		ide_complete_rq(drive, err, blk_rq_bytes(rq));
	पूर्ण
पूर्ण

/* needed below */
अटल ide_startstop_t करो_reset1(ide_drive_t *, पूर्णांक);

/*
 * atapi_reset_pollfunc() माला_लो invoked to poll the पूर्णांकerface क्रम completion
 * every 50ms during an atapi drive reset operation.  If the drive has not yet
 * responded, and we have not yet hit our maximum रुकोing समय, then the समयr
 * is restarted क्रम another 50ms.
 */
अटल ide_startstop_t atapi_reset_pollfunc(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	u8 stat;

	tp_ops->dev_select(drive);
	udelay(10);
	stat = tp_ops->पढ़ो_status(hwअगर);

	अगर (OK_STAT(stat, 0, ATA_BUSY))
		prपूर्णांकk(KERN_INFO "%s: ATAPI reset complete\n", drive->name);
	अन्यथा अणु
		अगर (समय_beक्रमe(jअगरfies, hwअगर->poll_समयout)) अणु
			ide_set_handler(drive, &atapi_reset_pollfunc, HZ/20);
			/* जारी polling */
			वापस ide_started;
		पूर्ण
		/* end of polling */
		hwअगर->polling = 0;
		prपूर्णांकk(KERN_ERR "%s: ATAPI reset timed-out, status=0x%02x\n",
			drive->name, stat);
		/* करो it the old fashioned way */
		वापस करो_reset1(drive, 1);
	पूर्ण
	/* करोne polling */
	hwअगर->polling = 0;
	ide_complete_drive_reset(drive, BLK_STS_OK);
	वापस ide_stopped;
पूर्ण

अटल व्योम ide_reset_report_error(ide_hwअगर_t *hwअगर, u8 err)
अणु
	अटल स्थिर अक्षर *err_master_vals[] =
		अणु शून्य, "passed", "formatter device error",
		  "sector buffer error", "ECC circuitry error",
		  "controlling MPU error" पूर्ण;

	u8 err_master = err & 0x7f;

	prपूर्णांकk(KERN_ERR "%s: reset: master: ", hwअगर->name);
	अगर (err_master && err_master < 6)
		prपूर्णांकk(KERN_CONT "%s", err_master_vals[err_master]);
	अन्यथा
		prपूर्णांकk(KERN_CONT "error (0x%02x?)", err);
	अगर (err & 0x80)
		prपूर्णांकk(KERN_CONT "; slave: failed");
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

/*
 * reset_pollfunc() माला_लो invoked to poll the पूर्णांकerface क्रम completion every 50ms
 * during an ide reset operation. If the drives have not yet responded,
 * and we have not yet hit our maximum रुकोing समय, then the समयr is restarted
 * क्रम another 50ms.
 */
अटल ide_startstop_t reset_pollfunc(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;
	u8 पंचांगp;
	blk_status_t err = BLK_STS_OK;

	अगर (port_ops && port_ops->reset_poll) अणु
		err = port_ops->reset_poll(drive);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: host reset_poll failure for %s.\n",
				hwअगर->name, drive->name);
			जाओ out;
		पूर्ण
	पूर्ण

	पंचांगp = hwअगर->tp_ops->पढ़ो_status(hwअगर);

	अगर (!OK_STAT(पंचांगp, 0, ATA_BUSY)) अणु
		अगर (समय_beक्रमe(jअगरfies, hwअगर->poll_समयout)) अणु
			ide_set_handler(drive, &reset_pollfunc, HZ/20);
			/* जारी polling */
			वापस ide_started;
		पूर्ण
		prपूर्णांकk(KERN_ERR "%s: reset timed-out, status=0x%02x\n",
			hwअगर->name, पंचांगp);
		drive->failures++;
		err = BLK_STS_IOERR;
	पूर्ण अन्यथा  अणु
		पंचांगp = ide_पढ़ो_error(drive);

		अगर (पंचांगp == 1) अणु
			prपूर्णांकk(KERN_INFO "%s: reset: success\n", hwअगर->name);
			drive->failures = 0;
		पूर्ण अन्यथा अणु
			ide_reset_report_error(hwअगर, पंचांगp);
			drive->failures++;
			err = BLK_STS_IOERR;
		पूर्ण
	पूर्ण
out:
	hwअगर->polling = 0;	/* करोne polling */
	ide_complete_drive_reset(drive, err);
	वापस ide_stopped;
पूर्ण

अटल व्योम ide_disk_pre_reset(ide_drive_t *drive)
अणु
	पूर्णांक legacy = (drive->id[ATA_ID_CFS_ENABLE_2] & 0x0400) ? 0 : 1;

	drive->special_flags =
		legacy ? (IDE_SFLAG_SET_GEOMETRY | IDE_SFLAG_RECALIBRATE) : 0;

	drive->mult_count = 0;
	drive->dev_flags &= ~IDE_DFLAG_PARKED;

	अगर ((drive->dev_flags & IDE_DFLAG_KEEP_SETTINGS) == 0 &&
	    (drive->dev_flags & IDE_DFLAG_USING_DMA) == 0)
		drive->mult_req = 0;

	अगर (drive->mult_req != drive->mult_count)
		drive->special_flags |= IDE_SFLAG_SET_MULTMODE;
पूर्ण

अटल व्योम pre_reset(ide_drive_t *drive)
अणु
	स्थिर काष्ठा ide_port_ops *port_ops = drive->hwअगर->port_ops;

	अगर (drive->media == ide_disk)
		ide_disk_pre_reset(drive);
	अन्यथा
		drive->dev_flags |= IDE_DFLAG_POST_RESET;

	अगर (drive->dev_flags & IDE_DFLAG_USING_DMA) अणु
		अगर (drive->crc_count)
			ide_check_dma_crc(drive);
		अन्यथा
			ide_dma_off(drive);
	पूर्ण

	अगर ((drive->dev_flags & IDE_DFLAG_KEEP_SETTINGS) == 0) अणु
		अगर ((drive->dev_flags & IDE_DFLAG_USING_DMA) == 0) अणु
			drive->dev_flags &= ~IDE_DFLAG_UNMASK;
			drive->io_32bit = 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (port_ops && port_ops->pre_reset)
		port_ops->pre_reset(drive);

	अगर (drive->current_speed != 0xff)
		drive->desired_speed = drive->current_speed;
	drive->current_speed = 0xff;
पूर्ण

/*
 * करो_reset1() attempts to recover a confused drive by resetting it.
 * Unक्रमtunately, resetting a disk drive actually resets all devices on
 * the same पूर्णांकerface, so it can really be thought of as resetting the
 * पूर्णांकerface rather than resetting the drive.
 *
 * ATAPI devices have their own reset mechanism which allows them to be
 * inभागidually reset without clobbering other devices on the same पूर्णांकerface.
 *
 * Unक्रमtunately, the IDE पूर्णांकerface करोes not generate an पूर्णांकerrupt to let
 * us know when the reset operation has finished, so we must poll क्रम this.
 * Equally poor, though, is the fact that this may a very दीर्घ समय to complete,
 * (up to 30 seconds worstहाल).  So, instead of busy-रुकोing here क्रम it,
 * we set a समयr to poll at 50ms पूर्णांकervals.
 */
अटल ide_startstop_t करो_reset1(ide_drive_t *drive, पूर्णांक करो_not_try_atapi)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	स्थिर काष्ठा ide_port_ops *port_ops;
	ide_drive_t *tdrive;
	अचिन्हित दीर्घ flags, समयout;
	पूर्णांक i;
	DEFINE_WAIT(रुको);

	spin_lock_irqsave(&hwअगर->lock, flags);

	/* We must not reset with running handlers */
	BUG_ON(hwअगर->handler != शून्य);

	/* For an ATAPI device, first try an ATAPI SRST. */
	अगर (drive->media != ide_disk && !करो_not_try_atapi) अणु
		pre_reset(drive);
		tp_ops->dev_select(drive);
		udelay(20);
		tp_ops->exec_command(hwअगर, ATA_CMD_DEV_RESET);
		ndelay(400);
		hwअगर->poll_समयout = jअगरfies + WAIT_WORSTCASE;
		hwअगर->polling = 1;
		__ide_set_handler(drive, &atapi_reset_pollfunc, HZ/20);
		spin_unlock_irqrestore(&hwअगर->lock, flags);
		वापस ide_started;
	पूर्ण

	/* We must not disturb devices in the IDE_DFLAG_PARKED state. */
	करो अणु
		अचिन्हित दीर्घ now;

		prepare_to_रुको(&ide_park_wq, &रुको, TASK_UNINTERRUPTIBLE);
		समयout = jअगरfies;
		ide_port_क्रम_each_present_dev(i, tdrive, hwअगर) अणु
			अगर ((tdrive->dev_flags & IDE_DFLAG_PARKED) &&
			    समय_after(tdrive->sleep, समयout))
				समयout = tdrive->sleep;
		पूर्ण

		now = jअगरfies;
		अगर (समय_beक्रमe_eq(समयout, now))
			अवरोध;

		spin_unlock_irqrestore(&hwअगर->lock, flags);
		समयout = schedule_समयout_unपूर्णांकerruptible(समयout - now);
		spin_lock_irqsave(&hwअगर->lock, flags);
	पूर्ण जबतक (समयout);
	finish_रुको(&ide_park_wq, &रुको);

	/*
	 * First, reset any device state data we were मुख्यtaining
	 * क्रम any of the drives on this पूर्णांकerface.
	 */
	ide_port_क्रम_each_dev(i, tdrive, hwअगर)
		pre_reset(tdrive);

	अगर (io_ports->ctl_addr == 0) अणु
		spin_unlock_irqrestore(&hwअगर->lock, flags);
		ide_complete_drive_reset(drive, BLK_STS_IOERR);
		वापस ide_stopped;
	पूर्ण

	/*
	 * Note that we also set nIEN जबतक resetting the device,
	 * to mask unwanted पूर्णांकerrupts from the पूर्णांकerface during the reset.
	 * However, due to the design of PC hardware, this will cause an
	 * immediate पूर्णांकerrupt due to the edge transition it produces.
	 * This single पूर्णांकerrupt gives us a "fast poll" क्रम drives that
	 * recover from reset very quickly, saving us the first 50ms रुको समय.
	 */
	/* set SRST and nIEN */
	tp_ops->ग_लिखो_devctl(hwअगर, ATA_SRST | ATA_NIEN | ATA_DEVCTL_OBS);
	/* more than enough समय */
	udelay(10);
	/* clear SRST, leave nIEN (unless device is on the quirk list) */
	tp_ops->ग_लिखो_devctl(hwअगर,
		((drive->dev_flags & IDE_DFLAG_NIEN_QUIRK) ? 0 : ATA_NIEN) |
		 ATA_DEVCTL_OBS);
	/* more than enough समय */
	udelay(10);
	hwअगर->poll_समयout = jअगरfies + WAIT_WORSTCASE;
	hwअगर->polling = 1;
	__ide_set_handler(drive, &reset_pollfunc, HZ/20);

	/*
	 * Some weird controller like resetting themselves to a strange
	 * state when the disks are reset this way. At least, the Winbond
	 * 553 करोcumentation says that
	 */
	port_ops = hwअगर->port_ops;
	अगर (port_ops && port_ops->resetproc)
		port_ops->resetproc(drive);

	spin_unlock_irqrestore(&hwअगर->lock, flags);
	वापस ide_started;
पूर्ण

/*
 * ide_करो_reset() is the entry poपूर्णांक to the drive/पूर्णांकerface reset code.
 */

ide_startstop_t ide_करो_reset(ide_drive_t *drive)
अणु
	वापस करो_reset1(drive, 0);
पूर्ण
EXPORT_SYMBOL(ide_करो_reset);
