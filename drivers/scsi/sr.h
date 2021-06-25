<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *      sr.h by David Giller
 *      CD-ROM disk driver header file
 *      
 *      adapted from:
 *      sd.h Copyright (C) 1992 Drew Eckhardt 
 *      SCSI disk driver header file by
 *              Drew Eckhardt 
 *
 *      <drew@coloraकरो.edu>
 *
 *       Modअगरied by Eric Youngdale eric@andante.org to
 *       add scatter-gather, multiple outstanding request, and other
 *       enhancements.
 */

#अगर_अघोषित _SR_H
#घोषणा _SR_H

#समावेश <linux/genhd.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>

#घोषणा MAX_RETRIES	3
#घोषणा SR_TIMEOUT	(30 * HZ)

काष्ठा scsi_device;

/* The CDROM is fairly slow, so we need a little extra समय */
/* In fact, it is very slow अगर it has to spin up first */
#घोषणा IOCTL_TIMEOUT 30*HZ


प्रकार काष्ठा scsi_cd अणु
	काष्ठा scsi_driver *driver;
	अचिन्हित capacity;	/* size in blocks                       */
	काष्ठा scsi_device *device;
	अचिन्हित पूर्णांक venकरोr;	/* venकरोr code, see sr_venकरोr.c         */
	अचिन्हित दीर्घ ms_offset;	/* क्रम पढ़ोing multisession-CD's        */
	अचिन्हित ग_लिखोable : 1;
	अचिन्हित use:1;		/* is this device still supportable     */
	अचिन्हित xa_flag:1;	/* CD has XA sectors ? */
	अचिन्हित पढ़ोcd_known:1;	/* drive supports READ_CD (0xbe) */
	अचिन्हित पढ़ोcd_cdda:1;	/* पढ़ोing audio data using READ_CD */
	अचिन्हित media_present:1;	/* media is present */

	/* GET_EVENT spurious event handling, blk layer guarantees exclusion */
	पूर्णांक tur_mismatch;		/* nr of get_event TUR mismatches */
	bool tur_changed:1;		/* changed according to TUR */
	bool get_event_changed:1;	/* changed according to GET_EVENT */
	bool ignore_get_event:1;	/* GET_EVENT is unreliable, use TUR */

	काष्ठा cdrom_device_info cdi;
	काष्ठा mutex lock;
	/* We hold gendisk and scsi_device references on probe and use
	 * the refs on this kref to decide when to release them */
	काष्ठा kref kref;
	काष्ठा gendisk *disk;
पूर्ण Scsi_CD;

#घोषणा sr_prपूर्णांकk(prefix, cd, fmt, a...) \
	sdev_prefix_prपूर्णांकk(prefix, (cd)->device, (cd)->cdi.name, fmt, ##a)

पूर्णांक sr_करो_ioctl(Scsi_CD *, काष्ठा packet_command *);

पूर्णांक sr_lock_करोor(काष्ठा cdrom_device_info *, पूर्णांक);
पूर्णांक sr_tray_move(काष्ठा cdrom_device_info *, पूर्णांक);
पूर्णांक sr_drive_status(काष्ठा cdrom_device_info *, पूर्णांक);
पूर्णांक sr_disk_status(काष्ठा cdrom_device_info *);
पूर्णांक sr_get_last_session(काष्ठा cdrom_device_info *, काष्ठा cdrom_multisession *);
पूर्णांक sr_get_mcn(काष्ठा cdrom_device_info *, काष्ठा cdrom_mcn *);
पूर्णांक sr_reset(काष्ठा cdrom_device_info *);
पूर्णांक sr_select_speed(काष्ठा cdrom_device_info *cdi, पूर्णांक speed);
पूर्णांक sr_audio_ioctl(काष्ठा cdrom_device_info *, अचिन्हित पूर्णांक, व्योम *);

पूर्णांक sr_is_xa(Scsi_CD *);

/* sr_venकरोr.c */
व्योम sr_venकरोr_init(Scsi_CD *);
पूर्णांक sr_cd_check(काष्ठा cdrom_device_info *);
पूर्णांक sr_set_blocklength(Scsi_CD *, पूर्णांक blocklength);

#पूर्ण_अगर
