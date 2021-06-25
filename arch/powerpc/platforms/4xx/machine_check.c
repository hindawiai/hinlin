<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/reg.h>

पूर्णांक machine_check_4xx(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ reason = regs->dsisr;

	अगर (reason & ESR_IMCP) अणु
		prपूर्णांकk("Instruction");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	पूर्ण अन्यथा
		prपूर्णांकk("Data");
	prपूर्णांकk(" machine check in kernel mode.\n");

	वापस 0;
पूर्ण
