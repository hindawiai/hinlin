<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * x86 FPU संकेत frame handling methods:
 */
#अगर_अघोषित _ASM_X86_FPU_SIGNAL_H
#घोषणा _ASM_X86_FPU_SIGNAL_H

#अगर_घोषित CONFIG_X86_64
# include <uapi/यंत्र/sigcontext.h>
# include <यंत्र/user32.h>
काष्ठा kसंकेत;
पूर्णांक ia32_setup_rt_frame(पूर्णांक sig, काष्ठा kसंकेत *ksig,
			compat_sigset_t *set, काष्ठा pt_regs *regs);
पूर्णांक ia32_setup_frame(पूर्णांक sig, काष्ठा kसंकेत *ksig,
		     compat_sigset_t *set, काष्ठा pt_regs *regs);
#अन्यथा
# define user_i387_ia32_काष्ठा	user_i387_काष्ठा
# define user32_fxsr_काष्ठा	user_fxsr_काष्ठा
# define ia32_setup_frame	__setup_frame
# define ia32_setup_rt_frame	__setup_rt_frame
#पूर्ण_अगर

बाह्य व्योम convert_from_fxsr(काष्ठा user_i387_ia32_काष्ठा *env,
			      काष्ठा task_काष्ठा *tsk);
बाह्य व्योम convert_to_fxsr(काष्ठा fxregs_state *fxsave,
			    स्थिर काष्ठा user_i387_ia32_काष्ठा *env);

अचिन्हित दीर्घ
fpu__alloc_mathframe(अचिन्हित दीर्घ sp, पूर्णांक ia32_frame,
		     अचिन्हित दीर्घ *buf_fx, अचिन्हित दीर्घ *size);

बाह्य व्योम fpu__init_prepare_fx_sw_frame(व्योम);

#पूर्ण_अगर /* _ASM_X86_FPU_SIGNAL_H */
