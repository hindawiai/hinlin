<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/buffer_head.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

अटल स्थिर अचिन्हित अक्षर मुक्त_bit[] = अणु
	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2,/*  0 ~  19*/
	0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 0, 1, 0, 2, 0, 1, 0, 3,/* 20 ~  39*/
	0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2,/* 40 ~  59*/
	0, 1, 0, 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4,/* 60 ~  79*/
	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 0, 1, 0, 2,/* 80 ~  99*/
	0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3,/*100 ~ 119*/
	0, 1, 0, 2, 0, 1, 0, 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2,/*120 ~ 139*/
	0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5,/*140 ~ 159*/
	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2,/*160 ~ 179*/
	0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 6, 0, 1, 0, 2, 0, 1, 0, 3,/*180 ~ 199*/
	0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2,/*200 ~ 219*/
	0, 1, 0, 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4,/*220 ~ 239*/
	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0                /*240 ~ 254*/
पूर्ण;

अटल स्थिर अचिन्हित अक्षर used_bit[] = अणु
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3,/*  0 ~  19*/
	2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4,/* 20 ~  39*/
	2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,/* 40 ~  59*/
	4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,/* 60 ~  79*/
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,/* 80 ~  99*/
	3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,/*100 ~ 119*/
	4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4,/*120 ~ 139*/
	3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,/*140 ~ 159*/
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5,/*160 ~ 179*/
	4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,/*180 ~ 199*/
	3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6,/*200 ~ 219*/
	5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,/*220 ~ 239*/
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8             /*240 ~ 255*/
पूर्ण;

/*
 *  Allocation Biपंचांगap Management Functions
 */
अटल पूर्णांक exfat_allocate_biपंचांगap(काष्ठा super_block *sb,
		काष्ठा exfat_dentry *ep)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	दीर्घ दीर्घ map_size;
	अचिन्हित पूर्णांक i, need_map_size;
	sector_t sector;

	sbi->map_clu = le32_to_cpu(ep->dentry.biपंचांगap.start_clu);
	map_size = le64_to_cpu(ep->dentry.biपंचांगap.size);
	need_map_size = ((EXFAT_DATA_CLUSTER_COUNT(sbi) - 1) / BITS_PER_BYTE)
		+ 1;
	अगर (need_map_size != map_size) अणु
		exfat_err(sb, "bogus allocation bitmap size(need : %u, cur : %lld)",
			  need_map_size, map_size);
		/*
		 * Only allowed when bogus allocation
		 * biपंचांगap size is large
		 */
		अगर (need_map_size > map_size)
			वापस -EIO;
	पूर्ण
	sbi->map_sectors = ((need_map_size - 1) >>
			(sb->s_blocksize_bits)) + 1;
	sbi->vol_amap = kदो_स्मृति_array(sbi->map_sectors,
				माप(काष्ठा buffer_head *), GFP_KERNEL);
	अगर (!sbi->vol_amap)
		वापस -ENOMEM;

	sector = exfat_cluster_to_sector(sbi, sbi->map_clu);
	क्रम (i = 0; i < sbi->map_sectors; i++) अणु
		sbi->vol_amap[i] = sb_bपढ़ो(sb, sector + i);
		अगर (!sbi->vol_amap[i]) अणु
			/* release all buffers and मुक्त vol_amap */
			पूर्णांक j = 0;

			जबतक (j < i)
				brअन्यथा(sbi->vol_amap[j++]);

			kमुक्त(sbi->vol_amap);
			sbi->vol_amap = शून्य;
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक exfat_load_biपंचांगap(काष्ठा super_block *sb)
अणु
	अचिन्हित पूर्णांक i, type;
	काष्ठा exfat_chain clu;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	exfat_chain_set(&clu, sbi->root_dir, 0, ALLOC_FAT_CHAIN);
	जबतक (clu.dir != EXFAT_खातापूर्ण_CLUSTER) अणु
		क्रम (i = 0; i < sbi->dentries_per_clu; i++) अणु
			काष्ठा exfat_dentry *ep;
			काष्ठा buffer_head *bh;

			ep = exfat_get_dentry(sb, &clu, i, &bh, शून्य);
			अगर (!ep)
				वापस -EIO;

			type = exfat_get_entry_type(ep);
			अगर (type == TYPE_UNUSED)
				अवरोध;
			अगर (type != TYPE_BITMAP)
				जारी;
			अगर (ep->dentry.biपंचांगap.flags == 0x0) अणु
				पूर्णांक err;

				err = exfat_allocate_biपंचांगap(sb, ep);
				brअन्यथा(bh);
				वापस err;
			पूर्ण
			brअन्यथा(bh);
		पूर्ण

		अगर (exfat_get_next_cluster(sb, &clu.dir))
			वापस -EIO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम exfat_मुक्त_biपंचांगap(काष्ठा exfat_sb_info *sbi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sbi->map_sectors; i++)
		__brअन्यथा(sbi->vol_amap[i]);

	kमुक्त(sbi->vol_amap);
पूर्ण

पूर्णांक exfat_set_biपंचांगap(काष्ठा inode *inode, अचिन्हित पूर्णांक clu, bool sync)
अणु
	पूर्णांक i, b;
	अचिन्हित पूर्णांक ent_idx;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	WARN_ON(clu < EXFAT_FIRST_CLUSTER);
	ent_idx = CLUSTER_TO_BITMAP_ENT(clu);
	i = BITMAP_OFFSET_SECTOR_INDEX(sb, ent_idx);
	b = BITMAP_OFFSET_BIT_IN_SECTOR(sb, ent_idx);

	set_bit_le(b, sbi->vol_amap[i]->b_data);
	exfat_update_bh(sbi->vol_amap[i], sync);
	वापस 0;
पूर्ण

व्योम exfat_clear_biपंचांगap(काष्ठा inode *inode, अचिन्हित पूर्णांक clu, bool sync)
अणु
	पूर्णांक i, b;
	अचिन्हित पूर्णांक ent_idx;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_mount_options *opts = &sbi->options;

	WARN_ON(clu < EXFAT_FIRST_CLUSTER);
	ent_idx = CLUSTER_TO_BITMAP_ENT(clu);
	i = BITMAP_OFFSET_SECTOR_INDEX(sb, ent_idx);
	b = BITMAP_OFFSET_BIT_IN_SECTOR(sb, ent_idx);

	clear_bit_le(b, sbi->vol_amap[i]->b_data);
	exfat_update_bh(sbi->vol_amap[i], sync);

	अगर (opts->discard) अणु
		पूर्णांक ret_discard;

		ret_discard = sb_issue_discard(sb,
			exfat_cluster_to_sector(sbi, clu),
			(1 << sbi->sect_per_clus_bits), GFP_NOFS, 0);

		अगर (ret_discard == -EOPNOTSUPP) अणु
			exfat_err(sb, "discard not supported by device, disabling");
			opts->discard = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * If the value of "clu" is 0, it means cluster 2 which is the first cluster of
 * the cluster heap.
 */
अचिन्हित पूर्णांक exfat_find_मुक्त_biपंचांगap(काष्ठा super_block *sb, अचिन्हित पूर्णांक clu)
अणु
	अचिन्हित पूर्णांक i, map_i, map_b, ent_idx;
	अचिन्हित पूर्णांक clu_base, clu_मुक्त;
	अचिन्हित अक्षर k, clu_mask;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	WARN_ON(clu < EXFAT_FIRST_CLUSTER);
	ent_idx = CLUSTER_TO_BITMAP_ENT(clu);
	clu_base = BITMAP_ENT_TO_CLUSTER(ent_idx & ~(BITS_PER_BYTE_MASK));
	clu_mask = IGNORED_BITS_REMAINED(clu, clu_base);

	map_i = BITMAP_OFFSET_SECTOR_INDEX(sb, ent_idx);
	map_b = BITMAP_OFFSET_BYTE_IN_SECTOR(sb, ent_idx);

	क्रम (i = EXFAT_FIRST_CLUSTER; i < sbi->num_clusters;
	     i += BITS_PER_BYTE) अणु
		k = *(sbi->vol_amap[map_i]->b_data + map_b);
		अगर (clu_mask > 0) अणु
			k |= clu_mask;
			clu_mask = 0;
		पूर्ण
		अगर (k < 0xFF) अणु
			clu_मुक्त = clu_base + मुक्त_bit[k];
			अगर (clu_मुक्त < sbi->num_clusters)
				वापस clu_मुक्त;
		पूर्ण
		clu_base += BITS_PER_BYTE;

		अगर (++map_b >= sb->s_blocksize ||
		    clu_base >= sbi->num_clusters) अणु
			अगर (++map_i >= sbi->map_sectors) अणु
				clu_base = EXFAT_FIRST_CLUSTER;
				map_i = 0;
			पूर्ण
			map_b = 0;
		पूर्ण
	पूर्ण

	वापस EXFAT_खातापूर्ण_CLUSTER;
पूर्ण

पूर्णांक exfat_count_used_clusters(काष्ठा super_block *sb, अचिन्हित पूर्णांक *ret_count)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक i, map_i = 0, map_b = 0;
	अचिन्हित पूर्णांक total_clus = EXFAT_DATA_CLUSTER_COUNT(sbi);
	अचिन्हित पूर्णांक last_mask = total_clus & BITS_PER_BYTE_MASK;
	अचिन्हित अक्षर clu_bits;
	स्थिर अचिन्हित अक्षर last_bit_mask[] = अणु0, 0b00000001, 0b00000011,
		0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111पूर्ण;

	total_clus &= ~last_mask;
	क्रम (i = 0; i < total_clus; i += BITS_PER_BYTE) अणु
		clu_bits = *(sbi->vol_amap[map_i]->b_data + map_b);
		count += used_bit[clu_bits];
		अगर (++map_b >= (अचिन्हित पूर्णांक)sb->s_blocksize) अणु
			map_i++;
			map_b = 0;
		पूर्ण
	पूर्ण

	अगर (last_mask) अणु
		clu_bits = *(sbi->vol_amap[map_i]->b_data + map_b);
		clu_bits &= last_bit_mask[last_mask];
		count += used_bit[clu_bits];
	पूर्ण

	*ret_count = count;
	वापस 0;
पूर्ण

पूर्णांक exfat_trim_fs(काष्ठा inode *inode, काष्ठा fstrim_range *range)
अणु
	अचिन्हित पूर्णांक trim_begin, trim_end, count, next_मुक्त_clu;
	u64 clu_start, clu_end, trim_minlen, trimmed_total = 0;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	पूर्णांक err = 0;

	clu_start = max_t(u64, range->start >> sbi->cluster_size_bits,
				EXFAT_FIRST_CLUSTER);
	clu_end = clu_start + (range->len >> sbi->cluster_size_bits) - 1;
	trim_minlen = range->minlen >> sbi->cluster_size_bits;

	अगर (clu_start >= sbi->num_clusters || range->len < sbi->cluster_size)
		वापस -EINVAL;

	अगर (clu_end >= sbi->num_clusters)
		clu_end = sbi->num_clusters - 1;

	mutex_lock(&sbi->biपंचांगap_lock);

	trim_begin = trim_end = exfat_find_मुक्त_biपंचांगap(sb, clu_start);
	अगर (trim_begin == EXFAT_खातापूर्ण_CLUSTER)
		जाओ unlock;

	next_मुक्त_clu = exfat_find_मुक्त_biपंचांगap(sb, trim_end + 1);
	अगर (next_मुक्त_clu == EXFAT_खातापूर्ण_CLUSTER)
		जाओ unlock;

	करो अणु
		अगर (next_मुक्त_clu == trim_end + 1) अणु
			/* extend trim range क्रम continuous मुक्त cluster */
			trim_end++;
		पूर्ण अन्यथा अणु
			/* trim current range अगर it's larger than trim_minlen */
			count = trim_end - trim_begin + 1;
			अगर (count >= trim_minlen) अणु
				err = sb_issue_discard(sb,
					exfat_cluster_to_sector(sbi, trim_begin),
					count * sbi->sect_per_clus, GFP_NOFS, 0);
				अगर (err)
					जाओ unlock;

				trimmed_total += count;
			पूर्ण

			/* set next start poपूर्णांक of the मुक्त hole */
			trim_begin = trim_end = next_मुक्त_clu;
		पूर्ण

		अगर (next_मुक्त_clu >= clu_end)
			अवरोध;

		अगर (fatal_संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ unlock;
		पूर्ण

		next_मुक्त_clu = exfat_find_मुक्त_biपंचांगap(sb, next_मुक्त_clu + 1);
	पूर्ण जबतक (next_मुक्त_clu != EXFAT_खातापूर्ण_CLUSTER &&
			next_मुक्त_clu > trim_end);

	/* try to trim reमुख्यder */
	count = trim_end - trim_begin + 1;
	अगर (count >= trim_minlen) अणु
		err = sb_issue_discard(sb, exfat_cluster_to_sector(sbi, trim_begin),
			count * sbi->sect_per_clus, GFP_NOFS, 0);
		अगर (err)
			जाओ unlock;

		trimmed_total += count;
	पूर्ण

unlock:
	mutex_unlock(&sbi->biपंचांगap_lock);
	range->len = trimmed_total << sbi->cluster_size_bits;

	वापस err;
पूर्ण
