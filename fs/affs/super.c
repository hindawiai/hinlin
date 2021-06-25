<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/affs/inode.c
 *
 *  (c) 1996  Hans-Joachim Widmaier - Rewritten
 *
 *  (C) 1993  Ray Burr - Modअगरied क्रम Amiga FFS fileप्रणाली.
 *
 *  (C) 1992  Eric Youngdale Modअगरied क्रम ISO 9660 fileप्रणाली.
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/statfs.h>
#समावेश <linux/parser.h>
#समावेश <linux/magic.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/slab.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/iversion.h>
#समावेश "affs.h"

अटल पूर्णांक affs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);
अटल पूर्णांक affs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root);
अटल पूर्णांक affs_remount (काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data);

अटल व्योम
affs_commit_super(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);
	काष्ठा buffer_head *bh = sbi->s_root_bh;
	काष्ठा affs_root_tail *tail = AFFS_ROOT_TAIL(sb, bh);

	lock_buffer(bh);
	affs_secs_to_datestamp(kसमय_get_real_seconds(), &tail->disk_change);
	affs_fix_checksum(sb, bh);
	unlock_buffer(bh);

	mark_buffer_dirty(bh);
	अगर (रुको)
		sync_dirty_buffer(bh);
पूर्ण

अटल व्योम
affs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);
	pr_debug("%s()\n", __func__);

	cancel_delayed_work_sync(&sbi->sb_work);
पूर्ण

अटल पूर्णांक
affs_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	affs_commit_super(sb, रुको);
	वापस 0;
पूर्ण

अटल व्योम flush_superblock(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा affs_sb_info *sbi;
	काष्ठा super_block *sb;

	sbi = container_of(work, काष्ठा affs_sb_info, sb_work.work);
	sb = sbi->sb;

	spin_lock(&sbi->work_lock);
	sbi->work_queued = 0;
	spin_unlock(&sbi->work_lock);

	affs_commit_super(sb, 1);
पूर्ण

व्योम affs_mark_sb_dirty(काष्ठा super_block *sb)
अणु
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);
	अचिन्हित दीर्घ delay;

	अगर (sb_rकरोnly(sb))
	       वापस;

	spin_lock(&sbi->work_lock);
	अगर (!sbi->work_queued) अणु
	       delay = msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
	       queue_delayed_work(प्रणाली_दीर्घ_wq, &sbi->sb_work, delay);
	       sbi->work_queued = 1;
	पूर्ण
	spin_unlock(&sbi->work_lock);
पूर्ण

अटल काष्ठा kmem_cache * affs_inode_cachep;

अटल काष्ठा inode *affs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा affs_inode_info *i;

	i = kmem_cache_alloc(affs_inode_cachep, GFP_KERNEL);
	अगर (!i)
		वापस शून्य;

	inode_set_iversion(&i->vfs_inode, 1);
	i->i_lc = शून्य;
	i->i_ext_bh = शून्य;
	i->i_pa_cnt = 0;

	वापस &i->vfs_inode;
पूर्ण

अटल व्योम affs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(affs_inode_cachep, AFFS_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा affs_inode_info *ei = (काष्ठा affs_inode_info *) foo;

	mutex_init(&ei->i_link_lock);
	mutex_init(&ei->i_ext_lock);
	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	affs_inode_cachep = kmem_cache_create("affs_inode_cache",
					     माप(काष्ठा affs_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (affs_inode_cachep == शून्य)
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
	kmem_cache_destroy(affs_inode_cachep);
पूर्ण

अटल स्थिर काष्ठा super_operations affs_sops = अणु
	.alloc_inode	= affs_alloc_inode,
	.मुक्त_inode	= affs_मुक्त_inode,
	.ग_लिखो_inode	= affs_ग_लिखो_inode,
	.evict_inode	= affs_evict_inode,
	.put_super	= affs_put_super,
	.sync_fs	= affs_sync_fs,
	.statfs		= affs_statfs,
	.remount_fs	= affs_remount,
	.show_options	= affs_show_options,
पूर्ण;

क्रमागत अणु
	Opt_bs, Opt_mode, Opt_mufs, Opt_notruncate, Opt_prefix, Opt_protect,
	Opt_reserved, Opt_root, Opt_setgid, Opt_setuid,
	Opt_verbose, Opt_volume, Opt_ignore, Opt_err,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_bs, "bs=%u"पूर्ण,
	अणुOpt_mode, "mode=%o"पूर्ण,
	अणुOpt_mufs, "mufs"पूर्ण,
	अणुOpt_notruncate, "nofilenametruncate"पूर्ण,
	अणुOpt_prefix, "prefix=%s"पूर्ण,
	अणुOpt_protect, "protect"पूर्ण,
	अणुOpt_reserved, "reserved=%u"पूर्ण,
	अणुOpt_root, "root=%u"पूर्ण,
	अणुOpt_setgid, "setgid=%u"पूर्ण,
	अणुOpt_setuid, "setuid=%u"पूर्ण,
	अणुOpt_verbose, "verbose"पूर्ण,
	अणुOpt_volume, "volume=%s"पूर्ण,
	अणुOpt_ignore, "grpquota"पूर्ण,
	अणुOpt_ignore, "noquota"पूर्ण,
	अणुOpt_ignore, "quota"पूर्ण,
	अणुOpt_ignore, "usrquota"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अटल पूर्णांक
parse_options(अक्षर *options, kuid_t *uid, kgid_t *gid, पूर्णांक *mode, पूर्णांक *reserved, s32 *root,
		पूर्णांक *blocksize, अक्षर **prefix, अक्षर *volume, अचिन्हित दीर्घ *mount_opts)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];

	/* Fill in शेषs */

	*uid        = current_uid();
	*gid        = current_gid();
	*reserved   = 2;
	*root       = -1;
	*blocksize  = -1;
	volume[0]   = ':';
	volume[1]   = 0;
	*mount_opts = 0;
	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token, n, option;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_bs:
			अगर (match_पूर्णांक(&args[0], &n))
				वापस 0;
			अगर (n != 512 && n != 1024 && n != 2048
			    && n != 4096) अणु
				pr_warn("Invalid blocksize (512, 1024, 2048, 4096 allowed)\n");
				वापस 0;
			पूर्ण
			*blocksize = n;
			अवरोध;
		हाल Opt_mode:
			अगर (match_octal(&args[0], &option))
				वापस 0;
			*mode = option & 0777;
			affs_set_opt(*mount_opts, SF_SETMODE);
			अवरोध;
		हाल Opt_mufs:
			affs_set_opt(*mount_opts, SF_MUFS);
			अवरोध;
		हाल Opt_notruncate:
			affs_set_opt(*mount_opts, SF_NO_TRUNCATE);
			अवरोध;
		हाल Opt_prefix:
			kमुक्त(*prefix);
			*prefix = match_strdup(&args[0]);
			अगर (!*prefix)
				वापस 0;
			affs_set_opt(*mount_opts, SF_PREFIX);
			अवरोध;
		हाल Opt_protect:
			affs_set_opt(*mount_opts, SF_IMMUTABLE);
			अवरोध;
		हाल Opt_reserved:
			अगर (match_पूर्णांक(&args[0], reserved))
				वापस 0;
			अवरोध;
		हाल Opt_root:
			अगर (match_पूर्णांक(&args[0], root))
				वापस 0;
			अवरोध;
		हाल Opt_setgid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			*gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(*gid))
				वापस 0;
			affs_set_opt(*mount_opts, SF_SETGID);
			अवरोध;
		हाल Opt_setuid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			*uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(*uid))
				वापस 0;
			affs_set_opt(*mount_opts, SF_SETUID);
			अवरोध;
		हाल Opt_verbose:
			affs_set_opt(*mount_opts, SF_VERBOSE);
			अवरोध;
		हाल Opt_volume: अणु
			अक्षर *vol = match_strdup(&args[0]);
			अगर (!vol)
				वापस 0;
			strlcpy(volume, vol, 32);
			kमुक्त(vol);
			अवरोध;
		पूर्ण
		हाल Opt_ignore:
		 	/* Silently ignore the quota options */
			अवरोध;
		शेष:
			pr_warn("Unrecognized mount option \"%s\" or missing value\n",
				p);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक affs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा super_block *sb = root->d_sb;
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);

	अगर (sb->s_blocksize)
		seq_म_लिखो(m, ",bs=%lu", sb->s_blocksize);
	अगर (affs_test_opt(sbi->s_flags, SF_SETMODE))
		seq_म_लिखो(m, ",mode=%o", sbi->s_mode);
	अगर (affs_test_opt(sbi->s_flags, SF_MUFS))
		seq_माला_दो(m, ",mufs");
	अगर (affs_test_opt(sbi->s_flags, SF_NO_TRUNCATE))
		seq_माला_दो(m, ",nofilenametruncate");
	अगर (affs_test_opt(sbi->s_flags, SF_PREFIX))
		seq_म_लिखो(m, ",prefix=%s", sbi->s_prefix);
	अगर (affs_test_opt(sbi->s_flags, SF_IMMUTABLE))
		seq_माला_दो(m, ",protect");
	अगर (sbi->s_reserved != 2)
		seq_म_लिखो(m, ",reserved=%u", sbi->s_reserved);
	अगर (sbi->s_root_block != (sbi->s_reserved + sbi->s_partition_size - 1) / 2)
		seq_म_लिखो(m, ",root=%u", sbi->s_root_block);
	अगर (affs_test_opt(sbi->s_flags, SF_SETGID))
		seq_म_लिखो(m, ",setgid=%u",
			   from_kgid_munged(&init_user_ns, sbi->s_gid));
	अगर (affs_test_opt(sbi->s_flags, SF_SETUID))
		seq_म_लिखो(m, ",setuid=%u",
			   from_kuid_munged(&init_user_ns, sbi->s_uid));
	अगर (affs_test_opt(sbi->s_flags, SF_VERBOSE))
		seq_माला_दो(m, ",verbose");
	अगर (sbi->s_volume[0])
		seq_म_लिखो(m, ",volume=%s", sbi->s_volume);
	वापस 0;
पूर्ण

/* This function definitely needs to be split up. Some fine day I'll
 * hopefully have the guts to करो so. Until then: sorry क्रम the mess.
 */

अटल पूर्णांक affs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा affs_sb_info	*sbi;
	काष्ठा buffer_head	*root_bh = शून्य;
	काष्ठा buffer_head	*boot_bh;
	काष्ठा inode		*root_inode = शून्य;
	s32			 root_block;
	पूर्णांक			 size, blocksize;
	u32			 chksum;
	पूर्णांक			 num_bm;
	पूर्णांक			 i, j;
	kuid_t			 uid;
	kgid_t			 gid;
	पूर्णांक			 reserved;
	अचिन्हित दीर्घ		 mount_flags;
	पूर्णांक			 पंचांगp_flags;	/* fix remount prototype... */
	u8			 sig[4];
	पूर्णांक			 ret;

	pr_debug("read_super(%s)\n", data ? (स्थिर अक्षर *)data : "no options");

	sb->s_magic             = AFFS_SUPER_MAGIC;
	sb->s_op                = &affs_sops;
	sb->s_flags |= SB_NOसूचीATIME;

	sb->s_समय_gran = NSEC_PER_SEC;
	sb->s_समय_min = sys_tz.tz_minuteswest * 60 + AFFS_EPOCH_DELTA;
	sb->s_समय_max = 86400LL * U32_MAX + 86400 + sb->s_समय_min;

	sbi = kzalloc(माप(काष्ठा affs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sb->s_fs_info = sbi;
	sbi->sb = sb;
	mutex_init(&sbi->s_bmlock);
	spin_lock_init(&sbi->symlink_lock);
	spin_lock_init(&sbi->work_lock);
	INIT_DELAYED_WORK(&sbi->sb_work, flush_superblock);

	अगर (!parse_options(data,&uid,&gid,&i,&reserved,&root_block,
				&blocksize,&sbi->s_prefix,
				sbi->s_volume, &mount_flags)) अणु
		pr_err("Error parsing options\n");
		वापस -EINVAL;
	पूर्ण
	/* N.B. after this poपूर्णांक s_prefix must be released */

	sbi->s_flags   = mount_flags;
	sbi->s_mode    = i;
	sbi->s_uid     = uid;
	sbi->s_gid     = gid;
	sbi->s_reserved= reserved;

	/* Get the size of the device in 512-byte blocks.
	 * If we later see that the partition uses bigger
	 * blocks, we will have to change it.
	 */

	size = i_size_पढ़ो(sb->s_bdev->bd_inode) >> 9;
	pr_debug("initial blocksize=%d, #blocks=%d\n", 512, size);

	affs_set_blocksize(sb, PAGE_SIZE);
	/* Try to find root block. Its location depends on the block size. */

	i = bdev_logical_block_size(sb->s_bdev);
	j = PAGE_SIZE;
	अगर (blocksize > 0) अणु
		i = j = blocksize;
		size = size / (blocksize / 512);
	पूर्ण

	क्रम (blocksize = i; blocksize <= j; blocksize <<= 1, size >>= 1) अणु
		sbi->s_root_block = root_block;
		अगर (root_block < 0)
			sbi->s_root_block = (reserved + size - 1) / 2;
		pr_debug("setting blocksize to %d\n", blocksize);
		affs_set_blocksize(sb, blocksize);
		sbi->s_partition_size = size;

		/* The root block location that was calculated above is not
		 * correct अगर the partition size is an odd number of 512-
		 * byte blocks, which will be rounded करोwn to a number of
		 * 1024-byte blocks, and अगर there were an even number of
		 * reserved blocks. Ideally, all partition checkers should
		 * report the real number of blocks of the real blocksize,
		 * but since this just cannot be करोne, we have to try to
		 * find the root block anyways. In the above हाल, it is one
		 * block behind the calculated one. So we check this one, too.
		 */
		क्रम (num_bm = 0; num_bm < 2; num_bm++) अणु
			pr_debug("Dev %s, trying root=%u, bs=%d, "
				"size=%d, reserved=%d\n",
				sb->s_id,
				sbi->s_root_block + num_bm,
				blocksize, size, reserved);
			root_bh = affs_bपढ़ो(sb, sbi->s_root_block + num_bm);
			अगर (!root_bh)
				जारी;
			अगर (!affs_checksum_block(sb, root_bh) &&
			    be32_to_cpu(AFFS_ROOT_HEAD(root_bh)->ptype) == T_SHORT &&
			    be32_to_cpu(AFFS_ROOT_TAIL(sb, root_bh)->stype) == ST_ROOT) अणु
				sbi->s_hashsize    = blocksize / 4 - 56;
				sbi->s_root_block += num_bm;
				जाओ got_root;
			पूर्ण
			affs_brअन्यथा(root_bh);
			root_bh = शून्य;
		पूर्ण
	पूर्ण
	अगर (!silent)
		pr_err("No valid root block on device %s\n", sb->s_id);
	वापस -EINVAL;

	/* N.B. after this poपूर्णांक bh must be released */
got_root:
	/* Keep super block in cache */
	sbi->s_root_bh = root_bh;
	root_block = sbi->s_root_block;

	/* Find out which kind of FS we have */
	boot_bh = sb_bपढ़ो(sb, 0);
	अगर (!boot_bh) अणु
		pr_err("Cannot read boot block\n");
		वापस -EINVAL;
	पूर्ण
	स_नकल(sig, boot_bh->b_data, 4);
	brअन्यथा(boot_bh);
	chksum = be32_to_cpu(*(__be32 *)sig);

	/* Dircache fileप्रणालीs are compatible with non-dircache ones
	 * when पढ़ोing. As दीर्घ as they aren't supported, writing is
	 * not recommended.
	 */
	अगर ((chksum == FS_DCFFS || chksum == MUFS_DCFFS || chksum == FS_DCOFS
	     || chksum == MUFS_DCOFS) && !sb_rकरोnly(sb)) अणु
		pr_notice("Dircache FS - mounting %s read only\n", sb->s_id);
		sb->s_flags |= SB_RDONLY;
	पूर्ण
	चयन (chksum) अणु
	हाल MUFS_FS:
	हाल MUFS_INTLFFS:
	हाल MUFS_DCFFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		fallthrough;
	हाल FS_INTLFFS:
	हाल FS_DCFFS:
		affs_set_opt(sbi->s_flags, SF_INTL);
		अवरोध;
	हाल MUFS_FFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		अवरोध;
	हाल FS_FFS:
		अवरोध;
	हाल MUFS_OFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		fallthrough;
	हाल FS_OFS:
		affs_set_opt(sbi->s_flags, SF_OFS);
		sb->s_flags |= SB_NOEXEC;
		अवरोध;
	हाल MUFS_DCOFS:
	हाल MUFS_INTLOFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		fallthrough;
	हाल FS_DCOFS:
	हाल FS_INTLOFS:
		affs_set_opt(sbi->s_flags, SF_INTL);
		affs_set_opt(sbi->s_flags, SF_OFS);
		sb->s_flags |= SB_NOEXEC;
		अवरोध;
	शेष:
		pr_err("Unknown filesystem on device %s: %08X\n",
		       sb->s_id, chksum);
		वापस -EINVAL;
	पूर्ण

	अगर (affs_test_opt(mount_flags, SF_VERBOSE)) अणु
		u8 len = AFFS_ROOT_TAIL(sb, root_bh)->disk_name[0];
		pr_notice("Mounting volume \"%.*s\": Type=%.3s\\%c, Blocksize=%d\n",
			len > 31 ? 31 : len,
			AFFS_ROOT_TAIL(sb, root_bh)->disk_name + 1,
			sig, sig[3] + '0', blocksize);
	पूर्ण

	sb->s_flags |= SB_NODEV | SB_NOSUID;

	sbi->s_data_blksize = sb->s_blocksize;
	अगर (affs_test_opt(sbi->s_flags, SF_OFS))
		sbi->s_data_blksize -= 24;

	पंचांगp_flags = sb->s_flags;
	ret = affs_init_biपंचांगap(sb, &पंचांगp_flags);
	अगर (ret)
		वापस ret;
	sb->s_flags = पंचांगp_flags;

	/* set up enough so that it can पढ़ो an inode */

	root_inode = affs_iget(sb, root_block);
	अगर (IS_ERR(root_inode))
		वापस PTR_ERR(root_inode);

	अगर (affs_test_opt(AFFS_SB(sb)->s_flags, SF_INTL))
		sb->s_d_op = &affs_पूर्णांकl_dentry_operations;
	अन्यथा
		sb->s_d_op = &affs_dentry_operations;

	sb->s_root = d_make_root(root_inode);
	अगर (!sb->s_root) अणु
		pr_err("AFFS: Get root inode failed\n");
		वापस -ENOMEM;
	पूर्ण

	sb->s_export_op = &affs_export_ops;
	pr_debug("s_flags=%lX\n", sb->s_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
affs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा affs_sb_info	*sbi = AFFS_SB(sb);
	पूर्णांक			 blocksize;
	kuid_t			 uid;
	kgid_t			 gid;
	पूर्णांक			 mode;
	पूर्णांक			 reserved;
	पूर्णांक			 root_block;
	अचिन्हित दीर्घ		 mount_flags;
	पूर्णांक			 res = 0;
	अक्षर			 volume[32];
	अक्षर			*prefix = शून्य;

	pr_debug("%s(flags=0x%x,opts=\"%s\")\n", __func__, *flags, data);

	sync_fileप्रणाली(sb);
	*flags |= SB_NOसूचीATIME;

	स_नकल(volume, sbi->s_volume, 32);
	अगर (!parse_options(data, &uid, &gid, &mode, &reserved, &root_block,
			   &blocksize, &prefix, volume,
			   &mount_flags)) अणु
		kमुक्त(prefix);
		वापस -EINVAL;
	पूर्ण

	flush_delayed_work(&sbi->sb_work);

	sbi->s_flags = mount_flags;
	sbi->s_mode  = mode;
	sbi->s_uid   = uid;
	sbi->s_gid   = gid;
	/* protect against पढ़ोers */
	spin_lock(&sbi->symlink_lock);
	अगर (prefix) अणु
		kमुक्त(sbi->s_prefix);
		sbi->s_prefix = prefix;
	पूर्ण
	स_नकल(sbi->s_volume, volume, 32);
	spin_unlock(&sbi->symlink_lock);

	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		वापस 0;

	अगर (*flags & SB_RDONLY)
		affs_मुक्त_biपंचांगap(sb);
	अन्यथा
		res = affs_init_biपंचांगap(sb, flags);

	वापस res;
पूर्ण

अटल पूर्णांक
affs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	पूर्णांक		 मुक्त;
	u64		 id = huge_encode_dev(sb->s_bdev->bd_dev);

	pr_debug("%s() partsize=%d, reserved=%d\n",
		 __func__, AFFS_SB(sb)->s_partition_size,
		 AFFS_SB(sb)->s_reserved);

	मुक्त          = affs_count_मुक्त_blocks(sb);
	buf->f_type    = AFFS_SUPER_MAGIC;
	buf->f_bsize   = sb->s_blocksize;
	buf->f_blocks  = AFFS_SB(sb)->s_partition_size - AFFS_SB(sb)->s_reserved;
	buf->f_bमुक्त   = मुक्त;
	buf->f_bavail  = मुक्त;
	buf->f_fsid    = u64_to_fsid(id);
	buf->f_namelen = AFFSNAMEMAX;
	वापस 0;
पूर्ण

अटल काष्ठा dentry *affs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, affs_fill_super);
पूर्ण

अटल व्योम affs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);
	समाप्त_block_super(sb);
	अगर (sbi) अणु
		affs_मुक्त_biपंचांगap(sb);
		affs_brअन्यथा(sbi->s_root_bh);
		kमुक्त(sbi->s_prefix);
		mutex_destroy(&sbi->s_bmlock);
		kमुक्त(sbi);
	पूर्ण
पूर्ण

अटल काष्ठा file_प्रणाली_type affs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "affs",
	.mount		= affs_mount,
	.समाप्त_sb	= affs_समाप्त_sb,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("affs");

अटल पूर्णांक __init init_affs_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&affs_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_affs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&affs_fs_type);
	destroy_inodecache();
पूर्ण

MODULE_DESCRIPTION("Amiga filesystem support for Linux");
MODULE_LICENSE("GPL");

module_init(init_affs_fs)
module_निकास(निकास_affs_fs)
