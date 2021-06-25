<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STRATO AG 2011.  All rights reserved.
 */

/*
 * This module can be used to catch हालs when the btrfs kernel
 * code executes ग_लिखो requests to the disk that bring the file
 * प्रणाली in an inconsistent state. In such a state, a घातer-loss
 * or kernel panic event would cause that the data on disk is
 * lost or at least damaged.
 *
 * Code is added that examines all block ग_लिखो requests during
 * runसमय (including ग_लिखोs of the super block). Three rules
 * are verअगरied and an error is prपूर्णांकed on violation of the
 * rules:
 * 1. It is not allowed to ग_लिखो a disk block which is
 *    currently referenced by the super block (either directly
 *    or indirectly).
 * 2. When a super block is written, it is verअगरied that all
 *    referenced (directly or indirectly) blocks fulfill the
 *    following requirements:
 *    2a. All referenced blocks have either been present when
 *        the file प्रणाली was mounted, (i.e., they have been
 *        referenced by the super block) or they have been
 *        written since then and the ग_लिखो completion callback
 *        was called and no ग_लिखो error was indicated and a
 *        FLUSH request to the device where these blocks are
 *        located was received and completed.
 *    2b. All referenced blocks need to have a generation
 *        number which is equal to the parent's number.
 *
 * One issue that was found using this module was that the log
 * tree on disk became temporarily corrupted because disk blocks
 * that had been in use क्रम the log tree had been मुक्तd and
 * reused too early, जबतक being referenced by the written super
 * block.
 *
 * The search term in the kernel log that can be used to filter
 * on the existence of detected पूर्णांकegrity issues is
 * "btrfs: attempt".
 *
 * The पूर्णांकegrity check is enabled via mount options. These
 * mount options are only supported अगर the पूर्णांकegrity check
 * tool is compiled by defining BTRFS_FS_CHECK_INTEGRITY.
 *
 * Example #1, apply पूर्णांकegrity checks to all metadata:
 * mount /dev/sdb1 /mnt -o check_पूर्णांक
 *
 * Example #2, apply पूर्णांकegrity checks to all metadata and
 * to data extents:
 * mount /dev/sdb1 /mnt -o check_पूर्णांक_data
 *
 * Example #3, apply पूर्णांकegrity checks to all metadata and dump
 * the tree that the super block references to kernel messages
 * each समय after a super block was written:
 * mount /dev/sdb1 /mnt -o check_पूर्णांक,check_पूर्णांक_prपूर्णांक_mask=263
 *
 * If the पूर्णांकegrity check tool is included and activated in
 * the mount options, plenty of kernel memory is used, and
 * plenty of additional CPU cycles are spent. Enabling this
 * functionality is not पूर्णांकended क्रम normal use. In most
 * हालs, unless you are a btrfs developer who needs to verअगरy
 * the पूर्णांकegrity of (super)-block ग_लिखो requests, करो not
 * enable the config option BTRFS_FS_CHECK_INTEGRITY to
 * include and compile the पूर्णांकegrity check tool.
 *
 * Expect millions of lines of inक्रमmation in the kernel log with an
 * enabled check_पूर्णांक_prपूर्णांक_mask. Thereक्रमe set LOG_BUF_SHIFT in the
 * kernel config to at least 26 (which is 64MB). Usually the value is
 * limited to 21 (which is 2MB) in init/Kconfig. The file needs to be
 * changed like this beक्रमe LOG_BUF_SHIFT can be set to a high value:
 * config LOG_BUF_SHIFT
 *       पूर्णांक "Kernel log buffer size (16 => 64KB, 17 => 128KB)"
 *       range 12 30
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/genhd.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <crypto/hash.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "extent_io.h"
#समावेश "volumes.h"
#समावेश "print-tree.h"
#समावेश "locking.h"
#समावेश "check-integrity.h"
#समावेश "rcu-string.h"
#समावेश "compression.h"

#घोषणा BTRFSIC_BLOCK_HASHTABLE_SIZE 0x10000
#घोषणा BTRFSIC_BLOCK_LINK_HASHTABLE_SIZE 0x10000
#घोषणा BTRFSIC_DEV2STATE_HASHTABLE_SIZE 0x100
#घोषणा BTRFSIC_BLOCK_MAGIC_NUMBER 0x14491051
#घोषणा BTRFSIC_BLOCK_LINK_MAGIC_NUMBER 0x11070807
#घोषणा BTRFSIC_DEV2STATE_MAGIC_NUMBER 0x20111530
#घोषणा BTRFSIC_BLOCK_STACK_FRAME_MAGIC_NUMBER 20111300
#घोषणा BTRFSIC_TREE_DUMP_MAX_INDENT_LEVEL (200 - 6)	/* in अक्षरacters,
							 * excluding " [...]" */
#घोषणा BTRFSIC_GENERATION_UNKNOWN ((u64)-1)

/*
 * The definition of the biपंचांगask fields क्रम the prपूर्णांक_mask.
 * They are specअगरied with the mount option check_पूर्णांकegrity_prपूर्णांक_mask.
 */
#घोषणा BTRFSIC_PRINT_MASK_SUPERBLOCK_WRITE			0x00000001
#घोषणा BTRFSIC_PRINT_MASK_ROOT_CHUNK_LOG_TREE_LOCATION		0x00000002
#घोषणा BTRFSIC_PRINT_MASK_TREE_AFTER_SB_WRITE			0x00000004
#घोषणा BTRFSIC_PRINT_MASK_TREE_BEFORE_SB_WRITE			0x00000008
#घोषणा BTRFSIC_PRINT_MASK_SUBMIT_BIO_BH			0x00000010
#घोषणा BTRFSIC_PRINT_MASK_END_IO_BIO_BH			0x00000020
#घोषणा BTRFSIC_PRINT_MASK_VERBOSE				0x00000040
#घोषणा BTRFSIC_PRINT_MASK_VERY_VERBOSE				0x00000080
#घोषणा BTRFSIC_PRINT_MASK_INITIAL_TREE				0x00000100
#घोषणा BTRFSIC_PRINT_MASK_INITIAL_ALL_TREES			0x00000200
#घोषणा BTRFSIC_PRINT_MASK_INITIAL_DATABASE			0x00000400
#घोषणा BTRFSIC_PRINT_MASK_NUM_COPIES				0x00000800
#घोषणा BTRFSIC_PRINT_MASK_TREE_WITH_ALL_MIRRORS		0x00001000
#घोषणा BTRFSIC_PRINT_MASK_SUBMIT_BIO_BH_VERBOSE		0x00002000

काष्ठा btrfsic_dev_state;
काष्ठा btrfsic_state;

काष्ठा btrfsic_block अणु
	u32 magic_num;		/* only used क्रम debug purposes */
	अचिन्हित पूर्णांक is_metadata:1;	/* अगर it is meta-data, not data-data */
	अचिन्हित पूर्णांक is_superblock:1;	/* अगर it is one of the superblocks */
	अचिन्हित पूर्णांक is_ioकरोne:1;	/* अगर is करोne by lower subप्रणाली */
	अचिन्हित पूर्णांक ioकरोne_w_error:1;	/* error was indicated to endio */
	अचिन्हित पूर्णांक never_written:1;	/* block was added because it was
					 * referenced, not because it was
					 * written */
	अचिन्हित पूर्णांक mirror_num;	/* large enough to hold
					 * BTRFS_SUPER_MIRROR_MAX */
	काष्ठा btrfsic_dev_state *dev_state;
	u64 dev_bytenr;		/* key, physical byte num on disk */
	u64 logical_bytenr;	/* logical byte num on disk */
	u64 generation;
	काष्ठा btrfs_disk_key disk_key;	/* extra info to prपूर्णांक in हाल of
					 * issues, will not always be correct */
	काष्ठा list_head collision_resolving_node;	/* list node */
	काष्ठा list_head all_blocks_node;	/* list node */

	/* the following two lists contain block_link items */
	काष्ठा list_head ref_to_list;	/* list */
	काष्ठा list_head ref_from_list;	/* list */
	काष्ठा btrfsic_block *next_in_same_bio;
	व्योम *orig_bio_निजी;
	bio_end_io_t *orig_bio_end_io;
	पूर्णांक submit_bio_bh_rw;
	u64 flush_gen; /* only valid अगर !never_written */
पूर्ण;

/*
 * Elements of this type are allocated dynamically and required because
 * each block object can refer to and can be ref from multiple blocks.
 * The key to lookup them in the hashtable is the dev_bytenr of
 * the block ref to plus the one from the block referred from.
 * The fact that they are searchable via a hashtable and that a
 * ref_cnt is मुख्यtained is not required क्रम the btrfs पूर्णांकegrity
 * check algorithm itself, it is only used to make the output more
 * beautअगरul in हाल that an error is detected (an error is defined
 * as a ग_लिखो operation to a block जबतक that block is still referenced).
 */
काष्ठा btrfsic_block_link अणु
	u32 magic_num;		/* only used क्रम debug purposes */
	u32 ref_cnt;
	काष्ठा list_head node_ref_to;	/* list node */
	काष्ठा list_head node_ref_from;	/* list node */
	काष्ठा list_head collision_resolving_node;	/* list node */
	काष्ठा btrfsic_block *block_ref_to;
	काष्ठा btrfsic_block *block_ref_from;
	u64 parent_generation;
पूर्ण;

काष्ठा btrfsic_dev_state अणु
	u32 magic_num;		/* only used क्रम debug purposes */
	काष्ठा block_device *bdev;
	काष्ठा btrfsic_state *state;
	काष्ठा list_head collision_resolving_node;	/* list node */
	काष्ठा btrfsic_block dummy_block_क्रम_bio_bh_flush;
	u64 last_flush_gen;
	अक्षर name[BDEVNAME_SIZE];
पूर्ण;

काष्ठा btrfsic_block_hashtable अणु
	काष्ठा list_head table[BTRFSIC_BLOCK_HASHTABLE_SIZE];
पूर्ण;

काष्ठा btrfsic_block_link_hashtable अणु
	काष्ठा list_head table[BTRFSIC_BLOCK_LINK_HASHTABLE_SIZE];
पूर्ण;

काष्ठा btrfsic_dev_state_hashtable अणु
	काष्ठा list_head table[BTRFSIC_DEV2STATE_HASHTABLE_SIZE];
पूर्ण;

काष्ठा btrfsic_block_data_ctx अणु
	u64 start;		/* भव bytenr */
	u64 dev_bytenr;		/* physical bytenr on device */
	u32 len;
	काष्ठा btrfsic_dev_state *dev;
	अक्षर **datav;
	काष्ठा page **pagev;
	व्योम *mem_to_मुक्त;
पूर्ण;

/* This काष्ठाure is used to implement recursion without occupying
 * any stack space, refer to btrfsic_process_metablock() */
काष्ठा btrfsic_stack_frame अणु
	u32 magic;
	u32 nr;
	पूर्णांक error;
	पूर्णांक i;
	पूर्णांक limit_nesting;
	पूर्णांक num_copies;
	पूर्णांक mirror_num;
	काष्ठा btrfsic_block *block;
	काष्ठा btrfsic_block_data_ctx *block_ctx;
	काष्ठा btrfsic_block *next_block;
	काष्ठा btrfsic_block_data_ctx next_block_ctx;
	काष्ठा btrfs_header *hdr;
	काष्ठा btrfsic_stack_frame *prev;
पूर्ण;

/* Some state per mounted fileप्रणाली */
काष्ठा btrfsic_state अणु
	u32 prपूर्णांक_mask;
	पूर्णांक include_extent_data;
	काष्ठा list_head all_blocks_list;
	काष्ठा btrfsic_block_hashtable block_hashtable;
	काष्ठा btrfsic_block_link_hashtable block_link_hashtable;
	काष्ठा btrfs_fs_info *fs_info;
	u64 max_superblock_generation;
	काष्ठा btrfsic_block *latest_superblock;
	u32 metablock_size;
	u32 datablock_size;
पूर्ण;

अटल व्योम btrfsic_block_init(काष्ठा btrfsic_block *b);
अटल काष्ठा btrfsic_block *btrfsic_block_alloc(व्योम);
अटल व्योम btrfsic_block_मुक्त(काष्ठा btrfsic_block *b);
अटल व्योम btrfsic_block_link_init(काष्ठा btrfsic_block_link *n);
अटल काष्ठा btrfsic_block_link *btrfsic_block_link_alloc(व्योम);
अटल व्योम btrfsic_block_link_मुक्त(काष्ठा btrfsic_block_link *n);
अटल व्योम btrfsic_dev_state_init(काष्ठा btrfsic_dev_state *ds);
अटल काष्ठा btrfsic_dev_state *btrfsic_dev_state_alloc(व्योम);
अटल व्योम btrfsic_dev_state_मुक्त(काष्ठा btrfsic_dev_state *ds);
अटल व्योम btrfsic_block_hashtable_init(काष्ठा btrfsic_block_hashtable *h);
अटल व्योम btrfsic_block_hashtable_add(काष्ठा btrfsic_block *b,
					काष्ठा btrfsic_block_hashtable *h);
अटल व्योम btrfsic_block_hashtable_हटाओ(काष्ठा btrfsic_block *b);
अटल काष्ठा btrfsic_block *btrfsic_block_hashtable_lookup(
		काष्ठा block_device *bdev,
		u64 dev_bytenr,
		काष्ठा btrfsic_block_hashtable *h);
अटल व्योम btrfsic_block_link_hashtable_init(
		काष्ठा btrfsic_block_link_hashtable *h);
अटल व्योम btrfsic_block_link_hashtable_add(
		काष्ठा btrfsic_block_link *l,
		काष्ठा btrfsic_block_link_hashtable *h);
अटल व्योम btrfsic_block_link_hashtable_हटाओ(काष्ठा btrfsic_block_link *l);
अटल काष्ठा btrfsic_block_link *btrfsic_block_link_hashtable_lookup(
		काष्ठा block_device *bdev_ref_to,
		u64 dev_bytenr_ref_to,
		काष्ठा block_device *bdev_ref_from,
		u64 dev_bytenr_ref_from,
		काष्ठा btrfsic_block_link_hashtable *h);
अटल व्योम btrfsic_dev_state_hashtable_init(
		काष्ठा btrfsic_dev_state_hashtable *h);
अटल व्योम btrfsic_dev_state_hashtable_add(
		काष्ठा btrfsic_dev_state *ds,
		काष्ठा btrfsic_dev_state_hashtable *h);
अटल व्योम btrfsic_dev_state_hashtable_हटाओ(काष्ठा btrfsic_dev_state *ds);
अटल काष्ठा btrfsic_dev_state *btrfsic_dev_state_hashtable_lookup(dev_t dev,
		काष्ठा btrfsic_dev_state_hashtable *h);
अटल काष्ठा btrfsic_stack_frame *btrfsic_stack_frame_alloc(व्योम);
अटल व्योम btrfsic_stack_frame_मुक्त(काष्ठा btrfsic_stack_frame *sf);
अटल पूर्णांक btrfsic_process_superblock(काष्ठा btrfsic_state *state,
				      काष्ठा btrfs_fs_devices *fs_devices);
अटल पूर्णांक btrfsic_process_metablock(काष्ठा btrfsic_state *state,
				     काष्ठा btrfsic_block *block,
				     काष्ठा btrfsic_block_data_ctx *block_ctx,
				     पूर्णांक limit_nesting, पूर्णांक क्रमce_ioकरोne_flag);
अटल व्योम btrfsic_पढ़ो_from_block_data(
	काष्ठा btrfsic_block_data_ctx *block_ctx,
	व्योम *dst, u32 offset, माप_प्रकार len);
अटल पूर्णांक btrfsic_create_link_to_next_block(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block *block,
		काष्ठा btrfsic_block_data_ctx
		*block_ctx, u64 next_bytenr,
		पूर्णांक limit_nesting,
		काष्ठा btrfsic_block_data_ctx *next_block_ctx,
		काष्ठा btrfsic_block **next_blockp,
		पूर्णांक क्रमce_ioकरोne_flag,
		पूर्णांक *num_copiesp, पूर्णांक *mirror_nump,
		काष्ठा btrfs_disk_key *disk_key,
		u64 parent_generation);
अटल पूर्णांक btrfsic_handle_extent_data(काष्ठा btrfsic_state *state,
				      काष्ठा btrfsic_block *block,
				      काष्ठा btrfsic_block_data_ctx *block_ctx,
				      u32 item_offset, पूर्णांक क्रमce_ioकरोne_flag);
अटल पूर्णांक btrfsic_map_block(काष्ठा btrfsic_state *state, u64 bytenr, u32 len,
			     काष्ठा btrfsic_block_data_ctx *block_ctx_out,
			     पूर्णांक mirror_num);
अटल व्योम btrfsic_release_block_ctx(काष्ठा btrfsic_block_data_ctx *block_ctx);
अटल पूर्णांक btrfsic_पढ़ो_block(काष्ठा btrfsic_state *state,
			      काष्ठा btrfsic_block_data_ctx *block_ctx);
अटल व्योम btrfsic_dump_database(काष्ठा btrfsic_state *state);
अटल पूर्णांक btrfsic_test_क्रम_metadata(काष्ठा btrfsic_state *state,
				     अक्षर **datav, अचिन्हित पूर्णांक num_pages);
अटल व्योम btrfsic_process_written_block(काष्ठा btrfsic_dev_state *dev_state,
					  u64 dev_bytenr, अक्षर **mapped_datav,
					  अचिन्हित पूर्णांक num_pages,
					  काष्ठा bio *bio, पूर्णांक *bio_is_patched,
					  पूर्णांक submit_bio_bh_rw);
अटल पूर्णांक btrfsic_process_written_superblock(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block *स्थिर block,
		काष्ठा btrfs_super_block *स्थिर super_hdr);
अटल व्योम btrfsic_bio_end_io(काष्ठा bio *bp);
अटल पूर्णांक btrfsic_is_block_ref_by_superblock(स्थिर काष्ठा btrfsic_state *state,
					      स्थिर काष्ठा btrfsic_block *block,
					      पूर्णांक recursion_level);
अटल पूर्णांक btrfsic_check_all_ref_blocks(काष्ठा btrfsic_state *state,
					काष्ठा btrfsic_block *स्थिर block,
					पूर्णांक recursion_level);
अटल व्योम btrfsic_prपूर्णांक_add_link(स्थिर काष्ठा btrfsic_state *state,
				   स्थिर काष्ठा btrfsic_block_link *l);
अटल व्योम btrfsic_prपूर्णांक_rem_link(स्थिर काष्ठा btrfsic_state *state,
				   स्थिर काष्ठा btrfsic_block_link *l);
अटल अक्षर btrfsic_get_block_type(स्थिर काष्ठा btrfsic_state *state,
				   स्थिर काष्ठा btrfsic_block *block);
अटल व्योम btrfsic_dump_tree(स्थिर काष्ठा btrfsic_state *state);
अटल व्योम btrfsic_dump_tree_sub(स्थिर काष्ठा btrfsic_state *state,
				  स्थिर काष्ठा btrfsic_block *block,
				  पूर्णांक indent_level);
अटल काष्ठा btrfsic_block_link *btrfsic_block_link_lookup_or_add(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block_data_ctx *next_block_ctx,
		काष्ठा btrfsic_block *next_block,
		काष्ठा btrfsic_block *from_block,
		u64 parent_generation);
अटल काष्ठा btrfsic_block *btrfsic_block_lookup_or_add(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block_data_ctx *block_ctx,
		स्थिर अक्षर *additional_string,
		पूर्णांक is_metadata,
		पूर्णांक is_ioकरोne,
		पूर्णांक never_written,
		पूर्णांक mirror_num,
		पूर्णांक *was_created);
अटल पूर्णांक btrfsic_process_superblock_dev_mirror(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_dev_state *dev_state,
		काष्ठा btrfs_device *device,
		पूर्णांक superblock_mirror_num,
		काष्ठा btrfsic_dev_state **selected_dev_state,
		काष्ठा btrfs_super_block *selected_super);
अटल काष्ठा btrfsic_dev_state *btrfsic_dev_state_lookup(dev_t dev);
अटल व्योम btrfsic_cmp_log_and_dev_bytenr(काष्ठा btrfsic_state *state,
					   u64 bytenr,
					   काष्ठा btrfsic_dev_state *dev_state,
					   u64 dev_bytenr);

अटल काष्ठा mutex btrfsic_mutex;
अटल पूर्णांक btrfsic_is_initialized;
अटल काष्ठा btrfsic_dev_state_hashtable btrfsic_dev_state_hashtable;


अटल व्योम btrfsic_block_init(काष्ठा btrfsic_block *b)
अणु
	b->magic_num = BTRFSIC_BLOCK_MAGIC_NUMBER;
	b->dev_state = शून्य;
	b->dev_bytenr = 0;
	b->logical_bytenr = 0;
	b->generation = BTRFSIC_GENERATION_UNKNOWN;
	b->disk_key.objectid = 0;
	b->disk_key.type = 0;
	b->disk_key.offset = 0;
	b->is_metadata = 0;
	b->is_superblock = 0;
	b->is_ioकरोne = 0;
	b->ioकरोne_w_error = 0;
	b->never_written = 0;
	b->mirror_num = 0;
	b->next_in_same_bio = शून्य;
	b->orig_bio_निजी = शून्य;
	b->orig_bio_end_io = शून्य;
	INIT_LIST_HEAD(&b->collision_resolving_node);
	INIT_LIST_HEAD(&b->all_blocks_node);
	INIT_LIST_HEAD(&b->ref_to_list);
	INIT_LIST_HEAD(&b->ref_from_list);
	b->submit_bio_bh_rw = 0;
	b->flush_gen = 0;
पूर्ण

अटल काष्ठा btrfsic_block *btrfsic_block_alloc(व्योम)
अणु
	काष्ठा btrfsic_block *b;

	b = kzalloc(माप(*b), GFP_NOFS);
	अगर (शून्य != b)
		btrfsic_block_init(b);

	वापस b;
पूर्ण

अटल व्योम btrfsic_block_मुक्त(काष्ठा btrfsic_block *b)
अणु
	BUG_ON(!(शून्य == b || BTRFSIC_BLOCK_MAGIC_NUMBER == b->magic_num));
	kमुक्त(b);
पूर्ण

अटल व्योम btrfsic_block_link_init(काष्ठा btrfsic_block_link *l)
अणु
	l->magic_num = BTRFSIC_BLOCK_LINK_MAGIC_NUMBER;
	l->ref_cnt = 1;
	INIT_LIST_HEAD(&l->node_ref_to);
	INIT_LIST_HEAD(&l->node_ref_from);
	INIT_LIST_HEAD(&l->collision_resolving_node);
	l->block_ref_to = शून्य;
	l->block_ref_from = शून्य;
पूर्ण

अटल काष्ठा btrfsic_block_link *btrfsic_block_link_alloc(व्योम)
अणु
	काष्ठा btrfsic_block_link *l;

	l = kzalloc(माप(*l), GFP_NOFS);
	अगर (शून्य != l)
		btrfsic_block_link_init(l);

	वापस l;
पूर्ण

अटल व्योम btrfsic_block_link_मुक्त(काष्ठा btrfsic_block_link *l)
अणु
	BUG_ON(!(शून्य == l || BTRFSIC_BLOCK_LINK_MAGIC_NUMBER == l->magic_num));
	kमुक्त(l);
पूर्ण

अटल व्योम btrfsic_dev_state_init(काष्ठा btrfsic_dev_state *ds)
अणु
	ds->magic_num = BTRFSIC_DEV2STATE_MAGIC_NUMBER;
	ds->bdev = शून्य;
	ds->state = शून्य;
	ds->name[0] = '\0';
	INIT_LIST_HEAD(&ds->collision_resolving_node);
	ds->last_flush_gen = 0;
	btrfsic_block_init(&ds->dummy_block_क्रम_bio_bh_flush);
	ds->dummy_block_क्रम_bio_bh_flush.is_ioकरोne = 1;
	ds->dummy_block_क्रम_bio_bh_flush.dev_state = ds;
पूर्ण

अटल काष्ठा btrfsic_dev_state *btrfsic_dev_state_alloc(व्योम)
अणु
	काष्ठा btrfsic_dev_state *ds;

	ds = kzalloc(माप(*ds), GFP_NOFS);
	अगर (शून्य != ds)
		btrfsic_dev_state_init(ds);

	वापस ds;
पूर्ण

अटल व्योम btrfsic_dev_state_मुक्त(काष्ठा btrfsic_dev_state *ds)
अणु
	BUG_ON(!(शून्य == ds ||
		 BTRFSIC_DEV2STATE_MAGIC_NUMBER == ds->magic_num));
	kमुक्त(ds);
पूर्ण

अटल व्योम btrfsic_block_hashtable_init(काष्ठा btrfsic_block_hashtable *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFSIC_BLOCK_HASHTABLE_SIZE; i++)
		INIT_LIST_HEAD(h->table + i);
पूर्ण

अटल व्योम btrfsic_block_hashtable_add(काष्ठा btrfsic_block *b,
					काष्ठा btrfsic_block_hashtable *h)
अणु
	स्थिर अचिन्हित पूर्णांक hashval =
	    (((अचिन्हित पूर्णांक)(b->dev_bytenr >> 16)) ^
	     ((अचिन्हित पूर्णांक)((uपूर्णांकptr_t)b->dev_state->bdev))) &
	     (BTRFSIC_BLOCK_HASHTABLE_SIZE - 1);

	list_add(&b->collision_resolving_node, h->table + hashval);
पूर्ण

अटल व्योम btrfsic_block_hashtable_हटाओ(काष्ठा btrfsic_block *b)
अणु
	list_del(&b->collision_resolving_node);
पूर्ण

अटल काष्ठा btrfsic_block *btrfsic_block_hashtable_lookup(
		काष्ठा block_device *bdev,
		u64 dev_bytenr,
		काष्ठा btrfsic_block_hashtable *h)
अणु
	स्थिर अचिन्हित पूर्णांक hashval =
	    (((अचिन्हित पूर्णांक)(dev_bytenr >> 16)) ^
	     ((अचिन्हित पूर्णांक)((uपूर्णांकptr_t)bdev))) &
	     (BTRFSIC_BLOCK_HASHTABLE_SIZE - 1);
	काष्ठा btrfsic_block *b;

	list_क्रम_each_entry(b, h->table + hashval, collision_resolving_node) अणु
		अगर (b->dev_state->bdev == bdev && b->dev_bytenr == dev_bytenr)
			वापस b;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम btrfsic_block_link_hashtable_init(
		काष्ठा btrfsic_block_link_hashtable *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFSIC_BLOCK_LINK_HASHTABLE_SIZE; i++)
		INIT_LIST_HEAD(h->table + i);
पूर्ण

अटल व्योम btrfsic_block_link_hashtable_add(
		काष्ठा btrfsic_block_link *l,
		काष्ठा btrfsic_block_link_hashtable *h)
अणु
	स्थिर अचिन्हित पूर्णांक hashval =
	    (((अचिन्हित पूर्णांक)(l->block_ref_to->dev_bytenr >> 16)) ^
	     ((अचिन्हित पूर्णांक)(l->block_ref_from->dev_bytenr >> 16)) ^
	     ((अचिन्हित पूर्णांक)((uपूर्णांकptr_t)l->block_ref_to->dev_state->bdev)) ^
	     ((अचिन्हित पूर्णांक)((uपूर्णांकptr_t)l->block_ref_from->dev_state->bdev)))
	     & (BTRFSIC_BLOCK_LINK_HASHTABLE_SIZE - 1);

	BUG_ON(शून्य == l->block_ref_to);
	BUG_ON(शून्य == l->block_ref_from);
	list_add(&l->collision_resolving_node, h->table + hashval);
पूर्ण

अटल व्योम btrfsic_block_link_hashtable_हटाओ(काष्ठा btrfsic_block_link *l)
अणु
	list_del(&l->collision_resolving_node);
पूर्ण

अटल काष्ठा btrfsic_block_link *btrfsic_block_link_hashtable_lookup(
		काष्ठा block_device *bdev_ref_to,
		u64 dev_bytenr_ref_to,
		काष्ठा block_device *bdev_ref_from,
		u64 dev_bytenr_ref_from,
		काष्ठा btrfsic_block_link_hashtable *h)
अणु
	स्थिर अचिन्हित पूर्णांक hashval =
	    (((अचिन्हित पूर्णांक)(dev_bytenr_ref_to >> 16)) ^
	     ((अचिन्हित पूर्णांक)(dev_bytenr_ref_from >> 16)) ^
	     ((अचिन्हित पूर्णांक)((uपूर्णांकptr_t)bdev_ref_to)) ^
	     ((अचिन्हित पूर्णांक)((uपूर्णांकptr_t)bdev_ref_from))) &
	     (BTRFSIC_BLOCK_LINK_HASHTABLE_SIZE - 1);
	काष्ठा btrfsic_block_link *l;

	list_क्रम_each_entry(l, h->table + hashval, collision_resolving_node) अणु
		BUG_ON(शून्य == l->block_ref_to);
		BUG_ON(शून्य == l->block_ref_from);
		अगर (l->block_ref_to->dev_state->bdev == bdev_ref_to &&
		    l->block_ref_to->dev_bytenr == dev_bytenr_ref_to &&
		    l->block_ref_from->dev_state->bdev == bdev_ref_from &&
		    l->block_ref_from->dev_bytenr == dev_bytenr_ref_from)
			वापस l;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम btrfsic_dev_state_hashtable_init(
		काष्ठा btrfsic_dev_state_hashtable *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFSIC_DEV2STATE_HASHTABLE_SIZE; i++)
		INIT_LIST_HEAD(h->table + i);
पूर्ण

अटल व्योम btrfsic_dev_state_hashtable_add(
		काष्ठा btrfsic_dev_state *ds,
		काष्ठा btrfsic_dev_state_hashtable *h)
अणु
	स्थिर अचिन्हित पूर्णांक hashval =
	    (((अचिन्हित पूर्णांक)((uपूर्णांकptr_t)ds->bdev->bd_dev)) &
	     (BTRFSIC_DEV2STATE_HASHTABLE_SIZE - 1));

	list_add(&ds->collision_resolving_node, h->table + hashval);
पूर्ण

अटल व्योम btrfsic_dev_state_hashtable_हटाओ(काष्ठा btrfsic_dev_state *ds)
अणु
	list_del(&ds->collision_resolving_node);
पूर्ण

अटल काष्ठा btrfsic_dev_state *btrfsic_dev_state_hashtable_lookup(dev_t dev,
		काष्ठा btrfsic_dev_state_hashtable *h)
अणु
	स्थिर अचिन्हित पूर्णांक hashval =
		dev & (BTRFSIC_DEV2STATE_HASHTABLE_SIZE - 1);
	काष्ठा btrfsic_dev_state *ds;

	list_क्रम_each_entry(ds, h->table + hashval, collision_resolving_node) अणु
		अगर (ds->bdev->bd_dev == dev)
			वापस ds;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक btrfsic_process_superblock(काष्ठा btrfsic_state *state,
				      काष्ठा btrfs_fs_devices *fs_devices)
अणु
	काष्ठा btrfs_super_block *selected_super;
	काष्ठा list_head *dev_head = &fs_devices->devices;
	काष्ठा btrfs_device *device;
	काष्ठा btrfsic_dev_state *selected_dev_state = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक pass;

	selected_super = kzalloc(माप(*selected_super), GFP_NOFS);
	अगर (!selected_super)
		वापस -ENOMEM;

	list_क्रम_each_entry(device, dev_head, dev_list) अणु
		पूर्णांक i;
		काष्ठा btrfsic_dev_state *dev_state;

		अगर (!device->bdev || !device->name)
			जारी;

		dev_state = btrfsic_dev_state_lookup(device->bdev->bd_dev);
		BUG_ON(शून्य == dev_state);
		क्रम (i = 0; i < BTRFS_SUPER_MIRROR_MAX; i++) अणु
			ret = btrfsic_process_superblock_dev_mirror(
					state, dev_state, device, i,
					&selected_dev_state, selected_super);
			अगर (0 != ret && 0 == i) अणु
				kमुक्त(selected_super);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (शून्य == state->latest_superblock) अणु
		pr_info("btrfsic: no superblock found!\n");
		kमुक्त(selected_super);
		वापस -1;
	पूर्ण

	क्रम (pass = 0; pass < 3; pass++) अणु
		पूर्णांक num_copies;
		पूर्णांक mirror_num;
		u64 next_bytenr;

		चयन (pass) अणु
		हाल 0:
			next_bytenr = btrfs_super_root(selected_super);
			अगर (state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_ROOT_CHUNK_LOG_TREE_LOCATION)
				pr_info("root@%llu\n", next_bytenr);
			अवरोध;
		हाल 1:
			next_bytenr = btrfs_super_chunk_root(selected_super);
			अगर (state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_ROOT_CHUNK_LOG_TREE_LOCATION)
				pr_info("chunk@%llu\n", next_bytenr);
			अवरोध;
		हाल 2:
			next_bytenr = btrfs_super_log_root(selected_super);
			अगर (0 == next_bytenr)
				जारी;
			अगर (state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_ROOT_CHUNK_LOG_TREE_LOCATION)
				pr_info("log@%llu\n", next_bytenr);
			अवरोध;
		पूर्ण

		num_copies = btrfs_num_copies(state->fs_info, next_bytenr,
					      state->metablock_size);
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_NUM_COPIES)
			pr_info("num_copies(log_bytenr=%llu) = %d\n",
			       next_bytenr, num_copies);

		क्रम (mirror_num = 1; mirror_num <= num_copies; mirror_num++) अणु
			काष्ठा btrfsic_block *next_block;
			काष्ठा btrfsic_block_data_ctx पंचांगp_next_block_ctx;
			काष्ठा btrfsic_block_link *l;

			ret = btrfsic_map_block(state, next_bytenr,
						state->metablock_size,
						&पंचांगp_next_block_ctx,
						mirror_num);
			अगर (ret) अणु
				pr_info("btrfsic: btrfsic_map_block(root @%llu, mirror %d) failed!\n",
				       next_bytenr, mirror_num);
				kमुक्त(selected_super);
				वापस -1;
			पूर्ण

			next_block = btrfsic_block_hashtable_lookup(
					पंचांगp_next_block_ctx.dev->bdev,
					पंचांगp_next_block_ctx.dev_bytenr,
					&state->block_hashtable);
			BUG_ON(शून्य == next_block);

			l = btrfsic_block_link_hashtable_lookup(
					पंचांगp_next_block_ctx.dev->bdev,
					पंचांगp_next_block_ctx.dev_bytenr,
					state->latest_superblock->dev_state->
					bdev,
					state->latest_superblock->dev_bytenr,
					&state->block_link_hashtable);
			BUG_ON(शून्य == l);

			ret = btrfsic_पढ़ो_block(state, &पंचांगp_next_block_ctx);
			अगर (ret < (पूर्णांक)PAGE_SIZE) अणु
				pr_info("btrfsic: read @logical %llu failed!\n",
				       पंचांगp_next_block_ctx.start);
				btrfsic_release_block_ctx(&पंचांगp_next_block_ctx);
				kमुक्त(selected_super);
				वापस -1;
			पूर्ण

			ret = btrfsic_process_metablock(state,
							next_block,
							&पंचांगp_next_block_ctx,
							BTRFS_MAX_LEVEL + 3, 1);
			btrfsic_release_block_ctx(&पंचांगp_next_block_ctx);
		पूर्ण
	पूर्ण

	kमुक्त(selected_super);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfsic_process_superblock_dev_mirror(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_dev_state *dev_state,
		काष्ठा btrfs_device *device,
		पूर्णांक superblock_mirror_num,
		काष्ठा btrfsic_dev_state **selected_dev_state,
		काष्ठा btrfs_super_block *selected_super)
अणु
	काष्ठा btrfs_fs_info *fs_info = state->fs_info;
	काष्ठा btrfs_super_block *super_पंचांगp;
	u64 dev_bytenr;
	काष्ठा btrfsic_block *superblock_पंचांगp;
	पूर्णांक pass;
	काष्ठा block_device *स्थिर superblock_bdev = device->bdev;
	काष्ठा page *page;
	काष्ठा address_space *mapping = superblock_bdev->bd_inode->i_mapping;
	पूर्णांक ret = 0;

	/* super block bytenr is always the unmapped device bytenr */
	dev_bytenr = btrfs_sb_offset(superblock_mirror_num);
	अगर (dev_bytenr + BTRFS_SUPER_INFO_SIZE > device->commit_total_bytes)
		वापस -1;

	page = पढ़ो_cache_page_gfp(mapping, dev_bytenr >> PAGE_SHIFT, GFP_NOFS);
	अगर (IS_ERR(page))
		वापस -1;

	super_पंचांगp = page_address(page);

	अगर (btrfs_super_bytenr(super_पंचांगp) != dev_bytenr ||
	    btrfs_super_magic(super_पंचांगp) != BTRFS_MAGIC ||
	    स_भेद(device->uuid, super_पंचांगp->dev_item.uuid, BTRFS_UUID_SIZE) ||
	    btrfs_super_nodesize(super_पंचांगp) != state->metablock_size ||
	    btrfs_super_sectorsize(super_पंचांगp) != state->datablock_size) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	superblock_पंचांगp =
	    btrfsic_block_hashtable_lookup(superblock_bdev,
					   dev_bytenr,
					   &state->block_hashtable);
	अगर (शून्य == superblock_पंचांगp) अणु
		superblock_पंचांगp = btrfsic_block_alloc();
		अगर (शून्य == superblock_पंचांगp) अणु
			ret = -1;
			जाओ out;
		पूर्ण
		/* क्रम superblock, only the dev_bytenr makes sense */
		superblock_पंचांगp->dev_bytenr = dev_bytenr;
		superblock_पंचांगp->dev_state = dev_state;
		superblock_पंचांगp->logical_bytenr = dev_bytenr;
		superblock_पंचांगp->generation = btrfs_super_generation(super_पंचांगp);
		superblock_पंचांगp->is_metadata = 1;
		superblock_पंचांगp->is_superblock = 1;
		superblock_पंचांगp->is_ioकरोne = 1;
		superblock_पंचांगp->never_written = 0;
		superblock_पंचांगp->mirror_num = 1 + superblock_mirror_num;
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_SUPERBLOCK_WRITE)
			btrfs_info_in_rcu(fs_info,
				"new initial S-block (bdev %p, %s) @%llu (%s/%llu/%d)",
				     superblock_bdev,
				     rcu_str_deref(device->name), dev_bytenr,
				     dev_state->name, dev_bytenr,
				     superblock_mirror_num);
		list_add(&superblock_पंचांगp->all_blocks_node,
			 &state->all_blocks_list);
		btrfsic_block_hashtable_add(superblock_पंचांगp,
					    &state->block_hashtable);
	पूर्ण

	/* select the one with the highest generation field */
	अगर (btrfs_super_generation(super_पंचांगp) >
	    state->max_superblock_generation ||
	    0 == state->max_superblock_generation) अणु
		स_नकल(selected_super, super_पंचांगp, माप(*selected_super));
		*selected_dev_state = dev_state;
		state->max_superblock_generation =
		    btrfs_super_generation(super_पंचांगp);
		state->latest_superblock = superblock_पंचांगp;
	पूर्ण

	क्रम (pass = 0; pass < 3; pass++) अणु
		u64 next_bytenr;
		पूर्णांक num_copies;
		पूर्णांक mirror_num;
		स्थिर अक्षर *additional_string = शून्य;
		काष्ठा btrfs_disk_key पंचांगp_disk_key;

		पंचांगp_disk_key.type = BTRFS_ROOT_ITEM_KEY;
		पंचांगp_disk_key.offset = 0;
		चयन (pass) अणु
		हाल 0:
			btrfs_set_disk_key_objectid(&पंचांगp_disk_key,
						    BTRFS_ROOT_TREE_OBJECTID);
			additional_string = "initial root ";
			next_bytenr = btrfs_super_root(super_पंचांगp);
			अवरोध;
		हाल 1:
			btrfs_set_disk_key_objectid(&पंचांगp_disk_key,
						    BTRFS_CHUNK_TREE_OBJECTID);
			additional_string = "initial chunk ";
			next_bytenr = btrfs_super_chunk_root(super_पंचांगp);
			अवरोध;
		हाल 2:
			btrfs_set_disk_key_objectid(&पंचांगp_disk_key,
						    BTRFS_TREE_LOG_OBJECTID);
			additional_string = "initial log ";
			next_bytenr = btrfs_super_log_root(super_पंचांगp);
			अगर (0 == next_bytenr)
				जारी;
			अवरोध;
		पूर्ण

		num_copies = btrfs_num_copies(fs_info, next_bytenr,
					      state->metablock_size);
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_NUM_COPIES)
			pr_info("num_copies(log_bytenr=%llu) = %d\n",
			       next_bytenr, num_copies);
		क्रम (mirror_num = 1; mirror_num <= num_copies; mirror_num++) अणु
			काष्ठा btrfsic_block *next_block;
			काष्ठा btrfsic_block_data_ctx पंचांगp_next_block_ctx;
			काष्ठा btrfsic_block_link *l;

			अगर (btrfsic_map_block(state, next_bytenr,
					      state->metablock_size,
					      &पंचांगp_next_block_ctx,
					      mirror_num)) अणु
				pr_info("btrfsic: btrfsic_map_block(bytenr @%llu, mirror %d) failed!\n",
				       next_bytenr, mirror_num);
				ret = -1;
				जाओ out;
			पूर्ण

			next_block = btrfsic_block_lookup_or_add(
					state, &पंचांगp_next_block_ctx,
					additional_string, 1, 1, 0,
					mirror_num, शून्य);
			अगर (शून्य == next_block) अणु
				btrfsic_release_block_ctx(&पंचांगp_next_block_ctx);
				ret = -1;
				जाओ out;
			पूर्ण

			next_block->disk_key = पंचांगp_disk_key;
			next_block->generation = BTRFSIC_GENERATION_UNKNOWN;
			l = btrfsic_block_link_lookup_or_add(
					state, &पंचांगp_next_block_ctx,
					next_block, superblock_पंचांगp,
					BTRFSIC_GENERATION_UNKNOWN);
			btrfsic_release_block_ctx(&पंचांगp_next_block_ctx);
			अगर (शून्य == l) अणु
				ret = -1;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_INITIAL_ALL_TREES)
		btrfsic_dump_tree_sub(state, superblock_पंचांगp, 0);

out:
	put_page(page);
	वापस ret;
पूर्ण

अटल काष्ठा btrfsic_stack_frame *btrfsic_stack_frame_alloc(व्योम)
अणु
	काष्ठा btrfsic_stack_frame *sf;

	sf = kzalloc(माप(*sf), GFP_NOFS);
	अगर (sf)
		sf->magic = BTRFSIC_BLOCK_STACK_FRAME_MAGIC_NUMBER;
	वापस sf;
पूर्ण

अटल व्योम btrfsic_stack_frame_मुक्त(काष्ठा btrfsic_stack_frame *sf)
अणु
	BUG_ON(!(शून्य == sf ||
		 BTRFSIC_BLOCK_STACK_FRAME_MAGIC_NUMBER == sf->magic));
	kमुक्त(sf);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक btrfsic_process_metablock(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block *स्थिर first_block,
		काष्ठा btrfsic_block_data_ctx *स्थिर first_block_ctx,
		पूर्णांक first_limit_nesting, पूर्णांक क्रमce_ioकरोne_flag)
अणु
	काष्ठा btrfsic_stack_frame initial_stack_frame = अणु 0 पूर्ण;
	काष्ठा btrfsic_stack_frame *sf;
	काष्ठा btrfsic_stack_frame *next_stack;
	काष्ठा btrfs_header *स्थिर first_hdr =
		(काष्ठा btrfs_header *)first_block_ctx->datav[0];

	BUG_ON(!first_hdr);
	sf = &initial_stack_frame;
	sf->error = 0;
	sf->i = -1;
	sf->limit_nesting = first_limit_nesting;
	sf->block = first_block;
	sf->block_ctx = first_block_ctx;
	sf->next_block = शून्य;
	sf->hdr = first_hdr;
	sf->prev = शून्य;

जारी_with_new_stack_frame:
	sf->block->generation = btrfs_stack_header_generation(sf->hdr);
	अगर (0 == sf->hdr->level) अणु
		काष्ठा btrfs_leaf *स्थिर leafhdr =
		    (काष्ठा btrfs_leaf *)sf->hdr;

		अगर (-1 == sf->i) अणु
			sf->nr = btrfs_stack_header_nritems(&leafhdr->header);

			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				pr_info("leaf %llu items %d generation %llu owner %llu\n",
				       sf->block_ctx->start, sf->nr,
				       btrfs_stack_header_generation(
					       &leafhdr->header),
				       btrfs_stack_header_owner(
					       &leafhdr->header));
		पूर्ण

जारी_with_current_leaf_stack_frame:
		अगर (0 == sf->num_copies || sf->mirror_num > sf->num_copies) अणु
			sf->i++;
			sf->num_copies = 0;
		पूर्ण

		अगर (sf->i < sf->nr) अणु
			काष्ठा btrfs_item disk_item;
			u32 disk_item_offset =
				(uपूर्णांकptr_t)(leafhdr->items + sf->i) -
				(uपूर्णांकptr_t)leafhdr;
			काष्ठा btrfs_disk_key *disk_key;
			u8 type;
			u32 item_offset;
			u32 item_size;

			अगर (disk_item_offset + माप(काष्ठा btrfs_item) >
			    sf->block_ctx->len) अणु
leaf_item_out_of_bounce_error:
				pr_info("btrfsic: leaf item out of bounce at logical %llu, dev %s\n",
				       sf->block_ctx->start,
				       sf->block_ctx->dev->name);
				जाओ one_stack_frame_backwards;
			पूर्ण
			btrfsic_पढ़ो_from_block_data(sf->block_ctx,
						     &disk_item,
						     disk_item_offset,
						     माप(काष्ठा btrfs_item));
			item_offset = btrfs_stack_item_offset(&disk_item);
			item_size = btrfs_stack_item_size(&disk_item);
			disk_key = &disk_item.key;
			type = btrfs_disk_key_type(disk_key);

			अगर (BTRFS_ROOT_ITEM_KEY == type) अणु
				काष्ठा btrfs_root_item root_item;
				u32 root_item_offset;
				u64 next_bytenr;

				root_item_offset = item_offset +
					दुरत्व(काष्ठा btrfs_leaf, items);
				अगर (root_item_offset + item_size >
				    sf->block_ctx->len)
					जाओ leaf_item_out_of_bounce_error;
				btrfsic_पढ़ो_from_block_data(
					sf->block_ctx, &root_item,
					root_item_offset,
					item_size);
				next_bytenr = btrfs_root_bytenr(&root_item);

				sf->error =
				    btrfsic_create_link_to_next_block(
						state,
						sf->block,
						sf->block_ctx,
						next_bytenr,
						sf->limit_nesting,
						&sf->next_block_ctx,
						&sf->next_block,
						क्रमce_ioकरोne_flag,
						&sf->num_copies,
						&sf->mirror_num,
						disk_key,
						btrfs_root_generation(
						&root_item));
				अगर (sf->error)
					जाओ one_stack_frame_backwards;

				अगर (शून्य != sf->next_block) अणु
					काष्ठा btrfs_header *स्थिर next_hdr =
					    (काष्ठा btrfs_header *)
					    sf->next_block_ctx.datav[0];

					next_stack =
					    btrfsic_stack_frame_alloc();
					अगर (शून्य == next_stack) अणु
						sf->error = -1;
						btrfsic_release_block_ctx(
								&sf->
								next_block_ctx);
						जाओ one_stack_frame_backwards;
					पूर्ण

					next_stack->i = -1;
					next_stack->block = sf->next_block;
					next_stack->block_ctx =
					    &sf->next_block_ctx;
					next_stack->next_block = शून्य;
					next_stack->hdr = next_hdr;
					next_stack->limit_nesting =
					    sf->limit_nesting - 1;
					next_stack->prev = sf;
					sf = next_stack;
					जाओ जारी_with_new_stack_frame;
				पूर्ण
			पूर्ण अन्यथा अगर (BTRFS_EXTENT_DATA_KEY == type &&
				   state->include_extent_data) अणु
				sf->error = btrfsic_handle_extent_data(
						state,
						sf->block,
						sf->block_ctx,
						item_offset,
						क्रमce_ioकरोne_flag);
				अगर (sf->error)
					जाओ one_stack_frame_backwards;
			पूर्ण

			जाओ जारी_with_current_leaf_stack_frame;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_node *स्थिर nodehdr = (काष्ठा btrfs_node *)sf->hdr;

		अगर (-1 == sf->i) अणु
			sf->nr = btrfs_stack_header_nritems(&nodehdr->header);

			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				pr_info("node %llu level %d items %d generation %llu owner %llu\n",
				       sf->block_ctx->start,
				       nodehdr->header.level, sf->nr,
				       btrfs_stack_header_generation(
				       &nodehdr->header),
				       btrfs_stack_header_owner(
				       &nodehdr->header));
		पूर्ण

जारी_with_current_node_stack_frame:
		अगर (0 == sf->num_copies || sf->mirror_num > sf->num_copies) अणु
			sf->i++;
			sf->num_copies = 0;
		पूर्ण

		अगर (sf->i < sf->nr) अणु
			काष्ठा btrfs_key_ptr key_ptr;
			u32 key_ptr_offset;
			u64 next_bytenr;

			key_ptr_offset = (uपूर्णांकptr_t)(nodehdr->ptrs + sf->i) -
					  (uपूर्णांकptr_t)nodehdr;
			अगर (key_ptr_offset + माप(काष्ठा btrfs_key_ptr) >
			    sf->block_ctx->len) अणु
				pr_info("btrfsic: node item out of bounce at logical %llu, dev %s\n",
				       sf->block_ctx->start,
				       sf->block_ctx->dev->name);
				जाओ one_stack_frame_backwards;
			पूर्ण
			btrfsic_पढ़ो_from_block_data(
				sf->block_ctx, &key_ptr, key_ptr_offset,
				माप(काष्ठा btrfs_key_ptr));
			next_bytenr = btrfs_stack_key_blockptr(&key_ptr);

			sf->error = btrfsic_create_link_to_next_block(
					state,
					sf->block,
					sf->block_ctx,
					next_bytenr,
					sf->limit_nesting,
					&sf->next_block_ctx,
					&sf->next_block,
					क्रमce_ioकरोne_flag,
					&sf->num_copies,
					&sf->mirror_num,
					&key_ptr.key,
					btrfs_stack_key_generation(&key_ptr));
			अगर (sf->error)
				जाओ one_stack_frame_backwards;

			अगर (शून्य != sf->next_block) अणु
				काष्ठा btrfs_header *स्थिर next_hdr =
				    (काष्ठा btrfs_header *)
				    sf->next_block_ctx.datav[0];

				next_stack = btrfsic_stack_frame_alloc();
				अगर (शून्य == next_stack) अणु
					sf->error = -1;
					जाओ one_stack_frame_backwards;
				पूर्ण

				next_stack->i = -1;
				next_stack->block = sf->next_block;
				next_stack->block_ctx = &sf->next_block_ctx;
				next_stack->next_block = शून्य;
				next_stack->hdr = next_hdr;
				next_stack->limit_nesting =
				    sf->limit_nesting - 1;
				next_stack->prev = sf;
				sf = next_stack;
				जाओ जारी_with_new_stack_frame;
			पूर्ण

			जाओ जारी_with_current_node_stack_frame;
		पूर्ण
	पूर्ण

one_stack_frame_backwards:
	अगर (शून्य != sf->prev) अणु
		काष्ठा btrfsic_stack_frame *स्थिर prev = sf->prev;

		/* the one क्रम the initial block is मुक्तd in the caller */
		btrfsic_release_block_ctx(sf->block_ctx);

		अगर (sf->error) अणु
			prev->error = sf->error;
			btrfsic_stack_frame_मुक्त(sf);
			sf = prev;
			जाओ one_stack_frame_backwards;
		पूर्ण

		btrfsic_stack_frame_मुक्त(sf);
		sf = prev;
		जाओ जारी_with_new_stack_frame;
	पूर्ण अन्यथा अणु
		BUG_ON(&initial_stack_frame != sf);
	पूर्ण

	वापस sf->error;
पूर्ण

अटल व्योम btrfsic_पढ़ो_from_block_data(
	काष्ठा btrfsic_block_data_ctx *block_ctx,
	व्योम *dstv, u32 offset, माप_प्रकार len)
अणु
	माप_प्रकार cur;
	माप_प्रकार pgoff;
	अक्षर *kaddr;
	अक्षर *dst = (अक्षर *)dstv;
	माप_प्रकार start_offset = offset_in_page(block_ctx->start);
	अचिन्हित दीर्घ i = (start_offset + offset) >> PAGE_SHIFT;

	WARN_ON(offset + len > block_ctx->len);
	pgoff = offset_in_page(start_offset + offset);

	जबतक (len > 0) अणु
		cur = min(len, ((माप_प्रकार)PAGE_SIZE - pgoff));
		BUG_ON(i >= DIV_ROUND_UP(block_ctx->len, PAGE_SIZE));
		kaddr = block_ctx->datav[i];
		स_नकल(dst, kaddr + pgoff, cur);

		dst += cur;
		len -= cur;
		pgoff = 0;
		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक btrfsic_create_link_to_next_block(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block *block,
		काष्ठा btrfsic_block_data_ctx *block_ctx,
		u64 next_bytenr,
		पूर्णांक limit_nesting,
		काष्ठा btrfsic_block_data_ctx *next_block_ctx,
		काष्ठा btrfsic_block **next_blockp,
		पूर्णांक क्रमce_ioकरोne_flag,
		पूर्णांक *num_copiesp, पूर्णांक *mirror_nump,
		काष्ठा btrfs_disk_key *disk_key,
		u64 parent_generation)
अणु
	काष्ठा btrfs_fs_info *fs_info = state->fs_info;
	काष्ठा btrfsic_block *next_block = शून्य;
	पूर्णांक ret;
	काष्ठा btrfsic_block_link *l;
	पूर्णांक did_alloc_block_link;
	पूर्णांक block_was_created;

	*next_blockp = शून्य;
	अगर (0 == *num_copiesp) अणु
		*num_copiesp = btrfs_num_copies(fs_info, next_bytenr,
						state->metablock_size);
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_NUM_COPIES)
			pr_info("num_copies(log_bytenr=%llu) = %d\n",
			       next_bytenr, *num_copiesp);
		*mirror_nump = 1;
	पूर्ण

	अगर (*mirror_nump > *num_copiesp)
		वापस 0;

	अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
		pr_info("btrfsic_create_link_to_next_block(mirror_num=%d)\n",
		       *mirror_nump);
	ret = btrfsic_map_block(state, next_bytenr,
				state->metablock_size,
				next_block_ctx, *mirror_nump);
	अगर (ret) अणु
		pr_info("btrfsic: btrfsic_map_block(@%llu, mirror=%d) failed!\n",
		       next_bytenr, *mirror_nump);
		btrfsic_release_block_ctx(next_block_ctx);
		*next_blockp = शून्य;
		वापस -1;
	पूर्ण

	next_block = btrfsic_block_lookup_or_add(state,
						 next_block_ctx, "referenced ",
						 1, क्रमce_ioकरोne_flag,
						 !क्रमce_ioकरोne_flag,
						 *mirror_nump,
						 &block_was_created);
	अगर (शून्य == next_block) अणु
		btrfsic_release_block_ctx(next_block_ctx);
		*next_blockp = शून्य;
		वापस -1;
	पूर्ण
	अगर (block_was_created) अणु
		l = शून्य;
		next_block->generation = BTRFSIC_GENERATION_UNKNOWN;
	पूर्ण अन्यथा अणु
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE) अणु
			अगर (next_block->logical_bytenr != next_bytenr &&
			    !(!next_block->is_metadata &&
			      0 == next_block->logical_bytenr))
				pr_info("Referenced block @%llu (%s/%llu/%d) found in hash table, %c, bytenr mismatch (!= stored %llu).\n",
				       next_bytenr, next_block_ctx->dev->name,
				       next_block_ctx->dev_bytenr, *mirror_nump,
				       btrfsic_get_block_type(state,
							      next_block),
				       next_block->logical_bytenr);
			अन्यथा
				pr_info("Referenced block @%llu (%s/%llu/%d) found in hash table, %c.\n",
				       next_bytenr, next_block_ctx->dev->name,
				       next_block_ctx->dev_bytenr, *mirror_nump,
				       btrfsic_get_block_type(state,
							      next_block));
		पूर्ण
		next_block->logical_bytenr = next_bytenr;

		next_block->mirror_num = *mirror_nump;
		l = btrfsic_block_link_hashtable_lookup(
				next_block_ctx->dev->bdev,
				next_block_ctx->dev_bytenr,
				block_ctx->dev->bdev,
				block_ctx->dev_bytenr,
				&state->block_link_hashtable);
	पूर्ण

	next_block->disk_key = *disk_key;
	अगर (शून्य == l) अणु
		l = btrfsic_block_link_alloc();
		अगर (शून्य == l) अणु
			btrfsic_release_block_ctx(next_block_ctx);
			*next_blockp = शून्य;
			वापस -1;
		पूर्ण

		did_alloc_block_link = 1;
		l->block_ref_to = next_block;
		l->block_ref_from = block;
		l->ref_cnt = 1;
		l->parent_generation = parent_generation;

		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			btrfsic_prपूर्णांक_add_link(state, l);

		list_add(&l->node_ref_to, &block->ref_to_list);
		list_add(&l->node_ref_from, &next_block->ref_from_list);

		btrfsic_block_link_hashtable_add(l,
						 &state->block_link_hashtable);
	पूर्ण अन्यथा अणु
		did_alloc_block_link = 0;
		अगर (0 == limit_nesting) अणु
			l->ref_cnt++;
			l->parent_generation = parent_generation;
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				btrfsic_prपूर्णांक_add_link(state, l);
		पूर्ण
	पूर्ण

	अगर (limit_nesting > 0 && did_alloc_block_link) अणु
		ret = btrfsic_पढ़ो_block(state, next_block_ctx);
		अगर (ret < (पूर्णांक)next_block_ctx->len) अणु
			pr_info("btrfsic: read block @logical %llu failed!\n",
			       next_bytenr);
			btrfsic_release_block_ctx(next_block_ctx);
			*next_blockp = शून्य;
			वापस -1;
		पूर्ण

		*next_blockp = next_block;
	पूर्ण अन्यथा अणु
		*next_blockp = शून्य;
	पूर्ण
	(*mirror_nump)++;

	वापस 0;
पूर्ण

अटल पूर्णांक btrfsic_handle_extent_data(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block *block,
		काष्ठा btrfsic_block_data_ctx *block_ctx,
		u32 item_offset, पूर्णांक क्रमce_ioकरोne_flag)
अणु
	काष्ठा btrfs_fs_info *fs_info = state->fs_info;
	काष्ठा btrfs_file_extent_item file_extent_item;
	u64 file_extent_item_offset;
	u64 next_bytenr;
	u64 num_bytes;
	u64 generation;
	काष्ठा btrfsic_block_link *l;
	पूर्णांक ret;

	file_extent_item_offset = दुरत्व(काष्ठा btrfs_leaf, items) +
				  item_offset;
	अगर (file_extent_item_offset +
	    दुरत्व(काष्ठा btrfs_file_extent_item, disk_num_bytes) >
	    block_ctx->len) अणु
		pr_info("btrfsic: file item out of bounce at logical %llu, dev %s\n",
		       block_ctx->start, block_ctx->dev->name);
		वापस -1;
	पूर्ण

	btrfsic_पढ़ो_from_block_data(block_ctx, &file_extent_item,
		file_extent_item_offset,
		दुरत्व(काष्ठा btrfs_file_extent_item, disk_num_bytes));
	अगर (BTRFS_खाता_EXTENT_REG != file_extent_item.type ||
	    btrfs_stack_file_extent_disk_bytenr(&file_extent_item) == 0) अणु
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERY_VERBOSE)
			pr_info("extent_data: type %u, disk_bytenr = %llu\n",
			       file_extent_item.type,
			       btrfs_stack_file_extent_disk_bytenr(
			       &file_extent_item));
		वापस 0;
	पूर्ण

	अगर (file_extent_item_offset + माप(काष्ठा btrfs_file_extent_item) >
	    block_ctx->len) अणु
		pr_info("btrfsic: file item out of bounce at logical %llu, dev %s\n",
		       block_ctx->start, block_ctx->dev->name);
		वापस -1;
	पूर्ण
	btrfsic_पढ़ो_from_block_data(block_ctx, &file_extent_item,
				     file_extent_item_offset,
				     माप(काष्ठा btrfs_file_extent_item));
	next_bytenr = btrfs_stack_file_extent_disk_bytenr(&file_extent_item);
	अगर (btrfs_stack_file_extent_compression(&file_extent_item) ==
	    BTRFS_COMPRESS_NONE) अणु
		next_bytenr += btrfs_stack_file_extent_offset(&file_extent_item);
		num_bytes = btrfs_stack_file_extent_num_bytes(&file_extent_item);
	पूर्ण अन्यथा अणु
		num_bytes = btrfs_stack_file_extent_disk_num_bytes(&file_extent_item);
	पूर्ण
	generation = btrfs_stack_file_extent_generation(&file_extent_item);

	अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERY_VERBOSE)
		pr_info("extent_data: type %u, disk_bytenr = %llu, offset = %llu, num_bytes = %llu\n",
		       file_extent_item.type,
		       btrfs_stack_file_extent_disk_bytenr(&file_extent_item),
		       btrfs_stack_file_extent_offset(&file_extent_item),
		       num_bytes);
	जबतक (num_bytes > 0) अणु
		u32 chunk_len;
		पूर्णांक num_copies;
		पूर्णांक mirror_num;

		अगर (num_bytes > state->datablock_size)
			chunk_len = state->datablock_size;
		अन्यथा
			chunk_len = num_bytes;

		num_copies = btrfs_num_copies(fs_info, next_bytenr,
					      state->datablock_size);
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_NUM_COPIES)
			pr_info("num_copies(log_bytenr=%llu) = %d\n",
			       next_bytenr, num_copies);
		क्रम (mirror_num = 1; mirror_num <= num_copies; mirror_num++) अणु
			काष्ठा btrfsic_block_data_ctx next_block_ctx;
			काष्ठा btrfsic_block *next_block;
			पूर्णांक block_was_created;

			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				pr_info("btrfsic_handle_extent_data(mirror_num=%d)\n",
					mirror_num);
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERY_VERBOSE)
				pr_info("\tdisk_bytenr = %llu, num_bytes %u\n",
				       next_bytenr, chunk_len);
			ret = btrfsic_map_block(state, next_bytenr,
						chunk_len, &next_block_ctx,
						mirror_num);
			अगर (ret) अणु
				pr_info("btrfsic: btrfsic_map_block(@%llu, mirror=%d) failed!\n",
				       next_bytenr, mirror_num);
				वापस -1;
			पूर्ण

			next_block = btrfsic_block_lookup_or_add(
					state,
					&next_block_ctx,
					"referenced ",
					0,
					क्रमce_ioकरोne_flag,
					!क्रमce_ioकरोne_flag,
					mirror_num,
					&block_was_created);
			अगर (शून्य == next_block) अणु
				btrfsic_release_block_ctx(&next_block_ctx);
				वापस -1;
			पूर्ण
			अगर (!block_was_created) अणु
				अगर ((state->prपूर्णांक_mask &
				     BTRFSIC_PRINT_MASK_VERBOSE) &&
				    next_block->logical_bytenr != next_bytenr &&
				    !(!next_block->is_metadata &&
				      0 == next_block->logical_bytenr)) अणु
					pr_info("Referenced block @%llu (%s/%llu/%d) found in hash table, D, bytenr mismatch (!= stored %llu).\n",
					       next_bytenr,
					       next_block_ctx.dev->name,
					       next_block_ctx.dev_bytenr,
					       mirror_num,
					       next_block->logical_bytenr);
				पूर्ण
				next_block->logical_bytenr = next_bytenr;
				next_block->mirror_num = mirror_num;
			पूर्ण

			l = btrfsic_block_link_lookup_or_add(state,
							     &next_block_ctx,
							     next_block, block,
							     generation);
			btrfsic_release_block_ctx(&next_block_ctx);
			अगर (शून्य == l)
				वापस -1;
		पूर्ण

		next_bytenr += chunk_len;
		num_bytes -= chunk_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btrfsic_map_block(काष्ठा btrfsic_state *state, u64 bytenr, u32 len,
			     काष्ठा btrfsic_block_data_ctx *block_ctx_out,
			     पूर्णांक mirror_num)
अणु
	काष्ठा btrfs_fs_info *fs_info = state->fs_info;
	पूर्णांक ret;
	u64 length;
	काष्ठा btrfs_bio *multi = शून्य;
	काष्ठा btrfs_device *device;

	length = len;
	ret = btrfs_map_block(fs_info, BTRFS_MAP_READ,
			      bytenr, &length, &multi, mirror_num);

	अगर (ret) अणु
		block_ctx_out->start = 0;
		block_ctx_out->dev_bytenr = 0;
		block_ctx_out->len = 0;
		block_ctx_out->dev = शून्य;
		block_ctx_out->datav = शून्य;
		block_ctx_out->pagev = शून्य;
		block_ctx_out->mem_to_मुक्त = शून्य;

		वापस ret;
	पूर्ण

	device = multi->stripes[0].dev;
	अगर (test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state) ||
	    !device->bdev || !device->name)
		block_ctx_out->dev = शून्य;
	अन्यथा
		block_ctx_out->dev = btrfsic_dev_state_lookup(
							device->bdev->bd_dev);
	block_ctx_out->dev_bytenr = multi->stripes[0].physical;
	block_ctx_out->start = bytenr;
	block_ctx_out->len = len;
	block_ctx_out->datav = शून्य;
	block_ctx_out->pagev = शून्य;
	block_ctx_out->mem_to_मुक्त = शून्य;

	kमुक्त(multi);
	अगर (शून्य == block_ctx_out->dev) अणु
		ret = -ENXIO;
		pr_info("btrfsic: error, cannot lookup dev (#1)!\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम btrfsic_release_block_ctx(काष्ठा btrfsic_block_data_ctx *block_ctx)
अणु
	अगर (block_ctx->mem_to_मुक्त) अणु
		अचिन्हित पूर्णांक num_pages;

		BUG_ON(!block_ctx->datav);
		BUG_ON(!block_ctx->pagev);
		num_pages = (block_ctx->len + (u64)PAGE_SIZE - 1) >>
			    PAGE_SHIFT;
		/* Pages must be unmapped in reverse order */
		जबतक (num_pages > 0) अणु
			num_pages--;
			अगर (block_ctx->datav[num_pages]) अणु
				kunmap_local(block_ctx->datav[num_pages]);
				block_ctx->datav[num_pages] = शून्य;
			पूर्ण
			अगर (block_ctx->pagev[num_pages]) अणु
				__मुक्त_page(block_ctx->pagev[num_pages]);
				block_ctx->pagev[num_pages] = शून्य;
			पूर्ण
		पूर्ण

		kमुक्त(block_ctx->mem_to_मुक्त);
		block_ctx->mem_to_मुक्त = शून्य;
		block_ctx->pagev = शून्य;
		block_ctx->datav = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक btrfsic_पढ़ो_block(काष्ठा btrfsic_state *state,
			      काष्ठा btrfsic_block_data_ctx *block_ctx)
अणु
	अचिन्हित पूर्णांक num_pages;
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;
	u64 dev_bytenr;
	पूर्णांक ret;

	BUG_ON(block_ctx->datav);
	BUG_ON(block_ctx->pagev);
	BUG_ON(block_ctx->mem_to_मुक्त);
	अगर (!PAGE_ALIGNED(block_ctx->dev_bytenr)) अणु
		pr_info("btrfsic: read_block() with unaligned bytenr %llu\n",
		       block_ctx->dev_bytenr);
		वापस -1;
	पूर्ण

	num_pages = (block_ctx->len + (u64)PAGE_SIZE - 1) >>
		    PAGE_SHIFT;
	size = माप(*block_ctx->datav) + माप(*block_ctx->pagev);
	block_ctx->mem_to_मुक्त = kसुस्मृति(num_pages, size, GFP_NOFS);
	अगर (!block_ctx->mem_to_मुक्त)
		वापस -ENOMEM;
	block_ctx->datav = block_ctx->mem_to_मुक्त;
	block_ctx->pagev = (काष्ठा page **)(block_ctx->datav + num_pages);
	क्रम (i = 0; i < num_pages; i++) अणु
		block_ctx->pagev[i] = alloc_page(GFP_NOFS);
		अगर (!block_ctx->pagev[i])
			वापस -1;
	पूर्ण

	dev_bytenr = block_ctx->dev_bytenr;
	क्रम (i = 0; i < num_pages;) अणु
		काष्ठा bio *bio;
		अचिन्हित पूर्णांक j;

		bio = btrfs_io_bio_alloc(num_pages - i);
		bio_set_dev(bio, block_ctx->dev->bdev);
		bio->bi_iter.bi_sector = dev_bytenr >> 9;
		bio->bi_opf = REQ_OP_READ;

		क्रम (j = i; j < num_pages; j++) अणु
			ret = bio_add_page(bio, block_ctx->pagev[j],
					   PAGE_SIZE, 0);
			अगर (PAGE_SIZE != ret)
				अवरोध;
		पूर्ण
		अगर (j == i) अणु
			pr_info("btrfsic: error, failed to add a single page!\n");
			वापस -1;
		पूर्ण
		अगर (submit_bio_रुको(bio)) अणु
			pr_info("btrfsic: read error at logical %llu dev %s!\n",
			       block_ctx->start, block_ctx->dev->name);
			bio_put(bio);
			वापस -1;
		पूर्ण
		bio_put(bio);
		dev_bytenr += (j - i) * PAGE_SIZE;
		i = j;
	पूर्ण
	क्रम (i = 0; i < num_pages; i++)
		block_ctx->datav[i] = kmap_local_page(block_ctx->pagev[i]);

	वापस block_ctx->len;
पूर्ण

अटल व्योम btrfsic_dump_database(काष्ठा btrfsic_state *state)
अणु
	स्थिर काष्ठा btrfsic_block *b_all;

	BUG_ON(शून्य == state);

	pr_info("all_blocks_list:\n");
	list_क्रम_each_entry(b_all, &state->all_blocks_list, all_blocks_node) अणु
		स्थिर काष्ठा btrfsic_block_link *l;

		pr_info("%c-block @%llu (%s/%llu/%d)\n",
		       btrfsic_get_block_type(state, b_all),
		       b_all->logical_bytenr, b_all->dev_state->name,
		       b_all->dev_bytenr, b_all->mirror_num);

		list_क्रम_each_entry(l, &b_all->ref_to_list, node_ref_to) अणु
			pr_info(" %c @%llu (%s/%llu/%d) refers %u* to %c @%llu (%s/%llu/%d)\n",
			       btrfsic_get_block_type(state, b_all),
			       b_all->logical_bytenr, b_all->dev_state->name,
			       b_all->dev_bytenr, b_all->mirror_num,
			       l->ref_cnt,
			       btrfsic_get_block_type(state, l->block_ref_to),
			       l->block_ref_to->logical_bytenr,
			       l->block_ref_to->dev_state->name,
			       l->block_ref_to->dev_bytenr,
			       l->block_ref_to->mirror_num);
		पूर्ण

		list_क्रम_each_entry(l, &b_all->ref_from_list, node_ref_from) अणु
			pr_info(" %c @%llu (%s/%llu/%d) is ref %u* from %c @%llu (%s/%llu/%d)\n",
			       btrfsic_get_block_type(state, b_all),
			       b_all->logical_bytenr, b_all->dev_state->name,
			       b_all->dev_bytenr, b_all->mirror_num,
			       l->ref_cnt,
			       btrfsic_get_block_type(state, l->block_ref_from),
			       l->block_ref_from->logical_bytenr,
			       l->block_ref_from->dev_state->name,
			       l->block_ref_from->dev_bytenr,
			       l->block_ref_from->mirror_num);
		पूर्ण

		pr_info("\n");
	पूर्ण
पूर्ण

/*
 * Test whether the disk block contains a tree block (leaf or node)
 * (note that this test fails क्रम the super block)
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक btrfsic_test_क्रम_metadata(
		काष्ठा btrfsic_state *state,
		अक्षर **datav, अचिन्हित पूर्णांक num_pages)
अणु
	काष्ठा btrfs_fs_info *fs_info = state->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	काष्ठा btrfs_header *h;
	u8 csum[BTRFS_CSUM_SIZE];
	अचिन्हित पूर्णांक i;

	अगर (num_pages * PAGE_SIZE < state->metablock_size)
		वापस 1; /* not metadata */
	num_pages = state->metablock_size >> PAGE_SHIFT;
	h = (काष्ठा btrfs_header *)datav[0];

	अगर (स_भेद(h->fsid, fs_info->fs_devices->fsid, BTRFS_FSID_SIZE))
		वापस 1;

	shash->tfm = fs_info->csum_shash;
	crypto_shash_init(shash);

	क्रम (i = 0; i < num_pages; i++) अणु
		u8 *data = i ? datav[i] : (datav[i] + BTRFS_CSUM_SIZE);
		माप_प्रकार sublen = i ? PAGE_SIZE :
				    (PAGE_SIZE - BTRFS_CSUM_SIZE);

		crypto_shash_update(shash, data, sublen);
	पूर्ण
	crypto_shash_final(shash, csum);
	अगर (स_भेद(csum, h->csum, fs_info->csum_size))
		वापस 1;

	वापस 0; /* is metadata */
पूर्ण

अटल व्योम btrfsic_process_written_block(काष्ठा btrfsic_dev_state *dev_state,
					  u64 dev_bytenr, अक्षर **mapped_datav,
					  अचिन्हित पूर्णांक num_pages,
					  काष्ठा bio *bio, पूर्णांक *bio_is_patched,
					  पूर्णांक submit_bio_bh_rw)
अणु
	पूर्णांक is_metadata;
	काष्ठा btrfsic_block *block;
	काष्ठा btrfsic_block_data_ctx block_ctx;
	पूर्णांक ret;
	काष्ठा btrfsic_state *state = dev_state->state;
	काष्ठा block_device *bdev = dev_state->bdev;
	अचिन्हित पूर्णांक processed_len;

	अगर (शून्य != bio_is_patched)
		*bio_is_patched = 0;

again:
	अगर (num_pages == 0)
		वापस;

	processed_len = 0;
	is_metadata = (0 == btrfsic_test_क्रम_metadata(state, mapped_datav,
						      num_pages));

	block = btrfsic_block_hashtable_lookup(bdev, dev_bytenr,
					       &state->block_hashtable);
	अगर (शून्य != block) अणु
		u64 bytenr = 0;
		काष्ठा btrfsic_block_link *l, *पंचांगp;

		अगर (block->is_superblock) अणु
			bytenr = btrfs_super_bytenr((काष्ठा btrfs_super_block *)
						    mapped_datav[0]);
			अगर (num_pages * PAGE_SIZE <
			    BTRFS_SUPER_INFO_SIZE) अणु
				pr_info("btrfsic: cannot work with too short bios!\n");
				वापस;
			पूर्ण
			is_metadata = 1;
			BUG_ON(!PAGE_ALIGNED(BTRFS_SUPER_INFO_SIZE));
			processed_len = BTRFS_SUPER_INFO_SIZE;
			अगर (state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_TREE_BEFORE_SB_WRITE) अणु
				pr_info("[before new superblock is written]:\n");
				btrfsic_dump_tree_sub(state, block, 0);
			पूर्ण
		पूर्ण
		अगर (is_metadata) अणु
			अगर (!block->is_superblock) अणु
				अगर (num_pages * PAGE_SIZE <
				    state->metablock_size) अणु
					pr_info("btrfsic: cannot work with too short bios!\n");
					वापस;
				पूर्ण
				processed_len = state->metablock_size;
				bytenr = btrfs_stack_header_bytenr(
						(काष्ठा btrfs_header *)
						mapped_datav[0]);
				btrfsic_cmp_log_and_dev_bytenr(state, bytenr,
							       dev_state,
							       dev_bytenr);
			पूर्ण
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE) अणु
				अगर (block->logical_bytenr != bytenr &&
				    !(!block->is_metadata &&
				      block->logical_bytenr == 0))
					pr_info("Written block @%llu (%s/%llu/%d) found in hash table, %c, bytenr mismatch (!= stored %llu).\n",
					       bytenr, dev_state->name,
					       dev_bytenr,
					       block->mirror_num,
					       btrfsic_get_block_type(state,
								      block),
					       block->logical_bytenr);
				अन्यथा
					pr_info("Written block @%llu (%s/%llu/%d) found in hash table, %c.\n",
					       bytenr, dev_state->name,
					       dev_bytenr, block->mirror_num,
					       btrfsic_get_block_type(state,
								      block));
			पूर्ण
			block->logical_bytenr = bytenr;
		पूर्ण अन्यथा अणु
			अगर (num_pages * PAGE_SIZE <
			    state->datablock_size) अणु
				pr_info("btrfsic: cannot work with too short bios!\n");
				वापस;
			पूर्ण
			processed_len = state->datablock_size;
			bytenr = block->logical_bytenr;
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				pr_info("Written block @%llu (%s/%llu/%d) found in hash table, %c.\n",
				       bytenr, dev_state->name, dev_bytenr,
				       block->mirror_num,
				       btrfsic_get_block_type(state, block));
		पूर्ण

		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("ref_to_list: %cE, ref_from_list: %cE\n",
			       list_empty(&block->ref_to_list) ? ' ' : '!',
			       list_empty(&block->ref_from_list) ? ' ' : '!');
		अगर (btrfsic_is_block_ref_by_superblock(state, block, 0)) अणु
			pr_info("btrfs: attempt to overwrite %c-block @%llu (%s/%llu/%d), old(gen=%llu, objectid=%llu, type=%d, offset=%llu), new(gen=%llu), which is referenced by most recent superblock (superblockgen=%llu)!\n",
			       btrfsic_get_block_type(state, block), bytenr,
			       dev_state->name, dev_bytenr, block->mirror_num,
			       block->generation,
			       btrfs_disk_key_objectid(&block->disk_key),
			       block->disk_key.type,
			       btrfs_disk_key_offset(&block->disk_key),
			       btrfs_stack_header_generation(
				       (काष्ठा btrfs_header *) mapped_datav[0]),
			       state->max_superblock_generation);
			btrfsic_dump_tree(state);
		पूर्ण

		अगर (!block->is_ioकरोne && !block->never_written) अणु
			pr_info("btrfs: attempt to overwrite %c-block @%llu (%s/%llu/%d), oldgen=%llu, newgen=%llu, which is not yet iodone!\n",
			       btrfsic_get_block_type(state, block), bytenr,
			       dev_state->name, dev_bytenr, block->mirror_num,
			       block->generation,
			       btrfs_stack_header_generation(
				       (काष्ठा btrfs_header *)
				       mapped_datav[0]));
			/* it would not be safe to go on */
			btrfsic_dump_tree(state);
			जाओ जारी_loop;
		पूर्ण

		/*
		 * Clear all references of this block. Do not मुक्त
		 * the block itself even अगर is not referenced anymore
		 * because it still carries valuable inक्रमmation
		 * like whether it was ever written and IO completed.
		 */
		list_क्रम_each_entry_safe(l, पंचांगp, &block->ref_to_list,
					 node_ref_to) अणु
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				btrfsic_prपूर्णांक_rem_link(state, l);
			l->ref_cnt--;
			अगर (0 == l->ref_cnt) अणु
				list_del(&l->node_ref_to);
				list_del(&l->node_ref_from);
				btrfsic_block_link_hashtable_हटाओ(l);
				btrfsic_block_link_मुक्त(l);
			पूर्ण
		पूर्ण

		block_ctx.dev = dev_state;
		block_ctx.dev_bytenr = dev_bytenr;
		block_ctx.start = bytenr;
		block_ctx.len = processed_len;
		block_ctx.pagev = शून्य;
		block_ctx.mem_to_मुक्त = शून्य;
		block_ctx.datav = mapped_datav;

		अगर (is_metadata || state->include_extent_data) अणु
			block->never_written = 0;
			block->ioकरोne_w_error = 0;
			अगर (शून्य != bio) अणु
				block->is_ioकरोne = 0;
				BUG_ON(शून्य == bio_is_patched);
				अगर (!*bio_is_patched) अणु
					block->orig_bio_निजी =
					    bio->bi_निजी;
					block->orig_bio_end_io =
					    bio->bi_end_io;
					block->next_in_same_bio = शून्य;
					bio->bi_निजी = block;
					bio->bi_end_io = btrfsic_bio_end_io;
					*bio_is_patched = 1;
				पूर्ण अन्यथा अणु
					काष्ठा btrfsic_block *chained_block =
					    (काष्ठा btrfsic_block *)
					    bio->bi_निजी;

					BUG_ON(शून्य == chained_block);
					block->orig_bio_निजी =
					    chained_block->orig_bio_निजी;
					block->orig_bio_end_io =
					    chained_block->orig_bio_end_io;
					block->next_in_same_bio = chained_block;
					bio->bi_निजी = block;
				पूर्ण
			पूर्ण अन्यथा अणु
				block->is_ioकरोne = 1;
				block->orig_bio_निजी = शून्य;
				block->orig_bio_end_io = शून्य;
				block->next_in_same_bio = शून्य;
			पूर्ण
		पूर्ण

		block->flush_gen = dev_state->last_flush_gen + 1;
		block->submit_bio_bh_rw = submit_bio_bh_rw;
		अगर (is_metadata) अणु
			block->logical_bytenr = bytenr;
			block->is_metadata = 1;
			अगर (block->is_superblock) अणु
				BUG_ON(PAGE_SIZE !=
				       BTRFS_SUPER_INFO_SIZE);
				ret = btrfsic_process_written_superblock(
						state,
						block,
						(काष्ठा btrfs_super_block *)
						mapped_datav[0]);
				अगर (state->prपूर्णांक_mask &
				    BTRFSIC_PRINT_MASK_TREE_AFTER_SB_WRITE) अणु
					pr_info("[after new superblock is written]:\n");
					btrfsic_dump_tree_sub(state, block, 0);
				पूर्ण
			पूर्ण अन्यथा अणु
				block->mirror_num = 0;	/* unknown */
				ret = btrfsic_process_metablock(
						state,
						block,
						&block_ctx,
						0, 0);
			पूर्ण
			अगर (ret)
				pr_info("btrfsic: btrfsic_process_metablock(root @%llu) failed!\n",
				       dev_bytenr);
		पूर्ण अन्यथा अणु
			block->is_metadata = 0;
			block->mirror_num = 0;	/* unknown */
			block->generation = BTRFSIC_GENERATION_UNKNOWN;
			अगर (!state->include_extent_data
			    && list_empty(&block->ref_from_list)) अणु
				/*
				 * disk block is overwritten with extent
				 * data (not meta data) and we are configured
				 * to not include extent data: take the
				 * chance and मुक्त the block's memory
				 */
				btrfsic_block_hashtable_हटाओ(block);
				list_del(&block->all_blocks_node);
				btrfsic_block_मुक्त(block);
			पूर्ण
		पूर्ण
		btrfsic_release_block_ctx(&block_ctx);
	पूर्ण अन्यथा अणु
		/* block has not been found in hash table */
		u64 bytenr;

		अगर (!is_metadata) अणु
			processed_len = state->datablock_size;
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				pr_info("Written block (%s/%llu/?) !found in hash table, D.\n",
				       dev_state->name, dev_bytenr);
			अगर (!state->include_extent_data) अणु
				/* ignore that written D block */
				जाओ जारी_loop;
			पूर्ण

			/* this is getting ugly क्रम the
			 * include_extent_data हाल... */
			bytenr = 0;	/* unknown */
		पूर्ण अन्यथा अणु
			processed_len = state->metablock_size;
			bytenr = btrfs_stack_header_bytenr(
					(काष्ठा btrfs_header *)
					mapped_datav[0]);
			btrfsic_cmp_log_and_dev_bytenr(state, bytenr, dev_state,
						       dev_bytenr);
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				pr_info("Written block @%llu (%s/%llu/?) !found in hash table, M.\n",
				       bytenr, dev_state->name, dev_bytenr);
		पूर्ण

		block_ctx.dev = dev_state;
		block_ctx.dev_bytenr = dev_bytenr;
		block_ctx.start = bytenr;
		block_ctx.len = processed_len;
		block_ctx.pagev = शून्य;
		block_ctx.mem_to_मुक्त = शून्य;
		block_ctx.datav = mapped_datav;

		block = btrfsic_block_alloc();
		अगर (शून्य == block) अणु
			btrfsic_release_block_ctx(&block_ctx);
			जाओ जारी_loop;
		पूर्ण
		block->dev_state = dev_state;
		block->dev_bytenr = dev_bytenr;
		block->logical_bytenr = bytenr;
		block->is_metadata = is_metadata;
		block->never_written = 0;
		block->ioकरोne_w_error = 0;
		block->mirror_num = 0;	/* unknown */
		block->flush_gen = dev_state->last_flush_gen + 1;
		block->submit_bio_bh_rw = submit_bio_bh_rw;
		अगर (शून्य != bio) अणु
			block->is_ioकरोne = 0;
			BUG_ON(शून्य == bio_is_patched);
			अगर (!*bio_is_patched) अणु
				block->orig_bio_निजी = bio->bi_निजी;
				block->orig_bio_end_io = bio->bi_end_io;
				block->next_in_same_bio = शून्य;
				bio->bi_निजी = block;
				bio->bi_end_io = btrfsic_bio_end_io;
				*bio_is_patched = 1;
			पूर्ण अन्यथा अणु
				काष्ठा btrfsic_block *chained_block =
				    (काष्ठा btrfsic_block *)
				    bio->bi_निजी;

				BUG_ON(शून्य == chained_block);
				block->orig_bio_निजी =
				    chained_block->orig_bio_निजी;
				block->orig_bio_end_io =
				    chained_block->orig_bio_end_io;
				block->next_in_same_bio = chained_block;
				bio->bi_निजी = block;
			पूर्ण
		पूर्ण अन्यथा अणु
			block->is_ioकरोne = 1;
			block->orig_bio_निजी = शून्य;
			block->orig_bio_end_io = शून्य;
			block->next_in_same_bio = शून्य;
		पूर्ण
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("New written %c-block @%llu (%s/%llu/%d)\n",
			       is_metadata ? 'M' : 'D',
			       block->logical_bytenr, block->dev_state->name,
			       block->dev_bytenr, block->mirror_num);
		list_add(&block->all_blocks_node, &state->all_blocks_list);
		btrfsic_block_hashtable_add(block, &state->block_hashtable);

		अगर (is_metadata) अणु
			ret = btrfsic_process_metablock(state, block,
							&block_ctx, 0, 0);
			अगर (ret)
				pr_info("btrfsic: process_metablock(root @%llu) failed!\n",
				       dev_bytenr);
		पूर्ण
		btrfsic_release_block_ctx(&block_ctx);
	पूर्ण

जारी_loop:
	BUG_ON(!processed_len);
	dev_bytenr += processed_len;
	mapped_datav += processed_len >> PAGE_SHIFT;
	num_pages -= processed_len >> PAGE_SHIFT;
	जाओ again;
पूर्ण

अटल व्योम btrfsic_bio_end_io(काष्ठा bio *bp)
अणु
	काष्ठा btrfsic_block *block = (काष्ठा btrfsic_block *)bp->bi_निजी;
	पूर्णांक ioकरोne_w_error;

	/* mutex is not held! This is not save अगर IO is not yet completed
	 * on umount */
	ioकरोne_w_error = 0;
	अगर (bp->bi_status)
		ioकरोne_w_error = 1;

	BUG_ON(शून्य == block);
	bp->bi_निजी = block->orig_bio_निजी;
	bp->bi_end_io = block->orig_bio_end_io;

	करो अणु
		काष्ठा btrfsic_block *next_block;
		काष्ठा btrfsic_dev_state *स्थिर dev_state = block->dev_state;

		अगर ((dev_state->state->prपूर्णांक_mask &
		     BTRFSIC_PRINT_MASK_END_IO_BIO_BH))
			pr_info("bio_end_io(err=%d) for %c @%llu (%s/%llu/%d)\n",
			       bp->bi_status,
			       btrfsic_get_block_type(dev_state->state, block),
			       block->logical_bytenr, dev_state->name,
			       block->dev_bytenr, block->mirror_num);
		next_block = block->next_in_same_bio;
		block->ioकरोne_w_error = ioकरोne_w_error;
		अगर (block->submit_bio_bh_rw & REQ_PREFLUSH) अणु
			dev_state->last_flush_gen++;
			अगर ((dev_state->state->prपूर्णांक_mask &
			     BTRFSIC_PRINT_MASK_END_IO_BIO_BH))
				pr_info("bio_end_io() new %s flush_gen=%llu\n",
				       dev_state->name,
				       dev_state->last_flush_gen);
		पूर्ण
		अगर (block->submit_bio_bh_rw & REQ_FUA)
			block->flush_gen = 0; /* FUA completed means block is
					       * on disk */
		block->is_ioकरोne = 1; /* क्रम FLUSH, this releases the block */
		block = next_block;
	पूर्ण जबतक (शून्य != block);

	bp->bi_end_io(bp);
पूर्ण

अटल पूर्णांक btrfsic_process_written_superblock(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block *स्थिर superblock,
		काष्ठा btrfs_super_block *स्थिर super_hdr)
अणु
	काष्ठा btrfs_fs_info *fs_info = state->fs_info;
	पूर्णांक pass;

	superblock->generation = btrfs_super_generation(super_hdr);
	अगर (!(superblock->generation > state->max_superblock_generation ||
	      0 == state->max_superblock_generation)) अणु
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_SUPERBLOCK_WRITE)
			pr_info("btrfsic: superblock @%llu (%s/%llu/%d) with old gen %llu <= %llu\n",
			       superblock->logical_bytenr,
			       superblock->dev_state->name,
			       superblock->dev_bytenr, superblock->mirror_num,
			       btrfs_super_generation(super_hdr),
			       state->max_superblock_generation);
	पूर्ण अन्यथा अणु
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_SUPERBLOCK_WRITE)
			pr_info("btrfsic: got new superblock @%llu (%s/%llu/%d) with new gen %llu > %llu\n",
			       superblock->logical_bytenr,
			       superblock->dev_state->name,
			       superblock->dev_bytenr, superblock->mirror_num,
			       btrfs_super_generation(super_hdr),
			       state->max_superblock_generation);

		state->max_superblock_generation =
		    btrfs_super_generation(super_hdr);
		state->latest_superblock = superblock;
	पूर्ण

	क्रम (pass = 0; pass < 3; pass++) अणु
		पूर्णांक ret;
		u64 next_bytenr;
		काष्ठा btrfsic_block *next_block;
		काष्ठा btrfsic_block_data_ctx पंचांगp_next_block_ctx;
		काष्ठा btrfsic_block_link *l;
		पूर्णांक num_copies;
		पूर्णांक mirror_num;
		स्थिर अक्षर *additional_string = शून्य;
		काष्ठा btrfs_disk_key पंचांगp_disk_key = अणु0पूर्ण;

		btrfs_set_disk_key_objectid(&पंचांगp_disk_key,
					    BTRFS_ROOT_ITEM_KEY);
		btrfs_set_disk_key_objectid(&पंचांगp_disk_key, 0);

		चयन (pass) अणु
		हाल 0:
			btrfs_set_disk_key_objectid(&पंचांगp_disk_key,
						    BTRFS_ROOT_TREE_OBJECTID);
			additional_string = "root ";
			next_bytenr = btrfs_super_root(super_hdr);
			अगर (state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_ROOT_CHUNK_LOG_TREE_LOCATION)
				pr_info("root@%llu\n", next_bytenr);
			अवरोध;
		हाल 1:
			btrfs_set_disk_key_objectid(&पंचांगp_disk_key,
						    BTRFS_CHUNK_TREE_OBJECTID);
			additional_string = "chunk ";
			next_bytenr = btrfs_super_chunk_root(super_hdr);
			अगर (state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_ROOT_CHUNK_LOG_TREE_LOCATION)
				pr_info("chunk@%llu\n", next_bytenr);
			अवरोध;
		हाल 2:
			btrfs_set_disk_key_objectid(&पंचांगp_disk_key,
						    BTRFS_TREE_LOG_OBJECTID);
			additional_string = "log ";
			next_bytenr = btrfs_super_log_root(super_hdr);
			अगर (0 == next_bytenr)
				जारी;
			अगर (state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_ROOT_CHUNK_LOG_TREE_LOCATION)
				pr_info("log@%llu\n", next_bytenr);
			अवरोध;
		पूर्ण

		num_copies = btrfs_num_copies(fs_info, next_bytenr,
					      BTRFS_SUPER_INFO_SIZE);
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_NUM_COPIES)
			pr_info("num_copies(log_bytenr=%llu) = %d\n",
			       next_bytenr, num_copies);
		क्रम (mirror_num = 1; mirror_num <= num_copies; mirror_num++) अणु
			पूर्णांक was_created;

			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				pr_info("btrfsic_process_written_superblock(mirror_num=%d)\n", mirror_num);
			ret = btrfsic_map_block(state, next_bytenr,
						BTRFS_SUPER_INFO_SIZE,
						&पंचांगp_next_block_ctx,
						mirror_num);
			अगर (ret) अणु
				pr_info("btrfsic: btrfsic_map_block(@%llu, mirror=%d) failed!\n",
				       next_bytenr, mirror_num);
				वापस -1;
			पूर्ण

			next_block = btrfsic_block_lookup_or_add(
					state,
					&पंचांगp_next_block_ctx,
					additional_string,
					1, 0, 1,
					mirror_num,
					&was_created);
			अगर (शून्य == next_block) अणु
				btrfsic_release_block_ctx(&पंचांगp_next_block_ctx);
				वापस -1;
			पूर्ण

			next_block->disk_key = पंचांगp_disk_key;
			अगर (was_created)
				next_block->generation =
				    BTRFSIC_GENERATION_UNKNOWN;
			l = btrfsic_block_link_lookup_or_add(
					state,
					&पंचांगp_next_block_ctx,
					next_block,
					superblock,
					BTRFSIC_GENERATION_UNKNOWN);
			btrfsic_release_block_ctx(&पंचांगp_next_block_ctx);
			अगर (शून्य == l)
				वापस -1;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(-1 == btrfsic_check_all_ref_blocks(state, superblock, 0)))
		btrfsic_dump_tree(state);

	वापस 0;
पूर्ण

अटल पूर्णांक btrfsic_check_all_ref_blocks(काष्ठा btrfsic_state *state,
					काष्ठा btrfsic_block *स्थिर block,
					पूर्णांक recursion_level)
अणु
	स्थिर काष्ठा btrfsic_block_link *l;
	पूर्णांक ret = 0;

	अगर (recursion_level >= 3 + BTRFS_MAX_LEVEL) अणु
		/*
		 * Note that this situation can happen and करोes not
		 * indicate an error in regular हालs. It happens
		 * when disk blocks are मुक्तd and later reused.
		 * The check-पूर्णांकegrity module is not aware of any
		 * block मुक्त operations, it just recognizes block
		 * ग_लिखो operations. Thereक्रमe it keeps the linkage
		 * inक्रमmation क्रम a block until a block is
		 * rewritten. This can temporarily cause incorrect
		 * and even circular linkage inक्रमmation. This
		 * causes no harm unless such blocks are referenced
		 * by the most recent super block.
		 */
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("btrfsic: abort cyclic linkage (case 1).\n");

		वापस ret;
	पूर्ण

	/*
	 * This algorithm is recursive because the amount of used stack
	 * space is very small and the max recursion depth is limited.
	 */
	list_क्रम_each_entry(l, &block->ref_to_list, node_ref_to) अणु
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("rl=%d, %c @%llu (%s/%llu/%d) %u* refers to %c @%llu (%s/%llu/%d)\n",
			       recursion_level,
			       btrfsic_get_block_type(state, block),
			       block->logical_bytenr, block->dev_state->name,
			       block->dev_bytenr, block->mirror_num,
			       l->ref_cnt,
			       btrfsic_get_block_type(state, l->block_ref_to),
			       l->block_ref_to->logical_bytenr,
			       l->block_ref_to->dev_state->name,
			       l->block_ref_to->dev_bytenr,
			       l->block_ref_to->mirror_num);
		अगर (l->block_ref_to->never_written) अणु
			pr_info("btrfs: attempt to write superblock which references block %c @%llu (%s/%llu/%d) which is never written!\n",
			       btrfsic_get_block_type(state, l->block_ref_to),
			       l->block_ref_to->logical_bytenr,
			       l->block_ref_to->dev_state->name,
			       l->block_ref_to->dev_bytenr,
			       l->block_ref_to->mirror_num);
			ret = -1;
		पूर्ण अन्यथा अगर (!l->block_ref_to->is_ioकरोne) अणु
			pr_info("btrfs: attempt to write superblock which references block %c @%llu (%s/%llu/%d) which is not yet iodone!\n",
			       btrfsic_get_block_type(state, l->block_ref_to),
			       l->block_ref_to->logical_bytenr,
			       l->block_ref_to->dev_state->name,
			       l->block_ref_to->dev_bytenr,
			       l->block_ref_to->mirror_num);
			ret = -1;
		पूर्ण अन्यथा अगर (l->block_ref_to->ioकरोne_w_error) अणु
			pr_info("btrfs: attempt to write superblock which references block %c @%llu (%s/%llu/%d) which has write error!\n",
			       btrfsic_get_block_type(state, l->block_ref_to),
			       l->block_ref_to->logical_bytenr,
			       l->block_ref_to->dev_state->name,
			       l->block_ref_to->dev_bytenr,
			       l->block_ref_to->mirror_num);
			ret = -1;
		पूर्ण अन्यथा अगर (l->parent_generation !=
			   l->block_ref_to->generation &&
			   BTRFSIC_GENERATION_UNKNOWN !=
			   l->parent_generation &&
			   BTRFSIC_GENERATION_UNKNOWN !=
			   l->block_ref_to->generation) अणु
			pr_info("btrfs: attempt to write superblock which references block %c @%llu (%s/%llu/%d) with generation %llu != parent generation %llu!\n",
			       btrfsic_get_block_type(state, l->block_ref_to),
			       l->block_ref_to->logical_bytenr,
			       l->block_ref_to->dev_state->name,
			       l->block_ref_to->dev_bytenr,
			       l->block_ref_to->mirror_num,
			       l->block_ref_to->generation,
			       l->parent_generation);
			ret = -1;
		पूर्ण अन्यथा अगर (l->block_ref_to->flush_gen >
			   l->block_ref_to->dev_state->last_flush_gen) अणु
			pr_info("btrfs: attempt to write superblock which references block %c @%llu (%s/%llu/%d) which is not flushed out of disk's write cache (block flush_gen=%llu, dev->flush_gen=%llu)!\n",
			       btrfsic_get_block_type(state, l->block_ref_to),
			       l->block_ref_to->logical_bytenr,
			       l->block_ref_to->dev_state->name,
			       l->block_ref_to->dev_bytenr,
			       l->block_ref_to->mirror_num, block->flush_gen,
			       l->block_ref_to->dev_state->last_flush_gen);
			ret = -1;
		पूर्ण अन्यथा अगर (-1 == btrfsic_check_all_ref_blocks(state,
							      l->block_ref_to,
							      recursion_level +
							      1)) अणु
			ret = -1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक btrfsic_is_block_ref_by_superblock(
		स्थिर काष्ठा btrfsic_state *state,
		स्थिर काष्ठा btrfsic_block *block,
		पूर्णांक recursion_level)
अणु
	स्थिर काष्ठा btrfsic_block_link *l;

	अगर (recursion_level >= 3 + BTRFS_MAX_LEVEL) अणु
		/* refer to comment at "abort cyclic linkage (case 1)" */
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("btrfsic: abort cyclic linkage (case 2).\n");

		वापस 0;
	पूर्ण

	/*
	 * This algorithm is recursive because the amount of used stack space
	 * is very small and the max recursion depth is limited.
	 */
	list_क्रम_each_entry(l, &block->ref_from_list, node_ref_from) अणु
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("rl=%d, %c @%llu (%s/%llu/%d) is ref %u* from %c @%llu (%s/%llu/%d)\n",
			       recursion_level,
			       btrfsic_get_block_type(state, block),
			       block->logical_bytenr, block->dev_state->name,
			       block->dev_bytenr, block->mirror_num,
			       l->ref_cnt,
			       btrfsic_get_block_type(state, l->block_ref_from),
			       l->block_ref_from->logical_bytenr,
			       l->block_ref_from->dev_state->name,
			       l->block_ref_from->dev_bytenr,
			       l->block_ref_from->mirror_num);
		अगर (l->block_ref_from->is_superblock &&
		    state->latest_superblock->dev_bytenr ==
		    l->block_ref_from->dev_bytenr &&
		    state->latest_superblock->dev_state->bdev ==
		    l->block_ref_from->dev_state->bdev)
			वापस 1;
		अन्यथा अगर (btrfsic_is_block_ref_by_superblock(state,
							    l->block_ref_from,
							    recursion_level +
							    1))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम btrfsic_prपूर्णांक_add_link(स्थिर काष्ठा btrfsic_state *state,
				   स्थिर काष्ठा btrfsic_block_link *l)
अणु
	pr_info("Add %u* link from %c @%llu (%s/%llu/%d) to %c @%llu (%s/%llu/%d).\n",
	       l->ref_cnt,
	       btrfsic_get_block_type(state, l->block_ref_from),
	       l->block_ref_from->logical_bytenr,
	       l->block_ref_from->dev_state->name,
	       l->block_ref_from->dev_bytenr, l->block_ref_from->mirror_num,
	       btrfsic_get_block_type(state, l->block_ref_to),
	       l->block_ref_to->logical_bytenr,
	       l->block_ref_to->dev_state->name, l->block_ref_to->dev_bytenr,
	       l->block_ref_to->mirror_num);
पूर्ण

अटल व्योम btrfsic_prपूर्णांक_rem_link(स्थिर काष्ठा btrfsic_state *state,
				   स्थिर काष्ठा btrfsic_block_link *l)
अणु
	pr_info("Rem %u* link from %c @%llu (%s/%llu/%d) to %c @%llu (%s/%llu/%d).\n",
	       l->ref_cnt,
	       btrfsic_get_block_type(state, l->block_ref_from),
	       l->block_ref_from->logical_bytenr,
	       l->block_ref_from->dev_state->name,
	       l->block_ref_from->dev_bytenr, l->block_ref_from->mirror_num,
	       btrfsic_get_block_type(state, l->block_ref_to),
	       l->block_ref_to->logical_bytenr,
	       l->block_ref_to->dev_state->name, l->block_ref_to->dev_bytenr,
	       l->block_ref_to->mirror_num);
पूर्ण

अटल अक्षर btrfsic_get_block_type(स्थिर काष्ठा btrfsic_state *state,
				   स्थिर काष्ठा btrfsic_block *block)
अणु
	अगर (block->is_superblock &&
	    state->latest_superblock->dev_bytenr == block->dev_bytenr &&
	    state->latest_superblock->dev_state->bdev == block->dev_state->bdev)
		वापस 'S';
	अन्यथा अगर (block->is_superblock)
		वापस 's';
	अन्यथा अगर (block->is_metadata)
		वापस 'M';
	अन्यथा
		वापस 'D';
पूर्ण

अटल व्योम btrfsic_dump_tree(स्थिर काष्ठा btrfsic_state *state)
अणु
	btrfsic_dump_tree_sub(state, state->latest_superblock, 0);
पूर्ण

अटल व्योम btrfsic_dump_tree_sub(स्थिर काष्ठा btrfsic_state *state,
				  स्थिर काष्ठा btrfsic_block *block,
				  पूर्णांक indent_level)
अणु
	स्थिर काष्ठा btrfsic_block_link *l;
	पूर्णांक indent_add;
	अटल अक्षर buf[80];
	पूर्णांक cursor_position;

	/*
	 * Should better fill an on-stack buffer with a complete line and
	 * dump it at once when it is समय to prपूर्णांक a newline अक्षरacter.
	 */

	/*
	 * This algorithm is recursive because the amount of used stack space
	 * is very small and the max recursion depth is limited.
	 */
	indent_add = प्र_लिखो(buf, "%c-%llu(%s/%llu/%u)",
			     btrfsic_get_block_type(state, block),
			     block->logical_bytenr, block->dev_state->name,
			     block->dev_bytenr, block->mirror_num);
	अगर (indent_level + indent_add > BTRFSIC_TREE_DUMP_MAX_INDENT_LEVEL) अणु
		prपूर्णांकk("[...]\n");
		वापस;
	पूर्ण
	prपूर्णांकk(buf);
	indent_level += indent_add;
	अगर (list_empty(&block->ref_to_list)) अणु
		prपूर्णांकk("\n");
		वापस;
	पूर्ण
	अगर (block->mirror_num > 1 &&
	    !(state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_TREE_WITH_ALL_MIRRORS)) अणु
		prपूर्णांकk(" [...]\n");
		वापस;
	पूर्ण

	cursor_position = indent_level;
	list_क्रम_each_entry(l, &block->ref_to_list, node_ref_to) अणु
		जबतक (cursor_position < indent_level) अणु
			prपूर्णांकk(" ");
			cursor_position++;
		पूर्ण
		अगर (l->ref_cnt > 1)
			indent_add = प्र_लिखो(buf, " %d*--> ", l->ref_cnt);
		अन्यथा
			indent_add = प्र_लिखो(buf, " --> ");
		अगर (indent_level + indent_add >
		    BTRFSIC_TREE_DUMP_MAX_INDENT_LEVEL) अणु
			prपूर्णांकk("[...]\n");
			cursor_position = 0;
			जारी;
		पूर्ण

		prपूर्णांकk(buf);

		btrfsic_dump_tree_sub(state, l->block_ref_to,
				      indent_level + indent_add);
		cursor_position = 0;
	पूर्ण
पूर्ण

अटल काष्ठा btrfsic_block_link *btrfsic_block_link_lookup_or_add(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block_data_ctx *next_block_ctx,
		काष्ठा btrfsic_block *next_block,
		काष्ठा btrfsic_block *from_block,
		u64 parent_generation)
अणु
	काष्ठा btrfsic_block_link *l;

	l = btrfsic_block_link_hashtable_lookup(next_block_ctx->dev->bdev,
						next_block_ctx->dev_bytenr,
						from_block->dev_state->bdev,
						from_block->dev_bytenr,
						&state->block_link_hashtable);
	अगर (शून्य == l) अणु
		l = btrfsic_block_link_alloc();
		अगर (!l)
			वापस शून्य;

		l->block_ref_to = next_block;
		l->block_ref_from = from_block;
		l->ref_cnt = 1;
		l->parent_generation = parent_generation;

		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			btrfsic_prपूर्णांक_add_link(state, l);

		list_add(&l->node_ref_to, &from_block->ref_to_list);
		list_add(&l->node_ref_from, &next_block->ref_from_list);

		btrfsic_block_link_hashtable_add(l,
						 &state->block_link_hashtable);
	पूर्ण अन्यथा अणु
		l->ref_cnt++;
		l->parent_generation = parent_generation;
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			btrfsic_prपूर्णांक_add_link(state, l);
	पूर्ण

	वापस l;
पूर्ण

अटल काष्ठा btrfsic_block *btrfsic_block_lookup_or_add(
		काष्ठा btrfsic_state *state,
		काष्ठा btrfsic_block_data_ctx *block_ctx,
		स्थिर अक्षर *additional_string,
		पूर्णांक is_metadata,
		पूर्णांक is_ioकरोne,
		पूर्णांक never_written,
		पूर्णांक mirror_num,
		पूर्णांक *was_created)
अणु
	काष्ठा btrfsic_block *block;

	block = btrfsic_block_hashtable_lookup(block_ctx->dev->bdev,
					       block_ctx->dev_bytenr,
					       &state->block_hashtable);
	अगर (शून्य == block) अणु
		काष्ठा btrfsic_dev_state *dev_state;

		block = btrfsic_block_alloc();
		अगर (!block)
			वापस शून्य;

		dev_state = btrfsic_dev_state_lookup(block_ctx->dev->bdev->bd_dev);
		अगर (शून्य == dev_state) अणु
			pr_info("btrfsic: error, lookup dev_state failed!\n");
			btrfsic_block_मुक्त(block);
			वापस शून्य;
		पूर्ण
		block->dev_state = dev_state;
		block->dev_bytenr = block_ctx->dev_bytenr;
		block->logical_bytenr = block_ctx->start;
		block->is_metadata = is_metadata;
		block->is_ioकरोne = is_ioकरोne;
		block->never_written = never_written;
		block->mirror_num = mirror_num;
		अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("New %s%c-block @%llu (%s/%llu/%d)\n",
			       additional_string,
			       btrfsic_get_block_type(state, block),
			       block->logical_bytenr, dev_state->name,
			       block->dev_bytenr, mirror_num);
		list_add(&block->all_blocks_node, &state->all_blocks_list);
		btrfsic_block_hashtable_add(block, &state->block_hashtable);
		अगर (शून्य != was_created)
			*was_created = 1;
	पूर्ण अन्यथा अणु
		अगर (शून्य != was_created)
			*was_created = 0;
	पूर्ण

	वापस block;
पूर्ण

अटल व्योम btrfsic_cmp_log_and_dev_bytenr(काष्ठा btrfsic_state *state,
					   u64 bytenr,
					   काष्ठा btrfsic_dev_state *dev_state,
					   u64 dev_bytenr)
अणु
	काष्ठा btrfs_fs_info *fs_info = state->fs_info;
	काष्ठा btrfsic_block_data_ctx block_ctx;
	पूर्णांक num_copies;
	पूर्णांक mirror_num;
	पूर्णांक match = 0;
	पूर्णांक ret;

	num_copies = btrfs_num_copies(fs_info, bytenr, state->metablock_size);

	क्रम (mirror_num = 1; mirror_num <= num_copies; mirror_num++) अणु
		ret = btrfsic_map_block(state, bytenr, state->metablock_size,
					&block_ctx, mirror_num);
		अगर (ret) अणु
			pr_info("btrfsic: btrfsic_map_block(logical @%llu, mirror %d) failed!\n",
			       bytenr, mirror_num);
			जारी;
		पूर्ण

		अगर (dev_state->bdev == block_ctx.dev->bdev &&
		    dev_bytenr == block_ctx.dev_bytenr) अणु
			match++;
			btrfsic_release_block_ctx(&block_ctx);
			अवरोध;
		पूर्ण
		btrfsic_release_block_ctx(&block_ctx);
	पूर्ण

	अगर (WARN_ON(!match)) अणु
		pr_info("btrfs: attempt to write M-block which contains logical bytenr that doesn't map to dev+physical bytenr of submit_bio, buffer->log_bytenr=%llu, submit_bio(bdev=%s, phys_bytenr=%llu)!\n",
		       bytenr, dev_state->name, dev_bytenr);
		क्रम (mirror_num = 1; mirror_num <= num_copies; mirror_num++) अणु
			ret = btrfsic_map_block(state, bytenr,
						state->metablock_size,
						&block_ctx, mirror_num);
			अगर (ret)
				जारी;

			pr_info("Read logical bytenr @%llu maps to (%s/%llu/%d)\n",
			       bytenr, block_ctx.dev->name,
			       block_ctx.dev_bytenr, mirror_num);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा btrfsic_dev_state *btrfsic_dev_state_lookup(dev_t dev)
अणु
	वापस btrfsic_dev_state_hashtable_lookup(dev,
						  &btrfsic_dev_state_hashtable);
पूर्ण

अटल व्योम __btrfsic_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा btrfsic_dev_state *dev_state;

	अगर (!btrfsic_is_initialized)
		वापस;

	mutex_lock(&btrfsic_mutex);
	/* since btrfsic_submit_bio() is also called beक्रमe
	 * btrfsic_mount(), this might वापस शून्य */
	dev_state = btrfsic_dev_state_lookup(bio->bi_bdev->bd_dev);
	अगर (शून्य != dev_state &&
	    (bio_op(bio) == REQ_OP_WRITE) && bio_has_data(bio)) अणु
		पूर्णांक i = 0;
		u64 dev_bytenr;
		u64 cur_bytenr;
		काष्ठा bio_vec bvec;
		काष्ठा bvec_iter iter;
		पूर्णांक bio_is_patched;
		अक्षर **mapped_datav;
		अचिन्हित पूर्णांक segs = bio_segments(bio);

		dev_bytenr = 512 * bio->bi_iter.bi_sector;
		bio_is_patched = 0;
		अगर (dev_state->state->prपूर्णांक_mask &
		    BTRFSIC_PRINT_MASK_SUBMIT_BIO_BH)
			pr_info("submit_bio(rw=%d,0x%x, bi_vcnt=%u, bi_sector=%llu (bytenr %llu), bi_bdev=%p)\n",
			       bio_op(bio), bio->bi_opf, segs,
			       bio->bi_iter.bi_sector, dev_bytenr, bio->bi_bdev);

		mapped_datav = kदो_स्मृति_array(segs,
					     माप(*mapped_datav), GFP_NOFS);
		अगर (!mapped_datav)
			जाओ leave;
		cur_bytenr = dev_bytenr;

		bio_क्रम_each_segment(bvec, bio, iter) अणु
			BUG_ON(bvec.bv_len != PAGE_SIZE);
			mapped_datav[i] = kmap_local_page(bvec.bv_page);
			i++;

			अगर (dev_state->state->prपूर्णांक_mask &
			    BTRFSIC_PRINT_MASK_SUBMIT_BIO_BH_VERBOSE)
				pr_info("#%u: bytenr=%llu, len=%u, offset=%u\n",
				       i, cur_bytenr, bvec.bv_len, bvec.bv_offset);
			cur_bytenr += bvec.bv_len;
		पूर्ण
		btrfsic_process_written_block(dev_state, dev_bytenr,
					      mapped_datav, segs,
					      bio, &bio_is_patched,
					      bio->bi_opf);
		/* Unmap in reverse order */
		क्रम (--i; i >= 0; i--)
			kunmap_local(mapped_datav[i]);
		kमुक्त(mapped_datav);
	पूर्ण अन्यथा अगर (शून्य != dev_state && (bio->bi_opf & REQ_PREFLUSH)) अणु
		अगर (dev_state->state->prपूर्णांक_mask &
		    BTRFSIC_PRINT_MASK_SUBMIT_BIO_BH)
			pr_info("submit_bio(rw=%d,0x%x FLUSH, bdev=%p)\n",
			       bio_op(bio), bio->bi_opf, bio->bi_bdev);
		अगर (!dev_state->dummy_block_क्रम_bio_bh_flush.is_ioकरोne) अणु
			अगर ((dev_state->state->prपूर्णांक_mask &
			     (BTRFSIC_PRINT_MASK_SUBMIT_BIO_BH |
			      BTRFSIC_PRINT_MASK_VERBOSE)))
				pr_info("btrfsic_submit_bio(%s) with FLUSH but dummy block already in use (ignored)!\n",
				       dev_state->name);
		पूर्ण अन्यथा अणु
			काष्ठा btrfsic_block *स्थिर block =
				&dev_state->dummy_block_क्रम_bio_bh_flush;

			block->is_ioकरोne = 0;
			block->never_written = 0;
			block->ioकरोne_w_error = 0;
			block->flush_gen = dev_state->last_flush_gen + 1;
			block->submit_bio_bh_rw = bio->bi_opf;
			block->orig_bio_निजी = bio->bi_निजी;
			block->orig_bio_end_io = bio->bi_end_io;
			block->next_in_same_bio = शून्य;
			bio->bi_निजी = block;
			bio->bi_end_io = btrfsic_bio_end_io;
		पूर्ण
	पूर्ण
leave:
	mutex_unlock(&btrfsic_mutex);
पूर्ण

व्योम btrfsic_submit_bio(काष्ठा bio *bio)
अणु
	__btrfsic_submit_bio(bio);
	submit_bio(bio);
पूर्ण

पूर्णांक btrfsic_submit_bio_रुको(काष्ठा bio *bio)
अणु
	__btrfsic_submit_bio(bio);
	वापस submit_bio_रुको(bio);
पूर्ण

पूर्णांक btrfsic_mount(काष्ठा btrfs_fs_info *fs_info,
		  काष्ठा btrfs_fs_devices *fs_devices,
		  पूर्णांक including_extent_data, u32 prपूर्णांक_mask)
अणु
	पूर्णांक ret;
	काष्ठा btrfsic_state *state;
	काष्ठा list_head *dev_head = &fs_devices->devices;
	काष्ठा btrfs_device *device;

	अगर (!PAGE_ALIGNED(fs_info->nodesize)) अणु
		pr_info("btrfsic: cannot handle nodesize %d not being a multiple of PAGE_SIZE %ld!\n",
		       fs_info->nodesize, PAGE_SIZE);
		वापस -1;
	पूर्ण
	अगर (!PAGE_ALIGNED(fs_info->sectorsize)) अणु
		pr_info("btrfsic: cannot handle sectorsize %d not being a multiple of PAGE_SIZE %ld!\n",
		       fs_info->sectorsize, PAGE_SIZE);
		वापस -1;
	पूर्ण
	state = kvzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	अगर (!btrfsic_is_initialized) अणु
		mutex_init(&btrfsic_mutex);
		btrfsic_dev_state_hashtable_init(&btrfsic_dev_state_hashtable);
		btrfsic_is_initialized = 1;
	पूर्ण
	mutex_lock(&btrfsic_mutex);
	state->fs_info = fs_info;
	state->prपूर्णांक_mask = prपूर्णांक_mask;
	state->include_extent_data = including_extent_data;
	state->metablock_size = fs_info->nodesize;
	state->datablock_size = fs_info->sectorsize;
	INIT_LIST_HEAD(&state->all_blocks_list);
	btrfsic_block_hashtable_init(&state->block_hashtable);
	btrfsic_block_link_hashtable_init(&state->block_link_hashtable);
	state->max_superblock_generation = 0;
	state->latest_superblock = शून्य;

	list_क्रम_each_entry(device, dev_head, dev_list) अणु
		काष्ठा btrfsic_dev_state *ds;
		स्थिर अक्षर *p;

		अगर (!device->bdev || !device->name)
			जारी;

		ds = btrfsic_dev_state_alloc();
		अगर (शून्य == ds) अणु
			mutex_unlock(&btrfsic_mutex);
			वापस -ENOMEM;
		पूर्ण
		ds->bdev = device->bdev;
		ds->state = state;
		bdevname(ds->bdev, ds->name);
		ds->name[BDEVNAME_SIZE - 1] = '\0';
		p = kbasename(ds->name);
		strlcpy(ds->name, p, माप(ds->name));
		btrfsic_dev_state_hashtable_add(ds,
						&btrfsic_dev_state_hashtable);
	पूर्ण

	ret = btrfsic_process_superblock(state, fs_devices);
	अगर (0 != ret) अणु
		mutex_unlock(&btrfsic_mutex);
		btrfsic_unmount(fs_devices);
		वापस ret;
	पूर्ण

	अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_INITIAL_DATABASE)
		btrfsic_dump_database(state);
	अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_INITIAL_TREE)
		btrfsic_dump_tree(state);

	mutex_unlock(&btrfsic_mutex);
	वापस 0;
पूर्ण

व्योम btrfsic_unmount(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	काष्ठा btrfsic_block *b_all, *पंचांगp_all;
	काष्ठा btrfsic_state *state;
	काष्ठा list_head *dev_head = &fs_devices->devices;
	काष्ठा btrfs_device *device;

	अगर (!btrfsic_is_initialized)
		वापस;

	mutex_lock(&btrfsic_mutex);

	state = शून्य;
	list_क्रम_each_entry(device, dev_head, dev_list) अणु
		काष्ठा btrfsic_dev_state *ds;

		अगर (!device->bdev || !device->name)
			जारी;

		ds = btrfsic_dev_state_hashtable_lookup(
				device->bdev->bd_dev,
				&btrfsic_dev_state_hashtable);
		अगर (शून्य != ds) अणु
			state = ds->state;
			btrfsic_dev_state_hashtable_हटाओ(ds);
			btrfsic_dev_state_मुक्त(ds);
		पूर्ण
	पूर्ण

	अगर (शून्य == state) अणु
		pr_info("btrfsic: error, cannot find state information on umount!\n");
		mutex_unlock(&btrfsic_mutex);
		वापस;
	पूर्ण

	/*
	 * Don't care about keeping the lists' state up to date,
	 * just मुक्त all memory that was allocated dynamically.
	 * Free the blocks and the block_links.
	 */
	list_क्रम_each_entry_safe(b_all, पंचांगp_all, &state->all_blocks_list,
				 all_blocks_node) अणु
		काष्ठा btrfsic_block_link *l, *पंचांगp;

		list_क्रम_each_entry_safe(l, पंचांगp, &b_all->ref_to_list,
					 node_ref_to) अणु
			अगर (state->prपूर्णांक_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				btrfsic_prपूर्णांक_rem_link(state, l);

			l->ref_cnt--;
			अगर (0 == l->ref_cnt)
				btrfsic_block_link_मुक्त(l);
		पूर्ण

		अगर (b_all->is_ioकरोne || b_all->never_written)
			btrfsic_block_मुक्त(b_all);
		अन्यथा
			pr_info("btrfs: attempt to free %c-block @%llu (%s/%llu/%d) on umount which is not yet iodone!\n",
			       btrfsic_get_block_type(state, b_all),
			       b_all->logical_bytenr, b_all->dev_state->name,
			       b_all->dev_bytenr, b_all->mirror_num);
	पूर्ण

	mutex_unlock(&btrfsic_mutex);

	kvमुक्त(state);
पूर्ण
