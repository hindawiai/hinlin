<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Compare and figure out the top N hottest streams
 * Copyright (c) 2020, Intel Corporation.
 * Author: Jin Yao
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <linux/zभाग.स>
#समावेश "debug.h"
#समावेश "hist.h"
#समावेश "sort.h"
#समावेश "stream.h"
#समावेश "evlist.h"

अटल व्योम evsel_streams__delete(काष्ठा evsel_streams *es, पूर्णांक nr_evsel)
अणु
	क्रम (पूर्णांक i = 0; i < nr_evsel; i++)
		zमुक्त(&es[i].streams);

	मुक्त(es);
पूर्ण

व्योम evlist_streams__delete(काष्ठा evlist_streams *els)
अणु
	evsel_streams__delete(els->ev_streams, els->nr_evsel);
	मुक्त(els);
पूर्ण

अटल काष्ठा evlist_streams *evlist_streams__new(पूर्णांक nr_evsel,
						  पूर्णांक nr_streams_max)
अणु
	काष्ठा evlist_streams *els;
	काष्ठा evsel_streams *es;

	els = zalloc(माप(*els));
	अगर (!els)
		वापस शून्य;

	es = सुस्मृति(nr_evsel, माप(काष्ठा evsel_streams));
	अगर (!es) अणु
		मुक्त(els);
		वापस शून्य;
	पूर्ण

	क्रम (पूर्णांक i = 0; i < nr_evsel; i++) अणु
		काष्ठा evsel_streams *s = &es[i];

		s->streams = सुस्मृति(nr_streams_max, माप(काष्ठा stream));
		अगर (!s->streams)
			जाओ err;

		s->nr_streams_max = nr_streams_max;
		s->evsel_idx = -1;
	पूर्ण

	els->ev_streams = es;
	els->nr_evsel = nr_evsel;
	वापस els;

err:
	evsel_streams__delete(es, nr_evsel);
	वापस शून्य;
पूर्ण

/*
 * The cnodes with high hit number are hot callchains.
 */
अटल व्योम evsel_streams__set_hot_cnode(काष्ठा evsel_streams *es,
					 काष्ठा callchain_node *cnode)
अणु
	पूर्णांक i, idx = 0;
	u64 hit;

	अगर (es->nr_streams < es->nr_streams_max) अणु
		i = es->nr_streams;
		es->streams[i].cnode = cnode;
		es->nr_streams++;
		वापस;
	पूर्ण

	/*
	 * Considering a few number of hot streams, only use simple
	 * way to find the cnode with smallest hit number and replace.
	 */
	hit = (es->streams[0].cnode)->hit;
	क्रम (i = 1; i < es->nr_streams; i++) अणु
		अगर ((es->streams[i].cnode)->hit < hit) अणु
			hit = (es->streams[i].cnode)->hit;
			idx = i;
		पूर्ण
	पूर्ण

	अगर (cnode->hit > hit)
		es->streams[idx].cnode = cnode;
पूर्ण

अटल व्योम update_hot_callchain(काष्ठा hist_entry *he,
				 काष्ठा evsel_streams *es)
अणु
	काष्ठा rb_root *root = &he->sorted_chain;
	काष्ठा rb_node *rb_node = rb_first(root);
	काष्ठा callchain_node *cnode;

	जबतक (rb_node) अणु
		cnode = rb_entry(rb_node, काष्ठा callchain_node, rb_node);
		evsel_streams__set_hot_cnode(es, cnode);
		rb_node = rb_next(rb_node);
	पूर्ण
पूर्ण

अटल व्योम init_hot_callchain(काष्ठा hists *hists, काष्ठा evsel_streams *es)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);

	जबतक (next) अणु
		काष्ठा hist_entry *he;

		he = rb_entry(next, काष्ठा hist_entry, rb_node);
		update_hot_callchain(he, es);
		next = rb_next(&he->rb_node);
	पूर्ण

	es->streams_hits = callchain_total_hits(hists);
पूर्ण

अटल पूर्णांक evlist__init_callchain_streams(काष्ठा evlist *evlist,
					  काष्ठा evlist_streams *els)
अणु
	काष्ठा evsel_streams *es = els->ev_streams;
	काष्ठा evsel *pos;
	पूर्णांक i = 0;

	BUG_ON(els->nr_evsel < evlist->core.nr_entries);

	evlist__क्रम_each_entry(evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);

		hists__output_resort(hists, शून्य);
		init_hot_callchain(hists, &es[i]);
		es[i].evsel_idx = pos->idx;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा evlist_streams *evlist__create_streams(काष्ठा evlist *evlist,
					      पूर्णांक nr_streams_max)
अणु
	पूर्णांक nr_evsel = evlist->core.nr_entries, ret = -1;
	काष्ठा evlist_streams *els = evlist_streams__new(nr_evsel,
							 nr_streams_max);

	अगर (!els)
		वापस शून्य;

	ret = evlist__init_callchain_streams(evlist, els);
	अगर (ret) अणु
		evlist_streams__delete(els);
		वापस शून्य;
	पूर्ण

	वापस els;
पूर्ण

काष्ठा evsel_streams *evsel_streams__entry(काष्ठा evlist_streams *els,
					   पूर्णांक evsel_idx)
अणु
	काष्ठा evsel_streams *es = els->ev_streams;

	क्रम (पूर्णांक i = 0; i < els->nr_evsel; i++) अणु
		अगर (es[i].evsel_idx == evsel_idx)
			वापस &es[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा stream *stream__callchain_match(काष्ठा stream *base_stream,
					      काष्ठा evsel_streams *es_pair)
अणु
	क्रम (पूर्णांक i = 0; i < es_pair->nr_streams; i++) अणु
		काष्ठा stream *pair_stream = &es_pair->streams[i];

		अगर (callchain_cnode_matched(base_stream->cnode,
					    pair_stream->cnode)) अणु
			वापस pair_stream;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा stream *stream__match(काष्ठा stream *base_stream,
				    काष्ठा evsel_streams *es_pair)
अणु
	वापस stream__callchain_match(base_stream, es_pair);
पूर्ण

अटल व्योम stream__link(काष्ठा stream *base_stream, काष्ठा stream *pair_stream)
अणु
	base_stream->pair_cnode = pair_stream->cnode;
	pair_stream->pair_cnode = base_stream->cnode;
पूर्ण

व्योम evsel_streams__match(काष्ठा evsel_streams *es_base,
			  काष्ठा evsel_streams *es_pair)
अणु
	क्रम (पूर्णांक i = 0; i < es_base->nr_streams; i++) अणु
		काष्ठा stream *base_stream = &es_base->streams[i];
		काष्ठा stream *pair_stream;

		pair_stream = stream__match(base_stream, es_pair);
		अगर (pair_stream)
			stream__link(base_stream, pair_stream);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_callchain_pair(काष्ठा stream *base_stream, पूर्णांक idx,
				 काष्ठा evsel_streams *es_base,
				 काष्ठा evsel_streams *es_pair)
अणु
	काष्ठा callchain_node *base_cnode = base_stream->cnode;
	काष्ठा callchain_node *pair_cnode = base_stream->pair_cnode;
	काष्ठा callchain_list *base_chain, *pair_chain;
	अक्षर buf1[512], buf2[512], cbuf1[256], cbuf2[256];
	अक्षर *s1, *s2;
	द्विगुन pct;

	म_लिखो("\nhot chain pair %d:\n", idx);

	pct = (द्विगुन)base_cnode->hit / (द्विगुन)es_base->streams_hits;
	scnम_लिखो(buf1, माप(buf1), "cycles: %ld, hits: %.2f%%",
		  callchain_avg_cycles(base_cnode), pct * 100.0);

	pct = (द्विगुन)pair_cnode->hit / (द्विगुन)es_pair->streams_hits;
	scnम_लिखो(buf2, माप(buf2), "cycles: %ld, hits: %.2f%%",
		  callchain_avg_cycles(pair_cnode), pct * 100.0);

	म_लिखो("%35s\t%35s\n", buf1, buf2);

	म_लिखो("%35s\t%35s\n",
	       "---------------------------",
	       "--------------------------");

	pair_chain = list_first_entry(&pair_cnode->val,
				      काष्ठा callchain_list,
				      list);

	list_क्रम_each_entry(base_chain, &base_cnode->val, list) अणु
		अगर (&pair_chain->list == &pair_cnode->val)
			वापस;

		s1 = callchain_list__sym_name(base_chain, cbuf1, माप(cbuf1),
					      false);
		s2 = callchain_list__sym_name(pair_chain, cbuf2, माप(cbuf2),
					      false);

		scnम_लिखो(buf1, माप(buf1), "%35s\t%35s", s1, s2);
		म_लिखो("%s\n", buf1);
		pair_chain = list_next_entry(pair_chain, list);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_stream_callchain(काष्ठा stream *stream, पूर्णांक idx,
				   काष्ठा evsel_streams *es, bool pair)
अणु
	काष्ठा callchain_node *cnode = stream->cnode;
	काष्ठा callchain_list *chain;
	अक्षर buf[512], cbuf[256], *s;
	द्विगुन pct;

	म_लिखो("\nhot chain %d:\n", idx);

	pct = (द्विगुन)cnode->hit / (द्विगुन)es->streams_hits;
	scnम_लिखो(buf, माप(buf), "cycles: %ld, hits: %.2f%%",
		  callchain_avg_cycles(cnode), pct * 100.0);

	अगर (pair) अणु
		म_लिखो("%35s\t%35s\n", "", buf);
		म_लिखो("%35s\t%35s\n",
		       "", "--------------------------");
	पूर्ण अन्यथा अणु
		म_लिखो("%35s\n", buf);
		म_लिखो("%35s\n", "--------------------------");
	पूर्ण

	list_क्रम_each_entry(chain, &cnode->val, list) अणु
		s = callchain_list__sym_name(chain, cbuf, माप(cbuf), false);

		अगर (pair)
			scnम_लिखो(buf, माप(buf), "%35s\t%35s", "", s);
		अन्यथा
			scnम_लिखो(buf, माप(buf), "%35s", s);

		म_लिखो("%s\n", buf);
	पूर्ण
पूर्ण

अटल व्योम callchain_streams_report(काष्ठा evsel_streams *es_base,
				     काष्ठा evsel_streams *es_pair)
अणु
	काष्ठा stream *base_stream;
	पूर्णांक i, idx = 0;

	म_लिखो("[ Matched hot streams ]\n");
	क्रम (i = 0; i < es_base->nr_streams; i++) अणु
		base_stream = &es_base->streams[i];
		अगर (base_stream->pair_cnode) अणु
			prपूर्णांक_callchain_pair(base_stream, ++idx,
					     es_base, es_pair);
		पूर्ण
	पूर्ण

	idx = 0;
	म_लिखो("\n[ Hot streams in old perf data only ]\n");
	क्रम (i = 0; i < es_base->nr_streams; i++) अणु
		base_stream = &es_base->streams[i];
		अगर (!base_stream->pair_cnode) अणु
			prपूर्णांक_stream_callchain(base_stream, ++idx,
					       es_base, false);
		पूर्ण
	पूर्ण

	idx = 0;
	म_लिखो("\n[ Hot streams in new perf data only ]\n");
	क्रम (i = 0; i < es_pair->nr_streams; i++) अणु
		base_stream = &es_pair->streams[i];
		अगर (!base_stream->pair_cnode) अणु
			prपूर्णांक_stream_callchain(base_stream, ++idx,
					       es_pair, true);
		पूर्ण
	पूर्ण
पूर्ण

व्योम evsel_streams__report(काष्ठा evsel_streams *es_base,
			   काष्ठा evsel_streams *es_pair)
अणु
	वापस callchain_streams_report(es_base, es_pair);
पूर्ण
