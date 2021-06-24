<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Endpoपूर्णांक Function Driver to implement Non-Transparent Bridge functionality
 *
 * Copyright (C) 2020 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

/*
 * The PCI NTB function driver configures the SoC with multiple PCIe Endpoपूर्णांक
 * (EP) controller instances (see diagram below) in such a way that
 * transactions from one EP controller are routed to the other EP controller.
 * Once PCI NTB function driver configures the SoC with multiple EP instances,
 * HOST1 and HOST2 can communicate with each other using SoC as a bridge.
 *
 *    +-------------+                                   +-------------+
 *    |             |                                   |             |
 *    |    HOST1    |                                   |    HOST2    |
 *    |             |                                   |             |
 *    +------^------+                                   +------^------+
 *           |                                                 |
 *           |                                                 |
 * +---------|-------------------------------------------------|---------+
 * |  +------v------+                                   +------v------+  |
 * |  |             |                                   |             |  |
 * |  |     EP      |                                   |     EP      |  |
 * |  | CONTROLLER1 |                                   | CONTROLLER2 |  |
 * |  |             <----------------------------------->             |  |
 * |  |             |                                   |             |  |
 * |  |             |                                   |             |  |
 * |  |             |  SoC With Multiple EP Instances   |             |  |
 * |  |             |  (Configured using NTB Function)  |             |  |
 * |  +-------------+                                   +-------------+  |
 * +---------------------------------------------------------------------+
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/pci-epc.h>
#समावेश <linux/pci-epf.h>

अटल काष्ठा workqueue_काष्ठा *kpcपूर्णांकb_workqueue;

#घोषणा COMMAND_CONFIGURE_DOORBELL	1
#घोषणा COMMAND_TEARDOWN_DOORBELL	2
#घोषणा COMMAND_CONFIGURE_MW		3
#घोषणा COMMAND_TEARDOWN_MW		4
#घोषणा COMMAND_LINK_UP			5
#घोषणा COMMAND_LINK_DOWN		6

#घोषणा COMMAND_STATUS_OK		1
#घोषणा COMMAND_STATUS_ERROR		2

#घोषणा LINK_STATUS_UP			BIT(0)

#घोषणा SPAD_COUNT			64
#घोषणा DB_COUNT			4
#घोषणा NTB_MW_OFFSET			2
#घोषणा DB_COUNT_MASK			GENMASK(15, 0)
#घोषणा MSIX_ENABLE			BIT(16)
#घोषणा MAX_DB_COUNT			32
#घोषणा MAX_MW				4

क्रमागत epf_ntb_bar अणु
	BAR_CONFIG,
	BAR_PEER_SPAD,
	BAR_DB_MW1,
	BAR_MW2,
	BAR_MW3,
	BAR_MW4,
पूर्ण;

काष्ठा epf_ntb अणु
	u32 num_mws;
	u32 db_count;
	u32 spad_count;
	काष्ठा pci_epf *epf;
	u64 mws_size[MAX_MW];
	काष्ठा config_group group;
	काष्ठा epf_ntb_epc *epc[2];
पूर्ण;

#घोषणा to_epf_ntb(epf_group) container_of((epf_group), काष्ठा epf_ntb, group)

काष्ठा epf_ntb_epc अणु
	u8 func_no;
	bool linkup;
	bool is_msix;
	पूर्णांक msix_bar;
	u32 spad_size;
	काष्ठा pci_epc *epc;
	काष्ठा epf_ntb *epf_ntb;
	व्योम __iomem *mw_addr[6];
	माप_प्रकार msix_table_offset;
	काष्ठा epf_ntb_ctrl *reg;
	काष्ठा pci_epf_bar *epf_bar;
	क्रमागत pci_barno epf_ntb_bar[6];
	काष्ठा delayed_work cmd_handler;
	क्रमागत pci_epc_पूर्णांकerface_type type;
	स्थिर काष्ठा pci_epc_features *epc_features;
पूर्ण;

काष्ठा epf_ntb_ctrl अणु
	u32	command;
	u32	argument;
	u16	command_status;
	u16	link_status;
	u32	topology;
	u64	addr;
	u64	size;
	u32	num_mws;
	u32	mw1_offset;
	u32	spad_offset;
	u32	spad_count;
	u32	db_entry_size;
	u32	db_data[MAX_DB_COUNT];
	u32	db_offset[MAX_DB_COUNT];
पूर्ण __packed;

अटल काष्ठा pci_epf_header epf_ntb_header = अणु
	.venकरोrid	= PCI_ANY_ID,
	.deviceid	= PCI_ANY_ID,
	.baseclass_code	= PCI_BASE_CLASS_MEMORY,
	.पूर्णांकerrupt_pin	= PCI_INTERRUPT_INTA,
पूर्ण;

/**
 * epf_ntb_link_up() - Raise link_up पूर्णांकerrupt to both the hosts
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @link_up: true or false indicating Link is UP or Down
 *
 * Once NTB function in HOST1 and the NTB function in HOST2 invoke
 * ntb_link_enable(), this NTB function driver will trigger a link event to
 * the NTB client in both the hosts.
 */
अटल पूर्णांक epf_ntb_link_up(काष्ठा epf_ntb *ntb, bool link_up)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;
	क्रमागत pci_epc_irq_type irq_type;
	काष्ठा epf_ntb_epc *ntb_epc;
	काष्ठा epf_ntb_ctrl *ctrl;
	काष्ठा pci_epc *epc;
	bool is_msix;
	u8 func_no;
	पूर्णांक ret;

	क्रम (type = PRIMARY_INTERFACE; type <= SECONDARY_INTERFACE; type++) अणु
		ntb_epc = ntb->epc[type];
		epc = ntb_epc->epc;
		func_no = ntb_epc->func_no;
		is_msix = ntb_epc->is_msix;
		ctrl = ntb_epc->reg;
		अगर (link_up)
			ctrl->link_status |= LINK_STATUS_UP;
		अन्यथा
			ctrl->link_status &= ~LINK_STATUS_UP;
		irq_type = is_msix ? PCI_EPC_IRQ_MSIX : PCI_EPC_IRQ_MSI;
		ret = pci_epc_उठाओ_irq(epc, func_no, irq_type, 1);
		अगर (ret) अणु
			dev_err(&epc->dev,
				"%s intf: Failed to raise Link Up IRQ\n",
				pci_epc_पूर्णांकerface_string(type));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_configure_mw() - Configure the Outbound Address Space क्रम one host
 *   to access the memory winकरोw of other host
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 * @mw: Index of the memory winकरोw (either 0, 1, 2 or 3)
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAR0      |    |     |   Doorbell 1   +-----------> MSI|X ADDRESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAR1      |    |     |   Doorbell 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAR2      |          |   Doorbell 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDRESS 2 |
 * |       BAR3      |    |     |   Doorbell 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAR4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDRESS 3||
 * |       BAR5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTROLLER 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDRESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTROLLER 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Address Space
 *                                                           (Managed by HOST2)
 *
 * This function perक्रमms stage (B) in the above diagram (see MW1) i.e., map OB
 * address space of memory winकरोw to PCI address space.
 *
 * This operation requires 3 parameters
 *  1) Address in the outbound address space
 *  2) Address in the PCI Address space
 *  3) Size of the address region to be mapped
 *
 * The address in the outbound address space (क्रम MW1, MW2, MW3 and MW4) is
 * stored in epf_bar corresponding to BAR_DB_MW1 क्रम MW1 and BAR_MW2, BAR_MW3
 * BAR_MW4 क्रम rest of the BARs of epf_ntb_epc that is connected to HOST1. This
 * is populated in epf_ntb_alloc_peer_mem() in this driver.
 *
 * The address and size of the PCI address region that has to be mapped would
 * be provided by HOST2 in ctrl->addr and ctrl->size of epf_ntb_epc that is
 * connected to HOST2.
 *
 * Please note Memory winकरोw1 (MW1) and Doorbell रेजिस्टरs together will be
 * mapped to a single BAR (BAR2) above क्रम 32-bit BARs. The exact BAR that's
 * used क्रम Memory winकरोw (MW) can be obtained from epf_ntb_bar[BAR_DB_MW1],
 * epf_ntb_bar[BAR_MW2], epf_ntb_bar[BAR_MW2], epf_ntb_bar[BAR_MW2].
 */
अटल पूर्णांक epf_ntb_configure_mw(काष्ठा epf_ntb *ntb,
				क्रमागत pci_epc_पूर्णांकerface_type type, u32 mw)
अणु
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	काष्ठा pci_epf_bar *peer_epf_bar;
	क्रमागत pci_barno peer_barno;
	काष्ठा epf_ntb_ctrl *ctrl;
	phys_addr_t phys_addr;
	काष्ठा pci_epc *epc;
	u64 addr, size;
	पूर्णांक ret = 0;
	u8 func_no;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peer_ntb_epc = ntb->epc[!type];
	peer_barno = peer_ntb_epc->epf_ntb_bar[mw + NTB_MW_OFFSET];
	peer_epf_bar = &peer_ntb_epc->epf_bar[peer_barno];

	phys_addr = peer_epf_bar->phys_addr;
	ctrl = ntb_epc->reg;
	addr = ctrl->addr;
	size = ctrl->size;
	अगर (mw + NTB_MW_OFFSET == BAR_DB_MW1)
		phys_addr += ctrl->mw1_offset;

	अगर (size > ntb->mws_size[mw]) अणु
		dev_err(&epc->dev,
			"%s intf: MW: %d Req Sz:%llxx > Supported Sz:%llx\n",
			pci_epc_पूर्णांकerface_string(type), mw, size,
			ntb->mws_size[mw]);
		ret = -EINVAL;
		जाओ err_invalid_size;
	पूर्ण

	func_no = ntb_epc->func_no;

	ret = pci_epc_map_addr(epc, func_no, phys_addr, addr, size);
	अगर (ret)
		dev_err(&epc->dev,
			"%s intf: Failed to map memory window %d address\n",
			pci_epc_पूर्णांकerface_string(type), mw);

err_invalid_size:

	वापस ret;
पूर्ण

/**
 * epf_ntb_tearकरोwn_mw() - Tearकरोwn the configured OB ATU
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 * @mw: Index of the memory winकरोw (either 0, 1, 2 or 3)
 *
 * Tearकरोwn the configured OB ATU configured in epf_ntb_configure_mw() using
 * pci_epc_unmap_addr()
 */
अटल व्योम epf_ntb_tearकरोwn_mw(काष्ठा epf_ntb *ntb,
				क्रमागत pci_epc_पूर्णांकerface_type type, u32 mw)
अणु
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	काष्ठा pci_epf_bar *peer_epf_bar;
	क्रमागत pci_barno peer_barno;
	काष्ठा epf_ntb_ctrl *ctrl;
	phys_addr_t phys_addr;
	काष्ठा pci_epc *epc;
	u8 func_no;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peer_ntb_epc = ntb->epc[!type];
	peer_barno = peer_ntb_epc->epf_ntb_bar[mw + NTB_MW_OFFSET];
	peer_epf_bar = &peer_ntb_epc->epf_bar[peer_barno];

	phys_addr = peer_epf_bar->phys_addr;
	ctrl = ntb_epc->reg;
	अगर (mw + NTB_MW_OFFSET == BAR_DB_MW1)
		phys_addr += ctrl->mw1_offset;
	func_no = ntb_epc->func_no;

	pci_epc_unmap_addr(epc, func_no, phys_addr);
पूर्ण

/**
 * epf_ntb_configure_msi() - Map OB address space to MSI address
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 * @db_count: Number of करोorbell पूर्णांकerrupts to map
 *
 *+-----------------+    +----->+----------------+-----------+-----------------+
 *|       BAR0      |    |      |   Doorbell 1   +---+------->   MSI ADDRESS   |
 *+-----------------+    |      +----------------+   |       +-----------------+
 *|       BAR1      |    |      |   Doorbell 2   +---+       |                 |
 *+-----------------+----+      +----------------+   |       |                 |
 *|       BAR2      |           |   Doorbell 3   +---+       |                 |
 *+-----------------+----+      +----------------+   |       |                 |
 *|       BAR3      |    |      |   Doorbell 4   +---+       |                 |
 *+-----------------+    |      |----------------+           |                 |
 *|       BAR4      |    |      |                |           |                 |
 *+-----------------+    |      |      MW1       |           |                 |
 *|       BAR5      |    |      |                |           |                 |
 *+-----------------+    +----->-----------------+           |                 |
 *  EP CONTROLLER 1             |                |           |                 |
 *                              |                |           |                 |
 *                              +----------------+           +-----------------+
 *                     (A)       EP CONTROLLER 2             |                 |
 *                                 (OB SPACE)                |                 |
 *                                                           |      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Address Space
 *                                                           (Managed by HOST2)
 *
 *
 * This function perक्रमms stage (B) in the above diagram (see Doorbell 1,
 * Doorbell 2, Doorbell 3, Doorbell 4) i.e map OB address space corresponding to
 * करोorbell to MSI address in PCI address space.
 *
 * This operation requires 3 parameters
 *  1) Address reserved क्रम करोorbell in the outbound address space
 *  2) MSI-X address in the PCIe Address space
 *  3) Number of MSI-X पूर्णांकerrupts that has to be configured
 *
 * The address in the outbound address space (क्रम the Doorbell) is stored in
 * epf_bar corresponding to BAR_DB_MW1 of epf_ntb_epc that is connected to
 * HOST1. This is populated in epf_ntb_alloc_peer_mem() in this driver aदीर्घ
 * with address क्रम MW1.
 *
 * pci_epc_map_msi_irq() takes the MSI address from MSI capability रेजिस्टर
 * and maps the OB address (obtained in epf_ntb_alloc_peer_mem()) to the MSI
 * address.
 *
 * epf_ntb_configure_msi() also stores the MSI data to उठाओ each पूर्णांकerrupt
 * in db_data of the peer's control region. This helps the peer to उठाओ
 * करोorbell of the other host by writing db_data to the BAR corresponding to
 * BAR_DB_MW1.
 */
अटल पूर्णांक epf_ntb_configure_msi(काष्ठा epf_ntb *ntb,
				 क्रमागत pci_epc_पूर्णांकerface_type type, u16 db_count)
अणु
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	u32 db_entry_size, db_data, db_offset;
	काष्ठा pci_epf_bar *peer_epf_bar;
	काष्ठा epf_ntb_ctrl *peer_ctrl;
	क्रमागत pci_barno peer_barno;
	phys_addr_t phys_addr;
	काष्ठा pci_epc *epc;
	u8 func_no;
	पूर्णांक ret, i;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peer_ntb_epc = ntb->epc[!type];
	peer_barno = peer_ntb_epc->epf_ntb_bar[BAR_DB_MW1];
	peer_epf_bar = &peer_ntb_epc->epf_bar[peer_barno];
	peer_ctrl = peer_ntb_epc->reg;
	db_entry_size = peer_ctrl->db_entry_size;

	phys_addr = peer_epf_bar->phys_addr;
	func_no = ntb_epc->func_no;

	ret = pci_epc_map_msi_irq(epc, func_no, phys_addr, db_count,
				  db_entry_size, &db_data, &db_offset);
	अगर (ret) अणु
		dev_err(&epc->dev, "%s intf: Failed to map MSI IRQ\n",
			pci_epc_पूर्णांकerface_string(type));
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < db_count; i++) अणु
		peer_ctrl->db_data[i] = db_data | i;
		peer_ctrl->db_offset[i] = db_offset;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_configure_msix() - Map OB address space to MSI-X address
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 * @db_count: Number of करोorbell पूर्णांकerrupts to map
 *
 *+-----------------+    +----->+----------------+-----------+-----------------+
 *|       BAR0      |    |      |   Doorbell 1   +-----------> MSI-X ADDRESS 1 |
 *+-----------------+    |      +----------------+           +-----------------+
 *|       BAR1      |    |      |   Doorbell 2   +---------+ |                 |
 *+-----------------+----+      +----------------+         | |                 |
 *|       BAR2      |           |   Doorbell 3   +-------+ | +-----------------+
 *+-----------------+----+      +----------------+       | +-> MSI-X ADDRESS 2 |
 *|       BAR3      |    |      |   Doorbell 4   +-----+ |   +-----------------+
 *+-----------------+    |      |----------------+     | |   |                 |
 *|       BAR4      |    |      |                |     | |   +-----------------+
 *+-----------------+    |      |      MW1       +     | +-->+ MSI-X ADDRESS 3||
 *|       BAR5      |    |      |                |     |     +-----------------+
 *+-----------------+    +----->-----------------+     |     |                 |
 *  EP CONTROLLER 1             |                |     |     +-----------------+
 *                              |                |     +---->+ MSI-X ADDRESS 4 |
 *                              +----------------+           +-----------------+
 *                     (A)       EP CONTROLLER 2             |                 |
 *                                 (OB SPACE)                |                 |
 *                                                           |      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Address Space
 *                                                           (Managed by HOST2)
 *
 * This function perक्रमms stage (B) in the above diagram (see Doorbell 1,
 * Doorbell 2, Doorbell 3, Doorbell 4) i.e map OB address space corresponding to
 * करोorbell to MSI-X address in PCI address space.
 *
 * This operation requires 3 parameters
 *  1) Address reserved क्रम करोorbell in the outbound address space
 *  2) MSI-X address in the PCIe Address space
 *  3) Number of MSI-X पूर्णांकerrupts that has to be configured
 *
 * The address in the outbound address space (क्रम the Doorbell) is stored in
 * epf_bar corresponding to BAR_DB_MW1 of epf_ntb_epc that is connected to
 * HOST1. This is populated in epf_ntb_alloc_peer_mem() in this driver aदीर्घ
 * with address क्रम MW1.
 *
 * The MSI-X address is in the MSI-X table of EP CONTROLLER 2 and
 * the count of करोorbell is in ctrl->argument of epf_ntb_epc that is connected
 * to HOST2. MSI-X table is stored memory mapped to ntb_epc->msix_bar and the
 * offset is in ntb_epc->msix_table_offset. From this epf_ntb_configure_msix()
 * माला_लो the MSI-X address and data.
 *
 * epf_ntb_configure_msix() also stores the MSI-X data to उठाओ each पूर्णांकerrupt
 * in db_data of the peer's control region. This helps the peer to उठाओ
 * करोorbell of the other host by writing db_data to the BAR corresponding to
 * BAR_DB_MW1.
 */
अटल पूर्णांक epf_ntb_configure_msix(काष्ठा epf_ntb *ntb,
				  क्रमागत pci_epc_पूर्णांकerface_type type,
				  u16 db_count)
अणु
	स्थिर काष्ठा pci_epc_features *epc_features;
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	काष्ठा pci_epf_bar *peer_epf_bar, *epf_bar;
	काष्ठा pci_epf_msix_tbl *msix_tbl;
	काष्ठा epf_ntb_ctrl *peer_ctrl;
	u32 db_entry_size, msg_data;
	क्रमागत pci_barno peer_barno;
	phys_addr_t phys_addr;
	काष्ठा pci_epc *epc;
	माप_प्रकार align;
	u64 msg_addr;
	u8 func_no;
	पूर्णांक ret, i;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	epf_bar = &ntb_epc->epf_bar[ntb_epc->msix_bar];
	msix_tbl = epf_bar->addr + ntb_epc->msix_table_offset;

	peer_ntb_epc = ntb->epc[!type];
	peer_barno = peer_ntb_epc->epf_ntb_bar[BAR_DB_MW1];
	peer_epf_bar = &peer_ntb_epc->epf_bar[peer_barno];
	phys_addr = peer_epf_bar->phys_addr;
	peer_ctrl = peer_ntb_epc->reg;
	epc_features = ntb_epc->epc_features;
	align = epc_features->align;

	func_no = ntb_epc->func_no;
	db_entry_size = peer_ctrl->db_entry_size;

	क्रम (i = 0; i < db_count; i++) अणु
		msg_addr = ALIGN_DOWN(msix_tbl[i].msg_addr, align);
		msg_data = msix_tbl[i].msg_data;
		ret = pci_epc_map_addr(epc, func_no, phys_addr, msg_addr,
				       db_entry_size);
		अगर (ret) अणु
			dev_err(&epc->dev,
				"%s intf: Failed to configure MSI-X IRQ\n",
				pci_epc_पूर्णांकerface_string(type));
			वापस ret;
		पूर्ण
		phys_addr = phys_addr + db_entry_size;
		peer_ctrl->db_data[i] = msg_data;
		peer_ctrl->db_offset[i] = msix_tbl[i].msg_addr & (align - 1);
	पूर्ण
	ntb_epc->is_msix = true;

	वापस 0;
पूर्ण

/**
 * epf_ntb_configure_db() - Configure the Outbound Address Space क्रम one host
 *   to ring the करोorbell of other host
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 * @db_count: Count of the number of करोorbells that has to be configured
 * @msix: Indicates whether MSI-X or MSI should be used
 *
 * Invokes epf_ntb_configure_msix() or epf_ntb_configure_msi() required क्रम
 * one HOST to ring the करोorbell of other HOST.
 */
अटल पूर्णांक epf_ntb_configure_db(काष्ठा epf_ntb *ntb,
				क्रमागत pci_epc_पूर्णांकerface_type type,
				u16 db_count, bool msix)
अणु
	काष्ठा epf_ntb_epc *ntb_epc;
	काष्ठा pci_epc *epc;
	पूर्णांक ret;

	अगर (db_count > MAX_DB_COUNT)
		वापस -EINVAL;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	अगर (msix)
		ret = epf_ntb_configure_msix(ntb, type, db_count);
	अन्यथा
		ret = epf_ntb_configure_msi(ntb, type, db_count);

	अगर (ret)
		dev_err(&epc->dev, "%s intf: Failed to configure DB\n",
			pci_epc_पूर्णांकerface_string(type));

	वापस ret;
पूर्ण

/**
 * epf_ntb_tearकरोwn_db() - Unmap address in OB address space to MSI/MSI-X
 *   address
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Invoke pci_epc_unmap_addr() to unmap OB address to MSI/MSI-X address.
 */
अटल व्योम
epf_ntb_tearकरोwn_db(काष्ठा epf_ntb *ntb, क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	काष्ठा pci_epf_bar *peer_epf_bar;
	क्रमागत pci_barno peer_barno;
	phys_addr_t phys_addr;
	काष्ठा pci_epc *epc;
	u8 func_no;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peer_ntb_epc = ntb->epc[!type];
	peer_barno = peer_ntb_epc->epf_ntb_bar[BAR_DB_MW1];
	peer_epf_bar = &peer_ntb_epc->epf_bar[peer_barno];
	phys_addr = peer_epf_bar->phys_addr;
	func_no = ntb_epc->func_no;

	pci_epc_unmap_addr(epc, func_no, phys_addr);
पूर्ण

/**
 * epf_ntb_cmd_handler() - Handle commands provided by the NTB Host
 * @work: work_काष्ठा क्रम the two epf_ntb_epc (PRIMARY and SECONDARY)
 *
 * Workqueue function that माला_लो invoked क्रम the two epf_ntb_epc
 * periodically (once every 5ms) to see अगर it has received any commands
 * from NTB host. The host can send commands to configure करोorbell or
 * configure memory winकरोw or to update link status.
 */
अटल व्योम epf_ntb_cmd_handler(काष्ठा work_काष्ठा *work)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;
	काष्ठा epf_ntb_epc *ntb_epc;
	काष्ठा epf_ntb_ctrl *ctrl;
	u32 command, argument;
	काष्ठा epf_ntb *ntb;
	काष्ठा device *dev;
	u16 db_count;
	bool is_msix;
	पूर्णांक ret;

	ntb_epc = container_of(work, काष्ठा epf_ntb_epc, cmd_handler.work);
	ctrl = ntb_epc->reg;
	command = ctrl->command;
	अगर (!command)
		जाओ reset_handler;
	argument = ctrl->argument;

	ctrl->command = 0;
	ctrl->argument = 0;

	ctrl = ntb_epc->reg;
	type = ntb_epc->type;
	ntb = ntb_epc->epf_ntb;
	dev = &ntb->epf->dev;

	चयन (command) अणु
	हाल COMMAND_CONFIGURE_DOORBELL:
		db_count = argument & DB_COUNT_MASK;
		is_msix = argument & MSIX_ENABLE;
		ret = epf_ntb_configure_db(ntb, type, db_count, is_msix);
		अगर (ret < 0)
			ctrl->command_status = COMMAND_STATUS_ERROR;
		अन्यथा
			ctrl->command_status = COMMAND_STATUS_OK;
		अवरोध;
	हाल COMMAND_TEARDOWN_DOORBELL:
		epf_ntb_tearकरोwn_db(ntb, type);
		ctrl->command_status = COMMAND_STATUS_OK;
		अवरोध;
	हाल COMMAND_CONFIGURE_MW:
		ret = epf_ntb_configure_mw(ntb, type, argument);
		अगर (ret < 0)
			ctrl->command_status = COMMAND_STATUS_ERROR;
		अन्यथा
			ctrl->command_status = COMMAND_STATUS_OK;
		अवरोध;
	हाल COMMAND_TEARDOWN_MW:
		epf_ntb_tearकरोwn_mw(ntb, type, argument);
		ctrl->command_status = COMMAND_STATUS_OK;
		अवरोध;
	हाल COMMAND_LINK_UP:
		ntb_epc->linkup = true;
		अगर (ntb->epc[PRIMARY_INTERFACE]->linkup &&
		    ntb->epc[SECONDARY_INTERFACE]->linkup) अणु
			ret = epf_ntb_link_up(ntb, true);
			अगर (ret < 0)
				ctrl->command_status = COMMAND_STATUS_ERROR;
			अन्यथा
				ctrl->command_status = COMMAND_STATUS_OK;
			जाओ reset_handler;
		पूर्ण
		ctrl->command_status = COMMAND_STATUS_OK;
		अवरोध;
	हाल COMMAND_LINK_DOWN:
		ntb_epc->linkup = false;
		ret = epf_ntb_link_up(ntb, false);
		अगर (ret < 0)
			ctrl->command_status = COMMAND_STATUS_ERROR;
		अन्यथा
			ctrl->command_status = COMMAND_STATUS_OK;
		अवरोध;
	शेष:
		dev_err(dev, "%s intf UNKNOWN command: %d\n",
			pci_epc_पूर्णांकerface_string(type), command);
		अवरोध;
	पूर्ण

reset_handler:
	queue_delayed_work(kpcपूर्णांकb_workqueue, &ntb_epc->cmd_handler,
			   msecs_to_jअगरfies(5));
पूर्ण

/**
 * epf_ntb_peer_spad_bar_clear() - Clear Peer Scratchpad BAR
 * @ntb_epc: EPC associated with one of the HOST which holds peer's outbound
 *	     address.
 *
 *+-----------------+------->+------------------+        +-----------------+
 *|       BAR0      |        |  CONFIG REGION   |        |       BAR0      |
 *+-----------------+----+   +------------------+<-------+-----------------+
 *|       BAR1      |    |   |SCRATCHPAD REGION |        |       BAR1      |
 *+-----------------+    +-->+------------------+<-------+-----------------+
 *|       BAR2      |            Local Memory            |       BAR2      |
 *+-----------------+                                    +-----------------+
 *|       BAR3      |                                    |       BAR3      |
 *+-----------------+                                    +-----------------+
 *|       BAR4      |                                    |       BAR4      |
 *+-----------------+                                    +-----------------+
 *|       BAR5      |                                    |       BAR5      |
 *+-----------------+                                    +-----------------+
 *  EP CONTROLLER 1                                        EP CONTROLLER 2
 *
 * Clear BAR1 of EP CONTROLLER 2 which contains the HOST2's peer scratchpad
 * region. While BAR1 is the शेष peer scratchpad BAR, an NTB could have
 * other BARs क्रम peer scratchpad (because of 64-bit BARs or reserved BARs).
 * This function can get the exact BAR used क्रम peer scratchpad from
 * epf_ntb_bar[BAR_PEER_SPAD].
 *
 * Since HOST2's peer scratchpad is also HOST1's self scratchpad, this function
 * माला_लो the address of peer scratchpad from
 * peer_ntb_epc->epf_ntb_bar[BAR_CONFIG].
 */
अटल व्योम epf_ntb_peer_spad_bar_clear(काष्ठा epf_ntb_epc *ntb_epc)
अणु
	काष्ठा pci_epf_bar *epf_bar;
	क्रमागत pci_barno barno;
	काष्ठा pci_epc *epc;
	u8 func_no;

	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;
	barno = ntb_epc->epf_ntb_bar[BAR_PEER_SPAD];
	epf_bar = &ntb_epc->epf_bar[barno];
	pci_epc_clear_bar(epc, func_no, epf_bar);
पूर्ण

/**
 * epf_ntb_peer_spad_bar_set() - Set peer scratchpad BAR
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 *+-----------------+------->+------------------+        +-----------------+
 *|       BAR0      |        |  CONFIG REGION   |        |       BAR0      |
 *+-----------------+----+   +------------------+<-------+-----------------+
 *|       BAR1      |    |   |SCRATCHPAD REGION |        |       BAR1      |
 *+-----------------+    +-->+------------------+<-------+-----------------+
 *|       BAR2      |            Local Memory            |       BAR2      |
 *+-----------------+                                    +-----------------+
 *|       BAR3      |                                    |       BAR3      |
 *+-----------------+                                    +-----------------+
 *|       BAR4      |                                    |       BAR4      |
 *+-----------------+                                    +-----------------+
 *|       BAR5      |                                    |       BAR5      |
 *+-----------------+                                    +-----------------+
 *  EP CONTROLLER 1                                        EP CONTROLLER 2
 *
 * Set BAR1 of EP CONTROLLER 2 which contains the HOST2's peer scratchpad
 * region. While BAR1 is the शेष peer scratchpad BAR, an NTB could have
 * other BARs क्रम peer scratchpad (because of 64-bit BARs or reserved BARs).
 * This function can get the exact BAR used क्रम peer scratchpad from
 * epf_ntb_bar[BAR_PEER_SPAD].
 *
 * Since HOST2's peer scratchpad is also HOST1's self scratchpad, this function
 * माला_लो the address of peer scratchpad from
 * peer_ntb_epc->epf_ntb_bar[BAR_CONFIG].
 */
अटल पूर्णांक epf_ntb_peer_spad_bar_set(काष्ठा epf_ntb *ntb,
				     क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	काष्ठा pci_epf_bar *peer_epf_bar, *epf_bar;
	क्रमागत pci_barno peer_barno, barno;
	u32 peer_spad_offset;
	काष्ठा pci_epc *epc;
	काष्ठा device *dev;
	u8 func_no;
	पूर्णांक ret;

	dev = &ntb->epf->dev;

	peer_ntb_epc = ntb->epc[!type];
	peer_barno = peer_ntb_epc->epf_ntb_bar[BAR_CONFIG];
	peer_epf_bar = &peer_ntb_epc->epf_bar[peer_barno];

	ntb_epc = ntb->epc[type];
	barno = ntb_epc->epf_ntb_bar[BAR_PEER_SPAD];
	epf_bar = &ntb_epc->epf_bar[barno];
	func_no = ntb_epc->func_no;
	epc = ntb_epc->epc;

	peer_spad_offset = peer_ntb_epc->reg->spad_offset;
	epf_bar->phys_addr = peer_epf_bar->phys_addr + peer_spad_offset;
	epf_bar->size = peer_ntb_epc->spad_size;
	epf_bar->barno = barno;
	epf_bar->flags = PCI_BASE_ADDRESS_MEM_TYPE_32;

	ret = pci_epc_set_bar(epc, func_no, epf_bar);
	अगर (ret) अणु
		dev_err(dev, "%s intf: peer SPAD BAR set failed\n",
			pci_epc_पूर्णांकerface_string(type));
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_config_sspad_bar_clear() - Clear Config + Self scratchpad BAR
 * @ntb_epc: EPC associated with one of the HOST which holds peer's outbound
 *	     address.
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAR0      |        |  CONFIG REGION   |        |       BAR0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAR1      |    |   |SCRATCHPAD REGION |        |       BAR1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAR2      |            Local Memory            |       BAR2      |
 * +-----------------+                                    +-----------------+
 * |       BAR3      |                                    |       BAR3      |
 * +-----------------+                                    +-----------------+
 * |       BAR4      |                                    |       BAR4      |
 * +-----------------+                                    +-----------------+
 * |       BAR5      |                                    |       BAR5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTROLLER 1                                        EP CONTROLLER 2
 *
 * Clear BAR0 of EP CONTROLLER 1 which contains the HOST1's config and
 * self scratchpad region (हटाओs inbound ATU configuration). While BAR0 is
 * the शेष self scratchpad BAR, an NTB could have other BARs क्रम self
 * scratchpad (because of reserved BARs). This function can get the exact BAR
 * used क्रम self scratchpad from epf_ntb_bar[BAR_CONFIG].
 *
 * Please note the self scratchpad region and config region is combined to
 * a single region and mapped using the same BAR. Also note HOST2's peer
 * scratchpad is HOST1's self scratchpad.
 */
अटल व्योम epf_ntb_config_sspad_bar_clear(काष्ठा epf_ntb_epc *ntb_epc)
अणु
	काष्ठा pci_epf_bar *epf_bar;
	क्रमागत pci_barno barno;
	काष्ठा pci_epc *epc;
	u8 func_no;

	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;
	barno = ntb_epc->epf_ntb_bar[BAR_CONFIG];
	epf_bar = &ntb_epc->epf_bar[barno];
	pci_epc_clear_bar(epc, func_no, epf_bar);
पूर्ण

/**
 * epf_ntb_config_sspad_bar_set() - Set Config + Self scratchpad BAR
 * @ntb_epc: EPC associated with one of the HOST which holds peer's outbound
 *	     address.
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAR0      |        |  CONFIG REGION   |        |       BAR0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAR1      |    |   |SCRATCHPAD REGION |        |       BAR1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAR2      |            Local Memory            |       BAR2      |
 * +-----------------+                                    +-----------------+
 * |       BAR3      |                                    |       BAR3      |
 * +-----------------+                                    +-----------------+
 * |       BAR4      |                                    |       BAR4      |
 * +-----------------+                                    +-----------------+
 * |       BAR5      |                                    |       BAR5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTROLLER 1                                        EP CONTROLLER 2
 *
 * Map BAR0 of EP CONTROLLER 1 which contains the HOST1's config and
 * self scratchpad region. While BAR0 is the शेष self scratchpad BAR, an
 * NTB could have other BARs क्रम self scratchpad (because of reserved BARs).
 * This function can get the exact BAR used क्रम self scratchpad from
 * epf_ntb_bar[BAR_CONFIG].
 *
 * Please note the self scratchpad region and config region is combined to
 * a single region and mapped using the same BAR. Also note HOST2's peer
 * scratchpad is HOST1's self scratchpad.
 */
अटल पूर्णांक epf_ntb_config_sspad_bar_set(काष्ठा epf_ntb_epc *ntb_epc)
अणु
	काष्ठा pci_epf_bar *epf_bar;
	क्रमागत pci_barno barno;
	काष्ठा epf_ntb *ntb;
	काष्ठा pci_epc *epc;
	काष्ठा device *dev;
	u8 func_no;
	पूर्णांक ret;

	ntb = ntb_epc->epf_ntb;
	dev = &ntb->epf->dev;

	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;
	barno = ntb_epc->epf_ntb_bar[BAR_CONFIG];
	epf_bar = &ntb_epc->epf_bar[barno];

	ret = pci_epc_set_bar(epc, func_no, epf_bar);
	अगर (ret) अणु
		dev_err(dev, "%s inft: Config/Status/SPAD BAR set failed\n",
			pci_epc_पूर्णांकerface_string(ntb_epc->type));
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_config_spad_bar_मुक्त() - Free the physical memory associated with
 *   config + scratchpad region
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAR0      |        |  CONFIG REGION   |        |       BAR0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAR1      |    |   |SCRATCHPAD REGION |        |       BAR1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAR2      |            Local Memory            |       BAR2      |
 * +-----------------+                                    +-----------------+
 * |       BAR3      |                                    |       BAR3      |
 * +-----------------+                                    +-----------------+
 * |       BAR4      |                                    |       BAR4      |
 * +-----------------+                                    +-----------------+
 * |       BAR5      |                                    |       BAR5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTROLLER 1                                        EP CONTROLLER 2
 *
 * Free the Local Memory mentioned in the above diagram. After invoking this
 * function, any of config + self scratchpad region of HOST1 or peer scratchpad
 * region of HOST2 should not be accessed.
 */
अटल व्योम epf_ntb_config_spad_bar_मुक्त(काष्ठा epf_ntb *ntb)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;
	काष्ठा epf_ntb_epc *ntb_epc;
	क्रमागत pci_barno barno;
	काष्ठा pci_epf *epf;

	epf = ntb->epf;
	क्रम (type = PRIMARY_INTERFACE; type <= SECONDARY_INTERFACE; type++) अणु
		ntb_epc = ntb->epc[type];
		barno = ntb_epc->epf_ntb_bar[BAR_CONFIG];
		अगर (ntb_epc->reg)
			pci_epf_मुक्त_space(epf, ntb_epc->reg, barno, type);
	पूर्ण
पूर्ण

/**
 * epf_ntb_config_spad_bar_alloc() - Allocate memory क्रम config + scratchpad
 *   region
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAR0      |        |  CONFIG REGION   |        |       BAR0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAR1      |    |   |SCRATCHPAD REGION |        |       BAR1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAR2      |            Local Memory            |       BAR2      |
 * +-----------------+                                    +-----------------+
 * |       BAR3      |                                    |       BAR3      |
 * +-----------------+                                    +-----------------+
 * |       BAR4      |                                    |       BAR4      |
 * +-----------------+                                    +-----------------+
 * |       BAR5      |                                    |       BAR5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTROLLER 1                                        EP CONTROLLER 2
 *
 * Allocate the Local Memory mentioned in the above diagram. The size of
 * CONFIG REGION is माप(काष्ठा epf_ntb_ctrl) and size of SCRATCHPAD REGION
 * is obtained from "spad-count" configfs entry.
 *
 * The size of both config region and scratchpad region has to be aligned,
 * since the scratchpad region will also be mapped as PEER SCRATCHPAD of
 * other host using a separate BAR.
 */
अटल पूर्णांक epf_ntb_config_spad_bar_alloc(काष्ठा epf_ntb *ntb,
					 क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	स्थिर काष्ठा pci_epc_features *peer_epc_features, *epc_features;
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	माप_प्रकार msix_table_size, pba_size, align;
	क्रमागत pci_barno peer_barno, barno;
	काष्ठा epf_ntb_ctrl *ctrl;
	u32 spad_size, ctrl_size;
	u64 size, peer_size;
	काष्ठा pci_epf *epf;
	काष्ठा device *dev;
	bool msix_capable;
	u32 spad_count;
	व्योम *base;

	epf = ntb->epf;
	dev = &epf->dev;
	ntb_epc = ntb->epc[type];

	epc_features = ntb_epc->epc_features;
	barno = ntb_epc->epf_ntb_bar[BAR_CONFIG];
	size = epc_features->bar_fixed_size[barno];
	align = epc_features->align;

	peer_ntb_epc = ntb->epc[!type];
	peer_epc_features = peer_ntb_epc->epc_features;
	peer_barno = ntb_epc->epf_ntb_bar[BAR_PEER_SPAD];
	peer_size = peer_epc_features->bar_fixed_size[peer_barno];

	/* Check अगर epc_features is populated incorrectly */
	अगर ((!IS_ALIGNED(size, align)))
		वापस -EINVAL;

	spad_count = ntb->spad_count;

	ctrl_size = माप(काष्ठा epf_ntb_ctrl);
	spad_size = spad_count * 4;

	msix_capable = epc_features->msix_capable;
	अगर (msix_capable) अणु
		msix_table_size = PCI_MSIX_ENTRY_SIZE * ntb->db_count;
		ctrl_size = ALIGN(ctrl_size, 8);
		ntb_epc->msix_table_offset = ctrl_size;
		ntb_epc->msix_bar = barno;
		/* Align to QWORD or 8 Bytes */
		pba_size = ALIGN(DIV_ROUND_UP(ntb->db_count, 8), 8);
		ctrl_size = ctrl_size + msix_table_size + pba_size;
	पूर्ण

	अगर (!align) अणु
		ctrl_size = roundup_घात_of_two(ctrl_size);
		spad_size = roundup_घात_of_two(spad_size);
	पूर्ण अन्यथा अणु
		ctrl_size = ALIGN(ctrl_size, align);
		spad_size = ALIGN(spad_size, align);
	पूर्ण

	अगर (peer_size) अणु
		अगर (peer_size < spad_size)
			spad_count = peer_size / 4;
		spad_size = peer_size;
	पूर्ण

	/*
	 * In order to make sure SPAD offset is aligned to its size,
	 * expand control region size to the size of SPAD अगर SPAD size
	 * is greater than control region size.
	 */
	अगर (spad_size > ctrl_size)
		ctrl_size = spad_size;

	अगर (!size)
		size = ctrl_size + spad_size;
	अन्यथा अगर (size < ctrl_size + spad_size)
		वापस -EINVAL;

	base = pci_epf_alloc_space(epf, size, barno, align, type);
	अगर (!base) अणु
		dev_err(dev, "%s intf: Config/Status/SPAD alloc region fail\n",
			pci_epc_पूर्णांकerface_string(type));
		वापस -ENOMEM;
	पूर्ण

	ntb_epc->reg = base;

	ctrl = ntb_epc->reg;
	ctrl->spad_offset = ctrl_size;
	ctrl->spad_count = spad_count;
	ctrl->num_mws = ntb->num_mws;
	ctrl->db_entry_size = align ? align : 4;
	ntb_epc->spad_size = spad_size;

	वापस 0;
पूर्ण

/**
 * epf_ntb_config_spad_bar_alloc_पूर्णांकerface() - Allocate memory क्रम config +
 *   scratchpad region क्रम each of PRIMARY and SECONDARY पूर्णांकerface
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 *
 * Wrapper क्रम epf_ntb_config_spad_bar_alloc() which allocates memory क्रम
 * config + scratchpad region क्रम a specअगरic पूर्णांकerface
 */
अटल पूर्णांक epf_ntb_config_spad_bar_alloc_पूर्णांकerface(काष्ठा epf_ntb *ntb)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = &ntb->epf->dev;

	क्रम (type = PRIMARY_INTERFACE; type <= SECONDARY_INTERFACE; type++) अणु
		ret = epf_ntb_config_spad_bar_alloc(ntb, type);
		अगर (ret) अणु
			dev_err(dev, "%s intf: Config/SPAD BAR alloc failed\n",
				pci_epc_पूर्णांकerface_string(type));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_मुक्त_peer_mem() - Free memory allocated in peers outbound address
 *   space
 * @ntb_epc: EPC associated with one of the HOST which holds peers outbound
 *   address regions
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAR0      |    |     |   Doorbell 1   +-----------> MSI|X ADDRESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAR1      |    |     |   Doorbell 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAR2      |          |   Doorbell 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDRESS 2 |
 * |       BAR3      |    |     |   Doorbell 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAR4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDRESS 3||
 * |       BAR5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTROLLER 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDRESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTROLLER 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Address Space
 *                                                           (Managed by HOST2)
 *
 * Free memory allocated in EP CONTROLLER 2 (OB SPACE) in the above diagram.
 * It'll मुक्त Doorbell 1, Doorbell 2, Doorbell 3, Doorbell 4, MW1 (and MW2, MW3,
 * MW4).
 */
अटल व्योम epf_ntb_मुक्त_peer_mem(काष्ठा epf_ntb_epc *ntb_epc)
अणु
	काष्ठा pci_epf_bar *epf_bar;
	व्योम __iomem *mw_addr;
	phys_addr_t phys_addr;
	क्रमागत epf_ntb_bar bar;
	क्रमागत pci_barno barno;
	काष्ठा pci_epc *epc;
	माप_प्रकार size;

	epc = ntb_epc->epc;

	क्रम (bar = BAR_DB_MW1; bar < BAR_MW4; bar++) अणु
		barno = ntb_epc->epf_ntb_bar[bar];
		mw_addr = ntb_epc->mw_addr[barno];
		epf_bar = &ntb_epc->epf_bar[barno];
		phys_addr = epf_bar->phys_addr;
		size = epf_bar->size;
		अगर (mw_addr) अणु
			pci_epc_mem_मुक्त_addr(epc, phys_addr, mw_addr, size);
			ntb_epc->mw_addr[barno] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * epf_ntb_db_mw_bar_clear() - Clear करोorbell and memory BAR
 * @ntb_epc: EPC associated with one of the HOST which holds peer's outbound
 *   address
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAR0      |    |     |   Doorbell 1   +-----------> MSI|X ADDRESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAR1      |    |     |   Doorbell 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAR2      |          |   Doorbell 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDRESS 2 |
 * |       BAR3      |    |     |   Doorbell 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAR4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDRESS 3||
 * |       BAR5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTROLLER 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDRESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTROLLER 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Address Space
 *                                                           (Managed by HOST2)
 *
 * Clear करोorbell and memory BARs (हटाओ inbound ATU configuration). In the above
 * diagram it clears BAR2 TO BAR5 of EP CONTROLLER 1 (Doorbell BAR, MW1 BAR, MW2
 * BAR, MW3 BAR and MW4 BAR).
 */
अटल व्योम epf_ntb_db_mw_bar_clear(काष्ठा epf_ntb_epc *ntb_epc)
अणु
	काष्ठा pci_epf_bar *epf_bar;
	क्रमागत epf_ntb_bar bar;
	क्रमागत pci_barno barno;
	काष्ठा pci_epc *epc;
	u8 func_no;

	epc = ntb_epc->epc;

	func_no = ntb_epc->func_no;

	क्रम (bar = BAR_DB_MW1; bar < BAR_MW4; bar++) अणु
		barno = ntb_epc->epf_ntb_bar[bar];
		epf_bar = &ntb_epc->epf_bar[barno];
		pci_epc_clear_bar(epc, func_no, epf_bar);
	पूर्ण
पूर्ण

/**
 * epf_ntb_db_mw_bar_cleanup() - Clear करोorbell/memory BAR and मुक्त memory
 *   allocated in peers outbound address space
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Wrapper क्रम epf_ntb_db_mw_bar_clear() to clear HOST1's BAR and
 * epf_ntb_मुक्त_peer_mem() which मुक्तs up HOST2 outbound memory.
 */
अटल व्योम epf_ntb_db_mw_bar_cleanup(काष्ठा epf_ntb *ntb,
				      क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;

	ntb_epc = ntb->epc[type];
	peer_ntb_epc = ntb->epc[!type];

	epf_ntb_db_mw_bar_clear(ntb_epc);
	epf_ntb_मुक्त_peer_mem(peer_ntb_epc);
पूर्ण

/**
 * epf_ntb_configure_पूर्णांकerrupt() - Configure MSI/MSI-X capaiblity
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Configure MSI/MSI-X capability क्रम each पूर्णांकerface with number of
 * पूर्णांकerrupts equal to "db_count" configfs entry.
 */
अटल पूर्णांक epf_ntb_configure_पूर्णांकerrupt(काष्ठा epf_ntb *ntb,
				       क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	स्थिर काष्ठा pci_epc_features *epc_features;
	bool msix_capable, msi_capable;
	काष्ठा epf_ntb_epc *ntb_epc;
	काष्ठा pci_epc *epc;
	काष्ठा device *dev;
	u32 db_count;
	u8 func_no;
	पूर्णांक ret;

	ntb_epc = ntb->epc[type];
	dev = &ntb->epf->dev;

	epc_features = ntb_epc->epc_features;
	msix_capable = epc_features->msix_capable;
	msi_capable = epc_features->msi_capable;

	अगर (!(msix_capable || msi_capable)) अणु
		dev_err(dev, "MSI or MSI-X is required for doorbell\n");
		वापस -EINVAL;
	पूर्ण

	func_no = ntb_epc->func_no;

	db_count = ntb->db_count;
	अगर (db_count > MAX_DB_COUNT) अणु
		dev_err(dev, "DB count cannot be more than %d\n", MAX_DB_COUNT);
		वापस -EINVAL;
	पूर्ण

	ntb->db_count = db_count;
	epc = ntb_epc->epc;

	अगर (msi_capable) अणु
		ret = pci_epc_set_msi(epc, func_no, db_count);
		अगर (ret) अणु
			dev_err(dev, "%s intf: MSI configuration failed\n",
				pci_epc_पूर्णांकerface_string(type));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (msix_capable) अणु
		ret = pci_epc_set_msix(epc, func_no, db_count,
				       ntb_epc->msix_bar,
				       ntb_epc->msix_table_offset);
		अगर (ret) अणु
			dev_err(dev, "MSI configuration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_alloc_peer_mem() - Allocate memory in peer's outbound address space
 * @dev: The PCI device.
 * @ntb_epc: EPC associated with one of the HOST whose BAR holds peer's outbound
 *   address
 * @bar: BAR of @ntb_epc in क्रम which memory has to be allocated (could be
 *   BAR_DB_MW1, BAR_MW2, BAR_MW3, BAR_MW4)
 * @peer_ntb_epc: EPC associated with HOST whose outbound address space is
 *   used by @ntb_epc
 * @size: Size of the address region that has to be allocated in peers OB SPACE
 *
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAR0      |    |     |   Doorbell 1   +-----------> MSI|X ADDRESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAR1      |    |     |   Doorbell 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAR2      |          |   Doorbell 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDRESS 2 |
 * |       BAR3      |    |     |   Doorbell 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAR4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDRESS 3||
 * |       BAR5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTROLLER 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDRESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTROLLER 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Address Space
 *                                                           (Managed by HOST2)
 *
 * Allocate memory in OB space of EP CONTROLLER 2 in the above diagram. Allocate
 * क्रम Doorbell 1, Doorbell 2, Doorbell 3, Doorbell 4, MW1 (and MW2, MW3, MW4).
 */
अटल पूर्णांक epf_ntb_alloc_peer_mem(काष्ठा device *dev,
				  काष्ठा epf_ntb_epc *ntb_epc,
				  क्रमागत epf_ntb_bar bar,
				  काष्ठा epf_ntb_epc *peer_ntb_epc,
				  माप_प्रकार size)
अणु
	स्थिर काष्ठा pci_epc_features *epc_features;
	काष्ठा pci_epf_bar *epf_bar;
	काष्ठा pci_epc *peer_epc;
	phys_addr_t phys_addr;
	व्योम __iomem *mw_addr;
	क्रमागत pci_barno barno;
	माप_प्रकार align;

	epc_features = ntb_epc->epc_features;
	align = epc_features->align;

	अगर (size < 128)
		size = 128;

	अगर (align)
		size = ALIGN(size, align);
	अन्यथा
		size = roundup_घात_of_two(size);

	peer_epc = peer_ntb_epc->epc;
	mw_addr = pci_epc_mem_alloc_addr(peer_epc, &phys_addr, size);
	अगर (!mw_addr) अणु
		dev_err(dev, "%s intf: Failed to allocate OB address\n",
			pci_epc_पूर्णांकerface_string(peer_ntb_epc->type));
		वापस -ENOMEM;
	पूर्ण

	barno = ntb_epc->epf_ntb_bar[bar];
	epf_bar = &ntb_epc->epf_bar[barno];
	ntb_epc->mw_addr[barno] = mw_addr;

	epf_bar->phys_addr = phys_addr;
	epf_bar->size = size;
	epf_bar->barno = barno;
	epf_bar->flags = PCI_BASE_ADDRESS_MEM_TYPE_32;

	वापस 0;
पूर्ण

/**
 * epf_ntb_db_mw_bar_init() - Configure Doorbell and Memory winकरोw BARs
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Wrapper क्रम epf_ntb_alloc_peer_mem() and pci_epc_set_bar() that allocates
 * memory in OB address space of HOST2 and configures BAR of HOST1
 */
अटल पूर्णांक epf_ntb_db_mw_bar_init(काष्ठा epf_ntb *ntb,
				  क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	स्थिर काष्ठा pci_epc_features *epc_features;
	काष्ठा epf_ntb_epc *peer_ntb_epc, *ntb_epc;
	काष्ठा pci_epf_bar *epf_bar;
	काष्ठा epf_ntb_ctrl *ctrl;
	u32 num_mws, db_count;
	क्रमागत epf_ntb_bar bar;
	क्रमागत pci_barno barno;
	काष्ठा pci_epc *epc;
	काष्ठा device *dev;
	माप_प्रकार align;
	पूर्णांक ret, i;
	u8 func_no;
	u64 size;

	ntb_epc = ntb->epc[type];
	peer_ntb_epc = ntb->epc[!type];

	dev = &ntb->epf->dev;
	epc_features = ntb_epc->epc_features;
	align = epc_features->align;
	func_no = ntb_epc->func_no;
	epc = ntb_epc->epc;
	num_mws = ntb->num_mws;
	db_count = ntb->db_count;

	क्रम (bar = BAR_DB_MW1, i = 0; i < num_mws; bar++, i++) अणु
		अगर (bar == BAR_DB_MW1) अणु
			align = align ? align : 4;
			size = db_count * align;
			size = ALIGN(size, ntb->mws_size[i]);
			ctrl = ntb_epc->reg;
			ctrl->mw1_offset = size;
			size += ntb->mws_size[i];
		पूर्ण अन्यथा अणु
			size = ntb->mws_size[i];
		पूर्ण

		ret = epf_ntb_alloc_peer_mem(dev, ntb_epc, bar,
					     peer_ntb_epc, size);
		अगर (ret) अणु
			dev_err(dev, "%s intf: DoorBell mem alloc failed\n",
				pci_epc_पूर्णांकerface_string(type));
			जाओ err_alloc_peer_mem;
		पूर्ण

		barno = ntb_epc->epf_ntb_bar[bar];
		epf_bar = &ntb_epc->epf_bar[barno];

		ret = pci_epc_set_bar(epc, func_no, epf_bar);
		अगर (ret) अणु
			dev_err(dev, "%s intf: DoorBell BAR set failed\n",
				pci_epc_पूर्णांकerface_string(type));
			जाओ err_alloc_peer_mem;
		पूर्ण
	पूर्ण

	वापस 0;

err_alloc_peer_mem:
	epf_ntb_db_mw_bar_cleanup(ntb, type);

	वापस ret;
पूर्ण

/**
 * epf_ntb_epc_destroy_पूर्णांकerface() - Cleanup NTB EPC पूर्णांकerface
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Unbind NTB function device from EPC and relinquish reference to pci_epc
 * क्रम each of the पूर्णांकerface.
 */
अटल व्योम epf_ntb_epc_destroy_पूर्णांकerface(काष्ठा epf_ntb *ntb,
					  क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा epf_ntb_epc *ntb_epc;
	काष्ठा pci_epc *epc;
	काष्ठा pci_epf *epf;

	अगर (type < 0)
		वापस;

	epf = ntb->epf;
	ntb_epc = ntb->epc[type];
	अगर (!ntb_epc)
		वापस;
	epc = ntb_epc->epc;
	pci_epc_हटाओ_epf(epc, epf, type);
	pci_epc_put(epc);
पूर्ण

/**
 * epf_ntb_epc_destroy() - Cleanup NTB EPC पूर्णांकerface
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 *
 * Wrapper क्रम epf_ntb_epc_destroy_पूर्णांकerface() to cleanup all the NTB पूर्णांकerfaces
 */
अटल व्योम epf_ntb_epc_destroy(काष्ठा epf_ntb *ntb)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;

	क्रम (type = PRIMARY_INTERFACE; type <= SECONDARY_INTERFACE; type++)
		epf_ntb_epc_destroy_पूर्णांकerface(ntb, type);
पूर्ण

/**
 * epf_ntb_epc_create_पूर्णांकerface() - Create and initialize NTB EPC पूर्णांकerface
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @epc: काष्ठा pci_epc to which a particular NTB पूर्णांकerface should be associated
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Allocate memory क्रम NTB EPC पूर्णांकerface and initialize it.
 */
अटल पूर्णांक epf_ntb_epc_create_पूर्णांकerface(काष्ठा epf_ntb *ntb,
					काष्ठा pci_epc *epc,
					क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	स्थिर काष्ठा pci_epc_features *epc_features;
	काष्ठा pci_epf_bar *epf_bar;
	काष्ठा epf_ntb_epc *ntb_epc;
	काष्ठा pci_epf *epf;
	काष्ठा device *dev;
	u8 func_no;

	dev = &ntb->epf->dev;

	ntb_epc = devm_kzalloc(dev, माप(*ntb_epc), GFP_KERNEL);
	अगर (!ntb_epc)
		वापस -ENOMEM;

	epf = ntb->epf;
	अगर (type == PRIMARY_INTERFACE) अणु
		func_no = epf->func_no;
		epf_bar = epf->bar;
	पूर्ण अन्यथा अणु
		func_no = epf->sec_epc_func_no;
		epf_bar = epf->sec_epc_bar;
	पूर्ण

	ntb_epc->linkup = false;
	ntb_epc->epc = epc;
	ntb_epc->func_no = func_no;
	ntb_epc->type = type;
	ntb_epc->epf_bar = epf_bar;
	ntb_epc->epf_ntb = ntb;

	epc_features = pci_epc_get_features(epc, func_no);
	अगर (!epc_features)
		वापस -EINVAL;
	ntb_epc->epc_features = epc_features;

	ntb->epc[type] = ntb_epc;

	वापस 0;
पूर्ण

/**
 * epf_ntb_epc_create() - Create and initialize NTB EPC पूर्णांकerface
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 *
 * Get a reference to EPC device and bind NTB function device to that EPC
 * क्रम each of the पूर्णांकerface. It is also a wrapper to
 * epf_ntb_epc_create_पूर्णांकerface() to allocate memory क्रम NTB EPC पूर्णांकerface
 * and initialize it
 */
अटल पूर्णांक epf_ntb_epc_create(काष्ठा epf_ntb *ntb)
अणु
	काष्ठा pci_epf *epf;
	काष्ठा device *dev;
	पूर्णांक ret;

	epf = ntb->epf;
	dev = &epf->dev;

	ret = epf_ntb_epc_create_पूर्णांकerface(ntb, epf->epc, PRIMARY_INTERFACE);
	अगर (ret) अणु
		dev_err(dev, "PRIMARY intf: Fail to create NTB EPC\n");
		वापस ret;
	पूर्ण

	ret = epf_ntb_epc_create_पूर्णांकerface(ntb, epf->sec_epc,
					   SECONDARY_INTERFACE);
	अगर (ret) अणु
		dev_err(dev, "SECONDARY intf: Fail to create NTB EPC\n");
		जाओ err_epc_create;
	पूर्ण

	वापस 0;

err_epc_create:
	epf_ntb_epc_destroy_पूर्णांकerface(ntb, PRIMARY_INTERFACE);

	वापस ret;
पूर्ण

/**
 * epf_ntb_init_epc_bar_पूर्णांकerface() - Identअगरy BARs to be used क्रम each of
 *   the NTB स्थिरructs (scratchpad region, करोorbell, memorywinकरोw)
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Identअगरy the मुक्त BARs to be used क्रम each of BAR_CONFIG, BAR_PEER_SPAD,
 * BAR_DB_MW1, BAR_MW2, BAR_MW3 and BAR_MW4.
 */
अटल पूर्णांक epf_ntb_init_epc_bar_पूर्णांकerface(काष्ठा epf_ntb *ntb,
					  क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	स्थिर काष्ठा pci_epc_features *epc_features;
	काष्ठा epf_ntb_epc *ntb_epc;
	क्रमागत pci_barno barno;
	क्रमागत epf_ntb_bar bar;
	काष्ठा device *dev;
	u32 num_mws;
	पूर्णांक i;

	barno = BAR_0;
	ntb_epc = ntb->epc[type];
	num_mws = ntb->num_mws;
	dev = &ntb->epf->dev;
	epc_features = ntb_epc->epc_features;

	/* These are required BARs which are mandatory क्रम NTB functionality */
	क्रम (bar = BAR_CONFIG; bar <= BAR_DB_MW1; bar++, barno++) अणु
		barno = pci_epc_get_next_मुक्त_bar(epc_features, barno);
		अगर (barno < 0) अणु
			dev_err(dev, "%s intf: Fail to get NTB function BAR\n",
				pci_epc_पूर्णांकerface_string(type));
			वापस barno;
		पूर्ण
		ntb_epc->epf_ntb_bar[bar] = barno;
	पूर्ण

	/* These are optional BARs which करोn't impact NTB functionality */
	क्रम (bar = BAR_MW2, i = 1; i < num_mws; bar++, barno++, i++) अणु
		barno = pci_epc_get_next_मुक्त_bar(epc_features, barno);
		अगर (barno < 0) अणु
			ntb->num_mws = i;
			dev_dbg(dev, "BAR not available for > MW%d\n", i + 1);
		पूर्ण
		ntb_epc->epf_ntb_bar[bar] = barno;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_init_epc_bar() - Identअगरy BARs to be used क्रम each of the NTB
 * स्थिरructs (scratchpad region, करोorbell, memorywinकरोw)
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 *
 * Wrapper to epf_ntb_init_epc_bar_पूर्णांकerface() to identअगरy the मुक्त BARs
 * to be used क्रम each of BAR_CONFIG, BAR_PEER_SPAD, BAR_DB_MW1, BAR_MW2,
 * BAR_MW3 and BAR_MW4 क्रम all the पूर्णांकerfaces.
 */
अटल पूर्णांक epf_ntb_init_epc_bar(काष्ठा epf_ntb *ntb)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = &ntb->epf->dev;
	क्रम (type = PRIMARY_INTERFACE; type <= SECONDARY_INTERFACE; type++) अणु
		ret = epf_ntb_init_epc_bar_पूर्णांकerface(ntb, type);
		अगर (ret) अणु
			dev_err(dev, "Fail to init EPC bar for %s interface\n",
				pci_epc_पूर्णांकerface_string(type));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * epf_ntb_epc_init_पूर्णांकerface() - Initialize NTB पूर्णांकerface
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Wrapper to initialize a particular EPC पूर्णांकerface and start the workqueue
 * to check क्रम commands from host. This function will ग_लिखो to the
 * EP controller HW क्रम configuring it.
 */
अटल पूर्णांक epf_ntb_epc_init_पूर्णांकerface(काष्ठा epf_ntb *ntb,
				      क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा epf_ntb_epc *ntb_epc;
	काष्ठा pci_epc *epc;
	काष्ठा pci_epf *epf;
	काष्ठा device *dev;
	u8 func_no;
	पूर्णांक ret;

	ntb_epc = ntb->epc[type];
	epf = ntb->epf;
	dev = &epf->dev;
	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;

	ret = epf_ntb_config_sspad_bar_set(ntb->epc[type]);
	अगर (ret) अणु
		dev_err(dev, "%s intf: Config/self SPAD BAR init failed\n",
			pci_epc_पूर्णांकerface_string(type));
		वापस ret;
	पूर्ण

	ret = epf_ntb_peer_spad_bar_set(ntb, type);
	अगर (ret) अणु
		dev_err(dev, "%s intf: Peer SPAD BAR init failed\n",
			pci_epc_पूर्णांकerface_string(type));
		जाओ err_peer_spad_bar_init;
	पूर्ण

	ret = epf_ntb_configure_पूर्णांकerrupt(ntb, type);
	अगर (ret) अणु
		dev_err(dev, "%s intf: Interrupt configuration failed\n",
			pci_epc_पूर्णांकerface_string(type));
		जाओ err_peer_spad_bar_init;
	पूर्ण

	ret = epf_ntb_db_mw_bar_init(ntb, type);
	अगर (ret) अणु
		dev_err(dev, "%s intf: DB/MW BAR init failed\n",
			pci_epc_पूर्णांकerface_string(type));
		जाओ err_db_mw_bar_init;
	पूर्ण

	ret = pci_epc_ग_लिखो_header(epc, func_no, epf->header);
	अगर (ret) अणु
		dev_err(dev, "%s intf: Configuration header write failed\n",
			pci_epc_पूर्णांकerface_string(type));
		जाओ err_ग_लिखो_header;
	पूर्ण

	INIT_DELAYED_WORK(&ntb->epc[type]->cmd_handler, epf_ntb_cmd_handler);
	queue_work(kpcपूर्णांकb_workqueue, &ntb->epc[type]->cmd_handler.work);

	वापस 0;

err_ग_लिखो_header:
	epf_ntb_db_mw_bar_cleanup(ntb, type);

err_db_mw_bar_init:
	epf_ntb_peer_spad_bar_clear(ntb->epc[type]);

err_peer_spad_bar_init:
	epf_ntb_config_sspad_bar_clear(ntb->epc[type]);

	वापस ret;
पूर्ण

/**
 * epf_ntb_epc_cleanup_पूर्णांकerface() - Cleanup NTB पूर्णांकerface
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 * @type: PRIMARY पूर्णांकerface or SECONDARY पूर्णांकerface
 *
 * Wrapper to cleanup a particular NTB पूर्णांकerface.
 */
अटल व्योम epf_ntb_epc_cleanup_पूर्णांकerface(काष्ठा epf_ntb *ntb,
					  क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा epf_ntb_epc *ntb_epc;

	अगर (type < 0)
		वापस;

	ntb_epc = ntb->epc[type];
	cancel_delayed_work(&ntb_epc->cmd_handler);
	epf_ntb_db_mw_bar_cleanup(ntb, type);
	epf_ntb_peer_spad_bar_clear(ntb_epc);
	epf_ntb_config_sspad_bar_clear(ntb_epc);
पूर्ण

/**
 * epf_ntb_epc_cleanup() - Cleanup all NTB पूर्णांकerfaces
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 *
 * Wrapper to cleanup all NTB पूर्णांकerfaces.
 */
अटल व्योम epf_ntb_epc_cleanup(काष्ठा epf_ntb *ntb)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;

	क्रम (type = PRIMARY_INTERFACE; type <= SECONDARY_INTERFACE; type++)
		epf_ntb_epc_cleanup_पूर्णांकerface(ntb, type);
पूर्ण

/**
 * epf_ntb_epc_init() - Initialize all NTB पूर्णांकerfaces
 * @ntb: NTB device that facilitates communication between HOST1 and HOST2
 *
 * Wrapper to initialize all NTB पूर्णांकerface and start the workqueue
 * to check क्रम commands from host.
 */
अटल पूर्णांक epf_ntb_epc_init(काष्ठा epf_ntb *ntb)
अणु
	क्रमागत pci_epc_पूर्णांकerface_type type;
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = &ntb->epf->dev;

	क्रम (type = PRIMARY_INTERFACE; type <= SECONDARY_INTERFACE; type++) अणु
		ret = epf_ntb_epc_init_पूर्णांकerface(ntb, type);
		अगर (ret) अणु
			dev_err(dev, "%s intf: Failed to initialize\n",
				pci_epc_पूर्णांकerface_string(type));
			जाओ err_init_type;
		पूर्ण
	पूर्ण

	वापस 0;

err_init_type:
	epf_ntb_epc_cleanup_पूर्णांकerface(ntb, type - 1);

	वापस ret;
पूर्ण

/**
 * epf_ntb_bind() - Initialize endpoपूर्णांक controller to provide NTB functionality
 * @epf: NTB endpoपूर्णांक function device
 *
 * Initialize both the endpoपूर्णांक controllers associated with NTB function device.
 * Invoked when a primary पूर्णांकerface or secondary पूर्णांकerface is bound to EPC
 * device. This function will succeed only when EPC is bound to both the
 * पूर्णांकerfaces.
 */
अटल पूर्णांक epf_ntb_bind(काष्ठा pci_epf *epf)
अणु
	काष्ठा epf_ntb *ntb = epf_get_drvdata(epf);
	काष्ठा device *dev = &epf->dev;
	पूर्णांक ret;

	अगर (!epf->epc) अणु
		dev_dbg(dev, "PRIMARY EPC interface not yet bound\n");
		वापस 0;
	पूर्ण

	अगर (!epf->sec_epc) अणु
		dev_dbg(dev, "SECONDARY EPC interface not yet bound\n");
		वापस 0;
	पूर्ण

	ret = epf_ntb_epc_create(ntb);
	अगर (ret) अणु
		dev_err(dev, "Failed to create NTB EPC\n");
		वापस ret;
	पूर्ण

	ret = epf_ntb_init_epc_bar(ntb);
	अगर (ret) अणु
		dev_err(dev, "Failed to create NTB EPC\n");
		जाओ err_bar_init;
	पूर्ण

	ret = epf_ntb_config_spad_bar_alloc_पूर्णांकerface(ntb);
	अगर (ret) अणु
		dev_err(dev, "Failed to allocate BAR memory\n");
		जाओ err_bar_alloc;
	पूर्ण

	ret = epf_ntb_epc_init(ntb);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize EPC\n");
		जाओ err_bar_alloc;
	पूर्ण

	epf_set_drvdata(epf, ntb);

	वापस 0;

err_bar_alloc:
	epf_ntb_config_spad_bar_मुक्त(ntb);

err_bar_init:
	epf_ntb_epc_destroy(ntb);

	वापस ret;
पूर्ण

/**
 * epf_ntb_unbind() - Cleanup the initialization from epf_ntb_bind()
 * @epf: NTB endpoपूर्णांक function device
 *
 * Cleanup the initialization from epf_ntb_bind()
 */
अटल व्योम epf_ntb_unbind(काष्ठा pci_epf *epf)
अणु
	काष्ठा epf_ntb *ntb = epf_get_drvdata(epf);

	epf_ntb_epc_cleanup(ntb);
	epf_ntb_config_spad_bar_मुक्त(ntb);
	epf_ntb_epc_destroy(ntb);
पूर्ण

#घोषणा EPF_NTB_R(_name)						\
अटल sमाप_प्रकार epf_ntb_##_name##_show(काष्ठा config_item *item,		\
				      अक्षर *page)			\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा epf_ntb *ntb = to_epf_ntb(group);			\
									\
	वापस प्र_लिखो(page, "%d\n", ntb->_name);			\
पूर्ण

#घोषणा EPF_NTB_W(_name)						\
अटल sमाप_प्रकार epf_ntb_##_name##_store(काष्ठा config_item *item,	\
				       स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा epf_ntb *ntb = to_epf_ntb(group);			\
	u32 val;							\
	पूर्णांक ret;							\
									\
	ret = kstrtou32(page, 0, &val);					\
	अगर (ret)							\
		वापस ret;						\
									\
	ntb->_name = val;						\
									\
	वापस len;							\
पूर्ण

#घोषणा EPF_NTB_MW_R(_name)						\
अटल sमाप_प्रकार epf_ntb_##_name##_show(काष्ठा config_item *item,		\
				      अक्षर *page)			\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा epf_ntb *ntb = to_epf_ntb(group);			\
	पूर्णांक win_no;							\
									\
	माला_पूछो(#_name, "mw%d", &win_no);				\
									\
	वापस प्र_लिखो(page, "%lld\n", ntb->mws_size[win_no - 1]);	\
पूर्ण

#घोषणा EPF_NTB_MW_W(_name)						\
अटल sमाप_प्रकार epf_ntb_##_name##_store(काष्ठा config_item *item,	\
				       स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा epf_ntb *ntb = to_epf_ntb(group);			\
	काष्ठा device *dev = &ntb->epf->dev;				\
	पूर्णांक win_no;							\
	u64 val;							\
	पूर्णांक ret;							\
									\
	ret = kstrtou64(page, 0, &val);					\
	अगर (ret)							\
		वापस ret;						\
									\
	अगर (माला_पूछो(#_name, "mw%d", &win_no) != 1)			\
		वापस -EINVAL;						\
									\
	अगर (ntb->num_mws < win_no) अणु					\
		dev_err(dev, "Invalid num_nws: %d value\n", ntb->num_mws); \
		वापस -EINVAL;						\
	पूर्ण								\
									\
	ntb->mws_size[win_no - 1] = val;				\
									\
	वापस len;							\
पूर्ण

अटल sमाप_प्रकार epf_ntb_num_mws_store(काष्ठा config_item *item,
				     स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा config_group *group = to_config_group(item);
	काष्ठा epf_ntb *ntb = to_epf_ntb(group);
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val > MAX_MW)
		वापस -EINVAL;

	ntb->num_mws = val;

	वापस len;
पूर्ण

EPF_NTB_R(spad_count)
EPF_NTB_W(spad_count)
EPF_NTB_R(db_count)
EPF_NTB_W(db_count)
EPF_NTB_R(num_mws)
EPF_NTB_MW_R(mw1)
EPF_NTB_MW_W(mw1)
EPF_NTB_MW_R(mw2)
EPF_NTB_MW_W(mw2)
EPF_NTB_MW_R(mw3)
EPF_NTB_MW_W(mw3)
EPF_NTB_MW_R(mw4)
EPF_NTB_MW_W(mw4)

CONFIGFS_ATTR(epf_ntb_, spad_count);
CONFIGFS_ATTR(epf_ntb_, db_count);
CONFIGFS_ATTR(epf_ntb_, num_mws);
CONFIGFS_ATTR(epf_ntb_, mw1);
CONFIGFS_ATTR(epf_ntb_, mw2);
CONFIGFS_ATTR(epf_ntb_, mw3);
CONFIGFS_ATTR(epf_ntb_, mw4);

अटल काष्ठा configfs_attribute *epf_ntb_attrs[] = अणु
	&epf_ntb_attr_spad_count,
	&epf_ntb_attr_db_count,
	&epf_ntb_attr_num_mws,
	&epf_ntb_attr_mw1,
	&epf_ntb_attr_mw2,
	&epf_ntb_attr_mw3,
	&epf_ntb_attr_mw4,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type ntb_group_type = अणु
	.ct_attrs	= epf_ntb_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/**
 * epf_ntb_add_cfs() - Add configfs directory specअगरic to NTB
 * @epf: NTB endpoपूर्णांक function device
 * @group: A poपूर्णांकer to the config_group काष्ठाure referencing a group of
 *	   config_items of a specअगरic type that beदीर्घ to a specअगरic sub-प्रणाली.
 *
 * Add configfs directory specअगरic to NTB. This directory will hold
 * NTB specअगरic properties like db_count, spad_count, num_mws etc.,
 */
अटल काष्ठा config_group *epf_ntb_add_cfs(काष्ठा pci_epf *epf,
					    काष्ठा config_group *group)
अणु
	काष्ठा epf_ntb *ntb = epf_get_drvdata(epf);
	काष्ठा config_group *ntb_group = &ntb->group;
	काष्ठा device *dev = &epf->dev;

	config_group_init_type_name(ntb_group, dev_name(dev), &ntb_group_type);

	वापस ntb_group;
पूर्ण

/**
 * epf_ntb_probe() - Probe NTB function driver
 * @epf: NTB endpoपूर्णांक function device
 *
 * Probe NTB function driver when endpoपूर्णांक function bus detects a NTB
 * endpoपूर्णांक function.
 */
अटल पूर्णांक epf_ntb_probe(काष्ठा pci_epf *epf)
अणु
	काष्ठा epf_ntb *ntb;
	काष्ठा device *dev;

	dev = &epf->dev;

	ntb = devm_kzalloc(dev, माप(*ntb), GFP_KERNEL);
	अगर (!ntb)
		वापस -ENOMEM;

	epf->header = &epf_ntb_header;
	ntb->epf = epf;
	epf_set_drvdata(epf, ntb);

	वापस 0;
पूर्ण

अटल काष्ठा pci_epf_ops epf_ntb_ops = अणु
	.bind	= epf_ntb_bind,
	.unbind	= epf_ntb_unbind,
	.add_cfs = epf_ntb_add_cfs,
पूर्ण;

अटल स्थिर काष्ठा pci_epf_device_id epf_ntb_ids[] = अणु
	अणु
		.name = "pci_epf_ntb",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pci_epf_driver epf_ntb_driver = अणु
	.driver.name	= "pci_epf_ntb",
	.probe		= epf_ntb_probe,
	.id_table	= epf_ntb_ids,
	.ops		= &epf_ntb_ops,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init epf_ntb_init(व्योम)
अणु
	पूर्णांक ret;

	kpcपूर्णांकb_workqueue = alloc_workqueue("kpcintb", WQ_MEM_RECLAIM |
					    WQ_HIGHPRI, 0);
	ret = pci_epf_रेजिस्टर_driver(&epf_ntb_driver);
	अगर (ret) अणु
		destroy_workqueue(kpcपूर्णांकb_workqueue);
		pr_err("Failed to register pci epf ntb driver --> %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(epf_ntb_init);

अटल व्योम __निकास epf_ntb_निकास(व्योम)
अणु
	pci_epf_unरेजिस्टर_driver(&epf_ntb_driver);
	destroy_workqueue(kpcपूर्णांकb_workqueue);
पूर्ण
module_निकास(epf_ntb_निकास);

MODULE_DESCRIPTION("PCI EPF NTB DRIVER");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
