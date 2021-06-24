<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * namei.c
 *
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from work (c) 1995,1996 Christian Vogelgsang.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/माला.स>
#समावेश <linux/exportfs.h>
#समावेश "efs.h"


अटल efs_ino_t efs_find_entry(काष्ठा inode *inode, स्थिर अक्षर *name, पूर्णांक len)
अणु
	काष्ठा buffer_head *bh;

	पूर्णांक			slot, namelen;
	अक्षर			*nameptr;
	काष्ठा efs_dir		*dirblock;
	काष्ठा efs_dentry	*dirslot;
	efs_ino_t		inodक्रमागत;
	efs_block_t		block;
 
	अगर (inode->i_size & (EFS_सूचीBSIZE-1))
		pr_warn("%s(): directory size not a multiple of EFS_DIRBSIZE\n",
			__func__);

	क्रम(block = 0; block < inode->i_blocks; block++) अणु

		bh = sb_bपढ़ो(inode->i_sb, efs_bmap(inode, block));
		अगर (!bh) अणु
			pr_err("%s(): failed to read dir block %d\n",
			       __func__, block);
			वापस 0;
		पूर्ण
    
		dirblock = (काष्ठा efs_dir *) bh->b_data;

		अगर (be16_to_cpu(dirblock->magic) != EFS_सूचीBLK_MAGIC) अणु
			pr_err("%s(): invalid directory block\n", __func__);
			brअन्यथा(bh);
			वापस 0;
		पूर्ण

		क्रम (slot = 0; slot < dirblock->slots; slot++) अणु
			dirslot  = (काष्ठा efs_dentry *) (((अक्षर *) bh->b_data) + EFS_SLOTAT(dirblock, slot));

			namelen  = dirslot->namelen;
			nameptr  = dirslot->name;

			अगर ((namelen == len) && (!स_भेद(name, nameptr, len))) अणु
				inodक्रमागत = be32_to_cpu(dirslot->inode);
				brअन्यथा(bh);
				वापस inodक्रमागत;
			पूर्ण
		पूर्ण
		brअन्यथा(bh);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा dentry *efs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	efs_ino_t inodक्रमागत;
	काष्ठा inode *inode = शून्य;

	inodक्रमागत = efs_find_entry(dir, dentry->d_name.name, dentry->d_name.len);
	अगर (inodक्रमागत)
		inode = efs_iget(dir->i_sb, inodक्रमागत);

	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल काष्ठा inode *efs_nfs_get_inode(काष्ठा super_block *sb, u64 ino,
		u32 generation)
अणु
	काष्ठा inode *inode;

	अगर (ino == 0)
		वापस ERR_PTR(-ESTALE);
	inode = efs_iget(sb, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	अगर (generation && inode->i_generation != generation) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	वापस inode;
पूर्ण

काष्ठा dentry *efs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    efs_nfs_get_inode);
पूर्ण

काष्ठा dentry *efs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    efs_nfs_get_inode);
पूर्ण

काष्ठा dentry *efs_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा dentry *parent = ERR_PTR(-ENOENT);
	efs_ino_t ino;

	ino = efs_find_entry(d_inode(child), "..", 2);
	अगर (ino)
		parent = d_obtain_alias(efs_iget(child->d_sb, ino));

	वापस parent;
पूर्ण
