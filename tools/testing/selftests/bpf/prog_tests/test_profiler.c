<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <test_progs.h>
#समावेश "progs/profiler.h"
#समावेश "profiler1.skel.h"
#समावेश "profiler2.skel.h"
#समावेश "profiler3.skel.h"

अटल पूर्णांक sanity_run(काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_prog_test_run_attr test_attr = अणुपूर्ण;
	__u64 args[] = अणु1, 2, 3पूर्ण;
	__u32 duration = 0;
	पूर्णांक err, prog_fd;

	prog_fd = bpf_program__fd(prog);
	test_attr.prog_fd = prog_fd;
	test_attr.ctx_in = args;
	test_attr.ctx_size_in = माप(args);
	err = bpf_prog_test_run_xattr(&test_attr);
	अगर (CHECK(err || test_attr.retval, "test_run",
		  "err %d errno %d retval %d duration %d\n",
		  err, त्रुटि_सं, test_attr.retval, duration))
		वापस -1;
	वापस 0;
पूर्ण

व्योम test_test_profiler(व्योम)
अणु
	काष्ठा profiler1 *profiler1_skel = शून्य;
	काष्ठा profiler2 *profiler2_skel = शून्य;
	काष्ठा profiler3 *profiler3_skel = शून्य;
	__u32 duration = 0;
	पूर्णांक err;

	profiler1_skel = profiler1__खोलो_and_load();
	अगर (CHECK(!profiler1_skel, "profiler1_skel_load", "profiler1 skeleton failed\n"))
		जाओ cleanup;

	err = profiler1__attach(profiler1_skel);
	अगर (CHECK(err, "profiler1_attach", "profiler1 attach failed: %d\n", err))
		जाओ cleanup;

	अगर (sanity_run(profiler1_skel->progs.raw_tracepoपूर्णांक__sched_process_exec))
		जाओ cleanup;

	profiler2_skel = profiler2__खोलो_and_load();
	अगर (CHECK(!profiler2_skel, "profiler2_skel_load", "profiler2 skeleton failed\n"))
		जाओ cleanup;

	err = profiler2__attach(profiler2_skel);
	अगर (CHECK(err, "profiler2_attach", "profiler2 attach failed: %d\n", err))
		जाओ cleanup;

	अगर (sanity_run(profiler2_skel->progs.raw_tracepoपूर्णांक__sched_process_exec))
		जाओ cleanup;

	profiler3_skel = profiler3__खोलो_and_load();
	अगर (CHECK(!profiler3_skel, "profiler3_skel_load", "profiler3 skeleton failed\n"))
		जाओ cleanup;

	err = profiler3__attach(profiler3_skel);
	अगर (CHECK(err, "profiler3_attach", "profiler3 attach failed: %d\n", err))
		जाओ cleanup;

	अगर (sanity_run(profiler3_skel->progs.raw_tracepoपूर्णांक__sched_process_exec))
		जाओ cleanup;
cleanup:
	profiler1__destroy(profiler1_skel);
	profiler2__destroy(profiler2_skel);
	profiler3__destroy(profiler3_skel);
पूर्ण
