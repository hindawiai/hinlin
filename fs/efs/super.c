<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * super.c
 *
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from work (c) 1995,1996 Christian Vogelgsang.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/vfs.h>
#समावेश <linux/blkdev.h>

#समावेश "efs.h"
#समावेश <linux/efs_vh.h>
#समावेश <linux/efs_fs_sb.h>

अटल पूर्णांक efs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);
अटल पूर्णांक efs_fill_super(काष्ठा super_block *s, व्योम *d, पूर्णांक silent);

अटल काष्ठा dentry *efs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, efs_fill_super);
पूर्ण

अटल व्योम efs_समाप्त_sb(काष्ठा super_block *s)
अणु
	काष्ठा efs_sb_info *sbi = SUPER_INFO(s);
	समाप्त_block_super(s);
	kमुक्त(sbi);
पूर्ण

अटल काष्ठा file_प्रणाली_type efs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "efs",
	.mount		= efs_mount,
	.समाप्त_sb	= efs_समाप्त_sb,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("efs");

अटल काष्ठा pt_types sgi_pt_types[] = अणु
	अणु0x00,		"SGI vh"पूर्ण,
	अणु0x01,		"SGI trkrepl"पूर्ण,
	अणु0x02,		"SGI secrepl"पूर्ण,
	अणु0x03,		"SGI raw"पूर्ण,
	अणु0x04,		"SGI bsd"पूर्ण,
	अणुSGI_SYSV,	"SGI sysv"पूर्ण,
	अणु0x06,		"SGI vol"पूर्ण,
	अणुSGI_EFS,	"SGI efs"पूर्ण,
	अणु0x08,		"SGI lv"पूर्ण,
	अणु0x09,		"SGI rlv"पूर्ण,
	अणु0x0A,		"SGI xfs"पूर्ण,
	अणु0x0B,		"SGI xfslog"पूर्ण,
	अणु0x0C,		"SGI xlv"पूर्ण,
	अणु0x82,		"Linux swap"पूर्ण,
	अणु0x83,		"Linux native"पूर्ण,
	अणु0,		शून्यपूर्ण
पूर्ण;


अटल काष्ठा kmem_cache * efs_inode_cachep;

अटल काष्ठा inode *efs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा efs_inode_info *ei;
	ei = kmem_cache_alloc(efs_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम efs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(efs_inode_cachep, INODE_INFO(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा efs_inode_info *ei = (काष्ठा efs_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	efs_inode_cachep = kmem_cache_create("efs_inode_cache",
				माप(काष्ठा efs_inode_info), 0,
				SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
				SLAB_ACCOUNT, init_once);
	अगर (efs_inode_cachep == शून्य)
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
	kmem_cache_destroy(efs_inode_cachep);
पूर्ण

अटल पूर्णांक efs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	*flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations efs_superblock_operations = अणु
	.alloc_inode	= efs_alloc_inode,
	.मुक्त_inode	= efs_मुक्त_inode,
	.statfs		= efs_statfs,
	.remount_fs	= efs_remount,
पूर्ण;

अटल स्थिर काष्ठा export_operations efs_export_ops = अणु
	.fh_to_dentry	= efs_fh_to_dentry,
	.fh_to_parent	= efs_fh_to_parent,
	.get_parent	= efs_get_parent,
पूर्ण;

अटल पूर्णांक __init init_efs_fs(व्योम) अणु
	पूर्णांक err;
	pr_info(EFS_VERSION" - http://aeschi.ch.eu.org/efs/\n");
	err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&efs_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_efs_fs(व्योम) अणु
	unरेजिस्टर_fileप्रणाली(&efs_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_efs_fs)
module_निकास(निकास_efs_fs)

अटल efs_block_t efs_validate_vh(काष्ठा volume_header *vh) अणु
	पूर्णांक		i;
	__be32		cs, *ui;
	पूर्णांक		csum;
	efs_block_t	sblock = 0; /* shuts up gcc */
	काष्ठा pt_types	*pt_entry;
	पूर्णांक		pt_type, slice = -1;

	अगर (be32_to_cpu(vh->vh_magic) != VHMAGIC) अणु
		/*
		 * assume that we're dealing with a partition and allow
		 * पढ़ो_super() to try and detect a valid superblock
		 * on the next block.
		 */
		वापस 0;
	पूर्ण

	ui = ((__be32 *) (vh + 1)) - 1;
	क्रम(csum = 0; ui >= ((__be32 *) vh);) अणु
		cs = *ui--;
		csum += be32_to_cpu(cs);
	पूर्ण
	अगर (csum) अणु
		pr_warn("SGI disklabel: checksum bad, label corrupted\n");
		वापस 0;
	पूर्ण

#अगर_घोषित DEBUG
	pr_debug("bf: \"%16s\"\n", vh->vh_bootfile);

	क्रम(i = 0; i < NVसूची; i++) अणु
		पूर्णांक	j;
		अक्षर	name[VDNAMESIZE+1];

		क्रम(j = 0; j < VDNAMESIZE; j++) अणु
			name[j] = vh->vh_vd[i].vd_name[j];
		पूर्ण
		name[j] = (अक्षर) 0;

		अगर (name[0]) अणु
			pr_debug("vh: %8s block: 0x%08x size: 0x%08x\n",
				name, (पूर्णांक) be32_to_cpu(vh->vh_vd[i].vd_lbn),
				(पूर्णांक) be32_to_cpu(vh->vh_vd[i].vd_nbytes));
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	क्रम(i = 0; i < NPARTAB; i++) अणु
		pt_type = (पूर्णांक) be32_to_cpu(vh->vh_pt[i].pt_type);
		क्रम(pt_entry = sgi_pt_types; pt_entry->pt_name; pt_entry++) अणु
			अगर (pt_type == pt_entry->pt_type) अवरोध;
		पूर्ण
#अगर_घोषित DEBUG
		अगर (be32_to_cpu(vh->vh_pt[i].pt_nblks)) अणु
			pr_debug("pt %2d: start: %08d size: %08d type: 0x%02x (%s)\n",
				 i, (पूर्णांक)be32_to_cpu(vh->vh_pt[i].pt_firstlbn),
				 (पूर्णांक)be32_to_cpu(vh->vh_pt[i].pt_nblks),
				 pt_type, (pt_entry->pt_name) ?
				 pt_entry->pt_name : "unknown");
		पूर्ण
#पूर्ण_अगर
		अगर (IS_EFS(pt_type)) अणु
			sblock = be32_to_cpu(vh->vh_pt[i].pt_firstlbn);
			slice = i;
		पूर्ण
	पूर्ण

	अगर (slice == -1) अणु
		pr_notice("partition table contained no EFS partitions\n");
#अगर_घोषित DEBUG
	पूर्ण अन्यथा अणु
		pr_info("using slice %d (type %s, offset 0x%x)\n", slice,
			(pt_entry->pt_name) ? pt_entry->pt_name : "unknown",
			sblock);
#पूर्ण_अगर
	पूर्ण
	वापस sblock;
पूर्ण

अटल पूर्णांक efs_validate_super(काष्ठा efs_sb_info *sb, काष्ठा efs_super *super) अणु

	अगर (!IS_EFS_MAGIC(be32_to_cpu(super->fs_magic)))
		वापस -1;

	sb->fs_magic     = be32_to_cpu(super->fs_magic);
	sb->total_blocks = be32_to_cpu(super->fs_size);
	sb->first_block  = be32_to_cpu(super->fs_firstcg);
	sb->group_size   = be32_to_cpu(super->fs_cgfsize);
	sb->data_मुक्त    = be32_to_cpu(super->fs_tमुक्त);
	sb->inode_मुक्त   = be32_to_cpu(super->fs_tinode);
	sb->inode_blocks = be16_to_cpu(super->fs_cgisize);
	sb->total_groups = be16_to_cpu(super->fs_ncg);
    
	वापस 0;    
पूर्ण

अटल पूर्णांक efs_fill_super(काष्ठा super_block *s, व्योम *d, पूर्णांक silent)
अणु
	काष्ठा efs_sb_info *sb;
	काष्ठा buffer_head *bh;
	काष्ठा inode *root;

 	sb = kzalloc(माप(काष्ठा efs_sb_info), GFP_KERNEL);
	अगर (!sb)
		वापस -ENOMEM;
	s->s_fs_info = sb;
	s->s_समय_min = 0;
	s->s_समय_max = U32_MAX;
 
	s->s_magic		= EFS_SUPER_MAGIC;
	अगर (!sb_set_blocksize(s, EFS_BLOCKSIZE)) अणु
		pr_err("device does not support %d byte blocks\n",
			EFS_BLOCKSIZE);
		वापस -EINVAL;
	पूर्ण
  
	/* पढ़ो the vh (volume header) block */
	bh = sb_bपढ़ो(s, 0);

	अगर (!bh) अणु
		pr_err("cannot read volume header\n");
		वापस -EIO;
	पूर्ण

	/*
	 * अगर this वापसs zero then we didn't find any partition table.
	 * this isn't (yet) an error - just assume क्रम the moment that
	 * the device is valid and go on to search क्रम a superblock.
	 */
	sb->fs_start = efs_validate_vh((काष्ठा volume_header *) bh->b_data);
	brअन्यथा(bh);

	अगर (sb->fs_start == -1) अणु
		वापस -EINVAL;
	पूर्ण

	bh = sb_bपढ़ो(s, sb->fs_start + EFS_SUPER);
	अगर (!bh) अणु
		pr_err("cannot read superblock\n");
		वापस -EIO;
	पूर्ण
		
	अगर (efs_validate_super(sb, (काष्ठा efs_super *) bh->b_data)) अणु
#अगर_घोषित DEBUG
		pr_warn("invalid superblock at block %u\n",
			sb->fs_start + EFS_SUPER);
#पूर्ण_अगर
		brअन्यथा(bh);
		वापस -EINVAL;
	पूर्ण
	brअन्यथा(bh);

	अगर (!sb_rकरोnly(s)) अणु
#अगर_घोषित DEBUG
		pr_info("forcing read-only mode\n");
#पूर्ण_अगर
		s->s_flags |= SB_RDONLY;
	पूर्ण
	s->s_op   = &efs_superblock_operations;
	s->s_export_op = &efs_export_ops;
	root = efs_iget(s, EFS_ROOTINODE);
	अगर (IS_ERR(root)) अणु
		pr_err("get root inode failed\n");
		वापस PTR_ERR(root);
	पूर्ण

	s->s_root = d_make_root(root);
	अगर (!(s->s_root)) अणु
		pr_err("get root dentry failed\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf) अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा efs_sb_info *sbi = SUPER_INFO(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type    = EFS_SUPER_MAGIC;	/* efs magic number */
	buf->f_bsize   = EFS_BLOCKSIZE;		/* blocksize */
	buf->f_blocks  = sbi->total_groups *	/* total data blocks */
			(sbi->group_size - sbi->inode_blocks);
	buf->f_bमुक्त   = sbi->data_मुक्त;	/* मुक्त data blocks */
	buf->f_bavail  = sbi->data_मुक्त;	/* मुक्त blocks क्रम non-root */
	buf->f_files   = sbi->total_groups *	/* total inodes */
			sbi->inode_blocks *
			(EFS_BLOCKSIZE / माप(काष्ठा efs_dinode));
	buf->f_fमुक्त   = sbi->inode_मुक्त;	/* मुक्त inodes */
	buf->f_fsid    = u64_to_fsid(id);
	buf->f_namelen = EFS_MAXNAMELEN;	/* max filename length */

	वापस 0;
पूर्ण

