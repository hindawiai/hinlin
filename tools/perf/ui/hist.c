<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <गणित.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/compiler.h>

#समावेश "../util/callchain.h"
#समावेश "../util/debug.h"
#समावेश "../util/hist.h"
#समावेश "../util/sort.h"
#समावेश "../util/evsel.h"
#समावेश "../util/evlist.h"
#समावेश "../perf.h"

/* hist period prपूर्णांक (hpp) functions */

#घोषणा hpp__call_prपूर्णांक_fn(hpp, fn, fmt, ...)			\
(अणु								\
	पूर्णांक __ret = fn(hpp, fmt, ##__VA_ARGS__);		\
	advance_hpp(hpp, __ret);				\
	__ret;							\
पूर्ण)

अटल पूर्णांक __hpp__fmt(काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he,
		      hpp_field_fn get_field, स्थिर अक्षर *fmt, पूर्णांक len,
		      hpp_snprपूर्णांक_fn prपूर्णांक_fn, bool fmt_percent)
अणु
	पूर्णांक ret;
	काष्ठा hists *hists = he->hists;
	काष्ठा evsel *evsel = hists_to_evsel(hists);
	अक्षर *buf = hpp->buf;
	माप_प्रकार size = hpp->size;

	अगर (fmt_percent) अणु
		द्विगुन percent = 0.0;
		u64 total = hists__total_period(hists);

		अगर (total)
			percent = 100.0 * get_field(he) / total;

		ret = hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn, fmt, len, percent);
	पूर्ण अन्यथा
		ret = hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn, fmt, len, get_field(he));

	अगर (evsel__is_group_event(evsel)) अणु
		पूर्णांक prev_idx, idx_delta;
		काष्ठा hist_entry *pair;
		पूर्णांक nr_members = evsel->core.nr_members;

		prev_idx = evsel__group_idx(evsel);

		list_क्रम_each_entry(pair, &he->pairs.head, pairs.node) अणु
			u64 period = get_field(pair);
			u64 total = hists__total_period(pair->hists);

			अगर (!total)
				जारी;

			evsel = hists_to_evsel(pair->hists);
			idx_delta = evsel__group_idx(evsel) - prev_idx - 1;

			जबतक (idx_delta--) अणु
				/*
				 * zero-fill group members in the middle which
				 * have no sample
				 */
				अगर (fmt_percent) अणु
					ret += hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn,
								  fmt, len, 0.0);
				पूर्ण अन्यथा अणु
					ret += hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn,
								  fmt, len, 0ULL);
				पूर्ण
			पूर्ण

			अगर (fmt_percent) अणु
				ret += hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn, fmt, len,
							  100.0 * period / total);
			पूर्ण अन्यथा अणु
				ret += hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn, fmt,
							  len, period);
			पूर्ण

			prev_idx = evsel__group_idx(evsel);
		पूर्ण

		idx_delta = nr_members - prev_idx - 1;

		जबतक (idx_delta--) अणु
			/*
			 * zero-fill group members at last which have no sample
			 */
			अगर (fmt_percent) अणु
				ret += hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn,
							  fmt, len, 0.0);
			पूर्ण अन्यथा अणु
				ret += hpp__call_prपूर्णांक_fn(hpp, prपूर्णांक_fn,
							  fmt, len, 0ULL);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Restore original buf and size as it's where caller expects
	 * the result will be saved.
	 */
	hpp->buf = buf;
	hpp->size = size;

	वापस ret;
पूर्ण

पूर्णांक hpp__fmt(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
	     काष्ठा hist_entry *he, hpp_field_fn get_field,
	     स्थिर अक्षर *fmtstr, hpp_snprपूर्णांक_fn prपूर्णांक_fn, bool fmt_percent)
अणु
	पूर्णांक len = fmt->user_len ?: fmt->len;

	अगर (symbol_conf.field_sep) अणु
		वापस __hpp__fmt(hpp, he, get_field, fmtstr, 1,
				  prपूर्णांक_fn, fmt_percent);
	पूर्ण

	अगर (fmt_percent)
		len -= 2; /* 2 क्रम a space and a % sign */
	अन्यथा
		len -= 1;

	वापस  __hpp__fmt(hpp, he, get_field, fmtstr, len, prपूर्णांक_fn, fmt_percent);
पूर्ण

पूर्णांक hpp__fmt_acc(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
		 काष्ठा hist_entry *he, hpp_field_fn get_field,
		 स्थिर अक्षर *fmtstr, hpp_snprपूर्णांक_fn prपूर्णांक_fn, bool fmt_percent)
अणु
	अगर (!symbol_conf.cumulate_callchain) अणु
		पूर्णांक len = fmt->user_len ?: fmt->len;
		वापस snम_लिखो(hpp->buf, hpp->size, " %*s", len - 1, "N/A");
	पूर्ण

	वापस hpp__fmt(fmt, hpp, he, get_field, fmtstr, prपूर्णांक_fn, fmt_percent);
पूर्ण

अटल पूर्णांक field_cmp(u64 field_a, u64 field_b)
अणु
	अगर (field_a > field_b)
		वापस 1;
	अगर (field_a < field_b)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक hist_entry__new_pair(काष्ठा hist_entry *a, काष्ठा hist_entry *b,
				hpp_field_fn get_field, पूर्णांक nr_members,
				u64 **fields_a, u64 **fields_b)
अणु
	u64 *fa = सुस्मृति(nr_members, माप(*fa)),
	    *fb = सुस्मृति(nr_members, माप(*fb));
	काष्ठा hist_entry *pair;

	अगर (!fa || !fb)
		जाओ out_मुक्त;

	list_क्रम_each_entry(pair, &a->pairs.head, pairs.node) अणु
		काष्ठा evsel *evsel = hists_to_evsel(pair->hists);
		fa[evsel__group_idx(evsel)] = get_field(pair);
	पूर्ण

	list_क्रम_each_entry(pair, &b->pairs.head, pairs.node) अणु
		काष्ठा evsel *evsel = hists_to_evsel(pair->hists);
		fb[evsel__group_idx(evsel)] = get_field(pair);
	पूर्ण

	*fields_a = fa;
	*fields_b = fb;
	वापस 0;
out_मुक्त:
	मुक्त(fa);
	मुक्त(fb);
	*fields_a = *fields_b = शून्य;
	वापस -1;
पूर्ण

अटल पूर्णांक __hpp__group_sort_idx(काष्ठा hist_entry *a, काष्ठा hist_entry *b,
				 hpp_field_fn get_field, पूर्णांक idx)
अणु
	काष्ठा evsel *evsel = hists_to_evsel(a->hists);
	u64 *fields_a, *fields_b;
	पूर्णांक cmp, nr_members, ret, i;

	cmp = field_cmp(get_field(a), get_field(b));
	अगर (!evsel__is_group_event(evsel))
		वापस cmp;

	nr_members = evsel->core.nr_members;
	अगर (idx < 1 || idx >= nr_members)
		वापस cmp;

	ret = hist_entry__new_pair(a, b, get_field, nr_members, &fields_a, &fields_b);
	अगर (ret) अणु
		ret = cmp;
		जाओ out;
	पूर्ण

	ret = field_cmp(fields_a[idx], fields_b[idx]);
	अगर (ret)
		जाओ out;

	क्रम (i = 1; i < nr_members; i++) अणु
		अगर (i != idx) अणु
			ret = field_cmp(fields_a[i], fields_b[i]);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	मुक्त(fields_a);
	मुक्त(fields_b);

	वापस ret;
पूर्ण

अटल पूर्णांक __hpp__sort(काष्ठा hist_entry *a, काष्ठा hist_entry *b,
		       hpp_field_fn get_field)
अणु
	s64 ret;
	पूर्णांक i, nr_members;
	काष्ठा evsel *evsel;
	u64 *fields_a, *fields_b;

	अगर (symbol_conf.group_sort_idx && symbol_conf.event_group) अणु
		वापस __hpp__group_sort_idx(a, b, get_field,
					     symbol_conf.group_sort_idx);
	पूर्ण

	ret = field_cmp(get_field(a), get_field(b));
	अगर (ret || !symbol_conf.event_group)
		वापस ret;

	evsel = hists_to_evsel(a->hists);
	अगर (!evsel__is_group_event(evsel))
		वापस ret;

	nr_members = evsel->core.nr_members;
	i = hist_entry__new_pair(a, b, get_field, nr_members, &fields_a, &fields_b);
	अगर (i)
		जाओ out;

	क्रम (i = 1; i < nr_members; i++) अणु
		ret = field_cmp(fields_a[i], fields_b[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

out:
	मुक्त(fields_a);
	मुक्त(fields_b);

	वापस ret;
पूर्ण

अटल पूर्णांक __hpp__sort_acc(काष्ठा hist_entry *a, काष्ठा hist_entry *b,
			   hpp_field_fn get_field)
अणु
	s64 ret = 0;

	अगर (symbol_conf.cumulate_callchain) अणु
		/*
		 * Put caller above callee when they have equal period.
		 */
		ret = field_cmp(get_field(a), get_field(b));
		अगर (ret)
			वापस ret;

		अगर (a->thपढ़ो != b->thपढ़ो || !hist_entry__has_callchains(a) || !symbol_conf.use_callchain)
			वापस 0;

		ret = b->callchain->max_depth - a->callchain->max_depth;
		अगर (callchain_param.order == ORDER_CALLER)
			ret = -ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक hpp__width_fn(काष्ठा perf_hpp_fmt *fmt,
			 काष्ठा perf_hpp *hpp __maybe_unused,
			 काष्ठा hists *hists)
अणु
	पूर्णांक len = fmt->user_len ?: fmt->len;
	काष्ठा evsel *evsel = hists_to_evsel(hists);

	अगर (symbol_conf.event_group)
		len = max(len, evsel->core.nr_members * fmt->len);

	अगर (len < (पूर्णांक)म_माप(fmt->name))
		len = म_माप(fmt->name);

	वापस len;
पूर्ण

अटल पूर्णांक hpp__header_fn(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			  काष्ठा hists *hists, पूर्णांक line __maybe_unused,
			  पूर्णांक *span __maybe_unused)
अणु
	पूर्णांक len = hpp__width_fn(fmt, hpp, hists);
	वापस scnम_लिखो(hpp->buf, hpp->size, "%*s", len, fmt->name);
पूर्ण

पूर्णांक hpp_color_scnम_लिखो(काष्ठा perf_hpp *hpp, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	sमाप_प्रकार ssize = hpp->size;
	द्विगुन percent;
	पूर्णांक ret, len;

	बहु_शुरू(args, fmt);
	len = बहु_तर्क(args, पूर्णांक);
	percent = बहु_तर्क(args, द्विगुन);
	ret = percent_color_len_snम_लिखो(hpp->buf, hpp->size, fmt, len, percent);
	बहु_पूर्ण(args);

	वापस (ret >= ssize) ? (ssize - 1) : ret;
पूर्ण

अटल पूर्णांक hpp_entry_scnम_लिखो(काष्ठा perf_hpp *hpp, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	sमाप_प्रकार ssize = hpp->size;
	पूर्णांक ret;

	बहु_शुरू(args, fmt);
	ret = vsnम_लिखो(hpp->buf, hpp->size, fmt, args);
	बहु_पूर्ण(args);

	वापस (ret >= ssize) ? (ssize - 1) : ret;
पूर्ण

#घोषणा __HPP_COLOR_PERCENT_FN(_type, _field)					\
अटल u64 he_get_##_field(काष्ठा hist_entry *he)				\
अणु										\
	वापस he->stat._field;							\
पूर्ण										\
										\
अटल पूर्णांक hpp__color_##_type(काष्ठा perf_hpp_fmt *fmt,				\
			      काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he) 	\
अणु										\
	वापस hpp__fmt(fmt, hpp, he, he_get_##_field, " %*.2f%%",		\
			hpp_color_scnम_लिखो, true);				\
पूर्ण

#घोषणा __HPP_ENTRY_PERCENT_FN(_type, _field)					\
अटल पूर्णांक hpp__entry_##_type(काष्ठा perf_hpp_fmt *fmt,				\
			      काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he) 	\
अणु										\
	वापस hpp__fmt(fmt, hpp, he, he_get_##_field, " %*.2f%%",		\
			hpp_entry_scnम_लिखो, true);				\
पूर्ण

#घोषणा __HPP_SORT_FN(_type, _field)						\
अटल पूर्णांक64_t hpp__sort_##_type(काष्ठा perf_hpp_fmt *fmt __maybe_unused, 	\
				 काष्ठा hist_entry *a, काष्ठा hist_entry *b) 	\
अणु										\
	वापस __hpp__sort(a, b, he_get_##_field);				\
पूर्ण

#घोषणा __HPP_COLOR_ACC_PERCENT_FN(_type, _field)				\
अटल u64 he_get_acc_##_field(काष्ठा hist_entry *he)				\
अणु										\
	वापस he->stat_acc->_field;						\
पूर्ण										\
										\
अटल पूर्णांक hpp__color_##_type(काष्ठा perf_hpp_fmt *fmt,				\
			      काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he) 	\
अणु										\
	वापस hpp__fmt_acc(fmt, hpp, he, he_get_acc_##_field, " %*.2f%%", 	\
			    hpp_color_scnम_लिखो, true);				\
पूर्ण

#घोषणा __HPP_ENTRY_ACC_PERCENT_FN(_type, _field)				\
अटल पूर्णांक hpp__entry_##_type(काष्ठा perf_hpp_fmt *fmt,				\
			      काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he) 	\
अणु										\
	वापस hpp__fmt_acc(fmt, hpp, he, he_get_acc_##_field, " %*.2f%%",	\
			    hpp_entry_scnम_लिखो, true);				\
पूर्ण

#घोषणा __HPP_SORT_ACC_FN(_type, _field)					\
अटल पूर्णांक64_t hpp__sort_##_type(काष्ठा perf_hpp_fmt *fmt __maybe_unused, 	\
				 काष्ठा hist_entry *a, काष्ठा hist_entry *b) 	\
अणु										\
	वापस __hpp__sort_acc(a, b, he_get_acc_##_field);			\
पूर्ण

#घोषणा __HPP_ENTRY_RAW_FN(_type, _field)					\
अटल u64 he_get_raw_##_field(काष्ठा hist_entry *he)				\
अणु										\
	वापस he->stat._field;							\
पूर्ण										\
										\
अटल पूर्णांक hpp__entry_##_type(काष्ठा perf_hpp_fmt *fmt,				\
			      काष्ठा perf_hpp *hpp, काष्ठा hist_entry *he) 	\
अणु										\
	वापस hpp__fmt(fmt, hpp, he, he_get_raw_##_field, " %*"PRIu64, 	\
			hpp_entry_scnम_लिखो, false);				\
पूर्ण

#घोषणा __HPP_SORT_RAW_FN(_type, _field)					\
अटल पूर्णांक64_t hpp__sort_##_type(काष्ठा perf_hpp_fmt *fmt __maybe_unused, 	\
				 काष्ठा hist_entry *a, काष्ठा hist_entry *b) 	\
अणु										\
	वापस __hpp__sort(a, b, he_get_raw_##_field);				\
पूर्ण


#घोषणा HPP_PERCENT_FNS(_type, _field)					\
__HPP_COLOR_PERCENT_FN(_type, _field)					\
__HPP_ENTRY_PERCENT_FN(_type, _field)					\
__HPP_SORT_FN(_type, _field)

#घोषणा HPP_PERCENT_ACC_FNS(_type, _field)				\
__HPP_COLOR_ACC_PERCENT_FN(_type, _field)				\
__HPP_ENTRY_ACC_PERCENT_FN(_type, _field)				\
__HPP_SORT_ACC_FN(_type, _field)

#घोषणा HPP_RAW_FNS(_type, _field)					\
__HPP_ENTRY_RAW_FN(_type, _field)					\
__HPP_SORT_RAW_FN(_type, _field)

HPP_PERCENT_FNS(overhead, period)
HPP_PERCENT_FNS(overhead_sys, period_sys)
HPP_PERCENT_FNS(overhead_us, period_us)
HPP_PERCENT_FNS(overhead_guest_sys, period_guest_sys)
HPP_PERCENT_FNS(overhead_guest_us, period_guest_us)
HPP_PERCENT_ACC_FNS(overhead_acc, period)

HPP_RAW_FNS(samples, nr_events)
HPP_RAW_FNS(period, period)

अटल पूर्णांक64_t hpp__nop_cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			    काष्ठा hist_entry *a __maybe_unused,
			    काष्ठा hist_entry *b __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल bool perf_hpp__is_hpp_entry(काष्ठा perf_hpp_fmt *a)
अणु
	वापस a->header == hpp__header_fn;
पूर्ण

अटल bool hpp__equal(काष्ठा perf_hpp_fmt *a, काष्ठा perf_hpp_fmt *b)
अणु
	अगर (!perf_hpp__is_hpp_entry(a) || !perf_hpp__is_hpp_entry(b))
		वापस false;

	वापस a->idx == b->idx;
पूर्ण

#घोषणा HPP__COLOR_PRINT_FNS(_name, _fn, _idx)		\
	अणु						\
		.name   = _name,			\
		.header	= hpp__header_fn,		\
		.width	= hpp__width_fn,		\
		.color	= hpp__color_ ## _fn,		\
		.entry	= hpp__entry_ ## _fn,		\
		.cmp	= hpp__nop_cmp,			\
		.collapse = hpp__nop_cmp,		\
		.sort	= hpp__sort_ ## _fn,		\
		.idx	= PERF_HPP__ ## _idx,		\
		.equal	= hpp__equal,			\
	पूर्ण

#घोषणा HPP__COLOR_ACC_PRINT_FNS(_name, _fn, _idx)	\
	अणु						\
		.name   = _name,			\
		.header	= hpp__header_fn,		\
		.width	= hpp__width_fn,		\
		.color	= hpp__color_ ## _fn,		\
		.entry	= hpp__entry_ ## _fn,		\
		.cmp	= hpp__nop_cmp,			\
		.collapse = hpp__nop_cmp,		\
		.sort	= hpp__sort_ ## _fn,		\
		.idx	= PERF_HPP__ ## _idx,		\
		.equal	= hpp__equal,			\
	पूर्ण

#घोषणा HPP__PRINT_FNS(_name, _fn, _idx)		\
	अणु						\
		.name   = _name,			\
		.header	= hpp__header_fn,		\
		.width	= hpp__width_fn,		\
		.entry	= hpp__entry_ ## _fn,		\
		.cmp	= hpp__nop_cmp,			\
		.collapse = hpp__nop_cmp,		\
		.sort	= hpp__sort_ ## _fn,		\
		.idx	= PERF_HPP__ ## _idx,		\
		.equal	= hpp__equal,			\
	पूर्ण

काष्ठा perf_hpp_fmt perf_hpp__क्रमmat[] = अणु
	HPP__COLOR_PRINT_FNS("Overhead", overhead, OVERHEAD),
	HPP__COLOR_PRINT_FNS("sys", overhead_sys, OVERHEAD_SYS),
	HPP__COLOR_PRINT_FNS("usr", overhead_us, OVERHEAD_US),
	HPP__COLOR_PRINT_FNS("guest sys", overhead_guest_sys, OVERHEAD_GUEST_SYS),
	HPP__COLOR_PRINT_FNS("guest usr", overhead_guest_us, OVERHEAD_GUEST_US),
	HPP__COLOR_ACC_PRINT_FNS("Children", overhead_acc, OVERHEAD_ACC),
	HPP__PRINT_FNS("Samples", samples, SAMPLES),
	HPP__PRINT_FNS("Period", period, PERIOD)
पूर्ण;

काष्ठा perf_hpp_list perf_hpp_list = अणु
	.fields	= LIST_HEAD_INIT(perf_hpp_list.fields),
	.sorts	= LIST_HEAD_INIT(perf_hpp_list.sorts),
	.nr_header_lines = 1,
पूर्ण;

#अघोषित HPP__COLOR_PRINT_FNS
#अघोषित HPP__COLOR_ACC_PRINT_FNS
#अघोषित HPP__PRINT_FNS

#अघोषित HPP_PERCENT_FNS
#अघोषित HPP_PERCENT_ACC_FNS
#अघोषित HPP_RAW_FNS

#अघोषित __HPP_HEADER_FN
#अघोषित __HPP_WIDTH_FN
#अघोषित __HPP_COLOR_PERCENT_FN
#अघोषित __HPP_ENTRY_PERCENT_FN
#अघोषित __HPP_COLOR_ACC_PERCENT_FN
#अघोषित __HPP_ENTRY_ACC_PERCENT_FN
#अघोषित __HPP_ENTRY_RAW_FN
#अघोषित __HPP_SORT_FN
#अघोषित __HPP_SORT_ACC_FN
#अघोषित __HPP_SORT_RAW_FN


व्योम perf_hpp__init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PERF_HPP__MAX_INDEX; i++) अणु
		काष्ठा perf_hpp_fmt *fmt = &perf_hpp__क्रमmat[i];

		INIT_LIST_HEAD(&fmt->list);

		/* sort_list may be linked by setup_sorting() */
		अगर (fmt->sort_list.next == शून्य)
			INIT_LIST_HEAD(&fmt->sort_list);
	पूर्ण

	/*
	 * If user specअगरied field order, no need to setup शेष fields.
	 */
	अगर (is_strict_order(field_order))
		वापस;

	अगर (symbol_conf.cumulate_callchain) अणु
		hpp_dimension__add_output(PERF_HPP__OVERHEAD_ACC);
		perf_hpp__क्रमmat[PERF_HPP__OVERHEAD].name = "Self";
	पूर्ण

	hpp_dimension__add_output(PERF_HPP__OVERHEAD);

	अगर (symbol_conf.show_cpu_utilization) अणु
		hpp_dimension__add_output(PERF_HPP__OVERHEAD_SYS);
		hpp_dimension__add_output(PERF_HPP__OVERHEAD_US);

		अगर (perf_guest) अणु
			hpp_dimension__add_output(PERF_HPP__OVERHEAD_GUEST_SYS);
			hpp_dimension__add_output(PERF_HPP__OVERHEAD_GUEST_US);
		पूर्ण
	पूर्ण

	अगर (symbol_conf.show_nr_samples)
		hpp_dimension__add_output(PERF_HPP__SAMPLES);

	अगर (symbol_conf.show_total_period)
		hpp_dimension__add_output(PERF_HPP__PERIOD);
पूर्ण

व्योम perf_hpp_list__column_रेजिस्टर(काष्ठा perf_hpp_list *list,
				    काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	list_add_tail(&क्रमmat->list, &list->fields);
पूर्ण

व्योम perf_hpp_list__रेजिस्टर_sort_field(काष्ठा perf_hpp_list *list,
					काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	list_add_tail(&क्रमmat->sort_list, &list->sorts);
पूर्ण

व्योम perf_hpp_list__prepend_sort_field(काष्ठा perf_hpp_list *list,
				       काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	list_add(&क्रमmat->sort_list, &list->sorts);
पूर्ण

व्योम perf_hpp__column_unरेजिस्टर(काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	list_del_init(&क्रमmat->list);
पूर्ण

व्योम perf_hpp__cancel_cumulate(व्योम)
अणु
	काष्ठा perf_hpp_fmt *fmt, *acc, *ovh, *पंचांगp;

	अगर (is_strict_order(field_order))
		वापस;

	ovh = &perf_hpp__क्रमmat[PERF_HPP__OVERHEAD];
	acc = &perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_ACC];

	perf_hpp_list__क्रम_each_क्रमmat_safe(&perf_hpp_list, fmt, पंचांगp) अणु
		अगर (acc->equal(acc, fmt)) अणु
			perf_hpp__column_unरेजिस्टर(fmt);
			जारी;
		पूर्ण

		अगर (ovh->equal(ovh, fmt))
			fmt->name = "Overhead";
	पूर्ण
पूर्ण

अटल bool fmt_equal(काष्ठा perf_hpp_fmt *a, काष्ठा perf_hpp_fmt *b)
अणु
	वापस a->equal && a->equal(a, b);
पूर्ण

व्योम perf_hpp__setup_output_field(काष्ठा perf_hpp_list *list)
अणु
	काष्ठा perf_hpp_fmt *fmt;

	/* append sort keys to output field */
	perf_hpp_list__क्रम_each_sort_list(list, fmt) अणु
		काष्ठा perf_hpp_fmt *pos;

		/* skip sort-only fields ("sort_compute" in perf dअगरf) */
		अगर (!fmt->entry && !fmt->color)
			जारी;

		perf_hpp_list__क्रम_each_क्रमmat(list, pos) अणु
			अगर (fmt_equal(fmt, pos))
				जाओ next;
		पूर्ण

		perf_hpp__column_रेजिस्टर(fmt);
next:
		जारी;
	पूर्ण
पूर्ण

व्योम perf_hpp__append_sort_keys(काष्ठा perf_hpp_list *list)
अणु
	काष्ठा perf_hpp_fmt *fmt;

	/* append output fields to sort keys */
	perf_hpp_list__क्रम_each_क्रमmat(list, fmt) अणु
		काष्ठा perf_hpp_fmt *pos;

		perf_hpp_list__क्रम_each_sort_list(list, pos) अणु
			अगर (fmt_equal(fmt, pos))
				जाओ next;
		पूर्ण

		perf_hpp__रेजिस्टर_sort_field(fmt);
next:
		जारी;
	पूर्ण
पूर्ण


अटल व्योम fmt_मुक्त(काष्ठा perf_hpp_fmt *fmt)
अणु
	/*
	 * At this poपूर्णांक fmt should be completely
	 * unhooked, अगर not it's a bug.
	 */
	BUG_ON(!list_empty(&fmt->list));
	BUG_ON(!list_empty(&fmt->sort_list));

	अगर (fmt->मुक्त)
		fmt->मुक्त(fmt);
पूर्ण

व्योम perf_hpp__reset_output_field(काष्ठा perf_hpp_list *list)
अणु
	काष्ठा perf_hpp_fmt *fmt, *पंचांगp;

	/* reset output fields */
	perf_hpp_list__क्रम_each_क्रमmat_safe(list, fmt, पंचांगp) अणु
		list_del_init(&fmt->list);
		list_del_init(&fmt->sort_list);
		fmt_मुक्त(fmt);
	पूर्ण

	/* reset sort keys */
	perf_hpp_list__क्रम_each_sort_list_safe(list, fmt, पंचांगp) अणु
		list_del_init(&fmt->list);
		list_del_init(&fmt->sort_list);
		fmt_मुक्त(fmt);
	पूर्ण
पूर्ण

/*
 * See hists__ख_लिखो to match the column widths
 */
अचिन्हित पूर्णांक hists__sort_list_width(काष्ठा hists *hists)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	पूर्णांक ret = 0;
	bool first = true;
	काष्ठा perf_hpp dummy_hpp;

	hists__क्रम_each_क्रमmat(hists, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, hists))
			जारी;

		अगर (first)
			first = false;
		अन्यथा
			ret += 2;

		ret += fmt->width(fmt, &dummy_hpp, hists);
	पूर्ण

	अगर (verbose > 0 && hists__has(hists, sym)) /* Addr + origin */
		ret += 3 + BITS_PER_LONG / 4;

	वापस ret;
पूर्ण

अचिन्हित पूर्णांक hists__overhead_width(काष्ठा hists *hists)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	पूर्णांक ret = 0;
	bool first = true;
	काष्ठा perf_hpp dummy_hpp;

	hists__क्रम_each_क्रमmat(hists, fmt) अणु
		अगर (perf_hpp__is_sort_entry(fmt) || perf_hpp__is_dynamic_entry(fmt))
			अवरोध;

		अगर (first)
			first = false;
		अन्यथा
			ret += 2;

		ret += fmt->width(fmt, &dummy_hpp, hists);
	पूर्ण

	वापस ret;
पूर्ण

व्योम perf_hpp__reset_width(काष्ठा perf_hpp_fmt *fmt, काष्ठा hists *hists)
अणु
	अगर (perf_hpp__is_sort_entry(fmt))
		वापस perf_hpp__reset_sort_width(fmt, hists);

	अगर (perf_hpp__is_dynamic_entry(fmt))
		वापस;

	BUG_ON(fmt->idx >= PERF_HPP__MAX_INDEX);

	चयन (fmt->idx) अणु
	हाल PERF_HPP__OVERHEAD:
	हाल PERF_HPP__OVERHEAD_SYS:
	हाल PERF_HPP__OVERHEAD_US:
	हाल PERF_HPP__OVERHEAD_ACC:
		fmt->len = 8;
		अवरोध;

	हाल PERF_HPP__OVERHEAD_GUEST_SYS:
	हाल PERF_HPP__OVERHEAD_GUEST_US:
		fmt->len = 9;
		अवरोध;

	हाल PERF_HPP__SAMPLES:
	हाल PERF_HPP__PERIOD:
		fmt->len = 12;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम hists__reset_column_width(काष्ठा hists *hists)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *node;

	hists__क्रम_each_क्रमmat(hists, fmt)
		perf_hpp__reset_width(fmt, hists);

	/* hierarchy entries have their own hpp list */
	list_क्रम_each_entry(node, &hists->hpp_क्रमmats, list) अणु
		perf_hpp_list__क्रम_each_क्रमmat(&node->hpp, fmt)
			perf_hpp__reset_width(fmt, hists);
	पूर्ण
पूर्ण

व्योम perf_hpp__set_user_width(स्थिर अक्षर *width_list_str)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	स्थिर अक्षर *ptr = width_list_str;

	perf_hpp_list__क्रम_each_क्रमmat(&perf_hpp_list, fmt) अणु
		अक्षर *p;

		पूर्णांक len = म_से_दीर्घ(ptr, &p, 10);
		fmt->user_len = len;

		अगर (*p == ',')
			ptr = p + 1;
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक add_hierarchy_fmt(काष्ठा hists *hists, काष्ठा perf_hpp_fmt *fmt)
अणु
	काष्ठा perf_hpp_list_node *node = शून्य;
	काष्ठा perf_hpp_fmt *fmt_copy;
	bool found = false;
	bool skip = perf_hpp__should_skip(fmt, hists);

	list_क्रम_each_entry(node, &hists->hpp_क्रमmats, list) अणु
		अगर (node->level == fmt->level) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		node = दो_स्मृति(माप(*node));
		अगर (node == शून्य)
			वापस -1;

		node->skip = skip;
		node->level = fmt->level;
		perf_hpp_list__init(&node->hpp);

		hists->nr_hpp_node++;
		list_add_tail(&node->list, &hists->hpp_क्रमmats);
	पूर्ण

	fmt_copy = perf_hpp_fmt__dup(fmt);
	अगर (fmt_copy == शून्य)
		वापस -1;

	अगर (!skip)
		node->skip = false;

	list_add_tail(&fmt_copy->list, &node->hpp.fields);
	list_add_tail(&fmt_copy->sort_list, &node->hpp.sorts);

	वापस 0;
पूर्ण

पूर्णांक perf_hpp__setup_hists_क्रमmats(काष्ठा perf_hpp_list *list,
				  काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा hists *hists;
	पूर्णांक ret;

	अगर (!symbol_conf.report_hierarchy)
		वापस 0;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		hists = evsel__hists(evsel);

		perf_hpp_list__क्रम_each_sort_list(list, fmt) अणु
			अगर (perf_hpp__is_dynamic_entry(fmt) &&
			    !perf_hpp__defined_dynamic_entry(fmt, hists))
				जारी;

			ret = add_hierarchy_fmt(hists, fmt);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
