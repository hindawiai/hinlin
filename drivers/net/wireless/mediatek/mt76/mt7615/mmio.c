<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>

#समावेश "mt7615.h"
#समावेश "regs.h"
#समावेश "mac.h"
#समावेश "../trace.h"

स्थिर u32 mt7615e_reg_map[] = अणु
	[MT_TOP_CFG_BASE]	= 0x01000,
	[MT_HW_BASE]		= 0x01000,
	[MT_PCIE_REMAP_2]	= 0x02504,
	[MT_ARB_BASE]		= 0x20c00,
	[MT_HIF_BASE]		= 0x04000,
	[MT_CSR_BASE]		= 0x07000,
	[MT_PLE_BASE]		= 0x08000,
	[MT_PSE_BASE]		= 0x0c000,
	[MT_CFG_BASE]		= 0x20200,
	[MT_AGG_BASE]		= 0x20a00,
	[MT_TMAC_BASE]		= 0x21000,
	[MT_RMAC_BASE]		= 0x21200,
	[MT_DMA_BASE]		= 0x21800,
	[MT_PF_BASE]		= 0x22000,
	[MT_WTBL_BASE_ON]	= 0x23000,
	[MT_WTBL_BASE_OFF]	= 0x23400,
	[MT_LPON_BASE]		= 0x24200,
	[MT_MIB_BASE]		= 0x24800,
	[MT_WTBL_BASE_ADDR]	= 0x30000,
	[MT_PCIE_REMAP_BASE2]	= 0x80000,
	[MT_TOP_MISC_BASE]	= 0xc0000,
	[MT_EFUSE_ADDR_BASE]	= 0x81070000,
पूर्ण;

स्थिर u32 mt7663e_reg_map[] = अणु
	[MT_TOP_CFG_BASE]	= 0x01000,
	[MT_HW_BASE]		= 0x02000,
	[MT_DMA_SHDL_BASE]	= 0x06000,
	[MT_PCIE_REMAP_2]	= 0x0700c,
	[MT_ARB_BASE]		= 0x20c00,
	[MT_HIF_BASE]		= 0x04000,
	[MT_CSR_BASE]		= 0x07000,
	[MT_PLE_BASE]		= 0x08000,
	[MT_PSE_BASE]		= 0x0c000,
	[MT_PP_BASE]            = 0x0e000,
	[MT_CFG_BASE]		= 0x20000,
	[MT_AGG_BASE]		= 0x22000,
	[MT_TMAC_BASE]		= 0x24000,
	[MT_RMAC_BASE]		= 0x25000,
	[MT_DMA_BASE]		= 0x27000,
	[MT_PF_BASE]		= 0x28000,
	[MT_WTBL_BASE_ON]	= 0x29000,
	[MT_WTBL_BASE_OFF]	= 0x29800,
	[MT_LPON_BASE]		= 0x2b000,
	[MT_MIB_BASE]		= 0x2d000,
	[MT_WTBL_BASE_ADDR]	= 0x30000,
	[MT_PCIE_REMAP_BASE2]	= 0x90000,
	[MT_TOP_MISC_BASE]	= 0xc0000,
	[MT_EFUSE_ADDR_BASE]	= 0x78011000,
पूर्ण;

u32 mt7615_reg_map(काष्ठा mt7615_dev *dev, u32 addr)
अणु
	u32 base, offset;

	अगर (is_mt7663(&dev->mt76)) अणु
		base = addr & MT7663_MCU_PCIE_REMAP_2_BASE;
		offset = addr & MT7663_MCU_PCIE_REMAP_2_OFFSET;
	पूर्ण अन्यथा अणु
		base = addr & MT_MCU_PCIE_REMAP_2_BASE;
		offset = addr & MT_MCU_PCIE_REMAP_2_OFFSET;
	पूर्ण
	mt76_wr(dev, MT_MCU_PCIE_REMAP_2, base);

	वापस MT_PCIE_REMAP_BASE_2 + offset;
पूर्ण

अटल व्योम
mt7615_rx_poll_complete(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);

	mt7615_irq_enable(dev, MT_INT_RX_DONE(q));
पूर्ण

अटल irqवापस_t mt7615_irq_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mt7615_dev *dev = dev_instance;

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->mphy.state))
		वापस IRQ_NONE;

	tasklet_schedule(&dev->irq_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mt7615_irq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mt7615_dev *dev = from_tasklet(dev, t, irq_tasklet);
	u32 पूर्णांकr, mask = 0, tx_mcu_mask = mt7615_tx_mcu_पूर्णांक_mask(dev);
	u32 mcu_पूर्णांक;

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	पूर्णांकr = mt76_rr(dev, MT_INT_SOURCE_CSR);
	पूर्णांकr &= dev->mt76.mmio.irqmask;
	mt76_wr(dev, MT_INT_SOURCE_CSR, पूर्णांकr);

	trace_dev_irq(&dev->mt76, पूर्णांकr, dev->mt76.mmio.irqmask);

	mask |= पूर्णांकr & MT_INT_RX_DONE_ALL;
	अगर (पूर्णांकr & tx_mcu_mask)
		mask |= tx_mcu_mask;
	mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, mask, 0);

	अगर (पूर्णांकr & tx_mcu_mask)
		napi_schedule(&dev->mt76.tx_napi);

	अगर (पूर्णांकr & MT_INT_RX_DONE(0))
		napi_schedule(&dev->mt76.napi[0]);

	अगर (पूर्णांकr & MT_INT_RX_DONE(1))
		napi_schedule(&dev->mt76.napi[1]);

	अगर (!(पूर्णांकr & (MT_INT_MCU_CMD | MT7663_INT_MCU_CMD)))
		वापस;

	अगर (is_mt7663(&dev->mt76)) अणु
		mcu_पूर्णांक = mt76_rr(dev, MT_MCU2HOST_INT_STATUS);
		mcu_पूर्णांक &= MT7663_MCU_CMD_ERROR_MASK;
	पूर्ण अन्यथा अणु
		mcu_पूर्णांक = mt76_rr(dev, MT_MCU_CMD);
		mcu_पूर्णांक &= MT_MCU_CMD_ERROR_MASK;
	पूर्ण

	अगर (!mcu_पूर्णांक)
		वापस;

	dev->reset_state = mcu_पूर्णांक;
	ieee80211_queue_work(mt76_hw(dev), &dev->reset_work);
	wake_up(&dev->reset_रुको);
पूर्ण

अटल u32 __mt7615_reg_addr(काष्ठा mt7615_dev *dev, u32 addr)
अणु
	अगर (addr < 0x100000)
		वापस addr;

	वापस mt7615_reg_map(dev, addr);
पूर्ण

अटल u32 mt7615_rr(काष्ठा mt76_dev *mdev, u32 offset)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	u32 addr = __mt7615_reg_addr(dev, offset);

	वापस dev->bus_ops->rr(mdev, addr);
पूर्ण

अटल व्योम mt7615_wr(काष्ठा mt76_dev *mdev, u32 offset, u32 val)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	u32 addr = __mt7615_reg_addr(dev, offset);

	dev->bus_ops->wr(mdev, addr, val);
पूर्ण

अटल u32 mt7615_rmw(काष्ठा mt76_dev *mdev, u32 offset, u32 mask, u32 val)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	u32 addr = __mt7615_reg_addr(dev, offset);

	वापस dev->bus_ops->rmw(mdev, addr, mask, val);
पूर्ण

पूर्णांक mt7615_mmio_probe(काष्ठा device *pdev, व्योम __iomem *mem_base,
		      पूर्णांक irq, स्थिर u32 *map)
अणु
	अटल स्थिर काष्ठा mt76_driver_ops drv_ops = अणु
		/* txwi_size = txd size + txp size */
		.txwi_size = MT_TXD_SIZE + माप(काष्ठा mt7615_txp_common),
		.drv_flags = MT_DRV_TXWI_NO_FREE | MT_DRV_HW_MGMT_TXQ,
		.survey_flags = SURVEY_INFO_TIME_TX |
				SURVEY_INFO_TIME_RX |
				SURVEY_INFO_TIME_BSS_RX,
		.token_size = MT7615_TOKEN_SIZE,
		.tx_prepare_skb = mt7615_tx_prepare_skb,
		.tx_complete_skb = mt7615_tx_complete_skb,
		.rx_skb = mt7615_queue_rx_skb,
		.rx_poll_complete = mt7615_rx_poll_complete,
		.sta_ps = mt7615_sta_ps,
		.sta_add = mt7615_mac_sta_add,
		.sta_हटाओ = mt7615_mac_sta_हटाओ,
		.update_survey = mt7615_update_channel,
	पूर्ण;
	काष्ठा mt76_bus_ops *bus_ops;
	काष्ठा ieee80211_ops *ops;
	काष्ठा mt7615_dev *dev;
	काष्ठा mt76_dev *mdev;
	पूर्णांक ret;

	ops = devm_kmemdup(pdev, &mt7615_ops, माप(mt7615_ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	mdev = mt76_alloc_device(pdev, माप(*dev), ops, &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	mt76_mmio_init(&dev->mt76, mem_base);
	tasklet_setup(&dev->irq_tasklet, mt7615_irq_tasklet);

	dev->reg_map = map;
	dev->ops = ops;
	mdev->rev = (mt76_rr(dev, MT_HW_CHIPID) << 16) |
		    (mt76_rr(dev, MT_HW_REV) & 0xff);
	dev_dbg(mdev->dev, "ASIC revision: %04x\n", mdev->rev);

	dev->bus_ops = dev->mt76.bus;
	bus_ops = devm_kmemdup(dev->mt76.dev, dev->bus_ops, माप(*bus_ops),
			       GFP_KERNEL);
	अगर (!bus_ops) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	bus_ops->rr = mt7615_rr;
	bus_ops->wr = mt7615_wr;
	bus_ops->rmw = mt7615_rmw;
	dev->mt76.bus = bus_ops;

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	ret = devm_request_irq(mdev->dev, irq, mt7615_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (ret)
		जाओ error;

	अगर (is_mt7663(mdev))
		mt76_wr(dev, MT_PCIE_IRQ_ENABLE, 1);

	ret = mt7615_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ error;

	वापस 0;
error:
	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल पूर्णांक __init mt7615_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&mt7615_pci_driver);
	अगर (ret)
		वापस ret;

	अगर (IS_ENABLED(CONFIG_MT7622_WMAC)) अणु
		ret = platक्रमm_driver_रेजिस्टर(&mt7622_wmac_driver);
		अगर (ret)
			pci_unरेजिस्टर_driver(&mt7615_pci_driver);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास mt7615_निकास(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_MT7622_WMAC))
		platक्रमm_driver_unरेजिस्टर(&mt7622_wmac_driver);
	pci_unरेजिस्टर_driver(&mt7615_pci_driver);
पूर्ण

module_init(mt7615_init);
module_निकास(mt7615_निकास);
MODULE_LICENSE("Dual BSD/GPL");
