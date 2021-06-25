<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ide-floppy IOCTLs handling.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ide.h>
#समावेश <linux/compat.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi_ioctl.h>

#समावेश "ide-floppy.h"

/*
 * Obtain the list of क्रमmattable capacities.
 * Very similar to ide_floppy_get_capacity, except that we push the capacity
 * descriptors to userland, instead of our own काष्ठाures.
 *
 * Userland gives us the following काष्ठाure:
 *
 * काष्ठा idefloppy_क्रमmat_capacities अणु
 *	पूर्णांक nक्रमmats;
 *	काष्ठा अणु
 *		पूर्णांक nblocks;
 *		पूर्णांक blocksize;
 *	पूर्ण क्रमmats[];
 * पूर्ण;
 *
 * userland initializes nक्रमmats to the number of allocated क्रमmats[] records.
 * On निकास we set nक्रमmats to the number of records we've actually initialized.
 */

अटल DEFINE_MUTEX(ide_floppy_ioctl_mutex);
अटल पूर्णांक ide_floppy_get_क्रमmat_capacities(ide_drive_t *drive,
					    काष्ठा ide_atapi_pc *pc,
					    पूर्णांक __user *arg)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	पूर्णांक i, blocks, length, u_array_size, u_index;
	पूर्णांक __user *argp;
	u8 pc_buf[256], header_len, desc_cnt;

	अगर (get_user(u_array_size, arg))
		वापस -EFAULT;

	अगर (u_array_size <= 0)
		वापस -EINVAL;

	ide_floppy_create_पढ़ो_capacity_cmd(pc);

	अगर (ide_queue_pc_tail(drive, floppy->disk, pc, pc_buf, pc->req_xfer)) अणु
		prपूर्णांकk(KERN_ERR "ide-floppy: Can't get floppy parameters\n");
		वापस -EIO;
	पूर्ण

	header_len = pc_buf[3];
	desc_cnt = header_len / 8; /* capacity descriptor of 8 bytes */

	u_index = 0;
	argp = arg + 1;

	/*
	 * We always skip the first capacity descriptor.  That's the current
	 * capacity.  We are पूर्णांकerested in the reमुख्यing descriptors, the
	 * क्रमmattable capacities.
	 */
	क्रम (i = 1; i < desc_cnt; i++) अणु
		अचिन्हित पूर्णांक desc_start = 4 + i*8;

		अगर (u_index >= u_array_size)
			अवरोध;	/* User-supplied buffer too small */

		blocks = be32_to_cpup((__be32 *)&pc_buf[desc_start]);
		length = be16_to_cpup((__be16 *)&pc_buf[desc_start + 6]);

		अगर (put_user(blocks, argp))
			वापस -EFAULT;

		++argp;

		अगर (put_user(length, argp))
			वापस -EFAULT;

		++argp;

		++u_index;
	पूर्ण

	अगर (put_user(u_index, arg))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम ide_floppy_create_क्रमmat_unit_cmd(काष्ठा ide_atapi_pc *pc,
					      u8 *buf, पूर्णांक b, पूर्णांक l,
					      पूर्णांक flags)
अणु
	ide_init_pc(pc);
	pc->c[0] = GPCMD_FORMAT_UNIT;
	pc->c[1] = 0x17;

	स_रखो(buf, 0, 12);
	buf[1] = 0xA2;
	/* Default क्रमmat list header, u8 1: FOV/DCRT/IMM bits set */

	अगर (flags & 1)				/* Verअगरy bit on... */
		buf[1] ^= 0x20;			/* ... turn off DCRT bit */
	buf[3] = 8;

	put_unaligned(cpu_to_be32(b), (अचिन्हित पूर्णांक *)(&buf[4]));
	put_unaligned(cpu_to_be32(l), (अचिन्हित पूर्णांक *)(&buf[8]));
	pc->req_xfer = 12;
	pc->flags |= PC_FLAG_WRITING;
पूर्ण

अटल पूर्णांक ide_floppy_get_sfrp_bit(ide_drive_t *drive, काष्ठा ide_atapi_pc *pc)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	u8 buf[20];

	drive->atapi_flags &= ~IDE_AFLAG_SRFP;

	ide_floppy_create_mode_sense_cmd(pc, IDEFLOPPY_CAPABILITIES_PAGE);
	pc->flags |= PC_FLAG_SUPPRESS_ERROR;

	अगर (ide_queue_pc_tail(drive, floppy->disk, pc, buf, pc->req_xfer))
		वापस 1;

	अगर (buf[8 + 2] & 0x40)
		drive->atapi_flags |= IDE_AFLAG_SRFP;

	वापस 0;
पूर्ण

अटल पूर्णांक ide_floppy_क्रमmat_unit(ide_drive_t *drive, काष्ठा ide_atapi_pc *pc,
				  पूर्णांक __user *arg)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	u8 buf[12];
	पूर्णांक blocks, length, flags, err = 0;

	अगर (floppy->खोलोers > 1) अणु
		/* Don't क्रमmat अगर someone is using the disk */
		drive->dev_flags &= ~IDE_DFLAG_FORMAT_IN_PROGRESS;
		वापस -EBUSY;
	पूर्ण

	drive->dev_flags |= IDE_DFLAG_FORMAT_IN_PROGRESS;

	/*
	 * Send ATAPI_FORMAT_UNIT to the drive.
	 *
	 * Userland gives us the following काष्ठाure:
	 *
	 * काष्ठा idefloppy_क्रमmat_command अणु
	 *        पूर्णांक nblocks;
	 *        पूर्णांक blocksize;
	 *        पूर्णांक flags;
	 *        पूर्ण ;
	 *
	 * flags is a biपंचांगask, currently, the only defined flag is:
	 *
	 *        0x01 - verअगरy media after क्रमmat.
	 */
	अगर (get_user(blocks, arg) ||
			get_user(length, arg+1) ||
			get_user(flags, arg+2)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	ide_floppy_get_sfrp_bit(drive, pc);
	ide_floppy_create_क्रमmat_unit_cmd(pc, buf, blocks, length, flags);

	अगर (ide_queue_pc_tail(drive, floppy->disk, pc, buf, pc->req_xfer))
		err = -EIO;

out:
	अगर (err)
		drive->dev_flags &= ~IDE_DFLAG_FORMAT_IN_PROGRESS;
	वापस err;
पूर्ण

/*
 * Get ATAPI_FORMAT_UNIT progress indication.
 *
 * Userland gives a poपूर्णांकer to an पूर्णांक.  The पूर्णांक is set to a progress
 * indicator 0-65536, with 65536=100%.
 *
 * If the drive करोes not support क्रमmat progress indication, we just check
 * the dsc bit, and वापस either 0 or 65536.
 */

अटल पूर्णांक ide_floppy_get_क्रमmat_progress(ide_drive_t *drive,
					  काष्ठा ide_atapi_pc *pc,
					  पूर्णांक __user *arg)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	u8 sense_buf[18];
	पूर्णांक progress_indication = 0x10000;

	अगर (drive->atapi_flags & IDE_AFLAG_SRFP) अणु
		ide_create_request_sense_cmd(drive, pc);
		अगर (ide_queue_pc_tail(drive, floppy->disk, pc, sense_buf,
				      pc->req_xfer))
			वापस -EIO;

		अगर (floppy->sense_key == 2 &&
		    floppy->asc == 4 &&
		    floppy->ascq == 4)
			progress_indication = floppy->progress_indication;

		/* Else assume क्रमmat_unit has finished, and we're at 0x10000 */
	पूर्ण अन्यथा अणु
		ide_hwअगर_t *hwअगर = drive->hwअगर;
		अचिन्हित दीर्घ flags;
		u8 stat;

		local_irq_save(flags);
		stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);
		local_irq_restore(flags);

		progress_indication = ((stat & ATA_DSC) == 0) ? 0 : 0x10000;
	पूर्ण

	अगर (put_user(progress_indication, arg))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ide_floppy_lockकरोor(ide_drive_t *drive, काष्ठा ide_atapi_pc *pc,
			       अचिन्हित दीर्घ arg, अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	काष्ठा gendisk *disk = floppy->disk;
	पूर्णांक prevent = (arg && cmd != CDROMEJECT) ? 1 : 0;

	अगर (floppy->खोलोers > 1)
		वापस -EBUSY;

	ide_set_media_lock(drive, disk, prevent);

	अगर (cmd == CDROMEJECT)
		ide_करो_start_stop(drive, disk, 2);

	वापस 0;
पूर्ण

अटल पूर्णांक ide_floppy_क्रमmat_ioctl(ide_drive_t *drive, काष्ठा ide_atapi_pc *pc,
				   भ_शेषe_t mode, अचिन्हित पूर्णांक cmd,
				   व्योम __user *argp)
अणु
	चयन (cmd) अणु
	हाल IDEFLOPPY_IOCTL_FORMAT_SUPPORTED:
		वापस 0;
	हाल IDEFLOPPY_IOCTL_FORMAT_GET_CAPACITY:
		वापस ide_floppy_get_क्रमmat_capacities(drive, pc, argp);
	हाल IDEFLOPPY_IOCTL_FORMAT_START:
		अगर (!(mode & FMODE_WRITE))
			वापस -EPERM;
		वापस ide_floppy_क्रमmat_unit(drive, pc, (पूर्णांक __user *)argp);
	हाल IDEFLOPPY_IOCTL_FORMAT_GET_PROGRESS:
		वापस ide_floppy_get_क्रमmat_progress(drive, pc, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

पूर्णांक ide_floppy_ioctl(ide_drive_t *drive, काष्ठा block_device *bdev,
		     भ_शेषe_t mode, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ide_atapi_pc pc;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक err;

	mutex_lock(&ide_floppy_ioctl_mutex);
	अगर (cmd == CDROMEJECT || cmd == CDROM_LOCKDOOR) अणु
		err = ide_floppy_lockकरोor(drive, &pc, arg, cmd);
		जाओ out;
	पूर्ण

	err = ide_floppy_क्रमmat_ioctl(drive, &pc, mode, cmd, argp);
	अगर (err != -ENOTTY)
		जाओ out;

	/*
	 * skip SCSI_IOCTL_SEND_COMMAND (deprecated)
	 * and CDROM_SEND_PACKET (legacy) ioctls
	 */
	अगर (cmd != CDROM_SEND_PACKET && cmd != SCSI_IOCTL_SEND_COMMAND)
		err = scsi_cmd_blk_ioctl(bdev, mode, cmd, argp);

	अगर (err == -ENOTTY)
		err = generic_ide_ioctl(drive, bdev, cmd, arg);

out:
	mutex_unlock(&ide_floppy_ioctl_mutex);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
पूर्णांक ide_floppy_compat_ioctl(ide_drive_t *drive, काष्ठा block_device *bdev,
			    भ_शेषe_t mode, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ide_atapi_pc pc;
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक err;

	mutex_lock(&ide_floppy_ioctl_mutex);
	अगर (cmd == CDROMEJECT || cmd == CDROM_LOCKDOOR) अणु
		err = ide_floppy_lockकरोor(drive, &pc, arg, cmd);
		जाओ out;
	पूर्ण

	err = ide_floppy_क्रमmat_ioctl(drive, &pc, mode, cmd, argp);
	अगर (err != -ENOTTY)
		जाओ out;

	/*
	 * skip SCSI_IOCTL_SEND_COMMAND (deprecated)
	 * and CDROM_SEND_PACKET (legacy) ioctls
	 */
	अगर (cmd != CDROM_SEND_PACKET && cmd != SCSI_IOCTL_SEND_COMMAND)
		err = scsi_cmd_blk_ioctl(bdev, mode, cmd, argp);

	अगर (err == -ENOTTY)
		err = generic_ide_ioctl(drive, bdev, cmd, arg);

out:
	mutex_unlock(&ide_floppy_ioctl_mutex);
	वापस err;
पूर्ण
#पूर्ण_अगर
