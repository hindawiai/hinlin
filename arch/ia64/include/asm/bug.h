<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_BUG_H
#घोषणा _ASM_IA64_BUG_H

#अगर_घोषित CONFIG_BUG
#घोषणा ia64_पात()	__builtin_trap()
#घोषणा BUG() करो अणु						\
	prपूर्णांकk("kernel BUG at %s:%d!\n", __खाता__, __LINE__);	\
	barrier_beक्रमe_unreachable();				\
	ia64_पात();						\
पूर्ण जबतक (0)

/* should this BUG be made generic? */
#घोषणा HAVE_ARCH_BUG
#पूर्ण_अगर

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर
