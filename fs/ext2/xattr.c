<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext2/xattr.c
 *
 * Copyright (C) 2001-2003 Andreas Gruenbacher <agruen@suse.de>
 *
 * Fix by Harrison Xing <harrison@mountainviewdata.com>.
 * Extended attributes क्रम symlinks and special files added per
 *  suggestion of Luka Renko <luka.renko@hermes.si>.
 * xattr consolidation Copyright (c) 2004 James Morris <jmorris@redhat.com>,
 *  Red Hat Inc.
 *
 */

/*
 * Extended attributes are stored on disk blocks allocated outside of
 * any inode. The i_file_acl field is then made to poपूर्णांक to this allocated
 * block. If all extended attributes of an inode are identical, these
 * inodes may share the same extended attribute block. Such situations
 * are स्वतःmatically detected by keeping a cache of recent attribute block
 * numbers and hashes over the block's contents in memory.
 *
 *
 * Extended attribute block layout:
 *
 *   +------------------+
 *   | header           |
 *   | entry 1          | |
 *   | entry 2          | | growing करोwnwards
 *   | entry 3          | v
 *   | four null bytes  |
 *   | . . .            |
 *   | value 1          | ^
 *   | value 3          | | growing upwards
 *   | value 2          | |
 *   +------------------+
 *
 * The block header is followed by multiple entry descriptors. These entry
 * descriptors are variable in size, and aligned to EXT2_XATTR_PAD
 * byte boundaries. The entry descriptors are sorted by attribute name,
 * so that two extended attribute blocks can be compared efficiently.
 *
 * Attribute values are aligned to the end of the block, stored in
 * no specअगरic order. They are also padded to EXT2_XATTR_PAD byte
 * boundaries. No additional gaps are left between them.
 *
 * Locking strategy
 * ----------------
 * EXT2_I(inode)->i_file_acl is रक्षित by EXT2_I(inode)->xattr_sem.
 * EA blocks are only changed अगर they are exclusive to an inode, so
 * holding xattr_sem also means that nothing but the EA block's reference
 * count will change. Multiple ग_लिखोrs to an EA block are synchronized
 * by the bh lock. No more than a single bh lock is held at any समय
 * to aव्योम deadlocks.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/init.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/mbcache.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/security.h>
#समावेश "ext2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

#घोषणा HDR(bh) ((काष्ठा ext2_xattr_header *)((bh)->b_data))
#घोषणा ENTRY(ptr) ((काष्ठा ext2_xattr_entry *)(ptr))
#घोषणा FIRST_ENTRY(bh) ENTRY(HDR(bh)+1)
#घोषणा IS_LAST_ENTRY(entry) (*(__u32 *)(entry) == 0)

#अगर_घोषित EXT2_XATTR_DEBUG
# define ea_idebug(inode, f...) करो अणु \
		prपूर्णांकk(KERN_DEBUG "inode %s:%ld: ", \
			inode->i_sb->s_id, inode->i_ino); \
		prपूर्णांकk(f); \
		prपूर्णांकk("\n"); \
	पूर्ण जबतक (0)
# define ea_bdebug(bh, f...) करो अणु \
		prपूर्णांकk(KERN_DEBUG "block %pg:%lu: ", \
			bh->b_bdev, (अचिन्हित दीर्घ) bh->b_blocknr); \
		prपूर्णांकk(f); \
		prपूर्णांकk("\n"); \
	पूर्ण जबतक (0)
#अन्यथा
# define ea_idebug(inode, f...)	no_prपूर्णांकk(f)
# define ea_bdebug(bh, f...)	no_prपूर्णांकk(f)
#पूर्ण_अगर

अटल पूर्णांक ext2_xattr_set2(काष्ठा inode *, काष्ठा buffer_head *,
			   काष्ठा ext2_xattr_header *);

अटल पूर्णांक ext2_xattr_cache_insert(काष्ठा mb_cache *, काष्ठा buffer_head *);
अटल काष्ठा buffer_head *ext2_xattr_cache_find(काष्ठा inode *,
						 काष्ठा ext2_xattr_header *);
अटल व्योम ext2_xattr_rehash(काष्ठा ext2_xattr_header *,
			      काष्ठा ext2_xattr_entry *);

अटल स्थिर काष्ठा xattr_handler *ext2_xattr_handler_map[] = अणु
	[EXT2_XATTR_INDEX_USER]		     = &ext2_xattr_user_handler,
#अगर_घोषित CONFIG_EXT2_FS_POSIX_ACL
	[EXT2_XATTR_INDEX_POSIX_ACL_ACCESS]  = &posix_acl_access_xattr_handler,
	[EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT] = &posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	[EXT2_XATTR_INDEX_TRUSTED]	     = &ext2_xattr_trusted_handler,
#अगर_घोषित CONFIG_EXT2_FS_SECURITY
	[EXT2_XATTR_INDEX_SECURITY]	     = &ext2_xattr_security_handler,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा xattr_handler *ext2_xattr_handlers[] = अणु
	&ext2_xattr_user_handler,
	&ext2_xattr_trusted_handler,
#अगर_घोषित CONFIG_EXT2_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EXT2_FS_SECURITY
	&ext2_xattr_security_handler,
#पूर्ण_अगर
	शून्य
पूर्ण;

#घोषणा EA_BLOCK_CACHE(inode)	(EXT2_SB(inode->i_sb)->s_ea_block_cache)

अटल अंतरभूत स्थिर काष्ठा xattr_handler *
ext2_xattr_handler(पूर्णांक name_index)
अणु
	स्थिर काष्ठा xattr_handler *handler = शून्य;

	अगर (name_index > 0 && name_index < ARRAY_SIZE(ext2_xattr_handler_map))
		handler = ext2_xattr_handler_map[name_index];
	वापस handler;
पूर्ण

अटल bool
ext2_xattr_header_valid(काष्ठा ext2_xattr_header *header)
अणु
	अगर (header->h_magic != cpu_to_le32(EXT2_XATTR_MAGIC) ||
	    header->h_blocks != cpu_to_le32(1))
		वापस false;

	वापस true;
पूर्ण

अटल bool
ext2_xattr_entry_valid(काष्ठा ext2_xattr_entry *entry,
		       अक्षर *end, माप_प्रकार end_offs)
अणु
	काष्ठा ext2_xattr_entry *next;
	माप_प्रकार size;

	next = EXT2_XATTR_NEXT(entry);
	अगर ((अक्षर *)next >= end)
		वापस false;

	अगर (entry->e_value_block != 0)
		वापस false;

	size = le32_to_cpu(entry->e_value_size);
	अगर (size > end_offs ||
	    le16_to_cpu(entry->e_value_offs) + size > end_offs)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
ext2_xattr_cmp_entry(पूर्णांक name_index, माप_प्रकार name_len, स्थिर अक्षर *name,
		     काष्ठा ext2_xattr_entry *entry)
अणु
	पूर्णांक cmp;

	cmp = name_index - entry->e_name_index;
	अगर (!cmp)
		cmp = name_len - entry->e_name_len;
	अगर (!cmp)
		cmp = स_भेद(name, entry->e_name, name_len);

	वापस cmp;
पूर्ण

/*
 * ext2_xattr_get()
 *
 * Copy an extended attribute पूर्णांकo the buffer
 * provided, or compute the buffer size required.
 * Buffer is शून्य to compute the size of the buffer required.
 *
 * Returns a negative error number on failure, or the number of bytes
 * used / required on success.
 */
पूर्णांक
ext2_xattr_get(काष्ठा inode *inode, पूर्णांक name_index, स्थिर अक्षर *name,
	       व्योम *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext2_xattr_entry *entry;
	माप_प्रकार name_len, size;
	अक्षर *end;
	पूर्णांक error, not_found;
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	ea_idebug(inode, "name=%d.%s, buffer=%p, buffer_size=%ld",
		  name_index, name, buffer, (दीर्घ)buffer_size);

	अगर (name == शून्य)
		वापस -EINVAL;
	name_len = म_माप(name);
	अगर (name_len > 255)
		वापस -दुस्फल;

	करोwn_पढ़ो(&EXT2_I(inode)->xattr_sem);
	error = -ENODATA;
	अगर (!EXT2_I(inode)->i_file_acl)
		जाओ cleanup;
	ea_idebug(inode, "reading block %d", EXT2_I(inode)->i_file_acl);
	bh = sb_bपढ़ो(inode->i_sb, EXT2_I(inode)->i_file_acl);
	error = -EIO;
	अगर (!bh)
		जाओ cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_पढ़ो(&(bh->b_count)), le32_to_cpu(HDR(bh)->h_refcount));
	end = bh->b_data + bh->b_size;
	अगर (!ext2_xattr_header_valid(HDR(bh))) अणु
bad_block:
		ext2_error(inode->i_sb, "ext2_xattr_get",
			"inode %ld: bad block %d", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		error = -EIO;
		जाओ cleanup;
	पूर्ण

	/* find named attribute */
	entry = FIRST_ENTRY(bh);
	जबतक (!IS_LAST_ENTRY(entry)) अणु
		अगर (!ext2_xattr_entry_valid(entry, end,
		    inode->i_sb->s_blocksize))
			जाओ bad_block;

		not_found = ext2_xattr_cmp_entry(name_index, name_len, name,
						 entry);
		अगर (!not_found)
			जाओ found;
		अगर (not_found < 0)
			अवरोध;

		entry = EXT2_XATTR_NEXT(entry);
	पूर्ण
	अगर (ext2_xattr_cache_insert(ea_block_cache, bh))
		ea_idebug(inode, "cache insert failed");
	error = -ENODATA;
	जाओ cleanup;
found:
	size = le32_to_cpu(entry->e_value_size);
	अगर (ext2_xattr_cache_insert(ea_block_cache, bh))
		ea_idebug(inode, "cache insert failed");
	अगर (buffer) अणु
		error = -दुस्फल;
		अगर (size > buffer_size)
			जाओ cleanup;
		/* वापस value of attribute */
		स_नकल(buffer, bh->b_data + le16_to_cpu(entry->e_value_offs),
			size);
	पूर्ण
	error = size;

cleanup:
	brअन्यथा(bh);
	up_पढ़ो(&EXT2_I(inode)->xattr_sem);

	वापस error;
पूर्ण

/*
 * ext2_xattr_list()
 *
 * Copy a list of attribute names पूर्णांकo the buffer
 * provided, or compute the buffer size required.
 * Buffer is शून्य to compute the size of the buffer required.
 *
 * Returns a negative error number on failure, or the number of bytes
 * used / required on success.
 */
अटल पूर्णांक
ext2_xattr_list(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext2_xattr_entry *entry;
	अक्षर *end;
	माप_प्रकार rest = buffer_size;
	पूर्णांक error;
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	ea_idebug(inode, "buffer=%p, buffer_size=%ld",
		  buffer, (दीर्घ)buffer_size);

	करोwn_पढ़ो(&EXT2_I(inode)->xattr_sem);
	error = 0;
	अगर (!EXT2_I(inode)->i_file_acl)
		जाओ cleanup;
	ea_idebug(inode, "reading block %d", EXT2_I(inode)->i_file_acl);
	bh = sb_bपढ़ो(inode->i_sb, EXT2_I(inode)->i_file_acl);
	error = -EIO;
	अगर (!bh)
		जाओ cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_पढ़ो(&(bh->b_count)), le32_to_cpu(HDR(bh)->h_refcount));
	end = bh->b_data + bh->b_size;
	अगर (!ext2_xattr_header_valid(HDR(bh))) अणु
bad_block:
		ext2_error(inode->i_sb, "ext2_xattr_list",
			"inode %ld: bad block %d", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		error = -EIO;
		जाओ cleanup;
	पूर्ण

	/* check the on-disk data काष्ठाure */
	entry = FIRST_ENTRY(bh);
	जबतक (!IS_LAST_ENTRY(entry)) अणु
		अगर (!ext2_xattr_entry_valid(entry, end,
		    inode->i_sb->s_blocksize))
			जाओ bad_block;
		entry = EXT2_XATTR_NEXT(entry);
	पूर्ण
	अगर (ext2_xattr_cache_insert(ea_block_cache, bh))
		ea_idebug(inode, "cache insert failed");

	/* list the attribute names */
	क्रम (entry = FIRST_ENTRY(bh); !IS_LAST_ENTRY(entry);
	     entry = EXT2_XATTR_NEXT(entry)) अणु
		स्थिर काष्ठा xattr_handler *handler =
			ext2_xattr_handler(entry->e_name_index);

		अगर (handler && (!handler->list || handler->list(dentry))) अणु
			स्थिर अक्षर *prefix = handler->prefix ?: handler->name;
			माप_प्रकार prefix_len = म_माप(prefix);
			माप_प्रकार size = prefix_len + entry->e_name_len + 1;

			अगर (buffer) अणु
				अगर (size > rest) अणु
					error = -दुस्फल;
					जाओ cleanup;
				पूर्ण
				स_नकल(buffer, prefix, prefix_len);
				buffer += prefix_len;
				स_नकल(buffer, entry->e_name, entry->e_name_len);
				buffer += entry->e_name_len;
				*buffer++ = 0;
			पूर्ण
			rest -= size;
		पूर्ण
	पूर्ण
	error = buffer_size - rest;  /* total size */

cleanup:
	brअन्यथा(bh);
	up_पढ़ो(&EXT2_I(inode)->xattr_sem);

	वापस error;
पूर्ण

/*
 * Inode operation listxattr()
 *
 * d_inode(dentry)->i_mutex: करोn't care
 */
sमाप_प्रकार
ext2_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	वापस ext2_xattr_list(dentry, buffer, size);
पूर्ण

/*
 * If the EXT2_FEATURE_COMPAT_EXT_ATTR feature of this file प्रणाली is
 * not set, set it.
 */
अटल व्योम ext2_xattr_update_super_block(काष्ठा super_block *sb)
अणु
	अगर (EXT2_HAS_COMPAT_FEATURE(sb, EXT2_FEATURE_COMPAT_EXT_ATTR))
		वापस;

	spin_lock(&EXT2_SB(sb)->s_lock);
	ext2_update_dynamic_rev(sb);
	EXT2_SET_COMPAT_FEATURE(sb, EXT2_FEATURE_COMPAT_EXT_ATTR);
	spin_unlock(&EXT2_SB(sb)->s_lock);
	mark_buffer_dirty(EXT2_SB(sb)->s_sbh);
पूर्ण

/*
 * ext2_xattr_set()
 *
 * Create, replace or हटाओ an extended attribute क्रम this inode.  Value
 * is शून्य to हटाओ an existing extended attribute, and non-शून्य to
 * either replace an existing extended attribute, or create a new extended
 * attribute. The flags XATTR_REPLACE and XATTR_CREATE
 * specअगरy that an extended attribute must exist and must not exist
 * previous to the call, respectively.
 *
 * Returns 0, or a negative error number on failure.
 */
पूर्णांक
ext2_xattr_set(काष्ठा inode *inode, पूर्णांक name_index, स्थिर अक्षर *name,
	       स्थिर व्योम *value, माप_प्रकार value_len, पूर्णांक flags)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext2_xattr_header *header = शून्य;
	काष्ठा ext2_xattr_entry *here = शून्य, *last = शून्य;
	माप_प्रकार name_len, मुक्त, min_offs = sb->s_blocksize;
	पूर्णांक not_found = 1, error;
	अक्षर *end;
	
	/*
	 * header -- Poपूर्णांकs either पूर्णांकo bh, or to a temporarily
	 *           allocated buffer.
	 * here -- The named entry found, or the place क्रम inserting, within
	 *         the block poपूर्णांकed to by header.
	 * last -- Poपूर्णांकs right after the last named entry within the block
	 *         poपूर्णांकed to by header.
	 * min_offs -- The offset of the first value (values are aligned
	 *             towards the end of the block).
	 * end -- Poपूर्णांकs right after the block poपूर्णांकed to by header.
	 */
	
	ea_idebug(inode, "name=%d.%s, value=%p, value_len=%ld",
		  name_index, name, value, (दीर्घ)value_len);

	अगर (value == शून्य)
		value_len = 0;
	अगर (name == शून्य)
		वापस -EINVAL;
	name_len = म_माप(name);
	अगर (name_len > 255 || value_len > sb->s_blocksize)
		वापस -दुस्फल;
	error = dquot_initialize(inode);
	अगर (error)
		वापस error;
	करोwn_ग_लिखो(&EXT2_I(inode)->xattr_sem);
	अगर (EXT2_I(inode)->i_file_acl) अणु
		/* The inode alपढ़ोy has an extended attribute block. */
		bh = sb_bपढ़ो(sb, EXT2_I(inode)->i_file_acl);
		error = -EIO;
		अगर (!bh)
			जाओ cleanup;
		ea_bdebug(bh, "b_count=%d, refcount=%d",
			atomic_पढ़ो(&(bh->b_count)),
			le32_to_cpu(HDR(bh)->h_refcount));
		header = HDR(bh);
		end = bh->b_data + bh->b_size;
		अगर (!ext2_xattr_header_valid(header)) अणु
bad_block:
			ext2_error(sb, "ext2_xattr_set",
				"inode %ld: bad block %d", inode->i_ino, 
				   EXT2_I(inode)->i_file_acl);
			error = -EIO;
			जाओ cleanup;
		पूर्ण
		/*
		 * Find the named attribute. If not found, 'here' will poपूर्णांक
		 * to entry where the new attribute should be inserted to
		 * मुख्यtain sorting.
		 */
		last = FIRST_ENTRY(bh);
		जबतक (!IS_LAST_ENTRY(last)) अणु
			अगर (!ext2_xattr_entry_valid(last, end, sb->s_blocksize))
				जाओ bad_block;
			अगर (last->e_value_size) अणु
				माप_प्रकार offs = le16_to_cpu(last->e_value_offs);
				अगर (offs < min_offs)
					min_offs = offs;
			पूर्ण
			अगर (not_found > 0) अणु
				not_found = ext2_xattr_cmp_entry(name_index,
								 name_len,
								 name, last);
				अगर (not_found <= 0)
					here = last;
			पूर्ण
			last = EXT2_XATTR_NEXT(last);
		पूर्ण
		अगर (not_found > 0)
			here = last;

		/* Check whether we have enough space left. */
		मुक्त = min_offs - ((अक्षर*)last - (अक्षर*)header) - माप(__u32);
	पूर्ण अन्यथा अणु
		/* We will use a new extended attribute block. */
		मुक्त = sb->s_blocksize -
			माप(काष्ठा ext2_xattr_header) - माप(__u32);
	पूर्ण

	अगर (not_found) अणु
		/* Request to हटाओ a nonexistent attribute? */
		error = -ENODATA;
		अगर (flags & XATTR_REPLACE)
			जाओ cleanup;
		error = 0;
		अगर (value == शून्य)
			जाओ cleanup;
	पूर्ण अन्यथा अणु
		/* Request to create an existing attribute? */
		error = -EEXIST;
		अगर (flags & XATTR_CREATE)
			जाओ cleanup;
		मुक्त += EXT2_XATTR_SIZE(le32_to_cpu(here->e_value_size));
		मुक्त += EXT2_XATTR_LEN(name_len);
	पूर्ण
	error = -ENOSPC;
	अगर (मुक्त < EXT2_XATTR_LEN(name_len) + EXT2_XATTR_SIZE(value_len))
		जाओ cleanup;

	/* Here we know that we can set the new attribute. */

	अगर (header) अणु
		/* निश्चित(header == HDR(bh)); */
		lock_buffer(bh);
		अगर (header->h_refcount == cpu_to_le32(1)) अणु
			__u32 hash = le32_to_cpu(header->h_hash);

			ea_bdebug(bh, "modifying in-place");
			/*
			 * This must happen under buffer lock क्रम
			 * ext2_xattr_set2() to reliably detect modअगरied block
			 */
			mb_cache_entry_delete(EA_BLOCK_CACHE(inode), hash,
					      bh->b_blocknr);

			/* keep the buffer locked जबतक modअगरying it. */
		पूर्ण अन्यथा अणु
			पूर्णांक offset;

			unlock_buffer(bh);
			ea_bdebug(bh, "cloning");
			header = kmemdup(HDR(bh), bh->b_size, GFP_KERNEL);
			error = -ENOMEM;
			अगर (header == शून्य)
				जाओ cleanup;
			header->h_refcount = cpu_to_le32(1);

			offset = (अक्षर *)here - bh->b_data;
			here = ENTRY((अक्षर *)header + offset);
			offset = (अक्षर *)last - bh->b_data;
			last = ENTRY((अक्षर *)header + offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Allocate a buffer where we स्थिरruct the new block. */
		header = kzalloc(sb->s_blocksize, GFP_KERNEL);
		error = -ENOMEM;
		अगर (header == शून्य)
			जाओ cleanup;
		end = (अक्षर *)header + sb->s_blocksize;
		header->h_magic = cpu_to_le32(EXT2_XATTR_MAGIC);
		header->h_blocks = header->h_refcount = cpu_to_le32(1);
		last = here = ENTRY(header+1);
	पूर्ण

	/* Iff we are modअगरying the block in-place, bh is locked here. */

	अगर (not_found) अणु
		/* Insert the new name. */
		माप_प्रकार size = EXT2_XATTR_LEN(name_len);
		माप_प्रकार rest = (अक्षर *)last - (अक्षर *)here;
		स_हटाओ((अक्षर *)here + size, here, rest);
		स_रखो(here, 0, size);
		here->e_name_index = name_index;
		here->e_name_len = name_len;
		स_नकल(here->e_name, name, name_len);
	पूर्ण अन्यथा अणु
		अगर (here->e_value_size) अणु
			अक्षर *first_val = (अक्षर *)header + min_offs;
			माप_प्रकार offs = le16_to_cpu(here->e_value_offs);
			अक्षर *val = (अक्षर *)header + offs;
			माप_प्रकार size = EXT2_XATTR_SIZE(
				le32_to_cpu(here->e_value_size));

			अगर (size == EXT2_XATTR_SIZE(value_len)) अणु
				/* The old and the new value have the same
				   size. Just replace. */
				here->e_value_size = cpu_to_le32(value_len);
				स_रखो(val + size - EXT2_XATTR_PAD, 0,
				       EXT2_XATTR_PAD); /* Clear pad bytes. */
				स_नकल(val, value, value_len);
				जाओ skip_replace;
			पूर्ण

			/* Remove the old value. */
			स_हटाओ(first_val + size, first_val, val - first_val);
			स_रखो(first_val, 0, size);
			min_offs += size;

			/* Adjust all value offsets. */
			last = ENTRY(header+1);
			जबतक (!IS_LAST_ENTRY(last)) अणु
				माप_प्रकार o = le16_to_cpu(last->e_value_offs);
				अगर (o < offs)
					last->e_value_offs =
						cpu_to_le16(o + size);
				last = EXT2_XATTR_NEXT(last);
			पूर्ण

			here->e_value_offs = 0;
		पूर्ण
		अगर (value == शून्य) अणु
			/* Remove the old name. */
			माप_प्रकार size = EXT2_XATTR_LEN(name_len);
			last = ENTRY((अक्षर *)last - size);
			स_हटाओ(here, (अक्षर*)here + size,
				(अक्षर*)last - (अक्षर*)here);
			स_रखो(last, 0, size);
		पूर्ण
	पूर्ण

	अगर (value != शून्य) अणु
		/* Insert the new value. */
		here->e_value_size = cpu_to_le32(value_len);
		अगर (value_len) अणु
			माप_प्रकार size = EXT2_XATTR_SIZE(value_len);
			अक्षर *val = (अक्षर *)header + min_offs - size;
			here->e_value_offs =
				cpu_to_le16((अक्षर *)val - (अक्षर *)header);
			स_रखो(val + size - EXT2_XATTR_PAD, 0,
			       EXT2_XATTR_PAD); /* Clear the pad bytes. */
			स_नकल(val, value, value_len);
		पूर्ण
	पूर्ण

skip_replace:
	अगर (IS_LAST_ENTRY(ENTRY(header+1))) अणु
		/* This block is now empty. */
		अगर (bh && header == HDR(bh))
			unlock_buffer(bh);  /* we were modअगरying in-place. */
		error = ext2_xattr_set2(inode, bh, शून्य);
	पूर्ण अन्यथा अणु
		ext2_xattr_rehash(header, here);
		अगर (bh && header == HDR(bh))
			unlock_buffer(bh);  /* we were modअगरying in-place. */
		error = ext2_xattr_set2(inode, bh, header);
	पूर्ण

cleanup:
	अगर (!(bh && header == HDR(bh)))
		kमुक्त(header);
	brअन्यथा(bh);
	up_ग_लिखो(&EXT2_I(inode)->xattr_sem);

	वापस error;
पूर्ण

/*
 * Second half of ext2_xattr_set(): Update the file प्रणाली.
 */
अटल पूर्णांक
ext2_xattr_set2(काष्ठा inode *inode, काष्ठा buffer_head *old_bh,
		काष्ठा ext2_xattr_header *header)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *new_bh = शून्य;
	पूर्णांक error;
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	अगर (header) अणु
		new_bh = ext2_xattr_cache_find(inode, header);
		अगर (new_bh) अणु
			/* We found an identical block in the cache. */
			अगर (new_bh == old_bh) अणु
				ea_bdebug(new_bh, "keeping this block");
			पूर्ण अन्यथा अणु
				/* The old block is released after updating
				   the inode.  */
				ea_bdebug(new_bh, "reusing block");

				error = dquot_alloc_block(inode, 1);
				अगर (error) अणु
					unlock_buffer(new_bh);
					जाओ cleanup;
				पूर्ण
				le32_add_cpu(&HDR(new_bh)->h_refcount, 1);
				ea_bdebug(new_bh, "refcount now=%d",
					le32_to_cpu(HDR(new_bh)->h_refcount));
			पूर्ण
			unlock_buffer(new_bh);
		पूर्ण अन्यथा अगर (old_bh && header == HDR(old_bh)) अणु
			/* Keep this block. No need to lock the block as we
			   करोn't need to change the reference count. */
			new_bh = old_bh;
			get_bh(new_bh);
			ext2_xattr_cache_insert(ea_block_cache, new_bh);
		पूर्ण अन्यथा अणु
			/* We need to allocate a new block */
			ext2_fsblk_t goal = ext2_group_first_block_no(sb,
						EXT2_I(inode)->i_block_group);
			पूर्णांक block = ext2_new_block(inode, goal, &error);
			अगर (error)
				जाओ cleanup;
			ea_idebug(inode, "creating block %d", block);

			new_bh = sb_getblk(sb, block);
			अगर (unlikely(!new_bh)) अणु
				ext2_मुक्त_blocks(inode, block, 1);
				mark_inode_dirty(inode);
				error = -ENOMEM;
				जाओ cleanup;
			पूर्ण
			lock_buffer(new_bh);
			स_नकल(new_bh->b_data, header, new_bh->b_size);
			set_buffer_uptodate(new_bh);
			unlock_buffer(new_bh);
			ext2_xattr_cache_insert(ea_block_cache, new_bh);
			
			ext2_xattr_update_super_block(sb);
		पूर्ण
		mark_buffer_dirty(new_bh);
		अगर (IS_SYNC(inode)) अणु
			sync_dirty_buffer(new_bh);
			error = -EIO;
			अगर (buffer_req(new_bh) && !buffer_uptodate(new_bh))
				जाओ cleanup;
		पूर्ण
	पूर्ण

	/* Update the inode. */
	EXT2_I(inode)->i_file_acl = new_bh ? new_bh->b_blocknr : 0;
	inode->i_स_समय = current_समय(inode);
	अगर (IS_SYNC(inode)) अणु
		error = sync_inode_metadata(inode, 1);
		/* In हाल sync failed due to ENOSPC the inode was actually
		 * written (only some dirty data were not) so we just proceed
		 * as अगर nothing happened and cleanup the unused block */
		अगर (error && error != -ENOSPC) अणु
			अगर (new_bh && new_bh != old_bh) अणु
				dquot_मुक्त_block_nodirty(inode, 1);
				mark_inode_dirty(inode);
			पूर्ण
			जाओ cleanup;
		पूर्ण
	पूर्ण अन्यथा
		mark_inode_dirty(inode);

	error = 0;
	अगर (old_bh && old_bh != new_bh) अणु
		/*
		 * If there was an old block and we are no दीर्घer using it,
		 * release the old block.
		 */
		lock_buffer(old_bh);
		अगर (HDR(old_bh)->h_refcount == cpu_to_le32(1)) अणु
			__u32 hash = le32_to_cpu(HDR(old_bh)->h_hash);

			/*
			 * This must happen under buffer lock क्रम
			 * ext2_xattr_set2() to reliably detect मुक्तd block
			 */
			mb_cache_entry_delete(ea_block_cache, hash,
					      old_bh->b_blocknr);
			/* Free the old block. */
			ea_bdebug(old_bh, "freeing");
			ext2_मुक्त_blocks(inode, old_bh->b_blocknr, 1);
			mark_inode_dirty(inode);
			/* We let our caller release old_bh, so we
			 * need to duplicate the buffer beक्रमe. */
			get_bh(old_bh);
			bक्रमget(old_bh);
		पूर्ण अन्यथा अणु
			/* Decrement the refcount only. */
			le32_add_cpu(&HDR(old_bh)->h_refcount, -1);
			dquot_मुक्त_block_nodirty(inode, 1);
			mark_inode_dirty(inode);
			mark_buffer_dirty(old_bh);
			ea_bdebug(old_bh, "refcount now=%d",
				le32_to_cpu(HDR(old_bh)->h_refcount));
		पूर्ण
		unlock_buffer(old_bh);
	पूर्ण

cleanup:
	brअन्यथा(new_bh);

	वापस error;
पूर्ण

/*
 * ext2_xattr_delete_inode()
 *
 * Free extended attribute resources associated with this inode. This
 * is called immediately beक्रमe an inode is मुक्तd.
 */
व्योम
ext2_xattr_delete_inode(काष्ठा inode *inode)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(inode->i_sb);

	/*
	 * We are the only ones holding inode reference. The xattr_sem should
	 * better be unlocked! We could as well just not acquire xattr_sem at
	 * all but this makes the code more futureproof. OTOH we need trylock
	 * here to aव्योम false-positive warning from lockdep about reclaim
	 * circular dependency.
	 */
	अगर (WARN_ON_ONCE(!करोwn_ग_लिखो_trylock(&EXT2_I(inode)->xattr_sem)))
		वापस;
	अगर (!EXT2_I(inode)->i_file_acl)
		जाओ cleanup;

	अगर (!ext2_data_block_valid(sbi, EXT2_I(inode)->i_file_acl, 1)) अणु
		ext2_error(inode->i_sb, "ext2_xattr_delete_inode",
			"inode %ld: xattr block %d is out of data blocks range",
			inode->i_ino, EXT2_I(inode)->i_file_acl);
		जाओ cleanup;
	पूर्ण

	bh = sb_bपढ़ो(inode->i_sb, EXT2_I(inode)->i_file_acl);
	अगर (!bh) अणु
		ext2_error(inode->i_sb, "ext2_xattr_delete_inode",
			"inode %ld: block %d read error", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		जाओ cleanup;
	पूर्ण
	ea_bdebug(bh, "b_count=%d", atomic_पढ़ो(&(bh->b_count)));
	अगर (!ext2_xattr_header_valid(HDR(bh))) अणु
		ext2_error(inode->i_sb, "ext2_xattr_delete_inode",
			"inode %ld: bad block %d", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		जाओ cleanup;
	पूर्ण
	lock_buffer(bh);
	अगर (HDR(bh)->h_refcount == cpu_to_le32(1)) अणु
		__u32 hash = le32_to_cpu(HDR(bh)->h_hash);

		/*
		 * This must happen under buffer lock क्रम ext2_xattr_set2() to
		 * reliably detect मुक्तd block
		 */
		mb_cache_entry_delete(EA_BLOCK_CACHE(inode), hash,
				      bh->b_blocknr);
		ext2_मुक्त_blocks(inode, EXT2_I(inode)->i_file_acl, 1);
		get_bh(bh);
		bक्रमget(bh);
		unlock_buffer(bh);
	पूर्ण अन्यथा अणु
		le32_add_cpu(&HDR(bh)->h_refcount, -1);
		ea_bdebug(bh, "refcount now=%d",
			le32_to_cpu(HDR(bh)->h_refcount));
		unlock_buffer(bh);
		mark_buffer_dirty(bh);
		अगर (IS_SYNC(inode))
			sync_dirty_buffer(bh);
		dquot_मुक्त_block_nodirty(inode, 1);
	पूर्ण
	EXT2_I(inode)->i_file_acl = 0;

cleanup:
	brअन्यथा(bh);
	up_ग_लिखो(&EXT2_I(inode)->xattr_sem);
पूर्ण

/*
 * ext2_xattr_cache_insert()
 *
 * Create a new entry in the extended attribute cache, and insert
 * it unless such an entry is alपढ़ोy in the cache.
 *
 * Returns 0, or a negative error number on failure.
 */
अटल पूर्णांक
ext2_xattr_cache_insert(काष्ठा mb_cache *cache, काष्ठा buffer_head *bh)
अणु
	__u32 hash = le32_to_cpu(HDR(bh)->h_hash);
	पूर्णांक error;

	error = mb_cache_entry_create(cache, GFP_NOFS, hash, bh->b_blocknr,
				      true);
	अगर (error) अणु
		अगर (error == -EBUSY) अणु
			ea_bdebug(bh, "already in cache");
			error = 0;
		पूर्ण
	पूर्ण अन्यथा
		ea_bdebug(bh, "inserting [%x]", (पूर्णांक)hash);
	वापस error;
पूर्ण

/*
 * ext2_xattr_cmp()
 *
 * Compare two extended attribute blocks क्रम equality.
 *
 * Returns 0 अगर the blocks are equal, 1 अगर they dअगरfer, and
 * a negative error number on errors.
 */
अटल पूर्णांक
ext2_xattr_cmp(काष्ठा ext2_xattr_header *header1,
	       काष्ठा ext2_xattr_header *header2)
अणु
	काष्ठा ext2_xattr_entry *entry1, *entry2;

	entry1 = ENTRY(header1+1);
	entry2 = ENTRY(header2+1);
	जबतक (!IS_LAST_ENTRY(entry1)) अणु
		अगर (IS_LAST_ENTRY(entry2))
			वापस 1;
		अगर (entry1->e_hash != entry2->e_hash ||
		    entry1->e_name_index != entry2->e_name_index ||
		    entry1->e_name_len != entry2->e_name_len ||
		    entry1->e_value_size != entry2->e_value_size ||
		    स_भेद(entry1->e_name, entry2->e_name, entry1->e_name_len))
			वापस 1;
		अगर (entry1->e_value_block != 0 || entry2->e_value_block != 0)
			वापस -EIO;
		अगर (स_भेद((अक्षर *)header1 + le16_to_cpu(entry1->e_value_offs),
			   (अक्षर *)header2 + le16_to_cpu(entry2->e_value_offs),
			   le32_to_cpu(entry1->e_value_size)))
			वापस 1;

		entry1 = EXT2_XATTR_NEXT(entry1);
		entry2 = EXT2_XATTR_NEXT(entry2);
	पूर्ण
	अगर (!IS_LAST_ENTRY(entry2))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * ext2_xattr_cache_find()
 *
 * Find an identical extended attribute block.
 *
 * Returns a locked buffer head to the block found, or शून्य अगर such
 * a block was not found or an error occurred.
 */
अटल काष्ठा buffer_head *
ext2_xattr_cache_find(काष्ठा inode *inode, काष्ठा ext2_xattr_header *header)
अणु
	__u32 hash = le32_to_cpu(header->h_hash);
	काष्ठा mb_cache_entry *ce;
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	अगर (!header->h_hash)
		वापस शून्य;  /* never share */
	ea_idebug(inode, "looking for cached blocks [%x]", (पूर्णांक)hash);
again:
	ce = mb_cache_entry_find_first(ea_block_cache, hash);
	जबतक (ce) अणु
		काष्ठा buffer_head *bh;

		bh = sb_bपढ़ो(inode->i_sb, ce->e_value);
		अगर (!bh) अणु
			ext2_error(inode->i_sb, "ext2_xattr_cache_find",
				"inode %ld: block %ld read error",
				inode->i_ino, (अचिन्हित दीर्घ) ce->e_value);
		पूर्ण अन्यथा अणु
			lock_buffer(bh);
			/*
			 * We have to be careful about races with मुक्तing or
			 * rehashing of xattr block. Once we hold buffer lock
			 * xattr block's state is stable so we can check
			 * whether the block got मुक्तd / rehashed or not.
			 * Since we unhash mbcache entry under buffer lock when
			 * मुक्तing / rehashing xattr block, checking whether
			 * entry is still hashed is reliable.
			 */
			अगर (hlist_bl_unhashed(&ce->e_hash_list)) अणु
				mb_cache_entry_put(ea_block_cache, ce);
				unlock_buffer(bh);
				brअन्यथा(bh);
				जाओ again;
			पूर्ण अन्यथा अगर (le32_to_cpu(HDR(bh)->h_refcount) >
				   EXT2_XATTR_REFCOUNT_MAX) अणु
				ea_idebug(inode, "block %ld refcount %d>%d",
					  (अचिन्हित दीर्घ) ce->e_value,
					  le32_to_cpu(HDR(bh)->h_refcount),
					  EXT2_XATTR_REFCOUNT_MAX);
			पूर्ण अन्यथा अगर (!ext2_xattr_cmp(header, HDR(bh))) अणु
				ea_bdebug(bh, "b_count=%d",
					  atomic_पढ़ो(&(bh->b_count)));
				mb_cache_entry_touch(ea_block_cache, ce);
				mb_cache_entry_put(ea_block_cache, ce);
				वापस bh;
			पूर्ण
			unlock_buffer(bh);
			brअन्यथा(bh);
		पूर्ण
		ce = mb_cache_entry_find_next(ea_block_cache, ce);
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा NAME_HASH_SHIFT 5
#घोषणा VALUE_HASH_SHIFT 16

/*
 * ext2_xattr_hash_entry()
 *
 * Compute the hash of an extended attribute.
 */
अटल अंतरभूत व्योम ext2_xattr_hash_entry(काष्ठा ext2_xattr_header *header,
					 काष्ठा ext2_xattr_entry *entry)
अणु
	__u32 hash = 0;
	अक्षर *name = entry->e_name;
	पूर्णांक n;

	क्रम (n=0; n < entry->e_name_len; n++) अणु
		hash = (hash << NAME_HASH_SHIFT) ^
		       (hash >> (8*माप(hash) - NAME_HASH_SHIFT)) ^
		       *name++;
	पूर्ण

	अगर (entry->e_value_block == 0 && entry->e_value_size != 0) अणु
		__le32 *value = (__le32 *)((अक्षर *)header +
			le16_to_cpu(entry->e_value_offs));
		क्रम (n = (le32_to_cpu(entry->e_value_size) +
		     EXT2_XATTR_ROUND) >> EXT2_XATTR_PAD_BITS; n; n--) अणु
			hash = (hash << VALUE_HASH_SHIFT) ^
			       (hash >> (8*माप(hash) - VALUE_HASH_SHIFT)) ^
			       le32_to_cpu(*value++);
		पूर्ण
	पूर्ण
	entry->e_hash = cpu_to_le32(hash);
पूर्ण

#अघोषित NAME_HASH_SHIFT
#अघोषित VALUE_HASH_SHIFT

#घोषणा BLOCK_HASH_SHIFT 16

/*
 * ext2_xattr_rehash()
 *
 * Re-compute the extended attribute hash value after an entry has changed.
 */
अटल व्योम ext2_xattr_rehash(काष्ठा ext2_xattr_header *header,
			      काष्ठा ext2_xattr_entry *entry)
अणु
	काष्ठा ext2_xattr_entry *here;
	__u32 hash = 0;
	
	ext2_xattr_hash_entry(header, entry);
	here = ENTRY(header+1);
	जबतक (!IS_LAST_ENTRY(here)) अणु
		अगर (!here->e_hash) अणु
			/* Block is not shared अगर an entry's hash value == 0 */
			hash = 0;
			अवरोध;
		पूर्ण
		hash = (hash << BLOCK_HASH_SHIFT) ^
		       (hash >> (8*माप(hash) - BLOCK_HASH_SHIFT)) ^
		       le32_to_cpu(here->e_hash);
		here = EXT2_XATTR_NEXT(here);
	पूर्ण
	header->h_hash = cpu_to_le32(hash);
पूर्ण

#अघोषित BLOCK_HASH_SHIFT

#घोषणा HASH_BUCKET_BITS 10

काष्ठा mb_cache *ext2_xattr_create_cache(व्योम)
अणु
	वापस mb_cache_create(HASH_BUCKET_BITS);
पूर्ण

व्योम ext2_xattr_destroy_cache(काष्ठा mb_cache *cache)
अणु
	अगर (cache)
		mb_cache_destroy(cache);
पूर्ण
