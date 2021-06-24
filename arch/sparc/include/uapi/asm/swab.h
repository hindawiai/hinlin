<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SPARC_SWAB_H
#घोषणा _SPARC_SWAB_H

#समावेश <linux/types.h>
#समावेश <यंत्र/asi.h>

#अगर defined(__sparc__) && defined(__arch64__)
अटल अंतरभूत __u16 __arch_swab16p(स्थिर __u16 *addr)
अणु
	__u16 ret;

	__यंत्र__ __अस्थिर__ ("lduha [%2] %3, %0"
			      : "=r" (ret)
			      : "m" (*addr), "r" (addr), "i" (ASI_PL));
	वापस ret;
पूर्ण
#घोषणा __arch_swab16p __arch_swab16p

अटल अंतरभूत __u32 __arch_swab32p(स्थिर __u32 *addr)
अणु
	__u32 ret;

	__यंत्र__ __अस्थिर__ ("lduwa [%2] %3, %0"
			      : "=r" (ret)
			      : "m" (*addr), "r" (addr), "i" (ASI_PL));
	वापस ret;
पूर्ण
#घोषणा __arch_swab32p __arch_swab32p

अटल अंतरभूत __u64 __arch_swab64p(स्थिर __u64 *addr)
अणु
	__u64 ret;

	__यंत्र__ __अस्थिर__ ("ldxa [%2] %3, %0"
			      : "=r" (ret)
			      : "m" (*addr), "r" (addr), "i" (ASI_PL));
	वापस ret;
पूर्ण
#घोषणा __arch_swab64p __arch_swab64p

#अन्यथा
#घोषणा __SWAB_64_THRU_32__
#पूर्ण_अगर /* defined(__sparc__) && defined(__arch64__) */

#पूर्ण_अगर /* _SPARC_SWAB_H */
