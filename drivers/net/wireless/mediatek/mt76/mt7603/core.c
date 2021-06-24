<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश "mt7603.h"
#समावेश "../trace.h"

व्योम mt7603_rx_poll_complete(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);

	mt7603_irq_enable(dev, MT_INT_RX_DONE(q));
पूर्ण

irqवापस_t mt7603_irq_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mt7603_dev *dev = dev_instance;
	u32 पूर्णांकr;

	पूर्णांकr = mt76_rr(dev, MT_INT_SOURCE_CSR);
	mt76_wr(dev, MT_INT_SOURCE_CSR, पूर्णांकr);

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->mphy.state))
		वापस IRQ_NONE;

	trace_dev_irq(&dev->mt76, पूर्णांकr, dev->mt76.mmio.irqmask);

	पूर्णांकr &= dev->mt76.mmio.irqmask;

	अगर (पूर्णांकr & MT_INT_MAC_IRQ3) अणु
		u32 hwपूर्णांकr = mt76_rr(dev, MT_HW_INT_STATUS(3));

		mt76_wr(dev, MT_HW_INT_STATUS(3), hwपूर्णांकr);
		अगर (hwपूर्णांकr & MT_HW_INT3_PRE_TBTT0)
			tasklet_schedule(&dev->mt76.pre_tbtt_tasklet);

		अगर ((hwपूर्णांकr & MT_HW_INT3_TBTT0) && dev->mt76.csa_complete)
			mt76_csa_finish(&dev->mt76);
	पूर्ण

	अगर (पूर्णांकr & MT_INT_TX_DONE_ALL) अणु
		mt7603_irq_disable(dev, MT_INT_TX_DONE_ALL);
		napi_schedule(&dev->mt76.tx_napi);
	पूर्ण

	अगर (पूर्णांकr & MT_INT_RX_DONE(0)) अणु
		mt7603_irq_disable(dev, MT_INT_RX_DONE(0));
		napi_schedule(&dev->mt76.napi[0]);
	पूर्ण

	अगर (पूर्णांकr & MT_INT_RX_DONE(1)) अणु
		mt7603_irq_disable(dev, MT_INT_RX_DONE(1));
		napi_schedule(&dev->mt76.napi[1]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

u32 mt7603_reg_map(काष्ठा mt7603_dev *dev, u32 addr)
अणु
	u32 base = addr & MT_MCU_PCIE_REMAP_2_BASE;
	u32 offset = addr & MT_MCU_PCIE_REMAP_2_OFFSET;

	dev->bus_ops->wr(&dev->mt76, MT_MCU_PCIE_REMAP_2, base);

	वापस MT_PCIE_REMAP_BASE_2 + offset;
पूर्ण
