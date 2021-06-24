<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

बाह्य पूर्णांक LINUX_KERNEL_VERSION __kconfig;
/* when an बाह्य is defined as both strong and weak, resulting symbol will be strong */
बाह्य bool CONFIG_BPF_SYSCALL __kconfig;
बाह्य स्थिर व्योम __start_BTF __ksym;

पूर्णांक input_bss2;
पूर्णांक input_data2 = 2;
स्थिर अस्थिर पूर्णांक input_rodata2 = 22;

पूर्णांक input_bss_weak __weak;
/* these two weak variables should lose */
पूर्णांक input_data_weak __weak = 20;
स्थिर अस्थिर पूर्णांक input_rodata_weak __weak = 200;

बाह्य पूर्णांक input_bss1;
बाह्य पूर्णांक input_data1;
बाह्य स्थिर पूर्णांक input_rodata1;

पूर्णांक output_bss2;
पूर्णांक output_data2;
पूर्णांक output_rodata2;

पूर्णांक output_sink2;

अटल __noअंतरभूत पूर्णांक get_data_res(व्योम)
अणु
	/* just make sure all the relocations work against .text as well */
	वापस input_data1 + input_data2 + input_data_weak;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक BPF_PROG(handler2)
अणु
	output_bss2 = input_bss1 + input_bss2 + input_bss_weak;
	output_data2 = get_data_res();
	output_rodata2 = input_rodata1 + input_rodata2 + input_rodata_weak;

	/* make sure we actually use above special बाह्यs, otherwise compiler
	 * will optimize them out
	 */
	output_sink2 = LINUX_KERNEL_VERSION
		       + CONFIG_BPF_SYSCALL
		       + (दीर्घ)&__start_BTF;

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
