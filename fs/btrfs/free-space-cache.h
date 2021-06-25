<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2009 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_FREE_SPACE_CACHE_H
#घोषणा BTRFS_FREE_SPACE_CACHE_H

/*
 * This is the trim state of an extent or biपंचांगap.
 *
 * BTRFS_TRIM_STATE_TRIMMING is special and used to मुख्यtain the state of a
 * biपंचांगap as we may need several trims to fully trim a single biपंचांगap entry.
 * This is reset should any मुक्त space other than trimmed space be added to the
 * biपंचांगap.
 */
क्रमागत btrfs_trim_state अणु
	BTRFS_TRIM_STATE_UNTRIMMED,
	BTRFS_TRIM_STATE_TRIMMED,
	BTRFS_TRIM_STATE_TRIMMING,
पूर्ण;

काष्ठा btrfs_मुक्त_space अणु
	काष्ठा rb_node offset_index;
	u64 offset;
	u64 bytes;
	u64 max_extent_size;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा list_head list;
	क्रमागत btrfs_trim_state trim_state;
	s32 biपंचांगap_extents;
पूर्ण;

अटल अंतरभूत bool btrfs_मुक्त_space_trimmed(काष्ठा btrfs_मुक्त_space *info)
अणु
	वापस (info->trim_state == BTRFS_TRIM_STATE_TRIMMED);
पूर्ण

अटल अंतरभूत bool btrfs_मुक्त_space_trimming_biपंचांगap(
					    काष्ठा btrfs_मुक्त_space *info)
अणु
	वापस (info->trim_state == BTRFS_TRIM_STATE_TRIMMING);
पूर्ण

काष्ठा btrfs_मुक्त_space_ctl अणु
	spinlock_t tree_lock;
	काष्ठा rb_root मुक्त_space_offset;
	u64 मुक्त_space;
	पूर्णांक extents_thresh;
	पूर्णांक मुक्त_extents;
	पूर्णांक total_biपंचांगaps;
	पूर्णांक unit;
	u64 start;
	s32 discardable_extents[BTRFS_STAT_NR_ENTRIES];
	s64 discardable_bytes[BTRFS_STAT_NR_ENTRIES];
	स्थिर काष्ठा btrfs_मुक्त_space_op *op;
	व्योम *निजी;
	काष्ठा mutex cache_ग_लिखोout_mutex;
	काष्ठा list_head trimming_ranges;
पूर्ण;

काष्ठा btrfs_मुक्त_space_op अणु
	bool (*use_biपंचांगap)(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			   काष्ठा btrfs_मुक्त_space *info);
पूर्ण;

काष्ठा btrfs_io_ctl अणु
	व्योम *cur, *orig;
	काष्ठा page *page;
	काष्ठा page **pages;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा inode *inode;
	अचिन्हित दीर्घ size;
	पूर्णांक index;
	पूर्णांक num_pages;
	पूर्णांक entries;
	पूर्णांक biपंचांगaps;
पूर्ण;

काष्ठा inode *lookup_मुक्त_space_inode(काष्ठा btrfs_block_group *block_group,
		काष्ठा btrfs_path *path);
पूर्णांक create_मुक्त_space_inode(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_block_group *block_group,
			    काष्ठा btrfs_path *path);
पूर्णांक btrfs_हटाओ_मुक्त_space_inode(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा inode *inode,
				  काष्ठा btrfs_block_group *block_group);

पूर्णांक btrfs_check_trunc_cache_मुक्त_space(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा btrfs_block_rsv *rsv);
पूर्णांक btrfs_truncate_मुक्त_space_cache(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_block_group *block_group,
				    काष्ठा inode *inode);
पूर्णांक load_मुक्त_space_cache(काष्ठा btrfs_block_group *block_group);
पूर्णांक btrfs_रुको_cache_io(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_block_group *block_group,
			काष्ठा btrfs_path *path);
पूर्णांक btrfs_ग_लिखो_out_cache(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_block_group *block_group,
			  काष्ठा btrfs_path *path);

व्योम btrfs_init_मुक्त_space_ctl(काष्ठा btrfs_block_group *block_group,
			       काष्ठा btrfs_मुक्त_space_ctl *ctl);
पूर्णांक __btrfs_add_मुक्त_space(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_मुक्त_space_ctl *ctl,
			   u64 bytenr, u64 size,
			   क्रमागत btrfs_trim_state trim_state);
पूर्णांक btrfs_add_मुक्त_space(काष्ठा btrfs_block_group *block_group,
			 u64 bytenr, u64 size);
पूर्णांक btrfs_add_मुक्त_space_unused(काष्ठा btrfs_block_group *block_group,
				u64 bytenr, u64 size);
पूर्णांक btrfs_add_मुक्त_space_async_trimmed(काष्ठा btrfs_block_group *block_group,
				       u64 bytenr, u64 size);
पूर्णांक btrfs_हटाओ_मुक्त_space(काष्ठा btrfs_block_group *block_group,
			    u64 bytenr, u64 size);
व्योम __btrfs_हटाओ_मुक्त_space_cache(काष्ठा btrfs_मुक्त_space_ctl *ctl);
व्योम btrfs_हटाओ_मुक्त_space_cache(काष्ठा btrfs_block_group *block_group);
bool btrfs_is_मुक्त_space_trimmed(काष्ठा btrfs_block_group *block_group);
u64 btrfs_find_space_क्रम_alloc(काष्ठा btrfs_block_group *block_group,
			       u64 offset, u64 bytes, u64 empty_size,
			       u64 *max_extent_size);
व्योम btrfs_dump_मुक्त_space(काष्ठा btrfs_block_group *block_group,
			   u64 bytes);
पूर्णांक btrfs_find_space_cluster(काष्ठा btrfs_block_group *block_group,
			     काष्ठा btrfs_मुक्त_cluster *cluster,
			     u64 offset, u64 bytes, u64 empty_size);
व्योम btrfs_init_मुक्त_cluster(काष्ठा btrfs_मुक्त_cluster *cluster);
u64 btrfs_alloc_from_cluster(काष्ठा btrfs_block_group *block_group,
			     काष्ठा btrfs_मुक्त_cluster *cluster, u64 bytes,
			     u64 min_start, u64 *max_extent_size);
व्योम btrfs_वापस_cluster_to_मुक्त_space(
			       काष्ठा btrfs_block_group *block_group,
			       काष्ठा btrfs_मुक्त_cluster *cluster);
पूर्णांक btrfs_trim_block_group(काष्ठा btrfs_block_group *block_group,
			   u64 *trimmed, u64 start, u64 end, u64 minlen);
पूर्णांक btrfs_trim_block_group_extents(काष्ठा btrfs_block_group *block_group,
				   u64 *trimmed, u64 start, u64 end, u64 minlen,
				   bool async);
पूर्णांक btrfs_trim_block_group_biपंचांगaps(काष्ठा btrfs_block_group *block_group,
				   u64 *trimmed, u64 start, u64 end, u64 minlen,
				   u64 maxlen, bool async);

bool btrfs_मुक्त_space_cache_v1_active(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_set_मुक्त_space_cache_v1_active(काष्ठा btrfs_fs_info *fs_info, bool active);
/* Support functions क्रम running our sanity tests */
#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
पूर्णांक test_add_मुक्त_space_entry(काष्ठा btrfs_block_group *cache,
			      u64 offset, u64 bytes, bool biपंचांगap);
पूर्णांक test_check_exists(काष्ठा btrfs_block_group *cache, u64 offset, u64 bytes);
#पूर्ण_अगर

#पूर्ण_अगर
