<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "block-rsv.h"
#समावेश "space-info.h"
#समावेश "transaction.h"
#समावेश "block-group.h"

/*
 * HOW DO BLOCK RESERVES WORK
 *
 *   Think of block_rsv's as buckets क्रम logically grouped metadata
 *   reservations.  Each block_rsv has a ->size and a ->reserved.  ->size is
 *   how large we want our block rsv to be, ->reserved is how much space is
 *   currently reserved क्रम this block reserve.
 *
 *   ->failfast exists क्रम the truncate हाल, and is described below.
 *
 * NORMAL OPERATION
 *
 *   -> Reserve
 *     Entrance: btrfs_block_rsv_add, btrfs_block_rsv_refill
 *
 *     We call पूर्णांकo btrfs_reserve_metadata_bytes() with our bytes, which is
 *     accounted क्रम in space_info->bytes_may_use, and then add the bytes to
 *     ->reserved, and ->size in the हाल of btrfs_block_rsv_add.
 *
 *     ->size is an over-estimation of how much we may use क्रम a particular
 *     operation.
 *
 *   -> Use
 *     Entrance: btrfs_use_block_rsv
 *
 *     When we करो a btrfs_alloc_tree_block() we call पूर्णांकo btrfs_use_block_rsv()
 *     to determine the appropriate block_rsv to use, and then verअगरy that
 *     ->reserved has enough space क्रम our tree block allocation.  Once
 *     successful we subtract fs_info->nodesize from ->reserved.
 *
 *   -> Finish
 *     Entrance: btrfs_block_rsv_release
 *
 *     We are finished with our operation, subtract our inभागidual reservation
 *     from ->size, and then subtract ->size from ->reserved and मुक्त up the
 *     excess अगर there is any.
 *
 *     There is some logic here to refill the delayed refs rsv or the global rsv
 *     as needed, otherwise the excess is subtracted from
 *     space_info->bytes_may_use.
 *
 * TYPES OF BLOCK RESERVES
 *
 * BLOCK_RSV_TRANS, BLOCK_RSV_DELOPS, BLOCK_RSV_CHUNK
 *   These behave normally, as described above, just within the confines of the
 *   lअगरeसमय of their particular operation (transaction क्रम the whole trans
 *   handle lअगरeसमय, क्रम example).
 *
 * BLOCK_RSV_GLOBAL
 *   It is impossible to properly account क्रम all the space that may be required
 *   to make our extent tree updates.  This block reserve acts as an overflow
 *   buffer in हाल our delayed refs reserve करोes not reserve enough space to
 *   update the extent tree.
 *
 *   We can steal from this in some हालs as well, notably on evict() or
 *   truncate() in order to help users recover from ENOSPC conditions.
 *
 * BLOCK_RSV_DELALLOC
 *   The inभागidual item sizes are determined by the per-inode size
 *   calculations, which are described with the delalloc code.  This is pretty
 *   straightक्रमward, it's just the calculation of ->size encodes a lot of
 *   dअगरferent items, and thus it माला_लो used when updating inodes, inserting file
 *   extents, and inserting checksums.
 *
 * BLOCK_RSV_DELREFS
 *   We keep a running tally of how many delayed refs we have on the प्रणाली.
 *   We assume each one of these delayed refs are going to use a full
 *   reservation.  We use the transaction items and pre-reserve space क्रम every
 *   operation, and use this reservation to refill any gap between ->size and
 *   ->reserved that may exist.
 *
 *   From there it's straightक्रमward, removing a delayed ref means we हटाओ its
 *   count from ->size and मुक्त up reservations as necessary.  Since this is
 *   the most dynamic block reserve in the प्रणाली, we will try to refill this
 *   block reserve first with any excess वापसed by any other block reserve.
 *
 * BLOCK_RSV_EMPTY
 *   This is the fallback block reserve to make us try to reserve space अगर we
 *   करोn't have a specअगरic bucket क्रम this allocation.  It is mostly used क्रम
 *   updating the device tree and such, since that is a separate pool we're
 *   content to just reserve space from the space_info on demand.
 *
 * BLOCK_RSV_TEMP
 *   This is used by things like truncate and iput.  We will temporarily
 *   allocate a block reserve, set it to some size, and then truncate bytes
 *   until we have no space left.  With ->failfast set we'll simply वापस
 *   ENOSPC from btrfs_use_block_rsv() to संकेत that we need to unwind and try
 *   to make a new reservation.  This is because these operations are
 *   unbounded, so we want to करो as much work as we can, and then back off and
 *   re-reserve.
 */

अटल u64 block_rsv_release_bytes(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_block_rsv *block_rsv,
				    काष्ठा btrfs_block_rsv *dest, u64 num_bytes,
				    u64 *qgroup_to_release_ret)
अणु
	काष्ठा btrfs_space_info *space_info = block_rsv->space_info;
	u64 qgroup_to_release = 0;
	u64 ret;

	spin_lock(&block_rsv->lock);
	अगर (num_bytes == (u64)-1) अणु
		num_bytes = block_rsv->size;
		qgroup_to_release = block_rsv->qgroup_rsv_size;
	पूर्ण
	block_rsv->size -= num_bytes;
	अगर (block_rsv->reserved >= block_rsv->size) अणु
		num_bytes = block_rsv->reserved - block_rsv->size;
		block_rsv->reserved = block_rsv->size;
		block_rsv->full = 1;
	पूर्ण अन्यथा अणु
		num_bytes = 0;
	पूर्ण
	अगर (block_rsv->qgroup_rsv_reserved >= block_rsv->qgroup_rsv_size) अणु
		qgroup_to_release = block_rsv->qgroup_rsv_reserved -
				    block_rsv->qgroup_rsv_size;
		block_rsv->qgroup_rsv_reserved = block_rsv->qgroup_rsv_size;
	पूर्ण अन्यथा अणु
		qgroup_to_release = 0;
	पूर्ण
	spin_unlock(&block_rsv->lock);

	ret = num_bytes;
	अगर (num_bytes > 0) अणु
		अगर (dest) अणु
			spin_lock(&dest->lock);
			अगर (!dest->full) अणु
				u64 bytes_to_add;

				bytes_to_add = dest->size - dest->reserved;
				bytes_to_add = min(num_bytes, bytes_to_add);
				dest->reserved += bytes_to_add;
				अगर (dest->reserved >= dest->size)
					dest->full = 1;
				num_bytes -= bytes_to_add;
			पूर्ण
			spin_unlock(&dest->lock);
		पूर्ण
		अगर (num_bytes)
			btrfs_space_info_मुक्त_bytes_may_use(fs_info,
							    space_info,
							    num_bytes);
	पूर्ण
	अगर (qgroup_to_release_ret)
		*qgroup_to_release_ret = qgroup_to_release;
	वापस ret;
पूर्ण

पूर्णांक btrfs_block_rsv_migrate(काष्ठा btrfs_block_rsv *src,
			    काष्ठा btrfs_block_rsv *dst, u64 num_bytes,
			    bool update_size)
अणु
	पूर्णांक ret;

	ret = btrfs_block_rsv_use_bytes(src, num_bytes);
	अगर (ret)
		वापस ret;

	btrfs_block_rsv_add_bytes(dst, num_bytes, update_size);
	वापस 0;
पूर्ण

व्योम btrfs_init_block_rsv(काष्ठा btrfs_block_rsv *rsv, अचिन्हित लघु type)
अणु
	स_रखो(rsv, 0, माप(*rsv));
	spin_lock_init(&rsv->lock);
	rsv->type = type;
पूर्ण

व्योम btrfs_init_metadata_block_rsv(काष्ठा btrfs_fs_info *fs_info,
				   काष्ठा btrfs_block_rsv *rsv,
				   अचिन्हित लघु type)
अणु
	btrfs_init_block_rsv(rsv, type);
	rsv->space_info = btrfs_find_space_info(fs_info,
					    BTRFS_BLOCK_GROUP_METADATA);
पूर्ण

काष्ठा btrfs_block_rsv *btrfs_alloc_block_rsv(काष्ठा btrfs_fs_info *fs_info,
					      अचिन्हित लघु type)
अणु
	काष्ठा btrfs_block_rsv *block_rsv;

	block_rsv = kदो_स्मृति(माप(*block_rsv), GFP_NOFS);
	अगर (!block_rsv)
		वापस शून्य;

	btrfs_init_metadata_block_rsv(fs_info, block_rsv, type);
	वापस block_rsv;
पूर्ण

व्योम btrfs_मुक्त_block_rsv(काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा btrfs_block_rsv *rsv)
अणु
	अगर (!rsv)
		वापस;
	btrfs_block_rsv_release(fs_info, rsv, (u64)-1, शून्य);
	kमुक्त(rsv);
पूर्ण

पूर्णांक btrfs_block_rsv_add(काष्ठा btrfs_root *root,
			काष्ठा btrfs_block_rsv *block_rsv, u64 num_bytes,
			क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	पूर्णांक ret;

	अगर (num_bytes == 0)
		वापस 0;

	ret = btrfs_reserve_metadata_bytes(root, block_rsv, num_bytes, flush);
	अगर (!ret)
		btrfs_block_rsv_add_bytes(block_rsv, num_bytes, true);

	वापस ret;
पूर्ण

पूर्णांक btrfs_block_rsv_check(काष्ठा btrfs_block_rsv *block_rsv, पूर्णांक min_factor)
अणु
	u64 num_bytes = 0;
	पूर्णांक ret = -ENOSPC;

	अगर (!block_rsv)
		वापस 0;

	spin_lock(&block_rsv->lock);
	num_bytes = भाग_factor(block_rsv->size, min_factor);
	अगर (block_rsv->reserved >= num_bytes)
		ret = 0;
	spin_unlock(&block_rsv->lock);

	वापस ret;
पूर्ण

पूर्णांक btrfs_block_rsv_refill(काष्ठा btrfs_root *root,
			   काष्ठा btrfs_block_rsv *block_rsv, u64 min_reserved,
			   क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	u64 num_bytes = 0;
	पूर्णांक ret = -ENOSPC;

	अगर (!block_rsv)
		वापस 0;

	spin_lock(&block_rsv->lock);
	num_bytes = min_reserved;
	अगर (block_rsv->reserved >= num_bytes)
		ret = 0;
	अन्यथा
		num_bytes -= block_rsv->reserved;
	spin_unlock(&block_rsv->lock);

	अगर (!ret)
		वापस 0;

	ret = btrfs_reserve_metadata_bytes(root, block_rsv, num_bytes, flush);
	अगर (!ret) अणु
		btrfs_block_rsv_add_bytes(block_rsv, num_bytes, false);
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

u64 btrfs_block_rsv_release(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_block_rsv *block_rsv, u64 num_bytes,
			    u64 *qgroup_to_release)
अणु
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	काष्ठा btrfs_block_rsv *delayed_rsv = &fs_info->delayed_refs_rsv;
	काष्ठा btrfs_block_rsv *target = शून्य;

	/*
	 * If we are the delayed_rsv then push to the global rsv, otherwise dump
	 * पूर्णांकo the delayed rsv अगर it is not full.
	 */
	अगर (block_rsv == delayed_rsv)
		target = global_rsv;
	अन्यथा अगर (block_rsv != global_rsv && !delayed_rsv->full)
		target = delayed_rsv;

	अगर (target && block_rsv->space_info != target->space_info)
		target = शून्य;

	वापस block_rsv_release_bytes(fs_info, block_rsv, target, num_bytes,
				       qgroup_to_release);
पूर्ण

पूर्णांक btrfs_block_rsv_use_bytes(काष्ठा btrfs_block_rsv *block_rsv, u64 num_bytes)
अणु
	पूर्णांक ret = -ENOSPC;

	spin_lock(&block_rsv->lock);
	अगर (block_rsv->reserved >= num_bytes) अणु
		block_rsv->reserved -= num_bytes;
		अगर (block_rsv->reserved < block_rsv->size)
			block_rsv->full = 0;
		ret = 0;
	पूर्ण
	spin_unlock(&block_rsv->lock);
	वापस ret;
पूर्ण

व्योम btrfs_block_rsv_add_bytes(काष्ठा btrfs_block_rsv *block_rsv,
			       u64 num_bytes, bool update_size)
अणु
	spin_lock(&block_rsv->lock);
	block_rsv->reserved += num_bytes;
	अगर (update_size)
		block_rsv->size += num_bytes;
	अन्यथा अगर (block_rsv->reserved >= block_rsv->size)
		block_rsv->full = 1;
	spin_unlock(&block_rsv->lock);
पूर्ण

पूर्णांक btrfs_cond_migrate_bytes(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा btrfs_block_rsv *dest, u64 num_bytes,
			     पूर्णांक min_factor)
अणु
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	u64 min_bytes;

	अगर (global_rsv->space_info != dest->space_info)
		वापस -ENOSPC;

	spin_lock(&global_rsv->lock);
	min_bytes = भाग_factor(global_rsv->size, min_factor);
	अगर (global_rsv->reserved < min_bytes + num_bytes) अणु
		spin_unlock(&global_rsv->lock);
		वापस -ENOSPC;
	पूर्ण
	global_rsv->reserved -= num_bytes;
	अगर (global_rsv->reserved < global_rsv->size)
		global_rsv->full = 0;
	spin_unlock(&global_rsv->lock);

	btrfs_block_rsv_add_bytes(dest, num_bytes, true);
	वापस 0;
पूर्ण

व्योम btrfs_update_global_block_rsv(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_block_rsv *block_rsv = &fs_info->global_block_rsv;
	काष्ठा btrfs_space_info *sinfo = block_rsv->space_info;
	u64 num_bytes;
	अचिन्हित min_items;

	/*
	 * The global block rsv is based on the size of the extent tree, the
	 * checksum tree and the root tree.  If the fs is empty we want to set
	 * it to a minimal amount क्रम safety.
	 */
	num_bytes = btrfs_root_used(&fs_info->extent_root->root_item) +
		btrfs_root_used(&fs_info->csum_root->root_item) +
		btrfs_root_used(&fs_info->tree_root->root_item);

	/*
	 * We at a minimum are going to modअगरy the csum root, the tree root, and
	 * the extent root.
	 */
	min_items = 3;

	/*
	 * But we also want to reserve enough space so we can करो the fallback
	 * global reserve क्रम an unlink, which is an additional 5 items (see the
	 * comment in __unlink_start_trans क्रम what we're modअगरying.)
	 *
	 * But we also need space क्रम the delayed ref updates from the unlink,
	 * so its 10, 5 क्रम the actual operation, and 5 क्रम the delayed ref
	 * updates.
	 */
	min_items += 10;

	num_bytes = max_t(u64, num_bytes,
			  btrfs_calc_insert_metadata_size(fs_info, min_items));

	spin_lock(&sinfo->lock);
	spin_lock(&block_rsv->lock);

	block_rsv->size = min_t(u64, num_bytes, SZ_512M);

	अगर (block_rsv->reserved < block_rsv->size) अणु
		num_bytes = block_rsv->size - block_rsv->reserved;
		btrfs_space_info_update_bytes_may_use(fs_info, sinfo,
						      num_bytes);
		block_rsv->reserved = block_rsv->size;
	पूर्ण अन्यथा अगर (block_rsv->reserved > block_rsv->size) अणु
		num_bytes = block_rsv->reserved - block_rsv->size;
		btrfs_space_info_update_bytes_may_use(fs_info, sinfo,
						      -num_bytes);
		block_rsv->reserved = block_rsv->size;
		btrfs_try_granting_tickets(fs_info, sinfo);
	पूर्ण

	अगर (block_rsv->reserved == block_rsv->size)
		block_rsv->full = 1;
	अन्यथा
		block_rsv->full = 0;

	अगर (block_rsv->size >= sinfo->total_bytes)
		sinfo->क्रमce_alloc = CHUNK_ALLOC_FORCE;
	spin_unlock(&block_rsv->lock);
	spin_unlock(&sinfo->lock);
पूर्ण

व्योम btrfs_init_global_block_rsv(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_space_info *space_info;

	space_info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_SYSTEM);
	fs_info->chunk_block_rsv.space_info = space_info;

	space_info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_METADATA);
	fs_info->global_block_rsv.space_info = space_info;
	fs_info->trans_block_rsv.space_info = space_info;
	fs_info->empty_block_rsv.space_info = space_info;
	fs_info->delayed_block_rsv.space_info = space_info;
	fs_info->delayed_refs_rsv.space_info = space_info;

	/*
	 * Our various recovery options can leave us with शून्य roots, so check
	 * here and just bail beक्रमe we go dereferencing शून्यs everywhere.
	 */
	अगर (!fs_info->extent_root || !fs_info->csum_root ||
	    !fs_info->dev_root || !fs_info->chunk_root || !fs_info->tree_root)
		वापस;

	fs_info->extent_root->block_rsv = &fs_info->delayed_refs_rsv;
	fs_info->csum_root->block_rsv = &fs_info->delayed_refs_rsv;
	fs_info->dev_root->block_rsv = &fs_info->global_block_rsv;
	fs_info->tree_root->block_rsv = &fs_info->global_block_rsv;
	अगर (fs_info->quota_root)
		fs_info->quota_root->block_rsv = &fs_info->global_block_rsv;
	fs_info->chunk_root->block_rsv = &fs_info->chunk_block_rsv;

	btrfs_update_global_block_rsv(fs_info);
पूर्ण

व्योम btrfs_release_global_block_rsv(काष्ठा btrfs_fs_info *fs_info)
अणु
	btrfs_block_rsv_release(fs_info, &fs_info->global_block_rsv, (u64)-1,
				शून्य);
	WARN_ON(fs_info->trans_block_rsv.size > 0);
	WARN_ON(fs_info->trans_block_rsv.reserved > 0);
	WARN_ON(fs_info->chunk_block_rsv.size > 0);
	WARN_ON(fs_info->chunk_block_rsv.reserved > 0);
	WARN_ON(fs_info->delayed_block_rsv.size > 0);
	WARN_ON(fs_info->delayed_block_rsv.reserved > 0);
	WARN_ON(fs_info->delayed_refs_rsv.reserved > 0);
	WARN_ON(fs_info->delayed_refs_rsv.size > 0);
पूर्ण

अटल काष्ठा btrfs_block_rsv *get_block_rsv(
					स्थिर काष्ठा btrfs_trans_handle *trans,
					स्थिर काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_block_rsv *block_rsv = शून्य;

	अगर (test_bit(BTRFS_ROOT_SHAREABLE, &root->state) ||
	    (root == fs_info->csum_root && trans->adding_csums) ||
	    (root == fs_info->uuid_root))
		block_rsv = trans->block_rsv;

	अगर (!block_rsv)
		block_rsv = root->block_rsv;

	अगर (!block_rsv)
		block_rsv = &fs_info->empty_block_rsv;

	वापस block_rsv;
पूर्ण

काष्ठा btrfs_block_rsv *btrfs_use_block_rsv(काष्ठा btrfs_trans_handle *trans,
					    काष्ठा btrfs_root *root,
					    u32 blocksize)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_block_rsv *block_rsv;
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	पूर्णांक ret;
	bool global_updated = false;

	block_rsv = get_block_rsv(trans, root);

	अगर (unlikely(block_rsv->size == 0))
		जाओ try_reserve;
again:
	ret = btrfs_block_rsv_use_bytes(block_rsv, blocksize);
	अगर (!ret)
		वापस block_rsv;

	अगर (block_rsv->failfast)
		वापस ERR_PTR(ret);

	अगर (block_rsv->type == BTRFS_BLOCK_RSV_GLOBAL && !global_updated) अणु
		global_updated = true;
		btrfs_update_global_block_rsv(fs_info);
		जाओ again;
	पूर्ण

	/*
	 * The global reserve still exists to save us from ourselves, so करोn't
	 * warn_on अगर we are लघु on our delayed refs reserve.
	 */
	अगर (block_rsv->type != BTRFS_BLOCK_RSV_DELREFS &&
	    btrfs_test_opt(fs_info, ENOSPC_DEBUG)) अणु
		अटल DEFINE_RATELIMIT_STATE(_rs,
				DEFAULT_RATELIMIT_INTERVAL * 10,
				/*DEFAULT_RATELIMIT_BURST*/ 1);
		अगर (__ratelimit(&_rs))
			WARN(1, KERN_DEBUG
				"BTRFS: block rsv %d returned %d\n",
				block_rsv->type, ret);
	पूर्ण
try_reserve:
	ret = btrfs_reserve_metadata_bytes(root, block_rsv, blocksize,
					   BTRFS_RESERVE_NO_FLUSH);
	अगर (!ret)
		वापस block_rsv;
	/*
	 * If we couldn't reserve metadata bytes try and use some from
	 * the global reserve अगर its space type is the same as the global
	 * reservation.
	 */
	अगर (block_rsv->type != BTRFS_BLOCK_RSV_GLOBAL &&
	    block_rsv->space_info == global_rsv->space_info) अणु
		ret = btrfs_block_rsv_use_bytes(global_rsv, blocksize);
		अगर (!ret)
			वापस global_rsv;
	पूर्ण
	वापस ERR_PTR(ret);
पूर्ण
