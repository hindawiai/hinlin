<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

/* test_tailcall_1 checks basic functionality by patching multiple locations
 * in a single program क्रम a single tail call slot with nop->jmp, jmp->nop
 * and jmp->jmp reग_लिखोs. Also checks क्रम nop->nop.
 */
अटल व्योम test_tailcall_1(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, i, j;
	काष्ठा bpf_map *prog_array;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अक्षर prog_name[32];
	अक्षर buff[128] = अणुपूर्ण;

	err = bpf_prog_load("tailcall1.o", BPF_PROG_TYPE_SCHED_CLS, &obj,
			    &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
					&duration, &retval, शून्य);
		CHECK(err || retval != i, "tailcall",
		      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);

		err = bpf_map_delete_elem(map_fd, &i);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 3, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 0, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		j = bpf_map__def(prog_array)->max_entries - 1 - i;
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", j);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		j = bpf_map__def(prog_array)->max_entries - 1 - i;

		err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
					&duration, &retval, शून्य);
		CHECK(err || retval != j, "tailcall",
		      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);

		err = bpf_map_delete_elem(map_fd, &i);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 3, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		err = bpf_map_delete_elem(map_fd, &i);
		अगर (CHECK_FAIL(err >= 0 || त्रुटि_सं != ENOENT))
			जाओ out;

		err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
					&duration, &retval, शून्य);
		CHECK(err || retval != 3, "tailcall",
		      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);
	पूर्ण

out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_2 checks that patching multiple programs क्रम a single
 * tail call slot works. It also jumps through several programs and tests
 * the tail call limit counter.
 */
अटल व्योम test_tailcall_2(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, i;
	काष्ठा bpf_map *prog_array;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अक्षर prog_name[32];
	अक्षर buff[128] = अणुपूर्ण;

	err = bpf_prog_load("tailcall2.o", BPF_PROG_TYPE_SCHED_CLS, &obj,
			    &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 2, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	i = 2;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 1, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	i = 0;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 3, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);
out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_3 checks that the count value of the tail call limit
 * enक्रमcement matches with expectations.
 */
अटल व्योम test_tailcall_3(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, data_fd, i, val;
	काष्ठा bpf_map *prog_array, *data_map;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अक्षर buff[128] = अणुपूर्ण;

	err = bpf_prog_load("tailcall3.o", BPF_PROG_TYPE_SCHED_CLS, &obj,
			    &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	prog = bpf_object__find_program_by_title(obj, "classifier/0");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	prog_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(prog_fd < 0))
		जाओ out;

	i = 0;
	err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 1, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	data_map = bpf_object__find_map_by_name(obj, "tailcall.bss");
	अगर (CHECK_FAIL(!data_map || !bpf_map__is_पूर्णांकernal(data_map)))
		वापस;

	data_fd = bpf_map__fd(data_map);
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	i = 0;
	err = bpf_map_lookup_elem(data_fd, &i, &val);
	CHECK(err || val != 33, "tailcall count", "err %d errno %d count %d\n",
	      err, त्रुटि_सं, val);

	i = 0;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 0, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);
out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_4 checks that the kernel properly selects indirect jump
 * क्रम the हाल where the key is not known. Latter is passed via global
 * data to select dअगरferent tarमाला_लो we can compare वापस value of.
 */
अटल व्योम test_tailcall_4(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, data_fd, i;
	काष्ठा bpf_map *prog_array, *data_map;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अटल स्थिर पूर्णांक zero = 0;
	अक्षर buff[128] = अणुपूर्ण;
	अक्षर prog_name[32];

	err = bpf_prog_load("tailcall4.o", BPF_PROG_TYPE_SCHED_CLS, &obj,
			    &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	data_map = bpf_object__find_map_by_name(obj, "tailcall.bss");
	अगर (CHECK_FAIL(!data_map || !bpf_map__is_पूर्णांकernal(data_map)))
		वापस;

	data_fd = bpf_map__fd(data_map);
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		err = bpf_map_update_elem(data_fd, &zero, &i, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;

		err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
					&duration, &retval, शून्य);
		CHECK(err || retval != i, "tailcall",
		      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);
	पूर्ण

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		err = bpf_map_update_elem(data_fd, &zero, &i, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;

		err = bpf_map_delete_elem(map_fd, &i);
		अगर (CHECK_FAIL(err))
			जाओ out;

		err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
					&duration, &retval, शून्य);
		CHECK(err || retval != 3, "tailcall",
		      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);
	पूर्ण
out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_5 probes similarly to test_tailcall_4 that the kernel generates
 * an indirect jump when the keys are स्थिर but dअगरferent from dअगरferent branches.
 */
अटल व्योम test_tailcall_5(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, data_fd, i, key[] = अणु 1111, 1234, 5678 पूर्ण;
	काष्ठा bpf_map *prog_array, *data_map;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अटल स्थिर पूर्णांक zero = 0;
	अक्षर buff[128] = अणुपूर्ण;
	अक्षर prog_name[32];

	err = bpf_prog_load("tailcall5.o", BPF_PROG_TYPE_SCHED_CLS, &obj,
			    &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	data_map = bpf_object__find_map_by_name(obj, "tailcall.bss");
	अगर (CHECK_FAIL(!data_map || !bpf_map__is_पूर्णांकernal(data_map)))
		वापस;

	data_fd = bpf_map__fd(data_map);
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		err = bpf_map_update_elem(data_fd, &zero, &key[i], BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;

		err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
					&duration, &retval, शून्य);
		CHECK(err || retval != i, "tailcall",
		      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);
	पूर्ण

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		err = bpf_map_update_elem(data_fd, &zero, &key[i], BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;

		err = bpf_map_delete_elem(map_fd, &i);
		अगर (CHECK_FAIL(err))
			जाओ out;

		err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
					&duration, &retval, शून्य);
		CHECK(err || retval != 3, "tailcall",
		      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);
	पूर्ण
out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_bpf2bpf_1 purpose is to make sure that tailcalls are working
 * correctly in correlation with BPF subprograms
 */
अटल व्योम test_tailcall_bpf2bpf_1(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, i;
	काष्ठा bpf_map *prog_array;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अक्षर prog_name[32];

	err = bpf_prog_load("tailcall_bpf2bpf1.o", BPF_PROG_TYPE_SCHED_CLS,
			    &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	/* nop -> jmp */
	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	err = bpf_prog_test_run(मुख्य_fd, 1, &pkt_v4, माप(pkt_v4), 0,
				0, &retval, &duration);
	CHECK(err || retval != 1, "tailcall",
	      "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);

	/* jmp -> nop, call subprog that will करो tailcall */
	i = 1;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, &pkt_v4, माप(pkt_v4), 0,
				0, &retval, &duration);
	CHECK(err || retval != 0, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	/* make sure that subprog can access ctx and entry prog that
	 * called this subprog can properly वापस
	 */
	i = 0;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, &pkt_v4, माप(pkt_v4), 0,
				0, &retval, &duration);
	CHECK(err || retval != माप(pkt_v4) * 2,
	      "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);
out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_bpf2bpf_2 checks that the count value of the tail call limit
 * enक्रमcement matches with expectations when tailcall is preceded with
 * bpf2bpf call.
 */
अटल व्योम test_tailcall_bpf2bpf_2(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, data_fd, i, val;
	काष्ठा bpf_map *prog_array, *data_map;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अक्षर buff[128] = अणुपूर्ण;

	err = bpf_prog_load("tailcall_bpf2bpf2.o", BPF_PROG_TYPE_SCHED_CLS,
			    &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	prog = bpf_object__find_program_by_title(obj, "classifier/0");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	prog_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(prog_fd < 0))
		जाओ out;

	i = 0;
	err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 1, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	data_map = bpf_object__find_map_by_name(obj, "tailcall.bss");
	अगर (CHECK_FAIL(!data_map || !bpf_map__is_पूर्णांकernal(data_map)))
		वापस;

	data_fd = bpf_map__fd(data_map);
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	i = 0;
	err = bpf_map_lookup_elem(data_fd, &i, &val);
	CHECK(err || val != 33, "tailcall count", "err %d errno %d count %d\n",
	      err, त्रुटि_सं, val);

	i = 0;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, buff, माप(buff), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != 0, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);
out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_bpf2bpf_3 checks that non-trivial amount of stack (up to
 * 256 bytes) can be used within bpf subprograms that have the tailcalls
 * in them
 */
अटल व्योम test_tailcall_bpf2bpf_3(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, i;
	काष्ठा bpf_map *prog_array;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अक्षर prog_name[32];

	err = bpf_prog_load("tailcall_bpf2bpf3.o", BPF_PROG_TYPE_SCHED_CLS,
			    &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	err = bpf_prog_test_run(मुख्य_fd, 1, &pkt_v4, माप(pkt_v4), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != माप(pkt_v4) * 3,
	      "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	i = 1;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, &pkt_v4, माप(pkt_v4), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != माप(pkt_v4),
	      "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	i = 0;
	err = bpf_map_delete_elem(map_fd, &i);
	अगर (CHECK_FAIL(err))
		जाओ out;

	err = bpf_prog_test_run(मुख्य_fd, 1, &pkt_v4, माप(pkt_v4), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != माप(pkt_v4) * 2,
	      "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);
out:
	bpf_object__बंद(obj);
पूर्ण

/* test_tailcall_bpf2bpf_4 checks that tailcall counter is correctly preserved
 * across tailcalls combined with bpf2bpf calls. क्रम making sure that tailcall
 * counter behaves correctly, bpf program will go through following flow:
 *
 * entry -> entry_subprog -> tailcall0 -> bpf_func0 -> subprog0 ->
 * -> tailcall1 -> bpf_func1 -> subprog1 -> tailcall2 -> bpf_func2 ->
 * subprog2 [here bump global counter] --------^
 *
 * We go through first two tailcalls and start counting from the subprog2 where
 * the loop begins. At the end of the test make sure that the global counter is
 * equal to 31, because tailcall counter includes the first two tailcalls
 * whereas global counter is incremented only on loop presented on flow above.
 */
अटल व्योम test_tailcall_bpf2bpf_4(व्योम)
अणु
	पूर्णांक err, map_fd, prog_fd, मुख्य_fd, data_fd, i, val;
	काष्ठा bpf_map *prog_array, *data_map;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	__u32 retval, duration;
	अक्षर prog_name[32];

	err = bpf_prog_load("tailcall_bpf2bpf4.o", BPF_PROG_TYPE_SCHED_CLS,
			    &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	prog = bpf_object__find_program_by_title(obj, "classifier");
	अगर (CHECK_FAIL(!prog))
		जाओ out;

	मुख्य_fd = bpf_program__fd(prog);
	अगर (CHECK_FAIL(मुख्य_fd < 0))
		जाओ out;

	prog_array = bpf_object__find_map_by_name(obj, "jmp_table");
	अगर (CHECK_FAIL(!prog_array))
		जाओ out;

	map_fd = bpf_map__fd(prog_array);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "classifier/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (CHECK_FAIL(!prog))
			जाओ out;

		prog_fd = bpf_program__fd(prog);
		अगर (CHECK_FAIL(prog_fd < 0))
			जाओ out;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	err = bpf_prog_test_run(मुख्य_fd, 1, &pkt_v4, माप(pkt_v4), 0,
				&duration, &retval, शून्य);
	CHECK(err || retval != माप(pkt_v4) * 3, "tailcall", "err %d errno %d retval %d\n",
	      err, त्रुटि_सं, retval);

	data_map = bpf_object__find_map_by_name(obj, "tailcall.bss");
	अगर (CHECK_FAIL(!data_map || !bpf_map__is_पूर्णांकernal(data_map)))
		वापस;

	data_fd = bpf_map__fd(data_map);
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	i = 0;
	err = bpf_map_lookup_elem(data_fd, &i, &val);
	CHECK(err || val != 31, "tailcall count", "err %d errno %d count %d\n",
	      err, त्रुटि_सं, val);

out:
	bpf_object__बंद(obj);
पूर्ण

व्योम test_tailcalls(व्योम)
अणु
	अगर (test__start_subtest("tailcall_1"))
		test_tailcall_1();
	अगर (test__start_subtest("tailcall_2"))
		test_tailcall_2();
	अगर (test__start_subtest("tailcall_3"))
		test_tailcall_3();
	अगर (test__start_subtest("tailcall_4"))
		test_tailcall_4();
	अगर (test__start_subtest("tailcall_5"))
		test_tailcall_5();
	अगर (test__start_subtest("tailcall_bpf2bpf_1"))
		test_tailcall_bpf2bpf_1();
	अगर (test__start_subtest("tailcall_bpf2bpf_2"))
		test_tailcall_bpf2bpf_2();
	अगर (test__start_subtest("tailcall_bpf2bpf_3"))
		test_tailcall_bpf2bpf_3();
	अगर (test__start_subtest("tailcall_bpf2bpf_4"))
		test_tailcall_bpf2bpf_4();
पूर्ण
