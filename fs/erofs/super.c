<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/statfs.h>
#समावेश <linux/parser.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश "xattr.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/erofs.h>

अटल काष्ठा kmem_cache *erofs_inode_cachep __पढ़ो_mostly;

व्योम _erofs_err(काष्ठा super_block *sb, स्थिर अक्षर *function,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_err("(device %s): %s: %pV", sb->s_id, function, &vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम _erofs_info(काष्ठा super_block *sb, स्थिर अक्षर *function,
		 स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_info("(device %s): %pV", sb->s_id, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक erofs_superblock_csum_verअगरy(काष्ठा super_block *sb, व्योम *sbdata)
अणु
	काष्ठा erofs_super_block *dsb;
	u32 expected_crc, crc;

	dsb = kmemdup(sbdata + EROFS_SUPER_OFFSET,
		      EROFS_BLKSIZ - EROFS_SUPER_OFFSET, GFP_KERNEL);
	अगर (!dsb)
		वापस -ENOMEM;

	expected_crc = le32_to_cpu(dsb->checksum);
	dsb->checksum = 0;
	/* to allow क्रम x86 boot sectors and other oddities. */
	crc = crc32c(~0, dsb, EROFS_BLKSIZ - EROFS_SUPER_OFFSET);
	kमुक्त(dsb);

	अगर (crc != expected_crc) अणु
		erofs_err(sb, "invalid checksum 0x%08x, 0x%08x expected",
			  crc, expected_crc);
		वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम erofs_inode_init_once(व्योम *ptr)
अणु
	काष्ठा erofs_inode *vi = ptr;

	inode_init_once(&vi->vfs_inode);
पूर्ण

अटल काष्ठा inode *erofs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा erofs_inode *vi =
		kmem_cache_alloc(erofs_inode_cachep, GFP_KERNEL);

	अगर (!vi)
		वापस शून्य;

	/* zero out everything except vfs_inode */
	स_रखो(vi, 0, दुरत्व(काष्ठा erofs_inode, vfs_inode));
	वापस &vi->vfs_inode;
पूर्ण

अटल व्योम erofs_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा erofs_inode *vi = EROFS_I(inode);

	/* be careful of RCU symlink path */
	अगर (inode->i_op == &erofs_fast_symlink_iops)
		kमुक्त(inode->i_link);
	kमुक्त(vi->xattr_shared_xattrs);

	kmem_cache_मुक्त(erofs_inode_cachep, vi);
पूर्ण

अटल bool check_layout_compatibility(काष्ठा super_block *sb,
				       काष्ठा erofs_super_block *dsb)
अणु
	स्थिर अचिन्हित पूर्णांक feature = le32_to_cpu(dsb->feature_incompat);

	EROFS_SB(sb)->feature_incompat = feature;

	/* check अगर current kernel meets all mandatory requirements */
	अगर (feature & (~EROFS_ALL_FEATURE_INCOMPAT)) अणु
		erofs_err(sb,
			  "unidentified incompatible feature %x, please upgrade kernel version",
			   feature & ~EROFS_ALL_FEATURE_INCOMPAT);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_EROFS_FS_ZIP
/* पढ़ो variable-sized metadata, offset will be aligned by 4-byte */
अटल व्योम *erofs_पढ़ो_metadata(काष्ठा super_block *sb, काष्ठा page **pagep,
				 erofs_off_t *offset, पूर्णांक *lengthp)
अणु
	काष्ठा page *page = *pagep;
	u8 *buffer, *ptr;
	पूर्णांक len, i, cnt;
	erofs_blk_t blk;

	*offset = round_up(*offset, 4);
	blk = erofs_blknr(*offset);

	अगर (!page || page->index != blk) अणु
		अगर (page) अणु
			unlock_page(page);
			put_page(page);
		पूर्ण
		page = erofs_get_meta_page(sb, blk);
		अगर (IS_ERR(page))
			जाओ err_nullpage;
	पूर्ण

	ptr = kmap(page);
	len = le16_to_cpu(*(__le16 *)&ptr[erofs_blkoff(*offset)]);
	अगर (!len)
		len = U16_MAX + 1;
	buffer = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buffer) अणु
		buffer = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	*offset += माप(__le16);
	*lengthp = len;

	क्रम (i = 0; i < len; i += cnt) अणु
		cnt = min(EROFS_BLKSIZ - (पूर्णांक)erofs_blkoff(*offset), len - i);
		blk = erofs_blknr(*offset);

		अगर (!page || page->index != blk) अणु
			अगर (page) अणु
				kunmap(page);
				unlock_page(page);
				put_page(page);
			पूर्ण
			page = erofs_get_meta_page(sb, blk);
			अगर (IS_ERR(page)) अणु
				kमुक्त(buffer);
				जाओ err_nullpage;
			पूर्ण
			ptr = kmap(page);
		पूर्ण
		स_नकल(buffer + i, ptr + erofs_blkoff(*offset), cnt);
		*offset += cnt;
	पूर्ण
out:
	kunmap(page);
	*pagep = page;
	वापस buffer;
err_nullpage:
	*pagep = शून्य;
	वापस page;
पूर्ण

अटल पूर्णांक erofs_load_compr_cfgs(काष्ठा super_block *sb,
				 काष्ठा erofs_super_block *dsb)
अणु
	काष्ठा erofs_sb_info *sbi;
	काष्ठा page *page;
	अचिन्हित पूर्णांक algs, alg;
	erofs_off_t offset;
	पूर्णांक size, ret;

	sbi = EROFS_SB(sb);
	sbi->available_compr_algs = le16_to_cpu(dsb->u1.available_compr_algs);

	अगर (sbi->available_compr_algs & ~Z_EROFS_ALL_COMPR_ALGS) अणु
		erofs_err(sb, "try to load compressed fs with unsupported algorithms %x",
			  sbi->available_compr_algs & ~Z_EROFS_ALL_COMPR_ALGS);
		वापस -EINVAL;
	पूर्ण

	offset = EROFS_SUPER_OFFSET + sbi->sb_size;
	page = शून्य;
	alg = 0;
	ret = 0;

	क्रम (algs = sbi->available_compr_algs; algs; algs >>= 1, ++alg) अणु
		व्योम *data;

		अगर (!(algs & 1))
			जारी;

		data = erofs_पढ़ो_metadata(sb, &page, &offset, &size);
		अगर (IS_ERR(data)) अणु
			ret = PTR_ERR(data);
			जाओ err;
		पूर्ण

		चयन (alg) अणु
		हाल Z_EROFS_COMPRESSION_LZ4:
			ret = z_erofs_load_lz4_config(sb, dsb, data, size);
			अवरोध;
		शेष:
			DBG_BUGON(1);
			ret = -EFAULT;
		पूर्ण
		kमुक्त(data);
		अगर (ret)
			जाओ err;
	पूर्ण
err:
	अगर (page) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक erofs_load_compr_cfgs(काष्ठा super_block *sb,
				 काष्ठा erofs_super_block *dsb)
अणु
	अगर (dsb->u1.available_compr_algs) अणु
		erofs_err(sb, "try to load compressed fs when compression is disabled");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक erofs_पढ़ो_superblock(काष्ठा super_block *sb)
अणु
	काष्ठा erofs_sb_info *sbi;
	काष्ठा page *page;
	काष्ठा erofs_super_block *dsb;
	अचिन्हित पूर्णांक blkszbits;
	व्योम *data;
	पूर्णांक ret;

	page = पढ़ो_mapping_page(sb->s_bdev->bd_inode->i_mapping, 0, शून्य);
	अगर (IS_ERR(page)) अणु
		erofs_err(sb, "cannot read erofs superblock");
		वापस PTR_ERR(page);
	पूर्ण

	sbi = EROFS_SB(sb);

	data = kmap(page);
	dsb = (काष्ठा erofs_super_block *)(data + EROFS_SUPER_OFFSET);

	ret = -EINVAL;
	अगर (le32_to_cpu(dsb->magic) != EROFS_SUPER_MAGIC_V1) अणु
		erofs_err(sb, "cannot find valid erofs superblock");
		जाओ out;
	पूर्ण

	sbi->feature_compat = le32_to_cpu(dsb->feature_compat);
	अगर (erofs_sb_has_sb_chksum(sbi)) अणु
		ret = erofs_superblock_csum_verअगरy(sb, data);
		अगर (ret)
			जाओ out;
	पूर्ण

	blkszbits = dsb->blkszbits;
	/* 9(512 bytes) + LOG_SECTORS_PER_BLOCK == LOG_BLOCK_SIZE */
	अगर (blkszbits != LOG_BLOCK_SIZE) अणु
		erofs_err(sb, "blkszbits %u isn't supported on this platform",
			  blkszbits);
		जाओ out;
	पूर्ण

	अगर (!check_layout_compatibility(sb, dsb))
		जाओ out;

	sbi->sb_size = 128 + dsb->sb_extslots * EROFS_SB_EXTSLOT_SIZE;
	अगर (sbi->sb_size > EROFS_BLKSIZ) अणु
		erofs_err(sb, "invalid sb_extslots %u (more than a fs block)",
			  sbi->sb_size);
		जाओ out;
	पूर्ण
	sbi->blocks = le32_to_cpu(dsb->blocks);
	sbi->meta_blkaddr = le32_to_cpu(dsb->meta_blkaddr);
#अगर_घोषित CONFIG_EROFS_FS_XATTR
	sbi->xattr_blkaddr = le32_to_cpu(dsb->xattr_blkaddr);
#पूर्ण_अगर
	sbi->islotbits = ilog2(माप(काष्ठा erofs_inode_compact));
	sbi->root_nid = le16_to_cpu(dsb->root_nid);
	sbi->inos = le64_to_cpu(dsb->inos);

	sbi->build_समय = le64_to_cpu(dsb->build_समय);
	sbi->build_समय_nsec = le32_to_cpu(dsb->build_समय_nsec);

	स_नकल(&sb->s_uuid, dsb->uuid, माप(dsb->uuid));

	ret = strscpy(sbi->volume_name, dsb->volume_name,
		      माप(dsb->volume_name));
	अगर (ret < 0) अणु	/* -E2BIG */
		erofs_err(sb, "bad volume name without NIL terminator");
		ret = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	/* parse on-disk compression configurations */
	अगर (erofs_sb_has_compr_cfgs(sbi))
		ret = erofs_load_compr_cfgs(sb, dsb);
	अन्यथा
		ret = z_erofs_load_lz4_config(sb, dsb, शून्य, 0);
out:
	kunmap(page);
	put_page(page);
	वापस ret;
पूर्ण

/* set up शेष EROFS parameters */
अटल व्योम erofs_शेष_options(काष्ठा erofs_fs_context *ctx)
अणु
#अगर_घोषित CONFIG_EROFS_FS_ZIP
	ctx->cache_strategy = EROFS_ZIP_CACHE_READAROUND;
	ctx->max_sync_decompress_pages = 3;
	ctx->पढ़ोahead_sync_decompress = false;
#पूर्ण_अगर
#अगर_घोषित CONFIG_EROFS_FS_XATTR
	set_opt(ctx, XATTR_USER);
#पूर्ण_अगर
#अगर_घोषित CONFIG_EROFS_FS_POSIX_ACL
	set_opt(ctx, POSIX_ACL);
#पूर्ण_अगर
पूर्ण

क्रमागत अणु
	Opt_user_xattr,
	Opt_acl,
	Opt_cache_strategy,
	Opt_err
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table erofs_param_cache_strategy[] = अणु
	अणु"disabled",	EROFS_ZIP_CACHE_DISABLEDपूर्ण,
	अणु"readahead",	EROFS_ZIP_CACHE_READAHEADपूर्ण,
	अणु"readaround",	EROFS_ZIP_CACHE_READAROUNDपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec erofs_fs_parameters[] = अणु
	fsparam_flag_no("user_xattr",	Opt_user_xattr),
	fsparam_flag_no("acl",		Opt_acl),
	fsparam_क्रमागत("cache_strategy",	Opt_cache_strategy,
		     erofs_param_cache_strategy),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक erofs_fc_parse_param(काष्ठा fs_context *fc,
				काष्ठा fs_parameter *param)
अणु
	काष्ठा erofs_fs_context *ctx __maybe_unused = fc->fs_निजी;
	काष्ठा fs_parse_result result;
	पूर्णांक opt;

	opt = fs_parse(fc, erofs_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_user_xattr:
#अगर_घोषित CONFIG_EROFS_FS_XATTR
		अगर (result.boolean)
			set_opt(ctx, XATTR_USER);
		अन्यथा
			clear_opt(ctx, XATTR_USER);
#अन्यथा
		errorfc(fc, "{,no}user_xattr options not supported");
#पूर्ण_अगर
		अवरोध;
	हाल Opt_acl:
#अगर_घोषित CONFIG_EROFS_FS_POSIX_ACL
		अगर (result.boolean)
			set_opt(ctx, POSIX_ACL);
		अन्यथा
			clear_opt(ctx, POSIX_ACL);
#अन्यथा
		errorfc(fc, "{,no}acl options not supported");
#पूर्ण_अगर
		अवरोध;
	हाल Opt_cache_strategy:
#अगर_घोषित CONFIG_EROFS_FS_ZIP
		ctx->cache_strategy = result.uपूर्णांक_32;
#अन्यथा
		errorfc(fc, "compression not supported, cache_strategy ignored");
#पूर्ण_अगर
		अवरोध;
	शेष:
		वापस -ENOPARAM;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_EROFS_FS_ZIP
अटल स्थिर काष्ठा address_space_operations managed_cache_aops;

अटल पूर्णांक erofs_managed_cache_releasepage(काष्ठा page *page, gfp_t gfp_mask)
अणु
	पूर्णांक ret = 1;	/* 0 - busy */
	काष्ठा address_space *स्थिर mapping = page->mapping;

	DBG_BUGON(!PageLocked(page));
	DBG_BUGON(mapping->a_ops != &managed_cache_aops);

	अगर (PagePrivate(page))
		ret = erofs_try_to_मुक्त_cached_page(mapping, page);

	वापस ret;
पूर्ण

अटल व्योम erofs_managed_cache_invalidatepage(काष्ठा page *page,
					       अचिन्हित पूर्णांक offset,
					       अचिन्हित पूर्णांक length)
अणु
	स्थिर अचिन्हित पूर्णांक stop = length + offset;

	DBG_BUGON(!PageLocked(page));

	/* Check क्रम potential overflow in debug mode */
	DBG_BUGON(stop > PAGE_SIZE || stop < length);

	अगर (offset == 0 && stop == PAGE_SIZE)
		जबतक (!erofs_managed_cache_releasepage(page, GFP_NOFS))
			cond_resched();
पूर्ण

अटल स्थिर काष्ठा address_space_operations managed_cache_aops = अणु
	.releasepage = erofs_managed_cache_releasepage,
	.invalidatepage = erofs_managed_cache_invalidatepage,
पूर्ण;

अटल पूर्णांक erofs_init_managed_cache(काष्ठा super_block *sb)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);
	काष्ठा inode *स्थिर inode = new_inode(sb);

	अगर (!inode)
		वापस -ENOMEM;

	set_nlink(inode, 1);
	inode->i_size = OFFSET_MAX;

	inode->i_mapping->a_ops = &managed_cache_aops;
	mapping_set_gfp_mask(inode->i_mapping,
			     GFP_NOFS | __GFP_HIGHMEM | __GFP_MOVABLE);
	sbi->managed_cache = inode;
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक erofs_init_managed_cache(काष्ठा super_block *sb) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक erofs_fc_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा inode *inode;
	काष्ठा erofs_sb_info *sbi;
	काष्ठा erofs_fs_context *ctx = fc->fs_निजी;
	पूर्णांक err;

	sb->s_magic = EROFS_SUPER_MAGIC;

	अगर (!sb_set_blocksize(sb, EROFS_BLKSIZ)) अणु
		erofs_err(sb, "failed to set erofs blksize");
		वापस -EINVAL;
	पूर्ण

	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sb->s_fs_info = sbi;
	err = erofs_पढ़ो_superblock(sb);
	अगर (err)
		वापस err;

	sb->s_flags |= SB_RDONLY | SB_NOATIME;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_समय_gran = 1;

	sb->s_op = &erofs_sops;
	sb->s_xattr = erofs_xattr_handlers;

	अगर (test_opt(ctx, POSIX_ACL))
		sb->s_flags |= SB_POSIXACL;
	अन्यथा
		sb->s_flags &= ~SB_POSIXACL;

	sbi->ctx = *ctx;

#अगर_घोषित CONFIG_EROFS_FS_ZIP
	xa_init(&sbi->managed_pslots);
#पूर्ण_अगर

	/* get the root inode */
	inode = erofs_iget(sb, ROOT_NID(sbi), true);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	अगर (!S_ISसूची(inode->i_mode)) अणु
		erofs_err(sb, "rootino(nid %llu) is not a directory(i_mode %o)",
			  ROOT_NID(sbi), inode->i_mode);
		iput(inode);
		वापस -EINVAL;
	पूर्ण

	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		वापस -ENOMEM;

	erofs_shrinker_रेजिस्टर(sb);
	/* sb->s_umount is alपढ़ोy locked, SB_ACTIVE and SB_BORN are not set */
	err = erofs_init_managed_cache(sb);
	अगर (err)
		वापस err;

	erofs_info(sb, "mounted with root inode @ nid %llu.", ROOT_NID(sbi));
	वापस 0;
पूर्ण

अटल पूर्णांक erofs_fc_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_bdev(fc, erofs_fc_fill_super);
पूर्ण

अटल पूर्णांक erofs_fc_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb = fc->root->d_sb;
	काष्ठा erofs_sb_info *sbi = EROFS_SB(sb);
	काष्ठा erofs_fs_context *ctx = fc->fs_निजी;

	DBG_BUGON(!sb_rकरोnly(sb));

	अगर (test_opt(ctx, POSIX_ACL))
		fc->sb_flags |= SB_POSIXACL;
	अन्यथा
		fc->sb_flags &= ~SB_POSIXACL;

	sbi->ctx = *ctx;

	fc->sb_flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल व्योम erofs_fc_मुक्त(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->fs_निजी);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations erofs_context_ops = अणु
	.parse_param	= erofs_fc_parse_param,
	.get_tree       = erofs_fc_get_tree,
	.reconfigure    = erofs_fc_reconfigure,
	.मुक्त		= erofs_fc_मुक्त,
पूर्ण;

अटल पूर्णांक erofs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->fs_निजी = kzalloc(माप(काष्ठा erofs_fs_context), GFP_KERNEL);
	अगर (!fc->fs_निजी)
		वापस -ENOMEM;

	/* set शेष mount options */
	erofs_शेष_options(fc->fs_निजी);

	fc->ops = &erofs_context_ops;

	वापस 0;
पूर्ण

/*
 * could be triggered after deactivate_locked_super()
 * is called, thus including umount and failed to initialize.
 */
अटल व्योम erofs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा erofs_sb_info *sbi;

	WARN_ON(sb->s_magic != EROFS_SUPER_MAGIC);

	समाप्त_block_super(sb);

	sbi = EROFS_SB(sb);
	अगर (!sbi)
		वापस;
	kमुक्त(sbi);
	sb->s_fs_info = शून्य;
पूर्ण

/* called when ->s_root is non-शून्य */
अटल व्योम erofs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);

	DBG_BUGON(!sbi);

	erofs_shrinker_unरेजिस्टर(sb);
#अगर_घोषित CONFIG_EROFS_FS_ZIP
	iput(sbi->managed_cache);
	sbi->managed_cache = शून्य;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा file_प्रणाली_type erofs_fs_type = अणु
	.owner          = THIS_MODULE,
	.name           = "erofs",
	.init_fs_context = erofs_init_fs_context,
	.समाप्त_sb        = erofs_समाप्त_sb,
	.fs_flags       = FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("erofs");

अटल पूर्णांक __init erofs_module_init(व्योम)
अणु
	पूर्णांक err;

	erofs_check_ondisk_layout_definitions();

	erofs_inode_cachep = kmem_cache_create("erofs_inode",
					       माप(काष्ठा erofs_inode), 0,
					       SLAB_RECLAIM_ACCOUNT,
					       erofs_inode_init_once);
	अगर (!erofs_inode_cachep) अणु
		err = -ENOMEM;
		जाओ icache_err;
	पूर्ण

	err = erofs_init_shrinker();
	अगर (err)
		जाओ shrinker_err;

	erofs_pcpubuf_init();
	err = z_erofs_init_zip_subप्रणाली();
	अगर (err)
		जाओ zip_err;

	err = रेजिस्टर_fileप्रणाली(&erofs_fs_type);
	अगर (err)
		जाओ fs_err;

	वापस 0;

fs_err:
	z_erofs_निकास_zip_subप्रणाली();
zip_err:
	erofs_निकास_shrinker();
shrinker_err:
	kmem_cache_destroy(erofs_inode_cachep);
icache_err:
	वापस err;
पूर्ण

अटल व्योम __निकास erofs_module_निकास(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&erofs_fs_type);
	z_erofs_निकास_zip_subप्रणाली();
	erofs_निकास_shrinker();

	/* Ensure all RCU मुक्त inodes are safe beक्रमe cache is destroyed. */
	rcu_barrier();
	kmem_cache_destroy(erofs_inode_cachep);
	erofs_pcpubuf_निकास();
पूर्ण

/* get fileप्रणाली statistics */
अटल पूर्णांक erofs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा erofs_sb_info *sbi = EROFS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = sb->s_magic;
	buf->f_bsize = EROFS_BLKSIZ;
	buf->f_blocks = sbi->blocks;
	buf->f_bमुक्त = buf->f_bavail = 0;

	buf->f_files = ULदीर्घ_उच्च;
	buf->f_fमुक्त = ULदीर्घ_उच्च - sbi->inos;

	buf->f_namelen = EROFS_NAME_LEN;

	buf->f_fsid    = u64_to_fsid(id);
	वापस 0;
पूर्ण

अटल पूर्णांक erofs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा erofs_sb_info *sbi __maybe_unused = EROFS_SB(root->d_sb);
	काष्ठा erofs_fs_context *ctx __maybe_unused = &sbi->ctx;

#अगर_घोषित CONFIG_EROFS_FS_XATTR
	अगर (test_opt(ctx, XATTR_USER))
		seq_माला_दो(seq, ",user_xattr");
	अन्यथा
		seq_माला_दो(seq, ",nouser_xattr");
#पूर्ण_अगर
#अगर_घोषित CONFIG_EROFS_FS_POSIX_ACL
	अगर (test_opt(ctx, POSIX_ACL))
		seq_माला_दो(seq, ",acl");
	अन्यथा
		seq_माला_दो(seq, ",noacl");
#पूर्ण_अगर
#अगर_घोषित CONFIG_EROFS_FS_ZIP
	अगर (ctx->cache_strategy == EROFS_ZIP_CACHE_DISABLED)
		seq_माला_दो(seq, ",cache_strategy=disabled");
	अन्यथा अगर (ctx->cache_strategy == EROFS_ZIP_CACHE_READAHEAD)
		seq_माला_दो(seq, ",cache_strategy=readahead");
	अन्यथा अगर (ctx->cache_strategy == EROFS_ZIP_CACHE_READAROUND)
		seq_माला_दो(seq, ",cache_strategy=readaround");
#पूर्ण_अगर
	वापस 0;
पूर्ण

स्थिर काष्ठा super_operations erofs_sops = अणु
	.put_super = erofs_put_super,
	.alloc_inode = erofs_alloc_inode,
	.मुक्त_inode = erofs_मुक्त_inode,
	.statfs = erofs_statfs,
	.show_options = erofs_show_options,
पूर्ण;

module_init(erofs_module_init);
module_निकास(erofs_module_निकास);

MODULE_DESCRIPTION("Enhanced ROM File System");
MODULE_AUTHOR("Gao Xiang, Chao Yu, Miao Xie, CONSUMER BG, HUAWEI Inc.");
MODULE_LICENSE("GPL");

