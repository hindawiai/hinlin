<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>

पूर्णांक
mcrfs(u32 *ccr, u32 crfD, u32 crfS)
अणु
	u32 value, clear;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %p (%08x) %d %d\n", __func__, ccr, *ccr, crfD, crfS);
#पूर्ण_अगर

	clear = 15 << ((7 - crfS) << 2);
	अगर (!crfS)
		clear = 0x90000000;

	value = (__FPU_FPSCR >> ((7 - crfS) << 2)) & 15;
	__FPU_FPSCR &= ~(clear);

	*ccr &= ~(15 << ((7 - crfD) << 2));
	*ccr |= (value << ((7 - crfD) << 2));

#अगर_घोषित DEBUG
	prपूर्णांकk("CR: %08x\n", __func__, *ccr);
#पूर्ण_अगर

	वापस 0;
पूर्ण
