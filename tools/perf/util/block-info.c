<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/zभाग.स>
#समावेश "block-info.h"
#समावेश "sort.h"
#समावेश "annotate.h"
#समावेश "symbol.h"
#समावेश "dso.h"
#समावेश "map.h"
#समावेश "srcline.h"
#समावेश "evlist.h"
#समावेश "hist.h"
#समावेश "ui/browsers/hists.h"

अटल काष्ठा block_header_column अणु
	स्थिर अक्षर *name;
	पूर्णांक width;
पूर्ण block_columns[PERF_HPP_REPORT__BLOCK_MAX_INDEX] = अणु
	[PERF_HPP_REPORT__BLOCK_TOTAL_CYCLES_PCT] = अणु
		.name = "Sampled Cycles%",
		.width = 15,
	पूर्ण,
	[PERF_HPP_REPORT__BLOCK_LBR_CYCLES] = अणु
		.name = "Sampled Cycles",
		.width = 14,
	पूर्ण,
	[PERF_HPP_REPORT__BLOCK_CYCLES_PCT] = अणु
		.name = "Avg Cycles%",
		.width = 11,
	पूर्ण,
	[PERF_HPP_REPORT__BLOCK_AVG_CYCLES] = अणु
		.name = "Avg Cycles",
		.width = 10,
	पूर्ण,
	[PERF_HPP_REPORT__BLOCK_RANGE] = अणु
		.name = "[Program Block Range]",
		.width = 70,
	पूर्ण,
	[PERF_HPP_REPORT__BLOCK_DSO] = अणु
		.name = "Shared Object",
		.width = 20,
	पूर्ण
पूर्ण;

काष्ठा block_info *block_info__get(काष्ठा block_info *bi)
अणु
	अगर (bi)
		refcount_inc(&bi->refcnt);
	वापस bi;
पूर्ण

व्योम block_info__put(काष्ठा block_info *bi)
अणु
	अगर (bi && refcount_dec_and_test(&bi->refcnt))
		मुक्त(bi);
पूर्ण

काष्ठा block_info *block_info__new(व्योम)
अणु
	काष्ठा block_info *bi = zalloc(माप(*bi));

	अगर (bi)
		refcount_set(&bi->refcnt, 1);
	वापस bi;
पूर्ण

पूर्णांक64_t __block_info__cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा block_info *bi_l = left->block_info;
	काष्ठा block_info *bi_r = right->block_info;
	पूर्णांक cmp;

	अगर (!bi_l->sym || !bi_r->sym) अणु
		अगर (!bi_l->sym && !bi_r->sym)
			वापस -1;
		अन्यथा अगर (!bi_l->sym)
			वापस -1;
		अन्यथा
			वापस 1;
	पूर्ण

	cmp = म_भेद(bi_l->sym->name, bi_r->sym->name);
	अगर (cmp)
		वापस cmp;

	अगर (bi_l->start != bi_r->start)
		वापस (पूर्णांक64_t)(bi_r->start - bi_l->start);

	वापस (पूर्णांक64_t)(bi_r->end - bi_l->end);
पूर्ण

पूर्णांक64_t block_info__cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस __block_info__cmp(left, right);
पूर्ण

अटल व्योम init_block_info(काष्ठा block_info *bi, काष्ठा symbol *sym,
			    काष्ठा cyc_hist *ch, पूर्णांक offset,
			    u64 total_cycles)
अणु
	bi->sym = sym;
	bi->start = ch->start;
	bi->end = offset;
	bi->cycles = ch->cycles;
	bi->cycles_aggr = ch->cycles_aggr;
	bi->num = ch->num;
	bi->num_aggr = ch->num_aggr;
	bi->total_cycles = total_cycles;

	स_नकल(bi->cycles_spark, ch->cycles_spark,
	       NUM_SPARKS * माप(u64));
पूर्ण

पूर्णांक block_info__process_sym(काष्ठा hist_entry *he, काष्ठा block_hist *bh,
			    u64 *block_cycles_aggr, u64 total_cycles)
अणु
	काष्ठा annotation *notes;
	काष्ठा cyc_hist *ch;
	अटल काष्ठा addr_location al;
	u64 cycles = 0;

	अगर (!he->ms.map || !he->ms.sym)
		वापस 0;

	स_रखो(&al, 0, माप(al));
	al.map = he->ms.map;
	al.sym = he->ms.sym;

	notes = symbol__annotation(he->ms.sym);
	अगर (!notes || !notes->src || !notes->src->cycles_hist)
		वापस 0;
	ch = notes->src->cycles_hist;
	क्रम (अचिन्हित पूर्णांक i = 0; i < symbol__size(he->ms.sym); i++) अणु
		अगर (ch[i].num_aggr) अणु
			काष्ठा block_info *bi;
			काष्ठा hist_entry *he_block;

			bi = block_info__new();
			अगर (!bi)
				वापस -1;

			init_block_info(bi, he->ms.sym, &ch[i], i,
					total_cycles);
			cycles += bi->cycles_aggr / bi->num_aggr;

			he_block = hists__add_entry_block(&bh->block_hists,
							  &al, bi);
			अगर (!he_block) अणु
				block_info__put(bi);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (block_cycles_aggr)
		*block_cycles_aggr += cycles;

	वापस 0;
पूर्ण

अटल पूर्णांक block_column_header(काष्ठा perf_hpp_fmt *fmt,
			       काष्ठा perf_hpp *hpp,
			       काष्ठा hists *hists __maybe_unused,
			       पूर्णांक line __maybe_unused,
			       पूर्णांक *span __maybe_unused)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", block_fmt->width,
			 block_fmt->header);
पूर्ण

अटल पूर्णांक block_column_width(काष्ठा perf_hpp_fmt *fmt,
			      काष्ठा perf_hpp *hpp __maybe_unused,
			      काष्ठा hists *hists __maybe_unused)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);

	वापस block_fmt->width;
पूर्ण

अटल पूर्णांक color_pct(काष्ठा perf_hpp *hpp, पूर्णांक width, द्विगुन pct)
अणु
#अगर_घोषित HAVE_SLANG_SUPPORT
	अगर (use_browser) अणु
		वापस __hpp__slsmg_color_म_लिखो(hpp, "%*.2f%%",
						 width - 1, pct);
	पूर्ण
#पूर्ण_अगर
	वापस hpp_color_scnम_लिखो(hpp, "%*.2f%%", width - 1, pct);
पूर्ण

अटल पूर्णांक block_total_cycles_pct_entry(काष्ठा perf_hpp_fmt *fmt,
					काष्ठा perf_hpp *hpp,
					काष्ठा hist_entry *he)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);
	काष्ठा block_info *bi = he->block_info;
	द्विगुन ratio = 0.0;

	अगर (block_fmt->total_cycles)
		ratio = (द्विगुन)bi->cycles_aggr / (द्विगुन)block_fmt->total_cycles;

	वापस color_pct(hpp, block_fmt->width, 100.0 * ratio);
पूर्ण

अटल पूर्णांक64_t block_total_cycles_pct_sort(काष्ठा perf_hpp_fmt *fmt,
					   काष्ठा hist_entry *left,
					   काष्ठा hist_entry *right)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);
	काष्ठा block_info *bi_l = left->block_info;
	काष्ठा block_info *bi_r = right->block_info;
	द्विगुन l, r;

	अगर (block_fmt->total_cycles) अणु
		l = ((द्विगुन)bi_l->cycles_aggr /
			(द्विगुन)block_fmt->total_cycles) * 100000.0;
		r = ((द्विगुन)bi_r->cycles_aggr /
			(द्विगुन)block_fmt->total_cycles) * 100000.0;
		वापस (पूर्णांक64_t)l - (पूर्णांक64_t)r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cycles_string(u64 cycles, अक्षर *buf, पूर्णांक size)
अणु
	अगर (cycles >= 1000000)
		scnम_लिखो(buf, size, "%.1fM", (द्विगुन)cycles / 1000000.0);
	अन्यथा अगर (cycles >= 1000)
		scnम_लिखो(buf, size, "%.1fK", (द्विगुन)cycles / 1000.0);
	अन्यथा
		scnम_लिखो(buf, size, "%1d", cycles);
पूर्ण

अटल पूर्णांक block_cycles_lbr_entry(काष्ठा perf_hpp_fmt *fmt,
				  काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);
	काष्ठा block_info *bi = he->block_info;
	अक्षर cycles_buf[16];

	cycles_string(bi->cycles_aggr, cycles_buf, माप(cycles_buf));

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", block_fmt->width,
			 cycles_buf);
पूर्ण

अटल पूर्णांक block_cycles_pct_entry(काष्ठा perf_hpp_fmt *fmt,
				  काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);
	काष्ठा block_info *bi = he->block_info;
	द्विगुन ratio = 0.0;
	u64 avg;

	अगर (block_fmt->block_cycles && bi->num_aggr) अणु
		avg = bi->cycles_aggr / bi->num_aggr;
		ratio = (द्विगुन)avg / (द्विगुन)block_fmt->block_cycles;
	पूर्ण

	वापस color_pct(hpp, block_fmt->width, 100.0 * ratio);
पूर्ण

अटल पूर्णांक block_avg_cycles_entry(काष्ठा perf_hpp_fmt *fmt,
				  काष्ठा perf_hpp *hpp,
				  काष्ठा hist_entry *he)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);
	काष्ठा block_info *bi = he->block_info;
	अक्षर cycles_buf[16];

	cycles_string(bi->cycles_aggr / bi->num_aggr, cycles_buf,
		      माप(cycles_buf));

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", block_fmt->width,
			 cycles_buf);
पूर्ण

अटल पूर्णांक block_range_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			     काष्ठा hist_entry *he)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);
	काष्ठा block_info *bi = he->block_info;
	अक्षर buf[128];
	अक्षर *start_line, *end_line;

	symbol_conf.disable_add2line_warn = true;

	start_line = map__srcline(he->ms.map, bi->sym->start + bi->start,
				  he->ms.sym);

	end_line = map__srcline(he->ms.map, bi->sym->start + bi->end,
				he->ms.sym);

	अगर ((म_भेदन(start_line, SRCLINE_UNKNOWN, म_माप(SRCLINE_UNKNOWN)) != 0) &&
	    (म_भेदन(end_line, SRCLINE_UNKNOWN, म_माप(SRCLINE_UNKNOWN)) != 0)) अणु
		scnम_लिखो(buf, माप(buf), "[%s -> %s]",
			  start_line, end_line);
	पूर्ण अन्यथा अणु
		scnम_लिखो(buf, माप(buf), "[%7lx -> %7lx]",
			  bi->start, bi->end);
	पूर्ण

	मुक्त_srcline(start_line);
	मुक्त_srcline(end_line);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", block_fmt->width, buf);
पूर्ण

अटल पूर्णांक block_dso_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			   काष्ठा hist_entry *he)
अणु
	काष्ठा block_fmt *block_fmt = container_of(fmt, काष्ठा block_fmt, fmt);
	काष्ठा map *map = he->ms.map;

	अगर (map && map->dso) अणु
		वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", block_fmt->width,
				 map->dso->लघु_name);
	पूर्ण

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", block_fmt->width,
			 "[unknown]");
पूर्ण

अटल व्योम init_block_header(काष्ठा block_fmt *block_fmt)
अणु
	काष्ठा perf_hpp_fmt *fmt = &block_fmt->fmt;

	BUG_ON(block_fmt->idx >= PERF_HPP_REPORT__BLOCK_MAX_INDEX);

	block_fmt->header = block_columns[block_fmt->idx].name;
	block_fmt->width = block_columns[block_fmt->idx].width;

	fmt->header = block_column_header;
	fmt->width = block_column_width;
पूर्ण

अटल व्योम hpp_रेजिस्टर(काष्ठा block_fmt *block_fmt, पूर्णांक idx,
			 काष्ठा perf_hpp_list *hpp_list)
अणु
	काष्ठा perf_hpp_fmt *fmt = &block_fmt->fmt;

	block_fmt->idx = idx;
	INIT_LIST_HEAD(&fmt->list);
	INIT_LIST_HEAD(&fmt->sort_list);

	चयन (idx) अणु
	हाल PERF_HPP_REPORT__BLOCK_TOTAL_CYCLES_PCT:
		fmt->color = block_total_cycles_pct_entry;
		fmt->cmp = block_info__cmp;
		fmt->sort = block_total_cycles_pct_sort;
		अवरोध;
	हाल PERF_HPP_REPORT__BLOCK_LBR_CYCLES:
		fmt->entry = block_cycles_lbr_entry;
		अवरोध;
	हाल PERF_HPP_REPORT__BLOCK_CYCLES_PCT:
		fmt->color = block_cycles_pct_entry;
		अवरोध;
	हाल PERF_HPP_REPORT__BLOCK_AVG_CYCLES:
		fmt->entry = block_avg_cycles_entry;
		अवरोध;
	हाल PERF_HPP_REPORT__BLOCK_RANGE:
		fmt->entry = block_range_entry;
		अवरोध;
	हाल PERF_HPP_REPORT__BLOCK_DSO:
		fmt->entry = block_dso_entry;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	init_block_header(block_fmt);
	perf_hpp_list__column_रेजिस्टर(hpp_list, fmt);
पूर्ण

अटल व्योम रेजिस्टर_block_columns(काष्ठा perf_hpp_list *hpp_list,
				   काष्ठा block_fmt *block_fmts,
				   पूर्णांक *block_hpps, पूर्णांक nr_hpps)
अणु
	क्रम (पूर्णांक i = 0; i < nr_hpps; i++)
		hpp_रेजिस्टर(&block_fmts[i], block_hpps[i], hpp_list);
पूर्ण

अटल व्योम init_block_hist(काष्ठा block_hist *bh, काष्ठा block_fmt *block_fmts,
			    पूर्णांक *block_hpps, पूर्णांक nr_hpps)
अणु
	__hists__init(&bh->block_hists, &bh->block_list);
	perf_hpp_list__init(&bh->block_list);
	bh->block_list.nr_header_lines = 1;

	रेजिस्टर_block_columns(&bh->block_list, block_fmts,
			       block_hpps, nr_hpps);

	/* Sort by the first fmt */
	perf_hpp_list__रेजिस्टर_sort_field(&bh->block_list, &block_fmts[0].fmt);
पूर्ण

अटल पूर्णांक process_block_report(काष्ठा hists *hists,
				काष्ठा block_report *block_report,
				u64 total_cycles, पूर्णांक *block_hpps,
				पूर्णांक nr_hpps)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);
	काष्ठा block_hist *bh = &block_report->hist;
	काष्ठा hist_entry *he;

	अगर (nr_hpps > PERF_HPP_REPORT__BLOCK_MAX_INDEX)
		वापस -1;

	block_report->nr_fmts = nr_hpps;
	init_block_hist(bh, block_report->fmts, block_hpps, nr_hpps);

	जबतक (next) अणु
		he = rb_entry(next, काष्ठा hist_entry, rb_node);
		block_info__process_sym(he, bh, &block_report->cycles,
					total_cycles);
		next = rb_next(&he->rb_node);
	पूर्ण

	क्रम (पूर्णांक i = 0; i < nr_hpps; i++) अणु
		block_report->fmts[i].total_cycles = total_cycles;
		block_report->fmts[i].block_cycles = block_report->cycles;
	पूर्ण

	hists__output_resort(&bh->block_hists, शून्य);
	वापस 0;
पूर्ण

काष्ठा block_report *block_info__create_report(काष्ठा evlist *evlist,
					       u64 total_cycles,
					       पूर्णांक *block_hpps, पूर्णांक nr_hpps,
					       पूर्णांक *nr_reps)
अणु
	काष्ठा block_report *block_reports;
	पूर्णांक nr_hists = evlist->core.nr_entries, i = 0;
	काष्ठा evsel *pos;

	block_reports = सुस्मृति(nr_hists, माप(काष्ठा block_report));
	अगर (!block_reports)
		वापस शून्य;

	evlist__क्रम_each_entry(evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);

		process_block_report(hists, &block_reports[i], total_cycles,
				     block_hpps, nr_hpps);
		i++;
	पूर्ण

	*nr_reps = nr_hists;
	वापस block_reports;
पूर्ण

व्योम block_info__मुक्त_report(काष्ठा block_report *reps, पूर्णांक nr_reps)
अणु
	क्रम (पूर्णांक i = 0; i < nr_reps; i++)
		hists__delete_entries(&reps[i].hist.block_hists);

	मुक्त(reps);
पूर्ण

पूर्णांक report__browse_block_hists(काष्ठा block_hist *bh, भग्न min_percent,
			       काष्ठा evsel *evsel, काष्ठा perf_env *env,
			       काष्ठा annotation_options *annotation_opts)
अणु
	पूर्णांक ret;

	चयन (use_browser) अणु
	हाल 0:
		symbol_conf.report_inभागidual_block = true;
		hists__ख_लिखो(&bh->block_hists, true, 0, 0, min_percent,
			       मानक_निकास, true);
		वापस 0;
	हाल 1:
		symbol_conf.report_inभागidual_block = true;
		ret = block_hists_tui_browse(bh, evsel, min_percent,
					     env, annotation_opts);
		वापस ret;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

भग्न block_info__total_cycles_percent(काष्ठा hist_entry *he)
अणु
	काष्ठा block_info *bi = he->block_info;

	अगर (bi->total_cycles)
		वापस bi->cycles * 100.0 / bi->total_cycles;

	वापस 0.0;
पूर्ण
