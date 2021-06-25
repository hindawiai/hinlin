<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/h8300/kernel/irq.c
 *
 * Copyright 2014-2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/traps.h>

#अगर_घोषित CONFIG_RAMKERNEL
प्रकार व्योम (*h8300_vector)(व्योम);

अटल स्थिर h8300_vector __initस्थिर trap_table[] = अणु
	0, 0, 0, 0,
	_trace_अवरोध,
	0, 0,
	_nmi,
	_प्रणाली_call,
	0, 0,
	_trace_अवरोध,
पूर्ण;

अटल अचिन्हित दीर्घ __init *get_vector_address(व्योम)
अणु
	अचिन्हित दीर्घ *rom_vector = CPU_VECTOR;
	अचिन्हित दीर्घ base, पंचांगp;
	पूर्णांक vec_no;

	base = rom_vector[EXT_IRQ0] & ADDR_MASK;

	/* check romvector क्रमmat */
	क्रम (vec_no = EXT_IRQ0 + 1; vec_no <= EXT_IRQ0+EXT_IRQS; vec_no++) अणु
		अगर ((base+(vec_no - EXT_IRQ0)*4) !=
		    (rom_vector[vec_no] & ADDR_MASK))
			वापस शून्य;
	पूर्ण

	/* ramvector base address */
	base -= EXT_IRQ0*4;

	/* ग_लिखोrble? */
	पंचांगp = ~(*(अस्थिर अचिन्हित दीर्घ *)base);
	(*(अस्थिर अचिन्हित दीर्घ *)base) = पंचांगp;
	अगर ((*(अस्थिर अचिन्हित दीर्घ *)base) != पंचांगp)
		वापस शून्य;
	वापस (अचिन्हित दीर्घ *)base;
पूर्ण

अटल व्योम __init setup_vector(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ *ramvec, *ramvec_p;
	स्थिर h8300_vector *trap_entry;

	ramvec = get_vector_address();
	अगर (ramvec == शून्य)
		panic("interrupt vector serup failed.");
	अन्यथा
		pr_debug("virtual vector at 0x%p\n", ramvec);

	/* create redirect table */
	ramvec_p = ramvec;
	trap_entry = trap_table;
	क्रम (i = 0; i < NR_IRQS; i++) अणु
		अगर (i < 12) अणु
			अगर (*trap_entry)
				*ramvec_p = VECTOR(*trap_entry);
			ramvec_p++;
			trap_entry++;
		पूर्ण अन्यथा
			*ramvec_p++ = REसूचीECT(_पूर्णांकerrupt_entry);
	पूर्ण
	_पूर्णांकerrupt_redirect_table = ramvec;
पूर्ण
#अन्यथा
व्योम setup_vector(व्योम)
अणु
	/* noting करो */
पूर्ण
#पूर्ण_अगर

व्योम __init init_IRQ(व्योम)
अणु
	setup_vector();
	irqchip_init();
पूर्ण

यंत्रlinkage व्योम करो_IRQ(पूर्णांक irq)
अणु
	irq_enter();
	generic_handle_irq(irq);
	irq_निकास();
पूर्ण
