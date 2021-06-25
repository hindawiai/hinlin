<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Reset a DECstation machine.
 *
 * Copyright (C) 199x  the Anonymous
 * Copyright (C) 2001, 2002, 2003  Maciej W. Rozycki
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/linkage.h>

#समावेश <यंत्र/addrspace.h>

प्रकार व्योम __noवापस (* noret_func_t)(व्योम);

अटल अंतरभूत व्योम __noवापस back_to_prom(व्योम)
अणु
	noret_func_t func = (व्योम *)CKSEG1ADDR(0x1fc00000);

	func();
पूर्ण

व्योम __noवापस dec_machine_restart(अक्षर *command)
अणु
	back_to_prom();
पूर्ण

व्योम __noवापस dec_machine_halt(व्योम)
अणु
	back_to_prom();
पूर्ण

व्योम __noवापस dec_machine_घातer_off(व्योम)
अणु
    /* DECstations करोn't have a software घातer चयन */
	back_to_prom();
पूर्ण

irqवापस_t dec_पूर्णांकr_halt(पूर्णांक irq, व्योम *dev_id)
अणु
	dec_machine_halt();
पूर्ण
