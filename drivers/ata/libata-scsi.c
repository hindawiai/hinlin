<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  libata-scsi.c - helper library क्रम ATA
 *
 *  Copyright 2003-2004 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2004 Jeff Garzik
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available from
 *  - http://www.t10.org/
 *  - http://www.t13.org/
 */

#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <linux/libata.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/ioprपन.स>
#समावेश <linux/of.h>

#समावेश "libata.h"
#समावेश "libata-transport.h"

#घोषणा ATA_SCSI_RBUF_SIZE	576

अटल DEFINE_SPINLOCK(ata_scsi_rbuf_lock);
अटल u8 ata_scsi_rbuf[ATA_SCSI_RBUF_SIZE];

प्रकार अचिन्हित पूर्णांक (*ata_xlat_func_t)(काष्ठा ata_queued_cmd *qc);

अटल काष्ठा ata_device *__ata_scsi_find_dev(काष्ठा ata_port *ap,
					स्थिर काष्ठा scsi_device *scsidev);

#घोषणा RW_RECOVERY_MPAGE 0x1
#घोषणा RW_RECOVERY_MPAGE_LEN 12
#घोषणा CACHE_MPAGE 0x8
#घोषणा CACHE_MPAGE_LEN 20
#घोषणा CONTROL_MPAGE 0xa
#घोषणा CONTROL_MPAGE_LEN 12
#घोषणा ALL_MPAGES 0x3f
#घोषणा ALL_SUB_MPAGES 0xff


अटल स्थिर u8 def_rw_recovery_mpage[RW_RECOVERY_MPAGE_LEN] = अणु
	RW_RECOVERY_MPAGE,
	RW_RECOVERY_MPAGE_LEN - 2,
	(1 << 7),	/* AWRE */
	0,		/* पढ़ो retry count */
	0, 0, 0, 0,
	0,		/* ग_लिखो retry count */
	0, 0, 0
पूर्ण;

अटल स्थिर u8 def_cache_mpage[CACHE_MPAGE_LEN] = अणु
	CACHE_MPAGE,
	CACHE_MPAGE_LEN - 2,
	0,		/* contains WCE, needs to be 0 क्रम logic */
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,		/* contains DRA, needs to be 0 क्रम logic */
	0, 0, 0, 0, 0, 0, 0
पूर्ण;

अटल स्थिर u8 def_control_mpage[CONTROL_MPAGE_LEN] = अणु
	CONTROL_MPAGE,
	CONTROL_MPAGE_LEN - 2,
	2,	/* DSENSE=0, GLTSD=1 */
	0,	/* [QAM+QERR may be 1, see 05-359r1] */
	0, 0, 0, 0, 0xff, 0xff,
	0, 30	/* extended self test समय, see 05-359r1 */
पूर्ण;

अटल sमाप_प्रकार ata_scsi_park_show(काष्ठा device *device,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(device);
	काष्ठा ata_port *ap;
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ now;
	अचिन्हित पूर्णांक msecs;
	पूर्णांक rc = 0;

	ap = ata_shost_to_port(sdev->host);

	spin_lock_irq(ap->lock);
	dev = ata_scsi_find_dev(ap, sdev);
	अगर (!dev) अणु
		rc = -ENODEV;
		जाओ unlock;
	पूर्ण
	अगर (dev->flags & ATA_DFLAG_NO_UNLOAD) अणु
		rc = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	link = dev->link;
	now = jअगरfies;
	अगर (ap->pflags & ATA_PFLAG_EH_IN_PROGRESS &&
	    link->eh_context.unloaded_mask & (1 << dev->devno) &&
	    समय_after(dev->unpark_deadline, now))
		msecs = jअगरfies_to_msecs(dev->unpark_deadline - now);
	अन्यथा
		msecs = 0;

unlock:
	spin_unlock_irq(ap->lock);

	वापस rc ? rc : snम_लिखो(buf, 20, "%u\n", msecs);
पूर्ण

अटल sमाप_प्रकार ata_scsi_park_store(काष्ठा device *device,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(device);
	काष्ठा ata_port *ap;
	काष्ठा ata_device *dev;
	दीर्घ पूर्णांक input;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	rc = kम_से_दीर्घ(buf, 10, &input);
	अगर (rc)
		वापस rc;
	अगर (input < -2)
		वापस -EINVAL;
	अगर (input > ATA_TMOUT_MAX_PARK) अणु
		rc = -EOVERFLOW;
		input = ATA_TMOUT_MAX_PARK;
	पूर्ण

	ap = ata_shost_to_port(sdev->host);

	spin_lock_irqsave(ap->lock, flags);
	dev = ata_scsi_find_dev(ap, sdev);
	अगर (unlikely(!dev)) अणु
		rc = -ENODEV;
		जाओ unlock;
	पूर्ण
	अगर (dev->class != ATA_DEV_ATA &&
	    dev->class != ATA_DEV_ZAC) अणु
		rc = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	अगर (input >= 0) अणु
		अगर (dev->flags & ATA_DFLAG_NO_UNLOAD) अणु
			rc = -EOPNOTSUPP;
			जाओ unlock;
		पूर्ण

		dev->unpark_deadline = ata_deadline(jअगरfies, input);
		dev->link->eh_info.dev_action[dev->devno] |= ATA_EH_PARK;
		ata_port_schedule_eh(ap);
		complete(&ap->park_req_pending);
	पूर्ण अन्यथा अणु
		चयन (input) अणु
		हाल -1:
			dev->flags &= ~ATA_DFLAG_NO_UNLOAD;
			अवरोध;
		हाल -2:
			dev->flags |= ATA_DFLAG_NO_UNLOAD;
			अवरोध;
		पूर्ण
	पूर्ण
unlock:
	spin_unlock_irqrestore(ap->lock, flags);

	वापस rc ? rc : len;
पूर्ण
DEVICE_ATTR(unload_heads, S_IRUGO | S_IWUSR,
	    ata_scsi_park_show, ata_scsi_park_store);
EXPORT_SYMBOL_GPL(dev_attr_unload_heads);

व्योम ata_scsi_set_sense(काष्ठा ata_device *dev, काष्ठा scsi_cmnd *cmd,
			u8 sk, u8 asc, u8 ascq)
अणु
	bool d_sense = (dev->flags & ATA_DFLAG_D_SENSE);

	अगर (!cmd)
		वापस;

	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	scsi_build_sense_buffer(d_sense, cmd->sense_buffer, sk, asc, ascq);
पूर्ण

व्योम ata_scsi_set_sense_inक्रमmation(काष्ठा ata_device *dev,
				    काष्ठा scsi_cmnd *cmd,
				    स्थिर काष्ठा ata_taskfile *tf)
अणु
	u64 inक्रमmation;

	अगर (!cmd)
		वापस;

	inक्रमmation = ata_tf_पढ़ो_block(tf, dev);
	अगर (inक्रमmation == U64_MAX)
		वापस;

	scsi_set_sense_inक्रमmation(cmd->sense_buffer,
				   SCSI_SENSE_BUFFERSIZE, inक्रमmation);
पूर्ण

अटल व्योम ata_scsi_set_invalid_field(काष्ठा ata_device *dev,
				       काष्ठा scsi_cmnd *cmd, u16 field, u8 bit)
अणु
	ata_scsi_set_sense(dev, cmd, ILLEGAL_REQUEST, 0x24, 0x0);
	/* "Invalid field in CDB" */
	scsi_set_sense_field_poपूर्णांकer(cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE,
				     field, bit, 1);
पूर्ण

अटल व्योम ata_scsi_set_invalid_parameter(काष्ठा ata_device *dev,
					   काष्ठा scsi_cmnd *cmd, u16 field)
अणु
	/* "Invalid field in parameter list" */
	ata_scsi_set_sense(dev, cmd, ILLEGAL_REQUEST, 0x26, 0x0);
	scsi_set_sense_field_poपूर्णांकer(cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE,
				     field, 0xff, 0);
पूर्ण

काष्ठा device_attribute *ata_common_sdev_attrs[] = अणु
	&dev_attr_unload_heads,
	शून्य
पूर्ण;
EXPORT_SYMBOL_GPL(ata_common_sdev_attrs);

/**
 *	ata_std_bios_param - generic bios head/sector/cylinder calculator used by sd.
 *	@sdev: SCSI device क्रम which BIOS geometry is to be determined
 *	@bdev: block device associated with @sdev
 *	@capacity: capacity of SCSI device
 *	@geom: location to which geometry will be output
 *
 *	Generic bios head/sector/cylinder calculator
 *	used by sd. Most BIOSes nowadays expect a XXX/255/16  (CHS)
 *	mapping. Some situations may arise where the disk is not
 *	bootable अगर this is not used.
 *
 *	LOCKING:
 *	Defined by the SCSI layer.  We करोn't really care.
 *
 *	RETURNS:
 *	Zero.
 */
पूर्णांक ata_std_bios_param(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		       sector_t capacity, पूर्णांक geom[])
अणु
	geom[0] = 255;
	geom[1] = 63;
	sector_भाग(capacity, 255*63);
	geom[2] = capacity;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_std_bios_param);

/**
 *	ata_scsi_unlock_native_capacity - unlock native capacity
 *	@sdev: SCSI device to adjust device capacity क्रम
 *
 *	This function is called अगर a partition on @sdev extends beyond
 *	the end of the device.  It requests EH to unlock HPA.
 *
 *	LOCKING:
 *	Defined by the SCSI layer.  Might sleep.
 */
व्योम ata_scsi_unlock_native_capacity(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ap->lock, flags);

	dev = ata_scsi_find_dev(ap, sdev);
	अगर (dev && dev->n_sectors < dev->n_native_sectors) अणु
		dev->flags |= ATA_DFLAG_UNLOCK_HPA;
		dev->link->eh_info.action |= ATA_EH_RESET;
		ata_port_schedule_eh(ap);
	पूर्ण

	spin_unlock_irqrestore(ap->lock, flags);
	ata_port_रुको_eh(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_unlock_native_capacity);

/**
 *	ata_get_identity - Handler क्रम HDIO_GET_IDENTITY ioctl
 *	@ap: target port
 *	@sdev: SCSI device to get identअगरy data क्रम
 *	@arg: User buffer area क्रम identअगरy data
 *
 *	LOCKING:
 *	Defined by the SCSI layer.  We करोn't really care.
 *
 *	RETURNS:
 *	Zero on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक ata_get_identity(काष्ठा ata_port *ap, काष्ठा scsi_device *sdev,
			    व्योम __user *arg)
अणु
	काष्ठा ata_device *dev = ata_scsi_find_dev(ap, sdev);
	u16 __user *dst = arg;
	अक्षर buf[40];

	अगर (!dev)
		वापस -ENOMSG;

	अगर (copy_to_user(dst, dev->id, ATA_ID_WORDS * माप(u16)))
		वापस -EFAULT;

	ata_id_string(dev->id, buf, ATA_ID_PROD, ATA_ID_PROD_LEN);
	अगर (copy_to_user(dst + ATA_ID_PROD, buf, ATA_ID_PROD_LEN))
		वापस -EFAULT;

	ata_id_string(dev->id, buf, ATA_ID_FW_REV, ATA_ID_FW_REV_LEN);
	अगर (copy_to_user(dst + ATA_ID_FW_REV, buf, ATA_ID_FW_REV_LEN))
		वापस -EFAULT;

	ata_id_string(dev->id, buf, ATA_ID_SERNO, ATA_ID_SERNO_LEN);
	अगर (copy_to_user(dst + ATA_ID_SERNO, buf, ATA_ID_SERNO_LEN))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 *	ata_cmd_ioctl - Handler क्रम HDIO_DRIVE_CMD ioctl
 *	@scsidev: Device to which we are issuing command
 *	@arg: User provided data क्रम issuing command
 *
 *	LOCKING:
 *	Defined by the SCSI layer.  We करोn't really care.
 *
 *	RETURNS:
 *	Zero on success, negative त्रुटि_सं on error.
 */
पूर्णांक ata_cmd_ioctl(काष्ठा scsi_device *scsidev, व्योम __user *arg)
अणु
	पूर्णांक rc = 0;
	u8 sensebuf[SCSI_SENSE_BUFFERSIZE];
	u8 scsi_cmd[MAX_COMMAND_SIZE];
	u8 args[4], *argbuf = शून्य;
	पूर्णांक argsize = 0;
	क्रमागत dma_data_direction data_dir;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक cmd_result;

	अगर (arg == शून्य)
		वापस -EINVAL;

	अगर (copy_from_user(args, arg, माप(args)))
		वापस -EFAULT;

	स_रखो(sensebuf, 0, माप(sensebuf));
	स_रखो(scsi_cmd, 0, माप(scsi_cmd));

	अगर (args[3]) अणु
		argsize = ATA_SECT_SIZE * args[3];
		argbuf = kदो_स्मृति(argsize, GFP_KERNEL);
		अगर (argbuf == शून्य) अणु
			rc = -ENOMEM;
			जाओ error;
		पूर्ण

		scsi_cmd[1]  = (4 << 1); /* PIO Data-in */
		scsi_cmd[2]  = 0x0e;     /* no off.line or cc, पढ़ो from dev,
					    block count in sector count field */
		data_dir = DMA_FROM_DEVICE;
	पूर्ण अन्यथा अणु
		scsi_cmd[1]  = (3 << 1); /* Non-data */
		scsi_cmd[2]  = 0x20;     /* cc but no off.line or data xfer */
		data_dir = DMA_NONE;
	पूर्ण

	scsi_cmd[0] = ATA_16;

	scsi_cmd[4] = args[2];
	अगर (args[0] == ATA_CMD_SMART) अणु /* hack -- ide driver करोes this too */
		scsi_cmd[6]  = args[3];
		scsi_cmd[8]  = args[1];
		scsi_cmd[10] = ATA_SMART_LBAM_PASS;
		scsi_cmd[12] = ATA_SMART_LBAH_PASS;
	पूर्ण अन्यथा अणु
		scsi_cmd[6]  = args[1];
	पूर्ण
	scsi_cmd[14] = args[0];

	/* Good values क्रम समयout and retries?  Values below
	   from scsi_ioctl_send_command() क्रम शेष हाल... */
	cmd_result = scsi_execute(scsidev, scsi_cmd, data_dir, argbuf, argsize,
				  sensebuf, &sshdr, (10*HZ), 5, 0, 0, शून्य);

	अगर (driver_byte(cmd_result) == DRIVER_SENSE) अणु/* sense data available */
		u8 *desc = sensebuf + 8;
		cmd_result &= ~(0xFF<<24); /* DRIVER_SENSE is not an error */

		/* If we set cc then ATA pass-through will cause a
		 * check condition even अगर no error. Filter that. */
		अगर (cmd_result & SAM_STAT_CHECK_CONDITION) अणु
			अगर (sshdr.sense_key == RECOVERED_ERROR &&
			    sshdr.asc == 0 && sshdr.ascq == 0x1d)
				cmd_result &= ~SAM_STAT_CHECK_CONDITION;
		पूर्ण

		/* Send userspace a few ATA रेजिस्टरs (same as drivers/ide) */
		अगर (sensebuf[0] == 0x72 &&	/* क्रमmat is "descriptor" */
		    desc[0] == 0x09) अणु		/* code is "ATA Descriptor" */
			args[0] = desc[13];	/* status */
			args[1] = desc[3];	/* error */
			args[2] = desc[5];	/* sector count (0:7) */
			अगर (copy_to_user(arg, args, माप(args)))
				rc = -EFAULT;
		पूर्ण
	पूर्ण


	अगर (cmd_result) अणु
		rc = -EIO;
		जाओ error;
	पूर्ण

	अगर ((argbuf)
	 && copy_to_user(arg + माप(args), argbuf, argsize))
		rc = -EFAULT;
error:
	kमुक्त(argbuf);
	वापस rc;
पूर्ण

/**
 *	ata_task_ioctl - Handler क्रम HDIO_DRIVE_TASK ioctl
 *	@scsidev: Device to which we are issuing command
 *	@arg: User provided data क्रम issuing command
 *
 *	LOCKING:
 *	Defined by the SCSI layer.  We करोn't really care.
 *
 *	RETURNS:
 *	Zero on success, negative त्रुटि_सं on error.
 */
पूर्णांक ata_task_ioctl(काष्ठा scsi_device *scsidev, व्योम __user *arg)
अणु
	पूर्णांक rc = 0;
	u8 sensebuf[SCSI_SENSE_BUFFERSIZE];
	u8 scsi_cmd[MAX_COMMAND_SIZE];
	u8 args[7];
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक cmd_result;

	अगर (arg == शून्य)
		वापस -EINVAL;

	अगर (copy_from_user(args, arg, माप(args)))
		वापस -EFAULT;

	स_रखो(sensebuf, 0, माप(sensebuf));
	स_रखो(scsi_cmd, 0, माप(scsi_cmd));
	scsi_cmd[0]  = ATA_16;
	scsi_cmd[1]  = (3 << 1); /* Non-data */
	scsi_cmd[2]  = 0x20;     /* cc but no off.line or data xfer */
	scsi_cmd[4]  = args[1];
	scsi_cmd[6]  = args[2];
	scsi_cmd[8]  = args[3];
	scsi_cmd[10] = args[4];
	scsi_cmd[12] = args[5];
	scsi_cmd[13] = args[6] & 0x4f;
	scsi_cmd[14] = args[0];

	/* Good values क्रम समयout and retries?  Values below
	   from scsi_ioctl_send_command() क्रम शेष हाल... */
	cmd_result = scsi_execute(scsidev, scsi_cmd, DMA_NONE, शून्य, 0,
				sensebuf, &sshdr, (10*HZ), 5, 0, 0, शून्य);

	अगर (driver_byte(cmd_result) == DRIVER_SENSE) अणु/* sense data available */
		u8 *desc = sensebuf + 8;
		cmd_result &= ~(0xFF<<24); /* DRIVER_SENSE is not an error */

		/* If we set cc then ATA pass-through will cause a
		 * check condition even अगर no error. Filter that. */
		अगर (cmd_result & SAM_STAT_CHECK_CONDITION) अणु
			अगर (sshdr.sense_key == RECOVERED_ERROR &&
			    sshdr.asc == 0 && sshdr.ascq == 0x1d)
				cmd_result &= ~SAM_STAT_CHECK_CONDITION;
		पूर्ण

		/* Send userspace ATA रेजिस्टरs */
		अगर (sensebuf[0] == 0x72 &&	/* क्रमmat is "descriptor" */
				desc[0] == 0x09) अणु/* code is "ATA Descriptor" */
			args[0] = desc[13];	/* status */
			args[1] = desc[3];	/* error */
			args[2] = desc[5];	/* sector count (0:7) */
			args[3] = desc[7];	/* lbal */
			args[4] = desc[9];	/* lbam */
			args[5] = desc[11];	/* lbah */
			args[6] = desc[12];	/* select */
			अगर (copy_to_user(arg, args, माप(args)))
				rc = -EFAULT;
		पूर्ण
	पूर्ण

	अगर (cmd_result) अणु
		rc = -EIO;
		जाओ error;
	पूर्ण

 error:
	वापस rc;
पूर्ण

अटल पूर्णांक ata_ioc32(काष्ठा ata_port *ap)
अणु
	अगर (ap->flags & ATA_FLAG_PIO_DMA)
		वापस 1;
	अगर (ap->pflags & ATA_PFLAG_PIO32)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * This handles both native and compat commands, so anything added
 * here must have a compatible argument, or check in_compat_syscall()
 */
पूर्णांक ata_sas_scsi_ioctl(काष्ठा ata_port *ap, काष्ठा scsi_device *scsidev,
		     अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक rc = -EINVAL;
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु
	हाल HDIO_GET_32BIT:
		spin_lock_irqsave(ap->lock, flags);
		val = ata_ioc32(ap);
		spin_unlock_irqrestore(ap->lock, flags);
#अगर_घोषित CONFIG_COMPAT
		अगर (in_compat_syscall())
			वापस put_user(val, (compat_uदीर्घ_t __user *)arg);
#पूर्ण_अगर
		वापस put_user(val, (अचिन्हित दीर्घ __user *)arg);

	हाल HDIO_SET_32BIT:
		val = (अचिन्हित दीर्घ) arg;
		rc = 0;
		spin_lock_irqsave(ap->lock, flags);
		अगर (ap->pflags & ATA_PFLAG_PIO32CHANGE) अणु
			अगर (val)
				ap->pflags |= ATA_PFLAG_PIO32;
			अन्यथा
				ap->pflags &= ~ATA_PFLAG_PIO32;
		पूर्ण अन्यथा अणु
			अगर (val != ata_ioc32(ap))
				rc = -EINVAL;
		पूर्ण
		spin_unlock_irqrestore(ap->lock, flags);
		वापस rc;

	हाल HDIO_GET_IDENTITY:
		वापस ata_get_identity(ap, scsidev, arg);

	हाल HDIO_DRIVE_CMD:
		अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		वापस ata_cmd_ioctl(scsidev, arg);

	हाल HDIO_DRIVE_TASK:
		अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		वापस ata_task_ioctl(scsidev, arg);

	शेष:
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_scsi_ioctl);

पूर्णांक ata_scsi_ioctl(काष्ठा scsi_device *scsidev, अचिन्हित पूर्णांक cmd,
		   व्योम __user *arg)
अणु
	वापस ata_sas_scsi_ioctl(ata_shost_to_port(scsidev->host),
				scsidev, cmd, arg);
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_ioctl);

/**
 *	ata_scsi_qc_new - acquire new ata_queued_cmd reference
 *	@dev: ATA device to which the new command is attached
 *	@cmd: SCSI command that originated this ATA command
 *
 *	Obtain a reference to an unused ata_queued_cmd काष्ठाure,
 *	which is the basic libata काष्ठाure representing a single
 *	ATA command sent to the hardware.
 *
 *	If a command was available, fill in the SCSI-specअगरic
 *	portions of the काष्ठाure with inक्रमmation on the
 *	current command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Command allocated, or %शून्य अगर none available.
 */
अटल काष्ठा ata_queued_cmd *ata_scsi_qc_new(काष्ठा ata_device *dev,
					      काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ata_queued_cmd *qc;

	qc = ata_qc_new_init(dev, cmd->request->tag);
	अगर (qc) अणु
		qc->scsicmd = cmd;
		qc->scsiकरोne = cmd->scsi_करोne;

		qc->sg = scsi_sglist(cmd);
		qc->n_elem = scsi_sg_count(cmd);

		अगर (cmd->request->rq_flags & RQF_QUIET)
			qc->flags |= ATA_QCFLAG_QUIET;
	पूर्ण अन्यथा अणु
		cmd->result = (DID_OK << 16) | (QUEUE_FULL << 1);
		cmd->scsi_करोne(cmd);
	पूर्ण

	वापस qc;
पूर्ण

अटल व्योम ata_qc_set_pc_nbytes(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;

	qc->extrabytes = scmd->extra_len;
	qc->nbytes = scsi_bufflen(scmd) + qc->extrabytes;
पूर्ण

/**
 *	ata_dump_status - user मित्रly display of error info
 *	@id: id of the port in question
 *	@tf: ptr to filled out taskfile
 *
 *	Decode and dump the ATA error/status रेजिस्टरs क्रम the user so
 *	that they have some idea what really happened at the non
 *	make-believe layer.
 *
 *	LOCKING:
 *	inherited from caller
 */
अटल व्योम ata_dump_status(अचिन्हित id, काष्ठा ata_taskfile *tf)
अणु
	u8 stat = tf->command, err = tf->feature;

	pr_warn("ata%u: status=0x%02x { ", id, stat);
	अगर (stat & ATA_BUSY) अणु
		pr_cont("Busy }\n");	/* Data is not valid in this हाल */
	पूर्ण अन्यथा अणु
		अगर (stat & ATA_DRDY)	pr_cont("DriveReady ");
		अगर (stat & ATA_DF)	pr_cont("DeviceFault ");
		अगर (stat & ATA_DSC)	pr_cont("SeekComplete ");
		अगर (stat & ATA_DRQ)	pr_cont("DataRequest ");
		अगर (stat & ATA_CORR)	pr_cont("CorrectedError ");
		अगर (stat & ATA_SENSE)	pr_cont("Sense ");
		अगर (stat & ATA_ERR)	pr_cont("Error ");
		pr_cont("}\n");

		अगर (err) अणु
			pr_warn("ata%u: error=0x%02x { ", id, err);
			अगर (err & ATA_ABORTED)	pr_cont("DriveStatusError ");
			अगर (err & ATA_ICRC) अणु
				अगर (err & ATA_ABORTED)
						pr_cont("BadCRC ");
				अन्यथा		pr_cont("Sector ");
			पूर्ण
			अगर (err & ATA_UNC)	pr_cont("UncorrectableError ");
			अगर (err & ATA_IDNF)	pr_cont("SectorIdNotFound ");
			अगर (err & ATA_TRK0NF)	pr_cont("TrackZeroNotFound ");
			अगर (err & ATA_AMNF)	pr_cont("AddrMarkNotFound ");
			pr_cont("}\n");
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	ata_to_sense_error - convert ATA error to SCSI error
 *	@id: ATA device number
 *	@drv_stat: value contained in ATA status रेजिस्टर
 *	@drv_err: value contained in ATA error रेजिस्टर
 *	@sk: the sense key we'll fill out
 *	@asc: the additional sense code we'll fill out
 *	@ascq: the additional sense code qualअगरier we'll fill out
 *	@verbose: be verbose
 *
 *	Converts an ATA error पूर्णांकo a SCSI error.  Fill out poपूर्णांकers to
 *	SK, ASC, and ASCQ bytes क्रम later use in fixed or descriptor
 *	क्रमmat sense blocks.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल व्योम ata_to_sense_error(अचिन्हित id, u8 drv_stat, u8 drv_err, u8 *sk,
			       u8 *asc, u8 *ascq, पूर्णांक verbose)
अणु
	पूर्णांक i;

	/* Based on the 3ware driver translation table */
	अटल स्थिर अचिन्हित अक्षर sense_table[][4] = अणु
		/* BBD|ECC|ID|MAR */
		अणु0xd1,		ABORTED_COMMAND, 0x00, 0x00पूर्ण,
			// Device busy                  Aborted command
		/* BBD|ECC|ID */
		अणु0xd0,		ABORTED_COMMAND, 0x00, 0x00पूर्ण,
			// Device busy                  Aborted command
		/* ECC|MC|MARK */
		अणु0x61,		HARDWARE_ERROR, 0x00, 0x00पूर्ण,
			// Device fault                 Hardware error
		/* ICRC|ABRT */		/* NB: ICRC & !ABRT is BBD */
		अणु0x84,		ABORTED_COMMAND, 0x47, 0x00पूर्ण,
			// Data CRC error               SCSI parity error
		/* MC|ID|ABRT|TRK0|MARK */
		अणु0x37,		NOT_READY, 0x04, 0x00पूर्ण,
			// Unit offline                 Not पढ़ोy
		/* MCR|MARK */
		अणु0x09,		NOT_READY, 0x04, 0x00पूर्ण,
			// Unrecovered disk error       Not पढ़ोy
		/*  Bad address mark */
		अणु0x01,		MEDIUM_ERROR, 0x13, 0x00पूर्ण,
			// Address mark not found क्रम data field
		/* TRK0 - Track 0 not found */
		अणु0x02,		HARDWARE_ERROR, 0x00, 0x00पूर्ण,
			// Hardware error
		/* Abort: 0x04 is not translated here, see below */
		/* Media change request */
		अणु0x08,		NOT_READY, 0x04, 0x00पूर्ण,
			// FIXME: faking offline
		/* SRV/IDNF - ID not found */
		अणु0x10,		ILLEGAL_REQUEST, 0x21, 0x00पूर्ण,
			// Logical address out of range
		/* MC - Media Changed */
		अणु0x20,		UNIT_ATTENTION, 0x28, 0x00पूर्ण,
			// Not पढ़ोy to पढ़ोy change, medium may have changed
		/* ECC - Uncorrectable ECC error */
		अणु0x40,		MEDIUM_ERROR, 0x11, 0x04पूर्ण,
			// Unrecovered पढ़ो error
		/* BBD - block marked bad */
		अणु0x80,		MEDIUM_ERROR, 0x11, 0x04पूर्ण,
			// Block marked bad	Medium error, unrecovered पढ़ो error
		अणु0xFF, 0xFF, 0xFF, 0xFFपूर्ण, // END mark
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर stat_table[][4] = अणु
		/* Must be first because BUSY means no other bits valid */
		अणु0x80,		ABORTED_COMMAND, 0x47, 0x00पूर्ण,
		// Busy, fake parity क्रम now
		अणु0x40,		ILLEGAL_REQUEST, 0x21, 0x04पूर्ण,
		// Device पढ़ोy, unaligned ग_लिखो command
		अणु0x20,		HARDWARE_ERROR,  0x44, 0x00पूर्ण,
		// Device fault, पूर्णांकernal target failure
		अणु0x08,		ABORTED_COMMAND, 0x47, 0x00पूर्ण,
		// Timed out in xfer, fake parity क्रम now
		अणु0x04,		RECOVERED_ERROR, 0x11, 0x00पूर्ण,
		// Recovered ECC error	  Medium error, recovered
		अणु0xFF, 0xFF, 0xFF, 0xFFपूर्ण, // END mark
	पूर्ण;

	/*
	 *	Is this an error we can process/parse
	 */
	अगर (drv_stat & ATA_BUSY) अणु
		drv_err = 0;	/* Ignore the err bits, they're invalid */
	पूर्ण

	अगर (drv_err) अणु
		/* Look क्रम drv_err */
		क्रम (i = 0; sense_table[i][0] != 0xFF; i++) अणु
			/* Look क्रम best matches first */
			अगर ((sense_table[i][0] & drv_err) ==
			    sense_table[i][0]) अणु
				*sk = sense_table[i][1];
				*asc = sense_table[i][2];
				*ascq = sense_table[i][3];
				जाओ translate_करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Fall back to पूर्णांकerpreting status bits.  Note that अगर the drv_err
	 * has only the ABRT bit set, we decode drv_stat.  ABRT by itself
	 * is not descriptive enough.
	 */
	क्रम (i = 0; stat_table[i][0] != 0xFF; i++) अणु
		अगर (stat_table[i][0] & drv_stat) अणु
			*sk = stat_table[i][1];
			*asc = stat_table[i][2];
			*ascq = stat_table[i][3];
			जाओ translate_करोne;
		पूर्ण
	पूर्ण

	/*
	 * We need a sensible error वापस here, which is tricky, and one
	 * that won't cause people to करो things like वापस a disk wrongly.
	 */
	*sk = ABORTED_COMMAND;
	*asc = 0x00;
	*ascq = 0x00;

 translate_करोne:
	अगर (verbose)
		pr_err("ata%u: translated ATA stat/err 0x%02x/%02x to SCSI SK/ASC/ASCQ 0x%x/%02x/%02x\n",
		       id, drv_stat, drv_err, *sk, *asc, *ascq);
	वापस;
पूर्ण

/*
 *	ata_gen_passthru_sense - Generate check condition sense block.
 *	@qc: Command that completed.
 *
 *	This function is specअगरic to the ATA descriptor क्रमmat sense
 *	block specअगरied क्रम the ATA pass through commands.  Regardless
 *	of whether the command errored or not, वापस a sense
 *	block. Copy all controller रेजिस्टरs पूर्णांकo the sense
 *	block. If there was no error, we get the request from an ATA
 *	passthrough command, so we use the following sense data:
 *	sk = RECOVERED ERROR
 *	asc,ascq = ATA PASS-THROUGH INFORMATION AVAILABLE
 *      
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम ata_gen_passthru_sense(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;
	काष्ठा ata_taskfile *tf = &qc->result_tf;
	अचिन्हित अक्षर *sb = cmd->sense_buffer;
	अचिन्हित अक्षर *desc = sb + 8;
	पूर्णांक verbose = qc->ap->ops->error_handler == शून्य;
	u8 sense_key, asc, ascq;

	स_रखो(sb, 0, SCSI_SENSE_BUFFERSIZE);

	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	/*
	 * Use ata_to_sense_error() to map status रेजिस्टर bits
	 * onto sense key, asc & ascq.
	 */
	अगर (qc->err_mask ||
	    tf->command & (ATA_BUSY | ATA_DF | ATA_ERR | ATA_DRQ)) अणु
		ata_to_sense_error(qc->ap->prपूर्णांक_id, tf->command, tf->feature,
				   &sense_key, &asc, &ascq, verbose);
		ata_scsi_set_sense(qc->dev, cmd, sense_key, asc, ascq);
	पूर्ण अन्यथा अणु
		/*
		 * ATA PASS-THROUGH INFORMATION AVAILABLE
		 * Always in descriptor क्रमmat sense.
		 */
		scsi_build_sense_buffer(1, cmd->sense_buffer,
					RECOVERED_ERROR, 0, 0x1D);
	पूर्ण

	अगर ((cmd->sense_buffer[0] & 0x7f) >= 0x72) अणु
		u8 len;

		/* descriptor क्रमmat */
		len = sb[7];
		desc = (अक्षर *)scsi_sense_desc_find(sb, len + 8, 9);
		अगर (!desc) अणु
			अगर (SCSI_SENSE_BUFFERSIZE < len + 14)
				वापस;
			sb[7] = len + 14;
			desc = sb + 8 + len;
		पूर्ण
		desc[0] = 9;
		desc[1] = 12;
		/*
		 * Copy रेजिस्टरs पूर्णांकo sense buffer.
		 */
		desc[2] = 0x00;
		desc[3] = tf->feature;	/* == error reg */
		desc[5] = tf->nsect;
		desc[7] = tf->lbal;
		desc[9] = tf->lbam;
		desc[11] = tf->lbah;
		desc[12] = tf->device;
		desc[13] = tf->command; /* == status reg */

		/*
		 * Fill in Extend bit, and the high order bytes
		 * अगर applicable.
		 */
		अगर (tf->flags & ATA_TFLAG_LBA48) अणु
			desc[2] |= 0x01;
			desc[4] = tf->hob_nsect;
			desc[6] = tf->hob_lbal;
			desc[8] = tf->hob_lbam;
			desc[10] = tf->hob_lbah;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fixed sense क्रमmat */
		desc[0] = tf->feature;
		desc[1] = tf->command; /* status */
		desc[2] = tf->device;
		desc[3] = tf->nsect;
		desc[7] = 0;
		अगर (tf->flags & ATA_TFLAG_LBA48)  अणु
			desc[8] |= 0x80;
			अगर (tf->hob_nsect)
				desc[8] |= 0x40;
			अगर (tf->hob_lbal || tf->hob_lbam || tf->hob_lbah)
				desc[8] |= 0x20;
		पूर्ण
		desc[9] = tf->lbal;
		desc[10] = tf->lbam;
		desc[11] = tf->lbah;
	पूर्ण
पूर्ण

/**
 *	ata_gen_ata_sense - generate a SCSI fixed sense block
 *	@qc: Command that we are erroring out
 *
 *	Generate sense block क्रम a failed ATA command @qc.  Descriptor
 *	क्रमmat is used to accommodate LBA48 block address.
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम ata_gen_ata_sense(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;
	काष्ठा ata_taskfile *tf = &qc->result_tf;
	अचिन्हित अक्षर *sb = cmd->sense_buffer;
	पूर्णांक verbose = qc->ap->ops->error_handler == शून्य;
	u64 block;
	u8 sense_key, asc, ascq;

	स_रखो(sb, 0, SCSI_SENSE_BUFFERSIZE);

	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	अगर (ata_dev_disabled(dev)) अणु
		/* Device disabled after error recovery */
		/* LOGICAL UNIT NOT READY, HARD RESET REQUIRED */
		ata_scsi_set_sense(dev, cmd, NOT_READY, 0x04, 0x21);
		वापस;
	पूर्ण
	/* Use ata_to_sense_error() to map status रेजिस्टर bits
	 * onto sense key, asc & ascq.
	 */
	अगर (qc->err_mask ||
	    tf->command & (ATA_BUSY | ATA_DF | ATA_ERR | ATA_DRQ)) अणु
		ata_to_sense_error(qc->ap->prपूर्णांक_id, tf->command, tf->feature,
				   &sense_key, &asc, &ascq, verbose);
		ata_scsi_set_sense(dev, cmd, sense_key, asc, ascq);
	पूर्ण अन्यथा अणु
		/* Could not decode error */
		ata_dev_warn(dev, "could not decode error status 0x%x err_mask 0x%x\n",
			     tf->command, qc->err_mask);
		ata_scsi_set_sense(dev, cmd, ABORTED_COMMAND, 0, 0);
		वापस;
	पूर्ण

	block = ata_tf_पढ़ो_block(&qc->result_tf, dev);
	अगर (block == U64_MAX)
		वापस;

	scsi_set_sense_inक्रमmation(sb, SCSI_SENSE_BUFFERSIZE, block);
पूर्ण

व्योम ata_scsi_sdev_config(काष्ठा scsi_device *sdev)
अणु
	sdev->use_10_क्रम_rw = 1;
	sdev->use_10_क्रम_ms = 1;
	sdev->no_ग_लिखो_same = 1;

	/* Schedule policy is determined by ->qc_defer() callback and
	 * it needs to see every deferred qc.  Set dev_blocked to 1 to
	 * prevent SCSI midlayer from स्वतःmatically deferring
	 * requests.
	 */
	sdev->max_device_blocked = 1;
पूर्ण

/**
 *	ata_scsi_dma_need_drain - Check whether data transfer may overflow
 *	@rq: request to be checked
 *
 *	ATAPI commands which transfer variable length data to host
 *	might overflow due to application error or hardware bug.  This
 *	function checks whether overflow should be drained and ignored
 *	क्रम @request.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	1 अगर ; otherwise, 0.
 */
bool ata_scsi_dma_need_drain(काष्ठा request *rq)
अणु
	वापस atapi_cmd_type(scsi_req(rq)->cmd[0]) == ATAPI_MISC;
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_dma_need_drain);

पूर्णांक ata_scsi_dev_config(काष्ठा scsi_device *sdev, काष्ठा ata_device *dev)
अणु
	काष्ठा request_queue *q = sdev->request_queue;

	अगर (!ata_id_has_unload(dev->id))
		dev->flags |= ATA_DFLAG_NO_UNLOAD;

	/* configure max sectors */
	blk_queue_max_hw_sectors(q, dev->max_sectors);

	अगर (dev->class == ATA_DEV_ATAPI) अणु
		sdev->sector_size = ATA_SECT_SIZE;

		/* set DMA padding */
		blk_queue_update_dma_pad(q, ATA_DMA_PAD_SZ - 1);

		/* make room क्रम appending the drain */
		blk_queue_max_segments(q, queue_max_segments(q) - 1);

		sdev->dma_drain_len = ATAPI_MAX_DRAIN;
		sdev->dma_drain_buf = kदो_स्मृति(sdev->dma_drain_len, GFP_NOIO);
		अगर (!sdev->dma_drain_buf) अणु
			ata_dev_err(dev, "drain buffer allocation failed\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		sdev->sector_size = ata_id_logical_sector_size(dev->id);
		sdev->manage_start_stop = 1;
	पूर्ण

	/*
	 * ata_pio_sectors() expects buffer क्रम each sector to not cross
	 * page boundary.  Enक्रमce it by requiring buffers to be sector
	 * aligned, which works अगरf sector_size is not larger than
	 * PAGE_SIZE.  ATAPI devices also need the alignment as
	 * IDENTIFY_PACKET is executed as ATA_PROT_PIO.
	 */
	अगर (sdev->sector_size > PAGE_SIZE)
		ata_dev_warn(dev,
			"sector_size=%u > PAGE_SIZE, PIO may malfunction\n",
			sdev->sector_size);

	blk_queue_update_dma_alignment(q, sdev->sector_size - 1);

	अगर (dev->flags & ATA_DFLAG_AN)
		set_bit(SDEV_EVT_MEDIA_CHANGE, sdev->supported_events);

	अगर (dev->flags & ATA_DFLAG_NCQ) अणु
		पूर्णांक depth;

		depth = min(sdev->host->can_queue, ata_id_queue_depth(dev->id));
		depth = min(ATA_MAX_QUEUE, depth);
		scsi_change_queue_depth(sdev, depth);
	पूर्ण

	अगर (dev->flags & ATA_DFLAG_TRUSTED)
		sdev->security_supported = 1;

	dev->sdev = sdev;
	वापस 0;
पूर्ण

/**
 *	ata_scsi_slave_config - Set SCSI device attributes
 *	@sdev: SCSI device to examine
 *
 *	This is called beक्रमe we actually start पढ़ोing
 *	and writing to the device, to configure certain
 *	SCSI mid-layer behaviors.
 *
 *	LOCKING:
 *	Defined by SCSI layer.  We करोn't really care.
 */

पूर्णांक ata_scsi_slave_config(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	काष्ठा ata_device *dev = __ata_scsi_find_dev(ap, sdev);
	पूर्णांक rc = 0;

	ata_scsi_sdev_config(sdev);

	अगर (dev)
		rc = ata_scsi_dev_config(sdev, dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_slave_config);

/**
 *	ata_scsi_slave_destroy - SCSI device is about to be destroyed
 *	@sdev: SCSI device to be destroyed
 *
 *	@sdev is about to be destroyed क्रम hot/warm unplugging.  If
 *	this unplugging was initiated by libata as indicated by शून्य
 *	dev->sdev, this function करोesn't have to करो anything.
 *	Otherwise, SCSI layer initiated warm-unplug is in progress.
 *	Clear dev->sdev, schedule the device क्रम ATA detach and invoke
 *	EH.
 *
 *	LOCKING:
 *	Defined by SCSI layer.  We करोn't really care.
 */
व्योम ata_scsi_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	अचिन्हित दीर्घ flags;
	काष्ठा ata_device *dev;

	अगर (!ap->ops->error_handler)
		वापस;

	spin_lock_irqsave(ap->lock, flags);
	dev = __ata_scsi_find_dev(ap, sdev);
	अगर (dev && dev->sdev) अणु
		/* SCSI device alपढ़ोy in CANCEL state, no need to offline it */
		dev->sdev = शून्य;
		dev->flags |= ATA_DFLAG_DETACH;
		ata_port_schedule_eh(ap);
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);

	kमुक्त(sdev->dma_drain_buf);
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_slave_destroy);

/**
 *	ata_scsi_start_stop_xlat - Translate SCSI START STOP UNIT command
 *	@qc: Storage क्रम translated ATA taskfile
 *
 *	Sets up an ATA taskfile to issue STANDBY (to stop) or READ VERIFY
 *	(to start). Perhaps these commands should be preceded by
 *	CHECK POWER MODE to see what घातer mode the device is alपढ़ोy in.
 *	[See SAT revision 5 at www.t10.org]
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, non-zero on error.
 */
अटल अचिन्हित पूर्णांक ata_scsi_start_stop_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	काष्ठा ata_taskfile *tf = &qc->tf;
	स्थिर u8 *cdb = scmd->cmnd;
	u16 fp;
	u8 bp = 0xff;

	अगर (scmd->cmd_len < 5) अणु
		fp = 4;
		जाओ invalid_fld;
	पूर्ण

	tf->flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;
	tf->protocol = ATA_PROT_NODATA;
	अगर (cdb[1] & 0x1) अणु
		;	/* ignore IMMED bit, violates sat-r05 */
	पूर्ण
	अगर (cdb[4] & 0x2) अणु
		fp = 4;
		bp = 1;
		जाओ invalid_fld;       /* LOEJ bit set not supported */
	पूर्ण
	अगर (((cdb[4] >> 4) & 0xf) != 0) अणु
		fp = 4;
		bp = 3;
		जाओ invalid_fld;       /* घातer conditions not supported */
	पूर्ण

	अगर (cdb[4] & 0x1) अणु
		tf->nsect = 1;	/* 1 sector, lba=0 */

		अगर (qc->dev->flags & ATA_DFLAG_LBA) अणु
			tf->flags |= ATA_TFLAG_LBA;

			tf->lbah = 0x0;
			tf->lbam = 0x0;
			tf->lbal = 0x0;
			tf->device |= ATA_LBA;
		पूर्ण अन्यथा अणु
			/* CHS */
			tf->lbal = 0x1; /* sect */
			tf->lbam = 0x0; /* cyl low */
			tf->lbah = 0x0; /* cyl high */
		पूर्ण

		tf->command = ATA_CMD_VERIFY;	/* READ VERIFY */
	पूर्ण अन्यथा अणु
		/* Some odd clown BIOSen issue spinकरोwn on घातer off (ACPI S4
		 * or S5) causing some drives to spin up and करोwn again.
		 */
		अगर ((qc->ap->flags & ATA_FLAG_NO_POWEROFF_SPINDOWN) &&
		    प्रणाली_state == SYSTEM_POWER_OFF)
			जाओ skip;

		अगर ((qc->ap->flags & ATA_FLAG_NO_HIBERNATE_SPINDOWN) &&
		     प्रणाली_entering_hibernation())
			जाओ skip;

		/* Issue ATA STANDBY IMMEDIATE command */
		tf->command = ATA_CMD_STANDBYNOW1;
	पूर्ण

	/*
	 * Standby and Idle condition समयrs could be implemented but that
	 * would require libata to implement the Power condition mode page
	 * and allow the user to change it. Changing mode pages requires
	 * MODE SELECT to be implemented.
	 */

	वापस 0;

 invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, bp);
	वापस 1;
 skip:
	scmd->result = SAM_STAT_GOOD;
	वापस 1;
पूर्ण


/**
 *	ata_scsi_flush_xlat - Translate SCSI SYNCHRONIZE CACHE command
 *	@qc: Storage क्रम translated ATA taskfile
 *
 *	Sets up an ATA taskfile to issue FLUSH CACHE or
 *	FLUSH CACHE EXT.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, non-zero on error.
 */
अटल अचिन्हित पूर्णांक ata_scsi_flush_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_taskfile *tf = &qc->tf;

	tf->flags |= ATA_TFLAG_DEVICE;
	tf->protocol = ATA_PROT_NODATA;

	अगर (qc->dev->flags & ATA_DFLAG_FLUSH_EXT)
		tf->command = ATA_CMD_FLUSH_EXT;
	अन्यथा
		tf->command = ATA_CMD_FLUSH;

	/* flush is critical क्रम IO पूर्णांकegrity, consider it an IO command */
	qc->flags |= ATA_QCFLAG_IO;

	वापस 0;
पूर्ण

/**
 *	scsi_6_lba_len - Get LBA and transfer length
 *	@cdb: SCSI command to translate
 *
 *	Calculate LBA and transfer length क्रम 6-byte commands.
 *
 *	RETURNS:
 *	@plba: the LBA
 *	@plen: the transfer length
 */
अटल व्योम scsi_6_lba_len(स्थिर u8 *cdb, u64 *plba, u32 *plen)
अणु
	u64 lba = 0;
	u32 len;

	VPRINTK("six-byte command\n");

	lba |= ((u64)(cdb[1] & 0x1f)) << 16;
	lba |= ((u64)cdb[2]) << 8;
	lba |= ((u64)cdb[3]);

	len = cdb[4];

	*plba = lba;
	*plen = len;
पूर्ण

/**
 *	scsi_10_lba_len - Get LBA and transfer length
 *	@cdb: SCSI command to translate
 *
 *	Calculate LBA and transfer length क्रम 10-byte commands.
 *
 *	RETURNS:
 *	@plba: the LBA
 *	@plen: the transfer length
 */
अटल व्योम scsi_10_lba_len(स्थिर u8 *cdb, u64 *plba, u32 *plen)
अणु
	u64 lba = 0;
	u32 len = 0;

	VPRINTK("ten-byte command\n");

	lba |= ((u64)cdb[2]) << 24;
	lba |= ((u64)cdb[3]) << 16;
	lba |= ((u64)cdb[4]) << 8;
	lba |= ((u64)cdb[5]);

	len |= ((u32)cdb[7]) << 8;
	len |= ((u32)cdb[8]);

	*plba = lba;
	*plen = len;
पूर्ण

/**
 *	scsi_16_lba_len - Get LBA and transfer length
 *	@cdb: SCSI command to translate
 *
 *	Calculate LBA and transfer length क्रम 16-byte commands.
 *
 *	RETURNS:
 *	@plba: the LBA
 *	@plen: the transfer length
 */
अटल व्योम scsi_16_lba_len(स्थिर u8 *cdb, u64 *plba, u32 *plen)
अणु
	u64 lba = 0;
	u32 len = 0;

	VPRINTK("sixteen-byte command\n");

	lba |= ((u64)cdb[2]) << 56;
	lba |= ((u64)cdb[3]) << 48;
	lba |= ((u64)cdb[4]) << 40;
	lba |= ((u64)cdb[5]) << 32;
	lba |= ((u64)cdb[6]) << 24;
	lba |= ((u64)cdb[7]) << 16;
	lba |= ((u64)cdb[8]) << 8;
	lba |= ((u64)cdb[9]);

	len |= ((u32)cdb[10]) << 24;
	len |= ((u32)cdb[11]) << 16;
	len |= ((u32)cdb[12]) << 8;
	len |= ((u32)cdb[13]);

	*plba = lba;
	*plen = len;
पूर्ण

/**
 *	ata_scsi_verअगरy_xlat - Translate SCSI VERIFY command पूर्णांकo an ATA one
 *	@qc: Storage क्रम translated ATA taskfile
 *
 *	Converts SCSI VERIFY command to an ATA READ VERIFY command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, non-zero on error.
 */
अटल अचिन्हित पूर्णांक ata_scsi_verअगरy_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	काष्ठा ata_taskfile *tf = &qc->tf;
	काष्ठा ata_device *dev = qc->dev;
	u64 dev_sectors = qc->dev->n_sectors;
	स्थिर u8 *cdb = scmd->cmnd;
	u64 block;
	u32 n_block;
	u16 fp;

	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf->protocol = ATA_PROT_NODATA;

	अगर (cdb[0] == VERIFY) अणु
		अगर (scmd->cmd_len < 10) अणु
			fp = 9;
			जाओ invalid_fld;
		पूर्ण
		scsi_10_lba_len(cdb, &block, &n_block);
	पूर्ण अन्यथा अगर (cdb[0] == VERIFY_16) अणु
		अगर (scmd->cmd_len < 16) अणु
			fp = 15;
			जाओ invalid_fld;
		पूर्ण
		scsi_16_lba_len(cdb, &block, &n_block);
	पूर्ण अन्यथा अणु
		fp = 0;
		जाओ invalid_fld;
	पूर्ण

	अगर (!n_block)
		जाओ nothing_to_करो;
	अगर (block >= dev_sectors)
		जाओ out_of_range;
	अगर ((block + n_block) > dev_sectors)
		जाओ out_of_range;

	अगर (dev->flags & ATA_DFLAG_LBA) अणु
		tf->flags |= ATA_TFLAG_LBA;

		अगर (lba_28_ok(block, n_block)) अणु
			/* use LBA28 */
			tf->command = ATA_CMD_VERIFY;
			tf->device |= (block >> 24) & 0xf;
		पूर्ण अन्यथा अगर (lba_48_ok(block, n_block)) अणु
			अगर (!(dev->flags & ATA_DFLAG_LBA48))
				जाओ out_of_range;

			/* use LBA48 */
			tf->flags |= ATA_TFLAG_LBA48;
			tf->command = ATA_CMD_VERIFY_EXT;

			tf->hob_nsect = (n_block >> 8) & 0xff;

			tf->hob_lbah = (block >> 40) & 0xff;
			tf->hob_lbam = (block >> 32) & 0xff;
			tf->hob_lbal = (block >> 24) & 0xff;
		पूर्ण अन्यथा
			/* request too large even क्रम LBA48 */
			जाओ out_of_range;

		tf->nsect = n_block & 0xff;

		tf->lbah = (block >> 16) & 0xff;
		tf->lbam = (block >> 8) & 0xff;
		tf->lbal = block & 0xff;

		tf->device |= ATA_LBA;
	पूर्ण अन्यथा अणु
		/* CHS */
		u32 sect, head, cyl, track;

		अगर (!lba_28_ok(block, n_block))
			जाओ out_of_range;

		/* Convert LBA to CHS */
		track = (u32)block / dev->sectors;
		cyl   = track / dev->heads;
		head  = track % dev->heads;
		sect  = (u32)block % dev->sectors + 1;

		DPRINTK("block %u track %u cyl %u head %u sect %u\n",
			(u32)block, track, cyl, head, sect);

		/* Check whether the converted CHS can fit.
		   Cylinder: 0-65535
		   Head: 0-15
		   Sector: 1-255*/
		अगर ((cyl >> 16) || (head >> 4) || (sect >> 8) || (!sect))
			जाओ out_of_range;

		tf->command = ATA_CMD_VERIFY;
		tf->nsect = n_block & 0xff; /* Sector count 0 means 256 sectors */
		tf->lbal = sect;
		tf->lbam = cyl;
		tf->lbah = cyl >> 8;
		tf->device |= head;
	पूर्ण

	वापस 0;

invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, 0xff);
	वापस 1;

out_of_range:
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x21, 0x0);
	/* "Logical Block Address out of range" */
	वापस 1;

nothing_to_करो:
	scmd->result = SAM_STAT_GOOD;
	वापस 1;
पूर्ण

अटल bool ata_check_nblocks(काष्ठा scsi_cmnd *scmd, u32 n_blocks)
अणु
	काष्ठा request *rq = scmd->request;
	u32 req_blocks;

	अगर (!blk_rq_is_passthrough(rq))
		वापस true;

	req_blocks = blk_rq_bytes(rq) / scmd->device->sector_size;
	अगर (n_blocks > req_blocks)
		वापस false;

	वापस true;
पूर्ण

/**
 *	ata_scsi_rw_xlat - Translate SCSI r/w command पूर्णांकo an ATA one
 *	@qc: Storage क्रम translated ATA taskfile
 *
 *	Converts any of six SCSI पढ़ो/ग_लिखो commands पूर्णांकo the
 *	ATA counterpart, including starting sector (LBA),
 *	sector count, and taking पूर्णांकo account the device's LBA48
 *	support.
 *
 *	Commands %READ_6, %READ_10, %READ_16, %WRITE_6, %WRITE_10, and
 *	%WRITE_16 are currently supported.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, non-zero on error.
 */
अटल अचिन्हित पूर्णांक ata_scsi_rw_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	स्थिर u8 *cdb = scmd->cmnd;
	काष्ठा request *rq = scmd->request;
	पूर्णांक class = IOPRIO_PRIO_CLASS(req_get_ioprio(rq));
	अचिन्हित पूर्णांक tf_flags = 0;
	u64 block;
	u32 n_block;
	पूर्णांक rc;
	u16 fp = 0;

	अगर (cdb[0] == WRITE_10 || cdb[0] == WRITE_6 || cdb[0] == WRITE_16)
		tf_flags |= ATA_TFLAG_WRITE;

	/* Calculate the SCSI LBA, transfer length and FUA. */
	चयन (cdb[0]) अणु
	हाल READ_10:
	हाल WRITE_10:
		अगर (unlikely(scmd->cmd_len < 10)) अणु
			fp = 9;
			जाओ invalid_fld;
		पूर्ण
		scsi_10_lba_len(cdb, &block, &n_block);
		अगर (cdb[1] & (1 << 3))
			tf_flags |= ATA_TFLAG_FUA;
		अगर (!ata_check_nblocks(scmd, n_block))
			जाओ invalid_fld;
		अवरोध;
	हाल READ_6:
	हाल WRITE_6:
		अगर (unlikely(scmd->cmd_len < 6)) अणु
			fp = 5;
			जाओ invalid_fld;
		पूर्ण
		scsi_6_lba_len(cdb, &block, &n_block);

		/* क्रम 6-byte r/w commands, transfer length 0
		 * means 256 blocks of data, not 0 block.
		 */
		अगर (!n_block)
			n_block = 256;
		अगर (!ata_check_nblocks(scmd, n_block))
			जाओ invalid_fld;
		अवरोध;
	हाल READ_16:
	हाल WRITE_16:
		अगर (unlikely(scmd->cmd_len < 16)) अणु
			fp = 15;
			जाओ invalid_fld;
		पूर्ण
		scsi_16_lba_len(cdb, &block, &n_block);
		अगर (cdb[1] & (1 << 3))
			tf_flags |= ATA_TFLAG_FUA;
		अगर (!ata_check_nblocks(scmd, n_block))
			जाओ invalid_fld;
		अवरोध;
	शेष:
		DPRINTK("no-byte command\n");
		fp = 0;
		जाओ invalid_fld;
	पूर्ण

	/* Check and compose ATA command */
	अगर (!n_block)
		/* For 10-byte and 16-byte SCSI R/W commands, transfer
		 * length 0 means transfer 0 block of data.
		 * However, क्रम ATA R/W commands, sector count 0 means
		 * 256 or 65536 sectors, not 0 sectors as in SCSI.
		 *
		 * WARNING: one or two older ATA drives treat 0 as 0...
		 */
		जाओ nothing_to_करो;

	qc->flags |= ATA_QCFLAG_IO;
	qc->nbytes = n_block * scmd->device->sector_size;

	rc = ata_build_rw_tf(&qc->tf, qc->dev, block, n_block, tf_flags,
			     qc->hw_tag, class);

	अगर (likely(rc == 0))
		वापस 0;

	अगर (rc == -दुस्फल)
		जाओ out_of_range;
	/* treat all other errors as -EINVAL, fall through */
invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, 0xff);
	वापस 1;

out_of_range:
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x21, 0x0);
	/* "Logical Block Address out of range" */
	वापस 1;

nothing_to_करो:
	scmd->result = SAM_STAT_GOOD;
	वापस 1;
पूर्ण

अटल व्योम ata_qc_करोne(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;
	व्योम (*करोne)(काष्ठा scsi_cmnd *) = qc->scsiकरोne;

	ata_qc_मुक्त(qc);
	करोne(cmd);
पूर्ण

अटल व्योम ata_scsi_qc_complete(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;
	u8 *cdb = cmd->cmnd;
	पूर्णांक need_sense = (qc->err_mask != 0);

	/* For ATA pass thru (SAT) commands, generate a sense block अगर
	 * user mandated it or अगर there's an error.  Note that अगर we
	 * generate because the user क्रमced us to [CK_COND =1], a check
	 * condition is generated and the ATA रेजिस्टर values are वापसed
	 * whether the command completed successfully or not. If there
	 * was no error, we use the following sense data:
	 * sk = RECOVERED ERROR
	 * asc,ascq = ATA PASS-THROUGH INFORMATION AVAILABLE
	 */
	अगर (((cdb[0] == ATA_16) || (cdb[0] == ATA_12)) &&
	    ((cdb[2] & 0x20) || need_sense))
		ata_gen_passthru_sense(qc);
	अन्यथा अगर (qc->flags & ATA_QCFLAG_SENSE_VALID)
		cmd->result = SAM_STAT_CHECK_CONDITION;
	अन्यथा अगर (need_sense)
		ata_gen_ata_sense(qc);
	अन्यथा
		cmd->result = SAM_STAT_GOOD;

	अगर (need_sense && !ap->ops->error_handler)
		ata_dump_status(ap->prपूर्णांक_id, &qc->result_tf);

	ata_qc_करोne(qc);
पूर्ण

/**
 *	ata_scsi_translate - Translate then issue SCSI command to ATA device
 *	@dev: ATA device to which the command is addressed
 *	@cmd: SCSI command to execute
 *	@xlat_func: Actor which translates @cmd to an ATA taskfile
 *
 *	Our ->queuecommand() function has decided that the SCSI
 *	command issued can be directly translated पूर्णांकo an ATA
 *	command, rather than handled पूर्णांकernally.
 *
 *	This function sets up an ata_queued_cmd काष्ठाure क्रम the
 *	SCSI command, and sends that ata_queued_cmd to the hardware.
 *
 *	The xlat_func argument (actor) वापसs 0 अगर पढ़ोy to execute
 *	ATA command, अन्यथा 1 to finish translation. If 1 is वापसed
 *	then cmd->result (and possibly cmd->sense_buffer) are assumed
 *	to be set reflecting an error condition or clean (early)
 *	termination.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	0 on success, SCSI_ML_QUEUE_DEVICE_BUSY अगर the command
 *	needs to be deferred.
 */
अटल पूर्णांक ata_scsi_translate(काष्ठा ata_device *dev, काष्ठा scsi_cmnd *cmd,
			      ata_xlat_func_t xlat_func)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_queued_cmd *qc;
	पूर्णांक rc;

	VPRINTK("ENTER\n");

	qc = ata_scsi_qc_new(dev, cmd);
	अगर (!qc)
		जाओ err_mem;

	/* data is present; dma-map it */
	अगर (cmd->sc_data_direction == DMA_FROM_DEVICE ||
	    cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		अगर (unlikely(scsi_bufflen(cmd) < 1)) अणु
			ata_dev_warn(dev, "WARNING: zero len r/w req\n");
			जाओ err_did;
		पूर्ण

		ata_sg_init(qc, scsi_sglist(cmd), scsi_sg_count(cmd));

		qc->dma_dir = cmd->sc_data_direction;
	पूर्ण

	qc->complete_fn = ata_scsi_qc_complete;

	अगर (xlat_func(qc))
		जाओ early_finish;

	अगर (ap->ops->qc_defer) अणु
		अगर ((rc = ap->ops->qc_defer(qc)))
			जाओ defer;
	पूर्ण

	/* select device, send command to hardware */
	ata_qc_issue(qc);

	VPRINTK("EXIT\n");
	वापस 0;

early_finish:
	ata_qc_मुक्त(qc);
	cmd->scsi_करोne(cmd);
	DPRINTK("EXIT - early finish (good or error)\n");
	वापस 0;

err_did:
	ata_qc_मुक्त(qc);
	cmd->result = (DID_ERROR << 16);
	cmd->scsi_करोne(cmd);
err_mem:
	DPRINTK("EXIT - internal\n");
	वापस 0;

defer:
	ata_qc_मुक्त(qc);
	DPRINTK("EXIT - defer\n");
	अगर (rc == ATA_DEFER_LINK)
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	अन्यथा
		वापस SCSI_MLQUEUE_HOST_BUSY;
पूर्ण

काष्ठा ata_scsi_args अणु
	काष्ठा ata_device	*dev;
	u16			*id;
	काष्ठा scsi_cmnd	*cmd;
पूर्ण;

/**
 *	ata_scsi_rbuf_get - Map response buffer.
 *	@cmd: SCSI command containing buffer to be mapped.
 *	@flags: अचिन्हित दीर्घ variable to store irq enable status
 *	@copy_in: copy in from user buffer
 *
 *	Prepare buffer क्रम simulated SCSI commands.
 *
 *	LOCKING:
 *	spin_lock_irqsave(ata_scsi_rbuf_lock) on success
 *
 *	RETURNS:
 *	Poपूर्णांकer to response buffer.
 */
अटल व्योम *ata_scsi_rbuf_get(काष्ठा scsi_cmnd *cmd, bool copy_in,
			       अचिन्हित दीर्घ *flags)
अणु
	spin_lock_irqsave(&ata_scsi_rbuf_lock, *flags);

	स_रखो(ata_scsi_rbuf, 0, ATA_SCSI_RBUF_SIZE);
	अगर (copy_in)
		sg_copy_to_buffer(scsi_sglist(cmd), scsi_sg_count(cmd),
				  ata_scsi_rbuf, ATA_SCSI_RBUF_SIZE);
	वापस ata_scsi_rbuf;
पूर्ण

/**
 *	ata_scsi_rbuf_put - Unmap response buffer.
 *	@cmd: SCSI command containing buffer to be unmapped.
 *	@copy_out: copy out result
 *	@flags: @flags passed to ata_scsi_rbuf_get()
 *
 *	Returns rbuf buffer.  The result is copied to @cmd's buffer अगर
 *	@copy_back is true.
 *
 *	LOCKING:
 *	Unlocks ata_scsi_rbuf_lock.
 */
अटल अंतरभूत व्योम ata_scsi_rbuf_put(काष्ठा scsi_cmnd *cmd, bool copy_out,
				     अचिन्हित दीर्घ *flags)
अणु
	अगर (copy_out)
		sg_copy_from_buffer(scsi_sglist(cmd), scsi_sg_count(cmd),
				    ata_scsi_rbuf, ATA_SCSI_RBUF_SIZE);
	spin_unlock_irqrestore(&ata_scsi_rbuf_lock, *flags);
पूर्ण

/**
 *	ata_scsi_rbuf_fill - wrapper क्रम SCSI command simulators
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@actor: Callback hook क्रम desired SCSI command simulator
 *
 *	Takes care of the hard work of simulating a SCSI command...
 *	Mapping the response buffer, calling the command's handler,
 *	and handling the handler's वापस value.  This वापस value
 *	indicates whether the handler wishes the SCSI command to be
 *	completed successfully (0), or not (in which हाल cmd->result
 *	and sense buffer are assumed to be set).
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल व्योम ata_scsi_rbuf_fill(काष्ठा ata_scsi_args *args,
		अचिन्हित पूर्णांक (*actor)(काष्ठा ata_scsi_args *args, u8 *rbuf))
अणु
	u8 *rbuf;
	अचिन्हित पूर्णांक rc;
	काष्ठा scsi_cmnd *cmd = args->cmd;
	अचिन्हित दीर्घ flags;

	rbuf = ata_scsi_rbuf_get(cmd, false, &flags);
	rc = actor(args, rbuf);
	ata_scsi_rbuf_put(cmd, rc == 0, &flags);

	अगर (rc == 0)
		cmd->result = SAM_STAT_GOOD;
पूर्ण

/**
 *	ata_scsiop_inq_std - Simulate INQUIRY command
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Returns standard device identअगरication data associated
 *	with non-VPD INQUIRY command output.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_inq_std(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	अटल स्थिर u8 versions[] = अणु
		0x00,
		0x60,	/* SAM-3 (no version claimed) */

		0x03,
		0x20,	/* SBC-2 (no version claimed) */

		0x03,
		0x00	/* SPC-3 (no version claimed) */
	पूर्ण;
	अटल स्थिर u8 versions_zbc[] = अणु
		0x00,
		0xA0,	/* SAM-5 (no version claimed) */

		0x06,
		0x00,	/* SBC-4 (no version claimed) */

		0x05,
		0xC0,	/* SPC-5 (no version claimed) */

		0x60,
		0x24,   /* ZBC r05 */
	पूर्ण;

	u8 hdr[] = अणु
		TYPE_DISK,
		0,
		0x5,	/* claim SPC-3 version compatibility */
		2,
		95 - 4,
		0,
		0,
		2
	पूर्ण;

	VPRINTK("ENTER\n");

	/* set scsi removable (RMB) bit per ata bit, or अगर the
	 * AHCI port says it's बाह्यal (Hotplug-capable, eSATA).
	 */
	अगर (ata_id_removable(args->id) ||
	    (args->dev->link->ap->pflags & ATA_PFLAG_EXTERNAL))
		hdr[1] |= (1 << 7);

	अगर (args->dev->class == ATA_DEV_ZAC) अणु
		hdr[0] = TYPE_ZBC;
		hdr[2] = 0x7; /* claim SPC-5 version compatibility */
	पूर्ण

	स_नकल(rbuf, hdr, माप(hdr));
	स_नकल(&rbuf[8], "ATA     ", 8);
	ata_id_string(args->id, &rbuf[16], ATA_ID_PROD, 16);

	/* From SAT, use last 2 words from fw rev unless they are spaces */
	ata_id_string(args->id, &rbuf[32], ATA_ID_FW_REV + 2, 4);
	अगर (म_भेदन(&rbuf[32], "    ", 4) == 0)
		ata_id_string(args->id, &rbuf[32], ATA_ID_FW_REV, 4);

	अगर (rbuf[32] == 0 || rbuf[32] == ' ')
		स_नकल(&rbuf[32], "n/a ", 4);

	अगर (ata_id_zoned_cap(args->id) || args->dev->class == ATA_DEV_ZAC)
		स_नकल(rbuf + 58, versions_zbc, माप(versions_zbc));
	अन्यथा
		स_नकल(rbuf + 58, versions, माप(versions));

	वापस 0;
पूर्ण

/**
 *	ata_scsiop_inq_00 - Simulate INQUIRY VPD page 0, list of pages
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Returns list of inquiry VPD pages available.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_inq_00(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	पूर्णांक num_pages;
	अटल स्थिर u8 pages[] = अणु
		0x00,	/* page 0x00, this page */
		0x80,	/* page 0x80, unit serial no page */
		0x83,	/* page 0x83, device ident page */
		0x89,	/* page 0x89, ata info page */
		0xb0,	/* page 0xb0, block limits page */
		0xb1,	/* page 0xb1, block device अक्षरacteristics page */
		0xb2,	/* page 0xb2, thin provisioning page */
		0xb6,	/* page 0xb6, zoned block device अक्षरacteristics */
	पूर्ण;

	num_pages = माप(pages);
	अगर (!(args->dev->flags & ATA_DFLAG_ZAC))
		num_pages--;
	rbuf[3] = num_pages;	/* number of supported VPD pages */
	स_नकल(rbuf + 4, pages, num_pages);
	वापस 0;
पूर्ण

/**
 *	ata_scsiop_inq_80 - Simulate INQUIRY VPD page 80, device serial number
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Returns ATA device serial number.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_inq_80(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	अटल स्थिर u8 hdr[] = अणु
		0,
		0x80,			/* this page code */
		0,
		ATA_ID_SERNO_LEN,	/* page len */
	पूर्ण;

	स_नकल(rbuf, hdr, माप(hdr));
	ata_id_string(args->id, (अचिन्हित अक्षर *) &rbuf[4],
		      ATA_ID_SERNO, ATA_ID_SERNO_LEN);
	वापस 0;
पूर्ण

/**
 *	ata_scsiop_inq_83 - Simulate INQUIRY VPD page 83, device identity
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Yields two logical unit device identअगरication designators:
 *	 - venकरोr specअगरic ASCII containing the ATA serial number
 *	 - SAT defined "t10 vendor id based" containing ASCII venकरोr
 *	   name ("ATA     "), model and serial numbers.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_inq_83(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	स्थिर पूर्णांक sat_model_serial_desc_len = 68;
	पूर्णांक num;

	rbuf[1] = 0x83;			/* this page code */
	num = 4;

	/* piv=0, assoc=lu, code_set=ACSII, designator=venकरोr */
	rbuf[num + 0] = 2;
	rbuf[num + 3] = ATA_ID_SERNO_LEN;
	num += 4;
	ata_id_string(args->id, (अचिन्हित अक्षर *) rbuf + num,
		      ATA_ID_SERNO, ATA_ID_SERNO_LEN);
	num += ATA_ID_SERNO_LEN;

	/* SAT defined lu model and serial numbers descriptor */
	/* piv=0, assoc=lu, code_set=ACSII, designator=t10 venकरोr id */
	rbuf[num + 0] = 2;
	rbuf[num + 1] = 1;
	rbuf[num + 3] = sat_model_serial_desc_len;
	num += 4;
	स_नकल(rbuf + num, "ATA     ", 8);
	num += 8;
	ata_id_string(args->id, (अचिन्हित अक्षर *) rbuf + num, ATA_ID_PROD,
		      ATA_ID_PROD_LEN);
	num += ATA_ID_PROD_LEN;
	ata_id_string(args->id, (अचिन्हित अक्षर *) rbuf + num, ATA_ID_SERNO,
		      ATA_ID_SERNO_LEN);
	num += ATA_ID_SERNO_LEN;

	अगर (ata_id_has_wwn(args->id)) अणु
		/* SAT defined lu world wide name */
		/* piv=0, assoc=lu, code_set=binary, designator=NAA */
		rbuf[num + 0] = 1;
		rbuf[num + 1] = 3;
		rbuf[num + 3] = ATA_ID_WWN_LEN;
		num += 4;
		ata_id_string(args->id, (अचिन्हित अक्षर *) rbuf + num,
			      ATA_ID_WWN, ATA_ID_WWN_LEN);
		num += ATA_ID_WWN_LEN;
	पूर्ण
	rbuf[3] = num - 4;    /* page len (assume less than 256 bytes) */
	वापस 0;
पूर्ण

/**
 *	ata_scsiop_inq_89 - Simulate INQUIRY VPD page 89, ATA info
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Yields SAT-specअगरied ATA VPD page.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_inq_89(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	rbuf[1] = 0x89;			/* our page code */
	rbuf[2] = (0x238 >> 8);		/* page size fixed at 238h */
	rbuf[3] = (0x238 & 0xff);

	स_नकल(&rbuf[8], "linux   ", 8);
	स_नकल(&rbuf[16], "libata          ", 16);
	स_नकल(&rbuf[32], DRV_VERSION, 4);

	rbuf[36] = 0x34;		/* क्रमce D2H Reg FIS (34h) */
	rbuf[37] = (1 << 7);		/* bit 7 indicates Command FIS */
					/* TODO: PMP? */

	/* we करोn't store the ATA device signature, so we fake it */
	rbuf[38] = ATA_DRDY;		/* really, this is Status reg */
	rbuf[40] = 0x1;
	rbuf[48] = 0x1;

	rbuf[56] = ATA_CMD_ID_ATA;

	स_नकल(&rbuf[60], &args->id[0], 512);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ata_scsiop_inq_b0(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	काष्ठा ata_device *dev = args->dev;
	u16 min_io_sectors;

	rbuf[1] = 0xb0;
	rbuf[3] = 0x3c;		/* required VPD size with unmap support */

	/*
	 * Optimal transfer length granularity.
	 *
	 * This is always one physical block, but क्रम disks with a smaller
	 * logical than physical sector size we need to figure out what the
	 * latter is.
	 */
	min_io_sectors = 1 << ata_id_log2_per_physical_sector(args->id);
	put_unaligned_be16(min_io_sectors, &rbuf[6]);

	/*
	 * Optimal unmap granularity.
	 *
	 * The ATA spec करोesn't even know about a granularity or alignment
	 * क्रम the TRIM command.  We can leave away most of the unmap related
	 * VPD page entries, but we have specअगरअगरy a granularity to संकेत
	 * that we support some क्रमm of unmap - in thise हाल via WRITE SAME
	 * with the unmap bit set.
	 */
	अगर (ata_id_has_trim(args->id)) अणु
		u64 max_blocks = 65535 * ATA_MAX_TRIM_RNUM;

		अगर (dev->horkage & ATA_HORKAGE_MAX_TRIM_128M)
			max_blocks = 128 << (20 - SECTOR_SHIFT);

		put_unaligned_be64(max_blocks, &rbuf[36]);
		put_unaligned_be32(1, &rbuf[28]);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ata_scsiop_inq_b1(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	पूर्णांक क्रमm_factor = ata_id_क्रमm_factor(args->id);
	पूर्णांक media_rotation_rate = ata_id_rotation_rate(args->id);
	u8 zoned = ata_id_zoned_cap(args->id);

	rbuf[1] = 0xb1;
	rbuf[3] = 0x3c;
	rbuf[4] = media_rotation_rate >> 8;
	rbuf[5] = media_rotation_rate;
	rbuf[7] = क्रमm_factor;
	अगर (zoned)
		rbuf[8] = (zoned << 4);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ata_scsiop_inq_b2(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	/* SCSI Thin Provisioning VPD page: SBC-3 rev 22 or later */
	rbuf[1] = 0xb2;
	rbuf[3] = 0x4;
	rbuf[5] = 1 << 6;	/* TPWS */

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ata_scsiop_inq_b6(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	/*
	 * zbc-r05 SCSI Zoned Block device अक्षरacteristics VPD page
	 */
	rbuf[1] = 0xb6;
	rbuf[3] = 0x3C;

	/*
	 * URSWRZ bit is only meaningful क्रम host-managed ZAC drives
	 */
	अगर (args->dev->zac_zoned_cap & 1)
		rbuf[4] |= 1;
	put_unaligned_be32(args->dev->zac_zones_optimal_खोलो, &rbuf[8]);
	put_unaligned_be32(args->dev->zac_zones_optimal_nonseq, &rbuf[12]);
	put_unaligned_be32(args->dev->zac_zones_max_खोलो, &rbuf[16]);

	वापस 0;
पूर्ण

/**
 *	modecpy - Prepare response क्रम MODE SENSE
 *	@dest: output buffer
 *	@src: data being copied
 *	@n: length of mode page
 *	@changeable: whether changeable parameters are requested
 *
 *	Generate a generic MODE SENSE page क्रम either current or changeable
 *	parameters.
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम modecpy(u8 *dest, स्थिर u8 *src, पूर्णांक n, bool changeable)
अणु
	अगर (changeable) अणु
		स_नकल(dest, src, 2);
		स_रखो(dest + 2, 0, n - 2);
	पूर्ण अन्यथा अणु
		स_नकल(dest, src, n);
	पूर्ण
पूर्ण

/**
 *	ata_msense_caching - Simulate MODE SENSE caching info page
 *	@id: device IDENTIFY data
 *	@buf: output buffer
 *	@changeable: whether changeable parameters are requested
 *
 *	Generate a caching info page, which conditionally indicates
 *	ग_लिखो caching to the SCSI layer, depending on device
 *	capabilities.
 *
 *	LOCKING:
 *	None.
 */
अटल अचिन्हित पूर्णांक ata_msense_caching(u16 *id, u8 *buf, bool changeable)
अणु
	modecpy(buf, def_cache_mpage, माप(def_cache_mpage), changeable);
	अगर (changeable) अणु
		buf[2] |= (1 << 2);	/* ata_mselect_caching() */
	पूर्ण अन्यथा अणु
		buf[2] |= (ata_id_wcache_enabled(id) << 2);	/* ग_लिखो cache enable */
		buf[12] |= (!ata_id_rahead_enabled(id) << 5);	/* disable पढ़ो ahead */
	पूर्ण
	वापस माप(def_cache_mpage);
पूर्ण

/**
 *	ata_msense_control - Simulate MODE SENSE control mode page
 *	@dev: ATA device of पूर्णांकerest
 *	@buf: output buffer
 *	@changeable: whether changeable parameters are requested
 *
 *	Generate a generic MODE SENSE control mode page.
 *
 *	LOCKING:
 *	None.
 */
अटल अचिन्हित पूर्णांक ata_msense_control(काष्ठा ata_device *dev, u8 *buf,
					bool changeable)
अणु
	modecpy(buf, def_control_mpage, माप(def_control_mpage), changeable);
	अगर (changeable) अणु
		buf[2] |= (1 << 2);	/* ata_mselect_control() */
	पूर्ण अन्यथा अणु
		bool d_sense = (dev->flags & ATA_DFLAG_D_SENSE);

		buf[2] |= (d_sense << 2);	/* descriptor क्रमmat sense data */
	पूर्ण
	वापस माप(def_control_mpage);
पूर्ण

/**
 *	ata_msense_rw_recovery - Simulate MODE SENSE r/w error recovery page
 *	@buf: output buffer
 *	@changeable: whether changeable parameters are requested
 *
 *	Generate a generic MODE SENSE r/w error recovery page.
 *
 *	LOCKING:
 *	None.
 */
अटल अचिन्हित पूर्णांक ata_msense_rw_recovery(u8 *buf, bool changeable)
अणु
	modecpy(buf, def_rw_recovery_mpage, माप(def_rw_recovery_mpage),
		changeable);
	वापस माप(def_rw_recovery_mpage);
पूर्ण

/*
 * We can turn this पूर्णांकo a real blacklist अगर it's needed, क्रम now just
 * blacklist any Maxtor BANC1G10 revision firmware
 */
अटल पूर्णांक ata_dev_supports_fua(u16 *id)
अणु
	अचिन्हित अक्षर model[ATA_ID_PROD_LEN + 1], fw[ATA_ID_FW_REV_LEN + 1];

	अगर (!libata_fua)
		वापस 0;
	अगर (!ata_id_has_fua(id))
		वापस 0;

	ata_id_c_string(id, model, ATA_ID_PROD, माप(model));
	ata_id_c_string(id, fw, ATA_ID_FW_REV, माप(fw));

	अगर (म_भेद(model, "Maxtor"))
		वापस 1;
	अगर (म_भेद(fw, "BANC1G10"))
		वापस 1;

	वापस 0; /* blacklisted */
पूर्ण

/**
 *	ata_scsiop_mode_sense - Simulate MODE SENSE 6, 10 commands
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Simulate MODE SENSE commands. Assume this is invoked क्रम direct
 *	access devices (e.g. disks) only. There should be no block
 *	descriptor क्रम other device types.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_mode_sense(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	काष्ठा ata_device *dev = args->dev;
	u8 *scsicmd = args->cmd->cmnd, *p = rbuf;
	अटल स्थिर u8 sat_blk_desc[] = अणु
		0, 0, 0, 0,	/* number of blocks: sat unspecअगरied */
		0,
		0, 0x2, 0x0	/* block length: 512 bytes */
	पूर्ण;
	u8 pg, spg;
	अचिन्हित पूर्णांक ebd, page_control, six_byte;
	u8 dpofua, bp = 0xff;
	u16 fp;

	VPRINTK("ENTER\n");

	six_byte = (scsicmd[0] == MODE_SENSE);
	ebd = !(scsicmd[1] & 0x8);      /* dbd bit inverted == edb */
	/*
	 * LLBA bit in msense(10) ignored (compliant)
	 */

	page_control = scsicmd[2] >> 6;
	चयन (page_control) अणु
	हाल 0: /* current */
	हाल 1: /* changeable */
	हाल 2: /* शेषs */
		अवरोध;  /* supported */
	हाल 3: /* saved */
		जाओ saving_not_supp;
	शेष:
		fp = 2;
		bp = 6;
		जाओ invalid_fld;
	पूर्ण

	अगर (six_byte)
		p += 4 + (ebd ? 8 : 0);
	अन्यथा
		p += 8 + (ebd ? 8 : 0);

	pg = scsicmd[2] & 0x3f;
	spg = scsicmd[3];
	/*
	 * No mode subpages supported (yet) but asking क्रम _all_
	 * subpages may be valid
	 */
	अगर (spg && (spg != ALL_SUB_MPAGES)) अणु
		fp = 3;
		जाओ invalid_fld;
	पूर्ण

	चयन(pg) अणु
	हाल RW_RECOVERY_MPAGE:
		p += ata_msense_rw_recovery(p, page_control == 1);
		अवरोध;

	हाल CACHE_MPAGE:
		p += ata_msense_caching(args->id, p, page_control == 1);
		अवरोध;

	हाल CONTROL_MPAGE:
		p += ata_msense_control(args->dev, p, page_control == 1);
		अवरोध;

	हाल ALL_MPAGES:
		p += ata_msense_rw_recovery(p, page_control == 1);
		p += ata_msense_caching(args->id, p, page_control == 1);
		p += ata_msense_control(args->dev, p, page_control == 1);
		अवरोध;

	शेष:		/* invalid page code */
		fp = 2;
		जाओ invalid_fld;
	पूर्ण

	dpofua = 0;
	अगर (ata_dev_supports_fua(args->id) && (dev->flags & ATA_DFLAG_LBA48) &&
	    (!(dev->flags & ATA_DFLAG_PIO) || dev->multi_count))
		dpofua = 1 << 4;

	अगर (six_byte) अणु
		rbuf[0] = p - rbuf - 1;
		rbuf[2] |= dpofua;
		अगर (ebd) अणु
			rbuf[3] = माप(sat_blk_desc);
			स_नकल(rbuf + 4, sat_blk_desc, माप(sat_blk_desc));
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक output_len = p - rbuf - 2;

		rbuf[0] = output_len >> 8;
		rbuf[1] = output_len;
		rbuf[3] |= dpofua;
		अगर (ebd) अणु
			rbuf[7] = माप(sat_blk_desc);
			स_नकल(rbuf + 8, sat_blk_desc, माप(sat_blk_desc));
		पूर्ण
	पूर्ण
	वापस 0;

invalid_fld:
	ata_scsi_set_invalid_field(dev, args->cmd, fp, bp);
	वापस 1;

saving_not_supp:
	ata_scsi_set_sense(dev, args->cmd, ILLEGAL_REQUEST, 0x39, 0x0);
	 /* "Saving parameters not supported" */
	वापस 1;
पूर्ण

/**
 *	ata_scsiop_पढ़ो_cap - Simulate READ CAPACITY[ 16] commands
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Simulate READ CAPACITY commands.
 *
 *	LOCKING:
 *	None.
 */
अटल अचिन्हित पूर्णांक ata_scsiop_पढ़ो_cap(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	काष्ठा ata_device *dev = args->dev;
	u64 last_lba = dev->n_sectors - 1; /* LBA of the last block */
	u32 sector_size; /* physical sector size in bytes */
	u8 log2_per_phys;
	u16 lowest_aligned;

	sector_size = ata_id_logical_sector_size(dev->id);
	log2_per_phys = ata_id_log2_per_physical_sector(dev->id);
	lowest_aligned = ata_id_logical_sector_offset(dev->id, log2_per_phys);

	VPRINTK("ENTER\n");

	अगर (args->cmd->cmnd[0] == READ_CAPACITY) अणु
		अगर (last_lba >= 0xffffffffULL)
			last_lba = 0xffffffff;

		/* sector count, 32-bit */
		rbuf[0] = last_lba >> (8 * 3);
		rbuf[1] = last_lba >> (8 * 2);
		rbuf[2] = last_lba >> (8 * 1);
		rbuf[3] = last_lba;

		/* sector size */
		rbuf[4] = sector_size >> (8 * 3);
		rbuf[5] = sector_size >> (8 * 2);
		rbuf[6] = sector_size >> (8 * 1);
		rbuf[7] = sector_size;
	पूर्ण अन्यथा अणु
		/* sector count, 64-bit */
		rbuf[0] = last_lba >> (8 * 7);
		rbuf[1] = last_lba >> (8 * 6);
		rbuf[2] = last_lba >> (8 * 5);
		rbuf[3] = last_lba >> (8 * 4);
		rbuf[4] = last_lba >> (8 * 3);
		rbuf[5] = last_lba >> (8 * 2);
		rbuf[6] = last_lba >> (8 * 1);
		rbuf[7] = last_lba;

		/* sector size */
		rbuf[ 8] = sector_size >> (8 * 3);
		rbuf[ 9] = sector_size >> (8 * 2);
		rbuf[10] = sector_size >> (8 * 1);
		rbuf[11] = sector_size;

		rbuf[12] = 0;
		rbuf[13] = log2_per_phys;
		rbuf[14] = (lowest_aligned >> 8) & 0x3f;
		rbuf[15] = lowest_aligned;

		अगर (ata_id_has_trim(args->id) &&
		    !(dev->horkage & ATA_HORKAGE_NOTRIM)) अणु
			rbuf[14] |= 0x80; /* LBPME */

			अगर (ata_id_has_zero_after_trim(args->id) &&
			    dev->horkage & ATA_HORKAGE_ZERO_AFTER_TRIM) अणु
				ata_dev_info(dev, "Enabling discard_zeroes_data\n");
				rbuf[14] |= 0x40; /* LBPRZ */
			पूर्ण
		पूर्ण
		अगर (ata_id_zoned_cap(args->id) ||
		    args->dev->class == ATA_DEV_ZAC)
			rbuf[12] = (1 << 4); /* RC_BASIS */
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	ata_scsiop_report_luns - Simulate REPORT LUNS command
 *	@args: device IDENTIFY data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Simulate REPORT LUNS command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_report_luns(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	VPRINTK("ENTER\n");
	rbuf[3] = 8;	/* just one lun, LUN 0, size 8 bytes */

	वापस 0;
पूर्ण

अटल व्योम atapi_sense_complete(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (qc->err_mask && ((qc->err_mask & AC_ERR_DEV) == 0)) अणु
		/* FIXME: not quite right; we करोn't want the
		 * translation of taskfile रेजिस्टरs पूर्णांकo
		 * a sense descriptors, since that's only
		 * correct क्रम ATA, not ATAPI
		 */
		ata_gen_passthru_sense(qc);
	पूर्ण

	ata_qc_करोne(qc);
पूर्ण

/* is it poपूर्णांकless to prefer PIO क्रम "safety reasons"? */
अटल अंतरभूत पूर्णांक ata_pio_use_silly(काष्ठा ata_port *ap)
अणु
	वापस (ap->flags & ATA_FLAG_PIO_DMA);
पूर्ण

अटल व्योम atapi_request_sense(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;

	DPRINTK("ATAPI request sense\n");

	स_रखो(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);

#अगर_घोषित CONFIG_ATA_SFF
	अगर (ap->ops->sff_tf_पढ़ो)
		ap->ops->sff_tf_पढ़ो(ap, &qc->tf);
#पूर्ण_अगर

	/* fill these in, क्रम the हाल where they are -not- overwritten */
	cmd->sense_buffer[0] = 0x70;
	cmd->sense_buffer[2] = qc->tf.feature >> 4;

	ata_qc_reinit(qc);

	/* setup sg table and init transfer direction */
	sg_init_one(&qc->sgent, cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE);
	ata_sg_init(qc, &qc->sgent, 1);
	qc->dma_dir = DMA_FROM_DEVICE;

	स_रखो(&qc->cdb, 0, qc->dev->cdb_len);
	qc->cdb[0] = REQUEST_SENSE;
	qc->cdb[4] = SCSI_SENSE_BUFFERSIZE;

	qc->tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	qc->tf.command = ATA_CMD_PACKET;

	अगर (ata_pio_use_silly(ap)) अणु
		qc->tf.protocol = ATAPI_PROT_DMA;
		qc->tf.feature |= ATAPI_PKT_DMA;
	पूर्ण अन्यथा अणु
		qc->tf.protocol = ATAPI_PROT_PIO;
		qc->tf.lbam = SCSI_SENSE_BUFFERSIZE;
		qc->tf.lbah = 0;
	पूर्ण
	qc->nbytes = SCSI_SENSE_BUFFERSIZE;

	qc->complete_fn = atapi_sense_complete;

	ata_qc_issue(qc);

	DPRINTK("EXIT\n");
पूर्ण

/*
 * ATAPI devices typically report zero क्रम their SCSI version, and someबार
 * deviate from the spec WRT response data क्रमmat.  If SCSI version is
 * reported as zero like normal, then we make the following fixups:
 *   1) Fake MMC-5 version, to indicate to the Linux scsi midlayer this is a
 *	modern device.
 *   2) Ensure response data क्रमmat / ATAPI inक्रमmation are always correct.
 */
अटल व्योम atapi_fixup_inquiry(काष्ठा scsi_cmnd *cmd)
अणु
	u8 buf[4];

	sg_copy_to_buffer(scsi_sglist(cmd), scsi_sg_count(cmd), buf, 4);
	अगर (buf[2] == 0) अणु
		buf[2] = 0x5;
		buf[3] = 0x32;
	पूर्ण
	sg_copy_from_buffer(scsi_sglist(cmd), scsi_sg_count(cmd), buf, 4);
पूर्ण

अटल व्योम atapi_qc_complete(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;
	अचिन्हित पूर्णांक err_mask = qc->err_mask;

	VPRINTK("ENTER, err_mask 0x%X\n", err_mask);

	/* handle completion from new EH */
	अगर (unlikely(qc->ap->ops->error_handler &&
		     (err_mask || qc->flags & ATA_QCFLAG_SENSE_VALID))) अणु

		अगर (!(qc->flags & ATA_QCFLAG_SENSE_VALID)) अणु
			/* FIXME: not quite right; we करोn't want the
			 * translation of taskfile रेजिस्टरs पूर्णांकo a
			 * sense descriptors, since that's only
			 * correct क्रम ATA, not ATAPI
			 */
			ata_gen_passthru_sense(qc);
		पूर्ण

		/* SCSI EH स्वतःmatically locks करोor अगर sdev->locked is
		 * set.  Someबार करोor lock request जारीs to
		 * fail, क्रम example, when no media is present.  This
		 * creates a loop - SCSI EH issues करोor lock which
		 * fails and माला_लो invoked again to acquire sense data
		 * क्रम the failed command.
		 *
		 * If करोor lock fails, always clear sdev->locked to
		 * aव्योम this infinite loop.
		 *
		 * This may happen beक्रमe SCSI scan is complete.  Make
		 * sure qc->dev->sdev isn't शून्य beक्रमe dereferencing.
		 */
		अगर (qc->cdb[0] == ALLOW_MEDIUM_REMOVAL && qc->dev->sdev)
			qc->dev->sdev->locked = 0;

		qc->scsicmd->result = SAM_STAT_CHECK_CONDITION;
		ata_qc_करोne(qc);
		वापस;
	पूर्ण

	/* successful completion or old EH failure path */
	अगर (unlikely(err_mask & AC_ERR_DEV)) अणु
		cmd->result = SAM_STAT_CHECK_CONDITION;
		atapi_request_sense(qc);
		वापस;
	पूर्ण अन्यथा अगर (unlikely(err_mask)) अणु
		/* FIXME: not quite right; we करोn't want the
		 * translation of taskfile रेजिस्टरs पूर्णांकo
		 * a sense descriptors, since that's only
		 * correct क्रम ATA, not ATAPI
		 */
		ata_gen_passthru_sense(qc);
	पूर्ण अन्यथा अणु
		अगर (cmd->cmnd[0] == INQUIRY && (cmd->cmnd[1] & 0x03) == 0)
			atapi_fixup_inquiry(cmd);
		cmd->result = SAM_STAT_GOOD;
	पूर्ण

	ata_qc_करोne(qc);
पूर्ण
/**
 *	atapi_xlat - Initialize PACKET taskfile
 *	@qc: command काष्ठाure to be initialized
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, non-zero on failure.
 */
अटल अचिन्हित पूर्णांक atapi_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	काष्ठा ata_device *dev = qc->dev;
	पूर्णांक nodata = (scmd->sc_data_direction == DMA_NONE);
	पूर्णांक using_pio = !nodata && (dev->flags & ATA_DFLAG_PIO);
	अचिन्हित पूर्णांक nbytes;

	स_रखो(qc->cdb, 0, dev->cdb_len);
	स_नकल(qc->cdb, scmd->cmnd, scmd->cmd_len);

	qc->complete_fn = atapi_qc_complete;

	qc->tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	अगर (scmd->sc_data_direction == DMA_TO_DEVICE) अणु
		qc->tf.flags |= ATA_TFLAG_WRITE;
		DPRINTK("direction: write\n");
	पूर्ण

	qc->tf.command = ATA_CMD_PACKET;
	ata_qc_set_pc_nbytes(qc);

	/* check whether ATAPI DMA is safe */
	अगर (!nodata && !using_pio && atapi_check_dma(qc))
		using_pio = 1;

	/* Some controller variants snoop this value क्रम Packet
	 * transfers to करो state machine and FIFO management.  Thus we
	 * want to set it properly, and क्रम DMA where it is
	 * effectively meaningless.
	 */
	nbytes = min(ata_qc_raw_nbytes(qc), (अचिन्हित पूर्णांक)63 * 1024);

	/* Most ATAPI devices which honor transfer chunk size करोn't
	 * behave according to the spec when odd chunk size which
	 * matches the transfer length is specअगरied.  If the number of
	 * bytes to transfer is 2n+1.  According to the spec, what
	 * should happen is to indicate that 2n+1 is going to be
	 * transferred and transfer 2n+2 bytes where the last byte is
	 * padding.
	 *
	 * In practice, this करोesn't happen.  ATAPI devices first
	 * indicate and transfer 2n bytes and then indicate and
	 * transfer 2 bytes where the last byte is padding.
	 *
	 * This inconsistency confuses several controllers which
	 * perक्रमm PIO using DMA such as Intel AHCIs and sil3124/32.
	 * These controllers use actual number of transferred bytes to
	 * update DMA poपूर्णांकer and transfer of 4n+2 bytes make those
	 * controller push DMA poपूर्णांकer by 4n+4 bytes because SATA data
	 * FISes are aligned to 4 bytes.  This causes data corruption
	 * and buffer overrun.
	 *
	 * Always setting nbytes to even number solves this problem
	 * because then ATAPI devices करोn't have to split data at 2n
	 * boundaries.
	 */
	अगर (nbytes & 0x1)
		nbytes++;

	qc->tf.lbam = (nbytes & 0xFF);
	qc->tf.lbah = (nbytes >> 8);

	अगर (nodata)
		qc->tf.protocol = ATAPI_PROT_NODATA;
	अन्यथा अगर (using_pio)
		qc->tf.protocol = ATAPI_PROT_PIO;
	अन्यथा अणु
		/* DMA data xfer */
		qc->tf.protocol = ATAPI_PROT_DMA;
		qc->tf.feature |= ATAPI_PKT_DMA;

		अगर ((dev->flags & ATA_DFLAG_DMAसूची) &&
		    (scmd->sc_data_direction != DMA_TO_DEVICE))
			/* some SATA bridges need us to indicate data xfer direction */
			qc->tf.feature |= ATAPI_DMAसूची;
	पूर्ण


	/* FIXME: We need to translate 0x05 READ_BLOCK_LIMITS to a MODE_SENSE
	   as ATAPI tape drives करोn't get this right otherwise */
	वापस 0;
पूर्ण

अटल काष्ठा ata_device *ata_find_dev(काष्ठा ata_port *ap, पूर्णांक devno)
अणु
	अगर (!sata_pmp_attached(ap)) अणु
		अगर (likely(devno >= 0 &&
			   devno < ata_link_max_devices(&ap->link)))
			वापस &ap->link.device[devno];
	पूर्ण अन्यथा अणु
		अगर (likely(devno >= 0 &&
			   devno < ap->nr_pmp_links))
			वापस &ap->pmp_link[devno].device[0];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा ata_device *__ata_scsi_find_dev(काष्ठा ata_port *ap,
					      स्थिर काष्ठा scsi_device *scsidev)
अणु
	पूर्णांक devno;

	/* skip commands not addressed to tarमाला_लो we simulate */
	अगर (!sata_pmp_attached(ap)) अणु
		अगर (unlikely(scsidev->channel || scsidev->lun))
			वापस शून्य;
		devno = scsidev->id;
	पूर्ण अन्यथा अणु
		अगर (unlikely(scsidev->id || scsidev->lun))
			वापस शून्य;
		devno = scsidev->channel;
	पूर्ण

	वापस ata_find_dev(ap, devno);
पूर्ण

/**
 *	ata_scsi_find_dev - lookup ata_device from scsi_cmnd
 *	@ap: ATA port to which the device is attached
 *	@scsidev: SCSI device from which we derive the ATA device
 *
 *	Given various inक्रमmation provided in काष्ठा scsi_cmnd,
 *	map that onto an ATA bus, and using that mapping
 *	determine which ata_device is associated with the
 *	SCSI command to be sent.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Associated ATA device, or %शून्य अगर not found.
 */
काष्ठा ata_device *
ata_scsi_find_dev(काष्ठा ata_port *ap, स्थिर काष्ठा scsi_device *scsidev)
अणु
	काष्ठा ata_device *dev = __ata_scsi_find_dev(ap, scsidev);

	अगर (unlikely(!dev || !ata_dev_enabled(dev)))
		वापस शून्य;

	वापस dev;
पूर्ण

/*
 *	ata_scsi_map_proto - Map pass-thru protocol value to taskfile value.
 *	@byte1: Byte 1 from pass-thru CDB.
 *
 *	RETURNS:
 *	ATA_PROT_UNKNOWN अगर mapping failed/unimplemented, protocol otherwise.
 */
अटल u8
ata_scsi_map_proto(u8 byte1)
अणु
	चयन((byte1 & 0x1e) >> 1) अणु
	हाल 3:		/* Non-data */
		वापस ATA_PROT_NODATA;

	हाल 6:		/* DMA */
	हाल 10:	/* UDMA Data-in */
	हाल 11:	/* UDMA Data-Out */
		वापस ATA_PROT_DMA;

	हाल 4:		/* PIO Data-in */
	हाल 5:		/* PIO Data-out */
		वापस ATA_PROT_PIO;

	हाल 12:	/* FPDMA */
		वापस ATA_PROT_NCQ;

	हाल 0:		/* Hard Reset */
	हाल 1:		/* SRST */
	हाल 8:		/* Device Diagnostic */
	हाल 9:		/* Device Reset */
	हाल 7:		/* DMA Queued */
	हाल 15:	/* Return Response Info */
	शेष:	/* Reserved */
		अवरोध;
	पूर्ण

	वापस ATA_PROT_UNKNOWN;
पूर्ण

/**
 *	ata_scsi_pass_thru - convert ATA pass-thru CDB to taskfile
 *	@qc: command काष्ठाure to be initialized
 *
 *	Handles either 12, 16, or 32-byte versions of the CDB.
 *
 *	RETURNS:
 *	Zero on success, non-zero on failure.
 */
अटल अचिन्हित पूर्णांक ata_scsi_pass_thru(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_taskfile *tf = &(qc->tf);
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	काष्ठा ata_device *dev = qc->dev;
	स्थिर u8 *cdb = scmd->cmnd;
	u16 fp;
	u16 cdb_offset = 0;

	/* 7Fh variable length cmd means a ata pass-thru(32) */
	अगर (cdb[0] == VARIABLE_LENGTH_CMD)
		cdb_offset = 9;

	tf->protocol = ata_scsi_map_proto(cdb[1 + cdb_offset]);
	अगर (tf->protocol == ATA_PROT_UNKNOWN) अणु
		fp = 1;
		जाओ invalid_fld;
	पूर्ण

	अगर (ata_is_ncq(tf->protocol) && (cdb[2 + cdb_offset] & 0x3) == 0)
		tf->protocol = ATA_PROT_NCQ_NODATA;

	/* enable LBA */
	tf->flags |= ATA_TFLAG_LBA;

	/*
	 * 12 and 16 byte CDBs use dअगरferent offsets to
	 * provide the various रेजिस्टर values.
	 */
	अगर (cdb[0] == ATA_16) अणु
		/*
		 * 16-byte CDB - may contain extended commands.
		 *
		 * If that is the हाल, copy the upper byte रेजिस्टर values.
		 */
		अगर (cdb[1] & 0x01) अणु
			tf->hob_feature = cdb[3];
			tf->hob_nsect = cdb[5];
			tf->hob_lbal = cdb[7];
			tf->hob_lbam = cdb[9];
			tf->hob_lbah = cdb[11];
			tf->flags |= ATA_TFLAG_LBA48;
		पूर्ण अन्यथा
			tf->flags &= ~ATA_TFLAG_LBA48;

		/*
		 * Always copy low byte, device and command रेजिस्टरs.
		 */
		tf->feature = cdb[4];
		tf->nsect = cdb[6];
		tf->lbal = cdb[8];
		tf->lbam = cdb[10];
		tf->lbah = cdb[12];
		tf->device = cdb[13];
		tf->command = cdb[14];
	पूर्ण अन्यथा अगर (cdb[0] == ATA_12) अणु
		/*
		 * 12-byte CDB - incapable of extended commands.
		 */
		tf->flags &= ~ATA_TFLAG_LBA48;

		tf->feature = cdb[3];
		tf->nsect = cdb[4];
		tf->lbal = cdb[5];
		tf->lbam = cdb[6];
		tf->lbah = cdb[7];
		tf->device = cdb[8];
		tf->command = cdb[9];
	पूर्ण अन्यथा अणु
		/*
		 * 32-byte CDB - may contain extended command fields.
		 *
		 * If that is the हाल, copy the upper byte रेजिस्टर values.
		 */
		अगर (cdb[10] & 0x01) अणु
			tf->hob_feature = cdb[20];
			tf->hob_nsect = cdb[22];
			tf->hob_lbal = cdb[16];
			tf->hob_lbam = cdb[15];
			tf->hob_lbah = cdb[14];
			tf->flags |= ATA_TFLAG_LBA48;
		पूर्ण अन्यथा
			tf->flags &= ~ATA_TFLAG_LBA48;

		tf->feature = cdb[21];
		tf->nsect = cdb[23];
		tf->lbal = cdb[19];
		tf->lbam = cdb[18];
		tf->lbah = cdb[17];
		tf->device = cdb[24];
		tf->command = cdb[25];
		tf->auxiliary = get_unaligned_be32(&cdb[28]);
	पूर्ण

	/* For NCQ commands copy the tag value */
	अगर (ata_is_ncq(tf->protocol))
		tf->nsect = qc->hw_tag << 3;

	/* enक्रमce correct master/slave bit */
	tf->device = dev->devno ?
		tf->device | ATA_DEV1 : tf->device & ~ATA_DEV1;

	चयन (tf->command) अणु
	/* READ/WRITE LONG use a non-standard sect_size */
	हाल ATA_CMD_READ_LONG:
	हाल ATA_CMD_READ_LONG_ONCE:
	हाल ATA_CMD_WRITE_LONG:
	हाल ATA_CMD_WRITE_LONG_ONCE:
		अगर (tf->protocol != ATA_PROT_PIO || tf->nsect != 1) अणु
			fp = 1;
			जाओ invalid_fld;
		पूर्ण
		qc->sect_size = scsi_bufflen(scmd);
		अवरोध;

	/* commands using reported Logical Block size (e.g. 512 or 4K) */
	हाल ATA_CMD_CFA_WRITE_NE:
	हाल ATA_CMD_CFA_TRANS_SECT:
	हाल ATA_CMD_CFA_WRITE_MULT_NE:
	/* XXX: हाल ATA_CMD_CFA_WRITE_SECTORS_WITHOUT_ERASE: */
	हाल ATA_CMD_READ:
	हाल ATA_CMD_READ_EXT:
	हाल ATA_CMD_READ_QUEUED:
	/* XXX: हाल ATA_CMD_READ_QUEUED_EXT: */
	हाल ATA_CMD_FPDMA_READ:
	हाल ATA_CMD_READ_MULTI:
	हाल ATA_CMD_READ_MULTI_EXT:
	हाल ATA_CMD_PIO_READ:
	हाल ATA_CMD_PIO_READ_EXT:
	हाल ATA_CMD_READ_STREAM_DMA_EXT:
	हाल ATA_CMD_READ_STREAM_EXT:
	हाल ATA_CMD_VERIFY:
	हाल ATA_CMD_VERIFY_EXT:
	हाल ATA_CMD_WRITE:
	हाल ATA_CMD_WRITE_EXT:
	हाल ATA_CMD_WRITE_FUA_EXT:
	हाल ATA_CMD_WRITE_QUEUED:
	हाल ATA_CMD_WRITE_QUEUED_FUA_EXT:
	हाल ATA_CMD_FPDMA_WRITE:
	हाल ATA_CMD_WRITE_MULTI:
	हाल ATA_CMD_WRITE_MULTI_EXT:
	हाल ATA_CMD_WRITE_MULTI_FUA_EXT:
	हाल ATA_CMD_PIO_WRITE:
	हाल ATA_CMD_PIO_WRITE_EXT:
	हाल ATA_CMD_WRITE_STREAM_DMA_EXT:
	हाल ATA_CMD_WRITE_STREAM_EXT:
		qc->sect_size = scmd->device->sector_size;
		अवरोध;

	/* Everything अन्यथा uses 512 byte "sectors" */
	शेष:
		qc->sect_size = ATA_SECT_SIZE;
	पूर्ण

	/*
	 * Set flags so that all रेजिस्टरs will be written, pass on
	 * ग_लिखो indication (used क्रम PIO/DMA setup), result TF is
	 * copied back and we करोn't whine too much about its failure.
	 */
	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	अगर (scmd->sc_data_direction == DMA_TO_DEVICE)
		tf->flags |= ATA_TFLAG_WRITE;

	qc->flags |= ATA_QCFLAG_RESULT_TF | ATA_QCFLAG_QUIET;

	/*
	 * Set transfer length.
	 *
	 * TODO: find out अगर we need to करो more here to
	 *       cover scatter/gather हाल.
	 */
	ata_qc_set_pc_nbytes(qc);

	/* We may not issue DMA commands अगर no DMA mode is set */
	अगर (tf->protocol == ATA_PROT_DMA && dev->dma_mode == 0) अणु
		fp = 1;
		जाओ invalid_fld;
	पूर्ण

	/* We may not issue NCQ commands to devices not supporting NCQ */
	अगर (ata_is_ncq(tf->protocol) && !ata_ncq_enabled(dev)) अणु
		fp = 1;
		जाओ invalid_fld;
	पूर्ण

	/* sanity check क्रम pio multi commands */
	अगर ((cdb[1] & 0xe0) && !is_multi_taskfile(tf)) अणु
		fp = 1;
		जाओ invalid_fld;
	पूर्ण

	अगर (is_multi_taskfile(tf)) अणु
		अचिन्हित पूर्णांक multi_count = 1 << (cdb[1] >> 5);

		/* compare the passed through multi_count
		 * with the cached multi_count of libata
		 */
		अगर (multi_count != dev->multi_count)
			ata_dev_warn(dev, "invalid multi_count %u ignored\n",
				     multi_count);
	पूर्ण

	/*
	 * Filter SET_FEATURES - XFER MODE command -- otherwise,
	 * SET_FEATURES - XFER MODE must be preceded/succeeded
	 * by an update to hardware-specअगरic रेजिस्टरs क्रम each
	 * controller (i.e. the reason क्रम ->set_piomode(),
	 * ->set_dmamode(), and ->post_set_mode() hooks).
	 */
	अगर (tf->command == ATA_CMD_SET_FEATURES &&
	    tf->feature == SETFEATURES_XFER) अणु
		fp = (cdb[0] == ATA_16) ? 4 : 3;
		जाओ invalid_fld;
	पूर्ण

	/*
	 * Filter TPM commands by शेष. These provide an
	 * essentially uncontrolled encrypted "back door" between
	 * applications and the disk. Set libata.allow_tpm=1 अगर you
	 * have a real reason क्रम wanting to use them. This ensures
	 * that installed software cannot easily mess stuff up without
	 * user पूर्णांकent. DVR type users will probably ship with this enabled
	 * क्रम movie content management.
	 *
	 * Note that क्रम ATA8 we can issue a DCS change and DCS मुक्तze lock
	 * क्रम this and should करो in future but that it is not sufficient as
	 * DCS is an optional feature set. Thus we also करो the software filter
	 * so that we comply with the TC consortium stated goal that the user
	 * can turn off TC features of their प्रणाली.
	 */
	अगर (tf->command >= 0x5C && tf->command <= 0x5F && !libata_allow_tpm) अणु
		fp = (cdb[0] == ATA_16) ? 14 : 9;
		जाओ invalid_fld;
	पूर्ण

	वापस 0;

 invalid_fld:
	ata_scsi_set_invalid_field(dev, scmd, fp, 0xff);
	वापस 1;
पूर्ण

/**
 * ata_क्रमmat_dsm_trim_descr() - SATL Write Same to DSM Trim
 * @cmd: SCSI command being translated
 * @trmax: Maximum number of entries that will fit in sector_size bytes.
 * @sector: Starting sector
 * @count: Total Range of request in logical sectors
 *
 * Reग_लिखो the WRITE SAME descriptor to be a DSM TRIM little-endian क्रमmatted
 * descriptor.
 *
 * Upto 64 entries of the क्रमmat:
 *   63:48 Range Length
 *   47:0  LBA
 *
 *  Range Length of 0 is ignored.
 *  LBA's should be sorted order and not overlap.
 *
 * NOTE: this is the same क्रमmat as ADD LBA(S) TO NV CACHE PINNED SET
 *
 * Return: Number of bytes copied पूर्णांकo sglist.
 */
अटल माप_प्रकार ata_क्रमmat_dsm_trim_descr(काष्ठा scsi_cmnd *cmd, u32 trmax,
					u64 sector, u32 count)
अणु
	काष्ठा scsi_device *sdp = cmd->device;
	माप_प्रकार len = sdp->sector_size;
	माप_प्रकार r;
	__le64 *buf;
	u32 i = 0;
	अचिन्हित दीर्घ flags;

	WARN_ON(len > ATA_SCSI_RBUF_SIZE);

	अगर (len > ATA_SCSI_RBUF_SIZE)
		len = ATA_SCSI_RBUF_SIZE;

	spin_lock_irqsave(&ata_scsi_rbuf_lock, flags);
	buf = ((व्योम *)ata_scsi_rbuf);
	स_रखो(buf, 0, len);
	जबतक (i < trmax) अणु
		u64 entry = sector |
			((u64)(count > 0xffff ? 0xffff : count) << 48);
		buf[i++] = __cpu_to_le64(entry);
		अगर (count <= 0xffff)
			अवरोध;
		count -= 0xffff;
		sector += 0xffff;
	पूर्ण
	r = sg_copy_from_buffer(scsi_sglist(cmd), scsi_sg_count(cmd), buf, len);
	spin_unlock_irqrestore(&ata_scsi_rbuf_lock, flags);

	वापस r;
पूर्ण

/**
 * ata_scsi_ग_लिखो_same_xlat() - SATL Write Same to ATA SCT Write Same
 * @qc: Command to be translated
 *
 * Translate a SCSI WRITE SAME command to be either a DSM TRIM command or
 * an SCT Write Same command.
 * Based on WRITE SAME has the UNMAP flag:
 *
 *   - When set translate to DSM TRIM
 *   - When clear translate to SCT Write Same
 */
अटल अचिन्हित पूर्णांक ata_scsi_ग_लिखो_same_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_taskfile *tf = &qc->tf;
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	काष्ठा scsi_device *sdp = scmd->device;
	माप_प्रकार len = sdp->sector_size;
	काष्ठा ata_device *dev = qc->dev;
	स्थिर u8 *cdb = scmd->cmnd;
	u64 block;
	u32 n_block;
	स्थिर u32 trmax = len >> 3;
	u32 size;
	u16 fp;
	u8 bp = 0xff;
	u8 unmap = cdb[1] & 0x8;

	/* we may not issue DMA commands अगर no DMA mode is set */
	अगर (unlikely(!dev->dma_mode))
		जाओ invalid_opcode;

	/*
	 * We only allow sending this command through the block layer,
	 * as it modअगरies the DATA OUT buffer, which would corrupt user
	 * memory क्रम SG_IO commands.
	 */
	अगर (unlikely(blk_rq_is_passthrough(scmd->request)))
		जाओ invalid_opcode;

	अगर (unlikely(scmd->cmd_len < 16)) अणु
		fp = 15;
		जाओ invalid_fld;
	पूर्ण
	scsi_16_lba_len(cdb, &block, &n_block);

	अगर (!unmap ||
	    (dev->horkage & ATA_HORKAGE_NOTRIM) ||
	    !ata_id_has_trim(dev->id)) अणु
		fp = 1;
		bp = 3;
		जाओ invalid_fld;
	पूर्ण
	/* If the request is too large the cmd is invalid */
	अगर (n_block > 0xffff * trmax) अणु
		fp = 2;
		जाओ invalid_fld;
	पूर्ण

	/*
	 * WRITE SAME always has a sector sized buffer as payload, this
	 * should never be a multiple entry S/G list.
	 */
	अगर (!scsi_sg_count(scmd))
		जाओ invalid_param_len;

	/*
	 * size must match sector size in bytes
	 * For DATA SET MANAGEMENT TRIM in ACS-2 nsect (aka count)
	 * is defined as number of 512 byte blocks to be transferred.
	 */

	size = ata_क्रमmat_dsm_trim_descr(scmd, trmax, block, n_block);
	अगर (size != len)
		जाओ invalid_param_len;

	अगर (ata_ncq_enabled(dev) && ata_fpdma_dsm_supported(dev)) अणु
		/* Newer devices support queued TRIM commands */
		tf->protocol = ATA_PROT_NCQ;
		tf->command = ATA_CMD_FPDMA_SEND;
		tf->hob_nsect = ATA_SUBCMD_FPDMA_SEND_DSM & 0x1f;
		tf->nsect = qc->hw_tag << 3;
		tf->hob_feature = (size / 512) >> 8;
		tf->feature = size / 512;

		tf->auxiliary = 1;
	पूर्ण अन्यथा अणु
		tf->protocol = ATA_PROT_DMA;
		tf->hob_feature = 0;
		tf->feature = ATA_DSM_TRIM;
		tf->hob_nsect = (size / 512) >> 8;
		tf->nsect = size / 512;
		tf->command = ATA_CMD_DSM;
	पूर्ण

	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48 |
		     ATA_TFLAG_WRITE;

	ata_qc_set_pc_nbytes(qc);

	वापस 0;

invalid_fld:
	ata_scsi_set_invalid_field(dev, scmd, fp, bp);
	वापस 1;
invalid_param_len:
	/* "Parameter list length error" */
	ata_scsi_set_sense(dev, scmd, ILLEGAL_REQUEST, 0x1a, 0x0);
	वापस 1;
invalid_opcode:
	/* "Invalid command operation code" */
	ata_scsi_set_sense(dev, scmd, ILLEGAL_REQUEST, 0x20, 0x0);
	वापस 1;
पूर्ण

/**
 *	ata_scsiop_मुख्यt_in - Simulate a subset of MAINTEन_अंकCE_IN
 *	@args: device MAINTEन_अंकCE_IN data / SCSI command of पूर्णांकerest.
 *	@rbuf: Response buffer, to which simulated SCSI cmd output is sent.
 *
 *	Yields a subset to satisfy scsi_report_opcode()
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsiop_मुख्यt_in(काष्ठा ata_scsi_args *args, u8 *rbuf)
अणु
	काष्ठा ata_device *dev = args->dev;
	u8 *cdb = args->cmd->cmnd;
	u8 supported = 0;
	अचिन्हित पूर्णांक err = 0;

	अगर (cdb[2] != 1) अणु
		ata_dev_warn(dev, "invalid command format %d\n", cdb[2]);
		err = 2;
		जाओ out;
	पूर्ण
	चयन (cdb[3]) अणु
	हाल INQUIRY:
	हाल MODE_SENSE:
	हाल MODE_SENSE_10:
	हाल READ_CAPACITY:
	हाल SERVICE_ACTION_IN_16:
	हाल REPORT_LUNS:
	हाल REQUEST_SENSE:
	हाल SYNCHRONIZE_CACHE:
	हाल REZERO_UNIT:
	हाल SEEK_6:
	हाल SEEK_10:
	हाल TEST_UNIT_READY:
	हाल SEND_DIAGNOSTIC:
	हाल MAINTEन_अंकCE_IN:
	हाल READ_6:
	हाल READ_10:
	हाल READ_16:
	हाल WRITE_6:
	हाल WRITE_10:
	हाल WRITE_16:
	हाल ATA_12:
	हाल ATA_16:
	हाल VERIFY:
	हाल VERIFY_16:
	हाल MODE_SELECT:
	हाल MODE_SELECT_10:
	हाल START_STOP:
		supported = 3;
		अवरोध;
	हाल ZBC_IN:
	हाल ZBC_OUT:
		अगर (ata_id_zoned_cap(dev->id) ||
		    dev->class == ATA_DEV_ZAC)
			supported = 3;
		अवरोध;
	हाल SECURITY_PROTOCOL_IN:
	हाल SECURITY_PROTOCOL_OUT:
		अगर (dev->flags & ATA_DFLAG_TRUSTED)
			supported = 3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out:
	rbuf[1] = supported; /* supported */
	वापस err;
पूर्ण

/**
 *	ata_scsi_report_zones_complete - convert ATA output
 *	@qc: command काष्ठाure वापसing the data
 *
 *	Convert T-13 little-endian field representation पूर्णांकo
 *	T-10 big-endian field representation.
 *	What a mess.
 */
अटल व्योम ata_scsi_report_zones_complete(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	काष्ठा sg_mapping_iter miter;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bytes = 0;

	sg_miter_start(&miter, scsi_sglist(scmd), scsi_sg_count(scmd),
		       SG_MITER_TO_SG | SG_MITER_ATOMIC);

	local_irq_save(flags);
	जबतक (sg_miter_next(&miter)) अणु
		अचिन्हित पूर्णांक offset = 0;

		अगर (bytes == 0) अणु
			अक्षर *hdr;
			u32 list_length;
			u64 max_lba, opt_lba;
			u16 same;

			/* Swizzle header */
			hdr = miter.addr;
			list_length = get_unaligned_le32(&hdr[0]);
			same = get_unaligned_le16(&hdr[4]);
			max_lba = get_unaligned_le64(&hdr[8]);
			opt_lba = get_unaligned_le64(&hdr[16]);
			put_unaligned_be32(list_length, &hdr[0]);
			hdr[4] = same & 0xf;
			put_unaligned_be64(max_lba, &hdr[8]);
			put_unaligned_be64(opt_lba, &hdr[16]);
			offset += 64;
			bytes += 64;
		पूर्ण
		जबतक (offset < miter.length) अणु
			अक्षर *rec;
			u8 cond, type, non_seq, reset;
			u64 size, start, wp;

			/* Swizzle zone descriptor */
			rec = miter.addr + offset;
			type = rec[0] & 0xf;
			cond = (rec[1] >> 4) & 0xf;
			non_seq = (rec[1] & 2);
			reset = (rec[1] & 1);
			size = get_unaligned_le64(&rec[8]);
			start = get_unaligned_le64(&rec[16]);
			wp = get_unaligned_le64(&rec[24]);
			rec[0] = type;
			rec[1] = (cond << 4) | non_seq | reset;
			put_unaligned_be64(size, &rec[8]);
			put_unaligned_be64(start, &rec[16]);
			put_unaligned_be64(wp, &rec[24]);
			WARN_ON(offset + 64 > miter.length);
			offset += 64;
			bytes += 64;
		पूर्ण
	पूर्ण
	sg_miter_stop(&miter);
	local_irq_restore(flags);

	ata_scsi_qc_complete(qc);
पूर्ण

अटल अचिन्हित पूर्णांक ata_scsi_zbc_in_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_taskfile *tf = &qc->tf;
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	स्थिर u8 *cdb = scmd->cmnd;
	u16 sect, fp = (u16)-1;
	u8 sa, options, bp = 0xff;
	u64 block;
	u32 n_block;

	अगर (unlikely(scmd->cmd_len < 16)) अणु
		ata_dev_warn(qc->dev, "invalid cdb length %d\n",
			     scmd->cmd_len);
		fp = 15;
		जाओ invalid_fld;
	पूर्ण
	scsi_16_lba_len(cdb, &block, &n_block);
	अगर (n_block != scsi_bufflen(scmd)) अणु
		ata_dev_warn(qc->dev, "non-matching transfer count (%d/%d)\n",
			     n_block, scsi_bufflen(scmd));
		जाओ invalid_param_len;
	पूर्ण
	sa = cdb[1] & 0x1f;
	अगर (sa != ZI_REPORT_ZONES) अणु
		ata_dev_warn(qc->dev, "invalid service action %d\n", sa);
		fp = 1;
		जाओ invalid_fld;
	पूर्ण
	/*
	 * ZAC allows only क्रम transfers in 512 byte blocks,
	 * and uses a 16 bit value क्रम the transfer count.
	 */
	अगर ((n_block / 512) > 0xffff || n_block < 512 || (n_block % 512)) अणु
		ata_dev_warn(qc->dev, "invalid transfer count %d\n", n_block);
		जाओ invalid_param_len;
	पूर्ण
	sect = n_block / 512;
	options = cdb[14] & 0xbf;

	अगर (ata_ncq_enabled(qc->dev) &&
	    ata_fpdma_zac_mgmt_in_supported(qc->dev)) अणु
		tf->protocol = ATA_PROT_NCQ;
		tf->command = ATA_CMD_FPDMA_RECV;
		tf->hob_nsect = ATA_SUBCMD_FPDMA_RECV_ZAC_MGMT_IN & 0x1f;
		tf->nsect = qc->hw_tag << 3;
		tf->feature = sect & 0xff;
		tf->hob_feature = (sect >> 8) & 0xff;
		tf->auxiliary = ATA_SUBCMD_ZAC_MGMT_IN_REPORT_ZONES | (options << 8);
	पूर्ण अन्यथा अणु
		tf->command = ATA_CMD_ZAC_MGMT_IN;
		tf->feature = ATA_SUBCMD_ZAC_MGMT_IN_REPORT_ZONES;
		tf->protocol = ATA_PROT_DMA;
		tf->hob_feature = options;
		tf->hob_nsect = (sect >> 8) & 0xff;
		tf->nsect = sect & 0xff;
	पूर्ण
	tf->device = ATA_LBA;
	tf->lbah = (block >> 16) & 0xff;
	tf->lbam = (block >> 8) & 0xff;
	tf->lbal = block & 0xff;
	tf->hob_lbah = (block >> 40) & 0xff;
	tf->hob_lbam = (block >> 32) & 0xff;
	tf->hob_lbal = (block >> 24) & 0xff;

	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48;
	qc->flags |= ATA_QCFLAG_RESULT_TF;

	ata_qc_set_pc_nbytes(qc);

	qc->complete_fn = ata_scsi_report_zones_complete;

	वापस 0;

invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, bp);
	वापस 1;

invalid_param_len:
	/* "Parameter list length error" */
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x1a, 0x0);
	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक ata_scsi_zbc_out_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_taskfile *tf = &qc->tf;
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	काष्ठा ata_device *dev = qc->dev;
	स्थिर u8 *cdb = scmd->cmnd;
	u8 all, sa;
	u64 block;
	u32 n_block;
	u16 fp = (u16)-1;

	अगर (unlikely(scmd->cmd_len < 16)) अणु
		fp = 15;
		जाओ invalid_fld;
	पूर्ण

	sa = cdb[1] & 0x1f;
	अगर ((sa != ZO_CLOSE_ZONE) && (sa != ZO_FINISH_ZONE) &&
	    (sa != ZO_OPEN_ZONE) && (sa != ZO_RESET_WRITE_POINTER)) अणु
		fp = 1;
		जाओ invalid_fld;
	पूर्ण

	scsi_16_lba_len(cdb, &block, &n_block);
	अगर (n_block) अणु
		/*
		 * ZAC MANAGEMENT OUT करोesn't define any length
		 */
		जाओ invalid_param_len;
	पूर्ण

	all = cdb[14] & 0x1;
	अगर (all) अणु
		/*
		 * Ignore the block address (zone ID) as defined by ZBC.
		 */
		block = 0;
	पूर्ण अन्यथा अगर (block >= dev->n_sectors) अणु
		/*
		 * Block must be a valid zone ID (a zone start LBA).
		 */
		fp = 2;
		जाओ invalid_fld;
	पूर्ण

	अगर (ata_ncq_enabled(qc->dev) &&
	    ata_fpdma_zac_mgmt_out_supported(qc->dev)) अणु
		tf->protocol = ATA_PROT_NCQ_NODATA;
		tf->command = ATA_CMD_NCQ_NON_DATA;
		tf->feature = ATA_SUBCMD_NCQ_NON_DATA_ZAC_MGMT_OUT;
		tf->nsect = qc->hw_tag << 3;
		tf->auxiliary = sa | ((u16)all << 8);
	पूर्ण अन्यथा अणु
		tf->protocol = ATA_PROT_NODATA;
		tf->command = ATA_CMD_ZAC_MGMT_OUT;
		tf->feature = sa;
		tf->hob_feature = all;
	पूर्ण
	tf->lbah = (block >> 16) & 0xff;
	tf->lbam = (block >> 8) & 0xff;
	tf->lbal = block & 0xff;
	tf->hob_lbah = (block >> 40) & 0xff;
	tf->hob_lbam = (block >> 32) & 0xff;
	tf->hob_lbal = (block >> 24) & 0xff;
	tf->device = ATA_LBA;
	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48;

	वापस 0;

 invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, 0xff);
	वापस 1;
invalid_param_len:
	/* "Parameter list length error" */
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x1a, 0x0);
	वापस 1;
पूर्ण

/**
 *	ata_mselect_caching - Simulate MODE SELECT क्रम caching info page
 *	@qc: Storage क्रम translated ATA taskfile
 *	@buf: input buffer
 *	@len: number of valid bytes in the input buffer
 *	@fp: out parameter क्रम the failed field on error
 *
 *	Prepare a taskfile to modअगरy caching inक्रमmation क्रम the device.
 *
 *	LOCKING:
 *	None.
 */
अटल पूर्णांक ata_mselect_caching(काष्ठा ata_queued_cmd *qc,
			       स्थिर u8 *buf, पूर्णांक len, u16 *fp)
अणु
	काष्ठा ata_taskfile *tf = &qc->tf;
	काष्ठा ata_device *dev = qc->dev;
	u8 mpage[CACHE_MPAGE_LEN];
	u8 wce;
	पूर्णांक i;

	/*
	 * The first two bytes of def_cache_mpage are a header, so offsets
	 * in mpage are off by 2 compared to buf.  Same क्रम len.
	 */

	अगर (len != CACHE_MPAGE_LEN - 2) अणु
		अगर (len < CACHE_MPAGE_LEN - 2)
			*fp = len;
		अन्यथा
			*fp = CACHE_MPAGE_LEN - 2;
		वापस -EINVAL;
	पूर्ण

	wce = buf[0] & (1 << 2);

	/*
	 * Check that पढ़ो-only bits are not modअगरied.
	 */
	ata_msense_caching(dev->id, mpage, false);
	क्रम (i = 0; i < CACHE_MPAGE_LEN - 2; i++) अणु
		अगर (i == 0)
			जारी;
		अगर (mpage[i + 2] != buf[i]) अणु
			*fp = i;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	tf->flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;
	tf->protocol = ATA_PROT_NODATA;
	tf->nsect = 0;
	tf->command = ATA_CMD_SET_FEATURES;
	tf->feature = wce ? SETFEATURES_WC_ON : SETFEATURES_WC_OFF;
	वापस 0;
पूर्ण

/**
 *	ata_mselect_control - Simulate MODE SELECT क्रम control page
 *	@qc: Storage क्रम translated ATA taskfile
 *	@buf: input buffer
 *	@len: number of valid bytes in the input buffer
 *	@fp: out parameter क्रम the failed field on error
 *
 *	Prepare a taskfile to modअगरy caching inक्रमmation क्रम the device.
 *
 *	LOCKING:
 *	None.
 */
अटल पूर्णांक ata_mselect_control(काष्ठा ata_queued_cmd *qc,
			       स्थिर u8 *buf, पूर्णांक len, u16 *fp)
अणु
	काष्ठा ata_device *dev = qc->dev;
	u8 mpage[CONTROL_MPAGE_LEN];
	u8 d_sense;
	पूर्णांक i;

	/*
	 * The first two bytes of def_control_mpage are a header, so offsets
	 * in mpage are off by 2 compared to buf.  Same क्रम len.
	 */

	अगर (len != CONTROL_MPAGE_LEN - 2) अणु
		अगर (len < CONTROL_MPAGE_LEN - 2)
			*fp = len;
		अन्यथा
			*fp = CONTROL_MPAGE_LEN - 2;
		वापस -EINVAL;
	पूर्ण

	d_sense = buf[0] & (1 << 2);

	/*
	 * Check that पढ़ो-only bits are not modअगरied.
	 */
	ata_msense_control(dev, mpage, false);
	क्रम (i = 0; i < CONTROL_MPAGE_LEN - 2; i++) अणु
		अगर (i == 0)
			जारी;
		अगर (mpage[2 + i] != buf[i]) अणु
			*fp = i;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (d_sense & (1 << 2))
		dev->flags |= ATA_DFLAG_D_SENSE;
	अन्यथा
		dev->flags &= ~ATA_DFLAG_D_SENSE;
	वापस 0;
पूर्ण

/**
 *	ata_scsi_mode_select_xlat - Simulate MODE SELECT 6, 10 commands
 *	@qc: Storage क्रम translated ATA taskfile
 *
 *	Converts a MODE SELECT command to an ATA SET FEATURES taskfile.
 *	Assume this is invoked क्रम direct access devices (e.g. disks) only.
 *	There should be no block descriptor क्रम other device types.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अचिन्हित पूर्णांक ata_scsi_mode_select_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	स्थिर u8 *cdb = scmd->cmnd;
	u8 pg, spg;
	अचिन्हित six_byte, pg_len, hdr_len, bd_len;
	पूर्णांक len;
	u16 fp = (u16)-1;
	u8 bp = 0xff;
	u8 buffer[64];
	स्थिर u8 *p = buffer;

	VPRINTK("ENTER\n");

	six_byte = (cdb[0] == MODE_SELECT);
	अगर (six_byte) अणु
		अगर (scmd->cmd_len < 5) अणु
			fp = 4;
			जाओ invalid_fld;
		पूर्ण

		len = cdb[4];
		hdr_len = 4;
	पूर्ण अन्यथा अणु
		अगर (scmd->cmd_len < 9) अणु
			fp = 8;
			जाओ invalid_fld;
		पूर्ण

		len = (cdb[7] << 8) + cdb[8];
		hdr_len = 8;
	पूर्ण

	/* We only support PF=1, SP=0.  */
	अगर ((cdb[1] & 0x11) != 0x10) अणु
		fp = 1;
		bp = (cdb[1] & 0x01) ? 1 : 5;
		जाओ invalid_fld;
	पूर्ण

	/* Test early क्रम possible overrun.  */
	अगर (!scsi_sg_count(scmd) || scsi_sglist(scmd)->length < len)
		जाओ invalid_param_len;

	/* Move past header and block descriptors.  */
	अगर (len < hdr_len)
		जाओ invalid_param_len;

	अगर (!sg_copy_to_buffer(scsi_sglist(scmd), scsi_sg_count(scmd),
			       buffer, माप(buffer)))
		जाओ invalid_param_len;

	अगर (six_byte)
		bd_len = p[3];
	अन्यथा
		bd_len = (p[6] << 8) + p[7];

	len -= hdr_len;
	p += hdr_len;
	अगर (len < bd_len)
		जाओ invalid_param_len;
	अगर (bd_len != 0 && bd_len != 8) अणु
		fp = (six_byte) ? 3 : 6;
		fp += bd_len + hdr_len;
		जाओ invalid_param;
	पूर्ण

	len -= bd_len;
	p += bd_len;
	अगर (len == 0)
		जाओ skip;

	/* Parse both possible क्रमmats क्रम the mode page headers.  */
	pg = p[0] & 0x3f;
	अगर (p[0] & 0x40) अणु
		अगर (len < 4)
			जाओ invalid_param_len;

		spg = p[1];
		pg_len = (p[2] << 8) | p[3];
		p += 4;
		len -= 4;
	पूर्ण अन्यथा अणु
		अगर (len < 2)
			जाओ invalid_param_len;

		spg = 0;
		pg_len = p[1];
		p += 2;
		len -= 2;
	पूर्ण

	/*
	 * No mode subpages supported (yet) but asking क्रम _all_
	 * subpages may be valid
	 */
	अगर (spg && (spg != ALL_SUB_MPAGES)) अणु
		fp = (p[0] & 0x40) ? 1 : 0;
		fp += hdr_len + bd_len;
		जाओ invalid_param;
	पूर्ण
	अगर (pg_len > len)
		जाओ invalid_param_len;

	चयन (pg) अणु
	हाल CACHE_MPAGE:
		अगर (ata_mselect_caching(qc, p, pg_len, &fp) < 0) अणु
			fp += hdr_len + bd_len;
			जाओ invalid_param;
		पूर्ण
		अवरोध;
	हाल CONTROL_MPAGE:
		अगर (ata_mselect_control(qc, p, pg_len, &fp) < 0) अणु
			fp += hdr_len + bd_len;
			जाओ invalid_param;
		पूर्ण अन्यथा अणु
			जाओ skip; /* No ATA command to send */
		पूर्ण
		अवरोध;
	शेष:		/* invalid page code */
		fp = bd_len + hdr_len;
		जाओ invalid_param;
	पूर्ण

	/*
	 * Only one page has changeable data, so we only support setting one
	 * page at a समय.
	 */
	अगर (len > pg_len)
		जाओ invalid_param;

	वापस 0;

 invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, bp);
	वापस 1;

 invalid_param:
	ata_scsi_set_invalid_parameter(qc->dev, scmd, fp);
	वापस 1;

 invalid_param_len:
	/* "Parameter list length error" */
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x1a, 0x0);
	वापस 1;

 skip:
	scmd->result = SAM_STAT_GOOD;
	वापस 1;
पूर्ण

अटल u8 ata_scsi_trusted_op(u32 len, bool send, bool dma)
अणु
	अगर (len == 0)
		वापस ATA_CMD_TRUSTED_NONDATA;
	अन्यथा अगर (send)
		वापस dma ? ATA_CMD_TRUSTED_SND_DMA : ATA_CMD_TRUSTED_SND;
	अन्यथा
		वापस dma ? ATA_CMD_TRUSTED_RCV_DMA : ATA_CMD_TRUSTED_RCV;
पूर्ण

अटल अचिन्हित पूर्णांक ata_scsi_security_inout_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	स्थिर u8 *cdb = scmd->cmnd;
	काष्ठा ata_taskfile *tf = &qc->tf;
	u8 secp = cdb[1];
	bool send = (cdb[0] == SECURITY_PROTOCOL_OUT);
	u16 spsp = get_unaligned_be16(&cdb[2]);
	u32 len = get_unaligned_be32(&cdb[6]);
	bool dma = !(qc->dev->flags & ATA_DFLAG_PIO);

	/*
	 * We करोn't support the ATA "security" protocol.
	 */
	अगर (secp == 0xef) अणु
		ata_scsi_set_invalid_field(qc->dev, scmd, 1, 0);
		वापस 1;
	पूर्ण

	अगर (cdb[4] & 7) अणु /* INC_512 */
		अगर (len > 0xffff) अणु
			ata_scsi_set_invalid_field(qc->dev, scmd, 6, 0);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (len > 0x01fffe00) अणु
			ata_scsi_set_invalid_field(qc->dev, scmd, 6, 0);
			वापस 1;
		पूर्ण

		/* convert to the sector-based ATA addressing */
		len = (len + 511) / 512;
	पूर्ण

	tf->protocol = dma ? ATA_PROT_DMA : ATA_PROT_PIO;
	tf->flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR | ATA_TFLAG_LBA;
	अगर (send)
		tf->flags |= ATA_TFLAG_WRITE;
	tf->command = ata_scsi_trusted_op(len, send, dma);
	tf->feature = secp;
	tf->lbam = spsp & 0xff;
	tf->lbah = spsp >> 8;

	अगर (len) अणु
		tf->nsect = len & 0xff;
		tf->lbal = len >> 8;
	पूर्ण अन्यथा अणु
		अगर (!send)
			tf->lbah = (1 << 7);
	पूर्ण

	ata_qc_set_pc_nbytes(qc);
	वापस 0;
पूर्ण

/**
 *	ata_scsi_var_len_cdb_xlat - SATL variable length CDB to Handler
 *	@qc: Command to be translated
 *
 *	Translate a SCSI variable length CDB to specअगरied commands.
 *	It checks a service action value in CDB to call corresponding handler.
 *
 *	RETURNS:
 *	Zero on success, non-zero on failure
 *
 */
अटल अचिन्हित पूर्णांक ata_scsi_var_len_cdb_xlat(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	स्थिर u8 *cdb = scmd->cmnd;
	स्थिर u16 sa = get_unaligned_be16(&cdb[8]);

	/*
	 * अगर service action represents a ata pass-thru(32) command,
	 * then pass it to ata_scsi_pass_thru handler.
	 */
	अगर (sa == ATA_32)
		वापस ata_scsi_pass_thru(qc);

	/* unsupported service action */
	वापस 1;
पूर्ण

/**
 *	ata_get_xlat_func - check अगर SCSI to ATA translation is possible
 *	@dev: ATA device
 *	@cmd: SCSI command opcode to consider
 *
 *	Look up the SCSI command given, and determine whether the
 *	SCSI command is to be translated or simulated.
 *
 *	RETURNS:
 *	Poपूर्णांकer to translation function अगर possible, %शून्य अगर not.
 */

अटल अंतरभूत ata_xlat_func_t ata_get_xlat_func(काष्ठा ata_device *dev, u8 cmd)
अणु
	चयन (cmd) अणु
	हाल READ_6:
	हाल READ_10:
	हाल READ_16:

	हाल WRITE_6:
	हाल WRITE_10:
	हाल WRITE_16:
		वापस ata_scsi_rw_xlat;

	हाल WRITE_SAME_16:
		वापस ata_scsi_ग_लिखो_same_xlat;

	हाल SYNCHRONIZE_CACHE:
		अगर (ata_try_flush_cache(dev))
			वापस ata_scsi_flush_xlat;
		अवरोध;

	हाल VERIFY:
	हाल VERIFY_16:
		वापस ata_scsi_verअगरy_xlat;

	हाल ATA_12:
	हाल ATA_16:
		वापस ata_scsi_pass_thru;

	हाल VARIABLE_LENGTH_CMD:
		वापस ata_scsi_var_len_cdb_xlat;

	हाल MODE_SELECT:
	हाल MODE_SELECT_10:
		वापस ata_scsi_mode_select_xlat;
		अवरोध;

	हाल ZBC_IN:
		वापस ata_scsi_zbc_in_xlat;

	हाल ZBC_OUT:
		वापस ata_scsi_zbc_out_xlat;

	हाल SECURITY_PROTOCOL_IN:
	हाल SECURITY_PROTOCOL_OUT:
		अगर (!(dev->flags & ATA_DFLAG_TRUSTED))
			अवरोध;
		वापस ata_scsi_security_inout_xlat;

	हाल START_STOP:
		वापस ata_scsi_start_stop_xlat;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 *	ata_scsi_dump_cdb - dump SCSI command contents to dmesg
 *	@ap: ATA port to which the command was being sent
 *	@cmd: SCSI command to dump
 *
 *	Prपूर्णांकs the contents of a SCSI command via prपूर्णांकk().
 */

व्योम ata_scsi_dump_cdb(काष्ठा ata_port *ap, काष्ठा scsi_cmnd *cmd)
अणु
#अगर_घोषित ATA_VERBOSE_DEBUG
	काष्ठा scsi_device *scsidev = cmd->device;

	VPRINTK("CDB (%u:%d,%d,%lld) %9ph\n",
		ap->prपूर्णांक_id,
		scsidev->channel, scsidev->id, scsidev->lun,
		cmd->cmnd);
#पूर्ण_अगर
पूर्ण

पूर्णांक __ata_scsi_queuecmd(काष्ठा scsi_cmnd *scmd, काष्ठा ata_device *dev)
अणु
	u8 scsi_op = scmd->cmnd[0];
	ata_xlat_func_t xlat_func;
	पूर्णांक rc = 0;

	अगर (dev->class == ATA_DEV_ATA || dev->class == ATA_DEV_ZAC) अणु
		अगर (unlikely(!scmd->cmd_len || scmd->cmd_len > dev->cdb_len))
			जाओ bad_cdb_len;

		xlat_func = ata_get_xlat_func(dev, scsi_op);
	पूर्ण अन्यथा अणु
		अगर (unlikely(!scmd->cmd_len))
			जाओ bad_cdb_len;

		xlat_func = शून्य;
		अगर (likely((scsi_op != ATA_16) || !atapi_passthru16)) अणु
			/* relay SCSI command to ATAPI device */
			पूर्णांक len = COMMAND_SIZE(scsi_op);
			अगर (unlikely(len > scmd->cmd_len ||
				     len > dev->cdb_len ||
				     scmd->cmd_len > ATAPI_CDB_LEN))
				जाओ bad_cdb_len;

			xlat_func = atapi_xlat;
		पूर्ण अन्यथा अणु
			/* ATA_16 passthru, treat as an ATA command */
			अगर (unlikely(scmd->cmd_len > 16))
				जाओ bad_cdb_len;

			xlat_func = ata_get_xlat_func(dev, scsi_op);
		पूर्ण
	पूर्ण

	अगर (xlat_func)
		rc = ata_scsi_translate(dev, scmd, xlat_func);
	अन्यथा
		ata_scsi_simulate(dev, scmd);

	वापस rc;

 bad_cdb_len:
	DPRINTK("bad CDB len=%u, scsi_op=0x%02x, max=%u\n",
		scmd->cmd_len, scsi_op, dev->cdb_len);
	scmd->result = DID_ERROR << 16;
	scmd->scsi_करोne(scmd);
	वापस 0;
पूर्ण

/**
 *	ata_scsi_queuecmd - Issue SCSI cdb to libata-managed device
 *	@shost: SCSI host of command to be sent
 *	@cmd: SCSI command to be sent
 *
 *	In some हालs, this function translates SCSI commands पूर्णांकo
 *	ATA taskfiles, and queues the taskfiles to be sent to
 *	hardware.  In other हालs, this function simulates a
 *	SCSI device by evaluating and responding to certain
 *	SCSI commands.  This creates the overall effect of
 *	ATA and ATAPI devices appearing as SCSI devices.
 *
 *	LOCKING:
 *	ATA host lock
 *
 *	RETURNS:
 *	Return value from __ata_scsi_queuecmd() अगर @cmd can be queued,
 *	0 otherwise.
 */
पूर्णांक ata_scsi_queuecmd(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ata_port *ap;
	काष्ठा ata_device *dev;
	काष्ठा scsi_device *scsidev = cmd->device;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ irq_flags;

	ap = ata_shost_to_port(shost);

	spin_lock_irqsave(ap->lock, irq_flags);

	ata_scsi_dump_cdb(ap, cmd);

	dev = ata_scsi_find_dev(ap, scsidev);
	अगर (likely(dev))
		rc = __ata_scsi_queuecmd(cmd, dev);
	अन्यथा अणु
		cmd->result = (DID_BAD_TARGET << 16);
		cmd->scsi_करोne(cmd);
	पूर्ण

	spin_unlock_irqrestore(ap->lock, irq_flags);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_queuecmd);

/**
 *	ata_scsi_simulate - simulate SCSI command on ATA device
 *	@dev: the target device
 *	@cmd: SCSI command being sent to device.
 *
 *	Interprets and directly executes a select list of SCSI commands
 *	that can be handled पूर्णांकernally.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */

व्योम ata_scsi_simulate(काष्ठा ata_device *dev, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ata_scsi_args args;
	स्थिर u8 *scsicmd = cmd->cmnd;
	u8 पंचांगp8;

	args.dev = dev;
	args.id = dev->id;
	args.cmd = cmd;

	चयन(scsicmd[0]) अणु
	हाल INQUIRY:
		अगर (scsicmd[1] & 2)		   /* is CmdDt set?  */
			ata_scsi_set_invalid_field(dev, cmd, 1, 0xff);
		अन्यथा अगर ((scsicmd[1] & 1) == 0)    /* is EVPD clear? */
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_std);
		अन्यथा चयन (scsicmd[2]) अणु
		हाल 0x00:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_00);
			अवरोध;
		हाल 0x80:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_80);
			अवरोध;
		हाल 0x83:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_83);
			अवरोध;
		हाल 0x89:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_89);
			अवरोध;
		हाल 0xb0:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_b0);
			अवरोध;
		हाल 0xb1:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_b1);
			अवरोध;
		हाल 0xb2:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_b2);
			अवरोध;
		हाल 0xb6:
			अगर (dev->flags & ATA_DFLAG_ZAC) अणु
				ata_scsi_rbuf_fill(&args, ata_scsiop_inq_b6);
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			ata_scsi_set_invalid_field(dev, cmd, 2, 0xff);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल MODE_SENSE:
	हाल MODE_SENSE_10:
		ata_scsi_rbuf_fill(&args, ata_scsiop_mode_sense);
		अवरोध;

	हाल READ_CAPACITY:
		ata_scsi_rbuf_fill(&args, ata_scsiop_पढ़ो_cap);
		अवरोध;

	हाल SERVICE_ACTION_IN_16:
		अगर ((scsicmd[1] & 0x1f) == SAI_READ_CAPACITY_16)
			ata_scsi_rbuf_fill(&args, ata_scsiop_पढ़ो_cap);
		अन्यथा
			ata_scsi_set_invalid_field(dev, cmd, 1, 0xff);
		अवरोध;

	हाल REPORT_LUNS:
		ata_scsi_rbuf_fill(&args, ata_scsiop_report_luns);
		अवरोध;

	हाल REQUEST_SENSE:
		ata_scsi_set_sense(dev, cmd, 0, 0, 0);
		cmd->result = (DRIVER_SENSE << 24);
		अवरोध;

	/* अगर we reach this, then ग_लिखोback caching is disabled,
	 * turning this पूर्णांकo a no-op.
	 */
	हाल SYNCHRONIZE_CACHE:
		fallthrough;

	/* no-op's, complete with success */
	हाल REZERO_UNIT:
	हाल SEEK_6:
	हाल SEEK_10:
	हाल TEST_UNIT_READY:
		अवरोध;

	हाल SEND_DIAGNOSTIC:
		पंचांगp8 = scsicmd[1] & ~(1 << 3);
		अगर (पंचांगp8 != 0x4 || scsicmd[3] || scsicmd[4])
			ata_scsi_set_invalid_field(dev, cmd, 1, 0xff);
		अवरोध;

	हाल MAINTEन_अंकCE_IN:
		अगर (scsicmd[1] == MI_REPORT_SUPPORTED_OPERATION_CODES)
			ata_scsi_rbuf_fill(&args, ata_scsiop_मुख्यt_in);
		अन्यथा
			ata_scsi_set_invalid_field(dev, cmd, 1, 0xff);
		अवरोध;

	/* all other commands */
	शेष:
		ata_scsi_set_sense(dev, cmd, ILLEGAL_REQUEST, 0x20, 0x0);
		/* "Invalid command operation code" */
		अवरोध;
	पूर्ण

	cmd->scsi_करोne(cmd);
पूर्ण

पूर्णांक ata_scsi_add_hosts(काष्ठा ata_host *host, काष्ठा scsi_host_ढाँचा *sht)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा Scsi_Host *shost;

		rc = -ENOMEM;
		shost = scsi_host_alloc(sht, माप(काष्ठा ata_port *));
		अगर (!shost)
			जाओ err_alloc;

		shost->eh_noresume = 1;
		*(काष्ठा ata_port **)&shost->hostdata[0] = ap;
		ap->scsi_host = shost;

		shost->transportt = ata_scsi_transport_ढाँचा;
		shost->unique_id = ap->prपूर्णांक_id;
		shost->max_id = 16;
		shost->max_lun = 1;
		shost->max_channel = 1;
		shost->max_cmd_len = 32;

		/* Schedule policy is determined by ->qc_defer()
		 * callback and it needs to see every deferred qc.
		 * Set host_blocked to 1 to prevent SCSI midlayer from
		 * स्वतःmatically deferring requests.
		 */
		shost->max_host_blocked = 1;

		rc = scsi_add_host_with_dma(shost, &ap->tdev, ap->host->dev);
		अगर (rc)
			जाओ err_alloc;
	पूर्ण

	वापस 0;

 err_alloc:
	जबतक (--i >= 0) अणु
		काष्ठा Scsi_Host *shost = host->ports[i]->scsi_host;

		/* scsi_host_put() is in ata_devres_release() */
		scsi_हटाओ_host(shost);
	पूर्ण
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल व्योम ata_scsi_assign_ofnode(काष्ठा ata_device *dev, काष्ठा ata_port *ap)
अणु
	काष्ठा scsi_device *sdev = dev->sdev;
	काष्ठा device *d = ap->host->dev;
	काष्ठा device_node *np = d->of_node;
	काष्ठा device_node *child;

	क्रम_each_available_child_of_node(np, child) अणु
		पूर्णांक ret;
		u32 val;

		ret = of_property_पढ़ो_u32(child, "reg", &val);
		अगर (ret)
			जारी;
		अगर (val == dev->devno) अणु
			dev_dbg(d, "found matching device node\n");
			sdev->sdev_gendev.of_node = child;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम ata_scsi_assign_ofnode(काष्ठा ata_device *dev, काष्ठा ata_port *ap)
अणु
पूर्ण
#पूर्ण_अगर

व्योम ata_scsi_scan_host(काष्ठा ata_port *ap, पूर्णांक sync)
अणु
	पूर्णांक tries = 5;
	काष्ठा ata_device *last_failed_dev = शून्य;
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;

 repeat:
	ata_क्रम_each_link(link, ap, EDGE) अणु
		ata_क्रम_each_dev(dev, link, ENABLED) अणु
			काष्ठा scsi_device *sdev;
			पूर्णांक channel = 0, id = 0;

			अगर (dev->sdev)
				जारी;

			अगर (ata_is_host_link(link))
				id = dev->devno;
			अन्यथा
				channel = link->pmp;

			sdev = __scsi_add_device(ap->scsi_host, channel, id, 0,
						 शून्य);
			अगर (!IS_ERR(sdev)) अणु
				dev->sdev = sdev;
				ata_scsi_assign_ofnode(dev, ap);
				scsi_device_put(sdev);
			पूर्ण अन्यथा अणु
				dev->sdev = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If we scanned जबतक EH was in progress or allocation
	 * failure occurred, scan would have failed silently.  Check
	 * whether all devices are attached.
	 */
	ata_क्रम_each_link(link, ap, EDGE) अणु
		ata_क्रम_each_dev(dev, link, ENABLED) अणु
			अगर (!dev->sdev)
				जाओ निकास_loop;
		पूर्ण
	पूर्ण
 निकास_loop:
	अगर (!link)
		वापस;

	/* we're missing some SCSI devices */
	अगर (sync) अणु
		/* If caller requested synchrnous scan && we've made
		 * any progress, sleep briefly and repeat.
		 */
		अगर (dev != last_failed_dev) अणु
			msleep(100);
			last_failed_dev = dev;
			जाओ repeat;
		पूर्ण

		/* We might be failing to detect boot device, give it
		 * a few more chances.
		 */
		अगर (--tries) अणु
			msleep(100);
			जाओ repeat;
		पूर्ण

		ata_port_err(ap,
			     "WARNING: synchronous SCSI scan failed without making any progress, switching to async\n");
	पूर्ण

	queue_delayed_work(प्रणाली_दीर्घ_wq, &ap->hotplug_task,
			   round_jअगरfies_relative(HZ));
पूर्ण

/**
 *	ata_scsi_offline_dev - offline attached SCSI device
 *	@dev: ATA device to offline attached SCSI device क्रम
 *
 *	This function is called from ata_eh_hotplug() and responsible
 *	क्रम taking the SCSI device attached to @dev offline.  This
 *	function is called with host lock which protects dev->sdev
 *	against clearing.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	1 अगर attached SCSI device exists, 0 otherwise.
 */
पूर्णांक ata_scsi_offline_dev(काष्ठा ata_device *dev)
अणु
	अगर (dev->sdev) अणु
		scsi_device_set_state(dev->sdev, SDEV_OFFLINE);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	ata_scsi_हटाओ_dev - हटाओ attached SCSI device
 *	@dev: ATA device to हटाओ attached SCSI device क्रम
 *
 *	This function is called from ata_eh_scsi_hotplug() and
 *	responsible क्रम removing the SCSI device attached to @dev.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
अटल व्योम ata_scsi_हटाओ_dev(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ flags;

	/* Alas, we need to grab scan_mutex to ensure SCSI device
	 * state करोesn't change underneath us and thus
	 * scsi_device_get() always succeeds.  The mutex locking can
	 * be हटाओd अगर there is __scsi_device_get() पूर्णांकerface which
	 * increments reference counts regardless of device state.
	 */
	mutex_lock(&ap->scsi_host->scan_mutex);
	spin_lock_irqsave(ap->lock, flags);

	/* clearing dev->sdev is रक्षित by host lock */
	sdev = dev->sdev;
	dev->sdev = शून्य;

	अगर (sdev) अणु
		/* If user initiated unplug races with us, sdev can go
		 * away underneath us after the host lock and
		 * scan_mutex are released.  Hold onto it.
		 */
		अगर (scsi_device_get(sdev) == 0) अणु
			/* The following ensures the attached sdev is
			 * offline on वापस from ata_scsi_offline_dev()
			 * regardless it wins or loses the race
			 * against this function.
			 */
			scsi_device_set_state(sdev, SDEV_OFFLINE);
		पूर्ण अन्यथा अणु
			WARN_ON(1);
			sdev = शून्य;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(ap->lock, flags);
	mutex_unlock(&ap->scsi_host->scan_mutex);

	अगर (sdev) अणु
		ata_dev_info(dev, "detaching (SCSI %s)\n",
			     dev_name(&sdev->sdev_gendev));

		scsi_हटाओ_device(sdev);
		scsi_device_put(sdev);
	पूर्ण
पूर्ण

अटल व्योम ata_scsi_handle_link_detach(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, link, ALL) अणु
		अचिन्हित दीर्घ flags;

		अगर (!(dev->flags & ATA_DFLAG_DETACHED))
			जारी;

		spin_lock_irqsave(ap->lock, flags);
		dev->flags &= ~ATA_DFLAG_DETACHED;
		spin_unlock_irqrestore(ap->lock, flags);

		अगर (zpodd_dev_enabled(dev))
			zpodd_निकास(dev);

		ata_scsi_हटाओ_dev(dev);
	पूर्ण
पूर्ण

/**
 *	ata_scsi_media_change_notअगरy - send media change event
 *	@dev: Poपूर्णांकer to the disk device with media change event
 *
 *	Tell the block layer to send a media change notअगरication
 *	event.
 *
 * 	LOCKING:
 * 	spin_lock_irqsave(host lock)
 */
व्योम ata_scsi_media_change_notअगरy(काष्ठा ata_device *dev)
अणु
	अगर (dev->sdev)
		sdev_evt_send_simple(dev->sdev, SDEV_EVT_MEDIA_CHANGE,
				     GFP_ATOMIC);
पूर्ण

/**
 *	ata_scsi_hotplug - SCSI part of hotplug
 *	@work: Poपूर्णांकer to ATA port to perक्रमm SCSI hotplug on
 *
 *	Perक्रमm SCSI part of hotplug.  It's executed from a separate
 *	workqueue after EH completes.  This is necessary because SCSI
 *	hot plugging requires working EH and hot unplugging is
 *	synchronized with hot plugging with a mutex.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_scsi_hotplug(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ata_port *ap =
		container_of(work, काष्ठा ata_port, hotplug_task.work);
	पूर्णांक i;

	अगर (ap->pflags & ATA_PFLAG_UNLOADING) अणु
		DPRINTK("ENTER/EXIT - unloading\n");
		वापस;
	पूर्ण

	DPRINTK("ENTER\n");
	mutex_lock(&ap->scsi_scan_mutex);

	/* Unplug detached devices.  We cannot use link iterator here
	 * because PMP links have to be scanned even अगर PMP is
	 * currently not attached.  Iterate manually.
	 */
	ata_scsi_handle_link_detach(&ap->link);
	अगर (ap->pmp_link)
		क्रम (i = 0; i < SATA_PMP_MAX_PORTS; i++)
			ata_scsi_handle_link_detach(&ap->pmp_link[i]);

	/* scan क्रम new ones */
	ata_scsi_scan_host(ap, 0);

	mutex_unlock(&ap->scsi_scan_mutex);
	DPRINTK("EXIT\n");
पूर्ण

/**
 *	ata_scsi_user_scan - indication क्रम user-initiated bus scan
 *	@shost: SCSI host to scan
 *	@channel: Channel to scan
 *	@id: ID to scan
 *	@lun: LUN to scan
 *
 *	This function is called when user explicitly requests bus
 *	scan.  Set probe pending flag and invoke EH.
 *
 *	LOCKING:
 *	SCSI layer (we करोn't care)
 *
 *	RETURNS:
 *	Zero.
 */
पूर्णांक ata_scsi_user_scan(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक channel,
		       अचिन्हित पूर्णांक id, u64 lun)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	अचिन्हित दीर्घ flags;
	पूर्णांक devno, rc = 0;

	अगर (!ap->ops->error_handler)
		वापस -EOPNOTSUPP;

	अगर (lun != SCAN_WILD_CARD && lun)
		वापस -EINVAL;

	अगर (!sata_pmp_attached(ap)) अणु
		अगर (channel != SCAN_WILD_CARD && channel)
			वापस -EINVAL;
		devno = id;
	पूर्ण अन्यथा अणु
		अगर (id != SCAN_WILD_CARD && id)
			वापस -EINVAL;
		devno = channel;
	पूर्ण

	spin_lock_irqsave(ap->lock, flags);

	अगर (devno == SCAN_WILD_CARD) अणु
		काष्ठा ata_link *link;

		ata_क्रम_each_link(link, ap, EDGE) अणु
			काष्ठा ata_eh_info *ehi = &link->eh_info;
			ehi->probe_mask |= ATA_ALL_DEVICES;
			ehi->action |= ATA_EH_RESET;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ata_device *dev = ata_find_dev(ap, devno);

		अगर (dev) अणु
			काष्ठा ata_eh_info *ehi = &dev->link->eh_info;
			ehi->probe_mask |= 1 << dev->devno;
			ehi->action |= ATA_EH_RESET;
		पूर्ण अन्यथा
			rc = -EINVAL;
	पूर्ण

	अगर (rc == 0) अणु
		ata_port_schedule_eh(ap);
		spin_unlock_irqrestore(ap->lock, flags);
		ata_port_रुको_eh(ap);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(ap->lock, flags);

	वापस rc;
पूर्ण

/**
 *	ata_scsi_dev_rescan - initiate scsi_rescan_device()
 *	@work: Poपूर्णांकer to ATA port to perक्रमm scsi_rescan_device()
 *
 *	After ATA pass thru (SAT) commands are executed successfully,
 *	libata need to propagate the changes to SCSI layer.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_scsi_dev_rescan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ata_port *ap =
		container_of(work, काष्ठा ata_port, scsi_rescan_task);
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ flags;

	mutex_lock(&ap->scsi_scan_mutex);
	spin_lock_irqsave(ap->lock, flags);

	ata_क्रम_each_link(link, ap, EDGE) अणु
		ata_क्रम_each_dev(dev, link, ENABLED) अणु
			काष्ठा scsi_device *sdev = dev->sdev;

			अगर (!sdev)
				जारी;
			अगर (scsi_device_get(sdev))
				जारी;

			spin_unlock_irqrestore(ap->lock, flags);
			scsi_rescan_device(&(sdev->sdev_gendev));
			scsi_device_put(sdev);
			spin_lock_irqsave(ap->lock, flags);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(ap->lock, flags);
	mutex_unlock(&ap->scsi_scan_mutex);
पूर्ण
