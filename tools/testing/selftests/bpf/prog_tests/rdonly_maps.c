<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

काष्ठा bss अणु
	अचिन्हित did_run;
	अचिन्हित iters;
	अचिन्हित sum;
पूर्ण;

काष्ठा rकरोnly_map_subtest अणु
	स्थिर अक्षर *subtest_name;
	स्थिर अक्षर *prog_name;
	अचिन्हित exp_iters;
	अचिन्हित exp_sum;
पूर्ण;

व्योम test_rकरोnly_maps(व्योम)
अणु
	स्थिर अक्षर *file = "test_rdonly_maps.o";
	काष्ठा rकरोnly_map_subtest subtests[] = अणु
		अणु "skip loop", "skip_loop", 0, 0 पूर्ण,
		अणु "part loop", "part_loop", 3, 2 + 3 + 4 पूर्ण,
		अणु "full loop", "full_loop", 4, 2 + 3 + 4 + 5 पूर्ण,
	पूर्ण;
	पूर्णांक i, err, zero = 0, duration = 0;
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_map *bss_map;
	काष्ठा bpf_object *obj;
	काष्ठा bss bss;

	obj = bpf_object__खोलो_file(file, शून्य);
	अगर (CHECK(IS_ERR(obj), "obj_open", "err %ld\n", PTR_ERR(obj)))
		वापस;

	err = bpf_object__load(obj);
	अगर (CHECK(err, "obj_load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	bss_map = bpf_object__find_map_by_name(obj, "test_rdo.bss");
	अगर (CHECK(!bss_map, "find_bss_map", "failed\n"))
		जाओ cleanup;

	क्रम (i = 0; i < ARRAY_SIZE(subtests); i++) अणु
		स्थिर काष्ठा rकरोnly_map_subtest *t = &subtests[i];

		अगर (!test__start_subtest(t->subtest_name))
			जारी;

		prog = bpf_object__find_program_by_name(obj, t->prog_name);
		अगर (CHECK(!prog, "find_prog", "prog '%s' not found\n",
			  t->prog_name))
			जाओ cleanup;

		स_रखो(&bss, 0, माप(bss));
		err = bpf_map_update_elem(bpf_map__fd(bss_map), &zero, &bss, 0);
		अगर (CHECK(err, "set_bss", "failed to set bss data: %d\n", err))
			जाओ cleanup;

		link = bpf_program__attach_raw_tracepoपूर्णांक(prog, "sys_enter");
		अगर (CHECK(IS_ERR(link), "attach_prog", "prog '%s', err %ld\n",
			  t->prog_name, PTR_ERR(link))) अणु
			link = शून्य;
			जाओ cleanup;
		पूर्ण

		/* trigger probe */
		usleep(1);

		bpf_link__destroy(link);
		link = शून्य;

		err = bpf_map_lookup_elem(bpf_map__fd(bss_map), &zero, &bss);
		अगर (CHECK(err, "get_bss", "failed to get bss data: %d\n", err))
			जाओ cleanup;
		अगर (CHECK(bss.did_run == 0, "check_run",
			  "prog '%s' didn't run?\n", t->prog_name))
			जाओ cleanup;
		अगर (CHECK(bss.iters != t->exp_iters, "check_iters",
			  "prog '%s' iters: %d, expected: %d\n",
			  t->prog_name, bss.iters, t->exp_iters))
			जाओ cleanup;
		अगर (CHECK(bss.sum != t->exp_sum, "check_sum",
			  "prog '%s' sum: %d, expected: %d\n",
			  t->prog_name, bss.sum, t->exp_sum))
			जाओ cleanup;
	पूर्ण

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
पूर्ण
