<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-report.c
 *
 * Builtin report command: Analyze the perf.data input file,
 * look up and पढ़ो DSOs and symbol inक्रमmation and display
 * a histogram of results, aदीर्घ various sorting keys.
 */
#समावेश "builtin.h"

#समावेश "util/config.h"

#समावेश "util/annotate.h"
#समावेश "util/color.h"
#समावेश "util/dso.h"
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/err.h>
#समावेश <linux/zभाग.स>
#समावेश "util/map.h"
#समावेश "util/symbol.h"
#समावेश "util/map_symbol.h"
#समावेश "util/mem-events.h"
#समावेश "util/branch.h"
#समावेश "util/callchain.h"
#समावेश "util/values.h"

#समावेश "perf.h"
#समावेश "util/debug.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/evswitch.h"
#समावेश "util/header.h"
#समावेश "util/session.h"
#समावेश "util/srcline.h"
#समावेश "util/tool.h"

#समावेश <subcmd/parse-options.h>
#समावेश <subcmd/exec-cmd.h>
#समावेश "util/parse-events.h"

#समावेश "util/thread.h"
#समावेश "util/sort.h"
#समावेश "util/hist.h"
#समावेश "util/data.h"
#समावेश "arch/common.h"
#समावेश "util/time-utils.h"
#समावेश "util/auxtrace.h"
#समावेश "util/units.h"
#समावेश "util/util.h" // perf_tip()
#समावेश "ui/ui.h"
#समावेश "ui/progress.h"
#समावेश "util/block-info.h"

#समावेश <dlfcn.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <regex.h>
#समावेश <linux/प्रकार.स>
#समावेश <संकेत.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/माला.स>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/समय64.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <linux/mman.h>

काष्ठा report अणु
	काष्ठा perf_tool	tool;
	काष्ठा perf_session	*session;
	काष्ठा evचयन		evचयन;
	bool			use_tui, use_gtk, use_stdio;
	bool			show_full_info;
	bool			show_thपढ़ोs;
	bool			inverted_callchain;
	bool			mem_mode;
	bool			stats_mode;
	bool			tasks_mode;
	bool			mmaps_mode;
	bool			header;
	bool			header_only;
	bool			nonany_branch_mode;
	bool			group_set;
	bool			stitch_lbr;
	bool			disable_order;
	bool			skip_empty;
	पूर्णांक			max_stack;
	काष्ठा perf_पढ़ो_values	show_thपढ़ोs_values;
	काष्ठा annotation_options annotation_opts;
	स्थिर अक्षर		*pretty_prपूर्णांकing_style;
	स्थिर अक्षर		*cpu_list;
	स्थिर अक्षर		*symbol_filter_str;
	स्थिर अक्षर		*समय_str;
	काष्ठा perf_समय_पूर्णांकerval *pसमय_range;
	पूर्णांक			range_size;
	पूर्णांक			range_num;
	भग्न			min_percent;
	u64			nr_entries;
	u64			queue_size;
	u64			total_cycles;
	पूर्णांक			socket_filter;
	DECLARE_BITMAP(cpu_biपंचांगap, MAX_NR_CPUS);
	काष्ठा branch_type_stat	brtype_stat;
	bool			symbol_ipc;
	bool			total_cycles_mode;
	काष्ठा block_report	*block_reports;
	पूर्णांक			nr_block_reports;
पूर्ण;

अटल पूर्णांक report__config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	काष्ठा report *rep = cb;

	अगर (!म_भेद(var, "report.group")) अणु
		symbol_conf.event_group = perf_config_bool(var, value);
		वापस 0;
	पूर्ण
	अगर (!म_भेद(var, "report.percent-limit")) अणु
		द्विगुन pcnt = strtof(value, शून्य);

		rep->min_percent = pcnt;
		callchain_param.min_percent = pcnt;
		वापस 0;
	पूर्ण
	अगर (!म_भेद(var, "report.children")) अणु
		symbol_conf.cumulate_callchain = perf_config_bool(var, value);
		वापस 0;
	पूर्ण
	अगर (!म_भेद(var, "report.queue-size"))
		वापस perf_config_u64(&rep->queue_size, var, value);

	अगर (!म_भेद(var, "report.sort_order")) अणु
		शेष_sort_order = strdup(value);
		वापस 0;
	पूर्ण

	अगर (!म_भेद(var, "report.skip-empty")) अणु
		rep->skip_empty = perf_config_bool(var, value);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hist_iter__report_callback(काष्ठा hist_entry_iter *iter,
				      काष्ठा addr_location *al, bool single,
				      व्योम *arg)
अणु
	पूर्णांक err = 0;
	काष्ठा report *rep = arg;
	काष्ठा hist_entry *he = iter->he;
	काष्ठा evsel *evsel = iter->evsel;
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा mem_info *mi;
	काष्ठा branch_info *bi;

	अगर (!ui__has_annotation() && !rep->symbol_ipc)
		वापस 0;

	अगर (sort__mode == SORT_MODE__BRANCH) अणु
		bi = he->branch_info;
		err = addr_map_symbol__inc_samples(&bi->from, sample, evsel);
		अगर (err)
			जाओ out;

		err = addr_map_symbol__inc_samples(&bi->to, sample, evsel);

	पूर्ण अन्यथा अगर (rep->mem_mode) अणु
		mi = he->mem_info;
		err = addr_map_symbol__inc_samples(&mi->daddr, sample, evsel);
		अगर (err)
			जाओ out;

		err = hist_entry__inc_addr_samples(he, sample, evsel, al->addr);

	पूर्ण अन्यथा अगर (symbol_conf.cumulate_callchain) अणु
		अगर (single)
			err = hist_entry__inc_addr_samples(he, sample, evsel, al->addr);
	पूर्ण अन्यथा अणु
		err = hist_entry__inc_addr_samples(he, sample, evsel, al->addr);
	पूर्ण

out:
	वापस err;
पूर्ण

अटल पूर्णांक hist_iter__branch_callback(काष्ठा hist_entry_iter *iter,
				      काष्ठा addr_location *al __maybe_unused,
				      bool single __maybe_unused,
				      व्योम *arg)
अणु
	काष्ठा hist_entry *he = iter->he;
	काष्ठा report *rep = arg;
	काष्ठा branch_info *bi = he->branch_info;
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा evsel *evsel = iter->evsel;
	पूर्णांक err;

	branch_type_count(&rep->brtype_stat, &bi->flags,
			  bi->from.addr, bi->to.addr);

	अगर (!ui__has_annotation() && !rep->symbol_ipc)
		वापस 0;

	err = addr_map_symbol__inc_samples(&bi->from, sample, evsel);
	अगर (err)
		जाओ out;

	err = addr_map_symbol__inc_samples(&bi->to, sample, evsel);

out:
	वापस err;
पूर्ण

अटल व्योम setup_क्रमced_leader(काष्ठा report *report,
				काष्ठा evlist *evlist)
अणु
	अगर (report->group_set)
		evlist__क्रमce_leader(evlist);
पूर्ण

अटल पूर्णांक process_feature_event(काष्ठा perf_session *session,
				 जोड़ perf_event *event)
अणु
	काष्ठा report *rep = container_of(session->tool, काष्ठा report, tool);

	अगर (event->feat.feat_id < HEADER_LAST_FEATURE)
		वापस perf_event__process_feature(session, event);

	अगर (event->feat.feat_id != HEADER_LAST_FEATURE) अणु
		pr_err("failed: wrong feature ID: %" PRI_lu64 "\n",
		       event->feat.feat_id);
		वापस -1;
	पूर्ण अन्यथा अगर (rep->header_only) अणु
		session_करोne = 1;
	पूर्ण

	/*
	 * (feat_id = HEADER_LAST_FEATURE) is the end marker which
	 * means all features are received, now we can क्रमce the
	 * group अगर needed.
	 */
	setup_क्रमced_leader(rep, session->evlist);
	वापस 0;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	काष्ठा report *rep = container_of(tool, काष्ठा report, tool);
	काष्ठा addr_location al;
	काष्ठा hist_entry_iter iter = अणु
		.evsel 			= evsel,
		.sample 		= sample,
		.hide_unresolved 	= symbol_conf.hide_unresolved,
		.add_entry_cb 		= hist_iter__report_callback,
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (perf_समय__ranges_skip_sample(rep->pसमय_range, rep->range_num,
					  sample->समय)) अणु
		वापस 0;
	पूर्ण

	अगर (evचयन__discard(&rep->evचयन, evsel))
		वापस 0;

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		pr_debug("problem processing %d event, skipping it.\n",
			 event->header.type);
		वापस -1;
	पूर्ण

	अगर (rep->stitch_lbr)
		al.thपढ़ो->lbr_stitch_enable = true;

	अगर (symbol_conf.hide_unresolved && al.sym == शून्य)
		जाओ out_put;

	अगर (rep->cpu_list && !test_bit(sample->cpu, rep->cpu_biपंचांगap))
		जाओ out_put;

	अगर (sort__mode == SORT_MODE__BRANCH) अणु
		/*
		 * A non-synthesized event might not have a branch stack अगर
		 * branch stacks have been synthesized (using itrace options).
		 */
		अगर (!sample->branch_stack)
			जाओ out_put;

		iter.add_entry_cb = hist_iter__branch_callback;
		iter.ops = &hist_iter_branch;
	पूर्ण अन्यथा अगर (rep->mem_mode) अणु
		iter.ops = &hist_iter_mem;
	पूर्ण अन्यथा अगर (symbol_conf.cumulate_callchain) अणु
		iter.ops = &hist_iter_cumulative;
	पूर्ण अन्यथा अणु
		iter.ops = &hist_iter_normal;
	पूर्ण

	अगर (al.map != शून्य)
		al.map->dso->hit = 1;

	अगर (ui__has_annotation() || rep->symbol_ipc || rep->total_cycles_mode) अणु
		hist__account_cycles(sample->branch_stack, &al, sample,
				     rep->nonany_branch_mode,
				     &rep->total_cycles);
	पूर्ण

	ret = hist_entry_iter__add(&iter, &al, rep->max_stack, rep);
	अगर (ret < 0)
		pr_debug("problem adding hist entry, skipping event\n");
out_put:
	addr_location__put(&al);
	वापस ret;
पूर्ण

अटल पूर्णांक process_पढ़ो_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा evsel *evsel,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा report *rep = container_of(tool, काष्ठा report, tool);

	अगर (rep->show_thपढ़ोs) अणु
		स्थिर अक्षर *name = evsel__name(evsel);
		पूर्णांक err = perf_पढ़ो_values_add_value(&rep->show_thपढ़ोs_values,
					   event->पढ़ो.pid, event->पढ़ो.tid,
					   evsel->idx,
					   name,
					   event->पढ़ो.value);

		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* For pipe mode, sample_type is not currently set */
अटल पूर्णांक report__setup_sample_type(काष्ठा report *rep)
अणु
	काष्ठा perf_session *session = rep->session;
	u64 sample_type = evlist__combined_sample_type(session->evlist);
	bool is_pipe = perf_data__is_pipe(session->data);

	अगर (session->itrace_synth_opts->callchain ||
	    session->itrace_synth_opts->add_callchain ||
	    (!is_pipe &&
	     perf_header__has_feat(&session->header, HEADER_AUXTRACE) &&
	     !session->itrace_synth_opts->set))
		sample_type |= PERF_SAMPLE_CALLCHAIN;

	अगर (session->itrace_synth_opts->last_branch ||
	    session->itrace_synth_opts->add_last_branch)
		sample_type |= PERF_SAMPLE_BRANCH_STACK;

	अगर (!is_pipe && !(sample_type & PERF_SAMPLE_CALLCHAIN)) अणु
		अगर (perf_hpp_list.parent) अणु
			ui__error("Selected --sort parent, but no "
				    "callchain data. Did you call "
				    "'perf record' without -g?\n");
			वापस -EINVAL;
		पूर्ण
		अगर (symbol_conf.use_callchain &&
			!symbol_conf.show_branchflag_count) अणु
			ui__error("Selected -g or --branch-history.\n"
				  "But no callchain or branch data.\n"
				  "Did you call 'perf record' without -g or -b?\n");
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अगर (!callchain_param.enabled &&
		   callchain_param.mode != CHAIN_NONE &&
		   !symbol_conf.use_callchain) अणु
			symbol_conf.use_callchain = true;
			अगर (callchain_रेजिस्टर_param(&callchain_param) < 0) अणु
				ui__error("Can't register callchain params.\n");
				वापस -EINVAL;
			पूर्ण
	पूर्ण

	अगर (symbol_conf.cumulate_callchain) अणु
		/* Silently ignore अगर callchain is missing */
		अगर (!(sample_type & PERF_SAMPLE_CALLCHAIN)) अणु
			symbol_conf.cumulate_callchain = false;
			perf_hpp__cancel_cumulate();
		पूर्ण
	पूर्ण

	अगर (sort__mode == SORT_MODE__BRANCH) अणु
		अगर (!is_pipe &&
		    !(sample_type & PERF_SAMPLE_BRANCH_STACK)) अणु
			ui__error("Selected -b but no branch data. "
				  "Did you call perf record without -b?\n");
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (sort__mode == SORT_MODE__MEMORY) अणु
		अगर (!is_pipe && !(sample_type & PERF_SAMPLE_DATA_SRC)) अणु
			ui__error("Selected --mem-mode but no mem data. "
				  "Did you call perf record without -d?\n");
			वापस -1;
		पूर्ण
	पूर्ण

	callchain_param_setup(sample_type);

	अगर (rep->stitch_lbr && (callchain_param.record_mode != CALLCHAIN_LBR)) अणु
		ui__warning("Can't find LBR callchain. Switch off --stitch-lbr.\n"
			    "Please apply --call-graph lbr when recording.\n");
		rep->stitch_lbr = false;
	पूर्ण

	/* ??? handle more हालs than just ANY? */
	अगर (!(evlist__combined_branch_type(session->evlist) & PERF_SAMPLE_BRANCH_ANY))
		rep->nonany_branch_mode = true;

#अगर !defined(HAVE_LIBUNWIND_SUPPORT) && !defined(HAVE_DWARF_SUPPORT)
	अगर (dwarf_callchain_users) अणु
		ui__warning("Please install libunwind or libdw "
			    "development packages during the perf build.\n");
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम sig_handler(पूर्णांक sig __maybe_unused)
अणु
	session_करोne = 1;
पूर्ण

अटल माप_प्रकार hists__ख_लिखो_nr_sample_events(काष्ठा hists *hists, काष्ठा report *rep,
					      स्थिर अक्षर *evname, खाता *fp)
अणु
	माप_प्रकार ret;
	अक्षर unit;
	अचिन्हित दीर्घ nr_samples = hists->stats.nr_samples;
	u64 nr_events = hists->stats.total_period;
	काष्ठा evsel *evsel = hists_to_evsel(hists);
	अक्षर buf[512];
	माप_प्रकार size = माप(buf);
	पूर्णांक socked_id = hists->socket_filter;

	अगर (quiet)
		वापस 0;

	अगर (symbol_conf.filter_relative) अणु
		nr_samples = hists->stats.nr_non_filtered_samples;
		nr_events = hists->stats.total_non_filtered_period;
	पूर्ण

	अगर (evsel__is_group_event(evsel)) अणु
		काष्ठा evsel *pos;

		evsel__group_desc(evsel, buf, size);
		evname = buf;

		क्रम_each_group_member(pos, evsel) अणु
			स्थिर काष्ठा hists *pos_hists = evsel__hists(pos);

			अगर (symbol_conf.filter_relative) अणु
				nr_samples += pos_hists->stats.nr_non_filtered_samples;
				nr_events += pos_hists->stats.total_non_filtered_period;
			पूर्ण अन्यथा अणु
				nr_samples += pos_hists->stats.nr_samples;
				nr_events += pos_hists->stats.total_period;
			पूर्ण
		पूर्ण
	पूर्ण

	nr_samples = convert_unit(nr_samples, &unit);
	ret = ख_लिखो(fp, "# Samples: %lu%c", nr_samples, unit);
	अगर (evname != शून्य) अणु
		ret += ख_लिखो(fp, " of event%s '%s'",
			       evsel->core.nr_members > 1 ? "s" : "", evname);
	पूर्ण

	अगर (rep->समय_str)
		ret += ख_लिखो(fp, " (time slices: %s)", rep->समय_str);

	अगर (symbol_conf.show_ref_callgraph && evname && म_माला(evname, "call-graph=no")) अणु
		ret += ख_लिखो(fp, ", show reference callgraph");
	पूर्ण

	अगर (rep->mem_mode) अणु
		ret += ख_लिखो(fp, "\n# Total weight : %" PRIu64, nr_events);
		ret += ख_लिखो(fp, "\n# Sort order   : %s", sort_order ? : शेष_mem_sort_order);
	पूर्ण अन्यथा
		ret += ख_लिखो(fp, "\n# Event count (approx.): %" PRIu64, nr_events);

	अगर (socked_id > -1)
		ret += ख_लिखो(fp, "\n# Processor Socket: %d", socked_id);

	वापस ret + ख_लिखो(fp, "\n#\n");
पूर्ण

अटल पूर्णांक evlist__tui_block_hists_browse(काष्ठा evlist *evlist, काष्ठा report *rep)
अणु
	काष्ठा evsel *pos;
	पूर्णांक i = 0, ret;

	evlist__क्रम_each_entry(evlist, pos) अणु
		ret = report__browse_block_hists(&rep->block_reports[i++].hist,
						 rep->min_percent, pos,
						 &rep->session->header.env,
						 &rep->annotation_opts);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evlist__tty_browse_hists(काष्ठा evlist *evlist, काष्ठा report *rep, स्थिर अक्षर *help)
अणु
	काष्ठा evsel *pos;
	पूर्णांक i = 0;

	अगर (!quiet) अणु
		ख_लिखो(मानक_निकास, "#\n# Total Lost Samples: %" PRIu64 "\n#\n",
			evlist->stats.total_lost_samples);
	पूर्ण

	evlist__क्रम_each_entry(evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);
		स्थिर अक्षर *evname = evsel__name(pos);

		अगर (symbol_conf.event_group && !evsel__is_group_leader(pos))
			जारी;

		अगर (rep->skip_empty && !hists->stats.nr_samples)
			जारी;

		hists__ख_लिखो_nr_sample_events(hists, rep, evname, मानक_निकास);

		अगर (rep->total_cycles_mode) अणु
			report__browse_block_hists(&rep->block_reports[i++].hist,
						   rep->min_percent, pos,
						   शून्य, शून्य);
			जारी;
		पूर्ण

		hists__ख_लिखो(hists, !quiet, 0, 0, rep->min_percent, मानक_निकास,
			       !(symbol_conf.use_callchain ||
			         symbol_conf.show_branchflag_count));
		ख_लिखो(मानक_निकास, "\n\n");
	पूर्ण

	अगर (!quiet)
		ख_लिखो(मानक_निकास, "#\n# (%s)\n#\n", help);

	अगर (rep->show_thपढ़ोs) अणु
		bool style = !म_भेद(rep->pretty_prपूर्णांकing_style, "raw");
		perf_पढ़ो_values_display(मानक_निकास, &rep->show_thपढ़ोs_values,
					 style);
		perf_पढ़ो_values_destroy(&rep->show_thपढ़ोs_values);
	पूर्ण

	अगर (sort__mode == SORT_MODE__BRANCH)
		branch_type_stat_display(मानक_निकास, &rep->brtype_stat);

	वापस 0;
पूर्ण

अटल व्योम report__warn_kptr_restrict(स्थिर काष्ठा report *rep)
अणु
	काष्ठा map *kernel_map = machine__kernel_map(&rep->session->machines.host);
	काष्ठा kmap *kernel_kmap = kernel_map ? map__kmap(kernel_map) : शून्य;

	अगर (evlist__exclude_kernel(rep->session->evlist))
		वापस;

	अगर (kernel_map == शून्य ||
	    (kernel_map->dso->hit &&
	     (kernel_kmap->ref_reloc_sym == शून्य ||
	      kernel_kmap->ref_reloc_sym->addr == 0))) अणु
		स्थिर अक्षर *desc =
		    "As no suitable kallsyms nor vmlinux was found, kernel samples\n"
		    "can't be resolved.";

		अगर (kernel_map && map__has_symbols(kernel_map)) अणु
			desc = "If some relocation was applied (e.g. "
			       "kexec) symbols may be misresolved.";
		पूर्ण

		ui__warning(
"Kernel address maps (/proc/{kallsyms,modules}) were restricted.\n\n"
"Check /proc/sys/kernel/kptr_restrict before running 'perf record'.\n\n%s\n\n"
"Samples in kernel modules can't be resolved as well.\n\n",
		desc);
	पूर्ण
पूर्ण

अटल पूर्णांक report__gtk_browse_hists(काष्ठा report *rep, स्थिर अक्षर *help)
अणु
	पूर्णांक (*hist_browser)(काष्ठा evlist *evlist, स्थिर अक्षर *help,
			    काष्ठा hist_browser_समयr *समयr, भग्न min_pcnt);

	hist_browser = dlsym(perf_gtk_handle, "evlist__gtk_browse_hists");

	अगर (hist_browser == शून्य) अणु
		ui__error("GTK browser not found!\n");
		वापस -1;
	पूर्ण

	वापस hist_browser(rep->session->evlist, help, शून्य, rep->min_percent);
पूर्ण

अटल पूर्णांक report__browse_hists(काष्ठा report *rep)
अणु
	पूर्णांक ret;
	काष्ठा perf_session *session = rep->session;
	काष्ठा evlist *evlist = session->evlist;
	स्थिर अक्षर *help = perf_tip(प्रणाली_path(TIPसूची));

	अगर (help == शून्य) अणु
		/* fallback क्रम people who करोn't install perf ;-) */
		help = perf_tip(DOCसूची);
		अगर (help == शून्य)
			help = "Cannot load tips.txt file, please install perf!";
	पूर्ण

	चयन (use_browser) अणु
	हाल 1:
		अगर (rep->total_cycles_mode) अणु
			ret = evlist__tui_block_hists_browse(evlist, rep);
			अवरोध;
		पूर्ण

		ret = evlist__tui_browse_hists(evlist, help, शून्य, rep->min_percent,
					       &session->header.env, true, &rep->annotation_opts);
		/*
		 * Usually "ret" is the last pressed key, and we only
		 * care अगर the key notअगरies us to चयन data file.
		 */
		अगर (ret != K_SWITCH_INPUT_DATA && ret != K_RELOAD)
			ret = 0;
		अवरोध;
	हाल 2:
		ret = report__gtk_browse_hists(rep, help);
		अवरोध;
	शेष:
		ret = evlist__tty_browse_hists(evlist, rep, help);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक report__collapse_hists(काष्ठा report *rep)
अणु
	काष्ठा ui_progress prog;
	काष्ठा evsel *pos;
	पूर्णांक ret = 0;

	ui_progress__init(&prog, rep->nr_entries, "Merging related events...");

	evlist__क्रम_each_entry(rep->session->evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);

		अगर (pos->idx == 0)
			hists->symbol_filter_str = rep->symbol_filter_str;

		hists->socket_filter = rep->socket_filter;

		ret = hists__collapse_resort(hists, &prog);
		अगर (ret < 0)
			अवरोध;

		/* Non-group events are considered as leader */
		अगर (symbol_conf.event_group && !evsel__is_group_leader(pos)) अणु
			काष्ठा hists *leader_hists = evsel__hists(pos->leader);

			hists__match(leader_hists, hists);
			hists__link(leader_hists, hists);
		पूर्ण
	पूर्ण

	ui_progress__finish();
	वापस ret;
पूर्ण

अटल पूर्णांक hists__resort_cb(काष्ठा hist_entry *he, व्योम *arg)
अणु
	काष्ठा report *rep = arg;
	काष्ठा symbol *sym = he->ms.sym;

	अगर (rep->symbol_ipc && sym && !sym->annotate2) अणु
		काष्ठा evsel *evsel = hists_to_evsel(he->hists);

		symbol__annotate2(&he->ms, evsel,
				  &annotation__शेष_options, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम report__output_resort(काष्ठा report *rep)
अणु
	काष्ठा ui_progress prog;
	काष्ठा evsel *pos;

	ui_progress__init(&prog, rep->nr_entries, "Sorting events for output...");

	evlist__क्रम_each_entry(rep->session->evlist, pos) अणु
		evsel__output_resort_cb(pos, &prog, hists__resort_cb, rep);
	पूर्ण

	ui_progress__finish();
पूर्ण

अटल पूर्णांक count_sample_event(काष्ठा perf_tool *tool __maybe_unused,
			      जोड़ perf_event *event __maybe_unused,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा evsel *evsel,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा hists *hists = evsel__hists(evsel);

	hists__inc_nr_events(hists);
	वापस 0;
पूर्ण

अटल व्योम stats_setup(काष्ठा report *rep)
अणु
	स_रखो(&rep->tool, 0, माप(rep->tool));
	rep->tool.sample = count_sample_event;
	rep->tool.no_warn = true;
पूर्ण

अटल पूर्णांक stats_prपूर्णांक(काष्ठा report *rep)
अणु
	काष्ठा perf_session *session = rep->session;

	perf_session__ख_लिखो_nr_events(session, मानक_निकास, rep->skip_empty);
	evlist__ख_लिखो_nr_events(session->evlist, मानक_निकास, rep->skip_empty);
	वापस 0;
पूर्ण

अटल व्योम tasks_setup(काष्ठा report *rep)
अणु
	स_रखो(&rep->tool, 0, माप(rep->tool));
	rep->tool.ordered_events = true;
	अगर (rep->mmaps_mode) अणु
		rep->tool.mmap = perf_event__process_mmap;
		rep->tool.mmap2 = perf_event__process_mmap2;
	पूर्ण
	rep->tool.comm = perf_event__process_comm;
	rep->tool.निकास = perf_event__process_निकास;
	rep->tool.विभाजन = perf_event__process_विभाजन;
	rep->tool.no_warn = true;
पूर्ण

काष्ठा task अणु
	काष्ठा thपढ़ो		*thपढ़ो;
	काष्ठा list_head	 list;
	काष्ठा list_head	 children;
पूर्ण;

अटल काष्ठा task *tasks_list(काष्ठा task *task, काष्ठा machine *machine)
अणु
	काष्ठा thपढ़ो *parent_thपढ़ो, *thपढ़ो = task->thपढ़ो;
	काष्ठा task   *parent_task;

	/* Alपढ़ोy listed. */
	अगर (!list_empty(&task->list))
		वापस शून्य;

	/* Last one in the chain. */
	अगर (thपढ़ो->ppid == -1)
		वापस task;

	parent_thपढ़ो = machine__find_thपढ़ो(machine, -1, thपढ़ो->ppid);
	अगर (!parent_thपढ़ो)
		वापस ERR_PTR(-ENOENT);

	parent_task = thपढ़ो__priv(parent_thपढ़ो);
	list_add_tail(&task->list, &parent_task->children);
	वापस tasks_list(parent_task, machine);
पूर्ण

अटल माप_प्रकार maps__ख_लिखो_task(काष्ठा maps *maps, पूर्णांक indent, खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed = 0;
	काष्ठा map *map;

	maps__क्रम_each_entry(maps, map) अणु
		prपूर्णांकed += ख_लिखो(fp, "%*s  %" PRIx64 "-%" PRIx64 " %c%c%c%c %08" PRIx64 " %" PRIu64 " %s\n",
				   indent, "", map->start, map->end,
				   map->prot & PROT_READ ? 'r' : '-',
				   map->prot & PROT_WRITE ? 'w' : '-',
				   map->prot & PROT_EXEC ? 'x' : '-',
				   map->flags & MAP_SHARED ? 's' : 'p',
				   map->pgoff,
				   map->dso->id.ino, map->dso->name);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल व्योम task__prपूर्णांक_level(काष्ठा task *task, खाता *fp, पूर्णांक level)
अणु
	काष्ठा thपढ़ो *thपढ़ो = task->thपढ़ो;
	काष्ठा task *child;
	पूर्णांक comm_indent = ख_लिखो(fp, "  %8d %8d %8d |%*s",
				  thपढ़ो->pid_, thपढ़ो->tid, thपढ़ो->ppid,
				  level, "");

	ख_लिखो(fp, "%s\n", thपढ़ो__comm_str(thपढ़ो));

	maps__ख_लिखो_task(thपढ़ो->maps, comm_indent, fp);

	अगर (!list_empty(&task->children)) अणु
		list_क्रम_each_entry(child, &task->children, list)
			task__prपूर्णांक_level(child, fp, level + 1);
	पूर्ण
पूर्ण

अटल पूर्णांक tasks_prपूर्णांक(काष्ठा report *rep, खाता *fp)
अणु
	काष्ठा perf_session *session = rep->session;
	काष्ठा machine      *machine = &session->machines.host;
	काष्ठा task *tasks, *task;
	अचिन्हित पूर्णांक nr = 0, itask = 0, i;
	काष्ठा rb_node *nd;
	LIST_HEAD(list);

	/*
	 * No locking needed जबतक accessing machine->thपढ़ोs,
	 * because --tasks is single thपढ़ोed command.
	 */

	/* Count all the thपढ़ोs. */
	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++)
		nr += machine->thपढ़ोs[i].nr;

	tasks = दो_स्मृति(माप(*tasks) * nr);
	अगर (!tasks)
		वापस -ENOMEM;

	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++) अणु
		काष्ठा thपढ़ोs *thपढ़ोs = &machine->thपढ़ोs[i];

		क्रम (nd = rb_first_cached(&thपढ़ोs->entries); nd;
		     nd = rb_next(nd)) अणु
			task = tasks + itask++;

			task->thपढ़ो = rb_entry(nd, काष्ठा thपढ़ो, rb_node);
			INIT_LIST_HEAD(&task->children);
			INIT_LIST_HEAD(&task->list);
			thपढ़ो__set_priv(task->thपढ़ो, task);
		पूर्ण
	पूर्ण

	/*
	 * Iterate every task करोwn to the unprocessed parent
	 * and link all in task children list. Task with no
	 * parent is added पूर्णांकo 'list'.
	 */
	क्रम (itask = 0; itask < nr; itask++) अणु
		task = tasks + itask;

		अगर (!list_empty(&task->list))
			जारी;

		task = tasks_list(task, machine);
		अगर (IS_ERR(task)) अणु
			pr_err("Error: failed to process tasks\n");
			मुक्त(tasks);
			वापस PTR_ERR(task);
		पूर्ण

		अगर (task)
			list_add_tail(&task->list, &list);
	पूर्ण

	ख_लिखो(fp, "# %8s %8s %8s  %s\n", "pid", "tid", "ppid", "comm");

	list_क्रम_each_entry(task, &list, list)
		task__prपूर्णांक_level(task, fp, 0);

	मुक्त(tasks);
	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_report(काष्ठा report *rep)
अणु
	पूर्णांक ret;
	काष्ठा perf_session *session = rep->session;
	काष्ठा evsel *pos;
	काष्ठा perf_data *data = session->data;

	संकेत(संक_विघ्न, sig_handler);

	अगर (rep->cpu_list) अणु
		ret = perf_session__cpu_biपंचांगap(session, rep->cpu_list,
					       rep->cpu_biपंचांगap);
		अगर (ret) अणु
			ui__error("failed to set cpu bitmap\n");
			वापस ret;
		पूर्ण
		session->itrace_synth_opts->cpu_biपंचांगap = rep->cpu_biपंचांगap;
	पूर्ण

	अगर (rep->show_thपढ़ोs) अणु
		ret = perf_पढ़ो_values_init(&rep->show_thपढ़ोs_values);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = report__setup_sample_type(rep);
	अगर (ret) अणु
		/* report__setup_sample_type() alपढ़ोy showed error message */
		वापस ret;
	पूर्ण

	अगर (rep->stats_mode)
		stats_setup(rep);

	अगर (rep->tasks_mode)
		tasks_setup(rep);

	ret = perf_session__process_events(session);
	अगर (ret) अणु
		ui__error("failed to process sample\n");
		वापस ret;
	पूर्ण

	अगर (rep->stats_mode)
		वापस stats_prपूर्णांक(rep);

	अगर (rep->tasks_mode)
		वापस tasks_prपूर्णांक(rep, मानक_निकास);

	report__warn_kptr_restrict(rep);

	evlist__क्रम_each_entry(session->evlist, pos)
		rep->nr_entries += evsel__hists(pos)->nr_entries;

	अगर (use_browser == 0) अणु
		अगर (verbose > 3)
			perf_session__ख_लिखो(session, मानक_निकास);

		अगर (verbose > 2)
			perf_session__ख_लिखो_dsos(session, मानक_निकास);

		अगर (dump_trace) अणु
			perf_session__ख_लिखो_nr_events(session, मानक_निकास,
							rep->skip_empty);
			evlist__ख_लिखो_nr_events(session->evlist, मानक_निकास,
						  rep->skip_empty);
			वापस 0;
		पूर्ण
	पूर्ण

	ret = report__collapse_hists(rep);
	अगर (ret) अणु
		ui__error("failed to process hist entry\n");
		वापस ret;
	पूर्ण

	अगर (session_करोne())
		वापस 0;

	/*
	 * recalculate number of entries after collapsing since it
	 * might be changed during the collapse phase.
	 */
	rep->nr_entries = 0;
	evlist__क्रम_each_entry(session->evlist, pos)
		rep->nr_entries += evsel__hists(pos)->nr_entries;

	अगर (rep->nr_entries == 0) अणु
		ui__error("The %s data has no samples!\n", data->path);
		वापस 0;
	पूर्ण

	report__output_resort(rep);

	अगर (rep->total_cycles_mode) अणु
		पूर्णांक block_hpps[6] = अणु
			PERF_HPP_REPORT__BLOCK_TOTAL_CYCLES_PCT,
			PERF_HPP_REPORT__BLOCK_LBR_CYCLES,
			PERF_HPP_REPORT__BLOCK_CYCLES_PCT,
			PERF_HPP_REPORT__BLOCK_AVG_CYCLES,
			PERF_HPP_REPORT__BLOCK_RANGE,
			PERF_HPP_REPORT__BLOCK_DSO,
		पूर्ण;

		rep->block_reports = block_info__create_report(session->evlist,
							       rep->total_cycles,
							       block_hpps, 6,
							       &rep->nr_block_reports);
		अगर (!rep->block_reports)
			वापस -1;
	पूर्ण

	वापस report__browse_hists(rep);
पूर्ण

अटल पूर्णांक
report_parse_callchain_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset)
अणु
	काष्ठा callchain_param *callchain = opt->value;

	callchain->enabled = !unset;
	/*
	 * --no-call-graph
	 */
	अगर (unset) अणु
		symbol_conf.use_callchain = false;
		callchain->mode = CHAIN_NONE;
		वापस 0;
	पूर्ण

	वापस parse_callchain_report_opt(arg);
पूर्ण

अटल पूर्णांक
parse_समय_quantum(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg,
		   पूर्णांक unset __maybe_unused)
अणु
	अचिन्हित दीर्घ *समय_q = opt->value;
	अक्षर *end;

	*समय_q = म_से_अदीर्घ(arg, &end, 0);
	अगर (end == arg)
		जाओ parse_err;
	अगर (*समय_q == 0) अणु
		pr_err("time quantum cannot be 0");
		वापस -1;
	पूर्ण
	end = skip_spaces(end);
	अगर (*end == 0)
		वापस 0;
	अगर (!म_भेद(end, "s")) अणु
		*समय_q *= NSEC_PER_SEC;
		वापस 0;
	पूर्ण
	अगर (!म_भेद(end, "ms")) अणु
		*समय_q *= NSEC_PER_MSEC;
		वापस 0;
	पूर्ण
	अगर (!म_भेद(end, "us")) अणु
		*समय_q *= NSEC_PER_USEC;
		वापस 0;
	पूर्ण
	अगर (!म_भेद(end, "ns"))
		वापस 0;
parse_err:
	pr_err("Cannot parse time quantum `%s'\n", arg);
	वापस -1;
पूर्ण

पूर्णांक
report_parse_ignore_callees_opt(स्थिर काष्ठा option *opt __maybe_unused,
				स्थिर अक्षर *arg, पूर्णांक unset __maybe_unused)
अणु
	अगर (arg) अणु
		पूर्णांक err = regcomp(&ignore_callees_regex, arg, REG_EXTENDED);
		अगर (err) अणु
			अक्षर buf[बफ_मान];
			regerror(err, &ignore_callees_regex, buf, माप(buf));
			pr_err("Invalid --ignore-callees regex: %s\n%s", arg, buf);
			वापस -1;
		पूर्ण
		have_ignore_callees = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
parse_branch_mode(स्थिर काष्ठा option *opt,
		  स्थिर अक्षर *str __maybe_unused, पूर्णांक unset)
अणु
	पूर्णांक *branch_mode = opt->value;

	*branch_mode = !unset;
	वापस 0;
पूर्ण

अटल पूर्णांक
parse_percent_limit(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
		    पूर्णांक unset __maybe_unused)
अणु
	काष्ठा report *rep = opt->value;
	द्विगुन pcnt = strtof(str, शून्य);

	rep->min_percent = pcnt;
	callchain_param.min_percent = pcnt;
	वापस 0;
पूर्ण

अटल पूर्णांक process_attr(काष्ठा perf_tool *tool __maybe_unused,
			जोड़ perf_event *event,
			काष्ठा evlist **pevlist)
अणु
	u64 sample_type;
	पूर्णांक err;

	err = perf_event__process_attr(tool, event, pevlist);
	अगर (err)
		वापस err;

	/*
	 * Check अगर we need to enable callchains based
	 * on events sample_type.
	 */
	sample_type = evlist__combined_sample_type(*pevlist);
	callchain_param_setup(sample_type);
	वापस 0;
पूर्ण

पूर्णांक cmd_report(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा perf_session *session;
	काष्ठा itrace_synth_opts itrace_synth_opts = अणु .set = 0, पूर्ण;
	काष्ठा stat st;
	bool has_br_stack = false;
	पूर्णांक branch_mode = -1;
	पूर्णांक last_key = 0;
	bool branch_call_mode = false;
#घोषणा CALLCHAIN_DEFAULT_OPT  "graph,0.5,caller,function,percent"
	अटल स्थिर अक्षर report_callchain_help[] = "Display call graph (stack chain/backtrace):\n\n"
						    CALLCHAIN_REPORT_HELP
						    "\n\t\t\t\tDefault: " CALLCHAIN_DEFAULT_OPT;
	अक्षर callchain_शेष_opt[] = CALLCHAIN_DEFAULT_OPT;
	स्थिर अक्षर * स्थिर report_usage[] = अणु
		"perf report [<options>]",
		शून्य
	पूर्ण;
	काष्ठा report report = अणु
		.tool = अणु
			.sample		 = process_sample_event,
			.mmap		 = perf_event__process_mmap,
			.mmap2		 = perf_event__process_mmap2,
			.comm		 = perf_event__process_comm,
			.namespaces	 = perf_event__process_namespaces,
			.cgroup		 = perf_event__process_cgroup,
			.निकास		 = perf_event__process_निकास,
			.विभाजन		 = perf_event__process_विभाजन,
			.lost		 = perf_event__process_lost,
			.पढ़ो		 = process_पढ़ो_event,
			.attr		 = process_attr,
			.tracing_data	 = perf_event__process_tracing_data,
			.build_id	 = perf_event__process_build_id,
			.id_index	 = perf_event__process_id_index,
			.auxtrace_info	 = perf_event__process_auxtrace_info,
			.auxtrace	 = perf_event__process_auxtrace,
			.event_update	 = perf_event__process_event_update,
			.feature	 = process_feature_event,
			.ordered_events	 = true,
			.ordering_requires_बारtamps = true,
		पूर्ण,
		.max_stack		 = PERF_MAX_STACK_DEPTH,
		.pretty_prपूर्णांकing_style	 = "normal",
		.socket_filter		 = -1,
		.annotation_opts	 = annotation__शेष_options,
		.skip_empty		 = true,
	पूर्ण;
	स्थिर काष्ठा option options[] = अणु
	OPT_STRING('i', "input", &input_name, "file",
		    "input file name"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('q', "quiet", &quiet, "Do not show any message"),
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace,
		    "dump raw trace in ASCII"),
	OPT_BOOLEAN(0, "stats", &report.stats_mode, "Display event stats"),
	OPT_BOOLEAN(0, "tasks", &report.tasks_mode, "Display recorded tasks"),
	OPT_BOOLEAN(0, "mmaps", &report.mmaps_mode, "Display recorded tasks memory maps"),
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_BOOLEAN(0, "ignore-vmlinux", &symbol_conf.ignore_vmlinux,
                    "don't load vmlinux even if found"),
	OPT_STRING(0, "kallsyms", &symbol_conf.kallsyms_name,
		   "file", "kallsyms pathname"),
	OPT_BOOLEAN('f', "force", &symbol_conf.force, "don't complain, करो it"),
	OPT_BOOLEAN('m', "modules", &symbol_conf.use_modules,
		    "load module symbols - WARNING: use only with -k and LIVE kernel"),
	OPT_BOOLEAN('n', "show-nr-samples", &symbol_conf.show_nr_samples,
		    "Show a column with the number of samples"),
	OPT_BOOLEAN('T', "threads", &report.show_thपढ़ोs,
		    "Show per-thread event counters"),
	OPT_STRING(0, "pretty", &report.pretty_prपूर्णांकing_style, "key",
		   "pretty printing style key: normal raw"),
	OPT_BOOLEAN(0, "tui", &report.use_tui, "Use the TUI interface"),
	OPT_BOOLEAN(0, "gtk", &report.use_gtk, "Use the GTK2 interface"),
	OPT_BOOLEAN(0, "stdio", &report.use_stdio,
		    "Use the stdio interface"),
	OPT_BOOLEAN(0, "header", &report.header, "Show data header."),
	OPT_BOOLEAN(0, "header-only", &report.header_only,
		    "Show only data header."),
	OPT_STRING('s', "sort", &sort_order, "key[,key2...]",
		   sort_help("sort by key(s):")),
	OPT_STRING('F', "fields", &field_order, "key[,keys...]",
		   sort_help("output field(s): overhead period sample ")),
	OPT_BOOLEAN(0, "show-cpu-utilization", &symbol_conf.show_cpu_utilization,
		    "Show sample percentage for different cpu modes"),
	OPT_BOOLEAN_FLAG(0, "showcpuutilization", &symbol_conf.show_cpu_utilization,
		    "Show sample percentage for different cpu modes", PARSE_OPT_HIDDEN),
	OPT_STRING('p', "parent", &parent_pattern, "regex",
		   "regex filter to identify parent, see: '--sort parent'"),
	OPT_BOOLEAN('x', "exclude-other", &symbol_conf.exclude_other,
		    "Only display entries with parent-match"),
	OPT_CALLBACK_DEFAULT('g', "call-graph", &callchain_param,
			     "print_type,threshold[,print_limit],order,sort_key[,branch],value",
			     report_callchain_help, &report_parse_callchain_opt,
			     callchain_शेष_opt),
	OPT_BOOLEAN(0, "children", &symbol_conf.cumulate_callchain,
		    "Accumulate callchains of children and show total overhead as well. "
		    "Enabled by default, use --no-children to disable."),
	OPT_INTEGER(0, "max-stack", &report.max_stack,
		    "Set the maximum stack depth when parsing the callchain, "
		    "anything beyond the specified depth will be ignored. "
		    "Default: kernel.perf_event_max_stack or " __stringअगरy(PERF_MAX_STACK_DEPTH)),
	OPT_BOOLEAN('G', "inverted", &report.inverted_callchain,
		    "alias for inverted call graph"),
	OPT_CALLBACK(0, "ignore-callees", शून्य, "regex",
		   "ignore callees of these functions in call graphs",
		   report_parse_ignore_callees_opt),
	OPT_STRING('d', "dsos", &symbol_conf.dso_list_str, "dso[,dso...]",
		   "only consider symbols in these dsos"),
	OPT_STRING('c', "comms", &symbol_conf.comm_list_str, "comm[,comm...]",
		   "only consider symbols in these comms"),
	OPT_STRING(0, "pid", &symbol_conf.pid_list_str, "pid[,pid...]",
		   "only consider symbols in these pids"),
	OPT_STRING(0, "tid", &symbol_conf.tid_list_str, "tid[,tid...]",
		   "only consider symbols in these tids"),
	OPT_STRING('S', "symbols", &symbol_conf.sym_list_str, "symbol[,symbol...]",
		   "only consider these symbols"),
	OPT_STRING(0, "symbol-filter", &report.symbol_filter_str, "filter",
		   "only show symbols that (partially) match with this filter"),
	OPT_STRING('w', "column-widths", &symbol_conf.col_width_list_str,
		   "width[,width...]",
		   "don't try to adjust column width, use these fixed values"),
	OPT_STRING_NOEMPTY('t', "field-separator", &symbol_conf.field_sep, "separator",
		   "separator for columns, no spaces will be added between "
		   "columns '.' is reserved."),
	OPT_BOOLEAN('U', "hide-unresolved", &symbol_conf.hide_unresolved,
		    "Only display entries resolved to a symbol"),
	OPT_CALLBACK(0, "symfs", शून्य, "directory",
		     "Look for files with symbols relative to this directory",
		     symbol__config_symfs),
	OPT_STRING('C', "cpu", &report.cpu_list, "cpu",
		   "list of cpus to profile"),
	OPT_BOOLEAN('I', "show-info", &report.show_full_info,
		    "Display extended information about perf.data file"),
	OPT_BOOLEAN(0, "source", &report.annotation_opts.annotate_src,
		    "Interleave source code with assembly code (default)"),
	OPT_BOOLEAN(0, "asm-raw", &report.annotation_opts.show_यंत्र_raw,
		    "Display raw encoding of assembly instructions (default)"),
	OPT_STRING('M', "disassembler-style", &report.annotation_opts.disassembler_style, "disassembler style",
		   "Specify disassembler style (e.g. -M intel for intel syntax)"),
	OPT_STRING(0, "prefix", &report.annotation_opts.prefix, "prefix",
		    "Add prefix to source file path names in programs (with --prefix-strip)"),
	OPT_STRING(0, "prefix-strip", &report.annotation_opts.prefix_strip, "N",
		    "Strip first N entries of source file path name in programs (with --prefix)"),
	OPT_BOOLEAN(0, "show-total-period", &symbol_conf.show_total_period,
		    "Show a column with the sum of periods"),
	OPT_BOOLEAN_SET(0, "group", &symbol_conf.event_group, &report.group_set,
		    "Show event group information together"),
	OPT_INTEGER(0, "group-sort-idx", &symbol_conf.group_sort_idx,
		    "Sort the output by the event at the index n in group. "
		    "If n is invalid, sort by the first event. "
		    "WARNING: should be used on grouped events."),
	OPT_CALLBACK_NOOPT('b', "branch-stack", &branch_mode, "",
		    "use branch records for per branch histogram filling",
		    parse_branch_mode),
	OPT_BOOLEAN(0, "branch-history", &branch_call_mode,
		    "add last branch records to call history"),
	OPT_STRING(0, "objdump", &report.annotation_opts.objdump_path, "path",
		   "objdump binary to use for disassembly and annotations"),
	OPT_BOOLEAN(0, "demangle", &symbol_conf.demangle,
		    "Disable symbol demangling"),
	OPT_BOOLEAN(0, "demangle-kernel", &symbol_conf.demangle_kernel,
		    "Enable kernel symbol demangling"),
	OPT_BOOLEAN(0, "mem-mode", &report.mem_mode, "mem access profile"),
	OPT_INTEGER(0, "samples", &symbol_conf.res_sample,
		    "Number of samples to save per histogram entry for individual browsing"),
	OPT_CALLBACK(0, "percent-limit", &report, "percent",
		     "Don't show entries under that percent", parse_percent_limit),
	OPT_CALLBACK(0, "percentage", शून्य, "relative|absolute",
		     "how to display percentage of filtered entries", parse_filter_percentage),
	OPT_CALLBACK_OPTARG(0, "itrace", &itrace_synth_opts, शून्य, "opts",
			    "Instruction Tracing options\n" ITRACE_HELP,
			    itrace_parse_synth_opts),
	OPT_BOOLEAN(0, "full-source-path", &srcline_full_filename,
			"Show full source file name path for source lines"),
	OPT_BOOLEAN(0, "show-ref-call-graph", &symbol_conf.show_ref_callgraph,
		    "Show callgraph from reference event"),
	OPT_BOOLEAN(0, "stitch-lbr", &report.stitch_lbr,
		    "Enable LBR callgraph stitching approach"),
	OPT_INTEGER(0, "socket-filter", &report.socket_filter,
		    "only show processor socket that match with this filter"),
	OPT_BOOLEAN(0, "raw-trace", &symbol_conf.raw_trace,
		    "Show raw trace event output (do not use print fmt or plugins)"),
	OPT_BOOLEAN(0, "hierarchy", &symbol_conf.report_hierarchy,
		    "Show entries in a hierarchy"),
	OPT_CALLBACK_DEFAULT(0, "stdio-color", शून्य, "mode",
			     "'always' (default), 'never' or 'auto' only applicable to --stdio mode",
			     stdio__config_color, "always"),
	OPT_STRING(0, "time", &report.समय_str, "str",
		   "Time span of interest (start,stop)"),
	OPT_BOOLEAN(0, "inline", &symbol_conf.अंतरभूत_name,
		    "Show inline function"),
	OPT_CALLBACK(0, "percent-type", &report.annotation_opts, "local-period",
		     "Set percent type local/global-period/hits",
		     annotate_parse_percent_type),
	OPT_BOOLEAN(0, "ns", &symbol_conf.nanosecs, "Show times in nanosecs"),
	OPT_CALLBACK(0, "time-quantum", &symbol_conf.समय_quantum, "time (ms|us|ns|s)",
		     "Set time quantum for time sort key (default 100ms)",
		     parse_समय_quantum),
	OPTS_EVSWITCH(&report.evचयन),
	OPT_BOOLEAN(0, "total-cycles", &report.total_cycles_mode,
		    "Sort all blocks by 'Sampled Cycles%'"),
	OPT_BOOLEAN(0, "disable-order", &report.disable_order,
		    "Disable raw trace ordering"),
	OPT_BOOLEAN(0, "skip-empty", &report.skip_empty,
		    "Do not display empty (or dummy) events in the output"),
	OPT_END()
	पूर्ण;
	काष्ठा perf_data data = अणु
		.mode  = PERF_DATA_MODE_READ,
	पूर्ण;
	पूर्णांक ret = hists__init();
	अक्षर sort_पंचांगp[128];

	अगर (ret < 0)
		वापस ret;

	ret = perf_config(report__config, &report);
	अगर (ret)
		वापस ret;

	argc = parse_options(argc, argv, options, report_usage, 0);
	अगर (argc) अणु
		/*
		 * Special हाल: अगर there's an argument left then assume that
		 * it's a symbol filter:
		 */
		अगर (argc > 1)
			usage_with_options(report_usage, options);

		report.symbol_filter_str = argv[0];
	पूर्ण

	अगर (annotate_check_args(&report.annotation_opts) < 0)
		वापस -EINVAL;

	अगर (report.mmaps_mode)
		report.tasks_mode = true;

	अगर (dump_trace && report.disable_order)
		report.tool.ordered_events = false;

	अगर (quiet)
		perf_quiet_option();

	अगर (symbol_conf.vmlinux_name &&
	    access(symbol_conf.vmlinux_name, R_OK)) अणु
		pr_err("Invalid file: %s\n", symbol_conf.vmlinux_name);
		वापस -EINVAL;
	पूर्ण
	अगर (symbol_conf.kallsyms_name &&
	    access(symbol_conf.kallsyms_name, R_OK)) अणु
		pr_err("Invalid file: %s\n", symbol_conf.kallsyms_name);
		वापस -EINVAL;
	पूर्ण

	अगर (report.inverted_callchain)
		callchain_param.order = ORDER_CALLER;
	अगर (symbol_conf.cumulate_callchain && !callchain_param.order_set)
		callchain_param.order = ORDER_CALLER;

	अगर ((itrace_synth_opts.callchain || itrace_synth_opts.add_callchain) &&
	    (पूर्णांक)itrace_synth_opts.callchain_sz > report.max_stack)
		report.max_stack = itrace_synth_opts.callchain_sz;

	अगर (!input_name || !म_माप(input_name)) अणु
		अगर (!ख_स्थिति(STDIN_खाताNO, &st) && S_ISFIFO(st.st_mode))
			input_name = "-";
		अन्यथा
			input_name = "perf.data";
	पूर्ण

	data.path  = input_name;
	data.क्रमce = symbol_conf.क्रमce;

repeat:
	session = perf_session__new(&data, false, &report.tool);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	ret = evचयन__init(&report.evचयन, session->evlist, मानक_त्रुटि);
	अगर (ret)
		वापस ret;

	अगर (zstd_init(&(session->zstd_data), 0) < 0)
		pr_warning("Decompression initialization failed. Reported data may be incomplete.\n");

	अगर (report.queue_size) अणु
		ordered_events__set_alloc_size(&session->ordered_events,
					       report.queue_size);
	पूर्ण

	session->itrace_synth_opts = &itrace_synth_opts;

	report.session = session;

	has_br_stack = perf_header__has_feat(&session->header,
					     HEADER_BRANCH_STACK);
	अगर (evlist__combined_sample_type(session->evlist) & PERF_SAMPLE_STACK_USER)
		has_br_stack = false;

	setup_क्रमced_leader(&report, session->evlist);

	अगर (symbol_conf.group_sort_idx && !session->evlist->nr_groups) अणु
		parse_options_usage(शून्य, options, "group-sort-idx", 0);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (itrace_synth_opts.last_branch || itrace_synth_opts.add_last_branch)
		has_br_stack = true;

	अगर (has_br_stack && branch_call_mode)
		symbol_conf.show_branchflag_count = true;

	स_रखो(&report.brtype_stat, 0, माप(काष्ठा branch_type_stat));

	/*
	 * Branch mode is a tristate:
	 * -1 means शेष, so decide based on the file having branch data.
	 * 0/1 means the user chose a mode.
	 */
	अगर (((branch_mode == -1 && has_br_stack) || branch_mode == 1) &&
	    !branch_call_mode) अणु
		sort__mode = SORT_MODE__BRANCH;
		symbol_conf.cumulate_callchain = false;
	पूर्ण
	अगर (branch_call_mode) अणु
		callchain_param.key = CCKEY_ADDRESS;
		callchain_param.branch_callstack = true;
		symbol_conf.use_callchain = true;
		callchain_रेजिस्टर_param(&callchain_param);
		अगर (sort_order == शून्य)
			sort_order = "srcline,symbol,dso";
	पूर्ण

	अगर (report.mem_mode) अणु
		अगर (sort__mode == SORT_MODE__BRANCH) अणु
			pr_err("branch and mem mode incompatible\n");
			जाओ error;
		पूर्ण
		sort__mode = SORT_MODE__MEMORY;
		symbol_conf.cumulate_callchain = false;
	पूर्ण

	अगर (symbol_conf.report_hierarchy) अणु
		/* disable incompatible options */
		symbol_conf.cumulate_callchain = false;

		अगर (field_order) अणु
			pr_err("Error: --hierarchy and --fields options cannot be used together\n");
			parse_options_usage(report_usage, options, "F", 1);
			parse_options_usage(शून्य, options, "hierarchy", 0);
			जाओ error;
		पूर्ण

		perf_hpp_list.need_collapse = true;
	पूर्ण

	अगर (report.use_stdio)
		use_browser = 0;
	अन्यथा अगर (report.use_tui)
		use_browser = 1;
	अन्यथा अगर (report.use_gtk)
		use_browser = 2;

	/* Force tty output क्रम header output and per-thपढ़ो stat. */
	अगर (report.header || report.header_only || report.show_thपढ़ोs)
		use_browser = 0;
	अगर (report.header || report.header_only)
		report.tool.show_feat_hdr = SHOW_FEAT_HEADER;
	अगर (report.show_full_info)
		report.tool.show_feat_hdr = SHOW_FEAT_HEADER_FULL_INFO;
	अगर (report.stats_mode || report.tasks_mode)
		use_browser = 0;
	अगर (report.stats_mode && report.tasks_mode) अणु
		pr_err("Error: --tasks and --mmaps can't be used together with --stats\n");
		जाओ error;
	पूर्ण

	अगर (report.total_cycles_mode) अणु
		अगर (sort__mode != SORT_MODE__BRANCH)
			report.total_cycles_mode = false;
		अन्यथा
			sort_order = शून्य;
	पूर्ण

	अगर (म_भेद(input_name, "-") != 0)
		setup_browser(true);
	अन्यथा
		use_browser = 0;

	अगर (sort_order && म_माला(sort_order, "ipc")) अणु
		parse_options_usage(report_usage, options, "s", 1);
		जाओ error;
	पूर्ण

	अगर (sort_order && म_माला(sort_order, "symbol")) अणु
		अगर (sort__mode == SORT_MODE__BRANCH) अणु
			snम_लिखो(sort_पंचांगp, माप(sort_पंचांगp), "%s,%s",
				 sort_order, "ipc_lbr");
			report.symbol_ipc = true;
		पूर्ण अन्यथा अणु
			snम_लिखो(sort_पंचांगp, माप(sort_पंचांगp), "%s,%s",
				 sort_order, "ipc_null");
		पूर्ण

		sort_order = sort_पंचांगp;
	पूर्ण

	अगर ((last_key != K_SWITCH_INPUT_DATA && last_key != K_RELOAD) &&
	    (setup_sorting(session->evlist) < 0)) अणु
		अगर (sort_order)
			parse_options_usage(report_usage, options, "s", 1);
		अगर (field_order)
			parse_options_usage(sort_order ? शून्य : report_usage,
					    options, "F", 1);
		जाओ error;
	पूर्ण

	अगर ((report.header || report.header_only) && !quiet) अणु
		perf_session__ख_लिखो_info(session, मानक_निकास,
					   report.show_full_info);
		अगर (report.header_only) अणु
			अगर (data.is_pipe) अणु
				/*
				 * we need to process first few records
				 * which contains PERF_RECORD_HEADER_FEATURE.
				 */
				perf_session__process_events(session);
			पूर्ण
			ret = 0;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अगर (use_browser == 0 && !quiet &&
		   !report.stats_mode && !report.tasks_mode) अणु
		ख_माला_दो("# To display the perf.data header info, please use --header/--header-only options.\n#\n",
		      मानक_निकास);
	पूर्ण

	/*
	 * Only in the TUI browser we are करोing पूर्णांकegrated annotation,
	 * so करोn't allocate extra space that won't be used in the stdio
	 * implementation.
	 */
	अगर (ui__has_annotation() || report.symbol_ipc ||
	    report.total_cycles_mode) अणु
		ret = symbol__annotation_init();
		अगर (ret < 0)
			जाओ error;
		/*
 		 * For searching by name on the "Browse map details".
 		 * providing it only in verbose mode not to bloat too
 		 * much काष्ठा symbol.
 		 */
		अगर (verbose > 0) अणु
			/*
			 * XXX: Need to provide a less kludgy way to ask क्रम
			 * more space per symbol, the u32 is क्रम the index on
			 * the ui browser.
			 * See symbol__browser_index.
			 */
			symbol_conf.priv_size += माप(u32);
			symbol_conf.sort_by_name = true;
		पूर्ण
		annotation_config__init(&report.annotation_opts);
	पूर्ण

	अगर (symbol__init(&session->header.env) < 0)
		जाओ error;

	अगर (report.समय_str) अणु
		ret = perf_समय__parse_क्रम_ranges(report.समय_str, session,
						  &report.pसमय_range,
						  &report.range_size,
						  &report.range_num);
		अगर (ret < 0)
			जाओ error;

		itrace_synth_opts__set_समय_range(&itrace_synth_opts,
						  report.pसमय_range,
						  report.range_num);
	पूर्ण

	अगर (session->tevent.pevent &&
	    tep_set_function_resolver(session->tevent.pevent,
				      machine__resolve_kernel_addr,
				      &session->machines.host) < 0) अणु
		pr_err("%s: failed to set libtraceevent function resolver\n",
		       __func__);
		वापस -1;
	पूर्ण

	sort__setup_elide(मानक_निकास);

	ret = __cmd_report(&report);
	अगर (ret == K_SWITCH_INPUT_DATA || ret == K_RELOAD) अणु
		perf_session__delete(session);
		last_key = K_SWITCH_INPUT_DATA;
		जाओ repeat;
	पूर्ण अन्यथा
		ret = 0;

error:
	अगर (report.pसमय_range) अणु
		itrace_synth_opts__clear_समय_range(&itrace_synth_opts);
		zमुक्त(&report.pसमय_range);
	पूर्ण

	अगर (report.block_reports) अणु
		block_info__मुक्त_report(report.block_reports,
					report.nr_block_reports);
		report.block_reports = शून्य;
	पूर्ण

	zstd_fini(&(session->zstd_data));
	perf_session__delete(session);
	वापस ret;
पूर्ण
