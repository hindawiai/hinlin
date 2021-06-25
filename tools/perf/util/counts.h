<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_COUNTS_H
#घोषणा __PERF_COUNTS_H

#समावेश <linux/types.h>
#समावेश <पूर्णांकernal/xyarray.h>
#समावेश <perf/evsel.h>
#समावेश <stdbool.h>

काष्ठा evsel;

काष्ठा perf_counts अणु
	s8			  scaled;
	काष्ठा perf_counts_values aggr;
	काष्ठा xyarray		  *values;
	काष्ठा xyarray		  *loaded;
पूर्ण;


अटल अंतरभूत काष्ठा perf_counts_values*
perf_counts(काष्ठा perf_counts *counts, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	वापस xyarray__entry(counts->values, cpu, thपढ़ो);
पूर्ण

अटल अंतरभूत bool
perf_counts__is_loaded(काष्ठा perf_counts *counts, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	वापस *((bool *) xyarray__entry(counts->loaded, cpu, thपढ़ो));
पूर्ण

अटल अंतरभूत व्योम
perf_counts__set_loaded(काष्ठा perf_counts *counts, पूर्णांक cpu, पूर्णांक thपढ़ो, bool loaded)
अणु
	*((bool *) xyarray__entry(counts->loaded, cpu, thपढ़ो)) = loaded;
पूर्ण

काष्ठा perf_counts *perf_counts__new(पूर्णांक ncpus, पूर्णांक nthपढ़ोs);
व्योम perf_counts__delete(काष्ठा perf_counts *counts);
व्योम perf_counts__reset(काष्ठा perf_counts *counts);

व्योम evsel__reset_counts(काष्ठा evsel *evsel);
पूर्णांक evsel__alloc_counts(काष्ठा evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs);
व्योम evsel__मुक्त_counts(काष्ठा evsel *evsel);

#पूर्ण_अगर /* __PERF_COUNTS_H */
