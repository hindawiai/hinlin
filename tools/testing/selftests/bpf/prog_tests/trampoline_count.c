<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <sys/prctl.h>
#समावेश <test_progs.h>

#घोषणा MAX_TRAMP_PROGS 38

काष्ठा inst अणु
	काष्ठा bpf_object *obj;
	काष्ठा bpf_link   *link_fentry;
	काष्ठा bpf_link   *link_fनिकास;
पूर्ण;

अटल पूर्णांक test_task_नाम(व्योम)
अणु
	पूर्णांक fd, duration = 0, err;
	अक्षर buf[] = "test_overhead";

	fd = खोलो("/proc/self/comm", O_WRONLY|O_TRUNC);
	अगर (CHECK(fd < 0, "open /proc", "err %d", त्रुटि_सं))
		वापस -1;
	err = ग_लिखो(fd, buf, माप(buf));
	अगर (err < 0) अणु
		CHECK(err < 0, "task rename", "err %d", त्रुटि_सं);
		बंद(fd);
		वापस -1;
	पूर्ण
	बंद(fd);
	वापस 0;
पूर्ण

अटल काष्ठा bpf_link *load(काष्ठा bpf_object *obj, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_program *prog;
	पूर्णांक duration = 0;

	prog = bpf_object__find_program_by_title(obj, name);
	अगर (CHECK(!prog, "find_probe", "prog '%s' not found\n", name))
		वापस ERR_PTR(-EINVAL);
	वापस bpf_program__attach_trace(prog);
पूर्ण

व्योम test_trampoline_count(व्योम)
अणु
	स्थिर अक्षर *fentry_name = "fentry/__set_task_comm";
	स्थिर अक्षर *fनिकास_name = "fexit/__set_task_comm";
	स्थिर अक्षर *object = "test_trampoline_count.o";
	काष्ठा inst inst[MAX_TRAMP_PROGS] = अणुपूर्ण;
	पूर्णांक err, i = 0, duration = 0;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_link *link;
	अक्षर comm[16] = अणुपूर्ण;

	/* attach 'allowed' trampoline programs */
	क्रम (i = 0; i < MAX_TRAMP_PROGS; i++) अणु
		obj = bpf_object__खोलो_file(object, शून्य);
		अगर (CHECK(IS_ERR(obj), "obj_open_file", "err %ld\n", PTR_ERR(obj))) अणु
			obj = शून्य;
			जाओ cleanup;
		पूर्ण

		err = bpf_object__load(obj);
		अगर (CHECK(err, "obj_load", "err %d\n", err))
			जाओ cleanup;
		inst[i].obj = obj;
		obj = शून्य;

		अगर (अक्रम() % 2) अणु
			link = load(inst[i].obj, fentry_name);
			अगर (CHECK(IS_ERR(link), "attach prog", "err %ld\n", PTR_ERR(link))) अणु
				link = शून्य;
				जाओ cleanup;
			पूर्ण
			inst[i].link_fentry = link;
		पूर्ण अन्यथा अणु
			link = load(inst[i].obj, fनिकास_name);
			अगर (CHECK(IS_ERR(link), "attach prog", "err %ld\n", PTR_ERR(link))) अणु
				link = शून्य;
				जाओ cleanup;
			पूर्ण
			inst[i].link_fनिकास = link;
		पूर्ण
	पूर्ण

	/* and try 1 extra.. */
	obj = bpf_object__खोलो_file(object, शून्य);
	अगर (CHECK(IS_ERR(obj), "obj_open_file", "err %ld\n", PTR_ERR(obj))) अणु
		obj = शून्य;
		जाओ cleanup;
	पूर्ण

	err = bpf_object__load(obj);
	अगर (CHECK(err, "obj_load", "err %d\n", err))
		जाओ cleanup_extra;

	/* ..that needs to fail */
	link = load(obj, fentry_name);
	अगर (CHECK(!IS_ERR(link), "cannot attach over the limit", "err %ld\n", PTR_ERR(link))) अणु
		bpf_link__destroy(link);
		जाओ cleanup_extra;
	पूर्ण

	/* with E2BIG error */
	CHECK(PTR_ERR(link) != -E2BIG, "proper error check", "err %ld\n", PTR_ERR(link));

	/* and finaly execute the probe */
	अगर (CHECK_FAIL(prctl(PR_GET_NAME, comm, 0L, 0L, 0L)))
		जाओ cleanup_extra;
	CHECK_FAIL(test_task_नाम());
	CHECK_FAIL(prctl(PR_SET_NAME, comm, 0L, 0L, 0L));

cleanup_extra:
	bpf_object__बंद(obj);
cleanup:
	अगर (i >= MAX_TRAMP_PROGS)
		i = MAX_TRAMP_PROGS - 1;
	क्रम (; i >= 0; i--) अणु
		bpf_link__destroy(inst[i].link_fentry);
		bpf_link__destroy(inst[i].link_fनिकास);
		bpf_object__बंद(inst[i].obj);
	पूर्ण
पूर्ण
