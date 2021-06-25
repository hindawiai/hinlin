<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __QCOM_IRQ_H
#घोषणा __QCOM_IRQ_H

#समावेश <linux/irqकरोमुख्य.h>

#घोषणा GPIO_NO_WAKE_IRQ	~0U

/*
 * QCOM specअगरic IRQ करोमुख्य flags that distinguishes the handling of wakeup
 * capable पूर्णांकerrupts by dअगरferent पूर्णांकerrupt controllers.
 *
 * IRQ_DOMAIN_FLAG_QCOM_PDC_WAKEUP: Line must be masked at TLMM and the
 *                                  पूर्णांकerrupt configuration is करोne at PDC
 * IRQ_DOMAIN_FLAG_QCOM_MPM_WAKEUP: Interrupt configuration is handled at TLMM
 */
#घोषणा IRQ_DOMAIN_FLAG_QCOM_PDC_WAKEUP		(IRQ_DOMAIN_FLAG_NONCORE << 0)
#घोषणा IRQ_DOMAIN_FLAG_QCOM_MPM_WAKEUP		(IRQ_DOMAIN_FLAG_NONCORE << 1)

/**
 * irq_करोमुख्य_qcom_handle_wakeup: Return अगर the करोमुख्य handles पूर्णांकerrupt
 *                                configuration
 * @d: irq करोमुख्य
 *
 * This QCOM specअगरic irq करोमुख्य call वापसs अगर the पूर्णांकerrupt controller
 * requires the पूर्णांकerrupt be masked at the child पूर्णांकerrupt controller.
 */
अटल अंतरभूत bool irq_करोमुख्य_qcom_handle_wakeup(स्थिर काष्ठा irq_करोमुख्य *d)
अणु
	वापस (d->flags & IRQ_DOMAIN_FLAG_QCOM_PDC_WAKEUP);
पूर्ण

#पूर्ण_अगर
