<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "callchain.h"
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "build-id.h"
#समावेश "hist.h"
#समावेश "map.h"
#समावेश "map_symbol.h"
#समावेश "branch.h"
#समावेश "mem-events.h"
#समावेश "session.h"
#समावेश "namespaces.h"
#समावेश "cgroup.h"
#समावेश "sort.h"
#समावेश "units.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "annotate.h"
#समावेश "srcline.h"
#समावेश "symbol.h"
#समावेश "thread.h"
#समावेश "block-info.h"
#समावेश "ui/progress.h"
#समावेश <त्रुटिसं.स>
#समावेश <गणित.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/param.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>

अटल bool hists__filter_entry_by_dso(काष्ठा hists *hists,
				       काष्ठा hist_entry *he);
अटल bool hists__filter_entry_by_thपढ़ो(काष्ठा hists *hists,
					  काष्ठा hist_entry *he);
अटल bool hists__filter_entry_by_symbol(काष्ठा hists *hists,
					  काष्ठा hist_entry *he);
अटल bool hists__filter_entry_by_socket(काष्ठा hists *hists,
					  काष्ठा hist_entry *he);

u16 hists__col_len(काष्ठा hists *hists, क्रमागत hist_column col)
अणु
	वापस hists->col_len[col];
पूर्ण

व्योम hists__set_col_len(काष्ठा hists *hists, क्रमागत hist_column col, u16 len)
अणु
	hists->col_len[col] = len;
पूर्ण

bool hists__new_col_len(काष्ठा hists *hists, क्रमागत hist_column col, u16 len)
अणु
	अगर (len > hists__col_len(hists, col)) अणु
		hists__set_col_len(hists, col, len);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम hists__reset_col_len(काष्ठा hists *hists)
अणु
	क्रमागत hist_column col;

	क्रम (col = 0; col < HISTC_NR_COLS; ++col)
		hists__set_col_len(hists, col, 0);
पूर्ण

अटल व्योम hists__set_unres_dso_col_len(काष्ठा hists *hists, पूर्णांक dso)
अणु
	स्थिर अचिन्हित पूर्णांक unresolved_col_width = BITS_PER_LONG / 4;

	अगर (hists__col_len(hists, dso) < unresolved_col_width &&
	    !symbol_conf.col_width_list_str && !symbol_conf.field_sep &&
	    !symbol_conf.dso_list)
		hists__set_col_len(hists, dso, unresolved_col_width);
पूर्ण

व्योम hists__calc_col_len(काष्ठा hists *hists, काष्ठा hist_entry *h)
अणु
	स्थिर अचिन्हित पूर्णांक unresolved_col_width = BITS_PER_LONG / 4;
	पूर्णांक symlen;
	u16 len;

	अगर (h->block_info)
		वापस;
	/*
	 * +4 accounts क्रम '[x] ' priv level info
	 * +2 accounts क्रम 0x prefix on raw addresses
	 * +3 accounts क्रम ' y ' symtab origin info
	 */
	अगर (h->ms.sym) अणु
		symlen = h->ms.sym->namelen + 4;
		अगर (verbose > 0)
			symlen += BITS_PER_LONG / 4 + 2 + 3;
		hists__new_col_len(hists, HISTC_SYMBOL, symlen);
	पूर्ण अन्यथा अणु
		symlen = unresolved_col_width + 4 + 2;
		hists__new_col_len(hists, HISTC_SYMBOL, symlen);
		hists__set_unres_dso_col_len(hists, HISTC_DSO);
	पूर्ण

	len = thपढ़ो__comm_len(h->thपढ़ो);
	अगर (hists__new_col_len(hists, HISTC_COMM, len))
		hists__set_col_len(hists, HISTC_THREAD, len + 8);

	अगर (h->ms.map) अणु
		len = dso__name_len(h->ms.map->dso);
		hists__new_col_len(hists, HISTC_DSO, len);
	पूर्ण

	अगर (h->parent)
		hists__new_col_len(hists, HISTC_PARENT, h->parent->namelen);

	अगर (h->branch_info) अणु
		अगर (h->branch_info->from.ms.sym) अणु
			symlen = (पूर्णांक)h->branch_info->from.ms.sym->namelen + 4;
			अगर (verbose > 0)
				symlen += BITS_PER_LONG / 4 + 2 + 3;
			hists__new_col_len(hists, HISTC_SYMBOL_FROM, symlen);

			symlen = dso__name_len(h->branch_info->from.ms.map->dso);
			hists__new_col_len(hists, HISTC_DSO_FROM, symlen);
		पूर्ण अन्यथा अणु
			symlen = unresolved_col_width + 4 + 2;
			hists__new_col_len(hists, HISTC_SYMBOL_FROM, symlen);
			hists__set_unres_dso_col_len(hists, HISTC_DSO_FROM);
		पूर्ण

		अगर (h->branch_info->to.ms.sym) अणु
			symlen = (पूर्णांक)h->branch_info->to.ms.sym->namelen + 4;
			अगर (verbose > 0)
				symlen += BITS_PER_LONG / 4 + 2 + 3;
			hists__new_col_len(hists, HISTC_SYMBOL_TO, symlen);

			symlen = dso__name_len(h->branch_info->to.ms.map->dso);
			hists__new_col_len(hists, HISTC_DSO_TO, symlen);
		पूर्ण अन्यथा अणु
			symlen = unresolved_col_width + 4 + 2;
			hists__new_col_len(hists, HISTC_SYMBOL_TO, symlen);
			hists__set_unres_dso_col_len(hists, HISTC_DSO_TO);
		पूर्ण

		अगर (h->branch_info->srcline_from)
			hists__new_col_len(hists, HISTC_SRCLINE_FROM,
					म_माप(h->branch_info->srcline_from));
		अगर (h->branch_info->srcline_to)
			hists__new_col_len(hists, HISTC_SRCLINE_TO,
					म_माप(h->branch_info->srcline_to));
	पूर्ण

	अगर (h->mem_info) अणु
		अगर (h->mem_info->daddr.ms.sym) अणु
			symlen = (पूर्णांक)h->mem_info->daddr.ms.sym->namelen + 4
			       + unresolved_col_width + 2;
			hists__new_col_len(hists, HISTC_MEM_DADDR_SYMBOL,
					   symlen);
			hists__new_col_len(hists, HISTC_MEM_DCACHELINE,
					   symlen + 1);
		पूर्ण अन्यथा अणु
			symlen = unresolved_col_width + 4 + 2;
			hists__new_col_len(hists, HISTC_MEM_DADDR_SYMBOL,
					   symlen);
			hists__new_col_len(hists, HISTC_MEM_DCACHELINE,
					   symlen);
		पूर्ण

		अगर (h->mem_info->iaddr.ms.sym) अणु
			symlen = (पूर्णांक)h->mem_info->iaddr.ms.sym->namelen + 4
			       + unresolved_col_width + 2;
			hists__new_col_len(hists, HISTC_MEM_IADDR_SYMBOL,
					   symlen);
		पूर्ण अन्यथा अणु
			symlen = unresolved_col_width + 4 + 2;
			hists__new_col_len(hists, HISTC_MEM_IADDR_SYMBOL,
					   symlen);
		पूर्ण

		अगर (h->mem_info->daddr.ms.map) अणु
			symlen = dso__name_len(h->mem_info->daddr.ms.map->dso);
			hists__new_col_len(hists, HISTC_MEM_DADDR_DSO,
					   symlen);
		पूर्ण अन्यथा अणु
			symlen = unresolved_col_width + 4 + 2;
			hists__set_unres_dso_col_len(hists, HISTC_MEM_DADDR_DSO);
		पूर्ण

		hists__new_col_len(hists, HISTC_MEM_PHYS_DADDR,
				   unresolved_col_width + 4 + 2);

		hists__new_col_len(hists, HISTC_MEM_DATA_PAGE_SIZE,
				   unresolved_col_width + 4 + 2);

	पूर्ण अन्यथा अणु
		symlen = unresolved_col_width + 4 + 2;
		hists__new_col_len(hists, HISTC_MEM_DADDR_SYMBOL, symlen);
		hists__new_col_len(hists, HISTC_MEM_IADDR_SYMBOL, symlen);
		hists__set_unres_dso_col_len(hists, HISTC_MEM_DADDR_DSO);
	पूर्ण

	hists__new_col_len(hists, HISTC_CGROUP, 6);
	hists__new_col_len(hists, HISTC_CGROUP_ID, 20);
	hists__new_col_len(hists, HISTC_CPU, 3);
	hists__new_col_len(hists, HISTC_SOCKET, 6);
	hists__new_col_len(hists, HISTC_MEM_LOCKED, 6);
	hists__new_col_len(hists, HISTC_MEM_TLB, 22);
	hists__new_col_len(hists, HISTC_MEM_SNOOP, 12);
	hists__new_col_len(hists, HISTC_MEM_LVL, 21 + 3);
	hists__new_col_len(hists, HISTC_LOCAL_WEIGHT, 12);
	hists__new_col_len(hists, HISTC_GLOBAL_WEIGHT, 12);
	hists__new_col_len(hists, HISTC_MEM_BLOCKED, 10);
	hists__new_col_len(hists, HISTC_LOCAL_INS_LAT, 13);
	hists__new_col_len(hists, HISTC_GLOBAL_INS_LAT, 13);
	hists__new_col_len(hists, HISTC_P_STAGE_CYC, 13);
	अगर (symbol_conf.nanosecs)
		hists__new_col_len(hists, HISTC_TIME, 16);
	अन्यथा
		hists__new_col_len(hists, HISTC_TIME, 12);
	hists__new_col_len(hists, HISTC_CODE_PAGE_SIZE, 6);

	अगर (h->srcline) अणु
		len = MAX(म_माप(h->srcline), म_माप(sort_srcline.se_header));
		hists__new_col_len(hists, HISTC_SRCLINE, len);
	पूर्ण

	अगर (h->srcfile)
		hists__new_col_len(hists, HISTC_SRCखाता, म_माप(h->srcfile));

	अगर (h->transaction)
		hists__new_col_len(hists, HISTC_TRANSACTION,
				   hist_entry__transaction_len());

	अगर (h->trace_output)
		hists__new_col_len(hists, HISTC_TRACE, म_माप(h->trace_output));

	अगर (h->cgroup) अणु
		स्थिर अक्षर *cgrp_name = "unknown";
		काष्ठा cgroup *cgrp = cgroup__find(h->ms.maps->machine->env,
						   h->cgroup);
		अगर (cgrp != शून्य)
			cgrp_name = cgrp->name;

		hists__new_col_len(hists, HISTC_CGROUP, म_माप(cgrp_name));
	पूर्ण
पूर्ण

व्योम hists__output_recalc_col_len(काष्ठा hists *hists, पूर्णांक max_rows)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);
	काष्ठा hist_entry *n;
	पूर्णांक row = 0;

	hists__reset_col_len(hists);

	जबतक (next && row++ < max_rows) अणु
		n = rb_entry(next, काष्ठा hist_entry, rb_node);
		अगर (!n->filtered)
			hists__calc_col_len(hists, n);
		next = rb_next(&n->rb_node);
	पूर्ण
पूर्ण

अटल व्योम he_stat__add_cpumode_period(काष्ठा he_stat *he_stat,
					अचिन्हित पूर्णांक cpumode, u64 period)
अणु
	चयन (cpumode) अणु
	हाल PERF_RECORD_MISC_KERNEL:
		he_stat->period_sys += period;
		अवरोध;
	हाल PERF_RECORD_MISC_USER:
		he_stat->period_us += period;
		अवरोध;
	हाल PERF_RECORD_MISC_GUEST_KERNEL:
		he_stat->period_guest_sys += period;
		अवरोध;
	हाल PERF_RECORD_MISC_GUEST_USER:
		he_stat->period_guest_us += period;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल दीर्घ hist_समय(अचिन्हित दीर्घ hसमय)
अणु
	अचिन्हित दीर्घ समय_quantum = symbol_conf.समय_quantum;
	अगर (समय_quantum)
		वापस (hसमय / समय_quantum) * समय_quantum;
	वापस hसमय;
पूर्ण

अटल व्योम he_stat__add_period(काष्ठा he_stat *he_stat, u64 period,
				u64 weight, u64 ins_lat, u64 p_stage_cyc)
अणु

	he_stat->period		+= period;
	he_stat->weight		+= weight;
	he_stat->nr_events	+= 1;
	he_stat->ins_lat	+= ins_lat;
	he_stat->p_stage_cyc	+= p_stage_cyc;
पूर्ण

अटल व्योम he_stat__add_stat(काष्ठा he_stat *dest, काष्ठा he_stat *src)
अणु
	dest->period		+= src->period;
	dest->period_sys	+= src->period_sys;
	dest->period_us		+= src->period_us;
	dest->period_guest_sys	+= src->period_guest_sys;
	dest->period_guest_us	+= src->period_guest_us;
	dest->nr_events		+= src->nr_events;
	dest->weight		+= src->weight;
	dest->ins_lat		+= src->ins_lat;
	dest->p_stage_cyc		+= src->p_stage_cyc;
पूर्ण

अटल व्योम he_stat__decay(काष्ठा he_stat *he_stat)
अणु
	he_stat->period = (he_stat->period * 7) / 8;
	he_stat->nr_events = (he_stat->nr_events * 7) / 8;
	/* XXX need decay क्रम weight too? */
पूर्ण

अटल व्योम hists__delete_entry(काष्ठा hists *hists, काष्ठा hist_entry *he);

अटल bool hists__decay_entry(काष्ठा hists *hists, काष्ठा hist_entry *he)
अणु
	u64 prev_period = he->stat.period;
	u64 dअगरf;

	अगर (prev_period == 0)
		वापस true;

	he_stat__decay(&he->stat);
	अगर (symbol_conf.cumulate_callchain)
		he_stat__decay(he->stat_acc);
	decay_callchain(he->callchain);

	dअगरf = prev_period - he->stat.period;

	अगर (!he->depth) अणु
		hists->stats.total_period -= dअगरf;
		अगर (!he->filtered)
			hists->stats.total_non_filtered_period -= dअगरf;
	पूर्ण

	अगर (!he->leaf) अणु
		काष्ठा hist_entry *child;
		काष्ठा rb_node *node = rb_first_cached(&he->hroot_out);
		जबतक (node) अणु
			child = rb_entry(node, काष्ठा hist_entry, rb_node);
			node = rb_next(node);

			अगर (hists__decay_entry(hists, child))
				hists__delete_entry(hists, child);
		पूर्ण
	पूर्ण

	वापस he->stat.period == 0;
पूर्ण

अटल व्योम hists__delete_entry(काष्ठा hists *hists, काष्ठा hist_entry *he)
अणु
	काष्ठा rb_root_cached *root_in;
	काष्ठा rb_root_cached *root_out;

	अगर (he->parent_he) अणु
		root_in  = &he->parent_he->hroot_in;
		root_out = &he->parent_he->hroot_out;
	पूर्ण अन्यथा अणु
		अगर (hists__has(hists, need_collapse))
			root_in = &hists->entries_collapsed;
		अन्यथा
			root_in = hists->entries_in;
		root_out = &hists->entries;
	पूर्ण

	rb_erase_cached(&he->rb_node_in, root_in);
	rb_erase_cached(&he->rb_node, root_out);

	--hists->nr_entries;
	अगर (!he->filtered)
		--hists->nr_non_filtered_entries;

	hist_entry__delete(he);
पूर्ण

व्योम hists__decay_entries(काष्ठा hists *hists, bool zap_user, bool zap_kernel)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);
	काष्ठा hist_entry *n;

	जबतक (next) अणु
		n = rb_entry(next, काष्ठा hist_entry, rb_node);
		next = rb_next(&n->rb_node);
		अगर (((zap_user && n->level == '.') ||
		     (zap_kernel && n->level != '.') ||
		     hists__decay_entry(hists, n))) अणु
			hists__delete_entry(hists, n);
		पूर्ण
	पूर्ण
पूर्ण

व्योम hists__delete_entries(काष्ठा hists *hists)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);
	काष्ठा hist_entry *n;

	जबतक (next) अणु
		n = rb_entry(next, काष्ठा hist_entry, rb_node);
		next = rb_next(&n->rb_node);

		hists__delete_entry(hists, n);
	पूर्ण
पूर्ण

काष्ठा hist_entry *hists__get_entry(काष्ठा hists *hists, पूर्णांक idx)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);
	काष्ठा hist_entry *n;
	पूर्णांक i = 0;

	जबतक (next) अणु
		n = rb_entry(next, काष्ठा hist_entry, rb_node);
		अगर (i == idx)
			वापस n;

		next = rb_next(&n->rb_node);
		i++;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * histogram, sorted on item, collects periods
 */

अटल पूर्णांक hist_entry__init(काष्ठा hist_entry *he,
			    काष्ठा hist_entry *ढाँचा,
			    bool sample_self,
			    माप_प्रकार callchain_size)
अणु
	*he = *ढाँचा;
	he->callchain_size = callchain_size;

	अगर (symbol_conf.cumulate_callchain) अणु
		he->stat_acc = दो_स्मृति(माप(he->stat));
		अगर (he->stat_acc == शून्य)
			वापस -ENOMEM;
		स_नकल(he->stat_acc, &he->stat, माप(he->stat));
		अगर (!sample_self)
			स_रखो(&he->stat, 0, माप(he->stat));
	पूर्ण

	map__get(he->ms.map);

	अगर (he->branch_info) अणु
		/*
		 * This branch info is (a part of) allocated from
		 * sample__resolve_bstack() and will be मुक्तd after
		 * adding new entries.  So we need to save a copy.
		 */
		he->branch_info = दो_स्मृति(माप(*he->branch_info));
		अगर (he->branch_info == शून्य)
			जाओ err;

		स_नकल(he->branch_info, ढाँचा->branch_info,
		       माप(*he->branch_info));

		map__get(he->branch_info->from.ms.map);
		map__get(he->branch_info->to.ms.map);
	पूर्ण

	अगर (he->mem_info) अणु
		map__get(he->mem_info->iaddr.ms.map);
		map__get(he->mem_info->daddr.ms.map);
	पूर्ण

	अगर (hist_entry__has_callchains(he) && symbol_conf.use_callchain)
		callchain_init(he->callchain);

	अगर (he->raw_data) अणु
		he->raw_data = memdup(he->raw_data, he->raw_size);
		अगर (he->raw_data == शून्य)
			जाओ err_infos;
	पूर्ण

	अगर (he->srcline) अणु
		he->srcline = strdup(he->srcline);
		अगर (he->srcline == शून्य)
			जाओ err_rawdata;
	पूर्ण

	अगर (symbol_conf.res_sample) अणु
		he->res_samples = सुस्मृति(माप(काष्ठा res_sample),
					symbol_conf.res_sample);
		अगर (!he->res_samples)
			जाओ err_srcline;
	पूर्ण

	INIT_LIST_HEAD(&he->pairs.node);
	thपढ़ो__get(he->thपढ़ो);
	he->hroot_in  = RB_ROOT_CACHED;
	he->hroot_out = RB_ROOT_CACHED;

	अगर (!symbol_conf.report_hierarchy)
		he->leaf = true;

	वापस 0;

err_srcline:
	zमुक्त(&he->srcline);

err_rawdata:
	zमुक्त(&he->raw_data);

err_infos:
	अगर (he->branch_info) अणु
		map__put(he->branch_info->from.ms.map);
		map__put(he->branch_info->to.ms.map);
		zमुक्त(&he->branch_info);
	पूर्ण
	अगर (he->mem_info) अणु
		map__put(he->mem_info->iaddr.ms.map);
		map__put(he->mem_info->daddr.ms.map);
	पूर्ण
err:
	map__zput(he->ms.map);
	zमुक्त(&he->stat_acc);
	वापस -ENOMEM;
पूर्ण

अटल व्योम *hist_entry__zalloc(माप_प्रकार size)
अणु
	वापस zalloc(size + माप(काष्ठा hist_entry));
पूर्ण

अटल व्योम hist_entry__मुक्त(व्योम *ptr)
अणु
	मुक्त(ptr);
पूर्ण

अटल काष्ठा hist_entry_ops शेष_ops = अणु
	.new	= hist_entry__zalloc,
	.मुक्त	= hist_entry__मुक्त,
पूर्ण;

अटल काष्ठा hist_entry *hist_entry__new(काष्ठा hist_entry *ढाँचा,
					  bool sample_self)
अणु
	काष्ठा hist_entry_ops *ops = ढाँचा->ops;
	माप_प्रकार callchain_size = 0;
	काष्ठा hist_entry *he;
	पूर्णांक err = 0;

	अगर (!ops)
		ops = ढाँचा->ops = &शेष_ops;

	अगर (symbol_conf.use_callchain)
		callchain_size = माप(काष्ठा callchain_root);

	he = ops->new(callchain_size);
	अगर (he) अणु
		err = hist_entry__init(he, ढाँचा, sample_self, callchain_size);
		अगर (err) अणु
			ops->मुक्त(he);
			he = शून्य;
		पूर्ण
	पूर्ण

	वापस he;
पूर्ण

अटल u8 symbol__parent_filter(स्थिर काष्ठा symbol *parent)
अणु
	अगर (symbol_conf.exclude_other && parent == शून्य)
		वापस 1 << HIST_FILTER__PARENT;
	वापस 0;
पूर्ण

अटल व्योम hist_entry__add_callchain_period(काष्ठा hist_entry *he, u64 period)
अणु
	अगर (!hist_entry__has_callchains(he) || !symbol_conf.use_callchain)
		वापस;

	he->hists->callchain_period += period;
	अगर (!he->filtered)
		he->hists->callchain_non_filtered_period += period;
पूर्ण

अटल काष्ठा hist_entry *hists__findnew_entry(काष्ठा hists *hists,
					       काष्ठा hist_entry *entry,
					       काष्ठा addr_location *al,
					       bool sample_self)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *he;
	पूर्णांक64_t cmp;
	u64 period = entry->stat.period;
	u64 weight = entry->stat.weight;
	u64 ins_lat = entry->stat.ins_lat;
	u64 p_stage_cyc = entry->stat.p_stage_cyc;
	bool lefपंचांगost = true;

	p = &hists->entries_in->rb_root.rb_node;

	जबतक (*p != शून्य) अणु
		parent = *p;
		he = rb_entry(parent, काष्ठा hist_entry, rb_node_in);

		/*
		 * Make sure that it receives arguments in a same order as
		 * hist_entry__collapse() so that we can use an appropriate
		 * function when searching an entry regardless which sort
		 * keys were used.
		 */
		cmp = hist_entry__cmp(he, entry);

		अगर (!cmp) अणु
			अगर (sample_self) अणु
				he_stat__add_period(&he->stat, period, weight, ins_lat, p_stage_cyc);
				hist_entry__add_callchain_period(he, period);
			पूर्ण
			अगर (symbol_conf.cumulate_callchain)
				he_stat__add_period(he->stat_acc, period, weight, ins_lat, p_stage_cyc);

			/*
			 * This mem info was allocated from sample__resolve_mem
			 * and will not be used anymore.
			 */
			mem_info__zput(entry->mem_info);

			block_info__zput(entry->block_info);

			/* If the map of an existing hist_entry has
			 * become out-of-date due to an exec() or
			 * similar, update it.  Otherwise we will
			 * mis-adjust symbol addresses when computing
			 * the history counter to increment.
			 */
			अगर (he->ms.map != entry->ms.map) अणु
				map__put(he->ms.map);
				he->ms.map = map__get(entry->ms.map);
			पूर्ण
			जाओ out;
		पूर्ण

		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	he = hist_entry__new(entry, sample_self);
	अगर (!he)
		वापस शून्य;

	अगर (sample_self)
		hist_entry__add_callchain_period(he, period);
	hists->nr_entries++;

	rb_link_node(&he->rb_node_in, parent, p);
	rb_insert_color_cached(&he->rb_node_in, hists->entries_in, lefपंचांगost);
out:
	अगर (sample_self)
		he_stat__add_cpumode_period(&he->stat, al->cpumode, period);
	अगर (symbol_conf.cumulate_callchain)
		he_stat__add_cpumode_period(he->stat_acc, al->cpumode, period);
	वापस he;
पूर्ण

अटल अचिन्हित अक्रमom_max(अचिन्हित high)
अणु
	अचिन्हित thresh = -high % high;
	क्रम (;;) अणु
		अचिन्हित r = अक्रमom();
		अगर (r >= thresh)
			वापस r % high;
	पूर्ण
पूर्ण

अटल व्योम hists__res_sample(काष्ठा hist_entry *he, काष्ठा perf_sample *sample)
अणु
	काष्ठा res_sample *r;
	पूर्णांक j;

	अगर (he->num_res < symbol_conf.res_sample) अणु
		j = he->num_res++;
	पूर्ण अन्यथा अणु
		j = अक्रमom_max(symbol_conf.res_sample);
	पूर्ण
	r = &he->res_samples[j];
	r->समय = sample->समय;
	r->cpu = sample->cpu;
	r->tid = sample->tid;
पूर्ण

अटल काष्ठा hist_entry*
__hists__add_entry(काष्ठा hists *hists,
		   काष्ठा addr_location *al,
		   काष्ठा symbol *sym_parent,
		   काष्ठा branch_info *bi,
		   काष्ठा mem_info *mi,
		   काष्ठा block_info *block_info,
		   काष्ठा perf_sample *sample,
		   bool sample_self,
		   काष्ठा hist_entry_ops *ops)
अणु
	काष्ठा namespaces *ns = thपढ़ो__namespaces(al->thपढ़ो);
	काष्ठा hist_entry entry = अणु
		.thपढ़ो	= al->thपढ़ो,
		.comm = thपढ़ो__comm(al->thपढ़ो),
		.cgroup_id = अणु
			.dev = ns ? ns->link_info[CGROUP_NS_INDEX].dev : 0,
			.ino = ns ? ns->link_info[CGROUP_NS_INDEX].ino : 0,
		पूर्ण,
		.cgroup = sample->cgroup,
		.ms = अणु
			.maps	= al->maps,
			.map	= al->map,
			.sym	= al->sym,
		पूर्ण,
		.srcline = (अक्षर *) al->srcline,
		.socket	 = al->socket,
		.cpu	 = al->cpu,
		.cpumode = al->cpumode,
		.ip	 = al->addr,
		.level	 = al->level,
		.code_page_size = sample->code_page_size,
		.stat = अणु
			.nr_events = 1,
			.period	= sample->period,
			.weight = sample->weight,
			.ins_lat = sample->ins_lat,
			.p_stage_cyc = sample->p_stage_cyc,
		पूर्ण,
		.parent = sym_parent,
		.filtered = symbol__parent_filter(sym_parent) | al->filtered,
		.hists	= hists,
		.branch_info = bi,
		.mem_info = mi,
		.block_info = block_info,
		.transaction = sample->transaction,
		.raw_data = sample->raw_data,
		.raw_size = sample->raw_size,
		.ops = ops,
		.समय = hist_समय(sample->समय),
	पूर्ण, *he = hists__findnew_entry(hists, &entry, al, sample_self);

	अगर (!hists->has_callchains && he && he->callchain_size != 0)
		hists->has_callchains = true;
	अगर (he && symbol_conf.res_sample)
		hists__res_sample(he, sample);
	वापस he;
पूर्ण

काष्ठा hist_entry *hists__add_entry(काष्ठा hists *hists,
				    काष्ठा addr_location *al,
				    काष्ठा symbol *sym_parent,
				    काष्ठा branch_info *bi,
				    काष्ठा mem_info *mi,
				    काष्ठा perf_sample *sample,
				    bool sample_self)
अणु
	वापस __hists__add_entry(hists, al, sym_parent, bi, mi, शून्य,
				  sample, sample_self, शून्य);
पूर्ण

काष्ठा hist_entry *hists__add_entry_ops(काष्ठा hists *hists,
					काष्ठा hist_entry_ops *ops,
					काष्ठा addr_location *al,
					काष्ठा symbol *sym_parent,
					काष्ठा branch_info *bi,
					काष्ठा mem_info *mi,
					काष्ठा perf_sample *sample,
					bool sample_self)
अणु
	वापस __hists__add_entry(hists, al, sym_parent, bi, mi, शून्य,
				  sample, sample_self, ops);
पूर्ण

काष्ठा hist_entry *hists__add_entry_block(काष्ठा hists *hists,
					  काष्ठा addr_location *al,
					  काष्ठा block_info *block_info)
अणु
	काष्ठा hist_entry entry = अणु
		.block_info = block_info,
		.hists = hists,
		.ms = अणु
			.maps = al->maps,
			.map = al->map,
			.sym = al->sym,
		पूर्ण,
	पूर्ण, *he = hists__findnew_entry(hists, &entry, al, false);

	वापस he;
पूर्ण

अटल पूर्णांक
iter_next_nop_entry(काष्ठा hist_entry_iter *iter __maybe_unused,
		    काष्ठा addr_location *al __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_add_next_nop_entry(काष्ठा hist_entry_iter *iter __maybe_unused,
			काष्ठा addr_location *al __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_prepare_mem_entry(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al)
अणु
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा mem_info *mi;

	mi = sample__resolve_mem(sample, al);
	अगर (mi == शून्य)
		वापस -ENOMEM;

	iter->priv = mi;
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_add_single_mem_entry(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al)
अणु
	u64 cost;
	काष्ठा mem_info *mi = iter->priv;
	काष्ठा hists *hists = evsel__hists(iter->evsel);
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा hist_entry *he;

	अगर (mi == शून्य)
		वापस -EINVAL;

	cost = sample->weight;
	अगर (!cost)
		cost = 1;

	/*
	 * must pass period=weight in order to get the correct
	 * sorting from hists__collapse_resort() which is solely
	 * based on periods. We want sorting be करोne on nr_events * weight
	 * and this is indirectly achieved by passing period=weight here
	 * and the he_stat__add_period() function.
	 */
	sample->period = cost;

	he = hists__add_entry(hists, al, iter->parent, शून्य, mi,
			      sample, true);
	अगर (!he)
		वापस -ENOMEM;

	iter->he = he;
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_finish_mem_entry(काष्ठा hist_entry_iter *iter,
		      काष्ठा addr_location *al __maybe_unused)
अणु
	काष्ठा evsel *evsel = iter->evsel;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry *he = iter->he;
	पूर्णांक err = -EINVAL;

	अगर (he == शून्य)
		जाओ out;

	hists__inc_nr_samples(hists, he->filtered);

	err = hist_entry__append_callchain(he, iter->sample);

out:
	/*
	 * We करोn't need to मुक्त iter->priv (mem_info) here since the mem info
	 * was either alपढ़ोy मुक्तd in hists__findnew_entry() or passed to a
	 * new hist entry by hist_entry__new().
	 */
	iter->priv = शून्य;

	iter->he = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक
iter_prepare_branch_entry(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al)
अणु
	काष्ठा branch_info *bi;
	काष्ठा perf_sample *sample = iter->sample;

	bi = sample__resolve_bstack(sample, al);
	अगर (!bi)
		वापस -ENOMEM;

	iter->curr = 0;
	iter->total = sample->branch_stack->nr;

	iter->priv = bi;
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_add_single_branch_entry(काष्ठा hist_entry_iter *iter __maybe_unused,
			     काष्ठा addr_location *al __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_next_branch_entry(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al)
अणु
	काष्ठा branch_info *bi = iter->priv;
	पूर्णांक i = iter->curr;

	अगर (bi == शून्य)
		वापस 0;

	अगर (iter->curr >= iter->total)
		वापस 0;

	al->maps = bi[i].to.ms.maps;
	al->map = bi[i].to.ms.map;
	al->sym = bi[i].to.ms.sym;
	al->addr = bi[i].to.addr;
	वापस 1;
पूर्ण

अटल पूर्णांक
iter_add_next_branch_entry(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al)
अणु
	काष्ठा branch_info *bi;
	काष्ठा evsel *evsel = iter->evsel;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा hist_entry *he = शून्य;
	पूर्णांक i = iter->curr;
	पूर्णांक err = 0;

	bi = iter->priv;

	अगर (iter->hide_unresolved && !(bi[i].from.ms.sym && bi[i].to.ms.sym))
		जाओ out;

	/*
	 * The report shows the percentage of total branches captured
	 * and not events sampled. Thus we use a pseuकरो period of 1.
	 */
	sample->period = 1;
	sample->weight = bi->flags.cycles ? bi->flags.cycles : 1;

	he = hists__add_entry(hists, al, iter->parent, &bi[i], शून्य,
			      sample, true);
	अगर (he == शून्य)
		वापस -ENOMEM;

	hists__inc_nr_samples(hists, he->filtered);

out:
	iter->he = he;
	iter->curr++;
	वापस err;
पूर्ण

अटल पूर्णांक
iter_finish_branch_entry(काष्ठा hist_entry_iter *iter,
			 काष्ठा addr_location *al __maybe_unused)
अणु
	zमुक्त(&iter->priv);
	iter->he = शून्य;

	वापस iter->curr >= iter->total ? 0 : -1;
पूर्ण

अटल पूर्णांक
iter_prepare_normal_entry(काष्ठा hist_entry_iter *iter __maybe_unused,
			  काष्ठा addr_location *al __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_add_single_normal_entry(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al)
अणु
	काष्ठा evsel *evsel = iter->evsel;
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा hist_entry *he;

	he = hists__add_entry(evsel__hists(evsel), al, iter->parent, शून्य, शून्य,
			      sample, true);
	अगर (he == शून्य)
		वापस -ENOMEM;

	iter->he = he;
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_finish_normal_entry(काष्ठा hist_entry_iter *iter,
			 काष्ठा addr_location *al __maybe_unused)
अणु
	काष्ठा hist_entry *he = iter->he;
	काष्ठा evsel *evsel = iter->evsel;
	काष्ठा perf_sample *sample = iter->sample;

	अगर (he == शून्य)
		वापस 0;

	iter->he = शून्य;

	hists__inc_nr_samples(evsel__hists(evsel), he->filtered);

	वापस hist_entry__append_callchain(he, sample);
पूर्ण

अटल पूर्णांक
iter_prepare_cumulative_entry(काष्ठा hist_entry_iter *iter,
			      काष्ठा addr_location *al __maybe_unused)
अणु
	काष्ठा hist_entry **he_cache;

	callchain_cursor_commit(&callchain_cursor);

	/*
	 * This is क्रम detecting cycles or recursions so that they're
	 * cumulated only one समय to prevent entries more than 100%
	 * overhead.
	 */
	he_cache = दो_स्मृति(माप(*he_cache) * (callchain_cursor.nr + 1));
	अगर (he_cache == शून्य)
		वापस -ENOMEM;

	iter->priv = he_cache;
	iter->curr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
iter_add_single_cumulative_entry(काष्ठा hist_entry_iter *iter,
				 काष्ठा addr_location *al)
अणु
	काष्ठा evsel *evsel = iter->evsel;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा hist_entry **he_cache = iter->priv;
	काष्ठा hist_entry *he;
	पूर्णांक err = 0;

	he = hists__add_entry(hists, al, iter->parent, शून्य, शून्य,
			      sample, true);
	अगर (he == शून्य)
		वापस -ENOMEM;

	iter->he = he;
	he_cache[iter->curr++] = he;

	hist_entry__append_callchain(he, sample);

	/*
	 * We need to re-initialize the cursor since callchain_append()
	 * advanced the cursor to the end.
	 */
	callchain_cursor_commit(&callchain_cursor);

	hists__inc_nr_samples(hists, he->filtered);

	वापस err;
पूर्ण

अटल पूर्णांक
iter_next_cumulative_entry(काष्ठा hist_entry_iter *iter,
			   काष्ठा addr_location *al)
अणु
	काष्ठा callchain_cursor_node *node;

	node = callchain_cursor_current(&callchain_cursor);
	अगर (node == शून्य)
		वापस 0;

	वापस fill_callchain_info(al, node, iter->hide_unresolved);
पूर्ण

अटल bool
hist_entry__fast__sym_dअगरf(काष्ठा hist_entry *left,
			   काष्ठा hist_entry *right)
अणु
	काष्ठा symbol *sym_l = left->ms.sym;
	काष्ठा symbol *sym_r = right->ms.sym;

	अगर (!sym_l && !sym_r)
		वापस left->ip != right->ip;

	वापस !!_sort__sym_cmp(sym_l, sym_r);
पूर्ण


अटल पूर्णांक
iter_add_next_cumulative_entry(काष्ठा hist_entry_iter *iter,
			       काष्ठा addr_location *al)
अणु
	काष्ठा evsel *evsel = iter->evsel;
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा hist_entry **he_cache = iter->priv;
	काष्ठा hist_entry *he;
	काष्ठा hist_entry he_पंचांगp = अणु
		.hists = evsel__hists(evsel),
		.cpu = al->cpu,
		.thपढ़ो = al->thपढ़ो,
		.comm = thपढ़ो__comm(al->thपढ़ो),
		.ip = al->addr,
		.ms = अणु
			.maps = al->maps,
			.map = al->map,
			.sym = al->sym,
		पूर्ण,
		.srcline = (अक्षर *) al->srcline,
		.parent = iter->parent,
		.raw_data = sample->raw_data,
		.raw_size = sample->raw_size,
	पूर्ण;
	पूर्णांक i;
	काष्ठा callchain_cursor cursor;
	bool fast = hists__has(he_पंचांगp.hists, sym);

	callchain_cursor_snapshot(&cursor, &callchain_cursor);

	callchain_cursor_advance(&callchain_cursor);

	/*
	 * Check अगर there's duplicate entries in the callchain.
	 * It's possible that it has cycles or recursive calls.
	 */
	क्रम (i = 0; i < iter->curr; i++) अणु
		/*
		 * For most हालs, there are no duplicate entries in callchain.
		 * The symbols are usually dअगरferent. Do a quick check क्रम
		 * symbols first.
		 */
		अगर (fast && hist_entry__fast__sym_dअगरf(he_cache[i], &he_पंचांगp))
			जारी;

		अगर (hist_entry__cmp(he_cache[i], &he_पंचांगp) == 0) अणु
			/* to aव्योम calling callback function */
			iter->he = शून्य;
			वापस 0;
		पूर्ण
	पूर्ण

	he = hists__add_entry(evsel__hists(evsel), al, iter->parent, शून्य, शून्य,
			      sample, false);
	अगर (he == शून्य)
		वापस -ENOMEM;

	iter->he = he;
	he_cache[iter->curr++] = he;

	अगर (hist_entry__has_callchains(he) && symbol_conf.use_callchain)
		callchain_append(he->callchain, &cursor, sample->period);
	वापस 0;
पूर्ण

अटल पूर्णांक
iter_finish_cumulative_entry(काष्ठा hist_entry_iter *iter,
			     काष्ठा addr_location *al __maybe_unused)
अणु
	zमुक्त(&iter->priv);
	iter->he = शून्य;

	वापस 0;
पूर्ण

स्थिर काष्ठा hist_iter_ops hist_iter_mem = अणु
	.prepare_entry 		= iter_prepare_mem_entry,
	.add_single_entry 	= iter_add_single_mem_entry,
	.next_entry 		= iter_next_nop_entry,
	.add_next_entry 	= iter_add_next_nop_entry,
	.finish_entry 		= iter_finish_mem_entry,
पूर्ण;

स्थिर काष्ठा hist_iter_ops hist_iter_branch = अणु
	.prepare_entry 		= iter_prepare_branch_entry,
	.add_single_entry 	= iter_add_single_branch_entry,
	.next_entry 		= iter_next_branch_entry,
	.add_next_entry 	= iter_add_next_branch_entry,
	.finish_entry 		= iter_finish_branch_entry,
पूर्ण;

स्थिर काष्ठा hist_iter_ops hist_iter_normal = अणु
	.prepare_entry 		= iter_prepare_normal_entry,
	.add_single_entry 	= iter_add_single_normal_entry,
	.next_entry 		= iter_next_nop_entry,
	.add_next_entry 	= iter_add_next_nop_entry,
	.finish_entry 		= iter_finish_normal_entry,
पूर्ण;

स्थिर काष्ठा hist_iter_ops hist_iter_cumulative = अणु
	.prepare_entry 		= iter_prepare_cumulative_entry,
	.add_single_entry 	= iter_add_single_cumulative_entry,
	.next_entry 		= iter_next_cumulative_entry,
	.add_next_entry 	= iter_add_next_cumulative_entry,
	.finish_entry 		= iter_finish_cumulative_entry,
पूर्ण;

पूर्णांक hist_entry_iter__add(काष्ठा hist_entry_iter *iter, काष्ठा addr_location *al,
			 पूर्णांक max_stack_depth, व्योम *arg)
अणु
	पूर्णांक err, err2;
	काष्ठा map *alm = शून्य;

	अगर (al)
		alm = map__get(al->map);

	err = sample__resolve_callchain(iter->sample, &callchain_cursor, &iter->parent,
					iter->evsel, al, max_stack_depth);
	अगर (err) अणु
		map__put(alm);
		वापस err;
	पूर्ण

	err = iter->ops->prepare_entry(iter, al);
	अगर (err)
		जाओ out;

	err = iter->ops->add_single_entry(iter, al);
	अगर (err)
		जाओ out;

	अगर (iter->he && iter->add_entry_cb) अणु
		err = iter->add_entry_cb(iter, al, true, arg);
		अगर (err)
			जाओ out;
	पूर्ण

	जबतक (iter->ops->next_entry(iter, al)) अणु
		err = iter->ops->add_next_entry(iter, al);
		अगर (err)
			अवरोध;

		अगर (iter->he && iter->add_entry_cb) अणु
			err = iter->add_entry_cb(iter, al, false, arg);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	err2 = iter->ops->finish_entry(iter, al);
	अगर (!err)
		err = err2;

	map__put(alm);

	वापस err;
पूर्ण

पूर्णांक64_t
hist_entry__cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा hists *hists = left->hists;
	काष्ठा perf_hpp_fmt *fmt;
	पूर्णांक64_t cmp = 0;

	hists__क्रम_each_sort_list(hists, fmt) अणु
		अगर (perf_hpp__is_dynamic_entry(fmt) &&
		    !perf_hpp__defined_dynamic_entry(fmt, hists))
			जारी;

		cmp = fmt->cmp(fmt, left, right);
		अगर (cmp)
			अवरोध;
	पूर्ण

	वापस cmp;
पूर्ण

पूर्णांक64_t
hist_entry__collapse(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा hists *hists = left->hists;
	काष्ठा perf_hpp_fmt *fmt;
	पूर्णांक64_t cmp = 0;

	hists__क्रम_each_sort_list(hists, fmt) अणु
		अगर (perf_hpp__is_dynamic_entry(fmt) &&
		    !perf_hpp__defined_dynamic_entry(fmt, hists))
			जारी;

		cmp = fmt->collapse(fmt, left, right);
		अगर (cmp)
			अवरोध;
	पूर्ण

	वापस cmp;
पूर्ण

व्योम hist_entry__delete(काष्ठा hist_entry *he)
अणु
	काष्ठा hist_entry_ops *ops = he->ops;

	thपढ़ो__zput(he->thपढ़ो);
	map__zput(he->ms.map);

	अगर (he->branch_info) अणु
		map__zput(he->branch_info->from.ms.map);
		map__zput(he->branch_info->to.ms.map);
		मुक्त_srcline(he->branch_info->srcline_from);
		मुक्त_srcline(he->branch_info->srcline_to);
		zमुक्त(&he->branch_info);
	पूर्ण

	अगर (he->mem_info) अणु
		map__zput(he->mem_info->iaddr.ms.map);
		map__zput(he->mem_info->daddr.ms.map);
		mem_info__zput(he->mem_info);
	पूर्ण

	अगर (he->block_info)
		block_info__zput(he->block_info);

	zमुक्त(&he->res_samples);
	zमुक्त(&he->stat_acc);
	मुक्त_srcline(he->srcline);
	अगर (he->srcfile && he->srcfile[0])
		zमुक्त(&he->srcfile);
	मुक्त_callchain(he->callchain);
	zमुक्त(&he->trace_output);
	zमुक्त(&he->raw_data);
	ops->मुक्त(he);
पूर्ण

/*
 * If this is not the last column, then we need to pad it according to the
 * pre-calculated max length क्रम this column, otherwise करोn't bother adding
 * spaces because that would अवरोध viewing this with, क्रम instance, 'less',
 * that would show tons of trailing spaces when a दीर्घ C++ demangled method
 * names is sampled.
*/
पूर्णांक hist_entry__snम_लिखो_alignment(काष्ठा hist_entry *he, काष्ठा perf_hpp *hpp,
				   काष्ठा perf_hpp_fmt *fmt, पूर्णांक prपूर्णांकed)
अणु
	अगर (!list_is_last(&fmt->list, &he->hists->hpp_list->fields)) अणु
		स्थिर पूर्णांक width = fmt->width(fmt, hpp, he->hists);
		अगर (prपूर्णांकed < width) अणु
			advance_hpp(hpp, prपूर्णांकed);
			prपूर्णांकed = scnम_लिखो(hpp->buf, hpp->size, "%-*s", width - prपूर्णांकed, " ");
		पूर्ण
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

/*
 * collapse the histogram
 */

अटल व्योम hists__apply_filters(काष्ठा hists *hists, काष्ठा hist_entry *he);
अटल व्योम hists__हटाओ_entry_filter(काष्ठा hists *hists, काष्ठा hist_entry *he,
				       क्रमागत hist_filter type);

प्रकार bool (*fmt_chk_fn)(काष्ठा perf_hpp_fmt *fmt);

अटल bool check_thपढ़ो_entry(काष्ठा perf_hpp_fmt *fmt)
अणु
	वापस perf_hpp__is_thपढ़ो_entry(fmt) || perf_hpp__is_comm_entry(fmt);
पूर्ण

अटल व्योम hist_entry__check_and_हटाओ_filter(काष्ठा hist_entry *he,
						क्रमागत hist_filter type,
						fmt_chk_fn check)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	bool type_match = false;
	काष्ठा hist_entry *parent = he->parent_he;

	चयन (type) अणु
	हाल HIST_FILTER__THREAD:
		अगर (symbol_conf.comm_list == शून्य &&
		    symbol_conf.pid_list == शून्य &&
		    symbol_conf.tid_list == शून्य)
			वापस;
		अवरोध;
	हाल HIST_FILTER__DSO:
		अगर (symbol_conf.dso_list == शून्य)
			वापस;
		अवरोध;
	हाल HIST_FILTER__SYMBOL:
		अगर (symbol_conf.sym_list == शून्य)
			वापस;
		अवरोध;
	हाल HIST_FILTER__PARENT:
	हाल HIST_FILTER__GUEST:
	हाल HIST_FILTER__HOST:
	हाल HIST_FILTER__SOCKET:
	हाल HIST_FILTER__C2C:
	शेष:
		वापस;
	पूर्ण

	/* अगर it's filtered by own fmt, it has to have filter bits */
	perf_hpp_list__क्रम_each_क्रमmat(he->hpp_list, fmt) अणु
		अगर (check(fmt)) अणु
			type_match = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (type_match) अणु
		/*
		 * If the filter is क्रम current level entry, propagate
		 * filter marker to parents.  The marker bit was
		 * alपढ़ोy set by शेष so it only needs to clear
		 * non-filtered entries.
		 */
		अगर (!(he->filtered & (1 << type))) अणु
			जबतक (parent) अणु
				parent->filtered &= ~(1 << type);
				parent = parent->parent_he;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If current entry करोesn't have matching क्रमmats, set
		 * filter marker क्रम upper level entries.  it will be
		 * cleared अगर its lower level entries is not filtered.
		 *
		 * For lower-level entries, it inherits parent's
		 * filter bit so that lower level entries of a
		 * non-filtered entry won't set the filter marker.
		 */
		अगर (parent == शून्य)
			he->filtered |= (1 << type);
		अन्यथा
			he->filtered |= (parent->filtered & (1 << type));
	पूर्ण
पूर्ण

अटल व्योम hist_entry__apply_hierarchy_filters(काष्ठा hist_entry *he)
अणु
	hist_entry__check_and_हटाओ_filter(he, HIST_FILTER__THREAD,
					    check_thपढ़ो_entry);

	hist_entry__check_and_हटाओ_filter(he, HIST_FILTER__DSO,
					    perf_hpp__is_dso_entry);

	hist_entry__check_and_हटाओ_filter(he, HIST_FILTER__SYMBOL,
					    perf_hpp__is_sym_entry);

	hists__apply_filters(he->hists, he);
पूर्ण

अटल काष्ठा hist_entry *hierarchy_insert_entry(काष्ठा hists *hists,
						 काष्ठा rb_root_cached *root,
						 काष्ठा hist_entry *he,
						 काष्ठा hist_entry *parent_he,
						 काष्ठा perf_hpp_list *hpp_list)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *iter, *new;
	काष्ठा perf_hpp_fmt *fmt;
	पूर्णांक64_t cmp;
	bool lefपंचांगost = true;

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा hist_entry, rb_node_in);

		cmp = 0;
		perf_hpp_list__क्रम_each_sort_list(hpp_list, fmt) अणु
			cmp = fmt->collapse(fmt, iter, he);
			अगर (cmp)
				अवरोध;
		पूर्ण

		अगर (!cmp) अणु
			he_stat__add_stat(&iter->stat, &he->stat);
			वापस iter;
		पूर्ण

		अगर (cmp < 0)
			p = &parent->rb_left;
		अन्यथा अणु
			p = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	new = hist_entry__new(he, true);
	अगर (new == शून्य)
		वापस शून्य;

	hists->nr_entries++;

	/* save related क्रमmat list क्रम output */
	new->hpp_list = hpp_list;
	new->parent_he = parent_he;

	hist_entry__apply_hierarchy_filters(new);

	/* some fields are now passed to 'new' */
	perf_hpp_list__क्रम_each_sort_list(hpp_list, fmt) अणु
		अगर (perf_hpp__is_trace_entry(fmt) || perf_hpp__is_dynamic_entry(fmt))
			he->trace_output = शून्य;
		अन्यथा
			new->trace_output = शून्य;

		अगर (perf_hpp__is_srcline_entry(fmt))
			he->srcline = शून्य;
		अन्यथा
			new->srcline = शून्य;

		अगर (perf_hpp__is_srcfile_entry(fmt))
			he->srcfile = शून्य;
		अन्यथा
			new->srcfile = शून्य;
	पूर्ण

	rb_link_node(&new->rb_node_in, parent, p);
	rb_insert_color_cached(&new->rb_node_in, root, lefपंचांगost);
	वापस new;
पूर्ण

अटल पूर्णांक hists__hierarchy_insert_entry(काष्ठा hists *hists,
					 काष्ठा rb_root_cached *root,
					 काष्ठा hist_entry *he)
अणु
	काष्ठा perf_hpp_list_node *node;
	काष्ठा hist_entry *new_he = शून्य;
	काष्ठा hist_entry *parent = शून्य;
	पूर्णांक depth = 0;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(node, &hists->hpp_क्रमmats, list) अणु
		/* skip period (overhead) and elided columns */
		अगर (node->level == 0 || node->skip)
			जारी;

		/* insert copy of 'he' क्रम each fmt पूर्णांकo the hierarchy */
		new_he = hierarchy_insert_entry(hists, root, he, parent, &node->hpp);
		अगर (new_he == शून्य) अणु
			ret = -1;
			अवरोध;
		पूर्ण

		root = &new_he->hroot_in;
		new_he->depth = depth++;
		parent = new_he;
	पूर्ण

	अगर (new_he) अणु
		new_he->leaf = true;

		अगर (hist_entry__has_callchains(new_he) &&
		    symbol_conf.use_callchain) अणु
			callchain_cursor_reset(&callchain_cursor);
			अगर (callchain_merge(&callchain_cursor,
					    new_he->callchain,
					    he->callchain) < 0)
				ret = -1;
		पूर्ण
	पूर्ण

	/* 'he' is no दीर्घer used */
	hist_entry__delete(he);

	/* वापस 0 (or -1) since it alपढ़ोy applied filters */
	वापस ret;
पूर्ण

अटल पूर्णांक hists__collapse_insert_entry(काष्ठा hists *hists,
					काष्ठा rb_root_cached *root,
					काष्ठा hist_entry *he)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *iter;
	पूर्णांक64_t cmp;
	bool lefपंचांगost = true;

	अगर (symbol_conf.report_hierarchy)
		वापस hists__hierarchy_insert_entry(hists, root, he);

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा hist_entry, rb_node_in);

		cmp = hist_entry__collapse(iter, he);

		अगर (!cmp) अणु
			पूर्णांक ret = 0;

			he_stat__add_stat(&iter->stat, &he->stat);
			अगर (symbol_conf.cumulate_callchain)
				he_stat__add_stat(iter->stat_acc, he->stat_acc);

			अगर (hist_entry__has_callchains(he) && symbol_conf.use_callchain) अणु
				callchain_cursor_reset(&callchain_cursor);
				अगर (callchain_merge(&callchain_cursor,
						    iter->callchain,
						    he->callchain) < 0)
					ret = -1;
			पूर्ण
			hist_entry__delete(he);
			वापस ret;
		पूर्ण

		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण
	hists->nr_entries++;

	rb_link_node(&he->rb_node_in, parent, p);
	rb_insert_color_cached(&he->rb_node_in, root, lefपंचांगost);
	वापस 1;
पूर्ण

काष्ठा rb_root_cached *hists__get_rotate_entries_in(काष्ठा hists *hists)
अणु
	काष्ठा rb_root_cached *root;

	pthपढ़ो_mutex_lock(&hists->lock);

	root = hists->entries_in;
	अगर (++hists->entries_in > &hists->entries_in_array[1])
		hists->entries_in = &hists->entries_in_array[0];

	pthपढ़ो_mutex_unlock(&hists->lock);

	वापस root;
पूर्ण

अटल व्योम hists__apply_filters(काष्ठा hists *hists, काष्ठा hist_entry *he)
अणु
	hists__filter_entry_by_dso(hists, he);
	hists__filter_entry_by_thपढ़ो(hists, he);
	hists__filter_entry_by_symbol(hists, he);
	hists__filter_entry_by_socket(hists, he);
पूर्ण

पूर्णांक hists__collapse_resort(काष्ठा hists *hists, काष्ठा ui_progress *prog)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *next;
	काष्ठा hist_entry *n;
	पूर्णांक ret;

	अगर (!hists__has(hists, need_collapse))
		वापस 0;

	hists->nr_entries = 0;

	root = hists__get_rotate_entries_in(hists);

	next = rb_first_cached(root);

	जबतक (next) अणु
		अगर (session_करोne())
			अवरोध;
		n = rb_entry(next, काष्ठा hist_entry, rb_node_in);
		next = rb_next(&n->rb_node_in);

		rb_erase_cached(&n->rb_node_in, root);
		ret = hists__collapse_insert_entry(hists, &hists->entries_collapsed, n);
		अगर (ret < 0)
			वापस -1;

		अगर (ret) अणु
			/*
			 * If it wasn't combined with one of the entries alपढ़ोy
			 * collapsed, we need to apply the filters that may have
			 * been set by, say, the hist_browser.
			 */
			hists__apply_filters(hists, n);
		पूर्ण
		अगर (prog)
			ui_progress__update(prog, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक64_t hist_entry__sort(काष्ठा hist_entry *a, काष्ठा hist_entry *b)
अणु
	काष्ठा hists *hists = a->hists;
	काष्ठा perf_hpp_fmt *fmt;
	पूर्णांक64_t cmp = 0;

	hists__क्रम_each_sort_list(hists, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, a->hists))
			जारी;

		cmp = fmt->sort(fmt, a, b);
		अगर (cmp)
			अवरोध;
	पूर्ण

	वापस cmp;
पूर्ण

अटल व्योम hists__reset_filter_stats(काष्ठा hists *hists)
अणु
	hists->nr_non_filtered_entries = 0;
	hists->stats.total_non_filtered_period = 0;
पूर्ण

व्योम hists__reset_stats(काष्ठा hists *hists)
अणु
	hists->nr_entries = 0;
	hists->stats.total_period = 0;

	hists__reset_filter_stats(hists);
पूर्ण

अटल व्योम hists__inc_filter_stats(काष्ठा hists *hists, काष्ठा hist_entry *h)
अणु
	hists->nr_non_filtered_entries++;
	hists->stats.total_non_filtered_period += h->stat.period;
पूर्ण

व्योम hists__inc_stats(काष्ठा hists *hists, काष्ठा hist_entry *h)
अणु
	अगर (!h->filtered)
		hists__inc_filter_stats(hists, h);

	hists->nr_entries++;
	hists->stats.total_period += h->stat.period;
पूर्ण

अटल व्योम hierarchy_recalc_total_periods(काष्ठा hists *hists)
अणु
	काष्ठा rb_node *node;
	काष्ठा hist_entry *he;

	node = rb_first_cached(&hists->entries);

	hists->stats.total_period = 0;
	hists->stats.total_non_filtered_period = 0;

	/*
	 * recalculate total period using top-level entries only
	 * since lower level entries only see non-filtered entries
	 * but upper level entries have sum of both entries.
	 */
	जबतक (node) अणु
		he = rb_entry(node, काष्ठा hist_entry, rb_node);
		node = rb_next(node);

		hists->stats.total_period += he->stat.period;
		अगर (!he->filtered)
			hists->stats.total_non_filtered_period += he->stat.period;
	पूर्ण
पूर्ण

अटल व्योम hierarchy_insert_output_entry(काष्ठा rb_root_cached *root,
					  काष्ठा hist_entry *he)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *iter;
	काष्ठा perf_hpp_fmt *fmt;
	bool lefपंचांगost = true;

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा hist_entry, rb_node);

		अगर (hist_entry__sort(he, iter) > 0)
			p = &parent->rb_left;
		अन्यथा अणु
			p = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&he->rb_node, parent, p);
	rb_insert_color_cached(&he->rb_node, root, lefपंचांगost);

	/* update column width of dynamic entry */
	perf_hpp_list__क्रम_each_sort_list(he->hpp_list, fmt) अणु
		अगर (perf_hpp__is_dynamic_entry(fmt))
			fmt->sort(fmt, he, शून्य);
	पूर्ण
पूर्ण

अटल व्योम hists__hierarchy_output_resort(काष्ठा hists *hists,
					   काष्ठा ui_progress *prog,
					   काष्ठा rb_root_cached *root_in,
					   काष्ठा rb_root_cached *root_out,
					   u64 min_callchain_hits,
					   bool use_callchain)
अणु
	काष्ठा rb_node *node;
	काष्ठा hist_entry *he;

	*root_out = RB_ROOT_CACHED;
	node = rb_first_cached(root_in);

	जबतक (node) अणु
		he = rb_entry(node, काष्ठा hist_entry, rb_node_in);
		node = rb_next(node);

		hierarchy_insert_output_entry(root_out, he);

		अगर (prog)
			ui_progress__update(prog, 1);

		hists->nr_entries++;
		अगर (!he->filtered) अणु
			hists->nr_non_filtered_entries++;
			hists__calc_col_len(hists, he);
		पूर्ण

		अगर (!he->leaf) अणु
			hists__hierarchy_output_resort(hists, prog,
						       &he->hroot_in,
						       &he->hroot_out,
						       min_callchain_hits,
						       use_callchain);
			जारी;
		पूर्ण

		अगर (!use_callchain)
			जारी;

		अगर (callchain_param.mode == CHAIN_GRAPH_REL) अणु
			u64 total = he->stat.period;

			अगर (symbol_conf.cumulate_callchain)
				total = he->stat_acc->period;

			min_callchain_hits = total * (callchain_param.min_percent / 100);
		पूर्ण

		callchain_param.sort(&he->sorted_chain, he->callchain,
				     min_callchain_hits, &callchain_param);
	पूर्ण
पूर्ण

अटल व्योम __hists__insert_output_entry(काष्ठा rb_root_cached *entries,
					 काष्ठा hist_entry *he,
					 u64 min_callchain_hits,
					 bool use_callchain)
अणु
	काष्ठा rb_node **p = &entries->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *iter;
	काष्ठा perf_hpp_fmt *fmt;
	bool lefपंचांगost = true;

	अगर (use_callchain) अणु
		अगर (callchain_param.mode == CHAIN_GRAPH_REL) अणु
			u64 total = he->stat.period;

			अगर (symbol_conf.cumulate_callchain)
				total = he->stat_acc->period;

			min_callchain_hits = total * (callchain_param.min_percent / 100);
		पूर्ण
		callchain_param.sort(&he->sorted_chain, he->callchain,
				      min_callchain_hits, &callchain_param);
	पूर्ण

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा hist_entry, rb_node);

		अगर (hist_entry__sort(he, iter) > 0)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&he->rb_node, parent, p);
	rb_insert_color_cached(&he->rb_node, entries, lefपंचांगost);

	perf_hpp_list__क्रम_each_sort_list(&perf_hpp_list, fmt) अणु
		अगर (perf_hpp__is_dynamic_entry(fmt) &&
		    perf_hpp__defined_dynamic_entry(fmt, he->hists))
			fmt->sort(fmt, he, शून्य);  /* update column width */
	पूर्ण
पूर्ण

अटल व्योम output_resort(काष्ठा hists *hists, काष्ठा ui_progress *prog,
			  bool use_callchain, hists__resort_cb_t cb,
			  व्योम *cb_arg)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *next;
	काष्ठा hist_entry *n;
	u64 callchain_total;
	u64 min_callchain_hits;

	callchain_total = hists->callchain_period;
	अगर (symbol_conf.filter_relative)
		callchain_total = hists->callchain_non_filtered_period;

	min_callchain_hits = callchain_total * (callchain_param.min_percent / 100);

	hists__reset_stats(hists);
	hists__reset_col_len(hists);

	अगर (symbol_conf.report_hierarchy) अणु
		hists__hierarchy_output_resort(hists, prog,
					       &hists->entries_collapsed,
					       &hists->entries,
					       min_callchain_hits,
					       use_callchain);
		hierarchy_recalc_total_periods(hists);
		वापस;
	पूर्ण

	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	next = rb_first_cached(root);
	hists->entries = RB_ROOT_CACHED;

	जबतक (next) अणु
		n = rb_entry(next, काष्ठा hist_entry, rb_node_in);
		next = rb_next(&n->rb_node_in);

		अगर (cb && cb(n, cb_arg))
			जारी;

		__hists__insert_output_entry(&hists->entries, n, min_callchain_hits, use_callchain);
		hists__inc_stats(hists, n);

		अगर (!n->filtered)
			hists__calc_col_len(hists, n);

		अगर (prog)
			ui_progress__update(prog, 1);
	पूर्ण
पूर्ण

व्योम evsel__output_resort_cb(काष्ठा evsel *evsel, काष्ठा ui_progress *prog,
			     hists__resort_cb_t cb, व्योम *cb_arg)
अणु
	bool use_callchain;

	अगर (evsel && symbol_conf.use_callchain && !symbol_conf.show_ref_callgraph)
		use_callchain = evsel__has_callchain(evsel);
	अन्यथा
		use_callchain = symbol_conf.use_callchain;

	use_callchain |= symbol_conf.show_branchflag_count;

	output_resort(evsel__hists(evsel), prog, use_callchain, cb, cb_arg);
पूर्ण

व्योम evsel__output_resort(काष्ठा evsel *evsel, काष्ठा ui_progress *prog)
अणु
	वापस evsel__output_resort_cb(evsel, prog, शून्य, शून्य);
पूर्ण

व्योम hists__output_resort(काष्ठा hists *hists, काष्ठा ui_progress *prog)
अणु
	output_resort(hists, prog, symbol_conf.use_callchain, शून्य, शून्य);
पूर्ण

व्योम hists__output_resort_cb(काष्ठा hists *hists, काष्ठा ui_progress *prog,
			     hists__resort_cb_t cb)
अणु
	output_resort(hists, prog, symbol_conf.use_callchain, cb, शून्य);
पूर्ण

अटल bool can_जाओ_child(काष्ठा hist_entry *he, क्रमागत hierarchy_move_dir hmd)
अणु
	अगर (he->leaf || hmd == HMD_FORCE_SIBLING)
		वापस false;

	अगर (he->unfolded || hmd == HMD_FORCE_CHILD)
		वापस true;

	वापस false;
पूर्ण

काष्ठा rb_node *rb_hierarchy_last(काष्ठा rb_node *node)
अणु
	काष्ठा hist_entry *he = rb_entry(node, काष्ठा hist_entry, rb_node);

	जबतक (can_जाओ_child(he, HMD_NORMAL)) अणु
		node = rb_last(&he->hroot_out.rb_root);
		he = rb_entry(node, काष्ठा hist_entry, rb_node);
	पूर्ण
	वापस node;
पूर्ण

काष्ठा rb_node *__rb_hierarchy_next(काष्ठा rb_node *node, क्रमागत hierarchy_move_dir hmd)
अणु
	काष्ठा hist_entry *he = rb_entry(node, काष्ठा hist_entry, rb_node);

	अगर (can_जाओ_child(he, hmd))
		node = rb_first_cached(&he->hroot_out);
	अन्यथा
		node = rb_next(node);

	जबतक (node == शून्य) अणु
		he = he->parent_he;
		अगर (he == शून्य)
			अवरोध;

		node = rb_next(&he->rb_node);
	पूर्ण
	वापस node;
पूर्ण

काष्ठा rb_node *rb_hierarchy_prev(काष्ठा rb_node *node)
अणु
	काष्ठा hist_entry *he = rb_entry(node, काष्ठा hist_entry, rb_node);

	node = rb_prev(node);
	अगर (node)
		वापस rb_hierarchy_last(node);

	he = he->parent_he;
	अगर (he == शून्य)
		वापस शून्य;

	वापस &he->rb_node;
पूर्ण

bool hist_entry__has_hierarchy_children(काष्ठा hist_entry *he, भग्न limit)
अणु
	काष्ठा rb_node *node;
	काष्ठा hist_entry *child;
	भग्न percent;

	अगर (he->leaf)
		वापस false;

	node = rb_first_cached(&he->hroot_out);
	child = rb_entry(node, काष्ठा hist_entry, rb_node);

	जबतक (node && child->filtered) अणु
		node = rb_next(node);
		child = rb_entry(node, काष्ठा hist_entry, rb_node);
	पूर्ण

	अगर (node)
		percent = hist_entry__get_percent_limit(child);
	अन्यथा
		percent = 0;

	वापस node && percent >= limit;
पूर्ण

अटल व्योम hists__हटाओ_entry_filter(काष्ठा hists *hists, काष्ठा hist_entry *h,
				       क्रमागत hist_filter filter)
अणु
	h->filtered &= ~(1 << filter);

	अगर (symbol_conf.report_hierarchy) अणु
		काष्ठा hist_entry *parent = h->parent_he;

		जबतक (parent) अणु
			he_stat__add_stat(&parent->stat, &h->stat);

			parent->filtered &= ~(1 << filter);

			अगर (parent->filtered)
				जाओ next;

			/* क्रमce fold unfiltered entry क्रम simplicity */
			parent->unfolded = false;
			parent->has_no_entry = false;
			parent->row_offset = 0;
			parent->nr_rows = 0;
next:
			parent = parent->parent_he;
		पूर्ण
	पूर्ण

	अगर (h->filtered)
		वापस;

	/* क्रमce fold unfiltered entry क्रम simplicity */
	h->unfolded = false;
	h->has_no_entry = false;
	h->row_offset = 0;
	h->nr_rows = 0;

	hists->stats.nr_non_filtered_samples += h->stat.nr_events;

	hists__inc_filter_stats(hists, h);
	hists__calc_col_len(hists, h);
पूर्ण


अटल bool hists__filter_entry_by_dso(काष्ठा hists *hists,
				       काष्ठा hist_entry *he)
अणु
	अगर (hists->dso_filter != शून्य &&
	    (he->ms.map == शून्य || he->ms.map->dso != hists->dso_filter)) अणु
		he->filtered |= (1 << HIST_FILTER__DSO);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hists__filter_entry_by_thपढ़ो(काष्ठा hists *hists,
					  काष्ठा hist_entry *he)
अणु
	अगर (hists->thपढ़ो_filter != शून्य &&
	    he->thपढ़ो != hists->thपढ़ो_filter) अणु
		he->filtered |= (1 << HIST_FILTER__THREAD);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hists__filter_entry_by_symbol(काष्ठा hists *hists,
					  काष्ठा hist_entry *he)
अणु
	अगर (hists->symbol_filter_str != शून्य &&
	    (!he->ms.sym || म_माला(he->ms.sym->name,
				   hists->symbol_filter_str) == शून्य)) अणु
		he->filtered |= (1 << HIST_FILTER__SYMBOL);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hists__filter_entry_by_socket(काष्ठा hists *hists,
					  काष्ठा hist_entry *he)
अणु
	अगर ((hists->socket_filter > -1) &&
	    (he->socket != hists->socket_filter)) अणु
		he->filtered |= (1 << HIST_FILTER__SOCKET);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

प्रकार bool (*filter_fn_t)(काष्ठा hists *hists, काष्ठा hist_entry *he);

अटल व्योम hists__filter_by_type(काष्ठा hists *hists, पूर्णांक type, filter_fn_t filter)
अणु
	काष्ठा rb_node *nd;

	hists->stats.nr_non_filtered_samples = 0;

	hists__reset_filter_stats(hists);
	hists__reset_col_len(hists);

	क्रम (nd = rb_first_cached(&hists->entries); nd; nd = rb_next(nd)) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);

		अगर (filter(hists, h))
			जारी;

		hists__हटाओ_entry_filter(hists, h, type);
	पूर्ण
पूर्ण

अटल व्योम resort_filtered_entry(काष्ठा rb_root_cached *root,
				  काष्ठा hist_entry *he)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *iter;
	काष्ठा rb_root_cached new_root = RB_ROOT_CACHED;
	काष्ठा rb_node *nd;
	bool lefपंचांगost = true;

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा hist_entry, rb_node);

		अगर (hist_entry__sort(he, iter) > 0)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&he->rb_node, parent, p);
	rb_insert_color_cached(&he->rb_node, root, lefपंचांगost);

	अगर (he->leaf || he->filtered)
		वापस;

	nd = rb_first_cached(&he->hroot_out);
	जबतक (nd) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);

		nd = rb_next(nd);
		rb_erase_cached(&h->rb_node, &he->hroot_out);

		resort_filtered_entry(&new_root, h);
	पूर्ण

	he->hroot_out = new_root;
पूर्ण

अटल व्योम hists__filter_hierarchy(काष्ठा hists *hists, पूर्णांक type, स्थिर व्योम *arg)
अणु
	काष्ठा rb_node *nd;
	काष्ठा rb_root_cached new_root = RB_ROOT_CACHED;

	hists->stats.nr_non_filtered_samples = 0;

	hists__reset_filter_stats(hists);
	hists__reset_col_len(hists);

	nd = rb_first_cached(&hists->entries);
	जबतक (nd) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);
		पूर्णांक ret;

		ret = hist_entry__filter(h, type, arg);

		/*
		 * हाल 1. non-matching type
		 * zero out the period, set filter marker and move to child
		 */
		अगर (ret < 0) अणु
			स_रखो(&h->stat, 0, माप(h->stat));
			h->filtered |= (1 << type);

			nd = __rb_hierarchy_next(&h->rb_node, HMD_FORCE_CHILD);
		पूर्ण
		/*
		 * हाल 2. matched type (filter out)
		 * set filter marker and move to next
		 */
		अन्यथा अगर (ret == 1) अणु
			h->filtered |= (1 << type);

			nd = __rb_hierarchy_next(&h->rb_node, HMD_FORCE_SIBLING);
		पूर्ण
		/*
		 * हाल 3. ok (not filtered)
		 * add period to hists and parents, erase the filter marker
		 * and move to next sibling
		 */
		अन्यथा अणु
			hists__हटाओ_entry_filter(hists, h, type);

			nd = __rb_hierarchy_next(&h->rb_node, HMD_FORCE_SIBLING);
		पूर्ण
	पूर्ण

	hierarchy_recalc_total_periods(hists);

	/*
	 * resort output after applying a new filter since filter in a lower
	 * hierarchy can change periods in a upper hierarchy.
	 */
	nd = rb_first_cached(&hists->entries);
	जबतक (nd) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);

		nd = rb_next(nd);
		rb_erase_cached(&h->rb_node, &hists->entries);

		resort_filtered_entry(&new_root, h);
	पूर्ण

	hists->entries = new_root;
पूर्ण

व्योम hists__filter_by_thपढ़ो(काष्ठा hists *hists)
अणु
	अगर (symbol_conf.report_hierarchy)
		hists__filter_hierarchy(hists, HIST_FILTER__THREAD,
					hists->thपढ़ो_filter);
	अन्यथा
		hists__filter_by_type(hists, HIST_FILTER__THREAD,
				      hists__filter_entry_by_thपढ़ो);
पूर्ण

व्योम hists__filter_by_dso(काष्ठा hists *hists)
अणु
	अगर (symbol_conf.report_hierarchy)
		hists__filter_hierarchy(hists, HIST_FILTER__DSO,
					hists->dso_filter);
	अन्यथा
		hists__filter_by_type(hists, HIST_FILTER__DSO,
				      hists__filter_entry_by_dso);
पूर्ण

व्योम hists__filter_by_symbol(काष्ठा hists *hists)
अणु
	अगर (symbol_conf.report_hierarchy)
		hists__filter_hierarchy(hists, HIST_FILTER__SYMBOL,
					hists->symbol_filter_str);
	अन्यथा
		hists__filter_by_type(hists, HIST_FILTER__SYMBOL,
				      hists__filter_entry_by_symbol);
पूर्ण

व्योम hists__filter_by_socket(काष्ठा hists *hists)
अणु
	अगर (symbol_conf.report_hierarchy)
		hists__filter_hierarchy(hists, HIST_FILTER__SOCKET,
					&hists->socket_filter);
	अन्यथा
		hists__filter_by_type(hists, HIST_FILTER__SOCKET,
				      hists__filter_entry_by_socket);
पूर्ण

व्योम events_stats__inc(काष्ठा events_stats *stats, u32 type)
अणु
	++stats->nr_events[0];
	++stats->nr_events[type];
पूर्ण

अटल व्योम hists_stats__inc(काष्ठा hists_stats *stats)
अणु
	++stats->nr_samples;
पूर्ण

व्योम hists__inc_nr_events(काष्ठा hists *hists)
अणु
	hists_stats__inc(&hists->stats);
पूर्ण

व्योम hists__inc_nr_samples(काष्ठा hists *hists, bool filtered)
अणु
	hists_stats__inc(&hists->stats);
	अगर (!filtered)
		hists->stats.nr_non_filtered_samples++;
पूर्ण

अटल काष्ठा hist_entry *hists__add_dummy_entry(काष्ठा hists *hists,
						 काष्ठा hist_entry *pair)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *he;
	पूर्णांक64_t cmp;
	bool lefपंचांगost = true;

	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	p = &root->rb_root.rb_node;

	जबतक (*p != शून्य) अणु
		parent = *p;
		he = rb_entry(parent, काष्ठा hist_entry, rb_node_in);

		cmp = hist_entry__collapse(he, pair);

		अगर (!cmp)
			जाओ out;

		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	he = hist_entry__new(pair, true);
	अगर (he) अणु
		स_रखो(&he->stat, 0, माप(he->stat));
		he->hists = hists;
		अगर (symbol_conf.cumulate_callchain)
			स_रखो(he->stat_acc, 0, माप(he->stat));
		rb_link_node(&he->rb_node_in, parent, p);
		rb_insert_color_cached(&he->rb_node_in, root, lefपंचांगost);
		hists__inc_stats(hists, he);
		he->dummy = true;
	पूर्ण
out:
	वापस he;
पूर्ण

अटल काष्ठा hist_entry *add_dummy_hierarchy_entry(काष्ठा hists *hists,
						    काष्ठा rb_root_cached *root,
						    काष्ठा hist_entry *pair)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hist_entry *he;
	काष्ठा perf_hpp_fmt *fmt;
	bool lefपंचांगost = true;

	p = &root->rb_root.rb_node;
	जबतक (*p != शून्य) अणु
		पूर्णांक64_t cmp = 0;

		parent = *p;
		he = rb_entry(parent, काष्ठा hist_entry, rb_node_in);

		perf_hpp_list__क्रम_each_sort_list(he->hpp_list, fmt) अणु
			cmp = fmt->collapse(fmt, he, pair);
			अगर (cmp)
				अवरोध;
		पूर्ण
		अगर (!cmp)
			जाओ out;

		अगर (cmp < 0)
			p = &parent->rb_left;
		अन्यथा अणु
			p = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	he = hist_entry__new(pair, true);
	अगर (he) अणु
		rb_link_node(&he->rb_node_in, parent, p);
		rb_insert_color_cached(&he->rb_node_in, root, lefपंचांगost);

		he->dummy = true;
		he->hists = hists;
		स_रखो(&he->stat, 0, माप(he->stat));
		hists__inc_stats(hists, he);
	पूर्ण
out:
	वापस he;
पूर्ण

अटल काष्ठा hist_entry *hists__find_entry(काष्ठा hists *hists,
					    काष्ठा hist_entry *he)
अणु
	काष्ठा rb_node *n;

	अगर (hists__has(hists, need_collapse))
		n = hists->entries_collapsed.rb_root.rb_node;
	अन्यथा
		n = hists->entries_in->rb_root.rb_node;

	जबतक (n) अणु
		काष्ठा hist_entry *iter = rb_entry(n, काष्ठा hist_entry, rb_node_in);
		पूर्णांक64_t cmp = hist_entry__collapse(iter, he);

		अगर (cmp < 0)
			n = n->rb_left;
		अन्यथा अगर (cmp > 0)
			n = n->rb_right;
		अन्यथा
			वापस iter;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hist_entry *hists__find_hierarchy_entry(काष्ठा rb_root_cached *root,
						      काष्ठा hist_entry *he)
अणु
	काष्ठा rb_node *n = root->rb_root.rb_node;

	जबतक (n) अणु
		काष्ठा hist_entry *iter;
		काष्ठा perf_hpp_fmt *fmt;
		पूर्णांक64_t cmp = 0;

		iter = rb_entry(n, काष्ठा hist_entry, rb_node_in);
		perf_hpp_list__क्रम_each_sort_list(he->hpp_list, fmt) अणु
			cmp = fmt->collapse(fmt, iter, he);
			अगर (cmp)
				अवरोध;
		पूर्ण

		अगर (cmp < 0)
			n = n->rb_left;
		अन्यथा अगर (cmp > 0)
			n = n->rb_right;
		अन्यथा
			वापस iter;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hists__match_hierarchy(काष्ठा rb_root_cached *leader_root,
				   काष्ठा rb_root_cached *other_root)
अणु
	काष्ठा rb_node *nd;
	काष्ठा hist_entry *pos, *pair;

	क्रम (nd = rb_first_cached(leader_root); nd; nd = rb_next(nd)) अणु
		pos  = rb_entry(nd, काष्ठा hist_entry, rb_node_in);
		pair = hists__find_hierarchy_entry(other_root, pos);

		अगर (pair) अणु
			hist_entry__add_pair(pair, pos);
			hists__match_hierarchy(&pos->hroot_in, &pair->hroot_in);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Look क्रम pairs to link to the leader buckets (hist_entries):
 */
व्योम hists__match(काष्ठा hists *leader, काष्ठा hists *other)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *nd;
	काष्ठा hist_entry *pos, *pair;

	अगर (symbol_conf.report_hierarchy) अणु
		/* hierarchy report always collapses entries */
		वापस hists__match_hierarchy(&leader->entries_collapsed,
					      &other->entries_collapsed);
	पूर्ण

	अगर (hists__has(leader, need_collapse))
		root = &leader->entries_collapsed;
	अन्यथा
		root = leader->entries_in;

	क्रम (nd = rb_first_cached(root); nd; nd = rb_next(nd)) अणु
		pos  = rb_entry(nd, काष्ठा hist_entry, rb_node_in);
		pair = hists__find_entry(other, pos);

		अगर (pair)
			hist_entry__add_pair(pair, pos);
	पूर्ण
पूर्ण

अटल पूर्णांक hists__link_hierarchy(काष्ठा hists *leader_hists,
				 काष्ठा hist_entry *parent,
				 काष्ठा rb_root_cached *leader_root,
				 काष्ठा rb_root_cached *other_root)
अणु
	काष्ठा rb_node *nd;
	काष्ठा hist_entry *pos, *leader;

	क्रम (nd = rb_first_cached(other_root); nd; nd = rb_next(nd)) अणु
		pos = rb_entry(nd, काष्ठा hist_entry, rb_node_in);

		अगर (hist_entry__has_pairs(pos)) अणु
			bool found = false;

			list_क्रम_each_entry(leader, &pos->pairs.head, pairs.node) अणु
				अगर (leader->hists == leader_hists) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!found)
				वापस -1;
		पूर्ण अन्यथा अणु
			leader = add_dummy_hierarchy_entry(leader_hists,
							   leader_root, pos);
			अगर (leader == शून्य)
				वापस -1;

			/* करो not poपूर्णांक parent in the pos */
			leader->parent_he = parent;

			hist_entry__add_pair(pos, leader);
		पूर्ण

		अगर (!pos->leaf) अणु
			अगर (hists__link_hierarchy(leader_hists, leader,
						  &leader->hroot_in,
						  &pos->hroot_in) < 0)
				वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Look क्रम entries in the other hists that are not present in the leader, अगर
 * we find them, just add a dummy entry on the leader hists, with period=0,
 * nr_events=0, to serve as the list header.
 */
पूर्णांक hists__link(काष्ठा hists *leader, काष्ठा hists *other)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *nd;
	काष्ठा hist_entry *pos, *pair;

	अगर (symbol_conf.report_hierarchy) अणु
		/* hierarchy report always collapses entries */
		वापस hists__link_hierarchy(leader, शून्य,
					     &leader->entries_collapsed,
					     &other->entries_collapsed);
	पूर्ण

	अगर (hists__has(other, need_collapse))
		root = &other->entries_collapsed;
	अन्यथा
		root = other->entries_in;

	क्रम (nd = rb_first_cached(root); nd; nd = rb_next(nd)) अणु
		pos = rb_entry(nd, काष्ठा hist_entry, rb_node_in);

		अगर (!hist_entry__has_pairs(pos)) अणु
			pair = hists__add_dummy_entry(leader, pos);
			अगर (pair == शून्य)
				वापस -1;
			hist_entry__add_pair(pos, pair);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hists__unlink(काष्ठा hists *hists)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *nd;
	काष्ठा hist_entry *pos;

	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	क्रम (nd = rb_first_cached(root); nd; nd = rb_next(nd)) अणु
		pos = rb_entry(nd, काष्ठा hist_entry, rb_node_in);
		list_del_init(&pos->pairs.node);
	पूर्ण

	वापस 0;
पूर्ण

व्योम hist__account_cycles(काष्ठा branch_stack *bs, काष्ठा addr_location *al,
			  काष्ठा perf_sample *sample, bool nonany_branch_mode,
			  u64 *total_cycles)
अणु
	काष्ठा branch_info *bi;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);

	/* If we have branch cycles always annotate them. */
	अगर (bs && bs->nr && entries[0].flags.cycles) अणु
		पूर्णांक i;

		bi = sample__resolve_bstack(sample, al);
		अगर (bi) अणु
			काष्ठा addr_map_symbol *prev = शून्य;

			/*
			 * Ignore errors, still want to process the
			 * other entries.
			 *
			 * For non standard branch modes always
			 * क्रमce no IPC (prev == शून्य)
			 *
			 * Note that perf stores branches reversed from
			 * program order!
			 */
			क्रम (i = bs->nr - 1; i >= 0; i--) अणु
				addr_map_symbol__account_cycles(&bi[i].from,
					nonany_branch_mode ? शून्य : prev,
					bi[i].flags.cycles);
				prev = &bi[i].to;

				अगर (total_cycles)
					*total_cycles += bi[i].flags.cycles;
			पूर्ण
			मुक्त(bi);
		पूर्ण
	पूर्ण
पूर्ण

माप_प्रकार evlist__ख_लिखो_nr_events(काष्ठा evlist *evlist, खाता *fp,
				 bool skip_empty)
अणु
	काष्ठा evsel *pos;
	माप_प्रकार ret = 0;

	evlist__क्रम_each_entry(evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);

		अगर (skip_empty && !hists->stats.nr_samples)
			जारी;

		ret += ख_लिखो(fp, "%s stats:\n", evsel__name(pos));
		ret += ख_लिखो(fp, "%16s events: %10d\n",
			       "SAMPLE", hists->stats.nr_samples);
	पूर्ण

	वापस ret;
पूर्ण


u64 hists__total_period(काष्ठा hists *hists)
अणु
	वापस symbol_conf.filter_relative ? hists->stats.total_non_filtered_period :
		hists->stats.total_period;
पूर्ण

पूर्णांक __hists__scnम_लिखो_title(काष्ठा hists *hists, अक्षर *bf, माप_प्रकार size, bool show_freq)
अणु
	अक्षर unit;
	पूर्णांक prपूर्णांकed;
	स्थिर काष्ठा dso *dso = hists->dso_filter;
	काष्ठा thपढ़ो *thपढ़ो = hists->thपढ़ो_filter;
	पूर्णांक socket_id = hists->socket_filter;
	अचिन्हित दीर्घ nr_samples = hists->stats.nr_samples;
	u64 nr_events = hists->stats.total_period;
	काष्ठा evsel *evsel = hists_to_evsel(hists);
	स्थिर अक्षर *ev_name = evsel__name(evsel);
	अक्षर buf[512], sample_freq_str[64] = "";
	माप_प्रकार buflen = माप(buf);
	अक्षर ref[30] = " show reference callgraph, ";
	bool enable_ref = false;

	अगर (symbol_conf.filter_relative) अणु
		nr_samples = hists->stats.nr_non_filtered_samples;
		nr_events = hists->stats.total_non_filtered_period;
	पूर्ण

	अगर (evsel__is_group_event(evsel)) अणु
		काष्ठा evsel *pos;

		evsel__group_desc(evsel, buf, buflen);
		ev_name = buf;

		क्रम_each_group_member(pos, evsel) अणु
			काष्ठा hists *pos_hists = evsel__hists(pos);

			अगर (symbol_conf.filter_relative) अणु
				nr_samples += pos_hists->stats.nr_non_filtered_samples;
				nr_events += pos_hists->stats.total_non_filtered_period;
			पूर्ण अन्यथा अणु
				nr_samples += pos_hists->stats.nr_samples;
				nr_events += pos_hists->stats.total_period;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (symbol_conf.show_ref_callgraph &&
	    म_माला(ev_name, "call-graph=no"))
		enable_ref = true;

	अगर (show_freq)
		scnम_लिखो(sample_freq_str, माप(sample_freq_str), " %d Hz,", evsel->core.attr.sample_freq);

	nr_samples = convert_unit(nr_samples, &unit);
	prपूर्णांकed = scnम_लिखो(bf, size,
			   "Samples: %lu%c of event%s '%s',%s%sEvent count (approx.): %" PRIu64,
			   nr_samples, unit, evsel->core.nr_members > 1 ? "s" : "",
			   ev_name, sample_freq_str, enable_ref ? ref : " ", nr_events);


	अगर (hists->uid_filter_str)
		prपूर्णांकed += snम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				    ", UID: %s", hists->uid_filter_str);
	अगर (thपढ़ो) अणु
		अगर (hists__has(hists, thपढ़ो)) अणु
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				    ", Thread: %s(%d)",
				     (thपढ़ो->comm_set ? thपढ़ो__comm_str(thपढ़ो) : ""),
				    thपढ़ो->tid);
		पूर्ण अन्यथा अणु
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				    ", Thread: %s",
				     (thपढ़ो->comm_set ? thपढ़ो__comm_str(thपढ़ो) : ""));
		पूर्ण
	पूर्ण
	अगर (dso)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				    ", DSO: %s", dso->लघु_name);
	अगर (socket_id > -1)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				    ", Processor Socket: %d", socket_id);

	वापस prपूर्णांकed;
पूर्ण

पूर्णांक parse_filter_percentage(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *arg, पूर्णांक unset __maybe_unused)
अणु
	अगर (!म_भेद(arg, "relative"))
		symbol_conf.filter_relative = true;
	अन्यथा अगर (!म_भेद(arg, "absolute"))
		symbol_conf.filter_relative = false;
	अन्यथा अणु
		pr_debug("Invalid percentage: %s\n", arg);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_hist_config(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	अगर (!म_भेद(var, "hist.percentage"))
		वापस parse_filter_percentage(शून्य, value, 0);

	वापस 0;
पूर्ण

पूर्णांक __hists__init(काष्ठा hists *hists, काष्ठा perf_hpp_list *hpp_list)
अणु
	स_रखो(hists, 0, माप(*hists));
	hists->entries_in_array[0] = hists->entries_in_array[1] = RB_ROOT_CACHED;
	hists->entries_in = &hists->entries_in_array[0];
	hists->entries_collapsed = RB_ROOT_CACHED;
	hists->entries = RB_ROOT_CACHED;
	pthपढ़ो_mutex_init(&hists->lock, शून्य);
	hists->socket_filter = -1;
	hists->hpp_list = hpp_list;
	INIT_LIST_HEAD(&hists->hpp_क्रमmats);
	वापस 0;
पूर्ण

अटल व्योम hists__delete_reमुख्यing_entries(काष्ठा rb_root_cached *root)
अणु
	काष्ठा rb_node *node;
	काष्ठा hist_entry *he;

	जबतक (!RB_EMPTY_ROOT(&root->rb_root)) अणु
		node = rb_first_cached(root);
		rb_erase_cached(node, root);

		he = rb_entry(node, काष्ठा hist_entry, rb_node_in);
		hist_entry__delete(he);
	पूर्ण
पूर्ण

अटल व्योम hists__delete_all_entries(काष्ठा hists *hists)
अणु
	hists__delete_entries(hists);
	hists__delete_reमुख्यing_entries(&hists->entries_in_array[0]);
	hists__delete_reमुख्यing_entries(&hists->entries_in_array[1]);
	hists__delete_reमुख्यing_entries(&hists->entries_collapsed);
पूर्ण

अटल व्योम hists_evsel__निकास(काष्ठा evsel *evsel)
अणु
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा perf_hpp_fmt *fmt, *pos;
	काष्ठा perf_hpp_list_node *node, *पंचांगp;

	hists__delete_all_entries(hists);

	list_क्रम_each_entry_safe(node, पंचांगp, &hists->hpp_क्रमmats, list) अणु
		perf_hpp_list__क्रम_each_क्रमmat_safe(&node->hpp, fmt, pos) अणु
			list_del_init(&fmt->list);
			मुक्त(fmt);
		पूर्ण
		list_del_init(&node->list);
		मुक्त(node);
	पूर्ण
पूर्ण

अटल पूर्णांक hists_evsel__init(काष्ठा evsel *evsel)
अणु
	काष्ठा hists *hists = evsel__hists(evsel);

	__hists__init(hists, &perf_hpp_list);
	वापस 0;
पूर्ण

/*
 * XXX We probably need a hists_evsel__निकास() to मुक्त the hist_entries
 * stored in the rbtree...
 */

पूर्णांक hists__init(व्योम)
अणु
	पूर्णांक err = evsel__object_config(माप(काष्ठा hists_evsel),
				       hists_evsel__init, hists_evsel__निकास);
	अगर (err)
		ख_माला_दो("FATAL ERROR: Couldn't setup hists class\n", मानक_त्रुटि);

	वापस err;
पूर्ण

व्योम perf_hpp_list__init(काष्ठा perf_hpp_list *list)
अणु
	INIT_LIST_HEAD(&list->fields);
	INIT_LIST_HEAD(&list->sorts);
पूर्ण
