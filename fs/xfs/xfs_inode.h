<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_INODE_H__
#घोषणा	__XFS_INODE_H__

#समावेश "xfs_inode_buf.h"
#समावेश "xfs_inode_fork.h"

/*
 * Kernel only inode definitions
 */
काष्ठा xfs_dinode;
काष्ठा xfs_inode;
काष्ठा xfs_buf;
काष्ठा xfs_bmbt_irec;
काष्ठा xfs_inode_log_item;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_dquot;

प्रकार काष्ठा xfs_inode अणु
	/* Inode linking and identअगरication inक्रमmation. */
	काष्ठा xfs_mount	*i_mount;	/* fs mount काष्ठा ptr */
	काष्ठा xfs_dquot	*i_udquot;	/* user dquot */
	काष्ठा xfs_dquot	*i_gdquot;	/* group dquot */
	काष्ठा xfs_dquot	*i_pdquot;	/* project dquot */

	/* Inode location stuff */
	xfs_ino_t		i_ino;		/* inode number (agno/agino)*/
	काष्ठा xfs_imap		i_imap;		/* location क्रम xfs_imap() */

	/* Extent inक्रमmation. */
	काष्ठा xfs_अगरork	*i_afp;		/* attribute विभाजन poपूर्णांकer */
	काष्ठा xfs_अगरork	*i_cowfp;	/* copy on ग_लिखो extents */
	काष्ठा xfs_अगरork	i_df;		/* data विभाजन */

	/* Transaction and locking inक्रमmation. */
	काष्ठा xfs_inode_log_item *i_itemp;	/* logging inक्रमmation */
	mrlock_t		i_lock;		/* inode lock */
	mrlock_t		i_mmaplock;	/* inode mmap IO lock */
	atomic_t		i_pincount;	/* inode pin count */

	/*
	 * Bitsets of inode metadata that have been checked and/or are sick.
	 * Callers must hold i_flags_lock beक्रमe accessing this field.
	 */
	uपूर्णांक16_t		i_checked;
	uपूर्णांक16_t		i_sick;

	spinlock_t		i_flags_lock;	/* inode i_flags lock */
	/* Miscellaneous state. */
	अचिन्हित दीर्घ		i_flags;	/* see defined flags below */
	uपूर्णांक64_t		i_delayed_blks;	/* count of delay alloc blks */
	xfs_fमाप_प्रकार		i_disk_size;	/* number of bytes in file */
	xfs_rfsblock_t		i_nblocks;	/* # of direct & btree blocks */
	prid_t			i_projid;	/* owner's project id */
	xfs_extlen_t		i_extsize;	/* basic/minimum extent size */
	/* cowextsize is only used क्रम v3 inodes, flushiter क्रम v1/2 */
	जोड़ अणु
		xfs_extlen_t	i_cowextsize;	/* basic cow extent size */
		uपूर्णांक16_t	i_flushiter;	/* incremented on flush */
	पूर्ण;
	uपूर्णांक8_t			i_विभाजनoff;	/* attr विभाजन offset >> 3 */
	uपूर्णांक16_t		i_dअगरlags;	/* XFS_DIFLAG_... */
	uपूर्णांक64_t		i_dअगरlags2;	/* XFS_DIFLAG2_... */
	काष्ठा बारpec64	i_crसमय;	/* समय created */

	/* VFS inode */
	काष्ठा inode		i_vnode;	/* embedded VFS inode */

	/* pending io completions */
	spinlock_t		i_ioend_lock;
	काष्ठा work_काष्ठा	i_ioend_work;
	काष्ठा list_head	i_ioend_list;
पूर्ण xfs_inode_t;

/* Convert from vfs inode to xfs inode */
अटल अंतरभूत काष्ठा xfs_inode *XFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा xfs_inode, i_vnode);
पूर्ण

/* convert from xfs inode to vfs inode */
अटल अंतरभूत काष्ठा inode *VFS_I(काष्ठा xfs_inode *ip)
अणु
	वापस &ip->i_vnode;
पूर्ण

/*
 * For regular files we only update the on-disk filesize when actually
 * writing data back to disk.  Until then only the copy in the VFS inode
 * is uptodate.
 */
अटल अंतरभूत xfs_fमाप_प्रकार XFS_ISIZE(काष्ठा xfs_inode *ip)
अणु
	अगर (S_ISREG(VFS_I(ip)->i_mode))
		वापस i_size_पढ़ो(VFS_I(ip));
	वापस ip->i_disk_size;
पूर्ण

/*
 * If this I/O goes past the on-disk inode size update it unless it would
 * be past the current in-core inode size.
 */
अटल अंतरभूत xfs_fमाप_प्रकार
xfs_new_eof(काष्ठा xfs_inode *ip, xfs_fमाप_प्रकार new_size)
अणु
	xfs_fमाप_प्रकार i_size = i_size_पढ़ो(VFS_I(ip));

	अगर (new_size > i_size || new_size < 0)
		new_size = i_size;
	वापस new_size > ip->i_disk_size ? new_size : 0;
पूर्ण

/*
 * i_flags helper functions
 */
अटल अंतरभूत व्योम
__xfs_अगरlags_set(xfs_inode_t *ip, अचिन्हित लघु flags)
अणु
	ip->i_flags |= flags;
पूर्ण

अटल अंतरभूत व्योम
xfs_अगरlags_set(xfs_inode_t *ip, अचिन्हित लघु flags)
अणु
	spin_lock(&ip->i_flags_lock);
	__xfs_अगरlags_set(ip, flags);
	spin_unlock(&ip->i_flags_lock);
पूर्ण

अटल अंतरभूत व्योम
xfs_अगरlags_clear(xfs_inode_t *ip, अचिन्हित लघु flags)
अणु
	spin_lock(&ip->i_flags_lock);
	ip->i_flags &= ~flags;
	spin_unlock(&ip->i_flags_lock);
पूर्ण

अटल अंतरभूत पूर्णांक
__xfs_अगरlags_test(xfs_inode_t *ip, अचिन्हित लघु flags)
अणु
	वापस (ip->i_flags & flags);
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_अगरlags_test(xfs_inode_t *ip, अचिन्हित लघु flags)
अणु
	पूर्णांक ret;
	spin_lock(&ip->i_flags_lock);
	ret = __xfs_अगरlags_test(ip, flags);
	spin_unlock(&ip->i_flags_lock);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_अगरlags_test_and_clear(xfs_inode_t *ip, अचिन्हित लघु flags)
अणु
	पूर्णांक ret;

	spin_lock(&ip->i_flags_lock);
	ret = ip->i_flags & flags;
	अगर (ret)
		ip->i_flags &= ~flags;
	spin_unlock(&ip->i_flags_lock);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_अगरlags_test_and_set(xfs_inode_t *ip, अचिन्हित लघु flags)
अणु
	पूर्णांक ret;

	spin_lock(&ip->i_flags_lock);
	ret = ip->i_flags & flags;
	अगर (!ret)
		ip->i_flags |= flags;
	spin_unlock(&ip->i_flags_lock);
	वापस ret;
पूर्ण

अटल अंतरभूत prid_t
xfs_get_initial_prid(काष्ठा xfs_inode *dp)
अणु
	अगर (dp->i_dअगरlags & XFS_DIFLAG_PROJINHERIT)
		वापस dp->i_projid;

	वापस XFS_PROJID_DEFAULT;
पूर्ण

अटल अंतरभूत bool xfs_is_reflink_inode(काष्ठा xfs_inode *ip)
अणु
	वापस ip->i_dअगरlags2 & XFS_DIFLAG2_REFLINK;
पूर्ण

अटल अंतरभूत bool xfs_is_metadata_inode(काष्ठा xfs_inode *ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;

	वापस ip == mp->m_rbmip || ip == mp->m_rsumip ||
		xfs_is_quota_inode(&mp->m_sb, ip->i_ino);
पूर्ण

/*
 * Check अगर an inode has any data in the COW विभाजन.  This might be often false
 * even क्रम inodes with the reflink flag when there is no pending COW operation.
 */
अटल अंतरभूत bool xfs_inode_has_cow_data(काष्ठा xfs_inode *ip)
अणु
	वापस ip->i_cowfp && ip->i_cowfp->अगर_bytes;
पूर्ण

अटल अंतरभूत bool xfs_inode_has_bigसमय(काष्ठा xfs_inode *ip)
अणु
	वापस ip->i_dअगरlags2 & XFS_DIFLAG2_BIGTIME;
पूर्ण

/*
 * Return the buftarg used क्रम data allocations on a given inode.
 */
#घोषणा xfs_inode_buftarg(ip) \
	(XFS_IS_REALTIME_INODE(ip) ? \
		(ip)->i_mount->m_rtdev_targp : (ip)->i_mount->m_ddev_targp)

/*
 * In-core inode flags.
 */
#घोषणा XFS_IRECLAIM		(1 << 0) /* started reclaiming this inode */
#घोषणा XFS_ISTALE		(1 << 1) /* inode has been staled */
#घोषणा XFS_IRECLAIMABLE	(1 << 2) /* inode can be reclaimed */
#घोषणा __XFS_INEW_BIT		3	 /* inode has just been allocated */
#घोषणा XFS_INEW		(1 << __XFS_INEW_BIT)
#घोषणा XFS_IPRESERVE_DM_FIELDS	(1 << 4) /* has legacy DMAPI fields set */
#घोषणा XFS_ITRUNCATED		(1 << 5) /* truncated करोwn so flush-on-बंद */
#घोषणा XFS_IसूचीTY_RELEASE	(1 << 6) /* dirty release alपढ़ोy seen */
#घोषणा XFS_IFLUSHING		(1 << 7) /* inode is being flushed */
#घोषणा __XFS_IPINNED_BIT	8	 /* wakeup key क्रम zero pin count */
#घोषणा XFS_IPINNED		(1 << __XFS_IPINNED_BIT)
#घोषणा XFS_Iखातापूर्णBLOCKS		(1 << 9) /* has the pपुनः_स्मृतिblocks tag set */
/*
 * If this unlinked inode is in the middle of recovery, करोn't let drop_inode
 * truncate and मुक्त the inode.  This can happen अगर we iget the inode during
 * log recovery to replay a bmap operation on the inode.
 */
#घोषणा XFS_IRECOVERY		(1 << 11)
#घोषणा XFS_ICOWBLOCKS		(1 << 12)/* has the cowblocks tag set */

/*
 * Per-lअगरeसमय flags need to be reset when re-using a reclaimable inode during
 * inode lookup. This prevents unपूर्णांकended behaviour on the new inode from
 * ocurring.
 */
#घोषणा XFS_IRECLAIM_RESET_FLAGS	\
	(XFS_IRECLAIMABLE | XFS_IRECLAIM | \
	 XFS_IसूचीTY_RELEASE | XFS_ITRUNCATED)

/*
 * Flags क्रम inode locking.
 * Bit ranges:	1<<1  - 1<<16-1 -- iolock/ilock modes (bitfield)
 *		1<<16 - 1<<32-1 -- lockdep annotation (पूर्णांकegers)
 */
#घोषणा	XFS_IOLOCK_EXCL		(1<<0)
#घोषणा	XFS_IOLOCK_SHARED	(1<<1)
#घोषणा	XFS_ILOCK_EXCL		(1<<2)
#घोषणा	XFS_ILOCK_SHARED	(1<<3)
#घोषणा	XFS_MMAPLOCK_EXCL	(1<<4)
#घोषणा	XFS_MMAPLOCK_SHARED	(1<<5)

#घोषणा XFS_LOCK_MASK		(XFS_IOLOCK_EXCL | XFS_IOLOCK_SHARED \
				| XFS_ILOCK_EXCL | XFS_ILOCK_SHARED \
				| XFS_MMAPLOCK_EXCL | XFS_MMAPLOCK_SHARED)

#घोषणा XFS_LOCK_FLAGS \
	अणु XFS_IOLOCK_EXCL,	"IOLOCK_EXCL" पूर्ण, \
	अणु XFS_IOLOCK_SHARED,	"IOLOCK_SHARED" पूर्ण, \
	अणु XFS_ILOCK_EXCL,	"ILOCK_EXCL" पूर्ण, \
	अणु XFS_ILOCK_SHARED,	"ILOCK_SHARED" पूर्ण, \
	अणु XFS_MMAPLOCK_EXCL,	"MMAPLOCK_EXCL" पूर्ण, \
	अणु XFS_MMAPLOCK_SHARED,	"MMAPLOCK_SHARED" पूर्ण


/*
 * Flags क्रम lockdep annotations.
 *
 * XFS_LOCK_PARENT - क्रम directory operations that require locking a
 * parent directory inode and a child entry inode. IOLOCK requires nesting,
 * MMAPLOCK करोes not support this class, ILOCK requires a single subclass
 * to dअगरferentiate parent from child.
 *
 * XFS_LOCK_RTBITMAP/XFS_LOCK_RTSUM - the realसमय device biपंचांगap and summary
 * inodes करो not participate in the normal lock order, and thus have their
 * own subclasses.
 *
 * XFS_LOCK_INUMORDER - क्रम locking several inodes at the some समय
 * with xfs_lock_inodes().  This flag is used as the starting subclass
 * and each subsequent lock acquired will increment the subclass by one.
 * However, MAX_LOCKDEP_SUBCLASSES == 8, which means we are greatly
 * limited to the subclasses we can represent via nesting. We need at least
 * 5 inodes nest depth क्रम the ILOCK through नाम, and we also have to support
 * XFS_ILOCK_PARENT, which gives 6 subclasses. Then we have XFS_ILOCK_RTBITMAP
 * and XFS_ILOCK_RTSUM, which are another 2 unique subclasses, so that's all
 * 8 subclasses supported by lockdep.
 *
 * This also means we have to number the sub-classes in the lowest bits of
 * the mask we keep, and we have to ensure we never exceed 3 bits of lockdep
 * mask and we can't use bit-masking to build the subclasses. What a mess.
 *
 * Bit layout:
 *
 * Bit		Lock Region
 * 16-19	XFS_IOLOCK_SHIFT dependencies
 * 20-23	XFS_MMAPLOCK_SHIFT dependencies
 * 24-31	XFS_ILOCK_SHIFT dependencies
 *
 * IOLOCK values
 *
 * 0-3		subclass value
 * 4-7		unused
 *
 * MMAPLOCK values
 *
 * 0-3		subclass value
 * 4-7		unused
 *
 * ILOCK values
 * 0-4		subclass values
 * 5		PARENT subclass (not nestable)
 * 6		RTBITMAP subclass (not nestable)
 * 7		RTSUM subclass (not nestable)
 * 
 */
#घोषणा XFS_IOLOCK_SHIFT		16
#घोषणा XFS_IOLOCK_MAX_SUBCLASS		3
#घोषणा XFS_IOLOCK_DEP_MASK		0x000f0000

#घोषणा XFS_MMAPLOCK_SHIFT		20
#घोषणा XFS_MMAPLOCK_NUMORDER		0
#घोषणा XFS_MMAPLOCK_MAX_SUBCLASS	3
#घोषणा XFS_MMAPLOCK_DEP_MASK		0x00f00000

#घोषणा XFS_ILOCK_SHIFT			24
#घोषणा XFS_ILOCK_PARENT_VAL		5
#घोषणा XFS_ILOCK_MAX_SUBCLASS		(XFS_ILOCK_PARENT_VAL - 1)
#घोषणा XFS_ILOCK_RTBITMAP_VAL		6
#घोषणा XFS_ILOCK_RTSUM_VAL		7
#घोषणा XFS_ILOCK_DEP_MASK		0xff000000
#घोषणा	XFS_ILOCK_PARENT		(XFS_ILOCK_PARENT_VAL << XFS_ILOCK_SHIFT)
#घोषणा	XFS_ILOCK_RTBITMAP		(XFS_ILOCK_RTBITMAP_VAL << XFS_ILOCK_SHIFT)
#घोषणा	XFS_ILOCK_RTSUM			(XFS_ILOCK_RTSUM_VAL << XFS_ILOCK_SHIFT)

#घोषणा XFS_LOCK_SUBCLASS_MASK	(XFS_IOLOCK_DEP_MASK | \
				 XFS_MMAPLOCK_DEP_MASK | \
				 XFS_ILOCK_DEP_MASK)

#घोषणा XFS_IOLOCK_DEP(flags)	(((flags) & XFS_IOLOCK_DEP_MASK) \
					>> XFS_IOLOCK_SHIFT)
#घोषणा XFS_MMAPLOCK_DEP(flags)	(((flags) & XFS_MMAPLOCK_DEP_MASK) \
					>> XFS_MMAPLOCK_SHIFT)
#घोषणा XFS_ILOCK_DEP(flags)	(((flags) & XFS_ILOCK_DEP_MASK) \
					>> XFS_ILOCK_SHIFT)

/*
 * Layouts are broken in the BREAK_WRITE हाल to ensure that
 * layout-holders करो not collide with local ग_लिखोs. Additionally,
 * layouts are broken in the BREAK_UNMAP हाल to make sure the
 * layout-holder has a consistent view of the file's extent map. While
 * BREAK_WRITE अवरोधs can be satisfied by recalling FL_LAYOUT leases,
 * BREAK_UNMAP अवरोधs additionally require रुकोing क्रम busy dax-pages to
 * go idle.
 */
क्रमागत layout_अवरोध_reason अणु
        BREAK_WRITE,
        BREAK_UNMAP,
पूर्ण;

/*
 * For multiple groups support: अगर S_ISGID bit is set in the parent
 * directory, group of new file is set to that of the parent, and
 * new subdirectory माला_लो S_ISGID bit from parent.
 */
#घोषणा XFS_INHERIT_GID(pip)	\
	(((pip)->i_mount->m_flags & XFS_MOUNT_GRPID) || \
	 (VFS_I(pip)->i_mode & S_ISGID))

पूर्णांक		xfs_release(काष्ठा xfs_inode *ip);
व्योम		xfs_inactive(काष्ठा xfs_inode *ip);
पूर्णांक		xfs_lookup(काष्ठा xfs_inode *dp, काष्ठा xfs_name *name,
			   काष्ठा xfs_inode **ipp, काष्ठा xfs_name *ci_name);
पूर्णांक		xfs_create(काष्ठा user_namespace *mnt_userns,
			   काष्ठा xfs_inode *dp, काष्ठा xfs_name *name,
			   umode_t mode, dev_t rdev, bool need_xattr,
			   काष्ठा xfs_inode **ipp);
पूर्णांक		xfs_create_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
			   काष्ठा xfs_inode *dp, umode_t mode,
			   काष्ठा xfs_inode **ipp);
पूर्णांक		xfs_हटाओ(काष्ठा xfs_inode *dp, काष्ठा xfs_name *name,
			   काष्ठा xfs_inode *ip);
पूर्णांक		xfs_link(काष्ठा xfs_inode *tdp, काष्ठा xfs_inode *sip,
			 काष्ठा xfs_name *target_name);
पूर्णांक		xfs_नाम(काष्ठा user_namespace *mnt_userns,
			   काष्ठा xfs_inode *src_dp, काष्ठा xfs_name *src_name,
			   काष्ठा xfs_inode *src_ip, काष्ठा xfs_inode *target_dp,
			   काष्ठा xfs_name *target_name,
			   काष्ठा xfs_inode *target_ip, अचिन्हित पूर्णांक flags);

व्योम		xfs_ilock(xfs_inode_t *, uपूर्णांक);
पूर्णांक		xfs_ilock_noरुको(xfs_inode_t *, uपूर्णांक);
व्योम		xfs_iunlock(xfs_inode_t *, uपूर्णांक);
व्योम		xfs_ilock_demote(xfs_inode_t *, uपूर्णांक);
पूर्णांक		xfs_isilocked(xfs_inode_t *, uपूर्णांक);
uपूर्णांक		xfs_ilock_data_map_shared(काष्ठा xfs_inode *);
uपूर्णांक		xfs_ilock_attr_map_shared(काष्ठा xfs_inode *);

uपूर्णांक		xfs_ip2xflags(काष्ठा xfs_inode *);
पूर्णांक		xfs_अगरree(काष्ठा xfs_trans *, काष्ठा xfs_inode *);
पूर्णांक		xfs_itruncate_extents_flags(काष्ठा xfs_trans **,
				काष्ठा xfs_inode *, पूर्णांक, xfs_fमाप_प्रकार, पूर्णांक);
व्योम		xfs_iext_पुनः_स्मृति(xfs_inode_t *, पूर्णांक, पूर्णांक);

पूर्णांक		xfs_log_क्रमce_inode(काष्ठा xfs_inode *ip);
व्योम		xfs_iunpin_रुको(xfs_inode_t *);
#घोषणा xfs_ipincount(ip)	((अचिन्हित पूर्णांक) atomic_पढ़ो(&ip->i_pincount))

पूर्णांक		xfs_अगरlush_cluster(काष्ठा xfs_buf *);
व्योम		xfs_lock_two_inodes(काष्ठा xfs_inode *ip0, uपूर्णांक ip0_mode,
				काष्ठा xfs_inode *ip1, uपूर्णांक ip1_mode);

xfs_extlen_t	xfs_get_extsz_hपूर्णांक(काष्ठा xfs_inode *ip);
xfs_extlen_t	xfs_get_cowextsz_hपूर्णांक(काष्ठा xfs_inode *ip);

पूर्णांक		xfs_dir_ialloc(काष्ठा user_namespace *mnt_userns,
			       काष्ठा xfs_trans **tpp, काष्ठा xfs_inode *dp,
			       umode_t mode, xfs_nlink_t nlink, dev_t dev,
			       prid_t prid, bool need_xattr,
			       काष्ठा xfs_inode **ipp);

अटल अंतरभूत पूर्णांक
xfs_itruncate_extents(
	काष्ठा xfs_trans	**tpp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	xfs_fमाप_प्रकार		new_size)
अणु
	वापस xfs_itruncate_extents_flags(tpp, ip, whichविभाजन, new_size, 0);
पूर्ण

/* from xfs_file.c */
क्रमागत xfs_pपुनः_स्मृति_flags अणु
	XFS_PREALLOC_SET	= (1 << 1),
	XFS_PREALLOC_CLEAR	= (1 << 2),
	XFS_PREALLOC_SYNC	= (1 << 3),
	XFS_PREALLOC_INVISIBLE	= (1 << 4),
पूर्ण;

पूर्णांक	xfs_update_pपुनः_स्मृति_flags(काष्ठा xfs_inode *ip,
				  क्रमागत xfs_pपुनः_स्मृति_flags flags);
पूर्णांक	xfs_अवरोध_layouts(काष्ठा inode *inode, uपूर्णांक *iolock,
		क्रमागत layout_अवरोध_reason reason);

/* from xfs_iops.c */
बाह्य व्योम xfs_setup_inode(काष्ठा xfs_inode *ip);
बाह्य व्योम xfs_setup_iops(काष्ठा xfs_inode *ip);
बाह्य व्योम xfs_dअगरlags_to_अगरlags(काष्ठा xfs_inode *ip, bool init);

/*
 * When setting up a newly allocated inode, we need to call
 * xfs_finish_inode_setup() once the inode is fully instantiated at
 * the VFS level to prevent the rest of the world seeing the inode
 * beक्रमe we've completed instantiation. Otherwise we can करो it
 * the moment the inode lookup is complete.
 */
अटल अंतरभूत व्योम xfs_finish_inode_setup(काष्ठा xfs_inode *ip)
अणु
	xfs_अगरlags_clear(ip, XFS_INEW);
	barrier();
	unlock_new_inode(VFS_I(ip));
	wake_up_bit(&ip->i_flags, __XFS_INEW_BIT);
पूर्ण

अटल अंतरभूत व्योम xfs_setup_existing_inode(काष्ठा xfs_inode *ip)
अणु
	xfs_setup_inode(ip);
	xfs_setup_iops(ip);
	xfs_finish_inode_setup(ip);
पूर्ण

व्योम xfs_irele(काष्ठा xfs_inode *ip);

बाह्य काष्ठा kmem_zone	*xfs_inode_zone;

/* The शेष CoW extent size hपूर्णांक. */
#घोषणा XFS_DEFAULT_COWEXTSZ_HINT 32

पूर्णांक xfs_iunlink_init(काष्ठा xfs_perag *pag);
व्योम xfs_iunlink_destroy(काष्ठा xfs_perag *pag);

व्योम xfs_end_io(काष्ठा work_काष्ठा *work);

पूर्णांक xfs_ilock2_io_mmap(काष्ठा xfs_inode *ip1, काष्ठा xfs_inode *ip2);
व्योम xfs_iunlock2_io_mmap(काष्ठा xfs_inode *ip1, काष्ठा xfs_inode *ip2);

#पूर्ण_अगर	/* __XFS_INODE_H__ */
