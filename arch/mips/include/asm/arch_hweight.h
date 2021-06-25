<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 */
#अगर_अघोषित _ASM_ARCH_HWEIGHT_H
#घोषणा _ASM_ARCH_HWEIGHT_H

#अगर_घोषित ARCH_HAS_USABLE_BUILTIN_POPCOUNT

#समावेश <यंत्र/types.h>

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight32(अचिन्हित पूर्णांक w)
अणु
	वापस __builtin_popcount(w);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight16(अचिन्हित पूर्णांक w)
अणु
	वापस __builtin_popcount(w & 0xffff);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight8(अचिन्हित पूर्णांक w)
अणु
	वापस __builtin_popcount(w & 0xff);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __arch_hweight64(__u64 w)
अणु
	वापस __builtin_popcountll(w);
पूर्ण

#अन्यथा
#समावेश <यंत्र-generic/bitops/arch_hweight.h>
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_ARCH_HWEIGHT_H */
