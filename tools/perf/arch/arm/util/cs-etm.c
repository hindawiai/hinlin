<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <api/fs/fs.h>
#समावेश <linux/bits.h>
#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/coresight-pmu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/zभाग.स>

#समावेश "cs-etm.h"
#समावेश "../../util/debug.h"
#समावेश "../../util/record.h"
#समावेश "../../util/auxtrace.h"
#समावेश "../../util/cpumap.h"
#समावेश "../../util/event.h"
#समावेश "../../util/evlist.h"
#समावेश "../../util/evsel.h"
#समावेश "../../util/perf_api_probe.h"
#समावेश "../../util/evsel_config.h"
#समावेश "../../util/pmu.h"
#समावेश "../../util/cs-etm.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "../../util/session.h"

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <sys/स्थिति.स>

काष्ठा cs_eपंचांग_recording अणु
	काष्ठा auxtrace_record	itr;
	काष्ठा perf_pmu		*cs_eपंचांग_pmu;
	काष्ठा evlist		*evlist;
	पूर्णांक			wrapped_cnt;
	bool			*wrapped;
	bool			snapshot_mode;
	माप_प्रकार			snapshot_size;
पूर्ण;

अटल स्थिर अक्षर *metadata_eपंचांगv3_ro[CS_ETM_PRIV_MAX] = अणु
	[CS_ETM_ETMCCER]	= "mgmt/etmccer",
	[CS_ETM_ETMIDR]		= "mgmt/etmidr",
पूर्ण;

अटल स्थिर अक्षर *metadata_eपंचांगv4_ro[CS_ETMV4_PRIV_MAX] = अणु
	[CS_ETMV4_TRCIDR0]		= "trcidr/trcidr0",
	[CS_ETMV4_TRCIDR1]		= "trcidr/trcidr1",
	[CS_ETMV4_TRCIDR2]		= "trcidr/trcidr2",
	[CS_ETMV4_TRCIDR8]		= "trcidr/trcidr8",
	[CS_ETMV4_TRCAUTHSTATUS]	= "mgmt/trcauthstatus",
पूर्ण;

अटल bool cs_eपंचांग_is_eपंचांगv4(काष्ठा auxtrace_record *itr, पूर्णांक cpu);

अटल पूर्णांक cs_eपंचांग_set_context_id(काष्ठा auxtrace_record *itr,
				 काष्ठा evsel *evsel, पूर्णांक cpu)
अणु
	काष्ठा cs_eपंचांग_recording *ptr;
	काष्ठा perf_pmu *cs_eपंचांग_pmu;
	अक्षर path[PATH_MAX];
	पूर्णांक err = -EINVAL;
	u32 val;
	u64 contextid;

	ptr = container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	cs_eपंचांग_pmu = ptr->cs_eपंचांग_pmu;

	अगर (!cs_eपंचांग_is_eपंचांगv4(itr, cpu))
		जाओ out;

	/* Get a handle on TRCIRD2 */
	snम_लिखो(path, PATH_MAX, "cpu%d/%s",
		 cpu, metadata_eपंचांगv4_ro[CS_ETMV4_TRCIDR2]);
	err = perf_pmu__scan_file(cs_eपंचांग_pmu, path, "%x", &val);

	/* There was a problem पढ़ोing the file, bailing out */
	अगर (err != 1) अणु
		pr_err("%s: can't read file %s\n",
		       CORESIGHT_ETM_PMU_NAME, path);
		जाओ out;
	पूर्ण

	/* User has configured क्रम PID tracing, respects it. */
	contextid = evsel->core.attr.config &
			(BIT(ETM_OPT_CTXTID) | BIT(ETM_OPT_CTXTID2));

	/*
	 * If user करोesn't configure the contextid क्रमmat, parse PMU क्रमmat and
	 * enable PID tracing according to the "contextid" क्रमmat bits:
	 *
	 *   If bit ETM_OPT_CTXTID is set, trace CONTEXTIDR_EL1;
	 *   If bit ETM_OPT_CTXTID2 is set, trace CONTEXTIDR_EL2.
	 */
	अगर (!contextid)
		contextid = perf_pmu__क्रमmat_bits(&cs_eपंचांग_pmu->क्रमmat,
						  "contextid");

	अगर (contextid & BIT(ETM_OPT_CTXTID)) अणु
		/*
		 * TRCIDR2.CIDSIZE, bit [9-5], indicates whether contextID
		 * tracing is supported:
		 *  0b00000 Context ID tracing is not supported.
		 *  0b00100 Maximum of 32-bit Context ID size.
		 *  All other values are reserved.
		 */
		val = BMVAL(val, 5, 9);
		अगर (!val || val != 0x4) अणु
			pr_err("%s: CONTEXTIDR_EL1 isn't supported\n",
			       CORESIGHT_ETM_PMU_NAME);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (contextid & BIT(ETM_OPT_CTXTID2)) अणु
		/*
		 * TRCIDR2.VMIDOPT[30:29] != 0 and
		 * TRCIDR2.VMIDSIZE[14:10] == 0b00100 (32bit भव contextid)
		 * We can't support CONTEXTIDR in VMID अगर the size of the
		 * भव context id is < 32bit.
		 * Any value of VMIDSIZE >= 4 (i.e, > 32bit) is fine क्रम us.
		 */
		अगर (!BMVAL(val, 29, 30) || BMVAL(val, 10, 14) < 4) अणु
			pr_err("%s: CONTEXTIDR_EL2 isn't supported\n",
			       CORESIGHT_ETM_PMU_NAME);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* All good, let the kernel know */
	evsel->core.attr.config |= contextid;
	err = 0;

out:
	वापस err;
पूर्ण

अटल पूर्णांक cs_eपंचांग_set_बारtamp(काष्ठा auxtrace_record *itr,
				काष्ठा evsel *evsel, पूर्णांक cpu)
अणु
	काष्ठा cs_eपंचांग_recording *ptr;
	काष्ठा perf_pmu *cs_eपंचांग_pmu;
	अक्षर path[PATH_MAX];
	पूर्णांक err = -EINVAL;
	u32 val;

	ptr = container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	cs_eपंचांग_pmu = ptr->cs_eपंचांग_pmu;

	अगर (!cs_eपंचांग_is_eपंचांगv4(itr, cpu))
		जाओ out;

	/* Get a handle on TRCIRD0 */
	snम_लिखो(path, PATH_MAX, "cpu%d/%s",
		 cpu, metadata_eपंचांगv4_ro[CS_ETMV4_TRCIDR0]);
	err = perf_pmu__scan_file(cs_eपंचांग_pmu, path, "%x", &val);

	/* There was a problem पढ़ोing the file, bailing out */
	अगर (err != 1) अणु
		pr_err("%s: can't read file %s\n",
		       CORESIGHT_ETM_PMU_NAME, path);
		जाओ out;
	पूर्ण

	/*
	 * TRCIDR0.TSSIZE, bit [28-24], indicates whether global बारtamping
	 * is supported:
	 *  0b00000 Global बारtamping is not implemented
	 *  0b00110 Implementation supports a maximum बारtamp of 48bits.
	 *  0b01000 Implementation supports a maximum बारtamp of 64bits.
	 */
	val &= GENMASK(28, 24);
	अगर (!val) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* All good, let the kernel know */
	evsel->core.attr.config |= (1 << ETM_OPT_TS);
	err = 0;

out:
	वापस err;
पूर्ण

#घोषणा ETM_SET_OPT_CTXTID	(1 << 0)
#घोषणा ETM_SET_OPT_TS		(1 << 1)
#घोषणा ETM_SET_OPT_MASK	(ETM_SET_OPT_CTXTID | ETM_SET_OPT_TS)

अटल पूर्णांक cs_eपंचांग_set_option(काष्ठा auxtrace_record *itr,
			     काष्ठा evsel *evsel, u32 option)
अणु
	पूर्णांक i, err = -EINVAL;
	काष्ठा perf_cpu_map *event_cpus = evsel->evlist->core.cpus;
	काष्ठा perf_cpu_map *online_cpus = perf_cpu_map__new(शून्य);

	/* Set option of each CPU we have */
	क्रम (i = 0; i < cpu__max_cpu(); i++) अणु
		अगर (!cpu_map__has(event_cpus, i) ||
		    !cpu_map__has(online_cpus, i))
			जारी;

		अगर (option & BIT(ETM_OPT_CTXTID)) अणु
			err = cs_eपंचांग_set_context_id(itr, evsel, i);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर (option & BIT(ETM_OPT_TS)) अणु
			err = cs_eपंचांग_set_बारtamp(itr, evsel, i);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर (option & ~(BIT(ETM_OPT_CTXTID) | BIT(ETM_OPT_TS)))
			/* Nothing अन्यथा is currently supported */
			जाओ out;
	पूर्ण

	err = 0;
out:
	perf_cpu_map__put(online_cpus);
	वापस err;
पूर्ण

अटल पूर्णांक cs_eपंचांग_parse_snapshot_options(काष्ठा auxtrace_record *itr,
					 काष्ठा record_opts *opts,
					 स्थिर अक्षर *str)
अणु
	काष्ठा cs_eपंचांग_recording *ptr =
				container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
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

अटल पूर्णांक cs_eपंचांग_set_sink_attr(काष्ठा perf_pmu *pmu,
				काष्ठा evsel *evsel)
अणु
	अक्षर msg[बफ_मान], path[PATH_MAX], *sink;
	काष्ठा evsel_config_term *term;
	पूर्णांक ret = -EINVAL;
	u32 hash;

	अगर (evsel->core.attr.config2 & GENMASK(31, 0))
		वापस 0;

	list_क्रम_each_entry(term, &evsel->config_terms, list) अणु
		अगर (term->type != EVSEL__CONFIG_TERM_DRV_CFG)
			जारी;

		sink = term->val.str;
		snम_लिखो(path, PATH_MAX, "sinks/%s", sink);

		ret = perf_pmu__scan_file(pmu, path, "%x", &hash);
		अगर (ret != 1) अणु
			pr_err("failed to set sink \"%s\" on event %s with %d (%s)\n",
			       sink, evsel__name(evsel), त्रुटि_सं,
			       str_error_r(त्रुटि_सं, msg, माप(msg)));
			वापस ret;
		पूर्ण

		evsel->core.attr.config2 |= hash;
		वापस 0;
	पूर्ण

	/*
	 * No sink was provided on the command line - allow the CoreSight
	 * प्रणाली to look क्रम a शेष
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग_recording_options(काष्ठा auxtrace_record *itr,
				    काष्ठा evlist *evlist,
				    काष्ठा record_opts *opts)
अणु
	पूर्णांक ret;
	काष्ठा cs_eपंचांग_recording *ptr =
				container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	काष्ठा perf_pmu *cs_eपंचांग_pmu = ptr->cs_eपंचांग_pmu;
	काष्ठा evsel *evsel, *cs_eपंचांग_evsel = शून्य;
	काष्ठा perf_cpu_map *cpus = evlist->core.cpus;
	bool privileged = perf_event_paranoid_check(-1);
	पूर्णांक err = 0;

	ptr->evlist = evlist;
	ptr->snapshot_mode = opts->auxtrace_snapshot_mode;

	अगर (!record_opts__no_चयन_events(opts) &&
	    perf_can_record_चयन_events())
		opts->record_चयन_events = true;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == cs_eपंचांग_pmu->type) अणु
			अगर (cs_eपंचांग_evsel) अणु
				pr_err("There may be only one %s event\n",
				       CORESIGHT_ETM_PMU_NAME);
				वापस -EINVAL;
			पूर्ण
			evsel->core.attr.freq = 0;
			evsel->core.attr.sample_period = 1;
			cs_eपंचांग_evsel = evsel;
			opts->full_auxtrace = true;
		पूर्ण
	पूर्ण

	/* no need to जारी अगर at least one event of पूर्णांकerest was found */
	अगर (!cs_eपंचांग_evsel)
		वापस 0;

	ret = cs_eपंचांग_set_sink_attr(cs_eपंचांग_pmu, cs_eपंचांग_evsel);
	अगर (ret)
		वापस ret;

	अगर (opts->use_घड़ीid) अणु
		pr_err("Cannot use clockid (-k option) with %s\n",
		       CORESIGHT_ETM_PMU_NAME);
		वापस -EINVAL;
	पूर्ण

	/* we are in snapshot mode */
	अगर (opts->auxtrace_snapshot_mode) अणु
		/*
		 * No size were given to '-S' or '-m,', so go with
		 * the शेष
		 */
		अगर (!opts->auxtrace_snapshot_size &&
		    !opts->auxtrace_mmap_pages) अणु
			अगर (privileged) अणु
				opts->auxtrace_mmap_pages = MiB(4) / page_size;
			पूर्ण अन्यथा अणु
				opts->auxtrace_mmap_pages =
							KiB(128) / page_size;
				अगर (opts->mmap_pages == अच_पूर्णांक_उच्च)
					opts->mmap_pages = KiB(256) / page_size;
			पूर्ण
		पूर्ण अन्यथा अगर (!opts->auxtrace_mmap_pages && !privileged &&
						opts->mmap_pages == अच_पूर्णांक_उच्च) अणु
			opts->mmap_pages = KiB(256) / page_size;
		पूर्ण

		/*
		 * '-m,xyz' was specअगरied but no snapshot size, so make the
		 * snapshot size as big as the auxtrace mmap area.
		 */
		अगर (!opts->auxtrace_snapshot_size) अणु
			opts->auxtrace_snapshot_size =
				opts->auxtrace_mmap_pages * (माप_प्रकार)page_size;
		पूर्ण

		/*
		 * -Sxyz was specअगरied but no auxtrace mmap area, so make the
		 * auxtrace mmap area big enough to fit the requested snapshot
		 * size.
		 */
		अगर (!opts->auxtrace_mmap_pages) अणु
			माप_प्रकार sz = opts->auxtrace_snapshot_size;

			sz = round_up(sz, page_size) / page_size;
			opts->auxtrace_mmap_pages = roundup_घात_of_two(sz);
		पूर्ण

		/* Snapshot size can't be bigger than the auxtrace area */
		अगर (opts->auxtrace_snapshot_size >
				opts->auxtrace_mmap_pages * (माप_प्रकार)page_size) अणु
			pr_err("Snapshot size %zu must not be greater than AUX area tracing mmap size %zu\n",
			       opts->auxtrace_snapshot_size,
			       opts->auxtrace_mmap_pages * (माप_प्रकार)page_size);
			वापस -EINVAL;
		पूर्ण

		/* Something went wrong somewhere - this shouldn't happen */
		अगर (!opts->auxtrace_snapshot_size ||
		    !opts->auxtrace_mmap_pages) अणु
			pr_err("Failed to calculate default snapshot size and/or AUX area tracing mmap pages\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

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

	/* Validate auxtrace_mmap_pages provided by user */
	अगर (opts->auxtrace_mmap_pages) अणु
		अचिन्हित पूर्णांक max_page = (KiB(128) / page_size);
		माप_प्रकार sz = opts->auxtrace_mmap_pages * (माप_प्रकार)page_size;

		अगर (!privileged &&
		    opts->auxtrace_mmap_pages > max_page) अणु
			opts->auxtrace_mmap_pages = max_page;
			pr_err("auxtrace too big, truncating to %d\n",
			       max_page);
		पूर्ण

		अगर (!is_घातer_of_2(sz)) अणु
			pr_err("Invalid mmap size for %s: must be a power of 2\n",
			       CORESIGHT_ETM_PMU_NAME);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (opts->auxtrace_snapshot_mode)
		pr_debug2("%s snapshot size: %zu\n", CORESIGHT_ETM_PMU_NAME,
			  opts->auxtrace_snapshot_size);

	/*
	 * To obtain the auxtrace buffer file descriptor, the auxtrace
	 * event must come first.
	 */
	evlist__to_front(evlist, cs_eपंचांग_evsel);

	/*
	 * In the हाल of per-cpu mmaps, we need the CPU on the
	 * AUX event.  We also need the contextID in order to be notअगरied
	 * when a context चयन happened.
	 */
	अगर (!perf_cpu_map__empty(cpus)) अणु
		evsel__set_sample_bit(cs_eपंचांग_evsel, CPU);

		err = cs_eपंचांग_set_option(itr, cs_eपंचांग_evsel,
					BIT(ETM_OPT_CTXTID) | BIT(ETM_OPT_TS));
		अगर (err)
			जाओ out;
	पूर्ण

	/* Add dummy event to keep tracking */
	अगर (opts->full_auxtrace) अणु
		काष्ठा evsel *tracking_evsel;

		err = parse_events(evlist, "dummy:u", शून्य);
		अगर (err)
			जाओ out;

		tracking_evsel = evlist__last(evlist);
		evlist__set_tracking_event(evlist, tracking_evsel);

		tracking_evsel->core.attr.freq = 0;
		tracking_evsel->core.attr.sample_period = 1;

		/* In per-cpu हाल, always need the समय of mmap events etc */
		अगर (!perf_cpu_map__empty(cpus))
			evsel__set_sample_bit(tracking_evsel, TIME);
	पूर्ण

out:
	वापस err;
पूर्ण

अटल u64 cs_eपंचांग_get_config(काष्ठा auxtrace_record *itr)
अणु
	u64 config = 0;
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	काष्ठा perf_pmu *cs_eपंचांग_pmu = ptr->cs_eपंचांग_pmu;
	काष्ठा evlist *evlist = ptr->evlist;
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == cs_eपंचांग_pmu->type) अणु
			/*
			 * Variable perf_event_attr::config is asचिन्हित to
			 * ETMv3/PTM.  The bit fields have been made to match
			 * the ETMv3.5 ETRMCR रेजिस्टर specअगरication.  See the
			 * PMU_FORMAT_ATTR() declarations in
			 * drivers/hwtracing/coresight/coresight-perf.c क्रम
			 * details.
			 */
			config = evsel->core.attr.config;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस config;
पूर्ण

#अगर_अघोषित BIT
#घोषणा BIT(N) (1UL << (N))
#पूर्ण_अगर

अटल u64 cs_eपंचांगv4_get_config(काष्ठा auxtrace_record *itr)
अणु
	u64 config = 0;
	u64 config_opts = 0;

	/*
	 * The perf event variable config bits represent both
	 * the command line options and रेजिस्टर programming
	 * bits in ETMv3/PTM. For ETMv4 we must remap options
	 * to real bits
	 */
	config_opts = cs_eपंचांग_get_config(itr);
	अगर (config_opts & BIT(ETM_OPT_CYCACC))
		config |= BIT(ETM4_CFG_BIT_CYCACC);
	अगर (config_opts & BIT(ETM_OPT_CTXTID))
		config |= BIT(ETM4_CFG_BIT_CTXTID);
	अगर (config_opts & BIT(ETM_OPT_TS))
		config |= BIT(ETM4_CFG_BIT_TS);
	अगर (config_opts & BIT(ETM_OPT_RETSTK))
		config |= BIT(ETM4_CFG_BIT_RETSTK);
	अगर (config_opts & BIT(ETM_OPT_CTXTID2))
		config |= BIT(ETM4_CFG_BIT_VMID) |
			  BIT(ETM4_CFG_BIT_VMID_OPT);
	वापस config;
पूर्ण

अटल माप_प्रकार
cs_eपंचांग_info_priv_size(काष्ठा auxtrace_record *itr __maybe_unused,
		      काष्ठा evlist *evlist __maybe_unused)
अणु
	पूर्णांक i;
	पूर्णांक eपंचांगv3 = 0, eपंचांगv4 = 0;
	काष्ठा perf_cpu_map *event_cpus = evlist->core.cpus;
	काष्ठा perf_cpu_map *online_cpus = perf_cpu_map__new(शून्य);

	/* cpu map is not empty, we have specअगरic CPUs to work with */
	अगर (!perf_cpu_map__empty(event_cpus)) अणु
		क्रम (i = 0; i < cpu__max_cpu(); i++) अणु
			अगर (!cpu_map__has(event_cpus, i) ||
			    !cpu_map__has(online_cpus, i))
				जारी;

			अगर (cs_eपंचांग_is_eपंचांगv4(itr, i))
				eपंचांगv4++;
			अन्यथा
				eपंचांगv3++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* get configuration क्रम all CPUs in the प्रणाली */
		क्रम (i = 0; i < cpu__max_cpu(); i++) अणु
			अगर (!cpu_map__has(online_cpus, i))
				जारी;

			अगर (cs_eपंचांग_is_eपंचांगv4(itr, i))
				eपंचांगv4++;
			अन्यथा
				eपंचांगv3++;
		पूर्ण
	पूर्ण

	perf_cpu_map__put(online_cpus);

	वापस (CS_ETM_HEADER_SIZE +
	       (eपंचांगv4 * CS_ETMV4_PRIV_SIZE) +
	       (eपंचांगv3 * CS_ETMV3_PRIV_SIZE));
पूर्ण

अटल bool cs_eपंचांग_is_eपंचांगv4(काष्ठा auxtrace_record *itr, पूर्णांक cpu)
अणु
	bool ret = false;
	अक्षर path[PATH_MAX];
	पूर्णांक scan;
	अचिन्हित पूर्णांक val;
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	काष्ठा perf_pmu *cs_eपंचांग_pmu = ptr->cs_eपंचांग_pmu;

	/* Take any of the RO files क्रम ETMv4 and see अगर it present */
	snम_लिखो(path, PATH_MAX, "cpu%d/%s",
		 cpu, metadata_eपंचांगv4_ro[CS_ETMV4_TRCIDR0]);
	scan = perf_pmu__scan_file(cs_eपंचांग_pmu, path, "%x", &val);

	/* The file was पढ़ो successfully, we have a winner */
	अगर (scan == 1)
		ret = true;

	वापस ret;
पूर्ण

अटल पूर्णांक cs_eपंचांग_get_ro(काष्ठा perf_pmu *pmu, पूर्णांक cpu, स्थिर अक्षर *path)
अणु
	अक्षर pmu_path[PATH_MAX];
	पूर्णांक scan;
	अचिन्हित पूर्णांक val = 0;

	/* Get RO metadata from sysfs */
	snम_लिखो(pmu_path, PATH_MAX, "cpu%d/%s", cpu, path);

	scan = perf_pmu__scan_file(pmu, pmu_path, "%x", &val);
	अगर (scan != 1)
		pr_err("%s: error reading: %s\n", __func__, pmu_path);

	वापस val;
पूर्ण

अटल व्योम cs_eपंचांग_get_metadata(पूर्णांक cpu, u32 *offset,
				काष्ठा auxtrace_record *itr,
				काष्ठा perf_record_auxtrace_info *info)
अणु
	u32 increment, nr_trc_params;
	u64 magic;
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	काष्ठा perf_pmu *cs_eपंचांग_pmu = ptr->cs_eपंचांग_pmu;

	/* first see what kind of tracer this cpu is affined to */
	अगर (cs_eपंचांग_is_eपंचांगv4(itr, cpu)) अणु
		magic = __perf_cs_eपंचांगv4_magic;
		/* Get trace configuration रेजिस्टर */
		info->priv[*offset + CS_ETMV4_TRCCONFIGR] =
						cs_eपंचांगv4_get_config(itr);
		/* Get traceID from the framework */
		info->priv[*offset + CS_ETMV4_TRCTRACEIDR] =
						coresight_get_trace_id(cpu);
		/* Get पढ़ो-only inक्रमmation from sysFS */
		info->priv[*offset + CS_ETMV4_TRCIDR0] =
			cs_eपंचांग_get_ro(cs_eपंचांग_pmu, cpu,
				      metadata_eपंचांगv4_ro[CS_ETMV4_TRCIDR0]);
		info->priv[*offset + CS_ETMV4_TRCIDR1] =
			cs_eपंचांग_get_ro(cs_eपंचांग_pmu, cpu,
				      metadata_eपंचांगv4_ro[CS_ETMV4_TRCIDR1]);
		info->priv[*offset + CS_ETMV4_TRCIDR2] =
			cs_eपंचांग_get_ro(cs_eपंचांग_pmu, cpu,
				      metadata_eपंचांगv4_ro[CS_ETMV4_TRCIDR2]);
		info->priv[*offset + CS_ETMV4_TRCIDR8] =
			cs_eपंचांग_get_ro(cs_eपंचांग_pmu, cpu,
				      metadata_eपंचांगv4_ro[CS_ETMV4_TRCIDR8]);
		info->priv[*offset + CS_ETMV4_TRCAUTHSTATUS] =
			cs_eपंचांग_get_ro(cs_eपंचांग_pmu, cpu,
				      metadata_eपंचांगv4_ro
				      [CS_ETMV4_TRCAUTHSTATUS]);

		/* How much space was used */
		increment = CS_ETMV4_PRIV_MAX;
		nr_trc_params = CS_ETMV4_PRIV_MAX - CS_ETMV4_TRCCONFIGR;
	पूर्ण अन्यथा अणु
		magic = __perf_cs_eपंचांगv3_magic;
		/* Get configuration रेजिस्टर */
		info->priv[*offset + CS_ETM_ETMCR] = cs_eपंचांग_get_config(itr);
		/* Get traceID from the framework */
		info->priv[*offset + CS_ETM_ETMTRACEIDR] =
						coresight_get_trace_id(cpu);
		/* Get पढ़ो-only inक्रमmation from sysFS */
		info->priv[*offset + CS_ETM_ETMCCER] =
			cs_eपंचांग_get_ro(cs_eपंचांग_pmu, cpu,
				      metadata_eपंचांगv3_ro[CS_ETM_ETMCCER]);
		info->priv[*offset + CS_ETM_ETMIDR] =
			cs_eपंचांग_get_ro(cs_eपंचांग_pmu, cpu,
				      metadata_eपंचांगv3_ro[CS_ETM_ETMIDR]);

		/* How much space was used */
		increment = CS_ETM_PRIV_MAX;
		nr_trc_params = CS_ETM_PRIV_MAX - CS_ETM_ETMCR;
	पूर्ण

	/* Build generic header portion */
	info->priv[*offset + CS_ETM_MAGIC] = magic;
	info->priv[*offset + CS_ETM_CPU] = cpu;
	info->priv[*offset + CS_ETM_NR_TRC_PARAMS] = nr_trc_params;
	/* Where the next CPU entry should start from */
	*offset += increment;
पूर्ण

अटल पूर्णांक cs_eपंचांग_info_fill(काष्ठा auxtrace_record *itr,
			    काष्ठा perf_session *session,
			    काष्ठा perf_record_auxtrace_info *info,
			    माप_प्रकार priv_size)
अणु
	पूर्णांक i;
	u32 offset;
	u64 nr_cpu, type;
	काष्ठा perf_cpu_map *cpu_map;
	काष्ठा perf_cpu_map *event_cpus = session->evlist->core.cpus;
	काष्ठा perf_cpu_map *online_cpus = perf_cpu_map__new(शून्य);
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	काष्ठा perf_pmu *cs_eपंचांग_pmu = ptr->cs_eपंचांग_pmu;

	अगर (priv_size != cs_eपंचांग_info_priv_size(itr, session->evlist))
		वापस -EINVAL;

	अगर (!session->evlist->core.nr_mmaps)
		वापस -EINVAL;

	/* If the cpu_map is empty all online CPUs are involved */
	अगर (perf_cpu_map__empty(event_cpus)) अणु
		cpu_map = online_cpus;
	पूर्ण अन्यथा अणु
		/* Make sure all specअगरied CPUs are online */
		क्रम (i = 0; i < perf_cpu_map__nr(event_cpus); i++) अणु
			अगर (cpu_map__has(event_cpus, i) &&
			    !cpu_map__has(online_cpus, i))
				वापस -EINVAL;
		पूर्ण

		cpu_map = event_cpus;
	पूर्ण

	nr_cpu = perf_cpu_map__nr(cpu_map);
	/* Get PMU type as dynamically asचिन्हित by the core */
	type = cs_eपंचांग_pmu->type;

	/* First fill out the session header */
	info->type = PERF_AUXTRACE_CS_ETM;
	info->priv[CS_HEADER_VERSION] = CS_HEADER_CURRENT_VERSION;
	info->priv[CS_PMU_TYPE_CPUS] = type << 32;
	info->priv[CS_PMU_TYPE_CPUS] |= nr_cpu;
	info->priv[CS_ETM_SNAPSHOT] = ptr->snapshot_mode;

	offset = CS_ETM_SNAPSHOT + 1;

	क्रम (i = 0; i < cpu__max_cpu() && offset < priv_size; i++)
		अगर (cpu_map__has(cpu_map, i))
			cs_eपंचांग_get_metadata(i, &offset, itr, info);

	perf_cpu_map__put(online_cpus);

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग_alloc_wrapped_array(काष्ठा cs_eपंचांग_recording *ptr, पूर्णांक idx)
अणु
	bool *wrapped;
	पूर्णांक cnt = ptr->wrapped_cnt;

	/* Make @ptr->wrapped as big as @idx */
	जबतक (cnt <= idx)
		cnt++;

	/*
	 * Free'ed in cs_eपंचांग_recording_मुक्त().  Using पुनः_स्मृति() to aव्योम
	 * cross compilation problems where the host's प्रणाली supports
	 * पुनः_स्मृतिarray() but not the target.
	 */
	wrapped = पुनः_स्मृति(ptr->wrapped, cnt * माप(bool));
	अगर (!wrapped)
		वापस -ENOMEM;

	wrapped[cnt - 1] = false;
	ptr->wrapped_cnt = cnt;
	ptr->wrapped = wrapped;

	वापस 0;
पूर्ण

अटल bool cs_eपंचांग_buffer_has_wrapped(अचिन्हित अक्षर *buffer,
				      माप_प्रकार buffer_size, u64 head)
अणु
	u64 i, watermark;
	u64 *buf = (u64 *)buffer;
	माप_प्रकार buf_size = buffer_size;

	/*
	 * We want to look the very last 512 byte (chosen arbitrarily) in
	 * the ring buffer.
	 */
	watermark = buf_size - 512;

	/*
	 * @head is continuously increasing - अगर its value is equal or greater
	 * than the size of the ring buffer, it has wrapped around.
	 */
	अगर (head >= buffer_size)
		वापस true;

	/*
	 * The value of @head is somewhere within the size of the ring buffer.
	 * This can be that there hasn't been enough data to fill the ring
	 * buffer yet or the trace समय was so दीर्घ that @head has numerically
	 * wrapped around.  To find we need to check अगर we have data at the very
	 * end of the ring buffer.  We can reliably करो this because mmap'ed
	 * pages are zeroed out and there is a fresh mapping with every new
	 * session.
	 */

	/* @head is less than 512 byte from the end of the ring buffer */
	अगर (head > watermark)
		watermark = head;

	/*
	 * Speed things up by using 64 bit transactions (see "u64 *buf" above)
	 */
	watermark >>= 3;
	buf_size >>= 3;

	/*
	 * If we find trace data at the end of the ring buffer, @head has
	 * been there and has numerically wrapped around at least once.
	 */
	क्रम (i = watermark; i < buf_size; i++)
		अगर (buf[i])
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक cs_eपंचांग_find_snapshot(काष्ठा auxtrace_record *itr,
				पूर्णांक idx, काष्ठा auxtrace_mmap *mm,
				अचिन्हित अक्षर *data,
				u64 *head, u64 *old)
अणु
	पूर्णांक err;
	bool wrapped;
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);

	/*
	 * Allocate memory to keep track of wrapping अगर this is the first
	 * समय we deal with this *mm.
	 */
	अगर (idx >= ptr->wrapped_cnt) अणु
		err = cs_eपंचांग_alloc_wrapped_array(ptr, idx);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Check to see अगर *head has wrapped around.  If it hasn't only the
	 * amount of data between *head and *old is snapshot'ed to aव्योम
	 * bloating the perf.data file with zeros.  But as soon as *head has
	 * wrapped around the entire size of the AUX ring buffer it taken.
	 */
	wrapped = ptr->wrapped[idx];
	अगर (!wrapped && cs_eपंचांग_buffer_has_wrapped(data, mm->len, *head)) अणु
		wrapped = true;
		ptr->wrapped[idx] = true;
	पूर्ण

	pr_debug3("%s: mmap index %d old head %zu new head %zu size %zu\n",
		  __func__, idx, (माप_प्रकार)*old, (माप_प्रकार)*head, mm->len);

	/* No wrap has occurred, we can just use *head and *old. */
	अगर (!wrapped)
		वापस 0;

	/*
	 * *head has wrapped around - adjust *head and *old to pickup the
	 * entire content of the AUX buffer.
	 */
	अगर (*head >= mm->len) अणु
		*old = *head - mm->len;
	पूर्ण अन्यथा अणु
		*head += mm->len;
		*old = *head - mm->len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग_snapshot_start(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(ptr->evlist, evsel) अणु
		अगर (evsel->core.attr.type == ptr->cs_eपंचांग_pmu->type)
			वापस evsel__disable(evsel);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs_eपंचांग_snapshot_finish(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(ptr->evlist, evsel) अणु
		अगर (evsel->core.attr.type == ptr->cs_eपंचांग_pmu->type)
			वापस evsel__enable(evsel);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल u64 cs_eपंचांग_reference(काष्ठा auxtrace_record *itr __maybe_unused)
अणु
	वापस (((u64) अक्रम() <<  0) & 0x00000000FFFFFFFFull) |
		(((u64) अक्रम() << 32) & 0xFFFFFFFF00000000ull);
पूर्ण

अटल व्योम cs_eपंचांग_recording_मुक्त(काष्ठा auxtrace_record *itr)
अणु
	काष्ठा cs_eपंचांग_recording *ptr =
			container_of(itr, काष्ठा cs_eपंचांग_recording, itr);

	zमुक्त(&ptr->wrapped);
	मुक्त(ptr);
पूर्ण

काष्ठा auxtrace_record *cs_eपंचांग_record_init(पूर्णांक *err)
अणु
	काष्ठा perf_pmu *cs_eपंचांग_pmu;
	काष्ठा cs_eपंचांग_recording *ptr;

	cs_eपंचांग_pmu = perf_pmu__find(CORESIGHT_ETM_PMU_NAME);

	अगर (!cs_eपंचांग_pmu) अणु
		*err = -EINVAL;
		जाओ out;
	पूर्ण

	ptr = zalloc(माप(काष्ठा cs_eपंचांग_recording));
	अगर (!ptr) अणु
		*err = -ENOMEM;
		जाओ out;
	पूर्ण

	ptr->cs_eपंचांग_pmu			= cs_eपंचांग_pmu;
	ptr->itr.pmu			= cs_eपंचांग_pmu;
	ptr->itr.parse_snapshot_options	= cs_eपंचांग_parse_snapshot_options;
	ptr->itr.recording_options	= cs_eपंचांग_recording_options;
	ptr->itr.info_priv_size		= cs_eपंचांग_info_priv_size;
	ptr->itr.info_fill		= cs_eपंचांग_info_fill;
	ptr->itr.find_snapshot		= cs_eपंचांग_find_snapshot;
	ptr->itr.snapshot_start		= cs_eपंचांग_snapshot_start;
	ptr->itr.snapshot_finish	= cs_eपंचांग_snapshot_finish;
	ptr->itr.reference		= cs_eपंचांग_reference;
	ptr->itr.मुक्त			= cs_eपंचांग_recording_मुक्त;
	ptr->itr.पढ़ो_finish		= auxtrace_record__पढ़ो_finish;

	*err = 0;
	वापस &ptr->itr;
out:
	वापस शून्य;
पूर्ण
