<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_HWEIGHT_H
#घोषणा _ASM_X86_HWEIGHT_H

#समावेश <यंत्र/cpufeatures.h>

#अगर_घोषित CONFIG_64BIT
#घोषणा REG_IN "D"
#घोषणा REG_OUT "a"
#अन्यथा
#घोषणा REG_IN "a"
#घोषणा REG_OUT "a"
#पूर्ण_अगर

अटल __always_अंतरभूत अचिन्हित पूर्णांक __arch_hweight32(अचिन्हित पूर्णांक w)
अणु
	अचिन्हित पूर्णांक res;

	यंत्र (ALTERNATIVE("call __sw_hweight32", "popcntl %1, %0", X86_FEATURE_POPCNT)
			 : "="REG_OUT (res)
			 : REG_IN (w));

	वापस res;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight16(अचिन्हित पूर्णांक w)
अणु
	वापस __arch_hweight32(w & 0xffff);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight8(अचिन्हित पूर्णांक w)
अणु
	वापस __arch_hweight32(w & 0xff);
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल अंतरभूत अचिन्हित दीर्घ __arch_hweight64(__u64 w)
अणु
	वापस  __arch_hweight32((u32)w) +
		__arch_hweight32((u32)(w >> 32));
पूर्ण
#अन्यथा
अटल __always_अंतरभूत अचिन्हित दीर्घ __arch_hweight64(__u64 w)
अणु
	अचिन्हित दीर्घ res;

	यंत्र (ALTERNATIVE("call __sw_hweight64", "popcntq %1, %0", X86_FEATURE_POPCNT)
			 : "="REG_OUT (res)
			 : REG_IN (w));

	वापस res;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */

#पूर्ण_अगर
