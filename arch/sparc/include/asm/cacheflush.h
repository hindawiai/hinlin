<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ___ASM_SPARC_CACHEFLUSH_H
#घोषणा ___ASM_SPARC_CACHEFLUSH_H

/* flush addr - to allow use of self-modअगरying code */
#घोषणा flushi(addr)	__यंत्र__ __अस्थिर__ ("flush %0" : : "r" (addr) : "memory")

#अगर defined(__sparc__) && defined(__arch64__)
#समावेश <यंत्र/cacheflush_64.h>
#अन्यथा
#समावेश <यंत्र/cacheflush_32.h>
#पूर्ण_अगर
#पूर्ण_अगर
