<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/migrate.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/uuid.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/sched/mm.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/hash.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "btrfs_inode.h"
#समावेश "volumes.h"
#समावेश "print-tree.h"
#समावेश "locking.h"
#समावेश "tree-log.h"
#समावेश "free-space-cache.h"
#समावेश "free-space-tree.h"
#समावेश "check-integrity.h"
#समावेश "rcu-string.h"
#समावेश "dev-replace.h"
#समावेश "raid56.h"
#समावेश "sysfs.h"
#समावेश "qgroup.h"
#समावेश "compression.h"
#समावेश "tree-checker.h"
#समावेश "ref-verify.h"
#समावेश "block-group.h"
#समावेश "discard.h"
#समावेश "space-info.h"
#समावेश "zoned.h"
#समावेश "subpage.h"

#घोषणा BTRFS_SUPER_FLAG_SUPP	(BTRFS_HEADER_FLAG_WRITTEN |\
				 BTRFS_HEADER_FLAG_RELOC |\
				 BTRFS_SUPER_FLAG_ERROR |\
				 BTRFS_SUPER_FLAG_SEEDING |\
				 BTRFS_SUPER_FLAG_METADUMP |\
				 BTRFS_SUPER_FLAG_METADUMP_V2)

अटल व्योम end_workqueue_fn(काष्ठा btrfs_work *work);
अटल व्योम btrfs_destroy_ordered_extents(काष्ठा btrfs_root *root);
अटल पूर्णांक btrfs_destroy_delayed_refs(काष्ठा btrfs_transaction *trans,
				      काष्ठा btrfs_fs_info *fs_info);
अटल व्योम btrfs_destroy_delalloc_inodes(काष्ठा btrfs_root *root);
अटल पूर्णांक btrfs_destroy_marked_extents(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा extent_io_tree *dirty_pages,
					पूर्णांक mark);
अटल पूर्णांक btrfs_destroy_pinned_extent(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा extent_io_tree *pinned_extents);
अटल पूर्णांक btrfs_cleanup_transaction(काष्ठा btrfs_fs_info *fs_info);
अटल व्योम btrfs_error_commit_super(काष्ठा btrfs_fs_info *fs_info);

/*
 * btrfs_end_io_wq काष्ठाs are used to करो processing in task context when an IO
 * is complete.  This is used during पढ़ोs to verअगरy checksums, and it is used
 * by ग_लिखोs to insert metadata क्रम new file extents after IO is complete.
 */
काष्ठा btrfs_end_io_wq अणु
	काष्ठा bio *bio;
	bio_end_io_t *end_io;
	व्योम *निजी;
	काष्ठा btrfs_fs_info *info;
	blk_status_t status;
	क्रमागत btrfs_wq_endio_type metadata;
	काष्ठा btrfs_work work;
पूर्ण;

अटल काष्ठा kmem_cache *btrfs_end_io_wq_cache;

पूर्णांक __init btrfs_end_io_wq_init(व्योम)
अणु
	btrfs_end_io_wq_cache = kmem_cache_create("btrfs_end_io_wq",
					माप(काष्ठा btrfs_end_io_wq),
					0,
					SLAB_MEM_SPREAD,
					शून्य);
	अगर (!btrfs_end_io_wq_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम __cold btrfs_end_io_wq_निकास(व्योम)
अणु
	kmem_cache_destroy(btrfs_end_io_wq_cache);
पूर्ण

अटल व्योम btrfs_मुक्त_csum_hash(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (fs_info->csum_shash)
		crypto_मुक्त_shash(fs_info->csum_shash);
पूर्ण

/*
 * async submit bios are used to offload expensive checksumming
 * onto the worker thपढ़ोs.  They checksum file and metadata bios
 * just beक्रमe they are sent करोwn the IO stack.
 */
काष्ठा async_submit_bio अणु
	काष्ठा inode *inode;
	काष्ठा bio *bio;
	extent_submit_bio_start_t *submit_bio_start;
	पूर्णांक mirror_num;

	/* Optional parameter क्रम submit_bio_start used by direct io */
	u64 dio_file_offset;
	काष्ठा btrfs_work work;
	blk_status_t status;
पूर्ण;

/*
 * Lockdep class keys क्रम extent_buffer->lock's in this root.  For a given
 * eb, the lockdep key is determined by the btrfs_root it beदीर्घs to and
 * the level the eb occupies in the tree.
 *
 * Dअगरferent roots are used क्रम dअगरferent purposes and may nest inside each
 * other and they require separate keysets.  As lockdep keys should be
 * अटल, assign keysets according to the purpose of the root as indicated
 * by btrfs_root->root_key.objectid.  This ensures that all special purpose
 * roots have separate keysets.
 *
 * Lock-nesting across peer nodes is always करोne with the immediate parent
 * node locked thus preventing deadlock.  As lockdep करोesn't know this, use
 * subclass to aव्योम triggering lockdep warning in such हालs.
 *
 * The key is set by the पढ़ोpage_end_io_hook after the buffer has passed
 * csum validation but beक्रमe the pages are unlocked.  It is also set by
 * btrfs_init_new_buffer on freshly allocated blocks.
 *
 * We also add a check to make sure the highest level of the tree is the
 * same as our lockdep setup here.  If BTRFS_MAX_LEVEL changes, this code
 * needs update as well.
 */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# अगर BTRFS_MAX_LEVEL != 8
#  error
# endअगर

#घोषणा DEFINE_LEVEL(stem, level)					\
	.names[level] = "btrfs-" stem "-0" #level,

#घोषणा DEFINE_NAME(stem)						\
	DEFINE_LEVEL(stem, 0)						\
	DEFINE_LEVEL(stem, 1)						\
	DEFINE_LEVEL(stem, 2)						\
	DEFINE_LEVEL(stem, 3)						\
	DEFINE_LEVEL(stem, 4)						\
	DEFINE_LEVEL(stem, 5)						\
	DEFINE_LEVEL(stem, 6)						\
	DEFINE_LEVEL(stem, 7)

अटल काष्ठा btrfs_lockdep_keyset अणु
	u64			id;		/* root objectid */
	/* Longest entry: btrfs-मुक्त-space-00 */
	अक्षर			names[BTRFS_MAX_LEVEL][20];
	काष्ठा lock_class_key	keys[BTRFS_MAX_LEVEL];
पूर्ण btrfs_lockdep_keysets[] = अणु
	अणु .id = BTRFS_ROOT_TREE_OBJECTID,	DEFINE_NAME("root")	पूर्ण,
	अणु .id = BTRFS_EXTENT_TREE_OBJECTID,	DEFINE_NAME("extent")	पूर्ण,
	अणु .id = BTRFS_CHUNK_TREE_OBJECTID,	DEFINE_NAME("chunk")	पूर्ण,
	अणु .id = BTRFS_DEV_TREE_OBJECTID,	DEFINE_NAME("dev")	पूर्ण,
	अणु .id = BTRFS_CSUM_TREE_OBJECTID,	DEFINE_NAME("csum")	पूर्ण,
	अणु .id = BTRFS_QUOTA_TREE_OBJECTID,	DEFINE_NAME("quota")	पूर्ण,
	अणु .id = BTRFS_TREE_LOG_OBJECTID,	DEFINE_NAME("log")	पूर्ण,
	अणु .id = BTRFS_TREE_RELOC_OBJECTID,	DEFINE_NAME("treloc")	पूर्ण,
	अणु .id = BTRFS_DATA_RELOC_TREE_OBJECTID,	DEFINE_NAME("dreloc")	पूर्ण,
	अणु .id = BTRFS_UUID_TREE_OBJECTID,	DEFINE_NAME("uuid")	पूर्ण,
	अणु .id = BTRFS_FREE_SPACE_TREE_OBJECTID,	DEFINE_NAME("free-space") पूर्ण,
	अणु .id = 0,				DEFINE_NAME("tree")	पूर्ण,
पूर्ण;

#अघोषित DEFINE_LEVEL
#अघोषित DEFINE_NAME

व्योम btrfs_set_buffer_lockdep_class(u64 objectid, काष्ठा extent_buffer *eb,
				    पूर्णांक level)
अणु
	काष्ठा btrfs_lockdep_keyset *ks;

	BUG_ON(level >= ARRAY_SIZE(ks->keys));

	/* find the matching keyset, id 0 is the शेष entry */
	क्रम (ks = btrfs_lockdep_keysets; ks->id; ks++)
		अगर (ks->id == objectid)
			अवरोध;

	lockdep_set_class_and_name(&eb->lock,
				   &ks->keys[level], ks->names[level]);
पूर्ण

#पूर्ण_अगर

/*
 * Compute the csum of a btree block and store the result to provided buffer.
 */
अटल व्योम csum_tree_block(काष्ठा extent_buffer *buf, u8 *result)
अणु
	काष्ठा btrfs_fs_info *fs_info = buf->fs_info;
	स्थिर पूर्णांक num_pages = fs_info->nodesize >> PAGE_SHIFT;
	स्थिर पूर्णांक first_page_part = min_t(u32, PAGE_SIZE, fs_info->nodesize);
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	अक्षर *kaddr;
	पूर्णांक i;

	shash->tfm = fs_info->csum_shash;
	crypto_shash_init(shash);
	kaddr = page_address(buf->pages[0]) + offset_in_page(buf->start);
	crypto_shash_update(shash, kaddr + BTRFS_CSUM_SIZE,
			    first_page_part - BTRFS_CSUM_SIZE);

	क्रम (i = 1; i < num_pages; i++) अणु
		kaddr = page_address(buf->pages[i]);
		crypto_shash_update(shash, kaddr, PAGE_SIZE);
	पूर्ण
	स_रखो(result, 0, BTRFS_CSUM_SIZE);
	crypto_shash_final(shash, result);
पूर्ण

/*
 * we can't consider a given block up to date unless the transid of the
 * block matches the transid in the parent node's poपूर्णांकer.  This is how we
 * detect blocks that either didn't get written at all or got written
 * in the wrong place.
 */
अटल पूर्णांक verअगरy_parent_transid(काष्ठा extent_io_tree *io_tree,
				 काष्ठा extent_buffer *eb, u64 parent_transid,
				 पूर्णांक atomic)
अणु
	काष्ठा extent_state *cached_state = शून्य;
	पूर्णांक ret;
	bool need_lock = (current->journal_info == BTRFS_SEND_TRANS_STUB);

	अगर (!parent_transid || btrfs_header_generation(eb) == parent_transid)
		वापस 0;

	अगर (atomic)
		वापस -EAGAIN;

	अगर (need_lock)
		btrfs_tree_पढ़ो_lock(eb);

	lock_extent_bits(io_tree, eb->start, eb->start + eb->len - 1,
			 &cached_state);
	अगर (extent_buffer_uptodate(eb) &&
	    btrfs_header_generation(eb) == parent_transid) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	btrfs_err_rl(eb->fs_info,
		"parent transid verify failed on %llu wanted %llu found %llu",
			eb->start,
			parent_transid, btrfs_header_generation(eb));
	ret = 1;

	/*
	 * Things पढ़ोing via commit roots that करोn't have normal protection,
	 * like send, can have a really old block in cache that may poपूर्णांक at a
	 * block that has been मुक्तd and re-allocated.  So करोn't clear uptodate
	 * अगर we find an eb that is under IO (dirty/ग_लिखोback) because we could
	 * end up पढ़ोing in the stale data and then writing it back out and
	 * making everybody very sad.
	 */
	अगर (!extent_buffer_under_io(eb))
		clear_extent_buffer_uptodate(eb);
out:
	unlock_extent_cached(io_tree, eb->start, eb->start + eb->len - 1,
			     &cached_state);
	अगर (need_lock)
		btrfs_tree_पढ़ो_unlock(eb);
	वापस ret;
पूर्ण

अटल bool btrfs_supported_super_csum(u16 csum_type)
अणु
	चयन (csum_type) अणु
	हाल BTRFS_CSUM_TYPE_CRC32:
	हाल BTRFS_CSUM_TYPE_XXHASH:
	हाल BTRFS_CSUM_TYPE_SHA256:
	हाल BTRFS_CSUM_TYPE_BLAKE2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * Return 0 अगर the superblock checksum type matches the checksum value of that
 * algorithm. Pass the raw disk superblock data.
 */
अटल पूर्णांक btrfs_check_super_csum(काष्ठा btrfs_fs_info *fs_info,
				  अक्षर *raw_disk_sb)
अणु
	काष्ठा btrfs_super_block *disk_sb =
		(काष्ठा btrfs_super_block *)raw_disk_sb;
	अक्षर result[BTRFS_CSUM_SIZE];
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);

	shash->tfm = fs_info->csum_shash;

	/*
	 * The super_block काष्ठाure करोes not span the whole
	 * BTRFS_SUPER_INFO_SIZE range, we expect that the unused space is
	 * filled with zeros and is included in the checksum.
	 */
	crypto_shash_digest(shash, raw_disk_sb + BTRFS_CSUM_SIZE,
			    BTRFS_SUPER_INFO_SIZE - BTRFS_CSUM_SIZE, result);

	अगर (स_भेद(disk_sb->csum, result, fs_info->csum_size))
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक btrfs_verअगरy_level_key(काष्ठा extent_buffer *eb, पूर्णांक level,
			   काष्ठा btrfs_key *first_key, u64 parent_transid)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	पूर्णांक found_level;
	काष्ठा btrfs_key found_key;
	पूर्णांक ret;

	found_level = btrfs_header_level(eb);
	अगर (found_level != level) अणु
		WARN(IS_ENABLED(CONFIG_BTRFS_DEBUG),
		     KERN_ERR "BTRFS: tree level check failed\n");
		btrfs_err(fs_info,
"tree level mismatch detected, bytenr=%llu level expected=%u has=%u",
			  eb->start, level, found_level);
		वापस -EIO;
	पूर्ण

	अगर (!first_key)
		वापस 0;

	/*
	 * For live tree block (new tree blocks in current transaction),
	 * we need proper lock context to aव्योम race, which is impossible here.
	 * So we only checks tree blocks which is पढ़ो from disk, whose
	 * generation <= fs_info->last_trans_committed.
	 */
	अगर (btrfs_header_generation(eb) > fs_info->last_trans_committed)
		वापस 0;

	/* We have @first_key, so this @eb must have at least one item */
	अगर (btrfs_header_nritems(eb) == 0) अणु
		btrfs_err(fs_info,
		"invalid tree nritems, bytenr=%llu nritems=0 expect >0",
			  eb->start);
		WARN_ON(IS_ENABLED(CONFIG_BTRFS_DEBUG));
		वापस -EUCLEAN;
	पूर्ण

	अगर (found_level)
		btrfs_node_key_to_cpu(eb, &found_key, 0);
	अन्यथा
		btrfs_item_key_to_cpu(eb, &found_key, 0);
	ret = btrfs_comp_cpu_keys(first_key, &found_key);

	अगर (ret) अणु
		WARN(IS_ENABLED(CONFIG_BTRFS_DEBUG),
		     KERN_ERR "BTRFS: tree first key check failed\n");
		btrfs_err(fs_info,
"tree first key mismatch detected, bytenr=%llu parent_transid=%llu key expected=(%llu,%u,%llu) has=(%llu,%u,%llu)",
			  eb->start, parent_transid, first_key->objectid,
			  first_key->type, first_key->offset,
			  found_key.objectid, found_key.type,
			  found_key.offset);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * helper to पढ़ो a given tree block, करोing retries as required when
 * the checksums करोn't match and we have alternate mirrors to try.
 *
 * @parent_transid:	expected transid, skip check अगर 0
 * @level:		expected level, mandatory check
 * @first_key:		expected key of first slot, skip check अगर शून्य
 */
अटल पूर्णांक btree_पढ़ो_extent_buffer_pages(काष्ठा extent_buffer *eb,
					  u64 parent_transid, पूर्णांक level,
					  काष्ठा btrfs_key *first_key)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा extent_io_tree *io_tree;
	पूर्णांक failed = 0;
	पूर्णांक ret;
	पूर्णांक num_copies = 0;
	पूर्णांक mirror_num = 0;
	पूर्णांक failed_mirror = 0;

	io_tree = &BTRFS_I(fs_info->btree_inode)->io_tree;
	जबतक (1) अणु
		clear_bit(EXTENT_BUFFER_CORRUPT, &eb->bflags);
		ret = पढ़ो_extent_buffer_pages(eb, WAIT_COMPLETE, mirror_num);
		अगर (!ret) अणु
			अगर (verअगरy_parent_transid(io_tree, eb,
						   parent_transid, 0))
				ret = -EIO;
			अन्यथा अगर (btrfs_verअगरy_level_key(eb, level,
						first_key, parent_transid))
				ret = -EUCLEAN;
			अन्यथा
				अवरोध;
		पूर्ण

		num_copies = btrfs_num_copies(fs_info,
					      eb->start, eb->len);
		अगर (num_copies == 1)
			अवरोध;

		अगर (!failed_mirror) अणु
			failed = 1;
			failed_mirror = eb->पढ़ो_mirror;
		पूर्ण

		mirror_num++;
		अगर (mirror_num == failed_mirror)
			mirror_num++;

		अगर (mirror_num > num_copies)
			अवरोध;
	पूर्ण

	अगर (failed && !ret && failed_mirror)
		btrfs_repair_eb_io_failure(eb, failed_mirror);

	वापस ret;
पूर्ण

अटल पूर्णांक csum_one_extent_buffer(काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	u8 result[BTRFS_CSUM_SIZE];
	पूर्णांक ret;

	ASSERT(स_भेद_extent_buffer(eb, fs_info->fs_devices->metadata_uuid,
				    दुरत्व(काष्ठा btrfs_header, fsid),
				    BTRFS_FSID_SIZE) == 0);
	csum_tree_block(eb, result);

	अगर (btrfs_header_level(eb))
		ret = btrfs_check_node(eb);
	अन्यथा
		ret = btrfs_check_leaf_full(eb);

	अगर (ret < 0) अणु
		btrfs_prपूर्णांक_tree(eb, 0);
		btrfs_err(fs_info,
			"block=%llu write time tree block corruption detected",
			eb->start);
		WARN_ON(IS_ENABLED(CONFIG_BTRFS_DEBUG));
		वापस ret;
	पूर्ण
	ग_लिखो_extent_buffer(eb, result, 0, fs_info->csum_size);

	वापस 0;
पूर्ण

/* Checksum all dirty extent buffers in one bio_vec */
अटल पूर्णांक csum_dirty_subpage_buffers(काष्ठा btrfs_fs_info *fs_info,
				      काष्ठा bio_vec *bvec)
अणु
	काष्ठा page *page = bvec->bv_page;
	u64 bvec_start = page_offset(page) + bvec->bv_offset;
	u64 cur;
	पूर्णांक ret = 0;

	क्रम (cur = bvec_start; cur < bvec_start + bvec->bv_len;
	     cur += fs_info->nodesize) अणु
		काष्ठा extent_buffer *eb;
		bool uptodate;

		eb = find_extent_buffer(fs_info, cur);
		uptodate = btrfs_subpage_test_uptodate(fs_info, page, cur,
						       fs_info->nodesize);

		/* A dirty eb shouldn't disappear from buffer_radix */
		अगर (WARN_ON(!eb))
			वापस -EUCLEAN;

		अगर (WARN_ON(cur != btrfs_header_bytenr(eb))) अणु
			मुक्त_extent_buffer(eb);
			वापस -EUCLEAN;
		पूर्ण
		अगर (WARN_ON(!uptodate)) अणु
			मुक्त_extent_buffer(eb);
			वापस -EUCLEAN;
		पूर्ण

		ret = csum_one_extent_buffer(eb);
		मुक्त_extent_buffer(eb);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Checksum a dirty tree block beक्रमe IO.  This has extra checks to make sure
 * we only fill in the checksum field in the first page of a multi-page block.
 * For subpage extent buffers we need bvec to also पढ़ो the offset in the page.
 */
अटल पूर्णांक csum_dirty_buffer(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio_vec *bvec)
अणु
	काष्ठा page *page = bvec->bv_page;
	u64 start = page_offset(page);
	u64 found_start;
	काष्ठा extent_buffer *eb;

	अगर (fs_info->sectorsize < PAGE_SIZE)
		वापस csum_dirty_subpage_buffers(fs_info, bvec);

	eb = (काष्ठा extent_buffer *)page->निजी;
	अगर (page != eb->pages[0])
		वापस 0;

	found_start = btrfs_header_bytenr(eb);

	अगर (test_bit(EXTENT_BUFFER_NO_CHECK, &eb->bflags)) अणु
		WARN_ON(found_start != 0);
		वापस 0;
	पूर्ण

	/*
	 * Please करो not consolidate these warnings पूर्णांकo a single अगर.
	 * It is useful to know what went wrong.
	 */
	अगर (WARN_ON(found_start != start))
		वापस -EUCLEAN;
	अगर (WARN_ON(!PageUptodate(page)))
		वापस -EUCLEAN;

	वापस csum_one_extent_buffer(eb);
पूर्ण

अटल पूर्णांक check_tree_block_fsid(काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices, *seed_devs;
	u8 fsid[BTRFS_FSID_SIZE];
	u8 *metadata_uuid;

	पढ़ो_extent_buffer(eb, fsid, दुरत्व(काष्ठा btrfs_header, fsid),
			   BTRFS_FSID_SIZE);
	/*
	 * Checking the incompat flag is only valid क्रम the current fs. For
	 * seed devices it's क्रमbidden to have their uuid changed so पढ़ोing
	 * ->fsid in this हाल is fine
	 */
	अगर (btrfs_fs_incompat(fs_info, METADATA_UUID))
		metadata_uuid = fs_devices->metadata_uuid;
	अन्यथा
		metadata_uuid = fs_devices->fsid;

	अगर (!स_भेद(fsid, metadata_uuid, BTRFS_FSID_SIZE))
		वापस 0;

	list_क्रम_each_entry(seed_devs, &fs_devices->seed_list, seed_list)
		अगर (!स_भेद(fsid, seed_devs->fsid, BTRFS_FSID_SIZE))
			वापस 0;

	वापस 1;
पूर्ण

/* Do basic extent buffer checks at पढ़ो समय */
अटल पूर्णांक validate_extent_buffer(काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	u64 found_start;
	स्थिर u32 csum_size = fs_info->csum_size;
	u8 found_level;
	u8 result[BTRFS_CSUM_SIZE];
	पूर्णांक ret = 0;

	found_start = btrfs_header_bytenr(eb);
	अगर (found_start != eb->start) अणु
		btrfs_err_rl(fs_info, "bad tree block start, want %llu have %llu",
			     eb->start, found_start);
		ret = -EIO;
		जाओ out;
	पूर्ण
	अगर (check_tree_block_fsid(eb)) अणु
		btrfs_err_rl(fs_info, "bad fsid on block %llu",
			     eb->start);
		ret = -EIO;
		जाओ out;
	पूर्ण
	found_level = btrfs_header_level(eb);
	अगर (found_level >= BTRFS_MAX_LEVEL) अणु
		btrfs_err(fs_info, "bad tree block level %d on %llu",
			  (पूर्णांक)btrfs_header_level(eb), eb->start);
		ret = -EIO;
		जाओ out;
	पूर्ण

	csum_tree_block(eb, result);

	अगर (स_भेद_extent_buffer(eb, result, 0, csum_size)) अणु
		u8 val[BTRFS_CSUM_SIZE] = अणु 0 पूर्ण;

		पढ़ो_extent_buffer(eb, &val, 0, csum_size);
		btrfs_warn_rl(fs_info,
	"%s checksum verify failed on %llu wanted " CSUM_FMT " found " CSUM_FMT " level %d",
			      fs_info->sb->s_id, eb->start,
			      CSUM_FMT_VALUE(csum_size, val),
			      CSUM_FMT_VALUE(csum_size, result),
			      btrfs_header_level(eb));
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण

	/*
	 * If this is a leaf block and it is corrupt, set the corrupt bit so
	 * that we करोn't try and पढ़ो the other copies of this block, just
	 * वापस -EIO.
	 */
	अगर (found_level == 0 && btrfs_check_leaf_full(eb)) अणु
		set_bit(EXTENT_BUFFER_CORRUPT, &eb->bflags);
		ret = -EIO;
	पूर्ण

	अगर (found_level > 0 && btrfs_check_node(eb))
		ret = -EIO;

	अगर (!ret)
		set_extent_buffer_uptodate(eb);
	अन्यथा
		btrfs_err(fs_info,
			  "block=%llu read time tree block corruption detected",
			  eb->start);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक validate_subpage_buffer(काष्ठा page *page, u64 start, u64 end,
				   पूर्णांक mirror)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(page->mapping->host->i_sb);
	काष्ठा extent_buffer *eb;
	bool पढ़ोs_करोne;
	पूर्णांक ret = 0;

	/*
	 * We करोn't allow bio merge क्रम subpage metadata पढ़ो, so we should
	 * only get one eb क्रम each endio hook.
	 */
	ASSERT(end == start + fs_info->nodesize - 1);
	ASSERT(PagePrivate(page));

	eb = find_extent_buffer(fs_info, start);
	/*
	 * When we are पढ़ोing one tree block, eb must have been inserted पूर्णांकo
	 * the radix tree. If not, something is wrong.
	 */
	ASSERT(eb);

	पढ़ोs_करोne = atomic_dec_and_test(&eb->io_pages);
	/* Subpage पढ़ो must finish in page पढ़ो */
	ASSERT(पढ़ोs_करोne);

	eb->पढ़ो_mirror = mirror;
	अगर (test_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण
	ret = validate_extent_buffer(eb);
	अगर (ret < 0)
		जाओ err;

	अगर (test_and_clear_bit(EXTENT_BUFFER_READAHEAD, &eb->bflags))
		btree_पढ़ोahead_hook(eb, ret);

	set_extent_buffer_uptodate(eb);

	मुक्त_extent_buffer(eb);
	वापस ret;
err:
	/*
	 * end_bio_extent_पढ़ोpage decrements io_pages in हाल of error,
	 * make sure it has something to decrement.
	 */
	atomic_inc(&eb->io_pages);
	clear_extent_buffer_uptodate(eb);
	मुक्त_extent_buffer(eb);
	वापस ret;
पूर्ण

पूर्णांक btrfs_validate_metadata_buffer(काष्ठा btrfs_io_bio *io_bio,
				   काष्ठा page *page, u64 start, u64 end,
				   पूर्णांक mirror)
अणु
	काष्ठा extent_buffer *eb;
	पूर्णांक ret = 0;
	पूर्णांक पढ़ोs_करोne;

	ASSERT(page->निजी);

	अगर (btrfs_sb(page->mapping->host->i_sb)->sectorsize < PAGE_SIZE)
		वापस validate_subpage_buffer(page, start, end, mirror);

	eb = (काष्ठा extent_buffer *)page->निजी;

	/*
	 * The pending IO might have been the only thing that kept this buffer
	 * in memory.  Make sure we have a ref क्रम all this other checks
	 */
	atomic_inc(&eb->refs);

	पढ़ोs_करोne = atomic_dec_and_test(&eb->io_pages);
	अगर (!पढ़ोs_करोne)
		जाओ err;

	eb->पढ़ो_mirror = mirror;
	अगर (test_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण
	ret = validate_extent_buffer(eb);
err:
	अगर (पढ़ोs_करोne &&
	    test_and_clear_bit(EXTENT_BUFFER_READAHEAD, &eb->bflags))
		btree_पढ़ोahead_hook(eb, ret);

	अगर (ret) अणु
		/*
		 * our io error hook is going to dec the io pages
		 * again, we have to make sure it has something
		 * to decrement
		 */
		atomic_inc(&eb->io_pages);
		clear_extent_buffer_uptodate(eb);
	पूर्ण
	मुक्त_extent_buffer(eb);

	वापस ret;
पूर्ण

अटल व्योम end_workqueue_bio(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_end_io_wq *end_io_wq = bio->bi_निजी;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_workqueue *wq;

	fs_info = end_io_wq->info;
	end_io_wq->status = bio->bi_status;

	अगर (btrfs_op(bio) == BTRFS_MAP_WRITE) अणु
		अगर (end_io_wq->metadata == BTRFS_WQ_ENDIO_METADATA)
			wq = fs_info->endio_meta_ग_लिखो_workers;
		अन्यथा अगर (end_io_wq->metadata == BTRFS_WQ_ENDIO_FREE_SPACE)
			wq = fs_info->endio_मुक्तspace_worker;
		अन्यथा अगर (end_io_wq->metadata == BTRFS_WQ_ENDIO_RAID56)
			wq = fs_info->endio_raid56_workers;
		अन्यथा
			wq = fs_info->endio_ग_लिखो_workers;
	पूर्ण अन्यथा अणु
		अगर (end_io_wq->metadata == BTRFS_WQ_ENDIO_RAID56)
			wq = fs_info->endio_raid56_workers;
		अन्यथा अगर (end_io_wq->metadata)
			wq = fs_info->endio_meta_workers;
		अन्यथा
			wq = fs_info->endio_workers;
	पूर्ण

	btrfs_init_work(&end_io_wq->work, end_workqueue_fn, शून्य, शून्य);
	btrfs_queue_work(wq, &end_io_wq->work);
पूर्ण

blk_status_t btrfs_bio_wq_end_io(काष्ठा btrfs_fs_info *info, काष्ठा bio *bio,
			क्रमागत btrfs_wq_endio_type metadata)
अणु
	काष्ठा btrfs_end_io_wq *end_io_wq;

	end_io_wq = kmem_cache_alloc(btrfs_end_io_wq_cache, GFP_NOFS);
	अगर (!end_io_wq)
		वापस BLK_STS_RESOURCE;

	end_io_wq->निजी = bio->bi_निजी;
	end_io_wq->end_io = bio->bi_end_io;
	end_io_wq->info = info;
	end_io_wq->status = 0;
	end_io_wq->bio = bio;
	end_io_wq->metadata = metadata;

	bio->bi_निजी = end_io_wq;
	bio->bi_end_io = end_workqueue_bio;
	वापस 0;
पूर्ण

अटल व्योम run_one_async_start(काष्ठा btrfs_work *work)
अणु
	काष्ठा async_submit_bio *async;
	blk_status_t ret;

	async = container_of(work, काष्ठा  async_submit_bio, work);
	ret = async->submit_bio_start(async->inode, async->bio,
				      async->dio_file_offset);
	अगर (ret)
		async->status = ret;
पूर्ण

/*
 * In order to insert checksums पूर्णांकo the metadata in large chunks, we रुको
 * until bio submission समय.   All the pages in the bio are checksummed and
 * sums are attached onto the ordered extent record.
 *
 * At IO completion समय the csums attached on the ordered extent record are
 * inserted पूर्णांकo the tree.
 */
अटल व्योम run_one_async_करोne(काष्ठा btrfs_work *work)
अणु
	काष्ठा async_submit_bio *async;
	काष्ठा inode *inode;
	blk_status_t ret;

	async = container_of(work, काष्ठा  async_submit_bio, work);
	inode = async->inode;

	/* If an error occurred we just want to clean up the bio and move on */
	अगर (async->status) अणु
		async->bio->bi_status = async->status;
		bio_endio(async->bio);
		वापस;
	पूर्ण

	/*
	 * All of the bios that pass through here are from async helpers.
	 * Use REQ_CGROUP_PUNT to issue them from the owning cgroup's context.
	 * This changes nothing when cgroups aren't in use.
	 */
	async->bio->bi_opf |= REQ_CGROUP_PUNT;
	ret = btrfs_map_bio(btrfs_sb(inode->i_sb), async->bio, async->mirror_num);
	अगर (ret) अणु
		async->bio->bi_status = ret;
		bio_endio(async->bio);
	पूर्ण
पूर्ण

अटल व्योम run_one_async_मुक्त(काष्ठा btrfs_work *work)
अणु
	काष्ठा async_submit_bio *async;

	async = container_of(work, काष्ठा  async_submit_bio, work);
	kमुक्त(async);
पूर्ण

blk_status_t btrfs_wq_submit_bio(काष्ठा inode *inode, काष्ठा bio *bio,
				 पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags,
				 u64 dio_file_offset,
				 extent_submit_bio_start_t *submit_bio_start)
अणु
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	काष्ठा async_submit_bio *async;

	async = kदो_स्मृति(माप(*async), GFP_NOFS);
	अगर (!async)
		वापस BLK_STS_RESOURCE;

	async->inode = inode;
	async->bio = bio;
	async->mirror_num = mirror_num;
	async->submit_bio_start = submit_bio_start;

	btrfs_init_work(&async->work, run_one_async_start, run_one_async_करोne,
			run_one_async_मुक्त);

	async->dio_file_offset = dio_file_offset;

	async->status = 0;

	अगर (op_is_sync(bio->bi_opf))
		btrfs_set_work_high_priority(&async->work);

	btrfs_queue_work(fs_info->workers, &async->work);
	वापस 0;
पूर्ण

अटल blk_status_t btree_csum_one_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा btrfs_root *root;
	पूर्णांक ret = 0;
	काष्ठा bvec_iter_all iter_all;

	ASSERT(!bio_flagged(bio, BIO_CLONED));
	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		root = BTRFS_I(bvec->bv_page->mapping->host)->root;
		ret = csum_dirty_buffer(root->fs_info, bvec);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस त्रुटि_सं_to_blk_status(ret);
पूर्ण

अटल blk_status_t btree_submit_bio_start(काष्ठा inode *inode, काष्ठा bio *bio,
					   u64 dio_file_offset)
अणु
	/*
	 * when we're called for a write, we're alपढ़ोy in the async
	 * submission context.  Just jump पूर्णांकo btrfs_map_bio
	 */
	वापस btree_csum_one_bio(bio);
पूर्ण

अटल पूर्णांक check_async_ग_लिखो(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा btrfs_inode *bi)
अणु
	अगर (btrfs_is_zoned(fs_info))
		वापस 0;
	अगर (atomic_पढ़ो(&bi->sync_ग_लिखोrs))
		वापस 0;
	अगर (test_bit(BTRFS_FS_CSUM_IMPL_FAST, &fs_info->flags))
		वापस 0;
	वापस 1;
पूर्ण

blk_status_t btrfs_submit_metadata_bio(काष्ठा inode *inode, काष्ठा bio *bio,
				       पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	पूर्णांक async = check_async_ग_लिखो(fs_info, BTRFS_I(inode));
	blk_status_t ret;

	अगर (btrfs_op(bio) != BTRFS_MAP_WRITE) अणु
		/*
		 * called क्रम a पढ़ो, करो the setup so that checksum validation
		 * can happen in the async kernel thपढ़ोs
		 */
		ret = btrfs_bio_wq_end_io(fs_info, bio,
					  BTRFS_WQ_ENDIO_METADATA);
		अगर (ret)
			जाओ out_w_error;
		ret = btrfs_map_bio(fs_info, bio, mirror_num);
	पूर्ण अन्यथा अगर (!async) अणु
		ret = btree_csum_one_bio(bio);
		अगर (ret)
			जाओ out_w_error;
		ret = btrfs_map_bio(fs_info, bio, mirror_num);
	पूर्ण अन्यथा अणु
		/*
		 * kthपढ़ो helpers are used to submit ग_लिखोs so that
		 * checksumming can happen in parallel across all CPUs
		 */
		ret = btrfs_wq_submit_bio(inode, bio, mirror_num, 0,
					  0, btree_submit_bio_start);
	पूर्ण

	अगर (ret)
		जाओ out_w_error;
	वापस 0;

out_w_error:
	bio->bi_status = ret;
	bio_endio(bio);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_MIGRATION
अटल पूर्णांक btree_migratepage(काष्ठा address_space *mapping,
			काष्ठा page *newpage, काष्ठा page *page,
			क्रमागत migrate_mode mode)
अणु
	/*
	 * we can't safely ग_लिखो a btree page from here,
	 * we haven't करोne the locking hook
	 */
	अगर (PageDirty(page))
		वापस -EAGAIN;
	/*
	 * Buffers may be managed in a fileप्रणाली specअगरic way.
	 * We must have no buffers or drop them.
	 */
	अगर (page_has_निजी(page) &&
	    !try_to_release_page(page, GFP_KERNEL))
		वापस -EAGAIN;
	वापस migrate_page(mapping, newpage, page, mode);
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक btree_ग_लिखोpages(काष्ठा address_space *mapping,
			    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	पूर्णांक ret;

	अगर (wbc->sync_mode == WB_SYNC_NONE) अणु

		अगर (wbc->क्रम_kupdate)
			वापस 0;

		fs_info = BTRFS_I(mapping->host)->root->fs_info;
		/* this is a bit racy, but that's ok */
		ret = __percpu_counter_compare(&fs_info->dirty_metadata_bytes,
					     BTRFS_सूचीTY_METADATA_THRESH,
					     fs_info->dirty_metadata_batch);
		अगर (ret < 0)
			वापस 0;
	पूर्ण
	वापस btree_ग_लिखो_cache_pages(mapping, wbc);
पूर्ण

अटल पूर्णांक btree_releasepage(काष्ठा page *page, gfp_t gfp_flags)
अणु
	अगर (PageWriteback(page) || PageDirty(page))
		वापस 0;

	वापस try_release_extent_buffer(page);
पूर्ण

अटल व्योम btree_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				 अचिन्हित पूर्णांक length)
अणु
	काष्ठा extent_io_tree *tree;
	tree = &BTRFS_I(page->mapping->host)->io_tree;
	extent_invalidatepage(tree, page, offset);
	btree_releasepage(page, GFP_NOFS);
	अगर (PagePrivate(page)) अणु
		btrfs_warn(BTRFS_I(page->mapping->host)->root->fs_info,
			   "page private not zero on page %llu",
			   (अचिन्हित दीर्घ दीर्घ)page_offset(page));
		detach_page_निजी(page);
	पूर्ण
पूर्ण

अटल पूर्णांक btree_set_page_dirty(काष्ठा page *page)
अणु
#अगर_घोषित DEBUG
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(page->mapping->host->i_sb);
	काष्ठा btrfs_subpage *subpage;
	काष्ठा extent_buffer *eb;
	पूर्णांक cur_bit = 0;
	u64 page_start = page_offset(page);

	अगर (fs_info->sectorsize == PAGE_SIZE) अणु
		BUG_ON(!PagePrivate(page));
		eb = (काष्ठा extent_buffer *)page->निजी;
		BUG_ON(!eb);
		BUG_ON(!test_bit(EXTENT_BUFFER_सूचीTY, &eb->bflags));
		BUG_ON(!atomic_पढ़ो(&eb->refs));
		btrfs_निश्चित_tree_locked(eb);
		वापस __set_page_dirty_nobuffers(page);
	पूर्ण
	ASSERT(PagePrivate(page) && page->निजी);
	subpage = (काष्ठा btrfs_subpage *)page->निजी;

	ASSERT(subpage->dirty_biपंचांगap);
	जबतक (cur_bit < BTRFS_SUBPAGE_BITMAP_SIZE) अणु
		अचिन्हित दीर्घ flags;
		u64 cur;
		u16 पंचांगp = (1 << cur_bit);

		spin_lock_irqsave(&subpage->lock, flags);
		अगर (!(पंचांगp & subpage->dirty_biपंचांगap)) अणु
			spin_unlock_irqrestore(&subpage->lock, flags);
			cur_bit++;
			जारी;
		पूर्ण
		spin_unlock_irqrestore(&subpage->lock, flags);
		cur = page_start + cur_bit * fs_info->sectorsize;

		eb = find_extent_buffer(fs_info, cur);
		ASSERT(eb);
		ASSERT(test_bit(EXTENT_BUFFER_सूचीTY, &eb->bflags));
		ASSERT(atomic_पढ़ो(&eb->refs));
		btrfs_निश्चित_tree_locked(eb);
		मुक्त_extent_buffer(eb);

		cur_bit += (fs_info->nodesize >> fs_info->sectorsize_bits);
	पूर्ण
#पूर्ण_अगर
	वापस __set_page_dirty_nobuffers(page);
पूर्ण

अटल स्थिर काष्ठा address_space_operations btree_aops = अणु
	.ग_लिखोpages	= btree_ग_लिखोpages,
	.releasepage	= btree_releasepage,
	.invalidatepage = btree_invalidatepage,
#अगर_घोषित CONFIG_MIGRATION
	.migratepage	= btree_migratepage,
#पूर्ण_अगर
	.set_page_dirty = btree_set_page_dirty,
पूर्ण;

काष्ठा extent_buffer *btrfs_find_create_tree_block(
						काष्ठा btrfs_fs_info *fs_info,
						u64 bytenr, u64 owner_root,
						पूर्णांक level)
अणु
	अगर (btrfs_is_testing(fs_info))
		वापस alloc_test_extent_buffer(fs_info, bytenr);
	वापस alloc_extent_buffer(fs_info, bytenr, owner_root, level);
पूर्ण

/*
 * Read tree block at logical address @bytenr and करो variant basic but critical
 * verअगरication.
 *
 * @owner_root:		the objectid of the root owner क्रम this block.
 * @parent_transid:	expected transid of this tree block, skip check अगर 0
 * @level:		expected level, mandatory check
 * @first_key:		expected key in slot 0, skip check अगर शून्य
 */
काष्ठा extent_buffer *पढ़ो_tree_block(काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
				      u64 owner_root, u64 parent_transid,
				      पूर्णांक level, काष्ठा btrfs_key *first_key)
अणु
	काष्ठा extent_buffer *buf = शून्य;
	पूर्णांक ret;

	buf = btrfs_find_create_tree_block(fs_info, bytenr, owner_root, level);
	अगर (IS_ERR(buf))
		वापस buf;

	ret = btree_पढ़ो_extent_buffer_pages(buf, parent_transid,
					     level, first_key);
	अगर (ret) अणु
		मुक्त_extent_buffer_stale(buf);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस buf;

पूर्ण

व्योम btrfs_clean_tree_block(काष्ठा extent_buffer *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = buf->fs_info;
	अगर (btrfs_header_generation(buf) ==
	    fs_info->running_transaction->transid) अणु
		btrfs_निश्चित_tree_locked(buf);

		अगर (test_and_clear_bit(EXTENT_BUFFER_सूचीTY, &buf->bflags)) अणु
			percpu_counter_add_batch(&fs_info->dirty_metadata_bytes,
						 -buf->len,
						 fs_info->dirty_metadata_batch);
			clear_extent_buffer_dirty(buf);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __setup_root(काष्ठा btrfs_root *root, काष्ठा btrfs_fs_info *fs_info,
			 u64 objectid)
अणु
	bool dummy = test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state);
	root->fs_info = fs_info;
	root->node = शून्य;
	root->commit_root = शून्य;
	root->state = 0;
	root->orphan_cleanup_state = 0;

	root->last_trans = 0;
	root->मुक्त_objectid = 0;
	root->nr_delalloc_inodes = 0;
	root->nr_ordered_extents = 0;
	root->inode_tree = RB_ROOT;
	INIT_RADIX_TREE(&root->delayed_nodes_tree, GFP_ATOMIC);
	root->block_rsv = शून्य;

	INIT_LIST_HEAD(&root->dirty_list);
	INIT_LIST_HEAD(&root->root_list);
	INIT_LIST_HEAD(&root->delalloc_inodes);
	INIT_LIST_HEAD(&root->delalloc_root);
	INIT_LIST_HEAD(&root->ordered_extents);
	INIT_LIST_HEAD(&root->ordered_root);
	INIT_LIST_HEAD(&root->reloc_dirty_list);
	INIT_LIST_HEAD(&root->logged_list[0]);
	INIT_LIST_HEAD(&root->logged_list[1]);
	spin_lock_init(&root->inode_lock);
	spin_lock_init(&root->delalloc_lock);
	spin_lock_init(&root->ordered_extent_lock);
	spin_lock_init(&root->accounting_lock);
	spin_lock_init(&root->log_extents_lock[0]);
	spin_lock_init(&root->log_extents_lock[1]);
	spin_lock_init(&root->qgroup_meta_rsv_lock);
	mutex_init(&root->objectid_mutex);
	mutex_init(&root->log_mutex);
	mutex_init(&root->ordered_extent_mutex);
	mutex_init(&root->delalloc_mutex);
	init_रुकोqueue_head(&root->qgroup_flush_रुको);
	init_रुकोqueue_head(&root->log_ग_लिखोr_रुको);
	init_रुकोqueue_head(&root->log_commit_रुको[0]);
	init_रुकोqueue_head(&root->log_commit_रुको[1]);
	INIT_LIST_HEAD(&root->log_ctxs[0]);
	INIT_LIST_HEAD(&root->log_ctxs[1]);
	atomic_set(&root->log_commit[0], 0);
	atomic_set(&root->log_commit[1], 0);
	atomic_set(&root->log_ग_लिखोrs, 0);
	atomic_set(&root->log_batch, 0);
	refcount_set(&root->refs, 1);
	atomic_set(&root->snapshot_क्रमce_cow, 0);
	atomic_set(&root->nr_swapfiles, 0);
	root->log_transid = 0;
	root->log_transid_committed = -1;
	root->last_log_commit = 0;
	अगर (!dummy) अणु
		extent_io_tree_init(fs_info, &root->dirty_log_pages,
				    IO_TREE_ROOT_सूचीTY_LOG_PAGES, शून्य);
		extent_io_tree_init(fs_info, &root->log_csum_range,
				    IO_TREE_LOG_CSUM_RANGE, शून्य);
	पूर्ण

	स_रखो(&root->root_key, 0, माप(root->root_key));
	स_रखो(&root->root_item, 0, माप(root->root_item));
	स_रखो(&root->defrag_progress, 0, माप(root->defrag_progress));
	root->root_key.objectid = objectid;
	root->anon_dev = 0;

	spin_lock_init(&root->root_item_lock);
	btrfs_qgroup_init_swapped_blocks(&root->swapped_blocks);
#अगर_घोषित CONFIG_BTRFS_DEBUG
	INIT_LIST_HEAD(&root->leak_list);
	spin_lock(&fs_info->fs_roots_radix_lock);
	list_add_tail(&root->leak_list, &fs_info->allocated_roots);
	spin_unlock(&fs_info->fs_roots_radix_lock);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा btrfs_root *btrfs_alloc_root(काष्ठा btrfs_fs_info *fs_info,
					   u64 objectid, gfp_t flags)
अणु
	काष्ठा btrfs_root *root = kzalloc(माप(*root), flags);
	अगर (root)
		__setup_root(root, fs_info, objectid);
	वापस root;
पूर्ण

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
/* Should only be used by the testing infraकाष्ठाure */
काष्ठा btrfs_root *btrfs_alloc_dummy_root(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root;

	अगर (!fs_info)
		वापस ERR_PTR(-EINVAL);

	root = btrfs_alloc_root(fs_info, BTRFS_ROOT_TREE_OBJECTID, GFP_KERNEL);
	अगर (!root)
		वापस ERR_PTR(-ENOMEM);

	/* We करोn't use the stripesize in selftest, set it as sectorsize */
	root->alloc_bytenr = 0;

	वापस root;
पूर्ण
#पूर्ण_अगर

काष्ठा btrfs_root *btrfs_create_tree(काष्ठा btrfs_trans_handle *trans,
				     u64 objectid)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक ret = 0;

	/*
	 * We're holding a transaction handle, so use a NOFS memory allocation
	 * context to aव्योम deadlock अगर reclaim happens.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	root = btrfs_alloc_root(fs_info, objectid, GFP_KERNEL);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (!root)
		वापस ERR_PTR(-ENOMEM);

	root->root_key.objectid = objectid;
	root->root_key.type = BTRFS_ROOT_ITEM_KEY;
	root->root_key.offset = 0;

	leaf = btrfs_alloc_tree_block(trans, root, 0, objectid, शून्य, 0, 0, 0,
				      BTRFS_NESTING_NORMAL);
	अगर (IS_ERR(leaf)) अणु
		ret = PTR_ERR(leaf);
		leaf = शून्य;
		जाओ fail_unlock;
	पूर्ण

	root->node = leaf;
	btrfs_mark_buffer_dirty(leaf);

	root->commit_root = btrfs_root_node(root);
	set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);

	btrfs_set_root_flags(&root->root_item, 0);
	btrfs_set_root_limit(&root->root_item, 0);
	btrfs_set_root_bytenr(&root->root_item, leaf->start);
	btrfs_set_root_generation(&root->root_item, trans->transid);
	btrfs_set_root_level(&root->root_item, 0);
	btrfs_set_root_refs(&root->root_item, 1);
	btrfs_set_root_used(&root->root_item, leaf->len);
	btrfs_set_root_last_snapshot(&root->root_item, 0);
	btrfs_set_root_dirid(&root->root_item, 0);
	अगर (is_fstree(objectid))
		generate_अक्रमom_guid(root->root_item.uuid);
	अन्यथा
		export_guid(root->root_item.uuid, &guid_null);
	btrfs_set_root_drop_level(&root->root_item, 0);

	btrfs_tree_unlock(leaf);

	key.objectid = objectid;
	key.type = BTRFS_ROOT_ITEM_KEY;
	key.offset = 0;
	ret = btrfs_insert_root(trans, tree_root, &key, &root->root_item);
	अगर (ret)
		जाओ fail;

	वापस root;

fail_unlock:
	अगर (leaf)
		btrfs_tree_unlock(leaf);
fail:
	btrfs_put_root(root);

	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा btrfs_root *alloc_log_tree(काष्ठा btrfs_trans_handle *trans,
					 काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root;

	root = btrfs_alloc_root(fs_info, BTRFS_TREE_LOG_OBJECTID, GFP_NOFS);
	अगर (!root)
		वापस ERR_PTR(-ENOMEM);

	root->root_key.objectid = BTRFS_TREE_LOG_OBJECTID;
	root->root_key.type = BTRFS_ROOT_ITEM_KEY;
	root->root_key.offset = BTRFS_TREE_LOG_OBJECTID;

	वापस root;
पूर्ण

पूर्णांक btrfs_alloc_log_tree_node(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_root *root)
अणु
	काष्ठा extent_buffer *leaf;

	/*
	 * DON'T set SHAREABLE bit क्रम log trees.
	 *
	 * Log trees are not exposed to user space thus can't be snapshotted,
	 * and they go away beक्रमe a real commit is actually करोne.
	 *
	 * They करो store poपूर्णांकers to file data extents, and those reference
	 * counts still get updated (aदीर्घ with back refs to the log tree).
	 */

	leaf = btrfs_alloc_tree_block(trans, root, 0, BTRFS_TREE_LOG_OBJECTID,
			शून्य, 0, 0, 0, BTRFS_NESTING_NORMAL);
	अगर (IS_ERR(leaf))
		वापस PTR_ERR(leaf);

	root->node = leaf;

	btrfs_mark_buffer_dirty(root->node);
	btrfs_tree_unlock(root->node);

	वापस 0;
पूर्ण

पूर्णांक btrfs_init_log_root_tree(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *log_root;

	log_root = alloc_log_tree(trans, fs_info);
	अगर (IS_ERR(log_root))
		वापस PTR_ERR(log_root);

	अगर (!btrfs_is_zoned(fs_info)) अणु
		पूर्णांक ret = btrfs_alloc_log_tree_node(trans, log_root);

		अगर (ret) अणु
			btrfs_put_root(log_root);
			वापस ret;
		पूर्ण
	पूर्ण

	WARN_ON(fs_info->log_root_tree);
	fs_info->log_root_tree = log_root;
	वापस 0;
पूर्ण

पूर्णांक btrfs_add_log_tree(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *log_root;
	काष्ठा btrfs_inode_item *inode_item;
	पूर्णांक ret;

	log_root = alloc_log_tree(trans, fs_info);
	अगर (IS_ERR(log_root))
		वापस PTR_ERR(log_root);

	ret = btrfs_alloc_log_tree_node(trans, log_root);
	अगर (ret) अणु
		btrfs_put_root(log_root);
		वापस ret;
	पूर्ण

	log_root->last_trans = trans->transid;
	log_root->root_key.offset = root->root_key.objectid;

	inode_item = &log_root->root_item.inode;
	btrfs_set_stack_inode_generation(inode_item, 1);
	btrfs_set_stack_inode_size(inode_item, 3);
	btrfs_set_stack_inode_nlink(inode_item, 1);
	btrfs_set_stack_inode_nbytes(inode_item,
				     fs_info->nodesize);
	btrfs_set_stack_inode_mode(inode_item, S_IFसूची | 0755);

	btrfs_set_root_node(&log_root->root_item, log_root->node);

	WARN_ON(root->log_root);
	root->log_root = log_root;
	root->log_transid = 0;
	root->log_transid_committed = -1;
	root->last_log_commit = 0;
	वापस 0;
पूर्ण

अटल काष्ठा btrfs_root *पढ़ो_tree_root_path(काष्ठा btrfs_root *tree_root,
					      काष्ठा btrfs_path *path,
					      काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_fs_info *fs_info = tree_root->fs_info;
	u64 generation;
	पूर्णांक ret;
	पूर्णांक level;

	root = btrfs_alloc_root(fs_info, key->objectid, GFP_NOFS);
	अगर (!root)
		वापस ERR_PTR(-ENOMEM);

	ret = btrfs_find_root(tree_root, key, path,
			      &root->root_item, &root->root_key);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -ENOENT;
		जाओ fail;
	पूर्ण

	generation = btrfs_root_generation(&root->root_item);
	level = btrfs_root_level(&root->root_item);
	root->node = पढ़ो_tree_block(fs_info,
				     btrfs_root_bytenr(&root->root_item),
				     key->objectid, generation, level, शून्य);
	अगर (IS_ERR(root->node)) अणु
		ret = PTR_ERR(root->node);
		root->node = शून्य;
		जाओ fail;
	पूर्ण अन्यथा अगर (!btrfs_buffer_uptodate(root->node, generation, 0)) अणु
		ret = -EIO;
		जाओ fail;
	पूर्ण
	root->commit_root = btrfs_root_node(root);
	वापस root;
fail:
	btrfs_put_root(root);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा btrfs_root *btrfs_पढ़ो_tree_root(काष्ठा btrfs_root *tree_root,
					काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_path *path;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस ERR_PTR(-ENOMEM);
	root = पढ़ो_tree_root_path(tree_root, path, key);
	btrfs_मुक्त_path(path);

	वापस root;
पूर्ण

/*
 * Initialize subvolume root in-memory काष्ठाure
 *
 * @anon_dev:	anonymous device to attach to the root, अगर zero, allocate new
 */
अटल पूर्णांक btrfs_init_fs_root(काष्ठा btrfs_root *root, dev_t anon_dev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक nofs_flag;

	/*
	 * We might be called under a transaction (e.g. indirect backref
	 * resolution) which could deadlock अगर it triggers memory reclaim
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	ret = btrfs_drew_lock_init(&root->snapshot_lock);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (ret)
		जाओ fail;

	अगर (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID &&
	    root->root_key.objectid != BTRFS_DATA_RELOC_TREE_OBJECTID) अणु
		set_bit(BTRFS_ROOT_SHAREABLE, &root->state);
		btrfs_check_and_init_root_item(&root->root_item);
	पूर्ण

	/*
	 * Don't assign anonymous block device to roots that are not exposed to
	 * userspace, the id pool is limited to 1M
	 */
	अगर (is_fstree(root->root_key.objectid) &&
	    btrfs_root_refs(&root->root_item) > 0) अणु
		अगर (!anon_dev) अणु
			ret = get_anon_bdev(&root->anon_dev);
			अगर (ret)
				जाओ fail;
		पूर्ण अन्यथा अणु
			root->anon_dev = anon_dev;
		पूर्ण
	पूर्ण

	mutex_lock(&root->objectid_mutex);
	ret = btrfs_init_root_मुक्त_objectid(root);
	अगर (ret) अणु
		mutex_unlock(&root->objectid_mutex);
		जाओ fail;
	पूर्ण

	ASSERT(root->मुक्त_objectid <= BTRFS_LAST_FREE_OBJECTID);

	mutex_unlock(&root->objectid_mutex);

	वापस 0;
fail:
	/* The caller is responsible to call btrfs_मुक्त_fs_root */
	वापस ret;
पूर्ण

अटल काष्ठा btrfs_root *btrfs_lookup_fs_root(काष्ठा btrfs_fs_info *fs_info,
					       u64 root_id)
अणु
	काष्ठा btrfs_root *root;

	spin_lock(&fs_info->fs_roots_radix_lock);
	root = radix_tree_lookup(&fs_info->fs_roots_radix,
				 (अचिन्हित दीर्घ)root_id);
	अगर (root)
		root = btrfs_grab_root(root);
	spin_unlock(&fs_info->fs_roots_radix_lock);
	वापस root;
पूर्ण

अटल काष्ठा btrfs_root *btrfs_get_global_root(काष्ठा btrfs_fs_info *fs_info,
						u64 objectid)
अणु
	अगर (objectid == BTRFS_ROOT_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->tree_root);
	अगर (objectid == BTRFS_EXTENT_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->extent_root);
	अगर (objectid == BTRFS_CHUNK_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->chunk_root);
	अगर (objectid == BTRFS_DEV_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->dev_root);
	अगर (objectid == BTRFS_CSUM_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->csum_root);
	अगर (objectid == BTRFS_QUOTA_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->quota_root) ?
			fs_info->quota_root : ERR_PTR(-ENOENT);
	अगर (objectid == BTRFS_UUID_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->uuid_root) ?
			fs_info->uuid_root : ERR_PTR(-ENOENT);
	अगर (objectid == BTRFS_FREE_SPACE_TREE_OBJECTID)
		वापस btrfs_grab_root(fs_info->मुक्त_space_root) ?
			fs_info->मुक्त_space_root : ERR_PTR(-ENOENT);
	वापस शून्य;
पूर्ण

पूर्णांक btrfs_insert_fs_root(काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा btrfs_root *root)
अणु
	पूर्णांक ret;

	ret = radix_tree_preload(GFP_NOFS);
	अगर (ret)
		वापस ret;

	spin_lock(&fs_info->fs_roots_radix_lock);
	ret = radix_tree_insert(&fs_info->fs_roots_radix,
				(अचिन्हित दीर्घ)root->root_key.objectid,
				root);
	अगर (ret == 0) अणु
		btrfs_grab_root(root);
		set_bit(BTRFS_ROOT_IN_RADIX, &root->state);
	पूर्ण
	spin_unlock(&fs_info->fs_roots_radix_lock);
	radix_tree_preload_end();

	वापस ret;
पूर्ण

व्योम btrfs_check_leaked_roots(काष्ठा btrfs_fs_info *fs_info)
अणु
#अगर_घोषित CONFIG_BTRFS_DEBUG
	काष्ठा btrfs_root *root;

	जबतक (!list_empty(&fs_info->allocated_roots)) अणु
		अक्षर buf[BTRFS_ROOT_NAME_BUF_LEN];

		root = list_first_entry(&fs_info->allocated_roots,
					काष्ठा btrfs_root, leak_list);
		btrfs_err(fs_info, "leaked root %s refcount %d",
			  btrfs_root_name(&root->root_key, buf),
			  refcount_पढ़ो(&root->refs));
		जबतक (refcount_पढ़ो(&root->refs) > 1)
			btrfs_put_root(root);
		btrfs_put_root(root);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम btrfs_मुक्त_fs_info(काष्ठा btrfs_fs_info *fs_info)
अणु
	percpu_counter_destroy(&fs_info->dirty_metadata_bytes);
	percpu_counter_destroy(&fs_info->delalloc_bytes);
	percpu_counter_destroy(&fs_info->ordered_bytes);
	percpu_counter_destroy(&fs_info->dev_replace.bio_counter);
	btrfs_मुक्त_csum_hash(fs_info);
	btrfs_मुक्त_stripe_hash_table(fs_info);
	btrfs_मुक्त_ref_cache(fs_info);
	kमुक्त(fs_info->balance_ctl);
	kमुक्त(fs_info->delayed_root);
	btrfs_put_root(fs_info->extent_root);
	btrfs_put_root(fs_info->tree_root);
	btrfs_put_root(fs_info->chunk_root);
	btrfs_put_root(fs_info->dev_root);
	btrfs_put_root(fs_info->csum_root);
	btrfs_put_root(fs_info->quota_root);
	btrfs_put_root(fs_info->uuid_root);
	btrfs_put_root(fs_info->मुक्त_space_root);
	btrfs_put_root(fs_info->fs_root);
	btrfs_put_root(fs_info->data_reloc_root);
	btrfs_check_leaked_roots(fs_info);
	btrfs_extent_buffer_leak_debug_check(fs_info);
	kमुक्त(fs_info->super_copy);
	kमुक्त(fs_info->super_क्रम_commit);
	kvमुक्त(fs_info);
पूर्ण


/*
 * Get an in-memory reference of a root काष्ठाure.
 *
 * For essential trees like root/extent tree, we grab it from fs_info directly.
 * For subvolume trees, we check the cached fileप्रणाली roots first. If not
 * found, then पढ़ो it from disk and add it to cached fs roots.
 *
 * Caller should release the root by calling btrfs_put_root() after the usage.
 *
 * NOTE: Reloc and log trees can't be पढ़ो by this function as they share the
 *	 same root objectid.
 *
 * @objectid:	root id
 * @anon_dev:	pपुनः_स्मृतिated anonymous block device number क्रम new roots,
 * 		pass 0 क्रम new allocation.
 * @check_ref:	whether to check root item references, If true, वापस -ENOENT
 *		क्रम orphan roots
 */
अटल काष्ठा btrfs_root *btrfs_get_root_ref(काष्ठा btrfs_fs_info *fs_info,
					     u64 objectid, dev_t anon_dev,
					     bool check_ref)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	root = btrfs_get_global_root(fs_info, objectid);
	अगर (root)
		वापस root;
again:
	root = btrfs_lookup_fs_root(fs_info, objectid);
	अगर (root) अणु
		/* Shouldn't get pपुनः_स्मृतिated anon_dev क्रम cached roots */
		ASSERT(!anon_dev);
		अगर (check_ref && btrfs_root_refs(&root->root_item) == 0) अणु
			btrfs_put_root(root);
			वापस ERR_PTR(-ENOENT);
		पूर्ण
		वापस root;
	पूर्ण

	key.objectid = objectid;
	key.type = BTRFS_ROOT_ITEM_KEY;
	key.offset = (u64)-1;
	root = btrfs_पढ़ो_tree_root(fs_info->tree_root, &key);
	अगर (IS_ERR(root))
		वापस root;

	अगर (check_ref && btrfs_root_refs(&root->root_item) == 0) अणु
		ret = -ENOENT;
		जाओ fail;
	पूर्ण

	ret = btrfs_init_fs_root(root, anon_dev);
	अगर (ret)
		जाओ fail;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = objectid;

	ret = btrfs_search_slot(शून्य, fs_info->tree_root, &key, path, 0, 0);
	btrfs_मुक्त_path(path);
	अगर (ret < 0)
		जाओ fail;
	अगर (ret == 0)
		set_bit(BTRFS_ROOT_ORPHAN_ITEM_INSERTED, &root->state);

	ret = btrfs_insert_fs_root(fs_info, root);
	अगर (ret) अणु
		btrfs_put_root(root);
		अगर (ret == -EEXIST)
			जाओ again;
		जाओ fail;
	पूर्ण
	वापस root;
fail:
	btrfs_put_root(root);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Get in-memory reference of a root काष्ठाure
 *
 * @objectid:	tree objectid
 * @check_ref:	अगर set, verअगरy that the tree exists and the item has at least
 *		one reference
 */
काष्ठा btrfs_root *btrfs_get_fs_root(काष्ठा btrfs_fs_info *fs_info,
				     u64 objectid, bool check_ref)
अणु
	वापस btrfs_get_root_ref(fs_info, objectid, 0, check_ref);
पूर्ण

/*
 * Get in-memory reference of a root काष्ठाure, created as new, optionally pass
 * the anonymous block device id
 *
 * @objectid:	tree objectid
 * @anon_dev:	अगर zero, allocate a new anonymous block device or use the
 *		parameter value
 */
काष्ठा btrfs_root *btrfs_get_new_fs_root(काष्ठा btrfs_fs_info *fs_info,
					 u64 objectid, dev_t anon_dev)
अणु
	वापस btrfs_get_root_ref(fs_info, objectid, anon_dev, true);
पूर्ण

/*
 * btrfs_get_fs_root_commit_root - वापस a root क्रम the given objectid
 * @fs_info:	the fs_info
 * @objectid:	the objectid we need to lookup
 *
 * This is exclusively used क्रम backref walking, and exists specअगरically because
 * of how qgroups करोes lookups.  Qgroups will करो a backref lookup at delayed ref
 * creation समय, which means we may have to पढ़ो the tree_root in order to look
 * up a fs root that is not in memory.  If the root is not in memory we will
 * पढ़ो the tree root commit root and look up the fs root from there.  This is a
 * temporary root, it will not be inserted पूर्णांकo the radix tree as it करोesn't
 * have the most uptodate inक्रमmation, it'll simply be discarded once the
 * backref code is finished using the root.
 */
काष्ठा btrfs_root *btrfs_get_fs_root_commit_root(काष्ठा btrfs_fs_info *fs_info,
						 काष्ठा btrfs_path *path,
						 u64 objectid)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;

	ASSERT(path->search_commit_root && path->skip_locking);

	/*
	 * This can वापस -ENOENT अगर we ask क्रम a root that करोesn't exist, but
	 * since this is called via the backref walking code we won't be looking
	 * up a root that करोesn't exist, unless there's corruption.  So अगर root
	 * != शून्य just वापस it.
	 */
	root = btrfs_get_global_root(fs_info, objectid);
	अगर (root)
		वापस root;

	root = btrfs_lookup_fs_root(fs_info, objectid);
	अगर (root)
		वापस root;

	key.objectid = objectid;
	key.type = BTRFS_ROOT_ITEM_KEY;
	key.offset = (u64)-1;
	root = पढ़ो_tree_root_path(fs_info->tree_root, path, &key);
	btrfs_release_path(path);

	वापस root;
पूर्ण

/*
 * called by the kthपढ़ो helper functions to finally call the bio end_io
 * functions.  This is where पढ़ो checksum verअगरication actually happens
 */
अटल व्योम end_workqueue_fn(काष्ठा btrfs_work *work)
अणु
	काष्ठा bio *bio;
	काष्ठा btrfs_end_io_wq *end_io_wq;

	end_io_wq = container_of(work, काष्ठा btrfs_end_io_wq, work);
	bio = end_io_wq->bio;

	bio->bi_status = end_io_wq->status;
	bio->bi_निजी = end_io_wq->निजी;
	bio->bi_end_io = end_io_wq->end_io;
	bio_endio(bio);
	kmem_cache_मुक्त(btrfs_end_io_wq_cache, end_io_wq);
पूर्ण

अटल पूर्णांक cleaner_kthपढ़ो(व्योम *arg)
अणु
	काष्ठा btrfs_root *root = arg;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक again;

	जबतक (1) अणु
		again = 0;

		set_bit(BTRFS_FS_CLEANER_RUNNING, &fs_info->flags);

		/* Make the cleaner go to sleep early. */
		अगर (btrfs_need_cleaner_sleep(fs_info))
			जाओ sleep;

		/*
		 * Do not करो anything अगर we might cause खोलो_ctree() to block
		 * beक्रमe we have finished mounting the fileप्रणाली.
		 */
		अगर (!test_bit(BTRFS_FS_OPEN, &fs_info->flags))
			जाओ sleep;

		अगर (!mutex_trylock(&fs_info->cleaner_mutex))
			जाओ sleep;

		/*
		 * Aव्योम the problem that we change the status of the fs
		 * during the above check and trylock.
		 */
		अगर (btrfs_need_cleaner_sleep(fs_info)) अणु
			mutex_unlock(&fs_info->cleaner_mutex);
			जाओ sleep;
		पूर्ण

		btrfs_run_delayed_iमाला_दो(fs_info);

		again = btrfs_clean_one_deleted_snapshot(root);
		mutex_unlock(&fs_info->cleaner_mutex);

		/*
		 * The defragger has dealt with the R/O remount and umount,
		 * needn't करो anything special here.
		 */
		btrfs_run_defrag_inodes(fs_info);

		/*
		 * Acquires fs_info->reclaim_bgs_lock to aव्योम racing
		 * with relocation (btrfs_relocate_chunk) and relocation
		 * acquires fs_info->cleaner_mutex (btrfs_relocate_block_group)
		 * after acquiring fs_info->reclaim_bgs_lock. So we
		 * can't hold, nor need to, fs_info->cleaner_mutex when deleting
		 * unused block groups.
		 */
		btrfs_delete_unused_bgs(fs_info);

		/*
		 * Reclaim block groups in the reclaim_bgs list after we deleted
		 * all unused block_groups. This possibly gives us some more मुक्त
		 * space.
		 */
		btrfs_reclaim_bgs(fs_info);
sleep:
		clear_and_wake_up_bit(BTRFS_FS_CLEANER_RUNNING, &fs_info->flags);
		अगर (kthपढ़ो_should_park())
			kthपढ़ो_parkme();
		अगर (kthपढ़ो_should_stop())
			वापस 0;
		अगर (!again) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			schedule();
			__set_current_state(TASK_RUNNING);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक transaction_kthपढ़ो(व्योम *arg)
अणु
	काष्ठा btrfs_root *root = arg;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_transaction *cur;
	u64 transid;
	समय64_t delta;
	अचिन्हित दीर्घ delay;
	bool cannot_commit;

	करो अणु
		cannot_commit = false;
		delay = msecs_to_jअगरfies(fs_info->commit_पूर्णांकerval * 1000);
		mutex_lock(&fs_info->transaction_kthपढ़ो_mutex);

		spin_lock(&fs_info->trans_lock);
		cur = fs_info->running_transaction;
		अगर (!cur) अणु
			spin_unlock(&fs_info->trans_lock);
			जाओ sleep;
		पूर्ण

		delta = kसमय_get_seconds() - cur->start_समय;
		अगर (cur->state < TRANS_STATE_COMMIT_START &&
		    delta < fs_info->commit_पूर्णांकerval) अणु
			spin_unlock(&fs_info->trans_lock);
			delay -= msecs_to_jअगरfies((delta - 1) * 1000);
			delay = min(delay,
				    msecs_to_jअगरfies(fs_info->commit_पूर्णांकerval * 1000));
			जाओ sleep;
		पूर्ण
		transid = cur->transid;
		spin_unlock(&fs_info->trans_lock);

		/* If the file प्रणाली is पातed, this will always fail. */
		trans = btrfs_attach_transaction(root);
		अगर (IS_ERR(trans)) अणु
			अगर (PTR_ERR(trans) != -ENOENT)
				cannot_commit = true;
			जाओ sleep;
		पूर्ण
		अगर (transid == trans->transid) अणु
			btrfs_commit_transaction(trans);
		पूर्ण अन्यथा अणु
			btrfs_end_transaction(trans);
		पूर्ण
sleep:
		wake_up_process(fs_info->cleaner_kthपढ़ो);
		mutex_unlock(&fs_info->transaction_kthपढ़ो_mutex);

		अगर (unlikely(test_bit(BTRFS_FS_STATE_ERROR,
				      &fs_info->fs_state)))
			btrfs_cleanup_transaction(fs_info);
		अगर (!kthपढ़ो_should_stop() &&
				(!btrfs_transaction_blocked(fs_info) ||
				 cannot_commit))
			schedule_समयout_पूर्णांकerruptible(delay);
	पूर्ण जबतक (!kthपढ़ो_should_stop());
	वापस 0;
पूर्ण

/*
 * This will find the highest generation in the array of root backups.  The
 * index of the highest array is वापसed, or -EINVAL अगर we can't find
 * anything.
 *
 * We check to make sure the array is valid by comparing the
 * generation of the latest  root in the array with the generation
 * in the super block.  If they करोn't match we pitch it.
 */
अटल पूर्णांक find_newest_super_backup(काष्ठा btrfs_fs_info *info)
अणु
	स्थिर u64 newest_gen = btrfs_super_generation(info->super_copy);
	u64 cur;
	काष्ठा btrfs_root_backup *root_backup;
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_NUM_BACKUP_ROOTS; i++) अणु
		root_backup = info->super_copy->super_roots + i;
		cur = btrfs_backup_tree_root_gen(root_backup);
		अगर (cur == newest_gen)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * copy all the root poपूर्णांकers पूर्णांकo the super backup array.
 * this will bump the backup poपूर्णांकer by one when it is
 * करोne
 */
अटल व्योम backup_super_roots(काष्ठा btrfs_fs_info *info)
अणु
	स्थिर पूर्णांक next_backup = info->backup_root_index;
	काष्ठा btrfs_root_backup *root_backup;

	root_backup = info->super_क्रम_commit->super_roots + next_backup;

	/*
	 * make sure all of our padding and empty slots get zero filled
	 * regardless of which ones we use today
	 */
	स_रखो(root_backup, 0, माप(*root_backup));

	info->backup_root_index = (next_backup + 1) % BTRFS_NUM_BACKUP_ROOTS;

	btrfs_set_backup_tree_root(root_backup, info->tree_root->node->start);
	btrfs_set_backup_tree_root_gen(root_backup,
			       btrfs_header_generation(info->tree_root->node));

	btrfs_set_backup_tree_root_level(root_backup,
			       btrfs_header_level(info->tree_root->node));

	btrfs_set_backup_chunk_root(root_backup, info->chunk_root->node->start);
	btrfs_set_backup_chunk_root_gen(root_backup,
			       btrfs_header_generation(info->chunk_root->node));
	btrfs_set_backup_chunk_root_level(root_backup,
			       btrfs_header_level(info->chunk_root->node));

	btrfs_set_backup_extent_root(root_backup, info->extent_root->node->start);
	btrfs_set_backup_extent_root_gen(root_backup,
			       btrfs_header_generation(info->extent_root->node));
	btrfs_set_backup_extent_root_level(root_backup,
			       btrfs_header_level(info->extent_root->node));

	/*
	 * we might commit during log recovery, which happens beक्रमe we set
	 * the fs_root.  Make sure it is valid beक्रमe we fill it in.
	 */
	अगर (info->fs_root && info->fs_root->node) अणु
		btrfs_set_backup_fs_root(root_backup,
					 info->fs_root->node->start);
		btrfs_set_backup_fs_root_gen(root_backup,
			       btrfs_header_generation(info->fs_root->node));
		btrfs_set_backup_fs_root_level(root_backup,
			       btrfs_header_level(info->fs_root->node));
	पूर्ण

	btrfs_set_backup_dev_root(root_backup, info->dev_root->node->start);
	btrfs_set_backup_dev_root_gen(root_backup,
			       btrfs_header_generation(info->dev_root->node));
	btrfs_set_backup_dev_root_level(root_backup,
				       btrfs_header_level(info->dev_root->node));

	btrfs_set_backup_csum_root(root_backup, info->csum_root->node->start);
	btrfs_set_backup_csum_root_gen(root_backup,
			       btrfs_header_generation(info->csum_root->node));
	btrfs_set_backup_csum_root_level(root_backup,
			       btrfs_header_level(info->csum_root->node));

	btrfs_set_backup_total_bytes(root_backup,
			     btrfs_super_total_bytes(info->super_copy));
	btrfs_set_backup_bytes_used(root_backup,
			     btrfs_super_bytes_used(info->super_copy));
	btrfs_set_backup_num_devices(root_backup,
			     btrfs_super_num_devices(info->super_copy));

	/*
	 * अगर we करोn't copy this out to the super_copy, it won't get remembered
	 * क्रम the next commit
	 */
	स_नकल(&info->super_copy->super_roots,
	       &info->super_क्रम_commit->super_roots,
	       माप(*root_backup) * BTRFS_NUM_BACKUP_ROOTS);
पूर्ण

/*
 * पढ़ो_backup_root - Reads a backup root based on the passed priority. Prio 0
 * is the newest, prio 1/2/3 are 2nd newest/3rd newest/4th (oldest) backup roots
 *
 * fs_info - fileप्रणाली whose backup roots need to be पढ़ो
 * priority - priority of backup root required
 *
 * Returns backup root index on success and -EINVAL otherwise.
 */
अटल पूर्णांक पढ़ो_backup_root(काष्ठा btrfs_fs_info *fs_info, u8 priority)
अणु
	पूर्णांक backup_index = find_newest_super_backup(fs_info);
	काष्ठा btrfs_super_block *super = fs_info->super_copy;
	काष्ठा btrfs_root_backup *root_backup;

	अगर (priority < BTRFS_NUM_BACKUP_ROOTS && backup_index >= 0) अणु
		अगर (priority == 0)
			वापस backup_index;

		backup_index = backup_index + BTRFS_NUM_BACKUP_ROOTS - priority;
		backup_index %= BTRFS_NUM_BACKUP_ROOTS;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	root_backup = super->super_roots + backup_index;

	btrfs_set_super_generation(super,
				   btrfs_backup_tree_root_gen(root_backup));
	btrfs_set_super_root(super, btrfs_backup_tree_root(root_backup));
	btrfs_set_super_root_level(super,
				   btrfs_backup_tree_root_level(root_backup));
	btrfs_set_super_bytes_used(super, btrfs_backup_bytes_used(root_backup));

	/*
	 * Fixme: the total bytes and num_devices need to match or we should
	 * need a fsck
	 */
	btrfs_set_super_total_bytes(super, btrfs_backup_total_bytes(root_backup));
	btrfs_set_super_num_devices(super, btrfs_backup_num_devices(root_backup));

	वापस backup_index;
पूर्ण

/* helper to cleanup workers */
अटल व्योम btrfs_stop_all_workers(काष्ठा btrfs_fs_info *fs_info)
अणु
	btrfs_destroy_workqueue(fs_info->fixup_workers);
	btrfs_destroy_workqueue(fs_info->delalloc_workers);
	btrfs_destroy_workqueue(fs_info->workers);
	btrfs_destroy_workqueue(fs_info->endio_workers);
	btrfs_destroy_workqueue(fs_info->endio_raid56_workers);
	btrfs_destroy_workqueue(fs_info->rmw_workers);
	btrfs_destroy_workqueue(fs_info->endio_ग_लिखो_workers);
	btrfs_destroy_workqueue(fs_info->endio_मुक्तspace_worker);
	btrfs_destroy_workqueue(fs_info->delayed_workers);
	btrfs_destroy_workqueue(fs_info->caching_workers);
	btrfs_destroy_workqueue(fs_info->पढ़ोahead_workers);
	btrfs_destroy_workqueue(fs_info->flush_workers);
	btrfs_destroy_workqueue(fs_info->qgroup_rescan_workers);
	अगर (fs_info->discard_ctl.discard_workers)
		destroy_workqueue(fs_info->discard_ctl.discard_workers);
	/*
	 * Now that all other work queues are destroyed, we can safely destroy
	 * the queues used क्रम metadata I/O, since tasks from those other work
	 * queues can करो metadata I/O operations.
	 */
	btrfs_destroy_workqueue(fs_info->endio_meta_workers);
	btrfs_destroy_workqueue(fs_info->endio_meta_ग_लिखो_workers);
पूर्ण

अटल व्योम मुक्त_root_extent_buffers(काष्ठा btrfs_root *root)
अणु
	अगर (root) अणु
		मुक्त_extent_buffer(root->node);
		मुक्त_extent_buffer(root->commit_root);
		root->node = शून्य;
		root->commit_root = शून्य;
	पूर्ण
पूर्ण

/* helper to cleanup tree roots */
अटल व्योम मुक्त_root_poपूर्णांकers(काष्ठा btrfs_fs_info *info, bool मुक्त_chunk_root)
अणु
	मुक्त_root_extent_buffers(info->tree_root);

	मुक्त_root_extent_buffers(info->dev_root);
	मुक्त_root_extent_buffers(info->extent_root);
	मुक्त_root_extent_buffers(info->csum_root);
	मुक्त_root_extent_buffers(info->quota_root);
	मुक्त_root_extent_buffers(info->uuid_root);
	मुक्त_root_extent_buffers(info->fs_root);
	मुक्त_root_extent_buffers(info->data_reloc_root);
	अगर (मुक्त_chunk_root)
		मुक्त_root_extent_buffers(info->chunk_root);
	मुक्त_root_extent_buffers(info->मुक्त_space_root);
पूर्ण

व्योम btrfs_put_root(काष्ठा btrfs_root *root)
अणु
	अगर (!root)
		वापस;

	अगर (refcount_dec_and_test(&root->refs)) अणु
		WARN_ON(!RB_EMPTY_ROOT(&root->inode_tree));
		WARN_ON(test_bit(BTRFS_ROOT_DEAD_RELOC_TREE, &root->state));
		अगर (root->anon_dev)
			मुक्त_anon_bdev(root->anon_dev);
		btrfs_drew_lock_destroy(&root->snapshot_lock);
		मुक्त_root_extent_buffers(root);
#अगर_घोषित CONFIG_BTRFS_DEBUG
		spin_lock(&root->fs_info->fs_roots_radix_lock);
		list_del_init(&root->leak_list);
		spin_unlock(&root->fs_info->fs_roots_radix_lock);
#पूर्ण_अगर
		kमुक्त(root);
	पूर्ण
पूर्ण

व्योम btrfs_मुक्त_fs_roots(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *gang[8];
	पूर्णांक i;

	जबतक (!list_empty(&fs_info->dead_roots)) अणु
		gang[0] = list_entry(fs_info->dead_roots.next,
				     काष्ठा btrfs_root, root_list);
		list_del(&gang[0]->root_list);

		अगर (test_bit(BTRFS_ROOT_IN_RADIX, &gang[0]->state))
			btrfs_drop_and_मुक्त_fs_root(fs_info, gang[0]);
		btrfs_put_root(gang[0]);
	पूर्ण

	जबतक (1) अणु
		ret = radix_tree_gang_lookup(&fs_info->fs_roots_radix,
					     (व्योम **)gang, 0,
					     ARRAY_SIZE(gang));
		अगर (!ret)
			अवरोध;
		क्रम (i = 0; i < ret; i++)
			btrfs_drop_and_मुक्त_fs_root(fs_info, gang[i]);
	पूर्ण
पूर्ण

अटल व्योम btrfs_init_scrub(काष्ठा btrfs_fs_info *fs_info)
अणु
	mutex_init(&fs_info->scrub_lock);
	atomic_set(&fs_info->scrubs_running, 0);
	atomic_set(&fs_info->scrub_छोड़ो_req, 0);
	atomic_set(&fs_info->scrubs_छोड़ोd, 0);
	atomic_set(&fs_info->scrub_cancel_req, 0);
	init_रुकोqueue_head(&fs_info->scrub_छोड़ो_रुको);
	refcount_set(&fs_info->scrub_workers_refcnt, 0);
पूर्ण

अटल व्योम btrfs_init_balance(काष्ठा btrfs_fs_info *fs_info)
अणु
	spin_lock_init(&fs_info->balance_lock);
	mutex_init(&fs_info->balance_mutex);
	atomic_set(&fs_info->balance_छोड़ो_req, 0);
	atomic_set(&fs_info->balance_cancel_req, 0);
	fs_info->balance_ctl = शून्य;
	init_रुकोqueue_head(&fs_info->balance_रुको_q);
पूर्ण

अटल व्योम btrfs_init_btree_inode(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा inode *inode = fs_info->btree_inode;

	inode->i_ino = BTRFS_BTREE_INODE_OBJECTID;
	set_nlink(inode, 1);
	/*
	 * we set the i_size on the btree inode to the max possible पूर्णांक.
	 * the real end of the address space is determined by all of
	 * the devices in the प्रणाली
	 */
	inode->i_size = OFFSET_MAX;
	inode->i_mapping->a_ops = &btree_aops;

	RB_CLEAR_NODE(&BTRFS_I(inode)->rb_node);
	extent_io_tree_init(fs_info, &BTRFS_I(inode)->io_tree,
			    IO_TREE_BTREE_INODE_IO, inode);
	BTRFS_I(inode)->io_tree.track_uptodate = false;
	extent_map_tree_init(&BTRFS_I(inode)->extent_tree);

	BTRFS_I(inode)->root = btrfs_grab_root(fs_info->tree_root);
	स_रखो(&BTRFS_I(inode)->location, 0, माप(काष्ठा btrfs_key));
	set_bit(BTRFS_INODE_DUMMY, &BTRFS_I(inode)->runसमय_flags);
	btrfs_insert_inode_hash(inode);
पूर्ण

अटल व्योम btrfs_init_dev_replace_locks(काष्ठा btrfs_fs_info *fs_info)
अणु
	mutex_init(&fs_info->dev_replace.lock_finishing_cancel_unmount);
	init_rwsem(&fs_info->dev_replace.rwsem);
	init_रुकोqueue_head(&fs_info->dev_replace.replace_रुको);
पूर्ण

अटल व्योम btrfs_init_qgroup(काष्ठा btrfs_fs_info *fs_info)
अणु
	spin_lock_init(&fs_info->qgroup_lock);
	mutex_init(&fs_info->qgroup_ioctl_lock);
	fs_info->qgroup_tree = RB_ROOT;
	INIT_LIST_HEAD(&fs_info->dirty_qgroups);
	fs_info->qgroup_seq = 1;
	fs_info->qgroup_ulist = शून्य;
	fs_info->qgroup_rescan_running = false;
	mutex_init(&fs_info->qgroup_rescan_lock);
पूर्ण

अटल पूर्णांक btrfs_init_workqueues(काष्ठा btrfs_fs_info *fs_info,
		काष्ठा btrfs_fs_devices *fs_devices)
अणु
	u32 max_active = fs_info->thपढ़ो_pool_size;
	अचिन्हित पूर्णांक flags = WQ_MEM_RECLAIM | WQ_FREEZABLE | WQ_UNBOUND;

	fs_info->workers =
		btrfs_alloc_workqueue(fs_info, "worker",
				      flags | WQ_HIGHPRI, max_active, 16);

	fs_info->delalloc_workers =
		btrfs_alloc_workqueue(fs_info, "delalloc",
				      flags, max_active, 2);

	fs_info->flush_workers =
		btrfs_alloc_workqueue(fs_info, "flush_delalloc",
				      flags, max_active, 0);

	fs_info->caching_workers =
		btrfs_alloc_workqueue(fs_info, "cache", flags, max_active, 0);

	fs_info->fixup_workers =
		btrfs_alloc_workqueue(fs_info, "fixup", flags, 1, 0);

	/*
	 * endios are largely parallel and should have a very
	 * low idle thresh
	 */
	fs_info->endio_workers =
		btrfs_alloc_workqueue(fs_info, "endio", flags, max_active, 4);
	fs_info->endio_meta_workers =
		btrfs_alloc_workqueue(fs_info, "endio-meta", flags,
				      max_active, 4);
	fs_info->endio_meta_ग_लिखो_workers =
		btrfs_alloc_workqueue(fs_info, "endio-meta-write", flags,
				      max_active, 2);
	fs_info->endio_raid56_workers =
		btrfs_alloc_workqueue(fs_info, "endio-raid56", flags,
				      max_active, 4);
	fs_info->rmw_workers =
		btrfs_alloc_workqueue(fs_info, "rmw", flags, max_active, 2);
	fs_info->endio_ग_लिखो_workers =
		btrfs_alloc_workqueue(fs_info, "endio-write", flags,
				      max_active, 2);
	fs_info->endio_मुक्तspace_worker =
		btrfs_alloc_workqueue(fs_info, "freespace-write", flags,
				      max_active, 0);
	fs_info->delayed_workers =
		btrfs_alloc_workqueue(fs_info, "delayed-meta", flags,
				      max_active, 0);
	fs_info->पढ़ोahead_workers =
		btrfs_alloc_workqueue(fs_info, "readahead", flags,
				      max_active, 2);
	fs_info->qgroup_rescan_workers =
		btrfs_alloc_workqueue(fs_info, "qgroup-rescan", flags, 1, 0);
	fs_info->discard_ctl.discard_workers =
		alloc_workqueue("btrfs_discard", WQ_UNBOUND | WQ_FREEZABLE, 1);

	अगर (!(fs_info->workers && fs_info->delalloc_workers &&
	      fs_info->flush_workers &&
	      fs_info->endio_workers && fs_info->endio_meta_workers &&
	      fs_info->endio_meta_ग_लिखो_workers &&
	      fs_info->endio_ग_लिखो_workers && fs_info->endio_raid56_workers &&
	      fs_info->endio_मुक्तspace_worker && fs_info->rmw_workers &&
	      fs_info->caching_workers && fs_info->पढ़ोahead_workers &&
	      fs_info->fixup_workers && fs_info->delayed_workers &&
	      fs_info->qgroup_rescan_workers &&
	      fs_info->discard_ctl.discard_workers)) अणु
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_init_csum_hash(काष्ठा btrfs_fs_info *fs_info, u16 csum_type)
अणु
	काष्ठा crypto_shash *csum_shash;
	स्थिर अक्षर *csum_driver = btrfs_super_csum_driver(csum_type);

	csum_shash = crypto_alloc_shash(csum_driver, 0, 0);

	अगर (IS_ERR(csum_shash)) अणु
		btrfs_err(fs_info, "error allocating %s hash for checksum",
			  csum_driver);
		वापस PTR_ERR(csum_shash);
	पूर्ण

	fs_info->csum_shash = csum_shash;

	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_replay_log(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_fs_devices *fs_devices)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *log_tree_root;
	काष्ठा btrfs_super_block *disk_super = fs_info->super_copy;
	u64 bytenr = btrfs_super_log_root(disk_super);
	पूर्णांक level = btrfs_super_log_root_level(disk_super);

	अगर (fs_devices->rw_devices == 0) अणु
		btrfs_warn(fs_info, "log replay required on RO media");
		वापस -EIO;
	पूर्ण

	log_tree_root = btrfs_alloc_root(fs_info, BTRFS_TREE_LOG_OBJECTID,
					 GFP_KERNEL);
	अगर (!log_tree_root)
		वापस -ENOMEM;

	log_tree_root->node = पढ़ो_tree_block(fs_info, bytenr,
					      BTRFS_TREE_LOG_OBJECTID,
					      fs_info->generation + 1, level,
					      शून्य);
	अगर (IS_ERR(log_tree_root->node)) अणु
		btrfs_warn(fs_info, "failed to read log tree");
		ret = PTR_ERR(log_tree_root->node);
		log_tree_root->node = शून्य;
		btrfs_put_root(log_tree_root);
		वापस ret;
	पूर्ण अन्यथा अगर (!extent_buffer_uptodate(log_tree_root->node)) अणु
		btrfs_err(fs_info, "failed to read log tree");
		btrfs_put_root(log_tree_root);
		वापस -EIO;
	पूर्ण
	/* वापसs with log_tree_root मुक्तd on success */
	ret = btrfs_recover_log_trees(log_tree_root);
	अगर (ret) अणु
		btrfs_handle_fs_error(fs_info, ret,
				      "Failed to recover log tree");
		btrfs_put_root(log_tree_root);
		वापस ret;
	पूर्ण

	अगर (sb_rकरोnly(fs_info->sb)) अणु
		ret = btrfs_commit_super(fs_info);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_पढ़ो_roots(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key location;
	पूर्णांक ret;

	BUG_ON(!fs_info->tree_root);

	location.objectid = BTRFS_EXTENT_TREE_OBJECTID;
	location.type = BTRFS_ROOT_ITEM_KEY;
	location.offset = 0;

	root = btrfs_पढ़ो_tree_root(tree_root, &location);
	अगर (IS_ERR(root)) अणु
		अगर (!btrfs_test_opt(fs_info, IGNOREBADROOTS)) अणु
			ret = PTR_ERR(root);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);
		fs_info->extent_root = root;
	पूर्ण

	location.objectid = BTRFS_DEV_TREE_OBJECTID;
	root = btrfs_पढ़ो_tree_root(tree_root, &location);
	अगर (IS_ERR(root)) अणु
		अगर (!btrfs_test_opt(fs_info, IGNOREBADROOTS)) अणु
			ret = PTR_ERR(root);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);
		fs_info->dev_root = root;
	पूर्ण
	/* Initialize fs_info क्रम all devices in any हाल */
	btrfs_init_devices_late(fs_info);

	/* If IGNOREDATACSUMS is set करोn't bother पढ़ोing the csum root. */
	अगर (!btrfs_test_opt(fs_info, IGNOREDATACSUMS)) अणु
		location.objectid = BTRFS_CSUM_TREE_OBJECTID;
		root = btrfs_पढ़ो_tree_root(tree_root, &location);
		अगर (IS_ERR(root)) अणु
			अगर (!btrfs_test_opt(fs_info, IGNOREBADROOTS)) अणु
				ret = PTR_ERR(root);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);
			fs_info->csum_root = root;
		पूर्ण
	पूर्ण

	/*
	 * This tree can share blocks with some other fs tree during relocation
	 * and we need a proper setup by btrfs_get_fs_root
	 */
	root = btrfs_get_fs_root(tree_root->fs_info,
				 BTRFS_DATA_RELOC_TREE_OBJECTID, true);
	अगर (IS_ERR(root)) अणु
		अगर (!btrfs_test_opt(fs_info, IGNOREBADROOTS)) अणु
			ret = PTR_ERR(root);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);
		fs_info->data_reloc_root = root;
	पूर्ण

	location.objectid = BTRFS_QUOTA_TREE_OBJECTID;
	root = btrfs_पढ़ो_tree_root(tree_root, &location);
	अगर (!IS_ERR(root)) अणु
		set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);
		set_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags);
		fs_info->quota_root = root;
	पूर्ण

	location.objectid = BTRFS_UUID_TREE_OBJECTID;
	root = btrfs_पढ़ो_tree_root(tree_root, &location);
	अगर (IS_ERR(root)) अणु
		अगर (!btrfs_test_opt(fs_info, IGNOREBADROOTS)) अणु
			ret = PTR_ERR(root);
			अगर (ret != -ENOENT)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);
		fs_info->uuid_root = root;
	पूर्ण

	अगर (btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE)) अणु
		location.objectid = BTRFS_FREE_SPACE_TREE_OBJECTID;
		root = btrfs_पढ़ो_tree_root(tree_root, &location);
		अगर (IS_ERR(root)) अणु
			अगर (!btrfs_test_opt(fs_info, IGNOREBADROOTS)) अणु
				ret = PTR_ERR(root);
				जाओ out;
			पूर्ण
		पूर्ण  अन्यथा अणु
			set_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state);
			fs_info->मुक्त_space_root = root;
		पूर्ण
	पूर्ण

	वापस 0;
out:
	btrfs_warn(fs_info, "failed to read root (objectid=%llu): %d",
		   location.objectid, ret);
	वापस ret;
पूर्ण

/*
 * Real super block validation
 * NOTE: super csum type and incompat features will not be checked here.
 *
 * @sb:		super block to check
 * @mirror_num:	the super block number to check its bytenr:
 * 		0	the primary (1st) sb
 * 		1, 2	2nd and 3rd backup copy
 * 	       -1	skip bytenr check
 */
अटल पूर्णांक validate_super(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_super_block *sb, पूर्णांक mirror_num)
अणु
	u64 nodesize = btrfs_super_nodesize(sb);
	u64 sectorsize = btrfs_super_sectorsize(sb);
	पूर्णांक ret = 0;

	अगर (btrfs_super_magic(sb) != BTRFS_MAGIC) अणु
		btrfs_err(fs_info, "no valid FS found");
		ret = -EINVAL;
	पूर्ण
	अगर (btrfs_super_flags(sb) & ~BTRFS_SUPER_FLAG_SUPP) अणु
		btrfs_err(fs_info, "unrecognized or unsupported super flag: %llu",
				btrfs_super_flags(sb) & ~BTRFS_SUPER_FLAG_SUPP);
		ret = -EINVAL;
	पूर्ण
	अगर (btrfs_super_root_level(sb) >= BTRFS_MAX_LEVEL) अणु
		btrfs_err(fs_info, "tree_root level too big: %d >= %d",
				btrfs_super_root_level(sb), BTRFS_MAX_LEVEL);
		ret = -EINVAL;
	पूर्ण
	अगर (btrfs_super_chunk_root_level(sb) >= BTRFS_MAX_LEVEL) अणु
		btrfs_err(fs_info, "chunk_root level too big: %d >= %d",
				btrfs_super_chunk_root_level(sb), BTRFS_MAX_LEVEL);
		ret = -EINVAL;
	पूर्ण
	अगर (btrfs_super_log_root_level(sb) >= BTRFS_MAX_LEVEL) अणु
		btrfs_err(fs_info, "log_root level too big: %d >= %d",
				btrfs_super_log_root_level(sb), BTRFS_MAX_LEVEL);
		ret = -EINVAL;
	पूर्ण

	/*
	 * Check sectorsize and nodesize first, other check will need it.
	 * Check all possible sectorsize(4K, 8K, 16K, 32K, 64K) here.
	 */
	अगर (!is_घातer_of_2(sectorsize) || sectorsize < 4096 ||
	    sectorsize > BTRFS_MAX_METADATA_BLOCKSIZE) अणु
		btrfs_err(fs_info, "invalid sectorsize %llu", sectorsize);
		ret = -EINVAL;
	पूर्ण

	/*
	 * For 4K page size, we only support 4K sector size.
	 * For 64K page size, we support पढ़ो-ग_लिखो क्रम 64K sector size, and
	 * पढ़ो-only क्रम 4K sector size.
	 */
	अगर ((PAGE_SIZE == SZ_4K && sectorsize != PAGE_SIZE) ||
	    (PAGE_SIZE == SZ_64K && (sectorsize != SZ_4K &&
				     sectorsize != SZ_64K))) अणु
		btrfs_err(fs_info,
			"sectorsize %llu not yet supported for page size %lu",
			sectorsize, PAGE_SIZE);
		ret = -EINVAL;
	पूर्ण

	अगर (!is_घातer_of_2(nodesize) || nodesize < sectorsize ||
	    nodesize > BTRFS_MAX_METADATA_BLOCKSIZE) अणु
		btrfs_err(fs_info, "invalid nodesize %llu", nodesize);
		ret = -EINVAL;
	पूर्ण
	अगर (nodesize != le32_to_cpu(sb->__unused_leafsize)) अणु
		btrfs_err(fs_info, "invalid leafsize %u, should be %llu",
			  le32_to_cpu(sb->__unused_leafsize), nodesize);
		ret = -EINVAL;
	पूर्ण

	/* Root alignment check */
	अगर (!IS_ALIGNED(btrfs_super_root(sb), sectorsize)) अणु
		btrfs_warn(fs_info, "tree_root block unaligned: %llu",
			   btrfs_super_root(sb));
		ret = -EINVAL;
	पूर्ण
	अगर (!IS_ALIGNED(btrfs_super_chunk_root(sb), sectorsize)) अणु
		btrfs_warn(fs_info, "chunk_root block unaligned: %llu",
			   btrfs_super_chunk_root(sb));
		ret = -EINVAL;
	पूर्ण
	अगर (!IS_ALIGNED(btrfs_super_log_root(sb), sectorsize)) अणु
		btrfs_warn(fs_info, "log_root block unaligned: %llu",
			   btrfs_super_log_root(sb));
		ret = -EINVAL;
	पूर्ण

	अगर (स_भेद(fs_info->fs_devices->fsid, fs_info->super_copy->fsid,
		   BTRFS_FSID_SIZE)) अणु
		btrfs_err(fs_info,
		"superblock fsid doesn't match fsid of fs_devices: %pU != %pU",
			fs_info->super_copy->fsid, fs_info->fs_devices->fsid);
		ret = -EINVAL;
	पूर्ण

	अगर (btrfs_fs_incompat(fs_info, METADATA_UUID) &&
	    स_भेद(fs_info->fs_devices->metadata_uuid,
		   fs_info->super_copy->metadata_uuid, BTRFS_FSID_SIZE)) अणु
		btrfs_err(fs_info,
"superblock metadata_uuid doesn't match metadata uuid of fs_devices: %pU != %pU",
			fs_info->super_copy->metadata_uuid,
			fs_info->fs_devices->metadata_uuid);
		ret = -EINVAL;
	पूर्ण

	अगर (स_भेद(fs_info->fs_devices->metadata_uuid, sb->dev_item.fsid,
		   BTRFS_FSID_SIZE) != 0) अणु
		btrfs_err(fs_info,
			"dev_item UUID does not match metadata fsid: %pU != %pU",
			fs_info->fs_devices->metadata_uuid, sb->dev_item.fsid);
		ret = -EINVAL;
	पूर्ण

	/*
	 * Hपूर्णांक to catch really bogus numbers, bitflips or so, more exact checks are
	 * करोne later
	 */
	अगर (btrfs_super_bytes_used(sb) < 6 * btrfs_super_nodesize(sb)) अणु
		btrfs_err(fs_info, "bytes_used is too small %llu",
			  btrfs_super_bytes_used(sb));
		ret = -EINVAL;
	पूर्ण
	अगर (!is_घातer_of_2(btrfs_super_stripesize(sb))) अणु
		btrfs_err(fs_info, "invalid stripesize %u",
			  btrfs_super_stripesize(sb));
		ret = -EINVAL;
	पूर्ण
	अगर (btrfs_super_num_devices(sb) > (1UL << 31))
		btrfs_warn(fs_info, "suspicious number of devices: %llu",
			   btrfs_super_num_devices(sb));
	अगर (btrfs_super_num_devices(sb) == 0) अणु
		btrfs_err(fs_info, "number of devices is 0");
		ret = -EINVAL;
	पूर्ण

	अगर (mirror_num >= 0 &&
	    btrfs_super_bytenr(sb) != btrfs_sb_offset(mirror_num)) अणु
		btrfs_err(fs_info, "super offset mismatch %llu != %u",
			  btrfs_super_bytenr(sb), BTRFS_SUPER_INFO_OFFSET);
		ret = -EINVAL;
	पूर्ण

	/*
	 * Obvious sys_chunk_array corruptions, it must hold at least one key
	 * and one chunk
	 */
	अगर (btrfs_super_sys_array_size(sb) > BTRFS_SYSTEM_CHUNK_ARRAY_SIZE) अणु
		btrfs_err(fs_info, "system chunk array too big %u > %u",
			  btrfs_super_sys_array_size(sb),
			  BTRFS_SYSTEM_CHUNK_ARRAY_SIZE);
		ret = -EINVAL;
	पूर्ण
	अगर (btrfs_super_sys_array_size(sb) < माप(काष्ठा btrfs_disk_key)
			+ माप(काष्ठा btrfs_chunk)) अणु
		btrfs_err(fs_info, "system chunk array too small %u < %zu",
			  btrfs_super_sys_array_size(sb),
			  माप(काष्ठा btrfs_disk_key)
			  + माप(काष्ठा btrfs_chunk));
		ret = -EINVAL;
	पूर्ण

	/*
	 * The generation is a global counter, we'll trust it more than the others
	 * but it's still possible that it's the one that's wrong.
	 */
	अगर (btrfs_super_generation(sb) < btrfs_super_chunk_root_generation(sb))
		btrfs_warn(fs_info,
			"suspicious: generation < chunk_root_generation: %llu < %llu",
			btrfs_super_generation(sb),
			btrfs_super_chunk_root_generation(sb));
	अगर (btrfs_super_generation(sb) < btrfs_super_cache_generation(sb)
	    && btrfs_super_cache_generation(sb) != (u64)-1)
		btrfs_warn(fs_info,
			"suspicious: generation < cache_generation: %llu < %llu",
			btrfs_super_generation(sb),
			btrfs_super_cache_generation(sb));

	वापस ret;
पूर्ण

/*
 * Validation of super block at mount समय.
 * Some checks alपढ़ोy करोne early at mount समय, like csum type and incompat
 * flags will be skipped.
 */
अटल पूर्णांक btrfs_validate_mount_super(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस validate_super(fs_info, fs_info->super_copy, 0);
पूर्ण

/*
 * Validation of super block at ग_लिखो समय.
 * Some checks like bytenr check will be skipped as their values will be
 * overwritten soon.
 * Extra checks like csum type and incompat flags will be करोne here.
 */
अटल पूर्णांक btrfs_validate_ग_लिखो_super(काष्ठा btrfs_fs_info *fs_info,
				      काष्ठा btrfs_super_block *sb)
अणु
	पूर्णांक ret;

	ret = validate_super(fs_info, sb, -1);
	अगर (ret < 0)
		जाओ out;
	अगर (!btrfs_supported_super_csum(btrfs_super_csum_type(sb))) अणु
		ret = -EUCLEAN;
		btrfs_err(fs_info, "invalid csum type, has %u want %u",
			  btrfs_super_csum_type(sb), BTRFS_CSUM_TYPE_CRC32);
		जाओ out;
	पूर्ण
	अगर (btrfs_super_incompat_flags(sb) & ~BTRFS_FEATURE_INCOMPAT_SUPP) अणु
		ret = -EUCLEAN;
		btrfs_err(fs_info,
		"invalid incompat flags, has 0x%llx valid mask 0x%llx",
			  btrfs_super_incompat_flags(sb),
			  (अचिन्हित दीर्घ दीर्घ)BTRFS_FEATURE_INCOMPAT_SUPP);
		जाओ out;
	पूर्ण
out:
	अगर (ret < 0)
		btrfs_err(fs_info,
		"super block corruption detected before writing it to disk");
	वापस ret;
पूर्ण

अटल पूर्णांक __cold init_tree_roots(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक backup_index = find_newest_super_backup(fs_info);
	काष्ठा btrfs_super_block *sb = fs_info->super_copy;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	bool handle_error = false;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_NUM_BACKUP_ROOTS; i++) अणु
		u64 generation;
		पूर्णांक level;

		अगर (handle_error) अणु
			अगर (!IS_ERR(tree_root->node))
				मुक्त_extent_buffer(tree_root->node);
			tree_root->node = शून्य;

			अगर (!btrfs_test_opt(fs_info, USEBACKUPROOT))
				अवरोध;

			मुक्त_root_poपूर्णांकers(fs_info, 0);

			/*
			 * Don't use the log in recovery mode, it won't be
			 * valid
			 */
			btrfs_set_super_log_root(sb, 0);

			/* We can't trust the मुक्त space cache either */
			btrfs_set_opt(fs_info->mount_opt, CLEAR_CACHE);

			ret = पढ़ो_backup_root(fs_info, i);
			backup_index = ret;
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		generation = btrfs_super_generation(sb);
		level = btrfs_super_root_level(sb);
		tree_root->node = पढ़ो_tree_block(fs_info, btrfs_super_root(sb),
						  BTRFS_ROOT_TREE_OBJECTID,
						  generation, level, शून्य);
		अगर (IS_ERR(tree_root->node)) अणु
			handle_error = true;
			ret = PTR_ERR(tree_root->node);
			tree_root->node = शून्य;
			btrfs_warn(fs_info, "couldn't read tree root");
			जारी;

		पूर्ण अन्यथा अगर (!extent_buffer_uptodate(tree_root->node)) अणु
			handle_error = true;
			ret = -EIO;
			btrfs_warn(fs_info, "error while reading tree root");
			जारी;
		पूर्ण

		btrfs_set_root_node(&tree_root->root_item, tree_root->node);
		tree_root->commit_root = btrfs_root_node(tree_root);
		btrfs_set_root_refs(&tree_root->root_item, 1);

		/*
		 * No need to hold btrfs_root::objectid_mutex since the fs
		 * hasn't been fully initialised and we are the only user
		 */
		ret = btrfs_init_root_मुक्त_objectid(tree_root);
		अगर (ret < 0) अणु
			handle_error = true;
			जारी;
		पूर्ण

		ASSERT(tree_root->मुक्त_objectid <= BTRFS_LAST_FREE_OBJECTID);

		ret = btrfs_पढ़ो_roots(fs_info);
		अगर (ret < 0) अणु
			handle_error = true;
			जारी;
		पूर्ण

		/* All successful */
		fs_info->generation = generation;
		fs_info->last_trans_committed = generation;

		/* Always begin writing backup roots after the one being used */
		अगर (backup_index < 0) अणु
			fs_info->backup_root_index = 0;
		पूर्ण अन्यथा अणु
			fs_info->backup_root_index = backup_index + 1;
			fs_info->backup_root_index %= BTRFS_NUM_BACKUP_ROOTS;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम btrfs_init_fs_info(काष्ठा btrfs_fs_info *fs_info)
अणु
	INIT_RADIX_TREE(&fs_info->fs_roots_radix, GFP_ATOMIC);
	INIT_RADIX_TREE(&fs_info->buffer_radix, GFP_ATOMIC);
	INIT_LIST_HEAD(&fs_info->trans_list);
	INIT_LIST_HEAD(&fs_info->dead_roots);
	INIT_LIST_HEAD(&fs_info->delayed_iमाला_दो);
	INIT_LIST_HEAD(&fs_info->delalloc_roots);
	INIT_LIST_HEAD(&fs_info->caching_block_groups);
	spin_lock_init(&fs_info->delalloc_root_lock);
	spin_lock_init(&fs_info->trans_lock);
	spin_lock_init(&fs_info->fs_roots_radix_lock);
	spin_lock_init(&fs_info->delayed_iput_lock);
	spin_lock_init(&fs_info->defrag_inodes_lock);
	spin_lock_init(&fs_info->super_lock);
	spin_lock_init(&fs_info->buffer_lock);
	spin_lock_init(&fs_info->unused_bgs_lock);
	spin_lock_init(&fs_info->treelog_bg_lock);
	rwlock_init(&fs_info->tree_mod_log_lock);
	mutex_init(&fs_info->unused_bg_unpin_mutex);
	mutex_init(&fs_info->reclaim_bgs_lock);
	mutex_init(&fs_info->reloc_mutex);
	mutex_init(&fs_info->delalloc_root_mutex);
	mutex_init(&fs_info->zoned_meta_io_lock);
	seqlock_init(&fs_info->profiles_lock);

	INIT_LIST_HEAD(&fs_info->dirty_cowonly_roots);
	INIT_LIST_HEAD(&fs_info->space_info);
	INIT_LIST_HEAD(&fs_info->tree_mod_seq_list);
	INIT_LIST_HEAD(&fs_info->unused_bgs);
	INIT_LIST_HEAD(&fs_info->reclaim_bgs);
#अगर_घोषित CONFIG_BTRFS_DEBUG
	INIT_LIST_HEAD(&fs_info->allocated_roots);
	INIT_LIST_HEAD(&fs_info->allocated_ebs);
	spin_lock_init(&fs_info->eb_leak_lock);
#पूर्ण_अगर
	extent_map_tree_init(&fs_info->mapping_tree);
	btrfs_init_block_rsv(&fs_info->global_block_rsv,
			     BTRFS_BLOCK_RSV_GLOBAL);
	btrfs_init_block_rsv(&fs_info->trans_block_rsv, BTRFS_BLOCK_RSV_TRANS);
	btrfs_init_block_rsv(&fs_info->chunk_block_rsv, BTRFS_BLOCK_RSV_CHUNK);
	btrfs_init_block_rsv(&fs_info->empty_block_rsv, BTRFS_BLOCK_RSV_EMPTY);
	btrfs_init_block_rsv(&fs_info->delayed_block_rsv,
			     BTRFS_BLOCK_RSV_DELOPS);
	btrfs_init_block_rsv(&fs_info->delayed_refs_rsv,
			     BTRFS_BLOCK_RSV_DELREFS);

	atomic_set(&fs_info->async_delalloc_pages, 0);
	atomic_set(&fs_info->defrag_running, 0);
	atomic_set(&fs_info->पढ़ोa_works_cnt, 0);
	atomic_set(&fs_info->nr_delayed_iमाला_दो, 0);
	atomic64_set(&fs_info->tree_mod_seq, 0);
	fs_info->max_अंतरभूत = BTRFS_DEFAULT_MAX_INLINE;
	fs_info->metadata_ratio = 0;
	fs_info->defrag_inodes = RB_ROOT;
	atomic64_set(&fs_info->मुक्त_chunk_space, 0);
	fs_info->tree_mod_log = RB_ROOT;
	fs_info->commit_पूर्णांकerval = BTRFS_DEFAULT_COMMIT_INTERVAL;
	fs_info->avg_delayed_ref_runसमय = NSEC_PER_SEC >> 6; /* भाग by 64 */
	/* पढ़ोahead state */
	INIT_RADIX_TREE(&fs_info->पढ़ोa_tree, GFP_NOFS & ~__GFP_सूचीECT_RECLAIM);
	spin_lock_init(&fs_info->पढ़ोa_lock);
	btrfs_init_ref_verअगरy(fs_info);

	fs_info->thपढ़ो_pool_size = min_t(अचिन्हित दीर्घ,
					  num_online_cpus() + 2, 8);

	INIT_LIST_HEAD(&fs_info->ordered_roots);
	spin_lock_init(&fs_info->ordered_root_lock);

	btrfs_init_scrub(fs_info);
#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
	fs_info->check_पूर्णांकegrity_prपूर्णांक_mask = 0;
#पूर्ण_अगर
	btrfs_init_balance(fs_info);
	btrfs_init_async_reclaim_work(fs_info);

	spin_lock_init(&fs_info->block_group_cache_lock);
	fs_info->block_group_cache_tree = RB_ROOT;
	fs_info->first_logical_byte = (u64)-1;

	extent_io_tree_init(fs_info, &fs_info->excluded_extents,
			    IO_TREE_FS_EXCLUDED_EXTENTS, शून्य);
	set_bit(BTRFS_FS_BARRIER, &fs_info->flags);

	mutex_init(&fs_info->ordered_operations_mutex);
	mutex_init(&fs_info->tree_log_mutex);
	mutex_init(&fs_info->chunk_mutex);
	mutex_init(&fs_info->transaction_kthपढ़ो_mutex);
	mutex_init(&fs_info->cleaner_mutex);
	mutex_init(&fs_info->ro_block_group_mutex);
	init_rwsem(&fs_info->commit_root_sem);
	init_rwsem(&fs_info->cleanup_work_sem);
	init_rwsem(&fs_info->subvol_sem);
	sema_init(&fs_info->uuid_tree_rescan_sem, 1);

	btrfs_init_dev_replace_locks(fs_info);
	btrfs_init_qgroup(fs_info);
	btrfs_discard_init(fs_info);

	btrfs_init_मुक्त_cluster(&fs_info->meta_alloc_cluster);
	btrfs_init_मुक्त_cluster(&fs_info->data_alloc_cluster);

	init_रुकोqueue_head(&fs_info->transaction_throttle);
	init_रुकोqueue_head(&fs_info->transaction_रुको);
	init_रुकोqueue_head(&fs_info->transaction_blocked_रुको);
	init_रुकोqueue_head(&fs_info->async_submit_रुको);
	init_रुकोqueue_head(&fs_info->delayed_iमाला_दो_रुको);

	/* Usable values until the real ones are cached from the superblock */
	fs_info->nodesize = 4096;
	fs_info->sectorsize = 4096;
	fs_info->sectorsize_bits = ilog2(4096);
	fs_info->stripesize = 4096;

	spin_lock_init(&fs_info->swapfile_pins_lock);
	fs_info->swapfile_pins = RB_ROOT;

	fs_info->send_in_progress = 0;

	fs_info->bg_reclaim_threshold = BTRFS_DEFAULT_RECLAIM_THRESH;
	INIT_WORK(&fs_info->reclaim_bgs_work, btrfs_reclaim_bgs_work);
पूर्ण

अटल पूर्णांक init_mount_fs_info(काष्ठा btrfs_fs_info *fs_info, काष्ठा super_block *sb)
अणु
	पूर्णांक ret;

	fs_info->sb = sb;
	sb->s_blocksize = BTRFS_BDEV_BLOCKSIZE;
	sb->s_blocksize_bits = blksize_bits(BTRFS_BDEV_BLOCKSIZE);

	ret = percpu_counter_init(&fs_info->ordered_bytes, 0, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	ret = percpu_counter_init(&fs_info->dirty_metadata_bytes, 0, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	fs_info->dirty_metadata_batch = PAGE_SIZE *
					(1 + ilog2(nr_cpu_ids));

	ret = percpu_counter_init(&fs_info->delalloc_bytes, 0, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	ret = percpu_counter_init(&fs_info->dev_replace.bio_counter, 0,
			GFP_KERNEL);
	अगर (ret)
		वापस ret;

	fs_info->delayed_root = kदो_स्मृति(माप(काष्ठा btrfs_delayed_root),
					GFP_KERNEL);
	अगर (!fs_info->delayed_root)
		वापस -ENOMEM;
	btrfs_init_delayed_root(fs_info->delayed_root);

	अगर (sb_rकरोnly(sb))
		set_bit(BTRFS_FS_STATE_RO, &fs_info->fs_state);

	वापस btrfs_alloc_stripe_hash_table(fs_info);
पूर्ण

अटल पूर्णांक btrfs_uuid_rescan_kthपढ़ो(व्योम *data)
अणु
	काष्ठा btrfs_fs_info *fs_info = (काष्ठा btrfs_fs_info *)data;
	पूर्णांक ret;

	/*
	 * 1st step is to iterate through the existing UUID tree and
	 * to delete all entries that contain outdated data.
	 * 2nd step is to add all missing entries to the UUID tree.
	 */
	ret = btrfs_uuid_tree_iterate(fs_info);
	अगर (ret < 0) अणु
		अगर (ret != -EINTR)
			btrfs_warn(fs_info, "iterating uuid_tree failed %d",
				   ret);
		up(&fs_info->uuid_tree_rescan_sem);
		वापस ret;
	पूर्ण
	वापस btrfs_uuid_scan_kthपढ़ो(data);
पूर्ण

अटल पूर्णांक btrfs_check_uuid_tree(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा task_काष्ठा *task;

	करोwn(&fs_info->uuid_tree_rescan_sem);
	task = kthपढ़ो_run(btrfs_uuid_rescan_kthपढ़ो, fs_info, "btrfs-uuid");
	अगर (IS_ERR(task)) अणु
		/* fs_info->update_uuid_tree_gen reमुख्यs 0 in all error हाल */
		btrfs_warn(fs_info, "failed to start uuid_rescan task");
		up(&fs_info->uuid_tree_rescan_sem);
		वापस PTR_ERR(task);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Some options only have meaning at mount समय and shouldn't persist across
 * remounts, or be displayed. Clear these at the end of mount and remount
 * code paths.
 */
व्योम btrfs_clear_oneshot_options(काष्ठा btrfs_fs_info *fs_info)
अणु
	btrfs_clear_opt(fs_info->mount_opt, USEBACKUPROOT);
	btrfs_clear_opt(fs_info->mount_opt, CLEAR_CACHE);
पूर्ण

/*
 * Mounting logic specअगरic to पढ़ो-ग_लिखो file प्रणालीs. Shared by खोलो_ctree
 * and btrfs_remount when remounting from पढ़ो-only to पढ़ो-ग_लिखो.
 */
पूर्णांक btrfs_start_pre_rw_mount(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक ret;
	स्थिर bool cache_opt = btrfs_test_opt(fs_info, SPACE_CACHE);
	bool clear_मुक्त_space_tree = false;

	अगर (btrfs_test_opt(fs_info, CLEAR_CACHE) &&
	    btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE)) अणु
		clear_मुक्त_space_tree = true;
	पूर्ण अन्यथा अगर (btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE) &&
		   !btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE_VALID)) अणु
		btrfs_warn(fs_info, "free space tree is invalid");
		clear_मुक्त_space_tree = true;
	पूर्ण

	अगर (clear_मुक्त_space_tree) अणु
		btrfs_info(fs_info, "clearing free space tree");
		ret = btrfs_clear_मुक्त_space_tree(fs_info);
		अगर (ret) अणु
			btrfs_warn(fs_info,
				   "failed to clear free space tree: %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * btrfs_find_orphan_roots() is responsible क्रम finding all the dead
	 * roots (with 0 refs), flag them with BTRFS_ROOT_DEAD_TREE and load
	 * them पूर्णांकo the fs_info->fs_roots_radix tree. This must be करोne beक्रमe
	 * calling btrfs_orphan_cleanup() on the tree root. If we करोn't करो it
	 * first, then btrfs_orphan_cleanup() will delete a dead root's orphan
	 * item beक्रमe the root's tree is deleted - this means that अगर we unmount
	 * or crash beक्रमe the deletion completes, on the next mount we will not
	 * delete what reमुख्यs of the tree because the orphan item करोes not
	 * exists anymore, which is what tells us we have a pending deletion.
	 */
	ret = btrfs_find_orphan_roots(fs_info);
	अगर (ret)
		जाओ out;

	ret = btrfs_cleanup_fs_roots(fs_info);
	अगर (ret)
		जाओ out;

	करोwn_पढ़ो(&fs_info->cleanup_work_sem);
	अगर ((ret = btrfs_orphan_cleanup(fs_info->fs_root)) ||
	    (ret = btrfs_orphan_cleanup(fs_info->tree_root))) अणु
		up_पढ़ो(&fs_info->cleanup_work_sem);
		जाओ out;
	पूर्ण
	up_पढ़ो(&fs_info->cleanup_work_sem);

	mutex_lock(&fs_info->cleaner_mutex);
	ret = btrfs_recover_relocation(fs_info->tree_root);
	mutex_unlock(&fs_info->cleaner_mutex);
	अगर (ret < 0) अणु
		btrfs_warn(fs_info, "failed to recover relocation: %d", ret);
		जाओ out;
	पूर्ण

	अगर (btrfs_test_opt(fs_info, FREE_SPACE_TREE) &&
	    !btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE)) अणु
		btrfs_info(fs_info, "creating free space tree");
		ret = btrfs_create_मुक्त_space_tree(fs_info);
		अगर (ret) अणु
			btrfs_warn(fs_info,
				"failed to create free space tree: %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (cache_opt != btrfs_मुक्त_space_cache_v1_active(fs_info)) अणु
		ret = btrfs_set_मुक्त_space_cache_v1_active(fs_info, cache_opt);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = btrfs_resume_balance_async(fs_info);
	अगर (ret)
		जाओ out;

	ret = btrfs_resume_dev_replace_async(fs_info);
	अगर (ret) अणु
		btrfs_warn(fs_info, "failed to resume dev_replace");
		जाओ out;
	पूर्ण

	btrfs_qgroup_rescan_resume(fs_info);

	अगर (!fs_info->uuid_root) अणु
		btrfs_info(fs_info, "creating UUID tree");
		ret = btrfs_create_uuid_tree(fs_info);
		अगर (ret) अणु
			btrfs_warn(fs_info,
				   "failed to create the UUID tree %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक __cold खोलो_ctree(काष्ठा super_block *sb, काष्ठा btrfs_fs_devices *fs_devices,
		      अक्षर *options)
अणु
	u32 sectorsize;
	u32 nodesize;
	u32 stripesize;
	u64 generation;
	u64 features;
	u16 csum_type;
	काष्ठा btrfs_super_block *disk_super;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	काष्ठा btrfs_root *tree_root;
	काष्ठा btrfs_root *chunk_root;
	पूर्णांक ret;
	पूर्णांक err = -EINVAL;
	पूर्णांक level;

	ret = init_mount_fs_info(fs_info, sb);
	अगर (ret) अणु
		err = ret;
		जाओ fail;
	पूर्ण

	/* These need to be init'ed beक्रमe we start creating inodes and such. */
	tree_root = btrfs_alloc_root(fs_info, BTRFS_ROOT_TREE_OBJECTID,
				     GFP_KERNEL);
	fs_info->tree_root = tree_root;
	chunk_root = btrfs_alloc_root(fs_info, BTRFS_CHUNK_TREE_OBJECTID,
				      GFP_KERNEL);
	fs_info->chunk_root = chunk_root;
	अगर (!tree_root || !chunk_root) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	fs_info->btree_inode = new_inode(sb);
	अगर (!fs_info->btree_inode) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण
	mapping_set_gfp_mask(fs_info->btree_inode->i_mapping, GFP_NOFS);
	btrfs_init_btree_inode(fs_info);

	invalidate_bdev(fs_devices->latest_bdev);

	/*
	 * Read super block and check the signature bytes only
	 */
	disk_super = btrfs_पढ़ो_dev_super(fs_devices->latest_bdev);
	अगर (IS_ERR(disk_super)) अणु
		err = PTR_ERR(disk_super);
		जाओ fail_alloc;
	पूर्ण

	/*
	 * Verअगरy the type first, अगर that or the checksum value are
	 * corrupted, we'll find out
	 */
	csum_type = btrfs_super_csum_type(disk_super);
	अगर (!btrfs_supported_super_csum(csum_type)) अणु
		btrfs_err(fs_info, "unsupported checksum algorithm: %u",
			  csum_type);
		err = -EINVAL;
		btrfs_release_disk_super(disk_super);
		जाओ fail_alloc;
	पूर्ण

	fs_info->csum_size = btrfs_super_csum_size(disk_super);

	ret = btrfs_init_csum_hash(fs_info, csum_type);
	अगर (ret) अणु
		err = ret;
		btrfs_release_disk_super(disk_super);
		जाओ fail_alloc;
	पूर्ण

	/*
	 * We want to check superblock checksum, the type is stored inside.
	 * Pass the whole disk block of size BTRFS_SUPER_INFO_SIZE (4k).
	 */
	अगर (btrfs_check_super_csum(fs_info, (u8 *)disk_super)) अणु
		btrfs_err(fs_info, "superblock checksum mismatch");
		err = -EINVAL;
		btrfs_release_disk_super(disk_super);
		जाओ fail_alloc;
	पूर्ण

	/*
	 * super_copy is zeroed at allocation समय and we never touch the
	 * following bytes up to INFO_SIZE, the checksum is calculated from
	 * the whole block of INFO_SIZE
	 */
	स_नकल(fs_info->super_copy, disk_super, माप(*fs_info->super_copy));
	btrfs_release_disk_super(disk_super);

	disk_super = fs_info->super_copy;


	features = btrfs_super_flags(disk_super);
	अगर (features & BTRFS_SUPER_FLAG_CHANGING_FSID_V2) अणु
		features &= ~BTRFS_SUPER_FLAG_CHANGING_FSID_V2;
		btrfs_set_super_flags(disk_super, features);
		btrfs_info(fs_info,
			"found metadata UUID change in progress flag, clearing");
	पूर्ण

	स_नकल(fs_info->super_क्रम_commit, fs_info->super_copy,
	       माप(*fs_info->super_क्रम_commit));

	ret = btrfs_validate_mount_super(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "superblock contains fatal errors");
		err = -EINVAL;
		जाओ fail_alloc;
	पूर्ण

	अगर (!btrfs_super_root(disk_super))
		जाओ fail_alloc;

	/* check FS state, whether FS is broken. */
	अगर (btrfs_super_flags(disk_super) & BTRFS_SUPER_FLAG_ERROR)
		set_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state);

	/*
	 * In the दीर्घ term, we'll store the compression type in the super
	 * block, and it'll be used क्रम per file compression control.
	 */
	fs_info->compress_type = BTRFS_COMPRESS_ZLIB;

	ret = btrfs_parse_options(fs_info, options, sb->s_flags);
	अगर (ret) अणु
		err = ret;
		जाओ fail_alloc;
	पूर्ण

	features = btrfs_super_incompat_flags(disk_super) &
		~BTRFS_FEATURE_INCOMPAT_SUPP;
	अगर (features) अणु
		btrfs_err(fs_info,
		    "cannot mount because of unsupported optional features (%llx)",
		    features);
		err = -EINVAL;
		जाओ fail_alloc;
	पूर्ण

	features = btrfs_super_incompat_flags(disk_super);
	features |= BTRFS_FEATURE_INCOMPAT_MIXED_BACKREF;
	अगर (fs_info->compress_type == BTRFS_COMPRESS_LZO)
		features |= BTRFS_FEATURE_INCOMPAT_COMPRESS_LZO;
	अन्यथा अगर (fs_info->compress_type == BTRFS_COMPRESS_ZSTD)
		features |= BTRFS_FEATURE_INCOMPAT_COMPRESS_ZSTD;

	अगर (features & BTRFS_FEATURE_INCOMPAT_SKINNY_METADATA)
		btrfs_info(fs_info, "has skinny extents");

	/*
	 * flag our fileप्रणाली as having big metadata blocks अगर
	 * they are bigger than the page size
	 */
	अगर (btrfs_super_nodesize(disk_super) > PAGE_SIZE) अणु
		अगर (!(features & BTRFS_FEATURE_INCOMPAT_BIG_METADATA))
			btrfs_info(fs_info,
				"flagging fs with big metadata feature");
		features |= BTRFS_FEATURE_INCOMPAT_BIG_METADATA;
	पूर्ण

	nodesize = btrfs_super_nodesize(disk_super);
	sectorsize = btrfs_super_sectorsize(disk_super);
	stripesize = sectorsize;
	fs_info->dirty_metadata_batch = nodesize * (1 + ilog2(nr_cpu_ids));
	fs_info->delalloc_batch = sectorsize * 512 * (1 + ilog2(nr_cpu_ids));

	/* Cache block sizes */
	fs_info->nodesize = nodesize;
	fs_info->sectorsize = sectorsize;
	fs_info->sectorsize_bits = ilog2(sectorsize);
	fs_info->csums_per_leaf = BTRFS_MAX_ITEM_SIZE(fs_info) / fs_info->csum_size;
	fs_info->stripesize = stripesize;

	/*
	 * mixed block groups end up with duplicate but slightly offset
	 * extent buffers क्रम the same range.  It leads to corruptions
	 */
	अगर ((features & BTRFS_FEATURE_INCOMPAT_MIXED_GROUPS) &&
	    (sectorsize != nodesize)) अणु
		btrfs_err(fs_info,
"unequal nodesize/sectorsize (%u != %u) are not allowed for mixed block groups",
			nodesize, sectorsize);
		जाओ fail_alloc;
	पूर्ण

	/*
	 * Needn't use the lock because there is no other task which will
	 * update the flag.
	 */
	btrfs_set_super_incompat_flags(disk_super, features);

	features = btrfs_super_compat_ro_flags(disk_super) &
		~BTRFS_FEATURE_COMPAT_RO_SUPP;
	अगर (!sb_rकरोnly(sb) && features) अणु
		btrfs_err(fs_info,
	"cannot mount read-write because of unsupported optional features (%llx)",
		       features);
		err = -EINVAL;
		जाओ fail_alloc;
	पूर्ण

	/* For 4K sector size support, it's only पढ़ो-only */
	अगर (PAGE_SIZE == SZ_64K && sectorsize == SZ_4K) अणु
		अगर (!sb_rकरोnly(sb) || btrfs_super_log_root(disk_super)) अणु
			btrfs_err(fs_info,
	"subpage sectorsize %u only supported read-only for page size %lu",
				sectorsize, PAGE_SIZE);
			err = -EINVAL;
			जाओ fail_alloc;
		पूर्ण
	पूर्ण

	ret = btrfs_init_workqueues(fs_info, fs_devices);
	अगर (ret) अणु
		err = ret;
		जाओ fail_sb_buffer;
	पूर्ण

	sb->s_bdi->ra_pages *= btrfs_super_num_devices(disk_super);
	sb->s_bdi->ra_pages = max(sb->s_bdi->ra_pages, SZ_4M / PAGE_SIZE);

	sb->s_blocksize = sectorsize;
	sb->s_blocksize_bits = blksize_bits(sectorsize);
	स_नकल(&sb->s_uuid, fs_info->fs_devices->fsid, BTRFS_FSID_SIZE);

	mutex_lock(&fs_info->chunk_mutex);
	ret = btrfs_पढ़ो_sys_array(fs_info);
	mutex_unlock(&fs_info->chunk_mutex);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to read the system array: %d", ret);
		जाओ fail_sb_buffer;
	पूर्ण

	generation = btrfs_super_chunk_root_generation(disk_super);
	level = btrfs_super_chunk_root_level(disk_super);

	chunk_root->node = पढ़ो_tree_block(fs_info,
					   btrfs_super_chunk_root(disk_super),
					   BTRFS_CHUNK_TREE_OBJECTID,
					   generation, level, शून्य);
	अगर (IS_ERR(chunk_root->node) ||
	    !extent_buffer_uptodate(chunk_root->node)) अणु
		btrfs_err(fs_info, "failed to read chunk root");
		अगर (!IS_ERR(chunk_root->node))
			मुक्त_extent_buffer(chunk_root->node);
		chunk_root->node = शून्य;
		जाओ fail_tree_roots;
	पूर्ण
	btrfs_set_root_node(&chunk_root->root_item, chunk_root->node);
	chunk_root->commit_root = btrfs_root_node(chunk_root);

	पढ़ो_extent_buffer(chunk_root->node, fs_info->chunk_tree_uuid,
			   दुरत्व(काष्ठा btrfs_header, chunk_tree_uuid),
			   BTRFS_UUID_SIZE);

	ret = btrfs_पढ़ो_chunk_tree(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to read chunk tree: %d", ret);
		जाओ fail_tree_roots;
	पूर्ण

	/*
	 * At this poपूर्णांक we know all the devices that make this fileप्रणाली,
	 * including the seed devices but we करोn't know yet अगर the replace
	 * target is required. So मुक्त devices that are not part of this
	 * fileप्रणाली but skip the replace traget device which is checked
	 * below in btrfs_init_dev_replace().
	 */
	btrfs_मुक्त_extra_devids(fs_devices);
	अगर (!fs_devices->latest_bdev) अणु
		btrfs_err(fs_info, "failed to read devices");
		जाओ fail_tree_roots;
	पूर्ण

	ret = init_tree_roots(fs_info);
	अगर (ret)
		जाओ fail_tree_roots;

	/*
	 * Get zone type inक्रमmation of zoned block devices. This will also
	 * handle emulation of a zoned fileप्रणाली अगर a regular device has the
	 * zoned incompat feature flag set.
	 */
	ret = btrfs_get_dev_zone_info_all_devices(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info,
			  "zoned: failed to read device zone info: %d",
			  ret);
		जाओ fail_block_groups;
	पूर्ण

	/*
	 * If we have a uuid root and we're not being told to rescan we need to
	 * check the generation here so we can set the
	 * BTRFS_FS_UPDATE_UUID_TREE_GEN bit.  Otherwise we could commit the
	 * transaction during a balance or the log replay without updating the
	 * uuid generation, and then अगर we crash we would rescan the uuid tree,
	 * even though it was perfectly fine.
	 */
	अगर (fs_info->uuid_root && !btrfs_test_opt(fs_info, RESCAN_UUID_TREE) &&
	    fs_info->generation == btrfs_super_uuid_tree_generation(disk_super))
		set_bit(BTRFS_FS_UPDATE_UUID_TREE_GEN, &fs_info->flags);

	ret = btrfs_verअगरy_dev_extents(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info,
			  "failed to verify dev extents against chunks: %d",
			  ret);
		जाओ fail_block_groups;
	पूर्ण
	ret = btrfs_recover_balance(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to recover balance: %d", ret);
		जाओ fail_block_groups;
	पूर्ण

	ret = btrfs_init_dev_stats(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to init dev_stats: %d", ret);
		जाओ fail_block_groups;
	पूर्ण

	ret = btrfs_init_dev_replace(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to init dev_replace: %d", ret);
		जाओ fail_block_groups;
	पूर्ण

	ret = btrfs_check_zoned_mode(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to initialize zoned mode: %d",
			  ret);
		जाओ fail_block_groups;
	पूर्ण

	ret = btrfs_sysfs_add_fsid(fs_devices);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to init sysfs fsid interface: %d",
				ret);
		जाओ fail_block_groups;
	पूर्ण

	ret = btrfs_sysfs_add_mounted(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to init sysfs interface: %d", ret);
		जाओ fail_fsdev_sysfs;
	पूर्ण

	ret = btrfs_init_space_info(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to initialize space info: %d", ret);
		जाओ fail_sysfs;
	पूर्ण

	ret = btrfs_पढ़ो_block_groups(fs_info);
	अगर (ret) अणु
		btrfs_err(fs_info, "failed to read block groups: %d", ret);
		जाओ fail_sysfs;
	पूर्ण

	अगर (!sb_rकरोnly(sb) && !btrfs_check_rw_degradable(fs_info, शून्य)) अणु
		btrfs_warn(fs_info,
		"writable mount is not allowed due to too many missing devices");
		जाओ fail_sysfs;
	पूर्ण

	fs_info->cleaner_kthपढ़ो = kthपढ़ो_run(cleaner_kthपढ़ो, tree_root,
					       "btrfs-cleaner");
	अगर (IS_ERR(fs_info->cleaner_kthपढ़ो))
		जाओ fail_sysfs;

	fs_info->transaction_kthपढ़ो = kthपढ़ो_run(transaction_kthपढ़ो,
						   tree_root,
						   "btrfs-transaction");
	अगर (IS_ERR(fs_info->transaction_kthपढ़ो))
		जाओ fail_cleaner;

	अगर (!btrfs_test_opt(fs_info, NOSSD) &&
	    !fs_info->fs_devices->rotating) अणु
		btrfs_set_and_info(fs_info, SSD, "enabling ssd optimizations");
	पूर्ण

	/*
	 * Mount करोes not set all options immediately, we can करो it now and करो
	 * not have to रुको क्रम transaction commit
	 */
	btrfs_apply_pending_changes(fs_info);

#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
	अगर (btrfs_test_opt(fs_info, CHECK_INTEGRITY)) अणु
		ret = btrfsic_mount(fs_info, fs_devices,
				    btrfs_test_opt(fs_info,
					CHECK_INTEGRITY_INCLUDING_EXTENT_DATA) ?
				    1 : 0,
				    fs_info->check_पूर्णांकegrity_prपूर्णांक_mask);
		अगर (ret)
			btrfs_warn(fs_info,
				"failed to initialize integrity check module: %d",
				ret);
	पूर्ण
#पूर्ण_अगर
	ret = btrfs_पढ़ो_qgroup_config(fs_info);
	अगर (ret)
		जाओ fail_trans_kthपढ़ो;

	अगर (btrfs_build_ref_tree(fs_info))
		btrfs_err(fs_info, "couldn't build ref tree");

	/* करो not make disk changes in broken FS or nologreplay is given */
	अगर (btrfs_super_log_root(disk_super) != 0 &&
	    !btrfs_test_opt(fs_info, NOLOGREPLAY)) अणु
		btrfs_info(fs_info, "start tree-log replay");
		ret = btrfs_replay_log(fs_info, fs_devices);
		अगर (ret) अणु
			err = ret;
			जाओ fail_qgroup;
		पूर्ण
	पूर्ण

	fs_info->fs_root = btrfs_get_fs_root(fs_info, BTRFS_FS_TREE_OBJECTID, true);
	अगर (IS_ERR(fs_info->fs_root)) अणु
		err = PTR_ERR(fs_info->fs_root);
		btrfs_warn(fs_info, "failed to read fs tree: %d", err);
		fs_info->fs_root = शून्य;
		जाओ fail_qgroup;
	पूर्ण

	अगर (sb_rकरोnly(sb))
		जाओ clear_oneshot;

	ret = btrfs_start_pre_rw_mount(fs_info);
	अगर (ret) अणु
		बंद_ctree(fs_info);
		वापस ret;
	पूर्ण
	btrfs_discard_resume(fs_info);

	अगर (fs_info->uuid_root &&
	    (btrfs_test_opt(fs_info, RESCAN_UUID_TREE) ||
	     fs_info->generation != btrfs_super_uuid_tree_generation(disk_super))) अणु
		btrfs_info(fs_info, "checking UUID tree");
		ret = btrfs_check_uuid_tree(fs_info);
		अगर (ret) अणु
			btrfs_warn(fs_info,
				"failed to check the UUID tree: %d", ret);
			बंद_ctree(fs_info);
			वापस ret;
		पूर्ण
	पूर्ण

	set_bit(BTRFS_FS_OPEN, &fs_info->flags);

clear_oneshot:
	btrfs_clear_oneshot_options(fs_info);
	वापस 0;

fail_qgroup:
	btrfs_मुक्त_qgroup_config(fs_info);
fail_trans_kthपढ़ो:
	kthपढ़ो_stop(fs_info->transaction_kthपढ़ो);
	btrfs_cleanup_transaction(fs_info);
	btrfs_मुक्त_fs_roots(fs_info);
fail_cleaner:
	kthपढ़ो_stop(fs_info->cleaner_kthपढ़ो);

	/*
	 * make sure we're करोne with the btree inode beक्रमe we stop our
	 * kthपढ़ोs
	 */
	filemap_ग_लिखो_and_रुको(fs_info->btree_inode->i_mapping);

fail_sysfs:
	btrfs_sysfs_हटाओ_mounted(fs_info);

fail_fsdev_sysfs:
	btrfs_sysfs_हटाओ_fsid(fs_info->fs_devices);

fail_block_groups:
	btrfs_put_block_group_cache(fs_info);

fail_tree_roots:
	अगर (fs_info->data_reloc_root)
		btrfs_drop_and_मुक्त_fs_root(fs_info, fs_info->data_reloc_root);
	मुक्त_root_poपूर्णांकers(fs_info, true);
	invalidate_inode_pages2(fs_info->btree_inode->i_mapping);

fail_sb_buffer:
	btrfs_stop_all_workers(fs_info);
	btrfs_मुक्त_block_groups(fs_info);
fail_alloc:
	btrfs_mapping_tree_मुक्त(&fs_info->mapping_tree);

	iput(fs_info->btree_inode);
fail:
	btrfs_बंद_devices(fs_info->fs_devices);
	वापस err;
पूर्ण
ALLOW_ERROR_INJECTION(खोलो_ctree, ERRNO);

अटल व्योम btrfs_end_super_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_device *device = bio->bi_निजी;
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;
	काष्ठा page *page;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		page = bvec->bv_page;

		अगर (bio->bi_status) अणु
			btrfs_warn_rl_in_rcu(device->fs_info,
				"lost page write due to IO error on %s (%d)",
				rcu_str_deref(device->name),
				blk_status_to_त्रुटि_सं(bio->bi_status));
			ClearPageUptodate(page);
			SetPageError(page);
			btrfs_dev_stat_inc_and_prपूर्णांक(device,
						     BTRFS_DEV_STAT_WRITE_ERRS);
		पूर्ण अन्यथा अणु
			SetPageUptodate(page);
		पूर्ण

		put_page(page);
		unlock_page(page);
	पूर्ण

	bio_put(bio);
पूर्ण

काष्ठा btrfs_super_block *btrfs_पढ़ो_dev_one_super(काष्ठा block_device *bdev,
						   पूर्णांक copy_num)
अणु
	काष्ठा btrfs_super_block *super;
	काष्ठा page *page;
	u64 bytenr, bytenr_orig;
	काष्ठा address_space *mapping = bdev->bd_inode->i_mapping;
	पूर्णांक ret;

	bytenr_orig = btrfs_sb_offset(copy_num);
	ret = btrfs_sb_log_location_bdev(bdev, copy_num, READ, &bytenr);
	अगर (ret == -ENOENT)
		वापस ERR_PTR(-EINVAL);
	अन्यथा अगर (ret)
		वापस ERR_PTR(ret);

	अगर (bytenr + BTRFS_SUPER_INFO_SIZE >= i_size_पढ़ो(bdev->bd_inode))
		वापस ERR_PTR(-EINVAL);

	page = पढ़ो_cache_page_gfp(mapping, bytenr >> PAGE_SHIFT, GFP_NOFS);
	अगर (IS_ERR(page))
		वापस ERR_CAST(page);

	super = page_address(page);
	अगर (btrfs_super_magic(super) != BTRFS_MAGIC) अणु
		btrfs_release_disk_super(super);
		वापस ERR_PTR(-ENODATA);
	पूर्ण

	अगर (btrfs_super_bytenr(super) != bytenr_orig) अणु
		btrfs_release_disk_super(super);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस super;
पूर्ण


काष्ठा btrfs_super_block *btrfs_पढ़ो_dev_super(काष्ठा block_device *bdev)
अणु
	काष्ठा btrfs_super_block *super, *latest = शून्य;
	पूर्णांक i;
	u64 transid = 0;

	/* we would like to check all the supers, but that would make
	 * a btrfs mount succeed after a mkfs from a dअगरferent FS.
	 * So, we need to add a special mount option to scan क्रम
	 * later supers, using BTRFS_SUPER_MIRROR_MAX instead
	 */
	क्रम (i = 0; i < 1; i++) अणु
		super = btrfs_पढ़ो_dev_one_super(bdev, i);
		अगर (IS_ERR(super))
			जारी;

		अगर (!latest || btrfs_super_generation(super) > transid) अणु
			अगर (latest)
				btrfs_release_disk_super(super);

			latest = super;
			transid = btrfs_super_generation(super);
		पूर्ण
	पूर्ण

	वापस super;
पूर्ण

/*
 * Write superblock @sb to the @device. Do not रुको क्रम completion, all the
 * pages we use क्रम writing are locked.
 *
 * Write @max_mirrors copies of the superblock, where 0 means शेष that fit
 * the expected device size at commit समय. Note that max_mirrors must be
 * same क्रम ग_लिखो and रुको phases.
 *
 * Return number of errors when page is not found or submission fails.
 */
अटल पूर्णांक ग_लिखो_dev_supers(काष्ठा btrfs_device *device,
			    काष्ठा btrfs_super_block *sb, पूर्णांक max_mirrors)
अणु
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;
	काष्ठा address_space *mapping = device->bdev->bd_inode->i_mapping;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	पूर्णांक i;
	पूर्णांक errors = 0;
	पूर्णांक ret;
	u64 bytenr, bytenr_orig;

	अगर (max_mirrors == 0)
		max_mirrors = BTRFS_SUPER_MIRROR_MAX;

	shash->tfm = fs_info->csum_shash;

	क्रम (i = 0; i < max_mirrors; i++) अणु
		काष्ठा page *page;
		काष्ठा bio *bio;
		काष्ठा btrfs_super_block *disk_super;

		bytenr_orig = btrfs_sb_offset(i);
		ret = btrfs_sb_log_location(device, i, WRITE, &bytenr);
		अगर (ret == -ENOENT) अणु
			जारी;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			btrfs_err(device->fs_info,
				"couldn't get super block location for mirror %d",
				i);
			errors++;
			जारी;
		पूर्ण
		अगर (bytenr + BTRFS_SUPER_INFO_SIZE >=
		    device->commit_total_bytes)
			अवरोध;

		btrfs_set_super_bytenr(sb, bytenr_orig);

		crypto_shash_digest(shash, (स्थिर अक्षर *)sb + BTRFS_CSUM_SIZE,
				    BTRFS_SUPER_INFO_SIZE - BTRFS_CSUM_SIZE,
				    sb->csum);

		page = find_or_create_page(mapping, bytenr >> PAGE_SHIFT,
					   GFP_NOFS);
		अगर (!page) अणु
			btrfs_err(device->fs_info,
			    "couldn't get super block page for bytenr %llu",
			    bytenr);
			errors++;
			जारी;
		पूर्ण

		/* Bump the refcount क्रम रुको_dev_supers() */
		get_page(page);

		disk_super = page_address(page);
		स_नकल(disk_super, sb, BTRFS_SUPER_INFO_SIZE);

		/*
		 * Directly use bios here instead of relying on the page cache
		 * to करो I/O, so we करोn't lose the ability to करो पूर्णांकegrity
		 * checking.
		 */
		bio = bio_alloc(GFP_NOFS, 1);
		bio_set_dev(bio, device->bdev);
		bio->bi_iter.bi_sector = bytenr >> SECTOR_SHIFT;
		bio->bi_निजी = device;
		bio->bi_end_io = btrfs_end_super_ग_लिखो;
		__bio_add_page(bio, page, BTRFS_SUPER_INFO_SIZE,
			       offset_in_page(bytenr));

		/*
		 * We FUA only the first super block.  The others we allow to
		 * go करोwn lazy and there's a लघु winकरोw where the on-disk
		 * copies might still contain the older version.
		 */
		bio->bi_opf = REQ_OP_WRITE | REQ_SYNC | REQ_META | REQ_PRIO;
		अगर (i == 0 && !btrfs_test_opt(device->fs_info, NOBARRIER))
			bio->bi_opf |= REQ_FUA;

		btrfsic_submit_bio(bio);
		btrfs_advance_sb_log(device, i);
	पूर्ण
	वापस errors < i ? 0 : -1;
पूर्ण

/*
 * Wait क्रम ग_लिखो completion of superblocks करोne by ग_लिखो_dev_supers,
 * @max_mirrors same क्रम ग_लिखो and रुको phases.
 *
 * Return number of errors when page is not found or not marked up to
 * date.
 */
अटल पूर्णांक रुको_dev_supers(काष्ठा btrfs_device *device, पूर्णांक max_mirrors)
अणु
	पूर्णांक i;
	पूर्णांक errors = 0;
	bool primary_failed = false;
	पूर्णांक ret;
	u64 bytenr;

	अगर (max_mirrors == 0)
		max_mirrors = BTRFS_SUPER_MIRROR_MAX;

	क्रम (i = 0; i < max_mirrors; i++) अणु
		काष्ठा page *page;

		ret = btrfs_sb_log_location(device, i, READ, &bytenr);
		अगर (ret == -ENOENT) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			errors++;
			अगर (i == 0)
				primary_failed = true;
			जारी;
		पूर्ण
		अगर (bytenr + BTRFS_SUPER_INFO_SIZE >=
		    device->commit_total_bytes)
			अवरोध;

		page = find_get_page(device->bdev->bd_inode->i_mapping,
				     bytenr >> PAGE_SHIFT);
		अगर (!page) अणु
			errors++;
			अगर (i == 0)
				primary_failed = true;
			जारी;
		पूर्ण
		/* Page is submitted locked and unlocked once the IO completes */
		रुको_on_page_locked(page);
		अगर (PageError(page)) अणु
			errors++;
			अगर (i == 0)
				primary_failed = true;
		पूर्ण

		/* Drop our reference */
		put_page(page);

		/* Drop the reference from the writing run */
		put_page(page);
	पूर्ण

	/* log error, क्रमce error वापस */
	अगर (primary_failed) अणु
		btrfs_err(device->fs_info, "error writing primary super block to device %llu",
			  device->devid);
		वापस -1;
	पूर्ण

	वापस errors < i ? 0 : -1;
पूर्ण

/*
 * endio क्रम the ग_लिखो_dev_flush, this will wake anyone रुकोing
 * क्रम the barrier when it is करोne
 */
अटल व्योम btrfs_end_empty_barrier(काष्ठा bio *bio)
अणु
	complete(bio->bi_निजी);
पूर्ण

/*
 * Submit a flush request to the device अगर it supports it. Error handling is
 * करोne in the रुकोing counterpart.
 */
अटल व्योम ग_लिखो_dev_flush(काष्ठा btrfs_device *device)
अणु
	काष्ठा request_queue *q = bdev_get_queue(device->bdev);
	काष्ठा bio *bio = device->flush_bio;

	अगर (!test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		वापस;

	bio_reset(bio);
	bio->bi_end_io = btrfs_end_empty_barrier;
	bio_set_dev(bio, device->bdev);
	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC | REQ_PREFLUSH;
	init_completion(&device->flush_रुको);
	bio->bi_निजी = &device->flush_रुको;

	btrfsic_submit_bio(bio);
	set_bit(BTRFS_DEV_STATE_FLUSH_SENT, &device->dev_state);
पूर्ण

/*
 * If the flush bio has been submitted by ग_लिखो_dev_flush, रुको क्रम it.
 */
अटल blk_status_t रुको_dev_flush(काष्ठा btrfs_device *device)
अणु
	काष्ठा bio *bio = device->flush_bio;

	अगर (!test_bit(BTRFS_DEV_STATE_FLUSH_SENT, &device->dev_state))
		वापस BLK_STS_OK;

	clear_bit(BTRFS_DEV_STATE_FLUSH_SENT, &device->dev_state);
	रुको_क्रम_completion_io(&device->flush_रुको);

	वापस bio->bi_status;
पूर्ण

अटल पूर्णांक check_barrier_error(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!btrfs_check_rw_degradable(fs_info, शून्य))
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * send an empty flush करोwn to each device in parallel,
 * then रुको क्रम them
 */
अटल पूर्णांक barrier_all_devices(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा list_head *head;
	काष्ठा btrfs_device *dev;
	पूर्णांक errors_रुको = 0;
	blk_status_t ret;

	lockdep_निश्चित_held(&info->fs_devices->device_list_mutex);
	/* send करोwn all the barriers */
	head = &info->fs_devices->devices;
	list_क्रम_each_entry(dev, head, dev_list) अणु
		अगर (test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state))
			जारी;
		अगर (!dev->bdev)
			जारी;
		अगर (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &dev->dev_state) ||
		    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state))
			जारी;

		ग_लिखो_dev_flush(dev);
		dev->last_flush_error = BLK_STS_OK;
	पूर्ण

	/* रुको क्रम all the barriers */
	list_क्रम_each_entry(dev, head, dev_list) अणु
		अगर (test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state))
			जारी;
		अगर (!dev->bdev) अणु
			errors_रुको++;
			जारी;
		पूर्ण
		अगर (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &dev->dev_state) ||
		    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state))
			जारी;

		ret = रुको_dev_flush(dev);
		अगर (ret) अणु
			dev->last_flush_error = ret;
			btrfs_dev_stat_inc_and_prपूर्णांक(dev,
					BTRFS_DEV_STAT_FLUSH_ERRS);
			errors_रुको++;
		पूर्ण
	पूर्ण

	अगर (errors_रुको) अणु
		/*
		 * At some poपूर्णांक we need the status of all disks
		 * to arrive at the volume status. So error checking
		 * is being pushed to a separate loop.
		 */
		वापस check_barrier_error(info);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक btrfs_get_num_tolerated_disk_barrier_failures(u64 flags)
अणु
	पूर्णांक raid_type;
	पूर्णांक min_tolerated = पूर्णांक_उच्च;

	अगर ((flags & BTRFS_BLOCK_GROUP_PROखाता_MASK) == 0 ||
	    (flags & BTRFS_AVAIL_ALLOC_BIT_SINGLE))
		min_tolerated = min_t(पूर्णांक, min_tolerated,
				    btrfs_raid_array[BTRFS_RAID_SINGLE].
				    tolerated_failures);

	क्रम (raid_type = 0; raid_type < BTRFS_NR_RAID_TYPES; raid_type++) अणु
		अगर (raid_type == BTRFS_RAID_SINGLE)
			जारी;
		अगर (!(flags & btrfs_raid_array[raid_type].bg_flag))
			जारी;
		min_tolerated = min_t(पूर्णांक, min_tolerated,
				    btrfs_raid_array[raid_type].
				    tolerated_failures);
	पूर्ण

	अगर (min_tolerated == पूर्णांक_उच्च) अणु
		pr_warn("BTRFS: unknown raid flag: %llu", flags);
		min_tolerated = 0;
	पूर्ण

	वापस min_tolerated;
पूर्ण

पूर्णांक ग_लिखो_all_supers(काष्ठा btrfs_fs_info *fs_info, पूर्णांक max_mirrors)
अणु
	काष्ठा list_head *head;
	काष्ठा btrfs_device *dev;
	काष्ठा btrfs_super_block *sb;
	काष्ठा btrfs_dev_item *dev_item;
	पूर्णांक ret;
	पूर्णांक करो_barriers;
	पूर्णांक max_errors;
	पूर्णांक total_errors = 0;
	u64 flags;

	करो_barriers = !btrfs_test_opt(fs_info, NOBARRIER);

	/*
	 * max_mirrors == 0 indicates we're from commit_transaction,
	 * not from fsync where the tree roots in fs_info have not
	 * been consistent on disk.
	 */
	अगर (max_mirrors == 0)
		backup_super_roots(fs_info);

	sb = fs_info->super_क्रम_commit;
	dev_item = &sb->dev_item;

	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	head = &fs_info->fs_devices->devices;
	max_errors = btrfs_super_num_devices(fs_info->super_copy) - 1;

	अगर (करो_barriers) अणु
		ret = barrier_all_devices(fs_info);
		अगर (ret) अणु
			mutex_unlock(
				&fs_info->fs_devices->device_list_mutex);
			btrfs_handle_fs_error(fs_info, ret,
					      "errors while submitting device barriers.");
			वापस ret;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(dev, head, dev_list) अणु
		अगर (!dev->bdev) अणु
			total_errors++;
			जारी;
		पूर्ण
		अगर (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &dev->dev_state) ||
		    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state))
			जारी;

		btrfs_set_stack_device_generation(dev_item, 0);
		btrfs_set_stack_device_type(dev_item, dev->type);
		btrfs_set_stack_device_id(dev_item, dev->devid);
		btrfs_set_stack_device_total_bytes(dev_item,
						   dev->commit_total_bytes);
		btrfs_set_stack_device_bytes_used(dev_item,
						  dev->commit_bytes_used);
		btrfs_set_stack_device_io_align(dev_item, dev->io_align);
		btrfs_set_stack_device_io_width(dev_item, dev->io_width);
		btrfs_set_stack_device_sector_size(dev_item, dev->sector_size);
		स_नकल(dev_item->uuid, dev->uuid, BTRFS_UUID_SIZE);
		स_नकल(dev_item->fsid, dev->fs_devices->metadata_uuid,
		       BTRFS_FSID_SIZE);

		flags = btrfs_super_flags(sb);
		btrfs_set_super_flags(sb, flags | BTRFS_HEADER_FLAG_WRITTEN);

		ret = btrfs_validate_ग_लिखो_super(fs_info, sb);
		अगर (ret < 0) अणु
			mutex_unlock(&fs_info->fs_devices->device_list_mutex);
			btrfs_handle_fs_error(fs_info, -EUCLEAN,
				"unexpected superblock corruption detected");
			वापस -EUCLEAN;
		पूर्ण

		ret = ग_लिखो_dev_supers(dev, sb, max_mirrors);
		अगर (ret)
			total_errors++;
	पूर्ण
	अगर (total_errors > max_errors) अणु
		btrfs_err(fs_info, "%d errors while writing supers",
			  total_errors);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);

		/* FUA is masked off अगर unsupported and can't be the reason */
		btrfs_handle_fs_error(fs_info, -EIO,
				      "%d errors while writing supers",
				      total_errors);
		वापस -EIO;
	पूर्ण

	total_errors = 0;
	list_क्रम_each_entry(dev, head, dev_list) अणु
		अगर (!dev->bdev)
			जारी;
		अगर (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &dev->dev_state) ||
		    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state))
			जारी;

		ret = रुको_dev_supers(dev, max_mirrors);
		अगर (ret)
			total_errors++;
	पूर्ण
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);
	अगर (total_errors > max_errors) अणु
		btrfs_handle_fs_error(fs_info, -EIO,
				      "%d errors while writing supers",
				      total_errors);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Drop a fs root from the radix tree and मुक्त it. */
व्योम btrfs_drop_and_मुक्त_fs_root(काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा btrfs_root *root)
अणु
	bool drop_ref = false;

	spin_lock(&fs_info->fs_roots_radix_lock);
	radix_tree_delete(&fs_info->fs_roots_radix,
			  (अचिन्हित दीर्घ)root->root_key.objectid);
	अगर (test_and_clear_bit(BTRFS_ROOT_IN_RADIX, &root->state))
		drop_ref = true;
	spin_unlock(&fs_info->fs_roots_radix_lock);

	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state)) अणु
		ASSERT(root->log_root == शून्य);
		अगर (root->reloc_root) अणु
			btrfs_put_root(root->reloc_root);
			root->reloc_root = शून्य;
		पूर्ण
	पूर्ण

	अगर (drop_ref)
		btrfs_put_root(root);
पूर्ण

पूर्णांक btrfs_cleanup_fs_roots(काष्ठा btrfs_fs_info *fs_info)
अणु
	u64 root_objectid = 0;
	काष्ठा btrfs_root *gang[8];
	पूर्णांक i = 0;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक ret = 0;

	जबतक (1) अणु
		spin_lock(&fs_info->fs_roots_radix_lock);
		ret = radix_tree_gang_lookup(&fs_info->fs_roots_radix,
					     (व्योम **)gang, root_objectid,
					     ARRAY_SIZE(gang));
		अगर (!ret) अणु
			spin_unlock(&fs_info->fs_roots_radix_lock);
			अवरोध;
		पूर्ण
		root_objectid = gang[ret - 1]->root_key.objectid + 1;

		क्रम (i = 0; i < ret; i++) अणु
			/* Aव्योम to grab roots in dead_roots */
			अगर (btrfs_root_refs(&gang[i]->root_item) == 0) अणु
				gang[i] = शून्य;
				जारी;
			पूर्ण
			/* grab all the search result क्रम later use */
			gang[i] = btrfs_grab_root(gang[i]);
		पूर्ण
		spin_unlock(&fs_info->fs_roots_radix_lock);

		क्रम (i = 0; i < ret; i++) अणु
			अगर (!gang[i])
				जारी;
			root_objectid = gang[i]->root_key.objectid;
			err = btrfs_orphan_cleanup(gang[i]);
			अगर (err)
				अवरोध;
			btrfs_put_root(gang[i]);
		पूर्ण
		root_objectid++;
	पूर्ण

	/* release the uncleaned roots due to error */
	क्रम (; i < ret; i++) अणु
		अगर (gang[i])
			btrfs_put_root(gang[i]);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक btrfs_commit_super(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_trans_handle *trans;

	mutex_lock(&fs_info->cleaner_mutex);
	btrfs_run_delayed_iमाला_दो(fs_info);
	mutex_unlock(&fs_info->cleaner_mutex);
	wake_up_process(fs_info->cleaner_kthपढ़ो);

	/* रुको until ongoing cleanup work करोne */
	करोwn_ग_लिखो(&fs_info->cleanup_work_sem);
	up_ग_लिखो(&fs_info->cleanup_work_sem);

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);
	वापस btrfs_commit_transaction(trans);
पूर्ण

व्योम __cold बंद_ctree(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक ret;

	set_bit(BTRFS_FS_CLOSING_START, &fs_info->flags);
	/*
	 * We करोn't want the cleaner to start new transactions, add more delayed
	 * iमाला_दो, etc. जबतक we're closing. We can't use kthपढ़ो_stop() yet
	 * because that मुक्तs the task_काष्ठा, and the transaction kthपढ़ो might
	 * still try to wake up the cleaner.
	 */
	kthपढ़ो_park(fs_info->cleaner_kthपढ़ो);

	/* रुको क्रम the qgroup rescan worker to stop */
	btrfs_qgroup_रुको_क्रम_completion(fs_info, false);

	/* रुको क्रम the uuid_scan task to finish */
	करोwn(&fs_info->uuid_tree_rescan_sem);
	/* aव्योम complains from lockdep et al., set sem back to initial state */
	up(&fs_info->uuid_tree_rescan_sem);

	/* छोड़ो restriper - we want to resume on mount */
	btrfs_छोड़ो_balance(fs_info);

	btrfs_dev_replace_suspend_क्रम_unmount(fs_info);

	btrfs_scrub_cancel(fs_info);

	/* रुको क्रम any defraggers to finish */
	रुको_event(fs_info->transaction_रुको,
		   (atomic_पढ़ो(&fs_info->defrag_running) == 0));

	/* clear out the rbtree of defraggable inodes */
	btrfs_cleanup_defrag_inodes(fs_info);

	cancel_work_sync(&fs_info->async_reclaim_work);
	cancel_work_sync(&fs_info->async_data_reclaim_work);
	cancel_work_sync(&fs_info->preempt_reclaim_work);

	cancel_work_sync(&fs_info->reclaim_bgs_work);

	/* Cancel or finish ongoing discard work */
	btrfs_discard_cleanup(fs_info);

	अगर (!sb_rकरोnly(fs_info->sb)) अणु
		/*
		 * The cleaner kthपढ़ो is stopped, so करो one final pass over
		 * unused block groups.
		 */
		btrfs_delete_unused_bgs(fs_info);

		/*
		 * There might be existing delayed inode workers still running
		 * and holding an empty delayed inode item. We must रुको क्रम
		 * them to complete first because they can create a transaction.
		 * This happens when someone calls btrfs_balance_delayed_items()
		 * and then a transaction commit runs the same delayed nodes
		 * beक्रमe any delayed worker has करोne something with the nodes.
		 * We must रुको क्रम any worker here and not at transaction
		 * commit समय since that could cause a deadlock.
		 * This is a very rare हाल.
		 */
		btrfs_flush_workqueue(fs_info->delayed_workers);

		ret = btrfs_commit_super(fs_info);
		अगर (ret)
			btrfs_err(fs_info, "commit super ret %d", ret);
	पूर्ण

	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state) ||
	    test_bit(BTRFS_FS_STATE_TRANS_ABORTED, &fs_info->fs_state))
		btrfs_error_commit_super(fs_info);

	kthपढ़ो_stop(fs_info->transaction_kthपढ़ो);
	kthपढ़ो_stop(fs_info->cleaner_kthपढ़ो);

	ASSERT(list_empty(&fs_info->delayed_iमाला_दो));
	set_bit(BTRFS_FS_CLOSING_DONE, &fs_info->flags);

	अगर (btrfs_check_quota_leak(fs_info)) अणु
		WARN_ON(IS_ENABLED(CONFIG_BTRFS_DEBUG));
		btrfs_err(fs_info, "qgroup reserved space leaked");
	पूर्ण

	btrfs_मुक्त_qgroup_config(fs_info);
	ASSERT(list_empty(&fs_info->delalloc_roots));

	अगर (percpu_counter_sum(&fs_info->delalloc_bytes)) अणु
		btrfs_info(fs_info, "at unmount delalloc count %lld",
		       percpu_counter_sum(&fs_info->delalloc_bytes));
	पूर्ण

	अगर (percpu_counter_sum(&fs_info->ordered_bytes))
		btrfs_info(fs_info, "at unmount dio bytes count %lld",
			   percpu_counter_sum(&fs_info->ordered_bytes));

	btrfs_sysfs_हटाओ_mounted(fs_info);
	btrfs_sysfs_हटाओ_fsid(fs_info->fs_devices);

	btrfs_put_block_group_cache(fs_info);

	/*
	 * we must make sure there is not any पढ़ो request to
	 * submit after we stopping all workers.
	 */
	invalidate_inode_pages2(fs_info->btree_inode->i_mapping);
	btrfs_stop_all_workers(fs_info);

	/* We shouldn't have any transaction खोलो at this poपूर्णांक */
	ASSERT(list_empty(&fs_info->trans_list));

	clear_bit(BTRFS_FS_OPEN, &fs_info->flags);
	मुक्त_root_poपूर्णांकers(fs_info, true);
	btrfs_मुक्त_fs_roots(fs_info);

	/*
	 * We must मुक्त the block groups after dropping the fs_roots as we could
	 * have had an IO error and have left over tree log blocks that aren't
	 * cleaned up until the fs roots are मुक्तd.  This makes the block group
	 * accounting appear to be wrong because there's pending reserved bytes,
	 * so make sure we करो the block group cleanup afterwards.
	 */
	btrfs_मुक्त_block_groups(fs_info);

	iput(fs_info->btree_inode);

#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
	अगर (btrfs_test_opt(fs_info, CHECK_INTEGRITY))
		btrfsic_unmount(fs_info->fs_devices);
#पूर्ण_अगर

	btrfs_mapping_tree_मुक्त(&fs_info->mapping_tree);
	btrfs_बंद_devices(fs_info->fs_devices);
पूर्ण

पूर्णांक btrfs_buffer_uptodate(काष्ठा extent_buffer *buf, u64 parent_transid,
			  पूर्णांक atomic)
अणु
	पूर्णांक ret;
	काष्ठा inode *btree_inode = buf->pages[0]->mapping->host;

	ret = extent_buffer_uptodate(buf);
	अगर (!ret)
		वापस ret;

	ret = verअगरy_parent_transid(&BTRFS_I(btree_inode)->io_tree, buf,
				    parent_transid, atomic);
	अगर (ret == -EAGAIN)
		वापस ret;
	वापस !ret;
पूर्ण

व्योम btrfs_mark_buffer_dirty(काष्ठा extent_buffer *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = buf->fs_info;
	u64 transid = btrfs_header_generation(buf);
	पूर्णांक was_dirty;

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
	/*
	 * This is a fast path so only करो this check अगर we have sanity tests
	 * enabled.  Normal people shouldn't be using unmapped buffers as dirty
	 * outside of the sanity tests.
	 */
	अगर (unlikely(test_bit(EXTENT_BUFFER_UNMAPPED, &buf->bflags)))
		वापस;
#पूर्ण_अगर
	btrfs_निश्चित_tree_locked(buf);
	अगर (transid != fs_info->generation)
		WARN(1, KERN_CRIT "btrfs transid mismatch buffer %llu, found %llu running %llu\n",
			buf->start, transid, fs_info->generation);
	was_dirty = set_extent_buffer_dirty(buf);
	अगर (!was_dirty)
		percpu_counter_add_batch(&fs_info->dirty_metadata_bytes,
					 buf->len,
					 fs_info->dirty_metadata_batch);
#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
	/*
	 * Since btrfs_mark_buffer_dirty() can be called with item poपूर्णांकer set
	 * but item data not updated.
	 * So here we should only check item poपूर्णांकers, not item data.
	 */
	अगर (btrfs_header_level(buf) == 0 &&
	    btrfs_check_leaf_relaxed(buf)) अणु
		btrfs_prपूर्णांक_leaf(buf);
		ASSERT(0);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __btrfs_btree_balance_dirty(काष्ठा btrfs_fs_info *fs_info,
					पूर्णांक flush_delayed)
अणु
	/*
	 * looks as though older kernels can get पूर्णांकo trouble with
	 * this code, they end up stuck in balance_dirty_pages क्रमever
	 */
	पूर्णांक ret;

	अगर (current->flags & PF_MEMALLOC)
		वापस;

	अगर (flush_delayed)
		btrfs_balance_delayed_items(fs_info);

	ret = __percpu_counter_compare(&fs_info->dirty_metadata_bytes,
				     BTRFS_सूचीTY_METADATA_THRESH,
				     fs_info->dirty_metadata_batch);
	अगर (ret > 0) अणु
		balance_dirty_pages_ratelimited(fs_info->btree_inode->i_mapping);
	पूर्ण
पूर्ण

व्योम btrfs_btree_balance_dirty(काष्ठा btrfs_fs_info *fs_info)
अणु
	__btrfs_btree_balance_dirty(fs_info, 1);
पूर्ण

व्योम btrfs_btree_balance_dirty_nodelay(काष्ठा btrfs_fs_info *fs_info)
अणु
	__btrfs_btree_balance_dirty(fs_info, 0);
पूर्ण

पूर्णांक btrfs_पढ़ो_buffer(काष्ठा extent_buffer *buf, u64 parent_transid, पूर्णांक level,
		      काष्ठा btrfs_key *first_key)
अणु
	वापस btree_पढ़ो_extent_buffer_pages(buf, parent_transid,
					      level, first_key);
पूर्ण

अटल व्योम btrfs_error_commit_super(काष्ठा btrfs_fs_info *fs_info)
अणु
	/* cleanup FS via transaction */
	btrfs_cleanup_transaction(fs_info);

	mutex_lock(&fs_info->cleaner_mutex);
	btrfs_run_delayed_iमाला_दो(fs_info);
	mutex_unlock(&fs_info->cleaner_mutex);

	करोwn_ग_लिखो(&fs_info->cleanup_work_sem);
	up_ग_लिखो(&fs_info->cleanup_work_sem);
पूर्ण

अटल व्योम btrfs_drop_all_logs(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *gang[8];
	u64 root_objectid = 0;
	पूर्णांक ret;

	spin_lock(&fs_info->fs_roots_radix_lock);
	जबतक ((ret = radix_tree_gang_lookup(&fs_info->fs_roots_radix,
					     (व्योम **)gang, root_objectid,
					     ARRAY_SIZE(gang))) != 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ret; i++)
			gang[i] = btrfs_grab_root(gang[i]);
		spin_unlock(&fs_info->fs_roots_radix_lock);

		क्रम (i = 0; i < ret; i++) अणु
			अगर (!gang[i])
				जारी;
			root_objectid = gang[i]->root_key.objectid;
			btrfs_मुक्त_log(शून्य, gang[i]);
			btrfs_put_root(gang[i]);
		पूर्ण
		root_objectid++;
		spin_lock(&fs_info->fs_roots_radix_lock);
	पूर्ण
	spin_unlock(&fs_info->fs_roots_radix_lock);
	btrfs_मुक्त_log_root_tree(शून्य, fs_info);
पूर्ण

अटल व्योम btrfs_destroy_ordered_extents(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_ordered_extent *ordered;

	spin_lock(&root->ordered_extent_lock);
	/*
	 * This will just लघु circuit the ordered completion stuff which will
	 * make sure the ordered extent माला_लो properly cleaned up.
	 */
	list_क्रम_each_entry(ordered, &root->ordered_extents,
			    root_extent_list)
		set_bit(BTRFS_ORDERED_IOERR, &ordered->flags);
	spin_unlock(&root->ordered_extent_lock);
पूर्ण

अटल व्योम btrfs_destroy_all_ordered_extents(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा list_head splice;

	INIT_LIST_HEAD(&splice);

	spin_lock(&fs_info->ordered_root_lock);
	list_splice_init(&fs_info->ordered_roots, &splice);
	जबतक (!list_empty(&splice)) अणु
		root = list_first_entry(&splice, काष्ठा btrfs_root,
					ordered_root);
		list_move_tail(&root->ordered_root,
			       &fs_info->ordered_roots);

		spin_unlock(&fs_info->ordered_root_lock);
		btrfs_destroy_ordered_extents(root);

		cond_resched();
		spin_lock(&fs_info->ordered_root_lock);
	पूर्ण
	spin_unlock(&fs_info->ordered_root_lock);

	/*
	 * We need this here because अगर we've been flipped read-only we won't
	 * get sync() from the umount, so we need to make sure any ordered
	 * extents that haven't had their dirty pages IO start ग_लिखोout yet
	 * actually get run and error out properly.
	 */
	btrfs_रुको_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);
पूर्ण

अटल पूर्णांक btrfs_destroy_delayed_refs(काष्ठा btrfs_transaction *trans,
				      काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा rb_node *node;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_delayed_ref_node *ref;
	पूर्णांक ret = 0;

	delayed_refs = &trans->delayed_refs;

	spin_lock(&delayed_refs->lock);
	अगर (atomic_पढ़ो(&delayed_refs->num_entries) == 0) अणु
		spin_unlock(&delayed_refs->lock);
		btrfs_debug(fs_info, "delayed_refs has NO entry");
		वापस ret;
	पूर्ण

	जबतक ((node = rb_first_cached(&delayed_refs->href_root)) != शून्य) अणु
		काष्ठा btrfs_delayed_ref_head *head;
		काष्ठा rb_node *n;
		bool pin_bytes = false;

		head = rb_entry(node, काष्ठा btrfs_delayed_ref_head,
				href_node);
		अगर (btrfs_delayed_ref_lock(delayed_refs, head))
			जारी;

		spin_lock(&head->lock);
		जबतक ((n = rb_first_cached(&head->ref_tree)) != शून्य) अणु
			ref = rb_entry(n, काष्ठा btrfs_delayed_ref_node,
				       ref_node);
			ref->in_tree = 0;
			rb_erase_cached(&ref->ref_node, &head->ref_tree);
			RB_CLEAR_NODE(&ref->ref_node);
			अगर (!list_empty(&ref->add_list))
				list_del(&ref->add_list);
			atomic_dec(&delayed_refs->num_entries);
			btrfs_put_delayed_ref(ref);
		पूर्ण
		अगर (head->must_insert_reserved)
			pin_bytes = true;
		btrfs_मुक्त_delayed_extent_op(head->extent_op);
		btrfs_delete_ref_head(delayed_refs, head);
		spin_unlock(&head->lock);
		spin_unlock(&delayed_refs->lock);
		mutex_unlock(&head->mutex);

		अगर (pin_bytes) अणु
			काष्ठा btrfs_block_group *cache;

			cache = btrfs_lookup_block_group(fs_info, head->bytenr);
			BUG_ON(!cache);

			spin_lock(&cache->space_info->lock);
			spin_lock(&cache->lock);
			cache->pinned += head->num_bytes;
			btrfs_space_info_update_bytes_pinned(fs_info,
				cache->space_info, head->num_bytes);
			cache->reserved -= head->num_bytes;
			cache->space_info->bytes_reserved -= head->num_bytes;
			spin_unlock(&cache->lock);
			spin_unlock(&cache->space_info->lock);
			percpu_counter_add_batch(
				&cache->space_info->total_bytes_pinned,
				head->num_bytes, BTRFS_TOTAL_BYTES_PINNED_BATCH);

			btrfs_put_block_group(cache);

			btrfs_error_unpin_extent_range(fs_info, head->bytenr,
				head->bytenr + head->num_bytes - 1);
		पूर्ण
		btrfs_cleanup_ref_head_accounting(fs_info, delayed_refs, head);
		btrfs_put_delayed_ref_head(head);
		cond_resched();
		spin_lock(&delayed_refs->lock);
	पूर्ण
	btrfs_qgroup_destroy_extent_records(trans);

	spin_unlock(&delayed_refs->lock);

	वापस ret;
पूर्ण

अटल व्योम btrfs_destroy_delalloc_inodes(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_inode *btrfs_inode;
	काष्ठा list_head splice;

	INIT_LIST_HEAD(&splice);

	spin_lock(&root->delalloc_lock);
	list_splice_init(&root->delalloc_inodes, &splice);

	जबतक (!list_empty(&splice)) अणु
		काष्ठा inode *inode = शून्य;
		btrfs_inode = list_first_entry(&splice, काष्ठा btrfs_inode,
					       delalloc_inodes);
		__btrfs_del_delalloc_inode(root, btrfs_inode);
		spin_unlock(&root->delalloc_lock);

		/*
		 * Make sure we get a live inode and that it'll not disappear
		 * meanजबतक.
		 */
		inode = igrab(&btrfs_inode->vfs_inode);
		अगर (inode) अणु
			invalidate_inode_pages2(inode->i_mapping);
			iput(inode);
		पूर्ण
		spin_lock(&root->delalloc_lock);
	पूर्ण
	spin_unlock(&root->delalloc_lock);
पूर्ण

अटल व्योम btrfs_destroy_all_delalloc_inodes(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा list_head splice;

	INIT_LIST_HEAD(&splice);

	spin_lock(&fs_info->delalloc_root_lock);
	list_splice_init(&fs_info->delalloc_roots, &splice);
	जबतक (!list_empty(&splice)) अणु
		root = list_first_entry(&splice, काष्ठा btrfs_root,
					 delalloc_root);
		root = btrfs_grab_root(root);
		BUG_ON(!root);
		spin_unlock(&fs_info->delalloc_root_lock);

		btrfs_destroy_delalloc_inodes(root);
		btrfs_put_root(root);

		spin_lock(&fs_info->delalloc_root_lock);
	पूर्ण
	spin_unlock(&fs_info->delalloc_root_lock);
पूर्ण

अटल पूर्णांक btrfs_destroy_marked_extents(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा extent_io_tree *dirty_pages,
					पूर्णांक mark)
अणु
	पूर्णांक ret;
	काष्ठा extent_buffer *eb;
	u64 start = 0;
	u64 end;

	जबतक (1) अणु
		ret = find_first_extent_bit(dirty_pages, start, &start, &end,
					    mark, शून्य);
		अगर (ret)
			अवरोध;

		clear_extent_bits(dirty_pages, start, end, mark);
		जबतक (start <= end) अणु
			eb = find_extent_buffer(fs_info, start);
			start += fs_info->nodesize;
			अगर (!eb)
				जारी;
			रुको_on_extent_buffer_ग_लिखोback(eb);

			अगर (test_and_clear_bit(EXTENT_BUFFER_सूचीTY,
					       &eb->bflags))
				clear_extent_buffer_dirty(eb);
			मुक्त_extent_buffer_stale(eb);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_destroy_pinned_extent(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा extent_io_tree *unpin)
अणु
	u64 start;
	u64 end;
	पूर्णांक ret;

	जबतक (1) अणु
		काष्ठा extent_state *cached_state = शून्य;

		/*
		 * The btrfs_finish_extent_commit() may get the same range as
		 * ours between find_first_extent_bit and clear_extent_dirty.
		 * Hence, hold the unused_bg_unpin_mutex to aव्योम द्विगुन unpin
		 * the same extent range.
		 */
		mutex_lock(&fs_info->unused_bg_unpin_mutex);
		ret = find_first_extent_bit(unpin, 0, &start, &end,
					    EXTENT_सूचीTY, &cached_state);
		अगर (ret) अणु
			mutex_unlock(&fs_info->unused_bg_unpin_mutex);
			अवरोध;
		पूर्ण

		clear_extent_dirty(unpin, start, end, &cached_state);
		मुक्त_extent_state(cached_state);
		btrfs_error_unpin_extent_range(fs_info, start, end);
		mutex_unlock(&fs_info->unused_bg_unpin_mutex);
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम btrfs_cleanup_bg_io(काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा inode *inode;

	inode = cache->io_ctl.inode;
	अगर (inode) अणु
		invalidate_inode_pages2(inode->i_mapping);
		BTRFS_I(inode)->generation = 0;
		cache->io_ctl.inode = शून्य;
		iput(inode);
	पूर्ण
	ASSERT(cache->io_ctl.pages == शून्य);
	btrfs_put_block_group(cache);
पूर्ण

व्योम btrfs_cleanup_dirty_bgs(काष्ठा btrfs_transaction *cur_trans,
			     काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_block_group *cache;

	spin_lock(&cur_trans->dirty_bgs_lock);
	जबतक (!list_empty(&cur_trans->dirty_bgs)) अणु
		cache = list_first_entry(&cur_trans->dirty_bgs,
					 काष्ठा btrfs_block_group,
					 dirty_list);

		अगर (!list_empty(&cache->io_list)) अणु
			spin_unlock(&cur_trans->dirty_bgs_lock);
			list_del_init(&cache->io_list);
			btrfs_cleanup_bg_io(cache);
			spin_lock(&cur_trans->dirty_bgs_lock);
		पूर्ण

		list_del_init(&cache->dirty_list);
		spin_lock(&cache->lock);
		cache->disk_cache_state = BTRFS_DC_ERROR;
		spin_unlock(&cache->lock);

		spin_unlock(&cur_trans->dirty_bgs_lock);
		btrfs_put_block_group(cache);
		btrfs_delayed_refs_rsv_release(fs_info, 1);
		spin_lock(&cur_trans->dirty_bgs_lock);
	पूर्ण
	spin_unlock(&cur_trans->dirty_bgs_lock);

	/*
	 * Refer to the definition of io_bgs member क्रम details why it's safe
	 * to use it without any locking
	 */
	जबतक (!list_empty(&cur_trans->io_bgs)) अणु
		cache = list_first_entry(&cur_trans->io_bgs,
					 काष्ठा btrfs_block_group,
					 io_list);

		list_del_init(&cache->io_list);
		spin_lock(&cache->lock);
		cache->disk_cache_state = BTRFS_DC_ERROR;
		spin_unlock(&cache->lock);
		btrfs_cleanup_bg_io(cache);
	पूर्ण
पूर्ण

व्योम btrfs_cleanup_one_transaction(काष्ठा btrfs_transaction *cur_trans,
				   काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_device *dev, *पंचांगp;

	btrfs_cleanup_dirty_bgs(cur_trans, fs_info);
	ASSERT(list_empty(&cur_trans->dirty_bgs));
	ASSERT(list_empty(&cur_trans->io_bgs));

	list_क्रम_each_entry_safe(dev, पंचांगp, &cur_trans->dev_update_list,
				 post_commit_list) अणु
		list_del_init(&dev->post_commit_list);
	पूर्ण

	btrfs_destroy_delayed_refs(cur_trans, fs_info);

	cur_trans->state = TRANS_STATE_COMMIT_START;
	wake_up(&fs_info->transaction_blocked_रुको);

	cur_trans->state = TRANS_STATE_UNBLOCKED;
	wake_up(&fs_info->transaction_रुको);

	btrfs_destroy_delayed_inodes(fs_info);

	btrfs_destroy_marked_extents(fs_info, &cur_trans->dirty_pages,
				     EXTENT_सूचीTY);
	btrfs_destroy_pinned_extent(fs_info, &cur_trans->pinned_extents);

	btrfs_मुक्त_redirty_list(cur_trans);

	cur_trans->state =TRANS_STATE_COMPLETED;
	wake_up(&cur_trans->commit_रुको);
पूर्ण

अटल पूर्णांक btrfs_cleanup_transaction(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_transaction *t;

	mutex_lock(&fs_info->transaction_kthपढ़ो_mutex);

	spin_lock(&fs_info->trans_lock);
	जबतक (!list_empty(&fs_info->trans_list)) अणु
		t = list_first_entry(&fs_info->trans_list,
				     काष्ठा btrfs_transaction, list);
		अगर (t->state >= TRANS_STATE_COMMIT_START) अणु
			refcount_inc(&t->use_count);
			spin_unlock(&fs_info->trans_lock);
			btrfs_रुको_क्रम_commit(fs_info, t->transid);
			btrfs_put_transaction(t);
			spin_lock(&fs_info->trans_lock);
			जारी;
		पूर्ण
		अगर (t == fs_info->running_transaction) अणु
			t->state = TRANS_STATE_COMMIT_DOING;
			spin_unlock(&fs_info->trans_lock);
			/*
			 * We रुको क्रम 0 num_ग_लिखोrs since we करोn't hold a trans
			 * handle खोलो currently क्रम this transaction.
			 */
			रुको_event(t->ग_लिखोr_रुको,
				   atomic_पढ़ो(&t->num_ग_लिखोrs) == 0);
		पूर्ण अन्यथा अणु
			spin_unlock(&fs_info->trans_lock);
		पूर्ण
		btrfs_cleanup_one_transaction(t, fs_info);

		spin_lock(&fs_info->trans_lock);
		अगर (t == fs_info->running_transaction)
			fs_info->running_transaction = शून्य;
		list_del_init(&t->list);
		spin_unlock(&fs_info->trans_lock);

		btrfs_put_transaction(t);
		trace_btrfs_transaction_commit(fs_info->tree_root);
		spin_lock(&fs_info->trans_lock);
	पूर्ण
	spin_unlock(&fs_info->trans_lock);
	btrfs_destroy_all_ordered_extents(fs_info);
	btrfs_destroy_delayed_inodes(fs_info);
	btrfs_निश्चित_delayed_root_empty(fs_info);
	btrfs_destroy_all_delalloc_inodes(fs_info);
	btrfs_drop_all_logs(fs_info);
	mutex_unlock(&fs_info->transaction_kthपढ़ो_mutex);

	वापस 0;
पूर्ण

पूर्णांक btrfs_init_root_मुक्त_objectid(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_path *path;
	पूर्णांक ret;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_key search_key;
	काष्ठा btrfs_key found_key;
	पूर्णांक slot;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	search_key.objectid = BTRFS_LAST_FREE_OBJECTID;
	search_key.type = -1;
	search_key.offset = (u64)-1;
	ret = btrfs_search_slot(शून्य, root, &search_key, path, 0, 0);
	अगर (ret < 0)
		जाओ error;
	BUG_ON(ret == 0); /* Corruption */
	अगर (path->slots[0] > 0) अणु
		slot = path->slots[0] - 1;
		l = path->nodes[0];
		btrfs_item_key_to_cpu(l, &found_key, slot);
		root->मुक्त_objectid = max_t(u64, found_key.objectid + 1,
					    BTRFS_FIRST_FREE_OBJECTID);
	पूर्ण अन्यथा अणु
		root->मुक्त_objectid = BTRFS_FIRST_FREE_OBJECTID;
	पूर्ण
	ret = 0;
error:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_get_मुक्त_objectid(काष्ठा btrfs_root *root, u64 *objectid)
अणु
	पूर्णांक ret;
	mutex_lock(&root->objectid_mutex);

	अगर (unlikely(root->मुक्त_objectid >= BTRFS_LAST_FREE_OBJECTID)) अणु
		btrfs_warn(root->fs_info,
			   "the objectid of root %llu reaches its highest value",
			   root->root_key.objectid);
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	*objectid = root->मुक्त_objectid++;
	ret = 0;
out:
	mutex_unlock(&root->objectid_mutex);
	वापस ret;
पूर्ण
