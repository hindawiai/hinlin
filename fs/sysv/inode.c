<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/sysv/inode.c
 *
 *  minix/inode.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  xenix/inode.c
 *  Copyright (C) 1992  Doug Evans
 *
 *  coh/inode.c
 *  Copyright (C) 1993  Pascal Haible, Bruno Haible
 *
 *  sysv/inode.c
 *  Copyright (C) 1993  Paul B. Monday
 *
 *  sysv/inode.c
 *  Copyright (C) 1993  Bruno Haible
 *  Copyright (C) 1997, 1998  Krzysztof G. Baranowski
 *
 *  This file contains code क्रम allocating/मुक्तing inodes and क्रम पढ़ो/writing
 *  the superblock.
 */

#समावेश <linux/highuid.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/namei.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "sysv.h"

अटल पूर्णांक sysv_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	u32 समय = (u32)kसमय_get_real_seconds(), old_समय;

	mutex_lock(&sbi->s_lock);

	/*
	 * If we are going to ग_लिखो out the super block,
	 * then attach current समय stamp.
	 * But अगर the fileप्रणाली was marked clean, keep it clean.
	 */
	old_समय = fs32_to_cpu(sbi, *sbi->s_sb_समय);
	अगर (sbi->s_type == FSTYPE_SYSV4) अणु
		अगर (*sbi->s_sb_state == cpu_to_fs32(sbi, 0x7c269d38u - old_समय))
			*sbi->s_sb_state = cpu_to_fs32(sbi, 0x7c269d38u - समय);
		*sbi->s_sb_समय = cpu_to_fs32(sbi, समय);
		mark_buffer_dirty(sbi->s_bh2);
	पूर्ण

	mutex_unlock(&sbi->s_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sysv_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);

	sync_fileप्रणाली(sb);
	अगर (sbi->s_क्रमced_ro)
		*flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल व्योम sysv_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);

	अगर (!sb_rकरोnly(sb)) अणु
		/* XXX ext2 also updates the state here */
		mark_buffer_dirty(sbi->s_bh1);
		अगर (sbi->s_bh1 != sbi->s_bh2)
			mark_buffer_dirty(sbi->s_bh2);
	पूर्ण

	brअन्यथा(sbi->s_bh1);
	अगर (sbi->s_bh1 != sbi->s_bh2)
		brअन्यथा(sbi->s_bh2);

	kमुक्त(sbi);
पूर्ण

अटल पूर्णांक sysv_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = sb->s_magic;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = sbi->s_ndatazones;
	buf->f_bavail = buf->f_bमुक्त = sysv_count_मुक्त_blocks(sb);
	buf->f_files = sbi->s_ninodes;
	buf->f_fमुक्त = sysv_count_मुक्त_inodes(sb);
	buf->f_namelen = SYSV_NAMELEN;
	buf->f_fsid = u64_to_fsid(id);
	वापस 0;
पूर्ण

/* 
 * NXI <-> N0XI क्रम PDP, XIN <-> XIN0 क्रम le32, NIX <-> 0NIX क्रम be32
 */
अटल अंतरभूत व्योम पढ़ो3byte(काष्ठा sysv_sb_info *sbi,
	अचिन्हित अक्षर * from, अचिन्हित अक्षर * to)
अणु
	अगर (sbi->s_bytesex == BYTESEX_PDP) अणु
		to[0] = from[0];
		to[1] = 0;
		to[2] = from[1];
		to[3] = from[2];
	पूर्ण अन्यथा अगर (sbi->s_bytesex == BYTESEX_LE) अणु
		to[0] = from[0];
		to[1] = from[1];
		to[2] = from[2];
		to[3] = 0;
	पूर्ण अन्यथा अणु
		to[0] = 0;
		to[1] = from[0];
		to[2] = from[1];
		to[3] = from[2];
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो3byte(काष्ठा sysv_sb_info *sbi,
	अचिन्हित अक्षर * from, अचिन्हित अक्षर * to)
अणु
	अगर (sbi->s_bytesex == BYTESEX_PDP) अणु
		to[0] = from[0];
		to[1] = from[2];
		to[2] = from[3];
	पूर्ण अन्यथा अगर (sbi->s_bytesex == BYTESEX_LE) अणु
		to[0] = from[0];
		to[1] = from[1];
		to[2] = from[2];
	पूर्ण अन्यथा अणु
		to[0] = from[1];
		to[1] = from[2];
		to[2] = from[3];
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा inode_operations sysv_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.getattr	= sysv_getattr,
पूर्ण;

व्योम sysv_set_inode(काष्ठा inode *inode, dev_t rdev)
अणु
	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &sysv_file_inode_operations;
		inode->i_fop = &sysv_file_operations;
		inode->i_mapping->a_ops = &sysv_aops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &sysv_dir_inode_operations;
		inode->i_fop = &sysv_dir_operations;
		inode->i_mapping->a_ops = &sysv_aops;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &sysv_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &sysv_aops;
	पूर्ण अन्यथा
		init_special_inode(inode, inode->i_mode, rdev);
पूर्ण

काष्ठा inode *sysv_iget(काष्ठा super_block *sb, अचिन्हित पूर्णांक ino)
अणु
	काष्ठा sysv_sb_info * sbi = SYSV_SB(sb);
	काष्ठा buffer_head * bh;
	काष्ठा sysv_inode * raw_inode;
	काष्ठा sysv_inode_info * si;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक block;

	अगर (!ino || ino > sbi->s_ninodes) अणु
		prपूर्णांकk("Bad inode number on dev %s: %d is out of range\n",
		       sb->s_id, ino);
		वापस ERR_PTR(-EIO);
	पूर्ण

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	raw_inode = sysv_raw_inode(sb, ino, &bh);
	अगर (!raw_inode) अणु
		prपूर्णांकk("Major problem: unable to read inode from dev %s\n",
		       inode->i_sb->s_id);
		जाओ bad_inode;
	पूर्ण
	/* SystemV FS: kludge permissions अगर ino==SYSV_ROOT_INO ?? */
	inode->i_mode = fs16_to_cpu(sbi, raw_inode->i_mode);
	i_uid_ग_लिखो(inode, (uid_t)fs16_to_cpu(sbi, raw_inode->i_uid));
	i_gid_ग_लिखो(inode, (gid_t)fs16_to_cpu(sbi, raw_inode->i_gid));
	set_nlink(inode, fs16_to_cpu(sbi, raw_inode->i_nlink));
	inode->i_size = fs32_to_cpu(sbi, raw_inode->i_size);
	inode->i_aसमय.tv_sec = fs32_to_cpu(sbi, raw_inode->i_aसमय);
	inode->i_mसमय.tv_sec = fs32_to_cpu(sbi, raw_inode->i_mसमय);
	inode->i_स_समय.tv_sec = fs32_to_cpu(sbi, raw_inode->i_स_समय);
	inode->i_स_समय.tv_nsec = 0;
	inode->i_aसमय.tv_nsec = 0;
	inode->i_mसमय.tv_nsec = 0;
	inode->i_blocks = 0;

	si = SYSV_I(inode);
	क्रम (block = 0; block < 10+1+1+1; block++)
		पढ़ो3byte(sbi, &raw_inode->i_data[3*block],
				(u8 *)&si->i_data[block]);
	brअन्यथा(bh);
	si->i_dir_start_lookup = 0;
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		sysv_set_inode(inode,
			       old_decode_dev(fs32_to_cpu(sbi, si->i_data[0])));
	अन्यथा
		sysv_set_inode(inode, 0);
	unlock_new_inode(inode);
	वापस inode;

bad_inode:
	iget_failed(inode);
	वापस ERR_PTR(-EIO);
पूर्ण

अटल पूर्णांक __sysv_ग_लिखो_inode(काष्ठा inode *inode, पूर्णांक रुको)
अणु
	काष्ठा super_block * sb = inode->i_sb;
	काष्ठा sysv_sb_info * sbi = SYSV_SB(sb);
	काष्ठा buffer_head * bh;
	काष्ठा sysv_inode * raw_inode;
	काष्ठा sysv_inode_info * si;
	अचिन्हित पूर्णांक ino, block;
	पूर्णांक err = 0;

	ino = inode->i_ino;
	अगर (!ino || ino > sbi->s_ninodes) अणु
		prपूर्णांकk("Bad inode number on dev %s: %d is out of range\n",
		       inode->i_sb->s_id, ino);
		वापस -EIO;
	पूर्ण
	raw_inode = sysv_raw_inode(sb, ino, &bh);
	अगर (!raw_inode) अणु
		prपूर्णांकk("unable to read i-node block\n");
		वापस -EIO;
	पूर्ण

	raw_inode->i_mode = cpu_to_fs16(sbi, inode->i_mode);
	raw_inode->i_uid = cpu_to_fs16(sbi, fs_high2lowuid(i_uid_पढ़ो(inode)));
	raw_inode->i_gid = cpu_to_fs16(sbi, fs_high2lowgid(i_gid_पढ़ो(inode)));
	raw_inode->i_nlink = cpu_to_fs16(sbi, inode->i_nlink);
	raw_inode->i_size = cpu_to_fs32(sbi, inode->i_size);
	raw_inode->i_aसमय = cpu_to_fs32(sbi, inode->i_aसमय.tv_sec);
	raw_inode->i_mसमय = cpu_to_fs32(sbi, inode->i_mसमय.tv_sec);
	raw_inode->i_स_समय = cpu_to_fs32(sbi, inode->i_स_समय.tv_sec);

	si = SYSV_I(inode);
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		si->i_data[0] = cpu_to_fs32(sbi, old_encode_dev(inode->i_rdev));
	क्रम (block = 0; block < 10+1+1+1; block++)
		ग_लिखो3byte(sbi, (u8 *)&si->i_data[block],
			&raw_inode->i_data[3*block]);
	mark_buffer_dirty(bh);
	अगर (रुको) अणु
                sync_dirty_buffer(bh);
                अगर (buffer_req(bh) && !buffer_uptodate(bh)) अणु
                        prपूर्णांकk ("IO error syncing sysv inode [%s:%08x]\n",
                                sb->s_id, ino);
                        err = -EIO;
                पूर्ण
        पूर्ण
	brअन्यथा(bh);
	वापस err;
पूर्ण

पूर्णांक sysv_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस __sysv_ग_लिखो_inode(inode, wbc->sync_mode == WB_SYNC_ALL);
पूर्ण

पूर्णांक sysv_sync_inode(काष्ठा inode *inode)
अणु
	वापस __sysv_ग_लिखो_inode(inode, 1);
पूर्ण

अटल व्योम sysv_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	अगर (!inode->i_nlink) अणु
		inode->i_size = 0;
		sysv_truncate(inode);
	पूर्ण
	invalidate_inode_buffers(inode);
	clear_inode(inode);
	अगर (!inode->i_nlink)
		sysv_मुक्त_inode(inode);
पूर्ण

अटल काष्ठा kmem_cache *sysv_inode_cachep;

अटल काष्ठा inode *sysv_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा sysv_inode_info *si;

	si = kmem_cache_alloc(sysv_inode_cachep, GFP_KERNEL);
	अगर (!si)
		वापस शून्य;
	वापस &si->vfs_inode;
पूर्ण

अटल व्योम sysv_मुक्त_in_core_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(sysv_inode_cachep, SYSV_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *p)
अणु
	काष्ठा sysv_inode_info *si = (काष्ठा sysv_inode_info *)p;

	inode_init_once(&si->vfs_inode);
पूर्ण

स्थिर काष्ठा super_operations sysv_sops = अणु
	.alloc_inode	= sysv_alloc_inode,
	.मुक्त_inode	= sysv_मुक्त_in_core_inode,
	.ग_लिखो_inode	= sysv_ग_लिखो_inode,
	.evict_inode	= sysv_evict_inode,
	.put_super	= sysv_put_super,
	.sync_fs	= sysv_sync_fs,
	.remount_fs	= sysv_remount,
	.statfs		= sysv_statfs,
पूर्ण;

पूर्णांक __init sysv_init_icache(व्योम)
अणु
	sysv_inode_cachep = kmem_cache_create("sysv_inode_cache",
			माप(काष्ठा sysv_inode_info), 0,
			SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|SLAB_ACCOUNT,
			init_once);
	अगर (!sysv_inode_cachep)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम sysv_destroy_icache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(sysv_inode_cachep);
पूर्ण
