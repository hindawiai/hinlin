<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM filemap

#अगर !defined(_TRACE_खाताMAP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_खाताMAP_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/mm.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/device.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/errseq.h>

DECLARE_EVENT_CLASS(mm_filemap_op_page_cache,

	TP_PROTO(काष्ठा page *page),

	TP_ARGS(page),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, pfn)
		__field(अचिन्हित दीर्घ, i_ino)
		__field(अचिन्हित दीर्घ, index)
		__field(dev_t, s_dev)
	),

	TP_fast_assign(
		__entry->pfn = page_to_pfn(page);
		__entry->i_ino = page->mapping->host->i_ino;
		__entry->index = page->index;
		अगर (page->mapping->host->i_sb)
			__entry->s_dev = page->mapping->host->i_sb->s_dev;
		अन्यथा
			__entry->s_dev = page->mapping->host->i_rdev;
	),

	TP_prपूर्णांकk("dev %d:%d ino %lx page=%p pfn=%lu ofs=%lu",
		MAJOR(__entry->s_dev), MINOR(__entry->s_dev),
		__entry->i_ino,
		pfn_to_page(__entry->pfn),
		__entry->pfn,
		__entry->index << PAGE_SHIFT)
);

DEFINE_EVENT(mm_filemap_op_page_cache, mm_filemap_delete_from_page_cache,
	TP_PROTO(काष्ठा page *page),
	TP_ARGS(page)
	);

DEFINE_EVENT(mm_filemap_op_page_cache, mm_filemap_add_to_page_cache,
	TP_PROTO(काष्ठा page *page),
	TP_ARGS(page)
	);

TRACE_EVENT(filemap_set_wb_err,
		TP_PROTO(काष्ठा address_space *mapping, errseq_t eseq),

		TP_ARGS(mapping, eseq),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, i_ino)
			__field(dev_t, s_dev)
			__field(errseq_t, errseq)
		),

		TP_fast_assign(
			__entry->i_ino = mapping->host->i_ino;
			__entry->errseq = eseq;
			अगर (mapping->host->i_sb)
				__entry->s_dev = mapping->host->i_sb->s_dev;
			अन्यथा
				__entry->s_dev = mapping->host->i_rdev;
		),

		TP_prपूर्णांकk("dev=%d:%d ino=0x%lx errseq=0x%x",
			MAJOR(__entry->s_dev), MINOR(__entry->s_dev),
			__entry->i_ino, __entry->errseq)
);

TRACE_EVENT(file_check_and_advance_wb_err,
		TP_PROTO(काष्ठा file *file, errseq_t old),

		TP_ARGS(file, old),

		TP_STRUCT__entry(
			__field(काष्ठा file *, file)
			__field(अचिन्हित दीर्घ, i_ino)
			__field(dev_t, s_dev)
			__field(errseq_t, old)
			__field(errseq_t, new)
		),

		TP_fast_assign(
			__entry->file = file;
			__entry->i_ino = file->f_mapping->host->i_ino;
			अगर (file->f_mapping->host->i_sb)
				__entry->s_dev =
					file->f_mapping->host->i_sb->s_dev;
			अन्यथा
				__entry->s_dev =
					file->f_mapping->host->i_rdev;
			__entry->old = old;
			__entry->new = file->f_wb_err;
		),

		TP_prपूर्णांकk("file=%p dev=%d:%d ino=0x%lx old=0x%x new=0x%x",
			__entry->file, MAJOR(__entry->s_dev),
			MINOR(__entry->s_dev), __entry->i_ino, __entry->old,
			__entry->new)
);
#पूर्ण_अगर /* _TRACE_खाताMAP_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
