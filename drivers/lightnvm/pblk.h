<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015 IT University of Cखोलोhagen (rrpc.h)
 * Copyright (C) 2016 CNEX Lअसल
 * Initial release: Matias Bjorling <matias@cnexद_असल.com>
 * Write buffering: Javier Gonzalez <javier@cnexद_असल.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * Implementation of a Physical Block-device target क्रम Open-channel SSDs.
 *
 */

#अगर_अघोषित PBLK_H_
#घोषणा PBLK_H_

#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/bपन.स>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/crc32.h>
#समावेश <linux/uuid.h>

#समावेश <linux/lightnvm.h>

/* Run only GC अगर less than 1/X blocks are मुक्त */
#घोषणा GC_LIMIT_INVERSE 5
#घोषणा GC_TIME_MSECS 1000

#घोषणा PBLK_SECTOR (512)
#घोषणा PBLK_EXPOSED_PAGE_SIZE (4096)

#घोषणा PBLK_NR_CLOSE_JOBS (4)

#घोषणा PBLK_CACHE_NAME_LEN (DISK_NAME_LEN + 16)

/* Max 512 LUNs per device */
#घोषणा PBLK_MAX_LUNS_BITMAP (4)

#घोषणा NR_PHY_IN_LOG (PBLK_EXPOSED_PAGE_SIZE / PBLK_SECTOR)

/* Static pool sizes */
#घोषणा PBLK_GEN_WS_POOL_SIZE (2)

#घोषणा PBLK_DEFAULT_OP (11)

क्रमागत अणु
	PBLK_READ		= READ,
	PBLK_WRITE		= WRITE,/* Write from ग_लिखो buffer */
	PBLK_WRITE_INT,			/* Internal ग_लिखो - no ग_लिखो buffer */
	PBLK_READ_RECOV,		/* Recovery पढ़ो - errors allowed */
	PBLK_ERASE,
पूर्ण;

क्रमागत अणु
	/* IO Types */
	PBLK_IOTYPE_USER	= 1 << 0,
	PBLK_IOTYPE_GC		= 1 << 1,

	/* Write buffer flags */
	PBLK_FLUSH_ENTRY	= 1 << 2,
	PBLK_WRITTEN_DATA	= 1 << 3,
	PBLK_SUBMITTED_ENTRY	= 1 << 4,
	PBLK_WRITABLE_ENTRY	= 1 << 5,
पूर्ण;

क्रमागत अणु
	PBLK_BLK_ST_OPEN =	0x1,
	PBLK_BLK_ST_CLOSED =	0x2,
पूर्ण;

क्रमागत अणु
	PBLK_CHUNK_RESET_START,
	PBLK_CHUNK_RESET_DONE,
	PBLK_CHUNK_RESET_FAILED,
पूर्ण;

काष्ठा pblk_sec_meta अणु
	u64 reserved;
	__le64 lba;
पूर्ण;

/* The number of GC lists and the rate-limiter states go together. This way the
 * rate-limiter can dictate how much GC is needed based on resource utilization.
 */
#घोषणा PBLK_GC_NR_LISTS 4

क्रमागत अणु
	PBLK_RL_OFF = 0,
	PBLK_RL_WERR = 1,
	PBLK_RL_HIGH = 2,
	PBLK_RL_MID = 3,
	PBLK_RL_LOW = 4
पूर्ण;

#घोषणा pblk_dma_ppa_size (माप(u64) * NVM_MAX_VLBA)

/* ग_लिखो buffer completion context */
काष्ठा pblk_c_ctx अणु
	काष्ठा list_head list;		/* Head क्रम out-of-order completion */

	अचिन्हित दीर्घ *lun_biपंचांगap;	/* Luns used on current request */
	अचिन्हित पूर्णांक sentry;
	अचिन्हित पूर्णांक nr_valid;
	अचिन्हित पूर्णांक nr_padded;
पूर्ण;

/* पढ़ो context */
काष्ठा pblk_g_ctx अणु
	व्योम *निजी;
	अचिन्हित दीर्घ start_समय;
	u64 lba;
पूर्ण;

/* Pad context */
काष्ठा pblk_pad_rq अणु
	काष्ठा pblk *pblk;
	काष्ठा completion रुको;
	काष्ठा kref ref;
पूर्ण;

/* Recovery context */
काष्ठा pblk_rec_ctx अणु
	काष्ठा pblk *pblk;
	काष्ठा nvm_rq *rqd;
	काष्ठा work_काष्ठा ws_rec;
पूर्ण;

/* Write context */
काष्ठा pblk_w_ctx अणु
	काष्ठा bio_list bios;		/* Original bios - used क्रम completion
					 * in REQ_FUA, REQ_FLUSH हाल
					 */
	u64 lba;			/* Logic addr. associated with entry */
	काष्ठा ppa_addr ppa;		/* Physic addr. associated with entry */
	पूर्णांक flags;			/* Write context flags */
पूर्ण;

काष्ठा pblk_rb_entry अणु
	काष्ठा ppa_addr cacheline;	/* Cacheline क्रम this entry */
	व्योम *data;			/* Poपूर्णांकer to data on this entry */
	काष्ठा pblk_w_ctx w_ctx;	/* Context क्रम this entry */
	काष्ठा list_head index;		/* List head to enable indexes */
पूर्ण;

#घोषणा EMPTY_ENTRY (~0U)

काष्ठा pblk_rb_pages अणु
	काष्ठा page *pages;
	पूर्णांक order;
	काष्ठा list_head list;
पूर्ण;

काष्ठा pblk_rb अणु
	काष्ठा pblk_rb_entry *entries;	/* Ring buffer entries */
	अचिन्हित पूर्णांक mem;		/* Write offset - poपूर्णांकs to next
					 * writable entry in memory
					 */
	अचिन्हित पूर्णांक subm;		/* Read offset - poपूर्णांकs to last entry
					 * that has been submitted to the media
					 * to be persisted
					 */
	अचिन्हित पूर्णांक sync;		/* Synced - backpoपूर्णांकer that संकेतs
					 * the last submitted entry that has
					 * been successfully persisted to media
					 */
	अचिन्हित पूर्णांक flush_poपूर्णांक;	/* Sync poपूर्णांक - last entry that must be
					 * flushed to the media. Used with
					 * REQ_FLUSH and REQ_FUA
					 */
	अचिन्हित पूर्णांक l2p_update;	/* l2p update poपूर्णांक - next entry क्रम
					 * which l2p mapping will be updated to
					 * contain a device ppa address (instead
					 * of a cacheline
					 */
	अचिन्हित पूर्णांक nr_entries;	/* Number of entries in ग_लिखो buffer -
					 * must be a घातer of two
					 */
	अचिन्हित पूर्णांक seg_size;		/* Size of the data segments being
					 * stored on each entry. Typically this
					 * will be 4KB
					 */

	अचिन्हित पूर्णांक back_thres;	/* Threshold that shall be मुख्यtained by
					 * the backpoपूर्णांकer in order to respect
					 * geo->mw_cunits on a per chunk basis
					 */

	काष्ठा list_head pages;		/* List of data pages */

	spinlock_t w_lock;		/* Write lock */
	spinlock_t s_lock;		/* Sync lock */

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_t inflight_flush_poपूर्णांक;	/* Not served REQ_FLUSH | REQ_FUA */
#पूर्ण_अगर
पूर्ण;

#घोषणा PBLK_RECOVERY_SECTORS 16

काष्ठा pblk_lun अणु
	काष्ठा ppa_addr bppa;
	काष्ठा semaphore wr_sem;
पूर्ण;

काष्ठा pblk_gc_rq अणु
	काष्ठा pblk_line *line;
	व्योम *data;
	u64 paddr_list[NVM_MAX_VLBA];
	u64 lba_list[NVM_MAX_VLBA];
	पूर्णांक nr_secs;
	पूर्णांक secs_to_gc;
	काष्ठा list_head list;
पूर्ण;

काष्ठा pblk_gc अणु
	/* These states are not रक्षित by a lock since (i) they are in the
	 * fast path, and (ii) they are not critical.
	 */
	पूर्णांक gc_active;
	पूर्णांक gc_enabled;
	पूर्णांक gc_क्रमced;

	काष्ठा task_काष्ठा *gc_ts;
	काष्ठा task_काष्ठा *gc_ग_लिखोr_ts;
	काष्ठा task_काष्ठा *gc_पढ़ोer_ts;

	काष्ठा workqueue_काष्ठा *gc_line_पढ़ोer_wq;
	काष्ठा workqueue_काष्ठा *gc_पढ़ोer_wq;

	काष्ठा समयr_list gc_समयr;

	काष्ठा semaphore gc_sem;
	atomic_t पढ़ो_inflight_gc; /* Number of lines with inflight GC पढ़ोs */
	atomic_t pipeline_gc;	   /* Number of lines in the GC pipeline -
				    * started पढ़ोs to finished ग_लिखोs
				    */
	पूर्णांक w_entries;

	काष्ठा list_head w_list;
	काष्ठा list_head r_list;

	spinlock_t lock;
	spinlock_t w_lock;
	spinlock_t r_lock;
पूर्ण;

काष्ठा pblk_rl अणु
	अचिन्हित पूर्णांक high;	/* Upper threshold क्रम rate limiter (मुक्त run -
				 * user I/O rate limiter
				 */
	अचिन्हित पूर्णांक high_pw;	/* High rounded up as a घातer of 2 */

#घोषणा PBLK_USER_HIGH_THRS 8	/* Begin ग_लिखो limit at 12% available blks */
#घोषणा PBLK_USER_LOW_THRS 10	/* Aggressive GC at 10% available blocks */

	पूर्णांक rb_winकरोws_pw;	/* Number of rate winकरोws in the ग_लिखो buffer
				 * given as a घातer-of-2. This guarantees that
				 * when user I/O is being rate limited, there
				 * will be reserved enough space क्रम the GC to
				 * place its payload. A winकरोw is of
				 * pblk->max_ग_लिखो_pgs size, which in NVMe is
				 * 64, i.e., 256kb.
				 */
	पूर्णांक rb_budget;		/* Total number of entries available क्रम I/O */
	पूर्णांक rb_user_max;	/* Max buffer entries available क्रम user I/O */
	पूर्णांक rb_gc_max;		/* Max buffer entries available क्रम GC I/O */
	पूर्णांक rb_gc_rsv;		/* Reserved buffer entries क्रम GC I/O */
	पूर्णांक rb_state;		/* Rate-limiter current state */
	पूर्णांक rb_max_io;		/* Maximum size क्रम an I/O giving the config */

	atomic_t rb_user_cnt;	/* User I/O buffer counter */
	atomic_t rb_gc_cnt;	/* GC I/O buffer counter */
	atomic_t rb_space;	/* Space limit in हाल of reaching capacity */

	पूर्णांक rsv_blocks;		/* Reserved blocks क्रम GC */

	पूर्णांक rb_user_active;
	पूर्णांक rb_gc_active;

	atomic_t werr_lines;	/* Number of ग_लिखो error lines that needs gc */

	काष्ठा समयr_list u_समयr;

	अचिन्हित दीर्घ total_blocks;

	atomic_t मुक्त_blocks;		/* Total number of मुक्त blocks (+ OP) */
	atomic_t मुक्त_user_blocks;	/* Number of user मुक्त blocks (no OP) */
पूर्ण;

#घोषणा PBLK_LINE_EMPTY (~0U)

क्रमागत अणु
	/* Line Types */
	PBLK_LINETYPE_FREE = 0,
	PBLK_LINETYPE_LOG = 1,
	PBLK_LINETYPE_DATA = 2,

	/* Line state */
	PBLK_LINESTATE_NEW = 9,
	PBLK_LINESTATE_FREE = 10,
	PBLK_LINESTATE_OPEN = 11,
	PBLK_LINESTATE_CLOSED = 12,
	PBLK_LINESTATE_GC = 13,
	PBLK_LINESTATE_BAD = 14,
	PBLK_LINESTATE_CORRUPT = 15,

	/* GC group */
	PBLK_LINEGC_NONE = 20,
	PBLK_LINEGC_EMPTY = 21,
	PBLK_LINEGC_LOW = 22,
	PBLK_LINEGC_MID = 23,
	PBLK_LINEGC_HIGH = 24,
	PBLK_LINEGC_FULL = 25,
	PBLK_LINEGC_WERR = 26
पूर्ण;

#घोषणा PBLK_MAGIC 0x70626c6b /*pblk*/

/* emeta/smeta persistent storage क्रमmat versions:
 * Changes in major version requires offline migration.
 * Changes in minor version are handled स्वतःmatically during
 * recovery.
 */

#घोषणा SMETA_VERSION_MAJOR (0)
#घोषणा SMETA_VERSION_MINOR (1)

#घोषणा EMETA_VERSION_MAJOR (0)
#घोषणा EMETA_VERSION_MINOR (2)

काष्ठा line_header अणु
	__le32 crc;
	__le32 identअगरier;	/* pblk identअगरier */
	__u8 uuid[16];		/* instance uuid */
	__le16 type;		/* line type */
	__u8 version_major;	/* version major */
	__u8 version_minor;	/* version minor */
	__le32 id;		/* line id क्रम current line */
पूर्ण;

काष्ठा line_smeta अणु
	काष्ठा line_header header;

	__le32 crc;		/* Full काष्ठाure including काष्ठा crc */
	/* Previous line metadata */
	__le32 prev_id;		/* Line id क्रम previous line */

	/* Current line metadata */
	__le64 seq_nr;		/* Sequence number क्रम current line */

	/* Active ग_लिखोrs */
	__le32 winकरोw_wr_lun;	/* Number of parallel LUNs to ग_लिखो */

	__le32 rsvd[2];

	__le64 lun_biपंचांगap[];
पूर्ण;


/*
 * Metadata layout in media:
 *	First sector:
 *		1. काष्ठा line_emeta
 *		2. bad block biपंचांगap (u64 * winकरोw_wr_lun)
 *		3. ग_लिखो amplअगरication counters
 *	Mid sectors (start at lbas_sector):
 *		3. nr_lbas (u64) क्रमming lba list
 *	Last sectors (start at vsc_sector):
 *		4. u32 valid sector count (vsc) क्रम all lines (~0U: मुक्त line)
 */
काष्ठा line_emeta अणु
	काष्ठा line_header header;

	__le32 crc;		/* Full काष्ठाure including काष्ठा crc */

	/* Previous line metadata */
	__le32 prev_id;		/* Line id क्रम prev line */

	/* Current line metadata */
	__le64 seq_nr;		/* Sequence number क्रम current line */

	/* Active ग_लिखोrs */
	__le32 winकरोw_wr_lun;	/* Number of parallel LUNs to ग_लिखो */

	/* Bookkeeping क्रम recovery */
	__le32 next_id;		/* Line id क्रम next line */
	__le64 nr_lbas;		/* Number of lbas mapped in line */
	__le64 nr_valid_lbas;	/* Number of valid lbas mapped in line */
	__le64 bb_biपंचांगap[];     /* Updated bad block biपंचांगap क्रम line */
पूर्ण;


/* Write amplअगरication counters stored on media */
काष्ठा wa_counters अणु
	__le64 user;		/* Number of user written sectors */
	__le64 gc;		/* Number of sectors written by GC*/
	__le64 pad;		/* Number of padded sectors */
पूर्ण;

काष्ठा pblk_emeta अणु
	काष्ठा line_emeta *buf;		/* emeta buffer in media क्रमmat */
	पूर्णांक mem;			/* Write offset - poपूर्णांकs to next
					 * writable entry in memory
					 */
	atomic_t sync;			/* Synced - backpoपूर्णांकer that संकेतs the
					 * last entry that has been successfully
					 * persisted to media
					 */
	अचिन्हित पूर्णांक nr_entries;	/* Number of emeta entries */
पूर्ण;

काष्ठा pblk_smeta अणु
	काष्ठा line_smeta *buf;		/* smeta buffer in persistent क्रमmat */
पूर्ण;

काष्ठा pblk_w_err_gc अणु
	पूर्णांक has_ग_लिखो_err;
	पूर्णांक has_gc_err;
	__le64 *lba_list;
पूर्ण;

काष्ठा pblk_line अणु
	काष्ठा pblk *pblk;
	अचिन्हित पूर्णांक id;		/* Line number corresponds to the
					 * block line
					 */
	अचिन्हित पूर्णांक seq_nr;		/* Unique line sequence number */

	पूर्णांक state;			/* PBLK_LINESTATE_X */
	पूर्णांक type;			/* PBLK_LINETYPE_X */
	पूर्णांक gc_group;			/* PBLK_LINEGC_X */
	काष्ठा list_head list;		/* Free, GC lists */

	अचिन्हित दीर्घ *lun_biपंचांगap;	/* Biपंचांगap क्रम LUNs mapped in line */

	काष्ठा nvm_chk_meta *chks;	/* Chunks क्रमming line */

	काष्ठा pblk_smeta *smeta;	/* Start metadata */
	काष्ठा pblk_emeta *emeta;	/* End medatada */

	पूर्णांक meta_line;			/* Metadata line id */
	पूर्णांक meta_distance;		/* Distance between data and metadata */

	u64 emeta_ssec;			/* Sector where emeta starts */

	अचिन्हित पूर्णांक sec_in_line;	/* Number of usable secs in line */

	atomic_t blk_in_line;		/* Number of good blocks in line */
	अचिन्हित दीर्घ *blk_biपंचांगap;	/* Biपंचांगap क्रम valid/invalid blocks */
	अचिन्हित दीर्घ *erase_biपंचांगap;	/* Biपंचांगap क्रम erased blocks */

	अचिन्हित दीर्घ *map_biपंचांगap;	/* Biपंचांगap क्रम mapped sectors in line */
	अचिन्हित दीर्घ *invalid_biपंचांगap;	/* Biपंचांगap क्रम invalid sectors in line */

	atomic_t left_eblks;		/* Blocks left क्रम erasing */
	atomic_t left_seblks;		/* Blocks left क्रम sync erasing */

	पूर्णांक left_msecs;			/* Sectors left क्रम mapping */
	अचिन्हित पूर्णांक cur_sec;		/* Sector map poपूर्णांकer */
	अचिन्हित पूर्णांक nr_valid_lbas;	/* Number of valid lbas in line */

	__le32 *vsc;			/* Valid sector count in line */

	काष्ठा kref ref;		/* Write buffer L2P references */
	atomic_t sec_to_update;         /* Outstanding L2P updates to ppa */

	काष्ठा pblk_w_err_gc *w_err_gc;	/* Write error gc recovery metadata */

	spinlock_t lock;		/* Necessary क्रम invalid_biपंचांगap only */
पूर्ण;

#घोषणा PBLK_DATA_LINES 4

क्रमागत अणु
	PBLK_EMETA_TYPE_HEADER = 1,	/* काष्ठा line_emeta first sector */
	PBLK_EMETA_TYPE_LLBA = 2,	/* lba list - type: __le64 */
	PBLK_EMETA_TYPE_VSC = 3,	/* vsc list - type: __le32 */
पूर्ण;

काष्ठा pblk_line_mgmt अणु
	पूर्णांक nr_lines;			/* Total number of full lines */
	पूर्णांक nr_मुक्त_lines;		/* Number of full lines in मुक्त list */

	/* Free lists - use मुक्त_lock */
	काष्ठा list_head मुक्त_list;	/* Full lines पढ़ोy to use */
	काष्ठा list_head corrupt_list;	/* Full lines corrupted */
	काष्ठा list_head bad_list;	/* Full lines bad */

	/* GC lists - use gc_lock */
	काष्ठा list_head *gc_lists[PBLK_GC_NR_LISTS];
	काष्ठा list_head gc_high_list;	/* Full lines पढ़ोy to GC, high isc */
	काष्ठा list_head gc_mid_list;	/* Full lines पढ़ोy to GC, mid isc */
	काष्ठा list_head gc_low_list;	/* Full lines पढ़ोy to GC, low isc */

	काष्ठा list_head gc_werr_list;  /* Write err recovery list */

	काष्ठा list_head gc_full_list;	/* Full lines पढ़ोy to GC, no valid */
	काष्ठा list_head gc_empty_list;	/* Full lines बंद, all valid */

	काष्ठा pblk_line *log_line;	/* Current FTL log line */
	काष्ठा pblk_line *data_line;	/* Current data line */
	काष्ठा pblk_line *log_next;	/* Next FTL log line */
	काष्ठा pblk_line *data_next;	/* Next data line */

	काष्ठा list_head emeta_list;	/* Lines queued to schedule emeta */

	__le32 *vsc_list;		/* Valid sector counts क्रम all lines */

	/* Pre-allocated metadata क्रम data lines */
	काष्ठा pblk_smeta *sline_meta[PBLK_DATA_LINES];
	काष्ठा pblk_emeta *eline_meta[PBLK_DATA_LINES];
	अचिन्हित दीर्घ meta_biपंचांगap;

	/* Cache and mempool क्रम map/invalid biपंचांगaps */
	काष्ठा kmem_cache *biपंचांगap_cache;
	mempool_t *biपंचांगap_pool;

	/* Helpers क्रम fast biपंचांगap calculations */
	अचिन्हित दीर्घ *bb_ढाँचा;
	अचिन्हित दीर्घ *bb_aux;

	अचिन्हित दीर्घ d_seq_nr;		/* Data line unique sequence number */
	अचिन्हित दीर्घ l_seq_nr;		/* Log line unique sequence number */

	spinlock_t मुक्त_lock;
	spinlock_t बंद_lock;
	spinlock_t gc_lock;
पूर्ण;

काष्ठा pblk_line_meta अणु
	अचिन्हित पूर्णांक smeta_len;		/* Total length क्रम smeta */
	अचिन्हित पूर्णांक smeta_sec;		/* Sectors needed क्रम smeta */

	अचिन्हित पूर्णांक emeta_len[4];	/* Lengths क्रम emeta:
					 *  [0]: Total
					 *  [1]: काष्ठा line_emeta +
					 *       bb_biपंचांगap + काष्ठा wa_counters
					 *  [2]: L2P portion
					 *  [3]: vsc
					 */
	अचिन्हित पूर्णांक emeta_sec[4];	/* Sectors needed क्रम emeta. Same layout
					 * as emeta_len
					 */

	अचिन्हित पूर्णांक emeta_bb;		/* Boundary क्रम bb that affects emeta */

	अचिन्हित पूर्णांक vsc_list_len;	/* Length क्रम vsc list */
	अचिन्हित पूर्णांक sec_biपंचांगap_len;	/* Length क्रम sector biपंचांगap in line */
	अचिन्हित पूर्णांक blk_biपंचांगap_len;	/* Length क्रम block biपंचांगap in line */
	अचिन्हित पूर्णांक lun_biपंचांगap_len;	/* Length क्रम lun biपंचांगap in line */

	अचिन्हित पूर्णांक blk_per_line;	/* Number of blocks in a full line */
	अचिन्हित पूर्णांक sec_per_line;	/* Number of sectors in a line */
	अचिन्हित पूर्णांक dsec_per_line;	/* Number of data sectors in a line */
	अचिन्हित पूर्णांक min_blk_line;	/* Min. number of good blocks in line */

	अचिन्हित पूर्णांक mid_thrs;		/* Threshold क्रम GC mid list */
	अचिन्हित पूर्णांक high_thrs;		/* Threshold क्रम GC high list */

	अचिन्हित पूर्णांक meta_distance;	/* Distance between data and metadata */
पूर्ण;

क्रमागत अणु
	PBLK_STATE_RUNNING = 0,
	PBLK_STATE_STOPPING = 1,
	PBLK_STATE_RECOVERING = 2,
	PBLK_STATE_STOPPED = 3,
पूर्ण;

/* Internal क्रमmat to support not घातer-of-2 device क्रमmats */
काष्ठा pblk_addrf अणु
	/* gen to dev */
	पूर्णांक sec_stripe;
	पूर्णांक ch_stripe;
	पूर्णांक lun_stripe;

	/* dev to gen */
	पूर्णांक sec_lun_stripe;
	पूर्णांक sec_ws_stripe;
पूर्ण;

काष्ठा pblk अणु
	काष्ठा nvm_tgt_dev *dev;
	काष्ठा gendisk *disk;

	काष्ठा kobject kobj;

	काष्ठा pblk_lun *luns;

	काष्ठा pblk_line *lines;		/* Line array */
	काष्ठा pblk_line_mgmt l_mg;		/* Line management */
	काष्ठा pblk_line_meta lm;		/* Line metadata */

	काष्ठा nvm_addrf addrf;		/* Aligned address क्रमmat */
	काष्ठा pblk_addrf uaddrf;	/* Unaligned address क्रमmat */
	पूर्णांक addrf_len;

	काष्ठा pblk_rb rwb;

	पूर्णांक state;			/* pblk line state */

	पूर्णांक min_ग_लिखो_pgs; /* Minimum amount of pages required by controller */
	पूर्णांक min_ग_लिखो_pgs_data; /* Minimum amount of payload pages */
	पूर्णांक max_ग_लिखो_pgs; /* Maximum amount of pages supported by controller */
	पूर्णांक oob_meta_size; /* Size of OOB sector metadata */

	sector_t capacity; /* Device capacity when bad blocks are subtracted */

	पूर्णांक op;      /* Percentage of device used क्रम over-provisioning */
	पूर्णांक op_blks; /* Number of blocks used क्रम over-provisioning */

	/* pblk provisioning values. Used by rate limiter */
	काष्ठा pblk_rl rl;

	पूर्णांक sec_per_ग_लिखो;

	guid_t instance_uuid;

	/* Persistent ग_लिखो amplअगरication counters, 4kb sector I/Os */
	atomic64_t user_wa;		/* Sectors written by user */
	atomic64_t gc_wa;		/* Sectors written by GC */
	atomic64_t pad_wa;		/* Padded sectors written */

	/* Reset values क्रम delta ग_लिखो amplअगरication measurements */
	u64 user_rst_wa;
	u64 gc_rst_wa;
	u64 pad_rst_wa;

	/* Counters used क्रम calculating padding distribution */
	atomic64_t *pad_dist;		/* Padding distribution buckets */
	u64 nr_flush_rst;		/* Flushes reset value क्रम pad dist.*/
	atomic64_t nr_flush;		/* Number of flush/fua I/O */

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Non-persistent debug counters, 4kb sector I/Os */
	atomic_दीर्घ_t inflight_ग_लिखोs;	/* Inflight ग_लिखोs (user and gc) */
	atomic_दीर्घ_t padded_ग_लिखोs;	/* Sectors padded due to flush/fua */
	atomic_दीर्घ_t padded_wb;	/* Sectors padded in ग_लिखो buffer */
	atomic_दीर्घ_t req_ग_लिखोs;	/* Sectors stored on ग_लिखो buffer */
	atomic_दीर्घ_t sub_ग_लिखोs;	/* Sectors submitted from buffer */
	atomic_दीर्घ_t sync_ग_लिखोs;	/* Sectors synced to media */
	atomic_दीर्घ_t inflight_पढ़ोs;	/* Inflight sector पढ़ो requests */
	atomic_दीर्घ_t cache_पढ़ोs;	/* Read requests that hit the cache */
	atomic_दीर्घ_t sync_पढ़ोs;	/* Completed sector पढ़ो requests */
	atomic_दीर्घ_t recov_ग_लिखोs;	/* Sectors submitted from recovery */
	atomic_दीर्घ_t recov_gc_ग_लिखोs;	/* Sectors submitted from ग_लिखो GC */
	atomic_दीर्घ_t recov_gc_पढ़ोs;	/* Sectors submitted from पढ़ो GC */
#पूर्ण_अगर

	spinlock_t lock;

	atomic_दीर्घ_t पढ़ो_failed;
	atomic_दीर्घ_t पढ़ो_empty;
	atomic_दीर्घ_t पढ़ो_high_ecc;
	atomic_दीर्घ_t पढ़ो_failed_gc;
	atomic_दीर्घ_t ग_लिखो_failed;
	atomic_दीर्घ_t erase_failed;

	atomic_t inflight_io;		/* General inflight I/O counter */

	काष्ठा task_काष्ठा *ग_लिखोr_ts;

	/* Simple translation map of logical addresses to physical addresses.
	 * The logical addresses is known by the host प्रणाली, जबतक the physical
	 * addresses are used when writing to the disk block device.
	 */
	अचिन्हित अक्षर *trans_map;
	spinlock_t trans_lock;

	काष्ठा list_head compl_list;

	spinlock_t resubmit_lock;	 /* Resubmit list lock */
	काष्ठा list_head resubmit_list; /* Resubmit list क्रम failed ग_लिखोs*/

	mempool_t page_bio_pool;
	mempool_t gen_ws_pool;
	mempool_t rec_pool;
	mempool_t r_rq_pool;
	mempool_t w_rq_pool;
	mempool_t e_rq_pool;

	काष्ठा workqueue_काष्ठा *बंद_wq;
	काष्ठा workqueue_काष्ठा *bb_wq;
	काष्ठा workqueue_काष्ठा *r_end_wq;

	काष्ठा समयr_list wसमयr;

	काष्ठा pblk_gc gc;
पूर्ण;

काष्ठा pblk_line_ws अणु
	काष्ठा pblk *pblk;
	काष्ठा pblk_line *line;
	व्योम *priv;
	काष्ठा work_काष्ठा ws;
पूर्ण;

#घोषणा pblk_g_rq_size (माप(काष्ठा nvm_rq) + माप(काष्ठा pblk_g_ctx))
#घोषणा pblk_w_rq_size (माप(काष्ठा nvm_rq) + माप(काष्ठा pblk_c_ctx))

#घोषणा pblk_err(pblk, fmt, ...)			\
	pr_err("pblk %s: " fmt, pblk->disk->disk_name, ##__VA_ARGS__)
#घोषणा pblk_info(pblk, fmt, ...)			\
	pr_info("pblk %s: " fmt, pblk->disk->disk_name, ##__VA_ARGS__)
#घोषणा pblk_warn(pblk, fmt, ...)			\
	pr_warn("pblk %s: " fmt, pblk->disk->disk_name, ##__VA_ARGS__)
#घोषणा pblk_debug(pblk, fmt, ...)			\
	pr_debug("pblk %s: " fmt, pblk->disk->disk_name, ##__VA_ARGS__)

/*
 * pblk ring buffer operations
 */
पूर्णांक pblk_rb_init(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक threshold,
		 अचिन्हित पूर्णांक seg_sz);
पूर्णांक pblk_rb_may_ग_लिखो_user(काष्ठा pblk_rb *rb, काष्ठा bio *bio,
			   अचिन्हित पूर्णांक nr_entries, अचिन्हित पूर्णांक *pos);
पूर्णांक pblk_rb_may_ग_लिखो_gc(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries,
			 अचिन्हित पूर्णांक *pos);
व्योम pblk_rb_ग_लिखो_entry_user(काष्ठा pblk_rb *rb, व्योम *data,
			      काष्ठा pblk_w_ctx w_ctx, अचिन्हित पूर्णांक pos);
व्योम pblk_rb_ग_लिखो_entry_gc(काष्ठा pblk_rb *rb, व्योम *data,
			    काष्ठा pblk_w_ctx w_ctx, काष्ठा pblk_line *line,
			    u64 paddr, अचिन्हित पूर्णांक pos);
काष्ठा pblk_w_ctx *pblk_rb_w_ctx(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक pos);
व्योम pblk_rb_flush(काष्ठा pblk_rb *rb);

व्योम pblk_rb_sync_l2p(काष्ठा pblk_rb *rb);
अचिन्हित पूर्णांक pblk_rb_पढ़ो_to_bio(काष्ठा pblk_rb *rb, काष्ठा nvm_rq *rqd,
				 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक nr_entries,
				 अचिन्हित पूर्णांक count);
पूर्णांक pblk_rb_copy_to_bio(काष्ठा pblk_rb *rb, काष्ठा bio *bio, sector_t lba,
			काष्ठा ppa_addr ppa);
अचिन्हित पूर्णांक pblk_rb_पढ़ो_commit(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक entries);

अचिन्हित पूर्णांक pblk_rb_sync_init(काष्ठा pblk_rb *rb, अचिन्हित दीर्घ *flags);
अचिन्हित पूर्णांक pblk_rb_sync_advance(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries);
अचिन्हित पूर्णांक pblk_rb_ptr_wrap(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक p,
			      अचिन्हित पूर्णांक nr_entries);
व्योम pblk_rb_sync_end(काष्ठा pblk_rb *rb, अचिन्हित दीर्घ *flags);
अचिन्हित पूर्णांक pblk_rb_flush_poपूर्णांक_count(काष्ठा pblk_rb *rb);

अचिन्हित पूर्णांक pblk_rb_पढ़ो_count(काष्ठा pblk_rb *rb);
अचिन्हित पूर्णांक pblk_rb_sync_count(काष्ठा pblk_rb *rb);
अचिन्हित पूर्णांक pblk_rb_wrap_pos(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक pos);

पूर्णांक pblk_rb_tear_करोwn_check(काष्ठा pblk_rb *rb);
पूर्णांक pblk_rb_pos_oob(काष्ठा pblk_rb *rb, u64 pos);
व्योम pblk_rb_मुक्त(काष्ठा pblk_rb *rb);
sमाप_प्रकार pblk_rb_sysfs(काष्ठा pblk_rb *rb, अक्षर *buf);

/*
 * pblk core
 */
काष्ठा nvm_rq *pblk_alloc_rqd(काष्ठा pblk *pblk, पूर्णांक type);
व्योम pblk_मुक्त_rqd(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, पूर्णांक type);
पूर्णांक pblk_alloc_rqd_meta(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);
व्योम pblk_मुक्त_rqd_meta(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);
व्योम pblk_set_sec_per_ग_लिखो(काष्ठा pblk *pblk, पूर्णांक sec_per_ग_लिखो);
पूर्णांक pblk_setup_w_rec_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
			काष्ठा pblk_c_ctx *c_ctx);
व्योम pblk_discard(काष्ठा pblk *pblk, काष्ठा bio *bio);
काष्ठा nvm_chk_meta *pblk_get_chunk_meta(काष्ठा pblk *pblk);
काष्ठा nvm_chk_meta *pblk_chunk_get_off(काष्ठा pblk *pblk,
					      काष्ठा nvm_chk_meta *lp,
					      काष्ठा ppa_addr ppa);
व्योम pblk_log_ग_लिखो_err(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);
व्योम pblk_log_पढ़ो_err(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);
पूर्णांक pblk_submit_io(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, व्योम *buf);
पूर्णांक pblk_submit_io_sync(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, व्योम *buf);
पूर्णांक pblk_submit_meta_io(काष्ठा pblk *pblk, काष्ठा pblk_line *meta_line);
व्योम pblk_check_chunk_state_update(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);
काष्ठा pblk_line *pblk_line_get(काष्ठा pblk *pblk);
काष्ठा pblk_line *pblk_line_get_first_data(काष्ठा pblk *pblk);
काष्ठा pblk_line *pblk_line_replace_data(काष्ठा pblk *pblk);
व्योम pblk_ppa_to_line_put(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa);
व्योम pblk_rq_to_line_put(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);
पूर्णांक pblk_line_recov_alloc(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
व्योम pblk_line_recov_बंद(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
काष्ठा pblk_line *pblk_line_get_data(काष्ठा pblk *pblk);
काष्ठा pblk_line *pblk_line_get_erase(काष्ठा pblk *pblk);
पूर्णांक pblk_line_erase(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
पूर्णांक pblk_line_is_full(काष्ठा pblk_line *line);
व्योम pblk_line_मुक्त(काष्ठा pblk_line *line);
व्योम pblk_line_बंद_meta(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
व्योम pblk_line_बंद(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
व्योम pblk_line_बंद_ws(काष्ठा work_काष्ठा *work);
व्योम pblk_pipeline_stop(काष्ठा pblk *pblk);
व्योम __pblk_pipeline_stop(काष्ठा pblk *pblk);
व्योम __pblk_pipeline_flush(काष्ठा pblk *pblk);
व्योम pblk_gen_run_ws(काष्ठा pblk *pblk, काष्ठा pblk_line *line, व्योम *priv,
		     व्योम (*work)(काष्ठा work_काष्ठा *), gfp_t gfp_mask,
		     काष्ठा workqueue_काष्ठा *wq);
u64 pblk_line_smeta_start(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
पूर्णांक pblk_line_smeta_पढ़ो(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
पूर्णांक pblk_line_emeta_पढ़ो(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			 व्योम *emeta_buf);
पूर्णांक pblk_blk_erase_async(काष्ठा pblk *pblk, काष्ठा ppa_addr erase_ppa);
व्योम pblk_line_put(काष्ठा kref *ref);
व्योम pblk_line_put_wq(काष्ठा kref *ref);
काष्ठा list_head *pblk_line_gc_list(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
u64 pblk_lookup_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line);
व्योम pblk_dealloc_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line, पूर्णांक nr_secs);
u64 pblk_alloc_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line, पूर्णांक nr_secs);
u64 __pblk_alloc_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line, पूर्णांक nr_secs);
पूर्णांक pblk_calc_secs(काष्ठा pblk *pblk, अचिन्हित दीर्घ secs_avail,
		   अचिन्हित दीर्घ secs_to_flush, bool skip_meta);
व्योम pblk_करोwn_rq(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa,
		  अचिन्हित दीर्घ *lun_biपंचांगap);
व्योम pblk_करोwn_chunk(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa);
व्योम pblk_up_chunk(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa);
व्योम pblk_up_rq(काष्ठा pblk *pblk, अचिन्हित दीर्घ *lun_biपंचांगap);
पूर्णांक pblk_bio_add_pages(काष्ठा pblk *pblk, काष्ठा bio *bio, gfp_t flags,
		       पूर्णांक nr_pages);
व्योम pblk_bio_मुक्त_pages(काष्ठा pblk *pblk, काष्ठा bio *bio, पूर्णांक off,
			 पूर्णांक nr_pages);
व्योम pblk_map_invalidate(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa);
व्योम __pblk_map_invalidate(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			   u64 paddr);
व्योम pblk_update_map(काष्ठा pblk *pblk, sector_t lba, काष्ठा ppa_addr ppa);
व्योम pblk_update_map_cache(काष्ठा pblk *pblk, sector_t lba,
			   काष्ठा ppa_addr ppa);
व्योम pblk_update_map_dev(काष्ठा pblk *pblk, sector_t lba,
			 काष्ठा ppa_addr ppa, काष्ठा ppa_addr entry_line);
पूर्णांक pblk_update_map_gc(काष्ठा pblk *pblk, sector_t lba, काष्ठा ppa_addr ppa,
		       काष्ठा pblk_line *gc_line, u64 paddr);
व्योम pblk_lookup_l2p_अक्रम(काष्ठा pblk *pblk, काष्ठा ppa_addr *ppas,
			  u64 *lba_list, पूर्णांक nr_secs);
पूर्णांक pblk_lookup_l2p_seq(काष्ठा pblk *pblk, काष्ठा ppa_addr *ppas,
			 sector_t blba, पूर्णांक nr_secs, bool *from_cache);
व्योम *pblk_get_meta_क्रम_ग_लिखोs(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);
व्योम pblk_get_packed_meta(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd);

/*
 * pblk user I/O ग_लिखो path
 */
व्योम pblk_ग_लिखो_to_cache(काष्ठा pblk *pblk, काष्ठा bio *bio,
			अचिन्हित दीर्घ flags);
पूर्णांक pblk_ग_लिखो_gc_to_cache(काष्ठा pblk *pblk, काष्ठा pblk_gc_rq *gc_rq);

/*
 * pblk map
 */
पूर्णांक pblk_map_erase_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
		       अचिन्हित पूर्णांक sentry, अचिन्हित दीर्घ *lun_biपंचांगap,
		       अचिन्हित पूर्णांक valid_secs, काष्ठा ppa_addr *erase_ppa);
पूर्णांक pblk_map_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, अचिन्हित पूर्णांक sentry,
		 अचिन्हित दीर्घ *lun_biपंचांगap, अचिन्हित पूर्णांक valid_secs,
		 अचिन्हित पूर्णांक off);

/*
 * pblk ग_लिखो thपढ़ो
 */
पूर्णांक pblk_ग_लिखो_ts(व्योम *data);
व्योम pblk_ग_लिखो_समयr_fn(काष्ठा समयr_list *t);
व्योम pblk_ग_लिखो_should_kick(काष्ठा pblk *pblk);
व्योम pblk_ग_लिखो_kick(काष्ठा pblk *pblk);

/*
 * pblk पढ़ो path
 */
बाह्य काष्ठा bio_set pblk_bio_set;
व्योम pblk_submit_पढ़ो(काष्ठा pblk *pblk, काष्ठा bio *bio);
पूर्णांक pblk_submit_पढ़ो_gc(काष्ठा pblk *pblk, काष्ठा pblk_gc_rq *gc_rq);
/*
 * pblk recovery
 */
काष्ठा pblk_line *pblk_recov_l2p(काष्ठा pblk *pblk);
पूर्णांक pblk_recov_pad(काष्ठा pblk *pblk);
पूर्णांक pblk_recov_check_emeta(काष्ठा pblk *pblk, काष्ठा line_emeta *emeta);

/*
 * pblk gc
 */
#घोषणा PBLK_GC_MAX_READERS 8	/* Max number of outstanding GC पढ़ोer jobs */
#घोषणा PBLK_GC_RQ_QD 128	/* Queue depth क्रम inflight GC requests */
#घोषणा PBLK_GC_L_QD 4		/* Queue depth क्रम inflight GC lines */

पूर्णांक pblk_gc_init(काष्ठा pblk *pblk);
व्योम pblk_gc_निकास(काष्ठा pblk *pblk, bool graceful);
व्योम pblk_gc_should_start(काष्ठा pblk *pblk);
व्योम pblk_gc_should_stop(काष्ठा pblk *pblk);
व्योम pblk_gc_should_kick(काष्ठा pblk *pblk);
व्योम pblk_gc_मुक्त_full_lines(काष्ठा pblk *pblk);
व्योम pblk_gc_sysfs_state_show(काष्ठा pblk *pblk, पूर्णांक *gc_enabled,
			      पूर्णांक *gc_active);
पूर्णांक pblk_gc_sysfs_क्रमce(काष्ठा pblk *pblk, पूर्णांक क्रमce);
व्योम pblk_put_line_back(काष्ठा pblk *pblk, काष्ठा pblk_line *line);

/*
 * pblk rate limiter
 */
व्योम pblk_rl_init(काष्ठा pblk_rl *rl, पूर्णांक budget, पूर्णांक threshold);
व्योम pblk_rl_मुक्त(काष्ठा pblk_rl *rl);
व्योम pblk_rl_update_rates(काष्ठा pblk_rl *rl);
पूर्णांक pblk_rl_high_thrs(काष्ठा pblk_rl *rl);
अचिन्हित दीर्घ pblk_rl_nr_मुक्त_blks(काष्ठा pblk_rl *rl);
अचिन्हित दीर्घ pblk_rl_nr_user_मुक्त_blks(काष्ठा pblk_rl *rl);
पूर्णांक pblk_rl_user_may_insert(काष्ठा pblk_rl *rl, पूर्णांक nr_entries);
व्योम pblk_rl_inserted(काष्ठा pblk_rl *rl, पूर्णांक nr_entries);
व्योम pblk_rl_user_in(काष्ठा pblk_rl *rl, पूर्णांक nr_entries);
पूर्णांक pblk_rl_gc_may_insert(काष्ठा pblk_rl *rl, पूर्णांक nr_entries);
व्योम pblk_rl_gc_in(काष्ठा pblk_rl *rl, पूर्णांक nr_entries);
व्योम pblk_rl_out(काष्ठा pblk_rl *rl, पूर्णांक nr_user, पूर्णांक nr_gc);
पूर्णांक pblk_rl_max_io(काष्ठा pblk_rl *rl);
व्योम pblk_rl_मुक्त_lines_inc(काष्ठा pblk_rl *rl, काष्ठा pblk_line *line);
व्योम pblk_rl_मुक्त_lines_dec(काष्ठा pblk_rl *rl, काष्ठा pblk_line *line,
			    bool used);
पूर्णांक pblk_rl_is_limit(काष्ठा pblk_rl *rl);

व्योम pblk_rl_werr_line_in(काष्ठा pblk_rl *rl);
व्योम pblk_rl_werr_line_out(काष्ठा pblk_rl *rl);

/*
 * pblk sysfs
 */
पूर्णांक pblk_sysfs_init(काष्ठा gendisk *tdisk);
व्योम pblk_sysfs_निकास(काष्ठा gendisk *tdisk);

अटल अंतरभूत काष्ठा nvm_rq *nvm_rq_from_c_ctx(व्योम *c_ctx)
अणु
	वापस c_ctx - माप(काष्ठा nvm_rq);
पूर्ण

अटल अंतरभूत व्योम *emeta_to_bb(काष्ठा line_emeta *emeta)
अणु
	वापस emeta->bb_biपंचांगap;
पूर्ण

अटल अंतरभूत व्योम *emeta_to_wa(काष्ठा pblk_line_meta *lm,
				काष्ठा line_emeta *emeta)
अणु
	वापस emeta->bb_biपंचांगap + lm->blk_biपंचांगap_len;
पूर्ण

अटल अंतरभूत व्योम *emeta_to_lbas(काष्ठा pblk *pblk, काष्ठा line_emeta *emeta)
अणु
	वापस ((व्योम *)emeta + pblk->lm.emeta_len[1]);
पूर्ण

अटल अंतरभूत व्योम *emeta_to_vsc(काष्ठा pblk *pblk, काष्ठा line_emeta *emeta)
अणु
	वापस (emeta_to_lbas(pblk, emeta) + pblk->lm.emeta_len[2]);
पूर्ण

अटल अंतरभूत पूर्णांक pblk_line_vsc(काष्ठा pblk_line *line)
अणु
	वापस le32_to_cpu(*line->vsc);
पूर्ण

अटल अंतरभूत पूर्णांक pblk_ppa_to_line_id(काष्ठा ppa_addr p)
अणु
	वापस p.a.blk;
पूर्ण

अटल अंतरभूत काष्ठा pblk_line *pblk_ppa_to_line(काष्ठा pblk *pblk,
						 काष्ठा ppa_addr p)
अणु
	वापस &pblk->lines[pblk_ppa_to_line_id(p)];
पूर्ण

अटल अंतरभूत पूर्णांक pblk_ppa_to_pos(काष्ठा nvm_geo *geo, काष्ठा ppa_addr p)
अणु
	वापस p.a.lun * geo->num_ch + p.a.ch;
पूर्ण

अटल अंतरभूत काष्ठा ppa_addr addr_to_gen_ppa(काष्ठा pblk *pblk, u64 paddr,
					      u64 line_id)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा ppa_addr ppa;

	अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		काष्ठा nvm_addrf_12 *ppaf = (काष्ठा nvm_addrf_12 *)&pblk->addrf;

		ppa.ppa = 0;
		ppa.g.blk = line_id;
		ppa.g.pg = (paddr & ppaf->pg_mask) >> ppaf->pg_offset;
		ppa.g.lun = (paddr & ppaf->lun_mask) >> ppaf->lun_offset;
		ppa.g.ch = (paddr & ppaf->ch_mask) >> ppaf->ch_offset;
		ppa.g.pl = (paddr & ppaf->pln_mask) >> ppaf->pln_offset;
		ppa.g.sec = (paddr & ppaf->sec_mask) >> ppaf->sec_offset;
	पूर्ण अन्यथा अणु
		काष्ठा pblk_addrf *uaddrf = &pblk->uaddrf;
		पूर्णांक secs, chnls, luns;

		ppa.ppa = 0;

		ppa.m.chk = line_id;

		paddr = भाग_u64_rem(paddr, uaddrf->sec_stripe, &secs);
		ppa.m.sec = secs;

		paddr = भाग_u64_rem(paddr, uaddrf->ch_stripe, &chnls);
		ppa.m.grp = chnls;

		paddr = भाग_u64_rem(paddr, uaddrf->lun_stripe, &luns);
		ppa.m.pu = luns;

		ppa.m.sec += uaddrf->sec_stripe * paddr;
	पूर्ण

	वापस ppa;
पूर्ण

अटल अंतरभूत काष्ठा nvm_chk_meta *pblk_dev_ppa_to_chunk(काष्ठा pblk *pblk,
							काष्ठा ppa_addr p)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line *line = pblk_ppa_to_line(pblk, p);
	पूर्णांक pos = pblk_ppa_to_pos(geo, p);

	वापस &line->chks[pos];
पूर्ण

अटल अंतरभूत u64 pblk_dev_ppa_to_chunk_addr(काष्ठा pblk *pblk,
							काष्ठा ppa_addr p)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;

	वापस dev_to_chunk_addr(dev->parent, &pblk->addrf, p);
पूर्ण

अटल अंतरभूत u64 pblk_dev_ppa_to_line_addr(काष्ठा pblk *pblk,
							काष्ठा ppa_addr p)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	u64 paddr;

	अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		काष्ठा nvm_addrf_12 *ppaf = (काष्ठा nvm_addrf_12 *)&pblk->addrf;

		paddr = (u64)p.g.ch << ppaf->ch_offset;
		paddr |= (u64)p.g.lun << ppaf->lun_offset;
		paddr |= (u64)p.g.pg << ppaf->pg_offset;
		paddr |= (u64)p.g.pl << ppaf->pln_offset;
		paddr |= (u64)p.g.sec << ppaf->sec_offset;
	पूर्ण अन्यथा अणु
		काष्ठा pblk_addrf *uaddrf = &pblk->uaddrf;
		u64 secs = p.m.sec;
		पूर्णांक sec_stripe;

		paddr = (u64)p.m.grp * uaddrf->sec_stripe;
		paddr += (u64)p.m.pu * uaddrf->sec_lun_stripe;

		secs = भाग_u64_rem(secs, uaddrf->sec_stripe, &sec_stripe);
		paddr += secs * uaddrf->sec_ws_stripe;
		paddr += sec_stripe;
	पूर्ण

	वापस paddr;
पूर्ण

अटल अंतरभूत काष्ठा ppa_addr pblk_ppa32_to_ppa64(काष्ठा pblk *pblk, u32 ppa32)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;

	वापस nvm_ppa32_to_ppa64(dev->parent, &pblk->addrf, ppa32);
पूर्ण

अटल अंतरभूत u32 pblk_ppa64_to_ppa32(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa64)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;

	वापस nvm_ppa64_to_ppa32(dev->parent, &pblk->addrf, ppa64);
पूर्ण

अटल अंतरभूत काष्ठा ppa_addr pblk_trans_map_get(काष्ठा pblk *pblk,
								sector_t lba)
अणु
	काष्ठा ppa_addr ppa;

	अगर (pblk->addrf_len < 32) अणु
		u32 *map = (u32 *)pblk->trans_map;

		ppa = pblk_ppa32_to_ppa64(pblk, map[lba]);
	पूर्ण अन्यथा अणु
		काष्ठा ppa_addr *map = (काष्ठा ppa_addr *)pblk->trans_map;

		ppa = map[lba];
	पूर्ण

	वापस ppa;
पूर्ण

अटल अंतरभूत व्योम pblk_trans_map_set(काष्ठा pblk *pblk, sector_t lba,
						काष्ठा ppa_addr ppa)
अणु
	अगर (pblk->addrf_len < 32) अणु
		u32 *map = (u32 *)pblk->trans_map;

		map[lba] = pblk_ppa64_to_ppa32(pblk, ppa);
	पूर्ण अन्यथा अणु
		u64 *map = (u64 *)pblk->trans_map;

		map[lba] = ppa.ppa;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक pblk_ppa_empty(काष्ठा ppa_addr ppa_addr)
अणु
	वापस (ppa_addr.ppa == ADDR_EMPTY);
पूर्ण

अटल अंतरभूत व्योम pblk_ppa_set_empty(काष्ठा ppa_addr *ppa_addr)
अणु
	ppa_addr->ppa = ADDR_EMPTY;
पूर्ण

अटल अंतरभूत bool pblk_ppa_comp(काष्ठा ppa_addr lppa, काष्ठा ppa_addr rppa)
अणु
	वापस (lppa.ppa == rppa.ppa);
पूर्ण

अटल अंतरभूत पूर्णांक pblk_addr_in_cache(काष्ठा ppa_addr ppa)
अणु
	वापस (ppa.ppa != ADDR_EMPTY && ppa.c.is_cached);
पूर्ण

अटल अंतरभूत पूर्णांक pblk_addr_to_cacheline(काष्ठा ppa_addr ppa)
अणु
	वापस ppa.c.line;
पूर्ण

अटल अंतरभूत काष्ठा ppa_addr pblk_cacheline_to_addr(पूर्णांक addr)
अणु
	काष्ठा ppa_addr p;

	p.c.line = addr;
	p.c.is_cached = 1;

	वापस p;
पूर्ण

अटल अंतरभूत u32 pblk_calc_meta_header_crc(काष्ठा pblk *pblk,
					    काष्ठा line_header *header)
अणु
	u32 crc = ~(u32)0;

	crc = crc32_le(crc, (अचिन्हित अक्षर *)header + माप(crc),
				माप(काष्ठा line_header) - माप(crc));

	वापस crc;
पूर्ण

अटल अंतरभूत u32 pblk_calc_smeta_crc(काष्ठा pblk *pblk,
				      काष्ठा line_smeta *smeta)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	u32 crc = ~(u32)0;

	crc = crc32_le(crc, (अचिन्हित अक्षर *)smeta +
				माप(काष्ठा line_header) + माप(crc),
				lm->smeta_len -
				माप(काष्ठा line_header) - माप(crc));

	वापस crc;
पूर्ण

अटल अंतरभूत u32 pblk_calc_emeta_crc(काष्ठा pblk *pblk,
				      काष्ठा line_emeta *emeta)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	u32 crc = ~(u32)0;

	crc = crc32_le(crc, (अचिन्हित अक्षर *)emeta +
				माप(काष्ठा line_header) + माप(crc),
				lm->emeta_len[0] -
				माप(काष्ठा line_header) - माप(crc));

	वापस crc;
पूर्ण

अटल अंतरभूत पूर्णांक pblk_io_aligned(काष्ठा pblk *pblk, पूर्णांक nr_secs)
अणु
	वापस !(nr_secs % pblk->min_ग_लिखो_pgs);
पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
अटल अंतरभूत व्योम prपूर्णांक_ppa(काष्ठा pblk *pblk, काष्ठा ppa_addr *p,
			     अक्षर *msg, पूर्णांक error)
अणु
	काष्ठा nvm_geo *geo = &pblk->dev->geo;

	अगर (p->c.is_cached) अणु
		pblk_err(pblk, "ppa: (%s: %x) cache line: %llu\n",
				msg, error, (u64)p->c.line);
	पूर्ण अन्यथा अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		pblk_err(pblk, "ppa: (%s: %x):ch:%d,lun:%d,blk:%d,pg:%d,pl:%d,sec:%d\n",
			msg, error,
			p->g.ch, p->g.lun, p->g.blk,
			p->g.pg, p->g.pl, p->g.sec);
	पूर्ण अन्यथा अणु
		pblk_err(pblk, "ppa: (%s: %x):ch:%d,lun:%d,chk:%d,sec:%d\n",
			msg, error,
			p->m.grp, p->m.pu, p->m.chk, p->m.sec);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pblk_prपूर्णांक_failed_rqd(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
					 पूर्णांक error)
अणु
	पूर्णांक bit = -1;

	अगर (rqd->nr_ppas ==  1) अणु
		prपूर्णांक_ppa(pblk, &rqd->ppa_addr, "rqd", error);
		वापस;
	पूर्ण

	जबतक ((bit = find_next_bit((व्योम *)&rqd->ppa_status, rqd->nr_ppas,
						bit + 1)) < rqd->nr_ppas) अणु
		prपूर्णांक_ppa(pblk, &rqd->ppa_list[bit], "rqd", error);
	पूर्ण

	pblk_err(pblk, "error:%d, ppa_status:%llx\n", error, rqd->ppa_status);
पूर्ण

अटल अंतरभूत पूर्णांक pblk_boundary_ppa_checks(काष्ठा nvm_tgt_dev *tgt_dev,
				       काष्ठा ppa_addr *ppas, पूर्णांक nr_ppas)
अणु
	काष्ठा nvm_geo *geo = &tgt_dev->geo;
	काष्ठा ppa_addr *ppa;
	पूर्णांक i;

	क्रम (i = 0; i < nr_ppas; i++) अणु
		ppa = &ppas[i];

		अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
			अगर (!ppa->c.is_cached &&
					ppa->g.ch < geo->num_ch &&
					ppa->g.lun < geo->num_lun &&
					ppa->g.pl < geo->num_pln &&
					ppa->g.blk < geo->num_chk &&
					ppa->g.pg < geo->num_pg &&
					ppa->g.sec < geo->ws_min)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!ppa->c.is_cached &&
					ppa->m.grp < geo->num_ch &&
					ppa->m.pu < geo->num_lun &&
					ppa->m.chk < geo->num_chk &&
					ppa->m.sec < geo->clba)
				जारी;
		पूर्ण

		prपूर्णांक_ppa(tgt_dev->q->queuedata, ppa, "boundary", i);

		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pblk_check_io(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

	अगर (pblk_boundary_ppa_checks(dev, ppa_list, rqd->nr_ppas)) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (rqd->opcode == NVM_OP_PWRITE) अणु
		काष्ठा pblk_line *line;
		पूर्णांक i;

		क्रम (i = 0; i < rqd->nr_ppas; i++) अणु
			line = pblk_ppa_to_line(pblk, ppa_list[i]);

			spin_lock(&line->lock);
			अगर (line->state != PBLK_LINESTATE_OPEN) अणु
				pblk_err(pblk, "bad ppa: line:%d,state:%d\n",
							line->id, line->state);
				WARN_ON(1);
				spin_unlock(&line->lock);
				वापस -EINVAL;
			पूर्ण
			spin_unlock(&line->lock);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pblk_boundary_paddr_checks(काष्ठा pblk *pblk, u64 paddr)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;

	अगर (paddr > lm->sec_per_line)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pblk_get_bi_idx(काष्ठा bio *bio)
अणु
	वापस bio->bi_iter.bi_idx;
पूर्ण

अटल अंतरभूत sector_t pblk_get_lba(काष्ठा bio *bio)
अणु
	वापस bio->bi_iter.bi_sector / NR_PHY_IN_LOG;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pblk_get_secs(काष्ठा bio *bio)
अणु
	वापस  bio->bi_iter.bi_size / PBLK_EXPOSED_PAGE_SIZE;
पूर्ण

अटल अंतरभूत अक्षर *pblk_disk_name(काष्ठा pblk *pblk)
अणु
	काष्ठा gendisk *disk = pblk->disk;

	वापस disk->disk_name;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pblk_get_min_chks(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	/* In a worst-हाल scenario every line will have OP invalid sectors.
	 * We will then need a minimum of 1/OP lines to मुक्त up a single line
	 */

	वापस DIV_ROUND_UP(100, pblk->op) * lm->blk_per_line;
पूर्ण

अटल अंतरभूत काष्ठा pblk_sec_meta *pblk_get_meta(काष्ठा pblk *pblk,
							 व्योम *meta, पूर्णांक index)
अणु
	वापस meta +
	       max_t(पूर्णांक, माप(काष्ठा pblk_sec_meta), pblk->oob_meta_size)
	       * index;
पूर्ण

अटल अंतरभूत पूर्णांक pblk_dma_meta_size(काष्ठा pblk *pblk)
अणु
	वापस max_t(पूर्णांक, माप(काष्ठा pblk_sec_meta), pblk->oob_meta_size)
	       * NVM_MAX_VLBA;
पूर्ण

अटल अंतरभूत पूर्णांक pblk_is_oob_meta_supported(काष्ठा pblk *pblk)
अणु
	वापस pblk->oob_meta_size >= माप(काष्ठा pblk_sec_meta);
पूर्ण
#पूर्ण_अगर /* PBLK_H_ */
