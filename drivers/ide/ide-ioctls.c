<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IDE ioctls handling.
 */

#समावेश <linux/compat.h>
#समावेश <linux/export.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/ide.h>
#समावेश <linux/slab.h>

अटल पूर्णांक put_user_दीर्घ(दीर्घ val, अचिन्हित दीर्घ arg)
अणु
	अगर (in_compat_syscall())
		वापस put_user(val, (compat_दीर्घ_t __user *)compat_ptr(arg));

	वापस put_user(val, (दीर्घ __user *)arg);
पूर्ण

अटल स्थिर काष्ठा ide_ioctl_devset ide_ioctl_settings[] = अणु
अणु HDIO_GET_32BIT,	 HDIO_SET_32BIT,	&ide_devset_io_32bit  पूर्ण,
अणु HDIO_GET_KEEPSETTINGS, HDIO_SET_KEEPSETTINGS,	&ide_devset_keepsettings पूर्ण,
अणु HDIO_GET_UNMASKINTR,	 HDIO_SET_UNMASKINTR,	&ide_devset_unmaskirq पूर्ण,
अणु HDIO_GET_DMA,		 HDIO_SET_DMA,		&ide_devset_using_dma पूर्ण,
अणु -1,			 HDIO_SET_PIO_MODE,	&ide_devset_pio_mode  पूर्ण,
अणु 0 पूर्ण
पूर्ण;

पूर्णांक ide_setting_ioctl(ide_drive_t *drive, काष्ठा block_device *bdev,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		      स्थिर काष्ठा ide_ioctl_devset *s)
अणु
	स्थिर काष्ठा ide_devset *ds;
	पूर्णांक err = -EOPNOTSUPP;

	क्रम (; (ds = s->setting); s++) अणु
		अगर (ds->get && s->get_ioctl == cmd)
			जाओ पढ़ो_val;
		अन्यथा अगर (ds->set && s->set_ioctl == cmd)
			जाओ set_val;
	पूर्ण

	वापस err;

पढ़ो_val:
	mutex_lock(&ide_setting_mtx);
	err = ds->get(drive);
	mutex_unlock(&ide_setting_mtx);
	वापस err >= 0 ? put_user_दीर्घ(err, arg) : err;

set_val:
	अगर (bdev_is_partition(bdev))
		err = -EINVAL;
	अन्यथा अणु
		अगर (!capable(CAP_SYS_ADMIN))
			err = -EACCES;
		अन्यथा अणु
			mutex_lock(&ide_setting_mtx);
			err = ide_devset_execute(drive, ds, arg);
			mutex_unlock(&ide_setting_mtx);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ide_setting_ioctl);

अटल पूर्णांक ide_get_identity_ioctl(ide_drive_t *drive, अचिन्हित पूर्णांक cmd,
				  व्योम __user *argp)
अणु
	u16 *id = शून्य;
	पूर्णांक size = (cmd == HDIO_GET_IDENTITY) ? (ATA_ID_WORDS * 2) : 142;
	पूर्णांक rc = 0;

	अगर ((drive->dev_flags & IDE_DFLAG_ID_READ) == 0) अणु
		rc = -ENOMSG;
		जाओ out;
	पूर्ण

	/* ata_id_to_hd_driveid() relies on 'id' to be fully allocated. */
	id = kदो_स्मृति(ATA_ID_WORDS * 2, GFP_KERNEL);
	अगर (id == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(id, drive->id, size);
	ata_id_to_hd_driveid(id);

	अगर (copy_to_user(argp, id, size))
		rc = -EFAULT;

	kमुक्त(id);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ide_get_nice_ioctl(ide_drive_t *drive, अचिन्हित दीर्घ arg)
अणु
	वापस put_user_दीर्घ((!!(drive->dev_flags & IDE_DFLAG_DSC_OVERLAP)
			 << IDE_NICE_DSC_OVERLAP) |
			(!!(drive->dev_flags & IDE_DFLAG_NICE1)
			 << IDE_NICE_1), arg);
पूर्ण

अटल पूर्णांक ide_set_nice_ioctl(ide_drive_t *drive, अचिन्हित दीर्घ arg)
अणु
	अगर (arg != (arg & ((1 << IDE_NICE_DSC_OVERLAP) | (1 << IDE_NICE_1))))
		वापस -EPERM;

	अगर (((arg >> IDE_NICE_DSC_OVERLAP) & 1) &&
	    (drive->media != ide_tape))
		वापस -EPERM;

	अगर ((arg >> IDE_NICE_DSC_OVERLAP) & 1)
		drive->dev_flags |= IDE_DFLAG_DSC_OVERLAP;
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_DSC_OVERLAP;

	अगर ((arg >> IDE_NICE_1) & 1)
		drive->dev_flags |= IDE_DFLAG_NICE1;
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_NICE1;

	वापस 0;
पूर्ण

अटल पूर्णांक ide_cmd_ioctl(ide_drive_t *drive, व्योम __user *argp)
अणु
	u8 *buf = शून्य;
	पूर्णांक bufsize = 0, err = 0;
	u8 args[4], xfer_rate = 0;
	काष्ठा ide_cmd cmd;
	काष्ठा ide_taskfile *tf = &cmd.tf;

	अगर (शून्य == argp) अणु
		काष्ठा request *rq;

		rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
		ide_req(rq)->type = ATA_PRIV_TASKखाता;
		blk_execute_rq(शून्य, rq, 0);
		err = scsi_req(rq)->result ? -EIO : 0;
		blk_put_request(rq);

		वापस err;
	पूर्ण

	अगर (copy_from_user(args, argp, 4))
		वापस -EFAULT;

	स_रखो(&cmd, 0, माप(cmd));
	tf->feature = args[2];
	अगर (args[0] == ATA_CMD_SMART) अणु
		tf->nsect = args[3];
		tf->lbal  = args[1];
		tf->lbam  = ATA_SMART_LBAM_PASS;
		tf->lbah  = ATA_SMART_LBAH_PASS;
		cmd.valid.out.tf = IDE_VALID_OUT_TF;
		cmd.valid.in.tf  = IDE_VALID_NSECT;
	पूर्ण अन्यथा अणु
		tf->nsect = args[1];
		cmd.valid.out.tf = IDE_VALID_FEATURE | IDE_VALID_NSECT;
		cmd.valid.in.tf  = IDE_VALID_NSECT;
	पूर्ण
	tf->command = args[0];
	cmd.protocol = args[3] ? ATA_PROT_PIO : ATA_PROT_NODATA;

	अगर (args[3]) अणु
		cmd.tf_flags |= IDE_TFLAG_IO_16BIT;
		bufsize = SECTOR_SIZE * args[3];
		buf = kzalloc(bufsize, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;
	पूर्ण

	अगर (tf->command == ATA_CMD_SET_FEATURES &&
	    tf->feature == SETFEATURES_XFER &&
	    tf->nsect >= XFER_SW_DMA_0) अणु
		xfer_rate = ide_find_dma_mode(drive, tf->nsect);
		अगर (xfer_rate != tf->nsect) अणु
			err = -EINVAL;
			जाओ पात;
		पूर्ण

		cmd.tf_flags |= IDE_TFLAG_SET_XFER;
	पूर्ण

	err = ide_raw_taskfile(drive, &cmd, buf, args[3]);

	args[0] = tf->status;
	args[1] = tf->error;
	args[2] = tf->nsect;
पात:
	अगर (copy_to_user(argp, &args, 4))
		err = -EFAULT;
	अगर (buf) अणु
		अगर (copy_to_user((argp + 4), buf, bufsize))
			err = -EFAULT;
		kमुक्त(buf);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ide_task_ioctl(ide_drive_t *drive, व्योम __user *p)
अणु
	पूर्णांक err = 0;
	u8 args[7];
	काष्ठा ide_cmd cmd;

	अगर (copy_from_user(args, p, 7))
		वापस -EFAULT;

	स_रखो(&cmd, 0, माप(cmd));
	स_नकल(&cmd.tf.feature, &args[1], 6);
	cmd.tf.command = args[0];
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;

	err = ide_no_data_taskfile(drive, &cmd);

	args[0] = cmd.tf.command;
	स_नकल(&args[1], &cmd.tf.feature, 6);

	अगर (copy_to_user(p, args, 7))
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक generic_drive_reset(ide_drive_t *drive)
अणु
	काष्ठा request *rq;
	पूर्णांक ret = 0;

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	scsi_req(rq)->cmd_len = 1;
	scsi_req(rq)->cmd[0] = REQ_DRIVE_RESET;
	blk_execute_rq(शून्य, rq, 1);
	ret = scsi_req(rq)->result;
	blk_put_request(rq);
	वापस ret;
पूर्ण

पूर्णांक generic_ide_ioctl(ide_drive_t *drive, काष्ठा block_device *bdev,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (in_compat_syscall())
		argp = compat_ptr(arg);

	err = ide_setting_ioctl(drive, bdev, cmd, arg, ide_ioctl_settings);
	अगर (err != -EOPNOTSUPP)
		वापस err;

	चयन (cmd) अणु
	हाल HDIO_OBSOLETE_IDENTITY:
	हाल HDIO_GET_IDENTITY:
		अगर (bdev_is_partition(bdev))
			वापस -EINVAL;
		वापस ide_get_identity_ioctl(drive, cmd, argp);
	हाल HDIO_GET_NICE:
		वापस ide_get_nice_ioctl(drive, arg);
	हाल HDIO_SET_NICE:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;
		वापस ide_set_nice_ioctl(drive, arg);
#अगर_घोषित CONFIG_IDE_TASK_IOCTL
	हाल HDIO_DRIVE_TASKखाता:
		अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		/* missing compat handler क्रम HDIO_DRIVE_TASKखाता */
		अगर (in_compat_syscall())
			वापस -ENOTTY;
		अगर (drive->media == ide_disk)
			वापस ide_taskfile_ioctl(drive, arg);
		वापस -ENOMSG;
#पूर्ण_अगर
	हाल HDIO_DRIVE_CMD:
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		वापस ide_cmd_ioctl(drive, argp);
	हाल HDIO_DRIVE_TASK:
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		वापस ide_task_ioctl(drive, argp);
	हाल HDIO_DRIVE_RESET:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;
		वापस generic_drive_reset(drive);
	हाल HDIO_GET_BUSSTATE:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;
		अगर (put_user_दीर्घ(BUSSTATE_ON, arg))
			वापस -EFAULT;
		वापस 0;
	हाल HDIO_SET_BUSSTATE:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(generic_ide_ioctl);
