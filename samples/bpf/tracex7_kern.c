<शैली गुरु>
#समावेश <uapi/linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>

SEC("kprobe/open_ctree")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	अचिन्हित दीर्घ rc = -12;

	bpf_override_वापस(ctx, rc);
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
