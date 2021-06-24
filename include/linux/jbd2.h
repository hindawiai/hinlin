<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/include/linux/jbd2.h
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>
 *
 * Copyright 1998-2000 Red Hat, Inc --- All Rights Reserved
 *
 * Definitions क्रम transaction data काष्ठाures क्रम the buffer cache
 * fileप्रणाली journaling support.
 */

#अगर_अघोषित _LINUX_JBD2_H
#घोषणा _LINUX_JBD2_H

/* Allow this file to be included directly पूर्णांकo e2fsprogs */
#अगर_अघोषित __KERNEL__
#समावेश "jfs_compat.h"
#घोषणा JBD2_DEBUG
#अन्यथा

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/journal-head.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/blkdev.h>
#समावेश <crypto/hash.h>
#पूर्ण_अगर

#घोषणा journal_oom_retry 1

/*
 * Define JBD2_PARANIOD_IOFAIL to cause a kernel BUG() अगर ext4 finds
 * certain classes of error which can occur due to failed IOs.  Under
 * normal use we want ext4 to जारी after such errors, because
 * hardware _can_ fail, but क्रम debugging purposes when running tests on
 * known-good hardware we may want to trap these errors.
 */
#अघोषित JBD2_PARANOID_IOFAIL

/*
 * The शेष maximum commit age, in seconds.
 */
#घोषणा JBD2_DEFAULT_MAX_COMMIT_AGE 5

#अगर_घोषित CONFIG_JBD2_DEBUG
/*
 * Define JBD2_EXPENSIVE_CHECKING to enable more expensive पूर्णांकernal
 * consistency checks.  By शेष we करोn't करो this unless
 * CONFIG_JBD2_DEBUG is on.
 */
#घोषणा JBD2_EXPENSIVE_CHECKING
बाह्य uलघु jbd2_journal_enable_debug;
व्योम __jbd2_debug(पूर्णांक level, स्थिर अक्षर *file, स्थिर अक्षर *func,
		  अचिन्हित पूर्णांक line, स्थिर अक्षर *fmt, ...);

#घोषणा jbd_debug(n, fmt, a...) \
	__jbd2_debug((n), __खाता__, __func__, __LINE__, (fmt), ##a)
#अन्यथा
#घोषणा jbd_debug(n, fmt, a...)  no_prपूर्णांकk(fmt, ##a)
#पूर्ण_अगर

बाह्य व्योम *jbd2_alloc(माप_प्रकार size, gfp_t flags);
बाह्य व्योम jbd2_मुक्त(व्योम *ptr, माप_प्रकार size);

#घोषणा JBD2_MIN_JOURNAL_BLOCKS 1024
#घोषणा JBD2_DEFAULT_FAST_COMMIT_BLOCKS 256

#अगर_घोषित __KERNEL__

/**
 * प्रकार handle_t - The handle_t type represents a single atomic update being perक्रमmed by some process.
 *
 * All fileप्रणाली modअगरications made by the process go
 * through this handle.  Recursive operations (such as quota operations)
 * are gathered पूर्णांकo a single update.
 *
 * The buffer credits field is used to account क्रम journaled buffers
 * being modअगरied by the running process.  To ensure that there is
 * enough log space क्रम all outstanding operations, we need to limit the
 * number of outstanding buffers possible at any समय.  When the
 * operation completes, any buffer credits not used are credited back to
 * the transaction, so that at all बार we know how many buffers the
 * outstanding updates on a transaction might possibly touch.
 *
 * This is an opaque datatype.
 **/
प्रकार काष्ठा jbd2_journal_handle handle_t;	/* Atomic operation type */


/**
 * प्रकार journal_t - The journal_t मुख्यtains all of the journaling state inक्रमmation क्रम a single fileप्रणाली.
 *
 * journal_t is linked to from the fs superblock काष्ठाure.
 *
 * We use the journal_t to keep track of all outstanding transaction
 * activity on the fileप्रणाली, and to manage the state of the log
 * writing process.
 *
 * This is an opaque datatype.
 **/
प्रकार काष्ठा journal_s	journal_t;	/* Journal control काष्ठाure */
#पूर्ण_अगर

/*
 * Internal काष्ठाures used by the logging mechanism:
 */

#घोषणा JBD2_MAGIC_NUMBER 0xc03b3998U /* The first 4 bytes of /dev/अक्रमom! */

/*
 * On-disk काष्ठाures
 */

/*
 * Descriptor block types:
 */

#घोषणा JBD2_DESCRIPTOR_BLOCK	1
#घोषणा JBD2_COMMIT_BLOCK	2
#घोषणा JBD2_SUPERBLOCK_V1	3
#घोषणा JBD2_SUPERBLOCK_V2	4
#घोषणा JBD2_REVOKE_BLOCK	5

/*
 * Standard header क्रम all descriptor blocks:
 */
प्रकार काष्ठा journal_header_s
अणु
	__be32		h_magic;
	__be32		h_blocktype;
	__be32		h_sequence;
पूर्ण journal_header_t;

/*
 * Checksum types.
 */
#घोषणा JBD2_CRC32_CHKSUM   1
#घोषणा JBD2_MD5_CHKSUM     2
#घोषणा JBD2_SHA1_CHKSUM    3
#घोषणा JBD2_CRC32C_CHKSUM  4

#घोषणा JBD2_CRC32_CHKSUM_SIZE 4

#घोषणा JBD2_CHECKSUM_BYTES (32 / माप(u32))
/*
 * Commit block header क्रम storing transactional checksums:
 *
 * NOTE: If FEATURE_COMPAT_CHECKSUM (checksum v1) is set, the h_chksum*
 * fields are used to store a checksum of the descriptor and data blocks.
 *
 * If FEATURE_INCOMPAT_CSUM_V2 (checksum v2) is set, then the h_chksum
 * field is used to store crc32c(uuid+commit_block).  Each journal metadata
 * block माला_लो its own checksum, and data block checksums are stored in
 * journal_block_tag (in the descriptor).  The other h_chksum* fields are
 * not used.
 *
 * If FEATURE_INCOMPAT_CSUM_V3 is set, the descriptor block uses
 * journal_block_tag3_t to store a full 32-bit checksum.  Everything अन्यथा
 * is the same as v2.
 *
 * Checksum v1, v2, and v3 are mutually exclusive features.
 */
काष्ठा commit_header अणु
	__be32		h_magic;
	__be32          h_blocktype;
	__be32          h_sequence;
	अचिन्हित अक्षर   h_chksum_type;
	अचिन्हित अक्षर   h_chksum_size;
	अचिन्हित अक्षर 	h_padding[2];
	__be32 		h_chksum[JBD2_CHECKSUM_BYTES];
	__be64		h_commit_sec;
	__be32		h_commit_nsec;
पूर्ण;

/*
 * The block tag: used to describe a single buffer in the journal.
 * t_blocknr_high is only used अगर INCOMPAT_64BIT is set, so this
 * raw काष्ठा shouldn't be used क्रम poपूर्णांकer math or माप() - use
 * journal_tag_bytes(journal) instead to compute this.
 */
प्रकार काष्ठा journal_block_tag3_s
अणु
	__be32		t_blocknr;	/* The on-disk block number */
	__be32		t_flags;	/* See below */
	__be32		t_blocknr_high; /* most-signअगरicant high 32bits. */
	__be32		t_checksum;	/* crc32c(uuid+seq+block) */
पूर्ण journal_block_tag3_t;

प्रकार काष्ठा journal_block_tag_s
अणु
	__be32		t_blocknr;	/* The on-disk block number */
	__be16		t_checksum;	/* truncated crc32c(uuid+seq+block) */
	__be16		t_flags;	/* See below */
	__be32		t_blocknr_high; /* most-signअगरicant high 32bits. */
पूर्ण journal_block_tag_t;

/* Tail of descriptor or revoke block, क्रम checksumming */
काष्ठा jbd2_journal_block_tail अणु
	__be32		t_checksum;	/* crc32c(uuid+descr_block) */
पूर्ण;

/*
 * The revoke descriptor: used on disk to describe a series of blocks to
 * be revoked from the log
 */
प्रकार काष्ठा jbd2_journal_revoke_header_s
अणु
	journal_header_t r_header;
	__be32		 r_count;	/* Count of bytes used in the block */
पूर्ण jbd2_journal_revoke_header_t;

/* Definitions क्रम the journal tag flags word: */
#घोषणा JBD2_FLAG_ESCAPE		1	/* on-disk block is escaped */
#घोषणा JBD2_FLAG_SAME_UUID	2	/* block has same uuid as previous */
#घोषणा JBD2_FLAG_DELETED	4	/* block deleted by this transaction */
#घोषणा JBD2_FLAG_LAST_TAG	8	/* last tag in this descriptor block */


/*
 * The journal superblock.  All fields are in big-endian byte order.
 */
प्रकार काष्ठा journal_superblock_s
अणु
/* 0x0000 */
	journal_header_t s_header;

/* 0x000C */
	/* Static inक्रमmation describing the journal */
	__be32	s_blocksize;		/* journal device blocksize */
	__be32	s_maxlen;		/* total blocks in journal file */
	__be32	s_first;		/* first block of log inक्रमmation */

/* 0x0018 */
	/* Dynamic inक्रमmation describing the current state of the log */
	__be32	s_sequence;		/* first commit ID expected in log */
	__be32	s_start;		/* blocknr of start of log */

/* 0x0020 */
	/* Error value, as set by jbd2_journal_पात(). */
	__be32	s_त्रुटि_सं;

/* 0x0024 */
	/* Reमुख्यing fields are only valid in a version-2 superblock */
	__be32	s_feature_compat;	/* compatible feature set */
	__be32	s_feature_incompat;	/* incompatible feature set */
	__be32	s_feature_ro_compat;	/* पढ़ोonly-compatible feature set */
/* 0x0030 */
	__u8	s_uuid[16];		/* 128-bit uuid क्रम journal */

/* 0x0040 */
	__be32	s_nr_users;		/* Nr of fileप्रणालीs sharing log */

	__be32	s_dynsuper;		/* Blocknr of dynamic superblock copy*/

/* 0x0048 */
	__be32	s_max_transaction;	/* Limit of journal blocks per trans.*/
	__be32	s_max_trans_data;	/* Limit of data blocks per trans. */

/* 0x0050 */
	__u8	s_checksum_type;	/* checksum type */
	__u8	s_padding2[3];
/* 0x0054 */
	__be32	s_num_fc_blks;		/* Number of fast commit blocks */
/* 0x0058 */
	__u32	s_padding[41];
	__be32	s_checksum;		/* crc32c(superblock) */

/* 0x0100 */
	__u8	s_users[16*48];		/* ids of all fs'es sharing the log */
/* 0x0400 */
पूर्ण journal_superblock_t;

/* Use the jbd2_अणुhas,set,clearपूर्ण_feature_* helpers; these will be हटाओd */
#घोषणा JBD2_HAS_COMPAT_FEATURE(j,mask)					\
	((j)->j_क्रमmat_version >= 2 &&					\
	 ((j)->j_superblock->s_feature_compat & cpu_to_be32((mask))))
#घोषणा JBD2_HAS_RO_COMPAT_FEATURE(j,mask)				\
	((j)->j_क्रमmat_version >= 2 &&					\
	 ((j)->j_superblock->s_feature_ro_compat & cpu_to_be32((mask))))
#घोषणा JBD2_HAS_INCOMPAT_FEATURE(j,mask)				\
	((j)->j_क्रमmat_version >= 2 &&					\
	 ((j)->j_superblock->s_feature_incompat & cpu_to_be32((mask))))

#घोषणा JBD2_FEATURE_COMPAT_CHECKSUM		0x00000001

#घोषणा JBD2_FEATURE_INCOMPAT_REVOKE		0x00000001
#घोषणा JBD2_FEATURE_INCOMPAT_64BIT		0x00000002
#घोषणा JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT	0x00000004
#घोषणा JBD2_FEATURE_INCOMPAT_CSUM_V2		0x00000008
#घोषणा JBD2_FEATURE_INCOMPAT_CSUM_V3		0x00000010
#घोषणा JBD2_FEATURE_INCOMPAT_FAST_COMMIT	0x00000020

/* See "journal feature predicate functions" below */

/* Features known to this kernel version: */
#घोषणा JBD2_KNOWN_COMPAT_FEATURES	JBD2_FEATURE_COMPAT_CHECKSUM
#घोषणा JBD2_KNOWN_ROCOMPAT_FEATURES	0
#घोषणा JBD2_KNOWN_INCOMPAT_FEATURES	(JBD2_FEATURE_INCOMPAT_REVOKE | \
					JBD2_FEATURE_INCOMPAT_64BIT | \
					JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT | \
					JBD2_FEATURE_INCOMPAT_CSUM_V2 | \
					JBD2_FEATURE_INCOMPAT_CSUM_V3 | \
					JBD2_FEATURE_INCOMPAT_FAST_COMMIT)

#अगर_घोषित __KERNEL__

#समावेश <linux/fs.h>
#समावेश <linux/sched.h>

क्रमागत jbd_state_bits अणु
	BH_JBD			/* Has an attached ext3 journal_head */
	  = BH_PrivateStart,
	BH_JWrite,		/* Being written to log (@@@ DEBUGGING) */
	BH_Freed,		/* Has been मुक्तd (truncated) */
	BH_Revoked,		/* Has been revoked from the log */
	BH_RevokeValid,		/* Revoked flag is valid */
	BH_JBDDirty,		/* Is dirty but journaled */
	BH_JournalHead,		/* Pins bh->b_निजी and jh->b_bh */
	BH_Shaकरोw,		/* IO on shaकरोw buffer is running */
	BH_Verअगरied,		/* Metadata block has been verअगरied ok */
	BH_JBDPrivateStart,	/* First bit available क्रम निजी use by FS */
पूर्ण;

BUFFER_FNS(JBD, jbd)
BUFFER_FNS(JWrite, jग_लिखो)
BUFFER_FNS(JBDDirty, jbddirty)
TAS_BUFFER_FNS(JBDDirty, jbddirty)
BUFFER_FNS(Revoked, revoked)
TAS_BUFFER_FNS(Revoked, revoked)
BUFFER_FNS(RevokeValid, revokevalid)
TAS_BUFFER_FNS(RevokeValid, revokevalid)
BUFFER_FNS(Freed, मुक्तd)
BUFFER_FNS(Shaकरोw, shaकरोw)
BUFFER_FNS(Verअगरied, verअगरied)

अटल अंतरभूत काष्ठा buffer_head *jh2bh(काष्ठा journal_head *jh)
अणु
	वापस jh->b_bh;
पूर्ण

अटल अंतरभूत काष्ठा journal_head *bh2jh(काष्ठा buffer_head *bh)
अणु
	वापस bh->b_निजी;
पूर्ण

अटल अंतरभूत व्योम jbd_lock_bh_journal_head(काष्ठा buffer_head *bh)
अणु
	bit_spin_lock(BH_JournalHead, &bh->b_state);
पूर्ण

अटल अंतरभूत व्योम jbd_unlock_bh_journal_head(काष्ठा buffer_head *bh)
अणु
	bit_spin_unlock(BH_JournalHead, &bh->b_state);
पूर्ण

#घोषणा J_ASSERT(निश्चित)	BUG_ON(!(निश्चित))

#घोषणा J_ASSERT_BH(bh, expr)	J_ASSERT(expr)
#घोषणा J_ASSERT_JH(jh, expr)	J_ASSERT(expr)

#अगर defined(JBD2_PARANOID_IOFAIL)
#घोषणा J_EXPECT(expr, why...)		J_ASSERT(expr)
#घोषणा J_EXPECT_BH(bh, expr, why...)	J_ASSERT_BH(bh, expr)
#घोषणा J_EXPECT_JH(jh, expr, why...)	J_ASSERT_JH(jh, expr)
#अन्यथा
#घोषणा __journal_expect(expr, why...)					     \
	(अणु								     \
		पूर्णांक val = (expr);					     \
		अगर (!val) अणु						     \
			prपूर्णांकk(KERN_ERR					     \
			       "JBD2 unexpected failure: %s: %s;\n",	     \
			       __func__, #expr);			     \
			prपूर्णांकk(KERN_ERR why "\n");			     \
		पूर्ण							     \
		val;							     \
	पूर्ण)
#घोषणा J_EXPECT(expr, why...)		__journal_expect(expr, ## why)
#घोषणा J_EXPECT_BH(bh, expr, why...)	__journal_expect(expr, ## why)
#घोषणा J_EXPECT_JH(jh, expr, why...)	__journal_expect(expr, ## why)
#पूर्ण_अगर

/* Flags in jbd_inode->i_flags */
#घोषणा __JI_COMMIT_RUNNING 0
#घोषणा __JI_WRITE_DATA 1
#घोषणा __JI_WAIT_DATA 2

/*
 * Commit of the inode data in progress. We use this flag to protect us from
 * concurrent deletion of inode. We cannot use reference to inode क्रम this
 * since we cannot afक्रमd करोing last iput() on behalf of kjournald
 */
#घोषणा JI_COMMIT_RUNNING (1 << __JI_COMMIT_RUNNING)
/* Write allocated dirty buffers in this inode beक्रमe commit */
#घोषणा JI_WRITE_DATA (1 << __JI_WRITE_DATA)
/* Wait क्रम outstanding data ग_लिखोs क्रम this inode beक्रमe commit */
#घोषणा JI_WAIT_DATA (1 << __JI_WAIT_DATA)

/**
 * काष्ठा jbd2_inode - The jbd_inode type is the काष्ठाure linking inodes in
 * ordered mode present in a transaction so that we can sync them during commit.
 */
काष्ठा jbd2_inode अणु
	/**
	 * @i_transaction:
	 *
	 * Which transaction करोes this inode beदीर्घ to? Either the running
	 * transaction or the committing one. [j_list_lock]
	 */
	transaction_t *i_transaction;

	/**
	 * @i_next_transaction:
	 *
	 * Poपूर्णांकer to the running transaction modअगरying inode's data in हाल
	 * there is alपढ़ोy a committing transaction touching it. [j_list_lock]
	 */
	transaction_t *i_next_transaction;

	/**
	 * @i_list: List of inodes in the i_transaction [j_list_lock]
	 */
	काष्ठा list_head i_list;

	/**
	 * @i_vfs_inode:
	 *
	 * VFS inode this inode beदीर्घs to [स्थिरant क्रम lअगरeसमय of काष्ठाure]
	 */
	काष्ठा inode *i_vfs_inode;

	/**
	 * @i_flags: Flags of inode [j_list_lock]
	 */
	अचिन्हित दीर्घ i_flags;

	/**
	 * @i_dirty_start:
	 *
	 * Offset in bytes where the dirty range क्रम this inode starts.
	 * [j_list_lock]
	 */
	loff_t i_dirty_start;

	/**
	 * @i_dirty_end:
	 *
	 * Inclusive offset in bytes where the dirty range क्रम this inode
	 * ends. [j_list_lock]
	 */
	loff_t i_dirty_end;
पूर्ण;

काष्ठा jbd2_revoke_table_s;

/**
 * काष्ठा jbd2_journal_handle - The jbd2_journal_handle type is the concrete
 *     type associated with handle_t.
 * @h_transaction: Which compound transaction is this update a part of?
 * @h_journal: Which journal handle beदीर्घs to - used अगरf h_reserved set.
 * @h_rsv_handle: Handle reserved क्रम finishing the logical operation.
 * @h_total_credits: Number of reमुख्यing buffers we are allowed to add to
 *	journal. These are dirty buffers and revoke descriptor blocks.
 * @h_revoke_credits: Number of reमुख्यing revoke records available क्रम handle
 * @h_ref: Reference count on this handle.
 * @h_err: Field क्रम caller's use to track errors through large fs operations.
 * @h_sync: Flag क्रम sync-on-बंद.
 * @h_jdata: Flag to क्रमce data journaling.
 * @h_reserved: Flag क्रम handle क्रम reserved credits.
 * @h_पातed: Flag indicating fatal error on handle.
 * @h_type: For handle statistics.
 * @h_line_no: For handle statistics.
 * @h_start_jअगरfies: Handle Start समय.
 * @h_requested_credits: Holds @h_total_credits after handle is started.
 * @h_revoke_credits_requested: Holds @h_revoke_credits after handle is started.
 * @saved_alloc_context: Saved context जबतक transaction is खोलो.
 **/

/* Docbook can't yet cope with the bit fields, but will leave the करोcumentation
 * in so it can be fixed later.
 */

काष्ठा jbd2_journal_handle
अणु
	जोड़ अणु
		transaction_t	*h_transaction;
		/* Which journal handle beदीर्घs to - used अगरf h_reserved set */
		journal_t	*h_journal;
	पूर्ण;

	handle_t		*h_rsv_handle;
	पूर्णांक			h_total_credits;
	पूर्णांक			h_revoke_credits;
	पूर्णांक			h_revoke_credits_requested;
	पूर्णांक			h_ref;
	पूर्णांक			h_err;

	/* Flags [no locking] */
	अचिन्हित पूर्णांक	h_sync:		1;
	अचिन्हित पूर्णांक	h_jdata:	1;
	अचिन्हित पूर्णांक	h_reserved:	1;
	अचिन्हित पूर्णांक	h_पातed:	1;
	अचिन्हित पूर्णांक	h_type:		8;
	अचिन्हित पूर्णांक	h_line_no:	16;

	अचिन्हित दीर्घ		h_start_jअगरfies;
	अचिन्हित पूर्णांक		h_requested_credits;

	अचिन्हित पूर्णांक		saved_alloc_context;
पूर्ण;


/*
 * Some stats क्रम checkpoपूर्णांक phase
 */
काष्ठा transaction_chp_stats_s अणु
	अचिन्हित दीर्घ		cs_chp_समय;
	__u32			cs_क्रमced_to_बंद;
	__u32			cs_written;
	__u32			cs_dropped;
पूर्ण;

/* The transaction_t type is the guts of the journaling mechanism.  It
 * tracks a compound transaction through its various states:
 *
 * RUNNING:	accepting new updates
 * LOCKED:	Updates still running but we करोn't accept new ones
 * RUNDOWN:	Updates are tidying up but have finished requesting
 *		new buffers to modअगरy (state not used क्रम now)
 * FLUSH:       All updates complete, but we are still writing to disk
 * COMMIT:      All data on disk, writing commit record
 * FINISHED:	We still have to keep the transaction क्रम checkpoपूर्णांकing.
 *
 * The transaction keeps track of all of the buffers modअगरied by a
 * running transaction, and all of the buffers committed but not yet
 * flushed to home क्रम finished transactions.
 * (Locking Documentation improved by LockDoc)
 */

/*
 * Lock ranking:
 *
 *    j_list_lock
 *      ->jbd_lock_bh_journal_head()	(This is "innermost")
 *
 *    j_state_lock
 *    ->b_state_lock
 *
 *    b_state_lock
 *    ->j_list_lock
 *
 *    j_state_lock
 *    ->t_handle_lock
 *
 *    j_state_lock
 *    ->j_list_lock			(journal_unmap_buffer)
 *
 */

काष्ठा transaction_s
अणु
	/* Poपूर्णांकer to the journal क्रम this transaction. [no locking] */
	journal_t		*t_journal;

	/* Sequence number क्रम this transaction [no locking] */
	tid_t			t_tid;

	/*
	 * Transaction's current state
	 * [no locking - only kjournald2 alters this]
	 * [j_list_lock] guards transition of a transaction पूर्णांकo T_FINISHED
	 * state and subsequent call of __jbd2_journal_drop_transaction()
	 * FIXME: needs barriers
	 * KLUDGE: [use j_state_lock]
	 */
	क्रमागत अणु
		T_RUNNING,
		T_LOCKED,
		T_SWITCH,
		T_FLUSH,
		T_COMMIT,
		T_COMMIT_DFLUSH,
		T_COMMIT_JFLUSH,
		T_COMMIT_CALLBACK,
		T_FINISHED
	पूर्ण			t_state;

	/*
	 * Where in the log करोes this transaction's commit start? [no locking]
	 */
	अचिन्हित दीर्घ		t_log_start;

	/* 
	 * Number of buffers on the t_buffers list [j_list_lock, no locks
	 * needed क्रम jbd2 thपढ़ो]
	 */
	पूर्णांक			t_nr_buffers;

	/*
	 * Doubly-linked circular list of all buffers reserved but not yet
	 * modअगरied by this transaction [j_list_lock, no locks needed fo
	 * jbd2 thपढ़ो]
	 */
	काष्ठा journal_head	*t_reserved_list;

	/*
	 * Doubly-linked circular list of all metadata buffers owned by this
	 * transaction [j_list_lock, no locks needed क्रम jbd2 thपढ़ो]
	 */
	काष्ठा journal_head	*t_buffers;

	/*
	 * Doubly-linked circular list of all क्रमget buffers (superseded
	 * buffers which we can un-checkpoपूर्णांक once this transaction commits)
	 * [j_list_lock]
	 */
	काष्ठा journal_head	*t_क्रमget;

	/*
	 * Doubly-linked circular list of all buffers still to be flushed beक्रमe
	 * this transaction can be checkpoपूर्णांकed. [j_list_lock]
	 */
	काष्ठा journal_head	*t_checkpoपूर्णांक_list;

	/*
	 * Doubly-linked circular list of all buffers submitted क्रम IO जबतक
	 * checkpoपूर्णांकing. [j_list_lock]
	 */
	काष्ठा journal_head	*t_checkpoपूर्णांक_io_list;

	/*
	 * Doubly-linked circular list of metadata buffers being
	 * shaकरोwed by log IO.  The IO buffers on the iobuf list and
	 * the shaकरोw buffers on this list match each other one क्रम
	 * one at all बार. [j_list_lock, no locks needed क्रम jbd2
	 * thपढ़ो]
	 */
	काष्ठा journal_head	*t_shaकरोw_list;

	/*
	 * List of inodes associated with the transaction; e.g., ext4 uses
	 * this to track inodes in data=ordered and data=journal mode that
	 * need special handling on transaction commit; also used by ocfs2.
	 * [j_list_lock]
	 */
	काष्ठा list_head	t_inode_list;

	/*
	 * Protects info related to handles
	 */
	spinlock_t		t_handle_lock;

	/*
	 * Longest समय some handle had to रुको क्रम running transaction
	 */
	अचिन्हित दीर्घ		t_max_रुको;

	/*
	 * When transaction started
	 */
	अचिन्हित दीर्घ		t_start;

	/*
	 * When commit was requested [j_state_lock]
	 */
	अचिन्हित दीर्घ		t_requested;

	/*
	 * Checkpoपूर्णांकing stats [j_list_lock]
	 */
	काष्ठा transaction_chp_stats_s t_chp_stats;

	/*
	 * Number of outstanding updates running on this transaction
	 * [none]
	 */
	atomic_t		t_updates;

	/*
	 * Number of blocks reserved क्रम this transaction in the journal.
	 * This is including all credits reserved when starting transaction
	 * handles as well as all journal descriptor blocks needed क्रम this
	 * transaction. [none]
	 */
	atomic_t		t_outstanding_credits;

	/*
	 * Number of revoke records क्रम this transaction added by alपढ़ोy
	 * stopped handles. [none]
	 */
	atomic_t		t_outstanding_revokes;

	/*
	 * How many handles used this transaction? [none]
	 */
	atomic_t		t_handle_count;

	/*
	 * Forward and backward links क्रम the circular list of all transactions
	 * aरुकोing checkpoपूर्णांक. [j_list_lock]
	 */
	transaction_t		*t_cpnext, *t_cpprev;

	/*
	 * When will the transaction expire (become due क्रम commit), in jअगरfies?
	 * [no locking]
	 */
	अचिन्हित दीर्घ		t_expires;

	/*
	 * When this transaction started, in nanoseconds [no locking]
	 */
	kसमय_प्रकार			t_start_समय;

	/*
	 * This transaction is being क्रमced and some process is
	 * रुकोing क्रम it to finish.
	 */
	अचिन्हित पूर्णांक t_synchronous_commit:1;

	/* Disk flush needs to be sent to fs partition [no locking] */
	पूर्णांक			t_need_data_flush;

	/*
	 * For use by the fileप्रणाली to store fs-specअगरic data
	 * काष्ठाures associated with the transaction
	 */
	काष्ठा list_head	t_निजी_list;
पूर्ण;

काष्ठा transaction_run_stats_s अणु
	अचिन्हित दीर्घ		rs_रुको;
	अचिन्हित दीर्घ		rs_request_delay;
	अचिन्हित दीर्घ		rs_running;
	अचिन्हित दीर्घ		rs_locked;
	अचिन्हित दीर्घ		rs_flushing;
	अचिन्हित दीर्घ		rs_logging;

	__u32			rs_handle_count;
	__u32			rs_blocks;
	__u32			rs_blocks_logged;
पूर्ण;

काष्ठा transaction_stats_s अणु
	अचिन्हित दीर्घ		ts_tid;
	अचिन्हित दीर्घ		ts_requested;
	काष्ठा transaction_run_stats_s run;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ
jbd2_समय_dअगरf(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (end >= start)
		वापस end - start;

	वापस end + (MAX_JIFFY_OFFSET - start);
पूर्ण

#घोषणा JBD2_NR_BATCH	64

क्रमागत passtype अणुPASS_SCAN, PASS_REVOKE, PASS_REPLAYपूर्ण;

#घोषणा JBD2_FC_REPLAY_STOP	0
#घोषणा JBD2_FC_REPLAY_CONTINUE	1

/**
 * काष्ठा journal_s - The journal_s type is the concrete type associated with
 *     journal_t.
 */
काष्ठा journal_s
अणु
	/**
	 * @j_flags: General journaling state flags [j_state_lock,
	 * no lock क्रम quick racy checks]
	 */
	अचिन्हित दीर्घ		j_flags;

	/**
	 * @j_त्रुटि_सं:
	 *
	 * Is there an outstanding uncleared error on the journal (from a prior
	 * पात)? [j_state_lock]
	 */
	पूर्णांक			j_त्रुटि_सं;

	/**
	 * @j_पात_mutex: Lock the whole पातing procedure.
	 */
	काष्ठा mutex		j_पात_mutex;

	/**
	 * @j_sb_buffer: The first part of the superblock buffer.
	 */
	काष्ठा buffer_head	*j_sb_buffer;

	/**
	 * @j_superblock: The second part of the superblock buffer.
	 */
	journal_superblock_t	*j_superblock;

	/**
	 * @j_क्रमmat_version: Version of the superblock क्रमmat.
	 */
	पूर्णांक			j_क्रमmat_version;

	/**
	 * @j_state_lock: Protect the various scalars in the journal.
	 */
	rwlock_t		j_state_lock;

	/**
	 * @j_barrier_count:
	 *
	 * Number of processes रुकोing to create a barrier lock [j_state_lock,
	 * no lock क्रम quick racy checks]
	 */
	पूर्णांक			j_barrier_count;

	/**
	 * @j_barrier: The barrier lock itself.
	 */
	काष्ठा mutex		j_barrier;

	/**
	 * @j_running_transaction:
	 *
	 * Transactions: The current running transaction...
	 * [j_state_lock, no lock क्रम quick racy checks] [caller holding
	 * खोलो handle]
	 */
	transaction_t		*j_running_transaction;

	/**
	 * @j_committing_transaction:
	 *
	 * the transaction we are pushing to disk
	 * [j_state_lock] [caller holding खोलो handle]
	 */
	transaction_t		*j_committing_transaction;

	/**
	 * @j_checkpoपूर्णांक_transactions:
	 *
	 * ... and a linked circular list of all transactions रुकोing क्रम
	 * checkpoपूर्णांकing. [j_list_lock]
	 */
	transaction_t		*j_checkpoपूर्णांक_transactions;

	/**
	 * @j_रुको_transaction_locked:
	 *
	 * Wait queue क्रम रुकोing क्रम a locked transaction to start committing,
	 * or क्रम a barrier lock to be released.
	 */
	रुको_queue_head_t	j_रुको_transaction_locked;

	/**
	 * @j_रुको_करोne_commit: Wait queue क्रम रुकोing क्रम commit to complete.
	 */
	रुको_queue_head_t	j_रुको_करोne_commit;

	/**
	 * @j_रुको_commit: Wait queue to trigger commit.
	 */
	रुको_queue_head_t	j_रुको_commit;

	/**
	 * @j_रुको_updates: Wait queue to रुको क्रम updates to complete.
	 */
	रुको_queue_head_t	j_रुको_updates;

	/**
	 * @j_रुको_reserved:
	 *
	 * Wait queue to रुको क्रम reserved buffer credits to drop.
	 */
	रुको_queue_head_t	j_रुको_reserved;

	/**
	 * @j_fc_रुको:
	 *
	 * Wait queue to रुको क्रम completion of async fast commits.
	 */
	रुको_queue_head_t	j_fc_रुको;

	/**
	 * @j_checkpoपूर्णांक_mutex:
	 *
	 * Semaphore क्रम locking against concurrent checkpoपूर्णांकs.
	 */
	काष्ठा mutex		j_checkpoपूर्णांक_mutex;

	/**
	 * @j_chkpt_bhs:
	 *
	 * List of buffer heads used by the checkpoपूर्णांक routine.  This
	 * was moved from jbd2_log_करो_checkpoपूर्णांक() to reduce stack
	 * usage.  Access to this array is controlled by the
	 * @j_checkpoपूर्णांक_mutex.  [j_checkpoपूर्णांक_mutex]
	 */
	काष्ठा buffer_head	*j_chkpt_bhs[JBD2_NR_BATCH];

	/**
	 * @j_head:
	 *
	 * Journal head: identअगरies the first unused block in the journal.
	 * [j_state_lock]
	 */
	अचिन्हित दीर्घ		j_head;

	/**
	 * @j_tail:
	 *
	 * Journal tail: identअगरies the oldest still-used block in the journal.
	 * [j_state_lock]
	 */
	अचिन्हित दीर्घ		j_tail;

	/**
	 * @j_मुक्त:
	 *
	 * Journal मुक्त: how many मुक्त blocks are there in the journal?
	 * [j_state_lock]
	 */
	अचिन्हित दीर्घ		j_मुक्त;

	/**
	 * @j_first:
	 *
	 * The block number of the first usable block in the journal
	 * [j_state_lock].
	 */
	अचिन्हित दीर्घ		j_first;

	/**
	 * @j_last:
	 *
	 * The block number one beyond the last usable block in the journal
	 * [j_state_lock].
	 */
	अचिन्हित दीर्घ		j_last;

	/**
	 * @j_fc_first:
	 *
	 * The block number of the first fast commit block in the journal
	 * [j_state_lock].
	 */
	अचिन्हित दीर्घ		j_fc_first;

	/**
	 * @j_fc_off:
	 *
	 * Number of fast commit blocks currently allocated. Accessed only
	 * during fast commit. Currently only process can करो fast commit, so
	 * this field is not रक्षित by any lock.
	 */
	अचिन्हित दीर्घ		j_fc_off;

	/**
	 * @j_fc_last:
	 *
	 * The block number one beyond the last fast commit block in the journal
	 * [j_state_lock].
	 */
	अचिन्हित दीर्घ		j_fc_last;

	/**
	 * @j_dev: Device where we store the journal.
	 */
	काष्ठा block_device	*j_dev;

	/**
	 * @j_blocksize: Block size क्रम the location where we store the journal.
	 */
	पूर्णांक			j_blocksize;

	/**
	 * @j_blk_offset:
	 *
	 * Starting block offset पूर्णांकo the device where we store the journal.
	 */
	अचिन्हित दीर्घ दीर्घ	j_blk_offset;

	/**
	 * @j_devname: Journal device name.
	 */
	अक्षर			j_devname[BDEVNAME_SIZE+24];

	/**
	 * @j_fs_dev:
	 *
	 * Device which holds the client fs.  For पूर्णांकernal journal this will be
	 * equal to j_dev.
	 */
	काष्ठा block_device	*j_fs_dev;

	/**
	 * @j_total_len: Total maximum capacity of the journal region on disk.
	 */
	अचिन्हित पूर्णांक		j_total_len;

	/**
	 * @j_reserved_credits:
	 *
	 * Number of buffers reserved from the running transaction.
	 */
	atomic_t		j_reserved_credits;

	/**
	 * @j_list_lock: Protects the buffer lists and पूर्णांकernal buffer state.
	 */
	spinlock_t		j_list_lock;

	/**
	 * @j_inode:
	 *
	 * Optional inode where we store the journal.  If present, all
	 * journal block numbers are mapped पूर्णांकo this inode via bmap().
	 */
	काष्ठा inode		*j_inode;

	/**
	 * @j_tail_sequence:
	 *
	 * Sequence number of the oldest transaction in the log [j_state_lock]
	 */
	tid_t			j_tail_sequence;

	/**
	 * @j_transaction_sequence:
	 *
	 * Sequence number of the next transaction to grant [j_state_lock]
	 */
	tid_t			j_transaction_sequence;

	/**
	 * @j_commit_sequence:
	 *
	 * Sequence number of the most recently committed transaction
	 * [j_state_lock, no lock क्रम quick racy checks]
	 */
	tid_t			j_commit_sequence;

	/**
	 * @j_commit_request:
	 *
	 * Sequence number of the most recent transaction wanting commit
	 * [j_state_lock, no lock क्रम quick racy checks]
	 */
	tid_t			j_commit_request;

	/**
	 * @j_uuid:
	 *
	 * Journal uuid: identअगरies the object (fileप्रणाली, LVM volume etc)
	 * backed by this journal.  This will eventually be replaced by an array
	 * of uuids, allowing us to index multiple devices within a single
	 * journal and to perक्रमm atomic updates across them.
	 */
	__u8			j_uuid[16];

	/**
	 * @j_task: Poपूर्णांकer to the current commit thपढ़ो क्रम this journal.
	 */
	काष्ठा task_काष्ठा	*j_task;

	/**
	 * @j_max_transaction_buffers:
	 *
	 * Maximum number of metadata buffers to allow in a single compound
	 * commit transaction.
	 */
	पूर्णांक			j_max_transaction_buffers;

	/**
	 * @j_revoke_records_per_block:
	 *
	 * Number of revoke records that fit in one descriptor block.
	 */
	पूर्णांक			j_revoke_records_per_block;

	/**
	 * @j_commit_पूर्णांकerval:
	 *
	 * What is the maximum transaction lअगरeसमय beक्रमe we begin a commit?
	 */
	अचिन्हित दीर्घ		j_commit_पूर्णांकerval;

	/**
	 * @j_commit_समयr: The समयr used to wakeup the commit thपढ़ो.
	 */
	काष्ठा समयr_list	j_commit_समयr;

	/**
	 * @j_revoke_lock: Protect the revoke table.
	 */
	spinlock_t		j_revoke_lock;

	/**
	 * @j_revoke:
	 *
	 * The revoke table - मुख्यtains the list of revoked blocks in the
	 * current transaction.
	 */
	काष्ठा jbd2_revoke_table_s *j_revoke;

	/**
	 * @j_revoke_table: Alternate revoke tables क्रम j_revoke.
	 */
	काष्ठा jbd2_revoke_table_s *j_revoke_table[2];

	/**
	 * @j_wbuf: Array of bhs क्रम jbd2_journal_commit_transaction.
	 */
	काष्ठा buffer_head	**j_wbuf;

	/**
	 * @j_fc_wbuf: Array of fast commit bhs क्रम fast commit. Accessed only
	 * during a fast commit. Currently only process can करो fast commit, so
	 * this field is not रक्षित by any lock.
	 */
	काष्ठा buffer_head	**j_fc_wbuf;

	/**
	 * @j_wbufsize:
	 *
	 * Size of @j_wbuf array.
	 */
	पूर्णांक			j_wbufsize;

	/**
	 * @j_fc_wbufsize:
	 *
	 * Size of @j_fc_wbuf array.
	 */
	पूर्णांक			j_fc_wbufsize;

	/**
	 * @j_last_sync_ग_लिखोr:
	 *
	 * The pid of the last person to run a synchronous operation
	 * through the journal.
	 */
	pid_t			j_last_sync_ग_लिखोr;

	/**
	 * @j_average_commit_समय:
	 *
	 * The average amount of समय in nanoseconds it takes to commit a
	 * transaction to disk. [j_state_lock]
	 */
	u64			j_average_commit_समय;

	/**
	 * @j_min_batch_समय:
	 *
	 * Minimum समय that we should रुको क्रम additional fileप्रणाली operations
	 * to get batched पूर्णांकo a synchronous handle in microseconds.
	 */
	u32			j_min_batch_समय;

	/**
	 * @j_max_batch_समय:
	 *
	 * Maximum समय that we should रुको क्रम additional fileप्रणाली operations
	 * to get batched पूर्णांकo a synchronous handle in microseconds.
	 */
	u32			j_max_batch_समय;

	/**
	 * @j_commit_callback:
	 *
	 * This function is called when a transaction is बंदd.
	 */
	व्योम			(*j_commit_callback)(journal_t *,
						     transaction_t *);

	/**
	 * @j_submit_inode_data_buffers:
	 *
	 * This function is called क्रम all inodes associated with the
	 * committing transaction marked with JI_WRITE_DATA flag
	 * beक्रमe we start to ग_लिखो out the transaction to the journal.
	 */
	पूर्णांक			(*j_submit_inode_data_buffers)
					(काष्ठा jbd2_inode *);

	/**
	 * @j_finish_inode_data_buffers:
	 *
	 * This function is called क्रम all inodes associated with the
	 * committing transaction marked with JI_WAIT_DATA flag
	 * after we have written the transaction to the journal
	 * but beक्रमe we ग_लिखो out the commit block.
	 */
	पूर्णांक			(*j_finish_inode_data_buffers)
					(काष्ठा jbd2_inode *);

	/*
	 * Journal statistics
	 */

	/**
	 * @j_history_lock: Protect the transactions statistics history.
	 */
	spinlock_t		j_history_lock;

	/**
	 * @j_proc_entry: procfs entry क्रम the jbd statistics directory.
	 */
	काष्ठा proc_dir_entry	*j_proc_entry;

	/**
	 * @j_stats: Overall statistics.
	 */
	काष्ठा transaction_stats_s j_stats;

	/**
	 * @j_failed_commit: Failed journal commit ID.
	 */
	अचिन्हित पूर्णांक		j_failed_commit;

	/**
	 * @j_निजी:
	 *
	 * An opaque poपूर्णांकer to fs-निजी inक्रमmation.  ext3 माला_दो its
	 * superblock poपूर्णांकer here.
	 */
	व्योम *j_निजी;

	/**
	 * @j_chksum_driver:
	 *
	 * Reference to checksum algorithm driver via cryptoapi.
	 */
	काष्ठा crypto_shash *j_chksum_driver;

	/**
	 * @j_csum_seed:
	 *
	 * Precomputed journal UUID checksum क्रम seeding other checksums.
	 */
	__u32 j_csum_seed;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	/**
	 * @j_trans_commit_map:
	 *
	 * Lockdep entity to track transaction commit dependencies. Handles
	 * hold this "lock" क्रम पढ़ो, when we रुको क्रम commit, we acquire the
	 * "lock" क्रम writing. This matches the properties of jbd2 journalling
	 * where the running transaction has to रुको क्रम all handles to be
	 * dropped to commit that transaction and also acquiring a handle may
	 * require transaction commit to finish.
	 */
	काष्ठा lockdep_map	j_trans_commit_map;
#पूर्ण_अगर

	/**
	 * @j_fc_cleanup_callback:
	 *
	 * Clean-up after fast commit or full commit. JBD2 calls this function
	 * after every commit operation.
	 */
	व्योम (*j_fc_cleanup_callback)(काष्ठा journal_s *journal, पूर्णांक);

	/**
	 * @j_fc_replay_callback:
	 *
	 * File-प्रणाली specअगरic function that perक्रमms replay of a fast
	 * commit. JBD2 calls this function क्रम each fast commit block found in
	 * the journal. This function should वापस JBD2_FC_REPLAY_CONTINUE
	 * to indicate that the block was processed correctly and more fast
	 * commit replay should जारी. Return value of JBD2_FC_REPLAY_STOP
	 * indicates the end of replay (no more blocks reमुख्यing). A negative
	 * वापस value indicates error.
	 */
	पूर्णांक (*j_fc_replay_callback)(काष्ठा journal_s *journal,
				    काष्ठा buffer_head *bh,
				    क्रमागत passtype pass, पूर्णांक off,
				    tid_t expected_commit_id);
पूर्ण;

#घोषणा jbd2_might_रुको_क्रम_commit(j) \
	करो अणु \
		rwsem_acquire(&j->j_trans_commit_map, 0, 0, _THIS_IP_); \
		rwsem_release(&j->j_trans_commit_map, _THIS_IP_); \
	पूर्ण जबतक (0)

/* journal feature predicate functions */
#घोषणा JBD2_FEATURE_COMPAT_FUNCS(name, flagname) \
अटल अंतरभूत bool jbd2_has_feature_##name(journal_t *j) \
अणु \
	वापस ((j)->j_क्रमmat_version >= 2 && \
		((j)->j_superblock->s_feature_compat & \
		 cpu_to_be32(JBD2_FEATURE_COMPAT_##flagname)) != 0); \
पूर्ण \
अटल अंतरभूत व्योम jbd2_set_feature_##name(journal_t *j) \
अणु \
	(j)->j_superblock->s_feature_compat |= \
		cpu_to_be32(JBD2_FEATURE_COMPAT_##flagname); \
पूर्ण \
अटल अंतरभूत व्योम jbd2_clear_feature_##name(journal_t *j) \
अणु \
	(j)->j_superblock->s_feature_compat &= \
		~cpu_to_be32(JBD2_FEATURE_COMPAT_##flagname); \
पूर्ण

#घोषणा JBD2_FEATURE_RO_COMPAT_FUNCS(name, flagname) \
अटल अंतरभूत bool jbd2_has_feature_##name(journal_t *j) \
अणु \
	वापस ((j)->j_क्रमmat_version >= 2 && \
		((j)->j_superblock->s_feature_ro_compat & \
		 cpu_to_be32(JBD2_FEATURE_RO_COMPAT_##flagname)) != 0); \
पूर्ण \
अटल अंतरभूत व्योम jbd2_set_feature_##name(journal_t *j) \
अणु \
	(j)->j_superblock->s_feature_ro_compat |= \
		cpu_to_be32(JBD2_FEATURE_RO_COMPAT_##flagname); \
पूर्ण \
अटल अंतरभूत व्योम jbd2_clear_feature_##name(journal_t *j) \
अणु \
	(j)->j_superblock->s_feature_ro_compat &= \
		~cpu_to_be32(JBD2_FEATURE_RO_COMPAT_##flagname); \
पूर्ण

#घोषणा JBD2_FEATURE_INCOMPAT_FUNCS(name, flagname) \
अटल अंतरभूत bool jbd2_has_feature_##name(journal_t *j) \
अणु \
	वापस ((j)->j_क्रमmat_version >= 2 && \
		((j)->j_superblock->s_feature_incompat & \
		 cpu_to_be32(JBD2_FEATURE_INCOMPAT_##flagname)) != 0); \
पूर्ण \
अटल अंतरभूत व्योम jbd2_set_feature_##name(journal_t *j) \
अणु \
	(j)->j_superblock->s_feature_incompat |= \
		cpu_to_be32(JBD2_FEATURE_INCOMPAT_##flagname); \
पूर्ण \
अटल अंतरभूत व्योम jbd2_clear_feature_##name(journal_t *j) \
अणु \
	(j)->j_superblock->s_feature_incompat &= \
		~cpu_to_be32(JBD2_FEATURE_INCOMPAT_##flagname); \
पूर्ण

JBD2_FEATURE_COMPAT_FUNCS(checksum,		CHECKSUM)

JBD2_FEATURE_INCOMPAT_FUNCS(revoke,		REVOKE)
JBD2_FEATURE_INCOMPAT_FUNCS(64bit,		64BIT)
JBD2_FEATURE_INCOMPAT_FUNCS(async_commit,	ASYNC_COMMIT)
JBD2_FEATURE_INCOMPAT_FUNCS(csum2,		CSUM_V2)
JBD2_FEATURE_INCOMPAT_FUNCS(csum3,		CSUM_V3)
JBD2_FEATURE_INCOMPAT_FUNCS(fast_commit,	FAST_COMMIT)

/*
 * Journal flag definitions
 */
#घोषणा JBD2_UNMOUNT	0x001	/* Journal thपढ़ो is being destroyed */
#घोषणा JBD2_ABORT	0x002	/* Journaling has been पातed क्रम errors. */
#घोषणा JBD2_ACK_ERR	0x004	/* The त्रुटि_सं in the sb has been acked */
#घोषणा JBD2_FLUSHED	0x008	/* The journal superblock has been flushed */
#घोषणा JBD2_LOADED	0x010	/* The journal superblock has been loaded */
#घोषणा JBD2_BARRIER	0x020	/* Use IDE barriers */
#घोषणा JBD2_ABORT_ON_SYNCDATA_ERR	0x040	/* Abort the journal on file
						 * data ग_लिखो error in ordered
						 * mode */
#घोषणा JBD2_FAST_COMMIT_ONGOING	0x100	/* Fast commit is ongoing */
#घोषणा JBD2_FULL_COMMIT_ONGOING	0x200	/* Full commit is ongoing */

/*
 * Function declarations क्रम the journaling transaction and buffer
 * management
 */

/* Filing buffers */
बाह्य व्योम jbd2_journal_unfile_buffer(journal_t *, काष्ठा journal_head *);
बाह्य bool __jbd2_journal_refile_buffer(काष्ठा journal_head *);
बाह्य व्योम jbd2_journal_refile_buffer(journal_t *, काष्ठा journal_head *);
बाह्य व्योम __jbd2_journal_file_buffer(काष्ठा journal_head *, transaction_t *, पूर्णांक);
बाह्य व्योम __journal_मुक्त_buffer(काष्ठा journal_head *bh);
बाह्य व्योम jbd2_journal_file_buffer(काष्ठा journal_head *, transaction_t *, पूर्णांक);
बाह्य व्योम __journal_clean_data_list(transaction_t *transaction);
अटल अंतरभूत व्योम jbd2_file_log_bh(काष्ठा list_head *head, काष्ठा buffer_head *bh)
अणु
	list_add_tail(&bh->b_assoc_buffers, head);
पूर्ण
अटल अंतरभूत व्योम jbd2_unfile_log_bh(काष्ठा buffer_head *bh)
अणु
	list_del_init(&bh->b_assoc_buffers);
पूर्ण

/* Log buffer allocation */
काष्ठा buffer_head *jbd2_journal_get_descriptor_buffer(transaction_t *, पूर्णांक);
व्योम jbd2_descriptor_block_csum_set(journal_t *, काष्ठा buffer_head *);
पूर्णांक jbd2_journal_next_log_block(journal_t *, अचिन्हित दीर्घ दीर्घ *);
पूर्णांक jbd2_journal_get_log_tail(journal_t *journal, tid_t *tid,
			      अचिन्हित दीर्घ *block);
पूर्णांक __jbd2_update_log_tail(journal_t *journal, tid_t tid, अचिन्हित दीर्घ block);
व्योम jbd2_update_log_tail(journal_t *journal, tid_t tid, अचिन्हित दीर्घ block);

/* Commit management */
बाह्य व्योम jbd2_journal_commit_transaction(journal_t *);

/* Checkpoपूर्णांक list management */
व्योम __jbd2_journal_clean_checkpoपूर्णांक_list(journal_t *journal, bool destroy);
पूर्णांक __jbd2_journal_हटाओ_checkpoपूर्णांक(काष्ठा journal_head *);
व्योम jbd2_journal_destroy_checkpoपूर्णांक(journal_t *journal);
व्योम __jbd2_journal_insert_checkpoपूर्णांक(काष्ठा journal_head *, transaction_t *);


/*
 * Triggers
 */

काष्ठा jbd2_buffer_trigger_type अणु
	/*
	 * Fired a the moment data to ग_लिखो to the journal are known to be
	 * stable - so either at the moment b_frozen_data is created or just
	 * beक्रमe a buffer is written to the journal.  mapped_data is a mapped
	 * buffer that is the frozen data क्रम commit.
	 */
	व्योम (*t_frozen)(काष्ठा jbd2_buffer_trigger_type *type,
			 काष्ठा buffer_head *bh, व्योम *mapped_data,
			 माप_प्रकार size);

	/*
	 * Fired during journal पात क्रम dirty buffers that will not be
	 * committed.
	 */
	व्योम (*t_पात)(काष्ठा jbd2_buffer_trigger_type *type,
			काष्ठा buffer_head *bh);
पूर्ण;

बाह्य व्योम jbd2_buffer_frozen_trigger(काष्ठा journal_head *jh,
				       व्योम *mapped_data,
				       काष्ठा jbd2_buffer_trigger_type *triggers);
बाह्य व्योम jbd2_buffer_पात_trigger(काष्ठा journal_head *jh,
				      काष्ठा jbd2_buffer_trigger_type *triggers);

/* Buffer IO */
बाह्य पूर्णांक jbd2_journal_ग_लिखो_metadata_buffer(transaction_t *transaction,
					      काष्ठा journal_head *jh_in,
					      काष्ठा buffer_head **bh_out,
					      sector_t blocknr);

/* Transaction locking */
बाह्य व्योम		__रुको_on_journal (journal_t *);

/* Transaction cache support */
बाह्य व्योम jbd2_journal_destroy_transaction_cache(व्योम);
बाह्य पूर्णांक __init jbd2_journal_init_transaction_cache(व्योम);
बाह्य व्योम jbd2_journal_मुक्त_transaction(transaction_t *);

/*
 * Journal locking.
 *
 * We need to lock the journal during transaction state changes so that nobody
 * ever tries to take a handle on the running transaction जबतक we are in the
 * middle of moving it to the commit phase.  j_state_lock करोes this.
 *
 * Note that the locking is completely पूर्णांकerrupt unsafe.  We never touch
 * journal काष्ठाures from पूर्णांकerrupts.
 */

अटल अंतरभूत handle_t *journal_current_handle(व्योम)
अणु
	वापस current->journal_info;
पूर्ण

/* The journaling code user पूर्णांकerface:
 *
 * Create and destroy handles
 * Register buffer modअगरications against the current transaction.
 */

बाह्य handle_t *jbd2_journal_start(journal_t *, पूर्णांक nblocks);
बाह्य handle_t *jbd2__journal_start(journal_t *, पूर्णांक blocks, पूर्णांक rsv_blocks,
				     पूर्णांक revoke_records, gfp_t gfp_mask,
				     अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक line_no);
बाह्य पूर्णांक	 jbd2_journal_restart(handle_t *, पूर्णांक nblocks);
बाह्य पूर्णांक	 jbd2__journal_restart(handle_t *, पूर्णांक nblocks,
				       पूर्णांक revoke_records, gfp_t gfp_mask);
बाह्य पूर्णांक	 jbd2_journal_start_reserved(handle_t *handle,
				अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक line_no);
बाह्य व्योम	 jbd2_journal_मुक्त_reserved(handle_t *handle);
बाह्य पूर्णांक	 jbd2_journal_extend(handle_t *handle, पूर्णांक nblocks,
				     पूर्णांक revoke_records);
बाह्य पूर्णांक	 jbd2_journal_get_ग_लिखो_access(handle_t *, काष्ठा buffer_head *);
बाह्य पूर्णांक	 jbd2_journal_get_create_access (handle_t *, काष्ठा buffer_head *);
बाह्य पूर्णांक	 jbd2_journal_get_unकरो_access(handle_t *, काष्ठा buffer_head *);
व्योम		 jbd2_journal_set_triggers(काष्ठा buffer_head *,
					   काष्ठा jbd2_buffer_trigger_type *type);
बाह्य पूर्णांक	 jbd2_journal_dirty_metadata (handle_t *, काष्ठा buffer_head *);
बाह्य पूर्णांक	 jbd2_journal_क्रमget (handle_t *, काष्ठा buffer_head *);
बाह्य पूर्णांक	 jbd2_journal_invalidatepage(journal_t *,
				काष्ठा page *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
बाह्य पूर्णांक	 jbd2_journal_try_to_मुक्त_buffers(journal_t *journal, काष्ठा page *page);
बाह्य पूर्णांक	 jbd2_journal_stop(handle_t *);
बाह्य पूर्णांक	 jbd2_journal_flush (journal_t *);
बाह्य व्योम	 jbd2_journal_lock_updates (journal_t *);
बाह्य व्योम	 jbd2_journal_unlock_updates (journal_t *);

बाह्य journal_t * jbd2_journal_init_dev(काष्ठा block_device *bdev,
				काष्ठा block_device *fs_dev,
				अचिन्हित दीर्घ दीर्घ start, पूर्णांक len, पूर्णांक bsize);
बाह्य journal_t * jbd2_journal_init_inode (काष्ठा inode *);
बाह्य पूर्णांक	   jbd2_journal_update_क्रमmat (journal_t *);
बाह्य पूर्णांक	   jbd2_journal_check_used_features
		   (journal_t *, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य पूर्णांक	   jbd2_journal_check_available_features
		   (journal_t *, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य पूर्णांक	   jbd2_journal_set_features
		   (journal_t *, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम	   jbd2_journal_clear_features
		   (journal_t *, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य पूर्णांक	   jbd2_journal_load       (journal_t *journal);
बाह्य पूर्णांक	   jbd2_journal_destroy    (journal_t *);
बाह्य पूर्णांक	   jbd2_journal_recover    (journal_t *journal);
बाह्य पूर्णांक	   jbd2_journal_wipe       (journal_t *, पूर्णांक);
बाह्य पूर्णांक	   jbd2_journal_skip_recovery	(journal_t *);
बाह्य व्योम	   jbd2_journal_update_sb_त्रुटि_सं(journal_t *);
बाह्य पूर्णांक	   jbd2_journal_update_sb_log_tail	(journal_t *, tid_t,
				अचिन्हित दीर्घ, पूर्णांक);
बाह्य व्योम	   jbd2_journal_पात      (journal_t *, पूर्णांक);
बाह्य पूर्णांक	   jbd2_journal_त्रुटि_सं      (journal_t *);
बाह्य व्योम	   jbd2_journal_ack_err    (journal_t *);
बाह्य पूर्णांक	   jbd2_journal_clear_err  (journal_t *);
बाह्य पूर्णांक	   jbd2_journal_bmap(journal_t *, अचिन्हित दीर्घ, अचिन्हित दीर्घ दीर्घ *);
बाह्य पूर्णांक	   jbd2_journal_क्रमce_commit(journal_t *);
बाह्य पूर्णांक	   jbd2_journal_क्रमce_commit_nested(journal_t *);
बाह्य पूर्णांक	   jbd2_journal_inode_ranged_ग_लिखो(handle_t *handle,
			काष्ठा jbd2_inode *inode, loff_t start_byte,
			loff_t length);
बाह्य पूर्णांक	   jbd2_journal_inode_ranged_रुको(handle_t *handle,
			काष्ठा jbd2_inode *inode, loff_t start_byte,
			loff_t length);
बाह्य पूर्णांक	   jbd2_journal_submit_inode_data_buffers(
			काष्ठा jbd2_inode *jinode);
बाह्य पूर्णांक	   jbd2_journal_finish_inode_data_buffers(
			काष्ठा jbd2_inode *jinode);
बाह्य पूर्णांक	   jbd2_journal_begin_ordered_truncate(journal_t *journal,
				काष्ठा jbd2_inode *inode, loff_t new_size);
बाह्य व्योम	   jbd2_journal_init_jbd_inode(काष्ठा jbd2_inode *jinode, काष्ठा inode *inode);
बाह्य व्योम	   jbd2_journal_release_jbd_inode(journal_t *journal, काष्ठा jbd2_inode *jinode);

/*
 * journal_head management
 */
काष्ठा journal_head *jbd2_journal_add_journal_head(काष्ठा buffer_head *bh);
काष्ठा journal_head *jbd2_journal_grab_journal_head(काष्ठा buffer_head *bh);
व्योम jbd2_journal_put_journal_head(काष्ठा journal_head *jh);

/*
 * handle management
 */
बाह्य काष्ठा kmem_cache *jbd2_handle_cache;

अटल अंतरभूत handle_t *jbd2_alloc_handle(gfp_t gfp_flags)
अणु
	वापस kmem_cache_zalloc(jbd2_handle_cache, gfp_flags);
पूर्ण

अटल अंतरभूत व्योम jbd2_मुक्त_handle(handle_t *handle)
अणु
	kmem_cache_मुक्त(jbd2_handle_cache, handle);
पूर्ण

/*
 * jbd2_inode management (optional, क्रम those file प्रणालीs that want to use
 * dynamically allocated jbd2_inode काष्ठाures)
 */
बाह्य काष्ठा kmem_cache *jbd2_inode_cache;

अटल अंतरभूत काष्ठा jbd2_inode *jbd2_alloc_inode(gfp_t gfp_flags)
अणु
	वापस kmem_cache_alloc(jbd2_inode_cache, gfp_flags);
पूर्ण

अटल अंतरभूत व्योम jbd2_मुक्त_inode(काष्ठा jbd2_inode *jinode)
अणु
	kmem_cache_मुक्त(jbd2_inode_cache, jinode);
पूर्ण

/* Primary revoke support */
#घोषणा JOURNAL_REVOKE_DEFAULT_HASH 256
बाह्य पूर्णांक	   jbd2_journal_init_revoke(journal_t *, पूर्णांक);
बाह्य व्योम	   jbd2_journal_destroy_revoke_record_cache(व्योम);
बाह्य व्योम	   jbd2_journal_destroy_revoke_table_cache(व्योम);
बाह्य पूर्णांक __init jbd2_journal_init_revoke_record_cache(व्योम);
बाह्य पूर्णांक __init jbd2_journal_init_revoke_table_cache(व्योम);

बाह्य व्योम	   jbd2_journal_destroy_revoke(journal_t *);
बाह्य पूर्णांक	   jbd2_journal_revoke (handle_t *, अचिन्हित दीर्घ दीर्घ, काष्ठा buffer_head *);
बाह्य पूर्णांक	   jbd2_journal_cancel_revoke(handle_t *, काष्ठा journal_head *);
बाह्य व्योम	   jbd2_journal_ग_लिखो_revoke_records(transaction_t *transaction,
						     काष्ठा list_head *log_bufs);

/* Recovery revoke support */
बाह्य पूर्णांक	jbd2_journal_set_revoke(journal_t *, अचिन्हित दीर्घ दीर्घ, tid_t);
बाह्य पूर्णांक	jbd2_journal_test_revoke(journal_t *, अचिन्हित दीर्घ दीर्घ, tid_t);
बाह्य व्योम	jbd2_journal_clear_revoke(journal_t *);
बाह्य व्योम	jbd2_journal_चयन_revoke_table(journal_t *journal);
बाह्य व्योम	jbd2_clear_buffer_revoked_flags(journal_t *journal);

/*
 * The log thपढ़ो user पूर्णांकerface:
 *
 * Request space in the current transaction, and क्रमce transaction commit
 * transitions on demand.
 */

पूर्णांक jbd2_log_start_commit(journal_t *journal, tid_t tid);
पूर्णांक __jbd2_log_start_commit(journal_t *journal, tid_t tid);
पूर्णांक jbd2_journal_start_commit(journal_t *journal, tid_t *tid);
पूर्णांक jbd2_log_रुको_commit(journal_t *journal, tid_t tid);
पूर्णांक jbd2_transaction_committed(journal_t *journal, tid_t tid);
पूर्णांक jbd2_complete_transaction(journal_t *journal, tid_t tid);
पूर्णांक jbd2_log_करो_checkpoपूर्णांक(journal_t *journal);
पूर्णांक jbd2_trans_will_send_data_barrier(journal_t *journal, tid_t tid);

व्योम __jbd2_log_रुको_क्रम_space(journal_t *journal);
बाह्य व्योम __jbd2_journal_drop_transaction(journal_t *, transaction_t *);
बाह्य पूर्णांक jbd2_cleanup_journal_tail(journal_t *);

/* Fast commit related APIs */
पूर्णांक jbd2_fc_begin_commit(journal_t *journal, tid_t tid);
पूर्णांक jbd2_fc_end_commit(journal_t *journal);
पूर्णांक jbd2_fc_end_commit_fallback(journal_t *journal);
पूर्णांक jbd2_fc_get_buf(journal_t *journal, काष्ठा buffer_head **bh_out);
पूर्णांक jbd2_submit_inode_data(काष्ठा jbd2_inode *jinode);
पूर्णांक jbd2_रुको_inode_data(journal_t *journal, काष्ठा jbd2_inode *jinode);
पूर्णांक jbd2_fc_रुको_bufs(journal_t *journal, पूर्णांक num_blks);
पूर्णांक jbd2_fc_release_bufs(journal_t *journal);

अटल अंतरभूत पूर्णांक jbd2_journal_get_max_txn_bufs(journal_t *journal)
अणु
	वापस (journal->j_total_len - journal->j_fc_wbufsize) / 4;
पूर्ण

/*
 * is_journal_पात
 *
 * Simple test wrapper function to test the JBD2_ABORT state flag.  This
 * bit, when set, indicates that we have had a fatal error somewhere,
 * either inside the journaling layer or indicated to us by the client
 * (eg. ext3), and that we and should not commit any further
 * transactions.
 */

अटल अंतरभूत पूर्णांक is_journal_पातed(journal_t *journal)
अणु
	वापस journal->j_flags & JBD2_ABORT;
पूर्ण

अटल अंतरभूत पूर्णांक is_handle_पातed(handle_t *handle)
अणु
	अगर (handle->h_पातed || !handle->h_transaction)
		वापस 1;
	वापस is_journal_पातed(handle->h_transaction->t_journal);
पूर्ण

अटल अंतरभूत व्योम jbd2_journal_पात_handle(handle_t *handle)
अणु
	handle->h_पातed = 1;
पूर्ण

#पूर्ण_अगर /* __KERNEL__   */

/* Comparison functions क्रम transaction IDs: perक्रमm comparisons using
 * modulo arithmetic so that they work over sequence number wraps. */

अटल अंतरभूत पूर्णांक tid_gt(tid_t x, tid_t y)
अणु
	पूर्णांक dअगरference = (x - y);
	वापस (dअगरference > 0);
पूर्ण

अटल अंतरभूत पूर्णांक tid_geq(tid_t x, tid_t y)
अणु
	पूर्णांक dअगरference = (x - y);
	वापस (dअगरference >= 0);
पूर्ण

बाह्य पूर्णांक jbd2_journal_blocks_per_page(काष्ठा inode *inode);
बाह्य माप_प्रकार journal_tag_bytes(journal_t *journal);

अटल अंतरभूत bool jbd2_journal_has_csum_v2or3_feature(journal_t *j)
अणु
	वापस jbd2_has_feature_csum2(j) || jbd2_has_feature_csum3(j);
पूर्ण

अटल अंतरभूत पूर्णांक jbd2_journal_has_csum_v2or3(journal_t *journal)
अणु
	WARN_ON_ONCE(jbd2_journal_has_csum_v2or3_feature(journal) &&
		     journal->j_chksum_driver == शून्य);

	वापस journal->j_chksum_driver != शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक jbd2_journal_get_num_fc_blks(journal_superblock_t *jsb)
अणु
	पूर्णांक num_fc_blocks = be32_to_cpu(jsb->s_num_fc_blks);

	वापस num_fc_blocks ? num_fc_blocks : JBD2_DEFAULT_FAST_COMMIT_BLOCKS;
पूर्ण

/*
 * Return number of मुक्त blocks in the log. Must be called under j_state_lock.
 */
अटल अंतरभूत अचिन्हित दीर्घ jbd2_log_space_left(journal_t *journal)
अणु
	/* Allow क्रम rounding errors */
	दीर्घ मुक्त = journal->j_मुक्त - 32;

	अगर (journal->j_committing_transaction) अणु
		मुक्त -= atomic_पढ़ो(&journal->
                        j_committing_transaction->t_outstanding_credits);
	पूर्ण
	वापस max_t(दीर्घ, मुक्त, 0);
पूर्ण

/*
 * Definitions which augment the buffer_head layer
 */

/* journaling buffer types */
#घोषणा BJ_None		0	/* Not journaled */
#घोषणा BJ_Metadata	1	/* Normal journaled metadata */
#घोषणा BJ_Forget	2	/* Buffer superseded by this transaction */
#घोषणा BJ_Shaकरोw	3	/* Buffer contents being shaकरोwed to the log */
#घोषणा BJ_Reserved	4	/* Buffer is reserved क्रम access by journal */
#घोषणा BJ_Types	5

बाह्य पूर्णांक jbd_blocks_per_page(काष्ठा inode *inode);

/* JBD uses a CRC32 checksum */
#घोषणा JBD_MAX_CHECKSUM_SIZE 4

अटल अंतरभूत u32 jbd2_chksum(journal_t *journal, u32 crc,
			      स्थिर व्योम *address, अचिन्हित पूर्णांक length)
अणु
	काष्ठा अणु
		काष्ठा shash_desc shash;
		अक्षर ctx[JBD_MAX_CHECKSUM_SIZE];
	पूर्ण desc;
	पूर्णांक err;

	BUG_ON(crypto_shash_descsize(journal->j_chksum_driver) >
		JBD_MAX_CHECKSUM_SIZE);

	desc.shash.tfm = journal->j_chksum_driver;
	*(u32 *)desc.ctx = crc;

	err = crypto_shash_update(&desc.shash, address, length);
	BUG_ON(err);

	वापस *(u32 *)desc.ctx;
पूर्ण

/* Return most recent uncommitted transaction */
अटल अंतरभूत tid_t  jbd2_get_latest_transaction(journal_t *journal)
अणु
	tid_t tid;

	पढ़ो_lock(&journal->j_state_lock);
	tid = journal->j_commit_request;
	अगर (journal->j_running_transaction)
		tid = journal->j_running_transaction->t_tid;
	पढ़ो_unlock(&journal->j_state_lock);
	वापस tid;
पूर्ण

अटल अंतरभूत पूर्णांक jbd2_handle_buffer_credits(handle_t *handle)
अणु
	journal_t *journal;

	अगर (!handle->h_reserved)
		journal = handle->h_transaction->t_journal;
	अन्यथा
		journal = handle->h_journal;

	वापस handle->h_total_credits -
		DIV_ROUND_UP(handle->h_revoke_credits_requested,
			     journal->j_revoke_records_per_block);
पूर्ण

#अगर_घोषित __KERNEL__

#घोषणा buffer_trace_init(bh)	करो अणुपूर्ण जबतक (0)
#घोषणा prपूर्णांक_buffer_fields(bh)	करो अणुपूर्ण जबतक (0)
#घोषणा prपूर्णांक_buffer_trace(bh)	करो अणुपूर्ण जबतक (0)
#घोषणा BUFFER_TRACE(bh, info)	करो अणुपूर्ण जबतक (0)
#घोषणा BUFFER_TRACE2(bh, bh2, info)	करो अणुपूर्ण जबतक (0)
#घोषणा JBUFFER_TRACE(jh, info)	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर	/* __KERNEL__ */

#घोषणा EFSBADCRC	EBADMSG		/* Bad CRC detected */
#घोषणा EFSCORRUPTED	EUCLEAN		/* Fileप्रणाली is corrupted */

#पूर्ण_अगर	/* _LINUX_JBD2_H */
