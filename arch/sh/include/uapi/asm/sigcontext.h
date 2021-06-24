<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_SH_SIGCONTEXT_H
#घोषणा __ASM_SH_SIGCONTEXT_H

काष्ठा sigcontext अणु
	अचिन्हित दीर्घ	oldmask;

	/* CPU रेजिस्टरs */
	अचिन्हित दीर्घ sc_regs[16];
	अचिन्हित दीर्घ sc_pc;
	अचिन्हित दीर्घ sc_pr;
	अचिन्हित दीर्घ sc_sr;
	अचिन्हित दीर्घ sc_gbr;
	अचिन्हित दीर्घ sc_mach;
	अचिन्हित दीर्घ sc_macl;

	/* FPU रेजिस्टरs */
	अचिन्हित दीर्घ sc_fpregs[16];
	अचिन्हित दीर्घ sc_xfpregs[16];
	अचिन्हित पूर्णांक sc_fpscr;
	अचिन्हित पूर्णांक sc_fpul;
	अचिन्हित पूर्णांक sc_ownedfp;
पूर्ण;

#पूर्ण_अगर /* __ASM_SH_SIGCONTEXT_H */
