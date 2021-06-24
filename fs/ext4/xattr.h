<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
  File: fs/ext4/xattr.h

  On-disk क्रमmat of extended attributes क्रम the ext4 fileप्रणाली.

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#समावेश <linux/xattr.h>

/* Magic value in attribute blocks */
#घोषणा EXT4_XATTR_MAGIC		0xEA020000

/* Maximum number of references to one attribute block */
#घोषणा EXT4_XATTR_REFCOUNT_MAX		1024

/* Name indexes */
#घोषणा EXT4_XATTR_INDEX_USER			1
#घोषणा EXT4_XATTR_INDEX_POSIX_ACL_ACCESS	2
#घोषणा EXT4_XATTR_INDEX_POSIX_ACL_DEFAULT	3
#घोषणा EXT4_XATTR_INDEX_TRUSTED		4
#घोषणा	EXT4_XATTR_INDEX_LUSTRE			5
#घोषणा EXT4_XATTR_INDEX_SECURITY	        6
#घोषणा EXT4_XATTR_INDEX_SYSTEM			7
#घोषणा EXT4_XATTR_INDEX_RICHACL		8
#घोषणा EXT4_XATTR_INDEX_ENCRYPTION		9
#घोषणा EXT4_XATTR_INDEX_HURD			10 /* Reserved क्रम Hurd */

काष्ठा ext4_xattr_header अणु
	__le32	h_magic;	/* magic number क्रम identअगरication */
	__le32	h_refcount;	/* reference count */
	__le32	h_blocks;	/* number of disk blocks used */
	__le32	h_hash;		/* hash value of all attributes */
	__le32	h_checksum;	/* crc32c(uuid+id+xattrblock) */
				/* id = inum अगर refcount=1, blknum otherwise */
	__u32	h_reserved[3];	/* zero right now */
पूर्ण;

काष्ठा ext4_xattr_ibody_header अणु
	__le32	h_magic;	/* magic number क्रम identअगरication */
पूर्ण;

काष्ठा ext4_xattr_entry अणु
	__u8	e_name_len;	/* length of name */
	__u8	e_name_index;	/* attribute name index */
	__le16	e_value_offs;	/* offset in disk block of value */
	__le32	e_value_inum;	/* inode in which the value is stored */
	__le32	e_value_size;	/* size of attribute value */
	__le32	e_hash;		/* hash value of name and value */
	अक्षर	e_name[];	/* attribute name */
पूर्ण;

#घोषणा EXT4_XATTR_PAD_BITS		2
#घोषणा EXT4_XATTR_PAD		(1<<EXT4_XATTR_PAD_BITS)
#घोषणा EXT4_XATTR_ROUND		(EXT4_XATTR_PAD-1)
#घोषणा EXT4_XATTR_LEN(name_len) \
	(((name_len) + EXT4_XATTR_ROUND + \
	माप(काष्ठा ext4_xattr_entry)) & ~EXT4_XATTR_ROUND)
#घोषणा EXT4_XATTR_NEXT(entry) \
	((काष्ठा ext4_xattr_entry *)( \
	 (अक्षर *)(entry) + EXT4_XATTR_LEN((entry)->e_name_len)))
#घोषणा EXT4_XATTR_SIZE(size) \
	(((size) + EXT4_XATTR_ROUND) & ~EXT4_XATTR_ROUND)

#घोषणा IHDR(inode, raw_inode) \
	((काष्ठा ext4_xattr_ibody_header *) \
		((व्योम *)raw_inode + \
		EXT4_GOOD_OLD_INODE_SIZE + \
		EXT4_I(inode)->i_extra_isize))
#घोषणा IFIRST(hdr) ((काष्ठा ext4_xattr_entry *)((hdr)+1))

/*
 * XATTR_SIZE_MAX is currently 64k, but क्रम the purposes of checking
 * क्रम file प्रणाली consistency errors, we use a somewhat bigger value.
 * This allows XATTR_SIZE_MAX to grow in the future, but by using this
 * instead of पूर्णांक_उच्च क्रम certain consistency checks, we करोn't need to
 * worry about arithmetic overflows.  (Actually XATTR_SIZE_MAX is
 * defined in include/uapi/linux/सीमा.स, so changing it is going
 * not going to be trivial....)
 */
#घोषणा EXT4_XATTR_SIZE_MAX (1 << 24)

/*
 * The minimum size of EA value when you start storing it in an बाह्यal inode
 * size of block - size of header - size of 1 entry - 4 null bytes
*/
#घोषणा EXT4_XATTR_MIN_LARGE_EA_SIZE(b)					\
	((b) - EXT4_XATTR_LEN(3) - माप(काष्ठा ext4_xattr_header) - 4)

#घोषणा BHDR(bh) ((काष्ठा ext4_xattr_header *)((bh)->b_data))
#घोषणा ENTRY(ptr) ((काष्ठा ext4_xattr_entry *)(ptr))
#घोषणा BFIRST(bh) ENTRY(BHDR(bh)+1)
#घोषणा IS_LAST_ENTRY(entry) (*(__u32 *)(entry) == 0)

#घोषणा EXT4_ZERO_XATTR_VALUE ((व्योम *)-1)

काष्ठा ext4_xattr_info अणु
	स्थिर अक्षर *name;
	स्थिर व्योम *value;
	माप_प्रकार value_len;
	पूर्णांक name_index;
	पूर्णांक in_inode;
पूर्ण;

काष्ठा ext4_xattr_search अणु
	काष्ठा ext4_xattr_entry *first;
	व्योम *base;
	व्योम *end;
	काष्ठा ext4_xattr_entry *here;
	पूर्णांक not_found;
पूर्ण;

काष्ठा ext4_xattr_ibody_find अणु
	काष्ठा ext4_xattr_search s;
	काष्ठा ext4_iloc iloc;
पूर्ण;

काष्ठा ext4_xattr_inode_array अणु
	अचिन्हित पूर्णांक count;		/* # of used items in the array */
	काष्ठा inode *inodes[];
पूर्ण;

बाह्य स्थिर काष्ठा xattr_handler ext4_xattr_user_handler;
बाह्य स्थिर काष्ठा xattr_handler ext4_xattr_trusted_handler;
बाह्य स्थिर काष्ठा xattr_handler ext4_xattr_security_handler;
बाह्य स्थिर काष्ठा xattr_handler ext4_xattr_hurd_handler;

#घोषणा EXT4_XATTR_NAME_ENCRYPTION_CONTEXT "c"

/*
 * The EXT4_STATE_NO_EXPAND is overloaded and used क्रम two purposes.
 * The first is to संकेत that there the अंतरभूत xattrs and data are
 * taking up so much space that we might as well not keep trying to
 * expand it.  The second is that xattr_sem is taken क्रम writing, so
 * we shouldn't try to recurse पूर्णांकo the inode expansion.  For this
 * second हाल, we need to make sure that we take save and restore the
 * NO_EXPAND state flag appropriately.
 */
अटल अंतरभूत व्योम ext4_ग_लिखो_lock_xattr(काष्ठा inode *inode, पूर्णांक *save)
अणु
	करोwn_ग_लिखो(&EXT4_I(inode)->xattr_sem);
	*save = ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND);
	ext4_set_inode_state(inode, EXT4_STATE_NO_EXPAND);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_ग_लिखो_trylock_xattr(काष्ठा inode *inode, पूर्णांक *save)
अणु
	अगर (करोwn_ग_लिखो_trylock(&EXT4_I(inode)->xattr_sem) == 0)
		वापस 0;
	*save = ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND);
	ext4_set_inode_state(inode, EXT4_STATE_NO_EXPAND);
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम ext4_ग_लिखो_unlock_xattr(काष्ठा inode *inode, पूर्णांक *save)
अणु
	अगर (*save == 0)
		ext4_clear_inode_state(inode, EXT4_STATE_NO_EXPAND);
	up_ग_लिखो(&EXT4_I(inode)->xattr_sem);
पूर्ण

बाह्य sमाप_प्रकार ext4_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);

बाह्य पूर्णांक ext4_xattr_get(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, व्योम *, माप_प्रकार);
बाह्य पूर्णांक ext4_xattr_set(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य पूर्णांक ext4_xattr_set_handle(handle_t *, काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य पूर्णांक ext4_xattr_set_credits(काष्ठा inode *inode, माप_प्रकार value_len,
				  bool is_create, पूर्णांक *credits);
बाह्य पूर्णांक __ext4_xattr_set_credits(काष्ठा super_block *sb, काष्ठा inode *inode,
				काष्ठा buffer_head *block_bh, माप_प्रकार value_len,
				bool is_create);

बाह्य पूर्णांक ext4_xattr_delete_inode(handle_t *handle, काष्ठा inode *inode,
				   काष्ठा ext4_xattr_inode_array **array,
				   पूर्णांक extra_credits);
बाह्य व्योम ext4_xattr_inode_array_मुक्त(काष्ठा ext4_xattr_inode_array *array);

बाह्य पूर्णांक ext4_expand_extra_isize_ea(काष्ठा inode *inode, पूर्णांक new_extra_isize,
			    काष्ठा ext4_inode *raw_inode, handle_t *handle);

बाह्य स्थिर काष्ठा xattr_handler *ext4_xattr_handlers[];

बाह्य पूर्णांक ext4_xattr_ibody_find(काष्ठा inode *inode, काष्ठा ext4_xattr_info *i,
				 काष्ठा ext4_xattr_ibody_find *is);
बाह्य पूर्णांक ext4_xattr_ibody_get(काष्ठा inode *inode, पूर्णांक name_index,
				स्थिर अक्षर *name,
				व्योम *buffer, माप_प्रकार buffer_size);
बाह्य पूर्णांक ext4_xattr_ibody_अंतरभूत_set(handle_t *handle, काष्ठा inode *inode,
				       काष्ठा ext4_xattr_info *i,
				       काष्ठा ext4_xattr_ibody_find *is);

बाह्य काष्ठा mb_cache *ext4_xattr_create_cache(व्योम);
बाह्य व्योम ext4_xattr_destroy_cache(काष्ठा mb_cache *);

#अगर_घोषित CONFIG_EXT4_FS_SECURITY
बाह्य पूर्णांक ext4_init_security(handle_t *handle, काष्ठा inode *inode,
			      काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr);
#अन्यथा
अटल अंतरभूत पूर्णांक ext4_init_security(handle_t *handle, काष्ठा inode *inode,
				     काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_LOCKDEP
बाह्य व्योम ext4_xattr_inode_set_class(काष्ठा inode *ea_inode);
#अन्यथा
अटल अंतरभूत व्योम ext4_xattr_inode_set_class(काष्ठा inode *ea_inode) अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक ext4_get_inode_usage(काष्ठा inode *inode, qमाप_प्रकार *usage);
