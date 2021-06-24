<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vvvvvvvvvvvvvvvvvvvvvvv Original vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *  Copyright (C) 1992  Eric Youngdale
 *  Simulate a host adapter with 2 disks attached.  Do a lot of checking
 *  to make sure that we are not getting blocks mixed up, and PANIC अगर
 *  anything out of the ordinary is seen.
 * ^^^^^^^^^^^^^^^^^^^^^^^ Original ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * Copyright (C) 2001 - 2020 Douglas Gilbert
 *
 *  For करोcumentation see http://sg.danny.cz/sg/scsi_debug.hपंचांगl
 */


#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/genhd.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/crc-t10dअगर.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/atomic.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/uuid.h>
#समावेश <linux/t10-pi.h>
#समावेश <linux/msकरोs_partition.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/xarray.h>
#समावेश <linux/prefetch.h>

#समावेश <net/checksum.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsicam.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "sd.h"
#समावेश "scsi_logging.h"

/* make sure inq_product_rev string corresponds to this version */
#घोषणा SDEBUG_VERSION "0190"	/* क्रमmat to fit INQUIRY revision field */
अटल स्थिर अक्षर *sdebug_version_date = "20200710";

#घोषणा MY_NAME "scsi_debug"

/* Additional Sense Code (ASC) */
#घोषणा NO_ADDITIONAL_SENSE 0x0
#घोषणा LOGICAL_UNIT_NOT_READY 0x4
#घोषणा LOGICAL_UNIT_COMMUNICATION_FAILURE 0x8
#घोषणा UNRECOVERED_READ_ERR 0x11
#घोषणा PARAMETER_LIST_LENGTH_ERR 0x1a
#घोषणा INVALID_OPCODE 0x20
#घोषणा LBA_OUT_OF_RANGE 0x21
#घोषणा INVALID_FIELD_IN_CDB 0x24
#घोषणा INVALID_FIELD_IN_PARAM_LIST 0x26
#घोषणा WRITE_PROTECTED 0x27
#घोषणा UA_RESET_ASC 0x29
#घोषणा UA_CHANGED_ASC 0x2a
#घोषणा TARGET_CHANGED_ASC 0x3f
#घोषणा LUNS_CHANGED_ASCQ 0x0e
#घोषणा INSUFF_RES_ASC 0x55
#घोषणा INSUFF_RES_ASCQ 0x3
#घोषणा POWER_ON_RESET_ASCQ 0x0
#घोषणा BUS_RESET_ASCQ 0x2	/* scsi bus reset occurred */
#घोषणा MODE_CHANGED_ASCQ 0x1	/* mode parameters changed */
#घोषणा CAPACITY_CHANGED_ASCQ 0x9
#घोषणा SAVING_PARAMS_UNSUP 0x39
#घोषणा TRANSPORT_PROBLEM 0x4b
#घोषणा THRESHOLD_EXCEEDED 0x5d
#घोषणा LOW_POWER_COND_ON 0x5e
#घोषणा MISCOMPARE_VERIFY_ASC 0x1d
#घोषणा MICROCODE_CHANGED_ASCQ 0x1	/* with TARGET_CHANGED_ASC */
#घोषणा MICROCODE_CHANGED_WO_RESET_ASCQ 0x16
#घोषणा WRITE_ERROR_ASC 0xc
#घोषणा UNALIGNED_WRITE_ASCQ 0x4
#घोषणा WRITE_BOUNDARY_ASCQ 0x5
#घोषणा READ_INVDATA_ASCQ 0x6
#घोषणा READ_BOUNDARY_ASCQ 0x7
#घोषणा INSUFF_ZONE_ASCQ 0xe

/* Additional Sense Code Qualअगरier (ASCQ) */
#घोषणा ACK_NAK_TO 0x3

/* Default values क्रम driver parameters */
#घोषणा DEF_NUM_HOST   1
#घोषणा DEF_NUM_TGTS   1
#घोषणा DEF_MAX_LUNS   1
/* With these शेषs, this driver will make 1 host with 1 target
 * (id 0) containing 1 logical unit (lun 0). That is 1 device.
 */
#घोषणा DEF_ATO 1
#घोषणा DEF_CDB_LEN 10
#घोषणा DEF_JDELAY   1		/* अगर > 0 unit is a jअगरfy */
#घोषणा DEF_DEV_SIZE_PRE_INIT   0
#घोषणा DEF_DEV_SIZE_MB   8
#घोषणा DEF_ZBC_DEV_SIZE_MB   128
#घोषणा DEF_DIF 0
#घोषणा DEF_DIX 0
#घोषणा DEF_PER_HOST_STORE false
#घोषणा DEF_D_SENSE   0
#घोषणा DEF_EVERY_NTH   0
#घोषणा DEF_FAKE_RW	0
#घोषणा DEF_GUARD 0
#घोषणा DEF_HOST_LOCK 0
#घोषणा DEF_LBPU 0
#घोषणा DEF_LBPWS 0
#घोषणा DEF_LBPWS10 0
#घोषणा DEF_LBPRZ 1
#घोषणा DEF_LOWEST_ALIGNED 0
#घोषणा DEF_NDELAY   0		/* अगर > 0 unit is a nanosecond */
#घोषणा DEF_NO_LUN_0   0
#घोषणा DEF_NUM_PARTS   0
#घोषणा DEF_OPTS   0
#घोषणा DEF_OPT_BLKS 1024
#घोषणा DEF_PHYSBLK_EXP 0
#घोषणा DEF_OPT_XFERLEN_EXP 0
#घोषणा DEF_PTYPE   TYPE_DISK
#घोषणा DEF_RANDOM false
#घोषणा DEF_REMOVABLE false
#घोषणा DEF_SCSI_LEVEL   7    /* INQUIRY, byte2 [6->SPC-4; 7->SPC-5] */
#घोषणा DEF_SECTOR_SIZE 512
#घोषणा DEF_UNMAP_ALIGNMENT 0
#घोषणा DEF_UNMAP_GRANULARITY 1
#घोषणा DEF_UNMAP_MAX_BLOCKS 0xFFFFFFFF
#घोषणा DEF_UNMAP_MAX_DESC 256
#घोषणा DEF_VIRTUAL_GB   0
#घोषणा DEF_VPD_USE_HOSTNO 1
#घोषणा DEF_WRITESAME_LENGTH 0xFFFF
#घोषणा DEF_STRICT 0
#घोषणा DEF_STATISTICS false
#घोषणा DEF_SUBMIT_QUEUES 1
#घोषणा DEF_TUR_MS_TO_READY 0
#घोषणा DEF_UUID_CTL 0
#घोषणा JDELAY_OVERRIDDEN -9999

/* Default parameters क्रम ZBC drives */
#घोषणा DEF_ZBC_ZONE_SIZE_MB	128
#घोषणा DEF_ZBC_MAX_OPEN_ZONES	8
#घोषणा DEF_ZBC_NR_CONV_ZONES	1

#घोषणा SDEBUG_LUN_0_VAL 0

/* bit mask values क्रम sdebug_opts */
#घोषणा SDEBUG_OPT_NOISE		1
#घोषणा SDEBUG_OPT_MEDIUM_ERR		2
#घोषणा SDEBUG_OPT_TIMEOUT		4
#घोषणा SDEBUG_OPT_RECOVERED_ERR	8
#घोषणा SDEBUG_OPT_TRANSPORT_ERR	16
#घोषणा SDEBUG_OPT_DIF_ERR		32
#घोषणा SDEBUG_OPT_DIX_ERR		64
#घोषणा SDEBUG_OPT_MAC_TIMEOUT		128
#घोषणा SDEBUG_OPT_SHORT_TRANSFER	0x100
#घोषणा SDEBUG_OPT_Q_NOISE		0x200
#घोषणा SDEBUG_OPT_ALL_TSF		0x400
#घोषणा SDEBUG_OPT_RARE_TSF		0x800
#घोषणा SDEBUG_OPT_N_WCE		0x1000
#घोषणा SDEBUG_OPT_RESET_NOISE		0x2000
#घोषणा SDEBUG_OPT_NO_CDB_NOISE		0x4000
#घोषणा SDEBUG_OPT_HOST_BUSY		0x8000
#घोषणा SDEBUG_OPT_CMD_ABORT		0x10000
#घोषणा SDEBUG_OPT_ALL_NOISE (SDEBUG_OPT_NOISE | SDEBUG_OPT_Q_NOISE | \
			      SDEBUG_OPT_RESET_NOISE)
#घोषणा SDEBUG_OPT_ALL_INJECTING (SDEBUG_OPT_RECOVERED_ERR | \
				  SDEBUG_OPT_TRANSPORT_ERR | \
				  SDEBUG_OPT_DIF_ERR | SDEBUG_OPT_DIX_ERR | \
				  SDEBUG_OPT_SHORT_TRANSFER | \
				  SDEBUG_OPT_HOST_BUSY | \
				  SDEBUG_OPT_CMD_ABORT)
#घोषणा SDEBUG_OPT_RECOV_DIF_DIX (SDEBUG_OPT_RECOVERED_ERR | \
				  SDEBUG_OPT_DIF_ERR | SDEBUG_OPT_DIX_ERR)

/* As indicated in SAM-5 and SPC-4 Unit Attentions (UAs) are वापसed in
 * priority order. In the subset implemented here lower numbers have higher
 * priority. The UA numbers should be a sequence starting from 0 with
 * SDEBUG_NUM_UAS being 1 higher than the highest numbered UA. */
#घोषणा SDEBUG_UA_POR 0		/* Power on, reset, or bus device reset */
#घोषणा SDEBUG_UA_BUS_RESET 1
#घोषणा SDEBUG_UA_MODE_CHANGED 2
#घोषणा SDEBUG_UA_CAPACITY_CHANGED 3
#घोषणा SDEBUG_UA_LUNS_CHANGED 4
#घोषणा SDEBUG_UA_MICROCODE_CHANGED 5	/* simulate firmware change */
#घोषणा SDEBUG_UA_MICROCODE_CHANGED_WO_RESET 6
#घोषणा SDEBUG_NUM_UAS 7

/* when 1==SDEBUG_OPT_MEDIUM_ERR, a medium error is simulated at this
 * sector on पढ़ो commands: */
#घोषणा OPT_MEDIUM_ERR_ADDR   0x1234 /* that's sector 4660 in decimal */
#घोषणा OPT_MEDIUM_ERR_NUM    10     /* number of consecutive medium errs */

/* SDEBUG_CANQUEUE is the maximum number of commands that can be queued
 * (क्रम response) per submit queue at one समय. Can be reduced by max_queue
 * option. Command responses are not queued when jdelay=0 and ndelay=0. The
 * per-device DEF_CMD_PER_LUN can be changed via sysfs:
 * /sys/class/scsi_device/<h:c:t:l>/device/queue_depth
 * but cannot exceed SDEBUG_CANQUEUE .
 */
#घोषणा SDEBUG_CANQUEUE_WORDS  3	/* a WORD is bits in a दीर्घ */
#घोषणा SDEBUG_CANQUEUE  (SDEBUG_CANQUEUE_WORDS * BITS_PER_LONG)
#घोषणा DEF_CMD_PER_LUN  SDEBUG_CANQUEUE

/* UA - Unit Attention; SA - Service Action; SSU - Start Stop Unit */
#घोषणा F_D_IN			1	/* Data-in command (e.g. READ) */
#घोषणा F_D_OUT			2	/* Data-out command (e.g. WRITE) */
#घोषणा F_D_OUT_MAYBE		4	/* WRITE SAME, NDOB bit */
#घोषणा F_D_UNKN		8
#घोषणा F_RL_WLUN_OK		0x10	/* allowed with REPORT LUNS W-LUN */
#घोषणा F_SKIP_UA		0x20	/* bypass UAs (e.g. INQUIRY command) */
#घोषणा F_DELAY_OVERR		0x40	/* क्रम commands like INQUIRY */
#घोषणा F_SA_LOW		0x80	/* SA is in cdb byte 1, bits 4 to 0 */
#घोषणा F_SA_HIGH		0x100	/* SA is in cdb bytes 8 and 9 */
#घोषणा F_INV_OP		0x200	/* invalid opcode (not supported) */
#घोषणा F_FAKE_RW		0x400	/* bypass resp_*() when fake_rw set */
#घोषणा F_M_ACCESS		0x800	/* media access, reacts to SSU state */
#घोषणा F_SSU_DELAY		0x1000	/* SSU command delay (दीर्घ-ish) */
#घोषणा F_SYNC_DELAY		0x2000	/* SYNCHRONIZE CACHE delay */

/* Useful combinations of the above flags */
#घोषणा FF_RESPOND (F_RL_WLUN_OK | F_SKIP_UA | F_DELAY_OVERR)
#घोषणा FF_MEDIA_IO (F_M_ACCESS | F_FAKE_RW)
#घोषणा FF_SA (F_SA_HIGH | F_SA_LOW)
#घोषणा F_LONG_DELAY		(F_SSU_DELAY | F_SYNC_DELAY)

#घोषणा SDEBUG_MAX_PARTS 4

#घोषणा SDEBUG_MAX_CMD_LEN 32

#घोषणा SDEB_XA_NOT_IN_USE XA_MARK_1

/* Zone types (zbcr05 table 25) */
क्रमागत sdebug_z_type अणु
	ZBC_ZONE_TYPE_CNV	= 0x1,
	ZBC_ZONE_TYPE_SWR	= 0x2,
	ZBC_ZONE_TYPE_SWP	= 0x3,
पूर्ण;

/* क्रमागतeration names taken from table 26, zbcr05 */
क्रमागत sdebug_z_cond अणु
	ZBC_NOT_WRITE_POINTER	= 0x0,
	ZC1_EMPTY		= 0x1,
	ZC2_IMPLICIT_OPEN	= 0x2,
	ZC3_EXPLICIT_OPEN	= 0x3,
	ZC4_CLOSED		= 0x4,
	ZC6_READ_ONLY		= 0xd,
	ZC5_FULL		= 0xe,
	ZC7_OFFLINE		= 0xf,
पूर्ण;

काष्ठा sdeb_zone_state अणु	/* ZBC: per zone state */
	क्रमागत sdebug_z_type z_type;
	क्रमागत sdebug_z_cond z_cond;
	bool z_non_seq_resource;
	अचिन्हित पूर्णांक z_size;
	sector_t z_start;
	sector_t z_wp;
पूर्ण;

काष्ठा sdebug_dev_info अणु
	काष्ठा list_head dev_list;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक target;
	u64 lun;
	uuid_t lu_name;
	काष्ठा sdebug_host_info *sdbg_host;
	अचिन्हित दीर्घ uas_bm[1];
	atomic_t num_in_q;
	atomic_t stopped;	/* 1: by SSU, 2: device start */
	bool used;

	/* For ZBC devices */
	क्रमागत blk_zoned_model zmodel;
	अचिन्हित पूर्णांक zsize;
	अचिन्हित पूर्णांक zsize_shअगरt;
	अचिन्हित पूर्णांक nr_zones;
	अचिन्हित पूर्णांक nr_conv_zones;
	अचिन्हित पूर्णांक nr_imp_खोलो;
	अचिन्हित पूर्णांक nr_exp_खोलो;
	अचिन्हित पूर्णांक nr_बंदd;
	अचिन्हित पूर्णांक max_खोलो;
	kसमय_प्रकार create_ts;	/* समय since bootup that this device was created */
	काष्ठा sdeb_zone_state *zstate;
पूर्ण;

काष्ठा sdebug_host_info अणु
	काष्ठा list_head host_list;
	पूर्णांक si_idx;	/* sdeb_store_info (per host) xarray index */
	काष्ठा Scsi_Host *shost;
	काष्ठा device dev;
	काष्ठा list_head dev_info_list;
पूर्ण;

/* There is an xarray of poपूर्णांकers to this काष्ठा's objects, one per host */
काष्ठा sdeb_store_info अणु
	rwlock_t macc_lck;	/* क्रम atomic media access on this store */
	u8 *storep;		/* user data storage (ram) */
	काष्ठा t10_pi_tuple *dअगर_storep; /* protection info */
	व्योम *map_storep;	/* provisioning map */
पूर्ण;

#घोषणा to_sdebug_host(d)	\
	container_of(d, काष्ठा sdebug_host_info, dev)

क्रमागत sdeb_defer_type अणुSDEB_DEFER_NONE = 0, SDEB_DEFER_HRT = 1,
		      SDEB_DEFER_WQ = 2, SDEB_DEFER_POLL = 3पूर्ण;

काष्ठा sdebug_defer अणु
	काष्ठा hrसमयr hrt;
	काष्ठा execute_work ew;
	kसमय_प्रकार cmpl_ts;/* समय since boot to complete this cmd */
	पूर्णांक sqa_idx;	/* index of sdebug_queue array */
	पूर्णांक qc_idx;	/* index of sdebug_queued_cmd array within sqa_idx */
	पूर्णांक hc_idx;	/* hostwide tag index */
	पूर्णांक issuing_cpu;
	bool init_hrt;
	bool init_wq;
	bool init_poll;
	bool पातed;	/* true when blk_पात_request() alपढ़ोy called */
	क्रमागत sdeb_defer_type defer_t;
पूर्ण;

काष्ठा sdebug_queued_cmd अणु
	/* corresponding bit set in in_use_bm[] in owning काष्ठा sdebug_queue
	 * instance indicates this slot is in use.
	 */
	काष्ठा sdebug_defer *sd_dp;
	काष्ठा scsi_cmnd *a_cmnd;
पूर्ण;

काष्ठा sdebug_queue अणु
	काष्ठा sdebug_queued_cmd qc_arr[SDEBUG_CANQUEUE];
	अचिन्हित दीर्घ in_use_bm[SDEBUG_CANQUEUE_WORDS];
	spinlock_t qc_lock;
	atomic_t blocked;	/* to temporarily stop more being queued */
पूर्ण;

अटल atomic_t sdebug_cmnd_count;   /* number of incoming commands */
अटल atomic_t sdebug_completions;  /* count of deferred completions */
अटल atomic_t sdebug_miss_cpus;    /* submission + completion cpus dअगरfer */
अटल atomic_t sdebug_a_tsf;	     /* 'almost task set full' counter */
अटल atomic_t sdeb_inject_pending;
अटल atomic_t sdeb_mq_poll_count;  /* bumped when mq_poll वापसs > 0 */

काष्ठा opcode_info_t अणु
	u8 num_attached;	/* 0 अगर this is it (i.e. a leaf); use 0xff */
				/* क्रम terminating element */
	u8 opcode;		/* अगर num_attached > 0, preferred */
	u16 sa;			/* service action */
	u32 flags;		/* OR-ed set of SDEB_F_* */
	पूर्णांक (*pfp)(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
	स्थिर काष्ठा opcode_info_t *arrp;  /* num_attached elements or शून्य */
	u8 len_mask[16];	/* len_mask[0]-->cdb_len, then mask क्रम cdb */
				/* 1 to min(cdb_len, 15); ignore cdb[15...] */
पूर्ण;

/* SCSI opcodes (first byte of cdb) of पूर्णांकerest mapped onto these indexes */
क्रमागत sdeb_opcode_index अणु
	SDEB_I_INVALID_OPCODE =	0,
	SDEB_I_INQUIRY = 1,
	SDEB_I_REPORT_LUNS = 2,
	SDEB_I_REQUEST_SENSE = 3,
	SDEB_I_TEST_UNIT_READY = 4,
	SDEB_I_MODE_SENSE = 5,		/* 6, 10 */
	SDEB_I_MODE_SELECT = 6,		/* 6, 10 */
	SDEB_I_LOG_SENSE = 7,
	SDEB_I_READ_CAPACITY = 8,	/* 10; 16 is in SA_IN(16) */
	SDEB_I_READ = 9,		/* 6, 10, 12, 16 */
	SDEB_I_WRITE = 10,		/* 6, 10, 12, 16 */
	SDEB_I_START_STOP = 11,
	SDEB_I_SERV_ACT_IN_16 = 12,	/* add ...SERV_ACT_IN_12 अगर needed */
	SDEB_I_SERV_ACT_OUT_16 = 13,	/* add ...SERV_ACT_OUT_12 अगर needed */
	SDEB_I_MAINT_IN = 14,
	SDEB_I_MAINT_OUT = 15,
	SDEB_I_VERIFY = 16,		/* VERIFY(10), VERIFY(16) */
	SDEB_I_VARIABLE_LEN = 17,	/* READ(32), WRITE(32), WR_SCAT(32) */
	SDEB_I_RESERVE = 18,		/* 6, 10 */
	SDEB_I_RELEASE = 19,		/* 6, 10 */
	SDEB_I_ALLOW_REMOVAL = 20,	/* PREVENT ALLOW MEDIUM REMOVAL */
	SDEB_I_REZERO_UNIT = 21,	/* REWIND in SSC */
	SDEB_I_ATA_PT = 22,		/* 12, 16 */
	SDEB_I_SEND_DIAG = 23,
	SDEB_I_UNMAP = 24,
	SDEB_I_WRITE_BUFFER = 25,
	SDEB_I_WRITE_SAME = 26,		/* 10, 16 */
	SDEB_I_SYNC_CACHE = 27,		/* 10, 16 */
	SDEB_I_COMP_WRITE = 28,
	SDEB_I_PRE_FETCH = 29,		/* 10, 16 */
	SDEB_I_ZONE_OUT = 30,		/* 0x94+SA; includes no data xfer */
	SDEB_I_ZONE_IN = 31,		/* 0x95+SA; all have data-in */
	SDEB_I_LAST_ELEM_P1 = 32,	/* keep this last (previous + 1) */
पूर्ण;


अटल स्थिर अचिन्हित अक्षर opcode_ind_arr[256] = अणु
/* 0x0; 0x0->0x1f: 6 byte cdbs */
	SDEB_I_TEST_UNIT_READY, SDEB_I_REZERO_UNIT, 0, SDEB_I_REQUEST_SENSE,
	    0, 0, 0, 0,
	SDEB_I_READ, 0, SDEB_I_WRITE, 0, 0, 0, 0, 0,
	0, 0, SDEB_I_INQUIRY, 0, 0, SDEB_I_MODE_SELECT, SDEB_I_RESERVE,
	    SDEB_I_RELEASE,
	0, 0, SDEB_I_MODE_SENSE, SDEB_I_START_STOP, 0, SDEB_I_SEND_DIAG,
	    SDEB_I_ALLOW_REMOVAL, 0,
/* 0x20; 0x20->0x3f: 10 byte cdbs */
	0, 0, 0, 0, 0, SDEB_I_READ_CAPACITY, 0, 0,
	SDEB_I_READ, 0, SDEB_I_WRITE, 0, 0, 0, 0, SDEB_I_VERIFY,
	0, 0, 0, 0, SDEB_I_PRE_FETCH, SDEB_I_SYNC_CACHE, 0, 0,
	0, 0, 0, SDEB_I_WRITE_BUFFER, 0, 0, 0, 0,
/* 0x40; 0x40->0x5f: 10 byte cdbs */
	0, SDEB_I_WRITE_SAME, SDEB_I_UNMAP, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, SDEB_I_LOG_SENSE, 0, 0,
	0, 0, 0, 0, 0, SDEB_I_MODE_SELECT, SDEB_I_RESERVE,
	    SDEB_I_RELEASE,
	0, 0, SDEB_I_MODE_SENSE, 0, 0, 0, 0, 0,
/* 0x60; 0x60->0x7d are reserved, 0x7e is "extended cdb" */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, SDEB_I_VARIABLE_LEN,
/* 0x80; 0x80->0x9f: 16 byte cdbs */
	0, 0, 0, 0, 0, SDEB_I_ATA_PT, 0, 0,
	SDEB_I_READ, SDEB_I_COMP_WRITE, SDEB_I_WRITE, 0,
	0, 0, 0, SDEB_I_VERIFY,
	SDEB_I_PRE_FETCH, SDEB_I_SYNC_CACHE, 0, SDEB_I_WRITE_SAME,
	SDEB_I_ZONE_OUT, SDEB_I_ZONE_IN, 0, 0,
	0, 0, 0, 0, 0, 0, SDEB_I_SERV_ACT_IN_16, SDEB_I_SERV_ACT_OUT_16,
/* 0xa0; 0xa0->0xbf: 12 byte cdbs */
	SDEB_I_REPORT_LUNS, SDEB_I_ATA_PT, 0, SDEB_I_MAINT_IN,
	     SDEB_I_MAINT_OUT, 0, 0, 0,
	SDEB_I_READ, 0 /* SDEB_I_SERV_ACT_OUT_12 */, SDEB_I_WRITE,
	     0 /* SDEB_I_SERV_ACT_IN_12 */, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
/* 0xc0; 0xc0->0xff: venकरोr specअगरic */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
पूर्ण;

/*
 * The following "response" functions वापस the SCSI mid-level's 4 byte
 * tuple-in-an-पूर्णांक. To handle commands with an IMMED bit, क्रम a faster
 * command completion, they can mask their वापस value with
 * SDEG_RES_IMMED_MASK .
 */
#घोषणा SDEG_RES_IMMED_MASK 0x40000000

अटल पूर्णांक resp_inquiry(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_report_luns(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_requests(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_mode_sense(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_mode_select(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_log_sense(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_पढ़ोcap(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_पढ़ो_dt0(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_ग_लिखो_dt0(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_ग_लिखो_scat(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_start_stop(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_पढ़ोcap16(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_get_lba_status(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_report_tgtpgs(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_unmap(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_rsup_opcodes(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_rsup_पंचांगfs(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_verअगरy(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_ग_लिखो_same_10(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_ग_लिखो_same_16(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_comp_ग_लिखो(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_ग_लिखो_buffer(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_sync_cache(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_pre_fetch(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_report_zones(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_खोलो_zone(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_बंद_zone(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_finish_zone(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
अटल पूर्णांक resp_rwp_zone(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);

अटल पूर्णांक sdebug_करो_add_host(bool mk_new_store);
अटल पूर्णांक sdebug_add_host_helper(पूर्णांक per_host_idx);
अटल व्योम sdebug_करो_हटाओ_host(bool the_end);
अटल पूर्णांक sdebug_add_store(व्योम);
अटल व्योम sdebug_erase_store(पूर्णांक idx, काष्ठा sdeb_store_info *sip);
अटल व्योम sdebug_erase_all_stores(bool apart_from_first);

/*
 * The following are overflow arrays क्रम cdbs that "hit" the same index in
 * the opcode_info_arr array. The most समय sensitive (or commonly used) cdb
 * should be placed in opcode_info_arr[], the others should be placed here.
 */
अटल स्थिर काष्ठा opcode_info_t msense_iarr[] = अणु
	अणु0, 0x1a, 0, F_D_IN, शून्य, शून्य,
	    अणु6,  0xe8, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t mselect_iarr[] = अणु
	अणु0, 0x15, 0, F_D_OUT, शून्य, शून्य,
	    अणु6,  0xf1, 0, 0, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t पढ़ो_iarr[] = अणु
	अणु0, 0x28, 0, F_D_IN | FF_MEDIA_IO, resp_पढ़ो_dt0, शून्य,/* READ(10) */
	    अणु10,  0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x8, 0, F_D_IN | FF_MEDIA_IO, resp_पढ़ो_dt0, शून्य, /* READ(6) */
	    अणु6,  0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0xa8, 0, F_D_IN | FF_MEDIA_IO, resp_पढ़ो_dt0, शून्य,/* READ(12) */
	    अणु12,  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf,
	     0xc7, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t ग_लिखो_iarr[] = अणु
	अणु0, 0x2a, 0, F_D_OUT | FF_MEDIA_IO, resp_ग_लिखो_dt0,  /* WRITE(10) */
	    शून्य, अणु10,  0xfb, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7,
		   0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0xa, 0, F_D_OUT | FF_MEDIA_IO, resp_ग_लिखो_dt0,   /* WRITE(6) */
	    शून्य, अणु6,  0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0,
		   0, 0, 0पूर्ण पूर्ण,
	अणु0, 0xaa, 0, F_D_OUT | FF_MEDIA_IO, resp_ग_लिखो_dt0,  /* WRITE(12) */
	    शून्य, अणु12,  0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		   0xbf, 0xc7, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t verअगरy_iarr[] = अणु
	अणु0, 0x2f, 0, F_D_OUT_MAYBE | FF_MEDIA_IO, resp_verअगरy,/* VERIFY(10) */
	    शून्य, अणु10,  0xf7, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xc7,
		   0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t sa_in_16_iarr[] = अणु
	अणु0, 0x9e, 0x12, F_SA_LOW | F_D_IN, resp_get_lba_status, शून्य,
	    अणु16,  0x12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0, 0xc7पूर्ण पूर्ण,	/* GET LBA STATUS(16) */
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t vl_iarr[] = अणु	/* VARIABLE LENGTH */
	अणु0, 0x7f, 0xb, F_SA_HIGH | F_D_OUT | FF_MEDIA_IO, resp_ग_लिखो_dt0,
	    शून्य, अणु32,  0xc7, 0, 0, 0, 0, 0x3f, 0x18, 0x0, 0xb, 0xfa,
		   0, 0xff, 0xff, 0xff, 0xffपूर्ण पूर्ण,	/* WRITE(32) */
	अणु0, 0x7f, 0x11, F_SA_HIGH | F_D_OUT | FF_MEDIA_IO, resp_ग_लिखो_scat,
	    शून्य, अणु32,  0xc7, 0, 0, 0, 0, 0x3f, 0x18, 0x0, 0x11, 0xf8,
		   0, 0xff, 0xff, 0x0, 0x0पूर्ण पूर्ण,	/* WRITE SCATTERED(32) */
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t मुख्यt_in_iarr[] = अणु	/* MAINT IN */
	अणु0, 0xa3, 0xc, F_SA_LOW | F_D_IN, resp_rsup_opcodes, शून्य,
	    अणु12,  0xc, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0,
	     0xc7, 0, 0, 0, 0पूर्ण पूर्ण, /* REPORT SUPPORTED OPERATION CODES */
	अणु0, 0xa3, 0xd, F_SA_LOW | F_D_IN, resp_rsup_पंचांगfs, शून्य,
	    अणु12,  0xd, 0x80, 0, 0, 0, 0xff, 0xff, 0xff, 0xff, 0, 0xc7, 0, 0,
	     0, 0पूर्ण पूर्ण,	/* REPORTED SUPPORTED TASK MANAGEMENT FUNCTIONS */
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t ग_लिखो_same_iarr[] = अणु
	अणु0, 0x93, 0, F_D_OUT_MAYBE | FF_MEDIA_IO, resp_ग_लिखो_same_16, शून्य,
	    अणु16,  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0x3f, 0xc7पूर्ण पूर्ण,		/* WRITE SAME(16) */
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t reserve_iarr[] = अणु
	अणु0, 0x16, 0, F_D_OUT, शून्य, शून्य,		/* RESERVE(6) */
	    अणु6,  0x1f, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t release_iarr[] = अणु
	अणु0, 0x17, 0, F_D_OUT, शून्य, शून्य,		/* RELEASE(6) */
	    अणु6,  0x1f, 0xff, 0, 0, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t sync_cache_iarr[] = अणु
	अणु0, 0x91, 0, F_SYNC_DELAY | F_M_ACCESS, resp_sync_cache, शून्य,
	    अणु16,  0x6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7पूर्ण पूर्ण,	/* SYNC_CACHE (16) */
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t pre_fetch_iarr[] = अणु
	अणु0, 0x90, 0, F_SYNC_DELAY | FF_MEDIA_IO, resp_pre_fetch, शून्य,
	    अणु16,  0x2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7पूर्ण पूर्ण,	/* PRE-FETCH (16) */
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t zone_out_iarr[] = अणु	/* ZONE OUT(16) */
	अणु0, 0x94, 0x1, F_SA_LOW | F_M_ACCESS, resp_बंद_zone, शून्य,
	    अणु16, 0x1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0, 0, 0xff, 0xff, 0x1, 0xc7पूर्ण पूर्ण,	/* CLOSE ZONE */
	अणु0, 0x94, 0x2, F_SA_LOW | F_M_ACCESS, resp_finish_zone, शून्य,
	    अणु16, 0x2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0, 0, 0xff, 0xff, 0x1, 0xc7पूर्ण पूर्ण,	/* FINISH ZONE */
	अणु0, 0x94, 0x4, F_SA_LOW | F_M_ACCESS, resp_rwp_zone, शून्य,
	    अणु16, 0x4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0, 0, 0xff, 0xff, 0x1, 0xc7पूर्ण पूर्ण,  /* RESET WRITE POINTER */
पूर्ण;

अटल स्थिर काष्ठा opcode_info_t zone_in_iarr[] = अणु	/* ZONE IN(16) */
	अणु0, 0x95, 0x6, F_SA_LOW | F_D_IN | F_M_ACCESS, शून्य, शून्य,
	    अणु16, 0x6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7पूर्ण पूर्ण, /* REPORT ZONES */
पूर्ण;


/* This array is accessed via SDEB_I_* values. Make sure all are mapped,
 * plus the terminating elements क्रम logic that scans this table such as
 * REPORT SUPPORTED OPERATION CODES. */
अटल स्थिर काष्ठा opcode_info_t opcode_info_arr[SDEB_I_LAST_ELEM_P1 + 1] = अणु
/* 0 */
	अणु0, 0, 0, F_INV_OP | FF_RESPOND, शून्य, शून्य,	/* unknown opcodes */
	    अणु0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x12, 0, FF_RESPOND | F_D_IN, resp_inquiry, शून्य, /* INQUIRY */
	    अणु6,  0xe3, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0xa0, 0, FF_RESPOND | F_D_IN, resp_report_luns, शून्य,
	    अणु12,  0xe3, 0xff, 0, 0, 0, 0xff, 0xff, 0xff, 0xff, 0, 0xc7, 0, 0,
	     0, 0पूर्ण पूर्ण,					/* REPORT LUNS */
	अणु0, 0x3, 0, FF_RESPOND | F_D_IN, resp_requests, शून्य,
	    अणु6,  0xe1, 0, 0, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x0, 0, F_M_ACCESS | F_RL_WLUN_OK, शून्य, शून्य,/* TEST UNIT READY */
	    अणु6,  0, 0, 0, 0, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
/* 5 */
	अणुARRAY_SIZE(msense_iarr), 0x5a, 0, F_D_IN,	/* MODE SENSE(10) */
	    resp_mode_sense, msense_iarr, अणु10,  0xf8, 0xff, 0xff, 0, 0, 0,
		0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणुARRAY_SIZE(mselect_iarr), 0x55, 0, F_D_OUT,	/* MODE SELECT(10) */
	    resp_mode_select, mselect_iarr, अणु10,  0xf1, 0, 0, 0, 0, 0, 0xff,
		0xff, 0xc7, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x4d, 0, F_D_IN, resp_log_sense, शून्य,	/* LOG SENSE */
	    अणु10,  0xe3, 0xff, 0xff, 0, 0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0,
	     0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x25, 0, F_D_IN, resp_पढ़ोcap, शून्य,    /* READ CAPACITY(10) */
	    अणु10,  0xe1, 0xff, 0xff, 0xff, 0xff, 0, 0, 0x1, 0xc7, 0, 0, 0, 0,
	     0, 0पूर्ण पूर्ण,
	अणुARRAY_SIZE(पढ़ो_iarr), 0x88, 0, F_D_IN | FF_MEDIA_IO, /* READ(16) */
	    resp_पढ़ो_dt0, पढ़ो_iarr, अणु16,  0xfe, 0xff, 0xff, 0xff, 0xff,
	    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7पूर्ण पूर्ण,
/* 10 */
	अणुARRAY_SIZE(ग_लिखो_iarr), 0x8a, 0, F_D_OUT | FF_MEDIA_IO,
	    resp_ग_लिखो_dt0, ग_लिखो_iarr,			/* WRITE(16) */
		अणु16,  0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7पूर्ण पूर्ण,
	अणु0, 0x1b, 0, F_SSU_DELAY, resp_start_stop, शून्य,/* START STOP UNIT */
	    अणु6,  0x1, 0, 0xf, 0xf7, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणुARRAY_SIZE(sa_in_16_iarr), 0x9e, 0x10, F_SA_LOW | F_D_IN,
	    resp_पढ़ोcap16, sa_in_16_iarr, /* SA_IN(16), READ CAPACITY(16) */
		अणु16,  0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0xff, 0xff, 0x1, 0xc7पूर्ण पूर्ण,
	अणु0, 0x9f, 0x12, F_SA_LOW | F_D_OUT | FF_MEDIA_IO, resp_ग_लिखो_scat,
	    शून्य, अणु16,  0x12, 0xf9, 0x0, 0xff, 0xff, 0, 0, 0xff, 0xff, 0xff,
	    0xff, 0xff, 0xff, 0xff, 0xc7पूर्ण पूर्ण,  /* SA_OUT(16), WRITE SCAT(16) */
	अणुARRAY_SIZE(मुख्यt_in_iarr), 0xa3, 0xa, F_SA_LOW | F_D_IN,
	    resp_report_tgtpgs,	/* MAINT IN, REPORT TARGET PORT GROUPS */
		मुख्यt_in_iarr, अणु12,  0xea, 0, 0, 0, 0, 0xff, 0xff, 0xff,
				0xff, 0, 0xc7, 0, 0, 0, 0पूर्ण पूर्ण,
/* 15 */
	अणु0, 0, 0, F_INV_OP | FF_RESPOND, शून्य, शून्य, /* MAINT OUT */
	    अणु0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणुARRAY_SIZE(verअगरy_iarr), 0x8f, 0,
	    F_D_OUT_MAYBE | FF_MEDIA_IO, resp_verअगरy,	/* VERIFY(16) */
	    verअगरy_iarr, अणु16,  0xf6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7पूर्ण पूर्ण,
	अणुARRAY_SIZE(vl_iarr), 0x7f, 0x9, F_SA_HIGH | F_D_IN | FF_MEDIA_IO,
	    resp_पढ़ो_dt0, vl_iarr,	/* VARIABLE LENGTH, READ(32) */
	    अणु32,  0xc7, 0, 0, 0, 0, 0x3f, 0x18, 0x0, 0x9, 0xfe, 0, 0xff, 0xff,
	     0xff, 0xffपूर्ण पूर्ण,
	अणुARRAY_SIZE(reserve_iarr), 0x56, 0, F_D_OUT,
	    शून्य, reserve_iarr,	/* RESERVE(10) <no response function> */
	    अणु10,  0xff, 0xff, 0xff, 0, 0, 0, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0,
	     0पूर्ण पूर्ण,
	अणुARRAY_SIZE(release_iarr), 0x57, 0, F_D_OUT,
	    शून्य, release_iarr, /* RELEASE(10) <no response function> */
	    अणु10,  0x13, 0xff, 0xff, 0, 0, 0, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0,
	     0पूर्ण पूर्ण,
/* 20 */
	अणु0, 0x1e, 0, 0, शून्य, शून्य, /* ALLOW REMOVAL */
	    अणु6,  0, 0, 0, 0x3, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x1, 0, 0, resp_start_stop, शून्य, /* REWIND ?? */
	    अणु6,  0x1, 0, 0, 0, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0, 0, F_INV_OP | FF_RESPOND, शून्य, शून्य, /* ATA_PT */
	    अणु0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x1d, F_D_OUT, 0, शून्य, शून्य,	/* SEND DIAGNOSTIC */
	    अणु6,  0xf7, 0, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु0, 0x42, 0, F_D_OUT | FF_MEDIA_IO, resp_unmap, शून्य, /* UNMAP */
	    अणु10,  0x1, 0, 0, 0, 0, 0x3f, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
/* 25 */
	अणु0, 0x3b, 0, F_D_OUT_MAYBE, resp_ग_लिखो_buffer, शून्य,
	    अणु10,  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0पूर्ण पूर्ण,			/* WRITE_BUFFER */
	अणुARRAY_SIZE(ग_लिखो_same_iarr), 0x41, 0, F_D_OUT_MAYBE | FF_MEDIA_IO,
	    resp_ग_लिखो_same_10, ग_लिखो_same_iarr,	/* WRITE SAME(10) */
		अणु10,  0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0,
		 0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणुARRAY_SIZE(sync_cache_iarr), 0x35, 0, F_SYNC_DELAY | F_M_ACCESS,
	    resp_sync_cache, sync_cache_iarr,
	    अणु10,  0x7, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0पूर्ण पूर्ण,			/* SYNC_CACHE (10) */
	अणु0, 0x89, 0, F_D_OUT | FF_MEDIA_IO, resp_comp_ग_लिखो, शून्य,
	    अणु16,  0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0,
	     0, 0xff, 0x3f, 0xc7पूर्ण पूर्ण,		/* COMPARE AND WRITE */
	अणुARRAY_SIZE(pre_fetch_iarr), 0x34, 0, F_SYNC_DELAY | FF_MEDIA_IO,
	    resp_pre_fetch, pre_fetch_iarr,
	    अणु10,  0x2, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0पूर्ण पूर्ण,			/* PRE-FETCH (10) */

/* 30 */
	अणुARRAY_SIZE(zone_out_iarr), 0x94, 0x3, F_SA_LOW | F_M_ACCESS,
	    resp_खोलो_zone, zone_out_iarr, /* ZONE_OUT(16), OPEN ZONE) */
		अणु16,  0x3 /* SA */, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x1, 0xc7पूर्ण पूर्ण,
	अणुARRAY_SIZE(zone_in_iarr), 0x95, 0x0, F_SA_LOW | F_M_ACCESS,
	    resp_report_zones, zone_in_iarr, /* ZONE_IN(16), REPORT ZONES) */
		अणु16,  0x0 /* SA */, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xc7पूर्ण पूर्ण,
/* sentinel */
	अणु0xff, 0, 0, 0, शून्य, शून्य,		/* terminating element */
	    अणु0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक sdebug_num_hosts;
अटल पूर्णांक sdebug_add_host = DEF_NUM_HOST;  /* in sysfs this is relative */
अटल पूर्णांक sdebug_ato = DEF_ATO;
अटल पूर्णांक sdebug_cdb_len = DEF_CDB_LEN;
अटल पूर्णांक sdebug_jdelay = DEF_JDELAY;	/* अगर > 0 then unit is jअगरfies */
अटल पूर्णांक sdebug_dev_size_mb = DEF_DEV_SIZE_PRE_INIT;
अटल पूर्णांक sdebug_dअगर = DEF_DIF;
अटल पूर्णांक sdebug_dix = DEF_DIX;
अटल पूर्णांक sdebug_dsense = DEF_D_SENSE;
अटल पूर्णांक sdebug_every_nth = DEF_EVERY_NTH;
अटल पूर्णांक sdebug_fake_rw = DEF_FAKE_RW;
अटल अचिन्हित पूर्णांक sdebug_guard = DEF_GUARD;
अटल पूर्णांक sdebug_host_max_queue;	/* per host */
अटल पूर्णांक sdebug_lowest_aligned = DEF_LOWEST_ALIGNED;
अटल पूर्णांक sdebug_max_luns = DEF_MAX_LUNS;
अटल पूर्णांक sdebug_max_queue = SDEBUG_CANQUEUE;	/* per submit queue */
अटल अचिन्हित पूर्णांक sdebug_medium_error_start = OPT_MEDIUM_ERR_ADDR;
अटल पूर्णांक sdebug_medium_error_count = OPT_MEDIUM_ERR_NUM;
अटल atomic_t retired_max_queue;	/* अगर > 0 then was prior max_queue */
अटल पूर्णांक sdebug_ndelay = DEF_NDELAY;	/* अगर > 0 then unit is nanoseconds */
अटल पूर्णांक sdebug_no_lun_0 = DEF_NO_LUN_0;
अटल पूर्णांक sdebug_no_uld;
अटल पूर्णांक sdebug_num_parts = DEF_NUM_PARTS;
अटल पूर्णांक sdebug_num_tgts = DEF_NUM_TGTS; /* tarमाला_लो per host */
अटल पूर्णांक sdebug_opt_blks = DEF_OPT_BLKS;
अटल पूर्णांक sdebug_opts = DEF_OPTS;
अटल पूर्णांक sdebug_physblk_exp = DEF_PHYSBLK_EXP;
अटल पूर्णांक sdebug_opt_xferlen_exp = DEF_OPT_XFERLEN_EXP;
अटल पूर्णांक sdebug_ptype = DEF_PTYPE; /* SCSI peripheral device type */
अटल पूर्णांक sdebug_scsi_level = DEF_SCSI_LEVEL;
अटल पूर्णांक sdebug_sector_size = DEF_SECTOR_SIZE;
अटल पूर्णांक sdeb_tur_ms_to_पढ़ोy = DEF_TUR_MS_TO_READY;
अटल पूर्णांक sdebug_भव_gb = DEF_VIRTUAL_GB;
अटल पूर्णांक sdebug_vpd_use_hostno = DEF_VPD_USE_HOSTNO;
अटल अचिन्हित पूर्णांक sdebug_lbpu = DEF_LBPU;
अटल अचिन्हित पूर्णांक sdebug_lbpws = DEF_LBPWS;
अटल अचिन्हित पूर्णांक sdebug_lbpws10 = DEF_LBPWS10;
अटल अचिन्हित पूर्णांक sdebug_lbprz = DEF_LBPRZ;
अटल अचिन्हित पूर्णांक sdebug_unmap_alignment = DEF_UNMAP_ALIGNMENT;
अटल अचिन्हित पूर्णांक sdebug_unmap_granularity = DEF_UNMAP_GRANULARITY;
अटल अचिन्हित पूर्णांक sdebug_unmap_max_blocks = DEF_UNMAP_MAX_BLOCKS;
अटल अचिन्हित पूर्णांक sdebug_unmap_max_desc = DEF_UNMAP_MAX_DESC;
अटल अचिन्हित पूर्णांक sdebug_ग_लिखो_same_length = DEF_WRITESAME_LENGTH;
अटल पूर्णांक sdebug_uuid_ctl = DEF_UUID_CTL;
अटल bool sdebug_अक्रमom = DEF_RANDOM;
अटल bool sdebug_per_host_store = DEF_PER_HOST_STORE;
अटल bool sdebug_removable = DEF_REMOVABLE;
अटल bool sdebug_clustering;
अटल bool sdebug_host_lock = DEF_HOST_LOCK;
अटल bool sdebug_strict = DEF_STRICT;
अटल bool sdebug_any_injecting_opt;
अटल bool sdebug_verbose;
अटल bool have_dअगर_prot;
अटल bool ग_लिखो_since_sync;
अटल bool sdebug_statistics = DEF_STATISTICS;
अटल bool sdebug_wp;
/* Following क्रमागत: 0: no zbc, def; 1: host aware; 2: host managed */
अटल क्रमागत blk_zoned_model sdeb_zbc_model = BLK_ZONED_NONE;
अटल अक्षर *sdeb_zbc_model_s;

क्रमागत sam_lun_addr_method अणुSAM_LUN_AM_PERIPHERAL = 0x0,
			  SAM_LUN_AM_FLAT = 0x1,
			  SAM_LUN_AM_LOGICAL_UNIT = 0x2,
			  SAM_LUN_AM_EXTENDED = 0x3पूर्ण;
अटल क्रमागत sam_lun_addr_method sdebug_lun_am = SAM_LUN_AM_PERIPHERAL;
अटल पूर्णांक sdebug_lun_am_i = (पूर्णांक)SAM_LUN_AM_PERIPHERAL;

अटल अचिन्हित पूर्णांक sdebug_store_sectors;
अटल sector_t sdebug_capacity;	/* in sectors */

/* old BIOS stuff, kernel may get rid of them but some mode sense pages
   may still need them */
अटल पूर्णांक sdebug_heads;		/* heads per disk */
अटल पूर्णांक sdebug_cylinders_per;	/* cylinders per surface */
अटल पूर्णांक sdebug_sectors_per;		/* sectors per cylinder */

अटल LIST_HEAD(sdebug_host_list);
अटल DEFINE_SPINLOCK(sdebug_host_list_lock);

अटल काष्ठा xarray per_store_arr;
अटल काष्ठा xarray *per_store_ap = &per_store_arr;
अटल पूर्णांक sdeb_first_idx = -1;		/* invalid index ==> none created */
अटल पूर्णांक sdeb_most_recent_idx = -1;
अटल DEFINE_RWLOCK(sdeb_fake_rw_lck);	/* need a RW lock when fake_rw=1 */

अटल अचिन्हित दीर्घ map_size;
अटल पूर्णांक num_पातs;
अटल पूर्णांक num_dev_resets;
अटल पूर्णांक num_target_resets;
अटल पूर्णांक num_bus_resets;
अटल पूर्णांक num_host_resets;
अटल पूर्णांक dix_ग_लिखोs;
अटल पूर्णांक dix_पढ़ोs;
अटल पूर्णांक dअगर_errors;

/* ZBC global data */
अटल bool sdeb_zbc_in_use;	/* true क्रम host-aware and host-managed disks */
अटल पूर्णांक sdeb_zbc_zone_size_mb;
अटल पूर्णांक sdeb_zbc_max_खोलो = DEF_ZBC_MAX_OPEN_ZONES;
अटल पूर्णांक sdeb_zbc_nr_conv = DEF_ZBC_NR_CONV_ZONES;

अटल पूर्णांक submit_queues = DEF_SUBMIT_QUEUES;  /* > 1 क्रम multi-queue (mq) */
अटल पूर्णांक poll_queues; /* iouring iopoll पूर्णांकerface.*/
अटल काष्ठा sdebug_queue *sdebug_q_arr;  /* ptr to array of submit queues */

अटल DEFINE_RWLOCK(atomic_rw);
अटल DEFINE_RWLOCK(atomic_rw2);

अटल rwlock_t *ramdisk_lck_a[2];

अटल अक्षर sdebug_proc_name[] = MY_NAME;
अटल स्थिर अक्षर *my_name = MY_NAME;

अटल काष्ठा bus_type pseuकरो_lld_bus;

अटल काष्ठा device_driver sdebug_driverfs_driver = अणु
	.name 		= sdebug_proc_name,
	.bus		= &pseuकरो_lld_bus,
पूर्ण;

अटल स्थिर पूर्णांक check_condition_result =
		(DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

अटल स्थिर पूर्णांक illegal_condition_result =
	(DRIVER_SENSE << 24) | (DID_ABORT << 16) | SAM_STAT_CHECK_CONDITION;

अटल स्थिर पूर्णांक device_qfull_result =
	(DID_OK << 16) | SAM_STAT_TASK_SET_FULL;

अटल स्थिर पूर्णांक condition_met_result = SAM_STAT_CONDITION_MET;


/* Only करो the extra work involved in logical block provisioning अगर one or
 * more of the lbpu, lbpws or lbpws10 parameters are given and we are करोing
 * real पढ़ोs and ग_लिखोs (i.e. not skipping them क्रम speed).
 */
अटल अंतरभूत bool scsi_debug_lbp(व्योम)
अणु
	वापस 0 == sdebug_fake_rw &&
		(sdebug_lbpu || sdebug_lbpws || sdebug_lbpws10);
पूर्ण

अटल व्योम *lba2fake_store(काष्ठा sdeb_store_info *sip,
			    अचिन्हित दीर्घ दीर्घ lba)
अणु
	काष्ठा sdeb_store_info *lsip = sip;

	lba = करो_भाग(lba, sdebug_store_sectors);
	अगर (!sip || !sip->storep) अणु
		WARN_ON_ONCE(true);
		lsip = xa_load(per_store_ap, 0);  /* should never be शून्य */
	पूर्ण
	वापस lsip->storep + lba * sdebug_sector_size;
पूर्ण

अटल काष्ठा t10_pi_tuple *dअगर_store(काष्ठा sdeb_store_info *sip,
				      sector_t sector)
अणु
	sector = sector_भाग(sector, sdebug_store_sectors);

	वापस sip->dअगर_storep + sector;
पूर्ण

अटल व्योम sdebug_max_tgts_luns(व्योम)
अणु
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा Scsi_Host *hpnt;

	spin_lock(&sdebug_host_list_lock);
	list_क्रम_each_entry(sdbg_host, &sdebug_host_list, host_list) अणु
		hpnt = sdbg_host->shost;
		अगर ((hpnt->this_id >= 0) &&
		    (sdebug_num_tgts > hpnt->this_id))
			hpnt->max_id = sdebug_num_tgts + 1;
		अन्यथा
			hpnt->max_id = sdebug_num_tgts;
		/* sdebug_max_luns; */
		hpnt->max_lun = SCSI_W_LUN_REPORT_LUNS + 1;
	पूर्ण
	spin_unlock(&sdebug_host_list_lock);
पूर्ण

क्रमागत sdeb_cmd_data अणुSDEB_IN_DATA = 0, SDEB_IN_CDB = 1पूर्ण;

/* Set in_bit to -1 to indicate no bit position of invalid field */
अटल व्योम mk_sense_invalid_fld(काष्ठा scsi_cmnd *scp,
				 क्रमागत sdeb_cmd_data c_d,
				 पूर्णांक in_byte, पूर्णांक in_bit)
अणु
	अचिन्हित अक्षर *sbuff;
	u8 sks[4];
	पूर्णांक sl, asc;

	sbuff = scp->sense_buffer;
	अगर (!sbuff) अणु
		sdev_prपूर्णांकk(KERN_ERR, scp->device,
			    "%s: sense_buffer is NULL\n", __func__);
		वापस;
	पूर्ण
	asc = c_d ? INVALID_FIELD_IN_CDB : INVALID_FIELD_IN_PARAM_LIST;
	स_रखो(sbuff, 0, SCSI_SENSE_BUFFERSIZE);
	scsi_build_sense_buffer(sdebug_dsense, sbuff, ILLEGAL_REQUEST, asc, 0);
	स_रखो(sks, 0, माप(sks));
	sks[0] = 0x80;
	अगर (c_d)
		sks[0] |= 0x40;
	अगर (in_bit >= 0) अणु
		sks[0] |= 0x8;
		sks[0] |= 0x7 & in_bit;
	पूर्ण
	put_unaligned_be16(in_byte, sks + 1);
	अगर (sdebug_dsense) अणु
		sl = sbuff[7] + 8;
		sbuff[7] = sl;
		sbuff[sl] = 0x2;
		sbuff[sl + 1] = 0x6;
		स_नकल(sbuff + sl + 4, sks, 3);
	पूर्ण अन्यथा
		स_नकल(sbuff + 15, sks, 3);
	अगर (sdebug_verbose)
		sdev_prपूर्णांकk(KERN_INFO, scp->device, "%s:  [sense_key,asc,ascq"
			    "]: [0x5,0x%x,0x0] %c byte=%d, bit=%d\n",
			    my_name, asc, c_d ? 'C' : 'D', in_byte, in_bit);
पूर्ण

अटल व्योम mk_sense_buffer(काष्ठा scsi_cmnd *scp, पूर्णांक key, पूर्णांक asc, पूर्णांक asq)
अणु
	अचिन्हित अक्षर *sbuff;

	sbuff = scp->sense_buffer;
	अगर (!sbuff) अणु
		sdev_prपूर्णांकk(KERN_ERR, scp->device,
			    "%s: sense_buffer is NULL\n", __func__);
		वापस;
	पूर्ण
	स_रखो(sbuff, 0, SCSI_SENSE_BUFFERSIZE);

	scsi_build_sense_buffer(sdebug_dsense, sbuff, key, asc, asq);

	अगर (sdebug_verbose)
		sdev_prपूर्णांकk(KERN_INFO, scp->device,
			    "%s:  [sense_key,asc,ascq]: [0x%x,0x%x,0x%x]\n",
			    my_name, key, asc, asq);
पूर्ण

अटल व्योम mk_sense_invalid_opcode(काष्ठा scsi_cmnd *scp)
अणु
	mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_OPCODE, 0);
पूर्ण

अटल पूर्णांक scsi_debug_ioctl(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
			    व्योम __user *arg)
अणु
	अगर (sdebug_verbose) अणु
		अगर (0x1261 == cmd)
			sdev_prपूर्णांकk(KERN_INFO, dev,
				    "%s: BLKFLSBUF [0x1261]\n", __func__);
		अन्यथा अगर (0x5331 == cmd)
			sdev_prपूर्णांकk(KERN_INFO, dev,
				    "%s: CDROM_GET_CAPABILITY [0x5331]\n",
				    __func__);
		अन्यथा
			sdev_prपूर्णांकk(KERN_INFO, dev, "%s: cmd=0x%x\n",
				    __func__, cmd);
	पूर्ण
	वापस -EINVAL;
	/* वापस -ENOTTY; // correct वापस but upsets fdisk */
पूर्ण

अटल व्योम config_cdb_len(काष्ठा scsi_device *sdev)
अणु
	चयन (sdebug_cdb_len) अणु
	हाल 6:	/* suggest 6 byte READ, WRITE and MODE SENSE/SELECT */
		sdev->use_10_क्रम_rw = false;
		sdev->use_16_क्रम_rw = false;
		sdev->use_10_क्रम_ms = false;
		अवरोध;
	हाल 10: /* suggest 10 byte RWs and 6 byte MODE SENSE/SELECT */
		sdev->use_10_क्रम_rw = true;
		sdev->use_16_क्रम_rw = false;
		sdev->use_10_क्रम_ms = false;
		अवरोध;
	हाल 12: /* suggest 10 byte RWs and 10 byte MODE SENSE/SELECT */
		sdev->use_10_क्रम_rw = true;
		sdev->use_16_क्रम_rw = false;
		sdev->use_10_क्रम_ms = true;
		अवरोध;
	हाल 16:
		sdev->use_10_क्रम_rw = false;
		sdev->use_16_क्रम_rw = true;
		sdev->use_10_क्रम_ms = true;
		अवरोध;
	हाल 32: /* No knobs to suggest this so same as 16 क्रम now */
		sdev->use_10_क्रम_rw = false;
		sdev->use_16_क्रम_rw = true;
		sdev->use_10_क्रम_ms = true;
		अवरोध;
	शेष:
		pr_warn("unexpected cdb_len=%d, force to 10\n",
			sdebug_cdb_len);
		sdev->use_10_क्रम_rw = true;
		sdev->use_16_क्रम_rw = false;
		sdev->use_10_क्रम_ms = false;
		sdebug_cdb_len = 10;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम all_config_cdb_len(व्योम)
अणु
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा Scsi_Host *shost;
	काष्ठा scsi_device *sdev;

	spin_lock(&sdebug_host_list_lock);
	list_क्रम_each_entry(sdbg_host, &sdebug_host_list, host_list) अणु
		shost = sdbg_host->shost;
		shost_क्रम_each_device(sdev, shost) अणु
			config_cdb_len(sdev);
		पूर्ण
	पूर्ण
	spin_unlock(&sdebug_host_list_lock);
पूर्ण

अटल व्योम clear_luns_changed_on_target(काष्ठा sdebug_dev_info *devip)
अणु
	काष्ठा sdebug_host_info *sdhp;
	काष्ठा sdebug_dev_info *dp;

	spin_lock(&sdebug_host_list_lock);
	list_क्रम_each_entry(sdhp, &sdebug_host_list, host_list) अणु
		list_क्रम_each_entry(dp, &sdhp->dev_info_list, dev_list) अणु
			अगर ((devip->sdbg_host == dp->sdbg_host) &&
			    (devip->target == dp->target))
				clear_bit(SDEBUG_UA_LUNS_CHANGED, dp->uas_bm);
		पूर्ण
	पूर्ण
	spin_unlock(&sdebug_host_list_lock);
पूर्ण

अटल पूर्णांक make_ua(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक k;

	k = find_first_bit(devip->uas_bm, SDEBUG_NUM_UAS);
	अगर (k != SDEBUG_NUM_UAS) अणु
		स्थिर अक्षर *cp = शून्य;

		चयन (k) अणु
		हाल SDEBUG_UA_POR:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_RESET_ASC,
					POWER_ON_RESET_ASCQ);
			अगर (sdebug_verbose)
				cp = "power on reset";
			अवरोध;
		हाल SDEBUG_UA_BUS_RESET:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_RESET_ASC,
					BUS_RESET_ASCQ);
			अगर (sdebug_verbose)
				cp = "bus reset";
			अवरोध;
		हाल SDEBUG_UA_MODE_CHANGED:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_CHANGED_ASC,
					MODE_CHANGED_ASCQ);
			अगर (sdebug_verbose)
				cp = "mode parameters changed";
			अवरोध;
		हाल SDEBUG_UA_CAPACITY_CHANGED:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_CHANGED_ASC,
					CAPACITY_CHANGED_ASCQ);
			अगर (sdebug_verbose)
				cp = "capacity data changed";
			अवरोध;
		हाल SDEBUG_UA_MICROCODE_CHANGED:
			mk_sense_buffer(scp, UNIT_ATTENTION,
					TARGET_CHANGED_ASC,
					MICROCODE_CHANGED_ASCQ);
			अगर (sdebug_verbose)
				cp = "microcode has been changed";
			अवरोध;
		हाल SDEBUG_UA_MICROCODE_CHANGED_WO_RESET:
			mk_sense_buffer(scp, UNIT_ATTENTION,
					TARGET_CHANGED_ASC,
					MICROCODE_CHANGED_WO_RESET_ASCQ);
			अगर (sdebug_verbose)
				cp = "microcode has been changed without reset";
			अवरोध;
		हाल SDEBUG_UA_LUNS_CHANGED:
			/*
			 * SPC-3 behavior is to report a UNIT ATTENTION with
			 * ASC/ASCQ REPORTED LUNS DATA HAS CHANGED on every LUN
			 * on the target, until a REPORT LUNS command is
			 * received.  SPC-4 behavior is to report it only once.
			 * NOTE:  sdebug_scsi_level करोes not use the same
			 * values as काष्ठा scsi_device->scsi_level.
			 */
			अगर (sdebug_scsi_level >= 6)	/* SPC-4 and above */
				clear_luns_changed_on_target(devip);
			mk_sense_buffer(scp, UNIT_ATTENTION,
					TARGET_CHANGED_ASC,
					LUNS_CHANGED_ASCQ);
			अगर (sdebug_verbose)
				cp = "reported luns data has changed";
			अवरोध;
		शेष:
			pr_warn("unexpected unit attention code=%d\n", k);
			अगर (sdebug_verbose)
				cp = "unknown";
			अवरोध;
		पूर्ण
		clear_bit(k, devip->uas_bm);
		अगर (sdebug_verbose)
			sdev_prपूर्णांकk(KERN_INFO, scp->device,
				   "%s reports: Unit attention: %s\n",
				   my_name, cp);
		वापस check_condition_result;
	पूर्ण
	वापस 0;
पूर्ण

/* Build SCSI "data-in" buffer. Returns 0 अगर ok अन्यथा (DID_ERROR << 16). */
अटल पूर्णांक fill_from_dev_buffer(काष्ठा scsi_cmnd *scp, अचिन्हित अक्षर *arr,
				पूर्णांक arr_len)
अणु
	पूर्णांक act_len;
	काष्ठा scsi_data_buffer *sdb = &scp->sdb;

	अगर (!sdb->length)
		वापस 0;
	अगर (scp->sc_data_direction != DMA_FROM_DEVICE)
		वापस DID_ERROR << 16;

	act_len = sg_copy_from_buffer(sdb->table.sgl, sdb->table.nents,
				      arr, arr_len);
	scsi_set_resid(scp, scsi_bufflen(scp) - act_len);

	वापस 0;
पूर्ण

/* Partial build of SCSI "data-in" buffer. Returns 0 अगर ok अन्यथा
 * (DID_ERROR << 16). Can ग_लिखो to offset in data-in buffer. If multiple
 * calls, not required to ग_लिखो in ascending offset order. Assumes resid
 * set to scsi_bufflen() prior to any calls.
 */
अटल पूर्णांक p_fill_from_dev_buffer(काष्ठा scsi_cmnd *scp, स्थिर व्योम *arr,
				  पूर्णांक arr_len, अचिन्हित पूर्णांक off_dst)
अणु
	अचिन्हित पूर्णांक act_len, n;
	काष्ठा scsi_data_buffer *sdb = &scp->sdb;
	off_t skip = off_dst;

	अगर (sdb->length <= off_dst)
		वापस 0;
	अगर (scp->sc_data_direction != DMA_FROM_DEVICE)
		वापस DID_ERROR << 16;

	act_len = sg_pcopy_from_buffer(sdb->table.sgl, sdb->table.nents,
				       arr, arr_len, skip);
	pr_debug("%s: off_dst=%u, scsi_bufflen=%u, act_len=%u, resid=%d\n",
		 __func__, off_dst, scsi_bufflen(scp), act_len,
		 scsi_get_resid(scp));
	n = scsi_bufflen(scp) - (off_dst + act_len);
	scsi_set_resid(scp, min_t(पूर्णांक, scsi_get_resid(scp), n));
	वापस 0;
पूर्ण

/* Fetches from SCSI "data-out" buffer. Returns number of bytes fetched पूर्णांकo
 * 'arr' or -1 अगर error.
 */
अटल पूर्णांक fetch_to_dev_buffer(काष्ठा scsi_cmnd *scp, अचिन्हित अक्षर *arr,
			       पूर्णांक arr_len)
अणु
	अगर (!scsi_bufflen(scp))
		वापस 0;
	अगर (scp->sc_data_direction != DMA_TO_DEVICE)
		वापस -1;

	वापस scsi_sg_copy_to_buffer(scp, arr, arr_len);
पूर्ण


अटल अक्षर sdebug_inq_venकरोr_id[9] = "Linux   ";
अटल अक्षर sdebug_inq_product_id[17] = "scsi_debug      ";
अटल अक्षर sdebug_inq_product_rev[5] = SDEBUG_VERSION;
/* Use some locally asचिन्हित NAAs क्रम SAS addresses. */
अटल स्थिर u64 naa3_comp_a = 0x3222222000000000ULL;
अटल स्थिर u64 naa3_comp_b = 0x3333333000000000ULL;
अटल स्थिर u64 naa3_comp_c = 0x3111111000000000ULL;

/* Device identअगरication VPD page. Returns number of bytes placed in arr */
अटल पूर्णांक inquiry_vpd_83(अचिन्हित अक्षर *arr, पूर्णांक port_group_id,
			  पूर्णांक target_dev_id, पूर्णांक dev_id_num,
			  स्थिर अक्षर *dev_id_str, पूर्णांक dev_id_str_len,
			  स्थिर uuid_t *lu_name)
अणु
	पूर्णांक num, port_a;
	अक्षर b[32];

	port_a = target_dev_id + 1;
	/* T10 venकरोr identअगरier field क्रमmat (faked) */
	arr[0] = 0x2;	/* ASCII */
	arr[1] = 0x1;
	arr[2] = 0x0;
	स_नकल(&arr[4], sdebug_inq_venकरोr_id, 8);
	स_नकल(&arr[12], sdebug_inq_product_id, 16);
	स_नकल(&arr[28], dev_id_str, dev_id_str_len);
	num = 8 + 16 + dev_id_str_len;
	arr[3] = num;
	num += 4;
	अगर (dev_id_num >= 0) अणु
		अगर (sdebug_uuid_ctl) अणु
			/* Locally asचिन्हित UUID */
			arr[num++] = 0x1;  /* binary (not necessarily sas) */
			arr[num++] = 0xa;  /* PIV=0, lu, naa */
			arr[num++] = 0x0;
			arr[num++] = 0x12;
			arr[num++] = 0x10; /* uuid type=1, locally asचिन्हित */
			arr[num++] = 0x0;
			स_नकल(arr + num, lu_name, 16);
			num += 16;
		पूर्ण अन्यथा अणु
			/* NAA-3, Logical unit identअगरier (binary) */
			arr[num++] = 0x1;  /* binary (not necessarily sas) */
			arr[num++] = 0x3;  /* PIV=0, lu, naa */
			arr[num++] = 0x0;
			arr[num++] = 0x8;
			put_unaligned_be64(naa3_comp_b + dev_id_num, arr + num);
			num += 8;
		पूर्ण
		/* Target relative port number */
		arr[num++] = 0x61;	/* proto=sas, binary */
		arr[num++] = 0x94;	/* PIV=1, target port, rel port */
		arr[num++] = 0x0;	/* reserved */
		arr[num++] = 0x4;	/* length */
		arr[num++] = 0x0;	/* reserved */
		arr[num++] = 0x0;	/* reserved */
		arr[num++] = 0x0;
		arr[num++] = 0x1;	/* relative port A */
	पूर्ण
	/* NAA-3, Target port identअगरier */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* piv=1, target port, naa */
	arr[num++] = 0x0;
	arr[num++] = 0x8;
	put_unaligned_be64(naa3_comp_a + port_a, arr + num);
	num += 8;
	/* NAA-3, Target port group identअगरier */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x95;	/* piv=1, target port group id */
	arr[num++] = 0x0;
	arr[num++] = 0x4;
	arr[num++] = 0;
	arr[num++] = 0;
	put_unaligned_be16(port_group_id, arr + num);
	num += 2;
	/* NAA-3, Target device identअगरier */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0xa3;	/* piv=1, target device, naa */
	arr[num++] = 0x0;
	arr[num++] = 0x8;
	put_unaligned_be64(naa3_comp_a + target_dev_id, arr + num);
	num += 8;
	/* SCSI name string: Target device identअगरier */
	arr[num++] = 0x63;	/* proto=sas, UTF-8 */
	arr[num++] = 0xa8;	/* piv=1, target device, SCSI name string */
	arr[num++] = 0x0;
	arr[num++] = 24;
	स_नकल(arr + num, "naa.32222220", 12);
	num += 12;
	snम_लिखो(b, माप(b), "%08X", target_dev_id);
	स_नकल(arr + num, b, 8);
	num += 8;
	स_रखो(arr + num, 0, 4);
	num += 4;
	वापस num;
पूर्ण

अटल अचिन्हित अक्षर vpd84_data[] = अणु
/* from 4th byte */ 0x22,0x22,0x22,0x0,0xbb,0x0,
    0x22,0x22,0x22,0x0,0xbb,0x1,
    0x22,0x22,0x22,0x0,0xbb,0x2,
पूर्ण;

/*  Software पूर्णांकerface identअगरication VPD page */
अटल पूर्णांक inquiry_vpd_84(अचिन्हित अक्षर *arr)
अणु
	स_नकल(arr, vpd84_data, माप(vpd84_data));
	वापस माप(vpd84_data);
पूर्ण

/* Management network addresses VPD page */
अटल पूर्णांक inquiry_vpd_85(अचिन्हित अक्षर *arr)
अणु
	पूर्णांक num = 0;
	स्थिर अक्षर *na1 = "https://www.kernel.org/config";
	स्थिर अक्षर *na2 = "http://www.kernel.org/log";
	पूर्णांक plen, olen;

	arr[num++] = 0x1;	/* lu, storage config */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	olen = म_माप(na1);
	plen = olen + 1;
	अगर (plen % 4)
		plen = ((plen / 4) + 1) * 4;
	arr[num++] = plen;	/* length, null termianted, padded */
	स_नकल(arr + num, na1, olen);
	स_रखो(arr + num + olen, 0, plen - olen);
	num += plen;

	arr[num++] = 0x4;	/* lu, logging */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	olen = म_माप(na2);
	plen = olen + 1;
	अगर (plen % 4)
		plen = ((plen / 4) + 1) * 4;
	arr[num++] = plen;	/* length, null terminated, padded */
	स_नकल(arr + num, na2, olen);
	स_रखो(arr + num + olen, 0, plen - olen);
	num += plen;

	वापस num;
पूर्ण

/* SCSI ports VPD page */
अटल पूर्णांक inquiry_vpd_88(अचिन्हित अक्षर *arr, पूर्णांक target_dev_id)
अणु
	पूर्णांक num = 0;
	पूर्णांक port_a, port_b;

	port_a = target_dev_id + 1;
	port_b = port_a + 1;
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	arr[num++] = 0x1;	/* relative port 1 (primary) */
	स_रखो(arr + num, 0, 6);
	num += 6;
	arr[num++] = 0x0;
	arr[num++] = 12;	/* length tp descriptor */
	/* naa-5 target port identअगरier (A) */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* PIV=1, target port, NAA */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x8;	/* length */
	put_unaligned_be64(naa3_comp_a + port_a, arr + num);
	num += 8;
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	arr[num++] = 0x2;	/* relative port 2 (secondary) */
	स_रखो(arr + num, 0, 6);
	num += 6;
	arr[num++] = 0x0;
	arr[num++] = 12;	/* length tp descriptor */
	/* naa-5 target port identअगरier (B) */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* PIV=1, target port, NAA */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x8;	/* length */
	put_unaligned_be64(naa3_comp_a + port_b, arr + num);
	num += 8;

	वापस num;
पूर्ण


अटल अचिन्हित अक्षर vpd89_data[] = अणु
/* from 4th byte */ 0,0,0,0,
'l','i','n','u','x',' ',' ',' ',
'S','A','T',' ','s','c','s','i','_','d','e','b','u','g',' ',' ',
'1','2','3','4',
0x34,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
0xec,0,0,0,
0x5a,0xc,0xff,0x3f,0x37,0xc8,0x10,0,0,0,0,0,0x3f,0,0,0,
0,0,0,0,0x58,0x58,0x58,0x58,0x58,0x58,0x58,0x58,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0,0,0,0x40,0x4,0,0x2e,0x33,
0x38,0x31,0x20,0x20,0x20,0x20,0x54,0x53,0x38,0x33,0x30,0x30,0x33,0x31,
0x53,0x41,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x10,0x80,
0,0,0,0x2f,0,0,0,0x2,0,0x2,0x7,0,0xff,0xff,0x1,0,
0x3f,0,0xc1,0xff,0x3e,0,0x10,0x1,0xb0,0xf8,0x50,0x9,0,0,0x7,0,
0x3,0,0x78,0,0x78,0,0xf0,0,0x78,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0x2,0,0,0,0,0,0,0,
0x7e,0,0x1b,0,0x6b,0x34,0x1,0x7d,0x3,0x40,0x69,0x34,0x1,0x3c,0x3,0x40,
0x7f,0x40,0,0,0,0,0xfe,0xfe,0,0,0,0,0,0xfe,0,0,
0,0,0,0,0,0,0,0,0xb0,0xf8,0x50,0x9,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0x1,0,0xb0,0xf8,0x50,0x9,0xb0,0xf8,0x50,0x9,0x20,0x20,0x2,0,0xb6,0x42,
0,0x80,0x8a,0,0x6,0x3c,0xa,0x3c,0xff,0xff,0xc6,0x7,0,0x1,0,0x8,
0xf0,0xf,0,0x10,0x2,0,0x30,0,0,0,0,0,0,0,0x6,0xfe,
0,0,0x2,0,0x50,0,0x8a,0,0x4f,0x95,0,0,0x21,0,0xb,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xa5,0x51,
पूर्ण;

/* ATA Inक्रमmation VPD page */
अटल पूर्णांक inquiry_vpd_89(अचिन्हित अक्षर *arr)
अणु
	स_नकल(arr, vpd89_data, माप(vpd89_data));
	वापस माप(vpd89_data);
पूर्ण


अटल अचिन्हित अक्षर vpdb0_data[] = अणु
	/* from 4th byte */ 0,0,0,4, 0,0,0x4,0, 0,0,0,64,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
पूर्ण;

/* Block limits VPD page (SBC-3) */
अटल पूर्णांक inquiry_vpd_b0(अचिन्हित अक्षर *arr)
अणु
	अचिन्हित पूर्णांक gran;

	स_नकल(arr, vpdb0_data, माप(vpdb0_data));

	/* Optimal transfer length granularity */
	अगर (sdebug_opt_xferlen_exp != 0 &&
	    sdebug_physblk_exp < sdebug_opt_xferlen_exp)
		gran = 1 << sdebug_opt_xferlen_exp;
	अन्यथा
		gran = 1 << sdebug_physblk_exp;
	put_unaligned_be16(gran, arr + 2);

	/* Maximum Transfer Length */
	अगर (sdebug_store_sectors > 0x400)
		put_unaligned_be32(sdebug_store_sectors, arr + 4);

	/* Optimal Transfer Length */
	put_unaligned_be32(sdebug_opt_blks, &arr[8]);

	अगर (sdebug_lbpu) अणु
		/* Maximum Unmap LBA Count */
		put_unaligned_be32(sdebug_unmap_max_blocks, &arr[16]);

		/* Maximum Unmap Block Descriptor Count */
		put_unaligned_be32(sdebug_unmap_max_desc, &arr[20]);
	पूर्ण

	/* Unmap Granularity Alignment */
	अगर (sdebug_unmap_alignment) अणु
		put_unaligned_be32(sdebug_unmap_alignment, &arr[28]);
		arr[28] |= 0x80; /* UGAVALID */
	पूर्ण

	/* Optimal Unmap Granularity */
	put_unaligned_be32(sdebug_unmap_granularity, &arr[24]);

	/* Maximum WRITE SAME Length */
	put_unaligned_be64(sdebug_ग_लिखो_same_length, &arr[32]);

	वापस 0x3c; /* Mandatory page length क्रम Logical Block Provisioning */

	वापस माप(vpdb0_data);
पूर्ण

/* Block device अक्षरacteristics VPD page (SBC-3) */
अटल पूर्णांक inquiry_vpd_b1(काष्ठा sdebug_dev_info *devip, अचिन्हित अक्षर *arr)
अणु
	स_रखो(arr, 0, 0x3c);
	arr[0] = 0;
	arr[1] = 1;	/* non rotating medium (e.g. solid state) */
	arr[2] = 0;
	arr[3] = 5;	/* less than 1.8" */
	अगर (devip->zmodel == BLK_ZONED_HA)
		arr[4] = 1 << 4;	/* zoned field = 01b */

	वापस 0x3c;
पूर्ण

/* Logical block provisioning VPD page (SBC-4) */
अटल पूर्णांक inquiry_vpd_b2(अचिन्हित अक्षर *arr)
अणु
	स_रखो(arr, 0, 0x4);
	arr[0] = 0;			/* threshold exponent */
	अगर (sdebug_lbpu)
		arr[1] = 1 << 7;
	अगर (sdebug_lbpws)
		arr[1] |= 1 << 6;
	अगर (sdebug_lbpws10)
		arr[1] |= 1 << 5;
	अगर (sdebug_lbprz && scsi_debug_lbp())
		arr[1] |= (sdebug_lbprz & 0x7) << 2;  /* sbc4r07 and later */
	/* anc_sup=0; dp=0 (no provisioning group descriptor) */
	/* minimum_percentage=0; provisioning_type=0 (unknown) */
	/* threshold_percentage=0 */
	वापस 0x4;
पूर्ण

/* Zoned block device अक्षरacteristics VPD page (ZBC mandatory) */
अटल पूर्णांक inquiry_vpd_b6(काष्ठा sdebug_dev_info *devip, अचिन्हित अक्षर *arr)
अणु
	स_रखो(arr, 0, 0x3c);
	arr[0] = 0x1; /* set URSWRZ (unrestricted पढ़ो in seq. wr req zone) */
	/*
	 * Set Optimal number of खोलो sequential ग_लिखो preferred zones and
	 * Optimal number of non-sequentially written sequential ग_लिखो
	 * preferred zones fields to 'not reported' (0xffffffff). Leave other
	 * fields set to zero, apart from Max. number of खोलो swrz_s field.
	 */
	put_unaligned_be32(0xffffffff, &arr[4]);
	put_unaligned_be32(0xffffffff, &arr[8]);
	अगर (sdeb_zbc_model == BLK_ZONED_HM && devip->max_खोलो)
		put_unaligned_be32(devip->max_खोलो, &arr[12]);
	अन्यथा
		put_unaligned_be32(0xffffffff, &arr[12]);
	वापस 0x3c;
पूर्ण

#घोषणा SDEBUG_LONG_INQ_SZ 96
#घोषणा SDEBUG_MAX_INQ_ARR_SZ 584

अटल पूर्णांक resp_inquiry(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर pq_pdt;
	अचिन्हित अक्षर *arr;
	अचिन्हित अक्षर *cmd = scp->cmnd;
	पूर्णांक alloc_len, n, ret;
	bool have_wlun, is_disk, is_zbc, is_disk_zbc;

	alloc_len = get_unaligned_be16(cmd + 3);
	arr = kzalloc(SDEBUG_MAX_INQ_ARR_SZ, GFP_ATOMIC);
	अगर (! arr)
		वापस DID_REQUEUE << 16;
	is_disk = (sdebug_ptype == TYPE_DISK);
	is_zbc = (devip->zmodel != BLK_ZONED_NONE);
	is_disk_zbc = (is_disk || is_zbc);
	have_wlun = scsi_is_wlun(scp->device->lun);
	अगर (have_wlun)
		pq_pdt = TYPE_WLUN;	/* present, wlun */
	अन्यथा अगर (sdebug_no_lun_0 && (devip->lun == SDEBUG_LUN_0_VAL))
		pq_pdt = 0x7f;	/* not present, PQ=3, PDT=0x1f */
	अन्यथा
		pq_pdt = (sdebug_ptype & 0x1f);
	arr[0] = pq_pdt;
	अगर (0x2 & cmd[1]) अणु  /* CMDDT bit set */
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 1, 1);
		kमुक्त(arr);
		वापस check_condition_result;
	पूर्ण अन्यथा अगर (0x1 & cmd[1]) अणु  /* EVPD bit set */
		पूर्णांक lu_id_num, port_group_id, target_dev_id, len;
		अक्षर lu_id_str[6];
		पूर्णांक host_no = devip->sdbg_host->shost->host_no;
		
		port_group_id = (((host_no + 1) & 0x7f) << 8) +
		    (devip->channel & 0x7f);
		अगर (sdebug_vpd_use_hostno == 0)
			host_no = 0;
		lu_id_num = have_wlun ? -1 : (((host_no + 1) * 2000) +
			    (devip->target * 1000) + devip->lun);
		target_dev_id = ((host_no + 1) * 2000) +
				 (devip->target * 1000) - 3;
		len = scnम_लिखो(lu_id_str, 6, "%d", lu_id_num);
		अगर (0 == cmd[2]) अणु /* supported vital product data pages */
			arr[1] = cmd[2];	/*sanity */
			n = 4;
			arr[n++] = 0x0;   /* this page */
			arr[n++] = 0x80;  /* unit serial number */
			arr[n++] = 0x83;  /* device identअगरication */
			arr[n++] = 0x84;  /* software पूर्णांकerface ident. */
			arr[n++] = 0x85;  /* management network addresses */
			arr[n++] = 0x86;  /* extended inquiry */
			arr[n++] = 0x87;  /* mode page policy */
			arr[n++] = 0x88;  /* SCSI ports */
			अगर (is_disk_zbc) अणु	  /* SBC or ZBC */
				arr[n++] = 0x89;  /* ATA inक्रमmation */
				arr[n++] = 0xb0;  /* Block limits */
				arr[n++] = 0xb1;  /* Block अक्षरacteristics */
				अगर (is_disk)
					arr[n++] = 0xb2;  /* LB Provisioning */
				अगर (is_zbc)
					arr[n++] = 0xb6;  /* ZB dev. अक्षर. */
			पूर्ण
			arr[3] = n - 4;	  /* number of supported VPD pages */
		पूर्ण अन्यथा अगर (0x80 == cmd[2]) अणु /* unit serial number */
			arr[1] = cmd[2];	/*sanity */
			arr[3] = len;
			स_नकल(&arr[4], lu_id_str, len);
		पूर्ण अन्यथा अगर (0x83 == cmd[2]) अणु /* device identअगरication */
			arr[1] = cmd[2];	/*sanity */
			arr[3] = inquiry_vpd_83(&arr[4], port_group_id,
						target_dev_id, lu_id_num,
						lu_id_str, len,
						&devip->lu_name);
		पूर्ण अन्यथा अगर (0x84 == cmd[2]) अणु /* Software पूर्णांकerface ident. */
			arr[1] = cmd[2];	/*sanity */
			arr[3] = inquiry_vpd_84(&arr[4]);
		पूर्ण अन्यथा अगर (0x85 == cmd[2]) अणु /* Management network addresses */
			arr[1] = cmd[2];	/*sanity */
			arr[3] = inquiry_vpd_85(&arr[4]);
		पूर्ण अन्यथा अगर (0x86 == cmd[2]) अणु /* extended inquiry */
			arr[1] = cmd[2];	/*sanity */
			arr[3] = 0x3c;	/* number of following entries */
			अगर (sdebug_dअगर == T10_PI_TYPE3_PROTECTION)
				arr[4] = 0x4;	/* SPT: GRD_CHK:1 */
			अन्यथा अगर (have_dअगर_prot)
				arr[4] = 0x5;   /* SPT: GRD_CHK:1, REF_CHK:1 */
			अन्यथा
				arr[4] = 0x0;   /* no protection stuff */
			arr[5] = 0x7;   /* head of q, ordered + simple q's */
		पूर्ण अन्यथा अगर (0x87 == cmd[2]) अणु /* mode page policy */
			arr[1] = cmd[2];	/*sanity */
			arr[3] = 0x8;	/* number of following entries */
			arr[4] = 0x2;	/* disconnect-reconnect mp */
			arr[6] = 0x80;	/* mlus, shared */
			arr[8] = 0x18;	 /* protocol specअगरic lu */
			arr[10] = 0x82;	 /* mlus, per initiator port */
		पूर्ण अन्यथा अगर (0x88 == cmd[2]) अणु /* SCSI Ports */
			arr[1] = cmd[2];	/*sanity */
			arr[3] = inquiry_vpd_88(&arr[4], target_dev_id);
		पूर्ण अन्यथा अगर (is_disk_zbc && 0x89 == cmd[2]) अणु /* ATA info */
			arr[1] = cmd[2];        /*sanity */
			n = inquiry_vpd_89(&arr[4]);
			put_unaligned_be16(n, arr + 2);
		पूर्ण अन्यथा अगर (is_disk_zbc && 0xb0 == cmd[2]) अणु /* Block limits */
			arr[1] = cmd[2];        /*sanity */
			arr[3] = inquiry_vpd_b0(&arr[4]);
		पूर्ण अन्यथा अगर (is_disk_zbc && 0xb1 == cmd[2]) अणु /* Block अक्षर. */
			arr[1] = cmd[2];        /*sanity */
			arr[3] = inquiry_vpd_b1(devip, &arr[4]);
		पूर्ण अन्यथा अगर (is_disk && 0xb2 == cmd[2]) अणु /* LB Prov. */
			arr[1] = cmd[2];        /*sanity */
			arr[3] = inquiry_vpd_b2(&arr[4]);
		पूर्ण अन्यथा अगर (is_zbc && cmd[2] == 0xb6) अणु /* ZB dev. अक्षरact. */
			arr[1] = cmd[2];        /*sanity */
			arr[3] = inquiry_vpd_b6(devip, &arr[4]);
		पूर्ण अन्यथा अणु
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, -1);
			kमुक्त(arr);
			वापस check_condition_result;
		पूर्ण
		len = min(get_unaligned_be16(arr + 2) + 4, alloc_len);
		ret = fill_from_dev_buffer(scp, arr,
			    min(len, SDEBUG_MAX_INQ_ARR_SZ));
		kमुक्त(arr);
		वापस ret;
	पूर्ण
	/* drops through here क्रम a standard inquiry */
	arr[1] = sdebug_removable ? 0x80 : 0;	/* Removable disk */
	arr[2] = sdebug_scsi_level;
	arr[3] = 2;    /* response_data_क्रमmat==2 */
	arr[4] = SDEBUG_LONG_INQ_SZ - 5;
	arr[5] = (पूर्णांक)have_dअगर_prot;	/* PROTECT bit */
	अगर (sdebug_vpd_use_hostno == 0)
		arr[5] |= 0x10; /* claim: implicit TPGS */
	arr[6] = 0x10; /* claim: MultiP */
	/* arr[6] |= 0x40; ... claim: EncServ (enclosure services) */
	arr[7] = 0xa; /* claim: LINKED + CMDQUE */
	स_नकल(&arr[8], sdebug_inq_venकरोr_id, 8);
	स_नकल(&arr[16], sdebug_inq_product_id, 16);
	स_नकल(&arr[32], sdebug_inq_product_rev, 4);
	/* Use Venकरोr Specअगरic area to place driver date in ASCII hex */
	स_नकल(&arr[36], sdebug_version_date, 8);
	/* version descriptors (2 bytes each) follow */
	put_unaligned_be16(0xc0, arr + 58);   /* SAM-6 no version claimed */
	put_unaligned_be16(0x5c0, arr + 60);  /* SPC-5 no version claimed */
	n = 62;
	अगर (is_disk) अणु		/* SBC-4 no version claimed */
		put_unaligned_be16(0x600, arr + n);
		n += 2;
	पूर्ण अन्यथा अगर (sdebug_ptype == TYPE_TAPE) अणु	/* SSC-4 rev 3 */
		put_unaligned_be16(0x525, arr + n);
		n += 2;
	पूर्ण अन्यथा अगर (is_zbc) अणु	/* ZBC BSR INCITS 536 revision 05 */
		put_unaligned_be16(0x624, arr + n);
		n += 2;
	पूर्ण
	put_unaligned_be16(0x2100, arr + n);	/* SPL-4 no version claimed */
	ret = fill_from_dev_buffer(scp, arr,
			    min_t(पूर्णांक, alloc_len, SDEBUG_LONG_INQ_SZ));
	kमुक्त(arr);
	वापस ret;
पूर्ण

/* See resp_iec_m_pg() क्रम how this data is manipulated */
अटल अचिन्हित अक्षर iec_m_pg[] = अणु0x1c, 0xa, 0x08, 0, 0, 0, 0, 0,
				   0, 0, 0x0, 0x0पूर्ण;

अटल पूर्णांक resp_requests(काष्ठा scsi_cmnd *scp,
			 काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर *cmd = scp->cmnd;
	अचिन्हित अक्षर arr[SCSI_SENSE_BUFFERSIZE];	/* assume >= 18 bytes */
	bool dsense = !!(cmd[1] & 1);
	पूर्णांक alloc_len = cmd[4];
	पूर्णांक len = 18;
	पूर्णांक stopped_state = atomic_पढ़ो(&devip->stopped);

	स_रखो(arr, 0, माप(arr));
	अगर (stopped_state > 0) अणु	/* some "pollable" data [spc6r02: 5.12.2] */
		अगर (dsense) अणु
			arr[0] = 0x72;
			arr[1] = NOT_READY;
			arr[2] = LOGICAL_UNIT_NOT_READY;
			arr[3] = (stopped_state == 2) ? 0x1 : 0x2;
			len = 8;
		पूर्ण अन्यथा अणु
			arr[0] = 0x70;
			arr[2] = NOT_READY;		/* NO_SENSE in sense_key */
			arr[7] = 0xa;			/* 18 byte sense buffer */
			arr[12] = LOGICAL_UNIT_NOT_READY;
			arr[13] = (stopped_state == 2) ? 0x1 : 0x2;
		पूर्ण
	पूर्ण अन्यथा अगर ((iec_m_pg[2] & 0x4) && (6 == (iec_m_pg[3] & 0xf))) अणु
		/* Inक्रमmation exceptions control mode page: TEST=1, MRIE=6 */
		अगर (dsense) अणु
			arr[0] = 0x72;
			arr[1] = 0x0;		/* NO_SENSE in sense_key */
			arr[2] = THRESHOLD_EXCEEDED;
			arr[3] = 0xff;		/* Failure prediction(false) */
			len = 8;
		पूर्ण अन्यथा अणु
			arr[0] = 0x70;
			arr[2] = 0x0;		/* NO_SENSE in sense_key */
			arr[7] = 0xa;   	/* 18 byte sense buffer */
			arr[12] = THRESHOLD_EXCEEDED;
			arr[13] = 0xff;		/* Failure prediction(false) */
		पूर्ण
	पूर्ण अन्यथा अणु	/* nothing to report */
		अगर (dsense) अणु
			len = 8;
			स_रखो(arr, 0, len);
			arr[0] = 0x72;
		पूर्ण अन्यथा अणु
			स_रखो(arr, 0, len);
			arr[0] = 0x70;
			arr[7] = 0xa;
		पूर्ण
	पूर्ण
	वापस fill_from_dev_buffer(scp, arr, min_t(पूर्णांक, len, alloc_len));
पूर्ण

अटल पूर्णांक resp_start_stop(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर *cmd = scp->cmnd;
	पूर्णांक घातer_cond, want_stop, stopped_state;
	bool changing;

	घातer_cond = (cmd[4] & 0xf0) >> 4;
	अगर (घातer_cond) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 4, 7);
		वापस check_condition_result;
	पूर्ण
	want_stop = !(cmd[4] & 1);
	stopped_state = atomic_पढ़ो(&devip->stopped);
	अगर (stopped_state == 2) अणु
		kसमय_प्रकार now_ts = kसमय_get_bootसमय();

		अगर (kसमय_प्रकारo_ns(now_ts) > kसमय_प्रकारo_ns(devip->create_ts)) अणु
			u64 dअगरf_ns = kसमय_प्रकारo_ns(kसमय_sub(now_ts, devip->create_ts));

			अगर (dअगरf_ns >= ((u64)sdeb_tur_ms_to_पढ़ोy * 1000000)) अणु
				/* tur_ms_to_पढ़ोy समयr extinguished */
				atomic_set(&devip->stopped, 0);
				stopped_state = 0;
			पूर्ण
		पूर्ण
		अगर (stopped_state == 2) अणु
			अगर (want_stop) अणु
				stopped_state = 1;	/* dummy up success */
			पूर्ण अन्यथा अणु	/* Disallow tur_ms_to_पढ़ोy delay to be overridden */
				mk_sense_invalid_fld(scp, SDEB_IN_CDB, 4, 0 /* START bit */);
				वापस check_condition_result;
			पूर्ण
		पूर्ण
	पूर्ण
	changing = (stopped_state != want_stop);
	अगर (changing)
		atomic_xchg(&devip->stopped, want_stop);
	अगर (!changing || (cmd[1] & 0x1))  /* state unchanged or IMMED bit set in cdb */
		वापस SDEG_RES_IMMED_MASK;
	अन्यथा
		वापस 0;
पूर्ण

अटल sector_t get_sdebug_capacity(व्योम)
अणु
	अटल स्थिर अचिन्हित पूर्णांक gibibyte = 1073741824;

	अगर (sdebug_भव_gb > 0)
		वापस (sector_t)sdebug_भव_gb *
			(gibibyte / sdebug_sector_size);
	अन्यथा
		वापस sdebug_store_sectors;
पूर्ण

#घोषणा SDEBUG_READCAP_ARR_SZ 8
अटल पूर्णांक resp_पढ़ोcap(काष्ठा scsi_cmnd *scp,
			काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर arr[SDEBUG_READCAP_ARR_SZ];
	अचिन्हित पूर्णांक capac;

	/* following just in हाल भव_gb changed */
	sdebug_capacity = get_sdebug_capacity();
	स_रखो(arr, 0, SDEBUG_READCAP_ARR_SZ);
	अगर (sdebug_capacity < 0xffffffff) अणु
		capac = (अचिन्हित पूर्णांक)sdebug_capacity - 1;
		put_unaligned_be32(capac, arr + 0);
	पूर्ण अन्यथा
		put_unaligned_be32(0xffffffff, arr + 0);
	put_unaligned_be16(sdebug_sector_size, arr + 6);
	वापस fill_from_dev_buffer(scp, arr, SDEBUG_READCAP_ARR_SZ);
पूर्ण

#घोषणा SDEBUG_READCAP16_ARR_SZ 32
अटल पूर्णांक resp_पढ़ोcap16(काष्ठा scsi_cmnd *scp,
			  काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर *cmd = scp->cmnd;
	अचिन्हित अक्षर arr[SDEBUG_READCAP16_ARR_SZ];
	पूर्णांक alloc_len;

	alloc_len = get_unaligned_be32(cmd + 10);
	/* following just in हाल भव_gb changed */
	sdebug_capacity = get_sdebug_capacity();
	स_रखो(arr, 0, SDEBUG_READCAP16_ARR_SZ);
	put_unaligned_be64((u64)(sdebug_capacity - 1), arr + 0);
	put_unaligned_be32(sdebug_sector_size, arr + 8);
	arr[13] = sdebug_physblk_exp & 0xf;
	arr[14] = (sdebug_lowest_aligned >> 8) & 0x3f;

	अगर (scsi_debug_lbp()) अणु
		arr[14] |= 0x80; /* LBPME */
		/* from sbc4r07, this LBPRZ field is 1 bit, but the LBPRZ in
		 * the LB Provisioning VPD page is 3 bits. Note that lbprz=2
		 * in the wider field maps to 0 in this field.
		 */
		अगर (sdebug_lbprz & 1)	/* precisely what the draft requires */
			arr[14] |= 0x40;
	पूर्ण

	arr[15] = sdebug_lowest_aligned & 0xff;

	अगर (have_dअगर_prot) अणु
		arr[12] = (sdebug_dअगर - 1) << 1; /* P_TYPE */
		arr[12] |= 1; /* PROT_EN */
	पूर्ण

	वापस fill_from_dev_buffer(scp, arr,
			    min_t(पूर्णांक, alloc_len, SDEBUG_READCAP16_ARR_SZ));
पूर्ण

#घोषणा SDEBUG_MAX_TGTPGS_ARR_SZ 1412

अटल पूर्णांक resp_report_tgtpgs(काष्ठा scsi_cmnd *scp,
			      काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर *cmd = scp->cmnd;
	अचिन्हित अक्षर *arr;
	पूर्णांक host_no = devip->sdbg_host->shost->host_no;
	पूर्णांक n, ret, alen, rlen;
	पूर्णांक port_group_a, port_group_b, port_a, port_b;

	alen = get_unaligned_be32(cmd + 6);
	arr = kzalloc(SDEBUG_MAX_TGTPGS_ARR_SZ, GFP_ATOMIC);
	अगर (! arr)
		वापस DID_REQUEUE << 16;
	/*
	 * EVPD page 0x88 states we have two ports, one
	 * real and a fake port with no device connected.
	 * So we create two port groups with one port each
	 * and set the group with port B to unavailable.
	 */
	port_a = 0x1; /* relative port A */
	port_b = 0x2; /* relative port B */
	port_group_a = (((host_no + 1) & 0x7f) << 8) +
			(devip->channel & 0x7f);
	port_group_b = (((host_no + 1) & 0x7f) << 8) +
			(devip->channel & 0x7f) + 0x80;

	/*
	 * The asymmetric access state is cycled according to the host_id.
	 */
	n = 4;
	अगर (sdebug_vpd_use_hostno == 0) अणु
		arr[n++] = host_no % 3; /* Asymm access state */
		arr[n++] = 0x0F; /* claim: all states are supported */
	पूर्ण अन्यथा अणु
		arr[n++] = 0x0; /* Active/Optimized path */
		arr[n++] = 0x01; /* only support active/optimized paths */
	पूर्ण
	put_unaligned_be16(port_group_a, arr + n);
	n += 2;
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Status code */
	arr[n++] = 0;    /* Venकरोr unique */
	arr[n++] = 0x1;  /* One port per group */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Reserved */
	put_unaligned_be16(port_a, arr + n);
	n += 2;
	arr[n++] = 3;    /* Port unavailable */
	arr[n++] = 0x08; /* claim: only unavailalbe paths are supported */
	put_unaligned_be16(port_group_b, arr + n);
	n += 2;
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Status code */
	arr[n++] = 0;    /* Venकरोr unique */
	arr[n++] = 0x1;  /* One port per group */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Reserved */
	put_unaligned_be16(port_b, arr + n);
	n += 2;

	rlen = n - 4;
	put_unaligned_be32(rlen, arr + 0);

	/*
	 * Return the smallest value of either
	 * - The allocated length
	 * - The स्थिरructed command length
	 * - The maximum array size
	 */
	rlen = min_t(पूर्णांक, alen, n);
	ret = fill_from_dev_buffer(scp, arr,
			   min_t(पूर्णांक, rlen, SDEBUG_MAX_TGTPGS_ARR_SZ));
	kमुक्त(arr);
	वापस ret;
पूर्ण

अटल पूर्णांक resp_rsup_opcodes(काष्ठा scsi_cmnd *scp,
			     काष्ठा sdebug_dev_info *devip)
अणु
	bool rctd;
	u8 reporting_opts, req_opcode, sdeb_i, supp;
	u16 req_sa, u;
	u32 alloc_len, a_len;
	पूर्णांक k, offset, len, errsts, count, bump, na;
	स्थिर काष्ठा opcode_info_t *oip;
	स्थिर काष्ठा opcode_info_t *r_oip;
	u8 *arr;
	u8 *cmd = scp->cmnd;

	rctd = !!(cmd[2] & 0x80);
	reporting_opts = cmd[2] & 0x7;
	req_opcode = cmd[3];
	req_sa = get_unaligned_be16(cmd + 4);
	alloc_len = get_unaligned_be32(cmd + 6);
	अगर (alloc_len < 4 || alloc_len > 0xffff) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 6, -1);
		वापस check_condition_result;
	पूर्ण
	अगर (alloc_len > 8192)
		a_len = 8192;
	अन्यथा
		a_len = alloc_len;
	arr = kzalloc((a_len < 256) ? 320 : a_len + 64, GFP_ATOMIC);
	अगर (शून्य == arr) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		वापस check_condition_result;
	पूर्ण
	चयन (reporting_opts) अणु
	हाल 0:	/* all commands */
		/* count number of commands */
		क्रम (count = 0, oip = opcode_info_arr;
		     oip->num_attached != 0xff; ++oip) अणु
			अगर (F_INV_OP & oip->flags)
				जारी;
			count += (oip->num_attached + 1);
		पूर्ण
		bump = rctd ? 20 : 8;
		put_unaligned_be32(count * bump, arr);
		क्रम (offset = 4, oip = opcode_info_arr;
		     oip->num_attached != 0xff && offset < a_len; ++oip) अणु
			अगर (F_INV_OP & oip->flags)
				जारी;
			na = oip->num_attached;
			arr[offset] = oip->opcode;
			put_unaligned_be16(oip->sa, arr + offset + 2);
			अगर (rctd)
				arr[offset + 5] |= 0x2;
			अगर (FF_SA & oip->flags)
				arr[offset + 5] |= 0x1;
			put_unaligned_be16(oip->len_mask[0], arr + offset + 6);
			अगर (rctd)
				put_unaligned_be16(0xa, arr + offset + 8);
			r_oip = oip;
			क्रम (k = 0, oip = oip->arrp; k < na; ++k, ++oip) अणु
				अगर (F_INV_OP & oip->flags)
					जारी;
				offset += bump;
				arr[offset] = oip->opcode;
				put_unaligned_be16(oip->sa, arr + offset + 2);
				अगर (rctd)
					arr[offset + 5] |= 0x2;
				अगर (FF_SA & oip->flags)
					arr[offset + 5] |= 0x1;
				put_unaligned_be16(oip->len_mask[0],
						   arr + offset + 6);
				अगर (rctd)
					put_unaligned_be16(0xa,
							   arr + offset + 8);
			पूर्ण
			oip = r_oip;
			offset += bump;
		पूर्ण
		अवरोध;
	हाल 1:	/* one command: opcode only */
	हाल 2:	/* one command: opcode plus service action */
	हाल 3:	/* one command: अगर sa==0 then opcode only अन्यथा opcode+sa */
		sdeb_i = opcode_ind_arr[req_opcode];
		oip = &opcode_info_arr[sdeb_i];
		अगर (F_INV_OP & oip->flags) अणु
			supp = 1;
			offset = 4;
		पूर्ण अन्यथा अणु
			अगर (1 == reporting_opts) अणु
				अगर (FF_SA & oip->flags) अणु
					mk_sense_invalid_fld(scp, SDEB_IN_CDB,
							     2, 2);
					kमुक्त(arr);
					वापस check_condition_result;
				पूर्ण
				req_sa = 0;
			पूर्ण अन्यथा अगर (2 == reporting_opts &&
				   0 == (FF_SA & oip->flags)) अणु
				mk_sense_invalid_fld(scp, SDEB_IN_CDB, 4, -1);
				kमुक्त(arr);	/* poपूर्णांक at requested sa */
				वापस check_condition_result;
			पूर्ण
			अगर (0 == (FF_SA & oip->flags) &&
			    req_opcode == oip->opcode)
				supp = 3;
			अन्यथा अगर (0 == (FF_SA & oip->flags)) अणु
				na = oip->num_attached;
				क्रम (k = 0, oip = oip->arrp; k < na;
				     ++k, ++oip) अणु
					अगर (req_opcode == oip->opcode)
						अवरोध;
				पूर्ण
				supp = (k >= na) ? 1 : 3;
			पूर्ण अन्यथा अगर (req_sa != oip->sa) अणु
				na = oip->num_attached;
				क्रम (k = 0, oip = oip->arrp; k < na;
				     ++k, ++oip) अणु
					अगर (req_sa == oip->sa)
						अवरोध;
				पूर्ण
				supp = (k >= na) ? 1 : 3;
			पूर्ण अन्यथा
				supp = 3;
			अगर (3 == supp) अणु
				u = oip->len_mask[0];
				put_unaligned_be16(u, arr + 2);
				arr[4] = oip->opcode;
				क्रम (k = 1; k < u; ++k)
					arr[4 + k] = (k < 16) ?
						 oip->len_mask[k] : 0xff;
				offset = 4 + u;
			पूर्ण अन्यथा
				offset = 4;
		पूर्ण
		arr[1] = (rctd ? 0x80 : 0) | supp;
		अगर (rctd) अणु
			put_unaligned_be16(0xa, arr + offset);
			offset += 12;
		पूर्ण
		अवरोध;
	शेष:
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, 2);
		kमुक्त(arr);
		वापस check_condition_result;
	पूर्ण
	offset = (offset < a_len) ? offset : a_len;
	len = (offset < alloc_len) ? offset : alloc_len;
	errsts = fill_from_dev_buffer(scp, arr, len);
	kमुक्त(arr);
	वापस errsts;
पूर्ण

अटल पूर्णांक resp_rsup_पंचांगfs(काष्ठा scsi_cmnd *scp,
			  काष्ठा sdebug_dev_info *devip)
अणु
	bool repd;
	u32 alloc_len, len;
	u8 arr[16];
	u8 *cmd = scp->cmnd;

	स_रखो(arr, 0, माप(arr));
	repd = !!(cmd[2] & 0x80);
	alloc_len = get_unaligned_be32(cmd + 6);
	अगर (alloc_len < 4) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 6, -1);
		वापस check_condition_result;
	पूर्ण
	arr[0] = 0xc8;		/* ATS | ATSS | LURS */
	arr[1] = 0x1;		/* ITNRS */
	अगर (repd) अणु
		arr[3] = 0xc;
		len = 16;
	पूर्ण अन्यथा
		len = 4;

	len = (len < alloc_len) ? len : alloc_len;
	वापस fill_from_dev_buffer(scp, arr, len);
पूर्ण

/* <<Following mode page info copied from ST318451LW>> */

अटल पूर्णांक resp_err_recov_pg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target)
अणु	/* Read-Write Error Recovery page क्रम mode_sense */
	अचिन्हित अक्षर err_recov_pg[] = अणु0x1, 0xa, 0xc0, 11, 240, 0, 0, 0,
					5, 0, 0xff, 0xffपूर्ण;

	स_नकल(p, err_recov_pg, माप(err_recov_pg));
	अगर (1 == pcontrol)
		स_रखो(p + 2, 0, माप(err_recov_pg) - 2);
	वापस माप(err_recov_pg);
पूर्ण

अटल पूर्णांक resp_disconnect_pg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target)
अणु 	/* Disconnect-Reconnect page क्रम mode_sense */
	अचिन्हित अक्षर disconnect_pg[] = अणु0x2, 0xe, 128, 128, 0, 10, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0पूर्ण;

	स_नकल(p, disconnect_pg, माप(disconnect_pg));
	अगर (1 == pcontrol)
		स_रखो(p + 2, 0, माप(disconnect_pg) - 2);
	वापस माप(disconnect_pg);
पूर्ण

अटल पूर्णांक resp_क्रमmat_pg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target)
अणु       /* Format device page क्रम mode_sense */
	अचिन्हित अक्षर क्रमmat_pg[] = अणु0x3, 0x16, 0, 0, 0, 0, 0, 0,
				     0, 0, 0, 0, 0, 0, 0, 0,
				     0, 0, 0, 0, 0x40, 0, 0, 0पूर्ण;

	स_नकल(p, क्रमmat_pg, माप(क्रमmat_pg));
	put_unaligned_be16(sdebug_sectors_per, p + 10);
	put_unaligned_be16(sdebug_sector_size, p + 12);
	अगर (sdebug_removable)
		p[20] |= 0x20; /* should agree with INQUIRY */
	अगर (1 == pcontrol)
		स_रखो(p + 2, 0, माप(क्रमmat_pg) - 2);
	वापस माप(क्रमmat_pg);
पूर्ण

अटल अचिन्हित अक्षर caching_pg[] = अणु0x8, 18, 0x14, 0, 0xff, 0xff, 0, 0,
				     0xff, 0xff, 0xff, 0xff, 0x80, 0x14, 0, 0,
				     0, 0, 0, 0पूर्ण;

अटल पूर्णांक resp_caching_pg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target)
अणु 	/* Caching page क्रम mode_sense */
	अचिन्हित अक्षर ch_caching_pg[] = अणु/* 0x8, 18, */ 0x4, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
	अचिन्हित अक्षर d_caching_pg[] = अणु0x8, 18, 0x14, 0, 0xff, 0xff, 0, 0,
		0xff, 0xff, 0xff, 0xff, 0x80, 0x14, 0, 0,     0, 0, 0, 0पूर्ण;

	अगर (SDEBUG_OPT_N_WCE & sdebug_opts)
		caching_pg[2] &= ~0x4;	/* set WCE=0 (शेष WCE=1) */
	स_नकल(p, caching_pg, माप(caching_pg));
	अगर (1 == pcontrol)
		स_नकल(p + 2, ch_caching_pg, माप(ch_caching_pg));
	अन्यथा अगर (2 == pcontrol)
		स_नकल(p, d_caching_pg, माप(d_caching_pg));
	वापस माप(caching_pg);
पूर्ण

अटल अचिन्हित अक्षर ctrl_m_pg[] = अणु0xa, 10, 2, 0, 0, 0, 0, 0,
				    0, 0, 0x2, 0x4bपूर्ण;

अटल पूर्णांक resp_ctrl_m_pg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target)
अणु 	/* Control mode page क्रम mode_sense */
	अचिन्हित अक्षर ch_ctrl_m_pg[] = अणु/* 0xa, 10, */ 0x6, 0, 0, 0, 0, 0,
					0, 0, 0, 0पूर्ण;
	अचिन्हित अक्षर d_ctrl_m_pg[] = अणु0xa, 10, 2, 0, 0, 0, 0, 0,
				     0, 0, 0x2, 0x4bपूर्ण;

	अगर (sdebug_dsense)
		ctrl_m_pg[2] |= 0x4;
	अन्यथा
		ctrl_m_pg[2] &= ~0x4;

	अगर (sdebug_ato)
		ctrl_m_pg[5] |= 0x80; /* ATO=1 */

	स_नकल(p, ctrl_m_pg, माप(ctrl_m_pg));
	अगर (1 == pcontrol)
		स_नकल(p + 2, ch_ctrl_m_pg, माप(ch_ctrl_m_pg));
	अन्यथा अगर (2 == pcontrol)
		स_नकल(p, d_ctrl_m_pg, माप(d_ctrl_m_pg));
	वापस माप(ctrl_m_pg);
पूर्ण


अटल पूर्णांक resp_iec_m_pg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target)
अणु	/* Inक्रमmational Exceptions control mode page क्रम mode_sense */
	अचिन्हित अक्षर ch_iec_m_pg[] = अणु/* 0x1c, 0xa, */ 0x4, 0xf, 0, 0, 0, 0,
				       0, 0, 0x0, 0x0पूर्ण;
	अचिन्हित अक्षर d_iec_m_pg[] = अणु0x1c, 0xa, 0x08, 0, 0, 0, 0, 0,
				      0, 0, 0x0, 0x0पूर्ण;

	स_नकल(p, iec_m_pg, माप(iec_m_pg));
	अगर (1 == pcontrol)
		स_नकल(p + 2, ch_iec_m_pg, माप(ch_iec_m_pg));
	अन्यथा अगर (2 == pcontrol)
		स_नकल(p, d_iec_m_pg, माप(d_iec_m_pg));
	वापस माप(iec_m_pg);
पूर्ण

अटल पूर्णांक resp_sas_sf_m_pg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target)
अणु	/* SAS SSP mode page - लघु क्रमmat क्रम mode_sense */
	अचिन्हित अक्षर sas_sf_m_pg[] = अणु0x19, 0x6,
		0x6, 0x0, 0x7, 0xd0, 0x0, 0x0पूर्ण;

	स_नकल(p, sas_sf_m_pg, माप(sas_sf_m_pg));
	अगर (1 == pcontrol)
		स_रखो(p + 2, 0, माप(sas_sf_m_pg) - 2);
	वापस माप(sas_sf_m_pg);
पूर्ण


अटल पूर्णांक resp_sas_pcd_m_spg(अचिन्हित अक्षर *p, पूर्णांक pcontrol, पूर्णांक target,
			      पूर्णांक target_dev_id)
अणु	/* SAS phy control and discover mode page क्रम mode_sense */
	अचिन्हित अक्षर sas_pcd_m_pg[] = अणु0x59, 0x1, 0, 0x64, 0, 0x6, 0, 2,
		    0, 0, 0, 0, 0x10, 0x9, 0x8, 0x0,
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insert SAS addr */
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insert SAS addr */
		    0x2, 0, 0, 0, 0, 0, 0, 0,
		    0x88, 0x99, 0, 0, 0, 0, 0, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		    0, 1, 0, 0, 0x10, 0x9, 0x8, 0x0,
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insert SAS addr */
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insert SAS addr */
		    0x3, 0, 0, 0, 0, 0, 0, 0,
		    0x88, 0x99, 0, 0, 0, 0, 0, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		पूर्ण;
	पूर्णांक port_a, port_b;

	put_unaligned_be64(naa3_comp_a, sas_pcd_m_pg + 16);
	put_unaligned_be64(naa3_comp_c + 1, sas_pcd_m_pg + 24);
	put_unaligned_be64(naa3_comp_a, sas_pcd_m_pg + 64);
	put_unaligned_be64(naa3_comp_c + 1, sas_pcd_m_pg + 72);
	port_a = target_dev_id + 1;
	port_b = port_a + 1;
	स_नकल(p, sas_pcd_m_pg, माप(sas_pcd_m_pg));
	put_unaligned_be32(port_a, p + 20);
	put_unaligned_be32(port_b, p + 48 + 20);
	अगर (1 == pcontrol)
		स_रखो(p + 4, 0, माप(sas_pcd_m_pg) - 4);
	वापस माप(sas_pcd_m_pg);
पूर्ण

अटल पूर्णांक resp_sas_sha_m_spg(अचिन्हित अक्षर *p, पूर्णांक pcontrol)
अणु	/* SAS SSP shared protocol specअगरic port mode subpage */
	अचिन्हित अक्षर sas_sha_m_pg[] = अणु0x59, 0x2, 0, 0xc, 0, 0x6, 0x10, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		पूर्ण;

	स_नकल(p, sas_sha_m_pg, माप(sas_sha_m_pg));
	अगर (1 == pcontrol)
		स_रखो(p + 4, 0, माप(sas_sha_m_pg) - 4);
	वापस माप(sas_sha_m_pg);
पूर्ण

#घोषणा SDEBUG_MAX_MSENSE_SZ 256

अटल पूर्णांक resp_mode_sense(काष्ठा scsi_cmnd *scp,
			   काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक pcontrol, pcode, subpcode, bd_len;
	अचिन्हित अक्षर dev_spec;
	पूर्णांक alloc_len, offset, len, target_dev_id;
	पूर्णांक target = scp->device->id;
	अचिन्हित अक्षर *ap;
	अचिन्हित अक्षर arr[SDEBUG_MAX_MSENSE_SZ];
	अचिन्हित अक्षर *cmd = scp->cmnd;
	bool dbd, llbaa, msense_6, is_disk, is_zbc, bad_pcode;

	dbd = !!(cmd[1] & 0x8);		/* disable block descriptors */
	pcontrol = (cmd[2] & 0xc0) >> 6;
	pcode = cmd[2] & 0x3f;
	subpcode = cmd[3];
	msense_6 = (MODE_SENSE == cmd[0]);
	llbaa = msense_6 ? false : !!(cmd[1] & 0x10);
	is_disk = (sdebug_ptype == TYPE_DISK);
	is_zbc = (devip->zmodel != BLK_ZONED_NONE);
	अगर ((is_disk || is_zbc) && !dbd)
		bd_len = llbaa ? 16 : 8;
	अन्यथा
		bd_len = 0;
	alloc_len = msense_6 ? cmd[4] : get_unaligned_be16(cmd + 7);
	स_रखो(arr, 0, SDEBUG_MAX_MSENSE_SZ);
	अगर (0x3 == pcontrol) अणु  /* Saving values not supported */
		mk_sense_buffer(scp, ILLEGAL_REQUEST, SAVING_PARAMS_UNSUP, 0);
		वापस check_condition_result;
	पूर्ण
	target_dev_id = ((devip->sdbg_host->shost->host_no + 1) * 2000) +
			(devip->target * 1000) - 3;
	/* क्रम disks+zbc set DPOFUA bit and clear ग_लिखो protect (WP) bit */
	अगर (is_disk || is_zbc) अणु
		dev_spec = 0x10;	/* =0x90 अगर WP=1 implies पढ़ो-only */
		अगर (sdebug_wp)
			dev_spec |= 0x80;
	पूर्ण अन्यथा
		dev_spec = 0x0;
	अगर (msense_6) अणु
		arr[2] = dev_spec;
		arr[3] = bd_len;
		offset = 4;
	पूर्ण अन्यथा अणु
		arr[3] = dev_spec;
		अगर (16 == bd_len)
			arr[4] = 0x1;	/* set LONGLBA bit */
		arr[7] = bd_len;	/* assume 255 or less */
		offset = 8;
	पूर्ण
	ap = arr + offset;
	अगर ((bd_len > 0) && (!sdebug_capacity))
		sdebug_capacity = get_sdebug_capacity();

	अगर (8 == bd_len) अणु
		अगर (sdebug_capacity > 0xfffffffe)
			put_unaligned_be32(0xffffffff, ap + 0);
		अन्यथा
			put_unaligned_be32(sdebug_capacity, ap + 0);
		put_unaligned_be16(sdebug_sector_size, ap + 6);
		offset += bd_len;
		ap = arr + offset;
	पूर्ण अन्यथा अगर (16 == bd_len) अणु
		put_unaligned_be64((u64)sdebug_capacity, ap + 0);
		put_unaligned_be32(sdebug_sector_size, ap + 12);
		offset += bd_len;
		ap = arr + offset;
	पूर्ण

	अगर ((subpcode > 0x0) && (subpcode < 0xff) && (0x19 != pcode)) अणु
		/* TODO: Control Extension page */
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 3, -1);
		वापस check_condition_result;
	पूर्ण
	bad_pcode = false;

	चयन (pcode) अणु
	हाल 0x1:	/* Read-Write error recovery page, direct access */
		len = resp_err_recov_pg(ap, pcontrol, target);
		offset += len;
		अवरोध;
	हाल 0x2:	/* Disconnect-Reconnect page, all devices */
		len = resp_disconnect_pg(ap, pcontrol, target);
		offset += len;
		अवरोध;
	हाल 0x3:       /* Format device page, direct access */
		अगर (is_disk) अणु
			len = resp_क्रमmat_pg(ap, pcontrol, target);
			offset += len;
		पूर्ण अन्यथा
			bad_pcode = true;
		अवरोध;
	हाल 0x8:	/* Caching page, direct access */
		अगर (is_disk || is_zbc) अणु
			len = resp_caching_pg(ap, pcontrol, target);
			offset += len;
		पूर्ण अन्यथा
			bad_pcode = true;
		अवरोध;
	हाल 0xa:	/* Control Mode page, all devices */
		len = resp_ctrl_m_pg(ap, pcontrol, target);
		offset += len;
		अवरोध;
	हाल 0x19:	/* अगर spc==1 then sas phy, control+discover */
		अगर ((subpcode > 0x2) && (subpcode < 0xff)) अणु
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 3, -1);
			वापस check_condition_result;
		पूर्ण
		len = 0;
		अगर ((0x0 == subpcode) || (0xff == subpcode))
			len += resp_sas_sf_m_pg(ap + len, pcontrol, target);
		अगर ((0x1 == subpcode) || (0xff == subpcode))
			len += resp_sas_pcd_m_spg(ap + len, pcontrol, target,
						  target_dev_id);
		अगर ((0x2 == subpcode) || (0xff == subpcode))
			len += resp_sas_sha_m_spg(ap + len, pcontrol);
		offset += len;
		अवरोध;
	हाल 0x1c:	/* Inक्रमmational Exceptions Mode page, all devices */
		len = resp_iec_m_pg(ap, pcontrol, target);
		offset += len;
		अवरोध;
	हाल 0x3f:	/* Read all Mode pages */
		अगर ((0 == subpcode) || (0xff == subpcode)) अणु
			len = resp_err_recov_pg(ap, pcontrol, target);
			len += resp_disconnect_pg(ap + len, pcontrol, target);
			अगर (is_disk) अणु
				len += resp_क्रमmat_pg(ap + len, pcontrol,
						      target);
				len += resp_caching_pg(ap + len, pcontrol,
						       target);
			पूर्ण अन्यथा अगर (is_zbc) अणु
				len += resp_caching_pg(ap + len, pcontrol,
						       target);
			पूर्ण
			len += resp_ctrl_m_pg(ap + len, pcontrol, target);
			len += resp_sas_sf_m_pg(ap + len, pcontrol, target);
			अगर (0xff == subpcode) अणु
				len += resp_sas_pcd_m_spg(ap + len, pcontrol,
						  target, target_dev_id);
				len += resp_sas_sha_m_spg(ap + len, pcontrol);
			पूर्ण
			len += resp_iec_m_pg(ap + len, pcontrol, target);
			offset += len;
		पूर्ण अन्यथा अणु
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 3, -1);
			वापस check_condition_result;
		पूर्ण
		अवरोध;
	शेष:
		bad_pcode = true;
		अवरोध;
	पूर्ण
	अगर (bad_pcode) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, 5);
		वापस check_condition_result;
	पूर्ण
	अगर (msense_6)
		arr[0] = offset - 1;
	अन्यथा
		put_unaligned_be16((offset - 2), arr + 0);
	वापस fill_from_dev_buffer(scp, arr, min_t(पूर्णांक, alloc_len, offset));
पूर्ण

#घोषणा SDEBUG_MAX_MSELECT_SZ 512

अटल पूर्णांक resp_mode_select(काष्ठा scsi_cmnd *scp,
			    काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक pf, sp, ps, md_len, bd_len, off, spf, pg_len;
	पूर्णांक param_len, res, mpage;
	अचिन्हित अक्षर arr[SDEBUG_MAX_MSELECT_SZ];
	अचिन्हित अक्षर *cmd = scp->cmnd;
	पूर्णांक mselect6 = (MODE_SELECT == cmd[0]);

	स_रखो(arr, 0, माप(arr));
	pf = cmd[1] & 0x10;
	sp = cmd[1] & 0x1;
	param_len = mselect6 ? cmd[4] : get_unaligned_be16(cmd + 7);
	अगर ((0 == pf) || sp || (param_len > SDEBUG_MAX_MSELECT_SZ)) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, mselect6 ? 4 : 7, -1);
		वापस check_condition_result;
	पूर्ण
	res = fetch_to_dev_buffer(scp, arr, param_len);
	अगर (-1 == res)
		वापस DID_ERROR << 16;
	अन्यथा अगर (sdebug_verbose && (res < param_len))
		sdev_prपूर्णांकk(KERN_INFO, scp->device,
			    "%s: cdb indicated=%d, IO sent=%d bytes\n",
			    __func__, param_len, res);
	md_len = mselect6 ? (arr[0] + 1) : (get_unaligned_be16(arr + 0) + 2);
	bd_len = mselect6 ? arr[3] : get_unaligned_be16(arr + 6);
	अगर (md_len > 2) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_DATA, 0, -1);
		वापस check_condition_result;
	पूर्ण
	off = bd_len + (mselect6 ? 4 : 8);
	mpage = arr[off] & 0x3f;
	ps = !!(arr[off] & 0x80);
	अगर (ps) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_DATA, off, 7);
		वापस check_condition_result;
	पूर्ण
	spf = !!(arr[off] & 0x40);
	pg_len = spf ? (get_unaligned_be16(arr + off + 2) + 4) :
		       (arr[off + 1] + 2);
	अगर ((pg_len + off) > param_len) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST,
				PARAMETER_LIST_LENGTH_ERR, 0);
		वापस check_condition_result;
	पूर्ण
	चयन (mpage) अणु
	हाल 0x8:      /* Caching Mode page */
		अगर (caching_pg[1] == arr[off + 1]) अणु
			स_नकल(caching_pg + 2, arr + off + 2,
			       माप(caching_pg) - 2);
			जाओ set_mode_changed_ua;
		पूर्ण
		अवरोध;
	हाल 0xa:      /* Control Mode page */
		अगर (ctrl_m_pg[1] == arr[off + 1]) अणु
			स_नकल(ctrl_m_pg + 2, arr + off + 2,
			       माप(ctrl_m_pg) - 2);
			अगर (ctrl_m_pg[4] & 0x8)
				sdebug_wp = true;
			अन्यथा
				sdebug_wp = false;
			sdebug_dsense = !!(ctrl_m_pg[2] & 0x4);
			जाओ set_mode_changed_ua;
		पूर्ण
		अवरोध;
	हाल 0x1c:      /* Inक्रमmational Exceptions Mode page */
		अगर (iec_m_pg[1] == arr[off + 1]) अणु
			स_नकल(iec_m_pg + 2, arr + off + 2,
			       माप(iec_m_pg) - 2);
			जाओ set_mode_changed_ua;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mk_sense_invalid_fld(scp, SDEB_IN_DATA, off, 5);
	वापस check_condition_result;
set_mode_changed_ua:
	set_bit(SDEBUG_UA_MODE_CHANGED, devip->uas_bm);
	वापस 0;
पूर्ण

अटल पूर्णांक resp_temp_l_pg(अचिन्हित अक्षर *arr)
अणु
	अचिन्हित अक्षर temp_l_pg[] = अणु0x0, 0x0, 0x3, 0x2, 0x0, 38,
				     0x0, 0x1, 0x3, 0x2, 0x0, 65,
		पूर्ण;

	स_नकल(arr, temp_l_pg, माप(temp_l_pg));
	वापस माप(temp_l_pg);
पूर्ण

अटल पूर्णांक resp_ie_l_pg(अचिन्हित अक्षर *arr)
अणु
	अचिन्हित अक्षर ie_l_pg[] = अणु0x0, 0x0, 0x3, 0x3, 0x0, 0x0, 38,
		पूर्ण;

	स_नकल(arr, ie_l_pg, माप(ie_l_pg));
	अगर (iec_m_pg[2] & 0x4) अणु	/* TEST bit set */
		arr[4] = THRESHOLD_EXCEEDED;
		arr[5] = 0xff;
	पूर्ण
	वापस माप(ie_l_pg);
पूर्ण

#घोषणा SDEBUG_MAX_LSENSE_SZ 512

अटल पूर्णांक resp_log_sense(काष्ठा scsi_cmnd *scp,
			  काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक ppc, sp, pcode, subpcode, alloc_len, len, n;
	अचिन्हित अक्षर arr[SDEBUG_MAX_LSENSE_SZ];
	अचिन्हित अक्षर *cmd = scp->cmnd;

	स_रखो(arr, 0, माप(arr));
	ppc = cmd[1] & 0x2;
	sp = cmd[1] & 0x1;
	अगर (ppc || sp) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 1, ppc ? 1 : 0);
		वापस check_condition_result;
	पूर्ण
	pcode = cmd[2] & 0x3f;
	subpcode = cmd[3] & 0xff;
	alloc_len = get_unaligned_be16(cmd + 7);
	arr[0] = pcode;
	अगर (0 == subpcode) अणु
		चयन (pcode) अणु
		हाल 0x0:	/* Supported log pages log page */
			n = 4;
			arr[n++] = 0x0;		/* this page */
			arr[n++] = 0xd;		/* Temperature */
			arr[n++] = 0x2f;	/* Inक्रमmational exceptions */
			arr[3] = n - 4;
			अवरोध;
		हाल 0xd:	/* Temperature log page */
			arr[3] = resp_temp_l_pg(arr + 4);
			अवरोध;
		हाल 0x2f:	/* Inक्रमmational exceptions log page */
			arr[3] = resp_ie_l_pg(arr + 4);
			अवरोध;
		शेष:
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, 5);
			वापस check_condition_result;
		पूर्ण
	पूर्ण अन्यथा अगर (0xff == subpcode) अणु
		arr[0] |= 0x40;
		arr[1] = subpcode;
		चयन (pcode) अणु
		हाल 0x0:	/* Supported log pages and subpages log page */
			n = 4;
			arr[n++] = 0x0;
			arr[n++] = 0x0;		/* 0,0 page */
			arr[n++] = 0x0;
			arr[n++] = 0xff;	/* this page */
			arr[n++] = 0xd;
			arr[n++] = 0x0;		/* Temperature */
			arr[n++] = 0x2f;
			arr[n++] = 0x0;	/* Inक्रमmational exceptions */
			arr[3] = n - 4;
			अवरोध;
		हाल 0xd:	/* Temperature subpages */
			n = 4;
			arr[n++] = 0xd;
			arr[n++] = 0x0;		/* Temperature */
			arr[3] = n - 4;
			अवरोध;
		हाल 0x2f:	/* Inक्रमmational exceptions subpages */
			n = 4;
			arr[n++] = 0x2f;
			arr[n++] = 0x0;		/* Inक्रमmational exceptions */
			arr[3] = n - 4;
			अवरोध;
		शेष:
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, 5);
			वापस check_condition_result;
		पूर्ण
	पूर्ण अन्यथा अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 3, -1);
		वापस check_condition_result;
	पूर्ण
	len = min_t(पूर्णांक, get_unaligned_be16(arr + 2) + 4, alloc_len);
	वापस fill_from_dev_buffer(scp, arr,
		    min_t(पूर्णांक, len, SDEBUG_MAX_INQ_ARR_SZ));
पूर्ण

अटल अंतरभूत bool sdebug_dev_is_zoned(काष्ठा sdebug_dev_info *devip)
अणु
	वापस devip->nr_zones != 0;
पूर्ण

अटल काष्ठा sdeb_zone_state *zbc_zone(काष्ठा sdebug_dev_info *devip,
					अचिन्हित दीर्घ दीर्घ lba)
अणु
	वापस &devip->zstate[lba >> devip->zsize_shअगरt];
पूर्ण

अटल अंतरभूत bool zbc_zone_is_conv(काष्ठा sdeb_zone_state *zsp)
अणु
	वापस zsp->z_type == ZBC_ZONE_TYPE_CNV;
पूर्ण

अटल व्योम zbc_बंद_zone(काष्ठा sdebug_dev_info *devip,
			   काष्ठा sdeb_zone_state *zsp)
अणु
	क्रमागत sdebug_z_cond zc;

	अगर (zbc_zone_is_conv(zsp))
		वापस;

	zc = zsp->z_cond;
	अगर (!(zc == ZC2_IMPLICIT_OPEN || zc == ZC3_EXPLICIT_OPEN))
		वापस;

	अगर (zc == ZC2_IMPLICIT_OPEN)
		devip->nr_imp_खोलो--;
	अन्यथा
		devip->nr_exp_खोलो--;

	अगर (zsp->z_wp == zsp->z_start) अणु
		zsp->z_cond = ZC1_EMPTY;
	पूर्ण अन्यथा अणु
		zsp->z_cond = ZC4_CLOSED;
		devip->nr_बंदd++;
	पूर्ण
पूर्ण

अटल व्योम zbc_बंद_imp_खोलो_zone(काष्ठा sdebug_dev_info *devip)
अणु
	काष्ठा sdeb_zone_state *zsp = &devip->zstate[0];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < devip->nr_zones; i++, zsp++) अणु
		अगर (zsp->z_cond == ZC2_IMPLICIT_OPEN) अणु
			zbc_बंद_zone(devip, zsp);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम zbc_खोलो_zone(काष्ठा sdebug_dev_info *devip,
			  काष्ठा sdeb_zone_state *zsp, bool explicit)
अणु
	क्रमागत sdebug_z_cond zc;

	अगर (zbc_zone_is_conv(zsp))
		वापस;

	zc = zsp->z_cond;
	अगर ((explicit && zc == ZC3_EXPLICIT_OPEN) ||
	    (!explicit && zc == ZC2_IMPLICIT_OPEN))
		वापस;

	/* Close an implicit खोलो zone अगर necessary */
	अगर (explicit && zsp->z_cond == ZC2_IMPLICIT_OPEN)
		zbc_बंद_zone(devip, zsp);
	अन्यथा अगर (devip->max_खोलो &&
		 devip->nr_imp_खोलो + devip->nr_exp_खोलो >= devip->max_खोलो)
		zbc_बंद_imp_खोलो_zone(devip);

	अगर (zsp->z_cond == ZC4_CLOSED)
		devip->nr_बंदd--;
	अगर (explicit) अणु
		zsp->z_cond = ZC3_EXPLICIT_OPEN;
		devip->nr_exp_खोलो++;
	पूर्ण अन्यथा अणु
		zsp->z_cond = ZC2_IMPLICIT_OPEN;
		devip->nr_imp_खोलो++;
	पूर्ण
पूर्ण

अटल व्योम zbc_inc_wp(काष्ठा sdebug_dev_info *devip,
		       अचिन्हित दीर्घ दीर्घ lba, अचिन्हित पूर्णांक num)
अणु
	काष्ठा sdeb_zone_state *zsp = zbc_zone(devip, lba);
	अचिन्हित दीर्घ दीर्घ n, end, zend = zsp->z_start + zsp->z_size;

	अगर (zbc_zone_is_conv(zsp))
		वापस;

	अगर (zsp->z_type == ZBC_ZONE_TYPE_SWR) अणु
		zsp->z_wp += num;
		अगर (zsp->z_wp >= zend)
			zsp->z_cond = ZC5_FULL;
		वापस;
	पूर्ण

	जबतक (num) अणु
		अगर (lba != zsp->z_wp)
			zsp->z_non_seq_resource = true;

		end = lba + num;
		अगर (end >= zend) अणु
			n = zend - lba;
			zsp->z_wp = zend;
		पूर्ण अन्यथा अगर (end > zsp->z_wp) अणु
			n = num;
			zsp->z_wp = end;
		पूर्ण अन्यथा अणु
			n = num;
		पूर्ण
		अगर (zsp->z_wp >= zend)
			zsp->z_cond = ZC5_FULL;

		num -= n;
		lba += n;
		अगर (num) अणु
			zsp++;
			zend = zsp->z_start + zsp->z_size;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक check_zbc_access_params(काष्ठा scsi_cmnd *scp,
			अचिन्हित दीर्घ दीर्घ lba, अचिन्हित पूर्णांक num, bool ग_लिखो)
अणु
	काष्ठा scsi_device *sdp = scp->device;
	काष्ठा sdebug_dev_info *devip = (काष्ठा sdebug_dev_info *)sdp->hostdata;
	काष्ठा sdeb_zone_state *zsp = zbc_zone(devip, lba);
	काष्ठा sdeb_zone_state *zsp_end = zbc_zone(devip, lba + num - 1);

	अगर (!ग_लिखो) अणु
		अगर (devip->zmodel == BLK_ZONED_HA)
			वापस 0;
		/* For host-managed, पढ़ोs cannot cross zone types boundaries */
		अगर (zsp_end != zsp &&
		    zbc_zone_is_conv(zsp) &&
		    !zbc_zone_is_conv(zsp_end)) अणु
			mk_sense_buffer(scp, ILLEGAL_REQUEST,
					LBA_OUT_OF_RANGE,
					READ_INVDATA_ASCQ);
			वापस check_condition_result;
		पूर्ण
		वापस 0;
	पूर्ण

	/* No restrictions क्रम ग_लिखोs within conventional zones */
	अगर (zbc_zone_is_conv(zsp)) अणु
		अगर (!zbc_zone_is_conv(zsp_end)) अणु
			mk_sense_buffer(scp, ILLEGAL_REQUEST,
					LBA_OUT_OF_RANGE,
					WRITE_BOUNDARY_ASCQ);
			वापस check_condition_result;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (zsp->z_type == ZBC_ZONE_TYPE_SWR) अणु
		/* Writes cannot cross sequential zone boundaries */
		अगर (zsp_end != zsp) अणु
			mk_sense_buffer(scp, ILLEGAL_REQUEST,
					LBA_OUT_OF_RANGE,
					WRITE_BOUNDARY_ASCQ);
			वापस check_condition_result;
		पूर्ण
		/* Cannot ग_लिखो full zones */
		अगर (zsp->z_cond == ZC5_FULL) अणु
			mk_sense_buffer(scp, ILLEGAL_REQUEST,
					INVALID_FIELD_IN_CDB, 0);
			वापस check_condition_result;
		पूर्ण
		/* Writes must be aligned to the zone WP */
		अगर (lba != zsp->z_wp) अणु
			mk_sense_buffer(scp, ILLEGAL_REQUEST,
					LBA_OUT_OF_RANGE,
					UNALIGNED_WRITE_ASCQ);
			वापस check_condition_result;
		पूर्ण
	पूर्ण

	/* Handle implicit खोलो of बंदd and empty zones */
	अगर (zsp->z_cond == ZC1_EMPTY || zsp->z_cond == ZC4_CLOSED) अणु
		अगर (devip->max_खोलो &&
		    devip->nr_exp_खोलो >= devip->max_खोलो) अणु
			mk_sense_buffer(scp, DATA_PROTECT,
					INSUFF_RES_ASC,
					INSUFF_ZONE_ASCQ);
			वापस check_condition_result;
		पूर्ण
		zbc_खोलो_zone(devip, zsp, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_device_access_params
			(काष्ठा scsi_cmnd *scp, अचिन्हित दीर्घ दीर्घ lba,
			 अचिन्हित पूर्णांक num, bool ग_लिखो)
अणु
	काष्ठा scsi_device *sdp = scp->device;
	काष्ठा sdebug_dev_info *devip = (काष्ठा sdebug_dev_info *)sdp->hostdata;

	अगर (lba + num > sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		वापस check_condition_result;
	पूर्ण
	/* transfer length excessive (tie in to block limits VPD page) */
	अगर (num > sdebug_store_sectors) अणु
		/* needs work to find which cdb byte 'num' comes from */
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		वापस check_condition_result;
	पूर्ण
	अगर (ग_लिखो && unlikely(sdebug_wp)) अणु
		mk_sense_buffer(scp, DATA_PROTECT, WRITE_PROTECTED, 0x2);
		वापस check_condition_result;
	पूर्ण
	अगर (sdebug_dev_is_zoned(devip))
		वापस check_zbc_access_params(scp, lba, num, ग_लिखो);

	वापस 0;
पूर्ण

/*
 * Note: अगर BUG_ON() fires it usually indicates a problem with the parser
 * tables. Perhaps a missing F_FAKE_RW or FF_MEDIA_IO flag. Response functions
 * that access any of the "stores" in काष्ठा sdeb_store_info should call this
 * function with bug_अगर_fake_rw set to true.
 */
अटल अंतरभूत काष्ठा sdeb_store_info *devip2sip(काष्ठा sdebug_dev_info *devip,
						bool bug_अगर_fake_rw)
अणु
	अगर (sdebug_fake_rw) अणु
		BUG_ON(bug_अगर_fake_rw);	/* See note above */
		वापस शून्य;
	पूर्ण
	वापस xa_load(per_store_ap, devip->sdbg_host->si_idx);
पूर्ण

/* Returns number of bytes copied or -1 अगर error. */
अटल पूर्णांक करो_device_access(काष्ठा sdeb_store_info *sip, काष्ठा scsi_cmnd *scp,
			    u32 sg_skip, u64 lba, u32 num, bool करो_ग_लिखो)
अणु
	पूर्णांक ret;
	u64 block, rest = 0;
	क्रमागत dma_data_direction dir;
	काष्ठा scsi_data_buffer *sdb = &scp->sdb;
	u8 *fsp;

	अगर (करो_ग_लिखो) अणु
		dir = DMA_TO_DEVICE;
		ग_लिखो_since_sync = true;
	पूर्ण अन्यथा अणु
		dir = DMA_FROM_DEVICE;
	पूर्ण

	अगर (!sdb->length || !sip)
		वापस 0;
	अगर (scp->sc_data_direction != dir)
		वापस -1;
	fsp = sip->storep;

	block = करो_भाग(lba, sdebug_store_sectors);
	अगर (block + num > sdebug_store_sectors)
		rest = block + num - sdebug_store_sectors;

	ret = sg_copy_buffer(sdb->table.sgl, sdb->table.nents,
		   fsp + (block * sdebug_sector_size),
		   (num - rest) * sdebug_sector_size, sg_skip, करो_ग_लिखो);
	अगर (ret != (num - rest) * sdebug_sector_size)
		वापस ret;

	अगर (rest) अणु
		ret += sg_copy_buffer(sdb->table.sgl, sdb->table.nents,
			    fsp, rest * sdebug_sector_size,
			    sg_skip + ((num - rest) * sdebug_sector_size),
			    करो_ग_लिखो);
	पूर्ण

	वापस ret;
पूर्ण

/* Returns number of bytes copied or -1 अगर error. */
अटल पूर्णांक करो_करोut_fetch(काष्ठा scsi_cmnd *scp, u32 num, u8 *करोutp)
अणु
	काष्ठा scsi_data_buffer *sdb = &scp->sdb;

	अगर (!sdb->length)
		वापस 0;
	अगर (scp->sc_data_direction != DMA_TO_DEVICE)
		वापस -1;
	वापस sg_copy_buffer(sdb->table.sgl, sdb->table.nents, करोutp,
			      num * sdebug_sector_size, 0, true);
पूर्ण

/* If sip->storep+lba compares equal to arr(num), then copy top half of
 * arr पूर्णांकo sip->storep+lba and वापस true. If comparison fails then
 * वापस false. */
अटल bool comp_ग_लिखो_worker(काष्ठा sdeb_store_info *sip, u64 lba, u32 num,
			      स्थिर u8 *arr, bool compare_only)
अणु
	bool res;
	u64 block, rest = 0;
	u32 store_blks = sdebug_store_sectors;
	u32 lb_size = sdebug_sector_size;
	u8 *fsp = sip->storep;

	block = करो_भाग(lba, store_blks);
	अगर (block + num > store_blks)
		rest = block + num - store_blks;

	res = !स_भेद(fsp + (block * lb_size), arr, (num - rest) * lb_size);
	अगर (!res)
		वापस res;
	अगर (rest)
		res = स_भेद(fsp, arr + ((num - rest) * lb_size),
			     rest * lb_size);
	अगर (!res)
		वापस res;
	अगर (compare_only)
		वापस true;
	arr += num * lb_size;
	स_नकल(fsp + (block * lb_size), arr, (num - rest) * lb_size);
	अगर (rest)
		स_नकल(fsp, arr + ((num - rest) * lb_size), rest * lb_size);
	वापस res;
पूर्ण

अटल __be16 dअगर_compute_csum(स्थिर व्योम *buf, पूर्णांक len)
अणु
	__be16 csum;

	अगर (sdebug_guard)
		csum = (__क्रमce __be16)ip_compute_csum(buf, len);
	अन्यथा
		csum = cpu_to_be16(crc_t10dअगर(buf, len));

	वापस csum;
पूर्ण

अटल पूर्णांक dअगर_verअगरy(काष्ठा t10_pi_tuple *sdt, स्थिर व्योम *data,
		      sector_t sector, u32 ei_lba)
अणु
	__be16 csum = dअगर_compute_csum(data, sdebug_sector_size);

	अगर (sdt->guard_tag != csum) अणु
		pr_err("GUARD check failed on sector %lu rcvd 0x%04x, data 0x%04x\n",
			(अचिन्हित दीर्घ)sector,
			be16_to_cpu(sdt->guard_tag),
			be16_to_cpu(csum));
		वापस 0x01;
	पूर्ण
	अगर (sdebug_dअगर == T10_PI_TYPE1_PROTECTION &&
	    be32_to_cpu(sdt->ref_tag) != (sector & 0xffffffff)) अणु
		pr_err("REF check failed on sector %lu\n",
			(अचिन्हित दीर्घ)sector);
		वापस 0x03;
	पूर्ण
	अगर (sdebug_dअगर == T10_PI_TYPE2_PROTECTION &&
	    be32_to_cpu(sdt->ref_tag) != ei_lba) अणु
		pr_err("REF check failed on sector %lu\n",
			(अचिन्हित दीर्घ)sector);
		वापस 0x03;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dअगर_copy_prot(काष्ठा scsi_cmnd *scp, sector_t sector,
			  अचिन्हित पूर्णांक sectors, bool पढ़ो)
अणु
	माप_प्रकार resid;
	व्योम *paddr;
	काष्ठा sdeb_store_info *sip = devip2sip((काष्ठा sdebug_dev_info *)
						scp->device->hostdata, true);
	काष्ठा t10_pi_tuple *dअगर_storep = sip->dअगर_storep;
	स्थिर व्योम *dअगर_store_end = dअगर_storep + sdebug_store_sectors;
	काष्ठा sg_mapping_iter miter;

	/* Bytes of protection data to copy पूर्णांकo sgl */
	resid = sectors * माप(*dअगर_storep);

	sg_miter_start(&miter, scsi_prot_sglist(scp),
		       scsi_prot_sg_count(scp), SG_MITER_ATOMIC |
		       (पढ़ो ? SG_MITER_TO_SG : SG_MITER_FROM_SG));

	जबतक (sg_miter_next(&miter) && resid > 0) अणु
		माप_प्रकार len = min_t(माप_प्रकार, miter.length, resid);
		व्योम *start = dअगर_store(sip, sector);
		माप_प्रकार rest = 0;

		अगर (dअगर_store_end < start + len)
			rest = start + len - dअगर_store_end;

		paddr = miter.addr;

		अगर (पढ़ो)
			स_नकल(paddr, start, len - rest);
		अन्यथा
			स_नकल(start, paddr, len - rest);

		अगर (rest) अणु
			अगर (पढ़ो)
				स_नकल(paddr + len - rest, dअगर_storep, rest);
			अन्यथा
				स_नकल(dअगर_storep, paddr + len - rest, rest);
		पूर्ण

		sector += len / माप(*dअगर_storep);
		resid -= len;
	पूर्ण
	sg_miter_stop(&miter);
पूर्ण

अटल पूर्णांक prot_verअगरy_पढ़ो(काष्ठा scsi_cmnd *scp, sector_t start_sec,
			    अचिन्हित पूर्णांक sectors, u32 ei_lba)
अणु
	अचिन्हित पूर्णांक i;
	sector_t sector;
	काष्ठा sdeb_store_info *sip = devip2sip((काष्ठा sdebug_dev_info *)
						scp->device->hostdata, true);
	काष्ठा t10_pi_tuple *sdt;

	क्रम (i = 0; i < sectors; i++, ei_lba++) अणु
		पूर्णांक ret;

		sector = start_sec + i;
		sdt = dअगर_store(sip, sector);

		अगर (sdt->app_tag == cpu_to_be16(0xffff))
			जारी;

		ret = dअगर_verअगरy(sdt, lba2fake_store(sip, sector), sector,
				 ei_lba);
		अगर (ret) अणु
			dअगर_errors++;
			वापस ret;
		पूर्ण
	पूर्ण

	dअगर_copy_prot(scp, start_sec, sectors, true);
	dix_पढ़ोs++;

	वापस 0;
पूर्ण

अटल पूर्णांक resp_पढ़ो_dt0(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	bool check_prot;
	u32 num;
	u32 ei_lba;
	पूर्णांक ret;
	u64 lba;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, true);
	rwlock_t *macc_lckp = sip ? &sip->macc_lck : &sdeb_fake_rw_lck;
	u8 *cmd = scp->cmnd;

	चयन (cmd[0]) अणु
	हाल READ_16:
		ei_lba = 0;
		lba = get_unaligned_be64(cmd + 2);
		num = get_unaligned_be32(cmd + 10);
		check_prot = true;
		अवरोध;
	हाल READ_10:
		ei_lba = 0;
		lba = get_unaligned_be32(cmd + 2);
		num = get_unaligned_be16(cmd + 7);
		check_prot = true;
		अवरोध;
	हाल READ_6:
		ei_lba = 0;
		lba = (u32)cmd[3] | (u32)cmd[2] << 8 |
		      (u32)(cmd[1] & 0x1f) << 16;
		num = (0 == cmd[4]) ? 256 : cmd[4];
		check_prot = true;
		अवरोध;
	हाल READ_12:
		ei_lba = 0;
		lba = get_unaligned_be32(cmd + 2);
		num = get_unaligned_be32(cmd + 6);
		check_prot = true;
		अवरोध;
	हाल XDWRITEREAD_10:
		ei_lba = 0;
		lba = get_unaligned_be32(cmd + 2);
		num = get_unaligned_be16(cmd + 7);
		check_prot = false;
		अवरोध;
	शेष:	/* assume READ(32) */
		lba = get_unaligned_be64(cmd + 12);
		ei_lba = get_unaligned_be32(cmd + 20);
		num = get_unaligned_be32(cmd + 28);
		check_prot = false;
		अवरोध;
	पूर्ण
	अगर (unlikely(have_dअगर_prot && check_prot)) अणु
		अगर (sdebug_dअगर == T10_PI_TYPE2_PROTECTION &&
		    (cmd[1] & 0xe0)) अणु
			mk_sense_invalid_opcode(scp);
			वापस check_condition_result;
		पूर्ण
		अगर ((sdebug_dअगर == T10_PI_TYPE1_PROTECTION ||
		     sdebug_dअगर == T10_PI_TYPE3_PROTECTION) &&
		    (cmd[1] & 0xe0) == 0)
			sdev_prपूर्णांकk(KERN_ERR, scp->device, "Unprotected RD "
				    "to DIF device\n");
	पूर्ण
	अगर (unlikely((sdebug_opts & SDEBUG_OPT_SHORT_TRANSFER) &&
		     atomic_पढ़ो(&sdeb_inject_pending))) अणु
		num /= 2;
		atomic_set(&sdeb_inject_pending, 0);
	पूर्ण

	ret = check_device_access_params(scp, lba, num, false);
	अगर (ret)
		वापस ret;
	अगर (unlikely((SDEBUG_OPT_MEDIUM_ERR & sdebug_opts) &&
		     (lba <= (sdebug_medium_error_start + sdebug_medium_error_count - 1)) &&
		     ((lba + num) > sdebug_medium_error_start))) अणु
		/* claim unrecoverable पढ़ो error */
		mk_sense_buffer(scp, MEDIUM_ERROR, UNRECOVERED_READ_ERR, 0);
		/* set info field and valid bit क्रम fixed descriptor */
		अगर (0x70 == (scp->sense_buffer[0] & 0x7f)) अणु
			scp->sense_buffer[0] |= 0x80;	/* Valid bit */
			ret = (lba < OPT_MEDIUM_ERR_ADDR)
			      ? OPT_MEDIUM_ERR_ADDR : (पूर्णांक)lba;
			put_unaligned_be32(ret, scp->sense_buffer + 3);
		पूर्ण
		scsi_set_resid(scp, scsi_bufflen(scp));
		वापस check_condition_result;
	पूर्ण

	पढ़ो_lock(macc_lckp);

	/* DIX + T10 DIF */
	अगर (unlikely(sdebug_dix && scsi_prot_sg_count(scp))) अणु
		पूर्णांक prot_ret = prot_verअगरy_पढ़ो(scp, lba, num, ei_lba);

		अगर (prot_ret) अणु
			पढ़ो_unlock(macc_lckp);
			mk_sense_buffer(scp, ABORTED_COMMAND, 0x10, prot_ret);
			वापस illegal_condition_result;
		पूर्ण
	पूर्ण

	ret = करो_device_access(sip, scp, 0, lba, num, false);
	पढ़ो_unlock(macc_lckp);
	अगर (unlikely(ret == -1))
		वापस DID_ERROR << 16;

	scsi_set_resid(scp, scsi_bufflen(scp) - ret);

	अगर (unlikely((sdebug_opts & SDEBUG_OPT_RECOV_DIF_DIX) &&
		     atomic_पढ़ो(&sdeb_inject_pending))) अणु
		अगर (sdebug_opts & SDEBUG_OPT_RECOVERED_ERR) अणु
			mk_sense_buffer(scp, RECOVERED_ERROR, THRESHOLD_EXCEEDED, 0);
			atomic_set(&sdeb_inject_pending, 0);
			वापस check_condition_result;
		पूर्ण अन्यथा अगर (sdebug_opts & SDEBUG_OPT_DIF_ERR) अणु
			/* Logical block guard check failed */
			mk_sense_buffer(scp, ABORTED_COMMAND, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			वापस illegal_condition_result;
		पूर्ण अन्यथा अगर (SDEBUG_OPT_DIX_ERR & sdebug_opts) अणु
			mk_sense_buffer(scp, ILLEGAL_REQUEST, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			वापस illegal_condition_result;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dump_sector(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i, j, n;

	pr_err(">>> Sector Dump <<<\n");
	क्रम (i = 0 ; i < len ; i += 16) अणु
		अक्षर b[128];

		क्रम (j = 0, n = 0; j < 16; j++) अणु
			अचिन्हित अक्षर c = buf[i+j];

			अगर (c >= 0x20 && c < 0x7e)
				n += scnम_लिखो(b + n, माप(b) - n,
					       " %c ", buf[i+j]);
			अन्यथा
				n += scnम_लिखो(b + n, माप(b) - n,
					       "%02x ", buf[i+j]);
		पूर्ण
		pr_err("%04d: %s\n", i, b);
	पूर्ण
पूर्ण

अटल पूर्णांक prot_verअगरy_ग_लिखो(काष्ठा scsi_cmnd *SCpnt, sector_t start_sec,
			     अचिन्हित पूर्णांक sectors, u32 ei_lba)
अणु
	पूर्णांक ret;
	काष्ठा t10_pi_tuple *sdt;
	व्योम *daddr;
	sector_t sector = start_sec;
	पूर्णांक ppage_offset;
	पूर्णांक dpage_offset;
	काष्ठा sg_mapping_iter diter;
	काष्ठा sg_mapping_iter piter;

	BUG_ON(scsi_sg_count(SCpnt) == 0);
	BUG_ON(scsi_prot_sg_count(SCpnt) == 0);

	sg_miter_start(&piter, scsi_prot_sglist(SCpnt),
			scsi_prot_sg_count(SCpnt),
			SG_MITER_ATOMIC | SG_MITER_FROM_SG);
	sg_miter_start(&diter, scsi_sglist(SCpnt), scsi_sg_count(SCpnt),
			SG_MITER_ATOMIC | SG_MITER_FROM_SG);

	/* For each protection page */
	जबतक (sg_miter_next(&piter)) अणु
		dpage_offset = 0;
		अगर (WARN_ON(!sg_miter_next(&diter))) अणु
			ret = 0x01;
			जाओ out;
		पूर्ण

		क्रम (ppage_offset = 0; ppage_offset < piter.length;
		     ppage_offset += माप(काष्ठा t10_pi_tuple)) अणु
			/* If we're at the end of the current
			 * data page advance to the next one
			 */
			अगर (dpage_offset >= diter.length) अणु
				अगर (WARN_ON(!sg_miter_next(&diter))) अणु
					ret = 0x01;
					जाओ out;
				पूर्ण
				dpage_offset = 0;
			पूर्ण

			sdt = piter.addr + ppage_offset;
			daddr = diter.addr + dpage_offset;

			ret = dअगर_verअगरy(sdt, daddr, sector, ei_lba);
			अगर (ret) अणु
				dump_sector(daddr, sdebug_sector_size);
				जाओ out;
			पूर्ण

			sector++;
			ei_lba++;
			dpage_offset += sdebug_sector_size;
		पूर्ण
		diter.consumed = dpage_offset;
		sg_miter_stop(&diter);
	पूर्ण
	sg_miter_stop(&piter);

	dअगर_copy_prot(SCpnt, start_sec, sectors, false);
	dix_ग_लिखोs++;

	वापस 0;

out:
	dअगर_errors++;
	sg_miter_stop(&diter);
	sg_miter_stop(&piter);
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ lba_to_map_index(sector_t lba)
अणु
	अगर (sdebug_unmap_alignment)
		lba += sdebug_unmap_granularity - sdebug_unmap_alignment;
	sector_भाग(lba, sdebug_unmap_granularity);
	वापस lba;
पूर्ण

अटल sector_t map_index_to_lba(अचिन्हित दीर्घ index)
अणु
	sector_t lba = index * sdebug_unmap_granularity;

	अगर (sdebug_unmap_alignment)
		lba -= sdebug_unmap_granularity - sdebug_unmap_alignment;
	वापस lba;
पूर्ण

अटल अचिन्हित पूर्णांक map_state(काष्ठा sdeb_store_info *sip, sector_t lba,
			      अचिन्हित पूर्णांक *num)
अणु
	sector_t end;
	अचिन्हित पूर्णांक mapped;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ next;

	index = lba_to_map_index(lba);
	mapped = test_bit(index, sip->map_storep);

	अगर (mapped)
		next = find_next_zero_bit(sip->map_storep, map_size, index);
	अन्यथा
		next = find_next_bit(sip->map_storep, map_size, index);

	end = min_t(sector_t, sdebug_store_sectors,  map_index_to_lba(next));
	*num = end - lba;
	वापस mapped;
पूर्ण

अटल व्योम map_region(काष्ठा sdeb_store_info *sip, sector_t lba,
		       अचिन्हित पूर्णांक len)
अणु
	sector_t end = lba + len;

	जबतक (lba < end) अणु
		अचिन्हित दीर्घ index = lba_to_map_index(lba);

		अगर (index < map_size)
			set_bit(index, sip->map_storep);

		lba = map_index_to_lba(index + 1);
	पूर्ण
पूर्ण

अटल व्योम unmap_region(काष्ठा sdeb_store_info *sip, sector_t lba,
			 अचिन्हित पूर्णांक len)
अणु
	sector_t end = lba + len;
	u8 *fsp = sip->storep;

	जबतक (lba < end) अणु
		अचिन्हित दीर्घ index = lba_to_map_index(lba);

		अगर (lba == map_index_to_lba(index) &&
		    lba + sdebug_unmap_granularity <= end &&
		    index < map_size) अणु
			clear_bit(index, sip->map_storep);
			अगर (sdebug_lbprz) अणु  /* क्रम LBPRZ=2 वापस 0xff_s */
				स_रखो(fsp + lba * sdebug_sector_size,
				       (sdebug_lbprz & 1) ? 0 : 0xff,
				       sdebug_sector_size *
				       sdebug_unmap_granularity);
			पूर्ण
			अगर (sip->dअगर_storep) अणु
				स_रखो(sip->dअगर_storep + lba, 0xff,
				       माप(*sip->dअगर_storep) *
				       sdebug_unmap_granularity);
			पूर्ण
		पूर्ण
		lba = map_index_to_lba(index + 1);
	पूर्ण
पूर्ण

अटल पूर्णांक resp_ग_लिखो_dt0(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	bool check_prot;
	u32 num;
	u32 ei_lba;
	पूर्णांक ret;
	u64 lba;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, true);
	rwlock_t *macc_lckp = &sip->macc_lck;
	u8 *cmd = scp->cmnd;

	चयन (cmd[0]) अणु
	हाल WRITE_16:
		ei_lba = 0;
		lba = get_unaligned_be64(cmd + 2);
		num = get_unaligned_be32(cmd + 10);
		check_prot = true;
		अवरोध;
	हाल WRITE_10:
		ei_lba = 0;
		lba = get_unaligned_be32(cmd + 2);
		num = get_unaligned_be16(cmd + 7);
		check_prot = true;
		अवरोध;
	हाल WRITE_6:
		ei_lba = 0;
		lba = (u32)cmd[3] | (u32)cmd[2] << 8 |
		      (u32)(cmd[1] & 0x1f) << 16;
		num = (0 == cmd[4]) ? 256 : cmd[4];
		check_prot = true;
		अवरोध;
	हाल WRITE_12:
		ei_lba = 0;
		lba = get_unaligned_be32(cmd + 2);
		num = get_unaligned_be32(cmd + 6);
		check_prot = true;
		अवरोध;
	हाल 0x53:	/* XDWRITEREAD(10) */
		ei_lba = 0;
		lba = get_unaligned_be32(cmd + 2);
		num = get_unaligned_be16(cmd + 7);
		check_prot = false;
		अवरोध;
	शेष:	/* assume WRITE(32) */
		lba = get_unaligned_be64(cmd + 12);
		ei_lba = get_unaligned_be32(cmd + 20);
		num = get_unaligned_be32(cmd + 28);
		check_prot = false;
		अवरोध;
	पूर्ण
	अगर (unlikely(have_dअगर_prot && check_prot)) अणु
		अगर (sdebug_dअगर == T10_PI_TYPE2_PROTECTION &&
		    (cmd[1] & 0xe0)) अणु
			mk_sense_invalid_opcode(scp);
			वापस check_condition_result;
		पूर्ण
		अगर ((sdebug_dअगर == T10_PI_TYPE1_PROTECTION ||
		     sdebug_dअगर == T10_PI_TYPE3_PROTECTION) &&
		    (cmd[1] & 0xe0) == 0)
			sdev_prपूर्णांकk(KERN_ERR, scp->device, "Unprotected WR "
				    "to DIF device\n");
	पूर्ण

	ग_लिखो_lock(macc_lckp);
	ret = check_device_access_params(scp, lba, num, true);
	अगर (ret) अणु
		ग_लिखो_unlock(macc_lckp);
		वापस ret;
	पूर्ण

	/* DIX + T10 DIF */
	अगर (unlikely(sdebug_dix && scsi_prot_sg_count(scp))) अणु
		पूर्णांक prot_ret = prot_verअगरy_ग_लिखो(scp, lba, num, ei_lba);

		अगर (prot_ret) अणु
			ग_लिखो_unlock(macc_lckp);
			mk_sense_buffer(scp, ILLEGAL_REQUEST, 0x10, prot_ret);
			वापस illegal_condition_result;
		पूर्ण
	पूर्ण

	ret = करो_device_access(sip, scp, 0, lba, num, true);
	अगर (unlikely(scsi_debug_lbp()))
		map_region(sip, lba, num);
	/* If ZBC zone then bump its ग_लिखो poपूर्णांकer */
	अगर (sdebug_dev_is_zoned(devip))
		zbc_inc_wp(devip, lba, num);
	ग_लिखो_unlock(macc_lckp);
	अगर (unlikely(-1 == ret))
		वापस DID_ERROR << 16;
	अन्यथा अगर (unlikely(sdebug_verbose &&
			  (ret < (num * sdebug_sector_size))))
		sdev_prपूर्णांकk(KERN_INFO, scp->device,
			    "%s: write: cdb indicated=%u, IO sent=%d bytes\n",
			    my_name, num * sdebug_sector_size, ret);

	अगर (unlikely((sdebug_opts & SDEBUG_OPT_RECOV_DIF_DIX) &&
		     atomic_पढ़ो(&sdeb_inject_pending))) अणु
		अगर (sdebug_opts & SDEBUG_OPT_RECOVERED_ERR) अणु
			mk_sense_buffer(scp, RECOVERED_ERROR, THRESHOLD_EXCEEDED, 0);
			atomic_set(&sdeb_inject_pending, 0);
			वापस check_condition_result;
		पूर्ण अन्यथा अगर (sdebug_opts & SDEBUG_OPT_DIF_ERR) अणु
			/* Logical block guard check failed */
			mk_sense_buffer(scp, ABORTED_COMMAND, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			वापस illegal_condition_result;
		पूर्ण अन्यथा अगर (sdebug_opts & SDEBUG_OPT_DIX_ERR) अणु
			mk_sense_buffer(scp, ILLEGAL_REQUEST, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			वापस illegal_condition_result;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * T10 has only specअगरied WRITE SCATTERED(16) and WRITE SCATTERED(32).
 * No READ GATHERED yet (requires bidi or दीर्घ cdb holding gather list).
 */
अटल पूर्णांक resp_ग_लिखो_scat(काष्ठा scsi_cmnd *scp,
			   काष्ठा sdebug_dev_info *devip)
अणु
	u8 *cmd = scp->cmnd;
	u8 *lrdp = शून्य;
	u8 *up;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, true);
	rwlock_t *macc_lckp = &sip->macc_lck;
	u8 wrprotect;
	u16 lbकरोf, num_lrd, k;
	u32 num, num_by, bt_len, lbकरोf_blen, sg_off, cum_lb;
	u32 lb_size = sdebug_sector_size;
	u32 ei_lba;
	u64 lba;
	पूर्णांक ret, res;
	bool is_16;
	अटल स्थिर u32 lrd_size = 32; /* + parameter list header size */

	अगर (cmd[0] == VARIABLE_LENGTH_CMD) अणु
		is_16 = false;
		wrprotect = (cmd[10] >> 5) & 0x7;
		lbकरोf = get_unaligned_be16(cmd + 12);
		num_lrd = get_unaligned_be16(cmd + 16);
		bt_len = get_unaligned_be32(cmd + 28);
	पूर्ण अन्यथा अणु        /* that leaves WRITE SCATTERED(16) */
		is_16 = true;
		wrprotect = (cmd[2] >> 5) & 0x7;
		lbकरोf = get_unaligned_be16(cmd + 4);
		num_lrd = get_unaligned_be16(cmd + 8);
		bt_len = get_unaligned_be32(cmd + 10);
		अगर (unlikely(have_dअगर_prot)) अणु
			अगर (sdebug_dअगर == T10_PI_TYPE2_PROTECTION &&
			    wrprotect) अणु
				mk_sense_invalid_opcode(scp);
				वापस illegal_condition_result;
			पूर्ण
			अगर ((sdebug_dअगर == T10_PI_TYPE1_PROTECTION ||
			     sdebug_dअगर == T10_PI_TYPE3_PROTECTION) &&
			     wrprotect == 0)
				sdev_prपूर्णांकk(KERN_ERR, scp->device,
					    "Unprotected WR to DIF device\n");
		पूर्ण
	पूर्ण
	अगर ((num_lrd == 0) || (bt_len == 0))
		वापस 0;       /* T10 says these करो-nothings are not errors */
	अगर (lbकरोf == 0) अणु
		अगर (sdebug_verbose)
			sdev_prपूर्णांकk(KERN_INFO, scp->device,
				"%s: %s: LB Data Offset field bad\n",
				my_name, __func__);
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		वापस illegal_condition_result;
	पूर्ण
	lbकरोf_blen = lbकरोf * lb_size;
	अगर ((lrd_size + (num_lrd * lrd_size)) > lbकरोf_blen) अणु
		अगर (sdebug_verbose)
			sdev_prपूर्णांकk(KERN_INFO, scp->device,
				"%s: %s: LBA range descriptors don't fit\n",
				my_name, __func__);
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		वापस illegal_condition_result;
	पूर्ण
	lrdp = kzalloc(lbकरोf_blen, GFP_ATOMIC);
	अगर (lrdp == शून्य)
		वापस SCSI_MLQUEUE_HOST_BUSY;
	अगर (sdebug_verbose)
		sdev_prपूर्णांकk(KERN_INFO, scp->device,
			"%s: %s: Fetch header+scatter_list, lbdof_blen=%u\n",
			my_name, __func__, lbकरोf_blen);
	res = fetch_to_dev_buffer(scp, lrdp, lbकरोf_blen);
	अगर (res == -1) अणु
		ret = DID_ERROR << 16;
		जाओ err_out;
	पूर्ण

	ग_लिखो_lock(macc_lckp);
	sg_off = lbकरोf_blen;
	/* Spec says Buffer xfer Length field in number of LBs in करोut */
	cum_lb = 0;
	क्रम (k = 0, up = lrdp + lrd_size; k < num_lrd; ++k, up += lrd_size) अणु
		lba = get_unaligned_be64(up + 0);
		num = get_unaligned_be32(up + 8);
		अगर (sdebug_verbose)
			sdev_prपूर्णांकk(KERN_INFO, scp->device,
				"%s: %s: k=%d  LBA=0x%llx num=%u  sg_off=%u\n",
				my_name, __func__, k, lba, num, sg_off);
		अगर (num == 0)
			जारी;
		ret = check_device_access_params(scp, lba, num, true);
		अगर (ret)
			जाओ err_out_unlock;
		num_by = num * lb_size;
		ei_lba = is_16 ? 0 : get_unaligned_be32(up + 12);

		अगर ((cum_lb + num) > bt_len) अणु
			अगर (sdebug_verbose)
				sdev_prपूर्णांकk(KERN_INFO, scp->device,
				    "%s: %s: sum of blocks > data provided\n",
				    my_name, __func__);
			mk_sense_buffer(scp, ILLEGAL_REQUEST, WRITE_ERROR_ASC,
					0);
			ret = illegal_condition_result;
			जाओ err_out_unlock;
		पूर्ण

		/* DIX + T10 DIF */
		अगर (unlikely(sdebug_dix && scsi_prot_sg_count(scp))) अणु
			पूर्णांक prot_ret = prot_verअगरy_ग_लिखो(scp, lba, num,
							 ei_lba);

			अगर (prot_ret) अणु
				mk_sense_buffer(scp, ILLEGAL_REQUEST, 0x10,
						prot_ret);
				ret = illegal_condition_result;
				जाओ err_out_unlock;
			पूर्ण
		पूर्ण

		ret = करो_device_access(sip, scp, sg_off, lba, num, true);
		/* If ZBC zone then bump its ग_लिखो poपूर्णांकer */
		अगर (sdebug_dev_is_zoned(devip))
			zbc_inc_wp(devip, lba, num);
		अगर (unlikely(scsi_debug_lbp()))
			map_region(sip, lba, num);
		अगर (unlikely(-1 == ret)) अणु
			ret = DID_ERROR << 16;
			जाओ err_out_unlock;
		पूर्ण अन्यथा अगर (unlikely(sdebug_verbose && (ret < num_by)))
			sdev_prपूर्णांकk(KERN_INFO, scp->device,
			    "%s: write: cdb indicated=%u, IO sent=%d bytes\n",
			    my_name, num_by, ret);

		अगर (unlikely((sdebug_opts & SDEBUG_OPT_RECOV_DIF_DIX) &&
			     atomic_पढ़ो(&sdeb_inject_pending))) अणु
			अगर (sdebug_opts & SDEBUG_OPT_RECOVERED_ERR) अणु
				mk_sense_buffer(scp, RECOVERED_ERROR, THRESHOLD_EXCEEDED, 0);
				atomic_set(&sdeb_inject_pending, 0);
				ret = check_condition_result;
				जाओ err_out_unlock;
			पूर्ण अन्यथा अगर (sdebug_opts & SDEBUG_OPT_DIF_ERR) अणु
				/* Logical block guard check failed */
				mk_sense_buffer(scp, ABORTED_COMMAND, 0x10, 1);
				atomic_set(&sdeb_inject_pending, 0);
				ret = illegal_condition_result;
				जाओ err_out_unlock;
			पूर्ण अन्यथा अगर (sdebug_opts & SDEBUG_OPT_DIX_ERR) अणु
				mk_sense_buffer(scp, ILLEGAL_REQUEST, 0x10, 1);
				atomic_set(&sdeb_inject_pending, 0);
				ret = illegal_condition_result;
				जाओ err_out_unlock;
			पूर्ण
		पूर्ण
		sg_off += num_by;
		cum_lb += num;
	पूर्ण
	ret = 0;
err_out_unlock:
	ग_लिखो_unlock(macc_lckp);
err_out:
	kमुक्त(lrdp);
	वापस ret;
पूर्ण

अटल पूर्णांक resp_ग_लिखो_same(काष्ठा scsi_cmnd *scp, u64 lba, u32 num,
			   u32 ei_lba, bool unmap, bool nकरोb)
अणु
	काष्ठा scsi_device *sdp = scp->device;
	काष्ठा sdebug_dev_info *devip = (काष्ठा sdebug_dev_info *)sdp->hostdata;
	अचिन्हित दीर्घ दीर्घ i;
	u64 block, lbaa;
	u32 lb_size = sdebug_sector_size;
	पूर्णांक ret;
	काष्ठा sdeb_store_info *sip = devip2sip((काष्ठा sdebug_dev_info *)
						scp->device->hostdata, true);
	rwlock_t *macc_lckp = &sip->macc_lck;
	u8 *fs1p;
	u8 *fsp;

	ग_लिखो_lock(macc_lckp);

	ret = check_device_access_params(scp, lba, num, true);
	अगर (ret) अणु
		ग_लिखो_unlock(macc_lckp);
		वापस ret;
	पूर्ण

	अगर (unmap && scsi_debug_lbp()) अणु
		unmap_region(sip, lba, num);
		जाओ out;
	पूर्ण
	lbaa = lba;
	block = करो_भाग(lbaa, sdebug_store_sectors);
	/* अगर nकरोb then zero 1 logical block, अन्यथा fetch 1 logical block */
	fsp = sip->storep;
	fs1p = fsp + (block * lb_size);
	अगर (nकरोb) अणु
		स_रखो(fs1p, 0, lb_size);
		ret = 0;
	पूर्ण अन्यथा
		ret = fetch_to_dev_buffer(scp, fs1p, lb_size);

	अगर (-1 == ret) अणु
		ग_लिखो_unlock(&sip->macc_lck);
		वापस DID_ERROR << 16;
	पूर्ण अन्यथा अगर (sdebug_verbose && !nकरोb && (ret < lb_size))
		sdev_prपूर्णांकk(KERN_INFO, scp->device,
			    "%s: %s: lb size=%u, IO sent=%d bytes\n",
			    my_name, "write same", lb_size, ret);

	/* Copy first sector to reमुख्यing blocks */
	क्रम (i = 1 ; i < num ; i++) अणु
		lbaa = lba + i;
		block = करो_भाग(lbaa, sdebug_store_sectors);
		स_हटाओ(fsp + (block * lb_size), fs1p, lb_size);
	पूर्ण
	अगर (scsi_debug_lbp())
		map_region(sip, lba, num);
	/* If ZBC zone then bump its ग_लिखो poपूर्णांकer */
	अगर (sdebug_dev_is_zoned(devip))
		zbc_inc_wp(devip, lba, num);
out:
	ग_लिखो_unlock(macc_lckp);

	वापस 0;
पूर्ण

अटल पूर्णांक resp_ग_लिखो_same_10(काष्ठा scsi_cmnd *scp,
			      काष्ठा sdebug_dev_info *devip)
अणु
	u8 *cmd = scp->cmnd;
	u32 lba;
	u16 num;
	u32 ei_lba = 0;
	bool unmap = false;

	अगर (cmd[1] & 0x8) अणु
		अगर (sdebug_lbpws10 == 0) अणु
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 1, 3);
			वापस check_condition_result;
		पूर्ण अन्यथा
			unmap = true;
	पूर्ण
	lba = get_unaligned_be32(cmd + 2);
	num = get_unaligned_be16(cmd + 7);
	अगर (num > sdebug_ग_लिखो_same_length) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 7, -1);
		वापस check_condition_result;
	पूर्ण
	वापस resp_ग_लिखो_same(scp, lba, num, ei_lba, unmap, false);
पूर्ण

अटल पूर्णांक resp_ग_लिखो_same_16(काष्ठा scsi_cmnd *scp,
			      काष्ठा sdebug_dev_info *devip)
अणु
	u8 *cmd = scp->cmnd;
	u64 lba;
	u32 num;
	u32 ei_lba = 0;
	bool unmap = false;
	bool nकरोb = false;

	अगर (cmd[1] & 0x8) अणु	/* UNMAP */
		अगर (sdebug_lbpws == 0) अणु
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 1, 3);
			वापस check_condition_result;
		पूर्ण अन्यथा
			unmap = true;
	पूर्ण
	अगर (cmd[1] & 0x1)  /* NDOB (no data-out buffer, assumes zeroes) */
		nकरोb = true;
	lba = get_unaligned_be64(cmd + 2);
	num = get_unaligned_be32(cmd + 10);
	अगर (num > sdebug_ग_लिखो_same_length) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 10, -1);
		वापस check_condition_result;
	पूर्ण
	वापस resp_ग_लिखो_same(scp, lba, num, ei_lba, unmap, nकरोb);
पूर्ण

/* Note the mode field is in the same position as the (lower) service action
 * field. For the Report supported operation codes command, SPC-4 suggests
 * each mode of this command should be reported separately; क्रम future. */
अटल पूर्णांक resp_ग_लिखो_buffer(काष्ठा scsi_cmnd *scp,
			     काष्ठा sdebug_dev_info *devip)
अणु
	u8 *cmd = scp->cmnd;
	काष्ठा scsi_device *sdp = scp->device;
	काष्ठा sdebug_dev_info *dp;
	u8 mode;

	mode = cmd[1] & 0x1f;
	चयन (mode) अणु
	हाल 0x4:	/* करोwnload microcode (MC) and activate (ACT) */
		/* set UAs on this device only */
		set_bit(SDEBUG_UA_BUS_RESET, devip->uas_bm);
		set_bit(SDEBUG_UA_MICROCODE_CHANGED, devip->uas_bm);
		अवरोध;
	हाल 0x5:	/* करोwnload MC, save and ACT */
		set_bit(SDEBUG_UA_MICROCODE_CHANGED_WO_RESET, devip->uas_bm);
		अवरोध;
	हाल 0x6:	/* करोwnload MC with offsets and ACT */
		/* set UAs on most devices (LUs) in this target */
		list_क्रम_each_entry(dp,
				    &devip->sdbg_host->dev_info_list,
				    dev_list)
			अगर (dp->target == sdp->id) अणु
				set_bit(SDEBUG_UA_BUS_RESET, dp->uas_bm);
				अगर (devip != dp)
					set_bit(SDEBUG_UA_MICROCODE_CHANGED,
						dp->uas_bm);
			पूर्ण
		अवरोध;
	हाल 0x7:	/* करोwnload MC with offsets, save, and ACT */
		/* set UA on all devices (LUs) in this target */
		list_क्रम_each_entry(dp,
				    &devip->sdbg_host->dev_info_list,
				    dev_list)
			अगर (dp->target == sdp->id)
				set_bit(SDEBUG_UA_MICROCODE_CHANGED_WO_RESET,
					dp->uas_bm);
		अवरोध;
	शेष:
		/* करो nothing क्रम this command क्रम other mode values */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक resp_comp_ग_लिखो(काष्ठा scsi_cmnd *scp,
			   काष्ठा sdebug_dev_info *devip)
अणु
	u8 *cmd = scp->cmnd;
	u8 *arr;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, true);
	rwlock_t *macc_lckp = &sip->macc_lck;
	u64 lba;
	u32 dnum;
	u32 lb_size = sdebug_sector_size;
	u8 num;
	पूर्णांक ret;
	पूर्णांक retval = 0;

	lba = get_unaligned_be64(cmd + 2);
	num = cmd[13];		/* 1 to a maximum of 255 logical blocks */
	अगर (0 == num)
		वापस 0;	/* degenerate हाल, not an error */
	अगर (sdebug_dअगर == T10_PI_TYPE2_PROTECTION &&
	    (cmd[1] & 0xe0)) अणु
		mk_sense_invalid_opcode(scp);
		वापस check_condition_result;
	पूर्ण
	अगर ((sdebug_dअगर == T10_PI_TYPE1_PROTECTION ||
	     sdebug_dअगर == T10_PI_TYPE3_PROTECTION) &&
	    (cmd[1] & 0xe0) == 0)
		sdev_prपूर्णांकk(KERN_ERR, scp->device, "Unprotected WR "
			    "to DIF device\n");
	ret = check_device_access_params(scp, lba, num, false);
	अगर (ret)
		वापस ret;
	dnum = 2 * num;
	arr = kसुस्मृति(lb_size, dnum, GFP_ATOMIC);
	अगर (शून्य == arr) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		वापस check_condition_result;
	पूर्ण

	ग_लिखो_lock(macc_lckp);

	ret = करो_करोut_fetch(scp, dnum, arr);
	अगर (ret == -1) अणु
		retval = DID_ERROR << 16;
		जाओ cleanup;
	पूर्ण अन्यथा अगर (sdebug_verbose && (ret < (dnum * lb_size)))
		sdev_prपूर्णांकk(KERN_INFO, scp->device, "%s: compare_write: cdb "
			    "indicated=%u, IO sent=%d bytes\n", my_name,
			    dnum * lb_size, ret);
	अगर (!comp_ग_लिखो_worker(sip, lba, num, arr, false)) अणु
		mk_sense_buffer(scp, MISCOMPARE, MISCOMPARE_VERIFY_ASC, 0);
		retval = check_condition_result;
		जाओ cleanup;
	पूर्ण
	अगर (scsi_debug_lbp())
		map_region(sip, lba, num);
cleanup:
	ग_लिखो_unlock(macc_lckp);
	kमुक्त(arr);
	वापस retval;
पूर्ण

काष्ठा unmap_block_desc अणु
	__be64	lba;
	__be32	blocks;
	__be32	__reserved;
पूर्ण;

अटल पूर्णांक resp_unmap(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर *buf;
	काष्ठा unmap_block_desc *desc;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, true);
	rwlock_t *macc_lckp = &sip->macc_lck;
	अचिन्हित पूर्णांक i, payload_len, descriptors;
	पूर्णांक ret;

	अगर (!scsi_debug_lbp())
		वापस 0;	/* fib and say its करोne */
	payload_len = get_unaligned_be16(scp->cmnd + 7);
	BUG_ON(scsi_bufflen(scp) != payload_len);

	descriptors = (payload_len - 8) / 16;
	अगर (descriptors > sdebug_unmap_max_desc) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 7, -1);
		वापस check_condition_result;
	पूर्ण

	buf = kzalloc(scsi_bufflen(scp), GFP_ATOMIC);
	अगर (!buf) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		वापस check_condition_result;
	पूर्ण

	scsi_sg_copy_to_buffer(scp, buf, scsi_bufflen(scp));

	BUG_ON(get_unaligned_be16(&buf[0]) != payload_len - 2);
	BUG_ON(get_unaligned_be16(&buf[2]) != descriptors * 16);

	desc = (व्योम *)&buf[8];

	ग_लिखो_lock(macc_lckp);

	क्रम (i = 0 ; i < descriptors ; i++) अणु
		अचिन्हित दीर्घ दीर्घ lba = get_unaligned_be64(&desc[i].lba);
		अचिन्हित पूर्णांक num = get_unaligned_be32(&desc[i].blocks);

		ret = check_device_access_params(scp, lba, num, true);
		अगर (ret)
			जाओ out;

		unmap_region(sip, lba, num);
	पूर्ण

	ret = 0;

out:
	ग_लिखो_unlock(macc_lckp);
	kमुक्त(buf);

	वापस ret;
पूर्ण

#घोषणा SDEBUG_GET_LBA_STATUS_LEN 32

अटल पूर्णांक resp_get_lba_status(काष्ठा scsi_cmnd *scp,
			       काष्ठा sdebug_dev_info *devip)
अणु
	u8 *cmd = scp->cmnd;
	u64 lba;
	u32 alloc_len, mapped, num;
	पूर्णांक ret;
	u8 arr[SDEBUG_GET_LBA_STATUS_LEN];

	lba = get_unaligned_be64(cmd + 2);
	alloc_len = get_unaligned_be32(cmd + 10);

	अगर (alloc_len < 24)
		वापस 0;

	ret = check_device_access_params(scp, lba, 1, false);
	अगर (ret)
		वापस ret;

	अगर (scsi_debug_lbp()) अणु
		काष्ठा sdeb_store_info *sip = devip2sip(devip, true);

		mapped = map_state(sip, lba, &num);
	पूर्ण अन्यथा अणु
		mapped = 1;
		/* following just in हाल भव_gb changed */
		sdebug_capacity = get_sdebug_capacity();
		अगर (sdebug_capacity - lba <= 0xffffffff)
			num = sdebug_capacity - lba;
		अन्यथा
			num = 0xffffffff;
	पूर्ण

	स_रखो(arr, 0, SDEBUG_GET_LBA_STATUS_LEN);
	put_unaligned_be32(20, arr);		/* Parameter Data Length */
	put_unaligned_be64(lba, arr + 8);	/* LBA */
	put_unaligned_be32(num, arr + 16);	/* Number of blocks */
	arr[20] = !mapped;		/* prov_stat=0: mapped; 1: dealloc */

	वापस fill_from_dev_buffer(scp, arr, SDEBUG_GET_LBA_STATUS_LEN);
पूर्ण

अटल पूर्णांक resp_sync_cache(काष्ठा scsi_cmnd *scp,
			   काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक res = 0;
	u64 lba;
	u32 num_blocks;
	u8 *cmd = scp->cmnd;

	अगर (cmd[0] == SYNCHRONIZE_CACHE) अणु	/* 10 byte cdb */
		lba = get_unaligned_be32(cmd + 2);
		num_blocks = get_unaligned_be16(cmd + 7);
	पूर्ण अन्यथा अणु				/* SYNCHRONIZE_CACHE(16) */
		lba = get_unaligned_be64(cmd + 2);
		num_blocks = get_unaligned_be32(cmd + 10);
	पूर्ण
	अगर (lba + num_blocks > sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		वापस check_condition_result;
	पूर्ण
	अगर (!ग_लिखो_since_sync || (cmd[1] & 0x2))
		res = SDEG_RES_IMMED_MASK;
	अन्यथा		/* delay अगर ग_लिखो_since_sync and IMMED clear */
		ग_लिखो_since_sync = false;
	वापस res;
पूर्ण

/*
 * Assuming the LBA+num_blocks is not out-of-range, this function will वापस
 * CONDITION MET अगर the specअगरied blocks will/have fitted in the cache, and
 * a GOOD status otherwise. Model a disk with a big cache and yield
 * CONDITION MET. Actually tries to bring range in मुख्य memory पूर्णांकo the
 * cache associated with the CPU(s).
 */
अटल पूर्णांक resp_pre_fetch(काष्ठा scsi_cmnd *scp,
			  काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक res = 0;
	u64 lba;
	u64 block, rest = 0;
	u32 nblks;
	u8 *cmd = scp->cmnd;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, true);
	rwlock_t *macc_lckp = &sip->macc_lck;
	u8 *fsp = sip->storep;

	अगर (cmd[0] == PRE_FETCH) अणु	/* 10 byte cdb */
		lba = get_unaligned_be32(cmd + 2);
		nblks = get_unaligned_be16(cmd + 7);
	पूर्ण अन्यथा अणु			/* PRE-FETCH(16) */
		lba = get_unaligned_be64(cmd + 2);
		nblks = get_unaligned_be32(cmd + 10);
	पूर्ण
	अगर (lba + nblks > sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		वापस check_condition_result;
	पूर्ण
	अगर (!fsp)
		जाओ fini;
	/* PRE-FETCH spec says nothing about LBP or PI so skip them */
	block = करो_भाग(lba, sdebug_store_sectors);
	अगर (block + nblks > sdebug_store_sectors)
		rest = block + nblks - sdebug_store_sectors;

	/* Try to bring the PRE-FETCH range पूर्णांकo CPU's cache */
	पढ़ो_lock(macc_lckp);
	prefetch_range(fsp + (sdebug_sector_size * block),
		       (nblks - rest) * sdebug_sector_size);
	अगर (rest)
		prefetch_range(fsp, rest * sdebug_sector_size);
	पढ़ो_unlock(macc_lckp);
fini:
	अगर (cmd[1] & 0x2)
		res = SDEG_RES_IMMED_MASK;
	वापस res | condition_met_result;
पूर्ण

#घोषणा RL_BUCKET_ELEMS 8

/* Even though each pseuकरो target has a REPORT LUNS "well known logical unit"
 * (W-LUN), the normal Linux scanning logic करोes not associate it with a
 * device (e.g. /dev/sg7). The following magic will make that association:
 *   "cd /sys/class/scsi_host/host<n> ; echo '- - 49409' > scan"
 * where <n> is a host number. If there are multiple tarमाला_लो in a host then
 * the above will associate a W-LUN to each target. To only get a W-LUN
 * क्रम target 2, then use "echo '- 2 49409' > scan" .
 */
अटल पूर्णांक resp_report_luns(काष्ठा scsi_cmnd *scp,
			    काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित अक्षर *cmd = scp->cmnd;
	अचिन्हित पूर्णांक alloc_len;
	अचिन्हित अक्षर select_report;
	u64 lun;
	काष्ठा scsi_lun *lun_p;
	u8 arr[RL_BUCKET_ELEMS * माप(काष्ठा scsi_lun)];
	अचिन्हित पूर्णांक lun_cnt;	/* normal LUN count (max: 256) */
	अचिन्हित पूर्णांक wlun_cnt;	/* report luns W-LUN count */
	अचिन्हित पूर्णांक tlun_cnt;	/* total LUN count */
	अचिन्हित पूर्णांक rlen;	/* response length (in bytes) */
	पूर्णांक k, j, n, res;
	अचिन्हित पूर्णांक off_rsp = 0;
	स्थिर पूर्णांक sz_lun = माप(काष्ठा scsi_lun);

	clear_luns_changed_on_target(devip);

	select_report = cmd[2];
	alloc_len = get_unaligned_be32(cmd + 6);

	अगर (alloc_len < 4) अणु
		pr_err("alloc len too small %d\n", alloc_len);
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 6, -1);
		वापस check_condition_result;
	पूर्ण

	चयन (select_report) अणु
	हाल 0:		/* all LUNs apart from W-LUNs */
		lun_cnt = sdebug_max_luns;
		wlun_cnt = 0;
		अवरोध;
	हाल 1:		/* only W-LUNs */
		lun_cnt = 0;
		wlun_cnt = 1;
		अवरोध;
	हाल 2:		/* all LUNs */
		lun_cnt = sdebug_max_luns;
		wlun_cnt = 1;
		अवरोध;
	हाल 0x10:	/* only administrative LUs */
	हाल 0x11:	/* see SPC-5 */
	हाल 0x12:	/* only subsiduary LUs owned by referenced LU */
	शेष:
		pr_debug("select report invalid %d\n", select_report);
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, -1);
		वापस check_condition_result;
	पूर्ण

	अगर (sdebug_no_lun_0 && (lun_cnt > 0))
		--lun_cnt;

	tlun_cnt = lun_cnt + wlun_cnt;
	rlen = tlun_cnt * sz_lun;	/* excluding 8 byte header */
	scsi_set_resid(scp, scsi_bufflen(scp));
	pr_debug("select_report %d luns = %d wluns = %d no_lun0 %d\n",
		 select_report, lun_cnt, wlun_cnt, sdebug_no_lun_0);

	/* loops rely on माप response header same as माप lun (both 8) */
	lun = sdebug_no_lun_0 ? 1 : 0;
	क्रम (k = 0, j = 0, res = 0; true; ++k, j = 0) अणु
		स_रखो(arr, 0, माप(arr));
		lun_p = (काष्ठा scsi_lun *)&arr[0];
		अगर (k == 0) अणु
			put_unaligned_be32(rlen, &arr[0]);
			++lun_p;
			j = 1;
		पूर्ण
		क्रम ( ; j < RL_BUCKET_ELEMS; ++j, ++lun_p) अणु
			अगर ((k * RL_BUCKET_ELEMS) + j > lun_cnt)
				अवरोध;
			पूर्णांक_to_scsilun(lun++, lun_p);
			अगर (lun > 1 && sdebug_lun_am == SAM_LUN_AM_FLAT)
				lun_p->scsi_lun[0] |= 0x40;
		पूर्ण
		अगर (j < RL_BUCKET_ELEMS)
			अवरोध;
		n = j * sz_lun;
		res = p_fill_from_dev_buffer(scp, arr, n, off_rsp);
		अगर (res)
			वापस res;
		off_rsp += n;
	पूर्ण
	अगर (wlun_cnt) अणु
		पूर्णांक_to_scsilun(SCSI_W_LUN_REPORT_LUNS, lun_p);
		++j;
	पूर्ण
	अगर (j > 0)
		res = p_fill_from_dev_buffer(scp, arr, j * sz_lun, off_rsp);
	वापस res;
पूर्ण

अटल पूर्णांक resp_verअगरy(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	bool is_bytchk3 = false;
	u8 bytchk;
	पूर्णांक ret, j;
	u32 vnum, a_num, off;
	स्थिर u32 lb_size = sdebug_sector_size;
	u64 lba;
	u8 *arr;
	u8 *cmd = scp->cmnd;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, true);
	rwlock_t *macc_lckp = &sip->macc_lck;

	bytchk = (cmd[1] >> 1) & 0x3;
	अगर (bytchk == 0) अणु
		वापस 0;	/* always claim पूर्णांकernal verअगरy okay */
	पूर्ण अन्यथा अगर (bytchk == 2) अणु
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, 2);
		वापस check_condition_result;
	पूर्ण अन्यथा अगर (bytchk == 3) अणु
		is_bytchk3 = true;	/* 1 block sent, compared repeatedly */
	पूर्ण
	चयन (cmd[0]) अणु
	हाल VERIFY_16:
		lba = get_unaligned_be64(cmd + 2);
		vnum = get_unaligned_be32(cmd + 10);
		अवरोध;
	हाल VERIFY:		/* is VERIFY(10) */
		lba = get_unaligned_be32(cmd + 2);
		vnum = get_unaligned_be16(cmd + 7);
		अवरोध;
	शेष:
		mk_sense_invalid_opcode(scp);
		वापस check_condition_result;
	पूर्ण
	a_num = is_bytchk3 ? 1 : vnum;
	/* Treat following check like one क्रम पढ़ो (i.e. no ग_लिखो) access */
	ret = check_device_access_params(scp, lba, a_num, false);
	अगर (ret)
		वापस ret;

	arr = kसुस्मृति(lb_size, vnum, GFP_ATOMIC);
	अगर (!arr) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		वापस check_condition_result;
	पूर्ण
	/* Not changing store, so only need पढ़ो access */
	पढ़ो_lock(macc_lckp);

	ret = करो_करोut_fetch(scp, a_num, arr);
	अगर (ret == -1) अणु
		ret = DID_ERROR << 16;
		जाओ cleanup;
	पूर्ण अन्यथा अगर (sdebug_verbose && (ret < (a_num * lb_size))) अणु
		sdev_prपूर्णांकk(KERN_INFO, scp->device,
			    "%s: %s: cdb indicated=%u, IO sent=%d bytes\n",
			    my_name, __func__, a_num * lb_size, ret);
	पूर्ण
	अगर (is_bytchk3) अणु
		क्रम (j = 1, off = lb_size; j < vnum; ++j, off += lb_size)
			स_नकल(arr + off, arr, lb_size);
	पूर्ण
	ret = 0;
	अगर (!comp_ग_लिखो_worker(sip, lba, vnum, arr, true)) अणु
		mk_sense_buffer(scp, MISCOMPARE, MISCOMPARE_VERIFY_ASC, 0);
		ret = check_condition_result;
		जाओ cleanup;
	पूर्ण
cleanup:
	पढ़ो_unlock(macc_lckp);
	kमुक्त(arr);
	वापस ret;
पूर्ण

#घोषणा RZONES_DESC_HD 64

/* Report zones depending on start LBA nad reporting options */
अटल पूर्णांक resp_report_zones(काष्ठा scsi_cmnd *scp,
			     काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित पूर्णांक i, max_zones, rep_max_zones, nrz = 0;
	पूर्णांक ret = 0;
	u32 alloc_len, rep_opts, rep_len;
	bool partial;
	u64 lba, zs_lba;
	u8 *arr = शून्य, *desc;
	u8 *cmd = scp->cmnd;
	काष्ठा sdeb_zone_state *zsp;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, false);
	rwlock_t *macc_lckp = sip ? &sip->macc_lck : &sdeb_fake_rw_lck;

	अगर (!sdebug_dev_is_zoned(devip)) अणु
		mk_sense_invalid_opcode(scp);
		वापस check_condition_result;
	पूर्ण
	zs_lba = get_unaligned_be64(cmd + 2);
	alloc_len = get_unaligned_be32(cmd + 10);
	rep_opts = cmd[14] & 0x3f;
	partial = cmd[14] & 0x80;

	अगर (zs_lba >= sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		वापस check_condition_result;
	पूर्ण

	max_zones = devip->nr_zones - (zs_lba >> devip->zsize_shअगरt);
	rep_max_zones = min((alloc_len - 64) >> ilog2(RZONES_DESC_HD),
			    max_zones);

	arr = kसुस्मृति(RZONES_DESC_HD, alloc_len, GFP_ATOMIC);
	अगर (!arr) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		वापस check_condition_result;
	पूर्ण

	पढ़ो_lock(macc_lckp);

	desc = arr + 64;
	क्रम (i = 0; i < max_zones; i++) अणु
		lba = zs_lba + devip->zsize * i;
		अगर (lba > sdebug_capacity)
			अवरोध;
		zsp = zbc_zone(devip, lba);
		चयन (rep_opts) अणु
		हाल 0x00:
			/* All zones */
			अवरोध;
		हाल 0x01:
			/* Empty zones */
			अगर (zsp->z_cond != ZC1_EMPTY)
				जारी;
			अवरोध;
		हाल 0x02:
			/* Implicit खोलो zones */
			अगर (zsp->z_cond != ZC2_IMPLICIT_OPEN)
				जारी;
			अवरोध;
		हाल 0x03:
			/* Explicit खोलो zones */
			अगर (zsp->z_cond != ZC3_EXPLICIT_OPEN)
				जारी;
			अवरोध;
		हाल 0x04:
			/* Closed zones */
			अगर (zsp->z_cond != ZC4_CLOSED)
				जारी;
			अवरोध;
		हाल 0x05:
			/* Full zones */
			अगर (zsp->z_cond != ZC5_FULL)
				जारी;
			अवरोध;
		हाल 0x06:
		हाल 0x07:
		हाल 0x10:
			/*
			 * Read-only, offline, reset WP recommended are
			 * not emulated: no zones to report;
			 */
			जारी;
		हाल 0x11:
			/* non-seq-resource set */
			अगर (!zsp->z_non_seq_resource)
				जारी;
			अवरोध;
		हाल 0x3f:
			/* Not ग_लिखो poपूर्णांकer (conventional) zones */
			अगर (!zbc_zone_is_conv(zsp))
				जारी;
			अवरोध;
		शेष:
			mk_sense_buffer(scp, ILLEGAL_REQUEST,
					INVALID_FIELD_IN_CDB, 0);
			ret = check_condition_result;
			जाओ fini;
		पूर्ण

		अगर (nrz < rep_max_zones) अणु
			/* Fill zone descriptor */
			desc[0] = zsp->z_type;
			desc[1] = zsp->z_cond << 4;
			अगर (zsp->z_non_seq_resource)
				desc[1] |= 1 << 1;
			put_unaligned_be64((u64)zsp->z_size, desc + 8);
			put_unaligned_be64((u64)zsp->z_start, desc + 16);
			put_unaligned_be64((u64)zsp->z_wp, desc + 24);
			desc += 64;
		पूर्ण

		अगर (partial && nrz >= rep_max_zones)
			अवरोध;

		nrz++;
	पूर्ण

	/* Report header */
	put_unaligned_be32(nrz * RZONES_DESC_HD, arr + 0);
	put_unaligned_be64(sdebug_capacity - 1, arr + 8);

	rep_len = (अचिन्हित दीर्घ)desc - (अचिन्हित दीर्घ)arr;
	ret = fill_from_dev_buffer(scp, arr, min_t(पूर्णांक, alloc_len, rep_len));

fini:
	पढ़ो_unlock(macc_lckp);
	kमुक्त(arr);
	वापस ret;
पूर्ण

/* Logic transplanted from tcmu-runner, file_zbc.c */
अटल व्योम zbc_खोलो_all(काष्ठा sdebug_dev_info *devip)
अणु
	काष्ठा sdeb_zone_state *zsp = &devip->zstate[0];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < devip->nr_zones; i++, zsp++) अणु
		अगर (zsp->z_cond == ZC4_CLOSED)
			zbc_खोलो_zone(devip, &devip->zstate[i], true);
	पूर्ण
पूर्ण

अटल पूर्णांक resp_खोलो_zone(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक res = 0;
	u64 z_id;
	क्रमागत sdebug_z_cond zc;
	u8 *cmd = scp->cmnd;
	काष्ठा sdeb_zone_state *zsp;
	bool all = cmd[14] & 0x01;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, false);
	rwlock_t *macc_lckp = sip ? &sip->macc_lck : &sdeb_fake_rw_lck;

	अगर (!sdebug_dev_is_zoned(devip)) अणु
		mk_sense_invalid_opcode(scp);
		वापस check_condition_result;
	पूर्ण

	ग_लिखो_lock(macc_lckp);

	अगर (all) अणु
		/* Check अगर all बंदd zones can be खोलो */
		अगर (devip->max_खोलो &&
		    devip->nr_exp_खोलो + devip->nr_बंदd > devip->max_खोलो) अणु
			mk_sense_buffer(scp, DATA_PROTECT, INSUFF_RES_ASC,
					INSUFF_ZONE_ASCQ);
			res = check_condition_result;
			जाओ fini;
		पूर्ण
		/* Open all बंदd zones */
		zbc_खोलो_all(devip);
		जाओ fini;
	पूर्ण

	/* Open the specअगरied zone */
	z_id = get_unaligned_be64(cmd + 2);
	अगर (z_id >= sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zsp = zbc_zone(devip, z_id);
	अगर (z_id != zsp->z_start) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण
	अगर (zbc_zone_is_conv(zsp)) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zc = zsp->z_cond;
	अगर (zc == ZC3_EXPLICIT_OPEN || zc == ZC5_FULL)
		जाओ fini;

	अगर (devip->max_खोलो && devip->nr_exp_खोलो >= devip->max_खोलो) अणु
		mk_sense_buffer(scp, DATA_PROTECT, INSUFF_RES_ASC,
				INSUFF_ZONE_ASCQ);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zbc_खोलो_zone(devip, zsp, true);
fini:
	ग_लिखो_unlock(macc_lckp);
	वापस res;
पूर्ण

अटल व्योम zbc_बंद_all(काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < devip->nr_zones; i++)
		zbc_बंद_zone(devip, &devip->zstate[i]);
पूर्ण

अटल पूर्णांक resp_बंद_zone(काष्ठा scsi_cmnd *scp,
			   काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक res = 0;
	u64 z_id;
	u8 *cmd = scp->cmnd;
	काष्ठा sdeb_zone_state *zsp;
	bool all = cmd[14] & 0x01;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, false);
	rwlock_t *macc_lckp = sip ? &sip->macc_lck : &sdeb_fake_rw_lck;

	अगर (!sdebug_dev_is_zoned(devip)) अणु
		mk_sense_invalid_opcode(scp);
		वापस check_condition_result;
	पूर्ण

	ग_लिखो_lock(macc_lckp);

	अगर (all) अणु
		zbc_बंद_all(devip);
		जाओ fini;
	पूर्ण

	/* Close specअगरied zone */
	z_id = get_unaligned_be64(cmd + 2);
	अगर (z_id >= sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zsp = zbc_zone(devip, z_id);
	अगर (z_id != zsp->z_start) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण
	अगर (zbc_zone_is_conv(zsp)) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zbc_बंद_zone(devip, zsp);
fini:
	ग_लिखो_unlock(macc_lckp);
	वापस res;
पूर्ण

अटल व्योम zbc_finish_zone(काष्ठा sdebug_dev_info *devip,
			    काष्ठा sdeb_zone_state *zsp, bool empty)
अणु
	क्रमागत sdebug_z_cond zc = zsp->z_cond;

	अगर (zc == ZC4_CLOSED || zc == ZC2_IMPLICIT_OPEN ||
	    zc == ZC3_EXPLICIT_OPEN || (empty && zc == ZC1_EMPTY)) अणु
		अगर (zc == ZC2_IMPLICIT_OPEN || zc == ZC3_EXPLICIT_OPEN)
			zbc_बंद_zone(devip, zsp);
		अगर (zsp->z_cond == ZC4_CLOSED)
			devip->nr_बंदd--;
		zsp->z_wp = zsp->z_start + zsp->z_size;
		zsp->z_cond = ZC5_FULL;
	पूर्ण
पूर्ण

अटल व्योम zbc_finish_all(काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < devip->nr_zones; i++)
		zbc_finish_zone(devip, &devip->zstate[i], false);
पूर्ण

अटल पूर्णांक resp_finish_zone(काष्ठा scsi_cmnd *scp,
			    काष्ठा sdebug_dev_info *devip)
अणु
	काष्ठा sdeb_zone_state *zsp;
	पूर्णांक res = 0;
	u64 z_id;
	u8 *cmd = scp->cmnd;
	bool all = cmd[14] & 0x01;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, false);
	rwlock_t *macc_lckp = sip ? &sip->macc_lck : &sdeb_fake_rw_lck;

	अगर (!sdebug_dev_is_zoned(devip)) अणु
		mk_sense_invalid_opcode(scp);
		वापस check_condition_result;
	पूर्ण

	ग_लिखो_lock(macc_lckp);

	अगर (all) अणु
		zbc_finish_all(devip);
		जाओ fini;
	पूर्ण

	/* Finish the specअगरied zone */
	z_id = get_unaligned_be64(cmd + 2);
	अगर (z_id >= sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zsp = zbc_zone(devip, z_id);
	अगर (z_id != zsp->z_start) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण
	अगर (zbc_zone_is_conv(zsp)) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zbc_finish_zone(devip, zsp, true);
fini:
	ग_लिखो_unlock(macc_lckp);
	वापस res;
पूर्ण

अटल व्योम zbc_rwp_zone(काष्ठा sdebug_dev_info *devip,
			 काष्ठा sdeb_zone_state *zsp)
अणु
	क्रमागत sdebug_z_cond zc;

	अगर (zbc_zone_is_conv(zsp))
		वापस;

	zc = zsp->z_cond;
	अगर (zc == ZC2_IMPLICIT_OPEN || zc == ZC3_EXPLICIT_OPEN)
		zbc_बंद_zone(devip, zsp);

	अगर (zsp->z_cond == ZC4_CLOSED)
		devip->nr_बंदd--;

	zsp->z_non_seq_resource = false;
	zsp->z_wp = zsp->z_start;
	zsp->z_cond = ZC1_EMPTY;
पूर्ण

अटल व्योम zbc_rwp_all(काष्ठा sdebug_dev_info *devip)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < devip->nr_zones; i++)
		zbc_rwp_zone(devip, &devip->zstate[i]);
पूर्ण

अटल पूर्णांक resp_rwp_zone(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	काष्ठा sdeb_zone_state *zsp;
	पूर्णांक res = 0;
	u64 z_id;
	u8 *cmd = scp->cmnd;
	bool all = cmd[14] & 0x01;
	काष्ठा sdeb_store_info *sip = devip2sip(devip, false);
	rwlock_t *macc_lckp = sip ? &sip->macc_lck : &sdeb_fake_rw_lck;

	अगर (!sdebug_dev_is_zoned(devip)) अणु
		mk_sense_invalid_opcode(scp);
		वापस check_condition_result;
	पूर्ण

	ग_लिखो_lock(macc_lckp);

	अगर (all) अणु
		zbc_rwp_all(devip);
		जाओ fini;
	पूर्ण

	z_id = get_unaligned_be64(cmd + 2);
	अगर (z_id >= sdebug_capacity) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zsp = zbc_zone(devip, z_id);
	अगर (z_id != zsp->z_start) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण
	अगर (zbc_zone_is_conv(zsp)) अणु
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		res = check_condition_result;
		जाओ fini;
	पूर्ण

	zbc_rwp_zone(devip, zsp);
fini:
	ग_लिखो_unlock(macc_lckp);
	वापस res;
पूर्ण

अटल काष्ठा sdebug_queue *get_queue(काष्ठा scsi_cmnd *cmnd)
अणु
	u16 hwq;
	u32 tag = blk_mq_unique_tag(cmnd->request);

	hwq = blk_mq_unique_tag_to_hwq(tag);

	pr_debug("tag=%#x, hwq=%d\n", tag, hwq);
	अगर (WARN_ON_ONCE(hwq >= submit_queues))
		hwq = 0;

	वापस sdebug_q_arr + hwq;
पूर्ण

अटल u32 get_tag(काष्ठा scsi_cmnd *cmnd)
अणु
	वापस blk_mq_unique_tag(cmnd->request);
पूर्ण

/* Queued (deferred) command completions converge here. */
अटल व्योम sdebug_q_cmd_complete(काष्ठा sdebug_defer *sd_dp)
अणु
	bool पातed = sd_dp->पातed;
	पूर्णांक qc_idx;
	पूर्णांक retiring = 0;
	अचिन्हित दीर्घ अगरlags;
	काष्ठा sdebug_queue *sqp;
	काष्ठा sdebug_queued_cmd *sqcp;
	काष्ठा scsi_cmnd *scp;
	काष्ठा sdebug_dev_info *devip;

	अगर (unlikely(पातed))
		sd_dp->पातed = false;
	qc_idx = sd_dp->qc_idx;
	sqp = sdebug_q_arr + sd_dp->sqa_idx;
	अगर (sdebug_statistics) अणु
		atomic_inc(&sdebug_completions);
		अगर (raw_smp_processor_id() != sd_dp->issuing_cpu)
			atomic_inc(&sdebug_miss_cpus);
	पूर्ण
	अगर (unlikely((qc_idx < 0) || (qc_idx >= SDEBUG_CANQUEUE))) अणु
		pr_err("wild qc_idx=%d\n", qc_idx);
		वापस;
	पूर्ण
	spin_lock_irqsave(&sqp->qc_lock, अगरlags);
	sd_dp->defer_t = SDEB_DEFER_NONE;
	sqcp = &sqp->qc_arr[qc_idx];
	scp = sqcp->a_cmnd;
	अगर (unlikely(scp == शून्य)) अणु
		spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
		pr_err("scp is NULL, sqa_idx=%d, qc_idx=%d, hc_idx=%d\n",
		       sd_dp->sqa_idx, qc_idx, sd_dp->hc_idx);
		वापस;
	पूर्ण
	devip = (काष्ठा sdebug_dev_info *)scp->device->hostdata;
	अगर (likely(devip))
		atomic_dec(&devip->num_in_q);
	अन्यथा
		pr_err("devip=NULL\n");
	अगर (unlikely(atomic_पढ़ो(&retired_max_queue) > 0))
		retiring = 1;

	sqcp->a_cmnd = शून्य;
	अगर (unlikely(!test_and_clear_bit(qc_idx, sqp->in_use_bm))) अणु
		spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
		pr_err("Unexpected completion\n");
		वापस;
	पूर्ण

	अगर (unlikely(retiring)) अणु	/* user has reduced max_queue */
		पूर्णांक k, retval;

		retval = atomic_पढ़ो(&retired_max_queue);
		अगर (qc_idx >= retval) अणु
			spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
			pr_err("index %d too large\n", retval);
			वापस;
		पूर्ण
		k = find_last_bit(sqp->in_use_bm, retval);
		अगर ((k < sdebug_max_queue) || (k == retval))
			atomic_set(&retired_max_queue, 0);
		अन्यथा
			atomic_set(&retired_max_queue, k + 1);
	पूर्ण
	spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
	अगर (unlikely(पातed)) अणु
		अगर (sdebug_verbose)
			pr_info("bypassing scsi_done() due to aborted cmd\n");
		वापस;
	पूर्ण
	scp->scsi_करोne(scp); /* callback to mid level */
पूर्ण

/* When high resolution समयr goes off this function is called. */
अटल क्रमागत hrसमयr_restart sdebug_q_cmd_hrt_complete(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा sdebug_defer *sd_dp = container_of(समयr, काष्ठा sdebug_defer,
						  hrt);
	sdebug_q_cmd_complete(sd_dp);
	वापस HRTIMER_NORESTART;
पूर्ण

/* When work queue schedules work, it calls this function. */
अटल व्योम sdebug_q_cmd_wq_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdebug_defer *sd_dp = container_of(work, काष्ठा sdebug_defer,
						  ew.work);
	sdebug_q_cmd_complete(sd_dp);
पूर्ण

अटल bool got_shared_uuid;
अटल uuid_t shared_uuid;

अटल पूर्णांक sdebug_device_create_zones(काष्ठा sdebug_dev_info *devip)
अणु
	काष्ठा sdeb_zone_state *zsp;
	sector_t capacity = get_sdebug_capacity();
	sector_t zstart = 0;
	अचिन्हित पूर्णांक i;

	/*
	 * Set the zone size: अगर sdeb_zbc_zone_size_mb is not set, figure out
	 * a zone size allowing क्रम at least 4 zones on the device. Otherwise,
	 * use the specअगरied zone size checking that at least 2 zones can be
	 * created क्रम the device.
	 */
	अगर (!sdeb_zbc_zone_size_mb) अणु
		devip->zsize = (DEF_ZBC_ZONE_SIZE_MB * SZ_1M)
			>> ilog2(sdebug_sector_size);
		जबतक (capacity < devip->zsize << 2 && devip->zsize >= 2)
			devip->zsize >>= 1;
		अगर (devip->zsize < 2) अणु
			pr_err("Device capacity too small\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!is_घातer_of_2(sdeb_zbc_zone_size_mb)) अणु
			pr_err("Zone size is not a power of 2\n");
			वापस -EINVAL;
		पूर्ण
		devip->zsize = (sdeb_zbc_zone_size_mb * SZ_1M)
			>> ilog2(sdebug_sector_size);
		अगर (devip->zsize >= capacity) अणु
			pr_err("Zone size too large for device capacity\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	devip->zsize_shअगरt = ilog2(devip->zsize);
	devip->nr_zones = (capacity + devip->zsize - 1) >> devip->zsize_shअगरt;

	अगर (sdeb_zbc_nr_conv >= devip->nr_zones) अणु
		pr_err("Number of conventional zones too large\n");
		वापस -EINVAL;
	पूर्ण
	devip->nr_conv_zones = sdeb_zbc_nr_conv;

	अगर (devip->zmodel == BLK_ZONED_HM) अणु
		/* zbc_max_खोलो_zones can be 0, meaning "not reported" */
		अगर (sdeb_zbc_max_खोलो >= devip->nr_zones - 1)
			devip->max_खोलो = (devip->nr_zones - 1) / 2;
		अन्यथा
			devip->max_खोलो = sdeb_zbc_max_खोलो;
	पूर्ण

	devip->zstate = kसुस्मृति(devip->nr_zones,
				माप(काष्ठा sdeb_zone_state), GFP_KERNEL);
	अगर (!devip->zstate)
		वापस -ENOMEM;

	क्रम (i = 0; i < devip->nr_zones; i++) अणु
		zsp = &devip->zstate[i];

		zsp->z_start = zstart;

		अगर (i < devip->nr_conv_zones) अणु
			zsp->z_type = ZBC_ZONE_TYPE_CNV;
			zsp->z_cond = ZBC_NOT_WRITE_POINTER;
			zsp->z_wp = (sector_t)-1;
		पूर्ण अन्यथा अणु
			अगर (devip->zmodel == BLK_ZONED_HM)
				zsp->z_type = ZBC_ZONE_TYPE_SWR;
			अन्यथा
				zsp->z_type = ZBC_ZONE_TYPE_SWP;
			zsp->z_cond = ZC1_EMPTY;
			zsp->z_wp = zsp->z_start;
		पूर्ण

		अगर (zsp->z_start + devip->zsize < capacity)
			zsp->z_size = devip->zsize;
		अन्यथा
			zsp->z_size = capacity - zsp->z_start;

		zstart += zsp->z_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sdebug_dev_info *sdebug_device_create(
			काष्ठा sdebug_host_info *sdbg_host, gfp_t flags)
अणु
	काष्ठा sdebug_dev_info *devip;

	devip = kzalloc(माप(*devip), flags);
	अगर (devip) अणु
		अगर (sdebug_uuid_ctl == 1)
			uuid_gen(&devip->lu_name);
		अन्यथा अगर (sdebug_uuid_ctl == 2) अणु
			अगर (got_shared_uuid)
				devip->lu_name = shared_uuid;
			अन्यथा अणु
				uuid_gen(&shared_uuid);
				got_shared_uuid = true;
				devip->lu_name = shared_uuid;
			पूर्ण
		पूर्ण
		devip->sdbg_host = sdbg_host;
		अगर (sdeb_zbc_in_use) अणु
			devip->zmodel = sdeb_zbc_model;
			अगर (sdebug_device_create_zones(devip)) अणु
				kमुक्त(devip);
				वापस शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			devip->zmodel = BLK_ZONED_NONE;
		पूर्ण
		devip->sdbg_host = sdbg_host;
		devip->create_ts = kसमय_get_bootसमय();
		atomic_set(&devip->stopped, (sdeb_tur_ms_to_पढ़ोy > 0 ? 2 : 0));
		list_add_tail(&devip->dev_list, &sdbg_host->dev_info_list);
	पूर्ण
	वापस devip;
पूर्ण

अटल काष्ठा sdebug_dev_info *find_build_dev_info(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा sdebug_dev_info *खोलो_devip = शून्य;
	काष्ठा sdebug_dev_info *devip;

	sdbg_host = *(काष्ठा sdebug_host_info **)shost_priv(sdev->host);
	अगर (!sdbg_host) अणु
		pr_err("Host info NULL\n");
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(devip, &sdbg_host->dev_info_list, dev_list) अणु
		अगर ((devip->used) && (devip->channel == sdev->channel) &&
		    (devip->target == sdev->id) &&
		    (devip->lun == sdev->lun))
			वापस devip;
		अन्यथा अणु
			अगर ((!devip->used) && (!खोलो_devip))
				खोलो_devip = devip;
		पूर्ण
	पूर्ण
	अगर (!खोलो_devip) अणु /* try and make a new one */
		खोलो_devip = sdebug_device_create(sdbg_host, GFP_ATOMIC);
		अगर (!खोलो_devip) अणु
			pr_err("out of memory at line %d\n", __LINE__);
			वापस शून्य;
		पूर्ण
	पूर्ण

	खोलो_devip->channel = sdev->channel;
	खोलो_devip->target = sdev->id;
	खोलो_devip->lun = sdev->lun;
	खोलो_devip->sdbg_host = sdbg_host;
	atomic_set(&खोलो_devip->num_in_q, 0);
	set_bit(SDEBUG_UA_POR, खोलो_devip->uas_bm);
	खोलो_devip->used = true;
	वापस खोलो_devip;
पूर्ण

अटल पूर्णांक scsi_debug_slave_alloc(काष्ठा scsi_device *sdp)
अणु
	अगर (sdebug_verbose)
		pr_info("slave_alloc <%u %u %u %llu>\n",
		       sdp->host->host_no, sdp->channel, sdp->id, sdp->lun);
	वापस 0;
पूर्ण

अटल पूर्णांक scsi_debug_slave_configure(काष्ठा scsi_device *sdp)
अणु
	काष्ठा sdebug_dev_info *devip =
			(काष्ठा sdebug_dev_info *)sdp->hostdata;

	अगर (sdebug_verbose)
		pr_info("slave_configure <%u %u %u %llu>\n",
		       sdp->host->host_no, sdp->channel, sdp->id, sdp->lun);
	अगर (sdp->host->max_cmd_len != SDEBUG_MAX_CMD_LEN)
		sdp->host->max_cmd_len = SDEBUG_MAX_CMD_LEN;
	अगर (devip == शून्य) अणु
		devip = find_build_dev_info(sdp);
		अगर (devip == शून्य)
			वापस 1;  /* no resources, will be marked offline */
	पूर्ण
	sdp->hostdata = devip;
	अगर (sdebug_no_uld)
		sdp->no_uld_attach = 1;
	config_cdb_len(sdp);
	वापस 0;
पूर्ण

अटल व्योम scsi_debug_slave_destroy(काष्ठा scsi_device *sdp)
अणु
	काष्ठा sdebug_dev_info *devip =
		(काष्ठा sdebug_dev_info *)sdp->hostdata;

	अगर (sdebug_verbose)
		pr_info("slave_destroy <%u %u %u %llu>\n",
		       sdp->host->host_no, sdp->channel, sdp->id, sdp->lun);
	अगर (devip) अणु
		/* make this slot available क्रम re-use */
		devip->used = false;
		sdp->hostdata = शून्य;
	पूर्ण
पूर्ण

अटल व्योम stop_qc_helper(काष्ठा sdebug_defer *sd_dp,
			   क्रमागत sdeb_defer_type defer_t)
अणु
	अगर (!sd_dp)
		वापस;
	अगर (defer_t == SDEB_DEFER_HRT)
		hrसमयr_cancel(&sd_dp->hrt);
	अन्यथा अगर (defer_t == SDEB_DEFER_WQ)
		cancel_work_sync(&sd_dp->ew.work);
पूर्ण

/* If @cmnd found deletes its समयr or work queue and वापसs true; अन्यथा
   वापसs false */
अटल bool stop_queued_cmnd(काष्ठा scsi_cmnd *cmnd)
अणु
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक j, k, qmax, r_qmax;
	क्रमागत sdeb_defer_type l_defer_t;
	काष्ठा sdebug_queue *sqp;
	काष्ठा sdebug_queued_cmd *sqcp;
	काष्ठा sdebug_dev_info *devip;
	काष्ठा sdebug_defer *sd_dp;

	क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp) अणु
		spin_lock_irqsave(&sqp->qc_lock, अगरlags);
		qmax = sdebug_max_queue;
		r_qmax = atomic_पढ़ो(&retired_max_queue);
		अगर (r_qmax > qmax)
			qmax = r_qmax;
		क्रम (k = 0; k < qmax; ++k) अणु
			अगर (test_bit(k, sqp->in_use_bm)) अणु
				sqcp = &sqp->qc_arr[k];
				अगर (cmnd != sqcp->a_cmnd)
					जारी;
				/* found */
				devip = (काष्ठा sdebug_dev_info *)
						cmnd->device->hostdata;
				अगर (devip)
					atomic_dec(&devip->num_in_q);
				sqcp->a_cmnd = शून्य;
				sd_dp = sqcp->sd_dp;
				अगर (sd_dp) अणु
					l_defer_t = sd_dp->defer_t;
					sd_dp->defer_t = SDEB_DEFER_NONE;
				पूर्ण अन्यथा
					l_defer_t = SDEB_DEFER_NONE;
				spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
				stop_qc_helper(sd_dp, l_defer_t);
				clear_bit(k, sqp->in_use_bm);
				वापस true;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
	पूर्ण
	वापस false;
पूर्ण

/* Deletes (stops) समयrs or work queues of all queued commands */
अटल व्योम stop_all_queued(व्योम)
अणु
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक j, k;
	क्रमागत sdeb_defer_type l_defer_t;
	काष्ठा sdebug_queue *sqp;
	काष्ठा sdebug_queued_cmd *sqcp;
	काष्ठा sdebug_dev_info *devip;
	काष्ठा sdebug_defer *sd_dp;

	क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp) अणु
		spin_lock_irqsave(&sqp->qc_lock, अगरlags);
		क्रम (k = 0; k < SDEBUG_CANQUEUE; ++k) अणु
			अगर (test_bit(k, sqp->in_use_bm)) अणु
				sqcp = &sqp->qc_arr[k];
				अगर (sqcp->a_cmnd == शून्य)
					जारी;
				devip = (काष्ठा sdebug_dev_info *)
					sqcp->a_cmnd->device->hostdata;
				अगर (devip)
					atomic_dec(&devip->num_in_q);
				sqcp->a_cmnd = शून्य;
				sd_dp = sqcp->sd_dp;
				अगर (sd_dp) अणु
					l_defer_t = sd_dp->defer_t;
					sd_dp->defer_t = SDEB_DEFER_NONE;
				पूर्ण अन्यथा
					l_defer_t = SDEB_DEFER_NONE;
				spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
				stop_qc_helper(sd_dp, l_defer_t);
				clear_bit(k, sqp->in_use_bm);
				spin_lock_irqsave(&sqp->qc_lock, अगरlags);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
	पूर्ण
पूर्ण

/* Free queued command memory on heap */
अटल व्योम मुक्त_all_queued(व्योम)
अणु
	पूर्णांक j, k;
	काष्ठा sdebug_queue *sqp;
	काष्ठा sdebug_queued_cmd *sqcp;

	क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp) अणु
		क्रम (k = 0; k < SDEBUG_CANQUEUE; ++k) अणु
			sqcp = &sqp->qc_arr[k];
			kमुक्त(sqcp->sd_dp);
			sqcp->sd_dp = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक scsi_debug_पात(काष्ठा scsi_cmnd *SCpnt)
अणु
	bool ok;

	++num_पातs;
	अगर (SCpnt) अणु
		ok = stop_queued_cmnd(SCpnt);
		अगर (SCpnt->device && (SDEBUG_OPT_ALL_NOISE & sdebug_opts))
			sdev_prपूर्णांकk(KERN_INFO, SCpnt->device,
				    "%s: command%s found\n", __func__,
				    ok ? "" : " not");
	पूर्ण
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक scsi_debug_device_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	++num_dev_resets;
	अगर (SCpnt && SCpnt->device) अणु
		काष्ठा scsi_device *sdp = SCpnt->device;
		काष्ठा sdebug_dev_info *devip =
				(काष्ठा sdebug_dev_info *)sdp->hostdata;

		अगर (SDEBUG_OPT_ALL_NOISE & sdebug_opts)
			sdev_prपूर्णांकk(KERN_INFO, sdp, "%s\n", __func__);
		अगर (devip)
			set_bit(SDEBUG_UA_POR, devip->uas_bm);
	पूर्ण
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक scsi_debug_target_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा sdebug_dev_info *devip;
	काष्ठा scsi_device *sdp;
	काष्ठा Scsi_Host *hp;
	पूर्णांक k = 0;

	++num_target_resets;
	अगर (!SCpnt)
		जाओ lie;
	sdp = SCpnt->device;
	अगर (!sdp)
		जाओ lie;
	अगर (SDEBUG_OPT_ALL_NOISE & sdebug_opts)
		sdev_prपूर्णांकk(KERN_INFO, sdp, "%s\n", __func__);
	hp = sdp->host;
	अगर (!hp)
		जाओ lie;
	sdbg_host = *(काष्ठा sdebug_host_info **)shost_priv(hp);
	अगर (sdbg_host) अणु
		list_क्रम_each_entry(devip,
				    &sdbg_host->dev_info_list,
				    dev_list)
			अगर (devip->target == sdp->id) अणु
				set_bit(SDEBUG_UA_BUS_RESET, devip->uas_bm);
				++k;
			पूर्ण
	पूर्ण
	अगर (SDEBUG_OPT_RESET_NOISE & sdebug_opts)
		sdev_prपूर्णांकk(KERN_INFO, sdp,
			    "%s: %d device(s) found in target\n", __func__, k);
lie:
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक scsi_debug_bus_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा sdebug_dev_info *devip;
	काष्ठा scsi_device *sdp;
	काष्ठा Scsi_Host *hp;
	पूर्णांक k = 0;

	++num_bus_resets;
	अगर (!(SCpnt && SCpnt->device))
		जाओ lie;
	sdp = SCpnt->device;
	अगर (SDEBUG_OPT_ALL_NOISE & sdebug_opts)
		sdev_prपूर्णांकk(KERN_INFO, sdp, "%s\n", __func__);
	hp = sdp->host;
	अगर (hp) अणु
		sdbg_host = *(काष्ठा sdebug_host_info **)shost_priv(hp);
		अगर (sdbg_host) अणु
			list_क्रम_each_entry(devip,
					    &sdbg_host->dev_info_list,
					    dev_list) अणु
				set_bit(SDEBUG_UA_BUS_RESET, devip->uas_bm);
				++k;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (SDEBUG_OPT_RESET_NOISE & sdebug_opts)
		sdev_prपूर्णांकk(KERN_INFO, sdp,
			    "%s: %d device(s) found in host\n", __func__, k);
lie:
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक scsi_debug_host_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा sdebug_dev_info *devip;
	पूर्णांक k = 0;

	++num_host_resets;
	अगर ((SCpnt->device) && (SDEBUG_OPT_ALL_NOISE & sdebug_opts))
		sdev_prपूर्णांकk(KERN_INFO, SCpnt->device, "%s\n", __func__);
	spin_lock(&sdebug_host_list_lock);
	list_क्रम_each_entry(sdbg_host, &sdebug_host_list, host_list) अणु
		list_क्रम_each_entry(devip, &sdbg_host->dev_info_list,
				    dev_list) अणु
			set_bit(SDEBUG_UA_BUS_RESET, devip->uas_bm);
			++k;
		पूर्ण
	पूर्ण
	spin_unlock(&sdebug_host_list_lock);
	stop_all_queued();
	अगर (SDEBUG_OPT_RESET_NOISE & sdebug_opts)
		sdev_prपूर्णांकk(KERN_INFO, SCpnt->device,
			    "%s: %d device(s) found\n", __func__, k);
	वापस SUCCESS;
पूर्ण

अटल व्योम sdebug_build_parts(अचिन्हित अक्षर *ramp, अचिन्हित दीर्घ store_size)
अणु
	काष्ठा msकरोs_partition *pp;
	पूर्णांक starts[SDEBUG_MAX_PARTS + 2], max_part_secs;
	पूर्णांक sectors_per_part, num_sectors, k;
	पूर्णांक heads_by_sects, start_sec, end_sec;

	/* assume partition table alपढ़ोy zeroed */
	अगर ((sdebug_num_parts < 1) || (store_size < 1048576))
		वापस;
	अगर (sdebug_num_parts > SDEBUG_MAX_PARTS) अणु
		sdebug_num_parts = SDEBUG_MAX_PARTS;
		pr_warn("reducing partitions to %d\n", SDEBUG_MAX_PARTS);
	पूर्ण
	num_sectors = (पूर्णांक)get_sdebug_capacity();
	sectors_per_part = (num_sectors - sdebug_sectors_per)
			   / sdebug_num_parts;
	heads_by_sects = sdebug_heads * sdebug_sectors_per;
	starts[0] = sdebug_sectors_per;
	max_part_secs = sectors_per_part;
	क्रम (k = 1; k < sdebug_num_parts; ++k) अणु
		starts[k] = ((k * sectors_per_part) / heads_by_sects)
			    * heads_by_sects;
		अगर (starts[k] - starts[k - 1] < max_part_secs)
			max_part_secs = starts[k] - starts[k - 1];
	पूर्ण
	starts[sdebug_num_parts] = num_sectors;
	starts[sdebug_num_parts + 1] = 0;

	ramp[510] = 0x55;	/* magic partition markings */
	ramp[511] = 0xAA;
	pp = (काष्ठा msकरोs_partition *)(ramp + 0x1be);
	क्रम (k = 0; starts[k + 1]; ++k, ++pp) अणु
		start_sec = starts[k];
		end_sec = starts[k] + max_part_secs - 1;
		pp->boot_ind = 0;

		pp->cyl = start_sec / heads_by_sects;
		pp->head = (start_sec - (pp->cyl * heads_by_sects))
			   / sdebug_sectors_per;
		pp->sector = (start_sec % sdebug_sectors_per) + 1;

		pp->end_cyl = end_sec / heads_by_sects;
		pp->end_head = (end_sec - (pp->end_cyl * heads_by_sects))
			       / sdebug_sectors_per;
		pp->end_sector = (end_sec % sdebug_sectors_per) + 1;

		pp->start_sect = cpu_to_le32(start_sec);
		pp->nr_sects = cpu_to_le32(end_sec - start_sec + 1);
		pp->sys_ind = 0x83;	/* plain Linux partition */
	पूर्ण
पूर्ण

अटल व्योम block_unblock_all_queues(bool block)
अणु
	पूर्णांक j;
	काष्ठा sdebug_queue *sqp;

	क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp)
		atomic_set(&sqp->blocked, (पूर्णांक)block);
पूर्ण

/* Adjust (by rounding करोwn) the sdebug_cmnd_count so असल(every_nth)-1
 * commands will be processed normally beक्रमe triggers occur.
 */
अटल व्योम tweak_cmnd_count(व्योम)
अणु
	पूर्णांक count, modulo;

	modulo = असल(sdebug_every_nth);
	अगर (modulo < 2)
		वापस;
	block_unblock_all_queues(true);
	count = atomic_पढ़ो(&sdebug_cmnd_count);
	atomic_set(&sdebug_cmnd_count, (count / modulo) * modulo);
	block_unblock_all_queues(false);
पूर्ण

अटल व्योम clear_queue_stats(व्योम)
अणु
	atomic_set(&sdebug_cmnd_count, 0);
	atomic_set(&sdebug_completions, 0);
	atomic_set(&sdebug_miss_cpus, 0);
	atomic_set(&sdebug_a_tsf, 0);
पूर्ण

अटल bool inject_on_this_cmd(व्योम)
अणु
	अगर (sdebug_every_nth == 0)
		वापस false;
	वापस (atomic_पढ़ो(&sdebug_cmnd_count) % असल(sdebug_every_nth)) == 0;
पूर्ण

#घोषणा INCLUSIVE_TIMING_MAX_NS 1000000		/* 1 millisecond */

/* Complete the processing of the thपढ़ो that queued a SCSI command to this
 * driver. It either completes the command by calling cmnd_करोne() or
 * schedules a hr समयr or work queue then वापसs 0. Returns
 * SCSI_MLQUEUE_HOST_BUSY अगर temporarily out of resources.
 */
अटल पूर्णांक schedule_resp(काष्ठा scsi_cmnd *cmnd, काष्ठा sdebug_dev_info *devip,
			 पूर्णांक scsi_result,
			 पूर्णांक (*pfp)(काष्ठा scsi_cmnd *,
				    काष्ठा sdebug_dev_info *),
			 पूर्णांक delta_jअगरf, पूर्णांक ndelay)
अणु
	bool new_sd_dp;
	bool inject = false;
	bool hipri = (cmnd->request->cmd_flags & REQ_HIPRI);
	पूर्णांक k, num_in_q, qdepth;
	अचिन्हित दीर्घ अगरlags;
	u64 ns_from_boot = 0;
	काष्ठा sdebug_queue *sqp;
	काष्ठा sdebug_queued_cmd *sqcp;
	काष्ठा scsi_device *sdp;
	काष्ठा sdebug_defer *sd_dp;

	अगर (unlikely(devip == शून्य)) अणु
		अगर (scsi_result == 0)
			scsi_result = DID_NO_CONNECT << 16;
		जाओ respond_in_thपढ़ो;
	पूर्ण
	sdp = cmnd->device;

	अगर (delta_jअगरf == 0)
		जाओ respond_in_thपढ़ो;

	sqp = get_queue(cmnd);
	spin_lock_irqsave(&sqp->qc_lock, अगरlags);
	अगर (unlikely(atomic_पढ़ो(&sqp->blocked))) अणु
		spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	num_in_q = atomic_पढ़ो(&devip->num_in_q);
	qdepth = cmnd->device->queue_depth;
	अगर (unlikely((qdepth > 0) && (num_in_q >= qdepth))) अणु
		अगर (scsi_result) अणु
			spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
			जाओ respond_in_thपढ़ो;
		पूर्ण अन्यथा
			scsi_result = device_qfull_result;
	पूर्ण अन्यथा अगर (unlikely(sdebug_every_nth &&
			    (SDEBUG_OPT_RARE_TSF & sdebug_opts) &&
			    (scsi_result == 0))) अणु
		अगर ((num_in_q == (qdepth - 1)) &&
		    (atomic_inc_वापस(&sdebug_a_tsf) >=
		     असल(sdebug_every_nth))) अणु
			atomic_set(&sdebug_a_tsf, 0);
			inject = true;
			scsi_result = device_qfull_result;
		पूर्ण
	पूर्ण

	k = find_first_zero_bit(sqp->in_use_bm, sdebug_max_queue);
	अगर (unlikely(k >= sdebug_max_queue)) अणु
		spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
		अगर (scsi_result)
			जाओ respond_in_thपढ़ो;
		अन्यथा अगर (SDEBUG_OPT_ALL_TSF & sdebug_opts)
			scsi_result = device_qfull_result;
		अगर (SDEBUG_OPT_Q_NOISE & sdebug_opts)
			sdev_prपूर्णांकk(KERN_INFO, sdp,
				    "%s: max_queue=%d exceeded, %s\n",
				    __func__, sdebug_max_queue,
				    (scsi_result ?  "status: TASK SET FULL" :
						    "report: host busy"));
		अगर (scsi_result)
			जाओ respond_in_thपढ़ो;
		अन्यथा
			वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	set_bit(k, sqp->in_use_bm);
	atomic_inc(&devip->num_in_q);
	sqcp = &sqp->qc_arr[k];
	sqcp->a_cmnd = cmnd;
	cmnd->host_scribble = (अचिन्हित अक्षर *)sqcp;
	sd_dp = sqcp->sd_dp;
	spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);

	अगर (!sd_dp) अणु
		sd_dp = kzalloc(माप(*sd_dp), GFP_ATOMIC);
		अगर (!sd_dp) अणु
			atomic_dec(&devip->num_in_q);
			clear_bit(k, sqp->in_use_bm);
			वापस SCSI_MLQUEUE_HOST_BUSY;
		पूर्ण
		new_sd_dp = true;
	पूर्ण अन्यथा अणु
		new_sd_dp = false;
	पूर्ण

	/* Set the hostwide tag */
	अगर (sdebug_host_max_queue)
		sd_dp->hc_idx = get_tag(cmnd);

	अगर (hipri)
		ns_from_boot = kसमय_get_bootसमय_ns();

	/* one of the resp_*() response functions is called here */
	cmnd->result = pfp ? pfp(cmnd, devip) : 0;
	अगर (cmnd->result & SDEG_RES_IMMED_MASK) अणु
		cmnd->result &= ~SDEG_RES_IMMED_MASK;
		delta_jअगरf = ndelay = 0;
	पूर्ण
	अगर (cmnd->result == 0 && scsi_result != 0)
		cmnd->result = scsi_result;
	अगर (cmnd->result == 0 && unlikely(sdebug_opts & SDEBUG_OPT_TRANSPORT_ERR)) अणु
		अगर (atomic_पढ़ो(&sdeb_inject_pending)) अणु
			mk_sense_buffer(cmnd, ABORTED_COMMAND, TRANSPORT_PROBLEM, ACK_NAK_TO);
			atomic_set(&sdeb_inject_pending, 0);
			cmnd->result = check_condition_result;
		पूर्ण
	पूर्ण

	अगर (unlikely(sdebug_verbose && cmnd->result))
		sdev_prपूर्णांकk(KERN_INFO, sdp, "%s: non-zero result=0x%x\n",
			    __func__, cmnd->result);

	अगर (delta_jअगरf > 0 || ndelay > 0) अणु
		kसमय_प्रकार kt;

		अगर (delta_jअगरf > 0) अणु
			u64 ns = jअगरfies_to_nsecs(delta_jअगरf);

			अगर (sdebug_अक्रमom && ns < U32_MAX) अणु
				ns = pअक्रमom_u32_max((u32)ns);
			पूर्ण अन्यथा अगर (sdebug_अक्रमom) अणु
				ns >>= 12;	/* scale to 4 usec precision */
				अगर (ns < U32_MAX)	/* over 4 hours max */
					ns = pअक्रमom_u32_max((u32)ns);
				ns <<= 12;
			पूर्ण
			kt = ns_to_kसमय(ns);
		पूर्ण अन्यथा अणु	/* ndelay has a 4.2 second max */
			kt = sdebug_अक्रमom ? pअक्रमom_u32_max((u32)ndelay) :
					     (u32)ndelay;
			अगर (ndelay < INCLUSIVE_TIMING_MAX_NS) अणु
				u64 d = kसमय_get_bootसमय_ns() - ns_from_boot;

				अगर (kt <= d) अणु	/* elapsed duration >= kt */
					spin_lock_irqsave(&sqp->qc_lock, अगरlags);
					sqcp->a_cmnd = शून्य;
					atomic_dec(&devip->num_in_q);
					clear_bit(k, sqp->in_use_bm);
					spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
					अगर (new_sd_dp)
						kमुक्त(sd_dp);
					/* call scsi_करोne() from this thपढ़ो */
					cmnd->scsi_करोne(cmnd);
					वापस 0;
				पूर्ण
				/* otherwise reduce kt by elapsed समय */
				kt -= d;
			पूर्ण
		पूर्ण
		अगर (hipri) अणु
			sd_dp->cmpl_ts = kसमय_add(ns_to_kसमय(ns_from_boot), kt);
			spin_lock_irqsave(&sqp->qc_lock, अगरlags);
			अगर (!sd_dp->init_poll) अणु
				sd_dp->init_poll = true;
				sqcp->sd_dp = sd_dp;
				sd_dp->sqa_idx = sqp - sdebug_q_arr;
				sd_dp->qc_idx = k;
			पूर्ण
			sd_dp->defer_t = SDEB_DEFER_POLL;
			spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
		पूर्ण अन्यथा अणु
			अगर (!sd_dp->init_hrt) अणु
				sd_dp->init_hrt = true;
				sqcp->sd_dp = sd_dp;
				hrसमयr_init(&sd_dp->hrt, CLOCK_MONOTONIC,
					     HRTIMER_MODE_REL_PINNED);
				sd_dp->hrt.function = sdebug_q_cmd_hrt_complete;
				sd_dp->sqa_idx = sqp - sdebug_q_arr;
				sd_dp->qc_idx = k;
			पूर्ण
			sd_dp->defer_t = SDEB_DEFER_HRT;
			/* schedule the invocation of scsi_करोne() क्रम a later समय */
			hrसमयr_start(&sd_dp->hrt, kt, HRTIMER_MODE_REL_PINNED);
		पूर्ण
		अगर (sdebug_statistics)
			sd_dp->issuing_cpu = raw_smp_processor_id();
	पूर्ण अन्यथा अणु	/* jdelay < 0, use work queue */
		अगर (unlikely((sdebug_opts & SDEBUG_OPT_CMD_ABORT) &&
			     atomic_पढ़ो(&sdeb_inject_pending)))
			sd_dp->पातed = true;
		अगर (hipri) अणु
			sd_dp->cmpl_ts = ns_to_kसमय(ns_from_boot);
			spin_lock_irqsave(&sqp->qc_lock, अगरlags);
			अगर (!sd_dp->init_poll) अणु
				sd_dp->init_poll = true;
				sqcp->sd_dp = sd_dp;
				sd_dp->sqa_idx = sqp - sdebug_q_arr;
				sd_dp->qc_idx = k;
			पूर्ण
			sd_dp->defer_t = SDEB_DEFER_POLL;
			spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
		पूर्ण अन्यथा अणु
			अगर (!sd_dp->init_wq) अणु
				sd_dp->init_wq = true;
				sqcp->sd_dp = sd_dp;
				sd_dp->sqa_idx = sqp - sdebug_q_arr;
				sd_dp->qc_idx = k;
				INIT_WORK(&sd_dp->ew.work, sdebug_q_cmd_wq_complete);
			पूर्ण
			sd_dp->defer_t = SDEB_DEFER_WQ;
			schedule_work(&sd_dp->ew.work);
		पूर्ण
		अगर (sdebug_statistics)
			sd_dp->issuing_cpu = raw_smp_processor_id();
		अगर (unlikely(sd_dp->पातed)) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdp, "abort request tag %d\n", cmnd->request->tag);
			blk_पात_request(cmnd->request);
			atomic_set(&sdeb_inject_pending, 0);
			sd_dp->पातed = false;
		पूर्ण
	पूर्ण
	अगर (unlikely((SDEBUG_OPT_Q_NOISE & sdebug_opts) && scsi_result == device_qfull_result))
		sdev_prपूर्णांकk(KERN_INFO, sdp, "%s: num_in_q=%d +1, %s%s\n", __func__,
			    num_in_q, (inject ? "<inject> " : ""), "status: TASK SET FULL");
	वापस 0;

respond_in_thपढ़ो:	/* call back to mid-layer using invocation thपढ़ो */
	cmnd->result = pfp != शून्य ? pfp(cmnd, devip) : 0;
	cmnd->result &= ~SDEG_RES_IMMED_MASK;
	अगर (cmnd->result == 0 && scsi_result != 0)
		cmnd->result = scsi_result;
	cmnd->scsi_करोne(cmnd);
	वापस 0;
पूर्ण

/* Note: The following macros create attribute files in the
   /sys/module/scsi_debug/parameters directory. Unक्रमtunately this
   driver is unaware of a change and cannot trigger auxiliary actions
   as it can when the corresponding attribute in the
   /sys/bus/pseuकरो/drivers/scsi_debug directory is changed.
 */
module_param_named(add_host, sdebug_add_host, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(ato, sdebug_ato, पूर्णांक, S_IRUGO);
module_param_named(cdb_len, sdebug_cdb_len, पूर्णांक, 0644);
module_param_named(clustering, sdebug_clustering, bool, S_IRUGO | S_IWUSR);
module_param_named(delay, sdebug_jdelay, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(dev_size_mb, sdebug_dev_size_mb, पूर्णांक, S_IRUGO);
module_param_named(dअगर, sdebug_dअगर, पूर्णांक, S_IRUGO);
module_param_named(dix, sdebug_dix, पूर्णांक, S_IRUGO);
module_param_named(dsense, sdebug_dsense, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(every_nth, sdebug_every_nth, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(fake_rw, sdebug_fake_rw, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(guard, sdebug_guard, uपूर्णांक, S_IRUGO);
module_param_named(host_lock, sdebug_host_lock, bool, S_IRUGO | S_IWUSR);
module_param_named(host_max_queue, sdebug_host_max_queue, पूर्णांक, S_IRUGO);
module_param_string(inq_product, sdebug_inq_product_id,
		    माप(sdebug_inq_product_id), S_IRUGO | S_IWUSR);
module_param_string(inq_rev, sdebug_inq_product_rev,
		    माप(sdebug_inq_product_rev), S_IRUGO | S_IWUSR);
module_param_string(inq_venकरोr, sdebug_inq_venकरोr_id,
		    माप(sdebug_inq_venकरोr_id), S_IRUGO | S_IWUSR);
module_param_named(lbprz, sdebug_lbprz, पूर्णांक, S_IRUGO);
module_param_named(lbpu, sdebug_lbpu, पूर्णांक, S_IRUGO);
module_param_named(lbpws, sdebug_lbpws, पूर्णांक, S_IRUGO);
module_param_named(lbpws10, sdebug_lbpws10, पूर्णांक, S_IRUGO);
module_param_named(lowest_aligned, sdebug_lowest_aligned, पूर्णांक, S_IRUGO);
module_param_named(lun_क्रमmat, sdebug_lun_am_i, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(max_luns, sdebug_max_luns, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(max_queue, sdebug_max_queue, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(medium_error_count, sdebug_medium_error_count, पूर्णांक,
		   S_IRUGO | S_IWUSR);
module_param_named(medium_error_start, sdebug_medium_error_start, पूर्णांक,
		   S_IRUGO | S_IWUSR);
module_param_named(ndelay, sdebug_ndelay, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(no_lun_0, sdebug_no_lun_0, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(no_uld, sdebug_no_uld, पूर्णांक, S_IRUGO);
module_param_named(num_parts, sdebug_num_parts, पूर्णांक, S_IRUGO);
module_param_named(num_tgts, sdebug_num_tgts, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(opt_blks, sdebug_opt_blks, पूर्णांक, S_IRUGO);
module_param_named(opt_xferlen_exp, sdebug_opt_xferlen_exp, पूर्णांक, S_IRUGO);
module_param_named(opts, sdebug_opts, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(per_host_store, sdebug_per_host_store, bool,
		   S_IRUGO | S_IWUSR);
module_param_named(physblk_exp, sdebug_physblk_exp, पूर्णांक, S_IRUGO);
module_param_named(ptype, sdebug_ptype, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(अक्रमom, sdebug_अक्रमom, bool, S_IRUGO | S_IWUSR);
module_param_named(removable, sdebug_removable, bool, S_IRUGO | S_IWUSR);
module_param_named(scsi_level, sdebug_scsi_level, पूर्णांक, S_IRUGO);
module_param_named(sector_size, sdebug_sector_size, पूर्णांक, S_IRUGO);
module_param_named(statistics, sdebug_statistics, bool, S_IRUGO | S_IWUSR);
module_param_named(strict, sdebug_strict, bool, S_IRUGO | S_IWUSR);
module_param_named(submit_queues, submit_queues, पूर्णांक, S_IRUGO);
module_param_named(poll_queues, poll_queues, पूर्णांक, S_IRUGO);
module_param_named(tur_ms_to_पढ़ोy, sdeb_tur_ms_to_पढ़ोy, पूर्णांक, S_IRUGO);
module_param_named(unmap_alignment, sdebug_unmap_alignment, पूर्णांक, S_IRUGO);
module_param_named(unmap_granularity, sdebug_unmap_granularity, पूर्णांक, S_IRUGO);
module_param_named(unmap_max_blocks, sdebug_unmap_max_blocks, पूर्णांक, S_IRUGO);
module_param_named(unmap_max_desc, sdebug_unmap_max_desc, पूर्णांक, S_IRUGO);
module_param_named(uuid_ctl, sdebug_uuid_ctl, पूर्णांक, S_IRUGO);
module_param_named(भव_gb, sdebug_भव_gb, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(vpd_use_hostno, sdebug_vpd_use_hostno, पूर्णांक,
		   S_IRUGO | S_IWUSR);
module_param_named(wp, sdebug_wp, bool, S_IRUGO | S_IWUSR);
module_param_named(ग_लिखो_same_length, sdebug_ग_लिखो_same_length, पूर्णांक,
		   S_IRUGO | S_IWUSR);
module_param_named(zbc, sdeb_zbc_model_s, अक्षरp, S_IRUGO);
module_param_named(zone_max_खोलो, sdeb_zbc_max_खोलो, पूर्णांक, S_IRUGO);
module_param_named(zone_nr_conv, sdeb_zbc_nr_conv, पूर्णांक, S_IRUGO);
module_param_named(zone_size_mb, sdeb_zbc_zone_size_mb, पूर्णांक, S_IRUGO);

MODULE_AUTHOR("Eric Youngdale + Douglas Gilbert");
MODULE_DESCRIPTION("SCSI debug adapter driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(SDEBUG_VERSION);

MODULE_PARM_DESC(add_host, "add n hosts, in sysfs if negative remove host(s) (def=1)");
MODULE_PARM_DESC(ato, "application tag ownership: 0=disk 1=host (def=1)");
MODULE_PARM_DESC(cdb_len, "suggest CDB lengths to drivers (def=10)");
MODULE_PARM_DESC(clustering, "when set enables larger transfers (def=0)");
MODULE_PARM_DESC(delay, "response delay (def=1 jiffy); 0:imm, -1,-2:tiny");
MODULE_PARM_DESC(dev_size_mb, "size in MiB of ram shared by devs(def=8)");
MODULE_PARM_DESC(dअगर, "data integrity field type: 0-3 (def=0)");
MODULE_PARM_DESC(dix, "data integrity extensions mask (def=0)");
MODULE_PARM_DESC(dsense, "use descriptor sense format(def=0 -> fixed)");
MODULE_PARM_DESC(every_nth, "timeout every nth command(def=0)");
MODULE_PARM_DESC(fake_rw, "fake reads/writes instead of copying (def=0)");
MODULE_PARM_DESC(guard, "protection checksum: 0=crc, 1=ip (def=0)");
MODULE_PARM_DESC(host_lock, "host_lock is ignored (def=0)");
MODULE_PARM_DESC(host_max_queue,
		 "host max # of queued cmds (0 to max(def) [max_queue fixed equal for !0])");
MODULE_PARM_DESC(inq_product, "SCSI INQUIRY product string (def=\"scsi_debug\")");
MODULE_PARM_DESC(inq_rev, "SCSI INQUIRY revision string (def=\""
		 SDEBUG_VERSION "\")");
MODULE_PARM_DESC(inq_venकरोr, "SCSI INQUIRY vendor string (def=\"Linux\")");
MODULE_PARM_DESC(lbprz,
		 "on read unmapped LBs return 0 when 1 (def), return 0xff when 2");
MODULE_PARM_DESC(lbpu, "enable LBP, support UNMAP command (def=0)");
MODULE_PARM_DESC(lbpws, "enable LBP, support WRITE SAME(16) with UNMAP bit (def=0)");
MODULE_PARM_DESC(lbpws10, "enable LBP, support WRITE SAME(10) with UNMAP bit (def=0)");
MODULE_PARM_DESC(lowest_aligned, "lowest aligned lba (def=0)");
MODULE_PARM_DESC(lun_क्रमmat, "LUN format: 0->peripheral (def); 1 --> flat address method");
MODULE_PARM_DESC(max_luns, "number of LUNs per target to simulate(def=1)");
MODULE_PARM_DESC(max_queue, "max number of queued commands (1 to max(def))");
MODULE_PARM_DESC(medium_error_count, "count of sectors to return follow on MEDIUM error");
MODULE_PARM_DESC(medium_error_start, "starting sector number to return MEDIUM error");
MODULE_PARM_DESC(ndelay, "response delay in nanoseconds (def=0 -> ignore)");
MODULE_PARM_DESC(no_lun_0, "no LU number 0 (def=0 -> have lun 0)");
MODULE_PARM_DESC(no_uld, "stop ULD (e.g. sd driver) attaching (def=0))");
MODULE_PARM_DESC(num_parts, "number of partitions(def=0)");
MODULE_PARM_DESC(num_tgts, "number of targets per host to simulate(def=1)");
MODULE_PARM_DESC(opt_blks, "optimal transfer length in blocks (def=1024)");
MODULE_PARM_DESC(opt_xferlen_exp, "optimal transfer length granularity exponent (def=physblk_exp)");
MODULE_PARM_DESC(opts, "1->noise, 2->medium_err, 4->timeout, 8->recovered_err... (def=0)");
MODULE_PARM_DESC(per_host_store, "If set, next positive add_host will get new store (def=0)");
MODULE_PARM_DESC(physblk_exp, "physical block exponent (def=0)");
MODULE_PARM_DESC(poll_queues, "support for iouring iopoll queues (1 to max(submit_queues - 1))");
MODULE_PARM_DESC(ptype, "SCSI peripheral type(def=0[disk])");
MODULE_PARM_DESC(अक्रमom, "If set, uniformly randomize command duration between 0 and delay_in_ns");
MODULE_PARM_DESC(removable, "claim to have removable media (def=0)");
MODULE_PARM_DESC(scsi_level, "SCSI level to simulate(def=7[SPC-5])");
MODULE_PARM_DESC(sector_size, "logical block size in bytes (def=512)");
MODULE_PARM_DESC(statistics, "collect statistics on commands, queues (def=0)");
MODULE_PARM_DESC(strict, "stricter checks: reserved field in cdb (def=0)");
MODULE_PARM_DESC(submit_queues, "support for block multi-queue (def=1)");
MODULE_PARM_DESC(tur_ms_to_पढ़ोy, "TEST UNIT READY millisecs before initial good status (def=0)");
MODULE_PARM_DESC(unmap_alignment, "lowest aligned thin provisioning lba (def=0)");
MODULE_PARM_DESC(unmap_granularity, "thin provisioning granularity in blocks (def=1)");
MODULE_PARM_DESC(unmap_max_blocks, "max # of blocks can be unmapped in one cmd (def=0xffffffff)");
MODULE_PARM_DESC(unmap_max_desc, "max # of ranges that can be unmapped in one cmd (def=256)");
MODULE_PARM_DESC(uuid_ctl,
		 "1->use uuid for lu name, 0->don't, 2->all use same (def=0)");
MODULE_PARM_DESC(भव_gb, "virtual gigabyte (GiB) size (def=0 -> use dev_size_mb)");
MODULE_PARM_DESC(vpd_use_hostno, "0 -> dev ids ignore hostno (def=1 -> unique dev ids)");
MODULE_PARM_DESC(wp, "Write Protect (def=0)");
MODULE_PARM_DESC(ग_लिखो_same_length, "Maximum blocks per WRITE SAME cmd (def=0xffff)");
MODULE_PARM_DESC(zbc, "'none' [0]; 'aware' [1]; 'managed' [2] (def=0). Can have 'host-' prefix");
MODULE_PARM_DESC(zone_max_खोलो, "Maximum number of open zones; [0] for no limit (def=auto)");
MODULE_PARM_DESC(zone_nr_conv, "Number of conventional zones (def=1)");
MODULE_PARM_DESC(zone_size_mb, "Zone size in MiB (def=auto)");

#घोषणा SDEBUG_INFO_LEN 256
अटल अक्षर sdebug_info[SDEBUG_INFO_LEN];

अटल स्थिर अक्षर *scsi_debug_info(काष्ठा Scsi_Host *shp)
अणु
	पूर्णांक k;

	k = scnम_लिखो(sdebug_info, SDEBUG_INFO_LEN, "%s: version %s [%s]\n",
		      my_name, SDEBUG_VERSION, sdebug_version_date);
	अगर (k >= (SDEBUG_INFO_LEN - 1))
		वापस sdebug_info;
	scnम_लिखो(sdebug_info + k, SDEBUG_INFO_LEN - k,
		  "  dev_size_mb=%d, opts=0x%x, submit_queues=%d, %s=%d",
		  sdebug_dev_size_mb, sdebug_opts, submit_queues,
		  "statistics", (पूर्णांक)sdebug_statistics);
	वापस sdebug_info;
पूर्ण

/* 'echo <val> > /proc/scsi/scsi_debug/<host_id>' ग_लिखोs to opts */
अटल पूर्णांक scsi_debug_ग_लिखो_info(काष्ठा Scsi_Host *host, अक्षर *buffer,
				 पूर्णांक length)
अणु
	अक्षर arr[16];
	पूर्णांक opts;
	पूर्णांक minLen = length > 15 ? 15 : length;

	अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		वापस -EACCES;
	स_नकल(arr, buffer, minLen);
	arr[minLen] = '\0';
	अगर (1 != माला_पूछो(arr, "%d", &opts))
		वापस -EINVAL;
	sdebug_opts = opts;
	sdebug_verbose = !!(SDEBUG_OPT_NOISE & opts);
	sdebug_any_injecting_opt = !!(SDEBUG_OPT_ALL_INJECTING & opts);
	अगर (sdebug_every_nth != 0)
		tweak_cmnd_count();
	वापस length;
पूर्ण

/* Output seen with 'cat /proc/scsi/scsi_debug/<host_id>'. It will be the
 * same क्रम each scsi_debug host (अगर more than one). Some of the counters
 * output are not atomics so might be inaccurate in a busy प्रणाली. */
अटल पूर्णांक scsi_debug_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	पूर्णांक f, j, l;
	काष्ठा sdebug_queue *sqp;
	काष्ठा sdebug_host_info *sdhp;

	seq_म_लिखो(m, "scsi_debug adapter driver, version %s [%s]\n",
		   SDEBUG_VERSION, sdebug_version_date);
	seq_म_लिखो(m, "num_tgts=%d, %ssize=%d MB, opts=0x%x, every_nth=%d\n",
		   sdebug_num_tgts, "shared (ram) ", sdebug_dev_size_mb,
		   sdebug_opts, sdebug_every_nth);
	seq_म_लिखो(m, "delay=%d, ndelay=%d, max_luns=%d, sector_size=%d %s\n",
		   sdebug_jdelay, sdebug_ndelay, sdebug_max_luns,
		   sdebug_sector_size, "bytes");
	seq_म_लिखो(m, "cylinders=%d, heads=%d, sectors=%d, command aborts=%d\n",
		   sdebug_cylinders_per, sdebug_heads, sdebug_sectors_per,
		   num_पातs);
	seq_म_लिखो(m, "RESETs: device=%d, target=%d, bus=%d, host=%d\n",
		   num_dev_resets, num_target_resets, num_bus_resets,
		   num_host_resets);
	seq_म_लिखो(m, "dix_reads=%d, dix_writes=%d, dif_errors=%d\n",
		   dix_पढ़ोs, dix_ग_लिखोs, dअगर_errors);
	seq_म_लिखो(m, "usec_in_jiffy=%lu, statistics=%d\n", TICK_NSEC / 1000,
		   sdebug_statistics);
	seq_म_लिखो(m, "cmnd_count=%d, completions=%d, %s=%d, a_tsf=%d, mq_polls=%d\n",
		   atomic_पढ़ो(&sdebug_cmnd_count),
		   atomic_पढ़ो(&sdebug_completions),
		   "miss_cpus", atomic_पढ़ो(&sdebug_miss_cpus),
		   atomic_पढ़ो(&sdebug_a_tsf),
		   atomic_पढ़ो(&sdeb_mq_poll_count));

	seq_म_लिखो(m, "submit_queues=%d\n", submit_queues);
	क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp) अणु
		seq_म_लिखो(m, "  queue %d:\n", j);
		f = find_first_bit(sqp->in_use_bm, sdebug_max_queue);
		अगर (f != sdebug_max_queue) अणु
			l = find_last_bit(sqp->in_use_bm, sdebug_max_queue);
			seq_म_लिखो(m, "    in_use_bm BUSY: %s: %d,%d\n",
				   "first,last bits", f, l);
		पूर्ण
	पूर्ण

	seq_म_लिखो(m, "this host_no=%d\n", host->host_no);
	अगर (!xa_empty(per_store_ap)) अणु
		bool niu;
		पूर्णांक idx;
		अचिन्हित दीर्घ l_idx;
		काष्ठा sdeb_store_info *sip;

		seq_माला_दो(m, "\nhost list:\n");
		j = 0;
		list_क्रम_each_entry(sdhp, &sdebug_host_list, host_list) अणु
			idx = sdhp->si_idx;
			seq_म_लिखो(m, "  %d: host_no=%d, si_idx=%d\n", j,
				   sdhp->shost->host_no, idx);
			++j;
		पूर्ण
		seq_म_लिखो(m, "\nper_store array [most_recent_idx=%d]:\n",
			   sdeb_most_recent_idx);
		j = 0;
		xa_क्रम_each(per_store_ap, l_idx, sip) अणु
			niu = xa_get_mark(per_store_ap, l_idx,
					  SDEB_XA_NOT_IN_USE);
			idx = (पूर्णांक)l_idx;
			seq_म_लिखो(m, "  %d: idx=%d%s\n", j, idx,
				   (niu ? "  not_in_use" : ""));
			++j;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार delay_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_jdelay);
पूर्ण
/* Returns -EBUSY अगर jdelay is being changed and commands are queued. The unit
 * of delay is jअगरfies.
 */
अटल sमाप_प्रकार delay_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	पूर्णांक jdelay, res;

	अगर (count > 0 && माला_पूछो(buf, "%d", &jdelay) == 1) अणु
		res = count;
		अगर (sdebug_jdelay != jdelay) अणु
			पूर्णांक j, k;
			काष्ठा sdebug_queue *sqp;

			block_unblock_all_queues(true);
			क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues;
			     ++j, ++sqp) अणु
				k = find_first_bit(sqp->in_use_bm,
						   sdebug_max_queue);
				अगर (k != sdebug_max_queue) अणु
					res = -EBUSY;   /* queued commands */
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (res > 0) अणु
				sdebug_jdelay = jdelay;
				sdebug_ndelay = 0;
			पूर्ण
			block_unblock_all_queues(false);
		पूर्ण
		वापस res;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(delay);

अटल sमाप_प्रकार ndelay_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_ndelay);
पूर्ण
/* Returns -EBUSY अगर ndelay is being changed and commands are queued */
/* If > 0 and accepted then sdebug_jdelay is set to JDELAY_OVERRIDDEN */
अटल sमाप_प्रकार ndelay_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक ndelay, res;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &ndelay)) &&
	    (ndelay >= 0) && (ndelay < (1000 * 1000 * 1000))) अणु
		res = count;
		अगर (sdebug_ndelay != ndelay) अणु
			पूर्णांक j, k;
			काष्ठा sdebug_queue *sqp;

			block_unblock_all_queues(true);
			क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues;
			     ++j, ++sqp) अणु
				k = find_first_bit(sqp->in_use_bm,
						   sdebug_max_queue);
				अगर (k != sdebug_max_queue) अणु
					res = -EBUSY;   /* queued commands */
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (res > 0) अणु
				sdebug_ndelay = ndelay;
				sdebug_jdelay = ndelay  ? JDELAY_OVERRIDDEN
							: DEF_JDELAY;
			पूर्ण
			block_unblock_all_queues(false);
		पूर्ण
		वापस res;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(ndelay);

अटल sमाप_प्रकार opts_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%x\n", sdebug_opts);
पूर्ण

अटल sमाप_प्रकार opts_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	पूर्णांक opts;
	अक्षर work[20];

	अगर (माला_पूछो(buf, "%10s", work) == 1) अणु
		अगर (strnहालcmp(work, "0x", 2) == 0) अणु
			अगर (kstrtoपूर्णांक(work + 2, 16, &opts) == 0)
				जाओ opts_करोne;
		पूर्ण अन्यथा अणु
			अगर (kstrtoपूर्णांक(work, 10, &opts) == 0)
				जाओ opts_करोne;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
opts_करोne:
	sdebug_opts = opts;
	sdebug_verbose = !!(SDEBUG_OPT_NOISE & opts);
	sdebug_any_injecting_opt = !!(SDEBUG_OPT_ALL_INJECTING & opts);
	tweak_cmnd_count();
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(opts);

अटल sमाप_प्रकार ptype_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_ptype);
पूर्ण
अटल sमाप_प्रकार ptype_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	पूर्णांक n;

	/* Cannot change from or to TYPE_ZBC with sysfs */
	अगर (sdebug_ptype == TYPE_ZBC)
		वापस -EINVAL;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		अगर (n == TYPE_ZBC)
			वापस -EINVAL;
		sdebug_ptype = n;
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(ptype);

अटल sमाप_प्रकार dsense_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_dsense);
पूर्ण
अटल sमाप_प्रकार dsense_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		sdebug_dsense = n;
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(dsense);

अटल sमाप_प्रकार fake_rw_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_fake_rw);
पूर्ण
अटल sमाप_प्रकार fake_rw_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	पूर्णांक n, idx;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		bool want_store = (n == 0);
		काष्ठा sdebug_host_info *sdhp;

		n = (n > 0);
		sdebug_fake_rw = (sdebug_fake_rw > 0);
		अगर (sdebug_fake_rw == n)
			वापस count;	/* not transitioning so करो nothing */

		अगर (want_store) अणु	/* 1 --> 0 transition, set up store */
			अगर (sdeb_first_idx < 0) अणु
				idx = sdebug_add_store();
				अगर (idx < 0)
					वापस idx;
			पूर्ण अन्यथा अणु
				idx = sdeb_first_idx;
				xa_clear_mark(per_store_ap, idx,
					      SDEB_XA_NOT_IN_USE);
			पूर्ण
			/* make all hosts use same store */
			list_क्रम_each_entry(sdhp, &sdebug_host_list,
					    host_list) अणु
				अगर (sdhp->si_idx != idx) अणु
					xa_set_mark(per_store_ap, sdhp->si_idx,
						    SDEB_XA_NOT_IN_USE);
					sdhp->si_idx = idx;
				पूर्ण
			पूर्ण
			sdeb_most_recent_idx = idx;
		पूर्ण अन्यथा अणु	/* 0 --> 1 transition is trigger क्रम shrink */
			sdebug_erase_all_stores(true /* apart from first */);
		पूर्ण
		sdebug_fake_rw = n;
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(fake_rw);

अटल sमाप_प्रकार no_lun_0_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_no_lun_0);
पूर्ण
अटल sमाप_प्रकार no_lun_0_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		sdebug_no_lun_0 = n;
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(no_lun_0);

अटल sमाप_प्रकार num_tgts_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_num_tgts);
पूर्ण
अटल sमाप_प्रकार num_tgts_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		sdebug_num_tgts = n;
		sdebug_max_tgts_luns();
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(num_tgts);

अटल sमाप_प्रकार dev_size_mb_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_dev_size_mb);
पूर्ण
अटल DRIVER_ATTR_RO(dev_size_mb);

अटल sमाप_प्रकार per_host_store_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_per_host_store);
पूर्ण

अटल sमाप_प्रकार per_host_store_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
				    माप_प्रकार count)
अणु
	bool v;

	अगर (kstrtobool(buf, &v))
		वापस -EINVAL;

	sdebug_per_host_store = v;
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(per_host_store);

अटल sमाप_प्रकार num_parts_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_num_parts);
पूर्ण
अटल DRIVER_ATTR_RO(num_parts);

अटल sमाप_प्रकार every_nth_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_every_nth);
पूर्ण
अटल sमाप_प्रकार every_nth_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	पूर्णांक nth;
	अक्षर work[20];

	अगर (माला_पूछो(buf, "%10s", work) == 1) अणु
		अगर (strnहालcmp(work, "0x", 2) == 0) अणु
			अगर (kstrtoपूर्णांक(work + 2, 16, &nth) == 0)
				जाओ every_nth_करोne;
		पूर्ण अन्यथा अणु
			अगर (kstrtoपूर्णांक(work, 10, &nth) == 0)
				जाओ every_nth_करोne;
		पूर्ण
	पूर्ण
	वापस -EINVAL;

every_nth_करोne:
	sdebug_every_nth = nth;
	अगर (nth && !sdebug_statistics) अणु
		pr_info("every_nth needs statistics=1, set it\n");
		sdebug_statistics = true;
	पूर्ण
	tweak_cmnd_count();
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(every_nth);

अटल sमाप_प्रकार lun_क्रमmat_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (पूर्णांक)sdebug_lun_am);
पूर्ण
अटल sमाप_प्रकार lun_क्रमmat_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक n;
	bool changed;

	अगर (kstrtoपूर्णांक(buf, 0, &n))
		वापस -EINVAL;
	अगर (n >= 0) अणु
		अगर (n > (पूर्णांक)SAM_LUN_AM_FLAT) अणु
			pr_warn("only LUN address methods 0 and 1 are supported\n");
			वापस -EINVAL;
		पूर्ण
		changed = ((पूर्णांक)sdebug_lun_am != n);
		sdebug_lun_am = n;
		अगर (changed && sdebug_scsi_level >= 5) अणु	/* >= SPC-3 */
			काष्ठा sdebug_host_info *sdhp;
			काष्ठा sdebug_dev_info *dp;

			spin_lock(&sdebug_host_list_lock);
			list_क्रम_each_entry(sdhp, &sdebug_host_list, host_list) अणु
				list_क्रम_each_entry(dp, &sdhp->dev_info_list, dev_list) अणु
					set_bit(SDEBUG_UA_LUNS_CHANGED, dp->uas_bm);
				पूर्ण
			पूर्ण
			spin_unlock(&sdebug_host_list_lock);
		पूर्ण
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(lun_क्रमmat);

अटल sमाप_प्रकार max_luns_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_max_luns);
पूर्ण
अटल sमाप_प्रकार max_luns_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक n;
	bool changed;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		अगर (n > 256) अणु
			pr_warn("max_luns can be no more than 256\n");
			वापस -EINVAL;
		पूर्ण
		changed = (sdebug_max_luns != n);
		sdebug_max_luns = n;
		sdebug_max_tgts_luns();
		अगर (changed && (sdebug_scsi_level >= 5)) अणु	/* >= SPC-3 */
			काष्ठा sdebug_host_info *sdhp;
			काष्ठा sdebug_dev_info *dp;

			spin_lock(&sdebug_host_list_lock);
			list_क्रम_each_entry(sdhp, &sdebug_host_list,
					    host_list) अणु
				list_क्रम_each_entry(dp, &sdhp->dev_info_list,
						    dev_list) अणु
					set_bit(SDEBUG_UA_LUNS_CHANGED,
						dp->uas_bm);
				पूर्ण
			पूर्ण
			spin_unlock(&sdebug_host_list_lock);
		पूर्ण
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(max_luns);

अटल sमाप_प्रकार max_queue_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_max_queue);
पूर्ण
/* N.B. max_queue can be changed जबतक there are queued commands. In flight
 * commands beyond the new max_queue will be completed. */
अटल sमाप_प्रकार max_queue_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	पूर्णांक j, n, k, a;
	काष्ठा sdebug_queue *sqp;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n > 0) &&
	    (n <= SDEBUG_CANQUEUE) &&
	    (sdebug_host_max_queue == 0)) अणु
		block_unblock_all_queues(true);
		k = 0;
		क्रम (j = 0, sqp = sdebug_q_arr; j < submit_queues;
		     ++j, ++sqp) अणु
			a = find_last_bit(sqp->in_use_bm, SDEBUG_CANQUEUE);
			अगर (a > k)
				k = a;
		पूर्ण
		sdebug_max_queue = n;
		अगर (k == SDEBUG_CANQUEUE)
			atomic_set(&retired_max_queue, 0);
		अन्यथा अगर (k >= n)
			atomic_set(&retired_max_queue, k + 1);
		अन्यथा
			atomic_set(&retired_max_queue, 0);
		block_unblock_all_queues(false);
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(max_queue);

अटल sमाप_प्रकार host_max_queue_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_host_max_queue);
पूर्ण

/*
 * Since this is used क्रम .can_queue, and we get the hc_idx tag from the biपंचांगap
 * in range [0, sdebug_host_max_queue), we can't change it.
 */
अटल DRIVER_ATTR_RO(host_max_queue);

अटल sमाप_प्रकार no_uld_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_no_uld);
पूर्ण
अटल DRIVER_ATTR_RO(no_uld);

अटल sमाप_प्रकार scsi_level_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_scsi_level);
पूर्ण
अटल DRIVER_ATTR_RO(scsi_level);

अटल sमाप_प्रकार भव_gb_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_भव_gb);
पूर्ण
अटल sमाप_प्रकार भव_gb_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक n;
	bool changed;

	/* Ignore capacity change क्रम ZBC drives क्रम now */
	अगर (sdeb_zbc_in_use)
		वापस -ENOTSUPP;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		changed = (sdebug_भव_gb != n);
		sdebug_भव_gb = n;
		sdebug_capacity = get_sdebug_capacity();
		अगर (changed) अणु
			काष्ठा sdebug_host_info *sdhp;
			काष्ठा sdebug_dev_info *dp;

			spin_lock(&sdebug_host_list_lock);
			list_क्रम_each_entry(sdhp, &sdebug_host_list,
					    host_list) अणु
				list_क्रम_each_entry(dp, &sdhp->dev_info_list,
						    dev_list) अणु
					set_bit(SDEBUG_UA_CAPACITY_CHANGED,
						dp->uas_bm);
				पूर्ण
			पूर्ण
			spin_unlock(&sdebug_host_list_lock);
		पूर्ण
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(भव_gb);

अटल sमाप_प्रकार add_host_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	/* असलolute number of hosts currently active is what is shown */
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_num_hosts);
पूर्ण

अटल sमाप_प्रकार add_host_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	bool found;
	अचिन्हित दीर्घ idx;
	काष्ठा sdeb_store_info *sip;
	bool want_phs = (sdebug_fake_rw == 0) && sdebug_per_host_store;
	पूर्णांक delta_hosts;

	अगर (माला_पूछो(buf, "%d", &delta_hosts) != 1)
		वापस -EINVAL;
	अगर (delta_hosts > 0) अणु
		करो अणु
			found = false;
			अगर (want_phs) अणु
				xa_क्रम_each_marked(per_store_ap, idx, sip,
						   SDEB_XA_NOT_IN_USE) अणु
					sdeb_most_recent_idx = (पूर्णांक)idx;
					found = true;
					अवरोध;
				पूर्ण
				अगर (found)	/* re-use हाल */
					sdebug_add_host_helper((पूर्णांक)idx);
				अन्यथा
					sdebug_करो_add_host(true);
			पूर्ण अन्यथा अणु
				sdebug_करो_add_host(false);
			पूर्ण
		पूर्ण जबतक (--delta_hosts);
	पूर्ण अन्यथा अगर (delta_hosts < 0) अणु
		करो अणु
			sdebug_करो_हटाओ_host(false);
		पूर्ण जबतक (++delta_hosts);
	पूर्ण
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(add_host);

अटल sमाप_प्रकार vpd_use_hostno_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_vpd_use_hostno);
पूर्ण
अटल sमाप_प्रकार vpd_use_hostno_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
				    माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		sdebug_vpd_use_hostno = n;
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(vpd_use_hostno);

अटल sमाप_प्रकार statistics_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (पूर्णांक)sdebug_statistics);
पूर्ण
अटल sमाप_प्रकार statistics_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (माला_पूछो(buf, "%d", &n) == 1) && (n >= 0)) अणु
		अगर (n > 0)
			sdebug_statistics = true;
		अन्यथा अणु
			clear_queue_stats();
			sdebug_statistics = false;
		पूर्ण
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(statistics);

अटल sमाप_प्रकार sector_size_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", sdebug_sector_size);
पूर्ण
अटल DRIVER_ATTR_RO(sector_size);

अटल sमाप_प्रकार submit_queues_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", submit_queues);
पूर्ण
अटल DRIVER_ATTR_RO(submit_queues);

अटल sमाप_प्रकार dix_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_dix);
पूर्ण
अटल DRIVER_ATTR_RO(dix);

अटल sमाप_प्रकार dअगर_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_dअगर);
पूर्ण
अटल DRIVER_ATTR_RO(dअगर);

अटल sमाप_प्रकार guard_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", sdebug_guard);
पूर्ण
अटल DRIVER_ATTR_RO(guard);

अटल sमाप_प्रकार ato_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_ato);
पूर्ण
अटल DRIVER_ATTR_RO(ato);

अटल sमाप_प्रकार map_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	sमाप_प्रकार count = 0;

	अगर (!scsi_debug_lbp())
		वापस scnम_लिखो(buf, PAGE_SIZE, "0-%u\n",
				 sdebug_store_sectors);

	अगर (sdebug_fake_rw == 0 && !xa_empty(per_store_ap)) अणु
		काष्ठा sdeb_store_info *sip = xa_load(per_store_ap, 0);

		अगर (sip)
			count = scnम_लिखो(buf, PAGE_SIZE - 1, "%*pbl",
					  (पूर्णांक)map_size, sip->map_storep);
	पूर्ण
	buf[count++] = '\n';
	buf[count] = '\0';

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RO(map);

अटल sमाप_प्रकार अक्रमom_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_अक्रमom);
पूर्ण

अटल sमाप_प्रकार अक्रमom_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	bool v;

	अगर (kstrtobool(buf, &v))
		वापस -EINVAL;

	sdebug_अक्रमom = v;
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(अक्रमom);

अटल sमाप_प्रकार removable_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_removable ? 1 : 0);
पूर्ण
अटल sमाप_प्रकार removable_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		sdebug_removable = (n > 0);
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(removable);

अटल sमाप_प्रकार host_lock_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!sdebug_host_lock);
पूर्ण
/* N.B. sdebug_host_lock करोes nothing, kept क्रम backward compatibility */
अटल sमाप_प्रकार host_lock_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		sdebug_host_lock = (n > 0);
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(host_lock);

अटल sमाप_प्रकार strict_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!sdebug_strict);
पूर्ण
अटल sमाप_प्रकार strict_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक n;

	अगर ((count > 0) && (1 == माला_पूछो(buf, "%d", &n)) && (n >= 0)) अणु
		sdebug_strict = (n > 0);
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(strict);

अटल sमाप_प्रकार uuid_ctl_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!sdebug_uuid_ctl);
पूर्ण
अटल DRIVER_ATTR_RO(uuid_ctl);

अटल sमाप_प्रकार cdb_len_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdebug_cdb_len);
पूर्ण
अटल sमाप_प्रकार cdb_len_store(काष्ठा device_driver *ddp, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	पूर्णांक ret, n;

	ret = kstrtoपूर्णांक(buf, 0, &n);
	अगर (ret)
		वापस ret;
	sdebug_cdb_len = n;
	all_config_cdb_len();
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(cdb_len);

अटल स्थिर अक्षर * स्थिर zbc_model_strs_a[] = अणु
	[BLK_ZONED_NONE] = "none",
	[BLK_ZONED_HA]   = "host-aware",
	[BLK_ZONED_HM]   = "host-managed",
पूर्ण;

अटल स्थिर अक्षर * स्थिर zbc_model_strs_b[] = अणु
	[BLK_ZONED_NONE] = "no",
	[BLK_ZONED_HA]   = "aware",
	[BLK_ZONED_HM]   = "managed",
पूर्ण;

अटल स्थिर अक्षर * स्थिर zbc_model_strs_c[] = अणु
	[BLK_ZONED_NONE] = "0",
	[BLK_ZONED_HA]   = "1",
	[BLK_ZONED_HM]   = "2",
पूर्ण;

अटल पूर्णांक sdeb_zbc_model_str(स्थिर अक्षर *cp)
अणु
	पूर्णांक res = sysfs_match_string(zbc_model_strs_a, cp);

	अगर (res < 0) अणु
		res = sysfs_match_string(zbc_model_strs_b, cp);
		अगर (res < 0) अणु
			res = sysfs_match_string(zbc_model_strs_c, cp);
			अगर (res < 0)
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल sमाप_प्रकार zbc_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
			 zbc_model_strs_a[sdeb_zbc_model]);
पूर्ण
अटल DRIVER_ATTR_RO(zbc);

अटल sमाप_प्रकार tur_ms_to_पढ़ोy_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", sdeb_tur_ms_to_पढ़ोy);
पूर्ण
अटल DRIVER_ATTR_RO(tur_ms_to_पढ़ोy);

/* Note: The following array creates attribute files in the
   /sys/bus/pseuकरो/drivers/scsi_debug directory. The advantage of these
   files (over those found in the /sys/module/scsi_debug/parameters
   directory) is that auxiliary actions can be triggered when an attribute
   is changed. For example see: add_host_store() above.
 */

अटल काष्ठा attribute *sdebug_drv_attrs[] = अणु
	&driver_attr_delay.attr,
	&driver_attr_opts.attr,
	&driver_attr_ptype.attr,
	&driver_attr_dsense.attr,
	&driver_attr_fake_rw.attr,
	&driver_attr_host_max_queue.attr,
	&driver_attr_no_lun_0.attr,
	&driver_attr_num_tgts.attr,
	&driver_attr_dev_size_mb.attr,
	&driver_attr_num_parts.attr,
	&driver_attr_every_nth.attr,
	&driver_attr_lun_क्रमmat.attr,
	&driver_attr_max_luns.attr,
	&driver_attr_max_queue.attr,
	&driver_attr_no_uld.attr,
	&driver_attr_scsi_level.attr,
	&driver_attr_भव_gb.attr,
	&driver_attr_add_host.attr,
	&driver_attr_per_host_store.attr,
	&driver_attr_vpd_use_hostno.attr,
	&driver_attr_sector_size.attr,
	&driver_attr_statistics.attr,
	&driver_attr_submit_queues.attr,
	&driver_attr_dix.attr,
	&driver_attr_dअगर.attr,
	&driver_attr_guard.attr,
	&driver_attr_ato.attr,
	&driver_attr_map.attr,
	&driver_attr_अक्रमom.attr,
	&driver_attr_removable.attr,
	&driver_attr_host_lock.attr,
	&driver_attr_ndelay.attr,
	&driver_attr_strict.attr,
	&driver_attr_uuid_ctl.attr,
	&driver_attr_cdb_len.attr,
	&driver_attr_tur_ms_to_पढ़ोy.attr,
	&driver_attr_zbc.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(sdebug_drv);

अटल काष्ठा device *pseuकरो_primary;

अटल पूर्णांक __init scsi_debug_init(व्योम)
अणु
	bool want_store = (sdebug_fake_rw == 0);
	अचिन्हित दीर्घ sz;
	पूर्णांक k, ret, hosts_to_add;
	पूर्णांक idx = -1;

	ramdisk_lck_a[0] = &atomic_rw;
	ramdisk_lck_a[1] = &atomic_rw2;
	atomic_set(&retired_max_queue, 0);

	अगर (sdebug_ndelay >= 1000 * 1000 * 1000) अणु
		pr_warn("ndelay must be less than 1 second, ignored\n");
		sdebug_ndelay = 0;
	पूर्ण अन्यथा अगर (sdebug_ndelay > 0)
		sdebug_jdelay = JDELAY_OVERRIDDEN;

	चयन (sdebug_sector_size) अणु
	हाल  512:
	हाल 1024:
	हाल 2048:
	हाल 4096:
		अवरोध;
	शेष:
		pr_err("invalid sector_size %d\n", sdebug_sector_size);
		वापस -EINVAL;
	पूर्ण

	चयन (sdebug_dअगर) अणु
	हाल T10_PI_TYPE0_PROTECTION:
		अवरोध;
	हाल T10_PI_TYPE1_PROTECTION:
	हाल T10_PI_TYPE2_PROTECTION:
	हाल T10_PI_TYPE3_PROTECTION:
		have_dअगर_prot = true;
		अवरोध;

	शेष:
		pr_err("dif must be 0, 1, 2 or 3\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sdebug_num_tgts < 0) अणु
		pr_err("num_tgts must be >= 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sdebug_guard > 1) अणु
		pr_err("guard must be 0 or 1\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sdebug_ato > 1) अणु
		pr_err("ato must be 0 or 1\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sdebug_physblk_exp > 15) अणु
		pr_err("invalid physblk_exp %u\n", sdebug_physblk_exp);
		वापस -EINVAL;
	पूर्ण

	sdebug_lun_am = sdebug_lun_am_i;
	अगर (sdebug_lun_am > SAM_LUN_AM_FLAT) अणु
		pr_warn("Invalid LUN format %u, using default\n", (पूर्णांक)sdebug_lun_am);
		sdebug_lun_am = SAM_LUN_AM_PERIPHERAL;
	पूर्ण

	अगर (sdebug_max_luns > 256) अणु
		अगर (sdebug_max_luns > 16384) अणु
			pr_warn("max_luns can be no more than 16384, use default\n");
			sdebug_max_luns = DEF_MAX_LUNS;
		पूर्ण
		sdebug_lun_am = SAM_LUN_AM_FLAT;
	पूर्ण

	अगर (sdebug_lowest_aligned > 0x3fff) अणु
		pr_err("lowest_aligned too big: %u\n", sdebug_lowest_aligned);
		वापस -EINVAL;
	पूर्ण

	अगर (submit_queues < 1) अणु
		pr_err("submit_queues must be 1 or more\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((sdebug_max_queue > SDEBUG_CANQUEUE) || (sdebug_max_queue < 1)) अणु
		pr_err("max_queue must be in range [1, %d]\n", SDEBUG_CANQUEUE);
		वापस -EINVAL;
	पूर्ण

	अगर ((sdebug_host_max_queue > SDEBUG_CANQUEUE) ||
	    (sdebug_host_max_queue < 0)) अणु
		pr_err("host_max_queue must be in range [0 %d]\n",
		       SDEBUG_CANQUEUE);
		वापस -EINVAL;
	पूर्ण

	अगर (sdebug_host_max_queue &&
	    (sdebug_max_queue != sdebug_host_max_queue)) अणु
		sdebug_max_queue = sdebug_host_max_queue;
		pr_warn("fixing max submit queue depth to host max queue depth, %d\n",
			sdebug_max_queue);
	पूर्ण

	sdebug_q_arr = kसुस्मृति(submit_queues, माप(काष्ठा sdebug_queue),
			       GFP_KERNEL);
	अगर (sdebug_q_arr == शून्य)
		वापस -ENOMEM;
	क्रम (k = 0; k < submit_queues; ++k)
		spin_lock_init(&sdebug_q_arr[k].qc_lock);

	/*
	 * check क्रम host managed zoned block device specअगरied with
	 * ptype=0x14 or zbc=XXX.
	 */
	अगर (sdebug_ptype == TYPE_ZBC) अणु
		sdeb_zbc_model = BLK_ZONED_HM;
	पूर्ण अन्यथा अगर (sdeb_zbc_model_s && *sdeb_zbc_model_s) अणु
		k = sdeb_zbc_model_str(sdeb_zbc_model_s);
		अगर (k < 0) अणु
			ret = k;
			जाओ मुक्त_q_arr;
		पूर्ण
		sdeb_zbc_model = k;
		चयन (sdeb_zbc_model) अणु
		हाल BLK_ZONED_NONE:
		हाल BLK_ZONED_HA:
			sdebug_ptype = TYPE_DISK;
			अवरोध;
		हाल BLK_ZONED_HM:
			sdebug_ptype = TYPE_ZBC;
			अवरोध;
		शेष:
			pr_err("Invalid ZBC model\n");
			ret = -EINVAL;
			जाओ मुक्त_q_arr;
		पूर्ण
	पूर्ण
	अगर (sdeb_zbc_model != BLK_ZONED_NONE) अणु
		sdeb_zbc_in_use = true;
		अगर (sdebug_dev_size_mb == DEF_DEV_SIZE_PRE_INIT)
			sdebug_dev_size_mb = DEF_ZBC_DEV_SIZE_MB;
	पूर्ण

	अगर (sdebug_dev_size_mb == DEF_DEV_SIZE_PRE_INIT)
		sdebug_dev_size_mb = DEF_DEV_SIZE_MB;
	अगर (sdebug_dev_size_mb < 1)
		sdebug_dev_size_mb = 1;  /* क्रमce minimum 1 MB ramdisk */
	sz = (अचिन्हित दीर्घ)sdebug_dev_size_mb * 1048576;
	sdebug_store_sectors = sz / sdebug_sector_size;
	sdebug_capacity = get_sdebug_capacity();

	/* play around with geometry, करोn't waste too much on track 0 */
	sdebug_heads = 8;
	sdebug_sectors_per = 32;
	अगर (sdebug_dev_size_mb >= 256)
		sdebug_heads = 64;
	अन्यथा अगर (sdebug_dev_size_mb >= 16)
		sdebug_heads = 32;
	sdebug_cylinders_per = (अचिन्हित दीर्घ)sdebug_capacity /
			       (sdebug_sectors_per * sdebug_heads);
	अगर (sdebug_cylinders_per >= 1024) अणु
		/* other LLDs करो this; implies >= 1GB ram disk ... */
		sdebug_heads = 255;
		sdebug_sectors_per = 63;
		sdebug_cylinders_per = (अचिन्हित दीर्घ)sdebug_capacity /
			       (sdebug_sectors_per * sdebug_heads);
	पूर्ण
	अगर (scsi_debug_lbp()) अणु
		sdebug_unmap_max_blocks =
			clamp(sdebug_unmap_max_blocks, 0U, 0xffffffffU);

		sdebug_unmap_max_desc =
			clamp(sdebug_unmap_max_desc, 0U, 256U);

		sdebug_unmap_granularity =
			clamp(sdebug_unmap_granularity, 1U, 0xffffffffU);

		अगर (sdebug_unmap_alignment &&
		    sdebug_unmap_granularity <=
		    sdebug_unmap_alignment) अणु
			pr_err("ERR: unmap_granularity <= unmap_alignment\n");
			ret = -EINVAL;
			जाओ मुक्त_q_arr;
		पूर्ण
	पूर्ण
	xa_init_flags(per_store_ap, XA_FLAGS_ALLOC | XA_FLAGS_LOCK_IRQ);
	अगर (want_store) अणु
		idx = sdebug_add_store();
		अगर (idx < 0) अणु
			ret = idx;
			जाओ मुक्त_q_arr;
		पूर्ण
	पूर्ण

	pseuकरो_primary = root_device_रेजिस्टर("pseudo_0");
	अगर (IS_ERR(pseuकरो_primary)) अणु
		pr_warn("root_device_register() error\n");
		ret = PTR_ERR(pseuकरो_primary);
		जाओ मुक्त_vm;
	पूर्ण
	ret = bus_रेजिस्टर(&pseuकरो_lld_bus);
	अगर (ret < 0) अणु
		pr_warn("bus_register error: %d\n", ret);
		जाओ dev_unreg;
	पूर्ण
	ret = driver_रेजिस्टर(&sdebug_driverfs_driver);
	अगर (ret < 0) अणु
		pr_warn("driver_register error: %d\n", ret);
		जाओ bus_unreg;
	पूर्ण

	hosts_to_add = sdebug_add_host;
	sdebug_add_host = 0;

	क्रम (k = 0; k < hosts_to_add; k++) अणु
		अगर (want_store && k == 0) अणु
			ret = sdebug_add_host_helper(idx);
			अगर (ret < 0) अणु
				pr_err("add_host_helper k=%d, error=%d\n",
				       k, -ret);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = sdebug_करो_add_host(want_store &&
						 sdebug_per_host_store);
			अगर (ret < 0) अणु
				pr_err("add_host k=%d error=%d\n", k, -ret);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (sdebug_verbose)
		pr_info("built %d host(s)\n", sdebug_num_hosts);

	वापस 0;

bus_unreg:
	bus_unरेजिस्टर(&pseuकरो_lld_bus);
dev_unreg:
	root_device_unरेजिस्टर(pseuकरो_primary);
मुक्त_vm:
	sdebug_erase_store(idx, शून्य);
मुक्त_q_arr:
	kमुक्त(sdebug_q_arr);
	वापस ret;
पूर्ण

अटल व्योम __निकास scsi_debug_निकास(व्योम)
अणु
	पूर्णांक k = sdebug_num_hosts;

	stop_all_queued();
	क्रम (; k; k--)
		sdebug_करो_हटाओ_host(true);
	मुक्त_all_queued();
	driver_unरेजिस्टर(&sdebug_driverfs_driver);
	bus_unरेजिस्टर(&pseuकरो_lld_bus);
	root_device_unरेजिस्टर(pseuकरो_primary);

	sdebug_erase_all_stores(false);
	xa_destroy(per_store_ap);
	kमुक्त(sdebug_q_arr);
पूर्ण

device_initcall(scsi_debug_init);
module_निकास(scsi_debug_निकास);

अटल व्योम sdebug_release_adapter(काष्ठा device *dev)
अणु
	काष्ठा sdebug_host_info *sdbg_host;

	sdbg_host = to_sdebug_host(dev);
	kमुक्त(sdbg_host);
पूर्ण

/* idx must be valid, अगर sip is शून्य then it will be obtained using idx */
अटल व्योम sdebug_erase_store(पूर्णांक idx, काष्ठा sdeb_store_info *sip)
अणु
	अगर (idx < 0)
		वापस;
	अगर (!sip) अणु
		अगर (xa_empty(per_store_ap))
			वापस;
		sip = xa_load(per_store_ap, idx);
		अगर (!sip)
			वापस;
	पूर्ण
	vमुक्त(sip->map_storep);
	vमुक्त(sip->dअगर_storep);
	vमुक्त(sip->storep);
	xa_erase(per_store_ap, idx);
	kमुक्त(sip);
पूर्ण

/* Assume apart_from_first==false only in shutकरोwn हाल. */
अटल व्योम sdebug_erase_all_stores(bool apart_from_first)
अणु
	अचिन्हित दीर्घ idx;
	काष्ठा sdeb_store_info *sip = शून्य;

	xa_क्रम_each(per_store_ap, idx, sip) अणु
		अगर (apart_from_first)
			apart_from_first = false;
		अन्यथा
			sdebug_erase_store(idx, sip);
	पूर्ण
	अगर (apart_from_first)
		sdeb_most_recent_idx = sdeb_first_idx;
पूर्ण

/*
 * Returns store xarray new element index (idx) अगर >=0 अन्यथा negated त्रुटि_सं.
 * Limit the number of stores to 65536.
 */
अटल पूर्णांक sdebug_add_store(व्योम)
अणु
	पूर्णांक res;
	u32 n_idx;
	अचिन्हित दीर्घ अगरlags;
	अचिन्हित दीर्घ sz = (अचिन्हित दीर्घ)sdebug_dev_size_mb * 1048576;
	काष्ठा sdeb_store_info *sip = शून्य;
	काष्ठा xa_limit xal = अणु .max = 1 << 16, .min = 0 पूर्ण;

	sip = kzalloc(माप(*sip), GFP_KERNEL);
	अगर (!sip)
		वापस -ENOMEM;

	xa_lock_irqsave(per_store_ap, अगरlags);
	res = __xa_alloc(per_store_ap, &n_idx, sip, xal, GFP_ATOMIC);
	अगर (unlikely(res < 0)) अणु
		xa_unlock_irqrestore(per_store_ap, अगरlags);
		kमुक्त(sip);
		pr_warn("%s: xa_alloc() errno=%d\n", __func__, -res);
		वापस res;
	पूर्ण
	sdeb_most_recent_idx = n_idx;
	अगर (sdeb_first_idx < 0)
		sdeb_first_idx = n_idx;
	xa_unlock_irqrestore(per_store_ap, अगरlags);

	res = -ENOMEM;
	sip->storep = vzalloc(sz);
	अगर (!sip->storep) अणु
		pr_err("user data oom\n");
		जाओ err;
	पूर्ण
	अगर (sdebug_num_parts > 0)
		sdebug_build_parts(sip->storep, sz);

	/* DIF/DIX: what T10 calls Protection Inक्रमmation (PI) */
	अगर (sdebug_dix) अणु
		पूर्णांक dअगर_size;

		dअगर_size = sdebug_store_sectors * माप(काष्ठा t10_pi_tuple);
		sip->dअगर_storep = vदो_स्मृति(dअगर_size);

		pr_info("dif_storep %u bytes @ %pK\n", dअगर_size,
			sip->dअगर_storep);

		अगर (!sip->dअगर_storep) अणु
			pr_err("DIX oom\n");
			जाओ err;
		पूर्ण
		स_रखो(sip->dअगर_storep, 0xff, dअगर_size);
	पूर्ण
	/* Logical Block Provisioning */
	अगर (scsi_debug_lbp()) अणु
		map_size = lba_to_map_index(sdebug_store_sectors - 1) + 1;
		sip->map_storep = vदो_स्मृति(array_size(माप(दीर्घ),
						     BITS_TO_LONGS(map_size)));

		pr_info("%lu provisioning blocks\n", map_size);

		अगर (!sip->map_storep) अणु
			pr_err("LBP map oom\n");
			जाओ err;
		पूर्ण

		biपंचांगap_zero(sip->map_storep, map_size);

		/* Map first 1KB क्रम partition table */
		अगर (sdebug_num_parts)
			map_region(sip, 0, 2);
	पूर्ण

	rwlock_init(&sip->macc_lck);
	वापस (पूर्णांक)n_idx;
err:
	sdebug_erase_store((पूर्णांक)n_idx, sip);
	pr_warn("%s: failed, errno=%d\n", __func__, -res);
	वापस res;
पूर्ण

अटल पूर्णांक sdebug_add_host_helper(पूर्णांक per_host_idx)
अणु
	पूर्णांक k, devs_per_host, idx;
	पूर्णांक error = -ENOMEM;
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा sdebug_dev_info *sdbg_devinfo, *पंचांगp;

	sdbg_host = kzalloc(माप(*sdbg_host), GFP_KERNEL);
	अगर (!sdbg_host)
		वापस -ENOMEM;
	idx = (per_host_idx < 0) ? sdeb_first_idx : per_host_idx;
	अगर (xa_get_mark(per_store_ap, idx, SDEB_XA_NOT_IN_USE))
		xa_clear_mark(per_store_ap, idx, SDEB_XA_NOT_IN_USE);
	sdbg_host->si_idx = idx;

	INIT_LIST_HEAD(&sdbg_host->dev_info_list);

	devs_per_host = sdebug_num_tgts * sdebug_max_luns;
	क्रम (k = 0; k < devs_per_host; k++) अणु
		sdbg_devinfo = sdebug_device_create(sdbg_host, GFP_KERNEL);
		अगर (!sdbg_devinfo)
			जाओ clean;
	पूर्ण

	spin_lock(&sdebug_host_list_lock);
	list_add_tail(&sdbg_host->host_list, &sdebug_host_list);
	spin_unlock(&sdebug_host_list_lock);

	sdbg_host->dev.bus = &pseuकरो_lld_bus;
	sdbg_host->dev.parent = pseuकरो_primary;
	sdbg_host->dev.release = &sdebug_release_adapter;
	dev_set_name(&sdbg_host->dev, "adapter%d", sdebug_num_hosts);

	error = device_रेजिस्टर(&sdbg_host->dev);
	अगर (error)
		जाओ clean;

	++sdebug_num_hosts;
	वापस 0;

clean:
	list_क्रम_each_entry_safe(sdbg_devinfo, पंचांगp, &sdbg_host->dev_info_list,
				 dev_list) अणु
		list_del(&sdbg_devinfo->dev_list);
		kमुक्त(sdbg_devinfo->zstate);
		kमुक्त(sdbg_devinfo);
	पूर्ण
	kमुक्त(sdbg_host);
	pr_warn("%s: failed, errno=%d\n", __func__, -error);
	वापस error;
पूर्ण

अटल पूर्णांक sdebug_करो_add_host(bool mk_new_store)
अणु
	पूर्णांक ph_idx = sdeb_most_recent_idx;

	अगर (mk_new_store) अणु
		ph_idx = sdebug_add_store();
		अगर (ph_idx < 0)
			वापस ph_idx;
	पूर्ण
	वापस sdebug_add_host_helper(ph_idx);
पूर्ण

अटल व्योम sdebug_करो_हटाओ_host(bool the_end)
अणु
	पूर्णांक idx = -1;
	काष्ठा sdebug_host_info *sdbg_host = शून्य;
	काष्ठा sdebug_host_info *sdbg_host2;

	spin_lock(&sdebug_host_list_lock);
	अगर (!list_empty(&sdebug_host_list)) अणु
		sdbg_host = list_entry(sdebug_host_list.prev,
				       काष्ठा sdebug_host_info, host_list);
		idx = sdbg_host->si_idx;
	पूर्ण
	अगर (!the_end && idx >= 0) अणु
		bool unique = true;

		list_क्रम_each_entry(sdbg_host2, &sdebug_host_list, host_list) अणु
			अगर (sdbg_host2 == sdbg_host)
				जारी;
			अगर (idx == sdbg_host2->si_idx) अणु
				unique = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (unique) अणु
			xa_set_mark(per_store_ap, idx, SDEB_XA_NOT_IN_USE);
			अगर (idx == sdeb_most_recent_idx)
				--sdeb_most_recent_idx;
		पूर्ण
	पूर्ण
	अगर (sdbg_host)
		list_del(&sdbg_host->host_list);
	spin_unlock(&sdebug_host_list_lock);

	अगर (!sdbg_host)
		वापस;

	device_unरेजिस्टर(&sdbg_host->dev);
	--sdebug_num_hosts;
पूर्ण

अटल पूर्णांक sdebug_change_qdepth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	पूर्णांक num_in_q = 0;
	काष्ठा sdebug_dev_info *devip;

	block_unblock_all_queues(true);
	devip = (काष्ठा sdebug_dev_info *)sdev->hostdata;
	अगर (शून्य == devip) अणु
		block_unblock_all_queues(false);
		वापस	-ENODEV;
	पूर्ण
	num_in_q = atomic_पढ़ो(&devip->num_in_q);

	अगर (qdepth > SDEBUG_CANQUEUE) अणु
		qdepth = SDEBUG_CANQUEUE;
		pr_warn("%s: requested qdepth [%d] exceeds canqueue [%d], trim\n", __func__,
			qdepth, SDEBUG_CANQUEUE);
	पूर्ण
	अगर (qdepth < 1)
		qdepth = 1;
	अगर (qdepth != sdev->queue_depth)
		scsi_change_queue_depth(sdev, qdepth);

	अगर (SDEBUG_OPT_Q_NOISE & sdebug_opts) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: qdepth=%d, num_in_q=%d\n",
			    __func__, qdepth, num_in_q);
	पूर्ण
	block_unblock_all_queues(false);
	वापस sdev->queue_depth;
पूर्ण

अटल bool fake_समयout(काष्ठा scsi_cmnd *scp)
अणु
	अगर (0 == (atomic_पढ़ो(&sdebug_cmnd_count) % असल(sdebug_every_nth))) अणु
		अगर (sdebug_every_nth < -1)
			sdebug_every_nth = -1;
		अगर (SDEBUG_OPT_TIMEOUT & sdebug_opts)
			वापस true; /* ignore command causing समयout */
		अन्यथा अगर (SDEBUG_OPT_MAC_TIMEOUT & sdebug_opts &&
			 scsi_medium_access_command(scp))
			वापस true; /* समय out पढ़ोs and ग_लिखोs */
	पूर्ण
	वापस false;
पूर्ण

/* Response to TUR or media access command when device stopped */
अटल पूर्णांक resp_not_पढ़ोy(काष्ठा scsi_cmnd *scp, काष्ठा sdebug_dev_info *devip)
अणु
	पूर्णांक stopped_state;
	u64 dअगरf_ns = 0;
	kसमय_प्रकार now_ts = kसमय_get_bootसमय();
	काष्ठा scsi_device *sdp = scp->device;

	stopped_state = atomic_पढ़ो(&devip->stopped);
	अगर (stopped_state == 2) अणु
		अगर (kसमय_प्रकारo_ns(now_ts) > kसमय_प्रकारo_ns(devip->create_ts)) अणु
			dअगरf_ns = kसमय_प्रकारo_ns(kसमय_sub(now_ts, devip->create_ts));
			अगर (dअगरf_ns >= ((u64)sdeb_tur_ms_to_पढ़ोy * 1000000)) अणु
				/* tur_ms_to_पढ़ोy समयr extinguished */
				atomic_set(&devip->stopped, 0);
				वापस 0;
			पूर्ण
		पूर्ण
		mk_sense_buffer(scp, NOT_READY, LOGICAL_UNIT_NOT_READY, 0x1);
		अगर (sdebug_verbose)
			sdev_prपूर्णांकk(KERN_INFO, sdp,
				    "%s: Not ready: in process of becoming ready\n", my_name);
		अगर (scp->cmnd[0] == TEST_UNIT_READY) अणु
			u64 tur_nanosecs_to_पढ़ोy = (u64)sdeb_tur_ms_to_पढ़ोy * 1000000;

			अगर (dअगरf_ns <= tur_nanosecs_to_पढ़ोy)
				dअगरf_ns = tur_nanosecs_to_पढ़ोy - dअगरf_ns;
			अन्यथा
				dअगरf_ns = tur_nanosecs_to_पढ़ोy;
			/* As per 20-061r2 approved क्रम spc6 by T10 on 20200716 */
			करो_भाग(dअगरf_ns, 1000000);	/* dअगरf_ns becomes milliseconds */
			scsi_set_sense_inक्रमmation(scp->sense_buffer, SCSI_SENSE_BUFFERSIZE,
						   dअगरf_ns);
			वापस check_condition_result;
		पूर्ण
	पूर्ण
	mk_sense_buffer(scp, NOT_READY, LOGICAL_UNIT_NOT_READY, 0x2);
	अगर (sdebug_verbose)
		sdev_prपूर्णांकk(KERN_INFO, sdp, "%s: Not ready: initializing command required\n",
			    my_name);
	वापस check_condition_result;
पूर्ण

अटल पूर्णांक sdebug_map_queues(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक i, qoff;

	अगर (shost->nr_hw_queues == 1)
		वापस 0;

	क्रम (i = 0, qoff = 0; i < HCTX_MAX_TYPES; i++) अणु
		काष्ठा blk_mq_queue_map *map = &shost->tag_set.map[i];

		map->nr_queues  = 0;

		अगर (i == HCTX_TYPE_DEFAULT)
			map->nr_queues = submit_queues - poll_queues;
		अन्यथा अगर (i == HCTX_TYPE_POLL)
			map->nr_queues = poll_queues;

		अगर (!map->nr_queues) अणु
			BUG_ON(i == HCTX_TYPE_DEFAULT);
			जारी;
		पूर्ण

		map->queue_offset = qoff;
		blk_mq_map_queues(map);

		qoff += map->nr_queues;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक sdebug_blk_mq_poll(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक queue_num)
अणु
	bool first;
	bool retiring = false;
	पूर्णांक num_entries = 0;
	अचिन्हित पूर्णांक qc_idx = 0;
	अचिन्हित दीर्घ अगरlags;
	kसमय_प्रकार kt_from_boot = kसमय_get_bootसमय();
	काष्ठा sdebug_queue *sqp;
	काष्ठा sdebug_queued_cmd *sqcp;
	काष्ठा scsi_cmnd *scp;
	काष्ठा sdebug_dev_info *devip;
	काष्ठा sdebug_defer *sd_dp;

	sqp = sdebug_q_arr + queue_num;
	spin_lock_irqsave(&sqp->qc_lock, अगरlags);

	क्रम (first = true; first || qc_idx + 1 < sdebug_max_queue; )   अणु
		अगर (first) अणु
			qc_idx = find_first_bit(sqp->in_use_bm, sdebug_max_queue);
			first = false;
		पूर्ण अन्यथा अणु
			qc_idx = find_next_bit(sqp->in_use_bm, sdebug_max_queue, qc_idx + 1);
		पूर्ण
		अगर (unlikely(qc_idx >= sdebug_max_queue))
			अवरोध;

		sqcp = &sqp->qc_arr[qc_idx];
		sd_dp = sqcp->sd_dp;
		अगर (unlikely(!sd_dp))
			जारी;
		scp = sqcp->a_cmnd;
		अगर (unlikely(scp == शून्य)) अणु
			pr_err("scp is NULL, queue_num=%d, qc_idx=%u from %s\n",
			       queue_num, qc_idx, __func__);
			अवरोध;
		पूर्ण
		अगर (sd_dp->defer_t == SDEB_DEFER_POLL) अणु
			अगर (kt_from_boot < sd_dp->cmpl_ts)
				जारी;

		पूर्ण अन्यथा		/* ignoring non REQ_HIPRI requests */
			जारी;
		devip = (काष्ठा sdebug_dev_info *)scp->device->hostdata;
		अगर (likely(devip))
			atomic_dec(&devip->num_in_q);
		अन्यथा
			pr_err("devip=NULL from %s\n", __func__);
		अगर (unlikely(atomic_पढ़ो(&retired_max_queue) > 0))
			retiring = true;

		sqcp->a_cmnd = शून्य;
		अगर (unlikely(!test_and_clear_bit(qc_idx, sqp->in_use_bm))) अणु
			pr_err("Unexpected completion sqp %p queue_num=%d qc_idx=%u from %s\n",
				sqp, queue_num, qc_idx, __func__);
			अवरोध;
		पूर्ण
		अगर (unlikely(retiring)) अणु	/* user has reduced max_queue */
			पूर्णांक k, retval;

			retval = atomic_पढ़ो(&retired_max_queue);
			अगर (qc_idx >= retval) अणु
				pr_err("index %d too large\n", retval);
				अवरोध;
			पूर्ण
			k = find_last_bit(sqp->in_use_bm, retval);
			अगर ((k < sdebug_max_queue) || (k == retval))
				atomic_set(&retired_max_queue, 0);
			अन्यथा
				atomic_set(&retired_max_queue, k + 1);
		पूर्ण
		sd_dp->defer_t = SDEB_DEFER_NONE;
		spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
		scp->scsi_करोne(scp); /* callback to mid level */
		spin_lock_irqsave(&sqp->qc_lock, अगरlags);
		num_entries++;
	पूर्ण
	spin_unlock_irqrestore(&sqp->qc_lock, अगरlags);
	अगर (num_entries > 0)
		atomic_add(num_entries, &sdeb_mq_poll_count);
	वापस num_entries;
पूर्ण

अटल पूर्णांक scsi_debug_queuecommand(काष्ठा Scsi_Host *shost,
				   काष्ठा scsi_cmnd *scp)
अणु
	u8 sdeb_i;
	काष्ठा scsi_device *sdp = scp->device;
	स्थिर काष्ठा opcode_info_t *oip;
	स्थिर काष्ठा opcode_info_t *r_oip;
	काष्ठा sdebug_dev_info *devip;
	u8 *cmd = scp->cmnd;
	पूर्णांक (*r_pfp)(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *);
	पूर्णांक (*pfp)(काष्ठा scsi_cmnd *, काष्ठा sdebug_dev_info *) = शून्य;
	पूर्णांक k, na;
	पूर्णांक errsts = 0;
	u64 lun_index = sdp->lun & 0x3FFF;
	u32 flags;
	u16 sa;
	u8 opcode = cmd[0];
	bool has_wlun_rl;
	bool inject_now;

	scsi_set_resid(scp, 0);
	अगर (sdebug_statistics) अणु
		atomic_inc(&sdebug_cmnd_count);
		inject_now = inject_on_this_cmd();
	पूर्ण अन्यथा अणु
		inject_now = false;
	पूर्ण
	अगर (unlikely(sdebug_verbose &&
		     !(SDEBUG_OPT_NO_CDB_NOISE & sdebug_opts))) अणु
		अक्षर b[120];
		पूर्णांक n, len, sb;

		len = scp->cmd_len;
		sb = (पूर्णांक)माप(b);
		अगर (len > 32)
			म_नकल(b, "too long, over 32 bytes");
		अन्यथा अणु
			क्रम (k = 0, n = 0; k < len && n < sb; ++k)
				n += scnम_लिखो(b + n, sb - n, "%02x ",
					       (u32)cmd[k]);
		पूर्ण
		sdev_prपूर्णांकk(KERN_INFO, sdp, "%s: tag=%#x, cmd %s\n", my_name,
			    blk_mq_unique_tag(scp->request), b);
	पूर्ण
	अगर (unlikely(inject_now && (sdebug_opts & SDEBUG_OPT_HOST_BUSY)))
		वापस SCSI_MLQUEUE_HOST_BUSY;
	has_wlun_rl = (sdp->lun == SCSI_W_LUN_REPORT_LUNS);
	अगर (unlikely(lun_index >= sdebug_max_luns && !has_wlun_rl))
		जाओ err_out;

	sdeb_i = opcode_ind_arr[opcode];	/* fully mapped */
	oip = &opcode_info_arr[sdeb_i];		/* safe अगर table consistent */
	devip = (काष्ठा sdebug_dev_info *)sdp->hostdata;
	अगर (unlikely(!devip)) अणु
		devip = find_build_dev_info(sdp);
		अगर (शून्य == devip)
			जाओ err_out;
	पूर्ण
	अगर (unlikely(inject_now && !atomic_पढ़ो(&sdeb_inject_pending)))
		atomic_set(&sdeb_inject_pending, 1);

	na = oip->num_attached;
	r_pfp = oip->pfp;
	अगर (na) अणु	/* multiple commands with this opcode */
		r_oip = oip;
		अगर (FF_SA & r_oip->flags) अणु
			अगर (F_SA_LOW & oip->flags)
				sa = 0x1f & cmd[1];
			अन्यथा
				sa = get_unaligned_be16(cmd + 8);
			क्रम (k = 0; k <= na; oip = r_oip->arrp + k++) अणु
				अगर (opcode == oip->opcode && sa == oip->sa)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु   /* since no service action only check opcode */
			क्रम (k = 0; k <= na; oip = r_oip->arrp + k++) अणु
				अगर (opcode == oip->opcode)
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (k > na) अणु
			अगर (F_SA_LOW & r_oip->flags)
				mk_sense_invalid_fld(scp, SDEB_IN_CDB, 1, 4);
			अन्यथा अगर (F_SA_HIGH & r_oip->flags)
				mk_sense_invalid_fld(scp, SDEB_IN_CDB, 8, 7);
			अन्यथा
				mk_sense_invalid_opcode(scp);
			जाओ check_cond;
		पूर्ण
	पूर्ण	/* अन्यथा (when na==0) we assume the oip is a match */
	flags = oip->flags;
	अगर (unlikely(F_INV_OP & flags)) अणु
		mk_sense_invalid_opcode(scp);
		जाओ check_cond;
	पूर्ण
	अगर (unlikely(has_wlun_rl && !(F_RL_WLUN_OK & flags))) अणु
		अगर (sdebug_verbose)
			sdev_prपूर्णांकk(KERN_INFO, sdp, "%s: Opcode 0x%x not%s\n",
				    my_name, opcode, " supported for wlun");
		mk_sense_invalid_opcode(scp);
		जाओ check_cond;
	पूर्ण
	अगर (unlikely(sdebug_strict)) अणु	/* check cdb against mask */
		u8 rem;
		पूर्णांक j;

		क्रम (k = 1; k < oip->len_mask[0] && k < 16; ++k) अणु
			rem = ~oip->len_mask[k] & cmd[k];
			अगर (rem) अणु
				क्रम (j = 7; j >= 0; --j, rem <<= 1) अणु
					अगर (0x80 & rem)
						अवरोध;
				पूर्ण
				mk_sense_invalid_fld(scp, SDEB_IN_CDB, k, j);
				जाओ check_cond;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (unlikely(!(F_SKIP_UA & flags) &&
		     find_first_bit(devip->uas_bm,
				    SDEBUG_NUM_UAS) != SDEBUG_NUM_UAS)) अणु
		errsts = make_ua(scp, devip);
		अगर (errsts)
			जाओ check_cond;
	पूर्ण
	अगर (unlikely(((F_M_ACCESS & flags) || scp->cmnd[0] == TEST_UNIT_READY) &&
		     atomic_पढ़ो(&devip->stopped))) अणु
		errsts = resp_not_पढ़ोy(scp, devip);
		अगर (errsts)
			जाओ fini;
	पूर्ण
	अगर (sdebug_fake_rw && (F_FAKE_RW & flags))
		जाओ fini;
	अगर (unlikely(sdebug_every_nth)) अणु
		अगर (fake_समयout(scp))
			वापस 0;	/* ignore command: make trouble */
	पूर्ण
	अगर (likely(oip->pfp))
		pfp = oip->pfp;	/* calls a resp_* function */
	अन्यथा
		pfp = r_pfp;    /* अगर leaf function ptr शून्य, try the root's */

fini:
	अगर (F_DELAY_OVERR & flags)	/* cmds like INQUIRY respond asap */
		वापस schedule_resp(scp, devip, errsts, pfp, 0, 0);
	अन्यथा अगर ((flags & F_LONG_DELAY) && (sdebug_jdelay > 0 ||
					    sdebug_ndelay > 10000)) अणु
		/*
		 * Skip दीर्घ delays अगर ndelay <= 10 microseconds. Otherwise
		 * क्रम Start Stop Unit (SSU) want at least 1 second delay and
		 * अगर sdebug_jdelay>1 want a दीर्घ delay of that many seconds.
		 * For Synchronize Cache want 1/20 of SSU's delay.
		 */
		पूर्णांक jdelay = (sdebug_jdelay < 2) ? 1 : sdebug_jdelay;
		पूर्णांक denom = (flags & F_SYNC_DELAY) ? 20 : 1;

		jdelay = mult_frac(USER_HZ * jdelay, HZ, denom * USER_HZ);
		वापस schedule_resp(scp, devip, errsts, pfp, jdelay, 0);
	पूर्ण अन्यथा
		वापस schedule_resp(scp, devip, errsts, pfp, sdebug_jdelay,
				     sdebug_ndelay);
check_cond:
	वापस schedule_resp(scp, devip, check_condition_result, शून्य, 0, 0);
err_out:
	वापस schedule_resp(scp, शून्य, DID_NO_CONNECT << 16, शून्य, 0, 0);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sdebug_driver_ढाँचा = अणु
	.show_info =		scsi_debug_show_info,
	.ग_लिखो_info =		scsi_debug_ग_लिखो_info,
	.proc_name =		sdebug_proc_name,
	.name =			"SCSI DEBUG",
	.info =			scsi_debug_info,
	.slave_alloc =		scsi_debug_slave_alloc,
	.slave_configure =	scsi_debug_slave_configure,
	.slave_destroy =	scsi_debug_slave_destroy,
	.ioctl =		scsi_debug_ioctl,
	.queuecommand =		scsi_debug_queuecommand,
	.change_queue_depth =	sdebug_change_qdepth,
	.map_queues =		sdebug_map_queues,
	.mq_poll =		sdebug_blk_mq_poll,
	.eh_पात_handler =	scsi_debug_पात,
	.eh_device_reset_handler = scsi_debug_device_reset,
	.eh_target_reset_handler = scsi_debug_target_reset,
	.eh_bus_reset_handler = scsi_debug_bus_reset,
	.eh_host_reset_handler = scsi_debug_host_reset,
	.can_queue =		SDEBUG_CANQUEUE,
	.this_id =		7,
	.sg_tablesize =		SG_MAX_SEGMENTS,
	.cmd_per_lun =		DEF_CMD_PER_LUN,
	.max_sectors =		-1U,
	.max_segment_size =	-1U,
	.module =		THIS_MODULE,
	.track_queue_depth =	1,
पूर्ण;

अटल पूर्णांक sdebug_driver_probe(काष्ठा device *dev)
अणु
	पूर्णांक error = 0;
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा Scsi_Host *hpnt;
	पूर्णांक hprot;

	sdbg_host = to_sdebug_host(dev);

	sdebug_driver_ढाँचा.can_queue = sdebug_max_queue;
	sdebug_driver_ढाँचा.cmd_per_lun = sdebug_max_queue;
	अगर (!sdebug_clustering)
		sdebug_driver_ढाँचा.dma_boundary = PAGE_SIZE - 1;

	hpnt = scsi_host_alloc(&sdebug_driver_ढाँचा, माप(sdbg_host));
	अगर (शून्य == hpnt) अणु
		pr_err("scsi_host_alloc failed\n");
		error = -ENODEV;
		वापस error;
	पूर्ण
	अगर (submit_queues > nr_cpu_ids) अणु
		pr_warn("%s: trim submit_queues (was %d) to nr_cpu_ids=%u\n",
			my_name, submit_queues, nr_cpu_ids);
		submit_queues = nr_cpu_ids;
	पूर्ण
	/*
	 * Decide whether to tell scsi subप्रणाली that we want mq. The
	 * following should give the same answer क्रम each host.
	 */
	hpnt->nr_hw_queues = submit_queues;
	अगर (sdebug_host_max_queue)
		hpnt->host_tagset = 1;

	/* poll queues are possible क्रम nr_hw_queues > 1 */
	अगर (hpnt->nr_hw_queues == 1 || (poll_queues < 1)) अणु
		pr_warn("%s: trim poll_queues to 0. poll_q/nr_hw = (%d/%d)\n",
			 my_name, poll_queues, hpnt->nr_hw_queues);
		poll_queues = 0;
	पूर्ण

	/*
	 * Poll queues करोn't need पूर्णांकerrupts, but we need at least one I/O queue
	 * left over क्रम non-polled I/O.
	 * If condition not met, trim poll_queues to 1 (just क्रम simplicity).
	 */
	अगर (poll_queues >= submit_queues) अणु
		अगर (submit_queues < 3)
			pr_warn("%s: trim poll_queues to 1\n", my_name);
		अन्यथा
			pr_warn("%s: trim poll_queues to 1. Perhaps try poll_queues=%d\n",
				my_name, submit_queues - 1);
		poll_queues = 1;
	पूर्ण
	अगर (poll_queues)
		hpnt->nr_maps = 3;

	sdbg_host->shost = hpnt;
	*((काष्ठा sdebug_host_info **)hpnt->hostdata) = sdbg_host;
	अगर ((hpnt->this_id >= 0) && (sdebug_num_tgts > hpnt->this_id))
		hpnt->max_id = sdebug_num_tgts + 1;
	अन्यथा
		hpnt->max_id = sdebug_num_tgts;
	/* = sdebug_max_luns; */
	hpnt->max_lun = SCSI_W_LUN_REPORT_LUNS + 1;

	hprot = 0;

	चयन (sdebug_dअगर) अणु

	हाल T10_PI_TYPE1_PROTECTION:
		hprot = SHOST_DIF_TYPE1_PROTECTION;
		अगर (sdebug_dix)
			hprot |= SHOST_DIX_TYPE1_PROTECTION;
		अवरोध;

	हाल T10_PI_TYPE2_PROTECTION:
		hprot = SHOST_DIF_TYPE2_PROTECTION;
		अगर (sdebug_dix)
			hprot |= SHOST_DIX_TYPE2_PROTECTION;
		अवरोध;

	हाल T10_PI_TYPE3_PROTECTION:
		hprot = SHOST_DIF_TYPE3_PROTECTION;
		अगर (sdebug_dix)
			hprot |= SHOST_DIX_TYPE3_PROTECTION;
		अवरोध;

	शेष:
		अगर (sdebug_dix)
			hprot |= SHOST_DIX_TYPE0_PROTECTION;
		अवरोध;
	पूर्ण

	scsi_host_set_prot(hpnt, hprot);

	अगर (have_dअगर_prot || sdebug_dix)
		pr_info("host protection%s%s%s%s%s%s%s\n",
			(hprot & SHOST_DIF_TYPE1_PROTECTION) ? " DIF1" : "",
			(hprot & SHOST_DIF_TYPE2_PROTECTION) ? " DIF2" : "",
			(hprot & SHOST_DIF_TYPE3_PROTECTION) ? " DIF3" : "",
			(hprot & SHOST_DIX_TYPE0_PROTECTION) ? " DIX0" : "",
			(hprot & SHOST_DIX_TYPE1_PROTECTION) ? " DIX1" : "",
			(hprot & SHOST_DIX_TYPE2_PROTECTION) ? " DIX2" : "",
			(hprot & SHOST_DIX_TYPE3_PROTECTION) ? " DIX3" : "");

	अगर (sdebug_guard == 1)
		scsi_host_set_guard(hpnt, SHOST_DIX_GUARD_IP);
	अन्यथा
		scsi_host_set_guard(hpnt, SHOST_DIX_GUARD_CRC);

	sdebug_verbose = !!(SDEBUG_OPT_NOISE & sdebug_opts);
	sdebug_any_injecting_opt = !!(SDEBUG_OPT_ALL_INJECTING & sdebug_opts);
	अगर (sdebug_every_nth)	/* need stats counters क्रम every_nth */
		sdebug_statistics = true;
	error = scsi_add_host(hpnt, &sdbg_host->dev);
	अगर (error) अणु
		pr_err("scsi_add_host failed\n");
		error = -ENODEV;
		scsi_host_put(hpnt);
	पूर्ण अन्यथा अणु
		scsi_scan_host(hpnt);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक sdebug_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा sdebug_host_info *sdbg_host;
	काष्ठा sdebug_dev_info *sdbg_devinfo, *पंचांगp;

	sdbg_host = to_sdebug_host(dev);

	अगर (!sdbg_host) अणु
		pr_err("Unable to locate host info\n");
		वापस -ENODEV;
	पूर्ण

	scsi_हटाओ_host(sdbg_host->shost);

	list_क्रम_each_entry_safe(sdbg_devinfo, पंचांगp, &sdbg_host->dev_info_list,
				 dev_list) अणु
		list_del(&sdbg_devinfo->dev_list);
		kमुक्त(sdbg_devinfo->zstate);
		kमुक्त(sdbg_devinfo);
	पूर्ण

	scsi_host_put(sdbg_host->shost);
	वापस 0;
पूर्ण

अटल पूर्णांक pseuकरो_lld_bus_match(काष्ठा device *dev,
				काष्ठा device_driver *dev_driver)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा bus_type pseuकरो_lld_bus = अणु
	.name = "pseudo",
	.match = pseuकरो_lld_bus_match,
	.probe = sdebug_driver_probe,
	.हटाओ = sdebug_driver_हटाओ,
	.drv_groups = sdebug_drv_groups,
पूर्ण;
