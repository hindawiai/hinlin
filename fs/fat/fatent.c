<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, OGAWA Hirofumi
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "fat.h"

काष्ठा fatent_operations अणु
	व्योम (*ent_blocknr)(काष्ठा super_block *, पूर्णांक, पूर्णांक *, sector_t *);
	व्योम (*ent_set_ptr)(काष्ठा fat_entry *, पूर्णांक);
	पूर्णांक (*ent_bपढ़ो)(काष्ठा super_block *, काष्ठा fat_entry *,
			 पूर्णांक, sector_t);
	पूर्णांक (*ent_get)(काष्ठा fat_entry *);
	व्योम (*ent_put)(काष्ठा fat_entry *, पूर्णांक);
	पूर्णांक (*ent_next)(काष्ठा fat_entry *);
पूर्ण;

अटल DEFINE_SPINLOCK(fat12_entry_lock);

अटल व्योम fat12_ent_blocknr(काष्ठा super_block *sb, पूर्णांक entry,
			      पूर्णांक *offset, sector_t *blocknr)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक bytes = entry + (entry >> 1);
	WARN_ON(!fat_valid_entry(sbi, entry));
	*offset = bytes & (sb->s_blocksize - 1);
	*blocknr = sbi->fat_start + (bytes >> sb->s_blocksize_bits);
पूर्ण

अटल व्योम fat_ent_blocknr(काष्ठा super_block *sb, पूर्णांक entry,
			    पूर्णांक *offset, sector_t *blocknr)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक bytes = (entry << sbi->fatent_shअगरt);
	WARN_ON(!fat_valid_entry(sbi, entry));
	*offset = bytes & (sb->s_blocksize - 1);
	*blocknr = sbi->fat_start + (bytes >> sb->s_blocksize_bits);
पूर्ण

अटल व्योम fat12_ent_set_ptr(काष्ठा fat_entry *fatent, पूर्णांक offset)
अणु
	काष्ठा buffer_head **bhs = fatent->bhs;
	अगर (fatent->nr_bhs == 1) अणु
		WARN_ON(offset >= (bhs[0]->b_size - 1));
		fatent->u.ent12_p[0] = bhs[0]->b_data + offset;
		fatent->u.ent12_p[1] = bhs[0]->b_data + (offset + 1);
	पूर्ण अन्यथा अणु
		WARN_ON(offset != (bhs[0]->b_size - 1));
		fatent->u.ent12_p[0] = bhs[0]->b_data + offset;
		fatent->u.ent12_p[1] = bhs[1]->b_data;
	पूर्ण
पूर्ण

अटल व्योम fat16_ent_set_ptr(काष्ठा fat_entry *fatent, पूर्णांक offset)
अणु
	WARN_ON(offset & (2 - 1));
	fatent->u.ent16_p = (__le16 *)(fatent->bhs[0]->b_data + offset);
पूर्ण

अटल व्योम fat32_ent_set_ptr(काष्ठा fat_entry *fatent, पूर्णांक offset)
अणु
	WARN_ON(offset & (4 - 1));
	fatent->u.ent32_p = (__le32 *)(fatent->bhs[0]->b_data + offset);
पूर्ण

अटल पूर्णांक fat12_ent_bपढ़ो(काष्ठा super_block *sb, काष्ठा fat_entry *fatent,
			   पूर्णांक offset, sector_t blocknr)
अणु
	काष्ठा buffer_head **bhs = fatent->bhs;

	WARN_ON(blocknr < MSDOS_SB(sb)->fat_start);
	fatent->fat_inode = MSDOS_SB(sb)->fat_inode;

	bhs[0] = sb_bपढ़ो(sb, blocknr);
	अगर (!bhs[0])
		जाओ err;

	अगर ((offset + 1) < sb->s_blocksize)
		fatent->nr_bhs = 1;
	अन्यथा अणु
		/* This entry is block boundary, it needs the next block */
		blocknr++;
		bhs[1] = sb_bपढ़ो(sb, blocknr);
		अगर (!bhs[1])
			जाओ err_brअन्यथा;
		fatent->nr_bhs = 2;
	पूर्ण
	fat12_ent_set_ptr(fatent, offset);
	वापस 0;

err_brअन्यथा:
	brअन्यथा(bhs[0]);
err:
	fat_msg(sb, KERN_ERR, "FAT read failed (blocknr %llu)", (llu)blocknr);
	वापस -EIO;
पूर्ण

अटल पूर्णांक fat_ent_bपढ़ो(काष्ठा super_block *sb, काष्ठा fat_entry *fatent,
			 पूर्णांक offset, sector_t blocknr)
अणु
	स्थिर काष्ठा fatent_operations *ops = MSDOS_SB(sb)->fatent_ops;

	WARN_ON(blocknr < MSDOS_SB(sb)->fat_start);
	fatent->fat_inode = MSDOS_SB(sb)->fat_inode;
	fatent->bhs[0] = sb_bपढ़ो(sb, blocknr);
	अगर (!fatent->bhs[0]) अणु
		fat_msg(sb, KERN_ERR, "FAT read failed (blocknr %llu)",
		       (llu)blocknr);
		वापस -EIO;
	पूर्ण
	fatent->nr_bhs = 1;
	ops->ent_set_ptr(fatent, offset);
	वापस 0;
पूर्ण

अटल पूर्णांक fat12_ent_get(काष्ठा fat_entry *fatent)
अणु
	u8 **ent12_p = fatent->u.ent12_p;
	पूर्णांक next;

	spin_lock(&fat12_entry_lock);
	अगर (fatent->entry & 1)
		next = (*ent12_p[0] >> 4) | (*ent12_p[1] << 4);
	अन्यथा
		next = (*ent12_p[1] << 8) | *ent12_p[0];
	spin_unlock(&fat12_entry_lock);

	next &= 0x0fff;
	अगर (next >= BAD_FAT12)
		next = FAT_ENT_खातापूर्ण;
	वापस next;
पूर्ण

अटल पूर्णांक fat16_ent_get(काष्ठा fat_entry *fatent)
अणु
	पूर्णांक next = le16_to_cpu(*fatent->u.ent16_p);
	WARN_ON((अचिन्हित दीर्घ)fatent->u.ent16_p & (2 - 1));
	अगर (next >= BAD_FAT16)
		next = FAT_ENT_खातापूर्ण;
	वापस next;
पूर्ण

अटल पूर्णांक fat32_ent_get(काष्ठा fat_entry *fatent)
अणु
	पूर्णांक next = le32_to_cpu(*fatent->u.ent32_p) & 0x0fffffff;
	WARN_ON((अचिन्हित दीर्घ)fatent->u.ent32_p & (4 - 1));
	अगर (next >= BAD_FAT32)
		next = FAT_ENT_खातापूर्ण;
	वापस next;
पूर्ण

अटल व्योम fat12_ent_put(काष्ठा fat_entry *fatent, पूर्णांक new)
अणु
	u8 **ent12_p = fatent->u.ent12_p;

	अगर (new == FAT_ENT_खातापूर्ण)
		new = खातापूर्ण_FAT12;

	spin_lock(&fat12_entry_lock);
	अगर (fatent->entry & 1) अणु
		*ent12_p[0] = (new << 4) | (*ent12_p[0] & 0x0f);
		*ent12_p[1] = new >> 4;
	पूर्ण अन्यथा अणु
		*ent12_p[0] = new & 0xff;
		*ent12_p[1] = (*ent12_p[1] & 0xf0) | (new >> 8);
	पूर्ण
	spin_unlock(&fat12_entry_lock);

	mark_buffer_dirty_inode(fatent->bhs[0], fatent->fat_inode);
	अगर (fatent->nr_bhs == 2)
		mark_buffer_dirty_inode(fatent->bhs[1], fatent->fat_inode);
पूर्ण

अटल व्योम fat16_ent_put(काष्ठा fat_entry *fatent, पूर्णांक new)
अणु
	अगर (new == FAT_ENT_खातापूर्ण)
		new = खातापूर्ण_FAT16;

	*fatent->u.ent16_p = cpu_to_le16(new);
	mark_buffer_dirty_inode(fatent->bhs[0], fatent->fat_inode);
पूर्ण

अटल व्योम fat32_ent_put(काष्ठा fat_entry *fatent, पूर्णांक new)
अणु
	WARN_ON(new & 0xf0000000);
	new |= le32_to_cpu(*fatent->u.ent32_p) & ~0x0fffffff;
	*fatent->u.ent32_p = cpu_to_le32(new);
	mark_buffer_dirty_inode(fatent->bhs[0], fatent->fat_inode);
पूर्ण

अटल पूर्णांक fat12_ent_next(काष्ठा fat_entry *fatent)
अणु
	u8 **ent12_p = fatent->u.ent12_p;
	काष्ठा buffer_head **bhs = fatent->bhs;
	u8 *nextp = ent12_p[1] + 1 + (fatent->entry & 1);

	fatent->entry++;
	अगर (fatent->nr_bhs == 1) अणु
		WARN_ON(ent12_p[0] > (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 2)));
		WARN_ON(ent12_p[1] > (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 1)));
		अगर (nextp < (u8 *)(bhs[0]->b_data + (bhs[0]->b_size - 1))) अणु
			ent12_p[0] = nextp - 1;
			ent12_p[1] = nextp;
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(ent12_p[0] != (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 1)));
		WARN_ON(ent12_p[1] != (u8 *)bhs[1]->b_data);
		ent12_p[0] = nextp - 1;
		ent12_p[1] = nextp;
		brअन्यथा(bhs[0]);
		bhs[0] = bhs[1];
		fatent->nr_bhs = 1;
		वापस 1;
	पूर्ण
	ent12_p[0] = शून्य;
	ent12_p[1] = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक fat16_ent_next(काष्ठा fat_entry *fatent)
अणु
	स्थिर काष्ठा buffer_head *bh = fatent->bhs[0];
	fatent->entry++;
	अगर (fatent->u.ent16_p < (__le16 *)(bh->b_data + (bh->b_size - 2))) अणु
		fatent->u.ent16_p++;
		वापस 1;
	पूर्ण
	fatent->u.ent16_p = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक fat32_ent_next(काष्ठा fat_entry *fatent)
अणु
	स्थिर काष्ठा buffer_head *bh = fatent->bhs[0];
	fatent->entry++;
	अगर (fatent->u.ent32_p < (__le32 *)(bh->b_data + (bh->b_size - 4))) अणु
		fatent->u.ent32_p++;
		वापस 1;
	पूर्ण
	fatent->u.ent32_p = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fatent_operations fat12_ops = अणु
	.ent_blocknr	= fat12_ent_blocknr,
	.ent_set_ptr	= fat12_ent_set_ptr,
	.ent_bपढ़ो	= fat12_ent_bपढ़ो,
	.ent_get	= fat12_ent_get,
	.ent_put	= fat12_ent_put,
	.ent_next	= fat12_ent_next,
पूर्ण;

अटल स्थिर काष्ठा fatent_operations fat16_ops = अणु
	.ent_blocknr	= fat_ent_blocknr,
	.ent_set_ptr	= fat16_ent_set_ptr,
	.ent_bपढ़ो	= fat_ent_bपढ़ो,
	.ent_get	= fat16_ent_get,
	.ent_put	= fat16_ent_put,
	.ent_next	= fat16_ent_next,
पूर्ण;

अटल स्थिर काष्ठा fatent_operations fat32_ops = अणु
	.ent_blocknr	= fat_ent_blocknr,
	.ent_set_ptr	= fat32_ent_set_ptr,
	.ent_bपढ़ो	= fat_ent_bपढ़ो,
	.ent_get	= fat32_ent_get,
	.ent_put	= fat32_ent_put,
	.ent_next	= fat32_ent_next,
पूर्ण;

अटल अंतरभूत व्योम lock_fat(काष्ठा msकरोs_sb_info *sbi)
अणु
	mutex_lock(&sbi->fat_lock);
पूर्ण

अटल अंतरभूत व्योम unlock_fat(काष्ठा msकरोs_sb_info *sbi)
अणु
	mutex_unlock(&sbi->fat_lock);
पूर्ण

व्योम fat_ent_access_init(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);

	mutex_init(&sbi->fat_lock);

	अगर (is_fat32(sbi)) अणु
		sbi->fatent_shअगरt = 2;
		sbi->fatent_ops = &fat32_ops;
	पूर्ण अन्यथा अगर (is_fat16(sbi)) अणु
		sbi->fatent_shअगरt = 1;
		sbi->fatent_ops = &fat16_ops;
	पूर्ण अन्यथा अगर (is_fat12(sbi)) अणु
		sbi->fatent_shअगरt = -1;
		sbi->fatent_ops = &fat12_ops;
	पूर्ण अन्यथा अणु
		fat_fs_error(sb, "invalid FAT variant, %u bits", sbi->fat_bits);
	पूर्ण
पूर्ण

अटल व्योम mark_fsinfo_dirty(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);

	अगर (sb_rकरोnly(sb) || !is_fat32(sbi))
		वापस;

	__mark_inode_dirty(sbi->fsinfo_inode, I_सूचीTY_SYNC);
पूर्ण

अटल अंतरभूत पूर्णांक fat_ent_update_ptr(काष्ठा super_block *sb,
				     काष्ठा fat_entry *fatent,
				     पूर्णांक offset, sector_t blocknr)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
	काष्ठा buffer_head **bhs = fatent->bhs;

	/* Is this fatent's blocks including this entry? */
	अगर (!fatent->nr_bhs || bhs[0]->b_blocknr != blocknr)
		वापस 0;
	अगर (is_fat12(sbi)) अणु
		अगर ((offset + 1) < sb->s_blocksize) अणु
			/* This entry is on bhs[0]. */
			अगर (fatent->nr_bhs == 2) अणु
				brअन्यथा(bhs[1]);
				fatent->nr_bhs = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* This entry needs the next block. */
			अगर (fatent->nr_bhs != 2)
				वापस 0;
			अगर (bhs[1]->b_blocknr != (blocknr + 1))
				वापस 0;
		पूर्ण
	पूर्ण
	ops->ent_set_ptr(fatent, offset);
	वापस 1;
पूर्ण

पूर्णांक fat_ent_पढ़ो(काष्ठा inode *inode, काष्ठा fat_entry *fatent, पूर्णांक entry)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
	पूर्णांक err, offset;
	sector_t blocknr;

	अगर (!fat_valid_entry(sbi, entry)) अणु
		fatent_brअन्यथा(fatent);
		fat_fs_error(sb, "invalid access to FAT (entry 0x%08x)", entry);
		वापस -EIO;
	पूर्ण

	fatent_set_entry(fatent, entry);
	ops->ent_blocknr(sb, entry, &offset, &blocknr);

	अगर (!fat_ent_update_ptr(sb, fatent, offset, blocknr)) अणु
		fatent_brअन्यथा(fatent);
		err = ops->ent_bपढ़ो(sb, fatent, offset, blocknr);
		अगर (err)
			वापस err;
	पूर्ण
	वापस ops->ent_get(fatent);
पूर्ण

/* FIXME: We can ग_लिखो the blocks as more big chunk. */
अटल पूर्णांक fat_mirror_bhs(काष्ठा super_block *sb, काष्ठा buffer_head **bhs,
			  पूर्णांक nr_bhs)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *c_bh;
	पूर्णांक err, n, copy;

	err = 0;
	क्रम (copy = 1; copy < sbi->fats; copy++) अणु
		sector_t backup_fat = sbi->fat_length * copy;

		क्रम (n = 0; n < nr_bhs; n++) अणु
			c_bh = sb_getblk(sb, backup_fat + bhs[n]->b_blocknr);
			अगर (!c_bh) अणु
				err = -ENOMEM;
				जाओ error;
			पूर्ण
			/* Aव्योम race with userspace पढ़ो via bdev */
			lock_buffer(c_bh);
			स_नकल(c_bh->b_data, bhs[n]->b_data, sb->s_blocksize);
			set_buffer_uptodate(c_bh);
			unlock_buffer(c_bh);
			mark_buffer_dirty_inode(c_bh, sbi->fat_inode);
			अगर (sb->s_flags & SB_SYNCHRONOUS)
				err = sync_dirty_buffer(c_bh);
			brअन्यथा(c_bh);
			अगर (err)
				जाओ error;
		पूर्ण
	पूर्ण
error:
	वापस err;
पूर्ण

पूर्णांक fat_ent_ग_लिखो(काष्ठा inode *inode, काष्ठा fat_entry *fatent,
		  पूर्णांक new, पूर्णांक रुको)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	स्थिर काष्ठा fatent_operations *ops = MSDOS_SB(sb)->fatent_ops;
	पूर्णांक err;

	ops->ent_put(fatent, new);
	अगर (रुको) अणु
		err = fat_sync_bhs(fatent->bhs, fatent->nr_bhs);
		अगर (err)
			वापस err;
	पूर्ण
	वापस fat_mirror_bhs(sb, fatent->bhs, fatent->nr_bhs);
पूर्ण

अटल अंतरभूत पूर्णांक fat_ent_next(काष्ठा msकरोs_sb_info *sbi,
			       काष्ठा fat_entry *fatent)
अणु
	अगर (sbi->fatent_ops->ent_next(fatent)) अणु
		अगर (fatent->entry < sbi->max_cluster)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fat_ent_पढ़ो_block(काष्ठा super_block *sb,
				     काष्ठा fat_entry *fatent)
अणु
	स्थिर काष्ठा fatent_operations *ops = MSDOS_SB(sb)->fatent_ops;
	sector_t blocknr;
	पूर्णांक offset;

	fatent_brअन्यथा(fatent);
	ops->ent_blocknr(sb, fatent->entry, &offset, &blocknr);
	वापस ops->ent_bपढ़ो(sb, fatent, offset, blocknr);
पूर्ण

अटल व्योम fat_collect_bhs(काष्ठा buffer_head **bhs, पूर्णांक *nr_bhs,
			    काष्ठा fat_entry *fatent)
अणु
	पूर्णांक n, i;

	क्रम (n = 0; n < fatent->nr_bhs; n++) अणु
		क्रम (i = 0; i < *nr_bhs; i++) अणु
			अगर (fatent->bhs[n] == bhs[i])
				अवरोध;
		पूर्ण
		अगर (i == *nr_bhs) अणु
			get_bh(fatent->bhs[n]);
			bhs[i] = fatent->bhs[n];
			(*nr_bhs)++;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक fat_alloc_clusters(काष्ठा inode *inode, पूर्णांक *cluster, पूर्णांक nr_cluster)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
	काष्ठा fat_entry fatent, prev_ent;
	काष्ठा buffer_head *bhs[MAX_BUF_PER_PAGE];
	पूर्णांक i, count, err, nr_bhs, idx_clus;

	BUG_ON(nr_cluster > (MAX_BUF_PER_PAGE / 2));	/* fixed limit */

	lock_fat(sbi);
	अगर (sbi->मुक्त_clusters != -1 && sbi->मुक्त_clus_valid &&
	    sbi->मुक्त_clusters < nr_cluster) अणु
		unlock_fat(sbi);
		वापस -ENOSPC;
	पूर्ण

	err = nr_bhs = idx_clus = 0;
	count = FAT_START_ENT;
	fatent_init(&prev_ent);
	fatent_init(&fatent);
	fatent_set_entry(&fatent, sbi->prev_मुक्त + 1);
	जबतक (count < sbi->max_cluster) अणु
		अगर (fatent.entry >= sbi->max_cluster)
			fatent.entry = FAT_START_ENT;
		fatent_set_entry(&fatent, fatent.entry);
		err = fat_ent_पढ़ो_block(sb, &fatent);
		अगर (err)
			जाओ out;

		/* Find the मुक्त entries in a block */
		करो अणु
			अगर (ops->ent_get(&fatent) == FAT_ENT_FREE) अणु
				पूर्णांक entry = fatent.entry;

				/* make the cluster chain */
				ops->ent_put(&fatent, FAT_ENT_खातापूर्ण);
				अगर (prev_ent.nr_bhs)
					ops->ent_put(&prev_ent, entry);

				fat_collect_bhs(bhs, &nr_bhs, &fatent);

				sbi->prev_मुक्त = entry;
				अगर (sbi->मुक्त_clusters != -1)
					sbi->मुक्त_clusters--;

				cluster[idx_clus] = entry;
				idx_clus++;
				अगर (idx_clus == nr_cluster)
					जाओ out;

				/*
				 * fat_collect_bhs() माला_लो ref-count of bhs,
				 * so we can still use the prev_ent.
				 */
				prev_ent = fatent;
			पूर्ण
			count++;
			अगर (count == sbi->max_cluster)
				अवरोध;
		पूर्ण जबतक (fat_ent_next(sbi, &fatent));
	पूर्ण

	/* Couldn't allocate the मुक्त entries */
	sbi->मुक्त_clusters = 0;
	sbi->मुक्त_clus_valid = 1;
	err = -ENOSPC;

out:
	unlock_fat(sbi);
	mark_fsinfo_dirty(sb);
	fatent_brअन्यथा(&fatent);
	अगर (!err) अणु
		अगर (inode_needs_sync(inode))
			err = fat_sync_bhs(bhs, nr_bhs);
		अगर (!err)
			err = fat_mirror_bhs(sb, bhs, nr_bhs);
	पूर्ण
	क्रम (i = 0; i < nr_bhs; i++)
		brअन्यथा(bhs[i]);

	अगर (err && idx_clus)
		fat_मुक्त_clusters(inode, cluster[0]);

	वापस err;
पूर्ण

पूर्णांक fat_मुक्त_clusters(काष्ठा inode *inode, पूर्णांक cluster)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
	काष्ठा fat_entry fatent;
	काष्ठा buffer_head *bhs[MAX_BUF_PER_PAGE];
	पूर्णांक i, err, nr_bhs;
	पूर्णांक first_cl = cluster, dirty_fsinfo = 0;

	nr_bhs = 0;
	fatent_init(&fatent);
	lock_fat(sbi);
	करो अणु
		cluster = fat_ent_पढ़ो(inode, &fatent, cluster);
		अगर (cluster < 0) अणु
			err = cluster;
			जाओ error;
		पूर्ण अन्यथा अगर (cluster == FAT_ENT_FREE) अणु
			fat_fs_error(sb, "%s: deleting FAT entry beyond EOF",
				     __func__);
			err = -EIO;
			जाओ error;
		पूर्ण

		अगर (sbi->options.discard) अणु
			/*
			 * Issue discard क्रम the sectors we no दीर्घer
			 * care about, batching contiguous clusters
			 * पूर्णांकo one request
			 */
			अगर (cluster != fatent.entry + 1) अणु
				पूर्णांक nr_clus = fatent.entry - first_cl + 1;

				sb_issue_discard(sb,
					fat_clus_to_blknr(sbi, first_cl),
					nr_clus * sbi->sec_per_clus,
					GFP_NOFS, 0);

				first_cl = cluster;
			पूर्ण
		पूर्ण

		ops->ent_put(&fatent, FAT_ENT_FREE);
		अगर (sbi->मुक्त_clusters != -1) अणु
			sbi->मुक्त_clusters++;
			dirty_fsinfo = 1;
		पूर्ण

		अगर (nr_bhs + fatent.nr_bhs > MAX_BUF_PER_PAGE) अणु
			अगर (sb->s_flags & SB_SYNCHRONOUS) अणु
				err = fat_sync_bhs(bhs, nr_bhs);
				अगर (err)
					जाओ error;
			पूर्ण
			err = fat_mirror_bhs(sb, bhs, nr_bhs);
			अगर (err)
				जाओ error;
			क्रम (i = 0; i < nr_bhs; i++)
				brअन्यथा(bhs[i]);
			nr_bhs = 0;
		पूर्ण
		fat_collect_bhs(bhs, &nr_bhs, &fatent);
	पूर्ण जबतक (cluster != FAT_ENT_खातापूर्ण);

	अगर (sb->s_flags & SB_SYNCHRONOUS) अणु
		err = fat_sync_bhs(bhs, nr_bhs);
		अगर (err)
			जाओ error;
	पूर्ण
	err = fat_mirror_bhs(sb, bhs, nr_bhs);
error:
	fatent_brअन्यथा(&fatent);
	क्रम (i = 0; i < nr_bhs; i++)
		brअन्यथा(bhs[i]);
	unlock_fat(sbi);
	अगर (dirty_fsinfo)
		mark_fsinfo_dirty(sb);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fat_मुक्त_clusters);

काष्ठा fatent_ra अणु
	sector_t cur;
	sector_t limit;

	अचिन्हित पूर्णांक ra_blocks;
	sector_t ra_advance;
	sector_t ra_next;
	sector_t ra_limit;
पूर्ण;

अटल व्योम fat_ra_init(काष्ठा super_block *sb, काष्ठा fatent_ra *ra,
			काष्ठा fat_entry *fatent, पूर्णांक ent_limit)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
	sector_t blocknr, block_end;
	पूर्णांक offset;
	/*
	 * This is the sequential पढ़ो, so ra_pages * 2 (but try to
	 * align the optimal hardware IO size).
	 * [BTW, 128kb covers the whole sectors क्रम FAT12 and FAT16]
	 */
	अचिन्हित दीर्घ ra_pages = sb->s_bdi->ra_pages;
	अचिन्हित पूर्णांक पढ़ोa_blocks;

	अगर (fatent->entry >= ent_limit)
		वापस;

	अगर (ra_pages > sb->s_bdi->io_pages)
		ra_pages = roundकरोwn(ra_pages, sb->s_bdi->io_pages);
	पढ़ोa_blocks = ra_pages << (PAGE_SHIFT - sb->s_blocksize_bits + 1);

	/* Initialize the range क्रम sequential पढ़ो */
	ops->ent_blocknr(sb, fatent->entry, &offset, &blocknr);
	ops->ent_blocknr(sb, ent_limit - 1, &offset, &block_end);
	ra->cur = 0;
	ra->limit = (block_end + 1) - blocknr;

	/* Advancing the winकरोw at half size */
	ra->ra_blocks = पढ़ोa_blocks >> 1;
	ra->ra_advance = ra->cur;
	ra->ra_next = ra->cur;
	ra->ra_limit = ra->cur + min_t(sector_t, पढ़ोa_blocks, ra->limit);
पूर्ण

/* Assuming to be called beक्रमe पढ़ोing a new block (increments ->cur). */
अटल व्योम fat_ent_पढ़ोa(काष्ठा super_block *sb, काष्ठा fatent_ra *ra,
			  काष्ठा fat_entry *fatent)
अणु
	अगर (ra->ra_next >= ra->ra_limit)
		वापस;

	अगर (ra->cur >= ra->ra_advance) अणु
		काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
		स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
		काष्ठा blk_plug plug;
		sector_t blocknr, dअगरf;
		पूर्णांक offset;

		ops->ent_blocknr(sb, fatent->entry, &offset, &blocknr);

		dअगरf = blocknr - ra->cur;
		blk_start_plug(&plug);
		/*
		 * FIXME: we would want to directly use the bio with
		 * pages to reduce the number of segments.
		 */
		क्रम (; ra->ra_next < ra->ra_limit; ra->ra_next++)
			sb_bपढ़ोahead(sb, ra->ra_next + dअगरf);
		blk_finish_plug(&plug);

		/* Advance the पढ़ोahead winकरोw */
		ra->ra_advance += ra->ra_blocks;
		ra->ra_limit += min_t(sector_t,
				      ra->ra_blocks, ra->limit - ra->ra_limit);
	पूर्ण
	ra->cur++;
पूर्ण

पूर्णांक fat_count_मुक्त_clusters(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
	काष्ठा fat_entry fatent;
	काष्ठा fatent_ra fatent_ra;
	पूर्णांक err = 0, मुक्त;

	lock_fat(sbi);
	अगर (sbi->मुक्त_clusters != -1 && sbi->मुक्त_clus_valid)
		जाओ out;

	मुक्त = 0;
	fatent_init(&fatent);
	fatent_set_entry(&fatent, FAT_START_ENT);
	fat_ra_init(sb, &fatent_ra, &fatent, sbi->max_cluster);
	जबतक (fatent.entry < sbi->max_cluster) अणु
		/* पढ़ोahead of fat blocks */
		fat_ent_पढ़ोa(sb, &fatent_ra, &fatent);

		err = fat_ent_पढ़ो_block(sb, &fatent);
		अगर (err)
			जाओ out;

		करो अणु
			अगर (ops->ent_get(&fatent) == FAT_ENT_FREE)
				मुक्त++;
		पूर्ण जबतक (fat_ent_next(sbi, &fatent));
		cond_resched();
	पूर्ण
	sbi->मुक्त_clusters = मुक्त;
	sbi->मुक्त_clus_valid = 1;
	mark_fsinfo_dirty(sb);
	fatent_brअन्यथा(&fatent);
out:
	unlock_fat(sbi);
	वापस err;
पूर्ण

अटल पूर्णांक fat_trim_clusters(काष्ठा super_block *sb, u32 clus, u32 nr_clus)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	वापस sb_issue_discard(sb, fat_clus_to_blknr(sbi, clus),
				nr_clus * sbi->sec_per_clus, GFP_NOFS, 0);
पूर्ण

पूर्णांक fat_trim_fs(काष्ठा inode *inode, काष्ठा fstrim_range *range)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	स्थिर काष्ठा fatent_operations *ops = sbi->fatent_ops;
	काष्ठा fat_entry fatent;
	काष्ठा fatent_ra fatent_ra;
	u64 ent_start, ent_end, minlen, trimmed = 0;
	u32 मुक्त = 0;
	पूर्णांक err = 0;

	/*
	 * FAT data is organized as clusters, trim at the granulary of cluster.
	 *
	 * fstrim_range is in byte, convert values to cluster index.
	 * Treat sectors beक्रमe data region as all used, not to trim them.
	 */
	ent_start = max_t(u64, range->start>>sbi->cluster_bits, FAT_START_ENT);
	ent_end = ent_start + (range->len >> sbi->cluster_bits) - 1;
	minlen = range->minlen >> sbi->cluster_bits;

	अगर (ent_start >= sbi->max_cluster || range->len < sbi->cluster_size)
		वापस -EINVAL;
	अगर (ent_end >= sbi->max_cluster)
		ent_end = sbi->max_cluster - 1;

	fatent_init(&fatent);
	lock_fat(sbi);
	fatent_set_entry(&fatent, ent_start);
	fat_ra_init(sb, &fatent_ra, &fatent, ent_end + 1);
	जबतक (fatent.entry <= ent_end) अणु
		/* पढ़ोahead of fat blocks */
		fat_ent_पढ़ोa(sb, &fatent_ra, &fatent);

		err = fat_ent_पढ़ो_block(sb, &fatent);
		अगर (err)
			जाओ error;
		करो अणु
			अगर (ops->ent_get(&fatent) == FAT_ENT_FREE) अणु
				मुक्त++;
			पूर्ण अन्यथा अगर (मुक्त) अणु
				अगर (मुक्त >= minlen) अणु
					u32 clus = fatent.entry - मुक्त;

					err = fat_trim_clusters(sb, clus, मुक्त);
					अगर (err && err != -EOPNOTSUPP)
						जाओ error;
					अगर (!err)
						trimmed += मुक्त;
					err = 0;
				पूर्ण
				मुक्त = 0;
			पूर्ण
		पूर्ण जबतक (fat_ent_next(sbi, &fatent) && fatent.entry <= ent_end);

		अगर (fatal_संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ error;
		पूर्ण

		अगर (need_resched()) अणु
			fatent_brअन्यथा(&fatent);
			unlock_fat(sbi);
			cond_resched();
			lock_fat(sbi);
		पूर्ण
	पूर्ण
	/* handle scenario when tail entries are all मुक्त */
	अगर (मुक्त && मुक्त >= minlen) अणु
		u32 clus = fatent.entry - मुक्त;

		err = fat_trim_clusters(sb, clus, मुक्त);
		अगर (err && err != -EOPNOTSUPP)
			जाओ error;
		अगर (!err)
			trimmed += मुक्त;
		err = 0;
	पूर्ण

error:
	fatent_brअन्यथा(&fatent);
	unlock_fat(sbi);

	range->len = trimmed << sbi->cluster_bits;

	वापस err;
पूर्ण
