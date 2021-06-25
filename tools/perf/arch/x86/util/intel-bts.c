<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel-bts.c: Intel Processor Trace support
 * Copyright (c) 2013-2015, Intel Corporation.
 */

#समावेश <त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/zभाग.स>

#समावेश "../../../util/cpumap.h"
#समावेश "../../../util/event.h"
#समावेश "../../../util/evsel.h"
#समावेश "../../../util/evlist.h"
#समावेश "../../../util/mmap.h"
#समावेश "../../../util/session.h"
#समावेश "../../../util/pmu.h"
#समावेश "../../../util/debug.h"
#समावेश "../../../util/record.h"
#समावेश "../../../util/tsc.h"
#समावेश "../../../util/auxtrace.h"
#समावेश "../../../util/intel-bts.h"
#समावेश <पूर्णांकernal/lib.h> // page_size

#घोषणा KiB(x) ((x) * 1024)
#घोषणा MiB(x) ((x) * 1024 * 1024)
#घोषणा KiB_MASK(x) (KiB(x) - 1)
#घोषणा MiB_MASK(x) (MiB(x) - 1)

काष्ठा पूर्णांकel_bts_snapshot_ref अणु
	व्योम	*ref_buf;
	माप_प्रकार	ref_offset;
	bool	wrapped;
पूर्ण;

काष्ठा पूर्णांकel_bts_recording अणु
	काष्ठा auxtrace_record		itr;
	काष्ठा perf_pmu			*पूर्णांकel_bts_pmu;
	काष्ठा evlist		*evlist;
	bool				snapshot_mode;
	माप_प्रकार				snapshot_size;
	पूर्णांक				snapshot_ref_cnt;
	काष्ठा पूर्णांकel_bts_snapshot_ref	*snapshot_refs;
पूर्ण;

काष्ठा branch अणु
	u64 from;
	u64 to;
	u64 misc;
पूर्ण;

अटल माप_प्रकार
पूर्णांकel_bts_info_priv_size(काष्ठा auxtrace_record *itr __maybe_unused,
			 काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस INTEL_BTS_AUXTRACE_PRIV_SIZE;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_info_fill(काष्ठा auxtrace_record *itr,
			       काष्ठा perf_session *session,
			       काष्ठा perf_record_auxtrace_info *auxtrace_info,
			       माप_प्रकार priv_size)
अणु
	काष्ठा पूर्णांकel_bts_recording *btsr =
			container_of(itr, काष्ठा पूर्णांकel_bts_recording, itr);
	काष्ठा perf_pmu *पूर्णांकel_bts_pmu = btsr->पूर्णांकel_bts_pmu;
	काष्ठा perf_event_mmap_page *pc;
	काष्ठा perf_tsc_conversion tc = अणु .समय_mult = 0, पूर्ण;
	bool cap_user_समय_zero = false;
	पूर्णांक err;

	अगर (priv_size != INTEL_BTS_AUXTRACE_PRIV_SIZE)
		वापस -EINVAL;

	अगर (!session->evlist->core.nr_mmaps)
		वापस -EINVAL;

	pc = session->evlist->mmap[0].core.base;
	अगर (pc) अणु
		err = perf_पढ़ो_tsc_conversion(pc, &tc);
		अगर (err) अणु
			अगर (err != -EOPNOTSUPP)
				वापस err;
		पूर्ण अन्यथा अणु
			cap_user_समय_zero = tc.समय_mult != 0;
		पूर्ण
		अगर (!cap_user_समय_zero)
			ui__warning("Intel BTS: TSC not available\n");
	पूर्ण

	auxtrace_info->type = PERF_AUXTRACE_INTEL_BTS;
	auxtrace_info->priv[INTEL_BTS_PMU_TYPE] = पूर्णांकel_bts_pmu->type;
	auxtrace_info->priv[INTEL_BTS_TIME_SHIFT] = tc.समय_shअगरt;
	auxtrace_info->priv[INTEL_BTS_TIME_MULT] = tc.समय_mult;
	auxtrace_info->priv[INTEL_BTS_TIME_ZERO] = tc.समय_zero;
	auxtrace_info->priv[INTEL_BTS_CAP_USER_TIME_ZERO] = cap_user_समय_zero;
	auxtrace_info->priv[INTEL_BTS_SNAPSHOT_MODE] = btsr->snapshot_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_recording_options(काष्ठा auxtrace_record *itr,
				       काष्ठा evlist *evlist,
				       काष्ठा record_opts *opts)
अणु
	काष्ठा पूर्णांकel_bts_recording *btsr =
			container_of(itr, काष्ठा पूर्णांकel_bts_recording, itr);
	काष्ठा perf_pmu *पूर्णांकel_bts_pmu = btsr->पूर्णांकel_bts_pmu;
	काष्ठा evsel *evsel, *पूर्णांकel_bts_evsel = शून्य;
	स्थिर काष्ठा perf_cpu_map *cpus = evlist->core.cpus;
	bool privileged = perf_event_paranoid_check(-1);

	अगर (opts->auxtrace_sample_mode) अणु
		pr_err("Intel BTS does not support AUX area sampling\n");
		वापस -EINVAL;
	पूर्ण

	btsr->evlist = evlist;
	btsr->snapshot_mode = opts->auxtrace_snapshot_mode;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == पूर्णांकel_bts_pmu->type) अणु
			अगर (पूर्णांकel_bts_evsel) अणु
				pr_err("There may be only one " INTEL_BTS_PMU_NAME " event\n");
				वापस -EINVAL;
			पूर्ण
			evsel->core.attr.freq = 0;
			evsel->core.attr.sample_period = 1;
			पूर्णांकel_bts_evsel = evsel;
			opts->full_auxtrace = true;
		पूर्ण
	पूर्ण

	अगर (opts->auxtrace_snapshot_mode && !opts->full_auxtrace) अणु
		pr_err("Snapshot mode (-S option) requires " INTEL_BTS_PMU_NAME " PMU event (-e " INTEL_BTS_PMU_NAME ")\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!opts->full_auxtrace)
		वापस 0;

	अगर (opts->full_auxtrace && !perf_cpu_map__empty(cpus)) अणु
		pr_err(INTEL_BTS_PMU_NAME " does not support per-cpu recording\n");
		वापस -EINVAL;
	पूर्ण

	/* Set शेष sizes क्रम snapshot mode */
	अगर (opts->auxtrace_snapshot_mode) अणु
		अगर (!opts->auxtrace_snapshot_size && !opts->auxtrace_mmap_pages) अणु
			अगर (privileged) अणु
				opts->auxtrace_mmap_pages = MiB(4) / page_size;
			पूर्ण अन्यथा अणु
				opts->auxtrace_mmap_pages = KiB(128) / page_size;
				अगर (opts->mmap_pages == अच_पूर्णांक_उच्च)
					opts->mmap_pages = KiB(256) / page_size;
			पूर्ण
		पूर्ण अन्यथा अगर (!opts->auxtrace_mmap_pages && !privileged &&
			   opts->mmap_pages == अच_पूर्णांक_उच्च) अणु
			opts->mmap_pages = KiB(256) / page_size;
		पूर्ण
		अगर (!opts->auxtrace_snapshot_size)
			opts->auxtrace_snapshot_size =
				opts->auxtrace_mmap_pages * (माप_प्रकार)page_size;
		अगर (!opts->auxtrace_mmap_pages) अणु
			माप_प्रकार sz = opts->auxtrace_snapshot_size;

			sz = round_up(sz, page_size) / page_size;
			opts->auxtrace_mmap_pages = roundup_घात_of_two(sz);
		पूर्ण
		अगर (opts->auxtrace_snapshot_size >
				opts->auxtrace_mmap_pages * (माप_प्रकार)page_size) अणु
			pr_err("Snapshot size %zu must not be greater than AUX area tracing mmap size %zu\n",
			       opts->auxtrace_snapshot_size,
			       opts->auxtrace_mmap_pages * (माप_प्रकार)page_size);
			वापस -EINVAL;
		पूर्ण
		अगर (!opts->auxtrace_snapshot_size || !opts->auxtrace_mmap_pages) अणु
			pr_err("Failed to calculate default snapshot size and/or AUX area tracing mmap pages\n");
			वापस -EINVAL;
		पूर्ण
		pr_debug2("Intel BTS snapshot size: %zu\n",
			  opts->auxtrace_snapshot_size);
	पूर्ण

	/* Set शेष sizes क्रम full trace mode */
	अगर (opts->full_auxtrace && !opts->auxtrace_mmap_pages) अणु
		अगर (privileged) अणु
			opts->auxtrace_mmap_pages = MiB(4) / page_size;
		पूर्ण अन्यथा अणु
			opts->auxtrace_mmap_pages = KiB(128) / page_size;
			अगर (opts->mmap_pages == अच_पूर्णांक_उच्च)
				opts->mmap_pages = KiB(256) / page_size;
		पूर्ण
	पूर्ण

	/* Validate auxtrace_mmap_pages */
	अगर (opts->auxtrace_mmap_pages) अणु
		माप_प्रकार sz = opts->auxtrace_mmap_pages * (माप_प्रकार)page_size;
		माप_प्रकार min_sz;

		अगर (opts->auxtrace_snapshot_mode)
			min_sz = KiB(4);
		अन्यथा
			min_sz = KiB(8);

		अगर (sz < min_sz || !is_घातer_of_2(sz)) अणु
			pr_err("Invalid mmap size for Intel BTS: must be at least %zuKiB and a power of 2\n",
			       min_sz / 1024);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकel_bts_evsel) अणु
		/*
		 * To obtain the auxtrace buffer file descriptor, the auxtrace event
		 * must come first.
		 */
		evlist__to_front(evlist, पूर्णांकel_bts_evsel);
		/*
		 * In the हाल of per-cpu mmaps, we need the CPU on the
		 * AUX event.
		 */
		अगर (!perf_cpu_map__empty(cpus))
			evsel__set_sample_bit(पूर्णांकel_bts_evsel, CPU);
	पूर्ण

	/* Add dummy event to keep tracking */
	अगर (opts->full_auxtrace) अणु
		काष्ठा evsel *tracking_evsel;
		पूर्णांक err;

		err = parse_events(evlist, "dummy:u", शून्य);
		अगर (err)
			वापस err;

		tracking_evsel = evlist__last(evlist);

		evlist__set_tracking_event(evlist, tracking_evsel);

		tracking_evsel->core.attr.freq = 0;
		tracking_evsel->core.attr.sample_period = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_parse_snapshot_options(काष्ठा auxtrace_record *itr,
					    काष्ठा record_opts *opts,
					    स्थिर अक्षर *str)
अणु
	काष्ठा पूर्णांकel_bts_recording *btsr =
			container_of(itr, काष्ठा पूर्णांकel_bts_recording, itr);
	अचिन्हित दीर्घ दीर्घ snapshot_size = 0;
	अक्षर *endptr;

	अगर (str) अणु
		snapshot_size = म_से_अदीर्घl(str, &endptr, 0);
		अगर (*endptr || snapshot_size > SIZE_MAX)
			वापस -1;
	पूर्ण

	opts->auxtrace_snapshot_mode = true;
	opts->auxtrace_snapshot_size = snapshot_size;

	btsr->snapshot_size = snapshot_size;

	वापस 0;
पूर्ण

अटल u64 पूर्णांकel_bts_reference(काष्ठा auxtrace_record *itr __maybe_unused)
अणु
	वापस rdtsc();
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_alloc_snapshot_refs(काष्ठा पूर्णांकel_bts_recording *btsr,
					 पूर्णांक idx)
अणु
	स्थिर माप_प्रकार sz = माप(काष्ठा पूर्णांकel_bts_snapshot_ref);
	पूर्णांक cnt = btsr->snapshot_ref_cnt, new_cnt = cnt * 2;
	काष्ठा पूर्णांकel_bts_snapshot_ref *refs;

	अगर (!new_cnt)
		new_cnt = 16;

	जबतक (new_cnt <= idx)
		new_cnt *= 2;

	refs = सुस्मृति(new_cnt, sz);
	अगर (!refs)
		वापस -ENOMEM;

	स_नकल(refs, btsr->snapshot_refs, cnt * sz);

	btsr->snapshot_refs = refs;
	btsr->snapshot_ref_cnt = new_cnt;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_bts_मुक्त_snapshot_refs(काष्ठा पूर्णांकel_bts_recording *btsr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < btsr->snapshot_ref_cnt; i++)
		zमुक्त(&btsr->snapshot_refs[i].ref_buf);
	zमुक्त(&btsr->snapshot_refs);
पूर्ण

अटल व्योम पूर्णांकel_bts_recording_मुक्त(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा पूर्णांकel_bts_recording *btsr =
			container_of(itr, काष्ठा पूर्णांकel_bts_recording, itr);

	पूर्णांकel_bts_मुक्त_snapshot_refs(btsr);
	मुक्त(btsr);
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_snapshot_start(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा पूर्णांकel_bts_recording *btsr =
			container_of(itr, काष्ठा पूर्णांकel_bts_recording, itr);
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(btsr->evlist, evsel) अणु
		अगर (evsel->core.attr.type == btsr->पूर्णांकel_bts_pmu->type)
			वापस evsel__disable(evsel);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_snapshot_finish(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा पूर्णांकel_bts_recording *btsr =
			container_of(itr, काष्ठा पूर्णांकel_bts_recording, itr);
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(btsr->evlist, evsel) अणु
		अगर (evsel->core.attr.type == btsr->पूर्णांकel_bts_pmu->type)
			वापस evsel__enable(evsel);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल bool पूर्णांकel_bts_first_wrap(u64 *data, माप_प्रकार buf_size)
अणु
	पूर्णांक i, a, b;

	b = buf_size >> 3;
	a = b - 512;
	अगर (a < 0)
		a = 0;

	क्रम (i = a; i < b; i++) अणु
		अगर (data[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_find_snapshot(काष्ठा auxtrace_record *itr, पूर्णांक idx,
				   काष्ठा auxtrace_mmap *mm, अचिन्हित अक्षर *data,
				   u64 *head, u64 *old)
अणु
	काष्ठा पूर्णांकel_bts_recording *btsr =
			container_of(itr, काष्ठा पूर्णांकel_bts_recording, itr);
	bool wrapped;
	पूर्णांक err;

	pr_debug3("%s: mmap index %d old head %zu new head %zu\n",
		  __func__, idx, (माप_प्रकार)*old, (माप_प्रकार)*head);

	अगर (idx >= btsr->snapshot_ref_cnt) अणु
		err = पूर्णांकel_bts_alloc_snapshot_refs(btsr, idx);
		अगर (err)
			जाओ out_err;
	पूर्ण

	wrapped = btsr->snapshot_refs[idx].wrapped;
	अगर (!wrapped && पूर्णांकel_bts_first_wrap((u64 *)data, mm->len)) अणु
		btsr->snapshot_refs[idx].wrapped = true;
		wrapped = true;
	पूर्ण

	/*
	 * In full trace mode 'head' continually increases.  However in snapshot
	 * mode 'head' is an offset within the buffer.  Here 'old' and 'head'
	 * are adjusted to match the full trace हाल which expects that 'old' is
	 * always less than 'head'.
	 */
	अगर (wrapped) अणु
		*old = *head;
		*head += mm->len;
	पूर्ण अन्यथा अणु
		अगर (mm->mask)
			*old &= mm->mask;
		अन्यथा
			*old %= mm->len;
		अगर (*old > *head)
			*head += mm->len;
	पूर्ण

	pr_debug3("%s: wrap-around %sdetected, adjusted old head %zu adjusted new head %zu\n",
		  __func__, wrapped ? "" : "not ", (माप_प्रकार)*old, (माप_प्रकार)*head);

	वापस 0;

out_err:
	pr_err("%s: failed, error %d\n", __func__, err);
	वापस err;
पूर्ण

काष्ठा auxtrace_record *पूर्णांकel_bts_recording_init(पूर्णांक *err)
अणु
	काष्ठा perf_pmu *पूर्णांकel_bts_pmu = perf_pmu__find(INTEL_BTS_PMU_NAME);
	काष्ठा पूर्णांकel_bts_recording *btsr;

	अगर (!पूर्णांकel_bts_pmu)
		वापस शून्य;

	अगर (setenv("JITDUMP_USE_ARCH_TIMESTAMP", "1", 1)) अणु
		*err = -त्रुटि_सं;
		वापस शून्य;
	पूर्ण

	btsr = zalloc(माप(काष्ठा पूर्णांकel_bts_recording));
	अगर (!btsr) अणु
		*err = -ENOMEM;
		वापस शून्य;
	पूर्ण

	btsr->पूर्णांकel_bts_pmu = पूर्णांकel_bts_pmu;
	btsr->itr.pmu = पूर्णांकel_bts_pmu;
	btsr->itr.recording_options = पूर्णांकel_bts_recording_options;
	btsr->itr.info_priv_size = पूर्णांकel_bts_info_priv_size;
	btsr->itr.info_fill = पूर्णांकel_bts_info_fill;
	btsr->itr.मुक्त = पूर्णांकel_bts_recording_मुक्त;
	btsr->itr.snapshot_start = पूर्णांकel_bts_snapshot_start;
	btsr->itr.snapshot_finish = पूर्णांकel_bts_snapshot_finish;
	btsr->itr.find_snapshot = पूर्णांकel_bts_find_snapshot;
	btsr->itr.parse_snapshot_options = पूर्णांकel_bts_parse_snapshot_options;
	btsr->itr.reference = पूर्णांकel_bts_reference;
	btsr->itr.पढ़ो_finish = auxtrace_record__पढ़ो_finish;
	btsr->itr.alignment = माप(काष्ठा branch);
	वापस &btsr->itr;
पूर्ण
