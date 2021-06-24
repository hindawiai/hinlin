<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>

#समावेश <यंत्र/चयन_to.h>

#समावेश "ptrace-decl.h"

पूर्णांक ptrace_get_fpr(काष्ठा task_काष्ठा *child, पूर्णांक index, अचिन्हित दीर्घ *data)
अणु
#अगर_घोषित CONFIG_PPC_FPU_REGS
	अचिन्हित पूर्णांक fpidx = index - PT_FPR0;
#पूर्ण_अगर

	अगर (index > PT_FPSCR)
		वापस -EIO;

#अगर_घोषित CONFIG_PPC_FPU_REGS
	flush_fp_to_thपढ़ो(child);
	अगर (fpidx < (PT_FPSCR - PT_FPR0))
		स_नकल(data, &child->thपढ़ो.TS_FPR(fpidx), माप(दीर्घ));
	अन्यथा
		*data = child->thपढ़ो.fp_state.fpscr;
#अन्यथा
	*data = 0;
#पूर्ण_अगर

	वापस 0;
पूर्ण

पूर्णांक ptrace_put_fpr(काष्ठा task_काष्ठा *child, पूर्णांक index, अचिन्हित दीर्घ data)
अणु
#अगर_घोषित CONFIG_PPC_FPU_REGS
	अचिन्हित पूर्णांक fpidx = index - PT_FPR0;
#पूर्ण_अगर

	अगर (index > PT_FPSCR)
		वापस -EIO;

#अगर_घोषित CONFIG_PPC_FPU_REGS
	flush_fp_to_thपढ़ो(child);
	अगर (fpidx < (PT_FPSCR - PT_FPR0))
		स_नकल(&child->thपढ़ो.TS_FPR(fpidx), &data, माप(दीर्घ));
	अन्यथा
		child->thपढ़ो.fp_state.fpscr = data;
#पूर्ण_अगर

	वापस 0;
पूर्ण

