<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM erofs

#अगर !defined(_TRACE_EROFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_EROFS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/fs.h>

काष्ठा erofs_map_blocks;

#घोषणा show_dev(dev)		MAJOR(dev), MINOR(dev)
#घोषणा show_dev_nid(entry)	show_dev(entry->dev), entry->nid

#घोषणा show_file_type(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु 0,		"FILE" पूर्ण,				\
		अणु 1,		"DIR" पूर्ण)

#घोषणा show_map_flags(flags) __prपूर्णांक_flags(flags, "|",	\
	अणु EROFS_GET_BLOCKS_RAW,	"RAW" पूर्ण)

#घोषणा show_mflags(flags) __prपूर्णांक_flags(flags, "",	\
	अणु EROFS_MAP_MAPPED,	"M" पूर्ण,			\
	अणु EROFS_MAP_META,	"I" पूर्ण,			\
	अणु EROFS_MAP_ZIPPED,	"Z" पूर्ण)

TRACE_EVENT(erofs_lookup,

	TP_PROTO(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags),

	TP_ARGS(dir, dentry, flags),

	TP_STRUCT__entry(
		__field(dev_t,		dev	)
		__field(erofs_nid_t,	nid	)
		__field(स्थिर अक्षर *,	name	)
		__field(अचिन्हित पूर्णांक,	flags	)
	),

	TP_fast_assign(
		__entry->dev	= dir->i_sb->s_dev;
		__entry->nid	= EROFS_I(dir)->nid;
		__entry->name	= dentry->d_name.name;
		__entry->flags	= flags;
	),

	TP_prपूर्णांकk("dev = (%d,%d), pnid = %llu, name:%s, flags:%x",
		show_dev_nid(__entry),
		__entry->name,
		__entry->flags)
);

TRACE_EVENT(erofs_fill_inode,
	TP_PROTO(काष्ठा inode *inode, पूर्णांक isdir),
	TP_ARGS(inode, isdir),

	TP_STRUCT__entry(
		__field(dev_t,		dev	)
		__field(erofs_nid_t,	nid	)
		__field(erofs_blk_t,	blkaddr )
		__field(अचिन्हित पूर्णांक,	ofs	)
		__field(पूर्णांक,		isdir	)
	),

	TP_fast_assign(
		__entry->dev		= inode->i_sb->s_dev;
		__entry->nid		= EROFS_I(inode)->nid;
		__entry->blkaddr	= erofs_blknr(iloc(EROFS_I_SB(inode), __entry->nid));
		__entry->ofs		= erofs_blkoff(iloc(EROFS_I_SB(inode), __entry->nid));
		__entry->isdir		= isdir;
	),

	TP_prपूर्णांकk("dev = (%d,%d), nid = %llu, blkaddr %u ofs %u, isdir %d",
		  show_dev_nid(__entry),
		  __entry->blkaddr, __entry->ofs,
		  __entry->isdir)
);

TRACE_EVENT(erofs_पढ़ोpage,

	TP_PROTO(काष्ठा page *page, bool raw),

	TP_ARGS(page, raw),

	TP_STRUCT__entry(
		__field(dev_t,		dev	)
		__field(erofs_nid_t,    nid     )
		__field(पूर्णांक,		dir	)
		__field(pgoff_t,	index	)
		__field(पूर्णांक,		uptodate)
		__field(bool,		raw	)
	),

	TP_fast_assign(
		__entry->dev	= page->mapping->host->i_sb->s_dev;
		__entry->nid	= EROFS_I(page->mapping->host)->nid;
		__entry->dir	= S_ISसूची(page->mapping->host->i_mode);
		__entry->index	= page->index;
		__entry->uptodate = PageUptodate(page);
		__entry->raw = raw;
	),

	TP_prपूर्णांकk("dev = (%d,%d), nid = %llu, %s, index = %lu, uptodate = %d "
		"raw = %d",
		show_dev_nid(__entry),
		show_file_type(__entry->dir),
		(अचिन्हित दीर्घ)__entry->index,
		__entry->uptodate,
		__entry->raw)
);

TRACE_EVENT(erofs_पढ़ोpages,

	TP_PROTO(काष्ठा inode *inode, pgoff_t start, अचिन्हित पूर्णांक nrpage,
		bool raw),

	TP_ARGS(inode, start, nrpage, raw),

	TP_STRUCT__entry(
		__field(dev_t,		dev	)
		__field(erofs_nid_t,	nid	)
		__field(pgoff_t,	start	)
		__field(अचिन्हित पूर्णांक,	nrpage	)
		__field(bool,		raw	)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->nid	= EROFS_I(inode)->nid;
		__entry->start	= start;
		__entry->nrpage	= nrpage;
		__entry->raw	= raw;
	),

	TP_prपूर्णांकk("dev = (%d,%d), nid = %llu, start = %lu nrpage = %u raw = %d",
		show_dev_nid(__entry),
		(अचिन्हित दीर्घ)__entry->start,
		__entry->nrpage,
		__entry->raw)
);

DECLARE_EVENT_CLASS(erofs__map_blocks_enter,
	TP_PROTO(काष्ठा inode *inode, काष्ठा erofs_map_blocks *map,
		 अचिन्हित पूर्णांक flags),

	TP_ARGS(inode, map, flags),

	TP_STRUCT__entry(
		__field(	dev_t,		dev		)
		__field(	erofs_nid_t,	nid		)
		__field(	erofs_off_t,	la		)
		__field(	u64,		llen		)
		__field(	अचिन्हित पूर्णांक,	flags		)
	),

	TP_fast_assign(
		__entry->dev    = inode->i_sb->s_dev;
		__entry->nid    = EROFS_I(inode)->nid;
		__entry->la	= map->m_la;
		__entry->llen	= map->m_llen;
		__entry->flags	= flags;
	),

	TP_prपूर्णांकk("dev = (%d,%d), nid = %llu, la %llu llen %llu flags %s",
		  show_dev_nid(__entry),
		  __entry->la, __entry->llen,
		  __entry->flags ? show_map_flags(__entry->flags) : "NULL")
);

DEFINE_EVENT(erofs__map_blocks_enter, erofs_map_blocks_flaपंचांगode_enter,
	TP_PROTO(काष्ठा inode *inode, काष्ठा erofs_map_blocks *map,
		 अचिन्हित flags),

	TP_ARGS(inode, map, flags)
);

DEFINE_EVENT(erofs__map_blocks_enter, z_erofs_map_blocks_iter_enter,
	TP_PROTO(काष्ठा inode *inode, काष्ठा erofs_map_blocks *map,
		 अचिन्हित पूर्णांक flags),

	TP_ARGS(inode, map, flags)
);

DECLARE_EVENT_CLASS(erofs__map_blocks_निकास,
	TP_PROTO(काष्ठा inode *inode, काष्ठा erofs_map_blocks *map,
		 अचिन्हित पूर्णांक flags, पूर्णांक ret),

	TP_ARGS(inode, map, flags, ret),

	TP_STRUCT__entry(
		__field(	dev_t,		dev		)
		__field(	erofs_nid_t,	nid		)
		__field(        अचिन्हित पूर्णांक,   flags           )
		__field(	erofs_off_t,	la		)
		__field(	erofs_off_t,	pa		)
		__field(	u64,		llen		)
		__field(	u64,		plen		)
		__field(        अचिन्हित पूर्णांक,	mflags		)
		__field(	पूर्णांक,		ret		)
	),

	TP_fast_assign(
		__entry->dev    = inode->i_sb->s_dev;
		__entry->nid    = EROFS_I(inode)->nid;
		__entry->flags	= flags;
		__entry->la	= map->m_la;
		__entry->pa	= map->m_pa;
		__entry->llen	= map->m_llen;
		__entry->plen	= map->m_plen;
		__entry->mflags	= map->m_flags;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("dev = (%d,%d), nid = %llu, flags %s "
		  "la %llu pa %llu llen %llu plen %llu mflags %s ret %d",
		  show_dev_nid(__entry),
		  __entry->flags ? show_map_flags(__entry->flags) : "NULL",
		  __entry->la, __entry->pa, __entry->llen, __entry->plen,
		  show_mflags(__entry->mflags), __entry->ret)
);

DEFINE_EVENT(erofs__map_blocks_निकास, erofs_map_blocks_flaपंचांगode_निकास,
	TP_PROTO(काष्ठा inode *inode, काष्ठा erofs_map_blocks *map,
		 अचिन्हित flags, पूर्णांक ret),

	TP_ARGS(inode, map, flags, ret)
);

DEFINE_EVENT(erofs__map_blocks_निकास, z_erofs_map_blocks_iter_निकास,
	TP_PROTO(काष्ठा inode *inode, काष्ठा erofs_map_blocks *map,
		 अचिन्हित पूर्णांक flags, पूर्णांक ret),

	TP_ARGS(inode, map, flags, ret)
);

TRACE_EVENT(erofs_destroy_inode,
	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry(
		__field(	dev_t,		dev		)
		__field(	erofs_nid_t,	nid		)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->nid	= EROFS_I(inode)->nid;
	),

	TP_prपूर्णांकk("dev = (%d,%d), nid = %llu", show_dev_nid(__entry))
);

#पूर्ण_अगर /* _TRACE_EROFS_H */

 /* This part must be outside protection */
#समावेश <trace/define_trace.h>
