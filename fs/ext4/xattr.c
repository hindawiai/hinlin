<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext4/xattr.c
 *
 * Copyright (C) 2001-2003 Andreas Gruenbacher, <agruen@suse.de>
 *
 * Fix by Harrison Xing <harrison@mountainviewdata.com>.
 * Ext4 code with a lot of help from Eric Jarman <ejarman@acm.org>.
 * Extended attributes क्रम symlinks and special files added per
 *  suggestion of Luka Renko <luka.renko@hermes.si>.
 * xattr consolidation Copyright (c) 2004 James Morris <jmorris@redhat.com>,
 *  Red Hat Inc.
 * ea-in-inode support by Alex Tomas <alex@clusterfs.com> aka bzzz
 *  and Andreas Gruenbacher <agruen@suse.de>.
 */

/*
 * Extended attributes are stored directly in inodes (on file प्रणालीs with
 * inodes bigger than 128 bytes) and on additional disk blocks. The i_file_acl
 * field contains the block number अगर an inode uses an additional block. All
 * attributes must fit in the inode and one additional block. Blocks that
 * contain the identical set of attributes may be shared among several inodes.
 * Identical blocks are detected by keeping a cache of blocks that have
 * recently been accessed.
 *
 * The attributes in inodes and on blocks have a dअगरferent header; the entries
 * are stored in the same क्रमmat:
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
 * The header is followed by multiple entry descriptors. In disk blocks, the
 * entry descriptors are kept sorted. In inodes, they are unsorted. The
 * attribute values are aligned to the end of the block in no specअगरic order.
 *
 * Locking strategy
 * ----------------
 * EXT4_I(inode)->i_file_acl is रक्षित by EXT4_I(inode)->xattr_sem.
 * EA blocks are only changed अगर they are exclusive to an inode, so
 * holding xattr_sem also means that nothing but the EA block's reference
 * count can change. Multiple ग_लिखोrs to the same block are synchronized
 * by the buffer lock.
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/mbcache.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/iversion.h>
#समावेश "ext4_jbd2.h"
#समावेश "ext4.h"
#समावेश "xattr.h"
#समावेश "acl.h"

#अगर_घोषित EXT4_XATTR_DEBUG
# define ea_idebug(inode, fmt, ...)					\
	prपूर्णांकk(KERN_DEBUG "inode %s:%lu: " fmt "\n",			\
	       inode->i_sb->s_id, inode->i_ino, ##__VA_ARGS__)
# define ea_bdebug(bh, fmt, ...)					\
	prपूर्णांकk(KERN_DEBUG "block %pg:%lu: " fmt "\n",			\
	       bh->b_bdev, (अचिन्हित दीर्घ)bh->b_blocknr, ##__VA_ARGS__)
#अन्यथा
# define ea_idebug(inode, fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
# define ea_bdebug(bh, fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

अटल व्योम ext4_xattr_block_cache_insert(काष्ठा mb_cache *,
					  काष्ठा buffer_head *);
अटल काष्ठा buffer_head *
ext4_xattr_block_cache_find(काष्ठा inode *, काष्ठा ext4_xattr_header *,
			    काष्ठा mb_cache_entry **);
अटल __le32 ext4_xattr_hash_entry(अक्षर *name, माप_प्रकार name_len, __le32 *value,
				    माप_प्रकार value_count);
अटल व्योम ext4_xattr_rehash(काष्ठा ext4_xattr_header *);

अटल स्थिर काष्ठा xattr_handler * स्थिर ext4_xattr_handler_map[] = अणु
	[EXT4_XATTR_INDEX_USER]		     = &ext4_xattr_user_handler,
#अगर_घोषित CONFIG_EXT4_FS_POSIX_ACL
	[EXT4_XATTR_INDEX_POSIX_ACL_ACCESS]  = &posix_acl_access_xattr_handler,
	[EXT4_XATTR_INDEX_POSIX_ACL_DEFAULT] = &posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	[EXT4_XATTR_INDEX_TRUSTED]	     = &ext4_xattr_trusted_handler,
#अगर_घोषित CONFIG_EXT4_FS_SECURITY
	[EXT4_XATTR_INDEX_SECURITY]	     = &ext4_xattr_security_handler,
#पूर्ण_अगर
	[EXT4_XATTR_INDEX_HURD]		     = &ext4_xattr_hurd_handler,
पूर्ण;

स्थिर काष्ठा xattr_handler *ext4_xattr_handlers[] = अणु
	&ext4_xattr_user_handler,
	&ext4_xattr_trusted_handler,
#अगर_घोषित CONFIG_EXT4_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EXT4_FS_SECURITY
	&ext4_xattr_security_handler,
#पूर्ण_अगर
	&ext4_xattr_hurd_handler,
	शून्य
पूर्ण;

#घोषणा EA_BLOCK_CACHE(inode)	(((काष्ठा ext4_sb_info *) \
				inode->i_sb->s_fs_info)->s_ea_block_cache)

#घोषणा EA_INODE_CACHE(inode)	(((काष्ठा ext4_sb_info *) \
				inode->i_sb->s_fs_info)->s_ea_inode_cache)

अटल पूर्णांक
ext4_expand_inode_array(काष्ठा ext4_xattr_inode_array **ea_inode_array,
			काष्ठा inode *inode);

#अगर_घोषित CONFIG_LOCKDEP
व्योम ext4_xattr_inode_set_class(काष्ठा inode *ea_inode)
अणु
	lockdep_set_subclass(&ea_inode->i_rwsem, 1);
पूर्ण
#पूर्ण_अगर

अटल __le32 ext4_xattr_block_csum(काष्ठा inode *inode,
				    sector_t block_nr,
				    काष्ठा ext4_xattr_header *hdr)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__u32 csum;
	__le64 dsk_block_nr = cpu_to_le64(block_nr);
	__u32 dummy_csum = 0;
	पूर्णांक offset = दुरत्व(काष्ठा ext4_xattr_header, h_checksum);

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&dsk_block_nr,
			   माप(dsk_block_nr));
	csum = ext4_chksum(sbi, csum, (__u8 *)hdr, offset);
	csum = ext4_chksum(sbi, csum, (__u8 *)&dummy_csum, माप(dummy_csum));
	offset += माप(dummy_csum);
	csum = ext4_chksum(sbi, csum, (__u8 *)hdr + offset,
			   EXT4_BLOCK_SIZE(inode->i_sb) - offset);

	वापस cpu_to_le32(csum);
पूर्ण

अटल पूर्णांक ext4_xattr_block_csum_verअगरy(काष्ठा inode *inode,
					काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_xattr_header *hdr = BHDR(bh);
	पूर्णांक ret = 1;

	अगर (ext4_has_metadata_csum(inode->i_sb)) अणु
		lock_buffer(bh);
		ret = (hdr->h_checksum == ext4_xattr_block_csum(inode,
							bh->b_blocknr, hdr));
		unlock_buffer(bh);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ext4_xattr_block_csum_set(काष्ठा inode *inode,
				      काष्ठा buffer_head *bh)
अणु
	अगर (ext4_has_metadata_csum(inode->i_sb))
		BHDR(bh)->h_checksum = ext4_xattr_block_csum(inode,
						bh->b_blocknr, BHDR(bh));
पूर्ण

अटल अंतरभूत स्थिर काष्ठा xattr_handler *
ext4_xattr_handler(पूर्णांक name_index)
अणु
	स्थिर काष्ठा xattr_handler *handler = शून्य;

	अगर (name_index > 0 && name_index < ARRAY_SIZE(ext4_xattr_handler_map))
		handler = ext4_xattr_handler_map[name_index];
	वापस handler;
पूर्ण

अटल पूर्णांक
ext4_xattr_check_entries(काष्ठा ext4_xattr_entry *entry, व्योम *end,
			 व्योम *value_start)
अणु
	काष्ठा ext4_xattr_entry *e = entry;

	/* Find the end of the names list */
	जबतक (!IS_LAST_ENTRY(e)) अणु
		काष्ठा ext4_xattr_entry *next = EXT4_XATTR_NEXT(e);
		अगर ((व्योम *)next >= end)
			वापस -EFSCORRUPTED;
		अगर (strnlen(e->e_name, e->e_name_len) != e->e_name_len)
			वापस -EFSCORRUPTED;
		e = next;
	पूर्ण

	/* Check the values */
	जबतक (!IS_LAST_ENTRY(entry)) अणु
		u32 size = le32_to_cpu(entry->e_value_size);

		अगर (size > EXT4_XATTR_SIZE_MAX)
			वापस -EFSCORRUPTED;

		अगर (size != 0 && entry->e_value_inum == 0) अणु
			u16 offs = le16_to_cpu(entry->e_value_offs);
			व्योम *value;

			/*
			 * The value cannot overlap the names, and the value
			 * with padding cannot extend beyond 'end'.  Check both
			 * the padded and unpadded sizes, since the size may
			 * overflow to 0 when adding padding.
			 */
			अगर (offs > end - value_start)
				वापस -EFSCORRUPTED;
			value = value_start + offs;
			अगर (value < (व्योम *)e + माप(u32) ||
			    size > end - value ||
			    EXT4_XATTR_SIZE(size) > end - value)
				वापस -EFSCORRUPTED;
		पूर्ण
		entry = EXT4_XATTR_NEXT(entry);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
__ext4_xattr_check_block(काष्ठा inode *inode, काष्ठा buffer_head *bh,
			 स्थिर अक्षर *function, अचिन्हित पूर्णांक line)
अणु
	पूर्णांक error = -EFSCORRUPTED;

	अगर (BHDR(bh)->h_magic != cpu_to_le32(EXT4_XATTR_MAGIC) ||
	    BHDR(bh)->h_blocks != cpu_to_le32(1))
		जाओ errout;
	अगर (buffer_verअगरied(bh))
		वापस 0;

	error = -EFSBADCRC;
	अगर (!ext4_xattr_block_csum_verअगरy(inode, bh))
		जाओ errout;
	error = ext4_xattr_check_entries(BFIRST(bh), bh->b_data + bh->b_size,
					 bh->b_data);
errout:
	अगर (error)
		__ext4_error_inode(inode, function, line, 0, -error,
				   "corrupted xattr block %llu",
				   (अचिन्हित दीर्घ दीर्घ) bh->b_blocknr);
	अन्यथा
		set_buffer_verअगरied(bh);
	वापस error;
पूर्ण

#घोषणा ext4_xattr_check_block(inode, bh) \
	__ext4_xattr_check_block((inode), (bh),  __func__, __LINE__)


अटल पूर्णांक
__xattr_check_inode(काष्ठा inode *inode, काष्ठा ext4_xattr_ibody_header *header,
			 व्योम *end, स्थिर अक्षर *function, अचिन्हित पूर्णांक line)
अणु
	पूर्णांक error = -EFSCORRUPTED;

	अगर (end - (व्योम *)header < माप(*header) + माप(u32) ||
	    (header->h_magic != cpu_to_le32(EXT4_XATTR_MAGIC)))
		जाओ errout;
	error = ext4_xattr_check_entries(IFIRST(header), end, IFIRST(header));
errout:
	अगर (error)
		__ext4_error_inode(inode, function, line, 0, -error,
				   "corrupted in-inode xattr");
	वापस error;
पूर्ण

#घोषणा xattr_check_inode(inode, header, end) \
	__xattr_check_inode((inode), (header), (end), __func__, __LINE__)

अटल पूर्णांक
xattr_find_entry(काष्ठा inode *inode, काष्ठा ext4_xattr_entry **pentry,
		 व्योम *end, पूर्णांक name_index, स्थिर अक्षर *name, पूर्णांक sorted)
अणु
	काष्ठा ext4_xattr_entry *entry, *next;
	माप_प्रकार name_len;
	पूर्णांक cmp = 1;

	अगर (name == शून्य)
		वापस -EINVAL;
	name_len = म_माप(name);
	क्रम (entry = *pentry; !IS_LAST_ENTRY(entry); entry = next) अणु
		next = EXT4_XATTR_NEXT(entry);
		अगर ((व्योम *) next >= end) अणु
			EXT4_ERROR_INODE(inode, "corrupted xattr entries");
			वापस -EFSCORRUPTED;
		पूर्ण
		cmp = name_index - entry->e_name_index;
		अगर (!cmp)
			cmp = name_len - entry->e_name_len;
		अगर (!cmp)
			cmp = स_भेद(name, entry->e_name, name_len);
		अगर (cmp <= 0 && (sorted || cmp == 0))
			अवरोध;
	पूर्ण
	*pentry = entry;
	वापस cmp ? -ENODATA : 0;
पूर्ण

अटल u32
ext4_xattr_inode_hash(काष्ठा ext4_sb_info *sbi, स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	वापस ext4_chksum(sbi, sbi->s_csum_seed, buffer, size);
पूर्ण

अटल u64 ext4_xattr_inode_get_ref(काष्ठा inode *ea_inode)
अणु
	वापस ((u64)ea_inode->i_स_समय.tv_sec << 32) |
		(u32) inode_peek_iversion_raw(ea_inode);
पूर्ण

अटल व्योम ext4_xattr_inode_set_ref(काष्ठा inode *ea_inode, u64 ref_count)
अणु
	ea_inode->i_स_समय.tv_sec = (u32)(ref_count >> 32);
	inode_set_iversion_raw(ea_inode, ref_count & 0xffffffff);
पूर्ण

अटल u32 ext4_xattr_inode_get_hash(काष्ठा inode *ea_inode)
अणु
	वापस (u32)ea_inode->i_aसमय.tv_sec;
पूर्ण

अटल व्योम ext4_xattr_inode_set_hash(काष्ठा inode *ea_inode, u32 hash)
अणु
	ea_inode->i_aसमय.tv_sec = hash;
पूर्ण

/*
 * Read the EA value from an inode.
 */
अटल पूर्णांक ext4_xattr_inode_पढ़ो(काष्ठा inode *ea_inode, व्योम *buf, माप_प्रकार size)
अणु
	पूर्णांक blocksize = 1 << ea_inode->i_blkbits;
	पूर्णांक bh_count = (size + blocksize - 1) >> ea_inode->i_blkbits;
	पूर्णांक tail_size = (size % blocksize) ?: blocksize;
	काष्ठा buffer_head *bhs_अंतरभूत[8];
	काष्ठा buffer_head **bhs = bhs_अंतरभूत;
	पूर्णांक i, ret;

	अगर (bh_count > ARRAY_SIZE(bhs_अंतरभूत)) अणु
		bhs = kदो_स्मृति_array(bh_count, माप(*bhs), GFP_NOFS);
		अगर (!bhs)
			वापस -ENOMEM;
	पूर्ण

	ret = ext4_bपढ़ो_batch(ea_inode, 0 /* block */, bh_count,
			       true /* रुको */, bhs);
	अगर (ret)
		जाओ मुक्त_bhs;

	क्रम (i = 0; i < bh_count; i++) अणु
		/* There shouldn't be any holes in ea_inode. */
		अगर (!bhs[i]) अणु
			ret = -EFSCORRUPTED;
			जाओ put_bhs;
		पूर्ण
		स_नकल((अक्षर *)buf + blocksize * i, bhs[i]->b_data,
		       i < bh_count - 1 ? blocksize : tail_size);
	पूर्ण
	ret = 0;
put_bhs:
	क्रम (i = 0; i < bh_count; i++)
		brअन्यथा(bhs[i]);
मुक्त_bhs:
	अगर (bhs != bhs_अंतरभूत)
		kमुक्त(bhs);
	वापस ret;
पूर्ण

#घोषणा EXT4_XATTR_INODE_GET_PARENT(inode) ((__u32)(inode)->i_mसमय.tv_sec)

अटल पूर्णांक ext4_xattr_inode_iget(काष्ठा inode *parent, अचिन्हित दीर्घ ea_ino,
				 u32 ea_inode_hash, काष्ठा inode **ea_inode)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;

	inode = ext4_iget(parent->i_sb, ea_ino, EXT4_IGET_NORMAL);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		ext4_error(parent->i_sb,
			   "error while reading EA inode %lu err=%d", ea_ino,
			   err);
		वापस err;
	पूर्ण

	अगर (is_bad_inode(inode)) अणु
		ext4_error(parent->i_sb,
			   "error while reading EA inode %lu is_bad_inode",
			   ea_ino);
		err = -EIO;
		जाओ error;
	पूर्ण

	अगर (!(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL)) अणु
		ext4_error(parent->i_sb,
			   "EA inode %lu does not have EXT4_EA_INODE_FL flag",
			    ea_ino);
		err = -EINVAL;
		जाओ error;
	पूर्ण

	ext4_xattr_inode_set_class(inode);

	/*
	 * Check whether this is an old Lustre-style xattr inode. Lustre
	 * implementation करोes not have hash validation, rather it has a
	 * backpoपूर्णांकer from ea_inode to the parent inode.
	 */
	अगर (ea_inode_hash != ext4_xattr_inode_get_hash(inode) &&
	    EXT4_XATTR_INODE_GET_PARENT(inode) == parent->i_ino &&
	    inode->i_generation == parent->i_generation) अणु
		ext4_set_inode_state(inode, EXT4_STATE_LUSTRE_EA_INODE);
		ext4_xattr_inode_set_ref(inode, 1);
	पूर्ण अन्यथा अणु
		inode_lock(inode);
		inode->i_flags |= S_NOQUOTA;
		inode_unlock(inode);
	पूर्ण

	*ea_inode = inode;
	वापस 0;
error:
	iput(inode);
	वापस err;
पूर्ण

अटल पूर्णांक
ext4_xattr_inode_verअगरy_hashes(काष्ठा inode *ea_inode,
			       काष्ठा ext4_xattr_entry *entry, व्योम *buffer,
			       माप_प्रकार size)
अणु
	u32 hash;

	/* Verअगरy stored hash matches calculated hash. */
	hash = ext4_xattr_inode_hash(EXT4_SB(ea_inode->i_sb), buffer, size);
	अगर (hash != ext4_xattr_inode_get_hash(ea_inode))
		वापस -EFSCORRUPTED;

	अगर (entry) अणु
		__le32 e_hash, पंचांगp_data;

		/* Verअगरy entry hash. */
		पंचांगp_data = cpu_to_le32(hash);
		e_hash = ext4_xattr_hash_entry(entry->e_name, entry->e_name_len,
					       &पंचांगp_data, 1);
		अगर (e_hash != entry->e_hash)
			वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Read xattr value from the EA inode.
 */
अटल पूर्णांक
ext4_xattr_inode_get(काष्ठा inode *inode, काष्ठा ext4_xattr_entry *entry,
		     व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा mb_cache *ea_inode_cache = EA_INODE_CACHE(inode);
	काष्ठा inode *ea_inode;
	पूर्णांक err;

	err = ext4_xattr_inode_iget(inode, le32_to_cpu(entry->e_value_inum),
				    le32_to_cpu(entry->e_hash), &ea_inode);
	अगर (err) अणु
		ea_inode = शून्य;
		जाओ out;
	पूर्ण

	अगर (i_size_पढ़ो(ea_inode) != size) अणु
		ext4_warning_inode(ea_inode,
				   "ea_inode file size=%llu entry size=%zu",
				   i_size_पढ़ो(ea_inode), size);
		err = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	err = ext4_xattr_inode_पढ़ो(ea_inode, buffer, size);
	अगर (err)
		जाओ out;

	अगर (!ext4_test_inode_state(ea_inode, EXT4_STATE_LUSTRE_EA_INODE)) अणु
		err = ext4_xattr_inode_verअगरy_hashes(ea_inode, entry, buffer,
						     size);
		अगर (err) अणु
			ext4_warning_inode(ea_inode,
					   "EA inode hash validation failed");
			जाओ out;
		पूर्ण

		अगर (ea_inode_cache)
			mb_cache_entry_create(ea_inode_cache, GFP_NOFS,
					ext4_xattr_inode_get_hash(ea_inode),
					ea_inode->i_ino, true /* reusable */);
	पूर्ण
out:
	iput(ea_inode);
	वापस err;
पूर्ण

अटल पूर्णांक
ext4_xattr_block_get(काष्ठा inode *inode, पूर्णांक name_index, स्थिर अक्षर *name,
		     व्योम *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext4_xattr_entry *entry;
	माप_प्रकार size;
	व्योम *end;
	पूर्णांक error;
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	ea_idebug(inode, "name=%d.%s, buffer=%p, buffer_size=%ld",
		  name_index, name, buffer, (दीर्घ)buffer_size);

	अगर (!EXT4_I(inode)->i_file_acl)
		वापस -ENODATA;
	ea_idebug(inode, "reading block %llu",
		  (अचिन्हित दीर्घ दीर्घ)EXT4_I(inode)->i_file_acl);
	bh = ext4_sb_bपढ़ो(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_पढ़ो(&(bh->b_count)), le32_to_cpu(BHDR(bh)->h_refcount));
	error = ext4_xattr_check_block(inode, bh);
	अगर (error)
		जाओ cleanup;
	ext4_xattr_block_cache_insert(ea_block_cache, bh);
	entry = BFIRST(bh);
	end = bh->b_data + bh->b_size;
	error = xattr_find_entry(inode, &entry, end, name_index, name, 1);
	अगर (error)
		जाओ cleanup;
	size = le32_to_cpu(entry->e_value_size);
	error = -दुस्फल;
	अगर (unlikely(size > EXT4_XATTR_SIZE_MAX))
		जाओ cleanup;
	अगर (buffer) अणु
		अगर (size > buffer_size)
			जाओ cleanup;
		अगर (entry->e_value_inum) अणु
			error = ext4_xattr_inode_get(inode, entry, buffer,
						     size);
			अगर (error)
				जाओ cleanup;
		पूर्ण अन्यथा अणु
			u16 offset = le16_to_cpu(entry->e_value_offs);
			व्योम *p = bh->b_data + offset;

			अगर (unlikely(p + size > end))
				जाओ cleanup;
			स_नकल(buffer, p, size);
		पूर्ण
	पूर्ण
	error = size;

cleanup:
	brअन्यथा(bh);
	वापस error;
पूर्ण

पूर्णांक
ext4_xattr_ibody_get(काष्ठा inode *inode, पूर्णांक name_index, स्थिर अक्षर *name,
		     व्योम *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा ext4_inode *raw_inode;
	काष्ठा ext4_iloc iloc;
	माप_प्रकार size;
	व्योम *end;
	पूर्णांक error;

	अगर (!ext4_test_inode_state(inode, EXT4_STATE_XATTR))
		वापस -ENODATA;
	error = ext4_get_inode_loc(inode, &iloc);
	अगर (error)
		वापस error;
	raw_inode = ext4_raw_inode(&iloc);
	header = IHDR(inode, raw_inode);
	end = (व्योम *)raw_inode + EXT4_SB(inode->i_sb)->s_inode_size;
	error = xattr_check_inode(inode, header, end);
	अगर (error)
		जाओ cleanup;
	entry = IFIRST(header);
	error = xattr_find_entry(inode, &entry, end, name_index, name, 0);
	अगर (error)
		जाओ cleanup;
	size = le32_to_cpu(entry->e_value_size);
	error = -दुस्फल;
	अगर (unlikely(size > EXT4_XATTR_SIZE_MAX))
		जाओ cleanup;
	अगर (buffer) अणु
		अगर (size > buffer_size)
			जाओ cleanup;
		अगर (entry->e_value_inum) अणु
			error = ext4_xattr_inode_get(inode, entry, buffer,
						     size);
			अगर (error)
				जाओ cleanup;
		पूर्ण अन्यथा अणु
			u16 offset = le16_to_cpu(entry->e_value_offs);
			व्योम *p = (व्योम *)IFIRST(header) + offset;

			अगर (unlikely(p + size > end))
				जाओ cleanup;
			स_नकल(buffer, p, size);
		पूर्ण
	पूर्ण
	error = size;

cleanup:
	brअन्यथा(iloc.bh);
	वापस error;
पूर्ण

/*
 * ext4_xattr_get()
 *
 * Copy an extended attribute पूर्णांकo the buffer
 * provided, or compute the buffer size required.
 * Buffer is शून्य to compute the size of the buffer required.
 *
 * Returns a negative error number on failure, or the number of bytes
 * used / required on success.
 */
पूर्णांक
ext4_xattr_get(काष्ठा inode *inode, पूर्णांक name_index, स्थिर अक्षर *name,
	       व्योम *buffer, माप_प्रकार buffer_size)
अणु
	पूर्णांक error;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	अगर (म_माप(name) > 255)
		वापस -दुस्फल;

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
	error = ext4_xattr_ibody_get(inode, name_index, name, buffer,
				     buffer_size);
	अगर (error == -ENODATA)
		error = ext4_xattr_block_get(inode, name_index, name, buffer,
					     buffer_size);
	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	वापस error;
पूर्ण

अटल पूर्णांक
ext4_xattr_list_entries(काष्ठा dentry *dentry, काष्ठा ext4_xattr_entry *entry,
			अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	माप_प्रकार rest = buffer_size;

	क्रम (; !IS_LAST_ENTRY(entry); entry = EXT4_XATTR_NEXT(entry)) अणु
		स्थिर काष्ठा xattr_handler *handler =
			ext4_xattr_handler(entry->e_name_index);

		अगर (handler && (!handler->list || handler->list(dentry))) अणु
			स्थिर अक्षर *prefix = handler->prefix ?: handler->name;
			माप_प्रकार prefix_len = म_माप(prefix);
			माप_प्रकार size = prefix_len + entry->e_name_len + 1;

			अगर (buffer) अणु
				अगर (size > rest)
					वापस -दुस्फल;
				स_नकल(buffer, prefix, prefix_len);
				buffer += prefix_len;
				स_नकल(buffer, entry->e_name, entry->e_name_len);
				buffer += entry->e_name_len;
				*buffer++ = 0;
			पूर्ण
			rest -= size;
		पूर्ण
	पूर्ण
	वापस buffer_size - rest;  /* total size */
पूर्ण

अटल पूर्णांक
ext4_xattr_block_list(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक error;

	ea_idebug(inode, "buffer=%p, buffer_size=%ld",
		  buffer, (दीर्घ)buffer_size);

	अगर (!EXT4_I(inode)->i_file_acl)
		वापस 0;
	ea_idebug(inode, "reading block %llu",
		  (अचिन्हित दीर्घ दीर्घ)EXT4_I(inode)->i_file_acl);
	bh = ext4_sb_bपढ़ो(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_पढ़ो(&(bh->b_count)), le32_to_cpu(BHDR(bh)->h_refcount));
	error = ext4_xattr_check_block(inode, bh);
	अगर (error)
		जाओ cleanup;
	ext4_xattr_block_cache_insert(EA_BLOCK_CACHE(inode), bh);
	error = ext4_xattr_list_entries(dentry, BFIRST(bh), buffer,
					buffer_size);
cleanup:
	brअन्यथा(bh);
	वापस error;
पूर्ण

अटल पूर्णांक
ext4_xattr_ibody_list(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_inode *raw_inode;
	काष्ठा ext4_iloc iloc;
	व्योम *end;
	पूर्णांक error;

	अगर (!ext4_test_inode_state(inode, EXT4_STATE_XATTR))
		वापस 0;
	error = ext4_get_inode_loc(inode, &iloc);
	अगर (error)
		वापस error;
	raw_inode = ext4_raw_inode(&iloc);
	header = IHDR(inode, raw_inode);
	end = (व्योम *)raw_inode + EXT4_SB(inode->i_sb)->s_inode_size;
	error = xattr_check_inode(inode, header, end);
	अगर (error)
		जाओ cleanup;
	error = ext4_xattr_list_entries(dentry, IFIRST(header),
					buffer, buffer_size);

cleanup:
	brअन्यथा(iloc.bh);
	वापस error;
पूर्ण

/*
 * Inode operation listxattr()
 *
 * d_inode(dentry)->i_rwsem: करोn't care
 *
 * Copy a list of attribute names पूर्णांकo the buffer
 * provided, or compute the buffer size required.
 * Buffer is शून्य to compute the size of the buffer required.
 *
 * Returns a negative error number on failure, or the number of bytes
 * used / required on success.
 */
sमाप_प्रकार
ext4_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	पूर्णांक ret, ret2;

	करोwn_पढ़ो(&EXT4_I(d_inode(dentry))->xattr_sem);
	ret = ret2 = ext4_xattr_ibody_list(dentry, buffer, buffer_size);
	अगर (ret < 0)
		जाओ errout;
	अगर (buffer) अणु
		buffer += ret;
		buffer_size -= ret;
	पूर्ण
	ret = ext4_xattr_block_list(dentry, buffer, buffer_size);
	अगर (ret < 0)
		जाओ errout;
	ret += ret2;
errout:
	up_पढ़ो(&EXT4_I(d_inode(dentry))->xattr_sem);
	वापस ret;
पूर्ण

/*
 * If the EXT4_FEATURE_COMPAT_EXT_ATTR feature of this file प्रणाली is
 * not set, set it.
 */
अटल व्योम ext4_xattr_update_super_block(handle_t *handle,
					  काष्ठा super_block *sb)
अणु
	अगर (ext4_has_feature_xattr(sb))
		वापस;

	BUFFER_TRACE(EXT4_SB(sb)->s_sbh, "get_write_access");
	अगर (ext4_journal_get_ग_लिखो_access(handle, EXT4_SB(sb)->s_sbh) == 0) अणु
		lock_buffer(EXT4_SB(sb)->s_sbh);
		ext4_set_feature_xattr(sb);
		ext4_superblock_csum_set(sb);
		unlock_buffer(EXT4_SB(sb)->s_sbh);
		ext4_handle_dirty_metadata(handle, शून्य, EXT4_SB(sb)->s_sbh);
	पूर्ण
पूर्ण

पूर्णांक ext4_get_inode_usage(काष्ठा inode *inode, qमाप_प्रकार *usage)
अणु
	काष्ठा ext4_iloc iloc = अणु .bh = शून्य पूर्ण;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext4_inode *raw_inode;
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_xattr_entry *entry;
	qमाप_प्रकार ea_inode_refs = 0;
	व्योम *end;
	पूर्णांक ret;

	lockdep_निश्चित_held_पढ़ो(&EXT4_I(inode)->xattr_sem);

	अगर (ext4_test_inode_state(inode, EXT4_STATE_XATTR)) अणु
		ret = ext4_get_inode_loc(inode, &iloc);
		अगर (ret)
			जाओ out;
		raw_inode = ext4_raw_inode(&iloc);
		header = IHDR(inode, raw_inode);
		end = (व्योम *)raw_inode + EXT4_SB(inode->i_sb)->s_inode_size;
		ret = xattr_check_inode(inode, header, end);
		अगर (ret)
			जाओ out;

		क्रम (entry = IFIRST(header); !IS_LAST_ENTRY(entry);
		     entry = EXT4_XATTR_NEXT(entry))
			अगर (entry->e_value_inum)
				ea_inode_refs++;
	पूर्ण

	अगर (EXT4_I(inode)->i_file_acl) अणु
		bh = ext4_sb_bपढ़ो(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
		अगर (IS_ERR(bh)) अणु
			ret = PTR_ERR(bh);
			bh = शून्य;
			जाओ out;
		पूर्ण

		ret = ext4_xattr_check_block(inode, bh);
		अगर (ret)
			जाओ out;

		क्रम (entry = BFIRST(bh); !IS_LAST_ENTRY(entry);
		     entry = EXT4_XATTR_NEXT(entry))
			अगर (entry->e_value_inum)
				ea_inode_refs++;
	पूर्ण
	*usage = ea_inode_refs + 1;
	ret = 0;
out:
	brअन्यथा(iloc.bh);
	brअन्यथा(bh);
	वापस ret;
पूर्ण

अटल अंतरभूत माप_प्रकार round_up_cluster(काष्ठा inode *inode, माप_प्रकार length)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	माप_प्रकार cluster_size = 1 << (EXT4_SB(sb)->s_cluster_bits +
				    inode->i_blkbits);
	माप_प्रकार mask = ~(cluster_size - 1);

	वापस (length + cluster_size - 1) & mask;
पूर्ण

अटल पूर्णांक ext4_xattr_inode_alloc_quota(काष्ठा inode *inode, माप_प्रकार len)
अणु
	पूर्णांक err;

	err = dquot_alloc_inode(inode);
	अगर (err)
		वापस err;
	err = dquot_alloc_space_nodirty(inode, round_up_cluster(inode, len));
	अगर (err)
		dquot_मुक्त_inode(inode);
	वापस err;
पूर्ण

अटल व्योम ext4_xattr_inode_मुक्त_quota(काष्ठा inode *parent,
					काष्ठा inode *ea_inode,
					माप_प्रकार len)
अणु
	अगर (ea_inode &&
	    ext4_test_inode_state(ea_inode, EXT4_STATE_LUSTRE_EA_INODE))
		वापस;
	dquot_मुक्त_space_nodirty(parent, round_up_cluster(parent, len));
	dquot_मुक्त_inode(parent);
पूर्ण

पूर्णांक __ext4_xattr_set_credits(काष्ठा super_block *sb, काष्ठा inode *inode,
			     काष्ठा buffer_head *block_bh, माप_प्रकार value_len,
			     bool is_create)
अणु
	पूर्णांक credits;
	पूर्णांक blocks;

	/*
	 * 1) Owner inode update
	 * 2) Ref count update on old xattr block
	 * 3) new xattr block
	 * 4) block biपंचांगap update क्रम new xattr block
	 * 5) group descriptor क्रम new xattr block
	 * 6) block biपंचांगap update क्रम old xattr block
	 * 7) group descriptor क्रम old block
	 *
	 * 6 & 7 can happen अगर we have two racing thपढ़ोs T_a and T_b
	 * which are each trying to set an xattr on inodes I_a and I_b
	 * which were both initially sharing an xattr block.
	 */
	credits = 7;

	/* Quota updates. */
	credits += EXT4_MAXQUOTAS_TRANS_BLOCKS(sb);

	/*
	 * In हाल of अंतरभूत data, we may push out the data to a block,
	 * so we need to reserve credits क्रम this eventuality
	 */
	अगर (inode && ext4_has_अंतरभूत_data(inode))
		credits += ext4_ग_लिखोpage_trans_blocks(inode) + 1;

	/* We are करोne अगर ea_inode feature is not enabled. */
	अगर (!ext4_has_feature_ea_inode(sb))
		वापस credits;

	/* New ea_inode, inode map, block biपंचांगap, group descriptor. */
	credits += 4;

	/* Data blocks. */
	blocks = (value_len + sb->s_blocksize - 1) >> sb->s_blocksize_bits;

	/* Indirection block or one level of extent tree. */
	blocks += 1;

	/* Block biपंचांगap and group descriptor updates क्रम each block. */
	credits += blocks * 2;

	/* Blocks themselves. */
	credits += blocks;

	अगर (!is_create) अणु
		/* Dereference ea_inode holding old xattr value.
		 * Old ea_inode, inode map, block biपंचांगap, group descriptor.
		 */
		credits += 4;

		/* Data blocks क्रम old ea_inode. */
		blocks = XATTR_SIZE_MAX >> sb->s_blocksize_bits;

		/* Indirection block or one level of extent tree क्रम old
		 * ea_inode.
		 */
		blocks += 1;

		/* Block biपंचांगap and group descriptor updates क्रम each block. */
		credits += blocks * 2;
	पूर्ण

	/* We may need to clone the existing xattr block in which हाल we need
	 * to increment ref counts क्रम existing ea_inodes referenced by it.
	 */
	अगर (block_bh) अणु
		काष्ठा ext4_xattr_entry *entry = BFIRST(block_bh);

		क्रम (; !IS_LAST_ENTRY(entry); entry = EXT4_XATTR_NEXT(entry))
			अगर (entry->e_value_inum)
				/* Ref count update on ea_inode. */
				credits += 1;
	पूर्ण
	वापस credits;
पूर्ण

अटल पूर्णांक ext4_xattr_inode_update_ref(handle_t *handle, काष्ठा inode *ea_inode,
				       पूर्णांक ref_change)
अणु
	काष्ठा mb_cache *ea_inode_cache = EA_INODE_CACHE(ea_inode);
	काष्ठा ext4_iloc iloc;
	s64 ref_count;
	u32 hash;
	पूर्णांक ret;

	inode_lock(ea_inode);

	ret = ext4_reserve_inode_ग_लिखो(handle, ea_inode, &iloc);
	अगर (ret)
		जाओ out;

	ref_count = ext4_xattr_inode_get_ref(ea_inode);
	ref_count += ref_change;
	ext4_xattr_inode_set_ref(ea_inode, ref_count);

	अगर (ref_change > 0) अणु
		WARN_ONCE(ref_count <= 0, "EA inode %lu ref_count=%lld",
			  ea_inode->i_ino, ref_count);

		अगर (ref_count == 1) अणु
			WARN_ONCE(ea_inode->i_nlink, "EA inode %lu i_nlink=%u",
				  ea_inode->i_ino, ea_inode->i_nlink);

			set_nlink(ea_inode, 1);
			ext4_orphan_del(handle, ea_inode);

			अगर (ea_inode_cache) अणु
				hash = ext4_xattr_inode_get_hash(ea_inode);
				mb_cache_entry_create(ea_inode_cache,
						      GFP_NOFS, hash,
						      ea_inode->i_ino,
						      true /* reusable */);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ONCE(ref_count < 0, "EA inode %lu ref_count=%lld",
			  ea_inode->i_ino, ref_count);

		अगर (ref_count == 0) अणु
			WARN_ONCE(ea_inode->i_nlink != 1,
				  "EA inode %lu i_nlink=%u",
				  ea_inode->i_ino, ea_inode->i_nlink);

			clear_nlink(ea_inode);
			ext4_orphan_add(handle, ea_inode);

			अगर (ea_inode_cache) अणु
				hash = ext4_xattr_inode_get_hash(ea_inode);
				mb_cache_entry_delete(ea_inode_cache, hash,
						      ea_inode->i_ino);
			पूर्ण
		पूर्ण
	पूर्ण

	ret = ext4_mark_iloc_dirty(handle, ea_inode, &iloc);
	अगर (ret)
		ext4_warning_inode(ea_inode,
				   "ext4_mark_iloc_dirty() failed ret=%d", ret);
out:
	inode_unlock(ea_inode);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_xattr_inode_inc_ref(handle_t *handle, काष्ठा inode *ea_inode)
अणु
	वापस ext4_xattr_inode_update_ref(handle, ea_inode, 1);
पूर्ण

अटल पूर्णांक ext4_xattr_inode_dec_ref(handle_t *handle, काष्ठा inode *ea_inode)
अणु
	वापस ext4_xattr_inode_update_ref(handle, ea_inode, -1);
पूर्ण

अटल पूर्णांक ext4_xattr_inode_inc_ref_all(handle_t *handle, काष्ठा inode *parent,
					काष्ठा ext4_xattr_entry *first)
अणु
	काष्ठा inode *ea_inode;
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा ext4_xattr_entry *failed_entry;
	अचिन्हित पूर्णांक ea_ino;
	पूर्णांक err, saved_err;

	क्रम (entry = first; !IS_LAST_ENTRY(entry);
	     entry = EXT4_XATTR_NEXT(entry)) अणु
		अगर (!entry->e_value_inum)
			जारी;
		ea_ino = le32_to_cpu(entry->e_value_inum);
		err = ext4_xattr_inode_iget(parent, ea_ino,
					    le32_to_cpu(entry->e_hash),
					    &ea_inode);
		अगर (err)
			जाओ cleanup;
		err = ext4_xattr_inode_inc_ref(handle, ea_inode);
		अगर (err) अणु
			ext4_warning_inode(ea_inode, "inc ref error %d", err);
			iput(ea_inode);
			जाओ cleanup;
		पूर्ण
		iput(ea_inode);
	पूर्ण
	वापस 0;

cleanup:
	saved_err = err;
	failed_entry = entry;

	क्रम (entry = first; entry != failed_entry;
	     entry = EXT4_XATTR_NEXT(entry)) अणु
		अगर (!entry->e_value_inum)
			जारी;
		ea_ino = le32_to_cpu(entry->e_value_inum);
		err = ext4_xattr_inode_iget(parent, ea_ino,
					    le32_to_cpu(entry->e_hash),
					    &ea_inode);
		अगर (err) अणु
			ext4_warning(parent->i_sb,
				     "cleanup ea_ino %u iget error %d", ea_ino,
				     err);
			जारी;
		पूर्ण
		err = ext4_xattr_inode_dec_ref(handle, ea_inode);
		अगर (err)
			ext4_warning_inode(ea_inode, "cleanup dec ref error %d",
					   err);
		iput(ea_inode);
	पूर्ण
	वापस saved_err;
पूर्ण

अटल पूर्णांक ext4_xattr_restart_fn(handle_t *handle, काष्ठा inode *inode,
			काष्ठा buffer_head *bh, bool block_csum, bool dirty)
अणु
	पूर्णांक error;

	अगर (bh && dirty) अणु
		अगर (block_csum)
			ext4_xattr_block_csum_set(inode, bh);
		error = ext4_handle_dirty_metadata(handle, शून्य, bh);
		अगर (error) अणु
			ext4_warning(inode->i_sb, "Handle metadata (error %d)",
				     error);
			वापस error;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
ext4_xattr_inode_dec_ref_all(handle_t *handle, काष्ठा inode *parent,
			     काष्ठा buffer_head *bh,
			     काष्ठा ext4_xattr_entry *first, bool block_csum,
			     काष्ठा ext4_xattr_inode_array **ea_inode_array,
			     पूर्णांक extra_credits, bool skip_quota)
अणु
	काष्ठा inode *ea_inode;
	काष्ठा ext4_xattr_entry *entry;
	bool dirty = false;
	अचिन्हित पूर्णांक ea_ino;
	पूर्णांक err;
	पूर्णांक credits;

	/* One credit क्रम dec ref on ea_inode, one क्रम orphan list addition, */
	credits = 2 + extra_credits;

	क्रम (entry = first; !IS_LAST_ENTRY(entry);
	     entry = EXT4_XATTR_NEXT(entry)) अणु
		अगर (!entry->e_value_inum)
			जारी;
		ea_ino = le32_to_cpu(entry->e_value_inum);
		err = ext4_xattr_inode_iget(parent, ea_ino,
					    le32_to_cpu(entry->e_hash),
					    &ea_inode);
		अगर (err)
			जारी;

		err = ext4_expand_inode_array(ea_inode_array, ea_inode);
		अगर (err) अणु
			ext4_warning_inode(ea_inode,
					   "Expand inode array err=%d", err);
			iput(ea_inode);
			जारी;
		पूर्ण

		err = ext4_journal_ensure_credits_fn(handle, credits, credits,
			ext4_मुक्त_metadata_revoke_credits(parent->i_sb, 1),
			ext4_xattr_restart_fn(handle, parent, bh, block_csum,
					      dirty));
		अगर (err < 0) अणु
			ext4_warning_inode(ea_inode, "Ensure credits err=%d",
					   err);
			जारी;
		पूर्ण
		अगर (err > 0) अणु
			err = ext4_journal_get_ग_लिखो_access(handle, bh);
			अगर (err) अणु
				ext4_warning_inode(ea_inode,
						"Re-get write access err=%d",
						err);
				जारी;
			पूर्ण
		पूर्ण

		err = ext4_xattr_inode_dec_ref(handle, ea_inode);
		अगर (err) अणु
			ext4_warning_inode(ea_inode, "ea_inode dec ref err=%d",
					   err);
			जारी;
		पूर्ण

		अगर (!skip_quota)
			ext4_xattr_inode_मुक्त_quota(parent, ea_inode,
					      le32_to_cpu(entry->e_value_size));

		/*
		 * Forget about ea_inode within the same transaction that
		 * decrements the ref count. This aव्योमs duplicate decrements in
		 * हाल the rest of the work spills over to subsequent
		 * transactions.
		 */
		entry->e_value_inum = 0;
		entry->e_value_size = 0;

		dirty = true;
	पूर्ण

	अगर (dirty) अणु
		/*
		 * Note that we are deliberately skipping csum calculation क्रम
		 * the final update because we करो not expect any journal
		 * restarts until xattr block is मुक्तd.
		 */

		err = ext4_handle_dirty_metadata(handle, शून्य, bh);
		अगर (err)
			ext4_warning_inode(parent,
					   "handle dirty metadata err=%d", err);
	पूर्ण
पूर्ण

/*
 * Release the xattr block BH: If the reference count is > 1, decrement it;
 * otherwise मुक्त the block.
 */
अटल व्योम
ext4_xattr_release_block(handle_t *handle, काष्ठा inode *inode,
			 काष्ठा buffer_head *bh,
			 काष्ठा ext4_xattr_inode_array **ea_inode_array,
			 पूर्णांक extra_credits)
अणु
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);
	u32 hash, ref;
	पूर्णांक error = 0;

	BUFFER_TRACE(bh, "get_write_access");
	error = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (error)
		जाओ out;

	lock_buffer(bh);
	hash = le32_to_cpu(BHDR(bh)->h_hash);
	ref = le32_to_cpu(BHDR(bh)->h_refcount);
	अगर (ref == 1) अणु
		ea_bdebug(bh, "refcount now=0; freeing");
		/*
		 * This must happen under buffer lock क्रम
		 * ext4_xattr_block_set() to reliably detect मुक्तd block
		 */
		अगर (ea_block_cache)
			mb_cache_entry_delete(ea_block_cache, hash,
					      bh->b_blocknr);
		get_bh(bh);
		unlock_buffer(bh);

		अगर (ext4_has_feature_ea_inode(inode->i_sb))
			ext4_xattr_inode_dec_ref_all(handle, inode, bh,
						     BFIRST(bh),
						     true /* block_csum */,
						     ea_inode_array,
						     extra_credits,
						     true /* skip_quota */);
		ext4_मुक्त_blocks(handle, inode, bh, 0, 1,
				 EXT4_FREE_BLOCKS_METADATA |
				 EXT4_FREE_BLOCKS_FORGET);
	पूर्ण अन्यथा अणु
		ref--;
		BHDR(bh)->h_refcount = cpu_to_le32(ref);
		अगर (ref == EXT4_XATTR_REFCOUNT_MAX - 1) अणु
			काष्ठा mb_cache_entry *ce;

			अगर (ea_block_cache) अणु
				ce = mb_cache_entry_get(ea_block_cache, hash,
							bh->b_blocknr);
				अगर (ce) अणु
					ce->e_reusable = 1;
					mb_cache_entry_put(ea_block_cache, ce);
				पूर्ण
			पूर्ण
		पूर्ण

		ext4_xattr_block_csum_set(inode, bh);
		/*
		 * Beware of this ugliness: Releasing of xattr block references
		 * from dअगरferent inodes can race and so we have to protect
		 * from a race where someone अन्यथा मुक्तs the block (and releases
		 * its journal_head) beक्रमe we are करोne dirtying the buffer. In
		 * nojournal mode this race is harmless and we actually cannot
		 * call ext4_handle_dirty_metadata() with locked buffer as
		 * that function can call sync_dirty_buffer() so क्रम that हाल
		 * we handle the dirtying after unlocking the buffer.
		 */
		अगर (ext4_handle_valid(handle))
			error = ext4_handle_dirty_metadata(handle, inode, bh);
		unlock_buffer(bh);
		अगर (!ext4_handle_valid(handle))
			error = ext4_handle_dirty_metadata(handle, inode, bh);
		अगर (IS_SYNC(inode))
			ext4_handle_sync(handle);
		dquot_मुक्त_block(inode, EXT4_C2B(EXT4_SB(inode->i_sb), 1));
		ea_bdebug(bh, "refcount now=%d; releasing",
			  le32_to_cpu(BHDR(bh)->h_refcount));
	पूर्ण
out:
	ext4_std_error(inode->i_sb, error);
	वापस;
पूर्ण

/*
 * Find the available मुक्त space क्रम EAs. This also वापसs the total number of
 * bytes used by EA entries.
 */
अटल माप_प्रकार ext4_xattr_मुक्त_space(काष्ठा ext4_xattr_entry *last,
				    माप_प्रकार *min_offs, व्योम *base, पूर्णांक *total)
अणु
	क्रम (; !IS_LAST_ENTRY(last); last = EXT4_XATTR_NEXT(last)) अणु
		अगर (!last->e_value_inum && last->e_value_size) अणु
			माप_प्रकार offs = le16_to_cpu(last->e_value_offs);
			अगर (offs < *min_offs)
				*min_offs = offs;
		पूर्ण
		अगर (total)
			*total += EXT4_XATTR_LEN(last->e_name_len);
	पूर्ण
	वापस (*min_offs - ((व्योम *)last - base) - माप(__u32));
पूर्ण

/*
 * Write the value of the EA in an inode.
 */
अटल पूर्णांक ext4_xattr_inode_ग_लिखो(handle_t *handle, काष्ठा inode *ea_inode,
				  स्थिर व्योम *buf, पूर्णांक bufsize)
अणु
	काष्ठा buffer_head *bh = शून्य;
	अचिन्हित दीर्घ block = 0;
	पूर्णांक blocksize = ea_inode->i_sb->s_blocksize;
	पूर्णांक max_blocks = (bufsize + blocksize - 1) >> ea_inode->i_blkbits;
	पूर्णांक csize, wsize = 0;
	पूर्णांक ret = 0, ret2 = 0;
	पूर्णांक retries = 0;

retry:
	जबतक (ret >= 0 && ret < max_blocks) अणु
		काष्ठा ext4_map_blocks map;
		map.m_lblk = block += ret;
		map.m_len = max_blocks -= ret;

		ret = ext4_map_blocks(handle, ea_inode, &map,
				      EXT4_GET_BLOCKS_CREATE);
		अगर (ret <= 0) अणु
			ext4_mark_inode_dirty(handle, ea_inode);
			अगर (ret == -ENOSPC &&
			    ext4_should_retry_alloc(ea_inode->i_sb, &retries)) अणु
				ret = 0;
				जाओ retry;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	block = 0;
	जबतक (wsize < bufsize) अणु
		brअन्यथा(bh);
		csize = (bufsize - wsize) > blocksize ? blocksize :
								bufsize - wsize;
		bh = ext4_getblk(handle, ea_inode, block, 0);
		अगर (IS_ERR(bh))
			वापस PTR_ERR(bh);
		अगर (!bh) अणु
			WARN_ON_ONCE(1);
			EXT4_ERROR_INODE(ea_inode,
					 "ext4_getblk() return bh = NULL");
			वापस -EFSCORRUPTED;
		पूर्ण
		ret = ext4_journal_get_ग_लिखो_access(handle, bh);
		अगर (ret)
			जाओ out;

		स_नकल(bh->b_data, buf, csize);
		set_buffer_uptodate(bh);
		ext4_handle_dirty_metadata(handle, ea_inode, bh);

		buf += csize;
		wsize += csize;
		block += 1;
	पूर्ण

	inode_lock(ea_inode);
	i_size_ग_लिखो(ea_inode, wsize);
	ext4_update_i_disksize(ea_inode, wsize);
	inode_unlock(ea_inode);

	ret2 = ext4_mark_inode_dirty(handle, ea_inode);
	अगर (unlikely(ret2 && !ret))
		ret = ret2;

out:
	brअन्यथा(bh);

	वापस ret;
पूर्ण

/*
 * Create an inode to store the value of a large EA.
 */
अटल काष्ठा inode *ext4_xattr_inode_create(handle_t *handle,
					     काष्ठा inode *inode, u32 hash)
अणु
	काष्ठा inode *ea_inode = शून्य;
	uid_t owner[2] = अणु i_uid_पढ़ो(inode), i_gid_पढ़ो(inode) पूर्ण;
	पूर्णांक err;

	/*
	 * Let the next inode be the goal, so we try and allocate the EA inode
	 * in the same group, or nearby one.
	 */
	ea_inode = ext4_new_inode(handle, inode->i_sb->s_root->d_inode,
				  S_IFREG | 0600, शून्य, inode->i_ino + 1, owner,
				  EXT4_EA_INODE_FL);
	अगर (!IS_ERR(ea_inode)) अणु
		ea_inode->i_op = &ext4_file_inode_operations;
		ea_inode->i_fop = &ext4_file_operations;
		ext4_set_aops(ea_inode);
		ext4_xattr_inode_set_class(ea_inode);
		unlock_new_inode(ea_inode);
		ext4_xattr_inode_set_ref(ea_inode, 1);
		ext4_xattr_inode_set_hash(ea_inode, hash);
		err = ext4_mark_inode_dirty(handle, ea_inode);
		अगर (!err)
			err = ext4_inode_attach_jinode(ea_inode);
		अगर (err) अणु
			iput(ea_inode);
			वापस ERR_PTR(err);
		पूर्ण

		/*
		 * Xattr inodes are shared thereक्रमe quota अक्षरging is perक्रमmed
		 * at a higher level.
		 */
		dquot_मुक्त_inode(ea_inode);
		dquot_drop(ea_inode);
		inode_lock(ea_inode);
		ea_inode->i_flags |= S_NOQUOTA;
		inode_unlock(ea_inode);
	पूर्ण

	वापस ea_inode;
पूर्ण

अटल काष्ठा inode *
ext4_xattr_inode_cache_find(काष्ठा inode *inode, स्थिर व्योम *value,
			    माप_प्रकार value_len, u32 hash)
अणु
	काष्ठा inode *ea_inode;
	काष्ठा mb_cache_entry *ce;
	काष्ठा mb_cache *ea_inode_cache = EA_INODE_CACHE(inode);
	व्योम *ea_data;

	अगर (!ea_inode_cache)
		वापस शून्य;

	ce = mb_cache_entry_find_first(ea_inode_cache, hash);
	अगर (!ce)
		वापस शून्य;

	WARN_ON_ONCE(ext4_handle_valid(journal_current_handle()) &&
		     !(current->flags & PF_MEMALLOC_NOFS));

	ea_data = kvदो_स्मृति(value_len, GFP_KERNEL);
	अगर (!ea_data) अणु
		mb_cache_entry_put(ea_inode_cache, ce);
		वापस शून्य;
	पूर्ण

	जबतक (ce) अणु
		ea_inode = ext4_iget(inode->i_sb, ce->e_value,
				     EXT4_IGET_NORMAL);
		अगर (!IS_ERR(ea_inode) &&
		    !is_bad_inode(ea_inode) &&
		    (EXT4_I(ea_inode)->i_flags & EXT4_EA_INODE_FL) &&
		    i_size_पढ़ो(ea_inode) == value_len &&
		    !ext4_xattr_inode_पढ़ो(ea_inode, ea_data, value_len) &&
		    !ext4_xattr_inode_verअगरy_hashes(ea_inode, शून्य, ea_data,
						    value_len) &&
		    !स_भेद(value, ea_data, value_len)) अणु
			mb_cache_entry_touch(ea_inode_cache, ce);
			mb_cache_entry_put(ea_inode_cache, ce);
			kvमुक्त(ea_data);
			वापस ea_inode;
		पूर्ण

		अगर (!IS_ERR(ea_inode))
			iput(ea_inode);
		ce = mb_cache_entry_find_next(ea_inode_cache, ce);
	पूर्ण
	kvमुक्त(ea_data);
	वापस शून्य;
पूर्ण

/*
 * Add value of the EA in an inode.
 */
अटल पूर्णांक ext4_xattr_inode_lookup_create(handle_t *handle, काष्ठा inode *inode,
					  स्थिर व्योम *value, माप_प्रकार value_len,
					  काष्ठा inode **ret_inode)
अणु
	काष्ठा inode *ea_inode;
	u32 hash;
	पूर्णांक err;

	hash = ext4_xattr_inode_hash(EXT4_SB(inode->i_sb), value, value_len);
	ea_inode = ext4_xattr_inode_cache_find(inode, value, value_len, hash);
	अगर (ea_inode) अणु
		err = ext4_xattr_inode_inc_ref(handle, ea_inode);
		अगर (err) अणु
			iput(ea_inode);
			वापस err;
		पूर्ण

		*ret_inode = ea_inode;
		वापस 0;
	पूर्ण

	/* Create an inode क्रम the EA value */
	ea_inode = ext4_xattr_inode_create(handle, inode, hash);
	अगर (IS_ERR(ea_inode))
		वापस PTR_ERR(ea_inode);

	err = ext4_xattr_inode_ग_लिखो(handle, ea_inode, value, value_len);
	अगर (err) अणु
		ext4_xattr_inode_dec_ref(handle, ea_inode);
		iput(ea_inode);
		वापस err;
	पूर्ण

	अगर (EA_INODE_CACHE(inode))
		mb_cache_entry_create(EA_INODE_CACHE(inode), GFP_NOFS, hash,
				      ea_inode->i_ino, true /* reusable */);

	*ret_inode = ea_inode;
	वापस 0;
पूर्ण

/*
 * Reserve min(block_size/8, 1024) bytes क्रम xattr entries/names अगर ea_inode
 * feature is enabled.
 */
#घोषणा EXT4_XATTR_BLOCK_RESERVE(inode)	min(i_blocksize(inode)/8, 1024U)

अटल पूर्णांक ext4_xattr_set_entry(काष्ठा ext4_xattr_info *i,
				काष्ठा ext4_xattr_search *s,
				handle_t *handle, काष्ठा inode *inode,
				bool is_block)
अणु
	काष्ठा ext4_xattr_entry *last, *next;
	काष्ठा ext4_xattr_entry *here = s->here;
	माप_प्रकार min_offs = s->end - s->base, name_len = म_माप(i->name);
	पूर्णांक in_inode = i->in_inode;
	काष्ठा inode *old_ea_inode = शून्य;
	काष्ठा inode *new_ea_inode = शून्य;
	माप_प्रकार old_size, new_size;
	पूर्णांक ret;

	/* Space used by old and new values. */
	old_size = (!s->not_found && !here->e_value_inum) ?
			EXT4_XATTR_SIZE(le32_to_cpu(here->e_value_size)) : 0;
	new_size = (i->value && !in_inode) ? EXT4_XATTR_SIZE(i->value_len) : 0;

	/*
	 * Optimization क्रम the simple हाल when old and new values have the
	 * same padded sizes. Not applicable अगर बाह्यal inodes are involved.
	 */
	अगर (new_size && new_size == old_size) अणु
		माप_प्रकार offs = le16_to_cpu(here->e_value_offs);
		व्योम *val = s->base + offs;

		here->e_value_size = cpu_to_le32(i->value_len);
		अगर (i->value == EXT4_ZERO_XATTR_VALUE) अणु
			स_रखो(val, 0, new_size);
		पूर्ण अन्यथा अणु
			स_नकल(val, i->value, i->value_len);
			/* Clear padding bytes. */
			स_रखो(val + i->value_len, 0, new_size - i->value_len);
		पूर्ण
		जाओ update_hash;
	पूर्ण

	/* Compute min_offs and last. */
	last = s->first;
	क्रम (; !IS_LAST_ENTRY(last); last = next) अणु
		next = EXT4_XATTR_NEXT(last);
		अगर ((व्योम *)next >= s->end) अणु
			EXT4_ERROR_INODE(inode, "corrupted xattr entries");
			ret = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		अगर (!last->e_value_inum && last->e_value_size) अणु
			माप_प्रकार offs = le16_to_cpu(last->e_value_offs);
			अगर (offs < min_offs)
				min_offs = offs;
		पूर्ण
	पूर्ण

	/* Check whether we have enough space. */
	अगर (i->value) अणु
		माप_प्रकार मुक्त;

		मुक्त = min_offs - ((व्योम *)last - s->base) - माप(__u32);
		अगर (!s->not_found)
			मुक्त += EXT4_XATTR_LEN(name_len) + old_size;

		अगर (मुक्त < EXT4_XATTR_LEN(name_len) + new_size) अणु
			ret = -ENOSPC;
			जाओ out;
		पूर्ण

		/*
		 * If storing the value in an बाह्यal inode is an option,
		 * reserve space क्रम xattr entries/names in the बाह्यal
		 * attribute block so that a दीर्घ value करोes not occupy the
		 * whole space and prevent further entries being added.
		 */
		अगर (ext4_has_feature_ea_inode(inode->i_sb) &&
		    new_size && is_block &&
		    (min_offs + old_size - new_size) <
					EXT4_XATTR_BLOCK_RESERVE(inode)) अणु
			ret = -ENOSPC;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Getting access to old and new ea inodes is subject to failures.
	 * Finish that work beक्रमe करोing any modअगरications to the xattr data.
	 */
	अगर (!s->not_found && here->e_value_inum) अणु
		ret = ext4_xattr_inode_iget(inode,
					    le32_to_cpu(here->e_value_inum),
					    le32_to_cpu(here->e_hash),
					    &old_ea_inode);
		अगर (ret) अणु
			old_ea_inode = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (i->value && in_inode) अणु
		WARN_ON_ONCE(!i->value_len);

		ret = ext4_xattr_inode_alloc_quota(inode, i->value_len);
		अगर (ret)
			जाओ out;

		ret = ext4_xattr_inode_lookup_create(handle, inode, i->value,
						     i->value_len,
						     &new_ea_inode);
		अगर (ret) अणु
			new_ea_inode = शून्य;
			ext4_xattr_inode_मुक्त_quota(inode, शून्य, i->value_len);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (old_ea_inode) अणु
		/* We are पढ़ोy to release ref count on the old_ea_inode. */
		ret = ext4_xattr_inode_dec_ref(handle, old_ea_inode);
		अगर (ret) अणु
			/* Release newly required ref count on new_ea_inode. */
			अगर (new_ea_inode) अणु
				पूर्णांक err;

				err = ext4_xattr_inode_dec_ref(handle,
							       new_ea_inode);
				अगर (err)
					ext4_warning_inode(new_ea_inode,
						  "dec ref new_ea_inode err=%d",
						  err);
				ext4_xattr_inode_मुक्त_quota(inode, new_ea_inode,
							    i->value_len);
			पूर्ण
			जाओ out;
		पूर्ण

		ext4_xattr_inode_मुक्त_quota(inode, old_ea_inode,
					    le32_to_cpu(here->e_value_size));
	पूर्ण

	/* No failures allowed past this poपूर्णांक. */

	अगर (!s->not_found && here->e_value_size && !here->e_value_inum) अणु
		/* Remove the old value. */
		व्योम *first_val = s->base + min_offs;
		माप_प्रकार offs = le16_to_cpu(here->e_value_offs);
		व्योम *val = s->base + offs;

		स_हटाओ(first_val + old_size, first_val, val - first_val);
		स_रखो(first_val, 0, old_size);
		min_offs += old_size;

		/* Adjust all value offsets. */
		last = s->first;
		जबतक (!IS_LAST_ENTRY(last)) अणु
			माप_प्रकार o = le16_to_cpu(last->e_value_offs);

			अगर (!last->e_value_inum &&
			    last->e_value_size && o < offs)
				last->e_value_offs = cpu_to_le16(o + old_size);
			last = EXT4_XATTR_NEXT(last);
		पूर्ण
	पूर्ण

	अगर (!i->value) अणु
		/* Remove old name. */
		माप_प्रकार size = EXT4_XATTR_LEN(name_len);

		last = ENTRY((व्योम *)last - size);
		स_हटाओ(here, (व्योम *)here + size,
			(व्योम *)last - (व्योम *)here + माप(__u32));
		स_रखो(last, 0, size);
	पूर्ण अन्यथा अगर (s->not_found) अणु
		/* Insert new name. */
		माप_प्रकार size = EXT4_XATTR_LEN(name_len);
		माप_प्रकार rest = (व्योम *)last - (व्योम *)here + माप(__u32);

		स_हटाओ((व्योम *)here + size, here, rest);
		स_रखो(here, 0, size);
		here->e_name_index = i->name_index;
		here->e_name_len = name_len;
		स_नकल(here->e_name, i->name, name_len);
	पूर्ण अन्यथा अणु
		/* This is an update, reset value info. */
		here->e_value_inum = 0;
		here->e_value_offs = 0;
		here->e_value_size = 0;
	पूर्ण

	अगर (i->value) अणु
		/* Insert new value. */
		अगर (in_inode) अणु
			here->e_value_inum = cpu_to_le32(new_ea_inode->i_ino);
		पूर्ण अन्यथा अगर (i->value_len) अणु
			व्योम *val = s->base + min_offs - new_size;

			here->e_value_offs = cpu_to_le16(min_offs - new_size);
			अगर (i->value == EXT4_ZERO_XATTR_VALUE) अणु
				स_रखो(val, 0, new_size);
			पूर्ण अन्यथा अणु
				स_नकल(val, i->value, i->value_len);
				/* Clear padding bytes. */
				स_रखो(val + i->value_len, 0,
				       new_size - i->value_len);
			पूर्ण
		पूर्ण
		here->e_value_size = cpu_to_le32(i->value_len);
	पूर्ण

update_hash:
	अगर (i->value) अणु
		__le32 hash = 0;

		/* Entry hash calculation. */
		अगर (in_inode) अणु
			__le32 crc32c_hash;

			/*
			 * Feed crc32c hash instead of the raw value क्रम entry
			 * hash calculation. This is to aव्योम walking
			 * potentially दीर्घ value buffer again.
			 */
			crc32c_hash = cpu_to_le32(
				       ext4_xattr_inode_get_hash(new_ea_inode));
			hash = ext4_xattr_hash_entry(here->e_name,
						     here->e_name_len,
						     &crc32c_hash, 1);
		पूर्ण अन्यथा अगर (is_block) अणु
			__le32 *value = s->base + le16_to_cpu(
							here->e_value_offs);

			hash = ext4_xattr_hash_entry(here->e_name,
						     here->e_name_len, value,
						     new_size >> 2);
		पूर्ण
		here->e_hash = hash;
	पूर्ण

	अगर (is_block)
		ext4_xattr_rehash((काष्ठा ext4_xattr_header *)s->base);

	ret = 0;
out:
	iput(old_ea_inode);
	iput(new_ea_inode);
	वापस ret;
पूर्ण

काष्ठा ext4_xattr_block_find अणु
	काष्ठा ext4_xattr_search s;
	काष्ठा buffer_head *bh;
पूर्ण;

अटल पूर्णांक
ext4_xattr_block_find(काष्ठा inode *inode, काष्ठा ext4_xattr_info *i,
		      काष्ठा ext4_xattr_block_find *bs)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक error;

	ea_idebug(inode, "name=%d.%s, value=%p, value_len=%ld",
		  i->name_index, i->name, i->value, (दीर्घ)i->value_len);

	अगर (EXT4_I(inode)->i_file_acl) अणु
		/* The inode alपढ़ोy has an extended attribute block. */
		bs->bh = ext4_sb_bपढ़ो(sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
		अगर (IS_ERR(bs->bh)) अणु
			error = PTR_ERR(bs->bh);
			bs->bh = शून्य;
			वापस error;
		पूर्ण
		ea_bdebug(bs->bh, "b_count=%d, refcount=%d",
			atomic_पढ़ो(&(bs->bh->b_count)),
			le32_to_cpu(BHDR(bs->bh)->h_refcount));
		error = ext4_xattr_check_block(inode, bs->bh);
		अगर (error)
			वापस error;
		/* Find the named attribute. */
		bs->s.base = BHDR(bs->bh);
		bs->s.first = BFIRST(bs->bh);
		bs->s.end = bs->bh->b_data + bs->bh->b_size;
		bs->s.here = bs->s.first;
		error = xattr_find_entry(inode, &bs->s.here, bs->s.end,
					 i->name_index, i->name, 1);
		अगर (error && error != -ENODATA)
			वापस error;
		bs->s.not_found = error;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
ext4_xattr_block_set(handle_t *handle, काष्ठा inode *inode,
		     काष्ठा ext4_xattr_info *i,
		     काष्ठा ext4_xattr_block_find *bs)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ext4_xattr_search s_copy = bs->s;
	काष्ठा ext4_xattr_search *s = &s_copy;
	काष्ठा mb_cache_entry *ce = शून्य;
	पूर्णांक error = 0;
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);
	काष्ठा inode *ea_inode = शून्य, *पंचांगp_inode;
	माप_प्रकार old_ea_inode_quota = 0;
	अचिन्हित पूर्णांक ea_ino;


#घोषणा header(x) ((काष्ठा ext4_xattr_header *)(x))

	अगर (s->base) अणु
		BUFFER_TRACE(bs->bh, "get_write_access");
		error = ext4_journal_get_ग_लिखो_access(handle, bs->bh);
		अगर (error)
			जाओ cleanup;
		lock_buffer(bs->bh);

		अगर (header(s->base)->h_refcount == cpu_to_le32(1)) अणु
			__u32 hash = le32_to_cpu(BHDR(bs->bh)->h_hash);

			/*
			 * This must happen under buffer lock क्रम
			 * ext4_xattr_block_set() to reliably detect modअगरied
			 * block
			 */
			अगर (ea_block_cache)
				mb_cache_entry_delete(ea_block_cache, hash,
						      bs->bh->b_blocknr);
			ea_bdebug(bs->bh, "modifying in-place");
			error = ext4_xattr_set_entry(i, s, handle, inode,
						     true /* is_block */);
			ext4_xattr_block_csum_set(inode, bs->bh);
			unlock_buffer(bs->bh);
			अगर (error == -EFSCORRUPTED)
				जाओ bad_block;
			अगर (!error)
				error = ext4_handle_dirty_metadata(handle,
								   inode,
								   bs->bh);
			अगर (error)
				जाओ cleanup;
			जाओ inserted;
		पूर्ण अन्यथा अणु
			पूर्णांक offset = (अक्षर *)s->here - bs->bh->b_data;

			unlock_buffer(bs->bh);
			ea_bdebug(bs->bh, "cloning");
			s->base = kदो_स्मृति(bs->bh->b_size, GFP_NOFS);
			error = -ENOMEM;
			अगर (s->base == शून्य)
				जाओ cleanup;
			स_नकल(s->base, BHDR(bs->bh), bs->bh->b_size);
			s->first = ENTRY(header(s->base)+1);
			header(s->base)->h_refcount = cpu_to_le32(1);
			s->here = ENTRY(s->base + offset);
			s->end = s->base + bs->bh->b_size;

			/*
			 * If existing entry poपूर्णांकs to an xattr inode, we need
			 * to prevent ext4_xattr_set_entry() from decrementing
			 * ref count on it because the reference beदीर्घs to the
			 * original block. In this हाल, make the entry look
			 * like it has an empty value.
			 */
			अगर (!s->not_found && s->here->e_value_inum) अणु
				ea_ino = le32_to_cpu(s->here->e_value_inum);
				error = ext4_xattr_inode_iget(inode, ea_ino,
					      le32_to_cpu(s->here->e_hash),
					      &पंचांगp_inode);
				अगर (error)
					जाओ cleanup;

				अगर (!ext4_test_inode_state(पंचांगp_inode,
						EXT4_STATE_LUSTRE_EA_INODE)) अणु
					/*
					 * Defer quota मुक्त call क्रम previous
					 * inode until success is guaranteed.
					 */
					old_ea_inode_quota = le32_to_cpu(
							s->here->e_value_size);
				पूर्ण
				iput(पंचांगp_inode);

				s->here->e_value_inum = 0;
				s->here->e_value_size = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Allocate a buffer where we स्थिरruct the new block. */
		s->base = kzalloc(sb->s_blocksize, GFP_NOFS);
		error = -ENOMEM;
		अगर (s->base == शून्य)
			जाओ cleanup;
		header(s->base)->h_magic = cpu_to_le32(EXT4_XATTR_MAGIC);
		header(s->base)->h_blocks = cpu_to_le32(1);
		header(s->base)->h_refcount = cpu_to_le32(1);
		s->first = ENTRY(header(s->base)+1);
		s->here = ENTRY(header(s->base)+1);
		s->end = s->base + sb->s_blocksize;
	पूर्ण

	error = ext4_xattr_set_entry(i, s, handle, inode, true /* is_block */);
	अगर (error == -EFSCORRUPTED)
		जाओ bad_block;
	अगर (error)
		जाओ cleanup;

	अगर (i->value && s->here->e_value_inum) अणु
		/*
		 * A ref count on ea_inode has been taken as part of the call to
		 * ext4_xattr_set_entry() above. We would like to drop this
		 * extra ref but we have to रुको until the xattr block is
		 * initialized and has its own ref count on the ea_inode.
		 */
		ea_ino = le32_to_cpu(s->here->e_value_inum);
		error = ext4_xattr_inode_iget(inode, ea_ino,
					      le32_to_cpu(s->here->e_hash),
					      &ea_inode);
		अगर (error) अणु
			ea_inode = शून्य;
			जाओ cleanup;
		पूर्ण
	पूर्ण

inserted:
	अगर (!IS_LAST_ENTRY(s->first)) अणु
		new_bh = ext4_xattr_block_cache_find(inode, header(s->base),
						     &ce);
		अगर (new_bh) अणु
			/* We found an identical block in the cache. */
			अगर (new_bh == bs->bh)
				ea_bdebug(new_bh, "keeping");
			अन्यथा अणु
				u32 ref;

				WARN_ON_ONCE(dquot_initialize_needed(inode));

				/* The old block is released after updating
				   the inode. */
				error = dquot_alloc_block(inode,
						EXT4_C2B(EXT4_SB(sb), 1));
				अगर (error)
					जाओ cleanup;
				BUFFER_TRACE(new_bh, "get_write_access");
				error = ext4_journal_get_ग_लिखो_access(handle,
								      new_bh);
				अगर (error)
					जाओ cleanup_dquot;
				lock_buffer(new_bh);
				/*
				 * We have to be careful about races with
				 * मुक्तing, rehashing or adding references to
				 * xattr block. Once we hold buffer lock xattr
				 * block's state is stable so we can check
				 * whether the block got मुक्तd / rehashed or
				 * not.  Since we unhash mbcache entry under
				 * buffer lock when मुक्तing / rehashing xattr
				 * block, checking whether entry is still
				 * hashed is reliable. Same rules hold क्रम
				 * e_reusable handling.
				 */
				अगर (hlist_bl_unhashed(&ce->e_hash_list) ||
				    !ce->e_reusable) अणु
					/*
					 * Unकरो everything and check mbcache
					 * again.
					 */
					unlock_buffer(new_bh);
					dquot_मुक्त_block(inode,
							 EXT4_C2B(EXT4_SB(sb),
								  1));
					brअन्यथा(new_bh);
					mb_cache_entry_put(ea_block_cache, ce);
					ce = शून्य;
					new_bh = शून्य;
					जाओ inserted;
				पूर्ण
				ref = le32_to_cpu(BHDR(new_bh)->h_refcount) + 1;
				BHDR(new_bh)->h_refcount = cpu_to_le32(ref);
				अगर (ref >= EXT4_XATTR_REFCOUNT_MAX)
					ce->e_reusable = 0;
				ea_bdebug(new_bh, "reusing; refcount now=%d",
					  ref);
				ext4_xattr_block_csum_set(inode, new_bh);
				unlock_buffer(new_bh);
				error = ext4_handle_dirty_metadata(handle,
								   inode,
								   new_bh);
				अगर (error)
					जाओ cleanup_dquot;
			पूर्ण
			mb_cache_entry_touch(ea_block_cache, ce);
			mb_cache_entry_put(ea_block_cache, ce);
			ce = शून्य;
		पूर्ण अन्यथा अगर (bs->bh && s->base == bs->bh->b_data) अणु
			/* We were modअगरying this block in-place. */
			ea_bdebug(bs->bh, "keeping this block");
			ext4_xattr_block_cache_insert(ea_block_cache, bs->bh);
			new_bh = bs->bh;
			get_bh(new_bh);
		पूर्ण अन्यथा अणु
			/* We need to allocate a new block */
			ext4_fsblk_t goal, block;

			WARN_ON_ONCE(dquot_initialize_needed(inode));

			goal = ext4_group_first_block_no(sb,
						EXT4_I(inode)->i_block_group);

			/* non-extent files can't have physical blocks past 2^32 */
			अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
				goal = goal & EXT4_MAX_BLOCK_खाता_PHYS;

			block = ext4_new_meta_blocks(handle, inode, goal, 0,
						     शून्य, &error);
			अगर (error)
				जाओ cleanup;

			अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
				BUG_ON(block > EXT4_MAX_BLOCK_खाता_PHYS);

			ea_idebug(inode, "creating block %llu",
				  (अचिन्हित दीर्घ दीर्घ)block);

			new_bh = sb_getblk(sb, block);
			अगर (unlikely(!new_bh)) अणु
				error = -ENOMEM;
getblk_failed:
				ext4_मुक्त_blocks(handle, inode, शून्य, block, 1,
						 EXT4_FREE_BLOCKS_METADATA);
				जाओ cleanup;
			पूर्ण
			error = ext4_xattr_inode_inc_ref_all(handle, inode,
						      ENTRY(header(s->base)+1));
			अगर (error)
				जाओ getblk_failed;
			अगर (ea_inode) अणु
				/* Drop the extra ref on ea_inode. */
				error = ext4_xattr_inode_dec_ref(handle,
								 ea_inode);
				अगर (error)
					ext4_warning_inode(ea_inode,
							   "dec ref error=%d",
							   error);
				iput(ea_inode);
				ea_inode = शून्य;
			पूर्ण

			lock_buffer(new_bh);
			error = ext4_journal_get_create_access(handle, new_bh);
			अगर (error) अणु
				unlock_buffer(new_bh);
				error = -EIO;
				जाओ getblk_failed;
			पूर्ण
			स_नकल(new_bh->b_data, s->base, new_bh->b_size);
			ext4_xattr_block_csum_set(inode, new_bh);
			set_buffer_uptodate(new_bh);
			unlock_buffer(new_bh);
			ext4_xattr_block_cache_insert(ea_block_cache, new_bh);
			error = ext4_handle_dirty_metadata(handle, inode,
							   new_bh);
			अगर (error)
				जाओ cleanup;
		पूर्ण
	पूर्ण

	अगर (old_ea_inode_quota)
		ext4_xattr_inode_मुक्त_quota(inode, शून्य, old_ea_inode_quota);

	/* Update the inode. */
	EXT4_I(inode)->i_file_acl = new_bh ? new_bh->b_blocknr : 0;

	/* Drop the previous xattr block. */
	अगर (bs->bh && bs->bh != new_bh) अणु
		काष्ठा ext4_xattr_inode_array *ea_inode_array = शून्य;

		ext4_xattr_release_block(handle, inode, bs->bh,
					 &ea_inode_array,
					 0 /* extra_credits */);
		ext4_xattr_inode_array_मुक्त(ea_inode_array);
	पूर्ण
	error = 0;

cleanup:
	अगर (ea_inode) अणु
		पूर्णांक error2;

		error2 = ext4_xattr_inode_dec_ref(handle, ea_inode);
		अगर (error2)
			ext4_warning_inode(ea_inode, "dec ref error=%d",
					   error2);

		/* If there was an error, revert the quota अक्षरge. */
		अगर (error)
			ext4_xattr_inode_मुक्त_quota(inode, ea_inode,
						    i_size_पढ़ो(ea_inode));
		iput(ea_inode);
	पूर्ण
	अगर (ce)
		mb_cache_entry_put(ea_block_cache, ce);
	brअन्यथा(new_bh);
	अगर (!(bs->bh && s->base == bs->bh->b_data))
		kमुक्त(s->base);

	वापस error;

cleanup_dquot:
	dquot_मुक्त_block(inode, EXT4_C2B(EXT4_SB(sb), 1));
	जाओ cleanup;

bad_block:
	EXT4_ERROR_INODE(inode, "bad block %llu",
			 EXT4_I(inode)->i_file_acl);
	जाओ cleanup;

#अघोषित header
पूर्ण

पूर्णांक ext4_xattr_ibody_find(काष्ठा inode *inode, काष्ठा ext4_xattr_info *i,
			  काष्ठा ext4_xattr_ibody_find *is)
अणु
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_inode *raw_inode;
	पूर्णांक error;

	अगर (EXT4_I(inode)->i_extra_isize == 0)
		वापस 0;
	raw_inode = ext4_raw_inode(&is->iloc);
	header = IHDR(inode, raw_inode);
	is->s.base = is->s.first = IFIRST(header);
	is->s.here = is->s.first;
	is->s.end = (व्योम *)raw_inode + EXT4_SB(inode->i_sb)->s_inode_size;
	अगर (ext4_test_inode_state(inode, EXT4_STATE_XATTR)) अणु
		error = xattr_check_inode(inode, header, is->s.end);
		अगर (error)
			वापस error;
		/* Find the named attribute. */
		error = xattr_find_entry(inode, &is->s.here, is->s.end,
					 i->name_index, i->name, 0);
		अगर (error && error != -ENODATA)
			वापस error;
		is->s.not_found = error;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ext4_xattr_ibody_अंतरभूत_set(handle_t *handle, काष्ठा inode *inode,
				काष्ठा ext4_xattr_info *i,
				काष्ठा ext4_xattr_ibody_find *is)
अणु
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_xattr_search *s = &is->s;
	पूर्णांक error;

	अगर (EXT4_I(inode)->i_extra_isize == 0)
		वापस -ENOSPC;
	error = ext4_xattr_set_entry(i, s, handle, inode, false /* is_block */);
	अगर (error)
		वापस error;
	header = IHDR(inode, ext4_raw_inode(&is->iloc));
	अगर (!IS_LAST_ENTRY(s->first)) अणु
		header->h_magic = cpu_to_le32(EXT4_XATTR_MAGIC);
		ext4_set_inode_state(inode, EXT4_STATE_XATTR);
	पूर्ण अन्यथा अणु
		header->h_magic = cpu_to_le32(0);
		ext4_clear_inode_state(inode, EXT4_STATE_XATTR);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_xattr_ibody_set(handle_t *handle, काष्ठा inode *inode,
				काष्ठा ext4_xattr_info *i,
				काष्ठा ext4_xattr_ibody_find *is)
अणु
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_xattr_search *s = &is->s;
	पूर्णांक error;

	अगर (EXT4_I(inode)->i_extra_isize == 0)
		वापस -ENOSPC;
	error = ext4_xattr_set_entry(i, s, handle, inode, false /* is_block */);
	अगर (error)
		वापस error;
	header = IHDR(inode, ext4_raw_inode(&is->iloc));
	अगर (!IS_LAST_ENTRY(s->first)) अणु
		header->h_magic = cpu_to_le32(EXT4_XATTR_MAGIC);
		ext4_set_inode_state(inode, EXT4_STATE_XATTR);
	पूर्ण अन्यथा अणु
		header->h_magic = cpu_to_le32(0);
		ext4_clear_inode_state(inode, EXT4_STATE_XATTR);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_xattr_value_same(काष्ठा ext4_xattr_search *s,
				 काष्ठा ext4_xattr_info *i)
अणु
	व्योम *value;

	/* When e_value_inum is set the value is stored बाह्यally. */
	अगर (s->here->e_value_inum)
		वापस 0;
	अगर (le32_to_cpu(s->here->e_value_size) != i->value_len)
		वापस 0;
	value = ((व्योम *)s->base) + le16_to_cpu(s->here->e_value_offs);
	वापस !स_भेद(value, i->value, i->value_len);
पूर्ण

अटल काष्ठा buffer_head *ext4_xattr_get_block(काष्ठा inode *inode)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक error;

	अगर (!EXT4_I(inode)->i_file_acl)
		वापस शून्य;
	bh = ext4_sb_bपढ़ो(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
	अगर (IS_ERR(bh))
		वापस bh;
	error = ext4_xattr_check_block(inode, bh);
	अगर (error) अणु
		brअन्यथा(bh);
		वापस ERR_PTR(error);
	पूर्ण
	वापस bh;
पूर्ण

/*
 * ext4_xattr_set_handle()
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
ext4_xattr_set_handle(handle_t *handle, काष्ठा inode *inode, पूर्णांक name_index,
		      स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार value_len,
		      पूर्णांक flags)
अणु
	काष्ठा ext4_xattr_info i = अणु
		.name_index = name_index,
		.name = name,
		.value = value,
		.value_len = value_len,
		.in_inode = 0,
	पूर्ण;
	काष्ठा ext4_xattr_ibody_find is = अणु
		.s = अणु .not_found = -ENODATA, पूर्ण,
	पूर्ण;
	काष्ठा ext4_xattr_block_find bs = अणु
		.s = अणु .not_found = -ENODATA, पूर्ण,
	पूर्ण;
	पूर्णांक no_expand;
	पूर्णांक error;

	अगर (!name)
		वापस -EINVAL;
	अगर (म_माप(name) > 255)
		वापस -दुस्फल;

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);

	/* Check journal credits under ग_लिखो lock. */
	अगर (ext4_handle_valid(handle)) अणु
		काष्ठा buffer_head *bh;
		पूर्णांक credits;

		bh = ext4_xattr_get_block(inode);
		अगर (IS_ERR(bh)) अणु
			error = PTR_ERR(bh);
			जाओ cleanup;
		पूर्ण

		credits = __ext4_xattr_set_credits(inode->i_sb, inode, bh,
						   value_len,
						   flags & XATTR_CREATE);
		brअन्यथा(bh);

		अगर (jbd2_handle_buffer_credits(handle) < credits) अणु
			error = -ENOSPC;
			जाओ cleanup;
		पूर्ण
		WARN_ON_ONCE(!(current->flags & PF_MEMALLOC_NOFS));
	पूर्ण

	error = ext4_reserve_inode_ग_लिखो(handle, inode, &is.iloc);
	अगर (error)
		जाओ cleanup;

	अगर (ext4_test_inode_state(inode, EXT4_STATE_NEW)) अणु
		काष्ठा ext4_inode *raw_inode = ext4_raw_inode(&is.iloc);
		स_रखो(raw_inode, 0, EXT4_SB(inode->i_sb)->s_inode_size);
		ext4_clear_inode_state(inode, EXT4_STATE_NEW);
	पूर्ण

	error = ext4_xattr_ibody_find(inode, &i, &is);
	अगर (error)
		जाओ cleanup;
	अगर (is.s.not_found)
		error = ext4_xattr_block_find(inode, &i, &bs);
	अगर (error)
		जाओ cleanup;
	अगर (is.s.not_found && bs.s.not_found) अणु
		error = -ENODATA;
		अगर (flags & XATTR_REPLACE)
			जाओ cleanup;
		error = 0;
		अगर (!value)
			जाओ cleanup;
	पूर्ण अन्यथा अणु
		error = -EEXIST;
		अगर (flags & XATTR_CREATE)
			जाओ cleanup;
	पूर्ण

	अगर (!value) अणु
		अगर (!is.s.not_found)
			error = ext4_xattr_ibody_set(handle, inode, &i, &is);
		अन्यथा अगर (!bs.s.not_found)
			error = ext4_xattr_block_set(handle, inode, &i, &bs);
	पूर्ण अन्यथा अणु
		error = 0;
		/* Xattr value did not change? Save us some work and bail out */
		अगर (!is.s.not_found && ext4_xattr_value_same(&is.s, &i))
			जाओ cleanup;
		अगर (!bs.s.not_found && ext4_xattr_value_same(&bs.s, &i))
			जाओ cleanup;

		अगर (ext4_has_feature_ea_inode(inode->i_sb) &&
		    (EXT4_XATTR_SIZE(i.value_len) >
			EXT4_XATTR_MIN_LARGE_EA_SIZE(inode->i_sb->s_blocksize)))
			i.in_inode = 1;
retry_inode:
		error = ext4_xattr_ibody_set(handle, inode, &i, &is);
		अगर (!error && !bs.s.not_found) अणु
			i.value = शून्य;
			error = ext4_xattr_block_set(handle, inode, &i, &bs);
		पूर्ण अन्यथा अगर (error == -ENOSPC) अणु
			अगर (EXT4_I(inode)->i_file_acl && !bs.s.base) अणु
				brअन्यथा(bs.bh);
				bs.bh = शून्य;
				error = ext4_xattr_block_find(inode, &i, &bs);
				अगर (error)
					जाओ cleanup;
			पूर्ण
			error = ext4_xattr_block_set(handle, inode, &i, &bs);
			अगर (!error && !is.s.not_found) अणु
				i.value = शून्य;
				error = ext4_xattr_ibody_set(handle, inode, &i,
							     &is);
			पूर्ण अन्यथा अगर (error == -ENOSPC) अणु
				/*
				 * Xattr करोes not fit in the block, store at
				 * बाह्यal inode अगर possible.
				 */
				अगर (ext4_has_feature_ea_inode(inode->i_sb) &&
				    i.value_len && !i.in_inode) अणु
					i.in_inode = 1;
					जाओ retry_inode;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!error) अणु
		ext4_xattr_update_super_block(handle, inode->i_sb);
		inode->i_स_समय = current_समय(inode);
		अगर (!value)
			no_expand = 0;
		error = ext4_mark_iloc_dirty(handle, inode, &is.iloc);
		/*
		 * The bh is consumed by ext4_mark_iloc_dirty, even with
		 * error != 0.
		 */
		is.iloc.bh = शून्य;
		अगर (IS_SYNC(inode))
			ext4_handle_sync(handle);
	पूर्ण
	ext4_fc_mark_ineligible(inode->i_sb, EXT4_FC_REASON_XATTR);

cleanup:
	brअन्यथा(is.iloc.bh);
	brअन्यथा(bs.bh);
	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
	वापस error;
पूर्ण

पूर्णांक ext4_xattr_set_credits(काष्ठा inode *inode, माप_प्रकार value_len,
			   bool is_create, पूर्णांक *credits)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	*credits = 0;

	अगर (!EXT4_SB(inode->i_sb)->s_journal)
		वापस 0;

	करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);

	bh = ext4_xattr_get_block(inode);
	अगर (IS_ERR(bh)) अणु
		err = PTR_ERR(bh);
	पूर्ण अन्यथा अणु
		*credits = __ext4_xattr_set_credits(inode->i_sb, inode, bh,
						    value_len, is_create);
		brअन्यथा(bh);
		err = 0;
	पूर्ण

	up_पढ़ो(&EXT4_I(inode)->xattr_sem);
	वापस err;
पूर्ण

/*
 * ext4_xattr_set()
 *
 * Like ext4_xattr_set_handle, but start from an inode. This extended
 * attribute modअगरication is a fileप्रणाली transaction by itself.
 *
 * Returns 0, or a negative error number on failure.
 */
पूर्णांक
ext4_xattr_set(काष्ठा inode *inode, पूर्णांक name_index, स्थिर अक्षर *name,
	       स्थिर व्योम *value, माप_प्रकार value_len, पूर्णांक flags)
अणु
	handle_t *handle;
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक error, retries = 0;
	पूर्णांक credits;

	error = dquot_initialize(inode);
	अगर (error)
		वापस error;

retry:
	error = ext4_xattr_set_credits(inode, value_len, flags & XATTR_CREATE,
				       &credits);
	अगर (error)
		वापस error;

	handle = ext4_journal_start(inode, EXT4_HT_XATTR, credits);
	अगर (IS_ERR(handle)) अणु
		error = PTR_ERR(handle);
	पूर्ण अन्यथा अणु
		पूर्णांक error2;

		error = ext4_xattr_set_handle(handle, inode, name_index, name,
					      value, value_len, flags);
		error2 = ext4_journal_stop(handle);
		अगर (error == -ENOSPC &&
		    ext4_should_retry_alloc(sb, &retries))
			जाओ retry;
		अगर (error == 0)
			error = error2;
	पूर्ण
	ext4_fc_mark_ineligible(inode->i_sb, EXT4_FC_REASON_XATTR);

	वापस error;
पूर्ण

/*
 * Shअगरt the EA entries in the inode to create space क्रम the increased
 * i_extra_isize.
 */
अटल व्योम ext4_xattr_shअगरt_entries(काष्ठा ext4_xattr_entry *entry,
				     पूर्णांक value_offs_shअगरt, व्योम *to,
				     व्योम *from, माप_प्रकार n)
अणु
	काष्ठा ext4_xattr_entry *last = entry;
	पूर्णांक new_offs;

	/* We always shअगरt xattr headers further thus offsets get lower */
	BUG_ON(value_offs_shअगरt > 0);

	/* Adjust the value offsets of the entries */
	क्रम (; !IS_LAST_ENTRY(last); last = EXT4_XATTR_NEXT(last)) अणु
		अगर (!last->e_value_inum && last->e_value_size) अणु
			new_offs = le16_to_cpu(last->e_value_offs) +
							value_offs_shअगरt;
			last->e_value_offs = cpu_to_le16(new_offs);
		पूर्ण
	पूर्ण
	/* Shअगरt the entries by n bytes */
	स_हटाओ(to, from, n);
पूर्ण

/*
 * Move xattr poपूर्णांकed to by 'entry' from inode पूर्णांकo बाह्यal xattr block
 */
अटल पूर्णांक ext4_xattr_move_to_block(handle_t *handle, काष्ठा inode *inode,
				    काष्ठा ext4_inode *raw_inode,
				    काष्ठा ext4_xattr_entry *entry)
अणु
	काष्ठा ext4_xattr_ibody_find *is = शून्य;
	काष्ठा ext4_xattr_block_find *bs = शून्य;
	अक्षर *buffer = शून्य, *b_entry_name = शून्य;
	माप_प्रकार value_size = le32_to_cpu(entry->e_value_size);
	काष्ठा ext4_xattr_info i = अणु
		.value = शून्य,
		.value_len = 0,
		.name_index = entry->e_name_index,
		.in_inode = !!entry->e_value_inum,
	पूर्ण;
	काष्ठा ext4_xattr_ibody_header *header = IHDR(inode, raw_inode);
	पूर्णांक error;

	is = kzalloc(माप(काष्ठा ext4_xattr_ibody_find), GFP_NOFS);
	bs = kzalloc(माप(काष्ठा ext4_xattr_block_find), GFP_NOFS);
	buffer = kदो_स्मृति(value_size, GFP_NOFS);
	b_entry_name = kदो_स्मृति(entry->e_name_len + 1, GFP_NOFS);
	अगर (!is || !bs || !buffer || !b_entry_name) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	is->s.not_found = -ENODATA;
	bs->s.not_found = -ENODATA;
	is->iloc.bh = शून्य;
	bs->bh = शून्य;

	/* Save the entry name and the entry value */
	अगर (entry->e_value_inum) अणु
		error = ext4_xattr_inode_get(inode, entry, buffer, value_size);
		अगर (error)
			जाओ out;
	पूर्ण अन्यथा अणु
		माप_प्रकार value_offs = le16_to_cpu(entry->e_value_offs);
		स_नकल(buffer, (व्योम *)IFIRST(header) + value_offs, value_size);
	पूर्ण

	स_नकल(b_entry_name, entry->e_name, entry->e_name_len);
	b_entry_name[entry->e_name_len] = '\0';
	i.name = b_entry_name;

	error = ext4_get_inode_loc(inode, &is->iloc);
	अगर (error)
		जाओ out;

	error = ext4_xattr_ibody_find(inode, &i, is);
	अगर (error)
		जाओ out;

	/* Remove the chosen entry from the inode */
	error = ext4_xattr_ibody_set(handle, inode, &i, is);
	अगर (error)
		जाओ out;

	i.value = buffer;
	i.value_len = value_size;
	error = ext4_xattr_block_find(inode, &i, bs);
	अगर (error)
		जाओ out;

	/* Add entry which was हटाओd from the inode पूर्णांकo the block */
	error = ext4_xattr_block_set(handle, inode, &i, bs);
	अगर (error)
		जाओ out;
	error = 0;
out:
	kमुक्त(b_entry_name);
	kमुक्त(buffer);
	अगर (is)
		brअन्यथा(is->iloc.bh);
	अगर (bs)
		brअन्यथा(bs->bh);
	kमुक्त(is);
	kमुक्त(bs);

	वापस error;
पूर्ण

अटल पूर्णांक ext4_xattr_make_inode_space(handle_t *handle, काष्ठा inode *inode,
				       काष्ठा ext4_inode *raw_inode,
				       पूर्णांक isize_dअगरf, माप_प्रकार अगरree,
				       माप_प्रकार bमुक्त, पूर्णांक *total_ino)
अणु
	काष्ठा ext4_xattr_ibody_header *header = IHDR(inode, raw_inode);
	काष्ठा ext4_xattr_entry *small_entry;
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा ext4_xattr_entry *last;
	अचिन्हित पूर्णांक entry_size;	/* EA entry size */
	अचिन्हित पूर्णांक total_size;	/* EA entry size + value size */
	अचिन्हित पूर्णांक min_total_size;
	पूर्णांक error;

	जबतक (isize_dअगरf > अगरree) अणु
		entry = शून्य;
		small_entry = शून्य;
		min_total_size = ~0U;
		last = IFIRST(header);
		/* Find the entry best suited to be pushed पूर्णांकo EA block */
		क्रम (; !IS_LAST_ENTRY(last); last = EXT4_XATTR_NEXT(last)) अणु
			/* never move प्रणाली.data out of the inode */
			अगर ((last->e_name_len == 4) &&
			    (last->e_name_index == EXT4_XATTR_INDEX_SYSTEM) &&
			    !स_भेद(last->e_name, "data", 4))
				जारी;
			total_size = EXT4_XATTR_LEN(last->e_name_len);
			अगर (!last->e_value_inum)
				total_size += EXT4_XATTR_SIZE(
					       le32_to_cpu(last->e_value_size));
			अगर (total_size <= bमुक्त &&
			    total_size < min_total_size) अणु
				अगर (total_size + अगरree < isize_dअगरf) अणु
					small_entry = last;
				पूर्ण अन्यथा अणु
					entry = last;
					min_total_size = total_size;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (entry == शून्य) अणु
			अगर (small_entry == शून्य)
				वापस -ENOSPC;
			entry = small_entry;
		पूर्ण

		entry_size = EXT4_XATTR_LEN(entry->e_name_len);
		total_size = entry_size;
		अगर (!entry->e_value_inum)
			total_size += EXT4_XATTR_SIZE(
					      le32_to_cpu(entry->e_value_size));
		error = ext4_xattr_move_to_block(handle, inode, raw_inode,
						 entry);
		अगर (error)
			वापस error;

		*total_ino -= entry_size;
		अगरree += total_size;
		bमुक्त -= total_size;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Expand an inode by new_extra_isize bytes when EAs are present.
 * Returns 0 on success or negative error number on failure.
 */
पूर्णांक ext4_expand_extra_isize_ea(काष्ठा inode *inode, पूर्णांक new_extra_isize,
			       काष्ठा ext4_inode *raw_inode, handle_t *handle)
अणु
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	अटल अचिन्हित पूर्णांक mnt_count;
	माप_प्रकार min_offs;
	माप_प्रकार अगरree, bमुक्त;
	पूर्णांक total_ino;
	व्योम *base, *end;
	पूर्णांक error = 0, tried_min_extra_isize = 0;
	पूर्णांक s_min_extra_isize = le16_to_cpu(sbi->s_es->s_min_extra_isize);
	पूर्णांक isize_dअगरf;	/* How much करो we need to grow i_extra_isize */

retry:
	isize_dअगरf = new_extra_isize - EXT4_I(inode)->i_extra_isize;
	अगर (EXT4_I(inode)->i_extra_isize >= new_extra_isize)
		वापस 0;

	header = IHDR(inode, raw_inode);

	/*
	 * Check अगर enough मुक्त space is available in the inode to shअगरt the
	 * entries ahead by new_extra_isize.
	 */

	base = IFIRST(header);
	end = (व्योम *)raw_inode + EXT4_SB(inode->i_sb)->s_inode_size;
	min_offs = end - base;
	total_ino = माप(काष्ठा ext4_xattr_ibody_header) + माप(u32);

	error = xattr_check_inode(inode, header, end);
	अगर (error)
		जाओ cleanup;

	अगरree = ext4_xattr_मुक्त_space(base, &min_offs, base, &total_ino);
	अगर (अगरree >= isize_dअगरf)
		जाओ shअगरt;

	/*
	 * Enough मुक्त space isn't available in the inode, check अगर
	 * EA block can hold new_extra_isize bytes.
	 */
	अगर (EXT4_I(inode)->i_file_acl) अणु
		काष्ठा buffer_head *bh;

		bh = ext4_sb_bपढ़ो(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
		अगर (IS_ERR(bh)) अणु
			error = PTR_ERR(bh);
			जाओ cleanup;
		पूर्ण
		error = ext4_xattr_check_block(inode, bh);
		अगर (error) अणु
			brअन्यथा(bh);
			जाओ cleanup;
		पूर्ण
		base = BHDR(bh);
		end = bh->b_data + bh->b_size;
		min_offs = end - base;
		bमुक्त = ext4_xattr_मुक्त_space(BFIRST(bh), &min_offs, base,
					      शून्य);
		brअन्यथा(bh);
		अगर (bमुक्त + अगरree < isize_dअगरf) अणु
			अगर (!tried_min_extra_isize && s_min_extra_isize) अणु
				tried_min_extra_isize++;
				new_extra_isize = s_min_extra_isize;
				जाओ retry;
			पूर्ण
			error = -ENOSPC;
			जाओ cleanup;
		पूर्ण
	पूर्ण अन्यथा अणु
		bमुक्त = inode->i_sb->s_blocksize;
	पूर्ण

	error = ext4_xattr_make_inode_space(handle, inode, raw_inode,
					    isize_dअगरf, अगरree, bमुक्त,
					    &total_ino);
	अगर (error) अणु
		अगर (error == -ENOSPC && !tried_min_extra_isize &&
		    s_min_extra_isize) अणु
			tried_min_extra_isize++;
			new_extra_isize = s_min_extra_isize;
			जाओ retry;
		पूर्ण
		जाओ cleanup;
	पूर्ण
shअगरt:
	/* Adjust the offsets and shअगरt the reमुख्यing entries ahead */
	ext4_xattr_shअगरt_entries(IFIRST(header), EXT4_I(inode)->i_extra_isize
			- new_extra_isize, (व्योम *)raw_inode +
			EXT4_GOOD_OLD_INODE_SIZE + new_extra_isize,
			(व्योम *)header, total_ino);
	EXT4_I(inode)->i_extra_isize = new_extra_isize;

cleanup:
	अगर (error && (mnt_count != le16_to_cpu(sbi->s_es->s_mnt_count))) अणु
		ext4_warning(inode->i_sb, "Unable to expand inode %lu. Delete some EAs or run e2fsck.",
			     inode->i_ino);
		mnt_count = le16_to_cpu(sbi->s_es->s_mnt_count);
	पूर्ण
	वापस error;
पूर्ण

#घोषणा EIA_INCR 16 /* must be 2^n */
#घोषणा EIA_MASK (EIA_INCR - 1)

/* Add the large xattr @inode पूर्णांकo @ea_inode_array क्रम deferred iput().
 * If @ea_inode_array is new or full it will be grown and the old
 * contents copied over.
 */
अटल पूर्णांक
ext4_expand_inode_array(काष्ठा ext4_xattr_inode_array **ea_inode_array,
			काष्ठा inode *inode)
अणु
	अगर (*ea_inode_array == शून्य) अणु
		/*
		 * Start with 15 inodes, so it fits पूर्णांकo a घातer-of-two size.
		 * If *ea_inode_array is शून्य, this is essentially दुरत्व()
		 */
		(*ea_inode_array) =
			kदो_स्मृति(दुरत्व(काष्ठा ext4_xattr_inode_array,
					 inodes[EIA_MASK]),
				GFP_NOFS);
		अगर (*ea_inode_array == शून्य)
			वापस -ENOMEM;
		(*ea_inode_array)->count = 0;
	पूर्ण अन्यथा अगर (((*ea_inode_array)->count & EIA_MASK) == EIA_MASK) अणु
		/* expand the array once all 15 + n * 16 slots are full */
		काष्ठा ext4_xattr_inode_array *new_array = शून्य;
		पूर्णांक count = (*ea_inode_array)->count;

		/* अगर new_array is शून्य, this is essentially दुरत्व() */
		new_array = kदो_स्मृति(
				दुरत्व(काष्ठा ext4_xattr_inode_array,
					 inodes[count + EIA_INCR]),
				GFP_NOFS);
		अगर (new_array == शून्य)
			वापस -ENOMEM;
		स_नकल(new_array, *ea_inode_array,
		       दुरत्व(काष्ठा ext4_xattr_inode_array, inodes[count]));
		kमुक्त(*ea_inode_array);
		*ea_inode_array = new_array;
	पूर्ण
	(*ea_inode_array)->inodes[(*ea_inode_array)->count++] = inode;
	वापस 0;
पूर्ण

/*
 * ext4_xattr_delete_inode()
 *
 * Free extended attribute resources associated with this inode. Traverse
 * all entries and decrement reference on any xattr inodes associated with this
 * inode. This is called immediately beक्रमe an inode is मुक्तd. We have exclusive
 * access to the inode. If an orphan inode is deleted it will also release its
 * references on xattr block and xattr inodes.
 */
पूर्णांक ext4_xattr_delete_inode(handle_t *handle, काष्ठा inode *inode,
			    काष्ठा ext4_xattr_inode_array **ea_inode_array,
			    पूर्णांक extra_credits)
अणु
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext4_xattr_ibody_header *header;
	काष्ठा ext4_iloc iloc = अणु .bh = शून्य पूर्ण;
	काष्ठा ext4_xattr_entry *entry;
	काष्ठा inode *ea_inode;
	पूर्णांक error;

	error = ext4_journal_ensure_credits(handle, extra_credits,
			ext4_मुक्त_metadata_revoke_credits(inode->i_sb, 1));
	अगर (error < 0) अणु
		EXT4_ERROR_INODE(inode, "ensure credits (error %d)", error);
		जाओ cleanup;
	पूर्ण

	अगर (ext4_has_feature_ea_inode(inode->i_sb) &&
	    ext4_test_inode_state(inode, EXT4_STATE_XATTR)) अणु

		error = ext4_get_inode_loc(inode, &iloc);
		अगर (error) अणु
			EXT4_ERROR_INODE(inode, "inode loc (error %d)", error);
			जाओ cleanup;
		पूर्ण

		error = ext4_journal_get_ग_लिखो_access(handle, iloc.bh);
		अगर (error) अणु
			EXT4_ERROR_INODE(inode, "write access (error %d)",
					 error);
			जाओ cleanup;
		पूर्ण

		header = IHDR(inode, ext4_raw_inode(&iloc));
		अगर (header->h_magic == cpu_to_le32(EXT4_XATTR_MAGIC))
			ext4_xattr_inode_dec_ref_all(handle, inode, iloc.bh,
						     IFIRST(header),
						     false /* block_csum */,
						     ea_inode_array,
						     extra_credits,
						     false /* skip_quota */);
	पूर्ण

	अगर (EXT4_I(inode)->i_file_acl) अणु
		bh = ext4_sb_bपढ़ो(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
		अगर (IS_ERR(bh)) अणु
			error = PTR_ERR(bh);
			अगर (error == -EIO) अणु
				EXT4_ERROR_INODE_ERR(inode, EIO,
						     "block %llu read error",
						     EXT4_I(inode)->i_file_acl);
			पूर्ण
			bh = शून्य;
			जाओ cleanup;
		पूर्ण
		error = ext4_xattr_check_block(inode, bh);
		अगर (error)
			जाओ cleanup;

		अगर (ext4_has_feature_ea_inode(inode->i_sb)) अणु
			क्रम (entry = BFIRST(bh); !IS_LAST_ENTRY(entry);
			     entry = EXT4_XATTR_NEXT(entry)) अणु
				अगर (!entry->e_value_inum)
					जारी;
				error = ext4_xattr_inode_iget(inode,
					      le32_to_cpu(entry->e_value_inum),
					      le32_to_cpu(entry->e_hash),
					      &ea_inode);
				अगर (error)
					जारी;
				ext4_xattr_inode_मुक्त_quota(inode, ea_inode,
					      le32_to_cpu(entry->e_value_size));
				iput(ea_inode);
			पूर्ण

		पूर्ण

		ext4_xattr_release_block(handle, inode, bh, ea_inode_array,
					 extra_credits);
		/*
		 * Update i_file_acl value in the same transaction that releases
		 * block.
		 */
		EXT4_I(inode)->i_file_acl = 0;
		error = ext4_mark_inode_dirty(handle, inode);
		अगर (error) अणु
			EXT4_ERROR_INODE(inode, "mark inode dirty (error %d)",
					 error);
			जाओ cleanup;
		पूर्ण
		ext4_fc_mark_ineligible(inode->i_sb, EXT4_FC_REASON_XATTR);
	पूर्ण
	error = 0;
cleanup:
	brअन्यथा(iloc.bh);
	brअन्यथा(bh);
	वापस error;
पूर्ण

व्योम ext4_xattr_inode_array_मुक्त(काष्ठा ext4_xattr_inode_array *ea_inode_array)
अणु
	पूर्णांक idx;

	अगर (ea_inode_array == शून्य)
		वापस;

	क्रम (idx = 0; idx < ea_inode_array->count; ++idx)
		iput(ea_inode_array->inodes[idx]);
	kमुक्त(ea_inode_array);
पूर्ण

/*
 * ext4_xattr_block_cache_insert()
 *
 * Create a new entry in the extended attribute block cache, and insert
 * it unless such an entry is alपढ़ोy in the cache.
 *
 * Returns 0, or a negative error number on failure.
 */
अटल व्योम
ext4_xattr_block_cache_insert(काष्ठा mb_cache *ea_block_cache,
			      काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_xattr_header *header = BHDR(bh);
	__u32 hash = le32_to_cpu(header->h_hash);
	पूर्णांक reusable = le32_to_cpu(header->h_refcount) <
		       EXT4_XATTR_REFCOUNT_MAX;
	पूर्णांक error;

	अगर (!ea_block_cache)
		वापस;
	error = mb_cache_entry_create(ea_block_cache, GFP_NOFS, hash,
				      bh->b_blocknr, reusable);
	अगर (error) अणु
		अगर (error == -EBUSY)
			ea_bdebug(bh, "already in cache");
	पूर्ण अन्यथा
		ea_bdebug(bh, "inserting [%x]", (पूर्णांक)hash);
पूर्ण

/*
 * ext4_xattr_cmp()
 *
 * Compare two extended attribute blocks क्रम equality.
 *
 * Returns 0 अगर the blocks are equal, 1 अगर they dअगरfer, and
 * a negative error number on errors.
 */
अटल पूर्णांक
ext4_xattr_cmp(काष्ठा ext4_xattr_header *header1,
	       काष्ठा ext4_xattr_header *header2)
अणु
	काष्ठा ext4_xattr_entry *entry1, *entry2;

	entry1 = ENTRY(header1+1);
	entry2 = ENTRY(header2+1);
	जबतक (!IS_LAST_ENTRY(entry1)) अणु
		अगर (IS_LAST_ENTRY(entry2))
			वापस 1;
		अगर (entry1->e_hash != entry2->e_hash ||
		    entry1->e_name_index != entry2->e_name_index ||
		    entry1->e_name_len != entry2->e_name_len ||
		    entry1->e_value_size != entry2->e_value_size ||
		    entry1->e_value_inum != entry2->e_value_inum ||
		    स_भेद(entry1->e_name, entry2->e_name, entry1->e_name_len))
			वापस 1;
		अगर (!entry1->e_value_inum &&
		    स_भेद((अक्षर *)header1 + le16_to_cpu(entry1->e_value_offs),
			   (अक्षर *)header2 + le16_to_cpu(entry2->e_value_offs),
			   le32_to_cpu(entry1->e_value_size)))
			वापस 1;

		entry1 = EXT4_XATTR_NEXT(entry1);
		entry2 = EXT4_XATTR_NEXT(entry2);
	पूर्ण
	अगर (!IS_LAST_ENTRY(entry2))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * ext4_xattr_block_cache_find()
 *
 * Find an identical extended attribute block.
 *
 * Returns a poपूर्णांकer to the block found, or शून्य अगर such a block was
 * not found or an error occurred.
 */
अटल काष्ठा buffer_head *
ext4_xattr_block_cache_find(काष्ठा inode *inode,
			    काष्ठा ext4_xattr_header *header,
			    काष्ठा mb_cache_entry **pce)
अणु
	__u32 hash = le32_to_cpu(header->h_hash);
	काष्ठा mb_cache_entry *ce;
	काष्ठा mb_cache *ea_block_cache = EA_BLOCK_CACHE(inode);

	अगर (!ea_block_cache)
		वापस शून्य;
	अगर (!header->h_hash)
		वापस शून्य;  /* never share */
	ea_idebug(inode, "looking for cached blocks [%x]", (पूर्णांक)hash);
	ce = mb_cache_entry_find_first(ea_block_cache, hash);
	जबतक (ce) अणु
		काष्ठा buffer_head *bh;

		bh = ext4_sb_bपढ़ो(inode->i_sb, ce->e_value, REQ_PRIO);
		अगर (IS_ERR(bh)) अणु
			अगर (PTR_ERR(bh) == -ENOMEM)
				वापस शून्य;
			bh = शून्य;
			EXT4_ERROR_INODE(inode, "block %lu read error",
					 (अचिन्हित दीर्घ)ce->e_value);
		पूर्ण अन्यथा अगर (ext4_xattr_cmp(header, BHDR(bh)) == 0) अणु
			*pce = ce;
			वापस bh;
		पूर्ण
		brअन्यथा(bh);
		ce = mb_cache_entry_find_next(ea_block_cache, ce);
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा NAME_HASH_SHIFT 5
#घोषणा VALUE_HASH_SHIFT 16

/*
 * ext4_xattr_hash_entry()
 *
 * Compute the hash of an extended attribute.
 */
अटल __le32 ext4_xattr_hash_entry(अक्षर *name, माप_प्रकार name_len, __le32 *value,
				    माप_प्रकार value_count)
अणु
	__u32 hash = 0;

	जबतक (name_len--) अणु
		hash = (hash << NAME_HASH_SHIFT) ^
		       (hash >> (8*माप(hash) - NAME_HASH_SHIFT)) ^
		       *name++;
	पूर्ण
	जबतक (value_count--) अणु
		hash = (hash << VALUE_HASH_SHIFT) ^
		       (hash >> (8*माप(hash) - VALUE_HASH_SHIFT)) ^
		       le32_to_cpu(*value++);
	पूर्ण
	वापस cpu_to_le32(hash);
पूर्ण

#अघोषित NAME_HASH_SHIFT
#अघोषित VALUE_HASH_SHIFT

#घोषणा BLOCK_HASH_SHIFT 16

/*
 * ext4_xattr_rehash()
 *
 * Re-compute the extended attribute hash value after an entry has changed.
 */
अटल व्योम ext4_xattr_rehash(काष्ठा ext4_xattr_header *header)
अणु
	काष्ठा ext4_xattr_entry *here;
	__u32 hash = 0;

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
		here = EXT4_XATTR_NEXT(here);
	पूर्ण
	header->h_hash = cpu_to_le32(hash);
पूर्ण

#अघोषित BLOCK_HASH_SHIFT

#घोषणा	HASH_BUCKET_BITS	10

काष्ठा mb_cache *
ext4_xattr_create_cache(व्योम)
अणु
	वापस mb_cache_create(HASH_BUCKET_BITS);
पूर्ण

व्योम ext4_xattr_destroy_cache(काष्ठा mb_cache *cache)
अणु
	अगर (cache)
		mb_cache_destroy(cache);
पूर्ण

