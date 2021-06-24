<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * inode.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_INODE_H
#घोषणा OCFS2_INODE_H

#समावेश "extent_map.h"

/* OCFS2 Inode Private Data */
काष्ठा ocfs2_inode_info
अणु
	u64			ip_blkno;

	काष्ठा ocfs2_lock_res		ip_rw_lockres;
	काष्ठा ocfs2_lock_res		ip_inode_lockres;
	काष्ठा ocfs2_lock_res		ip_खोलो_lockres;

	/* protects allocation changes on this inode. */
	काष्ठा rw_semaphore		ip_alloc_sem;

	/* protects extended attribute changes on this inode */
	काष्ठा rw_semaphore		ip_xattr_sem;

	/* These fields are रक्षित by ip_lock */
	spinlock_t			ip_lock;
	u32				ip_खोलो_count;
	काष्ठा list_head		ip_io_markers;
	u32				ip_clusters;

	u16				ip_dyn_features;
	काष्ठा mutex			ip_io_mutex;
	u32				ip_flags; /* see below */
	u32				ip_attr; /* inode attributes */

	/* Record unwritten extents during direct io. */
	काष्ठा list_head		ip_unwritten_list;

	/* रक्षित by recovery_lock. */
	काष्ठा inode			*ip_next_orphan;

	काष्ठा ocfs2_caching_info	ip_metadata_cache;
	काष्ठा ocfs2_extent_map		ip_extent_map;
	काष्ठा inode			vfs_inode;
	काष्ठा jbd2_inode		ip_jinode;

	u32				ip_dir_start_lookup;

	/* Only valid अगर the inode is the dir. */
	u32				ip_last_used_slot;
	u64				ip_last_used_group;
	u32				ip_dir_lock_gen;

	काष्ठा ocfs2_alloc_reservation	ip_la_data_resv;

	/*
	 * Transactions that contain inode's metadata needed to complete
	 * fsync and fdatasync, respectively.
	 */
	tid_t i_sync_tid;
	tid_t i_datasync_tid;

	काष्ठा dquot *i_dquot[MAXQUOTAS];
पूर्ण;

/*
 * Flags क्रम the ip_flags field
 */
/* System file inodes  */
#घोषणा OCFS2_INODE_SYSTEM_खाता		0x00000001
#घोषणा OCFS2_INODE_JOURNAL		0x00000002
#घोषणा OCFS2_INODE_BITMAP		0x00000004
/* This inode has been wiped from disk */
#घोषणा OCFS2_INODE_DELETED		0x00000008
/* Has the inode been orphaned on another node?
 *
 * This hपूर्णांकs to ocfs2_drop_inode that it should clear i_nlink beक्रमe
 * continuing.
 *
 * We *only* set this on unlink vote from another node. If the inode
 * was locally orphaned, then we're sure of the state and don't need
 * to twiddle i_nlink later - it's either zero or not depending on
 * whether our unlink succeeded. Otherwise we got this from a node
 * whose पूर्णांकention was to orphan the inode, however he may have
 * crashed, failed etc, so we let ocfs2_drop_inode zero the value and
 * rely on ocfs2_delete_inode to sort things out under the proper
 * cluster locks.
 */
#घोषणा OCFS2_INODE_MAYBE_ORPHANED	0x00000010
/* Does someone have the file खोलो O_सूचीECT */
#घोषणा OCFS2_INODE_OPEN_सूचीECT		0x00000020
/* Tell the inode wipe code it's not in orphan dir */
#घोषणा OCFS2_INODE_SKIP_ORPHAN_सूची     0x00000040
/* Entry in orphan dir with 'dio-' prefix */
#घोषणा OCFS2_INODE_DIO_ORPHAN_ENTRY	0x00000080

अटल अंतरभूत काष्ठा ocfs2_inode_info *OCFS2_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा ocfs2_inode_info, vfs_inode);
पूर्ण

#घोषणा INODE_JOURNAL(i) (OCFS2_I(i)->ip_flags & OCFS2_INODE_JOURNAL)
#घोषणा SET_INODE_JOURNAL(i) (OCFS2_I(i)->ip_flags |= OCFS2_INODE_JOURNAL)

बाह्य स्थिर काष्ठा address_space_operations ocfs2_aops;
बाह्य स्थिर काष्ठा ocfs2_caching_operations ocfs2_inode_caching_ops;

अटल अंतरभूत काष्ठा ocfs2_caching_info *INODE_CACHE(काष्ठा inode *inode)
अणु
	वापस &OCFS2_I(inode)->ip_metadata_cache;
पूर्ण

व्योम ocfs2_evict_inode(काष्ठा inode *inode);
पूर्णांक ocfs2_drop_inode(काष्ठा inode *inode);

/* Flags क्रम ocfs2_iget() */
#घोषणा OCFS2_FI_FLAG_SYSखाता		0x1
#घोषणा OCFS2_FI_FLAG_ORPHAN_RECOVERY	0x2
#घोषणा OCFS2_FI_FLAG_खाताCHECK_CHK	0x4
#घोषणा OCFS2_FI_FLAG_खाताCHECK_FIX	0x8

काष्ठा inode *ocfs2_ilookup(काष्ठा super_block *sb, u64 ख_पूर्णf);
काष्ठा inode *ocfs2_iget(काष्ठा ocfs2_super *osb, u64 ख_पूर्णf, अचिन्हित flags,
			 पूर्णांक sysfile_type);
पूर्णांक ocfs2_inode_revalidate(काष्ठा dentry *dentry);
व्योम ocfs2_populate_inode(काष्ठा inode *inode, काष्ठा ocfs2_dinode *fe,
			  पूर्णांक create_ino);
व्योम ocfs2_sync_blockdev(काष्ठा super_block *sb);
व्योम ocfs2_refresh_inode(काष्ठा inode *inode,
			 काष्ठा ocfs2_dinode *fe);
पूर्णांक ocfs2_mark_inode_dirty(handle_t *handle,
			   काष्ठा inode *inode,
			   काष्ठा buffer_head *bh);

व्योम ocfs2_set_inode_flags(काष्ठा inode *inode);
व्योम ocfs2_get_inode_flags(काष्ठा ocfs2_inode_info *oi);

अटल अंतरभूत blkcnt_t ocfs2_inode_sector_count(काष्ठा inode *inode)
अणु
	पूर्णांक c_to_s_bits = OCFS2_SB(inode->i_sb)->s_clustersize_bits - 9;

	वापस (blkcnt_t)OCFS2_I(inode)->ip_clusters << c_to_s_bits;
पूर्ण

/* Validate that a bh contains a valid inode */
पूर्णांक ocfs2_validate_inode_block(काष्ठा super_block *sb,
			       काष्ठा buffer_head *bh);
/*
 * Read an inode block पूर्णांकo *bh.  If *bh is शून्य, a bh will be allocated.
 * This is a cached पढ़ो.  The inode will be validated with
 * ocfs2_validate_inode_block().
 */
पूर्णांक ocfs2_पढ़ो_inode_block(काष्ठा inode *inode, काष्ठा buffer_head **bh);
/* The same, but can be passed OCFS2_BH_* flags */
पूर्णांक ocfs2_पढ़ो_inode_block_full(काष्ठा inode *inode, काष्ठा buffer_head **bh,
				पूर्णांक flags);

अटल अंतरभूत काष्ठा ocfs2_inode_info *cache_info_to_inode(काष्ठा ocfs2_caching_info *ci)
अणु
	वापस container_of(ci, काष्ठा ocfs2_inode_info, ip_metadata_cache);
पूर्ण

/* Does this inode have the reflink flag set? */
अटल अंतरभूत bool ocfs2_is_refcount_inode(काष्ठा inode *inode)
अणु
	वापस (OCFS2_I(inode)->ip_dyn_features & OCFS2_HAS_REFCOUNT_FL);
पूर्ण

#पूर्ण_अगर /* OCFS2_INODE_H */
