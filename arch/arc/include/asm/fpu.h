<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Synopsys, Inc. (www.synopsys.com)
 *
 */

#अगर_अघोषित _ASM_ARC_FPU_H
#घोषणा _ASM_ARC_FPU_H

#अगर_घोषित CONFIG_ARC_FPU_SAVE_RESTORE

#समावेश <यंत्र/ptrace.h>

#अगर_घोषित CONFIG_ISA_ARCOMPACT

/* These DPFP regs need to be saved/restored across ctx-sw */
काष्ठा arc_fpu अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक l, h;
	पूर्ण aux_dpfp[2];
पूर्ण;

#घोषणा fpu_init_task(regs)

#अन्यथा

/*
 * ARCv2 FPU Control aux रेजिस्टर
 *   - bits to enable Traps on Exceptions
 *   - Rounding mode
 *
 * ARCv2 FPU Status aux रेजिस्टर
 *   - FPU exceptions flags (Inv, Div-by-Zero, overflow, underflow, inexact)
 *   - Flag Write Enable to clear flags explicitly (vs. by fpu inकाष्ठाions
 *     only
 */

काष्ठा arc_fpu अणु
	अचिन्हित पूर्णांक ctrl, status;
पूर्ण;

बाह्य व्योम fpu_init_task(काष्ठा pt_regs *regs);

#पूर्ण_अगर	/* !CONFIG_ISA_ARCOMPACT */

काष्ठा task_काष्ठा;

बाह्य व्योम fpu_save_restore(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *n);

#अन्यथा	/* !CONFIG_ARC_FPU_SAVE_RESTORE */

#घोषणा fpu_save_restore(p, n)
#घोषणा fpu_init_task(regs)

#पूर्ण_अगर	/* CONFIG_ARC_FPU_SAVE_RESTORE */

#पूर्ण_अगर	/* _ASM_ARC_FPU_H */
