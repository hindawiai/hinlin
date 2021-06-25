<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PROTO_H
#घोषणा _ASM_X86_PROTO_H

#समावेश <यंत्र/ldt.h>

काष्ठा task_काष्ठा;

/* misc architecture specअगरic prototypes */

व्योम syscall_init(व्योम);

#अगर_घोषित CONFIG_X86_64
व्योम entry_SYSCALL_64(व्योम);
व्योम entry_SYSCALL_64_safe_stack(व्योम);
दीर्घ करो_arch_prctl_64(काष्ठा task_काष्ठा *task, पूर्णांक option, अचिन्हित दीर्घ arg2);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
व्योम entry_INT80_32(व्योम);
व्योम entry_SYSENTER_32(व्योम);
व्योम __begin_SYSENTER_singlestep_region(व्योम);
व्योम __end_SYSENTER_singlestep_region(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_IA32_EMULATION
व्योम entry_SYSENTER_compat(व्योम);
व्योम __end_entry_SYSENTER_compat(व्योम);
व्योम entry_SYSCALL_compat(व्योम);
व्योम entry_SYSCALL_compat_safe_stack(व्योम);
व्योम entry_INT80_compat(व्योम);
#अगर_घोषित CONFIG_XEN_PV
व्योम xen_entry_INT80_compat(व्योम);
#पूर्ण_अगर
#पूर्ण_अगर

व्योम x86_configure_nx(व्योम);
व्योम x86_report_nx(व्योम);

बाह्य पूर्णांक reboot_क्रमce;

दीर्घ करो_arch_prctl_common(काष्ठा task_काष्ठा *task, पूर्णांक option,
			  अचिन्हित दीर्घ cpuid_enabled);

#पूर्ण_अगर /* _ASM_X86_PROTO_H */
