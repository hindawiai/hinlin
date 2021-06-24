<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_STACKPROTECTOR_H
#घोषणा __ASM_SH_STACKPROTECTOR_H

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
	__stack_chk_guard = current->stack_canary;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_STACKPROTECTOR_H */
