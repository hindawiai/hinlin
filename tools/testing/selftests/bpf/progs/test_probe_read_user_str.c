<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#समावेश <sys/types.h>

pid_t pid = 0;
दीर्घ ret = 0;
व्योम *user_ptr = 0;
अक्षर buf[256] = अणुपूर्ण;

SEC("tracepoint/syscalls/sys_enter_nanosleep")
पूर्णांक on_ग_लिखो(व्योम *ctx)
अणु
	अगर (pid != (bpf_get_current_pid_tgid() >> 32))
		वापस 0;

	ret = bpf_probe_पढ़ो_user_str(buf, माप(buf), user_ptr);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
