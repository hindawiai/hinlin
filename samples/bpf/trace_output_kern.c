<शैली गुरु>
#समावेश <linux/ptrace.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "trace_common.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(u32));
	__uपूर्णांक(max_entries, 2);
पूर्ण my_map SEC(".maps");

SEC("kprobe/" SYSCALL(sys_ग_लिखो))
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	काष्ठा S अणु
		u64 pid;
		u64 cookie;
	पूर्ण data;

	data.pid = bpf_get_current_pid_tgid();
	data.cookie = 0x12345678;

	bpf_perf_event_output(ctx, &my_map, 0, &data, माप(data));

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
