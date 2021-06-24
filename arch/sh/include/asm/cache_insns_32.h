<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CACHE_INSNS_32_H
#घोषणा __ASM_SH_CACHE_INSNS_32_H

#समावेश <linux/types.h>

#अगर defined(CONFIG_CPU_SH4A)
#घोषणा __icbi(addr)	__यंत्र__ __अस्थिर__ ( "icbi @%0\n\t" : : "r" (addr))
#अन्यथा
#घोषणा __icbi(addr)	mb()
#पूर्ण_अगर

#घोषणा __ocbp(addr)	__यंत्र__ __अस्थिर__ ( "ocbp @%0\n\t" : : "r" (addr))
#घोषणा __ocbi(addr)	__यंत्र__ __अस्थिर__ ( "ocbi @%0\n\t" : : "r" (addr))
#घोषणा __ocbwb(addr)	__यंत्र__ __अस्थिर__ ( "ocbwb @%0\n\t" : : "r" (addr))

अटल अंतरभूत reg_माप_प्रकार रेजिस्टर_align(व्योम *val)
अणु
	वापस (अचिन्हित दीर्घ)(चिन्हित दीर्घ)val;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_CACHE_INSNS_32_H */
