<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_BUG_H
#घोषणा _ALPHA_BUG_H

#समावेश <linux/linkage.h>

#अगर_घोषित CONFIG_BUG
#समावेश <यंत्र/pal.h>

/* ??? Would be nice to use .gprel32 here, but we can't be sure that the
   function loaded the GP, so this could fail in modules.  */
#घोषणा BUG()	करो अणु							\
	__यंत्र__ __अस्थिर__(						\
		"call_pal %0  # bugchk\n\t"				\
		".long %1\n\t.8byte %2"					\
		: : "i"(PAL_bugchk), "i"(__LINE__), "i"(__खाता__));	\
	unreachable();							\
  पूर्ण जबतक (0)

#घोषणा HAVE_ARCH_BUG
#पूर्ण_अगर

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर
