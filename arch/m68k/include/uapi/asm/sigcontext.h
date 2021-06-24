<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_M68k_SIGCONTEXT_H
#घोषणा _ASM_M68k_SIGCONTEXT_H

काष्ठा sigcontext अणु
	अचिन्हित दीर्घ  sc_mask;		/* old sigmask */
	अचिन्हित दीर्घ  sc_usp;		/* old user stack poपूर्णांकer */
	अचिन्हित दीर्घ  sc_d0;
	अचिन्हित दीर्घ  sc_d1;
	अचिन्हित दीर्घ  sc_a0;
	अचिन्हित दीर्घ  sc_a1;
#अगर_घोषित __uClinux__
	अचिन्हित दीर्घ  sc_a5;
#पूर्ण_अगर
	अचिन्हित लघु sc_sr;
	अचिन्हित दीर्घ  sc_pc;
	अचिन्हित लघु sc_क्रमmatvec;
#अगर_अघोषित __uClinux__
	अचिन्हित दीर्घ  sc_fpregs[2*3];  /* room क्रम two fp रेजिस्टरs */
	अचिन्हित दीर्घ  sc_fpcntl[3];
	अचिन्हित अक्षर  sc_fpstate[216];
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
