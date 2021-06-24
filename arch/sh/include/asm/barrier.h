<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999, 2000  Niibe Yutaka  &  Kaz Kojima
 * Copyright (C) 2002 Paul Mundt
 */
#अगर_अघोषित __ASM_SH_BARRIER_H
#घोषणा __ASM_SH_BARRIER_H

#अगर defined(CONFIG_CPU_SH4A)
#समावेश <यंत्र/cache_insns.h>
#पूर्ण_अगर

/*
 * A brief note on ctrl_barrier(), the control रेजिस्टर ग_लिखो barrier.
 *
 * Legacy SH cores typically require a sequence of 8 nops after
 * modअगरication of a control रेजिस्टर in order क्रम the changes to take
 * effect. On newer cores (like the sh4a and sh5) this is accomplished
 * with icbi.
 *
 * Also note that on sh4a in the icbi हाल we can क्रमego a synco क्रम the
 * ग_लिखो barrier, as it's not necessary क्रम control रेजिस्टरs.
 *
 * Historically we have only करोne this type of barrier क्रम the MMUCR, but
 * it's also necessary क्रम the CCR, so we make it generic here instead.
 */
#अगर defined(CONFIG_CPU_SH4A)
#घोषणा mb()		__यंत्र__ __अस्थिर__ ("synco": : :"memory")
#घोषणा rmb()		mb()
#घोषणा wmb()		mb()
#घोषणा ctrl_barrier()	__icbi(PAGE_OFFSET)
#अन्यथा
#अगर defined(CONFIG_CPU_J2) && defined(CONFIG_SMP)
#घोषणा __smp_mb()	करो अणु पूर्णांक पंचांगp = 0; __यंत्र__ __अस्थिर__ ("cas.l %0,%0,@%1" : "+r"(पंचांगp) : "z"(&पंचांगp) : "memory", "t"); पूर्ण जबतक(0)
#घोषणा __smp_rmb()	__smp_mb()
#घोषणा __smp_wmb()	__smp_mb()
#पूर्ण_अगर
#घोषणा ctrl_barrier()	__यंत्र__ __अस्थिर__ ("nop;nop;nop;nop;nop;nop;nop;nop")
#पूर्ण_अगर

#घोषणा __smp_store_mb(var, value) करो अणु (व्योम)xchg(&var, value); पूर्ण जबतक (0)

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* __ASM_SH_BARRIER_H */
