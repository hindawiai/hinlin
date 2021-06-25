<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <stdbool.h>

#अगर_घोषित ENABLE_ATOMICS_TESTS
bool skip_tests __attribute((__section__(".data"))) = false;
#अन्यथा
bool skip_tests = true;
#पूर्ण_अगर

SEC("fentry/bpf_fentry_test1")
पूर्णांक BPF_PROG(sub, पूर्णांक x)
अणु
#अगर_घोषित ENABLE_ATOMICS_TESTS
	पूर्णांक a = 0;
	पूर्णांक b = __sync_fetch_and_add(&a, 1);
	/* b is certainly 0 here. Can the verअगरier tell? */
	जबतक (b)
		जारी;
#पूर्ण_अगर
	वापस 0;
पूर्ण
