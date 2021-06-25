<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"

#समावेश <bpf/bpf_helpers.h>

बाह्य स्थिर काष्ठा rq runqueues __ksym; /* काष्ठा type global var. */
बाह्य स्थिर पूर्णांक bpf_prog_active __ksym; /* पूर्णांक type global var. */

SEC("raw_tp/sys_enter")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	काष्ठा rq *rq;
	पूर्णांक *active;
	__u32 cpu;

	cpu = bpf_get_smp_processor_id();
	rq = (काष्ठा rq *)bpf_per_cpu_ptr(&runqueues, cpu);
	active = (पूर्णांक *)bpf_per_cpu_ptr(&bpf_prog_active, cpu);
	अगर (active) अणु
		/* READ_ONCE */
		*(अस्थिर पूर्णांक *)active;
		/* !rq has not been tested, so verअगरier should reject. */
		*(अस्थिर पूर्णांक *)(&rq->cpu);
	पूर्ण

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
