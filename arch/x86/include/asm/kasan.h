<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_KASAN_H
#घोषणा _ASM_X86_KASAN_H

#समावेश <linux/स्थिर.h>
#घोषणा KASAN_SHADOW_OFFSET _AC(CONFIG_KASAN_SHADOW_OFFSET, UL)
#घोषणा KASAN_SHADOW_SCALE_SHIFT 3

/*
 * Compiler uses shaकरोw offset assuming that addresses start
 * from 0. Kernel addresses करोn't start from 0, so shaकरोw
 * क्रम kernel really starts from compiler's shaकरोw offset +
 * 'kernel address space start' >> KASAN_SHADOW_SCALE_SHIFT
 */
#घोषणा KASAN_SHADOW_START      (KASAN_SHADOW_OFFSET + \
					((-1UL << __VIRTUAL_MASK_SHIFT) >> \
						KASAN_SHADOW_SCALE_SHIFT))
/*
 * 47 bits क्रम kernel address -> (47 - KASAN_SHADOW_SCALE_SHIFT) bits क्रम shaकरोw
 * 56 bits क्रम kernel address -> (56 - KASAN_SHADOW_SCALE_SHIFT) bits क्रम shaकरोw
 */
#घोषणा KASAN_SHADOW_END        (KASAN_SHADOW_START + \
					(1ULL << (__VIRTUAL_MASK_SHIFT - \
						  KASAN_SHADOW_SCALE_SHIFT)))

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_KASAN
व्योम __init kasan_early_init(व्योम);
व्योम __init kasan_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kasan_early_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर
