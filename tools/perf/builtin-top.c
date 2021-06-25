<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * builtin-top.c
 *
 * Builtin top command: Display a continuously updated profile of
 * any workload, CPU or specअगरic PID.
 *
 * Copyright (C) 2008, Red Hat Inc, Ingo Molnar <mingo@redhat.com>
 *		 2011, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Improvements and fixes by:
 *
 *   Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 *   Yanmin Zhang <yanmin.zhang@पूर्णांकel.com>
 *   Wu Fengguang <fengguang.wu@पूर्णांकel.com>
 *   Mike Galbraith <efault@gmx.de>
 *   Paul Mackerras <paulus@samba.org>
 */
#समावेश "builtin.h"

#समावेश "perf.h"

#समावेश "util/annotate.h"
#समावेश "util/bpf-event.h"
#समावेश "util/config.h"
#समावेश "util/color.h"
#समावेश "util/dso.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/evsel_config.h"
#समावेश "util/event.h"
#समावेश "util/machine.h"
#समावेश "util/map.h"
#समावेश "util/mmap.h"
#समावेश "util/session.h"
#समावेश "util/thread.h"
#समावेश "util/symbol.h"
#समावेश "util/synthetic-events.h"
#समावेश "util/top.h"
#समावेश "util/util.h"
#समावेश <linux/rbtree.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/parse-events.h"
#समावेश "util/callchain.h"
#समावेश "util/cpumap.h"
#समावेश "util/sort.h"
#समावेश "util/string2.h"
#समावेश "util/term.h"
#समावेश "util/intlist.h"
#समावेश "util/parse-branch-options.h"
#समावेश "arch/common.h"
#समावेश "ui/ui.h"

#समावेश "util/debug.h"
#समावेश "util/ordered-events.h"
#समावेश "util/pfm.h"

#समावेश <निश्चित.स>
#समावेश <elf.h>
#समावेश <fcntl.h>

#समावेश <मानकपन.स>
#समावेश <termios.h>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>

#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <sched.h>
#समावेश <संकेत.स>

#समावेश <sys/syscall.h>
#समावेश <sys/ioctl.h>
#समावेश <poll.h>
#समावेश <sys/prctl.h>
#समावेश <sys/रुको.h>
#समावेश <sys/uपन.स>
#समावेश <sys/utsname.h>
#समावेश <sys/mman.h>

#समावेश <linux/stringअगरy.h>
#समावेश <linux/समय64.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>

#समावेश <linux/प्रकार.स>
#समावेश <perf/mmap.h>

अटल अस्थिर पूर्णांक करोne;
अटल अस्थिर पूर्णांक resize;

#घोषणा HEADER_LINE_NR  5

अटल व्योम perf_top__update_prपूर्णांक_entries(काष्ठा perf_top *top)
अणु
	top->prपूर्णांक_entries = top->winsize.ws_row - HEADER_LINE_NR;
पूर्ण

अटल व्योम winch_sig(पूर्णांक sig __maybe_unused)
अणु
	resize = 1;
पूर्ण

अटल व्योम perf_top__resize(काष्ठा perf_top *top)
अणु
	get_term_dimensions(&top->winsize);
	perf_top__update_prपूर्णांक_entries(top);
पूर्ण

अटल पूर्णांक perf_top__parse_source(काष्ठा perf_top *top, काष्ठा hist_entry *he)
अणु
	काष्ठा evsel *evsel;
	काष्ठा symbol *sym;
	काष्ठा annotation *notes;
	काष्ठा map *map;
	पूर्णांक err = -1;

	अगर (!he || !he->ms.sym)
		वापस -1;

	evsel = hists_to_evsel(he->hists);

	sym = he->ms.sym;
	map = he->ms.map;

	/*
	 * We can't annotate with just /proc/kallsyms
	 */
	अगर (map->dso->symtab_type == DSO_BINARY_TYPE__KALLSYMS &&
	    !dso__is_kcore(map->dso)) अणु
		pr_err("Can't annotate %s: No vmlinux file was found in the "
		       "path\n", sym->name);
		sleep(1);
		वापस -1;
	पूर्ण

	notes = symbol__annotation(sym);
	pthपढ़ो_mutex_lock(&notes->lock);

	अगर (!symbol__hists(sym, top->evlist->core.nr_entries)) अणु
		pthपढ़ो_mutex_unlock(&notes->lock);
		pr_err("Not enough memory for annotating '%s' symbol!\n",
		       sym->name);
		sleep(1);
		वापस err;
	पूर्ण

	err = symbol__annotate(&he->ms, evsel, &top->annotation_opts, शून्य);
	अगर (err == 0) अणु
		top->sym_filter_entry = he;
	पूर्ण अन्यथा अणु
		अक्षर msg[बफ_मान];
		symbol__म_त्रुटि_disassemble(&he->ms, err, msg, माप(msg));
		pr_err("Couldn't annotate %s: %s\n", sym->name, msg);
	पूर्ण

	pthपढ़ो_mutex_unlock(&notes->lock);
	वापस err;
पूर्ण

अटल व्योम __zero_source_counters(काष्ठा hist_entry *he)
अणु
	काष्ठा symbol *sym = he->ms.sym;
	symbol__annotate_zero_histograms(sym);
पूर्ण

अटल व्योम ui__warn_map_erange(काष्ठा map *map, काष्ठा symbol *sym, u64 ip)
अणु
	काष्ठा utsname uts;
	पूर्णांक err = uname(&uts);

	ui__warning("Out of bounds address found:\n\n"
		    "Addr:   %" PRIx64 "\n"
		    "DSO:    %s %c\n"
		    "Map:    %" PRIx64 "-%" PRIx64 "\n"
		    "Symbol: %" PRIx64 "-%" PRIx64 " %c %s\n"
		    "Arch:   %s\n"
		    "Kernel: %s\n"
		    "Tools:  %s\n\n"
		    "Not all samples will be on the annotation output.\n\n"
		    "Please report to linux-kernel@vger.kernel.org\n",
		    ip, map->dso->दीर्घ_name, dso__symtab_origin(map->dso),
		    map->start, map->end, sym->start, sym->end,
		    sym->binding == STB_GLOBAL ? 'g' :
		    sym->binding == STB_LOCAL  ? 'l' : 'w', sym->name,
		    err ? "[unknown]" : uts.machine,
		    err ? "[unknown]" : uts.release, perf_version_string);
	अगर (use_browser <= 0)
		sleep(5);

	map->erange_warned = true;
पूर्ण

अटल व्योम perf_top__record_precise_ip(काष्ठा perf_top *top,
					काष्ठा hist_entry *he,
					काष्ठा perf_sample *sample,
					काष्ठा evsel *evsel, u64 ip)
अणु
	काष्ठा annotation *notes;
	काष्ठा symbol *sym = he->ms.sym;
	पूर्णांक err = 0;

	अगर (sym == शून्य || (use_browser == 0 &&
			    (top->sym_filter_entry == शून्य ||
			     top->sym_filter_entry->ms.sym != sym)))
		वापस;

	notes = symbol__annotation(sym);

	अगर (pthपढ़ो_mutex_trylock(&notes->lock))
		वापस;

	err = hist_entry__inc_addr_samples(he, sample, evsel, ip);

	pthपढ़ो_mutex_unlock(&notes->lock);

	अगर (unlikely(err)) अणु
		/*
		 * This function is now called with he->hists->lock held.
		 * Release it beक्रमe going to sleep.
		 */
		pthपढ़ो_mutex_unlock(&he->hists->lock);

		अगर (err == -दुस्फल && !he->ms.map->erange_warned)
			ui__warn_map_erange(he->ms.map, sym, ip);
		अन्यथा अगर (err == -ENOMEM) अणु
			pr_err("Not enough memory for annotating '%s' symbol!\n",
			       sym->name);
			sleep(1);
		पूर्ण

		pthपढ़ो_mutex_lock(&he->hists->lock);
	पूर्ण
पूर्ण

अटल व्योम perf_top__show_details(काष्ठा perf_top *top)
अणु
	काष्ठा hist_entry *he = top->sym_filter_entry;
	काष्ठा evsel *evsel;
	काष्ठा annotation *notes;
	काष्ठा symbol *symbol;
	पूर्णांक more;

	अगर (!he)
		वापस;

	evsel = hists_to_evsel(he->hists);

	symbol = he->ms.sym;
	notes = symbol__annotation(symbol);

	pthपढ़ो_mutex_lock(&notes->lock);

	symbol__calc_percent(symbol, evsel);

	अगर (notes->src == शून्य)
		जाओ out_unlock;

	म_लिखो("Showing %s for %s\n", evsel__name(top->sym_evsel), symbol->name);
	म_लिखो("  Events  Pcnt (>=%d%%)\n", top->annotation_opts.min_pcnt);

	more = symbol__annotate_म_लिखो(&he->ms, top->sym_evsel, &top->annotation_opts);

	अगर (top->evlist->enabled) अणु
		अगर (top->zero)
			symbol__annotate_zero_histogram(symbol, top->sym_evsel->idx);
		अन्यथा
			symbol__annotate_decay_histogram(symbol, top->sym_evsel->idx);
	पूर्ण
	अगर (more != 0)
		म_लिखो("%d lines not displayed, maybe increase display entries [e]\n", more);
out_unlock:
	pthपढ़ो_mutex_unlock(&notes->lock);
पूर्ण

अटल व्योम perf_top__resort_hists(काष्ठा perf_top *t)
अणु
	काष्ठा evlist *evlist = t->evlist;
	काष्ठा evsel *pos;

	evlist__क्रम_each_entry(evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);

		/*
		 * unlink existing entries so that they can be linked
		 * in a correct order in hists__match() below.
		 */
		hists__unlink(hists);

		अगर (evlist->enabled) अणु
			अगर (t->zero) अणु
				hists__delete_entries(hists);
			पूर्ण अन्यथा अणु
				hists__decay_entries(hists, t->hide_user_symbols,
						     t->hide_kernel_symbols);
			पूर्ण
		पूर्ण

		hists__collapse_resort(hists, शून्य);

		/* Non-group events are considered as leader */
		अगर (symbol_conf.event_group && !evsel__is_group_leader(pos)) अणु
			काष्ठा hists *leader_hists = evsel__hists(pos->leader);

			hists__match(leader_hists, hists);
			hists__link(leader_hists, hists);
		पूर्ण
	पूर्ण

	evlist__क्रम_each_entry(evlist, pos) अणु
		evsel__output_resort(pos, शून्य);
	पूर्ण
पूर्ण

अटल व्योम perf_top__prपूर्णांक_sym_table(काष्ठा perf_top *top)
अणु
	अक्षर bf[160];
	पूर्णांक prपूर्णांकed = 0;
	स्थिर पूर्णांक win_width = top->winsize.ws_col - 1;
	काष्ठा evsel *evsel = top->sym_evsel;
	काष्ठा hists *hists = evsel__hists(evsel);

	माला_दो(CONSOLE_CLEAR);

	perf_top__header_snम_लिखो(top, bf, माप(bf));
	म_लिखो("%s\n", bf);

	म_लिखो("%-*.*s\n", win_width, win_width, graph_करोtted_line);

	अगर (!top->record_opts.overग_लिखो &&
	    (top->evlist->stats.nr_lost_warned !=
	     top->evlist->stats.nr_events[PERF_RECORD_LOST])) अणु
		top->evlist->stats.nr_lost_warned =
			      top->evlist->stats.nr_events[PERF_RECORD_LOST];
		color_ख_लिखो(मानक_निकास, PERF_COLOR_RED,
			      "WARNING: LOST %d chunks, Check IO/CPU overload",
			      top->evlist->stats.nr_lost_warned);
		++prपूर्णांकed;
	पूर्ण

	अगर (top->sym_filter_entry) अणु
		perf_top__show_details(top);
		वापस;
	पूर्ण

	perf_top__resort_hists(top);

	hists__output_recalc_col_len(hists, top->prपूर्णांक_entries - prपूर्णांकed);
	अक्षर_दो('\n');
	hists__ख_लिखो(hists, false, top->prपूर्णांक_entries - prपूर्णांकed, win_width,
		       top->min_percent, मानक_निकास, !symbol_conf.use_callchain);
पूर्ण

अटल व्योम prompt_पूर्णांकeger(पूर्णांक *target, स्थिर अक्षर *msg)
अणु
	अक्षर *buf = दो_स्मृति(0), *p;
	माप_प्रकार dummy = 0;
	पूर्णांक पंचांगp;

	ख_लिखो(मानक_निकास, "\n%s: ", msg);
	अगर (getline(&buf, &dummy, मानक_निवेश) < 0)
		वापस;

	p = म_अक्षर(buf, '\n');
	अगर (p)
		*p = 0;

	p = buf;
	जबतक(*p) अणु
		अगर (!है_अंक(*p))
			जाओ out_मुक्त;
		p++;
	पूर्ण
	पंचांगp = म_से_अदीर्घ(buf, शून्य, 10);
	*target = पंचांगp;
out_मुक्त:
	मुक्त(buf);
पूर्ण

अटल व्योम prompt_percent(पूर्णांक *target, स्थिर अक्षर *msg)
अणु
	पूर्णांक पंचांगp = 0;

	prompt_पूर्णांकeger(&पंचांगp, msg);
	अगर (पंचांगp >= 0 && पंचांगp <= 100)
		*target = पंचांगp;
पूर्ण

अटल व्योम perf_top__prompt_symbol(काष्ठा perf_top *top, स्थिर अक्षर *msg)
अणु
	अक्षर *buf = दो_स्मृति(0), *p;
	काष्ठा hist_entry *syme = top->sym_filter_entry, *n, *found = शून्य;
	काष्ठा hists *hists = evsel__hists(top->sym_evsel);
	काष्ठा rb_node *next;
	माप_प्रकार dummy = 0;

	/* zero counters of active symbol */
	अगर (syme) अणु
		__zero_source_counters(syme);
		top->sym_filter_entry = शून्य;
	पूर्ण

	ख_लिखो(मानक_निकास, "\n%s: ", msg);
	अगर (getline(&buf, &dummy, मानक_निवेश) < 0)
		जाओ out_मुक्त;

	p = म_अक्षर(buf, '\n');
	अगर (p)
		*p = 0;

	next = rb_first_cached(&hists->entries);
	जबतक (next) अणु
		n = rb_entry(next, काष्ठा hist_entry, rb_node);
		अगर (n->ms.sym && !म_भेद(buf, n->ms.sym->name)) अणु
			found = n;
			अवरोध;
		पूर्ण
		next = rb_next(&n->rb_node);
	पूर्ण

	अगर (!found) अणु
		ख_लिखो(मानक_त्रुटि, "Sorry, %s is not active.\n", buf);
		sleep(1);
	पूर्ण अन्यथा
		perf_top__parse_source(top, found);

out_मुक्त:
	मुक्त(buf);
पूर्ण

अटल व्योम perf_top__prपूर्णांक_mapped_keys(काष्ठा perf_top *top)
अणु
	अक्षर *name = शून्य;

	अगर (top->sym_filter_entry) अणु
		काष्ठा symbol *sym = top->sym_filter_entry->ms.sym;
		name = sym->name;
	पूर्ण

	ख_लिखो(मानक_निकास, "\nMapped keys:\n");
	ख_लिखो(मानक_निकास, "\t[d]     display refresh delay.             \t(%d)\n", top->delay_secs);
	ख_लिखो(मानक_निकास, "\t[e]     display entries (lines).           \t(%d)\n", top->prपूर्णांक_entries);

	अगर (top->evlist->core.nr_entries > 1)
		ख_लिखो(मानक_निकास, "\t[E]     active event counter.              \t(%s)\n", evsel__name(top->sym_evsel));

	ख_लिखो(मानक_निकास, "\t[f]     profile display filter (count).    \t(%d)\n", top->count_filter);

	ख_लिखो(मानक_निकास, "\t[F]     annotate display filter (percent). \t(%d%%)\n", top->annotation_opts.min_pcnt);
	ख_लिखो(मानक_निकास, "\t[s]     annotate symbol.                   \t(%s)\n", name?: "NULL");
	ख_लिखो(मानक_निकास, "\t[S]     stop annotation.\n");

	ख_लिखो(मानक_निकास,
		"\t[K]     hide kernel symbols.             \t(%s)\n",
		top->hide_kernel_symbols ? "yes" : "no");
	ख_लिखो(मानक_निकास,
		"\t[U]     hide user symbols.               \t(%s)\n",
		top->hide_user_symbols ? "yes" : "no");
	ख_लिखो(मानक_निकास, "\t[z]     toggle sample zeroing.             \t(%d)\n", top->zero ? 1 : 0);
	ख_लिखो(मानक_निकास, "\t[qQ]    quit.\n");
पूर्ण

अटल पूर्णांक perf_top__key_mapped(काष्ठा perf_top *top, पूर्णांक c)
अणु
	चयन (c) अणु
		हाल 'd':
		हाल 'e':
		हाल 'f':
		हाल 'z':
		हाल 'q':
		हाल 'Q':
		हाल 'K':
		हाल 'U':
		हाल 'F':
		हाल 's':
		हाल 'S':
			वापस 1;
		हाल 'E':
			वापस top->evlist->core.nr_entries > 1 ? 1 : 0;
		शेष:
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool perf_top__handle_keypress(काष्ठा perf_top *top, पूर्णांक c)
अणु
	bool ret = true;

	अगर (!perf_top__key_mapped(top, c)) अणु
		काष्ठा pollfd मानक_निवेश_poll = अणु .fd = 0, .events = POLLIN पूर्ण;
		काष्ठा termios save;

		perf_top__prपूर्णांक_mapped_keys(top);
		ख_लिखो(मानक_निकास, "\nEnter selection, or unmapped key to continue: ");
		ख_साफ(मानक_निकास);

		set_term_quiet_input(&save);

		poll(&मानक_निवेश_poll, 1, -1);
		c = अ_लो(मानक_निवेश);

		tcsetattr(0, TCSAFLUSH, &save);
		अगर (!perf_top__key_mapped(top, c))
			वापस ret;
	पूर्ण

	चयन (c) अणु
		हाल 'd':
			prompt_पूर्णांकeger(&top->delay_secs, "Enter display delay");
			अगर (top->delay_secs < 1)
				top->delay_secs = 1;
			अवरोध;
		हाल 'e':
			prompt_पूर्णांकeger(&top->prपूर्णांक_entries, "Enter display entries (lines)");
			अगर (top->prपूर्णांक_entries == 0) अणु
				perf_top__resize(top);
				संकेत(SIGWINCH, winch_sig);
			पूर्ण अन्यथा अणु
				संकेत(SIGWINCH, संक_पूर्व);
			पूर्ण
			अवरोध;
		हाल 'E':
			अगर (top->evlist->core.nr_entries > 1) अणु
				/* Select 0 as the शेष event: */
				पूर्णांक counter = 0;

				ख_लिखो(मानक_त्रुटि, "\nAvailable events:");

				evlist__क्रम_each_entry(top->evlist, top->sym_evsel)
					ख_लिखो(मानक_त्रुटि, "\n\t%d %s", top->sym_evsel->idx, evsel__name(top->sym_evsel));

				prompt_पूर्णांकeger(&counter, "Enter details event counter");

				अगर (counter >= top->evlist->core.nr_entries) अणु
					top->sym_evsel = evlist__first(top->evlist);
					ख_लिखो(मानक_त्रुटि, "Sorry, no such event, using %s.\n", evsel__name(top->sym_evsel));
					sleep(1);
					अवरोध;
				पूर्ण
				evlist__क्रम_each_entry(top->evlist, top->sym_evsel)
					अगर (top->sym_evsel->idx == counter)
						अवरोध;
			पूर्ण अन्यथा
				top->sym_evsel = evlist__first(top->evlist);
			अवरोध;
		हाल 'f':
			prompt_पूर्णांकeger(&top->count_filter, "Enter display event count filter");
			अवरोध;
		हाल 'F':
			prompt_percent(&top->annotation_opts.min_pcnt,
				       "Enter details display event filter (percent)");
			अवरोध;
		हाल 'K':
			top->hide_kernel_symbols = !top->hide_kernel_symbols;
			अवरोध;
		हाल 'q':
		हाल 'Q':
			म_लिखो("exiting.\n");
			अगर (top->dump_symtab)
				perf_session__ख_लिखो_dsos(top->session, मानक_त्रुटि);
			ret = false;
			अवरोध;
		हाल 's':
			perf_top__prompt_symbol(top, "Enter details symbol");
			अवरोध;
		हाल 'S':
			अगर (!top->sym_filter_entry)
				अवरोध;
			अन्यथा अणु
				काष्ठा hist_entry *syme = top->sym_filter_entry;

				top->sym_filter_entry = शून्य;
				__zero_source_counters(syme);
			पूर्ण
			अवरोध;
		हाल 'U':
			top->hide_user_symbols = !top->hide_user_symbols;
			अवरोध;
		हाल 'z':
			top->zero = !top->zero;
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम perf_top__sort_new_samples(व्योम *arg)
अणु
	काष्ठा perf_top *t = arg;

	अगर (t->evlist->selected != शून्य)
		t->sym_evsel = t->evlist->selected;

	perf_top__resort_hists(t);

	अगर (t->lost || t->drop)
		pr_warning("Too slow to read ring buffer (change period (-c/-F) or limit CPUs (-C)\n");
पूर्ण

अटल व्योम stop_top(व्योम)
अणु
	session_करोne = 1;
	करोne = 1;
पूर्ण

अटल व्योम *display_thपढ़ो_tui(व्योम *arg)
अणु
	काष्ठा evsel *pos;
	काष्ठा perf_top *top = arg;
	स्थिर अक्षर *help = "For a higher level overview, try: perf top --sort comm,dso";
	काष्ठा hist_browser_समयr hbt = अणु
		.समयr		= perf_top__sort_new_samples,
		.arg		= top,
		.refresh	= top->delay_secs,
	पूर्ण;
	पूर्णांक ret;

	/* In order to पढ़ो symbols from other namespaces perf to  needs to call
	 * setns(2).  This isn't permitted अगर the काष्ठा_fs has multiple users.
	 * unshare(2) the fs so that we may जारी to setns पूर्णांकo namespaces
	 * that we're observing.
	 */
	unshare(CLONE_FS);

	prctl(PR_SET_NAME, "perf-top-UI", 0, 0, 0);

repeat:
	perf_top__sort_new_samples(top);

	/*
	 * Initialize the uid_filter_str, in the future the TUI will allow
	 * Zooming in/out UIDs. For now just use whatever the user passed
	 * via --uid.
	 */
	evlist__क्रम_each_entry(top->evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);
		hists->uid_filter_str = top->record_opts.target.uid_str;
	पूर्ण

	ret = evlist__tui_browse_hists(top->evlist, help, &hbt, top->min_percent,
				       &top->session->header.env, !top->record_opts.overग_लिखो,
				       &top->annotation_opts);
	अगर (ret == K_RELOAD) अणु
		top->zero = true;
		जाओ repeat;
	पूर्ण अन्यथा
		stop_top();

	वापस शून्य;
पूर्ण

अटल व्योम display_sig(पूर्णांक sig __maybe_unused)
अणु
	stop_top();
पूर्ण

अटल व्योम display_setup_sig(व्योम)
अणु
	संकेत(संक_अंश, sighandler_dump_stack);
	संकेत(संक_भ_त्रुटि, sighandler_dump_stack);
	संकेत(संक_विघ्न,  display_sig);
	संकेत(SIGQUIT, display_sig);
	संकेत(संक_इति, display_sig);
पूर्ण

अटल व्योम *display_thपढ़ो(व्योम *arg)
अणु
	काष्ठा pollfd मानक_निवेश_poll = अणु .fd = 0, .events = POLLIN पूर्ण;
	काष्ठा termios save;
	काष्ठा perf_top *top = arg;
	पूर्णांक delay_msecs, c;

	/* In order to पढ़ो symbols from other namespaces perf to  needs to call
	 * setns(2).  This isn't permitted अगर the काष्ठा_fs has multiple users.
	 * unshare(2) the fs so that we may जारी to setns पूर्णांकo namespaces
	 * that we're observing.
	 */
	unshare(CLONE_FS);

	prctl(PR_SET_NAME, "perf-top-UI", 0, 0, 0);

	display_setup_sig();
	pthपढ़ो__unblock_sigwinch();
repeat:
	delay_msecs = top->delay_secs * MSEC_PER_SEC;
	set_term_quiet_input(&save);
	/* trash वापस*/
	साफ_त्रुटि(मानक_निवेश);
	अगर (poll(&मानक_निवेश_poll, 1, 0) > 0)
		अ_लो(मानक_निवेश);

	जबतक (!करोne) अणु
		perf_top__prपूर्णांक_sym_table(top);
		/*
		 * Either समयout expired or we got an EINTR due to SIGWINCH,
		 * refresh screen in both हालs.
		 */
		चयन (poll(&मानक_निवेश_poll, 1, delay_msecs)) अणु
		हाल 0:
			जारी;
		हाल -1:
			अगर (त्रुटि_सं == EINTR)
				जारी;
			__fallthrough;
		शेष:
			c = अ_लो(मानक_निवेश);
			tcsetattr(0, TCSAFLUSH, &save);

			अगर (perf_top__handle_keypress(top, c))
				जाओ repeat;
			stop_top();
		पूर्ण
	पूर्ण

	tcsetattr(0, TCSAFLUSH, &save);
	वापस शून्य;
पूर्ण

अटल पूर्णांक hist_iter__top_callback(काष्ठा hist_entry_iter *iter,
				   काष्ठा addr_location *al, bool single,
				   व्योम *arg)
अणु
	काष्ठा perf_top *top = arg;
	काष्ठा hist_entry *he = iter->he;
	काष्ठा evsel *evsel = iter->evsel;

	अगर (perf_hpp_list.sym && single)
		perf_top__record_precise_ip(top, he, iter->sample, evsel, al->addr);

	hist__account_cycles(iter->sample->branch_stack, al, iter->sample,
		     !(top->record_opts.branch_stack & PERF_SAMPLE_BRANCH_ANY),
		     शून्य);
	वापस 0;
पूर्ण

अटल व्योम perf_event__process_sample(काष्ठा perf_tool *tool,
				       स्थिर जोड़ perf_event *event,
				       काष्ठा evsel *evsel,
				       काष्ठा perf_sample *sample,
				       काष्ठा machine *machine)
अणु
	काष्ठा perf_top *top = container_of(tool, काष्ठा perf_top, tool);
	काष्ठा addr_location al;
	पूर्णांक err;

	अगर (!machine && perf_guest) अणु
		अटल काष्ठा पूर्णांकlist *seen;

		अगर (!seen)
			seen = पूर्णांकlist__new(शून्य);

		अगर (!पूर्णांकlist__has_entry(seen, sample->pid)) अणु
			pr_err("Can't find guest [%d]'s kernel information\n",
				sample->pid);
			पूर्णांकlist__add(seen, sample->pid);
		पूर्ण
		वापस;
	पूर्ण

	अगर (!machine) अणु
		pr_err("%u unprocessable samples recorded.\r",
		       top->session->evlist->stats.nr_unprocessable_samples++);
		वापस;
	पूर्ण

	अगर (event->header.misc & PERF_RECORD_MISC_EXACT_IP)
		top->exact_samples++;

	अगर (machine__resolve(machine, &al, sample) < 0)
		वापस;

	अगर (top->stitch_lbr)
		al.thपढ़ो->lbr_stitch_enable = true;

	अगर (!machine->kptr_restrict_warned &&
	    symbol_conf.kptr_restrict &&
	    al.cpumode == PERF_RECORD_MISC_KERNEL) अणु
		अगर (!evlist__exclude_kernel(top->session->evlist)) अणु
			ui__warning(
"Kernel address maps (/proc/{kallsyms,modules}) are restricted.\n\n"
"Check /proc/sys/kernel/kptr_restrict and /proc/sys/kernel/perf_event_paranoid.\n\n"
"Kernel%s samples will not be resolved.\n",
			  al.map && map__has_symbols(al.map) ?
			  " modules" : "");
			अगर (use_browser <= 0)
				sleep(5);
		पूर्ण
		machine->kptr_restrict_warned = true;
	पूर्ण

	अगर (al.sym == शून्य && al.map != शून्य) अणु
		स्थिर अक्षर *msg = "Kernel samples will not be resolved.\n";
		/*
		 * As we करो lazy loading of symtअसल we only will know अगर the
		 * specअगरied vmlinux file is invalid when we actually have a
		 * hit in kernel space and then try to load it. So अगर we get
		 * here and there are _no_ symbols in the DSO backing the
		 * kernel map, bail out.
		 *
		 * We may never get here, क्रम instance, अगर we use -K/
		 * --hide-kernel-symbols, even अगर the user specअगरies an
		 * invalid --vmlinux ;-)
		 */
		अगर (!machine->kptr_restrict_warned && !top->vmlinux_warned &&
		    __map__is_kernel(al.map) && map__has_symbols(al.map)) अणु
			अगर (symbol_conf.vmlinux_name) अणु
				अक्षर serr[256];
				dso__म_त्रुटि_load(al.map->dso, serr, माप(serr));
				ui__warning("The %s file can't be used: %s\n%s",
					    symbol_conf.vmlinux_name, serr, msg);
			पूर्ण अन्यथा अणु
				ui__warning("A vmlinux file was not found.\n%s",
					    msg);
			पूर्ण

			अगर (use_browser <= 0)
				sleep(5);
			top->vmlinux_warned = true;
		पूर्ण
	पूर्ण

	अगर (al.sym == शून्य || !al.sym->idle) अणु
		काष्ठा hists *hists = evsel__hists(evsel);
		काष्ठा hist_entry_iter iter = अणु
			.evsel		= evsel,
			.sample 	= sample,
			.add_entry_cb 	= hist_iter__top_callback,
		पूर्ण;

		अगर (symbol_conf.cumulate_callchain)
			iter.ops = &hist_iter_cumulative;
		अन्यथा
			iter.ops = &hist_iter_normal;

		pthपढ़ो_mutex_lock(&hists->lock);

		err = hist_entry_iter__add(&iter, &al, top->max_stack, top);
		अगर (err < 0)
			pr_err("Problem incrementing symbol period, skipping event\n");

		pthपढ़ो_mutex_unlock(&hists->lock);
	पूर्ण

	addr_location__put(&al);
पूर्ण

अटल व्योम
perf_top__process_lost(काष्ठा perf_top *top, जोड़ perf_event *event,
		       काष्ठा evsel *evsel)
अणु
	top->lost += event->lost.lost;
	top->lost_total += event->lost.lost;
	evsel->evlist->stats.total_lost += event->lost.lost;
पूर्ण

अटल व्योम
perf_top__process_lost_samples(काष्ठा perf_top *top,
			       जोड़ perf_event *event,
			       काष्ठा evsel *evsel)
अणु
	top->lost += event->lost_samples.lost;
	top->lost_total += event->lost_samples.lost;
	evsel->evlist->stats.total_lost_samples += event->lost_samples.lost;
पूर्ण

अटल u64 last_बारtamp;

अटल व्योम perf_top__mmap_पढ़ो_idx(काष्ठा perf_top *top, पूर्णांक idx)
अणु
	काष्ठा record_opts *opts = &top->record_opts;
	काष्ठा evlist *evlist = top->evlist;
	काष्ठा mmap *md;
	जोड़ perf_event *event;

	md = opts->overग_लिखो ? &evlist->overग_लिखो_mmap[idx] : &evlist->mmap[idx];
	अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
		वापस;

	जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
		पूर्णांक ret;

		ret = evlist__parse_sample_बारtamp(evlist, event, &last_बारtamp);
		अगर (ret && ret != -1)
			अवरोध;

		ret = ordered_events__queue(top->qe.in, event, last_बारtamp, 0);
		अगर (ret)
			अवरोध;

		perf_mmap__consume(&md->core);

		अगर (top->qe.rotate) अणु
			pthपढ़ो_mutex_lock(&top->qe.mutex);
			top->qe.rotate = false;
			pthपढ़ो_cond_संकेत(&top->qe.cond);
			pthपढ़ो_mutex_unlock(&top->qe.mutex);
		पूर्ण
	पूर्ण

	perf_mmap__पढ़ो_करोne(&md->core);
पूर्ण

अटल व्योम perf_top__mmap_पढ़ो(काष्ठा perf_top *top)
अणु
	bool overग_लिखो = top->record_opts.overग_लिखो;
	काष्ठा evlist *evlist = top->evlist;
	पूर्णांक i;

	अगर (overग_लिखो)
		evlist__toggle_bkw_mmap(evlist, BKW_MMAP_DATA_PENDING);

	क्रम (i = 0; i < top->evlist->core.nr_mmaps; i++)
		perf_top__mmap_पढ़ो_idx(top, i);

	अगर (overग_लिखो) अणु
		evlist__toggle_bkw_mmap(evlist, BKW_MMAP_EMPTY);
		evlist__toggle_bkw_mmap(evlist, BKW_MMAP_RUNNING);
	पूर्ण
पूर्ण

/*
 * Check per-event overग_लिखो term.
 * perf top should support consistent term क्रम all events.
 * - All events करोn't have per-event term
 *   E.g. "cpu/cpu-cycles/,cpu/instructions/"
 *   Nothing change, वापस 0.
 * - All events have same per-event term
 *   E.g. "cpu/cpu-cycles,no-overग_लिखो/,cpu/inकाष्ठाions,no-overग_लिखो/
 *   Using the per-event setting to replace the opts->overग_लिखो अगर
 *   they are dअगरferent, then वापस 0.
 * - Events have dअगरferent per-event term
 *   E.g. "cpu/cpu-cycles,overwrite/,cpu/instructions,no-overwrite/"
 *   Return -1
 * - Some of the event set per-event term, but some not.
 *   E.g. "cpu/cpu-cycles/,cpu/instructions,no-overwrite/"
 *   Return -1
 */
अटल पूर्णांक perf_top__overग_लिखो_check(काष्ठा perf_top *top)
अणु
	काष्ठा record_opts *opts = &top->record_opts;
	काष्ठा evlist *evlist = top->evlist;
	काष्ठा evsel_config_term *term;
	काष्ठा list_head *config_terms;
	काष्ठा evsel *evsel;
	पूर्णांक set, overग_लिखो = -1;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		set = -1;
		config_terms = &evsel->config_terms;
		list_क्रम_each_entry(term, config_terms, list) अणु
			अगर (term->type == EVSEL__CONFIG_TERM_OVERWRITE)
				set = term->val.overग_लिखो ? 1 : 0;
		पूर्ण

		/* no term क्रम current and previous event (likely) */
		अगर ((overग_लिखो < 0) && (set < 0))
			जारी;

		/* has term क्रम both current and previous event, compare */
		अगर ((overग_लिखो >= 0) && (set >= 0) && (overग_लिखो != set))
			वापस -1;

		/* no term क्रम current event but has term क्रम previous one */
		अगर ((overग_लिखो >= 0) && (set < 0))
			वापस -1;

		/* has term क्रम current event */
		अगर ((overग_लिखो < 0) && (set >= 0)) अणु
			/* अगर it's first event, set overग_लिखो */
			अगर (evsel == evlist__first(evlist))
				overग_लिखो = set;
			अन्यथा
				वापस -1;
		पूर्ण
	पूर्ण

	अगर ((overग_लिखो >= 0) && (opts->overग_लिखो != overग_लिखो))
		opts->overग_लिखो = overग_लिखो;

	वापस 0;
पूर्ण

अटल पूर्णांक perf_top_overग_लिखो_fallback(काष्ठा perf_top *top,
				       काष्ठा evsel *evsel)
अणु
	काष्ठा record_opts *opts = &top->record_opts;
	काष्ठा evlist *evlist = top->evlist;
	काष्ठा evsel *counter;

	अगर (!opts->overग_लिखो)
		वापस 0;

	/* only fall back when first event fails */
	अगर (evsel != evlist__first(evlist))
		वापस 0;

	evlist__क्रम_each_entry(evlist, counter)
		counter->core.attr.ग_लिखो_backward = false;
	opts->overग_लिखो = false;
	pr_debug2("fall back to non-overwrite mode\n");
	वापस 1;
पूर्ण

अटल पूर्णांक perf_top__start_counters(काष्ठा perf_top *top)
अणु
	अक्षर msg[बफ_मान];
	काष्ठा evsel *counter;
	काष्ठा evlist *evlist = top->evlist;
	काष्ठा record_opts *opts = &top->record_opts;

	अगर (perf_top__overग_लिखो_check(top)) अणु
		ui__error("perf top only support consistent per-event "
			  "overwrite setting for all events\n");
		जाओ out_err;
	पूर्ण

	evlist__config(evlist, opts, &callchain_param);

	evlist__क्रम_each_entry(evlist, counter) अणु
try_again:
		अगर (evsel__खोलो(counter, top->evlist->core.cpus,
				     top->evlist->core.thपढ़ोs) < 0) अणु

			/*
			 * Specially handle overग_लिखो fall back.
			 * Because perf top is the only tool which has
			 * overग_लिखो mode by शेष, support
			 * both overग_लिखो and non-overग_लिखो mode, and
			 * require consistent mode क्रम all events.
			 *
			 * May move it to generic code with more tools
			 * have similar attribute.
			 */
			अगर (perf_missing_features.ग_लिखो_backward &&
			    perf_top_overग_लिखो_fallback(top, counter))
				जाओ try_again;

			अगर (evsel__fallback(counter, त्रुटि_सं, msg, माप(msg))) अणु
				अगर (verbose > 0)
					ui__warning("%s\n", msg);
				जाओ try_again;
			पूर्ण

			evsel__खोलो_म_त्रुटि(counter, &opts->target, त्रुटि_सं, msg, माप(msg));
			ui__error("%s\n", msg);
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (evlist__mmap(evlist, opts->mmap_pages) < 0) अणु
		ui__error("Failed to mmap with %d (%s)\n",
			    त्रुटि_सं, str_error_r(त्रुटि_सं, msg, माप(msg)));
		जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	वापस -1;
पूर्ण

अटल पूर्णांक callchain_param__setup_sample_type(काष्ठा callchain_param *callchain)
अणु
	अगर (callchain->mode != CHAIN_NONE) अणु
		अगर (callchain_रेजिस्टर_param(callchain) < 0) अणु
			ui__error("Can't register callchain params.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ordered_events *rotate_queues(काष्ठा perf_top *top)
अणु
	काष्ठा ordered_events *in = top->qe.in;

	अगर (top->qe.in == &top->qe.data[1])
		top->qe.in = &top->qe.data[0];
	अन्यथा
		top->qe.in = &top->qe.data[1];

	वापस in;
पूर्ण

अटल व्योम *process_thपढ़ो(व्योम *arg)
अणु
	काष्ठा perf_top *top = arg;

	जबतक (!करोne) अणु
		काष्ठा ordered_events *out, *in = top->qe.in;

		अगर (!in->nr_events) अणु
			usleep(100);
			जारी;
		पूर्ण

		out = rotate_queues(top);

		pthपढ़ो_mutex_lock(&top->qe.mutex);
		top->qe.rotate = true;
		pthपढ़ो_cond_रुको(&top->qe.cond, &top->qe.mutex);
		pthपढ़ो_mutex_unlock(&top->qe.mutex);

		अगर (ordered_events__flush(out, OE_FLUSH__TOP))
			pr_err("failed to process events\n");
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Allow only 'top->delay_secs' seconds behind samples.
 */
अटल पूर्णांक should_drop(काष्ठा ordered_event *qevent, काष्ठा perf_top *top)
अणु
	जोड़ perf_event *event = qevent->event;
	u64 delay_बारtamp;

	अगर (event->header.type != PERF_RECORD_SAMPLE)
		वापस false;

	delay_बारtamp = qevent->बारtamp + top->delay_secs * NSEC_PER_SEC;
	वापस delay_बारtamp < last_बारtamp;
पूर्ण

अटल पूर्णांक deliver_event(काष्ठा ordered_events *qe,
			 काष्ठा ordered_event *qevent)
अणु
	काष्ठा perf_top *top = qe->data;
	काष्ठा evlist *evlist = top->evlist;
	काष्ठा perf_session *session = top->session;
	जोड़ perf_event *event = qevent->event;
	काष्ठा perf_sample sample;
	काष्ठा evsel *evsel;
	काष्ठा machine *machine;
	पूर्णांक ret = -1;

	अगर (should_drop(qevent, top)) अणु
		top->drop++;
		top->drop_total++;
		वापस 0;
	पूर्ण

	ret = evlist__parse_sample(evlist, event, &sample);
	अगर (ret) अणु
		pr_err("Can't parse sample, err = %d\n", ret);
		जाओ next_event;
	पूर्ण

	evsel = evlist__id2evsel(session->evlist, sample.id);
	निश्चित(evsel != शून्य);

	अगर (event->header.type == PERF_RECORD_SAMPLE) अणु
		अगर (evचयन__discard(&top->evचयन, evsel))
			वापस 0;
		++top->samples;
	पूर्ण

	चयन (sample.cpumode) अणु
	हाल PERF_RECORD_MISC_USER:
		++top->us_samples;
		अगर (top->hide_user_symbols)
			जाओ next_event;
		machine = &session->machines.host;
		अवरोध;
	हाल PERF_RECORD_MISC_KERNEL:
		++top->kernel_samples;
		अगर (top->hide_kernel_symbols)
			जाओ next_event;
		machine = &session->machines.host;
		अवरोध;
	हाल PERF_RECORD_MISC_GUEST_KERNEL:
		++top->guest_kernel_samples;
		machine = perf_session__find_machine(session,
						     sample.pid);
		अवरोध;
	हाल PERF_RECORD_MISC_GUEST_USER:
		++top->guest_us_samples;
		/*
		 * TODO: we करोn't process guest user from host side
		 * except simple counting.
		 */
		जाओ next_event;
	शेष:
		अगर (event->header.type == PERF_RECORD_SAMPLE)
			जाओ next_event;
		machine = &session->machines.host;
		अवरोध;
	पूर्ण

	अगर (event->header.type == PERF_RECORD_SAMPLE) अणु
		perf_event__process_sample(&top->tool, event, evsel,
					   &sample, machine);
	पूर्ण अन्यथा अगर (event->header.type == PERF_RECORD_LOST) अणु
		perf_top__process_lost(top, event, evsel);
	पूर्ण अन्यथा अगर (event->header.type == PERF_RECORD_LOST_SAMPLES) अणु
		perf_top__process_lost_samples(top, event, evsel);
	पूर्ण अन्यथा अगर (event->header.type < PERF_RECORD_MAX) अणु
		events_stats__inc(&session->evlist->stats, event->header.type);
		machine__process_event(machine, event, &sample);
	पूर्ण अन्यथा
		++session->evlist->stats.nr_unknown_events;

	ret = 0;
next_event:
	वापस ret;
पूर्ण

अटल व्योम init_process_thपढ़ो(काष्ठा perf_top *top)
अणु
	ordered_events__init(&top->qe.data[0], deliver_event, top);
	ordered_events__init(&top->qe.data[1], deliver_event, top);
	ordered_events__set_copy_on_queue(&top->qe.data[0], true);
	ordered_events__set_copy_on_queue(&top->qe.data[1], true);
	top->qe.in = &top->qe.data[0];
	pthपढ़ो_mutex_init(&top->qe.mutex, शून्य);
	pthपढ़ो_cond_init(&top->qe.cond, शून्य);
पूर्ण

अटल पूर्णांक __cmd_top(काष्ठा perf_top *top)
अणु
	काष्ठा record_opts *opts = &top->record_opts;
	pthपढ़ो_t thपढ़ो, thपढ़ो_process;
	पूर्णांक ret;

	अगर (!top->annotation_opts.objdump_path) अणु
		ret = perf_env__lookup_objdump(&top->session->header.env,
					       &top->annotation_opts.objdump_path);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = callchain_param__setup_sample_type(&callchain_param);
	अगर (ret)
		वापस ret;

	अगर (perf_session__रेजिस्टर_idle_thपढ़ो(top->session) < 0)
		वापस ret;

	अगर (top->nr_thपढ़ोs_synthesize > 1)
		perf_set_multithपढ़ोed();

	init_process_thपढ़ो(top);

	अगर (opts->record_namespaces)
		top->tool.namespace_events = true;
	अगर (opts->record_cgroup) अणु
#अगर_घोषित HAVE_खाता_HANDLE
		top->tool.cgroup_events = true;
#अन्यथा
		pr_err("cgroup tracking is not supported.\n");
		वापस -1;
#पूर्ण_अगर
	पूर्ण

	ret = perf_event__synthesize_bpf_events(top->session, perf_event__process,
						&top->session->machines.host,
						&top->record_opts);
	अगर (ret < 0)
		pr_debug("Couldn't synthesize BPF events: Pre-existing BPF programs won't have symbols resolved.\n");

	ret = perf_event__synthesize_cgroups(&top->tool, perf_event__process,
					     &top->session->machines.host);
	अगर (ret < 0)
		pr_debug("Couldn't synthesize cgroup events.\n");

	machine__syntheमाप_प्रकारhपढ़ोs(&top->session->machines.host, &opts->target,
				    top->evlist->core.thपढ़ोs, false,
				    top->nr_thपढ़ोs_synthesize);

	अगर (top->nr_thपढ़ोs_synthesize > 1)
		perf_set_singlethपढ़ोed();

	अगर (perf_hpp_list.socket) अणु
		ret = perf_env__पढ़ो_cpu_topology_map(&perf_env);
		अगर (ret < 0) अणु
			अक्षर errbuf[बफ_मान];
			स्थिर अक्षर *err = str_error_r(-ret, errbuf, माप(errbuf));

			ui__error("Could not read the CPU topology map: %s\n", err);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = perf_top__start_counters(top);
	अगर (ret)
		वापस ret;

	top->session->evlist = top->evlist;
	perf_session__set_id_hdr_size(top->session);

	/*
	 * When perf is starting the traced process, all the events (apart from
	 * group members) have enable_on_exec=1 set, so करोn't spoil it by
	 * prematurely enabling them.
	 *
	 * XXX 'top' still doesn't start workloads like record, trace, but should,
	 * so leave the check here.
	 */
        अगर (!target__none(&opts->target))
		evlist__enable(top->evlist);

	ret = -1;
	अगर (pthपढ़ो_create(&thपढ़ो_process, शून्य, process_thपढ़ो, top)) अणु
		ui__error("Could not create process thread.\n");
		वापस ret;
	पूर्ण

	अगर (pthपढ़ो_create(&thपढ़ो, शून्य, (use_browser > 0 ? display_thपढ़ो_tui :
							    display_thपढ़ो), top)) अणु
		ui__error("Could not create display thread.\n");
		जाओ out_join_thपढ़ो;
	पूर्ण

	अगर (top->realसमय_prio) अणु
		काष्ठा sched_param param;

		param.sched_priority = top->realसमय_prio;
		अगर (sched_setscheduler(0, SCHED_FIFO, &param)) अणु
			ui__error("Could not set realtime priority.\n");
			जाओ out_join;
		पूर्ण
	पूर्ण

	/* Wait क्रम a minimal set of events beक्रमe starting the snapshot */
	evlist__poll(top->evlist, 100);

	perf_top__mmap_पढ़ो(top);

	जबतक (!करोne) अणु
		u64 hits = top->samples;

		perf_top__mmap_पढ़ो(top);

		अगर (opts->overग_लिखो || (hits == top->samples))
			ret = evlist__poll(top->evlist, 100);

		अगर (resize) अणु
			perf_top__resize(top);
			resize = 0;
		पूर्ण
	पूर्ण

	ret = 0;
out_join:
	pthपढ़ो_join(thपढ़ो, शून्य);
out_join_thपढ़ो:
	pthपढ़ो_cond_संकेत(&top->qe.cond);
	pthपढ़ो_join(thपढ़ो_process, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक
callchain_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset)
अणु
	symbol_conf.use_callchain = true;
	वापस record_callchain_opt(opt, arg, unset);
पूर्ण

अटल पूर्णांक
parse_callchain_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset)
अणु
	काष्ठा callchain_param *callchain = opt->value;

	callchain->enabled = !unset;
	callchain->record_mode = CALLCHAIN_FP;

	/*
	 * --no-call-graph
	 */
	अगर (unset) अणु
		symbol_conf.use_callchain = false;
		callchain->record_mode = CALLCHAIN_NONE;
		वापस 0;
	पूर्ण

	वापस parse_callchain_top_opt(arg);
पूर्ण

अटल पूर्णांक perf_top_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb __maybe_unused)
अणु
	अगर (!म_भेद(var, "top.call-graph")) अणु
		var = "call-graph.record-mode";
		वापस perf_शेष_config(var, value, cb);
	पूर्ण
	अगर (!म_भेद(var, "top.children")) अणु
		symbol_conf.cumulate_callchain = perf_config_bool(var, value);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
parse_percent_limit(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg,
		    पूर्णांक unset __maybe_unused)
अणु
	काष्ठा perf_top *top = opt->value;

	top->min_percent = strtof(arg, शून्य);
	वापस 0;
पूर्ण

स्थिर अक्षर top_callchain_help[] = CALLCHAIN_RECORD_HELP CALLCHAIN_REPORT_HELP
	"\n\t\t\t\tDefault: fp,graph,0.5,caller,function";

पूर्णांक cmd_top(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर errbuf[बफ_मान];
	काष्ठा perf_top top = अणु
		.count_filter	     = 5,
		.delay_secs	     = 2,
		.record_opts = अणु
			.mmap_pages	= अच_पूर्णांक_उच्च,
			.user_freq	= अच_पूर्णांक_उच्च,
			.user_पूर्णांकerval	= ULदीर्घ_उच्च,
			.freq		= 4000, /* 4 KHz */
			.target		= अणु
				.uses_mmap   = true,
			पूर्ण,
			/*
			 * FIXME: This will lose PERF_RECORD_MMAP and other metadata
			 * when we छोड़ो, fix that and reenable. Probably using a
			 * separate evlist with a dummy event, i.e. a non-overग_लिखो
			 * ring buffer just क्रम metadata events, जबतक PERF_RECORD_SAMPLE
			 * stays in overग_लिखो mode. -acme
			 * */
			.overग_लिखो	= 0,
			.sample_समय	= true,
			.sample_समय_set = true,
		पूर्ण,
		.max_stack	     = sysctl__max_stack(),
		.annotation_opts     = annotation__शेष_options,
		.nr_thपढ़ोs_synthesize = अच_पूर्णांक_उच्च,
	पूर्ण;
	काष्ठा record_opts *opts = &top.record_opts;
	काष्ठा target *target = &opts->target;
	स्थिर काष्ठा option options[] = अणु
	OPT_CALLBACK('e', "event", &top.evlist, "event",
		     "event selector. use 'perf list' to list available events",
		     parse_events_option),
	OPT_U64('c', "count", &opts->user_पूर्णांकerval, "event period to sample"),
	OPT_STRING('p', "pid", &target->pid, "pid",
		    "profile events on existing process id"),
	OPT_STRING('t', "tid", &target->tid, "tid",
		    "profile events on existing thread id"),
	OPT_BOOLEAN('a', "all-cpus", &target->प्रणाली_wide,
			    "system-wide collection from all CPUs"),
	OPT_STRING('C', "cpu", &target->cpu_list, "cpu",
		    "list of cpus to monitor"),
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_BOOLEAN(0, "ignore-vmlinux", &symbol_conf.ignore_vmlinux,
		    "don't load vmlinux even if found"),
	OPT_STRING(0, "kallsyms", &symbol_conf.kallsyms_name,
		   "file", "kallsyms pathname"),
	OPT_BOOLEAN('K', "hide_kernel_symbols", &top.hide_kernel_symbols,
		    "hide kernel symbols"),
	OPT_CALLBACK('m', "mmap-pages", &opts->mmap_pages, "pages",
		     "number of mmap data pages", evlist__parse_mmap_pages),
	OPT_INTEGER('r', "realtime", &top.realसमय_prio,
		    "collect data with this RT SCHED_FIFO priority"),
	OPT_INTEGER('d', "delay", &top.delay_secs,
		    "number of seconds to delay between refreshes"),
	OPT_BOOLEAN('D', "dump-symtab", &top.dump_symtab,
			    "dump the symbol table used for profiling"),
	OPT_INTEGER('f', "count-filter", &top.count_filter,
		    "only display functions with more events than this"),
	OPT_BOOLEAN(0, "group", &opts->group,
			    "put the counters into a counter group"),
	OPT_BOOLEAN('i', "no-inherit", &opts->no_inherit,
		    "child tasks do not inherit counters"),
	OPT_STRING(0, "sym-annotate", &top.sym_filter, "symbol name",
		    "symbol to annotate"),
	OPT_BOOLEAN('z', "zero", &top.zero, "zero history across updates"),
	OPT_CALLBACK('F', "freq", &top.record_opts, "freq or 'max'",
		     "profile at this frequency",
		      record__parse_freq),
	OPT_INTEGER('E', "entries", &top.prपूर्णांक_entries,
		    "display this many functions"),
	OPT_BOOLEAN('U', "hide_user_symbols", &top.hide_user_symbols,
		    "hide user symbols"),
	OPT_BOOLEAN(0, "tui", &top.use_tui, "Use the TUI interface"),
	OPT_BOOLEAN(0, "stdio", &top.use_stdio, "Use the stdio interface"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show counter open errors, etc)"),
	OPT_STRING('s', "sort", &sort_order, "key[,key2...]",
		   "sort by key(s): pid, comm, dso, symbol, parent, cpu, srcline, ..."
		   " Please refer the man page for the complete list."),
	OPT_STRING(0, "fields", &field_order, "key[,keys...]",
		   "output field(s): overhead, period, sample plus all of sort keys"),
	OPT_BOOLEAN('n', "show-nr-samples", &symbol_conf.show_nr_samples,
		    "Show a column with the number of samples"),
	OPT_CALLBACK_NOOPT('g', शून्य, &callchain_param,
			   शून्य, "enables call-graph recording and display",
			   &callchain_opt),
	OPT_CALLBACK(0, "call-graph", &callchain_param,
		     "record_mode[,record_size],print_type,threshold[,print_limit],order,sort_key[,branch]",
		     top_callchain_help, &parse_callchain_opt),
	OPT_BOOLEAN(0, "children", &symbol_conf.cumulate_callchain,
		    "Accumulate callchains of children and show total overhead as well"),
	OPT_INTEGER(0, "max-stack", &top.max_stack,
		    "Set the maximum stack depth when parsing the callchain. "
		    "Default: kernel.perf_event_max_stack or " __stringअगरy(PERF_MAX_STACK_DEPTH)),
	OPT_CALLBACK(0, "ignore-callees", शून्य, "regex",
		   "ignore callees of these functions in call graphs",
		   report_parse_ignore_callees_opt),
	OPT_BOOLEAN(0, "show-total-period", &symbol_conf.show_total_period,
		    "Show a column with the sum of periods"),
	OPT_STRING(0, "dsos", &symbol_conf.dso_list_str, "dso[,dso...]",
		   "only consider symbols in these dsos"),
	OPT_STRING(0, "comms", &symbol_conf.comm_list_str, "comm[,comm...]",
		   "only consider symbols in these comms"),
	OPT_STRING(0, "symbols", &symbol_conf.sym_list_str, "symbol[,symbol...]",
		   "only consider these symbols"),
	OPT_BOOLEAN(0, "source", &top.annotation_opts.annotate_src,
		    "Interleave source code with assembly code (default)"),
	OPT_BOOLEAN(0, "asm-raw", &top.annotation_opts.show_यंत्र_raw,
		    "Display raw encoding of assembly instructions (default)"),
	OPT_BOOLEAN(0, "demangle-kernel", &symbol_conf.demangle_kernel,
		    "Enable kernel symbol demangling"),
	OPT_BOOLEAN(0, "no-bpf-event", &top.record_opts.no_bpf_event, "do not record bpf events"),
	OPT_STRING(0, "objdump", &top.annotation_opts.objdump_path, "path",
		    "objdump binary to use for disassembly and annotations"),
	OPT_STRING('M', "disassembler-style", &top.annotation_opts.disassembler_style, "disassembler style",
		   "Specify disassembler style (e.g. -M intel for intel syntax)"),
	OPT_STRING(0, "prefix", &top.annotation_opts.prefix, "prefix",
		    "Add prefix to source file path names in programs (with --prefix-strip)"),
	OPT_STRING(0, "prefix-strip", &top.annotation_opts.prefix_strip, "N",
		    "Strip first N entries of source file path name in programs (with --prefix)"),
	OPT_STRING('u', "uid", &target->uid_str, "user", "user to profile"),
	OPT_CALLBACK(0, "percent-limit", &top, "percent",
		     "Don't show entries under that percent", parse_percent_limit),
	OPT_CALLBACK(0, "percentage", शून्य, "relative|absolute",
		     "How to display percentage of filtered entries", parse_filter_percentage),
	OPT_STRING('w', "column-widths", &symbol_conf.col_width_list_str,
		   "width[,width...]",
		   "don't try to adjust column width, use these fixed values"),
	OPT_UINTEGER(0, "proc-map-timeout", &proc_map_समयout,
			"per thread proc mmap processing timeout in ms"),
	OPT_CALLBACK_NOOPT('b', "branch-any", &opts->branch_stack,
		     "branch any", "sample any taken branches",
		     parse_branch_stack),
	OPT_CALLBACK('j', "branch-filter", &opts->branch_stack,
		     "branch filter mask", "branch stack filter modes",
		     parse_branch_stack),
	OPT_BOOLEAN(0, "raw-trace", &symbol_conf.raw_trace,
		    "Show raw trace event output (do not use print fmt or plugins)"),
	OPT_BOOLEAN(0, "hierarchy", &symbol_conf.report_hierarchy,
		    "Show entries in a hierarchy"),
	OPT_BOOLEAN(0, "overwrite", &top.record_opts.overग_लिखो,
		    "Use a backward ring buffer, default: no"),
	OPT_BOOLEAN(0, "force", &symbol_conf.क्रमce, "don't complain, do it"),
	OPT_UINTEGER(0, "num-thread-synthesize", &top.nr_thपढ़ोs_synthesize,
			"number of thread to run event synthesize"),
	OPT_BOOLEAN(0, "namespaces", &opts->record_namespaces,
		    "Record namespaces events"),
	OPT_BOOLEAN(0, "all-cgroups", &opts->record_cgroup,
		    "Record cgroup events"),
	OPT_INTEGER(0, "group-sort-idx", &symbol_conf.group_sort_idx,
		    "Sort the output by the event at the index n in group. "
		    "If n is invalid, sort by the first event. "
		    "WARNING: should be used on grouped events."),
	OPT_BOOLEAN(0, "stitch-lbr", &top.stitch_lbr,
		    "Enable LBR callgraph stitching approach"),
#अगर_घोषित HAVE_LIBPFM
	OPT_CALLBACK(0, "pfm-events", &top.evlist, "event",
		"libpfm4 event selector. use 'perf list' to list available events",
		parse_libpfm_events_option),
#पूर्ण_अगर
	OPTS_EVSWITCH(&top.evचयन),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर top_usage[] = अणु
		"perf top [<options>]",
		शून्य
	पूर्ण;
	पूर्णांक status = hists__init();

	अगर (status < 0)
		वापस status;

	top.annotation_opts.min_pcnt = 5;
	top.annotation_opts.context  = 4;

	top.evlist = evlist__new();
	अगर (top.evlist == शून्य)
		वापस -ENOMEM;

	status = perf_config(perf_top_config, &top);
	अगर (status)
		वापस status;
	/*
	 * Since the per arch annotation init routine may need the cpuid, पढ़ो
	 * it here, since we are not getting this from the perf.data header.
	 */
	status = perf_env__पढ़ो_cpuid(&perf_env);
	अगर (status) अणु
		/*
		 * Some arches करो not provide a get_cpuid(), so just use pr_debug, otherwise
		 * warn the user explicitly.
		 */
		eम_लिखो(status == ENOSYS ? 1 : 0, verbose,
			"Couldn't read the cpuid for this machine: %s\n",
			str_error_r(त्रुटि_सं, errbuf, माप(errbuf)));
	पूर्ण
	top.evlist->env = &perf_env;

	argc = parse_options(argc, argv, options, top_usage, 0);
	अगर (argc)
		usage_with_options(top_usage, options);

	अगर (annotate_check_args(&top.annotation_opts) < 0)
		जाओ out_delete_evlist;

	अगर (!top.evlist->core.nr_entries &&
	    evlist__add_शेष(top.evlist) < 0) अणु
		pr_err("Not enough memory for event selector list\n");
		जाओ out_delete_evlist;
	पूर्ण

	status = evचयन__init(&top.evचयन, top.evlist, मानक_त्रुटि);
	अगर (status)
		जाओ out_delete_evlist;

	अगर (symbol_conf.report_hierarchy) अणु
		/* disable incompatible options */
		symbol_conf.event_group = false;
		symbol_conf.cumulate_callchain = false;

		अगर (field_order) अणु
			pr_err("Error: --hierarchy and --fields options cannot be used together\n");
			parse_options_usage(top_usage, options, "fields", 0);
			parse_options_usage(शून्य, options, "hierarchy", 0);
			जाओ out_delete_evlist;
		पूर्ण
	पूर्ण

	अगर (top.stitch_lbr && !(callchain_param.record_mode == CALLCHAIN_LBR)) अणु
		pr_err("Error: --stitch-lbr must be used with --call-graph lbr\n");
		जाओ out_delete_evlist;
	पूर्ण

	अगर (opts->branch_stack && callchain_param.enabled)
		symbol_conf.show_branchflag_count = true;

	sort__mode = SORT_MODE__TOP;
	/* display thपढ़ो wants entries to be collapsed in a dअगरferent tree */
	perf_hpp_list.need_collapse = 1;

	अगर (top.use_stdio)
		use_browser = 0;
	अन्यथा अगर (top.use_tui)
		use_browser = 1;

	setup_browser(false);

	अगर (setup_sorting(top.evlist) < 0) अणु
		अगर (sort_order)
			parse_options_usage(top_usage, options, "s", 1);
		अगर (field_order)
			parse_options_usage(sort_order ? शून्य : top_usage,
					    options, "fields", 0);
		जाओ out_delete_evlist;
	पूर्ण

	status = target__validate(target);
	अगर (status) अणु
		target__म_त्रुटि(target, status, errbuf, बफ_मान);
		ui__warning("%s\n", errbuf);
	पूर्ण

	status = target__parse_uid(target);
	अगर (status) अणु
		पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;

		target__म_त्रुटि(target, status, errbuf, बफ_मान);
		ui__error("%s\n", errbuf);

		status = -saved_त्रुटि_सं;
		जाओ out_delete_evlist;
	पूर्ण

	अगर (target__none(target))
		target->प्रणाली_wide = true;

	अगर (evlist__create_maps(top.evlist, target) < 0) अणु
		ui__error("Couldn't create thread/CPU maps: %s\n",
			  त्रुटि_सं == ENOENT ? "No such process" : str_error_r(त्रुटि_सं, errbuf, माप(errbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	अगर (top.delay_secs < 1)
		top.delay_secs = 1;

	अगर (record_opts__config(opts)) अणु
		status = -EINVAL;
		जाओ out_delete_evlist;
	पूर्ण

	top.sym_evsel = evlist__first(top.evlist);

	अगर (!callchain_param.enabled) अणु
		symbol_conf.cumulate_callchain = false;
		perf_hpp__cancel_cumulate();
	पूर्ण

	अगर (symbol_conf.cumulate_callchain && !callchain_param.order_set)
		callchain_param.order = ORDER_CALLER;

	status = symbol__annotation_init();
	अगर (status < 0)
		जाओ out_delete_evlist;

	annotation_config__init(&top.annotation_opts);

	symbol_conf.try_vmlinux_path = (symbol_conf.vmlinux_name == शून्य);
	status = symbol__init(शून्य);
	अगर (status < 0)
		जाओ out_delete_evlist;

	sort__setup_elide(मानक_निकास);

	get_term_dimensions(&top.winsize);
	अगर (top.prपूर्णांक_entries == 0) अणु
		perf_top__update_prपूर्णांक_entries(&top);
		संकेत(SIGWINCH, winch_sig);
	पूर्ण

	top.session = perf_session__new(शून्य, false, शून्य);
	अगर (IS_ERR(top.session)) अणु
		status = PTR_ERR(top.session);
		जाओ out_delete_evlist;
	पूर्ण

#अगर_घोषित HAVE_LIBBPF_SUPPORT
	अगर (!top.record_opts.no_bpf_event) अणु
		top.sb_evlist = evlist__new();

		अगर (top.sb_evlist == शून्य) अणु
			pr_err("Couldn't create side band evlist.\n.");
			जाओ out_delete_evlist;
		पूर्ण

		अगर (evlist__add_bpf_sb_event(top.sb_evlist, &perf_env)) अणु
			pr_err("Couldn't ask for PERF_RECORD_BPF_EVENT side band events.\n.");
			जाओ out_delete_evlist;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (evlist__start_sb_thपढ़ो(top.sb_evlist, target)) अणु
		pr_debug("Couldn't start the BPF side band thread:\nBPF programs starting from now on won't be annotatable\n");
		opts->no_bpf_event = true;
	पूर्ण

	status = __cmd_top(&top);

	अगर (!opts->no_bpf_event)
		evlist__stop_sb_thपढ़ो(top.sb_evlist);

out_delete_evlist:
	evlist__delete(top.evlist);
	perf_session__delete(top.session);

	वापस status;
पूर्ण
