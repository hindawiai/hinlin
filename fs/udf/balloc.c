<शैली गुरु>
/*
 * balloc.c
 *
 * PURPOSE
 *	Block allocation handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 *
 *  (C) 1999-2001 Ben Fennema
 *  (C) 1999 Stelias Computing Inc
 *
 * HISTORY
 *
 *  02/24/99 blf  Created.
 *
 */

#समावेश "udfdecl.h"

#समावेश <linux/bitops.h>

#समावेश "udf_i.h"
#समावेश "udf_sb.h"

#घोषणा udf_clear_bit	__test_and_clear_bit_le
#घोषणा udf_set_bit	__test_and_set_bit_le
#घोषणा udf_test_bit	test_bit_le
#घोषणा udf_find_next_one_bit	find_next_bit_le

अटल पूर्णांक पढ़ो_block_biपंचांगap(काष्ठा super_block *sb,
			     काष्ठा udf_biपंचांगap *biपंचांगap, अचिन्हित पूर्णांक block,
			     अचिन्हित दीर्घ biपंचांगap_nr)
अणु
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक retval = 0;
	काष्ठा kernel_lb_addr loc;

	loc.logicalBlockNum = biपंचांगap->s_extPosition;
	loc.partitionReferenceNum = UDF_SB(sb)->s_partition;

	bh = udf_tपढ़ो(sb, udf_get_lb_pblock(sb, &loc, block));
	अगर (!bh)
		retval = -EIO;

	biपंचांगap->s_block_biपंचांगap[biपंचांगap_nr] = bh;
	वापस retval;
पूर्ण

अटल पूर्णांक __load_block_biपंचांगap(काष्ठा super_block *sb,
			       काष्ठा udf_biपंचांगap *biपंचांगap,
			       अचिन्हित पूर्णांक block_group)
अणु
	पूर्णांक retval = 0;
	पूर्णांक nr_groups = biपंचांगap->s_nr_groups;

	अगर (block_group >= nr_groups) अणु
		udf_debug("block_group (%u) > nr_groups (%d)\n",
			  block_group, nr_groups);
	पूर्ण

	अगर (biपंचांगap->s_block_biपंचांगap[block_group])
		वापस block_group;

	retval = पढ़ो_block_biपंचांगap(sb, biपंचांगap, block_group, block_group);
	अगर (retval < 0)
		वापस retval;

	वापस block_group;
पूर्ण

अटल अंतरभूत पूर्णांक load_block_biपंचांगap(काष्ठा super_block *sb,
				    काष्ठा udf_biपंचांगap *biपंचांगap,
				    अचिन्हित पूर्णांक block_group)
अणु
	पूर्णांक slot;

	slot = __load_block_biपंचांगap(sb, biपंचांगap, block_group);

	अगर (slot < 0)
		वापस slot;

	अगर (!biपंचांगap->s_block_biपंचांगap[slot])
		वापस -EIO;

	वापस slot;
पूर्ण

अटल व्योम udf_add_मुक्त_space(काष्ठा super_block *sb, u16 partition, u32 cnt)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा logicalVolIntegrityDesc *lvid;

	अगर (!sbi->s_lvid_bh)
		वापस;

	lvid = (काष्ठा logicalVolIntegrityDesc *)sbi->s_lvid_bh->b_data;
	le32_add_cpu(&lvid->मुक्तSpaceTable[partition], cnt);
	udf_updated_lvid(sb);
पूर्ण

अटल व्योम udf_biपंचांगap_मुक्त_blocks(काष्ठा super_block *sb,
				   काष्ठा udf_biपंचांगap *biपंचांगap,
				   काष्ठा kernel_lb_addr *bloc,
				   uपूर्णांक32_t offset,
				   uपूर्णांक32_t count)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा udf_part_map *parपंचांगap;
	अचिन्हित दीर्घ block;
	अचिन्हित दीर्घ block_group;
	अचिन्हित दीर्घ bit;
	अचिन्हित दीर्घ i;
	पूर्णांक biपंचांगap_nr;
	अचिन्हित दीर्घ overflow;

	mutex_lock(&sbi->s_alloc_mutex);
	parपंचांगap = &sbi->s_parपंचांगaps[bloc->partitionReferenceNum];
	अगर (bloc->logicalBlockNum + count < count ||
	    (bloc->logicalBlockNum + count) > parपंचांगap->s_partition_len) अणु
		udf_debug("%u < %d || %u + %u > %u\n",
			  bloc->logicalBlockNum, 0,
			  bloc->logicalBlockNum, count,
			  parपंचांगap->s_partition_len);
		जाओ error_वापस;
	पूर्ण

	block = bloc->logicalBlockNum + offset +
		(माप(काष्ठा spaceBiपंचांगapDesc) << 3);

	करो अणु
		overflow = 0;
		block_group = block >> (sb->s_blocksize_bits + 3);
		bit = block % (sb->s_blocksize << 3);

		/*
		* Check to see अगर we are मुक्तing blocks across a group boundary.
		*/
		अगर (bit + count > (sb->s_blocksize << 3)) अणु
			overflow = bit + count - (sb->s_blocksize << 3);
			count -= overflow;
		पूर्ण
		biपंचांगap_nr = load_block_biपंचांगap(sb, biपंचांगap, block_group);
		अगर (biपंचांगap_nr < 0)
			जाओ error_वापस;

		bh = biपंचांगap->s_block_biपंचांगap[biपंचांगap_nr];
		क्रम (i = 0; i < count; i++) अणु
			अगर (udf_set_bit(bit + i, bh->b_data)) अणु
				udf_debug("bit %lu already set\n", bit + i);
				udf_debug("byte=%2x\n",
					  ((__u8 *)bh->b_data)[(bit + i) >> 3]);
			पूर्ण
		पूर्ण
		udf_add_मुक्त_space(sb, sbi->s_partition, count);
		mark_buffer_dirty(bh);
		अगर (overflow) अणु
			block += count;
			count = overflow;
		पूर्ण
	पूर्ण जबतक (overflow);

error_वापस:
	mutex_unlock(&sbi->s_alloc_mutex);
पूर्ण

अटल पूर्णांक udf_biपंचांगap_pपुनः_स्मृति_blocks(काष्ठा super_block *sb,
				      काष्ठा udf_biपंचांगap *biपंचांगap,
				      uपूर्णांक16_t partition, uपूर्णांक32_t first_block,
				      uपूर्णांक32_t block_count)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक alloc_count = 0;
	पूर्णांक bit, block, block_group;
	पूर्णांक biपंचांगap_nr;
	काष्ठा buffer_head *bh;
	__u32 part_len;

	mutex_lock(&sbi->s_alloc_mutex);
	part_len = sbi->s_parपंचांगaps[partition].s_partition_len;
	अगर (first_block >= part_len)
		जाओ out;

	अगर (first_block + block_count > part_len)
		block_count = part_len - first_block;

	करो अणु
		block = first_block + (माप(काष्ठा spaceBiपंचांगapDesc) << 3);
		block_group = block >> (sb->s_blocksize_bits + 3);

		biपंचांगap_nr = load_block_biपंचांगap(sb, biपंचांगap, block_group);
		अगर (biपंचांगap_nr < 0)
			जाओ out;
		bh = biपंचांगap->s_block_biपंचांगap[biपंचांगap_nr];

		bit = block % (sb->s_blocksize << 3);

		जबतक (bit < (sb->s_blocksize << 3) && block_count > 0) अणु
			अगर (!udf_clear_bit(bit, bh->b_data))
				जाओ out;
			block_count--;
			alloc_count++;
			bit++;
			block++;
		पूर्ण
		mark_buffer_dirty(bh);
	पूर्ण जबतक (block_count > 0);

out:
	udf_add_मुक्त_space(sb, partition, -alloc_count);
	mutex_unlock(&sbi->s_alloc_mutex);
	वापस alloc_count;
पूर्ण

अटल udf_pblk_t udf_biपंचांगap_new_block(काष्ठा super_block *sb,
				काष्ठा udf_biपंचांगap *biपंचांगap, uपूर्णांक16_t partition,
				uपूर्णांक32_t goal, पूर्णांक *err)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक newbit, bit = 0;
	udf_pblk_t block;
	पूर्णांक block_group, group_start;
	पूर्णांक end_goal, nr_groups, biपंचांगap_nr, i;
	काष्ठा buffer_head *bh = शून्य;
	अक्षर *ptr;
	udf_pblk_t newblock = 0;

	*err = -ENOSPC;
	mutex_lock(&sbi->s_alloc_mutex);

repeat:
	अगर (goal >= sbi->s_parपंचांगaps[partition].s_partition_len)
		goal = 0;

	nr_groups = biपंचांगap->s_nr_groups;
	block = goal + (माप(काष्ठा spaceBiपंचांगapDesc) << 3);
	block_group = block >> (sb->s_blocksize_bits + 3);
	group_start = block_group ? 0 : माप(काष्ठा spaceBiपंचांगapDesc);

	biपंचांगap_nr = load_block_biपंचांगap(sb, biपंचांगap, block_group);
	अगर (biपंचांगap_nr < 0)
		जाओ error_वापस;
	bh = biपंचांगap->s_block_biपंचांगap[biपंचांगap_nr];
	ptr = memscan((अक्षर *)bh->b_data + group_start, 0xFF,
		      sb->s_blocksize - group_start);

	अगर ((ptr - ((अक्षर *)bh->b_data)) < sb->s_blocksize) अणु
		bit = block % (sb->s_blocksize << 3);
		अगर (udf_test_bit(bit, bh->b_data))
			जाओ got_block;

		end_goal = (bit + 63) & ~63;
		bit = udf_find_next_one_bit(bh->b_data, end_goal, bit);
		अगर (bit < end_goal)
			जाओ got_block;

		ptr = memscan((अक्षर *)bh->b_data + (bit >> 3), 0xFF,
			      sb->s_blocksize - ((bit + 7) >> 3));
		newbit = (ptr - ((अक्षर *)bh->b_data)) << 3;
		अगर (newbit < sb->s_blocksize << 3) अणु
			bit = newbit;
			जाओ search_back;
		पूर्ण

		newbit = udf_find_next_one_bit(bh->b_data,
					       sb->s_blocksize << 3, bit);
		अगर (newbit < sb->s_blocksize << 3) अणु
			bit = newbit;
			जाओ got_block;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < (nr_groups * 2); i++) अणु
		block_group++;
		अगर (block_group >= nr_groups)
			block_group = 0;
		group_start = block_group ? 0 : माप(काष्ठा spaceBiपंचांगapDesc);

		biपंचांगap_nr = load_block_biपंचांगap(sb, biपंचांगap, block_group);
		अगर (biपंचांगap_nr < 0)
			जाओ error_वापस;
		bh = biपंचांगap->s_block_biपंचांगap[biपंचांगap_nr];
		अगर (i < nr_groups) अणु
			ptr = memscan((अक्षर *)bh->b_data + group_start, 0xFF,
				      sb->s_blocksize - group_start);
			अगर ((ptr - ((अक्षर *)bh->b_data)) < sb->s_blocksize) अणु
				bit = (ptr - ((अक्षर *)bh->b_data)) << 3;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			bit = udf_find_next_one_bit(bh->b_data,
						    sb->s_blocksize << 3,
						    group_start << 3);
			अगर (bit < sb->s_blocksize << 3)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (i >= (nr_groups * 2)) अणु
		mutex_unlock(&sbi->s_alloc_mutex);
		वापस newblock;
	पूर्ण
	अगर (bit < sb->s_blocksize << 3)
		जाओ search_back;
	अन्यथा
		bit = udf_find_next_one_bit(bh->b_data, sb->s_blocksize << 3,
					    group_start << 3);
	अगर (bit >= sb->s_blocksize << 3) अणु
		mutex_unlock(&sbi->s_alloc_mutex);
		वापस 0;
	पूर्ण

search_back:
	i = 0;
	जबतक (i < 7 && bit > (group_start << 3) &&
	       udf_test_bit(bit - 1, bh->b_data)) अणु
		++i;
		--bit;
	पूर्ण

got_block:
	newblock = bit + (block_group << (sb->s_blocksize_bits + 3)) -
		(माप(काष्ठा spaceBiपंचांगapDesc) << 3);

	अगर (newblock >= sbi->s_parपंचांगaps[partition].s_partition_len) अणु
		/*
		 * Ran off the end of the biपंचांगap, and bits following are
		 * non-compliant (not all zero)
		 */
		udf_err(sb, "bitmap for partition %d corrupted (block %u marked"
			" as free, partition length is %u)\n", partition,
			newblock, sbi->s_parपंचांगaps[partition].s_partition_len);
		जाओ error_वापस;
	पूर्ण

	अगर (!udf_clear_bit(bit, bh->b_data)) अणु
		udf_debug("bit already cleared for block %d\n", bit);
		जाओ repeat;
	पूर्ण

	mark_buffer_dirty(bh);

	udf_add_मुक्त_space(sb, partition, -1);
	mutex_unlock(&sbi->s_alloc_mutex);
	*err = 0;
	वापस newblock;

error_वापस:
	*err = -EIO;
	mutex_unlock(&sbi->s_alloc_mutex);
	वापस 0;
पूर्ण

अटल व्योम udf_table_मुक्त_blocks(काष्ठा super_block *sb,
				  काष्ठा inode *table,
				  काष्ठा kernel_lb_addr *bloc,
				  uपूर्णांक32_t offset,
				  uपूर्णांक32_t count)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *parपंचांगap;
	uपूर्णांक32_t start, end;
	uपूर्णांक32_t elen;
	काष्ठा kernel_lb_addr eloc;
	काष्ठा extent_position oepos, epos;
	पूर्णांक8_t etype;
	काष्ठा udf_inode_info *iinfo;

	mutex_lock(&sbi->s_alloc_mutex);
	parपंचांगap = &sbi->s_parपंचांगaps[bloc->partitionReferenceNum];
	अगर (bloc->logicalBlockNum + count < count ||
	    (bloc->logicalBlockNum + count) > parपंचांगap->s_partition_len) अणु
		udf_debug("%u < %d || %u + %u > %u\n",
			  bloc->logicalBlockNum, 0,
			  bloc->logicalBlockNum, count,
			  parपंचांगap->s_partition_len);
		जाओ error_वापस;
	पूर्ण

	iinfo = UDF_I(table);
	udf_add_मुक्त_space(sb, sbi->s_partition, count);

	start = bloc->logicalBlockNum + offset;
	end = bloc->logicalBlockNum + offset + count - 1;

	epos.offset = oepos.offset = माप(काष्ठा unallocSpaceEntry);
	elen = 0;
	epos.block = oepos.block = iinfo->i_location;
	epos.bh = oepos.bh = शून्य;

	जबतक (count &&
	       (etype = udf_next_aext(table, &epos, &eloc, &elen, 1)) != -1) अणु
		अगर (((eloc.logicalBlockNum +
			(elen >> sb->s_blocksize_bits)) == start)) अणु
			अगर ((0x3FFFFFFF - elen) <
					(count << sb->s_blocksize_bits)) अणु
				uपूर्णांक32_t पंचांगp = ((0x3FFFFFFF - elen) >>
							sb->s_blocksize_bits);
				count -= पंचांगp;
				start += पंचांगp;
				elen = (etype << 30) |
					(0x40000000 - sb->s_blocksize);
			पूर्ण अन्यथा अणु
				elen = (etype << 30) |
					(elen +
					(count << sb->s_blocksize_bits));
				start += count;
				count = 0;
			पूर्ण
			udf_ग_लिखो_aext(table, &oepos, &eloc, elen, 1);
		पूर्ण अन्यथा अगर (eloc.logicalBlockNum == (end + 1)) अणु
			अगर ((0x3FFFFFFF - elen) <
					(count << sb->s_blocksize_bits)) अणु
				uपूर्णांक32_t पंचांगp = ((0x3FFFFFFF - elen) >>
						sb->s_blocksize_bits);
				count -= पंचांगp;
				end -= पंचांगp;
				eloc.logicalBlockNum -= पंचांगp;
				elen = (etype << 30) |
					(0x40000000 - sb->s_blocksize);
			पूर्ण अन्यथा अणु
				eloc.logicalBlockNum = start;
				elen = (etype << 30) |
					(elen +
					(count << sb->s_blocksize_bits));
				end -= count;
				count = 0;
			पूर्ण
			udf_ग_लिखो_aext(table, &oepos, &eloc, elen, 1);
		पूर्ण

		अगर (epos.bh != oepos.bh) अणु
			oepos.block = epos.block;
			brअन्यथा(oepos.bh);
			get_bh(epos.bh);
			oepos.bh = epos.bh;
			oepos.offset = 0;
		पूर्ण अन्यथा अणु
			oepos.offset = epos.offset;
		पूर्ण
	पूर्ण

	अगर (count) अणु
		/*
		 * NOTE: we CANNOT use udf_add_aext here, as it can try to
		 * allocate a new block, and since we hold the super block
		 * lock alपढ़ोy very bad things would happen :)
		 *
		 * We copy the behavior of udf_add_aext, but instead of
		 * trying to allocate a new block बंद to the existing one,
		 * we just steal a block from the extent we are trying to add.
		 *
		 * It would be nice अगर the blocks were बंद together, but it
		 * isn't required.
		 */

		पूर्णांक adsize;

		eloc.logicalBlockNum = start;
		elen = EXT_RECORDED_ALLOCATED |
			(count << sb->s_blocksize_bits);

		अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
			adsize = माप(काष्ठा लघु_ad);
		अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
			adsize = माप(काष्ठा दीर्घ_ad);
		अन्यथा अणु
			brअन्यथा(oepos.bh);
			brअन्यथा(epos.bh);
			जाओ error_वापस;
		पूर्ण

		अगर (epos.offset + (2 * adsize) > sb->s_blocksize) अणु
			/* Steal a block from the extent being मुक्त'd */
			udf_setup_indirect_aext(table, eloc.logicalBlockNum,
						&epos);

			eloc.logicalBlockNum++;
			elen -= sb->s_blocksize;
		पूर्ण

		/* It's possible that stealing the block emptied the extent */
		अगर (elen)
			__udf_add_aext(table, &epos, &eloc, elen, 1);
	पूर्ण

	brअन्यथा(epos.bh);
	brअन्यथा(oepos.bh);

error_वापस:
	mutex_unlock(&sbi->s_alloc_mutex);
	वापस;
पूर्ण

अटल पूर्णांक udf_table_pपुनः_स्मृति_blocks(काष्ठा super_block *sb,
				     काष्ठा inode *table, uपूर्णांक16_t partition,
				     uपूर्णांक32_t first_block, uपूर्णांक32_t block_count)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	पूर्णांक alloc_count = 0;
	uपूर्णांक32_t elen, adsize;
	काष्ठा kernel_lb_addr eloc;
	काष्ठा extent_position epos;
	पूर्णांक8_t etype = -1;
	काष्ठा udf_inode_info *iinfo;

	अगर (first_block >= sbi->s_parपंचांगaps[partition].s_partition_len)
		वापस 0;

	iinfo = UDF_I(table);
	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		वापस 0;

	mutex_lock(&sbi->s_alloc_mutex);
	epos.offset = माप(काष्ठा unallocSpaceEntry);
	epos.block = iinfo->i_location;
	epos.bh = शून्य;
	eloc.logicalBlockNum = 0xFFFFFFFF;

	जबतक (first_block != eloc.logicalBlockNum &&
	       (etype = udf_next_aext(table, &epos, &eloc, &elen, 1)) != -1) अणु
		udf_debug("eloc=%u, elen=%u, first_block=%u\n",
			  eloc.logicalBlockNum, elen, first_block);
		; /* empty loop body */
	पूर्ण

	अगर (first_block == eloc.logicalBlockNum) अणु
		epos.offset -= adsize;

		alloc_count = (elen >> sb->s_blocksize_bits);
		अगर (alloc_count > block_count) अणु
			alloc_count = block_count;
			eloc.logicalBlockNum += alloc_count;
			elen -= (alloc_count << sb->s_blocksize_bits);
			udf_ग_लिखो_aext(table, &epos, &eloc,
					(etype << 30) | elen, 1);
		पूर्ण अन्यथा
			udf_delete_aext(table, epos);
	पूर्ण अन्यथा अणु
		alloc_count = 0;
	पूर्ण

	brअन्यथा(epos.bh);

	अगर (alloc_count)
		udf_add_मुक्त_space(sb, partition, -alloc_count);
	mutex_unlock(&sbi->s_alloc_mutex);
	वापस alloc_count;
पूर्ण

अटल udf_pblk_t udf_table_new_block(काष्ठा super_block *sb,
			       काष्ठा inode *table, uपूर्णांक16_t partition,
			       uपूर्णांक32_t goal, पूर्णांक *err)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	uपूर्णांक32_t spपढ़ो = 0xFFFFFFFF, nspपढ़ो = 0xFFFFFFFF;
	udf_pblk_t newblock = 0;
	uपूर्णांक32_t adsize;
	uपूर्णांक32_t elen, goal_elen = 0;
	काष्ठा kernel_lb_addr eloc, goal_eloc;
	काष्ठा extent_position epos, goal_epos;
	पूर्णांक8_t etype;
	काष्ठा udf_inode_info *iinfo = UDF_I(table);

	*err = -ENOSPC;

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		वापस newblock;

	mutex_lock(&sbi->s_alloc_mutex);
	अगर (goal >= sbi->s_parपंचांगaps[partition].s_partition_len)
		goal = 0;

	/* We search क्रम the बंदst matching block to goal. If we find
	   a exact hit, we stop. Otherwise we keep going till we run out
	   of extents. We store the buffer_head, bloc, and extoffset
	   of the current बंदst match and use that when we are करोne.
	 */
	epos.offset = माप(काष्ठा unallocSpaceEntry);
	epos.block = iinfo->i_location;
	epos.bh = goal_epos.bh = शून्य;

	जबतक (spपढ़ो &&
	       (etype = udf_next_aext(table, &epos, &eloc, &elen, 1)) != -1) अणु
		अगर (goal >= eloc.logicalBlockNum) अणु
			अगर (goal < eloc.logicalBlockNum +
					(elen >> sb->s_blocksize_bits))
				nspपढ़ो = 0;
			अन्यथा
				nspपढ़ो = goal - eloc.logicalBlockNum -
					(elen >> sb->s_blocksize_bits);
		पूर्ण अन्यथा अणु
			nspपढ़ो = eloc.logicalBlockNum - goal;
		पूर्ण

		अगर (nspपढ़ो < spपढ़ो) अणु
			spपढ़ो = nspपढ़ो;
			अगर (goal_epos.bh != epos.bh) अणु
				brअन्यथा(goal_epos.bh);
				goal_epos.bh = epos.bh;
				get_bh(goal_epos.bh);
			पूर्ण
			goal_epos.block = epos.block;
			goal_epos.offset = epos.offset - adsize;
			goal_eloc = eloc;
			goal_elen = (etype << 30) | elen;
		पूर्ण
	पूर्ण

	brअन्यथा(epos.bh);

	अगर (spपढ़ो == 0xFFFFFFFF) अणु
		brअन्यथा(goal_epos.bh);
		mutex_unlock(&sbi->s_alloc_mutex);
		वापस 0;
	पूर्ण

	/* Only allocate blocks from the beginning of the extent.
	   That way, we only delete (empty) extents, never have to insert an
	   extent because of splitting */
	/* This works, but very poorly.... */

	newblock = goal_eloc.logicalBlockNum;
	goal_eloc.logicalBlockNum++;
	goal_elen -= sb->s_blocksize;

	अगर (goal_elen)
		udf_ग_लिखो_aext(table, &goal_epos, &goal_eloc, goal_elen, 1);
	अन्यथा
		udf_delete_aext(table, goal_epos);
	brअन्यथा(goal_epos.bh);

	udf_add_मुक्त_space(sb, partition, -1);

	mutex_unlock(&sbi->s_alloc_mutex);
	*err = 0;
	वापस newblock;
पूर्ण

व्योम udf_मुक्त_blocks(काष्ठा super_block *sb, काष्ठा inode *inode,
		     काष्ठा kernel_lb_addr *bloc, uपूर्णांक32_t offset,
		     uपूर्णांक32_t count)
अणु
	uपूर्णांक16_t partition = bloc->partitionReferenceNum;
	काष्ठा udf_part_map *map = &UDF_SB(sb)->s_parपंचांगaps[partition];

	अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP) अणु
		udf_biपंचांगap_मुक्त_blocks(sb, map->s_uspace.s_biपंचांगap,
				       bloc, offset, count);
	पूर्ण अन्यथा अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE) अणु
		udf_table_मुक्त_blocks(sb, map->s_uspace.s_table,
				      bloc, offset, count);
	पूर्ण

	अगर (inode) अणु
		inode_sub_bytes(inode,
				((sector_t)count) << sb->s_blocksize_bits);
	पूर्ण
पूर्ण

अंतरभूत पूर्णांक udf_pपुनः_स्मृति_blocks(काष्ठा super_block *sb,
			       काष्ठा inode *inode,
			       uपूर्णांक16_t partition, uपूर्णांक32_t first_block,
			       uपूर्णांक32_t block_count)
अणु
	काष्ठा udf_part_map *map = &UDF_SB(sb)->s_parपंचांगaps[partition];
	पूर्णांक allocated;

	अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP)
		allocated = udf_biपंचांगap_pपुनः_स्मृति_blocks(sb,
						       map->s_uspace.s_biपंचांगap,
						       partition, first_block,
						       block_count);
	अन्यथा अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE)
		allocated = udf_table_pपुनः_स्मृति_blocks(sb,
						      map->s_uspace.s_table,
						      partition, first_block,
						      block_count);
	अन्यथा
		वापस 0;

	अगर (inode && allocated > 0)
		inode_add_bytes(inode, allocated << sb->s_blocksize_bits);
	वापस allocated;
पूर्ण

अंतरभूत udf_pblk_t udf_new_block(काष्ठा super_block *sb,
			 काष्ठा inode *inode,
			 uपूर्णांक16_t partition, uपूर्णांक32_t goal, पूर्णांक *err)
अणु
	काष्ठा udf_part_map *map = &UDF_SB(sb)->s_parपंचांगaps[partition];
	udf_pblk_t block;

	अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP)
		block = udf_biपंचांगap_new_block(sb,
					     map->s_uspace.s_biपंचांगap,
					     partition, goal, err);
	अन्यथा अगर (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE)
		block = udf_table_new_block(sb,
					    map->s_uspace.s_table,
					    partition, goal, err);
	अन्यथा अणु
		*err = -EIO;
		वापस 0;
	पूर्ण
	अगर (inode && block)
		inode_add_bytes(inode, sb->s_blocksize);
	वापस block;
पूर्ण
