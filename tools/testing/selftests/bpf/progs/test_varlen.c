<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

#घोषणा MAX_LEN 256

अक्षर buf_in1[MAX_LEN] = अणुपूर्ण;
अक्षर buf_in2[MAX_LEN] = अणुपूर्ण;

पूर्णांक test_pid = 0;
bool capture = false;

/* .bss */
__u64 payload1_len1 = 0;
__u64 payload1_len2 = 0;
__u64 total1 = 0;
अक्षर payload1[MAX_LEN + MAX_LEN] = अणुपूर्ण;

/* .data */
पूर्णांक payload2_len1 = -1;
पूर्णांक payload2_len2 = -1;
पूर्णांक total2 = -1;
अक्षर payload2[MAX_LEN + MAX_LEN] = अणु 1 पूर्ण;

पूर्णांक payload3_len1 = -1;
पूर्णांक payload3_len2 = -1;
पूर्णांक total3= -1;
अक्षर payload3[MAX_LEN + MAX_LEN] = अणु 1 पूर्ण;

पूर्णांक payload4_len1 = -1;
पूर्णांक payload4_len2 = -1;
पूर्णांक total4= -1;
अक्षर payload4[MAX_LEN + MAX_LEN] = अणु 1 पूर्ण;

SEC("raw_tp/sys_enter")
पूर्णांक handler64_अचिन्हित(व्योम *regs)
अणु
	पूर्णांक pid = bpf_get_current_pid_tgid() >> 32;
	व्योम *payload = payload1;
	u64 len;

	/* ignore irrelevant invocations */
	अगर (test_pid != pid || !capture)
		वापस 0;

	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in1[0]);
	अगर (len <= MAX_LEN) अणु
		payload += len;
		payload1_len1 = len;
	पूर्ण

	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in2[0]);
	अगर (len <= MAX_LEN) अणु
		payload += len;
		payload1_len2 = len;
	पूर्ण

	total1 = payload - (व्योम *)payload1;

	वापस 0;
पूर्ण

SEC("raw_tp/sys_exit")
पूर्णांक handler64_चिन्हित(व्योम *regs)
अणु
	पूर्णांक pid = bpf_get_current_pid_tgid() >> 32;
	व्योम *payload = payload3;
	दीर्घ len;

	/* ignore irrelevant invocations */
	अगर (test_pid != pid || !capture)
		वापस 0;

	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in1[0]);
	अगर (len >= 0) अणु
		payload += len;
		payload3_len1 = len;
	पूर्ण
	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in2[0]);
	अगर (len >= 0) अणु
		payload += len;
		payload3_len2 = len;
	पूर्ण
	total3 = payload - (व्योम *)payload3;

	वापस 0;
पूर्ण

SEC("tp/raw_syscalls/sys_enter")
पूर्णांक handler32_अचिन्हित(व्योम *regs)
अणु
	पूर्णांक pid = bpf_get_current_pid_tgid() >> 32;
	व्योम *payload = payload2;
	u32 len;

	/* ignore irrelevant invocations */
	अगर (test_pid != pid || !capture)
		वापस 0;

	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in1[0]);
	अगर (len <= MAX_LEN) अणु
		payload += len;
		payload2_len1 = len;
	पूर्ण

	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in2[0]);
	अगर (len <= MAX_LEN) अणु
		payload += len;
		payload2_len2 = len;
	पूर्ण

	total2 = payload - (व्योम *)payload2;

	वापस 0;
पूर्ण

SEC("tp/raw_syscalls/sys_exit")
पूर्णांक handler32_चिन्हित(व्योम *regs)
अणु
	पूर्णांक pid = bpf_get_current_pid_tgid() >> 32;
	व्योम *payload = payload4;
	पूर्णांक len;

	/* ignore irrelevant invocations */
	अगर (test_pid != pid || !capture)
		वापस 0;

	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in1[0]);
	अगर (len >= 0) अणु
		payload += len;
		payload4_len1 = len;
	पूर्ण
	len = bpf_probe_पढ़ो_kernel_str(payload, MAX_LEN, &buf_in2[0]);
	अगर (len >= 0) अणु
		payload += len;
		payload4_len2 = len;
	पूर्ण
	total4 = payload - (व्योम *)payload4;

	वापस 0;
पूर्ण

SEC("tp/syscalls/sys_exit_getpid")
पूर्णांक handler_निकास(व्योम *regs)
अणु
	दीर्घ bla;

	अगर (bpf_probe_पढ़ो_kernel(&bla, माप(bla), 0))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
