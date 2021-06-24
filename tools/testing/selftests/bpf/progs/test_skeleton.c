<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <stdbool.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा s अणु
	पूर्णांक a;
	दीर्घ दीर्घ b;
पूर्ण __attribute__((packed));

/* .data section */
पूर्णांक in1 = -1;
दीर्घ दीर्घ in2 = -1;

/* .bss section */
अक्षर in3 = '\0';
दीर्घ दीर्घ in4 __attribute__((aligned(64))) = 0;
काष्ठा s in5 = अणुपूर्ण;

/* .rodata section */
स्थिर अस्थिर काष्ठा अणु
	स्थिर पूर्णांक in6;
पूर्ण in = अणुपूर्ण;

/* .data section */
पूर्णांक out1 = -1;
दीर्घ दीर्घ out2 = -1;

/* .bss section */
अक्षर out3 = 0;
दीर्घ दीर्घ out4 = 0;
पूर्णांक out6 = 0;

बाह्य bool CONFIG_BPF_SYSCALL __kconfig;
बाह्य पूर्णांक LINUX_KERNEL_VERSION __kconfig;
bool bpf_syscall = 0;
पूर्णांक kern_ver = 0;

SEC("raw_tp/sys_enter")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	अटल अस्थिर काष्ठा s out5;

	out1 = in1;
	out2 = in2;
	out3 = in3;
	out4 = in4;
	out5 = in5;
	out6 = in.in6;

	bpf_syscall = CONFIG_BPF_SYSCALL;
	kern_ver = LINUX_KERNEL_VERSION;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
