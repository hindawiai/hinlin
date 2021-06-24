<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7915.h"

अटल u32 mt7915_reg_map_l1(काष्ठा mt7915_dev *dev, u32 addr)
अणु
	u32 offset = FIELD_GET(MT_HIF_REMAP_L1_OFFSET, addr);
	u32 base = FIELD_GET(MT_HIF_REMAP_L1_BASE, addr);

	mt76_rmw_field(dev, MT_HIF_REMAP_L1, MT_HIF_REMAP_L1_MASK, base);
	/* use पढ़ो to push ग_लिखो */
	mt76_rr(dev, MT_HIF_REMAP_L1);

	वापस MT_HIF_REMAP_BASE_L1 + offset;
पूर्ण

अटल u32 mt7915_reg_map_l2(काष्ठा mt7915_dev *dev, u32 addr)
अणु
	u32 offset = FIELD_GET(MT_HIF_REMAP_L2_OFFSET, addr);
	u32 base = FIELD_GET(MT_HIF_REMAP_L2_BASE, addr);

	mt76_rmw_field(dev, MT_HIF_REMAP_L2, MT_HIF_REMAP_L2_MASK, base);
	/* use पढ़ो to push ग_लिखो */
	mt76_rr(dev, MT_HIF_REMAP_L2);

	वापस MT_HIF_REMAP_BASE_L2 + offset;
पूर्ण

अटल u32 __mt7915_reg_addr(काष्ठा mt7915_dev *dev, u32 addr)
अणु
	अटल स्थिर काष्ठा अणु
		u32 phys;
		u32 mapped;
		u32 size;
	पूर्ण fixed_map[] = अणु
		अणु 0x54000000, 0x02000, 0x1000 पूर्ण, /* WFDMA PCIE0 MCU DMA0 */
		अणु 0x55000000, 0x03000, 0x1000 पूर्ण, /* WFDMA PCIE0 MCU DMA1 */
		अणु 0x58000000, 0x06000, 0x1000 पूर्ण, /* WFDMA PCIE1 MCU DMA0 (MEM_DMA) */
		अणु 0x59000000, 0x07000, 0x1000 पूर्ण, /* WFDMA PCIE1 MCU DMA1 */
		अणु 0x7c000000, 0xf0000, 0x10000 पूर्ण, /* CONN_INFRA */
		अणु 0x7c020000, 0xd0000, 0x10000 पूर्ण, /* CONN_INFRA, WFDMA */
		अणु 0x80020000, 0xb0000, 0x10000 पूर्ण, /* WF_TOP_MISC_OFF */
		अणु 0x81020000, 0xc0000, 0x10000 पूर्ण, /* WF_TOP_MISC_ON */
		अणु 0x820c0000, 0x08000, 0x4000 पूर्ण, /* WF_UMAC_TOP (PLE) */
		अणु 0x820c8000, 0x0c000, 0x2000 पूर्ण, /* WF_UMAC_TOP (PSE) */
		अणु 0x820cc000, 0x0e000, 0x2000 पूर्ण, /* WF_UMAC_TOP (PP) */
		अणु 0x820ce000, 0x21c00, 0x0200 पूर्ण, /* WF_LMAC_TOP (WF_SEC) */
		अणु 0x820cf000, 0x22000, 0x1000 पूर्ण, /* WF_LMAC_TOP (WF_PF) */
		अणु 0x820d0000, 0x30000, 0x10000 पूर्ण, /* WF_LMAC_TOP (WF_WTBLON) */
		अणु 0x820e0000, 0x20000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_CFG) */
		अणु 0x820e1000, 0x20400, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_TRB) */
		अणु 0x820e2000, 0x20800, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_AGG) */
		अणु 0x820e3000, 0x20c00, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_ARB) */
		अणु 0x820e4000, 0x21000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_TMAC) */
		अणु 0x820e5000, 0x21400, 0x0800 पूर्ण, /* WF_LMAC_TOP BN0 (WF_RMAC) */
		अणु 0x820e7000, 0x21e00, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_DMA) */
		अणु 0x820e9000, 0x23400, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_WTBLOFF) */
		अणु 0x820ea000, 0x24000, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_ETBF) */
		अणु 0x820eb000, 0x24200, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_LPON) */
		अणु 0x820ec000, 0x24600, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_INT) */
		अणु 0x820ed000, 0x24800, 0x0800 पूर्ण, /* WF_LMAC_TOP BN0 (WF_MIB) */
		अणु 0x820f0000, 0xa0000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_CFG) */
		अणु 0x820f1000, 0xa0600, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_TRB) */
		अणु 0x820f2000, 0xa0800, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_AGG) */
		अणु 0x820f3000, 0xa0c00, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_ARB) */
		अणु 0x820f4000, 0xa1000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_TMAC) */
		अणु 0x820f5000, 0xa1400, 0x0800 पूर्ण, /* WF_LMAC_TOP BN1 (WF_RMAC) */
		अणु 0x820f7000, 0xa1e00, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_DMA) */
		अणु 0x820f9000, 0xa3400, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_WTBLOFF) */
		अणु 0x820fa000, 0xa4000, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_ETBF) */
		अणु 0x820fb000, 0xa4200, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_LPON) */
		अणु 0x820fc000, 0xa4600, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_INT) */
		अणु 0x820fd000, 0xa4800, 0x0800 पूर्ण, /* WF_LMAC_TOP BN1 (WF_MIB) */
	पूर्ण;
	पूर्णांक i;

	अगर (addr < 0x100000)
		वापस addr;

	क्रम (i = 0; i < ARRAY_SIZE(fixed_map); i++) अणु
		u32 ofs;

		अगर (addr < fixed_map[i].phys)
			जारी;

		ofs = addr - fixed_map[i].phys;
		अगर (ofs > fixed_map[i].size)
			जारी;

		वापस fixed_map[i].mapped + ofs;
	पूर्ण

	अगर ((addr >= 0x18000000 && addr < 0x18c00000) ||
	    (addr >= 0x70000000 && addr < 0x78000000) ||
	    (addr >= 0x7c000000 && addr < 0x7c400000))
		वापस mt7915_reg_map_l1(dev, addr);

	वापस mt7915_reg_map_l2(dev, addr);
पूर्ण

अटल u32 mt7915_rr(काष्ठा mt76_dev *mdev, u32 offset)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	u32 addr = __mt7915_reg_addr(dev, offset);

	वापस dev->bus_ops->rr(mdev, addr);
पूर्ण

अटल व्योम mt7915_wr(काष्ठा mt76_dev *mdev, u32 offset, u32 val)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	u32 addr = __mt7915_reg_addr(dev, offset);

	dev->bus_ops->wr(mdev, addr, val);
पूर्ण

अटल u32 mt7915_rmw(काष्ठा mt76_dev *mdev, u32 offset, u32 mask, u32 val)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	u32 addr = __mt7915_reg_addr(dev, offset);

	वापस dev->bus_ops->rmw(mdev, addr, mask, val);
पूर्ण

पूर्णांक mt7915_mmio_init(काष्ठा mt76_dev *mdev, व्योम __iomem *mem_base, पूर्णांक irq)
अणु
	काष्ठा mt76_bus_ops *bus_ops;
	काष्ठा mt7915_dev *dev;

	dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	mt76_mmio_init(&dev->mt76, mem_base);

	dev->bus_ops = dev->mt76.bus;
	bus_ops = devm_kmemdup(dev->mt76.dev, dev->bus_ops, माप(*bus_ops),
			       GFP_KERNEL);
	अगर (!bus_ops)
		वापस -ENOMEM;

	bus_ops->rr = mt7915_rr;
	bus_ops->wr = mt7915_wr;
	bus_ops->rmw = mt7915_rmw;
	dev->mt76.bus = bus_ops;

	mdev->rev = (mt76_rr(dev, MT_HW_CHIPID) << 16) |
		    (mt76_rr(dev, MT_HW_REV) & 0xff);
	dev_dbg(mdev->dev, "ASIC revision: %04x\n", mdev->rev);

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	वापस 0;
पूर्ण
