<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2009-2019 Christoph Hellwig
 *
 * NOTE: none of these tracepoपूर्णांकs shall be consider a stable kernel ABI
 * as they can change at any समय.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iomap

#अगर !defined(_IOMAP_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _IOMAP_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा inode;

DECLARE_EVENT_CLASS(iomap_पढ़ोpage_class,
	TP_PROTO(काष्ठा inode *inode, पूर्णांक nr_pages),
	TP_ARGS(inode, nr_pages),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(u64, ino)
		__field(पूर्णांक, nr_pages)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->nr_pages = nr_pages;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx nr_pages %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __entry->nr_pages)
)

#घोषणा DEFINE_READPAGE_EVENT(name)		\
DEFINE_EVENT(iomap_पढ़ोpage_class, name,	\
	TP_PROTO(काष्ठा inode *inode, पूर्णांक nr_pages), \
	TP_ARGS(inode, nr_pages))
DEFINE_READPAGE_EVENT(iomap_पढ़ोpage);
DEFINE_READPAGE_EVENT(iomap_पढ़ोahead);

DECLARE_EVENT_CLASS(iomap_range_class,
	TP_PROTO(काष्ठा inode *inode, अचिन्हित दीर्घ off, अचिन्हित पूर्णांक len),
	TP_ARGS(inode, off, len),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(u64, ino)
		__field(loff_t, size)
		__field(अचिन्हित दीर्घ, offset)
		__field(अचिन्हित पूर्णांक, length)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->size = i_size_पढ़ो(inode);
		__entry->offset = off;
		__entry->length = len;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx size 0x%llx offset %lx "
		  "length %x",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __entry->size,
		  __entry->offset,
		  __entry->length)
)

#घोषणा DEFINE_RANGE_EVENT(name)		\
DEFINE_EVENT(iomap_range_class, name,	\
	TP_PROTO(काष्ठा inode *inode, अचिन्हित दीर्घ off, अचिन्हित पूर्णांक len),\
	TP_ARGS(inode, off, len))
DEFINE_RANGE_EVENT(iomap_ग_लिखोpage);
DEFINE_RANGE_EVENT(iomap_releasepage);
DEFINE_RANGE_EVENT(iomap_invalidatepage);
DEFINE_RANGE_EVENT(iomap_dio_invalidate_fail);

#घोषणा IOMAP_TYPE_STRINGS \
	अणु IOMAP_HOLE,		"HOLE" पूर्ण, \
	अणु IOMAP_DELALLOC,	"DELALLOC" पूर्ण, \
	अणु IOMAP_MAPPED,		"MAPPED" पूर्ण, \
	अणु IOMAP_UNWRITTEN,	"UNWRITTEN" पूर्ण, \
	अणु IOMAP_INLINE,		"INLINE" पूर्ण

#घोषणा IOMAP_FLAGS_STRINGS \
	अणु IOMAP_WRITE,		"WRITE" पूर्ण, \
	अणु IOMAP_ZERO,		"ZERO" पूर्ण, \
	अणु IOMAP_REPORT,		"REPORT" पूर्ण, \
	अणु IOMAP_FAULT,		"FAULT" पूर्ण, \
	अणु IOMAP_सूचीECT,		"DIRECT" पूर्ण, \
	अणु IOMAP_NOWAIT,		"NOWAIT" पूर्ण

#घोषणा IOMAP_F_FLAGS_STRINGS \
	अणु IOMAP_F_NEW,		"NEW" पूर्ण, \
	अणु IOMAP_F_सूचीTY,	"DIRTY" पूर्ण, \
	अणु IOMAP_F_SHARED,	"SHARED" पूर्ण, \
	अणु IOMAP_F_MERGED,	"MERGED" पूर्ण, \
	अणु IOMAP_F_BUFFER_HEAD,	"BH" पूर्ण, \
	अणु IOMAP_F_SIZE_CHANGED,	"SIZE_CHANGED" पूर्ण

DECLARE_EVENT_CLASS(iomap_class,
	TP_PROTO(काष्ठा inode *inode, काष्ठा iomap *iomap),
	TP_ARGS(inode, iomap),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(u64, ino)
		__field(u64, addr)
		__field(loff_t, offset)
		__field(u64, length)
		__field(u16, type)
		__field(u16, flags)
		__field(dev_t, bdev)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->addr = iomap->addr;
		__entry->offset = iomap->offset;
		__entry->length = iomap->length;
		__entry->type = iomap->type;
		__entry->flags = iomap->flags;
		__entry->bdev = iomap->bdev ? iomap->bdev->bd_dev : 0;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx bdev %d:%d addr %lld offset %lld "
		  "length %llu type %s flags %s",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  MAJOR(__entry->bdev), MINOR(__entry->bdev),
		  __entry->addr,
		  __entry->offset,
		  __entry->length,
		  __prपूर्णांक_symbolic(__entry->type, IOMAP_TYPE_STRINGS),
		  __prपूर्णांक_flags(__entry->flags, "|", IOMAP_F_FLAGS_STRINGS))
)

#घोषणा DEFINE_IOMAP_EVENT(name)		\
DEFINE_EVENT(iomap_class, name,	\
	TP_PROTO(काष्ठा inode *inode, काष्ठा iomap *iomap), \
	TP_ARGS(inode, iomap))
DEFINE_IOMAP_EVENT(iomap_apply_dsपंचांगap);
DEFINE_IOMAP_EVENT(iomap_apply_srcmap);

TRACE_EVENT(iomap_apply,
	TP_PROTO(काष्ठा inode *inode, loff_t pos, loff_t length,
		अचिन्हित पूर्णांक flags, स्थिर व्योम *ops, व्योम *actor,
		अचिन्हित दीर्घ caller),
	TP_ARGS(inode, pos, length, flags, ops, actor, caller),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(u64, ino)
		__field(loff_t, pos)
		__field(loff_t, length)
		__field(अचिन्हित पूर्णांक, flags)
		__field(स्थिर व्योम *, ops)
		__field(व्योम *, actor)
		__field(अचिन्हित दीर्घ, caller)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->pos = pos;
		__entry->length = length;
		__entry->flags = flags;
		__entry->ops = ops;
		__entry->actor = actor;
		__entry->caller = caller;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx pos %lld length %lld flags %s (0x%x) "
		  "ops %ps caller %pS actor %ps",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		   __entry->ino,
		   __entry->pos,
		   __entry->length,
		   __prपूर्णांक_flags(__entry->flags, "|", IOMAP_FLAGS_STRINGS),
		   __entry->flags,
		   __entry->ops,
		   (व्योम *)__entry->caller,
		   __entry->actor)
);

#पूर्ण_अगर /* _IOMAP_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
