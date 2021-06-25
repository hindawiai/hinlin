<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_MSI_H
#घोषणा __ASM_GENERIC_MSI_H

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN

#अगर_अघोषित NUM_MSI_ALLOC_SCRATCHPAD_REGS
# define NUM_MSI_ALLOC_SCRATCHPAD_REGS	2
#पूर्ण_अगर

काष्ठा msi_desc;

/**
 * काष्ठा msi_alloc_info - Default काष्ठाure क्रम MSI पूर्णांकerrupt allocation.
 * @desc:	Poपूर्णांकer to msi descriptor
 * @hwirq:	Associated hw पूर्णांकerrupt number in the करोमुख्य
 * @scratchpad:	Storage क्रम implementation specअगरic scratch data
 *
 * Architectures can provide their own implementation by not including
 * यंत्र-generic/msi.h पूर्णांकo their arch specअगरic header file.
 */
प्रकार काष्ठा msi_alloc_info अणु
	काष्ठा msi_desc			*desc;
	irq_hw_number_t			hwirq;
	अचिन्हित दीर्घ			flags;
	जोड़ अणु
		अचिन्हित दीर्घ		ul;
		व्योम			*ptr;
	पूर्ण scratchpad[NUM_MSI_ALLOC_SCRATCHPAD_REGS];
पूर्ण msi_alloc_info_t;

/* Device generating MSIs is proxying क्रम another device */
#घोषणा MSI_ALLOC_FLAGS_PROXY_DEVICE	(1UL << 0)

#घोषणा GENERIC_MSI_DOMAIN_OPS		1

#पूर्ण_अगर /* CONFIG_GENERIC_MSI_IRQ_DOMAIN */

#पूर्ण_अगर
