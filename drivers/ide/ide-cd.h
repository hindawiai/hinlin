<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 1996-98  Erik Andersen
 *  Copyright (C) 1998-2000 Jens Axboe
 */
#अगर_अघोषित _IDE_CD_H
#घोषणा _IDE_CD_H

#समावेश <linux/cdrom.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा IDECD_DEBUG_LOG		0

#अगर IDECD_DEBUG_LOG
#घोषणा ide_debug_log(lvl, fmt, args...) __ide_debug_log(lvl, fmt, ## args)
#अन्यथा
#घोषणा ide_debug_log(lvl, fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा ATAPI_WAIT_WRITE_BUSY	(10 * HZ)

/************************************************************************/

#घोषणा SECTORS_PER_FRAME	(CD_FRAMESIZE >> SECTOR_SHIFT)
#घोषणा SECTOR_BUFFER_SIZE	(CD_FRAMESIZE * 32)

/* Capabilities Page size including 8 bytes of Mode Page Header */
#घोषणा ATAPI_CAPABILITIES_PAGE_SIZE		(8 + 20)
#घोषणा ATAPI_CAPABILITIES_PAGE_PAD_SIZE	4

/* Structure of a MSF cdrom address. */
काष्ठा atapi_msf अणु
	u8 reserved;
	u8 minute;
	u8 second;
	u8 frame;
पूर्ण;

/* Space to hold the disk TOC. */
#घोषणा MAX_TRACKS 99
काष्ठा atapi_toc_header अणु
	अचिन्हित लघु toc_length;
	u8 first_track;
	u8 last_track;
पूर्ण;

काष्ठा atapi_toc_entry अणु
	u8 reserved1;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 adr     : 4;
	u8 control : 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 control : 4;
	u8 adr     : 4;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	u8 track;
	u8 reserved2;
	जोड़ अणु
		अचिन्हित lba;
		काष्ठा atapi_msf msf;
	पूर्ण addr;
पूर्ण;

काष्ठा atapi_toc अणु
	पूर्णांक    last_session_lba;
	पूर्णांक    xa_flag;
	अचिन्हित दीर्घ capacity;
	काष्ठा atapi_toc_header hdr;
	काष्ठा atapi_toc_entry  ent[MAX_TRACKS+1];
	  /* One extra क्रम the leaकरोut. */
पूर्ण;

/* Extra per-device info क्रम cdrom drives. */
काष्ठा cdrom_info अणु
	ide_drive_t		*drive;
	काष्ठा ide_driver	*driver;
	काष्ठा gendisk		*disk;
	काष्ठा device		dev;

	/* Buffer क्रम table of contents.  शून्य अगर we haven't allocated
	   a TOC buffer क्रम this device yet. */

	काष्ठा atapi_toc *toc;

	u8 max_speed;		/* Max speed of the drive. */
	u8 current_speed;	/* Current speed of the drive. */

        /* Per-device info needed by cdrom.c generic driver. */
        काष्ठा cdrom_device_info devinfo;

	अचिन्हित दीर्घ ग_लिखो_समयout;
पूर्ण;

/* ide-cd_verbose.c */
व्योम ide_cd_log_error(स्थिर अक्षर *, काष्ठा request *, काष्ठा request_sense *);

/* ide-cd.c functions used by ide-cd_ioctl.c */
पूर्णांक ide_cd_queue_pc(ide_drive_t *, स्थिर अचिन्हित अक्षर *, पूर्णांक, व्योम *,
		    अचिन्हित *, काष्ठा scsi_sense_hdr *, पूर्णांक, req_flags_t);
पूर्णांक ide_cd_पढ़ो_toc(ide_drive_t *);
पूर्णांक ide_cdrom_get_capabilities(ide_drive_t *, u8 *);
व्योम ide_cdrom_update_speed(ide_drive_t *, u8 *);
पूर्णांक cdrom_check_status(ide_drive_t *, काष्ठा scsi_sense_hdr *);

/* ide-cd_ioctl.c */
पूर्णांक ide_cdrom_खोलो_real(काष्ठा cdrom_device_info *, पूर्णांक);
व्योम ide_cdrom_release_real(काष्ठा cdrom_device_info *);
पूर्णांक ide_cdrom_drive_status(काष्ठा cdrom_device_info *, पूर्णांक);
अचिन्हित पूर्णांक ide_cdrom_check_events_real(काष्ठा cdrom_device_info *,
					 अचिन्हित पूर्णांक clearing, पूर्णांक slot_nr);
पूर्णांक ide_cdrom_tray_move(काष्ठा cdrom_device_info *, पूर्णांक);
पूर्णांक ide_cdrom_lock_करोor(काष्ठा cdrom_device_info *, पूर्णांक);
पूर्णांक ide_cdrom_select_speed(काष्ठा cdrom_device_info *, पूर्णांक);
पूर्णांक ide_cdrom_get_last_session(काष्ठा cdrom_device_info *,
			       काष्ठा cdrom_multisession *);
पूर्णांक ide_cdrom_get_mcn(काष्ठा cdrom_device_info *, काष्ठा cdrom_mcn *);
पूर्णांक ide_cdrom_reset(काष्ठा cdrom_device_info *cdi);
पूर्णांक ide_cdrom_audio_ioctl(काष्ठा cdrom_device_info *, अचिन्हित पूर्णांक, व्योम *);
पूर्णांक ide_cdrom_packet(काष्ठा cdrom_device_info *, काष्ठा packet_command *);

#पूर्ण_अगर /* _IDE_CD_H */
