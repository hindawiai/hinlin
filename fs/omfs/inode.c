<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Optimized MPEG FS - inode and super operations.
 * Copyright (C) 2006 Bob Copeland <me@bobcopeland.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/cred.h>
#समावेश <linux/parser.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/crc-itu-t.h>
#समावेश "omfs.h"

MODULE_AUTHOR("Bob Copeland <me@bobcopeland.com>");
MODULE_DESCRIPTION("OMFS (ReplayTV/Karma) Filesystem for Linux");
MODULE_LICENSE("GPL");

काष्ठा buffer_head *omfs_bपढ़ो(काष्ठा super_block *sb, sector_t block)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	अगर (block >= sbi->s_num_blocks)
		वापस शून्य;

	वापस sb_bपढ़ो(sb, clus_to_blk(sbi, block));
पूर्ण

काष्ठा inode *omfs_new_inode(काष्ठा inode *dir, umode_t mode)
अणु
	काष्ठा inode *inode;
	u64 new_block;
	पूर्णांक err;
	पूर्णांक len;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(dir->i_sb);

	inode = new_inode(dir->i_sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	err = omfs_allocate_range(dir->i_sb, sbi->s_mirrors, sbi->s_mirrors,
			&new_block, &len);
	अगर (err)
		जाओ fail;

	inode->i_ino = new_block;
	inode_init_owner(&init_user_ns, inode, शून्य, mode);
	inode->i_mapping->a_ops = &omfs_aops;

	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	चयन (mode & S_IFMT) अणु
	हाल S_IFसूची:
		inode->i_op = &omfs_dir_inops;
		inode->i_fop = &omfs_dir_operations;
		inode->i_size = sbi->s_sys_blocksize;
		inc_nlink(inode);
		अवरोध;
	हाल S_IFREG:
		inode->i_op = &omfs_file_inops;
		inode->i_fop = &omfs_file_operations;
		inode->i_size = 0;
		अवरोध;
	पूर्ण

	insert_inode_hash(inode);
	mark_inode_dirty(inode);
	वापस inode;
fail:
	make_bad_inode(inode);
	iput(inode);
	वापस ERR_PTR(err);
पूर्ण

/*
 * Update the header checksums क्रम a dirty inode based on its contents.
 * Caller is expected to hold the buffer head underlying oi and mark it
 * dirty.
 */
अटल व्योम omfs_update_checksums(काष्ठा omfs_inode *oi)
अणु
	पूर्णांक xor, i, ofs = 0, count;
	u16 crc = 0;
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *) oi;

	count = be32_to_cpu(oi->i_head.h_body_size);
	ofs = माप(काष्ठा omfs_header);

	crc = crc_itu_t(crc, ptr + ofs, count);
	oi->i_head.h_crc = cpu_to_be16(crc);

	xor = ptr[0];
	क्रम (i = 1; i < OMFS_XOR_COUNT; i++)
		xor ^= ptr[i];

	oi->i_head.h_check_xor = xor;
पूर्ण

अटल पूर्णांक __omfs_ग_लिखो_inode(काष्ठा inode *inode, पूर्णांक रुको)
अणु
	काष्ठा omfs_inode *oi;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	काष्ठा buffer_head *bh, *bh2;
	u64 स_समय;
	पूर्णांक i;
	पूर्णांक ret = -EIO;
	पूर्णांक sync_failed = 0;

	/* get current inode since we may have written sibling ptrs etc. */
	bh = omfs_bपढ़ो(inode->i_sb, inode->i_ino);
	अगर (!bh)
		जाओ out;

	oi = (काष्ठा omfs_inode *) bh->b_data;

	oi->i_head.h_self = cpu_to_be64(inode->i_ino);
	अगर (S_ISसूची(inode->i_mode))
		oi->i_type = OMFS_सूची;
	अन्यथा अगर (S_ISREG(inode->i_mode))
		oi->i_type = OMFS_खाता;
	अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "omfs: unknown file type: %d\n",
			inode->i_mode);
		जाओ out_brअन्यथा;
	पूर्ण

	oi->i_head.h_body_size = cpu_to_be32(sbi->s_sys_blocksize -
		माप(काष्ठा omfs_header));
	oi->i_head.h_version = 1;
	oi->i_head.h_type = OMFS_INODE_NORMAL;
	oi->i_head.h_magic = OMFS_IMAGIC;
	oi->i_size = cpu_to_be64(inode->i_size);

	स_समय = inode->i_स_समय.tv_sec * 1000LL +
		((inode->i_स_समय.tv_nsec + 999)/1000);
	oi->i_स_समय = cpu_to_be64(स_समय);

	omfs_update_checksums(oi);

	mark_buffer_dirty(bh);
	अगर (रुको) अणु
		sync_dirty_buffer(bh);
		अगर (buffer_req(bh) && !buffer_uptodate(bh))
			sync_failed = 1;
	पूर्ण

	/* अगर mirroring ग_लिखोs, copy to next fsblock */
	क्रम (i = 1; i < sbi->s_mirrors; i++) अणु
		bh2 = omfs_bपढ़ो(inode->i_sb, inode->i_ino + i);
		अगर (!bh2)
			जाओ out_brअन्यथा;

		स_नकल(bh2->b_data, bh->b_data, bh->b_size);
		mark_buffer_dirty(bh2);
		अगर (रुको) अणु
			sync_dirty_buffer(bh2);
			अगर (buffer_req(bh2) && !buffer_uptodate(bh2))
				sync_failed = 1;
		पूर्ण
		brअन्यथा(bh2);
	पूर्ण
	ret = (sync_failed) ? -EIO : 0;
out_brअन्यथा:
	brअन्यथा(bh);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक omfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस __omfs_ग_लिखो_inode(inode, wbc->sync_mode == WB_SYNC_ALL);
पूर्ण

पूर्णांक omfs_sync_inode(काष्ठा inode *inode)
अणु
	वापस __omfs_ग_लिखो_inode(inode, 1);
पूर्ण

/*
 * called when an entry is deleted, need to clear the bits in the
 * biपंचांगaps.
 */
अटल व्योम omfs_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);

	अगर (inode->i_nlink)
		वापस;

	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_size = 0;
		omfs_shrink_inode(inode);
	पूर्ण

	omfs_clear_range(inode->i_sb, inode->i_ino, 2);
पूर्ण

काष्ठा inode *omfs_iget(काष्ठा super_block *sb, ino_t ino)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	काष्ठा omfs_inode *oi;
	काष्ठा buffer_head *bh;
	u64 स_समय;
	अचिन्हित दीर्घ nsecs;
	काष्ठा inode *inode;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	bh = omfs_bपढ़ो(inode->i_sb, ino);
	अगर (!bh)
		जाओ iget_failed;

	oi = (काष्ठा omfs_inode *)bh->b_data;

	/* check self */
	अगर (ino != be64_to_cpu(oi->i_head.h_self))
		जाओ fail_bh;

	inode->i_uid = sbi->s_uid;
	inode->i_gid = sbi->s_gid;

	स_समय = be64_to_cpu(oi->i_स_समय);
	nsecs = करो_भाग(स_समय, 1000) * 1000L;

	inode->i_aसमय.tv_sec = स_समय;
	inode->i_mसमय.tv_sec = स_समय;
	inode->i_स_समय.tv_sec = स_समय;
	inode->i_aसमय.tv_nsec = nsecs;
	inode->i_mसमय.tv_nsec = nsecs;
	inode->i_स_समय.tv_nsec = nsecs;

	inode->i_mapping->a_ops = &omfs_aops;

	चयन (oi->i_type) अणु
	हाल OMFS_सूची:
		inode->i_mode = S_IFसूची | (S_IRWXUGO & ~sbi->s_dmask);
		inode->i_op = &omfs_dir_inops;
		inode->i_fop = &omfs_dir_operations;
		inode->i_size = sbi->s_sys_blocksize;
		inc_nlink(inode);
		अवरोध;
	हाल OMFS_खाता:
		inode->i_mode = S_IFREG | (S_IRWXUGO & ~sbi->s_fmask);
		inode->i_fop = &omfs_file_operations;
		inode->i_size = be64_to_cpu(oi->i_size);
		अवरोध;
	पूर्ण
	brअन्यथा(bh);
	unlock_new_inode(inode);
	वापस inode;
fail_bh:
	brअन्यथा(bh);
iget_failed:
	iget_failed(inode);
	वापस ERR_PTR(-EIO);
पूर्ण

अटल व्योम omfs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	kमुक्त(sbi->s_imap);
	kमुक्त(sbi);
	sb->s_fs_info = शून्य;
पूर्ण

अटल पूर्णांक omfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *s = dentry->d_sb;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(s);
	u64 id = huge_encode_dev(s->s_bdev->bd_dev);

	buf->f_type = OMFS_MAGIC;
	buf->f_bsize = sbi->s_blocksize;
	buf->f_blocks = sbi->s_num_blocks;
	buf->f_files = sbi->s_num_blocks;
	buf->f_namelen = OMFS_NAMELEN;
	buf->f_fsid = u64_to_fsid(id);

	buf->f_bमुक्त = buf->f_bavail = buf->f_fमुक्त =
		omfs_count_मुक्त(s);

	वापस 0;
पूर्ण

/*
 * Display the mount options in /proc/mounts.
 */
अटल पूर्णांक omfs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(root->d_sb);
	umode_t cur_umask = current_umask();

	अगर (!uid_eq(sbi->s_uid, current_uid()))
		seq_म_लिखो(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, sbi->s_uid));
	अगर (!gid_eq(sbi->s_gid, current_gid()))
		seq_म_लिखो(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, sbi->s_gid));

	अगर (sbi->s_dmask == sbi->s_fmask) अणु
		अगर (sbi->s_fmask != cur_umask)
			seq_म_लिखो(m, ",umask=%o", sbi->s_fmask);
	पूर्ण अन्यथा अणु
		अगर (sbi->s_dmask != cur_umask)
			seq_म_लिखो(m, ",dmask=%o", sbi->s_dmask);
		अगर (sbi->s_fmask != cur_umask)
			seq_म_लिखो(m, ",fmask=%o", sbi->s_fmask);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations omfs_sops = अणु
	.ग_लिखो_inode	= omfs_ग_लिखो_inode,
	.evict_inode	= omfs_evict_inode,
	.put_super	= omfs_put_super,
	.statfs		= omfs_statfs,
	.show_options	= omfs_show_options,
पूर्ण;

/*
 * For Rio Karma, there is an on-disk मुक्त biपंचांगap whose location is
 * stored in the root block.  For ReplayTV, there is no such मुक्त biपंचांगap
 * so we have to walk the tree.  Both inodes and file data are allocated
 * from the same map.  This array can be big (300k) so we allocate
 * in units of the blocksize.
 */
अटल पूर्णांक omfs_get_imap(काष्ठा super_block *sb)
अणु
	अचिन्हित पूर्णांक biपंचांगap_size, array_size;
	पूर्णांक count;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	काष्ठा buffer_head *bh;
	अचिन्हित दीर्घ **ptr;
	sector_t block;

	biपंचांगap_size = DIV_ROUND_UP(sbi->s_num_blocks, 8);
	array_size = DIV_ROUND_UP(biपंचांगap_size, sb->s_blocksize);

	अगर (sbi->s_biपंचांगap_ino == ~0ULL)
		जाओ out;

	sbi->s_imap_size = array_size;
	sbi->s_imap = kसुस्मृति(array_size, माप(अचिन्हित दीर्घ *), GFP_KERNEL);
	अगर (!sbi->s_imap)
		जाओ nomem;

	block = clus_to_blk(sbi, sbi->s_biपंचांगap_ino);
	अगर (block >= sbi->s_num_blocks)
		जाओ nomem;

	ptr = sbi->s_imap;
	क्रम (count = biपंचांगap_size; count > 0; count -= sb->s_blocksize) अणु
		bh = sb_bपढ़ो(sb, block++);
		अगर (!bh)
			जाओ nomem_मुक्त;
		*ptr = kmemdup(bh->b_data, sb->s_blocksize, GFP_KERNEL);
		अगर (!*ptr) अणु
			brअन्यथा(bh);
			जाओ nomem_मुक्त;
		पूर्ण
		अगर (count < sb->s_blocksize)
			स_रखो((व्योम *)*ptr + count, 0xff,
				sb->s_blocksize - count);
		brअन्यथा(bh);
		ptr++;
	पूर्ण
out:
	वापस 0;

nomem_मुक्त:
	क्रम (count = 0; count < array_size; count++)
		kमुक्त(sbi->s_imap[count]);

	kमुक्त(sbi->s_imap);
nomem:
	sbi->s_imap = शून्य;
	sbi->s_imap_size = 0;
	वापस -ENOMEM;
पूर्ण

क्रमागत अणु
	Opt_uid, Opt_gid, Opt_umask, Opt_dmask, Opt_fmask, Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_umask, "umask=%o"पूर्ण,
	अणुOpt_dmask, "dmask=%o"पूर्ण,
	अणुOpt_fmask, "fmask=%o"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अटल पूर्णांक parse_options(अक्षर *options, काष्ठा omfs_sb_info *sbi)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_uid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			sbi->s_uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(sbi->s_uid))
				वापस 0;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			sbi->s_gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(sbi->s_gid))
				वापस 0;
			अवरोध;
		हाल Opt_umask:
			अगर (match_octal(&args[0], &option))
				वापस 0;
			sbi->s_fmask = sbi->s_dmask = option;
			अवरोध;
		हाल Opt_dmask:
			अगर (match_octal(&args[0], &option))
				वापस 0;
			sbi->s_dmask = option;
			अवरोध;
		हाल Opt_fmask:
			अगर (match_octal(&args[0], &option))
				वापस 0;
			sbi->s_fmask = option;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक omfs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh, *bh2;
	काष्ठा omfs_super_block *omfs_sb;
	काष्ठा omfs_root_block *omfs_rb;
	काष्ठा omfs_sb_info *sbi;
	काष्ठा inode *root;
	पूर्णांक ret = -EINVAL;

	sbi = kzalloc(माप(काष्ठा omfs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sb->s_fs_info = sbi;

	sbi->s_uid = current_uid();
	sbi->s_gid = current_gid();
	sbi->s_dmask = sbi->s_fmask = current_umask();

	अगर (!parse_options((अक्षर *) data, sbi))
		जाओ end;

	sb->s_maxbytes = 0xffffffff;

	sb->s_समय_gran = NSEC_PER_MSEC;
	sb->s_समय_min = 0;
	sb->s_समय_max = U64_MAX / MSEC_PER_SEC;

	sb_set_blocksize(sb, 0x200);

	bh = sb_bपढ़ो(sb, 0);
	अगर (!bh)
		जाओ end;

	omfs_sb = (काष्ठा omfs_super_block *)bh->b_data;

	अगर (omfs_sb->s_magic != cpu_to_be32(OMFS_MAGIC)) अणु
		अगर (!silent)
			prपूर्णांकk(KERN_ERR "omfs: Invalid superblock (%x)\n",
				   omfs_sb->s_magic);
		जाओ out_brअन्यथा_bh;
	पूर्ण
	sb->s_magic = OMFS_MAGIC;

	sbi->s_num_blocks = be64_to_cpu(omfs_sb->s_num_blocks);
	sbi->s_blocksize = be32_to_cpu(omfs_sb->s_blocksize);
	sbi->s_mirrors = be32_to_cpu(omfs_sb->s_mirrors);
	sbi->s_root_ino = be64_to_cpu(omfs_sb->s_root_block);
	sbi->s_sys_blocksize = be32_to_cpu(omfs_sb->s_sys_blocksize);
	mutex_init(&sbi->s_biपंचांगap_lock);

	अगर (sbi->s_num_blocks > OMFS_MAX_BLOCKS) अणु
		prपूर्णांकk(KERN_ERR "omfs: sysblock number (%llx) is out of range\n",
		       (अचिन्हित दीर्घ दीर्घ)sbi->s_num_blocks);
		जाओ out_brअन्यथा_bh;
	पूर्ण

	अगर (sbi->s_sys_blocksize > PAGE_SIZE) अणु
		prपूर्णांकk(KERN_ERR "omfs: sysblock size (%d) is out of range\n",
			sbi->s_sys_blocksize);
		जाओ out_brअन्यथा_bh;
	पूर्ण

	अगर (sbi->s_blocksize < sbi->s_sys_blocksize ||
	    sbi->s_blocksize > OMFS_MAX_BLOCK_SIZE) अणु
		prपूर्णांकk(KERN_ERR "omfs: block size (%d) is out of range\n",
			sbi->s_blocksize);
		जाओ out_brअन्यथा_bh;
	पूर्ण

	/*
	 * Use sys_blocksize as the fs block since it is smaller than a
	 * page जबतक the fs blocksize can be larger.
	 */
	sb_set_blocksize(sb, sbi->s_sys_blocksize);

	/*
	 * ...and the dअगरference goes पूर्णांकo a shअगरt.  sys_blocksize is always
	 * a घातer of two factor of blocksize.
	 */
	sbi->s_block_shअगरt = get_biपंचांगask_order(sbi->s_blocksize) -
		get_biपंचांगask_order(sbi->s_sys_blocksize);

	bh2 = omfs_bपढ़ो(sb, be64_to_cpu(omfs_sb->s_root_block));
	अगर (!bh2)
		जाओ out_brअन्यथा_bh;

	omfs_rb = (काष्ठा omfs_root_block *)bh2->b_data;

	sbi->s_biपंचांगap_ino = be64_to_cpu(omfs_rb->r_biपंचांगap);
	sbi->s_clustersize = be32_to_cpu(omfs_rb->r_clustersize);

	अगर (sbi->s_num_blocks != be64_to_cpu(omfs_rb->r_num_blocks)) अणु
		prपूर्णांकk(KERN_ERR "omfs: block count discrepancy between "
			"super and root blocks (%llx, %llx)\n",
			(अचिन्हित दीर्घ दीर्घ)sbi->s_num_blocks,
			(अचिन्हित दीर्घ दीर्घ)be64_to_cpu(omfs_rb->r_num_blocks));
		जाओ out_brअन्यथा_bh2;
	पूर्ण

	अगर (sbi->s_biपंचांगap_ino != ~0ULL &&
	    sbi->s_biपंचांगap_ino > sbi->s_num_blocks) अणु
		prपूर्णांकk(KERN_ERR "omfs: free space bitmap location is corrupt "
			"(%llx, total blocks %llx)\n",
			(अचिन्हित दीर्घ दीर्घ) sbi->s_biपंचांगap_ino,
			(अचिन्हित दीर्घ दीर्घ) sbi->s_num_blocks);
		जाओ out_brअन्यथा_bh2;
	पूर्ण
	अगर (sbi->s_clustersize < 1 ||
	    sbi->s_clustersize > OMFS_MAX_CLUSTER_SIZE) अणु
		prपूर्णांकk(KERN_ERR "omfs: cluster size out of range (%d)",
			sbi->s_clustersize);
		जाओ out_brअन्यथा_bh2;
	पूर्ण

	ret = omfs_get_imap(sb);
	अगर (ret)
		जाओ out_brअन्यथा_bh2;

	sb->s_op = &omfs_sops;

	root = omfs_iget(sb, be64_to_cpu(omfs_rb->r_root_dir));
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);
		जाओ out_brअन्यथा_bh2;
	पूर्ण

	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		ret = -ENOMEM;
		जाओ out_brअन्यथा_bh2;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "omfs: Mounted volume %s\n", omfs_rb->r_name);

	ret = 0;
out_brअन्यथा_bh2:
	brअन्यथा(bh2);
out_brअन्यथा_bh:
	brअन्यथा(bh);
end:
	अगर (ret)
		kमुक्त(sbi);
	वापस ret;
पूर्ण

अटल काष्ठा dentry *omfs_mount(काष्ठा file_प्रणाली_type *fs_type,
			पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, omfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type omfs_fs_type = अणु
	.owner = THIS_MODULE,
	.name = "omfs",
	.mount = omfs_mount,
	.समाप्त_sb = समाप्त_block_super,
	.fs_flags = FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("omfs");

अटल पूर्णांक __init init_omfs_fs(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&omfs_fs_type);
पूर्ण

अटल व्योम __निकास निकास_omfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&omfs_fs_type);
पूर्ण

module_init(init_omfs_fs);
module_निकास(निकास_omfs_fs);
