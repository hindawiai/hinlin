<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * GCC stack protector support.
 *
 */

#अगर_अघोषित _ASM_STACKPROTECTOR_H
#घोषणा _ASM_STACKPROTECTOR_H

#समावेश <linux/अक्रमom.h>
#समावेश <linux/version.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/paca.h>

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
	canary = get_अक्रमom_canary();
	canary ^= mftb();
	canary ^= LINUX_VERSION_CODE;
	canary &= CANARY_MASK;

	current->stack_canary = canary;
#अगर_घोषित CONFIG_PPC64
	get_paca()->canary = canary;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर	/* _ASM_STACKPROTECTOR_H */
