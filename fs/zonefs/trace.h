<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zonefs fileप्रणाली driver tracepoपूर्णांकs.
 *
 * Copyright (C) 2021 Western Digital Corporation or its affiliates.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM zonefs

#अगर !defined(_TRACE_ZONEFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_ZONEFS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>
#समावेश <linux/blkdev.h>

#समावेश "zonefs.h"

#घोषणा show_dev(dev) MAJOR(dev), MINOR(dev)

TRACE_EVENT(zonefs_zone_mgmt,
	    TP_PROTO(काष्ठा inode *inode, क्रमागत req_opf op),
	    TP_ARGS(inode, op),
	    TP_STRUCT__entry(
			     __field(dev_t, dev)
			     __field(ino_t, ino)
			     __field(पूर्णांक, op)
			     __field(sector_t, sector)
			     __field(sector_t, nr_sectors)
	    ),
	    TP_fast_assign(
			   __entry->dev = inode->i_sb->s_dev;
			   __entry->ino = inode->i_ino;
			   __entry->op = op;
			   __entry->sector = ZONEFS_I(inode)->i_zsector;
			   __entry->nr_sectors =
				   ZONEFS_I(inode)->i_zone_size >> SECTOR_SHIFT;
	    ),
	    TP_prपूर्णांकk("bdev=(%d,%d), ino=%lu op=%s, sector=%llu, nr_sectors=%llu",
		      show_dev(__entry->dev), (अचिन्हित दीर्घ)__entry->ino,
		      blk_op_str(__entry->op), __entry->sector,
		      __entry->nr_sectors
	    )
);

TRACE_EVENT(zonefs_file_dio_append,
	    TP_PROTO(काष्ठा inode *inode, sमाप_प्रकार size, sमाप_प्रकार ret),
	    TP_ARGS(inode, size, ret),
	    TP_STRUCT__entry(
			     __field(dev_t, dev)
			     __field(ino_t, ino)
			     __field(sector_t, sector)
			     __field(sमाप_प्रकार, size)
			     __field(loff_t, wpoffset)
			     __field(sमाप_प्रकार, ret)
	    ),
	    TP_fast_assign(
			   __entry->dev = inode->i_sb->s_dev;
			   __entry->ino = inode->i_ino;
			   __entry->sector = ZONEFS_I(inode)->i_zsector;
			   __entry->size = size;
			   __entry->wpoffset = ZONEFS_I(inode)->i_wpoffset;
			   __entry->ret = ret;
	    ),
	    TP_prपूर्णांकk("bdev=(%d, %d), ino=%lu, sector=%llu, size=%zu, wpoffset=%llu, ret=%zu",
		      show_dev(__entry->dev), (अचिन्हित दीर्घ)__entry->ino,
		      __entry->sector, __entry->size, __entry->wpoffset,
		      __entry->ret
	    )
);

TRACE_EVENT(zonefs_iomap_begin,
	    TP_PROTO(काष्ठा inode *inode, काष्ठा iomap *iomap),
	    TP_ARGS(inode, iomap),
	    TP_STRUCT__entry(
			     __field(dev_t, dev)
			     __field(ino_t, ino)
			     __field(u64, addr)
			     __field(loff_t, offset)
			     __field(u64, length)
	    ),
	    TP_fast_assign(
			   __entry->dev = inode->i_sb->s_dev;
			   __entry->ino = inode->i_ino;
			   __entry->addr = iomap->addr;
			   __entry->offset = iomap->offset;
			   __entry->length = iomap->length;
	    ),
	    TP_prपूर्णांकk("bdev=(%d,%d), ino=%lu, addr=%llu, offset=%llu, length=%llu",
		      show_dev(__entry->dev), (अचिन्हित दीर्घ)__entry->ino,
		      __entry->addr, __entry->offset, __entry->length
	    )
);

#पूर्ण_अगर /* _TRACE_ZONEFS_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
