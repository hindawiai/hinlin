<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/mount.h>
#समावेश <linux/cred.h>
#समावेश <linux/statfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/iversion.h>
#समावेश <linux/nls.h>
#समावेश <linux/buffer_head.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

अटल अक्षर exfat_शेष_ioअक्षरset[] = CONFIG_EXFAT_DEFAULT_IOCHARSET;
अटल काष्ठा kmem_cache *exfat_inode_cachep;

अटल व्योम exfat_मुक्त_ioअक्षरset(काष्ठा exfat_sb_info *sbi)
अणु
	अगर (sbi->options.ioअक्षरset != exfat_शेष_ioअक्षरset)
		kमुक्त(sbi->options.ioअक्षरset);
पूर्ण

अटल व्योम exfat_delayed_मुक्त(काष्ठा rcu_head *p)
अणु
	काष्ठा exfat_sb_info *sbi = container_of(p, काष्ठा exfat_sb_info, rcu);

	unload_nls(sbi->nls_io);
	exfat_मुक्त_ioअक्षरset(sbi);
	exfat_मुक्त_upहाल_table(sbi);
	kमुक्त(sbi);
पूर्ण

अटल व्योम exfat_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	mutex_lock(&sbi->s_lock);
	exfat_मुक्त_biपंचांगap(sbi);
	brअन्यथा(sbi->boot_bh);
	mutex_unlock(&sbi->s_lock);

	call_rcu(&sbi->rcu, exfat_delayed_मुक्त);
पूर्ण

अटल पूर्णांक exfat_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	पूर्णांक err = 0;

	अगर (!रुको)
		वापस 0;

	/* If there are some dirty buffers in the bdev inode */
	mutex_lock(&sbi->s_lock);
	sync_blockdev(sb->s_bdev);
	अगर (exfat_clear_volume_dirty(sb))
		err = -EIO;
	mutex_unlock(&sbi->s_lock);
	वापस err;
पूर्ण

अटल पूर्णांक exfat_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	अचिन्हित दीर्घ दीर्घ id = huge_encode_dev(sb->s_bdev->bd_dev);

	अगर (sbi->used_clusters == EXFAT_CLUSTERS_UNTRACKED) अणु
		mutex_lock(&sbi->s_lock);
		अगर (exfat_count_used_clusters(sb, &sbi->used_clusters)) अणु
			mutex_unlock(&sbi->s_lock);
			वापस -EIO;
		पूर्ण
		mutex_unlock(&sbi->s_lock);
	पूर्ण

	buf->f_type = sb->s_magic;
	buf->f_bsize = sbi->cluster_size;
	buf->f_blocks = sbi->num_clusters - 2; /* clu 0 & 1 */
	buf->f_bमुक्त = buf->f_blocks - sbi->used_clusters;
	buf->f_bavail = buf->f_bमुक्त;
	buf->f_fsid = u64_to_fsid(id);
	/* Unicode utf16 255 अक्षरacters */
	buf->f_namelen = EXFAT_MAX_खाता_LEN * NLS_MAX_CHARSET_SIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_set_vol_flags(काष्ठा super_block *sb, अचिन्हित लघु new_flags)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा boot_sector *p_boot = (काष्ठा boot_sector *)sbi->boot_bh->b_data;
	bool sync;

	/* retain persistent-flags */
	new_flags |= sbi->vol_flags_persistent;

	/* flags are not changed */
	अगर (sbi->vol_flags == new_flags)
		वापस 0;

	sbi->vol_flags = new_flags;

	/* skip updating volume dirty flag,
	 * अगर this volume has been mounted with पढ़ो-only
	 */
	अगर (sb_rकरोnly(sb))
		वापस 0;

	p_boot->vol_flags = cpu_to_le16(new_flags);

	अगर ((new_flags & VOLUME_सूचीTY) && !buffer_dirty(sbi->boot_bh))
		sync = true;
	अन्यथा
		sync = false;

	set_buffer_uptodate(sbi->boot_bh);
	mark_buffer_dirty(sbi->boot_bh);

	अगर (sync)
		sync_dirty_buffer(sbi->boot_bh);
	वापस 0;
पूर्ण

पूर्णांक exfat_set_volume_dirty(काष्ठा super_block *sb)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	वापस exfat_set_vol_flags(sb, sbi->vol_flags | VOLUME_सूचीTY);
पूर्ण

पूर्णांक exfat_clear_volume_dirty(काष्ठा super_block *sb)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	वापस exfat_set_vol_flags(sb, sbi->vol_flags & ~VOLUME_सूचीTY);
पूर्ण

अटल पूर्णांक exfat_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा super_block *sb = root->d_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_mount_options *opts = &sbi->options;

	/* Show partition info */
	अगर (!uid_eq(opts->fs_uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
				from_kuid_munged(&init_user_ns, opts->fs_uid));
	अगर (!gid_eq(opts->fs_gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
				from_kgid_munged(&init_user_ns, opts->fs_gid));
	seq_म_लिखो(m, ",fmask=%04o,dmask=%04o", opts->fs_fmask, opts->fs_dmask);
	अगर (opts->allow_uसमय)
		seq_म_लिखो(m, ",allow_utime=%04o", opts->allow_uसमय);
	अगर (opts->utf8)
		seq_माला_दो(m, ",iocharset=utf8");
	अन्यथा अगर (sbi->nls_io)
		seq_म_लिखो(m, ",iocharset=%s", sbi->nls_io->अक्षरset);
	अगर (opts->errors == EXFAT_ERRORS_CONT)
		seq_माला_दो(m, ",errors=continue");
	अन्यथा अगर (opts->errors == EXFAT_ERRORS_PANIC)
		seq_माला_दो(m, ",errors=panic");
	अन्यथा
		seq_माला_दो(m, ",errors=remount-ro");
	अगर (opts->discard)
		seq_माला_दो(m, ",discard");
	अगर (opts->समय_offset)
		seq_म_लिखो(m, ",time_offset=%d", opts->समय_offset);
	वापस 0;
पूर्ण

अटल काष्ठा inode *exfat_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा exfat_inode_info *ei;

	ei = kmem_cache_alloc(exfat_inode_cachep, GFP_NOFS);
	अगर (!ei)
		वापस शून्य;

	init_rwsem(&ei->truncate_lock);
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम exfat_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(exfat_inode_cachep, EXFAT_I(inode));
पूर्ण

अटल स्थिर काष्ठा super_operations exfat_sops = अणु
	.alloc_inode	= exfat_alloc_inode,
	.मुक्त_inode	= exfat_मुक्त_inode,
	.ग_लिखो_inode	= exfat_ग_लिखो_inode,
	.evict_inode	= exfat_evict_inode,
	.put_super	= exfat_put_super,
	.sync_fs	= exfat_sync_fs,
	.statfs		= exfat_statfs,
	.show_options	= exfat_show_options,
पूर्ण;

क्रमागत अणु
	Opt_uid,
	Opt_gid,
	Opt_umask,
	Opt_dmask,
	Opt_fmask,
	Opt_allow_uसमय,
	Opt_अक्षरset,
	Opt_errors,
	Opt_discard,
	Opt_समय_offset,

	/* Deprecated options */
	Opt_utf8,
	Opt_debug,
	Opt_nameहाल,
	Opt_codepage,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table exfat_param_क्रमागतs[] = अणु
	अणु "continue",		EXFAT_ERRORS_CONT पूर्ण,
	अणु "panic",		EXFAT_ERRORS_PANIC पूर्ण,
	अणु "remount-ro",		EXFAT_ERRORS_RO पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec exfat_parameters[] = अणु
	fsparam_u32("uid",			Opt_uid),
	fsparam_u32("gid",			Opt_gid),
	fsparam_u32oct("umask",			Opt_umask),
	fsparam_u32oct("dmask",			Opt_dmask),
	fsparam_u32oct("fmask",			Opt_fmask),
	fsparam_u32oct("allow_utime",		Opt_allow_uसमय),
	fsparam_string("iocharset",		Opt_अक्षरset),
	fsparam_क्रमागत("errors",			Opt_errors, exfat_param_क्रमागतs),
	fsparam_flag("discard",			Opt_discard),
	fsparam_s32("time_offset",		Opt_समय_offset),
	__fsparam(शून्य, "utf8",			Opt_utf8, fs_param_deprecated,
		  शून्य),
	__fsparam(शून्य, "debug",		Opt_debug, fs_param_deprecated,
		  शून्य),
	__fsparam(fs_param_is_u32, "namecase",	Opt_nameहाल,
		  fs_param_deprecated, शून्य),
	__fsparam(fs_param_is_u32, "codepage",	Opt_codepage,
		  fs_param_deprecated, शून्य),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक exfat_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा exfat_sb_info *sbi = fc->s_fs_info;
	काष्ठा exfat_mount_options *opts = &sbi->options;
	काष्ठा fs_parse_result result;
	पूर्णांक opt;

	opt = fs_parse(fc, exfat_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_uid:
		opts->fs_uid = make_kuid(current_user_ns(), result.uपूर्णांक_32);
		अवरोध;
	हाल Opt_gid:
		opts->fs_gid = make_kgid(current_user_ns(), result.uपूर्णांक_32);
		अवरोध;
	हाल Opt_umask:
		opts->fs_fmask = result.uपूर्णांक_32;
		opts->fs_dmask = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_dmask:
		opts->fs_dmask = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_fmask:
		opts->fs_fmask = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_allow_uसमय:
		opts->allow_uसमय = result.uपूर्णांक_32 & 0022;
		अवरोध;
	हाल Opt_अक्षरset:
		exfat_मुक्त_ioअक्षरset(sbi);
		opts->ioअक्षरset = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_errors:
		opts->errors = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_discard:
		opts->discard = 1;
		अवरोध;
	हाल Opt_समय_offset:
		/*
		 * Make the limit 24 just in हाल someone invents something
		 * unusual.
		 */
		अगर (result.पूर्णांक_32 < -24 * 60 || result.पूर्णांक_32 > 24 * 60)
			वापस -EINVAL;
		opts->समय_offset = result.पूर्णांक_32;
		अवरोध;
	हाल Opt_utf8:
	हाल Opt_debug:
	हाल Opt_nameहाल:
	हाल Opt_codepage:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exfat_hash_init(काष्ठा super_block *sb)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	पूर्णांक i;

	spin_lock_init(&sbi->inode_hash_lock);
	क्रम (i = 0; i < EXFAT_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&sbi->inode_hashtable[i]);
पूर्ण

अटल पूर्णांक exfat_पढ़ो_root(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा exfat_chain cdir;
	पूर्णांक num_subdirs, num_clu = 0;

	exfat_chain_set(&ei->dir, sbi->root_dir, 0, ALLOC_FAT_CHAIN);
	ei->entry = -1;
	ei->start_clu = sbi->root_dir;
	ei->flags = ALLOC_FAT_CHAIN;
	ei->type = TYPE_सूची;
	ei->version = 0;
	ei->hपूर्णांक_bmap.off = EXFAT_खातापूर्ण_CLUSTER;
	ei->hपूर्णांक_stat.eidx = 0;
	ei->hपूर्णांक_stat.clu = sbi->root_dir;
	ei->hपूर्णांक_femp.eidx = EXFAT_HINT_NONE;

	exfat_chain_set(&cdir, sbi->root_dir, 0, ALLOC_FAT_CHAIN);
	अगर (exfat_count_num_clusters(sb, &cdir, &num_clu))
		वापस -EIO;
	i_size_ग_लिखो(inode, num_clu << sbi->cluster_size_bits);

	num_subdirs = exfat_count_dir_entries(sb, &cdir);
	अगर (num_subdirs < 0)
		वापस -EIO;
	set_nlink(inode, num_subdirs + EXFAT_MIN_SUBसूची);

	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_iversion(inode);
	inode->i_generation = 0;
	inode->i_mode = exfat_make_mode(sbi, ATTR_SUBसूची, 0777);
	inode->i_op = &exfat_dir_inode_operations;
	inode->i_fop = &exfat_dir_operations;

	inode->i_blocks = ((i_size_पढ़ो(inode) + (sbi->cluster_size - 1))
			& ~(sbi->cluster_size - 1)) >> inode->i_blkbits;
	EXFAT_I(inode)->i_pos = ((loff_t)sbi->root_dir << 32) | 0xffffffff;
	EXFAT_I(inode)->i_size_aligned = i_size_पढ़ो(inode);
	EXFAT_I(inode)->i_size_ondisk = i_size_पढ़ो(inode);

	exfat_save_attr(inode, ATTR_SUBसूची);
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = ei->i_crसमय =
		current_समय(inode);
	exfat_truncate_aसमय(&inode->i_aसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_calibrate_blocksize(काष्ठा super_block *sb, पूर्णांक logical_sect)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	अगर (!is_घातer_of_2(logical_sect)) अणु
		exfat_err(sb, "bogus logical sector size %u", logical_sect);
		वापस -EIO;
	पूर्ण

	अगर (logical_sect < sb->s_blocksize) अणु
		exfat_err(sb, "logical sector size too small for device (logical sector size = %u)",
			  logical_sect);
		वापस -EIO;
	पूर्ण

	अगर (logical_sect > sb->s_blocksize) अणु
		brअन्यथा(sbi->boot_bh);
		sbi->boot_bh = शून्य;

		अगर (!sb_set_blocksize(sb, logical_sect)) अणु
			exfat_err(sb, "unable to set blocksize %u",
				  logical_sect);
			वापस -EIO;
		पूर्ण
		sbi->boot_bh = sb_bपढ़ो(sb, 0);
		अगर (!sbi->boot_bh) अणु
			exfat_err(sb, "unable to read boot sector (logical sector size = %lu)",
				  sb->s_blocksize);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_पढ़ो_boot_sector(काष्ठा super_block *sb)
अणु
	काष्ठा boot_sector *p_boot;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	/* set block size to पढ़ो super block */
	sb_min_blocksize(sb, 512);

	/* पढ़ो boot sector */
	sbi->boot_bh = sb_bपढ़ो(sb, 0);
	अगर (!sbi->boot_bh) अणु
		exfat_err(sb, "unable to read boot sector");
		वापस -EIO;
	पूर्ण
	p_boot = (काष्ठा boot_sector *)sbi->boot_bh->b_data;

	/* check the validity of BOOT */
	अगर (le16_to_cpu((p_boot->signature)) != BOOT_SIGNATURE) अणु
		exfat_err(sb, "invalid boot record signature");
		वापस -EINVAL;
	पूर्ण

	अगर (स_भेद(p_boot->fs_name, STR_EXFAT, BOOTSEC_FS_NAME_LEN)) अणु
		exfat_err(sb, "invalid fs_name"); /* fs_name may unprपूर्णांकable */
		वापस -EINVAL;
	पूर्ण

	/*
	 * must_be_zero field must be filled with zero to prevent mounting
	 * from FAT volume.
	 */
	अगर (स_प्रथम_inv(p_boot->must_be_zero, 0, माप(p_boot->must_be_zero)))
		वापस -EINVAL;

	अगर (p_boot->num_fats != 1 && p_boot->num_fats != 2) अणु
		exfat_err(sb, "bogus number of FAT structure");
		वापस -EINVAL;
	पूर्ण

	/*
	 * sect_size_bits could be at least 9 and at most 12.
	 */
	अगर (p_boot->sect_size_bits < EXFAT_MIN_SECT_SIZE_BITS ||
	    p_boot->sect_size_bits > EXFAT_MAX_SECT_SIZE_BITS) अणु
		exfat_err(sb, "bogus sector size bits : %u\n",
				p_boot->sect_size_bits);
		वापस -EINVAL;
	पूर्ण

	/*
	 * sect_per_clus_bits could be at least 0 and at most 25 - sect_size_bits.
	 */
	अगर (p_boot->sect_per_clus_bits > EXFAT_MAX_SECT_PER_CLUS_BITS(p_boot)) अणु
		exfat_err(sb, "bogus sectors bits per cluster : %u\n",
				p_boot->sect_per_clus_bits);
		वापस -EINVAL;
	पूर्ण

	sbi->sect_per_clus = 1 << p_boot->sect_per_clus_bits;
	sbi->sect_per_clus_bits = p_boot->sect_per_clus_bits;
	sbi->cluster_size_bits = p_boot->sect_per_clus_bits +
		p_boot->sect_size_bits;
	sbi->cluster_size = 1 << sbi->cluster_size_bits;
	sbi->num_FAT_sectors = le32_to_cpu(p_boot->fat_length);
	sbi->FAT1_start_sector = le32_to_cpu(p_boot->fat_offset);
	sbi->FAT2_start_sector = le32_to_cpu(p_boot->fat_offset);
	अगर (p_boot->num_fats == 2)
		sbi->FAT2_start_sector += sbi->num_FAT_sectors;
	sbi->data_start_sector = le32_to_cpu(p_boot->clu_offset);
	sbi->num_sectors = le64_to_cpu(p_boot->vol_length);
	/* because the cluster index starts with 2 */
	sbi->num_clusters = le32_to_cpu(p_boot->clu_count) +
		EXFAT_RESERVED_CLUSTERS;

	sbi->root_dir = le32_to_cpu(p_boot->root_cluster);
	sbi->dentries_per_clu = 1 <<
		(sbi->cluster_size_bits - DENTRY_SIZE_BITS);

	sbi->vol_flags = le16_to_cpu(p_boot->vol_flags);
	sbi->vol_flags_persistent = sbi->vol_flags & (VOLUME_सूचीTY | MEDIA_FAILURE);
	sbi->clu_srch_ptr = EXFAT_FIRST_CLUSTER;
	sbi->used_clusters = EXFAT_CLUSTERS_UNTRACKED;

	/* check consistencies */
	अगर ((u64)sbi->num_FAT_sectors << p_boot->sect_size_bits <
	    (u64)sbi->num_clusters * 4) अणु
		exfat_err(sb, "bogus fat length");
		वापस -EINVAL;
	पूर्ण

	अगर (sbi->data_start_sector <
	    (u64)sbi->FAT1_start_sector +
	    (u64)sbi->num_FAT_sectors * p_boot->num_fats) अणु
		exfat_err(sb, "bogus data start sector");
		वापस -EINVAL;
	पूर्ण

	अगर (sbi->vol_flags & VOLUME_सूचीTY)
		exfat_warn(sb, "Volume was not properly unmounted. Some data may be corrupt. Please run fsck.");
	अगर (sbi->vol_flags & MEDIA_FAILURE)
		exfat_warn(sb, "Medium has reported failures. Some data may be lost.");

	/* exFAT file size is limited by a disk volume size */
	sb->s_maxbytes = (u64)(sbi->num_clusters - EXFAT_RESERVED_CLUSTERS) <<
		sbi->cluster_size_bits;

	/* check logical sector size */
	अगर (exfat_calibrate_blocksize(sb, 1 << p_boot->sect_size_bits))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक exfat_verअगरy_boot_region(काष्ठा super_block *sb)
अणु
	काष्ठा buffer_head *bh = शून्य;
	u32 chksum = 0;
	__le32 *p_sig, *p_chksum;
	पूर्णांक sn, i;

	/* पढ़ो boot sector sub-regions */
	क्रम (sn = 0; sn < 11; sn++) अणु
		bh = sb_bपढ़ो(sb, sn);
		अगर (!bh)
			वापस -EIO;

		अगर (sn != 0 && sn <= 8) अणु
			/* extended boot sector sub-regions */
			p_sig = (__le32 *)&bh->b_data[sb->s_blocksize - 4];
			अगर (le32_to_cpu(*p_sig) != EXBOOT_SIGNATURE)
				exfat_warn(sb, "Invalid exboot-signature(sector = %d): 0x%08x",
					   sn, le32_to_cpu(*p_sig));
		पूर्ण

		chksum = exfat_calc_chksum32(bh->b_data, sb->s_blocksize,
			chksum, sn ? CS_DEFAULT : CS_BOOT_SECTOR);
		brअन्यथा(bh);
	पूर्ण

	/* boot checksum sub-regions */
	bh = sb_bपढ़ो(sb, sn);
	अगर (!bh)
		वापस -EIO;

	क्रम (i = 0; i < sb->s_blocksize; i += माप(u32)) अणु
		p_chksum = (__le32 *)&bh->b_data[i];
		अगर (le32_to_cpu(*p_chksum) != chksum) अणु
			exfat_err(sb, "Invalid boot checksum (boot checksum : 0x%08x, checksum : 0x%08x)",
				  le32_to_cpu(*p_chksum), chksum);
			brअन्यथा(bh);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	brअन्यथा(bh);
	वापस 0;
पूर्ण

/* mount the file प्रणाली volume */
अटल पूर्णांक __exfat_fill_super(काष्ठा super_block *sb)
अणु
	पूर्णांक ret;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	ret = exfat_पढ़ो_boot_sector(sb);
	अगर (ret) अणु
		exfat_err(sb, "failed to read boot sector");
		जाओ मुक्त_bh;
	पूर्ण

	ret = exfat_verअगरy_boot_region(sb);
	अगर (ret) अणु
		exfat_err(sb, "invalid boot region");
		जाओ मुक्त_bh;
	पूर्ण

	ret = exfat_create_upहाल_table(sb);
	अगर (ret) अणु
		exfat_err(sb, "failed to load upcase table");
		जाओ मुक्त_bh;
	पूर्ण

	ret = exfat_load_biपंचांगap(sb);
	अगर (ret) अणु
		exfat_err(sb, "failed to load alloc-bitmap");
		जाओ मुक्त_upहाल_table;
	पूर्ण

	ret = exfat_count_used_clusters(sb, &sbi->used_clusters);
	अगर (ret) अणु
		exfat_err(sb, "failed to scan clusters");
		जाओ मुक्त_alloc_biपंचांगap;
	पूर्ण

	वापस 0;

मुक्त_alloc_biपंचांगap:
	exfat_मुक्त_biपंचांगap(sbi);
मुक्त_upहाल_table:
	exfat_मुक्त_upहाल_table(sbi);
मुक्त_bh:
	brअन्यथा(sbi->boot_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक exfat_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा exfat_sb_info *sbi = sb->s_fs_info;
	काष्ठा exfat_mount_options *opts = &sbi->options;
	काष्ठा inode *root_inode;
	पूर्णांक err;

	अगर (opts->allow_uसमय == (अचिन्हित लघु)-1)
		opts->allow_uसमय = ~opts->fs_dmask & 0022;

	अगर (opts->discard) अणु
		काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);

		अगर (!blk_queue_discard(q)) अणु
			exfat_warn(sb, "mounting with \"discard\" option, but the device does not support discard");
			opts->discard = 0;
		पूर्ण
	पूर्ण

	sb->s_flags |= SB_NOसूचीATIME;
	sb->s_magic = EXFAT_SUPER_MAGIC;
	sb->s_op = &exfat_sops;

	sb->s_समय_gran = 10 * NSEC_PER_MSEC;
	sb->s_समय_min = EXFAT_MIN_TIMESTAMP_SECS;
	sb->s_समय_max = EXFAT_MAX_TIMESTAMP_SECS;

	err = __exfat_fill_super(sb);
	अगर (err) अणु
		exfat_err(sb, "failed to recognize exfat type");
		जाओ check_nls_io;
	पूर्ण

	/* set up enough so that it can पढ़ो an inode */
	exfat_hash_init(sb);

	अगर (!म_भेद(sbi->options.ioअक्षरset, "utf8"))
		opts->utf8 = 1;
	अन्यथा अणु
		sbi->nls_io = load_nls(sbi->options.ioअक्षरset);
		अगर (!sbi->nls_io) अणु
			exfat_err(sb, "IO charset %s not found",
				  sbi->options.ioअक्षरset);
			err = -EINVAL;
			जाओ मुक्त_table;
		पूर्ण
	पूर्ण

	अगर (sbi->options.utf8)
		sb->s_d_op = &exfat_utf8_dentry_ops;
	अन्यथा
		sb->s_d_op = &exfat_dentry_ops;

	root_inode = new_inode(sb);
	अगर (!root_inode) अणु
		exfat_err(sb, "failed to allocate root inode");
		err = -ENOMEM;
		जाओ मुक्त_table;
	पूर्ण

	root_inode->i_ino = EXFAT_ROOT_INO;
	inode_set_iversion(root_inode, 1);
	err = exfat_पढ़ो_root(root_inode);
	अगर (err) अणु
		exfat_err(sb, "failed to initialize root inode");
		जाओ put_inode;
	पूर्ण

	exfat_hash_inode(root_inode, EXFAT_I(root_inode)->i_pos);
	insert_inode_hash(root_inode);

	sb->s_root = d_make_root(root_inode);
	अगर (!sb->s_root) अणु
		exfat_err(sb, "failed to get the root dentry");
		err = -ENOMEM;
		जाओ put_inode;
	पूर्ण

	वापस 0;

put_inode:
	iput(root_inode);
	sb->s_root = शून्य;

मुक्त_table:
	exfat_मुक्त_upहाल_table(sbi);
	exfat_मुक्त_biपंचांगap(sbi);
	brअन्यथा(sbi->boot_bh);

check_nls_io:
	unload_nls(sbi->nls_io);
	exfat_मुक्त_ioअक्षरset(sbi);
	sb->s_fs_info = शून्य;
	kमुक्त(sbi);
	वापस err;
पूर्ण

अटल पूर्णांक exfat_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_bdev(fc, exfat_fill_super);
पूर्ण

अटल व्योम exfat_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा exfat_sb_info *sbi = fc->s_fs_info;

	अगर (sbi) अणु
		exfat_मुक्त_ioअक्षरset(sbi);
		kमुक्त(sbi);
	पूर्ण
पूर्ण

अटल पूर्णांक exfat_reconfigure(काष्ठा fs_context *fc)
अणु
	fc->sb_flags |= SB_NOसूचीATIME;

	/* volume flag will be updated in exfat_sync_fs */
	sync_fileप्रणाली(fc->root->d_sb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations exfat_context_ops = अणु
	.parse_param	= exfat_parse_param,
	.get_tree	= exfat_get_tree,
	.मुक्त		= exfat_मुक्त,
	.reconfigure	= exfat_reconfigure,
पूर्ण;

अटल पूर्णांक exfat_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा exfat_sb_info *sbi;

	sbi = kzalloc(माप(काष्ठा exfat_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	mutex_init(&sbi->s_lock);
	mutex_init(&sbi->biपंचांगap_lock);
	ratelimit_state_init(&sbi->ratelimit, DEFAULT_RATELIMIT_INTERVAL,
			DEFAULT_RATELIMIT_BURST);

	sbi->options.fs_uid = current_uid();
	sbi->options.fs_gid = current_gid();
	sbi->options.fs_fmask = current->fs->umask;
	sbi->options.fs_dmask = current->fs->umask;
	sbi->options.allow_uसमय = -1;
	sbi->options.ioअक्षरset = exfat_शेष_ioअक्षरset;
	sbi->options.errors = EXFAT_ERRORS_RO;

	fc->s_fs_info = sbi;
	fc->ops = &exfat_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type exfat_fs_type = अणु
	.owner			= THIS_MODULE,
	.name			= "exfat",
	.init_fs_context	= exfat_init_fs_context,
	.parameters		= exfat_parameters,
	.समाप्त_sb		= समाप्त_block_super,
	.fs_flags		= FS_REQUIRES_DEV,
पूर्ण;

अटल व्योम exfat_inode_init_once(व्योम *foo)
अणु
	काष्ठा exfat_inode_info *ei = (काष्ठा exfat_inode_info *)foo;

	spin_lock_init(&ei->cache_lru_lock);
	ei->nr_caches = 0;
	ei->cache_valid_id = EXFAT_CACHE_VALID + 1;
	INIT_LIST_HEAD(&ei->cache_lru);
	INIT_HLIST_NODE(&ei->i_hash_fat);
	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_exfat_fs(व्योम)
अणु
	पूर्णांक err;

	err = exfat_cache_init();
	अगर (err)
		वापस err;

	exfat_inode_cachep = kmem_cache_create("exfat_inode_cache",
			माप(काष्ठा exfat_inode_info),
			0, SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD,
			exfat_inode_init_once);
	अगर (!exfat_inode_cachep) अणु
		err = -ENOMEM;
		जाओ shutकरोwn_cache;
	पूर्ण

	err = रेजिस्टर_fileप्रणाली(&exfat_fs_type);
	अगर (err)
		जाओ destroy_cache;

	वापस 0;

destroy_cache:
	kmem_cache_destroy(exfat_inode_cachep);
shutकरोwn_cache:
	exfat_cache_shutकरोwn();
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_exfat_fs(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(exfat_inode_cachep);
	unरेजिस्टर_fileप्रणाली(&exfat_fs_type);
	exfat_cache_shutकरोwn();
पूर्ण

module_init(init_exfat_fs);
module_निकास(निकास_exfat_fs);

MODULE_ALIAS_FS("exfat");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("exFAT filesystem support");
MODULE_AUTHOR("Samsung Electronics Co., Ltd.");
