<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext4/truncate.h
 *
 * Common अंतरभूत functions needed क्रम truncate support
 */

/*
 * Truncate blocks that were not used by ग_लिखो. We have to truncate the
 * pagecache as well so that corresponding buffers get properly unmapped.
 */
अटल अंतरभूत व्योम ext4_truncate_failed_ग_लिखो(काष्ठा inode *inode)
अणु
	/*
	 * We करोn't need to call ext4_अवरोध_layouts() because the blocks we
	 * are truncating were never visible to userspace.
	 */
	करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
	truncate_inode_pages(inode->i_mapping, inode->i_size);
	ext4_truncate(inode);
	up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
पूर्ण

/*
 * Work out how many blocks we need to proceed with the next chunk of a
 * truncate transaction.
 */
अटल अंतरभूत अचिन्हित दीर्घ ext4_blocks_क्रम_truncate(काष्ठा inode *inode)
अणु
	ext4_lblk_t needed;

	needed = inode->i_blocks >> (inode->i_sb->s_blocksize_bits - 9);

	/* Give ourselves just enough room to cope with inodes in which
	 * i_blocks is corrupt: we've seen disk corruptions in the past
	 * which resulted in अक्रमom data in an inode which looked enough
	 * like a regular file क्रम ext4 to try to delete it.  Things
	 * will go a bit crazy अगर that happens, but at least we should
	 * try not to panic the whole kernel. */
	अगर (needed < 2)
		needed = 2;

	/* But we need to bound the transaction so we करोn't overflow the
	 * journal. */
	अगर (needed > EXT4_MAX_TRANS_DATA)
		needed = EXT4_MAX_TRANS_DATA;

	वापस EXT4_DATA_TRANS_BLOCKS(inode->i_sb) + needed;
पूर्ण

