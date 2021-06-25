<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * -- <linux/cdrom.h>
 * General header file क्रम linux CD-ROM drivers 
 * Copyright (C) 1992         David Giller, rafeपंचांगad@oxy.edu
 *               1994, 1995   Eberhard Mथघnkeberg, emoenke@gwdg.de
 *               1996         David van Leeuwen, david@पंचांग.tno.nl
 *               1997, 1998   Erik Andersen, andersee@debian.org
 *               1998-2002    Jens Axboe, axboe@suse.de
 */
#अगर_अघोषित	_LINUX_CDROM_H
#घोषणा	_LINUX_CDROM_H

#समावेश <linux/fs.h>		/* not really needed, later.. */
#समावेश <linux/list.h>
#समावेश <scsi/scsi_common.h>
#समावेश <uapi/linux/cdrom.h>

काष्ठा packet_command
अणु
	अचिन्हित अक्षर 		cmd[CDROM_PACKET_SIZE];
	अचिन्हित अक्षर 		*buffer;
	अचिन्हित पूर्णांक 		buflen;
	पूर्णांक			stat;
	काष्ठा scsi_sense_hdr	*sshdr;
	अचिन्हित अक्षर		data_direction;
	पूर्णांक			quiet;
	पूर्णांक			समयout;
	व्योम			*reserved[1];
पूर्ण;

/*
 * _OLD will use PIO transfer on atapi devices, _BPC_* will use DMA
 */
#घोषणा CDDA_OLD		0	/* old style */
#घोषणा CDDA_BPC_SINGLE		1	/* single frame block pc */
#घोषणा CDDA_BPC_FULL		2	/* multi frame block pc */

/* Unअगरorm cdrom data काष्ठाures क्रम cdrom.c */
काष्ठा cdrom_device_info अणु
	स्थिर काष्ठा cdrom_device_ops *ops; /* link to device_ops */
	काष्ठा list_head list;		/* linked list of all device_info */
	काष्ठा gendisk *disk;		/* matching block layer disk */
	व्योम *handle;		        /* driver-dependent data */
/* specअगरications */
	पूर्णांक mask;                       /* mask of capability: disables them */
	पूर्णांक speed;			/* maximum speed क्रम पढ़ोing data */
	पूर्णांक capacity;			/* number of discs in jukebox */
/* device-related storage */
	अचिन्हित पूर्णांक options	: 30;	/* options flags */
	अचिन्हित mc_flags	: 2;	/* media change buffer flags */
	अचिन्हित पूर्णांक vfs_events;	/* cached events क्रम vfs path */
	अचिन्हित पूर्णांक ioctl_events;	/* cached events क्रम ioctl path */
    	पूर्णांक use_count;                  /* number of बार device खोलोed */
    	अक्षर name[20];                  /* name of the device type */
/* per-device flags */
        __u8 sanyo_slot		: 2;	/* Sanyo 3 CD changer support */
        __u8 keeplocked		: 1;	/* CDROM_LOCKDOOR status */
        __u8 reserved		: 5;	/* not used yet */
	पूर्णांक cdda_method;		/* see flags */
	__u8 last_sense;
	__u8 media_written;		/* dirty flag, DVD+RW bookkeeping */
	अचिन्हित लघु mmc3_profile;	/* current MMC3 profile */
	पूर्णांक क्रम_data;
	पूर्णांक (*निकास)(काष्ठा cdrom_device_info *);
	पूर्णांक mrw_mode_page;
पूर्ण;

काष्ठा cdrom_device_ops अणु
/* routines */
	पूर्णांक (*खोलो) (काष्ठा cdrom_device_info *, पूर्णांक);
	व्योम (*release) (काष्ठा cdrom_device_info *);
	पूर्णांक (*drive_status) (काष्ठा cdrom_device_info *, पूर्णांक);
	अचिन्हित पूर्णांक (*check_events) (काष्ठा cdrom_device_info *cdi,
				      अचिन्हित पूर्णांक clearing, पूर्णांक slot);
	पूर्णांक (*tray_move) (काष्ठा cdrom_device_info *, पूर्णांक);
	पूर्णांक (*lock_करोor) (काष्ठा cdrom_device_info *, पूर्णांक);
	पूर्णांक (*select_speed) (काष्ठा cdrom_device_info *, पूर्णांक);
	पूर्णांक (*select_disc) (काष्ठा cdrom_device_info *, पूर्णांक);
	पूर्णांक (*get_last_session) (काष्ठा cdrom_device_info *,
				 काष्ठा cdrom_multisession *);
	पूर्णांक (*get_mcn) (काष्ठा cdrom_device_info *,
			काष्ठा cdrom_mcn *);
	/* hard reset device */
	पूर्णांक (*reset) (काष्ठा cdrom_device_info *);
	/* play stuff */
	पूर्णांक (*audio_ioctl) (काष्ठा cdrom_device_info *,अचिन्हित पूर्णांक, व्योम *);

/* driver specअगरications */
	स्थिर पूर्णांक capability;   /* capability flags */
	/* handle unअगरorm packets क्रम scsi type devices (scsi,atapi) */
	पूर्णांक (*generic_packet) (काष्ठा cdrom_device_info *,
			       काष्ठा packet_command *);
पूर्ण;

पूर्णांक cdrom_multisession(काष्ठा cdrom_device_info *cdi,
		काष्ठा cdrom_multisession *info);
पूर्णांक cdrom_पढ़ो_tocentry(काष्ठा cdrom_device_info *cdi,
		काष्ठा cdrom_tocentry *entry);

/* the general block_device operations काष्ठाure: */
बाह्य पूर्णांक cdrom_खोलो(काष्ठा cdrom_device_info *cdi, काष्ठा block_device *bdev,
			भ_शेषe_t mode);
बाह्य व्योम cdrom_release(काष्ठा cdrom_device_info *cdi, भ_शेषe_t mode);
बाह्य पूर्णांक cdrom_ioctl(काष्ठा cdrom_device_info *cdi, काष्ठा block_device *bdev,
		       भ_शेषe_t mode, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
बाह्य अचिन्हित पूर्णांक cdrom_check_events(काष्ठा cdrom_device_info *cdi,
				       अचिन्हित पूर्णांक clearing);

बाह्य पूर्णांक रेजिस्टर_cdrom(काष्ठा gendisk *disk, काष्ठा cdrom_device_info *cdi);
बाह्य व्योम unरेजिस्टर_cdrom(काष्ठा cdrom_device_info *cdi);

प्रकार काष्ठा अणु
    पूर्णांक data;
    पूर्णांक audio;
    पूर्णांक cdi;
    पूर्णांक xa;
    दीर्घ error;
पूर्ण tracktype;

बाह्य पूर्णांक cdrom_get_last_written(काष्ठा cdrom_device_info *cdi, दीर्घ *last_written);
बाह्य पूर्णांक cdrom_number_of_slots(काष्ठा cdrom_device_info *cdi);
बाह्य पूर्णांक cdrom_mode_select(काष्ठा cdrom_device_info *cdi,
			     काष्ठा packet_command *cgc);
बाह्य पूर्णांक cdrom_mode_sense(काष्ठा cdrom_device_info *cdi,
			    काष्ठा packet_command *cgc,
			    पूर्णांक page_code, पूर्णांक page_control);
बाह्य व्योम init_cdrom_command(काष्ठा packet_command *cgc,
			       व्योम *buffer, पूर्णांक len, पूर्णांक type);
बाह्य पूर्णांक cdrom_dummy_generic_packet(काष्ठा cdrom_device_info *cdi,
				      काष्ठा packet_command *cgc);

/* The SCSI spec says there could be 256 slots. */
#घोषणा CDROM_MAX_SLOTS	256

काष्ठा cdrom_mechstat_header अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 fault         : 1;
	__u8 changer_state : 2;
	__u8 curslot       : 5;
	__u8 mech_state    : 3;
	__u8 करोor_खोलो     : 1;
	__u8 reserved1     : 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 curslot       : 5;
	__u8 changer_state : 2;
	__u8 fault         : 1;
	__u8 reserved1     : 4;
	__u8 करोor_खोलो     : 1;
	__u8 mech_state    : 3;
#पूर्ण_अगर
	__u8     curlba[3];
	__u8     nslots;
	__u16 slot_tablelen;
पूर्ण;

काष्ठा cdrom_slot अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 disc_present : 1;
	__u8 reserved1    : 6;
	__u8 change       : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 change       : 1;
	__u8 reserved1    : 6;
	__u8 disc_present : 1;
#पूर्ण_अगर
	__u8 reserved2[3];
पूर्ण;

काष्ठा cdrom_changer_info अणु
	काष्ठा cdrom_mechstat_header hdr;
	काष्ठा cdrom_slot slots[CDROM_MAX_SLOTS];
पूर्ण;

प्रकार क्रमागत अणु
	mechtype_caddy = 0,
	mechtype_tray  = 1,
	mechtype_popup = 2,
	mechtype_inभागidual_changer = 4,
	mechtype_cartridge_changer  = 5
पूर्ण mechtype_t;

प्रकार काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 ps			: 1;
	__u8 reserved1		: 1;
	__u8 page_code		: 6;
        __u8 page_length;
	__u8 reserved2		: 1;
	__u8 bufe		: 1;
	__u8 ls_v		: 1;
	__u8 test_ग_लिखो		: 1;
        __u8 ग_लिखो_type		: 4;
	__u8 multi_session	: 2; /* or border, DVD */
	__u8 fp			: 1;
	__u8 copy		: 1;
	__u8 track_mode		: 4;
	__u8 reserved3		: 4;
	__u8 data_block_type	: 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 page_code		: 6;
	__u8 reserved1		: 1;
	__u8 ps			: 1;
        __u8 page_length;
        __u8 ग_लिखो_type		: 4;
	__u8 test_ग_लिखो		: 1;
	__u8 ls_v		: 1;
	__u8 bufe		: 1;
	__u8 reserved2		: 1;
	__u8 track_mode		: 4;
	__u8 copy		: 1;
	__u8 fp			: 1;
	__u8 multi_session	: 2; /* or border, DVD */
	__u8 data_block_type	: 4;
	__u8 reserved3		: 4;
#पूर्ण_अगर
	__u8 link_size;
	__u8 reserved4;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved5		: 2;
	__u8 app_code		: 6;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 app_code		: 6;
	__u8 reserved5		: 2;
#पूर्ण_अगर
	__u8 session_क्रमmat;
	__u8 reserved6;
	__be32 packet_size;
	__u16 audio_छोड़ो;
	__u8 mcn[16];
	__u8 isrc[16];
	__u8 subhdr0;
	__u8 subhdr1;
	__u8 subhdr2;
	__u8 subhdr3;
पूर्ण __attribute__((packed)) ग_लिखो_param_page;

काष्ठा modesel_head
अणु
	__u8	reserved1;
	__u8	medium;
	__u8	reserved2;
	__u8	block_desc_length;
	__u8	density;
	__u8	number_of_blocks_hi;
	__u8	number_of_blocks_med;
	__u8	number_of_blocks_lo;
	__u8	reserved3;
	__u8	block_length_hi;
	__u8	block_length_med;
	__u8	block_length_lo;
पूर्ण;

प्रकार काष्ठा अणु
	__u16 report_key_length;
	__u8 reserved1;
	__u8 reserved2;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 type_code			: 2;
	__u8 vra			: 3;
	__u8 ucca			: 3;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 ucca			: 3;
	__u8 vra			: 3;
	__u8 type_code			: 2;
#पूर्ण_अगर
	__u8 region_mask;
	__u8 rpc_scheme;
	__u8 reserved3;
पूर्ण rpc_state_t;

काष्ठा event_header अणु
	__be16 data_len;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 nea		: 1;
	__u8 reserved1		: 4;
	__u8 notअगरication_class	: 3;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 notअगरication_class	: 3;
	__u8 reserved1		: 4;
	__u8 nea		: 1;
#पूर्ण_अगर
	__u8 supp_event_class;
पूर्ण;

काष्ठा media_event_desc अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 reserved1		: 4;
	__u8 media_event_code	: 4;
	__u8 reserved2		: 6;
	__u8 media_present	: 1;
	__u8 करोor_खोलो		: 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 media_event_code	: 4;
	__u8 reserved1		: 4;
	__u8 करोor_खोलो		: 1;
	__u8 media_present	: 1;
	__u8 reserved2		: 6;
#पूर्ण_अगर
	__u8 start_slot;
	__u8 end_slot;
पूर्ण;

बाह्य पूर्णांक cdrom_get_media_event(काष्ठा cdrom_device_info *cdi, काष्ठा media_event_desc *med);

अटल अंतरभूत व्योम lba_to_msf(पूर्णांक lba, u8 *m, u8 *s, u8 *f)
अणु
	lba += CD_MSF_OFFSET;
	lba &= 0xffffff;  /* negative lbas use only 24 bits */
	*m = lba / (CD_SECS * CD_FRAMES);
	lba %= (CD_SECS * CD_FRAMES);
	*s = lba / CD_FRAMES;
	*f = lba % CD_FRAMES;
पूर्ण

अटल अंतरभूत पूर्णांक msf_to_lba(u8 m, u8 s, u8 f)
अणु
	वापस (((m * CD_SECS) + s) * CD_FRAMES + f) - CD_MSF_OFFSET;
पूर्ण
#पूर्ण_अगर  /* _LINUX_CDROM_H */
