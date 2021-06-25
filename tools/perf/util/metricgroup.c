<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, Intel Corporation.
 */

/* Manage metrics and groups of metrics from JSON files */

#समावेश "metricgroup.h"
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "strbuf.h"
#समावेश "pmu.h"
#समावेश "expr.h"
#समावेश "rblist.h"
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश "strlist.h"
#समावेश <निश्चित.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <subcmd/parse-options.h>
#समावेश <api/fs/fs.h>
#समावेश "util.h"
#समावेश <यंत्र/bug.h>
#समावेश "cgroup.h"

काष्ठा metric_event *metricgroup__lookup(काष्ठा rblist *metric_events,
					 काष्ठा evsel *evsel,
					 bool create)
अणु
	काष्ठा rb_node *nd;
	काष्ठा metric_event me = अणु
		.evsel = evsel
	पूर्ण;

	अगर (!metric_events)
		वापस शून्य;

	nd = rblist__find(metric_events, &me);
	अगर (nd)
		वापस container_of(nd, काष्ठा metric_event, nd);
	अगर (create) अणु
		rblist__add_node(metric_events, &me);
		nd = rblist__find(metric_events, &me);
		अगर (nd)
			वापस container_of(nd, काष्ठा metric_event, nd);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक metric_event_cmp(काष्ठा rb_node *rb_node, स्थिर व्योम *entry)
अणु
	काष्ठा metric_event *a = container_of(rb_node,
					      काष्ठा metric_event,
					      nd);
	स्थिर काष्ठा metric_event *b = entry;

	अगर (a->evsel == b->evsel)
		वापस 0;
	अगर ((अक्षर *)a->evsel < (अक्षर *)b->evsel)
		वापस -1;
	वापस +1;
पूर्ण

अटल काष्ठा rb_node *metric_event_new(काष्ठा rblist *rblist __maybe_unused,
					स्थिर व्योम *entry)
अणु
	काष्ठा metric_event *me = दो_स्मृति(माप(काष्ठा metric_event));

	अगर (!me)
		वापस शून्य;
	स_नकल(me, entry, माप(काष्ठा metric_event));
	me->evsel = ((काष्ठा metric_event *)entry)->evsel;
	INIT_LIST_HEAD(&me->head);
	वापस &me->nd;
पूर्ण

अटल व्योम metric_event_delete(काष्ठा rblist *rblist __maybe_unused,
				काष्ठा rb_node *rb_node)
अणु
	काष्ठा metric_event *me = container_of(rb_node, काष्ठा metric_event, nd);
	काष्ठा metric_expr *expr, *पंचांगp;

	list_क्रम_each_entry_safe(expr, पंचांगp, &me->head, nd) अणु
		मुक्त(expr->metric_refs);
		मुक्त(expr->metric_events);
		मुक्त(expr);
	पूर्ण

	मुक्त(me);
पूर्ण

अटल व्योम metricgroup__rblist_init(काष्ठा rblist *metric_events)
अणु
	rblist__init(metric_events);
	metric_events->node_cmp = metric_event_cmp;
	metric_events->node_new = metric_event_new;
	metric_events->node_delete = metric_event_delete;
पूर्ण

व्योम metricgroup__rblist_निकास(काष्ठा rblist *metric_events)
अणु
	rblist__निकास(metric_events);
पूर्ण

/*
 * A node in the list of referenced metrics. metric_expr
 * is held as a convenience to aव्योम a search through the
 * metric list.
 */
काष्ठा metric_ref_node अणु
	स्थिर अक्षर *metric_name;
	स्थिर अक्षर *metric_expr;
	काष्ठा list_head list;
पूर्ण;

काष्ठा metric अणु
	काष्ठा list_head nd;
	काष्ठा expr_parse_ctx pctx;
	स्थिर अक्षर *metric_name;
	स्थिर अक्षर *metric_expr;
	स्थिर अक्षर *metric_unit;
	काष्ठा list_head metric_refs;
	पूर्णांक metric_refs_cnt;
	पूर्णांक runसमय;
	bool has_स्थिरraपूर्णांक;
पूर्ण;

#घोषणा RECURSION_ID_MAX 1000

काष्ठा expr_ids अणु
	काष्ठा expr_id	id[RECURSION_ID_MAX];
	पूर्णांक		cnt;
पूर्ण;

अटल काष्ठा expr_id *expr_ids__alloc(काष्ठा expr_ids *ids)
अणु
	अगर (ids->cnt >= RECURSION_ID_MAX)
		वापस शून्य;
	वापस &ids->id[ids->cnt++];
पूर्ण

अटल व्योम expr_ids__निकास(काष्ठा expr_ids *ids)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ids->cnt; i++)
		मुक्त(ids->id[i].id);
पूर्ण

अटल bool contains_event(काष्ठा evsel **metric_events, पूर्णांक num_events,
			स्थिर अक्षर *event_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_events; i++) अणु
		अगर (!म_भेद(metric_events[i]->name, event_name))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool evsel_same_pmu_or_none(काष्ठा evsel *ev1, काष्ठा evsel *ev2)
अणु
	अगर (!ev1->pmu_name || !ev2->pmu_name)
		वापस true;

	वापस !म_भेद(ev1->pmu_name, ev2->pmu_name);
पूर्ण

/**
 * Find a group of events in perf_evlist that correspond to those from a parsed
 * metric expression. Note, as find_evsel_group is called in the same order as
 * perf_evlist was स्थिरructed, metric_no_merge करोesn't need to test क्रम
 * underfilling a group.
 * @perf_evlist: a list of events something like: अणुmetric1 leader, metric1
 * sibling, metric1 siblingपूर्ण:W,duration_समय,अणुmetric2 leader, metric2 sibling,
 * metric2 siblingपूर्ण:W,duration_समय
 * @pctx: the parse context क्रम the metric expression.
 * @metric_no_merge: करोn't attempt to share events क्रम the metric with other
 * metrics.
 * @has_स्थिरraपूर्णांक: is there a स्थिरraपूर्णांक on the group of events? In which हाल
 * the events won't be grouped.
 * @metric_events: out argument, null terminated array of evsel's associated
 * with the metric.
 * @evlist_used: in/out argument, biपंचांगap tracking which evlist events are used.
 * @वापस the first metric event or शून्य on failure.
 */
अटल काष्ठा evsel *find_evsel_group(काष्ठा evlist *perf_evlist,
				      काष्ठा expr_parse_ctx *pctx,
				      bool metric_no_merge,
				      bool has_स्थिरraपूर्णांक,
				      काष्ठा evsel **metric_events,
				      अचिन्हित दीर्घ *evlist_used)
अणु
	काष्ठा evsel *ev, *current_leader = शून्य;
	काष्ठा expr_id_data *val_ptr;
	पूर्णांक i = 0, matched_events = 0, events_to_match;
	स्थिर पूर्णांक idnum = (पूर्णांक)hashmap__size(&pctx->ids);

	/*
	 * duration_समय is always grouped separately, when events are grouped
	 * (ie has_स्थिरraपूर्णांक is false) then ignore it in the matching loop and
	 * add it to metric_events at the end.
	 */
	अगर (!has_स्थिरraपूर्णांक &&
	    hashmap__find(&pctx->ids, "duration_time", (व्योम **)&val_ptr))
		events_to_match = idnum - 1;
	अन्यथा
		events_to_match = idnum;

	evlist__क्रम_each_entry (perf_evlist, ev) अणु
		/*
		 * Events with a स्थिरraपूर्णांक aren't grouped and match the first
		 * events available.
		 */
		अगर (has_स्थिरraपूर्णांक && ev->weak_group)
			जारी;
		/* Ignore event अगर alपढ़ोy used and merging is disabled. */
		अगर (metric_no_merge && test_bit(ev->idx, evlist_used))
			जारी;
		अगर (!has_स्थिरraपूर्णांक && ev->leader != current_leader) अणु
			/*
			 * Start of a new group, discard the whole match and
			 * start again.
			 */
			matched_events = 0;
			स_रखो(metric_events, 0,
				माप(काष्ठा evsel *) * idnum);
			current_leader = ev->leader;
		पूर्ण
		/*
		 * Check क्रम duplicate events with the same name. For example,
		 * uncore_imc/cas_count_पढ़ो/ will turn पूर्णांकo 6 events per socket
		 * on skylakex. Only the first such event is placed in
		 * metric_events. If events aren't grouped then this also
		 * ensures that the same event in dअगरferent sibling groups
		 * aren't both added to metric_events.
		 */
		अगर (contains_event(metric_events, matched_events, ev->name))
			जारी;
		/* Does this event beदीर्घ to the parse context? */
		अगर (hashmap__find(&pctx->ids, ev->name, (व्योम **)&val_ptr))
			metric_events[matched_events++] = ev;

		अगर (matched_events == events_to_match)
			अवरोध;
	पूर्ण

	अगर (events_to_match != idnum) अणु
		/* Add the first duration_समय. */
		evlist__क्रम_each_entry(perf_evlist, ev) अणु
			अगर (!म_भेद(ev->name, "duration_time")) अणु
				metric_events[matched_events++] = ev;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (matched_events != idnum) अणु
		/* Not a whole match */
		वापस शून्य;
	पूर्ण

	metric_events[idnum] = शून्य;

	क्रम (i = 0; i < idnum; i++) अणु
		ev = metric_events[i];
		/* Don't मुक्त the used events. */
		set_bit(ev->idx, evlist_used);
		/*
		 * The metric leader poपूर्णांकs to the identically named event in
		 * metric_events.
		 */
		ev->metric_leader = ev;
		/*
		 * Mark two events with identical names in the same group (or
		 * globally) as being in use as uncore events may be duplicated
		 * क्रम each pmu. Set the metric leader of such events to be the
		 * event that appears in metric_events.
		 */
		evlist__क्रम_each_entry_जारी(perf_evlist, ev) अणु
			/*
			 * If events are grouped then the search can terminate
			 * when then group is left.
			 */
			अगर (!has_स्थिरraपूर्णांक &&
			    ev->leader != metric_events[i]->leader &&
			    evsel_same_pmu_or_none(ev->leader, metric_events[i]->leader))
				अवरोध;
			अगर (!म_भेद(metric_events[i]->name, ev->name)) अणु
				set_bit(ev->idx, evlist_used);
				ev->metric_leader = metric_events[i];
			पूर्ण
		पूर्ण
	पूर्ण

	वापस metric_events[0];
पूर्ण

अटल पूर्णांक metricgroup__setup_events(काष्ठा list_head *groups,
				     bool metric_no_merge,
				     काष्ठा evlist *perf_evlist,
				     काष्ठा rblist *metric_events_list)
अणु
	काष्ठा metric_event *me;
	काष्ठा metric_expr *expr;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;
	काष्ठा metric *m;
	काष्ठा evsel *evsel, *पंचांगp;
	अचिन्हित दीर्घ *evlist_used;

	evlist_used = biपंचांगap_alloc(perf_evlist->core.nr_entries);
	अगर (!evlist_used)
		वापस -ENOMEM;

	list_क्रम_each_entry (m, groups, nd) अणु
		काष्ठा evsel **metric_events;
		काष्ठा metric_ref *metric_refs = शून्य;

		metric_events = सुस्मृति(माप(व्योम *),
				hashmap__size(&m->pctx.ids) + 1);
		अगर (!metric_events) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		evsel = find_evsel_group(perf_evlist, &m->pctx,
					 metric_no_merge,
					 m->has_स्थिरraपूर्णांक, metric_events,
					 evlist_used);
		अगर (!evsel) अणु
			pr_debug("Cannot resolve %s: %s\n",
					m->metric_name, m->metric_expr);
			मुक्त(metric_events);
			जारी;
		पूर्ण
		क्रम (i = 0; metric_events[i]; i++)
			metric_events[i]->collect_stat = true;
		me = metricgroup__lookup(metric_events_list, evsel, true);
		अगर (!me) अणु
			ret = -ENOMEM;
			मुक्त(metric_events);
			अवरोध;
		पूर्ण
		expr = दो_स्मृति(माप(काष्ठा metric_expr));
		अगर (!expr) अणु
			ret = -ENOMEM;
			मुक्त(metric_events);
			अवरोध;
		पूर्ण

		/*
		 * Collect and store collected nested expressions
		 * क्रम metric processing.
		 */
		अगर (m->metric_refs_cnt) अणु
			काष्ठा metric_ref_node *ref;

			metric_refs = zalloc(माप(काष्ठा metric_ref) * (m->metric_refs_cnt + 1));
			अगर (!metric_refs) अणु
				ret = -ENOMEM;
				मुक्त(metric_events);
				मुक्त(expr);
				अवरोध;
			पूर्ण

			i = 0;
			list_क्रम_each_entry(ref, &m->metric_refs, list) अणु
				/*
				 * Intentionally passing just स्थिर अक्षर poपूर्णांकers,
				 * originally from 'struct pmu_event' object.
				 * We करोn't need to change them, so there's no
				 * need to create our own copy.
				 */
				metric_refs[i].metric_name = ref->metric_name;
				metric_refs[i].metric_expr = ref->metric_expr;
				i++;
			पूर्ण
		पूर्ण

		expr->metric_refs = metric_refs;
		expr->metric_expr = m->metric_expr;
		expr->metric_name = m->metric_name;
		expr->metric_unit = m->metric_unit;
		expr->metric_events = metric_events;
		expr->runसमय = m->runसमय;
		list_add(&expr->nd, &me->head);
	पूर्ण

	evlist__क्रम_each_entry_safe(perf_evlist, पंचांगp, evsel) अणु
		अगर (!test_bit(evsel->idx, evlist_used)) अणु
			evlist__हटाओ(perf_evlist, evsel);
			evsel__delete(evsel);
		पूर्ण
	पूर्ण
	biपंचांगap_मुक्त(evlist_used);

	वापस ret;
पूर्ण

अटल bool match_metric(स्थिर अक्षर *n, स्थिर अक्षर *list)
अणु
	पूर्णांक len;
	अक्षर *m;

	अगर (!list)
		वापस false;
	अगर (!म_भेद(list, "all"))
		वापस true;
	अगर (!n)
		वापस !strहालcmp(list, "No_group");
	len = म_माप(list);
	m = strहालstr(n, list);
	अगर (!m)
		वापस false;
	अगर ((m == n || m[-1] == ';' || m[-1] == ' ') &&
	    (m[len] == 0 || m[len] == ';'))
		वापस true;
	वापस false;
पूर्ण

अटल bool match_pe_metric(काष्ठा pmu_event *pe, स्थिर अक्षर *metric)
अणु
	वापस match_metric(pe->metric_group, metric) ||
	       match_metric(pe->metric_name, metric);
पूर्ण

काष्ठा mep अणु
	काष्ठा rb_node nd;
	स्थिर अक्षर *name;
	काष्ठा strlist *metrics;
पूर्ण;

अटल पूर्णांक mep_cmp(काष्ठा rb_node *rb_node, स्थिर व्योम *entry)
अणु
	काष्ठा mep *a = container_of(rb_node, काष्ठा mep, nd);
	काष्ठा mep *b = (काष्ठा mep *)entry;

	वापस म_भेद(a->name, b->name);
पूर्ण

अटल काष्ठा rb_node *mep_new(काष्ठा rblist *rl __maybe_unused,
					स्थिर व्योम *entry)
अणु
	काष्ठा mep *me = दो_स्मृति(माप(काष्ठा mep));

	अगर (!me)
		वापस शून्य;
	स_नकल(me, entry, माप(काष्ठा mep));
	me->name = strdup(me->name);
	अगर (!me->name)
		जाओ out_me;
	me->metrics = strlist__new(शून्य, शून्य);
	अगर (!me->metrics)
		जाओ out_name;
	वापस &me->nd;
out_name:
	zमुक्त(&me->name);
out_me:
	मुक्त(me);
	वापस शून्य;
पूर्ण

अटल काष्ठा mep *mep_lookup(काष्ठा rblist *groups, स्थिर अक्षर *name)
अणु
	काष्ठा rb_node *nd;
	काष्ठा mep me = अणु
		.name = name
	पूर्ण;
	nd = rblist__find(groups, &me);
	अगर (nd)
		वापस container_of(nd, काष्ठा mep, nd);
	rblist__add_node(groups, &me);
	nd = rblist__find(groups, &me);
	अगर (nd)
		वापस container_of(nd, काष्ठा mep, nd);
	वापस शून्य;
पूर्ण

अटल व्योम mep_delete(काष्ठा rblist *rl __maybe_unused,
		       काष्ठा rb_node *nd)
अणु
	काष्ठा mep *me = container_of(nd, काष्ठा mep, nd);

	strlist__delete(me->metrics);
	zमुक्त(&me->name);
	मुक्त(me);
पूर्ण

अटल व्योम metricgroup__prपूर्णांक_strlist(काष्ठा strlist *metrics, bool raw)
अणु
	काष्ठा str_node *sn;
	पूर्णांक n = 0;

	strlist__क्रम_each_entry (sn, metrics) अणु
		अगर (raw)
			म_लिखो("%s%s", n > 0 ? " " : "", sn->s);
		अन्यथा
			म_लिखो("  %s\n", sn->s);
		n++;
	पूर्ण
	अगर (raw)
		अक्षर_दो('\n');
पूर्ण

अटल पूर्णांक metricgroup__prपूर्णांक_pmu_event(काष्ठा pmu_event *pe,
					bool metricgroups, अक्षर *filter,
					bool raw, bool details,
					काष्ठा rblist *groups,
					काष्ठा strlist *metriclist)
अणु
	स्थिर अक्षर *g;
	अक्षर *omg, *mg;

	g = pe->metric_group;
	अगर (!g && pe->metric_name) अणु
		अगर (pe->name)
			वापस 0;
		g = "No_group";
	पूर्ण

	अगर (!g)
		वापस 0;

	mg = strdup(g);

	अगर (!mg)
		वापस -ENOMEM;
	omg = mg;
	जबतक ((g = strsep(&mg, ";")) != शून्य) अणु
		काष्ठा mep *me;
		अक्षर *s;

		g = skip_spaces(g);
		अगर (*g == 0)
			g = "No_group";
		अगर (filter && !म_माला(g, filter))
			जारी;
		अगर (raw)
			s = (अक्षर *)pe->metric_name;
		अन्यथा अणु
			अगर (aप्र_लिखो(&s, "%s\n%*s%s]",
				     pe->metric_name, 8, "[", pe->desc) < 0)
				वापस -1;
			अगर (details) अणु
				अगर (aप्र_लिखो(&s, "%s\n%*s%s]",
					     s, 8, "[", pe->metric_expr) < 0)
					वापस -1;
			पूर्ण
		पूर्ण

		अगर (!s)
			जारी;

		अगर (!metricgroups) अणु
			strlist__add(metriclist, s);
		पूर्ण अन्यथा अणु
			me = mep_lookup(groups, g);
			अगर (!me)
				जारी;
			strlist__add(me->metrics, s);
		पूर्ण

		अगर (!raw)
			मुक्त(s);
	पूर्ण
	मुक्त(omg);

	वापस 0;
पूर्ण

काष्ठा metricgroup_prपूर्णांक_sys_idata अणु
	काष्ठा strlist *metriclist;
	अक्षर *filter;
	काष्ठा rblist *groups;
	bool metricgroups;
	bool raw;
	bool details;
पूर्ण;

प्रकार पूर्णांक (*metricgroup_sys_event_iter_fn)(काष्ठा pmu_event *pe, व्योम *);

काष्ठा metricgroup_iter_data अणु
	metricgroup_sys_event_iter_fn fn;
	व्योम *data;
पूर्ण;

अटल पूर्णांक metricgroup__sys_event_iter(काष्ठा pmu_event *pe, व्योम *data)
अणु
	काष्ठा metricgroup_iter_data *d = data;
	काष्ठा perf_pmu *pmu = शून्य;

	अगर (!pe->metric_expr || !pe->compat)
		वापस 0;

	जबतक ((pmu = perf_pmu__scan(pmu))) अणु

		अगर (!pmu->id || म_भेद(pmu->id, pe->compat))
			जारी;

		वापस d->fn(pe, d->data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक metricgroup__prपूर्णांक_sys_event_iter(काष्ठा pmu_event *pe, व्योम *data)
अणु
	काष्ठा metricgroup_prपूर्णांक_sys_idata *d = data;

	वापस metricgroup__prपूर्णांक_pmu_event(pe, d->metricgroups, d->filter, d->raw,
				     d->details, d->groups, d->metriclist);
पूर्ण

व्योम metricgroup__prपूर्णांक(bool metrics, bool metricgroups, अक्षर *filter,
			bool raw, bool details)
अणु
	काष्ठा pmu_events_map *map = pmu_events_map__find();
	काष्ठा pmu_event *pe;
	पूर्णांक i;
	काष्ठा rblist groups;
	काष्ठा rb_node *node, *next;
	काष्ठा strlist *metriclist = शून्य;

	अगर (!metricgroups) अणु
		metriclist = strlist__new(शून्य, शून्य);
		अगर (!metriclist)
			वापस;
	पूर्ण

	rblist__init(&groups);
	groups.node_new = mep_new;
	groups.node_cmp = mep_cmp;
	groups.node_delete = mep_delete;
	क्रम (i = 0; map; i++) अणु
		pe = &map->table[i];

		अगर (!pe->name && !pe->metric_group && !pe->metric_name)
			अवरोध;
		अगर (!pe->metric_expr)
			जारी;
		अगर (metricgroup__prपूर्णांक_pmu_event(pe, metricgroups, filter,
						 raw, details, &groups,
						 metriclist) < 0)
			वापस;
	पूर्ण

	अणु
		काष्ठा metricgroup_iter_data data = अणु
			.fn = metricgroup__prपूर्णांक_sys_event_iter,
			.data = (व्योम *) &(काष्ठा metricgroup_prपूर्णांक_sys_idata)अणु
				.metriclist = metriclist,
				.metricgroups = metricgroups,
				.filter = filter,
				.raw = raw,
				.details = details,
				.groups = &groups,
			पूर्ण,
		पूर्ण;

		pmu_क्रम_each_sys_event(metricgroup__sys_event_iter, &data);
	पूर्ण

	अगर (!filter || !rblist__empty(&groups)) अणु
		अगर (metricgroups && !raw)
			म_लिखो("\nMetric Groups:\n\n");
		अन्यथा अगर (metrics && !raw)
			म_लिखो("\nMetrics:\n\n");
	पूर्ण

	क्रम (node = rb_first_cached(&groups.entries); node; node = next) अणु
		काष्ठा mep *me = container_of(node, काष्ठा mep, nd);

		अगर (metricgroups)
			म_लिखो("%s%s%s", me->name, metrics && !raw ? ":" : "", raw ? " " : "\n");
		अगर (metrics)
			metricgroup__prपूर्णांक_strlist(me->metrics, raw);
		next = rb_next(node);
		rblist__हटाओ_node(&groups, node);
	पूर्ण
	अगर (!metricgroups)
		metricgroup__prपूर्णांक_strlist(metriclist, raw);
	strlist__delete(metriclist);
पूर्ण

अटल व्योम metricgroup__add_metric_weak_group(काष्ठा strbuf *events,
					       काष्ठा expr_parse_ctx *ctx)
अणु
	काष्ठा hashmap_entry *cur;
	माप_प्रकार bkt;
	bool no_group = true, has_duration = false;

	hashmap__क्रम_each_entry((&ctx->ids), cur, bkt) अणु
		pr_debug("found event %s\n", (स्थिर अक्षर *)cur->key);
		/*
		 * Duration समय maps to a software event and can make
		 * groups not count. Always use it outside a
		 * group.
		 */
		अगर (!म_भेद(cur->key, "duration_time")) अणु
			has_duration = true;
			जारी;
		पूर्ण
		strbuf_addf(events, "%s%s",
			no_group ? "{" : ",",
			(स्थिर अक्षर *)cur->key);
		no_group = false;
	पूर्ण
	अगर (!no_group) अणु
		strbuf_addf(events, "}:W");
		अगर (has_duration)
			strbuf_addf(events, ",duration_time");
	पूर्ण अन्यथा अगर (has_duration)
		strbuf_addf(events, "duration_time");
पूर्ण

अटल व्योम metricgroup__add_metric_non_group(काष्ठा strbuf *events,
					      काष्ठा expr_parse_ctx *ctx)
अणु
	काष्ठा hashmap_entry *cur;
	माप_प्रकार bkt;
	bool first = true;

	hashmap__क्रम_each_entry((&ctx->ids), cur, bkt) अणु
		अगर (!first)
			strbuf_addf(events, ",");
		strbuf_addf(events, "%s", (स्थिर अक्षर *)cur->key);
		first = false;
	पूर्ण
पूर्ण

अटल व्योम metricgroup___watchकरोg_स्थिरraपूर्णांक_hपूर्णांक(स्थिर अक्षर *name, bool foot)
अणु
	अटल bool violate_nmi_स्थिरraपूर्णांक;

	अगर (!foot) अणु
		pr_warning("Splitting metric group %s into standalone metrics.\n", name);
		violate_nmi_स्थिरraपूर्णांक = true;
		वापस;
	पूर्ण

	अगर (!violate_nmi_स्थिरraपूर्णांक)
		वापस;

	pr_warning("Try disabling the NMI watchdog to comply NO_NMI_WATCHDOG metric constraint:\n"
		   "    echo 0 > /proc/sys/kernel/nmi_watchdog\n"
		   "    perf stat ...\n"
		   "    echo 1 > /proc/sys/kernel/nmi_watchdog\n");
पूर्ण

अटल bool metricgroup__has_स्थिरraपूर्णांक(काष्ठा pmu_event *pe)
अणु
	अगर (!pe->metric_स्थिरraपूर्णांक)
		वापस false;

	अगर (!म_भेद(pe->metric_स्थिरraपूर्णांक, "NO_NMI_WATCHDOG") &&
	    sysctl__nmi_watchकरोg_enabled()) अणु
		metricgroup___watchकरोg_स्थिरraपूर्णांक_hपूर्णांक(pe->metric_name, false);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक __weak arch_get_runसमयparam(काष्ठा pmu_event *pe __maybe_unused)
अणु
	वापस 1;
पूर्ण

काष्ठा metricgroup_add_iter_data अणु
	काष्ठा list_head *metric_list;
	स्थिर अक्षर *metric;
	काष्ठा expr_ids *ids;
	पूर्णांक *ret;
	bool *has_match;
	bool metric_no_group;
पूर्ण;

अटल पूर्णांक __add_metric(काष्ठा list_head *metric_list,
			काष्ठा pmu_event *pe,
			bool metric_no_group,
			पूर्णांक runसमय,
			काष्ठा metric **mp,
			काष्ठा expr_id *parent,
			काष्ठा expr_ids *ids)
अणु
	काष्ठा metric_ref_node *ref;
	काष्ठा metric *m;

	अगर (*mp == शून्य) अणु
		/*
		 * We got in here क्रम the parent group,
		 * allocate it and put it on the list.
		 */
		m = zalloc(माप(*m));
		अगर (!m)
			वापस -ENOMEM;

		expr__ctx_init(&m->pctx);
		m->metric_name = pe->metric_name;
		m->metric_expr = pe->metric_expr;
		m->metric_unit = pe->unit;
		m->runसमय = runसमय;
		m->has_स्थिरraपूर्णांक = metric_no_group || metricgroup__has_स्थिरraपूर्णांक(pe);
		INIT_LIST_HEAD(&m->metric_refs);
		m->metric_refs_cnt = 0;

		parent = expr_ids__alloc(ids);
		अगर (!parent) अणु
			मुक्त(m);
			वापस -EINVAL;
		पूर्ण

		parent->id = strdup(pe->metric_name);
		अगर (!parent->id) अणु
			मुक्त(m);
			वापस -ENOMEM;
		पूर्ण
		*mp = m;
	पूर्ण अन्यथा अणु
		/*
		 * We got here क्रम the referenced metric, via the
		 * recursive metricgroup__add_metric call, add
		 * it to the parent group.
		 */
		m = *mp;

		ref = दो_स्मृति(माप(*ref));
		अगर (!ref)
			वापस -ENOMEM;

		/*
		 * Intentionally passing just स्थिर अक्षर poपूर्णांकers,
		 * from 'pe' object, so they never go away. We don't
		 * need to change them, so there's no need to create
		 * our own copy.
		 */
		ref->metric_name = pe->metric_name;
		ref->metric_expr = pe->metric_expr;

		list_add(&ref->list, &m->metric_refs);
		m->metric_refs_cnt++;
	पूर्ण

	/* Force all found IDs in metric to have us as parent ID. */
	WARN_ON_ONCE(!parent);
	m->pctx.parent = parent;

	/*
	 * For both the parent and referenced metrics, we parse
	 * all the metric's IDs and add it to the parent context.
	 */
	अगर (expr__find_other(pe->metric_expr, शून्य, &m->pctx, runसमय) < 0) अणु
		अगर (m->metric_refs_cnt == 0) अणु
			expr__ctx_clear(&m->pctx);
			मुक्त(m);
			*mp = शून्य;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/*
	 * We add new group only in the 'parent' call,
	 * so bail out क्रम referenced metric हाल.
	 */
	अगर (m->metric_refs_cnt)
		वापस 0;

	अगर (list_empty(metric_list))
		list_add(&m->nd, metric_list);
	अन्यथा अणु
		काष्ठा list_head *pos;

		/* Place the largest groups at the front. */
		list_क्रम_each_prev(pos, metric_list) अणु
			काष्ठा metric *old = list_entry(pos, काष्ठा metric, nd);

			अगर (hashmap__size(&m->pctx.ids) <=
			    hashmap__size(&old->pctx.ids))
				अवरोध;
		पूर्ण
		list_add(&m->nd, pos);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा map_क्रम_each_event(__pe, __idx, __map)					\
	अगर (__map)								\
		क्रम (__idx = 0, __pe = &__map->table[__idx];			\
		     __pe->name || __pe->metric_group || __pe->metric_name;	\
		     __pe = &__map->table[++__idx])

#घोषणा map_क्रम_each_metric(__pe, __idx, __map, __metric)		\
	map_क्रम_each_event(__pe, __idx, __map)				\
		अगर (__pe->metric_expr &&				\
		    (match_metric(__pe->metric_group, __metric) ||	\
		     match_metric(__pe->metric_name, __metric)))

काष्ठा pmu_event *metricgroup__find_metric(स्थिर अक्षर *metric,
					   काष्ठा pmu_events_map *map)
अणु
	काष्ठा pmu_event *pe;
	पूर्णांक i;

	map_क्रम_each_event(pe, i, map) अणु
		अगर (match_metric(pe->metric_name, metric))
			वापस pe;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक recursion_check(काष्ठा metric *m, स्थिर अक्षर *id, काष्ठा expr_id **parent,
			   काष्ठा expr_ids *ids)
अणु
	काष्ठा expr_id_data *data;
	काष्ठा expr_id *p;
	पूर्णांक ret;

	/*
	 * We get the parent referenced by 'id' argument and
	 * traverse through all the parent object IDs to check
	 * अगर we alपढ़ोy processed 'id', if we did, it's recursion
	 * and we fail.
	 */
	ret = expr__get_id(&m->pctx, id, &data);
	अगर (ret)
		वापस ret;

	p = expr_id_data__parent(data);

	जबतक (p->parent) अणु
		अगर (!म_भेद(p->id, id)) अणु
			pr_err("failed: recursion detected for %s\n", id);
			वापस -1;
		पूर्ण
		p = p->parent;
	पूर्ण

	/*
	 * If we are over the limit of अटल entris, the metric
	 * is too dअगरficult/nested to process, fail as well.
	 */
	p = expr_ids__alloc(ids);
	अगर (!p) अणु
		pr_err("failed: too many nested metrics\n");
		वापस -EINVAL;
	पूर्ण

	p->id     = strdup(id);
	p->parent = expr_id_data__parent(data);
	*parent   = p;

	वापस p->id ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक add_metric(काष्ठा list_head *metric_list,
		      काष्ठा pmu_event *pe,
		      bool metric_no_group,
		      काष्ठा metric **mp,
		      काष्ठा expr_id *parent,
		      काष्ठा expr_ids *ids);

अटल पूर्णांक __resolve_metric(काष्ठा metric *m,
			    bool metric_no_group,
			    काष्ठा list_head *metric_list,
			    काष्ठा pmu_events_map *map,
			    काष्ठा expr_ids *ids)
अणु
	काष्ठा hashmap_entry *cur;
	माप_प्रकार bkt;
	bool all;
	पूर्णांक ret;

	/*
	 * Iterate all the parsed IDs and अगर there's metric,
	 * add it to the context.
	 */
	करो अणु
		all = true;
		hashmap__क्रम_each_entry((&m->pctx.ids), cur, bkt) अणु
			काष्ठा expr_id *parent;
			काष्ठा pmu_event *pe;

			pe = metricgroup__find_metric(cur->key, map);
			अगर (!pe)
				जारी;

			ret = recursion_check(m, cur->key, &parent, ids);
			अगर (ret)
				वापस ret;

			all = false;
			/* The metric key itself needs to go out.. */
			expr__del_id(&m->pctx, cur->key);

			/* ... and it माला_लो resolved to the parent context. */
			ret = add_metric(metric_list, pe, metric_no_group, &m, parent, ids);
			अगर (ret)
				वापस ret;

			/*
			 * We added new metric to hashmap, so we need
			 * to अवरोध the iteration and start over.
			 */
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!all);

	वापस 0;
पूर्ण

अटल पूर्णांक resolve_metric(bool metric_no_group,
			  काष्ठा list_head *metric_list,
			  काष्ठा pmu_events_map *map,
			  काष्ठा expr_ids *ids)
अणु
	काष्ठा metric *m;
	पूर्णांक err;

	list_क्रम_each_entry(m, metric_list, nd) अणु
		err = __resolve_metric(m, metric_no_group, metric_list, map, ids);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक add_metric(काष्ठा list_head *metric_list,
		      काष्ठा pmu_event *pe,
		      bool metric_no_group,
		      काष्ठा metric **m,
		      काष्ठा expr_id *parent,
		      काष्ठा expr_ids *ids)
अणु
	काष्ठा metric *orig = *m;
	पूर्णांक ret = 0;

	pr_debug("metric expr %s for %s\n", pe->metric_expr, pe->metric_name);

	अगर (!म_माला(pe->metric_expr, "?")) अणु
		ret = __add_metric(metric_list, pe, metric_no_group, 1, m, parent, ids);
	पूर्ण अन्यथा अणु
		पूर्णांक j, count;

		count = arch_get_runसमयparam(pe);

		/* This loop is added to create multiple
		 * events depend on count value and add
		 * those events to metric_list.
		 */

		क्रम (j = 0; j < count && !ret; j++, *m = orig)
			ret = __add_metric(metric_list, pe, metric_no_group, j, m, parent, ids);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक metricgroup__add_metric_sys_event_iter(काष्ठा pmu_event *pe,
						  व्योम *data)
अणु
	काष्ठा metricgroup_add_iter_data *d = data;
	काष्ठा metric *m = शून्य;
	पूर्णांक ret;

	अगर (!match_pe_metric(pe, d->metric))
		वापस 0;

	ret = add_metric(d->metric_list, pe, d->metric_no_group, &m, शून्य, d->ids);
	अगर (ret)
		जाओ out;

	ret = resolve_metric(d->metric_no_group,
				     d->metric_list, शून्य, d->ids);
	अगर (ret)
		जाओ out;

	*(d->has_match) = true;

out:
	*(d->ret) = ret;
	वापस ret;
पूर्ण

अटल पूर्णांक metricgroup__add_metric(स्थिर अक्षर *metric, bool metric_no_group,
				   काष्ठा strbuf *events,
				   काष्ठा list_head *metric_list,
				   काष्ठा pmu_events_map *map)
अणु
	काष्ठा expr_ids ids = अणु .cnt = 0, पूर्ण;
	काष्ठा pmu_event *pe;
	काष्ठा metric *m;
	LIST_HEAD(list);
	पूर्णांक i, ret;
	bool has_match = false;

	map_क्रम_each_metric(pe, i, map, metric) अणु
		has_match = true;
		m = शून्य;

		ret = add_metric(&list, pe, metric_no_group, &m, शून्य, &ids);
		अगर (ret)
			जाओ out;

		/*
		 * Process any possible referenced metrics
		 * included in the expression.
		 */
		ret = resolve_metric(metric_no_group,
				     &list, map, &ids);
		अगर (ret)
			जाओ out;
	पूर्ण

	अणु
		काष्ठा metricgroup_iter_data data = अणु
			.fn = metricgroup__add_metric_sys_event_iter,
			.data = (व्योम *) &(काष्ठा metricgroup_add_iter_data) अणु
				.metric_list = &list,
				.metric = metric,
				.metric_no_group = metric_no_group,
				.ids = &ids,
				.has_match = &has_match,
				.ret = &ret,
			पूर्ण,
		पूर्ण;

		pmu_क्रम_each_sys_event(metricgroup__sys_event_iter, &data);
	पूर्ण
	/* End of pmu events. */
	अगर (!has_match) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(m, &list, nd) अणु
		अगर (events->len > 0)
			strbuf_addf(events, ",");

		अगर (m->has_स्थिरraपूर्णांक) अणु
			metricgroup__add_metric_non_group(events,
							  &m->pctx);
		पूर्ण अन्यथा अणु
			metricgroup__add_metric_weak_group(events,
							   &m->pctx);
		पूर्ण
	पूर्ण

out:
	/*
	 * add to metric_list so that they can be released
	 * even अगर it's failed
	 */
	list_splice(&list, metric_list);
	expr_ids__निकास(&ids);
	वापस ret;
पूर्ण

अटल पूर्णांक metricgroup__add_metric_list(स्थिर अक्षर *list, bool metric_no_group,
					काष्ठा strbuf *events,
					काष्ठा list_head *metric_list,
					काष्ठा pmu_events_map *map)
अणु
	अक्षर *llist, *nlist, *p;
	पूर्णांक ret = -EINVAL;

	nlist = strdup(list);
	अगर (!nlist)
		वापस -ENOMEM;
	llist = nlist;

	strbuf_init(events, 100);
	strbuf_addf(events, "%s", "");

	जबतक ((p = strsep(&llist, ",")) != शून्य) अणु
		ret = metricgroup__add_metric(p, metric_no_group, events,
					      metric_list, map);
		अगर (ret == -EINVAL) अणु
			ख_लिखो(मानक_त्रुटि, "Cannot find metric or group `%s'\n",
					p);
			अवरोध;
		पूर्ण
	पूर्ण
	मुक्त(nlist);

	अगर (!ret)
		metricgroup___watchकरोg_स्थिरraपूर्णांक_hपूर्णांक(शून्य, true);

	वापस ret;
पूर्ण

अटल व्योम metric__मुक्त_refs(काष्ठा metric *metric)
अणु
	काष्ठा metric_ref_node *ref, *पंचांगp;

	list_क्रम_each_entry_safe(ref, पंचांगp, &metric->metric_refs, list) अणु
		list_del(&ref->list);
		मुक्त(ref);
	पूर्ण
पूर्ण

अटल व्योम metricgroup__मुक्त_metrics(काष्ठा list_head *metric_list)
अणु
	काष्ठा metric *m, *पंचांगp;

	list_क्रम_each_entry_safe (m, पंचांगp, metric_list, nd) अणु
		metric__मुक्त_refs(m);
		expr__ctx_clear(&m->pctx);
		list_del_init(&m->nd);
		मुक्त(m);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_groups(काष्ठा evlist *perf_evlist, स्थिर अक्षर *str,
			bool metric_no_group,
			bool metric_no_merge,
			काष्ठा perf_pmu *fake_pmu,
			काष्ठा rblist *metric_events,
			काष्ठा pmu_events_map *map)
अणु
	काष्ठा parse_events_error parse_error;
	काष्ठा strbuf extra_events;
	LIST_HEAD(metric_list);
	पूर्णांक ret;

	अगर (metric_events->nr_entries == 0)
		metricgroup__rblist_init(metric_events);
	ret = metricgroup__add_metric_list(str, metric_no_group,
					   &extra_events, &metric_list, map);
	अगर (ret)
		जाओ out;
	pr_debug("adding %s\n", extra_events.buf);
	bzero(&parse_error, माप(parse_error));
	ret = __parse_events(perf_evlist, extra_events.buf, &parse_error, fake_pmu);
	अगर (ret) अणु
		parse_events_prपूर्णांक_error(&parse_error, extra_events.buf);
		जाओ out;
	पूर्ण
	ret = metricgroup__setup_events(&metric_list, metric_no_merge,
					perf_evlist, metric_events);
out:
	metricgroup__मुक्त_metrics(&metric_list);
	strbuf_release(&extra_events);
	वापस ret;
पूर्ण

पूर्णांक metricgroup__parse_groups(स्थिर काष्ठा option *opt,
			      स्थिर अक्षर *str,
			      bool metric_no_group,
			      bool metric_no_merge,
			      काष्ठा rblist *metric_events)
अणु
	काष्ठा evlist *perf_evlist = *(काष्ठा evlist **)opt->value;
	काष्ठा pmu_events_map *map = pmu_events_map__find();

	वापस parse_groups(perf_evlist, str, metric_no_group,
			    metric_no_merge, शून्य, metric_events, map);
पूर्ण

पूर्णांक metricgroup__parse_groups_test(काष्ठा evlist *evlist,
				   काष्ठा pmu_events_map *map,
				   स्थिर अक्षर *str,
				   bool metric_no_group,
				   bool metric_no_merge,
				   काष्ठा rblist *metric_events)
अणु
	वापस parse_groups(evlist, str, metric_no_group,
			    metric_no_merge, &perf_pmu__fake, metric_events, map);
पूर्ण

bool metricgroup__has_metric(स्थिर अक्षर *metric)
अणु
	काष्ठा pmu_events_map *map = pmu_events_map__find();
	काष्ठा pmu_event *pe;
	पूर्णांक i;

	अगर (!map)
		वापस false;

	क्रम (i = 0; ; i++) अणु
		pe = &map->table[i];

		अगर (!pe->name && !pe->metric_group && !pe->metric_name)
			अवरोध;
		अगर (!pe->metric_expr)
			जारी;
		अगर (match_metric(pe->metric_name, metric))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक metricgroup__copy_metric_events(काष्ठा evlist *evlist, काष्ठा cgroup *cgrp,
				    काष्ठा rblist *new_metric_events,
				    काष्ठा rblist *old_metric_events)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < rblist__nr_entries(old_metric_events); i++) अणु
		काष्ठा rb_node *nd;
		काष्ठा metric_event *old_me, *new_me;
		काष्ठा metric_expr *old_expr, *new_expr;
		काष्ठा evsel *evsel;
		माप_प्रकार alloc_size;
		पूर्णांक idx, nr;

		nd = rblist__entry(old_metric_events, i);
		old_me = container_of(nd, काष्ठा metric_event, nd);

		evsel = evlist__find_evsel(evlist, old_me->evsel->idx);
		अगर (!evsel)
			वापस -EINVAL;
		new_me = metricgroup__lookup(new_metric_events, evsel, true);
		अगर (!new_me)
			वापस -ENOMEM;

		pr_debug("copying metric event for cgroup '%s': %s (idx=%d)\n",
			 cgrp ? cgrp->name : "root", evsel->name, evsel->idx);

		list_क्रम_each_entry(old_expr, &old_me->head, nd) अणु
			new_expr = दो_स्मृति(माप(*new_expr));
			अगर (!new_expr)
				वापस -ENOMEM;

			new_expr->metric_expr = old_expr->metric_expr;
			new_expr->metric_name = old_expr->metric_name;
			new_expr->metric_unit = old_expr->metric_unit;
			new_expr->runसमय = old_expr->runसमय;

			अगर (old_expr->metric_refs) अणु
				/* calculate number of metric_events */
				क्रम (nr = 0; old_expr->metric_refs[nr].metric_name; nr++)
					जारी;
				alloc_size = माप(*new_expr->metric_refs);
				new_expr->metric_refs = सुस्मृति(nr + 1, alloc_size);
				अगर (!new_expr->metric_refs) अणु
					मुक्त(new_expr);
					वापस -ENOMEM;
				पूर्ण

				स_नकल(new_expr->metric_refs, old_expr->metric_refs,
				       nr * alloc_size);
			पूर्ण अन्यथा अणु
				new_expr->metric_refs = शून्य;
			पूर्ण

			/* calculate number of metric_events */
			क्रम (nr = 0; old_expr->metric_events[nr]; nr++)
				जारी;
			alloc_size = माप(*new_expr->metric_events);
			new_expr->metric_events = सुस्मृति(nr + 1, alloc_size);
			अगर (!new_expr->metric_events) अणु
				मुक्त(new_expr->metric_refs);
				मुक्त(new_expr);
				वापस -ENOMEM;
			पूर्ण

			/* copy evsel in the same position */
			क्रम (idx = 0; idx < nr; idx++) अणु
				evsel = old_expr->metric_events[idx];
				evsel = evlist__find_evsel(evlist, evsel->idx);
				अगर (evsel == शून्य) अणु
					मुक्त(new_expr->metric_events);
					मुक्त(new_expr->metric_refs);
					मुक्त(new_expr);
					वापस -EINVAL;
				पूर्ण
				new_expr->metric_events[idx] = evsel;
			पूर्ण

			list_add(&new_expr->nd, &new_me->head);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
