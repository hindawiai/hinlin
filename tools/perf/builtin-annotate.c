<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-annotate.c
 *
 * Builtin annotate command: Analyze the perf.data input file,
 * look up and पढ़ो DSOs and symbol inक्रमmation and display
 * a histogram of results, aदीर्घ various sorting keys.
 */
#समावेश "builtin.h"

#समावेश "util/color.h"
#समावेश <linux/list.h>
#समावेश "util/cache.h"
#समावेश <linux/rbtree.h>
#समावेश <linux/zभाग.स>
#समावेश "util/symbol.h"

#समावेश "perf.h"
#समावेश "util/debug.h"

#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/annotate.h"
#समावेश "util/event.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/parse-events.h"
#समावेश "util/sort.h"
#समावेश "util/hist.h"
#समावेश "util/dso.h"
#समावेश "util/machine.h"
#समावेश "util/map.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/data.h"
#समावेश "arch/common.h"
#समावेश "util/block-range.h"
#समावेश "util/map_symbol.h"
#समावेश "util/branch.h"

#समावेश <dlfcn.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/err.h>

काष्ठा perf_annotate अणु
	काष्ठा perf_tool tool;
	काष्ठा perf_session *session;
	काष्ठा annotation_options opts;
	bool	   use_tui, use_stdio, use_stdio2, use_gtk;
	bool	   skip_missing;
	bool	   has_br_stack;
	bool	   group_set;
	स्थिर अक्षर *sym_hist_filter;
	स्थिर अक्षर *cpu_list;
	DECLARE_BITMAP(cpu_biपंचांगap, MAX_NR_CPUS);
पूर्ण;

/*
 * Given one basic block:
 *
 *	from	to		branch_i
 *	* ----> *
 *		|
 *		| block
 *		v
 *		* ----> *
 *		from	to	branch_i+1
 *
 * where the horizontal are the branches and the vertical is the executed
 * block of inकाष्ठाions.
 *
 * We count, क्रम each 'instruction', the number of blocks that covered it as
 * well as count the ratio each branch is taken.
 *
 * We can करो this without knowing the actual inकाष्ठाion stream by keeping
 * track of the address ranges. We अवरोध करोwn ranges such that there is no
 * overlap and iterate from the start until the end.
 *
 * @acme: once we parse the objdump output _beक्रमe_ processing the samples,
 * we can easily fold the branch.cycles IPC bits in.
 */
अटल व्योम process_basic_block(काष्ठा addr_map_symbol *start,
				काष्ठा addr_map_symbol *end,
				काष्ठा branch_flags *flags)
अणु
	काष्ठा symbol *sym = start->ms.sym;
	काष्ठा annotation *notes = sym ? symbol__annotation(sym) : शून्य;
	काष्ठा block_range_iter iter;
	काष्ठा block_range *entry;

	/*
	 * Sanity; शून्य isn't executable and the CPU cannot execute backwards
	 */
	अगर (!start->addr || start->addr > end->addr)
		वापस;

	iter = block_range__create(start->addr, end->addr);
	अगर (!block_range_iter__valid(&iter))
		वापस;

	/*
	 * First block in range is a branch target.
	 */
	entry = block_range_iter(&iter);
	निश्चित(entry->is_target);
	entry->entry++;

	करो अणु
		entry = block_range_iter(&iter);

		entry->coverage++;
		entry->sym = sym;

		अगर (notes)
			notes->max_coverage = max(notes->max_coverage, entry->coverage);

	पूर्ण जबतक (block_range_iter__next(&iter));

	/*
	 * Last block in rage is a branch.
	 */
	entry = block_range_iter(&iter);
	निश्चित(entry->is_branch);
	entry->taken++;
	अगर (flags->predicted)
		entry->pred++;
पूर्ण

अटल व्योम process_branch_stack(काष्ठा branch_stack *bs, काष्ठा addr_location *al,
				 काष्ठा perf_sample *sample)
अणु
	काष्ठा addr_map_symbol *prev = शून्य;
	काष्ठा branch_info *bi;
	पूर्णांक i;

	अगर (!bs || !bs->nr)
		वापस;

	bi = sample__resolve_bstack(sample, al);
	अगर (!bi)
		वापस;

	क्रम (i = bs->nr - 1; i >= 0; i--) अणु
		/*
		 * XXX filter against symbol
		 */
		अगर (prev)
			process_basic_block(prev, &bi[i].from, &bi[i].flags);
		prev = &bi[i].to;
	पूर्ण

	मुक्त(bi);
पूर्ण

अटल पूर्णांक hist_iter__branch_callback(काष्ठा hist_entry_iter *iter,
				      काष्ठा addr_location *al __maybe_unused,
				      bool single __maybe_unused,
				      व्योम *arg __maybe_unused)
अणु
	काष्ठा hist_entry *he = iter->he;
	काष्ठा branch_info *bi;
	काष्ठा perf_sample *sample = iter->sample;
	काष्ठा evsel *evsel = iter->evsel;
	पूर्णांक err;

	bi = he->branch_info;
	err = addr_map_symbol__inc_samples(&bi->from, sample, evsel);

	अगर (err)
		जाओ out;

	err = addr_map_symbol__inc_samples(&bi->to, sample, evsel);

out:
	वापस err;
पूर्ण

अटल पूर्णांक process_branch_callback(काष्ठा evsel *evsel,
				   काष्ठा perf_sample *sample,
				   काष्ठा addr_location *al __maybe_unused,
				   काष्ठा perf_annotate *ann,
				   काष्ठा machine *machine)
अणु
	काष्ठा hist_entry_iter iter = अणु
		.evsel		= evsel,
		.sample		= sample,
		.add_entry_cb	= hist_iter__branch_callback,
		.hide_unresolved	= symbol_conf.hide_unresolved,
		.ops		= &hist_iter_branch,
	पूर्ण;

	काष्ठा addr_location a;
	पूर्णांक ret;

	अगर (machine__resolve(machine, &a, sample) < 0)
		वापस -1;

	अगर (a.sym == शून्य)
		वापस 0;

	अगर (a.map != शून्य)
		a.map->dso->hit = 1;

	hist__account_cycles(sample->branch_stack, al, sample, false, शून्य);

	ret = hist_entry_iter__add(&iter, &a, PERF_MAX_STACK_DEPTH, ann);
	वापस ret;
पूर्ण

अटल bool has_annotation(काष्ठा perf_annotate *ann)
अणु
	वापस ui__has_annotation() || ann->use_stdio2;
पूर्ण

अटल पूर्णांक evsel__add_sample(काष्ठा evsel *evsel, काष्ठा perf_sample *sample,
			     काष्ठा addr_location *al, काष्ठा perf_annotate *ann,
			     काष्ठा machine *machine)
अणु
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry *he;
	पूर्णांक ret;

	अगर ((!ann->has_br_stack || !has_annotation(ann)) &&
	    ann->sym_hist_filter != शून्य &&
	    (al->sym == शून्य ||
	     म_भेद(ann->sym_hist_filter, al->sym->name) != 0)) अणु
		/* We're only पूर्णांकerested in a symbol named sym_hist_filter */
		/*
		 * FIXME: why isn't this करोne in the symbol_filter when loading
		 * the DSO?
		 */
		अगर (al->sym != शून्य) अणु
			rb_erase_cached(&al->sym->rb_node,
				 &al->map->dso->symbols);
			symbol__delete(al->sym);
			dso__reset_find_symbol_cache(al->map->dso);
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * XXX filtered samples can still have branch entries poपूर्णांकing पूर्णांकo our
	 * symbol and are missed.
	 */
	process_branch_stack(sample->branch_stack, al, sample);

	अगर (ann->has_br_stack && has_annotation(ann))
		वापस process_branch_callback(evsel, sample, al, ann, machine);

	he = hists__add_entry(hists, al, शून्य, शून्य, शून्य, sample, true);
	अगर (he == शून्य)
		वापस -ENOMEM;

	ret = hist_entry__inc_addr_samples(he, sample, evsel, al->addr);
	hists__inc_nr_samples(hists, true);
	वापस ret;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	काष्ठा perf_annotate *ann = container_of(tool, काष्ठा perf_annotate, tool);
	काष्ठा addr_location al;
	पूर्णांक ret = 0;

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		pr_warning("problem processing %d event, skipping it.\n",
			   event->header.type);
		वापस -1;
	पूर्ण

	अगर (ann->cpu_list && !test_bit(sample->cpu, ann->cpu_biपंचांगap))
		जाओ out_put;

	अगर (!al.filtered &&
	    evsel__add_sample(evsel, sample, &al, ann, machine)) अणु
		pr_warning("problem incrementing symbol count, "
			   "skipping event\n");
		ret = -1;
	पूर्ण
out_put:
	addr_location__put(&al);
	वापस ret;
पूर्ण

अटल पूर्णांक process_feature_event(काष्ठा perf_session *session,
				 जोड़ perf_event *event)
अणु
	अगर (event->feat.feat_id < HEADER_LAST_FEATURE)
		वापस perf_event__process_feature(session, event);
	वापस 0;
पूर्ण

अटल पूर्णांक hist_entry__tty_annotate(काष्ठा hist_entry *he,
				    काष्ठा evsel *evsel,
				    काष्ठा perf_annotate *ann)
अणु
	अगर (!ann->use_stdio2)
		वापस symbol__tty_annotate(&he->ms, evsel, &ann->opts);

	वापस symbol__tty_annotate2(&he->ms, evsel, &ann->opts);
पूर्ण

अटल व्योम hists__find_annotations(काष्ठा hists *hists,
				    काष्ठा evsel *evsel,
				    काष्ठा perf_annotate *ann)
अणु
	काष्ठा rb_node *nd = rb_first_cached(&hists->entries), *next;
	पूर्णांक key = K_RIGHT;

	जबतक (nd) अणु
		काष्ठा hist_entry *he = rb_entry(nd, काष्ठा hist_entry, rb_node);
		काष्ठा annotation *notes;

		अगर (he->ms.sym == शून्य || he->ms.map->dso->annotate_warned)
			जाओ find_next;

		अगर (ann->sym_hist_filter &&
		    (म_भेद(he->ms.sym->name, ann->sym_hist_filter) != 0))
			जाओ find_next;

		notes = symbol__annotation(he->ms.sym);
		अगर (notes->src == शून्य) अणु
find_next:
			अगर (key == K_LEFT)
				nd = rb_prev(nd);
			अन्यथा
				nd = rb_next(nd);
			जारी;
		पूर्ण

		अगर (use_browser == 2) अणु
			पूर्णांक ret;
			पूर्णांक (*annotate)(काष्ठा hist_entry *he,
					काष्ठा evsel *evsel,
					काष्ठा hist_browser_समयr *hbt);

			annotate = dlsym(perf_gtk_handle,
					 "hist_entry__gtk_annotate");
			अगर (annotate == शून्य) अणु
				ui__error("GTK browser not found!\n");
				वापस;
			पूर्ण

			ret = annotate(he, evsel, शून्य);
			अगर (!ret || !ann->skip_missing)
				वापस;

			/* skip missing symbols */
			nd = rb_next(nd);
		पूर्ण अन्यथा अगर (use_browser == 1) अणु
			key = hist_entry__tui_annotate(he, evsel, शून्य, &ann->opts);

			चयन (key) अणु
			हाल -1:
				अगर (!ann->skip_missing)
					वापस;
				/* fall through */
			हाल K_RIGHT:
				next = rb_next(nd);
				अवरोध;
			हाल K_LEFT:
				next = rb_prev(nd);
				अवरोध;
			शेष:
				वापस;
			पूर्ण

			अगर (next != शून्य)
				nd = next;
		पूर्ण अन्यथा अणु
			hist_entry__tty_annotate(he, evsel, ann);
			nd = rb_next(nd);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __cmd_annotate(काष्ठा perf_annotate *ann)
अणु
	पूर्णांक ret;
	काष्ठा perf_session *session = ann->session;
	काष्ठा evsel *pos;
	u64 total_nr_samples;

	अगर (ann->cpu_list) अणु
		ret = perf_session__cpu_biपंचांगap(session, ann->cpu_list,
					       ann->cpu_biपंचांगap);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (!ann->opts.objdump_path) अणु
		ret = perf_env__lookup_objdump(&session->header.env,
					       &ann->opts.objdump_path);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = perf_session__process_events(session);
	अगर (ret)
		जाओ out;

	अगर (dump_trace) अणु
		perf_session__ख_लिखो_nr_events(session, मानक_निकास, false);
		evlist__ख_लिखो_nr_events(session->evlist, मानक_निकास, false);
		जाओ out;
	पूर्ण

	अगर (verbose > 3)
		perf_session__ख_लिखो(session, मानक_निकास);

	अगर (verbose > 2)
		perf_session__ख_लिखो_dsos(session, मानक_निकास);

	total_nr_samples = 0;
	evlist__क्रम_each_entry(session->evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);
		u32 nr_samples = hists->stats.nr_samples;

		अगर (nr_samples > 0) अणु
			total_nr_samples += nr_samples;
			hists__collapse_resort(hists, शून्य);
			/* Don't sort callchain */
			evsel__reset_sample_bit(pos, CALLCHAIN);
			evsel__output_resort(pos, शून्य);

			अगर (symbol_conf.event_group && !evsel__is_group_leader(pos))
				जारी;

			hists__find_annotations(hists, pos, ann);
		पूर्ण
	पूर्ण

	अगर (total_nr_samples == 0) अणु
		ui__error("The %s data has no samples!\n", session->data->path);
		जाओ out;
	पूर्ण

	अगर (use_browser == 2) अणु
		व्योम (*show_annotations)(व्योम);

		show_annotations = dlsym(perf_gtk_handle,
					 "perf_gtk__show_annotations");
		अगर (show_annotations == शून्य) अणु
			ui__error("GTK browser not found!\n");
			जाओ out;
		पूर्ण
		show_annotations();
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर annotate_usage[] = अणु
	"perf annotate [<options>]",
	शून्य
पूर्ण;

पूर्णांक cmd_annotate(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा perf_annotate annotate = अणु
		.tool = अणु
			.sample	= process_sample_event,
			.mmap	= perf_event__process_mmap,
			.mmap2	= perf_event__process_mmap2,
			.comm	= perf_event__process_comm,
			.निकास	= perf_event__process_निकास,
			.विभाजन	= perf_event__process_विभाजन,
			.namespaces = perf_event__process_namespaces,
			.attr	= perf_event__process_attr,
			.build_id = perf_event__process_build_id,
			.tracing_data   = perf_event__process_tracing_data,
			.feature	= process_feature_event,
			.ordered_events = true,
			.ordering_requires_बारtamps = true,
		पूर्ण,
		.opts = annotation__शेष_options,
	पूर्ण;
	काष्ठा perf_data data = अणु
		.mode  = PERF_DATA_MODE_READ,
	पूर्ण;
	काष्ठा option options[] = अणु
	OPT_STRING('i', "input", &input_name, "file",
		    "input file name"),
	OPT_STRING('d', "dsos", &symbol_conf.dso_list_str, "dso[,dso...]",
		   "only consider symbols in these dsos"),
	OPT_STRING('s', "symbol", &annotate.sym_hist_filter, "symbol",
		    "symbol to annotate"),
	OPT_BOOLEAN('f', "force", &data.force, "don't complain, करो it"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('q', "quiet", &quiet, "do now show any message"),
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace,
		    "dump raw trace in ASCII"),
	OPT_BOOLEAN(0, "gtk", &annotate.use_gtk, "Use the GTK interface"),
	OPT_BOOLEAN(0, "tui", &annotate.use_tui, "Use the TUI interface"),
	OPT_BOOLEAN(0, "stdio", &annotate.use_stdio, "Use the stdio interface"),
	OPT_BOOLEAN(0, "stdio2", &annotate.use_stdio2, "Use the stdio interface"),
	OPT_BOOLEAN(0, "ignore-vmlinux", &symbol_conf.ignore_vmlinux,
                    "don't load vmlinux even if found"),
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_BOOLEAN('m', "modules", &symbol_conf.use_modules,
		    "load module symbols - WARNING: use only with -k and LIVE kernel"),
	OPT_BOOLEAN('l', "print-line", &annotate.opts.prपूर्णांक_lines,
		    "print matching source lines (may be slow)"),
	OPT_BOOLEAN('P', "full-paths", &annotate.opts.full_path,
		    "Don't shorten the displayed pathnames"),
	OPT_BOOLEAN(0, "skip-missing", &annotate.skip_missing,
		    "Skip symbols that cannot be annotated"),
	OPT_BOOLEAN_SET(0, "group", &symbol_conf.event_group,
			&annotate.group_set,
			"Show event group information together"),
	OPT_STRING('C', "cpu", &annotate.cpu_list, "cpu", "list of cpus to profile"),
	OPT_CALLBACK(0, "symfs", शून्य, "directory",
		     "Look for files with symbols relative to this directory",
		     symbol__config_symfs),
	OPT_BOOLEAN(0, "source", &annotate.opts.annotate_src,
		    "Interleave source code with assembly code (default)"),
	OPT_BOOLEAN(0, "asm-raw", &annotate.opts.show_यंत्र_raw,
		    "Display raw encoding of assembly instructions (default)"),
	OPT_STRING('M', "disassembler-style", &annotate.opts.disassembler_style, "disassembler style",
		   "Specify disassembler style (e.g. -M intel for intel syntax)"),
	OPT_STRING(0, "prefix", &annotate.opts.prefix, "prefix",
		    "Add prefix to source file path names in programs (with --prefix-strip)"),
	OPT_STRING(0, "prefix-strip", &annotate.opts.prefix_strip, "N",
		    "Strip first N entries of source file path name in programs (with --prefix)"),
	OPT_STRING(0, "objdump", &annotate.opts.objdump_path, "path",
		   "objdump binary to use for disassembly and annotations"),
	OPT_BOOLEAN(0, "demangle", &symbol_conf.demangle,
		    "Enable symbol demangling"),
	OPT_BOOLEAN(0, "demangle-kernel", &symbol_conf.demangle_kernel,
		    "Enable kernel symbol demangling"),
	OPT_BOOLEAN(0, "group", &symbol_conf.event_group,
		    "Show event group information together"),
	OPT_BOOLEAN(0, "show-total-period", &symbol_conf.show_total_period,
		    "Show a column with the sum of periods"),
	OPT_BOOLEAN('n', "show-nr-samples", &symbol_conf.show_nr_samples,
		    "Show a column with the number of samples"),
	OPT_CALLBACK_DEFAULT(0, "stdio-color", शून्य, "mode",
			     "'always' (default), 'never' or 'auto' only applicable to --stdio mode",
			     stdio__config_color, "always"),
	OPT_CALLBACK(0, "percent-type", &annotate.opts, "local-period",
		     "Set percent type local/global-period/hits",
		     annotate_parse_percent_type),

	OPT_END()
	पूर्ण;
	पूर्णांक ret;

	set_option_flag(options, 0, "show-total-period", PARSE_OPT_EXCLUSIVE);
	set_option_flag(options, 0, "show-nr-samples", PARSE_OPT_EXCLUSIVE);


	ret = hists__init();
	अगर (ret < 0)
		वापस ret;

	annotation_config__init(&annotate.opts);

	argc = parse_options(argc, argv, options, annotate_usage, 0);
	अगर (argc) अणु
		/*
		 * Special हाल: अगर there's an argument left then assume that
		 * it's a symbol filter:
		 */
		अगर (argc > 1)
			usage_with_options(annotate_usage, options);

		annotate.sym_hist_filter = argv[0];
	पूर्ण

	अगर (annotate_check_args(&annotate.opts) < 0)
		वापस -EINVAL;

	अगर (symbol_conf.show_nr_samples && annotate.use_gtk) अणु
		pr_err("--show-nr-samples is not available in --gtk mode at this time\n");
		वापस ret;
	पूर्ण

	अगर (quiet)
		perf_quiet_option();

	data.path = input_name;

	annotate.session = perf_session__new(&data, false, &annotate.tool);
	अगर (IS_ERR(annotate.session))
		वापस PTR_ERR(annotate.session);

	annotate.has_br_stack = perf_header__has_feat(&annotate.session->header,
						      HEADER_BRANCH_STACK);

	अगर (annotate.group_set)
		evlist__क्रमce_leader(annotate.session->evlist);

	ret = symbol__annotation_init();
	अगर (ret < 0)
		जाओ out_delete;

	symbol_conf.try_vmlinux_path = true;

	ret = symbol__init(&annotate.session->header.env);
	अगर (ret < 0)
		जाओ out_delete;

	अगर (annotate.use_stdio || annotate.use_stdio2)
		use_browser = 0;
	अन्यथा अगर (annotate.use_tui)
		use_browser = 1;
	अन्यथा अगर (annotate.use_gtk)
		use_browser = 2;

	setup_browser(true);

	/*
	 * Events of dअगरferent processes may correspond to the same
	 * symbol, we करो not care about the processes in annotate,
	 * set sort order to aव्योम repeated output.
	 */
	sort_order = "dso,symbol";

	/*
	 * Set SORT_MODE__BRANCH so that annotate display IPC/Cycle
	 * अगर branch info is in perf data in TUI mode.
	 */
	अगर ((use_browser == 1 || annotate.use_stdio2) && annotate.has_br_stack)
		sort__mode = SORT_MODE__BRANCH;

	अगर (setup_sorting(शून्य) < 0)
		usage_with_options(annotate_usage, options);

	ret = __cmd_annotate(&annotate);

out_delete:
	/*
	 * Speed up the निकास process, क्रम large files this can
	 * take quite a जबतक.
	 *
	 * XXX Enable this when using valgrind or अगर we ever
	 * librarize this command.
	 *
	 * Also experiment with obstacks to see how much speed
	 * up we'll get here.
	 *
	 * perf_session__delete(session);
	 */
	वापस ret;
पूर्ण
