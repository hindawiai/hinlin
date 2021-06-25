<शैली गुरु>
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

स्थिर अक्षर LICENSE[] SEC("license") = "GPL";

__attribute__((unused)) __noअंतरभूत पूर्णांक unused1(पूर्णांक x)
अणु
	वापस x + 1;
पूर्ण

अटल __attribute__((unused)) __noअंतरभूत पूर्णांक unused2(पूर्णांक x)
अणु
	वापस x + 2;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक मुख्य_prog(व्योम *ctx)
अणु
	वापस 0;
पूर्ण
