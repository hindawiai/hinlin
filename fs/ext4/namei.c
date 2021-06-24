<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/namei.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/namei.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 *  Directory entry file type support and क्रमward compatibility hooks
 *	क्रम B-tree directories by Theoकरोre Ts'o (tytso@mit.edu), 1998
 *  Hash Tree Directory indexing (c)
 *	Daniel Phillips, 2001
 *  Hash Tree Directory indexing porting
 *	Christopher Li, 2002
 *  Hash Tree Directory indexing cleanup
 *	Theoकरोre Ts'o, 2002
 */

#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/समय.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/bपन.स>
#समावेश <linux/iversion.h>
#समावेश <linux/unicode.h>
#समावेश "ext4.h"
#समावेश "ext4_jbd2.h"

#समावेश "xattr.h"
#समावेश "acl.h"

#समावेश <trace/events/ext4.h>
/*
 * define how far ahead to पढ़ो directories जबतक searching them.
 */
#घोषणा NAMEI_RA_CHUNKS  2
#घोषणा NAMEI_RA_BLOCKS  4
#घोषणा NAMEI_RA_SIZE	     (NAMEI_RA_CHUNKS * NAMEI_RA_BLOCKS)

अटल काष्ठा buffer_head *ext4_append(handle_t *handle,
					काष्ठा inode *inode,
					ext4_lblk_t *block)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	अगर (unlikely(EXT4_SB(inode->i_sb)->s_max_dir_size_kb &&
		     ((inode->i_size >> 10) >=
		      EXT4_SB(inode->i_sb)->s_max_dir_size_kb)))
		वापस ERR_PTR(-ENOSPC);

	*block = inode->i_size >> inode->i_sb->s_blocksize_bits;

	bh = ext4_bपढ़ो(handle, inode, *block, EXT4_GET_BLOCKS_CREATE);
	अगर (IS_ERR(bh))
		वापस bh;
	inode->i_size += inode->i_sb->s_blocksize;
	EXT4_I(inode)->i_disksize = inode->i_size;
	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (err) अणु
		brअन्यथा(bh);
		ext4_std_error(inode->i_sb, err);
		वापस ERR_PTR(err);
	पूर्ण
	वापस bh;
पूर्ण

अटल पूर्णांक ext4_dx_csum_verअगरy(काष्ठा inode *inode,
			       काष्ठा ext4_dir_entry *dirent);

/*
 * Hपूर्णांकs to ext4_पढ़ो_dirblock regarding whether we expect a directory
 * block being पढ़ो to be an index block, or a block containing
 * directory entries (and अगर the latter, whether it was found via a
 * logical block in an htree index block).  This is used to control
 * what sort of sanity checkinig ext4_पढ़ो_dirblock() will करो on the
 * directory block पढ़ो from the storage device.  EITHER will means
 * the caller करोesn't know what kind of directory block will be पढ़ो,
 * so no specअगरic verअगरication will be करोne.
 */
प्रकार क्रमागत अणु
	EITHER, INDEX, सूचीENT, सूचीENT_HTREE
पूर्ण dirblock_type_t;

#घोषणा ext4_पढ़ो_dirblock(inode, block, type) \
	__ext4_पढ़ो_dirblock((inode), (block), (type), __func__, __LINE__)

अटल काष्ठा buffer_head *__ext4_पढ़ो_dirblock(काष्ठा inode *inode,
						ext4_lblk_t block,
						dirblock_type_t type,
						स्थिर अक्षर *func,
						अचिन्हित पूर्णांक line)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा ext4_dir_entry *dirent;
	पूर्णांक is_dx_block = 0;

	अगर (ext4_simulate_fail(inode->i_sb, EXT4_SIM_सूचीBLOCK_EIO))
		bh = ERR_PTR(-EIO);
	अन्यथा
		bh = ext4_bपढ़ो(शून्य, inode, block, 0);
	अगर (IS_ERR(bh)) अणु
		__ext4_warning(inode->i_sb, func, line,
			       "inode #%lu: lblock %lu: comm %s: "
			       "error %ld reading directory block",
			       inode->i_ino, (अचिन्हित दीर्घ)block,
			       current->comm, PTR_ERR(bh));

		वापस bh;
	पूर्ण
	अगर (!bh && (type == INDEX || type == सूचीENT_HTREE)) अणु
		ext4_error_inode(inode, func, line, block,
				 "Directory hole found for htree %s block",
				 (type == INDEX) ? "index" : "leaf");
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण
	अगर (!bh)
		वापस शून्य;
	dirent = (काष्ठा ext4_dir_entry *) bh->b_data;
	/* Determine whether or not we have an index block */
	अगर (is_dx(inode)) अणु
		अगर (block == 0)
			is_dx_block = 1;
		अन्यथा अगर (ext4_rec_len_from_disk(dirent->rec_len,
						inode->i_sb->s_blocksize) ==
			 inode->i_sb->s_blocksize)
			is_dx_block = 1;
	पूर्ण
	अगर (!is_dx_block && type == INDEX) अणु
		ext4_error_inode(inode, func, line, block,
		       "directory leaf block found instead of index block");
		brअन्यथा(bh);
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण
	अगर (!ext4_has_metadata_csum(inode->i_sb) ||
	    buffer_verअगरied(bh))
		वापस bh;

	/*
	 * An empty leaf block can get mistaken क्रम a index block; क्रम
	 * this reason, we can only check the index checksum when the
	 * caller is sure it should be an index block.
	 */
	अगर (is_dx_block && type == INDEX) अणु
		अगर (ext4_dx_csum_verअगरy(inode, dirent) &&
		    !ext4_simulate_fail(inode->i_sb, EXT4_SIM_सूचीBLOCK_CRC))
			set_buffer_verअगरied(bh);
		अन्यथा अणु
			ext4_error_inode_err(inode, func, line, block,
					     EFSBADCRC,
					     "Directory index failed checksum");
			brअन्यथा(bh);
			वापस ERR_PTR(-EFSBADCRC);
		पूर्ण
	पूर्ण
	अगर (!is_dx_block) अणु
		अगर (ext4_dirblock_csum_verअगरy(inode, bh) &&
		    !ext4_simulate_fail(inode->i_sb, EXT4_SIM_सूचीBLOCK_CRC))
			set_buffer_verअगरied(bh);
		अन्यथा अणु
			ext4_error_inode_err(inode, func, line, block,
					     EFSBADCRC,
					     "Directory block failed checksum");
			brअन्यथा(bh);
			वापस ERR_PTR(-EFSBADCRC);
		पूर्ण
	पूर्ण
	वापस bh;
पूर्ण

#अगर_घोषित DX_DEBUG
#घोषणा dxtrace(command) command
#अन्यथा
#घोषणा dxtrace(command)
#पूर्ण_अगर

काष्ठा fake_dirent
अणु
	__le32 inode;
	__le16 rec_len;
	u8 name_len;
	u8 file_type;
पूर्ण;

काष्ठा dx_countlimit
अणु
	__le16 limit;
	__le16 count;
पूर्ण;

काष्ठा dx_entry
अणु
	__le32 hash;
	__le32 block;
पूर्ण;

/*
 * dx_root_info is laid out so that अगर it should somehow get overlaid by a
 * dirent the two low bits of the hash version will be zero.  Thereक्रमe, the
 * hash version mod 4 should never be 0.  Sincerely, the paranoia deparपंचांगent.
 */

काष्ठा dx_root
अणु
	काष्ठा fake_dirent करोt;
	अक्षर करोt_name[4];
	काष्ठा fake_dirent करोtकरोt;
	अक्षर करोtकरोt_name[4];
	काष्ठा dx_root_info
	अणु
		__le32 reserved_zero;
		u8 hash_version;
		u8 info_length; /* 8 */
		u8 indirect_levels;
		u8 unused_flags;
	पूर्ण
	info;
	काष्ठा dx_entry	entries[];
पूर्ण;

काष्ठा dx_node
अणु
	काष्ठा fake_dirent fake;
	काष्ठा dx_entry	entries[];
पूर्ण;


काष्ठा dx_frame
अणु
	काष्ठा buffer_head *bh;
	काष्ठा dx_entry *entries;
	काष्ठा dx_entry *at;
पूर्ण;

काष्ठा dx_map_entry
अणु
	u32 hash;
	u16 offs;
	u16 size;
पूर्ण;

/*
 * This goes at the end of each htree block.
 */
काष्ठा dx_tail अणु
	u32 dt_reserved;
	__le32 dt_checksum;	/* crc32c(uuid+inum+dirblock) */
पूर्ण;

अटल अंतरभूत ext4_lblk_t dx_get_block(काष्ठा dx_entry *entry);
अटल व्योम dx_set_block(काष्ठा dx_entry *entry, ext4_lblk_t value);
अटल अंतरभूत अचिन्हित dx_get_hash(काष्ठा dx_entry *entry);
अटल व्योम dx_set_hash(काष्ठा dx_entry *entry, अचिन्हित value);
अटल अचिन्हित dx_get_count(काष्ठा dx_entry *entries);
अटल अचिन्हित dx_get_limit(काष्ठा dx_entry *entries);
अटल व्योम dx_set_count(काष्ठा dx_entry *entries, अचिन्हित value);
अटल व्योम dx_set_limit(काष्ठा dx_entry *entries, अचिन्हित value);
अटल अचिन्हित dx_root_limit(काष्ठा inode *dir, अचिन्हित infosize);
अटल अचिन्हित dx_node_limit(काष्ठा inode *dir);
अटल काष्ठा dx_frame *dx_probe(काष्ठा ext4_filename *fname,
				 काष्ठा inode *dir,
				 काष्ठा dx_hash_info *hinfo,
				 काष्ठा dx_frame *frame);
अटल व्योम dx_release(काष्ठा dx_frame *frames);
अटल पूर्णांक dx_make_map(काष्ठा inode *dir, काष्ठा ext4_dir_entry_2 *de,
		       अचिन्हित blocksize, काष्ठा dx_hash_info *hinfo,
		       काष्ठा dx_map_entry map[]);
अटल व्योम dx_sort_map(काष्ठा dx_map_entry *map, अचिन्हित count);
अटल काष्ठा ext4_dir_entry_2 *dx_move_dirents(काष्ठा inode *dir, अक्षर *from,
					अक्षर *to, काष्ठा dx_map_entry *offsets,
					पूर्णांक count, अचिन्हित पूर्णांक blocksize);
अटल काष्ठा ext4_dir_entry_2 *dx_pack_dirents(काष्ठा inode *dir, अक्षर *base,
						अचिन्हित पूर्णांक blocksize);
अटल व्योम dx_insert_block(काष्ठा dx_frame *frame,
					u32 hash, ext4_lblk_t block);
अटल पूर्णांक ext4_htree_next_block(काष्ठा inode *dir, __u32 hash,
				 काष्ठा dx_frame *frame,
				 काष्ठा dx_frame *frames,
				 __u32 *start_hash);
अटल काष्ठा buffer_head * ext4_dx_find_entry(काष्ठा inode *dir,
		काष्ठा ext4_filename *fname,
		काष्ठा ext4_dir_entry_2 **res_dir);
अटल पूर्णांक ext4_dx_add_entry(handle_t *handle, काष्ठा ext4_filename *fname,
			     काष्ठा inode *dir, काष्ठा inode *inode);

/* checksumming functions */
व्योम ext4_initialize_dirent_tail(काष्ठा buffer_head *bh,
				 अचिन्हित पूर्णांक blocksize)
अणु
	काष्ठा ext4_dir_entry_tail *t = EXT4_सूचीENT_TAIL(bh->b_data, blocksize);

	स_रखो(t, 0, माप(काष्ठा ext4_dir_entry_tail));
	t->det_rec_len = ext4_rec_len_to_disk(
			माप(काष्ठा ext4_dir_entry_tail), blocksize);
	t->det_reserved_ft = EXT4_FT_सूची_CSUM;
पूर्ण

/* Walk through a dirent block to find a checksum "dirent" at the tail */
अटल काष्ठा ext4_dir_entry_tail *get_dirent_tail(काष्ठा inode *inode,
						   काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_dir_entry_tail *t;

#अगर_घोषित PARANOID
	काष्ठा ext4_dir_entry *d, *top;

	d = (काष्ठा ext4_dir_entry *)bh->b_data;
	top = (काष्ठा ext4_dir_entry *)(bh->b_data +
		(EXT4_BLOCK_SIZE(inode->i_sb) -
		 माप(काष्ठा ext4_dir_entry_tail)));
	जबतक (d < top && d->rec_len)
		d = (काष्ठा ext4_dir_entry *)(((व्योम *)d) +
		    le16_to_cpu(d->rec_len));

	अगर (d != top)
		वापस शून्य;

	t = (काष्ठा ext4_dir_entry_tail *)d;
#अन्यथा
	t = EXT4_सूचीENT_TAIL(bh->b_data, EXT4_BLOCK_SIZE(inode->i_sb));
#पूर्ण_अगर

	अगर (t->det_reserved_zero1 ||
	    le16_to_cpu(t->det_rec_len) != माप(काष्ठा ext4_dir_entry_tail) ||
	    t->det_reserved_zero2 ||
	    t->det_reserved_ft != EXT4_FT_सूची_CSUM)
		वापस शून्य;

	वापस t;
पूर्ण

अटल __le32 ext4_dirblock_csum(काष्ठा inode *inode, व्योम *dirent, पूर्णांक size)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	__u32 csum;

	csum = ext4_chksum(sbi, ei->i_csum_seed, (__u8 *)dirent, size);
	वापस cpu_to_le32(csum);
पूर्ण

#घोषणा warn_no_space_क्रम_csum(inode)					\
	__warn_no_space_क्रम_csum((inode), __func__, __LINE__)

अटल व्योम __warn_no_space_क्रम_csum(काष्ठा inode *inode, स्थिर अक्षर *func,
				     अचिन्हित पूर्णांक line)
अणु
	__ext4_warning_inode(inode, func, line,
		"No space for directory leaf checksum. Please run e2fsck -D.");
पूर्ण

पूर्णांक ext4_dirblock_csum_verअगरy(काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_dir_entry_tail *t;

	अगर (!ext4_has_metadata_csum(inode->i_sb))
		वापस 1;

	t = get_dirent_tail(inode, bh);
	अगर (!t) अणु
		warn_no_space_क्रम_csum(inode);
		वापस 0;
	पूर्ण

	अगर (t->det_checksum != ext4_dirblock_csum(inode, bh->b_data,
						  (अक्षर *)t - bh->b_data))
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम ext4_dirblock_csum_set(काष्ठा inode *inode,
				 काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_dir_entry_tail *t;

	अगर (!ext4_has_metadata_csum(inode->i_sb))
		वापस;

	t = get_dirent_tail(inode, bh);
	अगर (!t) अणु
		warn_no_space_क्रम_csum(inode);
		वापस;
	पूर्ण

	t->det_checksum = ext4_dirblock_csum(inode, bh->b_data,
					     (अक्षर *)t - bh->b_data);
पूर्ण

पूर्णांक ext4_handle_dirty_dirblock(handle_t *handle,
			       काष्ठा inode *inode,
			       काष्ठा buffer_head *bh)
अणु
	ext4_dirblock_csum_set(inode, bh);
	वापस ext4_handle_dirty_metadata(handle, inode, bh);
पूर्ण

अटल काष्ठा dx_countlimit *get_dx_countlimit(काष्ठा inode *inode,
					       काष्ठा ext4_dir_entry *dirent,
					       पूर्णांक *offset)
अणु
	काष्ठा ext4_dir_entry *dp;
	काष्ठा dx_root_info *root;
	पूर्णांक count_offset;

	अगर (le16_to_cpu(dirent->rec_len) == EXT4_BLOCK_SIZE(inode->i_sb))
		count_offset = 8;
	अन्यथा अगर (le16_to_cpu(dirent->rec_len) == 12) अणु
		dp = (काष्ठा ext4_dir_entry *)(((व्योम *)dirent) + 12);
		अगर (le16_to_cpu(dp->rec_len) !=
		    EXT4_BLOCK_SIZE(inode->i_sb) - 12)
			वापस शून्य;
		root = (काष्ठा dx_root_info *)(((व्योम *)dp + 12));
		अगर (root->reserved_zero ||
		    root->info_length != माप(काष्ठा dx_root_info))
			वापस शून्य;
		count_offset = 32;
	पूर्ण अन्यथा
		वापस शून्य;

	अगर (offset)
		*offset = count_offset;
	वापस (काष्ठा dx_countlimit *)(((व्योम *)dirent) + count_offset);
पूर्ण

अटल __le32 ext4_dx_csum(काष्ठा inode *inode, काष्ठा ext4_dir_entry *dirent,
			   पूर्णांक count_offset, पूर्णांक count, काष्ठा dx_tail *t)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	__u32 csum;
	पूर्णांक size;
	__u32 dummy_csum = 0;
	पूर्णांक offset = दुरत्व(काष्ठा dx_tail, dt_checksum);

	size = count_offset + (count * माप(काष्ठा dx_entry));
	csum = ext4_chksum(sbi, ei->i_csum_seed, (__u8 *)dirent, size);
	csum = ext4_chksum(sbi, csum, (__u8 *)t, offset);
	csum = ext4_chksum(sbi, csum, (__u8 *)&dummy_csum, माप(dummy_csum));

	वापस cpu_to_le32(csum);
पूर्ण

अटल पूर्णांक ext4_dx_csum_verअगरy(काष्ठा inode *inode,
			       काष्ठा ext4_dir_entry *dirent)
अणु
	काष्ठा dx_countlimit *c;
	काष्ठा dx_tail *t;
	पूर्णांक count_offset, limit, count;

	अगर (!ext4_has_metadata_csum(inode->i_sb))
		वापस 1;

	c = get_dx_countlimit(inode, dirent, &count_offset);
	अगर (!c) अणु
		EXT4_ERROR_INODE(inode, "dir seems corrupt?  Run e2fsck -D.");
		वापस 0;
	पूर्ण
	limit = le16_to_cpu(c->limit);
	count = le16_to_cpu(c->count);
	अगर (count_offset + (limit * माप(काष्ठा dx_entry)) >
	    EXT4_BLOCK_SIZE(inode->i_sb) - माप(काष्ठा dx_tail)) अणु
		warn_no_space_क्रम_csum(inode);
		वापस 0;
	पूर्ण
	t = (काष्ठा dx_tail *)(((काष्ठा dx_entry *)c) + limit);

	अगर (t->dt_checksum != ext4_dx_csum(inode, dirent, count_offset,
					    count, t))
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम ext4_dx_csum_set(काष्ठा inode *inode, काष्ठा ext4_dir_entry *dirent)
अणु
	काष्ठा dx_countlimit *c;
	काष्ठा dx_tail *t;
	पूर्णांक count_offset, limit, count;

	अगर (!ext4_has_metadata_csum(inode->i_sb))
		वापस;

	c = get_dx_countlimit(inode, dirent, &count_offset);
	अगर (!c) अणु
		EXT4_ERROR_INODE(inode, "dir seems corrupt?  Run e2fsck -D.");
		वापस;
	पूर्ण
	limit = le16_to_cpu(c->limit);
	count = le16_to_cpu(c->count);
	अगर (count_offset + (limit * माप(काष्ठा dx_entry)) >
	    EXT4_BLOCK_SIZE(inode->i_sb) - माप(काष्ठा dx_tail)) अणु
		warn_no_space_क्रम_csum(inode);
		वापस;
	पूर्ण
	t = (काष्ठा dx_tail *)(((काष्ठा dx_entry *)c) + limit);

	t->dt_checksum = ext4_dx_csum(inode, dirent, count_offset, count, t);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_handle_dirty_dx_node(handle_t *handle,
					    काष्ठा inode *inode,
					    काष्ठा buffer_head *bh)
अणु
	ext4_dx_csum_set(inode, (काष्ठा ext4_dir_entry *)bh->b_data);
	वापस ext4_handle_dirty_metadata(handle, inode, bh);
पूर्ण

/*
 * p is at least 6 bytes beक्रमe the end of page
 */
अटल अंतरभूत काष्ठा ext4_dir_entry_2 *
ext4_next_entry(काष्ठा ext4_dir_entry_2 *p, अचिन्हित दीर्घ blocksize)
अणु
	वापस (काष्ठा ext4_dir_entry_2 *)((अक्षर *)p +
		ext4_rec_len_from_disk(p->rec_len, blocksize));
पूर्ण

/*
 * Future: use high four bits of block क्रम coalesce-on-delete flags
 * Mask them off क्रम now.
 */

अटल अंतरभूत ext4_lblk_t dx_get_block(काष्ठा dx_entry *entry)
अणु
	वापस le32_to_cpu(entry->block) & 0x0fffffff;
पूर्ण

अटल अंतरभूत व्योम dx_set_block(काष्ठा dx_entry *entry, ext4_lblk_t value)
अणु
	entry->block = cpu_to_le32(value);
पूर्ण

अटल अंतरभूत अचिन्हित dx_get_hash(काष्ठा dx_entry *entry)
अणु
	वापस le32_to_cpu(entry->hash);
पूर्ण

अटल अंतरभूत व्योम dx_set_hash(काष्ठा dx_entry *entry, अचिन्हित value)
अणु
	entry->hash = cpu_to_le32(value);
पूर्ण

अटल अंतरभूत अचिन्हित dx_get_count(काष्ठा dx_entry *entries)
अणु
	वापस le16_to_cpu(((काष्ठा dx_countlimit *) entries)->count);
पूर्ण

अटल अंतरभूत अचिन्हित dx_get_limit(काष्ठा dx_entry *entries)
अणु
	वापस le16_to_cpu(((काष्ठा dx_countlimit *) entries)->limit);
पूर्ण

अटल अंतरभूत व्योम dx_set_count(काष्ठा dx_entry *entries, अचिन्हित value)
अणु
	((काष्ठा dx_countlimit *) entries)->count = cpu_to_le16(value);
पूर्ण

अटल अंतरभूत व्योम dx_set_limit(काष्ठा dx_entry *entries, अचिन्हित value)
अणु
	((काष्ठा dx_countlimit *) entries)->limit = cpu_to_le16(value);
पूर्ण

अटल अंतरभूत अचिन्हित dx_root_limit(काष्ठा inode *dir, अचिन्हित infosize)
अणु
	अचिन्हित पूर्णांक entry_space = dir->i_sb->s_blocksize -
			ext4_dir_rec_len(1, शून्य) -
			ext4_dir_rec_len(2, शून्य) - infosize;

	अगर (ext4_has_metadata_csum(dir->i_sb))
		entry_space -= माप(काष्ठा dx_tail);
	वापस entry_space / माप(काष्ठा dx_entry);
पूर्ण

अटल अंतरभूत अचिन्हित dx_node_limit(काष्ठा inode *dir)
अणु
	अचिन्हित पूर्णांक entry_space = dir->i_sb->s_blocksize -
			ext4_dir_rec_len(0, dir);

	अगर (ext4_has_metadata_csum(dir->i_sb))
		entry_space -= माप(काष्ठा dx_tail);
	वापस entry_space / माप(काष्ठा dx_entry);
पूर्ण

/*
 * Debug
 */
#अगर_घोषित DX_DEBUG
अटल व्योम dx_show_index(अक्षर * label, काष्ठा dx_entry *entries)
अणु
	पूर्णांक i, n = dx_get_count (entries);
	prपूर्णांकk(KERN_DEBUG "%s index", label);
	क्रम (i = 0; i < n; i++) अणु
		prपूर्णांकk(KERN_CONT " %x->%lu",
		       i ? dx_get_hash(entries + i) : 0,
		       (अचिन्हित दीर्घ)dx_get_block(entries + i));
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

काष्ठा stats
अणु
	अचिन्हित names;
	अचिन्हित space;
	अचिन्हित bcount;
पूर्ण;

अटल काष्ठा stats dx_show_leaf(काष्ठा inode *dir,
				काष्ठा dx_hash_info *hinfo,
				काष्ठा ext4_dir_entry_2 *de,
				पूर्णांक size, पूर्णांक show_names)
अणु
	अचिन्हित names = 0, space = 0;
	अक्षर *base = (अक्षर *) de;
	काष्ठा dx_hash_info h = *hinfo;

	prपूर्णांकk("names: ");
	जबतक ((अक्षर *) de < base + size)
	अणु
		अगर (de->inode)
		अणु
			अगर (show_names)
			अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
				पूर्णांक len;
				अक्षर *name;
				काष्ठा fscrypt_str fname_crypto_str =
					FSTR_INIT(शून्य, 0);
				पूर्णांक res = 0;

				name  = de->name;
				len = de->name_len;
				अगर (!IS_ENCRYPTED(dir)) अणु
					/* Directory is not encrypted */
					ext4fs_dirhash(dir, de->name,
						de->name_len, &h);
					prपूर्णांकk("%*.s:(U)%x.%u ", len,
					       name, h.hash,
					       (अचिन्हित) ((अक्षर *) de
							   - base));
				पूर्ण अन्यथा अणु
					काष्ठा fscrypt_str de_name =
						FSTR_INIT(name, len);

					/* Directory is encrypted */
					res = fscrypt_fname_alloc_buffer(
						len, &fname_crypto_str);
					अगर (res)
						prपूर्णांकk(KERN_WARNING "Error "
							"allocating crypto "
							"buffer--skipping "
							"crypto\n");
					res = fscrypt_fname_disk_to_usr(dir,
						0, 0, &de_name,
						&fname_crypto_str);
					अगर (res) अणु
						prपूर्णांकk(KERN_WARNING "Error "
							"converting filename "
							"from disk to usr"
							"\n");
						name = "??";
						len = 2;
					पूर्ण अन्यथा अणु
						name = fname_crypto_str.name;
						len = fname_crypto_str.len;
					पूर्ण
					अगर (IS_CASEFOLDED(dir))
						h.hash = EXT4_सूचीENT_HASH(de);
					अन्यथा
						ext4fs_dirhash(dir, de->name,
						       de->name_len, &h);
					prपूर्णांकk("%*.s:(E)%x.%u ", len, name,
					       h.hash, (अचिन्हित) ((अक्षर *) de
								   - base));
					fscrypt_fname_मुक्त_buffer(
							&fname_crypto_str);
				पूर्ण
#अन्यथा
				पूर्णांक len = de->name_len;
				अक्षर *name = de->name;
				ext4fs_dirhash(dir, de->name, de->name_len, &h);
				prपूर्णांकk("%*.s:%x.%u ", len, name, h.hash,
				       (अचिन्हित) ((अक्षर *) de - base));
#पूर्ण_अगर
			पूर्ण
			space += ext4_dir_rec_len(de->name_len, dir);
			names++;
		पूर्ण
		de = ext4_next_entry(de, size);
	पूर्ण
	prपूर्णांकk(KERN_CONT "(%i)\n", names);
	वापस (काष्ठा stats) अणु names, space, 1 पूर्ण;
पूर्ण

काष्ठा stats dx_show_entries(काष्ठा dx_hash_info *hinfo, काष्ठा inode *dir,
			     काष्ठा dx_entry *entries, पूर्णांक levels)
अणु
	अचिन्हित blocksize = dir->i_sb->s_blocksize;
	अचिन्हित count = dx_get_count(entries), names = 0, space = 0, i;
	अचिन्हित bcount = 0;
	काष्ठा buffer_head *bh;
	prपूर्णांकk("%i indexed blocks...\n", count);
	क्रम (i = 0; i < count; i++, entries++)
	अणु
		ext4_lblk_t block = dx_get_block(entries);
		ext4_lblk_t hash  = i ? dx_get_hash(entries): 0;
		u32 range = i < count - 1? (dx_get_hash(entries + 1) - hash): ~hash;
		काष्ठा stats stats;
		prपूर्णांकk("%s%3u:%03u hash %8x/%8x ",levels?"":"   ", i, block, hash, range);
		bh = ext4_bपढ़ो(शून्य,dir, block, 0);
		अगर (!bh || IS_ERR(bh))
			जारी;
		stats = levels?
		   dx_show_entries(hinfo, dir, ((काष्ठा dx_node *) bh->b_data)->entries, levels - 1):
		   dx_show_leaf(dir, hinfo, (काष्ठा ext4_dir_entry_2 *)
			bh->b_data, blocksize, 0);
		names += stats.names;
		space += stats.space;
		bcount += stats.bcount;
		brअन्यथा(bh);
	पूर्ण
	अगर (bcount)
		prपूर्णांकk(KERN_DEBUG "%snames %u, fullness %u (%u%%)\n",
		       levels ? "" : "   ", names, space/bcount,
		       (space/bcount)*100/blocksize);
	वापस (काष्ठा stats) अणु names, space, bcountपूर्ण;
पूर्ण

/*
 * Linear search cross check
 */
अटल अंतरभूत व्योम htree_rep_invariant_check(काष्ठा dx_entry *at,
					     काष्ठा dx_entry *target,
					     u32 hash, अचिन्हित पूर्णांक n)
अणु
	जबतक (n--) अणु
		dxtrace(prपूर्णांकk(KERN_CONT ","));
		अगर (dx_get_hash(++at) > hash) अणु
			at--;
			अवरोध;
		पूर्ण
	पूर्ण
	ASSERT(at == target - 1);
पूर्ण
#अन्यथा /* DX_DEBUG */
अटल अंतरभूत व्योम htree_rep_invariant_check(काष्ठा dx_entry *at,
					     काष्ठा dx_entry *target,
					     u32 hash, अचिन्हित पूर्णांक n)
अणु
पूर्ण
#पूर्ण_अगर /* DX_DEBUG */

/*
 * Probe क्रम a directory leaf block to search.
 *
 * dx_probe can वापस ERR_BAD_DX_सूची, which means there was a क्रमmat
 * error in the directory index, and the caller should fall back to
 * searching the directory normally.  The callers of dx_probe **MUST**
 * check क्रम this error code, and make sure it never माला_लो reflected
 * back to userspace.
 */
अटल काष्ठा dx_frame *
dx_probe(काष्ठा ext4_filename *fname, काष्ठा inode *dir,
	 काष्ठा dx_hash_info *hinfo, काष्ठा dx_frame *frame_in)
अणु
	अचिन्हित count, indirect;
	काष्ठा dx_entry *at, *entries, *p, *q, *m;
	काष्ठा dx_root *root;
	काष्ठा dx_frame *frame = frame_in;
	काष्ठा dx_frame *ret_err = ERR_PTR(ERR_BAD_DX_सूची);
	u32 hash;

	स_रखो(frame_in, 0, EXT4_HTREE_LEVEL * माप(frame_in[0]));
	frame->bh = ext4_पढ़ो_dirblock(dir, 0, INDEX);
	अगर (IS_ERR(frame->bh))
		वापस (काष्ठा dx_frame *) frame->bh;

	root = (काष्ठा dx_root *) frame->bh->b_data;
	अगर (root->info.hash_version != DX_HASH_TEA &&
	    root->info.hash_version != DX_HASH_HALF_MD4 &&
	    root->info.hash_version != DX_HASH_LEGACY &&
	    root->info.hash_version != DX_HASH_SIPHASH) अणु
		ext4_warning_inode(dir, "Unrecognised inode hash code %u",
				   root->info.hash_version);
		जाओ fail;
	पूर्ण
	अगर (ext4_hash_in_dirent(dir)) अणु
		अगर (root->info.hash_version != DX_HASH_SIPHASH) अणु
			ext4_warning_inode(dir,
				"Hash in dirent, but hash is not SIPHASH");
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (root->info.hash_version == DX_HASH_SIPHASH) अणु
			ext4_warning_inode(dir,
				"Hash code is SIPHASH, but hash not in dirent");
			जाओ fail;
		पूर्ण
	पूर्ण
	अगर (fname)
		hinfo = &fname->hinfo;
	hinfo->hash_version = root->info.hash_version;
	अगर (hinfo->hash_version <= DX_HASH_TEA)
		hinfo->hash_version += EXT4_SB(dir->i_sb)->s_hash_अचिन्हित;
	hinfo->seed = EXT4_SB(dir->i_sb)->s_hash_seed;
	/* hash is alपढ़ोy computed क्रम encrypted हालfolded directory */
	अगर (fname && fname_name(fname) &&
				!(IS_ENCRYPTED(dir) && IS_CASEFOLDED(dir)))
		ext4fs_dirhash(dir, fname_name(fname), fname_len(fname), hinfo);
	hash = hinfo->hash;

	अगर (root->info.unused_flags & 1) अणु
		ext4_warning_inode(dir, "Unimplemented hash flags: %#06x",
				   root->info.unused_flags);
		जाओ fail;
	पूर्ण

	indirect = root->info.indirect_levels;
	अगर (indirect >= ext4_dir_htree_level(dir->i_sb)) अणु
		ext4_warning(dir->i_sb,
			     "Directory (ino: %lu) htree depth %#06x exceed"
			     "supported value", dir->i_ino,
			     ext4_dir_htree_level(dir->i_sb));
		अगर (ext4_dir_htree_level(dir->i_sb) < EXT4_HTREE_LEVEL) अणु
			ext4_warning(dir->i_sb, "Enable large directory "
						"feature to access it");
		पूर्ण
		जाओ fail;
	पूर्ण

	entries = (काष्ठा dx_entry *)(((अक्षर *)&root->info) +
				      root->info.info_length);

	अगर (dx_get_limit(entries) != dx_root_limit(dir,
						   root->info.info_length)) अणु
		ext4_warning_inode(dir, "dx entry: limit %u != root limit %u",
				   dx_get_limit(entries),
				   dx_root_limit(dir, root->info.info_length));
		जाओ fail;
	पूर्ण

	dxtrace(prपूर्णांकk("Look up %x", hash));
	जबतक (1) अणु
		count = dx_get_count(entries);
		अगर (!count || count > dx_get_limit(entries)) अणु
			ext4_warning_inode(dir,
					   "dx entry: count %u beyond limit %u",
					   count, dx_get_limit(entries));
			जाओ fail;
		पूर्ण

		p = entries + 1;
		q = entries + count - 1;
		जबतक (p <= q) अणु
			m = p + (q - p) / 2;
			dxtrace(prपूर्णांकk(KERN_CONT "."));
			अगर (dx_get_hash(m) > hash)
				q = m - 1;
			अन्यथा
				p = m + 1;
		पूर्ण

		htree_rep_invariant_check(entries, p, hash, count - 1);

		at = p - 1;
		dxtrace(prपूर्णांकk(KERN_CONT " %x->%u\n",
			       at == entries ? 0 : dx_get_hash(at),
			       dx_get_block(at)));
		frame->entries = entries;
		frame->at = at;
		अगर (!indirect--)
			वापस frame;
		frame++;
		frame->bh = ext4_पढ़ो_dirblock(dir, dx_get_block(at), INDEX);
		अगर (IS_ERR(frame->bh)) अणु
			ret_err = (काष्ठा dx_frame *) frame->bh;
			frame->bh = शून्य;
			जाओ fail;
		पूर्ण
		entries = ((काष्ठा dx_node *) frame->bh->b_data)->entries;

		अगर (dx_get_limit(entries) != dx_node_limit(dir)) अणु
			ext4_warning_inode(dir,
				"dx entry: limit %u != node limit %u",
				dx_get_limit(entries), dx_node_limit(dir));
			जाओ fail;
		पूर्ण
	पूर्ण
fail:
	जबतक (frame >= frame_in) अणु
		brअन्यथा(frame->bh);
		frame--;
	पूर्ण

	अगर (ret_err == ERR_PTR(ERR_BAD_DX_सूची))
		ext4_warning_inode(dir,
			"Corrupt directory, running e2fsck is recommended");
	वापस ret_err;
पूर्ण

अटल व्योम dx_release(काष्ठा dx_frame *frames)
अणु
	काष्ठा dx_root_info *info;
	पूर्णांक i;
	अचिन्हित पूर्णांक indirect_levels;

	अगर (frames[0].bh == शून्य)
		वापस;

	info = &((काष्ठा dx_root *)frames[0].bh->b_data)->info;
	/* save local copy, "info" may be मुक्तd after brअन्यथा() */
	indirect_levels = info->indirect_levels;
	क्रम (i = 0; i <= indirect_levels; i++) अणु
		अगर (frames[i].bh == शून्य)
			अवरोध;
		brअन्यथा(frames[i].bh);
		frames[i].bh = शून्य;
	पूर्ण
पूर्ण

/*
 * This function increments the frame poपूर्णांकer to search the next leaf
 * block, and पढ़ोs in the necessary पूर्णांकervening nodes अगर the search
 * should be necessary.  Whether or not the search is necessary is
 * controlled by the hash parameter.  If the hash value is even, then
 * the search is only जारीd अगर the next block starts with that
 * hash value.  This is used अगर we are searching क्रम a specअगरic file.
 *
 * If the hash value is HASH_NB_ALWAYS, then always go to the next block.
 *
 * This function वापसs 1 अगर the caller should जारी to search,
 * or 0 अगर it should not.  If there is an error पढ़ोing one of the
 * index blocks, it will a negative error code.
 *
 * If start_hash is non-null, it will be filled in with the starting
 * hash of the next page.
 */
अटल पूर्णांक ext4_htree_next_block(काष्ठा inode *dir, __u32 hash,
				 काष्ठा dx_frame *frame,
				 काष्ठा dx_frame *frames,
				 __u32 *start_hash)
अणु
	काष्ठा dx_frame *p;
	काष्ठा buffer_head *bh;
	पूर्णांक num_frames = 0;
	__u32 bhash;

	p = frame;
	/*
	 * Find the next leaf page by incrementing the frame poपूर्णांकer.
	 * If we run out of entries in the पूर्णांकerior node, loop around and
	 * increment poपूर्णांकer in the parent node.  When we अवरोध out of
	 * this loop, num_frames indicates the number of पूर्णांकerior
	 * nodes need to be पढ़ो.
	 */
	जबतक (1) अणु
		अगर (++(p->at) < p->entries + dx_get_count(p->entries))
			अवरोध;
		अगर (p == frames)
			वापस 0;
		num_frames++;
		p--;
	पूर्ण

	/*
	 * If the hash is 1, then जारी only अगर the next page has a
	 * continuation hash of any value.  This is used क्रम सूची_पढ़ो
	 * handling.  Otherwise, check to see अगर the hash matches the
	 * desired continuation hash.  If it करोesn't, वापस since
	 * there's no poपूर्णांक to पढ़ो in the successive index pages.
	 */
	bhash = dx_get_hash(p->at);
	अगर (start_hash)
		*start_hash = bhash;
	अगर ((hash & 1) == 0) अणु
		अगर ((bhash & ~1) != hash)
			वापस 0;
	पूर्ण
	/*
	 * If the hash is HASH_NB_ALWAYS, we always go to the next
	 * block so no check is necessary
	 */
	जबतक (num_frames--) अणु
		bh = ext4_पढ़ो_dirblock(dir, dx_get_block(p->at), INDEX);
		अगर (IS_ERR(bh))
			वापस PTR_ERR(bh);
		p++;
		brअन्यथा(p->bh);
		p->bh = bh;
		p->at = p->entries = ((काष्ठा dx_node *) bh->b_data)->entries;
	पूर्ण
	वापस 1;
पूर्ण


/*
 * This function fills a red-black tree with inक्रमmation from a
 * directory block.  It वापसs the number directory entries loaded
 * पूर्णांकo the tree.  If there is an error it is वापसed in err.
 */
अटल पूर्णांक htree_dirblock_to_tree(काष्ठा file *dir_file,
				  काष्ठा inode *dir, ext4_lblk_t block,
				  काष्ठा dx_hash_info *hinfo,
				  __u32 start_hash, __u32 start_minor_hash)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा ext4_dir_entry_2 *de, *top;
	पूर्णांक err = 0, count = 0;
	काष्ठा fscrypt_str fname_crypto_str = FSTR_INIT(शून्य, 0), पंचांगp_str;
	पूर्णांक csum = ext4_has_metadata_csum(dir->i_sb);

	dxtrace(prपूर्णांकk(KERN_INFO "In htree dirblock_to_tree: block %lu\n",
							(अचिन्हित दीर्घ)block));
	bh = ext4_पढ़ो_dirblock(dir, block, सूचीENT_HTREE);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	de = (काष्ठा ext4_dir_entry_2 *) bh->b_data;
	/* csum entries are not larger in the हालfolded encrypted हाल */
	top = (काष्ठा ext4_dir_entry_2 *) ((अक्षर *) de +
					   dir->i_sb->s_blocksize -
					   ext4_dir_rec_len(0,
							   csum ? शून्य : dir));
	/* Check अगर the directory is encrypted */
	अगर (IS_ENCRYPTED(dir)) अणु
		err = fscrypt_prepare_सूची_पढ़ो(dir);
		अगर (err < 0) अणु
			brअन्यथा(bh);
			वापस err;
		पूर्ण
		err = fscrypt_fname_alloc_buffer(EXT4_NAME_LEN,
						 &fname_crypto_str);
		अगर (err < 0) अणु
			brअन्यथा(bh);
			वापस err;
		पूर्ण
	पूर्ण

	क्रम (; de < top; de = ext4_next_entry(de, dir->i_sb->s_blocksize)) अणु
		अगर (ext4_check_dir_entry(dir, शून्य, de, bh,
				bh->b_data, bh->b_size,
				(block<<EXT4_BLOCK_SIZE_BITS(dir->i_sb))
					 + ((अक्षर *)de - bh->b_data))) अणु
			/* silently ignore the rest of the block */
			अवरोध;
		पूर्ण
		अगर (ext4_hash_in_dirent(dir)) अणु
			अगर (de->name_len && de->inode) अणु
				hinfo->hash = EXT4_सूचीENT_HASH(de);
				hinfo->minor_hash = EXT4_सूचीENT_MINOR_HASH(de);
			पूर्ण अन्यथा अणु
				hinfo->hash = 0;
				hinfo->minor_hash = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			ext4fs_dirhash(dir, de->name, de->name_len, hinfo);
		पूर्ण
		अगर ((hinfo->hash < start_hash) ||
		    ((hinfo->hash == start_hash) &&
		     (hinfo->minor_hash < start_minor_hash)))
			जारी;
		अगर (de->inode == 0)
			जारी;
		अगर (!IS_ENCRYPTED(dir)) अणु
			पंचांगp_str.name = de->name;
			पंचांगp_str.len = de->name_len;
			err = ext4_htree_store_dirent(dir_file,
				   hinfo->hash, hinfo->minor_hash, de,
				   &पंचांगp_str);
		पूर्ण अन्यथा अणु
			पूर्णांक save_len = fname_crypto_str.len;
			काष्ठा fscrypt_str de_name = FSTR_INIT(de->name,
								de->name_len);

			/* Directory is encrypted */
			err = fscrypt_fname_disk_to_usr(dir, hinfo->hash,
					hinfo->minor_hash, &de_name,
					&fname_crypto_str);
			अगर (err) अणु
				count = err;
				जाओ errout;
			पूर्ण
			err = ext4_htree_store_dirent(dir_file,
				   hinfo->hash, hinfo->minor_hash, de,
					&fname_crypto_str);
			fname_crypto_str.len = save_len;
		पूर्ण
		अगर (err != 0) अणु
			count = err;
			जाओ errout;
		पूर्ण
		count++;
	पूर्ण
errout:
	brअन्यथा(bh);
	fscrypt_fname_मुक्त_buffer(&fname_crypto_str);
	वापस count;
पूर्ण


/*
 * This function fills a red-black tree with inक्रमmation from a
 * directory.  We start scanning the directory in hash order, starting
 * at start_hash and start_minor_hash.
 *
 * This function वापसs the number of entries inserted पूर्णांकo the tree,
 * or a negative error code.
 */
पूर्णांक ext4_htree_fill_tree(काष्ठा file *dir_file, __u32 start_hash,
			 __u32 start_minor_hash, __u32 *next_hash)
अणु
	काष्ठा dx_hash_info hinfo;
	काष्ठा ext4_dir_entry_2 *de;
	काष्ठा dx_frame frames[EXT4_HTREE_LEVEL], *frame;
	काष्ठा inode *dir;
	ext4_lblk_t block;
	पूर्णांक count = 0;
	पूर्णांक ret, err;
	__u32 hashval;
	काष्ठा fscrypt_str पंचांगp_str;

	dxtrace(prपूर्णांकk(KERN_DEBUG "In htree_fill_tree, start hash: %x:%x\n",
		       start_hash, start_minor_hash));
	dir = file_inode(dir_file);
	अगर (!(ext4_test_inode_flag(dir, EXT4_INODE_INDEX))) अणु
		अगर (ext4_hash_in_dirent(dir))
			hinfo.hash_version = DX_HASH_SIPHASH;
		अन्यथा
			hinfo.hash_version =
					EXT4_SB(dir->i_sb)->s_def_hash_version;
		अगर (hinfo.hash_version <= DX_HASH_TEA)
			hinfo.hash_version +=
				EXT4_SB(dir->i_sb)->s_hash_अचिन्हित;
		hinfo.seed = EXT4_SB(dir->i_sb)->s_hash_seed;
		अगर (ext4_has_अंतरभूत_data(dir)) अणु
			पूर्णांक has_अंतरभूत_data = 1;
			count = ext4_अंतरभूतdir_to_tree(dir_file, dir, 0,
						       &hinfo, start_hash,
						       start_minor_hash,
						       &has_अंतरभूत_data);
			अगर (has_अंतरभूत_data) अणु
				*next_hash = ~0;
				वापस count;
			पूर्ण
		पूर्ण
		count = htree_dirblock_to_tree(dir_file, dir, 0, &hinfo,
					       start_hash, start_minor_hash);
		*next_hash = ~0;
		वापस count;
	पूर्ण
	hinfo.hash = start_hash;
	hinfo.minor_hash = 0;
	frame = dx_probe(शून्य, dir, &hinfo, frames);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	/* Add '.' and '..' from the htree header */
	अगर (!start_hash && !start_minor_hash) अणु
		de = (काष्ठा ext4_dir_entry_2 *) frames[0].bh->b_data;
		पंचांगp_str.name = de->name;
		पंचांगp_str.len = de->name_len;
		err = ext4_htree_store_dirent(dir_file, 0, 0,
					      de, &पंचांगp_str);
		अगर (err != 0)
			जाओ errout;
		count++;
	पूर्ण
	अगर (start_hash < 2 || (start_hash ==2 && start_minor_hash==0)) अणु
		de = (काष्ठा ext4_dir_entry_2 *) frames[0].bh->b_data;
		de = ext4_next_entry(de, dir->i_sb->s_blocksize);
		पंचांगp_str.name = de->name;
		पंचांगp_str.len = de->name_len;
		err = ext4_htree_store_dirent(dir_file, 2, 0,
					      de, &पंचांगp_str);
		अगर (err != 0)
			जाओ errout;
		count++;
	पूर्ण

	जबतक (1) अणु
		अगर (fatal_संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ errout;
		पूर्ण
		cond_resched();
		block = dx_get_block(frame->at);
		ret = htree_dirblock_to_tree(dir_file, dir, block, &hinfo,
					     start_hash, start_minor_hash);
		अगर (ret < 0) अणु
			err = ret;
			जाओ errout;
		पूर्ण
		count += ret;
		hashval = ~0;
		ret = ext4_htree_next_block(dir, HASH_NB_ALWAYS,
					    frame, frames, &hashval);
		*next_hash = hashval;
		अगर (ret < 0) अणु
			err = ret;
			जाओ errout;
		पूर्ण
		/*
		 * Stop अगर:  (a) there are no more entries, or
		 * (b) we have inserted at least one entry and the
		 * next hash value is not a continuation
		 */
		अगर ((ret == 0) ||
		    (count && ((hashval & 1) == 0)))
			अवरोध;
	पूर्ण
	dx_release(frames);
	dxtrace(prपूर्णांकk(KERN_DEBUG "Fill tree: returned %d entries, "
		       "next hash: %x\n", count, *next_hash));
	वापस count;
errout:
	dx_release(frames);
	वापस (err);
पूर्ण

अटल अंतरभूत पूर्णांक search_dirblock(काष्ठा buffer_head *bh,
				  काष्ठा inode *dir,
				  काष्ठा ext4_filename *fname,
				  अचिन्हित पूर्णांक offset,
				  काष्ठा ext4_dir_entry_2 **res_dir)
अणु
	वापस ext4_search_dir(bh, bh->b_data, dir->i_sb->s_blocksize, dir,
			       fname, offset, res_dir);
पूर्ण

/*
 * Directory block splitting, compacting
 */

/*
 * Create map of hash values, offsets, and sizes, stored at end of block.
 * Returns number of entries mapped.
 */
अटल पूर्णांक dx_make_map(काष्ठा inode *dir, काष्ठा ext4_dir_entry_2 *de,
		       अचिन्हित blocksize, काष्ठा dx_hash_info *hinfo,
		       काष्ठा dx_map_entry *map_tail)
अणु
	पूर्णांक count = 0;
	अक्षर *base = (अक्षर *) de;
	काष्ठा dx_hash_info h = *hinfo;

	जबतक ((अक्षर *) de < base + blocksize) अणु
		अगर (de->name_len && de->inode) अणु
			अगर (ext4_hash_in_dirent(dir))
				h.hash = EXT4_सूचीENT_HASH(de);
			अन्यथा
				ext4fs_dirhash(dir, de->name, de->name_len, &h);
			map_tail--;
			map_tail->hash = h.hash;
			map_tail->offs = ((अक्षर *) de - base)>>2;
			map_tail->size = le16_to_cpu(de->rec_len);
			count++;
			cond_resched();
		पूर्ण
		/* XXX: करो we need to check rec_len == 0 हाल? -Chris */
		de = ext4_next_entry(de, blocksize);
	पूर्ण
	वापस count;
पूर्ण

/* Sort map by hash value */
अटल व्योम dx_sort_map (काष्ठा dx_map_entry *map, अचिन्हित count)
अणु
	काष्ठा dx_map_entry *p, *q, *top = map + count - 1;
	पूर्णांक more;
	/* Combsort until bubble sort करोesn't suck */
	जबतक (count > 2) अणु
		count = count*10/13;
		अगर (count - 9 < 2) /* 9, 10 -> 11 */
			count = 11;
		क्रम (p = top, q = p - count; q >= map; p--, q--)
			अगर (p->hash < q->hash)
				swap(*p, *q);
	पूर्ण
	/* Garden variety bubble sort */
	करो अणु
		more = 0;
		q = top;
		जबतक (q-- > map) अणु
			अगर (q[1].hash >= q[0].hash)
				जारी;
			swap(*(q+1), *q);
			more = 1;
		पूर्ण
	पूर्ण जबतक(more);
पूर्ण

अटल व्योम dx_insert_block(काष्ठा dx_frame *frame, u32 hash, ext4_lblk_t block)
अणु
	काष्ठा dx_entry *entries = frame->entries;
	काष्ठा dx_entry *old = frame->at, *new = old + 1;
	पूर्णांक count = dx_get_count(entries);

	ASSERT(count < dx_get_limit(entries));
	ASSERT(old < entries + count);
	स_हटाओ(new + 1, new, (अक्षर *)(entries + count) - (अक्षर *)(new));
	dx_set_hash(new, hash);
	dx_set_block(new, block);
	dx_set_count(entries, count + 1);
पूर्ण

#अगर_घोषित CONFIG_UNICODE
/*
 * Test whether a हाल-insensitive directory entry matches the filename
 * being searched क्रम.  If quick is set, assume the name being looked up
 * is alपढ़ोy in the हालfolded क्रमm.
 *
 * Returns: 0 अगर the directory entry matches, more than 0 अगर it
 * करोesn't match or less than zero on error.
 */
अटल पूर्णांक ext4_ci_compare(स्थिर काष्ठा inode *parent, स्थिर काष्ठा qstr *name,
			   u8 *de_name, माप_प्रकार de_name_len, bool quick)
अणु
	स्थिर काष्ठा super_block *sb = parent->i_sb;
	स्थिर काष्ठा unicode_map *um = sb->s_encoding;
	काष्ठा fscrypt_str decrypted_name = FSTR_INIT(शून्य, de_name_len);
	काष्ठा qstr entry = QSTR_INIT(de_name, de_name_len);
	पूर्णांक ret;

	अगर (IS_ENCRYPTED(parent)) अणु
		स्थिर काष्ठा fscrypt_str encrypted_name =
				FSTR_INIT(de_name, de_name_len);

		decrypted_name.name = kदो_स्मृति(de_name_len, GFP_KERNEL);
		अगर (!decrypted_name.name)
			वापस -ENOMEM;
		ret = fscrypt_fname_disk_to_usr(parent, 0, 0, &encrypted_name,
						&decrypted_name);
		अगर (ret < 0)
			जाओ out;
		entry.name = decrypted_name.name;
		entry.len = decrypted_name.len;
	पूर्ण

	अगर (quick)
		ret = utf8_strnहालcmp_folded(um, name, &entry);
	अन्यथा
		ret = utf8_strnहालcmp(um, name, &entry);
	अगर (ret < 0) अणु
		/* Handle invalid अक्षरacter sequence as either an error
		 * or as an opaque byte sequence.
		 */
		अगर (sb_has_strict_encoding(sb))
			ret = -EINVAL;
		अन्यथा अगर (name->len != entry.len)
			ret = 1;
		अन्यथा
			ret = !!स_भेद(name->name, entry.name, entry.len);
	पूर्ण
out:
	kमुक्त(decrypted_name.name);
	वापस ret;
पूर्ण

पूर्णांक ext4_fname_setup_ci_filename(काष्ठा inode *dir, स्थिर काष्ठा qstr *iname,
				  काष्ठा ext4_filename *name)
अणु
	काष्ठा fscrypt_str *cf_name = &name->cf_name;
	काष्ठा dx_hash_info *hinfo = &name->hinfo;
	पूर्णांक len;

	अगर (!IS_CASEFOLDED(dir) || !dir->i_sb->s_encoding ||
	    (IS_ENCRYPTED(dir) && !fscrypt_has_encryption_key(dir))) अणु
		cf_name->name = शून्य;
		वापस 0;
	पूर्ण

	cf_name->name = kदो_स्मृति(EXT4_NAME_LEN, GFP_NOFS);
	अगर (!cf_name->name)
		वापस -ENOMEM;

	len = utf8_हालfold(dir->i_sb->s_encoding,
			    iname, cf_name->name,
			    EXT4_NAME_LEN);
	अगर (len <= 0) अणु
		kमुक्त(cf_name->name);
		cf_name->name = शून्य;
	पूर्ण
	cf_name->len = (अचिन्हित) len;
	अगर (!IS_ENCRYPTED(dir))
		वापस 0;

	hinfo->hash_version = DX_HASH_SIPHASH;
	hinfo->seed = शून्य;
	अगर (cf_name->name)
		ext4fs_dirhash(dir, cf_name->name, cf_name->len, hinfo);
	अन्यथा
		ext4fs_dirhash(dir, iname->name, iname->len, hinfo);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Test whether a directory entry matches the filename being searched क्रम.
 *
 * Return: %true अगर the directory entry matches, otherwise %false.
 */
अटल bool ext4_match(काष्ठा inode *parent,
			      स्थिर काष्ठा ext4_filename *fname,
			      काष्ठा ext4_dir_entry_2 *de)
अणु
	काष्ठा fscrypt_name f;

	अगर (!de->inode)
		वापस false;

	f.usr_fname = fname->usr_fname;
	f.disk_name = fname->disk_name;
#अगर_घोषित CONFIG_FS_ENCRYPTION
	f.crypto_buf = fname->crypto_buf;
#पूर्ण_अगर

#अगर_घोषित CONFIG_UNICODE
	अगर (parent->i_sb->s_encoding && IS_CASEFOLDED(parent) &&
	    (!IS_ENCRYPTED(parent) || fscrypt_has_encryption_key(parent))) अणु
		अगर (fname->cf_name.name) अणु
			काष्ठा qstr cf = अणु.name = fname->cf_name.name,
					  .len = fname->cf_name.lenपूर्ण;
			अगर (IS_ENCRYPTED(parent)) अणु
				अगर (fname->hinfo.hash != EXT4_सूचीENT_HASH(de) ||
					fname->hinfo.minor_hash !=
						EXT4_सूचीENT_MINOR_HASH(de)) अणु

					वापस 0;
				पूर्ण
			पूर्ण
			वापस !ext4_ci_compare(parent, &cf, de->name,
							de->name_len, true);
		पूर्ण
		वापस !ext4_ci_compare(parent, fname->usr_fname, de->name,
						de->name_len, false);
	पूर्ण
#पूर्ण_अगर

	वापस fscrypt_match_name(&f, de->name, de->name_len);
पूर्ण

/*
 * Returns 0 अगर not found, -1 on failure, and 1 on success
 */
पूर्णांक ext4_search_dir(काष्ठा buffer_head *bh, अक्षर *search_buf, पूर्णांक buf_size,
		    काष्ठा inode *dir, काष्ठा ext4_filename *fname,
		    अचिन्हित पूर्णांक offset, काष्ठा ext4_dir_entry_2 **res_dir)
अणु
	काष्ठा ext4_dir_entry_2 * de;
	अक्षर * dlimit;
	पूर्णांक de_len;

	de = (काष्ठा ext4_dir_entry_2 *)search_buf;
	dlimit = search_buf + buf_size;
	जबतक ((अक्षर *) de < dlimit) अणु
		/* this code is executed quadratically often */
		/* करो minimal checking `by hand' */
		अगर ((अक्षर *) de + de->name_len <= dlimit &&
		    ext4_match(dir, fname, de)) अणु
			/* found a match - just to be sure, करो
			 * a full check */
			अगर (ext4_check_dir_entry(dir, शून्य, de, bh, search_buf,
						 buf_size, offset))
				वापस -1;
			*res_dir = de;
			वापस 1;
		पूर्ण
		/* prevent looping on a bad block */
		de_len = ext4_rec_len_from_disk(de->rec_len,
						dir->i_sb->s_blocksize);
		अगर (de_len <= 0)
			वापस -1;
		offset += de_len;
		de = (काष्ठा ext4_dir_entry_2 *) ((अक्षर *) de + de_len);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक is_dx_पूर्णांकernal_node(काष्ठा inode *dir, ext4_lblk_t block,
			       काष्ठा ext4_dir_entry *de)
अणु
	काष्ठा super_block *sb = dir->i_sb;

	अगर (!is_dx(dir))
		वापस 0;
	अगर (block == 0)
		वापस 1;
	अगर (de->inode == 0 &&
	    ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize) ==
			sb->s_blocksize)
		वापस 1;
	वापस 0;
पूर्ण

/*
 *	__ext4_find_entry()
 *
 * finds an entry in the specअगरied directory with the wanted name. It
 * वापसs the cache buffer in which the entry was found, and the entry
 * itself (as a parameter - res_dir). It करोes NOT पढ़ो the inode of the
 * entry - you'll have to करो that yourself अगर you want to.
 *
 * The वापसed buffer_head has ->b_count elevated.  The caller is expected
 * to brअन्यथा() it when appropriate.
 */
अटल काष्ठा buffer_head *__ext4_find_entry(काष्ठा inode *dir,
					     काष्ठा ext4_filename *fname,
					     काष्ठा ext4_dir_entry_2 **res_dir,
					     पूर्णांक *अंतरभूतd)
अणु
	काष्ठा super_block *sb;
	काष्ठा buffer_head *bh_use[NAMEI_RA_SIZE];
	काष्ठा buffer_head *bh, *ret = शून्य;
	ext4_lblk_t start, block;
	स्थिर u8 *name = fname->usr_fname->name;
	माप_प्रकार ra_max = 0;	/* Number of bh's in the पढ़ोahead
				   buffer, bh_use[] */
	माप_प्रकार ra_ptr = 0;	/* Current index पूर्णांकo पढ़ोahead
				   buffer */
	ext4_lblk_t  nblocks;
	पूर्णांक i, namelen, retval;

	*res_dir = शून्य;
	sb = dir->i_sb;
	namelen = fname->usr_fname->len;
	अगर (namelen > EXT4_NAME_LEN)
		वापस शून्य;

	अगर (ext4_has_अंतरभूत_data(dir)) अणु
		पूर्णांक has_अंतरभूत_data = 1;
		ret = ext4_find_अंतरभूत_entry(dir, fname, res_dir,
					     &has_अंतरभूत_data);
		अगर (has_अंतरभूत_data) अणु
			अगर (अंतरभूतd)
				*अंतरभूतd = 1;
			जाओ cleanup_and_निकास;
		पूर्ण
	पूर्ण

	अगर ((namelen <= 2) && (name[0] == '.') &&
	    (name[1] == '.' || name[1] == '\0')) अणु
		/*
		 * "." or ".." will only be in the first block
		 * NFS may look up ".."; "." should be handled by the VFS
		 */
		block = start = 0;
		nblocks = 1;
		जाओ restart;
	पूर्ण
	अगर (is_dx(dir)) अणु
		ret = ext4_dx_find_entry(dir, fname, res_dir);
		/*
		 * On success, or अगर the error was file not found,
		 * वापस.  Otherwise, fall back to करोing a search the
		 * old fashioned way.
		 */
		अगर (!IS_ERR(ret) || PTR_ERR(ret) != ERR_BAD_DX_सूची)
			जाओ cleanup_and_निकास;
		dxtrace(prपूर्णांकk(KERN_DEBUG "ext4_find_entry: dx failed, "
			       "falling back\n"));
		ret = शून्य;
	पूर्ण
	nblocks = dir->i_size >> EXT4_BLOCK_SIZE_BITS(sb);
	अगर (!nblocks) अणु
		ret = शून्य;
		जाओ cleanup_and_निकास;
	पूर्ण
	start = EXT4_I(dir)->i_dir_start_lookup;
	अगर (start >= nblocks)
		start = 0;
	block = start;
restart:
	करो अणु
		/*
		 * We deal with the पढ़ो-ahead logic here.
		 */
		cond_resched();
		अगर (ra_ptr >= ra_max) अणु
			/* Refill the पढ़ोahead buffer */
			ra_ptr = 0;
			अगर (block < start)
				ra_max = start - block;
			अन्यथा
				ra_max = nblocks - block;
			ra_max = min(ra_max, ARRAY_SIZE(bh_use));
			retval = ext4_bपढ़ो_batch(dir, block, ra_max,
						  false /* रुको */, bh_use);
			अगर (retval) अणु
				ret = ERR_PTR(retval);
				ra_max = 0;
				जाओ cleanup_and_निकास;
			पूर्ण
		पूर्ण
		अगर ((bh = bh_use[ra_ptr++]) == शून्य)
			जाओ next;
		रुको_on_buffer(bh);
		अगर (!buffer_uptodate(bh)) अणु
			EXT4_ERROR_INODE_ERR(dir, EIO,
					     "reading directory lblock %lu",
					     (अचिन्हित दीर्घ) block);
			brअन्यथा(bh);
			ret = ERR_PTR(-EIO);
			जाओ cleanup_and_निकास;
		पूर्ण
		अगर (!buffer_verअगरied(bh) &&
		    !is_dx_पूर्णांकernal_node(dir, block,
					 (काष्ठा ext4_dir_entry *)bh->b_data) &&
		    !ext4_dirblock_csum_verअगरy(dir, bh)) अणु
			EXT4_ERROR_INODE_ERR(dir, EFSBADCRC,
					     "checksumming directory "
					     "block %lu", (अचिन्हित दीर्घ)block);
			brअन्यथा(bh);
			ret = ERR_PTR(-EFSBADCRC);
			जाओ cleanup_and_निकास;
		पूर्ण
		set_buffer_verअगरied(bh);
		i = search_dirblock(bh, dir, fname,
			    block << EXT4_BLOCK_SIZE_BITS(sb), res_dir);
		अगर (i == 1) अणु
			EXT4_I(dir)->i_dir_start_lookup = block;
			ret = bh;
			जाओ cleanup_and_निकास;
		पूर्ण अन्यथा अणु
			brअन्यथा(bh);
			अगर (i < 0)
				जाओ cleanup_and_निकास;
		पूर्ण
	next:
		अगर (++block >= nblocks)
			block = 0;
	पूर्ण जबतक (block != start);

	/*
	 * If the directory has grown जबतक we were searching, then
	 * search the last part of the directory beक्रमe giving up.
	 */
	block = nblocks;
	nblocks = dir->i_size >> EXT4_BLOCK_SIZE_BITS(sb);
	अगर (block < nblocks) अणु
		start = 0;
		जाओ restart;
	पूर्ण

cleanup_and_निकास:
	/* Clean up the पढ़ो-ahead blocks */
	क्रम (; ra_ptr < ra_max; ra_ptr++)
		brअन्यथा(bh_use[ra_ptr]);
	वापस ret;
पूर्ण

अटल काष्ठा buffer_head *ext4_find_entry(काष्ठा inode *dir,
					   स्थिर काष्ठा qstr *d_name,
					   काष्ठा ext4_dir_entry_2 **res_dir,
					   पूर्णांक *अंतरभूतd)
अणु
	पूर्णांक err;
	काष्ठा ext4_filename fname;
	काष्ठा buffer_head *bh;

	err = ext4_fname_setup_filename(dir, d_name, 1, &fname);
	अगर (err == -ENOENT)
		वापस शून्य;
	अगर (err)
		वापस ERR_PTR(err);

	bh = __ext4_find_entry(dir, &fname, res_dir, अंतरभूतd);

	ext4_fname_मुक्त_filename(&fname);
	वापस bh;
पूर्ण

अटल काष्ठा buffer_head *ext4_lookup_entry(काष्ठा inode *dir,
					     काष्ठा dentry *dentry,
					     काष्ठा ext4_dir_entry_2 **res_dir)
अणु
	पूर्णांक err;
	काष्ठा ext4_filename fname;
	काष्ठा buffer_head *bh;

	err = ext4_fname_prepare_lookup(dir, dentry, &fname);
	generic_set_encrypted_ci_d_ops(dentry);
	अगर (err == -ENOENT)
		वापस शून्य;
	अगर (err)
		वापस ERR_PTR(err);

	bh = __ext4_find_entry(dir, &fname, res_dir, शून्य);

	ext4_fname_मुक्त_filename(&fname);
	वापस bh;
पूर्ण

अटल काष्ठा buffer_head * ext4_dx_find_entry(काष्ठा inode *dir,
			काष्ठा ext4_filename *fname,
			काष्ठा ext4_dir_entry_2 **res_dir)
अणु
	काष्ठा super_block * sb = dir->i_sb;
	काष्ठा dx_frame frames[EXT4_HTREE_LEVEL], *frame;
	काष्ठा buffer_head *bh;
	ext4_lblk_t block;
	पूर्णांक retval;

#अगर_घोषित CONFIG_FS_ENCRYPTION
	*res_dir = शून्य;
#पूर्ण_अगर
	frame = dx_probe(fname, dir, शून्य, frames);
	अगर (IS_ERR(frame))
		वापस (काष्ठा buffer_head *) frame;
	करो अणु
		block = dx_get_block(frame->at);
		bh = ext4_पढ़ो_dirblock(dir, block, सूचीENT_HTREE);
		अगर (IS_ERR(bh))
			जाओ errout;

		retval = search_dirblock(bh, dir, fname,
					 block << EXT4_BLOCK_SIZE_BITS(sb),
					 res_dir);
		अगर (retval == 1)
			जाओ success;
		brअन्यथा(bh);
		अगर (retval == -1) अणु
			bh = ERR_PTR(ERR_BAD_DX_सूची);
			जाओ errout;
		पूर्ण

		/* Check to see अगर we should जारी to search */
		retval = ext4_htree_next_block(dir, fname->hinfo.hash, frame,
					       frames, शून्य);
		अगर (retval < 0) अणु
			ext4_warning_inode(dir,
				"error %d reading directory index block",
				retval);
			bh = ERR_PTR(retval);
			जाओ errout;
		पूर्ण
	पूर्ण जबतक (retval == 1);

	bh = शून्य;
errout:
	dxtrace(prपूर्णांकk(KERN_DEBUG "%s not found\n", fname->usr_fname->name));
success:
	dx_release(frames);
	वापस bh;
पूर्ण

अटल काष्ठा dentry *ext4_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	काष्ठा ext4_dir_entry_2 *de;
	काष्ठा buffer_head *bh;

	अगर (dentry->d_name.len > EXT4_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	bh = ext4_lookup_entry(dir, dentry, &de);
	अगर (IS_ERR(bh))
		वापस ERR_CAST(bh);
	inode = शून्य;
	अगर (bh) अणु
		__u32 ino = le32_to_cpu(de->inode);
		brअन्यथा(bh);
		अगर (!ext4_valid_inum(dir->i_sb, ino)) अणु
			EXT4_ERROR_INODE(dir, "bad inode number: %u", ino);
			वापस ERR_PTR(-EFSCORRUPTED);
		पूर्ण
		अगर (unlikely(ino == dir->i_ino)) अणु
			EXT4_ERROR_INODE(dir, "'%pd' linked to parent dir",
					 dentry);
			वापस ERR_PTR(-EFSCORRUPTED);
		पूर्ण
		inode = ext4_iget(dir->i_sb, ino, EXT4_IGET_NORMAL);
		अगर (inode == ERR_PTR(-ESTALE)) अणु
			EXT4_ERROR_INODE(dir,
					 "deleted inode referenced: %u",
					 ino);
			वापस ERR_PTR(-EFSCORRUPTED);
		पूर्ण
		अगर (!IS_ERR(inode) && IS_ENCRYPTED(dir) &&
		    (S_ISसूची(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
		    !fscrypt_has_permitted_context(dir, inode)) अणु
			ext4_warning(inode->i_sb,
				     "Inconsistent encryption contexts: %lu/%lu",
				     dir->i_ino, inode->i_ino);
			iput(inode);
			वापस ERR_PTR(-EPERM);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_UNICODE
	अगर (!inode && IS_CASEFOLDED(dir)) अणु
		/* Eventually we want to call d_add_ci(dentry, शून्य)
		 * क्रम negative dentries in the encoding हाल as
		 * well.  For now, prevent the negative dentry
		 * from being cached.
		 */
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर
	वापस d_splice_alias(inode, dentry);
पूर्ण


काष्ठा dentry *ext4_get_parent(काष्ठा dentry *child)
अणु
	__u32 ino;
	काष्ठा ext4_dir_entry_2 * de;
	काष्ठा buffer_head *bh;

	bh = ext4_find_entry(d_inode(child), &करोtकरोt_name, &de, शून्य);
	अगर (IS_ERR(bh))
		वापस ERR_CAST(bh);
	अगर (!bh)
		वापस ERR_PTR(-ENOENT);
	ino = le32_to_cpu(de->inode);
	brअन्यथा(bh);

	अगर (!ext4_valid_inum(child->d_sb, ino)) अणु
		EXT4_ERROR_INODE(d_inode(child),
				 "bad parent inode number: %u", ino);
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण

	वापस d_obtain_alias(ext4_iget(child->d_sb, ino, EXT4_IGET_NORMAL));
पूर्ण

/*
 * Move count entries from end of map between two memory locations.
 * Returns poपूर्णांकer to last entry moved.
 */
अटल काष्ठा ext4_dir_entry_2 *
dx_move_dirents(काष्ठा inode *dir, अक्षर *from, अक्षर *to,
		काष्ठा dx_map_entry *map, पूर्णांक count,
		अचिन्हित blocksize)
अणु
	अचिन्हित rec_len = 0;

	जबतक (count--) अणु
		काष्ठा ext4_dir_entry_2 *de = (काष्ठा ext4_dir_entry_2 *)
						(from + (map->offs<<2));
		rec_len = ext4_dir_rec_len(de->name_len, dir);

		स_नकल (to, de, rec_len);
		((काष्ठा ext4_dir_entry_2 *) to)->rec_len =
				ext4_rec_len_to_disk(rec_len, blocksize);

		/* wipe dir_entry excluding the rec_len field */
		de->inode = 0;
		स_रखो(&de->name_len, 0, ext4_rec_len_from_disk(de->rec_len,
								blocksize) -
					 दुरत्व(काष्ठा ext4_dir_entry_2,
								name_len));

		map++;
		to += rec_len;
	पूर्ण
	वापस (काष्ठा ext4_dir_entry_2 *) (to - rec_len);
पूर्ण

/*
 * Compact each dir entry in the range to the minimal rec_len.
 * Returns poपूर्णांकer to last entry in range.
 */
अटल काष्ठा ext4_dir_entry_2 *dx_pack_dirents(काष्ठा inode *dir, अक्षर *base,
							अचिन्हित पूर्णांक blocksize)
अणु
	काष्ठा ext4_dir_entry_2 *next, *to, *prev, *de = (काष्ठा ext4_dir_entry_2 *) base;
	अचिन्हित rec_len = 0;

	prev = to = de;
	जबतक ((अक्षर*)de < base + blocksize) अणु
		next = ext4_next_entry(de, blocksize);
		अगर (de->inode && de->name_len) अणु
			rec_len = ext4_dir_rec_len(de->name_len, dir);
			अगर (de > to)
				स_हटाओ(to, de, rec_len);
			to->rec_len = ext4_rec_len_to_disk(rec_len, blocksize);
			prev = to;
			to = (काष्ठा ext4_dir_entry_2 *) (((अक्षर *) to) + rec_len);
		पूर्ण
		de = next;
	पूर्ण
	वापस prev;
पूर्ण

/*
 * Split a full leaf block to make room क्रम a new dir entry.
 * Allocate a new block, and move entries so that they are approx. equally full.
 * Returns poपूर्णांकer to de in block पूर्णांकo which the new entry will be inserted.
 */
अटल काष्ठा ext4_dir_entry_2 *करो_split(handle_t *handle, काष्ठा inode *dir,
			काष्ठा buffer_head **bh,काष्ठा dx_frame *frame,
			काष्ठा dx_hash_info *hinfo)
अणु
	अचिन्हित blocksize = dir->i_sb->s_blocksize;
	अचिन्हित count, जारीd;
	काष्ठा buffer_head *bh2;
	ext4_lblk_t newblock;
	u32 hash2;
	काष्ठा dx_map_entry *map;
	अक्षर *data1 = (*bh)->b_data, *data2;
	अचिन्हित split, move, size;
	काष्ठा ext4_dir_entry_2 *de = शून्य, *de2;
	पूर्णांक	csum_size = 0;
	पूर्णांक	err = 0, i;

	अगर (ext4_has_metadata_csum(dir->i_sb))
		csum_size = माप(काष्ठा ext4_dir_entry_tail);

	bh2 = ext4_append(handle, dir, &newblock);
	अगर (IS_ERR(bh2)) अणु
		brअन्यथा(*bh);
		*bh = शून्य;
		वापस (काष्ठा ext4_dir_entry_2 *) bh2;
	पूर्ण

	BUFFER_TRACE(*bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, *bh);
	अगर (err)
		जाओ journal_error;

	BUFFER_TRACE(frame->bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, frame->bh);
	अगर (err)
		जाओ journal_error;

	data2 = bh2->b_data;

	/* create map in the end of data2 block */
	map = (काष्ठा dx_map_entry *) (data2 + blocksize);
	count = dx_make_map(dir, (काष्ठा ext4_dir_entry_2 *) data1,
			     blocksize, hinfo, map);
	map -= count;
	dx_sort_map(map, count);
	/* Ensure that neither split block is over half full */
	size = 0;
	move = 0;
	क्रम (i = count-1; i >= 0; i--) अणु
		/* is more than half of this entry in 2nd half of the block? */
		अगर (size + map[i].size/2 > blocksize/2)
			अवरोध;
		size += map[i].size;
		move++;
	पूर्ण
	/*
	 * map index at which we will split
	 *
	 * If the sum of active entries didn't exceed half the block size, just
	 * split it in half by count; each resulting block will have at least
	 * half the space मुक्त.
	 */
	अगर (i > 0)
		split = count - move;
	अन्यथा
		split = count/2;

	hash2 = map[split].hash;
	जारीd = hash2 == map[split - 1].hash;
	dxtrace(prपूर्णांकk(KERN_INFO "Split block %lu at %x, %i/%i\n",
			(अचिन्हित दीर्घ)dx_get_block(frame->at),
					hash2, split, count-split));

	/* Fancy dance to stay within two buffers */
	de2 = dx_move_dirents(dir, data1, data2, map + split, count - split,
			      blocksize);
	de = dx_pack_dirents(dir, data1, blocksize);
	de->rec_len = ext4_rec_len_to_disk(data1 + (blocksize - csum_size) -
					   (अक्षर *) de,
					   blocksize);
	de2->rec_len = ext4_rec_len_to_disk(data2 + (blocksize - csum_size) -
					    (अक्षर *) de2,
					    blocksize);
	अगर (csum_size) अणु
		ext4_initialize_dirent_tail(*bh, blocksize);
		ext4_initialize_dirent_tail(bh2, blocksize);
	पूर्ण

	dxtrace(dx_show_leaf(dir, hinfo, (काष्ठा ext4_dir_entry_2 *) data1,
			blocksize, 1));
	dxtrace(dx_show_leaf(dir, hinfo, (काष्ठा ext4_dir_entry_2 *) data2,
			blocksize, 1));

	/* Which block माला_लो the new entry? */
	अगर (hinfo->hash >= hash2) अणु
		swap(*bh, bh2);
		de = de2;
	पूर्ण
	dx_insert_block(frame, hash2 + जारीd, newblock);
	err = ext4_handle_dirty_dirblock(handle, dir, bh2);
	अगर (err)
		जाओ journal_error;
	err = ext4_handle_dirty_dx_node(handle, dir, frame->bh);
	अगर (err)
		जाओ journal_error;
	brअन्यथा(bh2);
	dxtrace(dx_show_index("frame", frame->entries));
	वापस de;

journal_error:
	brअन्यथा(*bh);
	brअन्यथा(bh2);
	*bh = शून्य;
	ext4_std_error(dir->i_sb, err);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक ext4_find_dest_de(काष्ठा inode *dir, काष्ठा inode *inode,
		      काष्ठा buffer_head *bh,
		      व्योम *buf, पूर्णांक buf_size,
		      काष्ठा ext4_filename *fname,
		      काष्ठा ext4_dir_entry_2 **dest_de)
अणु
	काष्ठा ext4_dir_entry_2 *de;
	अचिन्हित लघु reclen = ext4_dir_rec_len(fname_len(fname), dir);
	पूर्णांक nlen, rlen;
	अचिन्हित पूर्णांक offset = 0;
	अक्षर *top;

	de = (काष्ठा ext4_dir_entry_2 *)buf;
	top = buf + buf_size - reclen;
	जबतक ((अक्षर *) de <= top) अणु
		अगर (ext4_check_dir_entry(dir, शून्य, de, bh,
					 buf, buf_size, offset))
			वापस -EFSCORRUPTED;
		अगर (ext4_match(dir, fname, de))
			वापस -EEXIST;
		nlen = ext4_dir_rec_len(de->name_len, dir);
		rlen = ext4_rec_len_from_disk(de->rec_len, buf_size);
		अगर ((de->inode ? rlen - nlen : rlen) >= reclen)
			अवरोध;
		de = (काष्ठा ext4_dir_entry_2 *)((अक्षर *)de + rlen);
		offset += rlen;
	पूर्ण
	अगर ((अक्षर *) de > top)
		वापस -ENOSPC;

	*dest_de = de;
	वापस 0;
पूर्ण

व्योम ext4_insert_dentry(काष्ठा inode *dir,
			काष्ठा inode *inode,
			काष्ठा ext4_dir_entry_2 *de,
			पूर्णांक buf_size,
			काष्ठा ext4_filename *fname)
अणु

	पूर्णांक nlen, rlen;

	nlen = ext4_dir_rec_len(de->name_len, dir);
	rlen = ext4_rec_len_from_disk(de->rec_len, buf_size);
	अगर (de->inode) अणु
		काष्ठा ext4_dir_entry_2 *de1 =
			(काष्ठा ext4_dir_entry_2 *)((अक्षर *)de + nlen);
		de1->rec_len = ext4_rec_len_to_disk(rlen - nlen, buf_size);
		de->rec_len = ext4_rec_len_to_disk(nlen, buf_size);
		de = de1;
	पूर्ण
	de->file_type = EXT4_FT_UNKNOWN;
	de->inode = cpu_to_le32(inode->i_ino);
	ext4_set_de_type(inode->i_sb, de, inode->i_mode);
	de->name_len = fname_len(fname);
	स_नकल(de->name, fname_name(fname), fname_len(fname));
	अगर (ext4_hash_in_dirent(dir)) अणु
		काष्ठा dx_hash_info *hinfo = &fname->hinfo;

		EXT4_सूचीENT_HASHES(de)->hash = cpu_to_le32(hinfo->hash);
		EXT4_सूचीENT_HASHES(de)->minor_hash =
						cpu_to_le32(hinfo->minor_hash);
	पूर्ण
पूर्ण

/*
 * Add a new entry पूर्णांकo a directory (leaf) block.  If de is non-शून्य,
 * it poपूर्णांकs to a directory entry which is guaranteed to be large
 * enough क्रम new directory entry.  If de is शून्य, then
 * add_dirent_to_buf will attempt search the directory block क्रम
 * space.  It will वापस -ENOSPC अगर no space is available, and -EIO
 * and -EEXIST अगर directory entry alपढ़ोy exists.
 */
अटल पूर्णांक add_dirent_to_buf(handle_t *handle, काष्ठा ext4_filename *fname,
			     काष्ठा inode *dir,
			     काष्ठा inode *inode, काष्ठा ext4_dir_entry_2 *de,
			     काष्ठा buffer_head *bh)
अणु
	अचिन्हित पूर्णांक	blocksize = dir->i_sb->s_blocksize;
	पूर्णांक		csum_size = 0;
	पूर्णांक		err, err2;

	अगर (ext4_has_metadata_csum(inode->i_sb))
		csum_size = माप(काष्ठा ext4_dir_entry_tail);

	अगर (!de) अणु
		err = ext4_find_dest_de(dir, inode, bh, bh->b_data,
					blocksize - csum_size, fname, &de);
		अगर (err)
			वापस err;
	पूर्ण
	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (err) अणु
		ext4_std_error(dir->i_sb, err);
		वापस err;
	पूर्ण

	/* By now the buffer is marked क्रम journaling */
	ext4_insert_dentry(dir, inode, de, blocksize, fname);

	/*
	 * XXX shouldn't update any बार until successful
	 * completion of syscall, but too many callers depend
	 * on this.
	 *
	 * XXX similarly, too many callers depend on
	 * ext4_new_inode() setting the बार, but error
	 * recovery deletes the inode, so the worst that can
	 * happen is that the बार are slightly out of date
	 * and/or dअगरferent from the directory change समय.
	 */
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	ext4_update_dx_flag(dir);
	inode_inc_iversion(dir);
	err2 = ext4_mark_inode_dirty(handle, dir);
	BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_dirblock(handle, dir, bh);
	अगर (err)
		ext4_std_error(dir->i_sb, err);
	वापस err ? err : err2;
पूर्ण

/*
 * This converts a one block unindexed directory to a 3 block indexed
 * directory, and adds the dentry to the indexed directory.
 */
अटल पूर्णांक make_indexed_dir(handle_t *handle, काष्ठा ext4_filename *fname,
			    काष्ठा inode *dir,
			    काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	काष्ठा buffer_head *bh2;
	काष्ठा dx_root	*root;
	काष्ठा dx_frame	frames[EXT4_HTREE_LEVEL], *frame;
	काष्ठा dx_entry *entries;
	काष्ठा ext4_dir_entry_2	*de, *de2;
	अक्षर		*data2, *top;
	अचिन्हित	len;
	पूर्णांक		retval;
	अचिन्हित	blocksize;
	ext4_lblk_t  block;
	काष्ठा fake_dirent *fde;
	पूर्णांक csum_size = 0;

	अगर (ext4_has_metadata_csum(inode->i_sb))
		csum_size = माप(काष्ठा ext4_dir_entry_tail);

	blocksize =  dir->i_sb->s_blocksize;
	dxtrace(prपूर्णांकk(KERN_DEBUG "Creating index: inode %lu\n", dir->i_ino));
	BUFFER_TRACE(bh, "get_write_access");
	retval = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (retval) अणु
		ext4_std_error(dir->i_sb, retval);
		brअन्यथा(bh);
		वापस retval;
	पूर्ण
	root = (काष्ठा dx_root *) bh->b_data;

	/* The 0th block becomes the root, move the dirents out */
	fde = &root->करोtकरोt;
	de = (काष्ठा ext4_dir_entry_2 *)((अक्षर *)fde +
		ext4_rec_len_from_disk(fde->rec_len, blocksize));
	अगर ((अक्षर *) de >= (((अक्षर *) root) + blocksize)) अणु
		EXT4_ERROR_INODE(dir, "invalid rec_len for '..'");
		brअन्यथा(bh);
		वापस -EFSCORRUPTED;
	पूर्ण
	len = ((अक्षर *) root) + (blocksize - csum_size) - (अक्षर *) de;

	/* Allocate new block क्रम the 0th block's dirents */
	bh2 = ext4_append(handle, dir, &block);
	अगर (IS_ERR(bh2)) अणु
		brअन्यथा(bh);
		वापस PTR_ERR(bh2);
	पूर्ण
	ext4_set_inode_flag(dir, EXT4_INODE_INDEX);
	data2 = bh2->b_data;

	स_नकल(data2, de, len);
	स_रखो(de, 0, len); /* wipe old data */
	de = (काष्ठा ext4_dir_entry_2 *) data2;
	top = data2 + len;
	जबतक ((अक्षर *)(de2 = ext4_next_entry(de, blocksize)) < top)
		de = de2;
	de->rec_len = ext4_rec_len_to_disk(data2 + (blocksize - csum_size) -
					   (अक्षर *) de, blocksize);

	अगर (csum_size)
		ext4_initialize_dirent_tail(bh2, blocksize);

	/* Initialize the root; the करोt dirents alपढ़ोy exist */
	de = (काष्ठा ext4_dir_entry_2 *) (&root->करोtकरोt);
	de->rec_len = ext4_rec_len_to_disk(
			blocksize - ext4_dir_rec_len(2, शून्य), blocksize);
	स_रखो (&root->info, 0, माप(root->info));
	root->info.info_length = माप(root->info);
	अगर (ext4_hash_in_dirent(dir))
		root->info.hash_version = DX_HASH_SIPHASH;
	अन्यथा
		root->info.hash_version =
				EXT4_SB(dir->i_sb)->s_def_hash_version;

	entries = root->entries;
	dx_set_block(entries, 1);
	dx_set_count(entries, 1);
	dx_set_limit(entries, dx_root_limit(dir, माप(root->info)));

	/* Initialize as क्रम dx_probe */
	fname->hinfo.hash_version = root->info.hash_version;
	अगर (fname->hinfo.hash_version <= DX_HASH_TEA)
		fname->hinfo.hash_version += EXT4_SB(dir->i_sb)->s_hash_अचिन्हित;
	fname->hinfo.seed = EXT4_SB(dir->i_sb)->s_hash_seed;

	/* हालfolded encrypted hashes are computed on fname setup */
	अगर (!ext4_hash_in_dirent(dir))
		ext4fs_dirhash(dir, fname_name(fname),
				fname_len(fname), &fname->hinfo);

	स_रखो(frames, 0, माप(frames));
	frame = frames;
	frame->entries = entries;
	frame->at = entries;
	frame->bh = bh;

	retval = ext4_handle_dirty_dx_node(handle, dir, frame->bh);
	अगर (retval)
		जाओ out_frames;
	retval = ext4_handle_dirty_dirblock(handle, dir, bh2);
	अगर (retval)
		जाओ out_frames;

	de = करो_split(handle,dir, &bh2, frame, &fname->hinfo);
	अगर (IS_ERR(de)) अणु
		retval = PTR_ERR(de);
		जाओ out_frames;
	पूर्ण

	retval = add_dirent_to_buf(handle, fname, dir, inode, de, bh2);
out_frames:
	/*
	 * Even अगर the block split failed, we have to properly ग_लिखो
	 * out all the changes we did so far. Otherwise we can end up
	 * with corrupted fileप्रणाली.
	 */
	अगर (retval)
		ext4_mark_inode_dirty(handle, dir);
	dx_release(frames);
	brअन्यथा(bh2);
	वापस retval;
पूर्ण

/*
 *	ext4_add_entry()
 *
 * adds a file entry to the specअगरied directory, using the same
 * semantics as ext4_find_entry(). It वापसs शून्य अगर it failed.
 *
 * NOTE!! The inode part of 'de' is left at 0 - which means you
 * may not sleep between calling this and putting something पूर्णांकo
 * the entry, as someone अन्यथा might have used it जबतक you slept.
 */
अटल पूर्णांक ext4_add_entry(handle_t *handle, काष्ठा dentry *dentry,
			  काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ext4_dir_entry_2 *de;
	काष्ठा super_block *sb;
	काष्ठा ext4_filename fname;
	पूर्णांक	retval;
	पूर्णांक	dx_fallback=0;
	अचिन्हित blocksize;
	ext4_lblk_t block, blocks;
	पूर्णांक	csum_size = 0;

	अगर (ext4_has_metadata_csum(inode->i_sb))
		csum_size = माप(काष्ठा ext4_dir_entry_tail);

	sb = dir->i_sb;
	blocksize = sb->s_blocksize;
	अगर (!dentry->d_name.len)
		वापस -EINVAL;

	अगर (fscrypt_is_nokey_name(dentry))
		वापस -ENOKEY;

#अगर_घोषित CONFIG_UNICODE
	अगर (sb_has_strict_encoding(sb) && IS_CASEFOLDED(dir) &&
	    sb->s_encoding && utf8_validate(sb->s_encoding, &dentry->d_name))
		वापस -EINVAL;
#पूर्ण_अगर

	retval = ext4_fname_setup_filename(dir, &dentry->d_name, 0, &fname);
	अगर (retval)
		वापस retval;

	अगर (ext4_has_अंतरभूत_data(dir)) अणु
		retval = ext4_try_add_अंतरभूत_entry(handle, &fname, dir, inode);
		अगर (retval < 0)
			जाओ out;
		अगर (retval == 1) अणु
			retval = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (is_dx(dir)) अणु
		retval = ext4_dx_add_entry(handle, &fname, dir, inode);
		अगर (!retval || (retval != ERR_BAD_DX_सूची))
			जाओ out;
		/* Can we just ignore htree data? */
		अगर (ext4_has_metadata_csum(sb)) अणु
			EXT4_ERROR_INODE(dir,
				"Directory has corrupted htree index.");
			retval = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		ext4_clear_inode_flag(dir, EXT4_INODE_INDEX);
		dx_fallback++;
		retval = ext4_mark_inode_dirty(handle, dir);
		अगर (unlikely(retval))
			जाओ out;
	पूर्ण
	blocks = dir->i_size >> sb->s_blocksize_bits;
	क्रम (block = 0; block < blocks; block++) अणु
		bh = ext4_पढ़ो_dirblock(dir, block, सूचीENT);
		अगर (bh == शून्य) अणु
			bh = ext4_bपढ़ो(handle, dir, block,
					EXT4_GET_BLOCKS_CREATE);
			जाओ add_to_new_block;
		पूर्ण
		अगर (IS_ERR(bh)) अणु
			retval = PTR_ERR(bh);
			bh = शून्य;
			जाओ out;
		पूर्ण
		retval = add_dirent_to_buf(handle, &fname, dir, inode,
					   शून्य, bh);
		अगर (retval != -ENOSPC)
			जाओ out;

		अगर (blocks == 1 && !dx_fallback &&
		    ext4_has_feature_dir_index(sb)) अणु
			retval = make_indexed_dir(handle, &fname, dir,
						  inode, bh);
			bh = शून्य; /* make_indexed_dir releases bh */
			जाओ out;
		पूर्ण
		brअन्यथा(bh);
	पूर्ण
	bh = ext4_append(handle, dir, &block);
add_to_new_block:
	अगर (IS_ERR(bh)) अणु
		retval = PTR_ERR(bh);
		bh = शून्य;
		जाओ out;
	पूर्ण
	de = (काष्ठा ext4_dir_entry_2 *) bh->b_data;
	de->inode = 0;
	de->rec_len = ext4_rec_len_to_disk(blocksize - csum_size, blocksize);

	अगर (csum_size)
		ext4_initialize_dirent_tail(bh, blocksize);

	retval = add_dirent_to_buf(handle, &fname, dir, inode, de, bh);
out:
	ext4_fname_मुक्त_filename(&fname);
	brअन्यथा(bh);
	अगर (retval == 0)
		ext4_set_inode_state(inode, EXT4_STATE_NEWENTRY);
	वापस retval;
पूर्ण

/*
 * Returns 0 क्रम success, or a negative error value
 */
अटल पूर्णांक ext4_dx_add_entry(handle_t *handle, काष्ठा ext4_filename *fname,
			     काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	काष्ठा dx_frame frames[EXT4_HTREE_LEVEL], *frame;
	काष्ठा dx_entry *entries, *at;
	काष्ठा buffer_head *bh;
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा ext4_dir_entry_2 *de;
	पूर्णांक restart;
	पूर्णांक err;

again:
	restart = 0;
	frame = dx_probe(fname, dir, शून्य, frames);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);
	entries = frame->entries;
	at = frame->at;
	bh = ext4_पढ़ो_dirblock(dir, dx_get_block(frame->at), सूचीENT_HTREE);
	अगर (IS_ERR(bh)) अणु
		err = PTR_ERR(bh);
		bh = शून्य;
		जाओ cleanup;
	पूर्ण

	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (err)
		जाओ journal_error;

	err = add_dirent_to_buf(handle, fname, dir, inode, शून्य, bh);
	अगर (err != -ENOSPC)
		जाओ cleanup;

	err = 0;
	/* Block full, should compress but क्रम now just split */
	dxtrace(prपूर्णांकk(KERN_DEBUG "using %u of %u node entries\n",
		       dx_get_count(entries), dx_get_limit(entries)));
	/* Need to split index? */
	अगर (dx_get_count(entries) == dx_get_limit(entries)) अणु
		ext4_lblk_t newblock;
		पूर्णांक levels = frame - frames + 1;
		अचिन्हित पूर्णांक icount;
		पूर्णांक add_level = 1;
		काष्ठा dx_entry *entries2;
		काष्ठा dx_node *node2;
		काष्ठा buffer_head *bh2;

		जबतक (frame > frames) अणु
			अगर (dx_get_count((frame - 1)->entries) <
			    dx_get_limit((frame - 1)->entries)) अणु
				add_level = 0;
				अवरोध;
			पूर्ण
			frame--; /* split higher index block */
			at = frame->at;
			entries = frame->entries;
			restart = 1;
		पूर्ण
		अगर (add_level && levels == ext4_dir_htree_level(sb)) अणु
			ext4_warning(sb, "Directory (ino: %lu) index full, "
					 "reach max htree level :%d",
					 dir->i_ino, levels);
			अगर (ext4_dir_htree_level(sb) < EXT4_HTREE_LEVEL) अणु
				ext4_warning(sb, "Large directory feature is "
						 "not enabled on this "
						 "filesystem");
			पूर्ण
			err = -ENOSPC;
			जाओ cleanup;
		पूर्ण
		icount = dx_get_count(entries);
		bh2 = ext4_append(handle, dir, &newblock);
		अगर (IS_ERR(bh2)) अणु
			err = PTR_ERR(bh2);
			जाओ cleanup;
		पूर्ण
		node2 = (काष्ठा dx_node *)(bh2->b_data);
		entries2 = node2->entries;
		स_रखो(&node2->fake, 0, माप(काष्ठा fake_dirent));
		node2->fake.rec_len = ext4_rec_len_to_disk(sb->s_blocksize,
							   sb->s_blocksize);
		BUFFER_TRACE(frame->bh, "get_write_access");
		err = ext4_journal_get_ग_लिखो_access(handle, frame->bh);
		अगर (err)
			जाओ journal_error;
		अगर (!add_level) अणु
			अचिन्हित icount1 = icount/2, icount2 = icount - icount1;
			अचिन्हित hash2 = dx_get_hash(entries + icount1);
			dxtrace(prपूर्णांकk(KERN_DEBUG "Split index %i/%i\n",
				       icount1, icount2));

			BUFFER_TRACE(frame->bh, "get_write_access"); /* index root */
			err = ext4_journal_get_ग_लिखो_access(handle,
							     (frame - 1)->bh);
			अगर (err)
				जाओ journal_error;

			स_नकल((अक्षर *) entries2, (अक्षर *) (entries + icount1),
			       icount2 * माप(काष्ठा dx_entry));
			dx_set_count(entries, icount1);
			dx_set_count(entries2, icount2);
			dx_set_limit(entries2, dx_node_limit(dir));

			/* Which index block माला_लो the new entry? */
			अगर (at - entries >= icount1) अणु
				frame->at = at = at - entries - icount1 + entries2;
				frame->entries = entries = entries2;
				swap(frame->bh, bh2);
			पूर्ण
			dx_insert_block((frame - 1), hash2, newblock);
			dxtrace(dx_show_index("node", frame->entries));
			dxtrace(dx_show_index("node",
			       ((काष्ठा dx_node *) bh2->b_data)->entries));
			err = ext4_handle_dirty_dx_node(handle, dir, bh2);
			अगर (err)
				जाओ journal_error;
			brअन्यथा (bh2);
			err = ext4_handle_dirty_dx_node(handle, dir,
						   (frame - 1)->bh);
			अगर (err)
				जाओ journal_error;
			err = ext4_handle_dirty_dx_node(handle, dir,
							frame->bh);
			अगर (err)
				जाओ journal_error;
		पूर्ण अन्यथा अणु
			काष्ठा dx_root *dxroot;
			स_नकल((अक्षर *) entries2, (अक्षर *) entries,
			       icount * माप(काष्ठा dx_entry));
			dx_set_limit(entries2, dx_node_limit(dir));

			/* Set up root */
			dx_set_count(entries, 1);
			dx_set_block(entries + 0, newblock);
			dxroot = (काष्ठा dx_root *)frames[0].bh->b_data;
			dxroot->info.indirect_levels += 1;
			dxtrace(prपूर्णांकk(KERN_DEBUG
				       "Creating %d level index...\n",
				       dxroot->info.indirect_levels));
			err = ext4_handle_dirty_dx_node(handle, dir, frame->bh);
			अगर (err)
				जाओ journal_error;
			err = ext4_handle_dirty_dx_node(handle, dir, bh2);
			brअन्यथा(bh2);
			restart = 1;
			जाओ journal_error;
		पूर्ण
	पूर्ण
	de = करो_split(handle, dir, &bh, frame, &fname->hinfo);
	अगर (IS_ERR(de)) अणु
		err = PTR_ERR(de);
		जाओ cleanup;
	पूर्ण
	err = add_dirent_to_buf(handle, fname, dir, inode, de, bh);
	जाओ cleanup;

journal_error:
	ext4_std_error(dir->i_sb, err); /* this is a no-op अगर err == 0 */
cleanup:
	brअन्यथा(bh);
	dx_release(frames);
	/* @restart is true means htree-path has been changed, we need to
	 * repeat dx_probe() to find out valid htree-path
	 */
	अगर (restart && err == 0)
		जाओ again;
	वापस err;
पूर्ण

/*
 * ext4_generic_delete_entry deletes a directory entry by merging it
 * with the previous entry
 */
पूर्णांक ext4_generic_delete_entry(काष्ठा inode *dir,
			      काष्ठा ext4_dir_entry_2 *de_del,
			      काष्ठा buffer_head *bh,
			      व्योम *entry_buf,
			      पूर्णांक buf_size,
			      पूर्णांक csum_size)
अणु
	काष्ठा ext4_dir_entry_2 *de, *pde;
	अचिन्हित पूर्णांक blocksize = dir->i_sb->s_blocksize;
	पूर्णांक i;

	i = 0;
	pde = शून्य;
	de = (काष्ठा ext4_dir_entry_2 *)entry_buf;
	जबतक (i < buf_size - csum_size) अणु
		अगर (ext4_check_dir_entry(dir, शून्य, de, bh,
					 entry_buf, buf_size, i))
			वापस -EFSCORRUPTED;
		अगर (de == de_del)  अणु
			अगर (pde) अणु
				pde->rec_len = ext4_rec_len_to_disk(
					ext4_rec_len_from_disk(pde->rec_len,
							       blocksize) +
					ext4_rec_len_from_disk(de->rec_len,
							       blocksize),
					blocksize);

				/* wipe entire dir_entry */
				स_रखो(de, 0, ext4_rec_len_from_disk(de->rec_len,
								blocksize));
			पूर्ण अन्यथा अणु
				/* wipe dir_entry excluding the rec_len field */
				de->inode = 0;
				स_रखो(&de->name_len, 0,
					ext4_rec_len_from_disk(de->rec_len,
								blocksize) -
					दुरत्व(काष्ठा ext4_dir_entry_2,
								name_len));
			पूर्ण

			inode_inc_iversion(dir);
			वापस 0;
		पूर्ण
		i += ext4_rec_len_from_disk(de->rec_len, blocksize);
		pde = de;
		de = ext4_next_entry(de, blocksize);
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक ext4_delete_entry(handle_t *handle,
			     काष्ठा inode *dir,
			     काष्ठा ext4_dir_entry_2 *de_del,
			     काष्ठा buffer_head *bh)
अणु
	पूर्णांक err, csum_size = 0;

	अगर (ext4_has_अंतरभूत_data(dir)) अणु
		पूर्णांक has_अंतरभूत_data = 1;
		err = ext4_delete_अंतरभूत_entry(handle, dir, de_del, bh,
					       &has_अंतरभूत_data);
		अगर (has_अंतरभूत_data)
			वापस err;
	पूर्ण

	अगर (ext4_has_metadata_csum(dir->i_sb))
		csum_size = माप(काष्ठा ext4_dir_entry_tail);

	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (unlikely(err))
		जाओ out;

	err = ext4_generic_delete_entry(dir, de_del, bh, bh->b_data,
					dir->i_sb->s_blocksize, csum_size);
	अगर (err)
		जाओ out;

	BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_dirblock(handle, dir, bh);
	अगर (unlikely(err))
		जाओ out;

	वापस 0;
out:
	अगर (err != -ENOENT)
		ext4_std_error(dir->i_sb, err);
	वापस err;
पूर्ण

/*
 * Set directory link count to 1 अगर nlinks > EXT4_LINK_MAX, or अगर nlinks == 2
 * since this indicates that nlinks count was previously 1 to aव्योम overflowing
 * the 16-bit i_links_count field on disk.  Directories with i_nlink == 1 mean
 * that subdirectory link counts are not being मुख्यtained accurately.
 *
 * The caller has alपढ़ोy checked क्रम i_nlink overflow in हाल the सूची_LINK
 * feature is not enabled and वापसed -EMLINK.  The is_dx() check is a proxy
 * क्रम checking S_ISसूची(inode) (since the INODE_INDEX feature will not be set
 * on regular files) and to aव्योम creating huge/slow non-HTREE directories.
 */
अटल व्योम ext4_inc_count(काष्ठा inode *inode)
अणु
	inc_nlink(inode);
	अगर (is_dx(inode) &&
	    (inode->i_nlink > EXT4_LINK_MAX || inode->i_nlink == 2))
		set_nlink(inode, 1);
पूर्ण

/*
 * If a directory had nlink == 1, then we should let it be 1. This indicates
 * directory has >EXT4_LINK_MAX subdirs.
 */
अटल व्योम ext4_dec_count(काष्ठा inode *inode)
अणु
	अगर (!S_ISसूची(inode->i_mode) || inode->i_nlink > 2)
		drop_nlink(inode);
पूर्ण


/*
 * Add non-directory inode to a directory. On success, the inode reference is
 * consumed by dentry is instantiation. This is also indicated by clearing of
 * *inodep poपूर्णांकer. On failure, the caller is responsible क्रम dropping the
 * inode reference in the safe context.
 */
अटल पूर्णांक ext4_add_nondir(handle_t *handle,
		काष्ठा dentry *dentry, काष्ठा inode **inodep)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	काष्ठा inode *inode = *inodep;
	पूर्णांक err = ext4_add_entry(handle, dentry, inode);
	अगर (!err) अणु
		err = ext4_mark_inode_dirty(handle, inode);
		अगर (IS_सूचीSYNC(dir))
			ext4_handle_sync(handle);
		d_instantiate_new(dentry, inode);
		*inodep = शून्य;
		वापस err;
	पूर्ण
	drop_nlink(inode);
	ext4_orphan_add(handle, inode);
	unlock_new_inode(inode);
	वापस err;
पूर्ण

/*
 * By the समय this is called, we alपढ़ोy have created
 * the directory cache entry क्रम the new file, but it
 * is so far negative - it has no inode.
 *
 * If the create succeeds, we fill in the inode inक्रमmation
 * with d_instantiate().
 */
अटल पूर्णांक ext4_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	handle_t *handle;
	काष्ठा inode *inode;
	पूर्णांक err, credits, retries = 0;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	credits = (EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
		   EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3);
retry:
	inode = ext4_new_inode_start_handle(mnt_userns, dir, mode, &dentry->d_name,
					    0, शून्य, EXT4_HT_सूची, credits);
	handle = ext4_journal_current_handle();
	err = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		inode->i_op = &ext4_file_inode_operations;
		inode->i_fop = &ext4_file_operations;
		ext4_set_aops(inode);
		err = ext4_add_nondir(handle, dentry, &inode);
		अगर (!err)
			ext4_fc_track_create(handle, dentry);
	पूर्ण
	अगर (handle)
		ext4_journal_stop(handle);
	अगर (!IS_ERR_OR_शून्य(inode))
		iput(inode);
	अगर (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		जाओ retry;
	वापस err;
पूर्ण

अटल पूर्णांक ext4_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	handle_t *handle;
	काष्ठा inode *inode;
	पूर्णांक err, credits, retries = 0;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	credits = (EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
		   EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3);
retry:
	inode = ext4_new_inode_start_handle(mnt_userns, dir, mode, &dentry->d_name,
					    0, शून्य, EXT4_HT_सूची, credits);
	handle = ext4_journal_current_handle();
	err = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		init_special_inode(inode, inode->i_mode, rdev);
		inode->i_op = &ext4_special_inode_operations;
		err = ext4_add_nondir(handle, dentry, &inode);
		अगर (!err)
			ext4_fc_track_create(handle, dentry);
	पूर्ण
	अगर (handle)
		ext4_journal_stop(handle);
	अगर (!IS_ERR_OR_शून्य(inode))
		iput(inode);
	अगर (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		जाओ retry;
	वापस err;
पूर्ण

अटल पूर्णांक ext4_क्षणिक_ख(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode)
अणु
	handle_t *handle;
	काष्ठा inode *inode;
	पूर्णांक err, retries = 0;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

retry:
	inode = ext4_new_inode_start_handle(mnt_userns, dir, mode,
					    शून्य, 0, शून्य,
					    EXT4_HT_सूची,
			EXT4_MAXQUOTAS_INIT_BLOCKS(dir->i_sb) +
			  4 + EXT4_XATTR_TRANS_BLOCKS);
	handle = ext4_journal_current_handle();
	err = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		inode->i_op = &ext4_file_inode_operations;
		inode->i_fop = &ext4_file_operations;
		ext4_set_aops(inode);
		d_क्षणिक_ख(dentry, inode);
		err = ext4_orphan_add(handle, inode);
		अगर (err)
			जाओ err_unlock_inode;
		mark_inode_dirty(inode);
		unlock_new_inode(inode);
	पूर्ण
	अगर (handle)
		ext4_journal_stop(handle);
	अगर (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		जाओ retry;
	वापस err;
err_unlock_inode:
	ext4_journal_stop(handle);
	unlock_new_inode(inode);
	वापस err;
पूर्ण

काष्ठा ext4_dir_entry_2 *ext4_init_करोt_करोtकरोt(काष्ठा inode *inode,
			  काष्ठा ext4_dir_entry_2 *de,
			  पूर्णांक blocksize, पूर्णांक csum_size,
			  अचिन्हित पूर्णांक parent_ino, पूर्णांक करोtकरोt_real_len)
अणु
	de->inode = cpu_to_le32(inode->i_ino);
	de->name_len = 1;
	de->rec_len = ext4_rec_len_to_disk(ext4_dir_rec_len(de->name_len, शून्य),
					   blocksize);
	म_नकल(de->name, ".");
	ext4_set_de_type(inode->i_sb, de, S_IFसूची);

	de = ext4_next_entry(de, blocksize);
	de->inode = cpu_to_le32(parent_ino);
	de->name_len = 2;
	अगर (!करोtकरोt_real_len)
		de->rec_len = ext4_rec_len_to_disk(blocksize -
					(csum_size + ext4_dir_rec_len(1, शून्य)),
					blocksize);
	अन्यथा
		de->rec_len = ext4_rec_len_to_disk(
					ext4_dir_rec_len(de->name_len, शून्य),
					blocksize);
	म_नकल(de->name, "..");
	ext4_set_de_type(inode->i_sb, de, S_IFसूची);

	वापस ext4_next_entry(de, blocksize);
पूर्ण

पूर्णांक ext4_init_new_dir(handle_t *handle, काष्ठा inode *dir,
			     काष्ठा inode *inode)
अणु
	काष्ठा buffer_head *dir_block = शून्य;
	काष्ठा ext4_dir_entry_2 *de;
	ext4_lblk_t block = 0;
	अचिन्हित पूर्णांक blocksize = dir->i_sb->s_blocksize;
	पूर्णांक csum_size = 0;
	पूर्णांक err;

	अगर (ext4_has_metadata_csum(dir->i_sb))
		csum_size = माप(काष्ठा ext4_dir_entry_tail);

	अगर (ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA)) अणु
		err = ext4_try_create_अंतरभूत_dir(handle, dir, inode);
		अगर (err < 0 && err != -ENOSPC)
			जाओ out;
		अगर (!err)
			जाओ out;
	पूर्ण

	inode->i_size = 0;
	dir_block = ext4_append(handle, inode, &block);
	अगर (IS_ERR(dir_block))
		वापस PTR_ERR(dir_block);
	de = (काष्ठा ext4_dir_entry_2 *)dir_block->b_data;
	ext4_init_करोt_करोtकरोt(inode, de, blocksize, csum_size, dir->i_ino, 0);
	set_nlink(inode, 2);
	अगर (csum_size)
		ext4_initialize_dirent_tail(dir_block, blocksize);

	BUFFER_TRACE(dir_block, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_dirblock(handle, inode, dir_block);
	अगर (err)
		जाओ out;
	set_buffer_verअगरied(dir_block);
out:
	brअन्यथा(dir_block);
	वापस err;
पूर्ण

अटल पूर्णांक ext4_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	handle_t *handle;
	काष्ठा inode *inode;
	पूर्णांक err, err2 = 0, credits, retries = 0;

	अगर (EXT4_सूची_LINK_MAX(dir))
		वापस -EMLINK;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	credits = (EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
		   EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3);
retry:
	inode = ext4_new_inode_start_handle(mnt_userns, dir, S_IFसूची | mode,
					    &dentry->d_name,
					    0, शून्य, EXT4_HT_सूची, credits);
	handle = ext4_journal_current_handle();
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out_stop;

	inode->i_op = &ext4_dir_inode_operations;
	inode->i_fop = &ext4_dir_operations;
	err = ext4_init_new_dir(handle, dir, inode);
	अगर (err)
		जाओ out_clear_inode;
	err = ext4_mark_inode_dirty(handle, inode);
	अगर (!err)
		err = ext4_add_entry(handle, dentry, inode);
	अगर (err) अणु
out_clear_inode:
		clear_nlink(inode);
		ext4_orphan_add(handle, inode);
		unlock_new_inode(inode);
		err2 = ext4_mark_inode_dirty(handle, inode);
		अगर (unlikely(err2))
			err = err2;
		ext4_journal_stop(handle);
		iput(inode);
		जाओ out_retry;
	पूर्ण
	ext4_inc_count(dir);

	ext4_update_dx_flag(dir);
	err = ext4_mark_inode_dirty(handle, dir);
	अगर (err)
		जाओ out_clear_inode;
	d_instantiate_new(dentry, inode);
	ext4_fc_track_create(handle, dentry);
	अगर (IS_सूचीSYNC(dir))
		ext4_handle_sync(handle);

out_stop:
	अगर (handle)
		ext4_journal_stop(handle);
out_retry:
	अगर (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		जाओ retry;
	वापस err;
पूर्ण

/*
 * routine to check that the specअगरied directory is empty (क्रम सूची_हटाओ)
 */
bool ext4_empty_dir(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक offset;
	काष्ठा buffer_head *bh;
	काष्ठा ext4_dir_entry_2 *de;
	काष्ठा super_block *sb;

	अगर (ext4_has_अंतरभूत_data(inode)) अणु
		पूर्णांक has_अंतरभूत_data = 1;
		पूर्णांक ret;

		ret = empty_अंतरभूत_dir(inode, &has_अंतरभूत_data);
		अगर (has_अंतरभूत_data)
			वापस ret;
	पूर्ण

	sb = inode->i_sb;
	अगर (inode->i_size < ext4_dir_rec_len(1, शून्य) +
					ext4_dir_rec_len(2, शून्य)) अणु
		EXT4_ERROR_INODE(inode, "invalid size");
		वापस true;
	पूर्ण
	/* The first directory block must not be a hole,
	 * so treat it as सूचीENT_HTREE
	 */
	bh = ext4_पढ़ो_dirblock(inode, 0, सूचीENT_HTREE);
	अगर (IS_ERR(bh))
		वापस true;

	de = (काष्ठा ext4_dir_entry_2 *) bh->b_data;
	अगर (ext4_check_dir_entry(inode, शून्य, de, bh, bh->b_data, bh->b_size,
				 0) ||
	    le32_to_cpu(de->inode) != inode->i_ino || म_भेद(".", de->name)) अणु
		ext4_warning_inode(inode, "directory missing '.'");
		brअन्यथा(bh);
		वापस true;
	पूर्ण
	offset = ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize);
	de = ext4_next_entry(de, sb->s_blocksize);
	अगर (ext4_check_dir_entry(inode, शून्य, de, bh, bh->b_data, bh->b_size,
				 offset) ||
	    le32_to_cpu(de->inode) == 0 || म_भेद("..", de->name)) अणु
		ext4_warning_inode(inode, "directory missing '..'");
		brअन्यथा(bh);
		वापस true;
	पूर्ण
	offset += ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize);
	जबतक (offset < inode->i_size) अणु
		अगर (!(offset & (sb->s_blocksize - 1))) अणु
			अचिन्हित पूर्णांक lblock;
			brअन्यथा(bh);
			lblock = offset >> EXT4_BLOCK_SIZE_BITS(sb);
			bh = ext4_पढ़ो_dirblock(inode, lblock, EITHER);
			अगर (bh == शून्य) अणु
				offset += sb->s_blocksize;
				जारी;
			पूर्ण
			अगर (IS_ERR(bh))
				वापस true;
		पूर्ण
		de = (काष्ठा ext4_dir_entry_2 *) (bh->b_data +
					(offset & (sb->s_blocksize - 1)));
		अगर (ext4_check_dir_entry(inode, शून्य, de, bh,
					 bh->b_data, bh->b_size, offset)) अणु
			offset = (offset | (sb->s_blocksize - 1)) + 1;
			जारी;
		पूर्ण
		अगर (le32_to_cpu(de->inode)) अणु
			brअन्यथा(bh);
			वापस false;
		पूर्ण
		offset += ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize);
	पूर्ण
	brअन्यथा(bh);
	वापस true;
पूर्ण

/*
 * ext4_orphan_add() links an unlinked or truncated inode पूर्णांकo a list of
 * such inodes, starting at the superblock, in हाल we crash beक्रमe the
 * file is बंदd/deleted, or in हाल the inode truncate spans multiple
 * transactions and the last transaction is not recovered after a crash.
 *
 * At fileप्रणाली recovery समय, we walk this list deleting unlinked
 * inodes and truncating linked inodes in ext4_orphan_cleanup().
 *
 * Orphan list manipulation functions must be called under i_mutex unless
 * we are just creating the inode or deleting it.
 */
पूर्णांक ext4_orphan_add(handle_t *handle, काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_iloc iloc;
	पूर्णांक err = 0, rc;
	bool dirty = false;

	अगर (!sbi->s_journal || is_bad_inode(inode))
		वापस 0;

	WARN_ON_ONCE(!(inode->i_state & (I_NEW | I_FREEING)) &&
		     !inode_is_locked(inode));
	/*
	 * Exit early अगर inode alपढ़ोy is on orphan list. This is a big speedup
	 * since we करोn't have to contend on the global s_orphan_lock.
	 */
	अगर (!list_empty(&EXT4_I(inode)->i_orphan))
		वापस 0;

	/*
	 * Orphan handling is only valid क्रम files with data blocks
	 * being truncated, or files being unlinked. Note that we either
	 * hold i_mutex, or the inode can not be referenced from outside,
	 * so i_nlink should not be bumped due to race
	 */
	ASSERT((S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
		  S_ISLNK(inode->i_mode)) || inode->i_nlink == 0);

	BUFFER_TRACE(sbi->s_sbh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, sbi->s_sbh);
	अगर (err)
		जाओ out;

	err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
	अगर (err)
		जाओ out;

	mutex_lock(&sbi->s_orphan_lock);
	/*
	 * Due to previous errors inode may be alपढ़ोy a part of on-disk
	 * orphan list. If so skip on-disk list modअगरication.
	 */
	अगर (!NEXT_ORPHAN(inode) || NEXT_ORPHAN(inode) >
	    (le32_to_cpu(sbi->s_es->s_inodes_count))) अणु
		/* Insert this inode at the head of the on-disk orphan list */
		NEXT_ORPHAN(inode) = le32_to_cpu(sbi->s_es->s_last_orphan);
		lock_buffer(sbi->s_sbh);
		sbi->s_es->s_last_orphan = cpu_to_le32(inode->i_ino);
		ext4_superblock_csum_set(sb);
		unlock_buffer(sbi->s_sbh);
		dirty = true;
	पूर्ण
	list_add(&EXT4_I(inode)->i_orphan, &sbi->s_orphan);
	mutex_unlock(&sbi->s_orphan_lock);

	अगर (dirty) अणु
		err = ext4_handle_dirty_metadata(handle, शून्य, sbi->s_sbh);
		rc = ext4_mark_iloc_dirty(handle, inode, &iloc);
		अगर (!err)
			err = rc;
		अगर (err) अणु
			/*
			 * We have to हटाओ inode from in-memory list अगर
			 * addition to on disk orphan list failed. Stray orphan
			 * list entries can cause panics at unmount समय.
			 */
			mutex_lock(&sbi->s_orphan_lock);
			list_del_init(&EXT4_I(inode)->i_orphan);
			mutex_unlock(&sbi->s_orphan_lock);
		पूर्ण
	पूर्ण अन्यथा
		brअन्यथा(iloc.bh);

	jbd_debug(4, "superblock will point to %lu\n", inode->i_ino);
	jbd_debug(4, "orphan inode %lu will point to %d\n",
			inode->i_ino, NEXT_ORPHAN(inode));
out:
	ext4_std_error(sb, err);
	वापस err;
पूर्ण

/*
 * ext4_orphan_del() हटाओs an unlinked or truncated inode from the list
 * of such inodes stored on disk, because it is finally being cleaned up.
 */
पूर्णांक ext4_orphan_del(handle_t *handle, काष्ठा inode *inode)
अणु
	काष्ठा list_head *prev;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__u32 ino_next;
	काष्ठा ext4_iloc iloc;
	पूर्णांक err = 0;

	अगर (!sbi->s_journal && !(sbi->s_mount_state & EXT4_ORPHAN_FS))
		वापस 0;

	WARN_ON_ONCE(!(inode->i_state & (I_NEW | I_FREEING)) &&
		     !inode_is_locked(inode));
	/* Do this quick check beक्रमe taking global s_orphan_lock. */
	अगर (list_empty(&ei->i_orphan))
		वापस 0;

	अगर (handle) अणु
		/* Grab inode buffer early beक्रमe taking global s_orphan_lock */
		err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
	पूर्ण

	mutex_lock(&sbi->s_orphan_lock);
	jbd_debug(4, "remove inode %lu from orphan list\n", inode->i_ino);

	prev = ei->i_orphan.prev;
	list_del_init(&ei->i_orphan);

	/* If we're on an error path, we may not have a valid
	 * transaction handle with which to update the orphan list on
	 * disk, but we still need to हटाओ the inode from the linked
	 * list in memory. */
	अगर (!handle || err) अणु
		mutex_unlock(&sbi->s_orphan_lock);
		जाओ out_err;
	पूर्ण

	ino_next = NEXT_ORPHAN(inode);
	अगर (prev == &sbi->s_orphan) अणु
		jbd_debug(4, "superblock will point to %u\n", ino_next);
		BUFFER_TRACE(sbi->s_sbh, "get_write_access");
		err = ext4_journal_get_ग_लिखो_access(handle, sbi->s_sbh);
		अगर (err) अणु
			mutex_unlock(&sbi->s_orphan_lock);
			जाओ out_brअन्यथा;
		पूर्ण
		lock_buffer(sbi->s_sbh);
		sbi->s_es->s_last_orphan = cpu_to_le32(ino_next);
		ext4_superblock_csum_set(inode->i_sb);
		unlock_buffer(sbi->s_sbh);
		mutex_unlock(&sbi->s_orphan_lock);
		err = ext4_handle_dirty_metadata(handle, शून्य, sbi->s_sbh);
	पूर्ण अन्यथा अणु
		काष्ठा ext4_iloc iloc2;
		काष्ठा inode *i_prev =
			&list_entry(prev, काष्ठा ext4_inode_info, i_orphan)->vfs_inode;

		jbd_debug(4, "orphan inode %lu will point to %u\n",
			  i_prev->i_ino, ino_next);
		err = ext4_reserve_inode_ग_लिखो(handle, i_prev, &iloc2);
		अगर (err) अणु
			mutex_unlock(&sbi->s_orphan_lock);
			जाओ out_brअन्यथा;
		पूर्ण
		NEXT_ORPHAN(i_prev) = ino_next;
		err = ext4_mark_iloc_dirty(handle, i_prev, &iloc2);
		mutex_unlock(&sbi->s_orphan_lock);
	पूर्ण
	अगर (err)
		जाओ out_brअन्यथा;
	NEXT_ORPHAN(inode) = 0;
	err = ext4_mark_iloc_dirty(handle, inode, &iloc);
out_err:
	ext4_std_error(inode->i_sb, err);
	वापस err;

out_brअन्यथा:
	brअन्यथा(iloc.bh);
	जाओ out_err;
पूर्ण

अटल पूर्णांक ext4_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode;
	काष्ठा buffer_head *bh;
	काष्ठा ext4_dir_entry_2 *de;
	handle_t *handle = शून्य;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(dir->i_sb))))
		वापस -EIO;

	/* Initialize quotas beक्रमe so that eventual ग_लिखोs go in
	 * separate transaction */
	retval = dquot_initialize(dir);
	अगर (retval)
		वापस retval;
	retval = dquot_initialize(d_inode(dentry));
	अगर (retval)
		वापस retval;

	retval = -ENOENT;
	bh = ext4_find_entry(dir, &dentry->d_name, &de, शून्य);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);
	अगर (!bh)
		जाओ end_सूची_हटाओ;

	inode = d_inode(dentry);

	retval = -EFSCORRUPTED;
	अगर (le32_to_cpu(de->inode) != inode->i_ino)
		जाओ end_सूची_हटाओ;

	retval = -ENOTEMPTY;
	अगर (!ext4_empty_dir(inode))
		जाओ end_सूची_हटाओ;

	handle = ext4_journal_start(dir, EXT4_HT_सूची,
				    EXT4_DATA_TRANS_BLOCKS(dir->i_sb));
	अगर (IS_ERR(handle)) अणु
		retval = PTR_ERR(handle);
		handle = शून्य;
		जाओ end_सूची_हटाओ;
	पूर्ण

	अगर (IS_सूचीSYNC(dir))
		ext4_handle_sync(handle);

	retval = ext4_delete_entry(handle, dir, de, bh);
	अगर (retval)
		जाओ end_सूची_हटाओ;
	अगर (!EXT4_सूची_LINK_EMPTY(inode))
		ext4_warning_inode(inode,
			     "empty directory '%.*s' has too many links (%u)",
			     dentry->d_name.len, dentry->d_name.name,
			     inode->i_nlink);
	inode_inc_iversion(inode);
	clear_nlink(inode);
	/* There's no need to set i_disksize: the fact that i_nlink is
	 * zero will ensure that the right thing happens during any
	 * recovery. */
	inode->i_size = 0;
	ext4_orphan_add(handle, inode);
	inode->i_स_समय = dir->i_स_समय = dir->i_mसमय = current_समय(inode);
	retval = ext4_mark_inode_dirty(handle, inode);
	अगर (retval)
		जाओ end_सूची_हटाओ;
	ext4_dec_count(dir);
	ext4_update_dx_flag(dir);
	ext4_fc_track_unlink(handle, dentry);
	retval = ext4_mark_inode_dirty(handle, dir);

#अगर_घोषित CONFIG_UNICODE
	/* VFS negative dentries are incompatible with Encoding and
	 * Case-insensitiveness. Eventually we'll want aव्योम
	 * invalidating the dentries here, aदीर्घside with वापसing the
	 * negative dentries at ext4_lookup(), when it is better
	 * supported by the VFS क्रम the CI हाल.
	 */
	अगर (IS_CASEFOLDED(dir))
		d_invalidate(dentry);
#पूर्ण_अगर

end_सूची_हटाओ:
	brअन्यथा(bh);
	अगर (handle)
		ext4_journal_stop(handle);
	वापस retval;
पूर्ण

पूर्णांक __ext4_unlink(handle_t *handle, काष्ठा inode *dir, स्थिर काष्ठा qstr *d_name,
		  काष्ठा inode *inode)
अणु
	पूर्णांक retval = -ENOENT;
	काष्ठा buffer_head *bh;
	काष्ठा ext4_dir_entry_2 *de;
	पूर्णांक skip_हटाओ_dentry = 0;

	bh = ext4_find_entry(dir, d_name, &de, शून्य);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	अगर (!bh)
		वापस -ENOENT;

	अगर (le32_to_cpu(de->inode) != inode->i_ino) अणु
		/*
		 * It's okay अगर we find करोnt find dentry which matches
		 * the inode. That's because it might have gotten
		 * नामd to a dअगरferent inode number
		 */
		अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
			skip_हटाओ_dentry = 1;
		अन्यथा
			जाओ out;
	पूर्ण

	अगर (IS_सूचीSYNC(dir))
		ext4_handle_sync(handle);

	अगर (!skip_हटाओ_dentry) अणु
		retval = ext4_delete_entry(handle, dir, de, bh);
		अगर (retval)
			जाओ out;
		dir->i_स_समय = dir->i_mसमय = current_समय(dir);
		ext4_update_dx_flag(dir);
		retval = ext4_mark_inode_dirty(handle, dir);
		अगर (retval)
			जाओ out;
	पूर्ण अन्यथा अणु
		retval = 0;
	पूर्ण
	अगर (inode->i_nlink == 0)
		ext4_warning_inode(inode, "Deleting file '%.*s' with no links",
				   d_name->len, d_name->name);
	अन्यथा
		drop_nlink(inode);
	अगर (!inode->i_nlink)
		ext4_orphan_add(handle, inode);
	inode->i_स_समय = current_समय(inode);
	retval = ext4_mark_inode_dirty(handle, inode);

out:
	brअन्यथा(bh);
	वापस retval;
पूर्ण

अटल पूर्णांक ext4_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	handle_t *handle;
	पूर्णांक retval;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(dir->i_sb))))
		वापस -EIO;

	trace_ext4_unlink_enter(dir, dentry);
	/*
	 * Initialize quotas beक्रमe so that eventual ग_लिखोs go
	 * in separate transaction
	 */
	retval = dquot_initialize(dir);
	अगर (retval)
		जाओ out_trace;
	retval = dquot_initialize(d_inode(dentry));
	अगर (retval)
		जाओ out_trace;

	handle = ext4_journal_start(dir, EXT4_HT_सूची,
				    EXT4_DATA_TRANS_BLOCKS(dir->i_sb));
	अगर (IS_ERR(handle)) अणु
		retval = PTR_ERR(handle);
		जाओ out_trace;
	पूर्ण

	retval = __ext4_unlink(handle, dir, &dentry->d_name, d_inode(dentry));
	अगर (!retval)
		ext4_fc_track_unlink(handle, dentry);
#अगर_घोषित CONFIG_UNICODE
	/* VFS negative dentries are incompatible with Encoding and
	 * Case-insensitiveness. Eventually we'll want aव्योम
	 * invalidating the dentries here, aदीर्घside with वापसing the
	 * negative dentries at ext4_lookup(), when it is  better
	 * supported by the VFS क्रम the CI हाल.
	 */
	अगर (IS_CASEFOLDED(dir))
		d_invalidate(dentry);
#पूर्ण_अगर
	अगर (handle)
		ext4_journal_stop(handle);

out_trace:
	trace_ext4_unlink_निकास(dentry, retval);
	वापस retval;
पूर्ण

अटल पूर्णांक ext4_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	handle_t *handle;
	काष्ठा inode *inode;
	पूर्णांक err, len = म_माप(symname);
	पूर्णांक credits;
	काष्ठा fscrypt_str disk_link;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(dir->i_sb))))
		वापस -EIO;

	err = fscrypt_prepare_symlink(dir, symname, len, dir->i_sb->s_blocksize,
				      &disk_link);
	अगर (err)
		वापस err;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	अगर ((disk_link.len > EXT4_N_BLOCKS * 4)) अणु
		/*
		 * For non-fast symlinks, we just allocate inode and put it on
		 * orphan list in the first transaction => we need biपंचांगap,
		 * group descriptor, sb, inode block, quota blocks, and
		 * possibly selinux xattr blocks.
		 */
		credits = 4 + EXT4_MAXQUOTAS_INIT_BLOCKS(dir->i_sb) +
			  EXT4_XATTR_TRANS_BLOCKS;
	पूर्ण अन्यथा अणु
		/*
		 * Fast symlink. We have to add entry to directory
		 * (EXT4_DATA_TRANS_BLOCKS + EXT4_INDEX_EXTRA_TRANS_BLOCKS),
		 * allocate new inode (biपंचांगap, group descriptor, inode block,
		 * quota blocks, sb is alपढ़ोy counted in previous macros).
		 */
		credits = EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
			  EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3;
	पूर्ण

	inode = ext4_new_inode_start_handle(mnt_userns, dir, S_IFLNK|S_IRWXUGO,
					    &dentry->d_name, 0, शून्य,
					    EXT4_HT_सूची, credits);
	handle = ext4_journal_current_handle();
	अगर (IS_ERR(inode)) अणु
		अगर (handle)
			ext4_journal_stop(handle);
		वापस PTR_ERR(inode);
	पूर्ण

	अगर (IS_ENCRYPTED(inode)) अणु
		err = fscrypt_encrypt_symlink(inode, symname, len, &disk_link);
		अगर (err)
			जाओ err_drop_inode;
		inode->i_op = &ext4_encrypted_symlink_inode_operations;
	पूर्ण

	अगर ((disk_link.len > EXT4_N_BLOCKS * 4)) अणु
		अगर (!IS_ENCRYPTED(inode))
			inode->i_op = &ext4_symlink_inode_operations;
		inode_nohighmem(inode);
		ext4_set_aops(inode);
		/*
		 * We cannot call page_symlink() with transaction started
		 * because it calls पूर्णांकo ext4_ग_लिखो_begin() which can रुको
		 * क्रम transaction commit अगर we are running out of space
		 * and thus we deadlock. So we have to stop transaction now
		 * and restart it when symlink contents is written.
		 *
		 * To keep fs consistent in हाल of crash, we have to put inode
		 * to orphan list in the mean समय.
		 */
		drop_nlink(inode);
		err = ext4_orphan_add(handle, inode);
		अगर (handle)
			ext4_journal_stop(handle);
		handle = शून्य;
		अगर (err)
			जाओ err_drop_inode;
		err = __page_symlink(inode, disk_link.name, disk_link.len, 1);
		अगर (err)
			जाओ err_drop_inode;
		/*
		 * Now inode is being linked पूर्णांकo dir (EXT4_DATA_TRANS_BLOCKS
		 * + EXT4_INDEX_EXTRA_TRANS_BLOCKS), inode is also modअगरied
		 */
		handle = ext4_journal_start(dir, EXT4_HT_सूची,
				EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
				EXT4_INDEX_EXTRA_TRANS_BLOCKS + 1);
		अगर (IS_ERR(handle)) अणु
			err = PTR_ERR(handle);
			handle = शून्य;
			जाओ err_drop_inode;
		पूर्ण
		set_nlink(inode, 1);
		err = ext4_orphan_del(handle, inode);
		अगर (err)
			जाओ err_drop_inode;
	पूर्ण अन्यथा अणु
		/* clear the extent क्रमmat क्रम fast symlink */
		ext4_clear_inode_flag(inode, EXT4_INODE_EXTENTS);
		अगर (!IS_ENCRYPTED(inode)) अणु
			inode->i_op = &ext4_fast_symlink_inode_operations;
			inode->i_link = (अक्षर *)&EXT4_I(inode)->i_data;
		पूर्ण
		स_नकल((अक्षर *)&EXT4_I(inode)->i_data, disk_link.name,
		       disk_link.len);
		inode->i_size = disk_link.len - 1;
	पूर्ण
	EXT4_I(inode)->i_disksize = inode->i_size;
	err = ext4_add_nondir(handle, dentry, &inode);
	अगर (handle)
		ext4_journal_stop(handle);
	अगर (inode)
		iput(inode);
	जाओ out_मुक्त_encrypted_link;

err_drop_inode:
	अगर (handle)
		ext4_journal_stop(handle);
	clear_nlink(inode);
	unlock_new_inode(inode);
	iput(inode);
out_मुक्त_encrypted_link:
	अगर (disk_link.name != (अचिन्हित अक्षर *)symname)
		kमुक्त(disk_link.name);
	वापस err;
पूर्ण

पूर्णांक __ext4_link(काष्ठा inode *dir, काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	handle_t *handle;
	पूर्णांक err, retries = 0;
retry:
	handle = ext4_journal_start(dir, EXT4_HT_सूची,
		(EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
		 EXT4_INDEX_EXTRA_TRANS_BLOCKS) + 1);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	अगर (IS_सूचीSYNC(dir))
		ext4_handle_sync(handle);

	inode->i_स_समय = current_समय(inode);
	ext4_inc_count(inode);
	ihold(inode);

	err = ext4_add_entry(handle, dentry, inode);
	अगर (!err) अणु
		err = ext4_mark_inode_dirty(handle, inode);
		/* this can happen only क्रम क्षणिक_ख being
		 * linked the first समय
		 */
		अगर (inode->i_nlink == 1)
			ext4_orphan_del(handle, inode);
		d_instantiate(dentry, inode);
		ext4_fc_track_link(handle, dentry);
	पूर्ण अन्यथा अणु
		drop_nlink(inode);
		iput(inode);
	पूर्ण
	ext4_journal_stop(handle);
	अगर (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		जाओ retry;
	वापस err;
पूर्ण

अटल पूर्णांक ext4_link(काष्ठा dentry *old_dentry,
		     काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक err;

	अगर (inode->i_nlink >= EXT4_LINK_MAX)
		वापस -EMLINK;

	err = fscrypt_prepare_link(old_dentry, dir, dentry);
	अगर (err)
		वापस err;

	अगर ((ext4_test_inode_flag(dir, EXT4_INODE_PROJINHERIT)) &&
	    (!projid_eq(EXT4_I(dir)->i_projid,
			EXT4_I(old_dentry->d_inode)->i_projid)))
		वापस -EXDEV;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;
	वापस __ext4_link(dir, inode, dentry);
पूर्ण

/*
 * Try to find buffer head where contains the parent block.
 * It should be the inode block अगर it is अंतरभूतd or the 1st block
 * अगर it is a normal dir.
 */
अटल काष्ठा buffer_head *ext4_get_first_dir_block(handle_t *handle,
					काष्ठा inode *inode,
					पूर्णांक *retval,
					काष्ठा ext4_dir_entry_2 **parent_de,
					पूर्णांक *अंतरभूतd)
अणु
	काष्ठा buffer_head *bh;

	अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		/* The first directory block must not be a hole, so
		 * treat it as सूचीENT_HTREE
		 */
		bh = ext4_पढ़ो_dirblock(inode, 0, सूचीENT_HTREE);
		अगर (IS_ERR(bh)) अणु
			*retval = PTR_ERR(bh);
			वापस शून्य;
		पूर्ण
		*parent_de = ext4_next_entry(
					(काष्ठा ext4_dir_entry_2 *)bh->b_data,
					inode->i_sb->s_blocksize);
		वापस bh;
	पूर्ण

	*अंतरभूतd = 1;
	वापस ext4_get_first_अंतरभूत_block(inode, parent_de, retval);
पूर्ण

काष्ठा ext4_नामnt अणु
	काष्ठा inode *dir;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	bool is_dir;
	पूर्णांक dir_nlink_delta;

	/* entry क्रम "dentry" */
	काष्ठा buffer_head *bh;
	काष्ठा ext4_dir_entry_2 *de;
	पूर्णांक अंतरभूतd;

	/* entry क्रम ".." in inode अगर it's a directory */
	काष्ठा buffer_head *dir_bh;
	काष्ठा ext4_dir_entry_2 *parent_de;
	पूर्णांक dir_अंतरभूतd;
पूर्ण;

अटल पूर्णांक ext4_नाम_dir_prepare(handle_t *handle, काष्ठा ext4_नामnt *ent)
अणु
	पूर्णांक retval;

	ent->dir_bh = ext4_get_first_dir_block(handle, ent->inode,
					      &retval, &ent->parent_de,
					      &ent->dir_अंतरभूतd);
	अगर (!ent->dir_bh)
		वापस retval;
	अगर (le32_to_cpu(ent->parent_de->inode) != ent->dir->i_ino)
		वापस -EFSCORRUPTED;
	BUFFER_TRACE(ent->dir_bh, "get_write_access");
	वापस ext4_journal_get_ग_लिखो_access(handle, ent->dir_bh);
पूर्ण

अटल पूर्णांक ext4_नाम_dir_finish(handle_t *handle, काष्ठा ext4_नामnt *ent,
				  अचिन्हित dir_ino)
अणु
	पूर्णांक retval;

	ent->parent_de->inode = cpu_to_le32(dir_ino);
	BUFFER_TRACE(ent->dir_bh, "call ext4_handle_dirty_metadata");
	अगर (!ent->dir_अंतरभूतd) अणु
		अगर (is_dx(ent->inode)) अणु
			retval = ext4_handle_dirty_dx_node(handle,
							   ent->inode,
							   ent->dir_bh);
		पूर्ण अन्यथा अणु
			retval = ext4_handle_dirty_dirblock(handle, ent->inode,
							    ent->dir_bh);
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = ext4_mark_inode_dirty(handle, ent->inode);
	पूर्ण
	अगर (retval) अणु
		ext4_std_error(ent->dir->i_sb, retval);
		वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_setent(handle_t *handle, काष्ठा ext4_नामnt *ent,
		       अचिन्हित ino, अचिन्हित file_type)
अणु
	पूर्णांक retval, retval2;

	BUFFER_TRACE(ent->bh, "get write access");
	retval = ext4_journal_get_ग_लिखो_access(handle, ent->bh);
	अगर (retval)
		वापस retval;
	ent->de->inode = cpu_to_le32(ino);
	अगर (ext4_has_feature_filetype(ent->dir->i_sb))
		ent->de->file_type = file_type;
	inode_inc_iversion(ent->dir);
	ent->dir->i_स_समय = ent->dir->i_mसमय =
		current_समय(ent->dir);
	retval = ext4_mark_inode_dirty(handle, ent->dir);
	BUFFER_TRACE(ent->bh, "call ext4_handle_dirty_metadata");
	अगर (!ent->अंतरभूतd) अणु
		retval2 = ext4_handle_dirty_dirblock(handle, ent->dir, ent->bh);
		अगर (unlikely(retval2)) अणु
			ext4_std_error(ent->dir->i_sb, retval2);
			वापस retval2;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम ext4_resetent(handle_t *handle, काष्ठा ext4_नामnt *ent,
			  अचिन्हित ino, अचिन्हित file_type)
अणु
	काष्ठा ext4_नामnt old = *ent;
	पूर्णांक retval = 0;

	/*
	 * old->de could have moved from under us during make indexed dir,
	 * so the old->de may no दीर्घer valid and need to find it again
	 * beक्रमe reset old inode info.
	 */
	old.bh = ext4_find_entry(old.dir, &old.dentry->d_name, &old.de, शून्य);
	अगर (IS_ERR(old.bh))
		retval = PTR_ERR(old.bh);
	अगर (!old.bh)
		retval = -ENOENT;
	अगर (retval) अणु
		ext4_std_error(old.dir->i_sb, retval);
		वापस;
	पूर्ण

	ext4_setent(handle, &old, ino, file_type);
	brअन्यथा(old.bh);
पूर्ण

अटल पूर्णांक ext4_find_delete_entry(handle_t *handle, काष्ठा inode *dir,
				  स्थिर काष्ठा qstr *d_name)
अणु
	पूर्णांक retval = -ENOENT;
	काष्ठा buffer_head *bh;
	काष्ठा ext4_dir_entry_2 *de;

	bh = ext4_find_entry(dir, d_name, &de, शून्य);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);
	अगर (bh) अणु
		retval = ext4_delete_entry(handle, dir, de, bh);
		brअन्यथा(bh);
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम ext4_नाम_delete(handle_t *handle, काष्ठा ext4_नामnt *ent,
			       पूर्णांक क्रमce_reपढ़ो)
अणु
	पूर्णांक retval;
	/*
	 * ent->de could have moved from under us during htree split, so make
	 * sure that we are deleting the right entry.  We might also be poपूर्णांकing
	 * to a stale entry in the unused part of ent->bh so just checking inum
	 * and the name isn't enough.
	 */
	अगर (le32_to_cpu(ent->de->inode) != ent->inode->i_ino ||
	    ent->de->name_len != ent->dentry->d_name.len ||
	    म_भेदन(ent->de->name, ent->dentry->d_name.name,
		    ent->de->name_len) ||
	    क्रमce_reपढ़ो) अणु
		retval = ext4_find_delete_entry(handle, ent->dir,
						&ent->dentry->d_name);
	पूर्ण अन्यथा अणु
		retval = ext4_delete_entry(handle, ent->dir, ent->de, ent->bh);
		अगर (retval == -ENOENT) अणु
			retval = ext4_find_delete_entry(handle, ent->dir,
							&ent->dentry->d_name);
		पूर्ण
	पूर्ण

	अगर (retval) अणु
		ext4_warning_inode(ent->dir,
				   "Deleting old file: nlink %d, error=%d",
				   ent->dir->i_nlink, retval);
	पूर्ण
पूर्ण

अटल व्योम ext4_update_dir_count(handle_t *handle, काष्ठा ext4_नामnt *ent)
अणु
	अगर (ent->dir_nlink_delta) अणु
		अगर (ent->dir_nlink_delta == -1)
			ext4_dec_count(ent->dir);
		अन्यथा
			ext4_inc_count(ent->dir);
		ext4_mark_inode_dirty(handle, ent->dir);
	पूर्ण
पूर्ण

अटल काष्ठा inode *ext4_whiteout_क्रम_नाम(काष्ठा user_namespace *mnt_userns,
					      काष्ठा ext4_नामnt *ent,
					      पूर्णांक credits, handle_t **h)
अणु
	काष्ठा inode *wh;
	handle_t *handle;
	पूर्णांक retries = 0;

	/*
	 * क्रम inode block, sb block, group summaries,
	 * and inode biपंचांगap
	 */
	credits += (EXT4_MAXQUOTAS_TRANS_BLOCKS(ent->dir->i_sb) +
		    EXT4_XATTR_TRANS_BLOCKS + 4);
retry:
	wh = ext4_new_inode_start_handle(mnt_userns, ent->dir,
					 S_IFCHR | WHITEOUT_MODE,
					 &ent->dentry->d_name, 0, शून्य,
					 EXT4_HT_सूची, credits);

	handle = ext4_journal_current_handle();
	अगर (IS_ERR(wh)) अणु
		अगर (handle)
			ext4_journal_stop(handle);
		अगर (PTR_ERR(wh) == -ENOSPC &&
		    ext4_should_retry_alloc(ent->dir->i_sb, &retries))
			जाओ retry;
	पूर्ण अन्यथा अणु
		*h = handle;
		init_special_inode(wh, wh->i_mode, WHITEOUT_DEV);
		wh->i_op = &ext4_special_inode_operations;
	पूर्ण
	वापस wh;
पूर्ण

/*
 * Anybody can नाम anything with this: the permission checks are left to the
 * higher-level routines.
 *
 * n.b.  old_अणुdentry,inode) refers to the source dentry/inode
 * जबतक new_अणुdentry,inode) refers to the destination dentry/inode
 * This comes from नाम(स्थिर अक्षर *oldpath, स्थिर अक्षर *newpath)
 */
अटल पूर्णांक ext4_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	handle_t *handle = शून्य;
	काष्ठा ext4_नामnt old = अणु
		.dir = old_dir,
		.dentry = old_dentry,
		.inode = d_inode(old_dentry),
	पूर्ण;
	काष्ठा ext4_नामnt new = अणु
		.dir = new_dir,
		.dentry = new_dentry,
		.inode = d_inode(new_dentry),
	पूर्ण;
	पूर्णांक क्रमce_reपढ़ो;
	पूर्णांक retval;
	काष्ठा inode *whiteout = शून्य;
	पूर्णांक credits;
	u8 old_file_type;

	अगर (new.inode && new.inode->i_nlink == 0) अणु
		EXT4_ERROR_INODE(new.inode,
				 "target of rename is already freed");
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर ((ext4_test_inode_flag(new_dir, EXT4_INODE_PROJINHERIT)) &&
	    (!projid_eq(EXT4_I(new_dir)->i_projid,
			EXT4_I(old_dentry->d_inode)->i_projid)))
		वापस -EXDEV;

	retval = dquot_initialize(old.dir);
	अगर (retval)
		वापस retval;
	retval = dquot_initialize(new.dir);
	अगर (retval)
		वापस retval;

	/* Initialize quotas beक्रमe so that eventual ग_लिखोs go
	 * in separate transaction */
	अगर (new.inode) अणु
		retval = dquot_initialize(new.inode);
		अगर (retval)
			वापस retval;
	पूर्ण

	old.bh = ext4_find_entry(old.dir, &old.dentry->d_name, &old.de, शून्य);
	अगर (IS_ERR(old.bh))
		वापस PTR_ERR(old.bh);
	/*
	 *  Check क्रम inode number is _not_ due to possible IO errors.
	 *  We might सूची_हटाओ the source, keep it as pwd of some process
	 *  and merrily समाप्त the link to whatever was created under the
	 *  same name. Goodbye sticky bit ;-<
	 */
	retval = -ENOENT;
	अगर (!old.bh || le32_to_cpu(old.de->inode) != old.inode->i_ino)
		जाओ release_bh;

	new.bh = ext4_find_entry(new.dir, &new.dentry->d_name,
				 &new.de, &new.अंतरभूतd);
	अगर (IS_ERR(new.bh)) अणु
		retval = PTR_ERR(new.bh);
		new.bh = शून्य;
		जाओ release_bh;
	पूर्ण
	अगर (new.bh) अणु
		अगर (!new.inode) अणु
			brअन्यथा(new.bh);
			new.bh = शून्य;
		पूर्ण
	पूर्ण
	अगर (new.inode && !test_opt(new.dir->i_sb, NO_AUTO_DA_ALLOC))
		ext4_alloc_da_blocks(old.inode);

	credits = (2 * EXT4_DATA_TRANS_BLOCKS(old.dir->i_sb) +
		   EXT4_INDEX_EXTRA_TRANS_BLOCKS + 2);
	अगर (!(flags & RENAME_WHITEOUT)) अणु
		handle = ext4_journal_start(old.dir, EXT4_HT_सूची, credits);
		अगर (IS_ERR(handle)) अणु
			retval = PTR_ERR(handle);
			जाओ release_bh;
		पूर्ण
	पूर्ण अन्यथा अणु
		whiteout = ext4_whiteout_क्रम_नाम(mnt_userns, &old, credits, &handle);
		अगर (IS_ERR(whiteout)) अणु
			retval = PTR_ERR(whiteout);
			जाओ release_bh;
		पूर्ण
	पूर्ण

	old_file_type = old.de->file_type;
	अगर (IS_सूचीSYNC(old.dir) || IS_सूचीSYNC(new.dir))
		ext4_handle_sync(handle);

	अगर (S_ISसूची(old.inode->i_mode)) अणु
		अगर (new.inode) अणु
			retval = -ENOTEMPTY;
			अगर (!ext4_empty_dir(new.inode))
				जाओ end_नाम;
		पूर्ण अन्यथा अणु
			retval = -EMLINK;
			अगर (new.dir != old.dir && EXT4_सूची_LINK_MAX(new.dir))
				जाओ end_नाम;
		पूर्ण
		retval = ext4_नाम_dir_prepare(handle, &old);
		अगर (retval)
			जाओ end_नाम;
	पूर्ण
	/*
	 * If we're renaming a file within an अंतरभूत_data dir and adding or
	 * setting the new dirent causes a conversion from अंतरभूत_data to
	 * extents/blockmap, we need to क्रमce the dirent delete code to
	 * re-पढ़ो the directory, or अन्यथा we end up trying to delete a dirent
	 * from what is now the extent tree root (or a block map).
	 */
	क्रमce_reपढ़ो = (new.dir->i_ino == old.dir->i_ino &&
			ext4_test_inode_flag(new.dir, EXT4_INODE_INLINE_DATA));

	अगर (whiteout) अणु
		/*
		 * Do this beक्रमe adding a new entry, so the old entry is sure
		 * to be still poपूर्णांकing to the valid old entry.
		 */
		retval = ext4_setent(handle, &old, whiteout->i_ino,
				     EXT4_FT_CHRDEV);
		अगर (retval)
			जाओ end_नाम;
		retval = ext4_mark_inode_dirty(handle, whiteout);
		अगर (unlikely(retval))
			जाओ end_नाम;

	पूर्ण
	अगर (!new.bh) अणु
		retval = ext4_add_entry(handle, new.dentry, old.inode);
		अगर (retval)
			जाओ end_नाम;
	पूर्ण अन्यथा अणु
		retval = ext4_setent(handle, &new,
				     old.inode->i_ino, old_file_type);
		अगर (retval)
			जाओ end_नाम;
	पूर्ण
	अगर (क्रमce_reपढ़ो)
		क्रमce_reपढ़ो = !ext4_test_inode_flag(new.dir,
						     EXT4_INODE_INLINE_DATA);

	/*
	 * Like most other Unix प्रणालीs, set the स_समय क्रम inodes on a
	 * नाम.
	 */
	old.inode->i_स_समय = current_समय(old.inode);
	retval = ext4_mark_inode_dirty(handle, old.inode);
	अगर (unlikely(retval))
		जाओ end_नाम;

	अगर (!whiteout) अणु
		/*
		 * ok, that's it
		 */
		ext4_नाम_delete(handle, &old, क्रमce_reपढ़ो);
	पूर्ण

	अगर (new.inode) अणु
		ext4_dec_count(new.inode);
		new.inode->i_स_समय = current_समय(new.inode);
	पूर्ण
	old.dir->i_स_समय = old.dir->i_mसमय = current_समय(old.dir);
	ext4_update_dx_flag(old.dir);
	अगर (old.dir_bh) अणु
		retval = ext4_नाम_dir_finish(handle, &old, new.dir->i_ino);
		अगर (retval)
			जाओ end_नाम;

		ext4_dec_count(old.dir);
		अगर (new.inode) अणु
			/* checked ext4_empty_dir above, can't have another
			 * parent, ext4_dec_count() won't work क्रम many-linked
			 * dirs */
			clear_nlink(new.inode);
		पूर्ण अन्यथा अणु
			ext4_inc_count(new.dir);
			ext4_update_dx_flag(new.dir);
			retval = ext4_mark_inode_dirty(handle, new.dir);
			अगर (unlikely(retval))
				जाओ end_नाम;
		पूर्ण
	पूर्ण
	retval = ext4_mark_inode_dirty(handle, old.dir);
	अगर (unlikely(retval))
		जाओ end_नाम;

	अगर (S_ISसूची(old.inode->i_mode)) अणु
		/*
		 * We disable fast commits here that's because the
		 * replay code is not yet capable of changing करोt करोt
		 * dirents in directories.
		 */
		ext4_fc_mark_ineligible(old.inode->i_sb,
			EXT4_FC_REASON_RENAME_सूची);
	पूर्ण अन्यथा अणु
		अगर (new.inode)
			ext4_fc_track_unlink(handle, new.dentry);
		__ext4_fc_track_link(handle, old.inode, new.dentry);
		__ext4_fc_track_unlink(handle, old.inode, old.dentry);
		अगर (whiteout)
			__ext4_fc_track_create(handle, whiteout, old.dentry);
	पूर्ण

	अगर (new.inode) अणु
		retval = ext4_mark_inode_dirty(handle, new.inode);
		अगर (unlikely(retval))
			जाओ end_नाम;
		अगर (!new.inode->i_nlink)
			ext4_orphan_add(handle, new.inode);
	पूर्ण
	retval = 0;

end_नाम:
	अगर (whiteout) अणु
		अगर (retval) अणु
			ext4_resetent(handle, &old,
				      old.inode->i_ino, old_file_type);
			drop_nlink(whiteout);
			ext4_orphan_add(handle, whiteout);
		पूर्ण
		unlock_new_inode(whiteout);
		ext4_journal_stop(handle);
		iput(whiteout);
	पूर्ण अन्यथा अणु
		ext4_journal_stop(handle);
	पूर्ण
release_bh:
	brअन्यथा(old.dir_bh);
	brअन्यथा(old.bh);
	brअन्यथा(new.bh);
	वापस retval;
पूर्ण

अटल पूर्णांक ext4_cross_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry)
अणु
	handle_t *handle = शून्य;
	काष्ठा ext4_नामnt old = अणु
		.dir = old_dir,
		.dentry = old_dentry,
		.inode = d_inode(old_dentry),
	पूर्ण;
	काष्ठा ext4_नामnt new = अणु
		.dir = new_dir,
		.dentry = new_dentry,
		.inode = d_inode(new_dentry),
	पूर्ण;
	u8 new_file_type;
	पूर्णांक retval;
	काष्ठा बारpec64 स_समय;

	अगर ((ext4_test_inode_flag(new_dir, EXT4_INODE_PROJINHERIT) &&
	     !projid_eq(EXT4_I(new_dir)->i_projid,
			EXT4_I(old_dentry->d_inode)->i_projid)) ||
	    (ext4_test_inode_flag(old_dir, EXT4_INODE_PROJINHERIT) &&
	     !projid_eq(EXT4_I(old_dir)->i_projid,
			EXT4_I(new_dentry->d_inode)->i_projid)))
		वापस -EXDEV;

	retval = dquot_initialize(old.dir);
	अगर (retval)
		वापस retval;
	retval = dquot_initialize(new.dir);
	अगर (retval)
		वापस retval;

	old.bh = ext4_find_entry(old.dir, &old.dentry->d_name,
				 &old.de, &old.अंतरभूतd);
	अगर (IS_ERR(old.bh))
		वापस PTR_ERR(old.bh);
	/*
	 *  Check क्रम inode number is _not_ due to possible IO errors.
	 *  We might सूची_हटाओ the source, keep it as pwd of some process
	 *  and merrily समाप्त the link to whatever was created under the
	 *  same name. Goodbye sticky bit ;-<
	 */
	retval = -ENOENT;
	अगर (!old.bh || le32_to_cpu(old.de->inode) != old.inode->i_ino)
		जाओ end_नाम;

	new.bh = ext4_find_entry(new.dir, &new.dentry->d_name,
				 &new.de, &new.अंतरभूतd);
	अगर (IS_ERR(new.bh)) अणु
		retval = PTR_ERR(new.bh);
		new.bh = शून्य;
		जाओ end_नाम;
	पूर्ण

	/* RENAME_EXCHANGE हाल: old *and* new must both exist */
	अगर (!new.bh || le32_to_cpu(new.de->inode) != new.inode->i_ino)
		जाओ end_नाम;

	handle = ext4_journal_start(old.dir, EXT4_HT_सूची,
		(2 * EXT4_DATA_TRANS_BLOCKS(old.dir->i_sb) +
		 2 * EXT4_INDEX_EXTRA_TRANS_BLOCKS + 2));
	अगर (IS_ERR(handle)) अणु
		retval = PTR_ERR(handle);
		handle = शून्य;
		जाओ end_नाम;
	पूर्ण

	अगर (IS_सूचीSYNC(old.dir) || IS_सूचीSYNC(new.dir))
		ext4_handle_sync(handle);

	अगर (S_ISसूची(old.inode->i_mode)) अणु
		old.is_dir = true;
		retval = ext4_नाम_dir_prepare(handle, &old);
		अगर (retval)
			जाओ end_नाम;
	पूर्ण
	अगर (S_ISसूची(new.inode->i_mode)) अणु
		new.is_dir = true;
		retval = ext4_नाम_dir_prepare(handle, &new);
		अगर (retval)
			जाओ end_नाम;
	पूर्ण

	/*
	 * Other than the special हाल of overwriting a directory, parents'
	 * nlink only needs to be modअगरied अगर this is a cross directory नाम.
	 */
	अगर (old.dir != new.dir && old.is_dir != new.is_dir) अणु
		old.dir_nlink_delta = old.is_dir ? -1 : 1;
		new.dir_nlink_delta = -old.dir_nlink_delta;
		retval = -EMLINK;
		अगर ((old.dir_nlink_delta > 0 && EXT4_सूची_LINK_MAX(old.dir)) ||
		    (new.dir_nlink_delta > 0 && EXT4_सूची_LINK_MAX(new.dir)))
			जाओ end_नाम;
	पूर्ण

	new_file_type = new.de->file_type;
	retval = ext4_setent(handle, &new, old.inode->i_ino, old.de->file_type);
	अगर (retval)
		जाओ end_नाम;

	retval = ext4_setent(handle, &old, new.inode->i_ino, new_file_type);
	अगर (retval)
		जाओ end_नाम;

	/*
	 * Like most other Unix प्रणालीs, set the स_समय क्रम inodes on a
	 * नाम.
	 */
	स_समय = current_समय(old.inode);
	old.inode->i_स_समय = स_समय;
	new.inode->i_स_समय = स_समय;
	retval = ext4_mark_inode_dirty(handle, old.inode);
	अगर (unlikely(retval))
		जाओ end_नाम;
	retval = ext4_mark_inode_dirty(handle, new.inode);
	अगर (unlikely(retval))
		जाओ end_नाम;
	ext4_fc_mark_ineligible(new.inode->i_sb,
				EXT4_FC_REASON_CROSS_RENAME);
	अगर (old.dir_bh) अणु
		retval = ext4_नाम_dir_finish(handle, &old, new.dir->i_ino);
		अगर (retval)
			जाओ end_नाम;
	पूर्ण
	अगर (new.dir_bh) अणु
		retval = ext4_नाम_dir_finish(handle, &new, old.dir->i_ino);
		अगर (retval)
			जाओ end_नाम;
	पूर्ण
	ext4_update_dir_count(handle, &old);
	ext4_update_dir_count(handle, &new);
	retval = 0;

end_नाम:
	brअन्यथा(old.dir_bh);
	brअन्यथा(new.dir_bh);
	brअन्यथा(old.bh);
	brअन्यथा(new.bh);
	अगर (handle)
		ext4_journal_stop(handle);
	वापस retval;
पूर्ण

अटल पूर्णांक ext4_नाम2(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(old_dir->i_sb))))
		वापस -EIO;

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		वापस -EINVAL;

	err = fscrypt_prepare_नाम(old_dir, old_dentry, new_dir, new_dentry,
				     flags);
	अगर (err)
		वापस err;

	अगर (flags & RENAME_EXCHANGE) अणु
		वापस ext4_cross_नाम(old_dir, old_dentry,
					 new_dir, new_dentry);
	पूर्ण

	वापस ext4_नाम(mnt_userns, old_dir, old_dentry, new_dir, new_dentry, flags);
पूर्ण

/*
 * directories can handle most operations...
 */
स्थिर काष्ठा inode_operations ext4_dir_inode_operations = अणु
	.create		= ext4_create,
	.lookup		= ext4_lookup,
	.link		= ext4_link,
	.unlink		= ext4_unlink,
	.symlink	= ext4_symlink,
	.सूची_गढ़ो		= ext4_सूची_गढ़ो,
	.सूची_हटाओ		= ext4_सूची_हटाओ,
	.mknod		= ext4_mknod,
	.क्षणिक_ख	= ext4_क्षणिक_ख,
	.नाम		= ext4_नाम2,
	.setattr	= ext4_setattr,
	.getattr	= ext4_getattr,
	.listxattr	= ext4_listxattr,
	.get_acl	= ext4_get_acl,
	.set_acl	= ext4_set_acl,
	.fiemap         = ext4_fiemap,
	.fileattr_get	= ext4_fileattr_get,
	.fileattr_set	= ext4_fileattr_set,
पूर्ण;

स्थिर काष्ठा inode_operations ext4_special_inode_operations = अणु
	.setattr	= ext4_setattr,
	.getattr	= ext4_getattr,
	.listxattr	= ext4_listxattr,
	.get_acl	= ext4_get_acl,
	.set_acl	= ext4_set_acl,
पूर्ण;
