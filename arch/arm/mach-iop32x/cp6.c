<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOP Coprocessor-6 access handler
 * Copyright (c) 2006, Intel Corporation.
 */
#समावेश <linux/init.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/ptrace.h>

अटल पूर्णांक cp6_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	u32 temp;

        /* enable cp6 access */
        यंत्र अस्थिर (
		"mrc	p15, 0, %0, c15, c1, 0\n\t"
		"orr	%0, %0, #(1 << 6)\n\t"
		"mcr	p15, 0, %0, c15, c1, 0\n\t"
		: "=r"(temp));

	वापस 0;
पूर्ण

/* permit kernel space cp6 access
 * deny user space cp6 access
 */
अटल काष्ठा undef_hook cp6_hook = अणु
	.instr_mask     = 0x0f000ff0,
	.instr_val      = 0x0e000610,
	.cpsr_mask      = MODE_MASK,
	.cpsr_val       = SVC_MODE,
	.fn             = cp6_trap,
पूर्ण;

व्योम __init iop_init_cp6_handler(व्योम)
अणु
	रेजिस्टर_undef_hook(&cp6_hook);
पूर्ण
