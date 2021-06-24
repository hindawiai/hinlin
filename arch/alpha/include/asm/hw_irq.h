<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_HW_IRQ_H
#घोषणा _ALPHA_HW_IRQ_H


बाह्य अस्थिर अचिन्हित दीर्घ irq_err_count;
DECLARE_PER_CPU(अचिन्हित दीर्घ, irq_pmi_count);

#अगर_घोषित CONFIG_ALPHA_GENERIC
#घोषणा ACTUAL_NR_IRQS	alpha_mv.nr_irqs
#अन्यथा
#घोषणा ACTUAL_NR_IRQS	NR_IRQS
#पूर्ण_अगर

#पूर्ण_अगर
