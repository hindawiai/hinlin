<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_LOG_RECOVER_H__
#घोषणा __XFS_LOG_RECOVER_H__

/*
 * Each log item type (XFS_LI_*) माला_लो its own xlog_recover_item_ops to
 * define how recovery should work क्रम that type of log item.
 */
काष्ठा xlog_recover_item;

/* Sorting hat क्रम log items as they're पढ़ो in. */
क्रमागत xlog_recover_reorder अणु
	XLOG_REORDER_BUFFER_LIST,
	XLOG_REORDER_ITEM_LIST,
	XLOG_REORDER_INODE_BUFFER_LIST,
	XLOG_REORDER_CANCEL_LIST,
पूर्ण;

काष्ठा xlog_recover_item_ops अणु
	uपूर्णांक16_t	item_type;	/* XFS_LI_* type code. */

	/*
	 * Help sort recovered log items पूर्णांकo the order required to replay them
	 * correctly.  Log item types that always use XLOG_REORDER_ITEM_LIST करो
	 * not have to supply a function here.  See the comment preceding
	 * xlog_recover_reorder_trans क्रम more details about what the वापस
	 * values mean.
	 */
	क्रमागत xlog_recover_reorder (*reorder)(काष्ठा xlog_recover_item *item);

	/* Start पढ़ोahead क्रम pass2, अगर provided. */
	व्योम (*ra_pass2)(काष्ठा xlog *log, काष्ठा xlog_recover_item *item);

	/* Do whatever work we need to करो क्रम pass1, अगर provided. */
	पूर्णांक (*commit_pass1)(काष्ठा xlog *log, काष्ठा xlog_recover_item *item);

	/*
	 * This function should करो whatever work is needed क्रम pass2 of log
	 * recovery, अगर provided.
	 *
	 * If the recovered item is an पूर्णांकent item, this function should parse
	 * the recovered item to स्थिरruct an in-core log पूर्णांकent item and
	 * insert it पूर्णांकo the AIL.  The in-core log पूर्णांकent item should have 1
	 * refcount so that the item is मुक्तd either (a) when we commit the
	 * recovered log item क्रम the पूर्णांकent-करोne item; (b) replay the work and
	 * log a new पूर्णांकent-करोne item; or (c) recovery fails and we have to
	 * पात.
	 *
	 * If the recovered item is an पूर्णांकent-करोne item, this function should
	 * parse the recovered item to find the id of the corresponding पूर्णांकent
	 * log item.  Next, it should find the in-core log पूर्णांकent item in the
	 * AIL and release it.
	 */
	पूर्णांक (*commit_pass2)(काष्ठा xlog *log, काष्ठा list_head *buffer_list,
			    काष्ठा xlog_recover_item *item, xfs_lsn_t lsn);
पूर्ण;

बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_icreate_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_buf_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_inode_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_dquot_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_quotaoff_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_bui_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_bud_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_efi_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_efd_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_rui_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_rud_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_cui_item_ops;
बाह्य स्थिर काष्ठा xlog_recover_item_ops xlog_cud_item_ops;

/*
 * Macros, काष्ठाures, prototypes क्रम पूर्णांकernal log manager use.
 */

#घोषणा XLOG_RHASH_BITS  4
#घोषणा XLOG_RHASH_SIZE	16
#घोषणा XLOG_RHASH_SHIFT 2
#घोषणा XLOG_RHASH(tid)	\
	((((uपूर्णांक32_t)tid)>>XLOG_RHASH_SHIFT) & (XLOG_RHASH_SIZE-1))

#घोषणा XLOG_MAX_REGIONS_IN_ITEM   (XFS_MAX_BLOCKSIZE / XFS_BLF_CHUNK / 2 + 1)


/*
 * item headers are in ri_buf[0].  Additional buffers follow.
 */
काष्ठा xlog_recover_item अणु
	काष्ठा list_head	ri_list;
	पूर्णांक			ri_cnt;	/* count of regions found */
	पूर्णांक			ri_total;	/* total regions */
	काष्ठा xfs_log_iovec	*ri_buf;	/* ptr to regions buffer */
	स्थिर काष्ठा xlog_recover_item_ops *ri_ops;
पूर्ण;

काष्ठा xlog_recover अणु
	काष्ठा hlist_node	r_list;
	xlog_tid_t		r_log_tid;	/* log's transaction id */
	xfs_trans_header_t	r_theader;	/* trans header क्रम partial */
	पूर्णांक			r_state;	/* not needed */
	xfs_lsn_t		r_lsn;		/* xact lsn */
	काष्ठा list_head	r_itemq;	/* q क्रम items */
पूर्ण;

#घोषणा ITEM_TYPE(i)	(*(अचिन्हित लघु *)(i)->ri_buf[0].i_addr)

/*
 * This is the number of entries in the l_buf_cancel_table used during
 * recovery.
 */
#घोषणा	XLOG_BC_TABLE_SIZE	64

#घोषणा	XLOG_RECOVER_CRCPASS	0
#घोषणा	XLOG_RECOVER_PASS1	1
#घोषणा	XLOG_RECOVER_PASS2	2

व्योम xlog_buf_पढ़ोahead(काष्ठा xlog *log, xfs_daddr_t blkno, uपूर्णांक len,
		स्थिर काष्ठा xfs_buf_ops *ops);
bool xlog_is_buffer_cancelled(काष्ठा xlog *log, xfs_daddr_t blkno, uपूर्णांक len);

व्योम xlog_recover_release_पूर्णांकent(काष्ठा xlog *log, अचिन्हित लघु पूर्णांकent_type,
		uपूर्णांक64_t पूर्णांकent_id);

#पूर्ण_अगर	/* __XFS_LOG_RECOVER_H__ */
