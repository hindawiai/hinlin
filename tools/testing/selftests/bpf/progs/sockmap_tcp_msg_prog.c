<शैली गुरु>
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

पूर्णांक _version SEC("version") = 1;

SEC("sk_msg1")
पूर्णांक bpf_prog1(काष्ठा sk_msg_md *msg)
अणु
	वापस SK_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
