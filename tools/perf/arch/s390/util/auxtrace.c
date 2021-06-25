<शैली गुरु>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/zभाग.स>

#समावेश "../../util/evlist.h"
#समावेश "../../util/auxtrace.h"
#समावेश "../../util/evsel.h"
#समावेश "../../util/record.h"

#घोषणा PERF_EVENT_CPUM_SF		0xB0000 /* Event: Basic-sampling */
#घोषणा PERF_EVENT_CPUM_SF_DIAG		0xBD000 /* Event: Combined-sampling */
#घोषणा DEFAULT_AUX_PAGES		128
#घोषणा DEFAULT_FREQ			4000

अटल व्योम cpumsf_मुक्त(काष्ठा auxtrace_record *itr)
अणु
	मुक्त(itr);
पूर्ण

अटल माप_प्रकार cpumsf_info_priv_size(काष्ठा auxtrace_record *itr __maybe_unused,
				    काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
cpumsf_info_fill(काष्ठा auxtrace_record *itr __maybe_unused,
		 काष्ठा perf_session *session __maybe_unused,
		 काष्ठा perf_record_auxtrace_info *auxtrace_info __maybe_unused,
		 माप_प्रकार priv_size __maybe_unused)
अणु
	auxtrace_info->type = PERF_AUXTRACE_S390_CPUMSF;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ
cpumsf_reference(काष्ठा auxtrace_record *itr __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
cpumsf_recording_options(काष्ठा auxtrace_record *ar __maybe_unused,
			 काष्ठा evlist *evlist __maybe_unused,
			 काष्ठा record_opts *opts)
अणु
	अचिन्हित पूर्णांक factor = 1;
	अचिन्हित पूर्णांक pages;

	opts->full_auxtrace = true;

	/*
	 * The AUX buffer size should be set properly to aव्योम
	 * overflow of samples अगर it is not set explicitly.
	 * DEFAULT_AUX_PAGES is an proper size when sampling frequency
	 * is DEFAULT_FREQ. It is expected to hold about 1/2 second
	 * of sampling data. The size used क्रम AUX buffer will scale
	 * according to the specअगरied frequency and DEFAULT_FREQ.
	 */
	अगर (!opts->auxtrace_mmap_pages) अणु
		अगर (opts->user_freq != अच_पूर्णांक_उच्च)
			factor = (opts->user_freq + DEFAULT_FREQ
				  - 1) / DEFAULT_FREQ;
		pages = DEFAULT_AUX_PAGES * factor;
		opts->auxtrace_mmap_pages = roundup_घात_of_two(pages);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
cpumsf_parse_snapshot_options(काष्ठा auxtrace_record *itr __maybe_unused,
			      काष्ठा record_opts *opts __maybe_unused,
			      स्थिर अक्षर *str __maybe_unused)
अणु
	वापस 0;
पूर्ण

/*
 * auxtrace_record__init is called when perf record
 * check अगर the event really need auxtrace
 */
काष्ठा auxtrace_record *auxtrace_record__init(काष्ठा evlist *evlist,
					      पूर्णांक *err)
अणु
	काष्ठा auxtrace_record *aux;
	काष्ठा evsel *pos;
	पूर्णांक diagnose = 0;

	*err = 0;
	अगर (evlist->core.nr_entries == 0)
		वापस शून्य;

	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (pos->core.attr.config == PERF_EVENT_CPUM_SF_DIAG) अणु
			diagnose = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!diagnose)
		वापस शून्य;

	/* sampling in diagnose mode. alloc aux buffer */
	aux = zalloc(माप(*aux));
	अगर (aux == शून्य) अणु
		*err = -ENOMEM;
		वापस शून्य;
	पूर्ण

	aux->parse_snapshot_options = cpumsf_parse_snapshot_options;
	aux->recording_options = cpumsf_recording_options;
	aux->info_priv_size = cpumsf_info_priv_size;
	aux->info_fill = cpumsf_info_fill;
	aux->मुक्त = cpumsf_मुक्त;
	aux->reference = cpumsf_reference;

	वापस aux;
पूर्ण
