<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Google */

#समावेश "vmlinux.h"

#समावेश <bpf/bpf_helpers.h>

__u64 out__runqueues_addr = -1;
__u64 out__bpf_prog_active_addr = -1;

__u32 out__rq_cpu = -1; /* percpu काष्ठा fields */
पूर्णांक out__bpf_prog_active = -1; /* percpu पूर्णांक */

__u32 out__this_rq_cpu = -1;
पूर्णांक out__this_bpf_prog_active = -1;

__u32 out__cpu_0_rq_cpu = -1; /* cpu_rq(0)->cpu */

बाह्य स्थिर काष्ठा rq runqueues __ksym; /* काष्ठा type global var. */
बाह्य स्थिर पूर्णांक bpf_prog_active __ksym; /* पूर्णांक type global var. */

SEC("raw_tp/sys_enter")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	काष्ठा rq *rq;
	पूर्णांक *active;
	__u32 cpu;

	out__runqueues_addr = (__u64)&runqueues;
	out__bpf_prog_active_addr = (__u64)&bpf_prog_active;

	cpu = bpf_get_smp_processor_id();

	/* test bpf_per_cpu_ptr() */
	rq = (काष्ठा rq *)bpf_per_cpu_ptr(&runqueues, cpu);
	अगर (rq)
		out__rq_cpu = rq->cpu;
	active = (पूर्णांक *)bpf_per_cpu_ptr(&bpf_prog_active, cpu);
	अगर (active)
		out__bpf_prog_active = *active;

	rq = (काष्ठा rq *)bpf_per_cpu_ptr(&runqueues, 0);
	अगर (rq) /* should always be valid, but we can't spare the check. */
		out__cpu_0_rq_cpu = rq->cpu;

	/* test bpf_this_cpu_ptr */
	rq = (काष्ठा rq *)bpf_this_cpu_ptr(&runqueues);
	out__this_rq_cpu = rq->cpu;
	active = (पूर्णांक *)bpf_this_cpu_ptr(&bpf_prog_active);
	out__this_bpf_prog_active = *active;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
