<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_H8300_PTRACE_H
#घोषणा _UAPI_H8300_PTRACE_H

#अगर_अघोषित __ASSEMBLY__

#घोषणा PT_ER1	   0
#घोषणा PT_ER2	   1
#घोषणा PT_ER3	   2
#घोषणा PT_ER4	   3
#घोषणा PT_ER5	   4
#घोषणा PT_ER6	   5
#घोषणा PT_ER0	   6
#घोषणा PT_USP	   7
#घोषणा PT_ORIG_ER0	   8
#घोषणा PT_CCR	   9
#घोषणा PT_PC	   10
#घोषणा PT_EXR     11

/* this काष्ठा defines the way the रेजिस्टरs are stored on the
   stack during a प्रणाली call. */

काष्ठा pt_regs अणु
	दीर्घ     retpc;
	दीर्घ     er4;
	दीर्घ     er5;
	दीर्घ     er6;
	दीर्घ     er3;
	दीर्घ     er2;
	दीर्घ     er1;
	दीर्घ     orig_er0;
	दीर्घ	 sp;
	अचिन्हित लघु	 ccr;
	दीर्घ     er0;
	दीर्घ     vector;
#अगर defined(__H8300S__)
	अचिन्हित लघु	 exr;
#पूर्ण_अगर
	अचिन्हित दीर्घ  pc;
पूर्ण __attribute__((aligned(2), packed));

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _UAPI_H8300_PTRACE_H */
