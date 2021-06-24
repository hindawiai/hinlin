<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>

पूर्णांक
mtfsfi(अचिन्हित पूर्णांक crfD, अचिन्हित पूर्णांक IMM)
अणु
	u32 mask = 0xf;

	अगर (!crfD)
		mask = 9;

	__FPU_FPSCR &= ~(mask << ((7 - crfD) << 2));
	__FPU_FPSCR |= (IMM & 0xf) << ((7 - crfD) << 2);

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %d %x: %08lx\n", __func__, crfD, IMM, __FPU_FPSCR);
#पूर्ण_अगर

	वापस 0;
पूर्ण
