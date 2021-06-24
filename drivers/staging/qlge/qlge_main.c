<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlge NIC HBA Driver
 * Copyright (c)  2003-2008 QLogic Corporation
 * Author:     Linux qlge network device driver by
 *                      Ron Mercer <ron.mercer@qlogic.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/mempool.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/prefetch.h>
#समावेश <net/ip6_checksum.h>

#समावेश "qlge.h"
#समावेश "qlge_devlink.h"

अक्षर qlge_driver_name[] = DRV_NAME;
स्थिर अक्षर qlge_driver_version[] = DRV_VERSION;

MODULE_AUTHOR("Ron Mercer <ron.mercer@qlogic.com>");
MODULE_DESCRIPTION(DRV_STRING " ");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

अटल स्थिर u32 शेष_msg =
	NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK |
	NETIF_MSG_IFDOWN |
	NETIF_MSG_IFUP |
	NETIF_MSG_RX_ERR |
	NETIF_MSG_TX_ERR |
	NETIF_MSG_HW | NETIF_MSG_WOL | 0;

अटल पूर्णांक debug = -1;	/* शेषs above */
module_param(debug, पूर्णांक, 0664);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

#घोषणा MSIX_IRQ 0
#घोषणा MSI_IRQ 1
#घोषणा LEG_IRQ 2
अटल पूर्णांक qlge_irq_type = MSIX_IRQ;
module_param(qlge_irq_type, पूर्णांक, 0664);
MODULE_PARM_DESC(qlge_irq_type, "0 = MSI-X, 1 = MSI, 2 = Legacy.");

अटल पूर्णांक qlge_mpi_coredump;
module_param(qlge_mpi_coredump, पूर्णांक, 0);
MODULE_PARM_DESC(qlge_mpi_coredump,
		 "Option to enable MPI firmware dump. Default is OFF - Do Not allocate memory. ");

अटल पूर्णांक qlge_क्रमce_coredump;
module_param(qlge_क्रमce_coredump, पूर्णांक, 0);
MODULE_PARM_DESC(qlge_क्रमce_coredump,
		 "Option to allow force of firmware core dump. Default is OFF - Do not allow.");

अटल स्थिर काष्ठा pci_device_id qlge_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_QLOGIC, QLGE_DEVICE_ID_8012)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_QLOGIC, QLGE_DEVICE_ID_8000)पूर्ण,
	/* required last entry */
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, qlge_pci_tbl);

अटल पूर्णांक qlge_wol(काष्ठा qlge_adapter *);
अटल व्योम qlge_set_multicast_list(काष्ठा net_device *);
अटल पूर्णांक qlge_adapter_करोwn(काष्ठा qlge_adapter *);
अटल पूर्णांक qlge_adapter_up(काष्ठा qlge_adapter *);

/* This hardware semaphore causes exclusive access to
 * resources shared between the NIC driver, MPI firmware,
 * FCOE firmware and the FC driver.
 */
अटल पूर्णांक qlge_sem_trylock(काष्ठा qlge_adapter *qdev, u32 sem_mask)
अणु
	u32 sem_bits = 0;

	चयन (sem_mask) अणु
	हाल SEM_XGMAC0_MASK:
		sem_bits = SEM_SET << SEM_XGMAC0_SHIFT;
		अवरोध;
	हाल SEM_XGMAC1_MASK:
		sem_bits = SEM_SET << SEM_XGMAC1_SHIFT;
		अवरोध;
	हाल SEM_ICB_MASK:
		sem_bits = SEM_SET << SEM_ICB_SHIFT;
		अवरोध;
	हाल SEM_MAC_ADDR_MASK:
		sem_bits = SEM_SET << SEM_MAC_ADDR_SHIFT;
		अवरोध;
	हाल SEM_FLASH_MASK:
		sem_bits = SEM_SET << SEM_FLASH_SHIFT;
		अवरोध;
	हाल SEM_PROBE_MASK:
		sem_bits = SEM_SET << SEM_PROBE_SHIFT;
		अवरोध;
	हाल SEM_RT_IDX_MASK:
		sem_bits = SEM_SET << SEM_RT_IDX_SHIFT;
		अवरोध;
	हाल SEM_PROC_REG_MASK:
		sem_bits = SEM_SET << SEM_PROC_REG_SHIFT;
		अवरोध;
	शेष:
		netअगर_alert(qdev, probe, qdev->ndev, "bad Semaphore mask!.\n");
		वापस -EINVAL;
	पूर्ण

	qlge_ग_लिखो32(qdev, SEM, sem_bits | sem_mask);
	वापस !(qlge_पढ़ो32(qdev, SEM) & sem_bits);
पूर्ण

पूर्णांक qlge_sem_spinlock(काष्ठा qlge_adapter *qdev, u32 sem_mask)
अणु
	अचिन्हित पूर्णांक रुको_count = 30;

	करो अणु
		अगर (!qlge_sem_trylock(qdev, sem_mask))
			वापस 0;
		udelay(100);
	पूर्ण जबतक (--रुको_count);
	वापस -ETIMEDOUT;
पूर्ण

व्योम qlge_sem_unlock(काष्ठा qlge_adapter *qdev, u32 sem_mask)
अणु
	qlge_ग_लिखो32(qdev, SEM, sem_mask);
	qlge_पढ़ो32(qdev, SEM);	/* flush */
पूर्ण

/* This function रुकोs क्रम a specअगरic bit to come पढ़ोy
 * in a given रेजिस्टर.  It is used mostly by the initialize
 * process, but is also used in kernel thपढ़ो API such as
 * netdev->set_multi, netdev->set_mac_address, netdev->vlan_rx_add_vid.
 */
पूर्णांक qlge_रुको_reg_rdy(काष्ठा qlge_adapter *qdev, u32 reg, u32 bit, u32 err_bit)
अणु
	u32 temp;
	पूर्णांक count;

	क्रम (count = 0; count < UDELAY_COUNT; count++) अणु
		temp = qlge_पढ़ो32(qdev, reg);

		/* check क्रम errors */
		अगर (temp & err_bit) अणु
			netअगर_alert(qdev, probe, qdev->ndev,
				    "register 0x%.08x access error, value = 0x%.08x!.\n",
				    reg, temp);
			वापस -EIO;
		पूर्ण अन्यथा अगर (temp & bit) अणु
			वापस 0;
		पूर्ण
		udelay(UDELAY_DELAY);
	पूर्ण
	netअगर_alert(qdev, probe, qdev->ndev,
		    "Timed out waiting for reg %x to come ready.\n", reg);
	वापस -ETIMEDOUT;
पूर्ण

/* The CFG रेजिस्टर is used to करोwnload TX and RX control blocks
 * to the chip. This function रुकोs क्रम an operation to complete.
 */
अटल पूर्णांक qlge_रुको_cfg(काष्ठा qlge_adapter *qdev, u32 bit)
अणु
	पूर्णांक count;
	u32 temp;

	क्रम (count = 0; count < UDELAY_COUNT; count++) अणु
		temp = qlge_पढ़ो32(qdev, CFG);
		अगर (temp & CFG_LE)
			वापस -EIO;
		अगर (!(temp & bit))
			वापस 0;
		udelay(UDELAY_DELAY);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

/* Used to issue init control blocks to hw. Maps control block,
 * sets address, triggers करोwnload, रुकोs क्रम completion.
 */
पूर्णांक qlge_ग_लिखो_cfg(काष्ठा qlge_adapter *qdev, व्योम *ptr, पूर्णांक size, u32 bit,
		   u16 q_id)
अणु
	u64 map;
	पूर्णांक status = 0;
	पूर्णांक direction;
	u32 mask;
	u32 value;

	अगर (bit & (CFG_LRQ | CFG_LR | CFG_LCQ))
		direction = DMA_TO_DEVICE;
	अन्यथा
		direction = DMA_FROM_DEVICE;

	map = dma_map_single(&qdev->pdev->dev, ptr, size, direction);
	अगर (dma_mapping_error(&qdev->pdev->dev, map)) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Couldn't map DMA area.\n");
		वापस -ENOMEM;
	पूर्ण

	status = qlge_sem_spinlock(qdev, SEM_ICB_MASK);
	अगर (status)
		जाओ lock_failed;

	status = qlge_रुको_cfg(qdev, bit);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Timed out waiting for CFG to come ready.\n");
		जाओ निकास;
	पूर्ण

	qlge_ग_लिखो32(qdev, ICB_L, (u32)map);
	qlge_ग_लिखो32(qdev, ICB_H, (u32)(map >> 32));

	mask = CFG_Q_MASK | (bit << 16);
	value = bit | (q_id << CFG_Q_SHIFT);
	qlge_ग_लिखो32(qdev, CFG, (mask | value));

	/*
	 * Wait क्रम the bit to clear after संकेतing hw.
	 */
	status = qlge_रुको_cfg(qdev, bit);
निकास:
	qlge_sem_unlock(qdev, SEM_ICB_MASK);	/* करोes flush too */
lock_failed:
	dma_unmap_single(&qdev->pdev->dev, map, size, direction);
	वापस status;
पूर्ण

/* Get a specअगरic MAC address from the CAM.  Used क्रम debug and reg dump. */
पूर्णांक qlge_get_mac_addr_reg(काष्ठा qlge_adapter *qdev, u32 type, u16 index,
			  u32 *value)
अणु
	u32 offset = 0;
	पूर्णांक status;

	चयन (type) अणु
	हाल MAC_ADDR_TYPE_MULTI_MAC:
	हाल MAC_ADDR_TYPE_CAM_MAC: अणु
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   MAC_ADDR_ADR | MAC_ADDR_RS |
				   type); /* type */
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MR, 0);
		अगर (status)
			अवरोध;
		*value++ = qlge_पढ़ो32(qdev, MAC_ADDR_DATA);
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   MAC_ADDR_ADR | MAC_ADDR_RS |
				   type); /* type */
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MR, 0);
		अगर (status)
			अवरोध;
		*value++ = qlge_पढ़ो32(qdev, MAC_ADDR_DATA);
		अगर (type == MAC_ADDR_TYPE_CAM_MAC) अणु
			status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX,
						   MAC_ADDR_MW, 0);
			अगर (status)
				अवरोध;
			qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
				     (offset++) | /* offset */
					   (index
					    << MAC_ADDR_IDX_SHIFT) | /* index */
					   MAC_ADDR_ADR |
					   MAC_ADDR_RS | type); /* type */
			status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX,
						   MAC_ADDR_MR, 0);
			अगर (status)
				अवरोध;
			*value++ = qlge_पढ़ो32(qdev, MAC_ADDR_DATA);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MAC_ADDR_TYPE_VLAN:
	हाल MAC_ADDR_TYPE_MULTI_FLTR:
	शेष:
		netअगर_crit(qdev, अगरup, qdev->ndev,
			   "Address type %d not yet supported.\n", type);
		status = -EPERM;
	पूर्ण
	वापस status;
पूर्ण

/* Set up a MAC, multicast or VLAN address क्रम the
 * inbound frame matching.
 */
अटल पूर्णांक qlge_set_mac_addr_reg(काष्ठा qlge_adapter *qdev, u8 *addr, u32 type,
				 u16 index)
अणु
	u32 offset = 0;
	पूर्णांक status = 0;

	चयन (type) अणु
	हाल MAC_ADDR_TYPE_MULTI_MAC: अणु
		u32 upper = (addr[0] << 8) | addr[1];
		u32 lower = (addr[2] << 24) | (addr[3] << 16) | (addr[4] << 8) |
			    (addr[5]);

		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     (offset++) | (index << MAC_ADDR_IDX_SHIFT) | type |
				   MAC_ADDR_E);
		qlge_ग_लिखो32(qdev, MAC_ADDR_DATA, lower);
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     (offset++) | (index << MAC_ADDR_IDX_SHIFT) | type |
				   MAC_ADDR_E);

		qlge_ग_लिखो32(qdev, MAC_ADDR_DATA, upper);
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अवरोध;
	पूर्ण
	हाल MAC_ADDR_TYPE_CAM_MAC: अणु
		u32 cam_output;
		u32 upper = (addr[0] << 8) | addr[1];
		u32 lower = (addr[2] << 24) | (addr[3] << 16) | (addr[4] << 8) |
			    (addr[5]);
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   type); /* type */
		qlge_ग_लिखो32(qdev, MAC_ADDR_DATA, lower);
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   type); /* type */
		qlge_ग_लिखो32(qdev, MAC_ADDR_DATA, upper);
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     (offset) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   type); /* type */
		/* This field should also include the queue id
		 * and possibly the function id.  Right now we hardcode
		 * the route field to NIC core.
		 */
		cam_output = (CAM_OUT_ROUTE_NIC |
			      (qdev->func << CAM_OUT_FUNC_SHIFT) |
			      (0 << CAM_OUT_CQ_ID_SHIFT));
		अगर (qdev->ndev->features & NETIF_F_HW_VLAN_CTAG_RX)
			cam_output |= CAM_OUT_RV;
		/* route to NIC core */
		qlge_ग_लिखो32(qdev, MAC_ADDR_DATA, cam_output);
		अवरोध;
	पूर्ण
	हाल MAC_ADDR_TYPE_VLAN: अणु
		u32 enable_bit = *((u32 *)&addr[0]);
		/* For VLAN, the addr actually holds a bit that
		 * either enables or disables the vlan id we are
		 * addressing. It's either MAC_ADDR_E on or off.
		 * That's bit-27 we're talking about.
		 */
		status = qlge_रुको_reg_rdy(qdev, MAC_ADDR_IDX, MAC_ADDR_MW, 0);
		अगर (status)
			अवरोध;
		qlge_ग_लिखो32(qdev, MAC_ADDR_IDX,
			     offset | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   type | /* type */
				   enable_bit); /* enable/disable */
		अवरोध;
	पूर्ण
	हाल MAC_ADDR_TYPE_MULTI_FLTR:
	शेष:
		netअगर_crit(qdev, अगरup, qdev->ndev,
			   "Address type %d not yet supported.\n", type);
		status = -EPERM;
	पूर्ण
	वापस status;
पूर्ण

/* Set or clear MAC address in hardware. We someबार
 * have to clear it to prevent wrong frame routing
 * especially in a bonding environment.
 */
अटल पूर्णांक qlge_set_mac_addr(काष्ठा qlge_adapter *qdev, पूर्णांक set)
अणु
	पूर्णांक status;
	अक्षर zero_mac_addr[ETH_ALEN];
	अक्षर *addr;

	अगर (set) अणु
		addr = &qdev->current_mac_addr[0];
		netअगर_prपूर्णांकk(qdev, अगरup, KERN_DEBUG, qdev->ndev,
			     "Set Mac addr %pM\n", addr);
	पूर्ण अन्यथा अणु
		eth_zero_addr(zero_mac_addr);
		addr = &zero_mac_addr[0];
		netअगर_prपूर्णांकk(qdev, अगरup, KERN_DEBUG, qdev->ndev,
			     "Clearing MAC address\n");
	पूर्ण
	status = qlge_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	अगर (status)
		वापस status;
	status = qlge_set_mac_addr_reg(qdev, (u8 *)addr,
				       MAC_ADDR_TYPE_CAM_MAC,
				       qdev->func * MAX_CQ);
	qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
	अगर (status)
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to init mac address.\n");
	वापस status;
पूर्ण

व्योम qlge_link_on(काष्ठा qlge_adapter *qdev)
अणु
	netअगर_err(qdev, link, qdev->ndev, "Link is up.\n");
	netअगर_carrier_on(qdev->ndev);
	qlge_set_mac_addr(qdev, 1);
पूर्ण

व्योम qlge_link_off(काष्ठा qlge_adapter *qdev)
अणु
	netअगर_err(qdev, link, qdev->ndev, "Link is down.\n");
	netअगर_carrier_off(qdev->ndev);
	qlge_set_mac_addr(qdev, 0);
पूर्ण

/* Get a specअगरic frame routing value from the CAM.
 * Used क्रम debug and reg dump.
 */
पूर्णांक qlge_get_routing_reg(काष्ठा qlge_adapter *qdev, u32 index, u32 *value)
अणु
	पूर्णांक status = 0;

	status = qlge_रुको_reg_rdy(qdev, RT_IDX, RT_IDX_MW, 0);
	अगर (status)
		जाओ निकास;

	qlge_ग_लिखो32(qdev, RT_IDX,
		     RT_IDX_TYPE_NICQ | RT_IDX_RS | (index << RT_IDX_IDX_SHIFT));
	status = qlge_रुको_reg_rdy(qdev, RT_IDX, RT_IDX_MR, 0);
	अगर (status)
		जाओ निकास;
	*value = qlge_पढ़ो32(qdev, RT_DATA);
निकास:
	वापस status;
पूर्ण

/* The NIC function क्रम this chip has 16 routing indexes.  Each one can be used
 * to route dअगरferent frame types to various inbound queues.  We send broadcast/
 * multicast/error frames to the शेष queue क्रम slow handling,
 * and CAM hit/RSS frames to the fast handling queues.
 */
अटल पूर्णांक qlge_set_routing_reg(काष्ठा qlge_adapter *qdev, u32 index, u32 mask,
				पूर्णांक enable)
अणु
	पूर्णांक status = -EINVAL; /* Return error अगर no mask match. */
	u32 value = 0;

	चयन (mask) अणु
	हाल RT_IDX_CAM_HIT:
		अणु
			value = RT_IDX_DST_CAM_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_CAM_HIT_SLOT << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_VALID:	/* Promiscuous Mode frames. */
		अणु
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_PROMISCUOUS_SLOT << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_ERR:	/* Pass up MAC,IP,TCP/UDP error frames. */
		अणु
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_ALL_ERR_SLOT << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_IP_CSUM_ERR: /* Pass up IP CSUM error frames. */
		अणु
			value = RT_IDX_DST_DFLT_Q | /* dest */
				RT_IDX_TYPE_NICQ | /* type */
				(RT_IDX_IP_CSUM_ERR_SLOT <<
				RT_IDX_IDX_SHIFT); /* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_TU_CSUM_ERR: /* Pass up TCP/UDP CSUM error frames. */
		अणु
			value = RT_IDX_DST_DFLT_Q | /* dest */
				RT_IDX_TYPE_NICQ | /* type */
				(RT_IDX_TCP_UDP_CSUM_ERR_SLOT <<
				RT_IDX_IDX_SHIFT); /* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_BCAST:	/* Pass up Broadcast frames to शेष Q. */
		अणु
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_BCAST_SLOT << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_MCAST:	/* Pass up All Multicast frames. */
		अणु
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_ALLMULTI_SLOT << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_MCAST_MATCH:	/* Pass up matched Multicast frames. */
		अणु
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_MCAST_MATCH_SLOT << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	हाल RT_IDX_RSS_MATCH:	/* Pass up matched RSS frames. */
		अणु
			value = RT_IDX_DST_RSS |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_RSS_MATCH_SLOT << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	हाल 0:		/* Clear the E-bit on an entry. */
		अणु
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (index << RT_IDX_IDX_SHIFT);/* index */
			अवरोध;
		पूर्ण
	शेष:
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Mask type %d not yet supported.\n", mask);
		status = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (value) अणु
		status = qlge_रुको_reg_rdy(qdev, RT_IDX, RT_IDX_MW, 0);
		अगर (status)
			जाओ निकास;
		value |= (enable ? RT_IDX_E : 0);
		qlge_ग_लिखो32(qdev, RT_IDX, value);
		qlge_ग_लिखो32(qdev, RT_DATA, enable ? mask : 0);
	पूर्ण
निकास:
	वापस status;
पूर्ण

अटल व्योम qlge_enable_पूर्णांकerrupts(काष्ठा qlge_adapter *qdev)
अणु
	qlge_ग_लिखो32(qdev, INTR_EN, (INTR_EN_EI << 16) | INTR_EN_EI);
पूर्ण

अटल व्योम qlge_disable_पूर्णांकerrupts(काष्ठा qlge_adapter *qdev)
अणु
	qlge_ग_लिखो32(qdev, INTR_EN, (INTR_EN_EI << 16));
पूर्ण

अटल व्योम qlge_enable_completion_पूर्णांकerrupt(काष्ठा qlge_adapter *qdev, u32 पूर्णांकr)
अणु
	काष्ठा पूर्णांकr_context *ctx = &qdev->पूर्णांकr_context[पूर्णांकr];

	qlge_ग_लिखो32(qdev, INTR_EN, ctx->पूर्णांकr_en_mask);
पूर्ण

अटल व्योम qlge_disable_completion_पूर्णांकerrupt(काष्ठा qlge_adapter *qdev, u32 पूर्णांकr)
अणु
	काष्ठा पूर्णांकr_context *ctx = &qdev->पूर्णांकr_context[पूर्णांकr];

	qlge_ग_लिखो32(qdev, INTR_EN, ctx->पूर्णांकr_dis_mask);
पूर्ण

अटल व्योम qlge_enable_all_completion_पूर्णांकerrupts(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qdev->पूर्णांकr_count; i++)
		qlge_enable_completion_पूर्णांकerrupt(qdev, i);
पूर्ण

अटल पूर्णांक qlge_validate_flash(काष्ठा qlge_adapter *qdev, u32 size, स्थिर अक्षर *str)
अणु
	पूर्णांक status, i;
	u16 csum = 0;
	__le16 *flash = (__le16 *)&qdev->flash;

	status = म_भेदन((अक्षर *)&qdev->flash, str, 4);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Invalid flash signature.\n");
		वापस	status;
	पूर्ण

	क्रम (i = 0; i < size; i++)
		csum += le16_to_cpu(*flash++);

	अगर (csum)
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Invalid flash checksum, csum = 0x%.04x.\n", csum);

	वापस csum;
पूर्ण

अटल पूर्णांक qlge_पढ़ो_flash_word(काष्ठा qlge_adapter *qdev, पूर्णांक offset, __le32 *data)
अणु
	पूर्णांक status = 0;
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev,
				   FLASH_ADDR, FLASH_ADDR_RDY, FLASH_ADDR_ERR);
	अगर (status)
		जाओ निकास;
	/* set up क्रम reg पढ़ो */
	qlge_ग_लिखो32(qdev, FLASH_ADDR, FLASH_ADDR_R | offset);
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev,
				   FLASH_ADDR, FLASH_ADDR_RDY, FLASH_ADDR_ERR);
	अगर (status)
		जाओ निकास;
	/* This data is stored on flash as an array of
	 * __le32.  Since qlge_पढ़ो32() वापसs cpu endian
	 * we need to swap it back.
	 */
	*data = cpu_to_le32(qlge_पढ़ो32(qdev, FLASH_DATA));
निकास:
	वापस status;
पूर्ण

अटल पूर्णांक qlge_get_8000_flash_params(काष्ठा qlge_adapter *qdev)
अणु
	u32 i, size;
	पूर्णांक status;
	__le32 *p = (__le32 *)&qdev->flash;
	u32 offset;
	u8 mac_addr[6];

	/* Get flash offset क्रम function and adjust
	 * क्रम dword access.
	 */
	अगर (!qdev->port)
		offset = FUNC0_FLASH_OFFSET / माप(u32);
	अन्यथा
		offset = FUNC1_FLASH_OFFSET / माप(u32);

	अगर (qlge_sem_spinlock(qdev, SEM_FLASH_MASK))
		वापस -ETIMEDOUT;

	size = माप(काष्ठा flash_params_8000) / माप(u32);
	क्रम (i = 0; i < size; i++, p++) अणु
		status = qlge_पढ़ो_flash_word(qdev, i + offset, p);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Error reading flash.\n");
			जाओ निकास;
		पूर्ण
	पूर्ण

	status = qlge_validate_flash(qdev,
				     माप(काष्ठा flash_params_8000) /
				   माप(u16),
				   "8000");
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Invalid flash.\n");
		status = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Extract either manufacturer or BOFM modअगरied
	 * MAC address.
	 */
	अगर (qdev->flash.flash_params_8000.data_type1 == 2)
		स_नकल(mac_addr,
		       qdev->flash.flash_params_8000.mac_addr1,
		       qdev->ndev->addr_len);
	अन्यथा
		स_नकल(mac_addr,
		       qdev->flash.flash_params_8000.mac_addr,
		       qdev->ndev->addr_len);

	अगर (!is_valid_ether_addr(mac_addr)) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Invalid MAC address.\n");
		status = -EINVAL;
		जाओ निकास;
	पूर्ण

	स_नकल(qdev->ndev->dev_addr,
	       mac_addr,
	       qdev->ndev->addr_len);

निकास:
	qlge_sem_unlock(qdev, SEM_FLASH_MASK);
	वापस status;
पूर्ण

अटल पूर्णांक qlge_get_8012_flash_params(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;
	पूर्णांक status;
	__le32 *p = (__le32 *)&qdev->flash;
	u32 offset = 0;
	u32 size = माप(काष्ठा flash_params_8012) / माप(u32);

	/* Second function's parameters follow the first
	 * function's.
	 */
	अगर (qdev->port)
		offset = size;

	अगर (qlge_sem_spinlock(qdev, SEM_FLASH_MASK))
		वापस -ETIMEDOUT;

	क्रम (i = 0; i < size; i++, p++) अणु
		status = qlge_पढ़ो_flash_word(qdev, i + offset, p);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Error reading flash.\n");
			जाओ निकास;
		पूर्ण
	पूर्ण

	status = qlge_validate_flash(qdev,
				     माप(काष्ठा flash_params_8012) /
				       माप(u16),
				     "8012");
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Invalid flash.\n");
		status = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (!is_valid_ether_addr(qdev->flash.flash_params_8012.mac_addr)) अणु
		status = -EINVAL;
		जाओ निकास;
	पूर्ण

	स_नकल(qdev->ndev->dev_addr,
	       qdev->flash.flash_params_8012.mac_addr,
	       qdev->ndev->addr_len);

निकास:
	qlge_sem_unlock(qdev, SEM_FLASH_MASK);
	वापस status;
पूर्ण

/* xgmac रेजिस्टर are located behind the xgmac_addr and xgmac_data
 * रेजिस्टर pair.  Each पढ़ो/ग_लिखो requires us to रुको क्रम the पढ़ोy
 * bit beक्रमe पढ़ोing/writing the data.
 */
अटल पूर्णांक qlge_ग_लिखो_xgmac_reg(काष्ठा qlge_adapter *qdev, u32 reg, u32 data)
अणु
	पूर्णांक status;
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev,
				   XGMAC_ADDR, XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	अगर (status)
		वापस status;
	/* ग_लिखो the data to the data reg */
	qlge_ग_लिखो32(qdev, XGMAC_DATA, data);
	/* trigger the ग_लिखो */
	qlge_ग_लिखो32(qdev, XGMAC_ADDR, reg);
	वापस status;
पूर्ण

/* xgmac रेजिस्टर are located behind the xgmac_addr and xgmac_data
 * रेजिस्टर pair.  Each पढ़ो/ग_लिखो requires us to रुको क्रम the पढ़ोy
 * bit beक्रमe पढ़ोing/writing the data.
 */
पूर्णांक qlge_पढ़ो_xgmac_reg(काष्ठा qlge_adapter *qdev, u32 reg, u32 *data)
अणु
	पूर्णांक status = 0;
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev,
				   XGMAC_ADDR, XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	अगर (status)
		जाओ निकास;
	/* set up क्रम reg पढ़ो */
	qlge_ग_लिखो32(qdev, XGMAC_ADDR, reg | XGMAC_ADDR_R);
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev,
				   XGMAC_ADDR, XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	अगर (status)
		जाओ निकास;
	/* get the data */
	*data = qlge_पढ़ो32(qdev, XGMAC_DATA);
निकास:
	वापस status;
पूर्ण

/* This is used क्रम पढ़ोing the 64-bit statistics regs. */
पूर्णांक qlge_पढ़ो_xgmac_reg64(काष्ठा qlge_adapter *qdev, u32 reg, u64 *data)
अणु
	पूर्णांक status = 0;
	u32 hi = 0;
	u32 lo = 0;

	status = qlge_पढ़ो_xgmac_reg(qdev, reg, &lo);
	अगर (status)
		जाओ निकास;

	status = qlge_पढ़ो_xgmac_reg(qdev, reg + 4, &hi);
	अगर (status)
		जाओ निकास;

	*data = (u64)lo | ((u64)hi << 32);

निकास:
	वापस status;
पूर्ण

अटल पूर्णांक qlge_8000_port_initialize(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status;
	/*
	 * Get MPI firmware version क्रम driver banner
	 * and ethool info.
	 */
	status = qlge_mb_about_fw(qdev);
	अगर (status)
		जाओ निकास;
	status = qlge_mb_get_fw_state(qdev);
	अगर (status)
		जाओ निकास;
	/* Wake up a worker to get/set the TX/RX frame sizes. */
	queue_delayed_work(qdev->workqueue, &qdev->mpi_port_cfg_work, 0);
निकास:
	वापस status;
पूर्ण

/* Take the MAC Core out of reset.
 * Enable statistics counting.
 * Take the transmitter/receiver out of reset.
 * This functionality may be करोne in the MPI firmware at a
 * later date.
 */
अटल पूर्णांक qlge_8012_port_initialize(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status = 0;
	u32 data;

	अगर (qlge_sem_trylock(qdev, qdev->xg_sem_mask)) अणु
		/* Another function has the semaphore, so
		 * रुको क्रम the port init bit to come पढ़ोy.
		 */
		netअगर_info(qdev, link, qdev->ndev,
			   "Another function has the semaphore, so wait for the port init bit to come ready.\n");
		status = qlge_रुको_reg_rdy(qdev, STS, qdev->port_init, 0);
		अगर (status) अणु
			netअगर_crit(qdev, link, qdev->ndev,
				   "Port initialize timed out.\n");
		पूर्ण
		वापस status;
	पूर्ण

	netअगर_info(qdev, link, qdev->ndev, "Got xgmac semaphore!.\n");
	/* Set the core reset. */
	status = qlge_पढ़ो_xgmac_reg(qdev, GLOBAL_CFG, &data);
	अगर (status)
		जाओ end;
	data |= GLOBAL_CFG_RESET;
	status = qlge_ग_लिखो_xgmac_reg(qdev, GLOBAL_CFG, data);
	अगर (status)
		जाओ end;

	/* Clear the core reset and turn on jumbo क्रम receiver. */
	data &= ~GLOBAL_CFG_RESET;	/* Clear core reset. */
	data |= GLOBAL_CFG_JUMBO;	/* Turn on jumbo. */
	data |= GLOBAL_CFG_TX_STAT_EN;
	data |= GLOBAL_CFG_RX_STAT_EN;
	status = qlge_ग_लिखो_xgmac_reg(qdev, GLOBAL_CFG, data);
	अगर (status)
		जाओ end;

	/* Enable transmitter, and clear it's reset. */
	status = qlge_पढ़ो_xgmac_reg(qdev, TX_CFG, &data);
	अगर (status)
		जाओ end;
	data &= ~TX_CFG_RESET;	/* Clear the TX MAC reset. */
	data |= TX_CFG_EN;	/* Enable the transmitter. */
	status = qlge_ग_लिखो_xgmac_reg(qdev, TX_CFG, data);
	अगर (status)
		जाओ end;

	/* Enable receiver and clear it's reset. */
	status = qlge_पढ़ो_xgmac_reg(qdev, RX_CFG, &data);
	अगर (status)
		जाओ end;
	data &= ~RX_CFG_RESET;	/* Clear the RX MAC reset. */
	data |= RX_CFG_EN;	/* Enable the receiver. */
	status = qlge_ग_लिखो_xgmac_reg(qdev, RX_CFG, data);
	अगर (status)
		जाओ end;

	/* Turn on jumbo. */
	status =
	    qlge_ग_लिखो_xgmac_reg(qdev, MAC_TX_PARAMS, MAC_TX_PARAMS_JUMBO | (0x2580 << 16));
	अगर (status)
		जाओ end;
	status =
	    qlge_ग_लिखो_xgmac_reg(qdev, MAC_RX_PARAMS, 0x2580);
	अगर (status)
		जाओ end;

	/* Signal to the world that the port is enabled.        */
	qlge_ग_लिखो32(qdev, STS, ((qdev->port_init << 16) | qdev->port_init));
end:
	qlge_sem_unlock(qdev, qdev->xg_sem_mask);
	वापस status;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक qlge_lbq_block_size(काष्ठा qlge_adapter *qdev)
अणु
	वापस PAGE_SIZE << qdev->lbq_buf_order;
पूर्ण

अटल काष्ठा qlge_bq_desc *qlge_get_curr_buf(काष्ठा qlge_bq *bq)
अणु
	काष्ठा qlge_bq_desc *bq_desc;

	bq_desc = &bq->queue[bq->next_to_clean];
	bq->next_to_clean = QLGE_BQ_WRAP(bq->next_to_clean + 1);

	वापस bq_desc;
पूर्ण

अटल काष्ठा qlge_bq_desc *qlge_get_curr_lchunk(काष्ठा qlge_adapter *qdev,
						 काष्ठा rx_ring *rx_ring)
अणु
	काष्ठा qlge_bq_desc *lbq_desc = qlge_get_curr_buf(&rx_ring->lbq);

	dma_sync_single_क्रम_cpu(&qdev->pdev->dev, lbq_desc->dma_addr,
				qdev->lbq_buf_size, DMA_FROM_DEVICE);

	अगर ((lbq_desc->p.pg_chunk.offset + qdev->lbq_buf_size) ==
	    qlge_lbq_block_size(qdev)) अणु
		/* last chunk of the master page */
		dma_unmap_page(&qdev->pdev->dev, lbq_desc->dma_addr,
			       qlge_lbq_block_size(qdev), DMA_FROM_DEVICE);
	पूर्ण

	वापस lbq_desc;
पूर्ण

/* Update an rx ring index. */
अटल व्योम qlge_update_cq(काष्ठा rx_ring *rx_ring)
अणु
	rx_ring->cnsmr_idx++;
	rx_ring->curr_entry++;
	अगर (unlikely(rx_ring->cnsmr_idx == rx_ring->cq_len)) अणु
		rx_ring->cnsmr_idx = 0;
		rx_ring->curr_entry = rx_ring->cq_base;
	पूर्ण
पूर्ण

अटल व्योम qlge_ग_लिखो_cq_idx(काष्ठा rx_ring *rx_ring)
अणु
	qlge_ग_लिखो_db_reg(rx_ring->cnsmr_idx, rx_ring->cnsmr_idx_db_reg);
पूर्ण

अटल स्थिर अक्षर * स्थिर bq_type_name[] = अणु
	[QLGE_SB] = "sbq",
	[QLGE_LB] = "lbq",
पूर्ण;

/* वापस 0 or negative error */
अटल पूर्णांक qlge_refill_sb(काष्ठा rx_ring *rx_ring,
			  काष्ठा qlge_bq_desc *sbq_desc, gfp_t gfp)
अणु
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	काष्ठा sk_buff *skb;

	अगर (sbq_desc->p.skb)
		वापस 0;

	netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
		     "ring %u sbq: getting new skb for index %d.\n",
		     rx_ring->cq_id, sbq_desc->index);

	skb = __netdev_alloc_skb(qdev->ndev, SMALL_BUFFER_SIZE, gfp);
	अगर (!skb)
		वापस -ENOMEM;
	skb_reserve(skb, QLGE_SB_PAD);

	sbq_desc->dma_addr = dma_map_single(&qdev->pdev->dev, skb->data,
					    SMALL_BUF_MAP_SIZE,
					    DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&qdev->pdev->dev, sbq_desc->dma_addr)) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "PCI mapping failed.\n");
		dev_kमुक्त_skb_any(skb);
		वापस -EIO;
	पूर्ण
	*sbq_desc->buf_ptr = cpu_to_le64(sbq_desc->dma_addr);

	sbq_desc->p.skb = skb;
	वापस 0;
पूर्ण

/* वापस 0 or negative error */
अटल पूर्णांक qlge_refill_lb(काष्ठा rx_ring *rx_ring,
			  काष्ठा qlge_bq_desc *lbq_desc, gfp_t gfp)
अणु
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	काष्ठा qlge_page_chunk *master_chunk = &rx_ring->master_chunk;

	अगर (!master_chunk->page) अणु
		काष्ठा page *page;
		dma_addr_t dma_addr;

		page = alloc_pages(gfp | __GFP_COMP, qdev->lbq_buf_order);
		अगर (unlikely(!page))
			वापस -ENOMEM;
		dma_addr = dma_map_page(&qdev->pdev->dev, page, 0,
					qlge_lbq_block_size(qdev),
					DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&qdev->pdev->dev, dma_addr)) अणु
			__मुक्त_pages(page, qdev->lbq_buf_order);
			netअगर_err(qdev, drv, qdev->ndev,
				  "PCI mapping failed.\n");
			वापस -EIO;
		पूर्ण
		master_chunk->page = page;
		master_chunk->va = page_address(page);
		master_chunk->offset = 0;
		rx_ring->chunk_dma_addr = dma_addr;
	पूर्ण

	lbq_desc->p.pg_chunk = *master_chunk;
	lbq_desc->dma_addr = rx_ring->chunk_dma_addr;
	*lbq_desc->buf_ptr = cpu_to_le64(lbq_desc->dma_addr +
					 lbq_desc->p.pg_chunk.offset);

	/* Adjust the master page chunk क्रम next
	 * buffer get.
	 */
	master_chunk->offset += qdev->lbq_buf_size;
	अगर (master_chunk->offset == qlge_lbq_block_size(qdev)) अणु
		master_chunk->page = शून्य;
	पूर्ण अन्यथा अणु
		master_chunk->va += qdev->lbq_buf_size;
		get_page(master_chunk->page);
	पूर्ण

	वापस 0;
पूर्ण

/* वापस 0 or negative error */
अटल पूर्णांक qlge_refill_bq(काष्ठा qlge_bq *bq, gfp_t gfp)
अणु
	काष्ठा rx_ring *rx_ring = QLGE_BQ_CONTAINER(bq);
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	काष्ठा qlge_bq_desc *bq_desc;
	पूर्णांक refill_count;
	पूर्णांक retval;
	पूर्णांक i;

	refill_count = QLGE_BQ_WRAP(QLGE_BQ_ALIGN(bq->next_to_clean - 1) -
				    bq->next_to_use);
	अगर (!refill_count)
		वापस 0;

	i = bq->next_to_use;
	bq_desc = &bq->queue[i];
	i -= QLGE_BQ_LEN;
	करो अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "ring %u %s: try cleaning idx %d\n",
			     rx_ring->cq_id, bq_type_name[bq->type], i);

		अगर (bq->type == QLGE_SB)
			retval = qlge_refill_sb(rx_ring, bq_desc, gfp);
		अन्यथा
			retval = qlge_refill_lb(rx_ring, bq_desc, gfp);
		अगर (retval < 0) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "ring %u %s: Could not get a page chunk, idx %d\n",
				  rx_ring->cq_id, bq_type_name[bq->type], i);
			अवरोध;
		पूर्ण

		bq_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			bq_desc = &bq->queue[0];
			i -= QLGE_BQ_LEN;
		पूर्ण
		refill_count--;
	पूर्ण जबतक (refill_count);
	i += QLGE_BQ_LEN;

	अगर (bq->next_to_use != i) अणु
		अगर (QLGE_BQ_ALIGN(bq->next_to_use) != QLGE_BQ_ALIGN(i)) अणु
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "ring %u %s: updating prod idx = %d.\n",
				     rx_ring->cq_id, bq_type_name[bq->type],
				     i);
			qlge_ग_लिखो_db_reg(i, bq->prod_idx_db_reg);
		पूर्ण
		bq->next_to_use = i;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम qlge_update_buffer_queues(काष्ठा rx_ring *rx_ring, gfp_t gfp,
				      अचिन्हित दीर्घ delay)
अणु
	bool sbq_fail, lbq_fail;

	sbq_fail = !!qlge_refill_bq(&rx_ring->sbq, gfp);
	lbq_fail = !!qlge_refill_bq(&rx_ring->lbq, gfp);

	/* Minimum number of buffers needed to be able to receive at least one
	 * frame of any क्रमmat:
	 * sbq: 1 क्रम header + 1 क्रम data
	 * lbq: mtu 9000 / lb size
	 * Below this, the queue might stall.
	 */
	अगर ((sbq_fail && QLGE_BQ_HW_OWNED(&rx_ring->sbq) < 2) ||
	    (lbq_fail && QLGE_BQ_HW_OWNED(&rx_ring->lbq) <
	     DIV_ROUND_UP(9000, LARGE_BUFFER_MAX_SIZE)))
		/* Allocations can take a दीर्घ समय in certain हालs (ex.
		 * reclaim). Thereक्रमe, use a workqueue क्रम दीर्घ-running
		 * work items.
		 */
		queue_delayed_work_on(smp_processor_id(), प्रणाली_दीर्घ_wq,
				      &rx_ring->refill_work, delay);
पूर्ण

अटल व्योम qlge_slow_refill(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rx_ring *rx_ring = container_of(work, काष्ठा rx_ring,
					       refill_work.work);
	काष्ठा napi_काष्ठा *napi = &rx_ring->napi;

	napi_disable(napi);
	qlge_update_buffer_queues(rx_ring, GFP_KERNEL, HZ / 2);
	napi_enable(napi);

	local_bh_disable();
	/* napi_disable() might have prevented incomplete napi work from being
	 * rescheduled.
	 */
	napi_schedule(napi);
	/* trigger softirq processing */
	local_bh_enable();
पूर्ण

/* Unmaps tx buffers.  Can be called from send() अगर a pci mapping
 * fails at some stage, or from the पूर्णांकerrupt when a tx completes.
 */
अटल व्योम qlge_unmap_send(काष्ठा qlge_adapter *qdev,
			    काष्ठा tx_ring_desc *tx_ring_desc, पूर्णांक mapped)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mapped; i++) अणु
		अगर (i == 0 || (i == 7 && mapped > 7)) अणु
			/*
			 * Unmap the skb->data area, or the
			 * बाह्यal sglist (AKA the Outbound
			 * Address List (OAL)).
			 * If its the zeroeth element, then it's
			 * the skb->data area.  If it's the 7th
			 * element and there is more than 6 frags,
			 * then its an OAL.
			 */
			अगर (i == 7) अणु
				netअगर_prपूर्णांकk(qdev, tx_करोne, KERN_DEBUG,
					     qdev->ndev,
					     "unmapping OAL area.\n");
			पूर्ण
			dma_unmap_single(&qdev->pdev->dev,
					 dma_unmap_addr(&tx_ring_desc->map[i],
							mapaddr),
					 dma_unmap_len(&tx_ring_desc->map[i],
						       maplen),
					 DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			netअगर_prपूर्णांकk(qdev, tx_करोne, KERN_DEBUG, qdev->ndev,
				     "unmapping frag %d.\n", i);
			dma_unmap_page(&qdev->pdev->dev,
				       dma_unmap_addr(&tx_ring_desc->map[i],
						      mapaddr),
				       dma_unmap_len(&tx_ring_desc->map[i],
						     maplen), DMA_TO_DEVICE);
		पूर्ण
	पूर्ण
पूर्ण

/* Map the buffers क्रम this transmit.  This will वापस
 * NETDEV_TX_BUSY or NETDEV_TX_OK based on success.
 */
अटल पूर्णांक qlge_map_send(काष्ठा qlge_adapter *qdev,
			 काष्ठा qlge_ob_mac_iocb_req *mac_iocb_ptr,
			 काष्ठा sk_buff *skb, काष्ठा tx_ring_desc *tx_ring_desc)
अणु
	पूर्णांक len = skb_headlen(skb);
	dma_addr_t map;
	पूर्णांक frag_idx, err, map_idx = 0;
	काष्ठा tx_buf_desc *tbd = mac_iocb_ptr->tbd;
	पूर्णांक frag_cnt = skb_shinfo(skb)->nr_frags;

	अगर (frag_cnt) अणु
		netअगर_prपूर्णांकk(qdev, tx_queued, KERN_DEBUG, qdev->ndev,
			     "frag_cnt = %d.\n", frag_cnt);
	पूर्ण
	/*
	 * Map the skb buffer first.
	 */
	map = dma_map_single(&qdev->pdev->dev, skb->data, len, DMA_TO_DEVICE);

	err = dma_mapping_error(&qdev->pdev->dev, map);
	अगर (err) अणु
		netअगर_err(qdev, tx_queued, qdev->ndev,
			  "PCI mapping failed with error: %d\n", err);

		वापस NETDEV_TX_BUSY;
	पूर्ण

	tbd->len = cpu_to_le32(len);
	tbd->addr = cpu_to_le64(map);
	dma_unmap_addr_set(&tx_ring_desc->map[map_idx], mapaddr, map);
	dma_unmap_len_set(&tx_ring_desc->map[map_idx], maplen, len);
	map_idx++;

	/*
	 * This loop fills the reमुख्यder of the 8 address descriptors
	 * in the IOCB.  If there are more than 7 fragments, then the
	 * eighth address desc will poपूर्णांक to an बाह्यal list (OAL).
	 * When this happens, the reमुख्यder of the frags will be stored
	 * in this list.
	 */
	क्रम (frag_idx = 0; frag_idx < frag_cnt; frag_idx++, map_idx++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[frag_idx];

		tbd++;
		अगर (frag_idx == 6 && frag_cnt > 7) अणु
			/* Let's tack on an sglist.
			 * Our control block will now
			 * look like this:
			 * iocb->seg[0] = skb->data
			 * iocb->seg[1] = frag[0]
			 * iocb->seg[2] = frag[1]
			 * iocb->seg[3] = frag[2]
			 * iocb->seg[4] = frag[3]
			 * iocb->seg[5] = frag[4]
			 * iocb->seg[6] = frag[5]
			 * iocb->seg[7] = ptr to OAL (बाह्यal sglist)
			 * oal->seg[0] = frag[6]
			 * oal->seg[1] = frag[7]
			 * oal->seg[2] = frag[8]
			 * oal->seg[3] = frag[9]
			 * oal->seg[4] = frag[10]
			 *      etc...
			 */
			/* Tack on the OAL in the eighth segment of IOCB. */
			map = dma_map_single(&qdev->pdev->dev, &tx_ring_desc->oal,
					     माप(काष्ठा qlge_oal),
					     DMA_TO_DEVICE);
			err = dma_mapping_error(&qdev->pdev->dev, map);
			अगर (err) अणु
				netअगर_err(qdev, tx_queued, qdev->ndev,
					  "PCI mapping outbound address list with error: %d\n",
					  err);
				जाओ map_error;
			पूर्ण

			tbd->addr = cpu_to_le64(map);
			/*
			 * The length is the number of fragments
			 * that reमुख्य to be mapped बार the length
			 * of our sglist (OAL).
			 */
			tbd->len =
			    cpu_to_le32((माप(काष्ठा tx_buf_desc) *
					 (frag_cnt - frag_idx)) | TX_DESC_C);
			dma_unmap_addr_set(&tx_ring_desc->map[map_idx], mapaddr,
					   map);
			dma_unmap_len_set(&tx_ring_desc->map[map_idx], maplen,
					  माप(काष्ठा qlge_oal));
			tbd = (काष्ठा tx_buf_desc *)&tx_ring_desc->oal;
			map_idx++;
		पूर्ण

		map = skb_frag_dma_map(&qdev->pdev->dev, frag, 0, skb_frag_size(frag),
				       DMA_TO_DEVICE);

		err = dma_mapping_error(&qdev->pdev->dev, map);
		अगर (err) अणु
			netअगर_err(qdev, tx_queued, qdev->ndev,
				  "PCI mapping frags failed with error: %d.\n",
				  err);
			जाओ map_error;
		पूर्ण

		tbd->addr = cpu_to_le64(map);
		tbd->len = cpu_to_le32(skb_frag_size(frag));
		dma_unmap_addr_set(&tx_ring_desc->map[map_idx], mapaddr, map);
		dma_unmap_len_set(&tx_ring_desc->map[map_idx], maplen,
				  skb_frag_size(frag));
	पूर्ण
	/* Save the number of segments we've mapped. */
	tx_ring_desc->map_cnt = map_idx;
	/* Terminate the last segment. */
	tbd->len = cpu_to_le32(le32_to_cpu(tbd->len) | TX_DESC_E);
	वापस NETDEV_TX_OK;

map_error:
	/*
	 * If the first frag mapping failed, then i will be zero.
	 * This causes the unmap of the skb->data area.  Otherwise
	 * we pass in the number of frags that mapped successfully
	 * so they can be umapped.
	 */
	qlge_unmap_send(qdev, tx_ring_desc, map_idx);
	वापस NETDEV_TX_BUSY;
पूर्ण

/* Categorizing receive firmware frame errors */
अटल व्योम qlge_categorize_rx_err(काष्ठा qlge_adapter *qdev, u8 rx_err,
				   काष्ठा rx_ring *rx_ring)
अणु
	काष्ठा nic_stats *stats = &qdev->nic_stats;

	stats->rx_err_count++;
	rx_ring->rx_errors++;

	चयन (rx_err & IB_MAC_IOCB_RSP_ERR_MASK) अणु
	हाल IB_MAC_IOCB_RSP_ERR_CODE_ERR:
		stats->rx_code_err++;
		अवरोध;
	हाल IB_MAC_IOCB_RSP_ERR_OVERSIZE:
		stats->rx_oversize_err++;
		अवरोध;
	हाल IB_MAC_IOCB_RSP_ERR_UNDERSIZE:
		stats->rx_undersize_err++;
		अवरोध;
	हाल IB_MAC_IOCB_RSP_ERR_PREAMBLE:
		stats->rx_preamble_err++;
		अवरोध;
	हाल IB_MAC_IOCB_RSP_ERR_FRAME_LEN:
		stats->rx_frame_len_err++;
		अवरोध;
	हाल IB_MAC_IOCB_RSP_ERR_CRC:
		stats->rx_crc_err++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * qlge_update_mac_hdr_len - helper routine to update the mac header length
 * based on vlan tags अगर present
 */
अटल व्योम qlge_update_mac_hdr_len(काष्ठा qlge_adapter *qdev,
				    काष्ठा qlge_ib_mac_iocb_rsp *ib_mac_rsp,
				    व्योम *page, माप_प्रकार *len)
अणु
	u16 *tags;

	अगर (qdev->ndev->features & NETIF_F_HW_VLAN_CTAG_RX)
		वापस;
	अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_V) अणु
		tags = (u16 *)page;
		/* Look क्रम stacked vlan tags in ethertype field */
		अगर (tags[6] == ETH_P_8021Q &&
		    tags[8] == ETH_P_8021Q)
			*len += 2 * VLAN_HLEN;
		अन्यथा
			*len += VLAN_HLEN;
	पूर्ण
पूर्ण

/* Process an inbound completion from an rx ring. */
अटल व्योम qlge_process_mac_rx_gro_page(काष्ठा qlge_adapter *qdev,
					 काष्ठा rx_ring *rx_ring,
					 काष्ठा qlge_ib_mac_iocb_rsp *ib_mac_rsp,
					 u32 length, u16 vlan_id)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा qlge_bq_desc *lbq_desc = qlge_get_curr_lchunk(qdev, rx_ring);
	काष्ठा napi_काष्ठा *napi = &rx_ring->napi;

	/* Frame error, so drop the packet. */
	अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_ERR_MASK) अणु
		qlge_categorize_rx_err(qdev, ib_mac_rsp->flags2, rx_ring);
		put_page(lbq_desc->p.pg_chunk.page);
		वापस;
	पूर्ण
	napi->dev = qdev->ndev;

	skb = napi_get_frags(napi);
	अगर (!skb) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Couldn't get an skb, exiting.\n");
		rx_ring->rx_dropped++;
		put_page(lbq_desc->p.pg_chunk.page);
		वापस;
	पूर्ण
	prefetch(lbq_desc->p.pg_chunk.va);
	__skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
			     lbq_desc->p.pg_chunk.page,
			     lbq_desc->p.pg_chunk.offset,
			     length);

	skb->len += length;
	skb->data_len += length;
	skb->truesize += length;
	skb_shinfo(skb)->nr_frags++;

	rx_ring->rx_packets++;
	rx_ring->rx_bytes += length;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb_record_rx_queue(skb, rx_ring->cq_id);
	अगर (vlan_id != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_id);
	napi_gro_frags(napi);
पूर्ण

/* Process an inbound completion from an rx ring. */
अटल व्योम qlge_process_mac_rx_page(काष्ठा qlge_adapter *qdev,
				     काष्ठा rx_ring *rx_ring,
				     काष्ठा qlge_ib_mac_iocb_rsp *ib_mac_rsp,
				     u32 length, u16 vlan_id)
अणु
	काष्ठा net_device *ndev = qdev->ndev;
	काष्ठा sk_buff *skb = शून्य;
	व्योम *addr;
	काष्ठा qlge_bq_desc *lbq_desc = qlge_get_curr_lchunk(qdev, rx_ring);
	काष्ठा napi_काष्ठा *napi = &rx_ring->napi;
	माप_प्रकार hlen = ETH_HLEN;

	skb = netdev_alloc_skb(ndev, length);
	अगर (!skb) अणु
		rx_ring->rx_dropped++;
		put_page(lbq_desc->p.pg_chunk.page);
		वापस;
	पूर्ण

	addr = lbq_desc->p.pg_chunk.va;
	prefetch(addr);

	/* Frame error, so drop the packet. */
	अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_ERR_MASK) अणु
		qlge_categorize_rx_err(qdev, ib_mac_rsp->flags2, rx_ring);
		जाओ err_out;
	पूर्ण

	/* Update the MAC header length*/
	qlge_update_mac_hdr_len(qdev, ib_mac_rsp, addr, &hlen);

	/* The max framesize filter on this chip is set higher than
	 * MTU since FCoE uses 2k frames.
	 */
	अगर (skb->len > ndev->mtu + hlen) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Segment too small, dropping.\n");
		rx_ring->rx_dropped++;
		जाओ err_out;
	पूर्ण
	skb_put_data(skb, addr, hlen);
	netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
		     "%d bytes of headers and data in large. Chain page to new skb and pull tail.\n",
		     length);
	skb_fill_page_desc(skb, 0, lbq_desc->p.pg_chunk.page,
			   lbq_desc->p.pg_chunk.offset + hlen, length - hlen);
	skb->len += length - hlen;
	skb->data_len += length - hlen;
	skb->truesize += length - hlen;

	rx_ring->rx_packets++;
	rx_ring->rx_bytes += skb->len;
	skb->protocol = eth_type_trans(skb, ndev);
	skb_checksum_none_निश्चित(skb);

	अगर ((ndev->features & NETIF_F_RXCSUM) &&
	    !(ib_mac_rsp->flags1 & IB_MAC_CSUM_ERR_MASK)) अणु
		/* TCP frame. */
		अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_T) अणु
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "TCP checksum done!\n");
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण अन्यथा अगर ((ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_U) &&
			   (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_V4)) अणु
			/* Unfragmented ipv4 UDP frame. */
			काष्ठा iphdr *iph =
				(काष्ठा iphdr *)((u8 *)addr + hlen);
			अगर (!(iph->frag_off &
			      htons(IP_MF | IP_OFFSET))) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG,
					     qdev->ndev,
					     "UDP checksum done!\n");
			पूर्ण
		पूर्ण
	पूर्ण

	skb_record_rx_queue(skb, rx_ring->cq_id);
	अगर (vlan_id != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_id);
	अगर (skb->ip_summed == CHECKSUM_UNNECESSARY)
		napi_gro_receive(napi, skb);
	अन्यथा
		netअगर_receive_skb(skb);
	वापस;
err_out:
	dev_kमुक्त_skb_any(skb);
	put_page(lbq_desc->p.pg_chunk.page);
पूर्ण

/* Process an inbound completion from an rx ring. */
अटल व्योम qlge_process_mac_rx_skb(काष्ठा qlge_adapter *qdev,
				    काष्ठा rx_ring *rx_ring,
				    काष्ठा qlge_ib_mac_iocb_rsp *ib_mac_rsp,
				    u32 length, u16 vlan_id)
अणु
	काष्ठा qlge_bq_desc *sbq_desc = qlge_get_curr_buf(&rx_ring->sbq);
	काष्ठा net_device *ndev = qdev->ndev;
	काष्ठा sk_buff *skb, *new_skb;

	skb = sbq_desc->p.skb;
	/* Allocate new_skb and copy */
	new_skb = netdev_alloc_skb(qdev->ndev, length + NET_IP_ALIGN);
	अगर (!new_skb) अणु
		rx_ring->rx_dropped++;
		वापस;
	पूर्ण
	skb_reserve(new_skb, NET_IP_ALIGN);

	dma_sync_single_क्रम_cpu(&qdev->pdev->dev, sbq_desc->dma_addr,
				SMALL_BUF_MAP_SIZE, DMA_FROM_DEVICE);

	skb_put_data(new_skb, skb->data, length);

	skb = new_skb;

	/* Frame error, so drop the packet. */
	अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_ERR_MASK) अणु
		qlge_categorize_rx_err(qdev, ib_mac_rsp->flags2, rx_ring);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	/* loopback self test क्रम ethtool */
	अगर (test_bit(QL_SELFTEST, &qdev->flags)) अणु
		qlge_check_lb_frame(qdev, skb);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	/* The max framesize filter on this chip is set higher than
	 * MTU since FCoE uses 2k frames.
	 */
	अगर (skb->len > ndev->mtu + ETH_HLEN) अणु
		dev_kमुक्त_skb_any(skb);
		rx_ring->rx_dropped++;
		वापस;
	पूर्ण

	prefetch(skb->data);
	अगर (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "%s Multicast.\n",
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_HASH ? "Hash" :
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_REG ? "Registered" :
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_PROM ? "Promiscuous" : "");
	पूर्ण
	अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_P)
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "Promiscuous Packet.\n");

	rx_ring->rx_packets++;
	rx_ring->rx_bytes += skb->len;
	skb->protocol = eth_type_trans(skb, ndev);
	skb_checksum_none_निश्चित(skb);

	/* If rx checksum is on, and there are no
	 * csum or frame errors.
	 */
	अगर ((ndev->features & NETIF_F_RXCSUM) &&
	    !(ib_mac_rsp->flags1 & IB_MAC_CSUM_ERR_MASK)) अणु
		/* TCP frame. */
		अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_T) अणु
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "TCP checksum done!\n");
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण अन्यथा अगर ((ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_U) &&
			   (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_V4)) अणु
			/* Unfragmented ipv4 UDP frame. */
			काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;

			अगर (!(iph->frag_off &
			      htons(IP_MF | IP_OFFSET))) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG,
					     qdev->ndev,
					     "UDP checksum done!\n");
			पूर्ण
		पूर्ण
	पूर्ण

	skb_record_rx_queue(skb, rx_ring->cq_id);
	अगर (vlan_id != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_id);
	अगर (skb->ip_summed == CHECKSUM_UNNECESSARY)
		napi_gro_receive(&rx_ring->napi, skb);
	अन्यथा
		netअगर_receive_skb(skb);
पूर्ण

अटल व्योम qlge_realign_skb(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	व्योम *temp_addr = skb->data;

	/* Unकरो the skb_reserve(skb,32) we did beक्रमe
	 * giving to hardware, and realign data on
	 * a 2-byte boundary.
	 */
	skb->data -= QLGE_SB_PAD - NET_IP_ALIGN;
	skb->tail -= QLGE_SB_PAD - NET_IP_ALIGN;
	स_हटाओ(skb->data, temp_addr, len);
पूर्ण

/*
 * This function builds an skb क्रम the given inbound
 * completion.  It will be rewritten क्रम पढ़ोability in the near
 * future, but क्रम not it works well.
 */
अटल काष्ठा sk_buff *qlge_build_rx_skb(काष्ठा qlge_adapter *qdev,
					 काष्ठा rx_ring *rx_ring,
					 काष्ठा qlge_ib_mac_iocb_rsp *ib_mac_rsp)
अणु
	u32 length = le32_to_cpu(ib_mac_rsp->data_len);
	u32 hdr_len = le32_to_cpu(ib_mac_rsp->hdr_len);
	काष्ठा qlge_bq_desc *lbq_desc, *sbq_desc;
	काष्ठा sk_buff *skb = शून्य;
	माप_प्रकार hlen = ETH_HLEN;

	/*
	 * Handle the header buffer अगर present.
	 */
	अगर (ib_mac_rsp->flags4 & IB_MAC_IOCB_RSP_HV &&
	    ib_mac_rsp->flags4 & IB_MAC_IOCB_RSP_HS) अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "Header of %d bytes in small buffer.\n", hdr_len);
		/*
		 * Headers fit nicely पूर्णांकo a small buffer.
		 */
		sbq_desc = qlge_get_curr_buf(&rx_ring->sbq);
		dma_unmap_single(&qdev->pdev->dev, sbq_desc->dma_addr,
				 SMALL_BUF_MAP_SIZE, DMA_FROM_DEVICE);
		skb = sbq_desc->p.skb;
		qlge_realign_skb(skb, hdr_len);
		skb_put(skb, hdr_len);
		sbq_desc->p.skb = शून्य;
	पूर्ण

	/*
	 * Handle the data buffer(s).
	 */
	अगर (unlikely(!length)) अणु	/* Is there data too? */
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "No Data buffer in this packet.\n");
		वापस skb;
	पूर्ण

	अगर (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DS) अणु
		अगर (ib_mac_rsp->flags4 & IB_MAC_IOCB_RSP_HS) अणु
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Headers in small, data of %d bytes in small, combine them.\n",
				     length);
			/*
			 * Data is less than small buffer size so it's
			 * stuffed in a small buffer.
			 * For this हाल we append the data
			 * from the "data" small buffer to the "header" small
			 * buffer.
			 */
			sbq_desc = qlge_get_curr_buf(&rx_ring->sbq);
			dma_sync_single_क्रम_cpu(&qdev->pdev->dev,
						sbq_desc->dma_addr,
						SMALL_BUF_MAP_SIZE,
						DMA_FROM_DEVICE);
			skb_put_data(skb, sbq_desc->p.skb->data, length);
		पूर्ण अन्यथा अणु
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "%d bytes in a single small buffer.\n",
				     length);
			sbq_desc = qlge_get_curr_buf(&rx_ring->sbq);
			skb = sbq_desc->p.skb;
			qlge_realign_skb(skb, length);
			skb_put(skb, length);
			dma_unmap_single(&qdev->pdev->dev, sbq_desc->dma_addr,
					 SMALL_BUF_MAP_SIZE,
					 DMA_FROM_DEVICE);
			sbq_desc->p.skb = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DL) अणु
		अगर (ib_mac_rsp->flags4 & IB_MAC_IOCB_RSP_HS) अणु
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Header in small, %d bytes in large. Chain large to small!\n",
				     length);
			/*
			 * The data is in a single large buffer.  We
			 * chain it to the header buffer's skb and let
			 * it rip.
			 */
			lbq_desc = qlge_get_curr_lchunk(qdev, rx_ring);
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Chaining page at offset = %d, for %d bytes  to skb.\n",
				     lbq_desc->p.pg_chunk.offset, length);
			skb_fill_page_desc(skb, 0, lbq_desc->p.pg_chunk.page,
					   lbq_desc->p.pg_chunk.offset, length);
			skb->len += length;
			skb->data_len += length;
			skb->truesize += length;
		पूर्ण अन्यथा अणु
			/*
			 * The headers and data are in a single large buffer. We
			 * copy it to a new skb and let it go. This can happen with
			 * jumbo mtu on a non-TCP/UDP frame.
			 */
			lbq_desc = qlge_get_curr_lchunk(qdev, rx_ring);
			skb = netdev_alloc_skb(qdev->ndev, length);
			अगर (!skb) अणु
				netअगर_prपूर्णांकk(qdev, probe, KERN_DEBUG, qdev->ndev,
					     "No skb available, drop the packet.\n");
				वापस शून्य;
			पूर्ण
			dma_unmap_page(&qdev->pdev->dev, lbq_desc->dma_addr,
				       qdev->lbq_buf_size,
				       DMA_FROM_DEVICE);
			skb_reserve(skb, NET_IP_ALIGN);
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "%d bytes of headers and data in large. Chain page to new skb and pull tail.\n",
				     length);
			skb_fill_page_desc(skb, 0, lbq_desc->p.pg_chunk.page,
					   lbq_desc->p.pg_chunk.offset,
					   length);
			skb->len += length;
			skb->data_len += length;
			skb->truesize += length;
			qlge_update_mac_hdr_len(qdev, ib_mac_rsp,
						lbq_desc->p.pg_chunk.va,
						&hlen);
			__pskb_pull_tail(skb, hlen);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The data is in a chain of large buffers
		 * poपूर्णांकed to by a small buffer.  We loop
		 * thru and chain them to the our small header
		 * buffer's skb.
		 * frags:  There are 18 max frags and our small
		 *         buffer will hold 32 of them. The thing is,
		 *         we'll use 3 max क्रम our 9000 byte jumbo
		 *         frames.  If the MTU goes up we could
		 *          eventually be in trouble.
		 */
		पूर्णांक size, i = 0;

		sbq_desc = qlge_get_curr_buf(&rx_ring->sbq);
		dma_unmap_single(&qdev->pdev->dev, sbq_desc->dma_addr,
				 SMALL_BUF_MAP_SIZE, DMA_FROM_DEVICE);
		अगर (!(ib_mac_rsp->flags4 & IB_MAC_IOCB_RSP_HS)) अणु
			/*
			 * This is an non TCP/UDP IP frame, so
			 * the headers aren't split पूर्णांकo a small
			 * buffer.  We have to use the small buffer
			 * that contains our sg list as our skb to
			 * send upstairs. Copy the sg list here to
			 * a local buffer and use it to find the
			 * pages to chain.
			 */
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "%d bytes of headers & data in chain of large.\n",
				     length);
			skb = sbq_desc->p.skb;
			sbq_desc->p.skb = शून्य;
			skb_reserve(skb, NET_IP_ALIGN);
		पूर्ण
		करो अणु
			lbq_desc = qlge_get_curr_lchunk(qdev, rx_ring);
			size = min(length, qdev->lbq_buf_size);

			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Adding page %d to skb for %d bytes.\n",
				     i, size);
			skb_fill_page_desc(skb, i,
					   lbq_desc->p.pg_chunk.page,
					   lbq_desc->p.pg_chunk.offset, size);
			skb->len += size;
			skb->data_len += size;
			skb->truesize += size;
			length -= size;
			i++;
		पूर्ण जबतक (length > 0);
		qlge_update_mac_hdr_len(qdev, ib_mac_rsp, lbq_desc->p.pg_chunk.va,
					&hlen);
		__pskb_pull_tail(skb, hlen);
	पूर्ण
	वापस skb;
पूर्ण

/* Process an inbound completion from an rx ring. */
अटल व्योम qlge_process_mac_split_rx_पूर्णांकr(काष्ठा qlge_adapter *qdev,
					   काष्ठा rx_ring *rx_ring,
					   काष्ठा qlge_ib_mac_iocb_rsp *ib_mac_rsp,
					   u16 vlan_id)
अणु
	काष्ठा net_device *ndev = qdev->ndev;
	काष्ठा sk_buff *skb = शून्य;

	skb = qlge_build_rx_skb(qdev, rx_ring, ib_mac_rsp);
	अगर (unlikely(!skb)) अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "No skb available, drop packet.\n");
		rx_ring->rx_dropped++;
		वापस;
	पूर्ण

	/* Frame error, so drop the packet. */
	अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_ERR_MASK) अणु
		qlge_categorize_rx_err(qdev, ib_mac_rsp->flags2, rx_ring);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	/* The max framesize filter on this chip is set higher than
	 * MTU since FCoE uses 2k frames.
	 */
	अगर (skb->len > ndev->mtu + ETH_HLEN) अणु
		dev_kमुक्त_skb_any(skb);
		rx_ring->rx_dropped++;
		वापस;
	पूर्ण

	/* loopback self test क्रम ethtool */
	अगर (test_bit(QL_SELFTEST, &qdev->flags)) अणु
		qlge_check_lb_frame(qdev, skb);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	prefetch(skb->data);
	अगर (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev, "%s Multicast.\n",
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_HASH ? "Hash" :
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_REG ? "Registered" :
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_PROM ? "Promiscuous" : "");
		rx_ring->rx_multicast++;
	पूर्ण
	अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_P) अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "Promiscuous Packet.\n");
	पूर्ण

	skb->protocol = eth_type_trans(skb, ndev);
	skb_checksum_none_निश्चित(skb);

	/* If rx checksum is on, and there are no
	 * csum or frame errors.
	 */
	अगर ((ndev->features & NETIF_F_RXCSUM) &&
	    !(ib_mac_rsp->flags1 & IB_MAC_CSUM_ERR_MASK)) अणु
		/* TCP frame. */
		अगर (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_T) अणु
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "TCP checksum done!\n");
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण अन्यथा अगर ((ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_U) &&
			   (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_V4)) अणु
			/* Unfragmented ipv4 UDP frame. */
			काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;

			अगर (!(iph->frag_off &
			      htons(IP_MF | IP_OFFSET))) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
					     "TCP checksum done!\n");
			पूर्ण
		पूर्ण
	पूर्ण

	rx_ring->rx_packets++;
	rx_ring->rx_bytes += skb->len;
	skb_record_rx_queue(skb, rx_ring->cq_id);
	अगर (vlan_id != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_id);
	अगर (skb->ip_summed == CHECKSUM_UNNECESSARY)
		napi_gro_receive(&rx_ring->napi, skb);
	अन्यथा
		netअगर_receive_skb(skb);
पूर्ण

/* Process an inbound completion from an rx ring. */
अटल अचिन्हित दीर्घ qlge_process_mac_rx_पूर्णांकr(काष्ठा qlge_adapter *qdev,
					      काष्ठा rx_ring *rx_ring,
					      काष्ठा qlge_ib_mac_iocb_rsp *ib_mac_rsp)
अणु
	u32 length = le32_to_cpu(ib_mac_rsp->data_len);
	u16 vlan_id = ((ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_V) &&
		       (qdev->ndev->features & NETIF_F_HW_VLAN_CTAG_RX)) ?
		((le16_to_cpu(ib_mac_rsp->vlan_id) &
		  IB_MAC_IOCB_RSP_VLAN_MASK)) : 0xffff;

	अगर (ib_mac_rsp->flags4 & IB_MAC_IOCB_RSP_HV) अणु
		/* The data and headers are split पूर्णांकo
		 * separate buffers.
		 */
		qlge_process_mac_split_rx_पूर्णांकr(qdev, rx_ring, ib_mac_rsp,
					       vlan_id);
	पूर्ण अन्यथा अगर (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DS) अणु
		/* The data fit in a single small buffer.
		 * Allocate a new skb, copy the data and
		 * वापस the buffer to the मुक्त pool.
		 */
		qlge_process_mac_rx_skb(qdev, rx_ring, ib_mac_rsp, length,
					vlan_id);
	पूर्ण अन्यथा अगर ((ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DL) &&
		   !(ib_mac_rsp->flags1 & IB_MAC_CSUM_ERR_MASK) &&
		   (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_T)) अणु
		/* TCP packet in a page chunk that's been checksummed.
		 * Tack it on to our GRO skb and let it go.
		 */
		qlge_process_mac_rx_gro_page(qdev, rx_ring, ib_mac_rsp, length,
					     vlan_id);
	पूर्ण अन्यथा अगर (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DL) अणु
		/* Non-TCP packet in a page chunk. Allocate an
		 * skb, tack it on frags, and send it up.
		 */
		qlge_process_mac_rx_page(qdev, rx_ring, ib_mac_rsp, length,
					 vlan_id);
	पूर्ण अन्यथा अणु
		/* Non-TCP/UDP large frames that span multiple buffers
		 * can be processed corrrectly by the split frame logic.
		 */
		qlge_process_mac_split_rx_पूर्णांकr(qdev, rx_ring, ib_mac_rsp,
					       vlan_id);
	पूर्ण

	वापस (अचिन्हित दीर्घ)length;
पूर्ण

/* Process an outbound completion from an rx ring. */
अटल व्योम qlge_process_mac_tx_पूर्णांकr(काष्ठा qlge_adapter *qdev,
				     काष्ठा qlge_ob_mac_iocb_rsp *mac_rsp)
अणु
	काष्ठा tx_ring *tx_ring;
	काष्ठा tx_ring_desc *tx_ring_desc;

	tx_ring = &qdev->tx_ring[mac_rsp->txq_idx];
	tx_ring_desc = &tx_ring->q[mac_rsp->tid];
	qlge_unmap_send(qdev, tx_ring_desc, tx_ring_desc->map_cnt);
	tx_ring->tx_bytes += (tx_ring_desc->skb)->len;
	tx_ring->tx_packets++;
	dev_kमुक्त_skb(tx_ring_desc->skb);
	tx_ring_desc->skb = शून्य;

	अगर (unlikely(mac_rsp->flags1 & (OB_MAC_IOCB_RSP_E |
					OB_MAC_IOCB_RSP_S |
					OB_MAC_IOCB_RSP_L |
					OB_MAC_IOCB_RSP_P | OB_MAC_IOCB_RSP_B))) अणु
		अगर (mac_rsp->flags1 & OB_MAC_IOCB_RSP_E) अणु
			netअगर_warn(qdev, tx_करोne, qdev->ndev,
				   "Total descriptor length did not match transfer length.\n");
		पूर्ण
		अगर (mac_rsp->flags1 & OB_MAC_IOCB_RSP_S) अणु
			netअगर_warn(qdev, tx_करोne, qdev->ndev,
				   "Frame too short to be valid, not sent.\n");
		पूर्ण
		अगर (mac_rsp->flags1 & OB_MAC_IOCB_RSP_L) अणु
			netअगर_warn(qdev, tx_करोne, qdev->ndev,
				   "Frame too long, but sent anyway.\n");
		पूर्ण
		अगर (mac_rsp->flags1 & OB_MAC_IOCB_RSP_B) अणु
			netअगर_warn(qdev, tx_करोne, qdev->ndev,
				   "PCI backplane error. Frame not sent.\n");
		पूर्ण
	पूर्ण
	atomic_inc(&tx_ring->tx_count);
पूर्ण

/* Fire up a handler to reset the MPI processor. */
व्योम qlge_queue_fw_error(काष्ठा qlge_adapter *qdev)
अणु
	qlge_link_off(qdev);
	queue_delayed_work(qdev->workqueue, &qdev->mpi_reset_work, 0);
पूर्ण

व्योम qlge_queue_asic_error(काष्ठा qlge_adapter *qdev)
अणु
	qlge_link_off(qdev);
	qlge_disable_पूर्णांकerrupts(qdev);
	/* Clear adapter up bit to संकेत the recovery
	 * process that it shouldn't समाप्त the reset worker
	 * thपढ़ो
	 */
	clear_bit(QL_ADAPTER_UP, &qdev->flags);
	/* Set asic recovery bit to indicate reset process that we are
	 * in fatal error recovery process rather than normal बंद
	 */
	set_bit(QL_ASIC_RECOVERY, &qdev->flags);
	queue_delayed_work(qdev->workqueue, &qdev->asic_reset_work, 0);
पूर्ण

अटल व्योम qlge_process_chip_ae_पूर्णांकr(काष्ठा qlge_adapter *qdev,
				      काष्ठा qlge_ib_ae_iocb_rsp *ib_ae_rsp)
अणु
	चयन (ib_ae_rsp->event) अणु
	हाल MGMT_ERR_EVENT:
		netअगर_err(qdev, rx_err, qdev->ndev,
			  "Management Processor Fatal Error.\n");
		qlge_queue_fw_error(qdev);
		वापस;

	हाल CAM_LOOKUP_ERR_EVENT:
		netdev_err(qdev->ndev, "Multiple CAM hits lookup occurred.\n");
		netdev_err(qdev->ndev, "This event shouldn't occur.\n");
		qlge_queue_asic_error(qdev);
		वापस;

	हाल SOFT_ECC_ERROR_EVENT:
		netdev_err(qdev->ndev, "Soft ECC error detected.\n");
		qlge_queue_asic_error(qdev);
		अवरोध;

	हाल PCI_ERR_ANON_BUF_RD:
		netdev_err(qdev->ndev,
			   "PCI error occurred when reading anonymous buffers from rx_ring %d.\n",
			   ib_ae_rsp->q_id);
		qlge_queue_asic_error(qdev);
		अवरोध;

	शेष:
		netअगर_err(qdev, drv, qdev->ndev, "Unexpected event %d.\n",
			  ib_ae_rsp->event);
		qlge_queue_asic_error(qdev);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_clean_outbound_rx_ring(काष्ठा rx_ring *rx_ring)
अणु
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	u32 prod = qlge_पढ़ो_sh_reg(rx_ring->prod_idx_sh_reg);
	काष्ठा qlge_ob_mac_iocb_rsp *net_rsp = शून्य;
	पूर्णांक count = 0;

	काष्ठा tx_ring *tx_ring;
	/* While there are entries in the completion queue. */
	जबतक (prod != rx_ring->cnsmr_idx) अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "cq_id = %d, prod = %d, cnsmr = %d\n",
			     rx_ring->cq_id, prod, rx_ring->cnsmr_idx);

		net_rsp = (काष्ठा qlge_ob_mac_iocb_rsp *)rx_ring->curr_entry;
		rmb();
		चयन (net_rsp->opcode) अणु
		हाल OPCODE_OB_MAC_TSO_IOCB:
		हाल OPCODE_OB_MAC_IOCB:
			qlge_process_mac_tx_पूर्णांकr(qdev, net_rsp);
			अवरोध;
		शेष:
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Hit default case, not handled! dropping the packet, opcode = %x.\n",
				     net_rsp->opcode);
		पूर्ण
		count++;
		qlge_update_cq(rx_ring);
		prod = qlge_पढ़ो_sh_reg(rx_ring->prod_idx_sh_reg);
	पूर्ण
	अगर (!net_rsp)
		वापस 0;
	qlge_ग_लिखो_cq_idx(rx_ring);
	tx_ring = &qdev->tx_ring[net_rsp->txq_idx];
	अगर (__netअगर_subqueue_stopped(qdev->ndev, tx_ring->wq_id)) अणु
		अगर ((atomic_पढ़ो(&tx_ring->tx_count) > (tx_ring->wq_len / 4)))
			/*
			 * The queue got stopped because the tx_ring was full.
			 * Wake it up, because it's now at least 25% empty.
			 */
			netअगर_wake_subqueue(qdev->ndev, tx_ring->wq_id);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक qlge_clean_inbound_rx_ring(काष्ठा rx_ring *rx_ring, पूर्णांक budget)
अणु
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	u32 prod = qlge_पढ़ो_sh_reg(rx_ring->prod_idx_sh_reg);
	काष्ठा qlge_net_rsp_iocb *net_rsp;
	पूर्णांक count = 0;

	/* While there are entries in the completion queue. */
	जबतक (prod != rx_ring->cnsmr_idx) अणु
		netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "cq_id = %d, prod = %d, cnsmr = %d\n",
			     rx_ring->cq_id, prod, rx_ring->cnsmr_idx);

		net_rsp = rx_ring->curr_entry;
		rmb();
		चयन (net_rsp->opcode) अणु
		हाल OPCODE_IB_MAC_IOCB:
			qlge_process_mac_rx_पूर्णांकr(qdev, rx_ring,
						 (काष्ठा qlge_ib_mac_iocb_rsp *)
						 net_rsp);
			अवरोध;

		हाल OPCODE_IB_AE_IOCB:
			qlge_process_chip_ae_पूर्णांकr(qdev, (काष्ठा qlge_ib_ae_iocb_rsp *)
						  net_rsp);
			अवरोध;
		शेष:
			netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Hit default case, not handled! dropping the packet, opcode = %x.\n",
				     net_rsp->opcode);
			अवरोध;
		पूर्ण
		count++;
		qlge_update_cq(rx_ring);
		prod = qlge_पढ़ो_sh_reg(rx_ring->prod_idx_sh_reg);
		अगर (count == budget)
			अवरोध;
	पूर्ण
	qlge_update_buffer_queues(rx_ring, GFP_ATOMIC, 0);
	qlge_ग_लिखो_cq_idx(rx_ring);
	वापस count;
पूर्ण

अटल पूर्णांक qlge_napi_poll_msix(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा rx_ring *rx_ring = container_of(napi, काष्ठा rx_ring, napi);
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	काष्ठा rx_ring *trx_ring;
	पूर्णांक i, work_करोne = 0;
	काष्ठा पूर्णांकr_context *ctx = &qdev->पूर्णांकr_context[rx_ring->cq_id];

	netअगर_prपूर्णांकk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
		     "Enter, NAPI POLL cq_id = %d.\n", rx_ring->cq_id);

	/* Service the TX rings first.  They start
	 * right after the RSS rings.
	 */
	क्रम (i = qdev->rss_ring_count; i < qdev->rx_ring_count; i++) अणु
		trx_ring = &qdev->rx_ring[i];
		/* If this TX completion ring beदीर्घs to this vector and
		 * it's not empty then service it.
		 */
		अगर ((ctx->irq_mask & (1 << trx_ring->cq_id)) &&
		    (qlge_पढ़ो_sh_reg(trx_ring->prod_idx_sh_reg) !=
		     trx_ring->cnsmr_idx)) अणु
			netअगर_prपूर्णांकk(qdev, पूर्णांकr, KERN_DEBUG, qdev->ndev,
				     "%s: Servicing TX completion ring %d.\n",
				     __func__, trx_ring->cq_id);
			qlge_clean_outbound_rx_ring(trx_ring);
		पूर्ण
	पूर्ण

	/*
	 * Now service the RSS ring अगर it's active.
	 */
	अगर (qlge_पढ़ो_sh_reg(rx_ring->prod_idx_sh_reg) !=
	    rx_ring->cnsmr_idx) अणु
		netअगर_prपूर्णांकk(qdev, पूर्णांकr, KERN_DEBUG, qdev->ndev,
			     "%s: Servicing RX completion ring %d.\n",
			     __func__, rx_ring->cq_id);
		work_करोne = qlge_clean_inbound_rx_ring(rx_ring, budget);
	पूर्ण

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		qlge_enable_completion_पूर्णांकerrupt(qdev, rx_ring->irq);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम qlge_vlan_mode(काष्ठा net_device *ndev, netdev_features_t features)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		qlge_ग_लिखो32(qdev, NIC_RCV_CFG, NIC_RCV_CFG_VLAN_MASK |
			     NIC_RCV_CFG_VLAN_MATCH_AND_NON);
	पूर्ण अन्यथा अणु
		qlge_ग_लिखो32(qdev, NIC_RCV_CFG, NIC_RCV_CFG_VLAN_MASK);
	पूर्ण
पूर्ण

/**
 * qlge_update_hw_vlan_features - helper routine to reinitialize the adapter
 * based on the features to enable/disable hardware vlan accel
 */
अटल पूर्णांक qlge_update_hw_vlan_features(काष्ठा net_device *ndev,
					netdev_features_t features)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	bool need_restart = netअगर_running(ndev);
	पूर्णांक status = 0;

	अगर (need_restart) अणु
		status = qlge_adapter_करोwn(qdev);
		अगर (status) अणु
			netअगर_err(qdev, link, qdev->ndev,
				  "Failed to bring down the adapter\n");
			वापस status;
		पूर्ण
	पूर्ण

	/* update the features with resent change */
	ndev->features = features;

	अगर (need_restart) अणु
		status = qlge_adapter_up(qdev);
		अगर (status) अणु
			netअगर_err(qdev, link, qdev->ndev,
				  "Failed to bring up the adapter\n");
			वापस status;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक qlge_set_features(काष्ठा net_device *ndev,
			     netdev_features_t features)
अणु
	netdev_features_t changed = ndev->features ^ features;
	पूर्णांक err;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX) अणु
		/* Update the behavior of vlan accel in the adapter */
		err = qlge_update_hw_vlan_features(ndev, features);
		अगर (err)
			वापस err;

		qlge_vlan_mode(ndev, features);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __qlge_vlan_rx_add_vid(काष्ठा qlge_adapter *qdev, u16 vid)
अणु
	u32 enable_bit = MAC_ADDR_E;
	पूर्णांक err;

	err = qlge_set_mac_addr_reg(qdev, (u8 *)&enable_bit,
				    MAC_ADDR_TYPE_VLAN, vid);
	अगर (err)
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to init vlan address.\n");
	वापस err;
पूर्ण

अटल पूर्णांक qlge_vlan_rx_add_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	पूर्णांक status;
	पूर्णांक err;

	status = qlge_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	अगर (status)
		वापस status;

	err = __qlge_vlan_rx_add_vid(qdev, vid);
	set_bit(vid, qdev->active_vlans);

	qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);

	वापस err;
पूर्ण

अटल पूर्णांक __qlge_vlan_rx_समाप्त_vid(काष्ठा qlge_adapter *qdev, u16 vid)
अणु
	u32 enable_bit = 0;
	पूर्णांक err;

	err = qlge_set_mac_addr_reg(qdev, (u8 *)&enable_bit,
				    MAC_ADDR_TYPE_VLAN, vid);
	अगर (err)
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to clear vlan address.\n");
	वापस err;
पूर्ण

अटल पूर्णांक qlge_vlan_rx_समाप्त_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	पूर्णांक status;
	पूर्णांक err;

	status = qlge_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	अगर (status)
		वापस status;

	err = __qlge_vlan_rx_समाप्त_vid(qdev, vid);
	clear_bit(vid, qdev->active_vlans);

	qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);

	वापस err;
पूर्ण

अटल व्योम qlge_restore_vlan(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status;
	u16 vid;

	status = qlge_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	अगर (status)
		वापस;

	क्रम_each_set_bit(vid, qdev->active_vlans, VLAN_N_VID)
		__qlge_vlan_rx_add_vid(qdev, vid);

	qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
पूर्ण

/* MSI-X Multiple Vector Interrupt Handler क्रम inbound completions. */
अटल irqवापस_t qlge_msix_rx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rx_ring *rx_ring = dev_id;

	napi_schedule(&rx_ring->napi);
	वापस IRQ_HANDLED;
पूर्ण

/* This handles a fatal error, MPI activity, and the शेष
 * rx_ring in an MSI-X multiple vector environment.
 * In MSI/Legacy environment it also process the rest of
 * the rx_rings.
 */
अटल irqवापस_t qlge_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rx_ring *rx_ring = dev_id;
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	काष्ठा पूर्णांकr_context *पूर्णांकr_context = &qdev->पूर्णांकr_context[0];
	u32 var;
	पूर्णांक work_करोne = 0;

	/* Experience shows that when using INTx पूर्णांकerrupts, पूर्णांकerrupts must
	 * be masked manually.
	 * When using MSI mode, INTR_EN_EN must be explicitly disabled
	 * (even though it is स्वतः-masked), otherwise a later command to
	 * enable it is not effective.
	 */
	अगर (!test_bit(QL_MSIX_ENABLED, &qdev->flags))
		qlge_disable_completion_पूर्णांकerrupt(qdev, 0);

	var = qlge_पढ़ो32(qdev, STS);

	/*
	 * Check क्रम fatal error.
	 */
	अगर (var & STS_FE) अणु
		qlge_disable_completion_पूर्णांकerrupt(qdev, 0);
		qlge_queue_asic_error(qdev);
		netdev_err(qdev->ndev, "Got fatal error, STS = %x.\n", var);
		var = qlge_पढ़ो32(qdev, ERR_STS);
		netdev_err(qdev->ndev, "Resetting chip. Error Status Register = 0x%x\n", var);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * Check MPI processor activity.
	 */
	अगर ((var & STS_PI) &&
	    (qlge_पढ़ो32(qdev, INTR_MASK) & INTR_MASK_PI)) अणु
		/*
		 * We've got an async event or mailbox completion.
		 * Handle it and clear the source of the पूर्णांकerrupt.
		 */
		netअगर_err(qdev, पूर्णांकr, qdev->ndev,
			  "Got MPI processor interrupt.\n");
		qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16));
		queue_delayed_work_on(smp_processor_id(),
				      qdev->workqueue, &qdev->mpi_work, 0);
		work_करोne++;
	पूर्ण

	/*
	 * Get the bit-mask that shows the active queues क्रम this
	 * pass.  Compare it to the queues that this irq services
	 * and call napi अगर there's a match.
	 */
	var = qlge_पढ़ो32(qdev, ISR1);
	अगर (var & पूर्णांकr_context->irq_mask) अणु
		netअगर_info(qdev, पूर्णांकr, qdev->ndev,
			   "Waking handler for rx_ring[0].\n");
		napi_schedule(&rx_ring->napi);
		work_करोne++;
	पूर्ण अन्यथा अणु
		/* Experience shows that the device someबार संकेतs an
		 * पूर्णांकerrupt but no work is scheduled from this function.
		 * Nevertheless, the पूर्णांकerrupt is स्वतः-masked. Thereक्रमe, we
		 * प्रणालीatically re-enable the पूर्णांकerrupt अगर we didn't
		 * schedule napi.
		 */
		qlge_enable_completion_पूर्णांकerrupt(qdev, 0);
	पूर्ण

	वापस work_करोne ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक qlge_tso(काष्ठा sk_buff *skb, काष्ठा qlge_ob_mac_tso_iocb_req *mac_iocb_ptr)
अणु
	अगर (skb_is_gso(skb)) अणु
		पूर्णांक err;
		__be16 l3_proto = vlan_get_protocol(skb);

		err = skb_cow_head(skb, 0);
		अगर (err < 0)
			वापस err;

		mac_iocb_ptr->opcode = OPCODE_OB_MAC_TSO_IOCB;
		mac_iocb_ptr->flags3 |= OB_MAC_TSO_IOCB_IC;
		mac_iocb_ptr->frame_len = cpu_to_le32((u32)skb->len);
		mac_iocb_ptr->total_hdrs_len =
			cpu_to_le16(skb_transport_offset(skb) + tcp_hdrlen(skb));
		mac_iocb_ptr->net_trans_offset =
			cpu_to_le16(skb_network_offset(skb) |
				    skb_transport_offset(skb)
				    << OB_MAC_TRANSPORT_HDR_SHIFT);
		mac_iocb_ptr->mss = cpu_to_le16(skb_shinfo(skb)->gso_size);
		mac_iocb_ptr->flags2 |= OB_MAC_TSO_IOCB_LSO;
		अगर (likely(l3_proto == htons(ETH_P_IP))) अणु
			काष्ठा iphdr *iph = ip_hdr(skb);

			iph->check = 0;
			mac_iocb_ptr->flags1 |= OB_MAC_TSO_IOCB_IP4;
			tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr,
								 iph->daddr, 0,
								 IPPROTO_TCP,
								 0);
		पूर्ण अन्यथा अगर (l3_proto == htons(ETH_P_IPV6)) अणु
			mac_iocb_ptr->flags1 |= OB_MAC_TSO_IOCB_IP6;
			tcp_hdr(skb)->check =
				~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
						 &ipv6_hdr(skb)->daddr,
						 0, IPPROTO_TCP, 0);
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qlge_hw_csum_setup(काष्ठा sk_buff *skb,
			       काष्ठा qlge_ob_mac_tso_iocb_req *mac_iocb_ptr)
अणु
	पूर्णांक len;
	काष्ठा iphdr *iph = ip_hdr(skb);
	__sum16 *check;

	mac_iocb_ptr->opcode = OPCODE_OB_MAC_TSO_IOCB;
	mac_iocb_ptr->frame_len = cpu_to_le32((u32)skb->len);
	mac_iocb_ptr->net_trans_offset =
		cpu_to_le16(skb_network_offset(skb) |
			    skb_transport_offset(skb) << OB_MAC_TRANSPORT_HDR_SHIFT);

	mac_iocb_ptr->flags1 |= OB_MAC_TSO_IOCB_IP4;
	len = (ntohs(iph->tot_len) - (iph->ihl << 2));
	अगर (likely(iph->protocol == IPPROTO_TCP)) अणु
		check = &(tcp_hdr(skb)->check);
		mac_iocb_ptr->flags2 |= OB_MAC_TSO_IOCB_TC;
		mac_iocb_ptr->total_hdrs_len =
			cpu_to_le16(skb_transport_offset(skb) +
				    (tcp_hdr(skb)->करोff << 2));
	पूर्ण अन्यथा अणु
		check = &(udp_hdr(skb)->check);
		mac_iocb_ptr->flags2 |= OB_MAC_TSO_IOCB_UC;
		mac_iocb_ptr->total_hdrs_len =
			cpu_to_le16(skb_transport_offset(skb) +
				    माप(काष्ठा udphdr));
	पूर्ण
	*check = ~csum_tcpudp_magic(iph->saddr,
				    iph->daddr, len, iph->protocol, 0);
पूर्ण

अटल netdev_tx_t qlge_send(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	काष्ठा qlge_ob_mac_iocb_req *mac_iocb_ptr;
	काष्ठा tx_ring_desc *tx_ring_desc;
	पूर्णांक tso;
	काष्ठा tx_ring *tx_ring;
	u32 tx_ring_idx = (u32)skb->queue_mapping;

	tx_ring = &qdev->tx_ring[tx_ring_idx];

	अगर (skb_padto(skb, ETH_ZLEN))
		वापस NETDEV_TX_OK;

	अगर (unlikely(atomic_पढ़ो(&tx_ring->tx_count) < 2)) अणु
		netअगर_info(qdev, tx_queued, qdev->ndev,
			   "%s: BUG! shutting down tx queue %d due to lack of resources.\n",
			   __func__, tx_ring_idx);
		netअगर_stop_subqueue(ndev, tx_ring->wq_id);
		tx_ring->tx_errors++;
		वापस NETDEV_TX_BUSY;
	पूर्ण
	tx_ring_desc = &tx_ring->q[tx_ring->prod_idx];
	mac_iocb_ptr = tx_ring_desc->queue_entry;
	स_रखो((व्योम *)mac_iocb_ptr, 0, माप(*mac_iocb_ptr));

	mac_iocb_ptr->opcode = OPCODE_OB_MAC_IOCB;
	mac_iocb_ptr->tid = tx_ring_desc->index;
	/* We use the upper 32-bits to store the tx queue क्रम this IO.
	 * When we get the completion we can use it to establish the context.
	 */
	mac_iocb_ptr->txq_idx = tx_ring_idx;
	tx_ring_desc->skb = skb;

	mac_iocb_ptr->frame_len = cpu_to_le16((u16)skb->len);

	अगर (skb_vlan_tag_present(skb)) अणु
		netअगर_prपूर्णांकk(qdev, tx_queued, KERN_DEBUG, qdev->ndev,
			     "Adding a vlan tag %d.\n", skb_vlan_tag_get(skb));
		mac_iocb_ptr->flags3 |= OB_MAC_IOCB_V;
		mac_iocb_ptr->vlan_tci = cpu_to_le16(skb_vlan_tag_get(skb));
	पूर्ण
	tso = qlge_tso(skb, (काष्ठा qlge_ob_mac_tso_iocb_req *)mac_iocb_ptr);
	अगर (tso < 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण अन्यथा अगर (unlikely(!tso) && (skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		qlge_hw_csum_setup(skb,
				   (काष्ठा qlge_ob_mac_tso_iocb_req *)mac_iocb_ptr);
	पूर्ण
	अगर (qlge_map_send(qdev, mac_iocb_ptr, skb, tx_ring_desc) !=
	    NETDEV_TX_OK) अणु
		netअगर_err(qdev, tx_queued, qdev->ndev,
			  "Could not map the segments.\n");
		tx_ring->tx_errors++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	tx_ring->prod_idx++;
	अगर (tx_ring->prod_idx == tx_ring->wq_len)
		tx_ring->prod_idx = 0;
	wmb();

	qlge_ग_लिखो_db_reg_relaxed(tx_ring->prod_idx, tx_ring->prod_idx_db_reg);
	netअगर_prपूर्णांकk(qdev, tx_queued, KERN_DEBUG, qdev->ndev,
		     "tx queued, slot %d, len %d\n",
		     tx_ring->prod_idx, skb->len);

	atomic_dec(&tx_ring->tx_count);

	अगर (unlikely(atomic_पढ़ो(&tx_ring->tx_count) < 2)) अणु
		netअगर_stop_subqueue(ndev, tx_ring->wq_id);
		अगर ((atomic_पढ़ो(&tx_ring->tx_count) > (tx_ring->wq_len / 4)))
			/*
			 * The queue got stopped because the tx_ring was full.
			 * Wake it up, because it's now at least 25% empty.
			 */
			netअगर_wake_subqueue(qdev->ndev, tx_ring->wq_id);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम qlge_मुक्त_shaकरोw_space(काष्ठा qlge_adapter *qdev)
अणु
	अगर (qdev->rx_ring_shaकरोw_reg_area) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev,
				  PAGE_SIZE,
				  qdev->rx_ring_shaकरोw_reg_area,
				  qdev->rx_ring_shaकरोw_reg_dma);
		qdev->rx_ring_shaकरोw_reg_area = शून्य;
	पूर्ण
	अगर (qdev->tx_ring_shaकरोw_reg_area) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev,
				  PAGE_SIZE,
				  qdev->tx_ring_shaकरोw_reg_area,
				  qdev->tx_ring_shaकरोw_reg_dma);
		qdev->tx_ring_shaकरोw_reg_area = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_alloc_shaकरोw_space(काष्ठा qlge_adapter *qdev)
अणु
	qdev->rx_ring_shaकरोw_reg_area =
		dma_alloc_coherent(&qdev->pdev->dev, PAGE_SIZE,
				   &qdev->rx_ring_shaकरोw_reg_dma, GFP_ATOMIC);
	अगर (!qdev->rx_ring_shaकरोw_reg_area) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Allocation of RX shadow space failed.\n");
		वापस -ENOMEM;
	पूर्ण

	qdev->tx_ring_shaकरोw_reg_area =
		dma_alloc_coherent(&qdev->pdev->dev, PAGE_SIZE,
				   &qdev->tx_ring_shaकरोw_reg_dma, GFP_ATOMIC);
	अगर (!qdev->tx_ring_shaकरोw_reg_area) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Allocation of TX shadow space failed.\n");
		जाओ err_wqp_sh_area;
	पूर्ण
	वापस 0;

err_wqp_sh_area:
	dma_मुक्त_coherent(&qdev->pdev->dev,
			  PAGE_SIZE,
			  qdev->rx_ring_shaकरोw_reg_area,
			  qdev->rx_ring_shaकरोw_reg_dma);
	वापस -ENOMEM;
पूर्ण

अटल व्योम qlge_init_tx_ring(काष्ठा qlge_adapter *qdev, काष्ठा tx_ring *tx_ring)
अणु
	काष्ठा tx_ring_desc *tx_ring_desc;
	पूर्णांक i;
	काष्ठा qlge_ob_mac_iocb_req *mac_iocb_ptr;

	mac_iocb_ptr = tx_ring->wq_base;
	tx_ring_desc = tx_ring->q;
	क्रम (i = 0; i < tx_ring->wq_len; i++) अणु
		tx_ring_desc->index = i;
		tx_ring_desc->skb = शून्य;
		tx_ring_desc->queue_entry = mac_iocb_ptr;
		mac_iocb_ptr++;
		tx_ring_desc++;
	पूर्ण
	atomic_set(&tx_ring->tx_count, tx_ring->wq_len);
पूर्ण

अटल व्योम qlge_मुक्त_tx_resources(काष्ठा qlge_adapter *qdev,
				   काष्ठा tx_ring *tx_ring)
अणु
	अगर (tx_ring->wq_base) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev, tx_ring->wq_size,
				  tx_ring->wq_base, tx_ring->wq_base_dma);
		tx_ring->wq_base = शून्य;
	पूर्ण
	kमुक्त(tx_ring->q);
	tx_ring->q = शून्य;
पूर्ण

अटल पूर्णांक qlge_alloc_tx_resources(काष्ठा qlge_adapter *qdev,
				   काष्ठा tx_ring *tx_ring)
अणु
	tx_ring->wq_base =
		dma_alloc_coherent(&qdev->pdev->dev, tx_ring->wq_size,
				   &tx_ring->wq_base_dma, GFP_ATOMIC);

	अगर (!tx_ring->wq_base ||
	    tx_ring->wq_base_dma & WQ_ADDR_ALIGN)
		जाओ pci_alloc_err;

	tx_ring->q =
		kदो_स्मृति_array(tx_ring->wq_len, माप(काष्ठा tx_ring_desc),
			      GFP_KERNEL);
	अगर (!tx_ring->q)
		जाओ err;

	वापस 0;
err:
	dma_मुक्त_coherent(&qdev->pdev->dev, tx_ring->wq_size,
			  tx_ring->wq_base, tx_ring->wq_base_dma);
	tx_ring->wq_base = शून्य;
pci_alloc_err:
	netअगर_err(qdev, अगरup, qdev->ndev, "tx_ring alloc failed.\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम qlge_मुक्त_lbq_buffers(काष्ठा qlge_adapter *qdev, काष्ठा rx_ring *rx_ring)
अणु
	काष्ठा qlge_bq *lbq = &rx_ring->lbq;
	अचिन्हित पूर्णांक last_offset;

	last_offset = qlge_lbq_block_size(qdev) - qdev->lbq_buf_size;
	जबतक (lbq->next_to_clean != lbq->next_to_use) अणु
		काष्ठा qlge_bq_desc *lbq_desc =
			&lbq->queue[lbq->next_to_clean];

		अगर (lbq_desc->p.pg_chunk.offset == last_offset)
			dma_unmap_page(&qdev->pdev->dev, lbq_desc->dma_addr,
				       qlge_lbq_block_size(qdev),
				       DMA_FROM_DEVICE);
		put_page(lbq_desc->p.pg_chunk.page);

		lbq->next_to_clean = QLGE_BQ_WRAP(lbq->next_to_clean + 1);
	पूर्ण

	अगर (rx_ring->master_chunk.page) अणु
		dma_unmap_page(&qdev->pdev->dev, rx_ring->chunk_dma_addr,
			       qlge_lbq_block_size(qdev), DMA_FROM_DEVICE);
		put_page(rx_ring->master_chunk.page);
		rx_ring->master_chunk.page = शून्य;
	पूर्ण
पूर्ण

अटल व्योम qlge_मुक्त_sbq_buffers(काष्ठा qlge_adapter *qdev, काष्ठा rx_ring *rx_ring)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QLGE_BQ_LEN; i++) अणु
		काष्ठा qlge_bq_desc *sbq_desc = &rx_ring->sbq.queue[i];

		अगर (!sbq_desc) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "sbq_desc %d is NULL.\n", i);
			वापस;
		पूर्ण
		अगर (sbq_desc->p.skb) अणु
			dma_unmap_single(&qdev->pdev->dev, sbq_desc->dma_addr,
					 SMALL_BUF_MAP_SIZE,
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(sbq_desc->p.skb);
			sbq_desc->p.skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Free all large and small rx buffers associated
 * with the completion queues क्रम this device.
 */
अटल व्योम qlge_मुक्त_rx_buffers(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qdev->rx_ring_count; i++) अणु
		काष्ठा rx_ring *rx_ring = &qdev->rx_ring[i];

		अगर (rx_ring->lbq.queue)
			qlge_मुक्त_lbq_buffers(qdev, rx_ring);
		अगर (rx_ring->sbq.queue)
			qlge_मुक्त_sbq_buffers(qdev, rx_ring);
	पूर्ण
पूर्ण

अटल व्योम qlge_alloc_rx_buffers(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qdev->rss_ring_count; i++)
		qlge_update_buffer_queues(&qdev->rx_ring[i], GFP_KERNEL,
					  HZ / 2);
पूर्ण

अटल पूर्णांक qlge_init_bq(काष्ठा qlge_bq *bq)
अणु
	काष्ठा rx_ring *rx_ring = QLGE_BQ_CONTAINER(bq);
	काष्ठा qlge_adapter *qdev = rx_ring->qdev;
	काष्ठा qlge_bq_desc *bq_desc;
	__le64 *buf_ptr;
	पूर्णांक i;

	bq->base = dma_alloc_coherent(&qdev->pdev->dev, QLGE_BQ_SIZE,
				      &bq->base_dma, GFP_ATOMIC);
	अगर (!bq->base) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "ring %u %s allocation failed.\n", rx_ring->cq_id,
			  bq_type_name[bq->type]);
		वापस -ENOMEM;
	पूर्ण

	bq->queue = kदो_स्मृति_array(QLGE_BQ_LEN, माप(काष्ठा qlge_bq_desc),
				  GFP_KERNEL);
	अगर (!bq->queue)
		वापस -ENOMEM;

	buf_ptr = bq->base;
	bq_desc = &bq->queue[0];
	क्रम (i = 0; i < QLGE_BQ_LEN; i++, buf_ptr++, bq_desc++) अणु
		bq_desc->p.skb = शून्य;
		bq_desc->index = i;
		bq_desc->buf_ptr = buf_ptr;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qlge_मुक्त_rx_resources(काष्ठा qlge_adapter *qdev,
				   काष्ठा rx_ring *rx_ring)
अणु
	/* Free the small buffer queue. */
	अगर (rx_ring->sbq.base) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev, QLGE_BQ_SIZE,
				  rx_ring->sbq.base, rx_ring->sbq.base_dma);
		rx_ring->sbq.base = शून्य;
	पूर्ण

	/* Free the small buffer queue control blocks. */
	kमुक्त(rx_ring->sbq.queue);
	rx_ring->sbq.queue = शून्य;

	/* Free the large buffer queue. */
	अगर (rx_ring->lbq.base) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev, QLGE_BQ_SIZE,
				  rx_ring->lbq.base, rx_ring->lbq.base_dma);
		rx_ring->lbq.base = शून्य;
	पूर्ण

	/* Free the large buffer queue control blocks. */
	kमुक्त(rx_ring->lbq.queue);
	rx_ring->lbq.queue = शून्य;

	/* Free the rx queue. */
	अगर (rx_ring->cq_base) अणु
		dma_मुक्त_coherent(&qdev->pdev->dev,
				  rx_ring->cq_size,
				  rx_ring->cq_base, rx_ring->cq_base_dma);
		rx_ring->cq_base = शून्य;
	पूर्ण
पूर्ण

/* Allocate queues and buffers क्रम this completions queue based
 * on the values in the parameter काष्ठाure.
 */
अटल पूर्णांक qlge_alloc_rx_resources(काष्ठा qlge_adapter *qdev,
				   काष्ठा rx_ring *rx_ring)
अणु
	/*
	 * Allocate the completion queue क्रम this rx_ring.
	 */
	rx_ring->cq_base =
		dma_alloc_coherent(&qdev->pdev->dev, rx_ring->cq_size,
				   &rx_ring->cq_base_dma, GFP_ATOMIC);

	अगर (!rx_ring->cq_base) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "rx_ring alloc failed.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (rx_ring->cq_id < qdev->rss_ring_count &&
	    (qlge_init_bq(&rx_ring->sbq) || qlge_init_bq(&rx_ring->lbq))) अणु
		qlge_मुक्त_rx_resources(qdev, rx_ring);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qlge_tx_ring_clean(काष्ठा qlge_adapter *qdev)
अणु
	काष्ठा tx_ring *tx_ring;
	काष्ठा tx_ring_desc *tx_ring_desc;
	पूर्णांक i, j;

	/*
	 * Loop through all queues and मुक्त
	 * any resources.
	 */
	क्रम (j = 0; j < qdev->tx_ring_count; j++) अणु
		tx_ring = &qdev->tx_ring[j];
		क्रम (i = 0; i < tx_ring->wq_len; i++) अणु
			tx_ring_desc = &tx_ring->q[i];
			अगर (tx_ring_desc && tx_ring_desc->skb) अणु
				netअगर_err(qdev, अगरकरोwn, qdev->ndev,
					  "Freeing lost SKB %p, from queue %d, index %d.\n",
					  tx_ring_desc->skb, j,
					  tx_ring_desc->index);
				qlge_unmap_send(qdev, tx_ring_desc,
						tx_ring_desc->map_cnt);
				dev_kमुक्त_skb(tx_ring_desc->skb);
				tx_ring_desc->skb = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qlge_मुक्त_mem_resources(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qdev->tx_ring_count; i++)
		qlge_मुक्त_tx_resources(qdev, &qdev->tx_ring[i]);
	क्रम (i = 0; i < qdev->rx_ring_count; i++)
		qlge_मुक्त_rx_resources(qdev, &qdev->rx_ring[i]);
	qlge_मुक्त_shaकरोw_space(qdev);
पूर्ण

अटल पूर्णांक qlge_alloc_mem_resources(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;

	/* Allocate space क्रम our shaकरोw रेजिस्टरs and such. */
	अगर (qlge_alloc_shaकरोw_space(qdev))
		वापस -ENOMEM;

	क्रम (i = 0; i < qdev->rx_ring_count; i++) अणु
		अगर (qlge_alloc_rx_resources(qdev, &qdev->rx_ring[i]) != 0) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "RX resource allocation failed.\n");
			जाओ err_mem;
		पूर्ण
	पूर्ण
	/* Allocate tx queue resources */
	क्रम (i = 0; i < qdev->tx_ring_count; i++) अणु
		अगर (qlge_alloc_tx_resources(qdev, &qdev->tx_ring[i]) != 0) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "TX resource allocation failed.\n");
			जाओ err_mem;
		पूर्ण
	पूर्ण
	वापस 0;

err_mem:
	qlge_मुक्त_mem_resources(qdev);
	वापस -ENOMEM;
पूर्ण

/* Set up the rx ring control block and pass it to the chip.
 * The control block is defined as
 * "Completion Queue Initialization Control Block", or cqicb.
 */
अटल पूर्णांक qlge_start_rx_ring(काष्ठा qlge_adapter *qdev, काष्ठा rx_ring *rx_ring)
अणु
	काष्ठा cqicb *cqicb = &rx_ring->cqicb;
	व्योम *shaकरोw_reg = qdev->rx_ring_shaकरोw_reg_area +
		(rx_ring->cq_id * RX_RING_SHADOW_SPACE);
	u64 shaकरोw_reg_dma = qdev->rx_ring_shaकरोw_reg_dma +
		(rx_ring->cq_id * RX_RING_SHADOW_SPACE);
	व्योम __iomem *करोorbell_area =
		qdev->करोorbell_area + (DB_PAGE_SIZE * (128 + rx_ring->cq_id));
	पूर्णांक err = 0;
	u64 पंचांगp;
	__le64 *base_indirect_ptr;
	पूर्णांक page_entries;

	/* Set up the shaकरोw रेजिस्टरs क्रम this ring. */
	rx_ring->prod_idx_sh_reg = shaकरोw_reg;
	rx_ring->prod_idx_sh_reg_dma = shaकरोw_reg_dma;
	*rx_ring->prod_idx_sh_reg = 0;
	shaकरोw_reg += माप(u64);
	shaकरोw_reg_dma += माप(u64);
	rx_ring->lbq.base_indirect = shaकरोw_reg;
	rx_ring->lbq.base_indirect_dma = shaकरोw_reg_dma;
	shaकरोw_reg += (माप(u64) * MAX_DB_PAGES_PER_BQ(QLGE_BQ_LEN));
	shaकरोw_reg_dma += (माप(u64) * MAX_DB_PAGES_PER_BQ(QLGE_BQ_LEN));
	rx_ring->sbq.base_indirect = shaकरोw_reg;
	rx_ring->sbq.base_indirect_dma = shaकरोw_reg_dma;

	/* PCI करोorbell mem area + 0x00 क्रम consumer index रेजिस्टर */
	rx_ring->cnsmr_idx_db_reg = (u32 __iomem *)करोorbell_area;
	rx_ring->cnsmr_idx = 0;
	rx_ring->curr_entry = rx_ring->cq_base;

	/* PCI करोorbell mem area + 0x04 क्रम valid रेजिस्टर */
	rx_ring->valid_db_reg = करोorbell_area + 0x04;

	/* PCI करोorbell mem area + 0x18 क्रम large buffer consumer */
	rx_ring->lbq.prod_idx_db_reg = (u32 __iomem *)(करोorbell_area + 0x18);

	/* PCI करोorbell mem area + 0x1c */
	rx_ring->sbq.prod_idx_db_reg = (u32 __iomem *)(करोorbell_area + 0x1c);

	स_रखो((व्योम *)cqicb, 0, माप(काष्ठा cqicb));
	cqicb->msix_vect = rx_ring->irq;

	cqicb->len = cpu_to_le16(QLGE_FIT16(rx_ring->cq_len) | LEN_V |
				 LEN_CPP_CONT);

	cqicb->addr = cpu_to_le64(rx_ring->cq_base_dma);

	cqicb->prod_idx_addr = cpu_to_le64(rx_ring->prod_idx_sh_reg_dma);

	/*
	 * Set up the control block load flags.
	 */
	cqicb->flags = FLAGS_LC |	/* Load queue base address */
		FLAGS_LV |		/* Load MSI-X vector */
		FLAGS_LI;		/* Load irq delay values */
	अगर (rx_ring->cq_id < qdev->rss_ring_count) अणु
		cqicb->flags |= FLAGS_LL;	/* Load lbq values */
		पंचांगp = (u64)rx_ring->lbq.base_dma;
		base_indirect_ptr = rx_ring->lbq.base_indirect;
		page_entries = 0;
		करो अणु
			*base_indirect_ptr = cpu_to_le64(पंचांगp);
			पंचांगp += DB_PAGE_SIZE;
			base_indirect_ptr++;
			page_entries++;
		पूर्ण जबतक (page_entries < MAX_DB_PAGES_PER_BQ(QLGE_BQ_LEN));
		cqicb->lbq_addr = cpu_to_le64(rx_ring->lbq.base_indirect_dma);
		cqicb->lbq_buf_size =
			cpu_to_le16(QLGE_FIT16(qdev->lbq_buf_size));
		cqicb->lbq_len = cpu_to_le16(QLGE_FIT16(QLGE_BQ_LEN));
		rx_ring->lbq.next_to_use = 0;
		rx_ring->lbq.next_to_clean = 0;

		cqicb->flags |= FLAGS_LS;	/* Load sbq values */
		पंचांगp = (u64)rx_ring->sbq.base_dma;
		base_indirect_ptr = rx_ring->sbq.base_indirect;
		page_entries = 0;
		करो अणु
			*base_indirect_ptr = cpu_to_le64(पंचांगp);
			पंचांगp += DB_PAGE_SIZE;
			base_indirect_ptr++;
			page_entries++;
		पूर्ण जबतक (page_entries < MAX_DB_PAGES_PER_BQ(QLGE_BQ_LEN));
		cqicb->sbq_addr =
			cpu_to_le64(rx_ring->sbq.base_indirect_dma);
		cqicb->sbq_buf_size = cpu_to_le16(SMALL_BUFFER_SIZE);
		cqicb->sbq_len = cpu_to_le16(QLGE_FIT16(QLGE_BQ_LEN));
		rx_ring->sbq.next_to_use = 0;
		rx_ring->sbq.next_to_clean = 0;
	पूर्ण
	अगर (rx_ring->cq_id < qdev->rss_ring_count) अणु
		/* Inbound completion handling rx_rings run in
		 * separate NAPI contexts.
		 */
		netअगर_napi_add(qdev->ndev, &rx_ring->napi, qlge_napi_poll_msix,
			       64);
		cqicb->irq_delay = cpu_to_le16(qdev->rx_coalesce_usecs);
		cqicb->pkt_delay = cpu_to_le16(qdev->rx_max_coalesced_frames);
	पूर्ण अन्यथा अणु
		cqicb->irq_delay = cpu_to_le16(qdev->tx_coalesce_usecs);
		cqicb->pkt_delay = cpu_to_le16(qdev->tx_max_coalesced_frames);
	पूर्ण
	err = qlge_ग_लिखो_cfg(qdev, cqicb, माप(काष्ठा cqicb),
			     CFG_LCQ, rx_ring->cq_id);
	अगर (err) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Failed to load CQICB.\n");
		वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक qlge_start_tx_ring(काष्ठा qlge_adapter *qdev, काष्ठा tx_ring *tx_ring)
अणु
	काष्ठा wqicb *wqicb = (काष्ठा wqicb *)tx_ring;
	व्योम __iomem *करोorbell_area =
		qdev->करोorbell_area + (DB_PAGE_SIZE * tx_ring->wq_id);
	व्योम *shaकरोw_reg = qdev->tx_ring_shaकरोw_reg_area +
		(tx_ring->wq_id * माप(u64));
	u64 shaकरोw_reg_dma = qdev->tx_ring_shaकरोw_reg_dma +
		(tx_ring->wq_id * माप(u64));
	पूर्णांक err = 0;

	/*
	 * Assign करोorbell रेजिस्टरs क्रम this tx_ring.
	 */
	/* TX PCI करोorbell mem area क्रम tx producer index */
	tx_ring->prod_idx_db_reg = (u32 __iomem *)करोorbell_area;
	tx_ring->prod_idx = 0;
	/* TX PCI करोorbell mem area + 0x04 */
	tx_ring->valid_db_reg = करोorbell_area + 0x04;

	/*
	 * Assign shaकरोw रेजिस्टरs क्रम this tx_ring.
	 */
	tx_ring->cnsmr_idx_sh_reg = shaकरोw_reg;
	tx_ring->cnsmr_idx_sh_reg_dma = shaकरोw_reg_dma;

	wqicb->len = cpu_to_le16(tx_ring->wq_len | Q_LEN_V | Q_LEN_CPP_CONT);
	wqicb->flags = cpu_to_le16(Q_FLAGS_LC |
				   Q_FLAGS_LB | Q_FLAGS_LI | Q_FLAGS_LO);
	wqicb->cq_id_rss = cpu_to_le16(tx_ring->cq_id);
	wqicb->rid = 0;
	wqicb->addr = cpu_to_le64(tx_ring->wq_base_dma);

	wqicb->cnsmr_idx_addr = cpu_to_le64(tx_ring->cnsmr_idx_sh_reg_dma);

	qlge_init_tx_ring(qdev, tx_ring);

	err = qlge_ग_लिखो_cfg(qdev, wqicb, माप(*wqicb), CFG_LRQ,
			     (u16)tx_ring->wq_id);
	अगर (err) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Failed to load tx_ring.\n");
		वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम qlge_disable_msix(काष्ठा qlge_adapter *qdev)
अणु
	अगर (test_bit(QL_MSIX_ENABLED, &qdev->flags)) अणु
		pci_disable_msix(qdev->pdev);
		clear_bit(QL_MSIX_ENABLED, &qdev->flags);
		kमुक्त(qdev->msi_x_entry);
		qdev->msi_x_entry = शून्य;
	पूर्ण अन्यथा अगर (test_bit(QL_MSI_ENABLED, &qdev->flags)) अणु
		pci_disable_msi(qdev->pdev);
		clear_bit(QL_MSI_ENABLED, &qdev->flags);
	पूर्ण
पूर्ण

/* We start by trying to get the number of vectors
 * stored in qdev->पूर्णांकr_count. If we करोn't get that
 * many then we reduce the count and try again.
 */
अटल व्योम qlge_enable_msix(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i, err;

	/* Get the MSIX vectors. */
	अगर (qlge_irq_type == MSIX_IRQ) अणु
		/* Try to alloc space क्रम the msix काष्ठा,
		 * अगर it fails then go to MSI/legacy.
		 */
		qdev->msi_x_entry = kसुस्मृति(qdev->पूर्णांकr_count,
					    माप(काष्ठा msix_entry),
					    GFP_KERNEL);
		अगर (!qdev->msi_x_entry) अणु
			qlge_irq_type = MSI_IRQ;
			जाओ msi;
		पूर्ण

		क्रम (i = 0; i < qdev->पूर्णांकr_count; i++)
			qdev->msi_x_entry[i].entry = i;

		err = pci_enable_msix_range(qdev->pdev, qdev->msi_x_entry,
					    1, qdev->पूर्णांकr_count);
		अगर (err < 0) अणु
			kमुक्त(qdev->msi_x_entry);
			qdev->msi_x_entry = शून्य;
			netअगर_warn(qdev, अगरup, qdev->ndev,
				   "MSI-X Enable failed, trying MSI.\n");
			qlge_irq_type = MSI_IRQ;
		पूर्ण अन्यथा अणु
			qdev->पूर्णांकr_count = err;
			set_bit(QL_MSIX_ENABLED, &qdev->flags);
			netअगर_info(qdev, अगरup, qdev->ndev,
				   "MSI-X Enabled, got %d vectors.\n",
				   qdev->पूर्णांकr_count);
			वापस;
		पूर्ण
	पूर्ण
msi:
	qdev->पूर्णांकr_count = 1;
	अगर (qlge_irq_type == MSI_IRQ) अणु
		अगर (pci_alloc_irq_vectors(qdev->pdev, 1, 1, PCI_IRQ_MSI) >= 0) अणु
			set_bit(QL_MSI_ENABLED, &qdev->flags);
			netअगर_info(qdev, अगरup, qdev->ndev,
				   "Running with MSI interrupts.\n");
			वापस;
		पूर्ण
	पूर्ण
	qlge_irq_type = LEG_IRQ;
	set_bit(QL_LEGACY_ENABLED, &qdev->flags);
	netअगर_prपूर्णांकk(qdev, अगरup, KERN_DEBUG, qdev->ndev,
		     "Running with legacy interrupts.\n");
पूर्ण

/* Each vector services 1 RSS ring and 1 or more
 * TX completion rings.  This function loops through
 * the TX completion rings and assigns the vector that
 * will service it.  An example would be अगर there are
 * 2 vectors (so 2 RSS rings) and 8 TX completion rings.
 * This would mean that vector 0 would service RSS ring 0
 * and TX completion rings 0,1,2 and 3.  Vector 1 would
 * service RSS ring 1 and TX completion rings 4,5,6 and 7.
 */
अटल व्योम qlge_set_tx_vect(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i, j, vect;
	u32 tx_rings_per_vector = qdev->tx_ring_count / qdev->पूर्णांकr_count;

	अगर (likely(test_bit(QL_MSIX_ENABLED, &qdev->flags))) अणु
		/* Assign irq vectors to TX rx_rings.*/
		क्रम (vect = 0, j = 0, i = qdev->rss_ring_count;
		     i < qdev->rx_ring_count; i++) अणु
			अगर (j == tx_rings_per_vector) अणु
				vect++;
				j = 0;
			पूर्ण
			qdev->rx_ring[i].irq = vect;
			j++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* For single vector all rings have an irq
		 * of zero.
		 */
		क्रम (i = 0; i < qdev->rx_ring_count; i++)
			qdev->rx_ring[i].irq = 0;
	पूर्ण
पूर्ण

/* Set the पूर्णांकerrupt mask क्रम this vector.  Each vector
 * will service 1 RSS ring and 1 or more TX completion
 * rings.  This function sets up a bit mask per vector
 * that indicates which rings it services.
 */
अटल व्योम qlge_set_irq_mask(काष्ठा qlge_adapter *qdev, काष्ठा पूर्णांकr_context *ctx)
अणु
	पूर्णांक j, vect = ctx->पूर्णांकr;
	u32 tx_rings_per_vector = qdev->tx_ring_count / qdev->पूर्णांकr_count;

	अगर (likely(test_bit(QL_MSIX_ENABLED, &qdev->flags))) अणु
		/* Add the RSS ring serviced by this vector
		 * to the mask.
		 */
		ctx->irq_mask = (1 << qdev->rx_ring[vect].cq_id);
		/* Add the TX ring(s) serviced by this vector
		 * to the mask.
		 */
		क्रम (j = 0; j < tx_rings_per_vector; j++) अणु
			ctx->irq_mask |=
				(1 << qdev->rx_ring[qdev->rss_ring_count +
				 (vect * tx_rings_per_vector) + j].cq_id);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* For single vector we just shअगरt each queue's
		 * ID पूर्णांकo the mask.
		 */
		क्रम (j = 0; j < qdev->rx_ring_count; j++)
			ctx->irq_mask |= (1 << qdev->rx_ring[j].cq_id);
	पूर्ण
पूर्ण

/*
 * Here we build the पूर्णांकr_context काष्ठाures based on
 * our rx_ring count and पूर्णांकr vector count.
 * The पूर्णांकr_context काष्ठाure is used to hook each vector
 * to possibly dअगरferent handlers.
 */
अटल व्योम qlge_resolve_queues_to_irqs(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i = 0;
	काष्ठा पूर्णांकr_context *पूर्णांकr_context = &qdev->पूर्णांकr_context[0];

	अगर (likely(test_bit(QL_MSIX_ENABLED, &qdev->flags))) अणु
		/* Each rx_ring has it's
		 * own पूर्णांकr_context since we have separate
		 * vectors क्रम each queue.
		 */
		क्रम (i = 0; i < qdev->पूर्णांकr_count; i++, पूर्णांकr_context++) अणु
			qdev->rx_ring[i].irq = i;
			पूर्णांकr_context->पूर्णांकr = i;
			पूर्णांकr_context->qdev = qdev;
			/* Set up this vector's bit-mask that indicates
			 * which queues it services.
			 */
			qlge_set_irq_mask(qdev, पूर्णांकr_context);
			/*
			 * We set up each vectors enable/disable/पढ़ो bits so
			 * there's no bit/mask calculations in the critical path.
			 */
			पूर्णांकr_context->पूर्णांकr_en_mask =
				INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
				INTR_EN_TYPE_ENABLE | INTR_EN_IHD_MASK | INTR_EN_IHD
				| i;
			पूर्णांकr_context->पूर्णांकr_dis_mask =
				INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
				INTR_EN_TYPE_DISABLE | INTR_EN_IHD_MASK |
				INTR_EN_IHD | i;
			पूर्णांकr_context->पूर्णांकr_पढ़ो_mask =
				INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
				INTR_EN_TYPE_READ | INTR_EN_IHD_MASK | INTR_EN_IHD |
				i;
			अगर (i == 0) अणु
				/* The first vector/queue handles
				 * broadcast/multicast, fatal errors,
				 * and firmware events.  This in addition
				 * to normal inbound NAPI processing.
				 */
				पूर्णांकr_context->handler = qlge_isr;
				प्र_लिखो(पूर्णांकr_context->name, "%s-rx-%d",
					qdev->ndev->name, i);
			पूर्ण अन्यथा अणु
				/*
				 * Inbound queues handle unicast frames only.
				 */
				पूर्णांकr_context->handler = qlge_msix_rx_isr;
				प्र_लिखो(पूर्णांकr_context->name, "%s-rx-%d",
					qdev->ndev->name, i);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * All rx_rings use the same पूर्णांकr_context since
		 * there is only one vector.
		 */
		पूर्णांकr_context->पूर्णांकr = 0;
		पूर्णांकr_context->qdev = qdev;
		/*
		 * We set up each vectors enable/disable/पढ़ो bits so
		 * there's no bit/mask calculations in the critical path.
		 */
		पूर्णांकr_context->पूर्णांकr_en_mask =
			INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK | INTR_EN_TYPE_ENABLE;
		पूर्णांकr_context->पूर्णांकr_dis_mask =
			INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
			INTR_EN_TYPE_DISABLE;
		अगर (test_bit(QL_LEGACY_ENABLED, &qdev->flags)) अणु
			/* Experience shows that when using INTx पूर्णांकerrupts,
			 * the device करोes not always स्वतः-mask INTR_EN_EN.
			 * Moreover, masking INTR_EN_EN manually करोes not
			 * immediately prevent पूर्णांकerrupt generation.
			 */
			पूर्णांकr_context->पूर्णांकr_en_mask |= INTR_EN_EI << 16 |
				INTR_EN_EI;
			पूर्णांकr_context->पूर्णांकr_dis_mask |= INTR_EN_EI << 16;
		पूर्ण
		पूर्णांकr_context->पूर्णांकr_पढ़ो_mask =
			INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK | INTR_EN_TYPE_READ;
		/*
		 * Single पूर्णांकerrupt means one handler क्रम all rings.
		 */
		पूर्णांकr_context->handler = qlge_isr;
		प्र_लिखो(पूर्णांकr_context->name, "%s-single_irq", qdev->ndev->name);
		/* Set up this vector's bit-mask that indicates
		 * which queues it services. In this हाल there is
		 * a single vector so it will service all RSS and
		 * TX completion rings.
		 */
		qlge_set_irq_mask(qdev, पूर्णांकr_context);
	पूर्ण
	/* Tell the TX completion rings which MSIx vector
	 * they will be using.
	 */
	qlge_set_tx_vect(qdev);
पूर्ण

अटल व्योम qlge_मुक्त_irq(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;
	काष्ठा पूर्णांकr_context *पूर्णांकr_context = &qdev->पूर्णांकr_context[0];

	क्रम (i = 0; i < qdev->पूर्णांकr_count; i++, पूर्णांकr_context++) अणु
		अगर (पूर्णांकr_context->hooked) अणु
			अगर (test_bit(QL_MSIX_ENABLED, &qdev->flags)) अणु
				मुक्त_irq(qdev->msi_x_entry[i].vector,
					 &qdev->rx_ring[i]);
			पूर्ण अन्यथा अणु
				मुक्त_irq(qdev->pdev->irq, &qdev->rx_ring[0]);
			पूर्ण
		पूर्ण
	पूर्ण
	qlge_disable_msix(qdev);
पूर्ण

अटल पूर्णांक qlge_request_irq(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;
	पूर्णांक status = 0;
	काष्ठा pci_dev *pdev = qdev->pdev;
	काष्ठा पूर्णांकr_context *पूर्णांकr_context = &qdev->पूर्णांकr_context[0];

	qlge_resolve_queues_to_irqs(qdev);

	क्रम (i = 0; i < qdev->पूर्णांकr_count; i++, पूर्णांकr_context++) अणु
		अगर (test_bit(QL_MSIX_ENABLED, &qdev->flags)) अणु
			status = request_irq(qdev->msi_x_entry[i].vector,
					     पूर्णांकr_context->handler,
					     0,
					     पूर्णांकr_context->name,
					     &qdev->rx_ring[i]);
			अगर (status) अणु
				netअगर_err(qdev, अगरup, qdev->ndev,
					  "Failed request for MSIX interrupt %d.\n",
					  i);
				जाओ err_irq;
			पूर्ण
		पूर्ण अन्यथा अणु
			netअगर_prपूर्णांकk(qdev, अगरup, KERN_DEBUG, qdev->ndev,
				     "trying msi or legacy interrupts.\n");
			netअगर_prपूर्णांकk(qdev, अगरup, KERN_DEBUG, qdev->ndev,
				     "%s: irq = %d.\n", __func__, pdev->irq);
			netअगर_prपूर्णांकk(qdev, अगरup, KERN_DEBUG, qdev->ndev,
				     "%s: context->name = %s.\n", __func__,
				     पूर्णांकr_context->name);
			netअगर_prपूर्णांकk(qdev, अगरup, KERN_DEBUG, qdev->ndev,
				     "%s: dev_id = 0x%p.\n", __func__,
				     &qdev->rx_ring[0]);
			status =
				request_irq(pdev->irq, qlge_isr,
					    test_bit(QL_MSI_ENABLED, &qdev->flags)
					    ? 0
					    : IRQF_SHARED,
					    पूर्णांकr_context->name, &qdev->rx_ring[0]);
			अगर (status)
				जाओ err_irq;

			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Hooked intr 0, queue type RX_Q, with name %s.\n",
				  पूर्णांकr_context->name);
		पूर्ण
		पूर्णांकr_context->hooked = 1;
	पूर्ण
	वापस status;
err_irq:
	netअगर_err(qdev, अगरup, qdev->ndev, "Failed to get the interrupts!!!\n");
	qlge_मुक्त_irq(qdev);
	वापस status;
पूर्ण

अटल पूर्णांक qlge_start_rss(काष्ठा qlge_adapter *qdev)
अणु
	अटल स्थिर u8 init_hash_seed[] = अणु
		0x6d, 0x5a, 0x56, 0xda, 0x25, 0x5b, 0x0e, 0xc2,
		0x41, 0x67, 0x25, 0x3d, 0x43, 0xa3, 0x8f, 0xb0,
		0xd0, 0xca, 0x2b, 0xcb, 0xae, 0x7b, 0x30, 0xb4,
		0x77, 0xcb, 0x2d, 0xa3, 0x80, 0x30, 0xf2, 0x0c,
		0x6a, 0x42, 0xb7, 0x3b, 0xbe, 0xac, 0x01, 0xfa
	पूर्ण;
	काष्ठा ricb *ricb = &qdev->ricb;
	पूर्णांक status = 0;
	पूर्णांक i;
	u8 *hash_id = (u8 *)ricb->hash_cq_id;

	स_रखो((व्योम *)ricb, 0, माप(*ricb));

	ricb->base_cq = RSS_L4K;
	ricb->flags =
		(RSS_L6K | RSS_LI | RSS_LB | RSS_LM | RSS_RT4 | RSS_RT6);
	ricb->mask = cpu_to_le16((u16)(0x3ff));

	/*
	 * Fill out the Indirection Table.
	 */
	क्रम (i = 0; i < 1024; i++)
		hash_id[i] = (i & (qdev->rss_ring_count - 1));

	स_नकल((व्योम *)&ricb->ipv6_hash_key[0], init_hash_seed, 40);
	स_नकल((व्योम *)&ricb->ipv4_hash_key[0], init_hash_seed, 16);

	status = qlge_ग_लिखो_cfg(qdev, ricb, माप(*ricb), CFG_LR, 0);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Failed to load RICB.\n");
		वापस status;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक qlge_clear_routing_entries(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i, status = 0;

	status = qlge_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	अगर (status)
		वापस status;
	/* Clear all the entries in the routing table. */
	क्रम (i = 0; i < 16; i++) अणु
		status = qlge_set_routing_reg(qdev, i, 0, 0);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Failed to init routing register for CAM packets.\n");
			अवरोध;
		पूर्ण
	पूर्ण
	qlge_sem_unlock(qdev, SEM_RT_IDX_MASK);
	वापस status;
पूर्ण

/* Initialize the frame-to-queue routing. */
अटल पूर्णांक qlge_route_initialize(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status = 0;

	/* Clear all the entries in the routing table. */
	status = qlge_clear_routing_entries(qdev);
	अगर (status)
		वापस status;

	status = qlge_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	अगर (status)
		वापस status;

	status = qlge_set_routing_reg(qdev, RT_IDX_IP_CSUM_ERR_SLOT,
				      RT_IDX_IP_CSUM_ERR, 1);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to init routing register for IP CSUM error packets.\n");
		जाओ निकास;
	पूर्ण
	status = qlge_set_routing_reg(qdev, RT_IDX_TCP_UDP_CSUM_ERR_SLOT,
				      RT_IDX_TU_CSUM_ERR, 1);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to init routing register for TCP/UDP CSUM error packets.\n");
		जाओ निकास;
	पूर्ण
	status = qlge_set_routing_reg(qdev, RT_IDX_BCAST_SLOT, RT_IDX_BCAST, 1);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to init routing register for broadcast packets.\n");
		जाओ निकास;
	पूर्ण
	/* If we have more than one inbound queue, then turn on RSS in the
	 * routing block.
	 */
	अगर (qdev->rss_ring_count > 1) अणु
		status = qlge_set_routing_reg(qdev, RT_IDX_RSS_MATCH_SLOT,
					      RT_IDX_RSS_MATCH, 1);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Failed to init routing register for MATCH RSS packets.\n");
			जाओ निकास;
		पूर्ण
	पूर्ण

	status = qlge_set_routing_reg(qdev, RT_IDX_CAM_HIT_SLOT,
				      RT_IDX_CAM_HIT, 1);
	अगर (status)
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to init routing register for CAM packets.\n");
निकास:
	qlge_sem_unlock(qdev, SEM_RT_IDX_MASK);
	वापस status;
पूर्ण

पूर्णांक qlge_cam_route_initialize(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status, set;

	/* If check अगर the link is up and use to
	 * determine अगर we are setting or clearing
	 * the MAC address in the CAM.
	 */
	set = qlge_पढ़ो32(qdev, STS);
	set &= qdev->port_link_up;
	status = qlge_set_mac_addr(qdev, set);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Failed to init mac address.\n");
		वापस status;
	पूर्ण

	status = qlge_route_initialize(qdev);
	अगर (status)
		netअगर_err(qdev, अगरup, qdev->ndev, "Failed to init routing table.\n");

	वापस status;
पूर्ण

अटल पूर्णांक qlge_adapter_initialize(काष्ठा qlge_adapter *qdev)
अणु
	u32 value, mask;
	पूर्णांक i;
	पूर्णांक status = 0;

	/*
	 * Set up the System रेजिस्टर to halt on errors.
	 */
	value = SYS_EFE | SYS_FAE;
	mask = value << 16;
	qlge_ग_लिखो32(qdev, SYS, mask | value);

	/* Set the शेष queue, and VLAN behavior. */
	value = NIC_RCV_CFG_DFQ;
	mask = NIC_RCV_CFG_DFQ_MASK;
	अगर (qdev->ndev->features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		value |= NIC_RCV_CFG_RV;
		mask |= (NIC_RCV_CFG_RV << 16);
	पूर्ण
	qlge_ग_लिखो32(qdev, NIC_RCV_CFG, (mask | value));

	/* Set the MPI पूर्णांकerrupt to enabled. */
	qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16) | INTR_MASK_PI);

	/* Enable the function, set pagesize, enable error checking. */
	value = FSC_FE | FSC_EPC_INBOUND | FSC_EPC_OUTBOUND |
		FSC_EC | FSC_VM_PAGE_4K;
	value |= SPLT_SETTING;

	/* Set/clear header splitting. */
	mask = FSC_VM_PAGESIZE_MASK |
		FSC_DBL_MASK | FSC_DBRST_MASK | (value << 16);
	qlge_ग_लिखो32(qdev, FSC, mask | value);

	qlge_ग_लिखो32(qdev, SPLT_HDR, SPLT_LEN);

	/* Set RX packet routing to use port/pci function on which the
	 * packet arrived on in addition to usual frame routing.
	 * This is helpful on bonding where both पूर्णांकerfaces can have
	 * the same MAC address.
	 */
	qlge_ग_लिखो32(qdev, RST_FO, RST_FO_RR_MASK | RST_FO_RR_RCV_FUNC_CQ);
	/* Reroute all packets to our Interface.
	 * They may have been routed to MPI firmware
	 * due to WOL.
	 */
	value = qlge_पढ़ो32(qdev, MGMT_RCV_CFG);
	value &= ~MGMT_RCV_CFG_RM;
	mask = 0xffff0000;

	/* Sticky reg needs clearing due to WOL. */
	qlge_ग_लिखो32(qdev, MGMT_RCV_CFG, mask);
	qlge_ग_लिखो32(qdev, MGMT_RCV_CFG, mask | value);

	/* Default WOL is enable on Mezz cards */
	अगर (qdev->pdev->subप्रणाली_device == 0x0068 ||
	    qdev->pdev->subप्रणाली_device == 0x0180)
		qdev->wol = WAKE_MAGIC;

	/* Start up the rx queues. */
	क्रम (i = 0; i < qdev->rx_ring_count; i++) अणु
		status = qlge_start_rx_ring(qdev, &qdev->rx_ring[i]);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Failed to start rx ring[%d].\n", i);
			वापस status;
		पूर्ण
	पूर्ण

	/* If there is more than one inbound completion queue
	 * then करोwnload a RICB to configure RSS.
	 */
	अगर (qdev->rss_ring_count > 1) अणु
		status = qlge_start_rss(qdev);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev, "Failed to start RSS.\n");
			वापस status;
		पूर्ण
	पूर्ण

	/* Start up the tx queues. */
	क्रम (i = 0; i < qdev->tx_ring_count; i++) अणु
		status = qlge_start_tx_ring(qdev, &qdev->tx_ring[i]);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Failed to start tx ring[%d].\n", i);
			वापस status;
		पूर्ण
	पूर्ण

	/* Initialize the port and set the max framesize. */
	status = qdev->nic_ops->port_initialize(qdev);
	अगर (status)
		netअगर_err(qdev, अगरup, qdev->ndev, "Failed to start port.\n");

	/* Set up the MAC address and frame routing filter. */
	status = qlge_cam_route_initialize(qdev);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Failed to init CAM/Routing tables.\n");
		वापस status;
	पूर्ण

	/* Start NAPI क्रम the RSS queues. */
	क्रम (i = 0; i < qdev->rss_ring_count; i++)
		napi_enable(&qdev->rx_ring[i].napi);

	वापस status;
पूर्ण

/* Issue soft reset to chip. */
अटल पूर्णांक qlge_adapter_reset(काष्ठा qlge_adapter *qdev)
अणु
	u32 value;
	पूर्णांक status = 0;
	अचिन्हित दीर्घ end_jअगरfies;

	/* Clear all the entries in the routing table. */
	status = qlge_clear_routing_entries(qdev);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Failed to clear routing bits.\n");
		वापस status;
	पूर्ण

	/* Check अगर bit is set then skip the mailbox command and
	 * clear the bit, अन्यथा we are in normal reset process.
	 */
	अगर (!test_bit(QL_ASIC_RECOVERY, &qdev->flags)) अणु
		/* Stop management traffic. */
		qlge_mb_set_mgmnt_traffic_ctl(qdev, MB_SET_MPI_TFK_STOP);

		/* Wait क्रम the NIC and MGMNT FIFOs to empty. */
		qlge_रुको_fअगरo_empty(qdev);
	पूर्ण अन्यथा अणु
		clear_bit(QL_ASIC_RECOVERY, &qdev->flags);
	पूर्ण

	qlge_ग_लिखो32(qdev, RST_FO, (RST_FO_FR << 16) | RST_FO_FR);

	end_jअगरfies = jअगरfies + usecs_to_jअगरfies(30);
	करो अणु
		value = qlge_पढ़ो32(qdev, RST_FO);
		अगर ((value & RST_FO_FR) == 0)
			अवरोध;
		cpu_relax();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_jअगरfies));

	अगर (value & RST_FO_FR) अणु
		netअगर_err(qdev, अगरकरोwn, qdev->ndev,
			  "ETIMEDOUT!!! errored out of resetting the chip!\n");
		status = -ETIMEDOUT;
	पूर्ण

	/* Resume management traffic. */
	qlge_mb_set_mgmnt_traffic_ctl(qdev, MB_SET_MPI_TFK_RESUME);
	वापस status;
पूर्ण

अटल व्योम qlge_display_dev_info(काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	netअगर_info(qdev, probe, qdev->ndev,
		   "Function #%d, Port %d, NIC Roll %d, NIC Rev = %d, XG Roll = %d, XG Rev = %d.\n",
		   qdev->func,
		   qdev->port,
		   qdev->chip_rev_id & 0x0000000f,
		   qdev->chip_rev_id >> 4 & 0x0000000f,
		   qdev->chip_rev_id >> 8 & 0x0000000f,
		   qdev->chip_rev_id >> 12 & 0x0000000f);
	netअगर_info(qdev, probe, qdev->ndev,
		   "MAC address %pM\n", ndev->dev_addr);
पूर्ण

अटल पूर्णांक qlge_wol(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status = 0;
	u32 wol = MB_WOL_DISABLE;

	/* The CAM is still पूर्णांकact after a reset, but अगर we
	 * are करोing WOL, then we may need to program the
	 * routing regs. We would also need to issue the mailbox
	 * commands to inकाष्ठा the MPI what to करो per the ethtool
	 * settings.
	 */

	अगर (qdev->wol & (WAKE_ARP | WAKE_MAGICSECURE | WAKE_PHY | WAKE_UCAST |
			 WAKE_MCAST | WAKE_BCAST)) अणु
		netअगर_err(qdev, अगरकरोwn, qdev->ndev,
			  "Unsupported WOL parameter. qdev->wol = 0x%x.\n",
			  qdev->wol);
		वापस -EINVAL;
	पूर्ण

	अगर (qdev->wol & WAKE_MAGIC) अणु
		status = qlge_mb_wol_set_magic(qdev, 1);
		अगर (status) अणु
			netअगर_err(qdev, अगरकरोwn, qdev->ndev,
				  "Failed to set magic packet on %s.\n",
				  qdev->ndev->name);
			वापस status;
		पूर्ण
		netअगर_info(qdev, drv, qdev->ndev,
			   "Enabled magic packet successfully on %s.\n",
			   qdev->ndev->name);

		wol |= MB_WOL_MAGIC_PKT;
	पूर्ण

	अगर (qdev->wol) अणु
		wol |= MB_WOL_MODE_ON;
		status = qlge_mb_wol_mode(qdev, wol);
		netअगर_err(qdev, drv, qdev->ndev,
			  "WOL %s (wol code 0x%x) on %s\n",
			  (status == 0) ? "Successfully set" : "Failed",
			  wol, qdev->ndev->name);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम qlge_cancel_all_work_sync(काष्ठा qlge_adapter *qdev)
अणु
	/* Don't समाप्त the reset worker thपढ़ो अगर we
	 * are in the process of recovery.
	 */
	अगर (test_bit(QL_ADAPTER_UP, &qdev->flags))
		cancel_delayed_work_sync(&qdev->asic_reset_work);
	cancel_delayed_work_sync(&qdev->mpi_reset_work);
	cancel_delayed_work_sync(&qdev->mpi_work);
	cancel_delayed_work_sync(&qdev->mpi_idc_work);
	cancel_delayed_work_sync(&qdev->mpi_port_cfg_work);
पूर्ण

अटल पूर्णांक qlge_adapter_करोwn(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i, status = 0;

	qlge_link_off(qdev);

	qlge_cancel_all_work_sync(qdev);

	क्रम (i = 0; i < qdev->rss_ring_count; i++)
		napi_disable(&qdev->rx_ring[i].napi);

	clear_bit(QL_ADAPTER_UP, &qdev->flags);

	qlge_disable_पूर्णांकerrupts(qdev);

	qlge_tx_ring_clean(qdev);

	/* Call netअगर_napi_del() from common poपूर्णांक. */
	क्रम (i = 0; i < qdev->rss_ring_count; i++)
		netअगर_napi_del(&qdev->rx_ring[i].napi);

	status = qlge_adapter_reset(qdev);
	अगर (status)
		netअगर_err(qdev, अगरकरोwn, qdev->ndev, "reset(func #%d) FAILED!\n",
			  qdev->func);
	qlge_मुक्त_rx_buffers(qdev);

	वापस status;
पूर्ण

अटल पूर्णांक qlge_adapter_up(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक err = 0;

	err = qlge_adapter_initialize(qdev);
	अगर (err) अणु
		netअगर_info(qdev, अगरup, qdev->ndev, "Unable to initialize adapter.\n");
		जाओ err_init;
	पूर्ण
	set_bit(QL_ADAPTER_UP, &qdev->flags);
	qlge_alloc_rx_buffers(qdev);
	/* If the port is initialized and the
	 * link is up the turn on the carrier.
	 */
	अगर ((qlge_पढ़ो32(qdev, STS) & qdev->port_init) &&
	    (qlge_पढ़ो32(qdev, STS) & qdev->port_link_up))
		qlge_link_on(qdev);
	/* Restore rx mode. */
	clear_bit(QL_ALLMULTI, &qdev->flags);
	clear_bit(QL_PROMISCUOUS, &qdev->flags);
	qlge_set_multicast_list(qdev->ndev);

	/* Restore vlan setting. */
	qlge_restore_vlan(qdev);

	qlge_enable_पूर्णांकerrupts(qdev);
	qlge_enable_all_completion_पूर्णांकerrupts(qdev);
	netअगर_tx_start_all_queues(qdev->ndev);

	वापस 0;
err_init:
	qlge_adapter_reset(qdev);
	वापस err;
पूर्ण

अटल व्योम qlge_release_adapter_resources(काष्ठा qlge_adapter *qdev)
अणु
	qlge_मुक्त_mem_resources(qdev);
	qlge_मुक्त_irq(qdev);
पूर्ण

अटल पूर्णांक qlge_get_adapter_resources(काष्ठा qlge_adapter *qdev)
अणु
	अगर (qlge_alloc_mem_resources(qdev)) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "Unable to  allocate memory.\n");
		वापस -ENOMEM;
	पूर्ण
	वापस qlge_request_irq(qdev);
पूर्ण

अटल पूर्णांक qlge_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	पूर्णांक i;

	/* If we hit pci_channel_io_perm_failure
	 * failure condition, then we alपढ़ोy
	 * brought the adapter करोwn.
	 */
	अगर (test_bit(QL_EEH_FATAL, &qdev->flags)) अणु
		netअगर_err(qdev, drv, qdev->ndev, "EEH fatal did unload.\n");
		clear_bit(QL_EEH_FATAL, &qdev->flags);
		वापस 0;
	पूर्ण

	/*
	 * Wait क्रम device to recover from a reset.
	 * (Rarely happens, but possible.)
	 */
	जबतक (!test_bit(QL_ADAPTER_UP, &qdev->flags))
		msleep(1);

	/* Make sure refill_work करोesn't re-enable napi */
	क्रम (i = 0; i < qdev->rss_ring_count; i++)
		cancel_delayed_work_sync(&qdev->rx_ring[i].refill_work);

	qlge_adapter_करोwn(qdev);
	qlge_release_adapter_resources(qdev);
	वापस 0;
पूर्ण

अटल व्योम qlge_set_lb_size(काष्ठा qlge_adapter *qdev)
अणु
	अगर (qdev->ndev->mtu <= 1500)
		qdev->lbq_buf_size = LARGE_BUFFER_MIN_SIZE;
	अन्यथा
		qdev->lbq_buf_size = LARGE_BUFFER_MAX_SIZE;
	qdev->lbq_buf_order = get_order(qdev->lbq_buf_size);
पूर्ण

अटल पूर्णांक qlge_configure_rings(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;
	काष्ठा rx_ring *rx_ring;
	काष्ठा tx_ring *tx_ring;
	पूर्णांक cpu_cnt = min_t(पूर्णांक, MAX_CPUS, num_online_cpus());

	/* In a perfect world we have one RSS ring क्रम each CPU
	 * and each has it's own vector.  To करो that we ask क्रम
	 * cpu_cnt vectors.  qlge_enable_msix() will adjust the
	 * vector count to what we actually get.  We then
	 * allocate an RSS ring क्रम each.
	 * Essentially, we are करोing min(cpu_count, msix_vector_count).
	 */
	qdev->पूर्णांकr_count = cpu_cnt;
	qlge_enable_msix(qdev);
	/* Adjust the RSS ring count to the actual vector count. */
	qdev->rss_ring_count = qdev->पूर्णांकr_count;
	qdev->tx_ring_count = cpu_cnt;
	qdev->rx_ring_count = qdev->tx_ring_count + qdev->rss_ring_count;

	क्रम (i = 0; i < qdev->tx_ring_count; i++) अणु
		tx_ring = &qdev->tx_ring[i];
		स_रखो((व्योम *)tx_ring, 0, माप(*tx_ring));
		tx_ring->qdev = qdev;
		tx_ring->wq_id = i;
		tx_ring->wq_len = qdev->tx_ring_size;
		tx_ring->wq_size =
			tx_ring->wq_len * माप(काष्ठा qlge_ob_mac_iocb_req);

		/*
		 * The completion queue ID क्रम the tx rings start
		 * immediately after the rss rings.
		 */
		tx_ring->cq_id = qdev->rss_ring_count + i;
	पूर्ण

	क्रम (i = 0; i < qdev->rx_ring_count; i++) अणु
		rx_ring = &qdev->rx_ring[i];
		स_रखो((व्योम *)rx_ring, 0, माप(*rx_ring));
		rx_ring->qdev = qdev;
		rx_ring->cq_id = i;
		rx_ring->cpu = i % cpu_cnt;	/* CPU to run handler on. */
		अगर (i < qdev->rss_ring_count) अणु
			/*
			 * Inbound (RSS) queues.
			 */
			rx_ring->cq_len = qdev->rx_ring_size;
			rx_ring->cq_size =
				rx_ring->cq_len * माप(काष्ठा qlge_net_rsp_iocb);
			rx_ring->lbq.type = QLGE_LB;
			rx_ring->sbq.type = QLGE_SB;
			INIT_DELAYED_WORK(&rx_ring->refill_work,
					  &qlge_slow_refill);
		पूर्ण अन्यथा अणु
			/*
			 * Outbound queue handles outbound completions only.
			 */
			/* outbound cq is same size as tx_ring it services. */
			rx_ring->cq_len = qdev->tx_ring_size;
			rx_ring->cq_size =
				rx_ring->cq_len * माप(काष्ठा qlge_net_rsp_iocb);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qlge_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	पूर्णांक err = 0;

	err = qlge_adapter_reset(qdev);
	अगर (err)
		वापस err;

	qlge_set_lb_size(qdev);
	err = qlge_configure_rings(qdev);
	अगर (err)
		वापस err;

	err = qlge_get_adapter_resources(qdev);
	अगर (err)
		जाओ error_up;

	err = qlge_adapter_up(qdev);
	अगर (err)
		जाओ error_up;

	वापस err;

error_up:
	qlge_release_adapter_resources(qdev);
	वापस err;
पूर्ण

अटल पूर्णांक qlge_change_rx_buffers(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status;

	/* Wait क्रम an outstanding reset to complete. */
	अगर (!test_bit(QL_ADAPTER_UP, &qdev->flags)) अणु
		पूर्णांक i = 4;

		जबतक (--i && !test_bit(QL_ADAPTER_UP, &qdev->flags)) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Waiting for adapter UP...\n");
			ssleep(1);
		पूर्ण

		अगर (!i) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Timed out waiting for adapter UP\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	status = qlge_adapter_करोwn(qdev);
	अगर (status)
		जाओ error;

	qlge_set_lb_size(qdev);

	status = qlge_adapter_up(qdev);
	अगर (status)
		जाओ error;

	वापस status;
error:
	netअगर_alert(qdev, अगरup, qdev->ndev,
		    "Driver up/down cycle failed, closing device.\n");
	set_bit(QL_ADAPTER_UP, &qdev->flags);
	dev_बंद(qdev->ndev);
	वापस status;
पूर्ण

अटल पूर्णांक qlge_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	पूर्णांक status;

	अगर (ndev->mtu == 1500 && new_mtu == 9000)
		netअगर_err(qdev, अगरup, qdev->ndev, "Changing to jumbo MTU.\n");
	अन्यथा अगर (ndev->mtu == 9000 && new_mtu == 1500)
		netअगर_err(qdev, अगरup, qdev->ndev, "Changing to normal MTU.\n");
	अन्यथा
		वापस -EINVAL;

	queue_delayed_work(qdev->workqueue,
			   &qdev->mpi_port_cfg_work, 3 * HZ);

	ndev->mtu = new_mtu;

	अगर (!netअगर_running(qdev->ndev))
		वापस 0;

	status = qlge_change_rx_buffers(qdev);
	अगर (status) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Changing MTU failed.\n");
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा net_device_stats *qlge_get_stats(काष्ठा net_device
					       *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	काष्ठा rx_ring *rx_ring = &qdev->rx_ring[0];
	काष्ठा tx_ring *tx_ring = &qdev->tx_ring[0];
	अचिन्हित दीर्घ pkts, mcast, dropped, errors, bytes;
	पूर्णांक i;

	/* Get RX stats. */
	pkts = mcast = dropped = errors = bytes = 0;
	क्रम (i = 0; i < qdev->rss_ring_count; i++, rx_ring++) अणु
		pkts += rx_ring->rx_packets;
		bytes += rx_ring->rx_bytes;
		dropped += rx_ring->rx_dropped;
		errors += rx_ring->rx_errors;
		mcast += rx_ring->rx_multicast;
	पूर्ण
	ndev->stats.rx_packets = pkts;
	ndev->stats.rx_bytes = bytes;
	ndev->stats.rx_dropped = dropped;
	ndev->stats.rx_errors = errors;
	ndev->stats.multicast = mcast;

	/* Get TX stats. */
	pkts = errors = bytes = 0;
	क्रम (i = 0; i < qdev->tx_ring_count; i++, tx_ring++) अणु
		pkts += tx_ring->tx_packets;
		bytes += tx_ring->tx_bytes;
		errors += tx_ring->tx_errors;
	पूर्ण
	ndev->stats.tx_packets = pkts;
	ndev->stats.tx_bytes = bytes;
	ndev->stats.tx_errors = errors;
	वापस &ndev->stats;
पूर्ण

अटल व्योम qlge_set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i, status;

	status = qlge_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	अगर (status)
		वापस;
	/*
	 * Set or clear promiscuous mode अगर a
	 * transition is taking place.
	 */
	अगर (ndev->flags & IFF_PROMISC) अणु
		अगर (!test_bit(QL_PROMISCUOUS, &qdev->flags)) अणु
			अगर (qlge_set_routing_reg
			    (qdev, RT_IDX_PROMISCUOUS_SLOT, RT_IDX_VALID, 1)) अणु
				netअगर_err(qdev, hw, qdev->ndev,
					  "Failed to set promiscuous mode.\n");
			पूर्ण अन्यथा अणु
				set_bit(QL_PROMISCUOUS, &qdev->flags);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_bit(QL_PROMISCUOUS, &qdev->flags)) अणु
			अगर (qlge_set_routing_reg
			    (qdev, RT_IDX_PROMISCUOUS_SLOT, RT_IDX_VALID, 0)) अणु
				netअगर_err(qdev, hw, qdev->ndev,
					  "Failed to clear promiscuous mode.\n");
			पूर्ण अन्यथा अणु
				clear_bit(QL_PROMISCUOUS, &qdev->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Set or clear all multicast mode अगर a
	 * transition is taking place.
	 */
	अगर ((ndev->flags & IFF_ALLMULTI) ||
	    (netdev_mc_count(ndev) > MAX_MULTICAST_ENTRIES)) अणु
		अगर (!test_bit(QL_ALLMULTI, &qdev->flags)) अणु
			अगर (qlge_set_routing_reg
			    (qdev, RT_IDX_ALLMULTI_SLOT, RT_IDX_MCAST, 1)) अणु
				netअगर_err(qdev, hw, qdev->ndev,
					  "Failed to set all-multi mode.\n");
			पूर्ण अन्यथा अणु
				set_bit(QL_ALLMULTI, &qdev->flags);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_bit(QL_ALLMULTI, &qdev->flags)) अणु
			अगर (qlge_set_routing_reg
			    (qdev, RT_IDX_ALLMULTI_SLOT, RT_IDX_MCAST, 0)) अणु
				netअगर_err(qdev, hw, qdev->ndev,
					  "Failed to clear all-multi mode.\n");
			पूर्ण अन्यथा अणु
				clear_bit(QL_ALLMULTI, &qdev->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!netdev_mc_empty(ndev)) अणु
		status = qlge_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
		अगर (status)
			जाओ निकास;
		i = 0;
		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			अगर (qlge_set_mac_addr_reg(qdev, (u8 *)ha->addr,
						  MAC_ADDR_TYPE_MULTI_MAC, i)) अणु
				netअगर_err(qdev, hw, qdev->ndev,
					  "Failed to loadmulticast address.\n");
				qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
				जाओ निकास;
			पूर्ण
			i++;
		पूर्ण
		qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
		अगर (qlge_set_routing_reg
		    (qdev, RT_IDX_MCAST_MATCH_SLOT, RT_IDX_MCAST_MATCH, 1)) अणु
			netअगर_err(qdev, hw, qdev->ndev,
				  "Failed to set multicast match mode.\n");
		पूर्ण अन्यथा अणु
			set_bit(QL_ALLMULTI, &qdev->flags);
		पूर्ण
	पूर्ण
निकास:
	qlge_sem_unlock(qdev, SEM_RT_IDX_MASK);
पूर्ण

अटल पूर्णांक qlge_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक status;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(ndev->dev_addr, addr->sa_data, ndev->addr_len);
	/* Update local copy of current mac address. */
	स_नकल(qdev->current_mac_addr, ndev->dev_addr, ndev->addr_len);

	status = qlge_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	अगर (status)
		वापस status;
	status = qlge_set_mac_addr_reg(qdev, (u8 *)ndev->dev_addr,
				       MAC_ADDR_TYPE_CAM_MAC,
				       qdev->func * MAX_CQ);
	अगर (status)
		netअगर_err(qdev, hw, qdev->ndev, "Failed to load MAC address.\n");
	qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
	वापस status;
पूर्ण

अटल व्योम qlge_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	qlge_queue_asic_error(qdev);
पूर्ण

अटल व्योम qlge_asic_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlge_adapter *qdev =
		container_of(work, काष्ठा qlge_adapter, asic_reset_work.work);
	पूर्णांक status;

	rtnl_lock();
	status = qlge_adapter_करोwn(qdev);
	अगर (status)
		जाओ error;

	status = qlge_adapter_up(qdev);
	अगर (status)
		जाओ error;

	/* Restore rx mode. */
	clear_bit(QL_ALLMULTI, &qdev->flags);
	clear_bit(QL_PROMISCUOUS, &qdev->flags);
	qlge_set_multicast_list(qdev->ndev);

	rtnl_unlock();
	वापस;
error:
	netअगर_alert(qdev, अगरup, qdev->ndev,
		    "Driver up/down cycle failed, closing device\n");

	set_bit(QL_ADAPTER_UP, &qdev->flags);
	dev_बंद(qdev->ndev);
	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा nic_operations qla8012_nic_ops = अणु
	.get_flash		= qlge_get_8012_flash_params,
	.port_initialize	= qlge_8012_port_initialize,
पूर्ण;

अटल स्थिर काष्ठा nic_operations qla8000_nic_ops = अणु
	.get_flash		= qlge_get_8000_flash_params,
	.port_initialize	= qlge_8000_port_initialize,
पूर्ण;

/* Find the pcie function number क्रम the other NIC
 * on this chip.  Since both NIC functions share a
 * common firmware we have the lowest enabled function
 * करो any common work.  Examples would be resetting
 * after a fatal firmware error, or करोing a firmware
 * coredump.
 */
अटल पूर्णांक qlge_get_alt_pcie_func(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status = 0;
	u32 temp;
	u32 nic_func1, nic_func2;

	status = qlge_पढ़ो_mpi_reg(qdev, MPI_TEST_FUNC_PORT_CFG,
				   &temp);
	अगर (status)
		वापस status;

	nic_func1 = ((temp >> MPI_TEST_NIC1_FUNC_SHIFT) &
		     MPI_TEST_NIC_FUNC_MASK);
	nic_func2 = ((temp >> MPI_TEST_NIC2_FUNC_SHIFT) &
		     MPI_TEST_NIC_FUNC_MASK);

	अगर (qdev->func == nic_func1)
		qdev->alt_func = nic_func2;
	अन्यथा अगर (qdev->func == nic_func2)
		qdev->alt_func = nic_func1;
	अन्यथा
		status = -EIO;

	वापस status;
पूर्ण

अटल पूर्णांक qlge_get_board_info(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status;

	qdev->func =
		(qlge_पढ़ो32(qdev, STS) & STS_FUNC_ID_MASK) >> STS_FUNC_ID_SHIFT;
	अगर (qdev->func > 3)
		वापस -EIO;

	status = qlge_get_alt_pcie_func(qdev);
	अगर (status)
		वापस status;

	qdev->port = (qdev->func < qdev->alt_func) ? 0 : 1;
	अगर (qdev->port) अणु
		qdev->xg_sem_mask = SEM_XGMAC1_MASK;
		qdev->port_link_up = STS_PL1;
		qdev->port_init = STS_PI1;
		qdev->mailbox_in = PROC_ADDR_MPI_RISC | PROC_ADDR_FUNC2_MBI;
		qdev->mailbox_out = PROC_ADDR_MPI_RISC | PROC_ADDR_FUNC2_MBO;
	पूर्ण अन्यथा अणु
		qdev->xg_sem_mask = SEM_XGMAC0_MASK;
		qdev->port_link_up = STS_PL0;
		qdev->port_init = STS_PI0;
		qdev->mailbox_in = PROC_ADDR_MPI_RISC | PROC_ADDR_FUNC0_MBI;
		qdev->mailbox_out = PROC_ADDR_MPI_RISC | PROC_ADDR_FUNC0_MBO;
	पूर्ण
	qdev->chip_rev_id = qlge_पढ़ो32(qdev, REV_ID);
	qdev->device_id = qdev->pdev->device;
	अगर (qdev->device_id == QLGE_DEVICE_ID_8012)
		qdev->nic_ops = &qla8012_nic_ops;
	अन्यथा अगर (qdev->device_id == QLGE_DEVICE_ID_8000)
		qdev->nic_ops = &qla8000_nic_ops;
	वापस status;
पूर्ण

अटल व्योम qlge_release_all(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlge_adapter *qdev = pci_get_drvdata(pdev);

	अगर (qdev->workqueue) अणु
		destroy_workqueue(qdev->workqueue);
		qdev->workqueue = शून्य;
	पूर्ण

	अगर (qdev->reg_base)
		iounmap(qdev->reg_base);
	अगर (qdev->करोorbell_area)
		iounmap(qdev->करोorbell_area);
	vमुक्त(qdev->mpi_coredump);
	pci_release_regions(pdev);
पूर्ण

अटल पूर्णांक qlge_init_device(काष्ठा pci_dev *pdev, काष्ठा qlge_adapter *qdev,
			    पूर्णांक cards_found)
अणु
	काष्ठा net_device *ndev = qdev->ndev;
	पूर्णांक err = 0;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "PCI device enable failed.\n");
		वापस err;
	पूर्ण

	qdev->pdev = pdev;
	pci_set_drvdata(pdev, qdev);

	/* Set PCIe पढ़ो request size */
	err = pcie_set_पढ़ोrq(pdev, 4096);
	अगर (err) अणु
		dev_err(&pdev->dev, "Set readrq failed.\n");
		जाओ err_disable_pci;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "PCI region request failed.\n");
		जाओ err_disable_pci;
	पूर्ण

	pci_set_master(pdev);
	अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		set_bit(QL_DMA64, &qdev->flags);
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
	पूर्ण अन्यथा अणु
		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (!err)
			err = dma_set_coherent_mask(&pdev->dev,
						    DMA_BIT_MASK(32));
	पूर्ण

	अगर (err) अणु
		dev_err(&pdev->dev, "No usable DMA configuration.\n");
		जाओ err_release_pci;
	पूर्ण

	/* Set PCIe reset type क्रम EEH to fundamental. */
	pdev->needs_freset = 1;
	pci_save_state(pdev);
	qdev->reg_base =
		ioremap(pci_resource_start(pdev, 1), pci_resource_len(pdev, 1));
	अगर (!qdev->reg_base) अणु
		dev_err(&pdev->dev, "Register mapping failed.\n");
		err = -ENOMEM;
		जाओ err_release_pci;
	पूर्ण

	qdev->करोorbell_area_size = pci_resource_len(pdev, 3);
	qdev->करोorbell_area =
		ioremap(pci_resource_start(pdev, 3), pci_resource_len(pdev, 3));
	अगर (!qdev->करोorbell_area) अणु
		dev_err(&pdev->dev, "Doorbell register mapping failed.\n");
		err = -ENOMEM;
		जाओ err_iounmap_base;
	पूर्ण

	err = qlge_get_board_info(qdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Register access failed.\n");
		err = -EIO;
		जाओ err_iounmap_करोorbell;
	पूर्ण
	qdev->msg_enable = netअगर_msg_init(debug, शेष_msg);
	spin_lock_init(&qdev->stats_lock);

	अगर (qlge_mpi_coredump) अणु
		qdev->mpi_coredump =
			vदो_स्मृति(माप(काष्ठा qlge_mpi_coredump));
		अगर (!qdev->mpi_coredump) अणु
			err = -ENOMEM;
			जाओ err_iounmap_करोorbell;
		पूर्ण
		अगर (qlge_क्रमce_coredump)
			set_bit(QL_FRC_COREDUMP, &qdev->flags);
	पूर्ण
	/* make sure the EEPROM is good */
	err = qdev->nic_ops->get_flash(qdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Invalid FLASH.\n");
		जाओ err_मुक्त_mpi_coredump;
	पूर्ण

	/* Keep local copy of current mac address. */
	स_नकल(qdev->current_mac_addr, ndev->dev_addr, ndev->addr_len);

	/* Set up the शेष ring sizes. */
	qdev->tx_ring_size = NUM_TX_RING_ENTRIES;
	qdev->rx_ring_size = NUM_RX_RING_ENTRIES;

	/* Set up the coalescing parameters. */
	qdev->rx_coalesce_usecs = DFLT_COALESCE_WAIT;
	qdev->tx_coalesce_usecs = DFLT_COALESCE_WAIT;
	qdev->rx_max_coalesced_frames = DFLT_INTER_FRAME_WAIT;
	qdev->tx_max_coalesced_frames = DFLT_INTER_FRAME_WAIT;

	/*
	 * Set up the operating parameters.
	 */
	qdev->workqueue = alloc_ordered_workqueue("%s", WQ_MEM_RECLAIM,
						  ndev->name);
	अगर (!qdev->workqueue) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_mpi_coredump;
	पूर्ण

	INIT_DELAYED_WORK(&qdev->asic_reset_work, qlge_asic_reset_work);
	INIT_DELAYED_WORK(&qdev->mpi_reset_work, qlge_mpi_reset_work);
	INIT_DELAYED_WORK(&qdev->mpi_work, qlge_mpi_work);
	INIT_DELAYED_WORK(&qdev->mpi_port_cfg_work, qlge_mpi_port_cfg_work);
	INIT_DELAYED_WORK(&qdev->mpi_idc_work, qlge_mpi_idc_work);
	init_completion(&qdev->ide_completion);
	mutex_init(&qdev->mpi_mutex);

	अगर (!cards_found) अणु
		dev_info(&pdev->dev, "%s\n", DRV_STRING);
		dev_info(&pdev->dev, "Driver name: %s, Version: %s.\n",
			 DRV_NAME, DRV_VERSION);
	पूर्ण
	वापस 0;

err_मुक्त_mpi_coredump:
	vमुक्त(qdev->mpi_coredump);
err_iounmap_करोorbell:
	iounmap(qdev->करोorbell_area);
err_iounmap_base:
	iounmap(qdev->reg_base);
err_release_pci:
	pci_release_regions(pdev);
err_disable_pci:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops qlge_netdev_ops = अणु
	.nकरो_खोलो		= qlge_खोलो,
	.nकरो_stop		= qlge_बंद,
	.nकरो_start_xmit		= qlge_send,
	.nकरो_change_mtu		= qlge_change_mtu,
	.nकरो_get_stats		= qlge_get_stats,
	.nकरो_set_rx_mode	= qlge_set_multicast_list,
	.nकरो_set_mac_address	= qlge_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= qlge_tx_समयout,
	.nकरो_set_features	= qlge_set_features,
	.nकरो_vlan_rx_add_vid	= qlge_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= qlge_vlan_rx_समाप्त_vid,
पूर्ण;

अटल व्योम qlge_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा qlge_adapter *qdev = from_समयr(qdev, t, समयr);
	u32 var = 0;

	var = qlge_पढ़ो32(qdev, STS);
	अगर (pci_channel_offline(qdev->pdev)) अणु
		netअगर_err(qdev, अगरup, qdev->ndev, "EEH STS = 0x%.08x.\n", var);
		वापस;
	पूर्ण

	mod_समयr(&qdev->समयr, jअगरfies + (5 * HZ));
पूर्ण

अटल स्थिर काष्ठा devlink_ops qlge_devlink_ops;

अटल पूर्णांक qlge_probe(काष्ठा pci_dev *pdev,
		      स्थिर काष्ठा pci_device_id *pci_entry)
अणु
	काष्ठा qlge_netdev_priv *ndev_priv;
	काष्ठा qlge_adapter *qdev = शून्य;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा devlink *devlink;
	अटल पूर्णांक cards_found;
	पूर्णांक err;

	devlink = devlink_alloc(&qlge_devlink_ops, माप(काष्ठा qlge_adapter));
	अगर (!devlink)
		वापस -ENOMEM;

	qdev = devlink_priv(devlink);

	ndev = alloc_etherdev_mq(माप(काष्ठा qlge_netdev_priv),
				 min(MAX_CPUS,
				     netअगर_get_num_शेष_rss_queues()));
	अगर (!ndev) अणु
		err = -ENOMEM;
		जाओ devlink_मुक्त;
	पूर्ण

	ndev_priv = netdev_priv(ndev);
	ndev_priv->qdev = qdev;
	ndev_priv->ndev = ndev;
	qdev->ndev = ndev;
	err = qlge_init_device(pdev, qdev, cards_found);
	अगर (err < 0)
		जाओ netdev_मुक्त;

	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->hw_features = NETIF_F_SG |
		NETIF_F_IP_CSUM |
		NETIF_F_TSO |
		NETIF_F_TSO_ECN |
		NETIF_F_HW_VLAN_CTAG_TX |
		NETIF_F_HW_VLAN_CTAG_RX |
		NETIF_F_HW_VLAN_CTAG_FILTER |
		NETIF_F_RXCSUM;
	ndev->features = ndev->hw_features;
	ndev->vlan_features = ndev->hw_features;
	/* vlan माला_लो same features (except vlan filter) */
	ndev->vlan_features &= ~(NETIF_F_HW_VLAN_CTAG_FILTER |
				 NETIF_F_HW_VLAN_CTAG_TX |
				 NETIF_F_HW_VLAN_CTAG_RX);

	अगर (test_bit(QL_DMA64, &qdev->flags))
		ndev->features |= NETIF_F_HIGHDMA;

	/*
	 * Set up net_device काष्ठाure.
	 */
	ndev->tx_queue_len = qdev->tx_ring_size;
	ndev->irq = pdev->irq;

	ndev->netdev_ops = &qlge_netdev_ops;
	ndev->ethtool_ops = &qlge_ethtool_ops;
	ndev->watchकरोg_समयo = 10 * HZ;

	/* MTU range: this driver only supports 1500 or 9000, so this only
	 * filters out values above or below, and we'll rely on
	 * qlge_change_mtu to make sure only 1500 or 9000 are allowed
	 */
	ndev->min_mtu = ETH_DATA_LEN;
	ndev->max_mtu = 9000;

	err = रेजिस्टर_netdev(ndev);
	अगर (err) अणु
		dev_err(&pdev->dev, "net device registration failed.\n");
		qlge_release_all(pdev);
		pci_disable_device(pdev);
		जाओ netdev_मुक्त;
	पूर्ण

	err = devlink_रेजिस्टर(devlink, &pdev->dev);
	अगर (err)
		जाओ netdev_मुक्त;

	err = qlge_health_create_reporters(qdev);

	अगर (err)
		जाओ devlink_unरेजिस्टर;

	/* Start up the समयr to trigger EEH अगर
	 * the bus goes dead
	 */
	समयr_setup(&qdev->समयr, qlge_समयr, TIMER_DEFERRABLE);
	mod_समयr(&qdev->समयr, jअगरfies + (5 * HZ));
	qlge_link_off(qdev);
	qlge_display_dev_info(ndev);
	atomic_set(&qdev->lb_count, 0);
	cards_found++;
	वापस 0;

devlink_unरेजिस्टर:
	devlink_unरेजिस्टर(devlink);
netdev_मुक्त:
	मुक्त_netdev(ndev);
devlink_मुक्त:
	devlink_मुक्त(devlink);

	वापस err;
पूर्ण

netdev_tx_t qlge_lb_send(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	वापस qlge_send(skb, ndev);
पूर्ण

पूर्णांक qlge_clean_lb_rx_ring(काष्ठा rx_ring *rx_ring, पूर्णांक budget)
अणु
	वापस qlge_clean_inbound_rx_ring(rx_ring, budget);
पूर्ण

अटल व्योम qlge_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlge_adapter *qdev = pci_get_drvdata(pdev);
	काष्ठा net_device *ndev = qdev->ndev;
	काष्ठा devlink *devlink = priv_to_devlink(qdev);

	del_समयr_sync(&qdev->समयr);
	qlge_cancel_all_work_sync(qdev);
	unरेजिस्टर_netdev(ndev);
	qlge_release_all(pdev);
	pci_disable_device(pdev);
	devlink_health_reporter_destroy(qdev->reporter);
	devlink_unरेजिस्टर(devlink);
	devlink_मुक्त(devlink);
	मुक्त_netdev(ndev);
पूर्ण

/* Clean up resources without touching hardware. */
अटल व्योम qlge_eeh_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	पूर्णांक i;

	अगर (netअगर_carrier_ok(ndev)) अणु
		netअगर_carrier_off(ndev);
		netअगर_stop_queue(ndev);
	पूर्ण

	/* Disabling the समयr */
	qlge_cancel_all_work_sync(qdev);

	क्रम (i = 0; i < qdev->rss_ring_count; i++)
		netअगर_napi_del(&qdev->rx_ring[i].napi);

	clear_bit(QL_ADAPTER_UP, &qdev->flags);
	qlge_tx_ring_clean(qdev);
	qlge_मुक्त_rx_buffers(qdev);
	qlge_release_adapter_resources(qdev);
पूर्ण

/*
 * This callback is called by the PCI subप्रणाली whenever
 * a PCI bus error is detected.
 */
अटल pci_ers_result_t qlge_io_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा qlge_adapter *qdev = pci_get_drvdata(pdev);
	काष्ठा net_device *ndev = qdev->ndev;

	चयन (state) अणु
	हाल pci_channel_io_normal:
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	हाल pci_channel_io_frozen:
		netअगर_device_detach(ndev);
		del_समयr_sync(&qdev->समयr);
		अगर (netअगर_running(ndev))
			qlge_eeh_बंद(ndev);
		pci_disable_device(pdev);
		वापस PCI_ERS_RESULT_NEED_RESET;
	हाल pci_channel_io_perm_failure:
		dev_err(&pdev->dev,
			"%s: pci_channel_io_perm_failure.\n", __func__);
		del_समयr_sync(&qdev->समयr);
		qlge_eeh_बंद(ndev);
		set_bit(QL_EEH_FATAL, &qdev->flags);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/*
 * This callback is called after the PCI buss has been reset.
 * Basically, this tries to restart the card from scratch.
 * This is a लघुened version of the device probe/discovery code,
 * it resembles the first-half of the () routine.
 */
अटल pci_ers_result_t qlge_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlge_adapter *qdev = pci_get_drvdata(pdev);

	pdev->error_state = pci_channel_io_normal;

	pci_restore_state(pdev);
	अगर (pci_enable_device(pdev)) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Cannot re-enable PCI device after reset.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	pci_set_master(pdev);

	अगर (qlge_adapter_reset(qdev)) अणु
		netअगर_err(qdev, drv, qdev->ndev, "reset FAILED!\n");
		set_bit(QL_EEH_FATAL, &qdev->flags);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम qlge_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlge_adapter *qdev = pci_get_drvdata(pdev);
	काष्ठा net_device *ndev = qdev->ndev;
	पूर्णांक err = 0;

	अगर (netअगर_running(ndev)) अणु
		err = qlge_खोलो(ndev);
		अगर (err) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Device initialization failed after reset.\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Device was not running prior to EEH.\n");
	पूर्ण
	mod_समयr(&qdev->समयr, jअगरfies + (5 * HZ));
	netअगर_device_attach(ndev);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers qlge_err_handler = अणु
	.error_detected = qlge_io_error_detected,
	.slot_reset = qlge_io_slot_reset,
	.resume = qlge_io_resume,
पूर्ण;

अटल पूर्णांक __maybe_unused qlge_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा qlge_adapter *qdev;
	काष्ठा net_device *ndev;
	पूर्णांक err;

	qdev = pci_get_drvdata(pdev);
	ndev = qdev->ndev;
	netअगर_device_detach(ndev);
	del_समयr_sync(&qdev->समयr);

	अगर (netअगर_running(ndev)) अणु
		err = qlge_adapter_करोwn(qdev);
		अगर (!err)
			वापस err;
	पूर्ण

	qlge_wol(qdev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qlge_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा qlge_adapter *qdev;
	काष्ठा net_device *ndev;
	पूर्णांक err;

	qdev = pci_get_drvdata(pdev);
	ndev = qdev->ndev;

	pci_set_master(pdev);

	device_wakeup_disable(dev_d);

	अगर (netअगर_running(ndev)) अणु
		err = qlge_adapter_up(qdev);
		अगर (err)
			वापस err;
	पूर्ण

	mod_समयr(&qdev->समयr, jअगरfies + (5 * HZ));
	netअगर_device_attach(ndev);

	वापस 0;
पूर्ण

अटल व्योम qlge_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	qlge_suspend(&pdev->dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(qlge_pm_ops, qlge_suspend, qlge_resume);

अटल काष्ठा pci_driver qlge_driver = अणु
	.name = DRV_NAME,
	.id_table = qlge_pci_tbl,
	.probe = qlge_probe,
	.हटाओ = qlge_हटाओ,
	.driver.pm = &qlge_pm_ops,
	.shutकरोwn = qlge_shutकरोwn,
	.err_handler = &qlge_err_handler
पूर्ण;

module_pci_driver(qlge_driver);
