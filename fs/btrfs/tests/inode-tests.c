<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Fusion IO.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../btrfs_inode.h"
#समावेश "../disk-io.h"
#समावेश "../extent_io.h"
#समावेश "../volumes.h"
#समावेश "../compression.h"

अटल व्योम insert_extent(काष्ठा btrfs_root *root, u64 start, u64 len,
			  u64 ram_bytes, u64 offset, u64 disk_bytenr,
			  u64 disk_len, u32 type, u8 compression, पूर्णांक slot)
अणु
	काष्ठा btrfs_path path;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा extent_buffer *leaf = root->node;
	काष्ठा btrfs_key key;
	u32 value_len = माप(काष्ठा btrfs_file_extent_item);

	अगर (type == BTRFS_खाता_EXTENT_INLINE)
		value_len += len;
	स_रखो(&path, 0, माप(path));

	path.nodes[0] = leaf;
	path.slots[0] = slot;

	key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = start;

	setup_items_क्रम_insert(root, &path, &key, &value_len, 1);
	fi = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);
	btrfs_set_file_extent_generation(leaf, fi, 1);
	btrfs_set_file_extent_type(leaf, fi, type);
	btrfs_set_file_extent_disk_bytenr(leaf, fi, disk_bytenr);
	btrfs_set_file_extent_disk_num_bytes(leaf, fi, disk_len);
	btrfs_set_file_extent_offset(leaf, fi, offset);
	btrfs_set_file_extent_num_bytes(leaf, fi, len);
	btrfs_set_file_extent_ram_bytes(leaf, fi, ram_bytes);
	btrfs_set_file_extent_compression(leaf, fi, compression);
	btrfs_set_file_extent_encryption(leaf, fi, 0);
	btrfs_set_file_extent_other_encoding(leaf, fi, 0);
पूर्ण

अटल व्योम insert_inode_item_key(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_path path;
	काष्ठा extent_buffer *leaf = root->node;
	काष्ठा btrfs_key key;
	u32 value_len = 0;

	स_रखो(&path, 0, माप(path));

	path.nodes[0] = leaf;
	path.slots[0] = 0;

	key.objectid = BTRFS_INODE_ITEM_KEY;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	setup_items_क्रम_insert(root, &path, &key, &value_len, 1);
पूर्ण

/*
 * Build the most complicated map of extents the earth has ever seen.  We want
 * this so we can test all of the corner हालs of btrfs_get_extent.  Here is a
 * diagram of how the extents will look though this may not be possible we still
 * want to make sure everything acts normally (the last number is not inclusive)
 *
 * [0 - 5][5 -  6][     6 - 4096     ][ 4096 - 4100][4100 - 8195][8195 - 12291]
 * [hole ][अंतरभूत][hole but no extent][  hole   ][   regular ][regular1 split]
 *
 * [12291 - 16387][16387 - 24579][24579 - 28675][ 28675 - 32771][32771 - 36867 ]
 * [    hole    ][regular1 split][   pपुनः_स्मृति ][   pपुनः_स्मृति1  ][pपुनः_स्मृति1 written]
 *
 * [36867 - 45059][45059 - 53251][53251 - 57347][57347 - 61443][61443- 69635]
 * [  pपुनः_स्मृति1  ][ compressed  ][ compressed1 ][    regular  ][ compressed1]
 *
 * [69635-73731][   73731 - 86019   ][86019-90115]
 * [  regular  ][ hole but no extent][  regular  ]
 */
अटल व्योम setup_file_extents(काष्ठा btrfs_root *root, u32 sectorsize)
अणु
	पूर्णांक slot = 0;
	u64 disk_bytenr = SZ_1M;
	u64 offset = 0;

	/* First we want a hole */
	insert_extent(root, offset, 5, 5, 0, 0, 0, BTRFS_खाता_EXTENT_REG, 0,
		      slot);
	slot++;
	offset += 5;

	/*
	 * Now we want an अंतरभूत extent, I करोn't think this is possible but hey
	 * why not?  Also keep in mind अगर we have an अंतरभूत extent it counts as
	 * the whole first page.  If we were to expand it we would have to cow
	 * and we wouldn't have an अंतरभूत extent anymore.
	 */
	insert_extent(root, offset, 1, 1, 0, 0, 0, BTRFS_खाता_EXTENT_INLINE, 0,
		      slot);
	slot++;
	offset = sectorsize;

	/* Now another hole */
	insert_extent(root, offset, 4, 4, 0, 0, 0, BTRFS_खाता_EXTENT_REG, 0,
		      slot);
	slot++;
	offset += 4;

	/* Now क्रम a regular extent */
	insert_extent(root, offset, sectorsize - 1, sectorsize - 1, 0,
		      disk_bytenr, sectorsize, BTRFS_खाता_EXTENT_REG, 0, slot);
	slot++;
	disk_bytenr += sectorsize;
	offset += sectorsize - 1;

	/*
	 * Now क्रम 3 extents that were split from a hole punch so we test
	 * offsets properly.
	 */
	insert_extent(root, offset, sectorsize, 4 * sectorsize, 0, disk_bytenr,
		      4 * sectorsize, BTRFS_खाता_EXTENT_REG, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, sectorsize, sectorsize, 0, 0, 0,
		      BTRFS_खाता_EXTENT_REG, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, 2 * sectorsize, 4 * sectorsize,
		      2 * sectorsize, disk_bytenr, 4 * sectorsize,
		      BTRFS_खाता_EXTENT_REG, 0, slot);
	slot++;
	offset += 2 * sectorsize;
	disk_bytenr += 4 * sectorsize;

	/* Now क्रम a unwritten pपुनः_स्मृति extent */
	insert_extent(root, offset, sectorsize, sectorsize, 0, disk_bytenr,
		sectorsize, BTRFS_खाता_EXTENT_PREALLOC, 0, slot);
	slot++;
	offset += sectorsize;

	/*
	 * We want to jack up disk_bytenr a little more so the em stuff करोesn't
	 * merge our records.
	 */
	disk_bytenr += 2 * sectorsize;

	/*
	 * Now क्रम a partially written pपुनः_स्मृति extent, basically the same as
	 * the hole punch example above.  Ram_bytes never changes when you mark
	 * extents written btw.
	 */
	insert_extent(root, offset, sectorsize, 4 * sectorsize, 0, disk_bytenr,
		      4 * sectorsize, BTRFS_खाता_EXTENT_PREALLOC, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, sectorsize, 4 * sectorsize, sectorsize,
		      disk_bytenr, 4 * sectorsize, BTRFS_खाता_EXTENT_REG, 0,
		      slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, 2 * sectorsize, 4 * sectorsize,
		      2 * sectorsize, disk_bytenr, 4 * sectorsize,
		      BTRFS_खाता_EXTENT_PREALLOC, 0, slot);
	slot++;
	offset += 2 * sectorsize;
	disk_bytenr += 4 * sectorsize;

	/* Now a normal compressed extent */
	insert_extent(root, offset, 2 * sectorsize, 2 * sectorsize, 0,
		      disk_bytenr, sectorsize, BTRFS_खाता_EXTENT_REG,
		      BTRFS_COMPRESS_ZLIB, slot);
	slot++;
	offset += 2 * sectorsize;
	/* No merges */
	disk_bytenr += 2 * sectorsize;

	/* Now a split compressed extent */
	insert_extent(root, offset, sectorsize, 4 * sectorsize, 0, disk_bytenr,
		      sectorsize, BTRFS_खाता_EXTENT_REG,
		      BTRFS_COMPRESS_ZLIB, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, sectorsize, sectorsize, 0,
		      disk_bytenr + sectorsize, sectorsize,
		      BTRFS_खाता_EXTENT_REG, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, 2 * sectorsize, 4 * sectorsize,
		      2 * sectorsize, disk_bytenr, sectorsize,
		      BTRFS_खाता_EXTENT_REG, BTRFS_COMPRESS_ZLIB, slot);
	slot++;
	offset += 2 * sectorsize;
	disk_bytenr += 2 * sectorsize;

	/* Now extents that have a hole but no hole extent */
	insert_extent(root, offset, sectorsize, sectorsize, 0, disk_bytenr,
		      sectorsize, BTRFS_खाता_EXTENT_REG, 0, slot);
	slot++;
	offset += 4 * sectorsize;
	disk_bytenr += sectorsize;
	insert_extent(root, offset, sectorsize, sectorsize, 0, disk_bytenr,
		      sectorsize, BTRFS_खाता_EXTENT_REG, 0, slot);
पूर्ण

अटल अचिन्हित दीर्घ pपुनः_स्मृति_only = 0;
अटल अचिन्हित दीर्घ compressed_only = 0;
अटल अचिन्हित दीर्घ vacancy_only = 0;

अटल noअंतरभूत पूर्णांक test_btrfs_get_extent(u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_fs_info *fs_info = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा btrfs_root *root = शून्य;
	काष्ठा extent_map *em = शून्य;
	u64 orig_start;
	u64 disk_bytenr;
	u64 offset;
	पूर्णांक ret = -ENOMEM;

	test_msg("running btrfs_get_extent tests");

	inode = btrfs_new_test_inode();
	अगर (!inode) अणु
		test_std_err(TEST_ALLOC_INODE);
		वापस ret;
	पूर्ण

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		जाओ out;
	पूर्ण

	root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		जाओ out;
	पूर्ण

	root->node = alloc_dummy_extent_buffer(fs_info, nodesize);
	अगर (!root->node) अणु
		test_std_err(TEST_ALLOC_ROOT);
		जाओ out;
	पूर्ण

	btrfs_set_header_nritems(root->node, 0);
	btrfs_set_header_level(root->node, 0);
	ret = -EINVAL;

	/* First with no extents */
	BTRFS_I(inode)->root = root;
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, 0, sectorsize);
	अगर (IS_ERR(em)) अणु
		em = शून्य;
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != EXTENT_MAP_HOLE) अणु
		test_err("expected a hole, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);
	btrfs_drop_extent_cache(BTRFS_I(inode), 0, (u64)-1, 0);

	/*
	 * All of the magic numbers are based on the mapping setup in
	 * setup_file_extents, so अगर you change anything there you need to
	 * update the comment and update the expected values below.
	 */
	setup_file_extents(root, sectorsize);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, 0, (u64)-1);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != EXTENT_MAP_HOLE) अणु
		test_err("expected a hole, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != 0 || em->len != 5) अणु
		test_err(
		"unexpected extent wanted start 0 len 5, got start %llu len %llu",
			em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != EXTENT_MAP_INLINE) अणु
		test_err("expected an inline, got %llu", em->block_start);
		जाओ out;
	पूर्ण

	अगर (em->start != offset || em->len != (sectorsize - 5)) अणु
		test_err(
	"unexpected extent wanted start %llu len 1, got start %llu len %llu",
			offset, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	/*
	 * We करोn't test anything else for inline since it doesn't get set
	 * unless we have a page क्रम it to ग_लिखो पूर्णांकo.  Maybe we should change
	 * this?
	 */
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != EXTENT_MAP_HOLE) अणु
		test_err("expected a hole, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != 4) अणु
		test_err(
	"unexpected extent wanted start %llu len 4, got start %llu len %llu",
			offset, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	/* Regular extent */
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize - 1) अणु
		test_err(
	"unexpected extent wanted start %llu len 4095, got start %llu len %llu",
			offset, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	/* The next 3 are split extents */
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
		"unexpected extent start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	disk_bytenr = em->block_start;
	orig_start = em->start;
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != EXTENT_MAP_HOLE) अणु
		test_err("expected a hole, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != 2 * sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, 2 * sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != orig_start) अणु
		test_err("wrong orig offset, want %llu, have %llu",
			 orig_start, em->orig_start);
		जाओ out;
	पूर्ण
	disk_bytenr += (em->start - orig_start);
	अगर (em->block_start != disk_bytenr) अणु
		test_err("wrong block start, want %llu, have %llu",
			 disk_bytenr, em->block_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	/* Pपुनः_स्मृति extent */
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != pपुनः_स्मृति_only) अणु
		test_err("unexpected flags set, want %lu have %lu",
			 pपुनः_स्मृति_only, em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	/* The next 3 are a half written pपुनः_स्मृति extent */
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != pपुनः_स्मृति_only) अणु
		test_err("unexpected flags set, want %lu have %lu",
			 pपुनः_स्मृति_only, em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	disk_bytenr = em->block_start;
	orig_start = em->start;
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_HOLE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != orig_start) अणु
		test_err("unexpected orig offset, wanted %llu, have %llu",
			 orig_start, em->orig_start);
		जाओ out;
	पूर्ण
	अगर (em->block_start != (disk_bytenr + (em->start - em->orig_start))) अणु
		test_err("unexpected block start, wanted %llu, have %llu",
			 disk_bytenr + (em->start - em->orig_start),
			 em->block_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != 2 * sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, 2 * sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != pपुनः_स्मृति_only) अणु
		test_err("unexpected flags set, want %lu have %lu",
			 pपुनः_स्मृति_only, em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != orig_start) अणु
		test_err("wrong orig offset, want %llu, have %llu", orig_start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	अगर (em->block_start != (disk_bytenr + (em->start - em->orig_start))) अणु
		test_err("unexpected block start, wanted %llu, have %llu",
			 disk_bytenr + (em->start - em->orig_start),
			 em->block_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	/* Now क्रम the compressed extent */
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != 2 * sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, 2 * sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != compressed_only) अणु
		test_err("unexpected flags set, want %lu have %lu",
			 compressed_only, em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu",
			 em->start, em->orig_start);
		जाओ out;
	पूर्ण
	अगर (em->compress_type != BTRFS_COMPRESS_ZLIB) अणु
		test_err("unexpected compress type, wanted %d, got %d",
			 BTRFS_COMPRESS_ZLIB, em->compress_type);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	/* Split compressed extent */
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != compressed_only) अणु
		test_err("unexpected flags set, want %lu have %lu",
			 compressed_only, em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu",
			 em->start, em->orig_start);
		जाओ out;
	पूर्ण
	अगर (em->compress_type != BTRFS_COMPRESS_ZLIB) अणु
		test_err("unexpected compress type, wanted %d, got %d",
			 BTRFS_COMPRESS_ZLIB, em->compress_type);
		जाओ out;
	पूर्ण
	disk_bytenr = em->block_start;
	orig_start = em->start;
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != disk_bytenr) अणु
		test_err("block start does not match, want %llu got %llu",
			 disk_bytenr, em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != 2 * sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, 2 * sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != compressed_only) अणु
		test_err("unexpected flags set, want %lu have %lu",
			 compressed_only, em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != orig_start) अणु
		test_err("wrong orig offset, want %llu, have %llu",
			 em->start, orig_start);
		जाओ out;
	पूर्ण
	अगर (em->compress_type != BTRFS_COMPRESS_ZLIB) अणु
		test_err("unexpected compress type, wanted %d, got %d",
			 BTRFS_COMPRESS_ZLIB, em->compress_type);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	/* A hole between regular extents but no hole extent */
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset + 6, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, SZ_4M);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != EXTENT_MAP_HOLE) अणु
		test_err("expected a hole extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	/*
	 * Currently we just वापस a length that we requested rather than the
	 * length of the actual hole, अगर this changes we'll have to change this
	 * test.
	 */
	अगर (em->start != offset || em->len != 3 * sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, 3 * sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != vacancy_only) अणु
		test_err("unexpected flags set, want %lu have %lu",
			 vacancy_only, em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	offset = em->start + em->len;
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != offset || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %llu len %u, got start %llu len %llu",
			offset, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, want 0 have %lu", em->flags);
		जाओ out;
	पूर्ण
	अगर (em->orig_start != em->start) अणु
		test_err("wrong orig offset, want %llu, have %llu", em->start,
			 em->orig_start);
		जाओ out;
	पूर्ण
	ret = 0;
out:
	अगर (!IS_ERR(em))
		मुक्त_extent_map(em);
	iput(inode);
	btrfs_मुक्त_dummy_root(root);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण

अटल पूर्णांक test_hole_first(u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_fs_info *fs_info = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा btrfs_root *root = शून्य;
	काष्ठा extent_map *em = शून्य;
	पूर्णांक ret = -ENOMEM;

	test_msg("running hole first btrfs_get_extent test");

	inode = btrfs_new_test_inode();
	अगर (!inode) अणु
		test_std_err(TEST_ALLOC_INODE);
		वापस ret;
	पूर्ण

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		जाओ out;
	पूर्ण

	root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		जाओ out;
	पूर्ण

	root->node = alloc_dummy_extent_buffer(fs_info, nodesize);
	अगर (!root->node) अणु
		test_std_err(TEST_ALLOC_ROOT);
		जाओ out;
	पूर्ण

	btrfs_set_header_nritems(root->node, 0);
	btrfs_set_header_level(root->node, 0);
	BTRFS_I(inode)->root = root;
	ret = -EINVAL;

	/*
	 * Need a blank inode item here just so we करोn't confuse
	 * btrfs_get_extent.
	 */
	insert_inode_item_key(root);
	insert_extent(root, sectorsize, sectorsize, sectorsize, 0, sectorsize,
		      sectorsize, BTRFS_खाता_EXTENT_REG, 0, 1);
	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, 0, 2 * sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != EXTENT_MAP_HOLE) अणु
		test_err("expected a hole, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != 0 || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start 0 len %u, got start %llu len %llu",
			sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != vacancy_only) अणु
		test_err("wrong flags, wanted %lu, have %lu", vacancy_only,
			 em->flags);
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, sectorsize, 2 * sectorsize);
	अगर (IS_ERR(em)) अणु
		test_err("got an error when we shouldn't have");
		जाओ out;
	पूर्ण
	अगर (em->block_start != sectorsize) अणु
		test_err("expected a real extent, got %llu", em->block_start);
		जाओ out;
	पूर्ण
	अगर (em->start != sectorsize || em->len != sectorsize) अणु
		test_err(
	"unexpected extent wanted start %u len %u, got start %llu len %llu",
			sectorsize, sectorsize, em->start, em->len);
		जाओ out;
	पूर्ण
	अगर (em->flags != 0) अणु
		test_err("unexpected flags set, wanted 0 got %lu",
			 em->flags);
		जाओ out;
	पूर्ण
	ret = 0;
out:
	अगर (!IS_ERR(em))
		मुक्त_extent_map(em);
	iput(inode);
	btrfs_मुक्त_dummy_root(root);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण

अटल पूर्णांक test_extent_accounting(u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_fs_info *fs_info = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा btrfs_root *root = शून्य;
	पूर्णांक ret = -ENOMEM;

	test_msg("running outstanding_extents tests");

	inode = btrfs_new_test_inode();
	अगर (!inode) अणु
		test_std_err(TEST_ALLOC_INODE);
		वापस ret;
	पूर्ण

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		जाओ out;
	पूर्ण

	root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		जाओ out;
	पूर्ण

	BTRFS_I(inode)->root = root;

	/* [BTRFS_MAX_EXTENT_SIZE] */
	ret = btrfs_set_extent_delalloc(BTRFS_I(inode), 0,
					BTRFS_MAX_EXTENT_SIZE - 1, 0, शून्य);
	अगर (ret) अणु
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 1) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 1, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/* [BTRFS_MAX_EXTENT_SIZE][sectorsize] */
	ret = btrfs_set_extent_delalloc(BTRFS_I(inode), BTRFS_MAX_EXTENT_SIZE,
					BTRFS_MAX_EXTENT_SIZE + sectorsize - 1,
					0, शून्य);
	अगर (ret) अणु
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 2) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 2, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/* [BTRFS_MAX_EXTENT_SIZE/2][sectorsize HOLE][the rest] */
	ret = clear_extent_bit(&BTRFS_I(inode)->io_tree,
			       BTRFS_MAX_EXTENT_SIZE >> 1,
			       (BTRFS_MAX_EXTENT_SIZE >> 1) + sectorsize - 1,
			       EXTENT_DELALLOC | EXTENT_DELALLOC_NEW |
			       EXTENT_UPTODATE, 0, 0, शून्य);
	अगर (ret) अणु
		test_err("clear_extent_bit returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 2) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 2, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/* [BTRFS_MAX_EXTENT_SIZE][sectorsize] */
	ret = btrfs_set_extent_delalloc(BTRFS_I(inode), BTRFS_MAX_EXTENT_SIZE >> 1,
					(BTRFS_MAX_EXTENT_SIZE >> 1)
					+ sectorsize - 1,
					0, शून्य);
	अगर (ret) अणु
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 2) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 2, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/*
	 * [BTRFS_MAX_EXTENT_SIZE+sectorsize][sectorsize HOLE][BTRFS_MAX_EXTENT_SIZE+sectorsize]
	 */
	ret = btrfs_set_extent_delalloc(BTRFS_I(inode),
			BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize,
			(BTRFS_MAX_EXTENT_SIZE << 1) + 3 * sectorsize - 1,
			0, शून्य);
	अगर (ret) अणु
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 4) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 4, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/*
	* [BTRFS_MAX_EXTENT_SIZE+sectorsize][sectorsize][BTRFS_MAX_EXTENT_SIZE+sectorsize]
	*/
	ret = btrfs_set_extent_delalloc(BTRFS_I(inode),
			BTRFS_MAX_EXTENT_SIZE + sectorsize,
			BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize - 1, 0, शून्य);
	अगर (ret) अणु
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 3) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 3, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/* [BTRFS_MAX_EXTENT_SIZE+4k][4K HOLE][BTRFS_MAX_EXTENT_SIZE+4k] */
	ret = clear_extent_bit(&BTRFS_I(inode)->io_tree,
			       BTRFS_MAX_EXTENT_SIZE + sectorsize,
			       BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize - 1,
			       EXTENT_DELALLOC | EXTENT_DELALLOC_NEW |
			       EXTENT_UPTODATE, 0, 0, शून्य);
	अगर (ret) अणु
		test_err("clear_extent_bit returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 4) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 4, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/*
	 * Refill the hole again just क्रम good measure, because I thought it
	 * might fail and I'd rather satisfy my paranoia at this poपूर्णांक.
	 */
	ret = btrfs_set_extent_delalloc(BTRFS_I(inode),
			BTRFS_MAX_EXTENT_SIZE + sectorsize,
			BTRFS_MAX_EXTENT_SIZE + 2 * sectorsize - 1, 0, शून्य);
	अगर (ret) अणु
		test_err("btrfs_set_extent_delalloc returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents != 3) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 3, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण

	/* Empty */
	ret = clear_extent_bit(&BTRFS_I(inode)->io_tree, 0, (u64)-1,
			       EXTENT_DELALLOC | EXTENT_DELALLOC_NEW |
			       EXTENT_UPTODATE, 0, 0, शून्य);
	अगर (ret) अणु
		test_err("clear_extent_bit returned %d", ret);
		जाओ out;
	पूर्ण
	अगर (BTRFS_I(inode)->outstanding_extents) अणु
		ret = -EINVAL;
		test_err("miscount, wanted 0, got %u",
			 BTRFS_I(inode)->outstanding_extents);
		जाओ out;
	पूर्ण
	ret = 0;
out:
	अगर (ret)
		clear_extent_bit(&BTRFS_I(inode)->io_tree, 0, (u64)-1,
				 EXTENT_DELALLOC | EXTENT_DELALLOC_NEW |
				 EXTENT_UPTODATE, 0, 0, शून्य);
	iput(inode);
	btrfs_मुक्त_dummy_root(root);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण

पूर्णांक btrfs_test_inodes(u32 sectorsize, u32 nodesize)
अणु
	पूर्णांक ret;

	test_msg("running inode tests");

	set_bit(EXTENT_FLAG_COMPRESSED, &compressed_only);
	set_bit(EXTENT_FLAG_PREALLOC, &pपुनः_स्मृति_only);

	ret = test_btrfs_get_extent(sectorsize, nodesize);
	अगर (ret)
		वापस ret;
	ret = test_hole_first(sectorsize, nodesize);
	अगर (ret)
		वापस ret;
	वापस test_extent_accounting(sectorsize, nodesize);
पूर्ण
