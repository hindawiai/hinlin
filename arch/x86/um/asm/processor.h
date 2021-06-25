<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_PROCESSOR_H
#घोषणा __UM_PROCESSOR_H
#समावेश <linux/समय-पूर्णांकernal.h>

/* include faultinfo काष्ठाure */
#समावेश <sysdep/faultinfo.h>

#अगर_घोषित CONFIG_X86_32
# include "processor_32.h"
#अन्यथा
# include "processor_64.h"
#पूर्ण_अगर

#घोषणा KSTK_EIP(tsk) KSTK_REG(tsk, HOST_IP)
#घोषणा KSTK_ESP(tsk) KSTK_REG(tsk, HOST_SP)
#घोषणा KSTK_EBP(tsk) KSTK_REG(tsk, HOST_BP)

#घोषणा ARCH_IS_STACKGROW(address) \
       (address + 65536 + 32 * माप(अचिन्हित दीर्घ) >= UPT_SP(&current->thपढ़ो.regs.regs))

#समावेश <यंत्र/user.h>

/* REP NOP (PAUSE) is a good thing to insert पूर्णांकo busy-रुको loops. */
अटल __always_अंतरभूत व्योम rep_nop(व्योम)
अणु
	__यंत्र__ __अस्थिर__("rep;nop": : :"memory");
पूर्ण

अटल __always_अंतरभूत व्योम cpu_relax(व्योम)
अणु
	अगर (समय_प्रकारravel_mode == TT_MODE_INFCPU ||
	    समय_प्रकारravel_mode == TT_MODE_EXTERNAL)
		समय_प्रकारravel_ndelay(1);
	अन्यथा
		rep_nop();
पूर्ण

#घोषणा task_pt_regs(t) (&(t)->thपढ़ो.regs)

#समावेश <यंत्र/processor-generic.h>

#पूर्ण_अगर
