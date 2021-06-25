<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ELFCORE_H
#घोषणा _LINUX_ELFCORE_H

#समावेश <linux/user.h>
#समावेश <linux/bug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/types.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/समय.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/fs.h>
#समावेश <linux/elf.h>

काष्ठा coredump_params;

काष्ठा elf_siginfo
अणु
	पूर्णांक	si_signo;			/* संकेत number */
	पूर्णांक	si_code;			/* extra code */
	पूर्णांक	si_त्रुटि_सं;			/* त्रुटि_सं */
पूर्ण;

/*
 * Definitions to generate Intel SVR4-like core files.
 * These mostly have the same names as the SVR4 types with "elf_"
 * tacked on the front to prevent clashes with linux definitions,
 * and the प्रकार क्रमms have been aव्योमed.  This is mostly like
 * the SVR4 काष्ठाure, but more Linuxy, with things that Linux करोes
 * not support and which gdb करोesn't really use excluded.
 */
काष्ठा elf_prstatus_common
अणु
	काष्ठा elf_siginfo pr_info;	/* Info associated with संकेत */
	लघु	pr_cursig;		/* Current संकेत */
	अचिन्हित दीर्घ pr_sigpend;	/* Set of pending संकेतs */
	अचिन्हित दीर्घ pr_sighold;	/* Set of held संकेतs */
	pid_t	pr_pid;
	pid_t	pr_ppid;
	pid_t	pr_pgrp;
	pid_t	pr_sid;
	काष्ठा __kernel_old_समयval pr_uसमय;	/* User समय */
	काष्ठा __kernel_old_समयval pr_sसमय;	/* System समय */
	काष्ठा __kernel_old_समयval pr_cuसमय;	/* Cumulative user समय */
	काष्ठा __kernel_old_समयval pr_csसमय;	/* Cumulative प्रणाली समय */
पूर्ण;

काष्ठा elf_prstatus
अणु
	काष्ठा elf_prstatus_common common;
	elf_gregset_t pr_reg;	/* GP रेजिस्टरs */
	पूर्णांक pr_fpvalid;		/* True अगर math co-processor being used.  */
पूर्ण;

#घोषणा ELF_PRARGSZ	(80)	/* Number of अक्षरs क्रम args */

काष्ठा elf_prpsinfo
अणु
	अक्षर	pr_state;	/* numeric process state */
	अक्षर	pr_sname;	/* अक्षर क्रम pr_state */
	अक्षर	pr_zomb;	/* zombie */
	अक्षर	pr_nice;	/* nice val */
	अचिन्हित दीर्घ pr_flag;	/* flags */
	__kernel_uid_t	pr_uid;
	__kernel_gid_t	pr_gid;
	pid_t	pr_pid, pr_ppid, pr_pgrp, pr_sid;
	/* Lots missing */
	अक्षर	pr_fname[16];	/* filename of executable */
	अक्षर	pr_psargs[ELF_PRARGSZ];	/* initial part of arg list */
पूर्ण;

अटल अंतरभूत व्योम elf_core_copy_regs(elf_gregset_t *elfregs, काष्ठा pt_regs *regs)
अणु
#अगर_घोषित ELF_CORE_COPY_REGS
	ELF_CORE_COPY_REGS((*elfregs), regs)
#अन्यथा
	BUG_ON(माप(*elfregs) != माप(*regs));
	*(काष्ठा pt_regs *)elfregs = *regs;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम elf_core_copy_kernel_regs(elf_gregset_t *elfregs, काष्ठा pt_regs *regs)
अणु
#अगर_घोषित ELF_CORE_COPY_KERNEL_REGS
	ELF_CORE_COPY_KERNEL_REGS((*elfregs), regs);
#अन्यथा
	elf_core_copy_regs(elfregs, regs);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक elf_core_copy_task_regs(काष्ठा task_काष्ठा *t, elf_gregset_t* elfregs)
अणु
#अगर defined (ELF_CORE_COPY_TASK_REGS)
	वापस ELF_CORE_COPY_TASK_REGS(t, elfregs);
#या_अगर defined (task_pt_regs)
	elf_core_copy_regs(elfregs, task_pt_regs(t));
#पूर्ण_अगर
	वापस 0;
पूर्ण

बाह्य पूर्णांक dump_fpu (काष्ठा pt_regs *, elf_fpregset_t *);

अटल अंतरभूत पूर्णांक elf_core_copy_task_fpregs(काष्ठा task_काष्ठा *t, काष्ठा pt_regs *regs, elf_fpregset_t *fpu)
अणु
#अगर_घोषित ELF_CORE_COPY_FPREGS
	वापस ELF_CORE_COPY_FPREGS(t, fpu);
#अन्यथा
	वापस dump_fpu(regs, fpu);
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_UM) || defined(CONFIG_IA64)
/*
 * These functions parameterize elf_core_dump in fs/binfmt_elf.c to ग_लिखो out
 * extra segments containing the gate DSO contents.  Dumping its
 * contents makes post-mortem fully पूर्णांकerpretable later without matching up
 * the same kernel and hardware config to see what PC values meant.
 * Dumping its extra ELF program headers includes all the other inक्रमmation
 * a debugger needs to easily find how the gate DSO was being used.
 */
बाह्य Elf_Half elf_core_extra_phdrs(व्योम);
बाह्य पूर्णांक
elf_core_ग_लिखो_extra_phdrs(काष्ठा coredump_params *cprm, loff_t offset);
बाह्य पूर्णांक
elf_core_ग_लिखो_extra_data(काष्ठा coredump_params *cprm);
बाह्य माप_प्रकार elf_core_extra_data_size(व्योम);
#अन्यथा
अटल अंतरभूत Elf_Half elf_core_extra_phdrs(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक elf_core_ग_लिखो_extra_phdrs(काष्ठा coredump_params *cprm, loff_t offset)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक elf_core_ग_लिखो_extra_data(काष्ठा coredump_params *cprm)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत माप_प्रकार elf_core_extra_data_size(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_ELFCORE_H */
