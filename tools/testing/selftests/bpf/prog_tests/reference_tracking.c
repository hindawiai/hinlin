<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_reference_tracking(व्योम)
अणु
	स्थिर अक्षर *file = "test_sk_lookup_kern.o";
	स्थिर अक्षर *obj_name = "ref_track";
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, खोलो_opts,
		.object_name = obj_name,
		.relaxed_maps = true,
	);
	काष्ठा bpf_object *obj;
	काष्ठा bpf_program *prog;
	__u32 duration = 0;
	पूर्णांक err = 0;

	obj = bpf_object__खोलो_file(file, &खोलो_opts);
	अगर (CHECK_FAIL(IS_ERR(obj)))
		वापस;

	अगर (CHECK(म_भेद(bpf_object__name(obj), obj_name), "obj_name",
		  "wrong obj name '%s', expected '%s'\n",
		  bpf_object__name(obj), obj_name))
		जाओ cleanup;

	bpf_object__क्रम_each_program(prog, obj) अणु
		स्थिर अक्षर *title;

		/* Ignore .text sections */
		title = bpf_program__section_name(prog);
		अगर (म_माला(title, ".text") != शून्य)
			जारी;

		अगर (!test__start_subtest(title))
			जारी;

		/* Expect verअगरier failure अगर test name has 'fail' */
		अगर (म_माला(title, "fail") != शून्य) अणु
			libbpf_prपूर्णांक_fn_t old_prपूर्णांक_fn;

			old_prपूर्णांक_fn = libbpf_set_prपूर्णांक(शून्य);
			err = !bpf_program__load(prog, "GPL", 0);
			libbpf_set_prपूर्णांक(old_prपूर्णांक_fn);
		पूर्ण अन्यथा अणु
			err = bpf_program__load(prog, "GPL", 0);
		पूर्ण
		CHECK(err, title, "\n");
	पूर्ण

cleanup:
	bpf_object__बंद(obj);
पूर्ण
