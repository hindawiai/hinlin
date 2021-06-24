<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <test_progs.h>

स्थिर अक्षर *err_str;
bool found;

अटल पूर्णांक libbpf_debug_prपूर्णांक(क्रमागत libbpf_prपूर्णांक_level level,
			      स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अक्षर *log_buf;

	अगर (level != LIBBPF_WARN ||
	    म_भेद(क्रमmat, "libbpf: \n%s\n")) अणु
		भ_लिखो(क्रमmat, args);
		वापस 0;
	पूर्ण

	log_buf = बहु_तर्क(args, अक्षर *);
	अगर (!log_buf)
		जाओ out;
	अगर (err_str && म_माला(log_buf, err_str) == 0)
		found = true;
out:
	म_लिखो(क्रमmat, log_buf);
	वापस 0;
पूर्ण

बाह्य पूर्णांक extra_prog_load_log_flags;

अटल पूर्णांक check_load(स्थिर अक्षर *file)
अणु
	काष्ठा bpf_prog_load_attr attr;
	काष्ठा bpf_object *obj = शून्य;
	पूर्णांक err, prog_fd;

	स_रखो(&attr, 0, माप(काष्ठा bpf_prog_load_attr));
	attr.file = file;
	attr.prog_type = BPF_PROG_TYPE_UNSPEC;
	attr.log_level = extra_prog_load_log_flags;
	attr.prog_flags = BPF_F_TEST_RND_HI32;
	found = false;
	err = bpf_prog_load_xattr(&attr, &obj, &prog_fd);
	bpf_object__बंद(obj);
	वापस err;
पूर्ण

काष्ठा test_def अणु
	स्थिर अक्षर *file;
	स्थिर अक्षर *err_str;
पूर्ण;

व्योम test_test_global_funcs(व्योम)
अणु
	काष्ठा test_def tests[] = अणु
		अणु "test_global_func1.o", "combined stack size of 4 calls is 544" पूर्ण,
		अणु "test_global_func2.o" पूर्ण,
		अणु "test_global_func3.o" , "the call stack of 8 frames" पूर्ण,
		अणु "test_global_func4.o" पूर्ण,
		अणु "test_global_func5.o" , "expected pointer to ctx, but got PTR" पूर्ण,
		अणु "test_global_func6.o" , "modified ctx ptr R2" पूर्ण,
		अणु "test_global_func7.o" , "foo() doesn't return scalar" पूर्ण,
		अणु "test_global_func8.o" पूर्ण,
		अणु "test_global_func9.o" पूर्ण,
		अणु "test_global_func10.o", "invalid indirect read from stack" पूर्ण,
		अणु "test_global_func11.o", "Caller passes invalid args into func#1" पूर्ण,
		अणु "test_global_func12.o", "invalid mem access 'mem_or_null'" पूर्ण,
		अणु "test_global_func13.o", "Caller passes invalid args into func#1" पूर्ण,
		अणु "test_global_func14.o", "reference type('FWD S') size cannot be determined" पूर्ण,
		अणु "test_global_func15.o", "At program exit the register R0 has value" पूर्ण,
		अणु "test_global_func16.o", "invalid indirect read from stack" पूर्ण,
	पूर्ण;
	libbpf_prपूर्णांक_fn_t old_prपूर्णांक_fn = शून्य;
	पूर्णांक err, i, duration = 0;

	old_prपूर्णांक_fn = libbpf_set_prपूर्णांक(libbpf_debug_prपूर्णांक);

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		स्थिर काष्ठा test_def *test = &tests[i];

		अगर (!test__start_subtest(test->file))
			जारी;

		err_str = test->err_str;
		err = check_load(test->file);
		CHECK_FAIL(!!err ^ !!err_str);
		अगर (err_str)
			CHECK(found, "", "expected string '%s'", err_str);
	पूर्ण
	libbpf_set_prपूर्णांक(old_prपूर्णांक_fn);
पूर्ण
