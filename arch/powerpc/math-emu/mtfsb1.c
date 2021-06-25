<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>

पूर्णांक
mtfsb1(पूर्णांक crbD)
अणु
	अगर ((crbD != 1) && (crbD != 2))
		__FPU_FPSCR |= (1 << (31 - crbD));

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %d %08lx\n", __func__, crbD, __FPU_FPSCR);
#पूर्ण_अगर

	वापस 0;
पूर्ण
