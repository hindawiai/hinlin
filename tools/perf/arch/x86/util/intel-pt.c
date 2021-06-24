<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pt.c: Intel Processor Trace support
 * Copyright (c) 2013-2015, Intel Corporation.
 */

#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/zभाग.स>
#समावेश <cpuid.h>

#समावेश "../../../util/session.h"
#समावेश "../../../util/event.h"
#समावेश "../../../util/evlist.h"
#समावेश "../../../util/evsel.h"
#समावेश "../../../util/evsel_config.h"
#समावेश "../../../util/cpumap.h"
#समावेश "../../../util/mmap.h"
#समावेश <subcmd/parse-options.h>
#समावेश "../../../util/parse-events.h"
#समावेश "../../../util/pmu.h"
#समावेश "../../../util/debug.h"
#समावेश "../../../util/auxtrace.h"
#समावेश "../../../util/perf_api_probe.h"
#समावेश "../../../util/record.h"
#समावेश "../../../util/target.h"
#समावेश "../../../util/tsc.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "../../../util/intel-pt.h"

#घोषणा KiB(x) ((x) * 1024)
#घोषणा MiB(x) ((x) * 1024 * 1024)
#घोषणा KiB_MASK(x) (KiB(x) - 1)
#घोषणा MiB_MASK(x) (MiB(x) - 1)

#घोषणा INTEL_PT_PSB_PERIOD_NEAR	256

काष्ठा पूर्णांकel_pt_snapshot_ref अणु
	व्योम *ref_buf;
	माप_प्रकार ref_offset;
	bool wrapped;
पूर्ण;

काष्ठा पूर्णांकel_pt_recording अणु
	काष्ठा auxtrace_record		itr;
	काष्ठा perf_pmu			*पूर्णांकel_pt_pmu;
	पूर्णांक				have_sched_चयन;
	काष्ठा evlist		*evlist;
	bool				snapshot_mode;
	bool				snapshot_init_करोne;
	माप_प्रकार				snapshot_size;
	माप_प्रकार				snapshot_ref_buf_size;
	पूर्णांक				snapshot_ref_cnt;
	काष्ठा पूर्णांकel_pt_snapshot_ref	*snapshot_refs;
	माप_प्रकार				priv_size;
पूर्ण;

अटल पूर्णांक पूर्णांकel_pt_parse_terms_with_शेष(स्थिर अक्षर *pmu_name,
					     काष्ठा list_head *क्रमmats,
					     स्थिर अक्षर *str,
					     u64 *config)
अणु
	काष्ठा list_head *terms;
	काष्ठा perf_event_attr attr = अणु .size = 0, पूर्ण;
	पूर्णांक err;

	terms = दो_स्मृति(माप(काष्ठा list_head));
	अगर (!terms)
		वापस -ENOMEM;

	INIT_LIST_HEAD(terms);

	err = parse_events_terms(terms, str);
	अगर (err)
		जाओ out_मुक्त;

	attr.config = *config;
	err = perf_pmu__config_terms(pmu_name, क्रमmats, &attr, terms, true,
				     शून्य);
	अगर (err)
		जाओ out_मुक्त;

	*config = attr.config;
out_मुक्त:
	parse_events_terms__delete(terms);
	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_parse_terms(स्थिर अक्षर *pmu_name, काष्ठा list_head *क्रमmats,
				स्थिर अक्षर *str, u64 *config)
अणु
	*config = 0;
	वापस पूर्णांकel_pt_parse_terms_with_शेष(pmu_name, क्रमmats, str,
						 config);
पूर्ण

अटल u64 पूर्णांकel_pt_masked_bits(u64 mask, u64 bits)
अणु
	स्थिर u64 top_bit = 1ULL << 63;
	u64 res = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 64; i++) अणु
		अगर (mask & top_bit) अणु
			res <<= 1;
			अगर (bits & top_bit)
				res |= 1;
		पूर्ण
		mask <<= 1;
		bits <<= 1;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_पढ़ो_config(काष्ठा perf_pmu *पूर्णांकel_pt_pmu, स्थिर अक्षर *str,
				काष्ठा evlist *evlist, u64 *res)
अणु
	काष्ठा evsel *evsel;
	u64 mask;

	*res = 0;

	mask = perf_pmu__क्रमmat_bits(&पूर्णांकel_pt_pmu->क्रमmat, str);
	अगर (!mask)
		वापस -EINVAL;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == पूर्णांकel_pt_pmu->type) अणु
			*res = पूर्णांकel_pt_masked_bits(mask, evsel->core.attr.config);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल माप_प्रकार पूर्णांकel_pt_psb_period(काष्ठा perf_pmu *पूर्णांकel_pt_pmu,
				  काष्ठा evlist *evlist)
अणु
	u64 val;
	पूर्णांक err, topa_multiple_entries;
	माप_प्रकार psb_period;

	अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "caps/topa_multiple_entries",
				"%d", &topa_multiple_entries) != 1)
		topa_multiple_entries = 0;

	/*
	 * Use caps/topa_multiple_entries to indicate early hardware that had
	 * extra frequent PSBs.
	 */
	अगर (!topa_multiple_entries) अणु
		psb_period = 256;
		जाओ out;
	पूर्ण

	err = पूर्णांकel_pt_पढ़ो_config(पूर्णांकel_pt_pmu, "psb_period", evlist, &val);
	अगर (err)
		val = 0;

	psb_period = 1 << (val + 11);
out:
	pr_debug2("%s psb_period %zu\n", पूर्णांकel_pt_pmu->name, psb_period);
	वापस psb_period;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_pick_bit(पूर्णांक bits, पूर्णांक target)
अणु
	पूर्णांक pos, pick = -1;

	क्रम (pos = 0; bits; bits >>= 1, pos++) अणु
		अगर (bits & 1) अणु
			अगर (pos <= target || pick < 0)
				pick = pos;
			अगर (pos >= target)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस pick;
पूर्ण

अटल u64 पूर्णांकel_pt_शेष_config(काष्ठा perf_pmu *पूर्णांकel_pt_pmu)
अणु
	अक्षर buf[256];
	पूर्णांक mtc, mtc_periods = 0, mtc_period;
	पूर्णांक psb_cyc, psb_periods, psb_period;
	पूर्णांक pos = 0;
	u64 config;
	अक्षर c;

	pos += scnम_लिखो(buf + pos, माप(buf) - pos, "tsc");

	अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "caps/mtc", "%d",
				&mtc) != 1)
		mtc = 1;

	अगर (mtc) अणु
		अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "caps/mtc_periods", "%x",
					&mtc_periods) != 1)
			mtc_periods = 0;
		अगर (mtc_periods) अणु
			mtc_period = पूर्णांकel_pt_pick_bit(mtc_periods, 3);
			pos += scnम_लिखो(buf + pos, माप(buf) - pos,
					 ",mtc,mtc_period=%d", mtc_period);
		पूर्ण
	पूर्ण

	अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "caps/psb_cyc", "%d",
				&psb_cyc) != 1)
		psb_cyc = 1;

	अगर (psb_cyc && mtc_periods) अणु
		अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "caps/psb_periods", "%x",
					&psb_periods) != 1)
			psb_periods = 0;
		अगर (psb_periods) अणु
			psb_period = पूर्णांकel_pt_pick_bit(psb_periods, 3);
			pos += scnम_लिखो(buf + pos, माप(buf) - pos,
					 ",psb_period=%d", psb_period);
		पूर्ण
	पूर्ण

	अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "format/pt", "%c", &c) == 1 &&
	    perf_pmu__scan_file(पूर्णांकel_pt_pmu, "format/branch", "%c", &c) == 1)
		pos += scnम_लिखो(buf + pos, माप(buf) - pos, ",pt,branch");

	pr_debug2("%s default config: %s\n", पूर्णांकel_pt_pmu->name, buf);

	पूर्णांकel_pt_parse_terms(पूर्णांकel_pt_pmu->name, &पूर्णांकel_pt_pmu->क्रमmat, buf,
			     &config);

	वापस config;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_parse_snapshot_options(काष्ठा auxtrace_record *itr,
					   काष्ठा record_opts *opts,
					   स्थिर अक्षर *str)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);
	अचिन्हित दीर्घ दीर्घ snapshot_size = 0;
	अक्षर *endptr;

	अगर (str) अणु
		snapshot_size = म_से_अदीर्घl(str, &endptr, 0);
		अगर (*endptr || snapshot_size > SIZE_MAX)
			वापस -1;
	पूर्ण

	opts->auxtrace_snapshot_mode = true;
	opts->auxtrace_snapshot_size = snapshot_size;

	ptr->snapshot_size = snapshot_size;

	वापस 0;
पूर्ण

काष्ठा perf_event_attr *
पूर्णांकel_pt_pmu_शेष_config(काष्ठा perf_pmu *पूर्णांकel_pt_pmu)
अणु
	काष्ठा perf_event_attr *attr;

	attr = zalloc(माप(काष्ठा perf_event_attr));
	अगर (!attr)
		वापस शून्य;

	attr->config = पूर्णांकel_pt_शेष_config(पूर्णांकel_pt_pmu);

	पूर्णांकel_pt_pmu->selectable = true;

	वापस attr;
पूर्ण

अटल स्थिर अक्षर *पूर्णांकel_pt_find_filter(काष्ठा evlist *evlist,
					काष्ठा perf_pmu *पूर्णांकel_pt_pmu)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == पूर्णांकel_pt_pmu->type)
			वापस evsel->filter;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल माप_प्रकार पूर्णांकel_pt_filter_bytes(स्थिर अक्षर *filter)
अणु
	माप_प्रकार len = filter ? म_माप(filter) : 0;

	वापस len ? roundup(len + 1, 8) : 0;
पूर्ण

अटल माप_प्रकार
पूर्णांकel_pt_info_priv_size(काष्ठा auxtrace_record *itr, काष्ठा evlist *evlist)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);
	स्थिर अक्षर *filter = पूर्णांकel_pt_find_filter(evlist, ptr->पूर्णांकel_pt_pmu);

	ptr->priv_size = (INTEL_PT_AUXTRACE_PRIV_MAX * माप(u64)) +
			 पूर्णांकel_pt_filter_bytes(filter);

	वापस ptr->priv_size;
पूर्ण

अटल व्योम पूर्णांकel_pt_tsc_ctc_ratio(u32 *n, u32 *d)
अणु
	अचिन्हित पूर्णांक eax = 0, ebx = 0, ecx = 0, edx = 0;

	__get_cpuid(0x15, &eax, &ebx, &ecx, &edx);
	*n = ebx;
	*d = eax;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_info_fill(काष्ठा auxtrace_record *itr,
			      काष्ठा perf_session *session,
			      काष्ठा perf_record_auxtrace_info *auxtrace_info,
			      माप_प्रकार priv_size)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);
	काष्ठा perf_pmu *पूर्णांकel_pt_pmu = ptr->पूर्णांकel_pt_pmu;
	काष्ठा perf_event_mmap_page *pc;
	काष्ठा perf_tsc_conversion tc = अणु .समय_mult = 0, पूर्ण;
	bool cap_user_समय_zero = false, per_cpu_mmaps;
	u64 tsc_bit, mtc_bit, mtc_freq_bits, cyc_bit, noretcomp_bit;
	u32 tsc_ctc_ratio_n, tsc_ctc_ratio_d;
	अचिन्हित दीर्घ max_non_turbo_ratio;
	माप_प्रकार filter_str_len;
	स्थिर अक्षर *filter;
	__u64 *info;
	पूर्णांक err;

	अगर (priv_size != ptr->priv_size)
		वापस -EINVAL;

	पूर्णांकel_pt_parse_terms(पूर्णांकel_pt_pmu->name, &पूर्णांकel_pt_pmu->क्रमmat,
			     "tsc", &tsc_bit);
	पूर्णांकel_pt_parse_terms(पूर्णांकel_pt_pmu->name, &पूर्णांकel_pt_pmu->क्रमmat,
			     "noretcomp", &noretcomp_bit);
	पूर्णांकel_pt_parse_terms(पूर्णांकel_pt_pmu->name, &पूर्णांकel_pt_pmu->क्रमmat,
			     "mtc", &mtc_bit);
	mtc_freq_bits = perf_pmu__क्रमmat_bits(&पूर्णांकel_pt_pmu->क्रमmat,
					      "mtc_period");
	पूर्णांकel_pt_parse_terms(पूर्णांकel_pt_pmu->name, &पूर्णांकel_pt_pmu->क्रमmat,
			     "cyc", &cyc_bit);

	पूर्णांकel_pt_tsc_ctc_ratio(&tsc_ctc_ratio_n, &tsc_ctc_ratio_d);

	अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "max_nonturbo_ratio",
				"%lu", &max_non_turbo_ratio) != 1)
		max_non_turbo_ratio = 0;

	filter = पूर्णांकel_pt_find_filter(session->evlist, ptr->पूर्णांकel_pt_pmu);
	filter_str_len = filter ? म_माप(filter) : 0;

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
			ui__warning("Intel Processor Trace: TSC not available\n");
	पूर्ण

	per_cpu_mmaps = !perf_cpu_map__empty(session->evlist->core.cpus);

	auxtrace_info->type = PERF_AUXTRACE_INTEL_PT;
	auxtrace_info->priv[INTEL_PT_PMU_TYPE] = पूर्णांकel_pt_pmu->type;
	auxtrace_info->priv[INTEL_PT_TIME_SHIFT] = tc.समय_shअगरt;
	auxtrace_info->priv[INTEL_PT_TIME_MULT] = tc.समय_mult;
	auxtrace_info->priv[INTEL_PT_TIME_ZERO] = tc.समय_zero;
	auxtrace_info->priv[INTEL_PT_CAP_USER_TIME_ZERO] = cap_user_समय_zero;
	auxtrace_info->priv[INTEL_PT_TSC_BIT] = tsc_bit;
	auxtrace_info->priv[INTEL_PT_NORETCOMP_BIT] = noretcomp_bit;
	auxtrace_info->priv[INTEL_PT_HAVE_SCHED_SWITCH] = ptr->have_sched_चयन;
	auxtrace_info->priv[INTEL_PT_SNAPSHOT_MODE] = ptr->snapshot_mode;
	auxtrace_info->priv[INTEL_PT_PER_CPU_MMAPS] = per_cpu_mmaps;
	auxtrace_info->priv[INTEL_PT_MTC_BIT] = mtc_bit;
	auxtrace_info->priv[INTEL_PT_MTC_FREQ_BITS] = mtc_freq_bits;
	auxtrace_info->priv[INTEL_PT_TSC_CTC_N] = tsc_ctc_ratio_n;
	auxtrace_info->priv[INTEL_PT_TSC_CTC_D] = tsc_ctc_ratio_d;
	auxtrace_info->priv[INTEL_PT_CYC_BIT] = cyc_bit;
	auxtrace_info->priv[INTEL_PT_MAX_NONTURBO_RATIO] = max_non_turbo_ratio;
	auxtrace_info->priv[INTEL_PT_FILTER_STR_LEN] = filter_str_len;

	info = &auxtrace_info->priv[INTEL_PT_FILTER_STR_LEN] + 1;

	अगर (filter_str_len) अणु
		माप_प्रकार len = पूर्णांकel_pt_filter_bytes(filter);

		म_नकलन((अक्षर *)info, filter, len);
		info += len >> 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_track_चयनes(काष्ठा evlist *evlist)
अणु
	स्थिर अक्षर *sched_चयन = "sched:sched_switch";
	काष्ठा evsel *evsel;
	पूर्णांक err;

	अगर (!evlist__can_select_event(evlist, sched_चयन))
		वापस -EPERM;

	err = parse_events(evlist, sched_चयन, शून्य);
	अगर (err) अणु
		pr_debug2("%s: failed to parse %s, error %d\n",
			  __func__, sched_चयन, err);
		वापस err;
	पूर्ण

	evsel = evlist__last(evlist);

	evsel__set_sample_bit(evsel, CPU);
	evsel__set_sample_bit(evsel, TIME);

	evsel->core.प्रणाली_wide = true;
	evsel->no_aux_samples = true;
	evsel->immediate = true;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_valid_str(अक्षर *str, माप_प्रकार len, u64 valid)
अणु
	अचिन्हित पूर्णांक val, last = 0, state = 1;
	पूर्णांक p = 0;

	str[0] = '\0';

	क्रम (val = 0; val <= 64; val++, valid >>= 1) अणु
		अगर (valid & 1) अणु
			last = val;
			चयन (state) अणु
			हाल 0:
				p += scnम_लिखो(str + p, len - p, ",");
				/* Fall through */
			हाल 1:
				p += scnम_लिखो(str + p, len - p, "%u", val);
				state = 2;
				अवरोध;
			हाल 2:
				state = 3;
				अवरोध;
			हाल 3:
				state = 4;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (state) अणु
			हाल 3:
				p += scnम_लिखो(str + p, len - p, ",%u", last);
				state = 0;
				अवरोध;
			हाल 4:
				p += scnम_लिखो(str + p, len - p, "-%u", last);
				state = 0;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अगर (state != 1)
				state = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_val_config_term(काष्ठा perf_pmu *पूर्णांकel_pt_pmu,
				    स्थिर अक्षर *caps, स्थिर अक्षर *name,
				    स्थिर अक्षर *supported, u64 config)
अणु
	अक्षर valid_str[256];
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित दीर्घ दीर्घ valid;
	u64 bits;
	पूर्णांक ok;

	अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, caps, "%llx", &valid) != 1)
		valid = 0;

	अगर (supported &&
	    perf_pmu__scan_file(पूर्णांकel_pt_pmu, supported, "%d", &ok) == 1 && !ok)
		valid = 0;

	valid |= 1;

	bits = perf_pmu__क्रमmat_bits(&पूर्णांकel_pt_pmu->क्रमmat, name);

	config &= bits;

	क्रम (shअगरt = 0; bits && !(bits & 1); shअगरt++)
		bits >>= 1;

	config >>= shअगरt;

	अगर (config > 63)
		जाओ out_err;

	अगर (valid & (1 << config))
		वापस 0;
out_err:
	पूर्णांकel_pt_valid_str(valid_str, माप(valid_str), valid);
	pr_err("Invalid %s for %s. Valid values are: %s\n",
	       name, INTEL_PT_PMU_NAME, valid_str);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_validate_config(काष्ठा perf_pmu *पूर्णांकel_pt_pmu,
				    काष्ठा evsel *evsel)
अणु
	पूर्णांक err;
	अक्षर c;

	अगर (!evsel)
		वापस 0;

	/*
	 * If supported, क्रमce pass-through config term (pt=1) even अगर user
	 * sets pt=0, which aव्योमs senseless kernel errors.
	 */
	अगर (perf_pmu__scan_file(पूर्णांकel_pt_pmu, "format/pt", "%c", &c) == 1 &&
	    !(evsel->core.attr.config & 1)) अणु
		pr_warning("pt=0 doesn't make sense, forcing pt=1\n");
		evsel->core.attr.config |= 1;
	पूर्ण

	err = पूर्णांकel_pt_val_config_term(पूर्णांकel_pt_pmu, "caps/cycle_thresholds",
				       "cyc_thresh", "caps/psb_cyc",
				       evsel->core.attr.config);
	अगर (err)
		वापस err;

	err = पूर्णांकel_pt_val_config_term(पूर्णांकel_pt_pmu, "caps/mtc_periods",
				       "mtc_period", "caps/mtc",
				       evsel->core.attr.config);
	अगर (err)
		वापस err;

	वापस पूर्णांकel_pt_val_config_term(पूर्णांकel_pt_pmu, "caps/psb_periods",
					"psb_period", "caps/psb_cyc",
					evsel->core.attr.config);
पूर्ण

अटल व्योम पूर्णांकel_pt_config_sample_mode(काष्ठा perf_pmu *पूर्णांकel_pt_pmu,
					काष्ठा evsel *evsel)
अणु
	u64 user_bits = 0, bits;
	काष्ठा evsel_config_term *term = evsel__get_config_term(evsel, CFG_CHG);

	अगर (term)
		user_bits = term->val.cfg_chg;

	bits = perf_pmu__क्रमmat_bits(&पूर्णांकel_pt_pmu->क्रमmat, "psb_period");

	/* Did user change psb_period */
	अगर (bits & user_bits)
		वापस;

	/* Set psb_period to 0 */
	evsel->core.attr.config &= ~bits;
पूर्ण

अटल व्योम पूर्णांकel_pt_min_max_sample_sz(काष्ठा evlist *evlist,
				       माप_प्रकार *min_sz, माप_प्रकार *max_sz)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		माप_प्रकार sz = evsel->core.attr.aux_sample_size;

		अगर (!sz)
			जारी;
		अगर (min_sz && (sz < *min_sz || !*min_sz))
			*min_sz = sz;
		अगर (max_sz && sz > *max_sz)
			*max_sz = sz;
	पूर्ण
पूर्ण

/*
 * Currently, there is not enough inक्रमmation to disambiguate dअगरferent PEBS
 * events, so only allow one.
 */
अटल bool पूर्णांकel_pt_too_many_aux_output(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक aux_output_cnt = 0;

	evlist__क्रम_each_entry(evlist, evsel)
		aux_output_cnt += !!evsel->core.attr.aux_output;

	अगर (aux_output_cnt > 1) अणु
		pr_err(INTEL_PT_PMU_NAME " supports at most one event with aux-output\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_recording_options(काष्ठा auxtrace_record *itr,
				      काष्ठा evlist *evlist,
				      काष्ठा record_opts *opts)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);
	काष्ठा perf_pmu *पूर्णांकel_pt_pmu = ptr->पूर्णांकel_pt_pmu;
	bool have_timing_info, need_immediate = false;
	काष्ठा evsel *evsel, *पूर्णांकel_pt_evsel = शून्य;
	स्थिर काष्ठा perf_cpu_map *cpus = evlist->core.cpus;
	bool privileged = perf_event_paranoid_check(-1);
	u64 tsc_bit;
	पूर्णांक err;

	ptr->evlist = evlist;
	ptr->snapshot_mode = opts->auxtrace_snapshot_mode;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == पूर्णांकel_pt_pmu->type) अणु
			अगर (पूर्णांकel_pt_evsel) अणु
				pr_err("There may be only one " INTEL_PT_PMU_NAME " event\n");
				वापस -EINVAL;
			पूर्ण
			evsel->core.attr.freq = 0;
			evsel->core.attr.sample_period = 1;
			evsel->no_aux_samples = true;
			पूर्णांकel_pt_evsel = evsel;
			opts->full_auxtrace = true;
		पूर्ण
	पूर्ण

	अगर (opts->auxtrace_snapshot_mode && !opts->full_auxtrace) अणु
		pr_err("Snapshot mode (-S option) requires " INTEL_PT_PMU_NAME " PMU event (-e " INTEL_PT_PMU_NAME ")\n");
		वापस -EINVAL;
	पूर्ण

	अगर (opts->auxtrace_snapshot_mode && opts->auxtrace_sample_mode) अणु
		pr_err("Snapshot mode (" INTEL_PT_PMU_NAME " PMU) and sample trace cannot be used together\n");
		वापस -EINVAL;
	पूर्ण

	अगर (opts->use_घड़ीid) अणु
		pr_err("Cannot use clockid (-k option) with " INTEL_PT_PMU_NAME "\n");
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकel_pt_too_many_aux_output(evlist))
		वापस -EINVAL;

	अगर (!opts->full_auxtrace)
		वापस 0;

	अगर (opts->auxtrace_sample_mode)
		पूर्णांकel_pt_config_sample_mode(पूर्णांकel_pt_pmu, पूर्णांकel_pt_evsel);

	err = पूर्णांकel_pt_validate_config(पूर्णांकel_pt_pmu, पूर्णांकel_pt_evsel);
	अगर (err)
		वापस err;

	/* Set शेष sizes क्रम snapshot mode */
	अगर (opts->auxtrace_snapshot_mode) अणु
		माप_प्रकार psb_period = पूर्णांकel_pt_psb_period(पूर्णांकel_pt_pmu, evlist);

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
		pr_debug2("Intel PT snapshot size: %zu\n",
			  opts->auxtrace_snapshot_size);
		अगर (psb_period &&
		    opts->auxtrace_snapshot_size <= psb_period +
						  INTEL_PT_PSB_PERIOD_NEAR)
			ui__warning("Intel PT snapshot size (%zu) may be too small for PSB period (%zu)\n",
				    opts->auxtrace_snapshot_size, psb_period);
	पूर्ण

	/* Set शेष sizes क्रम sample mode */
	अगर (opts->auxtrace_sample_mode) अणु
		माप_प्रकार psb_period = पूर्णांकel_pt_psb_period(पूर्णांकel_pt_pmu, evlist);
		माप_प्रकार min_sz = 0, max_sz = 0;

		पूर्णांकel_pt_min_max_sample_sz(evlist, &min_sz, &max_sz);
		अगर (!opts->auxtrace_mmap_pages && !privileged &&
		    opts->mmap_pages == अच_पूर्णांक_उच्च)
			opts->mmap_pages = KiB(256) / page_size;
		अगर (!opts->auxtrace_mmap_pages) अणु
			माप_प्रकार sz = round_up(max_sz, page_size) / page_size;

			opts->auxtrace_mmap_pages = roundup_घात_of_two(sz);
		पूर्ण
		अगर (max_sz > opts->auxtrace_mmap_pages * (माप_प्रकार)page_size) अणु
			pr_err("Sample size %zu must not be greater than AUX area tracing mmap size %zu\n",
			       max_sz,
			       opts->auxtrace_mmap_pages * (माप_प्रकार)page_size);
			वापस -EINVAL;
		पूर्ण
		pr_debug2("Intel PT min. sample size: %zu max. sample size: %zu\n",
			  min_sz, max_sz);
		अगर (psb_period &&
		    min_sz <= psb_period + INTEL_PT_PSB_PERIOD_NEAR)
			ui__warning("Intel PT sample size (%zu) may be too small for PSB period (%zu)\n",
				    min_sz, psb_period);
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

		अगर (opts->auxtrace_snapshot_mode || opts->auxtrace_sample_mode)
			min_sz = KiB(4);
		अन्यथा
			min_sz = KiB(8);

		अगर (sz < min_sz || !is_घातer_of_2(sz)) अणु
			pr_err("Invalid mmap size for Intel Processor Trace: must be at least %zuKiB and a power of 2\n",
			       min_sz / 1024);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!opts->auxtrace_snapshot_mode && !opts->auxtrace_sample_mode) अणु
		u32 aux_watermark = opts->auxtrace_mmap_pages * page_size / 4;

		पूर्णांकel_pt_evsel->core.attr.aux_watermark = aux_watermark;
	पूर्ण

	पूर्णांकel_pt_parse_terms(पूर्णांकel_pt_pmu->name, &पूर्णांकel_pt_pmu->क्रमmat,
			     "tsc", &tsc_bit);

	अगर (opts->full_auxtrace && (पूर्णांकel_pt_evsel->core.attr.config & tsc_bit))
		have_timing_info = true;
	अन्यथा
		have_timing_info = false;

	/*
	 * Per-cpu recording needs sched_चयन events to distinguish dअगरferent
	 * thपढ़ोs.
	 */
	अगर (have_timing_info && !perf_cpu_map__empty(cpus) &&
	    !record_opts__no_चयन_events(opts)) अणु
		अगर (perf_can_record_चयन_events()) अणु
			bool cpu_wide = !target__none(&opts->target) &&
					!target__has_task(&opts->target);

			अगर (!cpu_wide && perf_can_record_cpu_wide()) अणु
				काष्ठा evsel *चयन_evsel;

				err = parse_events(evlist, "dummy:u", शून्य);
				अगर (err)
					वापस err;

				चयन_evsel = evlist__last(evlist);

				चयन_evsel->core.attr.freq = 0;
				चयन_evsel->core.attr.sample_period = 1;
				चयन_evsel->core.attr.context_चयन = 1;

				चयन_evsel->core.प्रणाली_wide = true;
				चयन_evsel->no_aux_samples = true;
				चयन_evsel->immediate = true;

				evsel__set_sample_bit(चयन_evsel, TID);
				evsel__set_sample_bit(चयन_evsel, TIME);
				evsel__set_sample_bit(चयन_evsel, CPU);
				evsel__reset_sample_bit(चयन_evsel, BRANCH_STACK);

				opts->record_चयन_events = false;
				ptr->have_sched_चयन = 3;
			पूर्ण अन्यथा अणु
				opts->record_चयन_events = true;
				need_immediate = true;
				अगर (cpu_wide)
					ptr->have_sched_चयन = 3;
				अन्यथा
					ptr->have_sched_चयन = 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = पूर्णांकel_pt_track_चयनes(evlist);
			अगर (err == -EPERM)
				pr_debug2("Unable to select sched:sched_switch\n");
			अन्यथा अगर (err)
				वापस err;
			अन्यथा
				ptr->have_sched_चयन = 1;
		पूर्ण
	पूर्ण

	अगर (have_timing_info && !पूर्णांकel_pt_evsel->core.attr.exclude_kernel &&
	    perf_can_record_text_poke_events() && perf_can_record_cpu_wide())
		opts->text_poke = true;

	अगर (पूर्णांकel_pt_evsel) अणु
		/*
		 * To obtain the auxtrace buffer file descriptor, the auxtrace
		 * event must come first.
		 */
		evlist__to_front(evlist, पूर्णांकel_pt_evsel);
		/*
		 * In the हाल of per-cpu mmaps, we need the CPU on the
		 * AUX event.
		 */
		अगर (!perf_cpu_map__empty(cpus))
			evsel__set_sample_bit(पूर्णांकel_pt_evsel, CPU);
	पूर्ण

	/* Add dummy event to keep tracking */
	अगर (opts->full_auxtrace) अणु
		काष्ठा evsel *tracking_evsel;

		err = parse_events(evlist, "dummy:u", शून्य);
		अगर (err)
			वापस err;

		tracking_evsel = evlist__last(evlist);

		evlist__set_tracking_event(evlist, tracking_evsel);

		tracking_evsel->core.attr.freq = 0;
		tracking_evsel->core.attr.sample_period = 1;

		tracking_evsel->no_aux_samples = true;
		अगर (need_immediate)
			tracking_evsel->immediate = true;

		/* In per-cpu हाल, always need the समय of mmap events etc */
		अगर (!perf_cpu_map__empty(cpus)) अणु
			evsel__set_sample_bit(tracking_evsel, TIME);
			/* And the CPU क्रम चयन events */
			evsel__set_sample_bit(tracking_evsel, CPU);
		पूर्ण
		evsel__reset_sample_bit(tracking_evsel, BRANCH_STACK);
	पूर्ण

	/*
	 * Warn the user when we करो not have enough inक्रमmation to decode i.e.
	 * per-cpu with no sched_चयन (except workload-only).
	 */
	अगर (!ptr->have_sched_चयन && !perf_cpu_map__empty(cpus) &&
	    !target__none(&opts->target) &&
	    !पूर्णांकel_pt_evsel->core.attr.exclude_user)
		ui__warning("Intel Processor Trace decoding will not be possible except for kernel tracing!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_snapshot_start(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(ptr->evlist, evsel) अणु
		अगर (evsel->core.attr.type == ptr->पूर्णांकel_pt_pmu->type)
			वापस evsel__disable(evsel);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_snapshot_finish(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(ptr->evlist, evsel) अणु
		अगर (evsel->core.attr.type == ptr->पूर्णांकel_pt_pmu->type)
			वापस evsel__enable(evsel);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_alloc_snapshot_refs(काष्ठा पूर्णांकel_pt_recording *ptr, पूर्णांक idx)
अणु
	स्थिर माप_प्रकार sz = माप(काष्ठा पूर्णांकel_pt_snapshot_ref);
	पूर्णांक cnt = ptr->snapshot_ref_cnt, new_cnt = cnt * 2;
	काष्ठा पूर्णांकel_pt_snapshot_ref *refs;

	अगर (!new_cnt)
		new_cnt = 16;

	जबतक (new_cnt <= idx)
		new_cnt *= 2;

	refs = सुस्मृति(new_cnt, sz);
	अगर (!refs)
		वापस -ENOMEM;

	स_नकल(refs, ptr->snapshot_refs, cnt * sz);

	ptr->snapshot_refs = refs;
	ptr->snapshot_ref_cnt = new_cnt;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_मुक्त_snapshot_refs(काष्ठा पूर्णांकel_pt_recording *ptr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ptr->snapshot_ref_cnt; i++)
		zमुक्त(&ptr->snapshot_refs[i].ref_buf);
	zमुक्त(&ptr->snapshot_refs);
पूर्ण

अटल व्योम पूर्णांकel_pt_recording_मुक्त(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);

	पूर्णांकel_pt_मुक्त_snapshot_refs(ptr);
	मुक्त(ptr);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_alloc_snapshot_ref(काष्ठा पूर्णांकel_pt_recording *ptr, पूर्णांक idx,
				       माप_प्रकार snapshot_buf_size)
अणु
	माप_प्रकार ref_buf_size = ptr->snapshot_ref_buf_size;
	व्योम *ref_buf;

	ref_buf = zalloc(ref_buf_size);
	अगर (!ref_buf)
		वापस -ENOMEM;

	ptr->snapshot_refs[idx].ref_buf = ref_buf;
	ptr->snapshot_refs[idx].ref_offset = snapshot_buf_size - ref_buf_size;

	वापस 0;
पूर्ण

अटल माप_प्रकार पूर्णांकel_pt_snapshot_ref_buf_size(काष्ठा पूर्णांकel_pt_recording *ptr,
					     माप_प्रकार snapshot_buf_size)
अणु
	स्थिर माप_प्रकार max_size = 256 * 1024;
	माप_प्रकार buf_size = 0, psb_period;

	अगर (ptr->snapshot_size <= 64 * 1024)
		वापस 0;

	psb_period = पूर्णांकel_pt_psb_period(ptr->पूर्णांकel_pt_pmu, ptr->evlist);
	अगर (psb_period)
		buf_size = psb_period * 2;

	अगर (!buf_size || buf_size > max_size)
		buf_size = max_size;

	अगर (buf_size >= snapshot_buf_size)
		वापस 0;

	अगर (buf_size >= ptr->snapshot_size / 2)
		वापस 0;

	वापस buf_size;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_snapshot_init(काष्ठा पूर्णांकel_pt_recording *ptr,
				  माप_प्रकार snapshot_buf_size)
अणु
	अगर (ptr->snapshot_init_करोne)
		वापस 0;

	ptr->snapshot_init_करोne = true;

	ptr->snapshot_ref_buf_size = पूर्णांकel_pt_snapshot_ref_buf_size(ptr,
							snapshot_buf_size);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_pt_compare_buffers - compare bytes in a buffer to a circular buffer.
 * @buf1: first buffer
 * @compare_size: number of bytes to compare
 * @buf2: second buffer (a circular buffer)
 * @offs2: offset in second buffer
 * @buf2_size: size of second buffer
 *
 * The comparison allows क्रम the possibility that the bytes to compare in the
 * circular buffer are not contiguous.  It is assumed that @compare_size <=
 * @buf2_size.  This function वापसs %false अगर the bytes are identical, %true
 * otherwise.
 */
अटल bool पूर्णांकel_pt_compare_buffers(व्योम *buf1, माप_प्रकार compare_size,
				     व्योम *buf2, माप_प्रकार offs2, माप_प्रकार buf2_size)
अणु
	माप_प्रकार end2 = offs2 + compare_size, part_size;

	अगर (end2 <= buf2_size)
		वापस स_भेद(buf1, buf2 + offs2, compare_size);

	part_size = end2 - buf2_size;
	अगर (स_भेद(buf1, buf2 + offs2, part_size))
		वापस true;

	compare_size -= part_size;

	वापस स_भेद(buf1 + part_size, buf2, compare_size);
पूर्ण

अटल bool पूर्णांकel_pt_compare_ref(व्योम *ref_buf, माप_प्रकार ref_offset,
				 माप_प्रकार ref_size, माप_प्रकार buf_size,
				 व्योम *data, माप_प्रकार head)
अणु
	माप_प्रकार ref_end = ref_offset + ref_size;

	अगर (ref_end > buf_size) अणु
		अगर (head > ref_offset || head < ref_end - buf_size)
			वापस true;
	पूर्ण अन्यथा अगर (head > ref_offset && head < ref_end) अणु
		वापस true;
	पूर्ण

	वापस पूर्णांकel_pt_compare_buffers(ref_buf, ref_size, data, ref_offset,
					buf_size);
पूर्ण

अटल व्योम पूर्णांकel_pt_copy_ref(व्योम *ref_buf, माप_प्रकार ref_size, माप_प्रकार buf_size,
			      व्योम *data, माप_प्रकार head)
अणु
	अगर (head >= ref_size) अणु
		स_नकल(ref_buf, data + head - ref_size, ref_size);
	पूर्ण अन्यथा अणु
		स_नकल(ref_buf, data, head);
		ref_size -= head;
		स_नकल(ref_buf + head, data + buf_size - ref_size, ref_size);
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_pt_wrapped(काष्ठा पूर्णांकel_pt_recording *ptr, पूर्णांक idx,
			     काष्ठा auxtrace_mmap *mm, अचिन्हित अक्षर *data,
			     u64 head)
अणु
	काष्ठा पूर्णांकel_pt_snapshot_ref *ref = &ptr->snapshot_refs[idx];
	bool wrapped;

	wrapped = पूर्णांकel_pt_compare_ref(ref->ref_buf, ref->ref_offset,
				       ptr->snapshot_ref_buf_size, mm->len,
				       data, head);

	पूर्णांकel_pt_copy_ref(ref->ref_buf, ptr->snapshot_ref_buf_size, mm->len,
			  data, head);

	वापस wrapped;
पूर्ण

अटल bool पूर्णांकel_pt_first_wrap(u64 *data, माप_प्रकार buf_size)
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

अटल पूर्णांक पूर्णांकel_pt_find_snapshot(काष्ठा auxtrace_record *itr, पूर्णांक idx,
				  काष्ठा auxtrace_mmap *mm, अचिन्हित अक्षर *data,
				  u64 *head, u64 *old)
अणु
	काष्ठा पूर्णांकel_pt_recording *ptr =
			container_of(itr, काष्ठा पूर्णांकel_pt_recording, itr);
	bool wrapped;
	पूर्णांक err;

	pr_debug3("%s: mmap index %d old head %zu new head %zu\n",
		  __func__, idx, (माप_प्रकार)*old, (माप_प्रकार)*head);

	err = पूर्णांकel_pt_snapshot_init(ptr, mm->len);
	अगर (err)
		जाओ out_err;

	अगर (idx >= ptr->snapshot_ref_cnt) अणु
		err = पूर्णांकel_pt_alloc_snapshot_refs(ptr, idx);
		अगर (err)
			जाओ out_err;
	पूर्ण

	अगर (ptr->snapshot_ref_buf_size) अणु
		अगर (!ptr->snapshot_refs[idx].ref_buf) अणु
			err = पूर्णांकel_pt_alloc_snapshot_ref(ptr, idx, mm->len);
			अगर (err)
				जाओ out_err;
		पूर्ण
		wrapped = पूर्णांकel_pt_wrapped(ptr, idx, mm, data, *head);
	पूर्ण अन्यथा अणु
		wrapped = ptr->snapshot_refs[idx].wrapped;
		अगर (!wrapped && पूर्णांकel_pt_first_wrap((u64 *)data, mm->len)) अणु
			ptr->snapshot_refs[idx].wrapped = true;
			wrapped = true;
		पूर्ण
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

अटल u64 पूर्णांकel_pt_reference(काष्ठा auxtrace_record *itr __maybe_unused)
अणु
	वापस rdtsc();
पूर्ण

काष्ठा auxtrace_record *पूर्णांकel_pt_recording_init(पूर्णांक *err)
अणु
	काष्ठा perf_pmu *पूर्णांकel_pt_pmu = perf_pmu__find(INTEL_PT_PMU_NAME);
	काष्ठा पूर्णांकel_pt_recording *ptr;

	अगर (!पूर्णांकel_pt_pmu)
		वापस शून्य;

	अगर (setenv("JITDUMP_USE_ARCH_TIMESTAMP", "1", 1)) अणु
		*err = -त्रुटि_सं;
		वापस शून्य;
	पूर्ण

	ptr = zalloc(माप(काष्ठा पूर्णांकel_pt_recording));
	अगर (!ptr) अणु
		*err = -ENOMEM;
		वापस शून्य;
	पूर्ण

	ptr->पूर्णांकel_pt_pmu = पूर्णांकel_pt_pmu;
	ptr->itr.pmu = पूर्णांकel_pt_pmu;
	ptr->itr.recording_options = पूर्णांकel_pt_recording_options;
	ptr->itr.info_priv_size = पूर्णांकel_pt_info_priv_size;
	ptr->itr.info_fill = पूर्णांकel_pt_info_fill;
	ptr->itr.मुक्त = पूर्णांकel_pt_recording_मुक्त;
	ptr->itr.snapshot_start = पूर्णांकel_pt_snapshot_start;
	ptr->itr.snapshot_finish = पूर्णांकel_pt_snapshot_finish;
	ptr->itr.find_snapshot = पूर्णांकel_pt_find_snapshot;
	ptr->itr.parse_snapshot_options = पूर्णांकel_pt_parse_snapshot_options;
	ptr->itr.reference = पूर्णांकel_pt_reference;
	ptr->itr.पढ़ो_finish = auxtrace_record__पढ़ो_finish;
	/*
	 * Decoding starts at a PSB packet. Minimum PSB period is 2K so 4K
	 * should give at least 1 PSB per sample.
	 */
	ptr->itr.शेष_aux_sample_size = 4096;
	वापस &ptr->itr;
पूर्ण
