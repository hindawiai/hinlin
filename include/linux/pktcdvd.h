<शैली गुरु>
/*
 * Copyright (C) 2000 Jens Axboe <axboe@suse.de>
 * Copyright (C) 2001-2004 Peter Osterlund <petero2@telia.com>
 *
 * May be copied or modअगरied under the terms of the GNU General Public
 * License.  See linux/COPYING क्रम more inक्रमmation.
 *
 * Packet writing layer क्रम ATAPI and SCSI CD-R, CD-RW, DVD-R, and
 * DVD-RW devices.
 *
 */
#अगर_अघोषित __PKTCDVD_H
#घोषणा __PKTCDVD_H

#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/mempool.h>
#समावेश <uapi/linux/pktcdvd.h>

/* शेष bio ग_लिखो queue congestion marks */
#घोषणा PKT_WRITE_CONGESTION_ON    10000
#घोषणा PKT_WRITE_CONGESTION_OFF   9000


काष्ठा packet_settings
अणु
	__u32			size;		/* packet size in (512 byte) sectors */
	__u8			fp;		/* fixed packets */
	__u8			link_loss;	/* the rest is specअगरied
						 * as per Mt Fuji */
	__u8			ग_लिखो_type;
	__u8			track_mode;
	__u8			block_mode;
पूर्ण;

/*
 * Very crude stats क्रम now
 */
काष्ठा packet_stats
अणु
	अचिन्हित दीर्घ		pkt_started;
	अचिन्हित दीर्घ		pkt_ended;
	अचिन्हित दीर्घ		secs_w;
	अचिन्हित दीर्घ		secs_rg;
	अचिन्हित दीर्घ		secs_r;
पूर्ण;

काष्ठा packet_cdrw
अणु
	काष्ठा list_head	pkt_मुक्त_list;
	काष्ठा list_head	pkt_active_list;
	spinlock_t		active_list_lock; /* Serialize access to pkt_active_list */
	काष्ठा task_काष्ठा	*thपढ़ो;
	atomic_t		pending_bios;
पूर्ण;

/*
 * Switch to high speed पढ़ोing after पढ़ोing this many kilobytes
 * with no पूर्णांकerspersed ग_लिखोs.
 */
#घोषणा HI_SPEED_SWITCH 512

काष्ठा packet_iosched
अणु
	atomic_t		attention;	/* Set to non-zero when queue processing is needed */
	पूर्णांक			writing;	/* Non-zero when writing, zero when पढ़ोing */
	spinlock_t		lock;		/* Protecting पढ़ो/ग_लिखो queue manipulations */
	काष्ठा bio_list		पढ़ो_queue;
	काष्ठा bio_list		ग_लिखो_queue;
	sector_t		last_ग_लिखो;	/* The sector where the last ग_लिखो ended */
	पूर्णांक			successive_पढ़ोs;
पूर्ण;

/*
 * 32 buffers of 2048 bytes
 */
#अगर (PAGE_SIZE % CD_FRAMESIZE) != 0
#त्रुटि "PAGE_SIZE must be a multiple of CD_FRAMESIZE"
#पूर्ण_अगर
#घोषणा PACKET_MAX_SIZE		128
#घोषणा FRAMES_PER_PAGE		(PAGE_SIZE / CD_FRAMESIZE)
#घोषणा PACKET_MAX_SECTORS	(PACKET_MAX_SIZE * CD_FRAMESIZE >> 9)

क्रमागत packet_data_state अणु
	PACKET_IDLE_STATE,			/* Not used at the moment */
	PACKET_WAITING_STATE,			/* Waiting क्रम more bios to arrive, so */
						/* we करोn't have to करो as much */
						/* data gathering */
	PACKET_READ_WAIT_STATE,			/* Waiting क्रम पढ़ोs to fill in holes */
	PACKET_WRITE_WAIT_STATE,		/* Waiting क्रम the ग_लिखो to complete */
	PACKET_RECOVERY_STATE,			/* Recover after पढ़ो/ग_लिखो errors */
	PACKET_FINISHED_STATE,			/* After ग_लिखो has finished */

	PACKET_NUM_STATES			/* Number of possible states */
पूर्ण;

/*
 * Inक्रमmation needed क्रम writing a single packet
 */
काष्ठा pktcdvd_device;

काष्ठा packet_data
अणु
	काष्ठा list_head	list;

	spinlock_t		lock;		/* Lock protecting state transitions and */
						/* orig_bios list */

	काष्ठा bio_list		orig_bios;	/* Original bios passed to pkt_make_request */
						/* that will be handled by this packet */
	पूर्णांक			ग_लिखो_size;	/* Total size of all bios in the orig_bios */
						/* list, measured in number of frames */

	काष्ठा bio		*w_bio;		/* The bio we will send to the real CD */
						/* device once we have all data क्रम the */
						/* packet we are going to ग_लिखो */
	sector_t		sector;		/* First sector in this packet */
	पूर्णांक			frames;		/* Number of frames in this packet */

	क्रमागत packet_data_state	state;		/* Current state */
	atomic_t		run_sm;		/* Incremented whenever the state */
						/* machine needs to be run */
	दीर्घ			sleep_समय;	/* Set this to non-zero to make the state */
						/* machine run after this many jअगरfies. */

	atomic_t		io_रुको;	/* Number of pending IO operations */
	atomic_t		io_errors;	/* Number of पढ़ो/ग_लिखो errors during IO */

	काष्ठा bio		*r_bios[PACKET_MAX_SIZE]; /* bios to use during data gathering */
	काष्ठा page		*pages[PACKET_MAX_SIZE / FRAMES_PER_PAGE];

	पूर्णांक			cache_valid;	/* If non-zero, the data क्रम the zone defined */
						/* by the sector variable is completely cached */
						/* in the pages[] vector. */

	पूर्णांक			id;		/* ID number क्रम debugging */
	काष्ठा pktcdvd_device	*pd;
पूर्ण;

काष्ठा pkt_rb_node अणु
	काष्ठा rb_node		rb_node;
	काष्ठा bio		*bio;
पूर्ण;

काष्ठा packet_stacked_data
अणु
	काष्ठा bio		*bio;		/* Original पढ़ो request bio */
	काष्ठा pktcdvd_device	*pd;
पूर्ण;
#घोषणा PSD_POOL_SIZE		64

काष्ठा pktcdvd_kobj
अणु
	काष्ठा kobject		kobj;
	काष्ठा pktcdvd_device	*pd;
पूर्ण;
#घोषणा to_pktcdvdkobj(_k) \
  ((काष्ठा pktcdvd_kobj*)container_of(_k,काष्ठा pktcdvd_kobj,kobj))

काष्ठा pktcdvd_device
अणु
	काष्ठा block_device	*bdev;		/* dev attached */
	dev_t			pkt_dev;	/* our dev */
	अक्षर			name[20];
	काष्ठा packet_settings	settings;
	काष्ठा packet_stats	stats;
	पूर्णांक			refcnt;		/* Open count */
	पूर्णांक			ग_लिखो_speed;	/* current ग_लिखो speed, kB/s */
	पूर्णांक			पढ़ो_speed;	/* current पढ़ो speed, kB/s */
	अचिन्हित दीर्घ		offset;		/* start offset */
	__u8			mode_offset;	/* 0 / 8 */
	__u8			type;
	अचिन्हित दीर्घ		flags;
	__u16			mmc3_profile;
	__u32			nwa;		/* next writable address */
	__u32			lra;		/* last recorded address */
	काष्ठा packet_cdrw	cdrw;
	रुको_queue_head_t	wqueue;

	spinlock_t		lock;		/* Serialize access to bio_queue */
	काष्ठा rb_root		bio_queue;	/* Work queue of bios we need to handle */
	पूर्णांक			bio_queue_size;	/* Number of nodes in bio_queue */
	sector_t		current_sector;	/* Keep track of where the elevator is */
	atomic_t		scan_queue;	/* Set to non-zero when pkt_handle_queue */
						/* needs to be run. */
	mempool_t		rb_pool;	/* mempool क्रम pkt_rb_node allocations */

	काष्ठा packet_iosched   iosched;
	काष्ठा gendisk		*disk;

	पूर्णांक			ग_लिखो_congestion_off;
	पूर्णांक			ग_लिखो_congestion_on;

	काष्ठा device		*dev;		/* sysfs pktcdvd[0-7] dev */
	काष्ठा pktcdvd_kobj	*kobj_stat;	/* sysfs pktcdvd[0-7]/stat/     */
	काष्ठा pktcdvd_kobj	*kobj_wqueue;	/* sysfs pktcdvd[0-7]/ग_लिखो_queue/ */

	काष्ठा dentry		*dfs_d_root;	/* debugfs: devname directory */
	काष्ठा dentry		*dfs_f_info;	/* debugfs: info file */
पूर्ण;

#पूर्ण_अगर /* __PKTCDVD_H */
