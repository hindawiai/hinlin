<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2010 Ben Dooks <ben-linux@fluff.org>
 *
 * Support क्रम wakeup mask पूर्णांकerrupts on newer SoCs
 */

#अगर_अघोषित __PLAT_WAKEUP_MASK_H
#घोषणा __PLAT_WAKEUP_MASK_H __file__

/* अगर no irq yet defined, but still want to mask */
#घोषणा NO_WAKEUP_IRQ (0x90000000)

/**
 * काष्ठा samsung_wakeup_mask - wakeup mask inक्रमmation
 * @irq: The पूर्णांकerrupt associated with this wakeup.
 * @bit: The bit, as a (1 << bitno) controlling this source.
 */ 
काष्ठा samsung_wakeup_mask अणु
	अचिन्हित पूर्णांक	irq;
	u32		bit;
पूर्ण;

/**
 * samsung_sync_wakemask - sync wakeup mask inक्रमmation क्रम pm
 * @reg: The रेजिस्टर that is used.
 * @masks: The list of masks to use.
 * @nr_masks: The number of entries poपूर्णांकed to buy @masks.
 *
 * Synchronise the wakeup mask inक्रमmation at suspend समय from the list
 * of पूर्णांकerrupts and control bits in @masks. We करो this at suspend समय
 * as overriding the relevant irq chips is harder and the रेजिस्टर is only
 * required to be correct beक्रमe we enter sleep.
 */
बाह्य व्योम samsung_sync_wakemask(व्योम __iomem *reg,
				  स्थिर काष्ठा samsung_wakeup_mask *masks,
				  पूर्णांक nr_masks);

#पूर्ण_अगर /* __PLAT_WAKEUP_MASK_H */
