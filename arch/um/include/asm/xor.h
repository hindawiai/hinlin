<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <यंत्र-generic/xor.h>
#समावेश <linux/समय-पूर्णांकernal.h>

/* pick an arbitrary one - measuring isn't possible with inf-cpu */
#घोषणा XOR_SELECT_TEMPLATE(x)	\
	(समय_प्रकारravel_mode == TT_MODE_INFCPU ? &xor_block_8regs : शून्य)
