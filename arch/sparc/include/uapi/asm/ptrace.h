<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__SPARC_PTRACE_H
#घोषणा _UAPI__SPARC_PTRACE_H

#अगर defined(__sparc__) && defined(__arch64__)
/* 64 bit sparc */
#समावेश <यंत्र/pstate.h>

/* This काष्ठा defines the way the रेजिस्टरs are stored on the
 * stack during a प्रणाली call and basically all traps.
 */

/* This magic value must have the low 9 bits clear,
 * as that is where we encode the %tt value, see below.
 */
#घोषणा PT_REGS_MAGIC 0x57ac6c00

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

काष्ठा pt_regs अणु
	अचिन्हित दीर्घ u_regs[16]; /* globals and ins */
	अचिन्हित दीर्घ tstate;
	अचिन्हित दीर्घ tpc;
	अचिन्हित दीर्घ tnpc;
	अचिन्हित पूर्णांक y;

	/* We encode a magic number, PT_REGS_MAGIC, aदीर्घ
	 * with the %tt (trap type) रेजिस्टर value at trap
	 * entry समय.  The magic number allows us to identअगरy
	 * accurately a trap stack frame in the stack
	 * unwinder, and the %tt value allows us to test
	 * things like "in a system call" etc. क्रम an arbitray
	 * process.
	 *
	 * The PT_REGS_MAGIC is chosen such that it can be
	 * loaded completely using just a sethi inकाष्ठाion.
	 */
	अचिन्हित पूर्णांक magic;
पूर्ण;

काष्ठा pt_regs32 अणु
	अचिन्हित पूर्णांक psr;
	अचिन्हित पूर्णांक pc;
	अचिन्हित पूर्णांक npc;
	अचिन्हित पूर्णांक y;
	अचिन्हित पूर्णांक u_regs[16]; /* globals and ins */
पूर्ण;

/* A V9 रेजिस्टर winकरोw */
काष्ठा reg_winकरोw अणु
	अचिन्हित दीर्घ locals[8];
	अचिन्हित दीर्घ ins[8];
पूर्ण;

/* A 32-bit रेजिस्टर winकरोw. */
काष्ठा reg_winकरोw32 अणु
	अचिन्हित पूर्णांक locals[8];
	अचिन्हित पूर्णांक ins[8];
पूर्ण;

/* A V9 Sparc stack frame */
काष्ठा sparc_stackf अणु
	अचिन्हित दीर्घ locals[8];
        अचिन्हित दीर्घ ins[6];
	काष्ठा sparc_stackf *fp;
	अचिन्हित दीर्घ callers_pc;
	अक्षर *काष्ठाptr;
	अचिन्हित दीर्घ xargs[6];
	अचिन्हित दीर्घ xxargs[1];
पूर्ण;

/* A 32-bit Sparc stack frame */
काष्ठा sparc_stackf32 अणु
	अचिन्हित पूर्णांक locals[8];
        अचिन्हित पूर्णांक ins[6];
	अचिन्हित पूर्णांक fp;
	अचिन्हित पूर्णांक callers_pc;
	अचिन्हित पूर्णांक काष्ठाptr;
	अचिन्हित पूर्णांक xargs[6];
	अचिन्हित पूर्णांक xxargs[1];
पूर्ण;

काष्ठा sparc_trapf अणु
	अचिन्हित दीर्घ locals[8];
	अचिन्हित दीर्घ ins[8];
	अचिन्हित दीर्घ _unused;
	काष्ठा pt_regs *regs;
पूर्ण;
#पूर्ण_अगर /* (!__ASSEMBLY__) */
#अन्यथा
/* 32 bit sparc */

#समावेश <यंत्र/psr.h>

/* This काष्ठा defines the way the रेजिस्टरs are stored on the
 * stack during a प्रणाली call and basically all traps.
 */
#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

काष्ठा pt_regs अणु
	अचिन्हित दीर्घ psr;
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ npc;
	अचिन्हित दीर्घ y;
	अचिन्हित दीर्घ u_regs[16]; /* globals and ins */
पूर्ण;

/* A 32-bit रेजिस्टर winकरोw. */
काष्ठा reg_winकरोw32 अणु
	अचिन्हित दीर्घ locals[8];
	अचिन्हित दीर्घ ins[8];
पूर्ण;

/* A Sparc stack frame */
काष्ठा sparc_stackf अणु
	अचिन्हित दीर्घ locals[8];
        अचिन्हित दीर्घ ins[6];
	काष्ठा sparc_stackf *fp;
	अचिन्हित दीर्घ callers_pc;
	अक्षर *काष्ठाptr;
	अचिन्हित दीर्घ xargs[6];
	अचिन्हित दीर्घ xxargs[1];
पूर्ण;
#पूर्ण_अगर /* (!__ASSEMBLY__) */

#पूर्ण_अगर /* (defined(__sparc__) && defined(__arch64__))*/

#अगर_अघोषित __ASSEMBLY__

#घोषणा TRACEREG_SZ	माप(काष्ठा pt_regs)
#घोषणा STACKFRAME_SZ	माप(काष्ठा sparc_stackf)

#घोषणा TRACEREG32_SZ	माप(काष्ठा pt_regs32)
#घोषणा STACKFRAME32_SZ	माप(काष्ठा sparc_stackf32)

#पूर्ण_अगर /* (!__ASSEMBLY__) */

#घोषणा UREG_G0        0
#घोषणा UREG_G1        1
#घोषणा UREG_G2        2
#घोषणा UREG_G3        3
#घोषणा UREG_G4        4
#घोषणा UREG_G5        5
#घोषणा UREG_G6        6
#घोषणा UREG_G7        7
#घोषणा UREG_I0        8
#घोषणा UREG_I1        9
#घोषणा UREG_I2        10
#घोषणा UREG_I3        11
#घोषणा UREG_I4        12
#घोषणा UREG_I5        13
#घोषणा UREG_I6        14
#घोषणा UREG_I7        15
#घोषणा UREG_FP        UREG_I6
#घोषणा UREG_RETPC     UREG_I7

#अगर defined(__sparc__) && defined(__arch64__)
/* 64 bit sparc */

#अगर_अघोषित __ASSEMBLY__


#अन्यथा /* __ASSEMBLY__ */
/* For assembly code. */
#घोषणा TRACEREG_SZ		0xa0
#घोषणा STACKFRAME_SZ		0xc0

#घोषणा TRACEREG32_SZ		0x50
#घोषणा STACKFRAME32_SZ		0x60
#पूर्ण_अगर /* __ASSEMBLY__ */

#अन्यथा /* (defined(__sparc__) && defined(__arch64__)) */

/* 32 bit sparc */

#अगर_अघोषित __ASSEMBLY__


#अन्यथा /* (!__ASSEMBLY__) */
/* For assembly code. */
#घोषणा TRACEREG_SZ       0x50
#घोषणा STACKFRAME_SZ     0x60
#पूर्ण_अगर /* (!__ASSEMBLY__) */

#पूर्ण_अगर /* (defined(__sparc__) && defined(__arch64__)) */


/* These are क्रम pt_regs. */
#घोषणा PT_V9_G0     0x00
#घोषणा PT_V9_G1     0x08
#घोषणा PT_V9_G2     0x10
#घोषणा PT_V9_G3     0x18
#घोषणा PT_V9_G4     0x20
#घोषणा PT_V9_G5     0x28
#घोषणा PT_V9_G6     0x30
#घोषणा PT_V9_G7     0x38
#घोषणा PT_V9_I0     0x40
#घोषणा PT_V9_I1     0x48
#घोषणा PT_V9_I2     0x50
#घोषणा PT_V9_I3     0x58
#घोषणा PT_V9_I4     0x60
#घोषणा PT_V9_I5     0x68
#घोषणा PT_V9_I6     0x70
#घोषणा PT_V9_FP     PT_V9_I6
#घोषणा PT_V9_I7     0x78
#घोषणा PT_V9_TSTATE 0x80
#घोषणा PT_V9_TPC    0x88
#घोषणा PT_V9_TNPC   0x90
#घोषणा PT_V9_Y      0x98
#घोषणा PT_V9_MAGIC  0x9c
#घोषणा PT_TSTATE	PT_V9_TSTATE
#घोषणा PT_TPC		PT_V9_TPC
#घोषणा PT_TNPC		PT_V9_TNPC

/* These क्रम pt_regs32. */
#घोषणा PT_PSR    0x0
#घोषणा PT_PC     0x4
#घोषणा PT_NPC    0x8
#घोषणा PT_Y      0xc
#घोषणा PT_G0     0x10
#घोषणा PT_WIM    PT_G0
#घोषणा PT_G1     0x14
#घोषणा PT_G2     0x18
#घोषणा PT_G3     0x1c
#घोषणा PT_G4     0x20
#घोषणा PT_G5     0x24
#घोषणा PT_G6     0x28
#घोषणा PT_G7     0x2c
#घोषणा PT_I0     0x30
#घोषणा PT_I1     0x34
#घोषणा PT_I2     0x38
#घोषणा PT_I3     0x3c
#घोषणा PT_I4     0x40
#घोषणा PT_I5     0x44
#घोषणा PT_I6     0x48
#घोषणा PT_FP     PT_I6
#घोषणा PT_I7     0x4c

/* Reg_winकरोw offsets */
#घोषणा RW_V9_L0     0x00
#घोषणा RW_V9_L1     0x08
#घोषणा RW_V9_L2     0x10
#घोषणा RW_V9_L3     0x18
#घोषणा RW_V9_L4     0x20
#घोषणा RW_V9_L5     0x28
#घोषणा RW_V9_L6     0x30
#घोषणा RW_V9_L7     0x38
#घोषणा RW_V9_I0     0x40
#घोषणा RW_V9_I1     0x48
#घोषणा RW_V9_I2     0x50
#घोषणा RW_V9_I3     0x58
#घोषणा RW_V9_I4     0x60
#घोषणा RW_V9_I5     0x68
#घोषणा RW_V9_I6     0x70
#घोषणा RW_V9_I7     0x78

#घोषणा RW_L0     0x00
#घोषणा RW_L1     0x04
#घोषणा RW_L2     0x08
#घोषणा RW_L3     0x0c
#घोषणा RW_L4     0x10
#घोषणा RW_L5     0x14
#घोषणा RW_L6     0x18
#घोषणा RW_L7     0x1c
#घोषणा RW_I0     0x20
#घोषणा RW_I1     0x24
#घोषणा RW_I2     0x28
#घोषणा RW_I3     0x2c
#घोषणा RW_I4     0x30
#घोषणा RW_I5     0x34
#घोषणा RW_I6     0x38
#घोषणा RW_I7     0x3c

/* Stack_frame offsets */
#घोषणा SF_V9_L0     0x00
#घोषणा SF_V9_L1     0x08
#घोषणा SF_V9_L2     0x10
#घोषणा SF_V9_L3     0x18
#घोषणा SF_V9_L4     0x20
#घोषणा SF_V9_L5     0x28
#घोषणा SF_V9_L6     0x30
#घोषणा SF_V9_L7     0x38
#घोषणा SF_V9_I0     0x40
#घोषणा SF_V9_I1     0x48
#घोषणा SF_V9_I2     0x50
#घोषणा SF_V9_I3     0x58
#घोषणा SF_V9_I4     0x60
#घोषणा SF_V9_I5     0x68
#घोषणा SF_V9_FP     0x70
#घोषणा SF_V9_PC     0x78
#घोषणा SF_V9_RETP   0x80
#घोषणा SF_V9_XARG0  0x88
#घोषणा SF_V9_XARG1  0x90
#घोषणा SF_V9_XARG2  0x98
#घोषणा SF_V9_XARG3  0xa0
#घोषणा SF_V9_XARG4  0xa8
#घोषणा SF_V9_XARG5  0xb0
#घोषणा SF_V9_XXARG  0xb8

#घोषणा SF_L0     0x00
#घोषणा SF_L1     0x04
#घोषणा SF_L2     0x08
#घोषणा SF_L3     0x0c
#घोषणा SF_L4     0x10
#घोषणा SF_L5     0x14
#घोषणा SF_L6     0x18
#घोषणा SF_L7     0x1c
#घोषणा SF_I0     0x20
#घोषणा SF_I1     0x24
#घोषणा SF_I2     0x28
#घोषणा SF_I3     0x2c
#घोषणा SF_I4     0x30
#घोषणा SF_I5     0x34
#घोषणा SF_FP     0x38
#घोषणा SF_PC     0x3c
#घोषणा SF_RETP   0x40
#घोषणा SF_XARG0  0x44
#घोषणा SF_XARG1  0x48
#घोषणा SF_XARG2  0x4c
#घोषणा SF_XARG3  0x50
#घोषणा SF_XARG4  0x54
#घोषणा SF_XARG5  0x58
#घोषणा SF_XXARG  0x5c


/* Stuff क्रम the ptrace प्रणाली call */
#घोषणा PTRACE_SPARC_DETACH       11
#घोषणा PTRACE_GETREGS            12
#घोषणा PTRACE_SETREGS            13
#घोषणा PTRACE_GETFPREGS          14
#घोषणा PTRACE_SETFPREGS          15
#घोषणा PTRACE_READDATA           16
#घोषणा PTRACE_WRITEDATA          17
#घोषणा PTRACE_READTEXT           18
#घोषणा PTRACE_WRITETEXT          19
#घोषणा PTRACE_GETFPAREGS         20
#घोषणा PTRACE_SETFPAREGS         21

/* There are क्रम debugging 64-bit processes, either from a 32 or 64 bit
 * parent.  Thus their complements are क्रम debugging 32-bit processes only.
 */

#घोषणा PTRACE_GETREGS64	  22
#घोषणा PTRACE_SETREGS64	  23
/* PTRACE_SYSCALL is 24 */
#घोषणा PTRACE_GETFPREGS64	  25
#घोषणा PTRACE_SETFPREGS64	  26

#पूर्ण_अगर /* _UAPI__SPARC_PTRACE_H */
