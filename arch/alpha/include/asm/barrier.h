<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BARRIER_H
#घोषणा __BARRIER_H

#घोषणा mb()	__यंत्र__ __अस्थिर__("mb": : :"memory")
#घोषणा rmb()	__यंत्र__ __अस्थिर__("mb": : :"memory")
#घोषणा wmb()	__यंत्र__ __अस्थिर__("wmb": : :"memory")

#घोषणा __smp_load_acquire(p)						\
(अणु									\
	compileसमय_निश्चित_atomic_type(*p);				\
	__READ_ONCE(*p);						\
पूर्ण)

#अगर_घोषित CONFIG_SMP
#घोषणा __ASM_SMP_MB	"\tmb\n"
#अन्यथा
#घोषणा __ASM_SMP_MB
#पूर्ण_अगर

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर		/* __BARRIER_H */
