<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cdrom.c IOCTLs handling क्रम ide-cd driver.
 *
 * Copyright (C) 1994-1996  Scott Snyder <snyder@fnald0.fnal.gov>
 * Copyright (C) 1996-1998  Erik Andersen <andersee@debian.org>
 * Copyright (C) 1998-2000  Jens Axboe <axboe@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ide.h>
#समावेश <scsi/scsi.h>

#समावेश "ide-cd.h"

/****************************************************************************
 * Other driver requests (खोलो, बंद, check media change).
 */
पूर्णांक ide_cdrom_खोलो_real(काष्ठा cdrom_device_info *cdi, पूर्णांक purpose)
अणु
	वापस 0;
पूर्ण

/*
 * Close करोwn the device.  Invalidate all cached blocks.
 */
व्योम ide_cdrom_release_real(काष्ठा cdrom_device_info *cdi)
अणु
	ide_drive_t *drive = cdi->handle;

	अगर (!cdi->use_count)
		drive->atapi_flags &= ~IDE_AFLAG_TOC_VALID;
पूर्ण

/*
 * add logic to try GET_EVENT command first to check क्रम media and tray
 * status. this should be supported by newer cd-r/w and all DVD etc
 * drives
 */
पूर्णांक ide_cdrom_drive_status(काष्ठा cdrom_device_info *cdi, पूर्णांक slot_nr)
अणु
	ide_drive_t *drive = cdi->handle;
	काष्ठा media_event_desc med;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक stat;

	अगर (slot_nr != CDSL_CURRENT)
		वापस -EINVAL;

	stat = cdrom_check_status(drive, &sshdr);
	अगर (!stat || sshdr.sense_key == UNIT_ATTENTION)
		वापस CDS_DISC_OK;

	अगर (!cdrom_get_media_event(cdi, &med)) अणु
		अगर (med.media_present)
			वापस CDS_DISC_OK;
		अन्यथा अगर (med.करोor_खोलो)
			वापस CDS_TRAY_OPEN;
		अन्यथा
			वापस CDS_NO_DISC;
	पूर्ण

	अगर (sshdr.sense_key == NOT_READY && sshdr.asc == 0x04
			&& sshdr.ascq == 0x04)
		वापस CDS_DISC_OK;

	/*
	 * If not using Mt Fuji extended media tray reports,
	 * just वापस TRAY_OPEN since ATAPI करोesn't provide
	 * any other way to detect this...
	 */
	अगर (sshdr.sense_key == NOT_READY) अणु
		अगर (sshdr.asc == 0x3a && sshdr.ascq == 1)
			वापस CDS_NO_DISC;
		अन्यथा
			वापस CDS_TRAY_OPEN;
	पूर्ण
	वापस CDS_DRIVE_NOT_READY;
पूर्ण

/*
 * ide-cd always generates media changed event अगर media is missing, which
 * makes it impossible to use क्रम proper event reporting, so
 * DISK_EVENT_FLAG_UEVENT is cleared in disk->event_flags
 * and the following function is used only to trigger
 * revalidation and never propagated to userland.
 */
अचिन्हित पूर्णांक ide_cdrom_check_events_real(काष्ठा cdrom_device_info *cdi,
					 अचिन्हित पूर्णांक clearing, पूर्णांक slot_nr)
अणु
	ide_drive_t *drive = cdi->handle;
	पूर्णांक retval;

	अगर (slot_nr == CDSL_CURRENT) अणु
		(व्योम) cdrom_check_status(drive, शून्य);
		retval = (drive->dev_flags & IDE_DFLAG_MEDIA_CHANGED) ? 1 : 0;
		drive->dev_flags &= ~IDE_DFLAG_MEDIA_CHANGED;
		वापस retval ? DISK_EVENT_MEDIA_CHANGE : 0;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

/* Eject the disk अगर EJECTFLAG is 0.
   If EJECTFLAG is 1, try to reload the disk. */
अटल
पूर्णांक cdrom_eject(ide_drive_t *drive, पूर्णांक ejectflag)
अणु
	काष्ठा cdrom_info *cd = drive->driver_data;
	काष्ठा cdrom_device_info *cdi = &cd->devinfo;
	अक्षर loej = 0x02;
	अचिन्हित अक्षर cmd[BLK_MAX_CDB];

	अगर ((drive->atapi_flags & IDE_AFLAG_NO_EJECT) && !ejectflag)
		वापस -EDRIVE_CANT_DO_THIS;

	/* reload fails on some drives, अगर the tray is locked */
	अगर ((drive->atapi_flags & IDE_AFLAG_DOOR_LOCKED) && ejectflag)
		वापस 0;

	/* only tell drive to बंद tray अगर खोलो, अगर it can करो that */
	अगर (ejectflag && (cdi->mask & CDC_CLOSE_TRAY))
		loej = 0;

	स_रखो(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_START_STOP_UNIT;
	cmd[4] = loej | (ejectflag != 0);

	वापस ide_cd_queue_pc(drive, cmd, 0, शून्य, शून्य, शून्य, 0, 0);
पूर्ण

/* Lock the करोor अगर LOCKFLAG is nonzero; unlock it otherwise. */
अटल
पूर्णांक ide_cd_lockकरोor(ide_drive_t *drive, पूर्णांक lockflag)
अणु
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक stat;

	/* If the drive cannot lock the करोor, just pretend. */
	अगर ((drive->dev_flags & IDE_DFLAG_DOORLOCKING) == 0) अणु
		stat = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर cmd[BLK_MAX_CDB];

		स_रखो(cmd, 0, BLK_MAX_CDB);

		cmd[0] = GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL;
		cmd[4] = lockflag ? 1 : 0;

		stat = ide_cd_queue_pc(drive, cmd, 0, शून्य, शून्य,
				       &sshdr, 0, 0);
	पूर्ण

	/* If we got an illegal field error, the drive
	   probably cannot lock the करोor. */
	अगर (stat != 0 &&
	    sshdr.sense_key == ILLEGAL_REQUEST &&
	    (sshdr.asc == 0x24 || sshdr.asc == 0x20)) अणु
		prपूर्णांकk(KERN_ERR "%s: door locking not supported\n",
			drive->name);
		drive->dev_flags &= ~IDE_DFLAG_DOORLOCKING;
		stat = 0;
	पूर्ण

	/* no medium, that's alright. */
	अगर (stat != 0 && sshdr.sense_key == NOT_READY && sshdr.asc == 0x3a)
		stat = 0;

	अगर (stat == 0) अणु
		अगर (lockflag)
			drive->atapi_flags |= IDE_AFLAG_DOOR_LOCKED;
		अन्यथा
			drive->atapi_flags &= ~IDE_AFLAG_DOOR_LOCKED;
	पूर्ण

	वापस stat;
पूर्ण

पूर्णांक ide_cdrom_tray_move(काष्ठा cdrom_device_info *cdi, पूर्णांक position)
अणु
	ide_drive_t *drive = cdi->handle;

	अगर (position) अणु
		पूर्णांक stat = ide_cd_lockकरोor(drive, 0);

		अगर (stat)
			वापस stat;
	पूर्ण

	वापस cdrom_eject(drive, !position);
पूर्ण

पूर्णांक ide_cdrom_lock_करोor(काष्ठा cdrom_device_info *cdi, पूर्णांक lock)
अणु
	ide_drive_t *drive = cdi->handle;

	वापस ide_cd_lockकरोor(drive, lock);
पूर्ण

/*
 * ATAPI devices are मुक्त to select the speed you request or any slower
 * rate. :-(  Requesting too fast a speed will _not_ produce an error.
 */
पूर्णांक ide_cdrom_select_speed(काष्ठा cdrom_device_info *cdi, पूर्णांक speed)
अणु
	ide_drive_t *drive = cdi->handle;
	काष्ठा cdrom_info *cd = drive->driver_data;
	u8 buf[ATAPI_CAPABILITIES_PAGE_SIZE];
	पूर्णांक stat;
	अचिन्हित अक्षर cmd[BLK_MAX_CDB];

	अगर (speed == 0)
		speed = 0xffff; /* set to max */
	अन्यथा
		speed *= 177;   /* Nx to kbytes/s */

	स_रखो(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_SET_SPEED;
	/* Read Drive speed in kbytes/second MSB/LSB */
	cmd[2] = (speed >> 8) & 0xff;
	cmd[3] = speed & 0xff;
	अगर ((cdi->mask & (CDC_CD_R | CDC_CD_RW | CDC_DVD_R)) !=
	    (CDC_CD_R | CDC_CD_RW | CDC_DVD_R)) अणु
		/* Write Drive speed in kbytes/second MSB/LSB */
		cmd[4] = (speed >> 8) & 0xff;
		cmd[5] = speed & 0xff;
	पूर्ण

	stat = ide_cd_queue_pc(drive, cmd, 0, शून्य, शून्य, शून्य, 0, 0);

	अगर (!ide_cdrom_get_capabilities(drive, buf)) अणु
		ide_cdrom_update_speed(drive, buf);
		cdi->speed = cd->current_speed;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ide_cdrom_get_last_session(काष्ठा cdrom_device_info *cdi,
			       काष्ठा cdrom_multisession *ms_info)
अणु
	काष्ठा atapi_toc *toc;
	ide_drive_t *drive = cdi->handle;
	काष्ठा cdrom_info *info = drive->driver_data;
	पूर्णांक ret;

	अगर ((drive->atapi_flags & IDE_AFLAG_TOC_VALID) == 0 || !info->toc) अणु
		ret = ide_cd_पढ़ो_toc(drive);
		अगर (ret)
			वापस ret;
	पूर्ण

	toc = info->toc;
	ms_info->addr.lba = toc->last_session_lba;
	ms_info->xa_flag = toc->xa_flag;

	वापस 0;
पूर्ण

पूर्णांक ide_cdrom_get_mcn(काष्ठा cdrom_device_info *cdi,
		      काष्ठा cdrom_mcn *mcn_info)
अणु
	ide_drive_t *drive = cdi->handle;
	पूर्णांक stat, mcnlen;
	अक्षर buf[24];
	अचिन्हित अक्षर cmd[BLK_MAX_CDB];
	अचिन्हित len = माप(buf);

	स_रखो(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_READ_SUBCHANNEL;
	cmd[1] = 2;		/* MSF addressing */
	cmd[2] = 0x40;	/* request subQ data */
	cmd[3] = 2;		/* क्रमmat */
	cmd[8] = len;

	stat = ide_cd_queue_pc(drive, cmd, 0, buf, &len, शून्य, 0, 0);
	अगर (stat)
		वापस stat;

	mcnlen = माप(mcn_info->medium_catalog_number) - 1;
	स_नकल(mcn_info->medium_catalog_number, buf + 9, mcnlen);
	mcn_info->medium_catalog_number[mcnlen] = '\0';

	वापस 0;
पूर्ण

पूर्णांक ide_cdrom_reset(काष्ठा cdrom_device_info *cdi)
अणु
	ide_drive_t *drive = cdi->handle;
	काष्ठा cdrom_info *cd = drive->driver_data;
	काष्ठा request *rq;
	पूर्णांक ret;

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	rq->rq_flags = RQF_QUIET;
	blk_execute_rq(cd->disk, rq, 0);
	ret = scsi_req(rq)->result ? -EIO : 0;
	blk_put_request(rq);
	/*
	 * A reset will unlock the करोor. If it was previously locked,
	 * lock it again.
	 */
	अगर (drive->atapi_flags & IDE_AFLAG_DOOR_LOCKED)
		(व्योम)ide_cd_lockकरोor(drive, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक ide_cd_get_toc_entry(ide_drive_t *drive, पूर्णांक track,
				काष्ठा atapi_toc_entry **ent)
अणु
	काष्ठा cdrom_info *info = drive->driver_data;
	काष्ठा atapi_toc *toc = info->toc;
	पूर्णांक ntracks;

	/*
	 * करोn't serve cached data, if the toc isn't valid
	 */
	अगर ((drive->atapi_flags & IDE_AFLAG_TOC_VALID) == 0)
		वापस -EINVAL;

	/* Check validity of requested track number. */
	ntracks = toc->hdr.last_track - toc->hdr.first_track + 1;

	अगर (toc->hdr.first_track == CDROM_LEADOUT)
		ntracks = 0;

	अगर (track == CDROM_LEADOUT)
		*ent = &toc->ent[ntracks];
	अन्यथा अगर (track < toc->hdr.first_track || track > toc->hdr.last_track)
		वापस -EINVAL;
	अन्यथा
		*ent = &toc->ent[track - toc->hdr.first_track];

	वापस 0;
पूर्ण

अटल पूर्णांक ide_cd_fake_play_trkind(ide_drive_t *drive, व्योम *arg)
अणु
	काष्ठा cdrom_ti *ti = arg;
	काष्ठा atapi_toc_entry *first_toc, *last_toc;
	अचिन्हित दीर्घ lba_start, lba_end;
	पूर्णांक stat;
	अचिन्हित अक्षर cmd[BLK_MAX_CDB];

	stat = ide_cd_get_toc_entry(drive, ti->cdti_trk0, &first_toc);
	अगर (stat)
		वापस stat;

	stat = ide_cd_get_toc_entry(drive, ti->cdti_trk1, &last_toc);
	अगर (stat)
		वापस stat;

	अगर (ti->cdti_trk1 != CDROM_LEADOUT)
		++last_toc;
	lba_start = first_toc->addr.lba;
	lba_end   = last_toc->addr.lba;

	अगर (lba_end <= lba_start)
		वापस -EINVAL;

	स_रखो(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_PLAY_AUDIO_MSF;
	lba_to_msf(lba_start,   &cmd[3], &cmd[4], &cmd[5]);
	lba_to_msf(lba_end - 1, &cmd[6], &cmd[7], &cmd[8]);

	वापस ide_cd_queue_pc(drive, cmd, 0, शून्य, शून्य, शून्य, 0, 0);
पूर्ण

अटल पूर्णांक ide_cd_पढ़ो_tochdr(ide_drive_t *drive, व्योम *arg)
अणु
	काष्ठा cdrom_info *cd = drive->driver_data;
	काष्ठा cdrom_tochdr *tochdr = arg;
	काष्ठा atapi_toc *toc;
	पूर्णांक stat;

	/* Make sure our saved TOC is valid. */
	stat = ide_cd_पढ़ो_toc(drive);
	अगर (stat)
		वापस stat;

	toc = cd->toc;
	tochdr->cdth_trk0 = toc->hdr.first_track;
	tochdr->cdth_trk1 = toc->hdr.last_track;

	वापस 0;
पूर्ण

अटल पूर्णांक ide_cd_पढ़ो_tocentry(ide_drive_t *drive, व्योम *arg)
अणु
	काष्ठा cdrom_tocentry *tocentry = arg;
	काष्ठा atapi_toc_entry *toce;
	पूर्णांक stat;

	stat = ide_cd_get_toc_entry(drive, tocentry->cdte_track, &toce);
	अगर (stat)
		वापस stat;

	tocentry->cdte_ctrl = toce->control;
	tocentry->cdte_adr  = toce->adr;
	अगर (tocentry->cdte_क्रमmat == CDROM_MSF) अणु
		lba_to_msf(toce->addr.lba,
			   &tocentry->cdte_addr.msf.minute,
			   &tocentry->cdte_addr.msf.second,
			   &tocentry->cdte_addr.msf.frame);
	पूर्ण अन्यथा
		tocentry->cdte_addr.lba = toce->addr.lba;

	वापस 0;
पूर्ण

पूर्णांक ide_cdrom_audio_ioctl(काष्ठा cdrom_device_info *cdi,
			  अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	ide_drive_t *drive = cdi->handle;

	चयन (cmd) अणु
	/*
	 * emulate PLAY_AUDIO_TI command with PLAY_AUDIO_10, since
	 * atapi करोesn't support it
	 */
	हाल CDROMPLAYTRKIND:
		वापस ide_cd_fake_play_trkind(drive, arg);
	हाल CDROMREADTOCHDR:
		वापस ide_cd_पढ़ो_tochdr(drive, arg);
	हाल CDROMREADTOCENTRY:
		वापस ide_cd_पढ़ो_tocentry(drive, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* the generic packet पूर्णांकerface to cdrom.c */
पूर्णांक ide_cdrom_packet(काष्ठा cdrom_device_info *cdi,
			    काष्ठा packet_command *cgc)
अणु
	ide_drive_t *drive = cdi->handle;
	req_flags_t flags = 0;
	अचिन्हित len = cgc->buflen;

	अगर (cgc->समयout <= 0)
		cgc->समयout = ATAPI_WAIT_PC;

	/* here we queue the commands from the unअगरorm CD-ROM
	   layer. the packet must be complete, as we करो not
	   touch it at all. */

	अगर (cgc->sshdr)
		स_रखो(cgc->sshdr, 0, माप(*cgc->sshdr));

	अगर (cgc->quiet)
		flags |= RQF_QUIET;

	cgc->stat = ide_cd_queue_pc(drive, cgc->cmd,
				    cgc->data_direction == CGC_DATA_WRITE,
				    cgc->buffer, &len,
				    cgc->sshdr, cgc->समयout, flags);
	अगर (!cgc->stat)
		cgc->buflen -= len;
	वापस cgc->stat;
पूर्ण
