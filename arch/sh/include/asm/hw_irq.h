<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_HW_IRQ_H
#घोषणा __ASM_SH_HW_IRQ_H

#समावेश <linux/init.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/atomic.h>

बाह्य atomic_t irq_err_count;

काष्ठा ipr_data अणु
	अचिन्हित अक्षर irq;
	अचिन्हित अक्षर ipr_idx;		/* Index क्रम the IPR रेजिस्टरed */
	अचिन्हित अक्षर shअगरt;		/* Number of bits to shअगरt the data */
	अचिन्हित अक्षर priority;		/* The priority */
पूर्ण;

काष्ठा ipr_desc अणु
	अचिन्हित दीर्घ *ipr_offsets;
	अचिन्हित पूर्णांक nr_offsets;
	काष्ठा ipr_data *ipr_data;
	अचिन्हित पूर्णांक nr_irqs;
	काष्ठा irq_chip chip;
पूर्ण;

व्योम रेजिस्टर_ipr_controller(काष्ठा ipr_desc *);

व्योम __init plat_irq_setup(व्योम);
व्योम __init plat_irq_setup_sh3(व्योम);
व्योम __init plat_irq_setup_pins(पूर्णांक mode);

क्रमागत अणु IRQ_MODE_IRQ, IRQ_MODE_IRQ7654, IRQ_MODE_IRQ3210,
       IRQ_MODE_IRL7654_MASK, IRQ_MODE_IRL3210_MASK,
       IRQ_MODE_IRL7654, IRQ_MODE_IRL3210 पूर्ण;

#पूर्ण_अगर /* __ASM_SH_HW_IRQ_H */
