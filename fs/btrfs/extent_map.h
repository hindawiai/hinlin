<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_EXTENT_MAP_H
#घोषणा BTRFS_EXTENT_MAP_H

#समावेश <linux/rbtree.h>
#समावेश <linux/refcount.h>

#घोषणा EXTENT_MAP_LAST_BYTE ((u64)-4)
#घोषणा EXTENT_MAP_HOLE ((u64)-3)
#घोषणा EXTENT_MAP_INLINE ((u64)-2)
/* used only during fiemap calls */
#घोषणा EXTENT_MAP_DELALLOC ((u64)-1)

/* bits क्रम the extent_map::flags field */
क्रमागत अणु
	/* this entry not yet on disk, करोn't मुक्त it */
	EXTENT_FLAG_PINNED,
	EXTENT_FLAG_COMPRESSED,
	/* pre-allocated extent */
	EXTENT_FLAG_PREALLOC,
	/* Logging this extent */
	EXTENT_FLAG_LOGGING,
	/* Filling in a pपुनः_स्मृतिated extent */
	EXTENT_FLAG_FILLING,
	/* fileप्रणाली extent mapping type */
	EXTENT_FLAG_FS_MAPPING,
पूर्ण;

काष्ठा extent_map अणु
	काष्ठा rb_node rb_node;

	/* all of these are in bytes */
	u64 start;
	u64 len;
	u64 mod_start;
	u64 mod_len;
	u64 orig_start;
	u64 orig_block_len;
	u64 ram_bytes;
	u64 block_start;
	u64 block_len;
	u64 generation;
	अचिन्हित दीर्घ flags;
	/* Used क्रम chunk mappings, flag EXTENT_FLAG_FS_MAPPING must be set */
	काष्ठा map_lookup *map_lookup;
	refcount_t refs;
	अचिन्हित पूर्णांक compress_type;
	काष्ठा list_head list;
पूर्ण;

काष्ठा extent_map_tree अणु
	काष्ठा rb_root_cached map;
	काष्ठा list_head modअगरied_extents;
	rwlock_t lock;
पूर्ण;

अटल अंतरभूत पूर्णांक extent_map_in_tree(स्थिर काष्ठा extent_map *em)
अणु
	वापस !RB_EMPTY_NODE(&em->rb_node);
पूर्ण

अटल अंतरभूत u64 extent_map_end(काष्ठा extent_map *em)
अणु
	अगर (em->start + em->len < em->start)
		वापस (u64)-1;
	वापस em->start + em->len;
पूर्ण

अटल अंतरभूत u64 extent_map_block_end(काष्ठा extent_map *em)
अणु
	अगर (em->block_start + em->block_len < em->block_start)
		वापस (u64)-1;
	वापस em->block_start + em->block_len;
पूर्ण

व्योम extent_map_tree_init(काष्ठा extent_map_tree *tree);
काष्ठा extent_map *lookup_extent_mapping(काष्ठा extent_map_tree *tree,
					 u64 start, u64 len);
पूर्णांक add_extent_mapping(काष्ठा extent_map_tree *tree,
		       काष्ठा extent_map *em, पूर्णांक modअगरied);
व्योम हटाओ_extent_mapping(काष्ठा extent_map_tree *tree, काष्ठा extent_map *em);
व्योम replace_extent_mapping(काष्ठा extent_map_tree *tree,
			    काष्ठा extent_map *cur,
			    काष्ठा extent_map *new,
			    पूर्णांक modअगरied);

काष्ठा extent_map *alloc_extent_map(व्योम);
व्योम मुक्त_extent_map(काष्ठा extent_map *em);
पूर्णांक __init extent_map_init(व्योम);
व्योम __cold extent_map_निकास(व्योम);
पूर्णांक unpin_extent_cache(काष्ठा extent_map_tree *tree, u64 start, u64 len, u64 gen);
व्योम clear_em_logging(काष्ठा extent_map_tree *tree, काष्ठा extent_map *em);
काष्ठा extent_map *search_extent_mapping(काष्ठा extent_map_tree *tree,
					 u64 start, u64 len);
पूर्णांक btrfs_add_extent_mapping(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा extent_map_tree *em_tree,
			     काष्ठा extent_map **em_in, u64 start, u64 len);

#पूर्ण_अगर
