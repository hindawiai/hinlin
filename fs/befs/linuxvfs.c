<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/befs/linuxvfs.c
 *
 * Copyright (C) 2001 Will Dyson <will_dyson@pobox.com
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/nls.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/vfs.h>
#समावेश <linux/parser.h>
#समावेश <linux/namei.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blkdev.h>

#समावेश "befs.h"
#समावेश "btree.h"
#समावेश "inode.h"
#समावेश "datastream.h"
#समावेश "super.h"
#समावेश "io.h"

MODULE_DESCRIPTION("BeOS File System (BeFS) driver");
MODULE_AUTHOR("Will Dyson");
MODULE_LICENSE("GPL");

/* The units the vfs expects inode->i_blocks to be in */
#घोषणा VFS_BLOCK_SIZE 512

अटल पूर्णांक befs_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);
अटल पूर्णांक befs_get_block(काष्ठा inode *, sector_t, काष्ठा buffer_head *, पूर्णांक);
अटल पूर्णांक befs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page);
अटल sector_t befs_bmap(काष्ठा address_space *mapping, sector_t block);
अटल काष्ठा dentry *befs_lookup(काष्ठा inode *, काष्ठा dentry *,
				  अचिन्हित पूर्णांक);
अटल काष्ठा inode *befs_iget(काष्ठा super_block *, अचिन्हित दीर्घ);
अटल काष्ठा inode *befs_alloc_inode(काष्ठा super_block *sb);
अटल व्योम befs_मुक्त_inode(काष्ठा inode *inode);
अटल व्योम befs_destroy_inodecache(व्योम);
अटल पूर्णांक befs_symlink_पढ़ोpage(काष्ठा file *, काष्ठा page *);
अटल पूर्णांक befs_utf2nls(काष्ठा super_block *sb, स्थिर अक्षर *in, पूर्णांक in_len,
			अक्षर **out, पूर्णांक *out_len);
अटल पूर्णांक befs_nls2utf(काष्ठा super_block *sb, स्थिर अक्षर *in, पूर्णांक in_len,
			अक्षर **out, पूर्णांक *out_len);
अटल व्योम befs_put_super(काष्ठा super_block *);
अटल पूर्णांक befs_remount(काष्ठा super_block *, पूर्णांक *, अक्षर *);
अटल पूर्णांक befs_statfs(काष्ठा dentry *, काष्ठा kstatfs *);
अटल पूर्णांक befs_show_options(काष्ठा seq_file *, काष्ठा dentry *);
अटल पूर्णांक parse_options(अक्षर *, काष्ठा befs_mount_options *);
अटल काष्ठा dentry *befs_fh_to_dentry(काष्ठा super_block *sb,
				काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type);
अटल काष्ठा dentry *befs_fh_to_parent(काष्ठा super_block *sb,
				काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type);
अटल काष्ठा dentry *befs_get_parent(काष्ठा dentry *child);

अटल स्थिर काष्ठा super_operations befs_sops = अणु
	.alloc_inode	= befs_alloc_inode,	/* allocate a new inode */
	.मुक्त_inode	= befs_मुक्त_inode, /* deallocate an inode */
	.put_super	= befs_put_super,	/* uninit super */
	.statfs		= befs_statfs,	/* statfs */
	.remount_fs	= befs_remount,
	.show_options	= befs_show_options,
पूर्ण;

/* slab cache क्रम befs_inode_info objects */
अटल काष्ठा kmem_cache *befs_inode_cachep;

अटल स्थिर काष्ठा file_operations befs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= befs_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा inode_operations befs_dir_inode_operations = अणु
	.lookup		= befs_lookup,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations befs_aops = अणु
	.पढ़ोpage	= befs_पढ़ोpage,
	.bmap		= befs_bmap,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations befs_symlink_aops = अणु
	.पढ़ोpage	= befs_symlink_पढ़ोpage,
पूर्ण;

अटल स्थिर काष्ठा export_operations befs_export_operations = अणु
	.fh_to_dentry	= befs_fh_to_dentry,
	.fh_to_parent	= befs_fh_to_parent,
	.get_parent	= befs_get_parent,
पूर्ण;

/*
 * Called by generic_file_पढ़ो() to पढ़ो a page of data
 *
 * In turn, simply calls a generic block पढ़ो function and
 * passes it the address of befs_get_block, क्रम mapping file
 * positions to disk blocks.
 */
अटल पूर्णांक
befs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, befs_get_block);
पूर्ण

अटल sector_t
befs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, befs_get_block);
पूर्ण

/*
 * Generic function to map a file position (block) to a
 * disk offset (passed back in bh_result).
 *
 * Used by many higher level functions.
 *
 * Calls befs_fblock2brun() in datastream.c to करो the real work.
 */

अटल पूर्णांक
befs_get_block(काष्ठा inode *inode, sector_t block,
	       काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	befs_data_stream *ds = &BEFS_I(inode)->i_data.ds;
	befs_block_run run = BAD_IADDR;
	पूर्णांक res;
	uदीर्घ disk_off;

	befs_debug(sb, "---> befs_get_block() for inode %lu, block %ld",
		   (अचिन्हित दीर्घ)inode->i_ino, (दीर्घ)block);
	अगर (create) अणु
		befs_error(sb, "befs_get_block() was asked to write to "
			   "block %ld in inode %lu", (दीर्घ)block,
			   (अचिन्हित दीर्घ)inode->i_ino);
		वापस -EPERM;
	पूर्ण

	res = befs_fblock2brun(sb, ds, block, &run);
	अगर (res != BEFS_OK) अणु
		befs_error(sb,
			   "<--- %s for inode %lu, block %ld ERROR",
			   __func__, (अचिन्हित दीर्घ)inode->i_ino,
			   (दीर्घ)block);
		वापस -EFBIG;
	पूर्ण

	disk_off = (uदीर्घ) iaddr2blockno(sb, &run);

	map_bh(bh_result, inode->i_sb, disk_off);

	befs_debug(sb, "<--- %s for inode %lu, block %ld, disk address %lu",
		  __func__, (अचिन्हित दीर्घ)inode->i_ino, (दीर्घ)block,
		  (अचिन्हित दीर्घ)disk_off);

	वापस 0;
पूर्ण

अटल काष्ठा dentry *
befs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	काष्ठा super_block *sb = dir->i_sb;
	स्थिर befs_data_stream *ds = &BEFS_I(dir)->i_data.ds;
	befs_off_t offset;
	पूर्णांक ret;
	पूर्णांक utfnamelen;
	अक्षर *utfname;
	स्थिर अक्षर *name = dentry->d_name.name;

	befs_debug(sb, "---> %s name %pd inode %ld", __func__,
		   dentry, dir->i_ino);

	/* Convert to UTF-8 */
	अगर (BEFS_SB(sb)->nls) अणु
		ret =
		    befs_nls2utf(sb, name, म_माप(name), &utfname, &utfnamelen);
		अगर (ret < 0) अणु
			befs_debug(sb, "<--- %s ERROR", __func__);
			वापस ERR_PTR(ret);
		पूर्ण
		ret = befs_btree_find(sb, ds, utfname, &offset);
		kमुक्त(utfname);

	पूर्ण अन्यथा अणु
		ret = befs_btree_find(sb, ds, name, &offset);
	पूर्ण

	अगर (ret == BEFS_BT_NOT_FOUND) अणु
		befs_debug(sb, "<--- %s %pd not found", __func__, dentry);
		inode = शून्य;
	पूर्ण अन्यथा अगर (ret != BEFS_OK || offset == 0) अणु
		befs_error(sb, "<--- %s Error", __func__);
		inode = ERR_PTR(-ENODATA);
	पूर्ण अन्यथा अणु
		inode = befs_iget(dir->i_sb, (ino_t) offset);
	पूर्ण
	befs_debug(sb, "<--- %s", __func__);

	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक
befs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	स्थिर befs_data_stream *ds = &BEFS_I(inode)->i_data.ds;
	befs_off_t value;
	पूर्णांक result;
	माप_प्रकार keysize;
	अक्षर keybuf[BEFS_NAME_LEN + 1];

	befs_debug(sb, "---> %s name %pD, inode %ld, ctx->pos %lld",
		  __func__, file, inode->i_ino, ctx->pos);

	जबतक (1) अणु
		result = befs_btree_पढ़ो(sb, ds, ctx->pos, BEFS_NAME_LEN + 1,
					 keybuf, &keysize, &value);

		अगर (result == BEFS_ERR) अणु
			befs_debug(sb, "<--- %s ERROR", __func__);
			befs_error(sb, "IO error reading %pD (inode %lu)",
				   file, inode->i_ino);
			वापस -EIO;

		पूर्ण अन्यथा अगर (result == BEFS_BT_END) अणु
			befs_debug(sb, "<--- %s END", __func__);
			वापस 0;

		पूर्ण अन्यथा अगर (result == BEFS_BT_EMPTY) अणु
			befs_debug(sb, "<--- %s Empty directory", __func__);
			वापस 0;
		पूर्ण

		/* Convert to NLS */
		अगर (BEFS_SB(sb)->nls) अणु
			अक्षर *nlsname;
			पूर्णांक nlsnamelen;

			result =
			    befs_utf2nls(sb, keybuf, keysize, &nlsname,
					 &nlsnamelen);
			अगर (result < 0) अणु
				befs_debug(sb, "<--- %s ERROR", __func__);
				वापस result;
			पूर्ण
			अगर (!dir_emit(ctx, nlsname, nlsnamelen,
				      (ino_t) value, DT_UNKNOWN)) अणु
				kमुक्त(nlsname);
				वापस 0;
			पूर्ण
			kमुक्त(nlsname);
		पूर्ण अन्यथा अणु
			अगर (!dir_emit(ctx, keybuf, keysize,
				      (ino_t) value, DT_UNKNOWN))
				वापस 0;
		पूर्ण
		ctx->pos++;
	पूर्ण
पूर्ण

अटल काष्ठा inode *
befs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा befs_inode_info *bi;

	bi = kmem_cache_alloc(befs_inode_cachep, GFP_KERNEL);
	अगर (!bi)
		वापस शून्य;
	वापस &bi->vfs_inode;
पूर्ण

अटल व्योम befs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(befs_inode_cachep, BEFS_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा befs_inode_info *bi = (काष्ठा befs_inode_info *) foo;

	inode_init_once(&bi->vfs_inode);
पूर्ण

अटल काष्ठा inode *befs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा buffer_head *bh;
	befs_inode *raw_inode;
	काष्ठा befs_sb_info *befs_sb = BEFS_SB(sb);
	काष्ठा befs_inode_info *befs_ino;
	काष्ठा inode *inode;

	befs_debug(sb, "---> %s inode = %lu", __func__, ino);

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	befs_ino = BEFS_I(inode);

	/* convert from vfs's inode number to befs's inode number */
	befs_ino->i_inode_num = blockno2iaddr(sb, inode->i_ino);

	befs_debug(sb, "  real inode number [%u, %hu, %hu]",
		   befs_ino->i_inode_num.allocation_group,
		   befs_ino->i_inode_num.start, befs_ino->i_inode_num.len);

	bh = sb_bपढ़ो(sb, inode->i_ino);
	अगर (!bh) अणु
		befs_error(sb, "unable to read inode block - "
			   "inode = %lu", inode->i_ino);
		जाओ unacquire_none;
	पूर्ण

	raw_inode = (befs_inode *) bh->b_data;

	befs_dump_inode(sb, raw_inode);

	अगर (befs_check_inode(sb, raw_inode, inode->i_ino) != BEFS_OK) अणु
		befs_error(sb, "Bad inode: %lu", inode->i_ino);
		जाओ unacquire_bh;
	पूर्ण

	inode->i_mode = (umode_t) fs32_to_cpu(sb, raw_inode->mode);

	/*
	 * set uid and gid.  But since current BeOS is single user OS, so
	 * you can change by "uid" or "gid" options.
	 */

	inode->i_uid = befs_sb->mount_opts.use_uid ?
		befs_sb->mount_opts.uid :
		make_kuid(&init_user_ns, fs32_to_cpu(sb, raw_inode->uid));
	inode->i_gid = befs_sb->mount_opts.use_gid ?
		befs_sb->mount_opts.gid :
		make_kgid(&init_user_ns, fs32_to_cpu(sb, raw_inode->gid));

	set_nlink(inode, 1);

	/*
	 * BEFS's समय is 64 bits, but current VFS is 32 bits...
	 * BEFS करोn't have access समय. Nor inode change समय. VFS
	 * करोesn't have creation समय.
	 * Also, the lower 16 bits of the last_modअगरied_समय and
	 * create_समय are just a counter to help ensure uniqueness
	 * क्रम indexing purposes. (PFD, page 54)
	 */

	inode->i_mसमय.tv_sec =
	    fs64_to_cpu(sb, raw_inode->last_modअगरied_समय) >> 16;
	inode->i_mसमय.tv_nsec = 0;   /* lower 16 bits are not a समय */
	inode->i_स_समय = inode->i_mसमय;
	inode->i_aसमय = inode->i_mसमय;

	befs_ino->i_inode_num = fsrun_to_cpu(sb, raw_inode->inode_num);
	befs_ino->i_parent = fsrun_to_cpu(sb, raw_inode->parent);
	befs_ino->i_attribute = fsrun_to_cpu(sb, raw_inode->attributes);
	befs_ino->i_flags = fs32_to_cpu(sb, raw_inode->flags);

	अगर (S_ISLNK(inode->i_mode) && !(befs_ino->i_flags & BEFS_LONG_SYMLINK))अणु
		inode->i_size = 0;
		inode->i_blocks = befs_sb->block_size / VFS_BLOCK_SIZE;
		strlcpy(befs_ino->i_data.symlink, raw_inode->data.symlink,
			BEFS_SYMLINK_LEN);
	पूर्ण अन्यथा अणु
		पूर्णांक num_blks;

		befs_ino->i_data.ds =
		    fsds_to_cpu(sb, &raw_inode->data.datastream);

		num_blks = befs_count_blocks(sb, &befs_ino->i_data.ds);
		inode->i_blocks =
		    num_blks * (befs_sb->block_size / VFS_BLOCK_SIZE);
		inode->i_size = befs_ino->i_data.ds.size;
	पूर्ण

	inode->i_mapping->a_ops = &befs_aops;

	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_fop = &generic_ro_fops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &befs_dir_inode_operations;
		inode->i_fop = &befs_dir_operations;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		अगर (befs_ino->i_flags & BEFS_LONG_SYMLINK) अणु
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &befs_symlink_aops;
		पूर्ण अन्यथा अणु
			inode->i_link = befs_ino->i_data.symlink;
			inode->i_op = &simple_symlink_inode_operations;
		पूर्ण
	पूर्ण अन्यथा अणु
		befs_error(sb, "Inode %lu is not a regular file, "
			   "directory or symlink. THAT IS WRONG! BeFS has no "
			   "on disk special files", inode->i_ino);
		जाओ unacquire_bh;
	पूर्ण

	brअन्यथा(bh);
	befs_debug(sb, "<--- %s", __func__);
	unlock_new_inode(inode);
	वापस inode;

unacquire_bh:
	brअन्यथा(bh);

unacquire_none:
	iget_failed(inode);
	befs_debug(sb, "<--- %s - Bad inode", __func__);
	वापस ERR_PTR(-EIO);
पूर्ण

/* Initialize the inode cache. Called at fs setup.
 *
 * Taken from NFS implementation by Al Viro.
 */
अटल पूर्णांक __init
befs_init_inodecache(व्योम)
अणु
	befs_inode_cachep = kmem_cache_create_usercopy("befs_inode_cache",
				माप(काष्ठा befs_inode_info), 0,
				(SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
					SLAB_ACCOUNT),
				दुरत्व(काष्ठा befs_inode_info,
					i_data.symlink),
				माप_field(काष्ठा befs_inode_info,
					i_data.symlink),
				init_once);
	अगर (befs_inode_cachep == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Called at fs tearकरोwn.
 *
 * Taken from NFS implementation by Al Viro.
 */
अटल व्योम
befs_destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(befs_inode_cachep);
पूर्ण

/*
 * The inode of symbolic link is dअगरferent to data stream.
 * The data stream become link name. Unless the LONG_SYMLINK
 * flag is set.
 */
अटल पूर्णांक befs_symlink_पढ़ोpage(काष्ठा file *unused, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा befs_inode_info *befs_ino = BEFS_I(inode);
	befs_data_stream *data = &befs_ino->i_data.ds;
	befs_off_t len = data->size;
	अक्षर *link = page_address(page);

	अगर (len == 0 || len > PAGE_SIZE) अणु
		befs_error(sb, "Long symlink with illegal length");
		जाओ fail;
	पूर्ण
	befs_debug(sb, "Follow long symlink");

	अगर (befs_पढ़ो_lsymlink(sb, data, link, len) != len) अणु
		befs_error(sb, "Failed to read entire long symlink");
		जाओ fail;
	पूर्ण
	link[len - 1] = '\0';
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;
fail:
	SetPageError(page);
	unlock_page(page);
	वापस -EIO;
पूर्ण

/*
 * UTF-8 to NLS अक्षरset convert routine
 *
 * Uses uni2अक्षर() / अक्षर2uni() rather than the nls tables directly
 */
अटल पूर्णांक
befs_utf2nls(काष्ठा super_block *sb, स्थिर अक्षर *in,
	     पूर्णांक in_len, अक्षर **out, पूर्णांक *out_len)
अणु
	काष्ठा nls_table *nls = BEFS_SB(sb)->nls;
	पूर्णांक i, o;
	unicode_t uni;
	पूर्णांक unilen, utflen;
	अक्षर *result;
	/* The utf8->nls conversion won't make the final nls string bigger
	 * than the utf one, but अगर the string is pure ascii they'll have the
	 * same width and an extra अक्षर is needed to save the additional \0
	 */
	पूर्णांक maxlen = in_len + 1;

	befs_debug(sb, "---> %s", __func__);

	अगर (!nls) अणु
		befs_error(sb, "%s called with no NLS table loaded", __func__);
		वापस -EINVAL;
	पूर्ण

	*out = result = kदो_स्मृति(maxlen, GFP_NOFS);
	अगर (!*out)
		वापस -ENOMEM;

	क्रम (i = o = 0; i < in_len; i += utflen, o += unilen) अणु

		/* convert from UTF-8 to Unicode */
		utflen = utf8_to_utf32(&in[i], in_len - i, &uni);
		अगर (utflen < 0)
			जाओ conv_err;

		/* convert from Unicode to nls */
		अगर (uni > MAX_WCHAR_T)
			जाओ conv_err;
		unilen = nls->uni2अक्षर(uni, &result[o], in_len - o);
		अगर (unilen < 0)
			जाओ conv_err;
	पूर्ण
	result[o] = '\0';
	*out_len = o;

	befs_debug(sb, "<--- %s", __func__);

	वापस o;

conv_err:
	befs_error(sb, "Name using character set %s contains a character that "
		   "cannot be converted to unicode.", nls->अक्षरset);
	befs_debug(sb, "<--- %s", __func__);
	kमुक्त(result);
	वापस -EILSEQ;
पूर्ण

/**
 * befs_nls2utf - Convert NLS string to utf8 encodeing
 * @sb: Superblock
 * @in: Input string buffer in NLS क्रमmat
 * @in_len: Length of input string in bytes
 * @out: The output string in UTF-8 क्रमmat
 * @out_len: Length of the output buffer
 *
 * Converts input string @in, which is in the क्रमmat of the loaded NLS map,
 * पूर्णांकo a utf8 string.
 *
 * The destination string @out is allocated by this function and the caller is
 * responsible क्रम मुक्तing it with kमुक्त()
 *
 * On वापस, *@out_len is the length of @out in bytes.
 *
 * On success, the वापस value is the number of utf8 अक्षरacters written to
 * the output buffer @out.
 *
 * On Failure, a negative number coresponding to the error code is वापसed.
 */

अटल पूर्णांक
befs_nls2utf(काष्ठा super_block *sb, स्थिर अक्षर *in,
	     पूर्णांक in_len, अक्षर **out, पूर्णांक *out_len)
अणु
	काष्ठा nls_table *nls = BEFS_SB(sb)->nls;
	पूर्णांक i, o;
	ब_अक्षर_प्रकार uni;
	पूर्णांक unilen, utflen;
	अक्षर *result;
	/*
	 * There are nls अक्षरacters that will translate to 3-अक्षरs-wide UTF-8
	 * अक्षरacters, an additional byte is needed to save the final \0
	 * in special हालs
	 */
	पूर्णांक maxlen = (3 * in_len) + 1;

	befs_debug(sb, "---> %s\n", __func__);

	अगर (!nls) अणु
		befs_error(sb, "%s called with no NLS table loaded.",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	*out = result = kदो_स्मृति(maxlen, GFP_NOFS);
	अगर (!*out) अणु
		*out_len = 0;
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = o = 0; i < in_len; i += unilen, o += utflen) अणु

		/* convert from nls to unicode */
		unilen = nls->अक्षर2uni(&in[i], in_len - i, &uni);
		अगर (unilen < 0)
			जाओ conv_err;

		/* convert from unicode to UTF-8 */
		utflen = utf32_to_utf8(uni, &result[o], 3);
		अगर (utflen <= 0)
			जाओ conv_err;
	पूर्ण

	result[o] = '\0';
	*out_len = o;

	befs_debug(sb, "<--- %s", __func__);

	वापस i;

conv_err:
	befs_error(sb, "Name using character set %s contains a character that "
		   "cannot be converted to unicode.", nls->अक्षरset);
	befs_debug(sb, "<--- %s", __func__);
	kमुक्त(result);
	वापस -EILSEQ;
पूर्ण

अटल काष्ठा inode *befs_nfs_get_inode(काष्ठा super_block *sb, uपूर्णांक64_t ino,
					 uपूर्णांक32_t generation)
अणु
	/* No need to handle i_generation */
	वापस befs_iget(sb, ino);
पूर्ण

/*
 * Map a NFS file handle to a corresponding dentry
 */
अटल काष्ठा dentry *befs_fh_to_dentry(काष्ठा super_block *sb,
				काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    befs_nfs_get_inode);
पूर्ण

/*
 * Find the parent क्रम a file specअगरied by NFS handle
 */
अटल काष्ठा dentry *befs_fh_to_parent(काष्ठा super_block *sb,
				काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    befs_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *befs_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा inode *parent;
	काष्ठा befs_inode_info *befs_ino = BEFS_I(d_inode(child));

	parent = befs_iget(child->d_sb,
			   (अचिन्हित दीर्घ)befs_ino->i_parent.start);
	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	वापस d_obtain_alias(parent);
पूर्ण

क्रमागत अणु
	Opt_uid, Opt_gid, Opt_अक्षरset, Opt_debug, Opt_err,
पूर्ण;

अटल स्थिर match_table_t befs_tokens = अणु
	अणुOpt_uid, "uid=%d"पूर्ण,
	अणुOpt_gid, "gid=%d"पूर्ण,
	अणुOpt_अक्षरset, "iocharset=%s"पूर्ण,
	अणुOpt_debug, "debug"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक
parse_options(अक्षर *options, काष्ठा befs_mount_options *opts)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	kuid_t uid;
	kgid_t gid;

	/* Initialize options */
	opts->uid = GLOBAL_ROOT_UID;
	opts->gid = GLOBAL_ROOT_GID;
	opts->use_uid = 0;
	opts->use_gid = 0;
	opts->ioअक्षरset = शून्य;
	opts->debug = 0;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;

		token = match_token(p, befs_tokens, args);
		चयन (token) अणु
		हाल Opt_uid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			uid = INVALID_UID;
			अगर (option >= 0)
				uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(uid)) अणु
				pr_err("Invalid uid %d, "
				       "using default\n", option);
				अवरोध;
			पूर्ण
			opts->uid = uid;
			opts->use_uid = 1;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			gid = INVALID_GID;
			अगर (option >= 0)
				gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(gid)) अणु
				pr_err("Invalid gid %d, "
				       "using default\n", option);
				अवरोध;
			पूर्ण
			opts->gid = gid;
			opts->use_gid = 1;
			अवरोध;
		हाल Opt_अक्षरset:
			kमुक्त(opts->ioअक्षरset);
			opts->ioअक्षरset = match_strdup(&args[0]);
			अगर (!opts->ioअक्षरset) अणु
				pr_err("allocation failure for "
				       "iocharset string\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल Opt_debug:
			opts->debug = 1;
			अवरोध;
		शेष:
			pr_err("Unrecognized mount option \"%s\" "
			       "or missing value\n", p);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक befs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा befs_sb_info *befs_sb = BEFS_SB(root->d_sb);
	काष्ठा befs_mount_options *opts = &befs_sb->mount_opts;

	अगर (!uid_eq(opts->uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, opts->uid));
	अगर (!gid_eq(opts->gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, opts->gid));
	अगर (opts->ioअक्षरset)
		seq_म_लिखो(m, ",charset=%s", opts->ioअक्षरset);
	अगर (opts->debug)
		seq_माला_दो(m, ",debug");
	वापस 0;
पूर्ण

/* This function has the responsibiltiy of getting the
 * fileप्रणाली पढ़ोy क्रम unmounting.
 * Basically, we मुक्त everything that we allocated in
 * befs_पढ़ो_inode
 */
अटल व्योम
befs_put_super(काष्ठा super_block *sb)
अणु
	kमुक्त(BEFS_SB(sb)->mount_opts.ioअक्षरset);
	BEFS_SB(sb)->mount_opts.ioअक्षरset = शून्य;
	unload_nls(BEFS_SB(sb)->nls);
	kमुक्त(sb->s_fs_info);
	sb->s_fs_info = शून्य;
पूर्ण

/* Allocate निजी field of the superblock, fill it.
 *
 * Finish filling the खुला superblock fields
 * Make the root directory
 * Load a set of NLS translations अगर needed.
 */
अटल पूर्णांक
befs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा befs_sb_info *befs_sb;
	befs_super_block *disk_sb;
	काष्ठा inode *root;
	दीर्घ ret = -EINVAL;
	स्थिर अचिन्हित दीर्घ sb_block = 0;
	स्थिर off_t x86_sb_off = 512;
	पूर्णांक blocksize;

	sb->s_fs_info = kzalloc(माप(*befs_sb), GFP_KERNEL);
	अगर (sb->s_fs_info == शून्य)
		जाओ unacquire_none;

	befs_sb = BEFS_SB(sb);

	अगर (!parse_options((अक्षर *) data, &befs_sb->mount_opts)) अणु
		अगर (!silent)
			befs_error(sb, "cannot parse mount options");
		जाओ unacquire_priv_sbp;
	पूर्ण

	befs_debug(sb, "---> %s", __func__);

	अगर (!sb_rकरोnly(sb)) अणु
		befs_warning(sb,
			     "No write support. Marking filesystem read-only");
		sb->s_flags |= SB_RDONLY;
	पूर्ण

	/*
	 * Set dummy blocksize to पढ़ो super block.
	 * Will be set to real fs blocksize later.
	 *
	 * Linux 2.4.10 and later refuse to पढ़ो blocks smaller than
	 * the logical block size क्रम the device. But we also need to पढ़ो at
	 * least 1k to get the second 512 bytes of the volume.
	 */
	blocksize = sb_min_blocksize(sb, 1024);
	अगर (!blocksize) अणु
		अगर (!silent)
			befs_error(sb, "unable to set blocksize");
		जाओ unacquire_priv_sbp;
	पूर्ण

	bh = sb_bपढ़ो(sb, sb_block);
	अगर (!bh) अणु
		अगर (!silent)
			befs_error(sb, "unable to read superblock");
		जाओ unacquire_priv_sbp;
	पूर्ण

	/* account क्रम offset of super block on x86 */
	disk_sb = (befs_super_block *) bh->b_data;
	अगर ((disk_sb->magic1 == BEFS_SUPER_MAGIC1_LE) ||
	    (disk_sb->magic1 == BEFS_SUPER_MAGIC1_BE)) अणु
		befs_debug(sb, "Using PPC superblock location");
	पूर्ण अन्यथा अणु
		befs_debug(sb, "Using x86 superblock location");
		disk_sb =
		    (befs_super_block *) ((व्योम *) bh->b_data + x86_sb_off);
	पूर्ण

	अगर ((befs_load_sb(sb, disk_sb) != BEFS_OK) ||
	    (befs_check_sb(sb) != BEFS_OK))
		जाओ unacquire_bh;

	befs_dump_super_block(sb, disk_sb);

	brअन्यथा(bh);

	अगर (befs_sb->num_blocks > ~((sector_t)0)) अणु
		अगर (!silent)
			befs_error(sb, "blocks count: %llu is larger than the host can use",
					befs_sb->num_blocks);
		जाओ unacquire_priv_sbp;
	पूर्ण

	/*
	 * set up enough so that it can पढ़ो an inode
	 * Fill in kernel superblock fields from निजी sb
	 */
	sb->s_magic = BEFS_SUPER_MAGIC;
	/* Set real blocksize of fs */
	sb_set_blocksize(sb, (uदीर्घ) befs_sb->block_size);
	sb->s_op = &befs_sops;
	sb->s_export_op = &befs_export_operations;
	sb->s_समय_min = 0;
	sb->s_समय_max = 0xffffffffffffll;
	root = befs_iget(sb, iaddr2blockno(sb, &(befs_sb->root_dir)));
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);
		जाओ unacquire_priv_sbp;
	पूर्ण
	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		अगर (!silent)
			befs_error(sb, "get root inode failed");
		जाओ unacquire_priv_sbp;
	पूर्ण

	/* load nls library */
	अगर (befs_sb->mount_opts.ioअक्षरset) अणु
		befs_debug(sb, "Loading nls: %s",
			   befs_sb->mount_opts.ioअक्षरset);
		befs_sb->nls = load_nls(befs_sb->mount_opts.ioअक्षरset);
		अगर (!befs_sb->nls) अणु
			befs_warning(sb, "Cannot load nls %s"
					" loading default nls",
					befs_sb->mount_opts.ioअक्षरset);
			befs_sb->nls = load_nls_शेष();
		पूर्ण
	/* load शेष nls अगर none is specअगरied  in mount options */
	पूर्ण अन्यथा अणु
		befs_debug(sb, "Loading default nls");
		befs_sb->nls = load_nls_शेष();
	पूर्ण

	वापस 0;

unacquire_bh:
	brअन्यथा(bh);

unacquire_priv_sbp:
	kमुक्त(befs_sb->mount_opts.ioअक्षरset);
	kमुक्त(sb->s_fs_info);
	sb->s_fs_info = शून्य;

unacquire_none:
	वापस ret;
पूर्ण

अटल पूर्णांक
befs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	अगर (!(*flags & SB_RDONLY))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक
befs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	befs_debug(sb, "---> %s", __func__);

	buf->f_type = BEFS_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = BEFS_SB(sb)->num_blocks;
	buf->f_bमुक्त = BEFS_SB(sb)->num_blocks - BEFS_SB(sb)->used_blocks;
	buf->f_bavail = buf->f_bमुक्त;
	buf->f_files = 0;	/* UNKNOWN */
	buf->f_fमुक्त = 0;	/* UNKNOWN */
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen = BEFS_NAME_LEN;

	befs_debug(sb, "<--- %s", __func__);

	वापस 0;
पूर्ण

अटल काष्ठा dentry *
befs_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags, स्थिर अक्षर *dev_name,
	    व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, befs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type befs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "befs",
	.mount		= befs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("befs");

अटल पूर्णांक __init
init_befs_fs(व्योम)
अणु
	पूर्णांक err;

	pr_info("version: %s\n", BEFS_VERSION);

	err = befs_init_inodecache();
	अगर (err)
		जाओ unacquire_none;

	err = रेजिस्टर_fileप्रणाली(&befs_fs_type);
	अगर (err)
		जाओ unacquire_inodecache;

	वापस 0;

unacquire_inodecache:
	befs_destroy_inodecache();

unacquire_none:
	वापस err;
पूर्ण

अटल व्योम __निकास
निकास_befs_fs(व्योम)
अणु
	befs_destroy_inodecache();

	unरेजिस्टर_fileप्रणाली(&befs_fs_type);
पूर्ण

/*
 * Macros that typecheck the init and निकास functions,
 * ensures that they are called at init and cleanup,
 * and eliminates warnings about unused functions.
 */
module_init(init_befs_fs)
module_निकास(निकास_befs_fs)
