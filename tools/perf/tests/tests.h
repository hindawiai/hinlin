<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TESTS_H
#घोषणा TESTS_H

#समावेश <stdbool.h>

#घोषणा TEST_ASSERT_VAL(text, cond)					 \
करो अणु									 \
	अगर (!(cond)) अणु							 \
		pr_debug("FAILED %s:%d %s\n", __खाता__, __LINE__, text); \
		वापस -1;						 \
	पूर्ण								 \
पूर्ण जबतक (0)

#घोषणा TEST_ASSERT_EQUAL(text, val, expected)				 \
करो अणु									 \
	अगर (val != expected) अणु						 \
		pr_debug("FAILED %s:%d %s (%d != %d)\n",		 \
			 __खाता__, __LINE__, text, val, expected);	 \
		वापस -1;						 \
	पूर्ण								 \
पूर्ण जबतक (0)

क्रमागत अणु
	TEST_OK   =  0,
	TEST_FAIL = -1,
	TEST_SKIP = -2,
पूर्ण;

काष्ठा test अणु
	स्थिर अक्षर *desc;
	पूर्णांक (*func)(काष्ठा test *test, पूर्णांक subtest);
	काष्ठा अणु
		bool skip_अगर_fail;
		पूर्णांक (*get_nr)(व्योम);
		स्थिर अक्षर *(*get_desc)(पूर्णांक subtest);
		स्थिर अक्षर *(*skip_reason)(पूर्णांक subtest);
	पूर्ण subtest;
	bool (*is_supported)(व्योम);
	व्योम *priv;
पूर्ण;

/* Tests */
पूर्णांक test__vmlinux_matches_kallsyms(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__खोलोat_syscall_event(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__खोलोat_syscall_event_on_all_cpus(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__basic_mmap(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__PERF_RECORD(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__perf_evsel__roundtrip_name_test(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__perf_evsel__tp_sched_test(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__syscall_खोलोat_tp_fields(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__pmu(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__pmu_events(काष्ठा test *test, पूर्णांक subtest);
स्थिर अक्षर *test__pmu_events_subtest_get_desc(पूर्णांक subtest);
स्थिर अक्षर *test__pmu_events_subtest_skip_reason(पूर्णांक subtest);
पूर्णांक test__pmu_events_subtest_get_nr(व्योम);
पूर्णांक test__attr(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__dso_data(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__dso_data_cache(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__dso_data_reखोलो(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__parse_events(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__hists_link(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__python_use(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__bp_संकेत(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__bp_संकेत_overflow(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__bp_accounting(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__wp(काष्ठा test *test, पूर्णांक subtest);
स्थिर अक्षर *test__wp_subtest_get_desc(पूर्णांक subtest);
स्थिर अक्षर *test__wp_subtest_skip_reason(पूर्णांक subtest);
पूर्णांक test__wp_subtest_get_nr(व्योम);
पूर्णांक test__task_निकास(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__mem(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__sw_घड़ी_freq(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__code_पढ़ोing(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__sample_parsing(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__keep_tracking(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__parse_no_sample_id_all(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__dwarf_unwind(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__expr(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__hists_filter(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__mmap_thपढ़ो_lookup(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__thपढ़ो_maps_share(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__hists_output(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__hists_cumulate(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__चयन_tracking(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__fdarray__filter(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__fdarray__add(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__kmod_path__parse(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__thपढ़ो_map(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__llvm(काष्ठा test *test, पूर्णांक subtest);
स्थिर अक्षर *test__llvm_subtest_get_desc(पूर्णांक subtest);
पूर्णांक test__llvm_subtest_get_nr(व्योम);
पूर्णांक test__bpf(काष्ठा test *test, पूर्णांक subtest);
स्थिर अक्षर *test__bpf_subtest_get_desc(पूर्णांक subtest);
पूर्णांक test__bpf_subtest_get_nr(व्योम);
पूर्णांक test__session_topology(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__thपढ़ो_map_synthesize(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__thपढ़ो_map_हटाओ(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__cpu_map_synthesize(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__synthesize_stat_config(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__synthesize_stat(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__synthesize_stat_round(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__event_update(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__event_बार(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__backward_ring_buffer(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__cpu_map_prपूर्णांक(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__cpu_map_merge(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__sdt_event(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__is_prपूर्णांकable_array(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__biपंचांगap_prपूर्णांक(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__perf_hooks(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__clang(काष्ठा test *test, पूर्णांक subtest);
स्थिर अक्षर *test__clang_subtest_get_desc(पूर्णांक subtest);
पूर्णांक test__clang_subtest_get_nr(व्योम);
पूर्णांक test__unit_number__scnprपूर्णांक(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__mem2node(काष्ठा test *t, पूर्णांक subtest);
पूर्णांक test__maps__merge_in(काष्ठा test *t, पूर्णांक subtest);
पूर्णांक test__समय_utils(काष्ठा test *t, पूर्णांक subtest);
पूर्णांक test__jit_ग_लिखो_elf(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__api_io(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__demangle_java(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__demangle_ocaml(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__pfm(काष्ठा test *test, पूर्णांक subtest);
स्थिर अक्षर *test__pfm_subtest_get_desc(पूर्णांक subtest);
पूर्णांक test__pfm_subtest_get_nr(व्योम);
पूर्णांक test__parse_metric(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__pe_file_parsing(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__expand_cgroup_events(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__perf_समय_प्रकारo_tsc(काष्ठा test *test, पूर्णांक subtest);

bool test__bp_संकेत_is_supported(व्योम);
bool test__bp_account_is_supported(व्योम);
bool test__wp_is_supported(व्योम);
bool test__tsc_is_supported(व्योम);

#अगर defined(__arm__) || defined(__aarch64__)
#अगर_घोषित HAVE_DWARF_UNWIND_SUPPORT
काष्ठा thपढ़ो;
काष्ठा perf_sample;
पूर्णांक test__arch_unwind_sample(काष्ठा perf_sample *sample,
			     काष्ठा thपढ़ो *thपढ़ो);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(__arm__)
पूर्णांक test__vectors_page(काष्ठा test *test, पूर्णांक subtest);
#पूर्ण_अगर

#पूर्ण_अगर /* TESTS_H */
