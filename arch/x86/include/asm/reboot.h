<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_REBOOT_H
#घोषणा _ASM_X86_REBOOT_H

#समावेश <linux/kdebug.h>

काष्ठा pt_regs;

काष्ठा machine_ops अणु
	व्योम (*restart)(अक्षर *cmd);
	व्योम (*halt)(व्योम);
	व्योम (*घातer_off)(व्योम);
	व्योम (*shutकरोwn)(व्योम);
	व्योम (*crash_shutकरोwn)(काष्ठा pt_regs *);
	व्योम (*emergency_restart)(व्योम);
पूर्ण;

बाह्य काष्ठा machine_ops machine_ops;
बाह्य पूर्णांक crashing_cpu;

व्योम native_machine_crash_shutकरोwn(काष्ठा pt_regs *regs);
व्योम native_machine_shutकरोwn(व्योम);
व्योम __noवापस machine_real_restart(अचिन्हित पूर्णांक type);
/* These must match dispatch in arch/x86/realmore/rm/reboot.S */
#घोषणा MRR_BIOS	0
#घोषणा MRR_APM		1

प्रकार व्योम (*nmi_shootकरोwn_cb)(पूर्णांक, काष्ठा pt_regs*);
व्योम nmi_panic_self_stop(काष्ठा pt_regs *regs);
व्योम nmi_shootकरोwn_cpus(nmi_shootकरोwn_cb callback);
व्योम run_crash_ipi_callback(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* _ASM_X86_REBOOT_H */
