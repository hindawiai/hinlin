<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_M68K_PTRACE_H
#घोषणा _UAPI_M68K_PTRACE_H

#घोषणा PT_D1	   0
#घोषणा PT_D2	   1
#घोषणा PT_D3	   2
#घोषणा PT_D4	   3
#घोषणा PT_D5	   4
#घोषणा PT_D6	   5
#घोषणा PT_D7	   6
#घोषणा PT_A0	   7
#घोषणा PT_A1	   8
#घोषणा PT_A2	   9
#घोषणा PT_A3	   10
#घोषणा PT_A4	   11
#घोषणा PT_A5	   12
#घोषणा PT_A6	   13
#घोषणा PT_D0	   14
#घोषणा PT_USP	   15
#घोषणा PT_ORIG_D0 16
#घोषणा PT_SR	   17
#घोषणा PT_PC	   18

#अगर_अघोषित __ASSEMBLY__

/* this काष्ठा defines the way the रेजिस्टरs are stored on the
   stack during a प्रणाली call. */

काष्ठा pt_regs अणु
  दीर्घ     d1;
  दीर्घ     d2;
  दीर्घ     d3;
  दीर्घ     d4;
  दीर्घ     d5;
  दीर्घ     a0;
  दीर्घ     a1;
  दीर्घ     a2;
  दीर्घ     d0;
  दीर्घ     orig_d0;
  दीर्घ     stkadj;
#अगर_घोषित CONFIG_COLDFIRE
  अचिन्हित क्रमmat :  4; /* frame क्रमmat specअगरier */
  अचिन्हित vector : 12; /* vector offset */
  अचिन्हित लघु sr;
  अचिन्हित दीर्घ  pc;
#अन्यथा
  अचिन्हित लघु sr;
  अचिन्हित दीर्घ  pc;
  अचिन्हित क्रमmat :  4; /* frame क्रमmat specअगरier */
  अचिन्हित vector : 12; /* vector offset */
#पूर्ण_अगर
पूर्ण;

/*
 * This is the extended stack used by संकेत handlers and the context
 * चयनer: it's pushed after the normal "struct pt_regs".
 */
काष्ठा चयन_stack अणु
	अचिन्हित दीर्घ  d6;
	अचिन्हित दीर्घ  d7;
	अचिन्हित दीर्घ  a3;
	अचिन्हित दीर्घ  a4;
	अचिन्हित दीर्घ  a5;
	अचिन्हित दीर्घ  a6;
	अचिन्हित दीर्घ  retpc;
पूर्ण;

/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
#घोषणा PTRACE_GETREGS            12
#घोषणा PTRACE_SETREGS            13
#घोषणा PTRACE_GETFPREGS          14
#घोषणा PTRACE_SETFPREGS          15

#घोषणा PTRACE_GET_THREAD_AREA    25

#घोषणा PTRACE_SINGLEBLOCK	33	/* resume execution until next branch */

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _UAPI_M68K_PTRACE_H */
