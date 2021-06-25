<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

बाह्य पूर्णांक LINUX_KERNEL_VERSION __kconfig;
/* this weak बाह्य will be strict due to the other file's strong बाह्य */
बाह्य bool CONFIG_BPF_SYSCALL __kconfig __weak;
बाह्य स्थिर व्योम bpf_link_fops __ksym __weak;

पूर्णांक input_bss1;
पूर्णांक input_data1 = 1;
स्थिर अस्थिर पूर्णांक input_rodata1 = 11;

पूर्णांक input_bss_weak __weak;
/* these two definitions should win */
पूर्णांक input_data_weak __weak = 10;
स्थिर अस्थिर पूर्णांक input_rodata_weak __weak = 100;

बाह्य पूर्णांक input_bss2;
बाह्य पूर्णांक input_data2;
बाह्य स्थिर पूर्णांक input_rodata2;

पूर्णांक output_bss1;
पूर्णांक output_data1;
पूर्णांक output_rodata1;

दीर्घ output_sink1;

अटल __noअंतरभूत पूर्णांक get_bss_res(व्योम)
अणु
	/* just make sure all the relocations work against .text as well */
	वापस input_bss1 + input_bss2 + input_bss_weak;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक BPF_PROG(handler1)
अणु
	output_bss1 = get_bss_res();
	output_data1 = input_data1 + input_data2 + input_data_weak;
	output_rodata1 = input_rodata1 + input_rodata2 + input_rodata_weak;

	/* make sure we actually use above special बाह्यs, otherwise compiler
	 * will optimize them out
	 */
	output_sink1 = LINUX_KERNEL_VERSION
		       + CONFIG_BPF_SYSCALL
		       + (दीर्घ)&bpf_link_fops;
	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
