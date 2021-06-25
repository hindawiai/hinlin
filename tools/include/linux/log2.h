<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Integer base 2 logarithm calculation
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _TOOLS_LINUX_LOG2_H
#घोषणा _TOOLS_LINUX_LOG2_H

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>

/*
 * non-स्थिरant log of base 2 calculators
 * - the arch may override these in यंत्र/bitops.h अगर they can be implemented
 *   more efficiently than using fls() and fls64()
 * - the arch is not required to handle n==0 अगर implementing the fallback
 */
अटल अंतरभूत __attribute__((स्थिर))
पूर्णांक __ilog2_u32(u32 n)
अणु
	वापस fls(n) - 1;
पूर्ण

अटल अंतरभूत __attribute__((स्थिर))
पूर्णांक __ilog2_u64(u64 n)
अणु
	वापस fls64(n) - 1;
पूर्ण

/*
 *  Determine whether some value is a घातer of two, where zero is
 * *not* considered a घातer of two.
 */

अटल अंतरभूत __attribute__((स्थिर))
bool is_घातer_of_2(अचिन्हित दीर्घ n)
अणु
	वापस (n != 0 && ((n & (n - 1)) == 0));
पूर्ण

/*
 * round up to nearest घातer of two
 */
अटल अंतरभूत __attribute__((स्थिर))
अचिन्हित दीर्घ __roundup_घात_of_two(अचिन्हित दीर्घ n)
अणु
	वापस 1UL << fls_दीर्घ(n - 1);
पूर्ण

/*
 * round करोwn to nearest घातer of two
 */
अटल अंतरभूत __attribute__((स्थिर))
अचिन्हित दीर्घ __roundकरोwn_घात_of_two(अचिन्हित दीर्घ n)
अणु
	वापस 1UL << (fls_दीर्घ(n) - 1);
पूर्ण

/**
 * ilog2 - log of base 2 of 32-bit or a 64-bit अचिन्हित value
 * @n - parameter
 *
 * स्थिरant-capable log of base 2 calculation
 * - this can be used to initialise global variables from स्थिरant data, hence
 *   the massive ternary चालक स्थिरruction
 *
 * selects the appropriately-sized optimised version depending on माप(n)
 */
#घोषणा ilog2(n)				\
(						\
	__builtin_स्थिरant_p(n) ? (		\
		(n) < 2 ? 0 :			\
		(n) & (1ULL << 63) ? 63 :	\
		(n) & (1ULL << 62) ? 62 :	\
		(n) & (1ULL << 61) ? 61 :	\
		(n) & (1ULL << 60) ? 60 :	\
		(n) & (1ULL << 59) ? 59 :	\
		(n) & (1ULL << 58) ? 58 :	\
		(n) & (1ULL << 57) ? 57 :	\
		(n) & (1ULL << 56) ? 56 :	\
		(n) & (1ULL << 55) ? 55 :	\
		(n) & (1ULL << 54) ? 54 :	\
		(n) & (1ULL << 53) ? 53 :	\
		(n) & (1ULL << 52) ? 52 :	\
		(n) & (1ULL << 51) ? 51 :	\
		(n) & (1ULL << 50) ? 50 :	\
		(n) & (1ULL << 49) ? 49 :	\
		(n) & (1ULL << 48) ? 48 :	\
		(n) & (1ULL << 47) ? 47 :	\
		(n) & (1ULL << 46) ? 46 :	\
		(n) & (1ULL << 45) ? 45 :	\
		(n) & (1ULL << 44) ? 44 :	\
		(n) & (1ULL << 43) ? 43 :	\
		(n) & (1ULL << 42) ? 42 :	\
		(n) & (1ULL << 41) ? 41 :	\
		(n) & (1ULL << 40) ? 40 :	\
		(n) & (1ULL << 39) ? 39 :	\
		(n) & (1ULL << 38) ? 38 :	\
		(n) & (1ULL << 37) ? 37 :	\
		(n) & (1ULL << 36) ? 36 :	\
		(n) & (1ULL << 35) ? 35 :	\
		(n) & (1ULL << 34) ? 34 :	\
		(n) & (1ULL << 33) ? 33 :	\
		(n) & (1ULL << 32) ? 32 :	\
		(n) & (1ULL << 31) ? 31 :	\
		(n) & (1ULL << 30) ? 30 :	\
		(n) & (1ULL << 29) ? 29 :	\
		(n) & (1ULL << 28) ? 28 :	\
		(n) & (1ULL << 27) ? 27 :	\
		(n) & (1ULL << 26) ? 26 :	\
		(n) & (1ULL << 25) ? 25 :	\
		(n) & (1ULL << 24) ? 24 :	\
		(n) & (1ULL << 23) ? 23 :	\
		(n) & (1ULL << 22) ? 22 :	\
		(n) & (1ULL << 21) ? 21 :	\
		(n) & (1ULL << 20) ? 20 :	\
		(n) & (1ULL << 19) ? 19 :	\
		(n) & (1ULL << 18) ? 18 :	\
		(n) & (1ULL << 17) ? 17 :	\
		(n) & (1ULL << 16) ? 16 :	\
		(n) & (1ULL << 15) ? 15 :	\
		(n) & (1ULL << 14) ? 14 :	\
		(n) & (1ULL << 13) ? 13 :	\
		(n) & (1ULL << 12) ? 12 :	\
		(n) & (1ULL << 11) ? 11 :	\
		(n) & (1ULL << 10) ? 10 :	\
		(n) & (1ULL <<  9) ?  9 :	\
		(n) & (1ULL <<  8) ?  8 :	\
		(n) & (1ULL <<  7) ?  7 :	\
		(n) & (1ULL <<  6) ?  6 :	\
		(n) & (1ULL <<  5) ?  5 :	\
		(n) & (1ULL <<  4) ?  4 :	\
		(n) & (1ULL <<  3) ?  3 :	\
		(n) & (1ULL <<  2) ?  2 :	\
		1 ) :				\
	(माप(n) <= 4) ?			\
	__ilog2_u32(n) :			\
	__ilog2_u64(n)				\
 )

/**
 * roundup_घात_of_two - round the given value up to nearest घातer of two
 * @n - parameter
 *
 * round the given value up to the nearest घातer of two
 * - the result is undefined when n == 0
 * - this can be used to initialise global variables from स्थिरant data
 */
#घोषणा roundup_घात_of_two(n)			\
(						\
	__builtin_स्थिरant_p(n) ? (		\
		(n == 1) ? 1 :			\
		(1UL << (ilog2((n) - 1) + 1))	\
				   ) :		\
	__roundup_घात_of_two(n)			\
 )

/**
 * roundकरोwn_घात_of_two - round the given value करोwn to nearest घातer of two
 * @n - parameter
 *
 * round the given value करोwn to the nearest घातer of two
 * - the result is undefined when n == 0
 * - this can be used to initialise global variables from स्थिरant data
 */
#घोषणा roundकरोwn_घात_of_two(n)			\
(						\
	__builtin_स्थिरant_p(n) ? (		\
		(1UL << ilog2(n))) :		\
	__roundकरोwn_घात_of_two(n)		\
 )

#पूर्ण_अगर /* _TOOLS_LINUX_LOG2_H */
