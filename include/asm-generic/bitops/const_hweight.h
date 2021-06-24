<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_CONST_HWEIGHT_H_
#घोषणा _ASM_GENERIC_BITOPS_CONST_HWEIGHT_H_

/*
 * Compile समय versions of __arch_hweightN()
 */
#घोषणा __स्थिर_hweight8(w)		\
	((अचिन्हित पूर्णांक)			\
	 ((!!((w) & (1ULL << 0))) +	\
	  (!!((w) & (1ULL << 1))) +	\
	  (!!((w) & (1ULL << 2))) +	\
	  (!!((w) & (1ULL << 3))) +	\
	  (!!((w) & (1ULL << 4))) +	\
	  (!!((w) & (1ULL << 5))) +	\
	  (!!((w) & (1ULL << 6))) +	\
	  (!!((w) & (1ULL << 7)))))

#घोषणा __स्थिर_hweight16(w) (__स्थिर_hweight8(w)  + __स्थिर_hweight8((w)  >> 8 ))
#घोषणा __स्थिर_hweight32(w) (__स्थिर_hweight16(w) + __स्थिर_hweight16((w) >> 16))
#घोषणा __स्थिर_hweight64(w) (__स्थिर_hweight32(w) + __स्थिर_hweight32((w) >> 32))

/*
 * Generic पूर्णांकerface.
 */
#घोषणा hweight8(w)  (__builtin_स्थिरant_p(w) ? __स्थिर_hweight8(w)  : __arch_hweight8(w))
#घोषणा hweight16(w) (__builtin_स्थिरant_p(w) ? __स्थिर_hweight16(w) : __arch_hweight16(w))
#घोषणा hweight32(w) (__builtin_स्थिरant_p(w) ? __स्थिर_hweight32(w) : __arch_hweight32(w))
#घोषणा hweight64(w) (__builtin_स्थिरant_p(w) ? __स्थिर_hweight64(w) : __arch_hweight64(w))

/*
 * Interface क्रम known स्थिरant arguments
 */
#घोषणा HWEIGHT8(w)  (BUILD_BUG_ON_ZERO(!__builtin_स्थिरant_p(w)) + __स्थिर_hweight8(w))
#घोषणा HWEIGHT16(w) (BUILD_BUG_ON_ZERO(!__builtin_स्थिरant_p(w)) + __स्थिर_hweight16(w))
#घोषणा HWEIGHT32(w) (BUILD_BUG_ON_ZERO(!__builtin_स्थिरant_p(w)) + __स्थिर_hweight32(w))
#घोषणा HWEIGHT64(w) (BUILD_BUG_ON_ZERO(!__builtin_स्थिरant_p(w)) + __स्थिर_hweight64(w))

/*
 * Type invariant पूर्णांकerface to the compile समय स्थिरant hweight functions.
 */
#घोषणा HWEIGHT(w)   HWEIGHT64((u64)w)

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_CONST_HWEIGHT_H_ */
