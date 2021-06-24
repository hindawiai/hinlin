<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <test_progs.h>
#समावेश "test_ksyms.skel.h"
#समावेश <sys/स्थिति.स>

अटल पूर्णांक duration;

व्योम test_ksyms(व्योम)
अणु
	स्थिर अक्षर *btf_path = "/sys/kernel/btf/vmlinux";
	काष्ठा test_ksyms *skel;
	काष्ठा test_ksyms__data *data;
	__u64 link_fops_addr, per_cpu_start_addr;
	काष्ठा stat st;
	__u64 btf_size;
	पूर्णांक err;

	err = kallsyms_find("bpf_link_fops", &link_fops_addr);
	अगर (CHECK(err == -EINVAL, "kallsyms_fopen", "failed to open: %d\n", त्रुटि_सं))
		वापस;
	अगर (CHECK(err == -ENOENT, "ksym_find", "symbol 'bpf_link_fops' not found\n"))
		वापस;

	err = kallsyms_find("__per_cpu_start", &per_cpu_start_addr);
	अगर (CHECK(err == -EINVAL, "kallsyms_fopen", "failed to open: %d\n", त्रुटि_सं))
		वापस;
	अगर (CHECK(err == -ENOENT, "ksym_find", "symbol 'per_cpu_start' not found\n"))
		वापस;

	अगर (CHECK(stat(btf_path, &st), "stat_btf", "err %d\n", त्रुटि_सं))
		वापस;
	btf_size = st.st_size;

	skel = test_ksyms__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open and load skeleton\n"))
		वापस;

	err = test_ksyms__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	/* trigger tracepoपूर्णांक */
	usleep(1);

	data = skel->data;
	CHECK(data->out__bpf_link_fops != link_fops_addr, "bpf_link_fops",
	      "got 0x%llx, exp 0x%llx\n",
	      data->out__bpf_link_fops, link_fops_addr);
	CHECK(data->out__bpf_link_fops1 != 0, "bpf_link_fops1",
	      "got %llu, exp %llu\n", data->out__bpf_link_fops1, (__u64)0);
	CHECK(data->out__btf_size != btf_size, "btf_size",
	      "got %llu, exp %llu\n", data->out__btf_size, btf_size);
	CHECK(data->out__per_cpu_start != per_cpu_start_addr, "__per_cpu_start",
	      "got %llu, exp %llu\n", data->out__per_cpu_start,
	      per_cpu_start_addr);

cleanup:
	test_ksyms__destroy(skel);
पूर्ण
