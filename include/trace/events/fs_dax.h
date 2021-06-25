<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fs_dax

#अगर !defined(_TRACE_FS_DAX_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FS_DAX_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(dax_pmd_fault_class,
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf,
		pgoff_t max_pgoff, पूर्णांक result),
	TP_ARGS(inode, vmf, max_pgoff, result),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(अचिन्हित दीर्घ, vm_start)
		__field(अचिन्हित दीर्घ, vm_end)
		__field(अचिन्हित दीर्घ, vm_flags)
		__field(अचिन्हित दीर्घ, address)
		__field(pgoff_t, pgoff)
		__field(pgoff_t, max_pgoff)
		__field(dev_t, dev)
		__field(अचिन्हित पूर्णांक, flags)
		__field(पूर्णांक, result)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->vm_start = vmf->vma->vm_start;
		__entry->vm_end = vmf->vma->vm_end;
		__entry->vm_flags = vmf->vma->vm_flags;
		__entry->address = vmf->address;
		__entry->flags = vmf->flags;
		__entry->pgoff = vmf->pgoff;
		__entry->max_pgoff = max_pgoff;
		__entry->result = result;
	),
	TP_prपूर्णांकk("dev %d:%d ino %#lx %s %s address %#lx vm_start "
			"%#lx vm_end %#lx pgoff %#lx max_pgoff %#lx %s",
		MAJOR(__entry->dev),
		MINOR(__entry->dev),
		__entry->ino,
		__entry->vm_flags & VM_SHARED ? "shared" : "private",
		__prपूर्णांक_flags(__entry->flags, "|", FAULT_FLAG_TRACE),
		__entry->address,
		__entry->vm_start,
		__entry->vm_end,
		__entry->pgoff,
		__entry->max_pgoff,
		__prपूर्णांक_flags(__entry->result, "|", VM_FAULT_RESULT_TRACE)
	)
)

#घोषणा DEFINE_PMD_FAULT_EVENT(name) \
DEFINE_EVENT(dax_pmd_fault_class, name, \
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf, \
		pgoff_t max_pgoff, पूर्णांक result), \
	TP_ARGS(inode, vmf, max_pgoff, result))

DEFINE_PMD_FAULT_EVENT(dax_pmd_fault);
DEFINE_PMD_FAULT_EVENT(dax_pmd_fault_करोne);

DECLARE_EVENT_CLASS(dax_pmd_load_hole_class,
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf,
		काष्ठा page *zero_page,
		व्योम *radix_entry),
	TP_ARGS(inode, vmf, zero_page, radix_entry),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(अचिन्हित दीर्घ, vm_flags)
		__field(अचिन्हित दीर्घ, address)
		__field(काष्ठा page *, zero_page)
		__field(व्योम *, radix_entry)
		__field(dev_t, dev)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->vm_flags = vmf->vma->vm_flags;
		__entry->address = vmf->address;
		__entry->zero_page = zero_page;
		__entry->radix_entry = radix_entry;
	),
	TP_prपूर्णांकk("dev %d:%d ino %#lx %s address %#lx zero_page %p "
			"radix_entry %#lx",
		MAJOR(__entry->dev),
		MINOR(__entry->dev),
		__entry->ino,
		__entry->vm_flags & VM_SHARED ? "shared" : "private",
		__entry->address,
		__entry->zero_page,
		(अचिन्हित दीर्घ)__entry->radix_entry
	)
)

#घोषणा DEFINE_PMD_LOAD_HOLE_EVENT(name) \
DEFINE_EVENT(dax_pmd_load_hole_class, name, \
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf, \
		काष्ठा page *zero_page, व्योम *radix_entry), \
	TP_ARGS(inode, vmf, zero_page, radix_entry))

DEFINE_PMD_LOAD_HOLE_EVENT(dax_pmd_load_hole);
DEFINE_PMD_LOAD_HOLE_EVENT(dax_pmd_load_hole_fallback);

DECLARE_EVENT_CLASS(dax_pmd_insert_mapping_class,
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf,
		दीर्घ length, pfn_t pfn, व्योम *radix_entry),
	TP_ARGS(inode, vmf, length, pfn, radix_entry),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(अचिन्हित दीर्घ, vm_flags)
		__field(अचिन्हित दीर्घ, address)
		__field(दीर्घ, length)
		__field(u64, pfn_val)
		__field(व्योम *, radix_entry)
		__field(dev_t, dev)
		__field(पूर्णांक, ग_लिखो)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->vm_flags = vmf->vma->vm_flags;
		__entry->address = vmf->address;
		__entry->ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;
		__entry->length = length;
		__entry->pfn_val = pfn.val;
		__entry->radix_entry = radix_entry;
	),
	TP_prपूर्णांकk("dev %d:%d ino %#lx %s %s address %#lx length %#lx "
			"pfn %#llx %s radix_entry %#lx",
		MAJOR(__entry->dev),
		MINOR(__entry->dev),
		__entry->ino,
		__entry->vm_flags & VM_SHARED ? "shared" : "private",
		__entry->ग_लिखो ? "write" : "read",
		__entry->address,
		__entry->length,
		__entry->pfn_val & ~PFN_FLAGS_MASK,
		__prपूर्णांक_flags_u64(__entry->pfn_val & PFN_FLAGS_MASK, "|",
			PFN_FLAGS_TRACE),
		(अचिन्हित दीर्घ)__entry->radix_entry
	)
)

#घोषणा DEFINE_PMD_INSERT_MAPPING_EVENT(name) \
DEFINE_EVENT(dax_pmd_insert_mapping_class, name, \
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf, \
		दीर्घ length, pfn_t pfn, व्योम *radix_entry), \
	TP_ARGS(inode, vmf, length, pfn, radix_entry))

DEFINE_PMD_INSERT_MAPPING_EVENT(dax_pmd_insert_mapping);

DECLARE_EVENT_CLASS(dax_pte_fault_class,
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf, पूर्णांक result),
	TP_ARGS(inode, vmf, result),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(अचिन्हित दीर्घ, vm_flags)
		__field(अचिन्हित दीर्घ, address)
		__field(pgoff_t, pgoff)
		__field(dev_t, dev)
		__field(अचिन्हित पूर्णांक, flags)
		__field(पूर्णांक, result)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->vm_flags = vmf->vma->vm_flags;
		__entry->address = vmf->address;
		__entry->flags = vmf->flags;
		__entry->pgoff = vmf->pgoff;
		__entry->result = result;
	),
	TP_prपूर्णांकk("dev %d:%d ino %#lx %s %s address %#lx pgoff %#lx %s",
		MAJOR(__entry->dev),
		MINOR(__entry->dev),
		__entry->ino,
		__entry->vm_flags & VM_SHARED ? "shared" : "private",
		__prपूर्णांक_flags(__entry->flags, "|", FAULT_FLAG_TRACE),
		__entry->address,
		__entry->pgoff,
		__prपूर्णांक_flags(__entry->result, "|", VM_FAULT_RESULT_TRACE)
	)
)

#घोषणा DEFINE_PTE_FAULT_EVENT(name) \
DEFINE_EVENT(dax_pte_fault_class, name, \
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf, पूर्णांक result), \
	TP_ARGS(inode, vmf, result))

DEFINE_PTE_FAULT_EVENT(dax_pte_fault);
DEFINE_PTE_FAULT_EVENT(dax_pte_fault_करोne);
DEFINE_PTE_FAULT_EVENT(dax_load_hole);
DEFINE_PTE_FAULT_EVENT(dax_insert_pfn_mkग_लिखो_no_entry);
DEFINE_PTE_FAULT_EVENT(dax_insert_pfn_mkग_लिखो);

TRACE_EVENT(dax_insert_mapping,
	TP_PROTO(काष्ठा inode *inode, काष्ठा vm_fault *vmf, व्योम *radix_entry),
	TP_ARGS(inode, vmf, radix_entry),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(अचिन्हित दीर्घ, vm_flags)
		__field(अचिन्हित दीर्घ, address)
		__field(व्योम *, radix_entry)
		__field(dev_t, dev)
		__field(पूर्णांक, ग_लिखो)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->vm_flags = vmf->vma->vm_flags;
		__entry->address = vmf->address;
		__entry->ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;
		__entry->radix_entry = radix_entry;
	),
	TP_prपूर्णांकk("dev %d:%d ino %#lx %s %s address %#lx radix_entry %#lx",
		MAJOR(__entry->dev),
		MINOR(__entry->dev),
		__entry->ino,
		__entry->vm_flags & VM_SHARED ? "shared" : "private",
		__entry->ग_लिखो ? "write" : "read",
		__entry->address,
		(अचिन्हित दीर्घ)__entry->radix_entry
	)
)

DECLARE_EVENT_CLASS(dax_ग_लिखोback_range_class,
	TP_PROTO(काष्ठा inode *inode, pgoff_t start_index, pgoff_t end_index),
	TP_ARGS(inode, start_index, end_index),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(pgoff_t, start_index)
		__field(pgoff_t, end_index)
		__field(dev_t, dev)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->start_index = start_index;
		__entry->end_index = end_index;
	),
	TP_prपूर्णांकk("dev %d:%d ino %#lx pgoff %#lx-%#lx",
		MAJOR(__entry->dev),
		MINOR(__entry->dev),
		__entry->ino,
		__entry->start_index,
		__entry->end_index
	)
)

#घोषणा DEFINE_WRITEBACK_RANGE_EVENT(name) \
DEFINE_EVENT(dax_ग_लिखोback_range_class, name, \
	TP_PROTO(काष्ठा inode *inode, pgoff_t start_index, pgoff_t end_index),\
	TP_ARGS(inode, start_index, end_index))

DEFINE_WRITEBACK_RANGE_EVENT(dax_ग_लिखोback_range);
DEFINE_WRITEBACK_RANGE_EVENT(dax_ग_लिखोback_range_करोne);

TRACE_EVENT(dax_ग_लिखोback_one,
	TP_PROTO(काष्ठा inode *inode, pgoff_t pgoff, pgoff_t pglen),
	TP_ARGS(inode, pgoff, pglen),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(pgoff_t, pgoff)
		__field(pgoff_t, pglen)
		__field(dev_t, dev)
	),
	TP_fast_assign(
		__entry->dev = inode->i_sb->s_dev;
		__entry->ino = inode->i_ino;
		__entry->pgoff = pgoff;
		__entry->pglen = pglen;
	),
	TP_prपूर्णांकk("dev %d:%d ino %#lx pgoff %#lx pglen %#lx",
		MAJOR(__entry->dev),
		MINOR(__entry->dev),
		__entry->ino,
		__entry->pgoff,
		__entry->pglen
	)
)

#पूर्ण_अगर /* _TRACE_FS_DAX_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
