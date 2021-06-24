<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/affs/biपंचांगap.c
 *
 *  (c) 1996 Hans-Joachim Widmaier
 *
 *  biपंचांगap.c contains the code that handles all biपंचांगap related stuff -
 *  block allocation, deallocation, calculation of मुक्त space.
 */

#समावेश <linux/slab.h>
#समावेश "affs.h"

u32
affs_count_मुक्त_blocks(काष्ठा super_block *sb)
अणु
	काष्ठा affs_bm_info *bm;
	u32 मुक्त;
	पूर्णांक i;

	pr_debug("%s()\n", __func__);

	अगर (sb_rकरोnly(sb))
		वापस 0;

	mutex_lock(&AFFS_SB(sb)->s_bmlock);

	bm = AFFS_SB(sb)->s_biपंचांगap;
	मुक्त = 0;
	क्रम (i = AFFS_SB(sb)->s_bmap_count; i > 0; bm++, i--)
		मुक्त += bm->bm_मुक्त;

	mutex_unlock(&AFFS_SB(sb)->s_bmlock);

	वापस मुक्त;
पूर्ण

व्योम
affs_मुक्त_block(काष्ठा super_block *sb, u32 block)
अणु
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);
	काष्ठा affs_bm_info *bm;
	काष्ठा buffer_head *bh;
	u32 blk, bmap, bit, mask, पंचांगp;
	__be32 *data;

	pr_debug("%s(%u)\n", __func__, block);

	अगर (block > sbi->s_partition_size)
		जाओ err_range;

	blk     = block - sbi->s_reserved;
	bmap    = blk / sbi->s_bmap_bits;
	bit     = blk % sbi->s_bmap_bits;
	bm      = &sbi->s_biपंचांगap[bmap];

	mutex_lock(&sbi->s_bmlock);

	bh = sbi->s_bmap_bh;
	अगर (sbi->s_last_bmap != bmap) अणु
		affs_brअन्यथा(bh);
		bh = affs_bपढ़ो(sb, bm->bm_key);
		अगर (!bh)
			जाओ err_bh_पढ़ो;
		sbi->s_bmap_bh = bh;
		sbi->s_last_bmap = bmap;
	पूर्ण

	mask = 1 << (bit & 31);
	data = (__be32 *)bh->b_data + bit / 32 + 1;

	/* mark block मुक्त */
	पंचांगp = be32_to_cpu(*data);
	अगर (पंचांगp & mask)
		जाओ err_मुक्त;
	*data = cpu_to_be32(पंचांगp | mask);

	/* fix checksum */
	पंचांगp = be32_to_cpu(*(__be32 *)bh->b_data);
	*(__be32 *)bh->b_data = cpu_to_be32(पंचांगp - mask);

	mark_buffer_dirty(bh);
	affs_mark_sb_dirty(sb);
	bm->bm_मुक्त++;

	mutex_unlock(&sbi->s_bmlock);
	वापस;

err_मुक्त:
	affs_warning(sb,"affs_free_block","Trying to free block %u which is already free", block);
	mutex_unlock(&sbi->s_bmlock);
	वापस;

err_bh_पढ़ो:
	affs_error(sb,"affs_free_block","Cannot read bitmap block %u", bm->bm_key);
	sbi->s_bmap_bh = शून्य;
	sbi->s_last_bmap = ~0;
	mutex_unlock(&sbi->s_bmlock);
	वापस;

err_range:
	affs_error(sb, "affs_free_block","Block %u outside partition", block);
पूर्ण

/*
 * Allocate a block in the given allocation zone.
 * Since we have to byte-swap the biपंचांगap on little-endian
 * machines, this is rather expensive. Thereक्रमe we will
 * pपुनः_स्मृतिate up to 16 blocks from the same word, अगर
 * possible. We are not करोing pपुनः_स्मृतिations in the
 * header zone, though.
 */

u32
affs_alloc_block(काष्ठा inode *inode, u32 goal)
अणु
	काष्ठा super_block *sb;
	काष्ठा affs_sb_info *sbi;
	काष्ठा affs_bm_info *bm;
	काष्ठा buffer_head *bh;
	__be32 *data, *enddata;
	u32 blk, bmap, bit, mask, mask2, पंचांगp;
	पूर्णांक i;

	sb = inode->i_sb;
	sbi = AFFS_SB(sb);

	pr_debug("balloc(inode=%lu,goal=%u): ", inode->i_ino, goal);

	अगर (AFFS_I(inode)->i_pa_cnt) अणु
		pr_debug("%d\n", AFFS_I(inode)->i_lastalloc+1);
		AFFS_I(inode)->i_pa_cnt--;
		वापस ++AFFS_I(inode)->i_lastalloc;
	पूर्ण

	अगर (!goal || goal > sbi->s_partition_size) अणु
		अगर (goal)
			affs_warning(sb, "affs_balloc", "invalid goal %d", goal);
		//अगर (!AFFS_I(inode)->i_last_block)
		//	affs_warning(sb, "affs_balloc", "no last alloc block");
		goal = sbi->s_reserved;
	पूर्ण

	blk = goal - sbi->s_reserved;
	bmap = blk / sbi->s_bmap_bits;
	bm = &sbi->s_biपंचांगap[bmap];

	mutex_lock(&sbi->s_bmlock);

	अगर (bm->bm_मुक्त)
		जाओ find_bmap_bit;

find_bmap:
	/* search क्रम the next bmap buffer with मुक्त bits */
	i = sbi->s_bmap_count;
	करो अणु
		अगर (--i < 0)
			जाओ err_full;
		bmap++;
		bm++;
		अगर (bmap < sbi->s_bmap_count)
			जारी;
		/* restart search at zero */
		bmap = 0;
		bm = sbi->s_biपंचांगap;
	पूर्ण जबतक (!bm->bm_मुक्त);
	blk = bmap * sbi->s_bmap_bits;

find_bmap_bit:

	bh = sbi->s_bmap_bh;
	अगर (sbi->s_last_bmap != bmap) अणु
		affs_brअन्यथा(bh);
		bh = affs_bपढ़ो(sb, bm->bm_key);
		अगर (!bh)
			जाओ err_bh_पढ़ो;
		sbi->s_bmap_bh = bh;
		sbi->s_last_bmap = bmap;
	पूर्ण

	/* find an unused block in this biपंचांगap block */
	bit = blk % sbi->s_bmap_bits;
	data = (__be32 *)bh->b_data + bit / 32 + 1;
	enddata = (__be32 *)((u8 *)bh->b_data + sb->s_blocksize);
	mask = ~0UL << (bit & 31);
	blk &= ~31UL;

	पंचांगp = be32_to_cpu(*data);
	अगर (पंचांगp & mask)
		जाओ find_bit;

	/* scan the rest of the buffer */
	करो अणु
		blk += 32;
		अगर (++data >= enddata)
			/* didn't find something, can only happen
			 * अगर scan didn't start at 0, try next bmap
			 */
			जाओ find_bmap;
	पूर्ण जबतक (!*data);
	पंचांगp = be32_to_cpu(*data);
	mask = ~0;

find_bit:
	/* finally look क्रम a मुक्त bit in the word */
	bit = ffs(पंचांगp & mask) - 1;
	blk += bit + sbi->s_reserved;
	mask2 = mask = 1 << (bit & 31);
	AFFS_I(inode)->i_lastalloc = blk;

	/* pपुनः_स्मृति as much as possible within this word */
	जबतक ((mask2 <<= 1)) अणु
		अगर (!(पंचांगp & mask2))
			अवरोध;
		AFFS_I(inode)->i_pa_cnt++;
		mask |= mask2;
	पूर्ण
	bm->bm_मुक्त -= AFFS_I(inode)->i_pa_cnt + 1;

	*data = cpu_to_be32(पंचांगp & ~mask);

	/* fix checksum */
	पंचांगp = be32_to_cpu(*(__be32 *)bh->b_data);
	*(__be32 *)bh->b_data = cpu_to_be32(पंचांगp + mask);

	mark_buffer_dirty(bh);
	affs_mark_sb_dirty(sb);

	mutex_unlock(&sbi->s_bmlock);

	pr_debug("%d\n", blk);
	वापस blk;

err_bh_पढ़ो:
	affs_error(sb,"affs_read_block","Cannot read bitmap block %u", bm->bm_key);
	sbi->s_bmap_bh = शून्य;
	sbi->s_last_bmap = ~0;
err_full:
	mutex_unlock(&sbi->s_bmlock);
	pr_debug("failed\n");
	वापस 0;
पूर्ण

पूर्णांक affs_init_biपंचांगap(काष्ठा super_block *sb, पूर्णांक *flags)
अणु
	काष्ठा affs_bm_info *bm;
	काष्ठा buffer_head *bmap_bh = शून्य, *bh = शून्य;
	__be32 *bmap_blk;
	u32 size, blk, end, offset, mask;
	पूर्णांक i, res = 0;
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);

	अगर (*flags & SB_RDONLY)
		वापस 0;

	अगर (!AFFS_ROOT_TAIL(sb, sbi->s_root_bh)->bm_flag) अणु
		pr_notice("Bitmap invalid - mounting %s read only\n", sb->s_id);
		*flags |= SB_RDONLY;
		वापस 0;
	पूर्ण

	sbi->s_last_bmap = ~0;
	sbi->s_bmap_bh = शून्य;
	sbi->s_bmap_bits = sb->s_blocksize * 8 - 32;
	sbi->s_bmap_count = (sbi->s_partition_size - sbi->s_reserved +
				 sbi->s_bmap_bits - 1) / sbi->s_bmap_bits;
	size = sbi->s_bmap_count * माप(*bm);
	bm = sbi->s_biपंचांगap = kzalloc(size, GFP_KERNEL);
	अगर (!sbi->s_biपंचांगap) अणु
		pr_err("Bitmap allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	bmap_blk = (__be32 *)sbi->s_root_bh->b_data;
	blk = sb->s_blocksize / 4 - 49;
	end = blk + 25;

	क्रम (i = sbi->s_bmap_count; i > 0; bm++, i--) अणु
		affs_brअन्यथा(bh);

		bm->bm_key = be32_to_cpu(bmap_blk[blk]);
		bh = affs_bपढ़ो(sb, bm->bm_key);
		अगर (!bh) अणु
			pr_err("Cannot read bitmap\n");
			res = -EIO;
			जाओ out;
		पूर्ण
		अगर (affs_checksum_block(sb, bh)) अणु
			pr_warn("Bitmap %u invalid - mounting %s read only.\n",
				bm->bm_key, sb->s_id);
			*flags |= SB_RDONLY;
			जाओ out;
		पूर्ण
		pr_debug("read bitmap block %d: %d\n", blk, bm->bm_key);
		bm->bm_मुक्त = memweight(bh->b_data + 4, sb->s_blocksize - 4);

		/* Don't try पढ़ो the extension अगर this is the last block,
		 * but we also need the right bm poपूर्णांकer below
		 */
		अगर (++blk < end || i == 1)
			जारी;
		अगर (bmap_bh)
			affs_brअन्यथा(bmap_bh);
		bmap_bh = affs_bपढ़ो(sb, be32_to_cpu(bmap_blk[blk]));
		अगर (!bmap_bh) अणु
			pr_err("Cannot read bitmap extension\n");
			res = -EIO;
			जाओ out;
		पूर्ण
		bmap_blk = (__be32 *)bmap_bh->b_data;
		blk = 0;
		end = sb->s_blocksize / 4 - 1;
	पूर्ण

	offset = (sbi->s_partition_size - sbi->s_reserved) % sbi->s_bmap_bits;
	mask = ~(0xFFFFFFFFU << (offset & 31));
	pr_debug("last word: %d %d %d\n", offset, offset / 32 + 1, mask);
	offset = offset / 32 + 1;

	अगर (mask) अणु
		u32 old, new;

		/* Mark unused bits in the last word as allocated */
		old = be32_to_cpu(((__be32 *)bh->b_data)[offset]);
		new = old & mask;
		//अगर (old != new) अणु
			((__be32 *)bh->b_data)[offset] = cpu_to_be32(new);
			/* fix checksum */
			//new -= old;
			//old = be32_to_cpu(*(__be32 *)bh->b_data);
			//*(__be32 *)bh->b_data = cpu_to_be32(old - new);
			//mark_buffer_dirty(bh);
		//पूर्ण
		/* correct offset क्रम the biपंचांगap count below */
		//offset++;
	पूर्ण
	जबतक (++offset < sb->s_blocksize / 4)
		((__be32 *)bh->b_data)[offset] = 0;
	((__be32 *)bh->b_data)[0] = 0;
	((__be32 *)bh->b_data)[0] = cpu_to_be32(-affs_checksum_block(sb, bh));
	mark_buffer_dirty(bh);

	/* recalculate biपंचांगap count क्रम last block */
	bm--;
	bm->bm_मुक्त = memweight(bh->b_data + 4, sb->s_blocksize - 4);

out:
	affs_brअन्यथा(bh);
	affs_brअन्यथा(bmap_bh);
	वापस res;
पूर्ण

व्योम affs_मुक्त_biपंचांगap(काष्ठा super_block *sb)
अणु
	काष्ठा affs_sb_info *sbi = AFFS_SB(sb);

	अगर (!sbi->s_biपंचांगap)
		वापस;

	affs_brअन्यथा(sbi->s_bmap_bh);
	sbi->s_bmap_bh = शून्य;
	sbi->s_last_bmap = ~0;
	kमुक्त(sbi->s_biपंचांगap);
	sbi->s_biपंचांगap = शून्य;
पूर्ण
