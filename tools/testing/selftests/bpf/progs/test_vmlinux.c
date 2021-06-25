<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"
#समावेश <यंत्र/unistd.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

#घोषणा MY_TV_NSEC 1337

bool tp_called = false;
bool raw_tp_called = false;
bool tp_btf_called = false;
bool kprobe_called = false;
bool fentry_called = false;

SEC("tp/syscalls/sys_enter_nanosleep")
पूर्णांक handle__tp(काष्ठा trace_event_raw_sys_enter *args)
अणु
	काष्ठा __kernel_बारpec *ts;
	दीर्घ tv_nsec;

	अगर (args->id != __NR_nanosleep)
		वापस 0;

	ts = (व्योम *)args->args[0];
	अगर (bpf_probe_पढ़ो_user(&tv_nsec, माप(ts->tv_nsec), &ts->tv_nsec) ||
	    tv_nsec != MY_TV_NSEC)
		वापस 0;

	tp_called = true;
	वापस 0;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक BPF_PROG(handle__raw_tp, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	काष्ठा __kernel_बारpec *ts;
	दीर्घ tv_nsec;

	अगर (id != __NR_nanosleep)
		वापस 0;

	ts = (व्योम *)PT_REGS_PARM1_CORE(regs);
	अगर (bpf_probe_पढ़ो_user(&tv_nsec, माप(ts->tv_nsec), &ts->tv_nsec) ||
	    tv_nsec != MY_TV_NSEC)
		वापस 0;

	raw_tp_called = true;
	वापस 0;
पूर्ण

SEC("tp_btf/sys_enter")
पूर्णांक BPF_PROG(handle__tp_btf, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	काष्ठा __kernel_बारpec *ts;
	दीर्घ tv_nsec;

	अगर (id != __NR_nanosleep)
		वापस 0;

	ts = (व्योम *)PT_REGS_PARM1_CORE(regs);
	अगर (bpf_probe_पढ़ो_user(&tv_nsec, माप(ts->tv_nsec), &ts->tv_nsec) ||
	    tv_nsec != MY_TV_NSEC)
		वापस 0;

	tp_btf_called = true;
	वापस 0;
पूर्ण

SEC("kprobe/hrtimer_start_range_ns")
पूर्णांक BPF_KPROBE(handle__kprobe, काष्ठा hrसमयr *समयr, kसमय_प्रकार tim, u64 delta_ns,
	       स्थिर क्रमागत hrसमयr_mode mode)
अणु
	अगर (tim == MY_TV_NSEC)
		kprobe_called = true;
	वापस 0;
पूर्ण

SEC("fentry/hrtimer_start_range_ns")
पूर्णांक BPF_PROG(handle__fentry, काष्ठा hrसमयr *समयr, kसमय_प्रकार tim, u64 delta_ns,
	     स्थिर क्रमागत hrसमयr_mode mode)
अणु
	अगर (tim == MY_TV_NSEC)
		fentry_called = true;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
