<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/unistd.h>
#समावेश <linux/bpf.h>
#समावेश <unistd.h>

#अगर_अघोषित __NR_bpf
# अगर defined(__i386__)
#  define __NR_bpf 357
# elअगर defined(__x86_64__)
#  define __NR_bpf 321
# elअगर defined(__aarch64__)
#  define __NR_bpf 280
# elअगर defined(__sparc__)
#  define __NR_bpf 349
# elअगर defined(__s390__)
#  define __NR_bpf 351
# अन्यथा
#  error __NR_bpf not defined. libbpf करोes not support your arch.
# endअगर
#पूर्ण_अगर

पूर्णांक मुख्य(व्योम)
अणु
	जोड़ bpf_attr attr;

	/* Check fields in attr */
	attr.prog_type = BPF_PROG_TYPE_KPROBE;
	attr.insn_cnt = 0;
	attr.insns = 0;
	attr.license = 0;
	attr.log_buf = 0;
	attr.log_size = 0;
	attr.log_level = 0;
	attr.kern_version = 0;
	attr.prog_flags = 0;

	/*
	 * Test existence of __NR_bpf and BPF_PROG_LOAD.
	 * This call should fail अगर we run the testहाल.
	 */
	वापस syscall(__NR_bpf, BPF_PROG_LOAD, &attr, माप(attr));
पूर्ण
