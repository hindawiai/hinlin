<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arm Statistical Profiling Extensions (SPE) support
 * Copyright (c) 2017-2018, Arm Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/zभाग.स>
#समावेश <समय.स>

#समावेश "../../../util/cpumap.h"
#समावेश "../../../util/event.h"
#समावेश "../../../util/evsel.h"
#समावेश "../../../util/evlist.h"
#समावेश "../../../util/session.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "../../../util/pmu.h"
#समावेश "../../../util/debug.h"
#समावेश "../../../util/auxtrace.h"
#समावेश "../../../util/record.h"
#समावेश "../../../util/arm-spe.h"

#घोषणा KiB(x) ((x) * 1024)
#घोषणा MiB(x) ((x) * 1024 * 1024)

काष्ठा arm_spe_recording अणु
	काष्ठा auxtrace_record		itr;
	काष्ठा perf_pmu			*arm_spe_pmu;
	काष्ठा evlist		*evlist;
पूर्ण;

अटल माप_प्रकार
arm_spe_info_priv_size(काष्ठा auxtrace_record *itr __maybe_unused,
		       काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस ARM_SPE_AUXTRACE_PRIV_SIZE;
पूर्ण

अटल पूर्णांक arm_spe_info_fill(काष्ठा auxtrace_record *itr,
			     काष्ठा perf_session *session,
			     काष्ठा perf_record_auxtrace_info *auxtrace_info,
			     माप_प्रकार priv_size)
अणु
	काष्ठा arm_spe_recording *sper =
			container_of(itr, काष्ठा arm_spe_recording, itr);
	काष्ठा perf_pmu *arm_spe_pmu = sper->arm_spe_pmu;

	अगर (priv_size != ARM_SPE_AUXTRACE_PRIV_SIZE)
		वापस -EINVAL;

	अगर (!session->evlist->core.nr_mmaps)
		वापस -EINVAL;

	auxtrace_info->type = PERF_AUXTRACE_ARM_SPE;
	auxtrace_info->priv[ARM_SPE_PMU_TYPE] = arm_spe_pmu->type;

	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe_recording_options(काष्ठा auxtrace_record *itr,
				     काष्ठा evlist *evlist,
				     काष्ठा record_opts *opts)
अणु
	काष्ठा arm_spe_recording *sper =
			container_of(itr, काष्ठा arm_spe_recording, itr);
	काष्ठा perf_pmu *arm_spe_pmu = sper->arm_spe_pmu;
	काष्ठा evsel *evsel, *arm_spe_evsel = शून्य;
	bool privileged = perf_event_paranoid_check(-1);
	काष्ठा evsel *tracking_evsel;
	पूर्णांक err;

	sper->evlist = evlist;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == arm_spe_pmu->type) अणु
			अगर (arm_spe_evsel) अणु
				pr_err("There may be only one " ARM_SPE_PMU_NAME "x event\n");
				वापस -EINVAL;
			पूर्ण
			evsel->core.attr.freq = 0;
			evsel->core.attr.sample_period = 1;
			arm_spe_evsel = evsel;
			opts->full_auxtrace = true;
		पूर्ण
	पूर्ण

	अगर (!opts->full_auxtrace)
		वापस 0;

	/* We are in full trace mode but '-m,xyz' wasn't specअगरied */
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
		माप_प्रकार min_sz = KiB(8);

		अगर (sz < min_sz || !is_घातer_of_2(sz)) अणु
			pr_err("Invalid mmap size for ARM SPE: must be at least %zuKiB and a power of 2\n",
			       min_sz / 1024);
			वापस -EINVAL;
		पूर्ण
	पूर्ण


	/*
	 * To obtain the auxtrace buffer file descriptor, the auxtrace event
	 * must come first.
	 */
	evlist__to_front(evlist, arm_spe_evsel);

	evsel__set_sample_bit(arm_spe_evsel, CPU);
	evsel__set_sample_bit(arm_spe_evsel, TIME);
	evsel__set_sample_bit(arm_spe_evsel, TID);

	/* Add dummy event to keep tracking */
	err = parse_events(evlist, "dummy:u", शून्य);
	अगर (err)
		वापस err;

	tracking_evsel = evlist__last(evlist);
	evlist__set_tracking_event(evlist, tracking_evsel);

	tracking_evsel->core.attr.freq = 0;
	tracking_evsel->core.attr.sample_period = 1;
	evsel__set_sample_bit(tracking_evsel, TIME);
	evsel__set_sample_bit(tracking_evsel, CPU);
	evsel__reset_sample_bit(tracking_evsel, BRANCH_STACK);

	वापस 0;
पूर्ण

अटल u64 arm_spe_reference(काष्ठा auxtrace_record *itr __maybe_unused)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &ts);

	वापस ts.tv_sec ^ ts.tv_nsec;
पूर्ण

अटल व्योम arm_spe_recording_मुक्त(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा arm_spe_recording *sper =
			container_of(itr, काष्ठा arm_spe_recording, itr);

	मुक्त(sper);
पूर्ण

काष्ठा auxtrace_record *arm_spe_recording_init(पूर्णांक *err,
					       काष्ठा perf_pmu *arm_spe_pmu)
अणु
	काष्ठा arm_spe_recording *sper;

	अगर (!arm_spe_pmu) अणु
		*err = -ENODEV;
		वापस शून्य;
	पूर्ण

	sper = zalloc(माप(काष्ठा arm_spe_recording));
	अगर (!sper) अणु
		*err = -ENOMEM;
		वापस शून्य;
	पूर्ण

	sper->arm_spe_pmu = arm_spe_pmu;
	sper->itr.pmu = arm_spe_pmu;
	sper->itr.recording_options = arm_spe_recording_options;
	sper->itr.info_priv_size = arm_spe_info_priv_size;
	sper->itr.info_fill = arm_spe_info_fill;
	sper->itr.मुक्त = arm_spe_recording_मुक्त;
	sper->itr.reference = arm_spe_reference;
	sper->itr.पढ़ो_finish = auxtrace_record__पढ़ो_finish;
	sper->itr.alignment = 0;

	*err = 0;
	वापस &sper->itr;
पूर्ण

काष्ठा perf_event_attr
*arm_spe_pmu_शेष_config(काष्ठा perf_pmu *arm_spe_pmu)
अणु
	काष्ठा perf_event_attr *attr;

	attr = zalloc(माप(काष्ठा perf_event_attr));
	अगर (!attr) अणु
		pr_err("arm_spe default config cannot allocate a perf_event_attr\n");
		वापस शून्य;
	पूर्ण

	/*
	 * If kernel driver करोesn't advertise a minimum,
	 * use max allowable by PMSIDR_EL1.INTERVAL
	 */
	अगर (perf_pmu__scan_file(arm_spe_pmu, "caps/min_interval", "%llu",
				  &attr->sample_period) != 1) अणु
		pr_debug("arm_spe driver doesn't advertise a min. interval. Using 4096\n");
		attr->sample_period = 4096;
	पूर्ण

	arm_spe_pmu->selectable = true;
	arm_spe_pmu->is_uncore = false;

	वापस attr;
पूर्ण
