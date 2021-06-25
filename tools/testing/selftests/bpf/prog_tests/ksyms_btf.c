<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Google */

#समावेश <test_progs.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/btf.h>
#समावेश "test_ksyms_btf.skel.h"
#समावेश "test_ksyms_btf_null_check.skel.h"

अटल पूर्णांक duration;

अटल व्योम test_basic(व्योम)
अणु
	__u64 runqueues_addr, bpf_prog_active_addr;
	__u32 this_rq_cpu;
	पूर्णांक this_bpf_prog_active;
	काष्ठा test_ksyms_btf *skel = शून्य;
	काष्ठा test_ksyms_btf__data *data;
	पूर्णांक err;

	err = kallsyms_find("runqueues", &runqueues_addr);
	अगर (CHECK(err == -EINVAL, "kallsyms_fopen", "failed to open: %d\n", त्रुटि_सं))
		वापस;
	अगर (CHECK(err == -ENOENT, "ksym_find", "symbol 'runqueues' not found\n"))
		वापस;

	err = kallsyms_find("bpf_prog_active", &bpf_prog_active_addr);
	अगर (CHECK(err == -EINVAL, "kallsyms_fopen", "failed to open: %d\n", त्रुटि_सं))
		वापस;
	अगर (CHECK(err == -ENOENT, "ksym_find", "symbol 'bpf_prog_active' not found\n"))
		वापस;

	skel = test_ksyms_btf__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open and load skeleton\n"))
		जाओ cleanup;

	err = test_ksyms_btf__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	/* trigger tracepoपूर्णांक */
	usleep(1);

	data = skel->data;
	CHECK(data->out__runqueues_addr != runqueues_addr, "runqueues_addr",
	      "got %llu, exp %llu\n",
	      (अचिन्हित दीर्घ दीर्घ)data->out__runqueues_addr,
	      (अचिन्हित दीर्घ दीर्घ)runqueues_addr);
	CHECK(data->out__bpf_prog_active_addr != bpf_prog_active_addr, "bpf_prog_active_addr",
	      "got %llu, exp %llu\n",
	      (अचिन्हित दीर्घ दीर्घ)data->out__bpf_prog_active_addr,
	      (अचिन्हित दीर्घ दीर्घ)bpf_prog_active_addr);

	CHECK(data->out__rq_cpu == -1, "rq_cpu",
	      "got %u, exp != -1\n", data->out__rq_cpu);
	CHECK(data->out__bpf_prog_active < 0, "bpf_prog_active",
	      "got %d, exp >= 0\n", data->out__bpf_prog_active);
	CHECK(data->out__cpu_0_rq_cpu != 0, "cpu_rq(0)->cpu",
	      "got %u, exp 0\n", data->out__cpu_0_rq_cpu);

	this_rq_cpu = data->out__this_rq_cpu;
	CHECK(this_rq_cpu != data->out__rq_cpu, "this_rq_cpu",
	      "got %u, exp %u\n", this_rq_cpu, data->out__rq_cpu);

	this_bpf_prog_active = data->out__this_bpf_prog_active;
	CHECK(this_bpf_prog_active != data->out__bpf_prog_active, "this_bpf_prog_active",
	      "got %d, exp %d\n", this_bpf_prog_active,
	      data->out__bpf_prog_active);

cleanup:
	test_ksyms_btf__destroy(skel);
पूर्ण

अटल व्योम test_null_check(व्योम)
अणु
	काष्ठा test_ksyms_btf_null_check *skel;

	skel = test_ksyms_btf_null_check__खोलो_and_load();
	CHECK(skel, "skel_open", "unexpected load of a prog missing null check\n");

	test_ksyms_btf_null_check__destroy(skel);
पूर्ण

व्योम test_ksyms_btf(व्योम)
अणु
	पूर्णांक percpu_datasec;
	काष्ठा btf *btf;

	btf = libbpf_find_kernel_btf();
	अगर (CHECK(IS_ERR(btf), "btf_exists", "failed to load kernel BTF: %ld\n",
		  PTR_ERR(btf)))
		वापस;

	percpu_datasec = btf__find_by_name_kind(btf, ".data..percpu",
						BTF_KIND_DATASEC);
	btf__मुक्त(btf);
	अगर (percpu_datasec < 0) अणु
		म_लिखो("%s:SKIP:no PERCPU DATASEC in kernel btf\n",
		       __func__);
		test__skip();
		वापस;
	पूर्ण

	अगर (test__start_subtest("basic"))
		test_basic();

	अगर (test__start_subtest("null_check"))
		test_null_check();
पूर्ण
