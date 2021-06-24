<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_BUG_H
#घोषणा __ASM_CSKY_BUG_H

#समावेश <linux/compiler.h>
#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>

#घोषणा BUG()				\
करो अणु					\
	यंत्र अस्थिर ("bkpt\n");	\
	unreachable();			\
पूर्ण जबतक (0)

#घोषणा HAVE_ARCH_BUG

#समावेश <यंत्र-generic/bug.h>

काष्ठा pt_regs;

व्योम die(काष्ठा pt_regs *regs, स्थिर अक्षर *str);
व्योम करो_trap(काष्ठा pt_regs *regs, पूर्णांक signo, पूर्णांक code, अचिन्हित दीर्घ addr);

व्योम show_regs(काष्ठा pt_regs *regs);
व्योम show_code(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASM_CSKY_BUG_H */
