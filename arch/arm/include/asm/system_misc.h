<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_SYSTEM_MISC_H
#घोषणा __ASM_ARM_SYSTEM_MISC_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/reboot.h>
#समावेश <linux/percpu.h>

बाह्य व्योम cpu_init(व्योम);

व्योम soft_restart(अचिन्हित दीर्घ);
बाह्य व्योम (*arm_pm_restart)(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *cmd);
बाह्य व्योम (*arm_pm_idle)(व्योम);

#अगर_घोषित CONFIG_HARDEN_BRANCH_PREDICTOR
प्रकार व्योम (*harden_branch_predictor_fn_t)(व्योम);
DECLARE_PER_CPU(harden_branch_predictor_fn_t, harden_branch_predictor_fn);
अटल अंतरभूत व्योम harden_branch_predictor(व्योम)
अणु
	harden_branch_predictor_fn_t fn = per_cpu(harden_branch_predictor_fn,
						  smp_processor_id());
	अगर (fn)
		fn();
पूर्ण
#अन्यथा
#घोषणा harden_branch_predictor() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा UDBG_UNDEFINED	(1 << 0)
#घोषणा UDBG_SYSCALL	(1 << 1)
#घोषणा UDBG_BADABORT	(1 << 2)
#घोषणा UDBG_SEGV	(1 << 3)
#घोषणा UDBG_BUS	(1 << 4)

बाह्य अचिन्हित पूर्णांक user_debug;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_ARM_SYSTEM_MISC_H */
