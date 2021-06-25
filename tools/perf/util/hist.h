<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_HIST_H
#घोषणा __PERF_HIST_H

#समावेश <linux/rbtree.h>
#समावेश <linux/types.h>
#समावेश <pthपढ़ो.h>
#समावेश "evsel.h"
#समावेश "color.h"
#समावेश "events_stats.h"

काष्ठा hist_entry;
काष्ठा hist_entry_ops;
काष्ठा addr_location;
काष्ठा map_symbol;
काष्ठा mem_info;
काष्ठा branch_info;
काष्ठा branch_stack;
काष्ठा block_info;
काष्ठा symbol;
काष्ठा ui_progress;

क्रमागत hist_filter अणु
	HIST_FILTER__DSO,
	HIST_FILTER__THREAD,
	HIST_FILTER__PARENT,
	HIST_FILTER__SYMBOL,
	HIST_FILTER__GUEST,
	HIST_FILTER__HOST,
	HIST_FILTER__SOCKET,
	HIST_FILTER__C2C,
पूर्ण;

क्रमागत hist_column अणु
	HISTC_SYMBOL,
	HISTC_TIME,
	HISTC_DSO,
	HISTC_THREAD,
	HISTC_COMM,
	HISTC_CGROUP_ID,
	HISTC_CGROUP,
	HISTC_PARENT,
	HISTC_CPU,
	HISTC_SOCKET,
	HISTC_SRCLINE,
	HISTC_SRCखाता,
	HISTC_MISPREDICT,
	HISTC_IN_TX,
	HISTC_ABORT,
	HISTC_SYMBOL_FROM,
	HISTC_SYMBOL_TO,
	HISTC_DSO_FROM,
	HISTC_DSO_TO,
	HISTC_LOCAL_WEIGHT,
	HISTC_GLOBAL_WEIGHT,
	HISTC_CODE_PAGE_SIZE,
	HISTC_MEM_DADDR_SYMBOL,
	HISTC_MEM_DADDR_DSO,
	HISTC_MEM_PHYS_DADDR,
	HISTC_MEM_DATA_PAGE_SIZE,
	HISTC_MEM_LOCKED,
	HISTC_MEM_TLB,
	HISTC_MEM_LVL,
	HISTC_MEM_SNOOP,
	HISTC_MEM_DCACHELINE,
	HISTC_MEM_IADDR_SYMBOL,
	HISTC_TRANSACTION,
	HISTC_CYCLES,
	HISTC_SRCLINE_FROM,
	HISTC_SRCLINE_TO,
	HISTC_TRACE,
	HISTC_SYM_SIZE,
	HISTC_DSO_SIZE,
	HISTC_SYMBOL_IPC,
	HISTC_MEM_BLOCKED,
	HISTC_LOCAL_INS_LAT,
	HISTC_GLOBAL_INS_LAT,
	HISTC_P_STAGE_CYC,
	HISTC_NR_COLS, /* Last entry */
पूर्ण;

काष्ठा thपढ़ो;
काष्ठा dso;

काष्ठा hists अणु
	काष्ठा rb_root_cached	entries_in_array[2];
	काष्ठा rb_root_cached	*entries_in;
	काष्ठा rb_root_cached	entries;
	काष्ठा rb_root_cached	entries_collapsed;
	u64			nr_entries;
	u64			nr_non_filtered_entries;
	u64			callchain_period;
	u64			callchain_non_filtered_period;
	काष्ठा thपढ़ो		*thपढ़ो_filter;
	स्थिर काष्ठा dso	*dso_filter;
	स्थिर अक्षर		*uid_filter_str;
	स्थिर अक्षर		*symbol_filter_str;
	pthपढ़ो_mutex_t		lock;
	काष्ठा hists_stats	stats;
	u64			event_stream;
	u16			col_len[HISTC_NR_COLS];
	bool			has_callchains;
	पूर्णांक			socket_filter;
	काष्ठा perf_hpp_list	*hpp_list;
	काष्ठा list_head	hpp_क्रमmats;
	पूर्णांक			nr_hpp_node;
पूर्ण;

#घोषणा hists__has(__h, __f) (__h)->hpp_list->__f

काष्ठा hist_entry_iter;

काष्ठा hist_iter_ops अणु
	पूर्णांक (*prepare_entry)(काष्ठा hist_entry_iter *, काष्ठा addr_location *);
	पूर्णांक (*add_single_entry)(काष्ठा hist_entry_iter *, काष्ठा addr_location *);
	पूर्णांक (*next_entry)(काष्ठा hist_entry_iter *, काष्ठा addr_location *);
	पूर्णांक (*add_next_entry)(काष्ठा hist_entry_iter *, काष्ठा addr_location *);
	पूर्णांक (*finish_entry)(काष्ठा hist_entry_iter *, काष्ठा addr_location *);
पूर्ण;

काष्ठा hist_entry_iter अणु
	पूर्णांक total;
	पूर्णांक curr;

	bool hide_unresolved;

	काष्ठा evsel *evsel;
	काष्ठा perf_sample *sample;
	काष्ठा hist_entry *he;
	काष्ठा symbol *parent;
	व्योम *priv;

	स्थिर काष्ठा hist_iter_ops *ops;
	/* user-defined callback function (optional) */
	पूर्णांक (*add_entry_cb)(काष्ठा hist_entry_iter *iter,
			    काष्ठा addr_location *al, bool single, व्योम *arg);
पूर्ण;

बाह्य स्थिर काष्ठा hist_iter_ops hist_iter_normal;
बाह्य स्थिर काष्ठा hist_iter_ops hist_iter_branch;
बाह्य स्थिर काष्ठा hist_iter_ops hist_iter_mem;
बाह्य स्थिर काष्ठा hist_iter_ops hist_iter_cumulative;

काष्ठा hist_entry *hists__add_entry(काष्ठा hists *hists,
				    काष्ठा addr_location *al,
				    काष्ठा symbol *parent,
				    काष्ठा branch_info *bi,
				    काष्ठा mem_info *mi,
				    काष्ठा perf_sample *sample,
				    bool sample_self);

काष्ठा hist_entry *hists__add_entry_ops(काष्ठा hists *hists,
					काष्ठा hist_entry_ops *ops,
					काष्ठा addr_location *al,
					काष्ठा symbol *sym_parent,
					काष्ठा branch_info *bi,
					काष्ठा mem_info *mi,
					काष्ठा perf_sample *sample,
					bool sample_self);

काष्ठा hist_entry *hists__add_entry_block(काष्ठा hists *hists,
					  काष्ठा addr_location *al,
					  काष्ठा block_info *bi);

पूर्णांक hist_entry_iter__add(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al,
			 पूर्णांक max_stack_depth, व्योम *arg);

काष्ठा perf_hpp;
काष्ठा perf_hpp_fmt;

पूर्णांक64_t hist_entry__cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right);
पूर्णांक64_t hist_entry__collapse(काष्ठा hist_entry *left, काष्ठा hist_entry *right);
पूर्णांक hist_entry__transaction_len(व्योम);
पूर्णांक hist_entry__sort_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf, माप_प्रकार size,
			      काष्ठा hists *hists);
पूर्णांक hist_entry__snम_लिखो_alignment(काष्ठा hist_entry *he, काष्ठा perf_hpp *hpp,
				   काष्ठा perf_hpp_fmt *fmt, पूर्णांक prपूर्णांकed);
व्योम hist_entry__delete(काष्ठा hist_entry *he);

प्रकार पूर्णांक (*hists__resort_cb_t)(काष्ठा hist_entry *he, व्योम *arg);

व्योम evsel__output_resort_cb(काष्ठा evsel *evsel, काष्ठा ui_progress *prog,
			     hists__resort_cb_t cb, व्योम *cb_arg);
व्योम evsel__output_resort(काष्ठा evsel *evsel, काष्ठा ui_progress *prog);
व्योम hists__output_resort(काष्ठा hists *hists, काष्ठा ui_progress *prog);
व्योम hists__output_resort_cb(काष्ठा hists *hists, काष्ठा ui_progress *prog,
			     hists__resort_cb_t cb);
पूर्णांक hists__collapse_resort(काष्ठा hists *hists, काष्ठा ui_progress *prog);

व्योम hists__decay_entries(काष्ठा hists *hists, bool zap_user, bool zap_kernel);
व्योम hists__delete_entries(काष्ठा hists *hists);
व्योम hists__output_recalc_col_len(काष्ठा hists *hists, पूर्णांक max_rows);

काष्ठा hist_entry *hists__get_entry(काष्ठा hists *hists, पूर्णांक idx);

u64 hists__total_period(काष्ठा hists *hists);
व्योम hists__reset_stats(काष्ठा hists *hists);
व्योम hists__inc_stats(काष्ठा hists *hists, काष्ठा hist_entry *h);
व्योम hists__inc_nr_events(काष्ठा hists *hists);
व्योम hists__inc_nr_samples(काष्ठा hists *hists, bool filtered);

माप_प्रकार hists__ख_लिखो(काष्ठा hists *hists, bool show_header, पूर्णांक max_rows,
		      पूर्णांक max_cols, भग्न min_pcnt, खाता *fp,
		      bool ignore_callchains);
माप_प्रकार evlist__ख_लिखो_nr_events(काष्ठा evlist *evlist, खाता *fp,
				 bool skip_empty);

व्योम hists__filter_by_dso(काष्ठा hists *hists);
व्योम hists__filter_by_thपढ़ो(काष्ठा hists *hists);
व्योम hists__filter_by_symbol(काष्ठा hists *hists);
व्योम hists__filter_by_socket(काष्ठा hists *hists);

अटल अंतरभूत bool hists__has_filter(काष्ठा hists *hists)
अणु
	वापस hists->thपढ़ो_filter || hists->dso_filter ||
		hists->symbol_filter_str || (hists->socket_filter > -1);
पूर्ण

u16 hists__col_len(काष्ठा hists *hists, क्रमागत hist_column col);
व्योम hists__set_col_len(काष्ठा hists *hists, क्रमागत hist_column col, u16 len);
bool hists__new_col_len(काष्ठा hists *hists, क्रमागत hist_column col, u16 len);
व्योम hists__reset_col_len(काष्ठा hists *hists);
व्योम hists__calc_col_len(काष्ठा hists *hists, काष्ठा hist_entry *he);

व्योम hists__match(काष्ठा hists *leader, काष्ठा hists *other);
पूर्णांक hists__link(काष्ठा hists *leader, काष्ठा hists *other);
पूर्णांक hists__unlink(काष्ठा hists *hists);

काष्ठा hists_evsel अणु
	काष्ठा evsel evsel;
	काष्ठा hists	  hists;
पूर्ण;

अटल अंतरभूत काष्ठा evsel *hists_to_evsel(काष्ठा hists *hists)
अणु
	काष्ठा hists_evsel *hevsel = container_of(hists, काष्ठा hists_evsel, hists);
	वापस &hevsel->evsel;
पूर्ण

अटल अंतरभूत काष्ठा hists *evsel__hists(काष्ठा evsel *evsel)
अणु
	काष्ठा hists_evsel *hevsel = (काष्ठा hists_evsel *)evsel;
	वापस &hevsel->hists;
पूर्ण

अटल __pure अंतरभूत bool hists__has_callchains(काष्ठा hists *hists)
अणु
	वापस hists->has_callchains;
पूर्ण

पूर्णांक hists__init(व्योम);
पूर्णांक __hists__init(काष्ठा hists *hists, काष्ठा perf_hpp_list *hpp_list);

काष्ठा rb_root_cached *hists__get_rotate_entries_in(काष्ठा hists *hists);

काष्ठा perf_hpp अणु
	अक्षर *buf;
	माप_प्रकार size;
	स्थिर अक्षर *sep;
	व्योम *ptr;
	bool skip;
पूर्ण;

काष्ठा perf_hpp_fmt अणु
	स्थिर अक्षर *name;
	पूर्णांक (*header)(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		      काष्ठा hists *hists, पूर्णांक line, पूर्णांक *span);
	पूर्णांक (*width)(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		     काष्ठा hists *hists);
	पूर्णांक (*color)(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		     काष्ठा hist_entry *he);
	पूर्णांक (*entry)(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		     काष्ठा hist_entry *he);
	पूर्णांक64_t (*cmp)(काष्ठा perf_hpp_fmt *fmt,
		       काष्ठा hist_entry *a, काष्ठा hist_entry *b);
	पूर्णांक64_t (*collapse)(काष्ठा perf_hpp_fmt *fmt,
			    काष्ठा hist_entry *a, काष्ठा hist_entry *b);
	पूर्णांक64_t (*sort)(काष्ठा perf_hpp_fmt *fmt,
			काष्ठा hist_entry *a, काष्ठा hist_entry *b);
	bool (*equal)(काष्ठा perf_hpp_fmt *a, काष्ठा perf_hpp_fmt *b);
	व्योम (*मुक्त)(काष्ठा perf_hpp_fmt *fmt);

	काष्ठा list_head list;
	काष्ठा list_head sort_list;
	bool elide;
	पूर्णांक len;
	पूर्णांक user_len;
	पूर्णांक idx;
	पूर्णांक level;
पूर्ण;

काष्ठा perf_hpp_list अणु
	काष्ठा list_head fields;
	काष्ठा list_head sorts;

	पूर्णांक nr_header_lines;
	पूर्णांक need_collapse;
	पूर्णांक parent;
	पूर्णांक sym;
	पूर्णांक dso;
	पूर्णांक socket;
	पूर्णांक thपढ़ो;
	पूर्णांक comm;
पूर्ण;

बाह्य काष्ठा perf_hpp_list perf_hpp_list;

काष्ठा perf_hpp_list_node अणु
	काष्ठा list_head	list;
	काष्ठा perf_hpp_list	hpp;
	पूर्णांक			level;
	bool			skip;
पूर्ण;

व्योम perf_hpp_list__column_रेजिस्टर(काष्ठा perf_hpp_list *list,
				    काष्ठा perf_hpp_fmt *क्रमmat);
व्योम perf_hpp_list__रेजिस्टर_sort_field(काष्ठा perf_hpp_list *list,
					काष्ठा perf_hpp_fmt *क्रमmat);
व्योम perf_hpp_list__prepend_sort_field(काष्ठा perf_hpp_list *list,
				       काष्ठा perf_hpp_fmt *क्रमmat);

अटल अंतरभूत व्योम perf_hpp__column_रेजिस्टर(काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	perf_hpp_list__column_रेजिस्टर(&perf_hpp_list, क्रमmat);
पूर्ण

अटल अंतरभूत व्योम perf_hpp__रेजिस्टर_sort_field(काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	perf_hpp_list__रेजिस्टर_sort_field(&perf_hpp_list, क्रमmat);
पूर्ण

अटल अंतरभूत व्योम perf_hpp__prepend_sort_field(काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	perf_hpp_list__prepend_sort_field(&perf_hpp_list, क्रमmat);
पूर्ण

#घोषणा perf_hpp_list__क्रम_each_क्रमmat(_list, क्रमmat) \
	list_क्रम_each_entry(क्रमmat, &(_list)->fields, list)

#घोषणा perf_hpp_list__क्रम_each_क्रमmat_safe(_list, क्रमmat, पंचांगp)	\
	list_क्रम_each_entry_safe(क्रमmat, पंचांगp, &(_list)->fields, list)

#घोषणा perf_hpp_list__क्रम_each_sort_list(_list, क्रमmat) \
	list_क्रम_each_entry(क्रमmat, &(_list)->sorts, sort_list)

#घोषणा perf_hpp_list__क्रम_each_sort_list_safe(_list, क्रमmat, पंचांगp)	\
	list_क्रम_each_entry_safe(क्रमmat, पंचांगp, &(_list)->sorts, sort_list)

#घोषणा hists__क्रम_each_क्रमmat(hists, क्रमmat) \
	perf_hpp_list__क्रम_each_क्रमmat((hists)->hpp_list, क्रमmat)

#घोषणा hists__क्रम_each_sort_list(hists, क्रमmat) \
	perf_hpp_list__क्रम_each_sort_list((hists)->hpp_list, क्रमmat)

बाह्य काष्ठा perf_hpp_fmt perf_hpp__क्रमmat[];

क्रमागत अणु
	/* Matches perf_hpp__क्रमmat array. */
	PERF_HPP__OVERHEAD,
	PERF_HPP__OVERHEAD_SYS,
	PERF_HPP__OVERHEAD_US,
	PERF_HPP__OVERHEAD_GUEST_SYS,
	PERF_HPP__OVERHEAD_GUEST_US,
	PERF_HPP__OVERHEAD_ACC,
	PERF_HPP__SAMPLES,
	PERF_HPP__PERIOD,

	PERF_HPP__MAX_INDEX
पूर्ण;

व्योम perf_hpp__init(व्योम);
व्योम perf_hpp__column_unरेजिस्टर(काष्ठा perf_hpp_fmt *क्रमmat);
व्योम perf_hpp__cancel_cumulate(व्योम);
व्योम perf_hpp__setup_output_field(काष्ठा perf_hpp_list *list);
व्योम perf_hpp__reset_output_field(काष्ठा perf_hpp_list *list);
व्योम perf_hpp__append_sort_keys(काष्ठा perf_hpp_list *list);
पूर्णांक perf_hpp__setup_hists_क्रमmats(काष्ठा perf_hpp_list *list,
				  काष्ठा evlist *evlist);


bool perf_hpp__is_sort_entry(काष्ठा perf_hpp_fmt *क्रमmat);
bool perf_hpp__is_dynamic_entry(काष्ठा perf_hpp_fmt *क्रमmat);
bool perf_hpp__defined_dynamic_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा hists *hists);
bool perf_hpp__is_trace_entry(काष्ठा perf_hpp_fmt *fmt);
bool perf_hpp__is_srcline_entry(काष्ठा perf_hpp_fmt *fmt);
bool perf_hpp__is_srcfile_entry(काष्ठा perf_hpp_fmt *fmt);
bool perf_hpp__is_thपढ़ो_entry(काष्ठा perf_hpp_fmt *fmt);
bool perf_hpp__is_comm_entry(काष्ठा perf_hpp_fmt *fmt);
bool perf_hpp__is_dso_entry(काष्ठा perf_hpp_fmt *fmt);
bool perf_hpp__is_sym_entry(काष्ठा perf_hpp_fmt *fmt);

काष्ठा perf_hpp_fmt *perf_hpp_fmt__dup(काष्ठा perf_hpp_fmt *fmt);

पूर्णांक hist_entry__filter(काष्ठा hist_entry *he, पूर्णांक type, स्थिर व्योम *arg);

अटल अंतरभूत bool perf_hpp__should_skip(काष्ठा perf_hpp_fmt *क्रमmat,
					 काष्ठा hists *hists)
अणु
	अगर (क्रमmat->elide)
		वापस true;

	अगर (perf_hpp__is_dynamic_entry(क्रमmat) &&
	    !perf_hpp__defined_dynamic_entry(क्रमmat, hists))
		वापस true;

	वापस false;
पूर्ण

व्योम perf_hpp__reset_width(काष्ठा perf_hpp_fmt *fmt, काष्ठा hists *hists);
व्योम perf_hpp__reset_sort_width(काष्ठा perf_hpp_fmt *fmt, काष्ठा hists *hists);
व्योम perf_hpp__set_user_width(स्थिर अक्षर *width_list_str);
व्योम hists__reset_column_width(काष्ठा hists *hists);

प्रकार u64 (*hpp_field_fn)(काष्ठा hist_entry *he);
प्रकार पूर्णांक (*hpp_callback_fn)(काष्ठा perf_hpp *hpp, bool front);
प्रकार पूर्णांक (*hpp_snprपूर्णांक_fn)(काष्ठा perf_hpp *hpp, स्थिर अक्षर *fmt, ...);

पूर्णांक hpp__fmt(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	     काष्ठा hist_entry *he, hpp_field_fn get_field,
	     स्थिर अक्षर *fmtstr, hpp_snprपूर्णांक_fn prपूर्णांक_fn, bool fmt_percent);
पूर्णांक hpp__fmt_acc(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		 काष्ठा hist_entry *he, hpp_field_fn get_field,
		 स्थिर अक्षर *fmtstr, hpp_snprपूर्णांक_fn prपूर्णांक_fn, bool fmt_percent);

अटल अंतरभूत व्योम advance_hpp(काष्ठा perf_hpp *hpp, पूर्णांक inc)
अणु
	hpp->buf  += inc;
	hpp->size -= inc;
पूर्ण

अटल अंतरभूत माप_प्रकार perf_hpp__use_color(व्योम)
अणु
	वापस !symbol_conf.field_sep;
पूर्ण

अटल अंतरभूत माप_प्रकार perf_hpp__color_overhead(व्योम)
अणु
	वापस perf_hpp__use_color() ?
	       (COLOR_MAXLEN + माप(PERF_COLOR_RESET)) * PERF_HPP__MAX_INDEX
	       : 0;
पूर्ण

काष्ठा evlist;

काष्ठा hist_browser_समयr अणु
	व्योम (*समयr)(व्योम *arg);
	व्योम *arg;
	पूर्णांक refresh;
पूर्ण;

काष्ठा annotation_options;
काष्ठा res_sample;

क्रमागत rstype अणु
	A_NORMAL,
	A_ASM,
	A_SOURCE
पूर्ण;

काष्ठा block_hist;

#अगर_घोषित HAVE_SLANG_SUPPORT
#समावेश "../ui/keysyms.h"
व्योम attr_to_script(अक्षर *buf, काष्ठा perf_event_attr *attr);

पूर्णांक map_symbol__tui_annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			     काष्ठा hist_browser_समयr *hbt,
			     काष्ठा annotation_options *annotation_opts);

पूर्णांक hist_entry__tui_annotate(काष्ठा hist_entry *he, काष्ठा evsel *evsel,
			     काष्ठा hist_browser_समयr *hbt,
			     काष्ठा annotation_options *annotation_opts);

पूर्णांक evlist__tui_browse_hists(काष्ठा evlist *evlist, स्थिर अक्षर *help, काष्ठा hist_browser_समयr *hbt,
			     भग्न min_pcnt, काष्ठा perf_env *env, bool warn_lost_event,
			     काष्ठा annotation_options *annotation_options);

पूर्णांक script_browse(स्थिर अक्षर *script_opt, काष्ठा evsel *evsel);

व्योम run_script(अक्षर *cmd);
पूर्णांक res_sample_browse(काष्ठा res_sample *res_samples, पूर्णांक num_res,
		      काष्ठा evsel *evsel, क्रमागत rstype rstype);
व्योम res_sample_init(व्योम);

पूर्णांक block_hists_tui_browse(काष्ठा block_hist *bh, काष्ठा evsel *evsel,
			   भग्न min_percent, काष्ठा perf_env *env,
			   काष्ठा annotation_options *annotation_opts);
#अन्यथा
अटल अंतरभूत
पूर्णांक evlist__tui_browse_hists(काष्ठा evlist *evlist __maybe_unused,
			     स्थिर अक्षर *help __maybe_unused,
			     काष्ठा hist_browser_समयr *hbt __maybe_unused,
			     भग्न min_pcnt __maybe_unused,
			     काष्ठा perf_env *env __maybe_unused,
			     bool warn_lost_event __maybe_unused,
			     काष्ठा annotation_options *annotation_options __maybe_unused)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक map_symbol__tui_annotate(काष्ठा map_symbol *ms __maybe_unused,
					   काष्ठा evsel *evsel __maybe_unused,
					   काष्ठा hist_browser_समयr *hbt __maybe_unused,
					   काष्ठा annotation_options *annotation_options __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hist_entry__tui_annotate(काष्ठा hist_entry *he __maybe_unused,
					   काष्ठा evsel *evsel __maybe_unused,
					   काष्ठा hist_browser_समयr *hbt __maybe_unused,
					   काष्ठा annotation_options *annotation_opts __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक script_browse(स्थिर अक्षर *script_opt __maybe_unused,
				काष्ठा evsel *evsel __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक res_sample_browse(काष्ठा res_sample *res_samples __maybe_unused,
				    पूर्णांक num_res __maybe_unused,
				    काष्ठा evsel *evsel __maybe_unused,
				    क्रमागत rstype rstype __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम res_sample_init(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक block_hists_tui_browse(काष्ठा block_hist *bh __maybe_unused,
					 काष्ठा evsel *evsel __maybe_unused,
					 भग्न min_percent __maybe_unused,
					 काष्ठा perf_env *env __maybe_unused,
					 काष्ठा annotation_options *annotation_opts __maybe_unused)
अणु
	वापस 0;
पूर्ण

#घोषणा K_LEFT  -1000
#घोषणा K_RIGHT -2000
#घोषणा K_SWITCH_INPUT_DATA -3000
#घोषणा K_RELOAD -4000
#पूर्ण_अगर

अचिन्हित पूर्णांक hists__sort_list_width(काष्ठा hists *hists);
अचिन्हित पूर्णांक hists__overhead_width(काष्ठा hists *hists);

व्योम hist__account_cycles(काष्ठा branch_stack *bs, काष्ठा addr_location *al,
			  काष्ठा perf_sample *sample, bool nonany_branch_mode,
			  u64 *total_cycles);

काष्ठा option;
पूर्णांक parse_filter_percentage(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset);
पूर्णांक perf_hist_config(स्थिर अक्षर *var, स्थिर अक्षर *value);

व्योम perf_hpp_list__init(काष्ठा perf_hpp_list *list);

क्रमागत hierarchy_move_dir अणु
	HMD_NORMAL,
	HMD_FORCE_SIBLING,
	HMD_FORCE_CHILD,
पूर्ण;

काष्ठा rb_node *rb_hierarchy_last(काष्ठा rb_node *node);
काष्ठा rb_node *__rb_hierarchy_next(काष्ठा rb_node *node,
				    क्रमागत hierarchy_move_dir hmd);
काष्ठा rb_node *rb_hierarchy_prev(काष्ठा rb_node *node);

अटल अंतरभूत काष्ठा rb_node *rb_hierarchy_next(काष्ठा rb_node *node)
अणु
	वापस __rb_hierarchy_next(node, HMD_NORMAL);
पूर्ण

#घोषणा HIERARCHY_INDENT  3

bool hist_entry__has_hierarchy_children(काष्ठा hist_entry *he, भग्न limit);
पूर्णांक hpp_color_scnम_लिखो(काष्ठा perf_hpp *hpp, स्थिर अक्षर *fmt, ...);
पूर्णांक __hpp__slsmg_color_म_लिखो(काष्ठा perf_hpp *hpp, स्थिर अक्षर *fmt, ...);
पूर्णांक __hist_entry__snम_लिखो(काष्ठा hist_entry *he, काष्ठा perf_hpp *hpp,
			   काष्ठा perf_hpp_list *hpp_list);
पूर्णांक hists__ख_लिखो_headers(काष्ठा hists *hists, खाता *fp);
पूर्णांक __hists__scnम_लिखो_title(काष्ठा hists *hists, अक्षर *bf, माप_प्रकार size, bool show_freq);

अटल अंतरभूत पूर्णांक hists__scnम_लिखो_title(काष्ठा hists *hists, अक्षर *bf, माप_प्रकार size)
अणु
	वापस __hists__scnम_लिखो_title(hists, bf, size, true);
पूर्ण

#पूर्ण_अगर	/* __PERF_HIST_H */
