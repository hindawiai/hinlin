<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * inode.h - Defines क्रम inode काष्ठाures NTFS Linux kernel driver. Part of
 *	     the Linux-NTFS project.
 *
 * Copyright (c) 2001-2007 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#अगर_अघोषित _LINUX_NTFS_INODE_H
#घोषणा _LINUX_NTFS_INODE_H

#समावेश <linux/atomic.h>

#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>

#समावेश "layout.h"
#समावेश "volume.h"
#समावेश "types.h"
#समावेश "runlist.h"
#समावेश "debug.h"

प्रकार काष्ठा _ntfs_inode ntfs_inode;

/*
 * The NTFS in-memory inode काष्ठाure. It is just used as an extension to the
 * fields alपढ़ोy provided in the VFS inode.
 */
काष्ठा _ntfs_inode अणु
	rwlock_t size_lock;	/* Lock serializing access to inode sizes. */
	s64 initialized_size;	/* Copy from the attribute record. */
	s64 allocated_size;	/* Copy from the attribute record. */
	अचिन्हित दीर्घ state;	/* NTFS specअगरic flags describing this inode.
				   See ntfs_inode_state_bits below. */
	अचिन्हित दीर्घ mft_no;	/* Number of the mft record / inode. */
	u16 seq_no;		/* Sequence number of the mft record. */
	atomic_t count;		/* Inode reference count क्रम book keeping. */
	ntfs_volume *vol;	/* Poपूर्णांकer to the ntfs volume of this inode. */
	/*
	 * If NInoAttr() is true, the below fields describe the attribute which
	 * this fake inode beदीर्घs to. The actual inode of this attribute is
	 * poपूर्णांकed to by base_ntfs_ino and nr_extents is always set to -1 (see
	 * below). For real inodes, we also set the type (AT_DATA क्रम files and
	 * AT_INDEX_ALLOCATION क्रम directories), with the name = शून्य and
	 * name_len = 0 क्रम files and name = I30 (global स्थिरant) and
	 * name_len = 4 क्रम directories.
	 */
	ATTR_TYPE type;	/* Attribute type of this fake inode. */
	ntfsअक्षर *name;		/* Attribute name of this fake inode. */
	u32 name_len;		/* Attribute name length of this fake inode. */
	runlist runlist;	/* If state has the NI_NonResident bit set,
				   the runlist of the unnamed data attribute
				   (अगर a file) or of the index allocation
				   attribute (directory) or of the attribute
				   described by the fake inode (अगर NInoAttr()).
				   If runlist.rl is शून्य, the runlist has not
				   been पढ़ो in yet or has been unmapped. If
				   NI_NonResident is clear, the attribute is
				   resident (file and fake inode) or there is
				   no $I30 index allocation attribute
				   (small directory). In the latter हाल
				   runlist.rl is always शून्य.*/
	/*
	 * The following fields are only valid क्रम real inodes and extent
	 * inodes.
	 */
	काष्ठा mutex mrec_lock;	/* Lock क्रम serializing access to the
				   mft record beदीर्घing to this inode. */
	काष्ठा page *page;	/* The page containing the mft record of the
				   inode. This should only be touched by the
				   (un)map_mft_record*() functions. */
	पूर्णांक page_ofs;		/* Offset पूर्णांकo the page at which the mft record
				   begins. This should only be touched by the
				   (un)map_mft_record*() functions. */
	/*
	 * Attribute list support (only क्रम use by the attribute lookup
	 * functions). Setup during पढ़ो_inode क्रम all inodes with attribute
	 * lists. Only valid अगर NI_AttrList is set in state, and attr_list_rl is
	 * further only valid अगर NI_AttrListNonResident is set.
	 */
	u32 attr_list_size;	/* Length of attribute list value in bytes. */
	u8 *attr_list;		/* Attribute list value itself. */
	runlist attr_list_rl;	/* Run list क्रम the attribute list value. */
	जोड़ अणु
		काष्ठा अणु /* It is a directory, $MFT, or an index inode. */
			u32 block_size;		/* Size of an index block. */
			u32 vcn_size;		/* Size of a vcn in this
						   index. */
			COLLATION_RULE collation_rule; /* The collation rule
						   क्रम the index. */
			u8 block_size_bits; 	/* Log2 of the above. */
			u8 vcn_size_bits;	/* Log2 of the above. */
		पूर्ण index;
		काष्ठा अणु /* It is a compressed/sparse file/attribute inode. */
			s64 size;		/* Copy of compressed_size from
						   $DATA. */
			u32 block_size;		/* Size of a compression block
						   (cb). */
			u8 block_size_bits;	/* Log2 of the size of a cb. */
			u8 block_clusters;	/* Number of clusters per cb. */
		पूर्ण compressed;
	पूर्ण itype;
	काष्ठा mutex extent_lock;	/* Lock क्रम accessing/modअगरying the
					   below . */
	s32 nr_extents;	/* For a base mft record, the number of attached extent
			   inodes (0 अगर none), क्रम extent records and क्रम fake
			   inodes describing an attribute this is -1. */
	जोड़ अणु		/* This जोड़ is only used अगर nr_extents != 0. */
		ntfs_inode **extent_ntfs_inos;	/* For nr_extents > 0, array of
						   the ntfs inodes of the extent
						   mft records beदीर्घing to
						   this base inode which have
						   been loaded. */
		ntfs_inode *base_ntfs_ino;	/* For nr_extents == -1, the
						   ntfs inode of the base mft
						   record. For fake inodes, the
						   real (base) inode to which
						   the attribute beदीर्घs. */
	पूर्ण ext;
पूर्ण;

/*
 * Defined bits क्रम the state field in the ntfs_inode काष्ठाure.
 * (f) = files only, (d) = directories only, (a) = attributes/fake inodes only
 */
प्रकार क्रमागत अणु
	NI_Dirty,		/* 1: Mft record needs to be written to disk. */
	NI_AttrList,		/* 1: Mft record contains an attribute list. */
	NI_AttrListNonResident,	/* 1: Attribute list is non-resident. Implies
				      NI_AttrList is set. */

	NI_Attr,		/* 1: Fake inode क्रम attribute i/o.
				   0: Real inode or extent inode. */

	NI_MstProtected,	/* 1: Attribute is रक्षित by MST fixups.
				   0: Attribute is not रक्षित by fixups. */
	NI_NonResident,		/* 1: Unnamed data attr is non-resident (f).
				   1: Attribute is non-resident (a). */
	NI_IndexAllocPresent = NI_NonResident,	/* 1: $I30 index alloc attr is
						   present (d). */
	NI_Compressed,		/* 1: Unnamed data attr is compressed (f).
				   1: Create compressed files by शेष (d).
				   1: Attribute is compressed (a). */
	NI_Encrypted,		/* 1: Unnamed data attr is encrypted (f).
				   1: Create encrypted files by शेष (d).
				   1: Attribute is encrypted (a). */
	NI_Sparse,		/* 1: Unnamed data attr is sparse (f).
				   1: Create sparse files by शेष (d).
				   1: Attribute is sparse (a). */
	NI_SparseDisabled,	/* 1: May not create sparse regions. */
	NI_TruncateFailed,	/* 1: Last ntfs_truncate() call failed. */
पूर्ण ntfs_inode_state_bits;

/*
 * NOTE: We should be adding dirty mft records to a list somewhere and they
 * should be independent of the (ntfs/vfs) inode काष्ठाure so that an inode can
 * be हटाओd but the record can be left dirty क्रम syncing later.
 */

/*
 * Macro tricks to expand the NInoFoo(), NInoSetFoo(), and NInoClearFoo()
 * functions.
 */
#घोषणा NINO_FNS(flag)					\
अटल अंतरभूत पूर्णांक NIno##flag(ntfs_inode *ni)		\
अणु							\
	वापस test_bit(NI_##flag, &(ni)->state);	\
पूर्ण							\
अटल अंतरभूत व्योम NInoSet##flag(ntfs_inode *ni)	\
अणु							\
	set_bit(NI_##flag, &(ni)->state);		\
पूर्ण							\
अटल अंतरभूत व्योम NInoClear##flag(ntfs_inode *ni)	\
अणु							\
	clear_bit(NI_##flag, &(ni)->state);		\
पूर्ण

/*
 * As above क्रम NInoTestSetFoo() and NInoTestClearFoo().
 */
#घोषणा TAS_NINO_FNS(flag)					\
अटल अंतरभूत पूर्णांक NInoTestSet##flag(ntfs_inode *ni)		\
अणु								\
	वापस test_and_set_bit(NI_##flag, &(ni)->state);	\
पूर्ण								\
अटल अंतरभूत पूर्णांक NInoTestClear##flag(ntfs_inode *ni)		\
अणु								\
	वापस test_and_clear_bit(NI_##flag, &(ni)->state);	\
पूर्ण

/* Emit the ntfs inode bitops functions. */
NINO_FNS(Dirty)
TAS_NINO_FNS(Dirty)
NINO_FNS(AttrList)
NINO_FNS(AttrListNonResident)
NINO_FNS(Attr)
NINO_FNS(MstProtected)
NINO_FNS(NonResident)
NINO_FNS(IndexAllocPresent)
NINO_FNS(Compressed)
NINO_FNS(Encrypted)
NINO_FNS(Sparse)
NINO_FNS(SparseDisabled)
NINO_FNS(TruncateFailed)

/*
 * The full काष्ठाure containing a ntfs_inode and a vfs काष्ठा inode. Used क्रम
 * all real and fake inodes but not क्रम extent inodes which lack the vfs काष्ठा
 * inode.
 */
प्रकार काष्ठा अणु
	ntfs_inode ntfs_inode;
	काष्ठा inode vfs_inode;		/* The vfs inode काष्ठाure. */
पूर्ण big_ntfs_inode;

/**
 * NTFS_I - वापस the ntfs inode given a vfs inode
 * @inode:	VFS inode
 *
 * NTFS_I() वापसs the ntfs inode associated with the VFS @inode.
 */
अटल अंतरभूत ntfs_inode *NTFS_I(काष्ठा inode *inode)
अणु
	वापस (ntfs_inode *)container_of(inode, big_ntfs_inode, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा inode *VFS_I(ntfs_inode *ni)
अणु
	वापस &((big_ntfs_inode *)ni)->vfs_inode;
पूर्ण

/**
 * ntfs_attr - ntfs in memory attribute काष्ठाure
 * @mft_no:	mft record number of the base mft record of this attribute
 * @name:	Unicode name of the attribute (शून्य अगर unnamed)
 * @name_len:	length of @name in Unicode अक्षरacters (0 अगर unnamed)
 * @type:	attribute type (see layout.h)
 *
 * This काष्ठाure exists only to provide a small काष्ठाure क्रम the
 * ntfs_अणुattr_पूर्णiget()/ntfs_test_inode()/ntfs_init_locked_inode() mechanism.
 *
 * NOTE: Elements are ordered by size to make the काष्ठाure as compact as
 * possible on all architectures.
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ mft_no;
	ntfsअक्षर *name;
	u32 name_len;
	ATTR_TYPE type;
पूर्ण ntfs_attr;

बाह्य पूर्णांक ntfs_test_inode(काष्ठा inode *vi, व्योम *data);

बाह्य काष्ठा inode *ntfs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ mft_no);
बाह्य काष्ठा inode *ntfs_attr_iget(काष्ठा inode *base_vi, ATTR_TYPE type,
		ntfsअक्षर *name, u32 name_len);
बाह्य काष्ठा inode *ntfs_index_iget(काष्ठा inode *base_vi, ntfsअक्षर *name,
		u32 name_len);

बाह्य काष्ठा inode *ntfs_alloc_big_inode(काष्ठा super_block *sb);
बाह्य व्योम ntfs_मुक्त_big_inode(काष्ठा inode *inode);
बाह्य व्योम ntfs_evict_big_inode(काष्ठा inode *vi);

बाह्य व्योम __ntfs_init_inode(काष्ठा super_block *sb, ntfs_inode *ni);

अटल अंतरभूत व्योम ntfs_init_big_inode(काष्ठा inode *vi)
अणु
	ntfs_inode *ni = NTFS_I(vi);

	ntfs_debug("Entering.");
	__ntfs_init_inode(vi->i_sb, ni);
	ni->mft_no = vi->i_ino;
पूर्ण

बाह्य ntfs_inode *ntfs_new_extent_inode(काष्ठा super_block *sb,
		अचिन्हित दीर्घ mft_no);
बाह्य व्योम ntfs_clear_extent_inode(ntfs_inode *ni);

बाह्य पूर्णांक ntfs_पढ़ो_inode_mount(काष्ठा inode *vi);

बाह्य पूर्णांक ntfs_show_options(काष्ठा seq_file *sf, काष्ठा dentry *root);

#अगर_घोषित NTFS_RW

बाह्य पूर्णांक ntfs_truncate(काष्ठा inode *vi);
बाह्य व्योम ntfs_truncate_vfs(काष्ठा inode *vi);

बाह्य पूर्णांक ntfs_setattr(काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *dentry, काष्ठा iattr *attr);

बाह्य पूर्णांक __ntfs_ग_लिखो_inode(काष्ठा inode *vi, पूर्णांक sync);

अटल अंतरभूत व्योम ntfs_commit_inode(काष्ठा inode *vi)
अणु
	अगर (!is_bad_inode(vi))
		__ntfs_ग_लिखो_inode(vi, 1);
	वापस;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम ntfs_truncate_vfs(काष्ठा inode *vi) अणुपूर्ण

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* _LINUX_NTFS_INODE_H */
