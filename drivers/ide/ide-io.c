<शैली गुरु>
/*
 *	IDE I/O functions
 *
 *	Basic PIO and command management functionality.
 *
 * This code was split off from ide.c. See ide.c क्रम history and original
 * copyrights.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * For the aव्योमance of करोubt the "preferred form" of this code is one which
 * is in an खोलो non patent encumbered क्रमmat. Where cryptographic key signing
 * क्रमms part of the process of creating an executable the inक्रमmation
 * including keys needed to generate an equivalently functional executable
 * are deemed to be part of the source code.
 */
 
 
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genhd.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/ide.h>
#समावेश <linux/completion.h>
#समावेश <linux/reboot.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/kmod.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

पूर्णांक ide_end_rq(ide_drive_t *drive, काष्ठा request *rq, blk_status_t error,
	       अचिन्हित पूर्णांक nr_bytes)
अणु
	/*
	 * decide whether to reenable DMA -- 3 is a अक्रमom magic क्रम now,
	 * अगर we DMA समयout more than 3 बार, just stay in PIO
	 */
	अगर ((drive->dev_flags & IDE_DFLAG_DMA_PIO_RETRY) &&
	    drive->retry_pio <= 3) अणु
		drive->dev_flags &= ~IDE_DFLAG_DMA_PIO_RETRY;
		ide_dma_on(drive);
	पूर्ण

	अगर (!blk_update_request(rq, error, nr_bytes)) अणु
		अगर (rq == drive->sense_rq) अणु
			drive->sense_rq = शून्य;
			drive->sense_rq_active = false;
		पूर्ण

		__blk_mq_end_request(rq, error);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ide_end_rq);

व्योम ide_complete_cmd(ide_drive_t *drive, काष्ठा ide_cmd *cmd, u8 stat, u8 err)
अणु
	स्थिर काष्ठा ide_tp_ops *tp_ops = drive->hwअगर->tp_ops;
	काष्ठा ide_taskfile *tf = &cmd->tf;
	काष्ठा request *rq = cmd->rq;
	u8 tf_cmd = tf->command;

	tf->error = err;
	tf->status = stat;

	अगर (cmd->ftf_flags & IDE_FTFLAG_IN_DATA) अणु
		u8 data[2];

		tp_ops->input_data(drive, cmd, data, 2);

		cmd->tf.data  = data[0];
		cmd->hob.data = data[1];
	पूर्ण

	ide_tf_पढ़ोback(drive, cmd);

	अगर ((cmd->tf_flags & IDE_TFLAG_CUSTOM_HANDLER) &&
	    tf_cmd == ATA_CMD_IDLEIMMEDIATE) अणु
		अगर (tf->lbal != 0xc4) अणु
			prपूर्णांकk(KERN_ERR "%s: head unload failed!\n",
			       drive->name);
			ide_tf_dump(drive->name, cmd);
		पूर्ण अन्यथा
			drive->dev_flags |= IDE_DFLAG_PARKED;
	पूर्ण

	अगर (rq && ata_taskfile_request(rq)) अणु
		काष्ठा ide_cmd *orig_cmd = ide_req(rq)->special;

		अगर (cmd->tf_flags & IDE_TFLAG_DYN)
			kमुक्त(orig_cmd);
		अन्यथा अगर (cmd != orig_cmd)
			स_नकल(orig_cmd, cmd, माप(*cmd));
	पूर्ण
पूर्ण

पूर्णांक ide_complete_rq(ide_drive_t *drive, blk_status_t error, अचिन्हित पूर्णांक nr_bytes)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request *rq = hwअगर->rq;
	पूर्णांक rc;

	/*
	 * अगर failfast is set on a request, override number of sectors
	 * and complete the whole request right now
	 */
	अगर (blk_noretry_request(rq) && error)
		nr_bytes = blk_rq_sectors(rq) << 9;

	rc = ide_end_rq(drive, rq, error, nr_bytes);
	अगर (rc == 0)
		hwअगर->rq = शून्य;

	वापस rc;
पूर्ण
EXPORT_SYMBOL(ide_complete_rq);

व्योम ide_समाप्त_rq(ide_drive_t *drive, काष्ठा request *rq)
अणु
	u8 drv_req = ata_misc_request(rq) && rq->rq_disk;
	u8 media = drive->media;

	drive->failed_pc = शून्य;

	अगर ((media == ide_floppy || media == ide_tape) && drv_req) अणु
		scsi_req(rq)->result = 0;
	पूर्ण अन्यथा अणु
		अगर (media == ide_tape)
			scsi_req(rq)->result = IDE_DRV_ERROR_GENERAL;
		अन्यथा अगर (blk_rq_is_passthrough(rq) && scsi_req(rq)->result == 0)
			scsi_req(rq)->result = -EIO;
	पूर्ण

	ide_complete_rq(drive, BLK_STS_IOERR, blk_rq_bytes(rq));
पूर्ण

अटल व्योम ide_tf_set_specअगरy_cmd(ide_drive_t *drive, काष्ठा ide_taskfile *tf)
अणु
	tf->nsect   = drive->sect;
	tf->lbal    = drive->sect;
	tf->lbam    = drive->cyl;
	tf->lbah    = drive->cyl >> 8;
	tf->device  = (drive->head - 1) | drive->select;
	tf->command = ATA_CMD_INIT_DEV_PARAMS;
पूर्ण

अटल व्योम ide_tf_set_restore_cmd(ide_drive_t *drive, काष्ठा ide_taskfile *tf)
अणु
	tf->nsect   = drive->sect;
	tf->command = ATA_CMD_RESTORE;
पूर्ण

अटल व्योम ide_tf_set_seपंचांगult_cmd(ide_drive_t *drive, काष्ठा ide_taskfile *tf)
अणु
	tf->nsect   = drive->mult_req;
	tf->command = ATA_CMD_SET_MULTI;
पूर्ण

/**
 *	करो_special		-	issue some special commands
 *	@drive: drive the command is क्रम
 *
 *	करो_special() is used to issue ATA_CMD_INIT_DEV_PARAMS,
 *	ATA_CMD_RESTORE and ATA_CMD_SET_MULTI commands to a drive.
 */

अटल ide_startstop_t करो_special(ide_drive_t *drive)
अणु
	काष्ठा ide_cmd cmd;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: %s: 0x%02x\n", drive->name, __func__,
		drive->special_flags);
#पूर्ण_अगर
	अगर (drive->media != ide_disk) अणु
		drive->special_flags = 0;
		drive->mult_req = 0;
		वापस ide_stopped;
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	cmd.protocol = ATA_PROT_NODATA;

	अगर (drive->special_flags & IDE_SFLAG_SET_GEOMETRY) अणु
		drive->special_flags &= ~IDE_SFLAG_SET_GEOMETRY;
		ide_tf_set_specअगरy_cmd(drive, &cmd.tf);
	पूर्ण अन्यथा अगर (drive->special_flags & IDE_SFLAG_RECALIBRATE) अणु
		drive->special_flags &= ~IDE_SFLAG_RECALIBRATE;
		ide_tf_set_restore_cmd(drive, &cmd.tf);
	पूर्ण अन्यथा अगर (drive->special_flags & IDE_SFLAG_SET_MULTMODE) अणु
		drive->special_flags &= ~IDE_SFLAG_SET_MULTMODE;
		ide_tf_set_seपंचांगult_cmd(drive, &cmd.tf);
	पूर्ण अन्यथा
		BUG();

	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;
	cmd.tf_flags = IDE_TFLAG_CUSTOM_HANDLER;

	करो_rw_taskfile(drive, &cmd);

	वापस ide_started;
पूर्ण

व्योम ide_map_sg(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा scatterlist *sg = hwअगर->sg_table, *last_sg = शून्य;
	काष्ठा request *rq = cmd->rq;

	cmd->sg_nents = __blk_rq_map_sg(drive->queue, rq, sg, &last_sg);
	अगर (blk_rq_bytes(rq) && (blk_rq_bytes(rq) & rq->q->dma_pad_mask))
		last_sg->length +=
			(rq->q->dma_pad_mask & ~blk_rq_bytes(rq)) + 1;
पूर्ण
EXPORT_SYMBOL_GPL(ide_map_sg);

व्योम ide_init_sg_cmd(काष्ठा ide_cmd *cmd, अचिन्हित पूर्णांक nr_bytes)
अणु
	cmd->nbytes = cmd->nleft = nr_bytes;
	cmd->cursg_ofs = 0;
	cmd->cursg = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ide_init_sg_cmd);

/**
 *	execute_drive_command	-	issue special drive command
 *	@drive: the drive to issue the command on
 *	@rq: the request काष्ठाure holding the command
 *
 *	execute_drive_cmd() issues a special drive command,  usually 
 *	initiated by ioctl() from the बाह्यal hdparm program. The
 *	command can be a drive command, drive task or taskfile 
 *	operation. Weirdly you can call it with शून्य to रुको क्रम
 *	all commands to finish. Don't करो this as that is due to change
 */

अटल ide_startstop_t execute_drive_cmd (ide_drive_t *drive,
		काष्ठा request *rq)
अणु
	काष्ठा ide_cmd *cmd = ide_req(rq)->special;

	अगर (cmd) अणु
		अगर (cmd->protocol == ATA_PROT_PIO) अणु
			ide_init_sg_cmd(cmd, blk_rq_sectors(rq) << 9);
			ide_map_sg(drive, cmd);
		पूर्ण

		वापस करो_rw_taskfile(drive, cmd);
	पूर्ण

 	/*
 	 * शून्य is actually a valid way of रुकोing क्रम
 	 * all current requests to be flushed from the queue.
 	 */
#अगर_घोषित DEBUG
 	prपूर्णांकk("%s: DRIVE_CMD (null)\n", drive->name);
#पूर्ण_अगर
	scsi_req(rq)->result = 0;
	ide_complete_rq(drive, BLK_STS_OK, blk_rq_bytes(rq));

 	वापस ide_stopped;
पूर्ण

अटल ide_startstop_t ide_special_rq(ide_drive_t *drive, काष्ठा request *rq)
अणु
	u8 cmd = scsi_req(rq)->cmd[0];

	चयन (cmd) अणु
	हाल REQ_PARK_HEADS:
	हाल REQ_UNPARK_HEADS:
		वापस ide_करो_park_unpark(drive, rq);
	हाल REQ_DEVSET_EXEC:
		वापस ide_करो_devset(drive, rq);
	हाल REQ_DRIVE_RESET:
		वापस ide_करो_reset(drive);
	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 *	start_request	-	start of I/O and command issuing क्रम IDE
 *
 *	start_request() initiates handling of a new I/O request. It
 *	accepts commands and I/O (पढ़ो/ग_लिखो) requests.
 *
 *	FIXME: this function needs a नाम
 */
 
अटल ide_startstop_t start_request (ide_drive_t *drive, काष्ठा request *rq)
अणु
	ide_startstop_t startstop;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: start_request: current=0x%08lx\n",
		drive->hwअगर->name, (अचिन्हित दीर्घ) rq);
#पूर्ण_अगर

	/* bail early अगर we've exceeded max_failures */
	अगर (drive->max_failures && (drive->failures > drive->max_failures)) अणु
		rq->rq_flags |= RQF_FAILED;
		जाओ समाप्त_rq;
	पूर्ण

	अगर (drive->prep_rq && !drive->prep_rq(drive, rq))
		वापस ide_stopped;

	अगर (ata_pm_request(rq))
		ide_check_pm_state(drive, rq);

	drive->hwअगर->tp_ops->dev_select(drive);
	अगर (ide_रुको_stat(&startstop, drive, drive->पढ़ोy_stat,
			  ATA_BUSY | ATA_DRQ, WAIT_READY)) अणु
		prपूर्णांकk(KERN_ERR "%s: drive not ready for command\n", drive->name);
		वापस startstop;
	पूर्ण

	अगर (drive->special_flags == 0) अणु
		काष्ठा ide_driver *drv;

		/*
		 * We reset the drive so we need to issue a SETFEATURES.
		 * Do it _after_ करो_special() restored device parameters.
		 */
		अगर (drive->current_speed == 0xff)
			ide_config_drive_speed(drive, drive->desired_speed);

		अगर (ata_taskfile_request(rq))
			वापस execute_drive_cmd(drive, rq);
		अन्यथा अगर (ata_pm_request(rq)) अणु
			काष्ठा ide_pm_state *pm = ide_req(rq)->special;
#अगर_घोषित DEBUG_PM
			prपूर्णांकk("%s: start_power_step(step: %d)\n",
				drive->name, pm->pm_step);
#पूर्ण_अगर
			startstop = ide_start_घातer_step(drive, rq);
			अगर (startstop == ide_stopped &&
			    pm->pm_step == IDE_PM_COMPLETED)
				ide_complete_pm_rq(drive, rq);
			वापस startstop;
		पूर्ण अन्यथा अगर (!rq->rq_disk && ata_misc_request(rq))
			/*
			 * TODO: Once all ULDs have been modअगरied to
			 * check क्रम specअगरic op codes rather than
			 * blindly accepting any special request, the
			 * check क्रम ->rq_disk above may be replaced
			 * by a more suitable mechanism or even
			 * dropped entirely.
			 */
			वापस ide_special_rq(drive, rq);

		drv = *(काष्ठा ide_driver **)rq->rq_disk->निजी_data;

		वापस drv->करो_request(drive, rq, blk_rq_pos(rq));
	पूर्ण
	वापस करो_special(drive);
समाप्त_rq:
	ide_समाप्त_rq(drive, rq);
	वापस ide_stopped;
पूर्ण

/**
 *	ide_stall_queue		-	छोड़ो an IDE device
 *	@drive: drive to stall
 *	@समयout: समय to stall क्रम (jअगरfies)
 *
 *	ide_stall_queue() can be used by a drive to give excess bandwidth back
 *	to the port by sleeping क्रम समयout jअगरfies.
 */
 
व्योम ide_stall_queue (ide_drive_t *drive, अचिन्हित दीर्घ समयout)
अणु
	अगर (समयout > WAIT_WORSTCASE)
		समयout = WAIT_WORSTCASE;
	drive->sleep = समयout + jअगरfies;
	drive->dev_flags |= IDE_DFLAG_SLEEPING;
पूर्ण
EXPORT_SYMBOL(ide_stall_queue);

अटल अंतरभूत पूर्णांक ide_lock_port(ide_hwअगर_t *hwअगर)
अणु
	अगर (hwअगर->busy)
		वापस 1;

	hwअगर->busy = 1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ide_unlock_port(ide_hwअगर_t *hwअगर)
अणु
	hwअगर->busy = 0;
पूर्ण

अटल अंतरभूत पूर्णांक ide_lock_host(काष्ठा ide_host *host, ide_hwअगर_t *hwअगर)
अणु
	पूर्णांक rc = 0;

	अगर (host->host_flags & IDE_HFLAG_SERIALIZE) अणु
		rc = test_and_set_bit_lock(IDE_HOST_BUSY, &host->host_busy);
		अगर (rc == 0) अणु
			अगर (host->get_lock)
				host->get_lock(ide_पूर्णांकr, hwअगर);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम ide_unlock_host(काष्ठा ide_host *host)
अणु
	अगर (host->host_flags & IDE_HFLAG_SERIALIZE) अणु
		अगर (host->release_lock)
			host->release_lock();
		clear_bit_unlock(IDE_HOST_BUSY, &host->host_busy);
	पूर्ण
पूर्ण

व्योम ide_requeue_and_plug(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = drive->queue;

	/* Use 3ms as that was the old plug delay */
	अगर (rq) अणु
		blk_mq_requeue_request(rq, false);
		blk_mq_delay_kick_requeue_list(q, 3);
	पूर्ण अन्यथा
		blk_mq_delay_run_hw_queue(q->queue_hw_ctx[0], 3);
पूर्ण

blk_status_t ide_issue_rq(ide_drive_t *drive, काष्ठा request *rq,
			  bool local_requeue)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_host *host = hwअगर->host;
	ide_startstop_t	startstop;

	अगर (!blk_rq_is_passthrough(rq) && !(rq->rq_flags & RQF_DONTPREP)) अणु
		rq->rq_flags |= RQF_DONTPREP;
		ide_req(rq)->special = शून्य;
	पूर्ण

	/* HLD करो_request() callback might sleep, make sure it's okay */
	might_sleep();

	अगर (ide_lock_host(host, hwअगर))
		वापस BLK_STS_DEV_RESOURCE;

	spin_lock_irq(&hwअगर->lock);

	अगर (!ide_lock_port(hwअगर)) अणु
		ide_hwअगर_t *prev_port;

		WARN_ON_ONCE(hwअगर->rq);
repeat:
		prev_port = hwअगर->host->cur_port;
		अगर (drive->dev_flags & IDE_DFLAG_SLEEPING &&
		    समय_after(drive->sleep, jअगरfies)) अणु
			ide_unlock_port(hwअगर);
			जाओ plug_device;
		पूर्ण

		अगर ((hwअगर->host->host_flags & IDE_HFLAG_SERIALIZE) &&
		    hwअगर != prev_port) अणु
			ide_drive_t *cur_dev =
				prev_port ? prev_port->cur_dev : शून्य;

			/*
			 * set nIEN क्रम previous port, drives in the
			 * quirk list may not like पूर्णांकr setups/cleanups
			 */
			अगर (cur_dev &&
			    (cur_dev->dev_flags & IDE_DFLAG_NIEN_QUIRK) == 0)
				prev_port->tp_ops->ग_लिखो_devctl(prev_port,
								ATA_NIEN |
								ATA_DEVCTL_OBS);

			hwअगर->host->cur_port = hwअगर;
		पूर्ण
		hwअगर->cur_dev = drive;
		drive->dev_flags &= ~(IDE_DFLAG_SLEEPING | IDE_DFLAG_PARKED);

		/*
		 * Sanity: करोn't accept a request that isn't a PM request
		 * अगर we are currently घातer managed. This is very important as
		 * blk_stop_queue() करोesn't prevent the blk_fetch_request()
		 * above to वापस us whatever is in the queue. Since we call
		 * ide_करो_request() ourselves, we end up taking requests जबतक
		 * the queue is blocked...
		 */
		अगर ((drive->dev_flags & IDE_DFLAG_BLOCKED) &&
		    ata_pm_request(rq) == 0 &&
		    (rq->rq_flags & RQF_PM) == 0) अणु
			/* there should be no pending command at this poपूर्णांक */
			ide_unlock_port(hwअगर);
			जाओ plug_device;
		पूर्ण

		scsi_req(rq)->resid_len = blk_rq_bytes(rq);
		hwअगर->rq = rq;

		spin_unlock_irq(&hwअगर->lock);
		startstop = start_request(drive, rq);
		spin_lock_irq(&hwअगर->lock);

		अगर (startstop == ide_stopped) अणु
			rq = hwअगर->rq;
			hwअगर->rq = शून्य;
			अगर (rq)
				जाओ repeat;
			ide_unlock_port(hwअगर);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
plug_device:
		अगर (local_requeue)
			list_add(&rq->queuelist, &drive->rq_list);
		spin_unlock_irq(&hwअगर->lock);
		ide_unlock_host(host);
		अगर (!local_requeue)
			ide_requeue_and_plug(drive, rq);
		वापस BLK_STS_OK;
	पूर्ण

out:
	spin_unlock_irq(&hwअगर->lock);
	अगर (rq == शून्य)
		ide_unlock_host(host);
	वापस BLK_STS_OK;
पूर्ण

/*
 * Issue a new request to a device.
 */
blk_status_t ide_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			  स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	ide_drive_t *drive = hctx->queue->queuedata;
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	spin_lock_irq(&hwअगर->lock);
	अगर (drive->sense_rq_active) अणु
		spin_unlock_irq(&hwअगर->lock);
		वापस BLK_STS_DEV_RESOURCE;
	पूर्ण
	spin_unlock_irq(&hwअगर->lock);

	blk_mq_start_request(bd->rq);
	वापस ide_issue_rq(drive, bd->rq, false);
पूर्ण

अटल पूर्णांक drive_is_पढ़ोy(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 stat = 0;

	अगर (drive->रुकोing_क्रम_dma)
		वापस hwअगर->dma_ops->dma_test_irq(drive);

	अगर (hwअगर->io_ports.ctl_addr &&
	    (hwअगर->host_flags & IDE_HFLAG_BROKEN_ALTSTATUS) == 0)
		stat = hwअगर->tp_ops->पढ़ो_altstatus(hwअगर);
	अन्यथा
		/* Note: this may clear a pending IRQ!! */
		stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);

	अगर (stat & ATA_BUSY)
		/* drive busy: definitely not पूर्णांकerrupting */
		वापस 0;

	/* drive पढ़ोy: *might* be पूर्णांकerrupting */
	वापस 1;
पूर्ण

/**
 *	ide_समयr_expiry	-	handle lack of an IDE पूर्णांकerrupt
 *	@data: समयr callback magic (hwअगर)
 *
 *	An IDE command has समयd out beक्रमe the expected drive वापस
 *	occurred. At this poपूर्णांक we attempt to clean up the current
 *	mess. If the current handler includes an expiry handler then
 *	we invoke the expiry handler, and providing it is happy the
 *	work is करोne. If that fails we apply generic recovery rules
 *	invoking the handler and checking the drive DMA status. We
 *	have an excessively incestuous relationship with the DMA
 *	logic that wants cleaning up.
 */
 
व्योम ide_समयr_expiry (काष्ठा समयr_list *t)
अणु
	ide_hwअगर_t	*hwअगर = from_समयr(hwअगर, t, समयr);
	ide_drive_t	*drive;
	ide_handler_t	*handler;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		रुको = -1;
	पूर्णांक		plug_device = 0;
	काष्ठा request	*rq_in_flight;

	spin_lock_irqsave(&hwअगर->lock, flags);

	handler = hwअगर->handler;

	अगर (handler == शून्य || hwअगर->req_gen != hwअगर->req_gen_समयr) अणु
		/*
		 * Either a marginal समयout occurred
		 * (got the पूर्णांकerrupt just as समयr expired),
		 * or we were "sleeping" to give other devices a chance.
		 * Either way, we करोn't really want to complain about anything.
		 */
	पूर्ण अन्यथा अणु
		ide_expiry_t *expiry = hwअगर->expiry;
		ide_startstop_t startstop = ide_stopped;

		drive = hwअगर->cur_dev;

		अगर (expiry) अणु
			रुको = expiry(drive);
			अगर (रुको > 0) अणु /* जारी */
				/* reset समयr */
				hwअगर->समयr.expires = jअगरfies + रुको;
				hwअगर->req_gen_समयr = hwअगर->req_gen;
				add_समयr(&hwअगर->समयr);
				spin_unlock_irqrestore(&hwअगर->lock, flags);
				वापस;
			पूर्ण
		पूर्ण
		hwअगर->handler = शून्य;
		hwअगर->expiry = शून्य;
		/*
		 * We need to simulate a real पूर्णांकerrupt when invoking
		 * the handler() function, which means we need to
		 * globally mask the specअगरic IRQ:
		 */
		spin_unlock(&hwअगर->lock);
		/* disable_irq_nosync ?? */
		disable_irq(hwअगर->irq);

		अगर (hwअगर->polling) अणु
			startstop = handler(drive);
		पूर्ण अन्यथा अगर (drive_is_पढ़ोy(drive)) अणु
			अगर (drive->रुकोing_क्रम_dma)
				hwअगर->dma_ops->dma_lost_irq(drive);
			अगर (hwअगर->port_ops && hwअगर->port_ops->clear_irq)
				hwअगर->port_ops->clear_irq(drive);

			prपूर्णांकk(KERN_WARNING "%s: lost interrupt\n",
				drive->name);
			startstop = handler(drive);
		पूर्ण अन्यथा अणु
			अगर (drive->रुकोing_क्रम_dma)
				startstop = ide_dma_समयout_retry(drive, रुको);
			अन्यथा
				startstop = ide_error(drive, "irq timeout",
					hwअगर->tp_ops->पढ़ो_status(hwअगर));
		पूर्ण
		/* Disable पूर्णांकerrupts again, `handler' might have enabled it */
		spin_lock_irq(&hwअगर->lock);
		enable_irq(hwअगर->irq);
		अगर (startstop == ide_stopped && hwअगर->polling == 0) अणु
			rq_in_flight = hwअगर->rq;
			hwअगर->rq = शून्य;
			ide_unlock_port(hwअगर);
			plug_device = 1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hwअगर->lock, flags);

	अगर (plug_device) अणु
		ide_unlock_host(hwअगर->host);
		ide_requeue_and_plug(drive, rq_in_flight);
	पूर्ण
पूर्ण

/**
 *	unexpected_पूर्णांकr		-	handle an unexpected IDE पूर्णांकerrupt
 *	@irq: पूर्णांकerrupt line
 *	@hwअगर: port being processed
 *
 *	There's nothing really useful we can करो with an unexpected पूर्णांकerrupt,
 *	other than पढ़ोing the status रेजिस्टर (to clear it), and logging it.
 *	There should be no way that an irq can happen beक्रमe we're पढ़ोy क्रम it,
 *	so we needn't worry much about losing an "important" पूर्णांकerrupt here.
 *
 *	On laptops (and "green" PCs), an unexpected पूर्णांकerrupt occurs whenever
 *	the drive enters "idle", "standby", or "sleep" mode, so अगर the status
 *	looks "good", we just ignore the पूर्णांकerrupt completely.
 *
 *	This routine assumes __cli() is in effect when called.
 *
 *	If an unexpected पूर्णांकerrupt happens on irq15 जबतक we are handling irq14
 *	and अगर the two पूर्णांकerfaces are "serialized" (CMD640), then it looks like
 *	we could screw up by पूर्णांकerfering with a new request being set up क्रम 
 *	irq15.
 *
 *	In reality, this is a non-issue.  The new command is not sent unless 
 *	the drive is पढ़ोy to accept one, in which हाल we know the drive is
 *	not trying to पूर्णांकerrupt us.  And ide_set_handler() is always invoked
 *	beक्रमe completing the issuance of any new drive command, so we will not
 *	be accidentally invoked as a result of any valid command completion
 *	पूर्णांकerrupt.
 */

अटल व्योम unexpected_पूर्णांकr(पूर्णांक irq, ide_hwअगर_t *hwअगर)
अणु
	u8 stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);

	अगर (!OK_STAT(stat, ATA_DRDY, BAD_STAT)) अणु
		/* Try to not flood the console with msgs */
		अटल अचिन्हित दीर्घ last_msgसमय, count;
		++count;

		अगर (समय_after(jअगरfies, last_msgसमय + HZ)) अणु
			last_msgसमय = jअगरfies;
			prपूर्णांकk(KERN_ERR "%s: unexpected interrupt, "
				"status=0x%02x, count=%ld\n",
				hwअगर->name, stat, count);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	ide_पूर्णांकr	-	शेष IDE पूर्णांकerrupt handler
 *	@irq: पूर्णांकerrupt number
 *	@dev_id: hwअगर
 *	@regs: unused weirdness from the kernel irq layer
 *
 *	This is the शेष IRQ handler क्रम the IDE layer. You should
 *	not need to override it. If you करो be aware it is subtle in
 *	places
 *
 *	hwअगर is the पूर्णांकerface in the group currently perक्रमming
 *	a command. hwअगर->cur_dev is the drive and hwअगर->handler is
 *	the IRQ handler to call. As we issue a command the handlers
 *	step through multiple states, reassigning the handler to the
 *	next step in the process. Unlike a smart SCSI controller IDE
 *	expects the मुख्य processor to sequence the various transfer
 *	stages. We also manage a poll समयr to catch up with most
 *	समयout situations. There are still a few where the handlers
 *	करोn't ever decide to give up.
 *
 *	The handler eventually वापसs ide_stopped to indicate the
 *	request completed. At this poपूर्णांक we issue the next request
 *	on the port and the process begins again.
 */

irqवापस_t ide_पूर्णांकr (पूर्णांक irq, व्योम *dev_id)
अणु
	ide_hwअगर_t *hwअगर = (ide_hwअगर_t *)dev_id;
	काष्ठा ide_host *host = hwअगर->host;
	ide_drive_t *drive;
	ide_handler_t *handler;
	अचिन्हित दीर्घ flags;
	ide_startstop_t startstop;
	irqवापस_t irq_ret = IRQ_NONE;
	पूर्णांक plug_device = 0;
	काष्ठा request *rq_in_flight;

	अगर (host->host_flags & IDE_HFLAG_SERIALIZE) अणु
		अगर (hwअगर != host->cur_port)
			जाओ out_early;
	पूर्ण

	spin_lock_irqsave(&hwअगर->lock, flags);

	अगर (hwअगर->port_ops && hwअगर->port_ops->test_irq &&
	    hwअगर->port_ops->test_irq(hwअगर) == 0)
		जाओ out;

	handler = hwअगर->handler;

	अगर (handler == शून्य || hwअगर->polling) अणु
		/*
		 * Not expecting an पूर्णांकerrupt from this drive.
		 * That means this could be:
		 *	(1) an पूर्णांकerrupt from another PCI device
		 *	sharing the same PCI INT# as us.
		 * or	(2) a drive just entered sleep or standby mode,
		 *	and is पूर्णांकerrupting to let us know.
		 * or	(3) a spurious पूर्णांकerrupt of unknown origin.
		 *
		 * For PCI, we cannot tell the dअगरference,
		 * so in that हाल we just ignore it and hope it goes away.
		 */
		अगर ((host->irq_flags & IRQF_SHARED) == 0) अणु
			/*
			 * Probably not a shared PCI पूर्णांकerrupt,
			 * so we can safely try to करो something about it:
			 */
			unexpected_पूर्णांकr(irq, hwअगर);
		पूर्ण अन्यथा अणु
			/*
			 * Whack the status रेजिस्टर, just in हाल
			 * we have a leftover pending IRQ.
			 */
			(व्योम)hwअगर->tp_ops->पढ़ो_status(hwअगर);
		पूर्ण
		जाओ out;
	पूर्ण

	drive = hwअगर->cur_dev;

	अगर (!drive_is_पढ़ोy(drive))
		/*
		 * This happens regularly when we share a PCI IRQ with
		 * another device.  Unक्रमtunately, it can also happen
		 * with some buggy drives that trigger the IRQ beक्रमe
		 * their status रेजिस्टर is up to date.  Hopefully we have
		 * enough advance overhead that the latter isn't a problem.
		 */
		जाओ out;

	hwअगर->handler = शून्य;
	hwअगर->expiry = शून्य;
	hwअगर->req_gen++;
	del_समयr(&hwअगर->समयr);
	spin_unlock(&hwअगर->lock);

	अगर (hwअगर->port_ops && hwअगर->port_ops->clear_irq)
		hwअगर->port_ops->clear_irq(drive);

	अगर (drive->dev_flags & IDE_DFLAG_UNMASK)
		local_irq_enable_in_hardirq();

	/* service this पूर्णांकerrupt, may set handler क्रम next पूर्णांकerrupt */
	startstop = handler(drive);

	spin_lock_irq(&hwअगर->lock);
	/*
	 * Note that handler() may have set things up क्रम another
	 * पूर्णांकerrupt to occur soon, but it cannot happen until
	 * we निकास from this routine, because it will be the
	 * same irq as is currently being serviced here, and Linux
	 * won't allow another of the same (on any CPU) until we वापस.
	 */
	अगर (startstop == ide_stopped && hwअगर->polling == 0) अणु
		BUG_ON(hwअगर->handler);
		rq_in_flight = hwअगर->rq;
		hwअगर->rq = शून्य;
		ide_unlock_port(hwअगर);
		plug_device = 1;
	पूर्ण
	irq_ret = IRQ_HANDLED;
out:
	spin_unlock_irqrestore(&hwअगर->lock, flags);
out_early:
	अगर (plug_device) अणु
		ide_unlock_host(hwअगर->host);
		ide_requeue_and_plug(drive, rq_in_flight);
	पूर्ण

	वापस irq_ret;
पूर्ण
EXPORT_SYMBOL_GPL(ide_पूर्णांकr);

व्योम ide_pad_transfer(ide_drive_t *drive, पूर्णांक ग_लिखो, पूर्णांक len)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 buf[4] = अणु 0 पूर्ण;

	जबतक (len > 0) अणु
		अगर (ग_लिखो)
			hwअगर->tp_ops->output_data(drive, शून्य, buf, min(4, len));
		अन्यथा
			hwअगर->tp_ops->input_data(drive, शून्य, buf, min(4, len));
		len -= 4;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_pad_transfer);

व्योम ide_insert_request_head(ide_drive_t *drive, काष्ठा request *rq)
अणु
	drive->sense_rq_active = true;
	list_add_tail(&rq->queuelist, &drive->rq_list);
	kblockd_schedule_work(&drive->rq_work);
पूर्ण
EXPORT_SYMBOL_GPL(ide_insert_request_head);
