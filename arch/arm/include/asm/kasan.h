<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/include/यंत्र/kasan.h
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 *
 */

#अगर_अघोषित __ASM_KASAN_H
#घोषणा __ASM_KASAN_H

#अगर_घोषित CONFIG_KASAN

#समावेश <यंत्र/kasan_def.h>

#घोषणा KASAN_SHADOW_SCALE_SHIFT 3

/*
 * The compiler uses a shaकरोw offset assuming that addresses start
 * from 0. Kernel addresses करोn't start from 0, so shaकरोw
 * क्रम kernel really starts from 'compiler's shadow offset' +
 * ('kernel address space start' >> KASAN_SHADOW_SCALE_SHIFT)
 */

यंत्रlinkage व्योम kasan_early_init(व्योम);
बाह्य व्योम kasan_init(व्योम);

#अन्यथा
अटल अंतरभूत व्योम kasan_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
