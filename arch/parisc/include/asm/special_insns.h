<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PARISC_SPECIAL_INSNS_H
#घोषणा __PARISC_SPECIAL_INSNS_H

#घोषणा lpa(va)	(अणु			\
	अचिन्हित दीर्घ pa;		\
	__यंत्र__ __अस्थिर__(		\
		"copy %%r0,%0\n\t"	\
		"lpa %%r0(%1),%0"	\
		: "=r" (pa)		\
		: "r" (va)		\
		: "memory"		\
	);				\
	pa;				\
पूर्ण)

#घोषणा lpa_user(va)	(अणु		\
	अचिन्हित दीर्घ pa;		\
	__यंत्र__ __अस्थिर__(		\
		"copy %%r0,%0\n\t"	\
		"lpa %%r0(%%sr3,%1),%0"	\
		: "=r" (pa)		\
		: "r" (va)		\
		: "memory"		\
	);				\
	pa;				\
पूर्ण)

#घोषणा mfctl(reg)	(अणु		\
	अचिन्हित दीर्घ cr;		\
	__यंत्र__ __अस्थिर__(		\
		"mfctl " #reg ",%0" :	\
		 "=r" (cr)		\
	);				\
	cr;				\
पूर्ण)

#घोषणा mtctl(gr, cr) \
	__यंत्र__ __अस्थिर__("mtctl %0,%1" \
		: /* no outमाला_दो */ \
		: "r" (gr), "i" (cr) : "memory")

/* these are here to de-mystefy the calling code, and to provide hooks */
/* which I needed क्रम debugging EIEM problems -PB */
#घोषणा get_eiem() mfctl(15)
अटल अंतरभूत व्योम set_eiem(अचिन्हित दीर्घ val)
अणु
	mtctl(val, 15);
पूर्ण

#घोषणा mfsp(reg)	(अणु		\
	अचिन्हित दीर्घ cr;		\
	__यंत्र__ __अस्थिर__(		\
		"mfsp " #reg ",%0" :	\
		 "=r" (cr)		\
	);				\
	cr;				\
पूर्ण)

#घोषणा mtsp(val, cr) \
	अणु अगर (__builtin_स्थिरant_p(val) && ((val) == 0)) \
	 __यंत्र__ __अस्थिर__("mtsp %%r0,%0" : : "i" (cr) : "memory"); \
	अन्यथा \
	 __यंत्र__ __अस्थिर__("mtsp %0,%1" \
		: /* no outमाला_दो */ \
		: "r" (val), "i" (cr) : "memory"); पूर्ण

#पूर्ण_अगर /* __PARISC_SPECIAL_INSNS_H */
