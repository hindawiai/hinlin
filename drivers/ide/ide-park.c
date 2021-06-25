<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ide.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/blkdev.h>

DECLARE_WAIT_QUEUE_HEAD(ide_park_wq);

अटल व्योम issue_park_cmd(ide_drive_t *drive, अचिन्हित दीर्घ समयout)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request_queue *q = drive->queue;
	काष्ठा request *rq;
	पूर्णांक rc;

	समयout += jअगरfies;
	spin_lock_irq(&hwअगर->lock);
	अगर (drive->dev_flags & IDE_DFLAG_PARKED) अणु
		पूर्णांक reset_समयr = समय_beक्रमe(समयout, drive->sleep);
		पूर्णांक start_queue = 0;

		drive->sleep = समयout;
		wake_up_all(&ide_park_wq);
		अगर (reset_समयr && del_समयr(&hwअगर->समयr))
			start_queue = 1;
		spin_unlock_irq(&hwअगर->lock);

		अगर (start_queue)
			blk_mq_run_hw_queues(q, true);
		वापस;
	पूर्ण
	spin_unlock_irq(&hwअगर->lock);

	rq = blk_get_request(q, REQ_OP_DRV_IN, 0);
	scsi_req(rq)->cmd[0] = REQ_PARK_HEADS;
	scsi_req(rq)->cmd_len = 1;
	ide_req(rq)->type = ATA_PRIV_MISC;
	ide_req(rq)->special = &समयout;
	blk_execute_rq(शून्य, rq, 1);
	rc = scsi_req(rq)->result ? -EIO : 0;
	blk_put_request(rq);
	अगर (rc)
		जाओ out;

	/*
	 * Make sure that *some* command is sent to the drive after the
	 * समयout has expired, so घातer management will be reenabled.
	 */
	rq = blk_get_request(q, REQ_OP_DRV_IN, BLK_MQ_REQ_NOWAIT);
	अगर (IS_ERR(rq))
		जाओ out;

	scsi_req(rq)->cmd[0] = REQ_UNPARK_HEADS;
	scsi_req(rq)->cmd_len = 1;
	ide_req(rq)->type = ATA_PRIV_MISC;
	spin_lock_irq(&hwअगर->lock);
	ide_insert_request_head(drive, rq);
	spin_unlock_irq(&hwअगर->lock);

out:
	वापस;
पूर्ण

ide_startstop_t ide_करो_park_unpark(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा ide_cmd cmd;
	काष्ठा ide_taskfile *tf = &cmd.tf;

	स_रखो(&cmd, 0, माप(cmd));
	अगर (scsi_req(rq)->cmd[0] == REQ_PARK_HEADS) अणु
		drive->sleep = *(अचिन्हित दीर्घ *)ide_req(rq)->special;
		drive->dev_flags |= IDE_DFLAG_SLEEPING;
		tf->command = ATA_CMD_IDLEIMMEDIATE;
		tf->feature = 0x44;
		tf->lbal = 0x4c;
		tf->lbam = 0x4e;
		tf->lbah = 0x55;
		cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
		cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;
	पूर्ण अन्यथा		/* cmd == REQ_UNPARK_HEADS */
		tf->command = ATA_CMD_CHK_POWER;

	cmd.tf_flags |= IDE_TFLAG_CUSTOM_HANDLER;
	cmd.protocol = ATA_PROT_NODATA;

	cmd.rq = rq;

	वापस करो_rw_taskfile(drive, &cmd);
पूर्ण

sमाप_प्रकार ide_park_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित दीर्घ now;
	अचिन्हित पूर्णांक msecs;

	अगर (drive->dev_flags & IDE_DFLAG_NO_UNLOAD)
		वापस -EOPNOTSUPP;

	spin_lock_irq(&hwअगर->lock);
	now = jअगरfies;
	अगर (drive->dev_flags & IDE_DFLAG_PARKED &&
	    समय_after(drive->sleep, now))
		msecs = jअगरfies_to_msecs(drive->sleep - now);
	अन्यथा
		msecs = 0;
	spin_unlock_irq(&hwअगर->lock);

	वापस snम_लिखो(buf, 20, "%u\n", msecs);
पूर्ण

sमाप_प्रकार ide_park_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
#घोषणा MAX_PARK_TIMEOUT 30000
	ide_drive_t *drive = to_ide_device(dev);
	दीर्घ पूर्णांक input;
	पूर्णांक rc;

	rc = kम_से_दीर्घ(buf, 10, &input);
	अगर (rc)
		वापस rc;
	अगर (input < -2)
		वापस -EINVAL;
	अगर (input > MAX_PARK_TIMEOUT) अणु
		input = MAX_PARK_TIMEOUT;
		rc = -EOVERFLOW;
	पूर्ण

	mutex_lock(&ide_setting_mtx);
	अगर (input >= 0) अणु
		अगर (drive->dev_flags & IDE_DFLAG_NO_UNLOAD)
			rc = -EOPNOTSUPP;
		अन्यथा अगर (input || drive->dev_flags & IDE_DFLAG_PARKED)
			issue_park_cmd(drive, msecs_to_jअगरfies(input));
	पूर्ण अन्यथा अणु
		अगर (drive->media == ide_disk)
			चयन (input) अणु
			हाल -1:
				drive->dev_flags &= ~IDE_DFLAG_NO_UNLOAD;
				अवरोध;
			हाल -2:
				drive->dev_flags |= IDE_DFLAG_NO_UNLOAD;
				अवरोध;
			पूर्ण
		अन्यथा
			rc = -EOPNOTSUPP;
	पूर्ण
	mutex_unlock(&ide_setting_mtx);

	वापस rc ? rc : len;
पूर्ण
