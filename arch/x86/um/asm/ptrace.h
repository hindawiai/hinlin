<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_X86_PTRACE_H
#घोषणा __UM_X86_PTRACE_H

#समावेश <linux/compiler.h>
#अगर_अघोषित CONFIG_X86_32
#घोषणा __FRAME_OFFSETS /* Needed to get the R* macros */
#पूर्ण_अगर
#समावेश <यंत्र/ptrace-generic.h>

#घोषणा user_mode(r) UPT_IS_USER(&(r)->regs)

#घोषणा PT_REGS_AX(r) UPT_AX(&(r)->regs)
#घोषणा PT_REGS_BX(r) UPT_BX(&(r)->regs)
#घोषणा PT_REGS_CX(r) UPT_CX(&(r)->regs)
#घोषणा PT_REGS_DX(r) UPT_DX(&(r)->regs)

#घोषणा PT_REGS_SI(r) UPT_SI(&(r)->regs)
#घोषणा PT_REGS_DI(r) UPT_DI(&(r)->regs)
#घोषणा PT_REGS_BP(r) UPT_BP(&(r)->regs)
#घोषणा PT_REGS_EFLAGS(r) UPT_EFLAGS(&(r)->regs)

#घोषणा PT_REGS_CS(r) UPT_CS(&(r)->regs)
#घोषणा PT_REGS_SS(r) UPT_SS(&(r)->regs)
#घोषणा PT_REGS_DS(r) UPT_DS(&(r)->regs)
#घोषणा PT_REGS_ES(r) UPT_ES(&(r)->regs)

#घोषणा PT_REGS_ORIG_SYSCALL(r) PT_REGS_AX(r)
#घोषणा PT_REGS_SYSCALL_RET(r) PT_REGS_AX(r)

#घोषणा PT_FIX_EXEC_STACK(sp) करो ; जबतक(0)

#घोषणा profile_pc(regs) PT_REGS_IP(regs)

#घोषणा UPT_RESTART_SYSCALL(r) (UPT_IP(r) -= 2)
#घोषणा PT_REGS_SET_SYSCALL_RETURN(r, res) (PT_REGS_AX(r) = (res))

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस PT_REGS_AX(regs);
पूर्ण

/*
 * Forward declaration to aव्योम including sysdep/tls.h, which causes a
 * circular include, and compilation failures.
 */
काष्ठा user_desc;

#अगर_घोषित CONFIG_X86_32

बाह्य पूर्णांक ptrace_get_thपढ़ो_area(काष्ठा task_काष्ठा *child, पूर्णांक idx,
                                  काष्ठा user_desc __user *user_desc);

बाह्य पूर्णांक ptrace_set_thपढ़ो_area(काष्ठा task_काष्ठा *child, पूर्णांक idx,
                                  काष्ठा user_desc __user *user_desc);

#अन्यथा

#घोषणा PT_REGS_R8(r) UPT_R8(&(r)->regs)
#घोषणा PT_REGS_R9(r) UPT_R9(&(r)->regs)
#घोषणा PT_REGS_R10(r) UPT_R10(&(r)->regs)
#घोषणा PT_REGS_R11(r) UPT_R11(&(r)->regs)
#घोषणा PT_REGS_R12(r) UPT_R12(&(r)->regs)
#घोषणा PT_REGS_R13(r) UPT_R13(&(r)->regs)
#घोषणा PT_REGS_R14(r) UPT_R14(&(r)->regs)
#घोषणा PT_REGS_R15(r) UPT_R15(&(r)->regs)

#समावेश <यंत्र/त्रुटिसं.स>

अटल अंतरभूत पूर्णांक ptrace_get_thपढ़ो_area(काष्ठा task_काष्ठा *child, पूर्णांक idx,
                                         काष्ठा user_desc __user *user_desc)
अणु
        वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक ptrace_set_thपढ़ो_area(काष्ठा task_काष्ठा *child, पूर्णांक idx,
                                         काष्ठा user_desc __user *user_desc)
अणु
        वापस -ENOSYS;
पूर्ण

बाह्य दीर्घ arch_prctl(काष्ठा task_काष्ठा *task, पूर्णांक option,
		       अचिन्हित दीर्घ __user *addr);

#पूर्ण_अगर
#घोषणा user_stack_poपूर्णांकer(regs) PT_REGS_SP(regs)
#पूर्ण_अगर /* __UM_X86_PTRACE_H */
