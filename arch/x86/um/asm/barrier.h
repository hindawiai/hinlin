<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_UM_BARRIER_H_
#घोषणा _ASM_UM_BARRIER_H_

#समावेश <यंत्र/alternative.h>

/*
 * Force strict CPU ordering.
 * And yes, this is required on UP too when we're talking
 * to devices.
 */
#अगर_घोषित CONFIG_X86_32

#घोषणा mb()	alternative("lock; addl $0,0(%%esp)", "mfence", X86_FEATURE_XMM2)
#घोषणा rmb()	alternative("lock; addl $0,0(%%esp)", "lfence", X86_FEATURE_XMM2)
#घोषणा wmb()	alternative("lock; addl $0,0(%%esp)", "sfence", X86_FEATURE_XMM)

#अन्यथा /* CONFIG_X86_32 */

#घोषणा mb()	यंत्र अस्थिर("mfence" : : : "memory")
#घोषणा rmb()	यंत्र अस्थिर("lfence" : : : "memory")
#घोषणा wmb()	यंत्र अस्थिर("sfence" : : : "memory")

#पूर्ण_अगर /* CONFIG_X86_32 */

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर
