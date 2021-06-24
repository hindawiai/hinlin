<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* fpumacro.h: FPU related macros.
 *
 * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC64_FPUMACRO_H
#घोषणा _SPARC64_FPUMACRO_H

#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/visयंत्र.h>

काष्ठा fpustate अणु
	u32	regs[64];
पूर्ण;

#घोषणा FPUSTATE (काष्ठा fpustate *)(current_thपढ़ो_info()->fpregs)

अटल अंतरभूत अचिन्हित दीर्घ fprs_पढ़ो(व्योम)
अणु
	अचिन्हित दीर्घ retval;

	__यंत्र__ __अस्थिर__("rd %%fprs, %0" : "=r" (retval));

	वापस retval;
पूर्ण

अटल अंतरभूत व्योम fprs_ग_लिखो(अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__("wr %0, 0x0, %%fprs" : : "r" (val));
पूर्ण

#पूर्ण_अगर /* !(_SPARC64_FPUMACRO_H) */
