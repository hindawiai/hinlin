<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013-2016, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#अगर_अघोषित _MEI_HW_TXE_H_
#घोषणा _MEI_HW_TXE_H_

#समावेश <linux/irqवापस.h>

#समावेश "hw.h"
#समावेश "hw-txe-regs.h"

#घोषणा MEI_TXI_RPM_TIMEOUT    500 /* ms */

/* Flatten Hierarchy पूर्णांकerrupt cause */
#घोषणा TXE_INTR_READINESS_BIT  0 /* HISR_INT_0_STS */
#घोषणा TXE_INTR_READINESS      HISR_INT_0_STS
#घोषणा TXE_INTR_ALIVENESS_BIT  1 /* HISR_INT_1_STS */
#घोषणा TXE_INTR_ALIVENESS      HISR_INT_1_STS
#घोषणा TXE_INTR_OUT_DB_BIT     2 /* HISR_INT_2_STS */
#घोषणा TXE_INTR_OUT_DB         HISR_INT_2_STS
#घोषणा TXE_INTR_IN_READY_BIT   8 /* beyond HISR */
#घोषणा TXE_INTR_IN_READY       BIT(8)

/**
 * काष्ठा mei_txe_hw - txe hardware specअगरics
 *
 * @mem_addr:            SeC and BRIDGE bars
 * @aliveness:           aliveness (घातer gating) state of the hardware
 * @पढ़ोiness:           पढ़ोiness state of the hardware
 * @slots:               number of empty slots
 * @रुको_aliveness_resp: aliveness रुको queue
 * @पूर्णांकr_cause:          translated पूर्णांकerrupt cause
 */
काष्ठा mei_txe_hw अणु
	व्योम __iomem * स्थिर *mem_addr;
	u32 aliveness;
	u32 पढ़ोiness;
	u32 slots;

	रुको_queue_head_t रुको_aliveness_resp;

	अचिन्हित दीर्घ पूर्णांकr_cause;
पूर्ण;

#घोषणा to_txe_hw(dev) (काष्ठा mei_txe_hw *)((dev)->hw)

अटल अंतरभूत काष्ठा mei_device *hw_txe_to_mei(काष्ठा mei_txe_hw *hw)
अणु
	वापस container_of((व्योम *)hw, काष्ठा mei_device, hw);
पूर्ण

काष्ठा mei_device *mei_txe_dev_init(काष्ठा pci_dev *pdev);

irqवापस_t mei_txe_irq_quick_handler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t mei_txe_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id);

पूर्णांक mei_txe_aliveness_set_sync(काष्ठा mei_device *dev, u32 req);

पूर्णांक mei_txe_setup_satt2(काष्ठा mei_device *dev, phys_addr_t addr, u32 range);


#पूर्ण_अगर /* _MEI_HW_TXE_H_ */
