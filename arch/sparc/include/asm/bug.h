<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_BUG_H
#घोषणा _SPARC_BUG_H

#अगर_घोषित CONFIG_BUG
#समावेश <linux/compiler.h>

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
व्योम करो_BUG(स्थिर अक्षर *file, पूर्णांक line);
#घोषणा BUG() करो अणु					\
	करो_BUG(__खाता__, __LINE__);			\
	barrier_beक्रमe_unreachable();			\
	__builtin_trap();				\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा BUG() करो अणु					\
	barrier_beक्रमe_unreachable();			\
	__builtin_trap();				\
पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा HAVE_ARCH_BUG
#पूर्ण_अगर

#समावेश <यंत्र-generic/bug.h>

काष्ठा pt_regs;
व्योम __noवापस die_अगर_kernel(अक्षर *str, काष्ठा pt_regs *regs);

#पूर्ण_अगर
