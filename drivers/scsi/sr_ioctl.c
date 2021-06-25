<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "sr.h"

#अगर 0
#घोषणा DEBUG
#पूर्ण_अगर

/* The sr_is_xa() seems to trigger firmware bugs with some drives :-(
 * It is off by शेष and can be turned on with this module parameter */
अटल पूर्णांक xa_test = 0;

module_param(xa_test, पूर्णांक, S_IRUGO | S_IWUSR);

अटल पूर्णांक sr_पढ़ो_tochdr(काष्ठा cdrom_device_info *cdi,
		काष्ठा cdrom_tochdr *tochdr)
अणु
	काष्ठा scsi_cd *cd = cdi->handle;
	काष्ठा packet_command cgc;
	पूर्णांक result;
	अचिन्हित अक्षर *buffer;

	buffer = kदो_स्मृति(32, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.समयout = IOCTL_TIMEOUT;
	cgc.cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cgc.cmd[8] = 12;		/* LSB of length */
	cgc.buffer = buffer;
	cgc.buflen = 12;
	cgc.quiet = 1;
	cgc.data_direction = DMA_FROM_DEVICE;

	result = sr_करो_ioctl(cd, &cgc);

	tochdr->cdth_trk0 = buffer[2];
	tochdr->cdth_trk1 = buffer[3];

	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल पूर्णांक sr_पढ़ो_tocentry(काष्ठा cdrom_device_info *cdi,
		काष्ठा cdrom_tocentry *tocentry)
अणु
	काष्ठा scsi_cd *cd = cdi->handle;
	काष्ठा packet_command cgc;
	पूर्णांक result;
	अचिन्हित अक्षर *buffer;

	buffer = kदो_स्मृति(32, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.समयout = IOCTL_TIMEOUT;
	cgc.cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cgc.cmd[1] |= (tocentry->cdte_क्रमmat == CDROM_MSF) ? 0x02 : 0;
	cgc.cmd[6] = tocentry->cdte_track;
	cgc.cmd[8] = 12;		/* LSB of length */
	cgc.buffer = buffer;
	cgc.buflen = 12;
	cgc.data_direction = DMA_FROM_DEVICE;

	result = sr_करो_ioctl(cd, &cgc);

	tocentry->cdte_ctrl = buffer[5] & 0xf;
	tocentry->cdte_adr = buffer[5] >> 4;
	tocentry->cdte_datamode = (tocentry->cdte_ctrl & 0x04) ? 1 : 0;
	अगर (tocentry->cdte_क्रमmat == CDROM_MSF) अणु
		tocentry->cdte_addr.msf.minute = buffer[9];
		tocentry->cdte_addr.msf.second = buffer[10];
		tocentry->cdte_addr.msf.frame = buffer[11];
	पूर्ण अन्यथा
		tocentry->cdte_addr.lba = (((((buffer[8] << 8) + buffer[9]) << 8)
			+ buffer[10]) << 8) + buffer[11];

	kमुक्त(buffer);
	वापस result;
पूर्ण

#घोषणा IOCTL_RETRIES 3

/* ATAPI drives करोn't have a SCMD_PLAYAUDIO_TI command.  When these drives
   are emulating a SCSI device via the idescsi module, they need to have
   CDROMPLAYTRKIND commands translated पूर्णांकo CDROMPLAYMSF commands क्रम them */

अटल पूर्णांक sr_fake_playtrkind(काष्ठा cdrom_device_info *cdi, काष्ठा cdrom_ti *ti)
अणु
	काष्ठा cdrom_tocentry trk0_te, trk1_te;
	काष्ठा cdrom_tochdr tochdr;
	काष्ठा packet_command cgc;
	पूर्णांक ntracks, ret;

	ret = sr_पढ़ो_tochdr(cdi, &tochdr);
	अगर (ret)
		वापस ret;

	ntracks = tochdr.cdth_trk1 - tochdr.cdth_trk0 + 1;
	
	अगर (ti->cdti_trk1 == ntracks) 
		ti->cdti_trk1 = CDROM_LEADOUT;
	अन्यथा अगर (ti->cdti_trk1 != CDROM_LEADOUT)
		ti->cdti_trk1 ++;

	trk0_te.cdte_track = ti->cdti_trk0;
	trk0_te.cdte_क्रमmat = CDROM_MSF;
	trk1_te.cdte_track = ti->cdti_trk1;
	trk1_te.cdte_क्रमmat = CDROM_MSF;
	
	ret = sr_पढ़ो_tocentry(cdi, &trk0_te);
	अगर (ret)
		वापस ret;
	ret = sr_पढ़ो_tocentry(cdi, &trk1_te);
	अगर (ret)
		वापस ret;

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.cmd[0] = GPCMD_PLAY_AUDIO_MSF;
	cgc.cmd[3] = trk0_te.cdte_addr.msf.minute;
	cgc.cmd[4] = trk0_te.cdte_addr.msf.second;
	cgc.cmd[5] = trk0_te.cdte_addr.msf.frame;
	cgc.cmd[6] = trk1_te.cdte_addr.msf.minute;
	cgc.cmd[7] = trk1_te.cdte_addr.msf.second;
	cgc.cmd[8] = trk1_te.cdte_addr.msf.frame;
	cgc.data_direction = DMA_NONE;
	cgc.समयout = IOCTL_TIMEOUT;
	वापस sr_करो_ioctl(cdi->handle, &cgc);
पूर्ण

अटल पूर्णांक sr_play_trkind(काष्ठा cdrom_device_info *cdi,
		काष्ठा cdrom_ti *ti)

अणु
	काष्ठा scsi_cd *cd = cdi->handle;
	काष्ठा packet_command cgc;
	पूर्णांक result;

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.समयout = IOCTL_TIMEOUT;
	cgc.cmd[0] = GPCMD_PLAYAUDIO_TI;
	cgc.cmd[4] = ti->cdti_trk0;
	cgc.cmd[5] = ti->cdti_ind0;
	cgc.cmd[7] = ti->cdti_trk1;
	cgc.cmd[8] = ti->cdti_ind1;
	cgc.data_direction = DMA_NONE;

	result = sr_करो_ioctl(cd, &cgc);
	अगर (result == -EDRIVE_CANT_DO_THIS)
		result = sr_fake_playtrkind(cdi, ti);

	वापस result;
पूर्ण

/* We करो our own retries because we want to know what the specअगरic
   error code is.  Normally the UNIT_ATTENTION code will स्वतःmatically
   clear after one error */

पूर्णांक sr_करो_ioctl(Scsi_CD *cd, काष्ठा packet_command *cgc)
अणु
	काष्ठा scsi_device *SDev;
	काष्ठा scsi_sense_hdr local_sshdr, *sshdr = &local_sshdr;
	पूर्णांक result, err = 0, retries = 0;

	SDev = cd->device;

	अगर (cgc->sshdr)
		sshdr = cgc->sshdr;

      retry:
	अगर (!scsi_block_when_processing_errors(SDev)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	result = scsi_execute(SDev, cgc->cmd, cgc->data_direction,
			      cgc->buffer, cgc->buflen, शून्य, sshdr,
			      cgc->समयout, IOCTL_RETRIES, 0, 0, शून्य);

	/* Minimal error checking.  Ignore हालs we know about, and report the rest. */
	अगर (driver_byte(result) != 0) अणु
		चयन (sshdr->sense_key) अणु
		हाल UNIT_ATTENTION:
			SDev->changed = 1;
			अगर (!cgc->quiet)
				sr_prपूर्णांकk(KERN_INFO, cd,
					  "disc change detected.\n");
			अगर (retries++ < 10)
				जाओ retry;
			err = -ENOMEDIUM;
			अवरोध;
		हाल NOT_READY:	/* This happens अगर there is no disc in drive */
			अगर (sshdr->asc == 0x04 &&
			    sshdr->ascq == 0x01) अणु
				/* sense: Logical unit is in process of becoming पढ़ोy */
				अगर (!cgc->quiet)
					sr_prपूर्णांकk(KERN_INFO, cd,
						  "CDROM not ready yet.\n");
				अगर (retries++ < 10) अणु
					/* sleep 2 sec and try again */
					ssleep(2);
					जाओ retry;
				पूर्ण अन्यथा अणु
					/* 20 secs are enough? */
					err = -ENOMEDIUM;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!cgc->quiet)
				sr_prपूर्णांकk(KERN_INFO, cd,
					  "CDROM not ready.  Make sure there "
					  "is a disc in the drive.\n");
			err = -ENOMEDIUM;
			अवरोध;
		हाल ILLEGAL_REQUEST:
			err = -EIO;
			अगर (sshdr->asc == 0x20 &&
			    sshdr->ascq == 0x00)
				/* sense: Invalid command operation code */
				err = -EDRIVE_CANT_DO_THIS;
			अवरोध;
		शेष:
			err = -EIO;
		पूर्ण
	पूर्ण

	/* Wake up a process रुकोing क्रम device */
      out:
	cgc->stat = err;
	वापस err;
पूर्ण

/* ---------------------------------------------------------------------- */
/* पूर्णांकerface to cdrom.c                                                   */

पूर्णांक sr_tray_move(काष्ठा cdrom_device_info *cdi, पूर्णांक pos)
अणु
	Scsi_CD *cd = cdi->handle;
	काष्ठा packet_command cgc;

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.cmd[0] = GPCMD_START_STOP_UNIT;
	cgc.cmd[4] = (pos == 0) ? 0x03 /* बंद */ : 0x02 /* eject */ ;
	cgc.data_direction = DMA_NONE;
	cgc.समयout = IOCTL_TIMEOUT;
	वापस sr_करो_ioctl(cd, &cgc);
पूर्ण

पूर्णांक sr_lock_करोor(काष्ठा cdrom_device_info *cdi, पूर्णांक lock)
अणु
	Scsi_CD *cd = cdi->handle;

	वापस scsi_set_medium_removal(cd->device, lock ?
		       SCSI_REMOVAL_PREVENT : SCSI_REMOVAL_ALLOW);
पूर्ण

पूर्णांक sr_drive_status(काष्ठा cdrom_device_info *cdi, पूर्णांक slot)
अणु
	काष्ठा scsi_cd *cd = cdi->handle;
	काष्ठा scsi_sense_hdr sshdr;
	काष्ठा media_event_desc med;

	अगर (CDSL_CURRENT != slot) अणु
		/* we have no changer support */
		वापस -EINVAL;
	पूर्ण
	अगर (!scsi_test_unit_पढ़ोy(cd->device, SR_TIMEOUT, MAX_RETRIES, &sshdr))
		वापस CDS_DISC_OK;

	/* SK/ASC/ASCQ of 2/4/1 means "unit is becoming ready" */
	अगर (scsi_sense_valid(&sshdr) && sshdr.sense_key == NOT_READY
			&& sshdr.asc == 0x04 && sshdr.ascq == 0x01)
		वापस CDS_DRIVE_NOT_READY;

	अगर (!cdrom_get_media_event(cdi, &med)) अणु
		अगर (med.media_present)
			वापस CDS_DISC_OK;
		अन्यथा अगर (med.करोor_खोलो)
			वापस CDS_TRAY_OPEN;
		अन्यथा
			वापस CDS_NO_DISC;
	पूर्ण

	/*
	 * SK/ASC/ASCQ of 2/4/2 means "initialization required"
	 * Using CD_TRAY_OPEN results in an START_STOP_UNIT to बंद
	 * the tray, which resolves the initialization requirement.
	 */
	अगर (scsi_sense_valid(&sshdr) && sshdr.sense_key == NOT_READY
			&& sshdr.asc == 0x04 && sshdr.ascq == 0x02)
		वापस CDS_TRAY_OPEN;

	/*
	 * 0x04 is क्रमmat in progress .. but there must be a disc present!
	 */
	अगर (sshdr.sense_key == NOT_READY && sshdr.asc == 0x04)
		वापस CDS_DISC_OK;

	/*
	 * If not using Mt Fuji extended media tray reports,
	 * just वापस TRAY_OPEN since ATAPI करोesn't provide
	 * any other way to detect this...
	 */
	अगर (scsi_sense_valid(&sshdr) &&
	    /* 0x3a is medium not present */
	    sshdr.asc == 0x3a)
		वापस CDS_NO_DISC;
	अन्यथा
		वापस CDS_TRAY_OPEN;

	वापस CDS_DRIVE_NOT_READY;
पूर्ण

पूर्णांक sr_disk_status(काष्ठा cdrom_device_info *cdi)
अणु
	Scsi_CD *cd = cdi->handle;
	काष्ठा cdrom_tochdr toc_h;
	काष्ठा cdrom_tocentry toc_e;
	पूर्णांक i, rc, have_datatracks = 0;

	/* look क्रम data tracks */
	rc = sr_पढ़ो_tochdr(cdi, &toc_h);
	अगर (rc)
		वापस (rc == -ENOMEDIUM) ? CDS_NO_DISC : CDS_NO_INFO;

	क्रम (i = toc_h.cdth_trk0; i <= toc_h.cdth_trk1; i++) अणु
		toc_e.cdte_track = i;
		toc_e.cdte_क्रमmat = CDROM_LBA;
		अगर (sr_पढ़ो_tocentry(cdi, &toc_e))
			वापस CDS_NO_INFO;
		अगर (toc_e.cdte_ctrl & CDROM_DATA_TRACK) अणु
			have_datatracks = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!have_datatracks)
		वापस CDS_AUDIO;

	अगर (cd->xa_flag)
		वापस CDS_XA_2_1;
	अन्यथा
		वापस CDS_DATA_1;
पूर्ण

पूर्णांक sr_get_last_session(काष्ठा cdrom_device_info *cdi,
			काष्ठा cdrom_multisession *ms_info)
अणु
	Scsi_CD *cd = cdi->handle;

	ms_info->addr.lba = cd->ms_offset;
	ms_info->xa_flag = cd->xa_flag || cd->ms_offset > 0;

	वापस 0;
पूर्ण

पूर्णांक sr_get_mcn(काष्ठा cdrom_device_info *cdi, काष्ठा cdrom_mcn *mcn)
अणु
	Scsi_CD *cd = cdi->handle;
	काष्ठा packet_command cgc;
	अक्षर *buffer = kदो_स्मृति(32, GFP_KERNEL);
	पूर्णांक result;

	अगर (!buffer)
		वापस -ENOMEM;

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.cmd[0] = GPCMD_READ_SUBCHANNEL;
	cgc.cmd[2] = 0x40;	/* I करो want the subchannel info */
	cgc.cmd[3] = 0x02;	/* Give me medium catalog number info */
	cgc.cmd[8] = 24;
	cgc.buffer = buffer;
	cgc.buflen = 24;
	cgc.data_direction = DMA_FROM_DEVICE;
	cgc.समयout = IOCTL_TIMEOUT;
	result = sr_करो_ioctl(cd, &cgc);

	स_नकल(mcn->medium_catalog_number, buffer + 9, 13);
	mcn->medium_catalog_number[13] = 0;

	kमुक्त(buffer);
	वापस result;
पूर्ण

पूर्णांक sr_reset(काष्ठा cdrom_device_info *cdi)
अणु
	वापस 0;
पूर्ण

पूर्णांक sr_select_speed(काष्ठा cdrom_device_info *cdi, पूर्णांक speed)
अणु
	Scsi_CD *cd = cdi->handle;
	काष्ठा packet_command cgc;

	अगर (speed == 0)
		speed = 0xffff;	/* set to max */
	अन्यथा
		speed *= 177;	/* Nx to kbyte/s */

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.cmd[0] = GPCMD_SET_SPEED;	/* SET CD SPEED */
	cgc.cmd[2] = (speed >> 8) & 0xff;	/* MSB क्रम speed (in kbytes/sec) */
	cgc.cmd[3] = speed & 0xff;	/* LSB */
	cgc.data_direction = DMA_NONE;
	cgc.समयout = IOCTL_TIMEOUT;

	अगर (sr_करो_ioctl(cd, &cgc))
		वापस -EIO;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */
/* this is called by the generic cdrom driver. arg is a _kernel_ poपूर्णांकer,  */
/* because the generic cdrom driver करोes the user access stuff क्रम us.     */
/* only cdromपढ़ोtochdr and cdromपढ़ोtocentry are left - क्रम use with the  */
/* sr_disk_status पूर्णांकerface क्रम the generic cdrom driver.                  */

पूर्णांक sr_audio_ioctl(काष्ठा cdrom_device_info *cdi, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल CDROMREADTOCHDR:
		वापस sr_पढ़ो_tochdr(cdi, arg);
	हाल CDROMREADTOCENTRY:
		वापस sr_पढ़ो_tocentry(cdi, arg);
	हाल CDROMPLAYTRKIND:
		वापस sr_play_trkind(cdi, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------
 * a function to पढ़ो all sorts of funny cdrom sectors using the READ_CD
 * scsi-3 mmc command
 *
 * lba:     linear block address
 * क्रमmat:  0 = data (anything)
 *          1 = audio
 *          2 = data (mode 1)
 *          3 = data (mode 2)
 *          4 = data (mode 2 क्रमm1)
 *          5 = data (mode 2 क्रमm2)
 * blksize: 2048 | 2336 | 2340 | 2352
 */

अटल पूर्णांक sr_पढ़ो_cd(Scsi_CD *cd, अचिन्हित अक्षर *dest, पूर्णांक lba, पूर्णांक क्रमmat, पूर्णांक blksize)
अणु
	काष्ठा packet_command cgc;

#अगर_घोषित DEBUG
	sr_prपूर्णांकk(KERN_INFO, cd, "sr_read_cd lba=%d format=%d blksize=%d\n",
		  lba, क्रमmat, blksize);
#पूर्ण_अगर

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.cmd[0] = GPCMD_READ_CD;	/* READ_CD */
	cgc.cmd[1] = ((क्रमmat & 7) << 2);
	cgc.cmd[2] = (अचिन्हित अक्षर) (lba >> 24) & 0xff;
	cgc.cmd[3] = (अचिन्हित अक्षर) (lba >> 16) & 0xff;
	cgc.cmd[4] = (अचिन्हित अक्षर) (lba >> 8) & 0xff;
	cgc.cmd[5] = (अचिन्हित अक्षर) lba & 0xff;
	cgc.cmd[8] = 1;
	चयन (blksize) अणु
	हाल 2336:
		cgc.cmd[9] = 0x58;
		अवरोध;
	हाल 2340:
		cgc.cmd[9] = 0x78;
		अवरोध;
	हाल 2352:
		cgc.cmd[9] = 0xf8;
		अवरोध;
	शेष:
		cgc.cmd[9] = 0x10;
		अवरोध;
	पूर्ण
	cgc.buffer = dest;
	cgc.buflen = blksize;
	cgc.data_direction = DMA_FROM_DEVICE;
	cgc.समयout = IOCTL_TIMEOUT;
	वापस sr_करो_ioctl(cd, &cgc);
पूर्ण

/*
 * पढ़ो sectors with blocksizes other than 2048
 */

अटल पूर्णांक sr_पढ़ो_sector(Scsi_CD *cd, पूर्णांक lba, पूर्णांक blksize, अचिन्हित अक्षर *dest)
अणु
	काष्ठा packet_command cgc;
	पूर्णांक rc;

	/* we try the READ CD command first... */
	अगर (cd->पढ़ोcd_known) अणु
		rc = sr_पढ़ो_cd(cd, dest, lba, 0, blksize);
		अगर (-EDRIVE_CANT_DO_THIS != rc)
			वापस rc;
		cd->पढ़ोcd_known = 0;
		sr_prपूर्णांकk(KERN_INFO, cd,
			  "CDROM does'nt support READ CD (0xbe) command\n");
		/* fall & retry the other way */
	पूर्ण
	/* ... अगर this fails, we चयन the blocksize using MODE SELECT */
	अगर (blksize != cd->device->sector_size) अणु
		अगर (0 != (rc = sr_set_blocklength(cd, blksize)))
			वापस rc;
	पूर्ण
#अगर_घोषित DEBUG
	sr_prपूर्णांकk(KERN_INFO, cd, "sr_read_sector lba=%d blksize=%d\n",
		  lba, blksize);
#पूर्ण_अगर

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.cmd[0] = GPCMD_READ_10;
	cgc.cmd[2] = (अचिन्हित अक्षर) (lba >> 24) & 0xff;
	cgc.cmd[3] = (अचिन्हित अक्षर) (lba >> 16) & 0xff;
	cgc.cmd[4] = (अचिन्हित अक्षर) (lba >> 8) & 0xff;
	cgc.cmd[5] = (अचिन्हित अक्षर) lba & 0xff;
	cgc.cmd[8] = 1;
	cgc.buffer = dest;
	cgc.buflen = blksize;
	cgc.data_direction = DMA_FROM_DEVICE;
	cgc.समयout = IOCTL_TIMEOUT;
	rc = sr_करो_ioctl(cd, &cgc);

	अगर (blksize != CD_FRAMESIZE)
		rc |= sr_set_blocklength(cd, CD_FRAMESIZE);
	वापस rc;
पूर्ण

/*
 * पढ़ो a sector in raw mode to check the sector क्रमmat
 * ret: 1 == mode2 (XA), 0 == mode1, <0 == error 
 */

पूर्णांक sr_is_xa(Scsi_CD *cd)
अणु
	अचिन्हित अक्षर *raw_sector;
	पूर्णांक is_xa;

	अगर (!xa_test)
		वापस 0;

	raw_sector = kदो_स्मृति(2048, GFP_KERNEL);
	अगर (!raw_sector)
		वापस -ENOMEM;
	अगर (0 == sr_पढ़ो_sector(cd, cd->ms_offset + 16,
				CD_FRAMESIZE_RAW1, raw_sector)) अणु
		is_xa = (raw_sector[3] == 0x02) ? 1 : 0;
	पूर्ण अन्यथा अणु
		/* पढ़ो a raw sector failed क्रम some reason. */
		is_xa = -1;
	पूर्ण
	kमुक्त(raw_sector);
#अगर_घोषित DEBUG
	sr_prपूर्णांकk(KERN_INFO, cd, "sr_is_xa: %d\n", is_xa);
#पूर्ण_अगर
	वापस is_xa;
पूर्ण
