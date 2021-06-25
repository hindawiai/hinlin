<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mmap

#अगर !defined(_TRACE_MMAP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_MMAP_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(vm_unmapped_area,

	TP_PROTO(अचिन्हित दीर्घ addr, काष्ठा vm_unmapped_area_info *info),

	TP_ARGS(addr, info),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ,	addr)
		__field(अचिन्हित दीर्घ,	total_vm)
		__field(अचिन्हित दीर्घ,	flags)
		__field(अचिन्हित दीर्घ,	length)
		__field(अचिन्हित दीर्घ,	low_limit)
		__field(अचिन्हित दीर्घ,	high_limit)
		__field(अचिन्हित दीर्घ,	align_mask)
		__field(अचिन्हित दीर्घ,	align_offset)
	),

	TP_fast_assign(
		__entry->addr = addr;
		__entry->total_vm = current->mm->total_vm;
		__entry->flags = info->flags;
		__entry->length = info->length;
		__entry->low_limit = info->low_limit;
		__entry->high_limit = info->high_limit;
		__entry->align_mask = info->align_mask;
		__entry->align_offset = info->align_offset;
	),

	TP_prपूर्णांकk("addr=0x%lx err=%ld total_vm=0x%lx flags=0x%lx len=0x%lx lo=0x%lx hi=0x%lx mask=0x%lx ofs=0x%lx\n",
		IS_ERR_VALUE(__entry->addr) ? 0 : __entry->addr,
		IS_ERR_VALUE(__entry->addr) ? __entry->addr : 0,
		__entry->total_vm, __entry->flags, __entry->length,
		__entry->low_limit, __entry->high_limit, __entry->align_mask,
		__entry->align_offset)
);
#पूर्ण_अगर

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
