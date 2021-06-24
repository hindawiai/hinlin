<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */
/*
 *  linux/arch/math-emu/driver.c.c
 *
 *	decodes and dispatches unimplemented FPU inकाष्ठाions
 *
 *  Copyright (C) 1999, 2000  Philipp Rumpf <prumpf@tux.org>
 *  Copyright (C) 2001	      Hewlett-Packard <bame@debian.org>
 */

#समावेश <linux/sched/संकेत.स>

#समावेश "float.h"
#समावेश "math-emu.h"


#घोषणा fptpos 31
#घोषणा fpr1pos 10
#घोषणा extru(r,pos,len) (((r) >> (31-(pos))) & (( 1 << (len)) - 1))

#घोषणा FPUDEBUG 0

/* Format of the भग्नing-poपूर्णांक exception रेजिस्टरs. */
काष्ठा exc_reg अणु
	अचिन्हित पूर्णांक exception : 6;
	अचिन्हित पूर्णांक ei : 26;
पूर्ण;

/* Macros क्रम grabbing bits of the inकाष्ठाion क्रमmat from the 'ei'
   field above. */
/* Major opcode 0c and 0e */
#घोषणा FP0CE_UID(i) (((i) >> 6) & 3)
#घोषणा FP0CE_CLASS(i) (((i) >> 9) & 3)
#घोषणा FP0CE_SUBOP(i) (((i) >> 13) & 7)
#घोषणा FP0CE_SUBOP1(i) (((i) >> 15) & 7) /* Class 1 subopcode */
#घोषणा FP0C_FORMAT(i) (((i) >> 11) & 3)
#घोषणा FP0E_FORMAT(i) (((i) >> 11) & 1)

/* Major opcode 0c, uid 2 (perक्रमmance monitoring) */
#घोषणा FPPM_SUBOP(i) (((i) >> 9) & 0x1f)

/* Major opcode 2e (fused operations).   */
#घोषणा FP2E_SUBOP(i)  (((i) >> 5) & 1)
#घोषणा FP2E_FORMAT(i) (((i) >> 11) & 1)

/* Major opcode 26 (FMPYSUB) */
/* Major opcode 06 (FMPYADD) */
#घोषणा FPx6_FORMAT(i) ((i) & 0x1f)

/* Flags and enable bits of the status word. */
#घोषणा FPSW_FLAGS(w) ((w) >> 27)
#घोषणा FPSW_ENABLE(w) ((w) & 0x1f)
#घोषणा FPSW_V (1<<4)
#घोषणा FPSW_Z (1<<3)
#घोषणा FPSW_O (1<<2)
#घोषणा FPSW_U (1<<1)
#घोषणा FPSW_I (1<<0)

/* Handle a भग्नing poपूर्णांक exception.  Return zero अगर the faulting
   inकाष्ठाion can be completed successfully. */
पूर्णांक
handle_fpe(काष्ठा pt_regs *regs)
अणु
	बाह्य व्योम prपूर्णांकbinary(अचिन्हित दीर्घ x, पूर्णांक nbits);
	अचिन्हित पूर्णांक orig_sw, sw;
	पूर्णांक संकेतcode;
	/* need an पूर्णांकermediate copy of भग्न regs because FPU emulation
	 * code expects an artअगरicial last entry which contains zero
	 *
	 * also, the passed in fr रेजिस्टरs contain one word that defines
	 * the fpu type. the fpu type inक्रमmation is स्थिरructed 
	 * inside the emulation code
	 */
	__u64 frcopy[36];

	स_नकल(frcopy, regs->fr, माप regs->fr);
	frcopy[32] = 0;

	स_नकल(&orig_sw, frcopy, माप(orig_sw));

	अगर (FPUDEBUG) अणु
		prपूर्णांकk(KERN_DEBUG "FP VZOUICxxxxCQCQCQCQCQCRMxxTDVZOUI ->\n   ");
		prपूर्णांकbinary(orig_sw, 32);
		prपूर्णांकk(KERN_DEBUG "\n");
	पूर्ण

	संकेतcode = decode_fpu(frcopy, 0x666);

	/* Status word = FR0L. */
	स_नकल(&sw, frcopy, माप(sw));
	अगर (FPUDEBUG) अणु
		prपूर्णांकk(KERN_DEBUG "VZOUICxxxxCQCQCQCQCQCRMxxTDVZOUI decode_fpu returns %d|0x%x\n",
			संकेतcode >> 24, संकेतcode & 0xffffff);
		prपूर्णांकbinary(sw, 32);
		prपूर्णांकk(KERN_DEBUG "\n");
	पूर्ण

	स_नकल(regs->fr, frcopy, माप regs->fr);
	अगर (संकेतcode != 0) अणु
	    क्रमce_sig_fault(संकेतcode >> 24, संकेतcode & 0xffffff,
			    (व्योम __user *) regs->iaoq[0]);
	    वापस -1;
	पूर्ण

	वापस संकेतcode ? -1 : 0;
पूर्ण
