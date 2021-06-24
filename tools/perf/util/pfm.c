<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम libpfm4 event encoding.
 *
 * Copyright 2020 Google LLC.
 */
#समावेश "util/cpumap.h"
#समावेश "util/debug.h"
#समावेश "util/event.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/parse-events.h"
#समावेश "util/pmu.h"
#समावेश "util/pfm.h"

#समावेश <माला.स>
#समावेश <linux/kernel.h>
#समावेश <perfmon/pfmlib_perf_event.h>

अटल व्योम libpfm_initialize(व्योम)
अणु
	पूर्णांक ret;

	ret = pfm_initialize();
	अगर (ret != PFM_SUCCESS) अणु
		ui__warning("libpfm failed to initialize: %s\n",
			pfm_म_त्रुटि(ret));
	पूर्ण
पूर्ण

पूर्णांक parse_libpfm_events_option(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			पूर्णांक unset __maybe_unused)
अणु
	काष्ठा evlist *evlist = *(काष्ठा evlist **)opt->value;
	काष्ठा perf_event_attr attr;
	काष्ठा perf_pmu *pmu;
	काष्ठा evsel *evsel, *grp_leader = शून्य;
	अक्षर *p, *q, *p_orig;
	स्थिर अक्षर *sep;
	पूर्णांक grp_evt = -1;
	पूर्णांक ret;

	libpfm_initialize();

	p_orig = p = strdup(str);
	अगर (!p)
		वापस -1;
	/*
	 * क्रमce loading of the PMU list
	 */
	perf_pmu__scan(शून्य);

	क्रम (q = p; strsep(&p, ",{}"); q = p) अणु
		sep = p ? str + (p - p_orig - 1) : "";
		अगर (*sep == '{') अणु
			अगर (grp_evt > -1) अणु
				ui__error(
					"nested event groups not supported\n");
				जाओ error;
			पूर्ण
			grp_evt++;
		पूर्ण

		/* no event */
		अगर (*q == '\0') अणु
			अगर (*sep == '}') अणु
				अगर (grp_evt < 0) अणु
					ui__error("cannot close a non-existing event group\n");
					जाओ error;
				पूर्ण
				grp_evt--;
			पूर्ण
			जारी;
		पूर्ण

		स_रखो(&attr, 0, माप(attr));
		event_attr_init(&attr);

		ret = pfm_get_perf_event_encoding(q, PFM_PLM0|PFM_PLM3,
						&attr, शून्य, शून्य);

		अगर (ret != PFM_SUCCESS) अणु
			ui__error("failed to parse event %s : %s\n", str,
				  pfm_म_त्रुटि(ret));
			जाओ error;
		पूर्ण

		pmu = perf_pmu__find_by_type((अचिन्हित पूर्णांक)attr.type);
		evsel = parse_events__add_event(evlist->core.nr_entries,
						&attr, q, pmu);
		अगर (evsel == शून्य)
			जाओ error;

		evsel->is_libpfm_event = true;

		evlist__add(evlist, evsel);

		अगर (grp_evt == 0)
			grp_leader = evsel;

		अगर (grp_evt > -1) अणु
			evsel->leader = grp_leader;
			grp_leader->core.nr_members++;
			grp_evt++;
		पूर्ण

		अगर (*sep == '}') अणु
			अगर (grp_evt < 0) अणु
				ui__error(
				   "cannot close a non-existing event group\n");
				जाओ error;
			पूर्ण
			evlist->nr_groups++;
			grp_leader = शून्य;
			grp_evt = -1;
		पूर्ण
	पूर्ण
	मुक्त(p_orig);
	वापस 0;
error:
	मुक्त(p_orig);
	वापस -1;
पूर्ण

अटल स्थिर अक्षर *srcs[PFM_ATTR_CTRL_MAX] = अणु
	[PFM_ATTR_CTRL_UNKNOWN] = "???",
	[PFM_ATTR_CTRL_PMU] = "PMU",
	[PFM_ATTR_CTRL_PERF_EVENT] = "perf_event",
पूर्ण;

अटल व्योम
prपूर्णांक_attr_flags(pfm_event_attr_info_t *info)
अणु
	पूर्णांक n = 0;

	अगर (info->is_dfl) अणु
		म_लिखो("[default] ");
		n++;
	पूर्ण

	अगर (info->is_precise) अणु
		म_लिखो("[precise] ");
		n++;
	पूर्ण

	अगर (!n)
		म_लिखो("- ");
पूर्ण

अटल व्योम
prपूर्णांक_libpfm_events_detailed(pfm_event_info_t *info, bool दीर्घ_desc)
अणु
	pfm_event_attr_info_t ainfo;
	स्थिर अक्षर *src;
	पूर्णांक j, ret;

	ainfo.size = माप(ainfo);

	म_लिखो("  %s\n", info->name);
	म_लिखो("    [%s]\n", info->desc);
	अगर (दीर्घ_desc) अणु
		अगर (info->equiv)
			म_लिखो("      Equiv: %s\n", info->equiv);

		म_लिखो("      Code  : 0x%"PRIx64"\n", info->code);
	पूर्ण
	pfm_क्रम_each_event_attr(j, info) अणु
		ret = pfm_get_event_attr_info(info->idx, j,
					      PFM_OS_PERF_EVENT_EXT, &ainfo);
		अगर (ret != PFM_SUCCESS)
			जारी;

		अगर (ainfo.type == PFM_ATTR_UMASK) अणु
			म_लिखो("      %s:%s\n", info->name, ainfo.name);
			म_लिखो("        [%s]\n", ainfo.desc);
		पूर्ण

		अगर (!दीर्घ_desc)
			जारी;

		अगर (ainfo.ctrl >= PFM_ATTR_CTRL_MAX)
			ainfo.ctrl = PFM_ATTR_CTRL_UNKNOWN;

		src = srcs[ainfo.ctrl];
		चयन (ainfo.type) अणु
		हाल PFM_ATTR_UMASK:
			म_लिखो("        Umask : 0x%02"PRIx64" : %s: ",
				ainfo.code, src);
			prपूर्णांक_attr_flags(&ainfo);
			अक्षर_दो('\n');
			अवरोध;
		हाल PFM_ATTR_MOD_BOOL:
			म_लिखो("      Modif : %s: [%s] : %s (boolean)\n", src,
				ainfo.name, ainfo.desc);
			अवरोध;
		हाल PFM_ATTR_MOD_INTEGER:
			म_लिखो("      Modif : %s: [%s] : %s (integer)\n", src,
				ainfo.name, ainfo.desc);
			अवरोध;
		हाल PFM_ATTR_NONE:
		हाल PFM_ATTR_RAW_UMASK:
		हाल PFM_ATTR_MAX:
		शेष:
			म_लिखो("      Attr  : %s: [%s] : %s\n", src,
				ainfo.name, ainfo.desc);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * list all pmu::event:umask, pmu::event
 * prपूर्णांकed events may not be all valid combinations of umask क्रम an event
 */
अटल व्योम
prपूर्णांक_libpfm_events_raw(pfm_pmu_info_t *pinfo, pfm_event_info_t *info)
अणु
	pfm_event_attr_info_t ainfo;
	पूर्णांक j, ret;
	bool has_umask = false;

	ainfo.size = माप(ainfo);

	pfm_क्रम_each_event_attr(j, info) अणु
		ret = pfm_get_event_attr_info(info->idx, j,
					      PFM_OS_PERF_EVENT_EXT, &ainfo);
		अगर (ret != PFM_SUCCESS)
			जारी;

		अगर (ainfo.type != PFM_ATTR_UMASK)
			जारी;

		म_लिखो("%s::%s:%s\n", pinfo->name, info->name, ainfo.name);
		has_umask = true;
	पूर्ण
	अगर (!has_umask)
		म_लिखो("%s::%s\n", pinfo->name, info->name);
पूर्ण

व्योम prपूर्णांक_libpfm_events(bool name_only, bool दीर्घ_desc)
अणु
	pfm_event_info_t info;
	pfm_pmu_info_t pinfo;
	पूर्णांक i, p, ret;

	libpfm_initialize();

	/* initialize to zero to indicate ABI version */
	info.size  = माप(info);
	pinfo.size = माप(pinfo);

	अगर (!name_only)
		माला_दो("\nList of pre-defined events (to be used in --pfm-events):\n");

	pfm_क्रम_all_pmus(p) अणु
		bool prपूर्णांकed_pmu = false;

		ret = pfm_get_pmu_info(p, &pinfo);
		अगर (ret != PFM_SUCCESS)
			जारी;

		/* only prपूर्णांक events that are supported by host HW */
		अगर (!pinfo.is_present)
			जारी;

		/* handled by perf directly */
		अगर (pinfo.pmu == PFM_PMU_PERF_EVENT)
			जारी;

		क्रम (i = pinfo.first_event; i != -1;
		     i = pfm_get_event_next(i)) अणु

			ret = pfm_get_event_info(i, PFM_OS_PERF_EVENT_EXT,
						&info);
			अगर (ret != PFM_SUCCESS)
				जारी;

			अगर (!name_only && !prपूर्णांकed_pmu) अणु
				म_लिखो("%s:\n", pinfo.name);
				prपूर्णांकed_pmu = true;
			पूर्ण

			अगर (!name_only)
				prपूर्णांक_libpfm_events_detailed(&info, दीर्घ_desc);
			अन्यथा
				prपूर्णांक_libpfm_events_raw(&pinfo, &info);
		पूर्ण
		अगर (!name_only && prपूर्णांकed_pmu)
			अक्षर_दो('\n');
	पूर्ण
पूर्ण
