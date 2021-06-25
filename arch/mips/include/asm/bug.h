<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_BUG_H
#घोषणा __ASM_BUG_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/sgidefs.h>

#अगर_घोषित CONFIG_BUG

#समावेश <यंत्र/अवरोध.h>

अटल अंतरभूत व्योम __noवापस BUG(व्योम)
अणु
	__यंत्र__ __अस्थिर__("break %0" : : "i" (BRK_BUG));
	unreachable();
पूर्ण

#घोषणा HAVE_ARCH_BUG

#अगर (_MIPS_ISA > _MIPS_ISA_MIPS1)

अटल अंतरभूत व्योम  __BUG_ON(अचिन्हित दीर्घ condition)
अणु
	अगर (__builtin_स्थिरant_p(condition)) अणु
		अगर (condition)
			BUG();
		अन्यथा
			वापस;
	पूर्ण
	__यंत्र__ __अस्थिर__("tne $0, %0, %1"
			     : : "r" (condition), "i" (BRK_BUG));
पूर्ण

#घोषणा BUG_ON(C) __BUG_ON((अचिन्हित दीर्घ)(C))

#घोषणा HAVE_ARCH_BUG_ON

#पूर्ण_अगर /* _MIPS_ISA > _MIPS_ISA_MIPS1 */

#पूर्ण_अगर

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर /* __ASM_BUG_H */
