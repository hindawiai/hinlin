<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/dir.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/dir.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext4 directory handling functions
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 *
 * Hash Tree Directory indexing (c) 2001  Daniel Phillips
 *
 */

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/iversion.h>
#समावेश <linux/unicode.h>
#समावेश "ext4.h"
#समावेश "xattr.h"

अटल पूर्णांक ext4_dx_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);

/**
 * is_dx_dir() - check अगर a directory is using htree indexing
 * @inode: directory inode
 *
 * Check अगर the given dir-inode refers to an htree-indexed directory
 * (or a directory which could potentially get converted to use htree
 * indexing).
 *
 * Return 1 अगर it is a dx dir, 0 अगर not
 */
अटल पूर्णांक is_dx_dir(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	अगर (ext4_has_feature_dir_index(inode->i_sb) &&
	    ((ext4_test_inode_flag(inode, EXT4_INODE_INDEX)) ||
	     ((inode->i_size >> sb->s_blocksize_bits) == 1) ||
	     ext4_has_अंतरभूत_data(inode)))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool is_fake_dir_entry(काष्ठा ext4_dir_entry_2 *de)
अणु
	/* Check अगर . or .. , or skip अगर namelen is 0 */
	अगर ((de->name_len > 0) && (de->name_len <= 2) && (de->name[0] == '.') &&
	    (de->name[1] == '.' || de->name[1] == '\0'))
		वापस true;
	/* Check अगर this is a csum entry */
	अगर (de->file_type == EXT4_FT_सूची_CSUM)
		वापस true;
	वापस false;
पूर्ण

/*
 * Return 0 अगर the directory entry is OK, and 1 अगर there is a problem
 *
 * Note: this is the opposite of what ext2 and ext3 historically वापसed...
 *
 * bh passed here can be an inode block or a dir data block, depending
 * on the inode अंतरभूत data flag.
 */
पूर्णांक __ext4_check_dir_entry(स्थिर अक्षर *function, अचिन्हित पूर्णांक line,
			   काष्ठा inode *dir, काष्ठा file *filp,
			   काष्ठा ext4_dir_entry_2 *de,
			   काष्ठा buffer_head *bh, अक्षर *buf, पूर्णांक size,
			   अचिन्हित पूर्णांक offset)
अणु
	स्थिर अक्षर *error_msg = शून्य;
	स्थिर पूर्णांक rlen = ext4_rec_len_from_disk(de->rec_len,
						dir->i_sb->s_blocksize);
	स्थिर पूर्णांक next_offset = ((अक्षर *) de - buf) + rlen;
	bool fake = is_fake_dir_entry(de);
	bool has_csum = ext4_has_metadata_csum(dir->i_sb);

	अगर (unlikely(rlen < ext4_dir_rec_len(1, fake ? शून्य : dir)))
		error_msg = "rec_len is smaller than minimal";
	अन्यथा अगर (unlikely(rlen % 4 != 0))
		error_msg = "rec_len % 4 != 0";
	अन्यथा अगर (unlikely(rlen < ext4_dir_rec_len(de->name_len,
							fake ? शून्य : dir)))
		error_msg = "rec_len is too small for name_len";
	अन्यथा अगर (unlikely(next_offset > size))
		error_msg = "directory entry overrun";
	अन्यथा अगर (unlikely(next_offset > size - ext4_dir_rec_len(1,
						  has_csum ? शून्य : dir) &&
			  next_offset != size))
		error_msg = "directory entry too close to block end";
	अन्यथा अगर (unlikely(le32_to_cpu(de->inode) >
			le32_to_cpu(EXT4_SB(dir->i_sb)->s_es->s_inodes_count)))
		error_msg = "inode out of bounds";
	अन्यथा
		वापस 0;

	अगर (filp)
		ext4_error_file(filp, function, line, bh->b_blocknr,
				"bad entry in directory: %s - offset=%u, "
				"inode=%u, rec_len=%d, size=%d fake=%d",
				error_msg, offset, le32_to_cpu(de->inode),
				rlen, size, fake);
	अन्यथा
		ext4_error_inode(dir, function, line, bh->b_blocknr,
				"bad entry in directory: %s - offset=%u, "
				"inode=%u, rec_len=%d, size=%d fake=%d",
				 error_msg, offset, le32_to_cpu(de->inode),
				 rlen, size, fake);

	वापस 1;
पूर्ण

अटल पूर्णांक ext4_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	अचिन्हित पूर्णांक offset;
	पूर्णांक i;
	काष्ठा ext4_dir_entry_2 *de;
	पूर्णांक err;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा fscrypt_str fstr = FSTR_INIT(शून्य, 0);

	err = fscrypt_prepare_सूची_पढ़ो(inode);
	अगर (err)
		वापस err;

	अगर (is_dx_dir(inode)) अणु
		err = ext4_dx_सूची_पढ़ो(file, ctx);
		अगर (err != ERR_BAD_DX_सूची)
			वापस err;

		/* Can we just clear INDEX flag to ignore htree inक्रमmation? */
		अगर (!ext4_has_metadata_csum(sb)) अणु
			/*
			 * We करोn't set the inode dirty flag since it's not
			 * critical that it माला_लो flushed back to the disk.
			 */
			ext4_clear_inode_flag(inode, EXT4_INODE_INDEX);
		पूर्ण
	पूर्ण

	अगर (ext4_has_अंतरभूत_data(inode)) अणु
		पूर्णांक has_अंतरभूत_data = 1;
		err = ext4_पढ़ो_अंतरभूत_dir(file, ctx,
					   &has_अंतरभूत_data);
		अगर (has_अंतरभूत_data)
			वापस err;
	पूर्ण

	अगर (IS_ENCRYPTED(inode)) अणु
		err = fscrypt_fname_alloc_buffer(EXT4_NAME_LEN, &fstr);
		अगर (err < 0)
			वापस err;
	पूर्ण

	जबतक (ctx->pos < inode->i_size) अणु
		काष्ठा ext4_map_blocks map;

		अगर (fatal_संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ errout;
		पूर्ण
		cond_resched();
		offset = ctx->pos & (sb->s_blocksize - 1);
		map.m_lblk = ctx->pos >> EXT4_BLOCK_SIZE_BITS(sb);
		map.m_len = 1;
		err = ext4_map_blocks(शून्य, inode, &map, 0);
		अगर (err == 0) अणु
			/* m_len should never be zero but let's aव्योम
			 * an infinite loop अगर it somehow is */
			अगर (map.m_len == 0)
				map.m_len = 1;
			ctx->pos += map.m_len * sb->s_blocksize;
			जारी;
		पूर्ण
		अगर (err > 0) अणु
			pgoff_t index = map.m_pblk >>
					(PAGE_SHIFT - inode->i_blkbits);
			अगर (!ra_has_index(&file->f_ra, index))
				page_cache_sync_पढ़ोahead(
					sb->s_bdev->bd_inode->i_mapping,
					&file->f_ra, file,
					index, 1);
			file->f_ra.prev_pos = (loff_t)index << PAGE_SHIFT;
			bh = ext4_bपढ़ो(शून्य, inode, map.m_lblk, 0);
			अगर (IS_ERR(bh)) अणु
				err = PTR_ERR(bh);
				bh = शून्य;
				जाओ errout;
			पूर्ण
		पूर्ण

		अगर (!bh) अणु
			/* corrupt size?  Maybe no more blocks to पढ़ो */
			अगर (ctx->pos > inode->i_blocks << 9)
				अवरोध;
			ctx->pos += sb->s_blocksize - offset;
			जारी;
		पूर्ण

		/* Check the checksum */
		अगर (!buffer_verअगरied(bh) &&
		    !ext4_dirblock_csum_verअगरy(inode, bh)) अणु
			EXT4_ERROR_खाता(file, 0, "directory fails checksum "
					"at offset %llu",
					(अचिन्हित दीर्घ दीर्घ)ctx->pos);
			ctx->pos += sb->s_blocksize - offset;
			brअन्यथा(bh);
			bh = शून्य;
			जारी;
		पूर्ण
		set_buffer_verअगरied(bh);

		/* If the dir block has changed since the last call to
		 * सूची_पढ़ो(2), then we might be poपूर्णांकing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		अगर (!inode_eq_iversion(inode, file->f_version)) अणु
			क्रम (i = 0; i < sb->s_blocksize && i < offset; ) अणु
				de = (काष्ठा ext4_dir_entry_2 *)
					(bh->b_data + i);
				/* It's too expensive to करो a full
				 * dirent test each समय round this
				 * loop, but we करो have to test at
				 * least that it is non-zero.  A
				 * failure will be detected in the
				 * dirent test below. */
				अगर (ext4_rec_len_from_disk(de->rec_len,
					sb->s_blocksize) < ext4_dir_rec_len(1,
									inode))
					अवरोध;
				i += ext4_rec_len_from_disk(de->rec_len,
							    sb->s_blocksize);
			पूर्ण
			offset = i;
			ctx->pos = (ctx->pos & ~(sb->s_blocksize - 1))
				| offset;
			file->f_version = inode_query_iversion(inode);
		पूर्ण

		जबतक (ctx->pos < inode->i_size
		       && offset < sb->s_blocksize) अणु
			de = (काष्ठा ext4_dir_entry_2 *) (bh->b_data + offset);
			अगर (ext4_check_dir_entry(inode, file, de, bh,
						 bh->b_data, bh->b_size,
						 offset)) अणु
				/*
				 * On error, skip to the next block
				 */
				ctx->pos = (ctx->pos |
						(sb->s_blocksize - 1)) + 1;
				अवरोध;
			पूर्ण
			offset += ext4_rec_len_from_disk(de->rec_len,
					sb->s_blocksize);
			अगर (le32_to_cpu(de->inode)) अणु
				अगर (!IS_ENCRYPTED(inode)) अणु
					अगर (!dir_emit(ctx, de->name,
					    de->name_len,
					    le32_to_cpu(de->inode),
					    get_dtype(sb, de->file_type)))
						जाओ करोne;
				पूर्ण अन्यथा अणु
					पूर्णांक save_len = fstr.len;
					काष्ठा fscrypt_str de_name =
							FSTR_INIT(de->name,
								de->name_len);

					/* Directory is encrypted */
					err = fscrypt_fname_disk_to_usr(inode,
						EXT4_सूचीENT_HASH(de),
						EXT4_सूचीENT_MINOR_HASH(de),
						&de_name, &fstr);
					de_name = fstr;
					fstr.len = save_len;
					अगर (err)
						जाओ errout;
					अगर (!dir_emit(ctx,
					    de_name.name, de_name.len,
					    le32_to_cpu(de->inode),
					    get_dtype(sb, de->file_type)))
						जाओ करोne;
				पूर्ण
			पूर्ण
			ctx->pos += ext4_rec_len_from_disk(de->rec_len,
						sb->s_blocksize);
		पूर्ण
		अगर ((ctx->pos < inode->i_size) && !dir_relax_shared(inode))
			जाओ करोne;
		brअन्यथा(bh);
		bh = शून्य;
		offset = 0;
	पूर्ण
करोne:
	err = 0;
errout:
	fscrypt_fname_मुक्त_buffer(&fstr);
	brअन्यथा(bh);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक is_32bit_api(व्योम)
अणु
#अगर_घोषित CONFIG_COMPAT
	वापस in_compat_syscall();
#अन्यथा
	वापस (BITS_PER_LONG == 32);
#पूर्ण_अगर
पूर्ण

/*
 * These functions convert from the major/minor hash to an f_pos
 * value क्रम dx directories
 *
 * Upper layer (क्रम example NFS) should specअगरy FMODE_32BITHASH or
 * FMODE_64BITHASH explicitly. On the other hand, we allow ext4 to be mounted
 * directly on both 32-bit and 64-bit nodes, under such हाल, neither
 * FMODE_32BITHASH nor FMODE_64BITHASH is specअगरied.
 */
अटल अंतरभूत loff_t hash2pos(काष्ठा file *filp, __u32 major, __u32 minor)
अणु
	अगर ((filp->f_mode & FMODE_32BITHASH) ||
	    (!(filp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		वापस major >> 1;
	अन्यथा
		वापस ((__u64)(major >> 1) << 32) | (__u64)minor;
पूर्ण

अटल अंतरभूत __u32 pos2maj_hash(काष्ठा file *filp, loff_t pos)
अणु
	अगर ((filp->f_mode & FMODE_32BITHASH) ||
	    (!(filp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		वापस (pos << 1) & 0xffffffff;
	अन्यथा
		वापस ((pos >> 32) << 1) & 0xffffffff;
पूर्ण

अटल अंतरभूत __u32 pos2min_hash(काष्ठा file *filp, loff_t pos)
अणु
	अगर ((filp->f_mode & FMODE_32BITHASH) ||
	    (!(filp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		वापस 0;
	अन्यथा
		वापस pos & 0xffffffff;
पूर्ण

/*
 * Return 32- or 64-bit end-of-file क्रम dx directories
 */
अटल अंतरभूत loff_t ext4_get_htree_eof(काष्ठा file *filp)
अणु
	अगर ((filp->f_mode & FMODE_32BITHASH) ||
	    (!(filp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		वापस EXT4_HTREE_खातापूर्ण_32BIT;
	अन्यथा
		वापस EXT4_HTREE_खातापूर्ण_64BIT;
पूर्ण


/*
 * ext4_dir_llseek() calls generic_file_llseek_size to handle htree
 * directories, where the "offset" is in terms of the filename hash
 * value instead of the byte offset.
 *
 * Because we may वापस a 64-bit hash that is well beyond offset limits,
 * we need to pass the max hash as the maximum allowable offset in
 * the htree directory हाल.
 *
 * For non-htree, ext4_llseek alपढ़ोy chooses the proper max offset.
 */
अटल loff_t ext4_dir_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक dx_dir = is_dx_dir(inode);
	loff_t ret, htree_max = ext4_get_htree_eof(file);

	अगर (likely(dx_dir))
		ret = generic_file_llseek_size(file, offset, whence,
						    htree_max, htree_max);
	अन्यथा
		ret = ext4_llseek(file, offset, whence);
	file->f_version = inode_peek_iversion(inode) - 1;
	वापस ret;
पूर्ण

/*
 * This काष्ठाure holds the nodes of the red-black tree used to store
 * the directory entry in hash order.
 */
काष्ठा fname अणु
	__u32		hash;
	__u32		minor_hash;
	काष्ठा rb_node	rb_hash;
	काष्ठा fname	*next;
	__u32		inode;
	__u8		name_len;
	__u8		file_type;
	अक्षर		name[];
पूर्ण;

/*
 * This functoin implements a non-recursive way of मुक्तing all of the
 * nodes in the red-black tree.
 */
अटल व्योम मुक्त_rb_tree_fname(काष्ठा rb_root *root)
अणु
	काष्ठा fname *fname, *next;

	rbtree_postorder_क्रम_each_entry_safe(fname, next, root, rb_hash)
		जबतक (fname) अणु
			काष्ठा fname *old = fname;
			fname = fname->next;
			kमुक्त(old);
		पूर्ण

	*root = RB_ROOT;
पूर्ण


अटल काष्ठा dir_निजी_info *ext4_htree_create_dir_info(काष्ठा file *filp,
							   loff_t pos)
अणु
	काष्ठा dir_निजी_info *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;
	p->curr_hash = pos2maj_hash(filp, pos);
	p->curr_minor_hash = pos2min_hash(filp, pos);
	वापस p;
पूर्ण

व्योम ext4_htree_मुक्त_dir_info(काष्ठा dir_निजी_info *p)
अणु
	मुक्त_rb_tree_fname(&p->root);
	kमुक्त(p);
पूर्ण

/*
 * Given a directory entry, enter it पूर्णांकo the fname rb tree.
 *
 * When filename encryption is enabled, the dirent will hold the
 * encrypted filename, जबतक the htree will hold decrypted filename.
 * The decrypted filename is passed in via ent_name.  parameter.
 */
पूर्णांक ext4_htree_store_dirent(काष्ठा file *dir_file, __u32 hash,
			     __u32 minor_hash,
			    काष्ठा ext4_dir_entry_2 *dirent,
			    काष्ठा fscrypt_str *ent_name)
अणु
	काष्ठा rb_node **p, *parent = शून्य;
	काष्ठा fname *fname, *new_fn;
	काष्ठा dir_निजी_info *info;
	पूर्णांक len;

	info = dir_file->निजी_data;
	p = &info->root.rb_node;

	/* Create and allocate the fname काष्ठाure */
	len = माप(काष्ठा fname) + ent_name->len + 1;
	new_fn = kzalloc(len, GFP_KERNEL);
	अगर (!new_fn)
		वापस -ENOMEM;
	new_fn->hash = hash;
	new_fn->minor_hash = minor_hash;
	new_fn->inode = le32_to_cpu(dirent->inode);
	new_fn->name_len = ent_name->len;
	new_fn->file_type = dirent->file_type;
	स_नकल(new_fn->name, ent_name->name, ent_name->len);

	जबतक (*p) अणु
		parent = *p;
		fname = rb_entry(parent, काष्ठा fname, rb_hash);

		/*
		 * If the hash and minor hash match up, then we put
		 * them on a linked list.  This rarely happens...
		 */
		अगर ((new_fn->hash == fname->hash) &&
		    (new_fn->minor_hash == fname->minor_hash)) अणु
			new_fn->next = fname->next;
			fname->next = new_fn;
			वापस 0;
		पूर्ण

		अगर (new_fn->hash < fname->hash)
			p = &(*p)->rb_left;
		अन्यथा अगर (new_fn->hash > fname->hash)
			p = &(*p)->rb_right;
		अन्यथा अगर (new_fn->minor_hash < fname->minor_hash)
			p = &(*p)->rb_left;
		अन्यथा /* अगर (new_fn->minor_hash > fname->minor_hash) */
			p = &(*p)->rb_right;
	पूर्ण

	rb_link_node(&new_fn->rb_hash, parent, p);
	rb_insert_color(&new_fn->rb_hash, &info->root);
	वापस 0;
पूर्ण



/*
 * This is a helper function क्रम ext4_dx_सूची_पढ़ो.  It calls filldir
 * क्रम all entres on the fname linked list.  (Normally there is only
 * one entry on the linked list, unless there are 62 bit hash collisions.)
 */
अटल पूर्णांक call_filldir(काष्ठा file *file, काष्ठा dir_context *ctx,
			काष्ठा fname *fname)
अणु
	काष्ठा dir_निजी_info *info = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;

	अगर (!fname) अणु
		ext4_msg(sb, KERN_ERR, "%s:%d: inode #%lu: comm %s: "
			 "called with null fname?!?", __func__, __LINE__,
			 inode->i_ino, current->comm);
		वापस 0;
	पूर्ण
	ctx->pos = hash2pos(file, fname->hash, fname->minor_hash);
	जबतक (fname) अणु
		अगर (!dir_emit(ctx, fname->name,
				fname->name_len,
				fname->inode,
				get_dtype(sb, fname->file_type))) अणु
			info->extra_fname = fname;
			वापस 1;
		पूर्ण
		fname = fname->next;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_dx_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा dir_निजी_info *info = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fname *fname;
	पूर्णांक	ret;

	अगर (!info) अणु
		info = ext4_htree_create_dir_info(file, ctx->pos);
		अगर (!info)
			वापस -ENOMEM;
		file->निजी_data = info;
	पूर्ण

	अगर (ctx->pos == ext4_get_htree_eof(file))
		वापस 0;	/* खातापूर्ण */

	/* Some one has messed with f_pos; reset the world */
	अगर (info->last_pos != ctx->pos) अणु
		मुक्त_rb_tree_fname(&info->root);
		info->curr_node = शून्य;
		info->extra_fname = शून्य;
		info->curr_hash = pos2maj_hash(file, ctx->pos);
		info->curr_minor_hash = pos2min_hash(file, ctx->pos);
	पूर्ण

	/*
	 * If there are any leftover names on the hash collision
	 * chain, वापस them first.
	 */
	अगर (info->extra_fname) अणु
		अगर (call_filldir(file, ctx, info->extra_fname))
			जाओ finished;
		info->extra_fname = शून्य;
		जाओ next_node;
	पूर्ण अन्यथा अगर (!info->curr_node)
		info->curr_node = rb_first(&info->root);

	जबतक (1) अणु
		/*
		 * Fill the rbtree अगर we have no more entries,
		 * or the inode has changed since we last पढ़ो in the
		 * cached entries.
		 */
		अगर ((!info->curr_node) ||
		    !inode_eq_iversion(inode, file->f_version)) अणु
			info->curr_node = शून्य;
			मुक्त_rb_tree_fname(&info->root);
			file->f_version = inode_query_iversion(inode);
			ret = ext4_htree_fill_tree(file, info->curr_hash,
						   info->curr_minor_hash,
						   &info->next_hash);
			अगर (ret < 0)
				वापस ret;
			अगर (ret == 0) अणु
				ctx->pos = ext4_get_htree_eof(file);
				अवरोध;
			पूर्ण
			info->curr_node = rb_first(&info->root);
		पूर्ण

		fname = rb_entry(info->curr_node, काष्ठा fname, rb_hash);
		info->curr_hash = fname->hash;
		info->curr_minor_hash = fname->minor_hash;
		अगर (call_filldir(file, ctx, fname))
			अवरोध;
	next_node:
		info->curr_node = rb_next(info->curr_node);
		अगर (info->curr_node) अणु
			fname = rb_entry(info->curr_node, काष्ठा fname,
					 rb_hash);
			info->curr_hash = fname->hash;
			info->curr_minor_hash = fname->minor_hash;
		पूर्ण अन्यथा अणु
			अगर (info->next_hash == ~0) अणु
				ctx->pos = ext4_get_htree_eof(file);
				अवरोध;
			पूर्ण
			info->curr_hash = info->next_hash;
			info->curr_minor_hash = 0;
		पूर्ण
	पूर्ण
finished:
	info->last_pos = ctx->pos;
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_release_dir(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (filp->निजी_data)
		ext4_htree_मुक्त_dir_info(filp->निजी_data);

	वापस 0;
पूर्ण

पूर्णांक ext4_check_all_de(काष्ठा inode *dir, काष्ठा buffer_head *bh, व्योम *buf,
		      पूर्णांक buf_size)
अणु
	काष्ठा ext4_dir_entry_2 *de;
	पूर्णांक rlen;
	अचिन्हित पूर्णांक offset = 0;
	अक्षर *top;

	de = (काष्ठा ext4_dir_entry_2 *)buf;
	top = buf + buf_size;
	जबतक ((अक्षर *) de < top) अणु
		अगर (ext4_check_dir_entry(dir, शून्य, de, bh,
					 buf, buf_size, offset))
			वापस -EFSCORRUPTED;
		rlen = ext4_rec_len_from_disk(de->rec_len, buf_size);
		de = (काष्ठा ext4_dir_entry_2 *)((अक्षर *)de + rlen);
		offset += rlen;
	पूर्ण
	अगर ((अक्षर *) de > top)
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations ext4_dir_operations = अणु
	.llseek		= ext4_dir_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= ext4_सूची_पढ़ो,
	.unlocked_ioctl = ext4_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ext4_compat_ioctl,
#पूर्ण_अगर
	.fsync		= ext4_sync_file,
	.release	= ext4_release_dir,
पूर्ण;
