<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QNX4 file प्रणाली, Linux implementation.
 *
 * Version : 0.2.1
 *
 * Using parts of the xiafs fileप्रणाली.
 *
 * History :
 *
 * 01-06-1998 by Riअक्षरd Frowijn : first release.
 * 20-06-1998 by Frank Denis : Linux 2.1.99+ support, boot signature, misc.
 * 30-06-1998 by Frank Denis : first step to ग_लिखो inodes.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/highuid.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/statfs.h>
#समावेश "qnx4.h"

#घोषणा QNX4_VERSION  4
#घोषणा QNX4_BMNAME   ".bitmap"

अटल स्थिर काष्ठा super_operations qnx4_sops;

अटल काष्ठा inode *qnx4_alloc_inode(काष्ठा super_block *sb);
अटल व्योम qnx4_मुक्त_inode(काष्ठा inode *inode);
अटल पूर्णांक qnx4_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data);
अटल पूर्णांक qnx4_statfs(काष्ठा dentry *, काष्ठा kstatfs *);

अटल स्थिर काष्ठा super_operations qnx4_sops =
अणु
	.alloc_inode	= qnx4_alloc_inode,
	.मुक्त_inode	= qnx4_मुक्त_inode,
	.statfs		= qnx4_statfs,
	.remount_fs	= qnx4_remount,
पूर्ण;

अटल पूर्णांक qnx4_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा qnx4_sb_info *qs;

	sync_fileप्रणाली(sb);
	qs = qnx4_sb(sb);
	qs->Version = QNX4_VERSION;
	*flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल पूर्णांक qnx4_get_block( काष्ठा inode *inode, sector_t iblock, काष्ठा buffer_head *bh, पूर्णांक create )
अणु
	अचिन्हित दीर्घ phys;

	QNX4DEBUG((KERN_INFO "qnx4: qnx4_get_block inode=[%ld] iblock=[%ld]\n",inode->i_ino,iblock));

	phys = qnx4_block_map( inode, iblock );
	अगर ( phys ) अणु
		// logical block is beक्रमe खातापूर्ण
		map_bh(bh, inode->i_sb, phys);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u32 try_extent(qnx4_xtnt_t *extent, u32 *offset)
अणु
	u32 size = le32_to_cpu(extent->xtnt_size);
	अगर (*offset < size)
		वापस le32_to_cpu(extent->xtnt_blk) + *offset - 1;
	*offset -= size;
	वापस 0;
पूर्ण

अचिन्हित दीर्घ qnx4_block_map( काष्ठा inode *inode, दीर्घ iblock )
अणु
	पूर्णांक ix;
	दीर्घ i_xblk;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा qnx4_xblk *xblk = शून्य;
	काष्ठा qnx4_inode_entry *qnx4_inode = qnx4_raw_inode(inode);
	u16 nxtnt = le16_to_cpu(qnx4_inode->di_num_xtnts);
	u32 offset = iblock;
	u32 block = try_extent(&qnx4_inode->di_first_xtnt, &offset);

	अगर (block) अणु
		// iblock is in the first extent. This is easy.
	पूर्ण अन्यथा अणु
		// iblock is beyond first extent. We have to follow the extent chain.
		i_xblk = le32_to_cpu(qnx4_inode->di_xblk);
		ix = 0;
		जबतक ( --nxtnt > 0 ) अणु
			अगर ( ix == 0 ) अणु
				// पढ़ो next xtnt block.
				bh = sb_bपढ़ो(inode->i_sb, i_xblk - 1);
				अगर ( !bh ) अणु
					QNX4DEBUG((KERN_ERR "qnx4: I/O error reading xtnt block [%ld])\n", i_xblk - 1));
					वापस -EIO;
				पूर्ण
				xblk = (काष्ठा qnx4_xblk*)bh->b_data;
				अगर ( स_भेद( xblk->xblk_signature, "IamXblk", 7 ) ) अणु
					QNX4DEBUG((KERN_ERR "qnx4: block at %ld is not a valid xtnt\n", qnx4_inode->i_xblk));
					वापस -EIO;
				पूर्ण
			पूर्ण
			block = try_extent(&xblk->xblk_xtnts[ix], &offset);
			अगर (block) अणु
				// got it!
				अवरोध;
			पूर्ण
			अगर ( ++ix >= xblk->xblk_num_xtnts ) अणु
				i_xblk = le32_to_cpu(xblk->xblk_next_xblk);
				ix = 0;
				brअन्यथा( bh );
				bh = शून्य;
			पूर्ण
		पूर्ण
		अगर ( bh )
			brअन्यथा( bh );
	पूर्ण

	QNX4DEBUG((KERN_INFO "qnx4: mapping block %ld of inode %ld = %ld\n",iblock,inode->i_ino,block));
	वापस block;
पूर्ण

अटल पूर्णांक qnx4_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type    = sb->s_magic;
	buf->f_bsize   = sb->s_blocksize;
	buf->f_blocks  = le32_to_cpu(qnx4_sb(sb)->BitMap->di_size) * 8;
	buf->f_bमुक्त   = qnx4_count_मुक्त_blocks(sb);
	buf->f_bavail  = buf->f_bमुक्त;
	buf->f_namelen = QNX4_NAME_MAX;
	buf->f_fsid    = u64_to_fsid(id);

	वापस 0;
पूर्ण

/*
 * Check the root directory of the fileप्रणाली to make sure
 * it really _is_ a qnx4 fileप्रणाली, and to check the size
 * of the directory entry.
 */
अटल स्थिर अक्षर *qnx4_checkroot(काष्ठा super_block *sb,
				  काष्ठा qnx4_super_block *s)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा qnx4_inode_entry *rootdir;
	पूर्णांक rd, rl;
	पूर्णांक i, j;

	अगर (s->RootDir.di_fname[0] != '/' || s->RootDir.di_fname[1] != '\0')
		वापस "no qnx4 filesystem (no root dir).";
	QNX4DEBUG((KERN_NOTICE "QNX4 filesystem found on dev %s.\n", sb->s_id));
	rd = le32_to_cpu(s->RootDir.di_first_xtnt.xtnt_blk) - 1;
	rl = le32_to_cpu(s->RootDir.di_first_xtnt.xtnt_size);
	क्रम (j = 0; j < rl; j++) अणु
		bh = sb_bपढ़ो(sb, rd + j);	/* root dir, first block */
		अगर (bh == शून्य)
			वापस "unable to read root entry.";
		rootdir = (काष्ठा qnx4_inode_entry *) bh->b_data;
		क्रम (i = 0; i < QNX4_INODES_PER_BLOCK; i++, rootdir++) अणु
			QNX4DEBUG((KERN_INFO "rootdir entry found : [%s]\n", rootdir->di_fname));
			अगर (म_भेद(rootdir->di_fname, QNX4_BMNAME) != 0)
				जारी;
			qnx4_sb(sb)->BitMap = kmemdup(rootdir,
						      माप(काष्ठा qnx4_inode_entry),
						      GFP_KERNEL);
			brअन्यथा(bh);
			अगर (!qnx4_sb(sb)->BitMap)
				वापस "not enough memory for bitmap inode";
			/* keep biपंचांगap inode known */
			वापस शून्य;
		पूर्ण
		brअन्यथा(bh);
	पूर्ण
	वापस "bitmap file not found.";
पूर्ण

अटल पूर्णांक qnx4_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा inode *root;
	स्थिर अक्षर *errmsg;
	काष्ठा qnx4_sb_info *qs;

	qs = kzalloc(माप(काष्ठा qnx4_sb_info), GFP_KERNEL);
	अगर (!qs)
		वापस -ENOMEM;
	s->s_fs_info = qs;

	sb_set_blocksize(s, QNX4_BLOCK_SIZE);

	s->s_op = &qnx4_sops;
	s->s_magic = QNX4_SUPER_MAGIC;
	s->s_flags |= SB_RDONLY;	/* Yup, पढ़ो-only yet */
	s->s_समय_min = 0;
	s->s_समय_max = U32_MAX;

	/* Check the superblock signature. Since the qnx4 code is
	   dangerous, we should leave as quickly as possible
	   अगर we करोn't beदीर्घ here... */
	bh = sb_bपढ़ो(s, 1);
	अगर (!bh) अणु
		prपूर्णांकk(KERN_ERR "qnx4: unable to read the superblock\n");
		वापस -EINVAL;
	पूर्ण

 	/* check beक्रमe allocating dentries, inodes, .. */
	errmsg = qnx4_checkroot(s, (काष्ठा qnx4_super_block *) bh->b_data);
	brअन्यथा(bh);
	अगर (errmsg != शून्य) अणु
 		अगर (!silent)
			prपूर्णांकk(KERN_ERR "qnx4: %s\n", errmsg);
		वापस -EINVAL;
	पूर्ण

 	/* करोes root not have inode number QNX4_ROOT_INO ?? */
	root = qnx4_iget(s, QNX4_ROOT_INO * QNX4_INODES_PER_BLOCK);
	अगर (IS_ERR(root)) अणु
		prपूर्णांकk(KERN_ERR "qnx4: get inode failed\n");
		वापस PTR_ERR(root);
 	पूर्ण

 	s->s_root = d_make_root(root);
 	अगर (s->s_root == शून्य)
 		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम qnx4_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा qnx4_sb_info *qs = qnx4_sb(sb);
	समाप्त_block_super(sb);
	अगर (qs) अणु
		kमुक्त(qs->BitMap);
		kमुक्त(qs);
	पूर्ण
पूर्ण

अटल पूर्णांक qnx4_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page,qnx4_get_block);
पूर्ण

अटल sector_t qnx4_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,qnx4_get_block);
पूर्ण
अटल स्थिर काष्ठा address_space_operations qnx4_aops = अणु
	.पढ़ोpage	= qnx4_पढ़ोpage,
	.bmap		= qnx4_bmap
पूर्ण;

काष्ठा inode *qnx4_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा qnx4_inode_entry *raw_inode;
	पूर्णांक block;
	काष्ठा qnx4_inode_entry *qnx4_inode;
	काष्ठा inode *inode;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	qnx4_inode = qnx4_raw_inode(inode);
	inode->i_mode = 0;

	QNX4DEBUG((KERN_INFO "reading inode : [%d]\n", ino));
	अगर (!ino) अणु
		prपूर्णांकk(KERN_ERR "qnx4: bad inode number on dev %s: %lu is "
				"out of range\n",
		       sb->s_id, ino);
		iget_failed(inode);
		वापस ERR_PTR(-EIO);
	पूर्ण
	block = ino / QNX4_INODES_PER_BLOCK;

	अगर (!(bh = sb_bपढ़ो(sb, block))) अणु
		prपूर्णांकk(KERN_ERR "qnx4: major problem: unable to read inode from dev "
		       "%s\n", sb->s_id);
		iget_failed(inode);
		वापस ERR_PTR(-EIO);
	पूर्ण
	raw_inode = ((काष्ठा qnx4_inode_entry *) bh->b_data) +
	    (ino % QNX4_INODES_PER_BLOCK);

	inode->i_mode    = le16_to_cpu(raw_inode->di_mode);
	i_uid_ग_लिखो(inode, (uid_t)le16_to_cpu(raw_inode->di_uid));
	i_gid_ग_लिखो(inode, (gid_t)le16_to_cpu(raw_inode->di_gid));
	set_nlink(inode, le16_to_cpu(raw_inode->di_nlink));
	inode->i_size    = le32_to_cpu(raw_inode->di_size);
	inode->i_mसमय.tv_sec   = le32_to_cpu(raw_inode->di_mसमय);
	inode->i_mसमय.tv_nsec = 0;
	inode->i_aसमय.tv_sec   = le32_to_cpu(raw_inode->di_aसमय);
	inode->i_aसमय.tv_nsec = 0;
	inode->i_स_समय.tv_sec   = le32_to_cpu(raw_inode->di_स_समय);
	inode->i_स_समय.tv_nsec = 0;
	inode->i_blocks  = le32_to_cpu(raw_inode->di_first_xtnt.xtnt_size);

	स_नकल(qnx4_inode, raw_inode, QNX4_सूची_ENTRY_SIZE);
	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_fop = &generic_ro_fops;
		inode->i_mapping->a_ops = &qnx4_aops;
		qnx4_i(inode)->mmu_निजी = inode->i_size;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &qnx4_dir_inode_operations;
		inode->i_fop = &qnx4_dir_operations;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &qnx4_aops;
		qnx4_i(inode)->mmu_निजी = inode->i_size;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "qnx4: bad inode %lu on dev %s\n",
			ino, sb->s_id);
		iget_failed(inode);
		brअन्यथा(bh);
		वापस ERR_PTR(-EIO);
	पूर्ण
	brअन्यथा(bh);
	unlock_new_inode(inode);
	वापस inode;
पूर्ण

अटल काष्ठा kmem_cache *qnx4_inode_cachep;

अटल काष्ठा inode *qnx4_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा qnx4_inode_info *ei;
	ei = kmem_cache_alloc(qnx4_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम qnx4_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(qnx4_inode_cachep, qnx4_i(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा qnx4_inode_info *ei = (काष्ठा qnx4_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक init_inodecache(व्योम)
अणु
	qnx4_inode_cachep = kmem_cache_create("qnx4_inode_cache",
					     माप(काष्ठा qnx4_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (qnx4_inode_cachep == शून्य)
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
	kmem_cache_destroy(qnx4_inode_cachep);
पूर्ण

अटल काष्ठा dentry *qnx4_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, qnx4_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type qnx4_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "qnx4",
	.mount		= qnx4_mount,
	.समाप्त_sb	= qnx4_समाप्त_sb,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("qnx4");

अटल पूर्णांक __init init_qnx4_fs(व्योम)
अणु
	पूर्णांक err;

	err = init_inodecache();
	अगर (err)
		वापस err;

	err = रेजिस्टर_fileप्रणाली(&qnx4_fs_type);
	अगर (err) अणु
		destroy_inodecache();
		वापस err;
	पूर्ण

	prपूर्णांकk(KERN_INFO "QNX4 filesystem 0.2.3 registered.\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_qnx4_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&qnx4_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_qnx4_fs)
module_निकास(निकास_qnx4_fs)
MODULE_LICENSE("GPL");

