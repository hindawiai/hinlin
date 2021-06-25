<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Qu Wenruo 2017.  All rights reserved.
 */

/*
 * The module is used to catch unexpected/corrupted tree block data.
 * Such behavior can be caused either by a fuzzed image or bugs.
 *
 * The objective is to करो leaf/node validation checks when tree block is पढ़ो
 * from disk, and check *every* possible member, so other code won't
 * need to checking them again.
 *
 * Due to the potential and unwanted damage, every checker needs to be
 * carefully reviewed otherwise so it करोes not prevent mount of valid images.
 */

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/error-injection.h>
#समावेश "ctree.h"
#समावेश "tree-checker.h"
#समावेश "disk-io.h"
#समावेश "compression.h"
#समावेश "volumes.h"
#समावेश "misc.h"

/*
 * Error message should follow the following क्रमmat:
 * corrupt <type>: <identअगरier>, <reason>[, <bad_value>]
 *
 * @type:	leaf or node
 * @identअगरier:	the necessary info to locate the leaf/node.
 * 		It's recommended to decode key.objecitd/offset if it's
 * 		meaningful.
 * @reason:	describe the error
 * @bad_value:	optional, it's recommended to output bad value and its
 *		expected value (range).
 *
 * Since comma is used to separate the components, only space is allowed
 * inside each component.
 */

/*
 * Append generic "corrupt leaf/node root=%llu block=%llu slot=%d: " to @fmt.
 * Allows callers to customize the output.
 */
__म_लिखो(3, 4)
__cold
अटल व्योम generic_err(स्थिर काष्ठा extent_buffer *eb, पूर्णांक slot,
			स्थिर अक्षर *fmt, ...)
अणु
	स्थिर काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	btrfs_crit(fs_info,
		"corrupt %s: root=%llu block=%llu slot=%d, %pV",
		btrfs_header_level(eb) == 0 ? "leaf" : "node",
		btrfs_header_owner(eb), btrfs_header_bytenr(eb), slot, &vaf);
	बहु_पूर्ण(args);
पूर्ण

/*
 * Customized reporter क्रम extent data item, since its key objectid and
 * offset has its own meaning.
 */
__म_लिखो(3, 4)
__cold
अटल व्योम file_extent_err(स्थिर काष्ठा extent_buffer *eb, पूर्णांक slot,
			    स्थिर अक्षर *fmt, ...)
अणु
	स्थिर काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	btrfs_item_key_to_cpu(eb, &key, slot);
	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	btrfs_crit(fs_info,
	"corrupt %s: root=%llu block=%llu slot=%d ino=%llu file_offset=%llu, %pV",
		btrfs_header_level(eb) == 0 ? "leaf" : "node",
		btrfs_header_owner(eb), btrfs_header_bytenr(eb), slot,
		key.objectid, key.offset, &vaf);
	बहु_पूर्ण(args);
पूर्ण

/*
 * Return 0 अगर the btrfs_file_extent_##name is aligned to @alignment
 * Else वापस 1
 */
#घोषणा CHECK_FE_ALIGNED(leaf, slot, fi, name, alignment)		      \
(अणु									      \
	अगर (unlikely(!IS_ALIGNED(btrfs_file_extent_##name((leaf), (fi)),      \
				 (alignment))))				      \
		file_extent_err((leaf), (slot),				      \
	"invalid %s for file extent, have %llu, should be aligned to %u",     \
			(#name), btrfs_file_extent_##name((leaf), (fi)),      \
			(alignment));					      \
	(!IS_ALIGNED(btrfs_file_extent_##name((leaf), (fi)), (alignment)));   \
पूर्ण)

अटल u64 file_extent_end(काष्ठा extent_buffer *leaf,
			   काष्ठा btrfs_key *key,
			   काष्ठा btrfs_file_extent_item *extent)
अणु
	u64 end;
	u64 len;

	अगर (btrfs_file_extent_type(leaf, extent) == BTRFS_खाता_EXTENT_INLINE) अणु
		len = btrfs_file_extent_ram_bytes(leaf, extent);
		end = ALIGN(key->offset + len, leaf->fs_info->sectorsize);
	पूर्ण अन्यथा अणु
		len = btrfs_file_extent_num_bytes(leaf, extent);
		end = key->offset + len;
	पूर्ण
	वापस end;
पूर्ण

/*
 * Customized report क्रम dir_item, the only new important inक्रमmation is
 * key->objectid, which represents inode number
 */
__म_लिखो(3, 4)
__cold
अटल व्योम dir_item_err(स्थिर काष्ठा extent_buffer *eb, पूर्णांक slot,
			 स्थिर अक्षर *fmt, ...)
अणु
	स्थिर काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	btrfs_item_key_to_cpu(eb, &key, slot);
	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	btrfs_crit(fs_info,
		"corrupt %s: root=%llu block=%llu slot=%d ino=%llu, %pV",
		btrfs_header_level(eb) == 0 ? "leaf" : "node",
		btrfs_header_owner(eb), btrfs_header_bytenr(eb), slot,
		key.objectid, &vaf);
	बहु_पूर्ण(args);
पूर्ण

/*
 * This functions checks prev_key->objectid, to ensure current key and prev_key
 * share the same objectid as inode number.
 *
 * This is to detect missing INODE_ITEM in subvolume trees.
 *
 * Return true अगर everything is OK or we करोn't need to check.
 * Return false अगर anything is wrong.
 */
अटल bool check_prev_ino(काष्ठा extent_buffer *leaf,
			   काष्ठा btrfs_key *key, पूर्णांक slot,
			   काष्ठा btrfs_key *prev_key)
अणु
	/* No prev key, skip check */
	अगर (slot == 0)
		वापस true;

	/* Only these key->types needs to be checked */
	ASSERT(key->type == BTRFS_XATTR_ITEM_KEY ||
	       key->type == BTRFS_INODE_REF_KEY ||
	       key->type == BTRFS_सूची_INDEX_KEY ||
	       key->type == BTRFS_सूची_ITEM_KEY ||
	       key->type == BTRFS_EXTENT_DATA_KEY);

	/*
	 * Only subvolume trees aदीर्घ with their reloc trees need this check.
	 * Things like log tree करोesn't follow this ino requirement.
	 */
	अगर (!is_fstree(btrfs_header_owner(leaf)))
		वापस true;

	अगर (key->objectid == prev_key->objectid)
		वापस true;

	/* Error found */
	dir_item_err(leaf, slot,
		"invalid previous key objectid, have %llu expect %llu",
		prev_key->objectid, key->objectid);
	वापस false;
पूर्ण
अटल पूर्णांक check_extent_data_item(काष्ठा extent_buffer *leaf,
				  काष्ठा btrfs_key *key, पूर्णांक slot,
				  काष्ठा btrfs_key *prev_key)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा btrfs_file_extent_item *fi;
	u32 sectorsize = fs_info->sectorsize;
	u32 item_size = btrfs_item_size_nr(leaf, slot);
	u64 extent_end;

	अगर (unlikely(!IS_ALIGNED(key->offset, sectorsize))) अणु
		file_extent_err(leaf, slot,
"unaligned file_offset for file extent, have %llu should be aligned to %u",
			key->offset, sectorsize);
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * Previous key must have the same key->objectid (ino).
	 * It can be XATTR_ITEM, INODE_ITEM or just another EXTENT_DATA.
	 * But अगर objectids mismatch, it means we have a missing
	 * INODE_ITEM.
	 */
	अगर (unlikely(!check_prev_ino(leaf, key, slot, prev_key)))
		वापस -EUCLEAN;

	fi = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);

	/*
	 * Make sure the item contains at least अंतरभूत header, so the file
	 * extent type is not some garbage.
	 */
	अगर (unlikely(item_size < BTRFS_खाता_EXTENT_INLINE_DATA_START)) अणु
		file_extent_err(leaf, slot,
				"invalid item size, have %u expect [%zu, %u)",
				item_size, BTRFS_खाता_EXTENT_INLINE_DATA_START,
				SZ_4K);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_file_extent_type(leaf, fi) >=
		     BTRFS_NR_खाता_EXTENT_TYPES)) अणु
		file_extent_err(leaf, slot,
		"invalid type for file extent, have %u expect range [0, %u]",
			btrfs_file_extent_type(leaf, fi),
			BTRFS_NR_खाता_EXTENT_TYPES - 1);
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * Support क्रम new compression/encryption must पूर्णांकroduce incompat flag,
	 * and must be caught in खोलो_ctree().
	 */
	अगर (unlikely(btrfs_file_extent_compression(leaf, fi) >=
		     BTRFS_NR_COMPRESS_TYPES)) अणु
		file_extent_err(leaf, slot,
	"invalid compression for file extent, have %u expect range [0, %u]",
			btrfs_file_extent_compression(leaf, fi),
			BTRFS_NR_COMPRESS_TYPES - 1);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_file_extent_encryption(leaf, fi))) अणु
		file_extent_err(leaf, slot,
			"invalid encryption for file extent, have %u expect 0",
			btrfs_file_extent_encryption(leaf, fi));
		वापस -EUCLEAN;
	पूर्ण
	अगर (btrfs_file_extent_type(leaf, fi) == BTRFS_खाता_EXTENT_INLINE) अणु
		/* Inline extent must have 0 as key offset */
		अगर (unlikely(key->offset)) अणु
			file_extent_err(leaf, slot,
		"invalid file_offset for inline file extent, have %llu expect 0",
				key->offset);
			वापस -EUCLEAN;
		पूर्ण

		/* Compressed अंतरभूत extent has no on-disk size, skip it */
		अगर (btrfs_file_extent_compression(leaf, fi) !=
		    BTRFS_COMPRESS_NONE)
			वापस 0;

		/* Uncompressed अंतरभूत extent size must match item size */
		अगर (unlikely(item_size != BTRFS_खाता_EXTENT_INLINE_DATA_START +
					  btrfs_file_extent_ram_bytes(leaf, fi))) अणु
			file_extent_err(leaf, slot,
	"invalid ram_bytes for uncompressed inline extent, have %u expect %llu",
				item_size, BTRFS_खाता_EXTENT_INLINE_DATA_START +
				btrfs_file_extent_ram_bytes(leaf, fi));
			वापस -EUCLEAN;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Regular or pपुनः_स्मृतिated extent has fixed item size */
	अगर (unlikely(item_size != माप(*fi))) अणु
		file_extent_err(leaf, slot,
	"invalid item size for reg/prealloc file extent, have %u expect %zu",
			item_size, माप(*fi));
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(CHECK_FE_ALIGNED(leaf, slot, fi, ram_bytes, sectorsize) ||
		     CHECK_FE_ALIGNED(leaf, slot, fi, disk_bytenr, sectorsize) ||
		     CHECK_FE_ALIGNED(leaf, slot, fi, disk_num_bytes, sectorsize) ||
		     CHECK_FE_ALIGNED(leaf, slot, fi, offset, sectorsize) ||
		     CHECK_FE_ALIGNED(leaf, slot, fi, num_bytes, sectorsize)))
		वापस -EUCLEAN;

	/* Catch extent end overflow */
	अगर (unlikely(check_add_overflow(btrfs_file_extent_num_bytes(leaf, fi),
					key->offset, &extent_end))) अणु
		file_extent_err(leaf, slot,
	"extent end overflow, have file offset %llu extent num bytes %llu",
				key->offset,
				btrfs_file_extent_num_bytes(leaf, fi));
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * Check that no two consecutive file extent items, in the same leaf,
	 * present ranges that overlap each other.
	 */
	अगर (slot > 0 &&
	    prev_key->objectid == key->objectid &&
	    prev_key->type == BTRFS_EXTENT_DATA_KEY) अणु
		काष्ठा btrfs_file_extent_item *prev_fi;
		u64 prev_end;

		prev_fi = btrfs_item_ptr(leaf, slot - 1,
					 काष्ठा btrfs_file_extent_item);
		prev_end = file_extent_end(leaf, prev_key, prev_fi);
		अगर (unlikely(prev_end > key->offset)) अणु
			file_extent_err(leaf, slot - 1,
"file extent end range (%llu) goes beyond start offset (%llu) of the next file extent",
					prev_end, key->offset);
			वापस -EUCLEAN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_csum_item(काष्ठा extent_buffer *leaf, काष्ठा btrfs_key *key,
			   पूर्णांक slot, काष्ठा btrfs_key *prev_key)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	u32 sectorsize = fs_info->sectorsize;
	स्थिर u32 csumsize = fs_info->csum_size;

	अगर (unlikely(key->objectid != BTRFS_EXTENT_CSUM_OBJECTID)) अणु
		generic_err(leaf, slot,
		"invalid key objectid for csum item, have %llu expect %llu",
			key->objectid, BTRFS_EXTENT_CSUM_OBJECTID);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!IS_ALIGNED(key->offset, sectorsize))) अणु
		generic_err(leaf, slot,
	"unaligned key offset for csum item, have %llu should be aligned to %u",
			key->offset, sectorsize);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!IS_ALIGNED(btrfs_item_size_nr(leaf, slot), csumsize))) अणु
		generic_err(leaf, slot,
	"unaligned item size for csum item, have %u should be aligned to %u",
			btrfs_item_size_nr(leaf, slot), csumsize);
		वापस -EUCLEAN;
	पूर्ण
	अगर (slot > 0 && prev_key->type == BTRFS_EXTENT_CSUM_KEY) अणु
		u64 prev_csum_end;
		u32 prev_item_size;

		prev_item_size = btrfs_item_size_nr(leaf, slot - 1);
		prev_csum_end = (prev_item_size / csumsize) * sectorsize;
		prev_csum_end += prev_key->offset;
		अगर (unlikely(prev_csum_end > key->offset)) अणु
			generic_err(leaf, slot - 1,
"csum end range (%llu) goes beyond the start range (%llu) of the next csum item",
				    prev_csum_end, key->offset);
			वापस -EUCLEAN;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Inode item error output has the same क्रमmat as dir_item_err() */
#घोषणा inode_item_err(eb, slot, fmt, ...)			\
	dir_item_err(eb, slot, fmt, __VA_ARGS__)

अटल पूर्णांक check_inode_key(काष्ठा extent_buffer *leaf, काष्ठा btrfs_key *key,
			   पूर्णांक slot)
अणु
	काष्ठा btrfs_key item_key;
	bool is_inode_item;

	btrfs_item_key_to_cpu(leaf, &item_key, slot);
	is_inode_item = (item_key.type == BTRFS_INODE_ITEM_KEY);

	/* For XATTR_ITEM, location key should be all 0 */
	अगर (item_key.type == BTRFS_XATTR_ITEM_KEY) अणु
		अगर (unlikely(key->objectid != 0 || key->type != 0 ||
			     key->offset != 0))
			वापस -EUCLEAN;
		वापस 0;
	पूर्ण

	अगर (unlikely((key->objectid < BTRFS_FIRST_FREE_OBJECTID ||
		      key->objectid > BTRFS_LAST_FREE_OBJECTID) &&
		     key->objectid != BTRFS_ROOT_TREE_सूची_OBJECTID &&
		     key->objectid != BTRFS_FREE_INO_OBJECTID)) अणु
		अगर (is_inode_item) अणु
			generic_err(leaf, slot,
	"invalid key objectid: has %llu expect %llu or [%llu, %llu] or %llu",
				key->objectid, BTRFS_ROOT_TREE_सूची_OBJECTID,
				BTRFS_FIRST_FREE_OBJECTID,
				BTRFS_LAST_FREE_OBJECTID,
				BTRFS_FREE_INO_OBJECTID);
		पूर्ण अन्यथा अणु
			dir_item_err(leaf, slot,
"invalid location key objectid: has %llu expect %llu or [%llu, %llu] or %llu",
				key->objectid, BTRFS_ROOT_TREE_सूची_OBJECTID,
				BTRFS_FIRST_FREE_OBJECTID,
				BTRFS_LAST_FREE_OBJECTID,
				BTRFS_FREE_INO_OBJECTID);
		पूर्ण
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(key->offset != 0)) अणु
		अगर (is_inode_item)
			inode_item_err(leaf, slot,
				       "invalid key offset: has %llu expect 0",
				       key->offset);
		अन्यथा
			dir_item_err(leaf, slot,
				"invalid location key offset:has %llu expect 0",
				key->offset);
		वापस -EUCLEAN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_root_key(काष्ठा extent_buffer *leaf, काष्ठा btrfs_key *key,
			  पूर्णांक slot)
अणु
	काष्ठा btrfs_key item_key;
	bool is_root_item;

	btrfs_item_key_to_cpu(leaf, &item_key, slot);
	is_root_item = (item_key.type == BTRFS_ROOT_ITEM_KEY);

	/* No such tree id */
	अगर (unlikely(key->objectid == 0)) अणु
		अगर (is_root_item)
			generic_err(leaf, slot, "invalid root id 0");
		अन्यथा
			dir_item_err(leaf, slot,
				     "invalid location key root id 0");
		वापस -EUCLEAN;
	पूर्ण

	/* सूची_ITEM/INDEX/INODE_REF is not allowed to poपूर्णांक to non-fs trees */
	अगर (unlikely(!is_fstree(key->objectid) && !is_root_item)) अणु
		dir_item_err(leaf, slot,
		"invalid location key objectid, have %llu expect [%llu, %llu]",
				key->objectid, BTRFS_FIRST_FREE_OBJECTID,
				BTRFS_LAST_FREE_OBJECTID);
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * ROOT_ITEM with non-zero offset means this is a snapshot, created at
	 * @offset transid.
	 * Furthermore, क्रम location key in सूची_ITEM, its offset is always -1.
	 *
	 * So here we only check offset क्रम reloc tree whose key->offset must
	 * be a valid tree.
	 */
	अगर (unlikely(key->objectid == BTRFS_TREE_RELOC_OBJECTID &&
		     key->offset == 0)) अणु
		generic_err(leaf, slot, "invalid root id 0 for reloc tree");
		वापस -EUCLEAN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_dir_item(काष्ठा extent_buffer *leaf,
			  काष्ठा btrfs_key *key, काष्ठा btrfs_key *prev_key,
			  पूर्णांक slot)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा btrfs_dir_item *di;
	u32 item_size = btrfs_item_size_nr(leaf, slot);
	u32 cur = 0;

	अगर (unlikely(!check_prev_ino(leaf, key, slot, prev_key)))
		वापस -EUCLEAN;

	di = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_dir_item);
	जबतक (cur < item_size) अणु
		काष्ठा btrfs_key location_key;
		u32 name_len;
		u32 data_len;
		u32 max_name_len;
		u32 total_size;
		u32 name_hash;
		u8 dir_type;
		पूर्णांक ret;

		/* header itself should not cross item boundary */
		अगर (unlikely(cur + माप(*di) > item_size)) अणु
			dir_item_err(leaf, slot,
		"dir item header crosses item boundary, have %zu boundary %u",
				cur + माप(*di), item_size);
			वापस -EUCLEAN;
		पूर्ण

		/* Location key check */
		btrfs_dir_item_key_to_cpu(leaf, di, &location_key);
		अगर (location_key.type == BTRFS_ROOT_ITEM_KEY) अणु
			ret = check_root_key(leaf, &location_key, slot);
			अगर (unlikely(ret < 0))
				वापस ret;
		पूर्ण अन्यथा अगर (location_key.type == BTRFS_INODE_ITEM_KEY ||
			   location_key.type == 0) अणु
			ret = check_inode_key(leaf, &location_key, slot);
			अगर (unlikely(ret < 0))
				वापस ret;
		पूर्ण अन्यथा अणु
			dir_item_err(leaf, slot,
			"invalid location key type, have %u, expect %u or %u",
				     location_key.type, BTRFS_ROOT_ITEM_KEY,
				     BTRFS_INODE_ITEM_KEY);
			वापस -EUCLEAN;
		पूर्ण

		/* dir type check */
		dir_type = btrfs_dir_type(leaf, di);
		अगर (unlikely(dir_type >= BTRFS_FT_MAX)) अणु
			dir_item_err(leaf, slot,
			"invalid dir item type, have %u expect [0, %u)",
				dir_type, BTRFS_FT_MAX);
			वापस -EUCLEAN;
		पूर्ण

		अगर (unlikely(key->type == BTRFS_XATTR_ITEM_KEY &&
			     dir_type != BTRFS_FT_XATTR)) अणु
			dir_item_err(leaf, slot,
		"invalid dir item type for XATTR key, have %u expect %u",
				dir_type, BTRFS_FT_XATTR);
			वापस -EUCLEAN;
		पूर्ण
		अगर (unlikely(dir_type == BTRFS_FT_XATTR &&
			     key->type != BTRFS_XATTR_ITEM_KEY)) अणु
			dir_item_err(leaf, slot,
			"xattr dir type found for non-XATTR key");
			वापस -EUCLEAN;
		पूर्ण
		अगर (dir_type == BTRFS_FT_XATTR)
			max_name_len = XATTR_NAME_MAX;
		अन्यथा
			max_name_len = BTRFS_NAME_LEN;

		/* Name/data length check */
		name_len = btrfs_dir_name_len(leaf, di);
		data_len = btrfs_dir_data_len(leaf, di);
		अगर (unlikely(name_len > max_name_len)) अणु
			dir_item_err(leaf, slot,
			"dir item name len too long, have %u max %u",
				name_len, max_name_len);
			वापस -EUCLEAN;
		पूर्ण
		अगर (unlikely(name_len + data_len > BTRFS_MAX_XATTR_SIZE(fs_info))) अणु
			dir_item_err(leaf, slot,
			"dir item name and data len too long, have %u max %u",
				name_len + data_len,
				BTRFS_MAX_XATTR_SIZE(fs_info));
			वापस -EUCLEAN;
		पूर्ण

		अगर (unlikely(data_len && dir_type != BTRFS_FT_XATTR)) अणु
			dir_item_err(leaf, slot,
			"dir item with invalid data len, have %u expect 0",
				data_len);
			वापस -EUCLEAN;
		पूर्ण

		total_size = माप(*di) + name_len + data_len;

		/* header and name/data should not cross item boundary */
		अगर (unlikely(cur + total_size > item_size)) अणु
			dir_item_err(leaf, slot,
		"dir item data crosses item boundary, have %u boundary %u",
				cur + total_size, item_size);
			वापस -EUCLEAN;
		पूर्ण

		/*
		 * Special check क्रम XATTR/सूची_ITEM, as key->offset is name
		 * hash, should match its name
		 */
		अगर (key->type == BTRFS_सूची_ITEM_KEY ||
		    key->type == BTRFS_XATTR_ITEM_KEY) अणु
			अक्षर namebuf[max(BTRFS_NAME_LEN, XATTR_NAME_MAX)];

			पढ़ो_extent_buffer(leaf, namebuf,
					(अचिन्हित दीर्घ)(di + 1), name_len);
			name_hash = btrfs_name_hash(namebuf, name_len);
			अगर (unlikely(key->offset != name_hash)) अणु
				dir_item_err(leaf, slot,
		"name hash mismatch with key, have 0x%016x expect 0x%016llx",
					name_hash, key->offset);
				वापस -EUCLEAN;
			पूर्ण
		पूर्ण
		cur += total_size;
		di = (काष्ठा btrfs_dir_item *)((व्योम *)di + total_size);
	पूर्ण
	वापस 0;
पूर्ण

__म_लिखो(3, 4)
__cold
अटल व्योम block_group_err(स्थिर काष्ठा extent_buffer *eb, पूर्णांक slot,
			    स्थिर अक्षर *fmt, ...)
अणु
	स्थिर काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	btrfs_item_key_to_cpu(eb, &key, slot);
	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	btrfs_crit(fs_info,
	"corrupt %s: root=%llu block=%llu slot=%d bg_start=%llu bg_len=%llu, %pV",
		btrfs_header_level(eb) == 0 ? "leaf" : "node",
		btrfs_header_owner(eb), btrfs_header_bytenr(eb), slot,
		key.objectid, key.offset, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक check_block_group_item(काष्ठा extent_buffer *leaf,
				  काष्ठा btrfs_key *key, पूर्णांक slot)
अणु
	काष्ठा btrfs_block_group_item bgi;
	u32 item_size = btrfs_item_size_nr(leaf, slot);
	u64 flags;
	u64 type;

	/*
	 * Here we करोn't really care about alignment since extent allocator can
	 * handle it.  We care more about the size.
	 */
	अगर (unlikely(key->offset == 0)) अणु
		block_group_err(leaf, slot,
				"invalid block group size 0");
		वापस -EUCLEAN;
	पूर्ण

	अगर (unlikely(item_size != माप(bgi))) अणु
		block_group_err(leaf, slot,
			"invalid item size, have %u expect %zu",
				item_size, माप(bgi));
		वापस -EUCLEAN;
	पूर्ण

	पढ़ो_extent_buffer(leaf, &bgi, btrfs_item_ptr_offset(leaf, slot),
			   माप(bgi));
	अगर (unlikely(btrfs_stack_block_group_chunk_objectid(&bgi) !=
		     BTRFS_FIRST_CHUNK_TREE_OBJECTID)) अणु
		block_group_err(leaf, slot,
		"invalid block group chunk objectid, have %llu expect %llu",
				btrfs_stack_block_group_chunk_objectid(&bgi),
				BTRFS_FIRST_CHUNK_TREE_OBJECTID);
		वापस -EUCLEAN;
	पूर्ण

	अगर (unlikely(btrfs_stack_block_group_used(&bgi) > key->offset)) अणु
		block_group_err(leaf, slot,
			"invalid block group used, have %llu expect [0, %llu)",
				btrfs_stack_block_group_used(&bgi), key->offset);
		वापस -EUCLEAN;
	पूर्ण

	flags = btrfs_stack_block_group_flags(&bgi);
	अगर (unlikely(hweight64(flags & BTRFS_BLOCK_GROUP_PROखाता_MASK) > 1)) अणु
		block_group_err(leaf, slot,
"invalid profile flags, have 0x%llx (%lu bits set) expect no more than 1 bit set",
			flags & BTRFS_BLOCK_GROUP_PROखाता_MASK,
			hweight64(flags & BTRFS_BLOCK_GROUP_PROखाता_MASK));
		वापस -EUCLEAN;
	पूर्ण

	type = flags & BTRFS_BLOCK_GROUP_TYPE_MASK;
	अगर (unlikely(type != BTRFS_BLOCK_GROUP_DATA &&
		     type != BTRFS_BLOCK_GROUP_METADATA &&
		     type != BTRFS_BLOCK_GROUP_SYSTEM &&
		     type != (BTRFS_BLOCK_GROUP_METADATA |
			      BTRFS_BLOCK_GROUP_DATA))) अणु
		block_group_err(leaf, slot,
"invalid type, have 0x%llx (%lu bits set) expect either 0x%llx, 0x%llx, 0x%llx or 0x%llx",
			type, hweight64(type),
			BTRFS_BLOCK_GROUP_DATA, BTRFS_BLOCK_GROUP_METADATA,
			BTRFS_BLOCK_GROUP_SYSTEM,
			BTRFS_BLOCK_GROUP_METADATA | BTRFS_BLOCK_GROUP_DATA);
		वापस -EUCLEAN;
	पूर्ण
	वापस 0;
पूर्ण

__म_लिखो(4, 5)
__cold
अटल व्योम chunk_err(स्थिर काष्ठा extent_buffer *leaf,
		      स्थिर काष्ठा btrfs_chunk *chunk, u64 logical,
		      स्थिर अक्षर *fmt, ...)
अणु
	स्थिर काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	bool is_sb;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक i;
	पूर्णांक slot = -1;

	/* Only superblock eb is able to have such small offset */
	is_sb = (leaf->start == BTRFS_SUPER_INFO_OFFSET);

	अगर (!is_sb) अणु
		/*
		 * Get the slot number by iterating through all slots, this
		 * would provide better पढ़ोability.
		 */
		क्रम (i = 0; i < btrfs_header_nritems(leaf); i++) अणु
			अगर (btrfs_item_ptr_offset(leaf, i) ==
					(अचिन्हित दीर्घ)chunk) अणु
				slot = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (is_sb)
		btrfs_crit(fs_info,
		"corrupt superblock syschunk array: chunk_start=%llu, %pV",
			   logical, &vaf);
	अन्यथा
		btrfs_crit(fs_info,
	"corrupt leaf: root=%llu block=%llu slot=%d chunk_start=%llu, %pV",
			   BTRFS_CHUNK_TREE_OBJECTID, leaf->start, slot,
			   logical, &vaf);
	बहु_पूर्ण(args);
पूर्ण

/*
 * The common chunk check which could also work on super block sys chunk array.
 *
 * Return -EUCLEAN अगर anything is corrupted.
 * Return 0 अगर everything is OK.
 */
पूर्णांक btrfs_check_chunk_valid(काष्ठा extent_buffer *leaf,
			    काष्ठा btrfs_chunk *chunk, u64 logical)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	u64 length;
	u64 chunk_end;
	u64 stripe_len;
	u16 num_stripes;
	u16 sub_stripes;
	u64 type;
	u64 features;
	bool mixed = false;
	पूर्णांक raid_index;
	पूर्णांक nparity;
	पूर्णांक ncopies;

	length = btrfs_chunk_length(leaf, chunk);
	stripe_len = btrfs_chunk_stripe_len(leaf, chunk);
	num_stripes = btrfs_chunk_num_stripes(leaf, chunk);
	sub_stripes = btrfs_chunk_sub_stripes(leaf, chunk);
	type = btrfs_chunk_type(leaf, chunk);
	raid_index = btrfs_bg_flags_to_raid_index(type);
	ncopies = btrfs_raid_array[raid_index].ncopies;
	nparity = btrfs_raid_array[raid_index].nparity;

	अगर (unlikely(!num_stripes)) अणु
		chunk_err(leaf, chunk, logical,
			  "invalid chunk num_stripes, have %u", num_stripes);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(num_stripes < ncopies)) अणु
		chunk_err(leaf, chunk, logical,
			  "invalid chunk num_stripes < ncopies, have %u < %d",
			  num_stripes, ncopies);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(nparity && num_stripes == nparity)) अणु
		chunk_err(leaf, chunk, logical,
			  "invalid chunk num_stripes == nparity, have %u == %d",
			  num_stripes, nparity);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!IS_ALIGNED(logical, fs_info->sectorsize))) अणु
		chunk_err(leaf, chunk, logical,
		"invalid chunk logical, have %llu should aligned to %u",
			  logical, fs_info->sectorsize);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_chunk_sector_size(leaf, chunk) != fs_info->sectorsize)) अणु
		chunk_err(leaf, chunk, logical,
			  "invalid chunk sectorsize, have %u expect %u",
			  btrfs_chunk_sector_size(leaf, chunk),
			  fs_info->sectorsize);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!length || !IS_ALIGNED(length, fs_info->sectorsize))) अणु
		chunk_err(leaf, chunk, logical,
			  "invalid chunk length, have %llu", length);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(check_add_overflow(logical, length, &chunk_end))) अणु
		chunk_err(leaf, chunk, logical,
"invalid chunk logical start and length, have logical start %llu length %llu",
			  logical, length);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!is_घातer_of_2(stripe_len) || stripe_len != BTRFS_STRIPE_LEN)) अणु
		chunk_err(leaf, chunk, logical,
			  "invalid chunk stripe length: %llu",
			  stripe_len);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(type & ~(BTRFS_BLOCK_GROUP_TYPE_MASK |
			      BTRFS_BLOCK_GROUP_PROखाता_MASK))) अणु
		chunk_err(leaf, chunk, logical,
			  "unrecognized chunk type: 0x%llx",
			  ~(BTRFS_BLOCK_GROUP_TYPE_MASK |
			    BTRFS_BLOCK_GROUP_PROखाता_MASK) &
			  btrfs_chunk_type(leaf, chunk));
		वापस -EUCLEAN;
	पूर्ण

	अगर (unlikely(!has_single_bit_set(type & BTRFS_BLOCK_GROUP_PROखाता_MASK) &&
		     (type & BTRFS_BLOCK_GROUP_PROखाता_MASK) != 0)) अणु
		chunk_err(leaf, chunk, logical,
		"invalid chunk profile flag: 0x%llx, expect 0 or 1 bit set",
			  type & BTRFS_BLOCK_GROUP_PROखाता_MASK);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely((type & BTRFS_BLOCK_GROUP_TYPE_MASK) == 0)) अणु
		chunk_err(leaf, chunk, logical,
	"missing chunk type flag, have 0x%llx one bit must be set in 0x%llx",
			  type, BTRFS_BLOCK_GROUP_TYPE_MASK);
		वापस -EUCLEAN;
	पूर्ण

	अगर (unlikely((type & BTRFS_BLOCK_GROUP_SYSTEM) &&
		     (type & (BTRFS_BLOCK_GROUP_METADATA |
			      BTRFS_BLOCK_GROUP_DATA)))) अणु
		chunk_err(leaf, chunk, logical,
			  "system chunk with data or metadata type: 0x%llx",
			  type);
		वापस -EUCLEAN;
	पूर्ण

	features = btrfs_super_incompat_flags(fs_info->super_copy);
	अगर (features & BTRFS_FEATURE_INCOMPAT_MIXED_GROUPS)
		mixed = true;

	अगर (!mixed) अणु
		अगर (unlikely((type & BTRFS_BLOCK_GROUP_METADATA) &&
			     (type & BTRFS_BLOCK_GROUP_DATA))) अणु
			chunk_err(leaf, chunk, logical,
			"mixed chunk type in non-mixed mode: 0x%llx", type);
			वापस -EUCLEAN;
		पूर्ण
	पूर्ण

	अगर (unlikely((type & BTRFS_BLOCK_GROUP_RAID10 && sub_stripes != 2) ||
		     (type & BTRFS_BLOCK_GROUP_RAID1 && num_stripes != 2) ||
		     (type & BTRFS_BLOCK_GROUP_RAID5 && num_stripes < 2) ||
		     (type & BTRFS_BLOCK_GROUP_RAID6 && num_stripes < 3) ||
		     (type & BTRFS_BLOCK_GROUP_DUP && num_stripes != 2) ||
		     ((type & BTRFS_BLOCK_GROUP_PROखाता_MASK) == 0 &&
		      num_stripes != 1))) अणु
		chunk_err(leaf, chunk, logical,
			"invalid num_stripes:sub_stripes %u:%u for profile %llu",
			num_stripes, sub_stripes,
			type & BTRFS_BLOCK_GROUP_PROखाता_MASK);
		वापस -EUCLEAN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Enhanced version of chunk item checker.
 *
 * The common btrfs_check_chunk_valid() करोesn't check item size since it needs
 * to work on super block sys_chunk_array which करोesn't have full item ptr.
 */
अटल पूर्णांक check_leaf_chunk_item(काष्ठा extent_buffer *leaf,
				 काष्ठा btrfs_chunk *chunk,
				 काष्ठा btrfs_key *key, पूर्णांक slot)
अणु
	पूर्णांक num_stripes;

	अगर (unlikely(btrfs_item_size_nr(leaf, slot) < माप(काष्ठा btrfs_chunk))) अणु
		chunk_err(leaf, chunk, key->offset,
			"invalid chunk item size: have %u expect [%zu, %u)",
			btrfs_item_size_nr(leaf, slot),
			माप(काष्ठा btrfs_chunk),
			BTRFS_LEAF_DATA_SIZE(leaf->fs_info));
		वापस -EUCLEAN;
	पूर्ण

	num_stripes = btrfs_chunk_num_stripes(leaf, chunk);
	/* Let btrfs_check_chunk_valid() handle this error type */
	अगर (num_stripes == 0)
		जाओ out;

	अगर (unlikely(btrfs_chunk_item_size(num_stripes) !=
		     btrfs_item_size_nr(leaf, slot))) अणु
		chunk_err(leaf, chunk, key->offset,
			"invalid chunk item size: have %u expect %lu",
			btrfs_item_size_nr(leaf, slot),
			btrfs_chunk_item_size(num_stripes));
		वापस -EUCLEAN;
	पूर्ण
out:
	वापस btrfs_check_chunk_valid(leaf, chunk, key->offset);
पूर्ण

__म_लिखो(3, 4)
__cold
अटल व्योम dev_item_err(स्थिर काष्ठा extent_buffer *eb, पूर्णांक slot,
			 स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा btrfs_key key;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	btrfs_item_key_to_cpu(eb, &key, slot);
	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	btrfs_crit(eb->fs_info,
	"corrupt %s: root=%llu block=%llu slot=%d devid=%llu %pV",
		btrfs_header_level(eb) == 0 ? "leaf" : "node",
		btrfs_header_owner(eb), btrfs_header_bytenr(eb), slot,
		key.objectid, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक check_dev_item(काष्ठा extent_buffer *leaf,
			  काष्ठा btrfs_key *key, पूर्णांक slot)
अणु
	काष्ठा btrfs_dev_item *ditem;

	अगर (unlikely(key->objectid != BTRFS_DEV_ITEMS_OBJECTID)) अणु
		dev_item_err(leaf, slot,
			     "invalid objectid: has=%llu expect=%llu",
			     key->objectid, BTRFS_DEV_ITEMS_OBJECTID);
		वापस -EUCLEAN;
	पूर्ण
	ditem = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_dev_item);
	अगर (unlikely(btrfs_device_id(leaf, ditem) != key->offset)) अणु
		dev_item_err(leaf, slot,
			     "devid mismatch: key has=%llu item has=%llu",
			     key->offset, btrfs_device_id(leaf, ditem));
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * For device total_bytes, we करोn't have reliable way to check it, as
	 * it can be 0 क्रम device removal. Device size check can only be करोne
	 * by dev extents check.
	 */
	अगर (unlikely(btrfs_device_bytes_used(leaf, ditem) >
		     btrfs_device_total_bytes(leaf, ditem))) अणु
		dev_item_err(leaf, slot,
			     "invalid bytes used: have %llu expect [0, %llu]",
			     btrfs_device_bytes_used(leaf, ditem),
			     btrfs_device_total_bytes(leaf, ditem));
		वापस -EUCLEAN;
	पूर्ण
	/*
	 * Reमुख्यing members like io_align/type/gen/dev_group aren't really
	 * utilized.  Skip them to make later usage of them easier.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक check_inode_item(काष्ठा extent_buffer *leaf,
			    काष्ठा btrfs_key *key, पूर्णांक slot)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा btrfs_inode_item *iitem;
	u64 super_gen = btrfs_super_generation(fs_info->super_copy);
	u32 valid_mask = (S_IFMT | S_ISUID | S_ISGID | S_ISVTX | 0777);
	u32 mode;
	पूर्णांक ret;

	ret = check_inode_key(leaf, key, slot);
	अगर (unlikely(ret < 0))
		वापस ret;

	iitem = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_inode_item);

	/* Here we use super block generation + 1 to handle log tree */
	अगर (unlikely(btrfs_inode_generation(leaf, iitem) > super_gen + 1)) अणु
		inode_item_err(leaf, slot,
			"invalid inode generation: has %llu expect (0, %llu]",
			       btrfs_inode_generation(leaf, iitem),
			       super_gen + 1);
		वापस -EUCLEAN;
	पूर्ण
	/* Note क्रम ROOT_TREE_सूची_ITEM, mkfs could set its transid 0 */
	अगर (unlikely(btrfs_inode_transid(leaf, iitem) > super_gen + 1)) अणु
		inode_item_err(leaf, slot,
			"invalid inode transid: has %llu expect [0, %llu]",
			       btrfs_inode_transid(leaf, iitem), super_gen + 1);
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * For size and nbytes it's better not to be too strict, as क्रम dir
	 * item its size/nbytes can easily get wrong, but करोesn't affect
	 * anything in the fs. So here we skip the check.
	 */
	mode = btrfs_inode_mode(leaf, iitem);
	अगर (unlikely(mode & ~valid_mask)) अणु
		inode_item_err(leaf, slot,
			       "unknown mode bit detected: 0x%x",
			       mode & ~valid_mask);
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * S_IFMT is not bit mapped so we can't completely rely on
	 * is_घातer_of_2/has_single_bit_set, but it can save us from checking
	 * FIFO/CHR/सूची/REG.  Only needs to check BLK, LNK and SOCKS
	 */
	अगर (!has_single_bit_set(mode & S_IFMT)) अणु
		अगर (unlikely(!S_ISLNK(mode) && !S_ISBLK(mode) && !S_ISSOCK(mode))) अणु
			inode_item_err(leaf, slot,
			"invalid mode: has 0%o expect valid S_IF* bit(s)",
				       mode & S_IFMT);
			वापस -EUCLEAN;
		पूर्ण
	पूर्ण
	अगर (unlikely(S_ISसूची(mode) && btrfs_inode_nlink(leaf, iitem) > 1)) अणु
		inode_item_err(leaf, slot,
		       "invalid nlink: has %u expect no more than 1 for dir",
			btrfs_inode_nlink(leaf, iitem));
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_inode_flags(leaf, iitem) & ~BTRFS_INODE_FLAG_MASK)) अणु
		inode_item_err(leaf, slot,
			       "unknown flags detected: 0x%llx",
			       btrfs_inode_flags(leaf, iitem) &
			       ~BTRFS_INODE_FLAG_MASK);
		वापस -EUCLEAN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_root_item(काष्ठा extent_buffer *leaf, काष्ठा btrfs_key *key,
			   पूर्णांक slot)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा btrfs_root_item ri = अणु 0 पूर्ण;
	स्थिर u64 valid_root_flags = BTRFS_ROOT_SUBVOL_RDONLY |
				     BTRFS_ROOT_SUBVOL_DEAD;
	पूर्णांक ret;

	ret = check_root_key(leaf, key, slot);
	अगर (unlikely(ret < 0))
		वापस ret;

	अगर (unlikely(btrfs_item_size_nr(leaf, slot) != माप(ri) &&
		     btrfs_item_size_nr(leaf, slot) !=
		     btrfs_legacy_root_item_size())) अणु
		generic_err(leaf, slot,
			    "invalid root item size, have %u expect %zu or %u",
			    btrfs_item_size_nr(leaf, slot), माप(ri),
			    btrfs_legacy_root_item_size());
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * For legacy root item, the members starting at generation_v2 will be
	 * all filled with 0.
	 * And since we allow geneartion_v2 as 0, it will still pass the check.
	 */
	पढ़ो_extent_buffer(leaf, &ri, btrfs_item_ptr_offset(leaf, slot),
			   btrfs_item_size_nr(leaf, slot));

	/* Generation related */
	अगर (unlikely(btrfs_root_generation(&ri) >
		     btrfs_super_generation(fs_info->super_copy) + 1)) अणु
		generic_err(leaf, slot,
			"invalid root generation, have %llu expect (0, %llu]",
			    btrfs_root_generation(&ri),
			    btrfs_super_generation(fs_info->super_copy) + 1);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_root_generation_v2(&ri) >
		     btrfs_super_generation(fs_info->super_copy) + 1)) अणु
		generic_err(leaf, slot,
		"invalid root v2 generation, have %llu expect (0, %llu]",
			    btrfs_root_generation_v2(&ri),
			    btrfs_super_generation(fs_info->super_copy) + 1);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_root_last_snapshot(&ri) >
		     btrfs_super_generation(fs_info->super_copy) + 1)) अणु
		generic_err(leaf, slot,
		"invalid root last_snapshot, have %llu expect (0, %llu]",
			    btrfs_root_last_snapshot(&ri),
			    btrfs_super_generation(fs_info->super_copy) + 1);
		वापस -EUCLEAN;
	पूर्ण

	/* Alignment and level check */
	अगर (unlikely(!IS_ALIGNED(btrfs_root_bytenr(&ri), fs_info->sectorsize))) अणु
		generic_err(leaf, slot,
		"invalid root bytenr, have %llu expect to be aligned to %u",
			    btrfs_root_bytenr(&ri), fs_info->sectorsize);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_root_level(&ri) >= BTRFS_MAX_LEVEL)) अणु
		generic_err(leaf, slot,
			    "invalid root level, have %u expect [0, %u]",
			    btrfs_root_level(&ri), BTRFS_MAX_LEVEL - 1);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(btrfs_root_drop_level(&ri) >= BTRFS_MAX_LEVEL)) अणु
		generic_err(leaf, slot,
			    "invalid root level, have %u expect [0, %u]",
			    btrfs_root_drop_level(&ri), BTRFS_MAX_LEVEL - 1);
		वापस -EUCLEAN;
	पूर्ण

	/* Flags check */
	अगर (unlikely(btrfs_root_flags(&ri) & ~valid_root_flags)) अणु
		generic_err(leaf, slot,
			    "invalid root flags, have 0x%llx expect mask 0x%llx",
			    btrfs_root_flags(&ri), valid_root_flags);
		वापस -EUCLEAN;
	पूर्ण
	वापस 0;
पूर्ण

__म_लिखो(3,4)
__cold
अटल व्योम extent_err(स्थिर काष्ठा extent_buffer *eb, पूर्णांक slot,
		       स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा btrfs_key key;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	u64 bytenr;
	u64 len;

	btrfs_item_key_to_cpu(eb, &key, slot);
	bytenr = key.objectid;
	अगर (key.type == BTRFS_METADATA_ITEM_KEY ||
	    key.type == BTRFS_TREE_BLOCK_REF_KEY ||
	    key.type == BTRFS_SHARED_BLOCK_REF_KEY)
		len = eb->fs_info->nodesize;
	अन्यथा
		len = key.offset;
	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	btrfs_crit(eb->fs_info,
	"corrupt %s: block=%llu slot=%d extent bytenr=%llu len=%llu %pV",
		btrfs_header_level(eb) == 0 ? "leaf" : "node",
		eb->start, slot, bytenr, len, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक check_extent_item(काष्ठा extent_buffer *leaf,
			     काष्ठा btrfs_key *key, पूर्णांक slot)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा btrfs_extent_item *ei;
	bool is_tree_block = false;
	अचिन्हित दीर्घ ptr;	/* Current poपूर्णांकer inside अंतरभूत refs */
	अचिन्हित दीर्घ end;	/* Extent item end */
	स्थिर u32 item_size = btrfs_item_size_nr(leaf, slot);
	u64 flags;
	u64 generation;
	u64 total_refs;		/* Total refs in btrfs_extent_item */
	u64 अंतरभूत_refs = 0;	/* found total अंतरभूत refs */

	अगर (unlikely(key->type == BTRFS_METADATA_ITEM_KEY &&
		     !btrfs_fs_incompat(fs_info, SKINNY_METADATA))) अणु
		generic_err(leaf, slot,
"invalid key type, METADATA_ITEM type invalid when SKINNY_METADATA feature disabled");
		वापस -EUCLEAN;
	पूर्ण
	/* key->objectid is the bytenr क्रम both key types */
	अगर (unlikely(!IS_ALIGNED(key->objectid, fs_info->sectorsize))) अणु
		generic_err(leaf, slot,
		"invalid key objectid, have %llu expect to be aligned to %u",
			   key->objectid, fs_info->sectorsize);
		वापस -EUCLEAN;
	पूर्ण

	/* key->offset is tree level क्रम METADATA_ITEM_KEY */
	अगर (unlikely(key->type == BTRFS_METADATA_ITEM_KEY &&
		     key->offset >= BTRFS_MAX_LEVEL)) अणु
		extent_err(leaf, slot,
			   "invalid tree level, have %llu expect [0, %u]",
			   key->offset, BTRFS_MAX_LEVEL - 1);
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * EXTENT/METADATA_ITEM consists of:
	 * 1) One btrfs_extent_item
	 *    Records the total refs, type and generation of the extent.
	 *
	 * 2) One btrfs_tree_block_info (क्रम EXTENT_ITEM and tree backref only)
	 *    Records the first key and level of the tree block.
	 *
	 * 2) Zero or more btrfs_extent_अंतरभूत_ref(s)
	 *    Each अंतरभूत ref has one btrfs_extent_अंतरभूत_ref shows:
	 *    2.1) The ref type, one of the 4
	 *         TREE_BLOCK_REF	Tree block only
	 *         SHARED_BLOCK_REF	Tree block only
	 *         EXTENT_DATA_REF	Data only
	 *         SHARED_DATA_REF	Data only
	 *    2.2) Ref type specअगरic data
	 *         Either using btrfs_extent_अंतरभूत_ref::offset, or specअगरic
	 *         data काष्ठाure.
	 */
	अगर (unlikely(item_size < माप(*ei))) अणु
		extent_err(leaf, slot,
			   "invalid item size, have %u expect [%zu, %u)",
			   item_size, माप(*ei),
			   BTRFS_LEAF_DATA_SIZE(fs_info));
		वापस -EUCLEAN;
	पूर्ण
	end = item_size + btrfs_item_ptr_offset(leaf, slot);

	/* Checks against extent_item */
	ei = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_extent_item);
	flags = btrfs_extent_flags(leaf, ei);
	total_refs = btrfs_extent_refs(leaf, ei);
	generation = btrfs_extent_generation(leaf, ei);
	अगर (unlikely(generation >
		     btrfs_super_generation(fs_info->super_copy) + 1)) अणु
		extent_err(leaf, slot,
			   "invalid generation, have %llu expect (0, %llu]",
			   generation,
			   btrfs_super_generation(fs_info->super_copy) + 1);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!has_single_bit_set(flags & (BTRFS_EXTENT_FLAG_DATA |
						  BTRFS_EXTENT_FLAG_TREE_BLOCK)))) अणु
		extent_err(leaf, slot,
		"invalid extent flag, have 0x%llx expect 1 bit set in 0x%llx",
			flags, BTRFS_EXTENT_FLAG_DATA |
			BTRFS_EXTENT_FLAG_TREE_BLOCK);
		वापस -EUCLEAN;
	पूर्ण
	is_tree_block = !!(flags & BTRFS_EXTENT_FLAG_TREE_BLOCK);
	अगर (is_tree_block) अणु
		अगर (unlikely(key->type == BTRFS_EXTENT_ITEM_KEY &&
			     key->offset != fs_info->nodesize)) अणु
			extent_err(leaf, slot,
				   "invalid extent length, have %llu expect %u",
				   key->offset, fs_info->nodesize);
			वापस -EUCLEAN;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(key->type != BTRFS_EXTENT_ITEM_KEY)) अणु
			extent_err(leaf, slot,
			"invalid key type, have %u expect %u for data backref",
				   key->type, BTRFS_EXTENT_ITEM_KEY);
			वापस -EUCLEAN;
		पूर्ण
		अगर (unlikely(!IS_ALIGNED(key->offset, fs_info->sectorsize))) अणु
			extent_err(leaf, slot,
			"invalid extent length, have %llu expect aligned to %u",
				   key->offset, fs_info->sectorsize);
			वापस -EUCLEAN;
		पूर्ण
		अगर (unlikely(flags & BTRFS_BLOCK_FLAG_FULL_BACKREF)) अणु
			extent_err(leaf, slot,
			"invalid extent flag, data has full backref set");
			वापस -EUCLEAN;
		पूर्ण
	पूर्ण
	ptr = (अचिन्हित दीर्घ)(काष्ठा btrfs_extent_item *)(ei + 1);

	/* Check the special हाल of btrfs_tree_block_info */
	अगर (is_tree_block && key->type != BTRFS_METADATA_ITEM_KEY) अणु
		काष्ठा btrfs_tree_block_info *info;

		info = (काष्ठा btrfs_tree_block_info *)ptr;
		अगर (unlikely(btrfs_tree_block_level(leaf, info) >= BTRFS_MAX_LEVEL)) अणु
			extent_err(leaf, slot,
			"invalid tree block info level, have %u expect [0, %u]",
				   btrfs_tree_block_level(leaf, info),
				   BTRFS_MAX_LEVEL - 1);
			वापस -EUCLEAN;
		पूर्ण
		ptr = (अचिन्हित दीर्घ)(काष्ठा btrfs_tree_block_info *)(info + 1);
	पूर्ण

	/* Check अंतरभूत refs */
	जबतक (ptr < end) अणु
		काष्ठा btrfs_extent_अंतरभूत_ref *iref;
		काष्ठा btrfs_extent_data_ref *dref;
		काष्ठा btrfs_shared_data_ref *sref;
		u64 dref_offset;
		u64 अंतरभूत_offset;
		u8 अंतरभूत_type;

		अगर (unlikely(ptr + माप(*iref) > end)) अणु
			extent_err(leaf, slot,
"inline ref item overflows extent item, ptr %lu iref size %zu end %lu",
				   ptr, माप(*iref), end);
			वापस -EUCLEAN;
		पूर्ण
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
		अंतरभूत_type = btrfs_extent_अंतरभूत_ref_type(leaf, iref);
		अंतरभूत_offset = btrfs_extent_अंतरभूत_ref_offset(leaf, iref);
		अगर (unlikely(ptr + btrfs_extent_अंतरभूत_ref_size(अंतरभूत_type) > end)) अणु
			extent_err(leaf, slot,
"inline ref item overflows extent item, ptr %lu iref size %u end %lu",
				   ptr, अंतरभूत_type, end);
			वापस -EUCLEAN;
		पूर्ण

		चयन (अंतरभूत_type) अणु
		/* अंतरभूत_offset is subvolid of the owner, no need to check */
		हाल BTRFS_TREE_BLOCK_REF_KEY:
			अंतरभूत_refs++;
			अवरोध;
		/* Contains parent bytenr */
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			अगर (unlikely(!IS_ALIGNED(अंतरभूत_offset,
						 fs_info->sectorsize))) अणु
				extent_err(leaf, slot,
		"invalid tree parent bytenr, have %llu expect aligned to %u",
					   अंतरभूत_offset, fs_info->sectorsize);
				वापस -EUCLEAN;
			पूर्ण
			अंतरभूत_refs++;
			अवरोध;
		/*
		 * Contains owner subvolid, owner key objectid, adjusted offset.
		 * The only obvious corruption can happen in that offset.
		 */
		हाल BTRFS_EXTENT_DATA_REF_KEY:
			dref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
			dref_offset = btrfs_extent_data_ref_offset(leaf, dref);
			अगर (unlikely(!IS_ALIGNED(dref_offset,
						 fs_info->sectorsize))) अणु
				extent_err(leaf, slot,
		"invalid data ref offset, have %llu expect aligned to %u",
					   dref_offset, fs_info->sectorsize);
				वापस -EUCLEAN;
			पूर्ण
			अंतरभूत_refs += btrfs_extent_data_ref_count(leaf, dref);
			अवरोध;
		/* Contains parent bytenr and ref count */
		हाल BTRFS_SHARED_DATA_REF_KEY:
			sref = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
			अगर (unlikely(!IS_ALIGNED(अंतरभूत_offset,
						 fs_info->sectorsize))) अणु
				extent_err(leaf, slot,
		"invalid data parent bytenr, have %llu expect aligned to %u",
					   अंतरभूत_offset, fs_info->sectorsize);
				वापस -EUCLEAN;
			पूर्ण
			अंतरभूत_refs += btrfs_shared_data_ref_count(leaf, sref);
			अवरोध;
		शेष:
			extent_err(leaf, slot, "unknown inline ref type: %u",
				   अंतरभूत_type);
			वापस -EUCLEAN;
		पूर्ण
		ptr += btrfs_extent_अंतरभूत_ref_size(अंतरभूत_type);
	पूर्ण
	/* No padding is allowed */
	अगर (unlikely(ptr != end)) अणु
		extent_err(leaf, slot,
			   "invalid extent item size, padding bytes found");
		वापस -EUCLEAN;
	पूर्ण

	/* Finally, check the अंतरभूत refs against total refs */
	अगर (unlikely(अंतरभूत_refs > total_refs)) अणु
		extent_err(leaf, slot,
			"invalid extent refs, have %llu expect >= inline %llu",
			   total_refs, अंतरभूत_refs);
		वापस -EUCLEAN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_simple_keyed_refs(काष्ठा extent_buffer *leaf,
				   काष्ठा btrfs_key *key, पूर्णांक slot)
अणु
	u32 expect_item_size = 0;

	अगर (key->type == BTRFS_SHARED_DATA_REF_KEY)
		expect_item_size = माप(काष्ठा btrfs_shared_data_ref);

	अगर (unlikely(btrfs_item_size_nr(leaf, slot) != expect_item_size)) अणु
		generic_err(leaf, slot,
		"invalid item size, have %u expect %u for key type %u",
			    btrfs_item_size_nr(leaf, slot),
			    expect_item_size, key->type);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!IS_ALIGNED(key->objectid, leaf->fs_info->sectorsize))) अणु
		generic_err(leaf, slot,
"invalid key objectid for shared block ref, have %llu expect aligned to %u",
			    key->objectid, leaf->fs_info->sectorsize);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(key->type != BTRFS_TREE_BLOCK_REF_KEY &&
		     !IS_ALIGNED(key->offset, leaf->fs_info->sectorsize))) अणु
		extent_err(leaf, slot,
		"invalid tree parent bytenr, have %llu expect aligned to %u",
			   key->offset, leaf->fs_info->sectorsize);
		वापस -EUCLEAN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_extent_data_ref(काष्ठा extent_buffer *leaf,
				 काष्ठा btrfs_key *key, पूर्णांक slot)
अणु
	काष्ठा btrfs_extent_data_ref *dref;
	अचिन्हित दीर्घ ptr = btrfs_item_ptr_offset(leaf, slot);
	स्थिर अचिन्हित दीर्घ end = ptr + btrfs_item_size_nr(leaf, slot);

	अगर (unlikely(btrfs_item_size_nr(leaf, slot) % माप(*dref) != 0)) अणु
		generic_err(leaf, slot,
	"invalid item size, have %u expect aligned to %zu for key type %u",
			    btrfs_item_size_nr(leaf, slot),
			    माप(*dref), key->type);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(!IS_ALIGNED(key->objectid, leaf->fs_info->sectorsize))) अणु
		generic_err(leaf, slot,
"invalid key objectid for shared block ref, have %llu expect aligned to %u",
			    key->objectid, leaf->fs_info->sectorsize);
		वापस -EUCLEAN;
	पूर्ण
	क्रम (; ptr < end; ptr += माप(*dref)) अणु
		u64 offset;

		/*
		 * We cannot check the extent_data_ref hash due to possible
		 * overflow from the leaf due to hash collisions.
		 */
		dref = (काष्ठा btrfs_extent_data_ref *)ptr;
		offset = btrfs_extent_data_ref_offset(leaf, dref);
		अगर (unlikely(!IS_ALIGNED(offset, leaf->fs_info->sectorsize))) अणु
			extent_err(leaf, slot,
	"invalid extent data backref offset, have %llu expect aligned to %u",
				   offset, leaf->fs_info->sectorsize);
			वापस -EUCLEAN;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा inode_ref_err(eb, slot, fmt, args...)			\
	inode_item_err(eb, slot, fmt, ##args)
अटल पूर्णांक check_inode_ref(काष्ठा extent_buffer *leaf,
			   काष्ठा btrfs_key *key, काष्ठा btrfs_key *prev_key,
			   पूर्णांक slot)
अणु
	काष्ठा btrfs_inode_ref *iref;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ end;

	अगर (unlikely(!check_prev_ino(leaf, key, slot, prev_key)))
		वापस -EUCLEAN;
	/* namelen can't be 0, so item_size == माप() is also invalid */
	अगर (unlikely(btrfs_item_size_nr(leaf, slot) <= माप(*iref))) अणु
		inode_ref_err(leaf, slot,
			"invalid item size, have %u expect (%zu, %u)",
			btrfs_item_size_nr(leaf, slot),
			माप(*iref), BTRFS_LEAF_DATA_SIZE(leaf->fs_info));
		वापस -EUCLEAN;
	पूर्ण

	ptr = btrfs_item_ptr_offset(leaf, slot);
	end = ptr + btrfs_item_size_nr(leaf, slot);
	जबतक (ptr < end) अणु
		u16 namelen;

		अगर (unlikely(ptr + माप(iref) > end)) अणु
			inode_ref_err(leaf, slot,
			"inode ref overflow, ptr %lu end %lu inode_ref_size %zu",
				ptr, end, माप(iref));
			वापस -EUCLEAN;
		पूर्ण

		iref = (काष्ठा btrfs_inode_ref *)ptr;
		namelen = btrfs_inode_ref_name_len(leaf, iref);
		अगर (unlikely(ptr + माप(*iref) + namelen > end)) अणु
			inode_ref_err(leaf, slot,
				"inode ref overflow, ptr %lu end %lu namelen %u",
				ptr, end, namelen);
			वापस -EUCLEAN;
		पूर्ण

		/*
		 * NOTE: In theory we should record all found index numbers
		 * to find any duplicated indexes, but that will be too समय
		 * consuming क्रम inodes with too many hard links.
		 */
		ptr += माप(*iref) + namelen;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Common poपूर्णांक to चयन the item-specअगरic validation.
 */
अटल पूर्णांक check_leaf_item(काष्ठा extent_buffer *leaf,
			   काष्ठा btrfs_key *key, पूर्णांक slot,
			   काष्ठा btrfs_key *prev_key)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_chunk *chunk;

	चयन (key->type) अणु
	हाल BTRFS_EXTENT_DATA_KEY:
		ret = check_extent_data_item(leaf, key, slot, prev_key);
		अवरोध;
	हाल BTRFS_EXTENT_CSUM_KEY:
		ret = check_csum_item(leaf, key, slot, prev_key);
		अवरोध;
	हाल BTRFS_सूची_ITEM_KEY:
	हाल BTRFS_सूची_INDEX_KEY:
	हाल BTRFS_XATTR_ITEM_KEY:
		ret = check_dir_item(leaf, key, prev_key, slot);
		अवरोध;
	हाल BTRFS_INODE_REF_KEY:
		ret = check_inode_ref(leaf, key, prev_key, slot);
		अवरोध;
	हाल BTRFS_BLOCK_GROUP_ITEM_KEY:
		ret = check_block_group_item(leaf, key, slot);
		अवरोध;
	हाल BTRFS_CHUNK_ITEM_KEY:
		chunk = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_chunk);
		ret = check_leaf_chunk_item(leaf, chunk, key, slot);
		अवरोध;
	हाल BTRFS_DEV_ITEM_KEY:
		ret = check_dev_item(leaf, key, slot);
		अवरोध;
	हाल BTRFS_INODE_ITEM_KEY:
		ret = check_inode_item(leaf, key, slot);
		अवरोध;
	हाल BTRFS_ROOT_ITEM_KEY:
		ret = check_root_item(leaf, key, slot);
		अवरोध;
	हाल BTRFS_EXTENT_ITEM_KEY:
	हाल BTRFS_METADATA_ITEM_KEY:
		ret = check_extent_item(leaf, key, slot);
		अवरोध;
	हाल BTRFS_TREE_BLOCK_REF_KEY:
	हाल BTRFS_SHARED_DATA_REF_KEY:
	हाल BTRFS_SHARED_BLOCK_REF_KEY:
		ret = check_simple_keyed_refs(leaf, key, slot);
		अवरोध;
	हाल BTRFS_EXTENT_DATA_REF_KEY:
		ret = check_extent_data_ref(leaf, key, slot);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक check_leaf(काष्ठा extent_buffer *leaf, bool check_item_data)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	/* No valid key type is 0, so all key should be larger than this key */
	काष्ठा btrfs_key prev_key = अणु0, 0, 0पूर्ण;
	काष्ठा btrfs_key key;
	u32 nritems = btrfs_header_nritems(leaf);
	पूर्णांक slot;

	अगर (unlikely(btrfs_header_level(leaf) != 0)) अणु
		generic_err(leaf, 0,
			"invalid level for leaf, have %d expect 0",
			btrfs_header_level(leaf));
		वापस -EUCLEAN;
	पूर्ण

	/*
	 * Extent buffers from a relocation tree have a owner field that
	 * corresponds to the subvolume tree they are based on. So just from an
	 * extent buffer alone we can not find out what is the id of the
	 * corresponding subvolume tree, so we can not figure out अगर the extent
	 * buffer corresponds to the root of the relocation tree or not. So
	 * skip this check क्रम relocation trees.
	 */
	अगर (nritems == 0 && !btrfs_header_flag(leaf, BTRFS_HEADER_FLAG_RELOC)) अणु
		u64 owner = btrfs_header_owner(leaf);

		/* These trees must never be empty */
		अगर (unlikely(owner == BTRFS_ROOT_TREE_OBJECTID ||
			     owner == BTRFS_CHUNK_TREE_OBJECTID ||
			     owner == BTRFS_EXTENT_TREE_OBJECTID ||
			     owner == BTRFS_DEV_TREE_OBJECTID ||
			     owner == BTRFS_FS_TREE_OBJECTID ||
			     owner == BTRFS_DATA_RELOC_TREE_OBJECTID)) अणु
			generic_err(leaf, 0,
			"invalid root, root %llu must never be empty",
				    owner);
			वापस -EUCLEAN;
		पूर्ण
		/* Unknown tree */
		अगर (unlikely(owner == 0)) अणु
			generic_err(leaf, 0,
				"invalid owner, root 0 is not defined");
			वापस -EUCLEAN;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (unlikely(nritems == 0))
		वापस 0;

	/*
	 * Check the following things to make sure this is a good leaf, and
	 * leaf users won't need to bother with similar sanity checks:
	 *
	 * 1) key ordering
	 * 2) item offset and size
	 *    No overlap, no hole, all inside the leaf.
	 * 3) item content
	 *    If possible, करो comprehensive sanity check.
	 *    NOTE: All checks must only rely on the item data itself.
	 */
	क्रम (slot = 0; slot < nritems; slot++) अणु
		u32 item_end_expected;
		पूर्णांक ret;

		btrfs_item_key_to_cpu(leaf, &key, slot);

		/* Make sure the keys are in the right order */
		अगर (unlikely(btrfs_comp_cpu_keys(&prev_key, &key) >= 0)) अणु
			generic_err(leaf, slot,
	"bad key order, prev (%llu %u %llu) current (%llu %u %llu)",
				prev_key.objectid, prev_key.type,
				prev_key.offset, key.objectid, key.type,
				key.offset);
			वापस -EUCLEAN;
		पूर्ण

		/*
		 * Make sure the offset and ends are right, remember that the
		 * item data starts at the end of the leaf and grows towards the
		 * front.
		 */
		अगर (slot == 0)
			item_end_expected = BTRFS_LEAF_DATA_SIZE(fs_info);
		अन्यथा
			item_end_expected = btrfs_item_offset_nr(leaf,
								 slot - 1);
		अगर (unlikely(btrfs_item_end_nr(leaf, slot) != item_end_expected)) अणु
			generic_err(leaf, slot,
				"unexpected item end, have %u expect %u",
				btrfs_item_end_nr(leaf, slot),
				item_end_expected);
			वापस -EUCLEAN;
		पूर्ण

		/*
		 * Check to make sure that we करोn't poपूर्णांक outside of the leaf,
		 * just in हाल all the items are consistent to each other, but
		 * all poपूर्णांक outside of the leaf.
		 */
		अगर (unlikely(btrfs_item_end_nr(leaf, slot) >
			     BTRFS_LEAF_DATA_SIZE(fs_info))) अणु
			generic_err(leaf, slot,
			"slot end outside of leaf, have %u expect range [0, %u]",
				btrfs_item_end_nr(leaf, slot),
				BTRFS_LEAF_DATA_SIZE(fs_info));
			वापस -EUCLEAN;
		पूर्ण

		/* Also check अगर the item poपूर्णांकer overlaps with btrfs item. */
		अगर (unlikely(btrfs_item_ptr_offset(leaf, slot) <
			     btrfs_item_nr_offset(slot) + माप(काष्ठा btrfs_item))) अणु
			generic_err(leaf, slot,
		"slot overlaps with its data, item end %lu data start %lu",
				btrfs_item_nr_offset(slot) +
				माप(काष्ठा btrfs_item),
				btrfs_item_ptr_offset(leaf, slot));
			वापस -EUCLEAN;
		पूर्ण

		अगर (check_item_data) अणु
			/*
			 * Check अगर the item size and content meet other
			 * criteria
			 */
			ret = check_leaf_item(leaf, &key, slot, &prev_key);
			अगर (unlikely(ret < 0))
				वापस ret;
		पूर्ण

		prev_key.objectid = key.objectid;
		prev_key.type = key.type;
		prev_key.offset = key.offset;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btrfs_check_leaf_full(काष्ठा extent_buffer *leaf)
अणु
	वापस check_leaf(leaf, true);
पूर्ण
ALLOW_ERROR_INJECTION(btrfs_check_leaf_full, ERRNO);

पूर्णांक btrfs_check_leaf_relaxed(काष्ठा extent_buffer *leaf)
अणु
	वापस check_leaf(leaf, false);
पूर्ण

पूर्णांक btrfs_check_node(काष्ठा extent_buffer *node)
अणु
	काष्ठा btrfs_fs_info *fs_info = node->fs_info;
	अचिन्हित दीर्घ nr = btrfs_header_nritems(node);
	काष्ठा btrfs_key key, next_key;
	पूर्णांक slot;
	पूर्णांक level = btrfs_header_level(node);
	u64 bytenr;
	पूर्णांक ret = 0;

	अगर (unlikely(level <= 0 || level >= BTRFS_MAX_LEVEL)) अणु
		generic_err(node, 0,
			"invalid level for node, have %d expect [1, %d]",
			level, BTRFS_MAX_LEVEL - 1);
		वापस -EUCLEAN;
	पूर्ण
	अगर (unlikely(nr == 0 || nr > BTRFS_NODEPTRS_PER_BLOCK(fs_info))) अणु
		btrfs_crit(fs_info,
"corrupt node: root=%llu block=%llu, nritems too %s, have %lu expect range [1,%u]",
			   btrfs_header_owner(node), node->start,
			   nr == 0 ? "small" : "large", nr,
			   BTRFS_NODEPTRS_PER_BLOCK(fs_info));
		वापस -EUCLEAN;
	पूर्ण

	क्रम (slot = 0; slot < nr - 1; slot++) अणु
		bytenr = btrfs_node_blockptr(node, slot);
		btrfs_node_key_to_cpu(node, &key, slot);
		btrfs_node_key_to_cpu(node, &next_key, slot + 1);

		अगर (unlikely(!bytenr)) अणु
			generic_err(node, slot,
				"invalid NULL node pointer");
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
		अगर (unlikely(!IS_ALIGNED(bytenr, fs_info->sectorsize))) अणु
			generic_err(node, slot,
			"unaligned pointer, have %llu should be aligned to %u",
				bytenr, fs_info->sectorsize);
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण

		अगर (unlikely(btrfs_comp_cpu_keys(&key, &next_key) >= 0)) अणु
			generic_err(node, slot,
	"bad key order, current (%llu %u %llu) next (%llu %u %llu)",
				key.objectid, key.type, key.offset,
				next_key.objectid, next_key.type,
				next_key.offset);
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण
ALLOW_ERROR_INJECTION(btrfs_check_node, ERRNO);
