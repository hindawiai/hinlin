<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__ASM_SH_PTRACE_32_H
#घोषणा _UAPI__ASM_SH_PTRACE_32_H

/*
 * GCC defines रेजिस्टर number like this:
 * -----------------------------
 *	 0 - 15 are पूर्णांकeger रेजिस्टरs
 *	17 - 22 are control/special रेजिस्टरs
 *	24 - 39 fp रेजिस्टरs
 *	40 - 47 xd रेजिस्टरs
 *	48 -    fpscr रेजिस्टर
 * -----------------------------
 *
 * We follows above, except:
 *	16 --- program counter (PC)
 *	22 --- syscall #
 *	23 --- भग्नing poपूर्णांक communication रेजिस्टर
 */
#घोषणा REG_REG0	 0
#घोषणा REG_REG15	15

#घोषणा REG_PC		16

#घोषणा REG_PR		17
#घोषणा REG_SR		18
#घोषणा REG_GBR		19
#घोषणा REG_MACH	20
#घोषणा REG_MACL	21

#घोषणा REG_SYSCALL	22

#घोषणा REG_FPREG0	23
#घोषणा REG_FPREG15	38
#घोषणा REG_XFREG0	39
#घोषणा REG_XFREG15	54

#घोषणा REG_FPSCR	55
#घोषणा REG_FPUL	56

/*
 * This काष्ठा defines the way the रेजिस्टरs are stored on the
 * kernel stack during a प्रणाली call or other kernel entry.
 */
काष्ठा pt_regs अणु
	अचिन्हित दीर्घ regs[16];
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ pr;
	अचिन्हित दीर्घ sr;
	अचिन्हित दीर्घ gbr;
	अचिन्हित दीर्घ mach;
	अचिन्हित दीर्घ macl;
	दीर्घ tra;
पूर्ण;

/*
 * This काष्ठा defines the way the DSP रेजिस्टरs are stored on the
 * kernel stack during a प्रणाली call or other kernel entry.
 */
काष्ठा pt_dspregs अणु
	अचिन्हित दीर्घ	a1;
	अचिन्हित दीर्घ	a0g;
	अचिन्हित दीर्घ	a1g;
	अचिन्हित दीर्घ	m0;
	अचिन्हित दीर्घ	m1;
	अचिन्हित दीर्घ	a0;
	अचिन्हित दीर्घ	x0;
	अचिन्हित दीर्घ	x1;
	अचिन्हित दीर्घ	y0;
	अचिन्हित दीर्घ	y1;
	अचिन्हित दीर्घ	dsr;
	अचिन्हित दीर्घ	rs;
	अचिन्हित दीर्घ	re;
	अचिन्हित दीर्घ	mod;
पूर्ण;


#पूर्ण_अगर /* _UAPI__ASM_SH_PTRACE_32_H */
