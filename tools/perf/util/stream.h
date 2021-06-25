<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_STREAM_H
#घोषणा __PERF_STREAM_H

#समावेश "callchain.h"

काष्ठा stream अणु
	काष्ठा callchain_node	*cnode;
	काष्ठा callchain_node	*pair_cnode;
पूर्ण;

काष्ठा evsel_streams अणु
	काष्ठा stream		*streams;
	पूर्णांक			nr_streams_max;
	पूर्णांक			nr_streams;
	पूर्णांक			evsel_idx;
	u64			streams_hits;
पूर्ण;

काष्ठा evlist_streams अणु
	काष्ठा evsel_streams	*ev_streams;
	पूर्णांक			nr_evsel;
पूर्ण;

काष्ठा evlist;

व्योम evlist_streams__delete(काष्ठा evlist_streams *els);

काष्ठा evlist_streams *evlist__create_streams(काष्ठा evlist *evlist,
					      पूर्णांक nr_streams_max);

काष्ठा evsel_streams *evsel_streams__entry(काष्ठा evlist_streams *els,
					   पूर्णांक evsel_idx);

व्योम evsel_streams__match(काष्ठा evsel_streams *es_base,
			  काष्ठा evsel_streams *es_pair);

व्योम evsel_streams__report(काष्ठा evsel_streams *es_base,
			   काष्ठा evsel_streams *es_pair);

#पूर्ण_अगर /* __PERF_STREAM_H */
