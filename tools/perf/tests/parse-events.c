<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "parse-events.h"
#समावेश "evsel.h"
#समावेश "evlist.h"
#समावेश <api/fs/fs.h>
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "pmu.h"
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <api/fs/tracing_path.h>

#घोषणा PERF_TP_SAMPLE_TYPE (PERF_SAMPLE_RAW | PERF_SAMPLE_TIME | \
			     PERF_SAMPLE_CPU | PERF_SAMPLE_PERIOD)

#अगर defined(__s390x__)
/* Return true अगर kvm module is available and loaded. Test this
 * and वापस success when trace poपूर्णांक kvm_s390_create_vm
 * exists. Otherwise this test always fails.
 */
अटल bool kvm_s390_create_vm_valid(व्योम)
अणु
	अक्षर *eventfile;
	bool rc = false;

	eventfile = get_events_file("kvm-s390");

	अगर (eventfile) अणु
		सूची *mydir = सूची_खोलो(eventfile);

		अगर (mydir) अणु
			rc = true;
			बंद_सूची(mydir);
		पूर्ण
		put_events_file(eventfile);
	पूर्ण

	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक test__checkevent_tracepoपूर्णांक(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 0 == evlist->nr_groups);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_TRACEPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong sample_type",
		PERF_TP_SAMPLE_TYPE == evsel->core.attr.sample_type);
	TEST_ASSERT_VAL("wrong sample_period", 1 == evsel->core.attr.sample_period);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_tracepoपूर्णांक_multi(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	TEST_ASSERT_VAL("wrong number of entries", evlist->core.nr_entries > 1);
	TEST_ASSERT_VAL("wrong number of groups", 0 == evlist->nr_groups);

	evlist__क्रम_each_entry(evlist, evsel) अणु
		TEST_ASSERT_VAL("wrong type",
			PERF_TYPE_TRACEPOINT == evsel->core.attr.type);
		TEST_ASSERT_VAL("wrong sample_type",
			PERF_TP_SAMPLE_TYPE == evsel->core.attr.sample_type);
		TEST_ASSERT_VAL("wrong sample_period",
			1 == evsel->core.attr.sample_period);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_raw(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x1a == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_numeric(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", 1 == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 1 == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_symbolic_name(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_INSTRUCTIONS == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_symbolic_name_config(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	/*
	 * The period value माला_लो configured within evlist__config,
	 * जबतक this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",
			0 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong config1",
			0 == evsel->core.attr.config1);
	TEST_ASSERT_VAL("wrong config2",
			1 == evsel->core.attr.config2);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_symbolic_alias(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_SOFTWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_SW_PAGE_FAULTS == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_genhw(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HW_CACHE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", (1 << 16) == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_BREAKPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong bp_type", (HW_BREAKPOINT_R | HW_BREAKPOINT_W) ==
					 evsel->core.attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len", HW_BREAKPOINT_LEN_4 ==
					evsel->core.attr.bp_len);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_x(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_BREAKPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong bp_type",
			HW_BREAKPOINT_X == evsel->core.attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len", माप(दीर्घ) == evsel->core.attr.bp_len);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_r(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type",
			PERF_TYPE_BREAKPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong bp_type",
			HW_BREAKPOINT_R == evsel->core.attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len",
			HW_BREAKPOINT_LEN_4 == evsel->core.attr.bp_len);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_w(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type",
			PERF_TYPE_BREAKPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong bp_type",
			HW_BREAKPOINT_W == evsel->core.attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len",
			HW_BREAKPOINT_LEN_4 == evsel->core.attr.bp_len);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_rw(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type",
			PERF_TYPE_BREAKPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong bp_type",
		(HW_BREAKPOINT_R|HW_BREAKPOINT_W) == evsel->core.attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len",
			HW_BREAKPOINT_LEN_4 == evsel->core.attr.bp_len);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_tracepoपूर्णांक_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	वापस test__checkevent_tracepoपूर्णांक(evlist);
पूर्ण

अटल पूर्णांक
test__checkevent_tracepoपूर्णांक_multi_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	TEST_ASSERT_VAL("wrong number of entries", evlist->core.nr_entries > 1);

	evlist__क्रम_each_entry(evlist, evsel) अणु
		TEST_ASSERT_VAL("wrong exclude_user",
				!evsel->core.attr.exclude_user);
		TEST_ASSERT_VAL("wrong exclude_kernel",
				evsel->core.attr.exclude_kernel);
		TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
		TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	पूर्ण

	वापस test__checkevent_tracepoपूर्णांक_multi(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_raw_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);

	वापस test__checkevent_raw(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_numeric_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);

	वापस test__checkevent_numeric(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_symbolic_name_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	वापस test__checkevent_symbolic_name(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_exclude_host_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);

	वापस test__checkevent_symbolic_name(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_exclude_guest_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);

	वापस test__checkevent_symbolic_name(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_symbolic_alias_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	वापस test__checkevent_symbolic_alias(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_genhw_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);

	वापस test__checkevent_genhw(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_exclude_idle_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude idle", evsel->core.attr.exclude_idle);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	वापस test__checkevent_symbolic_name(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_exclude_idle_modअगरier_1(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude idle", evsel->core.attr.exclude_idle);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	वापस test__checkevent_symbolic_name(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);


	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong name",
			!म_भेद(evsel__name(evsel), "mem:0:u"));

	वापस test__checkevent_अवरोधpoपूर्णांक(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_x_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong name",
			!म_भेद(evsel__name(evsel), "mem:0:x:k"));

	वापस test__checkevent_अवरोधpoपूर्णांक_x(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_r_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong name",
			!म_भेद(evsel__name(evsel), "mem:0:r:hp"));

	वापस test__checkevent_अवरोधpoपूर्णांक_r(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_w_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong name",
			!म_भेद(evsel__name(evsel), "mem:0:w:up"));

	वापस test__checkevent_अवरोधpoपूर्णांक_w(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_rw_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong name",
			!म_भेद(evsel__name(evsel), "mem:0:rw:kp"));

	वापस test__checkevent_अवरोधpoपूर्णांक_rw(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_pmu(काष्ठा evlist *evlist)
अणु

	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",    10 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong config1",    1 == evsel->core.attr.config1);
	TEST_ASSERT_VAL("wrong config2",    3 == evsel->core.attr.config2);
	/*
	 * The period value माला_लो configured within evlist__config,
	 * जबतक this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",     0 == evsel->core.attr.sample_period);

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_list(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 3 == evlist->core.nr_entries);

	/* r1 */
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 1 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong config1", 0 == evsel->core.attr.config1);
	TEST_ASSERT_VAL("wrong config2", 0 == evsel->core.attr.config2);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	/* syscalls:sys_enter_खोलोat:k */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_TRACEPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong sample_type",
		PERF_TP_SAMPLE_TYPE == evsel->core.attr.sample_type);
	TEST_ASSERT_VAL("wrong sample_period", 1 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	/* 1:1:hp */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", 1 == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 1 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_pmu_name(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	/* cpu/config=1,name=krava/u */
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",  1 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong name", !म_भेद(evsel__name(evsel), "krava"));

	/* cpu/config=2/u" */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",  2 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong name",
			!म_भेद(evsel__name(evsel), "cpu/config=2/u"));

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_pmu_partial_समय_callgraph(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	/* cpu/config=1,call-graph=fp,समय,period=100000/ */
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",  1 == evsel->core.attr.config);
	/*
	 * The period, समय and callgraph value माला_लो configured within evlist__config,
	 * जबतक this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",     0 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong callgraph",  !evsel__has_callchain(evsel));
	TEST_ASSERT_VAL("wrong time",  !(PERF_SAMPLE_TIME & evsel->core.attr.sample_type));

	/* cpu/config=2,call-graph=no,समय=0,period=2000/ */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",  2 == evsel->core.attr.config);
	/*
	 * The period, समय and callgraph value माला_लो configured within evlist__config,
	 * जबतक this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",     0 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong callgraph",  !evsel__has_callchain(evsel));
	TEST_ASSERT_VAL("wrong time",  !(PERF_SAMPLE_TIME & evsel->core.attr.sample_type));

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_pmu_events(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong exclude_user",
			!evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel",
			evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);
	TEST_ASSERT_VAL("wrong exclusive", !evsel->core.attr.exclusive);

	वापस 0;
पूर्ण


अटल पूर्णांक test__checkevent_pmu_events_mix(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	/* pmu-event:u */
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong exclude_user",
			!evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel",
			evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);
	TEST_ASSERT_VAL("wrong exclusive", !evsel->core.attr.exclusive);

	/* cpu/pmu-event/u*/
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong exclude_user",
			!evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel",
			evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);
	TEST_ASSERT_VAL("wrong exclusive", !evsel->core.attr.pinned);

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkterms_simple(काष्ठा list_head *terms)
अणु
	काष्ठा parse_events_term *term;

	/* config=10 */
	term = list_entry(terms->next, काष्ठा parse_events_term, list);
	TEST_ASSERT_VAL("wrong type term",
			term->type_term == PARSE_EVENTS__TERM_TYPE_CONFIG);
	TEST_ASSERT_VAL("wrong type val",
			term->type_val == PARSE_EVENTS__TERM_TYPE_NUM);
	TEST_ASSERT_VAL("wrong val", term->val.num == 10);
	TEST_ASSERT_VAL("wrong config", !term->config);

	/* config1 */
	term = list_entry(term->list.next, काष्ठा parse_events_term, list);
	TEST_ASSERT_VAL("wrong type term",
			term->type_term == PARSE_EVENTS__TERM_TYPE_CONFIG1);
	TEST_ASSERT_VAL("wrong type val",
			term->type_val == PARSE_EVENTS__TERM_TYPE_NUM);
	TEST_ASSERT_VAL("wrong val", term->val.num == 1);
	TEST_ASSERT_VAL("wrong config", !term->config);

	/* config2=3 */
	term = list_entry(term->list.next, काष्ठा parse_events_term, list);
	TEST_ASSERT_VAL("wrong type term",
			term->type_term == PARSE_EVENTS__TERM_TYPE_CONFIG2);
	TEST_ASSERT_VAL("wrong type val",
			term->type_val == PARSE_EVENTS__TERM_TYPE_NUM);
	TEST_ASSERT_VAL("wrong val", term->val.num == 3);
	TEST_ASSERT_VAL("wrong config", !term->config);

	/* umask=1*/
	term = list_entry(term->list.next, काष्ठा parse_events_term, list);
	TEST_ASSERT_VAL("wrong type term",
			term->type_term == PARSE_EVENTS__TERM_TYPE_USER);
	TEST_ASSERT_VAL("wrong type val",
			term->type_val == PARSE_EVENTS__TERM_TYPE_NUM);
	TEST_ASSERT_VAL("wrong val", term->val.num == 1);
	TEST_ASSERT_VAL("wrong config", !म_भेद(term->config, "umask"));

	/*
	 * पढ़ो
	 *
	 * The perf_pmu__test_parse_init injects 'read' term पूर्णांकo
	 * perf_pmu_events_list, so 'read' is evaluated as पढ़ो term
	 * and not as raw event with 'ead' hex value.
	 */
	term = list_entry(term->list.next, काष्ठा parse_events_term, list);
	TEST_ASSERT_VAL("wrong type term",
			term->type_term == PARSE_EVENTS__TERM_TYPE_USER);
	TEST_ASSERT_VAL("wrong type val",
			term->type_val == PARSE_EVENTS__TERM_TYPE_NUM);
	TEST_ASSERT_VAL("wrong val", term->val.num == 1);
	TEST_ASSERT_VAL("wrong config", !म_भेद(term->config, "read"));

	/*
	 * r0xead
	 *
	 * To be still able to pass 'ead' value with 'r' syntax,
	 * we added support to parse 'r0xHEX' event.
	 */
	term = list_entry(term->list.next, काष्ठा parse_events_term, list);
	TEST_ASSERT_VAL("wrong type term",
			term->type_term == PARSE_EVENTS__TERM_TYPE_CONFIG);
	TEST_ASSERT_VAL("wrong type val",
			term->type_val == PARSE_EVENTS__TERM_TYPE_NUM);
	TEST_ASSERT_VAL("wrong val", term->val.num == 0xead);
	TEST_ASSERT_VAL("wrong config", !term->config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__group1(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* inकाष्ठाions:k */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_INSTRUCTIONS == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* cycles:upp */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	/* use of precise requires exclude_guest */
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip == 2);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक test__group2(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 3 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* faults + :ku modअगरier */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_SOFTWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_SW_PAGE_FAULTS == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* cache-references + :u modअगरier */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_REFERENCES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* cycles:k */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक test__group3(काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 5 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 2 == evlist->nr_groups);

	/* group1 syscalls:sys_enter_खोलोat:H */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_TRACEPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong sample_type",
		PERF_TP_SAMPLE_TYPE == evsel->core.attr.sample_type);
	TEST_ASSERT_VAL("wrong sample_period", 1 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong group name",
		!म_भेद(leader->group_name, "group1"));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* group1 cycles:kppp */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	/* use of precise requires exclude_guest */
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip == 3);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* group2 cycles + G modअगरier */
	evsel = leader = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong group name",
		!म_भेद(leader->group_name, "group2"));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* group2 1:3 + G modअगरier */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", 1 == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 3 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* inकाष्ठाions:u */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_INSTRUCTIONS == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक test__group4(काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* cycles:u + p */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	/* use of precise requires exclude_guest */
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip == 1);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* inकाष्ठाions:kp + p */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_INSTRUCTIONS == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	/* use of precise requires exclude_guest */
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip == 2);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक test__group5(काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 5 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 2 == evlist->nr_groups);

	/* cycles + G */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* inकाष्ठाions + G */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_INSTRUCTIONS == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* cycles:G */
	evsel = leader = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);
	TEST_ASSERT_VAL("wrong sample_read", !evsel->sample_पढ़ो);

	/* inकाष्ठाions:G */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_INSTRUCTIONS == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);

	/* cycles */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));

	वापस 0;
पूर्ण

अटल पूर्णांक test__group_gh1(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* cycles + :H group modअगरier */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);

	/* cache-misses:G + :H group modअगरier */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);

	वापस 0;
पूर्ण

अटल पूर्णांक test__group_gh2(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* cycles + :G group modअगरier */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);

	/* cache-misses:H + :G group modअगरier */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);

	वापस 0;
पूर्ण

अटल पूर्णांक test__group_gh3(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* cycles:G + :u group modअगरier */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);

	/* cache-misses:H + :u group modअगरier */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);

	वापस 0;
पूर्ण

अटल पूर्णांक test__group_gh4(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* cycles:G + :uG group modअगरier */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong core.nr_members", evsel->core.nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 0);

	/* cache-misses:H + :uG group modअगरier */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", evsel__group_idx(evsel) == 1);

	वापस 0;
पूर्ण

अटल पूर्णांक test__leader_sample1(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 3 == evlist->core.nr_entries);

	/* cycles - sampling group leader */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong sample_read", evsel->sample_पढ़ो);

	/* cache-misses - not sampling */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong sample_read", evsel->sample_पढ़ो);

	/* branch-misses - not sampling */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_BRANCH_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong sample_read", evsel->sample_पढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक test__leader_sample2(काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);

	/* inकाष्ठाions - sampling group leader */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_INSTRUCTIONS == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong sample_read", evsel->sample_पढ़ो);

	/* branch-misses - not sampling */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_BRANCH_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong sample_read", evsel->sample_पढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_pinned_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", evsel->core.attr.pinned);

	वापस test__checkevent_symbolic_name(evlist);
पूर्ण

अटल पूर्णांक test__pinned_group(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 3 == evlist->core.nr_entries);

	/* cycles - group leader */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong pinned", evsel->core.attr.pinned);

	/* cache-misses - can not be pinned, but will go on with the leader */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);

	/* branch-misses - ditto */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_BRANCH_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_exclusive_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong exclusive", evsel->core.attr.exclusive);

	वापस test__checkevent_symbolic_name(evlist);
पूर्ण

अटल पूर्णांक test__exclusive_group(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 3 == evlist->core.nr_entries);

	/* cycles - group leader */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong exclusive", evsel->core.attr.exclusive);

	/* cache-misses - can not be pinned, but will go on with the leader */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclusive", !evsel->core.attr.exclusive);

	/* branch-misses - ditto */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_BRANCH_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclusive", !evsel->core.attr.exclusive);

	वापस 0;
पूर्ण
अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_len(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_BREAKPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong bp_type", (HW_BREAKPOINT_R | HW_BREAKPOINT_W) ==
					 evsel->core.attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len", HW_BREAKPOINT_LEN_1 ==
					evsel->core.attr.bp_len);

	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_अवरोधpoपूर्णांक_len_w(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_BREAKPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong bp_type", HW_BREAKPOINT_W ==
					 evsel->core.attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len", HW_BREAKPOINT_LEN_2 ==
					evsel->core.attr.bp_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
test__checkevent_अवरोधpoपूर्णांक_len_rw_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	वापस test__checkevent_अवरोधpoपूर्णांक_rw(evlist);
पूर्ण

अटल पूर्णांक test__checkevent_precise_max_modअगरier(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_SOFTWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_SW_TASK_CLOCK == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_config_symbol(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong name setting", म_भेद(evsel->name, "insn") == 0);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_config_raw(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong name setting", म_भेद(evsel->name, "rawpmu") == 0);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_config_num(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong name setting", म_भेद(evsel->name, "numpmu") == 0);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_config_cache(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong name setting", म_भेद(evsel->name, "cachepmu") == 0);
	वापस 0;
पूर्ण

अटल bool test__पूर्णांकel_pt_valid(व्योम)
अणु
	वापस !!perf_pmu__find("intel_pt");
पूर्ण

अटल पूर्णांक test__पूर्णांकel_pt(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong name setting", म_भेद(evsel->name, "intel_pt//u") == 0);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_complex_name(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong complex name parsing", म_भेद(evsel->name, "COMPLEX_CYCLES_NAME:orig=cycles,desc=chip-clock-ticks") == 0);
	वापस 0;
पूर्ण

अटल पूर्णांक test__checkevent_raw_pmu(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_SOFTWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x1a == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__sym_event_slash(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong type", evsel->core.attr.type == PERF_TYPE_HARDWARE);
	TEST_ASSERT_VAL("wrong config", evsel->core.attr.config == PERF_COUNT_HW_CPU_CYCLES);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	वापस 0;
पूर्ण

अटल पूर्णांक test__sym_event_dc(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong type", evsel->core.attr.type == PERF_TYPE_HARDWARE);
	TEST_ASSERT_VAL("wrong config", evsel->core.attr.config == PERF_COUNT_HW_CPU_CYCLES);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	वापस 0;
पूर्ण

अटल पूर्णांक count_tracepoपूर्णांकs(व्योम)
अणु
	काष्ठा dirent *events_ent;
	सूची *events_dir;
	पूर्णांक cnt = 0;

	events_dir = tracing_events__सूची_खोलो();

	TEST_ASSERT_VAL("Can't open events dir", events_dir);

	जबतक ((events_ent = सूची_पढ़ो(events_dir))) अणु
		अक्षर *sys_path;
		काष्ठा dirent *sys_ent;
		सूची *sys_dir;

		अगर (!म_भेद(events_ent->d_name, ".")
		    || !म_भेद(events_ent->d_name, "..")
		    || !म_भेद(events_ent->d_name, "enable")
		    || !म_भेद(events_ent->d_name, "header_event")
		    || !म_भेद(events_ent->d_name, "header_page"))
			जारी;

		sys_path = get_events_file(events_ent->d_name);
		TEST_ASSERT_VAL("Can't get sys path", sys_path);

		sys_dir = सूची_खोलो(sys_path);
		TEST_ASSERT_VAL("Can't open sys dir", sys_dir);

		जबतक ((sys_ent = सूची_पढ़ो(sys_dir))) अणु
			अगर (!म_भेद(sys_ent->d_name, ".")
			    || !म_भेद(sys_ent->d_name, "..")
			    || !म_भेद(sys_ent->d_name, "enable")
			    || !म_भेद(sys_ent->d_name, "filter"))
				जारी;

			cnt++;
		पूर्ण

		बंद_सूची(sys_dir);
		put_events_file(sys_path);
	पूर्ण

	बंद_सूची(events_dir);
	वापस cnt;
पूर्ण

अटल पूर्णांक test__all_tracepoपूर्णांकs(काष्ठा evlist *evlist)
अणु
	TEST_ASSERT_VAL("wrong events count",
			count_tracepoपूर्णांकs() == evlist->core.nr_entries);

	वापस test__checkevent_tracepoपूर्णांक_multi(evlist);
पूर्ण

अटल पूर्णांक test__hybrid_hw_event_with_pmu(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x3c == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__hybrid_hw_group_event(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x3c == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);

	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0xc0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	वापस 0;
पूर्ण

अटल पूर्णांक test__hybrid_sw_hw_group_event(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_SOFTWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);

	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x3c == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	वापस 0;
पूर्ण

अटल पूर्णांक test__hybrid_hw_sw_group_event(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x3c == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);

	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_SOFTWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	वापस 0;
पूर्ण

अटल पूर्णांक test__hybrid_group_modअगरier1(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *leader;

	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x3c == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);

	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0xc0 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	वापस 0;
पूर्ण

अटल पूर्णांक test__hybrid_raw1(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x1a == evsel->core.attr.config);

	/* The type of second event is अक्रमome value */
	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong config", 0x1a == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__hybrid_raw2(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x1a == evsel->core.attr.config);
	वापस 0;
पूर्ण

अटल पूर्णांक test__hybrid_cache_event(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HW_CACHE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x2 == (evsel->core.attr.config & 0xffffffff));

	evsel = evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HW_CACHE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 0x10002 == (evsel->core.attr.config & 0xffffffff));
	वापस 0;
पूर्ण

काष्ठा evlist_test अणु
	स्थिर अक्षर *name;
	__u32 type;
	स्थिर पूर्णांक id;
	bool (*valid)(व्योम);
	पूर्णांक (*check)(काष्ठा evlist *evlist);
पूर्ण;

अटल काष्ठा evlist_test test__events[] = अणु
	अणु
		.name  = "syscalls:sys_enter_openat",
		.check = test__checkevent_tracepoपूर्णांक,
		.id    = 0,
	पूर्ण,
	अणु
		.name  = "syscalls:*",
		.check = test__checkevent_tracepoपूर्णांक_multi,
		.id    = 1,
	पूर्ण,
	अणु
		.name  = "r1a",
		.check = test__checkevent_raw,
		.id    = 2,
	पूर्ण,
	अणु
		.name  = "1:1",
		.check = test__checkevent_numeric,
		.id    = 3,
	पूर्ण,
	अणु
		.name  = "instructions",
		.check = test__checkevent_symbolic_name,
		.id    = 4,
	पूर्ण,
	अणु
		.name  = "cycles/period=100000,config2/",
		.check = test__checkevent_symbolic_name_config,
		.id    = 5,
	पूर्ण,
	अणु
		.name  = "faults",
		.check = test__checkevent_symbolic_alias,
		.id    = 6,
	पूर्ण,
	अणु
		.name  = "L1-dcache-load-miss",
		.check = test__checkevent_genhw,
		.id    = 7,
	पूर्ण,
	अणु
		.name  = "mem:0",
		.check = test__checkevent_अवरोधpoपूर्णांक,
		.id    = 8,
	पूर्ण,
	अणु
		.name  = "mem:0:x",
		.check = test__checkevent_अवरोधpoपूर्णांक_x,
		.id    = 9,
	पूर्ण,
	अणु
		.name  = "mem:0:r",
		.check = test__checkevent_अवरोधpoपूर्णांक_r,
		.id    = 10,
	पूर्ण,
	अणु
		.name  = "mem:0:w",
		.check = test__checkevent_अवरोधpoपूर्णांक_w,
		.id    = 11,
	पूर्ण,
	अणु
		.name  = "syscalls:sys_enter_openat:k",
		.check = test__checkevent_tracepoपूर्णांक_modअगरier,
		.id    = 12,
	पूर्ण,
	अणु
		.name  = "syscalls:*:u",
		.check = test__checkevent_tracepoपूर्णांक_multi_modअगरier,
		.id    = 13,
	पूर्ण,
	अणु
		.name  = "r1a:kp",
		.check = test__checkevent_raw_modअगरier,
		.id    = 14,
	पूर्ण,
	अणु
		.name  = "1:1:hp",
		.check = test__checkevent_numeric_modअगरier,
		.id    = 15,
	पूर्ण,
	अणु
		.name  = "instructions:h",
		.check = test__checkevent_symbolic_name_modअगरier,
		.id    = 16,
	पूर्ण,
	अणु
		.name  = "faults:u",
		.check = test__checkevent_symbolic_alias_modअगरier,
		.id    = 17,
	पूर्ण,
	अणु
		.name  = "L1-dcache-load-miss:kp",
		.check = test__checkevent_genhw_modअगरier,
		.id    = 18,
	पूर्ण,
	अणु
		.name  = "mem:0:u",
		.check = test__checkevent_अवरोधpoपूर्णांक_modअगरier,
		.id    = 19,
	पूर्ण,
	अणु
		.name  = "mem:0:x:k",
		.check = test__checkevent_अवरोधpoपूर्णांक_x_modअगरier,
		.id    = 20,
	पूर्ण,
	अणु
		.name  = "mem:0:r:hp",
		.check = test__checkevent_अवरोधpoपूर्णांक_r_modअगरier,
		.id    = 21,
	पूर्ण,
	अणु
		.name  = "mem:0:w:up",
		.check = test__checkevent_अवरोधpoपूर्णांक_w_modअगरier,
		.id    = 22,
	पूर्ण,
	अणु
		.name  = "r1,syscalls:sys_enter_openat:k,1:1:hp",
		.check = test__checkevent_list,
		.id    = 23,
	पूर्ण,
	अणु
		.name  = "instructions:G",
		.check = test__checkevent_exclude_host_modअगरier,
		.id    = 24,
	पूर्ण,
	अणु
		.name  = "instructions:H",
		.check = test__checkevent_exclude_guest_modअगरier,
		.id    = 25,
	पूर्ण,
	अणु
		.name  = "mem:0:rw",
		.check = test__checkevent_अवरोधpoपूर्णांक_rw,
		.id    = 26,
	पूर्ण,
	अणु
		.name  = "mem:0:rw:kp",
		.check = test__checkevent_अवरोधpoपूर्णांक_rw_modअगरier,
		.id    = 27,
	पूर्ण,
	अणु
		.name  = "{instructions:k,cycles:upp}",
		.check = test__group1,
		.id    = 28,
	पूर्ण,
	अणु
		.name  = "{faults:k,cache-references}:u,cycles:k",
		.check = test__group2,
		.id    = 29,
	पूर्ण,
	अणु
		.name  = "group1{syscalls:sys_enter_openat:H,cycles:kppp},group2{cycles,1:3}:G,instructions:u",
		.check = test__group3,
		.id    = 30,
	पूर्ण,
	अणु
		.name  = "{cycles:u,instructions:kp}:p",
		.check = test__group4,
		.id    = 31,
	पूर्ण,
	अणु
		.name  = "{cycles,instructions}:G,{cycles:G,instructions:G},cycles",
		.check = test__group5,
		.id    = 32,
	पूर्ण,
	अणु
		.name  = "*:*",
		.check = test__all_tracepoपूर्णांकs,
		.id    = 33,
	पूर्ण,
	अणु
		.name  = "{cycles,cache-misses:G}:H",
		.check = test__group_gh1,
		.id    = 34,
	पूर्ण,
	अणु
		.name  = "{cycles,cache-misses:H}:G",
		.check = test__group_gh2,
		.id    = 35,
	पूर्ण,
	अणु
		.name  = "{cycles:G,cache-misses:H}:u",
		.check = test__group_gh3,
		.id    = 36,
	पूर्ण,
	अणु
		.name  = "{cycles:G,cache-misses:H}:uG",
		.check = test__group_gh4,
		.id    = 37,
	पूर्ण,
	अणु
		.name  = "{cycles,cache-misses,branch-misses}:S",
		.check = test__leader_sample1,
		.id    = 38,
	पूर्ण,
	अणु
		.name  = "{instructions,branch-misses}:Su",
		.check = test__leader_sample2,
		.id    = 39,
	पूर्ण,
	अणु
		.name  = "instructions:uDp",
		.check = test__checkevent_pinned_modअगरier,
		.id    = 40,
	पूर्ण,
	अणु
		.name  = "{cycles,cache-misses,branch-misses}:D",
		.check = test__pinned_group,
		.id    = 41,
	पूर्ण,
	अणु
		.name  = "mem:0/1",
		.check = test__checkevent_अवरोधpoपूर्णांक_len,
		.id    = 42,
	पूर्ण,
	अणु
		.name  = "mem:0/2:w",
		.check = test__checkevent_अवरोधpoपूर्णांक_len_w,
		.id    = 43,
	पूर्ण,
	अणु
		.name  = "mem:0/4:rw:u",
		.check = test__checkevent_अवरोधpoपूर्णांक_len_rw_modअगरier,
		.id    = 44
	पूर्ण,
#अगर defined(__s390x__)
	अणु
		.name  = "kvm-s390:kvm_s390_create_vm",
		.check = test__checkevent_tracepoपूर्णांक,
		.valid = kvm_s390_create_vm_valid,
		.id    = 100,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name  = "instructions:I",
		.check = test__checkevent_exclude_idle_modअगरier,
		.id    = 45,
	पूर्ण,
	अणु
		.name  = "instructions:kIG",
		.check = test__checkevent_exclude_idle_modअगरier_1,
		.id    = 46,
	पूर्ण,
	अणु
		.name  = "task-clock:P,cycles",
		.check = test__checkevent_precise_max_modअगरier,
		.id    = 47,
	पूर्ण,
	अणु
		.name  = "instructions/name=insn/",
		.check = test__checkevent_config_symbol,
		.id    = 48,
	पूर्ण,
	अणु
		.name  = "r1234/name=rawpmu/",
		.check = test__checkevent_config_raw,
		.id    = 49,
	पूर्ण,
	अणु
		.name  = "4:0x6530160/name=numpmu/",
		.check = test__checkevent_config_num,
		.id    = 50,
	पूर्ण,
	अणु
		.name  = "L1-dcache-misses/name=cachepmu/",
		.check = test__checkevent_config_cache,
		.id    = 51,
	पूर्ण,
	अणु
		.name  = "intel_pt//u",
		.valid = test__पूर्णांकel_pt_valid,
		.check = test__पूर्णांकel_pt,
		.id    = 52,
	पूर्ण,
	अणु
		.name  = "cycles/name='COMPLEX_CYCLES_NAME:orig=cycles,desc=chip-clock-ticks'/Duk",
		.check = test__checkevent_complex_name,
		.id    = 53
	पूर्ण,
	अणु
		.name  = "cycles//u",
		.check = test__sym_event_slash,
		.id    = 54,
	पूर्ण,
	अणु
		.name  = "cycles:k",
		.check = test__sym_event_dc,
		.id    = 55,
	पूर्ण,
	अणु
		.name  = "instructions:uep",
		.check = test__checkevent_exclusive_modअगरier,
		.id    = 56,
	पूर्ण,
	अणु
		.name  = "{cycles,cache-misses,branch-misses}:e",
		.check = test__exclusive_group,
		.id    = 57,
	पूर्ण,
पूर्ण;

अटल काष्ठा evlist_test test__events_pmu[] = अणु
	अणु
		.name  = "cpu/config=10,config1,config2=3,period=1000/u",
		.check = test__checkevent_pmu,
		.id    = 0,
	पूर्ण,
	अणु
		.name  = "cpu/config=1,name=krava/u,cpu/config=2/u",
		.check = test__checkevent_pmu_name,
		.id    = 1,
	पूर्ण,
	अणु
		.name  = "cpu/config=1,call-graph=fp,time,period=100000/,cpu/config=2,call-graph=no,time=0,period=2000/",
		.check = test__checkevent_pmu_partial_समय_callgraph,
		.id    = 2,
	पूर्ण,
	अणु
		.name  = "cpu/name='COMPLEX_CYCLES_NAME:orig=cycles,desc=chip-clock-ticks',period=0x1,event=0x2/ukp",
		.check = test__checkevent_complex_name,
		.id    = 3,
	पूर्ण,
	अणु
		.name  = "software/r1a/",
		.check = test__checkevent_raw_pmu,
		.id    = 4,
	पूर्ण,
	अणु
		.name  = "software/r0x1a/",
		.check = test__checkevent_raw_pmu,
		.id    = 4,
	पूर्ण,
पूर्ण;

काष्ठा terms_test अणु
	स्थिर अक्षर *str;
	__u32 type;
	पूर्णांक (*check)(काष्ठा list_head *terms);
पूर्ण;

अटल काष्ठा terms_test test__terms[] = अणु
	[0] = अणु
		.str   = "config=10,config1,config2=3,umask=1,read,r0xead",
		.check = test__checkterms_simple,
	पूर्ण,
पूर्ण;

अटल काष्ठा evlist_test test__hybrid_events[] = अणु
	अणु
		.name  = "cpu_core/cpu-cycles/",
		.check = test__hybrid_hw_event_with_pmu,
		.id    = 0,
	पूर्ण,
	अणु
		.name  = "{cpu_core/cpu-cycles/,cpu_core/instructions/}",
		.check = test__hybrid_hw_group_event,
		.id    = 1,
	पूर्ण,
	अणु
		.name  = "{cpu-clock,cpu_core/cpu-cycles/}",
		.check = test__hybrid_sw_hw_group_event,
		.id    = 2,
	पूर्ण,
	अणु
		.name  = "{cpu_core/cpu-cycles/,cpu-clock}",
		.check = test__hybrid_hw_sw_group_event,
		.id    = 3,
	पूर्ण,
	अणु
		.name  = "{cpu_core/cpu-cycles/k,cpu_core/instructions/u}",
		.check = test__hybrid_group_modअगरier1,
		.id    = 4,
	पूर्ण,
	अणु
		.name  = "r1a",
		.check = test__hybrid_raw1,
		.id    = 5,
	पूर्ण,
	अणु
		.name  = "cpu_core/r1a/",
		.check = test__hybrid_raw2,
		.id    = 6,
	पूर्ण,
	अणु
		.name  = "cpu_core/config=10,config1,config2=3,period=1000/u",
		.check = test__checkevent_pmu,
		.id    = 7,
	पूर्ण,
	अणु
		.name  = "cpu_core/LLC-loads/,cpu_atom/LLC-load-misses/",
		.check = test__hybrid_cache_event,
		.id    = 8,
	पूर्ण,
पूर्ण;

अटल पूर्णांक test_event(काष्ठा evlist_test *e)
अणु
	काष्ठा parse_events_error err;
	काष्ठा evlist *evlist;
	पूर्णांक ret;

	bzero(&err, माप(err));
	अगर (e->valid && !e->valid()) अणु
		pr_debug("... SKIP");
		वापस 0;
	पूर्ण

	evlist = evlist__new();
	अगर (evlist == शून्य)
		वापस -ENOMEM;

	ret = parse_events(evlist, e->name, &err);
	अगर (ret) अणु
		pr_debug("failed to parse event '%s', err %d, str '%s'\n",
			 e->name, ret, err.str);
		parse_events_prपूर्णांक_error(&err, e->name);
	पूर्ण अन्यथा अणु
		ret = e->check(evlist);
	पूर्ण

	evlist__delete(evlist);

	वापस ret;
पूर्ण

अटल पूर्णांक test_events(काष्ठा evlist_test *events, अचिन्हित cnt)
अणु
	पूर्णांक ret1, ret2 = 0;
	अचिन्हित i;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा evlist_test *e = &events[i];

		pr_debug("running test %d '%s'", e->id, e->name);
		ret1 = test_event(e);
		अगर (ret1)
			ret2 = ret1;
		pr_debug("\n");
	पूर्ण

	वापस ret2;
पूर्ण

अटल पूर्णांक test_term(काष्ठा terms_test *t)
अणु
	काष्ठा list_head terms;
	पूर्णांक ret;

	INIT_LIST_HEAD(&terms);

	/*
	 * The perf_pmu__test_parse_init prepares perf_pmu_events_list
	 * which माला_लो मुक्तd in parse_events_terms.
	 */
	अगर (perf_pmu__test_parse_init())
		वापस -1;

	ret = parse_events_terms(&terms, t->str);
	अगर (ret) अणु
		pr_debug("failed to parse terms '%s', err %d\n",
			 t->str , ret);
		वापस ret;
	पूर्ण

	ret = t->check(&terms);
	parse_events_terms__purge(&terms);

	वापस ret;
पूर्ण

अटल पूर्णांक test_terms(काष्ठा terms_test *terms, अचिन्हित cnt)
अणु
	पूर्णांक ret = 0;
	अचिन्हित i;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा terms_test *t = &terms[i];

		pr_debug("running test %d '%s'\n", i, t->str);
		ret = test_term(t);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक test_pmu(व्योम)
अणु
	काष्ठा stat st;
	अक्षर path[PATH_MAX];
	पूर्णांक ret;

	snम_लिखो(path, PATH_MAX, "%s/bus/event_source/devices/cpu/format/",
		 sysfs__mountpoपूर्णांक());

	ret = stat(path, &st);
	अगर (ret)
		pr_debug("omitting PMU cpu tests\n");
	वापस !ret;
पूर्ण

अटल पूर्णांक test_pmu_events(व्योम)
अणु
	काष्ठा stat st;
	अक्षर path[PATH_MAX];
	काष्ठा dirent *ent;
	सूची *dir;
	पूर्णांक ret;

	snम_लिखो(path, PATH_MAX, "%s/bus/event_source/devices/cpu/events/",
		 sysfs__mountpoपूर्णांक());

	ret = stat(path, &st);
	अगर (ret) अणु
		pr_debug("omitting PMU cpu events tests\n");
		वापस 0;
	पूर्ण

	dir = सूची_खोलो(path);
	अगर (!dir) अणु
		pr_debug("can't open pmu event dir");
		वापस -1;
	पूर्ण

	जबतक (!ret && (ent = सूची_पढ़ो(dir))) अणु
		काष्ठा evlist_test e = अणु .id = 0, पूर्ण;
		अक्षर name[2 * NAME_MAX + 1 + 12 + 3];

		/* Names containing . are special and cannot be used directly */
		अगर (म_अक्षर(ent->d_name, '.'))
			जारी;

		snम_लिखो(name, माप(name), "cpu/event=%s/u", ent->d_name);

		e.name  = name;
		e.check = test__checkevent_pmu_events;

		ret = test_event(&e);
		अगर (ret)
			अवरोध;
		snम_लिखो(name, माप(name), "%s:u,cpu/event=%s/u", ent->d_name, ent->d_name);
		e.name  = name;
		e.check = test__checkevent_pmu_events_mix;
		ret = test_event(&e);
	पूर्ण

	बंद_सूची(dir);
	वापस ret;
पूर्ण

पूर्णांक test__parse_events(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret1, ret2 = 0;

#घोषणा TEST_EVENTS(tests)				\
करो अणु							\
	ret1 = test_events(tests, ARRAY_SIZE(tests));	\
	अगर (!ret2)					\
		ret2 = ret1;				\
पूर्ण जबतक (0)

	अगर (perf_pmu__has_hybrid()) अणु
		TEST_EVENTS(test__hybrid_events);
		वापस ret2;
	पूर्ण

	TEST_EVENTS(test__events);

	अगर (test_pmu())
		TEST_EVENTS(test__events_pmu);

	अगर (test_pmu()) अणु
		पूर्णांक ret = test_pmu_events();
		अगर (ret)
			वापस ret;
	पूर्ण

	ret1 = test_terms(test__terms, ARRAY_SIZE(test__terms));
	अगर (!ret2)
		ret2 = ret1;

	वापस ret2;
पूर्ण
