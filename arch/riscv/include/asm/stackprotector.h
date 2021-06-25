<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_RISCV_STACKPROTECTOR_H
#घोषणा _ASM_RISCV_STACKPROTECTOR_H

#समावेश <linux/अक्रमom.h>
#समावेश <linux/version.h>

बाह्य अचिन्हित दीर्घ __stack_chk_guard;

/*
 * Initialize the stackprotector canary value.
 *
 * NOTE: this must only be called from functions that never वापस,
 * and it must always be अंतरभूतd.
 */
अटल __always_अंतरभूत व्योम boot_init_stack_canary(व्योम)
अणु
	अचिन्हित दीर्घ canary;

	/* Try to get a semi अक्रमom initial value. */
	get_अक्रमom_bytes(&canary, माप(canary));
	canary ^= LINUX_VERSION_CODE;
	canary &= CANARY_MASK;

	current->stack_canary = canary;
	अगर (!IS_ENABLED(CONFIG_STACKPROTECTOR_PER_TASK))
		__stack_chk_guard = current->stack_canary;
पूर्ण
#पूर्ण_अगर /* _ASM_RISCV_STACKPROTECTOR_H */
