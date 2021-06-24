<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>

पूर्णांक
mtfsf(अचिन्हित पूर्णांक FM, u32 *frB)
अणु
	u32 mask;
	u32 fpscr;

	अगर (likely(FM == 1))
		mask = 0x0f;
	अन्यथा अगर (likely(FM == 0xff))
		mask = ~0;
	अन्यथा अणु
		mask = ((FM & 1) |
				((FM << 3) & 0x10) |
				((FM << 6) & 0x100) |
				((FM << 9) & 0x1000) |
				((FM << 12) & 0x10000) |
				((FM << 15) & 0x100000) |
				((FM << 18) & 0x1000000) |
				((FM << 21) & 0x10000000)) * 15;
	पूर्ण

	fpscr = ((__FPU_FPSCR & ~mask) | (frB[1] & mask)) &
		~(FPSCR_VX | FPSCR_FEX | 0x800);

	अगर (fpscr & (FPSCR_VXSन_अंक | FPSCR_VXISI | FPSCR_VXIDI |
		     FPSCR_VXZDZ | FPSCR_VXIMZ | FPSCR_VXVC |
		     FPSCR_VXSOFT | FPSCR_VXSQRT | FPSCR_VXCVI))
		fpscr |= FPSCR_VX;

	/* The bit order of exception enables and exception status
	 * is the same. Simply shअगरt and mask to check क्रम enabled
	 * exceptions.
	 */
	अगर (fpscr & (fpscr >> 22) &  0xf8)
		fpscr |= FPSCR_FEX;

	__FPU_FPSCR = fpscr;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %02x %p: %08lx\n", __func__, FM, frB, __FPU_FPSCR);
#पूर्ण_अगर

	वापस 0;
पूर्ण
