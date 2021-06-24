<शैली गुरु>
/*
 * partition.c
 *
 * PURPOSE
 *      Partition handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *      This file is distributed under the terms of the GNU General Public
 *      License (GPL). Copies of the GPL can be obtained from:
 *              ftp://prep.ai.mit.edu/pub/gnu/GPL
 *      Each contributing author retains all rights to their own work.
 *
 *  (C) 1998-2001 Ben Fennema
 *
 * HISTORY
 *
 * 12/06/98 blf  Created file.
 *
 */

#समावेश "udfdecl.h"
#समावेश "udf_sb.h"
#समावेश "udf_i.h"

#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>

uपूर्णांक32_t udf_get_pblock(काष्ठा super_block *sb, uपूर्णांक32_t block,
			uपूर्णांक16_t partition, uपूर्णांक32_t offset)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map;
	अगर (partition >= sbi->s_partitions) अणु
		udf_debug("block=%u, partition=%u, offset=%u: invalid partition\n",
			  block, partition, offset);
		वापस 0xFFFFFFFF;
	पूर्ण
	map = &sbi->s_parपंचांगaps[partition];
	अगर (map->s_partition_func)
		वापस map->s_partition_func(sb, block, partition, offset);
	अन्यथा
		वापस map->s_partition_root + block + offset;
पूर्ण

uपूर्णांक32_t udf_get_pblock_virt15(काष्ठा super_block *sb, uपूर्णांक32_t block,
			       uपूर्णांक16_t partition, uपूर्णांक32_t offset)
अणु
	काष्ठा buffer_head *bh = शून्य;
	uपूर्णांक32_t newblock;
	uपूर्णांक32_t index;
	uपूर्णांक32_t loc;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map;
	काष्ठा udf_भव_data *vdata;
	काष्ठा udf_inode_info *iinfo = UDF_I(sbi->s_vat_inode);

	map = &sbi->s_parपंचांगaps[partition];
	vdata = &map->s_type_specअगरic.s_भव;

	अगर (block > vdata->s_num_entries) अणु
		udf_debug("Trying to access block beyond end of VAT (%u max %u)\n",
			  block, vdata->s_num_entries);
		वापस 0xFFFFFFFF;
	पूर्ण

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
		loc = le32_to_cpu(((__le32 *)(iinfo->i_data +
			vdata->s_start_offset))[block]);
		जाओ translate;
	पूर्ण
	index = (sb->s_blocksize - vdata->s_start_offset) / माप(uपूर्णांक32_t);
	अगर (block >= index) अणु
		block -= index;
		newblock = 1 + (block / (sb->s_blocksize / माप(uपूर्णांक32_t)));
		index = block % (sb->s_blocksize / माप(uपूर्णांक32_t));
	पूर्ण अन्यथा अणु
		newblock = 0;
		index = vdata->s_start_offset / माप(uपूर्णांक32_t) + block;
	पूर्ण

	loc = udf_block_map(sbi->s_vat_inode, newblock);

	bh = sb_bपढ़ो(sb, loc);
	अगर (!bh) अणु
		udf_debug("get_pblock(UDF_VIRTUAL_MAP:%p,%u,%u) VAT: %u[%u]\n",
			  sb, block, partition, loc, index);
		वापस 0xFFFFFFFF;
	पूर्ण

	loc = le32_to_cpu(((__le32 *)bh->b_data)[index]);

	brअन्यथा(bh);

translate:
	अगर (iinfo->i_location.partitionReferenceNum == partition) अणु
		udf_debug("recursive call to udf_get_pblock!\n");
		वापस 0xFFFFFFFF;
	पूर्ण

	वापस udf_get_pblock(sb, loc,
			      iinfo->i_location.partitionReferenceNum,
			      offset);
पूर्ण

अंतरभूत uपूर्णांक32_t udf_get_pblock_virt20(काष्ठा super_block *sb, uपूर्णांक32_t block,
				      uपूर्णांक16_t partition, uपूर्णांक32_t offset)
अणु
	वापस udf_get_pblock_virt15(sb, block, partition, offset);
पूर्ण

uपूर्णांक32_t udf_get_pblock_spar15(काष्ठा super_block *sb, uपूर्णांक32_t block,
			       uपूर्णांक16_t partition, uपूर्णांक32_t offset)
अणु
	पूर्णांक i;
	काष्ठा sparingTable *st = शून्य;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map;
	uपूर्णांक32_t packet;
	काष्ठा udf_sparing_data *sdata;

	map = &sbi->s_parपंचांगaps[partition];
	sdata = &map->s_type_specअगरic.s_sparing;
	packet = (block + offset) & ~(sdata->s_packet_len - 1);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (sdata->s_spar_map[i] != शून्य) अणु
			st = (काष्ठा sparingTable *)
					sdata->s_spar_map[i]->b_data;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (st) अणु
		क्रम (i = 0; i < le16_to_cpu(st->पुनः_स्मृतिationTableLen); i++) अणु
			काष्ठा sparingEntry *entry = &st->mapEntry[i];
			u32 origLoc = le32_to_cpu(entry->origLocation);
			अगर (origLoc >= 0xFFFFFFF0)
				अवरोध;
			अन्यथा अगर (origLoc == packet)
				वापस le32_to_cpu(entry->mappedLocation) +
					((block + offset) &
						(sdata->s_packet_len - 1));
			अन्यथा अगर (origLoc > packet)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस map->s_partition_root + block + offset;
पूर्ण

पूर्णांक udf_relocate_blocks(काष्ठा super_block *sb, दीर्घ old_block, दीर्घ *new_block)
अणु
	काष्ठा udf_sparing_data *sdata;
	काष्ठा sparingTable *st = शून्य;
	काष्ठा sparingEntry mapEntry;
	uपूर्णांक32_t packet;
	पूर्णांक i, j, k, l;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	u16 पुनः_स्मृतिationTableLen;
	काष्ठा buffer_head *bh;
	पूर्णांक ret = 0;

	mutex_lock(&sbi->s_alloc_mutex);
	क्रम (i = 0; i < sbi->s_partitions; i++) अणु
		काष्ठा udf_part_map *map = &sbi->s_parपंचांगaps[i];
		अगर (old_block > map->s_partition_root &&
		    old_block < map->s_partition_root + map->s_partition_len) अणु
			sdata = &map->s_type_specअगरic.s_sparing;
			packet = (old_block - map->s_partition_root) &
						~(sdata->s_packet_len - 1);

			क्रम (j = 0; j < 4; j++)
				अगर (sdata->s_spar_map[j] != शून्य) अणु
					st = (काष्ठा sparingTable *)
						sdata->s_spar_map[j]->b_data;
					अवरोध;
				पूर्ण

			अगर (!st) अणु
				ret = 1;
				जाओ out;
			पूर्ण

			पुनः_स्मृतिationTableLen =
					le16_to_cpu(st->पुनः_स्मृतिationTableLen);
			क्रम (k = 0; k < पुनः_स्मृतिationTableLen; k++) अणु
				काष्ठा sparingEntry *entry = &st->mapEntry[k];
				u32 origLoc = le32_to_cpu(entry->origLocation);

				अगर (origLoc == 0xFFFFFFFF) अणु
					क्रम (; j < 4; j++) अणु
						पूर्णांक len;
						bh = sdata->s_spar_map[j];
						अगर (!bh)
							जारी;

						st = (काष्ठा sparingTable *)
								bh->b_data;
						entry->origLocation =
							cpu_to_le32(packet);
						len =
						  माप(काष्ठा sparingTable) +
						  पुनः_स्मृतिationTableLen *
						  माप(काष्ठा sparingEntry);
						udf_update_tag((अक्षर *)st, len);
						mark_buffer_dirty(bh);
					पूर्ण
					*new_block = le32_to_cpu(
							entry->mappedLocation) +
						     ((old_block -
							map->s_partition_root) &
						     (sdata->s_packet_len - 1));
					ret = 0;
					जाओ out;
				पूर्ण अन्यथा अगर (origLoc == packet) अणु
					*new_block = le32_to_cpu(
							entry->mappedLocation) +
						     ((old_block -
							map->s_partition_root) &
						     (sdata->s_packet_len - 1));
					ret = 0;
					जाओ out;
				पूर्ण अन्यथा अगर (origLoc > packet)
					अवरोध;
			पूर्ण

			क्रम (l = k; l < पुनः_स्मृतिationTableLen; l++) अणु
				काष्ठा sparingEntry *entry = &st->mapEntry[l];
				u32 origLoc = le32_to_cpu(entry->origLocation);

				अगर (origLoc != 0xFFFFFFFF)
					जारी;

				क्रम (; j < 4; j++) अणु
					bh = sdata->s_spar_map[j];
					अगर (!bh)
						जारी;

					st = (काष्ठा sparingTable *)bh->b_data;
					mapEntry = st->mapEntry[l];
					mapEntry.origLocation =
							cpu_to_le32(packet);
					स_हटाओ(&st->mapEntry[k + 1],
						&st->mapEntry[k],
						(l - k) *
						माप(काष्ठा sparingEntry));
					st->mapEntry[k] = mapEntry;
					udf_update_tag((अक्षर *)st,
						माप(काष्ठा sparingTable) +
						पुनः_स्मृतिationTableLen *
						माप(काष्ठा sparingEntry));
					mark_buffer_dirty(bh);
				पूर्ण
				*new_block =
					le32_to_cpu(
					      st->mapEntry[k].mappedLocation) +
					((old_block - map->s_partition_root) &
					 (sdata->s_packet_len - 1));
				ret = 0;
				जाओ out;
			पूर्ण

			ret = 1;
			जाओ out;
		पूर्ण /* अगर old_block */
	पूर्ण

	अगर (i == sbi->s_partitions) अणु
		/* outside of partitions */
		/* क्रम now, fail =) */
		ret = 1;
	पूर्ण

out:
	mutex_unlock(&sbi->s_alloc_mutex);
	वापस ret;
पूर्ण

अटल uपूर्णांक32_t udf_try_पढ़ो_meta(काष्ठा inode *inode, uपूर्णांक32_t block,
					uपूर्णांक16_t partition, uपूर्णांक32_t offset)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा udf_part_map *map;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;
	sector_t ext_offset;
	काष्ठा extent_position epos = अणुपूर्ण;
	uपूर्णांक32_t phyblock;

	अगर (inode_bmap(inode, block, &epos, &eloc, &elen, &ext_offset) !=
						(EXT_RECORDED_ALLOCATED >> 30))
		phyblock = 0xFFFFFFFF;
	अन्यथा अणु
		map = &UDF_SB(sb)->s_parपंचांगaps[partition];
		/* map to sparable/physical partition desc */
		phyblock = udf_get_pblock(sb, eloc.logicalBlockNum,
			map->s_type_specअगरic.s_metadata.s_phys_partition_ref,
			ext_offset + offset);
	पूर्ण

	brअन्यथा(epos.bh);
	वापस phyblock;
पूर्ण

uपूर्णांक32_t udf_get_pblock_meta25(काष्ठा super_block *sb, uपूर्णांक32_t block,
				uपूर्णांक16_t partition, uपूर्णांक32_t offset)
अणु
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा udf_part_map *map;
	काष्ठा udf_meta_data *mdata;
	uपूर्णांक32_t retblk;
	काष्ठा inode *inode;

	udf_debug("READING from METADATA\n");

	map = &sbi->s_parपंचांगaps[partition];
	mdata = &map->s_type_specअगरic.s_metadata;
	inode = mdata->s_metadata_fe ? : mdata->s_mirror_fe;

	अगर (!inode)
		वापस 0xFFFFFFFF;

	retblk = udf_try_पढ़ो_meta(inode, block, partition, offset);
	अगर (retblk == 0xFFFFFFFF && mdata->s_metadata_fe) अणु
		udf_warn(sb, "error reading from METADATA, trying to read from MIRROR\n");
		अगर (!(mdata->s_flags & MF_MIRROR_FE_LOADED)) अणु
			mdata->s_mirror_fe = udf_find_metadata_inode_efe(sb,
				mdata->s_mirror_file_loc,
				mdata->s_phys_partition_ref);
			अगर (IS_ERR(mdata->s_mirror_fe))
				mdata->s_mirror_fe = शून्य;
			mdata->s_flags |= MF_MIRROR_FE_LOADED;
		पूर्ण

		inode = mdata->s_mirror_fe;
		अगर (!inode)
			वापस 0xFFFFFFFF;
		retblk = udf_try_पढ़ो_meta(inode, block, partition, offset);
	पूर्ण

	वापस retblk;
पूर्ण
