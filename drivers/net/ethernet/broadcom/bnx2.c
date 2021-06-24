<शैली गुरु>
/* bnx2.c: QLogic bnx2 network driver.
 *
 * Copyright (c) 2004-2014 Broadcom Corporation
 * Copyright (c) 2014-2015 QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Michael Chan  (mchan@broadcom.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/stringअगरy.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/समय.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/checksum.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/crc32.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/cache.h>
#समावेश <linux/firmware.h>
#समावेश <linux/log2.h>
#समावेश <linux/aer.h>
#समावेश <linux/crash_dump.h>

#अगर IS_ENABLED(CONFIG_CNIC)
#घोषणा BCM_CNIC 1
#समावेश "cnic_if.h"
#पूर्ण_अगर
#समावेश "bnx2.h"
#समावेश "bnx2_fw.h"

#घोषणा DRV_MODULE_NAME		"bnx2"
#घोषणा FW_MIPS_खाता_06		"bnx2/bnx2-mips-06-6.2.3.fw"
#घोषणा FW_RV2P_खाता_06		"bnx2/bnx2-rv2p-06-6.0.15.fw"
#घोषणा FW_MIPS_खाता_09		"bnx2/bnx2-mips-09-6.2.1b.fw"
#घोषणा FW_RV2P_खाता_09_Ax	"bnx2/bnx2-rv2p-09ax-6.0.17.fw"
#घोषणा FW_RV2P_खाता_09		"bnx2/bnx2-rv2p-09-6.0.17.fw"

#घोषणा RUN_AT(x) (jअगरfies + (x))

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (5*HZ)

MODULE_AUTHOR("Michael Chan <mchan@broadcom.com>");
MODULE_DESCRIPTION("QLogic BCM5706/5708/5709/5716 Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FW_MIPS_खाता_06);
MODULE_FIRMWARE(FW_RV2P_खाता_06);
MODULE_FIRMWARE(FW_MIPS_खाता_09);
MODULE_FIRMWARE(FW_RV2P_खाता_09);
MODULE_FIRMWARE(FW_RV2P_खाता_09_Ax);

अटल पूर्णांक disable_msi = 0;

module_param(disable_msi, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_msi, "Disable Message Signaled Interrupt (MSI)");

प्रकार क्रमागत अणु
	BCM5706 = 0,
	NC370T,
	NC370I,
	BCM5706S,
	NC370F,
	BCM5708,
	BCM5708S,
	BCM5709,
	BCM5709S,
	BCM5716,
	BCM5716S,
पूर्ण board_t;

/* indexed by board_t, above */
अटल काष्ठा अणु
	अक्षर *name;
पूर्ण board_info[] = अणु
	अणु "Broadcom NetXtreme II BCM5706 1000Base-T" पूर्ण,
	अणु "HP NC370T Multifunction Gigabit Server Adapter" पूर्ण,
	अणु "HP NC370i Multifunction Gigabit Server Adapter" पूर्ण,
	अणु "Broadcom NetXtreme II BCM5706 1000Base-SX" पूर्ण,
	अणु "HP NC370F Multifunction Gigabit Server Adapter" पूर्ण,
	अणु "Broadcom NetXtreme II BCM5708 1000Base-T" पूर्ण,
	अणु "Broadcom NetXtreme II BCM5708 1000Base-SX" पूर्ण,
	अणु "Broadcom NetXtreme II BCM5709 1000Base-T" पूर्ण,
	अणु "Broadcom NetXtreme II BCM5709 1000Base-SX" पूर्ण,
	अणु "Broadcom NetXtreme II BCM5716 1000Base-T" पूर्ण,
	अणु "Broadcom NetXtreme II BCM5716 1000Base-SX" पूर्ण,
	पूर्ण;

अटल स्थिर काष्ठा pci_device_id bnx2_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5706,
	  PCI_VENDOR_ID_HP, 0x3101, 0, 0, NC370T पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5706,
	  PCI_VENDOR_ID_HP, 0x3106, 0, 0, NC370I पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5706,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5706 पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5708,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5708 पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5706S,
	  PCI_VENDOR_ID_HP, 0x3102, 0, 0, NC370F पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5706S,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5706S पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5708S,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5708S पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5709,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5709 पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_NX2_5709S,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5709S पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, 0x163b,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5716 पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, 0x163c,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, BCM5716S पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल स्थिर काष्ठा flash_spec flash_table[] =
अणु
#घोषणा BUFFERED_FLAGS		(BNX2_NV_BUFFERED | BNX2_NV_TRANSLATE)
#घोषणा NONBUFFERED_FLAGS	(BNX2_NV_WREN)
	/* Slow EEPROM */
	अणु0x00000000, 0x40830380, 0x009f0081, 0xa184a053, 0xaf000400,
	 BUFFERED_FLAGS, SEEPROM_PAGE_BITS, SEEPROM_PAGE_SIZE,
	 SEEPROM_BYTE_ADDR_MASK, SEEPROM_TOTAL_SIZE,
	 "EEPROM - slow"पूर्ण,
	/* Expansion entry 0001 */
	अणु0x08000002, 0x4b808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, 0,
	 "Entry 0001"पूर्ण,
	/* Saअगरun SA25F010 (non-buffered flash) */
	/* strap, cfg1, & ग_लिखो1 need updates */
	अणु0x04000001, 0x47808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, SAIFUN_FLASH_BASE_TOTAL_SIZE*2,
	 "Non-buffered flash (128kB)"पूर्ण,
	/* Saअगरun SA25F020 (non-buffered flash) */
	/* strap, cfg1, & ग_लिखो1 need updates */
	अणु0x0c000003, 0x4f808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, SAIFUN_FLASH_BASE_TOTAL_SIZE*4,
	 "Non-buffered flash (256kB)"पूर्ण,
	/* Expansion entry 0100 */
	अणु0x11000000, 0x53808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, 0,
	 "Entry 0100"पूर्ण,
	/* Entry 0101: ST M45PE10 (non-buffered flash, TetonII B0) */
	अणु0x19000002, 0x5b808201, 0x000500db, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, ST_MICRO_FLASH_PAGE_BITS, ST_MICRO_FLASH_PAGE_SIZE,
	 ST_MICRO_FLASH_BYTE_ADDR_MASK, ST_MICRO_FLASH_BASE_TOTAL_SIZE*2,
	 "Entry 0101: ST M45PE10 (128kB non-bufferred)"पूर्ण,
	/* Entry 0110: ST M45PE20 (non-buffered flash)*/
	अणु0x15000001, 0x57808201, 0x000500db, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, ST_MICRO_FLASH_PAGE_BITS, ST_MICRO_FLASH_PAGE_SIZE,
	 ST_MICRO_FLASH_BYTE_ADDR_MASK, ST_MICRO_FLASH_BASE_TOTAL_SIZE*4,
	 "Entry 0110: ST M45PE20 (256kB non-bufferred)"पूर्ण,
	/* Saअगरun SA25F005 (non-buffered flash) */
	/* strap, cfg1, & ग_लिखो1 need updates */
	अणु0x1d000003, 0x5f808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, SAIFUN_FLASH_BASE_TOTAL_SIZE,
	 "Non-buffered flash (64kB)"पूर्ण,
	/* Fast EEPROM */
	अणु0x22000000, 0x62808380, 0x009f0081, 0xa184a053, 0xaf000400,
	 BUFFERED_FLAGS, SEEPROM_PAGE_BITS, SEEPROM_PAGE_SIZE,
	 SEEPROM_BYTE_ADDR_MASK, SEEPROM_TOTAL_SIZE,
	 "EEPROM - fast"पूर्ण,
	/* Expansion entry 1001 */
	अणु0x2a000002, 0x6b808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, 0,
	 "Entry 1001"पूर्ण,
	/* Expansion entry 1010 */
	अणु0x26000001, 0x67808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, 0,
	 "Entry 1010"पूर्ण,
	/* ATMEL AT45DB011B (buffered flash) */
	अणु0x2e000003, 0x6e808273, 0x00570081, 0x68848353, 0xaf000400,
	 BUFFERED_FLAGS, BUFFERED_FLASH_PAGE_BITS, BUFFERED_FLASH_PAGE_SIZE,
	 BUFFERED_FLASH_BYTE_ADDR_MASK, BUFFERED_FLASH_TOTAL_SIZE,
	 "Buffered flash (128kB)"पूर्ण,
	/* Expansion entry 1100 */
	अणु0x33000000, 0x73808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, 0,
	 "Entry 1100"पूर्ण,
	/* Expansion entry 1101 */
	अणु0x3b000002, 0x7b808201, 0x00050081, 0x03840253, 0xaf020406,
	 NONBUFFERED_FLAGS, SAIFUN_FLASH_PAGE_BITS, SAIFUN_FLASH_PAGE_SIZE,
	 SAIFUN_FLASH_BYTE_ADDR_MASK, 0,
	 "Entry 1101"पूर्ण,
	/* Ateml Expansion entry 1110 */
	अणु0x37000001, 0x76808273, 0x00570081, 0x68848353, 0xaf000400,
	 BUFFERED_FLAGS, BUFFERED_FLASH_PAGE_BITS, BUFFERED_FLASH_PAGE_SIZE,
	 BUFFERED_FLASH_BYTE_ADDR_MASK, 0,
	 "Entry 1110 (Atmel)"पूर्ण,
	/* ATMEL AT45DB021B (buffered flash) */
	अणु0x3f000003, 0x7e808273, 0x00570081, 0x68848353, 0xaf000400,
	 BUFFERED_FLAGS, BUFFERED_FLASH_PAGE_BITS, BUFFERED_FLASH_PAGE_SIZE,
	 BUFFERED_FLASH_BYTE_ADDR_MASK, BUFFERED_FLASH_TOTAL_SIZE*2,
	 "Buffered flash (256kB)"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा flash_spec flash_5709 = अणु
	.flags		= BNX2_NV_BUFFERED,
	.page_bits	= BCM5709_FLASH_PAGE_BITS,
	.page_size	= BCM5709_FLASH_PAGE_SIZE,
	.addr_mask	= BCM5709_FLASH_BYTE_ADDR_MASK,
	.total_size	= BUFFERED_FLASH_TOTAL_SIZE*2,
	.name		= "5709 Buffered flash (256kB)",
पूर्ण;

MODULE_DEVICE_TABLE(pci, bnx2_pci_tbl);

अटल व्योम bnx2_init_napi(काष्ठा bnx2 *bp);
अटल व्योम bnx2_del_napi(काष्ठा bnx2 *bp);

अटल अंतरभूत u32 bnx2_tx_avail(काष्ठा bnx2 *bp, काष्ठा bnx2_tx_ring_info *txr)
अणु
	u32 dअगरf;

	/* The ring uses 256 indices क्रम 255 entries, one of them
	 * needs to be skipped.
	 */
	dअगरf = READ_ONCE(txr->tx_prod) - READ_ONCE(txr->tx_cons);
	अगर (unlikely(dअगरf >= BNX2_TX_DESC_CNT)) अणु
		dअगरf &= 0xffff;
		अगर (dअगरf == BNX2_TX_DESC_CNT)
			dअगरf = BNX2_MAX_TX_DESC_CNT;
	पूर्ण
	वापस bp->tx_ring_size - dअगरf;
पूर्ण

अटल u32
bnx2_reg_rd_ind(काष्ठा bnx2 *bp, u32 offset)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&bp->indirect_lock, flags);
	BNX2_WR(bp, BNX2_PCICFG_REG_WINDOW_ADDRESS, offset);
	val = BNX2_RD(bp, BNX2_PCICFG_REG_WINDOW);
	spin_unlock_irqrestore(&bp->indirect_lock, flags);
	वापस val;
पूर्ण

अटल व्योम
bnx2_reg_wr_ind(काष्ठा bnx2 *bp, u32 offset, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bp->indirect_lock, flags);
	BNX2_WR(bp, BNX2_PCICFG_REG_WINDOW_ADDRESS, offset);
	BNX2_WR(bp, BNX2_PCICFG_REG_WINDOW, val);
	spin_unlock_irqrestore(&bp->indirect_lock, flags);
पूर्ण

अटल व्योम
bnx2_shmem_wr(काष्ठा bnx2 *bp, u32 offset, u32 val)
अणु
	bnx2_reg_wr_ind(bp, bp->shmem_base + offset, val);
पूर्ण

अटल u32
bnx2_shmem_rd(काष्ठा bnx2 *bp, u32 offset)
अणु
	वापस bnx2_reg_rd_ind(bp, bp->shmem_base + offset);
पूर्ण

अटल व्योम
bnx2_ctx_wr(काष्ठा bnx2 *bp, u32 cid_addr, u32 offset, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	offset += cid_addr;
	spin_lock_irqsave(&bp->indirect_lock, flags);
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		पूर्णांक i;

		BNX2_WR(bp, BNX2_CTX_CTX_DATA, val);
		BNX2_WR(bp, BNX2_CTX_CTX_CTRL,
			offset | BNX2_CTX_CTX_CTRL_WRITE_REQ);
		क्रम (i = 0; i < 5; i++) अणु
			val = BNX2_RD(bp, BNX2_CTX_CTX_CTRL);
			अगर ((val & BNX2_CTX_CTX_CTRL_WRITE_REQ) == 0)
				अवरोध;
			udelay(5);
		पूर्ण
	पूर्ण अन्यथा अणु
		BNX2_WR(bp, BNX2_CTX_DATA_ADR, offset);
		BNX2_WR(bp, BNX2_CTX_DATA, val);
	पूर्ण
	spin_unlock_irqrestore(&bp->indirect_lock, flags);
पूर्ण

#अगर_घोषित BCM_CNIC
अटल पूर्णांक
bnx2_drv_ctl(काष्ठा net_device *dev, काष्ठा drv_ctl_info *info)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	काष्ठा drv_ctl_io *io = &info->data.io;

	चयन (info->cmd) अणु
	हाल DRV_CTL_IO_WR_CMD:
		bnx2_reg_wr_ind(bp, io->offset, io->data);
		अवरोध;
	हाल DRV_CTL_IO_RD_CMD:
		io->data = bnx2_reg_rd_ind(bp, io->offset);
		अवरोध;
	हाल DRV_CTL_CTX_WR_CMD:
		bnx2_ctx_wr(bp, io->cid_addr, io->offset, io->data);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnx2_setup_cnic_irq_info(काष्ठा bnx2 *bp)
अणु
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;
	काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[0];
	पूर्णांक sb_id;

	अगर (bp->flags & BNX2_FLAG_USING_MSIX) अणु
		cp->drv_state |= CNIC_DRV_STATE_USING_MSIX;
		bnapi->cnic_present = 0;
		sb_id = bp->irq_nvecs;
		cp->irq_arr[0].irq_flags |= CNIC_IRQ_FL_MSIX;
	पूर्ण अन्यथा अणु
		cp->drv_state &= ~CNIC_DRV_STATE_USING_MSIX;
		bnapi->cnic_tag = bnapi->last_status_idx;
		bnapi->cnic_present = 1;
		sb_id = 0;
		cp->irq_arr[0].irq_flags &= ~CNIC_IRQ_FL_MSIX;
	पूर्ण

	cp->irq_arr[0].vector = bp->irq_tbl[sb_id].vector;
	cp->irq_arr[0].status_blk = (व्योम *)
		((अचिन्हित दीर्घ) bnapi->status_blk.msi +
		(BNX2_SBLK_MSIX_ALIGN_SIZE * sb_id));
	cp->irq_arr[0].status_blk_num = sb_id;
	cp->num_irq = 1;
पूर्ण

अटल पूर्णांक bnx2_रेजिस्टर_cnic(काष्ठा net_device *dev, काष्ठा cnic_ops *ops,
			      व्योम *data)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	अगर (!ops)
		वापस -EINVAL;

	अगर (cp->drv_state & CNIC_DRV_STATE_REGD)
		वापस -EBUSY;

	अगर (!bnx2_reg_rd_ind(bp, BNX2_FW_MAX_ISCSI_CONN))
		वापस -ENODEV;

	bp->cnic_data = data;
	rcu_assign_poपूर्णांकer(bp->cnic_ops, ops);

	cp->num_irq = 0;
	cp->drv_state = CNIC_DRV_STATE_REGD;

	bnx2_setup_cnic_irq_info(bp);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2_unरेजिस्टर_cnic(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[0];
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	mutex_lock(&bp->cnic_lock);
	cp->drv_state = 0;
	bnapi->cnic_present = 0;
	RCU_INIT_POINTER(bp->cnic_ops, शून्य);
	mutex_unlock(&bp->cnic_lock);
	synchronize_rcu();
	वापस 0;
पूर्ण

अटल काष्ठा cnic_eth_dev *bnx2_cnic_probe(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	अगर (!cp->max_iscsi_conn)
		वापस शून्य;

	cp->drv_owner = THIS_MODULE;
	cp->chip_id = bp->chip_id;
	cp->pdev = bp->pdev;
	cp->io_base = bp->regview;
	cp->drv_ctl = bnx2_drv_ctl;
	cp->drv_रेजिस्टर_cnic = bnx2_रेजिस्टर_cnic;
	cp->drv_unरेजिस्टर_cnic = bnx2_unरेजिस्टर_cnic;

	वापस cp;
पूर्ण

अटल व्योम
bnx2_cnic_stop(काष्ठा bnx2 *bp)
अणु
	काष्ठा cnic_ops *c_ops;
	काष्ठा cnic_ctl_info info;

	mutex_lock(&bp->cnic_lock);
	c_ops = rcu_dereference_रक्षित(bp->cnic_ops,
					  lockdep_is_held(&bp->cnic_lock));
	अगर (c_ops) अणु
		info.cmd = CNIC_CTL_STOP_CMD;
		c_ops->cnic_ctl(bp->cnic_data, &info);
	पूर्ण
	mutex_unlock(&bp->cnic_lock);
पूर्ण

अटल व्योम
bnx2_cnic_start(काष्ठा bnx2 *bp)
अणु
	काष्ठा cnic_ops *c_ops;
	काष्ठा cnic_ctl_info info;

	mutex_lock(&bp->cnic_lock);
	c_ops = rcu_dereference_रक्षित(bp->cnic_ops,
					  lockdep_is_held(&bp->cnic_lock));
	अगर (c_ops) अणु
		अगर (!(bp->flags & BNX2_FLAG_USING_MSIX)) अणु
			काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[0];

			bnapi->cnic_tag = bnapi->last_status_idx;
		पूर्ण
		info.cmd = CNIC_CTL_START_CMD;
		c_ops->cnic_ctl(bp->cnic_data, &info);
	पूर्ण
	mutex_unlock(&bp->cnic_lock);
पूर्ण

#अन्यथा

अटल व्योम
bnx2_cnic_stop(काष्ठा bnx2 *bp)
अणु
पूर्ण

अटल व्योम
bnx2_cnic_start(काष्ठा bnx2 *bp)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक
bnx2_पढ़ो_phy(काष्ठा bnx2 *bp, u32 reg, u32 *val)
अणु
	u32 val1;
	पूर्णांक i, ret;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_INT_MODE_AUTO_POLLING) अणु
		val1 = BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);
		val1 &= ~BNX2_EMAC_MDIO_MODE_AUTO_POLL;

		BNX2_WR(bp, BNX2_EMAC_MDIO_MODE, val1);
		BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);

		udelay(40);
	पूर्ण

	val1 = (bp->phy_addr << 21) | (reg << 16) |
		BNX2_EMAC_MDIO_COMM_COMMAND_READ | BNX2_EMAC_MDIO_COMM_DISEXT |
		BNX2_EMAC_MDIO_COMM_START_BUSY;
	BNX2_WR(bp, BNX2_EMAC_MDIO_COMM, val1);

	क्रम (i = 0; i < 50; i++) अणु
		udelay(10);

		val1 = BNX2_RD(bp, BNX2_EMAC_MDIO_COMM);
		अगर (!(val1 & BNX2_EMAC_MDIO_COMM_START_BUSY)) अणु
			udelay(5);

			val1 = BNX2_RD(bp, BNX2_EMAC_MDIO_COMM);
			val1 &= BNX2_EMAC_MDIO_COMM_DATA;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (val1 & BNX2_EMAC_MDIO_COMM_START_BUSY) अणु
		*val = 0x0;
		ret = -EBUSY;
	पूर्ण
	अन्यथा अणु
		*val = val1;
		ret = 0;
	पूर्ण

	अगर (bp->phy_flags & BNX2_PHY_FLAG_INT_MODE_AUTO_POLLING) अणु
		val1 = BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);
		val1 |= BNX2_EMAC_MDIO_MODE_AUTO_POLL;

		BNX2_WR(bp, BNX2_EMAC_MDIO_MODE, val1);
		BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);

		udelay(40);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
bnx2_ग_लिखो_phy(काष्ठा bnx2 *bp, u32 reg, u32 val)
अणु
	u32 val1;
	पूर्णांक i, ret;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_INT_MODE_AUTO_POLLING) अणु
		val1 = BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);
		val1 &= ~BNX2_EMAC_MDIO_MODE_AUTO_POLL;

		BNX2_WR(bp, BNX2_EMAC_MDIO_MODE, val1);
		BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);

		udelay(40);
	पूर्ण

	val1 = (bp->phy_addr << 21) | (reg << 16) | val |
		BNX2_EMAC_MDIO_COMM_COMMAND_WRITE |
		BNX2_EMAC_MDIO_COMM_START_BUSY | BNX2_EMAC_MDIO_COMM_DISEXT;
	BNX2_WR(bp, BNX2_EMAC_MDIO_COMM, val1);

	क्रम (i = 0; i < 50; i++) अणु
		udelay(10);

		val1 = BNX2_RD(bp, BNX2_EMAC_MDIO_COMM);
		अगर (!(val1 & BNX2_EMAC_MDIO_COMM_START_BUSY)) अणु
			udelay(5);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (val1 & BNX2_EMAC_MDIO_COMM_START_BUSY)
        	ret = -EBUSY;
	अन्यथा
		ret = 0;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_INT_MODE_AUTO_POLLING) अणु
		val1 = BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);
		val1 |= BNX2_EMAC_MDIO_MODE_AUTO_POLL;

		BNX2_WR(bp, BNX2_EMAC_MDIO_MODE, val1);
		BNX2_RD(bp, BNX2_EMAC_MDIO_MODE);

		udelay(40);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
bnx2_disable_पूर्णांक(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	काष्ठा bnx2_napi *bnapi;

	क्रम (i = 0; i < bp->irq_nvecs; i++) अणु
		bnapi = &bp->bnx2_napi[i];
		BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, bnapi->पूर्णांक_num |
		       BNX2_PCICFG_INT_ACK_CMD_MASK_INT);
	पूर्ण
	BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD);
पूर्ण

अटल व्योम
bnx2_enable_पूर्णांक(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	काष्ठा bnx2_napi *bnapi;

	क्रम (i = 0; i < bp->irq_nvecs; i++) अणु
		bnapi = &bp->bnx2_napi[i];

		BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, bnapi->पूर्णांक_num |
			BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
			BNX2_PCICFG_INT_ACK_CMD_MASK_INT |
			bnapi->last_status_idx);

		BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, bnapi->पूर्णांक_num |
			BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
			bnapi->last_status_idx);
	पूर्ण
	BNX2_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW);
पूर्ण

अटल व्योम
bnx2_disable_पूर्णांक_sync(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	atomic_inc(&bp->पूर्णांकr_sem);
	अगर (!netअगर_running(bp->dev))
		वापस;

	bnx2_disable_पूर्णांक(bp);
	क्रम (i = 0; i < bp->irq_nvecs; i++)
		synchronize_irq(bp->irq_tbl[i].vector);
पूर्ण

अटल व्योम
bnx2_napi_disable(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->irq_nvecs; i++)
		napi_disable(&bp->bnx2_napi[i].napi);
पूर्ण

अटल व्योम
bnx2_napi_enable(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->irq_nvecs; i++)
		napi_enable(&bp->bnx2_napi[i].napi);
पूर्ण

अटल व्योम
bnx2_netअगर_stop(काष्ठा bnx2 *bp, bool stop_cnic)
अणु
	अगर (stop_cnic)
		bnx2_cnic_stop(bp);
	अगर (netअगर_running(bp->dev)) अणु
		bnx2_napi_disable(bp);
		netअगर_tx_disable(bp->dev);
	पूर्ण
	bnx2_disable_पूर्णांक_sync(bp);
	netअगर_carrier_off(bp->dev);	/* prevent tx समयout */
पूर्ण

अटल व्योम
bnx2_netअगर_start(काष्ठा bnx2 *bp, bool start_cnic)
अणु
	अगर (atomic_dec_and_test(&bp->पूर्णांकr_sem)) अणु
		अगर (netअगर_running(bp->dev)) अणु
			netअगर_tx_wake_all_queues(bp->dev);
			spin_lock_bh(&bp->phy_lock);
			अगर (bp->link_up)
				netअगर_carrier_on(bp->dev);
			spin_unlock_bh(&bp->phy_lock);
			bnx2_napi_enable(bp);
			bnx2_enable_पूर्णांक(bp);
			अगर (start_cnic)
				bnx2_cnic_start(bp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
bnx2_मुक्त_tx_mem(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->num_tx_rings; i++) अणु
		काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[i];
		काष्ठा bnx2_tx_ring_info *txr = &bnapi->tx_ring;

		अगर (txr->tx_desc_ring) अणु
			dma_मुक्त_coherent(&bp->pdev->dev, TXBD_RING_SIZE,
					  txr->tx_desc_ring,
					  txr->tx_desc_mapping);
			txr->tx_desc_ring = शून्य;
		पूर्ण
		kमुक्त(txr->tx_buf_ring);
		txr->tx_buf_ring = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
bnx2_मुक्त_rx_mem(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->num_rx_rings; i++) अणु
		काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[i];
		काष्ठा bnx2_rx_ring_info *rxr = &bnapi->rx_ring;
		पूर्णांक j;

		क्रम (j = 0; j < bp->rx_max_ring; j++) अणु
			अगर (rxr->rx_desc_ring[j])
				dma_मुक्त_coherent(&bp->pdev->dev, RXBD_RING_SIZE,
						  rxr->rx_desc_ring[j],
						  rxr->rx_desc_mapping[j]);
			rxr->rx_desc_ring[j] = शून्य;
		पूर्ण
		vमुक्त(rxr->rx_buf_ring);
		rxr->rx_buf_ring = शून्य;

		क्रम (j = 0; j < bp->rx_max_pg_ring; j++) अणु
			अगर (rxr->rx_pg_desc_ring[j])
				dma_मुक्त_coherent(&bp->pdev->dev, RXBD_RING_SIZE,
						  rxr->rx_pg_desc_ring[j],
						  rxr->rx_pg_desc_mapping[j]);
			rxr->rx_pg_desc_ring[j] = शून्य;
		पूर्ण
		vमुक्त(rxr->rx_pg_ring);
		rxr->rx_pg_ring = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2_alloc_tx_mem(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->num_tx_rings; i++) अणु
		काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[i];
		काष्ठा bnx2_tx_ring_info *txr = &bnapi->tx_ring;

		txr->tx_buf_ring = kzalloc(SW_TXBD_RING_SIZE, GFP_KERNEL);
		अगर (!txr->tx_buf_ring)
			वापस -ENOMEM;

		txr->tx_desc_ring =
			dma_alloc_coherent(&bp->pdev->dev, TXBD_RING_SIZE,
					   &txr->tx_desc_mapping, GFP_KERNEL);
		अगर (!txr->tx_desc_ring)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_alloc_rx_mem(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->num_rx_rings; i++) अणु
		काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[i];
		काष्ठा bnx2_rx_ring_info *rxr = &bnapi->rx_ring;
		पूर्णांक j;

		rxr->rx_buf_ring =
			vzalloc(array_size(SW_RXBD_RING_SIZE, bp->rx_max_ring));
		अगर (!rxr->rx_buf_ring)
			वापस -ENOMEM;

		क्रम (j = 0; j < bp->rx_max_ring; j++) अणु
			rxr->rx_desc_ring[j] =
				dma_alloc_coherent(&bp->pdev->dev,
						   RXBD_RING_SIZE,
						   &rxr->rx_desc_mapping[j],
						   GFP_KERNEL);
			अगर (!rxr->rx_desc_ring[j])
				वापस -ENOMEM;

		पूर्ण

		अगर (bp->rx_pg_ring_size) अणु
			rxr->rx_pg_ring =
				vzalloc(array_size(SW_RXPG_RING_SIZE,
						   bp->rx_max_pg_ring));
			अगर (!rxr->rx_pg_ring)
				वापस -ENOMEM;

		पूर्ण

		क्रम (j = 0; j < bp->rx_max_pg_ring; j++) अणु
			rxr->rx_pg_desc_ring[j] =
				dma_alloc_coherent(&bp->pdev->dev,
						   RXBD_RING_SIZE,
						   &rxr->rx_pg_desc_mapping[j],
						   GFP_KERNEL);
			अगर (!rxr->rx_pg_desc_ring[j])
				वापस -ENOMEM;

		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
bnx2_मुक्त_stats_blk(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (bp->status_blk) अणु
		dma_मुक्त_coherent(&bp->pdev->dev, bp->status_stats_size,
				  bp->status_blk,
				  bp->status_blk_mapping);
		bp->status_blk = शून्य;
		bp->stats_blk = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2_alloc_stats_blk(काष्ठा net_device *dev)
अणु
	पूर्णांक status_blk_size;
	व्योम *status_blk;
	काष्ठा bnx2 *bp = netdev_priv(dev);

	/* Combine status and statistics blocks पूर्णांकo one allocation. */
	status_blk_size = L1_CACHE_ALIGN(माप(काष्ठा status_block));
	अगर (bp->flags & BNX2_FLAG_MSIX_CAP)
		status_blk_size = L1_CACHE_ALIGN(BNX2_MAX_MSIX_HW_VEC *
						 BNX2_SBLK_MSIX_ALIGN_SIZE);
	bp->status_stats_size = status_blk_size +
				माप(काष्ठा statistics_block);
	status_blk = dma_alloc_coherent(&bp->pdev->dev, bp->status_stats_size,
					&bp->status_blk_mapping, GFP_KERNEL);
	अगर (!status_blk)
		वापस -ENOMEM;

	bp->status_blk = status_blk;
	bp->stats_blk = status_blk + status_blk_size;
	bp->stats_blk_mapping = bp->status_blk_mapping + status_blk_size;

	वापस 0;
पूर्ण

अटल व्योम
bnx2_मुक्त_mem(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[0];

	bnx2_मुक्त_tx_mem(bp);
	bnx2_मुक्त_rx_mem(bp);

	क्रम (i = 0; i < bp->ctx_pages; i++) अणु
		अगर (bp->ctx_blk[i]) अणु
			dma_मुक्त_coherent(&bp->pdev->dev, BNX2_PAGE_SIZE,
					  bp->ctx_blk[i],
					  bp->ctx_blk_mapping[i]);
			bp->ctx_blk[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (bnapi->status_blk.msi)
		bnapi->status_blk.msi = शून्य;
पूर्ण

अटल पूर्णांक
bnx2_alloc_mem(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i, err;
	काष्ठा bnx2_napi *bnapi;

	bnapi = &bp->bnx2_napi[0];
	bnapi->status_blk.msi = bp->status_blk;
	bnapi->hw_tx_cons_ptr =
		&bnapi->status_blk.msi->status_tx_quick_consumer_index0;
	bnapi->hw_rx_cons_ptr =
		&bnapi->status_blk.msi->status_rx_quick_consumer_index0;
	अगर (bp->flags & BNX2_FLAG_MSIX_CAP) अणु
		क्रम (i = 1; i < bp->irq_nvecs; i++) अणु
			काष्ठा status_block_msix *sblk;

			bnapi = &bp->bnx2_napi[i];

			sblk = (bp->status_blk + BNX2_SBLK_MSIX_ALIGN_SIZE * i);
			bnapi->status_blk.msix = sblk;
			bnapi->hw_tx_cons_ptr =
				&sblk->status_tx_quick_consumer_index;
			bnapi->hw_rx_cons_ptr =
				&sblk->status_rx_quick_consumer_index;
			bnapi->पूर्णांक_num = i << 24;
		पूर्ण
	पूर्ण

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		bp->ctx_pages = 0x2000 / BNX2_PAGE_SIZE;
		अगर (bp->ctx_pages == 0)
			bp->ctx_pages = 1;
		क्रम (i = 0; i < bp->ctx_pages; i++) अणु
			bp->ctx_blk[i] = dma_alloc_coherent(&bp->pdev->dev,
						BNX2_PAGE_SIZE,
						&bp->ctx_blk_mapping[i],
						GFP_KERNEL);
			अगर (!bp->ctx_blk[i])
				जाओ alloc_mem_err;
		पूर्ण
	पूर्ण

	err = bnx2_alloc_rx_mem(bp);
	अगर (err)
		जाओ alloc_mem_err;

	err = bnx2_alloc_tx_mem(bp);
	अगर (err)
		जाओ alloc_mem_err;

	वापस 0;

alloc_mem_err:
	bnx2_मुक्त_mem(bp);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
bnx2_report_fw_link(काष्ठा bnx2 *bp)
अणु
	u32 fw_link_status = 0;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		वापस;

	अगर (bp->link_up) अणु
		u32 bmsr;

		चयन (bp->line_speed) अणु
		हाल SPEED_10:
			अगर (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_10HALF;
			अन्यथा
				fw_link_status = BNX2_LINK_STATUS_10FULL;
			अवरोध;
		हाल SPEED_100:
			अगर (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_100HALF;
			अन्यथा
				fw_link_status = BNX2_LINK_STATUS_100FULL;
			अवरोध;
		हाल SPEED_1000:
			अगर (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_1000HALF;
			अन्यथा
				fw_link_status = BNX2_LINK_STATUS_1000FULL;
			अवरोध;
		हाल SPEED_2500:
			अगर (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_2500HALF;
			अन्यथा
				fw_link_status = BNX2_LINK_STATUS_2500FULL;
			अवरोध;
		पूर्ण

		fw_link_status |= BNX2_LINK_STATUS_LINK_UP;

		अगर (bp->स्वतःneg) अणु
			fw_link_status |= BNX2_LINK_STATUS_AN_ENABLED;

			bnx2_पढ़ो_phy(bp, bp->mii_bmsr, &bmsr);
			bnx2_पढ़ो_phy(bp, bp->mii_bmsr, &bmsr);

			अगर (!(bmsr & BMSR_ANEGCOMPLETE) ||
			    bp->phy_flags & BNX2_PHY_FLAG_PARALLEL_DETECT)
				fw_link_status |= BNX2_LINK_STATUS_PARALLEL_DET;
			अन्यथा
				fw_link_status |= BNX2_LINK_STATUS_AN_COMPLETE;
		पूर्ण
	पूर्ण
	अन्यथा
		fw_link_status = BNX2_LINK_STATUS_LINK_DOWN;

	bnx2_shmem_wr(bp, BNX2_LINK_STATUS, fw_link_status);
पूर्ण

अटल अक्षर *
bnx2_xceiver_str(काष्ठा bnx2 *bp)
अणु
	वापस (bp->phy_port == PORT_FIBRE) ? "SerDes" :
		((bp->phy_flags & BNX2_PHY_FLAG_SERDES) ? "Remote Copper" :
		 "Copper");
पूर्ण

अटल व्योम
bnx2_report_link(काष्ठा bnx2 *bp)
अणु
	अगर (bp->link_up) अणु
		netअगर_carrier_on(bp->dev);
		netdev_info(bp->dev, "NIC %s Link is Up, %d Mbps %s duplex",
			    bnx2_xceiver_str(bp),
			    bp->line_speed,
			    bp->duplex == DUPLEX_FULL ? "full" : "half");

		अगर (bp->flow_ctrl) अणु
			अगर (bp->flow_ctrl & FLOW_CTRL_RX) अणु
				pr_cont(", receive ");
				अगर (bp->flow_ctrl & FLOW_CTRL_TX)
					pr_cont("& transmit ");
			पूर्ण
			अन्यथा अणु
				pr_cont(", transmit ");
			पूर्ण
			pr_cont("flow control ON");
		पूर्ण
		pr_cont("\n");
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(bp->dev);
		netdev_err(bp->dev, "NIC %s Link is Down\n",
			   bnx2_xceiver_str(bp));
	पूर्ण

	bnx2_report_fw_link(bp);
पूर्ण

अटल व्योम
bnx2_resolve_flow_ctrl(काष्ठा bnx2 *bp)
अणु
	u32 local_adv, remote_adv;

	bp->flow_ctrl = 0;
	अगर ((bp->स्वतःneg & (AUTONEG_SPEED | AUTONEG_FLOW_CTRL)) !=
		(AUTONEG_SPEED | AUTONEG_FLOW_CTRL)) अणु

		अगर (bp->duplex == DUPLEX_FULL) अणु
			bp->flow_ctrl = bp->req_flow_ctrl;
		पूर्ण
		वापस;
	पूर्ण

	अगर (bp->duplex != DUPLEX_FULL) अणु
		वापस;
	पूर्ण

	अगर ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
	    (BNX2_CHIP(bp) == BNX2_CHIP_5708)) अणु
		u32 val;

		bnx2_पढ़ो_phy(bp, BCM5708S_1000X_STAT1, &val);
		अगर (val & BCM5708S_1000X_STAT1_TX_PAUSE)
			bp->flow_ctrl |= FLOW_CTRL_TX;
		अगर (val & BCM5708S_1000X_STAT1_RX_PAUSE)
			bp->flow_ctrl |= FLOW_CTRL_RX;
		वापस;
	पूर्ण

	bnx2_पढ़ो_phy(bp, bp->mii_adv, &local_adv);
	bnx2_पढ़ो_phy(bp, bp->mii_lpa, &remote_adv);

	अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
		u32 new_local_adv = 0;
		u32 new_remote_adv = 0;

		अगर (local_adv & ADVERTISE_1000XPAUSE)
			new_local_adv |= ADVERTISE_PAUSE_CAP;
		अगर (local_adv & ADVERTISE_1000XPSE_ASYM)
			new_local_adv |= ADVERTISE_PAUSE_ASYM;
		अगर (remote_adv & ADVERTISE_1000XPAUSE)
			new_remote_adv |= ADVERTISE_PAUSE_CAP;
		अगर (remote_adv & ADVERTISE_1000XPSE_ASYM)
			new_remote_adv |= ADVERTISE_PAUSE_ASYM;

		local_adv = new_local_adv;
		remote_adv = new_remote_adv;
	पूर्ण

	/* See Table 28B-3 of 802.3ab-1999 spec. */
	अगर (local_adv & ADVERTISE_PAUSE_CAP) अणु
		अगर(local_adv & ADVERTISE_PAUSE_ASYM) अणु
	                अगर (remote_adv & ADVERTISE_PAUSE_CAP) अणु
				bp->flow_ctrl = FLOW_CTRL_TX | FLOW_CTRL_RX;
			पूर्ण
			अन्यथा अगर (remote_adv & ADVERTISE_PAUSE_ASYM) अणु
				bp->flow_ctrl = FLOW_CTRL_RX;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			अगर (remote_adv & ADVERTISE_PAUSE_CAP) अणु
				bp->flow_ctrl = FLOW_CTRL_TX | FLOW_CTRL_RX;
			पूर्ण
		पूर्ण
	पूर्ण
	अन्यथा अगर (local_adv & ADVERTISE_PAUSE_ASYM) अणु
		अगर ((remote_adv & ADVERTISE_PAUSE_CAP) &&
			(remote_adv & ADVERTISE_PAUSE_ASYM)) अणु

			bp->flow_ctrl = FLOW_CTRL_TX;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2_5709s_linkup(काष्ठा bnx2 *bp)
अणु
	u32 val, speed;

	bp->link_up = 1;

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_GP_STATUS);
	bnx2_पढ़ो_phy(bp, MII_BNX2_GP_TOP_AN_STATUS1, &val);
	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_COMBO_IEEEB0);

	अगर ((bp->स्वतःneg & AUTONEG_SPEED) == 0) अणु
		bp->line_speed = bp->req_line_speed;
		bp->duplex = bp->req_duplex;
		वापस 0;
	पूर्ण
	speed = val & MII_BNX2_GP_TOP_AN_SPEED_MSK;
	चयन (speed) अणु
		हाल MII_BNX2_GP_TOP_AN_SPEED_10:
			bp->line_speed = SPEED_10;
			अवरोध;
		हाल MII_BNX2_GP_TOP_AN_SPEED_100:
			bp->line_speed = SPEED_100;
			अवरोध;
		हाल MII_BNX2_GP_TOP_AN_SPEED_1G:
		हाल MII_BNX2_GP_TOP_AN_SPEED_1GKV:
			bp->line_speed = SPEED_1000;
			अवरोध;
		हाल MII_BNX2_GP_TOP_AN_SPEED_2_5G:
			bp->line_speed = SPEED_2500;
			अवरोध;
	पूर्ण
	अगर (val & MII_BNX2_GP_TOP_AN_FD)
		bp->duplex = DUPLEX_FULL;
	अन्यथा
		bp->duplex = DUPLEX_HALF;
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_5708s_linkup(काष्ठा bnx2 *bp)
अणु
	u32 val;

	bp->link_up = 1;
	bnx2_पढ़ो_phy(bp, BCM5708S_1000X_STAT1, &val);
	चयन (val & BCM5708S_1000X_STAT1_SPEED_MASK) अणु
		हाल BCM5708S_1000X_STAT1_SPEED_10:
			bp->line_speed = SPEED_10;
			अवरोध;
		हाल BCM5708S_1000X_STAT1_SPEED_100:
			bp->line_speed = SPEED_100;
			अवरोध;
		हाल BCM5708S_1000X_STAT1_SPEED_1G:
			bp->line_speed = SPEED_1000;
			अवरोध;
		हाल BCM5708S_1000X_STAT1_SPEED_2G5:
			bp->line_speed = SPEED_2500;
			अवरोध;
	पूर्ण
	अगर (val & BCM5708S_1000X_STAT1_FD)
		bp->duplex = DUPLEX_FULL;
	अन्यथा
		bp->duplex = DUPLEX_HALF;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_5706s_linkup(काष्ठा bnx2 *bp)
अणु
	u32 bmcr, local_adv, remote_adv, common;

	bp->link_up = 1;
	bp->line_speed = SPEED_1000;

	bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
	अगर (bmcr & BMCR_FULLDPLX) अणु
		bp->duplex = DUPLEX_FULL;
	पूर्ण
	अन्यथा अणु
		bp->duplex = DUPLEX_HALF;
	पूर्ण

	अगर (!(bmcr & BMCR_ANENABLE)) अणु
		वापस 0;
	पूर्ण

	bnx2_पढ़ो_phy(bp, bp->mii_adv, &local_adv);
	bnx2_पढ़ो_phy(bp, bp->mii_lpa, &remote_adv);

	common = local_adv & remote_adv;
	अगर (common & (ADVERTISE_1000XHALF | ADVERTISE_1000XFULL)) अणु

		अगर (common & ADVERTISE_1000XFULL) अणु
			bp->duplex = DUPLEX_FULL;
		पूर्ण
		अन्यथा अणु
			bp->duplex = DUPLEX_HALF;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_copper_linkup(काष्ठा bnx2 *bp)
अणु
	u32 bmcr;

	bp->phy_flags &= ~BNX2_PHY_FLAG_MDIX;

	bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
	अगर (bmcr & BMCR_ANENABLE) अणु
		u32 local_adv, remote_adv, common;

		bnx2_पढ़ो_phy(bp, MII_CTRL1000, &local_adv);
		bnx2_पढ़ो_phy(bp, MII_STAT1000, &remote_adv);

		common = local_adv & (remote_adv >> 2);
		अगर (common & ADVERTISE_1000FULL) अणु
			bp->line_speed = SPEED_1000;
			bp->duplex = DUPLEX_FULL;
		पूर्ण
		अन्यथा अगर (common & ADVERTISE_1000HALF) अणु
			bp->line_speed = SPEED_1000;
			bp->duplex = DUPLEX_HALF;
		पूर्ण
		अन्यथा अणु
			bnx2_पढ़ो_phy(bp, bp->mii_adv, &local_adv);
			bnx2_पढ़ो_phy(bp, bp->mii_lpa, &remote_adv);

			common = local_adv & remote_adv;
			अगर (common & ADVERTISE_100FULL) अणु
				bp->line_speed = SPEED_100;
				bp->duplex = DUPLEX_FULL;
			पूर्ण
			अन्यथा अगर (common & ADVERTISE_100HALF) अणु
				bp->line_speed = SPEED_100;
				bp->duplex = DUPLEX_HALF;
			पूर्ण
			अन्यथा अगर (common & ADVERTISE_10FULL) अणु
				bp->line_speed = SPEED_10;
				bp->duplex = DUPLEX_FULL;
			पूर्ण
			अन्यथा अगर (common & ADVERTISE_10HALF) अणु
				bp->line_speed = SPEED_10;
				bp->duplex = DUPLEX_HALF;
			पूर्ण
			अन्यथा अणु
				bp->line_speed = 0;
				bp->link_up = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (bmcr & BMCR_SPEED100) अणु
			bp->line_speed = SPEED_100;
		पूर्ण
		अन्यथा अणु
			bp->line_speed = SPEED_10;
		पूर्ण
		अगर (bmcr & BMCR_FULLDPLX) अणु
			bp->duplex = DUPLEX_FULL;
		पूर्ण
		अन्यथा अणु
			bp->duplex = DUPLEX_HALF;
		पूर्ण
	पूर्ण

	अगर (bp->link_up) अणु
		u32 ext_status;

		bnx2_पढ़ो_phy(bp, MII_BNX2_EXT_STATUS, &ext_status);
		अगर (ext_status & EXT_STATUS_MDIX)
			bp->phy_flags |= BNX2_PHY_FLAG_MDIX;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
bnx2_init_rx_context(काष्ठा bnx2 *bp, u32 cid)
अणु
	u32 val, rx_cid_addr = GET_CID_ADDR(cid);

	val = BNX2_L2CTX_CTX_TYPE_CTX_BD_CHN_TYPE_VALUE;
	val |= BNX2_L2CTX_CTX_TYPE_SIZE_L2;
	val |= 0x02 << 8;

	अगर (bp->flow_ctrl & FLOW_CTRL_TX)
		val |= BNX2_L2CTX_FLOW_CTRL_ENABLE;

	bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_CTX_TYPE, val);
पूर्ण

अटल व्योम
bnx2_init_all_rx_contexts(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	u32 cid;

	क्रम (i = 0, cid = RX_CID; i < bp->num_rx_rings; i++, cid++) अणु
		अगर (i == 1)
			cid = RX_RSS_CID;
		bnx2_init_rx_context(bp, cid);
	पूर्ण
पूर्ण

अटल व्योम
bnx2_set_mac_link(काष्ठा bnx2 *bp)
अणु
	u32 val;

	BNX2_WR(bp, BNX2_EMAC_TX_LENGTHS, 0x2620);
	अगर (bp->link_up && (bp->line_speed == SPEED_1000) &&
		(bp->duplex == DUPLEX_HALF)) अणु
		BNX2_WR(bp, BNX2_EMAC_TX_LENGTHS, 0x26ff);
	पूर्ण

	/* Configure the EMAC mode रेजिस्टर. */
	val = BNX2_RD(bp, BNX2_EMAC_MODE);

	val &= ~(BNX2_EMAC_MODE_PORT | BNX2_EMAC_MODE_HALF_DUPLEX |
		BNX2_EMAC_MODE_MAC_LOOP | BNX2_EMAC_MODE_FORCE_LINK |
		BNX2_EMAC_MODE_25G_MODE);

	अगर (bp->link_up) अणु
		चयन (bp->line_speed) अणु
			हाल SPEED_10:
				अगर (BNX2_CHIP(bp) != BNX2_CHIP_5706) अणु
					val |= BNX2_EMAC_MODE_PORT_MII_10M;
					अवरोध;
				पूर्ण
				fallthrough;
			हाल SPEED_100:
				val |= BNX2_EMAC_MODE_PORT_MII;
				अवरोध;
			हाल SPEED_2500:
				val |= BNX2_EMAC_MODE_25G_MODE;
				fallthrough;
			हाल SPEED_1000:
				val |= BNX2_EMAC_MODE_PORT_GMII;
				अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		val |= BNX2_EMAC_MODE_PORT_GMII;
	पूर्ण

	/* Set the MAC to operate in the appropriate duplex mode. */
	अगर (bp->duplex == DUPLEX_HALF)
		val |= BNX2_EMAC_MODE_HALF_DUPLEX;
	BNX2_WR(bp, BNX2_EMAC_MODE, val);

	/* Enable/disable rx PAUSE. */
	bp->rx_mode &= ~BNX2_EMAC_RX_MODE_FLOW_EN;

	अगर (bp->flow_ctrl & FLOW_CTRL_RX)
		bp->rx_mode |= BNX2_EMAC_RX_MODE_FLOW_EN;
	BNX2_WR(bp, BNX2_EMAC_RX_MODE, bp->rx_mode);

	/* Enable/disable tx PAUSE. */
	val = BNX2_RD(bp, BNX2_EMAC_TX_MODE);
	val &= ~BNX2_EMAC_TX_MODE_FLOW_EN;

	अगर (bp->flow_ctrl & FLOW_CTRL_TX)
		val |= BNX2_EMAC_TX_MODE_FLOW_EN;
	BNX2_WR(bp, BNX2_EMAC_TX_MODE, val);

	/* Acknowledge the पूर्णांकerrupt. */
	BNX2_WR(bp, BNX2_EMAC_STATUS, BNX2_EMAC_STATUS_LINK_CHANGE);

	bnx2_init_all_rx_contexts(bp);
पूर्ण

अटल व्योम
bnx2_enable_bmsr1(काष्ठा bnx2 *bp)
अणु
	अगर ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
	    (BNX2_CHIP(bp) == BNX2_CHIP_5709))
		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_GP_STATUS);
पूर्ण

अटल व्योम
bnx2_disable_bmsr1(काष्ठा bnx2 *bp)
अणु
	अगर ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
	    (BNX2_CHIP(bp) == BNX2_CHIP_5709))
		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_COMBO_IEEEB0);
पूर्ण

अटल पूर्णांक
bnx2_test_and_enable_2g5(काष्ठा bnx2 *bp)
अणु
	u32 up1;
	पूर्णांक ret = 1;

	अगर (!(bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE))
		वापस 0;

	अगर (bp->स्वतःneg & AUTONEG_SPEED)
		bp->advertising |= ADVERTISED_2500baseX_Full;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_OVER1G);

	bnx2_पढ़ो_phy(bp, bp->mii_up1, &up1);
	अगर (!(up1 & BCM5708S_UP1_2G5)) अणु
		up1 |= BCM5708S_UP1_2G5;
		bnx2_ग_लिखो_phy(bp, bp->mii_up1, up1);
		ret = 0;
	पूर्ण

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_COMBO_IEEEB0);

	वापस ret;
पूर्ण

अटल पूर्णांक
bnx2_test_and_disable_2g5(काष्ठा bnx2 *bp)
अणु
	u32 up1;
	पूर्णांक ret = 0;

	अगर (!(bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE))
		वापस 0;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_OVER1G);

	bnx2_पढ़ो_phy(bp, bp->mii_up1, &up1);
	अगर (up1 & BCM5708S_UP1_2G5) अणु
		up1 &= ~BCM5708S_UP1_2G5;
		bnx2_ग_लिखो_phy(bp, bp->mii_up1, up1);
		ret = 1;
	पूर्ण

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_COMBO_IEEEB0);

	वापस ret;
पूर्ण

अटल व्योम
bnx2_enable_क्रमced_2g5(काष्ठा bnx2 *bp)
अणु
	u32 bmcr;
	पूर्णांक err;

	अगर (!(bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE))
		वापस;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		u32 val;

		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_SERDES_DIG);
		अगर (!bnx2_पढ़ो_phy(bp, MII_BNX2_SERDES_DIG_MISC1, &val)) अणु
			val &= ~MII_BNX2_SD_MISC1_FORCE_MSK;
			val |= MII_BNX2_SD_MISC1_FORCE |
				MII_BNX2_SD_MISC1_FORCE_2_5G;
			bnx2_ग_लिखो_phy(bp, MII_BNX2_SERDES_DIG_MISC1, val);
		पूर्ण

		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_COMBO_IEEEB0);
		err = bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);

	पूर्ण अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5708) अणु
		err = bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
		अगर (!err)
			bmcr |= BCM5708S_BMCR_FORCE_2500;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	अगर (err)
		वापस;

	अगर (bp->स्वतःneg & AUTONEG_SPEED) अणु
		bmcr &= ~BMCR_ANENABLE;
		अगर (bp->req_duplex == DUPLEX_FULL)
			bmcr |= BMCR_FULLDPLX;
	पूर्ण
	bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr);
पूर्ण

अटल व्योम
bnx2_disable_क्रमced_2g5(काष्ठा bnx2 *bp)
अणु
	u32 bmcr;
	पूर्णांक err;

	अगर (!(bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE))
		वापस;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		u32 val;

		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_SERDES_DIG);
		अगर (!bnx2_पढ़ो_phy(bp, MII_BNX2_SERDES_DIG_MISC1, &val)) अणु
			val &= ~MII_BNX2_SD_MISC1_FORCE;
			bnx2_ग_लिखो_phy(bp, MII_BNX2_SERDES_DIG_MISC1, val);
		पूर्ण

		bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_COMBO_IEEEB0);
		err = bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);

	पूर्ण अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5708) अणु
		err = bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
		अगर (!err)
			bmcr &= ~BCM5708S_BMCR_FORCE_2500;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	अगर (err)
		वापस;

	अगर (bp->स्वतःneg & AUTONEG_SPEED)
		bmcr |= BMCR_SPEED1000 | BMCR_ANENABLE | BMCR_ANRESTART;
	bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr);
पूर्ण

अटल व्योम
bnx2_5706s_क्रमce_link_dn(काष्ठा bnx2 *bp, पूर्णांक start)
अणु
	u32 val;

	bnx2_ग_लिखो_phy(bp, MII_BNX2_DSP_ADDRESS, MII_EXPAND_SERDES_CTL);
	bnx2_पढ़ो_phy(bp, MII_BNX2_DSP_RW_PORT, &val);
	अगर (start)
		bnx2_ग_लिखो_phy(bp, MII_BNX2_DSP_RW_PORT, val & 0xff0f);
	अन्यथा
		bnx2_ग_लिखो_phy(bp, MII_BNX2_DSP_RW_PORT, val | 0xc0);
पूर्ण

अटल पूर्णांक
bnx2_set_link(काष्ठा bnx2 *bp)
अणु
	u32 bmsr;
	u8 link_up;

	अगर (bp->loopback == MAC_LOOPBACK || bp->loopback == PHY_LOOPBACK) अणु
		bp->link_up = 1;
		वापस 0;
	पूर्ण

	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		वापस 0;

	link_up = bp->link_up;

	bnx2_enable_bmsr1(bp);
	bnx2_पढ़ो_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_पढ़ो_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_disable_bmsr1(bp);

	अगर ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
	    (BNX2_CHIP(bp) == BNX2_CHIP_5706)) अणु
		u32 val, an_dbg;

		अगर (bp->phy_flags & BNX2_PHY_FLAG_FORCED_DOWN) अणु
			bnx2_5706s_क्रमce_link_dn(bp, 0);
			bp->phy_flags &= ~BNX2_PHY_FLAG_FORCED_DOWN;
		पूर्ण
		val = BNX2_RD(bp, BNX2_EMAC_STATUS);

		bnx2_ग_लिखो_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_AN_DBG);
		bnx2_पढ़ो_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);
		bnx2_पढ़ो_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);

		अगर ((val & BNX2_EMAC_STATUS_LINK) &&
		    !(an_dbg & MISC_SHDW_AN_DBG_NOSYNC))
			bmsr |= BMSR_LSTATUS;
		अन्यथा
			bmsr &= ~BMSR_LSTATUS;
	पूर्ण

	अगर (bmsr & BMSR_LSTATUS) अणु
		bp->link_up = 1;

		अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
			अगर (BNX2_CHIP(bp) == BNX2_CHIP_5706)
				bnx2_5706s_linkup(bp);
			अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5708)
				bnx2_5708s_linkup(bp);
			अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
				bnx2_5709s_linkup(bp);
		पूर्ण
		अन्यथा अणु
			bnx2_copper_linkup(bp);
		पूर्ण
		bnx2_resolve_flow_ctrl(bp);
	पूर्ण
	अन्यथा अणु
		अगर ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
		    (bp->स्वतःneg & AUTONEG_SPEED))
			bnx2_disable_क्रमced_2g5(bp);

		अगर (bp->phy_flags & BNX2_PHY_FLAG_PARALLEL_DETECT) अणु
			u32 bmcr;

			bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
			bmcr |= BMCR_ANENABLE;
			bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr);

			bp->phy_flags &= ~BNX2_PHY_FLAG_PARALLEL_DETECT;
		पूर्ण
		bp->link_up = 0;
	पूर्ण

	अगर (bp->link_up != link_up) अणु
		bnx2_report_link(bp);
	पूर्ण

	bnx2_set_mac_link(bp);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_reset_phy(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	u32 reg;

        bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, BMCR_RESET);

#घोषणा PHY_RESET_MAX_WAIT 100
	क्रम (i = 0; i < PHY_RESET_MAX_WAIT; i++) अणु
		udelay(10);

		bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &reg);
		अगर (!(reg & BMCR_RESET)) अणु
			udelay(20);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == PHY_RESET_MAX_WAIT) अणु
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32
bnx2_phy_get_छोड़ो_adv(काष्ठा bnx2 *bp)
अणु
	u32 adv = 0;

	अगर ((bp->req_flow_ctrl & (FLOW_CTRL_RX | FLOW_CTRL_TX)) ==
		(FLOW_CTRL_RX | FLOW_CTRL_TX)) अणु

		अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
			adv = ADVERTISE_1000XPAUSE;
		पूर्ण
		अन्यथा अणु
			adv = ADVERTISE_PAUSE_CAP;
		पूर्ण
	पूर्ण
	अन्यथा अगर (bp->req_flow_ctrl & FLOW_CTRL_TX) अणु
		अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
			adv = ADVERTISE_1000XPSE_ASYM;
		पूर्ण
		अन्यथा अणु
			adv = ADVERTISE_PAUSE_ASYM;
		पूर्ण
	पूर्ण
	अन्यथा अगर (bp->req_flow_ctrl & FLOW_CTRL_RX) अणु
		अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
			adv = ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM;
		पूर्ण
		अन्यथा अणु
			adv = ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		पूर्ण
	पूर्ण
	वापस adv;
पूर्ण

अटल पूर्णांक bnx2_fw_sync(काष्ठा bnx2 *, u32, पूर्णांक, पूर्णांक);

अटल पूर्णांक
bnx2_setup_remote_phy(काष्ठा bnx2 *bp, u8 port)
__releases(&bp->phy_lock)
__acquires(&bp->phy_lock)
अणु
	u32 speed_arg = 0, छोड़ो_adv;

	छोड़ो_adv = bnx2_phy_get_छोड़ो_adv(bp);

	अगर (bp->स्वतःneg & AUTONEG_SPEED) अणु
		speed_arg |= BNX2_NETLINK_SET_LINK_ENABLE_AUTONEG;
		अगर (bp->advertising & ADVERTISED_10baseT_Half)
			speed_arg |= BNX2_NETLINK_SET_LINK_SPEED_10HALF;
		अगर (bp->advertising & ADVERTISED_10baseT_Full)
			speed_arg |= BNX2_NETLINK_SET_LINK_SPEED_10FULL;
		अगर (bp->advertising & ADVERTISED_100baseT_Half)
			speed_arg |= BNX2_NETLINK_SET_LINK_SPEED_100HALF;
		अगर (bp->advertising & ADVERTISED_100baseT_Full)
			speed_arg |= BNX2_NETLINK_SET_LINK_SPEED_100FULL;
		अगर (bp->advertising & ADVERTISED_1000baseT_Full)
			speed_arg |= BNX2_NETLINK_SET_LINK_SPEED_1GFULL;
		अगर (bp->advertising & ADVERTISED_2500baseX_Full)
			speed_arg |= BNX2_NETLINK_SET_LINK_SPEED_2G5FULL;
	पूर्ण अन्यथा अणु
		अगर (bp->req_line_speed == SPEED_2500)
			speed_arg = BNX2_NETLINK_SET_LINK_SPEED_2G5FULL;
		अन्यथा अगर (bp->req_line_speed == SPEED_1000)
			speed_arg = BNX2_NETLINK_SET_LINK_SPEED_1GFULL;
		अन्यथा अगर (bp->req_line_speed == SPEED_100) अणु
			अगर (bp->req_duplex == DUPLEX_FULL)
				speed_arg = BNX2_NETLINK_SET_LINK_SPEED_100FULL;
			अन्यथा
				speed_arg = BNX2_NETLINK_SET_LINK_SPEED_100HALF;
		पूर्ण अन्यथा अगर (bp->req_line_speed == SPEED_10) अणु
			अगर (bp->req_duplex == DUPLEX_FULL)
				speed_arg = BNX2_NETLINK_SET_LINK_SPEED_10FULL;
			अन्यथा
				speed_arg = BNX2_NETLINK_SET_LINK_SPEED_10HALF;
		पूर्ण
	पूर्ण

	अगर (छोड़ो_adv & (ADVERTISE_1000XPAUSE | ADVERTISE_PAUSE_CAP))
		speed_arg |= BNX2_NETLINK_SET_LINK_FC_SYM_PAUSE;
	अगर (छोड़ो_adv & (ADVERTISE_1000XPSE_ASYM | ADVERTISE_PAUSE_ASYM))
		speed_arg |= BNX2_NETLINK_SET_LINK_FC_ASYM_PAUSE;

	अगर (port == PORT_TP)
		speed_arg |= BNX2_NETLINK_SET_LINK_PHY_APP_REMOTE |
			     BNX2_NETLINK_SET_LINK_ETH_AT_WIRESPEED;

	bnx2_shmem_wr(bp, BNX2_DRV_MB_ARG0, speed_arg);

	spin_unlock_bh(&bp->phy_lock);
	bnx2_fw_sync(bp, BNX2_DRV_MSG_CODE_CMD_SET_LINK, 1, 0);
	spin_lock_bh(&bp->phy_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_setup_serdes_phy(काष्ठा bnx2 *bp, u8 port)
__releases(&bp->phy_lock)
__acquires(&bp->phy_lock)
अणु
	u32 adv, bmcr;
	u32 new_adv = 0;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		वापस bnx2_setup_remote_phy(bp, port);

	अगर (!(bp->स्वतःneg & AUTONEG_SPEED)) अणु
		u32 new_bmcr;
		पूर्णांक क्रमce_link_करोwn = 0;

		अगर (bp->req_line_speed == SPEED_2500) अणु
			अगर (!bnx2_test_and_enable_2g5(bp))
				क्रमce_link_करोwn = 1;
		पूर्ण अन्यथा अगर (bp->req_line_speed == SPEED_1000) अणु
			अगर (bnx2_test_and_disable_2g5(bp))
				क्रमce_link_करोwn = 1;
		पूर्ण
		bnx2_पढ़ो_phy(bp, bp->mii_adv, &adv);
		adv &= ~(ADVERTISE_1000XFULL | ADVERTISE_1000XHALF);

		bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
		new_bmcr = bmcr & ~BMCR_ANENABLE;
		new_bmcr |= BMCR_SPEED1000;

		अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
			अगर (bp->req_line_speed == SPEED_2500)
				bnx2_enable_क्रमced_2g5(bp);
			अन्यथा अगर (bp->req_line_speed == SPEED_1000) अणु
				bnx2_disable_क्रमced_2g5(bp);
				new_bmcr &= ~0x2000;
			पूर्ण

		पूर्ण अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5708) अणु
			अगर (bp->req_line_speed == SPEED_2500)
				new_bmcr |= BCM5708S_BMCR_FORCE_2500;
			अन्यथा
				new_bmcr = bmcr & ~BCM5708S_BMCR_FORCE_2500;
		पूर्ण

		अगर (bp->req_duplex == DUPLEX_FULL) अणु
			adv |= ADVERTISE_1000XFULL;
			new_bmcr |= BMCR_FULLDPLX;
		पूर्ण
		अन्यथा अणु
			adv |= ADVERTISE_1000XHALF;
			new_bmcr &= ~BMCR_FULLDPLX;
		पूर्ण
		अगर ((new_bmcr != bmcr) || (क्रमce_link_करोwn)) अणु
			/* Force a link करोwn visible on the other side */
			अगर (bp->link_up) अणु
				bnx2_ग_लिखो_phy(bp, bp->mii_adv, adv &
					       ~(ADVERTISE_1000XFULL |
						 ADVERTISE_1000XHALF));
				bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr |
					BMCR_ANRESTART | BMCR_ANENABLE);

				bp->link_up = 0;
				netअगर_carrier_off(bp->dev);
				bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, new_bmcr);
				bnx2_report_link(bp);
			पूर्ण
			bnx2_ग_लिखो_phy(bp, bp->mii_adv, adv);
			bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, new_bmcr);
		पूर्ण अन्यथा अणु
			bnx2_resolve_flow_ctrl(bp);
			bnx2_set_mac_link(bp);
		पूर्ण
		वापस 0;
	पूर्ण

	bnx2_test_and_enable_2g5(bp);

	अगर (bp->advertising & ADVERTISED_1000baseT_Full)
		new_adv |= ADVERTISE_1000XFULL;

	new_adv |= bnx2_phy_get_छोड़ो_adv(bp);

	bnx2_पढ़ो_phy(bp, bp->mii_adv, &adv);
	bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);

	bp->serdes_an_pending = 0;
	अगर ((adv != new_adv) || ((bmcr & BMCR_ANENABLE) == 0)) अणु
		/* Force a link करोwn visible on the other side */
		अगर (bp->link_up) अणु
			bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, BMCR_LOOPBACK);
			spin_unlock_bh(&bp->phy_lock);
			msleep(20);
			spin_lock_bh(&bp->phy_lock);
		पूर्ण

		bnx2_ग_लिखो_phy(bp, bp->mii_adv, new_adv);
		bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr | BMCR_ANRESTART |
			BMCR_ANENABLE);
		/* Speed up link-up समय when the link partner
		 * करोes not स्वतःnegotiate which is very common
		 * in blade servers. Some blade servers use
		 * IPMI क्रम kerboard input and it's important
		 * to minimize link disruptions. Autoneg. involves
		 * exchanging base pages plus 3 next pages and
		 * normally completes in about 120 msec.
		 */
		bp->current_पूर्णांकerval = BNX2_SERDES_AN_TIMEOUT;
		bp->serdes_an_pending = 1;
		mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);
	पूर्ण अन्यथा अणु
		bnx2_resolve_flow_ctrl(bp);
		bnx2_set_mac_link(bp);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ETHTOOL_ALL_FIBRE_SPEED						\
	(bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE) ?			\
		(ADVERTISED_2500baseX_Full | ADVERTISED_1000baseT_Full) :\
		(ADVERTISED_1000baseT_Full)

#घोषणा ETHTOOL_ALL_COPPER_SPEED					\
	(ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full |		\
	ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full |		\
	ADVERTISED_1000baseT_Full)

#घोषणा PHY_ALL_10_100_SPEED (ADVERTISE_10HALF | ADVERTISE_10FULL | \
	ADVERTISE_100HALF | ADVERTISE_100FULL | ADVERTISE_CSMA)

#घोषणा PHY_ALL_1000_SPEED (ADVERTISE_1000HALF | ADVERTISE_1000FULL)

अटल व्योम
bnx2_set_शेष_remote_link(काष्ठा bnx2 *bp)
अणु
	u32 link;

	अगर (bp->phy_port == PORT_TP)
		link = bnx2_shmem_rd(bp, BNX2_RPHY_COPPER_LINK);
	अन्यथा
		link = bnx2_shmem_rd(bp, BNX2_RPHY_SERDES_LINK);

	अगर (link & BNX2_NETLINK_SET_LINK_ENABLE_AUTONEG) अणु
		bp->req_line_speed = 0;
		bp->स्वतःneg |= AUTONEG_SPEED;
		bp->advertising = ADVERTISED_Autoneg;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_10HALF)
			bp->advertising |= ADVERTISED_10baseT_Half;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_10FULL)
			bp->advertising |= ADVERTISED_10baseT_Full;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_100HALF)
			bp->advertising |= ADVERTISED_100baseT_Half;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_100FULL)
			bp->advertising |= ADVERTISED_100baseT_Full;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_1GFULL)
			bp->advertising |= ADVERTISED_1000baseT_Full;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_2G5FULL)
			bp->advertising |= ADVERTISED_2500baseX_Full;
	पूर्ण अन्यथा अणु
		bp->स्वतःneg = 0;
		bp->advertising = 0;
		bp->req_duplex = DUPLEX_FULL;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_10) अणु
			bp->req_line_speed = SPEED_10;
			अगर (link & BNX2_NETLINK_SET_LINK_SPEED_10HALF)
				bp->req_duplex = DUPLEX_HALF;
		पूर्ण
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_100) अणु
			bp->req_line_speed = SPEED_100;
			अगर (link & BNX2_NETLINK_SET_LINK_SPEED_100HALF)
				bp->req_duplex = DUPLEX_HALF;
		पूर्ण
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_1GFULL)
			bp->req_line_speed = SPEED_1000;
		अगर (link & BNX2_NETLINK_SET_LINK_SPEED_2G5FULL)
			bp->req_line_speed = SPEED_2500;
	पूर्ण
पूर्ण

अटल व्योम
bnx2_set_शेष_link(काष्ठा bnx2 *bp)
अणु
	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) अणु
		bnx2_set_शेष_remote_link(bp);
		वापस;
	पूर्ण

	bp->स्वतःneg = AUTONEG_SPEED | AUTONEG_FLOW_CTRL;
	bp->req_line_speed = 0;
	अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
		u32 reg;

		bp->advertising = ETHTOOL_ALL_FIBRE_SPEED | ADVERTISED_Autoneg;

		reg = bnx2_shmem_rd(bp, BNX2_PORT_HW_CFG_CONFIG);
		reg &= BNX2_PORT_HW_CFG_CFG_DFLT_LINK_MASK;
		अगर (reg == BNX2_PORT_HW_CFG_CFG_DFLT_LINK_1G) अणु
			bp->स्वतःneg = 0;
			bp->req_line_speed = bp->line_speed = SPEED_1000;
			bp->req_duplex = DUPLEX_FULL;
		पूर्ण
	पूर्ण अन्यथा
		bp->advertising = ETHTOOL_ALL_COPPER_SPEED | ADVERTISED_Autoneg;
पूर्ण

अटल व्योम
bnx2_send_heart_beat(काष्ठा bnx2 *bp)
अणु
	u32 msg;
	u32 addr;

	spin_lock(&bp->indirect_lock);
	msg = (u32) (++bp->fw_drv_pulse_wr_seq & BNX2_DRV_PULSE_SEQ_MASK);
	addr = bp->shmem_base + BNX2_DRV_PULSE_MB;
	BNX2_WR(bp, BNX2_PCICFG_REG_WINDOW_ADDRESS, addr);
	BNX2_WR(bp, BNX2_PCICFG_REG_WINDOW, msg);
	spin_unlock(&bp->indirect_lock);
पूर्ण

अटल व्योम
bnx2_remote_phy_event(काष्ठा bnx2 *bp)
अणु
	u32 msg;
	u8 link_up = bp->link_up;
	u8 old_port;

	msg = bnx2_shmem_rd(bp, BNX2_LINK_STATUS);

	अगर (msg & BNX2_LINK_STATUS_HEART_BEAT_EXPIRED)
		bnx2_send_heart_beat(bp);

	msg &= ~BNX2_LINK_STATUS_HEART_BEAT_EXPIRED;

	अगर ((msg & BNX2_LINK_STATUS_LINK_UP) == BNX2_LINK_STATUS_LINK_DOWN)
		bp->link_up = 0;
	अन्यथा अणु
		u32 speed;

		bp->link_up = 1;
		speed = msg & BNX2_LINK_STATUS_SPEED_MASK;
		bp->duplex = DUPLEX_FULL;
		चयन (speed) अणु
			हाल BNX2_LINK_STATUS_10HALF:
				bp->duplex = DUPLEX_HALF;
				fallthrough;
			हाल BNX2_LINK_STATUS_10FULL:
				bp->line_speed = SPEED_10;
				अवरोध;
			हाल BNX2_LINK_STATUS_100HALF:
				bp->duplex = DUPLEX_HALF;
				fallthrough;
			हाल BNX2_LINK_STATUS_100BASE_T4:
			हाल BNX2_LINK_STATUS_100FULL:
				bp->line_speed = SPEED_100;
				अवरोध;
			हाल BNX2_LINK_STATUS_1000HALF:
				bp->duplex = DUPLEX_HALF;
				fallthrough;
			हाल BNX2_LINK_STATUS_1000FULL:
				bp->line_speed = SPEED_1000;
				अवरोध;
			हाल BNX2_LINK_STATUS_2500HALF:
				bp->duplex = DUPLEX_HALF;
				fallthrough;
			हाल BNX2_LINK_STATUS_2500FULL:
				bp->line_speed = SPEED_2500;
				अवरोध;
			शेष:
				bp->line_speed = 0;
				अवरोध;
		पूर्ण

		bp->flow_ctrl = 0;
		अगर ((bp->स्वतःneg & (AUTONEG_SPEED | AUTONEG_FLOW_CTRL)) !=
		    (AUTONEG_SPEED | AUTONEG_FLOW_CTRL)) अणु
			अगर (bp->duplex == DUPLEX_FULL)
				bp->flow_ctrl = bp->req_flow_ctrl;
		पूर्ण अन्यथा अणु
			अगर (msg & BNX2_LINK_STATUS_TX_FC_ENABLED)
				bp->flow_ctrl |= FLOW_CTRL_TX;
			अगर (msg & BNX2_LINK_STATUS_RX_FC_ENABLED)
				bp->flow_ctrl |= FLOW_CTRL_RX;
		पूर्ण

		old_port = bp->phy_port;
		अगर (msg & BNX2_LINK_STATUS_SERDES_LINK)
			bp->phy_port = PORT_FIBRE;
		अन्यथा
			bp->phy_port = PORT_TP;

		अगर (old_port != bp->phy_port)
			bnx2_set_शेष_link(bp);

	पूर्ण
	अगर (bp->link_up != link_up)
		bnx2_report_link(bp);

	bnx2_set_mac_link(bp);
पूर्ण

अटल पूर्णांक
bnx2_set_remote_link(काष्ठा bnx2 *bp)
अणु
	u32 evt_code;

	evt_code = bnx2_shmem_rd(bp, BNX2_FW_EVT_CODE_MB);
	चयन (evt_code) अणु
		हाल BNX2_FW_EVT_CODE_LINK_EVENT:
			bnx2_remote_phy_event(bp);
			अवरोध;
		हाल BNX2_FW_EVT_CODE_SW_TIMER_EXPIRATION_EVENT:
		शेष:
			bnx2_send_heart_beat(bp);
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_setup_copper_phy(काष्ठा bnx2 *bp)
__releases(&bp->phy_lock)
__acquires(&bp->phy_lock)
अणु
	u32 bmcr, adv_reg, new_adv = 0;
	u32 new_bmcr;

	bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);

	bnx2_पढ़ो_phy(bp, bp->mii_adv, &adv_reg);
	adv_reg &= (PHY_ALL_10_100_SPEED | ADVERTISE_PAUSE_CAP |
		    ADVERTISE_PAUSE_ASYM);

	new_adv = ADVERTISE_CSMA | ethtool_adv_to_mii_adv_t(bp->advertising);

	अगर (bp->स्वतःneg & AUTONEG_SPEED) अणु
		u32 adv1000_reg;
		u32 new_adv1000 = 0;

		new_adv |= bnx2_phy_get_छोड़ो_adv(bp);

		bnx2_पढ़ो_phy(bp, MII_CTRL1000, &adv1000_reg);
		adv1000_reg &= PHY_ALL_1000_SPEED;

		new_adv1000 |= ethtool_adv_to_mii_ctrl1000_t(bp->advertising);
		अगर ((adv1000_reg != new_adv1000) ||
			(adv_reg != new_adv) ||
			((bmcr & BMCR_ANENABLE) == 0)) अणु

			bnx2_ग_लिखो_phy(bp, bp->mii_adv, new_adv);
			bnx2_ग_लिखो_phy(bp, MII_CTRL1000, new_adv1000);
			bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, BMCR_ANRESTART |
				BMCR_ANENABLE);
		पूर्ण
		अन्यथा अगर (bp->link_up) अणु
			/* Flow ctrl may have changed from स्वतः to क्रमced */
			/* or vice-versa. */

			bnx2_resolve_flow_ctrl(bp);
			bnx2_set_mac_link(bp);
		पूर्ण
		वापस 0;
	पूर्ण

	/* advertise nothing when क्रमcing speed */
	अगर (adv_reg != new_adv)
		bnx2_ग_लिखो_phy(bp, bp->mii_adv, new_adv);

	new_bmcr = 0;
	अगर (bp->req_line_speed == SPEED_100) अणु
		new_bmcr |= BMCR_SPEED100;
	पूर्ण
	अगर (bp->req_duplex == DUPLEX_FULL) अणु
		new_bmcr |= BMCR_FULLDPLX;
	पूर्ण
	अगर (new_bmcr != bmcr) अणु
		u32 bmsr;

		bnx2_पढ़ो_phy(bp, bp->mii_bmsr, &bmsr);
		bnx2_पढ़ो_phy(bp, bp->mii_bmsr, &bmsr);

		अगर (bmsr & BMSR_LSTATUS) अणु
			/* Force link करोwn */
			bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, BMCR_LOOPBACK);
			spin_unlock_bh(&bp->phy_lock);
			msleep(50);
			spin_lock_bh(&bp->phy_lock);

			bnx2_पढ़ो_phy(bp, bp->mii_bmsr, &bmsr);
			bnx2_पढ़ो_phy(bp, bp->mii_bmsr, &bmsr);
		पूर्ण

		bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, new_bmcr);

		/* Normally, the new speed is setup after the link has
		 * gone करोwn and up again. In some हालs, link will not go
		 * करोwn so we need to set up the new speed here.
		 */
		अगर (bmsr & BMSR_LSTATUS) अणु
			bp->line_speed = bp->req_line_speed;
			bp->duplex = bp->req_duplex;
			bnx2_resolve_flow_ctrl(bp);
			bnx2_set_mac_link(bp);
		पूर्ण
	पूर्ण अन्यथा अणु
		bnx2_resolve_flow_ctrl(bp);
		bnx2_set_mac_link(bp);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_setup_phy(काष्ठा bnx2 *bp, u8 port)
__releases(&bp->phy_lock)
__acquires(&bp->phy_lock)
अणु
	अगर (bp->loopback == MAC_LOOPBACK)
		वापस 0;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
		वापस bnx2_setup_serdes_phy(bp, port);
	पूर्ण
	अन्यथा अणु
		वापस bnx2_setup_copper_phy(bp);
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2_init_5709s_phy(काष्ठा bnx2 *bp, पूर्णांक reset_phy)
अणु
	u32 val;

	bp->mii_bmcr = MII_BMCR + 0x10;
	bp->mii_bmsr = MII_BMSR + 0x10;
	bp->mii_bmsr1 = MII_BNX2_GP_TOP_AN_STATUS1;
	bp->mii_adv = MII_ADVERTISE + 0x10;
	bp->mii_lpa = MII_LPA + 0x10;
	bp->mii_up1 = MII_BNX2_OVER1G_UP1;

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_AER);
	bnx2_ग_लिखो_phy(bp, MII_BNX2_AER_AER, MII_BNX2_AER_AER_AN_MMD);

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_COMBO_IEEEB0);
	अगर (reset_phy)
		bnx2_reset_phy(bp);

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_SERDES_DIG);

	bnx2_पढ़ो_phy(bp, MII_BNX2_SERDES_DIG_1000XCTL1, &val);
	val &= ~MII_BNX2_SD_1000XCTL1_AUTODET;
	val |= MII_BNX2_SD_1000XCTL1_FIBER;
	bnx2_ग_लिखो_phy(bp, MII_BNX2_SERDES_DIG_1000XCTL1, val);

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_OVER1G);
	bnx2_पढ़ो_phy(bp, MII_BNX2_OVER1G_UP1, &val);
	अगर (bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE)
		val |= BCM5708S_UP1_2G5;
	अन्यथा
		val &= ~BCM5708S_UP1_2G5;
	bnx2_ग_लिखो_phy(bp, MII_BNX2_OVER1G_UP1, val);

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_BAM_NXTPG);
	bnx2_पढ़ो_phy(bp, MII_BNX2_BAM_NXTPG_CTL, &val);
	val |= MII_BNX2_NXTPG_CTL_T2 | MII_BNX2_NXTPG_CTL_BAM;
	bnx2_ग_लिखो_phy(bp, MII_BNX2_BAM_NXTPG_CTL, val);

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_CL73_USERB0);

	val = MII_BNX2_CL73_BAM_EN | MII_BNX2_CL73_BAM_STA_MGR_EN |
	      MII_BNX2_CL73_BAM_NP_AFT_BP_EN;
	bnx2_ग_लिखो_phy(bp, MII_BNX2_CL73_BAM_CTL1, val);

	bnx2_ग_लिखो_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_COMBO_IEEEB0);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_init_5708s_phy(काष्ठा bnx2 *bp, पूर्णांक reset_phy)
अणु
	u32 val;

	अगर (reset_phy)
		bnx2_reset_phy(bp);

	bp->mii_up1 = BCM5708S_UP1;

	bnx2_ग_लिखो_phy(bp, BCM5708S_BLK_ADDR, BCM5708S_BLK_ADDR_DIG3);
	bnx2_ग_लिखो_phy(bp, BCM5708S_DIG_3_0, BCM5708S_DIG_3_0_USE_IEEE);
	bnx2_ग_लिखो_phy(bp, BCM5708S_BLK_ADDR, BCM5708S_BLK_ADDR_DIG);

	bnx2_पढ़ो_phy(bp, BCM5708S_1000X_CTL1, &val);
	val |= BCM5708S_1000X_CTL1_FIBER_MODE | BCM5708S_1000X_CTL1_AUTODET_EN;
	bnx2_ग_लिखो_phy(bp, BCM5708S_1000X_CTL1, val);

	bnx2_पढ़ो_phy(bp, BCM5708S_1000X_CTL2, &val);
	val |= BCM5708S_1000X_CTL2_PLLEL_DET_EN;
	bnx2_ग_लिखो_phy(bp, BCM5708S_1000X_CTL2, val);

	अगर (bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE) अणु
		bnx2_पढ़ो_phy(bp, BCM5708S_UP1, &val);
		val |= BCM5708S_UP1_2G5;
		bnx2_ग_लिखो_phy(bp, BCM5708S_UP1, val);
	पूर्ण

	अगर ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_A0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_B0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_B1)) अणु
		/* increase tx संकेत amplitude */
		bnx2_ग_लिखो_phy(bp, BCM5708S_BLK_ADDR,
			       BCM5708S_BLK_ADDR_TX_MISC);
		bnx2_पढ़ो_phy(bp, BCM5708S_TX_ACTL1, &val);
		val &= ~BCM5708S_TX_ACTL1_DRIVER_VCM;
		bnx2_ग_लिखो_phy(bp, BCM5708S_TX_ACTL1, val);
		bnx2_ग_लिखो_phy(bp, BCM5708S_BLK_ADDR, BCM5708S_BLK_ADDR_DIG);
	पूर्ण

	val = bnx2_shmem_rd(bp, BNX2_PORT_HW_CFG_CONFIG) &
	      BNX2_PORT_HW_CFG_CFG_TXCTL3_MASK;

	अगर (val) अणु
		u32 is_backplane;

		is_backplane = bnx2_shmem_rd(bp, BNX2_SHARED_HW_CFG_CONFIG);
		अगर (is_backplane & BNX2_SHARED_HW_CFG_PHY_BACKPLANE) अणु
			bnx2_ग_लिखो_phy(bp, BCM5708S_BLK_ADDR,
				       BCM5708S_BLK_ADDR_TX_MISC);
			bnx2_ग_लिखो_phy(bp, BCM5708S_TX_ACTL3, val);
			bnx2_ग_लिखो_phy(bp, BCM5708S_BLK_ADDR,
				       BCM5708S_BLK_ADDR_DIG);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_init_5706s_phy(काष्ठा bnx2 *bp, पूर्णांक reset_phy)
अणु
	अगर (reset_phy)
		bnx2_reset_phy(bp);

	bp->phy_flags &= ~BNX2_PHY_FLAG_PARALLEL_DETECT;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5706)
		BNX2_WR(bp, BNX2_MISC_GP_HW_CTL0, 0x300);

	अगर (bp->dev->mtu > ETH_DATA_LEN) अणु
		u32 val;

		/* Set extended packet length bit */
		bnx2_ग_लिखो_phy(bp, 0x18, 0x7);
		bnx2_पढ़ो_phy(bp, 0x18, &val);
		bnx2_ग_लिखो_phy(bp, 0x18, (val & 0xfff8) | 0x4000);

		bnx2_ग_लिखो_phy(bp, 0x1c, 0x6c00);
		bnx2_पढ़ो_phy(bp, 0x1c, &val);
		bnx2_ग_लिखो_phy(bp, 0x1c, (val & 0x3ff) | 0xec02);
	पूर्ण
	अन्यथा अणु
		u32 val;

		bnx2_ग_लिखो_phy(bp, 0x18, 0x7);
		bnx2_पढ़ो_phy(bp, 0x18, &val);
		bnx2_ग_लिखो_phy(bp, 0x18, val & ~0x4007);

		bnx2_ग_लिखो_phy(bp, 0x1c, 0x6c00);
		bnx2_पढ़ो_phy(bp, 0x1c, &val);
		bnx2_ग_लिखो_phy(bp, 0x1c, (val & 0x3fd) | 0xec00);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_init_copper_phy(काष्ठा bnx2 *bp, पूर्णांक reset_phy)
अणु
	u32 val;

	अगर (reset_phy)
		bnx2_reset_phy(bp);

	अगर (bp->phy_flags & BNX2_PHY_FLAG_CRC_FIX) अणु
		bnx2_ग_लिखो_phy(bp, 0x18, 0x0c00);
		bnx2_ग_लिखो_phy(bp, 0x17, 0x000a);
		bnx2_ग_लिखो_phy(bp, 0x15, 0x310b);
		bnx2_ग_लिखो_phy(bp, 0x17, 0x201f);
		bnx2_ग_लिखो_phy(bp, 0x15, 0x9506);
		bnx2_ग_लिखो_phy(bp, 0x17, 0x401f);
		bnx2_ग_लिखो_phy(bp, 0x15, 0x14e2);
		bnx2_ग_लिखो_phy(bp, 0x18, 0x0400);
	पूर्ण

	अगर (bp->phy_flags & BNX2_PHY_FLAG_DIS_EARLY_DAC) अणु
		bnx2_ग_लिखो_phy(bp, MII_BNX2_DSP_ADDRESS,
			       MII_BNX2_DSP_EXPAND_REG | 0x8);
		bnx2_पढ़ो_phy(bp, MII_BNX2_DSP_RW_PORT, &val);
		val &= ~(1 << 8);
		bnx2_ग_लिखो_phy(bp, MII_BNX2_DSP_RW_PORT, val);
	पूर्ण

	अगर (bp->dev->mtu > ETH_DATA_LEN) अणु
		/* Set extended packet length bit */
		bnx2_ग_लिखो_phy(bp, 0x18, 0x7);
		bnx2_पढ़ो_phy(bp, 0x18, &val);
		bnx2_ग_लिखो_phy(bp, 0x18, val | 0x4000);

		bnx2_पढ़ो_phy(bp, 0x10, &val);
		bnx2_ग_लिखो_phy(bp, 0x10, val | 0x1);
	पूर्ण
	अन्यथा अणु
		bnx2_ग_लिखो_phy(bp, 0x18, 0x7);
		bnx2_पढ़ो_phy(bp, 0x18, &val);
		bnx2_ग_लिखो_phy(bp, 0x18, val & ~0x4007);

		bnx2_पढ़ो_phy(bp, 0x10, &val);
		bnx2_ग_लिखो_phy(bp, 0x10, val & ~0x1);
	पूर्ण

	/* ethernet@wirespeed */
	bnx2_ग_लिखो_phy(bp, MII_BNX2_AUX_CTL, AUX_CTL_MISC_CTL);
	bnx2_पढ़ो_phy(bp, MII_BNX2_AUX_CTL, &val);
	val |=  AUX_CTL_MISC_CTL_WR | AUX_CTL_MISC_CTL_WIRESPEED;

	/* स्वतः-mdix */
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		val |=  AUX_CTL_MISC_CTL_AUTOMDIX;

	bnx2_ग_लिखो_phy(bp, MII_BNX2_AUX_CTL, val);
	वापस 0;
पूर्ण


अटल पूर्णांक
bnx2_init_phy(काष्ठा bnx2 *bp, पूर्णांक reset_phy)
__releases(&bp->phy_lock)
__acquires(&bp->phy_lock)
अणु
	u32 val;
	पूर्णांक rc = 0;

	bp->phy_flags &= ~BNX2_PHY_FLAG_INT_MODE_MASK;
	bp->phy_flags |= BNX2_PHY_FLAG_INT_MODE_LINK_READY;

	bp->mii_bmcr = MII_BMCR;
	bp->mii_bmsr = MII_BMSR;
	bp->mii_bmsr1 = MII_BMSR;
	bp->mii_adv = MII_ADVERTISE;
	bp->mii_lpa = MII_LPA;

	BNX2_WR(bp, BNX2_EMAC_ATTENTION_ENA, BNX2_EMAC_ATTENTION_ENA_LINK);

	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		जाओ setup_phy;

	bnx2_पढ़ो_phy(bp, MII_PHYSID1, &val);
	bp->phy_id = val << 16;
	bnx2_पढ़ो_phy(bp, MII_PHYSID2, &val);
	bp->phy_id |= val & 0xffff;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
		अगर (BNX2_CHIP(bp) == BNX2_CHIP_5706)
			rc = bnx2_init_5706s_phy(bp, reset_phy);
		अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5708)
			rc = bnx2_init_5708s_phy(bp, reset_phy);
		अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
			rc = bnx2_init_5709s_phy(bp, reset_phy);
	पूर्ण
	अन्यथा अणु
		rc = bnx2_init_copper_phy(bp, reset_phy);
	पूर्ण

setup_phy:
	अगर (!rc)
		rc = bnx2_setup_phy(bp, bp->phy_port);

	वापस rc;
पूर्ण

अटल पूर्णांक
bnx2_set_mac_loopback(काष्ठा bnx2 *bp)
अणु
	u32 mac_mode;

	mac_mode = BNX2_RD(bp, BNX2_EMAC_MODE);
	mac_mode &= ~BNX2_EMAC_MODE_PORT;
	mac_mode |= BNX2_EMAC_MODE_MAC_LOOP | BNX2_EMAC_MODE_FORCE_LINK;
	BNX2_WR(bp, BNX2_EMAC_MODE, mac_mode);
	bp->link_up = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2_test_link(काष्ठा bnx2 *);

अटल पूर्णांक
bnx2_set_phy_loopback(काष्ठा bnx2 *bp)
अणु
	u32 mac_mode;
	पूर्णांक rc, i;

	spin_lock_bh(&bp->phy_lock);
	rc = bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, BMCR_LOOPBACK | BMCR_FULLDPLX |
			    BMCR_SPEED1000);
	spin_unlock_bh(&bp->phy_lock);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < 10; i++) अणु
		अगर (bnx2_test_link(bp) == 0)
			अवरोध;
		msleep(100);
	पूर्ण

	mac_mode = BNX2_RD(bp, BNX2_EMAC_MODE);
	mac_mode &= ~(BNX2_EMAC_MODE_PORT | BNX2_EMAC_MODE_HALF_DUPLEX |
		      BNX2_EMAC_MODE_MAC_LOOP | BNX2_EMAC_MODE_FORCE_LINK |
		      BNX2_EMAC_MODE_25G_MODE);

	mac_mode |= BNX2_EMAC_MODE_PORT_GMII;
	BNX2_WR(bp, BNX2_EMAC_MODE, mac_mode);
	bp->link_up = 1;
	वापस 0;
पूर्ण

अटल व्योम
bnx2_dump_mcp_state(काष्ठा bnx2 *bp)
अणु
	काष्ठा net_device *dev = bp->dev;
	u32 mcp_p0, mcp_p1;

	netdev_err(dev, "<--- start MCP states dump --->\n");
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		mcp_p0 = BNX2_MCP_STATE_P0;
		mcp_p1 = BNX2_MCP_STATE_P1;
	पूर्ण अन्यथा अणु
		mcp_p0 = BNX2_MCP_STATE_P0_5708;
		mcp_p1 = BNX2_MCP_STATE_P1_5708;
	पूर्ण
	netdev_err(dev, "DEBUG: MCP_STATE_P0[%08x] MCP_STATE_P1[%08x]\n",
		   bnx2_reg_rd_ind(bp, mcp_p0), bnx2_reg_rd_ind(bp, mcp_p1));
	netdev_err(dev, "DEBUG: MCP mode[%08x] state[%08x] evt_mask[%08x]\n",
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_MODE),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_STATE),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_EVENT_MASK));
	netdev_err(dev, "DEBUG: pc[%08x] pc[%08x] instr[%08x]\n",
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_PROGRAM_COUNTER),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_PROGRAM_COUNTER),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_INSTRUCTION));
	netdev_err(dev, "DEBUG: shmem states:\n");
	netdev_err(dev, "DEBUG: drv_mb[%08x] fw_mb[%08x] link_status[%08x]",
		   bnx2_shmem_rd(bp, BNX2_DRV_MB),
		   bnx2_shmem_rd(bp, BNX2_FW_MB),
		   bnx2_shmem_rd(bp, BNX2_LINK_STATUS));
	pr_cont(" drv_pulse_mb[%08x]\n", bnx2_shmem_rd(bp, BNX2_DRV_PULSE_MB));
	netdev_err(dev, "DEBUG: dev_info_signature[%08x] reset_type[%08x]",
		   bnx2_shmem_rd(bp, BNX2_DEV_INFO_SIGNATURE),
		   bnx2_shmem_rd(bp, BNX2_BC_STATE_RESET_TYPE));
	pr_cont(" condition[%08x]\n",
		bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION));
	DP_SHMEM_LINE(bp, BNX2_BC_RESET_TYPE);
	DP_SHMEM_LINE(bp, 0x3cc);
	DP_SHMEM_LINE(bp, 0x3dc);
	DP_SHMEM_LINE(bp, 0x3ec);
	netdev_err(dev, "DEBUG: 0x3fc[%08x]\n", bnx2_shmem_rd(bp, 0x3fc));
	netdev_err(dev, "<--- end MCP states dump --->\n");
पूर्ण

अटल पूर्णांक
bnx2_fw_sync(काष्ठा bnx2 *bp, u32 msg_data, पूर्णांक ack, पूर्णांक silent)
अणु
	पूर्णांक i;
	u32 val;

	bp->fw_wr_seq++;
	msg_data |= bp->fw_wr_seq;
	bp->fw_last_msg = msg_data;

	bnx2_shmem_wr(bp, BNX2_DRV_MB, msg_data);

	अगर (!ack)
		वापस 0;

	/* रुको क्रम an acknowledgement. */
	क्रम (i = 0; i < (BNX2_FW_ACK_TIME_OUT_MS / 10); i++) अणु
		msleep(10);

		val = bnx2_shmem_rd(bp, BNX2_FW_MB);

		अगर ((val & BNX2_FW_MSG_ACK) == (msg_data & BNX2_DRV_MSG_SEQ))
			अवरोध;
	पूर्ण
	अगर ((msg_data & BNX2_DRV_MSG_DATA) == BNX2_DRV_MSG_DATA_WAIT0)
		वापस 0;

	/* If we समयd out, inक्रमm the firmware that this is the हाल. */
	अगर ((val & BNX2_FW_MSG_ACK) != (msg_data & BNX2_DRV_MSG_SEQ)) अणु
		msg_data &= ~BNX2_DRV_MSG_CODE;
		msg_data |= BNX2_DRV_MSG_CODE_FW_TIMEOUT;

		bnx2_shmem_wr(bp, BNX2_DRV_MB, msg_data);
		अगर (!silent) अणु
			pr_err("fw sync timeout, reset code = %x\n", msg_data);
			bnx2_dump_mcp_state(bp);
		पूर्ण

		वापस -EBUSY;
	पूर्ण

	अगर ((val & BNX2_FW_MSG_STATUS_MASK) != BNX2_FW_MSG_STATUS_OK)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_init_5709_context(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i, ret = 0;
	u32 val;

	val = BNX2_CTX_COMMAND_ENABLED | BNX2_CTX_COMMAND_MEM_INIT | (1 << 12);
	val |= (BNX2_PAGE_BITS - 8) << 16;
	BNX2_WR(bp, BNX2_CTX_COMMAND, val);
	क्रम (i = 0; i < 10; i++) अणु
		val = BNX2_RD(bp, BNX2_CTX_COMMAND);
		अगर (!(val & BNX2_CTX_COMMAND_MEM_INIT))
			अवरोध;
		udelay(2);
	पूर्ण
	अगर (val & BNX2_CTX_COMMAND_MEM_INIT)
		वापस -EBUSY;

	क्रम (i = 0; i < bp->ctx_pages; i++) अणु
		पूर्णांक j;

		अगर (bp->ctx_blk[i])
			स_रखो(bp->ctx_blk[i], 0, BNX2_PAGE_SIZE);
		अन्यथा
			वापस -ENOMEM;

		BNX2_WR(bp, BNX2_CTX_HOST_PAGE_TBL_DATA0,
			(bp->ctx_blk_mapping[i] & 0xffffffff) |
			BNX2_CTX_HOST_PAGE_TBL_DATA0_VALID);
		BNX2_WR(bp, BNX2_CTX_HOST_PAGE_TBL_DATA1,
			(u64) bp->ctx_blk_mapping[i] >> 32);
		BNX2_WR(bp, BNX2_CTX_HOST_PAGE_TBL_CTRL, i |
			BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ);
		क्रम (j = 0; j < 10; j++) अणु

			val = BNX2_RD(bp, BNX2_CTX_HOST_PAGE_TBL_CTRL);
			अगर (!(val & BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ))
				अवरोध;
			udelay(5);
		पूर्ण
		अगर (val & BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
bnx2_init_context(काष्ठा bnx2 *bp)
अणु
	u32 vcid;

	vcid = 96;
	जबतक (vcid) अणु
		u32 vcid_addr, pcid_addr, offset;
		पूर्णांक i;

		vcid--;

		अगर (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) अणु
			u32 new_vcid;

			vcid_addr = GET_PCID_ADDR(vcid);
			अगर (vcid & 0x8) अणु
				new_vcid = 0x60 + (vcid & 0xf0) + (vcid & 0x7);
			पूर्ण
			अन्यथा अणु
				new_vcid = vcid;
			पूर्ण
			pcid_addr = GET_PCID_ADDR(new_vcid);
		पूर्ण
		अन्यथा अणु
	    		vcid_addr = GET_CID_ADDR(vcid);
			pcid_addr = vcid_addr;
		पूर्ण

		क्रम (i = 0; i < (CTX_SIZE / PHY_CTX_SIZE); i++) अणु
			vcid_addr += (i << PHY_CTX_SHIFT);
			pcid_addr += (i << PHY_CTX_SHIFT);

			BNX2_WR(bp, BNX2_CTX_VIRT_ADDR, vcid_addr);
			BNX2_WR(bp, BNX2_CTX_PAGE_TBL, pcid_addr);

			/* Zero out the context. */
			क्रम (offset = 0; offset < PHY_CTX_SIZE; offset += 4)
				bnx2_ctx_wr(bp, vcid_addr, offset, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2_alloc_bad_rbuf(काष्ठा bnx2 *bp)
अणु
	u16 *good_mbuf;
	u32 good_mbuf_cnt;
	u32 val;

	good_mbuf = kदो_स्मृति_array(512, माप(u16), GFP_KERNEL);
	अगर (!good_mbuf)
		वापस -ENOMEM;

	BNX2_WR(bp, BNX2_MISC_ENABLE_SET_BITS,
		BNX2_MISC_ENABLE_SET_BITS_RX_MBUF_ENABLE);

	good_mbuf_cnt = 0;

	/* Allocate a bunch of mbufs and save the good ones in an array. */
	val = bnx2_reg_rd_ind(bp, BNX2_RBUF_STATUS1);
	जबतक (val & BNX2_RBUF_STATUS1_FREE_COUNT) अणु
		bnx2_reg_wr_ind(bp, BNX2_RBUF_COMMAND,
				BNX2_RBUF_COMMAND_ALLOC_REQ);

		val = bnx2_reg_rd_ind(bp, BNX2_RBUF_FW_BUF_ALLOC);

		val &= BNX2_RBUF_FW_BUF_ALLOC_VALUE;

		/* The addresses with Bit 9 set are bad memory blocks. */
		अगर (!(val & (1 << 9))) अणु
			good_mbuf[good_mbuf_cnt] = (u16) val;
			good_mbuf_cnt++;
		पूर्ण

		val = bnx2_reg_rd_ind(bp, BNX2_RBUF_STATUS1);
	पूर्ण

	/* Free the good ones back to the mbuf pool thus discarding
	 * all the bad ones. */
	जबतक (good_mbuf_cnt) अणु
		good_mbuf_cnt--;

		val = good_mbuf[good_mbuf_cnt];
		val = (val << 9) | val | 1;

		bnx2_reg_wr_ind(bp, BNX2_RBUF_FW_BUF_FREE, val);
	पूर्ण
	kमुक्त(good_mbuf);
	वापस 0;
पूर्ण

अटल व्योम
bnx2_set_mac_addr(काष्ठा bnx2 *bp, u8 *mac_addr, u32 pos)
अणु
	u32 val;

	val = (mac_addr[0] << 8) | mac_addr[1];

	BNX2_WR(bp, BNX2_EMAC_MAC_MATCH0 + (pos * 8), val);

	val = (mac_addr[2] << 24) | (mac_addr[3] << 16) |
		(mac_addr[4] << 8) | mac_addr[5];

	BNX2_WR(bp, BNX2_EMAC_MAC_MATCH1 + (pos * 8), val);
पूर्ण

अटल अंतरभूत पूर्णांक
bnx2_alloc_rx_page(काष्ठा bnx2 *bp, काष्ठा bnx2_rx_ring_info *rxr, u16 index, gfp_t gfp)
अणु
	dma_addr_t mapping;
	काष्ठा bnx2_sw_pg *rx_pg = &rxr->rx_pg_ring[index];
	काष्ठा bnx2_rx_bd *rxbd =
		&rxr->rx_pg_desc_ring[BNX2_RX_RING(index)][BNX2_RX_IDX(index)];
	काष्ठा page *page = alloc_page(gfp);

	अगर (!page)
		वापस -ENOMEM;
	mapping = dma_map_page(&bp->pdev->dev, page, 0, PAGE_SIZE,
			       PCI_DMA_FROMDEVICE);
	अगर (dma_mapping_error(&bp->pdev->dev, mapping)) अणु
		__मुक्त_page(page);
		वापस -EIO;
	पूर्ण

	rx_pg->page = page;
	dma_unmap_addr_set(rx_pg, mapping, mapping);
	rxbd->rx_bd_haddr_hi = (u64) mapping >> 32;
	rxbd->rx_bd_haddr_lo = (u64) mapping & 0xffffffff;
	वापस 0;
पूर्ण

अटल व्योम
bnx2_मुक्त_rx_page(काष्ठा bnx2 *bp, काष्ठा bnx2_rx_ring_info *rxr, u16 index)
अणु
	काष्ठा bnx2_sw_pg *rx_pg = &rxr->rx_pg_ring[index];
	काष्ठा page *page = rx_pg->page;

	अगर (!page)
		वापस;

	dma_unmap_page(&bp->pdev->dev, dma_unmap_addr(rx_pg, mapping),
		       PAGE_SIZE, PCI_DMA_FROMDEVICE);

	__मुक्त_page(page);
	rx_pg->page = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
bnx2_alloc_rx_data(काष्ठा bnx2 *bp, काष्ठा bnx2_rx_ring_info *rxr, u16 index, gfp_t gfp)
अणु
	u8 *data;
	काष्ठा bnx2_sw_bd *rx_buf = &rxr->rx_buf_ring[index];
	dma_addr_t mapping;
	काष्ठा bnx2_rx_bd *rxbd =
		&rxr->rx_desc_ring[BNX2_RX_RING(index)][BNX2_RX_IDX(index)];

	data = kदो_स्मृति(bp->rx_buf_size, gfp);
	अगर (!data)
		वापस -ENOMEM;

	mapping = dma_map_single(&bp->pdev->dev,
				 get_l2_fhdr(data),
				 bp->rx_buf_use_size,
				 PCI_DMA_FROMDEVICE);
	अगर (dma_mapping_error(&bp->pdev->dev, mapping)) अणु
		kमुक्त(data);
		वापस -EIO;
	पूर्ण

	rx_buf->data = data;
	dma_unmap_addr_set(rx_buf, mapping, mapping);

	rxbd->rx_bd_haddr_hi = (u64) mapping >> 32;
	rxbd->rx_bd_haddr_lo = (u64) mapping & 0xffffffff;

	rxr->rx_prod_bseq += bp->rx_buf_use_size;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_phy_event_is_set(काष्ठा bnx2 *bp, काष्ठा bnx2_napi *bnapi, u32 event)
अणु
	काष्ठा status_block *sblk = bnapi->status_blk.msi;
	u32 new_link_state, old_link_state;
	पूर्णांक is_set = 1;

	new_link_state = sblk->status_attn_bits & event;
	old_link_state = sblk->status_attn_bits_ack & event;
	अगर (new_link_state != old_link_state) अणु
		अगर (new_link_state)
			BNX2_WR(bp, BNX2_PCICFG_STATUS_BIT_SET_CMD, event);
		अन्यथा
			BNX2_WR(bp, BNX2_PCICFG_STATUS_BIT_CLEAR_CMD, event);
	पूर्ण अन्यथा
		is_set = 0;

	वापस is_set;
पूर्ण

अटल व्योम
bnx2_phy_पूर्णांक(काष्ठा bnx2 *bp, काष्ठा bnx2_napi *bnapi)
अणु
	spin_lock(&bp->phy_lock);

	अगर (bnx2_phy_event_is_set(bp, bnapi, STATUS_ATTN_BITS_LINK_STATE))
		bnx2_set_link(bp);
	अगर (bnx2_phy_event_is_set(bp, bnapi, STATUS_ATTN_BITS_TIMER_ABORT))
		bnx2_set_remote_link(bp);

	spin_unlock(&bp->phy_lock);

पूर्ण

अटल अंतरभूत u16
bnx2_get_hw_tx_cons(काष्ठा bnx2_napi *bnapi)
अणु
	u16 cons;

	cons = READ_ONCE(*bnapi->hw_tx_cons_ptr);

	अगर (unlikely((cons & BNX2_MAX_TX_DESC_CNT) == BNX2_MAX_TX_DESC_CNT))
		cons++;
	वापस cons;
पूर्ण

अटल पूर्णांक
bnx2_tx_पूर्णांक(काष्ठा bnx2 *bp, काष्ठा bnx2_napi *bnapi, पूर्णांक budget)
अणु
	काष्ठा bnx2_tx_ring_info *txr = &bnapi->tx_ring;
	u16 hw_cons, sw_cons, sw_ring_cons;
	पूर्णांक tx_pkt = 0, index;
	अचिन्हित पूर्णांक tx_bytes = 0;
	काष्ठा netdev_queue *txq;

	index = (bnapi - bp->bnx2_napi);
	txq = netdev_get_tx_queue(bp->dev, index);

	hw_cons = bnx2_get_hw_tx_cons(bnapi);
	sw_cons = txr->tx_cons;

	जबतक (sw_cons != hw_cons) अणु
		काष्ठा bnx2_sw_tx_bd *tx_buf;
		काष्ठा sk_buff *skb;
		पूर्णांक i, last;

		sw_ring_cons = BNX2_TX_RING_IDX(sw_cons);

		tx_buf = &txr->tx_buf_ring[sw_ring_cons];
		skb = tx_buf->skb;

		/* prefetch skb_end_poपूर्णांकer() to speedup skb_shinfo(skb) */
		prefetch(&skb->end);

		/* partial BD completions possible with TSO packets */
		अगर (tx_buf->is_gso) अणु
			u16 last_idx, last_ring_idx;

			last_idx = sw_cons + tx_buf->nr_frags + 1;
			last_ring_idx = sw_ring_cons + tx_buf->nr_frags + 1;
			अगर (unlikely(last_ring_idx >= BNX2_MAX_TX_DESC_CNT)) अणु
				last_idx++;
			पूर्ण
			अगर (((s16) ((s16) last_idx - (s16) hw_cons)) > 0) अणु
				अवरोध;
			पूर्ण
		पूर्ण

		dma_unmap_single(&bp->pdev->dev, dma_unmap_addr(tx_buf, mapping),
			skb_headlen(skb), PCI_DMA_TODEVICE);

		tx_buf->skb = शून्य;
		last = tx_buf->nr_frags;

		क्रम (i = 0; i < last; i++) अणु
			काष्ठा bnx2_sw_tx_bd *tx_buf;

			sw_cons = BNX2_NEXT_TX_BD(sw_cons);

			tx_buf = &txr->tx_buf_ring[BNX2_TX_RING_IDX(sw_cons)];
			dma_unmap_page(&bp->pdev->dev,
				dma_unmap_addr(tx_buf, mapping),
				skb_frag_size(&skb_shinfo(skb)->frags[i]),
				PCI_DMA_TODEVICE);
		पूर्ण

		sw_cons = BNX2_NEXT_TX_BD(sw_cons);

		tx_bytes += skb->len;
		dev_kमुक्त_skb_any(skb);
		tx_pkt++;
		अगर (tx_pkt == budget)
			अवरोध;

		अगर (hw_cons == sw_cons)
			hw_cons = bnx2_get_hw_tx_cons(bnapi);
	पूर्ण

	netdev_tx_completed_queue(txq, tx_pkt, tx_bytes);
	txr->hw_tx_cons = hw_cons;
	txr->tx_cons = sw_cons;

	/* Need to make the tx_cons update visible to bnx2_start_xmit()
	 * beक्रमe checking क्रम netअगर_tx_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that bnx2_start_xmit()
	 * will miss it and cause the queue to be stopped क्रमever.
	 */
	smp_mb();

	अगर (unlikely(netअगर_tx_queue_stopped(txq)) &&
		     (bnx2_tx_avail(bp, txr) > bp->tx_wake_thresh)) अणु
		__netअगर_tx_lock(txq, smp_processor_id());
		अगर ((netअगर_tx_queue_stopped(txq)) &&
		    (bnx2_tx_avail(bp, txr) > bp->tx_wake_thresh))
			netअगर_tx_wake_queue(txq);
		__netअगर_tx_unlock(txq);
	पूर्ण

	वापस tx_pkt;
पूर्ण

अटल व्योम
bnx2_reuse_rx_skb_pages(काष्ठा bnx2 *bp, काष्ठा bnx2_rx_ring_info *rxr,
			काष्ठा sk_buff *skb, पूर्णांक count)
अणु
	काष्ठा bnx2_sw_pg *cons_rx_pg, *prod_rx_pg;
	काष्ठा bnx2_rx_bd *cons_bd, *prod_bd;
	पूर्णांक i;
	u16 hw_prod, prod;
	u16 cons = rxr->rx_pg_cons;

	cons_rx_pg = &rxr->rx_pg_ring[cons];

	/* The caller was unable to allocate a new page to replace the
	 * last one in the frags array, so we need to recycle that page
	 * and then मुक्त the skb.
	 */
	अगर (skb) अणु
		काष्ठा page *page;
		काष्ठा skb_shared_info *shinfo;

		shinfo = skb_shinfo(skb);
		shinfo->nr_frags--;
		page = skb_frag_page(&shinfo->frags[shinfo->nr_frags]);
		__skb_frag_set_page(&shinfo->frags[shinfo->nr_frags], शून्य);

		cons_rx_pg->page = page;
		dev_kमुक्त_skb(skb);
	पूर्ण

	hw_prod = rxr->rx_pg_prod;

	क्रम (i = 0; i < count; i++) अणु
		prod = BNX2_RX_PG_RING_IDX(hw_prod);

		prod_rx_pg = &rxr->rx_pg_ring[prod];
		cons_rx_pg = &rxr->rx_pg_ring[cons];
		cons_bd = &rxr->rx_pg_desc_ring[BNX2_RX_RING(cons)]
						[BNX2_RX_IDX(cons)];
		prod_bd = &rxr->rx_pg_desc_ring[BNX2_RX_RING(prod)]
						[BNX2_RX_IDX(prod)];

		अगर (prod != cons) अणु
			prod_rx_pg->page = cons_rx_pg->page;
			cons_rx_pg->page = शून्य;
			dma_unmap_addr_set(prod_rx_pg, mapping,
				dma_unmap_addr(cons_rx_pg, mapping));

			prod_bd->rx_bd_haddr_hi = cons_bd->rx_bd_haddr_hi;
			prod_bd->rx_bd_haddr_lo = cons_bd->rx_bd_haddr_lo;

		पूर्ण
		cons = BNX2_RX_PG_RING_IDX(BNX2_NEXT_RX_BD(cons));
		hw_prod = BNX2_NEXT_RX_BD(hw_prod);
	पूर्ण
	rxr->rx_pg_prod = hw_prod;
	rxr->rx_pg_cons = cons;
पूर्ण

अटल अंतरभूत व्योम
bnx2_reuse_rx_data(काष्ठा bnx2 *bp, काष्ठा bnx2_rx_ring_info *rxr,
		   u8 *data, u16 cons, u16 prod)
अणु
	काष्ठा bnx2_sw_bd *cons_rx_buf, *prod_rx_buf;
	काष्ठा bnx2_rx_bd *cons_bd, *prod_bd;

	cons_rx_buf = &rxr->rx_buf_ring[cons];
	prod_rx_buf = &rxr->rx_buf_ring[prod];

	dma_sync_single_क्रम_device(&bp->pdev->dev,
		dma_unmap_addr(cons_rx_buf, mapping),
		BNX2_RX_OFFSET + BNX2_RX_COPY_THRESH, PCI_DMA_FROMDEVICE);

	rxr->rx_prod_bseq += bp->rx_buf_use_size;

	prod_rx_buf->data = data;

	अगर (cons == prod)
		वापस;

	dma_unmap_addr_set(prod_rx_buf, mapping,
			dma_unmap_addr(cons_rx_buf, mapping));

	cons_bd = &rxr->rx_desc_ring[BNX2_RX_RING(cons)][BNX2_RX_IDX(cons)];
	prod_bd = &rxr->rx_desc_ring[BNX2_RX_RING(prod)][BNX2_RX_IDX(prod)];
	prod_bd->rx_bd_haddr_hi = cons_bd->rx_bd_haddr_hi;
	prod_bd->rx_bd_haddr_lo = cons_bd->rx_bd_haddr_lo;
पूर्ण

अटल काष्ठा sk_buff *
bnx2_rx_skb(काष्ठा bnx2 *bp, काष्ठा bnx2_rx_ring_info *rxr, u8 *data,
	    अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक hdr_len, dma_addr_t dma_addr,
	    u32 ring_idx)
अणु
	पूर्णांक err;
	u16 prod = ring_idx & 0xffff;
	काष्ठा sk_buff *skb;

	err = bnx2_alloc_rx_data(bp, rxr, prod, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		bnx2_reuse_rx_data(bp, rxr, data, (u16) (ring_idx >> 16), prod);
error:
		अगर (hdr_len) अणु
			अचिन्हित पूर्णांक raw_len = len + 4;
			पूर्णांक pages = PAGE_ALIGN(raw_len - hdr_len) >> PAGE_SHIFT;

			bnx2_reuse_rx_skb_pages(bp, rxr, शून्य, pages);
		पूर्ण
		वापस शून्य;
	पूर्ण

	dma_unmap_single(&bp->pdev->dev, dma_addr, bp->rx_buf_use_size,
			 PCI_DMA_FROMDEVICE);
	skb = build_skb(data, 0);
	अगर (!skb) अणु
		kमुक्त(data);
		जाओ error;
	पूर्ण
	skb_reserve(skb, ((u8 *)get_l2_fhdr(data) - data) + BNX2_RX_OFFSET);
	अगर (hdr_len == 0) अणु
		skb_put(skb, len);
		वापस skb;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i, frag_len, frag_size, pages;
		काष्ठा bnx2_sw_pg *rx_pg;
		u16 pg_cons = rxr->rx_pg_cons;
		u16 pg_prod = rxr->rx_pg_prod;

		frag_size = len + 4 - hdr_len;
		pages = PAGE_ALIGN(frag_size) >> PAGE_SHIFT;
		skb_put(skb, hdr_len);

		क्रम (i = 0; i < pages; i++) अणु
			dma_addr_t mapping_old;

			frag_len = min(frag_size, (अचिन्हित पूर्णांक) PAGE_SIZE);
			अगर (unlikely(frag_len <= 4)) अणु
				अचिन्हित पूर्णांक tail = 4 - frag_len;

				rxr->rx_pg_cons = pg_cons;
				rxr->rx_pg_prod = pg_prod;
				bnx2_reuse_rx_skb_pages(bp, rxr, शून्य,
							pages - i);
				skb->len -= tail;
				अगर (i == 0) अणु
					skb->tail -= tail;
				पूर्ण अन्यथा अणु
					skb_frag_t *frag =
						&skb_shinfo(skb)->frags[i - 1];
					skb_frag_size_sub(frag, tail);
					skb->data_len -= tail;
				पूर्ण
				वापस skb;
			पूर्ण
			rx_pg = &rxr->rx_pg_ring[pg_cons];

			/* Don't unmap yet.  If we're unable to allocate a new
			 * page, we need to recycle the page and the DMA addr.
			 */
			mapping_old = dma_unmap_addr(rx_pg, mapping);
			अगर (i == pages - 1)
				frag_len -= 4;

			skb_fill_page_desc(skb, i, rx_pg->page, 0, frag_len);
			rx_pg->page = शून्य;

			err = bnx2_alloc_rx_page(bp, rxr,
						 BNX2_RX_PG_RING_IDX(pg_prod),
						 GFP_ATOMIC);
			अगर (unlikely(err)) अणु
				rxr->rx_pg_cons = pg_cons;
				rxr->rx_pg_prod = pg_prod;
				bnx2_reuse_rx_skb_pages(bp, rxr, skb,
							pages - i);
				वापस शून्य;
			पूर्ण

			dma_unmap_page(&bp->pdev->dev, mapping_old,
				       PAGE_SIZE, PCI_DMA_FROMDEVICE);

			frag_size -= frag_len;
			skb->data_len += frag_len;
			skb->truesize += PAGE_SIZE;
			skb->len += frag_len;

			pg_prod = BNX2_NEXT_RX_BD(pg_prod);
			pg_cons = BNX2_RX_PG_RING_IDX(BNX2_NEXT_RX_BD(pg_cons));
		पूर्ण
		rxr->rx_pg_prod = pg_prod;
		rxr->rx_pg_cons = pg_cons;
	पूर्ण
	वापस skb;
पूर्ण

अटल अंतरभूत u16
bnx2_get_hw_rx_cons(काष्ठा bnx2_napi *bnapi)
अणु
	u16 cons;

	cons = READ_ONCE(*bnapi->hw_rx_cons_ptr);

	अगर (unlikely((cons & BNX2_MAX_RX_DESC_CNT) == BNX2_MAX_RX_DESC_CNT))
		cons++;
	वापस cons;
पूर्ण

अटल पूर्णांक
bnx2_rx_पूर्णांक(काष्ठा bnx2 *bp, काष्ठा bnx2_napi *bnapi, पूर्णांक budget)
अणु
	काष्ठा bnx2_rx_ring_info *rxr = &bnapi->rx_ring;
	u16 hw_cons, sw_cons, sw_ring_cons, sw_prod, sw_ring_prod;
	काष्ठा l2_fhdr *rx_hdr;
	पूर्णांक rx_pkt = 0, pg_ring_used = 0;

	अगर (budget <= 0)
		वापस rx_pkt;

	hw_cons = bnx2_get_hw_rx_cons(bnapi);
	sw_cons = rxr->rx_cons;
	sw_prod = rxr->rx_prod;

	/* Memory barrier necessary as speculative पढ़ोs of the rx
	 * buffer can be ahead of the index in the status block
	 */
	rmb();
	जबतक (sw_cons != hw_cons) अणु
		अचिन्हित पूर्णांक len, hdr_len;
		u32 status;
		काष्ठा bnx2_sw_bd *rx_buf, *next_rx_buf;
		काष्ठा sk_buff *skb;
		dma_addr_t dma_addr;
		u8 *data;
		u16 next_ring_idx;

		sw_ring_cons = BNX2_RX_RING_IDX(sw_cons);
		sw_ring_prod = BNX2_RX_RING_IDX(sw_prod);

		rx_buf = &rxr->rx_buf_ring[sw_ring_cons];
		data = rx_buf->data;
		rx_buf->data = शून्य;

		rx_hdr = get_l2_fhdr(data);
		prefetch(rx_hdr);

		dma_addr = dma_unmap_addr(rx_buf, mapping);

		dma_sync_single_क्रम_cpu(&bp->pdev->dev, dma_addr,
			BNX2_RX_OFFSET + BNX2_RX_COPY_THRESH,
			PCI_DMA_FROMDEVICE);

		next_ring_idx = BNX2_RX_RING_IDX(BNX2_NEXT_RX_BD(sw_cons));
		next_rx_buf = &rxr->rx_buf_ring[next_ring_idx];
		prefetch(get_l2_fhdr(next_rx_buf->data));

		len = rx_hdr->l2_fhdr_pkt_len;
		status = rx_hdr->l2_fhdr_status;

		hdr_len = 0;
		अगर (status & L2_FHDR_STATUS_SPLIT) अणु
			hdr_len = rx_hdr->l2_fhdr_ip_xsum;
			pg_ring_used = 1;
		पूर्ण अन्यथा अगर (len > bp->rx_jumbo_thresh) अणु
			hdr_len = bp->rx_jumbo_thresh;
			pg_ring_used = 1;
		पूर्ण

		अगर (unlikely(status & (L2_FHDR_ERRORS_BAD_CRC |
				       L2_FHDR_ERRORS_PHY_DECODE |
				       L2_FHDR_ERRORS_ALIGNMENT |
				       L2_FHDR_ERRORS_TOO_SHORT |
				       L2_FHDR_ERRORS_GIANT_FRAME))) अणु

			bnx2_reuse_rx_data(bp, rxr, data, sw_ring_cons,
					  sw_ring_prod);
			अगर (pg_ring_used) अणु
				पूर्णांक pages;

				pages = PAGE_ALIGN(len - hdr_len) >> PAGE_SHIFT;

				bnx2_reuse_rx_skb_pages(bp, rxr, शून्य, pages);
			पूर्ण
			जाओ next_rx;
		पूर्ण

		len -= 4;

		अगर (len <= bp->rx_copy_thresh) अणु
			skb = netdev_alloc_skb(bp->dev, len + 6);
			अगर (!skb) अणु
				bnx2_reuse_rx_data(bp, rxr, data, sw_ring_cons,
						  sw_ring_prod);
				जाओ next_rx;
			पूर्ण

			/* aligned copy */
			स_नकल(skb->data,
			       (u8 *)rx_hdr + BNX2_RX_OFFSET - 6,
			       len + 6);
			skb_reserve(skb, 6);
			skb_put(skb, len);

			bnx2_reuse_rx_data(bp, rxr, data,
				sw_ring_cons, sw_ring_prod);

		पूर्ण अन्यथा अणु
			skb = bnx2_rx_skb(bp, rxr, data, len, hdr_len, dma_addr,
					  (sw_ring_cons << 16) | sw_ring_prod);
			अगर (!skb)
				जाओ next_rx;
		पूर्ण
		अगर ((status & L2_FHDR_STATUS_L2_VLAN_TAG) &&
		    !(bp->rx_mode & BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rx_hdr->l2_fhdr_vlan_tag);

		skb->protocol = eth_type_trans(skb, bp->dev);

		अगर (len > (bp->dev->mtu + ETH_HLEN) &&
		    skb->protocol != htons(0x8100) &&
		    skb->protocol != htons(ETH_P_8021AD)) अणु

			dev_kमुक्त_skb(skb);
			जाओ next_rx;

		पूर्ण

		skb_checksum_none_निश्चित(skb);
		अगर ((bp->dev->features & NETIF_F_RXCSUM) &&
			(status & (L2_FHDR_STATUS_TCP_SEGMENT |
			L2_FHDR_STATUS_UDP_DATAGRAM))) अणु

			अगर (likely((status & (L2_FHDR_ERRORS_TCP_XSUM |
					      L2_FHDR_ERRORS_UDP_XSUM)) == 0))
				skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण
		अगर ((bp->dev->features & NETIF_F_RXHASH) &&
		    ((status & L2_FHDR_STATUS_USE_RXHASH) ==
		     L2_FHDR_STATUS_USE_RXHASH))
			skb_set_hash(skb, rx_hdr->l2_fhdr_hash,
				     PKT_HASH_TYPE_L3);

		skb_record_rx_queue(skb, bnapi - &bp->bnx2_napi[0]);
		napi_gro_receive(&bnapi->napi, skb);
		rx_pkt++;

next_rx:
		sw_cons = BNX2_NEXT_RX_BD(sw_cons);
		sw_prod = BNX2_NEXT_RX_BD(sw_prod);

		अगर (rx_pkt == budget)
			अवरोध;

		/* Refresh hw_cons to see अगर there is new work */
		अगर (sw_cons == hw_cons) अणु
			hw_cons = bnx2_get_hw_rx_cons(bnapi);
			rmb();
		पूर्ण
	पूर्ण
	rxr->rx_cons = sw_cons;
	rxr->rx_prod = sw_prod;

	अगर (pg_ring_used)
		BNX2_WR16(bp, rxr->rx_pg_bidx_addr, rxr->rx_pg_prod);

	BNX2_WR16(bp, rxr->rx_bidx_addr, sw_prod);

	BNX2_WR(bp, rxr->rx_bseq_addr, rxr->rx_prod_bseq);

	वापस rx_pkt;

पूर्ण

/* MSI ISR - The only dअगरference between this and the INTx ISR
 * is that the MSI पूर्णांकerrupt is always serviced.
 */
अटल irqवापस_t
bnx2_msi(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnx2_napi *bnapi = dev_instance;
	काष्ठा bnx2 *bp = bnapi->bp;

	prefetch(bnapi->status_blk.msi);
	BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD,
		BNX2_PCICFG_INT_ACK_CMD_USE_INT_HC_PARAM |
		BNX2_PCICFG_INT_ACK_CMD_MASK_INT);

	/* Return here अगर पूर्णांकerrupt is disabled. */
	अगर (unlikely(atomic_पढ़ो(&bp->पूर्णांकr_sem) != 0))
		वापस IRQ_HANDLED;

	napi_schedule(&bnapi->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
bnx2_msi_1shot(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnx2_napi *bnapi = dev_instance;
	काष्ठा bnx2 *bp = bnapi->bp;

	prefetch(bnapi->status_blk.msi);

	/* Return here अगर पूर्णांकerrupt is disabled. */
	अगर (unlikely(atomic_पढ़ो(&bp->पूर्णांकr_sem) != 0))
		वापस IRQ_HANDLED;

	napi_schedule(&bnapi->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
bnx2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnx2_napi *bnapi = dev_instance;
	काष्ठा bnx2 *bp = bnapi->bp;
	काष्ठा status_block *sblk = bnapi->status_blk.msi;

	/* When using INTx, it is possible क्रम the पूर्णांकerrupt to arrive
	 * at the CPU beक्रमe the status block posted prior to the
	 * पूर्णांकerrupt. Reading a रेजिस्टर will flush the status block.
	 * When using MSI, the MSI message will always complete after
	 * the status block ग_लिखो.
	 */
	अगर ((sblk->status_idx == bnapi->last_status_idx) &&
	    (BNX2_RD(bp, BNX2_PCICFG_MISC_STATUS) &
	     BNX2_PCICFG_MISC_STATUS_INTA_VALUE))
		वापस IRQ_NONE;

	BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD,
		BNX2_PCICFG_INT_ACK_CMD_USE_INT_HC_PARAM |
		BNX2_PCICFG_INT_ACK_CMD_MASK_INT);

	/* Read back to deनिश्चित IRQ immediately to aव्योम too many
	 * spurious पूर्णांकerrupts.
	 */
	BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD);

	/* Return here अगर पूर्णांकerrupt is shared and is disabled. */
	अगर (unlikely(atomic_पढ़ो(&bp->पूर्णांकr_sem) != 0))
		वापस IRQ_HANDLED;

	अगर (napi_schedule_prep(&bnapi->napi)) अणु
		bnapi->last_status_idx = sblk->status_idx;
		__napi_schedule(&bnapi->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत पूर्णांक
bnx2_has_fast_work(काष्ठा bnx2_napi *bnapi)
अणु
	काष्ठा bnx2_tx_ring_info *txr = &bnapi->tx_ring;
	काष्ठा bnx2_rx_ring_info *rxr = &bnapi->rx_ring;

	अगर ((bnx2_get_hw_rx_cons(bnapi) != rxr->rx_cons) ||
	    (bnx2_get_hw_tx_cons(bnapi) != txr->hw_tx_cons))
		वापस 1;
	वापस 0;
पूर्ण

#घोषणा STATUS_ATTN_EVENTS	(STATUS_ATTN_BITS_LINK_STATE | \
				 STATUS_ATTN_BITS_TIMER_ABORT)

अटल अंतरभूत पूर्णांक
bnx2_has_work(काष्ठा bnx2_napi *bnapi)
अणु
	काष्ठा status_block *sblk = bnapi->status_blk.msi;

	अगर (bnx2_has_fast_work(bnapi))
		वापस 1;

#अगर_घोषित BCM_CNIC
	अगर (bnapi->cnic_present && (bnapi->cnic_tag != sblk->status_idx))
		वापस 1;
#पूर्ण_अगर

	अगर ((sblk->status_attn_bits & STATUS_ATTN_EVENTS) !=
	    (sblk->status_attn_bits_ack & STATUS_ATTN_EVENTS))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम
bnx2_chk_missed_msi(काष्ठा bnx2 *bp)
अणु
	काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[0];
	u32 msi_ctrl;

	अगर (bnx2_has_work(bnapi)) अणु
		msi_ctrl = BNX2_RD(bp, BNX2_PCICFG_MSI_CONTROL);
		अगर (!(msi_ctrl & BNX2_PCICFG_MSI_CONTROL_ENABLE))
			वापस;

		अगर (bnapi->last_status_idx == bp->idle_chk_status_idx) अणु
			BNX2_WR(bp, BNX2_PCICFG_MSI_CONTROL, msi_ctrl &
				~BNX2_PCICFG_MSI_CONTROL_ENABLE);
			BNX2_WR(bp, BNX2_PCICFG_MSI_CONTROL, msi_ctrl);
			bnx2_msi(bp->irq_tbl[0].vector, bnapi);
		पूर्ण
	पूर्ण

	bp->idle_chk_status_idx = bnapi->last_status_idx;
पूर्ण

#अगर_घोषित BCM_CNIC
अटल व्योम bnx2_poll_cnic(काष्ठा bnx2 *bp, काष्ठा bnx2_napi *bnapi)
अणु
	काष्ठा cnic_ops *c_ops;

	अगर (!bnapi->cnic_present)
		वापस;

	rcu_पढ़ो_lock();
	c_ops = rcu_dereference(bp->cnic_ops);
	अगर (c_ops)
		bnapi->cnic_tag = c_ops->cnic_handler(bp->cnic_data,
						      bnapi->status_blk.msi);
	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर

अटल व्योम bnx2_poll_link(काष्ठा bnx2 *bp, काष्ठा bnx2_napi *bnapi)
अणु
	काष्ठा status_block *sblk = bnapi->status_blk.msi;
	u32 status_attn_bits = sblk->status_attn_bits;
	u32 status_attn_bits_ack = sblk->status_attn_bits_ack;

	अगर ((status_attn_bits & STATUS_ATTN_EVENTS) !=
	    (status_attn_bits_ack & STATUS_ATTN_EVENTS)) अणु

		bnx2_phy_पूर्णांक(bp, bnapi);

		/* This is needed to take care of transient status
		 * during link changes.
		 */
		BNX2_WR(bp, BNX2_HC_COMMAND,
			bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW_WO_INT);
		BNX2_RD(bp, BNX2_HC_COMMAND);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2_poll_work(काष्ठा bnx2 *bp, काष्ठा bnx2_napi *bnapi,
			  पूर्णांक work_करोne, पूर्णांक budget)
अणु
	काष्ठा bnx2_tx_ring_info *txr = &bnapi->tx_ring;
	काष्ठा bnx2_rx_ring_info *rxr = &bnapi->rx_ring;

	अगर (bnx2_get_hw_tx_cons(bnapi) != txr->hw_tx_cons)
		bnx2_tx_पूर्णांक(bp, bnapi, 0);

	अगर (bnx2_get_hw_rx_cons(bnapi) != rxr->rx_cons)
		work_करोne += bnx2_rx_पूर्णांक(bp, bnapi, budget - work_करोne);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक bnx2_poll_msix(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bnx2_napi *bnapi = container_of(napi, काष्ठा bnx2_napi, napi);
	काष्ठा bnx2 *bp = bnapi->bp;
	पूर्णांक work_करोne = 0;
	काष्ठा status_block_msix *sblk = bnapi->status_blk.msix;

	जबतक (1) अणु
		work_करोne = bnx2_poll_work(bp, bnapi, work_करोne, budget);
		अगर (unlikely(work_करोne >= budget))
			अवरोध;

		bnapi->last_status_idx = sblk->status_idx;
		/* status idx must be पढ़ो beक्रमe checking क्रम more work. */
		rmb();
		अगर (likely(!bnx2_has_fast_work(bnapi))) अणु

			napi_complete_करोne(napi, work_करोne);
			BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, bnapi->पूर्णांक_num |
				BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
				bnapi->last_status_idx);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल पूर्णांक bnx2_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bnx2_napi *bnapi = container_of(napi, काष्ठा bnx2_napi, napi);
	काष्ठा bnx2 *bp = bnapi->bp;
	पूर्णांक work_करोne = 0;
	काष्ठा status_block *sblk = bnapi->status_blk.msi;

	जबतक (1) अणु
		bnx2_poll_link(bp, bnapi);

		work_करोne = bnx2_poll_work(bp, bnapi, work_करोne, budget);

#अगर_घोषित BCM_CNIC
		bnx2_poll_cnic(bp, bnapi);
#पूर्ण_अगर

		/* bnapi->last_status_idx is used below to tell the hw how
		 * much work has been processed, so we must पढ़ो it beक्रमe
		 * checking क्रम more work.
		 */
		bnapi->last_status_idx = sblk->status_idx;

		अगर (unlikely(work_करोne >= budget))
			अवरोध;

		rmb();
		अगर (likely(!bnx2_has_work(bnapi))) अणु
			napi_complete_करोne(napi, work_करोne);
			अगर (likely(bp->flags & BNX2_FLAG_USING_MSI_OR_MSIX)) अणु
				BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD,
					BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
					bnapi->last_status_idx);
				अवरोध;
			पूर्ण
			BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD,
				BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
				BNX2_PCICFG_INT_ACK_CMD_MASK_INT |
				bnapi->last_status_idx);

			BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD,
				BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
				bnapi->last_status_idx);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

/* Called with rtnl_lock from vlan functions and also netअगर_tx_lock
 * from set_multicast.
 */
अटल व्योम
bnx2_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	u32 rx_mode, sort_mode;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

	अगर (!netअगर_running(dev))
		वापस;

	spin_lock_bh(&bp->phy_lock);

	rx_mode = bp->rx_mode & ~(BNX2_EMAC_RX_MODE_PROMISCUOUS |
				  BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG);
	sort_mode = 1 | BNX2_RPM_SORT_USER0_BC_EN;
	अगर (!(dev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	     (bp->flags & BNX2_FLAG_CAN_KEEP_VLAN))
		rx_mode |= BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG;
	अगर (dev->flags & IFF_PROMISC) अणु
		/* Promiscuous mode. */
		rx_mode |= BNX2_EMAC_RX_MODE_PROMISCUOUS;
		sort_mode |= BNX2_RPM_SORT_USER0_PROM_EN |
			     BNX2_RPM_SORT_USER0_PROM_VLAN;
	पूर्ण
	अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		क्रम (i = 0; i < NUM_MC_HASH_REGISTERS; i++) अणु
			BNX2_WR(bp, BNX2_EMAC_MULTICAST_HASH0 + (i * 4),
				0xffffffff);
        	पूर्ण
		sort_mode |= BNX2_RPM_SORT_USER0_MC_EN;
	पूर्ण
	अन्यथा अणु
		/* Accept one or more multicast(s). */
		u32 mc_filter[NUM_MC_HASH_REGISTERS];
		u32 regidx;
		u32 bit;
		u32 crc;

		स_रखो(mc_filter, 0, 4 * NUM_MC_HASH_REGISTERS);

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc_le(ETH_ALEN, ha->addr);
			bit = crc & 0xff;
			regidx = (bit & 0xe0) >> 5;
			bit &= 0x1f;
			mc_filter[regidx] |= (1 << bit);
		पूर्ण

		क्रम (i = 0; i < NUM_MC_HASH_REGISTERS; i++) अणु
			BNX2_WR(bp, BNX2_EMAC_MULTICAST_HASH0 + (i * 4),
				mc_filter[i]);
		पूर्ण

		sort_mode |= BNX2_RPM_SORT_USER0_MC_HSH_EN;
	पूर्ण

	अगर (netdev_uc_count(dev) > BNX2_MAX_UNICAST_ADDRESSES) अणु
		rx_mode |= BNX2_EMAC_RX_MODE_PROMISCUOUS;
		sort_mode |= BNX2_RPM_SORT_USER0_PROM_EN |
			     BNX2_RPM_SORT_USER0_PROM_VLAN;
	पूर्ण अन्यथा अगर (!(dev->flags & IFF_PROMISC)) अणु
		/* Add all entries पूर्णांकo to the match filter list */
		i = 0;
		netdev_क्रम_each_uc_addr(ha, dev) अणु
			bnx2_set_mac_addr(bp, ha->addr,
					  i + BNX2_START_UNICAST_ADDRESS_INDEX);
			sort_mode |= (1 <<
				      (i + BNX2_START_UNICAST_ADDRESS_INDEX));
			i++;
		पूर्ण

	पूर्ण

	अगर (rx_mode != bp->rx_mode) अणु
		bp->rx_mode = rx_mode;
		BNX2_WR(bp, BNX2_EMAC_RX_MODE, rx_mode);
	पूर्ण

	BNX2_WR(bp, BNX2_RPM_SORT_USER0, 0x0);
	BNX2_WR(bp, BNX2_RPM_SORT_USER0, sort_mode);
	BNX2_WR(bp, BNX2_RPM_SORT_USER0, sort_mode | BNX2_RPM_SORT_USER0_ENA);

	spin_unlock_bh(&bp->phy_lock);
पूर्ण

अटल पूर्णांक
check_fw_section(स्थिर काष्ठा firmware *fw,
		 स्थिर काष्ठा bnx2_fw_file_section *section,
		 u32 alignment, bool non_empty)
अणु
	u32 offset = be32_to_cpu(section->offset);
	u32 len = be32_to_cpu(section->len);

	अगर ((offset == 0 && len != 0) || offset >= fw->size || offset & 3)
		वापस -EINVAL;
	अगर ((non_empty && len == 0) || len > fw->size - offset ||
	    len & (alignment - 1))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक
check_mips_fw_entry(स्थिर काष्ठा firmware *fw,
		    स्थिर काष्ठा bnx2_mips_fw_file_entry *entry)
अणु
	अगर (check_fw_section(fw, &entry->text, 4, true) ||
	    check_fw_section(fw, &entry->data, 4, false) ||
	    check_fw_section(fw, &entry->rodata, 4, false))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम bnx2_release_firmware(काष्ठा bnx2 *bp)
अणु
	अगर (bp->rv2p_firmware) अणु
		release_firmware(bp->mips_firmware);
		release_firmware(bp->rv2p_firmware);
		bp->rv2p_firmware = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2_request_uncached_firmware(काष्ठा bnx2 *bp)
अणु
	स्थिर अक्षर *mips_fw_file, *rv2p_fw_file;
	स्थिर काष्ठा bnx2_mips_fw_file *mips_fw;
	स्थिर काष्ठा bnx2_rv2p_fw_file *rv2p_fw;
	पूर्णांक rc;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		mips_fw_file = FW_MIPS_खाता_09;
		अगर ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5709_A0) ||
		    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5709_A1))
			rv2p_fw_file = FW_RV2P_खाता_09_Ax;
		अन्यथा
			rv2p_fw_file = FW_RV2P_खाता_09;
	पूर्ण अन्यथा अणु
		mips_fw_file = FW_MIPS_खाता_06;
		rv2p_fw_file = FW_RV2P_खाता_06;
	पूर्ण

	rc = request_firmware(&bp->mips_firmware, mips_fw_file, &bp->pdev->dev);
	अगर (rc) अणु
		pr_err("Can't load firmware file \"%s\"\n", mips_fw_file);
		जाओ out;
	पूर्ण

	rc = request_firmware(&bp->rv2p_firmware, rv2p_fw_file, &bp->pdev->dev);
	अगर (rc) अणु
		pr_err("Can't load firmware file \"%s\"\n", rv2p_fw_file);
		जाओ err_release_mips_firmware;
	पूर्ण
	mips_fw = (स्थिर काष्ठा bnx2_mips_fw_file *) bp->mips_firmware->data;
	rv2p_fw = (स्थिर काष्ठा bnx2_rv2p_fw_file *) bp->rv2p_firmware->data;
	अगर (bp->mips_firmware->size < माप(*mips_fw) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->com) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->cp) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->rxp) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->tpat) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->txp)) अणु
		pr_err("Firmware file \"%s\" is invalid\n", mips_fw_file);
		rc = -EINVAL;
		जाओ err_release_firmware;
	पूर्ण
	अगर (bp->rv2p_firmware->size < माप(*rv2p_fw) ||
	    check_fw_section(bp->rv2p_firmware, &rv2p_fw->proc1.rv2p, 8, true) ||
	    check_fw_section(bp->rv2p_firmware, &rv2p_fw->proc2.rv2p, 8, true)) अणु
		pr_err("Firmware file \"%s\" is invalid\n", rv2p_fw_file);
		rc = -EINVAL;
		जाओ err_release_firmware;
	पूर्ण
out:
	वापस rc;

err_release_firmware:
	release_firmware(bp->rv2p_firmware);
	bp->rv2p_firmware = शून्य;
err_release_mips_firmware:
	release_firmware(bp->mips_firmware);
	जाओ out;
पूर्ण

अटल पूर्णांक bnx2_request_firmware(काष्ठा bnx2 *bp)
अणु
	वापस bp->rv2p_firmware ? 0 : bnx2_request_uncached_firmware(bp);
पूर्ण

अटल u32
rv2p_fw_fixup(u32 rv2p_proc, पूर्णांक idx, u32 loc, u32 rv2p_code)
अणु
	चयन (idx) अणु
	हाल RV2P_P1_FIXUP_PAGE_SIZE_IDX:
		rv2p_code &= ~RV2P_BD_PAGE_SIZE_MSK;
		rv2p_code |= RV2P_BD_PAGE_SIZE;
		अवरोध;
	पूर्ण
	वापस rv2p_code;
पूर्ण

अटल पूर्णांक
load_rv2p_fw(काष्ठा bnx2 *bp, u32 rv2p_proc,
	     स्थिर काष्ठा bnx2_rv2p_fw_file_entry *fw_entry)
अणु
	u32 rv2p_code_len, file_offset;
	__be32 *rv2p_code;
	पूर्णांक i;
	u32 val, cmd, addr;

	rv2p_code_len = be32_to_cpu(fw_entry->rv2p.len);
	file_offset = be32_to_cpu(fw_entry->rv2p.offset);

	rv2p_code = (__be32 *)(bp->rv2p_firmware->data + file_offset);

	अगर (rv2p_proc == RV2P_PROC1) अणु
		cmd = BNX2_RV2P_PROC1_ADDR_CMD_RDWR;
		addr = BNX2_RV2P_PROC1_ADDR_CMD;
	पूर्ण अन्यथा अणु
		cmd = BNX2_RV2P_PROC2_ADDR_CMD_RDWR;
		addr = BNX2_RV2P_PROC2_ADDR_CMD;
	पूर्ण

	क्रम (i = 0; i < rv2p_code_len; i += 8) अणु
		BNX2_WR(bp, BNX2_RV2P_INSTR_HIGH, be32_to_cpu(*rv2p_code));
		rv2p_code++;
		BNX2_WR(bp, BNX2_RV2P_INSTR_LOW, be32_to_cpu(*rv2p_code));
		rv2p_code++;

		val = (i / 8) | cmd;
		BNX2_WR(bp, addr, val);
	पूर्ण

	rv2p_code = (__be32 *)(bp->rv2p_firmware->data + file_offset);
	क्रम (i = 0; i < 8; i++) अणु
		u32 loc, code;

		loc = be32_to_cpu(fw_entry->fixup[i]);
		अगर (loc && ((loc * 4) < rv2p_code_len)) अणु
			code = be32_to_cpu(*(rv2p_code + loc - 1));
			BNX2_WR(bp, BNX2_RV2P_INSTR_HIGH, code);
			code = be32_to_cpu(*(rv2p_code + loc));
			code = rv2p_fw_fixup(rv2p_proc, i, loc, code);
			BNX2_WR(bp, BNX2_RV2P_INSTR_LOW, code);

			val = (loc / 2) | cmd;
			BNX2_WR(bp, addr, val);
		पूर्ण
	पूर्ण

	/* Reset the processor, un-stall is करोne later. */
	अगर (rv2p_proc == RV2P_PROC1) अणु
		BNX2_WR(bp, BNX2_RV2P_COMMAND, BNX2_RV2P_COMMAND_PROC1_RESET);
	पूर्ण
	अन्यथा अणु
		BNX2_WR(bp, BNX2_RV2P_COMMAND, BNX2_RV2P_COMMAND_PROC2_RESET);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
load_cpu_fw(काष्ठा bnx2 *bp, स्थिर काष्ठा cpu_reg *cpu_reg,
	    स्थिर काष्ठा bnx2_mips_fw_file_entry *fw_entry)
अणु
	u32 addr, len, file_offset;
	__be32 *data;
	u32 offset;
	u32 val;

	/* Halt the CPU. */
	val = bnx2_reg_rd_ind(bp, cpu_reg->mode);
	val |= cpu_reg->mode_value_halt;
	bnx2_reg_wr_ind(bp, cpu_reg->mode, val);
	bnx2_reg_wr_ind(bp, cpu_reg->state, cpu_reg->state_value_clear);

	/* Load the Text area. */
	addr = be32_to_cpu(fw_entry->text.addr);
	len = be32_to_cpu(fw_entry->text.len);
	file_offset = be32_to_cpu(fw_entry->text.offset);
	data = (__be32 *)(bp->mips_firmware->data + file_offset);

	offset = cpu_reg->spad_base + (addr - cpu_reg->mips_view_base);
	अगर (len) अणु
		पूर्णांक j;

		क्रम (j = 0; j < (len / 4); j++, offset += 4)
			bnx2_reg_wr_ind(bp, offset, be32_to_cpu(data[j]));
	पूर्ण

	/* Load the Data area. */
	addr = be32_to_cpu(fw_entry->data.addr);
	len = be32_to_cpu(fw_entry->data.len);
	file_offset = be32_to_cpu(fw_entry->data.offset);
	data = (__be32 *)(bp->mips_firmware->data + file_offset);

	offset = cpu_reg->spad_base + (addr - cpu_reg->mips_view_base);
	अगर (len) अणु
		पूर्णांक j;

		क्रम (j = 0; j < (len / 4); j++, offset += 4)
			bnx2_reg_wr_ind(bp, offset, be32_to_cpu(data[j]));
	पूर्ण

	/* Load the Read-Only area. */
	addr = be32_to_cpu(fw_entry->rodata.addr);
	len = be32_to_cpu(fw_entry->rodata.len);
	file_offset = be32_to_cpu(fw_entry->rodata.offset);
	data = (__be32 *)(bp->mips_firmware->data + file_offset);

	offset = cpu_reg->spad_base + (addr - cpu_reg->mips_view_base);
	अगर (len) अणु
		पूर्णांक j;

		क्रम (j = 0; j < (len / 4); j++, offset += 4)
			bnx2_reg_wr_ind(bp, offset, be32_to_cpu(data[j]));
	पूर्ण

	/* Clear the pre-fetch inकाष्ठाion. */
	bnx2_reg_wr_ind(bp, cpu_reg->inst, 0);

	val = be32_to_cpu(fw_entry->start_addr);
	bnx2_reg_wr_ind(bp, cpu_reg->pc, val);

	/* Start the CPU. */
	val = bnx2_reg_rd_ind(bp, cpu_reg->mode);
	val &= ~cpu_reg->mode_value_halt;
	bnx2_reg_wr_ind(bp, cpu_reg->state, cpu_reg->state_value_clear);
	bnx2_reg_wr_ind(bp, cpu_reg->mode, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_init_cpus(काष्ठा bnx2 *bp)
अणु
	स्थिर काष्ठा bnx2_mips_fw_file *mips_fw =
		(स्थिर काष्ठा bnx2_mips_fw_file *) bp->mips_firmware->data;
	स्थिर काष्ठा bnx2_rv2p_fw_file *rv2p_fw =
		(स्थिर काष्ठा bnx2_rv2p_fw_file *) bp->rv2p_firmware->data;
	पूर्णांक rc;

	/* Initialize the RV2P processor. */
	load_rv2p_fw(bp, RV2P_PROC1, &rv2p_fw->proc1);
	load_rv2p_fw(bp, RV2P_PROC2, &rv2p_fw->proc2);

	/* Initialize the RX Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_rxp, &mips_fw->rxp);
	अगर (rc)
		जाओ init_cpu_err;

	/* Initialize the TX Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_txp, &mips_fw->txp);
	अगर (rc)
		जाओ init_cpu_err;

	/* Initialize the TX Patch-up Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_tpat, &mips_fw->tpat);
	अगर (rc)
		जाओ init_cpu_err;

	/* Initialize the Completion Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_com, &mips_fw->com);
	अगर (rc)
		जाओ init_cpu_err;

	/* Initialize the Command Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_cp, &mips_fw->cp);

init_cpu_err:
	वापस rc;
पूर्ण

अटल व्योम
bnx2_setup_wol(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	u32 val, wol_msg;

	अगर (bp->wol) अणु
		u32 advertising;
		u8 स्वतःneg;

		स्वतःneg = bp->स्वतःneg;
		advertising = bp->advertising;

		अगर (bp->phy_port == PORT_TP) अणु
			bp->स्वतःneg = AUTONEG_SPEED;
			bp->advertising = ADVERTISED_10baseT_Half |
				ADVERTISED_10baseT_Full |
				ADVERTISED_100baseT_Half |
				ADVERTISED_100baseT_Full |
				ADVERTISED_Autoneg;
		पूर्ण

		spin_lock_bh(&bp->phy_lock);
		bnx2_setup_phy(bp, bp->phy_port);
		spin_unlock_bh(&bp->phy_lock);

		bp->स्वतःneg = स्वतःneg;
		bp->advertising = advertising;

		bnx2_set_mac_addr(bp, bp->dev->dev_addr, 0);

		val = BNX2_RD(bp, BNX2_EMAC_MODE);

		/* Enable port mode. */
		val &= ~BNX2_EMAC_MODE_PORT;
		val |= BNX2_EMAC_MODE_MPKT_RCVD |
		       BNX2_EMAC_MODE_ACPI_RCVD |
		       BNX2_EMAC_MODE_MPKT;
		अगर (bp->phy_port == PORT_TP) अणु
			val |= BNX2_EMAC_MODE_PORT_MII;
		पूर्ण अन्यथा अणु
			val |= BNX2_EMAC_MODE_PORT_GMII;
			अगर (bp->line_speed == SPEED_2500)
				val |= BNX2_EMAC_MODE_25G_MODE;
		पूर्ण

		BNX2_WR(bp, BNX2_EMAC_MODE, val);

		/* receive all multicast */
		क्रम (i = 0; i < NUM_MC_HASH_REGISTERS; i++) अणु
			BNX2_WR(bp, BNX2_EMAC_MULTICAST_HASH0 + (i * 4),
				0xffffffff);
		पूर्ण
		BNX2_WR(bp, BNX2_EMAC_RX_MODE, BNX2_EMAC_RX_MODE_SORT_MODE);

		val = 1 | BNX2_RPM_SORT_USER0_BC_EN | BNX2_RPM_SORT_USER0_MC_EN;
		BNX2_WR(bp, BNX2_RPM_SORT_USER0, 0x0);
		BNX2_WR(bp, BNX2_RPM_SORT_USER0, val);
		BNX2_WR(bp, BNX2_RPM_SORT_USER0, val | BNX2_RPM_SORT_USER0_ENA);

		/* Need to enable EMAC and RPM क्रम WOL. */
		BNX2_WR(bp, BNX2_MISC_ENABLE_SET_BITS,
			BNX2_MISC_ENABLE_SET_BITS_RX_PARSER_MAC_ENABLE |
			BNX2_MISC_ENABLE_SET_BITS_TX_HEADER_Q_ENABLE |
			BNX2_MISC_ENABLE_SET_BITS_EMAC_ENABLE);

		val = BNX2_RD(bp, BNX2_RPM_CONFIG);
		val &= ~BNX2_RPM_CONFIG_ACPI_ENA;
		BNX2_WR(bp, BNX2_RPM_CONFIG, val);

		wol_msg = BNX2_DRV_MSG_CODE_SUSPEND_WOL;
	पूर्ण अन्यथा अणु
			wol_msg = BNX2_DRV_MSG_CODE_SUSPEND_NO_WOL;
	पूर्ण

	अगर (!(bp->flags & BNX2_FLAG_NO_WOL)) अणु
		u32 val;

		wol_msg |= BNX2_DRV_MSG_DATA_WAIT3;
		अगर (bp->fw_last_msg || BNX2_CHIP(bp) != BNX2_CHIP_5709) अणु
			bnx2_fw_sync(bp, wol_msg, 1, 0);
			वापस;
		पूर्ण
		/* Tell firmware not to घातer करोwn the PHY yet, otherwise
		 * the chip will take a दीर्घ समय to respond to MMIO पढ़ोs.
		 */
		val = bnx2_shmem_rd(bp, BNX2_PORT_FEATURE);
		bnx2_shmem_wr(bp, BNX2_PORT_FEATURE,
			      val | BNX2_PORT_FEATURE_ASF_ENABLED);
		bnx2_fw_sync(bp, wol_msg, 1, 0);
		bnx2_shmem_wr(bp, BNX2_PORT_FEATURE, val);
	पूर्ण

पूर्ण

अटल पूर्णांक
bnx2_set_घातer_state(काष्ठा bnx2 *bp, pci_घातer_t state)
अणु
	चयन (state) अणु
	हाल PCI_D0: अणु
		u32 val;

		pci_enable_wake(bp->pdev, PCI_D0, false);
		pci_set_घातer_state(bp->pdev, PCI_D0);

		val = BNX2_RD(bp, BNX2_EMAC_MODE);
		val |= BNX2_EMAC_MODE_MPKT_RCVD | BNX2_EMAC_MODE_ACPI_RCVD;
		val &= ~BNX2_EMAC_MODE_MPKT;
		BNX2_WR(bp, BNX2_EMAC_MODE, val);

		val = BNX2_RD(bp, BNX2_RPM_CONFIG);
		val &= ~BNX2_RPM_CONFIG_ACPI_ENA;
		BNX2_WR(bp, BNX2_RPM_CONFIG, val);
		अवरोध;
	पूर्ण
	हाल PCI_D3hot: अणु
		bnx2_setup_wol(bp);
		pci_wake_from_d3(bp->pdev, bp->wol);
		अगर ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) ||
		    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1)) अणु

			अगर (bp->wol)
				pci_set_घातer_state(bp->pdev, PCI_D3hot);
			अवरोध;

		पूर्ण
		अगर (!bp->fw_last_msg && BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
			u32 val;

			/* Tell firmware not to घातer करोwn the PHY yet,
			 * otherwise the other port may not respond to
			 * MMIO पढ़ोs.
			 */
			val = bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION);
			val &= ~BNX2_CONDITION_PM_STATE_MASK;
			val |= BNX2_CONDITION_PM_STATE_UNPREP;
			bnx2_shmem_wr(bp, BNX2_BC_STATE_CONDITION, val);
		पूर्ण
		pci_set_घातer_state(bp->pdev, PCI_D3hot);

		/* No more memory access after this poपूर्णांक until
		 * device is brought back to D0.
		 */
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_acquire_nvram_lock(काष्ठा bnx2 *bp)
अणु
	u32 val;
	पूर्णांक j;

	/* Request access to the flash पूर्णांकerface. */
	BNX2_WR(bp, BNX2_NVM_SW_ARB, BNX2_NVM_SW_ARB_ARB_REQ_SET2);
	क्रम (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) अणु
		val = BNX2_RD(bp, BNX2_NVM_SW_ARB);
		अगर (val & BNX2_NVM_SW_ARB_ARB_ARB2)
			अवरोध;

		udelay(5);
	पूर्ण

	अगर (j >= NVRAM_TIMEOUT_COUNT)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_release_nvram_lock(काष्ठा bnx2 *bp)
अणु
	पूर्णांक j;
	u32 val;

	/* Relinquish nvram पूर्णांकerface. */
	BNX2_WR(bp, BNX2_NVM_SW_ARB, BNX2_NVM_SW_ARB_ARB_REQ_CLR2);

	क्रम (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) अणु
		val = BNX2_RD(bp, BNX2_NVM_SW_ARB);
		अगर (!(val & BNX2_NVM_SW_ARB_ARB_ARB2))
			अवरोध;

		udelay(5);
	पूर्ण

	अगर (j >= NVRAM_TIMEOUT_COUNT)
		वापस -EBUSY;

	वापस 0;
पूर्ण


अटल पूर्णांक
bnx2_enable_nvram_ग_लिखो(काष्ठा bnx2 *bp)
अणु
	u32 val;

	val = BNX2_RD(bp, BNX2_MISC_CFG);
	BNX2_WR(bp, BNX2_MISC_CFG, val | BNX2_MISC_CFG_NVM_WR_EN_PCI);

	अगर (bp->flash_info->flags & BNX2_NV_WREN) अणु
		पूर्णांक j;

		BNX2_WR(bp, BNX2_NVM_COMMAND, BNX2_NVM_COMMAND_DONE);
		BNX2_WR(bp, BNX2_NVM_COMMAND,
			BNX2_NVM_COMMAND_WREN | BNX2_NVM_COMMAND_DOIT);

		क्रम (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) अणु
			udelay(5);

			val = BNX2_RD(bp, BNX2_NVM_COMMAND);
			अगर (val & BNX2_NVM_COMMAND_DONE)
				अवरोध;
		पूर्ण

		अगर (j >= NVRAM_TIMEOUT_COUNT)
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
bnx2_disable_nvram_ग_लिखो(काष्ठा bnx2 *bp)
अणु
	u32 val;

	val = BNX2_RD(bp, BNX2_MISC_CFG);
	BNX2_WR(bp, BNX2_MISC_CFG, val & ~BNX2_MISC_CFG_NVM_WR_EN);
पूर्ण


अटल व्योम
bnx2_enable_nvram_access(काष्ठा bnx2 *bp)
अणु
	u32 val;

	val = BNX2_RD(bp, BNX2_NVM_ACCESS_ENABLE);
	/* Enable both bits, even on पढ़ो. */
	BNX2_WR(bp, BNX2_NVM_ACCESS_ENABLE,
		val | BNX2_NVM_ACCESS_ENABLE_EN | BNX2_NVM_ACCESS_ENABLE_WR_EN);
पूर्ण

अटल व्योम
bnx2_disable_nvram_access(काष्ठा bnx2 *bp)
अणु
	u32 val;

	val = BNX2_RD(bp, BNX2_NVM_ACCESS_ENABLE);
	/* Disable both bits, even after पढ़ो. */
	BNX2_WR(bp, BNX2_NVM_ACCESS_ENABLE,
		val & ~(BNX2_NVM_ACCESS_ENABLE_EN |
			BNX2_NVM_ACCESS_ENABLE_WR_EN));
पूर्ण

अटल पूर्णांक
bnx2_nvram_erase_page(काष्ठा bnx2 *bp, u32 offset)
अणु
	u32 cmd;
	पूर्णांक j;

	अगर (bp->flash_info->flags & BNX2_NV_BUFFERED)
		/* Buffered flash, no erase needed */
		वापस 0;

	/* Build an erase command */
	cmd = BNX2_NVM_COMMAND_ERASE | BNX2_NVM_COMMAND_WR |
	      BNX2_NVM_COMMAND_DOIT;

	/* Need to clear DONE bit separately. */
	BNX2_WR(bp, BNX2_NVM_COMMAND, BNX2_NVM_COMMAND_DONE);

	/* Address of the NVRAM to पढ़ो from. */
	BNX2_WR(bp, BNX2_NVM_ADDR, offset & BNX2_NVM_ADDR_NVM_ADDR_VALUE);

	/* Issue an erase command. */
	BNX2_WR(bp, BNX2_NVM_COMMAND, cmd);

	/* Wait क्रम completion. */
	क्रम (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) अणु
		u32 val;

		udelay(5);

		val = BNX2_RD(bp, BNX2_NVM_COMMAND);
		अगर (val & BNX2_NVM_COMMAND_DONE)
			अवरोध;
	पूर्ण

	अगर (j >= NVRAM_TIMEOUT_COUNT)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_nvram_पढ़ो_dword(काष्ठा bnx2 *bp, u32 offset, u8 *ret_val, u32 cmd_flags)
अणु
	u32 cmd;
	पूर्णांक j;

	/* Build the command word. */
	cmd = BNX2_NVM_COMMAND_DOIT | cmd_flags;

	/* Calculate an offset of a buffered flash, not needed क्रम 5709. */
	अगर (bp->flash_info->flags & BNX2_NV_TRANSLATE) अणु
		offset = ((offset / bp->flash_info->page_size) <<
			   bp->flash_info->page_bits) +
			  (offset % bp->flash_info->page_size);
	पूर्ण

	/* Need to clear DONE bit separately. */
	BNX2_WR(bp, BNX2_NVM_COMMAND, BNX2_NVM_COMMAND_DONE);

	/* Address of the NVRAM to पढ़ो from. */
	BNX2_WR(bp, BNX2_NVM_ADDR, offset & BNX2_NVM_ADDR_NVM_ADDR_VALUE);

	/* Issue a पढ़ो command. */
	BNX2_WR(bp, BNX2_NVM_COMMAND, cmd);

	/* Wait क्रम completion. */
	क्रम (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) अणु
		u32 val;

		udelay(5);

		val = BNX2_RD(bp, BNX2_NVM_COMMAND);
		अगर (val & BNX2_NVM_COMMAND_DONE) अणु
			__be32 v = cpu_to_be32(BNX2_RD(bp, BNX2_NVM_READ));
			स_नकल(ret_val, &v, 4);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (j >= NVRAM_TIMEOUT_COUNT)
		वापस -EBUSY;

	वापस 0;
पूर्ण


अटल पूर्णांक
bnx2_nvram_ग_लिखो_dword(काष्ठा bnx2 *bp, u32 offset, u8 *val, u32 cmd_flags)
अणु
	u32 cmd;
	__be32 val32;
	पूर्णांक j;

	/* Build the command word. */
	cmd = BNX2_NVM_COMMAND_DOIT | BNX2_NVM_COMMAND_WR | cmd_flags;

	/* Calculate an offset of a buffered flash, not needed क्रम 5709. */
	अगर (bp->flash_info->flags & BNX2_NV_TRANSLATE) अणु
		offset = ((offset / bp->flash_info->page_size) <<
			  bp->flash_info->page_bits) +
			 (offset % bp->flash_info->page_size);
	पूर्ण

	/* Need to clear DONE bit separately. */
	BNX2_WR(bp, BNX2_NVM_COMMAND, BNX2_NVM_COMMAND_DONE);

	स_नकल(&val32, val, 4);

	/* Write the data. */
	BNX2_WR(bp, BNX2_NVM_WRITE, be32_to_cpu(val32));

	/* Address of the NVRAM to ग_लिखो to. */
	BNX2_WR(bp, BNX2_NVM_ADDR, offset & BNX2_NVM_ADDR_NVM_ADDR_VALUE);

	/* Issue the ग_लिखो command. */
	BNX2_WR(bp, BNX2_NVM_COMMAND, cmd);

	/* Wait क्रम completion. */
	क्रम (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) अणु
		udelay(5);

		अगर (BNX2_RD(bp, BNX2_NVM_COMMAND) & BNX2_NVM_COMMAND_DONE)
			अवरोध;
	पूर्ण
	अगर (j >= NVRAM_TIMEOUT_COUNT)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_init_nvram(काष्ठा bnx2 *bp)
अणु
	u32 val;
	पूर्णांक j, entry_count, rc = 0;
	स्थिर काष्ठा flash_spec *flash;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		bp->flash_info = &flash_5709;
		जाओ get_flash_size;
	पूर्ण

	/* Determine the selected पूर्णांकerface. */
	val = BNX2_RD(bp, BNX2_NVM_CFG1);

	entry_count = ARRAY_SIZE(flash_table);

	अगर (val & 0x40000000) अणु

		/* Flash पूर्णांकerface has been reconfigured */
		क्रम (j = 0, flash = &flash_table[0]; j < entry_count;
		     j++, flash++) अणु
			अगर ((val & FLASH_BACKUP_STRAP_MASK) ==
			    (flash->config1 & FLASH_BACKUP_STRAP_MASK)) अणु
				bp->flash_info = flash;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अन्यथा अणु
		u32 mask;
		/* Not yet been reconfigured */

		अगर (val & (1 << 23))
			mask = FLASH_BACKUP_STRAP_MASK;
		अन्यथा
			mask = FLASH_STRAP_MASK;

		क्रम (j = 0, flash = &flash_table[0]; j < entry_count;
			j++, flash++) अणु

			अगर ((val & mask) == (flash->strapping & mask)) अणु
				bp->flash_info = flash;

				/* Request access to the flash पूर्णांकerface. */
				अगर ((rc = bnx2_acquire_nvram_lock(bp)) != 0)
					वापस rc;

				/* Enable access to flash पूर्णांकerface */
				bnx2_enable_nvram_access(bp);

				/* Reconfigure the flash पूर्णांकerface */
				BNX2_WR(bp, BNX2_NVM_CFG1, flash->config1);
				BNX2_WR(bp, BNX2_NVM_CFG2, flash->config2);
				BNX2_WR(bp, BNX2_NVM_CFG3, flash->config3);
				BNX2_WR(bp, BNX2_NVM_WRITE1, flash->ग_लिखो1);

				/* Disable access to flash पूर्णांकerface */
				bnx2_disable_nvram_access(bp);
				bnx2_release_nvram_lock(bp);

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण /* अगर (val & 0x40000000) */

	अगर (j == entry_count) अणु
		bp->flash_info = शून्य;
		pr_alert("Unknown flash/EEPROM type\n");
		वापस -ENODEV;
	पूर्ण

get_flash_size:
	val = bnx2_shmem_rd(bp, BNX2_SHARED_HW_CFG_CONFIG2);
	val &= BNX2_SHARED_HW_CFG2_NVM_SIZE_MASK;
	अगर (val)
		bp->flash_size = val;
	अन्यथा
		bp->flash_size = bp->flash_info->total_size;

	वापस rc;
पूर्ण

अटल पूर्णांक
bnx2_nvram_पढ़ो(काष्ठा bnx2 *bp, u32 offset, u8 *ret_buf,
		पूर्णांक buf_size)
अणु
	पूर्णांक rc = 0;
	u32 cmd_flags, offset32, len32, extra;

	अगर (buf_size == 0)
		वापस 0;

	/* Request access to the flash पूर्णांकerface. */
	अगर ((rc = bnx2_acquire_nvram_lock(bp)) != 0)
		वापस rc;

	/* Enable access to flash पूर्णांकerface */
	bnx2_enable_nvram_access(bp);

	len32 = buf_size;
	offset32 = offset;
	extra = 0;

	cmd_flags = 0;

	अगर (offset32 & 3) अणु
		u8 buf[4];
		u32 pre_len;

		offset32 &= ~3;
		pre_len = 4 - (offset & 3);

		अगर (pre_len >= len32) अणु
			pre_len = len32;
			cmd_flags = BNX2_NVM_COMMAND_FIRST |
				    BNX2_NVM_COMMAND_LAST;
		पूर्ण
		अन्यथा अणु
			cmd_flags = BNX2_NVM_COMMAND_FIRST;
		पूर्ण

		rc = bnx2_nvram_पढ़ो_dword(bp, offset32, buf, cmd_flags);

		अगर (rc)
			वापस rc;

		स_नकल(ret_buf, buf + (offset & 3), pre_len);

		offset32 += 4;
		ret_buf += pre_len;
		len32 -= pre_len;
	पूर्ण
	अगर (len32 & 3) अणु
		extra = 4 - (len32 & 3);
		len32 = (len32 + 4) & ~3;
	पूर्ण

	अगर (len32 == 4) अणु
		u8 buf[4];

		अगर (cmd_flags)
			cmd_flags = BNX2_NVM_COMMAND_LAST;
		अन्यथा
			cmd_flags = BNX2_NVM_COMMAND_FIRST |
				    BNX2_NVM_COMMAND_LAST;

		rc = bnx2_nvram_पढ़ो_dword(bp, offset32, buf, cmd_flags);

		स_नकल(ret_buf, buf, 4 - extra);
	पूर्ण
	अन्यथा अगर (len32 > 0) अणु
		u8 buf[4];

		/* Read the first word. */
		अगर (cmd_flags)
			cmd_flags = 0;
		अन्यथा
			cmd_flags = BNX2_NVM_COMMAND_FIRST;

		rc = bnx2_nvram_पढ़ो_dword(bp, offset32, ret_buf, cmd_flags);

		/* Advance to the next dword. */
		offset32 += 4;
		ret_buf += 4;
		len32 -= 4;

		जबतक (len32 > 4 && rc == 0) अणु
			rc = bnx2_nvram_पढ़ो_dword(bp, offset32, ret_buf, 0);

			/* Advance to the next dword. */
			offset32 += 4;
			ret_buf += 4;
			len32 -= 4;
		पूर्ण

		अगर (rc)
			वापस rc;

		cmd_flags = BNX2_NVM_COMMAND_LAST;
		rc = bnx2_nvram_पढ़ो_dword(bp, offset32, buf, cmd_flags);

		स_नकल(ret_buf, buf, 4 - extra);
	पूर्ण

	/* Disable access to flash पूर्णांकerface */
	bnx2_disable_nvram_access(bp);

	bnx2_release_nvram_lock(bp);

	वापस rc;
पूर्ण

अटल पूर्णांक
bnx2_nvram_ग_लिखो(काष्ठा bnx2 *bp, u32 offset, u8 *data_buf,
		पूर्णांक buf_size)
अणु
	u32 written, offset32, len32;
	u8 *buf, start[4], end[4], *align_buf = शून्य, *flash_buffer = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक align_start, align_end;

	buf = data_buf;
	offset32 = offset;
	len32 = buf_size;
	align_start = align_end = 0;

	अगर ((align_start = (offset32 & 3))) अणु
		offset32 &= ~3;
		len32 += align_start;
		अगर (len32 < 4)
			len32 = 4;
		अगर ((rc = bnx2_nvram_पढ़ो(bp, offset32, start, 4)))
			वापस rc;
	पूर्ण

	अगर (len32 & 3) अणु
		align_end = 4 - (len32 & 3);
		len32 += align_end;
		अगर ((rc = bnx2_nvram_पढ़ो(bp, offset32 + len32 - 4, end, 4)))
			वापस rc;
	पूर्ण

	अगर (align_start || align_end) अणु
		align_buf = kदो_स्मृति(len32, GFP_KERNEL);
		अगर (!align_buf)
			वापस -ENOMEM;
		अगर (align_start) अणु
			स_नकल(align_buf, start, 4);
		पूर्ण
		अगर (align_end) अणु
			स_नकल(align_buf + len32 - 4, end, 4);
		पूर्ण
		स_नकल(align_buf + align_start, data_buf, buf_size);
		buf = align_buf;
	पूर्ण

	अगर (!(bp->flash_info->flags & BNX2_NV_BUFFERED)) अणु
		flash_buffer = kदो_स्मृति(264, GFP_KERNEL);
		अगर (!flash_buffer) अणु
			rc = -ENOMEM;
			जाओ nvram_ग_लिखो_end;
		पूर्ण
	पूर्ण

	written = 0;
	जबतक ((written < len32) && (rc == 0)) अणु
		u32 page_start, page_end, data_start, data_end;
		u32 addr, cmd_flags;
		पूर्णांक i;

	        /* Find the page_start addr */
		page_start = offset32 + written;
		page_start -= (page_start % bp->flash_info->page_size);
		/* Find the page_end addr */
		page_end = page_start + bp->flash_info->page_size;
		/* Find the data_start addr */
		data_start = (written == 0) ? offset32 : page_start;
		/* Find the data_end addr */
		data_end = (page_end > offset32 + len32) ?
			(offset32 + len32) : page_end;

		/* Request access to the flash पूर्णांकerface. */
		अगर ((rc = bnx2_acquire_nvram_lock(bp)) != 0)
			जाओ nvram_ग_लिखो_end;

		/* Enable access to flash पूर्णांकerface */
		bnx2_enable_nvram_access(bp);

		cmd_flags = BNX2_NVM_COMMAND_FIRST;
		अगर (!(bp->flash_info->flags & BNX2_NV_BUFFERED)) अणु
			पूर्णांक j;

			/* Read the whole page पूर्णांकo the buffer
			 * (non-buffer flash only) */
			क्रम (j = 0; j < bp->flash_info->page_size; j += 4) अणु
				अगर (j == (bp->flash_info->page_size - 4)) अणु
					cmd_flags |= BNX2_NVM_COMMAND_LAST;
				पूर्ण
				rc = bnx2_nvram_पढ़ो_dword(bp,
					page_start + j,
					&flash_buffer[j],
					cmd_flags);

				अगर (rc)
					जाओ nvram_ग_लिखो_end;

				cmd_flags = 0;
			पूर्ण
		पूर्ण

		/* Enable ग_लिखोs to flash पूर्णांकerface (unlock ग_लिखो-protect) */
		अगर ((rc = bnx2_enable_nvram_ग_लिखो(bp)) != 0)
			जाओ nvram_ग_लिखो_end;

		/* Loop to ग_लिखो back the buffer data from page_start to
		 * data_start */
		i = 0;
		अगर (!(bp->flash_info->flags & BNX2_NV_BUFFERED)) अणु
			/* Erase the page */
			अगर ((rc = bnx2_nvram_erase_page(bp, page_start)) != 0)
				जाओ nvram_ग_लिखो_end;

			/* Re-enable the ग_लिखो again क्रम the actual ग_लिखो */
			bnx2_enable_nvram_ग_लिखो(bp);

			क्रम (addr = page_start; addr < data_start;
				addr += 4, i += 4) अणु

				rc = bnx2_nvram_ग_लिखो_dword(bp, addr,
					&flash_buffer[i], cmd_flags);

				अगर (rc != 0)
					जाओ nvram_ग_लिखो_end;

				cmd_flags = 0;
			पूर्ण
		पूर्ण

		/* Loop to ग_लिखो the new data from data_start to data_end */
		क्रम (addr = data_start; addr < data_end; addr += 4, i += 4) अणु
			अगर ((addr == page_end - 4) ||
				((bp->flash_info->flags & BNX2_NV_BUFFERED) &&
				 (addr == data_end - 4))) अणु

				cmd_flags |= BNX2_NVM_COMMAND_LAST;
			पूर्ण
			rc = bnx2_nvram_ग_लिखो_dword(bp, addr, buf,
				cmd_flags);

			अगर (rc != 0)
				जाओ nvram_ग_लिखो_end;

			cmd_flags = 0;
			buf += 4;
		पूर्ण

		/* Loop to ग_लिखो back the buffer data from data_end
		 * to page_end */
		अगर (!(bp->flash_info->flags & BNX2_NV_BUFFERED)) अणु
			क्रम (addr = data_end; addr < page_end;
				addr += 4, i += 4) अणु

				अगर (addr == page_end-4) अणु
					cmd_flags = BNX2_NVM_COMMAND_LAST;
                		पूर्ण
				rc = bnx2_nvram_ग_लिखो_dword(bp, addr,
					&flash_buffer[i], cmd_flags);

				अगर (rc != 0)
					जाओ nvram_ग_लिखो_end;

				cmd_flags = 0;
			पूर्ण
		पूर्ण

		/* Disable ग_लिखोs to flash पूर्णांकerface (lock ग_लिखो-protect) */
		bnx2_disable_nvram_ग_लिखो(bp);

		/* Disable access to flash पूर्णांकerface */
		bnx2_disable_nvram_access(bp);
		bnx2_release_nvram_lock(bp);

		/* Increment written */
		written += data_end - data_start;
	पूर्ण

nvram_ग_लिखो_end:
	kमुक्त(flash_buffer);
	kमुक्त(align_buf);
	वापस rc;
पूर्ण

अटल व्योम
bnx2_init_fw_cap(काष्ठा bnx2 *bp)
अणु
	u32 val, sig = 0;

	bp->phy_flags &= ~BNX2_PHY_FLAG_REMOTE_PHY_CAP;
	bp->flags &= ~BNX2_FLAG_CAN_KEEP_VLAN;

	अगर (!(bp->flags & BNX2_FLAG_ASF_ENABLE))
		bp->flags |= BNX2_FLAG_CAN_KEEP_VLAN;

	val = bnx2_shmem_rd(bp, BNX2_FW_CAP_MB);
	अगर ((val & BNX2_FW_CAP_SIGNATURE_MASK) != BNX2_FW_CAP_SIGNATURE)
		वापस;

	अगर ((val & BNX2_FW_CAP_CAN_KEEP_VLAN) == BNX2_FW_CAP_CAN_KEEP_VLAN) अणु
		bp->flags |= BNX2_FLAG_CAN_KEEP_VLAN;
		sig |= BNX2_DRV_ACK_CAP_SIGNATURE | BNX2_FW_CAP_CAN_KEEP_VLAN;
	पूर्ण

	अगर ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
	    (val & BNX2_FW_CAP_REMOTE_PHY_CAPABLE)) अणु
		u32 link;

		bp->phy_flags |= BNX2_PHY_FLAG_REMOTE_PHY_CAP;

		link = bnx2_shmem_rd(bp, BNX2_LINK_STATUS);
		अगर (link & BNX2_LINK_STATUS_SERDES_LINK)
			bp->phy_port = PORT_FIBRE;
		अन्यथा
			bp->phy_port = PORT_TP;

		sig |= BNX2_DRV_ACK_CAP_SIGNATURE |
		       BNX2_FW_CAP_REMOTE_PHY_CAPABLE;
	पूर्ण

	अगर (netअगर_running(bp->dev) && sig)
		bnx2_shmem_wr(bp, BNX2_DRV_ACK_CAP_MB, sig);
पूर्ण

अटल व्योम
bnx2_setup_msix_tbl(काष्ठा bnx2 *bp)
अणु
	BNX2_WR(bp, BNX2_PCI_GRC_WINDOW_ADDR, BNX2_PCI_GRC_WINDOW_ADDR_SEP_WIN);

	BNX2_WR(bp, BNX2_PCI_GRC_WINDOW2_ADDR, BNX2_MSIX_TABLE_ADDR);
	BNX2_WR(bp, BNX2_PCI_GRC_WINDOW3_ADDR, BNX2_MSIX_PBA_ADDR);
पूर्ण

अटल व्योम
bnx2_रुको_dma_complete(काष्ठा bnx2 *bp)
अणु
	u32 val;
	पूर्णांक i;

	/*
	 * Wait क्रम the current PCI transaction to complete beक्रमe
	 * issuing a reset.
	 */
	अगर ((BNX2_CHIP(bp) == BNX2_CHIP_5706) ||
	    (BNX2_CHIP(bp) == BNX2_CHIP_5708)) अणु
		BNX2_WR(bp, BNX2_MISC_ENABLE_CLR_BITS,
			BNX2_MISC_ENABLE_CLR_BITS_TX_DMA_ENABLE |
			BNX2_MISC_ENABLE_CLR_BITS_DMA_ENGINE_ENABLE |
			BNX2_MISC_ENABLE_CLR_BITS_RX_DMA_ENABLE |
			BNX2_MISC_ENABLE_CLR_BITS_HOST_COALESCE_ENABLE);
		val = BNX2_RD(bp, BNX2_MISC_ENABLE_CLR_BITS);
		udelay(5);
	पूर्ण अन्यथा अणु  /* 5709 */
		val = BNX2_RD(bp, BNX2_MISC_NEW_CORE_CTL);
		val &= ~BNX2_MISC_NEW_CORE_CTL_DMA_ENABLE;
		BNX2_WR(bp, BNX2_MISC_NEW_CORE_CTL, val);
		val = BNX2_RD(bp, BNX2_MISC_NEW_CORE_CTL);

		क्रम (i = 0; i < 100; i++) अणु
			msleep(1);
			val = BNX2_RD(bp, BNX2_PCICFG_DEVICE_CONTROL);
			अगर (!(val & BNX2_PCICFG_DEVICE_STATUS_NO_PEND))
				अवरोध;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण


अटल पूर्णांक
bnx2_reset_chip(काष्ठा bnx2 *bp, u32 reset_code)
अणु
	u32 val;
	पूर्णांक i, rc = 0;
	u8 old_port;

	/* Wait क्रम the current PCI transaction to complete beक्रमe
	 * issuing a reset. */
	bnx2_रुको_dma_complete(bp);

	/* Wait क्रम the firmware to tell us it is ok to issue a reset. */
	bnx2_fw_sync(bp, BNX2_DRV_MSG_DATA_WAIT0 | reset_code, 1, 1);

	/* Deposit a driver reset signature so the firmware knows that
	 * this is a soft reset. */
	bnx2_shmem_wr(bp, BNX2_DRV_RESET_SIGNATURE,
		      BNX2_DRV_RESET_SIGNATURE_MAGIC);

	/* Do a dummy पढ़ो to क्रमce the chip to complete all current transaction
	 * beक्रमe we issue a reset. */
	val = BNX2_RD(bp, BNX2_MISC_ID);

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		BNX2_WR(bp, BNX2_MISC_COMMAND, BNX2_MISC_COMMAND_SW_RESET);
		BNX2_RD(bp, BNX2_MISC_COMMAND);
		udelay(5);

		val = BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA |
		      BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP;

		BNX2_WR(bp, BNX2_PCICFG_MISC_CONFIG, val);

	पूर्ण अन्यथा अणु
		val = BNX2_PCICFG_MISC_CONFIG_CORE_RST_REQ |
		      BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA |
		      BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP;

		/* Chip reset. */
		BNX2_WR(bp, BNX2_PCICFG_MISC_CONFIG, val);

		/* Reading back any रेजिस्टर after chip reset will hang the
		 * bus on 5706 A0 and A1.  The msleep below provides plenty
		 * of margin क्रम ग_लिखो posting.
		 */
		अगर ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) ||
		    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1))
			msleep(20);

		/* Reset takes approximate 30 usec */
		क्रम (i = 0; i < 10; i++) अणु
			val = BNX2_RD(bp, BNX2_PCICFG_MISC_CONFIG);
			अगर ((val & (BNX2_PCICFG_MISC_CONFIG_CORE_RST_REQ |
				    BNX2_PCICFG_MISC_CONFIG_CORE_RST_BSY)) == 0)
				अवरोध;
			udelay(10);
		पूर्ण

		अगर (val & (BNX2_PCICFG_MISC_CONFIG_CORE_RST_REQ |
			   BNX2_PCICFG_MISC_CONFIG_CORE_RST_BSY)) अणु
			pr_err("Chip reset did not complete\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Make sure byte swapping is properly configured. */
	val = BNX2_RD(bp, BNX2_PCI_SWAP_DIAG0);
	अगर (val != 0x01020304) अणु
		pr_err("Chip not in correct endian mode\n");
		वापस -ENODEV;
	पूर्ण

	/* Wait क्रम the firmware to finish its initialization. */
	rc = bnx2_fw_sync(bp, BNX2_DRV_MSG_DATA_WAIT1 | reset_code, 1, 0);
	अगर (rc)
		वापस rc;

	spin_lock_bh(&bp->phy_lock);
	old_port = bp->phy_port;
	bnx2_init_fw_cap(bp);
	अगर ((bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) &&
	    old_port != bp->phy_port)
		bnx2_set_शेष_remote_link(bp);
	spin_unlock_bh(&bp->phy_lock);

	अगर (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) अणु
		/* Adjust the voltage regular to two steps lower.  The शेष
		 * of this रेजिस्टर is 0x0000000e. */
		BNX2_WR(bp, BNX2_MISC_VREG_CONTROL, 0x000000fa);

		/* Remove bad rbuf memory from the मुक्त pool. */
		rc = bnx2_alloc_bad_rbuf(bp);
	पूर्ण

	अगर (bp->flags & BNX2_FLAG_USING_MSIX) अणु
		bnx2_setup_msix_tbl(bp);
		/* Prevent MSIX table पढ़ोs and ग_लिखो from timing out */
		BNX2_WR(bp, BNX2_MISC_ECO_HW_CTL,
			BNX2_MISC_ECO_HW_CTL_LARGE_GRC_TMOUT_EN);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
bnx2_init_chip(काष्ठा bnx2 *bp)
अणु
	u32 val, mtu;
	पूर्णांक rc, i;

	/* Make sure the पूर्णांकerrupt is not active. */
	BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, BNX2_PCICFG_INT_ACK_CMD_MASK_INT);

	val = BNX2_DMA_CONFIG_DATA_BYTE_SWAP |
	      BNX2_DMA_CONFIG_DATA_WORD_SWAP |
#अगर_घोषित __BIG_ENDIAN
	      BNX2_DMA_CONFIG_CNTL_BYTE_SWAP |
#पूर्ण_अगर
	      BNX2_DMA_CONFIG_CNTL_WORD_SWAP |
	      DMA_READ_CHANS << 12 |
	      DMA_WRITE_CHANS << 16;

	val |= (0x2 << 20) | (1 << 11);

	अगर ((bp->flags & BNX2_FLAG_PCIX) && (bp->bus_speed_mhz == 133))
		val |= (1 << 23);

	अगर ((BNX2_CHIP(bp) == BNX2_CHIP_5706) &&
	    (BNX2_CHIP_ID(bp) != BNX2_CHIP_ID_5706_A0) &&
	    !(bp->flags & BNX2_FLAG_PCIX))
		val |= BNX2_DMA_CONFIG_CNTL_PING_PONG_DMA;

	BNX2_WR(bp, BNX2_DMA_CONFIG, val);

	अगर (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) अणु
		val = BNX2_RD(bp, BNX2_TDMA_CONFIG);
		val |= BNX2_TDMA_CONFIG_ONE_DMA;
		BNX2_WR(bp, BNX2_TDMA_CONFIG, val);
	पूर्ण

	अगर (bp->flags & BNX2_FLAG_PCIX) अणु
		u16 val16;

		pci_पढ़ो_config_word(bp->pdev, bp->pcix_cap + PCI_X_CMD,
				     &val16);
		pci_ग_लिखो_config_word(bp->pdev, bp->pcix_cap + PCI_X_CMD,
				      val16 & ~PCI_X_CMD_ERO);
	पूर्ण

	BNX2_WR(bp, BNX2_MISC_ENABLE_SET_BITS,
		BNX2_MISC_ENABLE_SET_BITS_HOST_COALESCE_ENABLE |
		BNX2_MISC_ENABLE_STATUS_BITS_RX_V2P_ENABLE |
		BNX2_MISC_ENABLE_STATUS_BITS_CONTEXT_ENABLE);

	/* Initialize context mapping and zero out the quick contexts.  The
	 * context block must have alपढ़ोy been enabled. */
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		rc = bnx2_init_5709_context(bp);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा
		bnx2_init_context(bp);

	अगर ((rc = bnx2_init_cpus(bp)) != 0)
		वापस rc;

	bnx2_init_nvram(bp);

	bnx2_set_mac_addr(bp, bp->dev->dev_addr, 0);

	val = BNX2_RD(bp, BNX2_MQ_CONFIG);
	val &= ~BNX2_MQ_CONFIG_KNL_BYP_BLK_SIZE;
	val |= BNX2_MQ_CONFIG_KNL_BYP_BLK_SIZE_256;
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		val |= BNX2_MQ_CONFIG_BIN_MQ_MODE;
		अगर (BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Ax)
			val |= BNX2_MQ_CONFIG_HALT_DIS;
	पूर्ण

	BNX2_WR(bp, BNX2_MQ_CONFIG, val);

	val = 0x10000 + (MAX_CID_CNT * MB_KERNEL_CTX_SIZE);
	BNX2_WR(bp, BNX2_MQ_KNL_BYP_WIND_START, val);
	BNX2_WR(bp, BNX2_MQ_KNL_WIND_END, val);

	val = (BNX2_PAGE_BITS - 8) << 24;
	BNX2_WR(bp, BNX2_RV2P_CONFIG, val);

	/* Configure page size. */
	val = BNX2_RD(bp, BNX2_TBDR_CONFIG);
	val &= ~BNX2_TBDR_CONFIG_PAGE_SIZE;
	val |= (BNX2_PAGE_BITS - 8) << 24 | 0x40;
	BNX2_WR(bp, BNX2_TBDR_CONFIG, val);

	val = bp->mac_addr[0] +
	      (bp->mac_addr[1] << 8) +
	      (bp->mac_addr[2] << 16) +
	      bp->mac_addr[3] +
	      (bp->mac_addr[4] << 8) +
	      (bp->mac_addr[5] << 16);
	BNX2_WR(bp, BNX2_EMAC_BACKOFF_SEED, val);

	/* Program the MTU.  Also include 4 bytes क्रम CRC32. */
	mtu = bp->dev->mtu;
	val = mtu + ETH_HLEN + ETH_FCS_LEN;
	अगर (val > (MAX_ETHERNET_PACKET_SIZE + ETH_HLEN + 4))
		val |= BNX2_EMAC_RX_MTU_SIZE_JUMBO_ENA;
	BNX2_WR(bp, BNX2_EMAC_RX_MTU_SIZE, val);

	अगर (mtu < ETH_DATA_LEN)
		mtu = ETH_DATA_LEN;

	bnx2_reg_wr_ind(bp, BNX2_RBUF_CONFIG, BNX2_RBUF_CONFIG_VAL(mtu));
	bnx2_reg_wr_ind(bp, BNX2_RBUF_CONFIG2, BNX2_RBUF_CONFIG2_VAL(mtu));
	bnx2_reg_wr_ind(bp, BNX2_RBUF_CONFIG3, BNX2_RBUF_CONFIG3_VAL(mtu));

	स_रखो(bp->bnx2_napi[0].status_blk.msi, 0, bp->status_stats_size);
	क्रम (i = 0; i < BNX2_MAX_MSIX_VEC; i++)
		bp->bnx2_napi[i].last_status_idx = 0;

	bp->idle_chk_status_idx = 0xffff;

	/* Set up how to generate a link change पूर्णांकerrupt. */
	BNX2_WR(bp, BNX2_EMAC_ATTENTION_ENA, BNX2_EMAC_ATTENTION_ENA_LINK);

	BNX2_WR(bp, BNX2_HC_STATUS_ADDR_L,
		(u64) bp->status_blk_mapping & 0xffffffff);
	BNX2_WR(bp, BNX2_HC_STATUS_ADDR_H, (u64) bp->status_blk_mapping >> 32);

	BNX2_WR(bp, BNX2_HC_STATISTICS_ADDR_L,
		(u64) bp->stats_blk_mapping & 0xffffffff);
	BNX2_WR(bp, BNX2_HC_STATISTICS_ADDR_H,
		(u64) bp->stats_blk_mapping >> 32);

	BNX2_WR(bp, BNX2_HC_TX_QUICK_CONS_TRIP,
		(bp->tx_quick_cons_trip_पूर्णांक << 16) | bp->tx_quick_cons_trip);

	BNX2_WR(bp, BNX2_HC_RX_QUICK_CONS_TRIP,
		(bp->rx_quick_cons_trip_पूर्णांक << 16) | bp->rx_quick_cons_trip);

	BNX2_WR(bp, BNX2_HC_COMP_PROD_TRIP,
		(bp->comp_prod_trip_पूर्णांक << 16) | bp->comp_prod_trip);

	BNX2_WR(bp, BNX2_HC_TX_TICKS, (bp->tx_ticks_पूर्णांक << 16) | bp->tx_ticks);

	BNX2_WR(bp, BNX2_HC_RX_TICKS, (bp->rx_ticks_पूर्णांक << 16) | bp->rx_ticks);

	BNX2_WR(bp, BNX2_HC_COM_TICKS,
		(bp->com_ticks_पूर्णांक << 16) | bp->com_ticks);

	BNX2_WR(bp, BNX2_HC_CMD_TICKS,
		(bp->cmd_ticks_पूर्णांक << 16) | bp->cmd_ticks);

	अगर (bp->flags & BNX2_FLAG_BROKEN_STATS)
		BNX2_WR(bp, BNX2_HC_STATS_TICKS, 0);
	अन्यथा
		BNX2_WR(bp, BNX2_HC_STATS_TICKS, bp->stats_ticks);
	BNX2_WR(bp, BNX2_HC_STAT_COLLECT_TICKS, 0xbb8);  /* 3ms */

	अगर (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1)
		val = BNX2_HC_CONFIG_COLLECT_STATS;
	अन्यथा अणु
		val = BNX2_HC_CONFIG_RX_TMR_MODE | BNX2_HC_CONFIG_TX_TMR_MODE |
		      BNX2_HC_CONFIG_COLLECT_STATS;
	पूर्ण

	अगर (bp->flags & BNX2_FLAG_USING_MSIX) अणु
		BNX2_WR(bp, BNX2_HC_MSIX_BIT_VECTOR,
			BNX2_HC_MSIX_BIT_VECTOR_VAL);

		val |= BNX2_HC_CONFIG_SB_ADDR_INC_128B;
	पूर्ण

	अगर (bp->flags & BNX2_FLAG_ONE_SHOT_MSI)
		val |= BNX2_HC_CONFIG_ONE_SHOT | BNX2_HC_CONFIG_USE_INT_PARAM;

	BNX2_WR(bp, BNX2_HC_CONFIG, val);

	अगर (bp->rx_ticks < 25)
		bnx2_reg_wr_ind(bp, BNX2_FW_RX_LOW_LATENCY, 1);
	अन्यथा
		bnx2_reg_wr_ind(bp, BNX2_FW_RX_LOW_LATENCY, 0);

	क्रम (i = 1; i < bp->irq_nvecs; i++) अणु
		u32 base = ((i - 1) * BNX2_HC_SB_CONFIG_SIZE) +
			   BNX2_HC_SB_CONFIG_1;

		BNX2_WR(bp, base,
			BNX2_HC_SB_CONFIG_1_TX_TMR_MODE |
			BNX2_HC_SB_CONFIG_1_RX_TMR_MODE |
			BNX2_HC_SB_CONFIG_1_ONE_SHOT);

		BNX2_WR(bp, base + BNX2_HC_TX_QUICK_CONS_TRIP_OFF,
			(bp->tx_quick_cons_trip_पूर्णांक << 16) |
			 bp->tx_quick_cons_trip);

		BNX2_WR(bp, base + BNX2_HC_TX_TICKS_OFF,
			(bp->tx_ticks_पूर्णांक << 16) | bp->tx_ticks);

		BNX2_WR(bp, base + BNX2_HC_RX_QUICK_CONS_TRIP_OFF,
			(bp->rx_quick_cons_trip_पूर्णांक << 16) |
			bp->rx_quick_cons_trip);

		BNX2_WR(bp, base + BNX2_HC_RX_TICKS_OFF,
			(bp->rx_ticks_पूर्णांक << 16) | bp->rx_ticks);
	पूर्ण

	/* Clear पूर्णांकernal stats counters. */
	BNX2_WR(bp, BNX2_HC_COMMAND, BNX2_HC_COMMAND_CLR_STAT_NOW);

	BNX2_WR(bp, BNX2_HC_ATTN_BITS_ENABLE, STATUS_ATTN_EVENTS);

	/* Initialize the receive filter. */
	bnx2_set_rx_mode(bp->dev);

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		val = BNX2_RD(bp, BNX2_MISC_NEW_CORE_CTL);
		val |= BNX2_MISC_NEW_CORE_CTL_DMA_ENABLE;
		BNX2_WR(bp, BNX2_MISC_NEW_CORE_CTL, val);
	पूर्ण
	rc = bnx2_fw_sync(bp, BNX2_DRV_MSG_DATA_WAIT2 | BNX2_DRV_MSG_CODE_RESET,
			  1, 0);

	BNX2_WR(bp, BNX2_MISC_ENABLE_SET_BITS, BNX2_MISC_ENABLE_DEFAULT);
	BNX2_RD(bp, BNX2_MISC_ENABLE_SET_BITS);

	udelay(20);

	bp->hc_cmd = BNX2_RD(bp, BNX2_HC_COMMAND);

	वापस rc;
पूर्ण

अटल व्योम
bnx2_clear_ring_states(काष्ठा bnx2 *bp)
अणु
	काष्ठा bnx2_napi *bnapi;
	काष्ठा bnx2_tx_ring_info *txr;
	काष्ठा bnx2_rx_ring_info *rxr;
	पूर्णांक i;

	क्रम (i = 0; i < BNX2_MAX_MSIX_VEC; i++) अणु
		bnapi = &bp->bnx2_napi[i];
		txr = &bnapi->tx_ring;
		rxr = &bnapi->rx_ring;

		txr->tx_cons = 0;
		txr->hw_tx_cons = 0;
		rxr->rx_prod_bseq = 0;
		rxr->rx_prod = 0;
		rxr->rx_cons = 0;
		rxr->rx_pg_prod = 0;
		rxr->rx_pg_cons = 0;
	पूर्ण
पूर्ण

अटल व्योम
bnx2_init_tx_context(काष्ठा bnx2 *bp, u32 cid, काष्ठा bnx2_tx_ring_info *txr)
अणु
	u32 val, offset0, offset1, offset2, offset3;
	u32 cid_addr = GET_CID_ADDR(cid);

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		offset0 = BNX2_L2CTX_TYPE_XI;
		offset1 = BNX2_L2CTX_CMD_TYPE_XI;
		offset2 = BNX2_L2CTX_TBDR_BHADDR_HI_XI;
		offset3 = BNX2_L2CTX_TBDR_BHADDR_LO_XI;
	पूर्ण अन्यथा अणु
		offset0 = BNX2_L2CTX_TYPE;
		offset1 = BNX2_L2CTX_CMD_TYPE;
		offset2 = BNX2_L2CTX_TBDR_BHADDR_HI;
		offset3 = BNX2_L2CTX_TBDR_BHADDR_LO;
	पूर्ण
	val = BNX2_L2CTX_TYPE_TYPE_L2 | BNX2_L2CTX_TYPE_SIZE_L2;
	bnx2_ctx_wr(bp, cid_addr, offset0, val);

	val = BNX2_L2CTX_CMD_TYPE_TYPE_L2 | (8 << 16);
	bnx2_ctx_wr(bp, cid_addr, offset1, val);

	val = (u64) txr->tx_desc_mapping >> 32;
	bnx2_ctx_wr(bp, cid_addr, offset2, val);

	val = (u64) txr->tx_desc_mapping & 0xffffffff;
	bnx2_ctx_wr(bp, cid_addr, offset3, val);
पूर्ण

अटल व्योम
bnx2_init_tx_ring(काष्ठा bnx2 *bp, पूर्णांक ring_num)
अणु
	काष्ठा bnx2_tx_bd *txbd;
	u32 cid = TX_CID;
	काष्ठा bnx2_napi *bnapi;
	काष्ठा bnx2_tx_ring_info *txr;

	bnapi = &bp->bnx2_napi[ring_num];
	txr = &bnapi->tx_ring;

	अगर (ring_num == 0)
		cid = TX_CID;
	अन्यथा
		cid = TX_TSS_CID + ring_num - 1;

	bp->tx_wake_thresh = bp->tx_ring_size / 2;

	txbd = &txr->tx_desc_ring[BNX2_MAX_TX_DESC_CNT];

	txbd->tx_bd_haddr_hi = (u64) txr->tx_desc_mapping >> 32;
	txbd->tx_bd_haddr_lo = (u64) txr->tx_desc_mapping & 0xffffffff;

	txr->tx_prod = 0;
	txr->tx_prod_bseq = 0;

	txr->tx_bidx_addr = MB_GET_CID_ADDR(cid) + BNX2_L2CTX_TX_HOST_BIDX;
	txr->tx_bseq_addr = MB_GET_CID_ADDR(cid) + BNX2_L2CTX_TX_HOST_BSEQ;

	bnx2_init_tx_context(bp, cid, txr);
पूर्ण

अटल व्योम
bnx2_init_rxbd_rings(काष्ठा bnx2_rx_bd *rx_ring[], dma_addr_t dma[],
		     u32 buf_size, पूर्णांक num_rings)
अणु
	पूर्णांक i;
	काष्ठा bnx2_rx_bd *rxbd;

	क्रम (i = 0; i < num_rings; i++) अणु
		पूर्णांक j;

		rxbd = &rx_ring[i][0];
		क्रम (j = 0; j < BNX2_MAX_RX_DESC_CNT; j++, rxbd++) अणु
			rxbd->rx_bd_len = buf_size;
			rxbd->rx_bd_flags = RX_BD_FLAGS_START | RX_BD_FLAGS_END;
		पूर्ण
		अगर (i == (num_rings - 1))
			j = 0;
		अन्यथा
			j = i + 1;
		rxbd->rx_bd_haddr_hi = (u64) dma[j] >> 32;
		rxbd->rx_bd_haddr_lo = (u64) dma[j] & 0xffffffff;
	पूर्ण
पूर्ण

अटल व्योम
bnx2_init_rx_ring(काष्ठा bnx2 *bp, पूर्णांक ring_num)
अणु
	पूर्णांक i;
	u16 prod, ring_prod;
	u32 cid, rx_cid_addr, val;
	काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[ring_num];
	काष्ठा bnx2_rx_ring_info *rxr = &bnapi->rx_ring;

	अगर (ring_num == 0)
		cid = RX_CID;
	अन्यथा
		cid = RX_RSS_CID + ring_num - 1;

	rx_cid_addr = GET_CID_ADDR(cid);

	bnx2_init_rxbd_rings(rxr->rx_desc_ring, rxr->rx_desc_mapping,
			     bp->rx_buf_use_size, bp->rx_max_ring);

	bnx2_init_rx_context(bp, cid);

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		val = BNX2_RD(bp, BNX2_MQ_MAP_L2_5);
		BNX2_WR(bp, BNX2_MQ_MAP_L2_5, val | BNX2_MQ_MAP_L2_5_ARM);
	पूर्ण

	bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_PG_BUF_SIZE, 0);
	अगर (bp->rx_pg_ring_size) अणु
		bnx2_init_rxbd_rings(rxr->rx_pg_desc_ring,
				     rxr->rx_pg_desc_mapping,
				     PAGE_SIZE, bp->rx_max_pg_ring);
		val = (bp->rx_buf_use_size << 16) | PAGE_SIZE;
		bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_PG_BUF_SIZE, val);
		bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_RBDC_KEY,
		       BNX2_L2CTX_RBDC_JUMBO_KEY - ring_num);

		val = (u64) rxr->rx_pg_desc_mapping[0] >> 32;
		bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_NX_PG_BDHADDR_HI, val);

		val = (u64) rxr->rx_pg_desc_mapping[0] & 0xffffffff;
		bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_NX_PG_BDHADDR_LO, val);

		अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
			BNX2_WR(bp, BNX2_MQ_MAP_L2_3, BNX2_MQ_MAP_L2_3_DEFAULT);
	पूर्ण

	val = (u64) rxr->rx_desc_mapping[0] >> 32;
	bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_NX_BDHADDR_HI, val);

	val = (u64) rxr->rx_desc_mapping[0] & 0xffffffff;
	bnx2_ctx_wr(bp, rx_cid_addr, BNX2_L2CTX_NX_BDHADDR_LO, val);

	ring_prod = prod = rxr->rx_pg_prod;
	क्रम (i = 0; i < bp->rx_pg_ring_size; i++) अणु
		अगर (bnx2_alloc_rx_page(bp, rxr, ring_prod, GFP_KERNEL) < 0) अणु
			netdev_warn(bp->dev, "init'ed rx page ring %d with %d/%d pages only\n",
				    ring_num, i, bp->rx_pg_ring_size);
			अवरोध;
		पूर्ण
		prod = BNX2_NEXT_RX_BD(prod);
		ring_prod = BNX2_RX_PG_RING_IDX(prod);
	पूर्ण
	rxr->rx_pg_prod = prod;

	ring_prod = prod = rxr->rx_prod;
	क्रम (i = 0; i < bp->rx_ring_size; i++) अणु
		अगर (bnx2_alloc_rx_data(bp, rxr, ring_prod, GFP_KERNEL) < 0) अणु
			netdev_warn(bp->dev, "init'ed rx ring %d with %d/%d skbs only\n",
				    ring_num, i, bp->rx_ring_size);
			अवरोध;
		पूर्ण
		prod = BNX2_NEXT_RX_BD(prod);
		ring_prod = BNX2_RX_RING_IDX(prod);
	पूर्ण
	rxr->rx_prod = prod;

	rxr->rx_bidx_addr = MB_GET_CID_ADDR(cid) + BNX2_L2CTX_HOST_BDIDX;
	rxr->rx_bseq_addr = MB_GET_CID_ADDR(cid) + BNX2_L2CTX_HOST_BSEQ;
	rxr->rx_pg_bidx_addr = MB_GET_CID_ADDR(cid) + BNX2_L2CTX_HOST_PG_BDIDX;

	BNX2_WR16(bp, rxr->rx_pg_bidx_addr, rxr->rx_pg_prod);
	BNX2_WR16(bp, rxr->rx_bidx_addr, prod);

	BNX2_WR(bp, rxr->rx_bseq_addr, rxr->rx_prod_bseq);
पूर्ण

अटल व्योम
bnx2_init_all_rings(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	u32 val;

	bnx2_clear_ring_states(bp);

	BNX2_WR(bp, BNX2_TSCH_TSS_CFG, 0);
	क्रम (i = 0; i < bp->num_tx_rings; i++)
		bnx2_init_tx_ring(bp, i);

	अगर (bp->num_tx_rings > 1)
		BNX2_WR(bp, BNX2_TSCH_TSS_CFG, ((bp->num_tx_rings - 1) << 24) |
			(TX_TSS_CID << 7));

	BNX2_WR(bp, BNX2_RLUP_RSS_CONFIG, 0);
	bnx2_reg_wr_ind(bp, BNX2_RXP_SCRATCH_RSS_TBL_SZ, 0);

	क्रम (i = 0; i < bp->num_rx_rings; i++)
		bnx2_init_rx_ring(bp, i);

	अगर (bp->num_rx_rings > 1) अणु
		u32 tbl_32 = 0;

		क्रम (i = 0; i < BNX2_RXP_SCRATCH_RSS_TBL_MAX_ENTRIES; i++) अणु
			पूर्णांक shअगरt = (i % 8) << 2;

			tbl_32 |= (i % (bp->num_rx_rings - 1)) << shअगरt;
			अगर ((i % 8) == 7) अणु
				BNX2_WR(bp, BNX2_RLUP_RSS_DATA, tbl_32);
				BNX2_WR(bp, BNX2_RLUP_RSS_COMMAND, (i >> 3) |
					BNX2_RLUP_RSS_COMMAND_RSS_WRITE_MASK |
					BNX2_RLUP_RSS_COMMAND_WRITE |
					BNX2_RLUP_RSS_COMMAND_HASH_MASK);
				tbl_32 = 0;
			पूर्ण
		पूर्ण

		val = BNX2_RLUP_RSS_CONFIG_IPV4_RSS_TYPE_ALL_XI |
		      BNX2_RLUP_RSS_CONFIG_IPV6_RSS_TYPE_ALL_XI;

		BNX2_WR(bp, BNX2_RLUP_RSS_CONFIG, val);

	पूर्ण
पूर्ण

अटल u32 bnx2_find_max_ring(u32 ring_size, u32 max_size)
अणु
	u32 max, num_rings = 1;

	जबतक (ring_size > BNX2_MAX_RX_DESC_CNT) अणु
		ring_size -= BNX2_MAX_RX_DESC_CNT;
		num_rings++;
	पूर्ण
	/* round to next घातer of 2 */
	max = max_size;
	जबतक ((max & num_rings) == 0)
		max >>= 1;

	अगर (num_rings != max)
		max <<= 1;

	वापस max;
पूर्ण

अटल व्योम
bnx2_set_rx_ring_size(काष्ठा bnx2 *bp, u32 size)
अणु
	u32 rx_size, rx_space, jumbo_size;

	/* 8 क्रम CRC and VLAN */
	rx_size = bp->dev->mtu + ETH_HLEN + BNX2_RX_OFFSET + 8;

	rx_space = SKB_DATA_ALIGN(rx_size + BNX2_RX_ALIGN) + NET_SKB_PAD +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	bp->rx_copy_thresh = BNX2_RX_COPY_THRESH;
	bp->rx_pg_ring_size = 0;
	bp->rx_max_pg_ring = 0;
	bp->rx_max_pg_ring_idx = 0;
	अगर ((rx_space > PAGE_SIZE) && !(bp->flags & BNX2_FLAG_JUMBO_BROKEN)) अणु
		पूर्णांक pages = PAGE_ALIGN(bp->dev->mtu - 40) >> PAGE_SHIFT;

		jumbo_size = size * pages;
		अगर (jumbo_size > BNX2_MAX_TOTAL_RX_PG_DESC_CNT)
			jumbo_size = BNX2_MAX_TOTAL_RX_PG_DESC_CNT;

		bp->rx_pg_ring_size = jumbo_size;
		bp->rx_max_pg_ring = bnx2_find_max_ring(jumbo_size,
							BNX2_MAX_RX_PG_RINGS);
		bp->rx_max_pg_ring_idx =
			(bp->rx_max_pg_ring * BNX2_RX_DESC_CNT) - 1;
		rx_size = BNX2_RX_COPY_THRESH + BNX2_RX_OFFSET;
		bp->rx_copy_thresh = 0;
	पूर्ण

	bp->rx_buf_use_size = rx_size;
	/* hw alignment + build_skb() overhead*/
	bp->rx_buf_size = SKB_DATA_ALIGN(bp->rx_buf_use_size + BNX2_RX_ALIGN) +
		NET_SKB_PAD + SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	bp->rx_jumbo_thresh = rx_size - BNX2_RX_OFFSET;
	bp->rx_ring_size = size;
	bp->rx_max_ring = bnx2_find_max_ring(size, BNX2_MAX_RX_RINGS);
	bp->rx_max_ring_idx = (bp->rx_max_ring * BNX2_RX_DESC_CNT) - 1;
पूर्ण

अटल व्योम
bnx2_मुक्त_tx_skbs(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->num_tx_rings; i++) अणु
		काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[i];
		काष्ठा bnx2_tx_ring_info *txr = &bnapi->tx_ring;
		पूर्णांक j;

		अगर (!txr->tx_buf_ring)
			जारी;

		क्रम (j = 0; j < BNX2_TX_DESC_CNT; ) अणु
			काष्ठा bnx2_sw_tx_bd *tx_buf = &txr->tx_buf_ring[j];
			काष्ठा sk_buff *skb = tx_buf->skb;
			पूर्णांक k, last;

			अगर (!skb) अणु
				j = BNX2_NEXT_TX_BD(j);
				जारी;
			पूर्ण

			dma_unmap_single(&bp->pdev->dev,
					 dma_unmap_addr(tx_buf, mapping),
					 skb_headlen(skb),
					 PCI_DMA_TODEVICE);

			tx_buf->skb = शून्य;

			last = tx_buf->nr_frags;
			j = BNX2_NEXT_TX_BD(j);
			क्रम (k = 0; k < last; k++, j = BNX2_NEXT_TX_BD(j)) अणु
				tx_buf = &txr->tx_buf_ring[BNX2_TX_RING_IDX(j)];
				dma_unmap_page(&bp->pdev->dev,
					dma_unmap_addr(tx_buf, mapping),
					skb_frag_size(&skb_shinfo(skb)->frags[k]),
					PCI_DMA_TODEVICE);
			पूर्ण
			dev_kमुक्त_skb(skb);
		पूर्ण
		netdev_tx_reset_queue(netdev_get_tx_queue(bp->dev, i));
	पूर्ण
पूर्ण

अटल व्योम
bnx2_मुक्त_rx_skbs(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->num_rx_rings; i++) अणु
		काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[i];
		काष्ठा bnx2_rx_ring_info *rxr = &bnapi->rx_ring;
		पूर्णांक j;

		अगर (!rxr->rx_buf_ring)
			वापस;

		क्रम (j = 0; j < bp->rx_max_ring_idx; j++) अणु
			काष्ठा bnx2_sw_bd *rx_buf = &rxr->rx_buf_ring[j];
			u8 *data = rx_buf->data;

			अगर (!data)
				जारी;

			dma_unmap_single(&bp->pdev->dev,
					 dma_unmap_addr(rx_buf, mapping),
					 bp->rx_buf_use_size,
					 PCI_DMA_FROMDEVICE);

			rx_buf->data = शून्य;

			kमुक्त(data);
		पूर्ण
		क्रम (j = 0; j < bp->rx_max_pg_ring_idx; j++)
			bnx2_मुक्त_rx_page(bp, rxr, j);
	पूर्ण
पूर्ण

अटल व्योम
bnx2_मुक्त_skbs(काष्ठा bnx2 *bp)
अणु
	bnx2_मुक्त_tx_skbs(bp);
	bnx2_मुक्त_rx_skbs(bp);
पूर्ण

अटल पूर्णांक
bnx2_reset_nic(काष्ठा bnx2 *bp, u32 reset_code)
अणु
	पूर्णांक rc;

	rc = bnx2_reset_chip(bp, reset_code);
	bnx2_मुक्त_skbs(bp);
	अगर (rc)
		वापस rc;

	अगर ((rc = bnx2_init_chip(bp)) != 0)
		वापस rc;

	bnx2_init_all_rings(bp);
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_init_nic(काष्ठा bnx2 *bp, पूर्णांक reset_phy)
अणु
	पूर्णांक rc;

	अगर ((rc = bnx2_reset_nic(bp, BNX2_DRV_MSG_CODE_RESET)) != 0)
		वापस rc;

	spin_lock_bh(&bp->phy_lock);
	bnx2_init_phy(bp, reset_phy);
	bnx2_set_link(bp);
	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		bnx2_remote_phy_event(bp);
	spin_unlock_bh(&bp->phy_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_shutकरोwn_chip(काष्ठा bnx2 *bp)
अणु
	u32 reset_code;

	अगर (bp->flags & BNX2_FLAG_NO_WOL)
		reset_code = BNX2_DRV_MSG_CODE_UNLOAD_LNK_DN;
	अन्यथा अगर (bp->wol)
		reset_code = BNX2_DRV_MSG_CODE_SUSPEND_WOL;
	अन्यथा
		reset_code = BNX2_DRV_MSG_CODE_SUSPEND_NO_WOL;

	वापस bnx2_reset_chip(bp, reset_code);
पूर्ण

अटल पूर्णांक
bnx2_test_रेजिस्टरs(काष्ठा bnx2 *bp)
अणु
	पूर्णांक ret;
	पूर्णांक i, is_5709;
	अटल स्थिर काष्ठा अणु
		u16   offset;
		u16   flags;
#घोषणा BNX2_FL_NOT_5709	1
		u32   rw_mask;
		u32   ro_mask;
	पूर्ण reg_tbl[] = अणु
		अणु 0x006c, 0, 0x00000000, 0x0000003f पूर्ण,
		अणु 0x0090, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x0094, 0, 0x00000000, 0x00000000 पूर्ण,

		अणु 0x0404, BNX2_FL_NOT_5709, 0x00003f00, 0x00000000 पूर्ण,
		अणु 0x0418, BNX2_FL_NOT_5709, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x041c, BNX2_FL_NOT_5709, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x0420, BNX2_FL_NOT_5709, 0x00000000, 0x80ffffff पूर्ण,
		अणु 0x0424, BNX2_FL_NOT_5709, 0x00000000, 0x00000000 पूर्ण,
		अणु 0x0428, BNX2_FL_NOT_5709, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x0450, BNX2_FL_NOT_5709, 0x00000000, 0x0000ffff पूर्ण,
		अणु 0x0454, BNX2_FL_NOT_5709, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x0458, BNX2_FL_NOT_5709, 0x00000000, 0xffffffff पूर्ण,

		अणु 0x0808, BNX2_FL_NOT_5709, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x0854, BNX2_FL_NOT_5709, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x0868, BNX2_FL_NOT_5709, 0x00000000, 0x77777777 पूर्ण,
		अणु 0x086c, BNX2_FL_NOT_5709, 0x00000000, 0x77777777 पूर्ण,
		अणु 0x0870, BNX2_FL_NOT_5709, 0x00000000, 0x77777777 पूर्ण,
		अणु 0x0874, BNX2_FL_NOT_5709, 0x00000000, 0x77777777 पूर्ण,

		अणु 0x0c00, BNX2_FL_NOT_5709, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x0c04, BNX2_FL_NOT_5709, 0x00000000, 0x03ff0001 पूर्ण,
		अणु 0x0c08, BNX2_FL_NOT_5709,  0x0f0ff073, 0x00000000 पूर्ण,

		अणु 0x1000, 0, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x1004, BNX2_FL_NOT_5709, 0x00000000, 0x000f0001 पूर्ण,

		अणु 0x1408, 0, 0x01c00800, 0x00000000 पूर्ण,
		अणु 0x149c, 0, 0x8000ffff, 0x00000000 पूर्ण,
		अणु 0x14a8, 0, 0x00000000, 0x000001ff पूर्ण,
		अणु 0x14ac, 0, 0x0fffffff, 0x10000000 पूर्ण,
		अणु 0x14b0, 0, 0x00000002, 0x00000001 पूर्ण,
		अणु 0x14b8, 0, 0x00000000, 0x00000000 पूर्ण,
		अणु 0x14c0, 0, 0x00000000, 0x00000009 पूर्ण,
		अणु 0x14c4, 0, 0x00003fff, 0x00000000 पूर्ण,
		अणु 0x14cc, 0, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x14d0, 0, 0xffffffff, 0x00000000 पूर्ण,

		अणु 0x1800, 0, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x1804, 0, 0x00000000, 0x00000003 पूर्ण,

		अणु 0x2800, 0, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x2804, 0, 0x00000000, 0x00003f01 पूर्ण,
		अणु 0x2808, 0, 0x0f3f3f03, 0x00000000 पूर्ण,
		अणु 0x2810, 0, 0xffff0000, 0x00000000 पूर्ण,
		अणु 0x2814, 0, 0xffff0000, 0x00000000 पूर्ण,
		अणु 0x2818, 0, 0xffff0000, 0x00000000 पूर्ण,
		अणु 0x281c, 0, 0xffff0000, 0x00000000 पूर्ण,
		अणु 0x2834, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x2840, 0, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x2844, 0, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x2848, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x284c, 0, 0xf800f800, 0x07ff07ff पूर्ण,

		अणु 0x2c00, 0, 0x00000000, 0x00000011 पूर्ण,
		अणु 0x2c04, 0, 0x00000000, 0x00030007 पूर्ण,

		अणु 0x3c00, 0, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x3c04, 0, 0x00000000, 0x00070000 पूर्ण,
		अणु 0x3c08, 0, 0x00007f71, 0x07f00000 पूर्ण,
		अणु 0x3c0c, 0, 0x1f3ffffc, 0x00000000 पूर्ण,
		अणु 0x3c10, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x3c14, 0, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x3c18, 0, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x3c1c, 0, 0xfffff000, 0x00000000 पूर्ण,
		अणु 0x3c20, 0, 0xffffff00, 0x00000000 पूर्ण,

		अणु 0x5004, 0, 0x00000000, 0x0000007f पूर्ण,
		अणु 0x5008, 0, 0x0f0007ff, 0x00000000 पूर्ण,

		अणु 0x5c00, 0, 0x00000000, 0x00000001 पूर्ण,
		अणु 0x5c04, 0, 0x00000000, 0x0003000f पूर्ण,
		अणु 0x5c08, 0, 0x00000003, 0x00000000 पूर्ण,
		अणु 0x5c0c, 0, 0x0000fff8, 0x00000000 पूर्ण,
		अणु 0x5c10, 0, 0x00000000, 0xffffffff पूर्ण,
		अणु 0x5c80, 0, 0x00000000, 0x0f7113f1 पूर्ण,
		अणु 0x5c84, 0, 0x00000000, 0x0000f333 पूर्ण,
		अणु 0x5c88, 0, 0x00000000, 0x00077373 पूर्ण,
		अणु 0x5c8c, 0, 0x00000000, 0x0007f737 पूर्ण,

		अणु 0x6808, 0, 0x0000ff7f, 0x00000000 पूर्ण,
		अणु 0x680c, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x6810, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x6814, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x6818, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x681c, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x6820, 0, 0x00ff00ff, 0x00000000 पूर्ण,
		अणु 0x6824, 0, 0x00ff00ff, 0x00000000 पूर्ण,
		अणु 0x6828, 0, 0x00ff00ff, 0x00000000 पूर्ण,
		अणु 0x682c, 0, 0x03ff03ff, 0x00000000 पूर्ण,
		अणु 0x6830, 0, 0x03ff03ff, 0x00000000 पूर्ण,
		अणु 0x6834, 0, 0x03ff03ff, 0x00000000 पूर्ण,
		अणु 0x6838, 0, 0x03ff03ff, 0x00000000 पूर्ण,
		अणु 0x683c, 0, 0x0000ffff, 0x00000000 पूर्ण,
		अणु 0x6840, 0, 0x00000ff0, 0x00000000 पूर्ण,
		अणु 0x6844, 0, 0x00ffff00, 0x00000000 पूर्ण,
		अणु 0x684c, 0, 0xffffffff, 0x00000000 पूर्ण,
		अणु 0x6850, 0, 0x7f7f7f7f, 0x00000000 पूर्ण,
		अणु 0x6854, 0, 0x7f7f7f7f, 0x00000000 पूर्ण,
		अणु 0x6858, 0, 0x7f7f7f7f, 0x00000000 पूर्ण,
		अणु 0x685c, 0, 0x7f7f7f7f, 0x00000000 पूर्ण,
		अणु 0x6908, 0, 0x00000000, 0x0001ff0f पूर्ण,
		अणु 0x690c, 0, 0x00000000, 0x0ffe00f0 पूर्ण,

		अणु 0xffff, 0, 0x00000000, 0x00000000 पूर्ण,
	पूर्ण;

	ret = 0;
	is_5709 = 0;
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		is_5709 = 1;

	क्रम (i = 0; reg_tbl[i].offset != 0xffff; i++) अणु
		u32 offset, rw_mask, ro_mask, save_val, val;
		u16 flags = reg_tbl[i].flags;

		अगर (is_5709 && (flags & BNX2_FL_NOT_5709))
			जारी;

		offset = (u32) reg_tbl[i].offset;
		rw_mask = reg_tbl[i].rw_mask;
		ro_mask = reg_tbl[i].ro_mask;

		save_val = पढ़ोl(bp->regview + offset);

		ग_लिखोl(0, bp->regview + offset);

		val = पढ़ोl(bp->regview + offset);
		अगर ((val & rw_mask) != 0) अणु
			जाओ reg_test_err;
		पूर्ण

		अगर ((val & ro_mask) != (save_val & ro_mask)) अणु
			जाओ reg_test_err;
		पूर्ण

		ग_लिखोl(0xffffffff, bp->regview + offset);

		val = पढ़ोl(bp->regview + offset);
		अगर ((val & rw_mask) != rw_mask) अणु
			जाओ reg_test_err;
		पूर्ण

		अगर ((val & ro_mask) != (save_val & ro_mask)) अणु
			जाओ reg_test_err;
		पूर्ण

		ग_लिखोl(save_val, bp->regview + offset);
		जारी;

reg_test_err:
		ग_लिखोl(save_val, bp->regview + offset);
		ret = -ENODEV;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
bnx2_करो_mem_test(काष्ठा bnx2 *bp, u32 start, u32 size)
अणु
	अटल स्थिर u32 test_pattern[] = अणु 0x00000000, 0xffffffff, 0x55555555,
		0xaaaaaaaa , 0xaa55aa55, 0x55aa55aa पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < माप(test_pattern) / 4; i++) अणु
		u32 offset;

		क्रम (offset = 0; offset < size; offset += 4) अणु

			bnx2_reg_wr_ind(bp, start + offset, test_pattern[i]);

			अगर (bnx2_reg_rd_ind(bp, start + offset) !=
				test_pattern[i]) अणु
				वापस -ENODEV;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_test_memory(काष्ठा bnx2 *bp)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	अटल काष्ठा mem_entry अणु
		u32   offset;
		u32   len;
	पूर्ण mem_tbl_5706[] = अणु
		अणु 0x60000,  0x4000 पूर्ण,
		अणु 0xa0000,  0x3000 पूर्ण,
		अणु 0xe0000,  0x4000 पूर्ण,
		अणु 0x120000, 0x4000 पूर्ण,
		अणु 0x1a0000, 0x4000 पूर्ण,
		अणु 0x160000, 0x4000 पूर्ण,
		अणु 0xffffffff, 0    पूर्ण,
	पूर्ण,
	mem_tbl_5709[] = अणु
		अणु 0x60000,  0x4000 पूर्ण,
		अणु 0xa0000,  0x3000 पूर्ण,
		अणु 0xe0000,  0x4000 पूर्ण,
		अणु 0x120000, 0x4000 पूर्ण,
		अणु 0x1a0000, 0x4000 पूर्ण,
		अणु 0xffffffff, 0    पूर्ण,
	पूर्ण;
	काष्ठा mem_entry *mem_tbl;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		mem_tbl = mem_tbl_5709;
	अन्यथा
		mem_tbl = mem_tbl_5706;

	क्रम (i = 0; mem_tbl[i].offset != 0xffffffff; i++) अणु
		अगर ((ret = bnx2_करो_mem_test(bp, mem_tbl[i].offset,
			mem_tbl[i].len)) != 0) अणु
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा BNX2_MAC_LOOPBACK	0
#घोषणा BNX2_PHY_LOOPBACK	1

अटल पूर्णांक
bnx2_run_loopback(काष्ठा bnx2 *bp, पूर्णांक loopback_mode)
अणु
	अचिन्हित पूर्णांक pkt_size, num_pkts, i;
	काष्ठा sk_buff *skb;
	u8 *data;
	अचिन्हित अक्षर *packet;
	u16 rx_start_idx, rx_idx;
	dma_addr_t map;
	काष्ठा bnx2_tx_bd *txbd;
	काष्ठा bnx2_sw_bd *rx_buf;
	काष्ठा l2_fhdr *rx_hdr;
	पूर्णांक ret = -ENODEV;
	काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[0], *tx_napi;
	काष्ठा bnx2_tx_ring_info *txr;
	काष्ठा bnx2_rx_ring_info *rxr;

	tx_napi = bnapi;

	txr = &tx_napi->tx_ring;
	rxr = &bnapi->rx_ring;
	अगर (loopback_mode == BNX2_MAC_LOOPBACK) अणु
		bp->loopback = MAC_LOOPBACK;
		bnx2_set_mac_loopback(bp);
	पूर्ण
	अन्यथा अगर (loopback_mode == BNX2_PHY_LOOPBACK) अणु
		अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
			वापस 0;

		bp->loopback = PHY_LOOPBACK;
		bnx2_set_phy_loopback(bp);
	पूर्ण
	अन्यथा
		वापस -EINVAL;

	pkt_size = min(bp->dev->mtu + ETH_HLEN, bp->rx_jumbo_thresh - 4);
	skb = netdev_alloc_skb(bp->dev, pkt_size);
	अगर (!skb)
		वापस -ENOMEM;
	packet = skb_put(skb, pkt_size);
	स_नकल(packet, bp->dev->dev_addr, ETH_ALEN);
	स_रखो(packet + ETH_ALEN, 0x0, 8);
	क्रम (i = 14; i < pkt_size; i++)
		packet[i] = (अचिन्हित अक्षर) (i & 0xff);

	map = dma_map_single(&bp->pdev->dev, skb->data, pkt_size,
			     PCI_DMA_TODEVICE);
	अगर (dma_mapping_error(&bp->pdev->dev, map)) अणु
		dev_kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	BNX2_WR(bp, BNX2_HC_COMMAND,
		bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW_WO_INT);

	BNX2_RD(bp, BNX2_HC_COMMAND);

	udelay(5);
	rx_start_idx = bnx2_get_hw_rx_cons(bnapi);

	num_pkts = 0;

	txbd = &txr->tx_desc_ring[BNX2_TX_RING_IDX(txr->tx_prod)];

	txbd->tx_bd_haddr_hi = (u64) map >> 32;
	txbd->tx_bd_haddr_lo = (u64) map & 0xffffffff;
	txbd->tx_bd_mss_nbytes = pkt_size;
	txbd->tx_bd_vlan_tag_flags = TX_BD_FLAGS_START | TX_BD_FLAGS_END;

	num_pkts++;
	txr->tx_prod = BNX2_NEXT_TX_BD(txr->tx_prod);
	txr->tx_prod_bseq += pkt_size;

	BNX2_WR16(bp, txr->tx_bidx_addr, txr->tx_prod);
	BNX2_WR(bp, txr->tx_bseq_addr, txr->tx_prod_bseq);

	udelay(100);

	BNX2_WR(bp, BNX2_HC_COMMAND,
		bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW_WO_INT);

	BNX2_RD(bp, BNX2_HC_COMMAND);

	udelay(5);

	dma_unmap_single(&bp->pdev->dev, map, pkt_size, PCI_DMA_TODEVICE);
	dev_kमुक्त_skb(skb);

	अगर (bnx2_get_hw_tx_cons(tx_napi) != txr->tx_prod)
		जाओ loopback_test_करोne;

	rx_idx = bnx2_get_hw_rx_cons(bnapi);
	अगर (rx_idx != rx_start_idx + num_pkts) अणु
		जाओ loopback_test_करोne;
	पूर्ण

	rx_buf = &rxr->rx_buf_ring[rx_start_idx];
	data = rx_buf->data;

	rx_hdr = get_l2_fhdr(data);
	data = (u8 *)rx_hdr + BNX2_RX_OFFSET;

	dma_sync_single_क्रम_cpu(&bp->pdev->dev,
		dma_unmap_addr(rx_buf, mapping),
		bp->rx_buf_use_size, PCI_DMA_FROMDEVICE);

	अगर (rx_hdr->l2_fhdr_status &
		(L2_FHDR_ERRORS_BAD_CRC |
		L2_FHDR_ERRORS_PHY_DECODE |
		L2_FHDR_ERRORS_ALIGNMENT |
		L2_FHDR_ERRORS_TOO_SHORT |
		L2_FHDR_ERRORS_GIANT_FRAME)) अणु

		जाओ loopback_test_करोne;
	पूर्ण

	अगर ((rx_hdr->l2_fhdr_pkt_len - 4) != pkt_size) अणु
		जाओ loopback_test_करोne;
	पूर्ण

	क्रम (i = 14; i < pkt_size; i++) अणु
		अगर (*(data + i) != (अचिन्हित अक्षर) (i & 0xff)) अणु
			जाओ loopback_test_करोne;
		पूर्ण
	पूर्ण

	ret = 0;

loopback_test_करोne:
	bp->loopback = 0;
	वापस ret;
पूर्ण

#घोषणा BNX2_MAC_LOOPBACK_FAILED	1
#घोषणा BNX2_PHY_LOOPBACK_FAILED	2
#घोषणा BNX2_LOOPBACK_FAILED		(BNX2_MAC_LOOPBACK_FAILED |	\
					 BNX2_PHY_LOOPBACK_FAILED)

अटल पूर्णांक
bnx2_test_loopback(काष्ठा bnx2 *bp)
अणु
	पूर्णांक rc = 0;

	अगर (!netअगर_running(bp->dev))
		वापस BNX2_LOOPBACK_FAILED;

	bnx2_reset_nic(bp, BNX2_DRV_MSG_CODE_RESET);
	spin_lock_bh(&bp->phy_lock);
	bnx2_init_phy(bp, 1);
	spin_unlock_bh(&bp->phy_lock);
	अगर (bnx2_run_loopback(bp, BNX2_MAC_LOOPBACK))
		rc |= BNX2_MAC_LOOPBACK_FAILED;
	अगर (bnx2_run_loopback(bp, BNX2_PHY_LOOPBACK))
		rc |= BNX2_PHY_LOOPBACK_FAILED;
	वापस rc;
पूर्ण

#घोषणा NVRAM_SIZE 0x200
#घोषणा CRC32_RESIDUAL 0xdebb20e3

अटल पूर्णांक
bnx2_test_nvram(काष्ठा bnx2 *bp)
अणु
	__be32 buf[NVRAM_SIZE / 4];
	u8 *data = (u8 *) buf;
	पूर्णांक rc = 0;
	u32 magic, csum;

	अगर ((rc = bnx2_nvram_पढ़ो(bp, 0, data, 4)) != 0)
		जाओ test_nvram_करोne;

        magic = be32_to_cpu(buf[0]);
	अगर (magic != 0x669955aa) अणु
		rc = -ENODEV;
		जाओ test_nvram_करोne;
	पूर्ण

	अगर ((rc = bnx2_nvram_पढ़ो(bp, 0x100, data, NVRAM_SIZE)) != 0)
		जाओ test_nvram_करोne;

	csum = ether_crc_le(0x100, data);
	अगर (csum != CRC32_RESIDUAL) अणु
		rc = -ENODEV;
		जाओ test_nvram_करोne;
	पूर्ण

	csum = ether_crc_le(0x100, data + 0x100);
	अगर (csum != CRC32_RESIDUAL) अणु
		rc = -ENODEV;
	पूर्ण

test_nvram_करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक
bnx2_test_link(काष्ठा bnx2 *bp)
अणु
	u32 bmsr;

	अगर (!netअगर_running(bp->dev))
		वापस -ENODEV;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) अणु
		अगर (bp->link_up)
			वापस 0;
		वापस -ENODEV;
	पूर्ण
	spin_lock_bh(&bp->phy_lock);
	bnx2_enable_bmsr1(bp);
	bnx2_पढ़ो_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_पढ़ो_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_disable_bmsr1(bp);
	spin_unlock_bh(&bp->phy_lock);

	अगर (bmsr & BMSR_LSTATUS) अणु
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
bnx2_test_पूर्णांकr(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	u16 status_idx;

	अगर (!netअगर_running(bp->dev))
		वापस -ENODEV;

	status_idx = BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD) & 0xffff;

	/* This रेजिस्टर is not touched during run-समय. */
	BNX2_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW);
	BNX2_RD(bp, BNX2_HC_COMMAND);

	क्रम (i = 0; i < 10; i++) अणु
		अगर ((BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD) & 0xffff) !=
			status_idx) अणु

			अवरोध;
		पूर्ण

		msleep_पूर्णांकerruptible(10);
	पूर्ण
	अगर (i < 10)
		वापस 0;

	वापस -ENODEV;
पूर्ण

/* Determining link क्रम parallel detection. */
अटल पूर्णांक
bnx2_5706_serdes_has_link(काष्ठा bnx2 *bp)
अणु
	u32 mode_ctl, an_dbg, exp;

	अगर (bp->phy_flags & BNX2_PHY_FLAG_NO_PARALLEL)
		वापस 0;

	bnx2_ग_लिखो_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_MODE_CTL);
	bnx2_पढ़ो_phy(bp, MII_BNX2_MISC_SHADOW, &mode_ctl);

	अगर (!(mode_ctl & MISC_SHDW_MODE_CTL_SIG_DET))
		वापस 0;

	bnx2_ग_लिखो_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_AN_DBG);
	bnx2_पढ़ो_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);
	bnx2_पढ़ो_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);

	अगर (an_dbg & (MISC_SHDW_AN_DBG_NOSYNC | MISC_SHDW_AN_DBG_RUDI_INVALID))
		वापस 0;

	bnx2_ग_लिखो_phy(bp, MII_BNX2_DSP_ADDRESS, MII_EXPAND_REG1);
	bnx2_पढ़ो_phy(bp, MII_BNX2_DSP_RW_PORT, &exp);
	bnx2_पढ़ो_phy(bp, MII_BNX2_DSP_RW_PORT, &exp);

	अगर (exp & MII_EXPAND_REG1_RUDI_C)	/* receiving CONFIG */
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम
bnx2_5706_serdes_समयr(काष्ठा bnx2 *bp)
अणु
	पूर्णांक check_link = 1;

	spin_lock(&bp->phy_lock);
	अगर (bp->serdes_an_pending) अणु
		bp->serdes_an_pending--;
		check_link = 0;
	पूर्ण अन्यथा अगर ((bp->link_up == 0) && (bp->स्वतःneg & AUTONEG_SPEED)) अणु
		u32 bmcr;

		bp->current_पूर्णांकerval = BNX2_TIMER_INTERVAL;

		bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);

		अगर (bmcr & BMCR_ANENABLE) अणु
			अगर (bnx2_5706_serdes_has_link(bp)) अणु
				bmcr &= ~BMCR_ANENABLE;
				bmcr |= BMCR_SPEED1000 | BMCR_FULLDPLX;
				bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr);
				bp->phy_flags |= BNX2_PHY_FLAG_PARALLEL_DETECT;
			पूर्ण
		पूर्ण
	पूर्ण
	अन्यथा अगर ((bp->link_up) && (bp->स्वतःneg & AUTONEG_SPEED) &&
		 (bp->phy_flags & BNX2_PHY_FLAG_PARALLEL_DETECT)) अणु
		u32 phy2;

		bnx2_ग_लिखो_phy(bp, 0x17, 0x0f01);
		bnx2_पढ़ो_phy(bp, 0x15, &phy2);
		अगर (phy2 & 0x20) अणु
			u32 bmcr;

			bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
			bmcr |= BMCR_ANENABLE;
			bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr);

			bp->phy_flags &= ~BNX2_PHY_FLAG_PARALLEL_DETECT;
		पूर्ण
	पूर्ण अन्यथा
		bp->current_पूर्णांकerval = BNX2_TIMER_INTERVAL;

	अगर (check_link) अणु
		u32 val;

		bnx2_ग_लिखो_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_AN_DBG);
		bnx2_पढ़ो_phy(bp, MII_BNX2_MISC_SHADOW, &val);
		bnx2_पढ़ो_phy(bp, MII_BNX2_MISC_SHADOW, &val);

		अगर (bp->link_up && (val & MISC_SHDW_AN_DBG_NOSYNC)) अणु
			अगर (!(bp->phy_flags & BNX2_PHY_FLAG_FORCED_DOWN)) अणु
				bnx2_5706s_क्रमce_link_dn(bp, 1);
				bp->phy_flags |= BNX2_PHY_FLAG_FORCED_DOWN;
			पूर्ण अन्यथा
				bnx2_set_link(bp);
		पूर्ण अन्यथा अगर (!bp->link_up && !(val & MISC_SHDW_AN_DBG_NOSYNC))
			bnx2_set_link(bp);
	पूर्ण
	spin_unlock(&bp->phy_lock);
पूर्ण

अटल व्योम
bnx2_5708_serdes_समयr(काष्ठा bnx2 *bp)
अणु
	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		वापस;

	अगर ((bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE) == 0) अणु
		bp->serdes_an_pending = 0;
		वापस;
	पूर्ण

	spin_lock(&bp->phy_lock);
	अगर (bp->serdes_an_pending)
		bp->serdes_an_pending--;
	अन्यथा अगर ((bp->link_up == 0) && (bp->स्वतःneg & AUTONEG_SPEED)) अणु
		u32 bmcr;

		bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
		अगर (bmcr & BMCR_ANENABLE) अणु
			bnx2_enable_क्रमced_2g5(bp);
			bp->current_पूर्णांकerval = BNX2_SERDES_FORCED_TIMEOUT;
		पूर्ण अन्यथा अणु
			bnx2_disable_क्रमced_2g5(bp);
			bp->serdes_an_pending = 2;
			bp->current_पूर्णांकerval = BNX2_TIMER_INTERVAL;
		पूर्ण

	पूर्ण अन्यथा
		bp->current_पूर्णांकerval = BNX2_TIMER_INTERVAL;

	spin_unlock(&bp->phy_lock);
पूर्ण

अटल व्योम
bnx2_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bnx2 *bp = from_समयr(bp, t, समयr);

	अगर (!netअगर_running(bp->dev))
		वापस;

	अगर (atomic_पढ़ो(&bp->पूर्णांकr_sem) != 0)
		जाओ bnx2_restart_समयr;

	अगर ((bp->flags & (BNX2_FLAG_USING_MSI | BNX2_FLAG_ONE_SHOT_MSI)) ==
	     BNX2_FLAG_USING_MSI)
		bnx2_chk_missed_msi(bp);

	bnx2_send_heart_beat(bp);

	bp->stats_blk->stat_FwRxDrop =
		bnx2_reg_rd_ind(bp, BNX2_FW_RX_DROP_COUNT);

	/* workaround occasional corrupted counters */
	अगर ((bp->flags & BNX2_FLAG_BROKEN_STATS) && bp->stats_ticks)
		BNX2_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd |
			BNX2_HC_COMMAND_STATS_NOW);

	अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
		अगर (BNX2_CHIP(bp) == BNX2_CHIP_5706)
			bnx2_5706_serdes_समयr(bp);
		अन्यथा
			bnx2_5708_serdes_समयr(bp);
	पूर्ण

bnx2_restart_समयr:
	mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);
पूर्ण

अटल पूर्णांक
bnx2_request_irq(काष्ठा bnx2 *bp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा bnx2_irq *irq;
	पूर्णांक rc = 0, i;

	अगर (bp->flags & BNX2_FLAG_USING_MSI_OR_MSIX)
		flags = 0;
	अन्यथा
		flags = IRQF_SHARED;

	क्रम (i = 0; i < bp->irq_nvecs; i++) अणु
		irq = &bp->irq_tbl[i];
		rc = request_irq(irq->vector, irq->handler, flags, irq->name,
				 &bp->bnx2_napi[i]);
		अगर (rc)
			अवरोध;
		irq->requested = 1;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम
__bnx2_मुक्त_irq(काष्ठा bnx2 *bp)
अणु
	काष्ठा bnx2_irq *irq;
	पूर्णांक i;

	क्रम (i = 0; i < bp->irq_nvecs; i++) अणु
		irq = &bp->irq_tbl[i];
		अगर (irq->requested)
			मुक्त_irq(irq->vector, &bp->bnx2_napi[i]);
		irq->requested = 0;
	पूर्ण
पूर्ण

अटल व्योम
bnx2_मुक्त_irq(काष्ठा bnx2 *bp)
अणु

	__bnx2_मुक्त_irq(bp);
	अगर (bp->flags & BNX2_FLAG_USING_MSI)
		pci_disable_msi(bp->pdev);
	अन्यथा अगर (bp->flags & BNX2_FLAG_USING_MSIX)
		pci_disable_msix(bp->pdev);

	bp->flags &= ~(BNX2_FLAG_USING_MSI_OR_MSIX | BNX2_FLAG_ONE_SHOT_MSI);
पूर्ण

अटल व्योम
bnx2_enable_msix(काष्ठा bnx2 *bp, पूर्णांक msix_vecs)
अणु
	पूर्णांक i, total_vecs;
	काष्ठा msix_entry msix_ent[BNX2_MAX_MSIX_VEC];
	काष्ठा net_device *dev = bp->dev;
	स्थिर पूर्णांक len = माप(bp->irq_tbl[0].name);

	bnx2_setup_msix_tbl(bp);
	BNX2_WR(bp, BNX2_PCI_MSIX_CONTROL, BNX2_MAX_MSIX_HW_VEC - 1);
	BNX2_WR(bp, BNX2_PCI_MSIX_TBL_OFF_BIR, BNX2_PCI_GRC_WINDOW2_BASE);
	BNX2_WR(bp, BNX2_PCI_MSIX_PBA_OFF_BIT, BNX2_PCI_GRC_WINDOW3_BASE);

	/*  Need to flush the previous three ग_लिखोs to ensure MSI-X
	 *  is setup properly */
	BNX2_RD(bp, BNX2_PCI_MSIX_CONTROL);

	क्रम (i = 0; i < BNX2_MAX_MSIX_VEC; i++) अणु
		msix_ent[i].entry = i;
		msix_ent[i].vector = 0;
	पूर्ण

	total_vecs = msix_vecs;
#अगर_घोषित BCM_CNIC
	total_vecs++;
#पूर्ण_अगर
	total_vecs = pci_enable_msix_range(bp->pdev, msix_ent,
					   BNX2_MIN_MSIX_VEC, total_vecs);
	अगर (total_vecs < 0)
		वापस;

	msix_vecs = total_vecs;
#अगर_घोषित BCM_CNIC
	msix_vecs--;
#पूर्ण_अगर
	bp->irq_nvecs = msix_vecs;
	bp->flags |= BNX2_FLAG_USING_MSIX | BNX2_FLAG_ONE_SHOT_MSI;
	क्रम (i = 0; i < total_vecs; i++) अणु
		bp->irq_tbl[i].vector = msix_ent[i].vector;
		snम_लिखो(bp->irq_tbl[i].name, len, "%s-%d", dev->name, i);
		bp->irq_tbl[i].handler = bnx2_msi_1shot;
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2_setup_पूर्णांक_mode(काष्ठा bnx2 *bp, पूर्णांक dis_msi)
अणु
	पूर्णांक cpus = netअगर_get_num_शेष_rss_queues();
	पूर्णांक msix_vecs;

	अगर (!bp->num_req_rx_rings)
		msix_vecs = max(cpus + 1, bp->num_req_tx_rings);
	अन्यथा अगर (!bp->num_req_tx_rings)
		msix_vecs = max(cpus, bp->num_req_rx_rings);
	अन्यथा
		msix_vecs = max(bp->num_req_rx_rings, bp->num_req_tx_rings);

	msix_vecs = min(msix_vecs, RX_MAX_RINGS);

	bp->irq_tbl[0].handler = bnx2_पूर्णांकerrupt;
	म_नकल(bp->irq_tbl[0].name, bp->dev->name);
	bp->irq_nvecs = 1;
	bp->irq_tbl[0].vector = bp->pdev->irq;

	अगर ((bp->flags & BNX2_FLAG_MSIX_CAP) && !dis_msi)
		bnx2_enable_msix(bp, msix_vecs);

	अगर ((bp->flags & BNX2_FLAG_MSI_CAP) && !dis_msi &&
	    !(bp->flags & BNX2_FLAG_USING_MSIX)) अणु
		अगर (pci_enable_msi(bp->pdev) == 0) अणु
			bp->flags |= BNX2_FLAG_USING_MSI;
			अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
				bp->flags |= BNX2_FLAG_ONE_SHOT_MSI;
				bp->irq_tbl[0].handler = bnx2_msi_1shot;
			पूर्ण अन्यथा
				bp->irq_tbl[0].handler = bnx2_msi;

			bp->irq_tbl[0].vector = bp->pdev->irq;
		पूर्ण
	पूर्ण

	अगर (!bp->num_req_tx_rings)
		bp->num_tx_rings = roundकरोwn_घात_of_two(bp->irq_nvecs);
	अन्यथा
		bp->num_tx_rings = min(bp->irq_nvecs, bp->num_req_tx_rings);

	अगर (!bp->num_req_rx_rings)
		bp->num_rx_rings = bp->irq_nvecs;
	अन्यथा
		bp->num_rx_rings = min(bp->irq_nvecs, bp->num_req_rx_rings);

	netअगर_set_real_num_tx_queues(bp->dev, bp->num_tx_rings);

	वापस netअगर_set_real_num_rx_queues(bp->dev, bp->num_rx_rings);
पूर्ण

/* Called with rtnl_lock */
अटल पूर्णांक
bnx2_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक rc;

	rc = bnx2_request_firmware(bp);
	अगर (rc < 0)
		जाओ out;

	netअगर_carrier_off(dev);

	bnx2_disable_पूर्णांक(bp);

	rc = bnx2_setup_पूर्णांक_mode(bp, disable_msi);
	अगर (rc)
		जाओ खोलो_err;
	bnx2_init_napi(bp);
	bnx2_napi_enable(bp);
	rc = bnx2_alloc_mem(bp);
	अगर (rc)
		जाओ खोलो_err;

	rc = bnx2_request_irq(bp);
	अगर (rc)
		जाओ खोलो_err;

	rc = bnx2_init_nic(bp, 1);
	अगर (rc)
		जाओ खोलो_err;

	mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);

	atomic_set(&bp->पूर्णांकr_sem, 0);

	स_रखो(bp->temp_stats_blk, 0, माप(काष्ठा statistics_block));

	bnx2_enable_पूर्णांक(bp);

	अगर (bp->flags & BNX2_FLAG_USING_MSI) अणु
		/* Test MSI to make sure it is working
		 * If MSI test fails, go back to INTx mode
		 */
		अगर (bnx2_test_पूर्णांकr(bp) != 0) अणु
			netdev_warn(bp->dev, "No interrupt was generated using MSI, switching to INTx mode. Please report this failure to the PCI maintainer and include system chipset information.\n");

			bnx2_disable_पूर्णांक(bp);
			bnx2_मुक्त_irq(bp);

			bnx2_setup_पूर्णांक_mode(bp, 1);

			rc = bnx2_init_nic(bp, 0);

			अगर (!rc)
				rc = bnx2_request_irq(bp);

			अगर (rc) अणु
				del_समयr_sync(&bp->समयr);
				जाओ खोलो_err;
			पूर्ण
			bnx2_enable_पूर्णांक(bp);
		पूर्ण
	पूर्ण
	अगर (bp->flags & BNX2_FLAG_USING_MSI)
		netdev_info(dev, "using MSI\n");
	अन्यथा अगर (bp->flags & BNX2_FLAG_USING_MSIX)
		netdev_info(dev, "using MSIX\n");

	netअगर_tx_start_all_queues(dev);
out:
	वापस rc;

खोलो_err:
	bnx2_napi_disable(bp);
	bnx2_मुक्त_skbs(bp);
	bnx2_मुक्त_irq(bp);
	bnx2_मुक्त_mem(bp);
	bnx2_del_napi(bp);
	bnx2_release_firmware(bp);
	जाओ out;
पूर्ण

अटल व्योम
bnx2_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2 *bp = container_of(work, काष्ठा bnx2, reset_task);
	पूर्णांक rc;
	u16 pcicmd;

	rtnl_lock();
	अगर (!netअगर_running(bp->dev)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	bnx2_netअगर_stop(bp, true);

	pci_पढ़ो_config_word(bp->pdev, PCI_COMMAND, &pcicmd);
	अगर (!(pcicmd & PCI_COMMAND_MEMORY)) अणु
		/* in हाल PCI block has reset */
		pci_restore_state(bp->pdev);
		pci_save_state(bp->pdev);
	पूर्ण
	rc = bnx2_init_nic(bp, 1);
	अगर (rc) अणु
		netdev_err(bp->dev, "failed to reset NIC, closing\n");
		bnx2_napi_enable(bp);
		dev_बंद(bp->dev);
		rtnl_unlock();
		वापस;
	पूर्ण

	atomic_set(&bp->पूर्णांकr_sem, 1);
	bnx2_netअगर_start(bp, true);
	rtnl_unlock();
पूर्ण

#घोषणा BNX2_FTQ_ENTRY(ftq) अणु __stringअगरy(ftq##FTQ_CTL), BNX2_##ftq##FTQ_CTL पूर्ण

अटल व्योम
bnx2_dump_ftq(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;
	u32 reg, bdidx, cid, valid;
	काष्ठा net_device *dev = bp->dev;
	अटल स्थिर काष्ठा ftq_reg अणु
		अक्षर *name;
		u32 off;
	पूर्ण ftq_arr[] = अणु
		BNX2_FTQ_ENTRY(RV2P_P),
		BNX2_FTQ_ENTRY(RV2P_T),
		BNX2_FTQ_ENTRY(RV2P_M),
		BNX2_FTQ_ENTRY(TBDR_),
		BNX2_FTQ_ENTRY(TDMA_),
		BNX2_FTQ_ENTRY(TXP_),
		BNX2_FTQ_ENTRY(TXP_),
		BNX2_FTQ_ENTRY(TPAT_),
		BNX2_FTQ_ENTRY(RXP_C),
		BNX2_FTQ_ENTRY(RXP_),
		BNX2_FTQ_ENTRY(COM_COMXQ_),
		BNX2_FTQ_ENTRY(COM_COMTQ_),
		BNX2_FTQ_ENTRY(COM_COMQ_),
		BNX2_FTQ_ENTRY(CP_CPQ_),
	पूर्ण;

	netdev_err(dev, "<--- start FTQ dump --->\n");
	क्रम (i = 0; i < ARRAY_SIZE(ftq_arr); i++)
		netdev_err(dev, "%s %08x\n", ftq_arr[i].name,
			   bnx2_reg_rd_ind(bp, ftq_arr[i].off));

	netdev_err(dev, "CPU states:\n");
	क्रम (reg = BNX2_TXP_CPU_MODE; reg <= BNX2_CP_CPU_MODE; reg += 0x40000)
		netdev_err(dev, "%06x mode %x state %x evt_mask %x pc %x pc %x instr %x\n",
			   reg, bnx2_reg_rd_ind(bp, reg),
			   bnx2_reg_rd_ind(bp, reg + 4),
			   bnx2_reg_rd_ind(bp, reg + 8),
			   bnx2_reg_rd_ind(bp, reg + 0x1c),
			   bnx2_reg_rd_ind(bp, reg + 0x1c),
			   bnx2_reg_rd_ind(bp, reg + 0x20));

	netdev_err(dev, "<--- end FTQ dump --->\n");
	netdev_err(dev, "<--- start TBDC dump --->\n");
	netdev_err(dev, "TBDC free cnt: %ld\n",
		   BNX2_RD(bp, BNX2_TBDC_STATUS) & BNX2_TBDC_STATUS_FREE_CNT);
	netdev_err(dev, "LINE     CID  BIDX   CMD  VALIDS\n");
	क्रम (i = 0; i < 0x20; i++) अणु
		पूर्णांक j = 0;

		BNX2_WR(bp, BNX2_TBDC_BD_ADDR, i);
		BNX2_WR(bp, BNX2_TBDC_CAM_OPCODE,
			BNX2_TBDC_CAM_OPCODE_OPCODE_CAM_READ);
		BNX2_WR(bp, BNX2_TBDC_COMMAND, BNX2_TBDC_COMMAND_CMD_REG_ARB);
		जबतक ((BNX2_RD(bp, BNX2_TBDC_COMMAND) &
			BNX2_TBDC_COMMAND_CMD_REG_ARB) && j < 100)
			j++;

		cid = BNX2_RD(bp, BNX2_TBDC_CID);
		bdidx = BNX2_RD(bp, BNX2_TBDC_BIDX);
		valid = BNX2_RD(bp, BNX2_TBDC_CAM_OPCODE);
		netdev_err(dev, "%02x    %06x  %04lx   %02x    [%x]\n",
			   i, cid, bdidx & BNX2_TBDC_BDIDX_BDIDX,
			   bdidx >> 24, (valid >> 8) & 0x0ff);
	पूर्ण
	netdev_err(dev, "<--- end TBDC dump --->\n");
पूर्ण

अटल व्योम
bnx2_dump_state(काष्ठा bnx2 *bp)
अणु
	काष्ठा net_device *dev = bp->dev;
	u32 val1, val2;

	pci_पढ़ो_config_dword(bp->pdev, PCI_COMMAND, &val1);
	netdev_err(dev, "DEBUG: intr_sem[%x] PCI_CMD[%08x]\n",
		   atomic_पढ़ो(&bp->पूर्णांकr_sem), val1);
	pci_पढ़ो_config_dword(bp->pdev, bp->pm_cap + PCI_PM_CTRL, &val1);
	pci_पढ़ो_config_dword(bp->pdev, BNX2_PCICFG_MISC_CONFIG, &val2);
	netdev_err(dev, "DEBUG: PCI_PM[%08x] PCI_MISC_CFG[%08x]\n", val1, val2);
	netdev_err(dev, "DEBUG: EMAC_TX_STATUS[%08x] EMAC_RX_STATUS[%08x]\n",
		   BNX2_RD(bp, BNX2_EMAC_TX_STATUS),
		   BNX2_RD(bp, BNX2_EMAC_RX_STATUS));
	netdev_err(dev, "DEBUG: RPM_MGMT_PKT_CTRL[%08x]\n",
		   BNX2_RD(bp, BNX2_RPM_MGMT_PKT_CTRL));
	netdev_err(dev, "DEBUG: HC_STATS_INTERRUPT_STATUS[%08x]\n",
		   BNX2_RD(bp, BNX2_HC_STATS_INTERRUPT_STATUS));
	अगर (bp->flags & BNX2_FLAG_USING_MSIX)
		netdev_err(dev, "DEBUG: PBA[%08x]\n",
			   BNX2_RD(bp, BNX2_PCI_GRC_WINDOW3_BASE));
पूर्ण

अटल व्योम
bnx2_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	bnx2_dump_ftq(bp);
	bnx2_dump_state(bp);
	bnx2_dump_mcp_state(bp);

	/* This allows the netअगर to be shutकरोwn gracefully beक्रमe resetting */
	schedule_work(&bp->reset_task);
पूर्ण

/* Called with netअगर_tx_lock.
 * bnx2_tx_पूर्णांक() runs without netअगर_tx_lock unless it needs to call
 * netअगर_wake_queue().
 */
अटल netdev_tx_t
bnx2_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	dma_addr_t mapping;
	काष्ठा bnx2_tx_bd *txbd;
	काष्ठा bnx2_sw_tx_bd *tx_buf;
	u32 len, vlan_tag_flags, last_frag, mss;
	u16 prod, ring_prod;
	पूर्णांक i;
	काष्ठा bnx2_napi *bnapi;
	काष्ठा bnx2_tx_ring_info *txr;
	काष्ठा netdev_queue *txq;

	/*  Determine which tx ring we will be placed on */
	i = skb_get_queue_mapping(skb);
	bnapi = &bp->bnx2_napi[i];
	txr = &bnapi->tx_ring;
	txq = netdev_get_tx_queue(dev, i);

	अगर (unlikely(bnx2_tx_avail(bp, txr) <
	    (skb_shinfo(skb)->nr_frags + 1))) अणु
		netअगर_tx_stop_queue(txq);
		netdev_err(dev, "BUG! Tx ring full when queue awake!\n");

		वापस NETDEV_TX_BUSY;
	पूर्ण
	len = skb_headlen(skb);
	prod = txr->tx_prod;
	ring_prod = BNX2_TX_RING_IDX(prod);

	vlan_tag_flags = 0;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		vlan_tag_flags |= TX_BD_FLAGS_TCP_UDP_CKSUM;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		vlan_tag_flags |=
			(TX_BD_FLAGS_VLAN_TAG | (skb_vlan_tag_get(skb) << 16));
	पूर्ण

	अगर ((mss = skb_shinfo(skb)->gso_size)) अणु
		u32 tcp_opt_len;
		काष्ठा iphdr *iph;

		vlan_tag_flags |= TX_BD_FLAGS_SW_LSO;

		tcp_opt_len = tcp_optlen(skb);

		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6) अणु
			u32 tcp_off = skb_transport_offset(skb) -
				      माप(काष्ठा ipv6hdr) - ETH_HLEN;

			vlan_tag_flags |= ((tcp_opt_len >> 2) << 8) |
					  TX_BD_FLAGS_SW_FLAGS;
			अगर (likely(tcp_off == 0))
				vlan_tag_flags &= ~TX_BD_FLAGS_TCP6_OFF0_MSK;
			अन्यथा अणु
				tcp_off >>= 3;
				vlan_tag_flags |= ((tcp_off & 0x3) <<
						   TX_BD_FLAGS_TCP6_OFF0_SHL) |
						  ((tcp_off & 0x10) <<
						   TX_BD_FLAGS_TCP6_OFF4_SHL);
				mss |= (tcp_off & 0xc) << TX_BD_TCP6_OFF2_SHL;
			पूर्ण
		पूर्ण अन्यथा अणु
			iph = ip_hdr(skb);
			अगर (tcp_opt_len || (iph->ihl > 5)) अणु
				vlan_tag_flags |= ((iph->ihl - 5) +
						   (tcp_opt_len >> 2)) << 8;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		mss = 0;

	mapping = dma_map_single(&bp->pdev->dev, skb->data, len, PCI_DMA_TODEVICE);
	अगर (dma_mapping_error(&bp->pdev->dev, mapping)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	tx_buf = &txr->tx_buf_ring[ring_prod];
	tx_buf->skb = skb;
	dma_unmap_addr_set(tx_buf, mapping, mapping);

	txbd = &txr->tx_desc_ring[ring_prod];

	txbd->tx_bd_haddr_hi = (u64) mapping >> 32;
	txbd->tx_bd_haddr_lo = (u64) mapping & 0xffffffff;
	txbd->tx_bd_mss_nbytes = len | (mss << 16);
	txbd->tx_bd_vlan_tag_flags = vlan_tag_flags | TX_BD_FLAGS_START;

	last_frag = skb_shinfo(skb)->nr_frags;
	tx_buf->nr_frags = last_frag;
	tx_buf->is_gso = skb_is_gso(skb);

	क्रम (i = 0; i < last_frag; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		prod = BNX2_NEXT_TX_BD(prod);
		ring_prod = BNX2_TX_RING_IDX(prod);
		txbd = &txr->tx_desc_ring[ring_prod];

		len = skb_frag_size(frag);
		mapping = skb_frag_dma_map(&bp->pdev->dev, frag, 0, len,
					   DMA_TO_DEVICE);
		अगर (dma_mapping_error(&bp->pdev->dev, mapping))
			जाओ dma_error;
		dma_unmap_addr_set(&txr->tx_buf_ring[ring_prod], mapping,
				   mapping);

		txbd->tx_bd_haddr_hi = (u64) mapping >> 32;
		txbd->tx_bd_haddr_lo = (u64) mapping & 0xffffffff;
		txbd->tx_bd_mss_nbytes = len | (mss << 16);
		txbd->tx_bd_vlan_tag_flags = vlan_tag_flags;

	पूर्ण
	txbd->tx_bd_vlan_tag_flags |= TX_BD_FLAGS_END;

	/* Sync BD data beक्रमe updating TX mailbox */
	wmb();

	netdev_tx_sent_queue(txq, skb->len);

	prod = BNX2_NEXT_TX_BD(prod);
	txr->tx_prod_bseq += skb->len;

	BNX2_WR16(bp, txr->tx_bidx_addr, prod);
	BNX2_WR(bp, txr->tx_bseq_addr, txr->tx_prod_bseq);

	txr->tx_prod = prod;

	अगर (unlikely(bnx2_tx_avail(bp, txr) <= MAX_SKB_FRAGS)) अणु
		netअगर_tx_stop_queue(txq);

		/* netअगर_tx_stop_queue() must be करोne beक्रमe checking
		 * tx index in bnx2_tx_avail() below, because in
		 * bnx2_tx_पूर्णांक(), we update tx index beक्रमe checking क्रम
		 * netअगर_tx_queue_stopped().
		 */
		smp_mb();
		अगर (bnx2_tx_avail(bp, txr) > bp->tx_wake_thresh)
			netअगर_tx_wake_queue(txq);
	पूर्ण

	वापस NETDEV_TX_OK;
dma_error:
	/* save value of frag that failed */
	last_frag = i;

	/* start back at beginning and unmap skb */
	prod = txr->tx_prod;
	ring_prod = BNX2_TX_RING_IDX(prod);
	tx_buf = &txr->tx_buf_ring[ring_prod];
	tx_buf->skb = शून्य;
	dma_unmap_single(&bp->pdev->dev, dma_unmap_addr(tx_buf, mapping),
			 skb_headlen(skb), PCI_DMA_TODEVICE);

	/* unmap reमुख्यing mapped pages */
	क्रम (i = 0; i < last_frag; i++) अणु
		prod = BNX2_NEXT_TX_BD(prod);
		ring_prod = BNX2_TX_RING_IDX(prod);
		tx_buf = &txr->tx_buf_ring[ring_prod];
		dma_unmap_page(&bp->pdev->dev, dma_unmap_addr(tx_buf, mapping),
			       skb_frag_size(&skb_shinfo(skb)->frags[i]),
			       PCI_DMA_TODEVICE);
	पूर्ण

	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* Called with rtnl_lock */
अटल पूर्णांक
bnx2_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	bnx2_disable_पूर्णांक_sync(bp);
	bnx2_napi_disable(bp);
	netअगर_tx_disable(dev);
	del_समयr_sync(&bp->समयr);
	bnx2_shutकरोwn_chip(bp);
	bnx2_मुक्त_irq(bp);
	bnx2_मुक्त_skbs(bp);
	bnx2_मुक्त_mem(bp);
	bnx2_del_napi(bp);
	bp->link_up = 0;
	netअगर_carrier_off(bp->dev);
	वापस 0;
पूर्ण

अटल व्योम
bnx2_save_stats(काष्ठा bnx2 *bp)
अणु
	u32 *hw_stats = (u32 *) bp->stats_blk;
	u32 *temp_stats = (u32 *) bp->temp_stats_blk;
	पूर्णांक i;

	/* The 1st 10 counters are 64-bit counters */
	क्रम (i = 0; i < 20; i += 2) अणु
		u32 hi;
		u64 lo;

		hi = temp_stats[i] + hw_stats[i];
		lo = (u64) temp_stats[i + 1] + (u64) hw_stats[i + 1];
		अगर (lo > 0xffffffff)
			hi++;
		temp_stats[i] = hi;
		temp_stats[i + 1] = lo & 0xffffffff;
	पूर्ण

	क्रम ( ; i < माप(काष्ठा statistics_block) / 4; i++)
		temp_stats[i] += hw_stats[i];
पूर्ण

#घोषणा GET_64BIT_NET_STATS64(ctr)		\
	(((u64) (ctr##_hi) << 32) + (u64) (ctr##_lo))

#घोषणा GET_64BIT_NET_STATS(ctr)				\
	GET_64BIT_NET_STATS64(bp->stats_blk->ctr) +		\
	GET_64BIT_NET_STATS64(bp->temp_stats_blk->ctr)

#घोषणा GET_32BIT_NET_STATS(ctr)				\
	(अचिन्हित दीर्घ) (bp->stats_blk->ctr +			\
			 bp->temp_stats_blk->ctr)

अटल व्योम
bnx2_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *net_stats)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (!bp->stats_blk)
		वापस;

	net_stats->rx_packets =
		GET_64BIT_NET_STATS(stat_IfHCInUcastPkts) +
		GET_64BIT_NET_STATS(stat_IfHCInMulticastPkts) +
		GET_64BIT_NET_STATS(stat_IfHCInBroadcastPkts);

	net_stats->tx_packets =
		GET_64BIT_NET_STATS(stat_IfHCOutUcastPkts) +
		GET_64BIT_NET_STATS(stat_IfHCOutMulticastPkts) +
		GET_64BIT_NET_STATS(stat_IfHCOutBroadcastPkts);

	net_stats->rx_bytes =
		GET_64BIT_NET_STATS(stat_IfHCInOctets);

	net_stats->tx_bytes =
		GET_64BIT_NET_STATS(stat_IfHCOutOctets);

	net_stats->multicast =
		GET_64BIT_NET_STATS(stat_IfHCInMulticastPkts);

	net_stats->collisions =
		GET_32BIT_NET_STATS(stat_EtherStatsCollisions);

	net_stats->rx_length_errors =
		GET_32BIT_NET_STATS(stat_EtherStatsUndersizePkts) +
		GET_32BIT_NET_STATS(stat_EtherStatsOverrsizePkts);

	net_stats->rx_over_errors =
		GET_32BIT_NET_STATS(stat_IfInFTQDiscards) +
		GET_32BIT_NET_STATS(stat_IfInMBUFDiscards);

	net_stats->rx_frame_errors =
		GET_32BIT_NET_STATS(stat_Dot3StatsAlignmentErrors);

	net_stats->rx_crc_errors =
		GET_32BIT_NET_STATS(stat_Dot3StatsFCSErrors);

	net_stats->rx_errors = net_stats->rx_length_errors +
		net_stats->rx_over_errors + net_stats->rx_frame_errors +
		net_stats->rx_crc_errors;

	net_stats->tx_पातed_errors =
		GET_32BIT_NET_STATS(stat_Dot3StatsExcessiveCollisions) +
		GET_32BIT_NET_STATS(stat_Dot3StatsLateCollisions);

	अगर ((BNX2_CHIP(bp) == BNX2_CHIP_5706) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_A0))
		net_stats->tx_carrier_errors = 0;
	अन्यथा अणु
		net_stats->tx_carrier_errors =
			GET_32BIT_NET_STATS(stat_Dot3StatsCarrierSenseErrors);
	पूर्ण

	net_stats->tx_errors =
		GET_32BIT_NET_STATS(stat_emac_tx_stat_करोt3statsपूर्णांकernalmactransmiterrors) +
		net_stats->tx_पातed_errors +
		net_stats->tx_carrier_errors;

	net_stats->rx_missed_errors =
		GET_32BIT_NET_STATS(stat_IfInFTQDiscards) +
		GET_32BIT_NET_STATS(stat_IfInMBUFDiscards) +
		GET_32BIT_NET_STATS(stat_FwRxDrop);

पूर्ण

/* All ethtool functions called with rtnl_lock */

अटल पूर्णांक
bnx2_get_link_ksettings(काष्ठा net_device *dev,
			काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक support_serdes = 0, support_copper = 0;
	u32 supported, advertising;

	supported = SUPPORTED_Autoneg;
	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) अणु
		support_serdes = 1;
		support_copper = 1;
	पूर्ण अन्यथा अगर (bp->phy_port == PORT_FIBRE)
		support_serdes = 1;
	अन्यथा
		support_copper = 1;

	अगर (support_serdes) अणु
		supported |= SUPPORTED_1000baseT_Full |
			SUPPORTED_FIBRE;
		अगर (bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE)
			supported |= SUPPORTED_2500baseX_Full;
	पूर्ण
	अगर (support_copper) अणु
		supported |= SUPPORTED_10baseT_Half |
			SUPPORTED_10baseT_Full |
			SUPPORTED_100baseT_Half |
			SUPPORTED_100baseT_Full |
			SUPPORTED_1000baseT_Full |
			SUPPORTED_TP;
	पूर्ण

	spin_lock_bh(&bp->phy_lock);
	cmd->base.port = bp->phy_port;
	advertising = bp->advertising;

	अगर (bp->स्वतःneg & AUTONEG_SPEED) अणु
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	पूर्ण अन्यथा अणु
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
	पूर्ण

	अगर (netअगर_carrier_ok(dev)) अणु
		cmd->base.speed = bp->line_speed;
		cmd->base.duplex = bp->duplex;
		अगर (!(bp->phy_flags & BNX2_PHY_FLAG_SERDES)) अणु
			अगर (bp->phy_flags & BNX2_PHY_FLAG_MDIX)
				cmd->base.eth_tp_mdix = ETH_TP_MDI_X;
			अन्यथा
				cmd->base.eth_tp_mdix = ETH_TP_MDI;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	spin_unlock_bh(&bp->phy_lock);

	cmd->base.phy_address = bp->phy_addr;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_set_link_ksettings(काष्ठा net_device *dev,
			स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	u8 स्वतःneg = bp->स्वतःneg;
	u8 req_duplex = bp->req_duplex;
	u16 req_line_speed = bp->req_line_speed;
	u32 advertising = bp->advertising;
	पूर्णांक err = -EINVAL;

	spin_lock_bh(&bp->phy_lock);

	अगर (cmd->base.port != PORT_TP && cmd->base.port != PORT_FIBRE)
		जाओ err_out_unlock;

	अगर (cmd->base.port != bp->phy_port &&
	    !(bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP))
		जाओ err_out_unlock;

	/* If device is करोwn, we can store the settings only अगर the user
	 * is setting the currently active port.
	 */
	अगर (!netअगर_running(dev) && cmd->base.port != bp->phy_port)
		जाओ err_out_unlock;

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		स्वतःneg |= AUTONEG_SPEED;

		ethtool_convert_link_mode_to_legacy_u32(
			&advertising, cmd->link_modes.advertising);

		अगर (cmd->base.port == PORT_TP) अणु
			advertising &= ETHTOOL_ALL_COPPER_SPEED;
			अगर (!advertising)
				advertising = ETHTOOL_ALL_COPPER_SPEED;
		पूर्ण अन्यथा अणु
			advertising &= ETHTOOL_ALL_FIBRE_SPEED;
			अगर (!advertising)
				advertising = ETHTOOL_ALL_FIBRE_SPEED;
		पूर्ण
		advertising |= ADVERTISED_Autoneg;
	पूर्ण
	अन्यथा अणु
		u32 speed = cmd->base.speed;

		अगर (cmd->base.port == PORT_FIBRE) अणु
			अगर ((speed != SPEED_1000 &&
			     speed != SPEED_2500) ||
			    (cmd->base.duplex != DUPLEX_FULL))
				जाओ err_out_unlock;

			अगर (speed == SPEED_2500 &&
			    !(bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE))
				जाओ err_out_unlock;
		पूर्ण अन्यथा अगर (speed == SPEED_1000 || speed == SPEED_2500)
			जाओ err_out_unlock;

		स्वतःneg &= ~AUTONEG_SPEED;
		req_line_speed = speed;
		req_duplex = cmd->base.duplex;
		advertising = 0;
	पूर्ण

	bp->स्वतःneg = स्वतःneg;
	bp->advertising = advertising;
	bp->req_line_speed = req_line_speed;
	bp->req_duplex = req_duplex;

	err = 0;
	/* If device is करोwn, the new settings will be picked up when it is
	 * brought up.
	 */
	अगर (netअगर_running(dev))
		err = bnx2_setup_phy(bp, cmd->base.port);

err_out_unlock:
	spin_unlock_bh(&bp->phy_lock);

	वापस err;
पूर्ण

अटल व्योम
bnx2_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(bp->pdev), माप(info->bus_info));
	strlcpy(info->fw_version, bp->fw_version, माप(info->fw_version));
पूर्ण

#घोषणा BNX2_REGDUMP_LEN		(32 * 1024)

अटल पूर्णांक
bnx2_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस BNX2_REGDUMP_LEN;
पूर्ण

अटल व्योम
bnx2_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *_p)
अणु
	u32 *p = _p, i, offset;
	u8 *orig_p = _p;
	काष्ठा bnx2 *bp = netdev_priv(dev);
	अटल स्थिर u32 reg_boundaries[] = अणु
		0x0000, 0x0098, 0x0400, 0x045c,
		0x0800, 0x0880, 0x0c00, 0x0c10,
		0x0c30, 0x0d08, 0x1000, 0x101c,
		0x1040, 0x1048, 0x1080, 0x10a4,
		0x1400, 0x1490, 0x1498, 0x14f0,
		0x1500, 0x155c, 0x1580, 0x15dc,
		0x1600, 0x1658, 0x1680, 0x16d8,
		0x1800, 0x1820, 0x1840, 0x1854,
		0x1880, 0x1894, 0x1900, 0x1984,
		0x1c00, 0x1c0c, 0x1c40, 0x1c54,
		0x1c80, 0x1c94, 0x1d00, 0x1d84,
		0x2000, 0x2030, 0x23c0, 0x2400,
		0x2800, 0x2820, 0x2830, 0x2850,
		0x2b40, 0x2c10, 0x2fc0, 0x3058,
		0x3c00, 0x3c94, 0x4000, 0x4010,
		0x4080, 0x4090, 0x43c0, 0x4458,
		0x4c00, 0x4c18, 0x4c40, 0x4c54,
		0x4fc0, 0x5010, 0x53c0, 0x5444,
		0x5c00, 0x5c18, 0x5c80, 0x5c90,
		0x5fc0, 0x6000, 0x6400, 0x6428,
		0x6800, 0x6848, 0x684c, 0x6860,
		0x6888, 0x6910, 0x8000
	पूर्ण;

	regs->version = 0;

	स_रखो(p, 0, BNX2_REGDUMP_LEN);

	अगर (!netअगर_running(bp->dev))
		वापस;

	i = 0;
	offset = reg_boundaries[0];
	p += offset;
	जबतक (offset < BNX2_REGDUMP_LEN) अणु
		*p++ = BNX2_RD(bp, offset);
		offset += 4;
		अगर (offset == reg_boundaries[i + 1]) अणु
			offset = reg_boundaries[i + 2];
			p = (u32 *) (orig_p + offset);
			i += 2;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
bnx2_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (bp->flags & BNX2_FLAG_NO_WOL) अणु
		wol->supported = 0;
		wol->wolopts = 0;
	पूर्ण
	अन्यथा अणु
		wol->supported = WAKE_MAGIC;
		अगर (bp->wol)
			wol->wolopts = WAKE_MAGIC;
		अन्यथा
			wol->wolopts = 0;
	पूर्ण
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक
bnx2_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		अगर (bp->flags & BNX2_FLAG_NO_WOL)
			वापस -EINVAL;

		bp->wol = 1;
	पूर्ण
	अन्यथा अणु
		bp->wol = 0;
	पूर्ण

	device_set_wakeup_enable(&bp->pdev->dev, bp->wol);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	u32 bmcr;

	अगर (!netअगर_running(dev))
		वापस -EAGAIN;

	अगर (!(bp->स्वतःneg & AUTONEG_SPEED)) अणु
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&bp->phy_lock);

	अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) अणु
		पूर्णांक rc;

		rc = bnx2_setup_remote_phy(bp, bp->phy_port);
		spin_unlock_bh(&bp->phy_lock);
		वापस rc;
	पूर्ण

	/* Force a link करोwn visible on the other side */
	अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
		bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, BMCR_LOOPBACK);
		spin_unlock_bh(&bp->phy_lock);

		msleep(20);

		spin_lock_bh(&bp->phy_lock);

		bp->current_पूर्णांकerval = BNX2_SERDES_AN_TIMEOUT;
		bp->serdes_an_pending = 1;
		mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);
	पूर्ण

	bnx2_पढ़ो_phy(bp, bp->mii_bmcr, &bmcr);
	bmcr &= ~BMCR_LOOPBACK;
	bnx2_ग_लिखो_phy(bp, bp->mii_bmcr, bmcr | BMCR_ANRESTART | BMCR_ANENABLE);

	spin_unlock_bh(&bp->phy_lock);

	वापस 0;
पूर्ण

अटल u32
bnx2_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	वापस bp->link_up;
पूर्ण

अटल पूर्णांक
bnx2_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (!bp->flash_info)
		वापस 0;

	वापस (पूर्णांक) bp->flash_size;
पूर्ण

अटल पूर्णांक
bnx2_get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
		u8 *eebuf)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक rc;

	/* parameters alपढ़ोy validated in ethtool_get_eeprom */

	rc = bnx2_nvram_पढ़ो(bp, eeprom->offset, eebuf, eeprom->len);

	वापस rc;
पूर्ण

अटल पूर्णांक
bnx2_set_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
		u8 *eebuf)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक rc;

	/* parameters alपढ़ोy validated in ethtool_set_eeprom */

	rc = bnx2_nvram_ग_लिखो(bp, eeprom->offset, eebuf, eeprom->len);

	वापस rc;
पूर्ण

अटल पूर्णांक
bnx2_get_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	स_रखो(coal, 0, माप(काष्ठा ethtool_coalesce));

	coal->rx_coalesce_usecs = bp->rx_ticks;
	coal->rx_max_coalesced_frames = bp->rx_quick_cons_trip;
	coal->rx_coalesce_usecs_irq = bp->rx_ticks_पूर्णांक;
	coal->rx_max_coalesced_frames_irq = bp->rx_quick_cons_trip_पूर्णांक;

	coal->tx_coalesce_usecs = bp->tx_ticks;
	coal->tx_max_coalesced_frames = bp->tx_quick_cons_trip;
	coal->tx_coalesce_usecs_irq = bp->tx_ticks_पूर्णांक;
	coal->tx_max_coalesced_frames_irq = bp->tx_quick_cons_trip_पूर्णांक;

	coal->stats_block_coalesce_usecs = bp->stats_ticks;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	bp->rx_ticks = (u16) coal->rx_coalesce_usecs;
	अगर (bp->rx_ticks > 0x3ff) bp->rx_ticks = 0x3ff;

	bp->rx_quick_cons_trip = (u16) coal->rx_max_coalesced_frames;
	अगर (bp->rx_quick_cons_trip > 0xff) bp->rx_quick_cons_trip = 0xff;

	bp->rx_ticks_पूर्णांक = (u16) coal->rx_coalesce_usecs_irq;
	अगर (bp->rx_ticks_पूर्णांक > 0x3ff) bp->rx_ticks_पूर्णांक = 0x3ff;

	bp->rx_quick_cons_trip_पूर्णांक = (u16) coal->rx_max_coalesced_frames_irq;
	अगर (bp->rx_quick_cons_trip_पूर्णांक > 0xff)
		bp->rx_quick_cons_trip_पूर्णांक = 0xff;

	bp->tx_ticks = (u16) coal->tx_coalesce_usecs;
	अगर (bp->tx_ticks > 0x3ff) bp->tx_ticks = 0x3ff;

	bp->tx_quick_cons_trip = (u16) coal->tx_max_coalesced_frames;
	अगर (bp->tx_quick_cons_trip > 0xff) bp->tx_quick_cons_trip = 0xff;

	bp->tx_ticks_पूर्णांक = (u16) coal->tx_coalesce_usecs_irq;
	अगर (bp->tx_ticks_पूर्णांक > 0x3ff) bp->tx_ticks_पूर्णांक = 0x3ff;

	bp->tx_quick_cons_trip_पूर्णांक = (u16) coal->tx_max_coalesced_frames_irq;
	अगर (bp->tx_quick_cons_trip_पूर्णांक > 0xff) bp->tx_quick_cons_trip_पूर्णांक =
		0xff;

	bp->stats_ticks = coal->stats_block_coalesce_usecs;
	अगर (bp->flags & BNX2_FLAG_BROKEN_STATS) अणु
		अगर (bp->stats_ticks != 0 && bp->stats_ticks != USEC_PER_SEC)
			bp->stats_ticks = USEC_PER_SEC;
	पूर्ण
	अगर (bp->stats_ticks > BNX2_HC_STATS_TICKS_HC_STAT_TICKS)
		bp->stats_ticks = BNX2_HC_STATS_TICKS_HC_STAT_TICKS;
	bp->stats_ticks &= BNX2_HC_STATS_TICKS_HC_STAT_TICKS;

	अगर (netअगर_running(bp->dev)) अणु
		bnx2_netअगर_stop(bp, true);
		bnx2_init_nic(bp, 0);
		bnx2_netअगर_start(bp, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
bnx2_get_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	ering->rx_max_pending = BNX2_MAX_TOTAL_RX_DESC_CNT;
	ering->rx_jumbo_max_pending = BNX2_MAX_TOTAL_RX_PG_DESC_CNT;

	ering->rx_pending = bp->rx_ring_size;
	ering->rx_jumbo_pending = bp->rx_pg_ring_size;

	ering->tx_max_pending = BNX2_MAX_TX_DESC_CNT;
	ering->tx_pending = bp->tx_ring_size;
पूर्ण

अटल पूर्णांक
bnx2_change_ring_size(काष्ठा bnx2 *bp, u32 rx, u32 tx, bool reset_irq)
अणु
	अगर (netअगर_running(bp->dev)) अणु
		/* Reset will erase chipset stats; save them */
		bnx2_save_stats(bp);

		bnx2_netअगर_stop(bp, true);
		bnx2_reset_chip(bp, BNX2_DRV_MSG_CODE_RESET);
		अगर (reset_irq) अणु
			bnx2_मुक्त_irq(bp);
			bnx2_del_napi(bp);
		पूर्ण अन्यथा अणु
			__bnx2_मुक्त_irq(bp);
		पूर्ण
		bnx2_मुक्त_skbs(bp);
		bnx2_मुक्त_mem(bp);
	पूर्ण

	bnx2_set_rx_ring_size(bp, rx);
	bp->tx_ring_size = tx;

	अगर (netअगर_running(bp->dev)) अणु
		पूर्णांक rc = 0;

		अगर (reset_irq) अणु
			rc = bnx2_setup_पूर्णांक_mode(bp, disable_msi);
			bnx2_init_napi(bp);
		पूर्ण

		अगर (!rc)
			rc = bnx2_alloc_mem(bp);

		अगर (!rc)
			rc = bnx2_request_irq(bp);

		अगर (!rc)
			rc = bnx2_init_nic(bp, 0);

		अगर (rc) अणु
			bnx2_napi_enable(bp);
			dev_बंद(bp->dev);
			वापस rc;
		पूर्ण
#अगर_घोषित BCM_CNIC
		mutex_lock(&bp->cnic_lock);
		/* Let cnic know about the new status block. */
		अगर (bp->cnic_eth_dev.drv_state & CNIC_DRV_STATE_REGD)
			bnx2_setup_cnic_irq_info(bp);
		mutex_unlock(&bp->cnic_lock);
#पूर्ण_अगर
		bnx2_netअगर_start(bp, true);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_set_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक rc;

	अगर ((ering->rx_pending > BNX2_MAX_TOTAL_RX_DESC_CNT) ||
		(ering->tx_pending > BNX2_MAX_TX_DESC_CNT) ||
		(ering->tx_pending <= MAX_SKB_FRAGS)) अणु

		वापस -EINVAL;
	पूर्ण
	rc = bnx2_change_ring_size(bp, ering->rx_pending, ering->tx_pending,
				   false);
	वापस rc;
पूर्ण

अटल व्योम
bnx2_get_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	eछोड़ो->स्वतःneg = ((bp->स्वतःneg & AUTONEG_FLOW_CTRL) != 0);
	eछोड़ो->rx_छोड़ो = ((bp->flow_ctrl & FLOW_CTRL_RX) != 0);
	eछोड़ो->tx_छोड़ो = ((bp->flow_ctrl & FLOW_CTRL_TX) != 0);
पूर्ण

अटल पूर्णांक
bnx2_set_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	bp->req_flow_ctrl = 0;
	अगर (eछोड़ो->rx_छोड़ो)
		bp->req_flow_ctrl |= FLOW_CTRL_RX;
	अगर (eछोड़ो->tx_छोड़ो)
		bp->req_flow_ctrl |= FLOW_CTRL_TX;

	अगर (eछोड़ो->स्वतःneg) अणु
		bp->स्वतःneg |= AUTONEG_FLOW_CTRL;
	पूर्ण
	अन्यथा अणु
		bp->स्वतःneg &= ~AUTONEG_FLOW_CTRL;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		spin_lock_bh(&bp->phy_lock);
		bnx2_setup_phy(bp, bp->phy_port);
		spin_unlock_bh(&bp->phy_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा अणु
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnx2_stats_str_arr[] = अणु
	अणु "rx_bytes" पूर्ण,
	अणु "rx_error_bytes" पूर्ण,
	अणु "tx_bytes" पूर्ण,
	अणु "tx_error_bytes" पूर्ण,
	अणु "rx_ucast_packets" पूर्ण,
	अणु "rx_mcast_packets" पूर्ण,
	अणु "rx_bcast_packets" पूर्ण,
	अणु "tx_ucast_packets" पूर्ण,
	अणु "tx_mcast_packets" पूर्ण,
	अणु "tx_bcast_packets" पूर्ण,
	अणु "tx_mac_errors" पूर्ण,
	अणु "tx_carrier_errors" पूर्ण,
	अणु "rx_crc_errors" पूर्ण,
	अणु "rx_align_errors" पूर्ण,
	अणु "tx_single_collisions" पूर्ण,
	अणु "tx_multi_collisions" पूर्ण,
	अणु "tx_deferred" पूर्ण,
	अणु "tx_excess_collisions" पूर्ण,
	अणु "tx_late_collisions" पूर्ण,
	अणु "tx_total_collisions" पूर्ण,
	अणु "rx_fragments" पूर्ण,
	अणु "rx_jabbers" पूर्ण,
	अणु "rx_undersize_packets" पूर्ण,
	अणु "rx_oversize_packets" पूर्ण,
	अणु "rx_64_byte_packets" पूर्ण,
	अणु "rx_65_to_127_byte_packets" पूर्ण,
	अणु "rx_128_to_255_byte_packets" पूर्ण,
	अणु "rx_256_to_511_byte_packets" पूर्ण,
	अणु "rx_512_to_1023_byte_packets" पूर्ण,
	अणु "rx_1024_to_1522_byte_packets" पूर्ण,
	अणु "rx_1523_to_9022_byte_packets" पूर्ण,
	अणु "tx_64_byte_packets" पूर्ण,
	अणु "tx_65_to_127_byte_packets" पूर्ण,
	अणु "tx_128_to_255_byte_packets" पूर्ण,
	अणु "tx_256_to_511_byte_packets" पूर्ण,
	अणु "tx_512_to_1023_byte_packets" पूर्ण,
	अणु "tx_1024_to_1522_byte_packets" पूर्ण,
	अणु "tx_1523_to_9022_byte_packets" पूर्ण,
	अणु "rx_xon_frames" पूर्ण,
	अणु "rx_xoff_frames" पूर्ण,
	अणु "tx_xon_frames" पूर्ण,
	अणु "tx_xoff_frames" पूर्ण,
	अणु "rx_mac_ctrl_frames" पूर्ण,
	अणु "rx_filtered_packets" पूर्ण,
	अणु "rx_ftq_discards" पूर्ण,
	अणु "rx_discards" पूर्ण,
	अणु "rx_fw_discards" पूर्ण,
पूर्ण;

#घोषणा BNX2_NUM_STATS ARRAY_SIZE(bnx2_stats_str_arr)

#घोषणा STATS_OFFSET32(offset_name) (दुरत्व(काष्ठा statistics_block, offset_name) / 4)

अटल स्थिर अचिन्हित दीर्घ bnx2_stats_offset_arr[BNX2_NUM_STATS] = अणु
    STATS_OFFSET32(stat_IfHCInOctets_hi),
    STATS_OFFSET32(stat_IfHCInBadOctets_hi),
    STATS_OFFSET32(stat_IfHCOutOctets_hi),
    STATS_OFFSET32(stat_IfHCOutBadOctets_hi),
    STATS_OFFSET32(stat_IfHCInUcastPkts_hi),
    STATS_OFFSET32(stat_IfHCInMulticastPkts_hi),
    STATS_OFFSET32(stat_IfHCInBroadcastPkts_hi),
    STATS_OFFSET32(stat_IfHCOutUcastPkts_hi),
    STATS_OFFSET32(stat_IfHCOutMulticastPkts_hi),
    STATS_OFFSET32(stat_IfHCOutBroadcastPkts_hi),
    STATS_OFFSET32(stat_emac_tx_stat_करोt3statsपूर्णांकernalmactransmiterrors),
    STATS_OFFSET32(stat_Dot3StatsCarrierSenseErrors),
    STATS_OFFSET32(stat_Dot3StatsFCSErrors),
    STATS_OFFSET32(stat_Dot3StatsAlignmentErrors),
    STATS_OFFSET32(stat_Dot3StatsSingleCollisionFrames),
    STATS_OFFSET32(stat_Dot3StatsMultipleCollisionFrames),
    STATS_OFFSET32(stat_Dot3StatsDeferredTransmissions),
    STATS_OFFSET32(stat_Dot3StatsExcessiveCollisions),
    STATS_OFFSET32(stat_Dot3StatsLateCollisions),
    STATS_OFFSET32(stat_EtherStatsCollisions),
    STATS_OFFSET32(stat_EtherStatsFragments),
    STATS_OFFSET32(stat_EtherStatsJabbers),
    STATS_OFFSET32(stat_EtherStatsUndersizePkts),
    STATS_OFFSET32(stat_EtherStatsOverrsizePkts),
    STATS_OFFSET32(stat_EtherStatsPktsRx64Octets),
    STATS_OFFSET32(stat_EtherStatsPktsRx65Octetsto127Octets),
    STATS_OFFSET32(stat_EtherStatsPktsRx128Octetsto255Octets),
    STATS_OFFSET32(stat_EtherStatsPktsRx256Octetsto511Octets),
    STATS_OFFSET32(stat_EtherStatsPktsRx512Octetsto1023Octets),
    STATS_OFFSET32(stat_EtherStatsPktsRx1024Octetsto1522Octets),
    STATS_OFFSET32(stat_EtherStatsPktsRx1523Octetsto9022Octets),
    STATS_OFFSET32(stat_EtherStatsPktsTx64Octets),
    STATS_OFFSET32(stat_EtherStatsPktsTx65Octetsto127Octets),
    STATS_OFFSET32(stat_EtherStatsPktsTx128Octetsto255Octets),
    STATS_OFFSET32(stat_EtherStatsPktsTx256Octetsto511Octets),
    STATS_OFFSET32(stat_EtherStatsPktsTx512Octetsto1023Octets),
    STATS_OFFSET32(stat_EtherStatsPktsTx1024Octetsto1522Octets),
    STATS_OFFSET32(stat_EtherStatsPktsTx1523Octetsto9022Octets),
    STATS_OFFSET32(stat_XonPauseFramesReceived),
    STATS_OFFSET32(stat_XoffPauseFramesReceived),
    STATS_OFFSET32(stat_OutXonSent),
    STATS_OFFSET32(stat_OutXoffSent),
    STATS_OFFSET32(stat_MacControlFramesReceived),
    STATS_OFFSET32(stat_IfInFramesL2FilterDiscards),
    STATS_OFFSET32(stat_IfInFTQDiscards),
    STATS_OFFSET32(stat_IfInMBUFDiscards),
    STATS_OFFSET32(stat_FwRxDrop),
पूर्ण;

/* stat_IfHCInBadOctets and stat_Dot3StatsCarrierSenseErrors are
 * skipped because of errata.
 */
अटल u8 bnx2_5706_stats_len_arr[BNX2_NUM_STATS] = अणु
	8,0,8,8,8,8,8,8,8,8,
	4,0,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,
पूर्ण;

अटल u8 bnx2_5708_stats_len_arr[BNX2_NUM_STATS] = अणु
	8,0,8,8,8,8,8,8,8,8,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,
पूर्ण;

#घोषणा BNX2_NUM_TESTS 6

अटल काष्ठा अणु
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnx2_tests_str_arr[BNX2_NUM_TESTS] = अणु
	अणु "register_test (offline)" पूर्ण,
	अणु "memory_test (offline)" पूर्ण,
	अणु "loopback_test (offline)" पूर्ण,
	अणु "nvram_test (online)" पूर्ण,
	अणु "interrupt_test (online)" पूर्ण,
	अणु "link_test (online)" पूर्ण,
पूर्ण;

अटल पूर्णांक
bnx2_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस BNX2_NUM_TESTS;
	हाल ETH_SS_STATS:
		वापस BNX2_NUM_STATS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
bnx2_self_test(काष्ठा net_device *dev, काष्ठा ethtool_test *etest, u64 *buf)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	स_रखो(buf, 0, माप(u64) * BNX2_NUM_TESTS);
	अगर (etest->flags & ETH_TEST_FL_OFFLINE) अणु
		पूर्णांक i;

		bnx2_netअगर_stop(bp, true);
		bnx2_reset_chip(bp, BNX2_DRV_MSG_CODE_DIAG);
		bnx2_मुक्त_skbs(bp);

		अगर (bnx2_test_रेजिस्टरs(bp) != 0) अणु
			buf[0] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		पूर्ण
		अगर (bnx2_test_memory(bp) != 0) अणु
			buf[1] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		पूर्ण
		अगर ((buf[2] = bnx2_test_loopback(bp)) != 0)
			etest->flags |= ETH_TEST_FL_FAILED;

		अगर (!netअगर_running(bp->dev))
			bnx2_shutकरोwn_chip(bp);
		अन्यथा अणु
			bnx2_init_nic(bp, 1);
			bnx2_netअगर_start(bp, true);
		पूर्ण

		/* रुको क्रम link up */
		क्रम (i = 0; i < 7; i++) अणु
			अगर (bp->link_up)
				अवरोध;
			msleep_पूर्णांकerruptible(1000);
		पूर्ण
	पूर्ण

	अगर (bnx2_test_nvram(bp) != 0) अणु
		buf[3] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण
	अगर (bnx2_test_पूर्णांकr(bp) != 0) अणु
		buf[4] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	अगर (bnx2_test_link(bp) != 0) अणु
		buf[5] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;

	पूर्ण
पूर्ण

अटल व्योम
bnx2_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buf, bnx2_stats_str_arr,
			माप(bnx2_stats_str_arr));
		अवरोध;
	हाल ETH_SS_TEST:
		स_नकल(buf, bnx2_tests_str_arr,
			माप(bnx2_tests_str_arr));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bnx2_get_ethtool_stats(काष्ठा net_device *dev,
		काष्ठा ethtool_stats *stats, u64 *buf)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक i;
	u32 *hw_stats = (u32 *) bp->stats_blk;
	u32 *temp_stats = (u32 *) bp->temp_stats_blk;
	u8 *stats_len_arr = शून्य;

	अगर (!hw_stats) अणु
		स_रखो(buf, 0, माप(u64) * BNX2_NUM_STATS);
		वापस;
	पूर्ण

	अगर ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A2) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_A0))
		stats_len_arr = bnx2_5706_stats_len_arr;
	अन्यथा
		stats_len_arr = bnx2_5708_stats_len_arr;

	क्रम (i = 0; i < BNX2_NUM_STATS; i++) अणु
		अचिन्हित दीर्घ offset;

		अगर (stats_len_arr[i] == 0) अणु
			/* skip this counter */
			buf[i] = 0;
			जारी;
		पूर्ण

		offset = bnx2_stats_offset_arr[i];
		अगर (stats_len_arr[i] == 4) अणु
			/* 4-byte counter */
			buf[i] = (u64) *(hw_stats + offset) +
				 *(temp_stats + offset);
			जारी;
		पूर्ण
		/* 8-byte counter */
		buf[i] = (((u64) *(hw_stats + offset)) << 32) +
			 *(hw_stats + offset + 1) +
			 (((u64) *(temp_stats + offset)) << 32) +
			 *(temp_stats + offset + 1);
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2_set_phys_id(काष्ठा net_device *dev, क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		bp->leds_save = BNX2_RD(bp, BNX2_MISC_CFG);
		BNX2_WR(bp, BNX2_MISC_CFG, BNX2_MISC_CFG_LEDMODE_MAC);
		वापस 1;	/* cycle on/off once per second */

	हाल ETHTOOL_ID_ON:
		BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE |
			BNX2_EMAC_LED_1000MB_OVERRIDE |
			BNX2_EMAC_LED_100MB_OVERRIDE |
			BNX2_EMAC_LED_10MB_OVERRIDE |
			BNX2_EMAC_LED_TRAFFIC_OVERRIDE |
			BNX2_EMAC_LED_TRAFFIC);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		BNX2_WR(bp, BNX2_EMAC_LED, 0);
		BNX2_WR(bp, BNX2_MISC_CFG, bp->leds_save);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	/* TSO with VLAN tag won't work with current firmware */
	अगर (features & NETIF_F_HW_VLAN_CTAG_TX)
		dev->vlan_features |= (dev->hw_features & NETIF_F_ALL_TSO);
	अन्यथा
		dev->vlan_features &= ~NETIF_F_ALL_TSO;

	अगर ((!!(features & NETIF_F_HW_VLAN_CTAG_RX) !=
	    !!(bp->rx_mode & BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG)) &&
	    netअगर_running(dev)) अणु
		bnx2_netअगर_stop(bp, false);
		dev->features = features;
		bnx2_set_rx_mode(dev);
		bnx2_fw_sync(bp, BNX2_DRV_MSG_CODE_KEEP_VLAN_UPDATE, 0, 1);
		bnx2_netअगर_start(bp, false);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2_get_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channels)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	u32 max_rx_rings = 1;
	u32 max_tx_rings = 1;

	अगर ((bp->flags & BNX2_FLAG_MSIX_CAP) && !disable_msi) अणु
		max_rx_rings = RX_MAX_RINGS;
		max_tx_rings = TX_MAX_RINGS;
	पूर्ण

	channels->max_rx = max_rx_rings;
	channels->max_tx = max_tx_rings;
	channels->max_other = 0;
	channels->max_combined = 0;
	channels->rx_count = bp->num_rx_rings;
	channels->tx_count = bp->num_tx_rings;
	channels->other_count = 0;
	channels->combined_count = 0;
पूर्ण

अटल पूर्णांक bnx2_set_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channels)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	u32 max_rx_rings = 1;
	u32 max_tx_rings = 1;
	पूर्णांक rc = 0;

	अगर ((bp->flags & BNX2_FLAG_MSIX_CAP) && !disable_msi) अणु
		max_rx_rings = RX_MAX_RINGS;
		max_tx_rings = TX_MAX_RINGS;
	पूर्ण
	अगर (channels->rx_count > max_rx_rings ||
	    channels->tx_count > max_tx_rings)
		वापस -EINVAL;

	bp->num_req_rx_rings = channels->rx_count;
	bp->num_req_tx_rings = channels->tx_count;

	अगर (netअगर_running(dev))
		rc = bnx2_change_ring_size(bp, bp->rx_ring_size,
					   bp->tx_ring_size, true);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bnx2_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USECS_IRQ |
				     ETHTOOL_COALESCE_MAX_FRAMES_IRQ |
				     ETHTOOL_COALESCE_STATS_BLOCK_USECS,
	.get_drvinfo		= bnx2_get_drvinfo,
	.get_regs_len		= bnx2_get_regs_len,
	.get_regs		= bnx2_get_regs,
	.get_wol		= bnx2_get_wol,
	.set_wol		= bnx2_set_wol,
	.nway_reset		= bnx2_nway_reset,
	.get_link		= bnx2_get_link,
	.get_eeprom_len		= bnx2_get_eeprom_len,
	.get_eeprom		= bnx2_get_eeprom,
	.set_eeprom		= bnx2_set_eeprom,
	.get_coalesce		= bnx2_get_coalesce,
	.set_coalesce		= bnx2_set_coalesce,
	.get_ringparam		= bnx2_get_ringparam,
	.set_ringparam		= bnx2_set_ringparam,
	.get_छोड़ोparam		= bnx2_get_छोड़ोparam,
	.set_छोड़ोparam		= bnx2_set_छोड़ोparam,
	.self_test		= bnx2_self_test,
	.get_strings		= bnx2_get_strings,
	.set_phys_id		= bnx2_set_phys_id,
	.get_ethtool_stats	= bnx2_get_ethtool_stats,
	.get_sset_count		= bnx2_get_sset_count,
	.get_channels		= bnx2_get_channels,
	.set_channels		= bnx2_set_channels,
	.get_link_ksettings	= bnx2_get_link_ksettings,
	.set_link_ksettings	= bnx2_set_link_ksettings,
पूर्ण;

/* Called with rtnl_lock */
अटल पूर्णांक
bnx2_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक err;

	चयन(cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = bp->phy_addr;

		fallthrough;
	हाल SIOCGMIIREG: अणु
		u32 mii_regval;

		अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
			वापस -EOPNOTSUPP;

		अगर (!netअगर_running(dev))
			वापस -EAGAIN;

		spin_lock_bh(&bp->phy_lock);
		err = bnx2_पढ़ो_phy(bp, data->reg_num & 0x1f, &mii_regval);
		spin_unlock_bh(&bp->phy_lock);

		data->val_out = mii_regval;

		वापस err;
	पूर्ण

	हाल SIOCSMIIREG:
		अगर (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
			वापस -EOPNOTSUPP;

		अगर (!netअगर_running(dev))
			वापस -EAGAIN;

		spin_lock_bh(&bp->phy_lock);
		err = bnx2_ग_लिखो_phy(bp, data->reg_num & 0x1f, data->val_in);
		spin_unlock_bh(&bp->phy_lock);

		वापस err;

	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

/* Called with rtnl_lock */
अटल पूर्णांक
bnx2_change_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	अगर (netअगर_running(dev))
		bnx2_set_mac_addr(bp, bp->dev->dev_addr, 0);

	वापस 0;
पूर्ण

/* Called with rtnl_lock */
अटल पूर्णांक
bnx2_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);

	dev->mtu = new_mtu;
	वापस bnx2_change_ring_size(bp, bp->rx_ring_size, bp->tx_ring_size,
				     false);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम
poll_bnx2(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < bp->irq_nvecs; i++) अणु
		काष्ठा bnx2_irq *irq = &bp->irq_tbl[i];

		disable_irq(irq->vector);
		irq->handler(irq->vector, &bp->bnx2_napi[i]);
		enable_irq(irq->vector);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम
bnx2_get_5709_media(काष्ठा bnx2 *bp)
अणु
	u32 val = BNX2_RD(bp, BNX2_MISC_DUAL_MEDIA_CTRL);
	u32 bond_id = val & BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID;
	u32 strap;

	अगर (bond_id == BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID_C)
		वापस;
	अन्यथा अगर (bond_id == BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID_S) अणु
		bp->phy_flags |= BNX2_PHY_FLAG_SERDES;
		वापस;
	पूर्ण

	अगर (val & BNX2_MISC_DUAL_MEDIA_CTRL_STRAP_OVERRIDE)
		strap = (val & BNX2_MISC_DUAL_MEDIA_CTRL_PHY_CTRL) >> 21;
	अन्यथा
		strap = (val & BNX2_MISC_DUAL_MEDIA_CTRL_PHY_CTRL_STRAP) >> 8;

	अगर (bp->func == 0) अणु
		चयन (strap) अणु
		हाल 0x4:
		हाल 0x5:
		हाल 0x6:
			bp->phy_flags |= BNX2_PHY_FLAG_SERDES;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (strap) अणु
		हाल 0x1:
		हाल 0x2:
		हाल 0x4:
			bp->phy_flags |= BNX2_PHY_FLAG_SERDES;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
bnx2_get_pci_speed(काष्ठा bnx2 *bp)
अणु
	u32 reg;

	reg = BNX2_RD(bp, BNX2_PCICFG_MISC_STATUS);
	अगर (reg & BNX2_PCICFG_MISC_STATUS_PCIX_DET) अणु
		u32 clkreg;

		bp->flags |= BNX2_FLAG_PCIX;

		clkreg = BNX2_RD(bp, BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS);

		clkreg &= BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET;
		चयन (clkreg) अणु
		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_133MHZ:
			bp->bus_speed_mhz = 133;
			अवरोध;

		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_95MHZ:
			bp->bus_speed_mhz = 100;
			अवरोध;

		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_66MHZ:
		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_80MHZ:
			bp->bus_speed_mhz = 66;
			अवरोध;

		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_48MHZ:
		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_55MHZ:
			bp->bus_speed_mhz = 50;
			अवरोध;

		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_LOW:
		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_32MHZ:
		हाल BNX2_PCICFG_PCI_CLOCK_CONTROL_BITS_PCI_CLK_SPD_DET_38MHZ:
			bp->bus_speed_mhz = 33;
			अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (reg & BNX2_PCICFG_MISC_STATUS_M66EN)
			bp->bus_speed_mhz = 66;
		अन्यथा
			bp->bus_speed_mhz = 33;
	पूर्ण

	अगर (reg & BNX2_PCICFG_MISC_STATUS_32BIT_DET)
		bp->flags |= BNX2_FLAG_PCI_32BIT;

पूर्ण

अटल व्योम
bnx2_पढ़ो_vpd_fw_ver(काष्ठा bnx2 *bp)
अणु
	पूर्णांक rc, i, j;
	u8 *data;
	अचिन्हित पूर्णांक block_end, rosize, len;

#घोषणा BNX2_VPD_NVRAM_OFFSET	0x300
#घोषणा BNX2_VPD_LEN		128
#घोषणा BNX2_MAX_VER_SLEN	30

	data = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!data)
		वापस;

	rc = bnx2_nvram_पढ़ो(bp, BNX2_VPD_NVRAM_OFFSET, data + BNX2_VPD_LEN,
			     BNX2_VPD_LEN);
	अगर (rc)
		जाओ vpd_करोne;

	क्रम (i = 0; i < BNX2_VPD_LEN; i += 4) अणु
		data[i] = data[i + BNX2_VPD_LEN + 3];
		data[i + 1] = data[i + BNX2_VPD_LEN + 2];
		data[i + 2] = data[i + BNX2_VPD_LEN + 1];
		data[i + 3] = data[i + BNX2_VPD_LEN];
	पूर्ण

	i = pci_vpd_find_tag(data, BNX2_VPD_LEN, PCI_VPD_LRDT_RO_DATA);
	अगर (i < 0)
		जाओ vpd_करोne;

	rosize = pci_vpd_lrdt_size(&data[i]);
	i += PCI_VPD_LRDT_TAG_SIZE;
	block_end = i + rosize;

	अगर (block_end > BNX2_VPD_LEN)
		जाओ vpd_करोne;

	j = pci_vpd_find_info_keyword(data, i, rosize,
				      PCI_VPD_RO_KEYWORD_MFR_ID);
	अगर (j < 0)
		जाओ vpd_करोne;

	len = pci_vpd_info_field_size(&data[j]);

	j += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (j + len > block_end || len != 4 ||
	    स_भेद(&data[j], "1028", 4))
		जाओ vpd_करोne;

	j = pci_vpd_find_info_keyword(data, i, rosize,
				      PCI_VPD_RO_KEYWORD_VENDOR0);
	अगर (j < 0)
		जाओ vpd_करोne;

	len = pci_vpd_info_field_size(&data[j]);

	j += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (j + len > block_end || len > BNX2_MAX_VER_SLEN)
		जाओ vpd_करोne;

	स_नकल(bp->fw_version, &data[j], len);
	bp->fw_version[len] = ' ';

vpd_करोne:
	kमुक्त(data);
पूर्ण

अटल पूर्णांक
bnx2_init_board(काष्ठा pci_dev *pdev, काष्ठा net_device *dev)
अणु
	काष्ठा bnx2 *bp;
	पूर्णांक rc, i, j;
	u32 reg;
	u64 dma_mask, persist_dma_mask;
	पूर्णांक err;

	SET_NETDEV_DEV(dev, &pdev->dev);
	bp = netdev_priv(dev);

	bp->flags = 0;
	bp->phy_flags = 0;

	bp->temp_stats_blk =
		kzalloc(माप(काष्ठा statistics_block), GFP_KERNEL);

	अगर (!bp->temp_stats_blk) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण

	/* enable device (incl. PCI PM wakeup), and bus-mastering */
	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		जाओ err_out;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev,
			"Cannot find PCI device base address, aborting\n");
		rc = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	rc = pci_request_regions(pdev, DRV_MODULE_NAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		जाओ err_out_disable;
	पूर्ण

	pci_set_master(pdev);

	bp->pm_cap = pdev->pm_cap;
	अगर (bp->pm_cap == 0) अणु
		dev_err(&pdev->dev,
			"Cannot find power management capability, aborting\n");
		rc = -EIO;
		जाओ err_out_release;
	पूर्ण

	bp->dev = dev;
	bp->pdev = pdev;

	spin_lock_init(&bp->phy_lock);
	spin_lock_init(&bp->indirect_lock);
#अगर_घोषित BCM_CNIC
	mutex_init(&bp->cnic_lock);
#पूर्ण_अगर
	INIT_WORK(&bp->reset_task, bnx2_reset_task);

	bp->regview = pci_iomap(pdev, 0, MB_GET_CID_ADDR(TX_TSS_CID +
							 TX_MAX_TSS_RINGS + 1));
	अगर (!bp->regview) अणु
		dev_err(&pdev->dev, "Cannot map register space, aborting\n");
		rc = -ENOMEM;
		जाओ err_out_release;
	पूर्ण

	/* Configure byte swap and enable ग_लिखो to the reg_winकरोw रेजिस्टरs.
	 * Rely on CPU to करो target byte swapping on big endian प्रणालीs
	 * The chip's target access swapping will not swap all accesses
	 */
	BNX2_WR(bp, BNX2_PCICFG_MISC_CONFIG,
		BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA |
		BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP);

	bp->chip_id = BNX2_RD(bp, BNX2_MISC_ID);

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709) अणु
		अगर (!pci_is_pcie(pdev)) अणु
			dev_err(&pdev->dev, "Not PCIE, aborting\n");
			rc = -EIO;
			जाओ err_out_unmap;
		पूर्ण
		bp->flags |= BNX2_FLAG_PCIE;
		अगर (BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Ax)
			bp->flags |= BNX2_FLAG_JUMBO_BROKEN;

		/* AER (Advanced Error Reporting) hooks */
		err = pci_enable_pcie_error_reporting(pdev);
		अगर (!err)
			bp->flags |= BNX2_FLAG_AER_ENABLED;

	पूर्ण अन्यथा अणु
		bp->pcix_cap = pci_find_capability(pdev, PCI_CAP_ID_PCIX);
		अगर (bp->pcix_cap == 0) अणु
			dev_err(&pdev->dev,
				"Cannot find PCIX capability, aborting\n");
			rc = -EIO;
			जाओ err_out_unmap;
		पूर्ण
		bp->flags |= BNX2_FLAG_BROKEN_STATS;
	पूर्ण

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709 &&
	    BNX2_CHIP_REV(bp) != BNX2_CHIP_REV_Ax) अणु
		अगर (pdev->msix_cap)
			bp->flags |= BNX2_FLAG_MSIX_CAP;
	पूर्ण

	अगर (BNX2_CHIP_ID(bp) != BNX2_CHIP_ID_5706_A0 &&
	    BNX2_CHIP_ID(bp) != BNX2_CHIP_ID_5706_A1) अणु
		अगर (pdev->msi_cap)
			bp->flags |= BNX2_FLAG_MSI_CAP;
	पूर्ण

	/* 5708 cannot support DMA addresses > 40-bit.  */
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5708)
		persist_dma_mask = dma_mask = DMA_BIT_MASK(40);
	अन्यथा
		persist_dma_mask = dma_mask = DMA_BIT_MASK(64);

	/* Configure DMA attributes. */
	अगर (pci_set_dma_mask(pdev, dma_mask) == 0) अणु
		dev->features |= NETIF_F_HIGHDMA;
		rc = pci_set_consistent_dma_mask(pdev, persist_dma_mask);
		अगर (rc) अणु
			dev_err(&pdev->dev,
				"pci_set_consistent_dma_mask failed, aborting\n");
			जाओ err_out_unmap;
		पूर्ण
	पूर्ण अन्यथा अगर ((rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) != 0) अणु
		dev_err(&pdev->dev, "System does not support DMA, aborting\n");
		जाओ err_out_unmap;
	पूर्ण

	अगर (!(bp->flags & BNX2_FLAG_PCIE))
		bnx2_get_pci_speed(bp);

	/* 5706A0 may falsely detect SERR and PERR. */
	अगर (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) अणु
		reg = BNX2_RD(bp, PCI_COMMAND);
		reg &= ~(PCI_COMMAND_SERR | PCI_COMMAND_PARITY);
		BNX2_WR(bp, PCI_COMMAND, reg);
	पूर्ण अन्यथा अगर ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1) &&
		!(bp->flags & BNX2_FLAG_PCIX)) अणु
		dev_err(&pdev->dev,
			"5706 A1 can only be used in a PCIX bus, aborting\n");
		rc = -EPERM;
		जाओ err_out_unmap;
	पूर्ण

	bnx2_init_nvram(bp);

	reg = bnx2_reg_rd_ind(bp, BNX2_SHM_HDR_SIGNATURE);

	अगर (bnx2_reg_rd_ind(bp, BNX2_MCP_TOE_ID) & BNX2_MCP_TOE_ID_FUNCTION_ID)
		bp->func = 1;

	अगर ((reg & BNX2_SHM_HDR_SIGNATURE_SIG_MASK) ==
	    BNX2_SHM_HDR_SIGNATURE_SIG) अणु
		u32 off = bp->func << 2;

		bp->shmem_base = bnx2_reg_rd_ind(bp, BNX2_SHM_HDR_ADDR_0 + off);
	पूर्ण अन्यथा
		bp->shmem_base = HOST_VIEW_SHMEM_BASE;

	/* Get the permanent MAC address.  First we need to make sure the
	 * firmware is actually running.
	 */
	reg = bnx2_shmem_rd(bp, BNX2_DEV_INFO_SIGNATURE);

	अगर ((reg & BNX2_DEV_INFO_SIGNATURE_MAGIC_MASK) !=
	    BNX2_DEV_INFO_SIGNATURE_MAGIC) अणु
		dev_err(&pdev->dev, "Firmware not running, aborting\n");
		rc = -ENODEV;
		जाओ err_out_unmap;
	पूर्ण

	bnx2_पढ़ो_vpd_fw_ver(bp);

	j = म_माप(bp->fw_version);
	reg = bnx2_shmem_rd(bp, BNX2_DEV_INFO_BC_REV);
	क्रम (i = 0; i < 3 && j < 24; i++) अणु
		u8 num, k, skip0;

		अगर (i == 0) अणु
			bp->fw_version[j++] = 'b';
			bp->fw_version[j++] = 'c';
			bp->fw_version[j++] = ' ';
		पूर्ण
		num = (u8) (reg >> (24 - (i * 8)));
		क्रम (k = 100, skip0 = 1; k >= 1; num %= k, k /= 10) अणु
			अगर (num >= k || !skip0 || k == 1) अणु
				bp->fw_version[j++] = (num / k) + '0';
				skip0 = 0;
			पूर्ण
		पूर्ण
		अगर (i != 2)
			bp->fw_version[j++] = '.';
	पूर्ण
	reg = bnx2_shmem_rd(bp, BNX2_PORT_FEATURE);
	अगर (reg & BNX2_PORT_FEATURE_WOL_ENABLED)
		bp->wol = 1;

	अगर (reg & BNX2_PORT_FEATURE_ASF_ENABLED) अणु
		bp->flags |= BNX2_FLAG_ASF_ENABLE;

		क्रम (i = 0; i < 30; i++) अणु
			reg = bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION);
			अगर (reg & BNX2_CONDITION_MFW_RUN_MASK)
				अवरोध;
			msleep(10);
		पूर्ण
	पूर्ण
	reg = bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION);
	reg &= BNX2_CONDITION_MFW_RUN_MASK;
	अगर (reg != BNX2_CONDITION_MFW_RUN_UNKNOWN &&
	    reg != BNX2_CONDITION_MFW_RUN_NONE) अणु
		u32 addr = bnx2_shmem_rd(bp, BNX2_MFW_VER_PTR);

		अगर (j < 32)
			bp->fw_version[j++] = ' ';
		क्रम (i = 0; i < 3 && j < 28; i++) अणु
			reg = bnx2_reg_rd_ind(bp, addr + i * 4);
			reg = be32_to_cpu(reg);
			स_नकल(&bp->fw_version[j], &reg, 4);
			j += 4;
		पूर्ण
	पूर्ण

	reg = bnx2_shmem_rd(bp, BNX2_PORT_HW_CFG_MAC_UPPER);
	bp->mac_addr[0] = (u8) (reg >> 8);
	bp->mac_addr[1] = (u8) reg;

	reg = bnx2_shmem_rd(bp, BNX2_PORT_HW_CFG_MAC_LOWER);
	bp->mac_addr[2] = (u8) (reg >> 24);
	bp->mac_addr[3] = (u8) (reg >> 16);
	bp->mac_addr[4] = (u8) (reg >> 8);
	bp->mac_addr[5] = (u8) reg;

	bp->tx_ring_size = BNX2_MAX_TX_DESC_CNT;
	bnx2_set_rx_ring_size(bp, 255);

	bp->tx_quick_cons_trip_पूर्णांक = 2;
	bp->tx_quick_cons_trip = 20;
	bp->tx_ticks_पूर्णांक = 18;
	bp->tx_ticks = 80;

	bp->rx_quick_cons_trip_पूर्णांक = 2;
	bp->rx_quick_cons_trip = 12;
	bp->rx_ticks_पूर्णांक = 18;
	bp->rx_ticks = 18;

	bp->stats_ticks = USEC_PER_SEC & BNX2_HC_STATS_TICKS_HC_STAT_TICKS;

	bp->current_पूर्णांकerval = BNX2_TIMER_INTERVAL;

	bp->phy_addr = 1;

	/* allocate stats_blk */
	rc = bnx2_alloc_stats_blk(dev);
	अगर (rc)
		जाओ err_out_unmap;

	/* Disable WOL support अगर we are running on a SERDES chip. */
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_get_5709_media(bp);
	अन्यथा अगर (BNX2_CHIP_BOND(bp) & BNX2_CHIP_BOND_SERDES_BIT)
		bp->phy_flags |= BNX2_PHY_FLAG_SERDES;

	bp->phy_port = PORT_TP;
	अगर (bp->phy_flags & BNX2_PHY_FLAG_SERDES) अणु
		bp->phy_port = PORT_FIBRE;
		reg = bnx2_shmem_rd(bp, BNX2_SHARED_HW_CFG_CONFIG);
		अगर (!(reg & BNX2_SHARED_HW_CFG_GIG_LINK_ON_VAUX)) अणु
			bp->flags |= BNX2_FLAG_NO_WOL;
			bp->wol = 0;
		पूर्ण
		अगर (BNX2_CHIP(bp) == BNX2_CHIP_5706) अणु
			/* Don't करो parallel detect on this board because of
			 * some board problems.  The link will not go करोwn
			 * अगर we करो parallel detect.
			 */
			अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_HP &&
			    pdev->subप्रणाली_device == 0x310c)
				bp->phy_flags |= BNX2_PHY_FLAG_NO_PARALLEL;
		पूर्ण अन्यथा अणु
			bp->phy_addr = 2;
			अगर (reg & BNX2_SHARED_HW_CFG_PHY_2_5G)
				bp->phy_flags |= BNX2_PHY_FLAG_2_5G_CAPABLE;
		पूर्ण
	पूर्ण अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5706 ||
		   BNX2_CHIP(bp) == BNX2_CHIP_5708)
		bp->phy_flags |= BNX2_PHY_FLAG_CRC_FIX;
	अन्यथा अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709 &&
		 (BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Ax ||
		  BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Bx))
		bp->phy_flags |= BNX2_PHY_FLAG_DIS_EARLY_DAC;

	bnx2_init_fw_cap(bp);

	अगर ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_A0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_B0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_B1) ||
	    !(BNX2_RD(bp, BNX2_PCI_CONFIG_3) & BNX2_PCI_CONFIG_3_VAUX_PRESET)) अणु
		bp->flags |= BNX2_FLAG_NO_WOL;
		bp->wol = 0;
	पूर्ण

	अगर (bp->flags & BNX2_FLAG_NO_WOL)
		device_set_wakeup_capable(&bp->pdev->dev, false);
	अन्यथा
		device_set_wakeup_enable(&bp->pdev->dev, bp->wol);

	अगर (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) अणु
		bp->tx_quick_cons_trip_पूर्णांक =
			bp->tx_quick_cons_trip;
		bp->tx_ticks_पूर्णांक = bp->tx_ticks;
		bp->rx_quick_cons_trip_पूर्णांक =
			bp->rx_quick_cons_trip;
		bp->rx_ticks_पूर्णांक = bp->rx_ticks;
		bp->comp_prod_trip_पूर्णांक = bp->comp_prod_trip;
		bp->com_ticks_पूर्णांक = bp->com_ticks;
		bp->cmd_ticks_पूर्णांक = bp->cmd_ticks;
	पूर्ण

	/* Disable MSI on 5706 अगर AMD 8132 bridge is found.
	 *
	 * MSI is defined to be 32-bit ग_लिखो.  The 5706 करोes 64-bit MSI ग_लिखोs
	 * with byte enables disabled on the unused 32-bit word.  This is legal
	 * but causes problems on the AMD 8132 which will eventually stop
	 * responding after a जबतक.
	 *
	 * AMD believes this incompatibility is unique to the 5706, and
	 * prefers to locally disable MSI rather than globally disabling it.
	 */
	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5706 && disable_msi == 0) अणु
		काष्ठा pci_dev *amd_8132 = शून्य;

		जबतक ((amd_8132 = pci_get_device(PCI_VENDOR_ID_AMD,
						  PCI_DEVICE_ID_AMD_8132_BRIDGE,
						  amd_8132))) अणु

			अगर (amd_8132->revision >= 0x10 &&
			    amd_8132->revision <= 0x13) अणु
				disable_msi = 1;
				pci_dev_put(amd_8132);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	bnx2_set_शेष_link(bp);
	bp->req_flow_ctrl = FLOW_CTRL_RX | FLOW_CTRL_TX;

	समयr_setup(&bp->समयr, bnx2_समयr, 0);
	bp->समयr.expires = RUN_AT(BNX2_TIMER_INTERVAL);

#अगर_घोषित BCM_CNIC
	अगर (bnx2_shmem_rd(bp, BNX2_ISCSI_INITIATOR) & BNX2_ISCSI_INITIATOR_EN)
		bp->cnic_eth_dev.max_iscsi_conn =
			(bnx2_shmem_rd(bp, BNX2_ISCSI_MAX_CONN) &
			 BNX2_ISCSI_MAX_CONN_MASK) >> BNX2_ISCSI_MAX_CONN_SHIFT;
	bp->cnic_probe = bnx2_cnic_probe;
#पूर्ण_अगर
	pci_save_state(pdev);

	वापस 0;

err_out_unmap:
	अगर (bp->flags & BNX2_FLAG_AER_ENABLED) अणु
		pci_disable_pcie_error_reporting(pdev);
		bp->flags &= ~BNX2_FLAG_AER_ENABLED;
	पूर्ण

	pci_iounmap(pdev, bp->regview);
	bp->regview = शून्य;

err_out_release:
	pci_release_regions(pdev);

err_out_disable:
	pci_disable_device(pdev);

err_out:
	kमुक्त(bp->temp_stats_blk);

	वापस rc;
पूर्ण

अटल अक्षर *
bnx2_bus_string(काष्ठा bnx2 *bp, अक्षर *str)
अणु
	अक्षर *s = str;

	अगर (bp->flags & BNX2_FLAG_PCIE) अणु
		s += प्र_लिखो(s, "PCI Express");
	पूर्ण अन्यथा अणु
		s += प्र_लिखो(s, "PCI");
		अगर (bp->flags & BNX2_FLAG_PCIX)
			s += प्र_लिखो(s, "-X");
		अगर (bp->flags & BNX2_FLAG_PCI_32BIT)
			s += प्र_लिखो(s, " 32-bit");
		अन्यथा
			s += प्र_लिखो(s, " 64-bit");
		s += प्र_लिखो(s, " %dMHz", bp->bus_speed_mhz);
	पूर्ण
	वापस str;
पूर्ण

अटल व्योम
bnx2_del_napi(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->irq_nvecs; i++)
		netअगर_napi_del(&bp->bnx2_napi[i].napi);
पूर्ण

अटल व्योम
bnx2_init_napi(काष्ठा bnx2 *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->irq_nvecs; i++) अणु
		काष्ठा bnx2_napi *bnapi = &bp->bnx2_napi[i];
		पूर्णांक (*poll)(काष्ठा napi_काष्ठा *, पूर्णांक);

		अगर (i == 0)
			poll = bnx2_poll;
		अन्यथा
			poll = bnx2_poll_msix;

		netअगर_napi_add(bp->dev, &bp->bnx2_napi[i].napi, poll, 64);
		bnapi->bp = bp;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops bnx2_netdev_ops = अणु
	.nकरो_खोलो		= bnx2_खोलो,
	.nकरो_start_xmit		= bnx2_start_xmit,
	.nकरो_stop		= bnx2_बंद,
	.nकरो_get_stats64	= bnx2_get_stats64,
	.nकरो_set_rx_mode	= bnx2_set_rx_mode,
	.nकरो_करो_ioctl		= bnx2_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= bnx2_change_mac_addr,
	.nकरो_change_mtu		= bnx2_change_mtu,
	.nकरो_set_features	= bnx2_set_features,
	.nकरो_tx_समयout		= bnx2_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= poll_bnx2,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक
bnx2_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा bnx2 *bp;
	पूर्णांक rc;
	अक्षर str[40];

	/* dev zeroed in init_etherdev */
	dev = alloc_etherdev_mq(माप(*bp), TX_MAX_RINGS);
	अगर (!dev)
		वापस -ENOMEM;

	rc = bnx2_init_board(pdev, dev);
	अगर (rc < 0)
		जाओ err_मुक्त;

	dev->netdev_ops = &bnx2_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	dev->ethtool_ops = &bnx2_ethtool_ops;

	bp = netdev_priv(dev);

	pci_set_drvdata(pdev, dev);

	/*
	 * In-flight DMA from 1st kernel could जारी going in kdump kernel.
	 * New io-page table has been created beक्रमe bnx2 करोes reset at खोलो stage.
	 * We have to रुको क्रम the in-flight DMA to complete to aव्योम it look up
	 * पूर्णांकo the newly created io-page table.
	 */
	अगर (is_kdump_kernel())
		bnx2_रुको_dma_complete(bp);

	स_नकल(dev->dev_addr, bp->mac_addr, ETH_ALEN);

	dev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG |
		NETIF_F_TSO | NETIF_F_TSO_ECN |
		NETIF_F_RXHASH | NETIF_F_RXCSUM;

	अगर (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		dev->hw_features |= NETIF_F_IPV6_CSUM | NETIF_F_TSO6;

	dev->vlan_features = dev->hw_features;
	dev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
	dev->features |= dev->hw_features;
	dev->priv_flags |= IFF_UNICAST_FLT;
	dev->min_mtu = MIN_ETHERNET_PACKET_SIZE;
	dev->max_mtu = MAX_ETHERNET_JUMBO_PACKET_SIZE;

	अगर (!(bp->flags & BNX2_FLAG_CAN_KEEP_VLAN))
		dev->hw_features &= ~NETIF_F_HW_VLAN_CTAG_RX;

	अगर ((rc = रेजिस्टर_netdev(dev))) अणु
		dev_err(&pdev->dev, "Cannot register net device\n");
		जाओ error;
	पूर्ण

	netdev_info(dev, "%s (%c%d) %s found at mem %lx, IRQ %d, "
		    "node addr %pM\n", board_info[ent->driver_data].name,
		    ((BNX2_CHIP_ID(bp) & 0xf000) >> 12) + 'A',
		    ((BNX2_CHIP_ID(bp) & 0x0ff0) >> 4),
		    bnx2_bus_string(bp, str), (दीर्घ)pci_resource_start(pdev, 0),
		    pdev->irq, dev->dev_addr);

	वापस 0;

error:
	pci_iounmap(pdev, bp->regview);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
err_मुक्त:
	bnx2_मुक्त_stats_blk(dev);
	मुक्त_netdev(dev);
	वापस rc;
पूर्ण

अटल व्योम
bnx2_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2 *bp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);

	del_समयr_sync(&bp->समयr);
	cancel_work_sync(&bp->reset_task);

	pci_iounmap(bp->pdev, bp->regview);

	bnx2_मुक्त_stats_blk(dev);
	kमुक्त(bp->temp_stats_blk);

	अगर (bp->flags & BNX2_FLAG_AER_ENABLED) अणु
		pci_disable_pcie_error_reporting(pdev);
		bp->flags &= ~BNX2_FLAG_AER_ENABLED;
	पूर्ण

	bnx2_release_firmware(bp);

	मुक्त_netdev(dev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक
bnx2_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (netअगर_running(dev)) अणु
		cancel_work_sync(&bp->reset_task);
		bnx2_netअगर_stop(bp, true);
		netअगर_device_detach(dev);
		del_समयr_sync(&bp->समयr);
		bnx2_shutकरोwn_chip(bp);
		__bnx2_मुक्त_irq(bp);
		bnx2_मुक्त_skbs(bp);
	पूर्ण
	bnx2_setup_wol(bp);
	वापस 0;
पूर्ण

अटल पूर्णांक
bnx2_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा bnx2 *bp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	bnx2_set_घातer_state(bp, PCI_D0);
	netअगर_device_attach(dev);
	bnx2_request_irq(bp);
	bnx2_init_nic(bp, 1);
	bnx2_netअगर_start(bp, true);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(bnx2_pm_ops, bnx2_suspend, bnx2_resume);
#घोषणा BNX2_PM_OPS (&bnx2_pm_ops)

#अन्यथा

#घोषणा BNX2_PM_OPS शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */
/**
 * bnx2_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t bnx2_io_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2 *bp = netdev_priv(dev);

	rtnl_lock();
	netअगर_device_detach(dev);

	अगर (state == pci_channel_io_perm_failure) अणु
		rtnl_unlock();
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		bnx2_netअगर_stop(bp, true);
		del_समयr_sync(&bp->समयr);
		bnx2_reset_nic(bp, BNX2_DRV_MSG_CODE_RESET);
	पूर्ण

	pci_disable_device(pdev);
	rtnl_unlock();

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * bnx2_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 */
अटल pci_ers_result_t bnx2_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2 *bp = netdev_priv(dev);
	pci_ers_result_t result = PCI_ERS_RESULT_DISCONNECT;
	पूर्णांक err = 0;

	rtnl_lock();
	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset\n");
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		pci_restore_state(pdev);
		pci_save_state(pdev);

		अगर (netअगर_running(dev))
			err = bnx2_init_nic(bp, 1);

		अगर (!err)
			result = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	अगर (result != PCI_ERS_RESULT_RECOVERED && netअगर_running(dev)) अणु
		bnx2_napi_enable(bp);
		dev_बंद(dev);
	पूर्ण
	rtnl_unlock();

	अगर (!(bp->flags & BNX2_FLAG_AER_ENABLED))
		वापस result;

	वापस result;
पूर्ण

/**
 * bnx2_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation.
 */
अटल व्योम bnx2_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2 *bp = netdev_priv(dev);

	rtnl_lock();
	अगर (netअगर_running(dev))
		bnx2_netअगर_start(bp, true);

	netअगर_device_attach(dev);
	rtnl_unlock();
पूर्ण

अटल व्योम bnx2_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2 *bp;

	अगर (!dev)
		वापस;

	bp = netdev_priv(dev);
	अगर (!bp)
		वापस;

	rtnl_lock();
	अगर (netअगर_running(dev))
		dev_बंद(bp->dev);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF)
		bnx2_set_घातer_state(bp, PCI_D3hot);

	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers bnx2_err_handler = अणु
	.error_detected	= bnx2_io_error_detected,
	.slot_reset	= bnx2_io_slot_reset,
	.resume		= bnx2_io_resume,
पूर्ण;

अटल काष्ठा pci_driver bnx2_pci_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= bnx2_pci_tbl,
	.probe		= bnx2_init_one,
	.हटाओ		= bnx2_हटाओ_one,
	.driver.pm	= BNX2_PM_OPS,
	.err_handler	= &bnx2_err_handler,
	.shutकरोwn	= bnx2_shutकरोwn,
पूर्ण;

module_pci_driver(bnx2_pci_driver);
