<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित XFS_SYNC_H
#घोषणा XFS_SYNC_H 1

काष्ठा xfs_mount;
काष्ठा xfs_perag;

काष्ठा xfs_eofblocks अणु
	__u32		eof_flags;
	kuid_t		eof_uid;
	kgid_t		eof_gid;
	prid_t		eof_prid;
	__u64		eof_min_file_size;
पूर्ण;

/*
 * tags क्रम inode radix tree
 */
#घोषणा XFS_ICI_NO_TAG		(-1)	/* special flag क्रम an untagged lookup
					   in xfs_inode_walk */
#घोषणा XFS_ICI_RECLAIM_TAG	0	/* inode is to be reclaimed */
/* Inode has speculative pपुनः_स्मृतिations (posteof or cow) to clean. */
#घोषणा XFS_ICI_BLOCKGC_TAG	1

/*
 * Flags क्रम xfs_iget()
 */
#घोषणा XFS_IGET_CREATE		0x1
#घोषणा XFS_IGET_UNTRUSTED	0x2
#घोषणा XFS_IGET_DONTCACHE	0x4
#घोषणा XFS_IGET_INCORE		0x8	/* करोn't पढ़ो from disk or reinit */

/*
 * flags क्रम AG inode iterator
 */
#घोषणा XFS_INODE_WALK_INEW_WAIT	0x1	/* रुको on new inodes */

पूर्णांक xfs_iget(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp, xfs_ino_t ino,
	     uपूर्णांक flags, uपूर्णांक lock_flags, xfs_inode_t **ipp);

/* recovery needs direct inode allocation capability */
काष्ठा xfs_inode * xfs_inode_alloc(काष्ठा xfs_mount *mp, xfs_ino_t ino);
व्योम xfs_inode_मुक्त(काष्ठा xfs_inode *ip);

व्योम xfs_reclaim_worker(काष्ठा work_काष्ठा *work);

व्योम xfs_reclaim_inodes(काष्ठा xfs_mount *mp);
पूर्णांक xfs_reclaim_inodes_count(काष्ठा xfs_mount *mp);
दीर्घ xfs_reclaim_inodes_nr(काष्ठा xfs_mount *mp, पूर्णांक nr_to_scan);

व्योम xfs_inode_set_reclaim_tag(काष्ठा xfs_inode *ip);

पूर्णांक xfs_blockgc_मुक्त_dquots(काष्ठा xfs_mount *mp, काष्ठा xfs_dquot *udqp,
		काष्ठा xfs_dquot *gdqp, काष्ठा xfs_dquot *pdqp,
		अचिन्हित पूर्णांक eof_flags);
पूर्णांक xfs_blockgc_मुक्त_quota(काष्ठा xfs_inode *ip, अचिन्हित पूर्णांक eof_flags);
पूर्णांक xfs_blockgc_मुक्त_space(काष्ठा xfs_mount *mp, काष्ठा xfs_eofblocks *eofb);

व्योम xfs_inode_set_eofblocks_tag(काष्ठा xfs_inode *ip);
व्योम xfs_inode_clear_eofblocks_tag(काष्ठा xfs_inode *ip);

व्योम xfs_inode_set_cowblocks_tag(काष्ठा xfs_inode *ip);
व्योम xfs_inode_clear_cowblocks_tag(काष्ठा xfs_inode *ip);

व्योम xfs_blockgc_worker(काष्ठा work_काष्ठा *work);

पूर्णांक xfs_inode_walk(काष्ठा xfs_mount *mp, पूर्णांक iter_flags,
	पूर्णांक (*execute)(काष्ठा xfs_inode *ip, व्योम *args),
	व्योम *args, पूर्णांक tag);

पूर्णांक xfs_icache_inode_is_allocated(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
				  xfs_ino_t ino, bool *inuse);

व्योम xfs_blockgc_stop(काष्ठा xfs_mount *mp);
व्योम xfs_blockgc_start(काष्ठा xfs_mount *mp);

#पूर्ण_अगर
