<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * GCC stack protector support.
 *
 * (This is directly aकरोpted from the ARM implementation)
 *
 * Stack protector works by putting predefined pattern at the start of
 * the stack frame and verअगरying that it hasn't been overwritten when
 * वापसing from the function.  The pattern is called stack canary
 * and gcc expects it to be defined by a global variable called
 * "__stack_chk_guard" on MIPS.  This unक्रमtunately means that on SMP
 * we cannot have a dअगरferent canary value per task.
 */

#अगर_अघोषित _ASM_STACKPROTECTOR_H
#घोषणा _ASM_STACKPROTECTOR_H 1

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

	current->stack_canary = canary;
	__stack_chk_guard = current->stack_canary;
पूर्ण

#पूर्ण_अगर	/* _ASM_STACKPROTECTOR_H */
