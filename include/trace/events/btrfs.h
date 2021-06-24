<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM btrfs

#अगर !defined(_TRACE_BTRFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_BTRFS_H

#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/mmflags.h>

काष्ठा btrfs_root;
काष्ठा btrfs_fs_info;
काष्ठा btrfs_inode;
काष्ठा extent_map;
काष्ठा btrfs_file_extent_item;
काष्ठा btrfs_ordered_extent;
काष्ठा btrfs_delayed_ref_node;
काष्ठा btrfs_delayed_tree_ref;
काष्ठा btrfs_delayed_data_ref;
काष्ठा btrfs_delayed_ref_head;
काष्ठा btrfs_block_group;
काष्ठा btrfs_मुक्त_cluster;
काष्ठा map_lookup;
काष्ठा extent_buffer;
काष्ठा btrfs_work;
काष्ठा __btrfs_workqueue;
काष्ठा btrfs_qgroup_extent_record;
काष्ठा btrfs_qgroup;
काष्ठा extent_io_tree;
काष्ठा prelim_ref;
काष्ठा btrfs_space_info;

#घोषणा show_ref_type(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु BTRFS_TREE_BLOCK_REF_KEY, 	"TREE_BLOCK_REF" पूर्ण,	\
		अणु BTRFS_EXTENT_DATA_REF_KEY, 	"EXTENT_DATA_REF" पूर्ण,	\
		अणु BTRFS_EXTENT_REF_V0_KEY, 	"EXTENT_REF_V0" पूर्ण,	\
		अणु BTRFS_SHARED_BLOCK_REF_KEY, 	"SHARED_BLOCK_REF" पूर्ण,	\
		अणु BTRFS_SHARED_DATA_REF_KEY, 	"SHARED_DATA_REF" पूर्ण)

#घोषणा __show_root_type(obj)						\
	__prपूर्णांक_symbolic_u64(obj,					\
		अणु BTRFS_ROOT_TREE_OBJECTID, 	"ROOT_TREE"	पूर्ण,	\
		अणु BTRFS_EXTENT_TREE_OBJECTID, 	"EXTENT_TREE"	पूर्ण,	\
		अणु BTRFS_CHUNK_TREE_OBJECTID, 	"CHUNK_TREE"	पूर्ण,	\
		अणु BTRFS_DEV_TREE_OBJECTID, 	"DEV_TREE"	पूर्ण,	\
		अणु BTRFS_FS_TREE_OBJECTID, 	"FS_TREE"	पूर्ण,	\
		अणु BTRFS_ROOT_TREE_सूची_OBJECTID, "ROOT_TREE_DIR"	पूर्ण,	\
		अणु BTRFS_CSUM_TREE_OBJECTID, 	"CSUM_TREE"	पूर्ण,	\
		अणु BTRFS_TREE_LOG_OBJECTID,	"TREE_LOG"	पूर्ण,	\
		अणु BTRFS_QUOTA_TREE_OBJECTID,	"QUOTA_TREE"	पूर्ण,	\
		अणु BTRFS_TREE_RELOC_OBJECTID,	"TREE_RELOC"	पूर्ण,	\
		अणु BTRFS_UUID_TREE_OBJECTID,	"UUID_TREE"	पूर्ण,	\
		अणु BTRFS_FREE_SPACE_TREE_OBJECTID, "FREE_SPACE_TREE" पूर्ण,	\
		अणु BTRFS_DATA_RELOC_TREE_OBJECTID, "DATA_RELOC_TREE" पूर्ण)

#घोषणा show_root_type(obj)						\
	obj, ((obj >= BTRFS_DATA_RELOC_TREE_OBJECTID) ||		\
	      (obj >= BTRFS_ROOT_TREE_OBJECTID &&			\
	       obj <= BTRFS_QUOTA_TREE_OBJECTID)) ? __show_root_type(obj) : "-"

#घोषणा FLUSH_ACTIONS								\
	EM( BTRFS_RESERVE_NO_FLUSH,		"BTRFS_RESERVE_NO_FLUSH")	\
	EM( BTRFS_RESERVE_FLUSH_LIMIT,		"BTRFS_RESERVE_FLUSH_LIMIT")	\
	EM( BTRFS_RESERVE_FLUSH_ALL,		"BTRFS_RESERVE_FLUSH_ALL")	\
	EMe(BTRFS_RESERVE_FLUSH_ALL_STEAL,	"BTRFS_RESERVE_FLUSH_ALL_STEAL")

#घोषणा FI_TYPES							\
	EM( BTRFS_खाता_EXTENT_INLINE,		"INLINE")		\
	EM( BTRFS_खाता_EXTENT_REG,		"REG")			\
	EMe(BTRFS_खाता_EXTENT_PREALLOC,		"PREALLOC")

#घोषणा QGROUP_RSV_TYPES						\
	EM( BTRFS_QGROUP_RSV_DATA,		"DATA")			\
	EM( BTRFS_QGROUP_RSV_META_PERTRANS,	"META_PERTRANS")	\
	EMe(BTRFS_QGROUP_RSV_META_PREALLOC,	"META_PREALLOC")

#घोषणा IO_TREE_OWNER						    \
	EM( IO_TREE_FS_PINNED_EXTENTS, 	  "PINNED_EXTENTS")	    \
	EM( IO_TREE_FS_EXCLUDED_EXTENTS,  "EXCLUDED_EXTENTS")	    \
	EM( IO_TREE_BTREE_INODE_IO,	  "BTREE_INODE_IO")	    \
	EM( IO_TREE_INODE_IO,		  "INODE_IO")		    \
	EM( IO_TREE_INODE_IO_FAILURE,	  "INODE_IO_FAILURE")	    \
	EM( IO_TREE_RELOC_BLOCKS,	  "RELOC_BLOCKS")	    \
	EM( IO_TREE_TRANS_सूचीTY_PAGES,	  "TRANS_DIRTY_PAGES")      \
	EM( IO_TREE_ROOT_सूचीTY_LOG_PAGES, "ROOT_DIRTY_LOG_PAGES")   \
	EM( IO_TREE_INODE_खाता_EXTENT,	  "INODE_FILE_EXTENT")      \
	EM( IO_TREE_LOG_CSUM_RANGE,	  "LOG_CSUM_RANGE")         \
	EMe(IO_TREE_SELFTEST,		  "SELFTEST")

#घोषणा FLUSH_STATES							\
	EM( FLUSH_DELAYED_ITEMS_NR,	"FLUSH_DELAYED_ITEMS_NR")	\
	EM( FLUSH_DELAYED_ITEMS,	"FLUSH_DELAYED_ITEMS")		\
	EM( FLUSH_DELALLOC,		"FLUSH_DELALLOC")		\
	EM( FLUSH_DELALLOC_WAIT,	"FLUSH_DELALLOC_WAIT")		\
	EM( FLUSH_DELAYED_REFS_NR,	"FLUSH_DELAYED_REFS_NR")	\
	EM( FLUSH_DELAYED_REFS,		"FLUSH_ELAYED_REFS")		\
	EM( ALLOC_CHUNK,		"ALLOC_CHUNK")			\
	EM( ALLOC_CHUNK_FORCE,		"ALLOC_CHUNK_FORCE")		\
	EM( RUN_DELAYED_IPUTS,		"RUN_DELAYED_IPUTS")		\
	EM( COMMIT_TRANS,		"COMMIT_TRANS")			\
	EMe(FORCE_COMMIT_TRANS,		"FORCE_COMMIT_TRANS")

/*
 * First define the क्रमागतs in the above macros to be exported to userspace via
 * TRACE_DEFINE_ENUM().
 */

#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

FLUSH_ACTIONS
FI_TYPES
QGROUP_RSV_TYPES
IO_TREE_OWNER
FLUSH_STATES

/*
 * Now redefine the EM and EMe macros to map the क्रमागतs to the strings that will
 * be prपूर्णांकed in the output
 */

#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)        अणुa, bपूर्ण,
#घोषणा EMe(a, b)       अणुa, bपूर्ण


#घोषणा BTRFS_GROUP_FLAGS	\
	अणु BTRFS_BLOCK_GROUP_DATA,	"DATA"पूर्ण,	\
	अणु BTRFS_BLOCK_GROUP_SYSTEM,	"SYSTEM"पूर्ण,	\
	अणु BTRFS_BLOCK_GROUP_METADATA,	"METADATA"पूर्ण,	\
	अणु BTRFS_BLOCK_GROUP_RAID0,	"RAID0"पूर्ण, 	\
	अणु BTRFS_BLOCK_GROUP_RAID1,	"RAID1"पूर्ण, 	\
	अणु BTRFS_BLOCK_GROUP_DUP,	"DUP"पूर्ण, 	\
	अणु BTRFS_BLOCK_GROUP_RAID10,	"RAID10"पूर्ण, 	\
	अणु BTRFS_BLOCK_GROUP_RAID5,	"RAID5"पूर्ण,	\
	अणु BTRFS_BLOCK_GROUP_RAID6,	"RAID6"पूर्ण

#घोषणा EXTENT_FLAGS						\
	अणु EXTENT_सूचीTY,			"DIRTY"पूर्ण,		\
	अणु EXTENT_UPTODATE,		"UPTODATE"पूर्ण,		\
	अणु EXTENT_LOCKED,		"LOCKED"पूर्ण,		\
	अणु EXTENT_NEW,			"NEW"पूर्ण,			\
	अणु EXTENT_DELALLOC,		"DELALLOC"पूर्ण,		\
	अणु EXTENT_DEFRAG,		"DEFRAG"पूर्ण,		\
	अणु EXTENT_BOUNDARY,		"BOUNDARY"पूर्ण,		\
	अणु EXTENT_NODATASUM,		"NODATASUM"पूर्ण,		\
	अणु EXTENT_CLEAR_META_RESV,	"CLEAR_META_RESV"पूर्ण,	\
	अणु EXTENT_NEED_WAIT,		"NEED_WAIT"पूर्ण,		\
	अणु EXTENT_DAMAGED,		"DAMAGED"पूर्ण,		\
	अणु EXTENT_NORESERVE,		"NORESERVE"पूर्ण,		\
	अणु EXTENT_QGROUP_RESERVED,	"QGROUP_RESERVED"पूर्ण,	\
	अणु EXTENT_CLEAR_DATA_RESV,	"CLEAR_DATA_RESV"पूर्ण,	\
	अणु EXTENT_DELALLOC_NEW,		"DELALLOC_NEW"पूर्ण

#घोषणा BTRFS_FSID_SIZE 16
#घोषणा TP_STRUCT__entry_fsid __array(u8, fsid, BTRFS_FSID_SIZE)

#घोषणा TP_fast_assign_fsid(fs_info)					\
(अणु									\
	अगर (fs_info)							\
		स_नकल(__entry->fsid, fs_info->fs_devices->fsid,	\
		       BTRFS_FSID_SIZE);				\
	अन्यथा								\
		स_रखो(__entry->fsid, 0, BTRFS_FSID_SIZE);		\
पूर्ण)

#घोषणा TP_STRUCT__entry_btrfs(args...)					\
	TP_STRUCT__entry(						\
		TP_STRUCT__entry_fsid					\
		args)
#घोषणा TP_fast_assign_btrfs(fs_info, args...)				\
	TP_fast_assign(							\
		TP_fast_assign_fsid(fs_info);				\
		args)
#घोषणा TP_prपूर्णांकk_btrfs(fmt, args...) \
	TP_prपूर्णांकk("%pU: " fmt, __entry->fsid, args)

TRACE_EVENT(btrfs_transaction_commit,

	TP_PROTO(स्थिर काष्ठा btrfs_root *root),

	TP_ARGS(root),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  generation		)
		__field(	u64,  root_objectid		)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->generation	= root->fs_info->generation;
		__entry->root_objectid	= root->root_key.objectid;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) gen=%llu",
		  show_root_type(__entry->root_objectid),
		  __entry->generation)
);

DECLARE_EVENT_CLASS(btrfs__inode,

	TP_PROTO(स्थिर काष्ठा inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  ino			)
		__field(	u64,  blocks			)
		__field(	u64,  disk_i_size		)
		__field(	u64,  generation		)
		__field(	u64,  last_trans		)
		__field(	u64,  logged_trans		)
		__field(	u64,  root_objectid		)
	),

	TP_fast_assign_btrfs(btrfs_sb(inode->i_sb),
		__entry->ino	= btrfs_ino(BTRFS_I(inode));
		__entry->blocks	= inode->i_blocks;
		__entry->disk_i_size  = BTRFS_I(inode)->disk_i_size;
		__entry->generation = BTRFS_I(inode)->generation;
		__entry->last_trans = BTRFS_I(inode)->last_trans;
		__entry->logged_trans = BTRFS_I(inode)->logged_trans;
		__entry->root_objectid =
				BTRFS_I(inode)->root->root_key.objectid;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) gen=%llu ino=%llu blocks=%llu "
		  "disk_i_size=%llu last_trans=%llu logged_trans=%llu",
		  show_root_type(__entry->root_objectid),
		  __entry->generation,
		  __entry->ino,
		  __entry->blocks,
		  __entry->disk_i_size,
		  __entry->last_trans,
		  __entry->logged_trans)
);

DEFINE_EVENT(btrfs__inode, btrfs_inode_new,

	TP_PROTO(स्थिर काष्ठा inode *inode),

	TP_ARGS(inode)
);

DEFINE_EVENT(btrfs__inode, btrfs_inode_request,

	TP_PROTO(स्थिर काष्ठा inode *inode),

	TP_ARGS(inode)
);

DEFINE_EVENT(btrfs__inode, btrfs_inode_evict,

	TP_PROTO(स्थिर काष्ठा inode *inode),

	TP_ARGS(inode)
);

#घोषणा __show_map_type(type)						\
	__prपूर्णांक_symbolic_u64(type,					\
		अणु EXTENT_MAP_LAST_BYTE, "LAST_BYTE" 	पूर्ण,		\
		अणु EXTENT_MAP_HOLE, 	"HOLE" 		पूर्ण,		\
		अणु EXTENT_MAP_INLINE, 	"INLINE" 	पूर्ण,		\
		अणु EXTENT_MAP_DELALLOC,	"DELALLOC" 	पूर्ण)

#घोषणा show_map_type(type)			\
	type, (type >= EXTENT_MAP_LAST_BYTE) ? "-" :  __show_map_type(type)

#घोषणा show_map_flags(flag)						\
	__prपूर्णांक_flags(flag, "|",					\
		अणु (1 << EXTENT_FLAG_PINNED), 		"PINNED" 	पूर्ण,\
		अणु (1 << EXTENT_FLAG_COMPRESSED), 	"COMPRESSED" 	पूर्ण,\
		अणु (1 << EXTENT_FLAG_PREALLOC), 		"PREALLOC" 	पूर्ण,\
		अणु (1 << EXTENT_FLAG_LOGGING),	 	"LOGGING" 	पूर्ण,\
		अणु (1 << EXTENT_FLAG_FILLING),	 	"FILLING" 	पूर्ण,\
		अणु (1 << EXTENT_FLAG_FS_MAPPING),	"FS_MAPPING"	पूर्ण)

TRACE_EVENT_CONDITION(btrfs_get_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_root *root, स्थिर काष्ठा btrfs_inode *inode,
		 स्थिर काष्ठा extent_map *map),

	TP_ARGS(root, inode, map),

	TP_CONDITION(map),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  root_objectid	)
		__field(	u64,  ino		)
		__field(	u64,  start		)
		__field(	u64,  len		)
		__field(	u64,  orig_start	)
		__field(	u64,  block_start	)
		__field(	u64,  block_len		)
		__field(	अचिन्हित दीर्घ,  flags	)
		__field(	पूर्णांक,  refs		)
		__field(	अचिन्हित पूर्णांक,  compress_type	)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->root_objectid	= root->root_key.objectid;
		__entry->ino		= btrfs_ino(inode);
		__entry->start		= map->start;
		__entry->len		= map->len;
		__entry->orig_start	= map->orig_start;
		__entry->block_start	= map->block_start;
		__entry->block_len	= map->block_len;
		__entry->flags		= map->flags;
		__entry->refs		= refcount_पढ़ो(&map->refs);
		__entry->compress_type	= map->compress_type;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) ino=%llu start=%llu len=%llu "
		  "orig_start=%llu block_start=%llu(%s) "
		  "block_len=%llu flags=%s refs=%u "
		  "compress_type=%u",
		  show_root_type(__entry->root_objectid),
		  __entry->ino,
		  __entry->start,
		  __entry->len,
		  __entry->orig_start,
		  show_map_type(__entry->block_start),
		  __entry->block_len,
		  show_map_flags(__entry->flags),
		  __entry->refs, __entry->compress_type)
);

TRACE_EVENT(btrfs_handle_em_exist,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		स्थिर काष्ठा extent_map *existing, स्थिर काष्ठा extent_map *map,
		u64 start, u64 len),

	TP_ARGS(fs_info, existing, map, start, len),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  e_start		)
		__field(	u64,  e_len		)
		__field(	u64,  map_start		)
		__field(	u64,  map_len		)
		__field(	u64,  start		)
		__field(	u64,  len		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->e_start	= existing->start;
		__entry->e_len		= existing->len;
		__entry->map_start	= map->start;
		__entry->map_len	= map->len;
		__entry->start		= start;
		__entry->len		= len;
	),

	TP_prपूर्णांकk_btrfs("start=%llu len=%llu "
		  "existing(start=%llu len=%llu) "
		  "em(start=%llu len=%llu)",
		  __entry->start,
		  __entry->len,
		  __entry->e_start,
		  __entry->e_len,
		  __entry->map_start,
		  __entry->map_len)
);

/* file extent item */
DECLARE_EVENT_CLASS(btrfs__file_extent_item_regular,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *bi, स्थिर काष्ठा extent_buffer *l,
		 स्थिर काष्ठा btrfs_file_extent_item *fi, u64 start),

	TP_ARGS(bi, l, fi, start),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	root_obj	)
		__field(	u64,	ino		)
		__field(	loff_t,	isize		)
		__field(	u64,	disk_isize	)
		__field(	u64,	num_bytes	)
		__field(	u64,	ram_bytes	)
		__field(	u64,	disk_bytenr	)
		__field(	u64,	disk_num_bytes	)
		__field(	u64,	extent_offset	)
		__field(	u8,	extent_type	)
		__field(	u8,	compression	)
		__field(	u64,	extent_start	)
		__field(	u64,	extent_end	)
	),

	TP_fast_assign_btrfs(bi->root->fs_info,
		__entry->root_obj	= bi->root->root_key.objectid;
		__entry->ino		= btrfs_ino(bi);
		__entry->isize		= bi->vfs_inode.i_size;
		__entry->disk_isize	= bi->disk_i_size;
		__entry->num_bytes	= btrfs_file_extent_num_bytes(l, fi);
		__entry->ram_bytes	= btrfs_file_extent_ram_bytes(l, fi);
		__entry->disk_bytenr	= btrfs_file_extent_disk_bytenr(l, fi);
		__entry->disk_num_bytes	= btrfs_file_extent_disk_num_bytes(l, fi);
		__entry->extent_offset	= btrfs_file_extent_offset(l, fi);
		__entry->extent_type	= btrfs_file_extent_type(l, fi);
		__entry->compression	= btrfs_file_extent_compression(l, fi);
		__entry->extent_start	= start;
		__entry->extent_end	= (start + __entry->num_bytes);
	),

	TP_prपूर्णांकk_btrfs(
		"root=%llu(%s) inode=%llu size=%llu disk_isize=%llu "
		"file extent range=[%llu %llu] "
		"(num_bytes=%llu ram_bytes=%llu disk_bytenr=%llu "
		"disk_num_bytes=%llu extent_offset=%llu type=%s "
		"compression=%u",
		show_root_type(__entry->root_obj), __entry->ino,
		__entry->isize,
		__entry->disk_isize, __entry->extent_start,
		__entry->extent_end, __entry->num_bytes, __entry->ram_bytes,
		__entry->disk_bytenr, __entry->disk_num_bytes,
		__entry->extent_offset, __prपूर्णांक_symbolic(__entry->extent_type, FI_TYPES),
		__entry->compression)
);

DECLARE_EVENT_CLASS(
	btrfs__file_extent_item_अंतरभूत,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *bi, स्थिर काष्ठा extent_buffer *l,
		 स्थिर काष्ठा btrfs_file_extent_item *fi, पूर्णांक slot, u64 start),

	TP_ARGS(bi, l, fi, slot,  start),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	root_obj	)
		__field(	u64,	ino		)
		__field(	loff_t,	isize		)
		__field(	u64,	disk_isize	)
		__field(	u8,	extent_type	)
		__field(	u8,	compression	)
		__field(	u64,	extent_start	)
		__field(	u64,	extent_end	)
	),

	TP_fast_assign_btrfs(
		bi->root->fs_info,
		__entry->root_obj	= bi->root->root_key.objectid;
		__entry->ino		= btrfs_ino(bi);
		__entry->isize		= bi->vfs_inode.i_size;
		__entry->disk_isize	= bi->disk_i_size;
		__entry->extent_type	= btrfs_file_extent_type(l, fi);
		__entry->compression	= btrfs_file_extent_compression(l, fi);
		__entry->extent_start	= start;
		__entry->extent_end	= (start + btrfs_file_extent_ram_bytes(l, fi));
	),

	TP_prपूर्णांकk_btrfs(
		"root=%llu(%s) inode=%llu size=%llu disk_isize=%llu "
		"file extent range=[%llu %llu] "
		"extent_type=%s compression=%u",
		show_root_type(__entry->root_obj), __entry->ino, __entry->isize,
		__entry->disk_isize, __entry->extent_start,
		__entry->extent_end, __prपूर्णांक_symbolic(__entry->extent_type, FI_TYPES),
		__entry->compression)
);

DEFINE_EVENT(
	btrfs__file_extent_item_regular, btrfs_get_extent_show_fi_regular,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *bi, स्थिर काष्ठा extent_buffer *l,
		 स्थिर काष्ठा btrfs_file_extent_item *fi, u64 start),

	TP_ARGS(bi, l, fi, start)
);

DEFINE_EVENT(
	btrfs__file_extent_item_regular, btrfs_truncate_show_fi_regular,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *bi, स्थिर काष्ठा extent_buffer *l,
		 स्थिर काष्ठा btrfs_file_extent_item *fi, u64 start),

	TP_ARGS(bi, l, fi, start)
);

DEFINE_EVENT(
	btrfs__file_extent_item_अंतरभूत, btrfs_get_extent_show_fi_अंतरभूत,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *bi, स्थिर काष्ठा extent_buffer *l,
		 स्थिर काष्ठा btrfs_file_extent_item *fi, पूर्णांक slot, u64 start),

	TP_ARGS(bi, l, fi, slot, start)
);

DEFINE_EVENT(
	btrfs__file_extent_item_अंतरभूत, btrfs_truncate_show_fi_अंतरभूत,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *bi, स्थिर काष्ठा extent_buffer *l,
		 स्थिर काष्ठा btrfs_file_extent_item *fi, पूर्णांक slot, u64 start),

	TP_ARGS(bi, l, fi, slot, start)
);

#घोषणा show_ordered_flags(flags)					   \
	__prपूर्णांक_flags(flags, "|",					   \
		अणु (1 << BTRFS_ORDERED_REGULAR), 	"REGULAR" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_NOCOW), 		"NOCOW" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_PREALLOC), 	"PREALLOC" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_COMPRESSED), 	"COMPRESSED" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_सूचीECT),	 	"DIRECT" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_IO_DONE), 	"IO_DONE" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_COMPLETE), 	"COMPLETE" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_IOERR), 		"IOERR" 	पूर्ण, \
		अणु (1 << BTRFS_ORDERED_TRUNCATED), 	"TRUNCATED"	पूर्ण)


DECLARE_EVENT_CLASS(btrfs__ordered_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *inode,
		 स्थिर काष्ठा btrfs_ordered_extent *ordered),

	TP_ARGS(inode, ordered),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  ino		)
		__field(	u64,  file_offset	)
		__field(	u64,  start		)
		__field(	u64,  len		)
		__field(	u64,  disk_len		)
		__field(	u64,  bytes_left	)
		__field(	अचिन्हित दीर्घ,  flags	)
		__field(	पूर्णांक,  compress_type	)
		__field(	पूर्णांक,  refs		)
		__field(	u64,  root_objectid	)
		__field(	u64,  truncated_len	)
	),

	TP_fast_assign_btrfs(inode->root->fs_info,
		__entry->ino 		= btrfs_ino(inode);
		__entry->file_offset	= ordered->file_offset;
		__entry->start		= ordered->disk_bytenr;
		__entry->len		= ordered->num_bytes;
		__entry->disk_len	= ordered->disk_num_bytes;
		__entry->bytes_left	= ordered->bytes_left;
		__entry->flags		= ordered->flags;
		__entry->compress_type	= ordered->compress_type;
		__entry->refs		= refcount_पढ़ो(&ordered->refs);
		__entry->root_objectid	= inode->root->root_key.objectid;
		__entry->truncated_len	= ordered->truncated_len;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) ino=%llu file_offset=%llu "
		  "start=%llu len=%llu disk_len=%llu "
		  "truncated_len=%llu "
		  "bytes_left=%llu flags=%s compress_type=%d "
		  "refs=%d",
		  show_root_type(__entry->root_objectid),
		  __entry->ino,
		  __entry->file_offset,
		  __entry->start,
		  __entry->len,
		  __entry->disk_len,
		  __entry->truncated_len,
		  __entry->bytes_left,
		  show_ordered_flags(__entry->flags),
		  __entry->compress_type, __entry->refs)
);

DEFINE_EVENT(btrfs__ordered_extent, btrfs_ordered_extent_add,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *inode,
		 स्थिर काष्ठा btrfs_ordered_extent *ordered),

	TP_ARGS(inode, ordered)
);

DEFINE_EVENT(btrfs__ordered_extent, btrfs_ordered_extent_हटाओ,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *inode,
		 स्थिर काष्ठा btrfs_ordered_extent *ordered),

	TP_ARGS(inode, ordered)
);

DEFINE_EVENT(btrfs__ordered_extent, btrfs_ordered_extent_start,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *inode,
		 स्थिर काष्ठा btrfs_ordered_extent *ordered),

	TP_ARGS(inode, ordered)
);

DEFINE_EVENT(btrfs__ordered_extent, btrfs_ordered_extent_put,

	TP_PROTO(स्थिर काष्ठा btrfs_inode *inode,
		 स्थिर काष्ठा btrfs_ordered_extent *ordered),

	TP_ARGS(inode, ordered)
);

DECLARE_EVENT_CLASS(btrfs__ग_लिखोpage,

	TP_PROTO(स्थिर काष्ठा page *page, स्थिर काष्ठा inode *inode,
		 स्थिर काष्ठा ग_लिखोback_control *wbc),

	TP_ARGS(page, inode, wbc),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	ino			)
		__field(	pgoff_t,  index			)
		__field(	दीर्घ,   nr_to_ग_लिखो		)
		__field(	दीर्घ,   pages_skipped		)
		__field(	loff_t, range_start		)
		__field(	loff_t, range_end		)
		__field(	अक्षर,   क्रम_kupdate		)
		__field(	अक्षर,   क्रम_reclaim		)
		__field(	अक्षर,   range_cyclic		)
		__field(	अचिन्हित दीर्घ,  ग_लिखोback_index	)
		__field(	u64,    root_objectid		)
	),

	TP_fast_assign_btrfs(btrfs_sb(inode->i_sb),
		__entry->ino		= btrfs_ino(BTRFS_I(inode));
		__entry->index		= page->index;
		__entry->nr_to_ग_लिखो	= wbc->nr_to_ग_लिखो;
		__entry->pages_skipped	= wbc->pages_skipped;
		__entry->range_start	= wbc->range_start;
		__entry->range_end	= wbc->range_end;
		__entry->क्रम_kupdate	= wbc->क्रम_kupdate;
		__entry->क्रम_reclaim	= wbc->क्रम_reclaim;
		__entry->range_cyclic	= wbc->range_cyclic;
		__entry->ग_लिखोback_index = inode->i_mapping->ग_लिखोback_index;
		__entry->root_objectid	=
				 BTRFS_I(inode)->root->root_key.objectid;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) ino=%llu page_index=%lu "
		  "nr_to_write=%ld pages_skipped=%ld range_start=%llu "
		  "range_end=%llu for_kupdate=%d "
		  "for_reclaim=%d range_cyclic=%d writeback_index=%lu",
		  show_root_type(__entry->root_objectid),
		  __entry->ino, __entry->index,
		  __entry->nr_to_ग_लिखो, __entry->pages_skipped,
		  __entry->range_start, __entry->range_end,
		  __entry->क्रम_kupdate,
		  __entry->क्रम_reclaim, __entry->range_cyclic,
		  __entry->ग_लिखोback_index)
);

DEFINE_EVENT(btrfs__ग_लिखोpage, __extent_ग_लिखोpage,

	TP_PROTO(स्थिर काष्ठा page *page, स्थिर काष्ठा inode *inode,
		 स्थिर काष्ठा ग_लिखोback_control *wbc),

	TP_ARGS(page, inode, wbc)
);

TRACE_EVENT(btrfs_ग_लिखोpage_end_io_hook,

	TP_PROTO(स्थिर काष्ठा page *page, u64 start, u64 end, पूर्णांक uptodate),

	TP_ARGS(page, start, end, uptodate),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	 ino		)
		__field(	अचिन्हित दीर्घ, index	)
		__field(	u64,	 start		)
		__field(	u64,	 end		)
		__field(	पूर्णांक,	 uptodate	)
		__field(	u64,    root_objectid	)
	),

	TP_fast_assign_btrfs(btrfs_sb(page->mapping->host->i_sb),
		__entry->ino	= btrfs_ino(BTRFS_I(page->mapping->host));
		__entry->index	= page->index;
		__entry->start	= start;
		__entry->end	= end;
		__entry->uptodate = uptodate;
		__entry->root_objectid	=
			 BTRFS_I(page->mapping->host)->root->root_key.objectid;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) ino=%llu page_index=%lu start=%llu "
		  "end=%llu uptodate=%d",
		  show_root_type(__entry->root_objectid),
		  __entry->ino, __entry->index,
		  __entry->start,
		  __entry->end, __entry->uptodate)
);

TRACE_EVENT(btrfs_sync_file,

	TP_PROTO(स्थिर काष्ठा file *file, पूर्णांक datasync),

	TP_ARGS(file, datasync),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	ino		)
		__field(	u64,	parent		)
		__field(	पूर्णांक,    datasync	)
		__field(	u64,    root_objectid	)
	),

	TP_fast_assign(
		स्थिर काष्ठा dentry *dentry = file->f_path.dentry;
		स्थिर काष्ठा inode *inode = d_inode(dentry);

		TP_fast_assign_fsid(btrfs_sb(file->f_path.dentry->d_sb));
		__entry->ino		= btrfs_ino(BTRFS_I(inode));
		__entry->parent		= btrfs_ino(BTRFS_I(d_inode(dentry->d_parent)));
		__entry->datasync	= datasync;
		__entry->root_objectid	=
				 BTRFS_I(inode)->root->root_key.objectid;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) ino=%llu parent=%llu datasync=%d",
		  show_root_type(__entry->root_objectid),
		  __entry->ino,
		  __entry->parent,
		  __entry->datasync)
);

TRACE_EVENT(btrfs_sync_fs,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, पूर्णांक रुको),

	TP_ARGS(fs_info, रुको),

	TP_STRUCT__entry_btrfs(
		__field(	पूर्णांक,  रुको		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->रुको	= रुको;
	),

	TP_prपूर्णांकk_btrfs("wait=%d", __entry->रुको)
);

TRACE_EVENT(btrfs_add_block_group,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_block_group *block_group, पूर्णांक create),

	TP_ARGS(fs_info, block_group, create),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	offset			)
		__field(	u64,	size			)
		__field(	u64,	flags			)
		__field(	u64,	bytes_used		)
		__field(	u64,	bytes_super		)
		__field(	पूर्णांक,	create			)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->offset		= block_group->start;
		__entry->size		= block_group->length;
		__entry->flags		= block_group->flags;
		__entry->bytes_used	= block_group->used;
		__entry->bytes_super	= block_group->bytes_super;
		__entry->create		= create;
	),

	TP_prपूर्णांकk_btrfs("block_group offset=%llu size=%llu "
		  "flags=%llu(%s) bytes_used=%llu bytes_super=%llu "
		  "create=%d",
		  __entry->offset,
		  __entry->size,
		  __entry->flags,
		  __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->flags, "|",
				BTRFS_GROUP_FLAGS),
		  __entry->bytes_used,
		  __entry->bytes_super, __entry->create)
);

#घोषणा show_ref_action(action)						\
	__prपूर्णांक_symbolic(action,					\
		अणु BTRFS_ADD_DELAYED_REF,    "ADD_DELAYED_REF" पूर्ण,	\
		अणु BTRFS_DROP_DELAYED_REF,   "DROP_DELAYED_REF" पूर्ण,	\
		अणु BTRFS_ADD_DELAYED_EXTENT, "ADD_DELAYED_EXTENT" पूर्ण, 	\
		अणु BTRFS_UPDATE_DELAYED_HEAD, "UPDATE_DELAYED_HEAD" पूर्ण)
			

DECLARE_EVENT_CLASS(btrfs_delayed_tree_ref,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_node *ref,
		 स्थिर काष्ठा btrfs_delayed_tree_ref *full_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, ref, full_ref, action),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  bytenr		)
		__field(	u64,  num_bytes		)
		__field(	पूर्णांक,  action		) 
		__field(	u64,  parent		)
		__field(	u64,  ref_root		)
		__field(	पूर्णांक,  level		)
		__field(	पूर्णांक,  type		)
		__field(	u64,  seq		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->bytenr		= ref->bytenr;
		__entry->num_bytes	= ref->num_bytes;
		__entry->action		= action;
		__entry->parent		= full_ref->parent;
		__entry->ref_root	= full_ref->root;
		__entry->level		= full_ref->level;
		__entry->type		= ref->type;
		__entry->seq		= ref->seq;
	),

	TP_prपूर्णांकk_btrfs("bytenr=%llu num_bytes=%llu action=%s "
		  "parent=%llu(%s) ref_root=%llu(%s) level=%d "
		  "type=%s seq=%llu",
		  __entry->bytenr,
		  __entry->num_bytes,
		  show_ref_action(__entry->action),
		  show_root_type(__entry->parent),
		  show_root_type(__entry->ref_root),
		  __entry->level, show_ref_type(__entry->type),
		  __entry->seq)
);

DEFINE_EVENT(btrfs_delayed_tree_ref,  add_delayed_tree_ref,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_node *ref,
		 स्थिर काष्ठा btrfs_delayed_tree_ref *full_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, ref, full_ref, action)
);

DEFINE_EVENT(btrfs_delayed_tree_ref,  run_delayed_tree_ref,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_node *ref,
		 स्थिर काष्ठा btrfs_delayed_tree_ref *full_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, ref, full_ref, action)
);

DECLARE_EVENT_CLASS(btrfs_delayed_data_ref,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_node *ref,
		 स्थिर काष्ठा btrfs_delayed_data_ref *full_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, ref, full_ref, action),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  bytenr		)
		__field(	u64,  num_bytes		)
		__field(	पूर्णांक,  action		) 
		__field(	u64,  parent		)
		__field(	u64,  ref_root		)
		__field(	u64,  owner		)
		__field(	u64,  offset		)
		__field(	पूर्णांक,  type		)
		__field(	u64,  seq		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->bytenr		= ref->bytenr;
		__entry->num_bytes	= ref->num_bytes;
		__entry->action		= action;
		__entry->parent		= full_ref->parent;
		__entry->ref_root	= full_ref->root;
		__entry->owner		= full_ref->objectid;
		__entry->offset		= full_ref->offset;
		__entry->type		= ref->type;
		__entry->seq		= ref->seq;
	),

	TP_prपूर्णांकk_btrfs("bytenr=%llu num_bytes=%llu action=%s "
		  "parent=%llu(%s) ref_root=%llu(%s) owner=%llu "
		  "offset=%llu type=%s seq=%llu",
		  __entry->bytenr,
		  __entry->num_bytes,
		  show_ref_action(__entry->action),
		  show_root_type(__entry->parent),
		  show_root_type(__entry->ref_root),
		  __entry->owner,
		  __entry->offset,
		  show_ref_type(__entry->type),
		  __entry->seq)
);

DEFINE_EVENT(btrfs_delayed_data_ref,  add_delayed_data_ref,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_node *ref,
		 स्थिर काष्ठा btrfs_delayed_data_ref *full_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, ref, full_ref, action)
);

DEFINE_EVENT(btrfs_delayed_data_ref,  run_delayed_data_ref,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_node *ref,
		 स्थिर काष्ठा btrfs_delayed_data_ref *full_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, ref, full_ref, action)
);

DECLARE_EVENT_CLASS(btrfs_delayed_ref_head,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_head *head_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, head_ref, action),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  bytenr		)
		__field(	u64,  num_bytes		)
		__field(	पूर्णांक,  action		) 
		__field(	पूर्णांक,  is_data		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->bytenr		= head_ref->bytenr;
		__entry->num_bytes	= head_ref->num_bytes;
		__entry->action		= action;
		__entry->is_data	= head_ref->is_data;
	),

	TP_prपूर्णांकk_btrfs("bytenr=%llu num_bytes=%llu action=%s is_data=%d",
		  __entry->bytenr,
		  __entry->num_bytes,
		  show_ref_action(__entry->action),
		  __entry->is_data)
);

DEFINE_EVENT(btrfs_delayed_ref_head,  add_delayed_ref_head,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_head *head_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, head_ref, action)
);

DEFINE_EVENT(btrfs_delayed_ref_head,  run_delayed_ref_head,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_delayed_ref_head *head_ref,
		 पूर्णांक action),

	TP_ARGS(fs_info, head_ref, action)
);

#घोषणा show_chunk_type(type)					\
	__prपूर्णांक_flags(type, "|",				\
		अणु BTRFS_BLOCK_GROUP_DATA, 	"DATA"	पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_SYSTEM, 	"SYSTEM"पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_METADATA, 	"METADATA"पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_RAID0, 	"RAID0" पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_RAID1, 	"RAID1" पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_DUP, 	"DUP"	पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_RAID10, 	"RAID10"पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_RAID5, 	"RAID5"	पूर्ण,	\
		अणु BTRFS_BLOCK_GROUP_RAID6, 	"RAID6"	पूर्ण)

DECLARE_EVENT_CLASS(btrfs__chunk,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा map_lookup *map, u64 offset, u64 size),

	TP_ARGS(fs_info, map, offset, size),

	TP_STRUCT__entry_btrfs(
		__field(	पूर्णांक,  num_stripes		)
		__field(	u64,  type			)
		__field(	पूर्णांक,  sub_stripes		)
		__field(	u64,  offset			)
		__field(	u64,  size			)
		__field(	u64,  root_objectid		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->num_stripes	= map->num_stripes;
		__entry->type		= map->type;
		__entry->sub_stripes	= map->sub_stripes;
		__entry->offset		= offset;
		__entry->size		= size;
		__entry->root_objectid	= fs_info->chunk_root->root_key.objectid;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) offset=%llu size=%llu "
		  "num_stripes=%d sub_stripes=%d type=%s",
		  show_root_type(__entry->root_objectid),
		  __entry->offset,
		  __entry->size,
		  __entry->num_stripes, __entry->sub_stripes,
		  show_chunk_type(__entry->type))
);

DEFINE_EVENT(btrfs__chunk,  btrfs_chunk_alloc,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा map_lookup *map, u64 offset, u64 size),

	TP_ARGS(fs_info, map, offset, size)
);

DEFINE_EVENT(btrfs__chunk,  btrfs_chunk_मुक्त,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा map_lookup *map, u64 offset, u64 size),

	TP_ARGS(fs_info, map, offset, size)
);

TRACE_EVENT(btrfs_cow_block,

	TP_PROTO(स्थिर काष्ठा btrfs_root *root, स्थिर काष्ठा extent_buffer *buf,
		 स्थिर काष्ठा extent_buffer *cow),

	TP_ARGS(root, buf, cow),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  root_objectid		)
		__field(	u64,  buf_start			)
		__field(	पूर्णांक,  refs			)
		__field(	u64,  cow_start			)
		__field(	पूर्णांक,  buf_level			)
		__field(	पूर्णांक,  cow_level			)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->root_objectid	= root->root_key.objectid;
		__entry->buf_start	= buf->start;
		__entry->refs		= atomic_पढ़ो(&buf->refs);
		__entry->cow_start	= cow->start;
		__entry->buf_level	= btrfs_header_level(buf);
		__entry->cow_level	= btrfs_header_level(cow);
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) refs=%d orig_buf=%llu "
		  "(orig_level=%d) cow_buf=%llu (cow_level=%d)",
		  show_root_type(__entry->root_objectid),
		  __entry->refs,
		  __entry->buf_start,
		  __entry->buf_level,
		  __entry->cow_start,
		  __entry->cow_level)
);

TRACE_EVENT(btrfs_space_reservation,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *type, u64 val,
		 u64 bytes, पूर्णांक reserve),

	TP_ARGS(fs_info, type, val, bytes, reserve),

	TP_STRUCT__entry_btrfs(
		__string(	type,	type			)
		__field(	u64,	val			)
		__field(	u64,	bytes			)
		__field(	पूर्णांक,	reserve			)
	),

	TP_fast_assign_btrfs(fs_info,
		__assign_str(type, type);
		__entry->val		= val;
		__entry->bytes		= bytes;
		__entry->reserve	= reserve;
	),

	TP_prपूर्णांकk_btrfs("%s: %llu %s %llu", __get_str(type), __entry->val,
			__entry->reserve ? "reserve" : "release",
			__entry->bytes)
);

TRACE_EVENT(btrfs_trigger_flush,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 flags, u64 bytes,
		 पूर्णांक flush, स्थिर अक्षर *reason),

	TP_ARGS(fs_info, flags, bytes, flush, reason),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	flags			)
		__field(	u64,	bytes			)
		__field(	पूर्णांक,	flush			)
		__string(	reason,	reason			)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->flags	= flags;
		__entry->bytes	= bytes;
		__entry->flush	= flush;
		__assign_str(reason, reason)
	),

	TP_prपूर्णांकk_btrfs("%s: flush=%d(%s) flags=%llu(%s) bytes=%llu",
		  __get_str(reason), __entry->flush,
		  __prपूर्णांक_symbolic(__entry->flush, FLUSH_ACTIONS),
		  __entry->flags,
		  __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->flags, "|",
				BTRFS_GROUP_FLAGS),
		  __entry->bytes)
);


TRACE_EVENT(btrfs_flush_space,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 flags, u64 num_bytes,
		 पूर्णांक state, पूर्णांक ret, bool क्रम_preempt),

	TP_ARGS(fs_info, flags, num_bytes, state, ret, क्रम_preempt),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	flags			)
		__field(	u64,	num_bytes		)
		__field(	पूर्णांक,	state			)
		__field(	पूर्णांक,	ret			)
		__field(       bool,	क्रम_preempt		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->flags		=	flags;
		__entry->num_bytes	=	num_bytes;
		__entry->state		=	state;
		__entry->ret		=	ret;
		__entry->क्रम_preempt	=	क्रम_preempt;
	),

	TP_prपूर्णांकk_btrfs("state=%d(%s) flags=%llu(%s) num_bytes=%llu ret=%d for_preempt=%d",
		  __entry->state,
		  __prपूर्णांक_symbolic(__entry->state, FLUSH_STATES),
		  __entry->flags,
		  __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->flags, "|",
				BTRFS_GROUP_FLAGS),
		  __entry->num_bytes, __entry->ret, __entry->क्रम_preempt)
);

DECLARE_EVENT_CLASS(btrfs__reserved_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 start, u64 len),

	TP_ARGS(fs_info, start, len),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  start			)
		__field(	u64,  len			)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->start		= start;
		__entry->len		= len;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) start=%llu len=%llu",
		  show_root_type(BTRFS_EXTENT_TREE_OBJECTID),
		  __entry->start,
		  __entry->len)
);

DEFINE_EVENT(btrfs__reserved_extent,  btrfs_reserved_extent_alloc,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 start, u64 len),

	TP_ARGS(fs_info, start, len)
);

DEFINE_EVENT(btrfs__reserved_extent,  btrfs_reserved_extent_मुक्त,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 start, u64 len),

	TP_ARGS(fs_info, start, len)
);

TRACE_EVENT(find_मुक्त_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_root *root, u64 num_bytes,
		 u64 empty_size, u64 data),

	TP_ARGS(root, num_bytes, empty_size, data),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	root_objectid		)
		__field(	u64,	num_bytes		)
		__field(	u64,	empty_size		)
		__field(	u64,	data			)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->root_objectid	= root->root_key.objectid;
		__entry->num_bytes	= num_bytes;
		__entry->empty_size	= empty_size;
		__entry->data		= data;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) len=%llu empty_size=%llu flags=%llu(%s)",
		  show_root_type(__entry->root_objectid),
		  __entry->num_bytes, __entry->empty_size, __entry->data,
		  __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->data, "|",
				 BTRFS_GROUP_FLAGS))
);

DECLARE_EVENT_CLASS(btrfs__reserve_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_block_group *block_group, u64 start,
		 u64 len),

	TP_ARGS(block_group, start, len),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	bg_objectid		)
		__field(	u64,	flags			)
		__field(	u64,	start			)
		__field(	u64,	len			)
	),

	TP_fast_assign_btrfs(block_group->fs_info,
		__entry->bg_objectid	= block_group->start;
		__entry->flags		= block_group->flags;
		__entry->start		= start;
		__entry->len		= len;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) block_group=%llu flags=%llu(%s) "
		  "start=%llu len=%llu",
		  show_root_type(BTRFS_EXTENT_TREE_OBJECTID),
		  __entry->bg_objectid,
		  __entry->flags, __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->flags,
						"|", BTRFS_GROUP_FLAGS),
		  __entry->start, __entry->len)
);

DEFINE_EVENT(btrfs__reserve_extent, btrfs_reserve_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_block_group *block_group, u64 start,
		 u64 len),

	TP_ARGS(block_group, start, len)
);

DEFINE_EVENT(btrfs__reserve_extent, btrfs_reserve_extent_cluster,

	TP_PROTO(स्थिर काष्ठा btrfs_block_group *block_group, u64 start,
		 u64 len),

	TP_ARGS(block_group, start, len)
);

TRACE_EVENT(btrfs_find_cluster,

	TP_PROTO(स्थिर काष्ठा btrfs_block_group *block_group, u64 start,
		 u64 bytes, u64 empty_size, u64 min_bytes),

	TP_ARGS(block_group, start, bytes, empty_size, min_bytes),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	bg_objectid		)
		__field(	u64,	flags			)
		__field(	u64,	start			)
		__field(	u64,	bytes			)
		__field(	u64,	empty_size		)
		__field(	u64,	min_bytes		)
	),

	TP_fast_assign_btrfs(block_group->fs_info,
		__entry->bg_objectid	= block_group->start;
		__entry->flags		= block_group->flags;
		__entry->start		= start;
		__entry->bytes		= bytes;
		__entry->empty_size	= empty_size;
		__entry->min_bytes	= min_bytes;
	),

	TP_prपूर्णांकk_btrfs("block_group=%llu flags=%llu(%s) start=%llu len=%llu "
		  "empty_size=%llu min_bytes=%llu", __entry->bg_objectid,
		  __entry->flags,
		  __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->flags, "|",
				BTRFS_GROUP_FLAGS), __entry->start,
		  __entry->bytes, __entry->empty_size,  __entry->min_bytes)
);

TRACE_EVENT(btrfs_failed_cluster_setup,

	TP_PROTO(स्थिर काष्ठा btrfs_block_group *block_group),

	TP_ARGS(block_group),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	bg_objectid		)
	),

	TP_fast_assign_btrfs(block_group->fs_info,
		__entry->bg_objectid	= block_group->start;
	),

	TP_prपूर्णांकk_btrfs("block_group=%llu", __entry->bg_objectid)
);

TRACE_EVENT(btrfs_setup_cluster,

	TP_PROTO(स्थिर काष्ठा btrfs_block_group *block_group,
		 स्थिर काष्ठा btrfs_मुक्त_cluster *cluster,
		 u64 size, पूर्णांक biपंचांगap),

	TP_ARGS(block_group, cluster, size, biपंचांगap),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	bg_objectid		)
		__field(	u64,	flags			)
		__field(	u64,	start			)
		__field(	u64,	max_size		)
		__field(	u64,	size			)
		__field(	पूर्णांक,	biपंचांगap			)
	),

	TP_fast_assign_btrfs(block_group->fs_info,
		__entry->bg_objectid	= block_group->start;
		__entry->flags		= block_group->flags;
		__entry->start		= cluster->winकरोw_start;
		__entry->max_size	= cluster->max_size;
		__entry->size		= size;
		__entry->biपंचांगap		= biपंचांगap;
	),

	TP_prपूर्णांकk_btrfs("block_group=%llu flags=%llu(%s) window_start=%llu "
		  "size=%llu max_size=%llu bitmap=%d",
		  __entry->bg_objectid,
		  __entry->flags,
		  __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->flags, "|",
				BTRFS_GROUP_FLAGS), __entry->start,
		  __entry->size, __entry->max_size, __entry->biपंचांगap)
);

काष्ठा extent_state;
TRACE_EVENT(alloc_extent_state,

	TP_PROTO(स्थिर काष्ठा extent_state *state,
		 gfp_t mask, अचिन्हित दीर्घ IP),

	TP_ARGS(state, mask, IP),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा extent_state *, state)
		__field(gfp_t, mask)
		__field(स्थिर व्योम*, ip)
	),

	TP_fast_assign(
		__entry->state	= state,
		__entry->mask	= mask,
		__entry->ip	= (स्थिर व्योम *)IP
	),

	TP_prपूर्णांकk("state=%p mask=%s caller=%pS", __entry->state,
		  show_gfp_flags(__entry->mask), __entry->ip)
);

TRACE_EVENT(मुक्त_extent_state,

	TP_PROTO(स्थिर काष्ठा extent_state *state, अचिन्हित दीर्घ IP),

	TP_ARGS(state, IP),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा extent_state *, state)
		__field(स्थिर व्योम*, ip)
	),

	TP_fast_assign(
		__entry->state	= state,
		__entry->ip = (स्थिर व्योम *)IP
	),

	TP_prपूर्णांकk("state=%p caller=%pS", __entry->state, __entry->ip)
);

DECLARE_EVENT_CLASS(btrfs__work,

	TP_PROTO(स्थिर काष्ठा btrfs_work *work),

	TP_ARGS(work),

	TP_STRUCT__entry_btrfs(
		__field(	स्थिर व्योम *,	work			)
		__field(	स्थिर व्योम *,	wq			)
		__field(	स्थिर व्योम *,	func			)
		__field(	स्थिर व्योम *,	ordered_func		)
		__field(	स्थिर व्योम *,	ordered_मुक्त		)
		__field(	स्थिर व्योम *,	normal_work		)
	),

	TP_fast_assign_btrfs(btrfs_work_owner(work),
		__entry->work		= work;
		__entry->wq		= work->wq;
		__entry->func		= work->func;
		__entry->ordered_func	= work->ordered_func;
		__entry->ordered_मुक्त	= work->ordered_मुक्त;
		__entry->normal_work	= &work->normal_work;
	),

	TP_prपूर्णांकk_btrfs("work=%p (normal_work=%p) wq=%p func=%ps ordered_func=%p "
		  "ordered_free=%p",
		  __entry->work, __entry->normal_work, __entry->wq,
		   __entry->func, __entry->ordered_func, __entry->ordered_मुक्त)
);

/*
 * For situations when the work is मुक्तd, we pass fs_info and a tag that matches
 * the address of the work काष्ठाure so it can be paired with the scheduling
 * event. DO NOT add anything here that dereferences wtag.
 */
DECLARE_EVENT_CLASS(btrfs__work__करोne,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, स्थिर व्योम *wtag),

	TP_ARGS(fs_info, wtag),

	TP_STRUCT__entry_btrfs(
		__field(	स्थिर व्योम *,	wtag			)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->wtag		= wtag;
	),

	TP_prपूर्णांकk_btrfs("work->%p", __entry->wtag)
);

DEFINE_EVENT(btrfs__work, btrfs_work_queued,

	TP_PROTO(स्थिर काष्ठा btrfs_work *work),

	TP_ARGS(work)
);

DEFINE_EVENT(btrfs__work, btrfs_work_sched,

	TP_PROTO(स्थिर काष्ठा btrfs_work *work),

	TP_ARGS(work)
);

DEFINE_EVENT(btrfs__work__करोne, btrfs_all_work_करोne,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, स्थिर व्योम *wtag),

	TP_ARGS(fs_info, wtag)
);

DEFINE_EVENT(btrfs__work, btrfs_ordered_sched,

	TP_PROTO(स्थिर काष्ठा btrfs_work *work),

	TP_ARGS(work)
);

DECLARE_EVENT_CLASS(btrfs__workqueue,

	TP_PROTO(स्थिर काष्ठा __btrfs_workqueue *wq,
		 स्थिर अक्षर *name, पूर्णांक high),

	TP_ARGS(wq, name, high),

	TP_STRUCT__entry_btrfs(
		__field(	स्थिर व्योम *,	wq			)
		__string(	name,	name			)
		__field(	पूर्णांक ,	high			)
	),

	TP_fast_assign_btrfs(btrfs_workqueue_owner(wq),
		__entry->wq		= wq;
		__assign_str(name, name);
		__entry->high		= high;
	),

	TP_prपूर्णांकk_btrfs("name=%s%s wq=%p", __get_str(name),
		  __prपूर्णांक_flags(__entry->high, "",
				अणु(WQ_HIGHPRI),	"-high"पूर्ण),
		  __entry->wq)
);

DEFINE_EVENT(btrfs__workqueue, btrfs_workqueue_alloc,

	TP_PROTO(स्थिर काष्ठा __btrfs_workqueue *wq,
		 स्थिर अक्षर *name, पूर्णांक high),

	TP_ARGS(wq, name, high)
);

DECLARE_EVENT_CLASS(btrfs__workqueue_करोne,

	TP_PROTO(स्थिर काष्ठा __btrfs_workqueue *wq),

	TP_ARGS(wq),

	TP_STRUCT__entry_btrfs(
		__field(	स्थिर व्योम *,	wq		)
	),

	TP_fast_assign_btrfs(btrfs_workqueue_owner(wq),
		__entry->wq		= wq;
	),

	TP_prपूर्णांकk_btrfs("wq=%p", __entry->wq)
);

DEFINE_EVENT(btrfs__workqueue_करोne, btrfs_workqueue_destroy,

	TP_PROTO(स्थिर काष्ठा __btrfs_workqueue *wq),

	TP_ARGS(wq)
);

#घोषणा BTRFS_QGROUP_OPERATIONS				\
	अणु QGROUP_RESERVE,	"reserve"	पूर्ण,	\
	अणु QGROUP_RELEASE,	"release"	पूर्ण,	\
	अणु QGROUP_FREE,		"free"		पूर्ण

DECLARE_EVENT_CLASS(btrfs__qgroup_rsv_data,

	TP_PROTO(स्थिर काष्ठा inode *inode, u64 start, u64 len,
		 u64 reserved, पूर्णांक op),

	TP_ARGS(inode, start, len, reserved, op),

	TP_STRUCT__entry_btrfs(
		__field(	u64,		rootid		)
		__field(	u64,		ino		)
		__field(	u64,		start		)
		__field(	u64,		len		)
		__field(	u64,		reserved	)
		__field(	पूर्णांक,		op		)
	),

	TP_fast_assign_btrfs(btrfs_sb(inode->i_sb),
		__entry->rootid		=
			BTRFS_I(inode)->root->root_key.objectid;
		__entry->ino		= btrfs_ino(BTRFS_I(inode));
		__entry->start		= start;
		__entry->len		= len;
		__entry->reserved	= reserved;
		__entry->op		= op;
	),

	TP_prपूर्णांकk_btrfs("root=%llu ino=%llu start=%llu len=%llu reserved=%llu op=%s",
		  __entry->rootid, __entry->ino, __entry->start, __entry->len,
		  __entry->reserved,
		  __prपूर्णांक_flags((अचिन्हित दीर्घ)__entry->op, "",
				BTRFS_QGROUP_OPERATIONS)
	)
);

DEFINE_EVENT(btrfs__qgroup_rsv_data, btrfs_qgroup_reserve_data,

	TP_PROTO(स्थिर काष्ठा inode *inode, u64 start, u64 len,
		 u64 reserved, पूर्णांक op),

	TP_ARGS(inode, start, len, reserved, op)
);

DEFINE_EVENT(btrfs__qgroup_rsv_data, btrfs_qgroup_release_data,

	TP_PROTO(स्थिर काष्ठा inode *inode, u64 start, u64 len,
		 u64 reserved, पूर्णांक op),

	TP_ARGS(inode, start, len, reserved, op)
);

DECLARE_EVENT_CLASS(btrfs_qgroup_extent,
	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_qgroup_extent_record *rec),

	TP_ARGS(fs_info, rec),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  bytenr		)
		__field(	u64,  num_bytes		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->bytenr		= rec->bytenr,
		__entry->num_bytes	= rec->num_bytes;
	),

	TP_prपूर्णांकk_btrfs("bytenr=%llu num_bytes=%llu",
		  __entry->bytenr, __entry->num_bytes)
);

DEFINE_EVENT(btrfs_qgroup_extent, btrfs_qgroup_account_extents,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_qgroup_extent_record *rec),

	TP_ARGS(fs_info, rec)
);

DEFINE_EVENT(btrfs_qgroup_extent, btrfs_qgroup_trace_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_qgroup_extent_record *rec),

	TP_ARGS(fs_info, rec)
);

TRACE_EVENT(qgroup_num_dirty_extents,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 transid,
		 u64 num_dirty_extents),

	TP_ARGS(fs_info, transid, num_dirty_extents),

	TP_STRUCT__entry_btrfs(
		__field(	u64, transid			)
		__field(	u64, num_dirty_extents		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->transid	   = transid;
		__entry->num_dirty_extents = num_dirty_extents;
	),

	TP_prपूर्णांकk_btrfs("transid=%llu num_dirty_extents=%llu",
		__entry->transid, __entry->num_dirty_extents)
);

TRACE_EVENT(btrfs_qgroup_account_extent,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 transid, u64 bytenr,
		 u64 num_bytes, u64 nr_old_roots, u64 nr_new_roots),

	TP_ARGS(fs_info, transid, bytenr, num_bytes, nr_old_roots,
		nr_new_roots),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  transid			)
		__field(	u64,  bytenr			)
		__field(	u64,  num_bytes			)
		__field(	u64,  nr_old_roots		)
		__field(	u64,  nr_new_roots		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->transid	= transid;
		__entry->bytenr		= bytenr;
		__entry->num_bytes	= num_bytes;
		__entry->nr_old_roots	= nr_old_roots;
		__entry->nr_new_roots	= nr_new_roots;
	),

	TP_prपूर्णांकk_btrfs(
"transid=%llu bytenr=%llu num_bytes=%llu nr_old_roots=%llu nr_new_roots=%llu",
		__entry->transid,
		__entry->bytenr,
		__entry->num_bytes,
		__entry->nr_old_roots,
		__entry->nr_new_roots)
);

TRACE_EVENT(qgroup_update_counters,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_qgroup *qgroup,
		 u64 cur_old_count, u64 cur_new_count),

	TP_ARGS(fs_info, qgroup, cur_old_count, cur_new_count),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  qgid			)
		__field(	u64,  old_rfer			)
		__field(	u64,  old_excl			)
		__field(	u64,  cur_old_count		)
		__field(	u64,  cur_new_count		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->qgid		= qgroup->qgroupid;
		__entry->old_rfer	= qgroup->rfer;
		__entry->old_excl	= qgroup->excl;
		__entry->cur_old_count	= cur_old_count;
		__entry->cur_new_count	= cur_new_count;
	),

	TP_prपूर्णांकk_btrfs("qgid=%llu old_rfer=%llu old_excl=%llu cur_old_count=%llu cur_new_count=%llu",
		  __entry->qgid, __entry->old_rfer, __entry->old_excl,
		  __entry->cur_old_count, __entry->cur_new_count)
);

TRACE_EVENT(qgroup_update_reserve,

	TP_PROTO(काष्ठा btrfs_fs_info *fs_info, काष्ठा btrfs_qgroup *qgroup,
		 s64 dअगरf, पूर्णांक type),

	TP_ARGS(fs_info, qgroup, dअगरf, type),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	qgid			)
		__field(	u64,	cur_reserved		)
		__field(	s64,	dअगरf			)
		__field(	पूर्णांक,	type			)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->qgid		= qgroup->qgroupid;
		__entry->cur_reserved	= qgroup->rsv.values[type];
		__entry->dअगरf		= dअगरf;
		__entry->type		= type;
	),

	TP_prपूर्णांकk_btrfs("qgid=%llu type=%s cur_reserved=%llu diff=%lld",
		__entry->qgid, __prपूर्णांक_symbolic(__entry->type, QGROUP_RSV_TYPES),
		__entry->cur_reserved, __entry->dअगरf)
);

TRACE_EVENT(qgroup_meta_reserve,

	TP_PROTO(काष्ठा btrfs_root *root, s64 dअगरf, पूर्णांक type),

	TP_ARGS(root, dअगरf, type),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	refroot			)
		__field(	s64,	dअगरf			)
		__field(	पूर्णांक,	type			)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->refroot	= root->root_key.objectid;
		__entry->dअगरf		= dअगरf;
		__entry->type		= type;
	),

	TP_prपूर्णांकk_btrfs("refroot=%llu(%s) type=%s diff=%lld",
		show_root_type(__entry->refroot),
		__prपूर्णांक_symbolic(__entry->type, QGROUP_RSV_TYPES), __entry->dअगरf)
);

TRACE_EVENT(qgroup_meta_convert,

	TP_PROTO(काष्ठा btrfs_root *root, s64 dअगरf),

	TP_ARGS(root, dअगरf),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	refroot			)
		__field(	s64,	dअगरf			)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->refroot	= root->root_key.objectid;
		__entry->dअगरf		= dअगरf;
	),

	TP_prपूर्णांकk_btrfs("refroot=%llu(%s) type=%s->%s diff=%lld",
		show_root_type(__entry->refroot),
		__prपूर्णांक_symbolic(BTRFS_QGROUP_RSV_META_PREALLOC, QGROUP_RSV_TYPES),
		__prपूर्णांक_symbolic(BTRFS_QGROUP_RSV_META_PERTRANS, QGROUP_RSV_TYPES),
		__entry->dअगरf)
);

TRACE_EVENT(qgroup_meta_मुक्त_all_pertrans,

	TP_PROTO(काष्ठा btrfs_root *root),

	TP_ARGS(root),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	refroot			)
		__field(	s64,	dअगरf			)
		__field(	पूर्णांक,	type			)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->refroot	= root->root_key.objectid;
		spin_lock(&root->qgroup_meta_rsv_lock);
		__entry->dअगरf		= -(s64)root->qgroup_meta_rsv_pertrans;
		spin_unlock(&root->qgroup_meta_rsv_lock);
		__entry->type		= BTRFS_QGROUP_RSV_META_PERTRANS;
	),

	TP_prपूर्णांकk_btrfs("refroot=%llu(%s) type=%s diff=%lld",
		show_root_type(__entry->refroot),
		__prपूर्णांक_symbolic(__entry->type, QGROUP_RSV_TYPES), __entry->dअगरf)
);

DECLARE_EVENT_CLASS(btrfs__prelim_ref,
	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा prelim_ref *oldref,
		 स्थिर काष्ठा prelim_ref *newref, u64 tree_size),
	TP_ARGS(fs_info, newref, oldref, tree_size),

	TP_STRUCT__entry_btrfs(
		__field(	u64,  root_id		)
		__field(	u64,  objectid		)
		__field(	 u8,  type		)
		__field(	u64,  offset		)
		__field(	पूर्णांक,  level		)
		__field(	पूर्णांक,  old_count		)
		__field(	u64,  parent		)
		__field(	u64,  bytenr		)
		__field(	पूर्णांक,  mod_count		)
		__field(	u64,  tree_size		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->root_id	= oldref->root_id;
		__entry->objectid	= oldref->key_क्रम_search.objectid;
		__entry->type		= oldref->key_क्रम_search.type;
		__entry->offset		= oldref->key_क्रम_search.offset;
		__entry->level		= oldref->level;
		__entry->old_count	= oldref->count;
		__entry->parent		= oldref->parent;
		__entry->bytenr		= oldref->wanted_disk_byte;
		__entry->mod_count	= newref ? newref->count : 0;
		__entry->tree_size	= tree_size;
	),

	TP_prपूर्णांकk_btrfs("root_id=%llu key=[%llu,%u,%llu] level=%d count=[%d+%d=%d] parent=%llu wanted_disk_byte=%llu nodes=%llu",
			__entry->root_id,
			__entry->objectid, __entry->type,
			__entry->offset, __entry->level,
			__entry->old_count, __entry->mod_count,
			__entry->old_count + __entry->mod_count,
			__entry->parent,
			__entry->bytenr,
			__entry->tree_size)
);

DEFINE_EVENT(btrfs__prelim_ref, btrfs_prelim_ref_merge,
	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा prelim_ref *oldref,
		 स्थिर काष्ठा prelim_ref *newref, u64 tree_size),
	TP_ARGS(fs_info, oldref, newref, tree_size)
);

DEFINE_EVENT(btrfs__prelim_ref, btrfs_prelim_ref_insert,
	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा prelim_ref *oldref,
		 स्थिर काष्ठा prelim_ref *newref, u64 tree_size),
	TP_ARGS(fs_info, oldref, newref, tree_size)
);

TRACE_EVENT(btrfs_inode_mod_outstanding_extents,
	TP_PROTO(स्थिर काष्ठा btrfs_root *root, u64 ino, पूर्णांक mod),

	TP_ARGS(root, ino, mod),

	TP_STRUCT__entry_btrfs(
		__field(	u64, root_objectid	)
		__field(	u64, ino		)
		__field(	पूर्णांक, mod		)
	),

	TP_fast_assign_btrfs(root->fs_info,
		__entry->root_objectid	= root->root_key.objectid;
		__entry->ino		= ino;
		__entry->mod		= mod;
	),

	TP_prपूर्णांकk_btrfs("root=%llu(%s) ino=%llu mod=%d",
			show_root_type(__entry->root_objectid),
			__entry->ino, __entry->mod)
);

DECLARE_EVENT_CLASS(btrfs__block_group,
	TP_PROTO(स्थिर काष्ठा btrfs_block_group *bg_cache),

	TP_ARGS(bg_cache),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	bytenr		)
		__field(	u64,	len		)
		__field(	u64,	used		)
		__field(	u64,	flags		)
	),

	TP_fast_assign_btrfs(bg_cache->fs_info,
		__entry->bytenr = bg_cache->start,
		__entry->len	= bg_cache->length,
		__entry->used	= bg_cache->used;
		__entry->flags	= bg_cache->flags;
	),

	TP_prपूर्णांकk_btrfs("bg bytenr=%llu len=%llu used=%llu flags=%llu(%s)",
		__entry->bytenr, __entry->len, __entry->used, __entry->flags,
		__prपूर्णांक_flags(__entry->flags, "|", BTRFS_GROUP_FLAGS))
);

DEFINE_EVENT(btrfs__block_group, btrfs_हटाओ_block_group,
	TP_PROTO(स्थिर काष्ठा btrfs_block_group *bg_cache),

	TP_ARGS(bg_cache)
);

DEFINE_EVENT(btrfs__block_group, btrfs_add_unused_block_group,
	TP_PROTO(स्थिर काष्ठा btrfs_block_group *bg_cache),

	TP_ARGS(bg_cache)
);

DEFINE_EVENT(btrfs__block_group, btrfs_add_reclaim_block_group,
	TP_PROTO(स्थिर काष्ठा btrfs_block_group *bg_cache),

	TP_ARGS(bg_cache)
);

DEFINE_EVENT(btrfs__block_group, btrfs_reclaim_block_group,
	TP_PROTO(स्थिर काष्ठा btrfs_block_group *bg_cache),

	TP_ARGS(bg_cache)
);

DEFINE_EVENT(btrfs__block_group, btrfs_skip_unused_block_group,
	TP_PROTO(स्थिर काष्ठा btrfs_block_group *bg_cache),

	TP_ARGS(bg_cache)
);

TRACE_EVENT(btrfs_set_extent_bit,
	TP_PROTO(स्थिर काष्ठा extent_io_tree *tree,
		 u64 start, u64 len, अचिन्हित set_bits),

	TP_ARGS(tree, start, len, set_bits),

	TP_STRUCT__entry_btrfs(
		__field(	अचिन्हित,	owner	)
		__field(	u64,		ino	)
		__field(	u64,		rootid	)
		__field(	u64,		start	)
		__field(	u64,		len	)
		__field(	अचिन्हित,	set_bits)
	),

	TP_fast_assign_btrfs(tree->fs_info,
		__entry->owner = tree->owner;
		अगर (tree->निजी_data) अणु
			स्थिर काष्ठा inode *inode = tree->निजी_data;

			__entry->ino	= btrfs_ino(BTRFS_I(inode));
			__entry->rootid	=
				BTRFS_I(inode)->root->root_key.objectid;
		पूर्ण अन्यथा अणु
			__entry->ino	= 0;
			__entry->rootid	= 0;
		पूर्ण
		__entry->start		= start;
		__entry->len		= len;
		__entry->set_bits	= set_bits;
	),

	TP_prपूर्णांकk_btrfs(
		"io_tree=%s ino=%llu root=%llu start=%llu len=%llu set_bits=%s",
		__prपूर्णांक_symbolic(__entry->owner, IO_TREE_OWNER), __entry->ino,
		__entry->rootid, __entry->start, __entry->len,
		__prपूर्णांक_flags(__entry->set_bits, "|", EXTENT_FLAGS))
);

TRACE_EVENT(btrfs_clear_extent_bit,
	TP_PROTO(स्थिर काष्ठा extent_io_tree *tree,
		 u64 start, u64 len, अचिन्हित clear_bits),

	TP_ARGS(tree, start, len, clear_bits),

	TP_STRUCT__entry_btrfs(
		__field(	अचिन्हित,	owner	)
		__field(	u64,		ino	)
		__field(	u64,		rootid	)
		__field(	u64,		start	)
		__field(	u64,		len	)
		__field(	अचिन्हित,	clear_bits)
	),

	TP_fast_assign_btrfs(tree->fs_info,
		__entry->owner = tree->owner;
		अगर (tree->निजी_data) अणु
			स्थिर काष्ठा inode *inode = tree->निजी_data;

			__entry->ino	= btrfs_ino(BTRFS_I(inode));
			__entry->rootid	=
				BTRFS_I(inode)->root->root_key.objectid;
		पूर्ण अन्यथा अणु
			__entry->ino	= 0;
			__entry->rootid	= 0;
		पूर्ण
		__entry->start		= start;
		__entry->len		= len;
		__entry->clear_bits	= clear_bits;
	),

	TP_prपूर्णांकk_btrfs(
		"io_tree=%s ino=%llu root=%llu start=%llu len=%llu clear_bits=%s",
		__prपूर्णांक_symbolic(__entry->owner, IO_TREE_OWNER), __entry->ino,
		__entry->rootid, __entry->start, __entry->len,
		__prपूर्णांक_flags(__entry->clear_bits, "|", EXTENT_FLAGS))
);

TRACE_EVENT(btrfs_convert_extent_bit,
	TP_PROTO(स्थिर काष्ठा extent_io_tree *tree,
		 u64 start, u64 len, अचिन्हित set_bits, अचिन्हित clear_bits),

	TP_ARGS(tree, start, len, set_bits, clear_bits),

	TP_STRUCT__entry_btrfs(
		__field(	अचिन्हित,	owner	)
		__field(	u64,		ino	)
		__field(	u64,		rootid	)
		__field(	u64,		start	)
		__field(	u64,		len	)
		__field(	अचिन्हित,	set_bits)
		__field(	अचिन्हित,	clear_bits)
	),

	TP_fast_assign_btrfs(tree->fs_info,
		__entry->owner = tree->owner;
		अगर (tree->निजी_data) अणु
			स्थिर काष्ठा inode *inode = tree->निजी_data;

			__entry->ino	= btrfs_ino(BTRFS_I(inode));
			__entry->rootid	=
				BTRFS_I(inode)->root->root_key.objectid;
		पूर्ण अन्यथा अणु
			__entry->ino	= 0;
			__entry->rootid	= 0;
		पूर्ण
		__entry->start		= start;
		__entry->len		= len;
		__entry->set_bits	= set_bits;
		__entry->clear_bits	= clear_bits;
	),

	TP_prपूर्णांकk_btrfs(
"io_tree=%s ino=%llu root=%llu start=%llu len=%llu set_bits=%s clear_bits=%s",
		  __prपूर्णांक_symbolic(__entry->owner, IO_TREE_OWNER), __entry->ino,
		  __entry->rootid, __entry->start, __entry->len,
		  __prपूर्णांक_flags(__entry->set_bits , "|", EXTENT_FLAGS),
		  __prपूर्णांक_flags(__entry->clear_bits, "|", EXTENT_FLAGS))
);

DECLARE_EVENT_CLASS(btrfs_dump_space_info,
	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_space_info *sinfo),

	TP_ARGS(fs_info, sinfo),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	flags			)
		__field(	u64,	total_bytes		)
		__field(	u64,	bytes_used		)
		__field(	u64,	bytes_pinned		)
		__field(	u64,	bytes_reserved		)
		__field(	u64,	bytes_may_use		)
		__field(	u64,	bytes_पढ़ोonly		)
		__field(	u64,	reclaim_size		)
		__field(	पूर्णांक,	clamp			)
		__field(	u64,	global_reserved		)
		__field(	u64,	trans_reserved		)
		__field(	u64,	delayed_refs_reserved	)
		__field(	u64,	delayed_reserved	)
		__field(	u64,	मुक्त_chunk_space	)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->flags			=	sinfo->flags;
		__entry->total_bytes		=	sinfo->total_bytes;
		__entry->bytes_used		=	sinfo->bytes_used;
		__entry->bytes_pinned		=	sinfo->bytes_pinned;
		__entry->bytes_reserved		=	sinfo->bytes_reserved;
		__entry->bytes_may_use		=	sinfo->bytes_may_use;
		__entry->bytes_पढ़ोonly		=	sinfo->bytes_पढ़ोonly;
		__entry->reclaim_size		=	sinfo->reclaim_size;
		__entry->clamp			=	sinfo->clamp;
		__entry->global_reserved	=	fs_info->global_block_rsv.reserved;
		__entry->trans_reserved		=	fs_info->trans_block_rsv.reserved;
		__entry->delayed_refs_reserved	=	fs_info->delayed_refs_rsv.reserved;
		__entry->delayed_reserved	=	fs_info->delayed_block_rsv.reserved;
		__entry->मुक्त_chunk_space	=	atomic64_पढ़ो(&fs_info->मुक्त_chunk_space);
	),

	TP_prपूर्णांकk_btrfs("flags=%s total_bytes=%llu bytes_used=%llu "
			"bytes_pinned=%llu bytes_reserved=%llu "
			"bytes_may_use=%llu bytes_readonly=%llu "
			"reclaim_size=%llu clamp=%d global_reserved=%llu "
			"trans_reserved=%llu delayed_refs_reserved=%llu "
			"delayed_reserved=%llu chunk_free_space=%llu",
			__prपूर्णांक_flags(__entry->flags, "|", BTRFS_GROUP_FLAGS),
			__entry->total_bytes, __entry->bytes_used,
			__entry->bytes_pinned, __entry->bytes_reserved,
			__entry->bytes_may_use, __entry->bytes_पढ़ोonly,
			__entry->reclaim_size, __entry->clamp,
			__entry->global_reserved, __entry->trans_reserved,
			__entry->delayed_refs_reserved,
			__entry->delayed_reserved, __entry->मुक्त_chunk_space)
);

DEFINE_EVENT(btrfs_dump_space_info, btrfs_करोne_preemptive_reclaim,
	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_space_info *sinfo),
	TP_ARGS(fs_info, sinfo)
);

TRACE_EVENT(btrfs_reserve_ticket,
	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info, u64 flags, u64 bytes,
		 u64 start_ns, पूर्णांक flush, पूर्णांक error),

	TP_ARGS(fs_info, flags, bytes, start_ns, flush, error),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	flags		)
		__field(	u64,	bytes		)
		__field(	u64,	start_ns	)
		__field(	पूर्णांक,	flush		)
		__field(	पूर्णांक,	error		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->flags		= flags;
		__entry->bytes		= bytes;
		__entry->start_ns	= start_ns;
		__entry->flush		= flush;
		__entry->error		= error;
	),

	TP_prपूर्णांकk_btrfs("flags=%s bytes=%llu start_ns=%llu flush=%s error=%d",
			__prपूर्णांक_flags(__entry->flags, "|", BTRFS_GROUP_FLAGS),
			__entry->bytes, __entry->start_ns,
			__prपूर्णांक_symbolic(__entry->flush, FLUSH_ACTIONS),
			__entry->error)
);

DECLARE_EVENT_CLASS(btrfs_sleep_tree_lock,
	TP_PROTO(स्थिर काष्ठा extent_buffer *eb, u64 start_ns),

	TP_ARGS(eb, start_ns),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	block		)
		__field(	u64,	generation	)
		__field(	u64,	start_ns	)
		__field(	u64,	end_ns		)
		__field(	u64,	dअगरf_ns		)
		__field(	u64,	owner		)
		__field(	पूर्णांक,	is_log_tree	)
	),

	TP_fast_assign_btrfs(eb->fs_info,
		__entry->block		= eb->start;
		__entry->generation	= btrfs_header_generation(eb);
		__entry->start_ns	= start_ns;
		__entry->end_ns		= kसमय_get_ns();
		__entry->dअगरf_ns	= __entry->end_ns - start_ns;
		__entry->owner		= btrfs_header_owner(eb);
		__entry->is_log_tree	= (eb->log_index >= 0);
	),

	TP_prपूर्णांकk_btrfs(
"block=%llu generation=%llu start_ns=%llu end_ns=%llu diff_ns=%llu owner=%llu is_log_tree=%d",
		__entry->block, __entry->generation,
		__entry->start_ns, __entry->end_ns, __entry->dअगरf_ns,
		__entry->owner, __entry->is_log_tree)
);

DEFINE_EVENT(btrfs_sleep_tree_lock, btrfs_tree_पढ़ो_lock,
	TP_PROTO(स्थिर काष्ठा extent_buffer *eb, u64 start_ns),

	TP_ARGS(eb, start_ns)
);

DEFINE_EVENT(btrfs_sleep_tree_lock, btrfs_tree_lock,
	TP_PROTO(स्थिर काष्ठा extent_buffer *eb, u64 start_ns),

	TP_ARGS(eb, start_ns)
);

DECLARE_EVENT_CLASS(btrfs_locking_events,
	TP_PROTO(स्थिर काष्ठा extent_buffer *eb),

	TP_ARGS(eb),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	block		)
		__field(	u64,	generation	)
		__field(	u64,	owner		)
		__field(	पूर्णांक,	is_log_tree	)
	),

	TP_fast_assign_btrfs(eb->fs_info,
		__entry->block		= eb->start;
		__entry->generation	= btrfs_header_generation(eb);
		__entry->owner		= btrfs_header_owner(eb);
		__entry->is_log_tree	= (eb->log_index >= 0);
	),

	TP_prपूर्णांकk_btrfs("block=%llu generation=%llu owner=%llu is_log_tree=%d",
		__entry->block, __entry->generation,
		__entry->owner, __entry->is_log_tree)
);

#घोषणा DEFINE_BTRFS_LOCK_EVENT(name)				\
DEFINE_EVENT(btrfs_locking_events, name,			\
		TP_PROTO(स्थिर काष्ठा extent_buffer *eb),	\
								\
		TP_ARGS(eb)					\
)

DEFINE_BTRFS_LOCK_EVENT(btrfs_tree_unlock);
DEFINE_BTRFS_LOCK_EVENT(btrfs_tree_पढ़ो_unlock);
DEFINE_BTRFS_LOCK_EVENT(btrfs_tree_पढ़ो_unlock_blocking);
DEFINE_BTRFS_LOCK_EVENT(btrfs_set_lock_blocking_पढ़ो);
DEFINE_BTRFS_LOCK_EVENT(btrfs_set_lock_blocking_ग_लिखो);
DEFINE_BTRFS_LOCK_EVENT(btrfs_try_tree_पढ़ो_lock);
DEFINE_BTRFS_LOCK_EVENT(btrfs_try_tree_ग_लिखो_lock);
DEFINE_BTRFS_LOCK_EVENT(btrfs_tree_पढ़ो_lock_atomic);

DECLARE_EVENT_CLASS(btrfs__space_info_update,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_space_info *sinfo, u64 old, s64 dअगरf),

	TP_ARGS(fs_info, sinfo, old, dअगरf),

	TP_STRUCT__entry_btrfs(
		__field(	u64,	type		)
		__field(	u64,	old		)
		__field(	s64,	dअगरf		)
	),

	TP_fast_assign_btrfs(fs_info,
		__entry->type	= sinfo->flags;
		__entry->old	= old;
		__entry->dअगरf	= dअगरf;
	),
	TP_prपूर्णांकk_btrfs("type=%s old=%llu diff=%lld",
		__prपूर्णांक_flags(__entry->type, "|", BTRFS_GROUP_FLAGS),
		__entry->old, __entry->dअगरf)
);

DEFINE_EVENT(btrfs__space_info_update, update_bytes_may_use,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_space_info *sinfo, u64 old, s64 dअगरf),

	TP_ARGS(fs_info, sinfo, old, dअगरf)
);

DEFINE_EVENT(btrfs__space_info_update, update_bytes_pinned,

	TP_PROTO(स्थिर काष्ठा btrfs_fs_info *fs_info,
		 स्थिर काष्ठा btrfs_space_info *sinfo, u64 old, s64 dअगरf),

	TP_ARGS(fs_info, sinfo, old, dअगरf)
);

#पूर्ण_अगर /* _TRACE_BTRFS_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
