<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Compiler-dependent पूर्णांकrinsics.
 *
 * Copyright (C) 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#अगर_अघोषित _UAPI_ASM_IA64_INTRINSICS_H
#घोषणा _UAPI_ASM_IA64_INTRINSICS_H


#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
/* include compiler specअगरic पूर्णांकrinsics */
#समावेश <यंत्र/ia64regs.h>
#अगर_घोषित __INTEL_COMPILER
# include <यंत्र/पूर्णांकel_पूर्णांकrin.h>
#अन्यथा
# include <यंत्र/gcc_पूर्णांकrin.h>
#पूर्ण_अगर
#समावेश <यंत्र/cmpxchg.h>

#घोषणा ia64_set_rr0_to_rr4(val0, val1, val2, val3, val4)		\
करो अणु									\
	ia64_set_rr(0x0000000000000000UL, (val0));			\
	ia64_set_rr(0x2000000000000000UL, (val1));			\
	ia64_set_rr(0x4000000000000000UL, (val2));			\
	ia64_set_rr(0x6000000000000000UL, (val3));			\
	ia64_set_rr(0x8000000000000000UL, (val4));			\
पूर्ण जबतक (0)

/*
 * Force an unresolved reference अगर someone tries to use
 * ia64_fetch_and_add() with a bad value.
 */
बाह्य अचिन्हित दीर्घ __bad_size_क्रम_ia64_fetch_and_add (व्योम);
बाह्य अचिन्हित दीर्घ __bad_increment_क्रम_ia64_fetch_and_add (व्योम);

#घोषणा IA64_FETCHADD(पंचांगp,v,n,sz,sem)						\
(अणु										\
	चयन (sz) अणु								\
	      हाल 4:								\
	        पंचांगp = ia64_fetchadd4_##sem((अचिन्हित पूर्णांक *) v, n);		\
		अवरोध;								\
										\
	      हाल 8:								\
	        पंचांगp = ia64_fetchadd8_##sem((अचिन्हित दीर्घ *) v, n);		\
		अवरोध;								\
										\
	      शेष:								\
		__bad_size_क्रम_ia64_fetch_and_add();				\
	पूर्ण									\
पूर्ण)

#घोषणा ia64_fetchadd(i,v,sem)								\
(अणु											\
	__u64 _पंचांगp;									\
	अस्थिर __typeof__(*(v)) *_v = (v);						\
	/* Can't use a switch () here: gcc isn't always smart enough क्रम that... */	\
	अगर ((i) == -16)									\
		IA64_FETCHADD(_पंचांगp, _v, -16, माप(*(v)), sem);			\
	अन्यथा अगर ((i) == -8)								\
		IA64_FETCHADD(_पंचांगp, _v, -8, माप(*(v)), sem);				\
	अन्यथा अगर ((i) == -4)								\
		IA64_FETCHADD(_पंचांगp, _v, -4, माप(*(v)), sem);				\
	अन्यथा अगर ((i) == -1)								\
		IA64_FETCHADD(_पंचांगp, _v, -1, माप(*(v)), sem);				\
	अन्यथा अगर ((i) == 1)								\
		IA64_FETCHADD(_पंचांगp, _v, 1, माप(*(v)), sem);				\
	अन्यथा अगर ((i) == 4)								\
		IA64_FETCHADD(_पंचांगp, _v, 4, माप(*(v)), sem);				\
	अन्यथा अगर ((i) == 8)								\
		IA64_FETCHADD(_पंचांगp, _v, 8, माप(*(v)), sem);				\
	अन्यथा अगर ((i) == 16)								\
		IA64_FETCHADD(_पंचांगp, _v, 16, माप(*(v)), sem);				\
	अन्यथा										\
		_पंचांगp = __bad_increment_क्रम_ia64_fetch_and_add();			\
	(__typeof__(*(v))) (_पंचांगp);	/* वापस old value */				\
पूर्ण)

#घोषणा ia64_fetch_and_add(i,v)	(ia64_fetchadd(i, v, rel) + (i)) /* वापस new value */

#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_ASM_IA64_INTRINSICS_H */
