<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_S390_ENTRY_COMMON_H
#घोषणा ARCH_S390_ENTRY_COMMON_H

#समावेश <linux/sched.h>
#समावेश <linux/audit.h>
#समावेश <linux/अक्रमomize_kstack.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/fpu/api.h>

#घोषणा ARCH_EXIT_TO_USER_MODE_WORK (_TIF_GUARDED_STORAGE | _TIF_PER_TRAP)

व्योम करो_per_trap(काष्ठा pt_regs *regs);
व्योम करो_syscall(काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_DEBUG_ENTRY
अटल __always_अंतरभूत व्योम arch_check_user_regs(काष्ठा pt_regs *regs)
अणु
	debug_user_asce(0);
पूर्ण

#घोषणा arch_check_user_regs arch_check_user_regs
#पूर्ण_अगर /* CONFIG_DEBUG_ENTRY */

अटल __always_अंतरभूत व्योम arch_निकास_to_user_mode_work(काष्ठा pt_regs *regs,
							अचिन्हित दीर्घ ti_work)
अणु
	अगर (ti_work & _TIF_PER_TRAP) अणु
		clear_thपढ़ो_flag(TIF_PER_TRAP);
		करो_per_trap(regs);
	पूर्ण

	अगर (ti_work & _TIF_GUARDED_STORAGE)
		gs_load_bc_cb(regs);
पूर्ण

#घोषणा arch_निकास_to_user_mode_work arch_निकास_to_user_mode_work

अटल __always_अंतरभूत व्योम arch_निकास_to_user_mode(व्योम)
अणु
	अगर (test_cpu_flag(CIF_FPU))
		__load_fpu_regs();

	अगर (IS_ENABLED(CONFIG_DEBUG_ENTRY))
		debug_user_asce(1);
पूर्ण

#घोषणा arch_निकास_to_user_mode arch_निकास_to_user_mode

अटल अंतरभूत व्योम arch_निकास_to_user_mode_prepare(काष्ठा pt_regs *regs,
						  अचिन्हित दीर्घ ti_work)
अणु
	choose_अक्रमom_kstack_offset(get_tod_घड़ी_fast() & 0xff);
पूर्ण

#घोषणा arch_निकास_to_user_mode_prepare arch_निकास_to_user_mode_prepare

अटल अंतरभूत bool on_thपढ़ो_stack(व्योम)
अणु
	वापस !(((अचिन्हित दीर्घ)(current->stack) ^ current_stack_poपूर्णांकer()) & ~(THREAD_SIZE - 1));
पूर्ण

#पूर्ण_अगर
