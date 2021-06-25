<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/super.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/parser.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/log2.h>
#समावेश <linux/crc16.h>
#समावेश <linux/dax.h>
#समावेश <linux/cleancache.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/iversion.h>
#समावेश <linux/unicode.h>
#समावेश <linux/part_स्थिति.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>

#समावेश "ext4.h"
#समावेश "ext4_extents.h"	/* Needed क्रम trace poपूर्णांकs definition */
#समावेश "ext4_jbd2.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "mballoc.h"
#समावेश "fsmap.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/ext4.h>

अटल काष्ठा ext4_lazy_init *ext4_li_info;
अटल DEFINE_MUTEX(ext4_li_mtx);
अटल काष्ठा ratelimit_state ext4_mount_msg_ratelimit;

अटल पूर्णांक ext4_load_journal(काष्ठा super_block *, काष्ठा ext4_super_block *,
			     अचिन्हित दीर्घ journal_devnum);
अटल पूर्णांक ext4_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root);
अटल व्योम ext4_update_super(काष्ठा super_block *sb);
अटल पूर्णांक ext4_commit_super(काष्ठा super_block *sb);
अटल पूर्णांक ext4_mark_recovery_complete(काष्ठा super_block *sb,
					काष्ठा ext4_super_block *es);
अटल पूर्णांक ext4_clear_journal_err(काष्ठा super_block *sb,
				  काष्ठा ext4_super_block *es);
अटल पूर्णांक ext4_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको);
अटल पूर्णांक ext4_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data);
अटल पूर्णांक ext4_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);
अटल पूर्णांक ext4_unमुक्तze(काष्ठा super_block *sb);
अटल पूर्णांक ext4_मुक्तze(काष्ठा super_block *sb);
अटल काष्ठा dentry *ext4_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
		       स्थिर अक्षर *dev_name, व्योम *data);
अटल अंतरभूत पूर्णांक ext2_feature_set_ok(काष्ठा super_block *sb);
अटल अंतरभूत पूर्णांक ext3_feature_set_ok(काष्ठा super_block *sb);
अटल पूर्णांक ext4_feature_set_ok(काष्ठा super_block *sb, पूर्णांक पढ़ोonly);
अटल व्योम ext4_destroy_lazyinit_thपढ़ो(व्योम);
अटल व्योम ext4_unरेजिस्टर_li_request(काष्ठा super_block *sb);
अटल व्योम ext4_clear_request_list(व्योम);
अटल काष्ठा inode *ext4_get_journal_inode(काष्ठा super_block *sb,
					    अचिन्हित पूर्णांक journal_inum);

/*
 * Lock ordering
 *
 * Note the dअगरference between i_mmap_sem (EXT4_I(inode)->i_mmap_sem) and
 * i_mmap_rwsem (inode->i_mmap_rwsem)!
 *
 * page fault path:
 * mmap_lock -> sb_start_pagefault -> i_mmap_sem (r) -> transaction start ->
 *   page lock -> i_data_sem (rw)
 *
 * buffered ग_लिखो path:
 * sb_start_ग_लिखो -> i_mutex -> mmap_lock
 * sb_start_ग_लिखो -> i_mutex -> transaction start -> page lock ->
 *   i_data_sem (rw)
 *
 * truncate:
 * sb_start_ग_लिखो -> i_mutex -> i_mmap_sem (w) -> i_mmap_rwsem (w) -> page lock
 * sb_start_ग_लिखो -> i_mutex -> i_mmap_sem (w) -> transaction start ->
 *   i_data_sem (rw)
 *
 * direct IO:
 * sb_start_ग_लिखो -> i_mutex -> mmap_lock
 * sb_start_ग_लिखो -> i_mutex -> transaction start -> i_data_sem (rw)
 *
 * ग_लिखोpages:
 * transaction start -> page lock(s) -> i_data_sem (rw)
 */

#अगर !defined(CONFIG_EXT2_FS) && !defined(CONFIG_EXT2_FS_MODULE) && defined(CONFIG_EXT4_USE_FOR_EXT2)
अटल काष्ठा file_प्रणाली_type ext2_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ext2",
	.mount		= ext4_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("ext2");
MODULE_ALIAS("ext2");
#घोषणा IS_EXT2_SB(sb) ((sb)->s_bdev->bd_holder == &ext2_fs_type)
#अन्यथा
#घोषणा IS_EXT2_SB(sb) (0)
#पूर्ण_अगर


अटल काष्ठा file_प्रणाली_type ext3_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ext3",
	.mount		= ext4_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("ext3");
MODULE_ALIAS("ext3");
#घोषणा IS_EXT3_SB(sb) ((sb)->s_bdev->bd_holder == &ext3_fs_type)


अटल अंतरभूत व्योम __ext4_पढ़ो_bh(काष्ठा buffer_head *bh, पूर्णांक op_flags,
				  bh_end_io_t *end_io)
अणु
	/*
	 * buffer's verअगरied bit is no दीर्घer valid after पढ़ोing from
	 * disk again due to ग_लिखो out error, clear it to make sure we
	 * recheck the buffer contents.
	 */
	clear_buffer_verअगरied(bh);

	bh->b_end_io = end_io ? end_io : end_buffer_पढ़ो_sync;
	get_bh(bh);
	submit_bh(REQ_OP_READ, op_flags, bh);
पूर्ण

व्योम ext4_पढ़ो_bh_noरुको(काष्ठा buffer_head *bh, पूर्णांक op_flags,
			 bh_end_io_t *end_io)
अणु
	BUG_ON(!buffer_locked(bh));

	अगर (ext4_buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		वापस;
	पूर्ण
	__ext4_पढ़ो_bh(bh, op_flags, end_io);
पूर्ण

पूर्णांक ext4_पढ़ो_bh(काष्ठा buffer_head *bh, पूर्णांक op_flags, bh_end_io_t *end_io)
अणु
	BUG_ON(!buffer_locked(bh));

	अगर (ext4_buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		वापस 0;
	पूर्ण

	__ext4_पढ़ो_bh(bh, op_flags, end_io);

	रुको_on_buffer(bh);
	अगर (buffer_uptodate(bh))
		वापस 0;
	वापस -EIO;
पूर्ण

पूर्णांक ext4_पढ़ो_bh_lock(काष्ठा buffer_head *bh, पूर्णांक op_flags, bool रुको)
अणु
	अगर (trylock_buffer(bh)) अणु
		अगर (रुको)
			वापस ext4_पढ़ो_bh(bh, op_flags, शून्य);
		ext4_पढ़ो_bh_noरुको(bh, op_flags, शून्य);
		वापस 0;
	पूर्ण
	अगर (रुको) अणु
		रुको_on_buffer(bh);
		अगर (buffer_uptodate(bh))
			वापस 0;
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This works like __bपढ़ो_gfp() except it uses ERR_PTR क्रम error
 * वापसs.  Currently with sb_bपढ़ो it's impossible to distinguish
 * between ENOMEM and EIO situations (since both result in a शून्य
 * वापस.
 */
अटल काष्ठा buffer_head *__ext4_sb_bपढ़ो_gfp(काष्ठा super_block *sb,
					       sector_t block, पूर्णांक op_flags,
					       gfp_t gfp)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक ret;

	bh = sb_getblk_gfp(sb, block, gfp);
	अगर (bh == शून्य)
		वापस ERR_PTR(-ENOMEM);
	अगर (ext4_buffer_uptodate(bh))
		वापस bh;

	ret = ext4_पढ़ो_bh_lock(bh, REQ_META | op_flags, true);
	अगर (ret) अणु
		put_bh(bh);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस bh;
पूर्ण

काष्ठा buffer_head *ext4_sb_bपढ़ो(काष्ठा super_block *sb, sector_t block,
				   पूर्णांक op_flags)
अणु
	वापस __ext4_sb_bपढ़ो_gfp(sb, block, op_flags, __GFP_MOVABLE);
पूर्ण

काष्ठा buffer_head *ext4_sb_bपढ़ो_unmovable(काष्ठा super_block *sb,
					    sector_t block)
अणु
	वापस __ext4_sb_bपढ़ो_gfp(sb, block, 0, 0);
पूर्ण

व्योम ext4_sb_bपढ़ोahead_unmovable(काष्ठा super_block *sb, sector_t block)
अणु
	काष्ठा buffer_head *bh = sb_getblk_gfp(sb, block, 0);

	अगर (likely(bh)) अणु
		ext4_पढ़ो_bh_lock(bh, REQ_RAHEAD, false);
		brअन्यथा(bh);
	पूर्ण
पूर्ण

अटल पूर्णांक ext4_verअगरy_csum_type(काष्ठा super_block *sb,
				 काष्ठा ext4_super_block *es)
अणु
	अगर (!ext4_has_feature_metadata_csum(sb))
		वापस 1;

	वापस es->s_checksum_type == EXT4_CRC32C_CHKSUM;
पूर्ण

अटल __le32 ext4_superblock_csum(काष्ठा super_block *sb,
				   काष्ठा ext4_super_block *es)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक offset = दुरत्व(काष्ठा ext4_super_block, s_checksum);
	__u32 csum;

	csum = ext4_chksum(sbi, ~0, (अक्षर *)es, offset);

	वापस cpu_to_le32(csum);
पूर्ण

अटल पूर्णांक ext4_superblock_csum_verअगरy(काष्ठा super_block *sb,
				       काष्ठा ext4_super_block *es)
अणु
	अगर (!ext4_has_metadata_csum(sb))
		वापस 1;

	वापस es->s_checksum == ext4_superblock_csum(sb, es);
पूर्ण

व्योम ext4_superblock_csum_set(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;

	अगर (!ext4_has_metadata_csum(sb))
		वापस;

	es->s_checksum = ext4_superblock_csum(sb, es);
पूर्ण

ext4_fsblk_t ext4_block_biपंचांगap(काष्ठा super_block *sb,
			       काष्ठा ext4_group_desc *bg)
अणु
	वापस le32_to_cpu(bg->bg_block_biपंचांगap_lo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (ext4_fsblk_t)le32_to_cpu(bg->bg_block_biपंचांगap_hi) << 32 : 0);
पूर्ण

ext4_fsblk_t ext4_inode_biपंचांगap(काष्ठा super_block *sb,
			       काष्ठा ext4_group_desc *bg)
अणु
	वापस le32_to_cpu(bg->bg_inode_biपंचांगap_lo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (ext4_fsblk_t)le32_to_cpu(bg->bg_inode_biपंचांगap_hi) << 32 : 0);
पूर्ण

ext4_fsblk_t ext4_inode_table(काष्ठा super_block *sb,
			      काष्ठा ext4_group_desc *bg)
अणु
	वापस le32_to_cpu(bg->bg_inode_table_lo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (ext4_fsblk_t)le32_to_cpu(bg->bg_inode_table_hi) << 32 : 0);
पूर्ण

__u32 ext4_मुक्त_group_clusters(काष्ठा super_block *sb,
			       काष्ठा ext4_group_desc *bg)
अणु
	वापस le16_to_cpu(bg->bg_मुक्त_blocks_count_lo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_मुक्त_blocks_count_hi) << 16 : 0);
पूर्ण

__u32 ext4_मुक्त_inodes_count(काष्ठा super_block *sb,
			      काष्ठा ext4_group_desc *bg)
अणु
	वापस le16_to_cpu(bg->bg_मुक्त_inodes_count_lo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_मुक्त_inodes_count_hi) << 16 : 0);
पूर्ण

__u32 ext4_used_dirs_count(काष्ठा super_block *sb,
			      काष्ठा ext4_group_desc *bg)
अणु
	वापस le16_to_cpu(bg->bg_used_dirs_count_lo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_used_dirs_count_hi) << 16 : 0);
पूर्ण

__u32 ext4_itable_unused_count(काष्ठा super_block *sb,
			      काष्ठा ext4_group_desc *bg)
अणु
	वापस le16_to_cpu(bg->bg_itable_unused_lo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_itable_unused_hi) << 16 : 0);
पूर्ण

व्योम ext4_block_biपंचांगap_set(काष्ठा super_block *sb,
			   काष्ठा ext4_group_desc *bg, ext4_fsblk_t blk)
अणु
	bg->bg_block_biपंचांगap_lo = cpu_to_le32((u32)blk);
	अगर (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_block_biपंचांगap_hi = cpu_to_le32(blk >> 32);
पूर्ण

व्योम ext4_inode_biपंचांगap_set(काष्ठा super_block *sb,
			   काष्ठा ext4_group_desc *bg, ext4_fsblk_t blk)
अणु
	bg->bg_inode_biपंचांगap_lo  = cpu_to_le32((u32)blk);
	अगर (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_inode_biपंचांगap_hi = cpu_to_le32(blk >> 32);
पूर्ण

व्योम ext4_inode_table_set(काष्ठा super_block *sb,
			  काष्ठा ext4_group_desc *bg, ext4_fsblk_t blk)
अणु
	bg->bg_inode_table_lo = cpu_to_le32((u32)blk);
	अगर (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_inode_table_hi = cpu_to_le32(blk >> 32);
पूर्ण

व्योम ext4_मुक्त_group_clusters_set(काष्ठा super_block *sb,
				  काष्ठा ext4_group_desc *bg, __u32 count)
अणु
	bg->bg_मुक्त_blocks_count_lo = cpu_to_le16((__u16)count);
	अगर (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_मुक्त_blocks_count_hi = cpu_to_le16(count >> 16);
पूर्ण

व्योम ext4_मुक्त_inodes_set(काष्ठा super_block *sb,
			  काष्ठा ext4_group_desc *bg, __u32 count)
अणु
	bg->bg_मुक्त_inodes_count_lo = cpu_to_le16((__u16)count);
	अगर (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_मुक्त_inodes_count_hi = cpu_to_le16(count >> 16);
पूर्ण

व्योम ext4_used_dirs_set(काष्ठा super_block *sb,
			  काष्ठा ext4_group_desc *bg, __u32 count)
अणु
	bg->bg_used_dirs_count_lo = cpu_to_le16((__u16)count);
	अगर (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_used_dirs_count_hi = cpu_to_le16(count >> 16);
पूर्ण

व्योम ext4_itable_unused_set(काष्ठा super_block *sb,
			  काष्ठा ext4_group_desc *bg, __u32 count)
अणु
	bg->bg_itable_unused_lo = cpu_to_le16((__u16)count);
	अगर (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_itable_unused_hi = cpu_to_le16(count >> 16);
पूर्ण

अटल व्योम __ext4_update_tstamp(__le32 *lo, __u8 *hi, समय64_t now)
अणु
	now = clamp_val(now, 0, (1ull << 40) - 1);

	*lo = cpu_to_le32(lower_32_bits(now));
	*hi = upper_32_bits(now);
पूर्ण

अटल समय64_t __ext4_get_tstamp(__le32 *lo, __u8 *hi)
अणु
	वापस ((समय64_t)(*hi) << 32) + le32_to_cpu(*lo);
पूर्ण
#घोषणा ext4_update_tstamp(es, tstamp) \
	__ext4_update_tstamp(&(es)->tstamp, &(es)->tstamp ## _hi, \
			     kसमय_get_real_seconds())
#घोषणा ext4_get_tstamp(es, tstamp) \
	__ext4_get_tstamp(&(es)->tstamp, &(es)->tstamp ## _hi)

/*
 * The del_gendisk() function uninitializes the disk-specअगरic data
 * काष्ठाures, including the bdi काष्ठाure, without telling anyone
 * अन्यथा.  Once this happens, any attempt to call mark_buffer_dirty()
 * (क्रम example, by ext4_commit_super), will cause a kernel OOPS.
 * This is a kludge to prevent these oops until we can put in a proper
 * hook in del_gendisk() to inक्रमm the VFS and file प्रणाली layers.
 */
अटल पूर्णांक block_device_ejected(काष्ठा super_block *sb)
अणु
	काष्ठा inode *bd_inode = sb->s_bdev->bd_inode;
	काष्ठा backing_dev_info *bdi = inode_to_bdi(bd_inode);

	वापस bdi->dev == शून्य;
पूर्ण

अटल व्योम ext4_journal_commit_callback(journal_t *journal, transaction_t *txn)
अणु
	काष्ठा super_block		*sb = journal->j_निजी;
	काष्ठा ext4_sb_info		*sbi = EXT4_SB(sb);
	पूर्णांक				error = is_journal_पातed(journal);
	काष्ठा ext4_journal_cb_entry	*jce;

	BUG_ON(txn->t_state == T_FINISHED);

	ext4_process_मुक्तd_data(sb, txn->t_tid);

	spin_lock(&sbi->s_md_lock);
	जबतक (!list_empty(&txn->t_निजी_list)) अणु
		jce = list_entry(txn->t_निजी_list.next,
				 काष्ठा ext4_journal_cb_entry, jce_list);
		list_del_init(&jce->jce_list);
		spin_unlock(&sbi->s_md_lock);
		jce->jce_func(sb, jce, error);
		spin_lock(&sbi->s_md_lock);
	पूर्ण
	spin_unlock(&sbi->s_md_lock);
पूर्ण

/*
 * This ग_लिखोpage callback क्रम ग_लिखो_cache_pages()
 * takes care of a few हालs after page cleaning.
 *
 * ग_लिखो_cache_pages() alपढ़ोy checks क्रम dirty pages
 * and calls clear_page_dirty_क्रम_io(), which we want,
 * to ग_लिखो protect the pages.
 *
 * However, we may have to redirty a page (see below.)
 */
अटल पूर्णांक ext4_journalled_ग_लिखोpage_callback(काष्ठा page *page,
					      काष्ठा ग_लिखोback_control *wbc,
					      व्योम *data)
अणु
	transaction_t *transaction = (transaction_t *) data;
	काष्ठा buffer_head *bh, *head;
	काष्ठा journal_head *jh;

	bh = head = page_buffers(page);
	करो अणु
		/*
		 * We have to redirty a page in these हालs:
		 * 1) If buffer is dirty, it means the page was dirty because it
		 * contains a buffer that needs checkpoपूर्णांकing. So the dirty bit
		 * needs to be preserved so that checkpoपूर्णांकing ग_लिखोs the buffer
		 * properly.
		 * 2) If buffer is not part of the committing transaction
		 * (we may have just accidentally come across this buffer because
		 * inode range tracking is not exact) or अगर the currently running
		 * transaction alपढ़ोy contains this buffer as well, dirty bit
		 * needs to be preserved so that the buffer माला_लो ग_लिखोरक्षित
		 * properly on running transaction's commit.
		 */
		jh = bh2jh(bh);
		अगर (buffer_dirty(bh) ||
		    (jh && (jh->b_transaction != transaction ||
			    jh->b_next_transaction))) अणु
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			जाओ out;
		पूर्ण
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

out:
	वापस AOP_WRITEPAGE_ACTIVATE;
पूर्ण

अटल पूर्णांक ext4_journalled_submit_inode_data_buffers(काष्ठा jbd2_inode *jinode)
अणु
	काष्ठा address_space *mapping = jinode->i_vfs_inode->i_mapping;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode =  WB_SYNC_ALL,
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.range_start = jinode->i_dirty_start,
		.range_end = jinode->i_dirty_end,
        पूर्ण;

	वापस ग_लिखो_cache_pages(mapping, &wbc,
				 ext4_journalled_ग_लिखोpage_callback,
				 jinode->i_transaction);
पूर्ण

अटल पूर्णांक ext4_journal_submit_inode_data_buffers(काष्ठा jbd2_inode *jinode)
अणु
	पूर्णांक ret;

	अगर (ext4_should_journal_data(jinode->i_vfs_inode))
		ret = ext4_journalled_submit_inode_data_buffers(jinode);
	अन्यथा
		ret = jbd2_journal_submit_inode_data_buffers(jinode);

	वापस ret;
पूर्ण

अटल पूर्णांक ext4_journal_finish_inode_data_buffers(काष्ठा jbd2_inode *jinode)
अणु
	पूर्णांक ret = 0;

	अगर (!ext4_should_journal_data(jinode->i_vfs_inode))
		ret = jbd2_journal_finish_inode_data_buffers(jinode);

	वापस ret;
पूर्ण

अटल bool प्रणाली_going_करोwn(व्योम)
अणु
	वापस प्रणाली_state == SYSTEM_HALT || प्रणाली_state == SYSTEM_POWER_OFF
		|| प्रणाली_state == SYSTEM_RESTART;
पूर्ण

काष्ठा ext4_err_translation अणु
	पूर्णांक code;
	पूर्णांक त्रुटि_सं;
पूर्ण;

#घोषणा EXT4_ERR_TRANSLATE(err) अणु .code = EXT4_ERR_##err, .त्रुटि_सं = err पूर्ण

अटल काष्ठा ext4_err_translation err_translation[] = अणु
	EXT4_ERR_TRANSLATE(EIO),
	EXT4_ERR_TRANSLATE(ENOMEM),
	EXT4_ERR_TRANSLATE(EFSBADCRC),
	EXT4_ERR_TRANSLATE(EFSCORRUPTED),
	EXT4_ERR_TRANSLATE(ENOSPC),
	EXT4_ERR_TRANSLATE(ENOKEY),
	EXT4_ERR_TRANSLATE(EROFS),
	EXT4_ERR_TRANSLATE(EFBIG),
	EXT4_ERR_TRANSLATE(EEXIST),
	EXT4_ERR_TRANSLATE(दुस्फल),
	EXT4_ERR_TRANSLATE(EOVERFLOW),
	EXT4_ERR_TRANSLATE(EBUSY),
	EXT4_ERR_TRANSLATE(ENOTसूची),
	EXT4_ERR_TRANSLATE(ENOTEMPTY),
	EXT4_ERR_TRANSLATE(ESHUTDOWN),
	EXT4_ERR_TRANSLATE(EFAULT),
पूर्ण;

अटल पूर्णांक ext4_त्रुटि_सं_to_code(पूर्णांक त्रुटि_सं)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(err_translation); i++)
		अगर (err_translation[i].त्रुटि_सं == त्रुटि_सं)
			वापस err_translation[i].code;
	वापस EXT4_ERR_UNKNOWN;
पूर्ण

अटल व्योम save_error_info(काष्ठा super_block *sb, पूर्णांक error,
			    __u32 ino, __u64 block,
			    स्थिर अक्षर *func, अचिन्हित पूर्णांक line)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	/* We शेष to EFSCORRUPTED error... */
	अगर (error == 0)
		error = EFSCORRUPTED;

	spin_lock(&sbi->s_error_lock);
	sbi->s_add_error_count++;
	sbi->s_last_error_code = error;
	sbi->s_last_error_line = line;
	sbi->s_last_error_ino = ino;
	sbi->s_last_error_block = block;
	sbi->s_last_error_func = func;
	sbi->s_last_error_समय = kसमय_get_real_seconds();
	अगर (!sbi->s_first_error_समय) अणु
		sbi->s_first_error_code = error;
		sbi->s_first_error_line = line;
		sbi->s_first_error_ino = ino;
		sbi->s_first_error_block = block;
		sbi->s_first_error_func = func;
		sbi->s_first_error_समय = sbi->s_last_error_समय;
	पूर्ण
	spin_unlock(&sbi->s_error_lock);
पूर्ण

/* Deal with the reporting of failure conditions on a fileप्रणाली such as
 * inconsistencies detected or पढ़ो IO failures.
 *
 * On ext2, we can store the error state of the fileप्रणाली in the
 * superblock.  That is not possible on ext4, because we may have other
 * ग_लिखो ordering स्थिरraपूर्णांकs on the superblock which prevent us from
 * writing it out straight away; and given that the journal is about to
 * be पातed, we can't rely on the current, or future, transactions to
 * ग_लिखो out the superblock safely.
 *
 * We'll just use the jbd2_journal_पात() error code to record an error in
 * the journal instead.  On recovery, the journal will complain about
 * that error until we've noted it करोwn and cleared it.
 *
 * If क्रमce_ro is set, we unconditionally क्रमce the fileप्रणाली पूर्णांकo an
 * ABORT|READONLY state, unless the error response on the fs has been set to
 * panic in which हाल we take the easy way out and panic immediately. This is
 * used to deal with unrecoverable failures such as journal IO errors or ENOMEM
 * at a critical moment in log management.
 */
अटल व्योम ext4_handle_error(काष्ठा super_block *sb, bool क्रमce_ro, पूर्णांक error,
			      __u32 ino, __u64 block,
			      स्थिर अक्षर *func, अचिन्हित पूर्णांक line)
अणु
	journal_t *journal = EXT4_SB(sb)->s_journal;
	bool जारी_fs = !क्रमce_ro && test_opt(sb, ERRORS_CONT);

	EXT4_SB(sb)->s_mount_state |= EXT4_ERROR_FS;
	अगर (test_opt(sb, WARN_ON_ERROR))
		WARN_ON_ONCE(1);

	अगर (!जारी_fs && !sb_rकरोnly(sb)) अणु
		ext4_set_mount_flag(sb, EXT4_MF_FS_ABORTED);
		अगर (journal)
			jbd2_journal_पात(journal, -EIO);
	पूर्ण

	अगर (!bdev_पढ़ो_only(sb->s_bdev)) अणु
		save_error_info(sb, error, ino, block, func, line);
		/*
		 * In हाल the fs should keep running, we need to ग_लिखोout
		 * superblock through the journal. Due to lock ordering
		 * स्थिरraपूर्णांकs, it may not be safe to करो it right here so we
		 * defer superblock flushing to a workqueue.
		 */
		अगर (जारी_fs)
			schedule_work(&EXT4_SB(sb)->s_error_work);
		अन्यथा
			ext4_commit_super(sb);
	पूर्ण

	/*
	 * We क्रमce ERRORS_RO behavior when प्रणाली is rebooting. Otherwise we
	 * could panic during 'reboot -f' as the underlying device got alपढ़ोy
	 * disabled.
	 */
	अगर (test_opt(sb, ERRORS_PANIC) && !प्रणाली_going_करोwn()) अणु
		panic("EXT4-fs (device %s): panic forced after error\n",
			sb->s_id);
	पूर्ण

	अगर (sb_rकरोnly(sb) || जारी_fs)
		वापस;

	ext4_msg(sb, KERN_CRIT, "Remounting filesystem read-only");
	/*
	 * Make sure updated value of ->s_mount_flags will be visible beक्रमe
	 * ->s_flags update
	 */
	smp_wmb();
	sb->s_flags |= SB_RDONLY;
पूर्ण

अटल व्योम flush_stashed_error_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ext4_sb_info *sbi = container_of(work, काष्ठा ext4_sb_info,
						s_error_work);
	journal_t *journal = sbi->s_journal;
	handle_t *handle;

	/*
	 * If the journal is still running, we have to ग_लिखो out superblock
	 * through the journal to aव्योम collisions of other journalled sb
	 * updates.
	 *
	 * We use directly jbd2 functions here to aव्योम recursing back पूर्णांकo
	 * ext4 error handling code during handling of previous errors.
	 */
	अगर (!sb_rकरोnly(sbi->s_sb) && journal) अणु
		handle = jbd2_journal_start(journal, 1);
		अगर (IS_ERR(handle))
			जाओ ग_लिखो_directly;
		अगर (jbd2_journal_get_ग_लिखो_access(handle, sbi->s_sbh)) अणु
			jbd2_journal_stop(handle);
			जाओ ग_लिखो_directly;
		पूर्ण
		ext4_update_super(sbi->s_sb);
		अगर (jbd2_journal_dirty_metadata(handle, sbi->s_sbh)) अणु
			jbd2_journal_stop(handle);
			जाओ ग_लिखो_directly;
		पूर्ण
		jbd2_journal_stop(handle);
		वापस;
	पूर्ण
ग_लिखो_directly:
	/*
	 * Write through journal failed. Write sb directly to get error info
	 * out and hope क्रम the best.
	 */
	ext4_commit_super(sbi->s_sb);
पूर्ण

#घोषणा ext4_error_ratelimit(sb)					\
		___ratelimit(&(EXT4_SB(sb)->s_err_ratelimit_state),	\
			     "EXT4-fs error")

व्योम __ext4_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		  अचिन्हित पूर्णांक line, bool क्रमce_ro, पूर्णांक error, __u64 block,
		  स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(sb))))
		वापस;

	trace_ext4_error(sb, function, line);
	अगर (ext4_error_ratelimit(sb)) अणु
		बहु_शुरू(args, fmt);
		vaf.fmt = fmt;
		vaf.va = &args;
		prपूर्णांकk(KERN_CRIT
		       "EXT4-fs error (device %s): %s:%d: comm %s: %pV\n",
		       sb->s_id, function, line, current->comm, &vaf);
		बहु_पूर्ण(args);
	पूर्ण
	ext4_handle_error(sb, क्रमce_ro, error, 0, block, function, line);
पूर्ण

व्योम __ext4_error_inode(काष्ठा inode *inode, स्थिर अक्षर *function,
			अचिन्हित पूर्णांक line, ext4_fsblk_t block, पूर्णांक error,
			स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	काष्ठा va_क्रमmat vaf;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस;

	trace_ext4_error(inode->i_sb, function, line);
	अगर (ext4_error_ratelimit(inode->i_sb)) अणु
		बहु_शुरू(args, fmt);
		vaf.fmt = fmt;
		vaf.va = &args;
		अगर (block)
			prपूर्णांकk(KERN_CRIT "EXT4-fs error (device %s): %s:%d: "
			       "inode #%lu: block %llu: comm %s: %pV\n",
			       inode->i_sb->s_id, function, line, inode->i_ino,
			       block, current->comm, &vaf);
		अन्यथा
			prपूर्णांकk(KERN_CRIT "EXT4-fs error (device %s): %s:%d: "
			       "inode #%lu: comm %s: %pV\n",
			       inode->i_sb->s_id, function, line, inode->i_ino,
			       current->comm, &vaf);
		बहु_पूर्ण(args);
	पूर्ण
	ext4_handle_error(inode->i_sb, false, error, inode->i_ino, block,
			  function, line);
पूर्ण

व्योम __ext4_error_file(काष्ठा file *file, स्थिर अक्षर *function,
		       अचिन्हित पूर्णांक line, ext4_fsblk_t block,
		       स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	काष्ठा va_क्रमmat vaf;
	काष्ठा inode *inode = file_inode(file);
	अक्षर pathname[80], *path;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस;

	trace_ext4_error(inode->i_sb, function, line);
	अगर (ext4_error_ratelimit(inode->i_sb)) अणु
		path = file_path(file, pathname, माप(pathname));
		अगर (IS_ERR(path))
			path = "(unknown)";
		बहु_शुरू(args, fmt);
		vaf.fmt = fmt;
		vaf.va = &args;
		अगर (block)
			prपूर्णांकk(KERN_CRIT
			       "EXT4-fs error (device %s): %s:%d: inode #%lu: "
			       "block %llu: comm %s: path %s: %pV\n",
			       inode->i_sb->s_id, function, line, inode->i_ino,
			       block, current->comm, path, &vaf);
		अन्यथा
			prपूर्णांकk(KERN_CRIT
			       "EXT4-fs error (device %s): %s:%d: inode #%lu: "
			       "comm %s: path %s: %pV\n",
			       inode->i_sb->s_id, function, line, inode->i_ino,
			       current->comm, path, &vaf);
		बहु_पूर्ण(args);
	पूर्ण
	ext4_handle_error(inode->i_sb, false, EFSCORRUPTED, inode->i_ino, block,
			  function, line);
पूर्ण

स्थिर अक्षर *ext4_decode_error(काष्ठा super_block *sb, पूर्णांक त्रुटि_सं,
			      अक्षर nbuf[16])
अणु
	अक्षर *errstr = शून्य;

	चयन (त्रुटि_सं) अणु
	हाल -EFSCORRUPTED:
		errstr = "Corrupt filesystem";
		अवरोध;
	हाल -EFSBADCRC:
		errstr = "Filesystem failed CRC";
		अवरोध;
	हाल -EIO:
		errstr = "IO failure";
		अवरोध;
	हाल -ENOMEM:
		errstr = "Out of memory";
		अवरोध;
	हाल -EROFS:
		अगर (!sb || (EXT4_SB(sb)->s_journal &&
			    EXT4_SB(sb)->s_journal->j_flags & JBD2_ABORT))
			errstr = "Journal has aborted";
		अन्यथा
			errstr = "Readonly filesystem";
		अवरोध;
	शेष:
		/* If the caller passed in an extra buffer क्रम unknown
		 * errors, textualise them now.  Else we just वापस
		 * शून्य. */
		अगर (nbuf) अणु
			/* Check क्रम truncated error codes... */
			अगर (snम_लिखो(nbuf, 16, "error %d", -त्रुटि_सं) >= 0)
				errstr = nbuf;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस errstr;
पूर्ण

/* __ext4_std_error decodes expected errors from journaling functions
 * स्वतःmatically and invokes the appropriate error response.  */

व्योम __ext4_std_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		      अचिन्हित पूर्णांक line, पूर्णांक त्रुटि_सं)
अणु
	अक्षर nbuf[16];
	स्थिर अक्षर *errstr;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(sb))))
		वापस;

	/* Special हाल: अगर the error is EROFS, and we're not alपढ़ोy
	 * inside a transaction, then there's really no poपूर्णांक in logging
	 * an error. */
	अगर (त्रुटि_सं == -EROFS && journal_current_handle() == शून्य && sb_rकरोnly(sb))
		वापस;

	अगर (ext4_error_ratelimit(sb)) अणु
		errstr = ext4_decode_error(sb, त्रुटि_सं, nbuf);
		prपूर्णांकk(KERN_CRIT "EXT4-fs error (device %s) in %s:%d: %s\n",
		       sb->s_id, function, line, errstr);
	पूर्ण

	ext4_handle_error(sb, false, -त्रुटि_सं, 0, 0, function, line);
पूर्ण

व्योम __ext4_msg(काष्ठा super_block *sb,
		स्थिर अक्षर *prefix, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	atomic_inc(&EXT4_SB(sb)->s_msg_count);
	अगर (!___ratelimit(&(EXT4_SB(sb)->s_msg_ratelimit_state), "EXT4-fs"))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	prपूर्णांकk("%sEXT4-fs (%s): %pV\n", prefix, sb->s_id, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक ext4_warning_ratelimit(काष्ठा super_block *sb)
अणु
	atomic_inc(&EXT4_SB(sb)->s_warning_count);
	वापस ___ratelimit(&(EXT4_SB(sb)->s_warning_ratelimit_state),
			    "EXT4-fs warning");
पूर्ण

व्योम __ext4_warning(काष्ठा super_block *sb, स्थिर अक्षर *function,
		    अचिन्हित पूर्णांक line, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!ext4_warning_ratelimit(sb))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	prपूर्णांकk(KERN_WARNING "EXT4-fs warning (device %s): %s:%d: %pV\n",
	       sb->s_id, function, line, &vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम __ext4_warning_inode(स्थिर काष्ठा inode *inode, स्थिर अक्षर *function,
			  अचिन्हित पूर्णांक line, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!ext4_warning_ratelimit(inode->i_sb))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	prपूर्णांकk(KERN_WARNING "EXT4-fs warning (device %s): %s:%d: "
	       "inode #%lu: comm %s: %pV\n", inode->i_sb->s_id,
	       function, line, inode->i_ino, current->comm, &vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम __ext4_grp_locked_error(स्थिर अक्षर *function, अचिन्हित पूर्णांक line,
			     काष्ठा super_block *sb, ext4_group_t grp,
			     अचिन्हित दीर्घ ino, ext4_fsblk_t block,
			     स्थिर अक्षर *fmt, ...)
__releases(bitlock)
__acquires(bitlock)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(sb))))
		वापस;

	trace_ext4_error(sb, function, line);
	अगर (ext4_error_ratelimit(sb)) अणु
		बहु_शुरू(args, fmt);
		vaf.fmt = fmt;
		vaf.va = &args;
		prपूर्णांकk(KERN_CRIT "EXT4-fs error (device %s): %s:%d: group %u, ",
		       sb->s_id, function, line, grp);
		अगर (ino)
			prपूर्णांकk(KERN_CONT "inode %lu: ", ino);
		अगर (block)
			prपूर्णांकk(KERN_CONT "block %llu:",
			       (अचिन्हित दीर्घ दीर्घ) block);
		prपूर्णांकk(KERN_CONT "%pV\n", &vaf);
		बहु_पूर्ण(args);
	पूर्ण

	अगर (test_opt(sb, ERRORS_CONT)) अणु
		अगर (test_opt(sb, WARN_ON_ERROR))
			WARN_ON_ONCE(1);
		EXT4_SB(sb)->s_mount_state |= EXT4_ERROR_FS;
		अगर (!bdev_पढ़ो_only(sb->s_bdev)) अणु
			save_error_info(sb, EFSCORRUPTED, ino, block, function,
					line);
			schedule_work(&EXT4_SB(sb)->s_error_work);
		पूर्ण
		वापस;
	पूर्ण
	ext4_unlock_group(sb, grp);
	ext4_handle_error(sb, false, EFSCORRUPTED, ino, block, function, line);
	/*
	 * We only get here in the ERRORS_RO हाल; relocking the group
	 * may be dangerous, but nothing bad will happen since the
	 * fileप्रणाली will have alपढ़ोy been marked पढ़ो/only and the
	 * journal has been पातed.  We वापस 1 as a hपूर्णांक to callers
	 * who might what to use the वापस value from
	 * ext4_grp_locked_error() to distinguish between the
	 * ERRORS_CONT and ERRORS_RO हाल, and perhaps वापस more
	 * aggressively from the ext4 function in question, with a
	 * more appropriate error code.
	 */
	ext4_lock_group(sb, grp);
	वापस;
पूर्ण

व्योम ext4_mark_group_biपंचांगap_corrupted(काष्ठा super_block *sb,
				     ext4_group_t group,
				     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, group);
	काष्ठा ext4_group_desc *gdp = ext4_get_group_desc(sb, group, शून्य);
	पूर्णांक ret;

	अगर (flags & EXT4_GROUP_INFO_BBITMAP_CORRUPT) अणु
		ret = ext4_test_and_set_bit(EXT4_GROUP_INFO_BBITMAP_CORRUPT_BIT,
					    &grp->bb_state);
		अगर (!ret)
			percpu_counter_sub(&sbi->s_मुक्तclusters_counter,
					   grp->bb_मुक्त);
	पूर्ण

	अगर (flags & EXT4_GROUP_INFO_IBITMAP_CORRUPT) अणु
		ret = ext4_test_and_set_bit(EXT4_GROUP_INFO_IBITMAP_CORRUPT_BIT,
					    &grp->bb_state);
		अगर (!ret && gdp) अणु
			पूर्णांक count;

			count = ext4_मुक्त_inodes_count(sb, gdp);
			percpu_counter_sub(&sbi->s_मुक्तinodes_counter,
					   count);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ext4_update_dynamic_rev(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;

	अगर (le32_to_cpu(es->s_rev_level) > EXT4_GOOD_OLD_REV)
		वापस;

	ext4_warning(sb,
		     "updating to rev %d because of new feature flag, "
		     "running e2fsck is recommended",
		     EXT4_DYNAMIC_REV);

	es->s_first_ino = cpu_to_le32(EXT4_GOOD_OLD_FIRST_INO);
	es->s_inode_size = cpu_to_le16(EXT4_GOOD_OLD_INODE_SIZE);
	es->s_rev_level = cpu_to_le32(EXT4_DYNAMIC_REV);
	/* leave es->s_feature_*compat flags alone */
	/* es->s_uuid will be set by e2fsck अगर empty */

	/*
	 * The rest of the superblock fields should be zero, and अगर not it
	 * means they are likely alपढ़ोy in use, so leave them alone.  We
	 * can leave it up to e2fsck to clean up any inconsistencies there.
	 */
पूर्ण

/*
 * Open the बाह्यal journal device
 */
अटल काष्ठा block_device *ext4_blkdev_get(dev_t dev, काष्ठा super_block *sb)
अणु
	काष्ठा block_device *bdev;

	bdev = blkdev_get_by_dev(dev, FMODE_READ|FMODE_WRITE|FMODE_EXCL, sb);
	अगर (IS_ERR(bdev))
		जाओ fail;
	वापस bdev;

fail:
	ext4_msg(sb, KERN_ERR,
		 "failed to open journal device unknown-block(%u,%u) %ld",
		 MAJOR(dev), MINOR(dev), PTR_ERR(bdev));
	वापस शून्य;
पूर्ण

/*
 * Release the journal device
 */
अटल व्योम ext4_blkdev_put(काष्ठा block_device *bdev)
अणु
	blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
पूर्ण

अटल व्योम ext4_blkdev_हटाओ(काष्ठा ext4_sb_info *sbi)
अणु
	काष्ठा block_device *bdev;
	bdev = sbi->s_journal_bdev;
	अगर (bdev) अणु
		ext4_blkdev_put(bdev);
		sbi->s_journal_bdev = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा inode *orphan_list_entry(काष्ठा list_head *l)
अणु
	वापस &list_entry(l, काष्ठा ext4_inode_info, i_orphan)->vfs_inode;
पूर्ण

अटल व्योम dump_orphan_list(काष्ठा super_block *sb, काष्ठा ext4_sb_info *sbi)
अणु
	काष्ठा list_head *l;

	ext4_msg(sb, KERN_ERR, "sb orphan head is %d",
		 le32_to_cpu(sbi->s_es->s_last_orphan));

	prपूर्णांकk(KERN_ERR "sb_info orphan list:\n");
	list_क्रम_each(l, &sbi->s_orphan) अणु
		काष्ठा inode *inode = orphan_list_entry(l);
		prपूर्णांकk(KERN_ERR "  "
		       "inode %s:%lu at %p: mode %o, nlink %d, next %d\n",
		       inode->i_sb->s_id, inode->i_ino, inode,
		       inode->i_mode, inode->i_nlink,
		       NEXT_ORPHAN(inode));
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक ext4_quota_off(काष्ठा super_block *sb, पूर्णांक type);

अटल अंतरभूत व्योम ext4_quota_off_umount(काष्ठा super_block *sb)
अणु
	पूर्णांक type;

	/* Use our quota_off function to clear inode flags etc. */
	क्रम (type = 0; type < EXT4_MAXQUOTAS; type++)
		ext4_quota_off(sb, type);
पूर्ण

/*
 * This is a helper function which is used in the mount/remount
 * codepaths (which holds s_umount) to fetch the quota file name.
 */
अटल अंतरभूत अक्षर *get_qf_name(काष्ठा super_block *sb,
				काष्ठा ext4_sb_info *sbi,
				पूर्णांक type)
अणु
	वापस rcu_dereference_रक्षित(sbi->s_qf_names[type],
					 lockdep_is_held(&sb->s_umount));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ext4_quota_off_umount(काष्ठा super_block *sb)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम ext4_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा buffer_head **group_desc;
	काष्ठा flex_groups **flex_groups;
	पूर्णांक पातed = 0;
	पूर्णांक i, err;

	ext4_unरेजिस्टर_li_request(sb);
	ext4_quota_off_umount(sb);

	flush_work(&sbi->s_error_work);
	destroy_workqueue(sbi->rsv_conversion_wq);

	/*
	 * Unरेजिस्टर sysfs beक्रमe destroying jbd2 journal.
	 * Since we could still access attr_journal_task attribute via sysfs
	 * path which could have sbi->s_journal->j_task as शून्य
	 */
	ext4_unरेजिस्टर_sysfs(sb);

	अगर (sbi->s_journal) अणु
		पातed = is_journal_पातed(sbi->s_journal);
		err = jbd2_journal_destroy(sbi->s_journal);
		sbi->s_journal = शून्य;
		अगर ((err < 0) && !पातed) अणु
			ext4_पात(sb, -err, "Couldn't clean up the journal");
		पूर्ण
	पूर्ण

	ext4_es_unरेजिस्टर_shrinker(sbi);
	del_समयr_sync(&sbi->s_err_report);
	ext4_release_प्रणाली_zone(sb);
	ext4_mb_release(sb);
	ext4_ext_release(sb);

	अगर (!sb_rकरोnly(sb) && !पातed) अणु
		ext4_clear_feature_journal_needs_recovery(sb);
		es->s_state = cpu_to_le16(sbi->s_mount_state);
	पूर्ण
	अगर (!sb_rकरोnly(sb))
		ext4_commit_super(sb);

	rcu_पढ़ो_lock();
	group_desc = rcu_dereference(sbi->s_group_desc);
	क्रम (i = 0; i < sbi->s_gdb_count; i++)
		brअन्यथा(group_desc[i]);
	kvमुक्त(group_desc);
	flex_groups = rcu_dereference(sbi->s_flex_groups);
	अगर (flex_groups) अणु
		क्रम (i = 0; i < sbi->s_flex_groups_allocated; i++)
			kvमुक्त(flex_groups[i]);
		kvमुक्त(flex_groups);
	पूर्ण
	rcu_पढ़ो_unlock();
	percpu_counter_destroy(&sbi->s_मुक्तclusters_counter);
	percpu_counter_destroy(&sbi->s_मुक्तinodes_counter);
	percpu_counter_destroy(&sbi->s_dirs_counter);
	percpu_counter_destroy(&sbi->s_dirtyclusters_counter);
	percpu_counter_destroy(&sbi->s_sra_exceeded_retry_limit);
	percpu_मुक्त_rwsem(&sbi->s_ग_लिखोpages_rwsem);
#अगर_घोषित CONFIG_QUOTA
	क्रम (i = 0; i < EXT4_MAXQUOTAS; i++)
		kमुक्त(get_qf_name(sb, sbi, i));
#पूर्ण_अगर

	/* Debugging code just in हाल the in-memory inode orphan list
	 * isn't empty.  The on-disk one can be non-empty if we've
	 * detected an error and taken the fs पढ़ोonly, but the
	 * in-memory list had better be clean by this poपूर्णांक. */
	अगर (!list_empty(&sbi->s_orphan))
		dump_orphan_list(sb, sbi);
	ASSERT(list_empty(&sbi->s_orphan));

	sync_blockdev(sb->s_bdev);
	invalidate_bdev(sb->s_bdev);
	अगर (sbi->s_journal_bdev && sbi->s_journal_bdev != sb->s_bdev) अणु
		/*
		 * Invalidate the journal device's buffers.  We don't want them
		 * भग्नing about in memory - the physical journal device may
		 * hotswapped, and it अवरोधs the `ro-after' testing code.
		 */
		sync_blockdev(sbi->s_journal_bdev);
		invalidate_bdev(sbi->s_journal_bdev);
		ext4_blkdev_हटाओ(sbi);
	पूर्ण

	ext4_xattr_destroy_cache(sbi->s_ea_inode_cache);
	sbi->s_ea_inode_cache = शून्य;

	ext4_xattr_destroy_cache(sbi->s_ea_block_cache);
	sbi->s_ea_block_cache = शून्य;

	अगर (sbi->s_mmp_tsk)
		kthपढ़ो_stop(sbi->s_mmp_tsk);
	brअन्यथा(sbi->s_sbh);
	sb->s_fs_info = शून्य;
	/*
	 * Now that we are completely करोne shutting करोwn the
	 * superblock, we need to actually destroy the kobject.
	 */
	kobject_put(&sbi->s_kobj);
	रुको_क्रम_completion(&sbi->s_kobj_unरेजिस्टर);
	अगर (sbi->s_chksum_driver)
		crypto_मुक्त_shash(sbi->s_chksum_driver);
	kमुक्त(sbi->s_blockgroup_lock);
	fs_put_dax(sbi->s_daxdev);
	fscrypt_मुक्त_dummy_policy(&sbi->s_dummy_enc_policy);
#अगर_घोषित CONFIG_UNICODE
	utf8_unload(sb->s_encoding);
#पूर्ण_अगर
	kमुक्त(sbi);
पूर्ण

अटल काष्ठा kmem_cache *ext4_inode_cachep;

/*
 * Called inside transaction, so use GFP_NOFS
 */
अटल काष्ठा inode *ext4_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_inode_info *ei;

	ei = kmem_cache_alloc(ext4_inode_cachep, GFP_NOFS);
	अगर (!ei)
		वापस शून्य;

	inode_set_iversion(&ei->vfs_inode, 1);
	spin_lock_init(&ei->i_raw_lock);
	INIT_LIST_HEAD(&ei->i_pपुनः_स्मृति_list);
	atomic_set(&ei->i_pपुनः_स्मृति_active, 0);
	spin_lock_init(&ei->i_pपुनः_स्मृति_lock);
	ext4_es_init_tree(&ei->i_es_tree);
	rwlock_init(&ei->i_es_lock);
	INIT_LIST_HEAD(&ei->i_es_list);
	ei->i_es_all_nr = 0;
	ei->i_es_shk_nr = 0;
	ei->i_es_shrink_lblk = 0;
	ei->i_reserved_data_blocks = 0;
	spin_lock_init(&(ei->i_block_reservation_lock));
	ext4_init_pending_tree(&ei->i_pending_tree);
#अगर_घोषित CONFIG_QUOTA
	ei->i_reserved_quota = 0;
	स_रखो(&ei->i_dquot, 0, माप(ei->i_dquot));
#पूर्ण_अगर
	ei->jinode = शून्य;
	INIT_LIST_HEAD(&ei->i_rsv_conversion_list);
	spin_lock_init(&ei->i_completed_io_lock);
	ei->i_sync_tid = 0;
	ei->i_datasync_tid = 0;
	atomic_set(&ei->i_unwritten, 0);
	INIT_WORK(&ei->i_rsv_conversion_work, ext4_end_io_rsv_work);
	ext4_fc_init_inode(&ei->vfs_inode);
	mutex_init(&ei->i_fc_lock);
	वापस &ei->vfs_inode;
पूर्ण

अटल पूर्णांक ext4_drop_inode(काष्ठा inode *inode)
अणु
	पूर्णांक drop = generic_drop_inode(inode);

	अगर (!drop)
		drop = fscrypt_drop_inode(inode);

	trace_ext4_drop_inode(inode, drop);
	वापस drop;
पूर्ण

अटल व्योम ext4_मुक्त_in_core_inode(काष्ठा inode *inode)
अणु
	fscrypt_मुक्त_inode(inode);
	अगर (!list_empty(&(EXT4_I(inode)->i_fc_list))) अणु
		pr_warn("%s: inode %ld still in fc list",
			__func__, inode->i_ino);
	पूर्ण
	kmem_cache_मुक्त(ext4_inode_cachep, EXT4_I(inode));
पूर्ण

अटल व्योम ext4_destroy_inode(काष्ठा inode *inode)
अणु
	अगर (!list_empty(&(EXT4_I(inode)->i_orphan))) अणु
		ext4_msg(inode->i_sb, KERN_ERR,
			 "Inode %lu (%p): orphan list check failed!",
			 inode->i_ino, EXT4_I(inode));
		prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 16, 4,
				EXT4_I(inode), माप(काष्ठा ext4_inode_info),
				true);
		dump_stack();
	पूर्ण
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा ext4_inode_info *ei = (काष्ठा ext4_inode_info *) foo;

	INIT_LIST_HEAD(&ei->i_orphan);
	init_rwsem(&ei->xattr_sem);
	init_rwsem(&ei->i_data_sem);
	init_rwsem(&ei->i_mmap_sem);
	inode_init_once(&ei->vfs_inode);
	ext4_fc_init_inode(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	ext4_inode_cachep = kmem_cache_create_usercopy("ext4_inode_cache",
				माप(काष्ठा ext4_inode_info), 0,
				(SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
					SLAB_ACCOUNT),
				दुरत्व(काष्ठा ext4_inode_info, i_data),
				माप_field(काष्ठा ext4_inode_info, i_data),
				init_once);
	अगर (ext4_inode_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(ext4_inode_cachep);
पूर्ण

व्योम ext4_clear_inode(काष्ठा inode *inode)
अणु
	ext4_fc_del(inode);
	invalidate_inode_buffers(inode);
	clear_inode(inode);
	ext4_discard_pपुनः_स्मृतिations(inode, 0);
	ext4_es_हटाओ_extent(inode, 0, EXT_MAX_BLOCKS);
	dquot_drop(inode);
	अगर (EXT4_I(inode)->jinode) अणु
		jbd2_journal_release_jbd_inode(EXT4_JOURNAL(inode),
					       EXT4_I(inode)->jinode);
		jbd2_मुक्त_inode(EXT4_I(inode)->jinode);
		EXT4_I(inode)->jinode = शून्य;
	पूर्ण
	fscrypt_put_encryption_info(inode);
	fsverity_cleanup_inode(inode);
पूर्ण

अटल काष्ठा inode *ext4_nfs_get_inode(काष्ठा super_block *sb,
					u64 ino, u32 generation)
अणु
	काष्ठा inode *inode;

	/*
	 * Currently we करोn't know the generation क्रम parent directory, so
	 * a generation of 0 means "accept any"
	 */
	inode = ext4_iget(sb, ino, EXT4_IGET_HANDLE);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (generation && inode->i_generation != generation) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	वापस inode;
पूर्ण

अटल काष्ठा dentry *ext4_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
					पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    ext4_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *ext4_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
					पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    ext4_nfs_get_inode);
पूर्ण

अटल पूर्णांक ext4_nfs_commit_metadata(काष्ठा inode *inode)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_ALL
	पूर्ण;

	trace_ext4_nfs_commit_metadata(inode);
	वापस ext4_ग_लिखो_inode(inode, &wbc);
पूर्ण

/*
 * Try to release metadata pages (indirect blocks, directories) which are
 * mapped via the block device.  Since these pages could have journal heads
 * which would prevent try_to_मुक्त_buffers() from मुक्तing them, we must use
 * jbd2 layer's try_to_मुक्त_buffers() function to release them.
 */
अटल पूर्णांक bdev_try_to_मुक्त_page(काष्ठा super_block *sb, काष्ठा page *page,
				 gfp_t रुको)
अणु
	journal_t *journal = EXT4_SB(sb)->s_journal;

	WARN_ON(PageChecked(page));
	अगर (!page_has_buffers(page))
		वापस 0;
	अगर (journal)
		वापस jbd2_journal_try_to_मुक्त_buffers(journal, page);

	वापस try_to_मुक्त_buffers(page);
पूर्ण

#अगर_घोषित CONFIG_FS_ENCRYPTION
अटल पूर्णांक ext4_get_context(काष्ठा inode *inode, व्योम *ctx, माप_प्रकार len)
अणु
	वापस ext4_xattr_get(inode, EXT4_XATTR_INDEX_ENCRYPTION,
				 EXT4_XATTR_NAME_ENCRYPTION_CONTEXT, ctx, len);
पूर्ण

अटल पूर्णांक ext4_set_context(काष्ठा inode *inode, स्थिर व्योम *ctx, माप_प्रकार len,
							व्योम *fs_data)
अणु
	handle_t *handle = fs_data;
	पूर्णांक res, res2, credits, retries = 0;

	/*
	 * Encrypting the root directory is not allowed because e2fsck expects
	 * lost+found to exist and be unencrypted, and encrypting the root
	 * directory would imply encrypting the lost+found directory as well as
	 * the filename "lost+found" itself.
	 */
	अगर (inode->i_ino == EXT4_ROOT_INO)
		वापस -EPERM;

	अगर (WARN_ON_ONCE(IS_DAX(inode) && i_size_पढ़ो(inode)))
		वापस -EINVAL;

	अगर (ext4_test_inode_flag(inode, EXT4_INODE_DAX))
		वापस -EOPNOTSUPP;

	res = ext4_convert_अंतरभूत_data(inode);
	अगर (res)
		वापस res;

	/*
	 * If a journal handle was specअगरied, then the encryption context is
	 * being set on a new inode via inheritance and is part of a larger
	 * transaction to create the inode.  Otherwise the encryption context is
	 * being set on an existing inode in its own transaction.  Only in the
	 * latter हाल should the "retry on ENOSPC" logic be used.
	 */

	अगर (handle) अणु
		res = ext4_xattr_set_handle(handle, inode,
					    EXT4_XATTR_INDEX_ENCRYPTION,
					    EXT4_XATTR_NAME_ENCRYPTION_CONTEXT,
					    ctx, len, 0);
		अगर (!res) अणु
			ext4_set_inode_flag(inode, EXT4_INODE_ENCRYPT);
			ext4_clear_inode_state(inode,
					EXT4_STATE_MAY_INLINE_DATA);
			/*
			 * Update inode->i_flags - S_ENCRYPTED will be enabled,
			 * S_DAX may be disabled
			 */
			ext4_set_inode_flags(inode, false);
		पूर्ण
		वापस res;
	पूर्ण

	res = dquot_initialize(inode);
	अगर (res)
		वापस res;
retry:
	res = ext4_xattr_set_credits(inode, len, false /* is_create */,
				     &credits);
	अगर (res)
		वापस res;

	handle = ext4_journal_start(inode, EXT4_HT_MISC, credits);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	res = ext4_xattr_set_handle(handle, inode, EXT4_XATTR_INDEX_ENCRYPTION,
				    EXT4_XATTR_NAME_ENCRYPTION_CONTEXT,
				    ctx, len, 0);
	अगर (!res) अणु
		ext4_set_inode_flag(inode, EXT4_INODE_ENCRYPT);
		/*
		 * Update inode->i_flags - S_ENCRYPTED will be enabled,
		 * S_DAX may be disabled
		 */
		ext4_set_inode_flags(inode, false);
		res = ext4_mark_inode_dirty(handle, inode);
		अगर (res)
			EXT4_ERROR_INODE(inode, "Failed to mark inode dirty");
	पूर्ण
	res2 = ext4_journal_stop(handle);

	अगर (res == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		जाओ retry;
	अगर (!res)
		res = res2;
	वापस res;
पूर्ण

अटल स्थिर जोड़ fscrypt_policy *ext4_get_dummy_policy(काष्ठा super_block *sb)
अणु
	वापस EXT4_SB(sb)->s_dummy_enc_policy.policy;
पूर्ण

अटल bool ext4_has_stable_inodes(काष्ठा super_block *sb)
अणु
	वापस ext4_has_feature_stable_inodes(sb);
पूर्ण

अटल व्योम ext4_get_ino_and_lblk_bits(काष्ठा super_block *sb,
				       पूर्णांक *ino_bits_ret, पूर्णांक *lblk_bits_ret)
अणु
	*ino_bits_ret = 8 * माप(EXT4_SB(sb)->s_es->s_inodes_count);
	*lblk_bits_ret = 8 * माप(ext4_lblk_t);
पूर्ण

अटल स्थिर काष्ठा fscrypt_operations ext4_cryptops = अणु
	.key_prefix		= "ext4:",
	.get_context		= ext4_get_context,
	.set_context		= ext4_set_context,
	.get_dummy_policy	= ext4_get_dummy_policy,
	.empty_dir		= ext4_empty_dir,
	.max_namelen		= EXT4_NAME_LEN,
	.has_stable_inodes	= ext4_has_stable_inodes,
	.get_ino_and_lblk_bits	= ext4_get_ino_and_lblk_bits,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_QUOTA
अटल स्थिर अक्षर * स्थिर quotatypes[] = INITQFNAMES;
#घोषणा QTYPE2NAME(t) (quotatypes[t])

अटल पूर्णांक ext4_ग_लिखो_dquot(काष्ठा dquot *dquot);
अटल पूर्णांक ext4_acquire_dquot(काष्ठा dquot *dquot);
अटल पूर्णांक ext4_release_dquot(काष्ठा dquot *dquot);
अटल पूर्णांक ext4_mark_dquot_dirty(काष्ठा dquot *dquot);
अटल पूर्णांक ext4_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type);
अटल पूर्णांक ext4_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			 स्थिर काष्ठा path *path);
अटल पूर्णांक ext4_quota_on_mount(काष्ठा super_block *sb, पूर्णांक type);
अटल sमाप_प्रकार ext4_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
			       माप_प्रकार len, loff_t off);
अटल sमाप_प्रकार ext4_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
				स्थिर अक्षर *data, माप_प्रकार len, loff_t off);
अटल पूर्णांक ext4_quota_enable(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			     अचिन्हित पूर्णांक flags);
अटल पूर्णांक ext4_enable_quotas(काष्ठा super_block *sb);

अटल काष्ठा dquot **ext4_get_dquots(काष्ठा inode *inode)
अणु
	वापस EXT4_I(inode)->i_dquot;
पूर्ण

अटल स्थिर काष्ठा dquot_operations ext4_quota_operations = अणु
	.get_reserved_space	= ext4_get_reserved_space,
	.ग_लिखो_dquot		= ext4_ग_लिखो_dquot,
	.acquire_dquot		= ext4_acquire_dquot,
	.release_dquot		= ext4_release_dquot,
	.mark_dirty		= ext4_mark_dquot_dirty,
	.ग_लिखो_info		= ext4_ग_लिखो_info,
	.alloc_dquot		= dquot_alloc,
	.destroy_dquot		= dquot_destroy,
	.get_projid		= ext4_get_projid,
	.get_inode_usage	= ext4_get_inode_usage,
	.get_next_id		= dquot_get_next_id,
पूर्ण;

अटल स्थिर काष्ठा quotactl_ops ext4_qctl_operations = अणु
	.quota_on	= ext4_quota_on,
	.quota_off	= ext4_quota_off,
	.quota_sync	= dquot_quota_sync,
	.get_state	= dquot_get_state,
	.set_info	= dquot_set_dqinfo,
	.get_dqblk	= dquot_get_dqblk,
	.set_dqblk	= dquot_set_dqblk,
	.get_nextdqblk	= dquot_get_next_dqblk,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा super_operations ext4_sops = अणु
	.alloc_inode	= ext4_alloc_inode,
	.मुक्त_inode	= ext4_मुक्त_in_core_inode,
	.destroy_inode	= ext4_destroy_inode,
	.ग_लिखो_inode	= ext4_ग_लिखो_inode,
	.dirty_inode	= ext4_dirty_inode,
	.drop_inode	= ext4_drop_inode,
	.evict_inode	= ext4_evict_inode,
	.put_super	= ext4_put_super,
	.sync_fs	= ext4_sync_fs,
	.मुक्तze_fs	= ext4_मुक्तze,
	.unमुक्तze_fs	= ext4_unमुक्तze,
	.statfs		= ext4_statfs,
	.remount_fs	= ext4_remount,
	.show_options	= ext4_show_options,
#अगर_घोषित CONFIG_QUOTA
	.quota_पढ़ो	= ext4_quota_पढ़ो,
	.quota_ग_लिखो	= ext4_quota_ग_लिखो,
	.get_dquots	= ext4_get_dquots,
#पूर्ण_अगर
	.bdev_try_to_मुक्त_page = bdev_try_to_मुक्त_page,
पूर्ण;

अटल स्थिर काष्ठा export_operations ext4_export_ops = अणु
	.fh_to_dentry = ext4_fh_to_dentry,
	.fh_to_parent = ext4_fh_to_parent,
	.get_parent = ext4_get_parent,
	.commit_metadata = ext4_nfs_commit_metadata,
पूर्ण;

क्रमागत अणु
	Opt_bsd_df, Opt_minix_df, Opt_grpid, Opt_nogrpid,
	Opt_resgid, Opt_resuid, Opt_sb, Opt_err_cont, Opt_err_panic, Opt_err_ro,
	Opt_nouid32, Opt_debug, Opt_हटाओd,
	Opt_user_xattr, Opt_nouser_xattr, Opt_acl, Opt_noacl,
	Opt_स्वतः_da_alloc, Opt_noस्वतः_da_alloc, Opt_noload,
	Opt_commit, Opt_min_batch_समय, Opt_max_batch_समय, Opt_journal_dev,
	Opt_journal_path, Opt_journal_checksum, Opt_journal_async_commit,
	Opt_पात, Opt_data_journal, Opt_data_ordered, Opt_data_ग_लिखोback,
	Opt_data_err_पात, Opt_data_err_ignore, Opt_test_dummy_encryption,
	Opt_अंतरभूतcrypt,
	Opt_usrjquota, Opt_grpjquota, Opt_offusrjquota, Opt_offgrpjquota,
	Opt_jqfmt_vfsold, Opt_jqfmt_vfsv0, Opt_jqfmt_vfsv1, Opt_quota,
	Opt_noquota, Opt_barrier, Opt_nobarrier, Opt_err,
	Opt_usrquota, Opt_grpquota, Opt_prjquota, Opt_i_version,
	Opt_dax, Opt_dax_always, Opt_dax_inode, Opt_dax_never,
	Opt_stripe, Opt_delalloc, Opt_nodelalloc, Opt_warn_on_error,
	Opt_nowarn_on_error, Opt_mblk_io_submit,
	Opt_lazyसमय, Opt_nolazyसमय, Opt_debug_want_extra_isize,
	Opt_nomblk_io_submit, Opt_block_validity, Opt_noblock_validity,
	Opt_inode_पढ़ोahead_blks, Opt_journal_ioprio,
	Opt_dioपढ़ो_nolock, Opt_dioपढ़ो_lock,
	Opt_discard, Opt_nodiscard, Opt_init_itable, Opt_noinit_itable,
	Opt_max_dir_size_kb, Opt_nojournal_checksum, Opt_nombcache,
	Opt_no_prefetch_block_biपंचांगaps, Opt_mb_optimize_scan,
#अगर_घोषित CONFIG_EXT4_DEBUG
	Opt_fc_debug_max_replay, Opt_fc_debug_क्रमce
#पूर्ण_अगर
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_bsd_df, "bsddf"पूर्ण,
	अणुOpt_minix_df, "minixdf"पूर्ण,
	अणुOpt_grpid, "grpid"पूर्ण,
	अणुOpt_grpid, "bsdgroups"पूर्ण,
	अणुOpt_nogrpid, "nogrpid"पूर्ण,
	अणुOpt_nogrpid, "sysvgroups"पूर्ण,
	अणुOpt_resgid, "resgid=%u"पूर्ण,
	अणुOpt_resuid, "resuid=%u"पूर्ण,
	अणुOpt_sb, "sb=%u"पूर्ण,
	अणुOpt_err_cont, "errors=continue"पूर्ण,
	अणुOpt_err_panic, "errors=panic"पूर्ण,
	अणुOpt_err_ro, "errors=remount-ro"पूर्ण,
	अणुOpt_nouid32, "nouid32"पूर्ण,
	अणुOpt_debug, "debug"पूर्ण,
	अणुOpt_हटाओd, "oldalloc"पूर्ण,
	अणुOpt_हटाओd, "orlov"पूर्ण,
	अणुOpt_user_xattr, "user_xattr"पूर्ण,
	अणुOpt_nouser_xattr, "nouser_xattr"पूर्ण,
	अणुOpt_acl, "acl"पूर्ण,
	अणुOpt_noacl, "noacl"पूर्ण,
	अणुOpt_noload, "norecovery"पूर्ण,
	अणुOpt_noload, "noload"पूर्ण,
	अणुOpt_हटाओd, "nobh"पूर्ण,
	अणुOpt_हटाओd, "bh"पूर्ण,
	अणुOpt_commit, "commit=%u"पूर्ण,
	अणुOpt_min_batch_समय, "min_batch_time=%u"पूर्ण,
	अणुOpt_max_batch_समय, "max_batch_time=%u"पूर्ण,
	अणुOpt_journal_dev, "journal_dev=%u"पूर्ण,
	अणुOpt_journal_path, "journal_path=%s"पूर्ण,
	अणुOpt_journal_checksum, "journal_checksum"पूर्ण,
	अणुOpt_nojournal_checksum, "nojournal_checksum"पूर्ण,
	अणुOpt_journal_async_commit, "journal_async_commit"पूर्ण,
	अणुOpt_पात, "abort"पूर्ण,
	अणुOpt_data_journal, "data=journal"पूर्ण,
	अणुOpt_data_ordered, "data=ordered"पूर्ण,
	अणुOpt_data_ग_लिखोback, "data=writeback"पूर्ण,
	अणुOpt_data_err_पात, "data_err=abort"पूर्ण,
	अणुOpt_data_err_ignore, "data_err=ignore"पूर्ण,
	अणुOpt_offusrjquota, "usrjquota="पूर्ण,
	अणुOpt_usrjquota, "usrjquota=%s"पूर्ण,
	अणुOpt_offgrpjquota, "grpjquota="पूर्ण,
	अणुOpt_grpjquota, "grpjquota=%s"पूर्ण,
	अणुOpt_jqfmt_vfsold, "jqfmt=vfsold"पूर्ण,
	अणुOpt_jqfmt_vfsv0, "jqfmt=vfsv0"पूर्ण,
	अणुOpt_jqfmt_vfsv1, "jqfmt=vfsv1"पूर्ण,
	अणुOpt_grpquota, "grpquota"पूर्ण,
	अणुOpt_noquota, "noquota"पूर्ण,
	अणुOpt_quota, "quota"पूर्ण,
	अणुOpt_usrquota, "usrquota"पूर्ण,
	अणुOpt_prjquota, "prjquota"पूर्ण,
	अणुOpt_barrier, "barrier=%u"पूर्ण,
	अणुOpt_barrier, "barrier"पूर्ण,
	अणुOpt_nobarrier, "nobarrier"पूर्ण,
	अणुOpt_i_version, "i_version"पूर्ण,
	अणुOpt_dax, "dax"पूर्ण,
	अणुOpt_dax_always, "dax=always"पूर्ण,
	अणुOpt_dax_inode, "dax=inode"पूर्ण,
	अणुOpt_dax_never, "dax=never"पूर्ण,
	अणुOpt_stripe, "stripe=%u"पूर्ण,
	अणुOpt_delalloc, "delalloc"पूर्ण,
	अणुOpt_warn_on_error, "warn_on_error"पूर्ण,
	अणुOpt_nowarn_on_error, "nowarn_on_error"पूर्ण,
	अणुOpt_lazyसमय, "lazytime"पूर्ण,
	अणुOpt_nolazyसमय, "nolazytime"पूर्ण,
	अणुOpt_debug_want_extra_isize, "debug_want_extra_isize=%u"पूर्ण,
	अणुOpt_nodelalloc, "nodelalloc"पूर्ण,
	अणुOpt_हटाओd, "mblk_io_submit"पूर्ण,
	अणुOpt_हटाओd, "nomblk_io_submit"पूर्ण,
	अणुOpt_block_validity, "block_validity"पूर्ण,
	अणुOpt_noblock_validity, "noblock_validity"पूर्ण,
	अणुOpt_inode_पढ़ोahead_blks, "inode_readahead_blks=%u"पूर्ण,
	अणुOpt_journal_ioprio, "journal_ioprio=%u"पूर्ण,
	अणुOpt_स्वतः_da_alloc, "auto_da_alloc=%u"पूर्ण,
	अणुOpt_स्वतः_da_alloc, "auto_da_alloc"पूर्ण,
	अणुOpt_noस्वतः_da_alloc, "noauto_da_alloc"पूर्ण,
	अणुOpt_dioपढ़ो_nolock, "dioread_nolock"पूर्ण,
	अणुOpt_dioपढ़ो_lock, "nodioread_nolock"पूर्ण,
	अणुOpt_dioपढ़ो_lock, "dioread_lock"पूर्ण,
	अणुOpt_discard, "discard"पूर्ण,
	अणुOpt_nodiscard, "nodiscard"पूर्ण,
	अणुOpt_init_itable, "init_itable=%u"पूर्ण,
	अणुOpt_init_itable, "init_itable"पूर्ण,
	अणुOpt_noinit_itable, "noinit_itable"पूर्ण,
#अगर_घोषित CONFIG_EXT4_DEBUG
	अणुOpt_fc_debug_क्रमce, "fc_debug_force"पूर्ण,
	अणुOpt_fc_debug_max_replay, "fc_debug_max_replay=%u"पूर्ण,
#पूर्ण_अगर
	अणुOpt_max_dir_size_kb, "max_dir_size_kb=%u"पूर्ण,
	अणुOpt_test_dummy_encryption, "test_dummy_encryption=%s"पूर्ण,
	अणुOpt_test_dummy_encryption, "test_dummy_encryption"पूर्ण,
	अणुOpt_अंतरभूतcrypt, "inlinecrypt"पूर्ण,
	अणुOpt_nombcache, "nombcache"पूर्ण,
	अणुOpt_nombcache, "no_mbcache"पूर्ण,	/* क्रम backward compatibility */
	अणुOpt_हटाओd, "prefetch_block_bitmaps"पूर्ण,
	अणुOpt_no_prefetch_block_biपंचांगaps, "no_prefetch_block_bitmaps"पूर्ण,
	अणुOpt_mb_optimize_scan, "mb_optimize_scan=%d"पूर्ण,
	अणुOpt_हटाओd, "check=none"पूर्ण,	/* mount option from ext2/3 */
	अणुOpt_हटाओd, "nocheck"पूर्ण,	/* mount option from ext2/3 */
	अणुOpt_हटाओd, "reservation"पूर्ण,	/* mount option from ext2/3 */
	अणुOpt_हटाओd, "noreservation"पूर्ण, /* mount option from ext2/3 */
	अणुOpt_हटाओd, "journal=%u"पूर्ण,	/* mount option from ext2/3 */
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अटल ext4_fsblk_t get_sb_block(व्योम **data)
अणु
	ext4_fsblk_t	sb_block;
	अक्षर		*options = (अक्षर *) *data;

	अगर (!options || म_भेदन(options, "sb=", 3) != 0)
		वापस 1;	/* Default location */

	options += 3;
	/* TODO: use simple_म_से_दीर्घl with >32bit ext4 */
	sb_block = simple_म_से_अदीर्घ(options, &options, 0);
	अगर (*options && *options != ',') अणु
		prपूर्णांकk(KERN_ERR "EXT4-fs: Invalid sb specification: %s\n",
		       (अक्षर *) *data);
		वापस 1;
	पूर्ण
	अगर (*options == ',')
		options++;
	*data = (व्योम *) options;

	वापस sb_block;
पूर्ण

#घोषणा DEFAULT_JOURNAL_IOPRIO (IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, 3))
#घोषणा DEFAULT_MB_OPTIMIZE_SCAN	(-1)

अटल स्थिर अक्षर deprecated_msg[] =
	"Mount option \"%s\" will be removed by %s\n"
	"Contact linux-ext4@vger.kernel.org if you think we should keep it.\n";

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक set_qf_name(काष्ठा super_block *sb, पूर्णांक qtype, substring_t *args)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अक्षर *qname, *old_qname = get_qf_name(sb, sbi, qtype);
	पूर्णांक ret = -1;

	अगर (sb_any_quota_loaded(sb) && !old_qname) अणु
		ext4_msg(sb, KERN_ERR,
			"Cannot change journaled "
			"quota options when quota turned on");
		वापस -1;
	पूर्ण
	अगर (ext4_has_feature_quota(sb)) अणु
		ext4_msg(sb, KERN_INFO, "Journaled quota options "
			 "ignored when QUOTA feature is enabled");
		वापस 1;
	पूर्ण
	qname = match_strdup(args);
	अगर (!qname) अणु
		ext4_msg(sb, KERN_ERR,
			"Not enough memory for storing quotafile name");
		वापस -1;
	पूर्ण
	अगर (old_qname) अणु
		अगर (म_भेद(old_qname, qname) == 0)
			ret = 1;
		अन्यथा
			ext4_msg(sb, KERN_ERR,
				 "%s quota file already specified",
				 QTYPE2NAME(qtype));
		जाओ errout;
	पूर्ण
	अगर (म_अक्षर(qname, '/')) अणु
		ext4_msg(sb, KERN_ERR,
			"quotafile must be on filesystem root");
		जाओ errout;
	पूर्ण
	rcu_assign_poपूर्णांकer(sbi->s_qf_names[qtype], qname);
	set_opt(sb, QUOTA);
	वापस 1;
errout:
	kमुक्त(qname);
	वापस ret;
पूर्ण

अटल पूर्णांक clear_qf_name(काष्ठा super_block *sb, पूर्णांक qtype)
अणु

	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अक्षर *old_qname = get_qf_name(sb, sbi, qtype);

	अगर (sb_any_quota_loaded(sb) && old_qname) अणु
		ext4_msg(sb, KERN_ERR, "Cannot change journaled quota options"
			" when quota turned on");
		वापस -1;
	पूर्ण
	rcu_assign_poपूर्णांकer(sbi->s_qf_names[qtype], शून्य);
	synchronize_rcu();
	kमुक्त(old_qname);
	वापस 1;
पूर्ण
#पूर्ण_अगर

#घोषणा MOPT_SET	0x0001
#घोषणा MOPT_CLEAR	0x0002
#घोषणा MOPT_NOSUPPORT	0x0004
#घोषणा MOPT_EXPLICIT	0x0008
#घोषणा MOPT_CLEAR_ERR	0x0010
#घोषणा MOPT_GTE0	0x0020
#अगर_घोषित CONFIG_QUOTA
#घोषणा MOPT_Q		0
#घोषणा MOPT_QFMT	0x0040
#अन्यथा
#घोषणा MOPT_Q		MOPT_NOSUPPORT
#घोषणा MOPT_QFMT	MOPT_NOSUPPORT
#पूर्ण_अगर
#घोषणा MOPT_DATAJ	0x0080
#घोषणा MOPT_NO_EXT2	0x0100
#घोषणा MOPT_NO_EXT3	0x0200
#घोषणा MOPT_EXT4_ONLY	(MOPT_NO_EXT2 | MOPT_NO_EXT3)
#घोषणा MOPT_STRING	0x0400
#घोषणा MOPT_SKIP	0x0800
#घोषणा	MOPT_2		0x1000

अटल स्थिर काष्ठा mount_opts अणु
	पूर्णांक	token;
	पूर्णांक	mount_opt;
	पूर्णांक	flags;
पूर्ण ext4_mount_opts[] = अणु
	अणुOpt_minix_df, EXT4_MOUNT_MINIX_DF, MOPT_SETपूर्ण,
	अणुOpt_bsd_df, EXT4_MOUNT_MINIX_DF, MOPT_CLEARपूर्ण,
	अणुOpt_grpid, EXT4_MOUNT_GRPID, MOPT_SETपूर्ण,
	अणुOpt_nogrpid, EXT4_MOUNT_GRPID, MOPT_CLEARपूर्ण,
	अणुOpt_block_validity, EXT4_MOUNT_BLOCK_VALIDITY, MOPT_SETपूर्ण,
	अणुOpt_noblock_validity, EXT4_MOUNT_BLOCK_VALIDITY, MOPT_CLEARपूर्ण,
	अणुOpt_dioपढ़ो_nolock, EXT4_MOUNT_DIOREAD_NOLOCK,
	 MOPT_EXT4_ONLY | MOPT_SETपूर्ण,
	अणुOpt_dioपढ़ो_lock, EXT4_MOUNT_DIOREAD_NOLOCK,
	 MOPT_EXT4_ONLY | MOPT_CLEARपूर्ण,
	अणुOpt_discard, EXT4_MOUNT_DISCARD, MOPT_SETपूर्ण,
	अणुOpt_nodiscard, EXT4_MOUNT_DISCARD, MOPT_CLEARपूर्ण,
	अणुOpt_delalloc, EXT4_MOUNT_DELALLOC,
	 MOPT_EXT4_ONLY | MOPT_SET | MOPT_EXPLICITपूर्ण,
	अणुOpt_nodelalloc, EXT4_MOUNT_DELALLOC,
	 MOPT_EXT4_ONLY | MOPT_CLEARपूर्ण,
	अणुOpt_warn_on_error, EXT4_MOUNT_WARN_ON_ERROR, MOPT_SETपूर्ण,
	अणुOpt_nowarn_on_error, EXT4_MOUNT_WARN_ON_ERROR, MOPT_CLEARपूर्ण,
	अणुOpt_nojournal_checksum, EXT4_MOUNT_JOURNAL_CHECKSUM,
	 MOPT_EXT4_ONLY | MOPT_CLEARपूर्ण,
	अणुOpt_journal_checksum, EXT4_MOUNT_JOURNAL_CHECKSUM,
	 MOPT_EXT4_ONLY | MOPT_SET | MOPT_EXPLICITपूर्ण,
	अणुOpt_journal_async_commit, (EXT4_MOUNT_JOURNAL_ASYNC_COMMIT |
				    EXT4_MOUNT_JOURNAL_CHECKSUM),
	 MOPT_EXT4_ONLY | MOPT_SET | MOPT_EXPLICITपूर्ण,
	अणुOpt_noload, EXT4_MOUNT_NOLOAD, MOPT_NO_EXT2 | MOPT_SETपूर्ण,
	अणुOpt_err_panic, EXT4_MOUNT_ERRORS_PANIC, MOPT_SET | MOPT_CLEAR_ERRपूर्ण,
	अणुOpt_err_ro, EXT4_MOUNT_ERRORS_RO, MOPT_SET | MOPT_CLEAR_ERRपूर्ण,
	अणुOpt_err_cont, EXT4_MOUNT_ERRORS_CONT, MOPT_SET | MOPT_CLEAR_ERRपूर्ण,
	अणुOpt_data_err_पात, EXT4_MOUNT_DATA_ERR_ABORT,
	 MOPT_NO_EXT2पूर्ण,
	अणुOpt_data_err_ignore, EXT4_MOUNT_DATA_ERR_ABORT,
	 MOPT_NO_EXT2पूर्ण,
	अणुOpt_barrier, EXT4_MOUNT_BARRIER, MOPT_SETपूर्ण,
	अणुOpt_nobarrier, EXT4_MOUNT_BARRIER, MOPT_CLEARपूर्ण,
	अणुOpt_noस्वतः_da_alloc, EXT4_MOUNT_NO_AUTO_DA_ALLOC, MOPT_SETपूर्ण,
	अणुOpt_स्वतः_da_alloc, EXT4_MOUNT_NO_AUTO_DA_ALLOC, MOPT_CLEARपूर्ण,
	अणुOpt_noinit_itable, EXT4_MOUNT_INIT_INODE_TABLE, MOPT_CLEARपूर्ण,
	अणुOpt_commit, 0, MOPT_GTE0पूर्ण,
	अणुOpt_max_batch_समय, 0, MOPT_GTE0पूर्ण,
	अणुOpt_min_batch_समय, 0, MOPT_GTE0पूर्ण,
	अणुOpt_inode_पढ़ोahead_blks, 0, MOPT_GTE0पूर्ण,
	अणुOpt_init_itable, 0, MOPT_GTE0पूर्ण,
	अणुOpt_dax, EXT4_MOUNT_DAX_ALWAYS, MOPT_SET | MOPT_SKIPपूर्ण,
	अणुOpt_dax_always, EXT4_MOUNT_DAX_ALWAYS,
		MOPT_EXT4_ONLY | MOPT_SET | MOPT_SKIPपूर्ण,
	अणुOpt_dax_inode, EXT4_MOUNT2_DAX_INODE,
		MOPT_EXT4_ONLY | MOPT_SET | MOPT_SKIPपूर्ण,
	अणुOpt_dax_never, EXT4_MOUNT2_DAX_NEVER,
		MOPT_EXT4_ONLY | MOPT_SET | MOPT_SKIPपूर्ण,
	अणुOpt_stripe, 0, MOPT_GTE0पूर्ण,
	अणुOpt_resuid, 0, MOPT_GTE0पूर्ण,
	अणुOpt_resgid, 0, MOPT_GTE0पूर्ण,
	अणुOpt_journal_dev, 0, MOPT_NO_EXT2 | MOPT_GTE0पूर्ण,
	अणुOpt_journal_path, 0, MOPT_NO_EXT2 | MOPT_STRINGपूर्ण,
	अणुOpt_journal_ioprio, 0, MOPT_NO_EXT2 | MOPT_GTE0पूर्ण,
	अणुOpt_data_journal, EXT4_MOUNT_JOURNAL_DATA, MOPT_NO_EXT2 | MOPT_DATAJपूर्ण,
	अणुOpt_data_ordered, EXT4_MOUNT_ORDERED_DATA, MOPT_NO_EXT2 | MOPT_DATAJपूर्ण,
	अणुOpt_data_ग_लिखोback, EXT4_MOUNT_WRITEBACK_DATA,
	 MOPT_NO_EXT2 | MOPT_DATAJपूर्ण,
	अणुOpt_user_xattr, EXT4_MOUNT_XATTR_USER, MOPT_SETपूर्ण,
	अणुOpt_nouser_xattr, EXT4_MOUNT_XATTR_USER, MOPT_CLEARपूर्ण,
#अगर_घोषित CONFIG_EXT4_FS_POSIX_ACL
	अणुOpt_acl, EXT4_MOUNT_POSIX_ACL, MOPT_SETपूर्ण,
	अणुOpt_noacl, EXT4_MOUNT_POSIX_ACL, MOPT_CLEARपूर्ण,
#अन्यथा
	अणुOpt_acl, 0, MOPT_NOSUPPORTपूर्ण,
	अणुOpt_noacl, 0, MOPT_NOSUPPORTपूर्ण,
#पूर्ण_अगर
	अणुOpt_nouid32, EXT4_MOUNT_NO_UID32, MOPT_SETपूर्ण,
	अणुOpt_debug, EXT4_MOUNT_DEBUG, MOPT_SETपूर्ण,
	अणुOpt_debug_want_extra_isize, 0, MOPT_GTE0पूर्ण,
	अणुOpt_quota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_USRQUOTA, MOPT_SET | MOPT_Qपूर्ण,
	अणुOpt_usrquota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_USRQUOTA,
							MOPT_SET | MOPT_Qपूर्ण,
	अणुOpt_grpquota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_GRPQUOTA,
							MOPT_SET | MOPT_Qपूर्ण,
	अणुOpt_prjquota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_PRJQUOTA,
							MOPT_SET | MOPT_Qपूर्ण,
	अणुOpt_noquota, (EXT4_MOUNT_QUOTA | EXT4_MOUNT_USRQUOTA |
		       EXT4_MOUNT_GRPQUOTA | EXT4_MOUNT_PRJQUOTA),
							MOPT_CLEAR | MOPT_Qपूर्ण,
	अणुOpt_usrjquota, 0, MOPT_Q | MOPT_STRINGपूर्ण,
	अणुOpt_grpjquota, 0, MOPT_Q | MOPT_STRINGपूर्ण,
	अणुOpt_offusrjquota, 0, MOPT_Qपूर्ण,
	अणुOpt_offgrpjquota, 0, MOPT_Qपूर्ण,
	अणुOpt_jqfmt_vfsold, QFMT_VFS_OLD, MOPT_QFMTपूर्ण,
	अणुOpt_jqfmt_vfsv0, QFMT_VFS_V0, MOPT_QFMTपूर्ण,
	अणुOpt_jqfmt_vfsv1, QFMT_VFS_V1, MOPT_QFMTपूर्ण,
	अणुOpt_max_dir_size_kb, 0, MOPT_GTE0पूर्ण,
	अणुOpt_test_dummy_encryption, 0, MOPT_STRINGपूर्ण,
	अणुOpt_nombcache, EXT4_MOUNT_NO_MBCACHE, MOPT_SETपूर्ण,
	अणुOpt_no_prefetch_block_biपंचांगaps, EXT4_MOUNT_NO_PREFETCH_BLOCK_BITMAPS,
	 MOPT_SETपूर्ण,
	अणुOpt_mb_optimize_scan, EXT4_MOUNT2_MB_OPTIMIZE_SCAN, MOPT_GTE0पूर्ण,
#अगर_घोषित CONFIG_EXT4_DEBUG
	अणुOpt_fc_debug_क्रमce, EXT4_MOUNT2_JOURNAL_FAST_COMMIT,
	 MOPT_SET | MOPT_2 | MOPT_EXT4_ONLYपूर्ण,
	अणुOpt_fc_debug_max_replay, 0, MOPT_GTE0पूर्ण,
#पूर्ण_अगर
	अणुOpt_err, 0, 0पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_UNICODE
अटल स्थिर काष्ठा ext4_sb_encodings अणु
	__u16 magic;
	अक्षर *name;
	अक्षर *version;
पूर्ण ext4_sb_encoding_map[] = अणु
	अणुEXT4_ENC_UTF8_12_1, "utf8", "12.1.0"पूर्ण,
पूर्ण;

अटल पूर्णांक ext4_sb_पढ़ो_encoding(स्थिर काष्ठा ext4_super_block *es,
				 स्थिर काष्ठा ext4_sb_encodings **encoding,
				 __u16 *flags)
अणु
	__u16 magic = le16_to_cpu(es->s_encoding);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ext4_sb_encoding_map); i++)
		अगर (magic == ext4_sb_encoding_map[i].magic)
			अवरोध;

	अगर (i >= ARRAY_SIZE(ext4_sb_encoding_map))
		वापस -EINVAL;

	*encoding = &ext4_sb_encoding_map[i];
	*flags = le16_to_cpu(es->s_encoding_flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ext4_set_test_dummy_encryption(काष्ठा super_block *sb,
					  स्थिर अक्षर *opt,
					  स्थिर substring_t *arg,
					  bool is_remount)
अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक err;

	/*
	 * This mount option is just क्रम testing, and it's not worthजबतक to
	 * implement the extra complनिकासy (e.g. RCU protection) that would be
	 * needed to allow it to be set or changed during remount.  We करो allow
	 * it to be specअगरied during remount, but only अगर there is no change.
	 */
	अगर (is_remount && !sbi->s_dummy_enc_policy.policy) अणु
		ext4_msg(sb, KERN_WARNING,
			 "Can't set test_dummy_encryption on remount");
		वापस -1;
	पूर्ण
	err = fscrypt_set_test_dummy_encryption(sb, arg->from,
						&sbi->s_dummy_enc_policy);
	अगर (err) अणु
		अगर (err == -EEXIST)
			ext4_msg(sb, KERN_WARNING,
				 "Can't change test_dummy_encryption on remount");
		अन्यथा अगर (err == -EINVAL)
			ext4_msg(sb, KERN_WARNING,
				 "Value of option \"%s\" is unrecognized", opt);
		अन्यथा
			ext4_msg(sb, KERN_WARNING,
				 "Error processing option \"%s\" [%d]",
				 opt, err);
		वापस -1;
	पूर्ण
	ext4_msg(sb, KERN_WARNING, "Test dummy encryption mode enabled");
#अन्यथा
	ext4_msg(sb, KERN_WARNING,
		 "Test dummy encryption mount option ignored");
#पूर्ण_अगर
	वापस 1;
पूर्ण

काष्ठा ext4_parsed_options अणु
	अचिन्हित दीर्घ journal_devnum;
	अचिन्हित पूर्णांक journal_ioprio;
	पूर्णांक mb_optimize_scan;
पूर्ण;

अटल पूर्णांक handle_mount_opt(काष्ठा super_block *sb, अक्षर *opt, पूर्णांक token,
			    substring_t *args, काष्ठा ext4_parsed_options *parsed_opts,
			    पूर्णांक is_remount)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	स्थिर काष्ठा mount_opts *m;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक arg = 0;

#अगर_घोषित CONFIG_QUOTA
	अगर (token == Opt_usrjquota)
		वापस set_qf_name(sb, USRQUOTA, &args[0]);
	अन्यथा अगर (token == Opt_grpjquota)
		वापस set_qf_name(sb, GRPQUOTA, &args[0]);
	अन्यथा अगर (token == Opt_offusrjquota)
		वापस clear_qf_name(sb, USRQUOTA);
	अन्यथा अगर (token == Opt_offgrpjquota)
		वापस clear_qf_name(sb, GRPQUOTA);
#पूर्ण_अगर
	चयन (token) अणु
	हाल Opt_noacl:
	हाल Opt_nouser_xattr:
		ext4_msg(sb, KERN_WARNING, deprecated_msg, opt, "3.5");
		अवरोध;
	हाल Opt_sb:
		वापस 1;	/* handled by get_sb_block() */
	हाल Opt_हटाओd:
		ext4_msg(sb, KERN_WARNING, "Ignoring removed %s option", opt);
		वापस 1;
	हाल Opt_पात:
		ext4_set_mount_flag(sb, EXT4_MF_FS_ABORTED);
		वापस 1;
	हाल Opt_i_version:
		sb->s_flags |= SB_I_VERSION;
		वापस 1;
	हाल Opt_lazyसमय:
		sb->s_flags |= SB_LAZYTIME;
		वापस 1;
	हाल Opt_nolazyसमय:
		sb->s_flags &= ~SB_LAZYTIME;
		वापस 1;
	हाल Opt_अंतरभूतcrypt:
#अगर_घोषित CONFIG_FS_ENCRYPTION_INLINE_CRYPT
		sb->s_flags |= SB_INLINECRYPT;
#अन्यथा
		ext4_msg(sb, KERN_ERR, "inline encryption not supported");
#पूर्ण_अगर
		वापस 1;
	पूर्ण

	क्रम (m = ext4_mount_opts; m->token != Opt_err; m++)
		अगर (token == m->token)
			अवरोध;

	अगर (m->token == Opt_err) अणु
		ext4_msg(sb, KERN_ERR, "Unrecognized mount option \"%s\" "
			 "or missing value", opt);
		वापस -1;
	पूर्ण

	अगर ((m->flags & MOPT_NO_EXT2) && IS_EXT2_SB(sb)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Mount option \"%s\" incompatible with ext2", opt);
		वापस -1;
	पूर्ण
	अगर ((m->flags & MOPT_NO_EXT3) && IS_EXT3_SB(sb)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Mount option \"%s\" incompatible with ext3", opt);
		वापस -1;
	पूर्ण

	अगर (args->from && !(m->flags & MOPT_STRING) && match_पूर्णांक(args, &arg))
		वापस -1;
	अगर (args->from && (m->flags & MOPT_GTE0) && (arg < 0))
		वापस -1;
	अगर (m->flags & MOPT_EXPLICIT) अणु
		अगर (m->mount_opt & EXT4_MOUNT_DELALLOC) अणु
			set_opt2(sb, EXPLICIT_DELALLOC);
		पूर्ण अन्यथा अगर (m->mount_opt & EXT4_MOUNT_JOURNAL_CHECKSUM) अणु
			set_opt2(sb, EXPLICIT_JOURNAL_CHECKSUM);
		पूर्ण अन्यथा
			वापस -1;
	पूर्ण
	अगर (m->flags & MOPT_CLEAR_ERR)
		clear_opt(sb, ERRORS_MASK);
	अगर (token == Opt_noquota && sb_any_quota_loaded(sb)) अणु
		ext4_msg(sb, KERN_ERR, "Cannot change quota "
			 "options when quota turned on");
		वापस -1;
	पूर्ण

	अगर (m->flags & MOPT_NOSUPPORT) अणु
		ext4_msg(sb, KERN_ERR, "%s option not supported", opt);
	पूर्ण अन्यथा अगर (token == Opt_commit) अणु
		अगर (arg == 0)
			arg = JBD2_DEFAULT_MAX_COMMIT_AGE;
		अन्यथा अगर (arg > पूर्णांक_उच्च / HZ) अणु
			ext4_msg(sb, KERN_ERR,
				 "Invalid commit interval %d, "
				 "must be smaller than %d",
				 arg, पूर्णांक_उच्च / HZ);
			वापस -1;
		पूर्ण
		sbi->s_commit_पूर्णांकerval = HZ * arg;
	पूर्ण अन्यथा अगर (token == Opt_debug_want_extra_isize) अणु
		अगर ((arg & 1) ||
		    (arg < 4) ||
		    (arg > (sbi->s_inode_size - EXT4_GOOD_OLD_INODE_SIZE))) अणु
			ext4_msg(sb, KERN_ERR,
				 "Invalid want_extra_isize %d", arg);
			वापस -1;
		पूर्ण
		sbi->s_want_extra_isize = arg;
	पूर्ण अन्यथा अगर (token == Opt_max_batch_समय) अणु
		sbi->s_max_batch_समय = arg;
	पूर्ण अन्यथा अगर (token == Opt_min_batch_समय) अणु
		sbi->s_min_batch_समय = arg;
	पूर्ण अन्यथा अगर (token == Opt_inode_पढ़ोahead_blks) अणु
		अगर (arg && (arg > (1 << 30) || !is_घातer_of_2(arg))) अणु
			ext4_msg(sb, KERN_ERR,
				 "EXT4-fs: inode_readahead_blks must be "
				 "0 or a घातer of 2 smaller than 2^31");
			वापस -1;
		पूर्ण
		sbi->s_inode_पढ़ोahead_blks = arg;
	पूर्ण अन्यथा अगर (token == Opt_init_itable) अणु
		set_opt(sb, INIT_INODE_TABLE);
		अगर (!args->from)
			arg = EXT4_DEF_LI_WAIT_MULT;
		sbi->s_li_रुको_mult = arg;
	पूर्ण अन्यथा अगर (token == Opt_max_dir_size_kb) अणु
		sbi->s_max_dir_size_kb = arg;
#अगर_घोषित CONFIG_EXT4_DEBUG
	पूर्ण अन्यथा अगर (token == Opt_fc_debug_max_replay) अणु
		sbi->s_fc_debug_max_replay = arg;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (token == Opt_stripe) अणु
		sbi->s_stripe = arg;
	पूर्ण अन्यथा अगर (token == Opt_resuid) अणु
		uid = make_kuid(current_user_ns(), arg);
		अगर (!uid_valid(uid)) अणु
			ext4_msg(sb, KERN_ERR, "Invalid uid value %d", arg);
			वापस -1;
		पूर्ण
		sbi->s_resuid = uid;
	पूर्ण अन्यथा अगर (token == Opt_resgid) अणु
		gid = make_kgid(current_user_ns(), arg);
		अगर (!gid_valid(gid)) अणु
			ext4_msg(sb, KERN_ERR, "Invalid gid value %d", arg);
			वापस -1;
		पूर्ण
		sbi->s_resgid = gid;
	पूर्ण अन्यथा अगर (token == Opt_journal_dev) अणु
		अगर (is_remount) अणु
			ext4_msg(sb, KERN_ERR,
				 "Cannot specify journal on remount");
			वापस -1;
		पूर्ण
		parsed_opts->journal_devnum = arg;
	पूर्ण अन्यथा अगर (token == Opt_journal_path) अणु
		अक्षर *journal_path;
		काष्ठा inode *journal_inode;
		काष्ठा path path;
		पूर्णांक error;

		अगर (is_remount) अणु
			ext4_msg(sb, KERN_ERR,
				 "Cannot specify journal on remount");
			वापस -1;
		पूर्ण
		journal_path = match_strdup(&args[0]);
		अगर (!journal_path) अणु
			ext4_msg(sb, KERN_ERR, "error: could not dup "
				"journal device string");
			वापस -1;
		पूर्ण

		error = kern_path(journal_path, LOOKUP_FOLLOW, &path);
		अगर (error) अणु
			ext4_msg(sb, KERN_ERR, "error: could not find "
				"journal device path: error %d", error);
			kमुक्त(journal_path);
			वापस -1;
		पूर्ण

		journal_inode = d_inode(path.dentry);
		अगर (!S_ISBLK(journal_inode->i_mode)) अणु
			ext4_msg(sb, KERN_ERR, "error: journal path %s "
				"is not a block device", journal_path);
			path_put(&path);
			kमुक्त(journal_path);
			वापस -1;
		पूर्ण

		parsed_opts->journal_devnum = new_encode_dev(journal_inode->i_rdev);
		path_put(&path);
		kमुक्त(journal_path);
	पूर्ण अन्यथा अगर (token == Opt_journal_ioprio) अणु
		अगर (arg > 7) अणु
			ext4_msg(sb, KERN_ERR, "Invalid journal IO priority"
				 " (must be 0-7)");
			वापस -1;
		पूर्ण
		parsed_opts->journal_ioprio =
			IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, arg);
	पूर्ण अन्यथा अगर (token == Opt_test_dummy_encryption) अणु
		वापस ext4_set_test_dummy_encryption(sb, opt, &args[0],
						      is_remount);
	पूर्ण अन्यथा अगर (m->flags & MOPT_DATAJ) अणु
		अगर (is_remount) अणु
			अगर (!sbi->s_journal)
				ext4_msg(sb, KERN_WARNING, "Remounting file system with no journal so ignoring journalled data option");
			अन्यथा अगर (test_opt(sb, DATA_FLAGS) != m->mount_opt) अणु
				ext4_msg(sb, KERN_ERR,
					 "Cannot change data mode on remount");
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			clear_opt(sb, DATA_FLAGS);
			sbi->s_mount_opt |= m->mount_opt;
		पूर्ण
#अगर_घोषित CONFIG_QUOTA
	पूर्ण अन्यथा अगर (m->flags & MOPT_QFMT) अणु
		अगर (sb_any_quota_loaded(sb) &&
		    sbi->s_jquota_fmt != m->mount_opt) अणु
			ext4_msg(sb, KERN_ERR, "Cannot change journaled "
				 "quota options when quota turned on");
			वापस -1;
		पूर्ण
		अगर (ext4_has_feature_quota(sb)) अणु
			ext4_msg(sb, KERN_INFO,
				 "Quota format mount options ignored "
				 "when QUOTA feature is enabled");
			वापस 1;
		पूर्ण
		sbi->s_jquota_fmt = m->mount_opt;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (token == Opt_dax || token == Opt_dax_always ||
		   token == Opt_dax_inode || token == Opt_dax_never) अणु
#अगर_घोषित CONFIG_FS_DAX
		चयन (token) अणु
		हाल Opt_dax:
		हाल Opt_dax_always:
			अगर (is_remount &&
			    (!(sbi->s_mount_opt & EXT4_MOUNT_DAX_ALWAYS) ||
			     (sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_NEVER))) अणु
			fail_dax_change_remount:
				ext4_msg(sb, KERN_ERR, "can't change "
					 "dax mount option while remounting");
				वापस -1;
			पूर्ण
			अगर (is_remount &&
			    (test_opt(sb, DATA_FLAGS) ==
			     EXT4_MOUNT_JOURNAL_DATA)) अणु
				    ext4_msg(sb, KERN_ERR, "can't mount with "
					     "both data=journal and dax");
				    वापस -1;
			पूर्ण
			ext4_msg(sb, KERN_WARNING,
				"DAX enabled. Warning: EXPERIMENTAL, use at your own risk");
			sbi->s_mount_opt |= EXT4_MOUNT_DAX_ALWAYS;
			sbi->s_mount_opt2 &= ~EXT4_MOUNT2_DAX_NEVER;
			अवरोध;
		हाल Opt_dax_never:
			अगर (is_remount &&
			    (!(sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_NEVER) ||
			     (sbi->s_mount_opt & EXT4_MOUNT_DAX_ALWAYS)))
				जाओ fail_dax_change_remount;
			sbi->s_mount_opt2 |= EXT4_MOUNT2_DAX_NEVER;
			sbi->s_mount_opt &= ~EXT4_MOUNT_DAX_ALWAYS;
			अवरोध;
		हाल Opt_dax_inode:
			अगर (is_remount &&
			    ((sbi->s_mount_opt & EXT4_MOUNT_DAX_ALWAYS) ||
			     (sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_NEVER) ||
			     !(sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_INODE)))
				जाओ fail_dax_change_remount;
			sbi->s_mount_opt &= ~EXT4_MOUNT_DAX_ALWAYS;
			sbi->s_mount_opt2 &= ~EXT4_MOUNT2_DAX_NEVER;
			/* Strictly क्रम prपूर्णांकing options */
			sbi->s_mount_opt2 |= EXT4_MOUNT2_DAX_INODE;
			अवरोध;
		पूर्ण
#अन्यथा
		ext4_msg(sb, KERN_INFO, "dax option not supported");
		sbi->s_mount_opt2 |= EXT4_MOUNT2_DAX_NEVER;
		sbi->s_mount_opt &= ~EXT4_MOUNT_DAX_ALWAYS;
		वापस -1;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (token == Opt_data_err_पात) अणु
		sbi->s_mount_opt |= m->mount_opt;
	पूर्ण अन्यथा अगर (token == Opt_data_err_ignore) अणु
		sbi->s_mount_opt &= ~m->mount_opt;
	पूर्ण अन्यथा अगर (token == Opt_mb_optimize_scan) अणु
		अगर (arg != 0 && arg != 1) अणु
			ext4_msg(sb, KERN_WARNING,
				 "mb_optimize_scan should be set to 0 or 1.");
			वापस -1;
		पूर्ण
		parsed_opts->mb_optimize_scan = arg;
	पूर्ण अन्यथा अणु
		अगर (!args->from)
			arg = 1;
		अगर (m->flags & MOPT_CLEAR)
			arg = !arg;
		अन्यथा अगर (unlikely(!(m->flags & MOPT_SET))) अणु
			ext4_msg(sb, KERN_WARNING,
				 "buggy handling of option %s", opt);
			WARN_ON(1);
			वापस -1;
		पूर्ण
		अगर (m->flags & MOPT_2) अणु
			अगर (arg != 0)
				sbi->s_mount_opt2 |= m->mount_opt;
			अन्यथा
				sbi->s_mount_opt2 &= ~m->mount_opt;
		पूर्ण अन्यथा अणु
			अगर (arg != 0)
				sbi->s_mount_opt |= m->mount_opt;
			अन्यथा
				sbi->s_mount_opt &= ~m->mount_opt;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक parse_options(अक्षर *options, काष्ठा super_block *sb,
			 काष्ठा ext4_parsed_options *ret_opts,
			 पूर्णांक is_remount)
अणु
	काष्ठा ext4_sb_info __maybe_unused *sbi = EXT4_SB(sb);
	अक्षर *p, __maybe_unused *usr_qf_name, __maybe_unused *grp_qf_name;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक token;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;
		/*
		 * Initialize args काष्ठा so we know whether arg was
		 * found; some options take optional arguments.
		 */
		args[0].to = args[0].from = शून्य;
		token = match_token(p, tokens, args);
		अगर (handle_mount_opt(sb, p, token, args, ret_opts,
				     is_remount) < 0)
			वापस 0;
	पूर्ण
#अगर_घोषित CONFIG_QUOTA
	/*
	 * We करो the test below only क्रम project quotas. 'usrquota' and
	 * 'grpquota' mount options are allowed even without quota feature
	 * to support legacy quotas in quota files.
	 */
	अगर (test_opt(sb, PRJQUOTA) && !ext4_has_feature_project(sb)) अणु
		ext4_msg(sb, KERN_ERR, "Project quota feature not enabled. "
			 "Cannot enable project quota enforcement.");
		वापस 0;
	पूर्ण
	usr_qf_name = get_qf_name(sb, sbi, USRQUOTA);
	grp_qf_name = get_qf_name(sb, sbi, GRPQUOTA);
	अगर (usr_qf_name || grp_qf_name) अणु
		अगर (test_opt(sb, USRQUOTA) && usr_qf_name)
			clear_opt(sb, USRQUOTA);

		अगर (test_opt(sb, GRPQUOTA) && grp_qf_name)
			clear_opt(sb, GRPQUOTA);

		अगर (test_opt(sb, GRPQUOTA) || test_opt(sb, USRQUOTA)) अणु
			ext4_msg(sb, KERN_ERR, "old and new quota "
					"format mixing");
			वापस 0;
		पूर्ण

		अगर (!sbi->s_jquota_fmt) अणु
			ext4_msg(sb, KERN_ERR, "journaled quota format "
					"not specified");
			वापस 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (test_opt(sb, DIOREAD_NOLOCK)) अणु
		पूर्णांक blocksize =
			BLOCK_SIZE << le32_to_cpu(sbi->s_es->s_log_block_size);
		अगर (blocksize < PAGE_SIZE)
			ext4_msg(sb, KERN_WARNING, "Warning: mounting with an "
				 "experimental mount option 'dioread_nolock' "
				 "for blocksize < PAGE_SIZE");
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम ext4_show_quota_options(काष्ठा seq_file *seq,
					   काष्ठा super_block *sb)
अणु
#अगर defined(CONFIG_QUOTA)
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अक्षर *usr_qf_name, *grp_qf_name;

	अगर (sbi->s_jquota_fmt) अणु
		अक्षर *fmtname = "";

		चयन (sbi->s_jquota_fmt) अणु
		हाल QFMT_VFS_OLD:
			fmtname = "vfsold";
			अवरोध;
		हाल QFMT_VFS_V0:
			fmtname = "vfsv0";
			अवरोध;
		हाल QFMT_VFS_V1:
			fmtname = "vfsv1";
			अवरोध;
		पूर्ण
		seq_म_लिखो(seq, ",jqfmt=%s", fmtname);
	पूर्ण

	rcu_पढ़ो_lock();
	usr_qf_name = rcu_dereference(sbi->s_qf_names[USRQUOTA]);
	grp_qf_name = rcu_dereference(sbi->s_qf_names[GRPQUOTA]);
	अगर (usr_qf_name)
		seq_show_option(seq, "usrjquota", usr_qf_name);
	अगर (grp_qf_name)
		seq_show_option(seq, "grpjquota", grp_qf_name);
	rcu_पढ़ो_unlock();
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर *token2str(पूर्णांक token)
अणु
	स्थिर काष्ठा match_token *t;

	क्रम (t = tokens; t->token != Opt_err; t++)
		अगर (t->token == token && !म_अक्षर(t->pattern, '='))
			अवरोध;
	वापस t->pattern;
पूर्ण

/*
 * Show an option अगर
 *  - it's set to a non-शेष value OR
 *  - अगर the per-sb शेष is dअगरferent from the global शेष
 */
अटल पूर्णांक _ext4_show_options(काष्ठा seq_file *seq, काष्ठा super_block *sb,
			      पूर्णांक nodefs)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	पूर्णांक def_errors, def_mount_opt = sbi->s_def_mount_opt;
	स्थिर काष्ठा mount_opts *m;
	अक्षर sep = nodefs ? '\n' : ',';

#घोषणा SEQ_OPTS_PUTS(str) seq_म_लिखो(seq, "%c" str, sep)
#घोषणा SEQ_OPTS_PRINT(str, arg) seq_म_लिखो(seq, "%c" str, sep, arg)

	अगर (sbi->s_sb_block != 1)
		SEQ_OPTS_PRINT("sb=%llu", sbi->s_sb_block);

	क्रम (m = ext4_mount_opts; m->token != Opt_err; m++) अणु
		पूर्णांक want_set = m->flags & MOPT_SET;
		अगर (((m->flags & (MOPT_SET|MOPT_CLEAR)) == 0) ||
		    (m->flags & MOPT_CLEAR_ERR) || m->flags & MOPT_SKIP)
			जारी;
		अगर (!nodefs && !(m->mount_opt & (sbi->s_mount_opt ^ def_mount_opt)))
			जारी; /* skip अगर same as the शेष */
		अगर ((want_set &&
		     (sbi->s_mount_opt & m->mount_opt) != m->mount_opt) ||
		    (!want_set && (sbi->s_mount_opt & m->mount_opt)))
			जारी; /* select Opt_noFoo vs Opt_Foo */
		SEQ_OPTS_PRINT("%s", token2str(m->token));
	पूर्ण

	अगर (nodefs || !uid_eq(sbi->s_resuid, make_kuid(&init_user_ns, EXT4_DEF_RESUID)) ||
	    le16_to_cpu(es->s_def_resuid) != EXT4_DEF_RESUID)
		SEQ_OPTS_PRINT("resuid=%u",
				from_kuid_munged(&init_user_ns, sbi->s_resuid));
	अगर (nodefs || !gid_eq(sbi->s_resgid, make_kgid(&init_user_ns, EXT4_DEF_RESGID)) ||
	    le16_to_cpu(es->s_def_resgid) != EXT4_DEF_RESGID)
		SEQ_OPTS_PRINT("resgid=%u",
				from_kgid_munged(&init_user_ns, sbi->s_resgid));
	def_errors = nodefs ? -1 : le16_to_cpu(es->s_errors);
	अगर (test_opt(sb, ERRORS_RO) && def_errors != EXT4_ERRORS_RO)
		SEQ_OPTS_PUTS("errors=remount-ro");
	अगर (test_opt(sb, ERRORS_CONT) && def_errors != EXT4_ERRORS_CONTINUE)
		SEQ_OPTS_PUTS("errors=continue");
	अगर (test_opt(sb, ERRORS_PANIC) && def_errors != EXT4_ERRORS_PANIC)
		SEQ_OPTS_PUTS("errors=panic");
	अगर (nodefs || sbi->s_commit_पूर्णांकerval != JBD2_DEFAULT_MAX_COMMIT_AGE*HZ)
		SEQ_OPTS_PRINT("commit=%lu", sbi->s_commit_पूर्णांकerval / HZ);
	अगर (nodefs || sbi->s_min_batch_समय != EXT4_DEF_MIN_BATCH_TIME)
		SEQ_OPTS_PRINT("min_batch_time=%u", sbi->s_min_batch_समय);
	अगर (nodefs || sbi->s_max_batch_समय != EXT4_DEF_MAX_BATCH_TIME)
		SEQ_OPTS_PRINT("max_batch_time=%u", sbi->s_max_batch_समय);
	अगर (sb->s_flags & SB_I_VERSION)
		SEQ_OPTS_PUTS("i_version");
	अगर (nodefs || sbi->s_stripe)
		SEQ_OPTS_PRINT("stripe=%lu", sbi->s_stripe);
	अगर (nodefs || EXT4_MOUNT_DATA_FLAGS &
			(sbi->s_mount_opt ^ def_mount_opt)) अणु
		अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA)
			SEQ_OPTS_PUTS("data=journal");
		अन्यथा अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_ORDERED_DATA)
			SEQ_OPTS_PUTS("data=ordered");
		अन्यथा अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_WRITEBACK_DATA)
			SEQ_OPTS_PUTS("data=writeback");
	पूर्ण
	अगर (nodefs ||
	    sbi->s_inode_पढ़ोahead_blks != EXT4_DEF_INODE_READAHEAD_BLKS)
		SEQ_OPTS_PRINT("inode_readahead_blks=%u",
			       sbi->s_inode_पढ़ोahead_blks);

	अगर (test_opt(sb, INIT_INODE_TABLE) && (nodefs ||
		       (sbi->s_li_रुको_mult != EXT4_DEF_LI_WAIT_MULT)))
		SEQ_OPTS_PRINT("init_itable=%u", sbi->s_li_रुको_mult);
	अगर (nodefs || sbi->s_max_dir_size_kb)
		SEQ_OPTS_PRINT("max_dir_size_kb=%u", sbi->s_max_dir_size_kb);
	अगर (test_opt(sb, DATA_ERR_ABORT))
		SEQ_OPTS_PUTS("data_err=abort");

	fscrypt_show_test_dummy_encryption(seq, sep, sb);

	अगर (sb->s_flags & SB_INLINECRYPT)
		SEQ_OPTS_PUTS("inlinecrypt");

	अगर (test_opt(sb, DAX_ALWAYS)) अणु
		अगर (IS_EXT2_SB(sb))
			SEQ_OPTS_PUTS("dax");
		अन्यथा
			SEQ_OPTS_PUTS("dax=always");
	पूर्ण अन्यथा अगर (test_opt2(sb, DAX_NEVER)) अणु
		SEQ_OPTS_PUTS("dax=never");
	पूर्ण अन्यथा अगर (test_opt2(sb, DAX_INODE)) अणु
		SEQ_OPTS_PUTS("dax=inode");
	पूर्ण
	ext4_show_quota_options(seq, sb);
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	वापस _ext4_show_options(seq, root->d_sb, 0);
पूर्ण

पूर्णांक ext4_seq_options_show(काष्ठा seq_file *seq, व्योम *offset)
अणु
	काष्ठा super_block *sb = seq->निजी;
	पूर्णांक rc;

	seq_माला_दो(seq, sb_rकरोnly(sb) ? "ro" : "rw");
	rc = _ext4_show_options(seq, sb, 1);
	seq_माला_दो(seq, "\n");
	वापस rc;
पूर्ण

अटल पूर्णांक ext4_setup_super(काष्ठा super_block *sb, काष्ठा ext4_super_block *es,
			    पूर्णांक पढ़ो_only)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक err = 0;

	अगर (le32_to_cpu(es->s_rev_level) > EXT4_MAX_SUPP_REV) अणु
		ext4_msg(sb, KERN_ERR, "revision level too high, "
			 "forcing read-only mode");
		err = -EROFS;
		जाओ करोne;
	पूर्ण
	अगर (पढ़ो_only)
		जाओ करोne;
	अगर (!(sbi->s_mount_state & EXT4_VALID_FS))
		ext4_msg(sb, KERN_WARNING, "warning: mounting unchecked fs, "
			 "running e2fsck is recommended");
	अन्यथा अगर (sbi->s_mount_state & EXT4_ERROR_FS)
		ext4_msg(sb, KERN_WARNING,
			 "warning: mounting fs with errors, "
			 "running e2fsck is recommended");
	अन्यथा अगर ((__s16) le16_to_cpu(es->s_max_mnt_count) > 0 &&
		 le16_to_cpu(es->s_mnt_count) >=
		 (अचिन्हित लघु) (__s16) le16_to_cpu(es->s_max_mnt_count))
		ext4_msg(sb, KERN_WARNING,
			 "warning: maximal mount count reached, "
			 "running e2fsck is recommended");
	अन्यथा अगर (le32_to_cpu(es->s_checkपूर्णांकerval) &&
		 (ext4_get_tstamp(es, s_lastcheck) +
		  le32_to_cpu(es->s_checkपूर्णांकerval) <= kसमय_get_real_seconds()))
		ext4_msg(sb, KERN_WARNING,
			 "warning: checktime reached, "
			 "running e2fsck is recommended");
	अगर (!sbi->s_journal)
		es->s_state &= cpu_to_le16(~EXT4_VALID_FS);
	अगर (!(__s16) le16_to_cpu(es->s_max_mnt_count))
		es->s_max_mnt_count = cpu_to_le16(EXT4_DFL_MAX_MNT_COUNT);
	le16_add_cpu(&es->s_mnt_count, 1);
	ext4_update_tstamp(es, s_mसमय);
	अगर (sbi->s_journal)
		ext4_set_feature_journal_needs_recovery(sb);

	err = ext4_commit_super(sb);
करोne:
	अगर (test_opt(sb, DEBUG))
		prपूर्णांकk(KERN_INFO "[EXT4 FS bs=%lu, gc=%u, "
				"bpg=%lu, ipg=%lu, mo=%04x, mo2=%04x]\n",
			sb->s_blocksize,
			sbi->s_groups_count,
			EXT4_BLOCKS_PER_GROUP(sb),
			EXT4_INODES_PER_GROUP(sb),
			sbi->s_mount_opt, sbi->s_mount_opt2);

	cleancache_init_fs(sb);
	वापस err;
पूर्ण

पूर्णांक ext4_alloc_flex_bg_array(काष्ठा super_block *sb, ext4_group_t ngroup)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा flex_groups **old_groups, **new_groups;
	पूर्णांक size, i, j;

	अगर (!sbi->s_log_groups_per_flex)
		वापस 0;

	size = ext4_flex_group(sbi, ngroup - 1) + 1;
	अगर (size <= sbi->s_flex_groups_allocated)
		वापस 0;

	new_groups = kvzalloc(roundup_घात_of_two(size *
			      माप(*sbi->s_flex_groups)), GFP_KERNEL);
	अगर (!new_groups) अणु
		ext4_msg(sb, KERN_ERR,
			 "not enough memory for %d flex group pointers", size);
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = sbi->s_flex_groups_allocated; i < size; i++) अणु
		new_groups[i] = kvzalloc(roundup_घात_of_two(
					 माप(काष्ठा flex_groups)),
					 GFP_KERNEL);
		अगर (!new_groups[i]) अणु
			क्रम (j = sbi->s_flex_groups_allocated; j < i; j++)
				kvमुक्त(new_groups[j]);
			kvमुक्त(new_groups);
			ext4_msg(sb, KERN_ERR,
				 "not enough memory for %d flex groups", size);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_lock();
	old_groups = rcu_dereference(sbi->s_flex_groups);
	अगर (old_groups)
		स_नकल(new_groups, old_groups,
		       (sbi->s_flex_groups_allocated *
			माप(काष्ठा flex_groups *)));
	rcu_पढ़ो_unlock();
	rcu_assign_poपूर्णांकer(sbi->s_flex_groups, new_groups);
	sbi->s_flex_groups_allocated = size;
	अगर (old_groups)
		ext4_kvमुक्त_array_rcu(old_groups);
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_fill_flex_info(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_group_desc *gdp = शून्य;
	काष्ठा flex_groups *fg;
	ext4_group_t flex_group;
	पूर्णांक i, err;

	sbi->s_log_groups_per_flex = sbi->s_es->s_log_groups_per_flex;
	अगर (sbi->s_log_groups_per_flex < 1 || sbi->s_log_groups_per_flex > 31) अणु
		sbi->s_log_groups_per_flex = 0;
		वापस 1;
	पूर्ण

	err = ext4_alloc_flex_bg_array(sb, sbi->s_groups_count);
	अगर (err)
		जाओ failed;

	क्रम (i = 0; i < sbi->s_groups_count; i++) अणु
		gdp = ext4_get_group_desc(sb, i, शून्य);

		flex_group = ext4_flex_group(sbi, i);
		fg = sbi_array_rcu_deref(sbi, s_flex_groups, flex_group);
		atomic_add(ext4_मुक्त_inodes_count(sb, gdp), &fg->मुक्त_inodes);
		atomic64_add(ext4_मुक्त_group_clusters(sb, gdp),
			     &fg->मुक्त_clusters);
		atomic_add(ext4_used_dirs_count(sb, gdp), &fg->used_dirs);
	पूर्ण

	वापस 1;
failed:
	वापस 0;
पूर्ण

अटल __le16 ext4_group_desc_csum(काष्ठा super_block *sb, __u32 block_group,
				   काष्ठा ext4_group_desc *gdp)
अणु
	पूर्णांक offset = दुरत्व(काष्ठा ext4_group_desc, bg_checksum);
	__u16 crc = 0;
	__le32 le_group = cpu_to_le32(block_group);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (ext4_has_metadata_csum(sbi->s_sb)) अणु
		/* Use new metadata_csum algorithm */
		__u32 csum32;
		__u16 dummy_csum = 0;

		csum32 = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&le_group,
				     माप(le_group));
		csum32 = ext4_chksum(sbi, csum32, (__u8 *)gdp, offset);
		csum32 = ext4_chksum(sbi, csum32, (__u8 *)&dummy_csum,
				     माप(dummy_csum));
		offset += माप(dummy_csum);
		अगर (offset < sbi->s_desc_size)
			csum32 = ext4_chksum(sbi, csum32, (__u8 *)gdp + offset,
					     sbi->s_desc_size - offset);

		crc = csum32 & 0xFFFF;
		जाओ out;
	पूर्ण

	/* old crc16 code */
	अगर (!ext4_has_feature_gdt_csum(sb))
		वापस 0;

	crc = crc16(~0, sbi->s_es->s_uuid, माप(sbi->s_es->s_uuid));
	crc = crc16(crc, (__u8 *)&le_group, माप(le_group));
	crc = crc16(crc, (__u8 *)gdp, offset);
	offset += माप(gdp->bg_checksum); /* skip checksum */
	/* क्रम checksum of काष्ठा ext4_group_desc करो the rest...*/
	अगर (ext4_has_feature_64bit(sb) &&
	    offset < le16_to_cpu(sbi->s_es->s_desc_size))
		crc = crc16(crc, (__u8 *)gdp + offset,
			    le16_to_cpu(sbi->s_es->s_desc_size) -
				offset);

out:
	वापस cpu_to_le16(crc);
पूर्ण

पूर्णांक ext4_group_desc_csum_verअगरy(काष्ठा super_block *sb, __u32 block_group,
				काष्ठा ext4_group_desc *gdp)
अणु
	अगर (ext4_has_group_desc_csum(sb) &&
	    (gdp->bg_checksum != ext4_group_desc_csum(sb, block_group, gdp)))
		वापस 0;

	वापस 1;
पूर्ण

व्योम ext4_group_desc_csum_set(काष्ठा super_block *sb, __u32 block_group,
			      काष्ठा ext4_group_desc *gdp)
अणु
	अगर (!ext4_has_group_desc_csum(sb))
		वापस;
	gdp->bg_checksum = ext4_group_desc_csum(sb, block_group, gdp);
पूर्ण

/* Called at mount-समय, super-block is locked */
अटल पूर्णांक ext4_check_descriptors(काष्ठा super_block *sb,
				  ext4_fsblk_t sb_block,
				  ext4_group_t *first_not_zeroed)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t first_block = le32_to_cpu(sbi->s_es->s_first_data_block);
	ext4_fsblk_t last_block;
	ext4_fsblk_t last_bg_block = sb_block + ext4_bg_num_gdb(sb, 0);
	ext4_fsblk_t block_biपंचांगap;
	ext4_fsblk_t inode_biपंचांगap;
	ext4_fsblk_t inode_table;
	पूर्णांक flexbg_flag = 0;
	ext4_group_t i, grp = sbi->s_groups_count;

	अगर (ext4_has_feature_flex_bg(sb))
		flexbg_flag = 1;

	ext4_debug("Checking group descriptors");

	क्रम (i = 0; i < sbi->s_groups_count; i++) अणु
		काष्ठा ext4_group_desc *gdp = ext4_get_group_desc(sb, i, शून्य);

		अगर (i == sbi->s_groups_count - 1 || flexbg_flag)
			last_block = ext4_blocks_count(sbi->s_es) - 1;
		अन्यथा
			last_block = first_block +
				(EXT4_BLOCKS_PER_GROUP(sb) - 1);

		अगर ((grp == sbi->s_groups_count) &&
		   !(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED)))
			grp = i;

		block_biपंचांगap = ext4_block_biपंचांगap(sb, gdp);
		अगर (block_biपंचांगap == sb_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Block bitmap for group %u overlaps "
				 "superblock", i);
			अगर (!sb_rकरोnly(sb))
				वापस 0;
		पूर्ण
		अगर (block_biपंचांगap >= sb_block + 1 &&
		    block_biपंचांगap <= last_bg_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Block bitmap for group %u overlaps "
				 "block group descriptors", i);
			अगर (!sb_rकरोnly(sb))
				वापस 0;
		पूर्ण
		अगर (block_biपंचांगap < first_block || block_biपंचांगap > last_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
			       "Block bitmap for group %u not in group "
			       "(block %llu)!", i, block_biपंचांगap);
			वापस 0;
		पूर्ण
		inode_biपंचांगap = ext4_inode_biपंचांगap(sb, gdp);
		अगर (inode_biपंचांगap == sb_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Inode bitmap for group %u overlaps "
				 "superblock", i);
			अगर (!sb_rकरोnly(sb))
				वापस 0;
		पूर्ण
		अगर (inode_biपंचांगap >= sb_block + 1 &&
		    inode_biपंचांगap <= last_bg_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Inode bitmap for group %u overlaps "
				 "block group descriptors", i);
			अगर (!sb_rकरोnly(sb))
				वापस 0;
		पूर्ण
		अगर (inode_biपंचांगap < first_block || inode_biपंचांगap > last_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
			       "Inode bitmap for group %u not in group "
			       "(block %llu)!", i, inode_biपंचांगap);
			वापस 0;
		पूर्ण
		inode_table = ext4_inode_table(sb, gdp);
		अगर (inode_table == sb_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Inode table for group %u overlaps "
				 "superblock", i);
			अगर (!sb_rकरोnly(sb))
				वापस 0;
		पूर्ण
		अगर (inode_table >= sb_block + 1 &&
		    inode_table <= last_bg_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Inode table for group %u overlaps "
				 "block group descriptors", i);
			अगर (!sb_rकरोnly(sb))
				वापस 0;
		पूर्ण
		अगर (inode_table < first_block ||
		    inode_table + sbi->s_itb_per_group - 1 > last_block) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
			       "Inode table for group %u not in group "
			       "(block %llu)!", i, inode_table);
			वापस 0;
		पूर्ण
		ext4_lock_group(sb, i);
		अगर (!ext4_group_desc_csum_verअगरy(sb, i, gdp)) अणु
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Checksum for group %u failed (%u!=%u)",
				 i, le16_to_cpu(ext4_group_desc_csum(sb, i,
				     gdp)), le16_to_cpu(gdp->bg_checksum));
			अगर (!sb_rकरोnly(sb)) अणु
				ext4_unlock_group(sb, i);
				वापस 0;
			पूर्ण
		पूर्ण
		ext4_unlock_group(sb, i);
		अगर (!flexbg_flag)
			first_block += EXT4_BLOCKS_PER_GROUP(sb);
	पूर्ण
	अगर (शून्य != first_not_zeroed)
		*first_not_zeroed = grp;
	वापस 1;
पूर्ण

/* ext4_orphan_cleanup() walks a singly-linked list of inodes (starting at
 * the superblock) which were deleted from all directories, but held खोलो by
 * a process at the समय of a crash.  We walk the list and try to delete these
 * inodes at recovery समय (only with a पढ़ो-ग_लिखो fileप्रणाली).
 *
 * In order to keep the orphan inode chain consistent during traversal (in
 * हाल of crash during recovery), we link each inode पूर्णांकo the superblock
 * orphan list_head and handle it the same way as an inode deletion during
 * normal operation (which journals the operations क्रम us).
 *
 * We only करो an iget() and an iput() on each inode, which is very safe अगर we
 * accidentally poपूर्णांक at an in-use or alपढ़ोy deleted inode.  The worst that
 * can happen in this हाल is that we get a "bit already cleared" message from
 * ext4_मुक्त_inode().  The only reason we would poपूर्णांक at a wrong inode is अगर
 * e2fsck was run on this fileप्रणाली, and it must have alपढ़ोy करोne the orphan
 * inode cleanup क्रम us, so we can safely पात without any further action.
 */
अटल व्योम ext4_orphan_cleanup(काष्ठा super_block *sb,
				काष्ठा ext4_super_block *es)
अणु
	अचिन्हित पूर्णांक s_flags = sb->s_flags;
	पूर्णांक ret, nr_orphans = 0, nr_truncates = 0;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक quota_update = 0;
	पूर्णांक i;
#पूर्ण_अगर
	अगर (!es->s_last_orphan) अणु
		jbd_debug(4, "no orphan inodes to clean up\n");
		वापस;
	पूर्ण

	अगर (bdev_पढ़ो_only(sb->s_bdev)) अणु
		ext4_msg(sb, KERN_ERR, "write access "
			"unavailable, skipping orphan cleanup");
		वापस;
	पूर्ण

	/* Check अगर feature set would not allow a r/w mount */
	अगर (!ext4_feature_set_ok(sb, 0)) अणु
		ext4_msg(sb, KERN_INFO, "Skipping orphan cleanup due to "
			 "unknown ROCOMPAT features");
		वापस;
	पूर्ण

	अगर (EXT4_SB(sb)->s_mount_state & EXT4_ERROR_FS) अणु
		/* करोn't clear list on RO mount w/ errors */
		अगर (es->s_last_orphan && !(s_flags & SB_RDONLY)) अणु
			ext4_msg(sb, KERN_INFO, "Errors on filesystem, "
				  "clearing orphan list.\n");
			es->s_last_orphan = 0;
		पूर्ण
		jbd_debug(1, "Skipping orphan recovery on fs with errors.\n");
		वापस;
	पूर्ण

	अगर (s_flags & SB_RDONLY) अणु
		ext4_msg(sb, KERN_INFO, "orphan cleanup on readonly fs");
		sb->s_flags &= ~SB_RDONLY;
	पूर्ण
#अगर_घोषित CONFIG_QUOTA
	/*
	 * Turn on quotas which were not enabled क्रम पढ़ो-only mounts अगर
	 * fileप्रणाली has quota feature, so that they are updated correctly.
	 */
	अगर (ext4_has_feature_quota(sb) && (s_flags & SB_RDONLY)) अणु
		पूर्णांक ret = ext4_enable_quotas(sb);

		अगर (!ret)
			quota_update = 1;
		अन्यथा
			ext4_msg(sb, KERN_ERR,
				"Cannot turn on quotas: error %d", ret);
	पूर्ण

	/* Turn on journaled quotas used क्रम old sytle */
	क्रम (i = 0; i < EXT4_MAXQUOTAS; i++) अणु
		अगर (EXT4_SB(sb)->s_qf_names[i]) अणु
			पूर्णांक ret = ext4_quota_on_mount(sb, i);

			अगर (!ret)
				quota_update = 1;
			अन्यथा
				ext4_msg(sb, KERN_ERR,
					"Cannot turn on journaled "
					"quota: type %d: error %d", i, ret);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	जबतक (es->s_last_orphan) अणु
		काष्ठा inode *inode;

		/*
		 * We may have encountered an error during cleanup; अगर
		 * so, skip the rest.
		 */
		अगर (EXT4_SB(sb)->s_mount_state & EXT4_ERROR_FS) अणु
			jbd_debug(1, "Skipping orphan recovery on fs with errors.\n");
			es->s_last_orphan = 0;
			अवरोध;
		पूर्ण

		inode = ext4_orphan_get(sb, le32_to_cpu(es->s_last_orphan));
		अगर (IS_ERR(inode)) अणु
			es->s_last_orphan = 0;
			अवरोध;
		पूर्ण

		list_add(&EXT4_I(inode)->i_orphan, &EXT4_SB(sb)->s_orphan);
		dquot_initialize(inode);
		अगर (inode->i_nlink) अणु
			अगर (test_opt(sb, DEBUG))
				ext4_msg(sb, KERN_DEBUG,
					"%s: truncating inode %lu to %lld bytes",
					__func__, inode->i_ino, inode->i_size);
			jbd_debug(2, "truncating inode %lu to %lld bytes\n",
				  inode->i_ino, inode->i_size);
			inode_lock(inode);
			truncate_inode_pages(inode->i_mapping, inode->i_size);
			ret = ext4_truncate(inode);
			अगर (ret)
				ext4_std_error(inode->i_sb, ret);
			inode_unlock(inode);
			nr_truncates++;
		पूर्ण अन्यथा अणु
			अगर (test_opt(sb, DEBUG))
				ext4_msg(sb, KERN_DEBUG,
					"%s: deleting unreferenced inode %lu",
					__func__, inode->i_ino);
			jbd_debug(2, "deleting unreferenced inode %lu\n",
				  inode->i_ino);
			nr_orphans++;
		पूर्ण
		iput(inode);  /* The delete magic happens here! */
	पूर्ण

#घोषणा PLURAL(x) (x), ((x) == 1) ? "" : "s"

	अगर (nr_orphans)
		ext4_msg(sb, KERN_INFO, "%d orphan inode%s deleted",
		       PLURAL(nr_orphans));
	अगर (nr_truncates)
		ext4_msg(sb, KERN_INFO, "%d truncate%s cleaned up",
		       PLURAL(nr_truncates));
#अगर_घोषित CONFIG_QUOTA
	/* Turn off quotas अगर they were enabled क्रम orphan cleanup */
	अगर (quota_update) अणु
		क्रम (i = 0; i < EXT4_MAXQUOTAS; i++) अणु
			अगर (sb_dqopt(sb)->files[i])
				dquot_quota_off(sb, i);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	sb->s_flags = s_flags; /* Restore SB_RDONLY status */
पूर्ण

/*
 * Maximal extent क्रमmat file size.
 * Resulting logical blkno at s_maxbytes must fit in our on-disk
 * extent क्रमmat containers, within a sector_t, and within i_blocks
 * in the vfs.  ext4 inode has 48 bits of i_block in fsblock units,
 * so that won't be a limiting factor.
 *
 * However there is other limiting factor. We करो store extents in the क्रमm
 * of starting block and length, hence the resulting length of the extent
 * covering maximum file size must fit पूर्णांकo on-disk क्रमmat containers as
 * well. Given that length is always by 1 unit bigger than max unit (because
 * we count 0 as well) we have to lower the s_maxbytes by one fs block.
 *
 * Note, this करोes *not* consider any metadata overhead क्रम vfs i_blocks.
 */
अटल loff_t ext4_max_size(पूर्णांक blkbits, पूर्णांक has_huge_files)
अणु
	loff_t res;
	loff_t upper_limit = MAX_LFS_खाताSIZE;

	BUILD_BUG_ON(माप(blkcnt_t) < माप(u64));

	अगर (!has_huge_files) अणु
		upper_limit = (1LL << 32) - 1;

		/* total blocks in file प्रणाली block size */
		upper_limit >>= (blkbits - 9);
		upper_limit <<= blkbits;
	पूर्ण

	/*
	 * 32-bit extent-start container, ee_block. We lower the maxbytes
	 * by one fs block, so ee_len can cover the extent of maximum file
	 * size
	 */
	res = (1LL << 32) - 1;
	res <<= blkbits;

	/* Sanity check against vm- & vfs- imposed limits */
	अगर (res > upper_limit)
		res = upper_limit;

	वापस res;
पूर्ण

/*
 * Maximal biपंचांगap file size.  There is a direct, and अणु,द्विगुन-,triple-पूर्णindirect
 * block limit, and also a limit of (2^48 - 1) 512-byte sectors in i_blocks.
 * We need to be 1 fileप्रणाली block less than the 2^48 sector limit.
 */
अटल loff_t ext4_max_biपंचांगap_size(पूर्णांक bits, पूर्णांक has_huge_files)
अणु
	loff_t res = EXT4_Nसूची_BLOCKS;
	पूर्णांक meta_blocks;
	loff_t upper_limit;
	/* This is calculated to be the largest file size क्रम a dense, block
	 * mapped file such that the file's total number of 512-byte sectors,
	 * including data and all indirect blocks, करोes not exceed (2^48 - 1).
	 *
	 * __u32 i_blocks_lo and _u16 i_blocks_high represent the total
	 * number of 512-byte sectors of the file.
	 */

	अगर (!has_huge_files) अणु
		/*
		 * !has_huge_files or implies that the inode i_block field
		 * represents total file blocks in 2^32 512-byte sectors ==
		 * size of vfs inode i_blocks * 8
		 */
		upper_limit = (1LL << 32) - 1;

		/* total blocks in file प्रणाली block size */
		upper_limit >>= (bits - 9);

	पूर्ण अन्यथा अणु
		/*
		 * We use 48 bit ext4_inode i_blocks
		 * With EXT4_HUGE_खाता_FL set the i_blocks
		 * represent total number of blocks in
		 * file प्रणाली block size
		 */
		upper_limit = (1LL << 48) - 1;

	पूर्ण

	/* indirect blocks */
	meta_blocks = 1;
	/* द्विगुन indirect blocks */
	meta_blocks += 1 + (1LL << (bits-2));
	/* tripple indirect blocks */
	meta_blocks += 1 + (1LL << (bits-2)) + (1LL << (2*(bits-2)));

	upper_limit -= meta_blocks;
	upper_limit <<= bits;

	res += 1LL << (bits-2);
	res += 1LL << (2*(bits-2));
	res += 1LL << (3*(bits-2));
	res <<= bits;
	अगर (res > upper_limit)
		res = upper_limit;

	अगर (res > MAX_LFS_खाताSIZE)
		res = MAX_LFS_खाताSIZE;

	वापस res;
पूर्ण

अटल ext4_fsblk_t descriptor_loc(काष्ठा super_block *sb,
				   ext4_fsblk_t logical_sb_block, पूर्णांक nr)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_group_t bg, first_meta_bg;
	पूर्णांक has_super = 0;

	first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);

	अगर (!ext4_has_feature_meta_bg(sb) || nr < first_meta_bg)
		वापस logical_sb_block + nr + 1;
	bg = sbi->s_desc_per_block * nr;
	अगर (ext4_bg_has_super(sb, bg))
		has_super = 1;

	/*
	 * If we have a meta_bg fs with 1k blocks, group 0's GDT is at
	 * block 2, not 1.  If s_first_data_block == 0 (bigalloc is enabled
	 * on modern mke2fs or blksize > 1k on older mke2fs) then we must
	 * compensate.
	 */
	अगर (sb->s_blocksize == 1024 && nr == 0 &&
	    le32_to_cpu(sbi->s_es->s_first_data_block) == 0)
		has_super++;

	वापस (has_super + ext4_group_first_block_no(sb, bg));
पूर्ण

/**
 * ext4_get_stripe_size: Get the stripe size.
 * @sbi: In memory super block info
 *
 * If we have specअगरied it via mount option, then
 * use the mount option value. If the value specअगरied at mount समय is
 * greater than the blocks per group use the super block value.
 * If the super block value is greater than blocks per group वापस 0.
 * Allocator needs it be less than blocks per group.
 *
 */
अटल अचिन्हित दीर्घ ext4_get_stripe_size(काष्ठा ext4_sb_info *sbi)
अणु
	अचिन्हित दीर्घ stride = le16_to_cpu(sbi->s_es->s_raid_stride);
	अचिन्हित दीर्घ stripe_width =
			le32_to_cpu(sbi->s_es->s_raid_stripe_width);
	पूर्णांक ret;

	अगर (sbi->s_stripe && sbi->s_stripe <= sbi->s_blocks_per_group)
		ret = sbi->s_stripe;
	अन्यथा अगर (stripe_width && stripe_width <= sbi->s_blocks_per_group)
		ret = stripe_width;
	अन्यथा अगर (stride && stride <= sbi->s_blocks_per_group)
		ret = stride;
	अन्यथा
		ret = 0;

	/*
	 * If the stripe width is 1, this makes no sense and
	 * we set it to 0 to turn off stripe handling code.
	 */
	अगर (ret <= 1)
		ret = 0;

	वापस ret;
पूर्ण

/*
 * Check whether this fileप्रणाली can be mounted based on
 * the features present and the RDONLY/RDWR mount requested.
 * Returns 1 अगर this fileप्रणाली can be mounted as requested,
 * 0 अगर it cannot be.
 */
अटल पूर्णांक ext4_feature_set_ok(काष्ठा super_block *sb, पूर्णांक पढ़ोonly)
अणु
	अगर (ext4_has_unknown_ext4_incompat_features(sb)) अणु
		ext4_msg(sb, KERN_ERR,
			"Couldn't mount because of "
			"unsupported optional features (%x)",
			(le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_incompat) &
			~EXT4_FEATURE_INCOMPAT_SUPP));
		वापस 0;
	पूर्ण

#अगर_अघोषित CONFIG_UNICODE
	अगर (ext4_has_feature_हालfold(sb)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Filesystem with casefold feature cannot be "
			 "mounted without CONFIG_UNICODE");
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (पढ़ोonly)
		वापस 1;

	अगर (ext4_has_feature_पढ़ोonly(sb)) अणु
		ext4_msg(sb, KERN_INFO, "filesystem is read-only");
		sb->s_flags |= SB_RDONLY;
		वापस 1;
	पूर्ण

	/* Check that feature set is OK क्रम a पढ़ो-ग_लिखो mount */
	अगर (ext4_has_unknown_ext4_ro_compat_features(sb)) अणु
		ext4_msg(sb, KERN_ERR, "couldn't mount RDWR because of "
			 "unsupported optional features (%x)",
			 (le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_ro_compat) &
				~EXT4_FEATURE_RO_COMPAT_SUPP));
		वापस 0;
	पूर्ण
	अगर (ext4_has_feature_bigalloc(sb) && !ext4_has_feature_extents(sb)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Can't support bigalloc feature without "
			 "extents feature\n");
		वापस 0;
	पूर्ण

#अगर !IS_ENABLED(CONFIG_QUOTA) || !IS_ENABLED(CONFIG_QFMT_V2)
	अगर (!पढ़ोonly && (ext4_has_feature_quota(sb) ||
			  ext4_has_feature_project(sb))) अणु
		ext4_msg(sb, KERN_ERR,
			 "The kernel was not built with CONFIG_QUOTA and CONFIG_QFMT_V2");
		वापस 0;
	पूर्ण
#पूर्ण_अगर  /* CONFIG_QUOTA */
	वापस 1;
पूर्ण

/*
 * This function is called once a day अगर we have errors logged
 * on the file प्रणाली
 */
अटल व्योम prपूर्णांक_daily_error_info(काष्ठा समयr_list *t)
अणु
	काष्ठा ext4_sb_info *sbi = from_समयr(sbi, t, s_err_report);
	काष्ठा super_block *sb = sbi->s_sb;
	काष्ठा ext4_super_block *es = sbi->s_es;

	अगर (es->s_error_count)
		/* fsck newer than v1.41.13 is needed to clean this condition. */
		ext4_msg(sb, KERN_NOTICE, "error count since last fsck: %u",
			 le32_to_cpu(es->s_error_count));
	अगर (es->s_first_error_समय) अणु
		prपूर्णांकk(KERN_NOTICE "EXT4-fs (%s): initial error at time %llu: %.*s:%d",
		       sb->s_id,
		       ext4_get_tstamp(es, s_first_error_समय),
		       (पूर्णांक) माप(es->s_first_error_func),
		       es->s_first_error_func,
		       le32_to_cpu(es->s_first_error_line));
		अगर (es->s_first_error_ino)
			prपूर्णांकk(KERN_CONT ": inode %u",
			       le32_to_cpu(es->s_first_error_ino));
		अगर (es->s_first_error_block)
			prपूर्णांकk(KERN_CONT ": block %llu", (अचिन्हित दीर्घ दीर्घ)
			       le64_to_cpu(es->s_first_error_block));
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
	अगर (es->s_last_error_समय) अणु
		prपूर्णांकk(KERN_NOTICE "EXT4-fs (%s): last error at time %llu: %.*s:%d",
		       sb->s_id,
		       ext4_get_tstamp(es, s_last_error_समय),
		       (पूर्णांक) माप(es->s_last_error_func),
		       es->s_last_error_func,
		       le32_to_cpu(es->s_last_error_line));
		अगर (es->s_last_error_ino)
			prपूर्णांकk(KERN_CONT ": inode %u",
			       le32_to_cpu(es->s_last_error_ino));
		अगर (es->s_last_error_block)
			prपूर्णांकk(KERN_CONT ": block %llu", (अचिन्हित दीर्घ दीर्घ)
			       le64_to_cpu(es->s_last_error_block));
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
	mod_समयr(&sbi->s_err_report, jअगरfies + 24*60*60*HZ);  /* Once a day */
पूर्ण

/* Find next suitable group and run ext4_init_inode_table */
अटल पूर्णांक ext4_run_li_request(काष्ठा ext4_li_request *elr)
अणु
	काष्ठा ext4_group_desc *gdp = शून्य;
	काष्ठा super_block *sb = elr->lr_super;
	ext4_group_t ngroups = EXT4_SB(sb)->s_groups_count;
	ext4_group_t group = elr->lr_next_group;
	अचिन्हित दीर्घ समयout = 0;
	अचिन्हित पूर्णांक prefetch_ios = 0;
	पूर्णांक ret = 0;

	अगर (elr->lr_mode == EXT4_LI_MODE_PREFETCH_BBITMAP) अणु
		elr->lr_next_group = ext4_mb_prefetch(sb, group,
				EXT4_SB(sb)->s_mb_prefetch, &prefetch_ios);
		अगर (prefetch_ios)
			ext4_mb_prefetch_fini(sb, elr->lr_next_group,
					      prefetch_ios);
		trace_ext4_prefetch_biपंचांगaps(sb, group, elr->lr_next_group,
					    prefetch_ios);
		अगर (group >= elr->lr_next_group) अणु
			ret = 1;
			अगर (elr->lr_first_not_zeroed != ngroups &&
			    !sb_rकरोnly(sb) && test_opt(sb, INIT_INODE_TABLE)) अणु
				elr->lr_next_group = elr->lr_first_not_zeroed;
				elr->lr_mode = EXT4_LI_MODE_ITABLE;
				ret = 0;
			पूर्ण
		पूर्ण
		वापस ret;
	पूर्ण

	क्रम (; group < ngroups; group++) अणु
		gdp = ext4_get_group_desc(sb, group, शून्य);
		अगर (!gdp) अणु
			ret = 1;
			अवरोध;
		पूर्ण

		अगर (!(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED)))
			अवरोध;
	पूर्ण

	अगर (group >= ngroups)
		ret = 1;

	अगर (!ret) अणु
		समयout = jअगरfies;
		ret = ext4_init_inode_table(sb, group,
					    elr->lr_समयout ? 0 : 1);
		trace_ext4_lazy_itable_init(sb, group);
		अगर (elr->lr_समयout == 0) अणु
			समयout = (jअगरfies - समयout) *
				EXT4_SB(elr->lr_super)->s_li_रुको_mult;
			elr->lr_समयout = समयout;
		पूर्ण
		elr->lr_next_sched = jअगरfies + elr->lr_समयout;
		elr->lr_next_group = group + 1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Remove lr_request from the list_request and मुक्त the
 * request काष्ठाure. Should be called with li_list_mtx held
 */
अटल व्योम ext4_हटाओ_li_request(काष्ठा ext4_li_request *elr)
अणु
	अगर (!elr)
		वापस;

	list_del(&elr->lr_request);
	EXT4_SB(elr->lr_super)->s_li_request = शून्य;
	kमुक्त(elr);
पूर्ण

अटल व्योम ext4_unरेजिस्टर_li_request(काष्ठा super_block *sb)
अणु
	mutex_lock(&ext4_li_mtx);
	अगर (!ext4_li_info) अणु
		mutex_unlock(&ext4_li_mtx);
		वापस;
	पूर्ण

	mutex_lock(&ext4_li_info->li_list_mtx);
	ext4_हटाओ_li_request(EXT4_SB(sb)->s_li_request);
	mutex_unlock(&ext4_li_info->li_list_mtx);
	mutex_unlock(&ext4_li_mtx);
पूर्ण

अटल काष्ठा task_काष्ठा *ext4_lazyinit_task;

/*
 * This is the function where ext4lazyinit thपढ़ो lives. It walks
 * through the request list searching क्रम next scheduled fileप्रणाली.
 * When such a fs is found, run the lazy initialization request
 * (ext4_rn_li_request) and keep track of the समय spend in this
 * function. Based on that समय we compute next schedule समय of
 * the request. When walking through the list is complete, compute
 * next waking समय and put itself पूर्णांकo sleep.
 */
अटल पूर्णांक ext4_lazyinit_thपढ़ो(व्योम *arg)
अणु
	काष्ठा ext4_lazy_init *eli = (काष्ठा ext4_lazy_init *)arg;
	काष्ठा list_head *pos, *n;
	काष्ठा ext4_li_request *elr;
	अचिन्हित दीर्घ next_wakeup, cur;

	BUG_ON(शून्य == eli);

cont_thपढ़ो:
	जबतक (true) अणु
		next_wakeup = MAX_JIFFY_OFFSET;

		mutex_lock(&eli->li_list_mtx);
		अगर (list_empty(&eli->li_request_list)) अणु
			mutex_unlock(&eli->li_list_mtx);
			जाओ निकास_thपढ़ो;
		पूर्ण
		list_क्रम_each_safe(pos, n, &eli->li_request_list) अणु
			पूर्णांक err = 0;
			पूर्णांक progress = 0;
			elr = list_entry(pos, काष्ठा ext4_li_request,
					 lr_request);

			अगर (समय_beक्रमe(jअगरfies, elr->lr_next_sched)) अणु
				अगर (समय_beक्रमe(elr->lr_next_sched, next_wakeup))
					next_wakeup = elr->lr_next_sched;
				जारी;
			पूर्ण
			अगर (करोwn_पढ़ो_trylock(&elr->lr_super->s_umount)) अणु
				अगर (sb_start_ग_लिखो_trylock(elr->lr_super)) अणु
					progress = 1;
					/*
					 * We hold sb->s_umount, sb can not
					 * be हटाओd from the list, it is
					 * now safe to drop li_list_mtx
					 */
					mutex_unlock(&eli->li_list_mtx);
					err = ext4_run_li_request(elr);
					sb_end_ग_लिखो(elr->lr_super);
					mutex_lock(&eli->li_list_mtx);
					n = pos->next;
				पूर्ण
				up_पढ़ो((&elr->lr_super->s_umount));
			पूर्ण
			/* error, हटाओ the lazy_init job */
			अगर (err) अणु
				ext4_हटाओ_li_request(elr);
				जारी;
			पूर्ण
			अगर (!progress) अणु
				elr->lr_next_sched = jअगरfies +
					(pअक्रमom_u32()
					 % (EXT4_DEF_LI_MAX_START_DELAY * HZ));
			पूर्ण
			अगर (समय_beक्रमe(elr->lr_next_sched, next_wakeup))
				next_wakeup = elr->lr_next_sched;
		पूर्ण
		mutex_unlock(&eli->li_list_mtx);

		try_to_मुक्तze();

		cur = jअगरfies;
		अगर ((समय_after_eq(cur, next_wakeup)) ||
		    (MAX_JIFFY_OFFSET == next_wakeup)) अणु
			cond_resched();
			जारी;
		पूर्ण

		schedule_समयout_पूर्णांकerruptible(next_wakeup - cur);

		अगर (kthपढ़ो_should_stop()) अणु
			ext4_clear_request_list();
			जाओ निकास_thपढ़ो;
		पूर्ण
	पूर्ण

निकास_thपढ़ो:
	/*
	 * It looks like the request list is empty, but we need
	 * to check it under the li_list_mtx lock, to prevent any
	 * additions पूर्णांकo it, and of course we should lock ext4_li_mtx
	 * to atomically मुक्त the list and ext4_li_info, because at
	 * this poपूर्णांक another ext4 fileप्रणाली could be रेजिस्टरing
	 * new one.
	 */
	mutex_lock(&ext4_li_mtx);
	mutex_lock(&eli->li_list_mtx);
	अगर (!list_empty(&eli->li_request_list)) अणु
		mutex_unlock(&eli->li_list_mtx);
		mutex_unlock(&ext4_li_mtx);
		जाओ cont_thपढ़ो;
	पूर्ण
	mutex_unlock(&eli->li_list_mtx);
	kमुक्त(ext4_li_info);
	ext4_li_info = शून्य;
	mutex_unlock(&ext4_li_mtx);

	वापस 0;
पूर्ण

अटल व्योम ext4_clear_request_list(व्योम)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा ext4_li_request *elr;

	mutex_lock(&ext4_li_info->li_list_mtx);
	list_क्रम_each_safe(pos, n, &ext4_li_info->li_request_list) अणु
		elr = list_entry(pos, काष्ठा ext4_li_request,
				 lr_request);
		ext4_हटाओ_li_request(elr);
	पूर्ण
	mutex_unlock(&ext4_li_info->li_list_mtx);
पूर्ण

अटल पूर्णांक ext4_run_lazyinit_thपढ़ो(व्योम)
अणु
	ext4_lazyinit_task = kthपढ़ो_run(ext4_lazyinit_thपढ़ो,
					 ext4_li_info, "ext4lazyinit");
	अगर (IS_ERR(ext4_lazyinit_task)) अणु
		पूर्णांक err = PTR_ERR(ext4_lazyinit_task);
		ext4_clear_request_list();
		kमुक्त(ext4_li_info);
		ext4_li_info = शून्य;
		prपूर्णांकk(KERN_CRIT "EXT4-fs: error %d creating inode table "
				 "initialization thread\n",
				 err);
		वापस err;
	पूर्ण
	ext4_li_info->li_state |= EXT4_LAZYINIT_RUNNING;
	वापस 0;
पूर्ण

/*
 * Check whether it make sense to run itable init. thपढ़ो or not.
 * If there is at least one uninitialized inode table, वापस
 * corresponding group number, अन्यथा the loop goes through all
 * groups and वापस total number of groups.
 */
अटल ext4_group_t ext4_has_uninit_itable(काष्ठा super_block *sb)
अणु
	ext4_group_t group, ngroups = EXT4_SB(sb)->s_groups_count;
	काष्ठा ext4_group_desc *gdp = शून्य;

	अगर (!ext4_has_group_desc_csum(sb))
		वापस ngroups;

	क्रम (group = 0; group < ngroups; group++) अणु
		gdp = ext4_get_group_desc(sb, group, शून्य);
		अगर (!gdp)
			जारी;

		अगर (!(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED)))
			अवरोध;
	पूर्ण

	वापस group;
पूर्ण

अटल पूर्णांक ext4_li_info_new(व्योम)
अणु
	काष्ठा ext4_lazy_init *eli = शून्य;

	eli = kzalloc(माप(*eli), GFP_KERNEL);
	अगर (!eli)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&eli->li_request_list);
	mutex_init(&eli->li_list_mtx);

	eli->li_state |= EXT4_LAZYINIT_QUIT;

	ext4_li_info = eli;

	वापस 0;
पूर्ण

अटल काष्ठा ext4_li_request *ext4_li_request_new(काष्ठा super_block *sb,
					    ext4_group_t start)
अणु
	काष्ठा ext4_li_request *elr;

	elr = kzalloc(माप(*elr), GFP_KERNEL);
	अगर (!elr)
		वापस शून्य;

	elr->lr_super = sb;
	elr->lr_first_not_zeroed = start;
	अगर (test_opt(sb, NO_PREFETCH_BLOCK_BITMAPS)) अणु
		elr->lr_mode = EXT4_LI_MODE_ITABLE;
		elr->lr_next_group = start;
	पूर्ण अन्यथा अणु
		elr->lr_mode = EXT4_LI_MODE_PREFETCH_BBITMAP;
	पूर्ण

	/*
	 * Ranकरोmize first schedule समय of the request to
	 * spपढ़ो the inode table initialization requests
	 * better.
	 */
	elr->lr_next_sched = jअगरfies + (pअक्रमom_u32() %
				(EXT4_DEF_LI_MAX_START_DELAY * HZ));
	वापस elr;
पूर्ण

पूर्णांक ext4_रेजिस्टर_li_request(काष्ठा super_block *sb,
			     ext4_group_t first_not_zeroed)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_li_request *elr = शून्य;
	ext4_group_t ngroups = sbi->s_groups_count;
	पूर्णांक ret = 0;

	mutex_lock(&ext4_li_mtx);
	अगर (sbi->s_li_request != शून्य) अणु
		/*
		 * Reset समयout so it can be computed again, because
		 * s_li_रुको_mult might have changed.
		 */
		sbi->s_li_request->lr_समयout = 0;
		जाओ out;
	पूर्ण

	अगर (test_opt(sb, NO_PREFETCH_BLOCK_BITMAPS) &&
	    (first_not_zeroed == ngroups || sb_rकरोnly(sb) ||
	     !test_opt(sb, INIT_INODE_TABLE)))
		जाओ out;

	elr = ext4_li_request_new(sb, first_not_zeroed);
	अगर (!elr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (शून्य == ext4_li_info) अणु
		ret = ext4_li_info_new();
		अगर (ret)
			जाओ out;
	पूर्ण

	mutex_lock(&ext4_li_info->li_list_mtx);
	list_add(&elr->lr_request, &ext4_li_info->li_request_list);
	mutex_unlock(&ext4_li_info->li_list_mtx);

	sbi->s_li_request = elr;
	/*
	 * set elr to शून्य here since it has been inserted to
	 * the request_list and the removal and मुक्त of it is
	 * handled by ext4_clear_request_list from now on.
	 */
	elr = शून्य;

	अगर (!(ext4_li_info->li_state & EXT4_LAZYINIT_RUNNING)) अणु
		ret = ext4_run_lazyinit_thपढ़ो();
		अगर (ret)
			जाओ out;
	पूर्ण
out:
	mutex_unlock(&ext4_li_mtx);
	अगर (ret)
		kमुक्त(elr);
	वापस ret;
पूर्ण

/*
 * We करो not need to lock anything since this is called on
 * module unload.
 */
अटल व्योम ext4_destroy_lazyinit_thपढ़ो(व्योम)
अणु
	/*
	 * If thपढ़ो निकासed earlier
	 * there's nothing to be करोne.
	 */
	अगर (!ext4_li_info || !ext4_lazyinit_task)
		वापस;

	kthपढ़ो_stop(ext4_lazyinit_task);
पूर्ण

अटल पूर्णांक set_journal_csum_feature_set(काष्ठा super_block *sb)
अणु
	पूर्णांक ret = 1;
	पूर्णांक compat, incompat;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (ext4_has_metadata_csum(sb)) अणु
		/* journal checksum v3 */
		compat = 0;
		incompat = JBD2_FEATURE_INCOMPAT_CSUM_V3;
	पूर्ण अन्यथा अणु
		/* journal checksum v1 */
		compat = JBD2_FEATURE_COMPAT_CHECKSUM;
		incompat = 0;
	पूर्ण

	jbd2_journal_clear_features(sbi->s_journal,
			JBD2_FEATURE_COMPAT_CHECKSUM, 0,
			JBD2_FEATURE_INCOMPAT_CSUM_V3 |
			JBD2_FEATURE_INCOMPAT_CSUM_V2);
	अगर (test_opt(sb, JOURNAL_ASYNC_COMMIT)) अणु
		ret = jbd2_journal_set_features(sbi->s_journal,
				compat, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT |
				incompat);
	पूर्ण अन्यथा अगर (test_opt(sb, JOURNAL_CHECKSUM)) अणु
		ret = jbd2_journal_set_features(sbi->s_journal,
				compat, 0,
				incompat);
		jbd2_journal_clear_features(sbi->s_journal, 0, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	पूर्ण अन्यथा अणु
		jbd2_journal_clear_features(sbi->s_journal, 0, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Note: calculating the overhead so we can be compatible with
 * historical BSD practice is quite dअगरficult in the face of
 * clusters/bigalloc.  This is because multiple metadata blocks from
 * dअगरferent block group can end up in the same allocation cluster.
 * Calculating the exact overhead in the face of clustered allocation
 * requires either O(all block biपंचांगaps) in memory or O(number of block
 * groups**2) in समय.  We will still calculate the superblock क्रम
 * older file प्रणालीs --- and अगर we come across with a bigalloc file
 * प्रणाली with zero in s_overhead_clusters the estimate will be बंद to
 * correct especially क्रम very large cluster sizes --- but क्रम newer
 * file प्रणालीs, it's better to calculate this figure once at mkfs
 * समय, and store it in the superblock.  If the superblock value is
 * present (even क्रम non-bigalloc file प्रणालीs), we will use it.
 */
अटल पूर्णांक count_overhead(काष्ठा super_block *sb, ext4_group_t grp,
			  अक्षर *buf)
अणु
	काष्ठा ext4_sb_info	*sbi = EXT4_SB(sb);
	काष्ठा ext4_group_desc	*gdp;
	ext4_fsblk_t		first_block, last_block, b;
	ext4_group_t		i, ngroups = ext4_get_groups_count(sb);
	पूर्णांक			s, j, count = 0;

	अगर (!ext4_has_feature_bigalloc(sb))
		वापस (ext4_bg_has_super(sb, grp) + ext4_bg_num_gdb(sb, grp) +
			sbi->s_itb_per_group + 2);

	first_block = le32_to_cpu(sbi->s_es->s_first_data_block) +
		(grp * EXT4_BLOCKS_PER_GROUP(sb));
	last_block = first_block + EXT4_BLOCKS_PER_GROUP(sb) - 1;
	क्रम (i = 0; i < ngroups; i++) अणु
		gdp = ext4_get_group_desc(sb, i, शून्य);
		b = ext4_block_biपंचांगap(sb, gdp);
		अगर (b >= first_block && b <= last_block) अणु
			ext4_set_bit(EXT4_B2C(sbi, b - first_block), buf);
			count++;
		पूर्ण
		b = ext4_inode_biपंचांगap(sb, gdp);
		अगर (b >= first_block && b <= last_block) अणु
			ext4_set_bit(EXT4_B2C(sbi, b - first_block), buf);
			count++;
		पूर्ण
		b = ext4_inode_table(sb, gdp);
		अगर (b >= first_block && b + sbi->s_itb_per_group <= last_block)
			क्रम (j = 0; j < sbi->s_itb_per_group; j++, b++) अणु
				पूर्णांक c = EXT4_B2C(sbi, b - first_block);
				ext4_set_bit(c, buf);
				count++;
			पूर्ण
		अगर (i != grp)
			जारी;
		s = 0;
		अगर (ext4_bg_has_super(sb, grp)) अणु
			ext4_set_bit(s++, buf);
			count++;
		पूर्ण
		j = ext4_bg_num_gdb(sb, grp);
		अगर (s + j > EXT4_BLOCKS_PER_GROUP(sb)) अणु
			ext4_error(sb, "Invalid number of block group "
				   "descriptor blocks: %d", j);
			j = EXT4_BLOCKS_PER_GROUP(sb) - s;
		पूर्ण
		count += j;
		क्रम (; j > 0; j--)
			ext4_set_bit(EXT4_B2C(sbi, s++), buf);
	पूर्ण
	अगर (!count)
		वापस 0;
	वापस EXT4_CLUSTERS_PER_GROUP(sb) -
		ext4_count_मुक्त(buf, EXT4_CLUSTERS_PER_GROUP(sb) / 8);
पूर्ण

/*
 * Compute the overhead and stash it in sbi->s_overhead
 */
पूर्णांक ext4_calculate_overhead(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा inode *j_inode;
	अचिन्हित पूर्णांक j_blocks, j_inum = le32_to_cpu(es->s_journal_inum);
	ext4_group_t i, ngroups = ext4_get_groups_count(sb);
	ext4_fsblk_t overhead = 0;
	अक्षर *buf = (अक्षर *) get_zeroed_page(GFP_NOFS);

	अगर (!buf)
		वापस -ENOMEM;

	/*
	 * Compute the overhead (FS काष्ठाures).  This is स्थिरant
	 * क्रम a given fileप्रणाली unless the number of block groups
	 * changes so we cache the previous value until it करोes.
	 */

	/*
	 * All of the blocks beक्रमe first_data_block are overhead
	 */
	overhead = EXT4_B2C(sbi, le32_to_cpu(es->s_first_data_block));

	/*
	 * Add the overhead found in each block group
	 */
	क्रम (i = 0; i < ngroups; i++) अणु
		पूर्णांक blks;

		blks = count_overhead(sb, i, buf);
		overhead += blks;
		अगर (blks)
			स_रखो(buf, 0, PAGE_SIZE);
		cond_resched();
	पूर्ण

	/*
	 * Add the पूर्णांकernal journal blocks whether the journal has been
	 * loaded or not
	 */
	अगर (sbi->s_journal && !sbi->s_journal_bdev)
		overhead += EXT4_NUM_B2C(sbi, sbi->s_journal->j_total_len);
	अन्यथा अगर (ext4_has_feature_journal(sb) && !sbi->s_journal && j_inum) अणु
		/* j_inum क्रम पूर्णांकernal journal is non-zero */
		j_inode = ext4_get_journal_inode(sb, j_inum);
		अगर (j_inode) अणु
			j_blocks = j_inode->i_size >> sb->s_blocksize_bits;
			overhead += EXT4_NUM_B2C(sbi, j_blocks);
			iput(j_inode);
		पूर्ण अन्यथा अणु
			ext4_msg(sb, KERN_ERR, "can't get journal size");
		पूर्ण
	पूर्ण
	sbi->s_overhead = overhead;
	smp_wmb();
	मुक्त_page((अचिन्हित दीर्घ) buf);
	वापस 0;
पूर्ण

अटल व्योम ext4_set_resv_clusters(काष्ठा super_block *sb)
अणु
	ext4_fsblk_t resv_clusters;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	/*
	 * There's no need to reserve anything when we aren't using extents.
	 * The space estimates are exact, there are no unwritten extents,
	 * hole punching करोesn't need new metadata... This is needed especially
	 * to keep ext2/3 backward compatibility.
	 */
	अगर (!ext4_has_feature_extents(sb))
		वापस;
	/*
	 * By शेष we reserve 2% or 4096 clusters, whichever is smaller.
	 * This should cover the situations where we can not afक्रमd to run
	 * out of space like क्रम example punch hole, or converting
	 * unwritten extents in delalloc path. In most हालs such
	 * allocation would require 1, or 2 blocks, higher numbers are
	 * very rare.
	 */
	resv_clusters = (ext4_blocks_count(sbi->s_es) >>
			 sbi->s_cluster_bits);

	करो_भाग(resv_clusters, 50);
	resv_clusters = min_t(ext4_fsblk_t, resv_clusters, 4096);

	atomic64_set(&sbi->s_resv_clusters, resv_clusters);
पूर्ण

अटल स्थिर अक्षर *ext4_quota_mode(काष्ठा super_block *sb)
अणु
#अगर_घोषित CONFIG_QUOTA
	अगर (!ext4_quota_capable(sb))
		वापस "none";

	अगर (EXT4_SB(sb)->s_journal && ext4_is_quota_journalled(sb))
		वापस "journalled";
	अन्यथा
		वापस "writeback";
#अन्यथा
	वापस "disabled";
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ext4_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा dax_device *dax_dev = fs_dax_get_by_bdev(sb->s_bdev);
	अक्षर *orig_data = kstrdup(data, GFP_KERNEL);
	काष्ठा buffer_head *bh, **group_desc;
	काष्ठा ext4_super_block *es = शून्य;
	काष्ठा ext4_sb_info *sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	काष्ठा flex_groups **flex_groups;
	ext4_fsblk_t block;
	ext4_fsblk_t sb_block = get_sb_block(&data);
	ext4_fsblk_t logical_sb_block;
	अचिन्हित दीर्घ offset = 0;
	अचिन्हित दीर्घ def_mount_opts;
	काष्ठा inode *root;
	स्थिर अक्षर *descr;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक blocksize, clustersize;
	अचिन्हित पूर्णांक db_count;
	अचिन्हित पूर्णांक i;
	पूर्णांक needs_recovery, has_huge_files;
	__u64 blocks_count;
	पूर्णांक err = 0;
	ext4_group_t first_not_zeroed;
	काष्ठा ext4_parsed_options parsed_opts;

	/* Set शेषs क्रम the variables that will be set during parsing */
	parsed_opts.journal_ioprio = DEFAULT_JOURNAL_IOPRIO;
	parsed_opts.journal_devnum = 0;
	parsed_opts.mb_optimize_scan = DEFAULT_MB_OPTIMIZE_SCAN;

	अगर ((data && !orig_data) || !sbi)
		जाओ out_मुक्त_base;

	sbi->s_daxdev = dax_dev;
	sbi->s_blockgroup_lock =
		kzalloc(माप(काष्ठा blockgroup_lock), GFP_KERNEL);
	अगर (!sbi->s_blockgroup_lock)
		जाओ out_मुक्त_base;

	sb->s_fs_info = sbi;
	sbi->s_sb = sb;
	sbi->s_inode_पढ़ोahead_blks = EXT4_DEF_INODE_READAHEAD_BLKS;
	sbi->s_sb_block = sb_block;
	sbi->s_sectors_written_start =
		part_stat_पढ़ो(sb->s_bdev, sectors[STAT_WRITE]);

	/* Cleanup superblock name */
	strreplace(sb->s_id, '/', '!');

	/* -EINVAL is शेष */
	ret = -EINVAL;
	blocksize = sb_min_blocksize(sb, EXT4_MIN_BLOCK_SIZE);
	अगर (!blocksize) अणु
		ext4_msg(sb, KERN_ERR, "unable to set blocksize");
		जाओ out_fail;
	पूर्ण

	/*
	 * The ext4 superblock will not be buffer aligned क्रम other than 1kB
	 * block sizes.  We need to calculate the offset from buffer start.
	 */
	अगर (blocksize != EXT4_MIN_BLOCK_SIZE) अणु
		logical_sb_block = sb_block * EXT4_MIN_BLOCK_SIZE;
		offset = करो_भाग(logical_sb_block, blocksize);
	पूर्ण अन्यथा अणु
		logical_sb_block = sb_block;
	पूर्ण

	bh = ext4_sb_bपढ़ो_unmovable(sb, logical_sb_block);
	अगर (IS_ERR(bh)) अणु
		ext4_msg(sb, KERN_ERR, "unable to read superblock");
		ret = PTR_ERR(bh);
		जाओ out_fail;
	पूर्ण
	/*
	 * Note: s_es must be initialized as soon as possible because
	 *       some ext4 macro-inकाष्ठाions depend on its value
	 */
	es = (काष्ठा ext4_super_block *) (bh->b_data + offset);
	sbi->s_es = es;
	sb->s_magic = le16_to_cpu(es->s_magic);
	अगर (sb->s_magic != EXT4_SUPER_MAGIC)
		जाओ cantfind_ext4;
	sbi->s_kbytes_written = le64_to_cpu(es->s_kbytes_written);

	/* Warn अगर metadata_csum and gdt_csum are both set. */
	अगर (ext4_has_feature_metadata_csum(sb) &&
	    ext4_has_feature_gdt_csum(sb))
		ext4_warning(sb, "metadata_csum and uninit_bg are "
			     "redundant flags; please run fsck.");

	/* Check क्रम a known checksum algorithm */
	अगर (!ext4_verअगरy_csum_type(sb, es)) अणु
		ext4_msg(sb, KERN_ERR, "VFS: Found ext4 filesystem with "
			 "unknown checksum algorithm.");
		silent = 1;
		जाओ cantfind_ext4;
	पूर्ण

	/* Load the checksum driver */
	sbi->s_chksum_driver = crypto_alloc_shash("crc32c", 0, 0);
	अगर (IS_ERR(sbi->s_chksum_driver)) अणु
		ext4_msg(sb, KERN_ERR, "Cannot load crc32c driver.");
		ret = PTR_ERR(sbi->s_chksum_driver);
		sbi->s_chksum_driver = शून्य;
		जाओ failed_mount;
	पूर्ण

	/* Check superblock checksum */
	अगर (!ext4_superblock_csum_verअगरy(sb, es)) अणु
		ext4_msg(sb, KERN_ERR, "VFS: Found ext4 filesystem with "
			 "invalid superblock checksum.  Run e2fsck?");
		silent = 1;
		ret = -EFSBADCRC;
		जाओ cantfind_ext4;
	पूर्ण

	/* Precompute checksum seed क्रम all metadata */
	अगर (ext4_has_feature_csum_seed(sb))
		sbi->s_csum_seed = le32_to_cpu(es->s_checksum_seed);
	अन्यथा अगर (ext4_has_metadata_csum(sb) || ext4_has_feature_ea_inode(sb))
		sbi->s_csum_seed = ext4_chksum(sbi, ~0, es->s_uuid,
					       माप(es->s_uuid));

	/* Set शेषs beक्रमe we parse the mount options */
	def_mount_opts = le32_to_cpu(es->s_शेष_mount_opts);
	set_opt(sb, INIT_INODE_TABLE);
	अगर (def_mount_opts & EXT4_DEFM_DEBUG)
		set_opt(sb, DEBUG);
	अगर (def_mount_opts & EXT4_DEFM_BSDGROUPS)
		set_opt(sb, GRPID);
	अगर (def_mount_opts & EXT4_DEFM_UID16)
		set_opt(sb, NO_UID32);
	/* xattr user namespace & acls are now शेषed on */
	set_opt(sb, XATTR_USER);
#अगर_घोषित CONFIG_EXT4_FS_POSIX_ACL
	set_opt(sb, POSIX_ACL);
#पूर्ण_अगर
	अगर (ext4_has_feature_fast_commit(sb))
		set_opt2(sb, JOURNAL_FAST_COMMIT);
	/* करोn't क्रमget to enable journal_csum when metadata_csum is enabled. */
	अगर (ext4_has_metadata_csum(sb))
		set_opt(sb, JOURNAL_CHECKSUM);

	अगर ((def_mount_opts & EXT4_DEFM_JMODE) == EXT4_DEFM_JMODE_DATA)
		set_opt(sb, JOURNAL_DATA);
	अन्यथा अगर ((def_mount_opts & EXT4_DEFM_JMODE) == EXT4_DEFM_JMODE_ORDERED)
		set_opt(sb, ORDERED_DATA);
	अन्यथा अगर ((def_mount_opts & EXT4_DEFM_JMODE) == EXT4_DEFM_JMODE_WBACK)
		set_opt(sb, WRITEBACK_DATA);

	अगर (le16_to_cpu(sbi->s_es->s_errors) == EXT4_ERRORS_PANIC)
		set_opt(sb, ERRORS_PANIC);
	अन्यथा अगर (le16_to_cpu(sbi->s_es->s_errors) == EXT4_ERRORS_CONTINUE)
		set_opt(sb, ERRORS_CONT);
	अन्यथा
		set_opt(sb, ERRORS_RO);
	/* block_validity enabled by शेष; disable with noblock_validity */
	set_opt(sb, BLOCK_VALIDITY);
	अगर (def_mount_opts & EXT4_DEFM_DISCARD)
		set_opt(sb, DISCARD);

	sbi->s_resuid = make_kuid(&init_user_ns, le16_to_cpu(es->s_def_resuid));
	sbi->s_resgid = make_kgid(&init_user_ns, le16_to_cpu(es->s_def_resgid));
	sbi->s_commit_पूर्णांकerval = JBD2_DEFAULT_MAX_COMMIT_AGE * HZ;
	sbi->s_min_batch_समय = EXT4_DEF_MIN_BATCH_TIME;
	sbi->s_max_batch_समय = EXT4_DEF_MAX_BATCH_TIME;

	अगर ((def_mount_opts & EXT4_DEFM_NOBARRIER) == 0)
		set_opt(sb, BARRIER);

	/*
	 * enable delayed allocation by शेष
	 * Use -o nodelalloc to turn it off
	 */
	अगर (!IS_EXT3_SB(sb) && !IS_EXT2_SB(sb) &&
	    ((def_mount_opts & EXT4_DEFM_NODELALLOC) == 0))
		set_opt(sb, DELALLOC);

	/*
	 * set शेष s_li_रुको_mult क्रम lazyinit, क्रम the हाल there is
	 * no mount option specअगरied.
	 */
	sbi->s_li_रुको_mult = EXT4_DEF_LI_WAIT_MULT;

	अगर (le32_to_cpu(es->s_log_block_size) >
	    (EXT4_MAX_BLOCK_LOG_SIZE - EXT4_MIN_BLOCK_LOG_SIZE)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Invalid log block size: %u",
			 le32_to_cpu(es->s_log_block_size));
		जाओ failed_mount;
	पूर्ण
	अगर (le32_to_cpu(es->s_log_cluster_size) >
	    (EXT4_MAX_CLUSTER_LOG_SIZE - EXT4_MIN_BLOCK_LOG_SIZE)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Invalid log cluster size: %u",
			 le32_to_cpu(es->s_log_cluster_size));
		जाओ failed_mount;
	पूर्ण

	blocksize = EXT4_MIN_BLOCK_SIZE << le32_to_cpu(es->s_log_block_size);

	अगर (blocksize == PAGE_SIZE)
		set_opt(sb, DIOREAD_NOLOCK);

	अगर (le32_to_cpu(es->s_rev_level) == EXT4_GOOD_OLD_REV) अणु
		sbi->s_inode_size = EXT4_GOOD_OLD_INODE_SIZE;
		sbi->s_first_ino = EXT4_GOOD_OLD_FIRST_INO;
	पूर्ण अन्यथा अणु
		sbi->s_inode_size = le16_to_cpu(es->s_inode_size);
		sbi->s_first_ino = le32_to_cpu(es->s_first_ino);
		अगर (sbi->s_first_ino < EXT4_GOOD_OLD_FIRST_INO) अणु
			ext4_msg(sb, KERN_ERR, "invalid first ino: %u",
				 sbi->s_first_ino);
			जाओ failed_mount;
		पूर्ण
		अगर ((sbi->s_inode_size < EXT4_GOOD_OLD_INODE_SIZE) ||
		    (!is_घातer_of_2(sbi->s_inode_size)) ||
		    (sbi->s_inode_size > blocksize)) अणु
			ext4_msg(sb, KERN_ERR,
			       "unsupported inode size: %d",
			       sbi->s_inode_size);
			ext4_msg(sb, KERN_ERR, "blocksize: %d", blocksize);
			जाओ failed_mount;
		पूर्ण
		/*
		 * i_aसमय_extra is the last extra field available क्रम
		 * [acm]बार in काष्ठा ext4_inode. Checking क्रम that
		 * field should suffice to ensure we have extra space
		 * क्रम all three.
		 */
		अगर (sbi->s_inode_size >= दुरत्व(काष्ठा ext4_inode, i_aसमय_extra) +
			माप(((काष्ठा ext4_inode *)0)->i_aसमय_extra)) अणु
			sb->s_समय_gran = 1;
			sb->s_समय_max = EXT4_EXTRA_TIMESTAMP_MAX;
		पूर्ण अन्यथा अणु
			sb->s_समय_gran = NSEC_PER_SEC;
			sb->s_समय_max = EXT4_NON_EXTRA_TIMESTAMP_MAX;
		पूर्ण
		sb->s_समय_min = EXT4_TIMESTAMP_MIN;
	पूर्ण
	अगर (sbi->s_inode_size > EXT4_GOOD_OLD_INODE_SIZE) अणु
		sbi->s_want_extra_isize = माप(काष्ठा ext4_inode) -
			EXT4_GOOD_OLD_INODE_SIZE;
		अगर (ext4_has_feature_extra_isize(sb)) अणु
			अचिन्हित v, max = (sbi->s_inode_size -
					   EXT4_GOOD_OLD_INODE_SIZE);

			v = le16_to_cpu(es->s_want_extra_isize);
			अगर (v > max) अणु
				ext4_msg(sb, KERN_ERR,
					 "bad s_want_extra_isize: %d", v);
				जाओ failed_mount;
			पूर्ण
			अगर (sbi->s_want_extra_isize < v)
				sbi->s_want_extra_isize = v;

			v = le16_to_cpu(es->s_min_extra_isize);
			अगर (v > max) अणु
				ext4_msg(sb, KERN_ERR,
					 "bad s_min_extra_isize: %d", v);
				जाओ failed_mount;
			पूर्ण
			अगर (sbi->s_want_extra_isize < v)
				sbi->s_want_extra_isize = v;
		पूर्ण
	पूर्ण

	अगर (sbi->s_es->s_mount_opts[0]) अणु
		अक्षर *s_mount_opts = kstrndup(sbi->s_es->s_mount_opts,
					      माप(sbi->s_es->s_mount_opts),
					      GFP_KERNEL);
		अगर (!s_mount_opts)
			जाओ failed_mount;
		अगर (!parse_options(s_mount_opts, sb, &parsed_opts, 0)) अणु
			ext4_msg(sb, KERN_WARNING,
				 "failed to parse options in superblock: %s",
				 s_mount_opts);
		पूर्ण
		kमुक्त(s_mount_opts);
	पूर्ण
	sbi->s_def_mount_opt = sbi->s_mount_opt;
	अगर (!parse_options((अक्षर *) data, sb, &parsed_opts, 0))
		जाओ failed_mount;

#अगर_घोषित CONFIG_UNICODE
	अगर (ext4_has_feature_हालfold(sb) && !sb->s_encoding) अणु
		स्थिर काष्ठा ext4_sb_encodings *encoding_info;
		काष्ठा unicode_map *encoding;
		__u16 encoding_flags;

		अगर (ext4_sb_पढ़ो_encoding(es, &encoding_info,
					  &encoding_flags)) अणु
			ext4_msg(sb, KERN_ERR,
				 "Encoding requested by superblock is unknown");
			जाओ failed_mount;
		पूर्ण

		encoding = utf8_load(encoding_info->version);
		अगर (IS_ERR(encoding)) अणु
			ext4_msg(sb, KERN_ERR,
				 "can't mount with superblock charset: %s-%s "
				 "not supported by the kernel. flags: 0x%x.",
				 encoding_info->name, encoding_info->version,
				 encoding_flags);
			जाओ failed_mount;
		पूर्ण
		ext4_msg(sb, KERN_INFO,"Using encoding defined by superblock: "
			 "%s-%s with flags 0x%hx", encoding_info->name,
			 encoding_info->version?:"\b", encoding_flags);

		sb->s_encoding = encoding;
		sb->s_encoding_flags = encoding_flags;
	पूर्ण
#पूर्ण_अगर

	अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA) अणु
		prपूर्णांकk_once(KERN_WARNING "EXT4-fs: Warning: mounting with data=journal disables delayed allocation, dioread_nolock, O_DIRECT and fast_commit support!\n");
		/* can't mount with both data=journal and dioपढ़ो_nolock. */
		clear_opt(sb, DIOREAD_NOLOCK);
		clear_opt2(sb, JOURNAL_FAST_COMMIT);
		अगर (test_opt2(sb, EXPLICIT_DELALLOC)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "both data=journal and delalloc");
			जाओ failed_mount;
		पूर्ण
		अगर (test_opt(sb, DAX_ALWAYS)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "both data=journal and dax");
			जाओ failed_mount;
		पूर्ण
		अगर (ext4_has_feature_encrypt(sb)) अणु
			ext4_msg(sb, KERN_WARNING,
				 "encrypted files will use data=ordered "
				 "instead of data journaling mode");
		पूर्ण
		अगर (test_opt(sb, DELALLOC))
			clear_opt(sb, DELALLOC);
	पूर्ण अन्यथा अणु
		sb->s_अगरlags |= SB_I_CGROUPWB;
	पूर्ण

	sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
		(test_opt(sb, POSIX_ACL) ? SB_POSIXACL : 0);

	अगर (le32_to_cpu(es->s_rev_level) == EXT4_GOOD_OLD_REV &&
	    (ext4_has_compat_features(sb) ||
	     ext4_has_ro_compat_features(sb) ||
	     ext4_has_incompat_features(sb)))
		ext4_msg(sb, KERN_WARNING,
		       "feature flags set on rev 0 fs, "
		       "running e2fsck is recommended");

	अगर (es->s_creator_os == cpu_to_le32(EXT4_OS_HURD)) अणु
		set_opt2(sb, HURD_COMPAT);
		अगर (ext4_has_feature_64bit(sb)) अणु
			ext4_msg(sb, KERN_ERR,
				 "The Hurd can't support 64-bit file systems");
			जाओ failed_mount;
		पूर्ण

		/*
		 * ea_inode feature uses l_i_version field which is not
		 * available in HURD_COMPAT mode.
		 */
		अगर (ext4_has_feature_ea_inode(sb)) अणु
			ext4_msg(sb, KERN_ERR,
				 "ea_inode feature is not supported for Hurd");
			जाओ failed_mount;
		पूर्ण
	पूर्ण

	अगर (IS_EXT2_SB(sb)) अणु
		अगर (ext2_feature_set_ok(sb))
			ext4_msg(sb, KERN_INFO, "mounting ext2 file system "
				 "using the ext4 subsystem");
		अन्यथा अणु
			/*
			 * If we're probing be silent, अगर this looks like
			 * it's actually an ext[34] fileप्रणाली.
			 */
			अगर (silent && ext4_feature_set_ok(sb, sb_rकरोnly(sb)))
				जाओ failed_mount;
			ext4_msg(sb, KERN_ERR, "couldn't mount as ext2 due "
				 "to feature incompatibilities");
			जाओ failed_mount;
		पूर्ण
	पूर्ण

	अगर (IS_EXT3_SB(sb)) अणु
		अगर (ext3_feature_set_ok(sb))
			ext4_msg(sb, KERN_INFO, "mounting ext3 file system "
				 "using the ext4 subsystem");
		अन्यथा अणु
			/*
			 * If we're probing be silent, अगर this looks like
			 * it's actually an ext4 fileप्रणाली.
			 */
			अगर (silent && ext4_feature_set_ok(sb, sb_rकरोnly(sb)))
				जाओ failed_mount;
			ext4_msg(sb, KERN_ERR, "couldn't mount as ext3 due "
				 "to feature incompatibilities");
			जाओ failed_mount;
		पूर्ण
	पूर्ण

	/*
	 * Check feature flags regardless of the revision level, since we
	 * previously didn't change the revision level when setting the flags,
	 * so there is a chance incompat flags are set on a rev 0 fileप्रणाली.
	 */
	अगर (!ext4_feature_set_ok(sb, (sb_rकरोnly(sb))))
		जाओ failed_mount;

	अगर (le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks) > (blocksize / 4)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Number of reserved GDT blocks insanely large: %d",
			 le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks));
		जाओ failed_mount;
	पूर्ण

	अगर (bdev_dax_supported(sb->s_bdev, blocksize))
		set_bit(EXT4_FLAGS_BDEV_IS_DAX, &sbi->s_ext4_flags);

	अगर (sbi->s_mount_opt & EXT4_MOUNT_DAX_ALWAYS) अणु
		अगर (ext4_has_feature_अंतरभूत_data(sb)) अणु
			ext4_msg(sb, KERN_ERR, "Cannot use DAX on a filesystem"
					" that may contain inline data");
			जाओ failed_mount;
		पूर्ण
		अगर (!test_bit(EXT4_FLAGS_BDEV_IS_DAX, &sbi->s_ext4_flags)) अणु
			ext4_msg(sb, KERN_ERR,
				"DAX unsupported by block device.");
			जाओ failed_mount;
		पूर्ण
	पूर्ण

	अगर (ext4_has_feature_encrypt(sb) && es->s_encryption_level) अणु
		ext4_msg(sb, KERN_ERR, "Unsupported encryption level %d",
			 es->s_encryption_level);
		जाओ failed_mount;
	पूर्ण

	अगर (sb->s_blocksize != blocksize) अणु
		/*
		 * bh must be released beक्रमe समाप्त_bdev(), otherwise
		 * it won't be मुक्तd and its page also. समाप्त_bdev()
		 * is called by sb_set_blocksize().
		 */
		brअन्यथा(bh);
		/* Validate the fileप्रणाली blocksize */
		अगर (!sb_set_blocksize(sb, blocksize)) अणु
			ext4_msg(sb, KERN_ERR, "bad block size %d",
					blocksize);
			bh = शून्य;
			जाओ failed_mount;
		पूर्ण

		logical_sb_block = sb_block * EXT4_MIN_BLOCK_SIZE;
		offset = करो_भाग(logical_sb_block, blocksize);
		bh = ext4_sb_bपढ़ो_unmovable(sb, logical_sb_block);
		अगर (IS_ERR(bh)) अणु
			ext4_msg(sb, KERN_ERR,
			       "Can't read superblock on 2nd try");
			ret = PTR_ERR(bh);
			bh = शून्य;
			जाओ failed_mount;
		पूर्ण
		es = (काष्ठा ext4_super_block *)(bh->b_data + offset);
		sbi->s_es = es;
		अगर (es->s_magic != cpu_to_le16(EXT4_SUPER_MAGIC)) अणु
			ext4_msg(sb, KERN_ERR,
			       "Magic mismatch, very weird!");
			जाओ failed_mount;
		पूर्ण
	पूर्ण

	has_huge_files = ext4_has_feature_huge_file(sb);
	sbi->s_biपंचांगap_maxbytes = ext4_max_biपंचांगap_size(sb->s_blocksize_bits,
						      has_huge_files);
	sb->s_maxbytes = ext4_max_size(sb->s_blocksize_bits, has_huge_files);

	sbi->s_desc_size = le16_to_cpu(es->s_desc_size);
	अगर (ext4_has_feature_64bit(sb)) अणु
		अगर (sbi->s_desc_size < EXT4_MIN_DESC_SIZE_64BIT ||
		    sbi->s_desc_size > EXT4_MAX_DESC_SIZE ||
		    !is_घातer_of_2(sbi->s_desc_size)) अणु
			ext4_msg(sb, KERN_ERR,
			       "unsupported descriptor size %lu",
			       sbi->s_desc_size);
			जाओ failed_mount;
		पूर्ण
	पूर्ण अन्यथा
		sbi->s_desc_size = EXT4_MIN_DESC_SIZE;

	sbi->s_blocks_per_group = le32_to_cpu(es->s_blocks_per_group);
	sbi->s_inodes_per_group = le32_to_cpu(es->s_inodes_per_group);

	sbi->s_inodes_per_block = blocksize / EXT4_INODE_SIZE(sb);
	अगर (sbi->s_inodes_per_block == 0)
		जाओ cantfind_ext4;
	अगर (sbi->s_inodes_per_group < sbi->s_inodes_per_block ||
	    sbi->s_inodes_per_group > blocksize * 8) अणु
		ext4_msg(sb, KERN_ERR, "invalid inodes per group: %lu\n",
			 sbi->s_inodes_per_group);
		जाओ failed_mount;
	पूर्ण
	sbi->s_itb_per_group = sbi->s_inodes_per_group /
					sbi->s_inodes_per_block;
	sbi->s_desc_per_block = blocksize / EXT4_DESC_SIZE(sb);
	sbi->s_sbh = bh;
	sbi->s_mount_state = le16_to_cpu(es->s_state);
	sbi->s_addr_per_block_bits = ilog2(EXT4_ADDR_PER_BLOCK(sb));
	sbi->s_desc_per_block_bits = ilog2(EXT4_DESC_PER_BLOCK(sb));

	क्रम (i = 0; i < 4; i++)
		sbi->s_hash_seed[i] = le32_to_cpu(es->s_hash_seed[i]);
	sbi->s_def_hash_version = es->s_def_hash_version;
	अगर (ext4_has_feature_dir_index(sb)) अणु
		i = le32_to_cpu(es->s_flags);
		अगर (i & EXT2_FLAGS_UNSIGNED_HASH)
			sbi->s_hash_अचिन्हित = 3;
		अन्यथा अगर ((i & EXT2_FLAGS_SIGNED_HASH) == 0) अणु
#अगर_घोषित __CHAR_UNSIGNED__
			अगर (!sb_rकरोnly(sb))
				es->s_flags |=
					cpu_to_le32(EXT2_FLAGS_UNSIGNED_HASH);
			sbi->s_hash_अचिन्हित = 3;
#अन्यथा
			अगर (!sb_rकरोnly(sb))
				es->s_flags |=
					cpu_to_le32(EXT2_FLAGS_SIGNED_HASH);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	/* Handle clustersize */
	clustersize = BLOCK_SIZE << le32_to_cpu(es->s_log_cluster_size);
	अगर (ext4_has_feature_bigalloc(sb)) अणु
		अगर (clustersize < blocksize) अणु
			ext4_msg(sb, KERN_ERR,
				 "cluster size (%d) smaller than "
				 "block size (%d)", clustersize, blocksize);
			जाओ failed_mount;
		पूर्ण
		sbi->s_cluster_bits = le32_to_cpu(es->s_log_cluster_size) -
			le32_to_cpu(es->s_log_block_size);
		sbi->s_clusters_per_group =
			le32_to_cpu(es->s_clusters_per_group);
		अगर (sbi->s_clusters_per_group > blocksize * 8) अणु
			ext4_msg(sb, KERN_ERR,
				 "#clusters per group too big: %lu",
				 sbi->s_clusters_per_group);
			जाओ failed_mount;
		पूर्ण
		अगर (sbi->s_blocks_per_group !=
		    (sbi->s_clusters_per_group * (clustersize / blocksize))) अणु
			ext4_msg(sb, KERN_ERR, "blocks per group (%lu) and "
				 "clusters per group (%lu) inconsistent",
				 sbi->s_blocks_per_group,
				 sbi->s_clusters_per_group);
			जाओ failed_mount;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (clustersize != blocksize) अणु
			ext4_msg(sb, KERN_ERR,
				 "fragment/cluster size (%d) != "
				 "block size (%d)", clustersize, blocksize);
			जाओ failed_mount;
		पूर्ण
		अगर (sbi->s_blocks_per_group > blocksize * 8) अणु
			ext4_msg(sb, KERN_ERR,
				 "#blocks per group too big: %lu",
				 sbi->s_blocks_per_group);
			जाओ failed_mount;
		पूर्ण
		sbi->s_clusters_per_group = sbi->s_blocks_per_group;
		sbi->s_cluster_bits = 0;
	पूर्ण
	sbi->s_cluster_ratio = clustersize / blocksize;

	/* Do we have standard group size of clustersize * 8 blocks ? */
	अगर (sbi->s_blocks_per_group == clustersize << 3)
		set_opt2(sb, STD_GROUP_SIZE);

	/*
	 * Test whether we have more sectors than will fit in sector_t,
	 * and whether the max offset is addressable by the page cache.
	 */
	err = generic_check_addressable(sb->s_blocksize_bits,
					ext4_blocks_count(es));
	अगर (err) अणु
		ext4_msg(sb, KERN_ERR, "filesystem"
			 " too large to mount safely on this system");
		जाओ failed_mount;
	पूर्ण

	अगर (EXT4_BLOCKS_PER_GROUP(sb) == 0)
		जाओ cantfind_ext4;

	/* check blocks count against device size */
	blocks_count = sb->s_bdev->bd_inode->i_size >> sb->s_blocksize_bits;
	अगर (blocks_count && ext4_blocks_count(es) > blocks_count) अणु
		ext4_msg(sb, KERN_WARNING, "bad geometry: block count %llu "
		       "exceeds size of device (%llu blocks)",
		       ext4_blocks_count(es), blocks_count);
		जाओ failed_mount;
	पूर्ण

	/*
	 * It makes no sense क्रम the first data block to be beyond the end
	 * of the fileप्रणाली.
	 */
	अगर (le32_to_cpu(es->s_first_data_block) >= ext4_blocks_count(es)) अणु
		ext4_msg(sb, KERN_WARNING, "bad geometry: first data "
			 "block %u is beyond end of filesystem (%llu)",
			 le32_to_cpu(es->s_first_data_block),
			 ext4_blocks_count(es));
		जाओ failed_mount;
	पूर्ण
	अगर ((es->s_first_data_block == 0) && (es->s_log_block_size == 0) &&
	    (sbi->s_cluster_ratio == 1)) अणु
		ext4_msg(sb, KERN_WARNING, "bad geometry: first data "
			 "block is 0 with a 1k block and cluster size");
		जाओ failed_mount;
	पूर्ण

	blocks_count = (ext4_blocks_count(es) -
			le32_to_cpu(es->s_first_data_block) +
			EXT4_BLOCKS_PER_GROUP(sb) - 1);
	करो_भाग(blocks_count, EXT4_BLOCKS_PER_GROUP(sb));
	अगर (blocks_count > ((uपूर्णांक64_t)1<<32) - EXT4_DESC_PER_BLOCK(sb)) अणु
		ext4_msg(sb, KERN_WARNING, "groups count too large: %llu "
		       "(block count %llu, first data block %u, "
		       "blocks per group %lu)", blocks_count,
		       ext4_blocks_count(es),
		       le32_to_cpu(es->s_first_data_block),
		       EXT4_BLOCKS_PER_GROUP(sb));
		जाओ failed_mount;
	पूर्ण
	sbi->s_groups_count = blocks_count;
	sbi->s_blockfile_groups = min_t(ext4_group_t, sbi->s_groups_count,
			(EXT4_MAX_BLOCK_खाता_PHYS / EXT4_BLOCKS_PER_GROUP(sb)));
	अगर (((u64)sbi->s_groups_count * sbi->s_inodes_per_group) !=
	    le32_to_cpu(es->s_inodes_count)) अणु
		ext4_msg(sb, KERN_ERR, "inodes count not valid: %u vs %llu",
			 le32_to_cpu(es->s_inodes_count),
			 ((u64)sbi->s_groups_count * sbi->s_inodes_per_group));
		ret = -EINVAL;
		जाओ failed_mount;
	पूर्ण
	db_count = (sbi->s_groups_count + EXT4_DESC_PER_BLOCK(sb) - 1) /
		   EXT4_DESC_PER_BLOCK(sb);
	अगर (ext4_has_feature_meta_bg(sb)) अणु
		अगर (le32_to_cpu(es->s_first_meta_bg) > db_count) अणु
			ext4_msg(sb, KERN_WARNING,
				 "first meta block group too large: %u "
				 "(group descriptor block count %u)",
				 le32_to_cpu(es->s_first_meta_bg), db_count);
			जाओ failed_mount;
		पूर्ण
	पूर्ण
	rcu_assign_poपूर्णांकer(sbi->s_group_desc,
			   kvदो_स्मृति_array(db_count,
					  माप(काष्ठा buffer_head *),
					  GFP_KERNEL));
	अगर (sbi->s_group_desc == शून्य) अणु
		ext4_msg(sb, KERN_ERR, "not enough memory");
		ret = -ENOMEM;
		जाओ failed_mount;
	पूर्ण

	bgl_lock_init(sbi->s_blockgroup_lock);

	/* Pre-पढ़ो the descriptors पूर्णांकo the buffer cache */
	क्रम (i = 0; i < db_count; i++) अणु
		block = descriptor_loc(sb, logical_sb_block, i);
		ext4_sb_bपढ़ोahead_unmovable(sb, block);
	पूर्ण

	क्रम (i = 0; i < db_count; i++) अणु
		काष्ठा buffer_head *bh;

		block = descriptor_loc(sb, logical_sb_block, i);
		bh = ext4_sb_bपढ़ो_unmovable(sb, block);
		अगर (IS_ERR(bh)) अणु
			ext4_msg(sb, KERN_ERR,
			       "can't read group descriptor %d", i);
			db_count = i;
			ret = PTR_ERR(bh);
			जाओ failed_mount2;
		पूर्ण
		rcu_पढ़ो_lock();
		rcu_dereference(sbi->s_group_desc)[i] = bh;
		rcu_पढ़ो_unlock();
	पूर्ण
	sbi->s_gdb_count = db_count;
	अगर (!ext4_check_descriptors(sb, logical_sb_block, &first_not_zeroed)) अणु
		ext4_msg(sb, KERN_ERR, "group descriptors corrupted!");
		ret = -EFSCORRUPTED;
		जाओ failed_mount2;
	पूर्ण

	समयr_setup(&sbi->s_err_report, prपूर्णांक_daily_error_info, 0);
	spin_lock_init(&sbi->s_error_lock);
	INIT_WORK(&sbi->s_error_work, flush_stashed_error_work);

	/* Register extent status tree shrinker */
	अगर (ext4_es_रेजिस्टर_shrinker(sbi))
		जाओ failed_mount3;

	sbi->s_stripe = ext4_get_stripe_size(sbi);
	sbi->s_extent_max_zeroout_kb = 32;

	/*
	 * set up enough so that it can पढ़ो an inode
	 */
	sb->s_op = &ext4_sops;
	sb->s_export_op = &ext4_export_ops;
	sb->s_xattr = ext4_xattr_handlers;
#अगर_घोषित CONFIG_FS_ENCRYPTION
	sb->s_cop = &ext4_cryptops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_VERITY
	sb->s_vop = &ext4_verityops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_QUOTA
	sb->dq_op = &ext4_quota_operations;
	अगर (ext4_has_feature_quota(sb))
		sb->s_qcop = &dquot_quotactl_sysfile_ops;
	अन्यथा
		sb->s_qcop = &ext4_qctl_operations;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP | QTYPE_MASK_PRJ;
#पूर्ण_अगर
	स_नकल(&sb->s_uuid, es->s_uuid, माप(es->s_uuid));

	INIT_LIST_HEAD(&sbi->s_orphan); /* unlinked but खोलो files */
	mutex_init(&sbi->s_orphan_lock);

	/* Initialize fast commit stuff */
	atomic_set(&sbi->s_fc_subtid, 0);
	atomic_set(&sbi->s_fc_ineligible_updates, 0);
	INIT_LIST_HEAD(&sbi->s_fc_q[FC_Q_MAIN]);
	INIT_LIST_HEAD(&sbi->s_fc_q[FC_Q_STAGING]);
	INIT_LIST_HEAD(&sbi->s_fc_dentry_q[FC_Q_MAIN]);
	INIT_LIST_HEAD(&sbi->s_fc_dentry_q[FC_Q_STAGING]);
	sbi->s_fc_bytes = 0;
	ext4_clear_mount_flag(sb, EXT4_MF_FC_INELIGIBLE);
	ext4_clear_mount_flag(sb, EXT4_MF_FC_COMMITTING);
	spin_lock_init(&sbi->s_fc_lock);
	स_रखो(&sbi->s_fc_stats, 0, माप(sbi->s_fc_stats));
	sbi->s_fc_replay_state.fc_regions = शून्य;
	sbi->s_fc_replay_state.fc_regions_size = 0;
	sbi->s_fc_replay_state.fc_regions_used = 0;
	sbi->s_fc_replay_state.fc_regions_valid = 0;
	sbi->s_fc_replay_state.fc_modअगरied_inodes = शून्य;
	sbi->s_fc_replay_state.fc_modअगरied_inodes_size = 0;
	sbi->s_fc_replay_state.fc_modअगरied_inodes_used = 0;

	sb->s_root = शून्य;

	needs_recovery = (es->s_last_orphan != 0 ||
			  ext4_has_feature_journal_needs_recovery(sb));

	अगर (ext4_has_feature_mmp(sb) && !sb_rकरोnly(sb))
		अगर (ext4_multi_mount_protect(sb, le64_to_cpu(es->s_mmp_block)))
			जाओ failed_mount3a;

	/*
	 * The first inode we look at is the journal inode.  Don't try
	 * root first: it may be modअगरied in the journal!
	 */
	अगर (!test_opt(sb, NOLOAD) && ext4_has_feature_journal(sb)) अणु
		err = ext4_load_journal(sb, es, parsed_opts.journal_devnum);
		अगर (err)
			जाओ failed_mount3a;
	पूर्ण अन्यथा अगर (test_opt(sb, NOLOAD) && !sb_rकरोnly(sb) &&
		   ext4_has_feature_journal_needs_recovery(sb)) अणु
		ext4_msg(sb, KERN_ERR, "required journal recovery "
		       "suppressed and not mounted read-only");
		जाओ failed_mount_wq;
	पूर्ण अन्यथा अणु
		/* Nojournal mode, all journal mount options are illegal */
		अगर (test_opt2(sb, EXPLICIT_JOURNAL_CHECKSUM)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "journal_checksum, fs mounted w/o journal");
			जाओ failed_mount_wq;
		पूर्ण
		अगर (test_opt(sb, JOURNAL_ASYNC_COMMIT)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "journal_async_commit, fs mounted w/o journal");
			जाओ failed_mount_wq;
		पूर्ण
		अगर (sbi->s_commit_पूर्णांकerval != JBD2_DEFAULT_MAX_COMMIT_AGE*HZ) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "commit=%lu, fs mounted w/o journal",
				 sbi->s_commit_पूर्णांकerval / HZ);
			जाओ failed_mount_wq;
		पूर्ण
		अगर (EXT4_MOUNT_DATA_FLAGS &
		    (sbi->s_mount_opt ^ sbi->s_def_mount_opt)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "data=, fs mounted w/o journal");
			जाओ failed_mount_wq;
		पूर्ण
		sbi->s_def_mount_opt &= ~EXT4_MOUNT_JOURNAL_CHECKSUM;
		clear_opt(sb, JOURNAL_CHECKSUM);
		clear_opt(sb, DATA_FLAGS);
		clear_opt2(sb, JOURNAL_FAST_COMMIT);
		sbi->s_journal = शून्य;
		needs_recovery = 0;
		जाओ no_journal;
	पूर्ण

	अगर (ext4_has_feature_64bit(sb) &&
	    !jbd2_journal_set_features(EXT4_SB(sb)->s_journal, 0, 0,
				       JBD2_FEATURE_INCOMPAT_64BIT)) अणु
		ext4_msg(sb, KERN_ERR, "Failed to set 64-bit journal feature");
		जाओ failed_mount_wq;
	पूर्ण

	अगर (!set_journal_csum_feature_set(sb)) अणु
		ext4_msg(sb, KERN_ERR, "Failed to set journal checksum "
			 "feature set");
		जाओ failed_mount_wq;
	पूर्ण

	अगर (test_opt2(sb, JOURNAL_FAST_COMMIT) &&
		!jbd2_journal_set_features(EXT4_SB(sb)->s_journal, 0, 0,
					  JBD2_FEATURE_INCOMPAT_FAST_COMMIT)) अणु
		ext4_msg(sb, KERN_ERR,
			"Failed to set fast commit journal feature");
		जाओ failed_mount_wq;
	पूर्ण

	/* We have now updated the journal अगर required, so we can
	 * validate the data journaling mode. */
	चयन (test_opt(sb, DATA_FLAGS)) अणु
	हाल 0:
		/* No mode set, assume a शेष based on the journal
		 * capabilities: ORDERED_DATA अगर the journal can
		 * cope, अन्यथा JOURNAL_DATA
		 */
		अगर (jbd2_journal_check_available_features
		    (sbi->s_journal, 0, 0, JBD2_FEATURE_INCOMPAT_REVOKE)) अणु
			set_opt(sb, ORDERED_DATA);
			sbi->s_def_mount_opt |= EXT4_MOUNT_ORDERED_DATA;
		पूर्ण अन्यथा अणु
			set_opt(sb, JOURNAL_DATA);
			sbi->s_def_mount_opt |= EXT4_MOUNT_JOURNAL_DATA;
		पूर्ण
		अवरोध;

	हाल EXT4_MOUNT_ORDERED_DATA:
	हाल EXT4_MOUNT_WRITEBACK_DATA:
		अगर (!jbd2_journal_check_available_features
		    (sbi->s_journal, 0, 0, JBD2_FEATURE_INCOMPAT_REVOKE)) अणु
			ext4_msg(sb, KERN_ERR, "Journal does not support "
			       "requested data journaling mode");
			जाओ failed_mount_wq;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_ORDERED_DATA &&
	    test_opt(sb, JOURNAL_ASYNC_COMMIT)) अणु
		ext4_msg(sb, KERN_ERR, "can't mount with "
			"journal_async_commit in data=ordered mode");
		जाओ failed_mount_wq;
	पूर्ण

	set_task_ioprio(sbi->s_journal->j_task, parsed_opts.journal_ioprio);

	sbi->s_journal->j_submit_inode_data_buffers =
		ext4_journal_submit_inode_data_buffers;
	sbi->s_journal->j_finish_inode_data_buffers =
		ext4_journal_finish_inode_data_buffers;

no_journal:
	अगर (!test_opt(sb, NO_MBCACHE)) अणु
		sbi->s_ea_block_cache = ext4_xattr_create_cache();
		अगर (!sbi->s_ea_block_cache) अणु
			ext4_msg(sb, KERN_ERR,
				 "Failed to create ea_block_cache");
			जाओ failed_mount_wq;
		पूर्ण

		अगर (ext4_has_feature_ea_inode(sb)) अणु
			sbi->s_ea_inode_cache = ext4_xattr_create_cache();
			अगर (!sbi->s_ea_inode_cache) अणु
				ext4_msg(sb, KERN_ERR,
					 "Failed to create ea_inode_cache");
				जाओ failed_mount_wq;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ext4_has_feature_verity(sb) && blocksize != PAGE_SIZE) अणु
		ext4_msg(sb, KERN_ERR, "Unsupported blocksize for fs-verity");
		जाओ failed_mount_wq;
	पूर्ण

	अगर (DUMMY_ENCRYPTION_ENABLED(sbi) && !sb_rकरोnly(sb) &&
	    !ext4_has_feature_encrypt(sb)) अणु
		ext4_set_feature_encrypt(sb);
		ext4_commit_super(sb);
	पूर्ण

	/*
	 * Get the # of file प्रणाली overhead blocks from the
	 * superblock अगर present.
	 */
	अगर (es->s_overhead_clusters)
		sbi->s_overhead = le32_to_cpu(es->s_overhead_clusters);
	अन्यथा अणु
		err = ext4_calculate_overhead(sb);
		अगर (err)
			जाओ failed_mount_wq;
	पूर्ण

	/*
	 * The maximum number of concurrent works can be high and
	 * concurrency isn't really necessary.  Limit it to 1.
	 */
	EXT4_SB(sb)->rsv_conversion_wq =
		alloc_workqueue("ext4-rsv-conversion", WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	अगर (!EXT4_SB(sb)->rsv_conversion_wq) अणु
		prपूर्णांकk(KERN_ERR "EXT4-fs: failed to create workqueue\n");
		ret = -ENOMEM;
		जाओ failed_mount4;
	पूर्ण

	/*
	 * The jbd2_journal_load will have करोne any necessary log recovery,
	 * so we can safely mount the rest of the fileप्रणाली now.
	 */

	root = ext4_iget(sb, EXT4_ROOT_INO, EXT4_IGET_SPECIAL);
	अगर (IS_ERR(root)) अणु
		ext4_msg(sb, KERN_ERR, "get root inode failed");
		ret = PTR_ERR(root);
		root = शून्य;
		जाओ failed_mount4;
	पूर्ण
	अगर (!S_ISसूची(root->i_mode) || !root->i_blocks || !root->i_size) अणु
		ext4_msg(sb, KERN_ERR, "corrupt root inode, run e2fsck");
		iput(root);
		जाओ failed_mount4;
	पूर्ण

	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		ext4_msg(sb, KERN_ERR, "get root dentry failed");
		ret = -ENOMEM;
		जाओ failed_mount4;
	पूर्ण

	ret = ext4_setup_super(sb, es, sb_rकरोnly(sb));
	अगर (ret == -EROFS) अणु
		sb->s_flags |= SB_RDONLY;
		ret = 0;
	पूर्ण अन्यथा अगर (ret)
		जाओ failed_mount4a;

	ext4_set_resv_clusters(sb);

	अगर (test_opt(sb, BLOCK_VALIDITY)) अणु
		err = ext4_setup_प्रणाली_zone(sb);
		अगर (err) अणु
			ext4_msg(sb, KERN_ERR, "failed to initialize system "
				 "zone (%d)", err);
			जाओ failed_mount4a;
		पूर्ण
	पूर्ण
	ext4_fc_replay_cleanup(sb);

	ext4_ext_init(sb);

	/*
	 * Enable optimize_scan अगर number of groups is > threshold. This can be
	 * turned off by passing "mb_optimize_scan=0". This can also be
	 * turned on क्रमcefully by passing "mb_optimize_scan=1".
	 */
	अगर (parsed_opts.mb_optimize_scan == 1)
		set_opt2(sb, MB_OPTIMIZE_SCAN);
	अन्यथा अगर (parsed_opts.mb_optimize_scan == 0)
		clear_opt2(sb, MB_OPTIMIZE_SCAN);
	अन्यथा अगर (sbi->s_groups_count >= MB_DEFAULT_LINEAR_SCAN_THRESHOLD)
		set_opt2(sb, MB_OPTIMIZE_SCAN);

	err = ext4_mb_init(sb);
	अगर (err) अणु
		ext4_msg(sb, KERN_ERR, "failed to initialize mballoc (%d)",
			 err);
		जाओ failed_mount5;
	पूर्ण

	/*
	 * We can only set up the journal commit callback once
	 * mballoc is initialized
	 */
	अगर (sbi->s_journal)
		sbi->s_journal->j_commit_callback =
			ext4_journal_commit_callback;

	block = ext4_count_मुक्त_clusters(sb);
	ext4_मुक्त_blocks_count_set(sbi->s_es,
				   EXT4_C2B(sbi, block));
	err = percpu_counter_init(&sbi->s_मुक्तclusters_counter, block,
				  GFP_KERNEL);
	अगर (!err) अणु
		अचिन्हित दीर्घ मुक्तi = ext4_count_मुक्त_inodes(sb);
		sbi->s_es->s_मुक्त_inodes_count = cpu_to_le32(मुक्तi);
		err = percpu_counter_init(&sbi->s_मुक्तinodes_counter, मुक्तi,
					  GFP_KERNEL);
	पूर्ण
	अगर (!err)
		err = percpu_counter_init(&sbi->s_dirs_counter,
					  ext4_count_dirs(sb), GFP_KERNEL);
	अगर (!err)
		err = percpu_counter_init(&sbi->s_dirtyclusters_counter, 0,
					  GFP_KERNEL);
	अगर (!err)
		err = percpu_counter_init(&sbi->s_sra_exceeded_retry_limit, 0,
					  GFP_KERNEL);
	अगर (!err)
		err = percpu_init_rwsem(&sbi->s_ग_लिखोpages_rwsem);

	अगर (err) अणु
		ext4_msg(sb, KERN_ERR, "insufficient memory");
		जाओ failed_mount6;
	पूर्ण

	अगर (ext4_has_feature_flex_bg(sb))
		अगर (!ext4_fill_flex_info(sb)) अणु
			ext4_msg(sb, KERN_ERR,
			       "unable to initialize "
			       "flex_bg meta info!");
			जाओ failed_mount6;
		पूर्ण

	err = ext4_रेजिस्टर_li_request(sb, first_not_zeroed);
	अगर (err)
		जाओ failed_mount6;

	err = ext4_रेजिस्टर_sysfs(sb);
	अगर (err)
		जाओ failed_mount7;

#अगर_घोषित CONFIG_QUOTA
	/* Enable quota usage during mount. */
	अगर (ext4_has_feature_quota(sb) && !sb_rकरोnly(sb)) अणु
		err = ext4_enable_quotas(sb);
		अगर (err)
			जाओ failed_mount8;
	पूर्ण
#पूर्ण_अगर  /* CONFIG_QUOTA */

	/*
	 * Save the original bdev mapping's wb_err value which could be
	 * used to detect the metadata async ग_लिखो error.
	 */
	spin_lock_init(&sbi->s_bdev_wb_lock);
	errseq_check_and_advance(&sb->s_bdev->bd_inode->i_mapping->wb_err,
				 &sbi->s_bdev_wb_err);
	sb->s_bdev->bd_super = sb;
	EXT4_SB(sb)->s_mount_state |= EXT4_ORPHAN_FS;
	ext4_orphan_cleanup(sb, es);
	EXT4_SB(sb)->s_mount_state &= ~EXT4_ORPHAN_FS;
	अगर (needs_recovery) अणु
		ext4_msg(sb, KERN_INFO, "recovery complete");
		err = ext4_mark_recovery_complete(sb, es);
		अगर (err)
			जाओ failed_mount8;
	पूर्ण
	अगर (EXT4_SB(sb)->s_journal) अणु
		अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA)
			descr = " journalled data mode";
		अन्यथा अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_ORDERED_DATA)
			descr = " ordered data mode";
		अन्यथा
			descr = " writeback data mode";
	पूर्ण अन्यथा
		descr = "out journal";

	अगर (test_opt(sb, DISCARD)) अणु
		काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
		अगर (!blk_queue_discard(q))
			ext4_msg(sb, KERN_WARNING,
				 "mounting with \"discard\" option, but "
				 "the device does not support discard");
	पूर्ण

	अगर (___ratelimit(&ext4_mount_msg_ratelimit, "EXT4-fs mount"))
		ext4_msg(sb, KERN_INFO, "mounted filesystem with%s. "
			 "Opts: %.*s%s%s. Quota mode: %s.", descr,
			 (पूर्णांक) माप(sbi->s_es->s_mount_opts),
			 sbi->s_es->s_mount_opts,
			 *sbi->s_es->s_mount_opts ? "; " : "", orig_data,
			 ext4_quota_mode(sb));

	अगर (es->s_error_count)
		mod_समयr(&sbi->s_err_report, jअगरfies + 300*HZ); /* 5 minutes */

	/* Enable message ratelimiting. Default is 10 messages per 5 secs. */
	ratelimit_state_init(&sbi->s_err_ratelimit_state, 5 * HZ, 10);
	ratelimit_state_init(&sbi->s_warning_ratelimit_state, 5 * HZ, 10);
	ratelimit_state_init(&sbi->s_msg_ratelimit_state, 5 * HZ, 10);
	atomic_set(&sbi->s_warning_count, 0);
	atomic_set(&sbi->s_msg_count, 0);

	kमुक्त(orig_data);
	वापस 0;

cantfind_ext4:
	अगर (!silent)
		ext4_msg(sb, KERN_ERR, "VFS: Can't find ext4 filesystem");
	जाओ failed_mount;

failed_mount8:
	ext4_unरेजिस्टर_sysfs(sb);
	kobject_put(&sbi->s_kobj);
failed_mount7:
	ext4_unरेजिस्टर_li_request(sb);
failed_mount6:
	ext4_mb_release(sb);
	rcu_पढ़ो_lock();
	flex_groups = rcu_dereference(sbi->s_flex_groups);
	अगर (flex_groups) अणु
		क्रम (i = 0; i < sbi->s_flex_groups_allocated; i++)
			kvमुक्त(flex_groups[i]);
		kvमुक्त(flex_groups);
	पूर्ण
	rcu_पढ़ो_unlock();
	percpu_counter_destroy(&sbi->s_मुक्तclusters_counter);
	percpu_counter_destroy(&sbi->s_मुक्तinodes_counter);
	percpu_counter_destroy(&sbi->s_dirs_counter);
	percpu_counter_destroy(&sbi->s_dirtyclusters_counter);
	percpu_counter_destroy(&sbi->s_sra_exceeded_retry_limit);
	percpu_मुक्त_rwsem(&sbi->s_ग_लिखोpages_rwsem);
failed_mount5:
	ext4_ext_release(sb);
	ext4_release_प्रणाली_zone(sb);
failed_mount4a:
	dput(sb->s_root);
	sb->s_root = शून्य;
failed_mount4:
	ext4_msg(sb, KERN_ERR, "mount failed");
	अगर (EXT4_SB(sb)->rsv_conversion_wq)
		destroy_workqueue(EXT4_SB(sb)->rsv_conversion_wq);
failed_mount_wq:
	ext4_xattr_destroy_cache(sbi->s_ea_inode_cache);
	sbi->s_ea_inode_cache = शून्य;

	ext4_xattr_destroy_cache(sbi->s_ea_block_cache);
	sbi->s_ea_block_cache = शून्य;

	अगर (sbi->s_journal) अणु
		jbd2_journal_destroy(sbi->s_journal);
		sbi->s_journal = शून्य;
	पूर्ण
failed_mount3a:
	ext4_es_unरेजिस्टर_shrinker(sbi);
failed_mount3:
	flush_work(&sbi->s_error_work);
	del_समयr_sync(&sbi->s_err_report);
	अगर (sbi->s_mmp_tsk)
		kthपढ़ो_stop(sbi->s_mmp_tsk);
failed_mount2:
	rcu_पढ़ो_lock();
	group_desc = rcu_dereference(sbi->s_group_desc);
	क्रम (i = 0; i < db_count; i++)
		brअन्यथा(group_desc[i]);
	kvमुक्त(group_desc);
	rcu_पढ़ो_unlock();
failed_mount:
	अगर (sbi->s_chksum_driver)
		crypto_मुक्त_shash(sbi->s_chksum_driver);

#अगर_घोषित CONFIG_UNICODE
	utf8_unload(sb->s_encoding);
#पूर्ण_अगर

#अगर_घोषित CONFIG_QUOTA
	क्रम (i = 0; i < EXT4_MAXQUOTAS; i++)
		kमुक्त(get_qf_name(sb, sbi, i));
#पूर्ण_अगर
	fscrypt_मुक्त_dummy_policy(&sbi->s_dummy_enc_policy);
	/* ext4_blkdev_हटाओ() calls समाप्त_bdev(), release bh beक्रमe it. */
	brअन्यथा(bh);
	ext4_blkdev_हटाओ(sbi);
out_fail:
	sb->s_fs_info = शून्य;
	kमुक्त(sbi->s_blockgroup_lock);
out_मुक्त_base:
	kमुक्त(sbi);
	kमुक्त(orig_data);
	fs_put_dax(dax_dev);
	वापस err ? err : ret;
पूर्ण

/*
 * Setup any per-fs journal parameters now.  We'll करो this both on
 * initial mount, once the journal has been initialised but beक्रमe we've
 * करोne any recovery; and again on any subsequent remount.
 */
अटल व्योम ext4_init_journal_params(काष्ठा super_block *sb, journal_t *journal)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	journal->j_commit_पूर्णांकerval = sbi->s_commit_पूर्णांकerval;
	journal->j_min_batch_समय = sbi->s_min_batch_समय;
	journal->j_max_batch_समय = sbi->s_max_batch_समय;
	ext4_fc_init(sb, journal);

	ग_लिखो_lock(&journal->j_state_lock);
	अगर (test_opt(sb, BARRIER))
		journal->j_flags |= JBD2_BARRIER;
	अन्यथा
		journal->j_flags &= ~JBD2_BARRIER;
	अगर (test_opt(sb, DATA_ERR_ABORT))
		journal->j_flags |= JBD2_ABORT_ON_SYNCDATA_ERR;
	अन्यथा
		journal->j_flags &= ~JBD2_ABORT_ON_SYNCDATA_ERR;
	ग_लिखो_unlock(&journal->j_state_lock);
पूर्ण

अटल काष्ठा inode *ext4_get_journal_inode(काष्ठा super_block *sb,
					     अचिन्हित पूर्णांक journal_inum)
अणु
	काष्ठा inode *journal_inode;

	/*
	 * Test क्रम the existence of a valid inode on disk.  Bad things
	 * happen अगर we iget() an unused inode, as the subsequent iput()
	 * will try to delete it.
	 */
	journal_inode = ext4_iget(sb, journal_inum, EXT4_IGET_SPECIAL);
	अगर (IS_ERR(journal_inode)) अणु
		ext4_msg(sb, KERN_ERR, "no journal found");
		वापस शून्य;
	पूर्ण
	अगर (!journal_inode->i_nlink) अणु
		make_bad_inode(journal_inode);
		iput(journal_inode);
		ext4_msg(sb, KERN_ERR, "journal inode is deleted");
		वापस शून्य;
	पूर्ण

	jbd_debug(2, "Journal inode found at %p: %lld bytes\n",
		  journal_inode, journal_inode->i_size);
	अगर (!S_ISREG(journal_inode->i_mode)) अणु
		ext4_msg(sb, KERN_ERR, "invalid journal inode");
		iput(journal_inode);
		वापस शून्य;
	पूर्ण
	वापस journal_inode;
पूर्ण

अटल journal_t *ext4_get_journal(काष्ठा super_block *sb,
				   अचिन्हित पूर्णांक journal_inum)
अणु
	काष्ठा inode *journal_inode;
	journal_t *journal;

	अगर (WARN_ON_ONCE(!ext4_has_feature_journal(sb)))
		वापस शून्य;

	journal_inode = ext4_get_journal_inode(sb, journal_inum);
	अगर (!journal_inode)
		वापस शून्य;

	journal = jbd2_journal_init_inode(journal_inode);
	अगर (!journal) अणु
		ext4_msg(sb, KERN_ERR, "Could not load journal inode");
		iput(journal_inode);
		वापस शून्य;
	पूर्ण
	journal->j_निजी = sb;
	ext4_init_journal_params(sb, journal);
	वापस journal;
पूर्ण

अटल journal_t *ext4_get_dev_journal(काष्ठा super_block *sb,
				       dev_t j_dev)
अणु
	काष्ठा buffer_head *bh;
	journal_t *journal;
	ext4_fsblk_t start;
	ext4_fsblk_t len;
	पूर्णांक hblock, blocksize;
	ext4_fsblk_t sb_block;
	अचिन्हित दीर्घ offset;
	काष्ठा ext4_super_block *es;
	काष्ठा block_device *bdev;

	अगर (WARN_ON_ONCE(!ext4_has_feature_journal(sb)))
		वापस शून्य;

	bdev = ext4_blkdev_get(j_dev, sb);
	अगर (bdev == शून्य)
		वापस शून्य;

	blocksize = sb->s_blocksize;
	hblock = bdev_logical_block_size(bdev);
	अगर (blocksize < hblock) अणु
		ext4_msg(sb, KERN_ERR,
			"blocksize too small for journal device");
		जाओ out_bdev;
	पूर्ण

	sb_block = EXT4_MIN_BLOCK_SIZE / blocksize;
	offset = EXT4_MIN_BLOCK_SIZE % blocksize;
	set_blocksize(bdev, blocksize);
	अगर (!(bh = __bपढ़ो(bdev, sb_block, blocksize))) अणु
		ext4_msg(sb, KERN_ERR, "couldn't read superblock of "
		       "external journal");
		जाओ out_bdev;
	पूर्ण

	es = (काष्ठा ext4_super_block *) (bh->b_data + offset);
	अगर ((le16_to_cpu(es->s_magic) != EXT4_SUPER_MAGIC) ||
	    !(le32_to_cpu(es->s_feature_incompat) &
	      EXT4_FEATURE_INCOMPAT_JOURNAL_DEV)) अणु
		ext4_msg(sb, KERN_ERR, "external journal has "
					"bad superblock");
		brअन्यथा(bh);
		जाओ out_bdev;
	पूर्ण

	अगर ((le32_to_cpu(es->s_feature_ro_compat) &
	     EXT4_FEATURE_RO_COMPAT_METADATA_CSUM) &&
	    es->s_checksum != ext4_superblock_csum(sb, es)) अणु
		ext4_msg(sb, KERN_ERR, "external journal has "
				       "corrupt superblock");
		brअन्यथा(bh);
		जाओ out_bdev;
	पूर्ण

	अगर (स_भेद(EXT4_SB(sb)->s_es->s_journal_uuid, es->s_uuid, 16)) अणु
		ext4_msg(sb, KERN_ERR, "journal UUID does not match");
		brअन्यथा(bh);
		जाओ out_bdev;
	पूर्ण

	len = ext4_blocks_count(es);
	start = sb_block + 1;
	brअन्यथा(bh);	/* we're करोne with the superblock */

	journal = jbd2_journal_init_dev(bdev, sb->s_bdev,
					start, len, blocksize);
	अगर (!journal) अणु
		ext4_msg(sb, KERN_ERR, "failed to create device journal");
		जाओ out_bdev;
	पूर्ण
	journal->j_निजी = sb;
	अगर (ext4_पढ़ो_bh_lock(journal->j_sb_buffer, REQ_META | REQ_PRIO, true)) अणु
		ext4_msg(sb, KERN_ERR, "I/O error on journal device");
		जाओ out_journal;
	पूर्ण
	अगर (be32_to_cpu(journal->j_superblock->s_nr_users) != 1) अणु
		ext4_msg(sb, KERN_ERR, "External journal has more than one "
					"user (unsupported) - %d",
			be32_to_cpu(journal->j_superblock->s_nr_users));
		जाओ out_journal;
	पूर्ण
	EXT4_SB(sb)->s_journal_bdev = bdev;
	ext4_init_journal_params(sb, journal);
	वापस journal;

out_journal:
	jbd2_journal_destroy(journal);
out_bdev:
	ext4_blkdev_put(bdev);
	वापस शून्य;
पूर्ण

अटल पूर्णांक ext4_load_journal(काष्ठा super_block *sb,
			     काष्ठा ext4_super_block *es,
			     अचिन्हित दीर्घ journal_devnum)
अणु
	journal_t *journal;
	अचिन्हित पूर्णांक journal_inum = le32_to_cpu(es->s_journal_inum);
	dev_t journal_dev;
	पूर्णांक err = 0;
	पूर्णांक really_पढ़ो_only;
	पूर्णांक journal_dev_ro;

	अगर (WARN_ON_ONCE(!ext4_has_feature_journal(sb)))
		वापस -EFSCORRUPTED;

	अगर (journal_devnum &&
	    journal_devnum != le32_to_cpu(es->s_journal_dev)) अणु
		ext4_msg(sb, KERN_INFO, "external journal device major/minor "
			"numbers have changed");
		journal_dev = new_decode_dev(journal_devnum);
	पूर्ण अन्यथा
		journal_dev = new_decode_dev(le32_to_cpu(es->s_journal_dev));

	अगर (journal_inum && journal_dev) अणु
		ext4_msg(sb, KERN_ERR,
			 "filesystem has both journal inode and journal device!");
		वापस -EINVAL;
	पूर्ण

	अगर (journal_inum) अणु
		journal = ext4_get_journal(sb, journal_inum);
		अगर (!journal)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		journal = ext4_get_dev_journal(sb, journal_dev);
		अगर (!journal)
			वापस -EINVAL;
	पूर्ण

	journal_dev_ro = bdev_पढ़ो_only(journal->j_dev);
	really_पढ़ो_only = bdev_पढ़ो_only(sb->s_bdev) | journal_dev_ro;

	अगर (journal_dev_ro && !sb_rकरोnly(sb)) अणु
		ext4_msg(sb, KERN_ERR,
			 "journal device read-only, try mounting with '-o ro'");
		err = -EROFS;
		जाओ err_out;
	पूर्ण

	/*
	 * Are we loading a blank journal or perक्रमming recovery after a
	 * crash?  For recovery, we need to check in advance whether we
	 * can get पढ़ो-ग_लिखो access to the device.
	 */
	अगर (ext4_has_feature_journal_needs_recovery(sb)) अणु
		अगर (sb_rकरोnly(sb)) अणु
			ext4_msg(sb, KERN_INFO, "INFO: recovery "
					"required on readonly filesystem");
			अगर (really_पढ़ो_only) अणु
				ext4_msg(sb, KERN_ERR, "write access "
					"unavailable, cannot proceed "
					"(try mounting with noload)");
				err = -EROFS;
				जाओ err_out;
			पूर्ण
			ext4_msg(sb, KERN_INFO, "write access will "
			       "be enabled during recovery");
		पूर्ण
	पूर्ण

	अगर (!(journal->j_flags & JBD2_BARRIER))
		ext4_msg(sb, KERN_INFO, "barriers disabled");

	अगर (!ext4_has_feature_journal_needs_recovery(sb))
		err = jbd2_journal_wipe(journal, !really_पढ़ो_only);
	अगर (!err) अणु
		अक्षर *save = kदो_स्मृति(EXT4_S_ERR_LEN, GFP_KERNEL);
		अगर (save)
			स_नकल(save, ((अक्षर *) es) +
			       EXT4_S_ERR_START, EXT4_S_ERR_LEN);
		err = jbd2_journal_load(journal);
		अगर (save)
			स_नकल(((अक्षर *) es) + EXT4_S_ERR_START,
			       save, EXT4_S_ERR_LEN);
		kमुक्त(save);
	पूर्ण

	अगर (err) अणु
		ext4_msg(sb, KERN_ERR, "error loading journal");
		जाओ err_out;
	पूर्ण

	EXT4_SB(sb)->s_journal = journal;
	err = ext4_clear_journal_err(sb, es);
	अगर (err) अणु
		EXT4_SB(sb)->s_journal = शून्य;
		jbd2_journal_destroy(journal);
		वापस err;
	पूर्ण

	अगर (!really_पढ़ो_only && journal_devnum &&
	    journal_devnum != le32_to_cpu(es->s_journal_dev)) अणु
		es->s_journal_dev = cpu_to_le32(journal_devnum);

		/* Make sure we flush the recovery flag to disk. */
		ext4_commit_super(sb);
	पूर्ण

	वापस 0;

err_out:
	jbd2_journal_destroy(journal);
	वापस err;
पूर्ण

/* Copy state of EXT4_SB(sb) पूर्णांकo buffer क्रम on-disk superblock */
अटल व्योम ext4_update_super(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा buffer_head *sbh = sbi->s_sbh;

	lock_buffer(sbh);
	/*
	 * If the file प्रणाली is mounted पढ़ो-only, करोn't update the
	 * superblock ग_लिखो समय.  This aव्योमs updating the superblock
	 * ग_लिखो समय when we are mounting the root file प्रणाली
	 * पढ़ो/only but we need to replay the journal; at that poपूर्णांक,
	 * क्रम people who are east of GMT and who make their घड़ी
	 * tick in स_स्थानीय क्रम Winकरोws bug-क्रम-bug compatibility,
	 * the घड़ी is set in the future, and this will cause e2fsck
	 * to complain and क्रमce a full file प्रणाली check.
	 */
	अगर (!(sb->s_flags & SB_RDONLY))
		ext4_update_tstamp(es, s_wसमय);
	es->s_kbytes_written =
		cpu_to_le64(sbi->s_kbytes_written +
		    ((part_stat_पढ़ो(sb->s_bdev, sectors[STAT_WRITE]) -
		      sbi->s_sectors_written_start) >> 1));
	अगर (percpu_counter_initialized(&sbi->s_मुक्तclusters_counter))
		ext4_मुक्त_blocks_count_set(es,
			EXT4_C2B(sbi, percpu_counter_sum_positive(
				&sbi->s_मुक्तclusters_counter)));
	अगर (percpu_counter_initialized(&sbi->s_मुक्तinodes_counter))
		es->s_मुक्त_inodes_count =
			cpu_to_le32(percpu_counter_sum_positive(
				&sbi->s_मुक्तinodes_counter));
	/* Copy error inक्रमmation to the on-disk superblock */
	spin_lock(&sbi->s_error_lock);
	अगर (sbi->s_add_error_count > 0) अणु
		es->s_state |= cpu_to_le16(EXT4_ERROR_FS);
		अगर (!es->s_first_error_समय && !es->s_first_error_समय_hi) अणु
			__ext4_update_tstamp(&es->s_first_error_समय,
					     &es->s_first_error_समय_hi,
					     sbi->s_first_error_समय);
			म_नकलन(es->s_first_error_func, sbi->s_first_error_func,
				माप(es->s_first_error_func));
			es->s_first_error_line =
				cpu_to_le32(sbi->s_first_error_line);
			es->s_first_error_ino =
				cpu_to_le32(sbi->s_first_error_ino);
			es->s_first_error_block =
				cpu_to_le64(sbi->s_first_error_block);
			es->s_first_error_errcode =
				ext4_त्रुटि_सं_to_code(sbi->s_first_error_code);
		पूर्ण
		__ext4_update_tstamp(&es->s_last_error_समय,
				     &es->s_last_error_समय_hi,
				     sbi->s_last_error_समय);
		म_नकलन(es->s_last_error_func, sbi->s_last_error_func,
			माप(es->s_last_error_func));
		es->s_last_error_line = cpu_to_le32(sbi->s_last_error_line);
		es->s_last_error_ino = cpu_to_le32(sbi->s_last_error_ino);
		es->s_last_error_block = cpu_to_le64(sbi->s_last_error_block);
		es->s_last_error_errcode =
				ext4_त्रुटि_सं_to_code(sbi->s_last_error_code);
		/*
		 * Start the daily error reporting function अगर it hasn't been
		 * started alपढ़ोy
		 */
		अगर (!es->s_error_count)
			mod_समयr(&sbi->s_err_report, jअगरfies + 24*60*60*HZ);
		le32_add_cpu(&es->s_error_count, sbi->s_add_error_count);
		sbi->s_add_error_count = 0;
	पूर्ण
	spin_unlock(&sbi->s_error_lock);

	ext4_superblock_csum_set(sb);
	unlock_buffer(sbh);
पूर्ण

अटल पूर्णांक ext4_commit_super(काष्ठा super_block *sb)
अणु
	काष्ठा buffer_head *sbh = EXT4_SB(sb)->s_sbh;
	पूर्णांक error = 0;

	अगर (!sbh)
		वापस -EINVAL;
	अगर (block_device_ejected(sb))
		वापस -ENODEV;

	ext4_update_super(sb);

	अगर (buffer_ग_लिखो_io_error(sbh) || !buffer_uptodate(sbh)) अणु
		/*
		 * Oh, dear.  A previous attempt to ग_लिखो the
		 * superblock failed.  This could happen because the
		 * USB device was yanked out.  Or it could happen to
		 * be a transient ग_लिखो error and maybe the block will
		 * be remapped.  Nothing we can करो but to retry the
		 * ग_लिखो and hope क्रम the best.
		 */
		ext4_msg(sb, KERN_ERR, "previous I/O error to "
		       "superblock detected");
		clear_buffer_ग_लिखो_io_error(sbh);
		set_buffer_uptodate(sbh);
	पूर्ण
	BUFFER_TRACE(sbh, "marking dirty");
	mark_buffer_dirty(sbh);
	error = __sync_dirty_buffer(sbh,
		REQ_SYNC | (test_opt(sb, BARRIER) ? REQ_FUA : 0));
	अगर (buffer_ग_लिखो_io_error(sbh)) अणु
		ext4_msg(sb, KERN_ERR, "I/O error while writing "
		       "superblock");
		clear_buffer_ग_लिखो_io_error(sbh);
		set_buffer_uptodate(sbh);
	पूर्ण
	वापस error;
पूर्ण

/*
 * Have we just finished recovery?  If so, and अगर we are mounting (or
 * remounting) the fileप्रणाली पढ़ोonly, then we will end up with a
 * consistent fs on disk.  Record that fact.
 */
अटल पूर्णांक ext4_mark_recovery_complete(काष्ठा super_block *sb,
				       काष्ठा ext4_super_block *es)
अणु
	पूर्णांक err;
	journal_t *journal = EXT4_SB(sb)->s_journal;

	अगर (!ext4_has_feature_journal(sb)) अणु
		अगर (journal != शून्य) अणु
			ext4_error(sb, "Journal got removed while the fs was "
				   "mounted!");
			वापस -EFSCORRUPTED;
		पूर्ण
		वापस 0;
	पूर्ण
	jbd2_journal_lock_updates(journal);
	err = jbd2_journal_flush(journal);
	अगर (err < 0)
		जाओ out;

	अगर (ext4_has_feature_journal_needs_recovery(sb) && sb_rकरोnly(sb)) अणु
		ext4_clear_feature_journal_needs_recovery(sb);
		ext4_commit_super(sb);
	पूर्ण
out:
	jbd2_journal_unlock_updates(journal);
	वापस err;
पूर्ण

/*
 * If we are mounting (or पढ़ो-ग_लिखो remounting) a fileप्रणाली whose journal
 * has recorded an error from a previous lअगरeसमय, move that error to the
 * मुख्य fileप्रणाली now.
 */
अटल पूर्णांक ext4_clear_journal_err(काष्ठा super_block *sb,
				   काष्ठा ext4_super_block *es)
अणु
	journal_t *journal;
	पूर्णांक j_त्रुटि_सं;
	स्थिर अक्षर *errstr;

	अगर (!ext4_has_feature_journal(sb)) अणु
		ext4_error(sb, "Journal got removed while the fs was mounted!");
		वापस -EFSCORRUPTED;
	पूर्ण

	journal = EXT4_SB(sb)->s_journal;

	/*
	 * Now check क्रम any error status which may have been recorded in the
	 * journal by a prior ext4_error() or ext4_पात()
	 */

	j_त्रुटि_सं = jbd2_journal_त्रुटि_सं(journal);
	अगर (j_त्रुटि_सं) अणु
		अक्षर nbuf[16];

		errstr = ext4_decode_error(sb, j_त्रुटि_सं, nbuf);
		ext4_warning(sb, "Filesystem error recorded "
			     "from previous mount: %s", errstr);
		ext4_warning(sb, "Marking fs in need of filesystem check.");

		EXT4_SB(sb)->s_mount_state |= EXT4_ERROR_FS;
		es->s_state |= cpu_to_le16(EXT4_ERROR_FS);
		ext4_commit_super(sb);

		jbd2_journal_clear_err(journal);
		jbd2_journal_update_sb_त्रुटि_सं(journal);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Force the running and committing transactions to commit,
 * and रुको on the commit.
 */
पूर्णांक ext4_क्रमce_commit(काष्ठा super_block *sb)
अणु
	journal_t *journal;

	अगर (sb_rकरोnly(sb))
		वापस 0;

	journal = EXT4_SB(sb)->s_journal;
	वापस ext4_journal_क्रमce_commit(journal);
पूर्ण

अटल पूर्णांक ext4_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	पूर्णांक ret = 0;
	tid_t target;
	bool needs_barrier = false;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (unlikely(ext4_क्रमced_shutकरोwn(sbi)))
		वापस 0;

	trace_ext4_sync_fs(sb, रुको);
	flush_workqueue(sbi->rsv_conversion_wq);
	/*
	 * Writeback quota in non-journalled quota हाल - journalled quota has
	 * no dirty dquots
	 */
	dquot_ग_लिखोback_dquots(sb, -1);
	/*
	 * Data ग_लिखोback is possible w/o journal transaction, so barrier must
	 * being sent at the end of the function. But we can skip it अगर
	 * transaction_commit will करो it क्रम us.
	 */
	अगर (sbi->s_journal) अणु
		target = jbd2_get_latest_transaction(sbi->s_journal);
		अगर (रुको && sbi->s_journal->j_flags & JBD2_BARRIER &&
		    !jbd2_trans_will_send_data_barrier(sbi->s_journal, target))
			needs_barrier = true;

		अगर (jbd2_journal_start_commit(sbi->s_journal, &target)) अणु
			अगर (रुको)
				ret = jbd2_log_रुको_commit(sbi->s_journal,
							   target);
		पूर्ण
	पूर्ण अन्यथा अगर (रुको && test_opt(sb, BARRIER))
		needs_barrier = true;
	अगर (needs_barrier) अणु
		पूर्णांक err;
		err = blkdev_issue_flush(sb->s_bdev);
		अगर (!ret)
			ret = err;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * LVM calls this function beक्रमe a (पढ़ो-only) snapshot is created.  This
 * gives us a chance to flush the journal completely and mark the fs clean.
 *
 * Note that only this function cannot bring a fileप्रणाली to be in a clean
 * state independently. It relies on upper layer to stop all data & metadata
 * modअगरications.
 */
अटल पूर्णांक ext4_मुक्तze(काष्ठा super_block *sb)
अणु
	पूर्णांक error = 0;
	journal_t *journal;

	अगर (sb_rकरोnly(sb))
		वापस 0;

	journal = EXT4_SB(sb)->s_journal;

	अगर (journal) अणु
		/* Now we set up the journal barrier. */
		jbd2_journal_lock_updates(journal);

		/*
		 * Don't clear the needs_recovery flag अगर we failed to
		 * flush the journal.
		 */
		error = jbd2_journal_flush(journal);
		अगर (error < 0)
			जाओ out;

		/* Journal blocked and flushed, clear needs_recovery flag. */
		ext4_clear_feature_journal_needs_recovery(sb);
	पूर्ण

	error = ext4_commit_super(sb);
out:
	अगर (journal)
		/* we rely on upper layer to stop further updates */
		jbd2_journal_unlock_updates(journal);
	वापस error;
पूर्ण

/*
 * Called by LVM after the snapshot is करोne.  We need to reset the RECOVER
 * flag here, even though the fileप्रणाली is not technically dirty yet.
 */
अटल पूर्णांक ext4_unमुक्तze(काष्ठा super_block *sb)
अणु
	अगर (sb_rकरोnly(sb) || ext4_क्रमced_shutकरोwn(EXT4_SB(sb)))
		वापस 0;

	अगर (EXT4_SB(sb)->s_journal) अणु
		/* Reset the needs_recovery flag beक्रमe the fs is unlocked. */
		ext4_set_feature_journal_needs_recovery(sb);
	पूर्ण

	ext4_commit_super(sb);
	वापस 0;
पूर्ण

/*
 * Structure to save mount options क्रम ext4_remount's benefit
 */
काष्ठा ext4_mount_options अणु
	अचिन्हित दीर्घ s_mount_opt;
	अचिन्हित दीर्घ s_mount_opt2;
	kuid_t s_resuid;
	kgid_t s_resgid;
	अचिन्हित दीर्घ s_commit_पूर्णांकerval;
	u32 s_min_batch_समय, s_max_batch_समय;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक s_jquota_fmt;
	अक्षर *s_qf_names[EXT4_MAXQUOTAS];
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ext4_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा ext4_super_block *es;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अचिन्हित दीर्घ old_sb_flags, vfs_flags;
	काष्ठा ext4_mount_options old_opts;
	पूर्णांक enable_quota = 0;
	ext4_group_t g;
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक i, j;
	अक्षर *to_मुक्त[EXT4_MAXQUOTAS];
#पूर्ण_अगर
	अक्षर *orig_data = kstrdup(data, GFP_KERNEL);
	काष्ठा ext4_parsed_options parsed_opts;

	parsed_opts.journal_ioprio = DEFAULT_JOURNAL_IOPRIO;
	parsed_opts.journal_devnum = 0;

	अगर (data && !orig_data)
		वापस -ENOMEM;

	/* Store the original options */
	old_sb_flags = sb->s_flags;
	old_opts.s_mount_opt = sbi->s_mount_opt;
	old_opts.s_mount_opt2 = sbi->s_mount_opt2;
	old_opts.s_resuid = sbi->s_resuid;
	old_opts.s_resgid = sbi->s_resgid;
	old_opts.s_commit_पूर्णांकerval = sbi->s_commit_पूर्णांकerval;
	old_opts.s_min_batch_समय = sbi->s_min_batch_समय;
	old_opts.s_max_batch_समय = sbi->s_max_batch_समय;
#अगर_घोषित CONFIG_QUOTA
	old_opts.s_jquota_fmt = sbi->s_jquota_fmt;
	क्रम (i = 0; i < EXT4_MAXQUOTAS; i++)
		अगर (sbi->s_qf_names[i]) अणु
			अक्षर *qf_name = get_qf_name(sb, sbi, i);

			old_opts.s_qf_names[i] = kstrdup(qf_name, GFP_KERNEL);
			अगर (!old_opts.s_qf_names[i]) अणु
				क्रम (j = 0; j < i; j++)
					kमुक्त(old_opts.s_qf_names[j]);
				kमुक्त(orig_data);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा
			old_opts.s_qf_names[i] = शून्य;
#पूर्ण_अगर
	अगर (sbi->s_journal && sbi->s_journal->j_task->io_context)
		parsed_opts.journal_ioprio =
			sbi->s_journal->j_task->io_context->ioprio;

	/*
	 * Some options can be enabled by ext4 and/or by VFS mount flag
	 * either way we need to make sure it matches in both *flags and
	 * s_flags. Copy those selected flags from *flags to s_flags
	 */
	vfs_flags = SB_LAZYTIME | SB_I_VERSION;
	sb->s_flags = (sb->s_flags & ~vfs_flags) | (*flags & vfs_flags);

	अगर (!parse_options(data, sb, &parsed_opts, 1)) अणु
		err = -EINVAL;
		जाओ restore_opts;
	पूर्ण

	अगर ((old_opts.s_mount_opt & EXT4_MOUNT_JOURNAL_CHECKSUM) ^
	    test_opt(sb, JOURNAL_CHECKSUM)) अणु
		ext4_msg(sb, KERN_ERR, "changing journal_checksum "
			 "during remount not supported; ignoring");
		sbi->s_mount_opt ^= EXT4_MOUNT_JOURNAL_CHECKSUM;
	पूर्ण

	अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA) अणु
		अगर (test_opt2(sb, EXPLICIT_DELALLOC)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "both data=journal and delalloc");
			err = -EINVAL;
			जाओ restore_opts;
		पूर्ण
		अगर (test_opt(sb, DIOREAD_NOLOCK)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				 "both data=journal and dioread_nolock");
			err = -EINVAL;
			जाओ restore_opts;
		पूर्ण
	पूर्ण अन्यथा अगर (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_ORDERED_DATA) अणु
		अगर (test_opt(sb, JOURNAL_ASYNC_COMMIT)) अणु
			ext4_msg(sb, KERN_ERR, "can't mount with "
				"journal_async_commit in data=ordered mode");
			err = -EINVAL;
			जाओ restore_opts;
		पूर्ण
	पूर्ण

	अगर ((sbi->s_mount_opt ^ old_opts.s_mount_opt) & EXT4_MOUNT_NO_MBCACHE) अणु
		ext4_msg(sb, KERN_ERR, "can't enable nombcache during remount");
		err = -EINVAL;
		जाओ restore_opts;
	पूर्ण

	अगर (ext4_test_mount_flag(sb, EXT4_MF_FS_ABORTED))
		ext4_पात(sb, EXT4_ERR_ESHUTDOWN, "Abort forced by user");

	sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
		(test_opt(sb, POSIX_ACL) ? SB_POSIXACL : 0);

	es = sbi->s_es;

	अगर (sbi->s_journal) अणु
		ext4_init_journal_params(sb, sbi->s_journal);
		set_task_ioprio(sbi->s_journal->j_task, parsed_opts.journal_ioprio);
	पूर्ण

	/* Flush outstanding errors beक्रमe changing fs state */
	flush_work(&sbi->s_error_work);

	अगर ((bool)(*flags & SB_RDONLY) != sb_rकरोnly(sb)) अणु
		अगर (ext4_test_mount_flag(sb, EXT4_MF_FS_ABORTED)) अणु
			err = -EROFS;
			जाओ restore_opts;
		पूर्ण

		अगर (*flags & SB_RDONLY) अणु
			err = sync_fileप्रणाली(sb);
			अगर (err < 0)
				जाओ restore_opts;
			err = dquot_suspend(sb, -1);
			अगर (err < 0)
				जाओ restore_opts;

			/*
			 * First of all, the unconditional stuff we have to करो
			 * to disable replay of the journal when we next remount
			 */
			sb->s_flags |= SB_RDONLY;

			/*
			 * OK, test अगर we are remounting a valid rw partition
			 * पढ़ोonly, and अगर so set the rकरोnly flag and then
			 * mark the partition as valid again.
			 */
			अगर (!(es->s_state & cpu_to_le16(EXT4_VALID_FS)) &&
			    (sbi->s_mount_state & EXT4_VALID_FS))
				es->s_state = cpu_to_le16(sbi->s_mount_state);

			अगर (sbi->s_journal) अणु
				/*
				 * We let remount-ro finish even अगर marking fs
				 * as clean failed...
				 */
				ext4_mark_recovery_complete(sb, es);
			पूर्ण
			अगर (sbi->s_mmp_tsk)
				kthपढ़ो_stop(sbi->s_mmp_tsk);
		पूर्ण अन्यथा अणु
			/* Make sure we can mount this feature set पढ़ोग_लिखो */
			अगर (ext4_has_feature_पढ़ोonly(sb) ||
			    !ext4_feature_set_ok(sb, 0)) अणु
				err = -EROFS;
				जाओ restore_opts;
			पूर्ण
			/*
			 * Make sure the group descriptor checksums
			 * are sane.  If they aren't, refuse to remount r/w.
			 */
			क्रम (g = 0; g < sbi->s_groups_count; g++) अणु
				काष्ठा ext4_group_desc *gdp =
					ext4_get_group_desc(sb, g, शून्य);

				अगर (!ext4_group_desc_csum_verअगरy(sb, g, gdp)) अणु
					ext4_msg(sb, KERN_ERR,
	       "ext4_remount: Checksum for group %u failed (%u!=%u)",
		g, le16_to_cpu(ext4_group_desc_csum(sb, g, gdp)),
					       le16_to_cpu(gdp->bg_checksum));
					err = -EFSBADCRC;
					जाओ restore_opts;
				पूर्ण
			पूर्ण

			/*
			 * If we have an unprocessed orphan list hanging
			 * around from a previously पढ़ोonly bdev mount,
			 * require a full umount/remount क्रम now.
			 */
			अगर (es->s_last_orphan) अणु
				ext4_msg(sb, KERN_WARNING, "Couldn't "
				       "remount RDWR because of unprocessed "
				       "orphan inode list.  Please "
				       "umount/remount instead");
				err = -EINVAL;
				जाओ restore_opts;
			पूर्ण

			/*
			 * Mounting a RDONLY partition पढ़ो-ग_लिखो, so reपढ़ो
			 * and store the current valid flag.  (It may have
			 * been changed by e2fsck since we originally mounted
			 * the partition.)
			 */
			अगर (sbi->s_journal) अणु
				err = ext4_clear_journal_err(sb, es);
				अगर (err)
					जाओ restore_opts;
			पूर्ण
			sbi->s_mount_state = le16_to_cpu(es->s_state);

			err = ext4_setup_super(sb, es, 0);
			अगर (err)
				जाओ restore_opts;

			sb->s_flags &= ~SB_RDONLY;
			अगर (ext4_has_feature_mmp(sb))
				अगर (ext4_multi_mount_protect(sb,
						le64_to_cpu(es->s_mmp_block))) अणु
					err = -EROFS;
					जाओ restore_opts;
				पूर्ण
			enable_quota = 1;
		पूर्ण
	पूर्ण

	/*
	 * Reinitialize lazy itable initialization thपढ़ो based on
	 * current settings
	 */
	अगर (sb_rकरोnly(sb) || !test_opt(sb, INIT_INODE_TABLE))
		ext4_unरेजिस्टर_li_request(sb);
	अन्यथा अणु
		ext4_group_t first_not_zeroed;
		first_not_zeroed = ext4_has_uninit_itable(sb);
		ext4_रेजिस्टर_li_request(sb, first_not_zeroed);
	पूर्ण

	/*
	 * Handle creation of प्रणाली zone data early because it can fail.
	 * Releasing of existing data is करोne when we are sure remount will
	 * succeed.
	 */
	अगर (test_opt(sb, BLOCK_VALIDITY) && !sbi->s_प्रणाली_blks) अणु
		err = ext4_setup_प्रणाली_zone(sb);
		अगर (err)
			जाओ restore_opts;
	पूर्ण

	अगर (sbi->s_journal == शून्य && !(old_sb_flags & SB_RDONLY)) अणु
		err = ext4_commit_super(sb);
		अगर (err)
			जाओ restore_opts;
	पूर्ण

#अगर_घोषित CONFIG_QUOTA
	/* Release old quota file names */
	क्रम (i = 0; i < EXT4_MAXQUOTAS; i++)
		kमुक्त(old_opts.s_qf_names[i]);
	अगर (enable_quota) अणु
		अगर (sb_any_quota_suspended(sb))
			dquot_resume(sb, -1);
		अन्यथा अगर (ext4_has_feature_quota(sb)) अणु
			err = ext4_enable_quotas(sb);
			अगर (err)
				जाओ restore_opts;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (!test_opt(sb, BLOCK_VALIDITY) && sbi->s_प्रणाली_blks)
		ext4_release_प्रणाली_zone(sb);

	/*
	 * Some options can be enabled by ext4 and/or by VFS mount flag
	 * either way we need to make sure it matches in both *flags and
	 * s_flags. Copy those selected flags from s_flags to *flags
	 */
	*flags = (*flags & ~vfs_flags) | (sb->s_flags & vfs_flags);

	ext4_msg(sb, KERN_INFO, "re-mounted. Opts: %s. Quota mode: %s.",
		 orig_data, ext4_quota_mode(sb));
	kमुक्त(orig_data);
	वापस 0;

restore_opts:
	sb->s_flags = old_sb_flags;
	sbi->s_mount_opt = old_opts.s_mount_opt;
	sbi->s_mount_opt2 = old_opts.s_mount_opt2;
	sbi->s_resuid = old_opts.s_resuid;
	sbi->s_resgid = old_opts.s_resgid;
	sbi->s_commit_पूर्णांकerval = old_opts.s_commit_पूर्णांकerval;
	sbi->s_min_batch_समय = old_opts.s_min_batch_समय;
	sbi->s_max_batch_समय = old_opts.s_max_batch_समय;
	अगर (!test_opt(sb, BLOCK_VALIDITY) && sbi->s_प्रणाली_blks)
		ext4_release_प्रणाली_zone(sb);
#अगर_घोषित CONFIG_QUOTA
	sbi->s_jquota_fmt = old_opts.s_jquota_fmt;
	क्रम (i = 0; i < EXT4_MAXQUOTAS; i++) अणु
		to_मुक्त[i] = get_qf_name(sb, sbi, i);
		rcu_assign_poपूर्णांकer(sbi->s_qf_names[i], old_opts.s_qf_names[i]);
	पूर्ण
	synchronize_rcu();
	क्रम (i = 0; i < EXT4_MAXQUOTAS; i++)
		kमुक्त(to_मुक्त[i]);
#पूर्ण_अगर
	kमुक्त(orig_data);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक ext4_statfs_project(काष्ठा super_block *sb,
			       kprojid_t projid, काष्ठा kstatfs *buf)
अणु
	काष्ठा kqid qid;
	काष्ठा dquot *dquot;
	u64 limit;
	u64 curblock;

	qid = make_kqid_projid(projid);
	dquot = dqget(sb, qid);
	अगर (IS_ERR(dquot))
		वापस PTR_ERR(dquot);
	spin_lock(&dquot->dq_dqb_lock);

	limit = min_not_zero(dquot->dq_dqb.dqb_bsoftlimit,
			     dquot->dq_dqb.dqb_bhardlimit);
	limit >>= sb->s_blocksize_bits;

	अगर (limit && buf->f_blocks > limit) अणु
		curblock = (dquot->dq_dqb.dqb_curspace +
			    dquot->dq_dqb.dqb_rsvspace) >> sb->s_blocksize_bits;
		buf->f_blocks = limit;
		buf->f_bमुक्त = buf->f_bavail =
			(buf->f_blocks > curblock) ?
			 (buf->f_blocks - curblock) : 0;
	पूर्ण

	limit = min_not_zero(dquot->dq_dqb.dqb_isoftlimit,
			     dquot->dq_dqb.dqb_ihardlimit);
	अगर (limit && buf->f_files > limit) अणु
		buf->f_files = limit;
		buf->f_fमुक्त =
			(buf->f_files > dquot->dq_dqb.dqb_curinodes) ?
			 (buf->f_files - dquot->dq_dqb.dqb_curinodes) : 0;
	पूर्ण

	spin_unlock(&dquot->dq_dqb_lock);
	dqput(dquot);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ext4_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	ext4_fsblk_t overhead = 0, resv_blocks;
	s64 bमुक्त;
	resv_blocks = EXT4_C2B(sbi, atomic64_पढ़ो(&sbi->s_resv_clusters));

	अगर (!test_opt(sb, MINIX_DF))
		overhead = sbi->s_overhead;

	buf->f_type = EXT4_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = ext4_blocks_count(es) - EXT4_C2B(sbi, overhead);
	bमुक्त = percpu_counter_sum_positive(&sbi->s_मुक्तclusters_counter) -
		percpu_counter_sum_positive(&sbi->s_dirtyclusters_counter);
	/* prevent underflow in हाल that few मुक्त space is available */
	buf->f_bमुक्त = EXT4_C2B(sbi, max_t(s64, bमुक्त, 0));
	buf->f_bavail = buf->f_bमुक्त -
			(ext4_r_blocks_count(es) + resv_blocks);
	अगर (buf->f_bमुक्त < (ext4_r_blocks_count(es) + resv_blocks))
		buf->f_bavail = 0;
	buf->f_files = le32_to_cpu(es->s_inodes_count);
	buf->f_fमुक्त = percpu_counter_sum_positive(&sbi->s_मुक्तinodes_counter);
	buf->f_namelen = EXT4_NAME_LEN;
	buf->f_fsid = uuid_to_fsid(es->s_uuid);

#अगर_घोषित CONFIG_QUOTA
	अगर (ext4_test_inode_flag(dentry->d_inode, EXT4_INODE_PROJINHERIT) &&
	    sb_has_quota_limits_enabled(sb, PRJQUOTA))
		ext4_statfs_project(sb, EXT4_I(dentry->d_inode)->i_projid, buf);
#पूर्ण_अगर
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_QUOTA

/*
 * Helper functions so that transaction is started beक्रमe we acquire dqio_sem
 * to keep correct lock ordering of transaction > dqio_sem
 */
अटल अंतरभूत काष्ठा inode *dquot_to_inode(काष्ठा dquot *dquot)
अणु
	वापस sb_dqopt(dquot->dq_sb)->files[dquot->dq_id.type];
पूर्ण

अटल पूर्णांक ext4_ग_लिखो_dquot(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret, err;
	handle_t *handle;
	काष्ठा inode *inode;

	inode = dquot_to_inode(dquot);
	handle = ext4_journal_start(inode, EXT4_HT_QUOTA,
				    EXT4_QUOTA_TRANS_BLOCKS(dquot->dq_sb));
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	ret = dquot_commit(dquot);
	err = ext4_journal_stop(handle);
	अगर (!ret)
		ret = err;
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_acquire_dquot(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret, err;
	handle_t *handle;

	handle = ext4_journal_start(dquot_to_inode(dquot), EXT4_HT_QUOTA,
				    EXT4_QUOTA_INIT_BLOCKS(dquot->dq_sb));
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	ret = dquot_acquire(dquot);
	err = ext4_journal_stop(handle);
	अगर (!ret)
		ret = err;
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_release_dquot(काष्ठा dquot *dquot)
अणु
	पूर्णांक ret, err;
	handle_t *handle;

	handle = ext4_journal_start(dquot_to_inode(dquot), EXT4_HT_QUOTA,
				    EXT4_QUOTA_DEL_BLOCKS(dquot->dq_sb));
	अगर (IS_ERR(handle)) अणु
		/* Release dquot anyway to aव्योम endless cycle in dqput() */
		dquot_release(dquot);
		वापस PTR_ERR(handle);
	पूर्ण
	ret = dquot_release(dquot);
	err = ext4_journal_stop(handle);
	अगर (!ret)
		ret = err;
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_mark_dquot_dirty(काष्ठा dquot *dquot)
अणु
	काष्ठा super_block *sb = dquot->dq_sb;

	अगर (ext4_is_quota_journalled(sb)) अणु
		dquot_mark_dquot_dirty(dquot);
		वापस ext4_ग_लिखो_dquot(dquot);
	पूर्ण अन्यथा अणु
		वापस dquot_mark_dquot_dirty(dquot);
	पूर्ण
पूर्ण

अटल पूर्णांक ext4_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	पूर्णांक ret, err;
	handle_t *handle;

	/* Data block + inode block */
	handle = ext4_journal_start(d_inode(sb->s_root), EXT4_HT_QUOTA, 2);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	ret = dquot_commit_info(sb, type);
	err = ext4_journal_stop(handle);
	अगर (!ret)
		ret = err;
	वापस ret;
पूर्ण

/*
 * Turn on quotas during mount समय - we need to find
 * the quota file and such...
 */
अटल पूर्णांक ext4_quota_on_mount(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस dquot_quota_on_mount(sb, get_qf_name(sb, EXT4_SB(sb), type),
					EXT4_SB(sb)->s_jquota_fmt, type);
पूर्ण

अटल व्योम lockdep_set_quota_inode(काष्ठा inode *inode, पूर्णांक subclass)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	/* The first argument of lockdep_set_subclass has to be
	 * *exactly* the same as the argument to init_rwsem() --- in
	 * this हाल, in init_once() --- or lockdep माला_लो unhappy
	 * because the name of the lock is set using the
	 * stringअगरication of the argument to init_rwsem().
	 */
	(व्योम) ei;	/* shut up clang warning अगर !CONFIG_LOCKDEP */
	lockdep_set_subclass(&ei->i_data_sem, subclass);
पूर्ण

/*
 * Standard function to be called on quota_on
 */
अटल पूर्णांक ext4_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			 स्थिर काष्ठा path *path)
अणु
	पूर्णांक err;

	अगर (!test_opt(sb, QUOTA))
		वापस -EINVAL;

	/* Quotafile not on the same fileप्रणाली? */
	अगर (path->dentry->d_sb != sb)
		वापस -EXDEV;

	/* Quota alपढ़ोy enabled क्रम this file? */
	अगर (IS_NOQUOTA(d_inode(path->dentry)))
		वापस -EBUSY;

	/* Journaling quota? */
	अगर (EXT4_SB(sb)->s_qf_names[type]) अणु
		/* Quotafile not in fs root? */
		अगर (path->dentry->d_parent != sb->s_root)
			ext4_msg(sb, KERN_WARNING,
				"Quota file not on filesystem root. "
				"Journaled quota will not work");
		sb_dqopt(sb)->flags |= DQUOT_NOLIST_सूचीTY;
	पूर्ण अन्यथा अणु
		/*
		 * Clear the flag just in हाल mount options changed since
		 * last समय.
		 */
		sb_dqopt(sb)->flags &= ~DQUOT_NOLIST_सूचीTY;
	पूर्ण

	/*
	 * When we journal data on quota file, we have to flush journal to see
	 * all updates to the file when we bypass pagecache...
	 */
	अगर (EXT4_SB(sb)->s_journal &&
	    ext4_should_journal_data(d_inode(path->dentry))) अणु
		/*
		 * We करोn't need to lock updates but journal_flush() could
		 * otherwise be livelocked...
		 */
		jbd2_journal_lock_updates(EXT4_SB(sb)->s_journal);
		err = jbd2_journal_flush(EXT4_SB(sb)->s_journal);
		jbd2_journal_unlock_updates(EXT4_SB(sb)->s_journal);
		अगर (err)
			वापस err;
	पूर्ण

	lockdep_set_quota_inode(path->dentry->d_inode, I_DATA_SEM_QUOTA);
	err = dquot_quota_on(sb, type, क्रमmat_id, path);
	अगर (err) अणु
		lockdep_set_quota_inode(path->dentry->d_inode,
					     I_DATA_SEM_NORMAL);
	पूर्ण अन्यथा अणु
		काष्ठा inode *inode = d_inode(path->dentry);
		handle_t *handle;

		/*
		 * Set inode flags to prevent userspace from messing with quota
		 * files. If this fails, we वापस success anyway since quotas
		 * are alपढ़ोy enabled and this is not a hard failure.
		 */
		inode_lock(inode);
		handle = ext4_journal_start(inode, EXT4_HT_QUOTA, 1);
		अगर (IS_ERR(handle))
			जाओ unlock_inode;
		EXT4_I(inode)->i_flags |= EXT4_NOATIME_FL | EXT4_IMMUTABLE_FL;
		inode_set_flags(inode, S_NOATIME | S_IMMUTABLE,
				S_NOATIME | S_IMMUTABLE);
		err = ext4_mark_inode_dirty(handle, inode);
		ext4_journal_stop(handle);
	unlock_inode:
		inode_unlock(inode);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ext4_quota_enable(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			     अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा inode *qf_inode;
	अचिन्हित दीर्घ qf_inums[EXT4_MAXQUOTAS] = अणु
		le32_to_cpu(EXT4_SB(sb)->s_es->s_usr_quota_inum),
		le32_to_cpu(EXT4_SB(sb)->s_es->s_grp_quota_inum),
		le32_to_cpu(EXT4_SB(sb)->s_es->s_prj_quota_inum)
	पूर्ण;

	BUG_ON(!ext4_has_feature_quota(sb));

	अगर (!qf_inums[type])
		वापस -EPERM;

	qf_inode = ext4_iget(sb, qf_inums[type], EXT4_IGET_SPECIAL);
	अगर (IS_ERR(qf_inode)) अणु
		ext4_error(sb, "Bad quota inode # %lu", qf_inums[type]);
		वापस PTR_ERR(qf_inode);
	पूर्ण

	/* Don't account quota क्रम quota files to aव्योम recursion */
	qf_inode->i_flags |= S_NOQUOTA;
	lockdep_set_quota_inode(qf_inode, I_DATA_SEM_QUOTA);
	err = dquot_load_quota_inode(qf_inode, type, क्रमmat_id, flags);
	अगर (err)
		lockdep_set_quota_inode(qf_inode, I_DATA_SEM_NORMAL);
	iput(qf_inode);

	वापस err;
पूर्ण

/* Enable usage tracking क्रम all quota types. */
अटल पूर्णांक ext4_enable_quotas(काष्ठा super_block *sb)
अणु
	पूर्णांक type, err = 0;
	अचिन्हित दीर्घ qf_inums[EXT4_MAXQUOTAS] = अणु
		le32_to_cpu(EXT4_SB(sb)->s_es->s_usr_quota_inum),
		le32_to_cpu(EXT4_SB(sb)->s_es->s_grp_quota_inum),
		le32_to_cpu(EXT4_SB(sb)->s_es->s_prj_quota_inum)
	पूर्ण;
	bool quota_mopt[EXT4_MAXQUOTAS] = अणु
		test_opt(sb, USRQUOTA),
		test_opt(sb, GRPQUOTA),
		test_opt(sb, PRJQUOTA),
	पूर्ण;

	sb_dqopt(sb)->flags |= DQUOT_QUOTA_SYS_खाता | DQUOT_NOLIST_सूचीTY;
	क्रम (type = 0; type < EXT4_MAXQUOTAS; type++) अणु
		अगर (qf_inums[type]) अणु
			err = ext4_quota_enable(sb, type, QFMT_VFS_V1,
				DQUOT_USAGE_ENABLED |
				(quota_mopt[type] ? DQUOT_LIMITS_ENABLED : 0));
			अगर (err) अणु
				ext4_warning(sb,
					"Failed to enable quota tracking "
					"(type=%d, err=%d). Please run "
					"e2fsck to fix.", type, err);
				क्रम (type--; type >= 0; type--)
					dquot_quota_off(sb, type);

				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_quota_off(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	handle_t *handle;
	पूर्णांक err;

	/* Force all delayed allocation blocks to be allocated.
	 * Caller alपढ़ोy holds s_umount sem */
	अगर (test_opt(sb, DELALLOC))
		sync_fileप्रणाली(sb);

	अगर (!inode || !igrab(inode))
		जाओ out;

	err = dquot_quota_off(sb, type);
	अगर (err || ext4_has_feature_quota(sb))
		जाओ out_put;

	inode_lock(inode);
	/*
	 * Update modअगरication बार of quota files when userspace can
	 * start looking at them. If we fail, we वापस success anyway since
	 * this is not a hard failure and quotas are alपढ़ोy disabled.
	 */
	handle = ext4_journal_start(inode, EXT4_HT_QUOTA, 1);
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		जाओ out_unlock;
	पूर्ण
	EXT4_I(inode)->i_flags &= ~(EXT4_NOATIME_FL | EXT4_IMMUTABLE_FL);
	inode_set_flags(inode, 0, S_NOATIME | S_IMMUTABLE);
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	err = ext4_mark_inode_dirty(handle, inode);
	ext4_journal_stop(handle);
out_unlock:
	inode_unlock(inode);
out_put:
	lockdep_set_quota_inode(inode, I_DATA_SEM_NORMAL);
	iput(inode);
	वापस err;
out:
	वापस dquot_quota_off(sb, type);
पूर्ण

/* Read data from quotafile - aव्योम pagecache and such because we cannot afक्रमd
 * acquiring the locks... As quota files are never truncated and quota code
 * itself serializes the operations (and no one अन्यथा should touch the files)
 * we करोn't have to be afraid of races */
अटल sमाप_प्रकार ext4_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
			       माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	ext4_lblk_t blk = off >> EXT4_BLOCK_SIZE_BITS(sb);
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	पूर्णांक tocopy;
	माप_प्रकार toपढ़ो;
	काष्ठा buffer_head *bh;
	loff_t i_size = i_size_पढ़ो(inode);

	अगर (off > i_size)
		वापस 0;
	अगर (off+len > i_size)
		len = i_size-off;
	toपढ़ो = len;
	जबतक (toपढ़ो > 0) अणु
		tocopy = sb->s_blocksize - offset < toपढ़ो ?
				sb->s_blocksize - offset : toपढ़ो;
		bh = ext4_bपढ़ो(शून्य, inode, blk, 0);
		अगर (IS_ERR(bh))
			वापस PTR_ERR(bh);
		अगर (!bh)	/* A hole? */
			स_रखो(data, 0, tocopy);
		अन्यथा
			स_नकल(data, bh->b_data+offset, tocopy);
		brअन्यथा(bh);
		offset = 0;
		toपढ़ो -= tocopy;
		data += tocopy;
		blk++;
	पूर्ण
	वापस len;
पूर्ण

/* Write to quotafile (we know the transaction is alपढ़ोy started and has
 * enough credits) */
अटल sमाप_प्रकार ext4_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
				स्थिर अक्षर *data, माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	ext4_lblk_t blk = off >> EXT4_BLOCK_SIZE_BITS(sb);
	पूर्णांक err = 0, err2 = 0, offset = off & (sb->s_blocksize - 1);
	पूर्णांक retries = 0;
	काष्ठा buffer_head *bh;
	handle_t *handle = journal_current_handle();

	अगर (EXT4_SB(sb)->s_journal && !handle) अणु
		ext4_msg(sb, KERN_WARNING, "Quota write (off=%llu, len=%llu)"
			" cancelled because transaction is not started",
			(अचिन्हित दीर्घ दीर्घ)off, (अचिन्हित दीर्घ दीर्घ)len);
		वापस -EIO;
	पूर्ण
	/*
	 * Since we account only one data block in transaction credits,
	 * then it is impossible to cross a block boundary.
	 */
	अगर (sb->s_blocksize - offset < len) अणु
		ext4_msg(sb, KERN_WARNING, "Quota write (off=%llu, len=%llu)"
			" cancelled because not block aligned",
			(अचिन्हित दीर्घ दीर्घ)off, (अचिन्हित दीर्घ दीर्घ)len);
		वापस -EIO;
	पूर्ण

	करो अणु
		bh = ext4_bपढ़ो(handle, inode, blk,
				EXT4_GET_BLOCKS_CREATE |
				EXT4_GET_BLOCKS_METADATA_NOFAIL);
	पूर्ण जबतक (PTR_ERR(bh) == -ENOSPC &&
		 ext4_should_retry_alloc(inode->i_sb, &retries));
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);
	अगर (!bh)
		जाओ out;
	BUFFER_TRACE(bh, "get write access");
	err = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (err) अणु
		brअन्यथा(bh);
		वापस err;
	पूर्ण
	lock_buffer(bh);
	स_नकल(bh->b_data+offset, data, len);
	flush_dcache_page(bh->b_page);
	unlock_buffer(bh);
	err = ext4_handle_dirty_metadata(handle, शून्य, bh);
	brअन्यथा(bh);
out:
	अगर (inode->i_size < off + len) अणु
		i_size_ग_लिखो(inode, off + len);
		EXT4_I(inode)->i_disksize = inode->i_size;
		err2 = ext4_mark_inode_dirty(handle, inode);
		अगर (unlikely(err2 && !err))
			err = err2;
	पूर्ण
	वापस err ? err : len;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा dentry *ext4_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
		       स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, ext4_fill_super);
पूर्ण

#अगर !defined(CONFIG_EXT2_FS) && !defined(CONFIG_EXT2_FS_MODULE) && defined(CONFIG_EXT4_USE_FOR_EXT2)
अटल अंतरभूत व्योम रेजिस्टर_as_ext2(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_fileप्रणाली(&ext2_fs_type);
	अगर (err)
		prपूर्णांकk(KERN_WARNING
		       "EXT4-fs: Unable to register as ext2 (%d)\n", err);
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_as_ext2(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&ext2_fs_type);
पूर्ण

अटल अंतरभूत पूर्णांक ext2_feature_set_ok(काष्ठा super_block *sb)
अणु
	अगर (ext4_has_unknown_ext2_incompat_features(sb))
		वापस 0;
	अगर (sb_rकरोnly(sb))
		वापस 1;
	अगर (ext4_has_unknown_ext2_ro_compat_features(sb))
		वापस 0;
	वापस 1;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम रेजिस्टर_as_ext2(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_as_ext2(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक ext2_feature_set_ok(काष्ठा super_block *sb) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम रेजिस्टर_as_ext3(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_fileप्रणाली(&ext3_fs_type);
	अगर (err)
		prपूर्णांकk(KERN_WARNING
		       "EXT4-fs: Unable to register as ext3 (%d)\n", err);
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_as_ext3(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&ext3_fs_type);
पूर्ण

अटल अंतरभूत पूर्णांक ext3_feature_set_ok(काष्ठा super_block *sb)
अणु
	अगर (ext4_has_unknown_ext3_incompat_features(sb))
		वापस 0;
	अगर (!ext4_has_feature_journal(sb))
		वापस 0;
	अगर (sb_rकरोnly(sb))
		वापस 1;
	अगर (ext4_has_unknown_ext3_ro_compat_features(sb))
		वापस 0;
	वापस 1;
पूर्ण

अटल काष्ठा file_प्रणाली_type ext4_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ext4",
	.mount		= ext4_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV | FS_ALLOW_IDMAP,
पूर्ण;
MODULE_ALIAS_FS("ext4");

/* Shared across all ext4 file प्रणालीs */
रुको_queue_head_t ext4__ioend_wq[EXT4_WQ_HASH_SZ];

अटल पूर्णांक __init ext4_init_fs(व्योम)
अणु
	पूर्णांक i, err;

	ratelimit_state_init(&ext4_mount_msg_ratelimit, 30 * HZ, 64);
	ext4_li_info = शून्य;

	/* Build-समय check क्रम flags consistency */
	ext4_check_flag_values();

	क्रम (i = 0; i < EXT4_WQ_HASH_SZ; i++)
		init_रुकोqueue_head(&ext4__ioend_wq[i]);

	err = ext4_init_es();
	अगर (err)
		वापस err;

	err = ext4_init_pending();
	अगर (err)
		जाओ out7;

	err = ext4_init_post_पढ़ो_processing();
	अगर (err)
		जाओ out6;

	err = ext4_init_pageio();
	अगर (err)
		जाओ out5;

	err = ext4_init_प्रणाली_zone();
	अगर (err)
		जाओ out4;

	err = ext4_init_sysfs();
	अगर (err)
		जाओ out3;

	err = ext4_init_mballoc();
	अगर (err)
		जाओ out2;
	err = init_inodecache();
	अगर (err)
		जाओ out1;

	err = ext4_fc_init_dentry_cache();
	अगर (err)
		जाओ out05;

	रेजिस्टर_as_ext3();
	रेजिस्टर_as_ext2();
	err = रेजिस्टर_fileप्रणाली(&ext4_fs_type);
	अगर (err)
		जाओ out;

	वापस 0;
out:
	unरेजिस्टर_as_ext2();
	unरेजिस्टर_as_ext3();
out05:
	destroy_inodecache();
out1:
	ext4_निकास_mballoc();
out2:
	ext4_निकास_sysfs();
out3:
	ext4_निकास_प्रणाली_zone();
out4:
	ext4_निकास_pageio();
out5:
	ext4_निकास_post_पढ़ो_processing();
out6:
	ext4_निकास_pending();
out7:
	ext4_निकास_es();

	वापस err;
पूर्ण

अटल व्योम __निकास ext4_निकास_fs(व्योम)
अणु
	ext4_destroy_lazyinit_thपढ़ो();
	unरेजिस्टर_as_ext2();
	unरेजिस्टर_as_ext3();
	unरेजिस्टर_fileप्रणाली(&ext4_fs_type);
	destroy_inodecache();
	ext4_निकास_mballoc();
	ext4_निकास_sysfs();
	ext4_निकास_प्रणाली_zone();
	ext4_निकास_pageio();
	ext4_निकास_post_पढ़ो_processing();
	ext4_निकास_es();
	ext4_निकास_pending();
पूर्ण

MODULE_AUTHOR("Remy Card, Stephen Tweedie, Andrew Morton, Andreas Dilger, Theodore Ts'o and others");
MODULE_DESCRIPTION("Fourth Extended Filesystem");
MODULE_LICENSE("GPL");
MODULE_SOFTDEP("pre: crc32c");
module_init(ext4_init_fs)
module_निकास(ext4_निकास_fs)
