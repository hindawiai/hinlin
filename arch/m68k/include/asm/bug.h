<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_BUG_H
#घोषणा _M68K_BUG_H

#अगर_घोषित CONFIG_MMU
#अगर_घोषित CONFIG_BUG
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#अगर_अघोषित CONFIG_SUN3
#घोषणा BUG() करो अणु \
	pr_crit("kernel BUG at %s:%d!\n", __खाता__, __LINE__); \
	barrier_beक्रमe_unreachable(); \
	__builtin_trap(); \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा BUG() करो अणु \
	pr_crit("kernel BUG at %s:%d!\n", __खाता__, __LINE__); \
	barrier_beक्रमe_unreachable(); \
	panic("BUG!"); \
पूर्ण जबतक (0)
#पूर्ण_अगर
#अन्यथा
#घोषणा BUG() करो अणु \
	barrier_beक्रमe_unreachable(); \
	__builtin_trap(); \
पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा HAVE_ARCH_BUG
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_MMU */

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर
