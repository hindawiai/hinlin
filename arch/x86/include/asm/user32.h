<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_USER32_H
#घोषणा _ASM_X86_USER32_H

/* IA32 compatible user काष्ठाures क्रम ptrace.
 * These should be used क्रम 32bit coredumps too. */

काष्ठा user_i387_ia32_काष्ठा अणु
	u32	cwd;
	u32	swd;
	u32	twd;
	u32	fip;
	u32	fcs;
	u32	foo;
	u32	fos;
	u32	st_space[20];   /* 8*10 bytes क्रम each FP-reg = 80 bytes */
पूर्ण;

/* FSAVE frame with extensions */
काष्ठा user32_fxsr_काष्ठा अणु
	अचिन्हित लघु	cwd;
	अचिन्हित लघु	swd;
	अचिन्हित लघु	twd;	/* not compatible to 64bit twd */
	अचिन्हित लघु	fop;
	पूर्णांक	fip;
	पूर्णांक	fcs;
	पूर्णांक	foo;
	पूर्णांक	fos;
	पूर्णांक	mxcsr;
	पूर्णांक	reserved;
	पूर्णांक	st_space[32];	/* 8*16 bytes क्रम each FP-reg = 128 bytes */
	पूर्णांक	xmm_space[32];	/* 8*16 bytes क्रम each XMM-reg = 128 bytes */
	पूर्णांक	padding[56];
पूर्ण;

काष्ठा user_regs_काष्ठा32 अणु
	__u32 ebx, ecx, edx, esi, edi, ebp, eax;
	अचिन्हित लघु ds, __ds, es, __es;
	अचिन्हित लघु fs, __fs, gs, __gs;
	__u32 orig_eax, eip;
	अचिन्हित लघु cs, __cs;
	__u32 eflags, esp;
	अचिन्हित लघु ss, __ss;
पूर्ण;

काष्ठा user32 अणु
  काष्ठा user_regs_काष्ठा32 regs; /* Where the रेजिस्टरs are actually stored */
  पूर्णांक u_fpvalid;		/* True अगर math co-processor being used. */
				/* क्रम this mess. Not yet used. */
  काष्ठा user_i387_ia32_काष्ठा i387;	/* Math Co-processor रेजिस्टरs. */
/* The rest of this junk is to help gdb figure out what goes where */
  __u32 u_tsize;	/* Text segment size (pages). */
  __u32 u_dsize;	/* Data segment size (pages). */
  __u32 u_ssize;	/* Stack segment size (pages). */
  __u32 start_code;     /* Starting भव address of text. */
  __u32 start_stack;	/* Starting भव address of stack area.
				   This is actually the bottom of the stack,
				   the top of the stack is always found in the
				   esp रेजिस्टर.  */
  __u32 संकेत;     		/* Signal that caused the core dump. */
  पूर्णांक reserved;			/* No __u32er used */
  __u32 u_ar0;	/* Used by gdb to help find the values क्रम */
				/* the रेजिस्टरs. */
  __u32 u_fpstate;	/* Math Co-processor poपूर्णांकer. */
  __u32 magic;		/* To uniquely identअगरy a core file */
  अक्षर u_comm[32];		/* User command that was responsible */
  पूर्णांक u_debugreg[8];
पूर्ण;


#पूर्ण_अगर /* _ASM_X86_USER32_H */
