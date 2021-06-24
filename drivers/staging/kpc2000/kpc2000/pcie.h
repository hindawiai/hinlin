<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित KP2000_PCIE_H
#घोषणा KP2000_PCIE_H
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश "../kpc.h"
#समावेश "dma_common_defs.h"

/*      System Register Map (BAR 1, Start Addr 0)
 *
 *  BAR Size:
 *  1048576 (0x100000) bytes = 131072 (0x20000) रेजिस्टरs = 256 pages (4K)
 *
 *             6         5         4         3         2         1         0
 *          3210987654321098765432109876543210987654321098765432109876543210
 *      0   <--------------------------- MAGIC ---------------------------->
 *      1   <----------- Card ID ---------><----------- Revision ---------->
 *      2   <--------- Date Stamp --------><--------- Time Stamp ---------->
 *      3   <-------- Core Tbl Len -------><-------- Core Tbl Offset ------>
 *      4   <---------------------------- SSID ---------------------------->
 *      5                                                           < HWID >
 *      6   <------------------------- FPGA DDNA -------------------------->
 *      7   <------------------------ CPLD Config ------------------------->
 *      8   <----------------------- IRQ Mask Flags ----------------------->
 *      9   <---------------------- IRQ Active Flags ---------------------->
 */

#घोषणा REG_WIDTH			8
#घोषणा REG_MAGIC_NUMBER		(0 * REG_WIDTH)
#घोषणा REG_CARD_ID_AND_BUILD		(1 * REG_WIDTH)
#घोषणा REG_DATE_AND_TIME_STAMPS	(2 * REG_WIDTH)
#घोषणा REG_CORE_TABLE_OFFSET		(3 * REG_WIDTH)
#घोषणा REG_FPGA_SSID			(4 * REG_WIDTH)
#घोषणा REG_FPGA_HW_ID			(5 * REG_WIDTH)
#घोषणा REG_FPGA_DDNA			(6 * REG_WIDTH)
#घोषणा REG_CPLD_CONFIG			(7 * REG_WIDTH)
#घोषणा REG_INTERRUPT_MASK		(8 * REG_WIDTH)
#घोषणा REG_INTERRUPT_ACTIVE		(9 * REG_WIDTH)
#घोषणा REG_PCIE_ERROR_COUNT		(10 * REG_WIDTH)

#घोषणा KP2000_MAGIC_VALUE		0x196C61482231894DULL

#घोषणा PCI_VENDOR_ID_DAKTRONICS	0x1c33
#घोषणा PCI_DEVICE_ID_DAKTRONICS	0x6021

#घोषणा DMA_BAR				0
#घोषणा REG_BAR				1

काष्ठा kp2000_device अणु
	काष्ठा pci_dev		*pdev;
	अक्षर			name[16];

	अचिन्हित पूर्णांक		card_num;
	काष्ठा mutex		sem;

	व्योम __iomem		*sysinfo_regs_base;
	व्योम __iomem		*regs_bar_base;
	काष्ठा resource		regs_base_resource;
	व्योम __iomem		*dma_bar_base;
	व्योम __iomem		*dma_common_regs;
	काष्ठा resource		dma_base_resource;

	// "System Registers"
	u32			card_id;
	u32			build_version;
	u32			build_datestamp;
	u32			build_बारtamp;
	u32			core_table_offset;
	u32			core_table_length;
	u8			core_table_rev;
	u8			hardware_revision;
	u64			ssid;
	u64			ddna;

	// IRQ stuff
	अचिन्हित पूर्णांक		irq;

	काष्ठा list_head	uio_devices_list;
पूर्ण;

बाह्य काष्ठा class *kpc_uio_class;
बाह्य काष्ठा attribute *kpc_uio_class_attrs[];

पूर्णांक kp2000_probe_cores(काष्ठा kp2000_device *pcard);
व्योम kp2000_हटाओ_cores(काष्ठा kp2000_device *pcard);

// Define this quick little macro because the expression is used frequently
#घोषणा PCARD_TO_DEV(pcard)	(&(pcard->pdev->dev))

#पूर्ण_अगर /* KP2000_PCIE_H */
