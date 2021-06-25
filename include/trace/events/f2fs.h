<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM f2fs

#अगर !defined(_TRACE_F2FS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_F2FS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <uapi/linux/f2fs.h>

#घोषणा show_dev(dev)		MAJOR(dev), MINOR(dev)
#घोषणा show_dev_ino(entry)	show_dev(entry->dev), (अचिन्हित दीर्घ)entry->ino

TRACE_DEFINE_ENUM(NODE);
TRACE_DEFINE_ENUM(DATA);
TRACE_DEFINE_ENUM(META);
TRACE_DEFINE_ENUM(META_FLUSH);
TRACE_DEFINE_ENUM(INMEM);
TRACE_DEFINE_ENUM(INMEM_DROP);
TRACE_DEFINE_ENUM(INMEM_INVALIDATE);
TRACE_DEFINE_ENUM(INMEM_REVOKE);
TRACE_DEFINE_ENUM(IPU);
TRACE_DEFINE_ENUM(OPU);
TRACE_DEFINE_ENUM(HOT);
TRACE_DEFINE_ENUM(WARM);
TRACE_DEFINE_ENUM(COLD);
TRACE_DEFINE_ENUM(CURSEG_HOT_DATA);
TRACE_DEFINE_ENUM(CURSEG_WARM_DATA);
TRACE_DEFINE_ENUM(CURSEG_COLD_DATA);
TRACE_DEFINE_ENUM(CURSEG_HOT_NODE);
TRACE_DEFINE_ENUM(CURSEG_WARM_NODE);
TRACE_DEFINE_ENUM(CURSEG_COLD_NODE);
TRACE_DEFINE_ENUM(NO_CHECK_TYPE);
TRACE_DEFINE_ENUM(GC_GREEDY);
TRACE_DEFINE_ENUM(GC_CB);
TRACE_DEFINE_ENUM(FG_GC);
TRACE_DEFINE_ENUM(BG_GC);
TRACE_DEFINE_ENUM(LFS);
TRACE_DEFINE_ENUM(SSR);
TRACE_DEFINE_ENUM(__REQ_RAHEAD);
TRACE_DEFINE_ENUM(__REQ_SYNC);
TRACE_DEFINE_ENUM(__REQ_IDLE);
TRACE_DEFINE_ENUM(__REQ_PREFLUSH);
TRACE_DEFINE_ENUM(__REQ_FUA);
TRACE_DEFINE_ENUM(__REQ_PRIO);
TRACE_DEFINE_ENUM(__REQ_META);
TRACE_DEFINE_ENUM(CP_UMOUNT);
TRACE_DEFINE_ENUM(CP_FASTBOOT);
TRACE_DEFINE_ENUM(CP_SYNC);
TRACE_DEFINE_ENUM(CP_RECOVERY);
TRACE_DEFINE_ENUM(CP_DISCARD);
TRACE_DEFINE_ENUM(CP_TRIMMED);
TRACE_DEFINE_ENUM(CP_PAUSE);
TRACE_DEFINE_ENUM(CP_RESIZE);

#घोषणा show_block_type(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु NODE,		"NODE" पूर्ण,				\
		अणु DATA,		"DATA" पूर्ण,				\
		अणु META,		"META" पूर्ण,				\
		अणु META_FLUSH,	"META_FLUSH" पूर्ण,				\
		अणु INMEM,	"INMEM" पूर्ण,				\
		अणु INMEM_DROP,	"INMEM_DROP" पूर्ण,				\
		अणु INMEM_INVALIDATE,	"INMEM_INVALIDATE" पूर्ण,		\
		अणु INMEM_REVOKE,	"INMEM_REVOKE" पूर्ण,			\
		अणु IPU,		"IN-PLACE" पूर्ण,				\
		अणु OPU,		"OUT-OF-PLACE" पूर्ण)

#घोषणा show_block_temp(temp)						\
	__prपूर्णांक_symbolic(temp,						\
		अणु HOT,		"HOT" पूर्ण,				\
		अणु WARM,		"WARM" पूर्ण,				\
		अणु COLD,		"COLD" पूर्ण)

#घोषणा F2FS_OP_FLAGS (REQ_RAHEAD | REQ_SYNC | REQ_META | REQ_PRIO |	\
			REQ_PREFLUSH | REQ_FUA)
#घोषणा F2FS_BIO_FLAG_MASK(t)	(t & F2FS_OP_FLAGS)

#घोषणा show_bio_type(op,op_flags)	show_bio_op(op),		\
						show_bio_op_flags(op_flags)

#घोषणा show_bio_op(op)		blk_op_str(op)

#घोषणा show_bio_op_flags(flags)					\
	__prपूर्णांक_flags(F2FS_BIO_FLAG_MASK(flags), "|",			\
		अणु REQ_RAHEAD,		"R" पूर्ण,				\
		अणु REQ_SYNC,		"S" पूर्ण,				\
		अणु REQ_META,		"M" पूर्ण,				\
		अणु REQ_PRIO,		"P" पूर्ण,				\
		अणु REQ_PREFLUSH,		"PF" पूर्ण,				\
		अणु REQ_FUA,		"FUA" पूर्ण)

#घोषणा show_data_type(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु CURSEG_HOT_DATA, 	"Hot DATA" पूर्ण,			\
		अणु CURSEG_WARM_DATA, 	"Warm DATA" पूर्ण,			\
		अणु CURSEG_COLD_DATA, 	"Cold DATA" पूर्ण,			\
		अणु CURSEG_HOT_NODE, 	"Hot NODE" पूर्ण,			\
		अणु CURSEG_WARM_NODE, 	"Warm NODE" पूर्ण,			\
		अणु CURSEG_COLD_NODE, 	"Cold NODE" पूर्ण,			\
		अणु NO_CHECK_TYPE, 	"No TYPE" पूर्ण)

#घोषणा show_file_type(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु 0,		"FILE" पूर्ण,				\
		अणु 1,		"DIR" पूर्ण)

#घोषणा show_gc_type(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु FG_GC,	"Foreground GC" पूर्ण,			\
		अणु BG_GC,	"Background GC" पूर्ण)

#घोषणा show_alloc_mode(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु LFS,		"LFS-mode" पूर्ण,				\
		अणु SSR,		"SSR-mode" पूर्ण,				\
		अणु AT_SSR,	"AT_SSR-mode" पूर्ण)

#घोषणा show_victim_policy(type)					\
	__prपूर्णांक_symbolic(type,						\
		अणु GC_GREEDY,	"Greedy" पूर्ण,				\
		अणु GC_CB,	"Cost-Benefit" पूर्ण,			\
		अणु GC_AT,	"Age-threshold" पूर्ण)

#घोषणा show_cpreason(type)						\
	__prपूर्णांक_flags(type, "|",					\
		अणु CP_UMOUNT,	"Umount" पूर्ण,				\
		अणु CP_FASTBOOT,	"Fastboot" पूर्ण,				\
		अणु CP_SYNC,	"Sync" पूर्ण,				\
		अणु CP_RECOVERY,	"Recovery" पूर्ण,				\
		अणु CP_DISCARD,	"Discard" पूर्ण,				\
		अणु CP_PAUSE,	"Pause" पूर्ण,				\
		अणु CP_TRIMMED,	"Trimmed" पूर्ण,				\
		अणु CP_RESIZE,	"Resize" पूर्ण)

#घोषणा show_fsync_cpreason(type)					\
	__prपूर्णांक_symbolic(type,						\
		अणु CP_NO_NEEDED,		"no needed" पूर्ण,			\
		अणु CP_NON_REGULAR,	"non regular" पूर्ण,		\
		अणु CP_COMPRESSED,	"compressed" पूर्ण,			\
		अणु CP_HARDLINK,		"hardlink" पूर्ण,			\
		अणु CP_SB_NEED_CP,	"sb needs cp" पूर्ण,		\
		अणु CP_WRONG_PINO,	"wrong pino" पूर्ण,			\
		अणु CP_NO_SPC_ROLL,	"no space roll forward" पूर्ण,	\
		अणु CP_NODE_NEED_CP,	"node needs cp" पूर्ण,		\
		अणु CP_FASTBOOT_MODE,	"fastboot mode" पूर्ण,		\
		अणु CP_SPEC_LOG_NUM,	"log type is 2" पूर्ण,		\
		अणु CP_RECOVER_सूची,	"dir needs recovery" पूर्ण)

#घोषणा show_shutकरोwn_mode(type)					\
	__prपूर्णांक_symbolic(type,						\
		अणु F2FS_GOING_DOWN_FULLSYNC,	"full sync" पूर्ण,		\
		अणु F2FS_GOING_DOWN_METASYNC,	"meta sync" पूर्ण,		\
		अणु F2FS_GOING_DOWN_NOSYNC,	"no sync" पूर्ण,		\
		अणु F2FS_GOING_DOWN_METAFLUSH,	"meta flush" पूर्ण,		\
		अणु F2FS_GOING_DOWN_NEED_FSCK,	"need fsck" पूर्ण)

#घोषणा show_compress_algorithm(type)					\
	__prपूर्णांक_symbolic(type,						\
		अणु COMPRESS_LZO,		"LZO" पूर्ण,			\
		अणु COMPRESS_LZ4,		"LZ4" पूर्ण,			\
		अणु COMPRESS_ZSTD,	"ZSTD" पूर्ण,			\
		अणु COMPRESS_LZORLE,	"LZO-RLE" पूर्ण)

काष्ठा f2fs_sb_info;
काष्ठा f2fs_io_info;
काष्ठा extent_info;
काष्ठा victim_sel_policy;
काष्ठा f2fs_map_blocks;

DECLARE_EVENT_CLASS(f2fs__inode,

	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(ino_t,	pino)
		__field(umode_t, mode)
		__field(loff_t,	size)
		__field(अचिन्हित पूर्णांक, nlink)
		__field(blkcnt_t, blocks)
		__field(__u8,	advise)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->pino	= F2FS_I(inode)->i_pino;
		__entry->mode	= inode->i_mode;
		__entry->nlink	= inode->i_nlink;
		__entry->size	= inode->i_size;
		__entry->blocks	= inode->i_blocks;
		__entry->advise	= F2FS_I(inode)->i_advise;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, pino = %lu, i_mode = 0x%hx, "
		"i_size = %lld, i_nlink = %u, i_blocks = %llu, i_advise = 0x%x",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ)__entry->pino,
		__entry->mode,
		__entry->size,
		(अचिन्हित पूर्णांक)__entry->nlink,
		(अचिन्हित दीर्घ दीर्घ)__entry->blocks,
		(अचिन्हित अक्षर)__entry->advise)
);

DECLARE_EVENT_CLASS(f2fs__inode_निकास,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(पूर्णांक,	ret)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, ret = %d",
		show_dev_ino(__entry),
		__entry->ret)
);

DEFINE_EVENT(f2fs__inode, f2fs_sync_file_enter,

	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode)
);

TRACE_EVENT(f2fs_sync_file_निकास,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक cp_reason, पूर्णांक datasync, पूर्णांक ret),

	TP_ARGS(inode, cp_reason, datasync, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(पूर्णांक,	cp_reason)
		__field(पूर्णांक,	datasync)
		__field(पूर्णांक,	ret)
	),

	TP_fast_assign(
		__entry->dev		= inode->i_sb->s_dev;
		__entry->ino		= inode->i_ino;
		__entry->cp_reason	= cp_reason;
		__entry->datasync	= datasync;
		__entry->ret		= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, cp_reason: %s, "
		"datasync = %d, ret = %d",
		show_dev_ino(__entry),
		show_fsync_cpreason(__entry->cp_reason),
		__entry->datasync,
		__entry->ret)
);

TRACE_EVENT(f2fs_sync_fs,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक रुको),

	TP_ARGS(sb, रुको),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(पूर्णांक,	dirty)
		__field(पूर्णांक,	रुको)
	),

	TP_fast_assign(
		__entry->dev	= sb->s_dev;
		__entry->dirty	= is_sbi_flag_set(F2FS_SB(sb), SBI_IS_सूचीTY);
		__entry->रुको	= रुको;
	),

	TP_prपूर्णांकk("dev = (%d,%d), superblock is %s, wait = %d",
		show_dev(__entry->dev),
		__entry->dirty ? "dirty" : "not dirty",
		__entry->रुको)
);

DEFINE_EVENT(f2fs__inode, f2fs_iget,

	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode)
);

DEFINE_EVENT(f2fs__inode_निकास, f2fs_iget_निकास,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret)
);

DEFINE_EVENT(f2fs__inode, f2fs_evict_inode,

	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode)
);

DEFINE_EVENT(f2fs__inode_निकास, f2fs_new_inode,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret)
);

TRACE_EVENT(f2fs_unlink_enter,

	TP_PROTO(काष्ठा inode *dir, काष्ठा dentry *dentry),

	TP_ARGS(dir, dentry),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(loff_t,	size)
		__field(blkcnt_t, blocks)
		__field(स्थिर अक्षर *,	name)
	),

	TP_fast_assign(
		__entry->dev	= dir->i_sb->s_dev;
		__entry->ino	= dir->i_ino;
		__entry->size	= dir->i_size;
		__entry->blocks	= dir->i_blocks;
		__entry->name	= dentry->d_name.name;
	),

	TP_prपूर्णांकk("dev = (%d,%d), dir ino = %lu, i_size = %lld, "
		"i_blocks = %llu, name = %s",
		show_dev_ino(__entry),
		__entry->size,
		(अचिन्हित दीर्घ दीर्घ)__entry->blocks,
		__entry->name)
);

DEFINE_EVENT(f2fs__inode_निकास, f2fs_unlink_निकास,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret)
);

DEFINE_EVENT(f2fs__inode_निकास, f2fs_drop_inode,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret)
);

DEFINE_EVENT(f2fs__inode, f2fs_truncate,

	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode)
);

TRACE_EVENT(f2fs_truncate_data_blocks_range,

	TP_PROTO(काष्ठा inode *inode, nid_t nid, अचिन्हित पूर्णांक ofs, पूर्णांक मुक्त),

	TP_ARGS(inode, nid,  ofs, मुक्त),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(nid_t,	nid)
		__field(अचिन्हित पूर्णांक,	ofs)
		__field(पूर्णांक,	मुक्त)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->nid	= nid;
		__entry->ofs	= ofs;
		__entry->मुक्त	= मुक्त;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, nid = %u, offset = %u, freed = %d",
		show_dev_ino(__entry),
		(अचिन्हित पूर्णांक)__entry->nid,
		__entry->ofs,
		__entry->मुक्त)
);

DECLARE_EVENT_CLASS(f2fs__truncate_op,

	TP_PROTO(काष्ठा inode *inode, u64 from),

	TP_ARGS(inode, from),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(loff_t,	size)
		__field(blkcnt_t, blocks)
		__field(u64,	from)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->size	= inode->i_size;
		__entry->blocks	= inode->i_blocks;
		__entry->from	= from;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, i_size = %lld, i_blocks = %llu, "
		"start file offset = %llu",
		show_dev_ino(__entry),
		__entry->size,
		(अचिन्हित दीर्घ दीर्घ)__entry->blocks,
		(अचिन्हित दीर्घ दीर्घ)__entry->from)
);

DEFINE_EVENT(f2fs__truncate_op, f2fs_truncate_blocks_enter,

	TP_PROTO(काष्ठा inode *inode, u64 from),

	TP_ARGS(inode, from)
);

DEFINE_EVENT(f2fs__inode_निकास, f2fs_truncate_blocks_निकास,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret)
);

DEFINE_EVENT(f2fs__truncate_op, f2fs_truncate_inode_blocks_enter,

	TP_PROTO(काष्ठा inode *inode, u64 from),

	TP_ARGS(inode, from)
);

DEFINE_EVENT(f2fs__inode_निकास, f2fs_truncate_inode_blocks_निकास,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret)
);

DECLARE_EVENT_CLASS(f2fs__truncate_node,

	TP_PROTO(काष्ठा inode *inode, nid_t nid, block_t blk_addr),

	TP_ARGS(inode, nid, blk_addr),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(nid_t,	nid)
		__field(block_t,	blk_addr)
	),

	TP_fast_assign(
		__entry->dev		= inode->i_sb->s_dev;
		__entry->ino		= inode->i_ino;
		__entry->nid		= nid;
		__entry->blk_addr	= blk_addr;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, nid = %u, block_address = 0x%llx",
		show_dev_ino(__entry),
		(अचिन्हित पूर्णांक)__entry->nid,
		(अचिन्हित दीर्घ दीर्घ)__entry->blk_addr)
);

DEFINE_EVENT(f2fs__truncate_node, f2fs_truncate_nodes_enter,

	TP_PROTO(काष्ठा inode *inode, nid_t nid, block_t blk_addr),

	TP_ARGS(inode, nid, blk_addr)
);

DEFINE_EVENT(f2fs__inode_निकास, f2fs_truncate_nodes_निकास,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक ret),

	TP_ARGS(inode, ret)
);

DEFINE_EVENT(f2fs__truncate_node, f2fs_truncate_node,

	TP_PROTO(काष्ठा inode *inode, nid_t nid, block_t blk_addr),

	TP_ARGS(inode, nid, blk_addr)
);

TRACE_EVENT(f2fs_truncate_partial_nodes,

	TP_PROTO(काष्ठा inode *inode, nid_t *nid, पूर्णांक depth, पूर्णांक err),

	TP_ARGS(inode, nid, depth, err),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(nid_t,	nid[3])
		__field(पूर्णांक,	depth)
		__field(पूर्णांक,	err)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->nid[0]	= nid[0];
		__entry->nid[1]	= nid[1];
		__entry->nid[2]	= nid[2];
		__entry->depth	= depth;
		__entry->err	= err;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, "
		"nid[0] = %u, nid[1] = %u, nid[2] = %u, depth = %d, err = %d",
		show_dev_ino(__entry),
		(अचिन्हित पूर्णांक)__entry->nid[0],
		(अचिन्हित पूर्णांक)__entry->nid[1],
		(अचिन्हित पूर्णांक)__entry->nid[2],
		__entry->depth,
		__entry->err)
);

TRACE_EVENT(f2fs_file_ग_लिखो_iter,

	TP_PROTO(काष्ठा inode *inode, अचिन्हित दीर्घ offset,
		अचिन्हित दीर्घ length, पूर्णांक ret),

	TP_ARGS(inode, offset, length, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(अचिन्हित दीर्घ, offset)
		__field(अचिन्हित दीर्घ, length)
		__field(पूर्णांक,	ret)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->offset	= offset;
		__entry->length	= length;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, "
		"offset = %lu, length = %lu, written(err) = %d",
		show_dev_ino(__entry),
		__entry->offset,
		__entry->length,
		__entry->ret)
);

TRACE_EVENT(f2fs_map_blocks,
	TP_PROTO(काष्ठा inode *inode, काष्ठा f2fs_map_blocks *map, पूर्णांक ret),

	TP_ARGS(inode, map, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(block_t,	m_lblk)
		__field(block_t,	m_pblk)
		__field(अचिन्हित पूर्णांक,	m_len)
		__field(अचिन्हित पूर्णांक,	m_flags)
		__field(पूर्णांक,	m_seg_type)
		__field(bool,	m_may_create)
		__field(पूर्णांक,	ret)
	),

	TP_fast_assign(
		__entry->dev		= inode->i_sb->s_dev;
		__entry->ino		= inode->i_ino;
		__entry->m_lblk		= map->m_lblk;
		__entry->m_pblk		= map->m_pblk;
		__entry->m_len		= map->m_len;
		__entry->m_flags	= map->m_flags;
		__entry->m_seg_type	= map->m_seg_type;
		__entry->m_may_create	= map->m_may_create;
		__entry->ret		= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, file offset = %llu, "
		"start blkaddr = 0x%llx, len = 0x%llx, flags = %u,"
		"seg_type = %d, may_create = %d, err = %d",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ दीर्घ)__entry->m_lblk,
		(अचिन्हित दीर्घ दीर्घ)__entry->m_pblk,
		(अचिन्हित दीर्घ दीर्घ)__entry->m_len,
		__entry->m_flags,
		__entry->m_seg_type,
		__entry->m_may_create,
		__entry->ret)
);

TRACE_EVENT(f2fs_background_gc,

	TP_PROTO(काष्ठा super_block *sb, अचिन्हित पूर्णांक रुको_ms,
			अचिन्हित पूर्णांक preमुक्त, अचिन्हित पूर्णांक मुक्त),

	TP_ARGS(sb, रुको_ms, preमुक्त, मुक्त),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(अचिन्हित पूर्णांक,	रुको_ms)
		__field(अचिन्हित पूर्णांक,	preमुक्त)
		__field(अचिन्हित पूर्णांक,	मुक्त)
	),

	TP_fast_assign(
		__entry->dev		= sb->s_dev;
		__entry->रुको_ms	= रुको_ms;
		__entry->preमुक्त	= preमुक्त;
		__entry->मुक्त		= मुक्त;
	),

	TP_prपूर्णांकk("dev = (%d,%d), wait_ms = %u, prefree = %u, free = %u",
		show_dev(__entry->dev),
		__entry->रुको_ms,
		__entry->preमुक्त,
		__entry->मुक्त)
);

TRACE_EVENT(f2fs_gc_begin,

	TP_PROTO(काष्ठा super_block *sb, bool sync, bool background,
			दीर्घ दीर्घ dirty_nodes, दीर्घ दीर्घ dirty_dents,
			दीर्घ दीर्घ dirty_imeta, अचिन्हित पूर्णांक मुक्त_sec,
			अचिन्हित पूर्णांक मुक्त_seg, पूर्णांक reserved_seg,
			अचिन्हित पूर्णांक preमुक्त_seg),

	TP_ARGS(sb, sync, background, dirty_nodes, dirty_dents, dirty_imeta,
		मुक्त_sec, मुक्त_seg, reserved_seg, preमुक्त_seg),

	TP_STRUCT__entry(
		__field(dev_t,		dev)
		__field(bool,		sync)
		__field(bool,		background)
		__field(दीर्घ दीर्घ,	dirty_nodes)
		__field(दीर्घ दीर्घ,	dirty_dents)
		__field(दीर्घ दीर्घ,	dirty_imeta)
		__field(अचिन्हित पूर्णांक,	मुक्त_sec)
		__field(अचिन्हित पूर्णांक,	मुक्त_seg)
		__field(पूर्णांक,		reserved_seg)
		__field(अचिन्हित पूर्णांक,	preमुक्त_seg)
	),

	TP_fast_assign(
		__entry->dev		= sb->s_dev;
		__entry->sync		= sync;
		__entry->background	= background;
		__entry->dirty_nodes	= dirty_nodes;
		__entry->dirty_dents	= dirty_dents;
		__entry->dirty_imeta	= dirty_imeta;
		__entry->मुक्त_sec	= मुक्त_sec;
		__entry->मुक्त_seg	= मुक्त_seg;
		__entry->reserved_seg	= reserved_seg;
		__entry->preमुक्त_seg	= preमुक्त_seg;
	),

	TP_prपूर्णांकk("dev = (%d,%d), sync = %d, background = %d, nodes = %lld, "
		"dents = %lld, imeta = %lld, free_sec:%u, free_seg:%u, "
		"rsv_seg:%d, prefree_seg:%u",
		show_dev(__entry->dev),
		__entry->sync,
		__entry->background,
		__entry->dirty_nodes,
		__entry->dirty_dents,
		__entry->dirty_imeta,
		__entry->मुक्त_sec,
		__entry->मुक्त_seg,
		__entry->reserved_seg,
		__entry->preमुक्त_seg)
);

TRACE_EVENT(f2fs_gc_end,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक ret, पूर्णांक seg_मुक्तd,
			पूर्णांक sec_मुक्तd, दीर्घ दीर्घ dirty_nodes,
			दीर्घ दीर्घ dirty_dents, दीर्घ दीर्घ dirty_imeta,
			अचिन्हित पूर्णांक मुक्त_sec, अचिन्हित पूर्णांक मुक्त_seg,
			पूर्णांक reserved_seg, अचिन्हित पूर्णांक preमुक्त_seg),

	TP_ARGS(sb, ret, seg_मुक्तd, sec_मुक्तd, dirty_nodes, dirty_dents,
		dirty_imeta, मुक्त_sec, मुक्त_seg, reserved_seg, preमुक्त_seg),

	TP_STRUCT__entry(
		__field(dev_t,		dev)
		__field(पूर्णांक,		ret)
		__field(पूर्णांक,		seg_मुक्तd)
		__field(पूर्णांक,		sec_मुक्तd)
		__field(दीर्घ दीर्घ,	dirty_nodes)
		__field(दीर्घ दीर्घ,	dirty_dents)
		__field(दीर्घ दीर्घ,	dirty_imeta)
		__field(अचिन्हित पूर्णांक,	मुक्त_sec)
		__field(अचिन्हित पूर्णांक,	मुक्त_seg)
		__field(पूर्णांक,		reserved_seg)
		__field(अचिन्हित पूर्णांक,	preमुक्त_seg)
	),

	TP_fast_assign(
		__entry->dev		= sb->s_dev;
		__entry->ret		= ret;
		__entry->seg_मुक्तd	= seg_मुक्तd;
		__entry->sec_मुक्तd	= sec_मुक्तd;
		__entry->dirty_nodes	= dirty_nodes;
		__entry->dirty_dents	= dirty_dents;
		__entry->dirty_imeta	= dirty_imeta;
		__entry->मुक्त_sec	= मुक्त_sec;
		__entry->मुक्त_seg	= मुक्त_seg;
		__entry->reserved_seg	= reserved_seg;
		__entry->preमुक्त_seg	= preमुक्त_seg;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ret = %d, seg_freed = %d, sec_freed = %d, "
		"nodes = %lld, dents = %lld, imeta = %lld, free_sec:%u, "
		"free_seg:%u, rsv_seg:%d, prefree_seg:%u",
		show_dev(__entry->dev),
		__entry->ret,
		__entry->seg_मुक्तd,
		__entry->sec_मुक्तd,
		__entry->dirty_nodes,
		__entry->dirty_dents,
		__entry->dirty_imeta,
		__entry->मुक्त_sec,
		__entry->मुक्त_seg,
		__entry->reserved_seg,
		__entry->preमुक्त_seg)
);

TRACE_EVENT(f2fs_get_victim,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक gc_type,
			काष्ठा victim_sel_policy *p, अचिन्हित पूर्णांक pre_victim,
			अचिन्हित पूर्णांक preमुक्त, अचिन्हित पूर्णांक मुक्त),

	TP_ARGS(sb, type, gc_type, p, pre_victim, preमुक्त, मुक्त),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(पूर्णांक,	type)
		__field(पूर्णांक,	gc_type)
		__field(पूर्णांक,	alloc_mode)
		__field(पूर्णांक,	gc_mode)
		__field(अचिन्हित पूर्णांक,	victim)
		__field(अचिन्हित पूर्णांक,	cost)
		__field(अचिन्हित पूर्णांक,	ofs_unit)
		__field(अचिन्हित पूर्णांक,	pre_victim)
		__field(अचिन्हित पूर्णांक,	preमुक्त)
		__field(अचिन्हित पूर्णांक,	मुक्त)
	),

	TP_fast_assign(
		__entry->dev		= sb->s_dev;
		__entry->type		= type;
		__entry->gc_type	= gc_type;
		__entry->alloc_mode	= p->alloc_mode;
		__entry->gc_mode	= p->gc_mode;
		__entry->victim		= p->min_segno;
		__entry->cost		= p->min_cost;
		__entry->ofs_unit	= p->ofs_unit;
		__entry->pre_victim	= pre_victim;
		__entry->preमुक्त	= preमुक्त;
		__entry->मुक्त		= मुक्त;
	),

	TP_prपूर्णांकk("dev = (%d,%d), type = %s, policy = (%s, %s, %s), "
		"victim = %u, cost = %u, ofs_unit = %u, "
		"pre_victim_secno = %d, prefree = %u, free = %u",
		show_dev(__entry->dev),
		show_data_type(__entry->type),
		show_gc_type(__entry->gc_type),
		show_alloc_mode(__entry->alloc_mode),
		show_victim_policy(__entry->gc_mode),
		__entry->victim,
		__entry->cost,
		__entry->ofs_unit,
		(पूर्णांक)__entry->pre_victim,
		__entry->preमुक्त,
		__entry->मुक्त)
);

TRACE_EVENT(f2fs_lookup_start,

	TP_PROTO(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags),

	TP_ARGS(dir, dentry, flags),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(स्थिर अक्षर *,	name)
		__field(अचिन्हित पूर्णांक, flags)
	),

	TP_fast_assign(
		__entry->dev	= dir->i_sb->s_dev;
		__entry->ino	= dir->i_ino;
		__entry->name	= dentry->d_name.name;
		__entry->flags	= flags;
	),

	TP_prपूर्णांकk("dev = (%d,%d), pino = %lu, name:%s, flags:%u",
		show_dev_ino(__entry),
		__entry->name,
		__entry->flags)
);

TRACE_EVENT(f2fs_lookup_end,

	TP_PROTO(काष्ठा inode *dir, काष्ठा dentry *dentry, nid_t ino,
		पूर्णांक err),

	TP_ARGS(dir, dentry, ino, err),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(स्थिर अक्षर *,	name)
		__field(nid_t,	cino)
		__field(पूर्णांक,	err)
	),

	TP_fast_assign(
		__entry->dev	= dir->i_sb->s_dev;
		__entry->ino	= dir->i_ino;
		__entry->name	= dentry->d_name.name;
		__entry->cino	= ino;
		__entry->err	= err;
	),

	TP_prपूर्णांकk("dev = (%d,%d), pino = %lu, name:%s, ino:%u, err:%d",
		show_dev_ino(__entry),
		__entry->name,
		__entry->cino,
		__entry->err)
);

TRACE_EVENT(f2fs_सूची_पढ़ो,

	TP_PROTO(काष्ठा inode *dir, loff_t start_pos, loff_t end_pos, पूर्णांक err),

	TP_ARGS(dir, start_pos, end_pos, err),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(loff_t,	start)
		__field(loff_t,	end)
		__field(पूर्णांक,	err)
	),

	TP_fast_assign(
		__entry->dev	= dir->i_sb->s_dev;
		__entry->ino	= dir->i_ino;
		__entry->start	= start_pos;
		__entry->end	= end_pos;
		__entry->err	= err;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, start_pos:%llu, end_pos:%llu, err:%d",
		show_dev_ino(__entry),
		__entry->start,
		__entry->end,
		__entry->err)
);

TRACE_EVENT(f2fs_fallocate,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक mode,
				loff_t offset, loff_t len, पूर्णांक ret),

	TP_ARGS(inode, mode, offset, len, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(पूर्णांक,	mode)
		__field(loff_t,	offset)
		__field(loff_t,	len)
		__field(loff_t, size)
		__field(blkcnt_t, blocks)
		__field(पूर्णांक,	ret)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->mode	= mode;
		__entry->offset	= offset;
		__entry->len	= len;
		__entry->size	= inode->i_size;
		__entry->blocks = inode->i_blocks;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, mode = %x, offset = %lld, "
		"len = %lld,  i_size = %lld, i_blocks = %llu, ret = %d",
		show_dev_ino(__entry),
		__entry->mode,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset,
		(अचिन्हित दीर्घ दीर्घ)__entry->len,
		(अचिन्हित दीर्घ दीर्घ)__entry->size,
		(अचिन्हित दीर्घ दीर्घ)__entry->blocks,
		__entry->ret)
);

TRACE_EVENT(f2fs_direct_IO_enter,

	TP_PROTO(काष्ठा inode *inode, loff_t offset, अचिन्हित दीर्घ len, पूर्णांक rw),

	TP_ARGS(inode, offset, len, rw),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(loff_t,	pos)
		__field(अचिन्हित दीर्घ,	len)
		__field(पूर्णांक,	rw)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->pos	= offset;
		__entry->len	= len;
		__entry->rw	= rw;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu pos = %lld len = %lu rw = %d",
		show_dev_ino(__entry),
		__entry->pos,
		__entry->len,
		__entry->rw)
);

TRACE_EVENT(f2fs_direct_IO_निकास,

	TP_PROTO(काष्ठा inode *inode, loff_t offset, अचिन्हित दीर्घ len,
		 पूर्णांक rw, पूर्णांक ret),

	TP_ARGS(inode, offset, len, rw, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(loff_t,	pos)
		__field(अचिन्हित दीर्घ,	len)
		__field(पूर्णांक,	rw)
		__field(पूर्णांक,	ret)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->pos	= offset;
		__entry->len	= len;
		__entry->rw	= rw;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu pos = %lld len = %lu "
		"rw = %d ret = %d",
		show_dev_ino(__entry),
		__entry->pos,
		__entry->len,
		__entry->rw,
		__entry->ret)
);

TRACE_EVENT(f2fs_reserve_new_blocks,

	TP_PROTO(काष्ठा inode *inode, nid_t nid, अचिन्हित पूर्णांक ofs_in_node,
							blkcnt_t count),

	TP_ARGS(inode, nid, ofs_in_node, count),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(nid_t, nid)
		__field(अचिन्हित पूर्णांक, ofs_in_node)
		__field(blkcnt_t, count)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->nid	= nid;
		__entry->ofs_in_node = ofs_in_node;
		__entry->count = count;
	),

	TP_prपूर्णांकk("dev = (%d,%d), nid = %u, ofs_in_node = %u, count = %llu",
		show_dev(__entry->dev),
		(अचिन्हित पूर्णांक)__entry->nid,
		__entry->ofs_in_node,
		(अचिन्हित दीर्घ दीर्घ)__entry->count)
);

DECLARE_EVENT_CLASS(f2fs__submit_page_bio,

	TP_PROTO(काष्ठा page *page, काष्ठा f2fs_io_info *fio),

	TP_ARGS(page, fio),

	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(ino_t, ino)
		__field(pgoff_t, index)
		__field(block_t, old_blkaddr)
		__field(block_t, new_blkaddr)
		__field(पूर्णांक, op)
		__field(पूर्णांक, op_flags)
		__field(पूर्णांक, temp)
		__field(पूर्णांक, type)
	),

	TP_fast_assign(
		__entry->dev		= page_file_mapping(page)->host->i_sb->s_dev;
		__entry->ino		= page_file_mapping(page)->host->i_ino;
		__entry->index		= page->index;
		__entry->old_blkaddr	= fio->old_blkaddr;
		__entry->new_blkaddr	= fio->new_blkaddr;
		__entry->op		= fio->op;
		__entry->op_flags	= fio->op_flags;
		__entry->temp		= fio->temp;
		__entry->type		= fio->type;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, page_index = 0x%lx, "
		"oldaddr = 0x%llx, newaddr = 0x%llx, rw = %s(%s), type = %s_%s",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ)__entry->index,
		(अचिन्हित दीर्घ दीर्घ)__entry->old_blkaddr,
		(अचिन्हित दीर्घ दीर्घ)__entry->new_blkaddr,
		show_bio_type(__entry->op, __entry->op_flags),
		show_block_temp(__entry->temp),
		show_block_type(__entry->type))
);

DEFINE_EVENT_CONDITION(f2fs__submit_page_bio, f2fs_submit_page_bio,

	TP_PROTO(काष्ठा page *page, काष्ठा f2fs_io_info *fio),

	TP_ARGS(page, fio),

	TP_CONDITION(page->mapping)
);

DEFINE_EVENT_CONDITION(f2fs__submit_page_bio, f2fs_submit_page_ग_लिखो,

	TP_PROTO(काष्ठा page *page, काष्ठा f2fs_io_info *fio),

	TP_ARGS(page, fio),

	TP_CONDITION(page->mapping)
);

DECLARE_EVENT_CLASS(f2fs__bio,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, काष्ठा bio *bio),

	TP_ARGS(sb, type, bio),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(dev_t,	target)
		__field(पूर्णांक,	op)
		__field(पूर्णांक,	op_flags)
		__field(पूर्णांक,	type)
		__field(sector_t,	sector)
		__field(अचिन्हित पूर्णांक,	size)
	),

	TP_fast_assign(
		__entry->dev		= sb->s_dev;
		__entry->target		= bio_dev(bio);
		__entry->op		= bio_op(bio);
		__entry->op_flags	= bio->bi_opf;
		__entry->type		= type;
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->size		= bio->bi_iter.bi_size;
	),

	TP_prपूर्णांकk("dev = (%d,%d)/(%d,%d), rw = %s(%s), %s, sector = %lld, size = %u",
		show_dev(__entry->target),
		show_dev(__entry->dev),
		show_bio_type(__entry->op, __entry->op_flags),
		show_block_type(__entry->type),
		(अचिन्हित दीर्घ दीर्घ)__entry->sector,
		__entry->size)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_prepare_ग_लिखो_bio,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, काष्ठा bio *bio),

	TP_ARGS(sb, type, bio),

	TP_CONDITION(bio)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_prepare_पढ़ो_bio,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, काष्ठा bio *bio),

	TP_ARGS(sb, type, bio),

	TP_CONDITION(bio)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_submit_पढ़ो_bio,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, काष्ठा bio *bio),

	TP_ARGS(sb, type, bio),

	TP_CONDITION(bio)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_submit_ग_लिखो_bio,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, काष्ठा bio *bio),

	TP_ARGS(sb, type, bio),

	TP_CONDITION(bio)
);

TRACE_EVENT(f2fs_ग_लिखो_begin,

	TP_PROTO(काष्ठा inode *inode, loff_t pos, अचिन्हित पूर्णांक len,
				अचिन्हित पूर्णांक flags),

	TP_ARGS(inode, pos, len, flags),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(loff_t,	pos)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, flags)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->pos	= pos;
		__entry->len	= len;
		__entry->flags	= flags;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, pos = %llu, len = %u, flags = %u",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ दीर्घ)__entry->pos,
		__entry->len,
		__entry->flags)
);

TRACE_EVENT(f2fs_ग_लिखो_end,

	TP_PROTO(काष्ठा inode *inode, loff_t pos, अचिन्हित पूर्णांक len,
				अचिन्हित पूर्णांक copied),

	TP_ARGS(inode, pos, len, copied),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(loff_t,	pos)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, copied)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->pos	= pos;
		__entry->len	= len;
		__entry->copied	= copied;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, pos = %llu, len = %u, copied = %u",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ दीर्घ)__entry->pos,
		__entry->len,
		__entry->copied)
);

DECLARE_EVENT_CLASS(f2fs__page,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(पूर्णांक, type)
		__field(पूर्णांक, dir)
		__field(pgoff_t, index)
		__field(पूर्णांक, dirty)
		__field(पूर्णांक, uptodate)
	),

	TP_fast_assign(
		__entry->dev	= page_file_mapping(page)->host->i_sb->s_dev;
		__entry->ino	= page_file_mapping(page)->host->i_ino;
		__entry->type	= type;
		__entry->dir	=
			S_ISसूची(page_file_mapping(page)->host->i_mode);
		__entry->index	= page->index;
		__entry->dirty	= PageDirty(page);
		__entry->uptodate = PageUptodate(page);
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, %s, %s, index = %lu, "
		"dirty = %d, uptodate = %d",
		show_dev_ino(__entry),
		show_block_type(__entry->type),
		show_file_type(__entry->dir),
		(अचिन्हित दीर्घ)__entry->index,
		__entry->dirty,
		__entry->uptodate)
);

DEFINE_EVENT(f2fs__page, f2fs_ग_लिखोpage,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_करो_ग_लिखो_data_page,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_पढ़ोpage,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_set_page_dirty,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_vm_page_mkग_लिखो,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_रेजिस्टर_inmem_page,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_commit_inmem_page,

	TP_PROTO(काष्ठा page *page, पूर्णांक type),

	TP_ARGS(page, type)
);

TRACE_EVENT(f2fs_filemap_fault,

	TP_PROTO(काष्ठा inode *inode, pgoff_t index, अचिन्हित दीर्घ ret),

	TP_ARGS(inode, index, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(pgoff_t, index)
		__field(अचिन्हित दीर्घ, ret)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->index	= index;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, index = %lu, ret = %lx",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ)__entry->index,
		__entry->ret)
);

TRACE_EVENT(f2fs_ग_लिखोpages,

	TP_PROTO(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc, पूर्णांक type),

	TP_ARGS(inode, wbc, type),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(पूर्णांक,	type)
		__field(पूर्णांक,	dir)
		__field(दीर्घ,	nr_to_ग_लिखो)
		__field(दीर्घ,	pages_skipped)
		__field(loff_t,	range_start)
		__field(loff_t,	range_end)
		__field(pgoff_t, ग_लिखोback_index)
		__field(पूर्णांक,	sync_mode)
		__field(अक्षर,	क्रम_kupdate)
		__field(अक्षर,	क्रम_background)
		__field(अक्षर,	tagged_ग_लिखोpages)
		__field(अक्षर,	क्रम_reclaim)
		__field(अक्षर,	range_cyclic)
		__field(अक्षर,	क्रम_sync)
	),

	TP_fast_assign(
		__entry->dev		= inode->i_sb->s_dev;
		__entry->ino		= inode->i_ino;
		__entry->type		= type;
		__entry->dir		= S_ISसूची(inode->i_mode);
		__entry->nr_to_ग_लिखो	= wbc->nr_to_ग_लिखो;
		__entry->pages_skipped	= wbc->pages_skipped;
		__entry->range_start	= wbc->range_start;
		__entry->range_end	= wbc->range_end;
		__entry->ग_लिखोback_index = inode->i_mapping->ग_लिखोback_index;
		__entry->sync_mode	= wbc->sync_mode;
		__entry->क्रम_kupdate	= wbc->क्रम_kupdate;
		__entry->क्रम_background	= wbc->क्रम_background;
		__entry->tagged_ग_लिखोpages	= wbc->tagged_ग_लिखोpages;
		__entry->क्रम_reclaim	= wbc->क्रम_reclaim;
		__entry->range_cyclic	= wbc->range_cyclic;
		__entry->क्रम_sync	= wbc->क्रम_sync;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, %s, %s, nr_to_write %ld, "
		"skipped %ld, start %lld, end %lld, wb_idx %lu, sync_mode %d, "
		"kupdate %u background %u tagged %u reclaim %u cyclic %u sync %u",
		show_dev_ino(__entry),
		show_block_type(__entry->type),
		show_file_type(__entry->dir),
		__entry->nr_to_ग_लिखो,
		__entry->pages_skipped,
		__entry->range_start,
		__entry->range_end,
		(अचिन्हित दीर्घ)__entry->ग_लिखोback_index,
		__entry->sync_mode,
		__entry->क्रम_kupdate,
		__entry->क्रम_background,
		__entry->tagged_ग_लिखोpages,
		__entry->क्रम_reclaim,
		__entry->range_cyclic,
		__entry->क्रम_sync)
);

TRACE_EVENT(f2fs_पढ़ोpages,

	TP_PROTO(काष्ठा inode *inode, pgoff_t start, अचिन्हित पूर्णांक nrpage),

	TP_ARGS(inode, start, nrpage),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(pgoff_t,	start)
		__field(अचिन्हित पूर्णांक,	nrpage)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->start	= start;
		__entry->nrpage	= nrpage;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, start = %lu nrpage = %u",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ)__entry->start,
		__entry->nrpage)
);

TRACE_EVENT(f2fs_ग_लिखो_checkpoपूर्णांक,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक reason, अक्षर *msg),

	TP_ARGS(sb, reason, msg),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(पूर्णांक,	reason)
		__field(अक्षर *,	msg)
	),

	TP_fast_assign(
		__entry->dev		= sb->s_dev;
		__entry->reason		= reason;
		__entry->msg		= msg;
	),

	TP_prपूर्णांकk("dev = (%d,%d), checkpoint for %s, state = %s",
		show_dev(__entry->dev),
		show_cpreason(__entry->reason),
		__entry->msg)
);

DECLARE_EVENT_CLASS(f2fs_discard,

	TP_PROTO(काष्ठा block_device *dev, block_t blkstart, block_t blklen),

	TP_ARGS(dev, blkstart, blklen),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(block_t, blkstart)
		__field(block_t, blklen)
	),

	TP_fast_assign(
		__entry->dev	= dev->bd_dev;
		__entry->blkstart = blkstart;
		__entry->blklen = blklen;
	),

	TP_prपूर्णांकk("dev = (%d,%d), blkstart = 0x%llx, blklen = 0x%llx",
		show_dev(__entry->dev),
		(अचिन्हित दीर्घ दीर्घ)__entry->blkstart,
		(अचिन्हित दीर्घ दीर्घ)__entry->blklen)
);

DEFINE_EVENT(f2fs_discard, f2fs_queue_discard,

	TP_PROTO(काष्ठा block_device *dev, block_t blkstart, block_t blklen),

	TP_ARGS(dev, blkstart, blklen)
);

DEFINE_EVENT(f2fs_discard, f2fs_issue_discard,

	TP_PROTO(काष्ठा block_device *dev, block_t blkstart, block_t blklen),

	TP_ARGS(dev, blkstart, blklen)
);

DEFINE_EVENT(f2fs_discard, f2fs_हटाओ_discard,

	TP_PROTO(काष्ठा block_device *dev, block_t blkstart, block_t blklen),

	TP_ARGS(dev, blkstart, blklen)
);

TRACE_EVENT(f2fs_issue_reset_zone,

	TP_PROTO(काष्ठा block_device *dev, block_t blkstart),

	TP_ARGS(dev, blkstart),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(block_t, blkstart)
	),

	TP_fast_assign(
		__entry->dev	= dev->bd_dev;
		__entry->blkstart = blkstart;
	),

	TP_prपूर्णांकk("dev = (%d,%d), reset zone at block = 0x%llx",
		show_dev(__entry->dev),
		(अचिन्हित दीर्घ दीर्घ)__entry->blkstart)
);

TRACE_EVENT(f2fs_issue_flush,

	TP_PROTO(काष्ठा block_device *dev, अचिन्हित पूर्णांक nobarrier,
				अचिन्हित पूर्णांक flush_merge, पूर्णांक ret),

	TP_ARGS(dev, nobarrier, flush_merge, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(अचिन्हित पूर्णांक, nobarrier)
		__field(अचिन्हित पूर्णांक, flush_merge)
		__field(पूर्णांक,  ret)
	),

	TP_fast_assign(
		__entry->dev	= dev->bd_dev;
		__entry->nobarrier = nobarrier;
		__entry->flush_merge = flush_merge;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), %s %s, ret = %d",
		show_dev(__entry->dev),
		__entry->nobarrier ? "skip (nobarrier)" : "issue",
		__entry->flush_merge ? " with flush_merge" : "",
		__entry->ret)
);

TRACE_EVENT(f2fs_lookup_extent_tree_start,

	TP_PROTO(काष्ठा inode *inode, अचिन्हित पूर्णांक pgofs),

	TP_ARGS(inode, pgofs),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(अचिन्हित पूर्णांक, pgofs)
	),

	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->pgofs = pgofs;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, pgofs = %u",
		show_dev_ino(__entry),
		__entry->pgofs)
);

TRACE_EVENT_CONDITION(f2fs_lookup_extent_tree_end,

	TP_PROTO(काष्ठा inode *inode, अचिन्हित पूर्णांक pgofs,
						काष्ठा extent_info *ei),

	TP_ARGS(inode, pgofs, ei),

	TP_CONDITION(ei),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(अचिन्हित पूर्णांक, pgofs)
		__field(अचिन्हित पूर्णांक, fofs)
		__field(u32, blk)
		__field(अचिन्हित पूर्णांक, len)
	),

	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->pgofs = pgofs;
		__entry->fofs = ei->fofs;
		__entry->blk = ei->blk;
		__entry->len = ei->len;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, pgofs = %u, "
		"ext_info(fofs: %u, blk: %u, len: %u)",
		show_dev_ino(__entry),
		__entry->pgofs,
		__entry->fofs,
		__entry->blk,
		__entry->len)
);

TRACE_EVENT(f2fs_update_extent_tree_range,

	TP_PROTO(काष्ठा inode *inode, अचिन्हित पूर्णांक pgofs, block_t blkaddr,
						अचिन्हित पूर्णांक len),

	TP_ARGS(inode, pgofs, blkaddr, len),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(अचिन्हित पूर्णांक, pgofs)
		__field(u32, blk)
		__field(अचिन्हित पूर्णांक, len)
	),

	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->pgofs = pgofs;
		__entry->blk = blkaddr;
		__entry->len = len;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, pgofs = %u, "
					"blkaddr = %u, len = %u",
		show_dev_ino(__entry),
		__entry->pgofs,
		__entry->blk,
		__entry->len)
);

TRACE_EVENT(f2fs_shrink_extent_tree,

	TP_PROTO(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक node_cnt,
						अचिन्हित पूर्णांक tree_cnt),

	TP_ARGS(sbi, node_cnt, tree_cnt),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(अचिन्हित पूर्णांक, node_cnt)
		__field(अचिन्हित पूर्णांक, tree_cnt)
	),

	TP_fast_assign(
		__entry->dev = sbi->sb->s_dev;
		__entry->node_cnt = node_cnt;
		__entry->tree_cnt = tree_cnt;
	),

	TP_prपूर्णांकk("dev = (%d,%d), shrunk: node_cnt = %u, tree_cnt = %u",
		show_dev(__entry->dev),
		__entry->node_cnt,
		__entry->tree_cnt)
);

TRACE_EVENT(f2fs_destroy_extent_tree,

	TP_PROTO(काष्ठा inode *inode, अचिन्हित पूर्णांक node_cnt),

	TP_ARGS(inode, node_cnt),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(अचिन्हित पूर्णांक, node_cnt)
	),

	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->node_cnt = node_cnt;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, destroyed: node_cnt = %u",
		show_dev_ino(__entry),
		__entry->node_cnt)
);

DECLARE_EVENT_CLASS(f2fs_sync_dirty_inodes,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, s64 count),

	TP_ARGS(sb, type, count),

	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(पूर्णांक, type)
		__field(s64, count)
	),

	TP_fast_assign(
		__entry->dev	= sb->s_dev;
		__entry->type	= type;
		__entry->count	= count;
	),

	TP_prपूर्णांकk("dev = (%d,%d), %s, dirty count = %lld",
		show_dev(__entry->dev),
		show_file_type(__entry->type),
		__entry->count)
);

DEFINE_EVENT(f2fs_sync_dirty_inodes, f2fs_sync_dirty_inodes_enter,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, s64 count),

	TP_ARGS(sb, type, count)
);

DEFINE_EVENT(f2fs_sync_dirty_inodes, f2fs_sync_dirty_inodes_निकास,

	TP_PROTO(काष्ठा super_block *sb, पूर्णांक type, s64 count),

	TP_ARGS(sb, type, count)
);

TRACE_EVENT(f2fs_shutकरोwn,

	TP_PROTO(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक mode, पूर्णांक ret),

	TP_ARGS(sbi, mode, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(अचिन्हित पूर्णांक, mode)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->dev = sbi->sb->s_dev;
		__entry->mode = mode;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), mode: %s, ret:%d",
		show_dev(__entry->dev),
		show_shutकरोwn_mode(__entry->mode),
		__entry->ret)
);

DECLARE_EVENT_CLASS(f2fs_zip_start,

	TP_PROTO(काष्ठा inode *inode, pgoff_t cluster_idx,
			अचिन्हित पूर्णांक cluster_size, अचिन्हित अक्षर algtype),

	TP_ARGS(inode, cluster_idx, cluster_size, algtype),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(pgoff_t, idx)
		__field(अचिन्हित पूर्णांक, size)
		__field(अचिन्हित पूर्णांक, algtype)
	),

	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->idx = cluster_idx;
		__entry->size = cluster_size;
		__entry->algtype = algtype;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, cluster_idx:%lu, "
		"cluster_size = %u, algorithm = %s",
		show_dev_ino(__entry),
		__entry->idx,
		__entry->size,
		show_compress_algorithm(__entry->algtype))
);

DECLARE_EVENT_CLASS(f2fs_zip_end,

	TP_PROTO(काष्ठा inode *inode, pgoff_t cluster_idx,
			अचिन्हित पूर्णांक compressed_size, पूर्णांक ret),

	TP_ARGS(inode, cluster_idx, compressed_size, ret),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(ino_t,	ino)
		__field(pgoff_t, idx)
		__field(अचिन्हित पूर्णांक, size)
		__field(अचिन्हित पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->idx = cluster_idx;
		__entry->size = compressed_size;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, cluster_idx:%lu, "
		"compressed_size = %u, ret = %d",
		show_dev_ino(__entry),
		__entry->idx,
		__entry->size,
		__entry->ret)
);

DEFINE_EVENT(f2fs_zip_start, f2fs_compress_pages_start,

	TP_PROTO(काष्ठा inode *inode, pgoff_t cluster_idx,
		अचिन्हित पूर्णांक cluster_size, अचिन्हित अक्षर algtype),

	TP_ARGS(inode, cluster_idx, cluster_size, algtype)
);

DEFINE_EVENT(f2fs_zip_start, f2fs_decompress_pages_start,

	TP_PROTO(काष्ठा inode *inode, pgoff_t cluster_idx,
		अचिन्हित पूर्णांक cluster_size, अचिन्हित अक्षर algtype),

	TP_ARGS(inode, cluster_idx, cluster_size, algtype)
);

DEFINE_EVENT(f2fs_zip_end, f2fs_compress_pages_end,

	TP_PROTO(काष्ठा inode *inode, pgoff_t cluster_idx,
			अचिन्हित पूर्णांक compressed_size, पूर्णांक ret),

	TP_ARGS(inode, cluster_idx, compressed_size, ret)
);

DEFINE_EVENT(f2fs_zip_end, f2fs_decompress_pages_end,

	TP_PROTO(काष्ठा inode *inode, pgoff_t cluster_idx,
			अचिन्हित पूर्णांक compressed_size, पूर्णांक ret),

	TP_ARGS(inode, cluster_idx, compressed_size, ret)
);

TRACE_EVENT(f2fs_iostat,

	TP_PROTO(काष्ठा f2fs_sb_info *sbi, अचिन्हित दीर्घ दीर्घ *iostat),

	TP_ARGS(sbi, iostat),

	TP_STRUCT__entry(
		__field(dev_t,	dev)
		__field(अचिन्हित दीर्घ दीर्घ,	app_dio)
		__field(अचिन्हित दीर्घ दीर्घ,	app_bio)
		__field(अचिन्हित दीर्घ दीर्घ,	app_wio)
		__field(अचिन्हित दीर्घ दीर्घ,	app_mio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_dio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_nio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_mio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_gc_dio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_gc_nio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_cp_dio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_cp_nio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_cp_mio)
		__field(अचिन्हित दीर्घ दीर्घ,	app_drio)
		__field(अचिन्हित दीर्घ दीर्घ,	app_brio)
		__field(अचिन्हित दीर्घ दीर्घ,	app_rio)
		__field(अचिन्हित दीर्घ दीर्घ,	app_mrio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_drio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_gdrio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_cdrio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_nrio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_mrio)
		__field(अचिन्हित दीर्घ दीर्घ,	fs_discard)
	),

	TP_fast_assign(
		__entry->dev		= sbi->sb->s_dev;
		__entry->app_dio	= iostat[APP_सूचीECT_IO];
		__entry->app_bio	= iostat[APP_BUFFERED_IO];
		__entry->app_wio	= iostat[APP_WRITE_IO];
		__entry->app_mio	= iostat[APP_MAPPED_IO];
		__entry->fs_dio		= iostat[FS_DATA_IO];
		__entry->fs_nio		= iostat[FS_NODE_IO];
		__entry->fs_mio		= iostat[FS_META_IO];
		__entry->fs_gc_dio	= iostat[FS_GC_DATA_IO];
		__entry->fs_gc_nio	= iostat[FS_GC_NODE_IO];
		__entry->fs_cp_dio	= iostat[FS_CP_DATA_IO];
		__entry->fs_cp_nio	= iostat[FS_CP_NODE_IO];
		__entry->fs_cp_mio	= iostat[FS_CP_META_IO];
		__entry->app_drio	= iostat[APP_सूचीECT_READ_IO];
		__entry->app_brio	= iostat[APP_BUFFERED_READ_IO];
		__entry->app_rio	= iostat[APP_READ_IO];
		__entry->app_mrio	= iostat[APP_MAPPED_READ_IO];
		__entry->fs_drio	= iostat[FS_DATA_READ_IO];
		__entry->fs_gdrio	= iostat[FS_GDATA_READ_IO];
		__entry->fs_cdrio	= iostat[FS_CDATA_READ_IO];
		__entry->fs_nrio	= iostat[FS_NODE_READ_IO];
		__entry->fs_mrio	= iostat[FS_META_READ_IO];
		__entry->fs_discard	= iostat[FS_DISCARD];
	),

	TP_prपूर्णांकk("dev = (%d,%d), "
		"app [write=%llu (direct=%llu, buffered=%llu), mapped=%llu], "
		"fs [data=%llu, node=%llu, meta=%llu, discard=%llu], "
		"gc [data=%llu, node=%llu], "
		"cp [data=%llu, node=%llu, meta=%llu], "
		"app [read=%llu (direct=%llu, buffered=%llu), mapped=%llu], "
		"fs [data=%llu, (gc_data=%llu, compr_data=%llu), "
		"node=%llu, meta=%llu]",
		show_dev(__entry->dev), __entry->app_wio, __entry->app_dio,
		__entry->app_bio, __entry->app_mio, __entry->fs_dio,
		__entry->fs_nio, __entry->fs_mio, __entry->fs_discard,
		__entry->fs_gc_dio, __entry->fs_gc_nio, __entry->fs_cp_dio,
		__entry->fs_cp_nio, __entry->fs_cp_mio,
		__entry->app_rio, __entry->app_drio, __entry->app_brio,
		__entry->app_mrio, __entry->fs_drio, __entry->fs_gdrio,
		__entry->fs_cdrio, __entry->fs_nrio, __entry->fs_mrio)
);

TRACE_EVENT(f2fs_bmap,

	TP_PROTO(काष्ठा inode *inode, sector_t lblock, sector_t pblock),

	TP_ARGS(inode, lblock, pblock),

	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(ino_t, ino)
		__field(sector_t, lblock)
		__field(sector_t, pblock)
	),

	TP_fast_assign(
		__entry->dev		= inode->i_sb->s_dev;
		__entry->ino		= inode->i_ino;
		__entry->lblock		= lblock;
		__entry->pblock		= pblock;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, lblock:%lld, pblock:%lld",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ दीर्घ)__entry->lblock,
		(अचिन्हित दीर्घ दीर्घ)__entry->pblock)
);

TRACE_EVENT(f2fs_fiemap,

	TP_PROTO(काष्ठा inode *inode, sector_t lblock, sector_t pblock,
		अचिन्हित दीर्घ दीर्घ len, अचिन्हित पूर्णांक flags, पूर्णांक ret),

	TP_ARGS(inode, lblock, pblock, len, flags, ret),

	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(ino_t, ino)
		__field(sector_t, lblock)
		__field(sector_t, pblock)
		__field(अचिन्हित दीर्घ दीर्घ, len)
		__field(अचिन्हित पूर्णांक, flags)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->dev		= inode->i_sb->s_dev;
		__entry->ino		= inode->i_ino;
		__entry->lblock		= lblock;
		__entry->pblock		= pblock;
		__entry->len		= len;
		__entry->flags		= flags;
		__entry->ret		= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), ino = %lu, lblock:%lld, pblock:%lld, "
		"len:%llu, flags:%u, ret:%d",
		show_dev_ino(__entry),
		(अचिन्हित दीर्घ दीर्घ)__entry->lblock,
		(अचिन्हित दीर्घ दीर्घ)__entry->pblock,
		__entry->len,
		__entry->flags,
		__entry->ret)
);

#पूर्ण_अगर /* _TRACE_F2FS_H */

 /* This part must be outside protection */
#समावेश <trace/define_trace.h>
