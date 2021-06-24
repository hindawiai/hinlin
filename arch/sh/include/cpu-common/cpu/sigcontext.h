<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_CPU_SH2_SIGCONTEXT_H
#घोषणा __ASM_CPU_SH2_SIGCONTEXT_H

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
पूर्ण;

#पूर्ण_अगर /* __ASM_CPU_SH2_SIGCONTEXT_H */
