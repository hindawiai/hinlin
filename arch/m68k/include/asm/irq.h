<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_IRQ_H_
#घोषणा _M68K_IRQ_H_

/*
 * This should be the same as the max(NUM_X_SOURCES) क्रम all the
 * dअगरferent m68k hosts compiled पूर्णांकo the kernel.
 * Currently the Atari has 72 and the Amiga 24, but अगर both are
 * supported in the kernel it is better to make room क्रम 72.
 * With EtherNAT add-on card on Atari, the highest पूर्णांकerrupt
 * number is 140 so NR_IRQS needs to be 141.
 */
#अगर defined(CONFIG_COLDFIRE)
#घोषणा NR_IRQS 256
#या_अगर defined(CONFIG_VME) || defined(CONFIG_SUN3) || defined(CONFIG_SUN3X)
#घोषणा NR_IRQS 200
#या_अगर defined(CONFIG_ATARI)
#घोषणा NR_IRQS 141
#या_अगर defined(CONFIG_MAC)
#घोषणा NR_IRQS 72
#या_अगर defined(CONFIG_Q40)
#घोषणा NR_IRQS	43
#या_अगर defined(CONFIG_AMIGA) || !defined(CONFIG_MMU)
#घोषणा NR_IRQS	32
#या_अगर defined(CONFIG_APOLLO)
#घोषणा NR_IRQS	24
#या_अगर defined(CONFIG_HP300)
#घोषणा NR_IRQS	8
#अन्यथा
#घोषणा NR_IRQS	0
#पूर्ण_अगर

#अगर defined(CONFIG_M68020) || defined(CONFIG_M68030) || \
    defined(CONFIG_M68040) || defined(CONFIG_M68060)

/*
 * Interrupt source definitions
 * General पूर्णांकerrupt sources are the level 1-7.
 * Adding an पूर्णांकerrupt service routine क्रम one of these sources
 * results in the addition of that routine to a chain of routines.
 * Each one is called in succession.  Each inभागidual पूर्णांकerrupt
 * service routine should determine अगर the device associated with
 * that routine requires service.
 */

#घोषणा IRQ_SPURIOUS	0

#घोषणा IRQ_AUTO_1	1	/* level 1 पूर्णांकerrupt */
#घोषणा IRQ_AUTO_2	2	/* level 2 पूर्णांकerrupt */
#घोषणा IRQ_AUTO_3	3	/* level 3 पूर्णांकerrupt */
#घोषणा IRQ_AUTO_4	4	/* level 4 पूर्णांकerrupt */
#घोषणा IRQ_AUTO_5	5	/* level 5 पूर्णांकerrupt */
#घोषणा IRQ_AUTO_6	6	/* level 6 पूर्णांकerrupt */
#घोषणा IRQ_AUTO_7	7	/* level 7 पूर्णांकerrupt (non-maskable) */

#घोषणा IRQ_USER	8

काष्ठा irq_data;
काष्ठा irq_chip;
काष्ठा irq_desc;
बाह्य अचिन्हित पूर्णांक m68k_irq_startup(काष्ठा irq_data *data);
बाह्य अचिन्हित पूर्णांक m68k_irq_startup_irq(अचिन्हित पूर्णांक irq);
बाह्य व्योम m68k_irq_shutकरोwn(काष्ठा irq_data *data);
बाह्य व्योम m68k_setup_स्वतः_पूर्णांकerrupt(व्योम (*handler)(अचिन्हित पूर्णांक,
						      काष्ठा pt_regs *));
बाह्य व्योम m68k_setup_user_पूर्णांकerrupt(अचिन्हित पूर्णांक vec, अचिन्हित पूर्णांक cnt);
बाह्य व्योम m68k_setup_irq_controller(काष्ठा irq_chip *,
				      व्योम (*handle)(काष्ठा irq_desc *desc),
				      अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक cnt);

बाह्य अचिन्हित पूर्णांक irq_canonicalize(अचिन्हित पूर्णांक irq);

#अन्यथा
#घोषणा irq_canonicalize(irq)  (irq)
#पूर्ण_अगर /* !(CONFIG_M68020 || CONFIG_M68030 || CONFIG_M68040 || CONFIG_M68060) */

यंत्रlinkage व्योम करो_IRQ(पूर्णांक irq, काष्ठा pt_regs *regs);
बाह्य atomic_t irq_err_count;

#पूर्ण_अगर /* _M68K_IRQ_H_ */
