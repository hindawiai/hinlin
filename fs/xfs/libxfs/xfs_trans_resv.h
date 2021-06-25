<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_TRANS_RESV_H__
#घोषणा	__XFS_TRANS_RESV_H__

काष्ठा xfs_mount;

/*
 * काष्ठाure क्रम मुख्यtaining pre-calculated transaction reservations.
 */
काष्ठा xfs_trans_res अणु
	uपूर्णांक	tr_logres;	/* log space unit in bytes per log ticket */
	पूर्णांक	tr_logcount;	/* number of log operations per log ticket */
	पूर्णांक	tr_logflags;	/* log flags, currently only used क्रम indicating
				 * a reservation request is permanent or not */
पूर्ण;

काष्ठा xfs_trans_resv अणु
	काष्ठा xfs_trans_res	tr_ग_लिखो;	/* extent alloc trans */
	काष्ठा xfs_trans_res	tr_itruncate;	/* truncate trans */
	काष्ठा xfs_trans_res	tr_नाम;	/* नाम trans */
	काष्ठा xfs_trans_res	tr_link;	/* link trans */
	काष्ठा xfs_trans_res	tr_हटाओ;	/* unlink trans */
	काष्ठा xfs_trans_res	tr_symlink;	/* symlink trans */
	काष्ठा xfs_trans_res	tr_create;	/* create trans */
	काष्ठा xfs_trans_res	tr_create_क्षणिक_ख; /* create O_TMPखाता trans */
	काष्ठा xfs_trans_res	tr_सूची_गढ़ो;	/* सूची_गढ़ो trans */
	काष्ठा xfs_trans_res	tr_अगरree;	/* inode मुक्त trans */
	काष्ठा xfs_trans_res	tr_ichange;	/* inode update trans */
	काष्ठा xfs_trans_res	tr_growdata;	/* fs data section grow trans */
	काष्ठा xfs_trans_res	tr_addaविभाजन;	/* add inode attr विभाजन trans */
	काष्ठा xfs_trans_res	tr_ग_लिखोid;	/* ग_लिखो setuid/setgid file */
	काष्ठा xfs_trans_res	tr_attrinval;	/* attr विभाजन buffer
						 * invalidation */
	काष्ठा xfs_trans_res	tr_attrseपंचांग;	/* set/create an attribute at
						 * mount समय */
	काष्ठा xfs_trans_res	tr_attrsetrt;	/* set/create an attribute at
						 * runसमय */
	काष्ठा xfs_trans_res	tr_attrrm;	/* हटाओ an attribute */
	काष्ठा xfs_trans_res	tr_clearagi;	/* clear agi unlinked bucket */
	काष्ठा xfs_trans_res	tr_growrtalloc;	/* grow realसमय allocations */
	काष्ठा xfs_trans_res	tr_growrtzero;	/* grow realसमय zeroing */
	काष्ठा xfs_trans_res	tr_growrtमुक्त;	/* grow realसमय मुक्तing */
	काष्ठा xfs_trans_res	tr_qm_setqlim;	/* adjust quota limits */
	काष्ठा xfs_trans_res	tr_qm_dqalloc;	/* allocate quota on disk */
	काष्ठा xfs_trans_res	tr_qm_quotaoff;	/* turn quota off */
	काष्ठा xfs_trans_res	tr_qm_equotaoff;/* end of turn quota off */
	काष्ठा xfs_trans_res	tr_sb;		/* modअगरy superblock */
	काष्ठा xfs_trans_res	tr_fsyncts;	/* update बारtamps on fsync */
पूर्ण;

/* लघुhand way of accessing reservation काष्ठाure */
#घोषणा M_RES(mp)	(&(mp)->m_resv)

/*
 * Per-directory log reservation क्रम any directory change.
 * dir blocks: (1 btree block per level + data block + मुक्त block) * dblock size
 * bmap btree: (levels + 2) * max depth * block size
 * v2 directory blocks can be fragmented below the dirblksize करोwn to the fsb
 * size, so account क्रम that in the DAENTER macros.
 */
#घोषणा	XFS_सूचीOP_LOG_RES(mp)	\
	(XFS_FSB_TO_B(mp, XFS_DAENTER_BLOCKS(mp, XFS_DATA_FORK)) + \
	 (XFS_FSB_TO_B(mp, XFS_DAENTER_BMAPS(mp, XFS_DATA_FORK) + 1)))
#घोषणा	XFS_सूचीOP_LOG_COUNT(mp)	\
	(XFS_DAENTER_BLOCKS(mp, XFS_DATA_FORK) + \
	 XFS_DAENTER_BMAPS(mp, XFS_DATA_FORK) + 1)

/*
 * Various log count values.
 */
#घोषणा	XFS_DEFAULT_LOG_COUNT		1
#घोषणा	XFS_DEFAULT_PERM_LOG_COUNT	2
#घोषणा	XFS_ITRUNCATE_LOG_COUNT		2
#घोषणा	XFS_ITRUNCATE_LOG_COUNT_REFLINK	8
#घोषणा XFS_INACTIVE_LOG_COUNT		2
#घोषणा	XFS_CREATE_LOG_COUNT		2
#घोषणा	XFS_CREATE_TMPखाता_LOG_COUNT	2
#घोषणा	XFS_MKसूची_LOG_COUNT		3
#घोषणा	XFS_SYMLINK_LOG_COUNT		3
#घोषणा	XFS_REMOVE_LOG_COUNT		2
#घोषणा	XFS_LINK_LOG_COUNT		2
#घोषणा	XFS_RENAME_LOG_COUNT		2
#घोषणा	XFS_WRITE_LOG_COUNT		2
#घोषणा	XFS_WRITE_LOG_COUNT_REFLINK	8
#घोषणा	XFS_ADDAFORK_LOG_COUNT		2
#घोषणा	XFS_ATTRINVAL_LOG_COUNT		1
#घोषणा	XFS_ATTRSET_LOG_COUNT		3
#घोषणा	XFS_ATTRRM_LOG_COUNT		3

व्योम xfs_trans_resv_calc(काष्ठा xfs_mount *mp, काष्ठा xfs_trans_resv *resp);
uपूर्णांक xfs_allocमुक्त_log_count(काष्ठा xfs_mount *mp, uपूर्णांक num_ops);

#पूर्ण_अगर	/* __XFS_TRANS_RESV_H__ */
