<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	fs/bfs/inode.c
 *	BFS superblock and inode operations.
 *	Copyright (C) 1999-2018 Tigran Aivazian <aivazian.tigran@gmail.com>
 *	From fs/minix, Copyright (C) 1991, 1992 Linus Torvalds.
 *	Made endianness-clean by Andrew Stribblehill <ads@wompom.org>, 2005.
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश "bfs.h"

MODULE_AUTHOR("Tigran Aivazian <aivazian.tigran@gmail.com>");
MODULE_DESCRIPTION("SCO UnixWare BFS filesystem for Linux");
MODULE_LICENSE("GPL");

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा dम_लिखो(x...)	म_लिखो(x)
#अन्यथा
#घोषणा dम_लिखो(x...)
#पूर्ण_अगर

काष्ठा inode *bfs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा bfs_inode *di;
	काष्ठा inode *inode;
	काष्ठा buffer_head *bh;
	पूर्णांक block, off;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	अगर ((ino < BFS_ROOT_INO) || (ino > BFS_SB(inode->i_sb)->si_lasti)) अणु
		म_लिखो("Bad inode number %s:%08lx\n", inode->i_sb->s_id, ino);
		जाओ error;
	पूर्ण

	block = (ino - BFS_ROOT_INO) / BFS_INODES_PER_BLOCK + 1;
	bh = sb_bपढ़ो(inode->i_sb, block);
	अगर (!bh) अणु
		म_लिखो("Unable to read inode %s:%08lx\n", inode->i_sb->s_id,
									ino);
		जाओ error;
	पूर्ण

	off = (ino - BFS_ROOT_INO) % BFS_INODES_PER_BLOCK;
	di = (काष्ठा bfs_inode *)bh->b_data + off;

	inode->i_mode = 0x0000FFFF & le32_to_cpu(di->i_mode);
	अगर (le32_to_cpu(di->i_vtype) == BFS_Vसूची) अणु
		inode->i_mode |= S_IFसूची;
		inode->i_op = &bfs_dir_inops;
		inode->i_fop = &bfs_dir_operations;
	पूर्ण अन्यथा अगर (le32_to_cpu(di->i_vtype) == BFS_VREG) अणु
		inode->i_mode |= S_IFREG;
		inode->i_op = &bfs_file_inops;
		inode->i_fop = &bfs_file_operations;
		inode->i_mapping->a_ops = &bfs_aops;
	पूर्ण

	BFS_I(inode)->i_sblock =  le32_to_cpu(di->i_sblock);
	BFS_I(inode)->i_eblock =  le32_to_cpu(di->i_eblock);
	BFS_I(inode)->i_dsk_ino = le16_to_cpu(di->i_ino);
	i_uid_ग_लिखो(inode, le32_to_cpu(di->i_uid));
	i_gid_ग_लिखो(inode,  le32_to_cpu(di->i_gid));
	set_nlink(inode, le32_to_cpu(di->i_nlink));
	inode->i_size = BFS_खाताSIZE(di);
	inode->i_blocks = BFS_खाताBLOCKS(di);
	inode->i_aसमय.tv_sec =  le32_to_cpu(di->i_aसमय);
	inode->i_mसमय.tv_sec =  le32_to_cpu(di->i_mसमय);
	inode->i_स_समय.tv_sec =  le32_to_cpu(di->i_स_समय);
	inode->i_aसमय.tv_nsec = 0;
	inode->i_mसमय.tv_nsec = 0;
	inode->i_स_समय.tv_nsec = 0;

	brअन्यथा(bh);
	unlock_new_inode(inode);
	वापस inode;

error:
	iget_failed(inode);
	वापस ERR_PTR(-EIO);
पूर्ण

अटल काष्ठा bfs_inode *find_inode(काष्ठा super_block *sb, u16 ino, काष्ठा buffer_head **p)
अणु
	अगर ((ino < BFS_ROOT_INO) || (ino > BFS_SB(sb)->si_lasti)) अणु
		म_लिखो("Bad inode number %s:%08x\n", sb->s_id, ino);
		वापस ERR_PTR(-EIO);
	पूर्ण

	ino -= BFS_ROOT_INO;

	*p = sb_bपढ़ो(sb, 1 + ino / BFS_INODES_PER_BLOCK);
	अगर (!*p) अणु
		म_लिखो("Unable to read inode %s:%08x\n", sb->s_id, ino);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस (काष्ठा bfs_inode *)(*p)->b_data +  ino % BFS_INODES_PER_BLOCK;
पूर्ण

अटल पूर्णांक bfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा bfs_sb_info *info = BFS_SB(inode->i_sb);
	अचिन्हित पूर्णांक ino = (u16)inode->i_ino;
	अचिन्हित दीर्घ i_sblock;
	काष्ठा bfs_inode *di;
	काष्ठा buffer_head *bh;
	पूर्णांक err = 0;

	dम_लिखो("ino=%08x\n", ino);

	di = find_inode(inode->i_sb, ino, &bh);
	अगर (IS_ERR(di))
		वापस PTR_ERR(di);

	mutex_lock(&info->bfs_lock);

	अगर (ino == BFS_ROOT_INO)
		di->i_vtype = cpu_to_le32(BFS_Vसूची);
	अन्यथा
		di->i_vtype = cpu_to_le32(BFS_VREG);

	di->i_ino = cpu_to_le16(ino);
	di->i_mode = cpu_to_le32(inode->i_mode);
	di->i_uid = cpu_to_le32(i_uid_पढ़ो(inode));
	di->i_gid = cpu_to_le32(i_gid_पढ़ो(inode));
	di->i_nlink = cpu_to_le32(inode->i_nlink);
	di->i_aसमय = cpu_to_le32(inode->i_aसमय.tv_sec);
	di->i_mसमय = cpu_to_le32(inode->i_mसमय.tv_sec);
	di->i_स_समय = cpu_to_le32(inode->i_स_समय.tv_sec);
	i_sblock = BFS_I(inode)->i_sblock;
	di->i_sblock = cpu_to_le32(i_sblock);
	di->i_eblock = cpu_to_le32(BFS_I(inode)->i_eblock);
	di->i_eoffset = cpu_to_le32(i_sblock * BFS_BSIZE + inode->i_size - 1);

	mark_buffer_dirty(bh);
	अगर (wbc->sync_mode == WB_SYNC_ALL) अणु
		sync_dirty_buffer(bh);
		अगर (buffer_req(bh) && !buffer_uptodate(bh))
			err = -EIO;
	पूर्ण
	brअन्यथा(bh);
	mutex_unlock(&info->bfs_lock);
	वापस err;
पूर्ण

अटल व्योम bfs_evict_inode(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ ino = inode->i_ino;
	काष्ठा bfs_inode *di;
	काष्ठा buffer_head *bh;
	काष्ठा super_block *s = inode->i_sb;
	काष्ठा bfs_sb_info *info = BFS_SB(s);
	काष्ठा bfs_inode_info *bi = BFS_I(inode);

	dम_लिखो("ino=%08lx\n", ino);

	truncate_inode_pages_final(&inode->i_data);
	invalidate_inode_buffers(inode);
	clear_inode(inode);

	अगर (inode->i_nlink)
		वापस;

	di = find_inode(s, inode->i_ino, &bh);
	अगर (IS_ERR(di))
		वापस;

	mutex_lock(&info->bfs_lock);
	/* clear on-disk inode */
	स_रखो(di, 0, माप(काष्ठा bfs_inode));
	mark_buffer_dirty(bh);
	brअन्यथा(bh);

	अगर (bi->i_dsk_ino) अणु
		अगर (bi->i_sblock)
			info->si_मुक्तb += bi->i_eblock + 1 - bi->i_sblock;
		info->si_मुक्तi++;
		clear_bit(ino, info->si_imap);
		bfs_dump_imap("evict_inode", s);
	पूर्ण

	/*
	 * If this was the last file, make the previous block
	 * "last block of the last file" even अगर there is no
	 * real file there, saves us 1 gap.
	 */
	अगर (info->si_lf_eblk == bi->i_eblock)
		info->si_lf_eblk = bi->i_sblock - 1;
	mutex_unlock(&info->bfs_lock);
पूर्ण

अटल व्योम bfs_put_super(काष्ठा super_block *s)
अणु
	काष्ठा bfs_sb_info *info = BFS_SB(s);

	अगर (!info)
		वापस;

	mutex_destroy(&info->bfs_lock);
	kमुक्त(info);
	s->s_fs_info = शून्य;
पूर्ण

अटल पूर्णांक bfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *s = dentry->d_sb;
	काष्ठा bfs_sb_info *info = BFS_SB(s);
	u64 id = huge_encode_dev(s->s_bdev->bd_dev);
	buf->f_type = BFS_MAGIC;
	buf->f_bsize = s->s_blocksize;
	buf->f_blocks = info->si_blocks;
	buf->f_bमुक्त = buf->f_bavail = info->si_मुक्तb;
	buf->f_files = info->si_lasti + 1 - BFS_ROOT_INO;
	buf->f_fमुक्त = info->si_मुक्तi;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen = BFS_NAMELEN;
	वापस 0;
पूर्ण

अटल काष्ठा kmem_cache *bfs_inode_cachep;

अटल काष्ठा inode *bfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा bfs_inode_info *bi;
	bi = kmem_cache_alloc(bfs_inode_cachep, GFP_KERNEL);
	अगर (!bi)
		वापस शून्य;
	वापस &bi->vfs_inode;
पूर्ण

अटल व्योम bfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(bfs_inode_cachep, BFS_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा bfs_inode_info *bi = foo;

	inode_init_once(&bi->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	bfs_inode_cachep = kmem_cache_create("bfs_inode_cache",
					     माप(काष्ठा bfs_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (bfs_inode_cachep == शून्य)
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
	kmem_cache_destroy(bfs_inode_cachep);
पूर्ण

अटल स्थिर काष्ठा super_operations bfs_sops = अणु
	.alloc_inode	= bfs_alloc_inode,
	.मुक्त_inode	= bfs_मुक्त_inode,
	.ग_लिखो_inode	= bfs_ग_लिखो_inode,
	.evict_inode	= bfs_evict_inode,
	.put_super	= bfs_put_super,
	.statfs		= bfs_statfs,
पूर्ण;

व्योम bfs_dump_imap(स्थिर अक्षर *prefix, काष्ठा super_block *s)
अणु
#अगर_घोषित DEBUG
	पूर्णांक i;
	अक्षर *पंचांगpbuf = (अक्षर *)get_zeroed_page(GFP_KERNEL);

	अगर (!पंचांगpbuf)
		वापस;
	क्रम (i = BFS_SB(s)->si_lasti; i >= 0; i--) अणु
		अगर (i > PAGE_SIZE - 100) अवरोध;
		अगर (test_bit(i, BFS_SB(s)->si_imap))
			म_जोड़ो(पंचांगpbuf, "1");
		अन्यथा
			म_जोड़ो(पंचांगpbuf, "0");
	पूर्ण
	म_लिखो("%s: lasti=%08lx <%s>\n", prefix, BFS_SB(s)->si_lasti, पंचांगpbuf);
	मुक्त_page((अचिन्हित दीर्घ)पंचांगpbuf);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bfs_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh, *sbh;
	काष्ठा bfs_super_block *bfs_sb;
	काष्ठा inode *inode;
	अचिन्हित i;
	काष्ठा bfs_sb_info *info;
	पूर्णांक ret = -EINVAL;
	अचिन्हित दीर्घ i_sblock, i_eblock, i_eoff, s_size;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	mutex_init(&info->bfs_lock);
	s->s_fs_info = info;
	s->s_समय_min = 0;
	s->s_समय_max = U32_MAX;

	sb_set_blocksize(s, BFS_BSIZE);

	sbh = sb_bपढ़ो(s, 0);
	अगर (!sbh)
		जाओ out;
	bfs_sb = (काष्ठा bfs_super_block *)sbh->b_data;
	अगर (le32_to_cpu(bfs_sb->s_magic) != BFS_MAGIC) अणु
		अगर (!silent)
			म_लिखो("No BFS filesystem on %s (magic=%08x)\n", s->s_id,  le32_to_cpu(bfs_sb->s_magic));
		जाओ out1;
	पूर्ण
	अगर (BFS_UNCLEAN(bfs_sb, s) && !silent)
		म_लिखो("%s is unclean, continuing\n", s->s_id);

	s->s_magic = BFS_MAGIC;

	अगर (le32_to_cpu(bfs_sb->s_start) > le32_to_cpu(bfs_sb->s_end) ||
	    le32_to_cpu(bfs_sb->s_start) < माप(काष्ठा bfs_super_block) + माप(काष्ठा bfs_dirent)) अणु
		म_लिखो("Superblock is corrupted on %s\n", s->s_id);
		जाओ out1;
	पूर्ण

	info->si_lasti = (le32_to_cpu(bfs_sb->s_start) - BFS_BSIZE) / माप(काष्ठा bfs_inode) + BFS_ROOT_INO - 1;
	अगर (info->si_lasti == BFS_MAX_LASTI)
		म_लिखो("NOTE: filesystem %s was created with 512 inodes, the real maximum is 511, mounting anyway\n", s->s_id);
	अन्यथा अगर (info->si_lasti > BFS_MAX_LASTI) अणु
		म_लिखो("Impossible last inode number %lu > %d on %s\n", info->si_lasti, BFS_MAX_LASTI, s->s_id);
		जाओ out1;
	पूर्ण
	क्रम (i = 0; i < BFS_ROOT_INO; i++)
		set_bit(i, info->si_imap);

	s->s_op = &bfs_sops;
	inode = bfs_iget(s, BFS_ROOT_INO);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		जाओ out1;
	पूर्ण
	s->s_root = d_make_root(inode);
	अगर (!s->s_root) अणु
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण

	info->si_blocks = (le32_to_cpu(bfs_sb->s_end) + 1) >> BFS_BSIZE_BITS;
	info->si_मुक्तb = (le32_to_cpu(bfs_sb->s_end) + 1 - le32_to_cpu(bfs_sb->s_start)) >> BFS_BSIZE_BITS;
	info->si_मुक्तi = 0;
	info->si_lf_eblk = 0;

	/* can we पढ़ो the last block? */
	bh = sb_bपढ़ो(s, info->si_blocks - 1);
	अगर (!bh) अणु
		म_लिखो("Last block not available on %s: %lu\n", s->s_id, info->si_blocks - 1);
		ret = -EIO;
		जाओ out2;
	पूर्ण
	brअन्यथा(bh);

	bh = शून्य;
	क्रम (i = BFS_ROOT_INO; i <= info->si_lasti; i++) अणु
		काष्ठा bfs_inode *di;
		पूर्णांक block = (i - BFS_ROOT_INO) / BFS_INODES_PER_BLOCK + 1;
		पूर्णांक off = (i - BFS_ROOT_INO) % BFS_INODES_PER_BLOCK;
		अचिन्हित दीर्घ eblock;

		अगर (!off) अणु
			brअन्यथा(bh);
			bh = sb_bपढ़ो(s, block);
		पूर्ण

		अगर (!bh)
			जारी;

		di = (काष्ठा bfs_inode *)bh->b_data + off;

		/* test अगर fileप्रणाली is not corrupted */

		i_eoff = le32_to_cpu(di->i_eoffset);
		i_sblock = le32_to_cpu(di->i_sblock);
		i_eblock = le32_to_cpu(di->i_eblock);
		s_size = le32_to_cpu(bfs_sb->s_end);

		अगर (i_sblock > info->si_blocks ||
			i_eblock > info->si_blocks ||
			i_sblock > i_eblock ||
			(i_eoff != le32_to_cpu(-1) && i_eoff > s_size) ||
			i_sblock * BFS_BSIZE > i_eoff) अणु

			म_लिखो("Inode 0x%08x corrupted on %s\n", i, s->s_id);

			brअन्यथा(bh);
			ret = -EIO;
			जाओ out2;
		पूर्ण

		अगर (!di->i_ino) अणु
			info->si_मुक्तi++;
			जारी;
		पूर्ण
		set_bit(i, info->si_imap);
		info->si_मुक्तb -= BFS_खाताBLOCKS(di);

		eblock =  le32_to_cpu(di->i_eblock);
		अगर (eblock > info->si_lf_eblk)
			info->si_lf_eblk = eblock;
	पूर्ण
	brअन्यथा(bh);
	brअन्यथा(sbh);
	bfs_dump_imap("fill_super", s);
	वापस 0;

out2:
	dput(s->s_root);
	s->s_root = शून्य;
out1:
	brअन्यथा(sbh);
out:
	mutex_destroy(&info->bfs_lock);
	kमुक्त(info);
	s->s_fs_info = शून्य;
	वापस ret;
पूर्ण

अटल काष्ठा dentry *bfs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, bfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type bfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "bfs",
	.mount		= bfs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("bfs");

अटल पूर्णांक __init init_bfs_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&bfs_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_bfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&bfs_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_bfs_fs)
module_निकास(निकास_bfs_fs)
