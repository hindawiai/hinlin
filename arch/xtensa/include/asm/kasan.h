<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_KASAN_H
#घोषणा __ASM_KASAN_H

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_KASAN

#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/kmem_layout.h>

#घोषणा KASAN_SHADOW_SCALE_SHIFT 3

/* Start of area covered by KASAN */
#घोषणा KASAN_START_VADDR __XTENSA_UL_CONST(0x90000000)
/* Start of the shaकरोw map */
#घोषणा KASAN_SHADOW_START (XCHAL_PAGE_TABLE_VADDR + XCHAL_PAGE_TABLE_SIZE)
/* Size of the shaकरोw map */
#घोषणा KASAN_SHADOW_SIZE (-KASAN_START_VADDR >> KASAN_SHADOW_SCALE_SHIFT)
/* Offset क्रम mem to shaकरोw address transक्रमmation */
#घोषणा KASAN_SHADOW_OFFSET __XTENSA_UL_CONST(CONFIG_KASAN_SHADOW_OFFSET)

व्योम __init kasan_early_init(व्योम);
व्योम __init kasan_init(व्योम);

#अन्यथा

अटल अंतरभूत व्योम kasan_early_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम kasan_init(व्योम)
अणु
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
