<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ATAPI support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/ide.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/gfp.h>

#समावेश <scsi/scsi.h>

#घोषणा DRV_NAME "ide-atapi"
#घोषणा PFX DRV_NAME ": "

#अगर_घोषित DEBUG
#घोषणा debug_log(fmt, args...) \
	prपूर्णांकk(KERN_INFO "ide: " fmt, ## args)
#अन्यथा
#घोषणा debug_log(fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा ATAPI_MIN_CDB_BYTES	12

अटल अंतरभूत पूर्णांक dev_is_idecd(ide_drive_t *drive)
अणु
	वापस drive->media == ide_cdrom || drive->media == ide_optical;
पूर्ण

/*
 * Check whether we can support a device,
 * based on the ATAPI IDENTIFY command results.
 */
पूर्णांक ide_check_atapi_device(ide_drive_t *drive, स्थिर अक्षर *s)
अणु
	u16 *id = drive->id;
	u8 gcw[2], protocol, device_type, removable, drq_type, packet_size;

	*((u16 *)&gcw) = id[ATA_ID_CONFIG];

	protocol    = (gcw[1] & 0xC0) >> 6;
	device_type =  gcw[1] & 0x1F;
	removable   = (gcw[0] & 0x80) >> 7;
	drq_type    = (gcw[0] & 0x60) >> 5;
	packet_size =  gcw[0] & 0x03;

#अगर_घोषित CONFIG_PPC
	/* kludge क्रम Apple PowerBook पूर्णांकernal zip */
	अगर (drive->media == ide_floppy && device_type == 5 &&
	    !म_माला((अक्षर *)&id[ATA_ID_PROD], "CD-ROM") &&
	    म_माला((अक्षर *)&id[ATA_ID_PROD], "ZIP"))
		device_type = 0;
#पूर्ण_अगर

	अगर (protocol != 2)
		prपूर्णांकk(KERN_ERR "%s: %s: protocol (0x%02x) is not ATAPI\n",
			s, drive->name, protocol);
	अन्यथा अगर ((drive->media == ide_floppy && device_type != 0) ||
		 (drive->media == ide_tape && device_type != 1))
		prपूर्णांकk(KERN_ERR "%s: %s: invalid device type (0x%02x)\n",
			s, drive->name, device_type);
	अन्यथा अगर (removable == 0)
		prपूर्णांकk(KERN_ERR "%s: %s: the removable flag is not set\n",
			s, drive->name);
	अन्यथा अगर (drive->media == ide_floppy && drq_type == 3)
		prपूर्णांकk(KERN_ERR "%s: %s: sorry, DRQ type (0x%02x) not "
			"supported\n", s, drive->name, drq_type);
	अन्यथा अगर (packet_size != 0)
		prपूर्णांकk(KERN_ERR "%s: %s: packet size (0x%02x) is not 12 "
			"bytes\n", s, drive->name, packet_size);
	अन्यथा
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_check_atapi_device);

व्योम ide_init_pc(काष्ठा ide_atapi_pc *pc)
अणु
	स_रखो(pc, 0, माप(*pc));
पूर्ण
EXPORT_SYMBOL_GPL(ide_init_pc);

/*
 * Add a special packet command request to the tail of the request queue,
 * and रुको क्रम it to be serviced.
 */
पूर्णांक ide_queue_pc_tail(ide_drive_t *drive, काष्ठा gendisk *disk,
		      काष्ठा ide_atapi_pc *pc, व्योम *buf, अचिन्हित पूर्णांक bufflen)
अणु
	काष्ठा request *rq;
	पूर्णांक error;

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	ide_req(rq)->special = pc;

	अगर (buf && bufflen) अणु
		error = blk_rq_map_kern(drive->queue, rq, buf, bufflen,
					GFP_NOIO);
		अगर (error)
			जाओ put_req;
	पूर्ण

	स_नकल(scsi_req(rq)->cmd, pc->c, 12);
	अगर (drive->media == ide_tape)
		scsi_req(rq)->cmd[13] = REQ_IDETAPE_PC1;
	blk_execute_rq(disk, rq, 0);
	error = scsi_req(rq)->result ? -EIO : 0;
put_req:
	blk_put_request(rq);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(ide_queue_pc_tail);

पूर्णांक ide_करो_test_unit_पढ़ोy(ide_drive_t *drive, काष्ठा gendisk *disk)
अणु
	काष्ठा ide_atapi_pc pc;

	ide_init_pc(&pc);
	pc.c[0] = TEST_UNIT_READY;

	वापस ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ide_करो_test_unit_पढ़ोy);

पूर्णांक ide_करो_start_stop(ide_drive_t *drive, काष्ठा gendisk *disk, पूर्णांक start)
अणु
	काष्ठा ide_atapi_pc pc;

	ide_init_pc(&pc);
	pc.c[0] = START_STOP;
	pc.c[4] = start;

	अगर (drive->media == ide_tape)
		pc.flags |= PC_FLAG_WAIT_FOR_DSC;

	वापस ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ide_करो_start_stop);

पूर्णांक ide_set_media_lock(ide_drive_t *drive, काष्ठा gendisk *disk, पूर्णांक on)
अणु
	काष्ठा ide_atapi_pc pc;

	अगर ((drive->dev_flags & IDE_DFLAG_DOORLOCKING) == 0)
		वापस 0;

	ide_init_pc(&pc);
	pc.c[0] = ALLOW_MEDIUM_REMOVAL;
	pc.c[4] = on;

	वापस ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ide_set_media_lock);

व्योम ide_create_request_sense_cmd(ide_drive_t *drive, काष्ठा ide_atapi_pc *pc)
अणु
	ide_init_pc(pc);
	pc->c[0] = REQUEST_SENSE;
	अगर (drive->media == ide_floppy) अणु
		pc->c[4] = 255;
		pc->req_xfer = 18;
	पूर्ण अन्यथा अणु
		pc->c[4] = 20;
		pc->req_xfer = 20;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_create_request_sense_cmd);

व्योम ide_prep_sense(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा request_sense *sense = &drive->sense_data;
	काष्ठा request *sense_rq;
	काष्ठा scsi_request *req;
	अचिन्हित पूर्णांक cmd_len, sense_len;
	पूर्णांक err;

	चयन (drive->media) अणु
	हाल ide_floppy:
		cmd_len = 255;
		sense_len = 18;
		अवरोध;
	हाल ide_tape:
		cmd_len = 20;
		sense_len = 20;
		अवरोध;
	शेष:
		cmd_len = 18;
		sense_len = 18;
	पूर्ण

	BUG_ON(sense_len > माप(*sense));

	अगर (ata_sense_request(rq) || drive->sense_rq_armed)
		वापस;

	sense_rq = drive->sense_rq;
	अगर (!sense_rq) अणु
		sense_rq = blk_mq_alloc_request(drive->queue, REQ_OP_DRV_IN,
					BLK_MQ_REQ_RESERVED | BLK_MQ_REQ_NOWAIT);
		drive->sense_rq = sense_rq;
	पूर्ण
	req = scsi_req(sense_rq);

	स_रखो(sense, 0, माप(*sense));

	scsi_req_init(req);

	err = blk_rq_map_kern(drive->queue, sense_rq, sense, sense_len,
			      GFP_NOIO);
	अगर (unlikely(err)) अणु
		अगर (prपूर्णांकk_ratelimit())
			prपूर्णांकk(KERN_WARNING PFX "%s: failed to map sense "
					    "buffer\n", drive->name);
		blk_mq_मुक्त_request(sense_rq);
		drive->sense_rq = शून्य;
		वापस;
	पूर्ण

	sense_rq->rq_disk = rq->rq_disk;
	sense_rq->cmd_flags = REQ_OP_DRV_IN;
	ide_req(sense_rq)->type = ATA_PRIV_SENSE;

	req->cmd[0] = GPCMD_REQUEST_SENSE;
	req->cmd[4] = cmd_len;
	अगर (drive->media == ide_tape)
		req->cmd[13] = REQ_IDETAPE_PC1;

	drive->sense_rq_armed = true;
पूर्ण
EXPORT_SYMBOL_GPL(ide_prep_sense);

पूर्णांक ide_queue_sense_rq(ide_drive_t *drive, व्योम *special)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request *sense_rq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwअगर->lock, flags);

	/* deferred failure from ide_prep_sense() */
	अगर (!drive->sense_rq_armed) अणु
		prपूर्णांकk(KERN_WARNING PFX "%s: error queuing a sense request\n",
		       drive->name);
		spin_unlock_irqrestore(&hwअगर->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	sense_rq = drive->sense_rq;
	ide_req(sense_rq)->special = special;
	drive->sense_rq_armed = false;

	drive->hwअगर->rq = शून्य;

	ide_insert_request_head(drive, sense_rq);
	spin_unlock_irqrestore(&hwअगर->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_queue_sense_rq);

/*
 * Called when an error was detected during the last packet command.
 * We queue a request sense packet command at the head of the request
 * queue.
 */
व्योम ide_retry_pc(ide_drive_t *drive)
अणु
	काष्ठा request *failed_rq = drive->hwअगर->rq;
	काष्ठा request *sense_rq = drive->sense_rq;
	काष्ठा ide_atapi_pc *pc = &drive->request_sense_pc;

	(व्योम)ide_पढ़ो_error(drive);

	/* init pc from sense_rq */
	ide_init_pc(pc);
	स_नकल(pc->c, scsi_req(sense_rq)->cmd, 12);

	अगर (drive->media == ide_tape)
		drive->atapi_flags |= IDE_AFLAG_IGNORE_DSC;

	/*
	 * Push back the failed request and put request sense on top
	 * of it.  The failed command will be retried after sense data
	 * is acquired.
	 */
	drive->hwअगर->rq = शून्य;
	ide_requeue_and_plug(drive, failed_rq);
	अगर (ide_queue_sense_rq(drive, pc))
		ide_complete_rq(drive, BLK_STS_IOERR, blk_rq_bytes(failed_rq));
पूर्ण
EXPORT_SYMBOL_GPL(ide_retry_pc);

पूर्णांक ide_cd_expiry(ide_drive_t *drive)
अणु
	काष्ठा request *rq = drive->hwअगर->rq;
	अचिन्हित दीर्घ रुको = 0;

	debug_log("%s: scsi_req(rq)->cmd[0]: 0x%x\n", __func__, scsi_req(rq)->cmd[0]);

	/*
	 * Some commands are *slow* and normally take a दीर्घ समय to complete.
	 * Usually we can use the ATAPI "disconnect" to bypass this, but not all
	 * commands/drives support that. Let ide_समयr_expiry keep polling us
	 * क्रम these.
	 */
	चयन (scsi_req(rq)->cmd[0]) अणु
	हाल GPCMD_BLANK:
	हाल GPCMD_FORMAT_UNIT:
	हाल GPCMD_RESERVE_RZONE_TRACK:
	हाल GPCMD_CLOSE_TRACK:
	हाल GPCMD_FLUSH_CACHE:
		रुको = ATAPI_WAIT_PC;
		अवरोध;
	शेष:
		अगर (!(rq->rq_flags & RQF_QUIET))
			prपूर्णांकk(KERN_INFO PFX "cmd 0x%x timed out\n",
					 scsi_req(rq)->cmd[0]);
		रुको = 0;
		अवरोध;
	पूर्ण
	वापस रुको;
पूर्ण
EXPORT_SYMBOL_GPL(ide_cd_expiry);

पूर्णांक ide_cd_get_xferlen(काष्ठा request *rq)
अणु
	चयन (req_op(rq)) अणु
	शेष:
		वापस 32768;
	हाल REQ_OP_SCSI_IN:
	हाल REQ_OP_SCSI_OUT:
		वापस blk_rq_bytes(rq);
	हाल REQ_OP_DRV_IN:
	हाल REQ_OP_DRV_OUT:
		चयन (ide_req(rq)->type) अणु
		हाल ATA_PRIV_PC:
		हाल ATA_PRIV_SENSE:
			वापस blk_rq_bytes(rq);
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_cd_get_xferlen);

व्योम ide_पढ़ो_bcount_and_ireason(ide_drive_t *drive, u16 *bcount, u8 *ireason)
अणु
	काष्ठा ide_taskfile tf;

	drive->hwअगर->tp_ops->tf_पढ़ो(drive, &tf, IDE_VALID_NSECT |
				     IDE_VALID_LBAM | IDE_VALID_LBAH);

	*bcount = (tf.lbah << 8) | tf.lbam;
	*ireason = tf.nsect & 3;
पूर्ण
EXPORT_SYMBOL_GPL(ide_पढ़ो_bcount_and_ireason);

/*
 * Check the contents of the पूर्णांकerrupt reason रेजिस्टर and attempt to recover अगर
 * there are problems.
 *
 * Returns:
 * - 0 अगर everything's ok
 * - 1 अगर the request has to be terminated.
 */
पूर्णांक ide_check_ireason(ide_drive_t *drive, काष्ठा request *rq, पूर्णांक len,
		      पूर्णांक ireason, पूर्णांक rw)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	debug_log("ireason: 0x%x, rw: 0x%x\n", ireason, rw);

	अगर (ireason == (!rw << 1))
		वापस 0;
	अन्यथा अगर (ireason == (rw << 1)) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: %s: wrong transfer direction!\n",
				drive->name, __func__);

		अगर (dev_is_idecd(drive))
			ide_pad_transfer(drive, rw, len);
	पूर्ण अन्यथा अगर (!rw && ireason == ATAPI_COD) अणु
		अगर (dev_is_idecd(drive)) अणु
			/*
			 * Some drives (ASUS) seem to tell us that status info
			 * is available.  Just get it and ignore.
			 */
			(व्योम)hwअगर->tp_ops->पढ़ो_status(hwअगर);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ireason & ATAPI_COD)
			prपूर्णांकk(KERN_ERR PFX "%s: CoD != 0 in %s\n", drive->name,
					__func__);

		/* drive wants a command packet, or invalid ireason... */
		prपूर्णांकk(KERN_ERR PFX "%s: %s: bad interrupt reason 0x%02x\n",
				drive->name, __func__, ireason);
	पूर्ण

	अगर (dev_is_idecd(drive) && ata_pc_request(rq))
		rq->rq_flags |= RQF_FAILED;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ide_check_ireason);

/*
 * This is the usual पूर्णांकerrupt handler which will be called during a packet
 * command.  We will transfer some of the data (as requested by the drive)
 * and will re-poपूर्णांक पूर्णांकerrupt handler to us.
 */
अटल ide_startstop_t ide_pc_पूर्णांकr(ide_drive_t *drive)
अणु
	काष्ठा ide_atapi_pc *pc = drive->pc;
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_cmd *cmd = &hwअगर->cmd;
	काष्ठा request *rq = hwअगर->rq;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	अचिन्हित पूर्णांक समयout, करोne;
	u16 bcount;
	u8 stat, ireason, dsc = 0;
	u8 ग_लिखो = !!(pc->flags & PC_FLAG_WRITING);

	debug_log("Enter %s - interrupt handler\n", __func__);

	समयout = (drive->media == ide_floppy) ? WAIT_FLOPPY_CMD
					       : WAIT_TAPE_CMD;

	/* Clear the पूर्णांकerrupt */
	stat = tp_ops->पढ़ो_status(hwअगर);

	अगर (pc->flags & PC_FLAG_DMA_IN_PROGRESS) अणु
		पूर्णांक rc;

		drive->रुकोing_क्रम_dma = 0;
		rc = hwअगर->dma_ops->dma_end(drive);
		ide_dma_unmap_sg(drive, cmd);

		अगर (rc || (drive->media == ide_tape && (stat & ATA_ERR))) अणु
			अगर (drive->media == ide_floppy)
				prपूर्णांकk(KERN_ERR PFX "%s: DMA %s error\n",
					drive->name, rq_data_dir(pc->rq)
						     ? "write" : "read");
			pc->flags |= PC_FLAG_DMA_ERROR;
		पूर्ण अन्यथा
			scsi_req(rq)->resid_len = 0;
		debug_log("%s: DMA finished\n", drive->name);
	पूर्ण

	/* No more पूर्णांकerrupts */
	अगर ((stat & ATA_DRQ) == 0) अणु
		पूर्णांक uptodate;
		blk_status_t error;

		debug_log("Packet command completed, %d bytes transferred\n",
			  blk_rq_bytes(rq));

		pc->flags &= ~PC_FLAG_DMA_IN_PROGRESS;

		local_irq_enable_in_hardirq();

		अगर (drive->media == ide_tape &&
		    (stat & ATA_ERR) && scsi_req(rq)->cmd[0] == REQUEST_SENSE)
			stat &= ~ATA_ERR;

		अगर ((stat & ATA_ERR) || (pc->flags & PC_FLAG_DMA_ERROR)) अणु
			/* Error detected */
			debug_log("%s: I/O error\n", drive->name);

			अगर (drive->media != ide_tape)
				scsi_req(pc->rq)->result++;

			अगर (scsi_req(rq)->cmd[0] == REQUEST_SENSE) अणु
				prपूर्णांकk(KERN_ERR PFX "%s: I/O error in request "
						"sense command\n", drive->name);
				वापस ide_करो_reset(drive);
			पूर्ण

			debug_log("[cmd %x]: check condition\n", scsi_req(rq)->cmd[0]);

			/* Retry operation */
			ide_retry_pc(drive);

			/* queued, but not started */
			वापस ide_stopped;
		पूर्ण
		pc->error = 0;

		अगर ((pc->flags & PC_FLAG_WAIT_FOR_DSC) && (stat & ATA_DSC) == 0)
			dsc = 1;

		/*
		 * ->pc_callback() might change rq->data_len क्रम
		 * residual count, cache total length.
		 */
		करोne = blk_rq_bytes(rq);

		/* Command finished - Call the callback function */
		uptodate = drive->pc_callback(drive, dsc);

		अगर (uptodate == 0)
			drive->failed_pc = शून्य;

		अगर (ata_misc_request(rq)) अणु
			scsi_req(rq)->result = 0;
			error = BLK_STS_OK;
		पूर्ण अन्यथा अणु

			अगर (blk_rq_is_passthrough(rq) && uptodate <= 0) अणु
				अगर (scsi_req(rq)->result == 0)
					scsi_req(rq)->result = -EIO;
			पूर्ण

			error = uptodate ? BLK_STS_OK : BLK_STS_IOERR;
		पूर्ण

		ide_complete_rq(drive, error, blk_rq_bytes(rq));
		वापस ide_stopped;
	पूर्ण

	अगर (pc->flags & PC_FLAG_DMA_IN_PROGRESS) अणु
		pc->flags &= ~PC_FLAG_DMA_IN_PROGRESS;
		prपूर्णांकk(KERN_ERR PFX "%s: The device wants to issue more "
				"interrupts in DMA mode\n", drive->name);
		ide_dma_off(drive);
		वापस ide_करो_reset(drive);
	पूर्ण

	/* Get the number of bytes to transfer on this पूर्णांकerrupt. */
	ide_पढ़ो_bcount_and_ireason(drive, &bcount, &ireason);

	अगर (ide_check_ireason(drive, rq, bcount, ireason, ग_लिखो))
		वापस ide_करो_reset(drive);

	करोne = min_t(अचिन्हित पूर्णांक, bcount, cmd->nleft);
	ide_pio_bytes(drive, cmd, ग_लिखो, करोne);

	/* Update transferred byte count */
	scsi_req(rq)->resid_len -= करोne;

	bcount -= करोne;

	अगर (bcount)
		ide_pad_transfer(drive, ग_लिखो, bcount);

	debug_log("[cmd %x] transferred %d bytes, padded %d bytes, resid: %u\n",
		  scsi_req(rq)->cmd[0], करोne, bcount, scsi_req(rq)->resid_len);

	/* And set the पूर्णांकerrupt handler again */
	ide_set_handler(drive, ide_pc_पूर्णांकr, समयout);
	वापस ide_started;
पूर्ण

अटल व्योम ide_init_packet_cmd(काष्ठा ide_cmd *cmd, u8 valid_tf,
				u16 bcount, u8 dma)
अणु
	cmd->protocol = dma ? ATAPI_PROT_DMA : ATAPI_PROT_PIO;
	cmd->valid.out.tf = IDE_VALID_LBAH | IDE_VALID_LBAM |
			    IDE_VALID_FEATURE | valid_tf;
	cmd->tf.command = ATA_CMD_PACKET;
	cmd->tf.feature = dma;		/* Use PIO/DMA */
	cmd->tf.lbam    = bcount & 0xff;
	cmd->tf.lbah    = (bcount >> 8) & 0xff;
पूर्ण

अटल u8 ide_पढ़ो_ireason(ide_drive_t *drive)
अणु
	काष्ठा ide_taskfile tf;

	drive->hwअगर->tp_ops->tf_पढ़ो(drive, &tf, IDE_VALID_NSECT);

	वापस tf.nsect & 3;
पूर्ण

अटल u8 ide_रुको_ireason(ide_drive_t *drive, u8 ireason)
अणु
	पूर्णांक retries = 100;

	जबतक (retries-- && ((ireason & ATAPI_COD) == 0 ||
		(ireason & ATAPI_IO))) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: (IO,CoD != (0,1) while issuing "
				"a packet command, retrying\n", drive->name);
		udelay(100);
		ireason = ide_पढ़ो_ireason(drive);
		अगर (retries == 0) अणु
			prपूर्णांकk(KERN_ERR PFX "%s: (IO,CoD != (0,1) while issuing"
					" a packet command, ignoring\n",
					drive->name);
			ireason |= ATAPI_COD;
			ireason &= ~ATAPI_IO;
		पूर्ण
	पूर्ण

	वापस ireason;
पूर्ण

अटल पूर्णांक ide_delayed_transfer_pc(ide_drive_t *drive)
अणु
	/* Send the actual packet */
	drive->hwअगर->tp_ops->output_data(drive, शून्य, drive->pc->c, 12);

	/* Timeout क्रम the packet command */
	वापस WAIT_FLOPPY_CMD;
पूर्ण

अटल ide_startstop_t ide_transfer_pc(ide_drive_t *drive)
अणु
	काष्ठा ide_atapi_pc *pc;
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request *rq = hwअगर->rq;
	ide_expiry_t *expiry;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक cmd_len;
	ide_startstop_t startstop;
	u8 ireason;

	अगर (ide_रुको_stat(&startstop, drive, ATA_DRQ, ATA_BUSY, WAIT_READY)) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: Strange, packet command initiated yet "
				"DRQ isn't asserted\n", drive->name);
		वापस startstop;
	पूर्ण

	अगर (drive->atapi_flags & IDE_AFLAG_DRQ_INTERRUPT) अणु
		अगर (drive->dma)
			drive->रुकोing_क्रम_dma = 1;
	पूर्ण

	अगर (dev_is_idecd(drive)) अणु
		/* ATAPI commands get padded out to 12 bytes minimum */
		cmd_len = COMMAND_SIZE(scsi_req(rq)->cmd[0]);
		अगर (cmd_len < ATAPI_MIN_CDB_BYTES)
			cmd_len = ATAPI_MIN_CDB_BYTES;

		समयout = rq->समयout;
		expiry  = ide_cd_expiry;
	पूर्ण अन्यथा अणु
		pc = drive->pc;

		cmd_len = ATAPI_MIN_CDB_BYTES;

		/*
		 * If necessary schedule the packet transfer to occur 'timeout'
		 * milliseconds later in ide_delayed_transfer_pc() after the
		 * device says it's पढ़ोy क्रम a packet.
		 */
		अगर (drive->atapi_flags & IDE_AFLAG_ZIP_DRIVE) अणु
			समयout = drive->pc_delay;
			expiry = &ide_delayed_transfer_pc;
		पूर्ण अन्यथा अणु
			समयout = (drive->media == ide_floppy) ? WAIT_FLOPPY_CMD
							       : WAIT_TAPE_CMD;
			expiry = शून्य;
		पूर्ण

		ireason = ide_पढ़ो_ireason(drive);
		अगर (drive->media == ide_tape)
			ireason = ide_रुको_ireason(drive, ireason);

		अगर ((ireason & ATAPI_COD) == 0 || (ireason & ATAPI_IO)) अणु
			prपूर्णांकk(KERN_ERR PFX "%s: (IO,CoD) != (0,1) while "
				"issuing a packet command\n", drive->name);

			वापस ide_करो_reset(drive);
		पूर्ण
	पूर्ण

	hwअगर->expiry = expiry;

	/* Set the पूर्णांकerrupt routine */
	ide_set_handler(drive,
			(dev_is_idecd(drive) ? drive->irq_handler
					     : ide_pc_पूर्णांकr),
			समयout);

	/* Send the actual packet */
	अगर ((drive->atapi_flags & IDE_AFLAG_ZIP_DRIVE) == 0)
		hwअगर->tp_ops->output_data(drive, शून्य, scsi_req(rq)->cmd, cmd_len);

	/* Begin DMA, अगर necessary */
	अगर (dev_is_idecd(drive)) अणु
		अगर (drive->dma)
			hwअगर->dma_ops->dma_start(drive);
	पूर्ण अन्यथा अणु
		अगर (pc->flags & PC_FLAG_DMA_OK) अणु
			pc->flags |= PC_FLAG_DMA_IN_PROGRESS;
			hwअगर->dma_ops->dma_start(drive);
		पूर्ण
	पूर्ण

	वापस ide_started;
पूर्ण

ide_startstop_t ide_issue_pc(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	काष्ठा ide_atapi_pc *pc;
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	ide_expiry_t *expiry = शून्य;
	काष्ठा request *rq = hwअगर->rq;
	अचिन्हित पूर्णांक समयout, bytes;
	u16 bcount;
	u8 valid_tf;
	u8 drq_पूर्णांक = !!(drive->atapi_flags & IDE_AFLAG_DRQ_INTERRUPT);

	अगर (dev_is_idecd(drive)) अणु
		valid_tf = IDE_VALID_NSECT | IDE_VALID_LBAL;
		bcount = ide_cd_get_xferlen(rq);
		expiry = ide_cd_expiry;
		समयout = ATAPI_WAIT_PC;

		अगर (drive->dma)
			drive->dma = !ide_dma_prepare(drive, cmd);
	पूर्ण अन्यथा अणु
		pc = drive->pc;

		valid_tf = IDE_VALID_DEVICE;
		bytes = blk_rq_bytes(rq);
		bcount = ((drive->media == ide_tape) ? bytes
						     : min_t(अचिन्हित पूर्णांक,
							     bytes, 63 * 1024));

		/* We haven't transferred any data yet */
		scsi_req(rq)->resid_len = bcount;

		अगर (pc->flags & PC_FLAG_DMA_ERROR) अणु
			pc->flags &= ~PC_FLAG_DMA_ERROR;
			ide_dma_off(drive);
		पूर्ण

		अगर (pc->flags & PC_FLAG_DMA_OK)
			drive->dma = !ide_dma_prepare(drive, cmd);

		अगर (!drive->dma)
			pc->flags &= ~PC_FLAG_DMA_OK;

		समयout = (drive->media == ide_floppy) ? WAIT_FLOPPY_CMD
						       : WAIT_TAPE_CMD;
	पूर्ण

	ide_init_packet_cmd(cmd, valid_tf, bcount, drive->dma);

	(व्योम)करो_rw_taskfile(drive, cmd);

	अगर (drq_पूर्णांक) अणु
		अगर (drive->dma)
			drive->रुकोing_क्रम_dma = 0;
		hwअगर->expiry = expiry;
	पूर्ण

	ide_execute_command(drive, cmd, ide_transfer_pc, समयout);

	वापस drq_पूर्णांक ? ide_started : ide_transfer_pc(drive);
पूर्ण
EXPORT_SYMBOL_GPL(ide_issue_pc);
