<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <traceevent/event-parse.h>
#समावेश "evsel.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "util/event.h"
#समावेश "callchain.h"
#समावेश "map.h"
#समावेश "strlist.h"
#समावेश "symbol.h"
#समावेश "srcline.h"

अटल पूर्णांक comma_ख_लिखो(खाता *fp, bool *first, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक ret = 0;

	अगर (!*first) अणु
		ret += ख_लिखो(fp, ",");
	पूर्ण अन्यथा अणु
		ret += ख_लिखो(fp, ":");
		*first = false;
	पूर्ण

	बहु_शुरू(args, fmt);
	ret += भख_लिखो(fp, fmt, args);
	बहु_पूर्ण(args);
	वापस ret;
पूर्ण

अटल पूर्णांक __prपूर्णांक_attr__ख_लिखो(खाता *fp, स्थिर अक्षर *name, स्थिर अक्षर *val, व्योम *priv)
अणु
	वापस comma_ख_लिखो(fp, (bool *)priv, " %s: %s", name, val);
पूर्ण

पूर्णांक evsel__ख_लिखो(काष्ठा evsel *evsel, काष्ठा perf_attr_details *details, खाता *fp)
अणु
	bool first = true;
	पूर्णांक prपूर्णांकed = 0;

	अगर (details->event_group) अणु
		काष्ठा evsel *pos;

		अगर (!evsel__is_group_leader(evsel))
			वापस 0;

		अगर (evsel->core.nr_members > 1)
			prपूर्णांकed += ख_लिखो(fp, "%s{", evsel->group_name ?: "");

		prपूर्णांकed += ख_लिखो(fp, "%s", evsel__name(evsel));
		क्रम_each_group_member(pos, evsel)
			prपूर्णांकed += ख_लिखो(fp, ",%s", evsel__name(pos));

		अगर (evsel->core.nr_members > 1)
			prपूर्णांकed += ख_लिखो(fp, "}");
		जाओ out;
	पूर्ण

	prपूर्णांकed += ख_लिखो(fp, "%s", evsel__name(evsel));

	अगर (details->verbose) अणु
		prपूर्णांकed += perf_event_attr__ख_लिखो(fp, &evsel->core.attr,
						    __prपूर्णांक_attr__ख_लिखो, &first);
	पूर्ण अन्यथा अगर (details->freq) अणु
		स्थिर अक्षर *term = "sample_freq";

		अगर (!evsel->core.attr.freq)
			term = "sample_period";

		prपूर्णांकed += comma_ख_लिखो(fp, &first, " %s=%" PRIu64,
					 term, (u64)evsel->core.attr.sample_freq);
	पूर्ण

	अगर (details->trace_fields) अणु
		काष्ठा tep_क्रमmat_field *field;

		अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT) अणु
			prपूर्णांकed += comma_ख_लिखो(fp, &first, " (not a tracepoint)");
			जाओ out;
		पूर्ण

		field = evsel->tp_क्रमmat->क्रमmat.fields;
		अगर (field == शून्य) अणु
			prपूर्णांकed += comma_ख_लिखो(fp, &first, " (no trace field)");
			जाओ out;
		पूर्ण

		prपूर्णांकed += comma_ख_लिखो(fp, &first, " trace_fields: %s", field->name);

		field = field->next;
		जबतक (field) अणु
			prपूर्णांकed += comma_ख_लिखो(fp, &first, "%s", field->name);
			field = field->next;
		पूर्ण
	पूर्ण
out:
	ख_अक्षर_दो('\n', fp);
	वापस ++prपूर्णांकed;
पूर्ण

#अगर_अघोषित PYTHON_PERF
पूर्णांक sample__ख_लिखो_callchain(काष्ठा perf_sample *sample, पूर्णांक left_alignment,
			      अचिन्हित पूर्णांक prपूर्णांक_opts, काष्ठा callchain_cursor *cursor,
			      काष्ठा strlist *bt_stop_list, खाता *fp)
अणु
	पूर्णांक prपूर्णांकed = 0;
	काष्ठा callchain_cursor_node *node;
	पूर्णांक prपूर्णांक_ip = prपूर्णांक_opts & EVSEL__PRINT_IP;
	पूर्णांक prपूर्णांक_sym = prपूर्णांक_opts & EVSEL__PRINT_SYM;
	पूर्णांक prपूर्णांक_dso = prपूर्णांक_opts & EVSEL__PRINT_DSO;
	पूर्णांक prपूर्णांक_symoffset = prपूर्णांक_opts & EVSEL__PRINT_SYMOFFSET;
	पूर्णांक prपूर्णांक_oneline = prपूर्णांक_opts & EVSEL__PRINT_ONELINE;
	पूर्णांक prपूर्णांक_srcline = prपूर्णांक_opts & EVSEL__PRINT_SRCLINE;
	पूर्णांक prपूर्णांक_unknown_as_addr = prपूर्णांक_opts & EVSEL__PRINT_UNKNOWN_AS_ADDR;
	पूर्णांक prपूर्णांक_arrow = prपूर्णांक_opts & EVSEL__PRINT_CALLCHAIN_ARROW;
	पूर्णांक prपूर्णांक_skip_ignored = prपूर्णांक_opts & EVSEL__PRINT_SKIP_IGNORED;
	अक्षर s = prपूर्णांक_oneline ? ' ' : '\t';
	bool first = true;

	अगर (sample->callchain) अणु
		काष्ठा addr_location node_al;

		callchain_cursor_commit(cursor);

		जबतक (1) अणु
			काष्ठा symbol *sym;
			काष्ठा map *map;
			u64 addr = 0;

			node = callchain_cursor_current(cursor);
			अगर (!node)
				अवरोध;

			sym = node->ms.sym;
			map = node->ms.map;

			अगर (sym && sym->ignore && prपूर्णांक_skip_ignored)
				जाओ next;

			prपूर्णांकed += ख_लिखो(fp, "%-*.*s", left_alignment, left_alignment, " ");

			अगर (prपूर्णांक_arrow && !first)
				prपूर्णांकed += ख_लिखो(fp, " <-");

			अगर (prपूर्णांक_ip)
				prपूर्णांकed += ख_लिखो(fp, "%c%16" PRIx64, s, node->ip);

			अगर (map)
				addr = map->map_ip(map, node->ip);

			अगर (prपूर्णांक_sym) अणु
				prपूर्णांकed += ख_लिखो(fp, " ");
				node_al.addr = addr;
				node_al.map  = map;

				अगर (prपूर्णांक_symoffset) अणु
					prपूर्णांकed += __symbol__ख_लिखो_symname_offs(sym, &node_al,
										  prपूर्णांक_unknown_as_addr,
										  true, fp);
				पूर्ण अन्यथा अणु
					prपूर्णांकed += __symbol__ख_लिखो_symname(sym, &node_al,
									     prपूर्णांक_unknown_as_addr, fp);
				पूर्ण
			पूर्ण

			अगर (prपूर्णांक_dso && (!sym || !sym->अंतरभूतd)) अणु
				prपूर्णांकed += ख_लिखो(fp, " (");
				prपूर्णांकed += map__ख_लिखो_dsoname(map, fp);
				prपूर्णांकed += ख_लिखो(fp, ")");
			पूर्ण

			अगर (prपूर्णांक_srcline)
				prपूर्णांकed += map__ख_लिखो_srcline(map, addr, "\n  ", fp);

			अगर (sym && sym->अंतरभूतd)
				prपूर्णांकed += ख_लिखो(fp, " (inlined)");

			अगर (!prपूर्णांक_oneline)
				prपूर्णांकed += ख_लिखो(fp, "\n");

			/* Add srccode here too? */
			अगर (bt_stop_list && sym &&
			    strlist__has_entry(bt_stop_list, sym->name)) अणु
				अवरोध;
			पूर्ण

			first = false;
next:
			callchain_cursor_advance(cursor);
		पूर्ण
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

पूर्णांक sample__ख_लिखो_sym(काष्ठा perf_sample *sample, काष्ठा addr_location *al,
			पूर्णांक left_alignment, अचिन्हित पूर्णांक prपूर्णांक_opts,
			काष्ठा callchain_cursor *cursor, काष्ठा strlist *bt_stop_list, खाता *fp)
अणु
	पूर्णांक prपूर्णांकed = 0;
	पूर्णांक prपूर्णांक_ip = prपूर्णांक_opts & EVSEL__PRINT_IP;
	पूर्णांक prपूर्णांक_sym = prपूर्णांक_opts & EVSEL__PRINT_SYM;
	पूर्णांक prपूर्णांक_dso = prपूर्णांक_opts & EVSEL__PRINT_DSO;
	पूर्णांक prपूर्णांक_symoffset = prपूर्णांक_opts & EVSEL__PRINT_SYMOFFSET;
	पूर्णांक prपूर्णांक_srcline = prपूर्णांक_opts & EVSEL__PRINT_SRCLINE;
	पूर्णांक prपूर्णांक_unknown_as_addr = prपूर्णांक_opts & EVSEL__PRINT_UNKNOWN_AS_ADDR;

	अगर (cursor != शून्य) अणु
		prपूर्णांकed += sample__ख_लिखो_callchain(sample, left_alignment, prपूर्णांक_opts,
						     cursor, bt_stop_list, fp);
	पूर्ण अन्यथा अणु
		prपूर्णांकed += ख_लिखो(fp, "%-*.*s", left_alignment, left_alignment, " ");

		अगर (prपूर्णांक_ip)
			prपूर्णांकed += ख_लिखो(fp, "%16" PRIx64, sample->ip);

		अगर (prपूर्णांक_sym) अणु
			prपूर्णांकed += ख_लिखो(fp, " ");
			अगर (prपूर्णांक_symoffset) अणु
				prपूर्णांकed += __symbol__ख_लिखो_symname_offs(al->sym, al,
									  prपूर्णांक_unknown_as_addr,
									  true, fp);
			पूर्ण अन्यथा अणु
				prपूर्णांकed += __symbol__ख_लिखो_symname(al->sym, al,
								     prपूर्णांक_unknown_as_addr, fp);
			पूर्ण
		पूर्ण

		अगर (prपूर्णांक_dso) अणु
			prपूर्णांकed += ख_लिखो(fp, " (");
			prपूर्णांकed += map__ख_लिखो_dsoname(al->map, fp);
			prपूर्णांकed += ख_लिखो(fp, ")");
		पूर्ण

		अगर (prपूर्णांक_srcline)
			prपूर्णांकed += map__ख_लिखो_srcline(al->map, al->addr, "\n  ", fp);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण
#पूर्ण_अगर /* PYTHON_PERF */
