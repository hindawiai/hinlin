<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_PTRACE_H
#घोषणा __SPARC_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

#अगर defined(__sparc__) && defined(__arch64__)
#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/चयन_to.h>

अटल अंतरभूत पूर्णांक pt_regs_trap_type(काष्ठा pt_regs *regs)
अणु
	वापस regs->magic & 0x1ff;
पूर्ण

अटल अंतरभूत bool pt_regs_is_syscall(काष्ठा pt_regs *regs)
अणु
	वापस (regs->tstate & TSTATE_SYSCALL);
पूर्ण

अटल अंतरभूत bool pt_regs_clear_syscall(काष्ठा pt_regs *regs)
अणु
	वापस (regs->tstate &= ~TSTATE_SYSCALL);
पूर्ण

#घोषणा arch_ptrace_stop_needed(निकास_code, info) \
(अणु	flush_user_winकरोws(); \
	get_thपढ़ो_wsaved() != 0; \
पूर्ण)

#घोषणा arch_ptrace_stop(निकास_code, info) \
	synchronize_user_stack()

#घोषणा current_pt_regs() \
	((काष्ठा pt_regs *)((अचिन्हित दीर्घ)current_thपढ़ो_info() + THREAD_SIZE) - 1)

काष्ठा global_reg_snapshot अणु
	अचिन्हित दीर्घ		tstate;
	अचिन्हित दीर्घ		tpc;
	अचिन्हित दीर्घ		tnpc;
	अचिन्हित दीर्घ		o7;
	अचिन्हित दीर्घ		i7;
	अचिन्हित दीर्घ		rpc;
	काष्ठा thपढ़ो_info	*thपढ़ो;
	अचिन्हित दीर्घ		pad1;
पूर्ण;

काष्ठा global_pmu_snapshot अणु
	अचिन्हित दीर्घ		pcr[4];
	अचिन्हित दीर्घ		pic[4];
पूर्ण;

जोड़ global_cpu_snapshot अणु
	काष्ठा global_reg_snapshot	reg;
	काष्ठा global_pmu_snapshot	pmu;
पूर्ण;

बाह्य जोड़ global_cpu_snapshot global_cpu_snapshot[NR_CPUS];

#घोषणा क्रमce_successful_syscall_वापस() set_thपढ़ो_noerror(1)
#घोषणा user_mode(regs) (!((regs)->tstate & TSTATE_PRIV))
#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->tpc)
#घोषणा inकाष्ठाion_poपूर्णांकer_set(regs, val) करो अणु \
		(regs)->tpc = (val); \
		(regs)->tnpc = (val)+4; \
	पूर्ण जबतक (0)
#घोषणा user_stack_poपूर्णांकer(regs) ((regs)->u_regs[UREG_FP])
अटल अंतरभूत पूर्णांक is_syscall_success(काष्ठा pt_regs *regs)
अणु
	वापस !(regs->tstate & (TSTATE_XCARRY | TSTATE_ICARRY));
पूर्ण

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->u_regs[UREG_I0];
पूर्ण
#अगर_घोषित CONFIG_SMP
अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *);
#अन्यथा
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
#पूर्ण_अगर

#घोषणा MAX_REG_OFFSET (दुरत्व(काष्ठा pt_regs, magic))

पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n);

/**
 * regs_get_रेजिस्टर() - get रेजिस्टर value from its offset
 * @regs:	pt_regs from which रेजिस्टर value is gotten
 * @offset:	offset number of the रेजिस्टर.
 *
 * regs_get_रेजिस्टर वापसs the value of a रेजिस्टर whose
 * offset from @regs. The @offset is the offset of the रेजिस्टर
 * in काष्ठा pt_regs. If @offset is bigger than MAX_REG_OFFSET,
 * this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_रेजिस्टर(काष्ठा pt_regs *regs,
					     अचिन्हित दीर्घ offset)
अणु
	अगर (unlikely(offset >= MAX_REG_OFFSET))
		वापस 0;
	अगर (offset == PT_V9_Y)
		वापस *(अचिन्हित पूर्णांक *)((अचिन्हित दीर्घ)regs + offset);
	वापस *(अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)regs + offset);
पूर्ण

/* Valid only क्रम Kernel mode traps. */
अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->u_regs[UREG_I6];
पूर्ण
#अन्यथा /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASSEMBLY__ */
#अन्यथा /* (defined(__sparc__) && defined(__arch64__)) */
#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/चयन_to.h>

अटल अंतरभूत bool pt_regs_is_syscall(काष्ठा pt_regs *regs)
अणु
	वापस (regs->psr & PSR_SYSCALL);
पूर्ण

अटल अंतरभूत bool pt_regs_clear_syscall(काष्ठा pt_regs *regs)
अणु
	वापस (regs->psr &= ~PSR_SYSCALL);
पूर्ण

#घोषणा arch_ptrace_stop_needed(निकास_code, info) \
(अणु	flush_user_winकरोws(); \
	current_thपढ़ो_info()->w_saved != 0;	\
पूर्ण)

#घोषणा arch_ptrace_stop(निकास_code, info) \
	synchronize_user_stack()

#घोषणा current_pt_regs() \
	((काष्ठा pt_regs *)((अचिन्हित दीर्घ)current_thपढ़ो_info() + THREAD_SIZE) - 1)

#घोषणा user_mode(regs) (!((regs)->psr & PSR_PS))
#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->pc)
#घोषणा user_stack_poपूर्णांकer(regs) ((regs)->u_regs[UREG_FP])
अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *);
#अन्यथा /* (!__ASSEMBLY__) */
#पूर्ण_अगर /* (!__ASSEMBLY__) */
#पूर्ण_अगर /* (defined(__sparc__) && defined(__arch64__)) */
#घोषणा STACK_BIAS		2047

/* global_reg_snapshot offsets */
#घोषणा GR_SNAP_TSTATE	0x00
#घोषणा GR_SNAP_TPC	0x08
#घोषणा GR_SNAP_TNPC	0x10
#घोषणा GR_SNAP_O7	0x18
#घोषणा GR_SNAP_I7	0x20
#घोषणा GR_SNAP_RPC	0x28
#घोषणा GR_SNAP_THREAD	0x30
#घोषणा GR_SNAP_PAD1	0x38

#पूर्ण_अगर /* !(__SPARC_PTRACE_H) */
