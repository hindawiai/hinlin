<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sr.c Copyright (C) 1992 David Giller
 *           Copyright (C) 1993, 1994, 1995, 1999 Eric Youngdale
 *
 *  adapted from:
 *      sd.c Copyright (C) 1992 Drew Eckhardt
 *      Linux scsi disk driver by
 *              Drew Eckhardt <drew@coloraकरो.edu>
 *
 *	Modअगरied by Eric Youngdale ericy@andante.org to
 *	add scatter-gather, multiple outstanding request, and other
 *	enhancements.
 *
 *      Modअगरied by Eric Youngdale eric@andante.org to support loadable
 *      low-level scsi drivers.
 *
 *      Modअगरied by Thomas Quinot thomas@melchior.cuivre.fdn.fr to
 *      provide स्वतः-eject.
 *
 *      Modअगरied by Gerd Knorr <kraxel@cs.tu-berlin.de> to support the
 *      generic cdrom पूर्णांकerface
 *
 *      Modअगरied by Jens Axboe <axboe@suse.de> - Unअगरorm sr_packet()
 *      पूर्णांकerface, capabilities probe additions, ioctl cleanups, etc.
 *
 *	Modअगरied by Riअक्षरd Gooch <rgooch@atnf.csiro.au> to support devfs
 *
 *	Modअगरied by Jens Axboe <axboe@suse.de> - support DVD-RAM
 *	transparently and lose the GHOST hack
 *
 *	Modअगरied by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *	check resource allocation in sr_init and some cleanups
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/bपन.स>
#समावेश <linux/compat.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cdrom.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-pm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>	/* For the करोor lock/unlock commands */

#समावेश "scsi_logging.h"
#समावेश "sr.h"


MODULE_DESCRIPTION("SCSI cdrom (sr) driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_CDROM_MAJOR);
MODULE_ALIAS_SCSI_DEVICE(TYPE_ROM);
MODULE_ALIAS_SCSI_DEVICE(TYPE_WORM);

#घोषणा SR_DISKS	256

#घोषणा SR_CAPABILITIES \
	(CDC_CLOSE_TRAY|CDC_OPEN_TRAY|CDC_LOCK|CDC_SELECT_SPEED| \
	 CDC_SELECT_DISC|CDC_MULTI_SESSION|CDC_MCN|CDC_MEDIA_CHANGED| \
	 CDC_PLAY_AUDIO|CDC_RESET|CDC_DRIVE_STATUS| \
	 CDC_CD_R|CDC_CD_RW|CDC_DVD|CDC_DVD_R|CDC_DVD_RAM|CDC_GENERIC_PACKET| \
	 CDC_MRW|CDC_MRW_W|CDC_RAM)

अटल पूर्णांक sr_probe(काष्ठा device *);
अटल पूर्णांक sr_हटाओ(काष्ठा device *);
अटल blk_status_t sr_init_command(काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक sr_करोne(काष्ठा scsi_cmnd *);
अटल पूर्णांक sr_runसमय_suspend(काष्ठा device *dev);

अटल स्थिर काष्ठा dev_pm_ops sr_pm_ops = अणु
	.runसमय_suspend	= sr_runसमय_suspend,
पूर्ण;

अटल काष्ठा scsi_driver sr_ढाँचा = अणु
	.gendrv = अणु
		.name   	= "sr",
		.owner		= THIS_MODULE,
		.probe		= sr_probe,
		.हटाओ		= sr_हटाओ,
		.pm		= &sr_pm_ops,
	पूर्ण,
	.init_command		= sr_init_command,
	.करोne			= sr_करोne,
पूर्ण;

अटल अचिन्हित दीर्घ sr_index_bits[SR_DISKS / BITS_PER_LONG];
अटल DEFINE_SPINLOCK(sr_index_lock);

/* This semaphore is used to mediate the 0->1 reference get in the
 * face of object deकाष्ठाion (i.e. we can't allow a get on an
 * object after last put) */
अटल DEFINE_MUTEX(sr_ref_mutex);

अटल पूर्णांक sr_खोलो(काष्ठा cdrom_device_info *, पूर्णांक);
अटल व्योम sr_release(काष्ठा cdrom_device_info *);

अटल व्योम get_sectorsize(काष्ठा scsi_cd *);
अटल व्योम get_capabilities(काष्ठा scsi_cd *);

अटल अचिन्हित पूर्णांक sr_check_events(काष्ठा cdrom_device_info *cdi,
				    अचिन्हित पूर्णांक clearing, पूर्णांक slot);
अटल पूर्णांक sr_packet(काष्ठा cdrom_device_info *, काष्ठा packet_command *);

अटल स्थिर काष्ठा cdrom_device_ops sr_करोps = अणु
	.खोलो			= sr_खोलो,
	.release	 	= sr_release,
	.drive_status	 	= sr_drive_status,
	.check_events		= sr_check_events,
	.tray_move		= sr_tray_move,
	.lock_करोor		= sr_lock_करोor,
	.select_speed		= sr_select_speed,
	.get_last_session	= sr_get_last_session,
	.get_mcn		= sr_get_mcn,
	.reset			= sr_reset,
	.audio_ioctl		= sr_audio_ioctl,
	.capability		= SR_CAPABILITIES,
	.generic_packet		= sr_packet,
पूर्ण;

अटल व्योम sr_kref_release(काष्ठा kref *kref);

अटल अंतरभूत काष्ठा scsi_cd *scsi_cd(काष्ठा gendisk *disk)
अणु
	वापस container_of(disk->निजी_data, काष्ठा scsi_cd, driver);
पूर्ण

अटल पूर्णांक sr_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा scsi_cd *cd = dev_get_drvdata(dev);

	अगर (!cd)	/* E.g.: runसमय suspend following sr_हटाओ() */
		वापस 0;

	अगर (cd->media_present)
		वापस -EBUSY;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * The get and put routines क्रम the काष्ठा scsi_cd.  Note this entity
 * has a scsi_device poपूर्णांकer and owns a reference to this.
 */
अटल अंतरभूत काष्ठा scsi_cd *scsi_cd_get(काष्ठा gendisk *disk)
अणु
	काष्ठा scsi_cd *cd = शून्य;

	mutex_lock(&sr_ref_mutex);
	अगर (disk->निजी_data == शून्य)
		जाओ out;
	cd = scsi_cd(disk);
	kref_get(&cd->kref);
	अगर (scsi_device_get(cd->device)) अणु
		kref_put(&cd->kref, sr_kref_release);
		cd = शून्य;
	पूर्ण
 out:
	mutex_unlock(&sr_ref_mutex);
	वापस cd;
पूर्ण

अटल व्योम scsi_cd_put(काष्ठा scsi_cd *cd)
अणु
	काष्ठा scsi_device *sdev = cd->device;

	mutex_lock(&sr_ref_mutex);
	kref_put(&cd->kref, sr_kref_release);
	scsi_device_put(sdev);
	mutex_unlock(&sr_ref_mutex);
पूर्ण

अटल अचिन्हित पूर्णांक sr_get_events(काष्ठा scsi_device *sdev)
अणु
	u8 buf[8];
	u8 cmd[] = अणु GET_EVENT_STATUS_NOTIFICATION,
		     1,			/* polled */
		     0, 0,		/* reserved */
		     1 << 4,		/* notअगरication class: media */
		     0, 0,		/* reserved */
		     0, माप(buf),	/* allocation length */
		     0,			/* control */
	पूर्ण;
	काष्ठा event_header *eh = (व्योम *)buf;
	काष्ठा media_event_desc *med = (व्योम *)(buf + 4);
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक result;

	result = scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buf, माप(buf),
				  &sshdr, SR_TIMEOUT, MAX_RETRIES, शून्य);
	अगर (scsi_sense_valid(&sshdr) && sshdr.sense_key == UNIT_ATTENTION)
		वापस DISK_EVENT_MEDIA_CHANGE;

	अगर (result || be16_to_cpu(eh->data_len) < माप(*med))
		वापस 0;

	अगर (eh->nea || eh->notअगरication_class != 0x4)
		वापस 0;

	अगर (med->media_event_code == 1)
		वापस DISK_EVENT_EJECT_REQUEST;
	अन्यथा अगर (med->media_event_code == 2)
		वापस DISK_EVENT_MEDIA_CHANGE;
	वापस 0;
पूर्ण

/*
 * This function checks to see अगर the media has been changed or eject
 * button has been pressed.  It is possible that we have alपढ़ोy
 * sensed a change, or the drive may have sensed one and not yet
 * reported it.  The past events are accumulated in sdev->changed and
 * वापसed together with the current state.
 */
अटल अचिन्हित पूर्णांक sr_check_events(काष्ठा cdrom_device_info *cdi,
				    अचिन्हित पूर्णांक clearing, पूर्णांक slot)
अणु
	काष्ठा scsi_cd *cd = cdi->handle;
	bool last_present;
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित पूर्णांक events;
	पूर्णांक ret;

	/* no changer support */
	अगर (CDSL_CURRENT != slot)
		वापस 0;

	events = sr_get_events(cd->device);
	cd->get_event_changed |= events & DISK_EVENT_MEDIA_CHANGE;

	/*
	 * If earlier GET_EVENT_STATUS_NOTIFICATION and TUR did not agree
	 * क्रम several बार in a row.  We rely on TUR only क्रम this likely
	 * broken device, to prevent generating incorrect media changed
	 * events क्रम every खोलो().
	 */
	अगर (cd->ignore_get_event) अणु
		events &= ~DISK_EVENT_MEDIA_CHANGE;
		जाओ करो_tur;
	पूर्ण

	/*
	 * GET_EVENT_STATUS_NOTIFICATION is enough unless MEDIA_CHANGE
	 * is being cleared.  Note that there are devices which hang
	 * अगर asked to execute TUR repeatedly.
	 */
	अगर (cd->device->changed) अणु
		events |= DISK_EVENT_MEDIA_CHANGE;
		cd->device->changed = 0;
		cd->tur_changed = true;
	पूर्ण

	अगर (!(clearing & DISK_EVENT_MEDIA_CHANGE))
		वापस events;
करो_tur:
	/* let's see whether the media is there with TUR */
	last_present = cd->media_present;
	ret = scsi_test_unit_पढ़ोy(cd->device, SR_TIMEOUT, MAX_RETRIES, &sshdr);

	/*
	 * Media is considered to be present अगर TUR succeeds or fails with
	 * sense data indicating something other than media-not-present
	 * (ASC 0x3a).
	 */
	cd->media_present = scsi_status_is_good(ret) ||
		(scsi_sense_valid(&sshdr) && sshdr.asc != 0x3a);

	अगर (last_present != cd->media_present)
		cd->device->changed = 1;

	अगर (cd->device->changed) अणु
		events |= DISK_EVENT_MEDIA_CHANGE;
		cd->device->changed = 0;
		cd->tur_changed = true;
	पूर्ण

	अगर (cd->ignore_get_event)
		वापस events;

	/* check whether GET_EVENT is reporting spurious MEDIA_CHANGE */
	अगर (!cd->tur_changed) अणु
		अगर (cd->get_event_changed) अणु
			अगर (cd->tur_mismatch++ > 8) अणु
				sr_prपूर्णांकk(KERN_WARNING, cd,
					  "GET_EVENT and TUR disagree continuously, suppress GET_EVENT events\n");
				cd->ignore_get_event = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			cd->tur_mismatch = 0;
		पूर्ण
	पूर्ण
	cd->tur_changed = false;
	cd->get_event_changed = false;

	वापस events;
पूर्ण

/*
 * sr_करोne is the पूर्णांकerrupt routine क्रम the device driver.
 *
 * It will be notअगरied on the end of a SCSI पढ़ो / ग_लिखो, and will take one
 * of several actions based on success or failure.
 */
अटल पूर्णांक sr_करोne(काष्ठा scsi_cmnd *SCpnt)
अणु
	पूर्णांक result = SCpnt->result;
	पूर्णांक this_count = scsi_bufflen(SCpnt);
	पूर्णांक good_bytes = (result == 0 ? this_count : 0);
	पूर्णांक block_sectors = 0;
	दीर्घ error_sector;
	काष्ठा scsi_cd *cd = scsi_cd(SCpnt->request->rq_disk);

#अगर_घोषित DEBUG
	scmd_prपूर्णांकk(KERN_INFO, SCpnt, "done: %x\n", result);
#पूर्ण_अगर

	/*
	 * Handle MEDIUM ERRORs or VOLUME OVERFLOWs that indicate partial
	 * success.  Since this is a relatively rare error condition, no
	 * care is taken to aव्योम unnecessary additional work such as
	 * स_नकल's that could be aव्योमed.
	 */
	अगर (driver_byte(result) != 0 &&		/* An error occurred */
	    (SCpnt->sense_buffer[0] & 0x7f) == 0x70) अणु /* Sense current */
		चयन (SCpnt->sense_buffer[2]) अणु
		हाल MEDIUM_ERROR:
		हाल VOLUME_OVERFLOW:
		हाल ILLEGAL_REQUEST:
			अगर (!(SCpnt->sense_buffer[0] & 0x90))
				अवरोध;
			error_sector =
				get_unaligned_be32(&SCpnt->sense_buffer[3]);
			अगर (SCpnt->request->bio != शून्य)
				block_sectors =
					bio_sectors(SCpnt->request->bio);
			अगर (block_sectors < 4)
				block_sectors = 4;
			अगर (cd->device->sector_size == 2048)
				error_sector <<= 2;
			error_sector &= ~(block_sectors - 1);
			good_bytes = (error_sector -
				      blk_rq_pos(SCpnt->request)) << 9;
			अगर (good_bytes < 0 || good_bytes >= this_count)
				good_bytes = 0;
			/*
			 * The SCSI specअगरication allows क्रम the value
			 * वापसed by READ CAPACITY to be up to 75 2K
			 * sectors past the last पढ़ोable block.
			 * Thereक्रमe, अगर we hit a medium error within the
			 * last 75 2K sectors, we decrease the saved size
			 * value.
			 */
			अगर (error_sector < get_capacity(cd->disk) &&
			    cd->capacity - error_sector < 4 * 75)
				set_capacity(cd->disk, error_sector);
			अवरोध;

		हाल RECOVERED_ERROR:
			good_bytes = this_count;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस good_bytes;
पूर्ण

अटल blk_status_t sr_init_command(काष्ठा scsi_cmnd *SCpnt)
अणु
	पूर्णांक block = 0, this_count, s_size;
	काष्ठा scsi_cd *cd;
	काष्ठा request *rq = SCpnt->request;
	blk_status_t ret;

	ret = scsi_alloc_sgtables(SCpnt);
	अगर (ret != BLK_STS_OK)
		वापस ret;
	cd = scsi_cd(rq->rq_disk);

	SCSI_LOG_HLQUEUE(1, scmd_prपूर्णांकk(KERN_INFO, SCpnt,
		"Doing sr request, block = %d\n", block));

	अगर (!cd->device || !scsi_device_online(cd->device)) अणु
		SCSI_LOG_HLQUEUE(2, scmd_prपूर्णांकk(KERN_INFO, SCpnt,
			"Finishing %u sectors\n", blk_rq_sectors(rq)));
		SCSI_LOG_HLQUEUE(2, scmd_prपूर्णांकk(KERN_INFO, SCpnt,
			"Retry with 0x%p\n", SCpnt));
		जाओ out;
	पूर्ण

	अगर (cd->device->changed) अणु
		/*
		 * quietly refuse to करो anything to a changed disc until the
		 * changed bit has been reset
		 */
		जाओ out;
	पूर्ण

	s_size = cd->device->sector_size;
	अगर (s_size != 512 && s_size != 1024 && s_size != 2048) अणु
		scmd_prपूर्णांकk(KERN_ERR, SCpnt, "bad sector size %d\n", s_size);
		जाओ out;
	पूर्ण

	चयन (req_op(rq)) अणु
	हाल REQ_OP_WRITE:
		अगर (!cd->ग_लिखोable)
			जाओ out;
		SCpnt->cmnd[0] = WRITE_10;
		cd->cdi.media_written = 1;
		अवरोध;
	हाल REQ_OP_READ:
		SCpnt->cmnd[0] = READ_10;
		अवरोध;
	शेष:
		blk_dump_rq_flags(rq, "Unknown sr command");
		जाओ out;
	पूर्ण

	अणु
		काष्ठा scatterlist *sg;
		पूर्णांक i, size = 0, sg_count = scsi_sg_count(SCpnt);

		scsi_क्रम_each_sg(SCpnt, sg, sg_count, i)
			size += sg->length;

		अगर (size != scsi_bufflen(SCpnt)) अणु
			scmd_prपूर्णांकk(KERN_ERR, SCpnt,
				"mismatch count %d, bytes %d\n",
				size, scsi_bufflen(SCpnt));
			अगर (scsi_bufflen(SCpnt) > size)
				SCpnt->sdb.length = size;
		पूर्ण
	पूर्ण

	/*
	 * request करोesn't start on hw block boundary, add scatter pads
	 */
	अगर (((अचिन्हित पूर्णांक)blk_rq_pos(rq) % (s_size >> 9)) ||
	    (scsi_bufflen(SCpnt) % s_size)) अणु
		scmd_prपूर्णांकk(KERN_NOTICE, SCpnt, "unaligned transfer\n");
		जाओ out;
	पूर्ण

	this_count = (scsi_bufflen(SCpnt) >> 9) / (s_size >> 9);


	SCSI_LOG_HLQUEUE(2, scmd_prपूर्णांकk(KERN_INFO, SCpnt,
					"%s %d/%u 512 byte blocks.\n",
					(rq_data_dir(rq) == WRITE) ?
					"writing" : "reading",
					this_count, blk_rq_sectors(rq)));

	SCpnt->cmnd[1] = 0;
	block = (अचिन्हित पूर्णांक)blk_rq_pos(rq) / (s_size >> 9);

	अगर (this_count > 0xffff) अणु
		this_count = 0xffff;
		SCpnt->sdb.length = this_count * s_size;
	पूर्ण

	put_unaligned_be32(block, &SCpnt->cmnd[2]);
	SCpnt->cmnd[6] = SCpnt->cmnd[9] = 0;
	put_unaligned_be16(this_count, &SCpnt->cmnd[7]);

	/*
	 * We shouldn't disconnect in the middle of a sector, so with a dumb
	 * host adapter, it's safe to assume that we can at least transfer
	 * this many bytes between each connect / disconnect.
	 */
	SCpnt->transfersize = cd->device->sector_size;
	SCpnt->underflow = this_count << 9;
	SCpnt->allowed = MAX_RETRIES;
	SCpnt->cmd_len = 10;

	/*
	 * This indicates that the command is पढ़ोy from our end to be queued.
	 */
	वापस BLK_STS_OK;
 out:
	scsi_मुक्त_sgtables(SCpnt);
	वापस BLK_STS_IOERR;
पूर्ण

अटल व्योम sr_revalidate_disk(काष्ठा scsi_cd *cd)
अणु
	काष्ठा scsi_sense_hdr sshdr;

	/* अगर the unit is not पढ़ोy, nothing more to करो */
	अगर (scsi_test_unit_पढ़ोy(cd->device, SR_TIMEOUT, MAX_RETRIES, &sshdr))
		वापस;
	sr_cd_check(&cd->cdi);
	get_sectorsize(cd);
पूर्ण

अटल पूर्णांक sr_block_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा scsi_cd *cd;
	काष्ठा scsi_device *sdev;
	पूर्णांक ret = -ENXIO;

	cd = scsi_cd_get(bdev->bd_disk);
	अगर (!cd)
		जाओ out;

	sdev = cd->device;
	scsi_स्वतःpm_get_device(sdev);
	अगर (bdev_check_media_change(bdev))
		sr_revalidate_disk(cd);

	mutex_lock(&cd->lock);
	ret = cdrom_खोलो(&cd->cdi, bdev, mode);
	mutex_unlock(&cd->lock);

	scsi_स्वतःpm_put_device(sdev);
	अगर (ret)
		scsi_cd_put(cd);

out:
	वापस ret;
पूर्ण

अटल व्योम sr_block_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा scsi_cd *cd = scsi_cd(disk);

	mutex_lock(&cd->lock);
	cdrom_release(&cd->cdi, mode);
	mutex_unlock(&cd->lock);

	scsi_cd_put(cd);
पूर्ण

अटल पूर्णांक sr_block_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा scsi_cd *cd = scsi_cd(bdev->bd_disk);
	काष्ठा scsi_device *sdev = cd->device;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक ret;

	mutex_lock(&cd->lock);

	ret = scsi_ioctl_block_when_processing_errors(sdev, cmd,
			(mode & FMODE_NDELAY) != 0);
	अगर (ret)
		जाओ out;

	scsi_स्वतःpm_get_device(sdev);

	/*
	 * Send SCSI addressing ioctls directly to mid level, send other
	 * ioctls to cdrom/block level.
	 */
	चयन (cmd) अणु
	हाल SCSI_IOCTL_GET_IDLUN:
	हाल SCSI_IOCTL_GET_BUS_NUMBER:
		ret = scsi_ioctl(sdev, cmd, argp);
		जाओ put;
	पूर्ण

	ret = cdrom_ioctl(&cd->cdi, bdev, mode, cmd, arg);
	अगर (ret != -ENOSYS)
		जाओ put;

	ret = scsi_ioctl(sdev, cmd, argp);

put:
	scsi_स्वतःpm_put_device(sdev);

out:
	mutex_unlock(&cd->lock);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक sr_block_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा scsi_cd *cd = scsi_cd(bdev->bd_disk);
	काष्ठा scsi_device *sdev = cd->device;
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक ret;

	mutex_lock(&cd->lock);

	ret = scsi_ioctl_block_when_processing_errors(sdev, cmd,
			(mode & FMODE_NDELAY) != 0);
	अगर (ret)
		जाओ out;

	scsi_स्वतःpm_get_device(sdev);

	/*
	 * Send SCSI addressing ioctls directly to mid level, send other
	 * ioctls to cdrom/block level.
	 */
	चयन (cmd) अणु
	हाल SCSI_IOCTL_GET_IDLUN:
	हाल SCSI_IOCTL_GET_BUS_NUMBER:
		ret = scsi_compat_ioctl(sdev, cmd, argp);
		जाओ put;
	पूर्ण

	ret = cdrom_ioctl(&cd->cdi, bdev, mode, cmd, (अचिन्हित दीर्घ)argp);
	अगर (ret != -ENOSYS)
		जाओ put;

	ret = scsi_compat_ioctl(sdev, cmd, argp);

put:
	scsi_स्वतःpm_put_device(sdev);

out:
	mutex_unlock(&cd->lock);
	वापस ret;

पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक sr_block_check_events(काष्ठा gendisk *disk,
					  अचिन्हित पूर्णांक clearing)
अणु
	अचिन्हित पूर्णांक ret = 0;
	काष्ठा scsi_cd *cd;

	cd = scsi_cd_get(disk);
	अगर (!cd)
		वापस 0;

	अगर (!atomic_पढ़ो(&cd->device->disk_events_disable_depth))
		ret = cdrom_check_events(&cd->cdi, clearing);

	scsi_cd_put(cd);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा block_device_operations sr_bकरोps =
अणु
	.owner		= THIS_MODULE,
	.खोलो		= sr_block_खोलो,
	.release	= sr_block_release,
	.ioctl		= sr_block_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= sr_block_compat_ioctl,
#पूर्ण_अगर
	.check_events	= sr_block_check_events,
पूर्ण;

अटल पूर्णांक sr_खोलो(काष्ठा cdrom_device_info *cdi, पूर्णांक purpose)
अणु
	काष्ठा scsi_cd *cd = cdi->handle;
	काष्ठा scsi_device *sdev = cd->device;
	पूर्णांक retval;

	/*
	 * If the device is in error recovery, रुको until it is करोne.
	 * If the device is offline, then disallow any access to it.
	 */
	retval = -ENXIO;
	अगर (!scsi_block_when_processing_errors(sdev))
		जाओ error_out;

	वापस 0;

error_out:
	वापस retval;	
पूर्ण

अटल व्योम sr_release(काष्ठा cdrom_device_info *cdi)
अणु
पूर्ण

अटल पूर्णांक sr_probe(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा gendisk *disk;
	काष्ठा scsi_cd *cd;
	पूर्णांक minor, error;

	scsi_स्वतःpm_get_device(sdev);
	error = -ENODEV;
	अगर (sdev->type != TYPE_ROM && sdev->type != TYPE_WORM)
		जाओ fail;

	error = -ENOMEM;
	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd)
		जाओ fail;

	kref_init(&cd->kref);

	disk = alloc_disk(1);
	अगर (!disk)
		जाओ fail_मुक्त;
	mutex_init(&cd->lock);

	spin_lock(&sr_index_lock);
	minor = find_first_zero_bit(sr_index_bits, SR_DISKS);
	अगर (minor == SR_DISKS) अणु
		spin_unlock(&sr_index_lock);
		error = -EBUSY;
		जाओ fail_put;
	पूर्ण
	__set_bit(minor, sr_index_bits);
	spin_unlock(&sr_index_lock);

	disk->major = SCSI_CDROM_MAJOR;
	disk->first_minor = minor;
	प्र_लिखो(disk->disk_name, "sr%d", minor);
	disk->fops = &sr_bकरोps;
	disk->flags = GENHD_FL_CD | GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE;
	disk->events = DISK_EVENT_MEDIA_CHANGE | DISK_EVENT_EJECT_REQUEST;
	disk->event_flags = DISK_EVENT_FLAG_POLL | DISK_EVENT_FLAG_UEVENT;

	blk_queue_rq_समयout(sdev->request_queue, SR_TIMEOUT);

	cd->device = sdev;
	cd->disk = disk;
	cd->driver = &sr_ढाँचा;
	cd->disk = disk;
	cd->capacity = 0x1fffff;
	cd->device->changed = 1;	/* क्रमce recheck CD type */
	cd->media_present = 1;
	cd->use = 1;
	cd->पढ़ोcd_known = 0;
	cd->पढ़ोcd_cdda = 0;

	cd->cdi.ops = &sr_करोps;
	cd->cdi.handle = cd;
	cd->cdi.mask = 0;
	cd->cdi.capacity = 1;
	प्र_लिखो(cd->cdi.name, "sr%d", minor);

	sdev->sector_size = 2048;	/* A guess, just in हाल */

	/* FIXME: need to handle a get_capabilities failure properly ?? */
	get_capabilities(cd);
	sr_venकरोr_init(cd);

	set_capacity(disk, cd->capacity);
	disk->निजी_data = &cd->driver;
	disk->queue = sdev->request_queue;

	अगर (रेजिस्टर_cdrom(disk, &cd->cdi))
		जाओ fail_minor;

	/*
	 * Initialize block layer runसमय PM stuffs beक्रमe the
	 * periodic event checking request माला_लो started in add_disk.
	 */
	blk_pm_runसमय_init(sdev->request_queue, dev);

	dev_set_drvdata(dev, cd);
	disk->flags |= GENHD_FL_REMOVABLE;
	sr_revalidate_disk(cd);
	device_add_disk(&sdev->sdev_gendev, disk, शून्य);

	sdev_prपूर्णांकk(KERN_DEBUG, sdev,
		    "Attached scsi CD-ROM %s\n", cd->cdi.name);
	scsi_स्वतःpm_put_device(cd->device);

	वापस 0;

fail_minor:
	spin_lock(&sr_index_lock);
	clear_bit(minor, sr_index_bits);
	spin_unlock(&sr_index_lock);
fail_put:
	put_disk(disk);
	mutex_destroy(&cd->lock);
fail_मुक्त:
	kमुक्त(cd);
fail:
	scsi_स्वतःpm_put_device(sdev);
	वापस error;
पूर्ण


अटल व्योम get_sectorsize(काष्ठा scsi_cd *cd)
अणु
	अचिन्हित अक्षर cmd[10];
	अचिन्हित अक्षर buffer[8];
	पूर्णांक the_result, retries = 3;
	पूर्णांक sector_size;
	काष्ठा request_queue *queue;

	करो अणु
		cmd[0] = READ_CAPACITY;
		स_रखो((व्योम *) &cmd[1], 0, 9);
		स_रखो(buffer, 0, माप(buffer));

		/* Do the command and रुको.. */
		the_result = scsi_execute_req(cd->device, cmd, DMA_FROM_DEVICE,
					      buffer, माप(buffer), शून्य,
					      SR_TIMEOUT, MAX_RETRIES, शून्य);

		retries--;

	पूर्ण जबतक (the_result && retries);


	अगर (the_result) अणु
		cd->capacity = 0x1fffff;
		sector_size = 2048;	/* A guess, just in हाल */
	पूर्ण अन्यथा अणु
		दीर्घ last_written;

		cd->capacity = 1 + get_unaligned_be32(&buffer[0]);
		/*
		 * READ_CAPACITY करोesn't वापस the correct size on
		 * certain UDF media.  If last_written is larger, use
		 * it instead.
		 *
		 * http://bugzilla.kernel.org/show_bug.cgi?id=9668
		 */
		अगर (!cdrom_get_last_written(&cd->cdi, &last_written))
			cd->capacity = max_t(दीर्घ, cd->capacity, last_written);

		sector_size = get_unaligned_be32(&buffer[4]);
		चयन (sector_size) अणु
			/*
			 * HP 4020i CD-Recorder reports 2340 byte sectors
			 * Philips CD-Writers report 2352 byte sectors
			 *
			 * Use 2k sectors क्रम them..
			 */
		हाल 0:
		हाल 2340:
		हाल 2352:
			sector_size = 2048;
			fallthrough;
		हाल 2048:
			cd->capacity *= 4;
			fallthrough;
		हाल 512:
			अवरोध;
		शेष:
			sr_prपूर्णांकk(KERN_INFO, cd,
				  "unsupported sector size %d.", sector_size);
			cd->capacity = 0;
		पूर्ण

		cd->device->sector_size = sector_size;

		/*
		 * Add this so that we have the ability to correctly gauge
		 * what the device is capable of.
		 */
		set_capacity(cd->disk, cd->capacity);
	पूर्ण

	queue = cd->device->request_queue;
	blk_queue_logical_block_size(queue, sector_size);

	वापस;
पूर्ण

अटल व्योम get_capabilities(काष्ठा scsi_cd *cd)
अणु
	अचिन्हित अक्षर *buffer;
	काष्ठा scsi_mode_data data;
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित पूर्णांक ms_len = 128;
	पूर्णांक rc, n;

	अटल स्थिर अक्षर *loadmech[] =
	अणु
		"caddy",
		"tray",
		"pop-up",
		"",
		"changer",
		"cartridge changer",
		"",
		""
	पूर्ण;


	/* allocate transfer buffer */
	buffer = kदो_स्मृति(512, GFP_KERNEL | GFP_DMA);
	अगर (!buffer) अणु
		sr_prपूर्णांकk(KERN_ERR, cd, "out of memory.\n");
		वापस;
	पूर्ण

	/* eat unit attentions */
	scsi_test_unit_पढ़ोy(cd->device, SR_TIMEOUT, MAX_RETRIES, &sshdr);

	/* ask क्रम mode page 0x2a */
	rc = scsi_mode_sense(cd->device, 0, 0x2a, buffer, ms_len,
			     SR_TIMEOUT, 3, &data, शून्य);

	अगर (!scsi_status_is_good(rc) || data.length > ms_len ||
	    data.header_length + data.block_descriptor_length > data.length) अणु
		/* failed, drive करोesn't have capabilities mode page */
		cd->cdi.speed = 1;
		cd->cdi.mask |= (CDC_CD_R | CDC_CD_RW | CDC_DVD_R |
				 CDC_DVD | CDC_DVD_RAM |
				 CDC_SELECT_DISC | CDC_SELECT_SPEED |
				 CDC_MRW | CDC_MRW_W | CDC_RAM);
		kमुक्त(buffer);
		sr_prपूर्णांकk(KERN_INFO, cd, "scsi-1 drive");
		वापस;
	पूर्ण

	n = data.header_length + data.block_descriptor_length;
	cd->cdi.speed = get_unaligned_be16(&buffer[n + 8]) / 176;
	cd->पढ़ोcd_known = 1;
	cd->पढ़ोcd_cdda = buffer[n + 5] & 0x01;
	/* prपूर्णांक some capability bits */
	sr_prपूर्णांकk(KERN_INFO, cd,
		  "scsi3-mmc drive: %dx/%dx %s%s%s%s%s%s\n",
		  get_unaligned_be16(&buffer[n + 14]) / 176,
		  cd->cdi.speed,
		  buffer[n + 3] & 0x01 ? "writer " : "", /* CD Writer */
		  buffer[n + 3] & 0x20 ? "dvd-ram " : "",
		  buffer[n + 2] & 0x02 ? "cd/rw " : "", /* can पढ़ो reग_लिखोable */
		  buffer[n + 4] & 0x20 ? "xa/form2 " : "",	/* can पढ़ो xa/from2 */
		  buffer[n + 5] & 0x01 ? "cdda " : "", /* can पढ़ो audio data */
		  loadmech[buffer[n + 6] >> 5]);
	अगर ((buffer[n + 6] >> 5) == 0)
		/* caddy drives can't बंद tray... */
		cd->cdi.mask |= CDC_CLOSE_TRAY;
	अगर ((buffer[n + 2] & 0x8) == 0)
		/* not a DVD drive */
		cd->cdi.mask |= CDC_DVD;
	अगर ((buffer[n + 3] & 0x20) == 0)
		/* can't ग_लिखो DVD-RAM media */
		cd->cdi.mask |= CDC_DVD_RAM;
	अगर ((buffer[n + 3] & 0x10) == 0)
		/* can't ग_लिखो DVD-R media */
		cd->cdi.mask |= CDC_DVD_R;
	अगर ((buffer[n + 3] & 0x2) == 0)
		/* can't ग_लिखो CD-RW media */
		cd->cdi.mask |= CDC_CD_RW;
	अगर ((buffer[n + 3] & 0x1) == 0)
		/* can't ग_लिखो CD-R media */
		cd->cdi.mask |= CDC_CD_R;
	अगर ((buffer[n + 6] & 0x8) == 0)
		/* can't eject */
		cd->cdi.mask |= CDC_OPEN_TRAY;

	अगर ((buffer[n + 6] >> 5) == mechtype_inभागidual_changer ||
	    (buffer[n + 6] >> 5) == mechtype_cartridge_changer)
		cd->cdi.capacity =
		    cdrom_number_of_slots(&cd->cdi);
	अगर (cd->cdi.capacity <= 1)
		/* not a changer */
		cd->cdi.mask |= CDC_SELECT_DISC;
	/*अन्यथा    I करोn't think it can बंद its tray
		cd->cdi.mask |= CDC_CLOSE_TRAY; */

	/*
	 * अगर DVD-RAM, MRW-W or CD-RW, we are अक्रमomly writable
	 */
	अगर ((cd->cdi.mask & (CDC_DVD_RAM | CDC_MRW_W | CDC_RAM | CDC_CD_RW)) !=
			(CDC_DVD_RAM | CDC_MRW_W | CDC_RAM | CDC_CD_RW)) अणु
		cd->ग_लिखोable = 1;
	पूर्ण

	kमुक्त(buffer);
पूर्ण

/*
 * sr_packet() is the entry poपूर्णांक क्रम the generic commands generated
 * by the Unअगरorm CD-ROM layer.
 */
अटल पूर्णांक sr_packet(काष्ठा cdrom_device_info *cdi,
		काष्ठा packet_command *cgc)
अणु
	काष्ठा scsi_cd *cd = cdi->handle;
	काष्ठा scsi_device *sdev = cd->device;

	अगर (cgc->cmd[0] == GPCMD_READ_DISC_INFO && sdev->no_पढ़ो_disc_info)
		वापस -EDRIVE_CANT_DO_THIS;

	अगर (cgc->समयout <= 0)
		cgc->समयout = IOCTL_TIMEOUT;

	sr_करो_ioctl(cd, cgc);

	वापस cgc->stat;
पूर्ण

/**
 *	sr_kref_release - Called to मुक्त the scsi_cd काष्ठाure
 *	@kref: poपूर्णांकer to embedded kref
 *
 *	sr_ref_mutex must be held entering this routine.  Because it is
 *	called on last put, you should always use the scsi_cd_get()
 *	scsi_cd_put() helpers which manipulate the semaphore directly
 *	and never करो a direct kref_put().
 **/
अटल व्योम sr_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा scsi_cd *cd = container_of(kref, काष्ठा scsi_cd, kref);
	काष्ठा gendisk *disk = cd->disk;

	spin_lock(&sr_index_lock);
	clear_bit(MINOR(disk_devt(disk)), sr_index_bits);
	spin_unlock(&sr_index_lock);

	unरेजिस्टर_cdrom(&cd->cdi);

	disk->निजी_data = शून्य;

	put_disk(disk);

	mutex_destroy(&cd->lock);

	kमुक्त(cd);
पूर्ण

अटल पूर्णांक sr_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा scsi_cd *cd = dev_get_drvdata(dev);

	scsi_स्वतःpm_get_device(cd->device);

	del_gendisk(cd->disk);
	dev_set_drvdata(dev, शून्य);

	mutex_lock(&sr_ref_mutex);
	kref_put(&cd->kref, sr_kref_release);
	mutex_unlock(&sr_ref_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __init init_sr(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_blkdev(SCSI_CDROM_MAJOR, "sr");
	अगर (rc)
		वापस rc;
	rc = scsi_रेजिस्टर_driver(&sr_ढाँचा.gendrv);
	अगर (rc)
		unरेजिस्टर_blkdev(SCSI_CDROM_MAJOR, "sr");

	वापस rc;
पूर्ण

अटल व्योम __निकास निकास_sr(व्योम)
अणु
	scsi_unरेजिस्टर_driver(&sr_ढाँचा.gendrv);
	unरेजिस्टर_blkdev(SCSI_CDROM_MAJOR, "sr");
पूर्ण

module_init(init_sr);
module_निकास(निकास_sr);
MODULE_LICENSE("GPL");
