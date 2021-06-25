<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Copyright (C) 1996  Gertjan van Wingerde
 *	Minix V2 fs support.
 *
 *  Modअगरied क्रम 680x0 by Andreas Schwab
 *  Updated to fileप्रणाली version 3 by Daniel Aragones
 */

#समावेश <linux/module.h>
#समावेश "minix.h"
#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/highuid.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ग_लिखोback.h>

अटल पूर्णांक minix_ग_लिखो_inode(काष्ठा inode *inode,
		काष्ठा ग_लिखोback_control *wbc);
अटल पूर्णांक minix_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);
अटल पूर्णांक minix_remount (काष्ठा super_block * sb, पूर्णांक * flags, अक्षर * data);

अटल व्योम minix_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	अगर (!inode->i_nlink) अणु
		inode->i_size = 0;
		minix_truncate(inode);
	पूर्ण
	invalidate_inode_buffers(inode);
	clear_inode(inode);
	अगर (!inode->i_nlink)
		minix_मुक्त_inode(inode);
पूर्ण

अटल व्योम minix_put_super(काष्ठा super_block *sb)
अणु
	पूर्णांक i;
	काष्ठा minix_sb_info *sbi = minix_sb(sb);

	अगर (!sb_rकरोnly(sb)) अणु
		अगर (sbi->s_version != MINIX_V3)	 /* s_state is now out from V3 sb */
			sbi->s_ms->s_state = sbi->s_mount_state;
		mark_buffer_dirty(sbi->s_sbh);
	पूर्ण
	क्रम (i = 0; i < sbi->s_imap_blocks; i++)
		brअन्यथा(sbi->s_imap[i]);
	क्रम (i = 0; i < sbi->s_zmap_blocks; i++)
		brअन्यथा(sbi->s_zmap[i]);
	brअन्यथा (sbi->s_sbh);
	kमुक्त(sbi->s_imap);
	sb->s_fs_info = शून्य;
	kमुक्त(sbi);
पूर्ण

अटल काष्ठा kmem_cache * minix_inode_cachep;

अटल काष्ठा inode *minix_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा minix_inode_info *ei;
	ei = kmem_cache_alloc(minix_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम minix_मुक्त_in_core_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(minix_inode_cachep, minix_i(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा minix_inode_info *ei = (काष्ठा minix_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	minix_inode_cachep = kmem_cache_create("minix_inode_cache",
					     माप(काष्ठा minix_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (minix_inode_cachep == शून्य)
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
	kmem_cache_destroy(minix_inode_cachep);
पूर्ण

अटल स्थिर काष्ठा super_operations minix_sops = अणु
	.alloc_inode	= minix_alloc_inode,
	.मुक्त_inode	= minix_मुक्त_in_core_inode,
	.ग_लिखो_inode	= minix_ग_लिखो_inode,
	.evict_inode	= minix_evict_inode,
	.put_super	= minix_put_super,
	.statfs		= minix_statfs,
	.remount_fs	= minix_remount,
पूर्ण;

अटल पूर्णांक minix_remount (काष्ठा super_block * sb, पूर्णांक * flags, अक्षर * data)
अणु
	काष्ठा minix_sb_info * sbi = minix_sb(sb);
	काष्ठा minix_super_block * ms;

	sync_fileप्रणाली(sb);
	ms = sbi->s_ms;
	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		वापस 0;
	अगर (*flags & SB_RDONLY) अणु
		अगर (ms->s_state & MINIX_VALID_FS ||
		    !(sbi->s_mount_state & MINIX_VALID_FS))
			वापस 0;
		/* Mounting a rw partition पढ़ो-only. */
		अगर (sbi->s_version != MINIX_V3)
			ms->s_state = sbi->s_mount_state;
		mark_buffer_dirty(sbi->s_sbh);
	पूर्ण अन्यथा अणु
	  	/* Mount a partition which is पढ़ो-only, पढ़ो-ग_लिखो. */
		अगर (sbi->s_version != MINIX_V3) अणु
			sbi->s_mount_state = ms->s_state;
			ms->s_state &= ~MINIX_VALID_FS;
		पूर्ण अन्यथा अणु
			sbi->s_mount_state = MINIX_VALID_FS;
		पूर्ण
		mark_buffer_dirty(sbi->s_sbh);

		अगर (!(sbi->s_mount_state & MINIX_VALID_FS))
			prपूर्णांकk("MINIX-fs warning: remounting unchecked fs, "
				"running fsck is recommended\n");
		अन्यथा अगर ((sbi->s_mount_state & MINIX_ERROR_FS))
			prपूर्णांकk("MINIX-fs warning: remounting fs with errors, "
				"running fsck is recommended\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल bool minix_check_superblock(काष्ठा super_block *sb)
अणु
	काष्ठा minix_sb_info *sbi = minix_sb(sb);

	अगर (sbi->s_imap_blocks == 0 || sbi->s_zmap_blocks == 0)
		वापस false;

	/*
	 * s_max_size must not exceed the block mapping limitation.  This check
	 * is only needed क्रम V1 fileप्रणालीs, since V2/V3 support an extra level
	 * of indirect blocks which places the limit well above U32_MAX.
	 */
	अगर (sbi->s_version == MINIX_V1 &&
	    sb->s_maxbytes > (7 + 512 + 512*512) * BLOCK_SIZE)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक minix_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head **map;
	काष्ठा minix_super_block *ms;
	काष्ठा minix3_super_block *m3s = शून्य;
	अचिन्हित दीर्घ i, block;
	काष्ठा inode *root_inode;
	काष्ठा minix_sb_info *sbi;
	पूर्णांक ret = -EINVAL;

	sbi = kzalloc(माप(काष्ठा minix_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;
	s->s_fs_info = sbi;

	BUILD_BUG_ON(32 != माप (काष्ठा minix_inode));
	BUILD_BUG_ON(64 != माप(काष्ठा minix2_inode));

	अगर (!sb_set_blocksize(s, BLOCK_SIZE))
		जाओ out_bad_hblock;

	अगर (!(bh = sb_bपढ़ो(s, 1)))
		जाओ out_bad_sb;

	ms = (काष्ठा minix_super_block *) bh->b_data;
	sbi->s_ms = ms;
	sbi->s_sbh = bh;
	sbi->s_mount_state = ms->s_state;
	sbi->s_ninodes = ms->s_ninodes;
	sbi->s_nzones = ms->s_nzones;
	sbi->s_imap_blocks = ms->s_imap_blocks;
	sbi->s_zmap_blocks = ms->s_zmap_blocks;
	sbi->s_firstdatazone = ms->s_firstdatazone;
	sbi->s_log_zone_size = ms->s_log_zone_size;
	s->s_maxbytes = ms->s_max_size;
	s->s_magic = ms->s_magic;
	अगर (s->s_magic == MINIX_SUPER_MAGIC) अणु
		sbi->s_version = MINIX_V1;
		sbi->s_dirsize = 16;
		sbi->s_namelen = 14;
		s->s_max_links = MINIX_LINK_MAX;
	पूर्ण अन्यथा अगर (s->s_magic == MINIX_SUPER_MAGIC2) अणु
		sbi->s_version = MINIX_V1;
		sbi->s_dirsize = 32;
		sbi->s_namelen = 30;
		s->s_max_links = MINIX_LINK_MAX;
	पूर्ण अन्यथा अगर (s->s_magic == MINIX2_SUPER_MAGIC) अणु
		sbi->s_version = MINIX_V2;
		sbi->s_nzones = ms->s_zones;
		sbi->s_dirsize = 16;
		sbi->s_namelen = 14;
		s->s_max_links = MINIX2_LINK_MAX;
	पूर्ण अन्यथा अगर (s->s_magic == MINIX2_SUPER_MAGIC2) अणु
		sbi->s_version = MINIX_V2;
		sbi->s_nzones = ms->s_zones;
		sbi->s_dirsize = 32;
		sbi->s_namelen = 30;
		s->s_max_links = MINIX2_LINK_MAX;
	पूर्ण अन्यथा अगर ( *(__u16 *)(bh->b_data + 24) == MINIX3_SUPER_MAGIC) अणु
		m3s = (काष्ठा minix3_super_block *) bh->b_data;
		s->s_magic = m3s->s_magic;
		sbi->s_imap_blocks = m3s->s_imap_blocks;
		sbi->s_zmap_blocks = m3s->s_zmap_blocks;
		sbi->s_firstdatazone = m3s->s_firstdatazone;
		sbi->s_log_zone_size = m3s->s_log_zone_size;
		s->s_maxbytes = m3s->s_max_size;
		sbi->s_ninodes = m3s->s_ninodes;
		sbi->s_nzones = m3s->s_zones;
		sbi->s_dirsize = 64;
		sbi->s_namelen = 60;
		sbi->s_version = MINIX_V3;
		sbi->s_mount_state = MINIX_VALID_FS;
		sb_set_blocksize(s, m3s->s_blocksize);
		s->s_max_links = MINIX2_LINK_MAX;
	पूर्ण अन्यथा
		जाओ out_no_fs;

	अगर (!minix_check_superblock(s))
		जाओ out_illegal_sb;

	/*
	 * Allocate the buffer map to keep the superblock small.
	 */
	i = (sbi->s_imap_blocks + sbi->s_zmap_blocks) * माप(bh);
	map = kzalloc(i, GFP_KERNEL);
	अगर (!map)
		जाओ out_no_map;
	sbi->s_imap = &map[0];
	sbi->s_zmap = &map[sbi->s_imap_blocks];

	block=2;
	क्रम (i=0 ; i < sbi->s_imap_blocks ; i++) अणु
		अगर (!(sbi->s_imap[i]=sb_bपढ़ो(s, block)))
			जाओ out_no_biपंचांगap;
		block++;
	पूर्ण
	क्रम (i=0 ; i < sbi->s_zmap_blocks ; i++) अणु
		अगर (!(sbi->s_zmap[i]=sb_bपढ़ो(s, block)))
			जाओ out_no_biपंचांगap;
		block++;
	पूर्ण

	minix_set_bit(0,sbi->s_imap[0]->b_data);
	minix_set_bit(0,sbi->s_zmap[0]->b_data);

	/* Apparently minix can create fileप्रणालीs that allocate more blocks क्रम
	 * the biपंचांगaps than needed.  We simply ignore that, but verअगरy it didn't
	 * create one with not enough blocks and bail out अगर so.
	 */
	block = minix_blocks_needed(sbi->s_ninodes, s->s_blocksize);
	अगर (sbi->s_imap_blocks < block) अणु
		prपूर्णांकk("MINIX-fs: file system does not have enough "
				"imap blocks allocated.  Refusing to mount.\n");
		जाओ out_no_biपंचांगap;
	पूर्ण

	block = minix_blocks_needed(
			(sbi->s_nzones - sbi->s_firstdatazone + 1),
			s->s_blocksize);
	अगर (sbi->s_zmap_blocks < block) अणु
		prपूर्णांकk("MINIX-fs: file system does not have enough "
				"zmap blocks allocated.  Refusing to mount.\n");
		जाओ out_no_biपंचांगap;
	पूर्ण

	/* set up enough so that it can पढ़ो an inode */
	s->s_op = &minix_sops;
	s->s_समय_min = 0;
	s->s_समय_max = U32_MAX;
	root_inode = minix_iget(s, MINIX_ROOT_INO);
	अगर (IS_ERR(root_inode)) अणु
		ret = PTR_ERR(root_inode);
		जाओ out_no_root;
	पूर्ण

	ret = -ENOMEM;
	s->s_root = d_make_root(root_inode);
	अगर (!s->s_root)
		जाओ out_no_root;

	अगर (!sb_rकरोnly(s)) अणु
		अगर (sbi->s_version != MINIX_V3) /* s_state is now out from V3 sb */
			ms->s_state &= ~MINIX_VALID_FS;
		mark_buffer_dirty(bh);
	पूर्ण
	अगर (!(sbi->s_mount_state & MINIX_VALID_FS))
		prपूर्णांकk("MINIX-fs: mounting unchecked file system, "
			"running fsck is recommended\n");
	अन्यथा अगर (sbi->s_mount_state & MINIX_ERROR_FS)
		prपूर्णांकk("MINIX-fs: mounting file system with errors, "
			"running fsck is recommended\n");

	वापस 0;

out_no_root:
	अगर (!silent)
		prपूर्णांकk("MINIX-fs: get root inode failed\n");
	जाओ out_मुक्तmap;

out_no_biपंचांगap:
	prपूर्णांकk("MINIX-fs: bad superblock or unable to read bitmaps\n");
out_मुक्तmap:
	क्रम (i = 0; i < sbi->s_imap_blocks; i++)
		brअन्यथा(sbi->s_imap[i]);
	क्रम (i = 0; i < sbi->s_zmap_blocks; i++)
		brअन्यथा(sbi->s_zmap[i]);
	kमुक्त(sbi->s_imap);
	जाओ out_release;

out_no_map:
	ret = -ENOMEM;
	अगर (!silent)
		prपूर्णांकk("MINIX-fs: can't allocate map\n");
	जाओ out_release;

out_illegal_sb:
	अगर (!silent)
		prपूर्णांकk("MINIX-fs: bad superblock\n");
	जाओ out_release;

out_no_fs:
	अगर (!silent)
		prपूर्णांकk("VFS: Can't find a Minix filesystem V1 | V2 | V3 "
		       "on device %s.\n", s->s_id);
out_release:
	brअन्यथा(bh);
	जाओ out;

out_bad_hblock:
	prपूर्णांकk("MINIX-fs: blocksize too small for device\n");
	जाओ out;

out_bad_sb:
	prपूर्णांकk("MINIX-fs: unable to read superblock\n");
out:
	s->s_fs_info = शून्य;
	kमुक्त(sbi);
	वापस ret;
पूर्ण

अटल पूर्णांक minix_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);
	buf->f_type = sb->s_magic;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = (sbi->s_nzones - sbi->s_firstdatazone) << sbi->s_log_zone_size;
	buf->f_bमुक्त = minix_count_मुक्त_blocks(sb);
	buf->f_bavail = buf->f_bमुक्त;
	buf->f_files = sbi->s_ninodes;
	buf->f_fमुक्त = minix_count_मुक्त_inodes(sb);
	buf->f_namelen = sbi->s_namelen;
	buf->f_fsid = u64_to_fsid(id);

	वापस 0;
पूर्ण

अटल पूर्णांक minix_get_block(काष्ठा inode *inode, sector_t block,
		    काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	अगर (INODE_VERSION(inode) == MINIX_V1)
		वापस V1_minix_get_block(inode, block, bh_result, create);
	अन्यथा
		वापस V2_minix_get_block(inode, block, bh_result, create);
पूर्ण

अटल पूर्णांक minix_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, minix_get_block, wbc);
पूर्ण

अटल पूर्णांक minix_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page,minix_get_block);
पूर्ण

पूर्णांक minix_prepare_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len)
अणु
	वापस __block_ग_लिखो_begin(page, pos, len, minix_get_block);
पूर्ण

अटल व्योम minix_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		minix_truncate(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक minix_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = block_ग_लिखो_begin(mapping, pos, len, flags, pagep,
				minix_get_block);
	अगर (unlikely(ret))
		minix_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t minix_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,minix_get_block);
पूर्ण

अटल स्थिर काष्ठा address_space_operations minix_aops = अणु
	.पढ़ोpage = minix_पढ़ोpage,
	.ग_लिखोpage = minix_ग_लिखोpage,
	.ग_लिखो_begin = minix_ग_लिखो_begin,
	.ग_लिखो_end = generic_ग_लिखो_end,
	.bmap = minix_bmap
पूर्ण;

अटल स्थिर काष्ठा inode_operations minix_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.getattr	= minix_getattr,
पूर्ण;

व्योम minix_set_inode(काष्ठा inode *inode, dev_t rdev)
अणु
	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &minix_file_inode_operations;
		inode->i_fop = &minix_file_operations;
		inode->i_mapping->a_ops = &minix_aops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &minix_dir_inode_operations;
		inode->i_fop = &minix_dir_operations;
		inode->i_mapping->a_ops = &minix_aops;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &minix_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &minix_aops;
	पूर्ण अन्यथा
		init_special_inode(inode, inode->i_mode, rdev);
पूर्ण

/*
 * The minix V1 function to पढ़ो an inode.
 */
अटल काष्ठा inode *V1_minix_iget(काष्ठा inode *inode)
अणु
	काष्ठा buffer_head * bh;
	काष्ठा minix_inode * raw_inode;
	काष्ठा minix_inode_info *minix_inode = minix_i(inode);
	पूर्णांक i;

	raw_inode = minix_V1_raw_inode(inode->i_sb, inode->i_ino, &bh);
	अगर (!raw_inode) अणु
		iget_failed(inode);
		वापस ERR_PTR(-EIO);
	पूर्ण
	अगर (raw_inode->i_nlinks == 0) अणु
		prपूर्णांकk("MINIX-fs: deleted inode referenced: %lu\n",
		       inode->i_ino);
		brअन्यथा(bh);
		iget_failed(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	inode->i_mode = raw_inode->i_mode;
	i_uid_ग_लिखो(inode, raw_inode->i_uid);
	i_gid_ग_लिखो(inode, raw_inode->i_gid);
	set_nlink(inode, raw_inode->i_nlinks);
	inode->i_size = raw_inode->i_size;
	inode->i_mसमय.tv_sec = inode->i_aसमय.tv_sec = inode->i_स_समय.tv_sec = raw_inode->i_समय;
	inode->i_mसमय.tv_nsec = 0;
	inode->i_aसमय.tv_nsec = 0;
	inode->i_स_समय.tv_nsec = 0;
	inode->i_blocks = 0;
	क्रम (i = 0; i < 9; i++)
		minix_inode->u.i1_data[i] = raw_inode->i_zone[i];
	minix_set_inode(inode, old_decode_dev(raw_inode->i_zone[0]));
	brअन्यथा(bh);
	unlock_new_inode(inode);
	वापस inode;
पूर्ण

/*
 * The minix V2 function to पढ़ो an inode.
 */
अटल काष्ठा inode *V2_minix_iget(काष्ठा inode *inode)
अणु
	काष्ठा buffer_head * bh;
	काष्ठा minix2_inode * raw_inode;
	काष्ठा minix_inode_info *minix_inode = minix_i(inode);
	पूर्णांक i;

	raw_inode = minix_V2_raw_inode(inode->i_sb, inode->i_ino, &bh);
	अगर (!raw_inode) अणु
		iget_failed(inode);
		वापस ERR_PTR(-EIO);
	पूर्ण
	अगर (raw_inode->i_nlinks == 0) अणु
		prपूर्णांकk("MINIX-fs: deleted inode referenced: %lu\n",
		       inode->i_ino);
		brअन्यथा(bh);
		iget_failed(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	inode->i_mode = raw_inode->i_mode;
	i_uid_ग_लिखो(inode, raw_inode->i_uid);
	i_gid_ग_लिखो(inode, raw_inode->i_gid);
	set_nlink(inode, raw_inode->i_nlinks);
	inode->i_size = raw_inode->i_size;
	inode->i_mसमय.tv_sec = raw_inode->i_mसमय;
	inode->i_aसमय.tv_sec = raw_inode->i_aसमय;
	inode->i_स_समय.tv_sec = raw_inode->i_स_समय;
	inode->i_mसमय.tv_nsec = 0;
	inode->i_aसमय.tv_nsec = 0;
	inode->i_स_समय.tv_nsec = 0;
	inode->i_blocks = 0;
	क्रम (i = 0; i < 10; i++)
		minix_inode->u.i2_data[i] = raw_inode->i_zone[i];
	minix_set_inode(inode, old_decode_dev(raw_inode->i_zone[0]));
	brअन्यथा(bh);
	unlock_new_inode(inode);
	वापस inode;
पूर्ण

/*
 * The global function to पढ़ो an inode.
 */
काष्ठा inode *minix_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा inode *inode;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	अगर (INODE_VERSION(inode) == MINIX_V1)
		वापस V1_minix_iget(inode);
	अन्यथा
		वापस V2_minix_iget(inode);
पूर्ण

/*
 * The minix V1 function to synchronize an inode.
 */
अटल काष्ठा buffer_head * V1_minix_update_inode(काष्ठा inode * inode)
अणु
	काष्ठा buffer_head * bh;
	काष्ठा minix_inode * raw_inode;
	काष्ठा minix_inode_info *minix_inode = minix_i(inode);
	पूर्णांक i;

	raw_inode = minix_V1_raw_inode(inode->i_sb, inode->i_ino, &bh);
	अगर (!raw_inode)
		वापस शून्य;
	raw_inode->i_mode = inode->i_mode;
	raw_inode->i_uid = fs_high2lowuid(i_uid_पढ़ो(inode));
	raw_inode->i_gid = fs_high2lowgid(i_gid_पढ़ो(inode));
	raw_inode->i_nlinks = inode->i_nlink;
	raw_inode->i_size = inode->i_size;
	raw_inode->i_समय = inode->i_mसमय.tv_sec;
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		raw_inode->i_zone[0] = old_encode_dev(inode->i_rdev);
	अन्यथा क्रम (i = 0; i < 9; i++)
		raw_inode->i_zone[i] = minix_inode->u.i1_data[i];
	mark_buffer_dirty(bh);
	वापस bh;
पूर्ण

/*
 * The minix V2 function to synchronize an inode.
 */
अटल काष्ठा buffer_head * V2_minix_update_inode(काष्ठा inode * inode)
अणु
	काष्ठा buffer_head * bh;
	काष्ठा minix2_inode * raw_inode;
	काष्ठा minix_inode_info *minix_inode = minix_i(inode);
	पूर्णांक i;

	raw_inode = minix_V2_raw_inode(inode->i_sb, inode->i_ino, &bh);
	अगर (!raw_inode)
		वापस शून्य;
	raw_inode->i_mode = inode->i_mode;
	raw_inode->i_uid = fs_high2lowuid(i_uid_पढ़ो(inode));
	raw_inode->i_gid = fs_high2lowgid(i_gid_पढ़ो(inode));
	raw_inode->i_nlinks = inode->i_nlink;
	raw_inode->i_size = inode->i_size;
	raw_inode->i_mसमय = inode->i_mसमय.tv_sec;
	raw_inode->i_aसमय = inode->i_aसमय.tv_sec;
	raw_inode->i_स_समय = inode->i_स_समय.tv_sec;
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		raw_inode->i_zone[0] = old_encode_dev(inode->i_rdev);
	अन्यथा क्रम (i = 0; i < 10; i++)
		raw_inode->i_zone[i] = minix_inode->u.i2_data[i];
	mark_buffer_dirty(bh);
	वापस bh;
पूर्ण

अटल पूर्णांक minix_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक err = 0;
	काष्ठा buffer_head *bh;

	अगर (INODE_VERSION(inode) == MINIX_V1)
		bh = V1_minix_update_inode(inode);
	अन्यथा
		bh = V2_minix_update_inode(inode);
	अगर (!bh)
		वापस -EIO;
	अगर (wbc->sync_mode == WB_SYNC_ALL && buffer_dirty(bh)) अणु
		sync_dirty_buffer(bh);
		अगर (buffer_req(bh) && !buffer_uptodate(bh)) अणु
			prपूर्णांकk("IO error syncing minix inode [%s:%08lx]\n",
				inode->i_sb->s_id, inode->i_ino);
			err = -EIO;
		पूर्ण
	पूर्ण
	brअन्यथा (bh);
	वापस err;
पूर्ण

पूर्णांक minix_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		  काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *sb = path->dentry->d_sb;
	काष्ठा inode *inode = d_inode(path->dentry);

	generic_fillattr(&init_user_ns, inode, stat);
	अगर (INODE_VERSION(inode) == MINIX_V1)
		stat->blocks = (BLOCK_SIZE / 512) * V1_minix_blocks(stat->size, sb);
	अन्यथा
		stat->blocks = (sb->s_blocksize / 512) * V2_minix_blocks(stat->size, sb);
	stat->blksize = sb->s_blocksize;
	वापस 0;
पूर्ण

/*
 * The function that is called क्रम file truncation.
 */
व्योम minix_truncate(काष्ठा inode * inode)
अणु
	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) || S_ISLNK(inode->i_mode)))
		वापस;
	अगर (INODE_VERSION(inode) == MINIX_V1)
		V1_minix_truncate(inode);
	अन्यथा
		V2_minix_truncate(inode);
पूर्ण

अटल काष्ठा dentry *minix_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, minix_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type minix_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "minix",
	.mount		= minix_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("minix");

अटल पूर्णांक __init init_minix_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&minix_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_minix_fs(व्योम)
अणु
        unरेजिस्टर_fileप्रणाली(&minix_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_minix_fs)
module_निकास(निकास_minix_fs)
MODULE_LICENSE("GPL");

