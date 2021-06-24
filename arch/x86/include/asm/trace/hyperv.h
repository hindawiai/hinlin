<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hyperv

#अगर !defined(_TRACE_HYPERV_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_HYPERV_H

#समावेश <linux/tracepoपूर्णांक.h>

#अगर IS_ENABLED(CONFIG_HYPERV)

TRACE_EVENT(hyperv_mmu_flush_tlb_multi,
	    TP_PROTO(स्थिर काष्ठा cpumask *cpus,
		     स्थिर काष्ठा flush_tlb_info *info),
	    TP_ARGS(cpus, info),
	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, ncpus)
		    __field(काष्ठा mm_काष्ठा *, mm)
		    __field(अचिन्हित दीर्घ, addr)
		    __field(अचिन्हित दीर्घ, end)
		    ),
	    TP_fast_assign(__entry->ncpus = cpumask_weight(cpus);
			   __entry->mm = info->mm;
			   __entry->addr = info->start;
			   __entry->end = info->end;
		    ),
	    TP_prपूर्णांकk("ncpus %d mm %p addr %lx, end %lx",
		      __entry->ncpus, __entry->mm,
		      __entry->addr, __entry->end)
	);

TRACE_EVENT(hyperv_nested_flush_guest_mapping,
	    TP_PROTO(u64 as, पूर्णांक ret),
	    TP_ARGS(as, ret),

	    TP_STRUCT__entry(
		    __field(u64, as)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(__entry->as = as;
			   __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("address space %llx ret %d", __entry->as, __entry->ret)
	);

TRACE_EVENT(hyperv_nested_flush_guest_mapping_range,
	    TP_PROTO(u64 as, पूर्णांक ret),
	    TP_ARGS(as, ret),

	    TP_STRUCT__entry(
		    __field(u64, as)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(__entry->as = as;
			   __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("address space %llx ret %d", __entry->as, __entry->ret)
	);

TRACE_EVENT(hyperv_send_ipi_mask,
	    TP_PROTO(स्थिर काष्ठा cpumask *cpus,
		     पूर्णांक vector),
	    TP_ARGS(cpus, vector),
	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, ncpus)
		    __field(पूर्णांक, vector)
		    ),
	    TP_fast_assign(__entry->ncpus = cpumask_weight(cpus);
			   __entry->vector = vector;
		    ),
	    TP_prपूर्णांकk("ncpus %d vector %x",
		      __entry->ncpus, __entry->vector)
	);

TRACE_EVENT(hyperv_send_ipi_one,
	    TP_PROTO(पूर्णांक cpu,
		     पूर्णांक vector),
	    TP_ARGS(cpu, vector),
	    TP_STRUCT__entry(
		    __field(पूर्णांक, cpu)
		    __field(पूर्णांक, vector)
		    ),
	    TP_fast_assign(__entry->cpu = cpu;
			   __entry->vector = vector;
		    ),
	    TP_prपूर्णांकk("cpu %d vector %x",
		      __entry->cpu, __entry->vector)
	);

#पूर्ण_अगर /* CONFIG_HYPERV */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH यंत्र/trace/
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता hyperv
#पूर्ण_अगर /* _TRACE_HYPERV_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
