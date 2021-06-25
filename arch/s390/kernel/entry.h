<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ENTRY_H
#घोषणा _ENTRY_H

#समावेश <linux/percpu.h>
#समावेश <linux/types.h>
#समावेश <linux/संकेत.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/idle.h>

बाह्य व्योम *restart_stack;

व्योम प्रणाली_call(व्योम);
व्योम pgm_check_handler(व्योम);
व्योम ext_पूर्णांक_handler(व्योम);
व्योम io_पूर्णांक_handler(व्योम);
व्योम mcck_पूर्णांक_handler(व्योम);
व्योम restart_पूर्णांक_handler(व्योम);

व्योम __ret_from_विभाजन(काष्ठा task_काष्ठा *prev, काष्ठा pt_regs *regs);
व्योम __करो_pgm_check(काष्ठा pt_regs *regs);
व्योम __करो_syscall(काष्ठा pt_regs *regs, पूर्णांक per_trap);

व्योम करो_protection_exception(काष्ठा pt_regs *regs);
व्योम करो_dat_exception(काष्ठा pt_regs *regs);
व्योम करो_secure_storage_access(काष्ठा pt_regs *regs);
व्योम करो_non_secure_storage_access(काष्ठा pt_regs *regs);
व्योम करो_secure_storage_violation(काष्ठा pt_regs *regs);
व्योम करो_report_trap(काष्ठा pt_regs *regs, पूर्णांक si_signo, पूर्णांक si_code, अक्षर *str);
व्योम kernel_stack_overflow(काष्ठा pt_regs * regs);
व्योम करो_संकेत(काष्ठा pt_regs *regs);
व्योम handle_संकेत32(काष्ठा kसंकेत *ksig, sigset_t *oldset,
		     काष्ठा pt_regs *regs);
व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs);

व्योम __init init_IRQ(व्योम);
व्योम करो_io_irq(काष्ठा pt_regs *regs);
व्योम करो_ext_irq(काष्ठा pt_regs *regs);
व्योम करो_restart(व्योम *arg);
व्योम __init startup_init(व्योम);
व्योम die(काष्ठा pt_regs *regs, स्थिर अक्षर *str);
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier);
व्योम __init समय_init(व्योम);
अचिन्हित दीर्घ prepare_ftrace_वापस(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ sp, अचिन्हित दीर्घ ip);

काष्ठा s390_mmap_arg_काष्ठा;
काष्ठा fadvise64_64_args;
काष्ठा old_sigaction;

दीर्घ sys_rt_sigवापस(व्योम);
दीर्घ sys_sigवापस(व्योम);

दीर्घ sys_s390_personality(अचिन्हित पूर्णांक personality);
दीर्घ sys_s390_runसमय_instr(पूर्णांक command, पूर्णांक signum);
दीर्घ sys_s390_guarded_storage(पूर्णांक command, काष्ठा gs_cb __user *);
दीर्घ sys_s390_pci_mmio_ग_लिखो(अचिन्हित दीर्घ, स्थिर व्योम __user *, माप_प्रकार);
दीर्घ sys_s390_pci_mmio_पढ़ो(अचिन्हित दीर्घ, व्योम __user *, माप_प्रकार);
दीर्घ sys_s390_sthyi(अचिन्हित दीर्घ function_code, व्योम __user *buffer, u64 __user *वापस_code, अचिन्हित दीर्घ flags);

DECLARE_PER_CPU(u64, mt_cycles[8]);

अचिन्हित दीर्घ stack_alloc(व्योम);
व्योम stack_मुक्त(अचिन्हित दीर्घ stack);

बाह्य अक्षर kprobes_insn_page[];

#पूर्ण_अगर /* _ENTRY_H */
