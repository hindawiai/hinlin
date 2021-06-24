<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SORT_H
#घोषणा __PERF_SORT_H
#समावेश <regex.h>
#समावेश <stdbool.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश "map_symbol.h"
#समावेश "symbol_conf.h"
#समावेश "callchain.h"
#समावेश "values.h"
#समावेश "hist.h"
#समावेश "stat.h"
#समावेश "spark.h"

काष्ठा option;
काष्ठा thपढ़ो;

बाह्य regex_t parent_regex;
बाह्य स्थिर अक्षर *sort_order;
बाह्य स्थिर अक्षर *field_order;
बाह्य स्थिर अक्षर शेष_parent_pattern[];
बाह्य स्थिर अक्षर *parent_pattern;
बाह्य स्थिर अक्षर *शेष_sort_order;
बाह्य regex_t ignore_callees_regex;
बाह्य पूर्णांक have_ignore_callees;
बाह्य क्रमागत sort_mode sort__mode;
बाह्य काष्ठा sort_entry sort_comm;
बाह्य काष्ठा sort_entry sort_dso;
बाह्य काष्ठा sort_entry sort_sym;
बाह्य काष्ठा sort_entry sort_parent;
बाह्य काष्ठा sort_entry sort_dso_from;
बाह्य काष्ठा sort_entry sort_dso_to;
बाह्य काष्ठा sort_entry sort_sym_from;
बाह्य काष्ठा sort_entry sort_sym_to;
बाह्य काष्ठा sort_entry sort_srcline;
बाह्य क्रमागत sort_type sort__first_dimension;
बाह्य स्थिर अक्षर शेष_mem_sort_order[];

काष्ठा res_sample अणु
	u64 समय;
	पूर्णांक cpu;
	पूर्णांक tid;
पूर्ण;

काष्ठा he_stat अणु
	u64			period;
	u64			period_sys;
	u64			period_us;
	u64			period_guest_sys;
	u64			period_guest_us;
	u64			weight;
	u64			ins_lat;
	u64			p_stage_cyc;
	u32			nr_events;
पूर्ण;

काष्ठा namespace_id अणु
	u64			dev;
	u64			ino;
पूर्ण;

काष्ठा hist_entry_dअगरf अणु
	bool	computed;
	जोड़ अणु
		/* PERF_HPP__DELTA */
		द्विगुन	period_ratio_delta;

		/* PERF_HPP__RATIO */
		द्विगुन	period_ratio;

		/* HISTC_WEIGHTED_DIFF */
		s64	wdअगरf;

		/* PERF_HPP_DIFF__CYCLES */
		s64	cycles;
	पूर्ण;
	काष्ठा stats	stats;
	अचिन्हित दीर्घ	svals[NUM_SPARKS];
पूर्ण;

काष्ठा hist_entry_ops अणु
	व्योम	*(*new)(माप_प्रकार size);
	व्योम	(*मुक्त)(व्योम *ptr);
पूर्ण;

/**
 * काष्ठा hist_entry - histogram entry
 *
 * @row_offset - offset from the first callchain expanded to appear on screen
 * @nr_rows - rows expanded in callchain, recalculated on folding/unfolding
 */
काष्ठा hist_entry अणु
	काष्ठा rb_node		rb_node_in;
	काष्ठा rb_node		rb_node;
	जोड़ अणु
		काष्ठा list_head node;
		काष्ठा list_head head;
	पूर्ण pairs;
	काष्ठा he_stat		stat;
	काष्ठा he_stat		*stat_acc;
	काष्ठा map_symbol	ms;
	काष्ठा thपढ़ो		*thपढ़ो;
	काष्ठा comm		*comm;
	काष्ठा namespace_id	cgroup_id;
	u64			cgroup;
	u64			ip;
	u64			transaction;
	s32			socket;
	s32			cpu;
	u64			code_page_size;
	u8			cpumode;
	u8			depth;

	/* We are added by hists__add_dummy_entry. */
	bool			dummy;
	bool			leaf;

	अक्षर			level;
	u8			filtered;

	u16			callchain_size;
	जोड़ अणु
		/*
		 * Since perf dअगरf only supports the stdio output, TUI
		 * fields are only accessed from perf report (or perf
		 * top).  So make it a जोड़ to reduce memory usage.
		 */
		काष्ठा hist_entry_dअगरf	dअगरf;
		काष्ठा /* क्रम TUI */ अणु
			u16	row_offset;
			u16	nr_rows;
			bool	init_have_children;
			bool	unfolded;
			bool	has_children;
			bool	has_no_entry;
		पूर्ण;
	पूर्ण;
	अक्षर			*srcline;
	अक्षर			*srcfile;
	काष्ठा symbol		*parent;
	काष्ठा branch_info	*branch_info;
	दीर्घ			समय;
	काष्ठा hists		*hists;
	काष्ठा mem_info		*mem_info;
	काष्ठा block_info	*block_info;
	व्योम			*raw_data;
	u32			raw_size;
	पूर्णांक			num_res;
	काष्ठा res_sample	*res_samples;
	व्योम			*trace_output;
	काष्ठा perf_hpp_list	*hpp_list;
	काष्ठा hist_entry	*parent_he;
	काष्ठा hist_entry_ops	*ops;
	जोड़ अणु
		/* this is क्रम hierarchical entry काष्ठाure */
		काष्ठा अणु
			काष्ठा rb_root_cached	hroot_in;
			काष्ठा rb_root_cached   hroot_out;
		पूर्ण;				/* non-leaf entries */
		काष्ठा rb_root	sorted_chain;	/* leaf entry has callchains */
	पूर्ण;
	काष्ठा callchain_root	callchain[0]; /* must be last member */
पूर्ण;

अटल __pure अंतरभूत bool hist_entry__has_callchains(काष्ठा hist_entry *he)
अणु
	वापस he->callchain_size != 0;
पूर्ण

पूर्णांक hist_entry__sym_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf, माप_प्रकार size, अचिन्हित पूर्णांक width);

अटल अंतरभूत bool hist_entry__has_pairs(काष्ठा hist_entry *he)
अणु
	वापस !list_empty(&he->pairs.node);
पूर्ण

अटल अंतरभूत काष्ठा hist_entry *hist_entry__next_pair(काष्ठा hist_entry *he)
अणु
	अगर (hist_entry__has_pairs(he))
		वापस list_entry(he->pairs.node.next, काष्ठा hist_entry, pairs.node);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम hist_entry__add_pair(काष्ठा hist_entry *pair,
					काष्ठा hist_entry *he)
अणु
	list_add_tail(&pair->pairs.node, &he->pairs.head);
पूर्ण

अटल अंतरभूत भग्न hist_entry__get_percent_limit(काष्ठा hist_entry *he)
अणु
	u64 period = he->stat.period;
	u64 total_period = hists__total_period(he->hists);

	अगर (unlikely(total_period == 0))
		वापस 0;

	अगर (symbol_conf.cumulate_callchain)
		period = he->stat_acc->period;

	वापस period * 100.0 / total_period;
पूर्ण

क्रमागत sort_mode अणु
	SORT_MODE__NORMAL,
	SORT_MODE__BRANCH,
	SORT_MODE__MEMORY,
	SORT_MODE__TOP,
	SORT_MODE__DIFF,
	SORT_MODE__TRACEPOINT,
पूर्ण;

क्रमागत sort_type अणु
	/* common sort keys */
	SORT_PID,
	SORT_COMM,
	SORT_DSO,
	SORT_SYM,
	SORT_PARENT,
	SORT_CPU,
	SORT_SOCKET,
	SORT_SRCLINE,
	SORT_SRCखाता,
	SORT_LOCAL_WEIGHT,
	SORT_GLOBAL_WEIGHT,
	SORT_TRANSACTION,
	SORT_TRACE,
	SORT_SYM_SIZE,
	SORT_DSO_SIZE,
	SORT_CGROUP,
	SORT_CGROUP_ID,
	SORT_SYM_IPC_शून्य,
	SORT_TIME,
	SORT_CODE_PAGE_SIZE,
	SORT_LOCAL_INS_LAT,
	SORT_GLOBAL_INS_LAT,
	SORT_PIPELINE_STAGE_CYC,

	/* branch stack specअगरic sort keys */
	__SORT_BRANCH_STACK,
	SORT_DSO_FROM = __SORT_BRANCH_STACK,
	SORT_DSO_TO,
	SORT_SYM_FROM,
	SORT_SYM_TO,
	SORT_MISPREDICT,
	SORT_ABORT,
	SORT_IN_TX,
	SORT_CYCLES,
	SORT_SRCLINE_FROM,
	SORT_SRCLINE_TO,
	SORT_SYM_IPC,

	/* memory mode specअगरic sort keys */
	__SORT_MEMORY_MODE,
	SORT_MEM_DADDR_SYMBOL = __SORT_MEMORY_MODE,
	SORT_MEM_DADDR_DSO,
	SORT_MEM_LOCKED,
	SORT_MEM_TLB,
	SORT_MEM_LVL,
	SORT_MEM_SNOOP,
	SORT_MEM_DCACHELINE,
	SORT_MEM_IADDR_SYMBOL,
	SORT_MEM_PHYS_DADDR,
	SORT_MEM_DATA_PAGE_SIZE,
	SORT_MEM_BLOCKED,
पूर्ण;

/*
 * configurable sorting bits
 */

काष्ठा sort_entry अणु
	स्थिर अक्षर *se_header;

	पूर्णांक64_t (*se_cmp)(काष्ठा hist_entry *, काष्ठा hist_entry *);
	पूर्णांक64_t (*se_collapse)(काष्ठा hist_entry *, काष्ठा hist_entry *);
	पूर्णांक64_t	(*se_sort)(काष्ठा hist_entry *, काष्ठा hist_entry *);
	पूर्णांक	(*se_snम_लिखो)(काष्ठा hist_entry *he, अक्षर *bf, माप_प्रकार size,
			       अचिन्हित पूर्णांक width);
	पूर्णांक	(*se_filter)(काष्ठा hist_entry *he, पूर्णांक type, स्थिर व्योम *arg);
	u8	se_width_idx;
पूर्ण;

काष्ठा block_hist अणु
	काष्ठा hists		block_hists;
	काष्ठा perf_hpp_list	block_list;
	काष्ठा perf_hpp_fmt	block_fmt;
	पूर्णांक			block_idx;
	bool			valid;
	काष्ठा hist_entry	he;
पूर्ण;

बाह्य काष्ठा sort_entry sort_thपढ़ो;
बाह्य काष्ठा list_head hist_entry__sort_list;

काष्ठा evlist;
काष्ठा tep_handle;
पूर्णांक setup_sorting(काष्ठा evlist *evlist);
पूर्णांक setup_output_field(व्योम);
व्योम reset_output_field(व्योम);
व्योम sort__setup_elide(खाता *fp);
व्योम perf_hpp__set_elide(पूर्णांक idx, bool elide);

स्थिर अक्षर *sort_help(स्थिर अक्षर *prefix);

पूर्णांक report_parse_ignore_callees_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset);

bool is_strict_order(स्थिर अक्षर *order);

पूर्णांक hpp_dimension__add_output(अचिन्हित col);
व्योम reset_dimensions(व्योम);
पूर्णांक sort_dimension__add(काष्ठा perf_hpp_list *list, स्थिर अक्षर *tok,
			काष्ठा evlist *evlist,
			पूर्णांक level);
पूर्णांक output_field_add(काष्ठा perf_hpp_list *list, अक्षर *tok);
पूर्णांक64_t
sort__iaddr_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right);
पूर्णांक64_t
sort__daddr_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right);
पूर्णांक64_t
sort__dcacheline_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right);
पूर्णांक64_t
_sort__sym_cmp(काष्ठा symbol *sym_l, काष्ठा symbol *sym_r);
अक्षर *hist_entry__srcline(काष्ठा hist_entry *he);
#पूर्ण_अगर	/* __PERF_SORT_H */
