<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "tests.h"
#समावेश "debug.h"

#अगर_घोषित HAVE_LIBBPF_SUPPORT
#समावेश <bpf/libbpf.h>
#समावेश <util/llvm-utils.h>
#समावेश "llvm.h"
अटल पूर्णांक test__bpf_parsing(व्योम *obj_buf, माप_प्रकार obj_buf_sz)
अणु
	काष्ठा bpf_object *obj;

	obj = bpf_object__खोलो_buffer(obj_buf, obj_buf_sz, शून्य);
	अगर (libbpf_get_error(obj))
		वापस TEST_FAIL;
	bpf_object__बंद(obj);
	वापस TEST_OK;
पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर *source;
	स्थिर अक्षर *desc;
	bool should_load_fail;
पूर्ण bpf_source_table[__LLVM_TESTCASE_MAX] = अणु
	[LLVM_TESTCASE_BASE] = अणु
		.source = test_llvm__bpf_base_prog,
		.desc = "Basic BPF llvm compile",
	पूर्ण,
	[LLVM_TESTCASE_KBUILD] = अणु
		.source = test_llvm__bpf_test_kbuild_prog,
		.desc = "kbuild searching",
	पूर्ण,
	[LLVM_TESTCASE_BPF_PROLOGUE] = अणु
		.source = test_llvm__bpf_test_prologue_prog,
		.desc = "Compile source for BPF prologue generation",
	पूर्ण,
	[LLVM_TESTCASE_BPF_RELOCATION] = अणु
		.source = test_llvm__bpf_test_relocation,
		.desc = "Compile source for BPF relocation",
		.should_load_fail = true,
	पूर्ण,
पूर्ण;

पूर्णांक
test_llvm__fetch_bpf_obj(व्योम **p_obj_buf,
			 माप_प्रकार *p_obj_buf_sz,
			 क्रमागत test_llvm__testहाल idx,
			 bool क्रमce,
			 bool *should_load_fail)
अणु
	स्थिर अक्षर *source;
	स्थिर अक्षर *desc;
	स्थिर अक्षर *पंचांगpl_old, *clang_opt_old;
	अक्षर *पंचांगpl_new = शून्य, *clang_opt_new = शून्य;
	पूर्णांक err, old_verbose, ret = TEST_FAIL;

	अगर (idx >= __LLVM_TESTCASE_MAX)
		वापस TEST_FAIL;

	source = bpf_source_table[idx].source;
	desc = bpf_source_table[idx].desc;
	अगर (should_load_fail)
		*should_load_fail = bpf_source_table[idx].should_load_fail;

	/*
	 * Skip this test अगर user's .perfconfig doesn't set [llvm] section
	 * and clang is not found in $PATH, and this is not perf test -v
	 */
	अगर (!क्रमce && (verbose <= 0 &&
		       !llvm_param.user_set_param &&
		       llvm__search_clang())) अणु
		pr_debug("No clang and no verbosive, skip this test\n");
		वापस TEST_SKIP;
	पूर्ण

	/*
	 * llvm is verbosity when error. Suppress all error output अगर
	 * not 'perf test -v'.
	 */
	old_verbose = verbose;
	अगर (verbose == 0)
		verbose = -1;

	*p_obj_buf = शून्य;
	*p_obj_buf_sz = 0;

	अगर (!llvm_param.clang_bpf_cmd_ढाँचा)
		जाओ out;

	अगर (!llvm_param.clang_opt)
		llvm_param.clang_opt = strdup("");

	err = aप्र_लिखो(&पंचांगpl_new, "echo '%s' | %s%s", source,
		       llvm_param.clang_bpf_cmd_ढाँचा,
		       old_verbose ? "" : " 2>/dev/null");
	अगर (err < 0)
		जाओ out;
	err = aप्र_लिखो(&clang_opt_new, "-xc %s", llvm_param.clang_opt);
	अगर (err < 0)
		जाओ out;

	पंचांगpl_old = llvm_param.clang_bpf_cmd_ढाँचा;
	llvm_param.clang_bpf_cmd_ढाँचा = पंचांगpl_new;
	clang_opt_old = llvm_param.clang_opt;
	llvm_param.clang_opt = clang_opt_new;

	err = llvm__compile_bpf("-", p_obj_buf, p_obj_buf_sz);

	llvm_param.clang_bpf_cmd_ढाँचा = पंचांगpl_old;
	llvm_param.clang_opt = clang_opt_old;

	verbose = old_verbose;
	अगर (err)
		जाओ out;

	ret = TEST_OK;
out:
	मुक्त(पंचांगpl_new);
	मुक्त(clang_opt_new);
	अगर (ret != TEST_OK)
		pr_debug("Failed to compile test case: '%s'\n", desc);
	वापस ret;
पूर्ण

पूर्णांक test__llvm(काष्ठा test *test __maybe_unused, पूर्णांक subtest)
अणु
	पूर्णांक ret;
	व्योम *obj_buf = शून्य;
	माप_प्रकार obj_buf_sz = 0;
	bool should_load_fail = false;

	अगर ((subtest < 0) || (subtest >= __LLVM_TESTCASE_MAX))
		वापस TEST_FAIL;

	ret = test_llvm__fetch_bpf_obj(&obj_buf, &obj_buf_sz,
				       subtest, false, &should_load_fail);

	अगर (ret == TEST_OK && !should_load_fail) अणु
		ret = test__bpf_parsing(obj_buf, obj_buf_sz);
		अगर (ret != TEST_OK) अणु
			pr_debug("Failed to parse test case '%s'\n",
				 bpf_source_table[subtest].desc);
		पूर्ण
	पूर्ण
	मुक्त(obj_buf);

	वापस ret;
पूर्ण

पूर्णांक test__llvm_subtest_get_nr(व्योम)
अणु
	वापस __LLVM_TESTCASE_MAX;
पूर्ण

स्थिर अक्षर *test__llvm_subtest_get_desc(पूर्णांक subtest)
अणु
	अगर ((subtest < 0) || (subtest >= __LLVM_TESTCASE_MAX))
		वापस शून्य;

	वापस bpf_source_table[subtest].desc;
पूर्ण
#अन्यथा //HAVE_LIBBPF_SUPPORT
पूर्णांक test__llvm(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	वापस TEST_SKIP;
पूर्ण

पूर्णांक test__llvm_subtest_get_nr(व्योम)
अणु
	वापस 0;
पूर्ण

स्थिर अक्षर *test__llvm_subtest_get_desc(पूर्णांक subtest __maybe_unused)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT
