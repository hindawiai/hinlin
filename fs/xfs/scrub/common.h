<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_COMMON_H__
#घोषणा __XFS_SCRUB_COMMON_H__

/*
 * We /could/ terminate a scrub/repair operation early.  If we're not
 * in a good place to जारी (fatal संकेत, etc.) then bail out.
 * Note that we're careful not to make any judgements about *error.
 */
अटल अंतरभूत bool
xchk_should_terminate(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			*error)
अणु
	/*
	 * If preemption is disabled, we need to yield to the scheduler every
	 * few seconds so that we करोn't run afoul of the soft lockup watchकरोg
	 * or RCU stall detector.
	 */
	cond_resched();

	अगर (fatal_संकेत_pending(current)) अणु
		अगर (*error == 0)
			*error = -EAGAIN;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक xchk_trans_alloc(काष्ठा xfs_scrub *sc, uपूर्णांक resblks);
bool xchk_process_error(काष्ठा xfs_scrub *sc, xfs_agnumber_t agno,
		xfs_agblock_t bno, पूर्णांक *error);
bool xchk_fblock_process_error(काष्ठा xfs_scrub *sc, पूर्णांक whichविभाजन,
		xfs_fileoff_t offset, पूर्णांक *error);

bool xchk_xref_process_error(काष्ठा xfs_scrub *sc,
		xfs_agnumber_t agno, xfs_agblock_t bno, पूर्णांक *error);
bool xchk_fblock_xref_process_error(काष्ठा xfs_scrub *sc,
		पूर्णांक whichविभाजन, xfs_fileoff_t offset, पूर्णांक *error);

व्योम xchk_block_set_preen(काष्ठा xfs_scrub *sc,
		काष्ठा xfs_buf *bp);
व्योम xchk_ino_set_preen(काष्ठा xfs_scrub *sc, xfs_ino_t ino);

व्योम xchk_set_corrupt(काष्ठा xfs_scrub *sc);
व्योम xchk_block_set_corrupt(काष्ठा xfs_scrub *sc,
		काष्ठा xfs_buf *bp);
व्योम xchk_ino_set_corrupt(काष्ठा xfs_scrub *sc, xfs_ino_t ino);
व्योम xchk_fblock_set_corrupt(काष्ठा xfs_scrub *sc, पूर्णांक whichविभाजन,
		xfs_fileoff_t offset);

व्योम xchk_block_xref_set_corrupt(काष्ठा xfs_scrub *sc,
		काष्ठा xfs_buf *bp);
व्योम xchk_ino_xref_set_corrupt(काष्ठा xfs_scrub *sc,
		xfs_ino_t ino);
व्योम xchk_fblock_xref_set_corrupt(काष्ठा xfs_scrub *sc,
		पूर्णांक whichविभाजन, xfs_fileoff_t offset);

व्योम xchk_ino_set_warning(काष्ठा xfs_scrub *sc, xfs_ino_t ino);
व्योम xchk_fblock_set_warning(काष्ठा xfs_scrub *sc, पूर्णांक whichविभाजन,
		xfs_fileoff_t offset);

व्योम xchk_set_incomplete(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_checkpoपूर्णांक_log(काष्ठा xfs_mount *mp);

/* Are we set up क्रम a cross-referencing check? */
bool xchk_should_check_xref(काष्ठा xfs_scrub *sc, पूर्णांक *error,
			   काष्ठा xfs_btree_cur **curpp);

/* Setup functions */
पूर्णांक xchk_setup_fs(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_ag_allocbt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_ag_iallocbt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_ag_rmapbt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_ag_refcountbt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_inode(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_inode_bmap(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_inode_bmap_data(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_directory(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_xattr(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_symlink(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_parent(काष्ठा xfs_scrub *sc);
#अगर_घोषित CONFIG_XFS_RT
पूर्णांक xchk_setup_rt(काष्ठा xfs_scrub *sc);
#अन्यथा
अटल अंतरभूत पूर्णांक
xchk_setup_rt(काष्ठा xfs_scrub *sc)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFS_QUOTA
पूर्णांक xchk_setup_quota(काष्ठा xfs_scrub *sc);
#अन्यथा
अटल अंतरभूत पूर्णांक
xchk_setup_quota(काष्ठा xfs_scrub *sc)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर
पूर्णांक xchk_setup_fscounters(काष्ठा xfs_scrub *sc);

व्योम xchk_ag_मुक्त(काष्ठा xfs_scrub *sc, काष्ठा xchk_ag *sa);
पूर्णांक xchk_ag_init(काष्ठा xfs_scrub *sc, xfs_agnumber_t agno,
		काष्ठा xchk_ag *sa);
व्योम xchk_perag_get(काष्ठा xfs_mount *mp, काष्ठा xchk_ag *sa);
पूर्णांक xchk_ag_पढ़ो_headers(काष्ठा xfs_scrub *sc, xfs_agnumber_t agno,
		काष्ठा xchk_ag *sa);
व्योम xchk_ag_btcur_मुक्त(काष्ठा xchk_ag *sa);
व्योम xchk_ag_btcur_init(काष्ठा xfs_scrub *sc, काष्ठा xchk_ag *sa);
पूर्णांक xchk_count_rmap_ownedby_ag(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur,
		स्थिर काष्ठा xfs_owner_info *oinfo, xfs_filblks_t *blocks);

पूर्णांक xchk_setup_ag_btree(काष्ठा xfs_scrub *sc, bool क्रमce_log);
पूर्णांक xchk_get_inode(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_setup_inode_contents(काष्ठा xfs_scrub *sc, अचिन्हित पूर्णांक resblks);
व्योम xchk_buffer_recheck(काष्ठा xfs_scrub *sc, काष्ठा xfs_buf *bp);

/*
 * Don't bother cross-referencing अगर we alपढ़ोy found corruption or cross
 * referencing discrepancies.
 */
अटल अंतरभूत bool xchk_skip_xref(काष्ठा xfs_scrub_metadata *sm)
अणु
	वापस sm->sm_flags & (XFS_SCRUB_OFLAG_CORRUPT |
			       XFS_SCRUB_OFLAG_XCORRUPT);
पूर्ण

पूर्णांक xchk_metadata_inode_विभाजनs(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_ilock_inverted(काष्ठा xfs_inode *ip, uपूर्णांक lock_mode);
व्योम xchk_stop_reaping(काष्ठा xfs_scrub *sc);
व्योम xchk_start_reaping(काष्ठा xfs_scrub *sc);

#पूर्ण_अगर	/* __XFS_SCRUB_COMMON_H__ */
