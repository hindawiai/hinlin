<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* fs/fat/nfs.c
 */

#समावेश <linux/exportfs.h>
#समावेश "fat.h"

काष्ठा fat_fid अणु
	u32 i_gen;
	u32 i_pos_low;
	u16 i_pos_hi;
	u16 parent_i_pos_hi;
	u32 parent_i_pos_low;
	u32 parent_i_gen;
पूर्ण;

#घोषणा FAT_FID_SIZE_WITHOUT_PARENT 3
#घोषणा FAT_FID_SIZE_WITH_PARENT (माप(काष्ठा fat_fid)/माप(u32))

/**
 * Look up a directory inode given its starting cluster.
 */
अटल काष्ठा inode *fat_dget(काष्ठा super_block *sb, पूर्णांक i_logstart)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा hlist_head *head;
	काष्ठा msकरोs_inode_info *i;
	काष्ठा inode *inode = शून्य;

	head = sbi->dir_hashtable + fat_dir_hash(i_logstart);
	spin_lock(&sbi->dir_hash_lock);
	hlist_क्रम_each_entry(i, head, i_dir_hash) अणु
		BUG_ON(i->vfs_inode.i_sb != sb);
		अगर (i->i_logstart != i_logstart)
			जारी;
		inode = igrab(&i->vfs_inode);
		अगर (inode)
			अवरोध;
	पूर्ण
	spin_unlock(&sbi->dir_hash_lock);
	वापस inode;
पूर्ण

अटल काष्ठा inode *fat_ilookup(काष्ठा super_block *sb, u64 ino, loff_t i_pos)
अणु
	अगर (MSDOS_SB(sb)->options.nfs == FAT_NFS_NOSTALE_RO)
		वापस fat_iget(sb, i_pos);

	अन्यथा अणु
		अगर ((ino < MSDOS_ROOT_INO) || (ino == MSDOS_FSINFO_INO))
			वापस शून्य;
		वापस ilookup(sb, ino);
	पूर्ण
पूर्ण

अटल काष्ठा inode *__fat_nfs_get_inode(काष्ठा super_block *sb,
				       u64 ino, u32 generation, loff_t i_pos)
अणु
	काष्ठा inode *inode = fat_ilookup(sb, ino, i_pos);

	अगर (inode && generation && (inode->i_generation != generation)) अणु
		iput(inode);
		inode = शून्य;
	पूर्ण
	अगर (inode == शून्य && MSDOS_SB(sb)->options.nfs == FAT_NFS_NOSTALE_RO) अणु
		काष्ठा buffer_head *bh = शून्य;
		काष्ठा msकरोs_dir_entry *de ;
		sector_t blocknr;
		पूर्णांक offset;
		fat_get_blknr_offset(MSDOS_SB(sb), i_pos, &blocknr, &offset);
		bh = sb_bपढ़ो(sb, blocknr);
		अगर (!bh) अणु
			fat_msg(sb, KERN_ERR,
				"unable to read block(%llu) for building NFS inode",
				(llu)blocknr);
			वापस inode;
		पूर्ण
		de = (काष्ठा msकरोs_dir_entry *)bh->b_data;
		/* If a file is deleted on server and client is not updated
		 * yet, we must not build the inode upon a lookup call.
		 */
		अगर (IS_FREE(de[offset].name))
			inode = शून्य;
		अन्यथा
			inode = fat_build_inode(sb, &de[offset], i_pos);
		brअन्यथा(bh);
	पूर्ण

	वापस inode;
पूर्ण

अटल काष्ठा inode *fat_nfs_get_inode(काष्ठा super_block *sb,
				       u64 ino, u32 generation)
अणु

	वापस __fat_nfs_get_inode(sb, ino, generation, 0);
पूर्ण

अटल पूर्णांक
fat_encode_fh_nostale(काष्ठा inode *inode, __u32 *fh, पूर्णांक *lenp,
		      काष्ठा inode *parent)
अणु
	पूर्णांक len = *lenp;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	काष्ठा fat_fid *fid = (काष्ठा fat_fid *) fh;
	loff_t i_pos;
	पूर्णांक type = खाताID_FAT_WITHOUT_PARENT;

	अगर (parent) अणु
		अगर (len < FAT_FID_SIZE_WITH_PARENT) अणु
			*lenp = FAT_FID_SIZE_WITH_PARENT;
			वापस खाताID_INVALID;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (len < FAT_FID_SIZE_WITHOUT_PARENT) अणु
			*lenp = FAT_FID_SIZE_WITHOUT_PARENT;
			वापस खाताID_INVALID;
		पूर्ण
	पूर्ण

	i_pos = fat_i_pos_पढ़ो(sbi, inode);
	*lenp = FAT_FID_SIZE_WITHOUT_PARENT;
	fid->i_gen = inode->i_generation;
	fid->i_pos_low = i_pos & 0xFFFFFFFF;
	fid->i_pos_hi = (i_pos >> 32) & 0xFFFF;
	अगर (parent) अणु
		i_pos = fat_i_pos_पढ़ो(sbi, parent);
		fid->parent_i_pos_hi = (i_pos >> 32) & 0xFFFF;
		fid->parent_i_pos_low = i_pos & 0xFFFFFFFF;
		fid->parent_i_gen = parent->i_generation;
		type = खाताID_FAT_WITH_PARENT;
		*lenp = FAT_FID_SIZE_WITH_PARENT;
	पूर्ण

	वापस type;
पूर्ण

/**
 * Map a NFS file handle to a corresponding dentry.
 * The dentry may or may not be connected to the fileप्रणाली root.
 */
अटल काष्ठा dentry *fat_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
				पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    fat_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *fat_fh_to_dentry_nostale(काष्ठा super_block *sb,
					       काष्ठा fid *fh, पूर्णांक fh_len,
					       पूर्णांक fh_type)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा fat_fid *fid = (काष्ठा fat_fid *)fh;
	loff_t i_pos;

	चयन (fh_type) अणु
	हाल खाताID_FAT_WITHOUT_PARENT:
		अगर (fh_len < FAT_FID_SIZE_WITHOUT_PARENT)
			वापस शून्य;
		अवरोध;
	हाल खाताID_FAT_WITH_PARENT:
		अगर (fh_len < FAT_FID_SIZE_WITH_PARENT)
			वापस शून्य;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण
	i_pos = fid->i_pos_hi;
	i_pos = (i_pos << 32) | (fid->i_pos_low);
	inode = __fat_nfs_get_inode(sb, 0, fid->i_gen, i_pos);

	वापस d_obtain_alias(inode);
पूर्ण

/*
 * Find the parent क्रम a file specअगरied by NFS handle.
 * This requires that the handle contain the i_ino of the parent.
 */
अटल काष्ठा dentry *fat_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
				पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    fat_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *fat_fh_to_parent_nostale(काष्ठा super_block *sb,
					       काष्ठा fid *fh, पूर्णांक fh_len,
					       पूर्णांक fh_type)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा fat_fid *fid = (काष्ठा fat_fid *)fh;
	loff_t i_pos;

	अगर (fh_len < FAT_FID_SIZE_WITH_PARENT)
		वापस शून्य;

	चयन (fh_type) अणु
	हाल खाताID_FAT_WITH_PARENT:
		i_pos = fid->parent_i_pos_hi;
		i_pos = (i_pos << 32) | (fid->parent_i_pos_low);
		inode = __fat_nfs_get_inode(sb, 0, fid->parent_i_gen, i_pos);
		अवरोध;
	पूर्ण

	वापस d_obtain_alias(inode);
पूर्ण

/*
 * Rebuild the parent क्रम a directory that is not connected
 *  to the fileप्रणाली root
 */
अटल
काष्ठा inode *fat_rebuild_parent(काष्ठा super_block *sb, पूर्णांक parent_logstart)
अणु
	पूर्णांक search_clus, clus_to_match;
	काष्ठा msकरोs_dir_entry *de;
	काष्ठा inode *parent = शून्य;
	काष्ठा inode *dummy_gअक्रम_parent = शून्य;
	काष्ठा fat_slot_info sinfo;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	sector_t blknr = fat_clus_to_blknr(sbi, parent_logstart);
	काष्ठा buffer_head *parent_bh = sb_bपढ़ो(sb, blknr);
	अगर (!parent_bh) अणु
		fat_msg(sb, KERN_ERR,
			"unable to read cluster of parent directory");
		वापस शून्य;
	पूर्ण

	de = (काष्ठा msकरोs_dir_entry *) parent_bh->b_data;
	clus_to_match = fat_get_start(sbi, &de[0]);
	search_clus = fat_get_start(sbi, &de[1]);

	dummy_gअक्रम_parent = fat_dget(sb, search_clus);
	अगर (!dummy_gअक्रम_parent) अणु
		dummy_gअक्रम_parent = new_inode(sb);
		अगर (!dummy_gअक्रम_parent) अणु
			brअन्यथा(parent_bh);
			वापस parent;
		पूर्ण

		dummy_gअक्रम_parent->i_ino = iunique(sb, MSDOS_ROOT_INO);
		fat_fill_inode(dummy_gअक्रम_parent, &de[1]);
		MSDOS_I(dummy_gअक्रम_parent)->i_pos = -1;
	पूर्ण

	अगर (!fat_scan_logstart(dummy_gअक्रम_parent, clus_to_match, &sinfo))
		parent = fat_build_inode(sb, sinfo.de, sinfo.i_pos);

	brअन्यथा(parent_bh);
	iput(dummy_gअक्रम_parent);

	वापस parent;
पूर्ण

/*
 * Find the parent क्रम a directory that is not currently connected to
 * the fileप्रणाली root.
 *
 * On entry, the caller holds d_inode(child_dir)->i_mutex.
 */
अटल काष्ठा dentry *fat_get_parent(काष्ठा dentry *child_dir)
अणु
	काष्ठा super_block *sb = child_dir->d_sb;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा msकरोs_dir_entry *de;
	काष्ठा inode *parent_inode = शून्य;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);

	अगर (!fat_get_करोtकरोt_entry(d_inode(child_dir), &bh, &de)) अणु
		पूर्णांक parent_logstart = fat_get_start(sbi, de);
		parent_inode = fat_dget(sb, parent_logstart);
		अगर (!parent_inode && sbi->options.nfs == FAT_NFS_NOSTALE_RO)
			parent_inode = fat_rebuild_parent(sb, parent_logstart);
	पूर्ण
	brअन्यथा(bh);

	वापस d_obtain_alias(parent_inode);
पूर्ण

स्थिर काष्ठा export_operations fat_export_ops = अणु
	.fh_to_dentry   = fat_fh_to_dentry,
	.fh_to_parent   = fat_fh_to_parent,
	.get_parent     = fat_get_parent,
पूर्ण;

स्थिर काष्ठा export_operations fat_export_ops_nostale = अणु
	.encode_fh      = fat_encode_fh_nostale,
	.fh_to_dentry   = fat_fh_to_dentry_nostale,
	.fh_to_parent   = fat_fh_to_parent_nostale,
	.get_parent     = fat_get_parent,
पूर्ण;
