<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_LOG_FORMAT_H__
#घोषणा __XFS_LOG_FORMAT_H__

काष्ठा xfs_mount;
काष्ठा xfs_trans_res;

/*
 * On-disk Log Format definitions.
 *
 * This file contains all the on-disk क्रमmat definitions used within the log. It
 * includes the physical log काष्ठाure itself, as well as all the log item
 * क्रमmat काष्ठाures that are written पूर्णांकo the log and पूर्णांकepreted by log
 * recovery. We start with the physical log क्रमmat definitions, and then work
 * through all the log items definitions and everything they encode पूर्णांकo the
 * log.
 */
प्रकार uपूर्णांक32_t xlog_tid_t;

#घोषणा XLOG_MIN_ICLOGS		2
#घोषणा XLOG_MAX_ICLOGS		8
#घोषणा XLOG_HEADER_MAGIC_NUM	0xFEEDbabe	/* Invalid cycle number */
#घोषणा XLOG_VERSION_1		1
#घोषणा XLOG_VERSION_2		2		/* Large IClogs, Log sunit */
#घोषणा XLOG_VERSION_OKBITS	(XLOG_VERSION_1 | XLOG_VERSION_2)
#घोषणा XLOG_MIN_RECORD_BSIZE	(16*1024)	/* eventually 32k */
#घोषणा XLOG_BIG_RECORD_BSIZE	(32*1024)	/* 32k buffers */
#घोषणा XLOG_MAX_RECORD_BSIZE	(256*1024)
#घोषणा XLOG_HEADER_CYCLE_SIZE	(32*1024)	/* cycle data in header */
#घोषणा XLOG_MIN_RECORD_BSHIFT	14		/* 16384 == 1 << 14 */
#घोषणा XLOG_BIG_RECORD_BSHIFT	15		/* 32k == 1 << 15 */
#घोषणा XLOG_MAX_RECORD_BSHIFT	18		/* 256k == 1 << 18 */
#घोषणा XLOG_BTOLSUNIT(log, b)  (((b)+(log)->l_mp->m_sb.sb_logsunit-1) / \
                                 (log)->l_mp->m_sb.sb_logsunit)
#घोषणा XLOG_LSUNITTOB(log, su) ((su) * (log)->l_mp->m_sb.sb_logsunit)

#घोषणा XLOG_HEADER_SIZE	512

/* Minimum number of transactions that must fit in the log (defined by mkfs) */
#घोषणा XFS_MIN_LOG_FACTOR	3

#घोषणा XLOG_REC_SHIFT(log) \
	BTOBB(1 << (xfs_sb_version_haslogv2(&log->l_mp->m_sb) ? \
	 XLOG_MAX_RECORD_BSHIFT : XLOG_BIG_RECORD_BSHIFT))
#घोषणा XLOG_TOTAL_REC_SHIFT(log) \
	BTOBB(XLOG_MAX_ICLOGS << (xfs_sb_version_haslogv2(&log->l_mp->m_sb) ? \
	 XLOG_MAX_RECORD_BSHIFT : XLOG_BIG_RECORD_BSHIFT))

/* get lsn fields */
#घोषणा CYCLE_LSN(lsn) ((uपूर्णांक)((lsn)>>32))
#घोषणा BLOCK_LSN(lsn) ((uपूर्णांक)(lsn))

/* this is used in a spot where we might otherwise द्विगुन-endian-flip */
#घोषणा CYCLE_LSN_DISK(lsn) (((__be32 *)&(lsn))[0])

अटल अंतरभूत xfs_lsn_t xlog_assign_lsn(uपूर्णांक cycle, uपूर्णांक block)
अणु
	वापस ((xfs_lsn_t)cycle << 32) | block;
पूर्ण

अटल अंतरभूत uपूर्णांक xlog_get_cycle(अक्षर *ptr)
अणु
	अगर (be32_to_cpu(*(__be32 *)ptr) == XLOG_HEADER_MAGIC_NUM)
		वापस be32_to_cpu(*((__be32 *)ptr + 1));
	अन्यथा
		वापस be32_to_cpu(*(__be32 *)ptr);
पूर्ण

/* Log Clients */
#घोषणा XFS_TRANSACTION		0x69
#घोषणा XFS_VOLUME		0x2
#घोषणा XFS_LOG			0xaa

#घोषणा XLOG_UNMOUNT_TYPE	0x556e	/* Un क्रम Unmount */

/*
 * Log item क्रम unmount records.
 *
 * The unmount record used to have a string "Unmount filesystem--" in the
 * data section where the "Un" was really a magic number (XLOG_UNMOUNT_TYPE).
 * We just ग_लिखो the magic number now; see xfs_log_unmount_ग_लिखो.
 */
काष्ठा xfs_unmount_log_क्रमmat अणु
	uपूर्णांक16_t	magic;	/* XLOG_UNMOUNT_TYPE */
	uपूर्णांक16_t	pad1;
	uपूर्णांक32_t	pad2;	/* may as well make it 64 bits */
पूर्ण;

/* Region types क्रम iovec's i_type */
#घोषणा XLOG_REG_TYPE_BFORMAT		1
#घोषणा XLOG_REG_TYPE_BCHUNK		2
#घोषणा XLOG_REG_TYPE_EFI_FORMAT	3
#घोषणा XLOG_REG_TYPE_EFD_FORMAT	4
#घोषणा XLOG_REG_TYPE_IFORMAT		5
#घोषणा XLOG_REG_TYPE_ICORE		6
#घोषणा XLOG_REG_TYPE_IEXT		7
#घोषणा XLOG_REG_TYPE_IBROOT		8
#घोषणा XLOG_REG_TYPE_ILOCAL		9
#घोषणा XLOG_REG_TYPE_IATTR_EXT		10
#घोषणा XLOG_REG_TYPE_IATTR_BROOT	11
#घोषणा XLOG_REG_TYPE_IATTR_LOCAL	12
#घोषणा XLOG_REG_TYPE_QFORMAT		13
#घोषणा XLOG_REG_TYPE_DQUOT		14
#घोषणा XLOG_REG_TYPE_QUOTAOFF		15
#घोषणा XLOG_REG_TYPE_LRHEADER		16
#घोषणा XLOG_REG_TYPE_UNMOUNT		17
#घोषणा XLOG_REG_TYPE_COMMIT		18
#घोषणा XLOG_REG_TYPE_TRANSHDR		19
#घोषणा XLOG_REG_TYPE_ICREATE		20
#घोषणा XLOG_REG_TYPE_RUI_FORMAT	21
#घोषणा XLOG_REG_TYPE_RUD_FORMAT	22
#घोषणा XLOG_REG_TYPE_CUI_FORMAT	23
#घोषणा XLOG_REG_TYPE_CUD_FORMAT	24
#घोषणा XLOG_REG_TYPE_BUI_FORMAT	25
#घोषणा XLOG_REG_TYPE_BUD_FORMAT	26
#घोषणा XLOG_REG_TYPE_MAX		26

/*
 * Flags to log operation header
 *
 * The first ग_लिखो of a new transaction will be preceded with a start
 * record, XLOG_START_TRANS.  Once a transaction is committed, a commit
 * record is written, XLOG_COMMIT_TRANS.  If a single region can not fit पूर्णांकo
 * the reमुख्यder of the current active in-core log, it is split up पूर्णांकo
 * multiple regions.  Each partial region will be marked with a
 * XLOG_CONTINUE_TRANS until the last one, which माला_लो marked with XLOG_END_TRANS.
 *
 */
#घोषणा XLOG_START_TRANS	0x01	/* Start a new transaction */
#घोषणा XLOG_COMMIT_TRANS	0x02	/* Commit this transaction */
#घोषणा XLOG_CONTINUE_TRANS	0x04	/* Cont this trans पूर्णांकo new region */
#घोषणा XLOG_WAS_CONT_TRANS	0x08	/* Cont this trans पूर्णांकo new region */
#घोषणा XLOG_END_TRANS		0x10	/* End a जारीd transaction */
#घोषणा XLOG_UNMOUNT_TRANS	0x20	/* Unmount a fileप्रणाली transaction */


प्रकार काष्ठा xlog_op_header अणु
	__be32	   oh_tid;	/* transaction id of operation	:  4 b */
	__be32	   oh_len;	/* bytes in data region		:  4 b */
	__u8	   oh_clientid;	/* who sent me this		:  1 b */
	__u8	   oh_flags;	/*				:  1 b */
	__u16	   oh_res2;	/* 32 bit align			:  2 b */
पूर्ण xlog_op_header_t;

/* valid values क्रम h_fmt */
#घोषणा XLOG_FMT_UNKNOWN  0
#घोषणा XLOG_FMT_LINUX_LE 1
#घोषणा XLOG_FMT_LINUX_BE 2
#घोषणा XLOG_FMT_IRIX_BE  3

/* our fmt */
#अगर_घोषित XFS_NATIVE_HOST
#घोषणा XLOG_FMT XLOG_FMT_LINUX_BE
#अन्यथा
#घोषणा XLOG_FMT XLOG_FMT_LINUX_LE
#पूर्ण_अगर

प्रकार काष्ठा xlog_rec_header अणु
	__be32	  h_magicno;	/* log record (LR) identअगरier		:  4 */
	__be32	  h_cycle;	/* ग_लिखो cycle of log			:  4 */
	__be32	  h_version;	/* LR version				:  4 */
	__be32	  h_len;	/* len in bytes; should be 64-bit aligned: 4 */
	__be64	  h_lsn;	/* lsn of this LR			:  8 */
	__be64	  h_tail_lsn;	/* lsn of 1st LR w/ buffers not committed: 8 */
	__le32	  h_crc;	/* crc of log record                    :  4 */
	__be32	  h_prev_block; /* block number to previous LR		:  4 */
	__be32	  h_num_logops;	/* number of log operations in this LR	:  4 */
	__be32	  h_cycle_data[XLOG_HEADER_CYCLE_SIZE / BBSIZE];
	/* new fields */
	__be32    h_fmt;        /* क्रमmat of log record                 :  4 */
	uuid_t	  h_fs_uuid;    /* uuid of FS                           : 16 */
	__be32	  h_size;	/* iclog size				:  4 */
पूर्ण xlog_rec_header_t;

प्रकार काष्ठा xlog_rec_ext_header अणु
	__be32	  xh_cycle;	/* ग_लिखो cycle of log			: 4 */
	__be32	  xh_cycle_data[XLOG_HEADER_CYCLE_SIZE / BBSIZE]; /*	: 256 */
पूर्ण xlog_rec_ext_header_t;

/*
 * Quite misnamed, because this जोड़ lays out the actual on-disk log buffer.
 */
प्रकार जोड़ xlog_in_core2 अणु
	xlog_rec_header_t	hic_header;
	xlog_rec_ext_header_t	hic_xheader;
	अक्षर			hic_sector[XLOG_HEADER_SIZE];
पूर्ण xlog_in_core_2_t;

/* not an on-disk काष्ठाure, but needed by log recovery in userspace */
प्रकार काष्ठा xfs_log_iovec अणु
	व्योम		*i_addr;	/* beginning address of region */
	पूर्णांक		i_len;		/* length in bytes of region */
	uपूर्णांक		i_type;		/* type of region */
पूर्ण xfs_log_iovec_t;


/*
 * Transaction Header definitions.
 *
 * This is the काष्ठाure written in the log at the head of every transaction. It
 * identअगरies the type and id of the transaction, and contains the number of
 * items logged by the transaction so we know how many to expect during
 * recovery.
 *
 * Do not change the below काष्ठाure without reकरोing the code in
 * xlog_recover_add_to_trans() and xlog_recover_add_to_cont_trans().
 */
प्रकार काष्ठा xfs_trans_header अणु
	uपूर्णांक		th_magic;		/* magic number */
	uपूर्णांक		th_type;		/* transaction type */
	पूर्णांक32_t		th_tid;			/* transaction id (unused) */
	uपूर्णांक		th_num_items;		/* num items logged by trans */
पूर्ण xfs_trans_header_t;

#घोषणा	XFS_TRANS_HEADER_MAGIC	0x5452414e	/* TRAN */

/*
 * The only type valid क्रम th_type in CIL-enabled file प्रणाली logs:
 */
#घोषणा XFS_TRANS_CHECKPOINT	40

/*
 * Log item types.
 */
#घोषणा	XFS_LI_EFI		0x1236
#घोषणा	XFS_LI_EFD		0x1237
#घोषणा	XFS_LI_IUNLINK		0x1238
#घोषणा	XFS_LI_INODE		0x123b	/* aligned ino chunks, var-size ibufs */
#घोषणा	XFS_LI_BUF		0x123c	/* v2 bufs, variable sized inode bufs */
#घोषणा	XFS_LI_DQUOT		0x123d
#घोषणा	XFS_LI_QUOTAOFF		0x123e
#घोषणा	XFS_LI_ICREATE		0x123f
#घोषणा	XFS_LI_RUI		0x1240	/* rmap update पूर्णांकent */
#घोषणा	XFS_LI_RUD		0x1241
#घोषणा	XFS_LI_CUI		0x1242	/* refcount update पूर्णांकent */
#घोषणा	XFS_LI_CUD		0x1243
#घोषणा	XFS_LI_BUI		0x1244	/* bmbt update पूर्णांकent */
#घोषणा	XFS_LI_BUD		0x1245

#घोषणा XFS_LI_TYPE_DESC \
	अणु XFS_LI_EFI,		"XFS_LI_EFI" पूर्ण, \
	अणु XFS_LI_EFD,		"XFS_LI_EFD" पूर्ण, \
	अणु XFS_LI_IUNLINK,	"XFS_LI_IUNLINK" पूर्ण, \
	अणु XFS_LI_INODE,		"XFS_LI_INODE" पूर्ण, \
	अणु XFS_LI_BUF,		"XFS_LI_BUF" पूर्ण, \
	अणु XFS_LI_DQUOT,		"XFS_LI_DQUOT" पूर्ण, \
	अणु XFS_LI_QUOTAOFF,	"XFS_LI_QUOTAOFF" पूर्ण, \
	अणु XFS_LI_ICREATE,	"XFS_LI_ICREATE" पूर्ण, \
	अणु XFS_LI_RUI,		"XFS_LI_RUI" पूर्ण, \
	अणु XFS_LI_RUD,		"XFS_LI_RUD" पूर्ण, \
	अणु XFS_LI_CUI,		"XFS_LI_CUI" पूर्ण, \
	अणु XFS_LI_CUD,		"XFS_LI_CUD" पूर्ण, \
	अणु XFS_LI_BUI,		"XFS_LI_BUI" पूर्ण, \
	अणु XFS_LI_BUD,		"XFS_LI_BUD" पूर्ण

/*
 * Inode Log Item Format definitions.
 *
 * This is the काष्ठाure used to lay out an inode log item in the
 * log.  The size of the अंतरभूत data/extents/b-tree root to be logged
 * (अगर any) is indicated in the ilf_dsize field.  Changes to this काष्ठाure
 * must be added on to the end.
 */
काष्ठा xfs_inode_log_क्रमmat अणु
	uपूर्णांक16_t		ilf_type;	/* inode log item type */
	uपूर्णांक16_t		ilf_size;	/* size of this item */
	uपूर्णांक32_t		ilf_fields;	/* flags क्रम fields logged */
	uपूर्णांक16_t		ilf_asize;	/* size of attr d/ext/root */
	uपूर्णांक16_t		ilf_dsize;	/* size of data/ext/root */
	uपूर्णांक32_t		ilf_pad;	/* pad क्रम 64 bit boundary */
	uपूर्णांक64_t		ilf_ino;	/* inode number */
	जोड़ अणु
		uपूर्णांक32_t	ilfu_rdev;	/* rdev value क्रम dev inode*/
		uपूर्णांक8_t		__pad[16];	/* unused */
	पूर्ण ilf_u;
	पूर्णांक64_t			ilf_blkno;	/* blkno of inode buffer */
	पूर्णांक32_t			ilf_len;	/* len of inode buffer */
	पूर्णांक32_t			ilf_boffset;	/* off of inode in buffer */
पूर्ण;

/*
 * Old 32 bit प्रणालीs will log in this क्रमmat without the 64 bit
 * alignment padding. Recovery will detect this and convert it to the
 * correct क्रमmat.
 */
काष्ठा xfs_inode_log_क्रमmat_32 अणु
	uपूर्णांक16_t		ilf_type;	/* inode log item type */
	uपूर्णांक16_t		ilf_size;	/* size of this item */
	uपूर्णांक32_t		ilf_fields;	/* flags क्रम fields logged */
	uपूर्णांक16_t		ilf_asize;	/* size of attr d/ext/root */
	uपूर्णांक16_t		ilf_dsize;	/* size of data/ext/root */
	uपूर्णांक64_t		ilf_ino;	/* inode number */
	जोड़ अणु
		uपूर्णांक32_t	ilfu_rdev;	/* rdev value क्रम dev inode*/
		uपूर्णांक8_t		__pad[16];	/* unused */
	पूर्ण ilf_u;
	पूर्णांक64_t			ilf_blkno;	/* blkno of inode buffer */
	पूर्णांक32_t			ilf_len;	/* len of inode buffer */
	पूर्णांक32_t			ilf_boffset;	/* off of inode in buffer */
पूर्ण __attribute__((packed));


/*
 * Flags क्रम xfs_trans_log_inode flags field.
 */
#घोषणा	XFS_ILOG_CORE	0x001	/* log standard inode fields */
#घोषणा	XFS_ILOG_DDATA	0x002	/* log i_df.अगर_data */
#घोषणा	XFS_ILOG_DEXT	0x004	/* log i_df.अगर_extents */
#घोषणा	XFS_ILOG_DBROOT	0x008	/* log i_df.i_broot */
#घोषणा	XFS_ILOG_DEV	0x010	/* log the dev field */
#घोषणा	XFS_ILOG_UUID	0x020	/* added दीर्घ ago, but never used */
#घोषणा	XFS_ILOG_ADATA	0x040	/* log i_af.अगर_data */
#घोषणा	XFS_ILOG_AEXT	0x080	/* log i_af.अगर_extents */
#घोषणा	XFS_ILOG_ABROOT	0x100	/* log i_af.i_broot */
#घोषणा XFS_ILOG_DOWNER	0x200	/* change the data विभाजन owner on replay */
#घोषणा XFS_ILOG_AOWNER	0x400	/* change the attr विभाजन owner on replay */


/*
 * The बारtamps are dirty, but not necessarily anything अन्यथा in the inode
 * core.  Unlike the other fields above this one must never make it to disk
 * in the ilf_fields of the inode_log_क्रमmat, but is purely store in-memory in
 * ili_fields in the inode_log_item.
 */
#घोषणा XFS_ILOG_TIMESTAMP	0x4000

#घोषणा	XFS_ILOG_NONCORE	(XFS_ILOG_DDATA | XFS_ILOG_DEXT | \
				 XFS_ILOG_DBROOT | XFS_ILOG_DEV | \
				 XFS_ILOG_ADATA | XFS_ILOG_AEXT | \
				 XFS_ILOG_ABROOT | XFS_ILOG_DOWNER | \
				 XFS_ILOG_AOWNER)

#घोषणा	XFS_ILOG_DFORK		(XFS_ILOG_DDATA | XFS_ILOG_DEXT | \
				 XFS_ILOG_DBROOT)

#घोषणा	XFS_ILOG_AFORK		(XFS_ILOG_ADATA | XFS_ILOG_AEXT | \
				 XFS_ILOG_ABROOT)

#घोषणा	XFS_ILOG_ALL		(XFS_ILOG_CORE | XFS_ILOG_DDATA | \
				 XFS_ILOG_DEXT | XFS_ILOG_DBROOT | \
				 XFS_ILOG_DEV | XFS_ILOG_ADATA | \
				 XFS_ILOG_AEXT | XFS_ILOG_ABROOT | \
				 XFS_ILOG_TIMESTAMP | XFS_ILOG_DOWNER | \
				 XFS_ILOG_AOWNER)

अटल अंतरभूत पूर्णांक xfs_ilog_fbroot(पूर्णांक w)
अणु
	वापस (w == XFS_DATA_FORK ? XFS_ILOG_DBROOT : XFS_ILOG_ABROOT);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_ilog_fext(पूर्णांक w)
अणु
	वापस (w == XFS_DATA_FORK ? XFS_ILOG_DEXT : XFS_ILOG_AEXT);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_ilog_fdata(पूर्णांक w)
अणु
	वापस (w == XFS_DATA_FORK ? XFS_ILOG_DDATA : XFS_ILOG_ADATA);
पूर्ण

/*
 * Incore version of the on-disk inode core काष्ठाures. We log this directly
 * पूर्णांकo the journal in host CPU क्रमmat (क्रम better or worse) and as such
 * directly mirrors the xfs_dinode काष्ठाure as it must contain all the same
 * inक्रमmation.
 */
प्रकार uपूर्णांक64_t xfs_log_बारtamp_t;

/* Legacy बारtamp encoding क्रमmat. */
काष्ठा xfs_log_legacy_बारtamp अणु
	पूर्णांक32_t		t_sec;		/* बारtamp seconds */
	पूर्णांक32_t		t_nsec;		/* बारtamp nanoseconds */
पूर्ण;

/*
 * Define the क्रमmat of the inode core that is logged. This काष्ठाure must be
 * kept identical to काष्ठा xfs_dinode except क्रम the endianness annotations.
 */
काष्ठा xfs_log_dinode अणु
	uपूर्णांक16_t	di_magic;	/* inode magic # = XFS_DINODE_MAGIC */
	uपूर्णांक16_t	di_mode;	/* mode and type of file */
	पूर्णांक8_t		di_version;	/* inode version */
	पूर्णांक8_t		di_क्रमmat;	/* क्रमmat of di_c data */
	uपूर्णांक8_t		di_pad3[2];	/* unused in v2/3 inodes */
	uपूर्णांक32_t	di_uid;		/* owner's user id */
	uपूर्णांक32_t	di_gid;		/* owner's group id */
	uपूर्णांक32_t	di_nlink;	/* number of links to file */
	uपूर्णांक16_t	di_projid_lo;	/* lower part of owner's project id */
	uपूर्णांक16_t	di_projid_hi;	/* higher part of owner's project id */
	uपूर्णांक8_t		di_pad[6];	/* unused, zeroed space */
	uपूर्णांक16_t	di_flushiter;	/* incremented on flush */
	xfs_log_बारtamp_t di_aसमय;	/* समय last accessed */
	xfs_log_बारtamp_t di_mसमय;	/* समय last modअगरied */
	xfs_log_बारtamp_t di_स_समय;	/* समय created/inode modअगरied */
	xfs_fमाप_प्रकार	di_size;	/* number of bytes in file */
	xfs_rfsblock_t	di_nblocks;	/* # of direct & btree blocks used */
	xfs_extlen_t	di_extsize;	/* basic/minimum extent size क्रम file */
	xfs_extnum_t	di_nextents;	/* number of extents in data विभाजन */
	xfs_aextnum_t	di_anextents;	/* number of extents in attribute विभाजन*/
	uपूर्णांक8_t		di_विभाजनoff;	/* attr विभाजन offs, <<3 क्रम 64b align */
	पूर्णांक8_t		di_aक्रमmat;	/* क्रमmat of attr विभाजन's data */
	uपूर्णांक32_t	di_dmevmask;	/* DMIG event mask */
	uपूर्णांक16_t	di_dmstate;	/* DMIG state info */
	uपूर्णांक16_t	di_flags;	/* अक्रमom flags, XFS_DIFLAG_... */
	uपूर्णांक32_t	di_gen;		/* generation number */

	/* di_next_unlinked is the only non-core field in the old dinode */
	xfs_agino_t	di_next_unlinked;/* agi unlinked list ptr */

	/* start of the extended dinode, writable fields */
	uपूर्णांक32_t	di_crc;		/* CRC of the inode */
	uपूर्णांक64_t	di_changecount;	/* number of attribute changes */
	xfs_lsn_t	di_lsn;		/* flush sequence */
	uपूर्णांक64_t	di_flags2;	/* more अक्रमom flags */
	uपूर्णांक32_t	di_cowextsize;	/* basic cow extent size क्रम file */
	uपूर्णांक8_t		di_pad2[12];	/* more padding क्रम future expansion */

	/* fields only written to during inode creation */
	xfs_log_बारtamp_t di_crसमय;	/* समय created */
	xfs_ino_t	di_ino;		/* inode number */
	uuid_t		di_uuid;	/* UUID of the fileप्रणाली */

	/* काष्ठाure must be padded to 64 bit alignment */
पूर्ण;

#घोषणा xfs_log_dinode_size(mp)						\
	(xfs_sb_version_has_v3inode(&(mp)->m_sb) ?			\
		माप(काष्ठा xfs_log_dinode) :				\
		दुरत्व(काष्ठा xfs_log_dinode, di_next_unlinked))

/*
 * Buffer Log Format definitions
 *
 * These are the physical dirty biपंचांगap definitions क्रम the log क्रमmat काष्ठाure.
 */
#घोषणा	XFS_BLF_CHUNK		128
#घोषणा	XFS_BLF_SHIFT		7
#घोषणा	BIT_TO_WORD_SHIFT	5
#घोषणा	NBWORD			(NBBY * माप(अचिन्हित पूर्णांक))

/*
 * This flag indicates that the buffer contains on disk inodes
 * and requires special recovery handling.
 */
#घोषणा	XFS_BLF_INODE_BUF	(1<<0)

/*
 * This flag indicates that the buffer should not be replayed
 * during recovery because its blocks are being मुक्तd.
 */
#घोषणा	XFS_BLF_CANCEL		(1<<1)

/*
 * This flag indicates that the buffer contains on disk
 * user or group dquots and may require special recovery handling.
 */
#घोषणा	XFS_BLF_UDQUOT_BUF	(1<<2)
#घोषणा XFS_BLF_PDQUOT_BUF	(1<<3)
#घोषणा	XFS_BLF_GDQUOT_BUF	(1<<4)

/*
 * This is the काष्ठाure used to lay out a buf log item in the log.  The data
 * map describes which 128 byte chunks of the buffer have been logged.
 *
 * The placement of blf_map_size causes blf_data_map to start at an odd
 * multiple of माप(अचिन्हित पूर्णांक) offset within the काष्ठा.  Because the data
 * biपंचांगap size will always be an even number, the end of the data_map (and
 * thereक्रमe the काष्ठाure) will also be at an odd multiple of माप(अचिन्हित
 * पूर्णांक).  Some 64-bit compilers will insert padding at the end of the काष्ठा to
 * ensure 64-bit alignment of blf_blkno, but 32-bit ones will not.  Thereक्रमe,
 * XFS_BLF_DATAMAP_SIZE must be an odd number to make the padding explicit and
 * keep the काष्ठाure size consistent between 32-bit and 64-bit platक्रमms.
 */
#घोषणा __XFS_BLF_DATAMAP_SIZE	((XFS_MAX_BLOCKSIZE / XFS_BLF_CHUNK) / NBWORD)
#घोषणा XFS_BLF_DATAMAP_SIZE	(__XFS_BLF_DATAMAP_SIZE + 1)

प्रकार काष्ठा xfs_buf_log_क्रमmat अणु
	अचिन्हित लघु	blf_type;	/* buf log item type indicator */
	अचिन्हित लघु	blf_size;	/* size of this item */
	अचिन्हित लघु	blf_flags;	/* misc state */
	अचिन्हित लघु	blf_len;	/* number of blocks in this buf */
	पूर्णांक64_t		blf_blkno;	/* starting blkno of this buf */
	अचिन्हित पूर्णांक	blf_map_size;	/* used size of data biपंचांगap in words */
	अचिन्हित पूर्णांक	blf_data_map[XFS_BLF_DATAMAP_SIZE]; /* dirty biपंचांगap */
पूर्ण xfs_buf_log_क्रमmat_t;

/*
 * All buffers now need to tell recovery where the magic number
 * is so that it can verअगरy and calculate the CRCs on the buffer correctly
 * once the changes have been replayed पूर्णांकo the buffer.
 *
 * The type value is held in the upper 5 bits of the blf_flags field, which is
 * an अचिन्हित 16 bit field. Hence we need to shअगरt it 11 bits up and करोwn.
 */
#घोषणा XFS_BLFT_BITS	5
#घोषणा XFS_BLFT_SHIFT	11
#घोषणा XFS_BLFT_MASK	(((1 << XFS_BLFT_BITS) - 1) << XFS_BLFT_SHIFT)

क्रमागत xfs_blft अणु
	XFS_BLFT_UNKNOWN_BUF = 0,
	XFS_BLFT_UDQUOT_BUF,
	XFS_BLFT_PDQUOT_BUF,
	XFS_BLFT_GDQUOT_BUF,
	XFS_BLFT_BTREE_BUF,
	XFS_BLFT_AGF_BUF,
	XFS_BLFT_AGFL_BUF,
	XFS_BLFT_AGI_BUF,
	XFS_BLFT_DINO_BUF,
	XFS_BLFT_SYMLINK_BUF,
	XFS_BLFT_सूची_BLOCK_BUF,
	XFS_BLFT_सूची_DATA_BUF,
	XFS_BLFT_सूची_FREE_BUF,
	XFS_BLFT_सूची_LEAF1_BUF,
	XFS_BLFT_सूची_LEAFN_BUF,
	XFS_BLFT_DA_NODE_BUF,
	XFS_BLFT_ATTR_LEAF_BUF,
	XFS_BLFT_ATTR_RMT_BUF,
	XFS_BLFT_SB_BUF,
	XFS_BLFT_RTBITMAP_BUF,
	XFS_BLFT_RTSUMMARY_BUF,
	XFS_BLFT_MAX_BUF = (1 << XFS_BLFT_BITS),
पूर्ण;

अटल अंतरभूत व्योम
xfs_blft_to_flags(काष्ठा xfs_buf_log_क्रमmat *blf, क्रमागत xfs_blft type)
अणु
	ASSERT(type > XFS_BLFT_UNKNOWN_BUF && type < XFS_BLFT_MAX_BUF);
	blf->blf_flags &= ~XFS_BLFT_MASK;
	blf->blf_flags |= ((type << XFS_BLFT_SHIFT) & XFS_BLFT_MASK);
पूर्ण

अटल अंतरभूत uपूर्णांक16_t
xfs_blft_from_flags(काष्ठा xfs_buf_log_क्रमmat *blf)
अणु
	वापस (blf->blf_flags & XFS_BLFT_MASK) >> XFS_BLFT_SHIFT;
पूर्ण

/*
 * EFI/EFD log क्रमmat definitions
 */
प्रकार काष्ठा xfs_extent अणु
	xfs_fsblock_t	ext_start;
	xfs_extlen_t	ext_len;
पूर्ण xfs_extent_t;

/*
 * Since an xfs_extent_t has types (start:64, len: 32)
 * there are dअगरferent alignments on 32 bit and 64 bit kernels.
 * So we provide the dअगरferent variants क्रम use by a
 * conversion routine.
 */
प्रकार काष्ठा xfs_extent_32 अणु
	uपूर्णांक64_t	ext_start;
	uपूर्णांक32_t	ext_len;
पूर्ण __attribute__((packed)) xfs_extent_32_t;

प्रकार काष्ठा xfs_extent_64 अणु
	uपूर्णांक64_t	ext_start;
	uपूर्णांक32_t	ext_len;
	uपूर्णांक32_t	ext_pad;
पूर्ण xfs_extent_64_t;

/*
 * This is the काष्ठाure used to lay out an efi log item in the
 * log.  The efi_extents field is a variable size array whose
 * size is given by efi_nextents.
 */
प्रकार काष्ठा xfs_efi_log_क्रमmat अणु
	uपूर्णांक16_t		efi_type;	/* efi log item type */
	uपूर्णांक16_t		efi_size;	/* size of this item */
	uपूर्णांक32_t		efi_nextents;	/* # extents to मुक्त */
	uपूर्णांक64_t		efi_id;		/* efi identअगरier */
	xfs_extent_t		efi_extents[1];	/* array of extents to मुक्त */
पूर्ण xfs_efi_log_क्रमmat_t;

प्रकार काष्ठा xfs_efi_log_क्रमmat_32 अणु
	uपूर्णांक16_t		efi_type;	/* efi log item type */
	uपूर्णांक16_t		efi_size;	/* size of this item */
	uपूर्णांक32_t		efi_nextents;	/* # extents to मुक्त */
	uपूर्णांक64_t		efi_id;		/* efi identअगरier */
	xfs_extent_32_t		efi_extents[1];	/* array of extents to मुक्त */
पूर्ण __attribute__((packed)) xfs_efi_log_क्रमmat_32_t;

प्रकार काष्ठा xfs_efi_log_क्रमmat_64 अणु
	uपूर्णांक16_t		efi_type;	/* efi log item type */
	uपूर्णांक16_t		efi_size;	/* size of this item */
	uपूर्णांक32_t		efi_nextents;	/* # extents to मुक्त */
	uपूर्णांक64_t		efi_id;		/* efi identअगरier */
	xfs_extent_64_t		efi_extents[1];	/* array of extents to मुक्त */
पूर्ण xfs_efi_log_क्रमmat_64_t;

/*
 * This is the काष्ठाure used to lay out an efd log item in the
 * log.  The efd_extents array is a variable size array whose
 * size is given by efd_nextents;
 */
प्रकार काष्ठा xfs_efd_log_क्रमmat अणु
	uपूर्णांक16_t		efd_type;	/* efd log item type */
	uपूर्णांक16_t		efd_size;	/* size of this item */
	uपूर्णांक32_t		efd_nextents;	/* # of extents मुक्तd */
	uपूर्णांक64_t		efd_efi_id;	/* id of corresponding efi */
	xfs_extent_t		efd_extents[1];	/* array of extents मुक्तd */
पूर्ण xfs_efd_log_क्रमmat_t;

प्रकार काष्ठा xfs_efd_log_क्रमmat_32 अणु
	uपूर्णांक16_t		efd_type;	/* efd log item type */
	uपूर्णांक16_t		efd_size;	/* size of this item */
	uपूर्णांक32_t		efd_nextents;	/* # of extents मुक्तd */
	uपूर्णांक64_t		efd_efi_id;	/* id of corresponding efi */
	xfs_extent_32_t		efd_extents[1];	/* array of extents मुक्तd */
पूर्ण __attribute__((packed)) xfs_efd_log_क्रमmat_32_t;

प्रकार काष्ठा xfs_efd_log_क्रमmat_64 अणु
	uपूर्णांक16_t		efd_type;	/* efd log item type */
	uपूर्णांक16_t		efd_size;	/* size of this item */
	uपूर्णांक32_t		efd_nextents;	/* # of extents मुक्तd */
	uपूर्णांक64_t		efd_efi_id;	/* id of corresponding efi */
	xfs_extent_64_t		efd_extents[1];	/* array of extents मुक्तd */
पूर्ण xfs_efd_log_क्रमmat_64_t;

/*
 * RUI/RUD (reverse mapping) log क्रमmat definitions
 */
काष्ठा xfs_map_extent अणु
	uपूर्णांक64_t		me_owner;
	uपूर्णांक64_t		me_startblock;
	uपूर्णांक64_t		me_startoff;
	uपूर्णांक32_t		me_len;
	uपूर्णांक32_t		me_flags;
पूर्ण;

/* rmap me_flags: upper bits are flags, lower byte is type code */
#घोषणा XFS_RMAP_EXTENT_MAP		1
#घोषणा XFS_RMAP_EXTENT_MAP_SHARED	2
#घोषणा XFS_RMAP_EXTENT_UNMAP		3
#घोषणा XFS_RMAP_EXTENT_UNMAP_SHARED	4
#घोषणा XFS_RMAP_EXTENT_CONVERT		5
#घोषणा XFS_RMAP_EXTENT_CONVERT_SHARED	6
#घोषणा XFS_RMAP_EXTENT_ALLOC		7
#घोषणा XFS_RMAP_EXTENT_FREE		8
#घोषणा XFS_RMAP_EXTENT_TYPE_MASK	0xFF

#घोषणा XFS_RMAP_EXTENT_ATTR_FORK	(1U << 31)
#घोषणा XFS_RMAP_EXTENT_BMBT_BLOCK	(1U << 30)
#घोषणा XFS_RMAP_EXTENT_UNWRITTEN	(1U << 29)

#घोषणा XFS_RMAP_EXTENT_FLAGS		(XFS_RMAP_EXTENT_TYPE_MASK | \
					 XFS_RMAP_EXTENT_ATTR_FORK | \
					 XFS_RMAP_EXTENT_BMBT_BLOCK | \
					 XFS_RMAP_EXTENT_UNWRITTEN)

/*
 * This is the काष्ठाure used to lay out an rui log item in the
 * log.  The rui_extents field is a variable size array whose
 * size is given by rui_nextents.
 */
काष्ठा xfs_rui_log_क्रमmat अणु
	uपूर्णांक16_t		rui_type;	/* rui log item type */
	uपूर्णांक16_t		rui_size;	/* size of this item */
	uपूर्णांक32_t		rui_nextents;	/* # extents to मुक्त */
	uपूर्णांक64_t		rui_id;		/* rui identअगरier */
	काष्ठा xfs_map_extent	rui_extents[];	/* array of extents to rmap */
पूर्ण;

अटल अंतरभूत माप_प्रकार
xfs_rui_log_क्रमmat_माप(
	अचिन्हित पूर्णांक		nr)
अणु
	वापस माप(काष्ठा xfs_rui_log_क्रमmat) +
			nr * माप(काष्ठा xfs_map_extent);
पूर्ण

/*
 * This is the काष्ठाure used to lay out an rud log item in the
 * log.  The rud_extents array is a variable size array whose
 * size is given by rud_nextents;
 */
काष्ठा xfs_rud_log_क्रमmat अणु
	uपूर्णांक16_t		rud_type;	/* rud log item type */
	uपूर्णांक16_t		rud_size;	/* size of this item */
	uपूर्णांक32_t		__pad;
	uपूर्णांक64_t		rud_rui_id;	/* id of corresponding rui */
पूर्ण;

/*
 * CUI/CUD (refcount update) log क्रमmat definitions
 */
काष्ठा xfs_phys_extent अणु
	uपूर्णांक64_t		pe_startblock;
	uपूर्णांक32_t		pe_len;
	uपूर्णांक32_t		pe_flags;
पूर्ण;

/* refcount pe_flags: upper bits are flags, lower byte is type code */
/* Type codes are taken directly from क्रमागत xfs_refcount_पूर्णांकent_type. */
#घोषणा XFS_REFCOUNT_EXTENT_TYPE_MASK	0xFF

#घोषणा XFS_REFCOUNT_EXTENT_FLAGS	(XFS_REFCOUNT_EXTENT_TYPE_MASK)

/*
 * This is the काष्ठाure used to lay out a cui log item in the
 * log.  The cui_extents field is a variable size array whose
 * size is given by cui_nextents.
 */
काष्ठा xfs_cui_log_क्रमmat अणु
	uपूर्णांक16_t		cui_type;	/* cui log item type */
	uपूर्णांक16_t		cui_size;	/* size of this item */
	uपूर्णांक32_t		cui_nextents;	/* # extents to मुक्त */
	uपूर्णांक64_t		cui_id;		/* cui identअगरier */
	काष्ठा xfs_phys_extent	cui_extents[];	/* array of extents */
पूर्ण;

अटल अंतरभूत माप_प्रकार
xfs_cui_log_क्रमmat_माप(
	अचिन्हित पूर्णांक		nr)
अणु
	वापस माप(काष्ठा xfs_cui_log_क्रमmat) +
			nr * माप(काष्ठा xfs_phys_extent);
पूर्ण

/*
 * This is the काष्ठाure used to lay out a cud log item in the
 * log.  The cud_extents array is a variable size array whose
 * size is given by cud_nextents;
 */
काष्ठा xfs_cud_log_क्रमmat अणु
	uपूर्णांक16_t		cud_type;	/* cud log item type */
	uपूर्णांक16_t		cud_size;	/* size of this item */
	uपूर्णांक32_t		__pad;
	uपूर्णांक64_t		cud_cui_id;	/* id of corresponding cui */
पूर्ण;

/*
 * BUI/BUD (inode block mapping) log क्रमmat definitions
 */

/* bmbt me_flags: upper bits are flags, lower byte is type code */
/* Type codes are taken directly from क्रमागत xfs_bmap_पूर्णांकent_type. */
#घोषणा XFS_BMAP_EXTENT_TYPE_MASK	0xFF

#घोषणा XFS_BMAP_EXTENT_ATTR_FORK	(1U << 31)
#घोषणा XFS_BMAP_EXTENT_UNWRITTEN	(1U << 30)

#घोषणा XFS_BMAP_EXTENT_FLAGS		(XFS_BMAP_EXTENT_TYPE_MASK | \
					 XFS_BMAP_EXTENT_ATTR_FORK | \
					 XFS_BMAP_EXTENT_UNWRITTEN)

/*
 * This is the काष्ठाure used to lay out an bui log item in the
 * log.  The bui_extents field is a variable size array whose
 * size is given by bui_nextents.
 */
काष्ठा xfs_bui_log_क्रमmat अणु
	uपूर्णांक16_t		bui_type;	/* bui log item type */
	uपूर्णांक16_t		bui_size;	/* size of this item */
	uपूर्णांक32_t		bui_nextents;	/* # extents to मुक्त */
	uपूर्णांक64_t		bui_id;		/* bui identअगरier */
	काष्ठा xfs_map_extent	bui_extents[];	/* array of extents to bmap */
पूर्ण;

अटल अंतरभूत माप_प्रकार
xfs_bui_log_क्रमmat_माप(
	अचिन्हित पूर्णांक		nr)
अणु
	वापस माप(काष्ठा xfs_bui_log_क्रमmat) +
			nr * माप(काष्ठा xfs_map_extent);
पूर्ण

/*
 * This is the काष्ठाure used to lay out an bud log item in the
 * log.  The bud_extents array is a variable size array whose
 * size is given by bud_nextents;
 */
काष्ठा xfs_bud_log_क्रमmat अणु
	uपूर्णांक16_t		bud_type;	/* bud log item type */
	uपूर्णांक16_t		bud_size;	/* size of this item */
	uपूर्णांक32_t		__pad;
	uपूर्णांक64_t		bud_bui_id;	/* id of corresponding bui */
पूर्ण;

/*
 * Dquot Log क्रमmat definitions.
 *
 * The first two fields must be the type and size fitting पूर्णांकo
 * 32 bits : log_recovery code assumes that.
 */
प्रकार काष्ठा xfs_dq_logक्रमmat अणु
	uपूर्णांक16_t		qlf_type;      /* dquot log item type */
	uपूर्णांक16_t		qlf_size;      /* size of this item */
	xfs_dqid_t		qlf_id;	       /* usr/grp/proj id : 32 bits */
	पूर्णांक64_t			qlf_blkno;     /* blkno of dquot buffer */
	पूर्णांक32_t			qlf_len;       /* len of dquot buffer */
	uपूर्णांक32_t		qlf_boffset;   /* off of dquot in buffer */
पूर्ण xfs_dq_logक्रमmat_t;

/*
 * log क्रमmat काष्ठा क्रम QUOTAOFF records.
 * The first two fields must be the type and size fitting पूर्णांकo
 * 32 bits : log_recovery code assumes that.
 * We ग_लिखो two LI_QUOTAOFF logitems per quotaoff, the last one keeps a poपूर्णांकer
 * to the first and ensures that the first logitem is taken out of the AIL
 * only when the last one is securely committed.
 */
प्रकार काष्ठा xfs_qoff_logक्रमmat अणु
	अचिन्हित लघु		qf_type;	/* quotaoff log item type */
	अचिन्हित लघु		qf_size;	/* size of this item */
	अचिन्हित पूर्णांक		qf_flags;	/* USR and/or GRP */
	अक्षर			qf_pad[12];	/* padding क्रम future */
पूर्ण xfs_qoff_logक्रमmat_t;

/*
 * Disk quotas status in m_qflags, and also sb_qflags. 16 bits.
 */
#घोषणा XFS_UQUOTA_ACCT	0x0001  /* user quota accounting ON */
#घोषणा XFS_UQUOTA_ENFD	0x0002  /* user quota limits enक्रमced */
#घोषणा XFS_UQUOTA_CHKD	0x0004  /* quotacheck run on usr quotas */
#घोषणा XFS_PQUOTA_ACCT	0x0008  /* project quota accounting ON */
#घोषणा XFS_OQUOTA_ENFD	0x0010  /* other (grp/prj) quota limits enक्रमced */
#घोषणा XFS_OQUOTA_CHKD	0x0020  /* quotacheck run on other (grp/prj) quotas */
#घोषणा XFS_GQUOTA_ACCT	0x0040  /* group quota accounting ON */

/*
 * Conversion to and from the combined OQUOTA flag (अगर necessary)
 * is करोne only in xfs_sb_qflags_to_disk() and xfs_sb_qflags_from_disk()
 */
#घोषणा XFS_GQUOTA_ENFD	0x0080  /* group quota limits enक्रमced */
#घोषणा XFS_GQUOTA_CHKD	0x0100  /* quotacheck run on group quotas */
#घोषणा XFS_PQUOTA_ENFD	0x0200  /* project quota limits enक्रमced */
#घोषणा XFS_PQUOTA_CHKD	0x0400  /* quotacheck run on project quotas */

#घोषणा XFS_ALL_QUOTA_ACCT	\
		(XFS_UQUOTA_ACCT | XFS_GQUOTA_ACCT | XFS_PQUOTA_ACCT)
#घोषणा XFS_ALL_QUOTA_ENFD	\
		(XFS_UQUOTA_ENFD | XFS_GQUOTA_ENFD | XFS_PQUOTA_ENFD)
#घोषणा XFS_ALL_QUOTA_CHKD	\
		(XFS_UQUOTA_CHKD | XFS_GQUOTA_CHKD | XFS_PQUOTA_CHKD)

#घोषणा XFS_MOUNT_QUOTA_ALL	(XFS_UQUOTA_ACCT|XFS_UQUOTA_ENFD|\
				 XFS_UQUOTA_CHKD|XFS_GQUOTA_ACCT|\
				 XFS_GQUOTA_ENFD|XFS_GQUOTA_CHKD|\
				 XFS_PQUOTA_ACCT|XFS_PQUOTA_ENFD|\
				 XFS_PQUOTA_CHKD)

/*
 * Inode create log item काष्ठाure
 *
 * Log recovery assumes the first two entries are the type and size and they fit
 * in 32 bits. Also in host order (ugh) so they have to be 32 bit aligned so
 * decoding can be करोne correctly.
 */
काष्ठा xfs_icreate_log अणु
	uपूर्णांक16_t	icl_type;	/* type of log क्रमmat काष्ठाure */
	uपूर्णांक16_t	icl_size;	/* size of log क्रमmat काष्ठाure */
	__be32		icl_ag;		/* ag being allocated in */
	__be32		icl_agbno;	/* start block of inode range */
	__be32		icl_count;	/* number of inodes to initialise */
	__be32		icl_isize;	/* size of inodes */
	__be32		icl_length;	/* length of extent to initialise */
	__be32		icl_gen;	/* inode generation number to use */
पूर्ण;

#पूर्ण_अगर /* __XFS_LOG_FORMAT_H__ */
