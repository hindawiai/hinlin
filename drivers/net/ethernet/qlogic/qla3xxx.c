<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * QLogic QLA3xxx NIC HBA Driver
 * Copyright (c)  2003-2006 QLogic Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/mempool.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/prefetch.h>

#समावेश "qla3xxx.h"

#घोषणा DRV_NAME	"qla3xxx"
#घोषणा DRV_STRING	"QLogic ISP3XXX Network Driver"
#घोषणा DRV_VERSION	"v2.03.00-k5"

अटल स्थिर अक्षर ql3xxx_driver_name[] = DRV_NAME;
अटल स्थिर अक्षर ql3xxx_driver_version[] = DRV_VERSION;

#घोषणा TIMED_OUT_MSG							\
"Timed out waiting for management port to get free before issuing command\n"

MODULE_AUTHOR("QLogic Corporation");
MODULE_DESCRIPTION("QLogic ISP3XXX Network Driver " DRV_VERSION " ");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

अटल स्थिर u32 शेष_msg
    = NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK
    | NETIF_MSG_IFUP | NETIF_MSG_IFDOWN;

अटल पूर्णांक debug = -1;		/* शेषs above */
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल पूर्णांक msi;
module_param(msi, पूर्णांक, 0);
MODULE_PARM_DESC(msi, "Turn on Message Signaled Interrupts.");

अटल स्थिर काष्ठा pci_device_id ql3xxx_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_QLOGIC, QL3022_DEVICE_ID)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_QLOGIC, QL3032_DEVICE_ID)पूर्ण,
	/* required last entry */
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ql3xxx_pci_tbl);

/*
 *  These are the known PHY's which are used
 */
क्रमागत PHY_DEVICE_TYPE अणु
   PHY_TYPE_UNKNOWN   = 0,
   PHY_VITESSE_VSC8211,
   PHY_AGERE_ET1011C,
   MAX_PHY_DEV_TYPES
पूर्ण;

काष्ठा PHY_DEVICE_INFO अणु
	स्थिर क्रमागत PHY_DEVICE_TYPE	phyDevice;
	स्थिर u32		phyIdOUI;
	स्थिर u16		phyIdModel;
	स्थिर अक्षर		*name;
पूर्ण;

अटल स्थिर काष्ठा PHY_DEVICE_INFO PHY_DEVICES[] = अणु
	अणुPHY_TYPE_UNKNOWN,    0x000000, 0x0, "PHY_TYPE_UNKNOWN"पूर्ण,
	अणुPHY_VITESSE_VSC8211, 0x0003f1, 0xb, "PHY_VITESSE_VSC8211"पूर्ण,
	अणुPHY_AGERE_ET1011C,   0x00a0bc, 0x1, "PHY_AGERE_ET1011C"पूर्ण,
पूर्ण;


/*
 * Caller must take hw_lock.
 */
अटल पूर्णांक ql_sem_spinlock(काष्ठा ql3_adapter *qdev,
			    u32 sem_mask, u32 sem_bits)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	u32 value;
	अचिन्हित पूर्णांक seconds = 3;

	करो अणु
		ग_लिखोl((sem_mask | sem_bits),
		       &port_regs->CommonRegs.semaphoreReg);
		value = पढ़ोl(&port_regs->CommonRegs.semaphoreReg);
		अगर ((value & (sem_mask >> 16)) == sem_bits)
			वापस 0;
		mdelay(1000);
	पूर्ण जबतक (--seconds);
	वापस -1;
पूर्ण

अटल व्योम ql_sem_unlock(काष्ठा ql3_adapter *qdev, u32 sem_mask)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	ग_लिखोl(sem_mask, &port_regs->CommonRegs.semaphoreReg);
	पढ़ोl(&port_regs->CommonRegs.semaphoreReg);
पूर्ण

अटल पूर्णांक ql_sem_lock(काष्ठा ql3_adapter *qdev, u32 sem_mask, u32 sem_bits)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	u32 value;

	ग_लिखोl((sem_mask | sem_bits), &port_regs->CommonRegs.semaphoreReg);
	value = पढ़ोl(&port_regs->CommonRegs.semaphoreReg);
	वापस ((value & (sem_mask >> 16)) == sem_bits);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल पूर्णांक ql_रुको_क्रम_drvr_lock(काष्ठा ql3_adapter *qdev)
अणु
	पूर्णांक i = 0;

	करो अणु
		अगर (ql_sem_lock(qdev,
				QL_DRVR_SEM_MASK,
				(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index)
				 * 2) << 1)) अणु
			netdev_prपूर्णांकk(KERN_DEBUG, qdev->ndev,
				      "driver lock acquired\n");
			वापस 1;
		पूर्ण
		ssleep(1);
	पूर्ण जबतक (++i < 10);

	netdev_err(qdev->ndev, "Timed out waiting for driver lock...\n");
	वापस 0;
पूर्ण

अटल व्योम ql_set_रेजिस्टर_page(काष्ठा ql3_adapter *qdev, u32 page)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;

	ग_लिखोl(((ISP_CONTROL_NP_MASK << 16) | page),
			&port_regs->CommonRegs.ispControlStatus);
	पढ़ोl(&port_regs->CommonRegs.ispControlStatus);
	qdev->current_page = page;
पूर्ण

अटल u32 ql_पढ़ो_common_reg_l(काष्ठा ql3_adapter *qdev, u32 __iomem *reg)
अणु
	u32 value;
	अचिन्हित दीर्घ hw_flags;

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	value = पढ़ोl(reg);
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);

	वापस value;
पूर्ण

अटल u32 ql_पढ़ो_common_reg(काष्ठा ql3_adapter *qdev, u32 __iomem *reg)
अणु
	वापस पढ़ोl(reg);
पूर्ण

अटल u32 ql_पढ़ो_page0_reg_l(काष्ठा ql3_adapter *qdev, u32 __iomem *reg)
अणु
	u32 value;
	अचिन्हित दीर्घ hw_flags;

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);

	अगर (qdev->current_page != 0)
		ql_set_रेजिस्टर_page(qdev, 0);
	value = पढ़ोl(reg);

	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	वापस value;
पूर्ण

अटल u32 ql_पढ़ो_page0_reg(काष्ठा ql3_adapter *qdev, u32 __iomem *reg)
अणु
	अगर (qdev->current_page != 0)
		ql_set_रेजिस्टर_page(qdev, 0);
	वापस पढ़ोl(reg);
पूर्ण

अटल व्योम ql_ग_लिखो_common_reg_l(काष्ठा ql3_adapter *qdev,
				u32 __iomem *reg, u32 value)
अणु
	अचिन्हित दीर्घ hw_flags;

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
पूर्ण

अटल व्योम ql_ग_लिखो_common_reg(काष्ठा ql3_adapter *qdev,
				u32 __iomem *reg, u32 value)
अणु
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
पूर्ण

अटल व्योम ql_ग_लिखो_nvram_reg(काष्ठा ql3_adapter *qdev,
				u32 __iomem *reg, u32 value)
अणु
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
	udelay(1);
पूर्ण

अटल व्योम ql_ग_लिखो_page0_reg(काष्ठा ql3_adapter *qdev,
			       u32 __iomem *reg, u32 value)
अणु
	अगर (qdev->current_page != 0)
		ql_set_रेजिस्टर_page(qdev, 0);
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
पूर्ण

/*
 * Caller holds hw_lock. Only called during init.
 */
अटल व्योम ql_ग_लिखो_page1_reg(काष्ठा ql3_adapter *qdev,
			       u32 __iomem *reg, u32 value)
अणु
	अगर (qdev->current_page != 1)
		ql_set_रेजिस्टर_page(qdev, 1);
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
पूर्ण

/*
 * Caller holds hw_lock. Only called during init.
 */
अटल व्योम ql_ग_लिखो_page2_reg(काष्ठा ql3_adapter *qdev,
			       u32 __iomem *reg, u32 value)
अणु
	अगर (qdev->current_page != 2)
		ql_set_रेजिस्टर_page(qdev, 2);
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
पूर्ण

अटल व्योम ql_disable_पूर्णांकerrupts(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;

	ql_ग_लिखो_common_reg_l(qdev, &port_regs->CommonRegs.ispInterruptMaskReg,
			    (ISP_IMR_ENABLE_INT << 16));

पूर्ण

अटल व्योम ql_enable_पूर्णांकerrupts(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;

	ql_ग_लिखो_common_reg_l(qdev, &port_regs->CommonRegs.ispInterruptMaskReg,
			    ((0xff << 16) | ISP_IMR_ENABLE_INT));

पूर्ण

अटल व्योम ql_release_to_lrg_buf_मुक्त_list(काष्ठा ql3_adapter *qdev,
					    काष्ठा ql_rcv_buf_cb *lrg_buf_cb)
अणु
	dma_addr_t map;
	पूर्णांक err;
	lrg_buf_cb->next = शून्य;

	अगर (qdev->lrg_buf_मुक्त_tail == शून्य) अणु	/* The list is empty  */
		qdev->lrg_buf_मुक्त_head = qdev->lrg_buf_मुक्त_tail = lrg_buf_cb;
	पूर्ण अन्यथा अणु
		qdev->lrg_buf_मुक्त_tail->next = lrg_buf_cb;
		qdev->lrg_buf_मुक्त_tail = lrg_buf_cb;
	पूर्ण

	अगर (!lrg_buf_cb->skb) अणु
		lrg_buf_cb->skb = netdev_alloc_skb(qdev->ndev,
						   qdev->lrg_buffer_len);
		अगर (unlikely(!lrg_buf_cb->skb)) अणु
			qdev->lrg_buf_skb_check++;
		पूर्ण अन्यथा अणु
			/*
			 * We save some space to copy the ethhdr from first
			 * buffer
			 */
			skb_reserve(lrg_buf_cb->skb, QL_HEADER_SPACE);
			map = dma_map_single(&qdev->pdev->dev,
					     lrg_buf_cb->skb->data,
					     qdev->lrg_buffer_len - QL_HEADER_SPACE,
					     DMA_FROM_DEVICE);
			err = dma_mapping_error(&qdev->pdev->dev, map);
			अगर (err) अणु
				netdev_err(qdev->ndev,
					   "PCI mapping failed with error: %d\n",
					   err);
				dev_kमुक्त_skb(lrg_buf_cb->skb);
				lrg_buf_cb->skb = शून्य;

				qdev->lrg_buf_skb_check++;
				वापस;
			पूर्ण

			lrg_buf_cb->buf_phy_addr_low =
			    cpu_to_le32(LS_64BITS(map));
			lrg_buf_cb->buf_phy_addr_high =
			    cpu_to_le32(MS_64BITS(map));
			dma_unmap_addr_set(lrg_buf_cb, mapaddr, map);
			dma_unmap_len_set(lrg_buf_cb, maplen,
					  qdev->lrg_buffer_len -
					  QL_HEADER_SPACE);
		पूर्ण
	पूर्ण

	qdev->lrg_buf_मुक्त_count++;
पूर्ण

अटल काष्ठा ql_rcv_buf_cb *ql_get_from_lrg_buf_मुक्त_list(काष्ठा ql3_adapter
							   *qdev)
अणु
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb = qdev->lrg_buf_मुक्त_head;

	अगर (lrg_buf_cb != शून्य) अणु
		qdev->lrg_buf_मुक्त_head = lrg_buf_cb->next;
		अगर (qdev->lrg_buf_मुक्त_head == शून्य)
			qdev->lrg_buf_मुक्त_tail = शून्य;
		qdev->lrg_buf_मुक्त_count--;
	पूर्ण

	वापस lrg_buf_cb;
पूर्ण

अटल u32 addrBits = EEPROM_NO_ADDR_BITS;
अटल u32 dataBits = EEPROM_NO_DATA_BITS;

अटल व्योम fm93c56a_deselect(काष्ठा ql3_adapter *qdev);
अटल व्योम eeprom_पढ़ोword(काष्ठा ql3_adapter *qdev, u32 eepromAddr,
			    अचिन्हित लघु *value);

/*
 * Caller holds hw_lock.
 */
अटल व्योम fm93c56a_select(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	__iomem u32 *spir = &port_regs->CommonRegs.serialPortInterfaceReg;

	qdev->eeprom_cmd_data = AUBURN_EEPROM_CS_1;
	ql_ग_लिखो_nvram_reg(qdev, spir, ISP_NVRAM_MASK | qdev->eeprom_cmd_data);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम fm93c56a_cmd(काष्ठा ql3_adapter *qdev, u32 cmd, u32 eepromAddr)
अणु
	पूर्णांक i;
	u32 mask;
	u32 dataBit;
	u32 previousBit;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	__iomem u32 *spir = &port_regs->CommonRegs.serialPortInterfaceReg;

	/* Clock in a zero, then करो the start bit */
	ql_ग_लिखो_nvram_reg(qdev, spir,
			   (ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
			    AUBURN_EEPROM_DO_1));
	ql_ग_लिखो_nvram_reg(qdev, spir,
			   (ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
			    AUBURN_EEPROM_DO_1 | AUBURN_EEPROM_CLK_RISE));
	ql_ग_लिखो_nvram_reg(qdev, spir,
			   (ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
			    AUBURN_EEPROM_DO_1 | AUBURN_EEPROM_CLK_FALL));

	mask = 1 << (FM93C56A_CMD_BITS - 1);
	/* Force the previous data bit to be dअगरferent */
	previousBit = 0xffff;
	क्रम (i = 0; i < FM93C56A_CMD_BITS; i++) अणु
		dataBit = (cmd & mask)
			? AUBURN_EEPROM_DO_1
			: AUBURN_EEPROM_DO_0;
		अगर (previousBit != dataBit) अणु
			/* If the bit changed, change the DO state to match */
			ql_ग_लिखो_nvram_reg(qdev, spir,
					   (ISP_NVRAM_MASK |
					    qdev->eeprom_cmd_data | dataBit));
			previousBit = dataBit;
		पूर्ण
		ql_ग_लिखो_nvram_reg(qdev, spir,
				   (ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
				    dataBit | AUBURN_EEPROM_CLK_RISE));
		ql_ग_लिखो_nvram_reg(qdev, spir,
				   (ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
				    dataBit | AUBURN_EEPROM_CLK_FALL));
		cmd = cmd << 1;
	पूर्ण

	mask = 1 << (addrBits - 1);
	/* Force the previous data bit to be dअगरferent */
	previousBit = 0xffff;
	क्रम (i = 0; i < addrBits; i++) अणु
		dataBit = (eepromAddr & mask) ? AUBURN_EEPROM_DO_1
			: AUBURN_EEPROM_DO_0;
		अगर (previousBit != dataBit) अणु
			/*
			 * If the bit changed, then change the DO state to
			 * match
			 */
			ql_ग_लिखो_nvram_reg(qdev, spir,
					   (ISP_NVRAM_MASK |
					    qdev->eeprom_cmd_data | dataBit));
			previousBit = dataBit;
		पूर्ण
		ql_ग_लिखो_nvram_reg(qdev, spir,
				   (ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
				    dataBit | AUBURN_EEPROM_CLK_RISE));
		ql_ग_लिखो_nvram_reg(qdev, spir,
				   (ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
				    dataBit | AUBURN_EEPROM_CLK_FALL));
		eepromAddr = eepromAddr << 1;
	पूर्ण
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम fm93c56a_deselect(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	__iomem u32 *spir = &port_regs->CommonRegs.serialPortInterfaceReg;

	qdev->eeprom_cmd_data = AUBURN_EEPROM_CS_0;
	ql_ग_लिखो_nvram_reg(qdev, spir, ISP_NVRAM_MASK | qdev->eeprom_cmd_data);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम fm93c56a_datain(काष्ठा ql3_adapter *qdev, अचिन्हित लघु *value)
अणु
	पूर्णांक i;
	u32 data = 0;
	u32 dataBit;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	__iomem u32 *spir = &port_regs->CommonRegs.serialPortInterfaceReg;

	/* Read the data bits */
	/* The first bit is a dummy.  Clock right over it. */
	क्रम (i = 0; i < dataBits; i++) अणु
		ql_ग_लिखो_nvram_reg(qdev, spir,
				   ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
				   AUBURN_EEPROM_CLK_RISE);
		ql_ग_लिखो_nvram_reg(qdev, spir,
				   ISP_NVRAM_MASK | qdev->eeprom_cmd_data |
				   AUBURN_EEPROM_CLK_FALL);
		dataBit = (ql_पढ़ो_common_reg(qdev, spir) &
			   AUBURN_EEPROM_DI_1) ? 1 : 0;
		data = (data << 1) | dataBit;
	पूर्ण
	*value = (u16)data;
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम eeprom_पढ़ोword(काष्ठा ql3_adapter *qdev,
			    u32 eepromAddr, अचिन्हित लघु *value)
अणु
	fm93c56a_select(qdev);
	fm93c56a_cmd(qdev, (पूर्णांक)FM93C56A_READ, eepromAddr);
	fm93c56a_datain(qdev, value);
	fm93c56a_deselect(qdev);
पूर्ण

अटल व्योम ql_set_mac_addr(काष्ठा net_device *ndev, u16 *addr)
अणु
	__le16 *p = (__le16 *)ndev->dev_addr;
	p[0] = cpu_to_le16(addr[0]);
	p[1] = cpu_to_le16(addr[1]);
	p[2] = cpu_to_le16(addr[2]);
पूर्ण

अटल पूर्णांक ql_get_nvram_params(काष्ठा ql3_adapter *qdev)
अणु
	u16 *pEEPROMData;
	u16 checksum = 0;
	u32 index;
	अचिन्हित दीर्घ hw_flags;

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);

	pEEPROMData = (u16 *)&qdev->nvram_data;
	qdev->eeprom_cmd_data = 0;
	अगर (ql_sem_spinlock(qdev, QL_NVRAM_SEM_MASK,
			(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 10)) अणु
		pr_err("%s: Failed ql_sem_spinlock()\n", __func__);
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
		वापस -1;
	पूर्ण

	क्रम (index = 0; index < EEPROM_SIZE; index++) अणु
		eeprom_पढ़ोword(qdev, index, pEEPROMData);
		checksum += *pEEPROMData;
		pEEPROMData++;
	पूर्ण
	ql_sem_unlock(qdev, QL_NVRAM_SEM_MASK);

	अगर (checksum != 0) अणु
		netdev_err(qdev->ndev, "checksum should be zero, is %x!!\n",
			   checksum);
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
		वापस -1;
	पूर्ण

	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	वापस checksum;
पूर्ण

अटल स्थिर u32 PHYAddr[2] = अणु
	PORT0_PHY_ADDRESS, PORT1_PHY_ADDRESS
पूर्ण;

अटल पूर्णांक ql_रुको_क्रम_mii_पढ़ोy(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 temp;
	पूर्णांक count = 1000;

	जबतक (count) अणु
		temp = ql_पढ़ो_page0_reg(qdev, &port_regs->macMIIStatusReg);
		अगर (!(temp & MAC_MII_STATUS_BSY))
			वापस 0;
		udelay(10);
		count--;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम ql_mii_enable_scan_mode(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 scanControl;

	अगर (qdev->numPorts > 1) अणु
		/* Auto scan will cycle through multiple ports */
		scanControl = MAC_MII_CONTROL_AS | MAC_MII_CONTROL_SC;
	पूर्ण अन्यथा अणु
		scanControl = MAC_MII_CONTROL_SC;
	पूर्ण

	/*
	 * Scan रेजिस्टर 1 of PHY/PETBI,
	 * Set up to scan both devices
	 * The स्वतःscan starts from the first रेजिस्टर, completes
	 * the last one beक्रमe rolling over to the first
	 */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtAddrReg,
			   PHYAddr[0] | MII_SCAN_REGISTER);

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg,
			   (scanControl) |
			   ((MAC_MII_CONTROL_SC | MAC_MII_CONTROL_AS) << 16));
पूर्ण

अटल u8 ql_mii_disable_scan_mode(काष्ठा ql3_adapter *qdev)
अणु
	u8 ret;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
					qdev->mem_map_रेजिस्टरs;

	/* See अगर scan mode is enabled beक्रमe we turn it off */
	अगर (ql_पढ़ो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg) &
	    (MAC_MII_CONTROL_AS | MAC_MII_CONTROL_SC)) अणु
		/* Scan is enabled */
		ret = 1;
	पूर्ण अन्यथा अणु
		/* Scan is disabled */
		ret = 0;
	पूर्ण

	/*
	 * When disabling scan mode you must first change the MII रेजिस्टर
	 * address
	 */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtAddrReg,
			   PHYAddr[0] | MII_SCAN_REGISTER);

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg,
			   ((MAC_MII_CONTROL_SC | MAC_MII_CONTROL_AS |
			     MAC_MII_CONTROL_RC) << 16));

	वापस ret;
पूर्ण

अटल पूर्णांक ql_mii_ग_लिखो_reg_ex(काष्ठा ql3_adapter *qdev,
			       u16 regAddr, u16 value, u32 phyAddr)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u8 scanWasEnabled;

	scanWasEnabled = ql_mii_disable_scan_mode(qdev);

	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtAddrReg,
			   phyAddr | regAddr);

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtDataReg, value);

	/* Wait क्रम ग_लिखो to complete 9/10/04 SJP */
	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	अगर (scanWasEnabled)
		ql_mii_enable_scan_mode(qdev);

	वापस 0;
पूर्ण

अटल पूर्णांक ql_mii_पढ़ो_reg_ex(काष्ठा ql3_adapter *qdev, u16 regAddr,
			      u16 *value, u32 phyAddr)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u8 scanWasEnabled;
	u32 temp;

	scanWasEnabled = ql_mii_disable_scan_mode(qdev);

	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtAddrReg,
			   phyAddr | regAddr);

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg,
			   (MAC_MII_CONTROL_RC << 16));

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg,
			   (MAC_MII_CONTROL_RC << 16) | MAC_MII_CONTROL_RC);

	/* Wait क्रम the पढ़ो to complete */
	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	temp = ql_पढ़ो_page0_reg(qdev, &port_regs->macMIIMgmtDataReg);
	*value = (u16) temp;

	अगर (scanWasEnabled)
		ql_mii_enable_scan_mode(qdev);

	वापस 0;
पूर्ण

अटल पूर्णांक ql_mii_ग_लिखो_reg(काष्ठा ql3_adapter *qdev, u16 regAddr, u16 value)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;

	ql_mii_disable_scan_mode(qdev);

	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtAddrReg,
			   qdev->PHYAddr | regAddr);

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtDataReg, value);

	/* Wait क्रम ग_लिखो to complete. */
	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	ql_mii_enable_scan_mode(qdev);

	वापस 0;
पूर्ण

अटल पूर्णांक ql_mii_पढ़ो_reg(काष्ठा ql3_adapter *qdev, u16 regAddr, u16 *value)
अणु
	u32 temp;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;

	ql_mii_disable_scan_mode(qdev);

	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtAddrReg,
			   qdev->PHYAddr | regAddr);

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg,
			   (MAC_MII_CONTROL_RC << 16));

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg,
			   (MAC_MII_CONTROL_RC << 16) | MAC_MII_CONTROL_RC);

	/* Wait क्रम the पढ़ो to complete */
	अगर (ql_रुको_क्रम_mii_पढ़ोy(qdev)) अणु
		netअगर_warn(qdev, link, qdev->ndev, TIMED_OUT_MSG);
		वापस -1;
	पूर्ण

	temp = ql_पढ़ो_page0_reg(qdev, &port_regs->macMIIMgmtDataReg);
	*value = (u16) temp;

	ql_mii_enable_scan_mode(qdev);

	वापस 0;
पूर्ण

अटल व्योम ql_petbi_reset(काष्ठा ql3_adapter *qdev)
अणु
	ql_mii_ग_लिखो_reg(qdev, PETBI_CONTROL_REG, PETBI_CTRL_SOFT_RESET);
पूर्ण

अटल व्योम ql_petbi_start_neg(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;

	/* Enable Auto-negotiation sense */
	ql_mii_पढ़ो_reg(qdev, PETBI_TBI_CTRL, &reg);
	reg |= PETBI_TBI_AUTO_SENSE;
	ql_mii_ग_लिखो_reg(qdev, PETBI_TBI_CTRL, reg);

	ql_mii_ग_लिखो_reg(qdev, PETBI_NEG_ADVER,
			 PETBI_NEG_PAUSE | PETBI_NEG_DUPLEX);

	ql_mii_ग_लिखो_reg(qdev, PETBI_CONTROL_REG,
			 PETBI_CTRL_AUTO_NEG | PETBI_CTRL_RESTART_NEG |
			 PETBI_CTRL_FULL_DUPLEX | PETBI_CTRL_SPEED_1000);

पूर्ण

अटल व्योम ql_petbi_reset_ex(काष्ठा ql3_adapter *qdev)
अणु
	ql_mii_ग_लिखो_reg_ex(qdev, PETBI_CONTROL_REG, PETBI_CTRL_SOFT_RESET,
			    PHYAddr[qdev->mac_index]);
पूर्ण

अटल व्योम ql_petbi_start_neg_ex(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;

	/* Enable Auto-negotiation sense */
	ql_mii_पढ़ो_reg_ex(qdev, PETBI_TBI_CTRL, &reg,
			   PHYAddr[qdev->mac_index]);
	reg |= PETBI_TBI_AUTO_SENSE;
	ql_mii_ग_लिखो_reg_ex(qdev, PETBI_TBI_CTRL, reg,
			    PHYAddr[qdev->mac_index]);

	ql_mii_ग_लिखो_reg_ex(qdev, PETBI_NEG_ADVER,
			    PETBI_NEG_PAUSE | PETBI_NEG_DUPLEX,
			    PHYAddr[qdev->mac_index]);

	ql_mii_ग_लिखो_reg_ex(qdev, PETBI_CONTROL_REG,
			    PETBI_CTRL_AUTO_NEG | PETBI_CTRL_RESTART_NEG |
			    PETBI_CTRL_FULL_DUPLEX | PETBI_CTRL_SPEED_1000,
			    PHYAddr[qdev->mac_index]);
पूर्ण

अटल व्योम ql_petbi_init(काष्ठा ql3_adapter *qdev)
अणु
	ql_petbi_reset(qdev);
	ql_petbi_start_neg(qdev);
पूर्ण

अटल व्योम ql_petbi_init_ex(काष्ठा ql3_adapter *qdev)
अणु
	ql_petbi_reset_ex(qdev);
	ql_petbi_start_neg_ex(qdev);
पूर्ण

अटल पूर्णांक ql_is_petbi_neg_छोड़ो(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;

	अगर (ql_mii_पढ़ो_reg(qdev, PETBI_NEG_PARTNER, &reg) < 0)
		वापस 0;

	वापस (reg & PETBI_NEG_PAUSE_MASK) == PETBI_NEG_PAUSE;
पूर्ण

अटल व्योम phyAgereSpecअगरicInit(काष्ठा ql3_adapter *qdev, u32 miiAddr)
अणु
	netdev_info(qdev->ndev, "enabling Agere specific PHY\n");
	/* घातer करोwn device bit 11 = 1 */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x00, 0x1940, miiAddr);
	/* enable diagnostic mode bit 2 = 1 */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x12, 0x840e, miiAddr);
	/* 1000MB amplitude adjust (see Agere errata) */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x10, 0x8805, miiAddr);
	/* 1000MB amplitude adjust (see Agere errata) */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x11, 0xf03e, miiAddr);
	/* 100MB amplitude adjust (see Agere errata) */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x10, 0x8806, miiAddr);
	/* 100MB amplitude adjust (see Agere errata) */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x11, 0x003e, miiAddr);
	/* 10MB amplitude adjust (see Agere errata) */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x10, 0x8807, miiAddr);
	/* 10MB amplitude adjust (see Agere errata) */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x11, 0x1f00, miiAddr);
	/* poपूर्णांक to hidden reg 0x2806 */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x10, 0x2806, miiAddr);
	/* Write new PHYAD w/bit 5 set */
	ql_mii_ग_लिखो_reg_ex(qdev, 0x11,
			    0x0020 | (PHYAddr[qdev->mac_index] >> 8), miiAddr);
	/*
	 * Disable diagnostic mode bit 2 = 0
	 * Power up device bit 11 = 0
	 * Link up (on) and activity (blink)
	 */
	ql_mii_ग_लिखो_reg(qdev, 0x12, 0x840a);
	ql_mii_ग_लिखो_reg(qdev, 0x00, 0x1140);
	ql_mii_ग_लिखो_reg(qdev, 0x1c, 0xfaf0);
पूर्ण

अटल क्रमागत PHY_DEVICE_TYPE getPhyType(काष्ठा ql3_adapter *qdev,
				       u16 phyIdReg0, u16 phyIdReg1)
अणु
	क्रमागत PHY_DEVICE_TYPE result = PHY_TYPE_UNKNOWN;
	u32   oui;
	u16   model;
	पूर्णांक i;

	अगर (phyIdReg0 == 0xffff)
		वापस result;

	अगर (phyIdReg1 == 0xffff)
		वापस result;

	/* oui is split between two रेजिस्टरs */
	oui = (phyIdReg0 << 6) | ((phyIdReg1 & PHY_OUI_1_MASK) >> 10);

	model = (phyIdReg1 & PHY_MODEL_MASK) >> 4;

	/* Scan table क्रम this PHY */
	क्रम (i = 0; i < MAX_PHY_DEV_TYPES; i++) अणु
		अगर ((oui == PHY_DEVICES[i].phyIdOUI) &&
		    (model == PHY_DEVICES[i].phyIdModel)) अणु
			netdev_info(qdev->ndev, "Phy: %s\n",
				    PHY_DEVICES[i].name);
			result = PHY_DEVICES[i].phyDevice;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक ql_phy_get_speed(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;

	चयन (qdev->phyType) अणु
	हाल PHY_AGERE_ET1011C: अणु
		अगर (ql_mii_पढ़ो_reg(qdev, 0x1A, &reg) < 0)
			वापस 0;

		reg = (reg >> 8) & 3;
		अवरोध;
	पूर्ण
	शेष:
		अगर (ql_mii_पढ़ो_reg(qdev, AUX_CONTROL_STATUS, &reg) < 0)
			वापस 0;

		reg = (((reg & 0x18) >> 3) & 3);
	पूर्ण

	चयन (reg) अणु
	हाल 2:
		वापस SPEED_1000;
	हाल 1:
		वापस SPEED_100;
	हाल 0:
		वापस SPEED_10;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक ql_is_full_dup(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;

	चयन (qdev->phyType) अणु
	हाल PHY_AGERE_ET1011C: अणु
		अगर (ql_mii_पढ़ो_reg(qdev, 0x1A, &reg))
			वापस 0;

		वापस ((reg & 0x0080) && (reg & 0x1000)) != 0;
	पूर्ण
	हाल PHY_VITESSE_VSC8211:
	शेष: अणु
		अगर (ql_mii_पढ़ो_reg(qdev, AUX_CONTROL_STATUS, &reg) < 0)
			वापस 0;
		वापस (reg & PHY_AUX_DUPLEX_STAT) != 0;
	पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ql_is_phy_neg_छोड़ो(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;

	अगर (ql_mii_पढ़ो_reg(qdev, PHY_NEG_PARTNER, &reg) < 0)
		वापस 0;

	वापस (reg & PHY_NEG_PAUSE) != 0;
पूर्ण

अटल पूर्णांक PHY_Setup(काष्ठा ql3_adapter *qdev)
अणु
	u16   reg1;
	u16   reg2;
	bool  agereAddrChangeNeeded = false;
	u32 miiAddr = 0;
	पूर्णांक err;

	/*  Determine the PHY we are using by पढ़ोing the ID's */
	err = ql_mii_पढ़ो_reg(qdev, PHY_ID_0_REG, &reg1);
	अगर (err != 0) अणु
		netdev_err(qdev->ndev, "Could not read from reg PHY_ID_0_REG\n");
		वापस err;
	पूर्ण

	err = ql_mii_पढ़ो_reg(qdev, PHY_ID_1_REG, &reg2);
	अगर (err != 0) अणु
		netdev_err(qdev->ndev, "Could not read from reg PHY_ID_1_REG\n");
		वापस err;
	पूर्ण

	/*  Check अगर we have a Agere PHY */
	अगर ((reg1 == 0xffff) || (reg2 == 0xffff)) अणु

		/* Determine which MII address we should be using
		   determined by the index of the card */
		अगर (qdev->mac_index == 0)
			miiAddr = MII_AGERE_ADDR_1;
		अन्यथा
			miiAddr = MII_AGERE_ADDR_2;

		err = ql_mii_पढ़ो_reg_ex(qdev, PHY_ID_0_REG, &reg1, miiAddr);
		अगर (err != 0) अणु
			netdev_err(qdev->ndev,
				   "Could not read from reg PHY_ID_0_REG after Agere detected\n");
			वापस err;
		पूर्ण

		err = ql_mii_पढ़ो_reg_ex(qdev, PHY_ID_1_REG, &reg2, miiAddr);
		अगर (err != 0) अणु
			netdev_err(qdev->ndev, "Could not read from reg PHY_ID_1_REG after Agere detected\n");
			वापस err;
		पूर्ण

		/*  We need to remember to initialize the Agere PHY */
		agereAddrChangeNeeded = true;
	पूर्ण

	/*  Determine the particular PHY we have on board to apply
	    PHY specअगरic initializations */
	qdev->phyType = getPhyType(qdev, reg1, reg2);

	अगर ((qdev->phyType == PHY_AGERE_ET1011C) && agereAddrChangeNeeded) अणु
		/* need this here so address माला_लो changed */
		phyAgereSpecअगरicInit(qdev, miiAddr);
	पूर्ण अन्यथा अगर (qdev->phyType == PHY_TYPE_UNKNOWN) अणु
		netdev_err(qdev->ndev, "PHY is unknown\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम ql_mac_enable(काष्ठा ql3_adapter *qdev, u32 enable)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 value;

	अगर (enable)
		value = (MAC_CONFIG_REG_PE | (MAC_CONFIG_REG_PE << 16));
	अन्यथा
		value = (MAC_CONFIG_REG_PE << 16);

	अगर (qdev->mac_index)
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac1ConfigReg, value);
	अन्यथा
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac0ConfigReg, value);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम ql_mac_cfg_soft_reset(काष्ठा ql3_adapter *qdev, u32 enable)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 value;

	अगर (enable)
		value = (MAC_CONFIG_REG_SR | (MAC_CONFIG_REG_SR << 16));
	अन्यथा
		value = (MAC_CONFIG_REG_SR << 16);

	अगर (qdev->mac_index)
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac1ConfigReg, value);
	अन्यथा
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac0ConfigReg, value);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम ql_mac_cfg_gig(काष्ठा ql3_adapter *qdev, u32 enable)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 value;

	अगर (enable)
		value = (MAC_CONFIG_REG_GM | (MAC_CONFIG_REG_GM << 16));
	अन्यथा
		value = (MAC_CONFIG_REG_GM << 16);

	अगर (qdev->mac_index)
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac1ConfigReg, value);
	अन्यथा
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac0ConfigReg, value);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम ql_mac_cfg_full_dup(काष्ठा ql3_adapter *qdev, u32 enable)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 value;

	अगर (enable)
		value = (MAC_CONFIG_REG_FD | (MAC_CONFIG_REG_FD << 16));
	अन्यथा
		value = (MAC_CONFIG_REG_FD << 16);

	अगर (qdev->mac_index)
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac1ConfigReg, value);
	अन्यथा
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac0ConfigReg, value);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम ql_mac_cfg_छोड़ो(काष्ठा ql3_adapter *qdev, u32 enable)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 value;

	अगर (enable)
		value =
		    ((MAC_CONFIG_REG_TF | MAC_CONFIG_REG_RF) |
		     ((MAC_CONFIG_REG_TF | MAC_CONFIG_REG_RF) << 16));
	अन्यथा
		value = ((MAC_CONFIG_REG_TF | MAC_CONFIG_REG_RF) << 16);

	अगर (qdev->mac_index)
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac1ConfigReg, value);
	अन्यथा
		ql_ग_लिखो_page0_reg(qdev, &port_regs->mac0ConfigReg, value);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल पूर्णांक ql_is_fiber(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 bitToCheck = 0;
	u32 temp;

	चयन (qdev->mac_index) अणु
	हाल 0:
		bitToCheck = PORT_STATUS_SM0;
		अवरोध;
	हाल 1:
		bitToCheck = PORT_STATUS_SM1;
		अवरोध;
	पूर्ण

	temp = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
	वापस (temp & bitToCheck) != 0;
पूर्ण

अटल पूर्णांक ql_is_स्वतः_cfg(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;
	ql_mii_पढ़ो_reg(qdev, 0x00, &reg);
	वापस (reg & 0x1000) != 0;
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल पूर्णांक ql_is_स्वतः_neg_complete(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 bitToCheck = 0;
	u32 temp;

	चयन (qdev->mac_index) अणु
	हाल 0:
		bitToCheck = PORT_STATUS_AC0;
		अवरोध;
	हाल 1:
		bitToCheck = PORT_STATUS_AC1;
		अवरोध;
	पूर्ण

	temp = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
	अगर (temp & bitToCheck) अणु
		netअगर_info(qdev, link, qdev->ndev, "Auto-Negotiate complete\n");
		वापस 1;
	पूर्ण
	netअगर_info(qdev, link, qdev->ndev, "Auto-Negotiate incomplete\n");
	वापस 0;
पूर्ण

/*
 *  ql_is_neg_छोड़ो() वापसs 1 अगर छोड़ो was negotiated to be on
 */
अटल पूर्णांक ql_is_neg_छोड़ो(काष्ठा ql3_adapter *qdev)
अणु
	अगर (ql_is_fiber(qdev))
		वापस ql_is_petbi_neg_छोड़ो(qdev);
	अन्यथा
		वापस ql_is_phy_neg_छोड़ो(qdev);
पूर्ण

अटल पूर्णांक ql_स्वतः_neg_error(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 bitToCheck = 0;
	u32 temp;

	चयन (qdev->mac_index) अणु
	हाल 0:
		bitToCheck = PORT_STATUS_AE0;
		अवरोध;
	हाल 1:
		bitToCheck = PORT_STATUS_AE1;
		अवरोध;
	पूर्ण
	temp = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
	वापस (temp & bitToCheck) != 0;
पूर्ण

अटल u32 ql_get_link_speed(काष्ठा ql3_adapter *qdev)
अणु
	अगर (ql_is_fiber(qdev))
		वापस SPEED_1000;
	अन्यथा
		वापस ql_phy_get_speed(qdev);
पूर्ण

अटल पूर्णांक ql_is_link_full_dup(काष्ठा ql3_adapter *qdev)
अणु
	अगर (ql_is_fiber(qdev))
		वापस 1;
	अन्यथा
		वापस ql_is_full_dup(qdev);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल पूर्णांक ql_link_करोwn_detect(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 bitToCheck = 0;
	u32 temp;

	चयन (qdev->mac_index) अणु
	हाल 0:
		bitToCheck = ISP_CONTROL_LINK_DN_0;
		अवरोध;
	हाल 1:
		bitToCheck = ISP_CONTROL_LINK_DN_1;
		अवरोध;
	पूर्ण

	temp =
	    ql_पढ़ो_common_reg(qdev, &port_regs->CommonRegs.ispControlStatus);
	वापस (temp & bitToCheck) != 0;
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल पूर्णांक ql_link_करोwn_detect_clear(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;

	चयन (qdev->mac_index) अणु
	हाल 0:
		ql_ग_लिखो_common_reg(qdev,
				    &port_regs->CommonRegs.ispControlStatus,
				    (ISP_CONTROL_LINK_DN_0) |
				    (ISP_CONTROL_LINK_DN_0 << 16));
		अवरोध;

	हाल 1:
		ql_ग_लिखो_common_reg(qdev,
				    &port_regs->CommonRegs.ispControlStatus,
				    (ISP_CONTROL_LINK_DN_1) |
				    (ISP_CONTROL_LINK_DN_1 << 16));
		अवरोध;

	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल पूर्णांक ql_this_adapter_controls_port(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 bitToCheck = 0;
	u32 temp;

	चयन (qdev->mac_index) अणु
	हाल 0:
		bitToCheck = PORT_STATUS_F1_ENABLED;
		अवरोध;
	हाल 1:
		bitToCheck = PORT_STATUS_F3_ENABLED;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	temp = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
	अगर (temp & bitToCheck) अणु
		netअगर_prपूर्णांकk(qdev, link, KERN_DEBUG, qdev->ndev,
			     "not link master\n");
		वापस 0;
	पूर्ण

	netअगर_prपूर्णांकk(qdev, link, KERN_DEBUG, qdev->ndev, "link master\n");
	वापस 1;
पूर्ण

अटल व्योम ql_phy_reset_ex(काष्ठा ql3_adapter *qdev)
अणु
	ql_mii_ग_लिखो_reg_ex(qdev, CONTROL_REG, PHY_CTRL_SOFT_RESET,
			    PHYAddr[qdev->mac_index]);
पूर्ण

अटल व्योम ql_phy_start_neg_ex(काष्ठा ql3_adapter *qdev)
अणु
	u16 reg;
	u16 portConfiguration;

	अगर (qdev->phyType == PHY_AGERE_ET1011C)
		ql_mii_ग_लिखो_reg(qdev, 0x13, 0x0000);
					/* turn off बाह्यal loopback */

	अगर (qdev->mac_index == 0)
		portConfiguration =
			qdev->nvram_data.macCfg_port0.portConfiguration;
	अन्यथा
		portConfiguration =
			qdev->nvram_data.macCfg_port1.portConfiguration;

	/*  Some HBA's in the field are set to 0 and they need to
	    be reपूर्णांकerpreted with a शेष value */
	अगर (portConfiguration == 0)
		portConfiguration = PORT_CONFIG_DEFAULT;

	/* Set the 1000 advertisements */
	ql_mii_पढ़ो_reg_ex(qdev, PHY_GIG_CONTROL, &reg,
			   PHYAddr[qdev->mac_index]);
	reg &= ~PHY_GIG_ALL_PARAMS;

	अगर (portConfiguration & PORT_CONFIG_1000MB_SPEED) अणु
		अगर (portConfiguration & PORT_CONFIG_FULL_DUPLEX_ENABLED)
			reg |= PHY_GIG_ADV_1000F;
		अन्यथा
			reg |= PHY_GIG_ADV_1000H;
	पूर्ण

	ql_mii_ग_लिखो_reg_ex(qdev, PHY_GIG_CONTROL, reg,
			    PHYAddr[qdev->mac_index]);

	/* Set the 10/100 & छोड़ो negotiation advertisements */
	ql_mii_पढ़ो_reg_ex(qdev, PHY_NEG_ADVER, &reg,
			   PHYAddr[qdev->mac_index]);
	reg &= ~PHY_NEG_ALL_PARAMS;

	अगर (portConfiguration & PORT_CONFIG_SYM_PAUSE_ENABLED)
		reg |= PHY_NEG_ASY_PAUSE | PHY_NEG_SYM_PAUSE;

	अगर (portConfiguration & PORT_CONFIG_FULL_DUPLEX_ENABLED) अणु
		अगर (portConfiguration & PORT_CONFIG_100MB_SPEED)
			reg |= PHY_NEG_ADV_100F;

		अगर (portConfiguration & PORT_CONFIG_10MB_SPEED)
			reg |= PHY_NEG_ADV_10F;
	पूर्ण

	अगर (portConfiguration & PORT_CONFIG_HALF_DUPLEX_ENABLED) अणु
		अगर (portConfiguration & PORT_CONFIG_100MB_SPEED)
			reg |= PHY_NEG_ADV_100H;

		अगर (portConfiguration & PORT_CONFIG_10MB_SPEED)
			reg |= PHY_NEG_ADV_10H;
	पूर्ण

	अगर (portConfiguration & PORT_CONFIG_1000MB_SPEED)
		reg |= 1;

	ql_mii_ग_लिखो_reg_ex(qdev, PHY_NEG_ADVER, reg,
			    PHYAddr[qdev->mac_index]);

	ql_mii_पढ़ो_reg_ex(qdev, CONTROL_REG, &reg, PHYAddr[qdev->mac_index]);

	ql_mii_ग_लिखो_reg_ex(qdev, CONTROL_REG,
			    reg | PHY_CTRL_RESTART_NEG | PHY_CTRL_AUTO_NEG,
			    PHYAddr[qdev->mac_index]);
पूर्ण

अटल व्योम ql_phy_init_ex(काष्ठा ql3_adapter *qdev)
अणु
	ql_phy_reset_ex(qdev);
	PHY_Setup(qdev);
	ql_phy_start_neg_ex(qdev);
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल u32 ql_get_link_state(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	u32 bitToCheck = 0;
	u32 temp, linkState;

	चयन (qdev->mac_index) अणु
	हाल 0:
		bitToCheck = PORT_STATUS_UP0;
		अवरोध;
	हाल 1:
		bitToCheck = PORT_STATUS_UP1;
		अवरोध;
	पूर्ण

	temp = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
	अगर (temp & bitToCheck)
		linkState = LS_UP;
	अन्यथा
		linkState = LS_DOWN;

	वापस linkState;
पूर्ण

अटल पूर्णांक ql_port_start(काष्ठा ql3_adapter *qdev)
अणु
	अगर (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
		(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 7)) अणु
		netdev_err(qdev->ndev, "Could not get hw lock for GIO\n");
		वापस -1;
	पूर्ण

	अगर (ql_is_fiber(qdev)) अणु
		ql_petbi_init(qdev);
	पूर्ण अन्यथा अणु
		/* Copper port */
		ql_phy_init_ex(qdev);
	पूर्ण

	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	वापस 0;
पूर्ण

अटल पूर्णांक ql_finish_स्वतः_neg(काष्ठा ql3_adapter *qdev)
अणु

	अगर (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
		(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 7))
		वापस -1;

	अगर (!ql_स्वतः_neg_error(qdev)) अणु
		अगर (test_bit(QL_LINK_MASTER, &qdev->flags)) अणु
			/* configure the MAC */
			netअगर_prपूर्णांकk(qdev, link, KERN_DEBUG, qdev->ndev,
				     "Configuring link\n");
			ql_mac_cfg_soft_reset(qdev, 1);
			ql_mac_cfg_gig(qdev,
				       (ql_get_link_speed
					(qdev) ==
					SPEED_1000));
			ql_mac_cfg_full_dup(qdev,
					    ql_is_link_full_dup
					    (qdev));
			ql_mac_cfg_छोड़ो(qdev,
					 ql_is_neg_छोड़ो
					 (qdev));
			ql_mac_cfg_soft_reset(qdev, 0);

			/* enable the MAC */
			netअगर_prपूर्णांकk(qdev, link, KERN_DEBUG, qdev->ndev,
				     "Enabling mac\n");
			ql_mac_enable(qdev, 1);
		पूर्ण

		qdev->port_link_state = LS_UP;
		netअगर_start_queue(qdev->ndev);
		netअगर_carrier_on(qdev->ndev);
		netअगर_info(qdev, link, qdev->ndev,
			   "Link is up at %d Mbps, %s duplex\n",
			   ql_get_link_speed(qdev),
			   ql_is_link_full_dup(qdev) ? "full" : "half");

	पूर्ण अन्यथा अणु	/* Remote error detected */

		अगर (test_bit(QL_LINK_MASTER, &qdev->flags)) अणु
			netअगर_prपूर्णांकk(qdev, link, KERN_DEBUG, qdev->ndev,
				     "Remote error detected. Calling ql_port_start()\n");
			/*
			 * ql_port_start() is shared code and needs
			 * to lock the PHY on it's own.
			 */
			ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
			अगर (ql_port_start(qdev))	/* Restart port */
				वापस -1;
			वापस 0;
		पूर्ण
	पूर्ण
	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	वापस 0;
पूर्ण

अटल व्योम ql_link_state_machine_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ql3_adapter *qdev =
		container_of(work, काष्ठा ql3_adapter, link_state_work.work);

	u32 curr_link_state;
	अचिन्हित दीर्घ hw_flags;

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);

	curr_link_state = ql_get_link_state(qdev);

	अगर (test_bit(QL_RESET_ACTIVE, &qdev->flags)) अणु
		netअगर_info(qdev, link, qdev->ndev,
			   "Reset in progress, skip processing link state\n");

		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);

		/* Restart समयr on 2 second पूर्णांकerval. */
		mod_समयr(&qdev->adapter_समयr, jअगरfies + HZ * 1);

		वापस;
	पूर्ण

	चयन (qdev->port_link_state) अणु
	शेष:
		अगर (test_bit(QL_LINK_MASTER, &qdev->flags))
			ql_port_start(qdev);
		qdev->port_link_state = LS_DOWN;
		fallthrough;

	हाल LS_DOWN:
		अगर (curr_link_state == LS_UP) अणु
			netअगर_info(qdev, link, qdev->ndev, "Link is up\n");
			अगर (ql_is_स्वतः_neg_complete(qdev))
				ql_finish_स्वतः_neg(qdev);

			अगर (qdev->port_link_state == LS_UP)
				ql_link_करोwn_detect_clear(qdev);

			qdev->port_link_state = LS_UP;
		पूर्ण
		अवरोध;

	हाल LS_UP:
		/*
		 * See अगर the link is currently करोwn or went करोwn and came
		 * back up
		 */
		अगर (curr_link_state == LS_DOWN) अणु
			netअगर_info(qdev, link, qdev->ndev, "Link is down\n");
			qdev->port_link_state = LS_DOWN;
		पूर्ण
		अगर (ql_link_करोwn_detect(qdev))
			qdev->port_link_state = LS_DOWN;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);

	/* Restart समयr on 2 second पूर्णांकerval. */
	mod_समयr(&qdev->adapter_समयr, jअगरfies + HZ * 1);
पूर्ण

/*
 * Caller must take hw_lock and QL_PHY_GIO_SEM.
 */
अटल व्योम ql_get_phy_owner(काष्ठा ql3_adapter *qdev)
अणु
	अगर (ql_this_adapter_controls_port(qdev))
		set_bit(QL_LINK_MASTER, &qdev->flags);
	अन्यथा
		clear_bit(QL_LINK_MASTER, &qdev->flags);
पूर्ण

/*
 * Caller must take hw_lock and QL_PHY_GIO_SEM.
 */
अटल व्योम ql_init_scan_mode(काष्ठा ql3_adapter *qdev)
अणु
	ql_mii_enable_scan_mode(qdev);

	अगर (test_bit(QL_LINK_OPTICAL, &qdev->flags)) अणु
		अगर (ql_this_adapter_controls_port(qdev))
			ql_petbi_init_ex(qdev);
	पूर्ण अन्यथा अणु
		अगर (ql_this_adapter_controls_port(qdev))
			ql_phy_init_ex(qdev);
	पूर्ण
पूर्ण

/*
 * MII_Setup needs to be called beक्रमe taking the PHY out of reset
 * so that the management पूर्णांकerface घड़ी speed can be set properly.
 * It would be better अगर we had a way to disable MDC until after the
 * PHY is out of reset, but we करोn't have that capability.
 */
अटल पूर्णांक ql_mii_setup(काष्ठा ql3_adapter *qdev)
अणु
	u32 reg;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;

	अगर (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
			(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 7))
		वापस -1;

	अगर (qdev->device_id == QL3032_DEVICE_ID)
		ql_ग_लिखो_page0_reg(qdev,
			&port_regs->macMIIMgmtControlReg, 0x0f00000);

	/* Divide 125MHz घड़ी by 28 to meet PHY timing requirements */
	reg = MAC_MII_CONTROL_CLK_SEL_DIV28;

	ql_ग_लिखो_page0_reg(qdev, &port_regs->macMIIMgmtControlReg,
			   reg | ((MAC_MII_CONTROL_CLK_SEL_MASK) << 16));

	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	वापस 0;
पूर्ण

#घोषणा SUPPORTED_OPTICAL_MODES	(SUPPORTED_1000baseT_Full |	\
				 SUPPORTED_FIBRE |		\
				 SUPPORTED_Autoneg)
#घोषणा SUPPORTED_TP_MODES	(SUPPORTED_10baseT_Half |	\
				 SUPPORTED_10baseT_Full |	\
				 SUPPORTED_100baseT_Half |	\
				 SUPPORTED_100baseT_Full |	\
				 SUPPORTED_1000baseT_Half |	\
				 SUPPORTED_1000baseT_Full |	\
				 SUPPORTED_Autoneg |		\
				 SUPPORTED_TP)			\

अटल u32 ql_supported_modes(काष्ठा ql3_adapter *qdev)
अणु
	अगर (test_bit(QL_LINK_OPTICAL, &qdev->flags))
		वापस SUPPORTED_OPTICAL_MODES;

	वापस SUPPORTED_TP_MODES;
पूर्ण

अटल पूर्णांक ql_get_स्वतः_cfg_status(काष्ठा ql3_adapter *qdev)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ hw_flags;
	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	अगर (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
			    (QL_RESOURCE_BITS_BASE_CODE |
			     (qdev->mac_index) * 2) << 7)) अणु
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
		वापस 0;
	पूर्ण
	status = ql_is_स्वतः_cfg(qdev);
	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	वापस status;
पूर्ण

अटल u32 ql_get_speed(काष्ठा ql3_adapter *qdev)
अणु
	u32 status;
	अचिन्हित दीर्घ hw_flags;
	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	अगर (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
			    (QL_RESOURCE_BITS_BASE_CODE |
			     (qdev->mac_index) * 2) << 7)) अणु
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
		वापस 0;
	पूर्ण
	status = ql_get_link_speed(qdev);
	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	वापस status;
पूर्ण

अटल पूर्णांक ql_get_full_dup(काष्ठा ql3_adapter *qdev)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ hw_flags;
	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	अगर (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
			    (QL_RESOURCE_BITS_BASE_CODE |
			     (qdev->mac_index) * 2) << 7)) अणु
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
		वापस 0;
	पूर्ण
	status = ql_is_link_full_dup(qdev);
	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	वापस status;
पूर्ण

अटल पूर्णांक ql_get_link_ksettings(काष्ठा net_device *ndev,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	u32 supported, advertising;

	supported = ql_supported_modes(qdev);

	अगर (test_bit(QL_LINK_OPTICAL, &qdev->flags)) अणु
		cmd->base.port = PORT_FIBRE;
	पूर्ण अन्यथा अणु
		cmd->base.port = PORT_TP;
		cmd->base.phy_address = qdev->PHYAddr;
	पूर्ण
	advertising = ql_supported_modes(qdev);
	cmd->base.स्वतःneg = ql_get_स्वतः_cfg_status(qdev);
	cmd->base.speed = ql_get_speed(qdev);
	cmd->base.duplex = ql_get_full_dup(qdev);

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल व्योम ql_get_drvinfo(काष्ठा net_device *ndev,
			   काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	strlcpy(drvinfo->driver, ql3xxx_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->version, ql3xxx_driver_version,
		माप(drvinfo->version));
	strlcpy(drvinfo->bus_info, pci_name(qdev->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल u32 ql_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	वापस qdev->msg_enable;
पूर्ण

अटल व्योम ql_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	qdev->msg_enable = value;
पूर्ण

अटल व्योम ql_get_छोड़ोparam(काष्ठा net_device *ndev,
			      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;

	u32 reg;
	अगर (qdev->mac_index == 0)
		reg = ql_पढ़ो_page0_reg(qdev, &port_regs->mac0ConfigReg);
	अन्यथा
		reg = ql_पढ़ो_page0_reg(qdev, &port_regs->mac1ConfigReg);

	छोड़ो->स्वतःneg  = ql_get_स्वतः_cfg_status(qdev);
	छोड़ो->rx_छोड़ो = (reg & MAC_CONFIG_REG_RF) >> 2;
	छोड़ो->tx_छोड़ो = (reg & MAC_CONFIG_REG_TF) >> 1;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ql3xxx_ethtool_ops = अणु
	.get_drvinfo = ql_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_msglevel = ql_get_msglevel,
	.set_msglevel = ql_set_msglevel,
	.get_छोड़ोparam = ql_get_छोड़ोparam,
	.get_link_ksettings = ql_get_link_ksettings,
पूर्ण;

अटल पूर्णांक ql_populate_मुक्त_queue(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb = qdev->lrg_buf_मुक्त_head;
	dma_addr_t map;
	पूर्णांक err;

	जबतक (lrg_buf_cb) अणु
		अगर (!lrg_buf_cb->skb) अणु
			lrg_buf_cb->skb =
				netdev_alloc_skb(qdev->ndev,
						 qdev->lrg_buffer_len);
			अगर (unlikely(!lrg_buf_cb->skb)) अणु
				netdev_prपूर्णांकk(KERN_DEBUG, qdev->ndev,
					      "Failed netdev_alloc_skb()\n");
				अवरोध;
			पूर्ण अन्यथा अणु
				/*
				 * We save some space to copy the ethhdr from
				 * first buffer
				 */
				skb_reserve(lrg_buf_cb->skb, QL_HEADER_SPACE);
				map = dma_map_single(&qdev->pdev->dev,
						     lrg_buf_cb->skb->data,
						     qdev->lrg_buffer_len - QL_HEADER_SPACE,
						     DMA_FROM_DEVICE);

				err = dma_mapping_error(&qdev->pdev->dev, map);
				अगर (err) अणु
					netdev_err(qdev->ndev,
						   "PCI mapping failed with error: %d\n",
						   err);
					dev_kमुक्त_skb(lrg_buf_cb->skb);
					lrg_buf_cb->skb = शून्य;
					अवरोध;
				पूर्ण


				lrg_buf_cb->buf_phy_addr_low =
					cpu_to_le32(LS_64BITS(map));
				lrg_buf_cb->buf_phy_addr_high =
					cpu_to_le32(MS_64BITS(map));
				dma_unmap_addr_set(lrg_buf_cb, mapaddr, map);
				dma_unmap_len_set(lrg_buf_cb, maplen,
						  qdev->lrg_buffer_len -
						  QL_HEADER_SPACE);
				--qdev->lrg_buf_skb_check;
				अगर (!qdev->lrg_buf_skb_check)
					वापस 1;
			पूर्ण
		पूर्ण
		lrg_buf_cb = lrg_buf_cb->next;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम ql_update_small_bufq_prod_index(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;

	अगर (qdev->small_buf_release_cnt >= 16) अणु
		जबतक (qdev->small_buf_release_cnt >= 16) अणु
			qdev->small_buf_q_producer_index++;

			अगर (qdev->small_buf_q_producer_index ==
			    NUM_SBUFQ_ENTRIES)
				qdev->small_buf_q_producer_index = 0;
			qdev->small_buf_release_cnt -= 8;
		पूर्ण
		wmb();
		ग_लिखोl_relaxed(qdev->small_buf_q_producer_index,
			       &port_regs->CommonRegs.rxSmallQProducerIndex);
	पूर्ण
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल व्योम ql_update_lrg_bufq_prod_index(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा bufq_addr_element *lrg_buf_q_ele;
	पूर्णांक i;
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;

	अगर ((qdev->lrg_buf_मुक्त_count >= 8) &&
	    (qdev->lrg_buf_release_cnt >= 16)) अणु

		अगर (qdev->lrg_buf_skb_check)
			अगर (!ql_populate_मुक्त_queue(qdev))
				वापस;

		lrg_buf_q_ele = qdev->lrg_buf_next_मुक्त;

		जबतक ((qdev->lrg_buf_release_cnt >= 16) &&
		       (qdev->lrg_buf_मुक्त_count >= 8)) अणु

			क्रम (i = 0; i < 8; i++) अणु
				lrg_buf_cb =
				    ql_get_from_lrg_buf_मुक्त_list(qdev);
				lrg_buf_q_ele->addr_high =
				    lrg_buf_cb->buf_phy_addr_high;
				lrg_buf_q_ele->addr_low =
				    lrg_buf_cb->buf_phy_addr_low;
				lrg_buf_q_ele++;

				qdev->lrg_buf_release_cnt--;
			पूर्ण

			qdev->lrg_buf_q_producer_index++;

			अगर (qdev->lrg_buf_q_producer_index ==
			    qdev->num_lbufq_entries)
				qdev->lrg_buf_q_producer_index = 0;

			अगर (qdev->lrg_buf_q_producer_index ==
			    (qdev->num_lbufq_entries - 1)) अणु
				lrg_buf_q_ele = qdev->lrg_buf_q_virt_addr;
			पूर्ण
		पूर्ण
		wmb();
		qdev->lrg_buf_next_मुक्त = lrg_buf_q_ele;
		ग_लिखोl(qdev->lrg_buf_q_producer_index,
			&port_regs->CommonRegs.rxLargeQProducerIndex);
	पूर्ण
पूर्ण

अटल व्योम ql_process_mac_tx_पूर्णांकr(काष्ठा ql3_adapter *qdev,
				   काष्ठा ob_mac_iocb_rsp *mac_rsp)
अणु
	काष्ठा ql_tx_buf_cb *tx_cb;
	पूर्णांक i;

	अगर (mac_rsp->flags & OB_MAC_IOCB_RSP_S) अणु
		netdev_warn(qdev->ndev,
			    "Frame too short but it was padded and sent\n");
	पूर्ण

	tx_cb = &qdev->tx_buf[mac_rsp->transaction_id];

	/*  Check the transmit response flags क्रम any errors */
	अगर (mac_rsp->flags & OB_MAC_IOCB_RSP_S) अणु
		netdev_err(qdev->ndev,
			   "Frame too short to be legal, frame not sent\n");

		qdev->ndev->stats.tx_errors++;
		जाओ frame_not_sent;
	पूर्ण

	अगर (tx_cb->seg_count == 0) अणु
		netdev_err(qdev->ndev, "tx_cb->seg_count == 0: %d\n",
			   mac_rsp->transaction_id);

		qdev->ndev->stats.tx_errors++;
		जाओ invalid_seg_count;
	पूर्ण

	dma_unmap_single(&qdev->pdev->dev,
			 dma_unmap_addr(&tx_cb->map[0], mapaddr),
			 dma_unmap_len(&tx_cb->map[0], maplen), DMA_TO_DEVICE);
	tx_cb->seg_count--;
	अगर (tx_cb->seg_count) अणु
		क्रम (i = 1; i < tx_cb->seg_count; i++) अणु
			dma_unmap_page(&qdev->pdev->dev,
				       dma_unmap_addr(&tx_cb->map[i], mapaddr),
				       dma_unmap_len(&tx_cb->map[i], maplen),
				       DMA_TO_DEVICE);
		पूर्ण
	पूर्ण
	qdev->ndev->stats.tx_packets++;
	qdev->ndev->stats.tx_bytes += tx_cb->skb->len;

frame_not_sent:
	dev_kमुक्त_skb_irq(tx_cb->skb);
	tx_cb->skb = शून्य;

invalid_seg_count:
	atomic_inc(&qdev->tx_count);
पूर्ण

अटल व्योम ql_get_sbuf(काष्ठा ql3_adapter *qdev)
अणु
	अगर (++qdev->small_buf_index == NUM_SMALL_BUFFERS)
		qdev->small_buf_index = 0;
	qdev->small_buf_release_cnt++;
पूर्ण

अटल काष्ठा ql_rcv_buf_cb *ql_get_lbuf(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb = शून्य;
	lrg_buf_cb = &qdev->lrg_buf[qdev->lrg_buf_index];
	qdev->lrg_buf_release_cnt++;
	अगर (++qdev->lrg_buf_index == qdev->num_large_buffers)
		qdev->lrg_buf_index = 0;
	वापस lrg_buf_cb;
पूर्ण

/*
 * The dअगरference between 3022 and 3032 क्रम inbound completions:
 * 3022 uses two buffers per completion.  The first buffer contains
 * (some) header info, the second the reमुख्यder of the headers plus
 * the data.  For this chip we reserve some space at the top of the
 * receive buffer so that the header info in buffer one can be
 * prepended to the buffer two.  Buffer two is the sent up जबतक
 * buffer one is वापसed to the hardware to be reused.
 * 3032 receives all of it's data and headers in one buffer क्रम a
 * simpler process.  3032 also supports checksum verअगरication as
 * can be seen in ql_process_macip_rx_पूर्णांकr().
 */
अटल व्योम ql_process_mac_rx_पूर्णांकr(काष्ठा ql3_adapter *qdev,
				   काष्ठा ib_mac_iocb_rsp *ib_mac_rsp_ptr)
अणु
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb1 = शून्य;
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb2 = शून्य;
	काष्ठा sk_buff *skb;
	u16 length = le16_to_cpu(ib_mac_rsp_ptr->length);

	/*
	 * Get the inbound address list (small buffer).
	 */
	ql_get_sbuf(qdev);

	अगर (qdev->device_id == QL3022_DEVICE_ID)
		lrg_buf_cb1 = ql_get_lbuf(qdev);

	/* start of second buffer */
	lrg_buf_cb2 = ql_get_lbuf(qdev);
	skb = lrg_buf_cb2->skb;

	qdev->ndev->stats.rx_packets++;
	qdev->ndev->stats.rx_bytes += length;

	skb_put(skb, length);
	dma_unmap_single(&qdev->pdev->dev,
			 dma_unmap_addr(lrg_buf_cb2, mapaddr),
			 dma_unmap_len(lrg_buf_cb2, maplen), DMA_FROM_DEVICE);
	prefetch(skb->data);
	skb_checksum_none_निश्चित(skb);
	skb->protocol = eth_type_trans(skb, qdev->ndev);

	napi_gro_receive(&qdev->napi, skb);
	lrg_buf_cb2->skb = शून्य;

	अगर (qdev->device_id == QL3022_DEVICE_ID)
		ql_release_to_lrg_buf_मुक्त_list(qdev, lrg_buf_cb1);
	ql_release_to_lrg_buf_मुक्त_list(qdev, lrg_buf_cb2);
पूर्ण

अटल व्योम ql_process_macip_rx_पूर्णांकr(काष्ठा ql3_adapter *qdev,
				     काष्ठा ib_ip_iocb_rsp *ib_ip_rsp_ptr)
अणु
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb1 = शून्य;
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb2 = शून्य;
	काष्ठा sk_buff *skb1 = शून्य, *skb2;
	काष्ठा net_device *ndev = qdev->ndev;
	u16 length = le16_to_cpu(ib_ip_rsp_ptr->length);
	u16 size = 0;

	/*
	 * Get the inbound address list (small buffer).
	 */

	ql_get_sbuf(qdev);

	अगर (qdev->device_id == QL3022_DEVICE_ID) अणु
		/* start of first buffer on 3022 */
		lrg_buf_cb1 = ql_get_lbuf(qdev);
		skb1 = lrg_buf_cb1->skb;
		size = ETH_HLEN;
		अगर (*((u16 *) skb1->data) != 0xFFFF)
			size += VLAN_ETH_HLEN - ETH_HLEN;
	पूर्ण

	/* start of second buffer */
	lrg_buf_cb2 = ql_get_lbuf(qdev);
	skb2 = lrg_buf_cb2->skb;

	skb_put(skb2, length);	/* Just the second buffer length here. */
	dma_unmap_single(&qdev->pdev->dev,
			 dma_unmap_addr(lrg_buf_cb2, mapaddr),
			 dma_unmap_len(lrg_buf_cb2, maplen), DMA_FROM_DEVICE);
	prefetch(skb2->data);

	skb_checksum_none_निश्चित(skb2);
	अगर (qdev->device_id == QL3022_DEVICE_ID) अणु
		/*
		 * Copy the ethhdr from first buffer to second. This
		 * is necessary क्रम 3022 IP completions.
		 */
		skb_copy_from_linear_data_offset(skb1, VLAN_ID_LEN,
						 skb_push(skb2, size), size);
	पूर्ण अन्यथा अणु
		u16 checksum = le16_to_cpu(ib_ip_rsp_ptr->checksum);
		अगर (checksum &
			(IB_IP_IOCB_RSP_3032_ICE |
			 IB_IP_IOCB_RSP_3032_CE)) अणु
			netdev_err(ndev,
				   "%s: Bad checksum for this %s packet, checksum = %x\n",
				   __func__,
				   ((checksum & IB_IP_IOCB_RSP_3032_TCP) ?
				    "TCP" : "UDP"), checksum);
		पूर्ण अन्यथा अगर ((checksum & IB_IP_IOCB_RSP_3032_TCP) ||
				(checksum & IB_IP_IOCB_RSP_3032_UDP &&
				!(checksum & IB_IP_IOCB_RSP_3032_NUC))) अणु
			skb2->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण
	पूर्ण
	skb2->protocol = eth_type_trans(skb2, qdev->ndev);

	napi_gro_receive(&qdev->napi, skb2);
	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += length;
	lrg_buf_cb2->skb = शून्य;

	अगर (qdev->device_id == QL3022_DEVICE_ID)
		ql_release_to_lrg_buf_मुक्त_list(qdev, lrg_buf_cb1);
	ql_release_to_lrg_buf_मुक्त_list(qdev, lrg_buf_cb2);
पूर्ण

अटल पूर्णांक ql_tx_rx_clean(काष्ठा ql3_adapter *qdev, पूर्णांक budget)
अणु
	काष्ठा net_rsp_iocb *net_rsp;
	काष्ठा net_device *ndev = qdev->ndev;
	पूर्णांक work_करोne = 0;

	/* While there are entries in the completion queue. */
	जबतक ((le32_to_cpu(*(qdev->prsp_producer_index)) !=
		qdev->rsp_consumer_index) && (work_करोne < budget)) अणु

		net_rsp = qdev->rsp_current;
		rmb();
		/*
		 * Fix 4032 chip's unकरोcumented "feature" where bit-8 is set
		 * अगर the inbound completion is क्रम a VLAN.
		 */
		अगर (qdev->device_id == QL3032_DEVICE_ID)
			net_rsp->opcode &= 0x7f;
		चयन (net_rsp->opcode) अणु

		हाल OPCODE_OB_MAC_IOCB_FN0:
		हाल OPCODE_OB_MAC_IOCB_FN2:
			ql_process_mac_tx_पूर्णांकr(qdev, (काष्ठा ob_mac_iocb_rsp *)
					       net_rsp);
			अवरोध;

		हाल OPCODE_IB_MAC_IOCB:
		हाल OPCODE_IB_3032_MAC_IOCB:
			ql_process_mac_rx_पूर्णांकr(qdev, (काष्ठा ib_mac_iocb_rsp *)
					       net_rsp);
			work_करोne++;
			अवरोध;

		हाल OPCODE_IB_IP_IOCB:
		हाल OPCODE_IB_3032_IP_IOCB:
			ql_process_macip_rx_पूर्णांकr(qdev, (काष्ठा ib_ip_iocb_rsp *)
						 net_rsp);
			work_करोne++;
			अवरोध;
		शेष: अणु
			u32 *पंचांगp = (u32 *)net_rsp;
			netdev_err(ndev,
				   "Hit default case, not handled!\n"
				   "	dropping the packet, opcode = %x\n"
				   "0x%08lx 0x%08lx 0x%08lx 0x%08lx\n",
				   net_rsp->opcode,
				   (अचिन्हित दीर्घ पूर्णांक)पंचांगp[0],
				   (अचिन्हित दीर्घ पूर्णांक)पंचांगp[1],
				   (अचिन्हित दीर्घ पूर्णांक)पंचांगp[2],
				   (अचिन्हित दीर्घ पूर्णांक)पंचांगp[3]);
		पूर्ण
		पूर्ण

		qdev->rsp_consumer_index++;

		अगर (qdev->rsp_consumer_index == NUM_RSP_Q_ENTRIES) अणु
			qdev->rsp_consumer_index = 0;
			qdev->rsp_current = qdev->rsp_q_virt_addr;
		पूर्ण अन्यथा अणु
			qdev->rsp_current++;
		पूर्ण

	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक ql_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ql3_adapter *qdev = container_of(napi, काष्ठा ql3_adapter, napi);
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	पूर्णांक work_करोne;

	work_करोne = ql_tx_rx_clean(qdev, budget);

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&qdev->hw_lock, flags);
		ql_update_small_bufq_prod_index(qdev);
		ql_update_lrg_bufq_prod_index(qdev);
		ग_लिखोl(qdev->rsp_consumer_index,
			    &port_regs->CommonRegs.rspQConsumerIndex);
		spin_unlock_irqrestore(&qdev->hw_lock, flags);

		ql_enable_पूर्णांकerrupts(qdev);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल irqवापस_t ql3xxx_isr(पूर्णांक irq, व्योम *dev_id)
अणु

	काष्ठा net_device *ndev = dev_id;
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	u32 value;
	पूर्णांक handled = 1;
	u32 var;

	value = ql_पढ़ो_common_reg_l(qdev,
				     &port_regs->CommonRegs.ispControlStatus);

	अगर (value & (ISP_CONTROL_FE | ISP_CONTROL_RI)) अणु
		spin_lock(&qdev->adapter_lock);
		netअगर_stop_queue(qdev->ndev);
		netअगर_carrier_off(qdev->ndev);
		ql_disable_पूर्णांकerrupts(qdev);
		qdev->port_link_state = LS_DOWN;
		set_bit(QL_RESET_ACTIVE, &qdev->flags) ;

		अगर (value & ISP_CONTROL_FE) अणु
			/*
			 * Chip Fatal Error.
			 */
			var =
			    ql_पढ़ो_page0_reg_l(qdev,
					      &port_regs->PortFatalErrStatus);
			netdev_warn(ndev,
				    "Resetting chip. PortFatalErrStatus register = 0x%x\n",
				    var);
			set_bit(QL_RESET_START, &qdev->flags) ;
		पूर्ण अन्यथा अणु
			/*
			 * Soft Reset Requested.
			 */
			set_bit(QL_RESET_PER_SCSI, &qdev->flags) ;
			netdev_err(ndev,
				   "Another function issued a reset to the chip. ISR value = %x\n",
				   value);
		पूर्ण
		queue_delayed_work(qdev->workqueue, &qdev->reset_work, 0);
		spin_unlock(&qdev->adapter_lock);
	पूर्ण अन्यथा अगर (value & ISP_IMR_DISABLE_CMPL_INT) अणु
		ql_disable_पूर्णांकerrupts(qdev);
		अगर (likely(napi_schedule_prep(&qdev->napi)))
			__napi_schedule(&qdev->napi);
	पूर्ण अन्यथा
		वापस IRQ_NONE;

	वापस IRQ_RETVAL(handled);
पूर्ण

/*
 * Get the total number of segments needed क्रम the given number of fragments.
 * This is necessary because outbound address lists (OAL) will be used when
 * more than two frags are given.  Each address list has 5 addr/len pairs.
 * The 5th pair in each OAL is used to  poपूर्णांक to the next OAL अगर more frags
 * are coming.  That is why the frags:segment count ratio is not linear.
 */
अटल पूर्णांक ql_get_seg_count(काष्ठा ql3_adapter *qdev, अचिन्हित लघु frags)
अणु
	अगर (qdev->device_id == QL3022_DEVICE_ID)
		वापस 1;

	अगर (frags <= 2)
		वापस frags + 1;
	अन्यथा अगर (frags <= 6)
		वापस frags + 2;
	अन्यथा अगर (frags <= 10)
		वापस frags + 3;
	अन्यथा अगर (frags <= 14)
		वापस frags + 4;
	अन्यथा अगर (frags <= 18)
		वापस frags + 5;
	वापस -1;
पूर्ण

अटल व्योम ql_hw_csum_setup(स्थिर काष्ठा sk_buff *skb,
			     काष्ठा ob_mac_iocb_req *mac_iocb_ptr)
अणु
	स्थिर काष्ठा iphdr *ip = ip_hdr(skb);

	mac_iocb_ptr->ip_hdr_off = skb_network_offset(skb);
	mac_iocb_ptr->ip_hdr_len = ip->ihl;

	अगर (ip->protocol == IPPROTO_TCP) अणु
		mac_iocb_ptr->flags1 |= OB_3032MAC_IOCB_REQ_TC |
			OB_3032MAC_IOCB_REQ_IC;
	पूर्ण अन्यथा अणु
		mac_iocb_ptr->flags1 |= OB_3032MAC_IOCB_REQ_UC |
			OB_3032MAC_IOCB_REQ_IC;
	पूर्ण

पूर्ण

/*
 * Map the buffers क्रम this transmit.
 * This will वापस NETDEV_TX_BUSY or NETDEV_TX_OK based on success.
 */
अटल पूर्णांक ql_send_map(काष्ठा ql3_adapter *qdev,
				काष्ठा ob_mac_iocb_req *mac_iocb_ptr,
				काष्ठा ql_tx_buf_cb *tx_cb,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा oal *oal;
	काष्ठा oal_entry *oal_entry;
	पूर्णांक len = skb_headlen(skb);
	dma_addr_t map;
	पूर्णांक err;
	पूर्णांक completed_segs, i;
	पूर्णांक seg_cnt, seg = 0;
	पूर्णांक frag_cnt = (पूर्णांक)skb_shinfo(skb)->nr_frags;

	seg_cnt = tx_cb->seg_count;
	/*
	 * Map the skb buffer first.
	 */
	map = dma_map_single(&qdev->pdev->dev, skb->data, len, DMA_TO_DEVICE);

	err = dma_mapping_error(&qdev->pdev->dev, map);
	अगर (err) अणु
		netdev_err(qdev->ndev, "PCI mapping failed with error: %d\n",
			   err);

		वापस NETDEV_TX_BUSY;
	पूर्ण

	oal_entry = (काष्ठा oal_entry *)&mac_iocb_ptr->buf_addr0_low;
	oal_entry->dma_lo = cpu_to_le32(LS_64BITS(map));
	oal_entry->dma_hi = cpu_to_le32(MS_64BITS(map));
	oal_entry->len = cpu_to_le32(len);
	dma_unmap_addr_set(&tx_cb->map[seg], mapaddr, map);
	dma_unmap_len_set(&tx_cb->map[seg], maplen, len);
	seg++;

	अगर (seg_cnt == 1) अणु
		/* Terminate the last segment. */
		oal_entry->len |= cpu_to_le32(OAL_LAST_ENTRY);
		वापस NETDEV_TX_OK;
	पूर्ण
	oal = tx_cb->oal;
	क्रम (completed_segs = 0;
	     completed_segs < frag_cnt;
	     completed_segs++, seg++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[completed_segs];
		oal_entry++;
		/*
		 * Check क्रम continuation requirements.
		 * It's strange but necessary.
		 * Continuation entry poपूर्णांकs to outbound address list.
		 */
		अगर ((seg == 2 && seg_cnt > 3) ||
		    (seg == 7 && seg_cnt > 8) ||
		    (seg == 12 && seg_cnt > 13) ||
		    (seg == 17 && seg_cnt > 18)) अणु
			map = dma_map_single(&qdev->pdev->dev, oal,
					     माप(काष्ठा oal),
					     DMA_TO_DEVICE);

			err = dma_mapping_error(&qdev->pdev->dev, map);
			अगर (err) अणु
				netdev_err(qdev->ndev,
					   "PCI mapping outbound address list with error: %d\n",
					   err);
				जाओ map_error;
			पूर्ण

			oal_entry->dma_lo = cpu_to_le32(LS_64BITS(map));
			oal_entry->dma_hi = cpu_to_le32(MS_64BITS(map));
			oal_entry->len = cpu_to_le32(माप(काष्ठा oal) |
						     OAL_CONT_ENTRY);
			dma_unmap_addr_set(&tx_cb->map[seg], mapaddr, map);
			dma_unmap_len_set(&tx_cb->map[seg], maplen,
					  माप(काष्ठा oal));
			oal_entry = (काष्ठा oal_entry *)oal;
			oal++;
			seg++;
		पूर्ण

		map = skb_frag_dma_map(&qdev->pdev->dev, frag, 0, skb_frag_size(frag),
				       DMA_TO_DEVICE);

		err = dma_mapping_error(&qdev->pdev->dev, map);
		अगर (err) अणु
			netdev_err(qdev->ndev,
				   "PCI mapping frags failed with error: %d\n",
				   err);
			जाओ map_error;
		पूर्ण

		oal_entry->dma_lo = cpu_to_le32(LS_64BITS(map));
		oal_entry->dma_hi = cpu_to_le32(MS_64BITS(map));
		oal_entry->len = cpu_to_le32(skb_frag_size(frag));
		dma_unmap_addr_set(&tx_cb->map[seg], mapaddr, map);
		dma_unmap_len_set(&tx_cb->map[seg], maplen, skb_frag_size(frag));
		पूर्ण
	/* Terminate the last segment. */
	oal_entry->len |= cpu_to_le32(OAL_LAST_ENTRY);
	वापस NETDEV_TX_OK;

map_error:
	/* A PCI mapping failed and now we will need to back out
	 * We need to traverse through the oal's and associated pages which
	 * have been mapped and now we must unmap them to clean up properly
	 */

	seg = 1;
	oal_entry = (काष्ठा oal_entry *)&mac_iocb_ptr->buf_addr0_low;
	oal = tx_cb->oal;
	क्रम (i = 0; i < completed_segs; i++, seg++) अणु
		oal_entry++;

		/*
		 * Check क्रम continuation requirements.
		 * It's strange but necessary.
		 */

		अगर ((seg == 2 && seg_cnt > 3) ||
		    (seg == 7 && seg_cnt > 8) ||
		    (seg == 12 && seg_cnt > 13) ||
		    (seg == 17 && seg_cnt > 18)) अणु
			dma_unmap_single(&qdev->pdev->dev,
					 dma_unmap_addr(&tx_cb->map[seg], mapaddr),
					 dma_unmap_len(&tx_cb->map[seg], maplen),
					 DMA_TO_DEVICE);
			oal++;
			seg++;
		पूर्ण

		dma_unmap_page(&qdev->pdev->dev,
			       dma_unmap_addr(&tx_cb->map[seg], mapaddr),
			       dma_unmap_len(&tx_cb->map[seg], maplen),
			       DMA_TO_DEVICE);
	पूर्ण

	dma_unmap_single(&qdev->pdev->dev,
			 dma_unmap_addr(&tx_cb->map[0], mapaddr),
			 dma_unmap_addr(&tx_cb->map[0], maplen),
			 DMA_TO_DEVICE);

	वापस NETDEV_TX_BUSY;

पूर्ण

/*
 * The dअगरference between 3022 and 3032 sends:
 * 3022 only supports a simple single segment transmission.
 * 3032 supports checksumming and scatter/gather lists (fragments).
 * The 3032 supports sglists by using the 3 addr/len pairs (ALP)
 * in the IOCB plus a chain of outbound address lists (OAL) that
 * each contain 5 ALPs.  The last ALP of the IOCB (3rd) or OAL (5th)
 * will be used to poपूर्णांक to an OAL when more ALP entries are required.
 * The IOCB is always the top of the chain followed by one or more
 * OALs (when necessary).
 */
अटल netdev_tx_t ql3xxx_send(काष्ठा sk_buff *skb,
			       काष्ठा net_device *ndev)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	काष्ठा ql_tx_buf_cb *tx_cb;
	u32 tot_len = skb->len;
	काष्ठा ob_mac_iocb_req *mac_iocb_ptr;

	अगर (unlikely(atomic_पढ़ो(&qdev->tx_count) < 2))
		वापस NETDEV_TX_BUSY;

	tx_cb = &qdev->tx_buf[qdev->req_producer_index];
	tx_cb->seg_count = ql_get_seg_count(qdev,
					     skb_shinfo(skb)->nr_frags);
	अगर (tx_cb->seg_count == -1) अणु
		netdev_err(ndev, "%s: invalid segment count!\n", __func__);
		वापस NETDEV_TX_OK;
	पूर्ण

	mac_iocb_ptr = tx_cb->queue_entry;
	स_रखो((व्योम *)mac_iocb_ptr, 0, माप(काष्ठा ob_mac_iocb_req));
	mac_iocb_ptr->opcode = qdev->mac_ob_opcode;
	mac_iocb_ptr->flags = OB_MAC_IOCB_REQ_X;
	mac_iocb_ptr->flags |= qdev->mb_bit_mask;
	mac_iocb_ptr->transaction_id = qdev->req_producer_index;
	mac_iocb_ptr->data_len = cpu_to_le16((u16) tot_len);
	tx_cb->skb = skb;
	अगर (qdev->device_id == QL3032_DEVICE_ID &&
	    skb->ip_summed == CHECKSUM_PARTIAL)
		ql_hw_csum_setup(skb, mac_iocb_ptr);

	अगर (ql_send_map(qdev, mac_iocb_ptr, tx_cb, skb) != NETDEV_TX_OK) अणु
		netdev_err(ndev, "%s: Could not map the segments!\n", __func__);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	wmb();
	qdev->req_producer_index++;
	अगर (qdev->req_producer_index == NUM_REQ_Q_ENTRIES)
		qdev->req_producer_index = 0;
	wmb();
	ql_ग_लिखो_common_reg_l(qdev,
			    &port_regs->CommonRegs.reqQProducerIndex,
			    qdev->req_producer_index);

	netअगर_prपूर्णांकk(qdev, tx_queued, KERN_DEBUG, ndev,
		     "tx queued, slot %d, len %d\n",
		     qdev->req_producer_index, skb->len);

	atomic_dec(&qdev->tx_count);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ql_alloc_net_req_rsp_queues(काष्ठा ql3_adapter *qdev)
अणु
	qdev->req_q_size =
	    (u32) (NUM_REQ_Q_ENTRIES * माप(काष्ठा ob_mac_iocb_req));

	qdev->rsp_q_size = NUM_RSP_Q_ENTRIES * माप(काष्ठा net_rsp_iocb);

	/* The barrier is required to ensure request and response queue
	 * addr ग_लिखोs to the रेजिस्टरs.
	 */
	wmb();

	qdev->req_q_virt_addr =
	    dma_alloc_coherent(&qdev->pdev->dev, (माप_प्रकार)qdev->req_q_size,
			       &qdev->req_q_phy_addr, GFP_KERNEL);

	अगर ((qdev->req_q_virt_addr == शून्य) ||
	    LS_64BITS(qdev->req_q_phy_addr) & (qdev->req_q_size - 1)) अणु
		netdev_err(qdev->ndev, "reqQ failed\n");
		वापस -ENOMEM;
	पूर्ण

	qdev->rsp_q_virt_addr =
	    dma_alloc_coherent(&qdev->pdev->dev, (माप_प्रकार)qdev->rsp_q_size,
			       &qdev->rsp_q_phy_addr, GFP_KERNEL);

	अगर ((qdev->rsp_q_virt_addr == शून्य) ||
	    LS_64BITS(qdev->rsp_q_phy_addr) & (qdev->rsp_q_size - 1)) अणु
		netdev_err(qdev->ndev, "rspQ allocation failed\n");
		dma_मुक्त_coherent(&qdev->pdev->dev, (माप_प्रकार)qdev->req_q_size,
				  qdev->req_q_virt_addr, qdev->req_q_phy_addr);
		वापस -ENOMEM;
	पूर्ण

	set_bit(QL_ALLOC_REQ_RSP_Q_DONE, &qdev->flags);

	वापस 0;
पूर्ण

अटल व्योम ql_मुक्त_net_req_rsp_queues(काष्ठा ql3_adapter *qdev)
अणु
	अगर (!test_bit(QL_ALLOC_REQ_RSP_Q_DONE, &qdev->flags)) अणु
		netdev_info(qdev->ndev, "Already done\n");
		वापस;
	पूर्ण

	dma_मुक्त_coherent(&qdev->pdev->dev, qdev->req_q_size,
			  qdev->req_q_virt_addr, qdev->req_q_phy_addr);

	qdev->req_q_virt_addr = शून्य;

	dma_मुक्त_coherent(&qdev->pdev->dev, qdev->rsp_q_size,
			  qdev->rsp_q_virt_addr, qdev->rsp_q_phy_addr);

	qdev->rsp_q_virt_addr = शून्य;

	clear_bit(QL_ALLOC_REQ_RSP_Q_DONE, &qdev->flags);
पूर्ण

अटल पूर्णांक ql_alloc_buffer_queues(काष्ठा ql3_adapter *qdev)
अणु
	/* Create Large Buffer Queue */
	qdev->lrg_buf_q_size =
		qdev->num_lbufq_entries * माप(काष्ठा lrg_buf_q_entry);
	अगर (qdev->lrg_buf_q_size < PAGE_SIZE)
		qdev->lrg_buf_q_alloc_size = PAGE_SIZE;
	अन्यथा
		qdev->lrg_buf_q_alloc_size = qdev->lrg_buf_q_size * 2;

	qdev->lrg_buf = kदो_स्मृति_array(qdev->num_large_buffers,
				      माप(काष्ठा ql_rcv_buf_cb),
				      GFP_KERNEL);
	अगर (qdev->lrg_buf == शून्य)
		वापस -ENOMEM;

	qdev->lrg_buf_q_alloc_virt_addr =
		dma_alloc_coherent(&qdev->pdev->dev,
				   qdev->lrg_buf_q_alloc_size,
				   &qdev->lrg_buf_q_alloc_phy_addr, GFP_KERNEL);

	अगर (qdev->lrg_buf_q_alloc_virt_addr == शून्य) अणु
		netdev_err(qdev->ndev, "lBufQ failed\n");
		वापस -ENOMEM;
	पूर्ण
	qdev->lrg_buf_q_virt_addr = qdev->lrg_buf_q_alloc_virt_addr;
	qdev->lrg_buf_q_phy_addr = qdev->lrg_buf_q_alloc_phy_addr;

	/* Create Small Buffer Queue */
	qdev->small_buf_q_size =
		NUM_SBUFQ_ENTRIES * माप(काष्ठा lrg_buf_q_entry);
	अगर (qdev->small_buf_q_size < PAGE_SIZE)
		qdev->small_buf_q_alloc_size = PAGE_SIZE;
	अन्यथा
		qdev->small_buf_q_alloc_size = qdev->small_buf_q_size * 2;

	qdev->small_buf_q_alloc_virt_addr =
		dma_alloc_coherent(&qdev->pdev->dev,
				   qdev->small_buf_q_alloc_size,
				   &qdev->small_buf_q_alloc_phy_addr, GFP_KERNEL);

	अगर (qdev->small_buf_q_alloc_virt_addr == शून्य) अणु
		netdev_err(qdev->ndev, "Small Buffer Queue allocation failed\n");
		dma_मुक्त_coherent(&qdev->pdev->dev,
				  qdev->lrg_buf_q_alloc_size,
				  qdev->lrg_buf_q_alloc_virt_addr,
				  qdev->lrg_buf_q_alloc_phy_addr);
		वापस -ENOMEM;
	पूर्ण

	qdev->small_buf_q_virt_addr = qdev->small_buf_q_alloc_virt_addr;
	qdev->small_buf_q_phy_addr = qdev->small_buf_q_alloc_phy_addr;
	set_bit(QL_ALLOC_BUFQS_DONE, &qdev->flags);
	वापस 0;
पूर्ण

अटल व्योम ql_मुक्त_buffer_queues(काष्ठा ql3_adapter *qdev)
अणु
	अगर (!test_bit(QL_ALLOC_BUFQS_DONE, &qdev->flags)) अणु
		netdev_info(qdev->ndev, "Already done\n");
		वापस;
	पूर्ण
	kमुक्त(qdev->lrg_buf);
	dma_मुक्त_coherent(&qdev->pdev->dev, qdev->lrg_buf_q_alloc_size,
			  qdev->lrg_buf_q_alloc_virt_addr,
			  qdev->lrg_buf_q_alloc_phy_addr);

	qdev->lrg_buf_q_virt_addr = शून्य;

	dma_मुक्त_coherent(&qdev->pdev->dev, qdev->small_buf_q_alloc_size,
			  qdev->small_buf_q_alloc_virt_addr,
			  qdev->small_buf_q_alloc_phy_addr);

	qdev->small_buf_q_virt_addr = शून्य;

	clear_bit(QL_ALLOC_BUFQS_DONE, &qdev->flags);
पूर्ण

अटल पूर्णांक ql_alloc_small_buffers(काष्ठा ql3_adapter *qdev)
अणु
	पूर्णांक i;
	काष्ठा bufq_addr_element *small_buf_q_entry;

	/* Currently we allocate on one of memory and use it क्रम smallbuffers */
	qdev->small_buf_total_size =
		(QL_ADDR_ELE_PER_BUFQ_ENTRY * NUM_SBUFQ_ENTRIES *
		 QL_SMALL_BUFFER_SIZE);

	qdev->small_buf_virt_addr =
		dma_alloc_coherent(&qdev->pdev->dev,
				   qdev->small_buf_total_size,
				   &qdev->small_buf_phy_addr, GFP_KERNEL);

	अगर (qdev->small_buf_virt_addr == शून्य) अणु
		netdev_err(qdev->ndev, "Failed to get small buffer memory\n");
		वापस -ENOMEM;
	पूर्ण

	qdev->small_buf_phy_addr_low = LS_64BITS(qdev->small_buf_phy_addr);
	qdev->small_buf_phy_addr_high = MS_64BITS(qdev->small_buf_phy_addr);

	small_buf_q_entry = qdev->small_buf_q_virt_addr;

	/* Initialize the small buffer queue. */
	क्रम (i = 0; i < (QL_ADDR_ELE_PER_BUFQ_ENTRY * NUM_SBUFQ_ENTRIES); i++) अणु
		small_buf_q_entry->addr_high =
		    cpu_to_le32(qdev->small_buf_phy_addr_high);
		small_buf_q_entry->addr_low =
		    cpu_to_le32(qdev->small_buf_phy_addr_low +
				(i * QL_SMALL_BUFFER_SIZE));
		small_buf_q_entry++;
	पूर्ण
	qdev->small_buf_index = 0;
	set_bit(QL_ALLOC_SMALL_BUF_DONE, &qdev->flags);
	वापस 0;
पूर्ण

अटल व्योम ql_मुक्त_small_buffers(काष्ठा ql3_adapter *qdev)
अणु
	अगर (!test_bit(QL_ALLOC_SMALL_BUF_DONE, &qdev->flags)) अणु
		netdev_info(qdev->ndev, "Already done\n");
		वापस;
	पूर्ण
	अगर (qdev->small_buf_virt_addr != शून्य) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev,
				  qdev->small_buf_total_size,
				  qdev->small_buf_virt_addr,
				  qdev->small_buf_phy_addr);

		qdev->small_buf_virt_addr = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ql_मुक्त_large_buffers(काष्ठा ql3_adapter *qdev)
अणु
	पूर्णांक i = 0;
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb;

	क्रम (i = 0; i < qdev->num_large_buffers; i++) अणु
		lrg_buf_cb = &qdev->lrg_buf[i];
		अगर (lrg_buf_cb->skb) अणु
			dev_kमुक्त_skb(lrg_buf_cb->skb);
			dma_unmap_single(&qdev->pdev->dev,
					 dma_unmap_addr(lrg_buf_cb, mapaddr),
					 dma_unmap_len(lrg_buf_cb, maplen),
					 DMA_FROM_DEVICE);
			स_रखो(lrg_buf_cb, 0, माप(काष्ठा ql_rcv_buf_cb));
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ql_init_large_buffers(काष्ठा ql3_adapter *qdev)
अणु
	पूर्णांक i;
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb;
	काष्ठा bufq_addr_element *buf_addr_ele = qdev->lrg_buf_q_virt_addr;

	क्रम (i = 0; i < qdev->num_large_buffers; i++) अणु
		lrg_buf_cb = &qdev->lrg_buf[i];
		buf_addr_ele->addr_high = lrg_buf_cb->buf_phy_addr_high;
		buf_addr_ele->addr_low = lrg_buf_cb->buf_phy_addr_low;
		buf_addr_ele++;
	पूर्ण
	qdev->lrg_buf_index = 0;
	qdev->lrg_buf_skb_check = 0;
पूर्ण

अटल पूर्णांक ql_alloc_large_buffers(काष्ठा ql3_adapter *qdev)
अणु
	पूर्णांक i;
	काष्ठा ql_rcv_buf_cb *lrg_buf_cb;
	काष्ठा sk_buff *skb;
	dma_addr_t map;
	पूर्णांक err;

	क्रम (i = 0; i < qdev->num_large_buffers; i++) अणु
		lrg_buf_cb = &qdev->lrg_buf[i];
		स_रखो(lrg_buf_cb, 0, माप(काष्ठा ql_rcv_buf_cb));

		skb = netdev_alloc_skb(qdev->ndev,
				       qdev->lrg_buffer_len);
		अगर (unlikely(!skb)) अणु
			/* Better luck next round */
			netdev_err(qdev->ndev,
				   "large buff alloc failed for %d bytes at index %d\n",
				   qdev->lrg_buffer_len * 2, i);
			ql_मुक्त_large_buffers(qdev);
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			lrg_buf_cb->index = i;
			/*
			 * We save some space to copy the ethhdr from first
			 * buffer
			 */
			skb_reserve(skb, QL_HEADER_SPACE);
			map = dma_map_single(&qdev->pdev->dev, skb->data,
					     qdev->lrg_buffer_len - QL_HEADER_SPACE,
					     DMA_FROM_DEVICE);

			err = dma_mapping_error(&qdev->pdev->dev, map);
			अगर (err) अणु
				netdev_err(qdev->ndev,
					   "PCI mapping failed with error: %d\n",
					   err);
				dev_kमुक्त_skb_irq(skb);
				ql_मुक्त_large_buffers(qdev);
				वापस -ENOMEM;
			पूर्ण

			lrg_buf_cb->skb = skb;
			dma_unmap_addr_set(lrg_buf_cb, mapaddr, map);
			dma_unmap_len_set(lrg_buf_cb, maplen,
					  qdev->lrg_buffer_len -
					  QL_HEADER_SPACE);
			lrg_buf_cb->buf_phy_addr_low =
			    cpu_to_le32(LS_64BITS(map));
			lrg_buf_cb->buf_phy_addr_high =
			    cpu_to_le32(MS_64BITS(map));
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ql_मुक्त_send_मुक्त_list(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql_tx_buf_cb *tx_cb;
	पूर्णांक i;

	tx_cb = &qdev->tx_buf[0];
	क्रम (i = 0; i < NUM_REQ_Q_ENTRIES; i++) अणु
		kमुक्त(tx_cb->oal);
		tx_cb->oal = शून्य;
		tx_cb++;
	पूर्ण
पूर्ण

अटल पूर्णांक ql_create_send_मुक्त_list(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql_tx_buf_cb *tx_cb;
	पूर्णांक i;
	काष्ठा ob_mac_iocb_req *req_q_curr = qdev->req_q_virt_addr;

	/* Create मुक्त list of transmit buffers */
	क्रम (i = 0; i < NUM_REQ_Q_ENTRIES; i++) अणु

		tx_cb = &qdev->tx_buf[i];
		tx_cb->skb = शून्य;
		tx_cb->queue_entry = req_q_curr;
		req_q_curr++;
		tx_cb->oal = kदो_स्मृति(512, GFP_KERNEL);
		अगर (tx_cb->oal == शून्य)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ql_alloc_mem_resources(काष्ठा ql3_adapter *qdev)
अणु
	अगर (qdev->ndev->mtu == NORMAL_MTU_SIZE) अणु
		qdev->num_lbufq_entries = NUM_LBUFQ_ENTRIES;
		qdev->lrg_buffer_len = NORMAL_MTU_SIZE;
	पूर्ण अन्यथा अगर (qdev->ndev->mtu == JUMBO_MTU_SIZE) अणु
		/*
		 * Bigger buffers, so less of them.
		 */
		qdev->num_lbufq_entries = JUMBO_NUM_LBUFQ_ENTRIES;
		qdev->lrg_buffer_len = JUMBO_MTU_SIZE;
	पूर्ण अन्यथा अणु
		netdev_err(qdev->ndev, "Invalid mtu size: %d.  Only %d and %d are accepted.\n",
			   qdev->ndev->mtu, NORMAL_MTU_SIZE, JUMBO_MTU_SIZE);
		वापस -ENOMEM;
	पूर्ण
	qdev->num_large_buffers =
		qdev->num_lbufq_entries * QL_ADDR_ELE_PER_BUFQ_ENTRY;
	qdev->lrg_buffer_len += VLAN_ETH_HLEN + VLAN_ID_LEN + QL_HEADER_SPACE;
	qdev->max_frame_size =
		(qdev->lrg_buffer_len - QL_HEADER_SPACE) + ETHERNET_CRC_SIZE;

	/*
	 * First allocate a page of shared memory and use it क्रम shaकरोw
	 * locations of Network Request Queue Consumer Address Register and
	 * Network Completion Queue Producer Index Register
	 */
	qdev->shaकरोw_reg_virt_addr =
		dma_alloc_coherent(&qdev->pdev->dev, PAGE_SIZE,
				   &qdev->shaकरोw_reg_phy_addr, GFP_KERNEL);

	अगर (qdev->shaकरोw_reg_virt_addr != शून्य) अणु
		qdev->preq_consumer_index = qdev->shaकरोw_reg_virt_addr;
		qdev->req_consumer_index_phy_addr_high =
			MS_64BITS(qdev->shaकरोw_reg_phy_addr);
		qdev->req_consumer_index_phy_addr_low =
			LS_64BITS(qdev->shaकरोw_reg_phy_addr);

		qdev->prsp_producer_index =
			(__le32 *) (((u8 *) qdev->preq_consumer_index) + 8);
		qdev->rsp_producer_index_phy_addr_high =
			qdev->req_consumer_index_phy_addr_high;
		qdev->rsp_producer_index_phy_addr_low =
			qdev->req_consumer_index_phy_addr_low + 8;
	पूर्ण अन्यथा अणु
		netdev_err(qdev->ndev, "shadowReg Alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (ql_alloc_net_req_rsp_queues(qdev) != 0) अणु
		netdev_err(qdev->ndev, "ql_alloc_net_req_rsp_queues failed\n");
		जाओ err_req_rsp;
	पूर्ण

	अगर (ql_alloc_buffer_queues(qdev) != 0) अणु
		netdev_err(qdev->ndev, "ql_alloc_buffer_queues failed\n");
		जाओ err_buffer_queues;
	पूर्ण

	अगर (ql_alloc_small_buffers(qdev) != 0) अणु
		netdev_err(qdev->ndev, "ql_alloc_small_buffers failed\n");
		जाओ err_small_buffers;
	पूर्ण

	अगर (ql_alloc_large_buffers(qdev) != 0) अणु
		netdev_err(qdev->ndev, "ql_alloc_large_buffers failed\n");
		जाओ err_small_buffers;
	पूर्ण

	/* Initialize the large buffer queue. */
	ql_init_large_buffers(qdev);
	अगर (ql_create_send_मुक्त_list(qdev))
		जाओ err_मुक्त_list;

	qdev->rsp_current = qdev->rsp_q_virt_addr;

	वापस 0;
err_मुक्त_list:
	ql_मुक्त_send_मुक्त_list(qdev);
err_small_buffers:
	ql_मुक्त_buffer_queues(qdev);
err_buffer_queues:
	ql_मुक्त_net_req_rsp_queues(qdev);
err_req_rsp:
	dma_मुक्त_coherent(&qdev->pdev->dev, PAGE_SIZE,
			  qdev->shaकरोw_reg_virt_addr,
			  qdev->shaकरोw_reg_phy_addr);

	वापस -ENOMEM;
पूर्ण

अटल व्योम ql_मुक्त_mem_resources(काष्ठा ql3_adapter *qdev)
अणु
	ql_मुक्त_send_मुक्त_list(qdev);
	ql_मुक्त_large_buffers(qdev);
	ql_मुक्त_small_buffers(qdev);
	ql_मुक्त_buffer_queues(qdev);
	ql_मुक्त_net_req_rsp_queues(qdev);
	अगर (qdev->shaकरोw_reg_virt_addr != शून्य) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev, PAGE_SIZE,
				  qdev->shaकरोw_reg_virt_addr,
				  qdev->shaकरोw_reg_phy_addr);
		qdev->shaकरोw_reg_virt_addr = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ql_init_misc_रेजिस्टरs(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_local_ram_रेजिस्टरs __iomem *local_ram =
	    (व्योम __iomem *)qdev->mem_map_रेजिस्टरs;

	अगर (ql_sem_spinlock(qdev, QL_DDR_RAM_SEM_MASK,
			(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 4))
		वापस -1;

	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->bufletSize, qdev->nvram_data.bufletSize);

	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->maxBufletCount,
			   qdev->nvram_data.bufletCount);

	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->मुक्तBufletThresholdLow,
			   (qdev->nvram_data.tcpWinकरोwThreshold25 << 16) |
			   (qdev->nvram_data.tcpWinकरोwThreshold0));

	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->मुक्तBufletThresholdHigh,
			   qdev->nvram_data.tcpWinकरोwThreshold50);

	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->ipHashTableBase,
			   (qdev->nvram_data.ipHashTableBaseHi << 16) |
			   qdev->nvram_data.ipHashTableBaseLo);
	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->ipHashTableCount,
			   qdev->nvram_data.ipHashTableSize);
	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->tcpHashTableBase,
			   (qdev->nvram_data.tcpHashTableBaseHi << 16) |
			   qdev->nvram_data.tcpHashTableBaseLo);
	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->tcpHashTableCount,
			   qdev->nvram_data.tcpHashTableSize);
	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->ncbBase,
			   (qdev->nvram_data.ncbTableBaseHi << 16) |
			   qdev->nvram_data.ncbTableBaseLo);
	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->maxNcbCount,
			   qdev->nvram_data.ncbTableSize);
	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->drbBase,
			   (qdev->nvram_data.drbTableBaseHi << 16) |
			   qdev->nvram_data.drbTableBaseLo);
	ql_ग_लिखो_page2_reg(qdev,
			   &local_ram->maxDrbCount,
			   qdev->nvram_data.drbTableSize);
	ql_sem_unlock(qdev, QL_DDR_RAM_SEM_MASK);
	वापस 0;
पूर्ण

अटल पूर्णांक ql_adapter_initialize(काष्ठा ql3_adapter *qdev)
अणु
	u32 value;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	__iomem u32 *spir = &port_regs->CommonRegs.serialPortInterfaceReg;
	काष्ठा ql3xxx_host_memory_रेजिस्टरs __iomem *hmem_regs =
		(व्योम __iomem *)port_regs;
	u32 delay = 10;
	पूर्णांक status = 0;

	अगर (ql_mii_setup(qdev))
		वापस -1;

	/* Bring out PHY out of reset */
	ql_ग_लिखो_common_reg(qdev, spir,
			    (ISP_SERIAL_PORT_IF_WE |
			     (ISP_SERIAL_PORT_IF_WE << 16)));
	/* Give the PHY समय to come out of reset. */
	mdelay(100);
	qdev->port_link_state = LS_DOWN;
	netअगर_carrier_off(qdev->ndev);

	/* V2 chip fix क्रम ARS-39168. */
	ql_ग_लिखो_common_reg(qdev, spir,
			    (ISP_SERIAL_PORT_IF_SDE |
			     (ISP_SERIAL_PORT_IF_SDE << 16)));

	/* Request Queue Registers */
	*((u32 *)(qdev->preq_consumer_index)) = 0;
	atomic_set(&qdev->tx_count, NUM_REQ_Q_ENTRIES);
	qdev->req_producer_index = 0;

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->reqConsumerIndexAddrHigh,
			   qdev->req_consumer_index_phy_addr_high);
	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->reqConsumerIndexAddrLow,
			   qdev->req_consumer_index_phy_addr_low);

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->reqBaseAddrHigh,
			   MS_64BITS(qdev->req_q_phy_addr));
	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->reqBaseAddrLow,
			   LS_64BITS(qdev->req_q_phy_addr));
	ql_ग_लिखो_page1_reg(qdev, &hmem_regs->reqLength, NUM_REQ_Q_ENTRIES);

	/* Response Queue Registers */
	*((__le16 *) (qdev->prsp_producer_index)) = 0;
	qdev->rsp_consumer_index = 0;
	qdev->rsp_current = qdev->rsp_q_virt_addr;

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rspProducerIndexAddrHigh,
			   qdev->rsp_producer_index_phy_addr_high);

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rspProducerIndexAddrLow,
			   qdev->rsp_producer_index_phy_addr_low);

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rspBaseAddrHigh,
			   MS_64BITS(qdev->rsp_q_phy_addr));

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rspBaseAddrLow,
			   LS_64BITS(qdev->rsp_q_phy_addr));

	ql_ग_लिखो_page1_reg(qdev, &hmem_regs->rspLength, NUM_RSP_Q_ENTRIES);

	/* Large Buffer Queue */
	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rxLargeQBaseAddrHigh,
			   MS_64BITS(qdev->lrg_buf_q_phy_addr));

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rxLargeQBaseAddrLow,
			   LS_64BITS(qdev->lrg_buf_q_phy_addr));

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rxLargeQLength,
			   qdev->num_lbufq_entries);

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rxLargeBufferLength,
			   qdev->lrg_buffer_len);

	/* Small Buffer Queue */
	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rxSmallQBaseAddrHigh,
			   MS_64BITS(qdev->small_buf_q_phy_addr));

	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rxSmallQBaseAddrLow,
			   LS_64BITS(qdev->small_buf_q_phy_addr));

	ql_ग_लिखो_page1_reg(qdev, &hmem_regs->rxSmallQLength, NUM_SBUFQ_ENTRIES);
	ql_ग_लिखो_page1_reg(qdev,
			   &hmem_regs->rxSmallBufferLength,
			   QL_SMALL_BUFFER_SIZE);

	qdev->small_buf_q_producer_index = NUM_SBUFQ_ENTRIES - 1;
	qdev->small_buf_release_cnt = 8;
	qdev->lrg_buf_q_producer_index = qdev->num_lbufq_entries - 1;
	qdev->lrg_buf_release_cnt = 8;
	qdev->lrg_buf_next_मुक्त = qdev->lrg_buf_q_virt_addr;
	qdev->small_buf_index = 0;
	qdev->lrg_buf_index = 0;
	qdev->lrg_buf_मुक्त_count = 0;
	qdev->lrg_buf_मुक्त_head = शून्य;
	qdev->lrg_buf_मुक्त_tail = शून्य;

	ql_ग_लिखो_common_reg(qdev,
			    &port_regs->CommonRegs.
			    rxSmallQProducerIndex,
			    qdev->small_buf_q_producer_index);
	ql_ग_लिखो_common_reg(qdev,
			    &port_regs->CommonRegs.
			    rxLargeQProducerIndex,
			    qdev->lrg_buf_q_producer_index);

	/*
	 * Find out अगर the chip has alपढ़ोy been initialized.  If it has, then
	 * we skip some of the initialization.
	 */
	clear_bit(QL_LINK_MASTER, &qdev->flags);
	value = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
	अगर ((value & PORT_STATUS_IC) == 0) अणु

		/* Chip has not been configured yet, so let it rip. */
		अगर (ql_init_misc_रेजिस्टरs(qdev)) अणु
			status = -1;
			जाओ out;
		पूर्ण

		value = qdev->nvram_data.tcpMaxWinकरोwSize;
		ql_ग_लिखो_page0_reg(qdev, &port_regs->tcpMaxWinकरोw, value);

		value = (0xFFFF << 16) | qdev->nvram_data.extHwConfig;

		अगर (ql_sem_spinlock(qdev, QL_FLASH_SEM_MASK,
				(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index)
				 * 2) << 13)) अणु
			status = -1;
			जाओ out;
		पूर्ण
		ql_ग_लिखो_page0_reg(qdev, &port_regs->ExternalHWConfig, value);
		ql_ग_लिखो_page0_reg(qdev, &port_regs->InternalChipConfig,
				   (((INTERNAL_CHIP_SD | INTERNAL_CHIP_WE) <<
				     16) | (INTERNAL_CHIP_SD |
					    INTERNAL_CHIP_WE)));
		ql_sem_unlock(qdev, QL_FLASH_SEM_MASK);
	पूर्ण

	अगर (qdev->mac_index)
		ql_ग_लिखो_page0_reg(qdev,
				   &port_regs->mac1MaxFrameLengthReg,
				   qdev->max_frame_size);
	अन्यथा
		ql_ग_लिखो_page0_reg(qdev,
					   &port_regs->mac0MaxFrameLengthReg,
					   qdev->max_frame_size);

	अगर (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
			(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 7)) अणु
		status = -1;
		जाओ out;
	पूर्ण

	PHY_Setup(qdev);
	ql_init_scan_mode(qdev);
	ql_get_phy_owner(qdev);

	/* Load the MAC Configuration */

	/* Program lower 32 bits of the MAC address */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrIndirectPtrReg,
			   (MAC_ADDR_INसूचीECT_PTR_REG_RP_MASK << 16));
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrDataReg,
			   ((qdev->ndev->dev_addr[2] << 24)
			    | (qdev->ndev->dev_addr[3] << 16)
			    | (qdev->ndev->dev_addr[4] << 8)
			    | qdev->ndev->dev_addr[5]));

	/* Program top 16 bits of the MAC address */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrIndirectPtrReg,
			   ((MAC_ADDR_INसूचीECT_PTR_REG_RP_MASK << 16) | 1));
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrDataReg,
			   ((qdev->ndev->dev_addr[0] << 8)
			    | qdev->ndev->dev_addr[1]));

	/* Enable Primary MAC */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrIndirectPtrReg,
			   ((MAC_ADDR_INसूचीECT_PTR_REG_PE << 16) |
			    MAC_ADDR_INसूचीECT_PTR_REG_PE));

	/* Clear Primary and Secondary IP addresses */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->ipAddrIndexReg,
			   ((IP_ADDR_INDEX_REG_MASK << 16) |
			    (qdev->mac_index << 2)));
	ql_ग_लिखो_page0_reg(qdev, &port_regs->ipAddrDataReg, 0);

	ql_ग_लिखो_page0_reg(qdev, &port_regs->ipAddrIndexReg,
			   ((IP_ADDR_INDEX_REG_MASK << 16) |
			    ((qdev->mac_index << 2) + 1)));
	ql_ग_लिखो_page0_reg(qdev, &port_regs->ipAddrDataReg, 0);

	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);

	/* Indicate Configuration Complete */
	ql_ग_लिखो_page0_reg(qdev,
			   &port_regs->portControl,
			   ((PORT_CONTROL_CC << 16) | PORT_CONTROL_CC));

	करो अणु
		value = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
		अगर (value & PORT_STATUS_IC)
			अवरोध;
		spin_unlock_irq(&qdev->hw_lock);
		msleep(500);
		spin_lock_irq(&qdev->hw_lock);
	पूर्ण जबतक (--delay);

	अगर (delay == 0) अणु
		netdev_err(qdev->ndev, "Hw Initialization timeout\n");
		status = -1;
		जाओ out;
	पूर्ण

	/* Enable Ethernet Function */
	अगर (qdev->device_id == QL3032_DEVICE_ID) अणु
		value =
		    (QL3032_PORT_CONTROL_EF | QL3032_PORT_CONTROL_KIE |
		     QL3032_PORT_CONTROL_EIv6 | QL3032_PORT_CONTROL_EIv4 |
			QL3032_PORT_CONTROL_ET);
		ql_ग_लिखो_page0_reg(qdev, &port_regs->functionControl,
				   ((value << 16) | value));
	पूर्ण अन्यथा अणु
		value =
		    (PORT_CONTROL_EF | PORT_CONTROL_ET | PORT_CONTROL_EI |
		     PORT_CONTROL_HH);
		ql_ग_लिखो_page0_reg(qdev, &port_regs->portControl,
				   ((value << 16) | value));
	पूर्ण


out:
	वापस status;
पूर्ण

/*
 * Caller holds hw_lock.
 */
अटल पूर्णांक ql_adapter_reset(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	पूर्णांक status = 0;
	u16 value;
	पूर्णांक max_रुको_समय;

	set_bit(QL_RESET_ACTIVE, &qdev->flags);
	clear_bit(QL_RESET_DONE, &qdev->flags);

	/*
	 * Issue soft reset to chip.
	 */
	netdev_prपूर्णांकk(KERN_DEBUG, qdev->ndev, "Issue soft reset to chip\n");
	ql_ग_लिखो_common_reg(qdev,
			    &port_regs->CommonRegs.ispControlStatus,
			    ((ISP_CONTROL_SR << 16) | ISP_CONTROL_SR));

	/* Wait 3 seconds क्रम reset to complete. */
	netdev_prपूर्णांकk(KERN_DEBUG, qdev->ndev,
		      "Wait 10 milliseconds for reset to complete\n");

	/* Wait until the firmware tells us the Soft Reset is करोne */
	max_रुको_समय = 5;
	करो अणु
		value =
		    ql_पढ़ो_common_reg(qdev,
				       &port_regs->CommonRegs.ispControlStatus);
		अगर ((value & ISP_CONTROL_SR) == 0)
			अवरोध;

		ssleep(1);
	पूर्ण जबतक ((--max_रुको_समय));

	/*
	 * Also, make sure that the Network Reset Interrupt bit has been
	 * cleared after the soft reset has taken place.
	 */
	value =
	    ql_पढ़ो_common_reg(qdev, &port_regs->CommonRegs.ispControlStatus);
	अगर (value & ISP_CONTROL_RI) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, qdev->ndev,
			      "clearing RI after reset\n");
		ql_ग_लिखो_common_reg(qdev,
				    &port_regs->CommonRegs.
				    ispControlStatus,
				    ((ISP_CONTROL_RI << 16) | ISP_CONTROL_RI));
	पूर्ण

	अगर (max_रुको_समय == 0) अणु
		/* Issue Force Soft Reset */
		ql_ग_लिखो_common_reg(qdev,
				    &port_regs->CommonRegs.
				    ispControlStatus,
				    ((ISP_CONTROL_FSR << 16) |
				     ISP_CONTROL_FSR));
		/*
		 * Wait until the firmware tells us the Force Soft Reset is
		 * करोne
		 */
		max_रुको_समय = 5;
		करो अणु
			value = ql_पढ़ो_common_reg(qdev,
						   &port_regs->CommonRegs.
						   ispControlStatus);
			अगर ((value & ISP_CONTROL_FSR) == 0)
				अवरोध;
			ssleep(1);
		पूर्ण जबतक ((--max_रुको_समय));
	पूर्ण
	अगर (max_रुको_समय == 0)
		status = 1;

	clear_bit(QL_RESET_ACTIVE, &qdev->flags);
	set_bit(QL_RESET_DONE, &qdev->flags);
	वापस status;
पूर्ण

अटल व्योम ql_set_mac_info(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	u32 value, port_status;
	u8 func_number;

	/* Get the function number */
	value =
	    ql_पढ़ो_common_reg_l(qdev, &port_regs->CommonRegs.ispControlStatus);
	func_number = (u8) ((value >> 4) & OPCODE_FUNC_ID_MASK);
	port_status = ql_पढ़ो_page0_reg(qdev, &port_regs->portStatus);
	चयन (value & ISP_CONTROL_FN_MASK) अणु
	हाल ISP_CONTROL_FN0_NET:
		qdev->mac_index = 0;
		qdev->mac_ob_opcode = OUTBOUND_MAC_IOCB | func_number;
		qdev->mb_bit_mask = FN0_MA_BITS_MASK;
		qdev->PHYAddr = PORT0_PHY_ADDRESS;
		अगर (port_status & PORT_STATUS_SM0)
			set_bit(QL_LINK_OPTICAL, &qdev->flags);
		अन्यथा
			clear_bit(QL_LINK_OPTICAL, &qdev->flags);
		अवरोध;

	हाल ISP_CONTROL_FN1_NET:
		qdev->mac_index = 1;
		qdev->mac_ob_opcode = OUTBOUND_MAC_IOCB | func_number;
		qdev->mb_bit_mask = FN1_MA_BITS_MASK;
		qdev->PHYAddr = PORT1_PHY_ADDRESS;
		अगर (port_status & PORT_STATUS_SM1)
			set_bit(QL_LINK_OPTICAL, &qdev->flags);
		अन्यथा
			clear_bit(QL_LINK_OPTICAL, &qdev->flags);
		अवरोध;

	हाल ISP_CONTROL_FN0_SCSI:
	हाल ISP_CONTROL_FN1_SCSI:
	शेष:
		netdev_prपूर्णांकk(KERN_DEBUG, qdev->ndev,
			      "Invalid function number, ispControlStatus = 0x%x\n",
			      value);
		अवरोध;
	पूर्ण
	qdev->numPorts = qdev->nvram_data.version_and_numPorts >> 8;
पूर्ण

अटल व्योम ql_display_dev_info(काष्ठा net_device *ndev)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	काष्ठा pci_dev *pdev = qdev->pdev;

	netdev_info(ndev,
		    "%s Adapter %d RevisionID %d found %s on PCI slot %d\n",
		    DRV_NAME, qdev->index, qdev->chip_rev_id,
		    qdev->device_id == QL3032_DEVICE_ID ? "QLA3032" : "QLA3022",
		    qdev->pci_slot);
	netdev_info(ndev, "%s Interface\n",
		test_bit(QL_LINK_OPTICAL, &qdev->flags) ? "OPTICAL" : "COPPER");

	/*
	 * Prपूर्णांक PCI bus width/type.
	 */
	netdev_info(ndev, "Bus interface is %s %s\n",
		    ((qdev->pci_width == 64) ? "64-bit" : "32-bit"),
		    ((qdev->pci_x) ? "PCI-X" : "PCI"));

	netdev_info(ndev, "mem  IO base address adjusted = 0x%p\n",
		    qdev->mem_map_रेजिस्टरs);
	netdev_info(ndev, "Interrupt number = %d\n", pdev->irq);

	netअगर_info(qdev, probe, ndev, "MAC address %pM\n", ndev->dev_addr);
पूर्ण

अटल पूर्णांक ql_adapter_करोwn(काष्ठा ql3_adapter *qdev, पूर्णांक करो_reset)
अणु
	काष्ठा net_device *ndev = qdev->ndev;
	पूर्णांक retval = 0;

	netअगर_stop_queue(ndev);
	netअगर_carrier_off(ndev);

	clear_bit(QL_ADAPTER_UP, &qdev->flags);
	clear_bit(QL_LINK_MASTER, &qdev->flags);

	ql_disable_पूर्णांकerrupts(qdev);

	मुक्त_irq(qdev->pdev->irq, ndev);

	अगर (qdev->msi && test_bit(QL_MSI_ENABLED, &qdev->flags)) अणु
		netdev_info(qdev->ndev, "calling pci_disable_msi()\n");
		clear_bit(QL_MSI_ENABLED, &qdev->flags);
		pci_disable_msi(qdev->pdev);
	पूर्ण

	del_समयr_sync(&qdev->adapter_समयr);

	napi_disable(&qdev->napi);

	अगर (करो_reset) अणु
		पूर्णांक soft_reset;
		अचिन्हित दीर्घ hw_flags;

		spin_lock_irqsave(&qdev->hw_lock, hw_flags);
		अगर (ql_रुको_क्रम_drvr_lock(qdev)) अणु
			soft_reset = ql_adapter_reset(qdev);
			अगर (soft_reset) अणु
				netdev_err(ndev, "ql_adapter_reset(%d) FAILED!\n",
					   qdev->index);
			पूर्ण
			netdev_err(ndev,
				   "Releasing driver lock via chip reset\n");
		पूर्ण अन्यथा अणु
			netdev_err(ndev,
				   "Could not acquire driver lock to do reset!\n");
			retval = -1;
		पूर्ण
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	पूर्ण
	ql_मुक्त_mem_resources(qdev);
	वापस retval;
पूर्ण

अटल पूर्णांक ql_adapter_up(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा net_device *ndev = qdev->ndev;
	पूर्णांक err;
	अचिन्हित दीर्घ irq_flags = IRQF_SHARED;
	अचिन्हित दीर्घ hw_flags;

	अगर (ql_alloc_mem_resources(qdev)) अणु
		netdev_err(ndev, "Unable to  allocate buffers\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (qdev->msi) अणु
		अगर (pci_enable_msi(qdev->pdev)) अणु
			netdev_err(ndev,
				   "User requested MSI, but MSI failed to initialize.  Continuing without MSI.\n");
			qdev->msi = 0;
		पूर्ण अन्यथा अणु
			netdev_info(ndev, "MSI Enabled...\n");
			set_bit(QL_MSI_ENABLED, &qdev->flags);
			irq_flags &= ~IRQF_SHARED;
		पूर्ण
	पूर्ण

	err = request_irq(qdev->pdev->irq, ql3xxx_isr,
			  irq_flags, ndev->name, ndev);
	अगर (err) अणु
		netdev_err(ndev,
			   "Failed to reserve interrupt %d - already in use\n",
			   qdev->pdev->irq);
		जाओ err_irq;
	पूर्ण

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);

	err = ql_रुको_क्रम_drvr_lock(qdev);
	अगर (err) अणु
		err = ql_adapter_initialize(qdev);
		अगर (err) अणु
			netdev_err(ndev, "Unable to initialize adapter\n");
			जाओ err_init;
		पूर्ण
		netdev_err(ndev, "Releasing driver lock\n");
		ql_sem_unlock(qdev, QL_DRVR_SEM_MASK);
	पूर्ण अन्यथा अणु
		netdev_err(ndev, "Could not acquire driver lock\n");
		जाओ err_lock;
	पूर्ण

	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);

	set_bit(QL_ADAPTER_UP, &qdev->flags);

	mod_समयr(&qdev->adapter_समयr, jअगरfies + HZ * 1);

	napi_enable(&qdev->napi);
	ql_enable_पूर्णांकerrupts(qdev);
	वापस 0;

err_init:
	ql_sem_unlock(qdev, QL_DRVR_SEM_MASK);
err_lock:
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	मुक्त_irq(qdev->pdev->irq, ndev);
err_irq:
	अगर (qdev->msi && test_bit(QL_MSI_ENABLED, &qdev->flags)) अणु
		netdev_info(ndev, "calling pci_disable_msi()\n");
		clear_bit(QL_MSI_ENABLED, &qdev->flags);
		pci_disable_msi(qdev->pdev);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ql_cycle_adapter(काष्ठा ql3_adapter *qdev, पूर्णांक reset)
अणु
	अगर (ql_adapter_करोwn(qdev, reset) || ql_adapter_up(qdev)) अणु
		netdev_err(qdev->ndev,
			   "Driver up/down cycle failed, closing device\n");
		rtnl_lock();
		dev_बंद(qdev->ndev);
		rtnl_unlock();
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ql3xxx_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);

	/*
	 * Wait क्रम device to recover from a reset.
	 * (Rarely happens, but possible.)
	 */
	जबतक (!test_bit(QL_ADAPTER_UP, &qdev->flags))
		msleep(50);

	ql_adapter_करोwn(qdev, QL_DO_RESET);
	वापस 0;
पूर्ण

अटल पूर्णांक ql3xxx_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	वापस ql_adapter_up(qdev);
पूर्ण

अटल पूर्णांक ql3xxx_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
			qdev->mem_map_रेजिस्टरs;
	काष्ठा sockaddr *addr = p;
	अचिन्हित दीर्घ hw_flags;

	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(ndev->dev_addr, addr->sa_data, ndev->addr_len);

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	/* Program lower 32 bits of the MAC address */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrIndirectPtrReg,
			   (MAC_ADDR_INसूचीECT_PTR_REG_RP_MASK << 16));
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrDataReg,
			   ((ndev->dev_addr[2] << 24) | (ndev->
							 dev_addr[3] << 16) |
			    (ndev->dev_addr[4] << 8) | ndev->dev_addr[5]));

	/* Program top 16 bits of the MAC address */
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrIndirectPtrReg,
			   ((MAC_ADDR_INसूचीECT_PTR_REG_RP_MASK << 16) | 1));
	ql_ग_लिखो_page0_reg(qdev, &port_regs->macAddrDataReg,
			   ((ndev->dev_addr[0] << 8) | ndev->dev_addr[1]));
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);

	वापस 0;
पूर्ण

अटल व्योम ql3xxx_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);

	netdev_err(ndev, "Resetting...\n");
	/*
	 * Stop the queues, we've got a problem.
	 */
	netअगर_stop_queue(ndev);

	/*
	 * Wake up the worker to process this event.
	 */
	queue_delayed_work(qdev->workqueue, &qdev->tx_समयout_work, 0);
पूर्ण

अटल व्योम ql_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ql3_adapter *qdev =
		container_of(work, काष्ठा ql3_adapter, reset_work.work);
	काष्ठा net_device *ndev = qdev->ndev;
	u32 value;
	काष्ठा ql_tx_buf_cb *tx_cb;
	पूर्णांक max_रुको_समय, i;
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	अचिन्हित दीर्घ hw_flags;

	अगर (test_bit((QL_RESET_PER_SCSI | QL_RESET_START), &qdev->flags)) अणु
		clear_bit(QL_LINK_MASTER, &qdev->flags);

		/*
		 * Loop through the active list and वापस the skb.
		 */
		क्रम (i = 0; i < NUM_REQ_Q_ENTRIES; i++) अणु
			पूर्णांक j;
			tx_cb = &qdev->tx_buf[i];
			अगर (tx_cb->skb) अणु
				netdev_prपूर्णांकk(KERN_DEBUG, ndev,
					      "Freeing lost SKB\n");
				dma_unmap_single(&qdev->pdev->dev,
						 dma_unmap_addr(&tx_cb->map[0], mapaddr),
						 dma_unmap_len(&tx_cb->map[0], maplen),
						 DMA_TO_DEVICE);
				क्रम (j = 1; j < tx_cb->seg_count; j++) अणु
					dma_unmap_page(&qdev->pdev->dev,
						       dma_unmap_addr(&tx_cb->map[j], mapaddr),
						       dma_unmap_len(&tx_cb->map[j], maplen),
						       DMA_TO_DEVICE);
				पूर्ण
				dev_kमुक्त_skb(tx_cb->skb);
				tx_cb->skb = शून्य;
			पूर्ण
		पूर्ण

		netdev_err(ndev, "Clearing NRI after reset\n");
		spin_lock_irqsave(&qdev->hw_lock, hw_flags);
		ql_ग_लिखो_common_reg(qdev,
				    &port_regs->CommonRegs.
				    ispControlStatus,
				    ((ISP_CONTROL_RI << 16) | ISP_CONTROL_RI));
		/*
		 * Wait the क्रम Soft Reset to Complete.
		 */
		max_रुको_समय = 10;
		करो अणु
			value = ql_पढ़ो_common_reg(qdev,
						   &port_regs->CommonRegs.

						   ispControlStatus);
			अगर ((value & ISP_CONTROL_SR) == 0) अणु
				netdev_prपूर्णांकk(KERN_DEBUG, ndev,
					      "reset completed\n");
				अवरोध;
			पूर्ण

			अगर (value & ISP_CONTROL_RI) अणु
				netdev_prपूर्णांकk(KERN_DEBUG, ndev,
					      "clearing NRI after reset\n");
				ql_ग_लिखो_common_reg(qdev,
						    &port_regs->
						    CommonRegs.
						    ispControlStatus,
						    ((ISP_CONTROL_RI <<
						      16) | ISP_CONTROL_RI));
			पूर्ण

			spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
			ssleep(1);
			spin_lock_irqsave(&qdev->hw_lock, hw_flags);
		पूर्ण जबतक (--max_रुको_समय);
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);

		अगर (value & ISP_CONTROL_SR) अणु

			/*
			 * Set the reset flags and clear the board again.
			 * Nothing अन्यथा to करो...
			 */
			netdev_err(ndev,
				   "Timed out waiting for reset to complete\n");
			netdev_err(ndev, "Do a reset\n");
			clear_bit(QL_RESET_PER_SCSI, &qdev->flags);
			clear_bit(QL_RESET_START, &qdev->flags);
			ql_cycle_adapter(qdev, QL_DO_RESET);
			वापस;
		पूर्ण

		clear_bit(QL_RESET_ACTIVE, &qdev->flags);
		clear_bit(QL_RESET_PER_SCSI, &qdev->flags);
		clear_bit(QL_RESET_START, &qdev->flags);
		ql_cycle_adapter(qdev, QL_NO_RESET);
	पूर्ण
पूर्ण

अटल व्योम ql_tx_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ql3_adapter *qdev =
		container_of(work, काष्ठा ql3_adapter, tx_समयout_work.work);

	ql_cycle_adapter(qdev, QL_DO_RESET);
पूर्ण

अटल व्योम ql_get_board_info(काष्ठा ql3_adapter *qdev)
अणु
	काष्ठा ql3xxx_port_रेजिस्टरs __iomem *port_regs =
		qdev->mem_map_रेजिस्टरs;
	u32 value;

	value = ql_पढ़ो_page0_reg_l(qdev, &port_regs->portStatus);

	qdev->chip_rev_id = ((value & PORT_STATUS_REV_ID_MASK) >> 12);
	अगर (value & PORT_STATUS_64)
		qdev->pci_width = 64;
	अन्यथा
		qdev->pci_width = 32;
	अगर (value & PORT_STATUS_X)
		qdev->pci_x = 1;
	अन्यथा
		qdev->pci_x = 0;
	qdev->pci_slot = (u8) PCI_SLOT(qdev->pdev->devfn);
पूर्ण

अटल व्योम ql3xxx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ql3_adapter *qdev = from_समयr(qdev, t, adapter_समयr);
	queue_delayed_work(qdev->workqueue, &qdev->link_state_work, 0);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ql3xxx_netdev_ops = अणु
	.nकरो_खोलो		= ql3xxx_खोलो,
	.nकरो_start_xmit		= ql3xxx_send,
	.nकरो_stop		= ql3xxx_बंद,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= ql3xxx_set_mac_address,
	.nकरो_tx_समयout		= ql3xxx_tx_समयout,
पूर्ण;

अटल पूर्णांक ql3xxx_probe(काष्ठा pci_dev *pdev,
			स्थिर काष्ठा pci_device_id *pci_entry)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा ql3_adapter *qdev = शून्य;
	अटल पूर्णांक cards_found;
	पूर्णांक pci_using_dac, err;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		pr_err("%s cannot enable PCI device\n", pci_name(pdev));
		जाओ err_out;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		pr_err("%s cannot obtain PCI resources\n", pci_name(pdev));
		जाओ err_out_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64)))
		pci_using_dac = 1;
	अन्यथा अगर (!(err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32))))
		pci_using_dac = 0;

	अगर (err) अणु
		pr_err("%s no usable DMA configuration\n", pci_name(pdev));
		जाओ err_out_मुक्त_regions;
	पूर्ण

	ndev = alloc_etherdev(माप(काष्ठा ql3_adapter));
	अगर (!ndev) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_regions;
	पूर्ण

	SET_NETDEV_DEV(ndev, &pdev->dev);

	pci_set_drvdata(pdev, ndev);

	qdev = netdev_priv(ndev);
	qdev->index = cards_found;
	qdev->ndev = ndev;
	qdev->pdev = pdev;
	qdev->device_id = pci_entry->device;
	qdev->port_link_state = LS_DOWN;
	अगर (msi)
		qdev->msi = 1;

	qdev->msg_enable = netअगर_msg_init(debug, शेष_msg);

	अगर (pci_using_dac)
		ndev->features |= NETIF_F_HIGHDMA;
	अगर (qdev->device_id == QL3032_DEVICE_ID)
		ndev->features |= NETIF_F_IP_CSUM | NETIF_F_SG;

	qdev->mem_map_रेजिस्टरs = pci_ioremap_bar(pdev, 1);
	अगर (!qdev->mem_map_रेजिस्टरs) अणु
		pr_err("%s: cannot map device registers\n", pci_name(pdev));
		err = -EIO;
		जाओ err_out_मुक्त_ndev;
	पूर्ण

	spin_lock_init(&qdev->adapter_lock);
	spin_lock_init(&qdev->hw_lock);

	/* Set driver entry poपूर्णांकs */
	ndev->netdev_ops = &ql3xxx_netdev_ops;
	ndev->ethtool_ops = &ql3xxx_ethtool_ops;
	ndev->watchकरोg_समयo = 5 * HZ;

	netअगर_napi_add(ndev, &qdev->napi, ql_poll, 64);

	ndev->irq = pdev->irq;

	/* make sure the EEPROM is good */
	अगर (ql_get_nvram_params(qdev)) अणु
		pr_alert("%s: Adapter #%d, Invalid NVRAM parameters\n",
			 __func__, qdev->index);
		err = -EIO;
		जाओ err_out_iounmap;
	पूर्ण

	ql_set_mac_info(qdev);

	/* Validate and set parameters */
	अगर (qdev->mac_index) अणु
		ndev->mtu = qdev->nvram_data.macCfg_port1.etherMtu_mac ;
		ql_set_mac_addr(ndev, qdev->nvram_data.funcCfg_fn2.macAddress);
	पूर्ण अन्यथा अणु
		ndev->mtu = qdev->nvram_data.macCfg_port0.etherMtu_mac ;
		ql_set_mac_addr(ndev, qdev->nvram_data.funcCfg_fn0.macAddress);
	पूर्ण

	ndev->tx_queue_len = NUM_REQ_Q_ENTRIES;

	/* Record PCI bus inक्रमmation. */
	ql_get_board_info(qdev);

	/*
	 * Set the Maximum Memory Read Byte Count value. We करो this to handle
	 * jumbo frames.
	 */
	अगर (qdev->pci_x)
		pci_ग_लिखो_config_word(pdev, (पूर्णांक)0x4e, (u16) 0x0036);

	err = रेजिस्टर_netdev(ndev);
	अगर (err) अणु
		pr_err("%s: cannot register net device\n", pci_name(pdev));
		जाओ err_out_iounmap;
	पूर्ण

	/* we're going to reset, so assume we have no link क्रम now */

	netअगर_carrier_off(ndev);
	netअगर_stop_queue(ndev);

	qdev->workqueue = create_singlethपढ़ो_workqueue(ndev->name);
	अगर (!qdev->workqueue) अणु
		unरेजिस्टर_netdev(ndev);
		err = -ENOMEM;
		जाओ err_out_iounmap;
	पूर्ण

	INIT_DELAYED_WORK(&qdev->reset_work, ql_reset_work);
	INIT_DELAYED_WORK(&qdev->tx_समयout_work, ql_tx_समयout_work);
	INIT_DELAYED_WORK(&qdev->link_state_work, ql_link_state_machine_work);

	समयr_setup(&qdev->adapter_समयr, ql3xxx_समयr, 0);
	qdev->adapter_समयr.expires = jअगरfies + HZ * 2;	/* two second delay */

	अगर (!cards_found) अणु
		pr_alert("%s\n", DRV_STRING);
		pr_alert("Driver name: %s, Version: %s\n",
			 DRV_NAME, DRV_VERSION);
	पूर्ण
	ql_display_dev_info(ndev);

	cards_found++;
	वापस 0;

err_out_iounmap:
	iounmap(qdev->mem_map_रेजिस्टरs);
err_out_मुक्त_ndev:
	मुक्त_netdev(ndev);
err_out_मुक्त_regions:
	pci_release_regions(pdev);
err_out_disable_pdev:
	pci_disable_device(pdev);
err_out:
	वापस err;
पूर्ण

अटल व्योम ql3xxx_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *ndev = pci_get_drvdata(pdev);
	काष्ठा ql3_adapter *qdev = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);

	ql_disable_पूर्णांकerrupts(qdev);

	अगर (qdev->workqueue) अणु
		cancel_delayed_work(&qdev->reset_work);
		cancel_delayed_work(&qdev->tx_समयout_work);
		destroy_workqueue(qdev->workqueue);
		qdev->workqueue = शून्य;
	पूर्ण

	iounmap(qdev->mem_map_रेजिस्टरs);
	pci_release_regions(pdev);
	मुक्त_netdev(ndev);
पूर्ण

अटल काष्ठा pci_driver ql3xxx_driver = अणु

	.name = DRV_NAME,
	.id_table = ql3xxx_pci_tbl,
	.probe = ql3xxx_probe,
	.हटाओ = ql3xxx_हटाओ,
पूर्ण;

module_pci_driver(ql3xxx_driver);
