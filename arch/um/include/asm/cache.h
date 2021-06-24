<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_CACHE_H
#घोषणा __UM_CACHE_H


#अगर defined(CONFIG_UML_X86) && !defined(CONFIG_64BIT)
# define L1_CACHE_SHIFT		(CONFIG_X86_L1_CACHE_SHIFT)
#या_अगर defined(CONFIG_UML_X86) /* 64-bit */
# define L1_CACHE_SHIFT		6 /* Should be 7 on Intel */
#अन्यथा
/* XXX: this was taken from x86, now it's completely अक्रमom. Luckily only
 * affects SMP padding. */
# define L1_CACHE_SHIFT		5
#पूर्ण_अगर

#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

#पूर्ण_अगर
