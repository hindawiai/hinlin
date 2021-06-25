<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_CALLCHAIN_H
#घोषणा __PERF_CALLCHAIN_H

#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश "map_symbol.h"
#समावेश "branch.h"

काष्ठा addr_location;
काष्ठा evsel;
काष्ठा ip_callchain;
काष्ठा map;
काष्ठा perf_sample;
काष्ठा thपढ़ो;
काष्ठा hists;

#घोषणा HELP_PAD "\t\t\t\t"

#घोषणा CALLCHAIN_HELP "setup and enables call-graph (stack chain/backtrace):\n\n"

# define RECORD_MODE_HELP  HELP_PAD "record_mode:\tcall graph recording mode (fp|dwarf|lbr)\n"

#घोषणा RECORD_SIZE_HELP						\
	HELP_PAD "record_size:\tif record_mode is 'dwarf', max size of stack recording (<bytes>)\n" \
	HELP_PAD "\t\tdefault: 8192 (bytes)\n"

#घोषणा CALLCHAIN_RECORD_HELP  CALLCHAIN_HELP RECORD_MODE_HELP RECORD_SIZE_HELP

#घोषणा CALLCHAIN_REPORT_HELP						\
	HELP_PAD "print_type:\tcall graph printing style (graph|flat|fractal|folded|none)\n" \
	HELP_PAD "threshold:\tminimum call graph inclusion threshold (<percent>)\n" \
	HELP_PAD "print_limit:\tmaximum number of call graph entry (<number>)\n" \
	HELP_PAD "order:\t\tcall graph order (caller|callee)\n" \
	HELP_PAD "sort_key:\tcall graph sort key (function|address)\n"	\
	HELP_PAD "branch:\t\tinclude last branch info to call graph (branch)\n" \
	HELP_PAD "value:\t\tcall graph value (percent|period|count)\n"

क्रमागत perf_call_graph_mode अणु
	CALLCHAIN_NONE,
	CALLCHAIN_FP,
	CALLCHAIN_DWARF,
	CALLCHAIN_LBR,
	CALLCHAIN_MAX
पूर्ण;

क्रमागत chain_mode अणु
	CHAIN_NONE,
	CHAIN_FLAT,
	CHAIN_GRAPH_ABS,
	CHAIN_GRAPH_REL,
	CHAIN_FOLDED,
पूर्ण;

क्रमागत chain_order अणु
	ORDER_CALLER,
	ORDER_CALLEE
पूर्ण;

काष्ठा callchain_node अणु
	काष्ठा callchain_node	*parent;
	काष्ठा list_head	val;
	काष्ठा list_head	parent_val;
	काष्ठा rb_node		rb_node_in; /* to insert nodes in an rbtree */
	काष्ठा rb_node		rb_node;    /* to sort nodes in an output tree */
	काष्ठा rb_root		rb_root_in; /* input tree of children */
	काष्ठा rb_root		rb_root;    /* sorted output tree of children */
	अचिन्हित पूर्णांक		val_nr;
	अचिन्हित पूर्णांक		count;
	अचिन्हित पूर्णांक		children_count;
	u64			hit;
	u64			children_hit;
पूर्ण;

काष्ठा callchain_root अणु
	u64			max_depth;
	काष्ठा callchain_node	node;
पूर्ण;

काष्ठा callchain_param;

प्रकार व्योम (*sort_chain_func_t)(काष्ठा rb_root *, काष्ठा callchain_root *,
				 u64, काष्ठा callchain_param *);

क्रमागत chain_key अणु
	CCKEY_FUNCTION,
	CCKEY_ADDRESS,
	CCKEY_SRCLINE
पूर्ण;

क्रमागत chain_value अणु
	CCVAL_PERCENT,
	CCVAL_PERIOD,
	CCVAL_COUNT,
पूर्ण;

बाह्य bool dwarf_callchain_users;

काष्ठा callchain_param अणु
	bool			enabled;
	क्रमागत perf_call_graph_mode record_mode;
	u32			dump_size;
	क्रमागत chain_mode 	mode;
	u16			max_stack;
	u32			prपूर्णांक_limit;
	द्विगुन			min_percent;
	sort_chain_func_t	sort;
	क्रमागत chain_order	order;
	bool			order_set;
	क्रमागत chain_key		key;
	bool			branch_callstack;
	क्रमागत chain_value	value;
पूर्ण;

बाह्य काष्ठा callchain_param callchain_param;
बाह्य काष्ठा callchain_param callchain_param_शेष;

काष्ठा callchain_list अणु
	u64			ip;
	काष्ठा map_symbol	ms;
	काष्ठा /* क्रम TUI */ अणु
		bool		unfolded;
		bool		has_children;
	पूर्ण;
	u64			branch_count;
	u64			from_count;
	u64			predicted_count;
	u64			पात_count;
	u64			cycles_count;
	u64			iter_count;
	u64			iter_cycles;
	काष्ठा branch_type_stat brtype_stat;
	स्थिर अक्षर		*srcline;
	काष्ठा list_head	list;
पूर्ण;

/*
 * A callchain cursor is a single linked list that
 * let one feed a callchain progressively.
 * It keeps persistent allocated entries to minimize
 * allocations.
 */
काष्ठा callchain_cursor_node अणु
	u64				ip;
	काष्ठा map_symbol		ms;
	स्थिर अक्षर			*srcline;
	/* Indicate valid cursor node क्रम LBR stitch */
	bool				valid;

	bool				branch;
	काष्ठा branch_flags		branch_flags;
	u64				branch_from;
	पूर्णांक				nr_loop_iter;
	u64				iter_cycles;
	काष्ठा callchain_cursor_node	*next;
पूर्ण;

काष्ठा stitch_list अणु
	काष्ठा list_head		node;
	काष्ठा callchain_cursor_node	cursor;
पूर्ण;

काष्ठा callchain_cursor अणु
	u64				nr;
	काष्ठा callchain_cursor_node	*first;
	काष्ठा callchain_cursor_node	**last;
	u64				pos;
	काष्ठा callchain_cursor_node	*curr;
पूर्ण;

बाह्य __thपढ़ो काष्ठा callchain_cursor callchain_cursor;

अटल अंतरभूत व्योम callchain_init(काष्ठा callchain_root *root)
अणु
	INIT_LIST_HEAD(&root->node.val);
	INIT_LIST_HEAD(&root->node.parent_val);

	root->node.parent = शून्य;
	root->node.hit = 0;
	root->node.children_hit = 0;
	root->node.rb_root_in = RB_ROOT;
	root->max_depth = 0;
पूर्ण

अटल अंतरभूत u64 callchain_cumul_hits(काष्ठा callchain_node *node)
अणु
	वापस node->hit + node->children_hit;
पूर्ण

अटल अंतरभूत अचिन्हित callchain_cumul_counts(काष्ठा callchain_node *node)
अणु
	वापस node->count + node->children_count;
पूर्ण

पूर्णांक callchain_रेजिस्टर_param(काष्ठा callchain_param *param);
पूर्णांक callchain_append(काष्ठा callchain_root *root,
		     काष्ठा callchain_cursor *cursor,
		     u64 period);

पूर्णांक callchain_merge(काष्ठा callchain_cursor *cursor,
		    काष्ठा callchain_root *dst, काष्ठा callchain_root *src);

व्योम callchain_cursor_reset(काष्ठा callchain_cursor *cursor);

पूर्णांक callchain_cursor_append(काष्ठा callchain_cursor *cursor, u64 ip,
			    काष्ठा map_symbol *ms,
			    bool branch, काष्ठा branch_flags *flags,
			    पूर्णांक nr_loop_iter, u64 iter_cycles, u64 branch_from,
			    स्थिर अक्षर *srcline);

/* Close a cursor writing session. Initialize क्रम the पढ़ोer */
अटल अंतरभूत व्योम callchain_cursor_commit(काष्ठा callchain_cursor *cursor)
अणु
	cursor->curr = cursor->first;
	cursor->pos = 0;
पूर्ण

/* Cursor पढ़ोing iteration helpers */
अटल अंतरभूत काष्ठा callchain_cursor_node *
callchain_cursor_current(काष्ठा callchain_cursor *cursor)
अणु
	अगर (cursor->pos == cursor->nr)
		वापस शून्य;

	वापस cursor->curr;
पूर्ण

अटल अंतरभूत व्योम callchain_cursor_advance(काष्ठा callchain_cursor *cursor)
अणु
	cursor->curr = cursor->curr->next;
	cursor->pos++;
पूर्ण

पूर्णांक callchain_cursor__copy(काष्ठा callchain_cursor *dst,
			   काष्ठा callchain_cursor *src);

काष्ठा option;
काष्ठा hist_entry;

पूर्णांक record_parse_callchain_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset);
पूर्णांक record_callchain_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset);

काष्ठा record_opts;

पूर्णांक record_opts__parse_callchain(काष्ठा record_opts *record,
				 काष्ठा callchain_param *callchain,
				 स्थिर अक्षर *arg, bool unset);

पूर्णांक sample__resolve_callchain(काष्ठा perf_sample *sample,
			      काष्ठा callchain_cursor *cursor, काष्ठा symbol **parent,
			      काष्ठा evsel *evsel, काष्ठा addr_location *al,
			      पूर्णांक max_stack);
पूर्णांक hist_entry__append_callchain(काष्ठा hist_entry *he, काष्ठा perf_sample *sample);
पूर्णांक fill_callchain_info(काष्ठा addr_location *al, काष्ठा callchain_cursor_node *node,
			bool hide_unresolved);

बाह्य स्थिर अक्षर record_callchain_help[];
पूर्णांक parse_callchain_record(स्थिर अक्षर *arg, काष्ठा callchain_param *param);
पूर्णांक parse_callchain_record_opt(स्थिर अक्षर *arg, काष्ठा callchain_param *param);
पूर्णांक parse_callchain_report_opt(स्थिर अक्षर *arg);
पूर्णांक parse_callchain_top_opt(स्थिर अक्षर *arg);
पूर्णांक perf_callchain_config(स्थिर अक्षर *var, स्थिर अक्षर *value);

अटल अंतरभूत व्योम callchain_cursor_snapshot(काष्ठा callchain_cursor *dest,
					     काष्ठा callchain_cursor *src)
अणु
	*dest = *src;

	dest->first = src->curr;
	dest->nr -= src->pos;
पूर्ण

#अगर_घोषित HAVE_SKIP_CALLCHAIN_IDX
पूर्णांक arch_skip_callchain_idx(काष्ठा thपढ़ो *thपढ़ो, काष्ठा ip_callchain *chain);
#अन्यथा
अटल अंतरभूत पूर्णांक arch_skip_callchain_idx(काष्ठा thपढ़ो *thपढ़ो __maybe_unused,
			काष्ठा ip_callchain *chain __maybe_unused)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

अक्षर *callchain_list__sym_name(काष्ठा callchain_list *cl,
			       अक्षर *bf, माप_प्रकार bfsize, bool show_dso);
अक्षर *callchain_node__scnम_लिखो_value(काष्ठा callchain_node *node,
				      अक्षर *bf, माप_प्रकार bfsize, u64 total);
पूर्णांक callchain_node__ख_लिखो_value(काष्ठा callchain_node *node,
				  खाता *fp, u64 total);

पूर्णांक callchain_list_counts__म_लिखो_value(काष्ठा callchain_list *clist,
					खाता *fp, अक्षर *bf, पूर्णांक bfsize);

व्योम मुक्त_callchain(काष्ठा callchain_root *root);
व्योम decay_callchain(काष्ठा callchain_root *root);
पूर्णांक callchain_node__make_parent_list(काष्ठा callchain_node *node);

पूर्णांक callchain_branch_counts(काष्ठा callchain_root *root,
			    u64 *branch_count, u64 *predicted_count,
			    u64 *पात_count, u64 *cycles_count);

व्योम callchain_param_setup(u64 sample_type);

bool callchain_cnode_matched(काष्ठा callchain_node *base_cnode,
			     काष्ठा callchain_node *pair_cnode);

u64 callchain_total_hits(काष्ठा hists *hists);

s64 callchain_avg_cycles(काष्ठा callchain_node *cnode);

#पूर्ण_अगर	/* __PERF_CALLCHAIN_H */
