<शैली गुरु>
/* Block- or MTD-based romfs
 *
 * Copyright तऊ 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * Derived from: ROMFS file प्रणाली, Linux implementation
 *
 * Copyright तऊ 1997-1999  Janos Farkas <chexum@shaकरोw.banki.hu>
 *
 * Using parts of the minix fileप्रणाली
 * Copyright तऊ 1991, 1992  Linus Torvalds
 *
 * and parts of the affs fileप्रणाली additionally
 * Copyright तऊ 1993  Ray Burr
 * Copyright तऊ 1996  Hans-Joachim Widmaier
 *
 * Changes
 *					Changed क्रम 2.1.19 modules
 *	Jan 1997			Initial release
 *	Jun 1997			2.1.43+ changes
 *					Proper page locking in पढ़ोpage
 *					Changed to work with 2.1.45+ fs
 *	Jul 1997			Fixed follow_link
 *			2.1.47
 *					lookup shouldn't वापस -ENOENT
 *					from Horst von Bअक्रम:
 *					  fail on wrong checksum
 *					  द्विगुन unlock_super was possible
 *					  correct namelen क्रम statfs
 *					spotted by Bill Hawes:
 *					  पढ़ोlink shouldn't iput()
 *	Jun 1998	2.1.106		from Avery Pennarun: glibc scandir()
 *					  exposed a problem in सूची_पढ़ो
 *			2.1.107		code-मुक्तze spellchecker run
 *	Aug 1998			2.1.118+ VFS changes
 *	Sep 1998	2.1.122		another VFS change (follow_link)
 *	Apr 1999	2.2.7		no more EBADF checking in
 *					  lookup/सूची_पढ़ो, use ERR_PTR
 *	Jun 1999	2.3.6		d_alloc_root use changed
 *			2.3.9		clean up usage of ENOENT/negative
 *					  dentries in lookup
 *					clean up page flags setting
 *					  (error, uptodate, locking) in
 *					  in पढ़ोpage
 *					use init_special_inode क्रम
 *					  fअगरos/sockets (and streamline) in
 *					  पढ़ो_inode, fix _ops table order
 *	Aug 1999	2.3.16		__initfunc() => __init change
 *	Oct 1999	2.3.24		page->owner hack obsoleted
 *	Nov 1999	2.3.27		2.3.25+ page->offset => index change
 *
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/statfs.h>
#समावेश <linux/mtd/super.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/major.h>
#समावेश "internal.h"

अटल काष्ठा kmem_cache *romfs_inode_cachep;

अटल स्थिर umode_t romfs_modemap[8] = अणु
	0,			/* hard link */
	S_IFसूची  | 0644,	/* directory */
	S_IFREG  | 0644,	/* regular file */
	S_IFLNK  | 0777,	/* symlink */
	S_IFBLK  | 0600,	/* blockdev */
	S_IFCHR  | 0600,	/* अक्षरdev */
	S_IFSOCK | 0644,	/* socket */
	S_IFIFO  | 0644		/* FIFO */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर romfs_dtype_table[] = अणु
	DT_UNKNOWN, DT_सूची, DT_REG, DT_LNK, DT_BLK, DT_CHR, DT_SOCK, DT_FIFO
पूर्ण;

अटल काष्ठा inode *romfs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ pos);

/*
 * पढ़ो a page worth of data from the image
 */
अटल पूर्णांक romfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	loff_t offset, size;
	अचिन्हित दीर्घ fillsize, pos;
	व्योम *buf;
	पूर्णांक ret;

	buf = kmap(page);
	अगर (!buf)
		वापस -ENOMEM;

	/* 32 bit warning -- but not क्रम us :) */
	offset = page_offset(page);
	size = i_size_पढ़ो(inode);
	fillsize = 0;
	ret = 0;
	अगर (offset < size) अणु
		size -= offset;
		fillsize = size > PAGE_SIZE ? PAGE_SIZE : size;

		pos = ROMFS_I(inode)->i_dataoffset + offset;

		ret = romfs_dev_पढ़ो(inode->i_sb, pos, buf, fillsize);
		अगर (ret < 0) अणु
			SetPageError(page);
			fillsize = 0;
			ret = -EIO;
		पूर्ण
	पूर्ण

	अगर (fillsize < PAGE_SIZE)
		स_रखो(buf + fillsize, 0, PAGE_SIZE - fillsize);
	अगर (ret == 0)
		SetPageUptodate(page);

	flush_dcache_page(page);
	kunmap(page);
	unlock_page(page);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा address_space_operations romfs_aops = अणु
	.पढ़ोpage	= romfs_पढ़ोpage
पूर्ण;

/*
 * पढ़ो the entries from a directory
 */
अटल पूर्णांक romfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *i = file_inode(file);
	काष्ठा romfs_inode ri;
	अचिन्हित दीर्घ offset, maxoff;
	पूर्णांक j, ino, nextfh;
	अक्षर fsname[ROMFS_MAXFN];	/* XXX dynamic? */
	पूर्णांक ret;

	maxoff = romfs_maxsize(i->i_sb);

	offset = ctx->pos;
	अगर (!offset) अणु
		offset = i->i_ino & ROMFH_MASK;
		ret = romfs_dev_पढ़ो(i->i_sb, offset, &ri, ROMFH_SIZE);
		अगर (ret < 0)
			जाओ out;
		offset = be32_to_cpu(ri.spec) & ROMFH_MASK;
	पूर्ण

	/* Not really failsafe, but we are पढ़ो-only... */
	क्रम (;;) अणु
		अगर (!offset || offset >= maxoff) अणु
			offset = maxoff;
			ctx->pos = offset;
			जाओ out;
		पूर्ण
		ctx->pos = offset;

		/* Fetch inode info */
		ret = romfs_dev_पढ़ो(i->i_sb, offset, &ri, ROMFH_SIZE);
		अगर (ret < 0)
			जाओ out;

		j = romfs_dev_strnlen(i->i_sb, offset + ROMFH_SIZE,
				      माप(fsname) - 1);
		अगर (j < 0)
			जाओ out;

		ret = romfs_dev_पढ़ो(i->i_sb, offset + ROMFH_SIZE, fsname, j);
		अगर (ret < 0)
			जाओ out;
		fsname[j] = '\0';

		ino = offset;
		nextfh = be32_to_cpu(ri.next);
		अगर ((nextfh & ROMFH_TYPE) == ROMFH_HRD)
			ino = be32_to_cpu(ri.spec);
		अगर (!dir_emit(ctx, fsname, j, ino,
			    romfs_dtype_table[nextfh & ROMFH_TYPE]))
			जाओ out;

		offset = nextfh & ROMFH_MASK;
	पूर्ण
out:
	वापस 0;
पूर्ण

/*
 * look up an entry in a directory
 */
अटल काष्ठा dentry *romfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				   अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ offset, maxoff;
	काष्ठा inode *inode = शून्य;
	काष्ठा romfs_inode ri;
	स्थिर अक्षर *name;		/* got from dentry */
	पूर्णांक len, ret;

	offset = dir->i_ino & ROMFH_MASK;
	ret = romfs_dev_पढ़ो(dir->i_sb, offset, &ri, ROMFH_SIZE);
	अगर (ret < 0)
		जाओ error;

	/* search all the file entries in the list starting from the one
	 * poपूर्णांकed to by the directory's special data */
	maxoff = romfs_maxsize(dir->i_sb);
	offset = be32_to_cpu(ri.spec) & ROMFH_MASK;

	name = dentry->d_name.name;
	len = dentry->d_name.len;

	क्रम (;;) अणु
		अगर (!offset || offset >= maxoff)
			अवरोध;

		ret = romfs_dev_पढ़ो(dir->i_sb, offset, &ri, माप(ri));
		अगर (ret < 0)
			जाओ error;

		/* try to match the first 16 bytes of name */
		ret = romfs_dev_म_भेद(dir->i_sb, offset + ROMFH_SIZE, name,
				       len);
		अगर (ret < 0)
			जाओ error;
		अगर (ret == 1) अणु
			/* Hard link handling */
			अगर ((be32_to_cpu(ri.next) & ROMFH_TYPE) == ROMFH_HRD)
				offset = be32_to_cpu(ri.spec) & ROMFH_MASK;
			inode = romfs_iget(dir->i_sb, offset);
			अवरोध;
		पूर्ण

		/* next entry */
		offset = be32_to_cpu(ri.next) & ROMFH_MASK;
	पूर्ण

	वापस d_splice_alias(inode, dentry);
error:
	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा file_operations romfs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= romfs_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा inode_operations romfs_dir_inode_operations = अणु
	.lookup		= romfs_lookup,
पूर्ण;

/*
 * get a romfs inode based on its position in the image (which द्विगुनs as the
 * inode number)
 */
अटल काष्ठा inode *romfs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ pos)
अणु
	काष्ठा romfs_inode_info *inode;
	काष्ठा romfs_inode ri;
	काष्ठा inode *i;
	अचिन्हित दीर्घ nlen;
	अचिन्हित nextfh;
	पूर्णांक ret;
	umode_t mode;

	/* we might have to traverse a chain of "hard link" file entries to get
	 * to the actual file */
	क्रम (;;) अणु
		ret = romfs_dev_पढ़ो(sb, pos, &ri, माप(ri));
		अगर (ret < 0)
			जाओ error;

		/* XXX: करो romfs_checksum here too (with name) */

		nextfh = be32_to_cpu(ri.next);
		अगर ((nextfh & ROMFH_TYPE) != ROMFH_HRD)
			अवरोध;

		pos = be32_to_cpu(ri.spec) & ROMFH_MASK;
	पूर्ण

	/* determine the length of the filename */
	nlen = romfs_dev_strnlen(sb, pos + ROMFH_SIZE, ROMFS_MAXFN);
	अगर (IS_ERR_VALUE(nlen))
		जाओ eio;

	/* get an inode क्रम this image position */
	i = iget_locked(sb, pos);
	अगर (!i)
		वापस ERR_PTR(-ENOMEM);

	अगर (!(i->i_state & I_NEW))
		वापस i;

	/* precalculate the data offset */
	inode = ROMFS_I(i);
	inode->i_metasize = (ROMFH_SIZE + nlen + 1 + ROMFH_PAD) & ROMFH_MASK;
	inode->i_dataoffset = pos + inode->i_metasize;

	set_nlink(i, 1);		/* Hard to decide.. */
	i->i_size = be32_to_cpu(ri.size);
	i->i_mसमय.tv_sec = i->i_aसमय.tv_sec = i->i_स_समय.tv_sec = 0;
	i->i_mसमय.tv_nsec = i->i_aसमय.tv_nsec = i->i_स_समय.tv_nsec = 0;

	/* set up mode and ops */
	mode = romfs_modemap[nextfh & ROMFH_TYPE];

	चयन (nextfh & ROMFH_TYPE) अणु
	हाल ROMFH_सूची:
		i->i_size = ROMFS_I(i)->i_metasize;
		i->i_op = &romfs_dir_inode_operations;
		i->i_fop = &romfs_dir_operations;
		अगर (nextfh & ROMFH_EXEC)
			mode |= S_IXUGO;
		अवरोध;
	हाल ROMFH_REG:
		i->i_fop = &romfs_ro_fops;
		i->i_data.a_ops = &romfs_aops;
		अगर (nextfh & ROMFH_EXEC)
			mode |= S_IXUGO;
		अवरोध;
	हाल ROMFH_SYM:
		i->i_op = &page_symlink_inode_operations;
		inode_nohighmem(i);
		i->i_data.a_ops = &romfs_aops;
		mode |= S_IRWXUGO;
		अवरोध;
	शेष:
		/* depending on MBZ क्रम sock/fअगरos */
		nextfh = be32_to_cpu(ri.spec);
		init_special_inode(i, mode, MKDEV(nextfh >> 16,
						  nextfh & 0xffff));
		अवरोध;
	पूर्ण

	i->i_mode = mode;
	i->i_blocks = (i->i_size + 511) >> 9;

	unlock_new_inode(i);
	वापस i;

eio:
	ret = -EIO;
error:
	pr_err("read error for inode 0x%lx\n", pos);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * allocate a new inode
 */
अटल काष्ठा inode *romfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा romfs_inode_info *inode;

	inode = kmem_cache_alloc(romfs_inode_cachep, GFP_KERNEL);
	वापस inode ? &inode->vfs_inode : शून्य;
पूर्ण

/*
 * वापस a spent inode to the slab cache
 */
अटल व्योम romfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(romfs_inode_cachep, ROMFS_I(inode));
पूर्ण

/*
 * get fileप्रणाली statistics
 */
अटल पूर्णांक romfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	u64 id = 0;

	/* When calling huge_encode_dev(),
	 * use sb->s_bdev->bd_dev when,
	 *   - CONFIG_ROMFS_ON_BLOCK defined
	 * use sb->s_dev when,
	 *   - CONFIG_ROMFS_ON_BLOCK undefined and
	 *   - CONFIG_ROMFS_ON_MTD defined
	 * leave id as 0 when,
	 *   - CONFIG_ROMFS_ON_BLOCK undefined and
	 *   - CONFIG_ROMFS_ON_MTD undefined
	 */
	अगर (sb->s_bdev)
		id = huge_encode_dev(sb->s_bdev->bd_dev);
	अन्यथा अगर (sb->s_dev)
		id = huge_encode_dev(sb->s_dev);

	buf->f_type = ROMFS_MAGIC;
	buf->f_namelen = ROMFS_MAXFN;
	buf->f_bsize = ROMBSIZE;
	buf->f_bमुक्त = buf->f_bavail = buf->f_fमुक्त;
	buf->f_blocks =
		(romfs_maxsize(dentry->d_sb) + ROMBSIZE - 1) >> ROMBSBITS;
	buf->f_fsid = u64_to_fsid(id);
	वापस 0;
पूर्ण

/*
 * remounting must involve पढ़ो-only
 */
अटल पूर्णांक romfs_reconfigure(काष्ठा fs_context *fc)
अणु
	sync_fileप्रणाली(fc->root->d_sb);
	fc->sb_flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations romfs_super_ops = अणु
	.alloc_inode	= romfs_alloc_inode,
	.मुक्त_inode	= romfs_मुक्त_inode,
	.statfs		= romfs_statfs,
पूर्ण;

/*
 * checksum check on part of a romfs fileप्रणाली
 */
अटल __u32 romfs_checksum(स्थिर व्योम *data, पूर्णांक size)
अणु
	स्थिर __be32 *ptr = data;
	__u32 sum;

	sum = 0;
	size >>= 2;
	जबतक (size > 0) अणु
		sum += be32_to_cpu(*ptr++);
		size--;
	पूर्ण
	वापस sum;
पूर्ण

/*
 * fill in the superblock
 */
अटल पूर्णांक romfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा romfs_super_block *rsb;
	काष्ठा inode *root;
	अचिन्हित दीर्घ pos, img_size;
	स्थिर अक्षर *storage;
	माप_प्रकार len;
	पूर्णांक ret;

#अगर_घोषित CONFIG_BLOCK
	अगर (!sb->s_mtd) अणु
		sb_set_blocksize(sb, ROMBSIZE);
	पूर्ण अन्यथा अणु
		sb->s_blocksize = ROMBSIZE;
		sb->s_blocksize_bits = blksize_bits(ROMBSIZE);
	पूर्ण
#पूर्ण_अगर

	sb->s_maxbytes = 0xFFFFFFFF;
	sb->s_magic = ROMFS_MAGIC;
	sb->s_flags |= SB_RDONLY | SB_NOATIME;
	sb->s_समय_min = 0;
	sb->s_समय_max = 0;
	sb->s_op = &romfs_super_ops;

#अगर_घोषित CONFIG_ROMFS_ON_MTD
	/* Use same dev ID from the underlying mtdblock device */
	अगर (sb->s_mtd)
		sb->s_dev = MKDEV(MTD_BLOCK_MAJOR, sb->s_mtd->index);
#पूर्ण_अगर
	/* पढ़ो the image superblock and check it */
	rsb = kदो_स्मृति(512, GFP_KERNEL);
	अगर (!rsb)
		वापस -ENOMEM;

	sb->s_fs_info = (व्योम *) 512;
	ret = romfs_dev_पढ़ो(sb, 0, rsb, 512);
	अगर (ret < 0)
		जाओ error_rsb;

	img_size = be32_to_cpu(rsb->size);

	अगर (sb->s_mtd && img_size > sb->s_mtd->size)
		जाओ error_rsb_inval;

	sb->s_fs_info = (व्योम *) img_size;

	अगर (rsb->word0 != ROMSB_WORD0 || rsb->word1 != ROMSB_WORD1 ||
	    img_size < ROMFH_SIZE) अणु
		अगर (!(fc->sb_flags & SB_SILENT))
			errorf(fc, "VFS: Can't find a romfs filesystem on dev %s.\n",
			       sb->s_id);
		जाओ error_rsb_inval;
	पूर्ण

	अगर (romfs_checksum(rsb, min_t(माप_प्रकार, img_size, 512))) अणु
		pr_err("bad initial checksum on dev %s.\n", sb->s_id);
		जाओ error_rsb_inval;
	पूर्ण

	storage = sb->s_mtd ? "MTD" : "the block layer";

	len = strnlen(rsb->name, ROMFS_MAXFN);
	अगर (!(fc->sb_flags & SB_SILENT))
		pr_notice("Mounting image '%*.*s' through %s\n",
			  (अचिन्हित) len, (अचिन्हित) len, rsb->name, storage);

	kमुक्त(rsb);
	rsb = शून्य;

	/* find the root directory */
	pos = (ROMFH_SIZE + len + 1 + ROMFH_PAD) & ROMFH_MASK;

	root = romfs_iget(sb, pos);
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	sb->s_root = d_make_root(root);
	अगर (!sb->s_root)
		वापस -ENOMEM;

	वापस 0;

error_rsb_inval:
	ret = -EINVAL;
error_rsb:
	kमुक्त(rsb);
	वापस ret;
पूर्ण

/*
 * get a superblock क्रम mounting
 */
अटल पूर्णांक romfs_get_tree(काष्ठा fs_context *fc)
अणु
	पूर्णांक ret = -EINVAL;

#अगर_घोषित CONFIG_ROMFS_ON_MTD
	ret = get_tree_mtd(fc, romfs_fill_super);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ROMFS_ON_BLOCK
	अगर (ret == -EINVAL)
		ret = get_tree_bdev(fc, romfs_fill_super);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations romfs_context_ops = अणु
	.get_tree	= romfs_get_tree,
	.reconfigure	= romfs_reconfigure,
पूर्ण;

/*
 * Set up the fileप्रणाली mount context.
 */
अटल पूर्णांक romfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &romfs_context_ops;
	वापस 0;
पूर्ण

/*
 * destroy a romfs superblock in the appropriate manner
 */
अटल व्योम romfs_समाप्त_sb(काष्ठा super_block *sb)
अणु
#अगर_घोषित CONFIG_ROMFS_ON_MTD
	अगर (sb->s_mtd) अणु
		समाप्त_mtd_super(sb);
		वापस;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ROMFS_ON_BLOCK
	अगर (sb->s_bdev) अणु
		समाप्त_block_super(sb);
		वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल काष्ठा file_प्रणाली_type romfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "romfs",
	.init_fs_context = romfs_init_fs_context,
	.समाप्त_sb	= romfs_समाप्त_sb,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("romfs");

/*
 * inode storage initialiser
 */
अटल व्योम romfs_i_init_once(व्योम *_inode)
अणु
	काष्ठा romfs_inode_info *inode = _inode;

	inode_init_once(&inode->vfs_inode);
पूर्ण

/*
 * romfs module initialisation
 */
अटल पूर्णांक __init init_romfs_fs(व्योम)
अणु
	पूर्णांक ret;

	pr_info("ROMFS MTD (C) 2007 Red Hat, Inc.\n");

	romfs_inode_cachep =
		kmem_cache_create("romfs_i",
				  माप(काष्ठा romfs_inode_info), 0,
				  SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD |
				  SLAB_ACCOUNT, romfs_i_init_once);

	अगर (!romfs_inode_cachep) अणु
		pr_err("Failed to initialise inode cache\n");
		वापस -ENOMEM;
	पूर्ण
	ret = रेजिस्टर_fileप्रणाली(&romfs_fs_type);
	अगर (ret) अणु
		pr_err("Failed to register filesystem\n");
		जाओ error_रेजिस्टर;
	पूर्ण
	वापस 0;

error_रेजिस्टर:
	kmem_cache_destroy(romfs_inode_cachep);
	वापस ret;
पूर्ण

/*
 * romfs module removal
 */
अटल व्योम __निकास निकास_romfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&romfs_fs_type);
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(romfs_inode_cachep);
पूर्ण

module_init(init_romfs_fs);
module_निकास(निकास_romfs_fs);

MODULE_DESCRIPTION("Direct-MTD Capable RomFS");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL"); /* Actually dual-licensed, but it करोesn't matter क्रम */
