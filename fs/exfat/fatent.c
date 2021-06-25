<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/buffer_head.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

अटल पूर्णांक exfat_mirror_bh(काष्ठा super_block *sb, sector_t sec,
		काष्ठा buffer_head *bh)
अणु
	काष्ठा buffer_head *c_bh;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	sector_t sec2;
	पूर्णांक err = 0;

	अगर (sbi->FAT2_start_sector != sbi->FAT1_start_sector) अणु
		sec2 = sec - sbi->FAT1_start_sector + sbi->FAT2_start_sector;
		c_bh = sb_getblk(sb, sec2);
		अगर (!c_bh)
			वापस -ENOMEM;
		स_नकल(c_bh->b_data, bh->b_data, sb->s_blocksize);
		set_buffer_uptodate(c_bh);
		mark_buffer_dirty(c_bh);
		अगर (sb->s_flags & SB_SYNCHRONOUS)
			err = sync_dirty_buffer(c_bh);
		brअन्यथा(c_bh);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __exfat_ent_get(काष्ठा super_block *sb, अचिन्हित पूर्णांक loc,
		अचिन्हित पूर्णांक *content)
अणु
	अचिन्हित पूर्णांक off;
	sector_t sec;
	काष्ठा buffer_head *bh;

	sec = FAT_ENT_OFFSET_SECTOR(sb, loc);
	off = FAT_ENT_OFFSET_BYTE_IN_SECTOR(sb, loc);

	bh = sb_bपढ़ो(sb, sec);
	अगर (!bh)
		वापस -EIO;

	*content = le32_to_cpu(*(__le32 *)(&bh->b_data[off]));

	/* remap reserved clusters to simplअगरy code */
	अगर (*content > EXFAT_BAD_CLUSTER)
		*content = EXFAT_खातापूर्ण_CLUSTER;

	brअन्यथा(bh);
	वापस 0;
पूर्ण

पूर्णांक exfat_ent_set(काष्ठा super_block *sb, अचिन्हित पूर्णांक loc,
		अचिन्हित पूर्णांक content)
अणु
	अचिन्हित पूर्णांक off;
	sector_t sec;
	__le32 *fat_entry;
	काष्ठा buffer_head *bh;

	sec = FAT_ENT_OFFSET_SECTOR(sb, loc);
	off = FAT_ENT_OFFSET_BYTE_IN_SECTOR(sb, loc);

	bh = sb_bपढ़ो(sb, sec);
	अगर (!bh)
		वापस -EIO;

	fat_entry = (__le32 *)&(bh->b_data[off]);
	*fat_entry = cpu_to_le32(content);
	exfat_update_bh(bh, sb->s_flags & SB_SYNCHRONOUS);
	exfat_mirror_bh(sb, sec, bh);
	brअन्यथा(bh);
	वापस 0;
पूर्ण

अटल अंतरभूत bool is_valid_cluster(काष्ठा exfat_sb_info *sbi,
		अचिन्हित पूर्णांक clus)
अणु
	अगर (clus < EXFAT_FIRST_CLUSTER || sbi->num_clusters <= clus)
		वापस false;
	वापस true;
पूर्ण

पूर्णांक exfat_ent_get(काष्ठा super_block *sb, अचिन्हित पूर्णांक loc,
		अचिन्हित पूर्णांक *content)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	पूर्णांक err;

	अगर (!is_valid_cluster(sbi, loc)) अणु
		exfat_fs_error(sb, "invalid access to FAT (entry 0x%08x)",
			loc);
		वापस -EIO;
	पूर्ण

	err = __exfat_ent_get(sb, loc, content);
	अगर (err) अणु
		exfat_fs_error(sb,
			"failed to access to FAT (entry 0x%08x, err:%d)",
			loc, err);
		वापस err;
	पूर्ण

	अगर (*content == EXFAT_FREE_CLUSTER) अणु
		exfat_fs_error(sb,
			"invalid access to FAT free cluster (entry 0x%08x)",
			loc);
		वापस -EIO;
	पूर्ण

	अगर (*content == EXFAT_BAD_CLUSTER) अणु
		exfat_fs_error(sb,
			"invalid access to FAT bad cluster (entry 0x%08x)",
			loc);
		वापस -EIO;
	पूर्ण

	अगर (*content != EXFAT_खातापूर्ण_CLUSTER && !is_valid_cluster(sbi, *content)) अणु
		exfat_fs_error(sb,
			"invalid access to FAT (entry 0x%08x) bogus content (0x%08x)",
			loc, *content);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक exfat_chain_cont_cluster(काष्ठा super_block *sb, अचिन्हित पूर्णांक chain,
		अचिन्हित पूर्णांक len)
अणु
	अगर (!len)
		वापस 0;

	जबतक (len > 1) अणु
		अगर (exfat_ent_set(sb, chain, chain + 1))
			वापस -EIO;
		chain++;
		len--;
	पूर्ण

	अगर (exfat_ent_set(sb, chain, EXFAT_खातापूर्ण_CLUSTER))
		वापस -EIO;
	वापस 0;
पूर्ण

/* This function must be called with biपंचांगap_lock held */
अटल पूर्णांक __exfat_मुक्त_cluster(काष्ठा inode *inode, काष्ठा exfat_chain *p_chain)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	पूर्णांक cur_cmap_i, next_cmap_i;
	अचिन्हित पूर्णांक num_clusters = 0;
	अचिन्हित पूर्णांक clu;

	/* invalid cluster number */
	अगर (p_chain->dir == EXFAT_FREE_CLUSTER ||
	    p_chain->dir == EXFAT_खातापूर्ण_CLUSTER ||
	    p_chain->dir < EXFAT_FIRST_CLUSTER)
		वापस 0;

	/* no cluster to truncate */
	अगर (p_chain->size == 0)
		वापस 0;

	/* check cluster validation */
	अगर (!is_valid_cluster(sbi, p_chain->dir)) अणु
		exfat_err(sb, "invalid start cluster (%u)", p_chain->dir);
		वापस -EIO;
	पूर्ण

	clu = p_chain->dir;

	cur_cmap_i = next_cmap_i =
		BITMAP_OFFSET_SECTOR_INDEX(sb, CLUSTER_TO_BITMAP_ENT(clu));

	अगर (p_chain->flags == ALLOC_NO_FAT_CHAIN) अणु
		अचिन्हित पूर्णांक last_cluster = p_chain->dir + p_chain->size - 1;
		करो अणु
			bool sync = false;

			अगर (clu < last_cluster)
				next_cmap_i =
				  BITMAP_OFFSET_SECTOR_INDEX(sb, CLUSTER_TO_BITMAP_ENT(clu+1));

			/* flush biपंचांगap only अगर index would be changed or क्रम last cluster */
			अगर (clu == last_cluster || cur_cmap_i != next_cmap_i) अणु
				sync = true;
				cur_cmap_i = next_cmap_i;
			पूर्ण

			exfat_clear_biपंचांगap(inode, clu, (sync && IS_सूचीSYNC(inode)));
			clu++;
			num_clusters++;
		पूर्ण जबतक (num_clusters < p_chain->size);
	पूर्ण अन्यथा अणु
		करो अणु
			bool sync = false;
			अचिन्हित पूर्णांक n_clu = clu;
			पूर्णांक err = exfat_get_next_cluster(sb, &n_clu);

			अगर (err || n_clu == EXFAT_खातापूर्ण_CLUSTER)
				sync = true;
			अन्यथा
				next_cmap_i =
				  BITMAP_OFFSET_SECTOR_INDEX(sb, CLUSTER_TO_BITMAP_ENT(n_clu));

			अगर (cur_cmap_i != next_cmap_i) अणु
				sync = true;
				cur_cmap_i = next_cmap_i;
			पूर्ण

			exfat_clear_biपंचांगap(inode, clu, (sync && IS_सूचीSYNC(inode)));
			clu = n_clu;
			num_clusters++;

			अगर (err)
				जाओ dec_used_clus;
		पूर्ण जबतक (clu != EXFAT_खातापूर्ण_CLUSTER);
	पूर्ण

dec_used_clus:
	sbi->used_clusters -= num_clusters;
	वापस 0;
पूर्ण

पूर्णांक exfat_मुक्त_cluster(काष्ठा inode *inode, काष्ठा exfat_chain *p_chain)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&EXFAT_SB(inode->i_sb)->biपंचांगap_lock);
	ret = __exfat_मुक्त_cluster(inode, p_chain);
	mutex_unlock(&EXFAT_SB(inode->i_sb)->biपंचांगap_lock);

	वापस ret;
पूर्ण

पूर्णांक exfat_find_last_cluster(काष्ठा super_block *sb, काष्ठा exfat_chain *p_chain,
		अचिन्हित पूर्णांक *ret_clu)
अणु
	अचिन्हित पूर्णांक clu, next;
	अचिन्हित पूर्णांक count = 0;

	next = p_chain->dir;
	अगर (p_chain->flags == ALLOC_NO_FAT_CHAIN) अणु
		*ret_clu = next + p_chain->size - 1;
		वापस 0;
	पूर्ण

	करो अणु
		count++;
		clu = next;
		अगर (exfat_ent_get(sb, clu, &next))
			वापस -EIO;
	पूर्ण जबतक (next != EXFAT_खातापूर्ण_CLUSTER);

	अगर (p_chain->size != count) अणु
		exfat_fs_error(sb,
			"bogus directory size (clus : ondisk(%d) != counted(%d))",
			p_chain->size, count);
		वापस -EIO;
	पूर्ण

	*ret_clu = clu;
	वापस 0;
पूर्ण

पूर्णांक exfat_zeroed_cluster(काष्ठा inode *dir, अचिन्हित पूर्णांक clu)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा buffer_head *bhs[MAX_BUF_PER_PAGE];
	पूर्णांक nr_bhs = MAX_BUF_PER_PAGE;
	sector_t blknr, last_blknr;
	पूर्णांक err, i, n;

	blknr = exfat_cluster_to_sector(sbi, clu);
	last_blknr = blknr + sbi->sect_per_clus;

	अगर (last_blknr > sbi->num_sectors && sbi->num_sectors > 0) अणु
		exfat_fs_error_ratelimit(sb,
			"%s: out of range(sect:%llu len:%u)",
			__func__, (अचिन्हित दीर्घ दीर्घ)blknr,
			sbi->sect_per_clus);
		वापस -EIO;
	पूर्ण

	/* Zeroing the unused blocks on this cluster */
	जबतक (blknr < last_blknr) अणु
		क्रम (n = 0; n < nr_bhs && blknr < last_blknr; n++, blknr++) अणु
			bhs[n] = sb_getblk(sb, blknr);
			अगर (!bhs[n]) अणु
				err = -ENOMEM;
				जाओ release_bhs;
			पूर्ण
			स_रखो(bhs[n]->b_data, 0, sb->s_blocksize);
		पूर्ण

		err = exfat_update_bhs(bhs, n, IS_सूचीSYNC(dir));
		अगर (err)
			जाओ release_bhs;

		क्रम (i = 0; i < n; i++)
			brअन्यथा(bhs[i]);
	पूर्ण
	वापस 0;

release_bhs:
	exfat_err(sb, "failed zeroed sect %llu\n", (अचिन्हित दीर्घ दीर्घ)blknr);
	क्रम (i = 0; i < n; i++)
		bक्रमget(bhs[i]);
	वापस err;
पूर्ण

पूर्णांक exfat_alloc_cluster(काष्ठा inode *inode, अचिन्हित पूर्णांक num_alloc,
		काष्ठा exfat_chain *p_chain, bool sync_bmap)
अणु
	पूर्णांक ret = -ENOSPC;
	अचिन्हित पूर्णांक num_clusters = 0, total_cnt;
	अचिन्हित पूर्णांक hपूर्णांक_clu, new_clu, last_clu = EXFAT_खातापूर्ण_CLUSTER;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	total_cnt = EXFAT_DATA_CLUSTER_COUNT(sbi);

	अगर (unlikely(total_cnt < sbi->used_clusters)) अणु
		exfat_fs_error_ratelimit(sb,
			"%s: invalid used clusters(t:%u,u:%u)\n",
			__func__, total_cnt, sbi->used_clusters);
		वापस -EIO;
	पूर्ण

	अगर (num_alloc > total_cnt - sbi->used_clusters)
		वापस -ENOSPC;

	mutex_lock(&sbi->biपंचांगap_lock);

	hपूर्णांक_clu = p_chain->dir;
	/* find new cluster */
	अगर (hपूर्णांक_clu == EXFAT_खातापूर्ण_CLUSTER) अणु
		अगर (sbi->clu_srch_ptr < EXFAT_FIRST_CLUSTER) अणु
			exfat_err(sb, "sbi->clu_srch_ptr is invalid (%u)\n",
				  sbi->clu_srch_ptr);
			sbi->clu_srch_ptr = EXFAT_FIRST_CLUSTER;
		पूर्ण

		hपूर्णांक_clu = exfat_find_मुक्त_biपंचांगap(sb, sbi->clu_srch_ptr);
		अगर (hपूर्णांक_clu == EXFAT_खातापूर्ण_CLUSTER) अणु
			ret = -ENOSPC;
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* check cluster validation */
	अगर (!is_valid_cluster(sbi, hपूर्णांक_clu)) अणु
		exfat_err(sb, "hint_cluster is invalid (%u)",
			hपूर्णांक_clu);
		hपूर्णांक_clu = EXFAT_FIRST_CLUSTER;
		अगर (p_chain->flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (exfat_chain_cont_cluster(sb, p_chain->dir,
					num_clusters)) अणु
				ret = -EIO;
				जाओ unlock;
			पूर्ण
			p_chain->flags = ALLOC_FAT_CHAIN;
		पूर्ण
	पूर्ण

	p_chain->dir = EXFAT_खातापूर्ण_CLUSTER;

	जबतक ((new_clu = exfat_find_मुक्त_biपंचांगap(sb, hपूर्णांक_clu)) !=
	       EXFAT_खातापूर्ण_CLUSTER) अणु
		अगर (new_clu != hपूर्णांक_clu &&
		    p_chain->flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (exfat_chain_cont_cluster(sb, p_chain->dir,
					num_clusters)) अणु
				ret = -EIO;
				जाओ मुक्त_cluster;
			पूर्ण
			p_chain->flags = ALLOC_FAT_CHAIN;
		पूर्ण

		/* update allocation biपंचांगap */
		अगर (exfat_set_biपंचांगap(inode, new_clu, sync_bmap)) अणु
			ret = -EIO;
			जाओ मुक्त_cluster;
		पूर्ण

		num_clusters++;

		/* update FAT table */
		अगर (p_chain->flags == ALLOC_FAT_CHAIN) अणु
			अगर (exfat_ent_set(sb, new_clu, EXFAT_खातापूर्ण_CLUSTER)) अणु
				ret = -EIO;
				जाओ मुक्त_cluster;
			पूर्ण
		पूर्ण

		अगर (p_chain->dir == EXFAT_खातापूर्ण_CLUSTER) अणु
			p_chain->dir = new_clu;
		पूर्ण अन्यथा अगर (p_chain->flags == ALLOC_FAT_CHAIN) अणु
			अगर (exfat_ent_set(sb, last_clu, new_clu)) अणु
				ret = -EIO;
				जाओ मुक्त_cluster;
			पूर्ण
		पूर्ण
		last_clu = new_clu;

		अगर (--num_alloc == 0) अणु
			sbi->clu_srch_ptr = hपूर्णांक_clu;
			sbi->used_clusters += num_clusters;

			p_chain->size += num_clusters;
			mutex_unlock(&sbi->biपंचांगap_lock);
			वापस 0;
		पूर्ण

		hपूर्णांक_clu = new_clu + 1;
		अगर (hपूर्णांक_clu >= sbi->num_clusters) अणु
			hपूर्णांक_clu = EXFAT_FIRST_CLUSTER;

			अगर (p_chain->flags == ALLOC_NO_FAT_CHAIN) अणु
				अगर (exfat_chain_cont_cluster(sb, p_chain->dir,
						num_clusters)) अणु
					ret = -EIO;
					जाओ मुक्त_cluster;
				पूर्ण
				p_chain->flags = ALLOC_FAT_CHAIN;
			पूर्ण
		पूर्ण
	पूर्ण
मुक्त_cluster:
	अगर (num_clusters)
		__exfat_मुक्त_cluster(inode, p_chain);
unlock:
	mutex_unlock(&sbi->biपंचांगap_lock);
	वापस ret;
पूर्ण

पूर्णांक exfat_count_num_clusters(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_chain, अचिन्हित पूर्णांक *ret_count)
अणु
	अचिन्हित पूर्णांक i, count;
	अचिन्हित पूर्णांक clu;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	अगर (!p_chain->dir || p_chain->dir == EXFAT_खातापूर्ण_CLUSTER) अणु
		*ret_count = 0;
		वापस 0;
	पूर्ण

	अगर (p_chain->flags == ALLOC_NO_FAT_CHAIN) अणु
		*ret_count = p_chain->size;
		वापस 0;
	पूर्ण

	clu = p_chain->dir;
	count = 0;
	क्रम (i = EXFAT_FIRST_CLUSTER; i < sbi->num_clusters; i++) अणु
		count++;
		अगर (exfat_ent_get(sb, clu, &clu))
			वापस -EIO;
		अगर (clu == EXFAT_खातापूर्ण_CLUSTER)
			अवरोध;
	पूर्ण

	*ret_count = count;
	वापस 0;
पूर्ण
