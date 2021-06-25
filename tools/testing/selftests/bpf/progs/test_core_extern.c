<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* non-existing BPF helper, to test dead code elimination */
अटल पूर्णांक (*bpf_missing_helper)(स्थिर व्योम *arg1, पूर्णांक arg2) = (व्योम *) 999;

बाह्य पूर्णांक LINUX_KERNEL_VERSION __kconfig;
बाह्य bool CONFIG_BPF_SYSCALL __kconfig; /* strong */
बाह्य क्रमागत libbpf_tristate CONFIG_TRISTATE __kconfig __weak;
बाह्य bool CONFIG_BOOL __kconfig __weak;
बाह्य अक्षर CONFIG_CHAR __kconfig __weak;
बाह्य uपूर्णांक16_t CONFIG_USHORT __kconfig __weak;
बाह्य पूर्णांक CONFIG_INT __kconfig __weak;
बाह्य uपूर्णांक64_t CONFIG_ULONG __kconfig __weak;
बाह्य स्थिर अक्षर CONFIG_STR[8] __kconfig __weak;
बाह्य uपूर्णांक64_t CONFIG_MISSING __kconfig __weak;

uपूर्णांक64_t kern_ver = -1;
uपूर्णांक64_t bpf_syscall = -1;
uपूर्णांक64_t tristate_val = -1;
uपूर्णांक64_t bool_val = -1;
uपूर्णांक64_t अक्षर_val = -1;
uपूर्णांक64_t uलघु_val = -1;
uपूर्णांक64_t पूर्णांक_val = -1;
uपूर्णांक64_t uदीर्घ_val = -1;
अक्षर str_val[8] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
uपूर्णांक64_t missing_val = -1;

SEC("raw_tp/sys_enter")
पूर्णांक handle_sys_enter(काष्ठा pt_regs *ctx)
अणु
	पूर्णांक i;

	kern_ver = LINUX_KERNEL_VERSION;
	bpf_syscall = CONFIG_BPF_SYSCALL;
	tristate_val = CONFIG_TRISTATE;
	bool_val = CONFIG_BOOL;
	अक्षर_val = CONFIG_CHAR;
	uलघु_val = CONFIG_USHORT;
	पूर्णांक_val = CONFIG_INT;
	uदीर्घ_val = CONFIG_ULONG;

	क्रम (i = 0; i < माप(CONFIG_STR); i++) अणु
		str_val[i] = CONFIG_STR[i];
	पूर्ण

	अगर (CONFIG_MISSING)
		/* invalid, but dead code - never executed */
		missing_val = bpf_missing_helper(ctx, 123);
	अन्यथा
		missing_val = 0xDEADC0DE;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
