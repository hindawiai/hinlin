<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SYMBOL_CONF
#घोषणा __PERF_SYMBOL_CONF 1

#समावेश <stdbool.h>

काष्ठा strlist;
काष्ठा पूर्णांकlist;

काष्ठा symbol_conf अणु
	bool		nanosecs;
	अचिन्हित लघु	priv_size;
	bool		try_vmlinux_path,
			init_annotation,
			क्रमce,
			ignore_vmlinux,
			ignore_vmlinux_buildid,
			show_kernel_path,
			use_modules,
			allow_aliases,
			sort_by_name,
			show_nr_samples,
			show_total_period,
			use_callchain,
			cumulate_callchain,
			show_branchflag_count,
			exclude_other,
			show_cpu_utilization,
			initialized,
			kptr_restrict,
			event_group,
			demangle,
			demangle_kernel,
			filter_relative,
			show_hist_headers,
			branch_callstack,
			has_filter,
			show_ref_callgraph,
			hide_unresolved,
			raw_trace,
			report_hierarchy,
			report_block,
			report_inभागidual_block,
			अंतरभूत_name,
			disable_add2line_warn,
			buildid_mmap2;
	स्थिर अक्षर	*vmlinux_name,
			*kallsyms_name,
			*source_prefix,
			*field_sep,
			*graph_function;
	स्थिर अक्षर	*शेष_guest_vmlinux_name,
			*शेष_guest_kallsyms,
			*शेष_guest_modules;
	स्थिर अक्षर	*guesपंचांगount;
	स्थिर अक्षर	*dso_list_str,
			*comm_list_str,
			*pid_list_str,
			*tid_list_str,
			*sym_list_str,
			*col_width_list_str,
			*bt_stop_list_str;
	अचिन्हित दीर्घ	समय_quantum;
       काष्ठा strlist	*dso_list,
			*comm_list,
			*sym_list,
			*dso_from_list,
			*dso_to_list,
			*sym_from_list,
			*sym_to_list,
			*bt_stop_list;
	काष्ठा पूर्णांकlist	*pid_list,
			*tid_list,
			*addr_list;
	स्थिर अक्षर	*symfs;
	पूर्णांक		res_sample;
	पूर्णांक		pad_output_len_dso;
	पूर्णांक		group_sort_idx;
	पूर्णांक		addr_range;
पूर्ण;

बाह्य काष्ठा symbol_conf symbol_conf;

#पूर्ण_अगर // __PERF_SYMBOL_CONF
