<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ST_H
#घोषणा _ST_H

#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kref.h>
#समावेश <scsi/scsi_cmnd.h>

/* Descriptor क्रम analyzed sense data */
काष्ठा st_cmdstatus अणु
	पूर्णांक midlevel_result;
	काष्ठा scsi_sense_hdr sense_hdr;
	पूर्णांक have_sense;
	पूर्णांक residual;
	u64 ureमुख्यder64;
	u8 flags;
	u8 reमुख्यder_valid;
	u8 fixed_क्रमmat;
	u8 deferred;
पूर्ण;

काष्ठा scsi_tape;

/* scsi tape command */
काष्ठा st_request अणु
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	अचिन्हित अक्षर sense[SCSI_SENSE_BUFFERSIZE];
	पूर्णांक result;
	काष्ठा scsi_tape *stp;
	काष्ठा completion *रुकोing;
	काष्ठा bio *bio;
पूर्ण;

/* The tape buffer descriptor. */
काष्ठा st_buffer अणु
	अचिन्हित अक्षर cleared;  /* पूर्णांकernal buffer cleared after खोलो? */
	अचिन्हित लघु करो_dio;  /* direct i/o set up? */
	पूर्णांक buffer_size;
	पूर्णांक buffer_blocks;
	पूर्णांक buffer_bytes;
	पूर्णांक पढ़ो_poपूर्णांकer;
	पूर्णांक writing;
	पूर्णांक syscall_result;
	काष्ठा st_request *last_SRpnt;
	काष्ठा st_cmdstatus cmdstat;
	काष्ठा page **reserved_pages;
	पूर्णांक reserved_page_order;
	काष्ठा page **mapped_pages;
	काष्ठा rq_map_data map_data;
	अचिन्हित अक्षर *b_data;
	अचिन्हित लघु use_sg;	/* zero or max number of s/g segments क्रम this adapter */
	अचिन्हित लघु sg_segs;		/* number of segments in s/g list */
	अचिन्हित लघु frp_segs;	/* number of buffer segments */
पूर्ण;

/* The tape mode definition */
काष्ठा st_modedef अणु
	अचिन्हित अक्षर defined;
	अचिन्हित अक्षर sysv;	/* SYS V semantics? */
	अचिन्हित अक्षर करो_async_ग_लिखोs;
	अचिन्हित अक्षर करो_buffer_ग_लिखोs;
	अचिन्हित अक्षर करो_पढ़ो_ahead;
	अचिन्हित अक्षर शेषs_क्रम_ग_लिखोs;
	अचिन्हित अक्षर शेष_compression;	/* 0 = करोn't touch, etc */
	लघु शेष_density;	/* Forced density, -1 = no value */
	पूर्णांक शेष_blksize;	/* Forced blocksize, -1 = no value */
	काष्ठा scsi_tape *tape;
	काष्ठा device *devs[2];  /* Auto-शुरुआत and non-शुरुआत devices */
	काष्ठा cdev *cdevs[2];  /* Auto-शुरुआत and non-शुरुआत devices */
पूर्ण;

/* Number of modes can be changed by changing ST_NBR_MODE_BITS. The maximum
   number of modes is 16 (ST_NBR_MODE_BITS 4) */
#घोषणा ST_NBR_MODE_BITS 2
#घोषणा ST_NBR_MODES (1 << ST_NBR_MODE_BITS)
#घोषणा ST_MODE_SHIFT (7 - ST_NBR_MODE_BITS)
#घोषणा ST_MODE_MASK ((ST_NBR_MODES - 1) << ST_MODE_SHIFT)

#घोषणा ST_MAX_TAPES (1 << (20 - (ST_NBR_MODE_BITS + 1)))
#घोषणा ST_MAX_TAPE_ENTRIES  (ST_MAX_TAPES << (ST_NBR_MODE_BITS + 1))

/* The status related to each partition */
काष्ठा st_partstat अणु
	अचिन्हित अक्षर rw;
	अचिन्हित अक्षर eof;
	अचिन्हित अक्षर at_sm;
	अचिन्हित अक्षर last_block_valid;
	u32 last_block_visited;
	पूर्णांक drv_block;		/* The block where the drive head is */
	पूर्णांक drv_file;
पूर्ण;

/* Tape statistics */
काष्ठा scsi_tape_stats अणु
	atomic64_t पढ़ो_byte_cnt;  /* bytes पढ़ो */
	atomic64_t ग_लिखो_byte_cnt; /* bytes written */
	atomic64_t in_flight;      /* Number of I/Os in flight */
	atomic64_t पढ़ो_cnt;       /* Count of पढ़ो requests */
	atomic64_t ग_लिखो_cnt;      /* Count of ग_लिखो requests */
	atomic64_t other_cnt;      /* Count of other requests either
				    * implicit or from user space
				    * ioctl. */
	atomic64_t resid_cnt;      /* Count of resid_len > 0 */
	atomic64_t tot_पढ़ो_समय;  /* kसमय spent completing पढ़ोs */
	atomic64_t tot_ग_लिखो_समय; /* kसमय spent completing ग_लिखोs */
	atomic64_t tot_io_समय;    /* kसमय spent करोing any I/O */
	kसमय_प्रकार पढ़ो_समय;         /* holds kसमय request was queued */
	kसमय_प्रकार ग_लिखो_समय;        /* holds kसमय request was queued */
	kसमय_प्रकार other_समय;        /* holds kसमय request was queued */
	atomic_t last_पढ़ो_size;   /* Number of bytes issued क्रम last पढ़ो */
	atomic_t last_ग_लिखो_size;  /* Number of bytes issued क्रम last ग_लिखो */
पूर्ण;

#घोषणा ST_NBR_PARTITIONS 4

/* The tape drive descriptor */
काष्ठा scsi_tape अणु
	काष्ठा scsi_driver *driver;
	काष्ठा scsi_device *device;
	काष्ठा mutex lock;	/* For serialization */
	काष्ठा completion रुको;	/* For SCSI commands */
	काष्ठा st_buffer *buffer;
	पूर्णांक index;

	/* Drive अक्षरacteristics */
	अचिन्हित अक्षर omit_blklims;
	अचिन्हित अक्षर करो_स्वतः_lock;
	अचिन्हित अक्षर can_bsr;
	अचिन्हित अक्षर can_partitions;
	अचिन्हित अक्षर two_fm;
	अचिन्हित अक्षर fast_mteom;
	अचिन्हित अक्षर immediate;
	अचिन्हित अक्षर scsi2_logical;
	अचिन्हित अक्षर शेष_drvbuffer;	/* 0xff = करोn't touch, value 3 bits */
	अचिन्हित अक्षर cln_mode;			/* 0 = none, otherwise sense byte nbr */
	अचिन्हित अक्षर cln_sense_value;
	अचिन्हित अक्षर cln_sense_mask;
	अचिन्हित अक्षर use_pf;			/* Set Page Format bit in all mode selects? */
	अचिन्हित अक्षर try_dio;			/* try direct i/o in general? */
	अचिन्हित अक्षर try_dio_now;		/* try direct i/o beक्रमe next बंद? */
	अचिन्हित अक्षर c_algo;			/* compression algorithm */
	अचिन्हित अक्षर pos_unknown;			/* after reset position unknown */
	अचिन्हित अक्षर sili;			/* use SILI when पढ़ोing in variable b mode */
	अचिन्हित अक्षर immediate_filemark;	/* ग_लिखो filemark immediately */
	पूर्णांक tape_type;
	पूर्णांक दीर्घ_समयout;	/* समयout क्रम commands known to take दीर्घ समय */

	/* Mode अक्षरacteristics */
	काष्ठा st_modedef modes[ST_NBR_MODES];
	पूर्णांक current_mode;

	/* Status variables */
	पूर्णांक partition;
	पूर्णांक new_partition;
	पूर्णांक nbr_partitions;	/* zero until partition support enabled */
	काष्ठा st_partstat ps[ST_NBR_PARTITIONS];
	अचिन्हित अक्षर dirty;
	अचिन्हित अक्षर पढ़ोy;
	अचिन्हित अक्षर ग_लिखो_prot;
	अचिन्हित अक्षर drv_ग_लिखो_prot;
	अचिन्हित अक्षर in_use;
	अचिन्हित अक्षर blksize_changed;
	अचिन्हित अक्षर density_changed;
	अचिन्हित अक्षर compression_changed;
	अचिन्हित अक्षर drv_buffer;
	अचिन्हित अक्षर density;
	अचिन्हित अक्षर करोor_locked;
	अचिन्हित अक्षर स्वतःrew_dev;   /* स्वतः-शुरुआत device */
	अचिन्हित अक्षर rew_at_बंद;  /* शुरुआत necessary at बंद */
	अचिन्हित अक्षर inited;
	अचिन्हित अक्षर cleaning_req;  /* cleaning requested? */
	पूर्णांक block_size;
	पूर्णांक min_block;
	पूर्णांक max_block;
	पूर्णांक recover_count;     /* From tape खोलोing */
	पूर्णांक recover_reg;       /* From last status call */

#अगर DEBUG
	अचिन्हित अक्षर ग_लिखो_pending;
	पूर्णांक nbr_finished;
	पूर्णांक nbr_रुकोs;
	पूर्णांक nbr_requests;
	पूर्णांक nbr_dio;
	पूर्णांक nbr_pages;
	अचिन्हित अक्षर last_cmnd[6];
	अचिन्हित अक्षर last_sense[16];
#पूर्ण_अगर
	काष्ठा gendisk *disk;
	काष्ठा kref     kref;
	काष्ठा scsi_tape_stats *stats;
पूर्ण;

/* Bit masks क्रम use_pf */
#घोषणा USE_PF      1
#घोषणा PF_TESTED   2

/* Values of eof */
#घोषणा	ST_NOखातापूर्ण	0
#घोषणा ST_FM_HIT       1
#घोषणा ST_FM           2
#घोषणा ST_EOM_OK       3
#घोषणा ST_EOM_ERROR	4
#घोषणा	ST_EOD_1        5
#घोषणा ST_EOD_2        6
#घोषणा ST_EOD		7
/* EOD hit जबतक पढ़ोing => ST_EOD_1 => वापस zero => ST_EOD_2 =>
   वापस zero => ST_EOD, वापस ENOSPC */
/* When writing: ST_EOM_OK == early warning found, ग_लिखो OK
		 ST_EOD_1  == allow trying new ग_लिखो after early warning
		 ST_EOM_ERROR == early warning found, not able to ग_लिखो all */

/* Values of rw */
#घोषणा	ST_IDLE		0
#घोषणा	ST_READING	1
#घोषणा	ST_WRITING	2

/* Values of पढ़ोy state */
#घोषणा ST_READY	0
#घोषणा ST_NOT_READY	1
#घोषणा ST_NO_TAPE	2

/* Values क्रम करोor lock state */
#घोषणा ST_UNLOCKED	0
#घोषणा ST_LOCKED_EXPLICIT 1
#घोषणा ST_LOCKED_AUTO  2
#घोषणा ST_LOCK_FAILS   3

/* Positioning SCSI-commands क्रम Tandberg, etc. drives */
#घोषणा	QFA_REQUEST_BLOCK	0x02
#घोषणा	QFA_SEEK_BLOCK		0x0c

/* Setting the binary options */
#घोषणा ST_DONT_TOUCH  0
#घोषणा ST_NO          1
#घोषणा ST_YES         2

#घोषणा EXTENDED_SENSE_START  18

/* Masks क्रम some conditions in the sense data */
#घोषणा SENSE_FMK   0x80
#घोषणा SENSE_EOM   0x40
#घोषणा SENSE_ILI   0x20

#पूर्ण_अगर
