<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * super.c
 */

/*
 * This file implements code to पढ़ो the superblock, पढ़ो and initialise
 * in-memory काष्ठाures at mount समय, and all the VFS glue code to रेजिस्टर
 * the fileप्रणाली.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/magic.h>
#समावेश <linux/xattr.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"
#समावेश "decompressor.h"
#समावेश "xattr.h"

अटल काष्ठा file_प्रणाली_type squashfs_fs_type;
अटल स्थिर काष्ठा super_operations squashfs_super_ops;

अटल स्थिर काष्ठा squashfs_decompressor *supported_squashfs_fileप्रणाली(
	काष्ठा fs_context *fc,
	लघु major, लघु minor, लघु id)
अणु
	स्थिर काष्ठा squashfs_decompressor *decompressor;

	अगर (major < SQUASHFS_MAJOR) अणु
		errorf(fc, "Major/Minor mismatch, older Squashfs %d.%d "
		       "filesystems are unsupported", major, minor);
		वापस शून्य;
	पूर्ण अन्यथा अगर (major > SQUASHFS_MAJOR || minor > SQUASHFS_MINOR) अणु
		errorf(fc, "Major/Minor mismatch, trying to mount newer "
		       "%d.%d filesystem", major, minor);
		errorf(fc, "Please update your kernel");
		वापस शून्य;
	पूर्ण

	decompressor = squashfs_lookup_decompressor(id);
	अगर (!decompressor->supported) अणु
		errorf(fc, "Filesystem uses \"%s\" compression. This is not supported",
		       decompressor->name);
		वापस शून्य;
	पूर्ण

	वापस decompressor;
पूर्ण


अटल पूर्णांक squashfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा squashfs_sb_info *msblk;
	काष्ठा squashfs_super_block *sblk = शून्य;
	काष्ठा inode *root;
	दीर्घ दीर्घ root_inode;
	अचिन्हित लघु flags;
	अचिन्हित पूर्णांक fragments;
	u64 lookup_table_start, xattr_id_table_start, next_table;
	पूर्णांक err;

	TRACE("Entered squashfs_fill_superblock\n");

	sb->s_fs_info = kzalloc(माप(*msblk), GFP_KERNEL);
	अगर (sb->s_fs_info == शून्य) अणु
		ERROR("Failed to allocate squashfs_sb_info\n");
		वापस -ENOMEM;
	पूर्ण
	msblk = sb->s_fs_info;

	msblk->devblksize = sb_min_blocksize(sb, SQUASHFS_DEVBLK_SIZE);
	msblk->devblksize_log2 = ffz(~msblk->devblksize);

	mutex_init(&msblk->meta_index_mutex);

	/*
	 * msblk->bytes_used is checked in squashfs_पढ़ो_table to ensure पढ़ोs
	 * are not beyond fileप्रणाली end.  But as we're using
	 * squashfs_पढ़ो_table here to पढ़ो the superblock (including the value
	 * of bytes_used) we need to set it to an initial sensible dummy value
	 */
	msblk->bytes_used = माप(*sblk);
	sblk = squashfs_पढ़ो_table(sb, SQUASHFS_START, माप(*sblk));

	अगर (IS_ERR(sblk)) अणु
		errorf(fc, "unable to read squashfs_super_block");
		err = PTR_ERR(sblk);
		sblk = शून्य;
		जाओ failed_mount;
	पूर्ण

	err = -EINVAL;

	/* Check it is a SQUASHFS superblock */
	sb->s_magic = le32_to_cpu(sblk->s_magic);
	अगर (sb->s_magic != SQUASHFS_MAGIC) अणु
		अगर (!(fc->sb_flags & SB_SILENT))
			errorf(fc, "Can't find a SQUASHFS superblock on %pg",
			       sb->s_bdev);
		जाओ failed_mount;
	पूर्ण

	/* Check the MAJOR & MINOR versions and lookup compression type */
	msblk->decompressor = supported_squashfs_fileप्रणाली(
			fc,
			le16_to_cpu(sblk->s_major),
			le16_to_cpu(sblk->s_minor),
			le16_to_cpu(sblk->compression));
	अगर (msblk->decompressor == शून्य)
		जाओ failed_mount;

	/* Check the fileप्रणाली करोes not extend beyond the end of the
	   block device */
	msblk->bytes_used = le64_to_cpu(sblk->bytes_used);
	अगर (msblk->bytes_used < 0 || msblk->bytes_used >
			i_size_पढ़ो(sb->s_bdev->bd_inode))
		जाओ failed_mount;

	/* Check block size क्रम sanity */
	msblk->block_size = le32_to_cpu(sblk->block_size);
	अगर (msblk->block_size > SQUASHFS_खाता_MAX_SIZE)
		जाओ insanity;

	/*
	 * Check the प्रणाली page size is not larger than the fileप्रणाली
	 * block size (by शेष 128K).  This is currently not supported.
	 */
	अगर (PAGE_SIZE > msblk->block_size) अणु
		errorf(fc, "Page size > filesystem block size (%d).  This is "
		       "currently not supported!", msblk->block_size);
		जाओ failed_mount;
	पूर्ण

	/* Check block log क्रम sanity */
	msblk->block_log = le16_to_cpu(sblk->block_log);
	अगर (msblk->block_log > SQUASHFS_खाता_MAX_LOG)
		जाओ failed_mount;

	/* Check that block_size and block_log match */
	अगर (msblk->block_size != (1 << msblk->block_log))
		जाओ insanity;

	/* Check the root inode क्रम sanity */
	root_inode = le64_to_cpu(sblk->root_inode);
	अगर (SQUASHFS_INODE_OFFSET(root_inode) > SQUASHFS_METADATA_SIZE)
		जाओ insanity;

	msblk->inode_table = le64_to_cpu(sblk->inode_table_start);
	msblk->directory_table = le64_to_cpu(sblk->directory_table_start);
	msblk->inodes = le32_to_cpu(sblk->inodes);
	msblk->fragments = le32_to_cpu(sblk->fragments);
	msblk->ids = le16_to_cpu(sblk->no_ids);
	flags = le16_to_cpu(sblk->flags);

	TRACE("Found valid superblock on %pg\n", sb->s_bdev);
	TRACE("Inodes are %scompressed\n", SQUASHFS_UNCOMPRESSED_INODES(flags)
				? "un" : "");
	TRACE("Data is %scompressed\n", SQUASHFS_UNCOMPRESSED_DATA(flags)
				? "un" : "");
	TRACE("Filesystem size %lld bytes\n", msblk->bytes_used);
	TRACE("Block size %d\n", msblk->block_size);
	TRACE("Number of inodes %d\n", msblk->inodes);
	TRACE("Number of fragments %d\n", msblk->fragments);
	TRACE("Number of ids %d\n", msblk->ids);
	TRACE("sblk->inode_table_start %llx\n", msblk->inode_table);
	TRACE("sblk->directory_table_start %llx\n", msblk->directory_table);
	TRACE("sblk->fragment_table_start %llx\n",
		(u64) le64_to_cpu(sblk->fragment_table_start));
	TRACE("sblk->id_table_start %llx\n",
		(u64) le64_to_cpu(sblk->id_table_start));

	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_समय_min = 0;
	sb->s_समय_max = U32_MAX;
	sb->s_flags |= SB_RDONLY;
	sb->s_op = &squashfs_super_ops;

	err = -ENOMEM;

	msblk->block_cache = squashfs_cache_init("metadata",
			SQUASHFS_CACHED_BLKS, SQUASHFS_METADATA_SIZE);
	अगर (msblk->block_cache == शून्य)
		जाओ failed_mount;

	/* Allocate पढ़ो_page block */
	msblk->पढ़ो_page = squashfs_cache_init("data",
		squashfs_max_decompressors(), msblk->block_size);
	अगर (msblk->पढ़ो_page == शून्य) अणु
		errorf(fc, "Failed to allocate read_page block");
		जाओ failed_mount;
	पूर्ण

	msblk->stream = squashfs_decompressor_setup(sb, flags);
	अगर (IS_ERR(msblk->stream)) अणु
		err = PTR_ERR(msblk->stream);
		msblk->stream = शून्य;
		जाओ insanity;
	पूर्ण

	/* Handle xattrs */
	sb->s_xattr = squashfs_xattr_handlers;
	xattr_id_table_start = le64_to_cpu(sblk->xattr_id_table_start);
	अगर (xattr_id_table_start == SQUASHFS_INVALID_BLK) अणु
		next_table = msblk->bytes_used;
		जाओ allocate_id_index_table;
	पूर्ण

	/* Allocate and पढ़ो xattr id lookup table */
	msblk->xattr_id_table = squashfs_पढ़ो_xattr_id_table(sb,
		xattr_id_table_start, &msblk->xattr_table, &msblk->xattr_ids);
	अगर (IS_ERR(msblk->xattr_id_table)) अणु
		errorf(fc, "unable to read xattr id index table");
		err = PTR_ERR(msblk->xattr_id_table);
		msblk->xattr_id_table = शून्य;
		अगर (err != -ENOTSUPP)
			जाओ failed_mount;
	पूर्ण
	next_table = msblk->xattr_table;

allocate_id_index_table:
	/* Allocate and पढ़ो id index table */
	msblk->id_table = squashfs_पढ़ो_id_index_table(sb,
		le64_to_cpu(sblk->id_table_start), next_table, msblk->ids);
	अगर (IS_ERR(msblk->id_table)) अणु
		errorf(fc, "unable to read id index table");
		err = PTR_ERR(msblk->id_table);
		msblk->id_table = शून्य;
		जाओ failed_mount;
	पूर्ण
	next_table = le64_to_cpu(msblk->id_table[0]);

	/* Handle inode lookup table */
	lookup_table_start = le64_to_cpu(sblk->lookup_table_start);
	अगर (lookup_table_start == SQUASHFS_INVALID_BLK)
		जाओ handle_fragments;

	/* Allocate and पढ़ो inode lookup table */
	msblk->inode_lookup_table = squashfs_पढ़ो_inode_lookup_table(sb,
		lookup_table_start, next_table, msblk->inodes);
	अगर (IS_ERR(msblk->inode_lookup_table)) अणु
		errorf(fc, "unable to read inode lookup table");
		err = PTR_ERR(msblk->inode_lookup_table);
		msblk->inode_lookup_table = शून्य;
		जाओ failed_mount;
	पूर्ण
	next_table = le64_to_cpu(msblk->inode_lookup_table[0]);

	sb->s_export_op = &squashfs_export_ops;

handle_fragments:
	fragments = msblk->fragments;
	अगर (fragments == 0)
		जाओ check_directory_table;

	msblk->fragment_cache = squashfs_cache_init("fragment",
		SQUASHFS_CACHED_FRAGMENTS, msblk->block_size);
	अगर (msblk->fragment_cache == शून्य) अणु
		err = -ENOMEM;
		जाओ failed_mount;
	पूर्ण

	/* Allocate and पढ़ो fragment index table */
	msblk->fragment_index = squashfs_पढ़ो_fragment_index_table(sb,
		le64_to_cpu(sblk->fragment_table_start), next_table, fragments);
	अगर (IS_ERR(msblk->fragment_index)) अणु
		errorf(fc, "unable to read fragment index table");
		err = PTR_ERR(msblk->fragment_index);
		msblk->fragment_index = शून्य;
		जाओ failed_mount;
	पूर्ण
	next_table = le64_to_cpu(msblk->fragment_index[0]);

check_directory_table:
	/* Sanity check directory_table */
	अगर (msblk->directory_table > next_table) अणु
		err = -EINVAL;
		जाओ insanity;
	पूर्ण

	/* Sanity check inode_table */
	अगर (msblk->inode_table >= msblk->directory_table) अणु
		err = -EINVAL;
		जाओ insanity;
	पूर्ण

	/* allocate root */
	root = new_inode(sb);
	अगर (!root) अणु
		err = -ENOMEM;
		जाओ failed_mount;
	पूर्ण

	err = squashfs_पढ़ो_inode(root, root_inode);
	अगर (err) अणु
		make_bad_inode(root);
		iput(root);
		जाओ failed_mount;
	पूर्ण
	insert_inode_hash(root);

	sb->s_root = d_make_root(root);
	अगर (sb->s_root == शून्य) अणु
		ERROR("Root inode create failed\n");
		err = -ENOMEM;
		जाओ failed_mount;
	पूर्ण

	TRACE("Leaving squashfs_fill_super\n");
	kमुक्त(sblk);
	वापस 0;

insanity:
	errorf(fc, "squashfs image failed sanity check");
failed_mount:
	squashfs_cache_delete(msblk->block_cache);
	squashfs_cache_delete(msblk->fragment_cache);
	squashfs_cache_delete(msblk->पढ़ो_page);
	squashfs_decompressor_destroy(msblk);
	kमुक्त(msblk->inode_lookup_table);
	kमुक्त(msblk->fragment_index);
	kमुक्त(msblk->id_table);
	kमुक्त(msblk->xattr_id_table);
	kमुक्त(sb->s_fs_info);
	sb->s_fs_info = शून्य;
	kमुक्त(sblk);
	वापस err;
पूर्ण

अटल पूर्णांक squashfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_bdev(fc, squashfs_fill_super);
पूर्ण

अटल पूर्णांक squashfs_reconfigure(काष्ठा fs_context *fc)
अणु
	sync_fileप्रणाली(fc->root->d_sb);
	fc->sb_flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations squashfs_context_ops = अणु
	.get_tree	= squashfs_get_tree,
	.reconfigure	= squashfs_reconfigure,
पूर्ण;

अटल पूर्णांक squashfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &squashfs_context_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक squashfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा squashfs_sb_info *msblk = dentry->d_sb->s_fs_info;
	u64 id = huge_encode_dev(dentry->d_sb->s_bdev->bd_dev);

	TRACE("Entered squashfs_statfs\n");

	buf->f_type = SQUASHFS_MAGIC;
	buf->f_bsize = msblk->block_size;
	buf->f_blocks = ((msblk->bytes_used - 1) >> msblk->block_log) + 1;
	buf->f_bमुक्त = buf->f_bavail = 0;
	buf->f_files = msblk->inodes;
	buf->f_fमुक्त = 0;
	buf->f_namelen = SQUASHFS_NAME_LEN;
	buf->f_fsid = u64_to_fsid(id);

	वापस 0;
पूर्ण


अटल व्योम squashfs_put_super(काष्ठा super_block *sb)
अणु
	अगर (sb->s_fs_info) अणु
		काष्ठा squashfs_sb_info *sbi = sb->s_fs_info;
		squashfs_cache_delete(sbi->block_cache);
		squashfs_cache_delete(sbi->fragment_cache);
		squashfs_cache_delete(sbi->पढ़ो_page);
		squashfs_decompressor_destroy(sbi);
		kमुक्त(sbi->id_table);
		kमुक्त(sbi->fragment_index);
		kमुक्त(sbi->meta_index);
		kमुक्त(sbi->inode_lookup_table);
		kमुक्त(sbi->xattr_id_table);
		kमुक्त(sb->s_fs_info);
		sb->s_fs_info = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा kmem_cache *squashfs_inode_cachep;


अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा squashfs_inode_info *ei = foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण


अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	squashfs_inode_cachep = kmem_cache_create("squashfs_inode_cache",
		माप(काष्ठा squashfs_inode_info), 0,
		SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|SLAB_ACCOUNT,
		init_once);

	वापस squashfs_inode_cachep ? 0 : -ENOMEM;
पूर्ण


अटल व्योम destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(squashfs_inode_cachep);
पूर्ण


अटल पूर्णांक __init init_squashfs_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();

	अगर (err)
		वापस err;

	err = रेजिस्टर_fileप्रणाली(&squashfs_fs_type);
	अगर (err) अणु
		destroy_inodecache();
		वापस err;
	पूर्ण

	pr_info("version 4.0 (2009/01/31) Phillip Lougher\n");

	वापस 0;
पूर्ण


अटल व्योम __निकास निकास_squashfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&squashfs_fs_type);
	destroy_inodecache();
पूर्ण


अटल काष्ठा inode *squashfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा squashfs_inode_info *ei =
		kmem_cache_alloc(squashfs_inode_cachep, GFP_KERNEL);

	वापस ei ? &ei->vfs_inode : शून्य;
पूर्ण


अटल व्योम squashfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(squashfs_inode_cachep, squashfs_i(inode));
पूर्ण

अटल काष्ठा file_प्रणाली_type squashfs_fs_type = अणु
	.owner = THIS_MODULE,
	.name = "squashfs",
	.init_fs_context = squashfs_init_fs_context,
	.समाप्त_sb = समाप्त_block_super,
	.fs_flags = FS_REQUIRES_DEV
पूर्ण;
MODULE_ALIAS_FS("squashfs");

अटल स्थिर काष्ठा super_operations squashfs_super_ops = अणु
	.alloc_inode = squashfs_alloc_inode,
	.मुक्त_inode = squashfs_मुक्त_inode,
	.statfs = squashfs_statfs,
	.put_super = squashfs_put_super,
पूर्ण;

module_init(init_squashfs_fs);
module_निकास(निकास_squashfs_fs);
MODULE_DESCRIPTION("squashfs 4.0, a compressed read-only filesystem");
MODULE_AUTHOR("Phillip Lougher <phillip@squashfs.org.uk>");
MODULE_LICENSE("GPL");
