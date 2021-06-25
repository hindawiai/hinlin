<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ide.h>

DEFINE_MUTEX(ide_setting_mtx);

ide_devset_get(io_32bit, io_32bit);

अटल पूर्णांक set_io_32bit(ide_drive_t *drive, पूर्णांक arg)
अणु
	अगर (drive->dev_flags & IDE_DFLAG_NO_IO_32BIT)
		वापस -EPERM;

	अगर (arg < 0 || arg > 1 + (SUPPORT_VLB_SYNC << 1))
		वापस -EINVAL;

	drive->io_32bit = arg;

	वापस 0;
पूर्ण

ide_devset_get_flag(ksettings, IDE_DFLAG_KEEP_SETTINGS);

अटल पूर्णांक set_ksettings(ide_drive_t *drive, पूर्णांक arg)
अणु
	अगर (arg < 0 || arg > 1)
		वापस -EINVAL;

	अगर (arg)
		drive->dev_flags |= IDE_DFLAG_KEEP_SETTINGS;
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_KEEP_SETTINGS;

	वापस 0;
पूर्ण

ide_devset_get_flag(using_dma, IDE_DFLAG_USING_DMA);

अटल पूर्णांक set_using_dma(ide_drive_t *drive, पूर्णांक arg)
अणु
#अगर_घोषित CONFIG_BLK_DEV_IDEDMA
	पूर्णांक err = -EPERM;

	अगर (arg < 0 || arg > 1)
		वापस -EINVAL;

	अगर (ata_id_has_dma(drive->id) == 0)
		जाओ out;

	अगर (drive->hwअगर->dma_ops == शून्य)
		जाओ out;

	err = 0;

	अगर (arg) अणु
		अगर (ide_set_dma(drive))
			err = -EIO;
	पूर्ण अन्यथा
		ide_dma_off(drive);

out:
	वापस err;
#अन्यथा
	अगर (arg < 0 || arg > 1)
		वापस -EINVAL;

	वापस -EPERM;
#पूर्ण_अगर
पूर्ण

/*
 * handle HDIO_SET_PIO_MODE ioctl abusers here, eventually it will go away
 */
अटल पूर्णांक set_pio_mode_abuse(ide_hwअगर_t *hwअगर, u8 req_pio)
अणु
	चयन (req_pio) अणु
	हाल 202:
	हाल 201:
	हाल 200:
	हाल 102:
	हाल 101:
	हाल 100:
		वापस (hwअगर->host_flags & IDE_HFLAG_ABUSE_DMA_MODES) ? 1 : 0;
	हाल 9:
	हाल 8:
		वापस (hwअगर->host_flags & IDE_HFLAG_ABUSE_PREFETCH) ? 1 : 0;
	हाल 7:
	हाल 6:
		वापस (hwअगर->host_flags & IDE_HFLAG_ABUSE_FAST_DEVSEL) ? 1 : 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक set_pio_mode(ide_drive_t *drive, पूर्णांक arg)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;

	अगर (arg < 0 || arg > 255)
		वापस -EINVAL;

	अगर (port_ops == शून्य || port_ops->set_pio_mode == शून्य ||
	    (hwअगर->host_flags & IDE_HFLAG_NO_SET_MODE))
		वापस -ENOSYS;

	अगर (set_pio_mode_abuse(drive->hwअगर, arg)) अणु
		drive->pio_mode = arg + XFER_PIO_0;

		अगर (arg == 8 || arg == 9) अणु
			अचिन्हित दीर्घ flags;

			/* take lock क्रम IDE_DFLAG_[NO_]UNMASK/[NO_]IO_32BIT */
			spin_lock_irqsave(&hwअगर->lock, flags);
			port_ops->set_pio_mode(hwअगर, drive);
			spin_unlock_irqrestore(&hwअगर->lock, flags);
		पूर्ण अन्यथा
			port_ops->set_pio_mode(hwअगर, drive);
	पूर्ण अन्यथा अणु
		पूर्णांक keep_dma = !!(drive->dev_flags & IDE_DFLAG_USING_DMA);

		ide_set_pio(drive, arg);

		अगर (hwअगर->host_flags & IDE_HFLAG_SET_PIO_MODE_KEEP_DMA) अणु
			अगर (keep_dma)
				ide_dma_on(drive);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

ide_devset_get_flag(unmaskirq, IDE_DFLAG_UNMASK);

अटल पूर्णांक set_unmaskirq(ide_drive_t *drive, पूर्णांक arg)
अणु
	अगर (drive->dev_flags & IDE_DFLAG_NO_UNMASK)
		वापस -EPERM;

	अगर (arg < 0 || arg > 1)
		वापस -EINVAL;

	अगर (arg)
		drive->dev_flags |= IDE_DFLAG_UNMASK;
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_UNMASK;

	वापस 0;
पूर्ण

ide_ext_devset_rw_sync(io_32bit, io_32bit);
ide_ext_devset_rw_sync(keepsettings, ksettings);
ide_ext_devset_rw_sync(unmaskirq, unmaskirq);
ide_ext_devset_rw_sync(using_dma, using_dma);
__IDE_DEVSET(pio_mode, DS_SYNC, शून्य, set_pio_mode);

पूर्णांक ide_devset_execute(ide_drive_t *drive, स्थिर काष्ठा ide_devset *setting,
		       पूर्णांक arg)
अणु
	काष्ठा request_queue *q = drive->queue;
	काष्ठा request *rq;
	पूर्णांक ret = 0;

	अगर (!(setting->flags & DS_SYNC))
		वापस setting->set(drive, arg);

	rq = blk_get_request(q, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	scsi_req(rq)->cmd_len = 5;
	scsi_req(rq)->cmd[0] = REQ_DEVSET_EXEC;
	*(पूर्णांक *)&scsi_req(rq)->cmd[1] = arg;
	ide_req(rq)->special = setting->set;

	blk_execute_rq(शून्य, rq, 0);
	ret = scsi_req(rq)->result;
	blk_put_request(rq);

	वापस ret;
पूर्ण

ide_startstop_t ide_करो_devset(ide_drive_t *drive, काष्ठा request *rq)
अणु
	पूर्णांक err, (*setfunc)(ide_drive_t *, पूर्णांक) = ide_req(rq)->special;

	err = setfunc(drive, *(पूर्णांक *)&scsi_req(rq)->cmd[1]);
	अगर (err)
		scsi_req(rq)->result = err;
	ide_complete_rq(drive, 0, blk_rq_bytes(rq));
	वापस ide_stopped;
पूर्ण
