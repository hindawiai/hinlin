<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-dअगरf.c
 *
 * Builtin dअगरf command: Analyze two perf.data input files, look up and पढ़ो
 * DSOs and symbol inक्रमmation, sort them and produce a dअगरf.
 */
#समावेश "builtin.h"
#समावेश "perf.h"

#समावेश "util/debug.h"
#समावेश "util/event.h"
#समावेश "util/hist.h"
#समावेश "util/evsel.h"
#समावेश "util/evlist.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/sort.h"
#समावेश "util/srcline.h"
#समावेश "util/symbol.h"
#समावेश "util/data.h"
#समावेश "util/config.h"
#समावेश "util/time-utils.h"
#समावेश "util/annotate.h"
#समावेश "util/map.h"
#समावेश "util/spark.h"
#समावेश "util/block-info.h"
#समावेश "util/stream.h"
#समावेश <linux/err.h>
#समावेश <linux/zभाग.स>
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <गणित.स>

काष्ठा perf_dअगरf अणु
	काष्ठा perf_tool		 tool;
	स्थिर अक्षर			*समय_str;
	काष्ठा perf_समय_पूर्णांकerval	*pसमय_range;
	पूर्णांक				 range_size;
	पूर्णांक				 range_num;
	bool				 has_br_stack;
	bool				 stream;
पूर्ण;

/* Dअगरf command specअगरic HPP columns. */
क्रमागत अणु
	PERF_HPP_DIFF__BASELINE,
	PERF_HPP_DIFF__PERIOD,
	PERF_HPP_DIFF__PERIOD_BASELINE,
	PERF_HPP_DIFF__DELTA,
	PERF_HPP_DIFF__RATIO,
	PERF_HPP_DIFF__WEIGHTED_DIFF,
	PERF_HPP_DIFF__FORMULA,
	PERF_HPP_DIFF__DELTA_ABS,
	PERF_HPP_DIFF__CYCLES,
	PERF_HPP_DIFF__CYCLES_HIST,

	PERF_HPP_DIFF__MAX_INDEX
पूर्ण;

काष्ठा dअगरf_hpp_fmt अणु
	काष्ठा perf_hpp_fmt	 fmt;
	पूर्णांक			 idx;
	अक्षर			*header;
	पूर्णांक			 header_width;
पूर्ण;

काष्ठा data__file अणु
	काष्ठा perf_session	*session;
	काष्ठा perf_data	 data;
	पूर्णांक			 idx;
	काष्ठा hists		*hists;
	काष्ठा evlist_streams	*evlist_streams;
	काष्ठा dअगरf_hpp_fmt	 fmt[PERF_HPP_DIFF__MAX_INDEX];
पूर्ण;

अटल काष्ठा data__file *data__files;
अटल पूर्णांक data__files_cnt;

#घोषणा data__क्रम_each_file_start(i, d, s)	\
	क्रम (i = s, d = &data__files[s];	\
	     i < data__files_cnt;		\
	     i++, d = &data__files[i])

#घोषणा data__क्रम_each_file(i, d) data__क्रम_each_file_start(i, d, 0)
#घोषणा data__क्रम_each_file_new(i, d) data__क्रम_each_file_start(i, d, 1)

अटल bool क्रमce;
अटल bool show_period;
अटल bool show_क्रमmula;
अटल bool show_baseline_only;
अटल bool cycles_hist;
अटल अचिन्हित पूर्णांक sort_compute = 1;

अटल s64 compute_wdअगरf_w1;
अटल s64 compute_wdअगरf_w2;

अटल स्थिर अक्षर		*cpu_list;
अटल DECLARE_BITMAP(cpu_biपंचांगap, MAX_NR_CPUS);

क्रमागत अणु
	COMPUTE_DELTA,
	COMPUTE_RATIO,
	COMPUTE_WEIGHTED_DIFF,
	COMPUTE_DELTA_ABS,
	COMPUTE_CYCLES,
	COMPUTE_MAX,
	COMPUTE_STREAM,	/* After COMPUTE_MAX to aव्योम use current compute arrays */
पूर्ण;

स्थिर अक्षर *compute_names[COMPUTE_MAX] = अणु
	[COMPUTE_DELTA] = "delta",
	[COMPUTE_DELTA_ABS] = "delta-abs",
	[COMPUTE_RATIO] = "ratio",
	[COMPUTE_WEIGHTED_DIFF] = "wdiff",
	[COMPUTE_CYCLES] = "cycles",
पूर्ण;

अटल पूर्णांक compute = COMPUTE_DELTA_ABS;

अटल पूर्णांक compute_2_hpp[COMPUTE_MAX] = अणु
	[COMPUTE_DELTA]		= PERF_HPP_DIFF__DELTA,
	[COMPUTE_DELTA_ABS]	= PERF_HPP_DIFF__DELTA_ABS,
	[COMPUTE_RATIO]		= PERF_HPP_DIFF__RATIO,
	[COMPUTE_WEIGHTED_DIFF]	= PERF_HPP_DIFF__WEIGHTED_DIFF,
	[COMPUTE_CYCLES]	= PERF_HPP_DIFF__CYCLES,
पूर्ण;

#घोषणा MAX_COL_WIDTH 70

अटल काष्ठा header_column अणु
	स्थिर अक्षर *name;
	पूर्णांक width;
पूर्ण columns[PERF_HPP_DIFF__MAX_INDEX] = अणु
	[PERF_HPP_DIFF__BASELINE] = अणु
		.name  = "Baseline",
	पूर्ण,
	[PERF_HPP_DIFF__PERIOD] = अणु
		.name  = "Period",
		.width = 14,
	पूर्ण,
	[PERF_HPP_DIFF__PERIOD_BASELINE] = अणु
		.name  = "Base period",
		.width = 14,
	पूर्ण,
	[PERF_HPP_DIFF__DELTA] = अणु
		.name  = "Delta",
		.width = 7,
	पूर्ण,
	[PERF_HPP_DIFF__DELTA_ABS] = अणु
		.name  = "Delta Abs",
		.width = 7,
	पूर्ण,
	[PERF_HPP_DIFF__RATIO] = अणु
		.name  = "Ratio",
		.width = 14,
	पूर्ण,
	[PERF_HPP_DIFF__WEIGHTED_DIFF] = अणु
		.name  = "Weighted diff",
		.width = 14,
	पूर्ण,
	[PERF_HPP_DIFF__FORMULA] = अणु
		.name  = "Formula",
		.width = MAX_COL_WIDTH,
	पूर्ण,
	[PERF_HPP_DIFF__CYCLES] = अणु
		.name  = "[Program Block Range] Cycles Diff",
		.width = 70,
	पूर्ण,
	[PERF_HPP_DIFF__CYCLES_HIST] = अणु
		.name  = "stddev/Hist",
		.width = NUM_SPARKS + 9,
	पूर्ण
पूर्ण;

अटल पूर्णांक setup_compute_opt_wdअगरf(अक्षर *opt)
अणु
	अक्षर *w1_str = opt;
	अक्षर *w2_str;

	पूर्णांक ret = -EINVAL;

	अगर (!opt)
		जाओ out;

	w2_str = म_अक्षर(opt, ',');
	अगर (!w2_str)
		जाओ out;

	*w2_str++ = 0x0;
	अगर (!*w2_str)
		जाओ out;

	compute_wdअगरf_w1 = म_से_दीर्घ(w1_str, शून्य, 10);
	compute_wdअगरf_w2 = म_से_दीर्घ(w2_str, शून्य, 10);

	अगर (!compute_wdअगरf_w1 || !compute_wdअगरf_w2)
		जाओ out;

	pr_debug("compute wdiff w1(%" PRId64 ") w2(%" PRId64 ")\n",
		  compute_wdअगरf_w1, compute_wdअगरf_w2);

	ret = 0;

 out:
	अगर (ret)
		pr_err("Failed: wrong weight data, use 'wdiff:w1,w2'\n");

	वापस ret;
पूर्ण

अटल पूर्णांक setup_compute_opt(अक्षर *opt)
अणु
	अगर (compute == COMPUTE_WEIGHTED_DIFF)
		वापस setup_compute_opt_wdअगरf(opt);

	अगर (opt) अणु
		pr_err("Failed: extra option specified '%s'", opt);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_compute(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			 पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक *cp = (पूर्णांक *) opt->value;
	अक्षर *cstr = (अक्षर *) str;
	अक्षर buf[50];
	अचिन्हित i;
	अक्षर *option;

	अगर (!str) अणु
		*cp = COMPUTE_DELTA;
		वापस 0;
	पूर्ण

	option = म_अक्षर(str, ':');
	अगर (option) अणु
		अचिन्हित len = option++ - str;

		/*
		 * The str data are not ग_लिखोable, so we need
		 * to use another buffer.
		 */

		/* No option value is दीर्घer. */
		अगर (len >= माप(buf))
			वापस -EINVAL;

		म_नकलन(buf, str, len);
		buf[len] = 0x0;
		cstr = buf;
	पूर्ण

	क्रम (i = 0; i < COMPUTE_MAX; i++)
		अगर (!म_भेद(cstr, compute_names[i])) अणु
			*cp = i;
			वापस setup_compute_opt(option);
		पूर्ण

	pr_err("Failed: '%s' is not computation method "
	       "(use 'delta','ratio' or 'wdiff')\n", str);
	वापस -EINVAL;
पूर्ण

अटल द्विगुन period_percent(काष्ठा hist_entry *he, u64 period)
अणु
	u64 total = hists__total_period(he->hists);

	वापस (period * 100.0) / total;
पूर्ण

अटल द्विगुन compute_delta(काष्ठा hist_entry *he, काष्ठा hist_entry *pair)
अणु
	द्विगुन old_percent = period_percent(he, he->stat.period);
	द्विगुन new_percent = period_percent(pair, pair->stat.period);

	pair->dअगरf.period_ratio_delta = new_percent - old_percent;
	pair->dअगरf.computed = true;
	वापस pair->dअगरf.period_ratio_delta;
पूर्ण

अटल द्विगुन compute_ratio(काष्ठा hist_entry *he, काष्ठा hist_entry *pair)
अणु
	द्विगुन old_period = he->stat.period ?: 1;
	द्विगुन new_period = pair->stat.period;

	pair->dअगरf.computed = true;
	pair->dअगरf.period_ratio = new_period / old_period;
	वापस pair->dअगरf.period_ratio;
पूर्ण

अटल s64 compute_wdअगरf(काष्ठा hist_entry *he, काष्ठा hist_entry *pair)
अणु
	u64 old_period = he->stat.period;
	u64 new_period = pair->stat.period;

	pair->dअगरf.computed = true;
	pair->dअगरf.wdअगरf = new_period * compute_wdअगरf_w2 -
			   old_period * compute_wdअगरf_w1;

	वापस pair->dअगरf.wdअगरf;
पूर्ण

अटल पूर्णांक क्रमmula_delta(काष्ठा hist_entry *he, काष्ठा hist_entry *pair,
			 अक्षर *buf, माप_प्रकार size)
अणु
	u64 he_total = he->hists->stats.total_period;
	u64 pair_total = pair->hists->stats.total_period;

	अगर (symbol_conf.filter_relative) अणु
		he_total = he->hists->stats.total_non_filtered_period;
		pair_total = pair->hists->stats.total_non_filtered_period;
	पूर्ण
	वापस scnम_लिखो(buf, size,
			 "(%" PRIu64 " * 100 / %" PRIu64 ") - "
			 "(%" PRIu64 " * 100 / %" PRIu64 ")",
			 pair->stat.period, pair_total,
			 he->stat.period, he_total);
पूर्ण

अटल पूर्णांक क्रमmula_ratio(काष्ठा hist_entry *he, काष्ठा hist_entry *pair,
			 अक्षर *buf, माप_प्रकार size)
अणु
	द्विगुन old_period = he->stat.period;
	द्विगुन new_period = pair->stat.period;

	वापस scnम_लिखो(buf, size, "%.0F / %.0F", new_period, old_period);
पूर्ण

अटल पूर्णांक क्रमmula_wdअगरf(काष्ठा hist_entry *he, काष्ठा hist_entry *pair,
			 अक्षर *buf, माप_प्रकार size)
अणु
	u64 old_period = he->stat.period;
	u64 new_period = pair->stat.period;

	वापस scnम_लिखो(buf, size,
		  "(%" PRIu64 " * " "%" PRId64 ") - (%" PRIu64 " * " "%" PRId64 ")",
		  new_period, compute_wdअगरf_w2, old_period, compute_wdअगरf_w1);
पूर्ण

अटल पूर्णांक क्रमmula_ख_लिखो(काष्ठा hist_entry *he, काष्ठा hist_entry *pair,
			   अक्षर *buf, माप_प्रकार size)
अणु
	चयन (compute) अणु
	हाल COMPUTE_DELTA:
	हाल COMPUTE_DELTA_ABS:
		वापस क्रमmula_delta(he, pair, buf, size);
	हाल COMPUTE_RATIO:
		वापस क्रमmula_ratio(he, pair, buf, size);
	हाल COMPUTE_WEIGHTED_DIFF:
		वापस क्रमmula_wdअगरf(he, pair, buf, size);
	शेष:
		BUG_ON(1);
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम *block_hist_zalloc(माप_प्रकार size)
अणु
	काष्ठा block_hist *bh;

	bh = zalloc(size + माप(*bh));
	अगर (!bh)
		वापस शून्य;

	वापस &bh->he;
पूर्ण

अटल व्योम block_hist_मुक्त(व्योम *he)
अणु
	काष्ठा block_hist *bh;

	bh = container_of(he, काष्ठा block_hist, he);
	hists__delete_entries(&bh->block_hists);
	मुक्त(bh);
पूर्ण

काष्ठा hist_entry_ops block_hist_ops = अणु
	.new    = block_hist_zalloc,
	.मुक्त   = block_hist_मुक्त,
पूर्ण;

अटल पूर्णांक dअगरf__process_sample_event(काष्ठा perf_tool *tool,
				      जोड़ perf_event *event,
				      काष्ठा perf_sample *sample,
				      काष्ठा evsel *evsel,
				      काष्ठा machine *machine)
अणु
	काष्ठा perf_dअगरf *pdअगरf = container_of(tool, काष्ठा perf_dअगरf, tool);
	काष्ठा addr_location al;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry_iter iter = अणु
		.evsel	= evsel,
		.sample	= sample,
		.ops	= &hist_iter_normal,
	पूर्ण;
	पूर्णांक ret = -1;

	अगर (perf_समय__ranges_skip_sample(pdअगरf->pसमय_range, pdअगरf->range_num,
					  sample->समय)) अणु
		वापस 0;
	पूर्ण

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		pr_warning("problem processing %d event, skipping it.\n",
			   event->header.type);
		वापस -1;
	पूर्ण

	अगर (cpu_list && !test_bit(sample->cpu, cpu_biपंचांगap)) अणु
		ret = 0;
		जाओ out_put;
	पूर्ण

	चयन (compute) अणु
	हाल COMPUTE_CYCLES:
		अगर (!hists__add_entry_ops(hists, &block_hist_ops, &al, शून्य,
					  शून्य, शून्य, sample, true)) अणु
			pr_warning("problem incrementing symbol period, "
				   "skipping event\n");
			जाओ out_put;
		पूर्ण

		hist__account_cycles(sample->branch_stack, &al, sample, false,
				     शून्य);
		अवरोध;

	हाल COMPUTE_STREAM:
		अगर (hist_entry_iter__add(&iter, &al, PERF_MAX_STACK_DEPTH,
					 शून्य)) अणु
			pr_debug("problem adding hist entry, skipping event\n");
			जाओ out_put;
		पूर्ण
		अवरोध;

	शेष:
		अगर (!hists__add_entry(hists, &al, शून्य, शून्य, शून्य, sample,
				      true)) अणु
			pr_warning("problem incrementing symbol period, "
				   "skipping event\n");
			जाओ out_put;
		पूर्ण
	पूर्ण

	/*
	 * The total_period is updated here beक्रमe going to the output
	 * tree since normally only the baseline hists will call
	 * hists__output_resort() and precompute needs the total
	 * period in order to sort entries by percentage delta.
	 */
	hists->stats.total_period += sample->period;
	अगर (!al.filtered)
		hists->stats.total_non_filtered_period += sample->period;
	ret = 0;
out_put:
	addr_location__put(&al);
	वापस ret;
पूर्ण

अटल काष्ठा perf_dअगरf pdअगरf = अणु
	.tool = अणु
		.sample	= dअगरf__process_sample_event,
		.mmap	= perf_event__process_mmap,
		.mmap2	= perf_event__process_mmap2,
		.comm	= perf_event__process_comm,
		.निकास	= perf_event__process_निकास,
		.विभाजन	= perf_event__process_विभाजन,
		.lost	= perf_event__process_lost,
		.namespaces = perf_event__process_namespaces,
		.cgroup = perf_event__process_cgroup,
		.ordered_events = true,
		.ordering_requires_बारtamps = true,
	पूर्ण,
पूर्ण;

अटल काष्ठा evsel *evsel_match(काष्ठा evsel *evsel,
				      काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *e;

	evlist__क्रम_each_entry(evlist, e) अणु
		अगर (evsel__match2(evsel, e))
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम evlist__collapse_resort(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		काष्ठा hists *hists = evsel__hists(evsel);

		hists__collapse_resort(hists, शून्य);
	पूर्ण
पूर्ण

अटल काष्ठा data__file *fmt_to_data_file(काष्ठा perf_hpp_fmt *fmt)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt = container_of(fmt, काष्ठा dअगरf_hpp_fmt, fmt);
	व्योम *ptr = dfmt - dfmt->idx;
	काष्ठा data__file *d = container_of(ptr, काष्ठा data__file, fmt);

	वापस d;
पूर्ण

अटल काष्ठा hist_entry*
get_pair_data(काष्ठा hist_entry *he, काष्ठा data__file *d)
अणु
	अगर (hist_entry__has_pairs(he)) अणु
		काष्ठा hist_entry *pair;

		list_क्रम_each_entry(pair, &he->pairs.head, pairs.node)
			अगर (pair->hists == d->hists)
				वापस pair;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hist_entry*
get_pair_fmt(काष्ठा hist_entry *he, काष्ठा dअगरf_hpp_fmt *dfmt)
अणु
	काष्ठा data__file *d = fmt_to_data_file(&dfmt->fmt);

	वापस get_pair_data(he, d);
पूर्ण

अटल व्योम hists__baseline_only(काष्ठा hists *hists)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *next;

	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	next = rb_first_cached(root);
	जबतक (next != शून्य) अणु
		काष्ठा hist_entry *he = rb_entry(next, काष्ठा hist_entry, rb_node_in);

		next = rb_next(&he->rb_node_in);
		अगर (!hist_entry__next_pair(he)) अणु
			rb_erase_cached(&he->rb_node_in, root);
			hist_entry__delete(he);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक64_t block_cycles_dअगरf_cmp(काष्ठा hist_entry *left,
				     काष्ठा hist_entry *right)
अणु
	bool pairs_left  = hist_entry__has_pairs(left);
	bool pairs_right = hist_entry__has_pairs(right);
	s64 l, r;

	अगर (!pairs_left && !pairs_right)
		वापस 0;

	l = lद_असल(left->dअगरf.cycles);
	r = lद_असल(right->dअगरf.cycles);
	वापस r - l;
पूर्ण

अटल पूर्णांक64_t block_sort(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			  काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस block_cycles_dअगरf_cmp(right, left);
पूर्ण

अटल व्योम init_block_hist(काष्ठा block_hist *bh)
अणु
	__hists__init(&bh->block_hists, &bh->block_list);
	perf_hpp_list__init(&bh->block_list);

	INIT_LIST_HEAD(&bh->block_fmt.list);
	INIT_LIST_HEAD(&bh->block_fmt.sort_list);
	bh->block_fmt.cmp = block_info__cmp;
	bh->block_fmt.sort = block_sort;
	perf_hpp_list__रेजिस्टर_sort_field(&bh->block_list,
					   &bh->block_fmt);
	bh->valid = true;
पूर्ण

अटल काष्ठा hist_entry *get_block_pair(काष्ठा hist_entry *he,
					 काष्ठा hists *hists_pair)
अणु
	काष्ठा rb_root_cached *root = hists_pair->entries_in;
	काष्ठा rb_node *next = rb_first_cached(root);
	पूर्णांक64_t cmp;

	जबतक (next != शून्य) अणु
		काष्ठा hist_entry *he_pair = rb_entry(next, काष्ठा hist_entry,
						      rb_node_in);

		next = rb_next(&he_pair->rb_node_in);

		cmp = __block_info__cmp(he_pair, he);
		अगर (!cmp)
			वापस he_pair;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम init_spark_values(अचिन्हित दीर्घ *svals, पूर्णांक num)
अणु
	क्रम (पूर्णांक i = 0; i < num; i++)
		svals[i] = 0;
पूर्ण

अटल व्योम update_spark_value(अचिन्हित दीर्घ *svals, पूर्णांक num,
			       काष्ठा stats *stats, u64 val)
अणु
	पूर्णांक n = stats->n;

	अगर (n < num)
		svals[n] = val;
पूर्ण

अटल व्योम compute_cycles_dअगरf(काष्ठा hist_entry *he,
				काष्ठा hist_entry *pair)
अणु
	pair->dअगरf.computed = true;
	अगर (pair->block_info->num && he->block_info->num) अणु
		pair->dअगरf.cycles =
			pair->block_info->cycles_aggr / pair->block_info->num_aggr -
			he->block_info->cycles_aggr / he->block_info->num_aggr;

		अगर (!cycles_hist)
			वापस;

		init_stats(&pair->dअगरf.stats);
		init_spark_values(pair->dअगरf.svals, NUM_SPARKS);

		क्रम (पूर्णांक i = 0; i < pair->block_info->num; i++) अणु
			u64 val;

			अगर (i >= he->block_info->num || i >= NUM_SPARKS)
				अवरोध;

			val = lद_असल(pair->block_info->cycles_spark[i] -
				     he->block_info->cycles_spark[i]);

			update_spark_value(pair->dअगरf.svals, NUM_SPARKS,
					   &pair->dअगरf.stats, val);
			update_stats(&pair->dअगरf.stats, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम block_hists_match(काष्ठा hists *hists_base,
			      काष्ठा hists *hists_pair)
अणु
	काष्ठा rb_root_cached *root = hists_base->entries_in;
	काष्ठा rb_node *next = rb_first_cached(root);

	जबतक (next != शून्य) अणु
		काष्ठा hist_entry *he = rb_entry(next, काष्ठा hist_entry,
						 rb_node_in);
		काष्ठा hist_entry *pair = get_block_pair(he, hists_pair);

		next = rb_next(&he->rb_node_in);

		अगर (pair) अणु
			hist_entry__add_pair(pair, he);
			compute_cycles_dअगरf(he, pair);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hists__precompute(काष्ठा hists *hists)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *next;

	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	next = rb_first_cached(root);
	जबतक (next != शून्य) अणु
		काष्ठा block_hist *bh, *pair_bh;
		काष्ठा hist_entry *he, *pair;
		काष्ठा data__file *d;
		पूर्णांक i;

		he   = rb_entry(next, काष्ठा hist_entry, rb_node_in);
		next = rb_next(&he->rb_node_in);

		अगर (compute == COMPUTE_CYCLES) अणु
			bh = container_of(he, काष्ठा block_hist, he);
			init_block_hist(bh);
			block_info__process_sym(he, bh, शून्य, 0);
		पूर्ण

		data__क्रम_each_file_new(i, d) अणु
			pair = get_pair_data(he, d);
			अगर (!pair)
				जारी;

			चयन (compute) अणु
			हाल COMPUTE_DELTA:
			हाल COMPUTE_DELTA_ABS:
				compute_delta(he, pair);
				अवरोध;
			हाल COMPUTE_RATIO:
				compute_ratio(he, pair);
				अवरोध;
			हाल COMPUTE_WEIGHTED_DIFF:
				compute_wdअगरf(he, pair);
				अवरोध;
			हाल COMPUTE_CYCLES:
				pair_bh = container_of(pair, काष्ठा block_hist,
						       he);
				init_block_hist(pair_bh);
				block_info__process_sym(pair, pair_bh, शून्य, 0);

				bh = container_of(he, काष्ठा block_hist, he);

				अगर (bh->valid && pair_bh->valid) अणु
					block_hists_match(&bh->block_hists,
							  &pair_bh->block_hists);
					hists__output_resort(&pair_bh->block_hists,
							     शून्य);
				पूर्ण
				अवरोध;
			शेष:
				BUG_ON(1);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक64_t cmp_द्विगुनs(द्विगुन l, द्विगुन r)
अणु
	अगर (l > r)
		वापस -1;
	अन्यथा अगर (l < r)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक64_t
__hist_entry__cmp_compute(काष्ठा hist_entry *left, काष्ठा hist_entry *right,
			पूर्णांक c)
अणु
	चयन (c) अणु
	हाल COMPUTE_DELTA:
	अणु
		द्विगुन l = left->dअगरf.period_ratio_delta;
		द्विगुन r = right->dअगरf.period_ratio_delta;

		वापस cmp_द्विगुनs(l, r);
	पूर्ण
	हाल COMPUTE_DELTA_ABS:
	अणु
		द्विगुन l = भ_असल(left->dअगरf.period_ratio_delta);
		द्विगुन r = भ_असल(right->dअगरf.period_ratio_delta);

		वापस cmp_द्विगुनs(l, r);
	पूर्ण
	हाल COMPUTE_RATIO:
	अणु
		द्विगुन l = left->dअगरf.period_ratio;
		द्विगुन r = right->dअगरf.period_ratio;

		वापस cmp_द्विगुनs(l, r);
	पूर्ण
	हाल COMPUTE_WEIGHTED_DIFF:
	अणु
		s64 l = left->dअगरf.wdअगरf;
		s64 r = right->dअगरf.wdअगरf;

		वापस r - l;
	पूर्ण
	शेष:
		BUG_ON(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_compute(काष्ठा hist_entry *left, काष्ठा hist_entry *right,
			पूर्णांक c, पूर्णांक sort_idx)
अणु
	bool pairs_left  = hist_entry__has_pairs(left);
	bool pairs_right = hist_entry__has_pairs(right);
	काष्ठा hist_entry *p_right, *p_left;

	अगर (!pairs_left && !pairs_right)
		वापस 0;

	अगर (!pairs_left || !pairs_right)
		वापस pairs_left ? -1 : 1;

	p_left  = get_pair_data(left,  &data__files[sort_idx]);
	p_right = get_pair_data(right, &data__files[sort_idx]);

	अगर (!p_left && !p_right)
		वापस 0;

	अगर (!p_left || !p_right)
		वापस p_left ? -1 : 1;

	/*
	 * We have 2 entries of same kind, let's
	 * make the data comparison.
	 */
	वापस __hist_entry__cmp_compute(p_left, p_right, c);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_compute_idx(काष्ठा hist_entry *left, काष्ठा hist_entry *right,
			    पूर्णांक c, पूर्णांक sort_idx)
अणु
	काष्ठा hist_entry *p_right, *p_left;

	p_left  = get_pair_data(left,  &data__files[sort_idx]);
	p_right = get_pair_data(right, &data__files[sort_idx]);

	अगर (!p_left && !p_right)
		वापस 0;

	अगर (!p_left || !p_right)
		वापस p_left ? -1 : 1;

	अगर (c != COMPUTE_DELTA && c != COMPUTE_DELTA_ABS) अणु
		/*
		 * The delta can be computed without the baseline, but
		 * others are not.  Put those entries which have no
		 * values below.
		 */
		अगर (left->dummy && right->dummy)
			वापस 0;

		अगर (left->dummy || right->dummy)
			वापस left->dummy ? 1 : -1;
	पूर्ण

	वापस __hist_entry__cmp_compute(p_left, p_right, c);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_nop(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
		    काष्ठा hist_entry *left __maybe_unused,
		    काष्ठा hist_entry *right __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_baseline(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			 काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (left->stat.period == right->stat.period)
		वापस 0;
	वापस left->stat.period > right->stat.period ? 1 : -1;
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_delta(काष्ठा perf_hpp_fmt *fmt,
		      काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा data__file *d = fmt_to_data_file(fmt);

	वापस hist_entry__cmp_compute(right, left, COMPUTE_DELTA, d->idx);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_delta_असल(काष्ठा perf_hpp_fmt *fmt,
		      काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा data__file *d = fmt_to_data_file(fmt);

	वापस hist_entry__cmp_compute(right, left, COMPUTE_DELTA_ABS, d->idx);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_ratio(काष्ठा perf_hpp_fmt *fmt,
		      काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा data__file *d = fmt_to_data_file(fmt);

	वापस hist_entry__cmp_compute(right, left, COMPUTE_RATIO, d->idx);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_wdअगरf(काष्ठा perf_hpp_fmt *fmt,
		      काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा data__file *d = fmt_to_data_file(fmt);

	वापस hist_entry__cmp_compute(right, left, COMPUTE_WEIGHTED_DIFF, d->idx);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_delta_idx(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			  काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस hist_entry__cmp_compute_idx(right, left, COMPUTE_DELTA,
					   sort_compute);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_delta_असल_idx(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			      काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस hist_entry__cmp_compute_idx(right, left, COMPUTE_DELTA_ABS,
					   sort_compute);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_ratio_idx(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			  काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस hist_entry__cmp_compute_idx(right, left, COMPUTE_RATIO,
					   sort_compute);
पूर्ण

अटल पूर्णांक64_t
hist_entry__cmp_wdअगरf_idx(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			  काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस hist_entry__cmp_compute_idx(right, left, COMPUTE_WEIGHTED_DIFF,
					   sort_compute);
पूर्ण

अटल व्योम hists__process(काष्ठा hists *hists)
अणु
	अगर (show_baseline_only)
		hists__baseline_only(hists);

	hists__precompute(hists);
	hists__output_resort(hists, शून्य);

	अगर (compute == COMPUTE_CYCLES)
		symbol_conf.report_block = true;

	hists__ख_लिखो(hists, !quiet, 0, 0, 0, मानक_निकास,
		       !symbol_conf.use_callchain);
पूर्ण

अटल व्योम data__ख_लिखो(व्योम)
अणु
	काष्ठा data__file *d;
	पूर्णांक i;

	ख_लिखो(मानक_निकास, "# Data files:\n");

	data__क्रम_each_file(i, d)
		ख_लिखो(मानक_निकास, "#  [%d] %s %s\n",
			d->idx, d->data.path,
			!d->idx ? "(Baseline)" : "");

	ख_लिखो(मानक_निकास, "#\n");
पूर्ण

अटल व्योम data_process(व्योम)
अणु
	काष्ठा evlist *evlist_base = data__files[0].session->evlist;
	काष्ठा evsel *evsel_base;
	bool first = true;

	evlist__क्रम_each_entry(evlist_base, evsel_base) अणु
		काष्ठा hists *hists_base = evsel__hists(evsel_base);
		काष्ठा data__file *d;
		पूर्णांक i;

		data__क्रम_each_file_new(i, d) अणु
			काष्ठा evlist *evlist = d->session->evlist;
			काष्ठा evsel *evsel;
			काष्ठा hists *hists;

			evsel = evsel_match(evsel_base, evlist);
			अगर (!evsel)
				जारी;

			hists = evsel__hists(evsel);
			d->hists = hists;

			hists__match(hists_base, hists);

			अगर (!show_baseline_only)
				hists__link(hists_base, hists);
		पूर्ण

		अगर (!quiet) अणु
			ख_लिखो(मानक_निकास, "%s# Event '%s'\n#\n", first ? "" : "\n",
				evsel__name(evsel_base));
		पूर्ण

		first = false;

		अगर (verbose > 0 || ((data__files_cnt > 2) && !quiet))
			data__ख_लिखो();

		/* Don't sort callchain क्रम perf dअगरf */
		evsel__reset_sample_bit(evsel_base, CALLCHAIN);

		hists__process(hists_base);
	पूर्ण
पूर्ण

अटल पूर्णांक process_base_stream(काष्ठा data__file *data_base,
			       काष्ठा data__file *data_pair,
			       स्थिर अक्षर *title __maybe_unused)
अणु
	काष्ठा evlist *evlist_base = data_base->session->evlist;
	काष्ठा evlist *evlist_pair = data_pair->session->evlist;
	काष्ठा evsel *evsel_base, *evsel_pair;
	काष्ठा evsel_streams *es_base, *es_pair;

	evlist__क्रम_each_entry(evlist_base, evsel_base) अणु
		evsel_pair = evsel_match(evsel_base, evlist_pair);
		अगर (!evsel_pair)
			जारी;

		es_base = evsel_streams__entry(data_base->evlist_streams,
					       evsel_base->idx);
		अगर (!es_base)
			वापस -1;

		es_pair = evsel_streams__entry(data_pair->evlist_streams,
					       evsel_pair->idx);
		अगर (!es_pair)
			वापस -1;

		evsel_streams__match(es_base, es_pair);
		evsel_streams__report(es_base, es_pair);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम stream_process(व्योम)
अणु
	/*
	 * Stream comparison only supports two data files.
	 * perf.data.old and perf.data. data__files[0] is perf.data.old,
	 * data__files[1] is perf.data.
	 */
	process_base_stream(&data__files[0], &data__files[1],
			    "# Output based on old perf data:\n#\n");
पूर्ण

अटल व्योम data__मुक्त(काष्ठा data__file *d)
अणु
	पूर्णांक col;

	अगर (d->evlist_streams)
		evlist_streams__delete(d->evlist_streams);

	क्रम (col = 0; col < PERF_HPP_DIFF__MAX_INDEX; col++) अणु
		काष्ठा dअगरf_hpp_fmt *fmt = &d->fmt[col];

		zमुक्त(&fmt->header);
	पूर्ण
पूर्ण

अटल पूर्णांक असलसमय_str_dup(अक्षर **pstr)
अणु
	अक्षर *str = शून्य;

	अगर (pdअगरf.समय_str && म_अक्षर(pdअगरf.समय_str, ':')) अणु
		str = strdup(pdअगरf.समय_str);
		अगर (!str)
			वापस -ENOMEM;
	पूर्ण

	*pstr = str;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_असलolute_समय(काष्ठा data__file *d, अक्षर **pstr)
अणु
	अक्षर *p = *pstr;
	पूर्णांक ret;

	/*
	 * Absolute बारtamp क्रम one file has the क्रमmat: a.b,c.d
	 * For multiple files, the क्रमmat is: a.b,c.d:a.b,c.d
	 */
	p = म_अक्षर(*pstr, ':');
	अगर (p) अणु
		अगर (p == *pstr) अणु
			pr_err("Invalid time string\n");
			वापस -EINVAL;
		पूर्ण

		*p = 0;
		p++;
		अगर (*p == 0) अणु
			pr_err("Invalid time string\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = perf_समय__parse_क्रम_ranges(*pstr, d->session,
					  &pdअगरf.pसमय_range,
					  &pdअगरf.range_size,
					  &pdअगरf.range_num);
	अगर (ret < 0)
		वापस ret;

	अगर (!p || *p == 0)
		*pstr = शून्य;
	अन्यथा
		*pstr = p;

	वापस ret;
पूर्ण

अटल पूर्णांक parse_percent_समय(काष्ठा data__file *d)
अणु
	पूर्णांक ret;

	ret = perf_समय__parse_क्रम_ranges(pdअगरf.समय_str, d->session,
					  &pdअगरf.pसमय_range,
					  &pdअगरf.range_size,
					  &pdअगरf.range_num);
	वापस ret;
पूर्ण

अटल पूर्णांक parse_समय_str(काष्ठा data__file *d, अक्षर *असलसमय_ostr,
			   अक्षर **pअसलसमय_प्रकारmp)
अणु
	पूर्णांक ret = 0;

	अगर (असलसमय_ostr)
		ret = parse_असलolute_समय(d, pअसलसमय_प्रकारmp);
	अन्यथा अगर (pdअगरf.समय_str)
		ret = parse_percent_समय(d);

	वापस ret;
पूर्ण

अटल पूर्णांक check_file_brstack(व्योम)
अणु
	काष्ठा data__file *d;
	bool has_br_stack;
	पूर्णांक i;

	data__क्रम_each_file(i, d) अणु
		d->session = perf_session__new(&d->data, false, &pdअगरf.tool);
		अगर (IS_ERR(d->session)) अणु
			pr_err("Failed to open %s\n", d->data.path);
			वापस PTR_ERR(d->session);
		पूर्ण

		has_br_stack = perf_header__has_feat(&d->session->header,
						     HEADER_BRANCH_STACK);
		perf_session__delete(d->session);
		अगर (!has_br_stack)
			वापस 0;
	पूर्ण

	/* Set only all files having branch stacks */
	pdअगरf.has_br_stack = true;
	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_dअगरf(व्योम)
अणु
	काष्ठा data__file *d;
	पूर्णांक ret, i;
	अक्षर *असलसमय_ostr, *असलसमय_प्रकारmp;

	ret = असलसमय_str_dup(&असलसमय_ostr);
	अगर (ret)
		वापस ret;

	असलसमय_प्रकारmp = असलसमय_ostr;
	ret = -EINVAL;

	data__क्रम_each_file(i, d) अणु
		d->session = perf_session__new(&d->data, false, &pdअगरf.tool);
		अगर (IS_ERR(d->session)) अणु
			ret = PTR_ERR(d->session);
			pr_err("Failed to open %s\n", d->data.path);
			जाओ out_delete;
		पूर्ण

		अगर (pdअगरf.समय_str) अणु
			ret = parse_समय_str(d, असलसमय_ostr, &असलसमय_प्रकारmp);
			अगर (ret < 0)
				जाओ out_delete;
		पूर्ण

		अगर (cpu_list) अणु
			ret = perf_session__cpu_biपंचांगap(d->session, cpu_list,
						       cpu_biपंचांगap);
			अगर (ret < 0)
				जाओ out_delete;
		पूर्ण

		ret = perf_session__process_events(d->session);
		अगर (ret) अणु
			pr_err("Failed to process %s\n", d->data.path);
			जाओ out_delete;
		पूर्ण

		evlist__collapse_resort(d->session->evlist);

		अगर (pdअगरf.pसमय_range)
			zमुक्त(&pdअगरf.pसमय_range);

		अगर (compute == COMPUTE_STREAM) अणु
			d->evlist_streams = evlist__create_streams(
						d->session->evlist, 5);
			अगर (!d->evlist_streams) अणु
				ret = -ENOMEM;
				जाओ out_delete;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (compute == COMPUTE_STREAM)
		stream_process();
	अन्यथा
		data_process();

 out_delete:
	data__क्रम_each_file(i, d) अणु
		अगर (!IS_ERR(d->session))
			perf_session__delete(d->session);
		data__मुक्त(d);
	पूर्ण

	मुक्त(data__files);

	अगर (pdअगरf.pसमय_range)
		zमुक्त(&pdअगरf.pसमय_range);

	अगर (असलसमय_ostr)
		मुक्त(असलसमय_ostr);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर dअगरf_usage[] = अणु
	"perf diff [<options>] [old_file] [new_file]",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('q', "quiet", &quiet, "Do not show any message"),
	OPT_BOOLEAN('b', "baseline-only", &show_baseline_only,
		    "Show only items with match in baseline"),
	OPT_CALLBACK('c', "compute", &compute,
		     "delta,delta-abs,ratio,wdiff:w1,w2 (default delta-abs),cycles",
		     "Entries differential computation selection",
		     setup_compute),
	OPT_BOOLEAN('p', "period", &show_period,
		    "Show period values."),
	OPT_BOOLEAN('F', "formula", &show_क्रमmula,
		    "Show formula."),
	OPT_BOOLEAN(0, "cycles-hist", &cycles_hist,
		    "Show cycles histogram and standard deviation "
		    "- WARNING: use only with -c cycles."),
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace,
		    "dump raw trace in ASCII"),
	OPT_BOOLEAN('f', "force", &force, "don't complain, करो it"),
	OPT_STRING(0, "kallsyms", &symbol_conf.kallsyms_name,
		   "file", "kallsyms pathname"),
	OPT_BOOLEAN('m', "modules", &symbol_conf.use_modules,
		    "load module symbols - WARNING: use only with -k and LIVE kernel"),
	OPT_STRING('d', "dsos", &symbol_conf.dso_list_str, "dso[,dso...]",
		   "only consider symbols in these dsos"),
	OPT_STRING('C', "comms", &symbol_conf.comm_list_str, "comm[,comm...]",
		   "only consider symbols in these comms"),
	OPT_STRING('S', "symbols", &symbol_conf.sym_list_str, "symbol[,symbol...]",
		   "only consider these symbols"),
	OPT_STRING('s', "sort", &sort_order, "key[,key2...]",
		   "sort by key(s): pid, comm, dso, symbol, parent, cpu, srcline, ..."
		   " Please refer the man page for the complete list."),
	OPT_STRING_NOEMPTY('t', "field-separator", &symbol_conf.field_sep, "separator",
		   "separator for columns, no spaces will be added between "
		   "columns '.' is reserved."),
	OPT_CALLBACK(0, "symfs", शून्य, "directory",
		     "Look for files with symbols relative to this directory",
		     symbol__config_symfs),
	OPT_UINTEGER('o', "order", &sort_compute, "Specify compute sorting."),
	OPT_CALLBACK(0, "percentage", शून्य, "relative|absolute",
		     "How to display percentage of filtered entries", parse_filter_percentage),
	OPT_STRING(0, "time", &pdअगरf.समय_str, "str",
		   "Time span (time percent or absolute timestamp)"),
	OPT_STRING(0, "cpu", &cpu_list, "cpu", "list of cpus to profile"),
	OPT_STRING(0, "pid", &symbol_conf.pid_list_str, "pid[,pid...]",
		   "only consider symbols in these pids"),
	OPT_STRING(0, "tid", &symbol_conf.tid_list_str, "tid[,tid...]",
		   "only consider symbols in these tids"),
	OPT_BOOLEAN(0, "stream", &pdअगरf.stream,
		    "Enable hot streams comparison."),
	OPT_END()
पूर्ण;

अटल द्विगुन baseline_percent(काष्ठा hist_entry *he)
अणु
	u64 total = hists__total_period(he->hists);

	वापस 100.0 * he->stat.period / total;
पूर्ण

अटल पूर्णांक hpp__color_baseline(काष्ठा perf_hpp_fmt *fmt,
			       काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt =
		container_of(fmt, काष्ठा dअगरf_hpp_fmt, fmt);
	द्विगुन percent = baseline_percent(he);
	अक्षर pfmt[20] = " ";

	अगर (!he->dummy) अणु
		scnम_लिखो(pfmt, 20, "%%%d.2f%%%%", dfmt->header_width - 1);
		वापस percent_color_snम_लिखो(hpp->buf, hpp->size,
					      pfmt, percent);
	पूर्ण अन्यथा
		वापस scnम_लिखो(hpp->buf, hpp->size, "%*s",
				 dfmt->header_width, pfmt);
पूर्ण

अटल पूर्णांक hpp__entry_baseline(काष्ठा hist_entry *he, अक्षर *buf, माप_प्रकार size)
अणु
	द्विगुन percent = baseline_percent(he);
	स्थिर अक्षर *fmt = symbol_conf.field_sep ? "%.2f" : "%6.2f%%";
	पूर्णांक ret = 0;

	अगर (!he->dummy)
		ret = scnम_लिखो(buf, size, fmt, percent);

	वापस ret;
पूर्ण

अटल पूर्णांक cycles_म_लिखो(काष्ठा hist_entry *he, काष्ठा hist_entry *pair,
			 काष्ठा perf_hpp *hpp, पूर्णांक width)
अणु
	काष्ठा block_hist *bh = container_of(he, काष्ठा block_hist, he);
	काष्ठा block_hist *bh_pair = container_of(pair, काष्ठा block_hist, he);
	काष्ठा hist_entry *block_he;
	काष्ठा block_info *bi;
	अक्षर buf[128];
	अक्षर *start_line, *end_line;

	block_he = hists__get_entry(&bh_pair->block_hists, bh->block_idx);
	अगर (!block_he) अणु
		hpp->skip = true;
		वापस 0;
	पूर्ण

	/*
	 * Aव्योम prपूर्णांकing the warning "addr2line_init failed for ..."
	 */
	symbol_conf.disable_add2line_warn = true;

	bi = block_he->block_info;

	start_line = map__srcline(he->ms.map, bi->sym->start + bi->start,
				  he->ms.sym);

	end_line = map__srcline(he->ms.map, bi->sym->start + bi->end,
				he->ms.sym);

	अगर ((म_भेदन(start_line, SRCLINE_UNKNOWN, म_माप(SRCLINE_UNKNOWN)) != 0) &&
	    (म_भेदन(end_line, SRCLINE_UNKNOWN, म_माप(SRCLINE_UNKNOWN)) != 0)) अणु
		scnम_लिखो(buf, माप(buf), "[%s -> %s] %4ld",
			  start_line, end_line, block_he->dअगरf.cycles);
	पूर्ण अन्यथा अणु
		scnम_लिखो(buf, माप(buf), "[%7lx -> %7lx] %4ld",
			  bi->start, bi->end, block_he->dअगरf.cycles);
	पूर्ण

	मुक्त_srcline(start_line);
	मुक्त_srcline(end_line);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", width, buf);
पूर्ण

अटल पूर्णांक __hpp__color_compare(काष्ठा perf_hpp_fmt *fmt,
				काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he,
				पूर्णांक comparison_method)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt =
		container_of(fmt, काष्ठा dअगरf_hpp_fmt, fmt);
	काष्ठा hist_entry *pair = get_pair_fmt(he, dfmt);
	द्विगुन dअगरf;
	s64 wdअगरf;
	अक्षर pfmt[20] = " ";

	अगर (!pair) अणु
		अगर (comparison_method == COMPUTE_CYCLES) अणु
			काष्ठा block_hist *bh;

			bh = container_of(he, काष्ठा block_hist, he);
			अगर (bh->block_idx)
				hpp->skip = true;
		पूर्ण

		जाओ no_prपूर्णांक;
	पूर्ण

	चयन (comparison_method) अणु
	हाल COMPUTE_DELTA:
		अगर (pair->dअगरf.computed)
			dअगरf = pair->dअगरf.period_ratio_delta;
		अन्यथा
			dअगरf = compute_delta(he, pair);

		scnम_लिखो(pfmt, 20, "%%%+d.2f%%%%", dfmt->header_width - 1);
		वापस percent_color_snम_लिखो(hpp->buf, hpp->size,
					pfmt, dअगरf);
	हाल COMPUTE_RATIO:
		अगर (he->dummy)
			जाओ dummy_prपूर्णांक;
		अगर (pair->dअगरf.computed)
			dअगरf = pair->dअगरf.period_ratio;
		अन्यथा
			dअगरf = compute_ratio(he, pair);

		scnम_लिखो(pfmt, 20, "%%%d.6f", dfmt->header_width);
		वापस value_color_snम_लिखो(hpp->buf, hpp->size,
					pfmt, dअगरf);
	हाल COMPUTE_WEIGHTED_DIFF:
		अगर (he->dummy)
			जाओ dummy_prपूर्णांक;
		अगर (pair->dअगरf.computed)
			wdअगरf = pair->dअगरf.wdअगरf;
		अन्यथा
			wdअगरf = compute_wdअगरf(he, pair);

		scnम_लिखो(pfmt, 20, "%%14ld", dfmt->header_width);
		वापस color_snम_लिखो(hpp->buf, hpp->size,
				get_percent_color(wdअगरf),
				pfmt, wdअगरf);
	हाल COMPUTE_CYCLES:
		वापस cycles_म_लिखो(he, pair, hpp, dfmt->header_width);
	शेष:
		BUG_ON(1);
	पूर्ण
dummy_prपूर्णांक:
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s",
			dfmt->header_width, "N/A");
no_prपूर्णांक:
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s",
			dfmt->header_width, pfmt);
पूर्ण

अटल पूर्णांक hpp__color_delta(काष्ठा perf_hpp_fmt *fmt,
			काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	वापस __hpp__color_compare(fmt, hpp, he, COMPUTE_DELTA);
पूर्ण

अटल पूर्णांक hpp__color_ratio(काष्ठा perf_hpp_fmt *fmt,
			काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	वापस __hpp__color_compare(fmt, hpp, he, COMPUTE_RATIO);
पूर्ण

अटल पूर्णांक hpp__color_wdअगरf(काष्ठा perf_hpp_fmt *fmt,
			काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	वापस __hpp__color_compare(fmt, hpp, he, COMPUTE_WEIGHTED_DIFF);
पूर्ण

अटल पूर्णांक hpp__color_cycles(काष्ठा perf_hpp_fmt *fmt,
			     काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	वापस __hpp__color_compare(fmt, hpp, he, COMPUTE_CYCLES);
पूर्ण

अटल पूर्णांक all_zero(अचिन्हित दीर्घ *vals, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (vals[i] != 0)
			वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक prपूर्णांक_cycles_spark(अक्षर *bf, पूर्णांक size, अचिन्हित दीर्घ *svals, u64 n)
अणु
	पूर्णांक prपूर्णांकed;

	अगर (n <= 1)
		वापस 0;

	अगर (n > NUM_SPARKS)
		n = NUM_SPARKS;
	अगर (all_zero(svals, n))
		वापस 0;

	prपूर्णांकed = prपूर्णांक_spark(bf, size, svals, n);
	prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, " ");
	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक hpp__color_cycles_hist(काष्ठा perf_hpp_fmt *fmt,
			    काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt =
		container_of(fmt, काष्ठा dअगरf_hpp_fmt, fmt);
	काष्ठा hist_entry *pair = get_pair_fmt(he, dfmt);
	काष्ठा block_hist *bh = container_of(he, काष्ठा block_hist, he);
	काष्ठा block_hist *bh_pair;
	काष्ठा hist_entry *block_he;
	अक्षर spark[32], buf[128];
	द्विगुन r;
	पूर्णांक ret, pad;

	अगर (!pair) अणु
		अगर (bh->block_idx)
			hpp->skip = true;

		जाओ no_prपूर्णांक;
	पूर्ण

	bh_pair = container_of(pair, काष्ठा block_hist, he);

	block_he = hists__get_entry(&bh_pair->block_hists, bh->block_idx);
	अगर (!block_he) अणु
		hpp->skip = true;
		जाओ no_prपूर्णांक;
	पूर्ण

	ret = prपूर्णांक_cycles_spark(spark, माप(spark), block_he->dअगरf.svals,
				 block_he->dअगरf.stats.n);

	r = rel_stddev_stats(stddev_stats(&block_he->dअगरf.stats),
			     avg_stats(&block_he->dअगरf.stats));

	अगर (ret) अणु
		/*
		 * Padding spaces अगर number of sparks less than NUM_SPARKS
		 * otherwise the output is not aligned.
		 */
		pad = NUM_SPARKS - ((ret - 1) / 3);
		scnम_लिखो(buf, माप(buf), "%s%5.1f%% %s", "\u00B1", r, spark);
		ret = scnम_लिखो(hpp->buf, hpp->size, "%*s",
				dfmt->header_width, buf);

		अगर (pad) अणु
			ret += scnम_लिखो(hpp->buf + ret, hpp->size - ret,
					 "%-*s", pad, " ");
		पूर्ण

		वापस ret;
	पूर्ण

no_prपूर्णांक:
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s",
			dfmt->header_width, " ");
पूर्ण

अटल व्योम
hpp__entry_unpair(काष्ठा hist_entry *he, पूर्णांक idx, अक्षर *buf, माप_प्रकार size)
अणु
	चयन (idx) अणु
	हाल PERF_HPP_DIFF__PERIOD_BASELINE:
		scnम_लिखो(buf, size, "%" PRIu64, he->stat.period);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
hpp__entry_pair(काष्ठा hist_entry *he, काष्ठा hist_entry *pair,
		पूर्णांक idx, अक्षर *buf, माप_प्रकार size)
अणु
	द्विगुन dअगरf;
	द्विगुन ratio;
	s64 wdअगरf;

	चयन (idx) अणु
	हाल PERF_HPP_DIFF__DELTA:
	हाल PERF_HPP_DIFF__DELTA_ABS:
		अगर (pair->dअगरf.computed)
			dअगरf = pair->dअगरf.period_ratio_delta;
		अन्यथा
			dअगरf = compute_delta(he, pair);

		scnम_लिखो(buf, size, "%+4.2F%%", dअगरf);
		अवरोध;

	हाल PERF_HPP_DIFF__RATIO:
		/* No poपूर्णांक क्रम ratio number अगर we are dummy.. */
		अगर (he->dummy) अणु
			scnम_लिखो(buf, size, "N/A");
			अवरोध;
		पूर्ण

		अगर (pair->dअगरf.computed)
			ratio = pair->dअगरf.period_ratio;
		अन्यथा
			ratio = compute_ratio(he, pair);

		अगर (ratio > 0.0)
			scnम_लिखो(buf, size, "%14.6F", ratio);
		अवरोध;

	हाल PERF_HPP_DIFF__WEIGHTED_DIFF:
		/* No poपूर्णांक क्रम wdअगरf number अगर we are dummy.. */
		अगर (he->dummy) अणु
			scnम_लिखो(buf, size, "N/A");
			अवरोध;
		पूर्ण

		अगर (pair->dअगरf.computed)
			wdअगरf = pair->dअगरf.wdअगरf;
		अन्यथा
			wdअगरf = compute_wdअगरf(he, pair);

		अगर (wdअगरf != 0)
			scnम_लिखो(buf, size, "%14ld", wdअगरf);
		अवरोध;

	हाल PERF_HPP_DIFF__FORMULA:
		क्रमmula_ख_लिखो(he, pair, buf, size);
		अवरोध;

	हाल PERF_HPP_DIFF__PERIOD:
		scnम_लिखो(buf, size, "%" PRIu64, pair->stat.period);
		अवरोध;

	शेष:
		BUG_ON(1);
	पूर्ण
पूर्ण

अटल व्योम
__hpp__entry_global(काष्ठा hist_entry *he, काष्ठा dअगरf_hpp_fmt *dfmt,
		    अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा hist_entry *pair = get_pair_fmt(he, dfmt);
	पूर्णांक idx = dfmt->idx;

	/* baseline is special */
	अगर (idx == PERF_HPP_DIFF__BASELINE)
		hpp__entry_baseline(he, buf, size);
	अन्यथा अणु
		अगर (pair)
			hpp__entry_pair(he, pair, idx, buf, size);
		अन्यथा
			hpp__entry_unpair(he, idx, buf, size);
	पूर्ण
पूर्ण

अटल पूर्णांक hpp__entry_global(काष्ठा perf_hpp_fmt *_fmt, काष्ठा perf_hpp *hpp,
			     काष्ठा hist_entry *he)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt =
		container_of(_fmt, काष्ठा dअगरf_hpp_fmt, fmt);
	अक्षर buf[MAX_COL_WIDTH] = " ";

	__hpp__entry_global(he, dfmt, buf, MAX_COL_WIDTH);

	अगर (symbol_conf.field_sep)
		वापस scnम_लिखो(hpp->buf, hpp->size, "%s", buf);
	अन्यथा
		वापस scnम_लिखो(hpp->buf, hpp->size, "%*s",
				 dfmt->header_width, buf);
पूर्ण

अटल पूर्णांक hpp__header(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		       काष्ठा hists *hists __maybe_unused,
		       पूर्णांक line __maybe_unused,
		       पूर्णांक *span __maybe_unused)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt =
		container_of(fmt, काष्ठा dअगरf_hpp_fmt, fmt);

	BUG_ON(!dfmt->header);
	वापस scnम_लिखो(hpp->buf, hpp->size, dfmt->header);
पूर्ण

अटल पूर्णांक hpp__width(काष्ठा perf_hpp_fmt *fmt,
		      काष्ठा perf_hpp *hpp __maybe_unused,
		      काष्ठा hists *hists __maybe_unused)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt =
		container_of(fmt, काष्ठा dअगरf_hpp_fmt, fmt);

	BUG_ON(dfmt->header_width <= 0);
	वापस dfmt->header_width;
पूर्ण

अटल व्योम init_header(काष्ठा data__file *d, काष्ठा dअगरf_hpp_fmt *dfmt)
अणु
#घोषणा MAX_HEADER_NAME 100
	अक्षर buf_indent[MAX_HEADER_NAME];
	अक्षर buf[MAX_HEADER_NAME];
	स्थिर अक्षर *header = शून्य;
	पूर्णांक width = 0;

	BUG_ON(dfmt->idx >= PERF_HPP_DIFF__MAX_INDEX);
	header = columns[dfmt->idx].name;
	width  = columns[dfmt->idx].width;

	/* Only our defined HPP fmts should appear here. */
	BUG_ON(!header);

	अगर (data__files_cnt > 2)
		scnम_लिखो(buf, MAX_HEADER_NAME, "%s/%d", header, d->idx);

#घोषणा NAME (data__files_cnt > 2 ? buf : header)
	dfmt->header_width = width;
	width = (पूर्णांक) म_माप(NAME);
	अगर (dfmt->header_width < width)
		dfmt->header_width = width;

	scnम_लिखो(buf_indent, MAX_HEADER_NAME, "%*s",
		  dfmt->header_width, NAME);

	dfmt->header = strdup(buf_indent);
#अघोषित MAX_HEADER_NAME
#अघोषित NAME
पूर्ण

अटल व्योम data__hpp_रेजिस्टर(काष्ठा data__file *d, पूर्णांक idx)
अणु
	काष्ठा dअगरf_hpp_fmt *dfmt = &d->fmt[idx];
	काष्ठा perf_hpp_fmt *fmt = &dfmt->fmt;

	dfmt->idx = idx;

	fmt->header = hpp__header;
	fmt->width  = hpp__width;
	fmt->entry  = hpp__entry_global;
	fmt->cmp    = hist_entry__cmp_nop;
	fmt->collapse = hist_entry__cmp_nop;

	/* TODO more colors */
	चयन (idx) अणु
	हाल PERF_HPP_DIFF__BASELINE:
		fmt->color = hpp__color_baseline;
		fmt->sort  = hist_entry__cmp_baseline;
		अवरोध;
	हाल PERF_HPP_DIFF__DELTA:
		fmt->color = hpp__color_delta;
		fmt->sort  = hist_entry__cmp_delta;
		अवरोध;
	हाल PERF_HPP_DIFF__RATIO:
		fmt->color = hpp__color_ratio;
		fmt->sort  = hist_entry__cmp_ratio;
		अवरोध;
	हाल PERF_HPP_DIFF__WEIGHTED_DIFF:
		fmt->color = hpp__color_wdअगरf;
		fmt->sort  = hist_entry__cmp_wdअगरf;
		अवरोध;
	हाल PERF_HPP_DIFF__DELTA_ABS:
		fmt->color = hpp__color_delta;
		fmt->sort  = hist_entry__cmp_delta_असल;
		अवरोध;
	हाल PERF_HPP_DIFF__CYCLES:
		fmt->color = hpp__color_cycles;
		fmt->sort  = hist_entry__cmp_nop;
		अवरोध;
	हाल PERF_HPP_DIFF__CYCLES_HIST:
		fmt->color = hpp__color_cycles_hist;
		fmt->sort  = hist_entry__cmp_nop;
		अवरोध;
	शेष:
		fmt->sort  = hist_entry__cmp_nop;
		अवरोध;
	पूर्ण

	init_header(d, dfmt);
	perf_hpp__column_रेजिस्टर(fmt);
	perf_hpp__रेजिस्टर_sort_field(fmt);
पूर्ण

अटल पूर्णांक ui_init(व्योम)
अणु
	काष्ठा data__file *d;
	काष्ठा perf_hpp_fmt *fmt;
	पूर्णांक i;

	data__क्रम_each_file(i, d) अणु

		/*
		 * Baseline or compute related columns:
		 *
		 *   PERF_HPP_DIFF__BASELINE
		 *   PERF_HPP_DIFF__DELTA
		 *   PERF_HPP_DIFF__RATIO
		 *   PERF_HPP_DIFF__WEIGHTED_DIFF
		 *   PERF_HPP_DIFF__CYCLES
		 */
		data__hpp_रेजिस्टर(d, i ? compute_2_hpp[compute] :
					  PERF_HPP_DIFF__BASELINE);

		अगर (cycles_hist && i)
			data__hpp_रेजिस्टर(d, PERF_HPP_DIFF__CYCLES_HIST);

		/*
		 * And the rest:
		 *
		 * PERF_HPP_DIFF__FORMULA
		 * PERF_HPP_DIFF__PERIOD
		 * PERF_HPP_DIFF__PERIOD_BASELINE
		 */
		अगर (show_क्रमmula && i)
			data__hpp_रेजिस्टर(d, PERF_HPP_DIFF__FORMULA);

		अगर (show_period)
			data__hpp_रेजिस्टर(d, i ? PERF_HPP_DIFF__PERIOD :
						  PERF_HPP_DIFF__PERIOD_BASELINE);
	पूर्ण

	अगर (!sort_compute)
		वापस 0;

	/*
	 * Prepend an fmt to sort on columns at 'sort_compute' first.
	 * This fmt is added only to the sort list but not to the
	 * output fields list.
	 *
	 * Note that this column (data) can be compared twice - one
	 * क्रम this 'sort_compute' fmt and another क्रम the normal
	 * dअगरf_hpp_fmt.  But it shouldn't a problem as most entries
	 * will be sorted out by first try or baseline and comparing
	 * is not a costly operation.
	 */
	fmt = zalloc(माप(*fmt));
	अगर (fmt == शून्य) अणु
		pr_err("Memory allocation failed\n");
		वापस -1;
	पूर्ण

	fmt->cmp      = hist_entry__cmp_nop;
	fmt->collapse = hist_entry__cmp_nop;

	चयन (compute) अणु
	हाल COMPUTE_DELTA:
		fmt->sort = hist_entry__cmp_delta_idx;
		अवरोध;
	हाल COMPUTE_RATIO:
		fmt->sort = hist_entry__cmp_ratio_idx;
		अवरोध;
	हाल COMPUTE_WEIGHTED_DIFF:
		fmt->sort = hist_entry__cmp_wdअगरf_idx;
		अवरोध;
	हाल COMPUTE_DELTA_ABS:
		fmt->sort = hist_entry__cmp_delta_असल_idx;
		अवरोध;
	हाल COMPUTE_CYCLES:
		/*
		 * Should set since 'fmt->sort' is called without
		 * checking valid during sorting
		 */
		fmt->sort = hist_entry__cmp_nop;
		अवरोध;
	शेष:
		BUG_ON(1);
	पूर्ण

	perf_hpp__prepend_sort_field(fmt);
	वापस 0;
पूर्ण

अटल पूर्णांक data_init(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा data__file *d;
	अटल स्थिर अक्षर *शेषs[] = अणु
		"perf.data.old",
		"perf.data",
	पूर्ण;
	bool use_शेष = true;
	पूर्णांक i;

	data__files_cnt = 2;

	अगर (argc) अणु
		अगर (argc == 1)
			शेषs[1] = argv[0];
		अन्यथा अणु
			data__files_cnt = argc;
			use_शेष = false;
		पूर्ण
	पूर्ण अन्यथा अगर (perf_guest) अणु
		शेषs[0] = "perf.data.host";
		शेषs[1] = "perf.data.guest";
	पूर्ण

	अगर (sort_compute >= (अचिन्हित पूर्णांक) data__files_cnt) अणु
		pr_err("Order option out of limit.\n");
		वापस -EINVAL;
	पूर्ण

	data__files = zalloc(माप(*data__files) * data__files_cnt);
	अगर (!data__files)
		वापस -ENOMEM;

	data__क्रम_each_file(i, d) अणु
		काष्ठा perf_data *data = &d->data;

		data->path  = use_शेष ? शेषs[i] : argv[i];
		data->mode  = PERF_DATA_MODE_READ,
		data->क्रमce = क्रमce,

		d->idx  = i;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dअगरf__config(स्थिर अक्षर *var, स्थिर अक्षर *value,
			व्योम *cb __maybe_unused)
अणु
	अगर (!म_भेद(var, "diff.order")) अणु
		पूर्णांक ret;
		अगर (perf_config_पूर्णांक(&ret, var, value) < 0)
			वापस -1;
		sort_compute = ret;
		वापस 0;
	पूर्ण
	अगर (!म_भेद(var, "diff.compute")) अणु
		अगर (!म_भेद(value, "delta")) अणु
			compute = COMPUTE_DELTA;
		पूर्ण अन्यथा अगर (!म_भेद(value, "delta-abs")) अणु
			compute = COMPUTE_DELTA_ABS;
		पूर्ण अन्यथा अगर (!म_भेद(value, "ratio")) अणु
			compute = COMPUTE_RATIO;
		पूर्ण अन्यथा अगर (!म_भेद(value, "wdiff")) अणु
			compute = COMPUTE_WEIGHTED_DIFF;
		पूर्ण अन्यथा अणु
			pr_err("Invalid compute method: %s\n", value);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cmd_dअगरf(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक ret = hists__init();

	अगर (ret < 0)
		वापस ret;

	perf_config(dअगरf__config, शून्य);

	argc = parse_options(argc, argv, options, dअगरf_usage, 0);

	अगर (quiet)
		perf_quiet_option();

	अगर (cycles_hist && (compute != COMPUTE_CYCLES))
		usage_with_options(dअगरf_usage, options);

	अगर (pdअगरf.stream)
		compute = COMPUTE_STREAM;

	symbol__annotation_init();

	अगर (symbol__init(शून्य) < 0)
		वापस -1;

	अगर (data_init(argc, argv) < 0)
		वापस -1;

	अगर (check_file_brstack() < 0)
		वापस -1;

	अगर ((compute == COMPUTE_CYCLES || compute == COMPUTE_STREAM)
	    && !pdअगरf.has_br_stack) अणु
		वापस -1;
	पूर्ण

	अगर (compute == COMPUTE_STREAM) अणु
		symbol_conf.show_branchflag_count = true;
		symbol_conf.disable_add2line_warn = true;
		callchain_param.mode = CHAIN_FLAT;
		callchain_param.key = CCKEY_SRCLINE;
		callchain_param.branch_callstack = 1;
		symbol_conf.use_callchain = true;
		callchain_रेजिस्टर_param(&callchain_param);
		sort_order = "srcline,symbol,dso";
	पूर्ण अन्यथा अणु
		अगर (ui_init() < 0)
			वापस -1;

		sort__mode = SORT_MODE__DIFF;
	पूर्ण

	अगर (setup_sorting(शून्य) < 0)
		usage_with_options(dअगरf_usage, options);

	setup_pager();

	sort__setup_elide(शून्य);

	वापस __cmd_dअगरf();
पूर्ण
