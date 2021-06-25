<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_DSEMUL_H__
#घोषणा __MIPS_ASM_DSEMUL_H__

#समावेश <यंत्र/अवरोध.h>
#समावेश <यंत्र/inst.h>

/* Break inकाष्ठाion with special math emu अवरोध code set */
#घोषणा BREAK_MATH(micromips)	(((micromips) ? 0x7 : 0xd) | (BRK_MEMU << 16))

/* When used as a frame index, indicates the lack of a frame */
#घोषणा BD_EMUFRAME_NONE	((पूर्णांक)BIT(31))

काष्ठा mm_काष्ठा;
काष्ठा pt_regs;
काष्ठा task_काष्ठा;

/**
 * mips_dsemul() - 'Emulate' an inकाष्ठाion from a branch delay slot
 * @regs:	User thपढ़ो रेजिस्टर context.
 * @ir:		The inकाष्ठाion to be 'emulated'.
 * @branch_pc:	The PC of the branch inकाष्ठाion.
 * @cont_pc:	The PC to जारी at following 'emulation'.
 *
 * Emulate or execute an arbitrary MIPS inकाष्ठाion within the context of
 * the current user thपढ़ो. This is used primarily to handle inकाष्ठाions
 * in the delay slots of emulated branch inकाष्ठाions, क्रम example FP
 * branch inकाष्ठाions on प्रणालीs without an FPU.
 *
 * Return: Zero on success, negative अगर ir is a NOP, संकेत number on failure.
 */
बाह्य पूर्णांक mips_dsemul(काष्ठा pt_regs *regs, mips_inकाष्ठाion ir,
		       अचिन्हित दीर्घ branch_pc, अचिन्हित दीर्घ cont_pc);

/**
 * करो_dsemulret() - Return from a delay slot 'emulation' frame
 * @xcp:	User thपढ़ो रेजिस्टर context.
 *
 * Call in response to the BRK_MEMU अवरोध inकाष्ठाion used to वापस to
 * the kernel from branch delay slot 'emulation' frames following a call
 * to mips_dsemul(). Restores the user thपढ़ो PC to the value that was
 * passed as the cpc parameter to mips_dsemul().
 *
 * Return: True अगर an emulation frame was वापसed from, अन्यथा false.
 */
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
बाह्य bool करो_dsemulret(काष्ठा pt_regs *xcp);
#अन्यथा
अटल अंतरभूत bool करो_dsemulret(काष्ठा pt_regs *xcp)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/**
 * dsemul_thपढ़ो_cleanup() - Cleanup thपढ़ो 'emulation' frame
 * @tsk: The task काष्ठाure associated with the thपढ़ो
 *
 * If the thपढ़ो @tsk has a branch delay slot 'emulation' frame
 * allocated to it then मुक्त that frame.
 *
 * Return: True अगर a frame was मुक्तd, अन्यथा false.
 */
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
बाह्य bool dsemul_thपढ़ो_cleanup(काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत bool dsemul_thपढ़ो_cleanup(काष्ठा task_काष्ठा *tsk)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
/**
 * dsemul_thपढ़ो_rollback() - Rollback from an 'emulation' frame
 * @regs:	User thपढ़ो रेजिस्टर context.
 *
 * If the current thपढ़ो, whose रेजिस्टर context is represented by @regs,
 * is executing within a delay slot 'emulation' frame then निकास that
 * frame. The PC will be rolled back to the branch अगर the inकाष्ठाion
 * that was being 'emulated' has not yet executed, or advanced to the
 * continuation PC अगर it has.
 *
 * Return: True अगर a frame was निकासed, अन्यथा false.
 */
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
बाह्य bool dsemul_thपढ़ो_rollback(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत bool dsemul_thपढ़ो_rollback(काष्ठा pt_regs *regs)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/**
 * dsemul_mm_cleanup() - Cleanup per-mm delay slot 'emulation' state
 * @mm:		The काष्ठा mm_काष्ठा to cleanup state क्रम.
 *
 * Cleanup state क्रम the given @mm, ensuring that any memory allocated
 * क्रम delay slot 'emulation' book-keeping is मुक्तd. This is to be called
 * beक्रमe @mm is मुक्तd in order to aव्योम memory leaks.
 */
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
बाह्य व्योम dsemul_mm_cleanup(काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत व्योम dsemul_mm_cleanup(काष्ठा mm_काष्ठा *mm)
अणु
	/* no-op */
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MIPS_ASM_DSEMUL_H__ */
