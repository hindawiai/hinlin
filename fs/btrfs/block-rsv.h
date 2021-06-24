<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_BLOCK_RSV_H
#घोषणा BTRFS_BLOCK_RSV_H

काष्ठा btrfs_trans_handle;
क्रमागत btrfs_reserve_flush_क्रमागत;

/*
 * Types of block reserves
 */
क्रमागत अणु
	BTRFS_BLOCK_RSV_GLOBAL,
	BTRFS_BLOCK_RSV_DELALLOC,
	BTRFS_BLOCK_RSV_TRANS,
	BTRFS_BLOCK_RSV_CHUNK,
	BTRFS_BLOCK_RSV_DELOPS,
	BTRFS_BLOCK_RSV_DELREFS,
	BTRFS_BLOCK_RSV_EMPTY,
	BTRFS_BLOCK_RSV_TEMP,
पूर्ण;

काष्ठा btrfs_block_rsv अणु
	u64 size;
	u64 reserved;
	काष्ठा btrfs_space_info *space_info;
	spinlock_t lock;
	अचिन्हित लघु full;
	अचिन्हित लघु type;
	अचिन्हित लघु failfast;

	/*
	 * Qgroup equivalent क्रम @size @reserved
	 *
	 * Unlike normal @size/@reserved क्रम inode rsv, qgroup करोesn't care
	 * about things like csum size nor how many tree blocks it will need to
	 * reserve.
	 *
	 * Qgroup cares more about net change of the extent usage.
	 *
	 * So क्रम one newly inserted file extent, in worst हाल it will cause
	 * leaf split and level increase, nodesize क्रम each file extent is
	 * alपढ़ोy too much.
	 *
	 * In लघु, qgroup_size/reserved is the upper limit of possible needed
	 * qgroup metadata reservation.
	 */
	u64 qgroup_rsv_size;
	u64 qgroup_rsv_reserved;
पूर्ण;

व्योम btrfs_init_block_rsv(काष्ठा btrfs_block_rsv *rsv, अचिन्हित लघु type);
काष्ठा btrfs_block_rsv *btrfs_alloc_block_rsv(काष्ठा btrfs_fs_info *fs_info,
					      अचिन्हित लघु type);
व्योम btrfs_init_metadata_block_rsv(काष्ठा btrfs_fs_info *fs_info,
				   काष्ठा btrfs_block_rsv *rsv,
				   अचिन्हित लघु type);
व्योम btrfs_मुक्त_block_rsv(काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा btrfs_block_rsv *rsv);
पूर्णांक btrfs_block_rsv_add(काष्ठा btrfs_root *root,
			काष्ठा btrfs_block_rsv *block_rsv, u64 num_bytes,
			क्रमागत btrfs_reserve_flush_क्रमागत flush);
पूर्णांक btrfs_block_rsv_check(काष्ठा btrfs_block_rsv *block_rsv, पूर्णांक min_factor);
पूर्णांक btrfs_block_rsv_refill(काष्ठा btrfs_root *root,
			   काष्ठा btrfs_block_rsv *block_rsv, u64 min_reserved,
			   क्रमागत btrfs_reserve_flush_क्रमागत flush);
पूर्णांक btrfs_block_rsv_migrate(काष्ठा btrfs_block_rsv *src_rsv,
			    काष्ठा btrfs_block_rsv *dst_rsv, u64 num_bytes,
			    bool update_size);
पूर्णांक btrfs_block_rsv_use_bytes(काष्ठा btrfs_block_rsv *block_rsv, u64 num_bytes);
पूर्णांक btrfs_cond_migrate_bytes(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा btrfs_block_rsv *dest, u64 num_bytes,
			     पूर्णांक min_factor);
व्योम btrfs_block_rsv_add_bytes(काष्ठा btrfs_block_rsv *block_rsv,
			       u64 num_bytes, bool update_size);
u64 btrfs_block_rsv_release(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा btrfs_block_rsv *block_rsv,
			      u64 num_bytes, u64 *qgroup_to_release);
व्योम btrfs_update_global_block_rsv(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_init_global_block_rsv(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_release_global_block_rsv(काष्ठा btrfs_fs_info *fs_info);
काष्ठा btrfs_block_rsv *btrfs_use_block_rsv(काष्ठा btrfs_trans_handle *trans,
					    काष्ठा btrfs_root *root,
					    u32 blocksize);
अटल अंतरभूत व्योम btrfs_unuse_block_rsv(काष्ठा btrfs_fs_info *fs_info,
					 काष्ठा btrfs_block_rsv *block_rsv,
					 u32 blocksize)
अणु
	btrfs_block_rsv_add_bytes(block_rsv, blocksize, false);
	btrfs_block_rsv_release(fs_info, block_rsv, 0, शून्य);
पूर्ण

#पूर्ण_अगर /* BTRFS_BLOCK_RSV_H */
