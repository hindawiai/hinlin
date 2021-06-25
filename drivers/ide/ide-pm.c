<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ide.h>

पूर्णांक generic_ide_suspend(काष्ठा device *dev, pm_message_t mesg)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request *rq;
	काष्ठा ide_pm_state rqpm;
	पूर्णांक ret;

	अगर (ide_port_acpi(hwअगर)) अणु
		/* call ACPI _GTM only once */
		अगर ((drive->dn & 1) == 0 || pair == शून्य)
			ide_acpi_get_timing(hwअगर);
	पूर्ण

	स_रखो(&rqpm, 0, माप(rqpm));
	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_PM_SUSPEND;
	ide_req(rq)->special = &rqpm;
	rqpm.pm_step = IDE_PM_START_SUSPEND;
	अगर (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	rqpm.pm_state = mesg.event;

	blk_execute_rq(शून्य, rq, 0);
	ret = scsi_req(rq)->result ? -EIO : 0;
	blk_put_request(rq);

	अगर (ret == 0 && ide_port_acpi(hwअगर)) अणु
		/* call ACPI _PS3 only after both devices are suspended */
		अगर ((drive->dn & 1) || pair == शून्य)
			ide_acpi_set_state(hwअगर, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ide_pm_execute_rq(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;

	अगर (unlikely(blk_queue_dying(q))) अणु
		rq->rq_flags |= RQF_QUIET;
		scsi_req(rq)->result = -ENXIO;
		blk_mq_end_request(rq, BLK_STS_OK);
		वापस -ENXIO;
	पूर्ण
	blk_execute_rq(शून्य, rq, true);

	वापस scsi_req(rq)->result ? -EIO : 0;
पूर्ण

पूर्णांक generic_ide_resume(काष्ठा device *dev)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request *rq;
	काष्ठा ide_pm_state rqpm;
	पूर्णांक err;

	blk_mq_start_stopped_hw_queues(drive->queue, true);

	अगर (ide_port_acpi(hwअगर)) अणु
		/* call ACPI _PS0 / _STM only once */
		अगर ((drive->dn & 1) == 0 || pair == शून्य) अणु
			ide_acpi_set_state(hwअगर, 1);
			ide_acpi_push_timing(hwअगर);
		पूर्ण

		ide_acpi_exec_tfs(drive);
	पूर्ण

	स_रखो(&rqpm, 0, माप(rqpm));
	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, BLK_MQ_REQ_PM);
	ide_req(rq)->type = ATA_PRIV_PM_RESUME;
	ide_req(rq)->special = &rqpm;
	rqpm.pm_step = IDE_PM_START_RESUME;
	rqpm.pm_state = PM_EVENT_ON;

	err = ide_pm_execute_rq(rq);
	blk_put_request(rq);

	अगर (err == 0 && dev->driver) अणु
		काष्ठा ide_driver *drv = to_ide_driver(dev->driver);

		अगर (drv->resume)
			drv->resume(drive);
	पूर्ण

	वापस err;
पूर्ण

व्योम ide_complete_घातer_step(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा ide_pm_state *pm = ide_req(rq)->special;

#अगर_घोषित DEBUG_PM
	prपूर्णांकk(KERN_INFO "%s: complete_power_step(step: %d)\n",
		drive->name, pm->pm_step);
#पूर्ण_अगर
	अगर (drive->media != ide_disk)
		वापस;

	चयन (pm->pm_step) अणु
	हाल IDE_PM_FLUSH_CACHE:	/* Suspend step 1 (flush cache) */
		अगर (pm->pm_state == PM_EVENT_FREEZE)
			pm->pm_step = IDE_PM_COMPLETED;
		अन्यथा
			pm->pm_step = IDE_PM_STANDBY;
		अवरोध;
	हाल IDE_PM_STANDBY:		/* Suspend step 2 (standby) */
		pm->pm_step = IDE_PM_COMPLETED;
		अवरोध;
	हाल IDE_PM_RESTORE_PIO:	/* Resume step 1 (restore PIO) */
		pm->pm_step = IDE_PM_IDLE;
		अवरोध;
	हाल IDE_PM_IDLE:		/* Resume step 2 (idle)*/
		pm->pm_step = IDE_PM_RESTORE_DMA;
		अवरोध;
	पूर्ण
पूर्ण

ide_startstop_t ide_start_घातer_step(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा ide_pm_state *pm = ide_req(rq)->special;
	काष्ठा ide_cmd cmd = अणु पूर्ण;

	चयन (pm->pm_step) अणु
	हाल IDE_PM_FLUSH_CACHE:	/* Suspend step 1 (flush cache) */
		अगर (drive->media != ide_disk)
			अवरोध;
		/* Not supported? Switch to next step now. */
		अगर (ata_id_flush_enabled(drive->id) == 0 ||
		    (drive->dev_flags & IDE_DFLAG_WCACHE) == 0) अणु
			ide_complete_घातer_step(drive, rq);
			वापस ide_stopped;
		पूर्ण
		अगर (ata_id_flush_ext_enabled(drive->id))
			cmd.tf.command = ATA_CMD_FLUSH_EXT;
		अन्यथा
			cmd.tf.command = ATA_CMD_FLUSH;
		जाओ out_करो_tf;
	हाल IDE_PM_STANDBY:		/* Suspend step 2 (standby) */
		cmd.tf.command = ATA_CMD_STANDBYNOW1;
		जाओ out_करो_tf;
	हाल IDE_PM_RESTORE_PIO:	/* Resume step 1 (restore PIO) */
		ide_set_max_pio(drive);
		/*
		 * skip IDE_PM_IDLE क्रम ATAPI devices
		 */
		अगर (drive->media != ide_disk)
			pm->pm_step = IDE_PM_RESTORE_DMA;
		अन्यथा
			ide_complete_घातer_step(drive, rq);
		वापस ide_stopped;
	हाल IDE_PM_IDLE:		/* Resume step 2 (idle) */
		cmd.tf.command = ATA_CMD_IDLEIMMEDIATE;
		जाओ out_करो_tf;
	हाल IDE_PM_RESTORE_DMA:	/* Resume step 3 (restore DMA) */
		/*
		 * Right now, all we करो is call ide_set_dma(drive),
		 * we could be smarter and check क्रम current xfer_speed
		 * in काष्ठा drive etc...
		 */
		अगर (drive->hwअगर->dma_ops == शून्य)
			अवरोध;
		/*
		 * TODO: respect IDE_DFLAG_USING_DMA
		 */
		ide_set_dma(drive);
		अवरोध;
	पूर्ण

	pm->pm_step = IDE_PM_COMPLETED;

	वापस ide_stopped;

out_करो_tf:
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;
	cmd.protocol = ATA_PROT_NODATA;

	वापस करो_rw_taskfile(drive, &cmd);
पूर्ण

/**
 *	ide_complete_pm_rq - end the current Power Management request
 *	@drive: target drive
 *	@rq: request
 *
 *	This function cleans up the current PM request and stops the queue
 *	अगर necessary.
 */
व्योम ide_complete_pm_rq(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = drive->queue;
	काष्ठा ide_pm_state *pm = ide_req(rq)->special;

	ide_complete_घातer_step(drive, rq);
	अगर (pm->pm_step != IDE_PM_COMPLETED)
		वापस;

#अगर_घोषित DEBUG_PM
	prपूर्णांकk("%s: completing PM request, %s\n", drive->name,
	       (ide_req(rq)->type == ATA_PRIV_PM_SUSPEND) ? "suspend" : "resume");
#पूर्ण_अगर
	अगर (ide_req(rq)->type == ATA_PRIV_PM_SUSPEND)
		blk_mq_stop_hw_queues(q);
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_BLOCKED;

	drive->hwअगर->rq = शून्य;

	blk_mq_end_request(rq, BLK_STS_OK);
पूर्ण

व्योम ide_check_pm_state(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा ide_pm_state *pm = ide_req(rq)->special;

	अगर (blk_rq_is_निजी(rq) &&
	    ide_req(rq)->type == ATA_PRIV_PM_SUSPEND &&
	    pm->pm_step == IDE_PM_START_SUSPEND)
		/* Mark drive blocked when starting the suspend sequence. */
		drive->dev_flags |= IDE_DFLAG_BLOCKED;
	अन्यथा अगर (blk_rq_is_निजी(rq) &&
	         ide_req(rq)->type == ATA_PRIV_PM_RESUME &&
		 pm->pm_step == IDE_PM_START_RESUME) अणु
		/*
		 * The first thing we करो on wakeup is to रुको क्रम BSY bit to
		 * go away (with a looong समयout) as a drive on this hwअगर may
		 * just be POSTing itself.
		 * We करो that beक्रमe even selecting as the "other" device on
		 * the bus may be broken enough to walk on our toes at this
		 * poपूर्णांक.
		 */
		ide_hwअगर_t *hwअगर = drive->hwअगर;
		स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
		काष्ठा request_queue *q = drive->queue;
		पूर्णांक rc;
#अगर_घोषित DEBUG_PM
		prपूर्णांकk("%s: Wakeup request inited, waiting for !BSY...\n", drive->name);
#पूर्ण_अगर
		rc = ide_रुको_not_busy(hwअगर, 35000);
		अगर (rc)
			prपूर्णांकk(KERN_WARNING "%s: bus not ready on wakeup\n", drive->name);
		tp_ops->dev_select(drive);
		tp_ops->ग_लिखो_devctl(hwअगर, ATA_DEVCTL_OBS);
		rc = ide_रुको_not_busy(hwअगर, 100000);
		अगर (rc)
			prपूर्णांकk(KERN_WARNING "%s: drive not ready on wakeup\n", drive->name);

		blk_mq_start_hw_queues(q);
	पूर्ण
पूर्ण
