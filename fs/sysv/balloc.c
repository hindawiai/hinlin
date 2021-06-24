<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/sysv/balloc.c
 *
 *  minix/biपंचांगap.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext/मुक्तlists.c
 *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)
 *
 *  xenix/alloc.c
 *  Copyright (C) 1992  Doug Evans
 *
 *  coh/alloc.c
 *  Copyright (C) 1993  Pascal Haible, Bruno Haible
 *
 *  sysv/balloc.c
 *  Copyright (C) 1993  Bruno Haible
 *
 *  This file contains code क्रम allocating/मुक्तing blocks.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/माला.स>
#समावेश "sysv.h"

/* We करोn't trust the value of
   sb->sv_sbd2->s_tमुक्त = *sb->sv_मुक्त_blocks
   but we nevertheless keep it up to date. */

अटल अंतरभूत sysv_zone_t *get_chunk(काष्ठा super_block *sb, काष्ठा buffer_head *bh)
अणु
	अक्षर *bh_data = bh->b_data;

	अगर (SYSV_SB(sb)->s_type == FSTYPE_SYSV4)
		वापस (sysv_zone_t*)(bh_data+4);
	अन्यथा
		वापस (sysv_zone_t*)(bh_data+2);
पूर्ण

/* NOTE NOTE NOTE: nr is a block number _as_ _stored_ _on_ _disk_ */

व्योम sysv_मुक्त_block(काष्ठा super_block * sb, sysv_zone_t nr)
अणु
	काष्ठा sysv_sb_info * sbi = SYSV_SB(sb);
	काष्ठा buffer_head * bh;
	sysv_zone_t *blocks = sbi->s_bcache;
	अचिन्हित count;
	अचिन्हित block = fs32_to_cpu(sbi, nr);

	/*
	 * This code करोes not work at all क्रम AFS (it has a biपंचांगap
	 * मुक्त list).  As AFS is supposed to be पढ़ो-only no one
	 * should call this क्रम an AFS fileप्रणाली anyway...
	 */
	अगर (sbi->s_type == FSTYPE_AFS)
		वापस;

	अगर (block < sbi->s_firstdatazone || block >= sbi->s_nzones) अणु
		prपूर्णांकk("sysv_free_block: trying to free block not in datazone\n");
		वापस;
	पूर्ण

	mutex_lock(&sbi->s_lock);
	count = fs16_to_cpu(sbi, *sbi->s_bcache_count);

	अगर (count > sbi->s_flc_size) अणु
		prपूर्णांकk("sysv_free_block: flc_count > flc_size\n");
		mutex_unlock(&sbi->s_lock);
		वापस;
	पूर्ण
	/* If the मुक्त list head in super-block is full, it is copied
	 * पूर्णांकo this block being मुक्तd, ditto अगर it's completely empty
	 * (applies only on Coherent).
	 */
	अगर (count == sbi->s_flc_size || count == 0) अणु
		block += sbi->s_block_base;
		bh = sb_getblk(sb, block);
		अगर (!bh) अणु
			prपूर्णांकk("sysv_free_block: getblk() failed\n");
			mutex_unlock(&sbi->s_lock);
			वापस;
		पूर्ण
		स_रखो(bh->b_data, 0, sb->s_blocksize);
		*(__fs16*)bh->b_data = cpu_to_fs16(sbi, count);
		स_नकल(get_chunk(sb,bh), blocks, count * माप(sysv_zone_t));
		mark_buffer_dirty(bh);
		set_buffer_uptodate(bh);
		brअन्यथा(bh);
		count = 0;
	पूर्ण
	sbi->s_bcache[count++] = nr;

	*sbi->s_bcache_count = cpu_to_fs16(sbi, count);
	fs32_add(sbi, sbi->s_मुक्त_blocks, 1);
	dirty_sb(sb);
	mutex_unlock(&sbi->s_lock);
पूर्ण

sysv_zone_t sysv_new_block(काष्ठा super_block * sb)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	अचिन्हित पूर्णांक block;
	sysv_zone_t nr;
	काष्ठा buffer_head * bh;
	अचिन्हित count;

	mutex_lock(&sbi->s_lock);
	count = fs16_to_cpu(sbi, *sbi->s_bcache_count);

	अगर (count == 0) /* Applies only to Coherent FS */
		जाओ Enospc;
	nr = sbi->s_bcache[--count];
	अगर (nr == 0)  /* Applies only to Xenix FS, SystemV FS */
		जाओ Enospc;

	block = fs32_to_cpu(sbi, nr);

	*sbi->s_bcache_count = cpu_to_fs16(sbi, count);

	अगर (block < sbi->s_firstdatazone || block >= sbi->s_nzones) अणु
		prपूर्णांकk("sysv_new_block: new block %d is not in data zone\n",
			block);
		जाओ Enospc;
	पूर्ण

	अगर (count == 0) अणु /* the last block जारीs the मुक्त list */
		अचिन्हित count;

		block += sbi->s_block_base;
		अगर (!(bh = sb_bपढ़ो(sb, block))) अणु
			prपूर्णांकk("sysv_new_block: cannot read free-list block\n");
			/* retry this same block next समय */
			*sbi->s_bcache_count = cpu_to_fs16(sbi, 1);
			जाओ Enospc;
		पूर्ण
		count = fs16_to_cpu(sbi, *(__fs16*)bh->b_data);
		अगर (count > sbi->s_flc_size) अणु
			prपूर्णांकk("sysv_new_block: free-list block with >flc_size entries\n");
			brअन्यथा(bh);
			जाओ Enospc;
		पूर्ण
		*sbi->s_bcache_count = cpu_to_fs16(sbi, count);
		स_नकल(sbi->s_bcache, get_chunk(sb, bh),
				count * माप(sysv_zone_t));
		brअन्यथा(bh);
	पूर्ण
	/* Now the मुक्त list head in the superblock is valid again. */
	fs32_add(sbi, sbi->s_मुक्त_blocks, -1);
	dirty_sb(sb);
	mutex_unlock(&sbi->s_lock);
	वापस nr;

Enospc:
	mutex_unlock(&sbi->s_lock);
	वापस 0;
पूर्ण

अचिन्हित दीर्घ sysv_count_मुक्त_blocks(काष्ठा super_block * sb)
अणु
	काष्ठा sysv_sb_info * sbi = SYSV_SB(sb);
	पूर्णांक sb_count;
	पूर्णांक count;
	काष्ठा buffer_head * bh = शून्य;
	sysv_zone_t *blocks;
	अचिन्हित block;
	पूर्णांक n;

	/*
	 * This code करोes not work at all क्रम AFS (it has a biपंचांगap
	 * मुक्त list).  As AFS is supposed to be पढ़ो-only we just
	 * lie and say it has no मुक्त block at all.
	 */
	अगर (sbi->s_type == FSTYPE_AFS)
		वापस 0;

	mutex_lock(&sbi->s_lock);
	sb_count = fs32_to_cpu(sbi, *sbi->s_मुक्त_blocks);

	अगर (0)
		जाओ trust_sb;

	/* this causes a lot of disk traffic ... */
	count = 0;
	n = fs16_to_cpu(sbi, *sbi->s_bcache_count);
	blocks = sbi->s_bcache;
	जबतक (1) अणु
		sysv_zone_t zone;
		अगर (n > sbi->s_flc_size)
			जाओ E2big;
		zone = 0;
		जबतक (n && (zone = blocks[--n]) != 0)
			count++;
		अगर (zone == 0)
			अवरोध;

		block = fs32_to_cpu(sbi, zone);
		अगर (bh)
			brअन्यथा(bh);

		अगर (block < sbi->s_firstdatazone || block >= sbi->s_nzones)
			जाओ Einval;
		block += sbi->s_block_base;
		bh = sb_bपढ़ो(sb, block);
		अगर (!bh)
			जाओ Eio;
		n = fs16_to_cpu(sbi, *(__fs16*)bh->b_data);
		blocks = get_chunk(sb, bh);
	पूर्ण
	अगर (bh)
		brअन्यथा(bh);
	अगर (count != sb_count)
		जाओ Ecount;
करोne:
	mutex_unlock(&sbi->s_lock);
	वापस count;

Einval:
	prपूर्णांकk("sysv_count_free_blocks: new block %d is not in data zone\n",
		block);
	जाओ trust_sb;
Eio:
	prपूर्णांकk("sysv_count_free_blocks: cannot read free-list block\n");
	जाओ trust_sb;
E2big:
	prपूर्णांकk("sysv_count_free_blocks: >flc_size entries in free-list block\n");
	अगर (bh)
		brअन्यथा(bh);
trust_sb:
	count = sb_count;
	जाओ करोne;
Ecount:
	prपूर्णांकk("sysv_count_free_blocks: free block count was %d, "
		"correcting to %d\n", sb_count, count);
	अगर (!sb_rकरोnly(sb)) अणु
		*sbi->s_मुक्त_blocks = cpu_to_fs32(sbi, count);
		dirty_sb(sb);
	पूर्ण
	जाओ करोne;
पूर्ण
