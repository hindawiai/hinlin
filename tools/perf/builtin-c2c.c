<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is reग_लिखो of original c2c tool पूर्णांकroduced in here:
 *   http://lwn.net/Articles/588866/
 *
 * The original tool was changed to fit in current perf state.
 *
 * Original authors:
 *   Don Zickus <dzickus@redhat.com>
 *   Dick Fowles <fowles@inreach.com>
 *   Joe Mario <jmario@redhat.com>
 */
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/compiler.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/zभाग.स>
#समावेश <यंत्र/bug.h>
#समावेश <sys/param.h>
#समावेश "debug.h"
#समावेश "builtin.h"
#समावेश <perf/cpumap.h>
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "map_symbol.h"
#समावेश "mem-events.h"
#समावेश "session.h"
#समावेश "hist.h"
#समावेश "sort.h"
#समावेश "tool.h"
#समावेश "cacheline.h"
#समावेश "data.h"
#समावेश "event.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "ui/browsers/hists.h"
#समावेश "thread.h"
#समावेश "mem2node.h"
#समावेश "symbol.h"
#समावेश "ui/ui.h"
#समावेश "ui/progress.h"
#समावेश "../perf.h"

काष्ठा c2c_hists अणु
	काष्ठा hists		hists;
	काष्ठा perf_hpp_list	list;
	काष्ठा c2c_stats	stats;
पूर्ण;

काष्ठा compute_stats अणु
	काष्ठा stats		 lcl_hiपंचांग;
	काष्ठा stats		 rmt_hiपंचांग;
	काष्ठा stats		 load;
पूर्ण;

काष्ठा c2c_hist_entry अणु
	काष्ठा c2c_hists	*hists;
	काष्ठा c2c_stats	 stats;
	अचिन्हित दीर्घ		*cpuset;
	अचिन्हित दीर्घ		*nodeset;
	काष्ठा c2c_stats	*node_stats;
	अचिन्हित पूर्णांक		 cacheline_idx;

	काष्ठा compute_stats	 cstats;

	अचिन्हित दीर्घ		 paddr;
	अचिन्हित दीर्घ		 paddr_cnt;
	bool			 paddr_zero;
	अक्षर			*nodestr;

	/*
	 * must be at the end,
	 * because of its callchain dynamic entry
	 */
	काष्ठा hist_entry	he;
पूर्ण;

अटल अक्षर स्थिर *coalesce_शेष = "iaddr";

काष्ठा perf_c2c अणु
	काष्ठा perf_tool	tool;
	काष्ठा c2c_hists	hists;
	काष्ठा mem2node		mem2node;

	अचिन्हित दीर्घ		**nodes;
	पूर्णांक			 nodes_cnt;
	पूर्णांक			 cpus_cnt;
	पूर्णांक			*cpu2node;
	पूर्णांक			 node_info;

	bool			 show_src;
	bool			 show_all;
	bool			 use_stdio;
	bool			 stats_only;
	bool			 symbol_full;
	bool			 stitch_lbr;

	/* Shared cache line stats */
	काष्ठा c2c_stats	shared_clines_stats;
	पूर्णांक			shared_clines;

	पूर्णांक			 display;

	स्थिर अक्षर		*coalesce;
	अक्षर			*cl_sort;
	अक्षर			*cl_resort;
	अक्षर			*cl_output;
पूर्ण;

क्रमागत अणु
	DISPLAY_LCL,
	DISPLAY_RMT,
	DISPLAY_TOT,
	DISPLAY_MAX,
पूर्ण;

अटल स्थिर अक्षर *display_str[DISPLAY_MAX] = अणु
	[DISPLAY_LCL] = "Local",
	[DISPLAY_RMT] = "Remote",
	[DISPLAY_TOT] = "Total",
पूर्ण;

अटल स्थिर काष्ठा option c2c_options[] = अणु
	OPT_INCR('v', "verbose", &verbose, "be more verbose (show counter open errors, etc)"),
	OPT_END()
पूर्ण;

अटल काष्ठा perf_c2c c2c;

अटल व्योम *c2c_he_zalloc(माप_प्रकार size)
अणु
	काष्ठा c2c_hist_entry *c2c_he;

	c2c_he = zalloc(size + माप(*c2c_he));
	अगर (!c2c_he)
		वापस शून्य;

	c2c_he->cpuset = biपंचांगap_alloc(c2c.cpus_cnt);
	अगर (!c2c_he->cpuset)
		वापस शून्य;

	c2c_he->nodeset = biपंचांगap_alloc(c2c.nodes_cnt);
	अगर (!c2c_he->nodeset)
		वापस शून्य;

	c2c_he->node_stats = zalloc(c2c.nodes_cnt * माप(*c2c_he->node_stats));
	अगर (!c2c_he->node_stats)
		वापस शून्य;

	init_stats(&c2c_he->cstats.lcl_hiपंचांग);
	init_stats(&c2c_he->cstats.rmt_hiपंचांग);
	init_stats(&c2c_he->cstats.load);

	वापस &c2c_he->he;
पूर्ण

अटल व्योम c2c_he_मुक्त(व्योम *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	अगर (c2c_he->hists) अणु
		hists__delete_entries(&c2c_he->hists->hists);
		मुक्त(c2c_he->hists);
	पूर्ण

	मुक्त(c2c_he->cpuset);
	मुक्त(c2c_he->nodeset);
	मुक्त(c2c_he->nodestr);
	मुक्त(c2c_he->node_stats);
	मुक्त(c2c_he);
पूर्ण

अटल काष्ठा hist_entry_ops c2c_entry_ops = अणु
	.new	= c2c_he_zalloc,
	.मुक्त	= c2c_he_मुक्त,
पूर्ण;

अटल पूर्णांक c2c_hists__init(काष्ठा c2c_hists *hists,
			   स्थिर अक्षर *sort,
			   पूर्णांक nr_header_lines);

अटल काष्ठा c2c_hists*
he__get_c2c_hists(काष्ठा hist_entry *he,
		  स्थिर अक्षर *sort,
		  पूर्णांक nr_header_lines)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	काष्ठा c2c_hists *hists;
	पूर्णांक ret;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	अगर (c2c_he->hists)
		वापस c2c_he->hists;

	hists = c2c_he->hists = zalloc(माप(*hists));
	अगर (!hists)
		वापस शून्य;

	ret = c2c_hists__init(hists, sort, nr_header_lines);
	अगर (ret) अणु
		मुक्त(hists);
		वापस शून्य;
	पूर्ण

	वापस hists;
पूर्ण

अटल व्योम c2c_he__set_cpu(काष्ठा c2c_hist_entry *c2c_he,
			    काष्ठा perf_sample *sample)
अणु
	अगर (WARN_ONCE(sample->cpu == (अचिन्हित पूर्णांक) -1,
		      "WARNING: no sample cpu value"))
		वापस;

	set_bit(sample->cpu, c2c_he->cpuset);
पूर्ण

अटल व्योम c2c_he__set_node(काष्ठा c2c_hist_entry *c2c_he,
			     काष्ठा perf_sample *sample)
अणु
	पूर्णांक node;

	अगर (!sample->phys_addr) अणु
		c2c_he->paddr_zero = true;
		वापस;
	पूर्ण

	node = mem2node__node(&c2c.mem2node, sample->phys_addr);
	अगर (WARN_ONCE(node < 0, "WARNING: failed to find node\n"))
		वापस;

	set_bit(node, c2c_he->nodeset);

	अगर (c2c_he->paddr != sample->phys_addr) अणु
		c2c_he->paddr_cnt++;
		c2c_he->paddr = sample->phys_addr;
	पूर्ण
पूर्ण

अटल व्योम compute_stats(काष्ठा c2c_hist_entry *c2c_he,
			  काष्ठा c2c_stats *stats,
			  u64 weight)
अणु
	काष्ठा compute_stats *cstats = &c2c_he->cstats;

	अगर (stats->rmt_hiपंचांग)
		update_stats(&cstats->rmt_hiपंचांग, weight);
	अन्यथा अगर (stats->lcl_hiपंचांग)
		update_stats(&cstats->lcl_hiपंचांग, weight);
	अन्यथा अगर (stats->load)
		update_stats(&cstats->load, weight);
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool __maybe_unused,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	काष्ठा c2c_hists *c2c_hists = &c2c.hists;
	काष्ठा c2c_hist_entry *c2c_he;
	काष्ठा c2c_stats stats = अणु .nr_entries = 0, पूर्ण;
	काष्ठा hist_entry *he;
	काष्ठा addr_location al;
	काष्ठा mem_info *mi, *mi_dup;
	पूर्णांक ret;

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		pr_debug("problem processing %d event, skipping it.\n",
			 event->header.type);
		वापस -1;
	पूर्ण

	अगर (c2c.stitch_lbr)
		al.thपढ़ो->lbr_stitch_enable = true;

	ret = sample__resolve_callchain(sample, &callchain_cursor, शून्य,
					evsel, &al, sysctl_perf_event_max_stack);
	अगर (ret)
		जाओ out;

	mi = sample__resolve_mem(sample, &al);
	अगर (mi == शून्य)
		वापस -ENOMEM;

	/*
	 * The mi object is released in hists__add_entry_ops,
	 * अगर it माला_लो sorted out पूर्णांकo existing data, so we need
	 * to take the copy now.
	 */
	mi_dup = mem_info__get(mi);

	c2c_decode_stats(&stats, mi);

	he = hists__add_entry_ops(&c2c_hists->hists, &c2c_entry_ops,
				  &al, शून्य, शून्य, mi,
				  sample, true);
	अगर (he == शून्य)
		जाओ मुक्त_mi;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	c2c_add_stats(&c2c_he->stats, &stats);
	c2c_add_stats(&c2c_hists->stats, &stats);

	c2c_he__set_cpu(c2c_he, sample);
	c2c_he__set_node(c2c_he, sample);

	hists__inc_nr_samples(&c2c_hists->hists, he->filtered);
	ret = hist_entry__append_callchain(he, sample);

	अगर (!ret) अणु
		/*
		 * There's alपढ़ोy been warning about missing
		 * sample's cpu value. Let's account all to
		 * node 0 in this हाल, without any further
		 * warning.
		 *
		 * Doing node stats only क्रम single callchain data.
		 */
		पूर्णांक cpu = sample->cpu == (अचिन्हित पूर्णांक) -1 ? 0 : sample->cpu;
		पूर्णांक node = c2c.cpu2node[cpu];

		mi = mi_dup;

		c2c_hists = he__get_c2c_hists(he, c2c.cl_sort, 2);
		अगर (!c2c_hists)
			जाओ मुक्त_mi;

		he = hists__add_entry_ops(&c2c_hists->hists, &c2c_entry_ops,
					  &al, शून्य, शून्य, mi,
					  sample, true);
		अगर (he == शून्य)
			जाओ मुक्त_mi;

		c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
		c2c_add_stats(&c2c_he->stats, &stats);
		c2c_add_stats(&c2c_hists->stats, &stats);
		c2c_add_stats(&c2c_he->node_stats[node], &stats);

		compute_stats(c2c_he, &stats, sample->weight);

		c2c_he__set_cpu(c2c_he, sample);
		c2c_he__set_node(c2c_he, sample);

		hists__inc_nr_samples(&c2c_hists->hists, he->filtered);
		ret = hist_entry__append_callchain(he, sample);
	पूर्ण

out:
	addr_location__put(&al);
	वापस ret;

मुक्त_mi:
	mem_info__put(mi_dup);
	mem_info__put(mi);
	ret = -ENOMEM;
	जाओ out;
पूर्ण

अटल काष्ठा perf_c2c c2c = अणु
	.tool = अणु
		.sample		= process_sample_event,
		.mmap		= perf_event__process_mmap,
		.mmap2		= perf_event__process_mmap2,
		.comm		= perf_event__process_comm,
		.निकास		= perf_event__process_निकास,
		.विभाजन		= perf_event__process_विभाजन,
		.lost		= perf_event__process_lost,
		.attr		= perf_event__process_attr,
		.auxtrace_info  = perf_event__process_auxtrace_info,
		.auxtrace       = perf_event__process_auxtrace,
		.auxtrace_error = perf_event__process_auxtrace_error,
		.ordered_events	= true,
		.ordering_requires_बारtamps = true,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर c2c_usage[] = अणु
	"perf c2c {record|report}",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर __usage_report[] = अणु
	"perf c2c report",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर *report_c2c_usage = __usage_report;

#घोषणा C2C_HEADER_MAX 2

काष्ठा c2c_header अणु
	काष्ठा अणु
		स्थिर अक्षर *text;
		पूर्णांक	    span;
	पूर्ण line[C2C_HEADER_MAX];
पूर्ण;

काष्ठा c2c_dimension अणु
	काष्ठा c2c_header	 header;
	स्थिर अक्षर		*name;
	पूर्णांक			 width;
	काष्ठा sort_entry	*se;

	पूर्णांक64_t (*cmp)(काष्ठा perf_hpp_fmt *fmt,
		       काष्ठा hist_entry *, काष्ठा hist_entry *);
	पूर्णांक   (*entry)(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		       काष्ठा hist_entry *he);
	पूर्णांक   (*color)(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		       काष्ठा hist_entry *he);
पूर्ण;

काष्ठा c2c_fmt अणु
	काष्ठा perf_hpp_fmt	 fmt;
	काष्ठा c2c_dimension	*dim;
पूर्ण;

#घोषणा SYMBOL_WIDTH 30

अटल काष्ठा c2c_dimension dim_symbol;
अटल काष्ठा c2c_dimension dim_srcline;

अटल पूर्णांक symbol_width(काष्ठा hists *hists, काष्ठा sort_entry *se)
अणु
	पूर्णांक width = hists__col_len(hists, se->se_width_idx);

	अगर (!c2c.symbol_full)
		width = MIN(width, SYMBOL_WIDTH);

	वापस width;
पूर्ण

अटल पूर्णांक c2c_width(काष्ठा perf_hpp_fmt *fmt,
		     काष्ठा perf_hpp *hpp __maybe_unused,
		     काष्ठा hists *hists)
अणु
	काष्ठा c2c_fmt *c2c_fmt;
	काष्ठा c2c_dimension *dim;

	c2c_fmt = container_of(fmt, काष्ठा c2c_fmt, fmt);
	dim = c2c_fmt->dim;

	अगर (dim == &dim_symbol || dim == &dim_srcline)
		वापस symbol_width(hists, dim->se);

	वापस dim->se ? hists__col_len(hists, dim->se->se_width_idx) :
			 c2c_fmt->dim->width;
पूर्ण

अटल पूर्णांक c2c_header(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		      काष्ठा hists *hists, पूर्णांक line, पूर्णांक *span)
अणु
	काष्ठा perf_hpp_list *hpp_list = hists->hpp_list;
	काष्ठा c2c_fmt *c2c_fmt;
	काष्ठा c2c_dimension *dim;
	स्थिर अक्षर *text = शून्य;
	पूर्णांक width = c2c_width(fmt, hpp, hists);

	c2c_fmt = container_of(fmt, काष्ठा c2c_fmt, fmt);
	dim = c2c_fmt->dim;

	अगर (dim->se) अणु
		text = dim->header.line[line].text;
		/* Use the last line from sort_entry अगर not defined. */
		अगर (!text && (line == hpp_list->nr_header_lines - 1))
			text = dim->se->se_header;
	पूर्ण अन्यथा अणु
		text = dim->header.line[line].text;

		अगर (*span) अणु
			(*span)--;
			वापस 0;
		पूर्ण अन्यथा अणु
			*span = dim->header.line[line].span;
		पूर्ण
	पूर्ण

	अगर (text == शून्य)
		text = "";

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, text);
पूर्ण

#घोषणा HEX_STR(__s, __v)				\
(अणु							\
	scnम_लिखो(__s, माप(__s), "0x%" PRIx64, __v);	\
	__s;						\
पूर्ण)

अटल पूर्णांक64_t
dcacheline_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	       काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस sort__dcacheline_cmp(left, right);
पूर्ण

अटल पूर्णांक dcacheline_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			    काष्ठा hist_entry *he)
अणु
	uपूर्णांक64_t addr = 0;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अक्षर buf[20];

	अगर (he->mem_info)
		addr = cl_address(he->mem_info->daddr.addr);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, HEX_STR(buf, addr));
पूर्ण

अटल पूर्णांक
dcacheline_node_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		      काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	अगर (WARN_ON_ONCE(!c2c_he->nodestr))
		वापस 0;

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, c2c_he->nodestr);
पूर्ण

अटल पूर्णांक
dcacheline_node_count(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		      काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*lu", width, c2c_he->paddr_cnt);
पूर्ण

अटल पूर्णांक offset_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			काष्ठा hist_entry *he)
अणु
	uपूर्णांक64_t addr = 0;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अक्षर buf[20];

	अगर (he->mem_info)
		addr = cl_offset(he->mem_info->daddr.al_addr);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, HEX_STR(buf, addr));
पूर्ण

अटल पूर्णांक64_t
offset_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	   काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	uपूर्णांक64_t l = 0, r = 0;

	अगर (left->mem_info)
		l = cl_offset(left->mem_info->daddr.addr);
	अगर (right->mem_info)
		r = cl_offset(right->mem_info->daddr.addr);

	वापस (पूर्णांक64_t)(r - l);
पूर्ण

अटल पूर्णांक
iaddr_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	    काष्ठा hist_entry *he)
अणु
	uपूर्णांक64_t addr = 0;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अक्षर buf[20];

	अगर (he->mem_info)
		addr = he->mem_info->iaddr.addr;

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, HEX_STR(buf, addr));
पूर्ण

अटल पूर्णांक64_t
iaddr_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	  काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस sort__iaddr_cmp(left, right);
पूर्ण

अटल पूर्णांक
tot_hiपंचांग_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	       काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अचिन्हित पूर्णांक tot_hiपंचांग;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	tot_hiपंचांग = c2c_he->stats.lcl_hiपंचांग + c2c_he->stats.rmt_hiपंचांग;

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*u", width, tot_hiपंचांग);
पूर्ण

अटल पूर्णांक64_t
tot_hiपंचांग_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	     काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा c2c_hist_entry *c2c_left;
	काष्ठा c2c_hist_entry *c2c_right;
	uपूर्णांक64_t tot_hiपंचांग_left;
	uपूर्णांक64_t tot_hiपंचांग_right;

	c2c_left  = container_of(left, काष्ठा c2c_hist_entry, he);
	c2c_right = container_of(right, काष्ठा c2c_hist_entry, he);

	tot_hiपंचांग_left  = c2c_left->stats.lcl_hiपंचांग + c2c_left->stats.rmt_hiपंचांग;
	tot_hiपंचांग_right = c2c_right->stats.lcl_hiपंचांग + c2c_right->stats.rmt_hiपंचांग;

	वापस tot_hiपंचांग_left - tot_hiपंचांग_right;
पूर्ण

#घोषणा STAT_FN_ENTRY(__f)					\
अटल पूर्णांक							\
__f ## _entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,	\
	      काष्ठा hist_entry *he)				\
अणु								\
	काष्ठा c2c_hist_entry *c2c_he;				\
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);		\
								\
	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);	\
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*u", width,	\
			 c2c_he->stats.__f);			\
पूर्ण

#घोषणा STAT_FN_CMP(__f)						\
अटल पूर्णांक64_t								\
__f ## _cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,			\
	    काष्ठा hist_entry *left, काष्ठा hist_entry *right)		\
अणु									\
	काष्ठा c2c_hist_entry *c2c_left, *c2c_right;			\
									\
	c2c_left  = container_of(left, काष्ठा c2c_hist_entry, he);	\
	c2c_right = container_of(right, काष्ठा c2c_hist_entry, he);	\
	वापस (uपूर्णांक64_t) c2c_left->stats.__f -				\
	       (uपूर्णांक64_t) c2c_right->stats.__f;				\
पूर्ण

#घोषणा STAT_FN(__f)		\
	STAT_FN_ENTRY(__f)	\
	STAT_FN_CMP(__f)

STAT_FN(rmt_hiपंचांग)
STAT_FN(lcl_hiपंचांग)
STAT_FN(store)
STAT_FN(st_l1hit)
STAT_FN(st_l1miss)
STAT_FN(ld_fbhit)
STAT_FN(ld_l1hit)
STAT_FN(ld_l2hit)
STAT_FN(ld_llchit)
STAT_FN(rmt_hit)

अटल uपूर्णांक64_t total_records(काष्ठा c2c_stats *stats)
अणु
	uपूर्णांक64_t lclmiss, ldcnt, total;

	lclmiss  = stats->lcl_dram +
		   stats->rmt_dram +
		   stats->rmt_hiपंचांग +
		   stats->rmt_hit;

	ldcnt    = lclmiss +
		   stats->ld_fbhit +
		   stats->ld_l1hit +
		   stats->ld_l2hit +
		   stats->ld_llchit +
		   stats->lcl_hiपंचांग;

	total    = ldcnt +
		   stats->st_l1hit +
		   stats->st_l1miss;

	वापस total;
पूर्ण

अटल पूर्णांक
tot_recs_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	uपूर्णांक64_t tot_recs;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	tot_recs = total_records(&c2c_he->stats);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*" PRIu64, width, tot_recs);
पूर्ण

अटल पूर्णांक64_t
tot_recs_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	     काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा c2c_hist_entry *c2c_left;
	काष्ठा c2c_hist_entry *c2c_right;
	uपूर्णांक64_t tot_recs_left;
	uपूर्णांक64_t tot_recs_right;

	c2c_left  = container_of(left, काष्ठा c2c_hist_entry, he);
	c2c_right = container_of(right, काष्ठा c2c_hist_entry, he);

	tot_recs_left  = total_records(&c2c_left->stats);
	tot_recs_right = total_records(&c2c_right->stats);

	वापस tot_recs_left - tot_recs_right;
पूर्ण

अटल uपूर्णांक64_t total_loads(काष्ठा c2c_stats *stats)
अणु
	uपूर्णांक64_t lclmiss, ldcnt;

	lclmiss  = stats->lcl_dram +
		   stats->rmt_dram +
		   stats->rmt_hiपंचांग +
		   stats->rmt_hit;

	ldcnt    = lclmiss +
		   stats->ld_fbhit +
		   stats->ld_l1hit +
		   stats->ld_l2hit +
		   stats->ld_llchit +
		   stats->lcl_hiपंचांग;

	वापस ldcnt;
पूर्ण

अटल पूर्णांक
tot_loads_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	uपूर्णांक64_t tot_recs;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	tot_recs = total_loads(&c2c_he->stats);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*" PRIu64, width, tot_recs);
पूर्ण

अटल पूर्णांक64_t
tot_loads_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	      काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा c2c_hist_entry *c2c_left;
	काष्ठा c2c_hist_entry *c2c_right;
	uपूर्णांक64_t tot_recs_left;
	uपूर्णांक64_t tot_recs_right;

	c2c_left  = container_of(left, काष्ठा c2c_hist_entry, he);
	c2c_right = container_of(right, काष्ठा c2c_hist_entry, he);

	tot_recs_left  = total_loads(&c2c_left->stats);
	tot_recs_right = total_loads(&c2c_right->stats);

	वापस tot_recs_left - tot_recs_right;
पूर्ण

प्रकार द्विगुन (get_percent_cb)(काष्ठा c2c_hist_entry *);

अटल पूर्णांक
percent_color(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	      काष्ठा hist_entry *he, get_percent_cb get_percent)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	द्विगुन per;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	per = get_percent(c2c_he);

#अगर_घोषित HAVE_SLANG_SUPPORT
	अगर (use_browser)
		वापस __hpp__slsmg_color_म_लिखो(hpp, "%*.2f%%", width - 1, per);
#पूर्ण_अगर
	वापस hpp_color_scnम_लिखो(hpp, "%*.2f%%", width - 1, per);
पूर्ण

अटल द्विगुन percent_hiपंचांग(काष्ठा c2c_hist_entry *c2c_he)
अणु
	काष्ठा c2c_hists *hists;
	काष्ठा c2c_stats *stats;
	काष्ठा c2c_stats *total;
	पूर्णांक tot = 0, st = 0;
	द्विगुन p;

	hists = container_of(c2c_he->he.hists, काष्ठा c2c_hists, hists);
	stats = &c2c_he->stats;
	total = &hists->stats;

	चयन (c2c.display) अणु
	हाल DISPLAY_RMT:
		st  = stats->rmt_hiपंचांग;
		tot = total->rmt_hiपंचांग;
		अवरोध;
	हाल DISPLAY_LCL:
		st  = stats->lcl_hiपंचांग;
		tot = total->lcl_hiपंचांग;
		अवरोध;
	हाल DISPLAY_TOT:
		st  = stats->tot_hiपंचांग;
		tot = total->tot_hiपंचांग;
	शेष:
		अवरोध;
	पूर्ण

	p = tot ? (द्विगुन) st / tot : 0;

	वापस 100 * p;
पूर्ण

#घोषणा PERC_STR(__s, __v)				\
(अणु							\
	scnम_लिखो(__s, माप(__s), "%.2F%%", __v);	\
	__s;						\
पूर्ण)

अटल पूर्णांक
percent_hiपंचांग_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		   काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अक्षर buf[10];
	द्विगुन per;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	per = percent_hiपंचांग(c2c_he);
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, PERC_STR(buf, per));
पूर्ण

अटल पूर्णांक
percent_hiपंचांग_color(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		   काष्ठा hist_entry *he)
अणु
	वापस percent_color(fmt, hpp, he, percent_hiपंचांग);
पूर्ण

अटल पूर्णांक64_t
percent_hiपंचांग_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
		 काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा c2c_hist_entry *c2c_left;
	काष्ठा c2c_hist_entry *c2c_right;
	द्विगुन per_left;
	द्विगुन per_right;

	c2c_left  = container_of(left, काष्ठा c2c_hist_entry, he);
	c2c_right = container_of(right, काष्ठा c2c_hist_entry, he);

	per_left  = percent_hiपंचांग(c2c_left);
	per_right = percent_hiपंचांग(c2c_right);

	वापस per_left - per_right;
पूर्ण

अटल काष्ठा c2c_stats *he_stats(काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	वापस &c2c_he->stats;
पूर्ण

अटल काष्ठा c2c_stats *total_stats(काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hists *hists;

	hists = container_of(he->hists, काष्ठा c2c_hists, hists);
	वापस &hists->stats;
पूर्ण

अटल द्विगुन percent(u32 st, u32 tot)
अणु
	वापस tot ? 100. * (द्विगुन) st / (द्विगुन) tot : 0;
पूर्ण

#घोषणा PERCENT(__h, __f) percent(he_stats(__h)->__f, total_stats(__h)->__f)

#घोषणा PERCENT_FN(__f)								\
अटल द्विगुन percent_ ## __f(काष्ठा c2c_hist_entry *c2c_he)			\
अणु										\
	काष्ठा c2c_hists *hists;						\
										\
	hists = container_of(c2c_he->he.hists, काष्ठा c2c_hists, hists);	\
	वापस percent(c2c_he->stats.__f, hists->stats.__f);			\
पूर्ण

PERCENT_FN(rmt_hiपंचांग)
PERCENT_FN(lcl_hiपंचांग)
PERCENT_FN(st_l1hit)
PERCENT_FN(st_l1miss)

अटल पूर्णांक
percent_rmt_hiपंचांग_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		       काष्ठा hist_entry *he)
अणु
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	द्विगुन per = PERCENT(he, rmt_hiपंचांग);
	अक्षर buf[10];

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, PERC_STR(buf, per));
पूर्ण

अटल पूर्णांक
percent_rmt_hiपंचांग_color(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		       काष्ठा hist_entry *he)
अणु
	वापस percent_color(fmt, hpp, he, percent_rmt_hiपंचांग);
पूर्ण

अटल पूर्णांक64_t
percent_rmt_hiपंचांग_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
		     काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	द्विगुन per_left;
	द्विगुन per_right;

	per_left  = PERCENT(left, lcl_hiपंचांग);
	per_right = PERCENT(right, lcl_hiपंचांग);

	वापस per_left - per_right;
पूर्ण

अटल पूर्णांक
percent_lcl_hiपंचांग_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		       काष्ठा hist_entry *he)
अणु
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	द्विगुन per = PERCENT(he, lcl_hiपंचांग);
	अक्षर buf[10];

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, PERC_STR(buf, per));
पूर्ण

अटल पूर्णांक
percent_lcl_hiपंचांग_color(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		       काष्ठा hist_entry *he)
अणु
	वापस percent_color(fmt, hpp, he, percent_lcl_hiपंचांग);
पूर्ण

अटल पूर्णांक64_t
percent_lcl_hiपंचांग_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
		     काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	द्विगुन per_left;
	द्विगुन per_right;

	per_left  = PERCENT(left, lcl_hiपंचांग);
	per_right = PERCENT(right, lcl_hiपंचांग);

	वापस per_left - per_right;
पूर्ण

अटल पूर्णांक
percent_stores_l1hit_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			   काष्ठा hist_entry *he)
अणु
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	द्विगुन per = PERCENT(he, st_l1hit);
	अक्षर buf[10];

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, PERC_STR(buf, per));
पूर्ण

अटल पूर्णांक
percent_stores_l1hit_color(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			   काष्ठा hist_entry *he)
अणु
	वापस percent_color(fmt, hpp, he, percent_st_l1hit);
पूर्ण

अटल पूर्णांक64_t
percent_stores_l1hit_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	द्विगुन per_left;
	द्विगुन per_right;

	per_left  = PERCENT(left, st_l1hit);
	per_right = PERCENT(right, st_l1hit);

	वापस per_left - per_right;
पूर्ण

अटल पूर्णांक
percent_stores_l1miss_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			   काष्ठा hist_entry *he)
अणु
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	द्विगुन per = PERCENT(he, st_l1miss);
	अक्षर buf[10];

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, PERC_STR(buf, per));
पूर्ण

अटल पूर्णांक
percent_stores_l1miss_color(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			    काष्ठा hist_entry *he)
अणु
	वापस percent_color(fmt, hpp, he, percent_st_l1miss);
पूर्ण

अटल पूर्णांक64_t
percent_stores_l1miss_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			  काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	द्विगुन per_left;
	द्विगुन per_right;

	per_left  = PERCENT(left, st_l1miss);
	per_right = PERCENT(right, st_l1miss);

	वापस per_left - per_right;
पूर्ण

STAT_FN(lcl_dram)
STAT_FN(rmt_dram)

अटल पूर्णांक
pid_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	  काष्ठा hist_entry *he)
अणु
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*d", width, he->thपढ़ो->pid_);
पूर्ण

अटल पूर्णांक64_t
pid_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस left->thपढ़ो->pid_ - right->thपढ़ो->pid_;
पूर्ण

अटल पूर्णांक64_t
empty_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
	  काष्ठा hist_entry *left __maybe_unused,
	  काष्ठा hist_entry *right __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक display_metrics(काष्ठा perf_hpp *hpp, u32 val, u32 sum)
अणु
	पूर्णांक ret;

	अगर (sum != 0)
		ret = scnम_लिखो(hpp->buf, hpp->size, "%5.1f%% ",
				percent(val, sum));
	अन्यथा
		ret = scnम_लिखो(hpp->buf, hpp->size, "%6s ", "n/a");

	वापस ret;
पूर्ण

अटल पूर्णांक
node_entry(काष्ठा perf_hpp_fmt *fmt __maybe_unused, काष्ठा perf_hpp *hpp,
	   काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	bool first = true;
	पूर्णांक node;
	पूर्णांक ret = 0;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);

	क्रम (node = 0; node < c2c.nodes_cnt; node++) अणु
		DECLARE_BITMAP(set, c2c.cpus_cnt);

		biपंचांगap_zero(set, c2c.cpus_cnt);
		biपंचांगap_and(set, c2c_he->cpuset, c2c.nodes[node], c2c.cpus_cnt);

		अगर (!biपंचांगap_weight(set, c2c.cpus_cnt)) अणु
			अगर (c2c.node_info == 1) अणु
				ret = scnम_लिखो(hpp->buf, hpp->size, "%21s", " ");
				advance_hpp(hpp, ret);
			पूर्ण
			जारी;
		पूर्ण

		अगर (!first) अणु
			ret = scnम_लिखो(hpp->buf, hpp->size, " ");
			advance_hpp(hpp, ret);
		पूर्ण

		चयन (c2c.node_info) अणु
		हाल 0:
			ret = scnम_लिखो(hpp->buf, hpp->size, "%2d", node);
			advance_hpp(hpp, ret);
			अवरोध;
		हाल 1:
		अणु
			पूर्णांक num = biपंचांगap_weight(set, c2c.cpus_cnt);
			काष्ठा c2c_stats *stats = &c2c_he->node_stats[node];

			ret = scnम_लिखो(hpp->buf, hpp->size, "%2d{%2d ", node, num);
			advance_hpp(hpp, ret);

			चयन (c2c.display) अणु
			हाल DISPLAY_RMT:
				ret = display_metrics(hpp, stats->rmt_hiपंचांग,
						      c2c_he->stats.rmt_hiपंचांग);
				अवरोध;
			हाल DISPLAY_LCL:
				ret = display_metrics(hpp, stats->lcl_hiपंचांग,
						      c2c_he->stats.lcl_hiपंचांग);
				अवरोध;
			हाल DISPLAY_TOT:
				ret = display_metrics(hpp, stats->tot_hiपंचांग,
						      c2c_he->stats.tot_hiपंचांग);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			advance_hpp(hpp, ret);

			अगर (c2c_he->stats.store > 0) अणु
				ret = scnम_लिखो(hpp->buf, hpp->size, "%5.1f%%}",
						percent(stats->store, c2c_he->stats.store));
			पूर्ण अन्यथा अणु
				ret = scnम_लिखो(hpp->buf, hpp->size, "%6s}", "n/a");
			पूर्ण

			advance_hpp(hpp, ret);
			अवरोध;
		पूर्ण
		हाल 2:
			ret = scnम_लिखो(hpp->buf, hpp->size, "%2d{", node);
			advance_hpp(hpp, ret);

			ret = biपंचांगap_scnम_लिखो(set, c2c.cpus_cnt, hpp->buf, hpp->size);
			advance_hpp(hpp, ret);

			ret = scnम_लिखो(hpp->buf, hpp->size, "}");
			advance_hpp(hpp, ret);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		first = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mean_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	   काष्ठा hist_entry *he, द्विगुन mean)
अणु
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अक्षर buf[10];

	scnम_लिखो(buf, 10, "%6.0f", mean);
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, buf);
पूर्ण

#घोषणा MEAN_ENTRY(__func, __val)						\
अटल पूर्णांक									\
__func(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)	\
अणु										\
	काष्ठा c2c_hist_entry *c2c_he;						\
	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);			\
	वापस mean_entry(fmt, hpp, he, avg_stats(&c2c_he->cstats.__val));	\
पूर्ण

MEAN_ENTRY(mean_rmt_entry,  rmt_hiपंचांग);
MEAN_ENTRY(mean_lcl_entry,  lcl_hiपंचांग);
MEAN_ENTRY(mean_load_entry, load);

अटल पूर्णांक
cpucnt_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	     काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अक्षर buf[10];

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);

	scnम_लिखो(buf, 10, "%d", biपंचांगap_weight(c2c_he->cpuset, c2c.cpus_cnt));
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, buf);
पूर्ण

अटल पूर्णांक
cl_idx_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	     काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);
	अक्षर buf[10];

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);

	scnम_लिखो(buf, 10, "%u", c2c_he->cacheline_idx);
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, buf);
पूर्ण

अटल पूर्णांक
cl_idx_empty_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		   काष्ठा hist_entry *he)
अणु
	पूर्णांक width = c2c_width(fmt, hpp, he->hists);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, "");
पूर्ण

#घोषणा HEADER_LOW(__h)			\
	अणु				\
		.line[1] = अणु		\
			.text = __h,	\
		पूर्ण,			\
	पूर्ण

#घोषणा HEADER_BOTH(__h0, __h1)		\
	अणु				\
		.line[0] = अणु		\
			.text = __h0,	\
		पूर्ण,			\
		.line[1] = अणु		\
			.text = __h1,	\
		पूर्ण,			\
	पूर्ण

#घोषणा HEADER_SPAN(__h0, __h1, __s)	\
	अणु				\
		.line[0] = अणु		\
			.text = __h0,	\
			.span = __s,	\
		पूर्ण,			\
		.line[1] = अणु		\
			.text = __h1,	\
		पूर्ण,			\
	पूर्ण

#घोषणा HEADER_SPAN_LOW(__h)		\
	अणु				\
		.line[1] = अणु		\
			.text = __h,	\
		पूर्ण,			\
	पूर्ण

अटल काष्ठा c2c_dimension dim_dcacheline = अणु
	.header		= HEADER_SPAN("--- Cacheline ----", "Address", 2),
	.name		= "dcacheline",
	.cmp		= dcacheline_cmp,
	.entry		= dcacheline_entry,
	.width		= 18,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dcacheline_node = अणु
	.header		= HEADER_LOW("Node"),
	.name		= "dcacheline_node",
	.cmp		= empty_cmp,
	.entry		= dcacheline_node_entry,
	.width		= 4,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dcacheline_count = अणु
	.header		= HEADER_LOW("PA cnt"),
	.name		= "dcacheline_count",
	.cmp		= empty_cmp,
	.entry		= dcacheline_node_count,
	.width		= 6,
पूर्ण;

अटल काष्ठा c2c_header header_offset_tui = HEADER_SPAN("-----", "Off", 2);

अटल काष्ठा c2c_dimension dim_offset = अणु
	.header		= HEADER_SPAN("--- Data address -", "Offset", 2),
	.name		= "offset",
	.cmp		= offset_cmp,
	.entry		= offset_entry,
	.width		= 18,
पूर्ण;

अटल काष्ठा c2c_dimension dim_offset_node = अणु
	.header		= HEADER_LOW("Node"),
	.name		= "offset_node",
	.cmp		= empty_cmp,
	.entry		= dcacheline_node_entry,
	.width		= 4,
पूर्ण;

अटल काष्ठा c2c_dimension dim_iaddr = अणु
	.header		= HEADER_LOW("Code address"),
	.name		= "iaddr",
	.cmp		= iaddr_cmp,
	.entry		= iaddr_entry,
	.width		= 18,
पूर्ण;

अटल काष्ठा c2c_dimension dim_tot_hiपंचांग = अणु
	.header		= HEADER_SPAN("------- Load Hitm -------", "Total", 2),
	.name		= "tot_hitm",
	.cmp		= tot_hiपंचांग_cmp,
	.entry		= tot_hiपंचांग_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_lcl_hiपंचांग = अणु
	.header		= HEADER_SPAN_LOW("LclHitm"),
	.name		= "lcl_hitm",
	.cmp		= lcl_hiपंचांग_cmp,
	.entry		= lcl_hiपंचांग_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_rmt_hiपंचांग = अणु
	.header		= HEADER_SPAN_LOW("RmtHitm"),
	.name		= "rmt_hitm",
	.cmp		= rmt_hiपंचांग_cmp,
	.entry		= rmt_hiपंचांग_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_cl_rmt_hiपंचांग = अणु
	.header		= HEADER_SPAN("----- HITM -----", "Rmt", 1),
	.name		= "cl_rmt_hitm",
	.cmp		= rmt_hiपंचांग_cmp,
	.entry		= rmt_hiपंचांग_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_cl_lcl_hiपंचांग = अणु
	.header		= HEADER_SPAN_LOW("Lcl"),
	.name		= "cl_lcl_hitm",
	.cmp		= lcl_hiपंचांग_cmp,
	.entry		= lcl_hiपंचांग_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_tot_stores = अणु
	.header		= HEADER_BOTH("Total", "Stores"),
	.name		= "tot_stores",
	.cmp		= store_cmp,
	.entry		= store_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_stores_l1hit = अणु
	.header		= HEADER_SPAN("---- Stores ----", "L1Hit", 1),
	.name		= "stores_l1hit",
	.cmp		= st_l1hit_cmp,
	.entry		= st_l1hit_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_stores_l1miss = अणु
	.header		= HEADER_SPAN_LOW("L1Miss"),
	.name		= "stores_l1miss",
	.cmp		= st_l1miss_cmp,
	.entry		= st_l1miss_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_cl_stores_l1hit = अणु
	.header		= HEADER_SPAN("-- Store Refs --", "L1 Hit", 1),
	.name		= "cl_stores_l1hit",
	.cmp		= st_l1hit_cmp,
	.entry		= st_l1hit_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_cl_stores_l1miss = अणु
	.header		= HEADER_SPAN_LOW("L1 Miss"),
	.name		= "cl_stores_l1miss",
	.cmp		= st_l1miss_cmp,
	.entry		= st_l1miss_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_ld_fbhit = अणु
	.header		= HEADER_SPAN("----- Core Load Hit -----", "FB", 2),
	.name		= "ld_fbhit",
	.cmp		= ld_fbhit_cmp,
	.entry		= ld_fbhit_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_ld_l1hit = अणु
	.header		= HEADER_SPAN_LOW("L1"),
	.name		= "ld_l1hit",
	.cmp		= ld_l1hit_cmp,
	.entry		= ld_l1hit_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_ld_l2hit = अणु
	.header		= HEADER_SPAN_LOW("L2"),
	.name		= "ld_l2hit",
	.cmp		= ld_l2hit_cmp,
	.entry		= ld_l2hit_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_ld_llchit = अणु
	.header		= HEADER_SPAN("- LLC Load Hit --", "LclHit", 1),
	.name		= "ld_lclhit",
	.cmp		= ld_llchit_cmp,
	.entry		= ld_llchit_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_ld_rmthit = अणु
	.header		= HEADER_SPAN("- RMT Load Hit --", "RmtHit", 1),
	.name		= "ld_rmthit",
	.cmp		= rmt_hit_cmp,
	.entry		= rmt_hit_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_tot_recs = अणु
	.header		= HEADER_BOTH("Total", "records"),
	.name		= "tot_recs",
	.cmp		= tot_recs_cmp,
	.entry		= tot_recs_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_tot_loads = अणु
	.header		= HEADER_BOTH("Total", "Loads"),
	.name		= "tot_loads",
	.cmp		= tot_loads_cmp,
	.entry		= tot_loads_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_header percent_hiपंचांग_header[] = अणु
	[DISPLAY_LCL] = HEADER_BOTH("Lcl", "Hitm"),
	[DISPLAY_RMT] = HEADER_BOTH("Rmt", "Hitm"),
	[DISPLAY_TOT] = HEADER_BOTH("Tot", "Hitm"),
पूर्ण;

अटल काष्ठा c2c_dimension dim_percent_hiपंचांग = अणु
	.name		= "percent_hitm",
	.cmp		= percent_hiपंचांग_cmp,
	.entry		= percent_hiपंचांग_entry,
	.color		= percent_hiपंचांग_color,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_percent_rmt_hiपंचांग = अणु
	.header		= HEADER_SPAN("----- HITM -----", "RmtHitm", 1),
	.name		= "percent_rmt_hitm",
	.cmp		= percent_rmt_hiपंचांग_cmp,
	.entry		= percent_rmt_hiपंचांग_entry,
	.color		= percent_rmt_hiपंचांग_color,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_percent_lcl_hiपंचांग = अणु
	.header		= HEADER_SPAN_LOW("LclHitm"),
	.name		= "percent_lcl_hitm",
	.cmp		= percent_lcl_hiपंचांग_cmp,
	.entry		= percent_lcl_hiपंचांग_entry,
	.color		= percent_lcl_hiपंचांग_color,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_percent_stores_l1hit = अणु
	.header		= HEADER_SPAN("-- Store Refs --", "L1 Hit", 1),
	.name		= "percent_stores_l1hit",
	.cmp		= percent_stores_l1hit_cmp,
	.entry		= percent_stores_l1hit_entry,
	.color		= percent_stores_l1hit_color,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_percent_stores_l1miss = अणु
	.header		= HEADER_SPAN_LOW("L1 Miss"),
	.name		= "percent_stores_l1miss",
	.cmp		= percent_stores_l1miss_cmp,
	.entry		= percent_stores_l1miss_entry,
	.color		= percent_stores_l1miss_color,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dram_lcl = अणु
	.header		= HEADER_SPAN("--- Load Dram ----", "Lcl", 1),
	.name		= "dram_lcl",
	.cmp		= lcl_dram_cmp,
	.entry		= lcl_dram_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dram_rmt = अणु
	.header		= HEADER_SPAN_LOW("Rmt"),
	.name		= "dram_rmt",
	.cmp		= rmt_dram_cmp,
	.entry		= rmt_dram_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_pid = अणु
	.header		= HEADER_LOW("Pid"),
	.name		= "pid",
	.cmp		= pid_cmp,
	.entry		= pid_entry,
	.width		= 7,
पूर्ण;

अटल काष्ठा c2c_dimension dim_tid = अणु
	.header		= HEADER_LOW("Tid"),
	.name		= "tid",
	.se		= &sort_thपढ़ो,
पूर्ण;

अटल काष्ठा c2c_dimension dim_symbol = अणु
	.name		= "symbol",
	.se		= &sort_sym,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dso = अणु
	.header		= HEADER_BOTH("Shared", "Object"),
	.name		= "dso",
	.se		= &sort_dso,
पूर्ण;

अटल काष्ठा c2c_header header_node[3] = अणु
	HEADER_LOW("Node"),
	HEADER_LOW("Node{cpus %hitms %stores}"),
	HEADER_LOW("Node{cpu list}"),
पूर्ण;

अटल काष्ठा c2c_dimension dim_node = अणु
	.name		= "node",
	.cmp		= empty_cmp,
	.entry		= node_entry,
	.width		= 4,
पूर्ण;

अटल काष्ठा c2c_dimension dim_mean_rmt = अणु
	.header		= HEADER_SPAN("---------- cycles ----------", "rmt hitm", 2),
	.name		= "mean_rmt",
	.cmp		= empty_cmp,
	.entry		= mean_rmt_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_mean_lcl = अणु
	.header		= HEADER_SPAN_LOW("lcl hitm"),
	.name		= "mean_lcl",
	.cmp		= empty_cmp,
	.entry		= mean_lcl_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_mean_load = अणु
	.header		= HEADER_SPAN_LOW("load"),
	.name		= "mean_load",
	.cmp		= empty_cmp,
	.entry		= mean_load_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_cpucnt = अणु
	.header		= HEADER_BOTH("cpu", "cnt"),
	.name		= "cpucnt",
	.cmp		= empty_cmp,
	.entry		= cpucnt_entry,
	.width		= 8,
पूर्ण;

अटल काष्ठा c2c_dimension dim_srcline = अणु
	.name		= "cl_srcline",
	.se		= &sort_srcline,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dcacheline_idx = अणु
	.header		= HEADER_LOW("Index"),
	.name		= "cl_idx",
	.cmp		= empty_cmp,
	.entry		= cl_idx_entry,
	.width		= 5,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dcacheline_num = अणु
	.header		= HEADER_LOW("Num"),
	.name		= "cl_num",
	.cmp		= empty_cmp,
	.entry		= cl_idx_entry,
	.width		= 5,
पूर्ण;

अटल काष्ठा c2c_dimension dim_dcacheline_num_empty = अणु
	.header		= HEADER_LOW("Num"),
	.name		= "cl_num_empty",
	.cmp		= empty_cmp,
	.entry		= cl_idx_empty_entry,
	.width		= 5,
पूर्ण;

अटल काष्ठा c2c_dimension *dimensions[] = अणु
	&dim_dcacheline,
	&dim_dcacheline_node,
	&dim_dcacheline_count,
	&dim_offset,
	&dim_offset_node,
	&dim_iaddr,
	&dim_tot_hiपंचांग,
	&dim_lcl_hiपंचांग,
	&dim_rmt_hiपंचांग,
	&dim_cl_lcl_hiपंचांग,
	&dim_cl_rmt_hiपंचांग,
	&dim_tot_stores,
	&dim_stores_l1hit,
	&dim_stores_l1miss,
	&dim_cl_stores_l1hit,
	&dim_cl_stores_l1miss,
	&dim_ld_fbhit,
	&dim_ld_l1hit,
	&dim_ld_l2hit,
	&dim_ld_llchit,
	&dim_ld_rmthit,
	&dim_tot_recs,
	&dim_tot_loads,
	&dim_percent_hiपंचांग,
	&dim_percent_rmt_hiपंचांग,
	&dim_percent_lcl_hiपंचांग,
	&dim_percent_stores_l1hit,
	&dim_percent_stores_l1miss,
	&dim_dram_lcl,
	&dim_dram_rmt,
	&dim_pid,
	&dim_tid,
	&dim_symbol,
	&dim_dso,
	&dim_node,
	&dim_mean_rmt,
	&dim_mean_lcl,
	&dim_mean_load,
	&dim_cpucnt,
	&dim_srcline,
	&dim_dcacheline_idx,
	&dim_dcacheline_num,
	&dim_dcacheline_num_empty,
	शून्य,
पूर्ण;

अटल व्योम fmt_मुक्त(काष्ठा perf_hpp_fmt *fmt)
अणु
	काष्ठा c2c_fmt *c2c_fmt;

	c2c_fmt = container_of(fmt, काष्ठा c2c_fmt, fmt);
	मुक्त(c2c_fmt);
पूर्ण

अटल bool fmt_equal(काष्ठा perf_hpp_fmt *a, काष्ठा perf_hpp_fmt *b)
अणु
	काष्ठा c2c_fmt *c2c_a = container_of(a, काष्ठा c2c_fmt, fmt);
	काष्ठा c2c_fmt *c2c_b = container_of(b, काष्ठा c2c_fmt, fmt);

	वापस c2c_a->dim == c2c_b->dim;
पूर्ण

अटल काष्ठा c2c_dimension *get_dimension(स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; dimensions[i]; i++) अणु
		काष्ठा c2c_dimension *dim = dimensions[i];

		अगर (!म_भेद(dim->name, name))
			वापस dim;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक c2c_se_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_fmt *c2c_fmt = container_of(fmt, काष्ठा c2c_fmt, fmt);
	काष्ठा c2c_dimension *dim = c2c_fmt->dim;
	माप_प्रकार len = fmt->user_len;

	अगर (!len) अणु
		len = hists__col_len(he->hists, dim->se->se_width_idx);

		अगर (dim == &dim_symbol || dim == &dim_srcline)
			len = symbol_width(he->hists, dim->se);
	पूर्ण

	वापस dim->se->se_snम_लिखो(he, hpp->buf, hpp->size, len);
पूर्ण

अटल पूर्णांक64_t c2c_se_cmp(काष्ठा perf_hpp_fmt *fmt,
			  काष्ठा hist_entry *a, काष्ठा hist_entry *b)
अणु
	काष्ठा c2c_fmt *c2c_fmt = container_of(fmt, काष्ठा c2c_fmt, fmt);
	काष्ठा c2c_dimension *dim = c2c_fmt->dim;

	वापस dim->se->se_cmp(a, b);
पूर्ण

अटल पूर्णांक64_t c2c_se_collapse(काष्ठा perf_hpp_fmt *fmt,
			       काष्ठा hist_entry *a, काष्ठा hist_entry *b)
अणु
	काष्ठा c2c_fmt *c2c_fmt = container_of(fmt, काष्ठा c2c_fmt, fmt);
	काष्ठा c2c_dimension *dim = c2c_fmt->dim;
	पूर्णांक64_t (*collapse_fn)(काष्ठा hist_entry *, काष्ठा hist_entry *);

	collapse_fn = dim->se->se_collapse ?: dim->se->se_cmp;
	वापस collapse_fn(a, b);
पूर्ण

अटल काष्ठा c2c_fmt *get_क्रमmat(स्थिर अक्षर *name)
अणु
	काष्ठा c2c_dimension *dim = get_dimension(name);
	काष्ठा c2c_fmt *c2c_fmt;
	काष्ठा perf_hpp_fmt *fmt;

	अगर (!dim)
		वापस शून्य;

	c2c_fmt = zalloc(माप(*c2c_fmt));
	अगर (!c2c_fmt)
		वापस शून्य;

	c2c_fmt->dim = dim;

	fmt = &c2c_fmt->fmt;
	INIT_LIST_HEAD(&fmt->list);
	INIT_LIST_HEAD(&fmt->sort_list);

	fmt->cmp	= dim->se ? c2c_se_cmp   : dim->cmp;
	fmt->sort	= dim->se ? c2c_se_cmp   : dim->cmp;
	fmt->color	= dim->se ? शून्य	 : dim->color;
	fmt->entry	= dim->se ? c2c_se_entry : dim->entry;
	fmt->header	= c2c_header;
	fmt->width	= c2c_width;
	fmt->collapse	= dim->se ? c2c_se_collapse : dim->cmp;
	fmt->equal	= fmt_equal;
	fmt->मुक्त	= fmt_मुक्त;

	वापस c2c_fmt;
पूर्ण

अटल पूर्णांक c2c_hists__init_output(काष्ठा perf_hpp_list *hpp_list, अक्षर *name)
अणु
	काष्ठा c2c_fmt *c2c_fmt = get_क्रमmat(name);

	अगर (!c2c_fmt) अणु
		reset_dimensions();
		वापस output_field_add(hpp_list, name);
	पूर्ण

	perf_hpp_list__column_रेजिस्टर(hpp_list, &c2c_fmt->fmt);
	वापस 0;
पूर्ण

अटल पूर्णांक c2c_hists__init_sort(काष्ठा perf_hpp_list *hpp_list, अक्षर *name)
अणु
	काष्ठा c2c_fmt *c2c_fmt = get_क्रमmat(name);
	काष्ठा c2c_dimension *dim;

	अगर (!c2c_fmt) अणु
		reset_dimensions();
		वापस sort_dimension__add(hpp_list, name, शून्य, 0);
	पूर्ण

	dim = c2c_fmt->dim;
	अगर (dim == &dim_dso)
		hpp_list->dso = 1;

	perf_hpp_list__रेजिस्टर_sort_field(hpp_list, &c2c_fmt->fmt);
	वापस 0;
पूर्ण

#घोषणा PARSE_LIST(_list, _fn)							\
	करो अणु									\
		अक्षर *पंचांगp, *tok;						\
		ret = 0;							\
										\
		अगर (!_list)							\
			अवरोध;							\
										\
		क्रम (tok = म_मोहर_r((अक्षर *)_list, ", ", &पंचांगp);			\
				tok; tok = म_मोहर_r(शून्य, ", ", &पंचांगp)) अणु	\
			ret = _fn(hpp_list, tok);				\
			अगर (ret == -EINVAL) अणु					\
				pr_err("Invalid --fields key: `%s'", tok);	\
				अवरोध;						\
			पूर्ण अन्यथा अगर (ret == -ESRCH) अणु				\
				pr_err("Unknown --fields key: `%s'", tok);	\
				अवरोध;						\
			पूर्ण							\
		पूर्ण								\
	पूर्ण जबतक (0)

अटल पूर्णांक hpp_list__parse(काष्ठा perf_hpp_list *hpp_list,
			   स्थिर अक्षर *output_,
			   स्थिर अक्षर *sort_)
अणु
	अक्षर *output = output_ ? strdup(output_) : शून्य;
	अक्षर *sort   = sort_   ? strdup(sort_) : शून्य;
	पूर्णांक ret;

	PARSE_LIST(output, c2c_hists__init_output);
	PARSE_LIST(sort,   c2c_hists__init_sort);

	/* copy sort keys to output fields */
	perf_hpp__setup_output_field(hpp_list);

	/*
	 * We करोnt need other sorting keys other than those
	 * we alपढ़ोy specअगरied. It also really slows करोwn
	 * the processing a lot with big number of output
	 * fields, so चयनing this off क्रम c2c.
	 */

#अगर 0
	/* and then copy output fields to sort keys */
	perf_hpp__append_sort_keys(&hists->list);
#पूर्ण_अगर

	मुक्त(output);
	मुक्त(sort);
	वापस ret;
पूर्ण

अटल पूर्णांक c2c_hists__init(काष्ठा c2c_hists *hists,
			   स्थिर अक्षर *sort,
			   पूर्णांक nr_header_lines)
अणु
	__hists__init(&hists->hists, &hists->list);

	/*
	 * Initialize only with sort fields, we need to resort
	 * later anyway, and that's where we add output fields
	 * as well.
	 */
	perf_hpp_list__init(&hists->list);

	/* Overload number of header lines.*/
	hists->list.nr_header_lines = nr_header_lines;

	वापस hpp_list__parse(&hists->list, शून्य, sort);
पूर्ण

अटल पूर्णांक c2c_hists__reinit(काष्ठा c2c_hists *c2c_hists,
			     स्थिर अक्षर *output,
			     स्थिर अक्षर *sort)
अणु
	perf_hpp__reset_output_field(&c2c_hists->list);
	वापस hpp_list__parse(&c2c_hists->list, output, sort);
पूर्ण

#घोषणा DISPLAY_LINE_LIMIT  0.001

अटल u8 filter_display(u32 val, u32 sum)
अणु
	अगर (sum == 0 || ((द्विगुन)val / sum) < DISPLAY_LINE_LIMIT)
		वापस HIST_FILTER__C2C;

	वापस 0;
पूर्ण

अटल bool he__display(काष्ठा hist_entry *he, काष्ठा c2c_stats *stats)
अणु
	काष्ठा c2c_hist_entry *c2c_he;

	अगर (c2c.show_all)
		वापस true;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);

	चयन (c2c.display) अणु
	हाल DISPLAY_LCL:
		he->filtered = filter_display(c2c_he->stats.lcl_hiपंचांग,
					      stats->lcl_hiपंचांग);
		अवरोध;
	हाल DISPLAY_RMT:
		he->filtered = filter_display(c2c_he->stats.rmt_hiपंचांग,
					      stats->rmt_hiपंचांग);
		अवरोध;
	हाल DISPLAY_TOT:
		he->filtered = filter_display(c2c_he->stats.tot_hiपंचांग,
					      stats->tot_hiपंचांग);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस he->filtered == 0;
पूर्ण

अटल अंतरभूत bool is_valid_hist_entry(काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	bool has_record = false;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);

	/* It's a valid entry अगर contains stores */
	अगर (c2c_he->stats.store)
		वापस true;

	चयन (c2c.display) अणु
	हाल DISPLAY_LCL:
		has_record = !!c2c_he->stats.lcl_hiपंचांग;
		अवरोध;
	हाल DISPLAY_RMT:
		has_record = !!c2c_he->stats.rmt_hiपंचांग;
		अवरोध;
	हाल DISPLAY_TOT:
		has_record = !!c2c_he->stats.tot_hiपंचांग;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस has_record;
पूर्ण

अटल व्योम set_node_width(काष्ठा c2c_hist_entry *c2c_he, पूर्णांक len)
अणु
	काष्ठा c2c_dimension *dim;

	dim = &c2c.hists == c2c_he->hists ?
	      &dim_dcacheline_node : &dim_offset_node;

	अगर (len > dim->width)
		dim->width = len;
पूर्ण

अटल पूर्णांक set_nodestr(काष्ठा c2c_hist_entry *c2c_he)
अणु
	अक्षर buf[30];
	पूर्णांक len;

	अगर (c2c_he->nodestr)
		वापस 0;

	अगर (biपंचांगap_weight(c2c_he->nodeset, c2c.nodes_cnt)) अणु
		len = biपंचांगap_scnम_लिखो(c2c_he->nodeset, c2c.nodes_cnt,
				      buf, माप(buf));
	पूर्ण अन्यथा अणु
		len = scnम_लिखो(buf, माप(buf), "N/A");
	पूर्ण

	set_node_width(c2c_he, len);
	c2c_he->nodestr = strdup(buf);
	वापस c2c_he->nodestr ? 0 : -ENOMEM;
पूर्ण

अटल व्योम calc_width(काष्ठा c2c_hist_entry *c2c_he)
अणु
	काष्ठा c2c_hists *c2c_hists;

	c2c_hists = container_of(c2c_he->he.hists, काष्ठा c2c_hists, hists);
	hists__calc_col_len(&c2c_hists->hists, &c2c_he->he);
	set_nodestr(c2c_he);
पूर्ण

अटल पूर्णांक filter_cb(काष्ठा hist_entry *he, व्योम *arg __maybe_unused)
अणु
	काष्ठा c2c_hist_entry *c2c_he;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);

	अगर (c2c.show_src && !he->srcline)
		he->srcline = hist_entry__srcline(he);

	calc_width(c2c_he);

	अगर (!is_valid_hist_entry(he))
		he->filtered = HIST_FILTER__C2C;

	वापस 0;
पूर्ण

अटल पूर्णांक resort_cl_cb(काष्ठा hist_entry *he, व्योम *arg __maybe_unused)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	काष्ठा c2c_hists *c2c_hists;
	bool display = he__display(he, &c2c.shared_clines_stats);

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	c2c_hists = c2c_he->hists;

	अगर (display && c2c_hists) अणु
		अटल अचिन्हित पूर्णांक idx;

		c2c_he->cacheline_idx = idx++;
		calc_width(c2c_he);

		c2c_hists__reinit(c2c_hists, c2c.cl_output, c2c.cl_resort);

		hists__collapse_resort(&c2c_hists->hists, शून्य);
		hists__output_resort_cb(&c2c_hists->hists, शून्य, filter_cb);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम setup_nodes_header(व्योम)
अणु
	dim_node.header = header_node[c2c.node_info];
पूर्ण

अटल पूर्णांक setup_nodes(काष्ठा perf_session *session)
अणु
	काष्ठा numa_node *n;
	अचिन्हित दीर्घ **nodes;
	पूर्णांक node, cpu;
	पूर्णांक *cpu2node;

	अगर (c2c.node_info > 2)
		c2c.node_info = 2;

	c2c.nodes_cnt = session->header.env.nr_numa_nodes;
	c2c.cpus_cnt  = session->header.env.nr_cpus_avail;

	n = session->header.env.numa_nodes;
	अगर (!n)
		वापस -EINVAL;

	nodes = zalloc(माप(अचिन्हित दीर्घ *) * c2c.nodes_cnt);
	अगर (!nodes)
		वापस -ENOMEM;

	c2c.nodes = nodes;

	cpu2node = zalloc(माप(पूर्णांक) * c2c.cpus_cnt);
	अगर (!cpu2node)
		वापस -ENOMEM;

	क्रम (cpu = 0; cpu < c2c.cpus_cnt; cpu++)
		cpu2node[cpu] = -1;

	c2c.cpu2node = cpu2node;

	क्रम (node = 0; node < c2c.nodes_cnt; node++) अणु
		काष्ठा perf_cpu_map *map = n[node].map;
		अचिन्हित दीर्घ *set;

		set = biपंचांगap_alloc(c2c.cpus_cnt);
		अगर (!set)
			वापस -ENOMEM;

		nodes[node] = set;

		/* empty node, skip */
		अगर (perf_cpu_map__empty(map))
			जारी;

		क्रम (cpu = 0; cpu < map->nr; cpu++) अणु
			set_bit(map->map[cpu], set);

			अगर (WARN_ONCE(cpu2node[map->map[cpu]] != -1, "node/cpu topology bug"))
				वापस -EINVAL;

			cpu2node[map->map[cpu]] = node;
		पूर्ण
	पूर्ण

	setup_nodes_header();
	वापस 0;
पूर्ण

#घोषणा HAS_HITMS(__h) ((__h)->stats.lcl_hiपंचांग || (__h)->stats.rmt_hiपंचांग)

अटल पूर्णांक resort_shared_cl_cb(काष्ठा hist_entry *he, व्योम *arg __maybe_unused)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);

	अगर (HAS_HITMS(c2c_he)) अणु
		c2c.shared_clines++;
		c2c_add_stats(&c2c.shared_clines_stats, &c2c_he->stats);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hists__iterate_cb(काष्ठा hists *hists, hists__resort_cb_t cb)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);
	पूर्णांक ret = 0;

	जबतक (next) अणु
		काष्ठा hist_entry *he;

		he = rb_entry(next, काष्ठा hist_entry, rb_node);
		ret = cb(he, शून्य);
		अगर (ret)
			अवरोध;
		next = rb_next(&he->rb_node);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम prपूर्णांक_c2c__display_stats(खाता *out)
अणु
	पूर्णांक llc_misses;
	काष्ठा c2c_stats *stats = &c2c.hists.stats;

	llc_misses = stats->lcl_dram +
		     stats->rmt_dram +
		     stats->rmt_hit +
		     stats->rmt_hiपंचांग;

	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "            Trace Event Information              \n");
	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "  Total records                     : %10d\n", stats->nr_entries);
	ख_लिखो(out, "  Locked Load/Store Operations      : %10d\n", stats->locks);
	ख_लिखो(out, "  Load Operations                   : %10d\n", stats->load);
	ख_लिखो(out, "  Loads - uncacheable               : %10d\n", stats->ld_uncache);
	ख_लिखो(out, "  Loads - IO                        : %10d\n", stats->ld_io);
	ख_लिखो(out, "  Loads - Miss                      : %10d\n", stats->ld_miss);
	ख_लिखो(out, "  Loads - no mapping                : %10d\n", stats->ld_noadrs);
	ख_लिखो(out, "  Load Fill Buffer Hit              : %10d\n", stats->ld_fbhit);
	ख_लिखो(out, "  Load L1D hit                      : %10d\n", stats->ld_l1hit);
	ख_लिखो(out, "  Load L2D hit                      : %10d\n", stats->ld_l2hit);
	ख_लिखो(out, "  Load LLC hit                      : %10d\n", stats->ld_llchit + stats->lcl_hiपंचांग);
	ख_लिखो(out, "  Load Local HITM                   : %10d\n", stats->lcl_hiपंचांग);
	ख_लिखो(out, "  Load Remote HITM                  : %10d\n", stats->rmt_hiपंचांग);
	ख_लिखो(out, "  Load Remote HIT                   : %10d\n", stats->rmt_hit);
	ख_लिखो(out, "  Load Local DRAM                   : %10d\n", stats->lcl_dram);
	ख_लिखो(out, "  Load Remote DRAM                  : %10d\n", stats->rmt_dram);
	ख_लिखो(out, "  Load MESI State Exclusive         : %10d\n", stats->ld_excl);
	ख_लिखो(out, "  Load MESI State Shared            : %10d\n", stats->ld_shared);
	ख_लिखो(out, "  Load LLC Misses                   : %10d\n", llc_misses);
	ख_लिखो(out, "  Load access blocked by data       : %10d\n", stats->blk_data);
	ख_लिखो(out, "  Load access blocked by address    : %10d\n", stats->blk_addr);
	ख_लिखो(out, "  LLC Misses to Local DRAM          : %10.1f%%\n", ((द्विगुन)stats->lcl_dram/(द्विगुन)llc_misses) * 100.);
	ख_लिखो(out, "  LLC Misses to Remote DRAM         : %10.1f%%\n", ((द्विगुन)stats->rmt_dram/(द्विगुन)llc_misses) * 100.);
	ख_लिखो(out, "  LLC Misses to Remote cache (HIT)  : %10.1f%%\n", ((द्विगुन)stats->rmt_hit /(द्विगुन)llc_misses) * 100.);
	ख_लिखो(out, "  LLC Misses to Remote cache (HITM) : %10.1f%%\n", ((द्विगुन)stats->rmt_hiपंचांग/(द्विगुन)llc_misses) * 100.);
	ख_लिखो(out, "  Store Operations                  : %10d\n", stats->store);
	ख_लिखो(out, "  Store - uncacheable               : %10d\n", stats->st_uncache);
	ख_लिखो(out, "  Store - no mapping                : %10d\n", stats->st_noadrs);
	ख_लिखो(out, "  Store L1D Hit                     : %10d\n", stats->st_l1hit);
	ख_लिखो(out, "  Store L1D Miss                    : %10d\n", stats->st_l1miss);
	ख_लिखो(out, "  No Page Map Rejects               : %10d\n", stats->nomap);
	ख_लिखो(out, "  Unable to parse data source       : %10d\n", stats->noparse);
पूर्ण

अटल व्योम prपूर्णांक_shared_cacheline_info(खाता *out)
अणु
	काष्ठा c2c_stats *stats = &c2c.shared_clines_stats;
	पूर्णांक hiपंचांग_cnt = stats->lcl_hiपंचांग + stats->rmt_hiपंचांग;

	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "    Global Shared Cache Line Event Information   \n");
	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "  Total Shared Cache Lines          : %10d\n", c2c.shared_clines);
	ख_लिखो(out, "  Load HITs on shared lines         : %10d\n", stats->load);
	ख_लिखो(out, "  Fill Buffer Hits on shared lines  : %10d\n", stats->ld_fbhit);
	ख_लिखो(out, "  L1D hits on shared lines          : %10d\n", stats->ld_l1hit);
	ख_लिखो(out, "  L2D hits on shared lines          : %10d\n", stats->ld_l2hit);
	ख_लिखो(out, "  LLC hits on shared lines          : %10d\n", stats->ld_llchit + stats->lcl_hiपंचांग);
	ख_लिखो(out, "  Locked Access on shared lines     : %10d\n", stats->locks);
	ख_लिखो(out, "  Blocked Access on shared lines    : %10d\n", stats->blk_data + stats->blk_addr);
	ख_लिखो(out, "  Store HITs on shared lines        : %10d\n", stats->store);
	ख_लिखो(out, "  Store L1D hits on shared lines    : %10d\n", stats->st_l1hit);
	ख_लिखो(out, "  Total Merged records              : %10d\n", hiपंचांग_cnt + stats->store);
पूर्ण

अटल व्योम prपूर्णांक_cacheline(काष्ठा c2c_hists *c2c_hists,
			    काष्ठा hist_entry *he_cl,
			    काष्ठा perf_hpp_list *hpp_list,
			    खाता *out)
अणु
	अक्षर bf[1000];
	काष्ठा perf_hpp hpp = अणु
		.buf            = bf,
		.size           = 1000,
	पूर्ण;
	अटल bool once;

	अगर (!once) अणु
		hists__ख_लिखो_headers(&c2c_hists->hists, out);
		once = true;
	पूर्ण अन्यथा अणु
		ख_लिखो(out, "\n");
	पूर्ण

	ख_लिखो(out, "  -------------------------------------------------------------\n");
	__hist_entry__snम_लिखो(he_cl, &hpp, hpp_list);
	ख_लिखो(out, "%s\n", bf);
	ख_लिखो(out, "  -------------------------------------------------------------\n");

	hists__ख_लिखो(&c2c_hists->hists, false, 0, 0, 0, out, false);
पूर्ण

अटल व्योम prपूर्णांक_pareto(खाता *out)
अणु
	काष्ठा perf_hpp_list hpp_list;
	काष्ठा rb_node *nd;
	पूर्णांक ret;
	स्थिर अक्षर *cl_output;

	cl_output = "cl_num,"
		    "cl_rmt_hitm,"
		    "cl_lcl_hitm,"
		    "cl_stores_l1hit,"
		    "cl_stores_l1miss,"
		    "dcacheline";

	perf_hpp_list__init(&hpp_list);
	ret = hpp_list__parse(&hpp_list, cl_output, शून्य);

	अगर (WARN_ONCE(ret, "failed to setup sort entries\n"))
		वापस;

	nd = rb_first_cached(&c2c.hists.hists.entries);

	क्रम (; nd; nd = rb_next(nd)) अणु
		काष्ठा hist_entry *he = rb_entry(nd, काष्ठा hist_entry, rb_node);
		काष्ठा c2c_hist_entry *c2c_he;

		अगर (he->filtered)
			जारी;

		c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
		prपूर्णांक_cacheline(c2c_he->hists, he, &hpp_list, out);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_c2c_info(खाता *out, काष्ठा perf_session *session)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा evsel *evsel;
	bool first = true;

	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "                 c2c details                     \n");
	ख_लिखो(out, "=================================================\n");

	evlist__क्रम_each_entry(evlist, evsel) अणु
		ख_लिखो(out, "%-36s: %s\n", first ? "  Events" : "", evsel__name(evsel));
		first = false;
	पूर्ण
	ख_लिखो(out, "  Cachelines sort on                : %s HITMs\n",
		display_str[c2c.display]);
	ख_लिखो(out, "  Cacheline data grouping           : %s\n", c2c.cl_sort);
पूर्ण

अटल व्योम perf_c2c__hists_ख_लिखो(खाता *out, काष्ठा perf_session *session)
अणु
	setup_pager();

	prपूर्णांक_c2c__display_stats(out);
	ख_लिखो(out, "\n");
	prपूर्णांक_shared_cacheline_info(out);
	ख_लिखो(out, "\n");
	prपूर्णांक_c2c_info(out, session);

	अगर (c2c.stats_only)
		वापस;

	ख_लिखो(out, "\n");
	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "           Shared Data Cache Line Table          \n");
	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "#\n");

	hists__ख_लिखो(&c2c.hists.hists, true, 0, 0, 0, मानक_निकास, true);

	ख_लिखो(out, "\n");
	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "      Shared Cache Line Distribution Pareto      \n");
	ख_लिखो(out, "=================================================\n");
	ख_लिखो(out, "#\n");

	prपूर्णांक_pareto(out);
पूर्ण

#अगर_घोषित HAVE_SLANG_SUPPORT
अटल व्योम c2c_browser__update_nr_entries(काष्ठा hist_browser *hb)
अणु
	u64 nr_entries = 0;
	काष्ठा rb_node *nd = rb_first_cached(&hb->hists->entries);

	जबतक (nd) अणु
		काष्ठा hist_entry *he = rb_entry(nd, काष्ठा hist_entry, rb_node);

		अगर (!he->filtered)
			nr_entries++;

		nd = rb_next(nd);
	पूर्ण

	hb->nr_non_filtered_entries = nr_entries;
पूर्ण

काष्ठा c2c_cacheline_browser अणु
	काष्ठा hist_browser	 hb;
	काष्ठा hist_entry	*he;
पूर्ण;

अटल पूर्णांक
perf_c2c_cacheline_browser__title(काष्ठा hist_browser *browser,
				  अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा c2c_cacheline_browser *cl_browser;
	काष्ठा hist_entry *he;
	uपूर्णांक64_t addr = 0;

	cl_browser = container_of(browser, काष्ठा c2c_cacheline_browser, hb);
	he = cl_browser->he;

	अगर (he->mem_info)
		addr = cl_address(he->mem_info->daddr.addr);

	scnम_लिखो(bf, size, "Cacheline 0x%lx", addr);
	वापस 0;
पूर्ण

अटल काष्ठा c2c_cacheline_browser*
c2c_cacheline_browser__new(काष्ठा hists *hists, काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_cacheline_browser *browser;

	browser = zalloc(माप(*browser));
	अगर (browser) अणु
		hist_browser__init(&browser->hb, hists);
		browser->hb.c2c_filter	= true;
		browser->hb.title	= perf_c2c_cacheline_browser__title;
		browser->he		= he;
	पूर्ण

	वापस browser;
पूर्ण

अटल पूर्णांक perf_c2c__browse_cacheline(काष्ठा hist_entry *he)
अणु
	काष्ठा c2c_hist_entry *c2c_he;
	काष्ठा c2c_hists *c2c_hists;
	काष्ठा c2c_cacheline_browser *cl_browser;
	काष्ठा hist_browser *browser;
	पूर्णांक key = -1;
	अटल स्थिर अक्षर help[] =
	" ENTER         Toggle callchains (if present) \n"
	" n             Toggle Node details info \n"
	" s             Toggle full length of symbol and source line columns \n"
	" q             Return back to cacheline list \n";

	अगर (!he)
		वापस 0;

	/* Display compact version first. */
	c2c.symbol_full = false;

	c2c_he = container_of(he, काष्ठा c2c_hist_entry, he);
	c2c_hists = c2c_he->hists;

	cl_browser = c2c_cacheline_browser__new(&c2c_hists->hists, he);
	अगर (cl_browser == शून्य)
		वापस -1;

	browser = &cl_browser->hb;

	/* reset पात key so that it can get Ctrl-C as a key */
	SLang_reset_tty();
	SLang_init_tty(0, 0, 0);

	c2c_browser__update_nr_entries(browser);

	जबतक (1) अणु
		key = hist_browser__run(browser, "? - help", true, 0);

		चयन (key) अणु
		हाल 's':
			c2c.symbol_full = !c2c.symbol_full;
			अवरोध;
		हाल 'n':
			c2c.node_info = (c2c.node_info + 1) % 3;
			setup_nodes_header();
			अवरोध;
		हाल 'q':
			जाओ out;
		हाल '?':
			ui_browser__help_winकरोw(&browser->b, help);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	मुक्त(cl_browser);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_c2c_browser__title(काष्ठा hist_browser *browser,
				   अक्षर *bf, माप_प्रकार size)
अणु
	scnम_लिखो(bf, size,
		  "Shared Data Cache Line Table     "
		  "(%lu entries, sorted on %s HITMs)",
		  browser->nr_non_filtered_entries,
		  display_str[c2c.display]);
	वापस 0;
पूर्ण

अटल काष्ठा hist_browser*
perf_c2c_browser__new(काष्ठा hists *hists)
अणु
	काष्ठा hist_browser *browser = hist_browser__new(hists);

	अगर (browser) अणु
		browser->title = perf_c2c_browser__title;
		browser->c2c_filter = true;
	पूर्ण

	वापस browser;
पूर्ण

अटल पूर्णांक perf_c2c__hists_browse(काष्ठा hists *hists)
अणु
	काष्ठा hist_browser *browser;
	पूर्णांक key = -1;
	अटल स्थिर अक्षर help[] =
	" d             Display cacheline details \n"
	" ENTER         Toggle callchains (if present) \n"
	" q             Quit \n";

	browser = perf_c2c_browser__new(hists);
	अगर (browser == शून्य)
		वापस -1;

	/* reset पात key so that it can get Ctrl-C as a key */
	SLang_reset_tty();
	SLang_init_tty(0, 0, 0);

	c2c_browser__update_nr_entries(browser);

	जबतक (1) अणु
		key = hist_browser__run(browser, "? - help", true, 0);

		चयन (key) अणु
		हाल 'q':
			जाओ out;
		हाल 'd':
			perf_c2c__browse_cacheline(browser->he_selection);
			अवरोध;
		हाल '?':
			ui_browser__help_winकरोw(&browser->b, help);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	hist_browser__delete(browser);
	वापस 0;
पूर्ण

अटल व्योम perf_c2c_display(काष्ठा perf_session *session)
अणु
	अगर (use_browser == 0)
		perf_c2c__hists_ख_लिखो(मानक_निकास, session);
	अन्यथा
		perf_c2c__hists_browse(&c2c.hists.hists);
पूर्ण
#अन्यथा
अटल व्योम perf_c2c_display(काष्ठा perf_session *session)
अणु
	use_browser = 0;
	perf_c2c__hists_ख_लिखो(मानक_निकास, session);
पूर्ण
#पूर्ण_अगर /* HAVE_SLANG_SUPPORT */

अटल अक्षर *fill_line(स्थिर अक्षर *orig, पूर्णांक len)
अणु
	पूर्णांक i, j, olen = म_माप(orig);
	अक्षर *buf;

	buf = zalloc(len + 1);
	अगर (!buf)
		वापस शून्य;

	j = len / 2 - olen / 2;

	क्रम (i = 0; i < j - 1; i++)
		buf[i] = '-';

	buf[i++] = ' ';

	म_नकल(buf + i, orig);

	i += olen;

	buf[i++] = ' ';

	क्रम (; i < len; i++)
		buf[i] = '-';

	वापस buf;
पूर्ण

अटल पूर्णांक ui_quirks(व्योम)
अणु
	स्थिर अक्षर *nodestr = "Data address";
	अक्षर *buf;

	अगर (!c2c.use_stdio) अणु
		dim_offset.width  = 5;
		dim_offset.header = header_offset_tui;
		nodestr = "CL";
	पूर्ण

	dim_percent_hiपंचांग.header = percent_hiपंचांग_header[c2c.display];

	/* Fix the zero line क्रम dcacheline column. */
	buf = fill_line("Cacheline", dim_dcacheline.width +
				     dim_dcacheline_node.width +
				     dim_dcacheline_count.width + 4);
	अगर (!buf)
		वापस -ENOMEM;

	dim_dcacheline.header.line[0].text = buf;

	/* Fix the zero line क्रम offset column. */
	buf = fill_line(nodestr, dim_offset.width +
			         dim_offset_node.width +
				 dim_dcacheline_count.width + 4);
	अगर (!buf)
		वापस -ENOMEM;

	dim_offset.header.line[0].text = buf;

	वापस 0;
पूर्ण

#घोषणा CALLCHAIN_DEFAULT_OPT  "graph,0.5,caller,function,percent"

स्थिर अक्षर callchain_help[] = "Display call graph (stack chain/backtrace):\n\n"
				CALLCHAIN_REPORT_HELP
				"\n\t\t\t\tDefault: " CALLCHAIN_DEFAULT_OPT;

अटल पूर्णांक
parse_callchain_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset)
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

अटल पूर्णांक setup_callchain(काष्ठा evlist *evlist)
अणु
	u64 sample_type = evlist__combined_sample_type(evlist);
	क्रमागत perf_call_graph_mode mode = CALLCHAIN_NONE;

	अगर ((sample_type & PERF_SAMPLE_REGS_USER) &&
	    (sample_type & PERF_SAMPLE_STACK_USER)) अणु
		mode = CALLCHAIN_DWARF;
		dwarf_callchain_users = true;
	पूर्ण अन्यथा अगर (sample_type & PERF_SAMPLE_BRANCH_STACK)
		mode = CALLCHAIN_LBR;
	अन्यथा अगर (sample_type & PERF_SAMPLE_CALLCHAIN)
		mode = CALLCHAIN_FP;

	अगर (!callchain_param.enabled &&
	    callchain_param.mode != CHAIN_NONE &&
	    mode != CALLCHAIN_NONE) अणु
		symbol_conf.use_callchain = true;
		अगर (callchain_रेजिस्टर_param(&callchain_param) < 0) अणु
			ui__error("Can't register callchain params.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (c2c.stitch_lbr && (mode != CALLCHAIN_LBR)) अणु
		ui__warning("Can't find LBR callchain. Switch off --stitch-lbr.\n"
			    "Please apply --call-graph lbr when recording.\n");
		c2c.stitch_lbr = false;
	पूर्ण

	callchain_param.record_mode = mode;
	callchain_param.min_percent = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक setup_display(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *display = str ?: "tot";

	अगर (!म_भेद(display, "tot"))
		c2c.display = DISPLAY_TOT;
	अन्यथा अगर (!म_भेद(display, "rmt"))
		c2c.display = DISPLAY_RMT;
	अन्यथा अगर (!म_भेद(display, "lcl"))
		c2c.display = DISPLAY_LCL;
	अन्यथा अणु
		pr_err("failed: unknown display type: %s\n", str);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा क्रम_each_token(__tok, __buf, __sep, __पंचांगp)		\
	क्रम (__tok = म_मोहर_r(__buf, __sep, &__पंचांगp); __tok;	\
	     __tok = म_मोहर_r(शून्य,  __sep, &__पंचांगp))

अटल पूर्णांक build_cl_output(अक्षर *cl_sort, bool no_source)
अणु
	अक्षर *tok, *पंचांगp, *buf = strdup(cl_sort);
	bool add_pid   = false;
	bool add_tid   = false;
	bool add_iaddr = false;
	bool add_sym   = false;
	bool add_dso   = false;
	bool add_src   = false;
	पूर्णांक ret = 0;

	अगर (!buf)
		वापस -ENOMEM;

	क्रम_each_token(tok, buf, ",", पंचांगp) अणु
		अगर (!म_भेद(tok, "tid")) अणु
			add_tid = true;
		पूर्ण अन्यथा अगर (!म_भेद(tok, "pid")) अणु
			add_pid = true;
		पूर्ण अन्यथा अगर (!म_भेद(tok, "iaddr")) अणु
			add_iaddr = true;
			add_sym   = true;
			add_dso   = true;
			add_src   = no_source ? false : true;
		पूर्ण अन्यथा अगर (!म_भेद(tok, "dso")) अणु
			add_dso = true;
		पूर्ण अन्यथा अगर (म_भेद(tok, "offset")) अणु
			pr_err("unrecognized sort token: %s\n", tok);
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (aप्र_लिखो(&c2c.cl_output,
		"%s%s%s%s%s%s%s%s%s%s",
		c2c.use_stdio ? "cl_num_empty," : "",
		"percent_rmt_hitm,"
		"percent_lcl_hitm,"
		"percent_stores_l1hit,"
		"percent_stores_l1miss,"
		"offset,offset_node,dcacheline_count,",
		add_pid   ? "pid," : "",
		add_tid   ? "tid," : "",
		add_iaddr ? "iaddr," : "",
		"mean_rmt,"
		"mean_lcl,"
		"mean_load,"
		"tot_recs,"
		"cpucnt,",
		add_sym ? "symbol," : "",
		add_dso ? "dso," : "",
		add_src ? "cl_srcline," : "",
		"node") < 0) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	c2c.show_src = add_src;
err:
	मुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक setup_coalesce(स्थिर अक्षर *coalesce, bool no_source)
अणु
	स्थिर अक्षर *c = coalesce ?: coalesce_शेष;

	अगर (aप्र_लिखो(&c2c.cl_sort, "offset,%s", c) < 0)
		वापस -ENOMEM;

	अगर (build_cl_output(c2c.cl_sort, no_source))
		वापस -1;

	अगर (aप्र_लिखो(&c2c.cl_resort, "offset,%s",
		     c2c.display == DISPLAY_TOT ?
		     "tot_hitm" :
		     c2c.display == DISPLAY_RMT ?
		     "rmt_hitm,lcl_hitm" :
		     "lcl_hitm,rmt_hitm") < 0)
		वापस -ENOMEM;

	pr_debug("coalesce sort   fields: %s\n", c2c.cl_sort);
	pr_debug("coalesce resort fields: %s\n", c2c.cl_resort);
	pr_debug("coalesce output fields: %s\n", c2c.cl_output);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_c2c__report(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा itrace_synth_opts itrace_synth_opts = अणु
		.set = true,
		.mem = true,	/* Only enable memory event */
		.शेष_no_sample = true,
	पूर्ण;

	काष्ठा perf_session *session;
	काष्ठा ui_progress prog;
	काष्ठा perf_data data = अणु
		.mode = PERF_DATA_MODE_READ,
	पूर्ण;
	अक्षर callchain_शेष_opt[] = CALLCHAIN_DEFAULT_OPT;
	स्थिर अक्षर *display = शून्य;
	स्थिर अक्षर *coalesce = शून्य;
	bool no_source = false;
	स्थिर काष्ठा option options[] = अणु
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_STRING('i', "input", &input_name, "file",
		   "the input file to process"),
	OPT_INCR('N', "node-info", &c2c.node_info,
		 "show extra node info in report (repeat for more info)"),
#अगर_घोषित HAVE_SLANG_SUPPORT
	OPT_BOOLEAN(0, "stdio", &c2c.use_stdio, "Use the stdio interface"),
#पूर्ण_अगर
	OPT_BOOLEAN(0, "stats", &c2c.stats_only,
		    "Display only statistic tables (implies --stdio)"),
	OPT_BOOLEAN(0, "full-symbols", &c2c.symbol_full,
		    "Display full length of symbols"),
	OPT_BOOLEAN(0, "no-source", &no_source,
		    "Do not display Source Line column"),
	OPT_BOOLEAN(0, "show-all", &c2c.show_all,
		    "Show all captured HITM lines."),
	OPT_CALLBACK_DEFAULT('g', "call-graph", &callchain_param,
			     "print_type,threshold[,print_limit],order,sort_key[,branch],value",
			     callchain_help, &parse_callchain_opt,
			     callchain_शेष_opt),
	OPT_STRING('d', "display", &display, "Switch HITM output type", "lcl,rmt"),
	OPT_STRING('c', "coalesce", &coalesce, "coalesce fields",
		   "coalesce fields: pid,tid,iaddr,dso"),
	OPT_BOOLEAN('f', "force", &symbol_conf.force, "don't complain, करो it"),
	OPT_BOOLEAN(0, "stitch-lbr", &c2c.stitch_lbr,
		    "Enable LBR callgraph stitching approach"),
	OPT_PARENT(c2c_options),
	OPT_END()
	पूर्ण;
	पूर्णांक err = 0;
	स्थिर अक्षर *output_str, *sort_str = शून्य;

	argc = parse_options(argc, argv, options, report_c2c_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (argc)
		usage_with_options(report_c2c_usage, options);

	अगर (c2c.stats_only)
		c2c.use_stdio = true;

	अगर (!input_name || !म_माप(input_name))
		input_name = "perf.data";

	data.path  = input_name;
	data.क्रमce = symbol_conf.क्रमce;

	err = setup_display(display);
	अगर (err)
		जाओ out;

	err = setup_coalesce(coalesce, no_source);
	अगर (err) अणु
		pr_debug("Failed to initialize hists\n");
		जाओ out;
	पूर्ण

	err = c2c_hists__init(&c2c.hists, "dcacheline", 2);
	अगर (err) अणु
		pr_debug("Failed to initialize hists\n");
		जाओ out;
	पूर्ण

	session = perf_session__new(&data, 0, &c2c.tool);
	अगर (IS_ERR(session)) अणु
		err = PTR_ERR(session);
		pr_debug("Error creating perf session\n");
		जाओ out;
	पूर्ण

	session->itrace_synth_opts = &itrace_synth_opts;

	err = setup_nodes(session);
	अगर (err) अणु
		pr_err("Failed setup nodes\n");
		जाओ out;
	पूर्ण

	err = mem2node__init(&c2c.mem2node, &session->header.env);
	अगर (err)
		जाओ out_session;

	err = setup_callchain(session->evlist);
	अगर (err)
		जाओ out_mem2node;

	अगर (symbol__init(&session->header.env) < 0)
		जाओ out_mem2node;

	/* No pipe support at the moment. */
	अगर (perf_data__is_pipe(session->data)) अणु
		pr_debug("No pipe support at the moment.\n");
		जाओ out_mem2node;
	पूर्ण

	अगर (c2c.use_stdio)
		use_browser = 0;
	अन्यथा
		use_browser = 1;

	setup_browser(false);

	err = perf_session__process_events(session);
	अगर (err) अणु
		pr_err("failed to process sample\n");
		जाओ out_mem2node;
	पूर्ण

	output_str = "cl_idx,"
		     "dcacheline,"
		     "dcacheline_node,"
		     "dcacheline_count,"
		     "percent_hitm,"
		     "tot_hitm,lcl_hitm,rmt_hitm,"
		     "tot_recs,"
		     "tot_loads,"
		     "tot_stores,"
		     "stores_l1hit,stores_l1miss,"
		     "ld_fbhit,ld_l1hit,ld_l2hit,"
		     "ld_lclhit,lcl_hitm,"
		     "ld_rmthit,rmt_hitm,"
		     "dram_lcl,dram_rmt";

	अगर (c2c.display == DISPLAY_TOT)
		sort_str = "tot_hitm";
	अन्यथा अगर (c2c.display == DISPLAY_RMT)
		sort_str = "rmt_hitm";
	अन्यथा अगर (c2c.display == DISPLAY_LCL)
		sort_str = "lcl_hitm";

	c2c_hists__reinit(&c2c.hists, output_str, sort_str);

	ui_progress__init(&prog, c2c.hists.hists.nr_entries, "Sorting...");

	hists__collapse_resort(&c2c.hists.hists, शून्य);
	hists__output_resort_cb(&c2c.hists.hists, &prog, resort_shared_cl_cb);
	hists__iterate_cb(&c2c.hists.hists, resort_cl_cb);

	ui_progress__finish();

	अगर (ui_quirks()) अणु
		pr_err("failed to setup UI\n");
		जाओ out_mem2node;
	पूर्ण

	perf_c2c_display(session);

out_mem2node:
	mem2node__निकास(&c2c.mem2node);
out_session:
	perf_session__delete(session);
out:
	वापस err;
पूर्ण

अटल पूर्णांक parse_record_events(स्थिर काष्ठा option *opt,
			       स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	bool *event_set = (bool *) opt->value;

	अगर (!म_भेद(str, "list")) अणु
		perf_mem_events__list();
		निकास(0);
	पूर्ण
	अगर (perf_mem_events__parse(str))
		निकास(-1);

	*event_set = true;
	वापस 0;
पूर्ण


अटल स्थिर अक्षर * स्थिर __usage_record[] = अणु
	"perf c2c record [<options>] [<command>]",
	"perf c2c record [<options>] -- <command> [<options>]",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर *record_mem_usage = __usage_record;

अटल पूर्णांक perf_c2c__record(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक rec_argc, i = 0, j;
	स्थिर अक्षर **rec_argv;
	पूर्णांक ret;
	bool all_user = false, all_kernel = false;
	bool event_set = false;
	काष्ठा perf_mem_event *e;
	काष्ठा option options[] = अणु
	OPT_CALLBACK('e', "event", &event_set, "event",
		     "event selector. Use 'perf c2c record -e list' to list available events",
		     parse_record_events),
	OPT_BOOLEAN('u', "all-user", &all_user, "collect only user level data"),
	OPT_BOOLEAN('k', "all-kernel", &all_kernel, "collect only kernel level data"),
	OPT_UINTEGER('l', "ldlat", &perf_mem_events__loads_ldlat, "setup mem-loads latency"),
	OPT_PARENT(c2c_options),
	OPT_END()
	पूर्ण;

	अगर (perf_mem_events__init()) अणु
		pr_err("failed: memory events not supported\n");
		वापस -1;
	पूर्ण

	argc = parse_options(argc, argv, options, record_mem_usage,
			     PARSE_OPT_KEEP_UNKNOWN);

	rec_argc = argc + 11; /* max number of arguments */
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));
	अगर (!rec_argv)
		वापस -1;

	rec_argv[i++] = "record";

	अगर (!event_set) अणु
		e = perf_mem_events__ptr(PERF_MEM_EVENTS__LOAD_STORE);
		/*
		 * The load and store operations are required, use the event
		 * PERF_MEM_EVENTS__LOAD_STORE अगर it is supported.
		 */
		अगर (e->tag) अणु
			e->record = true;
		पूर्ण अन्यथा अणु
			e = perf_mem_events__ptr(PERF_MEM_EVENTS__LOAD);
			e->record = true;

			e = perf_mem_events__ptr(PERF_MEM_EVENTS__STORE);
			e->record = true;
		पूर्ण
	पूर्ण

	e = perf_mem_events__ptr(PERF_MEM_EVENTS__LOAD);
	अगर (e->record)
		rec_argv[i++] = "-W";

	rec_argv[i++] = "-d";
	rec_argv[i++] = "--phys-data";
	rec_argv[i++] = "--sample-cpu";

	क्रम (j = 0; j < PERF_MEM_EVENTS__MAX; j++) अणु
		e = perf_mem_events__ptr(j);
		अगर (!e->record)
			जारी;

		अगर (!e->supported) अणु
			pr_err("failed: event '%s' not supported\n",
			       perf_mem_events__name(j));
			मुक्त(rec_argv);
			वापस -1;
		पूर्ण

		rec_argv[i++] = "-e";
		rec_argv[i++] = perf_mem_events__name(j);
	पूर्ण

	अगर (all_user)
		rec_argv[i++] = "--all-user";

	अगर (all_kernel)
		rec_argv[i++] = "--all-kernel";

	क्रम (j = 0; j < argc; j++, i++)
		rec_argv[i] = argv[j];

	अगर (verbose > 0) अणु
		pr_debug("calling: ");

		j = 0;

		जबतक (rec_argv[j]) अणु
			pr_debug("%s ", rec_argv[j]);
			j++;
		पूर्ण
		pr_debug("\n");
	पूर्ण

	ret = cmd_record(i, rec_argv);
	मुक्त(rec_argv);
	वापस ret;
पूर्ण

पूर्णांक cmd_c2c(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	argc = parse_options(argc, argv, c2c_options, c2c_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	अगर (!argc)
		usage_with_options(c2c_usage, c2c_options);

	अगर (!म_भेदन(argv[0], "rec", 3)) अणु
		वापस perf_c2c__record(argc, argv);
	पूर्ण अन्यथा अगर (!म_भेदन(argv[0], "rep", 3)) अणु
		वापस perf_c2c__report(argc, argv);
	पूर्ण अन्यथा अणु
		usage_with_options(c2c_usage, c2c_options);
	पूर्ण

	वापस 0;
पूर्ण
