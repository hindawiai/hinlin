<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "evsel.h"
#समावेश "counts.h"
#समावेश <linux/zभाग.स>

काष्ठा perf_counts *perf_counts__new(पूर्णांक ncpus, पूर्णांक nthपढ़ोs)
अणु
	काष्ठा perf_counts *counts = zalloc(माप(*counts));

	अगर (counts) अणु
		काष्ठा xyarray *values;

		values = xyarray__new(ncpus, nthपढ़ोs, माप(काष्ठा perf_counts_values));
		अगर (!values) अणु
			मुक्त(counts);
			वापस शून्य;
		पूर्ण

		counts->values = values;

		values = xyarray__new(ncpus, nthपढ़ोs, माप(bool));
		अगर (!values) अणु
			xyarray__delete(counts->values);
			मुक्त(counts);
			वापस शून्य;
		पूर्ण

		counts->loaded = values;
	पूर्ण

	वापस counts;
पूर्ण

व्योम perf_counts__delete(काष्ठा perf_counts *counts)
अणु
	अगर (counts) अणु
		xyarray__delete(counts->loaded);
		xyarray__delete(counts->values);
		मुक्त(counts);
	पूर्ण
पूर्ण

व्योम perf_counts__reset(काष्ठा perf_counts *counts)
अणु
	xyarray__reset(counts->loaded);
	xyarray__reset(counts->values);
	स_रखो(&counts->aggr, 0, माप(काष्ठा perf_counts_values));
पूर्ण

व्योम evsel__reset_counts(काष्ठा evsel *evsel)
अणु
	perf_counts__reset(evsel->counts);
पूर्ण

पूर्णांक evsel__alloc_counts(काष्ठा evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs)
अणु
	evsel->counts = perf_counts__new(ncpus, nthपढ़ोs);
	वापस evsel->counts != शून्य ? 0 : -ENOMEM;
पूर्ण

व्योम evsel__मुक्त_counts(काष्ठा evsel *evsel)
अणु
	perf_counts__delete(evsel->counts);
	evsel->counts = शून्य;
पूर्ण
