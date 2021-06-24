<शैली गुरु>
/*
 * ATAPI CD-ROM driver.
 *
 * Copyright (C) 1994-1996   Scott Snyder <snyder@fnald0.fnal.gov>
 * Copyright (C) 1996-1998   Erik Andersen <andersee@debian.org>
 * Copyright (C) 1998-2000   Jens Axboe <axboe@suse.de>
 * Copyright (C) 2005, 2007-2009  Bartlomiej Zolnierkiewicz
 *
 * May be copied or modअगरied under the terms of the GNU General Public
 * License.  See linux/COPYING क्रम more inक्रमmation.
 *
 * See Documentation/cdrom/ide-cd.rst क्रम usage inक्रमmation.
 *
 * Suggestions are welcome. Patches that work are more welcome though. ;-)
 *
 * Documentation:
 *	Mt. Fuji (SFF8090 version 4) and ATAPI (SFF-8020i rev 2.6) standards.
 *
 * For historical changelog please see:
 *	Documentation/ide/ChangeLog.ide-cd.1994-2004
 */

#घोषणा DRV_NAME "ide-cd"
#घोषणा PFX DRV_NAME ": "

#घोषणा IDECD_VERSION "5.00"

#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cdrom.h>
#समावेश <linux/ide.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/bcd.h>

/* For SCSI -> ATAPI command conversion */
#समावेश <scsi/scsi.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ide-cd.h"

अटल DEFINE_MUTEX(ide_cd_mutex);
अटल DEFINE_MUTEX(idecd_ref_mutex);

अटल व्योम ide_cd_release(काष्ठा device *);

अटल काष्ठा cdrom_info *ide_cd_get(काष्ठा gendisk *disk)
अणु
	काष्ठा cdrom_info *cd = शून्य;

	mutex_lock(&idecd_ref_mutex);
	cd = ide_drv_g(disk, cdrom_info);
	अगर (cd) अणु
		अगर (ide_device_get(cd->drive))
			cd = शून्य;
		अन्यथा
			get_device(&cd->dev);

	पूर्ण
	mutex_unlock(&idecd_ref_mutex);
	वापस cd;
पूर्ण

अटल व्योम ide_cd_put(काष्ठा cdrom_info *cd)
अणु
	ide_drive_t *drive = cd->drive;

	mutex_lock(&idecd_ref_mutex);
	put_device(&cd->dev);
	ide_device_put(drive);
	mutex_unlock(&idecd_ref_mutex);
पूर्ण

/*
 * Generic packet command support and error handling routines.
 */

/* Mark that we've seen a media change and invalidate our पूर्णांकernal buffers. */
अटल व्योम cdrom_saw_media_change(ide_drive_t *drive)
अणु
	drive->dev_flags |= IDE_DFLAG_MEDIA_CHANGED;
	drive->atapi_flags &= ~IDE_AFLAG_TOC_VALID;
पूर्ण

अटल पूर्णांक cdrom_log_sense(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा request_sense *sense = &drive->sense_data;
	पूर्णांक log = 0;

	अगर (!sense || !rq || (rq->rq_flags & RQF_QUIET))
		वापस 0;

	ide_debug_log(IDE_DBG_SENSE, "sense_key: 0x%x", sense->sense_key);

	चयन (sense->sense_key) अणु
	हाल NO_SENSE:
	हाल RECOVERED_ERROR:
		अवरोध;
	हाल NOT_READY:
		/*
		 * करोn't care about tray state messages क्रम e.g. capacity
		 * commands or in-progress or becoming पढ़ोy
		 */
		अगर (sense->asc == 0x3a || sense->asc == 0x04)
			अवरोध;
		log = 1;
		अवरोध;
	हाल ILLEGAL_REQUEST:
		/*
		 * करोn't log START_STOP unit with LoEj set, since we cannot
		 * reliably check अगर drive can स्वतः-बंद
		 */
		अगर (scsi_req(rq)->cmd[0] == GPCMD_START_STOP_UNIT && sense->asc == 0x24)
			अवरोध;
		log = 1;
		अवरोध;
	हाल UNIT_ATTENTION:
		/*
		 * Make good and sure we've seen this potential media change.
		 * Some drives (i.e. Creative) fail to present the correct sense
		 * key in the error रेजिस्टर.
		 */
		cdrom_saw_media_change(drive);
		अवरोध;
	शेष:
		log = 1;
		अवरोध;
	पूर्ण
	वापस log;
पूर्ण

अटल व्योम cdrom_analyze_sense_data(ide_drive_t *drive,
				     काष्ठा request *failed_command)
अणु
	काष्ठा request_sense *sense = &drive->sense_data;
	काष्ठा cdrom_info *info = drive->driver_data;
	अचिन्हित दीर्घ sector;
	अचिन्हित दीर्घ bio_sectors;

	ide_debug_log(IDE_DBG_SENSE, "error_code: 0x%x, sense_key: 0x%x",
				     sense->error_code, sense->sense_key);

	अगर (failed_command)
		ide_debug_log(IDE_DBG_SENSE, "failed cmd: 0x%x",
					     failed_command->cmd[0]);

	अगर (!cdrom_log_sense(drive, failed_command))
		वापस;

	/*
	 * If a पढ़ो toc is executed क्रम a CD-R or CD-RW medium where the first
	 * toc has not been recorded yet, it will fail with 05/24/00 (which is a
	 * confusing error)
	 */
	अगर (failed_command && scsi_req(failed_command)->cmd[0] == GPCMD_READ_TOC_PMA_ATIP)
		अगर (sense->sense_key == 0x05 && sense->asc == 0x24)
			वापस;

	/* current error */
	अगर (sense->error_code == 0x70) अणु
		चयन (sense->sense_key) अणु
		हाल MEDIUM_ERROR:
		हाल VOLUME_OVERFLOW:
		हाल ILLEGAL_REQUEST:
			अगर (!sense->valid)
				अवरोध;
			अगर (failed_command == शून्य ||
			    blk_rq_is_passthrough(failed_command))
				अवरोध;
			sector = (sense->inक्रमmation[0] << 24) |
				 (sense->inक्रमmation[1] << 16) |
				 (sense->inक्रमmation[2] <<  8) |
				 (sense->inक्रमmation[3]);

			अगर (queue_logical_block_size(drive->queue) == 2048)
				/* device sector size is 2K */
				sector <<= 2;

			bio_sectors = max(bio_sectors(failed_command->bio), 4U);
			sector &= ~(bio_sectors - 1);

			/*
			 * The SCSI specअगरication allows क्रम the value
			 * वापसed by READ CAPACITY to be up to 75 2K
			 * sectors past the last पढ़ोable block.
			 * Thereक्रमe, अगर we hit a medium error within the
			 * last 75 2K sectors, we decrease the saved size
			 * value.
			 */
			अगर (sector < get_capacity(info->disk) &&
			    drive->probed_capacity - sector < 4 * 75)
				set_capacity(info->disk, sector);
		पूर्ण
	पूर्ण

	ide_cd_log_error(drive->name, failed_command, sense);
पूर्ण

अटल व्योम ide_cd_complete_failed_rq(ide_drive_t *drive, काष्ठा request *rq)
अणु
	/*
	 * For ATA_PRIV_SENSE, "ide_req(rq)->special" poपूर्णांकs to the original
	 * failed request.  Also, the sense data should be पढ़ो
	 * directly from rq which might be dअगरferent from the original
	 * sense buffer अगर it got copied during mapping.
	 */
	काष्ठा request *failed = ide_req(rq)->special;
	व्योम *sense = bio_data(rq->bio);

	अगर (failed) अणु
		/*
		 * Sense is always पढ़ो पूर्णांकo drive->sense_data, copy back to the
		 * original request.
		 */
		स_नकल(scsi_req(failed)->sense, sense, 18);
		scsi_req(failed)->sense_len = scsi_req(rq)->sense_len;
		cdrom_analyze_sense_data(drive, failed);

		अगर (ide_end_rq(drive, failed, BLK_STS_IOERR, blk_rq_bytes(failed)))
			BUG();
	पूर्ण अन्यथा
		cdrom_analyze_sense_data(drive, शून्य);
पूर्ण


/*
 * Allow the drive 5 seconds to recover; some devices will वापस NOT_READY
 * जबतक flushing data from cache.
 *
 * वापसs: 0 failed (ग_लिखो समयout expired)
 *	    1 success
 */
अटल पूर्णांक ide_cd_breathe(ide_drive_t *drive, काष्ठा request *rq)
अणु

	काष्ठा cdrom_info *info = drive->driver_data;

	अगर (!scsi_req(rq)->result)
		info->ग_लिखो_समयout = jअगरfies +	ATAPI_WAIT_WRITE_BUSY;

	scsi_req(rq)->result = 1;

	अगर (समय_after(jअगरfies, info->ग_लिखो_समयout))
		वापस 0;
	अन्यथा अणु
		/*
		 * take a breather
		 */
		blk_mq_requeue_request(rq, false);
		blk_mq_delay_kick_requeue_list(drive->queue, 1);
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम ide_cd_मुक्त_sense(ide_drive_t *drive)
अणु
	अगर (!drive->sense_rq)
		वापस;

	blk_mq_मुक्त_request(drive->sense_rq);
	drive->sense_rq = शून्य;
	drive->sense_rq_armed = false;
पूर्ण

/**
 * Returns:
 * 0: अगर the request should be जारीd.
 * 1: अगर the request will be going through error recovery.
 * 2: अगर the request should be ended.
 */
अटल पूर्णांक cdrom_decode_status(ide_drive_t *drive, u8 stat)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request *rq = hwअगर->rq;
	पूर्णांक err, sense_key, करो_end_request = 0;

	/* get the IDE error रेजिस्टर */
	err = ide_पढ़ो_error(drive);
	sense_key = err >> 4;

	ide_debug_log(IDE_DBG_RQ, "cmd: 0x%x, rq->cmd_type: 0x%x, err: 0x%x, "
				  "stat 0x%x",
				  rq->cmd[0], rq->cmd_type, err, stat);

	अगर (ata_sense_request(rq)) अणु
		/*
		 * We got an error trying to get sense info from the drive
		 * (probably जबतक trying to recover from a क्रमmer error).
		 * Just give up.
		 */
		rq->rq_flags |= RQF_FAILED;
		वापस 2;
	पूर्ण

	/* अगर we have an error, pass CHECK_CONDITION as the SCSI status byte */
	अगर (blk_rq_is_scsi(rq) && !scsi_req(rq)->result)
		scsi_req(rq)->result = SAM_STAT_CHECK_CONDITION;

	अगर (blk_noretry_request(rq))
		करो_end_request = 1;

	चयन (sense_key) अणु
	हाल NOT_READY:
		अगर (req_op(rq) == REQ_OP_WRITE) अणु
			अगर (ide_cd_breathe(drive, rq))
				वापस 1;
		पूर्ण अन्यथा अणु
			cdrom_saw_media_change(drive);

			अगर (!blk_rq_is_passthrough(rq) &&
			    !(rq->rq_flags & RQF_QUIET))
				prपूर्णांकk(KERN_ERR PFX "%s: tray open\n",
					drive->name);
		पूर्ण
		करो_end_request = 1;
		अवरोध;
	हाल UNIT_ATTENTION:
		cdrom_saw_media_change(drive);

		अगर (blk_rq_is_passthrough(rq))
			वापस 0;

		/*
		 * Arrange to retry the request but be sure to give up अगर we've
		 * retried too many बार.
		 */
		अगर (++scsi_req(rq)->result > ERROR_MAX)
			करो_end_request = 1;
		अवरोध;
	हाल ILLEGAL_REQUEST:
		/*
		 * Don't prपूर्णांक error message क्रम this condition -- SFF8090i
		 * indicates that 5/24/00 is the correct response to a request
		 * to बंद the tray अगर the drive करोesn't have that capability.
		 *
		 * cdrom_log_sense() knows this!
		 */
		अगर (scsi_req(rq)->cmd[0] == GPCMD_START_STOP_UNIT)
			अवरोध;
		fallthrough;
	हाल DATA_PROTECT:
		/*
		 * No poपूर्णांक in retrying after an illegal request or data
		 * protect error.
		 */
		अगर (!(rq->rq_flags & RQF_QUIET))
			ide_dump_status(drive, "command error", stat);
		करो_end_request = 1;
		अवरोध;
	हाल MEDIUM_ERROR:
		/*
		 * No poपूर्णांक in re-trying a zillion बार on a bad sector.
		 * If we got here the error is not correctable.
		 */
		अगर (!(rq->rq_flags & RQF_QUIET))
			ide_dump_status(drive, "media error "
					"(bad sector)", stat);
		करो_end_request = 1;
		अवरोध;
	हाल BLANK_CHECK:
		/* disk appears blank? */
		अगर (!(rq->rq_flags & RQF_QUIET))
			ide_dump_status(drive, "media error (blank)",
					stat);
		करो_end_request = 1;
		अवरोध;
	शेष:
		अगर (blk_rq_is_passthrough(rq))
			अवरोध;
		अगर (err & ~ATA_ABORTED) अणु
			/* go to the शेष handler क्रम other errors */
			ide_error(drive, "cdrom_decode_status", stat);
			वापस 1;
		पूर्ण अन्यथा अगर (++scsi_req(rq)->result > ERROR_MAX)
			/* we've racked up too many retries, पात */
			करो_end_request = 1;
	पूर्ण

	अगर (blk_rq_is_passthrough(rq)) अणु
		rq->rq_flags |= RQF_FAILED;
		करो_end_request = 1;
	पूर्ण

	/*
	 * End a request through request sense analysis when we have sense data.
	 * We need this in order to perक्रमm end of media processing.
	 */
	अगर (करो_end_request)
		जाओ end_request;

	/* अगर we got a CHECK_CONDITION status, queue a request sense command */
	अगर (stat & ATA_ERR)
		वापस ide_queue_sense_rq(drive, शून्य) ? 2 : 1;
	वापस 1;

end_request:
	अगर (stat & ATA_ERR) अणु
		hwअगर->rq = शून्य;
		वापस ide_queue_sense_rq(drive, rq) ? 2 : 1;
	पूर्ण अन्यथा
		वापस 2;
पूर्ण

अटल व्योम ide_cd_request_sense_fixup(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	काष्ठा request *rq = cmd->rq;

	ide_debug_log(IDE_DBG_FUNC, "rq->cmd[0]: 0x%x", rq->cmd[0]);

	/*
	 * Some of the trailing request sense fields are optional,
	 * and some drives करोn't send them.  Sigh.
	 */
	अगर (scsi_req(rq)->cmd[0] == GPCMD_REQUEST_SENSE &&
	    cmd->nleft > 0 && cmd->nleft <= 5)
		cmd->nleft = 0;
पूर्ण

पूर्णांक ide_cd_queue_pc(ide_drive_t *drive, स्थिर अचिन्हित अक्षर *cmd,
		    पूर्णांक ग_लिखो, व्योम *buffer, अचिन्हित *bufflen,
		    काष्ठा scsi_sense_hdr *sshdr, पूर्णांक समयout,
		    req_flags_t rq_flags)
अणु
	काष्ठा cdrom_info *info = drive->driver_data;
	काष्ठा scsi_sense_hdr local_sshdr;
	पूर्णांक retries = 10;
	bool failed;

	ide_debug_log(IDE_DBG_PC, "cmd[0]: 0x%x, write: 0x%x, timeout: %d, "
				  "rq_flags: 0x%x",
				  cmd[0], ग_लिखो, समयout, rq_flags);

	अगर (!sshdr)
		sshdr = &local_sshdr;

	/* start of retry loop */
	करो अणु
		काष्ठा request *rq;
		पूर्णांक error;
		bool delay = false;

		rq = blk_get_request(drive->queue,
			ग_लिखो ? REQ_OP_DRV_OUT : REQ_OP_DRV_IN, 0);
		स_नकल(scsi_req(rq)->cmd, cmd, BLK_MAX_CDB);
		ide_req(rq)->type = ATA_PRIV_PC;
		rq->rq_flags |= rq_flags;
		rq->समयout = समयout;
		अगर (buffer) अणु
			error = blk_rq_map_kern(drive->queue, rq, buffer,
						*bufflen, GFP_NOIO);
			अगर (error) अणु
				blk_put_request(rq);
				वापस error;
			पूर्ण
		पूर्ण

		blk_execute_rq(info->disk, rq, 0);
		error = scsi_req(rq)->result ? -EIO : 0;

		अगर (buffer)
			*bufflen = scsi_req(rq)->resid_len;
		scsi_normalize_sense(scsi_req(rq)->sense,
				     scsi_req(rq)->sense_len, sshdr);

		/*
		 * FIXME: we should probably पात/retry or something in हाल of
		 * failure.
		 */
		failed = (rq->rq_flags & RQF_FAILED) != 0;
		अगर (failed) अणु
			/*
			 * The request failed.  Retry अगर it was due to a unit
			 * attention status (usually means media was changed).
			 */
			अगर (sshdr->sense_key == UNIT_ATTENTION)
				cdrom_saw_media_change(drive);
			अन्यथा अगर (sshdr->sense_key == NOT_READY &&
				 sshdr->asc == 4 && sshdr->ascq != 4) अणु
				/*
				 * The drive is in the process of loading
				 * a disk.  Retry, but रुको a little to give
				 * the drive समय to complete the load.
				 */
				delay = true;
			पूर्ण अन्यथा अणु
				/* otherwise, करोn't retry */
				retries = 0;
			पूर्ण
			--retries;
		पूर्ण
		blk_put_request(rq);
		अगर (delay)
			ssleep(2);
	पूर्ण जबतक (failed && retries >= 0);

	/* वापस an error अगर the command failed */
	वापस failed ? -EIO : 0;
पूर्ण

/*
 * वापसs true अगर rq has been completed
 */
अटल bool ide_cd_error_cmd(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	अचिन्हित पूर्णांक nr_bytes = cmd->nbytes - cmd->nleft;

	अगर (cmd->tf_flags & IDE_TFLAG_WRITE)
		nr_bytes -= cmd->last_xfer_len;

	अगर (nr_bytes > 0) अणु
		ide_complete_rq(drive, BLK_STS_OK, nr_bytes);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* standard prep_rq that builds 10 byte cmds */
अटल bool ide_cdrom_prep_fs(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	पूर्णांक hard_sect = queue_logical_block_size(q);
	दीर्घ block = (दीर्घ)blk_rq_pos(rq) / (hard_sect >> 9);
	अचिन्हित दीर्घ blocks = blk_rq_sectors(rq) / (hard_sect >> 9);
	काष्ठा scsi_request *req = scsi_req(rq);

	अगर (rq_data_dir(rq) == READ)
		req->cmd[0] = GPCMD_READ_10;
	अन्यथा
		req->cmd[0] = GPCMD_WRITE_10;

	/*
	 * fill in lba
	 */
	req->cmd[2] = (block >> 24) & 0xff;
	req->cmd[3] = (block >> 16) & 0xff;
	req->cmd[4] = (block >>  8) & 0xff;
	req->cmd[5] = block & 0xff;

	/*
	 * and transfer length
	 */
	req->cmd[7] = (blocks >> 8) & 0xff;
	req->cmd[8] = blocks & 0xff;
	req->cmd_len = 10;
	वापस true;
पूर्ण

/*
 * Most of the SCSI commands are supported directly by ATAPI devices.
 * This transक्रमm handles the few exceptions.
 */
अटल bool ide_cdrom_prep_pc(काष्ठा request *rq)
अणु
	u8 *c = scsi_req(rq)->cmd;

	/* transक्रमm 6-byte पढ़ो/ग_लिखो commands to the 10-byte version */
	अगर (c[0] == READ_6 || c[0] == WRITE_6) अणु
		c[8] = c[4];
		c[5] = c[3];
		c[4] = c[2];
		c[3] = c[1] & 0x1f;
		c[2] = 0;
		c[1] &= 0xe0;
		c[0] += (READ_10 - READ_6);
		scsi_req(rq)->cmd_len = 10;
		वापस true;
	पूर्ण

	/*
	 * it's silly to pretend we understand 6-byte sense commands, just
	 * reject with ILLEGAL_REQUEST and the caller should take the
	 * appropriate action
	 */
	अगर (c[0] == MODE_SENSE || c[0] == MODE_SELECT) अणु
		scsi_req(rq)->result = ILLEGAL_REQUEST;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ide_cdrom_prep_rq(ide_drive_t *drive, काष्ठा request *rq)
अणु
	अगर (!blk_rq_is_passthrough(rq)) अणु
		scsi_req_init(scsi_req(rq));

		वापस ide_cdrom_prep_fs(drive->queue, rq);
	पूर्ण अन्यथा अगर (blk_rq_is_scsi(rq))
		वापस ide_cdrom_prep_pc(rq);

	वापस true;
पूर्ण

अटल ide_startstop_t cdrom_newpc_पूर्णांकr(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_cmd *cmd = &hwअगर->cmd;
	काष्ठा request *rq = hwअगर->rq;
	ide_expiry_t *expiry = शून्य;
	पूर्णांक dma_error = 0, dma, thislen, uptodate = 0;
	पूर्णांक ग_लिखो = (rq_data_dir(rq) == WRITE) ? 1 : 0, rc = 0;
	पूर्णांक sense = ata_sense_request(rq);
	अचिन्हित पूर्णांक समयout;
	u16 len;
	u8 ireason, stat;

	ide_debug_log(IDE_DBG_PC, "cmd: 0x%x, write: 0x%x", rq->cmd[0], ग_लिखो);

	/* check क्रम errors */
	dma = drive->dma;
	अगर (dma) अणु
		drive->dma = 0;
		drive->रुकोing_क्रम_dma = 0;
		dma_error = hwअगर->dma_ops->dma_end(drive);
		ide_dma_unmap_sg(drive, cmd);
		अगर (dma_error) अणु
			prपूर्णांकk(KERN_ERR PFX "%s: DMA %s error\n", drive->name,
					ग_लिखो ? "write" : "read");
			ide_dma_off(drive);
		पूर्ण
	पूर्ण

	/* check status */
	stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);

	अगर (!OK_STAT(stat, 0, BAD_R_STAT)) अणु
		rc = cdrom_decode_status(drive, stat);
		अगर (rc) अणु
			अगर (rc == 2)
				जाओ out_end;
			वापस ide_stopped;
		पूर्ण
	पूर्ण

	/* using dma, transfer is complete now */
	अगर (dma) अणु
		अगर (dma_error)
			वापस ide_error(drive, "dma error", stat);
		uptodate = 1;
		जाओ out_end;
	पूर्ण

	ide_पढ़ो_bcount_and_ireason(drive, &len, &ireason);

	thislen = !blk_rq_is_passthrough(rq) ? len : cmd->nleft;
	अगर (thislen > len)
		thislen = len;

	ide_debug_log(IDE_DBG_PC, "DRQ: stat: 0x%x, thislen: %d",
				  stat, thislen);

	/* If DRQ is clear, the command has completed. */
	अगर ((stat & ATA_DRQ) == 0) अणु
		चयन (req_op(rq)) अणु
		शेष:
			/*
			 * If we're not करोne पढ़ोing/writing, complain.
			 * Otherwise, complete the command normally.
			 */
			uptodate = 1;
			अगर (cmd->nleft > 0) अणु
				prपूर्णांकk(KERN_ERR PFX "%s: %s: data underrun "
					"(%u bytes)\n", drive->name, __func__,
					cmd->nleft);
				अगर (!ग_लिखो)
					rq->rq_flags |= RQF_FAILED;
				uptodate = 0;
			पूर्ण
			जाओ out_end;
		हाल REQ_OP_DRV_IN:
		हाल REQ_OP_DRV_OUT:
			ide_cd_request_sense_fixup(drive, cmd);

			uptodate = cmd->nleft ? 0 : 1;

			/*
			 * suck out the reमुख्यing bytes from the drive in an
			 * attempt to complete the data xfer. (see BZ#13399)
			 */
			अगर (!(stat & ATA_ERR) && !uptodate && thislen) अणु
				ide_pio_bytes(drive, cmd, ग_लिखो, thislen);
				uptodate = cmd->nleft ? 0 : 1;
			पूर्ण

			अगर (!uptodate)
				rq->rq_flags |= RQF_FAILED;
			जाओ out_end;
		हाल REQ_OP_SCSI_IN:
		हाल REQ_OP_SCSI_OUT:
			जाओ out_end;
		पूर्ण
	पूर्ण

	rc = ide_check_ireason(drive, rq, len, ireason, ग_लिखो);
	अगर (rc)
		जाओ out_end;

	cmd->last_xfer_len = 0;

	ide_debug_log(IDE_DBG_PC, "data transfer, rq->cmd_type: 0x%x, "
				  "ireason: 0x%x",
				  rq->cmd_type, ireason);

	/* transfer data */
	जबतक (thislen > 0) अणु
		पूर्णांक blen = min_t(पूर्णांक, thislen, cmd->nleft);

		अगर (cmd->nleft == 0)
			अवरोध;

		ide_pio_bytes(drive, cmd, ग_लिखो, blen);
		cmd->last_xfer_len += blen;

		thislen -= blen;
		len -= blen;

		अगर (sense && ग_लिखो == 0)
			scsi_req(rq)->sense_len += blen;
	पूर्ण

	/* pad, अगर necessary */
	अगर (len > 0) अणु
		अगर (blk_rq_is_passthrough(rq) || ग_लिखो == 0)
			ide_pad_transfer(drive, ग_लिखो, len);
		अन्यथा अणु
			prपूर्णांकk(KERN_ERR PFX "%s: confused, missing data\n",
				drive->name);
			blk_dump_rq_flags(rq, "cdrom_newpc_intr");
		पूर्ण
	पूर्ण

	चयन (req_op(rq)) अणु
	हाल REQ_OP_SCSI_IN:
	हाल REQ_OP_SCSI_OUT:
		समयout = rq->समयout;
		अवरोध;
	हाल REQ_OP_DRV_IN:
	हाल REQ_OP_DRV_OUT:
		expiry = ide_cd_expiry;
		fallthrough;
	शेष:
		समयout = ATAPI_WAIT_PC;
		अवरोध;
	पूर्ण

	hwअगर->expiry = expiry;
	ide_set_handler(drive, cdrom_newpc_पूर्णांकr, समयout);
	वापस ide_started;

out_end:
	अगर (blk_rq_is_scsi(rq) && rc == 0) अणु
		scsi_req(rq)->resid_len = 0;
		blk_mq_end_request(rq, BLK_STS_OK);
		hwअगर->rq = शून्य;
	पूर्ण अन्यथा अणु
		अगर (sense && uptodate)
			ide_cd_complete_failed_rq(drive, rq);

		अगर (!blk_rq_is_passthrough(rq)) अणु
			अगर (cmd->nleft == 0)
				uptodate = 1;
		पूर्ण अन्यथा अणु
			अगर (uptodate <= 0 && scsi_req(rq)->result == 0)
				scsi_req(rq)->result = -EIO;
		पूर्ण

		अगर (uptodate == 0 && rq->bio)
			अगर (ide_cd_error_cmd(drive, cmd))
				वापस ide_stopped;

		/* make sure it's fully ended */
		अगर (blk_rq_is_passthrough(rq)) अणु
			scsi_req(rq)->resid_len -= cmd->nbytes - cmd->nleft;
			अगर (uptodate == 0 && (cmd->tf_flags & IDE_TFLAG_WRITE))
				scsi_req(rq)->resid_len += cmd->last_xfer_len;
		पूर्ण

		ide_complete_rq(drive, uptodate ? BLK_STS_OK : BLK_STS_IOERR, blk_rq_bytes(rq));

		अगर (sense && rc == 2)
			ide_error(drive, "request sense failure", stat);
	पूर्ण

	ide_cd_मुक्त_sense(drive);
	वापस ide_stopped;
पूर्ण

अटल ide_startstop_t cdrom_start_rw(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा cdrom_info *cd = drive->driver_data;
	काष्ठा request_queue *q = drive->queue;
	पूर्णांक ग_लिखो = rq_data_dir(rq) == WRITE;
	अचिन्हित लघु sectors_per_frame =
		queue_logical_block_size(q) >> SECTOR_SHIFT;

	ide_debug_log(IDE_DBG_RQ, "rq->cmd[0]: 0x%x, rq->cmd_flags: 0x%x, "
				  "secs_per_frame: %u",
				  rq->cmd[0], rq->cmd_flags, sectors_per_frame);

	अगर (ग_लिखो) अणु
		/* disk has become ग_लिखो रक्षित */
		अगर (get_disk_ro(cd->disk))
			वापस ide_stopped;
	पूर्ण अन्यथा अणु
		/*
		 * We may be retrying this request after an error.  Fix up any
		 * weirdness which might be present in the request packet.
		 */
		ide_cdrom_prep_rq(drive, rq);
	पूर्ण

	/* fs requests *must* be hardware frame aligned */
	अगर ((blk_rq_sectors(rq) & (sectors_per_frame - 1)) ||
	    (blk_rq_pos(rq) & (sectors_per_frame - 1)))
		वापस ide_stopped;

	/* use DMA, अगर possible */
	drive->dma = !!(drive->dev_flags & IDE_DFLAG_USING_DMA);

	अगर (ग_लिखो)
		cd->devinfo.media_written = 1;

	rq->समयout = ATAPI_WAIT_PC;

	वापस ide_started;
पूर्ण

अटल व्योम cdrom_करो_block_pc(ide_drive_t *drive, काष्ठा request *rq)
अणु

	ide_debug_log(IDE_DBG_PC, "rq->cmd[0]: 0x%x, rq->cmd_type: 0x%x",
				  rq->cmd[0], rq->cmd_type);

	अगर (blk_rq_is_scsi(rq))
		rq->rq_flags |= RQF_QUIET;
	अन्यथा
		rq->rq_flags &= ~RQF_FAILED;

	drive->dma = 0;

	/* sg request */
	अगर (rq->bio) अणु
		काष्ठा request_queue *q = drive->queue;
		अक्षर *buf = bio_data(rq->bio);
		अचिन्हित पूर्णांक alignment;

		drive->dma = !!(drive->dev_flags & IDE_DFLAG_USING_DMA);

		/*
		 * check अगर dma is safe
		 *
		 * NOTE! The "len" and "addr" checks should possibly have
		 * separate masks.
		 */
		alignment = queue_dma_alignment(q) | q->dma_pad_mask;
		अगर ((अचिन्हित दीर्घ)buf & alignment
		    || blk_rq_bytes(rq) & q->dma_pad_mask
		    || object_is_on_stack(buf))
			drive->dma = 0;
	पूर्ण
पूर्ण

अटल ide_startstop_t ide_cd_करो_request(ide_drive_t *drive, काष्ठा request *rq,
					sector_t block)
अणु
	काष्ठा ide_cmd cmd;
	पूर्णांक uptodate = 0;
	अचिन्हित पूर्णांक nsectors;

	ide_debug_log(IDE_DBG_RQ, "cmd: 0x%x, block: %llu",
				  rq->cmd[0], (अचिन्हित दीर्घ दीर्घ)block);

	अगर (drive->debug_mask & IDE_DBG_RQ)
		blk_dump_rq_flags(rq, "ide_cd_do_request");

	चयन (req_op(rq)) अणु
	शेष:
		अगर (cdrom_start_rw(drive, rq) == ide_stopped)
			जाओ out_end;
		अवरोध;
	हाल REQ_OP_SCSI_IN:
	हाल REQ_OP_SCSI_OUT:
	handle_pc:
		अगर (!rq->समयout)
			rq->समयout = ATAPI_WAIT_PC;
		cdrom_करो_block_pc(drive, rq);
		अवरोध;
	हाल REQ_OP_DRV_IN:
	हाल REQ_OP_DRV_OUT:
		चयन (ide_req(rq)->type) अणु
		हाल ATA_PRIV_MISC:
			/* right now this can only be a reset... */
			uptodate = 1;
			जाओ out_end;
		हाल ATA_PRIV_SENSE:
		हाल ATA_PRIV_PC:
			जाओ handle_pc;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	/* prepare sense request क्रम this command */
	ide_prep_sense(drive, rq);

	स_रखो(&cmd, 0, माप(cmd));

	अगर (rq_data_dir(rq))
		cmd.tf_flags |= IDE_TFLAG_WRITE;

	cmd.rq = rq;

	अगर (!blk_rq_is_passthrough(rq) || blk_rq_bytes(rq)) अणु
		ide_init_sg_cmd(&cmd, blk_rq_bytes(rq));
		ide_map_sg(drive, &cmd);
	पूर्ण

	वापस ide_issue_pc(drive, &cmd);
out_end:
	nsectors = blk_rq_sectors(rq);

	अगर (nsectors == 0)
		nsectors = 1;

	ide_complete_rq(drive, uptodate ? BLK_STS_OK : BLK_STS_IOERR, nsectors << 9);

	वापस ide_stopped;
पूर्ण

/*
 * Ioctl handling.
 *
 * Routines which queue packet commands take as a final argument a poपूर्णांकer to a
 * request_sense काष्ठा. If execution of the command results in an error with a
 * CHECK CONDITION status, this काष्ठाure will be filled with the results of the
 * subsequent request sense command. The poपूर्णांकer can also be शून्य, in which हाल
 * no sense inक्रमmation is वापसed.
 */
अटल व्योम msf_from_bcd(काष्ठा atapi_msf *msf)
अणु
	msf->minute = bcd2bin(msf->minute);
	msf->second = bcd2bin(msf->second);
	msf->frame  = bcd2bin(msf->frame);
पूर्ण

पूर्णांक cdrom_check_status(ide_drive_t *drive, काष्ठा scsi_sense_hdr *sshdr)
अणु
	काष्ठा cdrom_info *info = drive->driver_data;
	काष्ठा cdrom_device_info *cdi;
	अचिन्हित अक्षर cmd[BLK_MAX_CDB];

	ide_debug_log(IDE_DBG_FUNC, "enter");

	अगर (!info)
		वापस -EIO;

	cdi = &info->devinfo;

	स_रखो(cmd, 0, BLK_MAX_CDB);
	cmd[0] = GPCMD_TEST_UNIT_READY;

	/*
	 * Sanyo 3 CD changer uses byte 7 of TEST_UNIT_READY to चयन CDs
	 * instead of supporting the LOAD_UNLOAD opcode.
	 */
	cmd[7] = cdi->sanyo_slot % 3;

	वापस ide_cd_queue_pc(drive, cmd, 0, शून्य, शून्य, sshdr, 0, RQF_QUIET);
पूर्ण

अटल पूर्णांक cdrom_पढ़ो_capacity(ide_drive_t *drive, अचिन्हित दीर्घ *capacity,
			       अचिन्हित दीर्घ *sectors_per_frame)
अणु
	काष्ठा अणु
		__be32 lba;
		__be32 blocklen;
	पूर्ण capbuf;

	पूर्णांक stat;
	अचिन्हित अक्षर cmd[BLK_MAX_CDB];
	अचिन्हित len = माप(capbuf);
	u32 blocklen;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	स_रखो(cmd, 0, BLK_MAX_CDB);
	cmd[0] = GPCMD_READ_CDVD_CAPACITY;

	stat = ide_cd_queue_pc(drive, cmd, 0, &capbuf, &len, शून्य, 0,
			       RQF_QUIET);
	अगर (stat)
		वापस stat;

	/*
	 * Sanity check the given block size, in so far as making
	 * sure the sectors_per_frame we give to the caller won't
	 * end up being bogus.
	 */
	blocklen = be32_to_cpu(capbuf.blocklen);
	blocklen = (blocklen >> SECTOR_SHIFT) << SECTOR_SHIFT;
	चयन (blocklen) अणु
	हाल 512:
	हाल 1024:
	हाल 2048:
	हाल 4096:
		अवरोध;
	शेष:
		prपूर्णांकk_once(KERN_ERR PFX "%s: weird block size %u; "
				"setting default block size to 2048\n",
				drive->name, blocklen);
		blocklen = 2048;
		अवरोध;
	पूर्ण

	*capacity = 1 + be32_to_cpu(capbuf.lba);
	*sectors_per_frame = blocklen >> SECTOR_SHIFT;

	ide_debug_log(IDE_DBG_PROBE, "cap: %lu, sectors_per_frame: %lu",
				     *capacity, *sectors_per_frame);

	वापस 0;
पूर्ण

अटल पूर्णांक ide_cdrom_पढ़ो_tocentry(ide_drive_t *drive, पूर्णांक trackno,
		पूर्णांक msf_flag, पूर्णांक क्रमmat, अक्षर *buf, पूर्णांक buflen)
अणु
	अचिन्हित अक्षर cmd[BLK_MAX_CDB];

	ide_debug_log(IDE_DBG_FUNC, "enter");

	स_रखो(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cmd[6] = trackno;
	cmd[7] = (buflen >> 8);
	cmd[8] = (buflen & 0xff);
	cmd[9] = (क्रमmat << 6);

	अगर (msf_flag)
		cmd[1] = 2;

	वापस ide_cd_queue_pc(drive, cmd, 0, buf, &buflen, शून्य, 0, RQF_QUIET);
पूर्ण

/* Try to पढ़ो the entire TOC क्रम the disk पूर्णांकo our पूर्णांकernal buffer. */
पूर्णांक ide_cd_पढ़ो_toc(ide_drive_t *drive)
अणु
	पूर्णांक stat, ntracks, i;
	काष्ठा cdrom_info *info = drive->driver_data;
	काष्ठा cdrom_device_info *cdi = &info->devinfo;
	काष्ठा atapi_toc *toc = info->toc;
	काष्ठा अणु
		काष्ठा atapi_toc_header hdr;
		काष्ठा atapi_toc_entry  ent;
	पूर्ण ms_पंचांगp;
	दीर्घ last_written;
	अचिन्हित दीर्घ sectors_per_frame = SECTORS_PER_FRAME;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	अगर (toc == शून्य) अणु
		/* try to allocate space */
		toc = kदो_स्मृति(माप(काष्ठा atapi_toc), GFP_KERNEL);
		अगर (toc == शून्य) अणु
			prपूर्णांकk(KERN_ERR PFX "%s: No cdrom TOC buffer!\n",
					drive->name);
			वापस -ENOMEM;
		पूर्ण
		info->toc = toc;
	पूर्ण

	/*
	 * Check to see अगर the existing data is still valid. If it is,
	 * just वापस.
	 */
	(व्योम) cdrom_check_status(drive, शून्य);

	अगर (drive->atapi_flags & IDE_AFLAG_TOC_VALID)
		वापस 0;

	/* try to get the total cdrom capacity and sector size */
	stat = cdrom_पढ़ो_capacity(drive, &toc->capacity, &sectors_per_frame);
	अगर (stat)
		toc->capacity = 0x1fffff;

	set_capacity(info->disk, toc->capacity * sectors_per_frame);
	/* save a निजी copy of the TOC capacity क्रम error handling */
	drive->probed_capacity = toc->capacity * sectors_per_frame;

	blk_queue_logical_block_size(drive->queue,
				     sectors_per_frame << SECTOR_SHIFT);

	/* first पढ़ो just the header, so we know how दीर्घ the TOC is */
	stat = ide_cdrom_पढ़ो_tocentry(drive, 0, 1, 0, (अक्षर *) &toc->hdr,
				    माप(काष्ठा atapi_toc_header));
	अगर (stat)
		वापस stat;

	अगर (drive->atapi_flags & IDE_AFLAG_TOCTRACKS_AS_BCD) अणु
		toc->hdr.first_track = bcd2bin(toc->hdr.first_track);
		toc->hdr.last_track  = bcd2bin(toc->hdr.last_track);
	पूर्ण

	ntracks = toc->hdr.last_track - toc->hdr.first_track + 1;
	अगर (ntracks <= 0)
		वापस -EIO;
	अगर (ntracks > MAX_TRACKS)
		ntracks = MAX_TRACKS;

	/* now पढ़ो the whole schmeer */
	stat = ide_cdrom_पढ़ो_tocentry(drive, toc->hdr.first_track, 1, 0,
				  (अक्षर *)&toc->hdr,
				   माप(काष्ठा atapi_toc_header) +
				   (ntracks + 1) *
				   माप(काष्ठा atapi_toc_entry));

	अगर (stat && toc->hdr.first_track > 1) अणु
		/*
		 * Cds with CDI tracks only करोn't have any TOC entries, despite
		 * of this the वापसed values are
		 * first_track == last_track = number of CDI tracks + 1,
		 * so that this हाल is indistinguishable from the same layout
		 * plus an additional audio track. If we get an error क्रम the
		 * regular हाल, we assume a CDI without additional audio
		 * tracks. In this हाल the पढ़ोable TOC is empty (CDI tracks
		 * are not included) and only holds the Leaकरोut entry.
		 *
		 * Heiko Eiथfeldt.
		 */
		ntracks = 0;
		stat = ide_cdrom_पढ़ो_tocentry(drive, CDROM_LEADOUT, 1, 0,
					   (अक्षर *)&toc->hdr,
					   माप(काष्ठा atapi_toc_header) +
					   (ntracks + 1) *
					   माप(काष्ठा atapi_toc_entry));
		अगर (stat)
			वापस stat;

		अगर (drive->atapi_flags & IDE_AFLAG_TOCTRACKS_AS_BCD) अणु
			toc->hdr.first_track = (u8)bin2bcd(CDROM_LEADOUT);
			toc->hdr.last_track = (u8)bin2bcd(CDROM_LEADOUT);
		पूर्ण अन्यथा अणु
			toc->hdr.first_track = CDROM_LEADOUT;
			toc->hdr.last_track = CDROM_LEADOUT;
		पूर्ण
	पूर्ण

	अगर (stat)
		वापस stat;

	toc->hdr.toc_length = be16_to_cpu(toc->hdr.toc_length);

	अगर (drive->atapi_flags & IDE_AFLAG_TOCTRACKS_AS_BCD) अणु
		toc->hdr.first_track = bcd2bin(toc->hdr.first_track);
		toc->hdr.last_track  = bcd2bin(toc->hdr.last_track);
	पूर्ण

	क्रम (i = 0; i <= ntracks; i++) अणु
		अगर (drive->atapi_flags & IDE_AFLAG_TOCADDR_AS_BCD) अणु
			अगर (drive->atapi_flags & IDE_AFLAG_TOCTRACKS_AS_BCD)
				toc->ent[i].track = bcd2bin(toc->ent[i].track);
			msf_from_bcd(&toc->ent[i].addr.msf);
		पूर्ण
		toc->ent[i].addr.lba = msf_to_lba(toc->ent[i].addr.msf.minute,
						  toc->ent[i].addr.msf.second,
						  toc->ent[i].addr.msf.frame);
	पूर्ण

	अगर (toc->hdr.first_track != CDROM_LEADOUT) अणु
		/* पढ़ो the multisession inक्रमmation */
		stat = ide_cdrom_पढ़ो_tocentry(drive, 0, 0, 1, (अक्षर *)&ms_पंचांगp,
					   माप(ms_पंचांगp));
		अगर (stat)
			वापस stat;

		toc->last_session_lba = be32_to_cpu(ms_पंचांगp.ent.addr.lba);
	पूर्ण अन्यथा अणु
		ms_पंचांगp.hdr.last_track = CDROM_LEADOUT;
		ms_पंचांगp.hdr.first_track = ms_पंचांगp.hdr.last_track;
		toc->last_session_lba = msf_to_lba(0, 2, 0); /* 0m 2s 0f */
	पूर्ण

	अगर (drive->atapi_flags & IDE_AFLAG_TOCADDR_AS_BCD) अणु
		/* re-पढ़ो multisession inक्रमmation using MSF क्रमmat */
		stat = ide_cdrom_पढ़ो_tocentry(drive, 0, 1, 1, (अक्षर *)&ms_पंचांगp,
					   माप(ms_पंचांगp));
		अगर (stat)
			वापस stat;

		msf_from_bcd(&ms_पंचांगp.ent.addr.msf);
		toc->last_session_lba = msf_to_lba(ms_पंचांगp.ent.addr.msf.minute,
						   ms_पंचांगp.ent.addr.msf.second,
						   ms_पंचांगp.ent.addr.msf.frame);
	पूर्ण

	toc->xa_flag = (ms_पंचांगp.hdr.first_track != ms_पंचांगp.hdr.last_track);

	/* now try to get the total cdrom capacity */
	stat = cdrom_get_last_written(cdi, &last_written);
	अगर (!stat && (last_written > toc->capacity)) अणु
		toc->capacity = last_written;
		set_capacity(info->disk, toc->capacity * sectors_per_frame);
		drive->probed_capacity = toc->capacity * sectors_per_frame;
	पूर्ण

	/* Remember that we've पढ़ो this stuff. */
	drive->atapi_flags |= IDE_AFLAG_TOC_VALID;

	वापस 0;
पूर्ण

पूर्णांक ide_cdrom_get_capabilities(ide_drive_t *drive, u8 *buf)
अणु
	काष्ठा cdrom_info *info = drive->driver_data;
	काष्ठा cdrom_device_info *cdi = &info->devinfo;
	काष्ठा packet_command cgc;
	पूर्णांक stat, attempts = 3, size = ATAPI_CAPABILITIES_PAGE_SIZE;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	अगर ((drive->atapi_flags & IDE_AFLAG_FULL_CAPS_PAGE) == 0)
		size -= ATAPI_CAPABILITIES_PAGE_PAD_SIZE;

	init_cdrom_command(&cgc, buf, size, CGC_DATA_UNKNOWN);
	करो अणु
		/* we seem to get stat=0x01,err=0x00 the first समय (??) */
		stat = cdrom_mode_sense(cdi, &cgc, GPMODE_CAPABILITIES_PAGE, 0);
		अगर (!stat)
			अवरोध;
	पूर्ण जबतक (--attempts);
	वापस stat;
पूर्ण

व्योम ide_cdrom_update_speed(ide_drive_t *drive, u8 *buf)
अणु
	काष्ठा cdrom_info *cd = drive->driver_data;
	u16 curspeed, maxspeed;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	अगर (drive->atapi_flags & IDE_AFLAG_LE_SPEED_FIELDS) अणु
		curspeed = le16_to_cpup((__le16 *)&buf[8 + 14]);
		maxspeed = le16_to_cpup((__le16 *)&buf[8 + 8]);
	पूर्ण अन्यथा अणु
		curspeed = be16_to_cpup((__be16 *)&buf[8 + 14]);
		maxspeed = be16_to_cpup((__be16 *)&buf[8 + 8]);
	पूर्ण

	ide_debug_log(IDE_DBG_PROBE, "curspeed: %u, maxspeed: %u",
				     curspeed, maxspeed);

	cd->current_speed = DIV_ROUND_CLOSEST(curspeed, 176);
	cd->max_speed = DIV_ROUND_CLOSEST(maxspeed, 176);
पूर्ण

#घोषणा IDE_CD_CAPABILITIES \
	(CDC_CLOSE_TRAY | CDC_OPEN_TRAY | CDC_LOCK | CDC_SELECT_SPEED | \
	 CDC_SELECT_DISC | CDC_MULTI_SESSION | CDC_MCN | CDC_MEDIA_CHANGED | \
	 CDC_PLAY_AUDIO | CDC_RESET | CDC_DRIVE_STATUS | CDC_CD_R | \
	 CDC_CD_RW | CDC_DVD | CDC_DVD_R | CDC_DVD_RAM | CDC_GENERIC_PACKET | \
	 CDC_MO_DRIVE | CDC_MRW | CDC_MRW_W | CDC_RAM)

अटल स्थिर काष्ठा cdrom_device_ops ide_cdrom_करोps = अणु
	.खोलो			= ide_cdrom_खोलो_real,
	.release		= ide_cdrom_release_real,
	.drive_status		= ide_cdrom_drive_status,
	.check_events		= ide_cdrom_check_events_real,
	.tray_move		= ide_cdrom_tray_move,
	.lock_करोor		= ide_cdrom_lock_करोor,
	.select_speed		= ide_cdrom_select_speed,
	.get_last_session	= ide_cdrom_get_last_session,
	.get_mcn		= ide_cdrom_get_mcn,
	.reset			= ide_cdrom_reset,
	.audio_ioctl		= ide_cdrom_audio_ioctl,
	.capability		= IDE_CD_CAPABILITIES,
	.generic_packet		= ide_cdrom_packet,
पूर्ण;

अटल पूर्णांक ide_cdrom_रेजिस्टर(ide_drive_t *drive, पूर्णांक nslots)
अणु
	काष्ठा cdrom_info *info = drive->driver_data;
	काष्ठा cdrom_device_info *devinfo = &info->devinfo;

	ide_debug_log(IDE_DBG_PROBE, "nslots: %d", nslots);

	devinfo->ops = &ide_cdrom_करोps;
	devinfo->speed = info->current_speed;
	devinfo->capacity = nslots;
	devinfo->handle = drive;
	म_नकल(devinfo->name, drive->name);

	अगर (drive->atapi_flags & IDE_AFLAG_NO_SPEED_SELECT)
		devinfo->mask |= CDC_SELECT_SPEED;

	वापस रेजिस्टर_cdrom(info->disk, devinfo);
पूर्ण

अटल पूर्णांक ide_cdrom_probe_capabilities(ide_drive_t *drive)
अणु
	काष्ठा cdrom_info *cd = drive->driver_data;
	काष्ठा cdrom_device_info *cdi = &cd->devinfo;
	u8 buf[ATAPI_CAPABILITIES_PAGE_SIZE];
	mechtype_t mechtype;
	पूर्णांक nslots = 1;

	ide_debug_log(IDE_DBG_PROBE, "media: 0x%x, atapi_flags: 0x%lx",
				     drive->media, drive->atapi_flags);

	cdi->mask = (CDC_CD_R | CDC_CD_RW | CDC_DVD | CDC_DVD_R |
		     CDC_DVD_RAM | CDC_SELECT_DISC | CDC_PLAY_AUDIO |
		     CDC_MO_DRIVE | CDC_RAM);

	अगर (drive->media == ide_optical) अणु
		cdi->mask &= ~(CDC_MO_DRIVE | CDC_RAM);
		prपूर्णांकk(KERN_ERR PFX "%s: ATAPI magneto-optical drive\n",
				drive->name);
		वापस nslots;
	पूर्ण

	अगर (drive->atapi_flags & IDE_AFLAG_PRE_ATAPI12) अणु
		drive->atapi_flags &= ~IDE_AFLAG_NO_EJECT;
		cdi->mask &= ~CDC_PLAY_AUDIO;
		वापस nslots;
	पूर्ण

	/*
	 * We have to cheat a little here. the packet will eventually be queued
	 * with ide_cdrom_packet(), which extracts the drive from cdi->handle.
	 * Since this device hasn't been रेजिस्टरed with the Unअगरorm layer yet,
	 * it can't करो this. Same goes क्रम cdi->ops.
	 */
	cdi->handle = drive;
	cdi->ops = &ide_cdrom_करोps;

	अगर (ide_cdrom_get_capabilities(drive, buf))
		वापस 0;

	अगर ((buf[8 + 6] & 0x01) == 0)
		drive->dev_flags &= ~IDE_DFLAG_DOORLOCKING;
	अगर (buf[8 + 6] & 0x08)
		drive->atapi_flags &= ~IDE_AFLAG_NO_EJECT;
	अगर (buf[8 + 3] & 0x01)
		cdi->mask &= ~CDC_CD_R;
	अगर (buf[8 + 3] & 0x02)
		cdi->mask &= ~(CDC_CD_RW | CDC_RAM);
	अगर (buf[8 + 2] & 0x38)
		cdi->mask &= ~CDC_DVD;
	अगर (buf[8 + 3] & 0x20)
		cdi->mask &= ~(CDC_DVD_RAM | CDC_RAM);
	अगर (buf[8 + 3] & 0x10)
		cdi->mask &= ~CDC_DVD_R;
	अगर ((buf[8 + 4] & 0x01) || (drive->atapi_flags & IDE_AFLAG_PLAY_AUDIO_OK))
		cdi->mask &= ~CDC_PLAY_AUDIO;

	mechtype = buf[8 + 6] >> 5;
	अगर (mechtype == mechtype_caddy ||
	    mechtype == mechtype_popup ||
	    (drive->atapi_flags & IDE_AFLAG_NO_AUTOCLOSE))
		cdi->mask |= CDC_CLOSE_TRAY;

	अगर (cdi->sanyo_slot > 0) अणु
		cdi->mask &= ~CDC_SELECT_DISC;
		nslots = 3;
	पूर्ण अन्यथा अगर (mechtype == mechtype_inभागidual_changer ||
		   mechtype == mechtype_cartridge_changer) अणु
		nslots = cdrom_number_of_slots(cdi);
		अगर (nslots > 1)
			cdi->mask &= ~CDC_SELECT_DISC;
	पूर्ण

	ide_cdrom_update_speed(drive, buf);

	prपूर्णांकk(KERN_INFO PFX "%s: ATAPI", drive->name);

	/* करोn't prपूर्णांक speed अगर the drive reported 0 */
	अगर (cd->max_speed)
		prपूर्णांकk(KERN_CONT " %dX", cd->max_speed);

	prपूर्णांकk(KERN_CONT " %s", (cdi->mask & CDC_DVD) ? "CD-ROM" : "DVD-ROM");

	अगर ((cdi->mask & CDC_DVD_R) == 0 || (cdi->mask & CDC_DVD_RAM) == 0)
		prपूर्णांकk(KERN_CONT " DVD%s%s",
				 (cdi->mask & CDC_DVD_R) ? "" : "-R",
				 (cdi->mask & CDC_DVD_RAM) ? "" : "/RAM");

	अगर ((cdi->mask & CDC_CD_R) == 0 || (cdi->mask & CDC_CD_RW) == 0)
		prपूर्णांकk(KERN_CONT " CD%s%s",
				 (cdi->mask & CDC_CD_R) ? "" : "-R",
				 (cdi->mask & CDC_CD_RW) ? "" : "/RW");

	अगर ((cdi->mask & CDC_SELECT_DISC) == 0)
		prपूर्णांकk(KERN_CONT " changer w/%d slots", nslots);
	अन्यथा
		prपूर्णांकk(KERN_CONT " drive");

	prपूर्णांकk(KERN_CONT ", %dkB Cache\n",
			 be16_to_cpup((__be16 *)&buf[8 + 12]));

	वापस nslots;
पूर्ण

काष्ठा cd_list_entry अणु
	स्थिर अक्षर	*id_model;
	स्थिर अक्षर	*id_firmware;
	अचिन्हित पूर्णांक	cd_flags;
पूर्ण;

#अगर_घोषित CONFIG_IDE_PROC_FS
अटल sector_t ide_cdrom_capacity(ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ capacity, sectors_per_frame;

	अगर (cdrom_पढ़ो_capacity(drive, &capacity, &sectors_per_frame))
		वापस 0;

	वापस capacity * sectors_per_frame;
पूर्ण

अटल पूर्णांक idecd_capacity_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t *drive = m->निजी;

	seq_म_लिखो(m, "%llu\n", (दीर्घ दीर्घ)ide_cdrom_capacity(drive));
	वापस 0;
पूर्ण

अटल ide_proc_entry_t idecd_proc[] = अणु
	अणु "capacity", S_IFREG|S_IRUGO, idecd_capacity_proc_show पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल ide_proc_entry_t *ide_cd_proc_entries(ide_drive_t *drive)
अणु
	वापस idecd_proc;
पूर्ण

अटल स्थिर काष्ठा ide_proc_devset *ide_cd_proc_devsets(ide_drive_t *drive)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा cd_list_entry ide_cd_quirks_list[] = अणु
	/* SCR-3231 करोesn't support the SET_CD_SPEED command. */
	अणु "SAMSUNG CD-ROM SCR-3231", शून्य,   IDE_AFLAG_NO_SPEED_SELECT	     पूर्ण,
	/* Old NEC260 (not R) was released beक्रमe ATAPI 1.2 spec. */
	अणु "NEC CD-ROM DRIVE:260",    "1.01", IDE_AFLAG_TOCADDR_AS_BCD |
					     IDE_AFLAG_PRE_ATAPI12,	     पूर्ण,
	/* Vertos 300, some versions of this drive like to talk BCD. */
	अणु "V003S0DS",		     शून्य,   IDE_AFLAG_VERTOS_300_SSD,	     पूर्ण,
	/* Vertos 600 ESD. */
	अणु "V006E0DS",		     शून्य,   IDE_AFLAG_VERTOS_600_ESD,	     पूर्ण,
	/*
	 * Sanyo 3 CD changer uses a non-standard command क्रम CD changing
	 * (by शेष standard ATAPI support क्रम CD changers is used).
	 */
	अणु "CD-ROM CDR-C3 G",	     शून्य,   IDE_AFLAG_SANYO_3CD	     पूर्ण,
	अणु "CD-ROM CDR-C3G",	     शून्य,   IDE_AFLAG_SANYO_3CD	     पूर्ण,
	अणु "CD-ROM CDR_C36",	     शून्य,   IDE_AFLAG_SANYO_3CD	     पूर्ण,
	/* Stingray 8X CD-ROM. */
	अणु "STINGRAY 8422 IDE 8X CD-ROM 7-27-95", शून्य, IDE_AFLAG_PRE_ATAPI12 पूर्ण,
	/*
	 * ACER 50X CD-ROM and WPI 32X CD-ROM require the full spec length
	 * mode sense page capabilities size, but older drives अवरोध.
	 */
	अणु "ATAPI CD ROM DRIVE 50X MAX",	शून्य,	IDE_AFLAG_FULL_CAPS_PAGE     पूर्ण,
	अणु "WPI CDS-32X",		शून्य,	IDE_AFLAG_FULL_CAPS_PAGE     पूर्ण,
	/* ACER/AOpen 24X CD-ROM has the speed fields byte-swapped. */
	अणु "",			     "241N", IDE_AFLAG_LE_SPEED_FIELDS       पूर्ण,
	/*
	 * Some drives used by Apple करोn't advertise audio play
	 * but they करो support पढ़ोing TOC & audio datas.
	 */
	अणु "MATSHITADVD-ROM SR-8187", शून्य,   IDE_AFLAG_PLAY_AUDIO_OK	     पूर्ण,
	अणु "MATSHITADVD-ROM SR-8186", शून्य,   IDE_AFLAG_PLAY_AUDIO_OK	     पूर्ण,
	अणु "MATSHITADVD-ROM SR-8176", शून्य,   IDE_AFLAG_PLAY_AUDIO_OK	     पूर्ण,
	अणु "MATSHITADVD-ROM SR-8174", शून्य,   IDE_AFLAG_PLAY_AUDIO_OK	     पूर्ण,
	अणु "Optiarc DVD RW AD-5200A", शून्य,   IDE_AFLAG_PLAY_AUDIO_OK	     पूर्ण,
	अणु "Optiarc DVD RW AD-7200A", शून्य,   IDE_AFLAG_PLAY_AUDIO_OK	     पूर्ण,
	अणु "Optiarc DVD RW AD-7543A", शून्य,   IDE_AFLAG_NO_AUTOCLOSE	     पूर्ण,
	अणु "TEAC CD-ROM CD-224E",     शून्य,   IDE_AFLAG_NO_AUTOCLOSE	     पूर्ण,
	अणु शून्य, शून्य, 0 पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक ide_cd_flags(u16 *id)
अणु
	स्थिर काष्ठा cd_list_entry *cle = ide_cd_quirks_list;

	जबतक (cle->id_model) अणु
		अगर (म_भेद(cle->id_model, (अक्षर *)&id[ATA_ID_PROD]) == 0 &&
		    (cle->id_firmware == शून्य ||
		     म_माला((अक्षर *)&id[ATA_ID_FW_REV], cle->id_firmware)))
			वापस cle->cd_flags;
		cle++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ide_cdrom_setup(ide_drive_t *drive)
अणु
	काष्ठा cdrom_info *cd = drive->driver_data;
	काष्ठा cdrom_device_info *cdi = &cd->devinfo;
	काष्ठा request_queue *q = drive->queue;
	u16 *id = drive->id;
	अक्षर *fw_rev = (अक्षर *)&id[ATA_ID_FW_REV];
	पूर्णांक nslots;

	ide_debug_log(IDE_DBG_PROBE, "enter");

	drive->prep_rq = ide_cdrom_prep_rq;
	blk_queue_dma_alignment(q, 31);
	blk_queue_update_dma_pad(q, 15);

	drive->dev_flags |= IDE_DFLAG_MEDIA_CHANGED;
	drive->atapi_flags = IDE_AFLAG_NO_EJECT | ide_cd_flags(id);

	अगर ((drive->atapi_flags & IDE_AFLAG_VERTOS_300_SSD) &&
	    fw_rev[4] == '1' && fw_rev[6] <= '2')
		drive->atapi_flags |= (IDE_AFLAG_TOCTRACKS_AS_BCD |
				     IDE_AFLAG_TOCADDR_AS_BCD);
	अन्यथा अगर ((drive->atapi_flags & IDE_AFLAG_VERTOS_600_ESD) &&
		 fw_rev[4] == '1' && fw_rev[6] <= '2')
		drive->atapi_flags |= IDE_AFLAG_TOCTRACKS_AS_BCD;
	अन्यथा अगर (drive->atapi_flags & IDE_AFLAG_SANYO_3CD)
		/* 3 => use CD in slot 0 */
		cdi->sanyo_slot = 3;

	nslots = ide_cdrom_probe_capabilities(drive);

	blk_queue_logical_block_size(q, CD_FRAMESIZE);

	अगर (ide_cdrom_रेजिस्टर(drive, nslots)) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: %s failed to register device with the"
				" cdrom driver.\n", drive->name, __func__);
		cd->devinfo.handle = शून्य;
		वापस 1;
	पूर्ण

	ide_proc_रेजिस्टर_driver(drive, cd->driver);
	वापस 0;
पूर्ण

अटल व्योम ide_cd_हटाओ(ide_drive_t *drive)
अणु
	काष्ठा cdrom_info *info = drive->driver_data;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	ide_proc_unरेजिस्टर_driver(drive, info->driver);
	device_del(&info->dev);
	del_gendisk(info->disk);

	mutex_lock(&idecd_ref_mutex);
	put_device(&info->dev);
	mutex_unlock(&idecd_ref_mutex);
पूर्ण

अटल व्योम ide_cd_release(काष्ठा device *dev)
अणु
	काष्ठा cdrom_info *info = to_ide_drv(dev, cdrom_info);
	काष्ठा cdrom_device_info *devinfo = &info->devinfo;
	ide_drive_t *drive = info->drive;
	काष्ठा gendisk *g = info->disk;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	kमुक्त(info->toc);
	अगर (devinfo->handle == drive)
		unरेजिस्टर_cdrom(devinfo);
	drive->driver_data = शून्य;
	drive->prep_rq = शून्य;
	g->निजी_data = शून्य;
	put_disk(g);
	kमुक्त(info);
पूर्ण

अटल पूर्णांक ide_cd_probe(ide_drive_t *);

अटल काष्ठा ide_driver ide_cdrom_driver = अणु
	.gen_driver = अणु
		.owner		= THIS_MODULE,
		.name		= "ide-cdrom",
		.bus		= &ide_bus_type,
	पूर्ण,
	.probe			= ide_cd_probe,
	.हटाओ			= ide_cd_हटाओ,
	.version		= IDECD_VERSION,
	.करो_request		= ide_cd_करो_request,
#अगर_घोषित CONFIG_IDE_PROC_FS
	.proc_entries		= ide_cd_proc_entries,
	.proc_devsets		= ide_cd_proc_devsets,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक idecd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा cdrom_info *info;
	पूर्णांक rc = -ENXIO;

	अगर (bdev_check_media_change(bdev)) अणु
		info = ide_drv_g(bdev->bd_disk, cdrom_info);

		ide_cd_पढ़ो_toc(info->drive);
	पूर्ण

	mutex_lock(&ide_cd_mutex);
	info = ide_cd_get(bdev->bd_disk);
	अगर (!info)
		जाओ out;

	rc = cdrom_खोलो(&info->devinfo, bdev, mode);
	अगर (rc < 0)
		ide_cd_put(info);
out:
	mutex_unlock(&ide_cd_mutex);
	वापस rc;
पूर्ण

अटल व्योम idecd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा cdrom_info *info = ide_drv_g(disk, cdrom_info);

	mutex_lock(&ide_cd_mutex);
	cdrom_release(&info->devinfo, mode);

	ide_cd_put(info);
	mutex_unlock(&ide_cd_mutex);
पूर्ण

अटल पूर्णांक idecd_set_spinकरोwn(काष्ठा cdrom_device_info *cdi, अचिन्हित दीर्घ arg)
अणु
	काष्ठा packet_command cgc;
	अक्षर buffer[16];
	पूर्णांक stat;
	अक्षर spinकरोwn;

	अगर (copy_from_user(&spinकरोwn, (व्योम __user *)arg, माप(अक्षर)))
		वापस -EFAULT;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_UNKNOWN);

	stat = cdrom_mode_sense(cdi, &cgc, GPMODE_CDROM_PAGE, 0);
	अगर (stat)
		वापस stat;

	buffer[11] = (buffer[11] & 0xf0) | (spinकरोwn & 0x0f);
	वापस cdrom_mode_select(cdi, &cgc);
पूर्ण

अटल पूर्णांक idecd_get_spinकरोwn(काष्ठा cdrom_device_info *cdi, अचिन्हित दीर्घ arg)
अणु
	काष्ठा packet_command cgc;
	अक्षर buffer[16];
	पूर्णांक stat;
	अक्षर spinकरोwn;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_UNKNOWN);

	stat = cdrom_mode_sense(cdi, &cgc, GPMODE_CDROM_PAGE, 0);
	अगर (stat)
		वापस stat;

	spinकरोwn = buffer[11] & 0x0f;
	अगर (copy_to_user((व्योम __user *)arg, &spinकरोwn, माप(अक्षर)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक idecd_locked_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cdrom_info *info = ide_drv_g(bdev->bd_disk, cdrom_info);
	पूर्णांक err;

	चयन (cmd) अणु
	हाल CDROMSETSPINDOWN:
		वापस idecd_set_spinकरोwn(&info->devinfo, arg);
	हाल CDROMGETSPINDOWN:
		वापस idecd_get_spinकरोwn(&info->devinfo, arg);
	शेष:
		अवरोध;
	पूर्ण

	err = generic_ide_ioctl(info->drive, bdev, cmd, arg);
	अगर (err == -EINVAL)
		err = cdrom_ioctl(&info->devinfo, bdev, mode, cmd, arg);

	वापस err;
पूर्ण

अटल पूर्णांक idecd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&ide_cd_mutex);
	ret = idecd_locked_ioctl(bdev, mode, cmd, arg);
	mutex_unlock(&ide_cd_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक idecd_locked_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cdrom_info *info = ide_drv_g(bdev->bd_disk, cdrom_info);
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक err;

	चयन (cmd) अणु
	हाल CDROMSETSPINDOWN:
		वापस idecd_set_spinकरोwn(&info->devinfo, (अचिन्हित दीर्घ)argp);
	हाल CDROMGETSPINDOWN:
		वापस idecd_get_spinकरोwn(&info->devinfo, (अचिन्हित दीर्घ)argp);
	शेष:
		अवरोध;
	पूर्ण

	err = generic_ide_ioctl(info->drive, bdev, cmd, arg);
	अगर (err == -EINVAL)
		err = cdrom_ioctl(&info->devinfo, bdev, mode, cmd,
				  (अचिन्हित दीर्घ)argp);

	वापस err;
पूर्ण

अटल पूर्णांक idecd_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&ide_cd_mutex);
	ret = idecd_locked_compat_ioctl(bdev, mode, cmd, arg);
	mutex_unlock(&ide_cd_mutex);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक idecd_check_events(काष्ठा gendisk *disk,
				       अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा cdrom_info *info = ide_drv_g(disk, cdrom_info);
	वापस cdrom_check_events(&info->devinfo, clearing);
पूर्ण

अटल स्थिर काष्ठा block_device_operations idecd_ops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= idecd_खोलो,
	.release		= idecd_release,
	.ioctl			= idecd_ioctl,
	.compat_ioctl		= IS_ENABLED(CONFIG_COMPAT) ?
				  idecd_compat_ioctl : शून्य,
	.check_events		= idecd_check_events,
पूर्ण;

/* module options */
अटल अचिन्हित दीर्घ debug_mask;
module_param(debug_mask, uदीर्घ, 0644);

MODULE_DESCRIPTION("ATAPI CD-ROM Driver");

अटल पूर्णांक ide_cd_probe(ide_drive_t *drive)
अणु
	काष्ठा cdrom_info *info;
	काष्ठा gendisk *g;

	ide_debug_log(IDE_DBG_PROBE, "driver_req: %s, media: 0x%x",
				     drive->driver_req, drive->media);

	अगर (!म_माला("ide-cdrom", drive->driver_req))
		जाओ failed;

	अगर (drive->media != ide_cdrom && drive->media != ide_optical)
		जाओ failed;

	drive->debug_mask = debug_mask;
	drive->irq_handler = cdrom_newpc_पूर्णांकr;

	info = kzalloc(माप(काष्ठा cdrom_info), GFP_KERNEL);
	अगर (info == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: Can't allocate a cdrom structure\n",
				drive->name);
		जाओ failed;
	पूर्ण

	g = alloc_disk(1 << PARTN_BITS);
	अगर (!g)
		जाओ out_मुक्त_cd;

	ide_init_disk(g, drive);

	info->dev.parent = &drive->gendev;
	info->dev.release = ide_cd_release;
	dev_set_name(&info->dev, "%s", dev_name(&drive->gendev));

	अगर (device_रेजिस्टर(&info->dev))
		जाओ out_मुक्त_disk;

	info->drive = drive;
	info->driver = &ide_cdrom_driver;
	info->disk = g;

	g->निजी_data = &info->driver;

	drive->driver_data = info;

	g->minors = 1;
	g->flags = GENHD_FL_CD | GENHD_FL_REMOVABLE;
	अगर (ide_cdrom_setup(drive)) अणु
		put_device(&info->dev);
		जाओ failed;
	पूर्ण

	ide_cd_पढ़ो_toc(drive);
	g->fops = &idecd_ops;
	g->flags |= GENHD_FL_REMOVABLE | GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE;
	g->events = DISK_EVENT_MEDIA_CHANGE;
	device_add_disk(&drive->gendev, g, शून्य);
	वापस 0;

out_मुक्त_disk:
	put_disk(g);
out_मुक्त_cd:
	kमुक्त(info);
failed:
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास ide_cdrom_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&ide_cdrom_driver.gen_driver);
पूर्ण

अटल पूर्णांक __init ide_cdrom_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO DRV_NAME " driver " IDECD_VERSION "\n");
	वापस driver_रेजिस्टर(&ide_cdrom_driver.gen_driver);
पूर्ण

MODULE_ALIAS("ide:*m-cdrom*");
MODULE_ALIAS("ide-cd");
module_init(ide_cdrom_init);
module_निकास(ide_cdrom_निकास);
MODULE_LICENSE("GPL");
